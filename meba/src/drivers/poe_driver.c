// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/i2c-dev.h>  /* I2C support */
#include <errno.h>
#include <microchip/ethernet/board/api.h>
#include "../meba_aux.h"
#include "../meba_generic.h"
#include "poe_driver.h"

#define VTSS_MSLEEP(m) usleep((m)*1000)

#define INTERUPTIBLE_POE_OFF_TIME         5000  // for how many ms to turn off all poe ports and turn on only the cfg enabled poe ports
#define PD_BUFFER_SIZE                    15    // PoE 15bytes message length is 15 bytes

#define MAX_STR_SIZE  100

// poe adc pin reading - will be defined from version 3.57 and above
//#define POE_READ_ADC_PIN


// The sequence number is updated by the transmit function, but we have to insert a dummy seq number when building the data structure.
#define DUMMY_SEQ_NUM                           0x00
#define SEQ_NUM_TELEMETRY_AFTER_RESET           0xFF
#define SEQ_NUM_DO_NOT_CHK                      0xFF
#define DUMMY_BYTE                              0x4E

// BT individual masks - stay with defaults
#define INDV_MASK_BT_IGNORE_HIGHER_PRIORITY     0x00
#define INDV_MASK_BT_SUPPORT_HIGH_RES_DETECTION 0x10
#define INDV_MASK_BT_I2C_RESTART_ENABLE         0x1B
#define INDV_MASK_BT_LED_STREAM_TYPE            0x20
#define INDV_MASK_BT_HOCPP                      0x50
#define INDV_MASK_BT_PSE_POWERING_PSE_CHECKING               0x1F
#define INDV_MASK_BT_LAYER2_POWER_ALLOCATION_LIMIT           0x2C
#define INDV_MASK_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY       0x4F

// BT individual masks - configuration depends on product
#define INDV_MASK_BT_LED_STREAM_TYPE             0x20
#define INDV_MASK_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR 0x30
#define INDV_MASK_BT_xSYSTEM_OK_PIN_BEHAVIOR     0x40


// AT individual masks - stay with defaults
#define INDV_MASK_AT_IGNORE_HIGHER_PRIORITY     0x00
#define INDV_MASK_AT_SUPPORTS_LEGACY_DETECTION  0x01
#define INDV_MASK_AT_MESSAGE_READY_NOTIFY       0x1E
#define INDV_MASK_AT_LAYER2_LLDP_ENABLE         0x2E
#define INDV_MASK_AT_LAYER2_PRIORITY_BY_PD      0x2F
#define INDV_MASK_AT_MATRIX_SUPPORT_4P          0x34

// AT individual masks - configuration depends on product
#define INDV_MASK_AT_SUPPORTS_BACKOFF           0x11
#define INDV_MASK_AT_LED_STREAM_TYPE            0x16
#define INDV_MASK_AT_PSE_POWERING_PSE_CHECKING  0x1F
#define INDV_MASK_AT_xSYSTEM_OK_PIN_BEHAVIOR	0x28
#define INDV_MASK_AT_ENABLE_ASIC_REFRESH        0x2A
#define INDV_MASK_AT_LAYER2_LLDP_ENABLE         0x2E
#define INDV_MASK_AT_CLASS_0_EQUAL_AF	        0x38
#define INDV_MASK_AT_CLASS_1_2_3_EQUAL_AF       0x39
#define INDV_MASK_AT_LLDP_BEST_EFFORT	        0x47
#define INDV_MASK_AT_AUTO_ZONE2_PORT_ACTIVATION 0x49
#define INDV_MASK_AT_HOCPP_HIGH_OVER_CURRENT_PULSE_PROTECTION	 0x50



#define LINE_SIZE_MAX         100 // PoE firmware file line max size in bytes
#define POE_FIRMWARE_SIZE_MAX 2000000 // Maximum size of the PoE firmware in bytes (file mscc_firmware.txt)
#define MAX_POE_TYPES         4       // 4 types - BT (15W,30W,60W,90W)

#define MESA_RC(EXPR) { mesa_rc rc = EXPR; if (rc != MESA_RC_OK) { return rc; } }

#define DEBUG(_inst, _lvl, _fmt, ...) do { ((poe_driver_private_t *)((_inst)->private_data))->debug(_lvl, __FILE__, __LINE__, "(%s) " _fmt, _inst->adapter_name, ##__VA_ARGS__); } while (0)


// Section 4.1. in PD69200 user guide - key definitions
enum KEYS
{
    COMMAND_KEY            =  0x00 ,
    PROGRAM_KEY            =  0x01 ,
    REQUEST_KEY            =  0x02 ,
    TELEMETRY_KEY          =  0x03 ,
    CHANNEL_KEY            =  0x05 ,
    E2_KEY                 =  0x06 ,
    GLBL_KEY               =  0x07 ,
    PRIORITY_KEY           =  0x0A ,
    SUPPLY_KEY             =  0x0B ,
    ENABLE_DISABLE_KEY     =  0x0C ,
    PORT_STATUS_KEY        =  0x0E ,
    SAVE_CONFIG_KEY        =  0x0F ,
    PRDCTINFO_KEY          =  0x13 ,
    MAIN_KEY               =  0x17 ,
    MEASUREMENTS_KEY       =  0x1A ,
    VERSIONZ_KEY           =  0x1E ,
    SW_VERSION_KEY         =  0x21 ,
    PARAMZ_KEY             =  0x25 ,
    SET_SYSTEM_MASKS       =  0x2B ,
    RESTORE_FACT_KEY       =  0x2D ,
    SYSTEM_STATUS_KEY      =  0x3D ,
    TMP_MATRIX_KEY         =  0x43 ,
    CHANNEL_MATRIX_KEY     =  0x44 ,
    LAYER2_BT_LLDP_PD_KEY  =  0x50 ,
    LAYER2_BT_LLDP_PSE_KEY =  0x51 ,
    REPORT_KEY             =  0x52 ,
    RESET_KEY              =  0x55 ,
    INDIV_MASK_KEY         =  0x56 ,
    POWER_BUDGET_KEY       =  0x57 ,
    POWER_MANAGE_MODE_KEY  =  0x5F ,
    TOTAL_POWER_KEY        =  0x60 ,
    TEMPORARY_SUPPLY_KEY   =  0xA2 ,
    LAYER2_LLDP_PD_KEY     =  0xA6 ,
    LLDP_PSE_KEY           =  0xA8 ,
    ACTUAL_SYSTEM_DATA_KEY =  0xAD ,
    ADC_KEY                =  0xAE ,
    PortFullInit4Pair_KEY  =  0xAF ,
    BT_PORT_CONFIG1_KEY    =  0xC0 ,
    BT_PORT_STATUS_KEY     =  0xC1 ,
    BT_PORT_CLASS_KEY      =  0xC4 ,
    BT_PORT_MEASE_KEY      =  0xC5 ,
    BT_SYSTEM_STATUS_KEY   =  0xD0 ,
    BT_EVENT_KEY           =  0xD1 ,
    BT_CLASS_PWR_KEY       =  0xD2 ,
    SYSTEM_STATUS_ECHO_KEY =  0xFF ,
};


enum MAX_CLASS_NUMBER_e
{
    ePOE_CLASS_MAX_PWR_15W =  3,
    ePOE_CLASS_MAX_PWR_30W =  4,
    ePOE_CLASS_MAX_PWR_60W =  6,
    ePOE_CLASS_MAX_PWR_90W =  8
};


enum BT_PORT_STATUS_e
{
    //---------------------------------------------------------------------------------------------------------------
    //                                        #  --------- SNMP COUNTERS ---------- #  SNMP Port       #
    //                                        # Absnt # Inv  # Pwr   # Over # Short #  Detection       #
    //                                        # (UDL) # Sig  # Dnied # Load #       #  Status          #
    //---------------------------------------------------------------------------------------------------------------

    //--- Port off ---//
    eBT_0x06_OFF_Main_supply_voltage_is_high        = 0x06,
    eBT_0x07_OFF_Main_supply_voltage_is_low         = 0x07,
    eBT_0x08_OFF_Disable_all_ports_pin_is_active    = 0x08,
    eBT_0x0C_OFF_Non_existing_port_number           = 0x0C,
    eBT_0x11_OFF_Port_is_yet_undefined              = 0x11,
    eBT_0x12_OFF_Internal_hardware_fault            = 0x12,
    eBT_0x1A_OFF_User_setting                       = 0x1A,
    eBT_0x1B_OFF_Detection_is_in_process            = 0x1B,
    eBT_0x1C_OFF_Non_802_3AF_AT_powered_device      = 0x1C,
    eBT_0x1E_OFF_Underload_state                    = 0x1E,
    eBT_0x1F_OFF_Overload_state                     = 0x1F,
    eBT_0x20_OFF_Power_budget_exceeded              = 0x20,
    eBT_0x21_OFF_Internal_hardware_routing_error    = 0x21,
    eBT_0x22_OFF_Configuration_change               = 0x22,
    eBT_0x24_OFF_Voltage_injection_into_the_port    = 0x24,
    eBT_0x25_OFF_Improper_Cap_Det_results_or_Det_val_indicating_short = 0x25,
    eBT_0x26_OFF_Discharged_load                    = 0x26,
    eBT_0x34_OFF_Short_condition                    = 0x34,
    eBT_0x35_OFF_Over_temperature_at_the_port       = 0x35,
    eBT_0x36_OFF_Device_is_too_hot                  = 0x36,
    eBT_0x37_Unknown_device_port_status             = 0x37,
    eBT_0x3C_OFF_Power_Mng_Static_calc_pwr_exceed_pwr_limit  = 0x3C,
    eBT_0x3D_OFF_Power_Management_Static_ovl                 = 0x3D,
    eBT_0x41_OFF_Power_denied_Hardware_power_limit  = 0x41,
    eBT_0x43_OFF_Class_Error                        = 0x43,
    eBT_0x44_OFF_Port_turn_off_during_host_crash    = 0x44,
    eBT_0x45_OFF_Delivering_power_forced_off_during_host_crash  = 0x45,
    eBT_0x46_OFF_Enabled_port_forced_off_during_host_crash      = 0x46,
    eBT_0x47_OFF_Forced_power_crash_error                       = 0x47,
    eBT_0x48_OFF_recovery_UDL                       = 0x48,
    eBT_0x49_OFF_recovery_PG                        = 0x49,
    eBT_0x4A_OFF_recovery_OVL                       = 0x4A,
    eBT_0x4B_OFF_recovery_SC                        = 0x4B,
    eBT_0x4C_OFF_recovery_voltage_injection         = 0x4C,

    //--- Port delivering ---//
    eBT_0x80_ON_2P_Port_delivering_non_IEEE         = 0x80,
    eBT_0x81_ON_2P_Port_delivering_IEEE             = 0x81,
    eBT_0x82_ON_4P_Port_that_deliver_only_2_Pair_non_IEEE = 0x82,
    eBT_0x83_ON_4P_Port_delivering_2P_non_IEEE      = 0x83,
    eBT_0x84_ON_4P_Port_delivering_4P_non_IEEE      = 0x84,
    eBT_0x85_ON_4P_Port_delivering_2P_IEEE_SSPD     = 0x85,
    eBT_0x86_ON_4P_Port_delivering_4P_IEEE_SSPD     = 0x86,
    eBT_0x87_ON_4P_Port_delivering_4P_IEEE_DSPD_1st_phase = 0x87,
    eBT_0x88_ON_4P_Port_delivering_2P_IEEE_DSPD     = 0x88,
    eBT_0x89_ON_4P_Port_delivering_4P_IEEE_DSPD     = 0x89,
    eBT_0x90_ON_Force_Power_BT_2P                   = 0x90,
    eBT_0x91_ON_Force_Power_BT_4P                   = 0x91,

    //--- Port error ---//
    eBT_0xA0_OFF_Force_Power_BT_Error               = 0xA0,

    //--- Port noral searching ---//
    eBT_0xA7_OFF_Connection_Check_error             = 0xA7,  // normal Ethernet none PD device is connected
    eBT_0xA8_OFF_Open_Port_is_not_connected         = 0xA8,  // Nopthing is conencted to teh Etehrnet port

    eBT_0xFF_PORT_STATUS_ONKNOWN                    = 255    // internal soft state which mark that port status was never read and updated
};


// possible values rec by 'GET_SINGLE_PORT_STATUS' or 'GET_ALL_PORTS_STATUS'
enum ePORT_STATUS
{
    //---------------------------------------------------------------------------------------------------------------
    //                                             #  SNMP Port       #
    //                                             #  Detection       #
    //                                             #  Status          #
    //-------------------------------------------------------------------------
    eAT_0x00_ON__LEGACY_PD_DET                =  0, //# eDELIVERINGPOWER # Legacy PD was detected
    eAT_0x01_ON__802_2PAIR_3AF_DET            =  1, //# eDELIVERINGPOWER # Valid PD which comply to 802.3AF spec was detected, or only two pair out of 4 pair are ON (Midspan 95xxG)
    eAT_0x02_ON__802_4PAIR_DET                =  2, //# eDELIVERINGPOWER # 95xxG Midspan apply power to both pairs (data+spare)
    eAT_0x03_ON__802_2PAIR_POWER_SEQUENCE     =  3, //# eDELIVERINGPOWER # PD is powered as ALT_A in CDP mode. ALT_B is waiting for turn on command.
    eAT_0x04_ON__802_4PAIR_POWER_SEQUENCE     =  4, //# eDELIVERINGPOWER # ALT_A and ALT_B are powered in CDP Mode.#
    eAT_0x06_OFF_MAIN_PS_TO_HIGH              =  6, //#                  # Main voltage is higher then limit - cause all ports to be shut down
    eAT_0x07_OFF_MAIN_PS_TO_LOW               =  7, //#                  # Main voltage is lower then limit - cause all ports to be shut down
    eAT_0x08_OFF_DIS_ALL_PORTS_PIN_ACT        =  8, //# eDISABLED        # HW pin disable all ports
    eAT_0x09_OFF_DERATING_TEMPERATURE_HIGH    =  9, //# eOTHERFAULT      # 95xxG Temperature is so high, that HC08 shut down all PoE ports
    eAT_0x0C_OFF_NON_EXIST_PORT_NUM           = 12, //#                  # Port number that doesn't exist
    eAT_0x11_OFF_PWR_UP_IN_PROCESS            = 17, //# eOTHERFAULT      # Interium state during power-up. State will be changed.
    eAT_0x12_OFF_INTERNAL_HW_FAULT            = 18, //#                  # Port doesn't responed, or HW failure
    eAT_0x1A_OFF_USER_SETTING                 = 26, //# eDISABLED        # Set to off by user
    eAT_0x1B_OFF_DET_IN_PROCESS               = 27, //# eSEARCHING       # Interium state during line detection. State will be changed.
    eAT_0x1C_OFF_NON_802_3AF_PD               = 28, //#                  # Non standart PD is connected
    eAT_0x1D_OFF_SUCCESION_OF_OVL_AND_UDL     = 29, //# eOTHERFAULT      # PD consume more or less then - cause port to be shut down
    eAT_0x1E_OFF_UNDERLOAD_OR_CAP_TO_SMALL    = 30, //# eFAULT           # underload according to 802.3AF, or capacitor is bellow 22uf
    eAT_0x1F_OFF_OVERLOAD_OR_CAP_TO_BIG       = 31, //# eFAULT           # Overload according to 802.3AF, or capacitor is above 1000uf
    eAT_0x20_OFF_PWR_BUDGET_EXCEDDED          = 32, //# eOTHERFAULT      # Power Management shut down the port due to lack of power
    eAT_0x21_OFF_INTERNAL_HW_ROUTING_ERROR    = 33, //# eOTHERFAULT      # HW problems prevent port operation
    eAT_0x24_OFF_EXT_VOLT_INJ_CAP_DET_MODE    = 36, //#                  # Port fails cap det due to voltage being applied to the port
    eAT_0x25_OFF_IMPROPER_CAP_DET_MODE        = 37, //#                  # Port fails Capacitor detection due to out-of-range cap value
    eAT_0x26_OFF_DISCHARGED_LOAD_CAP_DET_MODE = 38, //#                  # Port fails Cap Det due to discharged capacitor
                                                    //#                  #
    eAT_0x2B_ON__FORCE                        = 43, //# eTEST            # Port was forced to turn on
    eAT_0x2C_OFF_FORCE_ERROR                  = 44, //# eOTHERFAULT      # Port was forced to ON, and shut down due to other error was shut down
    eAT_0x2D_OFF_FORCE_PS_TOO_HIGH            = 45, //# eOTHERFAULT      # Port was forced to ON, and detected that power supply is to high
    eAT_0x2E_OFF_FORCE_PS_TOO_LOW             = 46, //# eOTHERFAULT      # Port was forced to ON, and detected that power supply is to low
    eAT_0x2F_OFF_FORCE_DIS_PDU_FLAG_WAS_RAISE = 47, //# eOTHERFAULT      # Port was forced to ON, and Disable PDU flag was raise
    eAT_0x30_OFF_FORCE_DIS_COMMAND_WAS_REC    = 48, //# eOTHERFAULT      # Port was forced ON, and disable command was rec
    eAT_0x31_OFF_FORCE_802_3AF_OVERLOAD       = 49, //# eFAULT           # 802.3AF overload condition during force on
    eAT_0x32_OFF_FORCE_OUT_OF_PWR_BUDGET      = 50, //# eOTHERFAULT      # Power management det out of power. Port is down or denied.
    eAT_0x33_UNKNOWN_FORCE_COMMUNICATION_ERR  = 51, //# eOTHERFAULT      # Port was forced ON, and comm with ASIC occure
    eAT_0x34_OFF_SHORT_CONDITION              = 52, //# eFAULT           # Short condition was detected at a port delivering power
    eAT_0x35_OFF_OVER_TEMP_AT_PORT            = 53, //#                  # Port temperature protection was activated
    eAT_0x36_OFF_DEVICE_TOO_HOT               = 54, //#                  # DIE temp is above safe operation value
    eAT_0x37_OFF_UNKNOWN_DEVICE_PORT_STATUS   = 55, //# eOTHERFAULT      # The device returns an unknown port status for the software
    eAT_0x38_OFF_FORCE_PWR_ERR_SHORT_CIRCUIT  = 56, //# eFAULT           # Short in the port during force On
    eAT_0x39_OFF_FORCE_PWR_ERR_CH_OVER_TEMP   = 57, //# eOTHERFAULT      # Channel over temperature during Force-ON
    eAT_0x3A_OFF_FORCE_PWR_ERR_CHIP_OVER_TEMP = 58, //# eOTHERFAULT      # Device over temperature during force-ON
                                                    //#                  #
    eAT_0x3C_OFF_PWR_MANAGEMENT_STATIC        = 60, //# eOTHERFAULT      # Calculated power > power limit
    eAT_0x3D_OFF_PWR_MANAGEMENT_STATIC_OV     = 61, //# eOTHERFAULT      # PD class report > user predefined power value
    eAT_0x3E_OFF_FORCE_PWR_ERR_MNGMNT_STAT    = 62, //# eOTHERFAULT      # Calculated power > power limit during Force-ON
    eAT_0x3F_OFF_FORCE_PWR_ERR_MNGMNT_STAT_OV = 63, //# eOTHERFAULT      # PD class report > user predefined power value during force ON
    eAT_0x40_ON__HIGH_POWER_PORT_IS_ON        = 64, //# eDELIVERINGPOWER # PD get power from two PSE ports
    eAT_0x41_OFF_CHIP_OVER_POWER              = 65, //# eOTHERFAULT      # Total Chip power delivery exceed max limit.
    eAT_0x42_OFF_FORCE_PWR_ERR_CHIP_OVR_PWR   = 66, //# eOTHERFAULT      # Total Chip power delivery exceed max limit.
    eAT_0x43_OFF_CLASS_ERROR                  = 67, //# eOTHERFAULT      # 90xxG Midspan Rotem based - Invalid Class signature, don't power PD.
    eAT_0x44_OFF_DURING_HOST_CRASH            = 68, //# eOTHERFAULT      # This status appears due to OVL,UDL or Short events during host crash.
    eAT_0x45_OFF_FROM_DELIVERED_TO_HOST_SHUTDOWN = 69, //# eOTHERFAULT   # Port is off - The port was delivering power before host crash but was configured to be forced shut when host crashes.
    eAT_0x46_OFF_FROM_ENABLED_TO_HOST_SHUTDOWN = 70,//# eOTHERFAULT      # Port is off - The port was enabled and not delivering power before host crash and was configured to be forced shut when host crashes.
    eAT_0x47_OFF_FORCE_POWER_CRASH_ERROR      = 71, //# eOTHERFAULT      # Port is off - Port is at force power error, according to IEEE test mode error. The port was forced power and host crash occurred.
    eAT_0x48_OFF_RECOVERY_UDL                 = 72, //# eOTHERFAULT      # During crash a recovery port delivering power was disconnected due to UDL.
    eAT_0x49_OFF_RECOVERY_PG_EVENT            = 73, //# eOTHERFAULT      # During crash a recovery port delivering power was disconnected due to PG event.
    eAT_0x4A_OFF_RECOVERY_OVL                 = 74, //# eOTHERFAULT      # During crash a recovery port delivering power was disconnected due to OVL.
    eAT_0x4B_OFF_RECOVERY_SC                  = 75, //# eOTHERFAULT      # During crash a recovery port delivering power was disconnected due to SC.
    eAT_0x4C_OFF_RECOVERY_VOLTAGE_INJECTION   = 76, //# eOTHERFAULT      # Voltage was applied to the port from external source, during or before crash.
    eAT_0x4D_OFF_DVDT_FAIL_DURING_STARTUP     = 77, //# eOTHERFAULT      # DVDT algorithm that checks power up sequence failed to power up the port.

    eAT_PORT_STATUS_ONKNOWN_0xFF              = 255 //                   # internal NMS soft state which mark that port status was never read and updated.
};


typedef enum
{
    ePD69200_AT = 22,
    ePD69200_BT = 24,
    ePD69210_AT = 27,
    ePD69210_BT = 26,
    ePD69220_AT = 28,
    ePD69220_BT = 29,
    ePD69200M_AT = 23,
    ePD69200M_BT = 25
}PoE_Controller_Type_prod_e;


typedef enum
{
    ePort_Disable                          = 0,
    ePort_Enable                           = 1,
    ePort_Enable_with_ignored_inrush_check = 2,
    ePort_Force_Power_4P_60w__2P_30w       = 3,
    ePort_Force_Power_4P_90w__2P_45w       = 4,
    ePort_EnDis_No_change                  = 0xF
}CFG1_0_3_Port_EnDis_Modes_e;


typedef enum
{
    eIgnore_PD_Auto_Class_Request_bit1         = 1,
    eSpecial_Port_Configuration_Bits_No_change = 0xF
}Special_Port_Configuration_Bits_e;


typedef enum //bits[3..0] ? BT port PM mode
{
    eBT_port_PM_mode_dynamic_Iport_x_Vmain = 0,                              // 0
    eBT_port_PM_mode_TPPL_BT,                                                // 1
    eBT_port_PM_mode_Dynamic_for_non_LLDP_ports_and_TPPL_BT_for_LLDP_ports,  // 2
    eBT_port_PM_mode_Do_not_change_settings = 0xF                            // 0xF
}CFG2_0_3_PM_mode_e;


typedef enum //bits[7..4] ? Class Error Operation Select
{
    eClass_error_configuration_is_disabled = 0,
    eClass_error_Request_class_SSPD_3_DSPD_3, //0x1
    eClass_error_Request_class_SSPD_4_DSPD_3, //0x2
    eClass_error_Request_class_SSPD_6_DSPD_4, //0x3
    eClass_error_Request_class_SSPD_8_DSPD_5, //0x4
    //0x5 to 0xE ? Reserved for future usage
    eClass_error_Do_not_change_settings = 0xF
}CFG2_4_7_Class_Error_Operation_Select_e;


typedef enum
{
    eBT_Disable = 0,
    eBT_Enable = 1,
    eBT_State_No_change = 0xF
}BT_EN_e;


typedef enum
{
    // 4Pair/2Pair BT Compliant Modes
    eBT_Compliant_4P_90w_2P_30w = 0,
    eBT_Compliant_4P_60w_2P_30w = 1,
    eBT_Compliant_4P_30w_2P_30w = 2,
    eBT_Compliant_4P_15w_2P_15w = 3,

    // 4Pair/2Pair Non Compliant Modes
    eBT_Non_Compliant_4P_90w_2P_30w_Legacy = 0x10,
    eBT_Non_Compliant_4P_60w_2P_30w_Legacy = 0x11,
    eBT_Non_Compliant_4P_30w_2P_30w_Legacy = 0x12,
    eBT_Non_Compliant_4P_15w_2P_15w_Legacy = 0x13,

    // 4Pair/2Pair Non Compliant Special Modes
    eBT_Non_Compliant_4P_BT_90w_2P_BT_45w_PoH_Like_On_class_4_Legacy = 0x20,
    eBT_Non_Compliant_4P_PreBT_2P_PreBT_30w_60w_Legacy               = 0x21,
    eBT_Non_Compliant_4P_BT_90w_2P_BT_Special_45w_Legacy             = 0x30,

    eBT_Mode_No_change                                               = 0xFF,
} Port_Operation_Mode_e;


typedef enum {
    ePORT_PRIORITY_CRITICAL = 1,  // Highest port power priority
    ePORT_PRIORITY_HIGH     = 2,  // Medium port power priority
    ePORT_PRIORITY_LOW      = 3,  // Least port power priority. */
    ePORT_PRIORITY_NoChange = 0xFF
} port_power_priority_e;


typedef enum
{
    eBoot_Unknown_error = 0,
    eBoot_error_Application_CRC_error_Download_is_required_for_PD69200,
    eBoot_error_Application_CRC_error_Download_is_required_for_PD69210_PD69220,
    eBoot_error_hw_error_from_Boot_try_to_program_a_PD69200_firmware_into_PD69210_PD69220_device,
    eBoot_error_hW_error_from_Boot_try_to_program_a_PD69210_PD69220_firmware_into_PD69200_device,
    eBoot_error_sys_type_error_from_APP_try_to_program_a_PD69220_firmware_into_PD69210_device,
    eBoot_error_sys_type_error_from_APP_try_to_program_a_PD69210_firmware_into_PD69220_device,
}Telemetry_at_Boot_Up_Error_e;


typedef struct  {
    meba_poe_global_cfg_t global;
    meba_poe_port_cfg_t*  ports;
} poe_private_cfg_data_t;


typedef struct  {
    mesa_poe_milliwatt_t        requested_power_single_mw;
    mesa_poe_milliwatt_t        requested_power_mode_a_mw;
    mesa_poe_milliwatt_t        requested_power_mode_b_mw;
} meba_poe_port_private_status_t;


typedef struct {
    meba_poe_status_t               global;
    meba_poe_port_private_status_t* ports;
} poe_private_status_data_t;


typedef struct  {
    poe_private_status_data_t   status;
    poe_private_cfg_data_t      cfg;
    poe_private_cfg_data_t      cfg_POEMCU;
    meba_debug_t                debug;             // Board debug output
    const char                  *builtin_firmware; // Path to file with builtin firmware
    mesa_bool_t                 is_bt;             // poe mode user config
    meba_poe_parameters_t       tPoE_parameters;

    uint8_t                     buf_rx[PD_BUFFER_SIZE];
    mesa_bool_t                 IsBootError;
    Telemetry_at_Boot_Up_Error_e eTelemetry_at_Boot_Up_Error;
} poe_driver_private_t;


typedef struct   // parameters taken from DB according to PN read from POEMCU serial number
{
    int         poe_port_mode_max_power_index;  // class index 0 - 8
    uint8_t     poe_class_max_pwr;              // default class 6
    uint8_t     class_error_selection[2];       // 0=Legacy , 1=BT
    uint32_t    port_max_pwr_per_type_mW;       // Max single POE port power in mWatt
    uint8_t     port_type_operation_mode[MAX_POE_TYPES][4];  // columne0: pse_type and 0=Legacy,1=BT  columne1: 0-BT ,1-legacy org ,2-poh ,3-Ignore-PD-Class
}Prod;


static const uint16_t ClassMode_MaxPower_W[]     = { 15 , 30 , 60 , 90 };                  // System has 4 modes = 15/30/60/90
static uint8_t        MAX_ADDED_CLASS_POWER_dW   = 0;   //25;   // Extra power per class in DeciWatt (25=2.5W)
//static const uint8_t  PowerPerClass_W[]        = { 0, 4 , 7,  15, 30, 45, 60, 75, 90 };  // Max PoE power per Class

int POE_MAX_LOGICAL_PORTS      =       48;
Prod prod;


/*********************
   Local Functions
**********************/


/*---------------------------------------------------------------------
 *    description: read legal 15 bytes prtocol message from PoE device buffer. includes sunc mechnism and message checksum test.
 *    			   in case of message system status telemetry with echo 255 - it checks for any firmware damage.
 *    			   if no legal 15bytes command found - buffer with be empty at the end of function.
 *
 *    input :   bI2C_Address                 - device I2C address
 *              U8 byEcho                    - messgae Echo
 *    output:   byArrRxBuffer[]              - pointer to recieve data byte array
 *              *pePOE_BOOL_Is_system_status - parameter to inform calling function if special system status (with echo 255) message was detected.
 *    return:   MESA_RC_OK                   - operation succeed
 *              MESA_RC_ERR_POE_RX_BUF_EMPTY - rx buffer empty
 *              MESA_RC_ERROR                - i2c device error
 *              MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED - poe firmware update needed
 *---------------------------------------------------------------------*/
mesa_rc Get_15Bytes_CommProtocol_Reply(const meba_poe_ctrl_inst_t* const inst,
                   uint8_t* data,
                   uint8_t byTxEcho,
                   mesa_bool_t *pePOE_BOOL_Is_system_status,
                   Telemetry_at_Boot_Up_Error_e *peTelemetry_at_Boot_Up_Error);



/*---------------------------------------------------------------------
 *    return:   MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED - firmware update needed
 *              MESA_RC_ERROR                - i2c device error
 *              MESA_RC_OK                   - operation succeed
 *---------------------------------------------------------------------*/
//mesa_rc (*functionPtr_rd_system_status_ok)        (const meba_poe_ctrl_inst_t*, mesa_bool_t*, Telemetry_at_Boot_Up_Error_e*);
//mesa_rc (*functionPtr_rd_system_status_analyze_ok)(const meba_poe_ctrl_inst_t*, uint8_t*    ,Telemetry_at_Boot_Up_Error_e*);




static char* print_as_hex_string(uint8_t* in, int in_size, char* out, int out_size)
{
    int i, s, size_old = out_size;
    char *tmp = out;

    for (i = 0; i < in_size; ++i) {
        s = snprintf(tmp, out_size, "%02hhX ", in[i]);
        tmp += s;
        out_size -= s;

        if (out_size <= 0)
            goto OUT;
    }

OUT:
    out[size_old - 1] = 0;

    return out;
}

int meba_pd69200_i2c_adapter_open(const char* filename, uint8_t i2c_addr)
{
    int file;
    if ((file = open(filename, O_RDWR)) >= 0) {
        if (ioctl(file, I2C_SLAVE, i2c_addr) < 0) {
            printf("cannot specify i2c slave at 0x%02x! [%s]\n", i2c_addr, strerror(errno));
        }
    } else {
        printf("cannot open %s! [%s]\n", filename, strerror(errno));
    }
    return file;
}


// Function for reading data from the MicroSemi micro-controller.
// IN/OUT : Data - Pointer to where to put the read data
// IN     : Size - Number of bytes to read.
static
mesa_rc pd69200_rd(const meba_poe_ctrl_inst_t* const inst,
                   uint8_t* data,
                   uint8_t size)
{
    char buf[size * 3 + 1];
    VTSS_MSLEEP(50); // Wait 50ms
    memset(data, 0, size);
    int cnt = read(inst->adapter_fd, data, size);
    DEBUG(inst, MEBA_TRACE_LVL_NOISE, "%s: Read(%d/%d)  %s ",
          inst->adapter_name, size, cnt,
          print_as_hex_string(data, size, buf, sizeof(buf)));
    return (cnt == size) ? MESA_RC_OK : MESA_RC_ERROR;
}



int iFF_byte_count = 0;   // no i2c response
int i00_byte_count = 0;   // poe data buffer empty


void CheckReadingByte(uint8_t data)
{
    if (data == 0)
        i00_byte_count++;
    else
        i00_byte_count = 0;

    if (data == 0xFF)
        iFF_byte_count++;
    else
        iFF_byte_count = 0;
}


// Function for writing data from the MicroSemi micro-controller.
// IN  : Data - Pointer to data to write
//     : Size - Number of bytes to write.
// returns:
//  MESA_RC_OK    - i2c operation succeed
//  MESA_RC_ERROR - failed
static
mesa_rc pd69200_wr(const meba_poe_ctrl_inst_t* const inst,
                   uint8_t* data,
                   char size,
                   char *data_description)
{
    char buf[size * 3 + 1];
    int cnt = write(inst->adapter_fd, data, size);
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: %s Wrote(%d/%d) %s ",
          inst->adapter_name, data_description, size, cnt,
          print_as_hex_string(data, size, buf, sizeof(buf)));

    if(cnt == size) {
        return MESA_RC_OK;
    } else {
        poe_driver_private_t *private_data = (poe_driver_private_t *)(inst->private_data);

        private_data->status.global.i2c_tx_error_counter++;

        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s: %s Wrote(%d/%d. TxErrCnt=%lu) %s ",
              inst->adapter_name, data_description, size, cnt, private_data->status.global.i2c_tx_error_counter,
              print_as_hex_string(data, size, buf, sizeof(buf)));

        return MESA_RC_ERROR;
    }
}



// Function for reading data from the MicroSemi micro-controller.
// IN/OUT : Data - Pointer to where to put the read data
// IN     : Size - Number of bytes to read.
mesa_rc pd69200_firm_update_rd(const meba_poe_ctrl_inst_t* const inst, uint8_t* data, char size)
{
    mesa_rc rc = MESA_RC_OK;
    int loop_number = 0;
    do {
        rc = read(inst->adapter_fd, data, 1);

        if (rc == MESA_RC_ERROR) {
            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "read error: %d", rc);
            return rc;
        }

        if (data[0] == 0) {
            VTSS_MSLEEP(5);
            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "read again:%d", loop_number);
        }
        loop_number++;
    }
    while ((data[0] == 0) && (loop_number < 40));

    if (data[0] == 0)
        return rc;

    rc = read(inst->adapter_fd, &(data[1]), size - 1);

    if (rc == MESA_RC_ERROR) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "error2:%d", rc);
    }

    return rc;
}


static
void meba_poe_pd69200_set_chipset(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_chip_state_t       chip_state)
{
    meba_poe_status_t* current_status =
            &(((poe_driver_private_t*)(inst->private_data))->status.global);

    current_status->chip_state = chip_state;
}

static
meba_poe_chip_state_t meba_poe_pd69200_get_chipset(
    const meba_poe_ctrl_inst_t* const inst) {
    if (inst == NULL || inst->private_data == NULL) {
        return MEBA_POE_NO_CHIPSET_FOUND;
    }

    meba_poe_status_t* current_status =
            &(((poe_driver_private_t*)(inst->private_data))->status.global);

    return current_status->chip_state;
}

// Something went wrong, we should do synchronization. We do not do as described in section 7 in the userguide. Instead
// microSemi has suggested that we simply wait more than 10 sec. After 10 sec. the I2C buffer is flushed, and we do not have
// to do a reset of the PoE chip, which microSemi didn't like. We only do the wait once.
// The above suggestion from microsemi didn't work, so the workaround below is used instead.
static mesa_rc meba_poe_pd69200_sync(const meba_poe_ctrl_inst_t* const inst)
{
    uint8_t buf[PD_BUFFER_SIZE];
    uint8_t timeout;
    char charbuf[PD_BUFFER_SIZE * 4];

    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Driver instance %s not found", inst->adapter_name);
        return MESA_RC_OK;
    }
    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Syncing driver instance: %s", inst->adapter_name);

    VTSS_MSLEEP(10000); // Wait at least 10 sec in order to reset i2c system. See Section 8.2 MASK Registers list in "PD69200 Serial Communication Protocol User Guide"

    // Do dummy reads to insure that the i2c is in fact empty now.
    for (timeout = PD_BUFFER_SIZE * 4; timeout > 0; timeout--) {
        if (pd69200_rd(inst, buf, PD_BUFFER_SIZE) == MESA_RC_OK) {
            uint8_t zero_buf[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            if (memcmp(zero_buf, buf, PD_BUFFER_SIZE) == 0) {
                // Empty I2C buffer in controller, just continue
                return MESA_RC_OK;
            }
        }
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
              "No sync found: %s", print_as_hex_string(buf, PD_BUFFER_SIZE, charbuf, sizeof(charbuf)));
        VTSS_MSLEEP(1000);
    }
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
          "Did not find and Report or Telemetry Key");
    return MESA_RC_ERROR;
}

// The sequence number is also named ECHO in the user guide. Two consecutive
// messages must not contain the same sequunce number. See section 4.1 - ECHO
// in the user guide.
// In : reset_seq_num - Set to TRUE in order to reset the sequence number to 0.
static char get_seq_num(mesa_bool_t reset_seq_num)
{
    static uint8_t seq_num = 0;

    if (reset_seq_num) {
        seq_num = 0;
    }
    else if (seq_num >= (SEQ_NUM_DO_NOT_CHK-1)) {
        seq_num = 0;
    } else {
        seq_num++;
    }

    return seq_num;
}

// Updates the check sum for the command. See section 4.1-CHECKSUM in the user guide
// In : buf - pointer to the I2C data
static void pd69200_update_check_sum(uint8_t* buf)
{
    int buf_index = 0;
    unsigned int sum = 0;

    // Find the check for the data (skip the last 2 bytes - They are the check sum bytes going to be replaced.
    for (buf_index = 0; buf_index < PD_BUFFER_SIZE - 2; buf_index++) {
        sum += buf[buf_index]; // Sum up the checksum
    }

    // Convert from integer to 2 bytes.
    buf[13] = (sum >> 8) & 0xFF;
    buf[14] = sum & 0xFF;
}

// Do the real I2C transmitting. Returns FALSE is the trasmit went wrong.
static mesa_bool_t is_tx_ok(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t* buf,
    char *data_description)
{
    buf[1] = get_seq_num(false);

    // Update the checksum
    pd69200_update_check_sum(buf);

    return MESA_RC_OK == pd69200_wr(inst, buf, PD_BUFFER_SIZE, data_description);
}

// Check if the check sum is correct. See Section 4.1 - CHECKSUM in the user guide
// In : buf - pointer to the I2C data
static mesa_bool_t pd69200_check_sum_ok(uint8_t* buf)
{
    int buf_index = 0;
    unsigned int sum = 0;

    // -2 because the Sum bytes shall not be part of the checksum
    for (buf_index = 0; buf_index < PD_BUFFER_SIZE - 2; buf_index++) {
        sum += buf[buf_index]; // Sum up the checksum
    }


    // Do the check of the checksum
    if ((buf[13] != (sum >> 8 & 0xFF)) && (buf[14] != (sum & 0xFF))) {
        return false;
    } else {
        return true;
    }
}

// Report key - See section 4.6 in the user guide
// expected_seq_num - The expected sequence number for the report
// returnes:
//   true    - checksum and report OK
//   false   - checksum or report ERROR
static mesa_bool_t report_key_ok(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t expected_seq_num,
    uint8_t *buf)
{
    mesa_bool_t report_key_ok_v = true;

    // First make sure that the checksum is correct
    if (pd69200_check_sum_ok(&buf[0])) {
        uint16_t buf2_3 = (buf[2]<<8) + buf[3];

        if (buf[0] != REPORT_KEY) {
            report_key_ok_v = false;
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, report key value error \n", __FUNCTION__);
        } else if (buf[2] == 0x00 && buf[3] == 0x00) {
            report_key_ok_v = true;
            //DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Command received/correctly executed \n", __FUNCTION__);
        } else if  (buf[2] == 0xFF && buf[3] == 0xFF && buf[4] == 0xFF && buf[5] == 0xFF) {
            report_key_ok_v = false;
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Command Received/Wrong Checksum \n", __FUNCTION__);
        } else if  (buf2_3 >= 0x1  && buf2_3 <= 0x7FFF) {
            report_key_ok_v = false;
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Failed Execution/Conflict in Subject Bytes \n", __FUNCTION__);
            //S_I("PoE-Control: poe software module use unsupported communication message");
        } else if  (buf2_3 >= 0x8001 && buf2_3 <= 0x8FFF) {
            report_key_ok_v = false;
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Failed Execution/Wrong Data Byte Value \n", __FUNCTION__);
        } else if  (buf[2] == 0xFF  && buf[3] == 0xFF) {
            report_key_ok_v = false;
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Failed Execution/Undefined Key Value \n", __FUNCTION__);
        } else {
            report_key_ok_v = false;
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Undefined reply code Key Value \n", __FUNCTION__);
        }
    } else {
        report_key_ok_v = false;
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Rx packet checksum error \n", __FUNCTION__);
    }

    return report_key_ok_v;
}


// Function that reads controller response ( reponds upon request ), and check the key and checksum.
// Returns:
//   MESA_RC_OK                    - rx message OK
//   MESA_RC_ERR_POE_COMM_PROT_ERR - checksum or KEY error
static mesa_rc get_controller_request_response(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t* buf_rx,
    uint8_t* buf_tx)
{
    // Check checksum
    if (!pd69200_check_sum_ok(buf_rx)) {
        char dbg_txt[PD_BUFFER_SIZE * 4];
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Invalid checksum: %s\n",  __FUNCTION__,
              print_as_hex_string(buf_rx, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));
        return MESA_RC_ERR_POE_COMM_PROT_ERR;
    }

    if  (buf_rx[0] != TELEMETRY_KEY) {
        char dbg_txt[PD_BUFFER_SIZE * 4];
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Invalid key (%d), TX: %s ,Rx: %s\n",
              __FUNCTION__, buf_rx[0], print_as_hex_string(buf_tx, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)), print_as_hex_string(buf_rx, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));
        return MESA_RC_ERR_POE_COMM_PROT_ERR;
    }

    return MESA_RC_OK;
}




/*---------------------------------------------------------------------
 *    description: Transmit the command - and read telemetr/reply (byte after byte...)
 *    			  if no legal 15bytes command found - buffer with be empty at the end of function.
 *
 *    input :   bI2C_Address                 - device I2C address
 *              U8 byEcho                    - messgae Echo
 *    output:   byArrRxBuffer[]              - pointer to recieve data byte array
 *              *pePOE_BOOL_Is_system_status - parameter to inform calling function if special system status (with echo 255) message was detected.
 *    return:   MESA_RC_OK                   - operation succeed
 *              MESA_RC_ERR_POE_RX_BUF_EMPTY - rx buffer empty
 *              MESA_RC_ERROR                - i2c device error
 *              MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED - poe firmware update needed
 *              MESA_RC_ERR_POE_COMM_PROT_ERR - communication protocol error (checksum or key)
 *---------------------------------------------------------------------*/
static mesa_rc pd69200_tx(
    const meba_poe_ctrl_inst_t* const inst,
    const char* file,
    int line,
    uint8_t* buf,
    char *data_description)
{
    uint8_t buf_tx[PD_BUFFER_SIZE];
    memcpy(buf_tx, buf, PD_BUFFER_SIZE);

    mesa_rc rc = MESA_RC_ERROR;

    // write i2c data
    if (!is_tx_ok(inst, buf_tx, data_description)) {
        uint8_t      bRxMsg[PD_BUFFER_SIZE];
        /* Read the 15 to clear i2x rx buffer */
        MESA_RC(pd69200_rd(inst, bRxMsg, PD_BUFFER_SIZE));

        return MESA_RC_ERROR;
    }

    if (strcmp(data_description, "RESTORE_FACTORY_DEFAULT") == 0) {
        VTSS_MSLEEP(150); // Wait 100ms (4.1.2 note 1)
    }

    mesa_bool_t                     ePOE_BOOL_Is_system_status = false;
    Telemetry_at_Boot_Up_Error_e    eTelemetry_at_Boot_Up_Error = eBoot_Unknown_error;

    rc = Get_15Bytes_CommProtocol_Reply(inst,
                   buf,
                   buf_tx[1],
                   &ePOE_BOOL_Is_system_status,
                   &eTelemetry_at_Boot_Up_Error);

    // Do the I2C transmission and check report key.
    if (rc ==  MESA_RC_OK) {
        // Section 4.6 in PD69200/G user guide - check report in case of command or program
        if ((buf_tx[0] == COMMAND_KEY || buf_tx[0] == PROGRAM_KEY)) {
            if (report_key_ok(inst, buf_tx[1], buf)) {
                rc = MESA_RC_OK;
            } else {
                DEBUG(inst, MEBA_TRACE_LVL_WARNING, "%s called from %s(%d) failed\n",  __FUNCTION__, file, line);
            }
        }
        else if (buf_tx[0] == REQUEST_KEY) {
            rc = get_controller_request_response(inst, buf, buf_tx);
        } else {
            rc = MESA_RC_OK;
        }
    } else {
        char dbg_txt[sizeof(buf_tx) * 4];
        DEBUG(inst, MEBA_TRACE_LVL_WARNING,
              "%s called from %s(%d), Invalid response: %s\n",  __FUNCTION__, file, line,
              print_as_hex_string(buf, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));
    }

    return rc;
}


// Get serial number
mesa_rc pd69200bt_get_serial_number(const meba_poe_ctrl_inst_t* const inst,
                                    meba_poe_serial_number_t *ptSN )
{
    // Send request to get serial number
    unsigned char buf[PD_BUFFER_SIZE] = { REQUEST_KEY,
                                          DUMMY_SEQ_NUM,
                                          GLBL_KEY,
                                          PRDCTINFO_KEY,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE,
                                          DUMMY_BYTE
    };

    // T_DG(VTSS_TRACE_POEBT_GRP_CUSTOM, "pd69200bt_get_serial_number");
    char *fname = "GET SERIAL NUMBER";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    ptSN->NumOfCh_HC08_Sprt   = buf[2];
    ptSN->SubContractor       = buf[3];
    ptSN->Year                = buf[4];
    ptSN->Week                = buf[5];
    ptSN->PN                  = ((uint16_t)buf[6] << 8) | (uint16_t)buf[7];
    ptSN->UN                  = ((uint32_t)buf[8] << 16) | ((uint32_t)buf[9] << 8) | (uint32_t)buf[10];

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,Year=%d ,Week=%d ,PN=%d ,UN=%d",
         fname,
         ptSN->NumOfCh_HC08_Sprt,
         ptSN->Year,
         ptSN->Week,
         ptSN->PN,
         ptSN->UN);

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200_individual_mask_get(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t   mask_key_number,
    uint8_t*  indv_mask_value,
    char* indv_desc)
{
    // Send request to get status
    unsigned char buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        INDIV_MASK_KEY,
        mask_key_number,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET INDIVIDUAL MASK";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));
    *indv_mask_value = buf[2];

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] %s ,mask_key_number=%d ,indv_mask_value=%d",
          fname,
          indv_desc,
          mask_key_number,
         *indv_mask_value);

    return MESA_RC_OK;
}




static
mesa_rc meba_poe_pd69200_individual_mask_set(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t mask,
    uint8_t val)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        INDIV_MASK_KEY,
        mask,
        val,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "SET INDIVIDUAL MASK";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname))

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] mask=%d ,val=%d",
          fname,
          mask,
          val);

    return MESA_RC_OK;
}

#ifdef SYNC_MISC_POE_PARAMS
static mesa_rc meba_poe_pd69200_get_pm_method(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t *pm1,
    uint8_t *pm2,
    uint8_t *pm3)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SUPPLY_KEY,
        POWER_MANAGE_MODE_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET PM METHOD";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *pm1 = buf[2];
    *pm2 = buf[3];
    *pm3 = buf[4];

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] pm1=%d ,pm2=%d ,pm3=%d",
          fname,
         *pm1,
         *pm2,
         *pm3);

    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_set_pm_method(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t pm1,
    uint8_t pm2,
    uint8_t pm3)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SUPPLY_KEY,
        POWER_MANAGE_MODE_KEY,
        pm1,
        pm2,
        pm3,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "SET PM METHOD";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname))

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] pm1=%d ,pm2=%d ,pm3=%d",
          fname,
          pm1,
          pm2,
          pm3);

    return MESA_RC_OK;
}
#endif // SYNC_MISC_POE_PARAMS

static mesa_rc meba_poe_pd69200_set_power_banks(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t bank,
    uint16_t power_limit_w,
    uint16_t max_shutdown_voltage_dv,
    uint16_t min_shutdown_voltage_dv,
    uint8_t guard_band)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SUPPLY_KEY,
        POWER_BUDGET_KEY,
        bank,
        power_limit_w >> 8 & 0xFF,
        power_limit_w & 0xFF,
        max_shutdown_voltage_dv >> 8 & 0xFF,
        max_shutdown_voltage_dv & 0xFF,
        min_shutdown_voltage_dv >> 8 & 0xFF,
        min_shutdown_voltage_dv & 0xFF,
        guard_band,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "SET POWER BANKS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] bank=%d ,power_limit_w=%lu ,max_shutdown_voltage_dv=%lu ,min_shutdown_voltage_dv=%lu ,guard_band=%d",
          fname,
          bank,
          power_limit_w,
          max_shutdown_voltage_dv,
          min_shutdown_voltage_dv,
          guard_band);

    return MESA_RC_OK;
}

// Section 4.7.7
static mesa_rc pd69200_get_power_supply_parameters(
    const meba_poe_ctrl_inst_t* const inst,
    uint16_t* power_consumption_w,
    uint16_t* max_shutdown_voltage_dv,
    uint16_t* min_shutdown_voltage_dv,
    uint8_t*  guard_band,
    uint8_t*  bank,
    uint16_t* power_limit_w)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SUPPLY_KEY,
        MAIN_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET POWER SUPPLY PARAMETERS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *power_consumption_w     = (buf[2] << 8) + buf[3];
    *max_shutdown_voltage_dv = (buf[4] << 8) + buf[5];
    *min_shutdown_voltage_dv = (buf[6] << 8) + buf[7];
    *guard_band              = buf[8];
    *bank                    = buf[9];
    *power_limit_w           = (buf[10] << 8) + buf[11];

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] pwr_consumption=%lu[w] ,max_shutdown_voltage_dv=%lu ,min_shutdown_voltage_dv=%lu ,guard_band=%d ,bank=%d ,power_limit_w=%lu",
          fname,
         *power_consumption_w,
         *max_shutdown_voltage_dv,
         *min_shutdown_voltage_dv,
         *guard_band,
         *bank,
         *power_limit_w);
    return MESA_RC_OK;
}



static mesa_rc meba_poe_pd69200_ctrl_get_port_power_limit(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                      channel,
    uint16_t* ppl,
    uint16_t* tppl)
{
    // Transmit the command

    uint8_t  buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        SUPPLY_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET PORT POWER LIMIT";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *ppl = (buf[2] << 8) + buf[3];
    *tppl  = (buf[4] << 8) + buf[5];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "[%s] CH=%d ,ppl=%lu ,tppl=%lu",
          fname,
          channel,
         *ppl,
         *tppl);

    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_ctrl_set_enable_disable_channels(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                      channel,
    uint8_t                      cmd,
    uint8_t                      port_type)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        ENABLE_DISABLE_KEY,
        channel,
        cmd,
        port_type,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "SET ENABLE DISABLE CHANNELS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,cmd=%d ,port_type=%d",
          fname,
          channel,
          cmd,
          port_type);

    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_ctrl_set_port_priority(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                      channel,
    uint8_t                      priority)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        PRIORITY_KEY,
        channel,
        priority,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "SET PORT PRIORITY";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,priority=%d",
          fname,
          channel,
          priority);

    return MESA_RC_OK;
}


/*

static
mesa_rc meba_poe_pd69200_ctrl_set_bt_port_layer2_lldp_pd_request(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      channel,
    uint16_t                    pd_request_power_single,  // deciwatt
    uint16_t                    pd_request_power_dual_a,  // deciwatt
    uint16_t                    pd_request_power_dual_b,  // deciwatt
    uint8_t                     cable_len_plus_req_autoclass,
    uint8_t                     l2_cfg)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        LAYER2_BT_LLDP_PD_KEY,
        channel,
        (uint8_t)((pd_request_power_single >> 8) & 0xFF),
        (uint8_t)(pd_request_power_single & 0xFF),
        (uint8_t)((pd_request_power_dual_a >> 8) & 0xFF),
        (uint8_t)(pd_request_power_dual_a & 0xFF),
        (uint8_t)((pd_request_power_dual_b >> 8) & 0xFF),
        (uint8_t)(pd_request_power_dual_b & 0xFF),
        cable_len_plus_req_autoclass,
        l2_cfg,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));
    return MESA_RC_OK;
}




static
mesa_rc meba_poe_pd69200_ctrl_get_bt_port_layer2_lldp_pse_data(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      channel,
    uint16_t* pse_allocated_power_alt_A,
    uint16_t* pse_allocated_power_alt_B,
    uint16_t* pse_max_power,
    uint8_t* assigned_class,
    uint8_t* layer2_status,
    uint8_t* ieee_bt_power_bits,
    uint8_t* cable_len,
    uint8_t* l2_cfg)
{
    // Transmit the command

    uint8_t  buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        LAYER2_BT_LLDP_PSE_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *pse_allocated_power_alt_A  = (buf[2] << 8) + buf[3];
    *pse_allocated_power_alt_B  = (buf[4] << 8) + buf[5];
    *pse_max_power              = (buf[6] << 8) + buf[7];
    *assigned_class             =  buf[8];
    *layer2_status              =  buf[9];
    *ieee_bt_power_bits         =  buf[10];
    *cable_len                  =  buf[11];
    *l2_cfg                     =  buf[12];

    return MESA_RC_OK;
}

*/



static
mesa_rc meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      channel,
    uint8_t                     layer2_pd_type,
    uint16_t                    requested_power_dw,
    uint16_t                    allocated_power_dw,
    uint8_t                     cable_len,
    uint8_t                     execute_lldp)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        LAYER2_LLDP_PD_KEY,
        channel,
        layer2_pd_type,
        (uint8_t)((requested_power_dw >> 8) & 0xFF),
        (uint8_t)(requested_power_dw & 0xFF),
        (uint8_t)((allocated_power_dw >> 8) & 0xFF),
        (uint8_t)(allocated_power_dw & 0xFF),
        cable_len,
        execute_lldp,
        DUMMY_BYTE
    };

    char *fname = "SET PORT LAYER2 LLDP PD DATA";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,layer2_pd_type=%d ,requested_power_dw=%lu ,allocated_power_dw=%lu ,cable_len=%d ,execute_lldp=%d",
          fname,
          channel,
          layer2_pd_type,
          requested_power_dw,
          allocated_power_dw,
          cable_len,
          execute_lldp);

    return MESA_RC_OK;
}


// Get Port Layer2 LLDP PSE Data
static mesa_rc meba_poe_pd69200_ctrl_get_port_layer2_lldp_pse_data(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      channel,
    uint16_t* pse_allocated_power_dw,
    uint16_t* pd_requested_power_dw,
    uint8_t* pse_power_type,
    uint8_t* power_class,
    uint8_t* pse_power_pair,
    uint8_t* mdi_power_status,
    uint8_t* cable_len,
    uint8_t  *power_reserve_mode_active,
    uint8_t  *layer2_request_pending,
    uint8_t  *port_delivering_power_type,
    uint16_t *port_power_consumption
    )
{
    // Transmit the command

    uint8_t  buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        LLDP_PSE_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET PORT LAYER2 LLDP PSE DATA";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *pse_allocated_power_dw = (buf[2] << 8) + buf[3];
    *pd_requested_power_dw  = (buf[4] << 8) + buf[5];
    *pse_power_type      =  buf[6];
    *power_class         =  buf[7];
    *pse_power_pair      =  buf[8];
    *mdi_power_status    =  buf[9];
    *cable_len           =  buf[10];
    uint16_t power_indicator =  (buf[11] << 8) + buf[12];

    *power_reserve_mode_active  = (power_indicator >> 15) & 1; //Bit 15 - Power reserve mode active
    *layer2_request_pending     = (power_indicator >> 14) & 1; //Bit 14 - Layer2 request Pending
    *port_delivering_power_type = (power_indicator >> 12) & 3; //Bit 15 - port delivering power type
    *port_power_consumption     =  power_indicator & 0xFFF   ; // Port Power Consumption

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
          "[%s] CH=%d ,pse allocated pwr=%u ,pd requested pwr=%u ,pse pwr type=%d ,pwr class=%d ,pse pwr pair=%d ,mdi pwr status=%d ,cable len=%d ,pwr reserve=%d ,l2 req pend=%d ,del pwr type=%d ,pwr cons=%u",
          fname,
          channel,
         *pse_allocated_power_dw,
         *pd_requested_power_dw,
         *pse_power_type,
         *power_class,
         *pse_power_pair,
         *mdi_power_status,
         *cable_len,
         *power_reserve_mode_active,
         *layer2_request_pending,
         *port_delivering_power_type,
         *port_power_consumption
         );

    return MESA_RC_OK;
}




static
mesa_rc meba_poe_pd69200_ctrl_get_single_port_status(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                     channel,
    uint8_t* enable,
    uint8_t* port_status,
    uint8_t* force_power_enable,
    uint8_t* latch,
    uint8_t* class,
    uint8_t* af_at_poh,
    uint8_t* four_pair_enable)
{
    uint8_t  buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        PORT_STATUS_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET SINGLE PORT STATUS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *enable             = buf[2];
    *port_status        = buf[3];
    *force_power_enable = buf[4];
    *latch              = buf[5];
    *class              = buf[6];
    *af_at_poh          = buf[10];
    *four_pair_enable   = buf[11];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
          "[%s] CH=%d ,enable=%d ,port status=%d ,force pwr enable=%d ,latch=%d ,class=%d ,af_at_poh=%d ,4pair enable=%d",
          fname,
          channel,
         *enable,
         *port_status,
         *force_power_enable,
         *latch,
         *class,
         *af_at_poh,
         *four_pair_enable);

    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_power_supply_measurements_get(
    const meba_poe_ctrl_inst_t* const inst,
    uint16_t* vmain_voltage_dv,
    uint16_t* imain_current_ma)
{

    // Send request to get status
    unsigned char buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SUPPLY_KEY,
        MEASUREMENTS_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET TOTAL PWR";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *vmain_voltage_dv    = (buf[2] << 8) + buf[3];
    *imain_current_ma    = (buf[7] << 8) + buf[8];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
         "[%s] vmain_voltage_dv=%lu ,imain_current_ma=%lu [W]",
          fname,
         *vmain_voltage_dv,
         *imain_current_ma);

    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_total_power_get(
    const meba_poe_ctrl_inst_t* const inst,
    mesa_bool_t is_bt_command,
    uint16_t* power_consumption_w,
    uint16_t* calculated_power_w,
    uint16_t* available_power_w,
    uint16_t* power_limit_w,
    uint8_t*  power_bank,
    uint16_t* vmain_voltage_dv)
{

    // Send request to get status
    unsigned char buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SUPPLY_KEY,
        TOTAL_POWER_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET TOTAL PWR";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *power_consumption_w = (buf[2] << 8) + buf[3];
    *calculated_power_w  = (buf[4] << 8) + buf[5];
    *available_power_w   = (buf[6] << 8) + buf[7];
    *power_limit_w       = (buf[8] << 8) + buf[9];
    *power_bank          = buf[10];

    if (is_bt_command)
    {
        *vmain_voltage_dv    = (buf[11] << 8) + buf[12];
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
         "[%s] power_consumption_w=%lu ,calculated_power=%lu [W] ,available_power=%lu [W] ,power_limit_w=%lu ,power_bank=%d ,vmain_voltage=%lu [dV]",
          fname,
         *power_consumption_w,
         *calculated_power_w,
         *available_power_w,
         *power_limit_w,
         *power_bank,
         *vmain_voltage_dv);

    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_port_4Pair_Port_Parameters_get(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                         channel,
    uint8_t* port_type_af_at_poh)
{

    // Send request to get status
    unsigned char buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        PortFullInit4Pair_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET PORT 4PAIR_PORT_PARAMS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *port_type_af_at_poh = buf[6];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
         "[%s] CH=%d ,port_type_af_at_poh=%d",
          fname,
          channel,
         *port_type_af_at_poh);

    return MESA_RC_OK;
}



mesa_rc meba_poe_pd69200_ctrl_port_measurements_get(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                         channel,
    uint16_t* main_voltage,
    uint16_t* calculated_current,
    uint16_t* port_power_consumption,
    uint16_t* port_voltage)
{

    // Send request to get status
    unsigned char buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        PARAMZ_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET PORT MEASUREMENTS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *main_voltage = (buf[2] << 8) + buf[3];
    *calculated_current = (buf[4] << 8) + buf[5];
    *port_power_consumption = (buf[6] << 8) + buf[7];
    *port_voltage = (buf[9] << 8) + buf[10];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
         "[%s] CH=%d ,main voltage=%lu ,calc current=%lu ,port pwr consumption=%lu ,port voltage=%lu",
          fname,
          channel,
         *main_voltage,
         *calculated_current,
         *port_power_consumption,
         *port_voltage);

    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_ctrl_reset_command(
    const meba_poe_ctrl_inst_t* const inst)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        0x55,
        0x00,
        0x55,
        0x00,
        0x55,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "RESET COMMAND";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s]", fname);

    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_ctrl_save_command(
    const meba_poe_ctrl_inst_t* const inst)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        PROGRAM_KEY,
        DUMMY_SEQ_NUM,
        E2_KEY,
        SAVE_CONFIG_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "SAVE COMMAND";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s]", fname);

    return MESA_RC_OK;
}


/*
static
mesa_rc meba_poe_pd69200_ctrl_get_temporary_matrix(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      handle,
    uint8_t* phys_numb_a,
    uint8_t* phys_numb_b)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        TMP_MATRIX_KEY,
        handle,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *phys_numb_a = buf[2];
    *phys_numb_b = buf[3];

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[GET TEMPORARY MATRIX] CH=%d ,phys numb a=%d ,phys_numb_b=%d",
       handle,
       *phys_numb_a,
       *phys_numb_b);


    return MESA_RC_OK;
}
*/


static
mesa_rc meba_poe_pd69200_ctrl_get_active_matrix(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      handle,
    uint8_t* phys_numb_a,
    uint8_t* phys_numb_b)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        CHANNEL_MATRIX_KEY,
        handle,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET ACTIVE MATRIX";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *phys_numb_a = buf[2];
    *phys_numb_b = buf[3];

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,phys numb_a=%d ,phys numb_b=%d",
          fname,
          handle,
         *phys_numb_a,
         *phys_numb_b);

    return MESA_RC_OK;
}

static
mesa_rc meba_poe_pd69200_ctrl_set_temporary_matrix(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      handle,
    uint8_t                     phys_numb_a,
    uint8_t                     phys_numb_b)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        TMP_MATRIX_KEY,
        handle,
        phys_numb_a,
        phys_numb_b,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "SET TEMPORARY MATRIX";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,phys numb_a=%d ,phys numb_b=%d",
          fname,
          handle,
          phys_numb_a,
          phys_numb_b);

    return MESA_RC_OK;
}

// Apply the port mapping
static
mesa_rc pd69200_program_global_matrix(
    const meba_poe_ctrl_inst_t* const inst)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        TMP_MATRIX_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "PROGRAM GLOBAL MATRIX";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s]", fname);

    return MESA_RC_OK;
}




/*---------------------------------------------------------------------
 *    description: analyze system status info.
 *
 *    input :   uint8_t *buf
 *    output:
 *    return:   MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED     - poe firmware update needed
 *              MESA_RC_ERROR                - i2c device error
 *              MESA_RC_OK                   - operation succeed
 *---------------------------------------------------------------------*/
mesa_rc check_for_poe_firmware_errors(const meba_poe_ctrl_inst_t* const inst,
                                              uint8_t *buf,
                                              Telemetry_at_Boot_Up_Error_e *peTelemetry_at_Boot_Up_Error)
{
	char boot_up_error_1         = buf[2];
	//char cpu_status2_error_codes = buf[3];
	//char factory_default         = buf[4];
	char boot_up_error_2         = buf[5];
	//char ram_private_label       = buf[6];
	//char nvm_private_label       = buf[7];
	//char found_devices           = buf[8];
	//char event_exist             = buf[12];

	if(peTelemetry_at_Boot_Up_Error)
        *peTelemetry_at_Boot_Up_Error = eBoot_Unknown_error;

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: [0]=0x%X ,[1]=0x%X ,[2]=0x%X ,[3]=0x%X ,[4]=0x%X ,[5]=0x%X ,[6]=0x%X ,[7]=0x%X ,[8]=0x%X ,[9]=0x%X ,[10]=0x%X ,[11]=0x%X ,[12]=0x%X",
          __FUNCTION__ ,buf[0] ,buf[1] ,buf[2] ,buf[3] ,buf[4] ,buf[5] ,buf[6] ,buf[7] ,buf[8] ,buf[9] ,buf[10] ,buf[11] ,buf[12]);

	// Telemetry at Boot Up Error
	if ((boot_up_error_1 != 0) || (boot_up_error_2 != 0))
	{
		char err_code       = buf[5];
		char err_info1      = buf[6];
		char err_info2      = buf[7];
		char download_type  = buf[8];

		if ((err_code == 0x4E) && (err_info1 == 0x4E) && (err_info2 == 0x4E) && (download_type == 0x4E))
		{
			if(peTelemetry_at_Boot_Up_Error) *peTelemetry_at_Boot_Up_Error = eBoot_error_Application_CRC_error_Download_is_required_for_PD69200;
			DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: Application CRC error Download is required for PD69200", __FUNCTION__);
		}
		else if ((err_code == 0x4E) && (err_info1 == 0x4E) && (err_info2 == 0x4E) && (download_type == 0x33))
		{
			if(peTelemetry_at_Boot_Up_Error) *peTelemetry_at_Boot_Up_Error = eBoot_error_Application_CRC_error_Download_is_required_for_PD69210_PD69220;
			DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: Application CRC error Download is required for PD69210_PD69220", __FUNCTION__);
		}
		else if ((err_code == 0x02) && (err_info1 == 0x33) && (err_info2 == 0x2C) && (download_type == 0x33))
		{
			if(peTelemetry_at_Boot_Up_Error) *peTelemetry_at_Boot_Up_Error = eBoot_error_hw_error_from_Boot_try_to_program_a_PD69200_firmware_into_PD69210_PD69220_device;
			DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: HW error from Boot Try to program a PD69200 firmware into PD69210_PD69220 device", __FUNCTION__);
		}
		else if ((err_code == 0x02) && (err_info1 == 0x2C) && (err_info2 == 0x33) && (download_type == 0x4E))
		{
			if(peTelemetry_at_Boot_Up_Error) *peTelemetry_at_Boot_Up_Error = eBoot_error_hW_error_from_Boot_try_to_program_a_PD69210_PD69220_firmware_into_PD69200_device;
			DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: HW error from Boot Try to program a PD69210_PD69220 firmware into PD69200 device", __FUNCTION__);
		}
		else if ((err_code == 0x03) && (err_info1 == 0x40) && (err_info2 == 0x41) && (download_type == 0x4E))
		{
			if(peTelemetry_at_Boot_Up_Error) *peTelemetry_at_Boot_Up_Error = eBoot_error_sys_type_error_from_APP_try_to_program_a_PD69220_firmware_into_PD69210_device;
			DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: Sys Type error from APP Try to program a PD69220 firmware into PD69210 device", __FUNCTION__);
		}
		else if ((err_code == 0x03) && (err_info1 == 0x41) && (err_info2 == 0x40) && (download_type == 0x4E))
		{
			if(peTelemetry_at_Boot_Up_Error) *peTelemetry_at_Boot_Up_Error = eBoot_error_sys_type_error_from_APP_try_to_program_a_PD69210_firmware_into_PD69220_device;
			DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: Sys Type error from APP Try to program a PD69210 firmware into PD69220 device", __FUNCTION__);
		}
        else
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: unknown boot error", __FUNCTION__);
            return MESA_RC_ERROR;
        }

		DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: boot up error", __FUNCTION__);
		return MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: Telemetry at Boot Up OK", __FUNCTION__);

//  if ((cpu_status2_error_codes != 0)) {
//	DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: cpu error=%d", __FUNCTION__, cpu_status2_error_codes);
//	return MESA_RC_ERROR;
//  }

    // if we are here we have valid message

	return MESA_RC_OK;
}






/*---------------------------------------------------------------------
 *    description: read legal 15 bytes prtocol message from PoE device buffer. includes sunc mechnism and message checksum test.
 *    			   in case of message system status telemetry with echo 255 - it checks for any firmware damage.
 *    			   if no legal 15bytes command found - buffer with be empty at the end of function.
 *
 *    input :   bI2C_Address                 - device I2C address
 *              U8 byEcho                    - messgae Echo
 *    output:   byArrRxBuffer[]              - pointer to recieve data byte array
 *              *pePOE_BOOL_Is_system_status - parameter to inform calling function if special system status (with echo 255) message was detected.
 *    return:   MESA_RC_OK                   - operation succeed
 *              MESA_RC_ERR_POE_RX_BUF_EMPTY - rx buffer empty
 *              MESA_RC_ERROR                - i2c device error
 *              MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED - poe firmware update needed
 *---------------------------------------------------------------------*/
mesa_rc Get_15Bytes_CommProtocol_Reply(const meba_poe_ctrl_inst_t* const inst,
                   uint8_t* rx_data,
                   uint8_t byTxEcho,
                   mesa_bool_t *pePOE_BOOL_Is_system_status,
                   Telemetry_at_Boot_Up_Error_e *peTelemetry_at_Boot_Up_Error)
{
	uint8_t      bRxMsg[PD_BUFFER_SIZE];

    iFF_byte_count = 0;   // no i2c response
    i00_byte_count = 0;   // poe data buffer empty

	memset(rx_data, 0, sizeof(PD_BUFFER_SIZE));

    VTSS_MSLEEP(50); // Wait 50ms

	while ((iFF_byte_count < 30) && (i00_byte_count < 30)) /* 30 bytes with value 0 means that I2C driver has no data to send */
	{
		/* Read the 1 first byte from PoE Device */
        MESA_RC(pd69200_rd(inst, bRxMsg, 1));

        CheckReadingByte(bRxMsg[0]);

	if (bRxMsg[0] == TELEMETRY_KEY || bRxMsg[0] == REPORT_KEY) /* first msg byte - telemetry or response */
	{
            rx_data[0] = bRxMsg[0];  // store telemetry/response

            // Read the second byte (ECHO) from PoE Device
            MESA_RC(pd69200_rd(inst, bRxMsg, 1));

            CheckReadingByte(bRxMsg[0]);

	    /* second msg byte - echo */
	    if ((bRxMsg[0] == byTxEcho) ||     									     	  /* original messsage */
	       ((rx_data[0] == TELEMETRY_KEY) && (bRxMsg[0] == SYSTEM_STATUS_ECHO_KEY)))  /* system status on startup */
	    {
		    rx_data[1] = bRxMsg[0];     /* store echo */

                /* Read the last 13 bytes from PoE Device */
                char size = PD_BUFFER_SIZE - 2;
                MESA_RC(pd69200_rd(inst, bRxMsg, size));

                for (int i=0;i<PD_BUFFER_SIZE - 2;i++)
                    CheckReadingByte(bRxMsg[i]);

                memcpy(rx_data + 2 , bRxMsg , PD_BUFFER_SIZE - 2);

		    // checksum check
		    if (!pd69200_check_sum_ok(rx_data))
		    {
                    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "RX checksum is not valid");
		        continue; //see if we have other valid data bytes in the buffer
		    }

                if (rx_data[1] == 0xFF) // it's a system status telemetry with echo 255 - system status on startup or firmware damage...
		    {
		        if (pePOE_BOOL_Is_system_status)
                            *pePOE_BOOL_Is_system_status = true;

                        return check_for_poe_firmware_errors(inst, rx_data, peTelemetry_at_Boot_Up_Error);
                }

			if (rx_data[1] == byTxEcho) // ECHO ok
			{
					return MESA_RC_OK;
			}
			}
		}
	}

    if(i00_byte_count >= 15)
    {
        // Empty I2C buffer in controller, just continue
        return MESA_RC_ERR_POE_RX_BUF_EMPTY;
    }
    else if (iFF_byte_count >= 15)
    {
        // No I2C response
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Reading all 0xFF", __FUNCTION__);
        return MESA_RC_ERROR;
    }

	return MESA_RC_ERROR;
}


/*---------------------------------------------------------------------
 *
 *    return:   MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED     - poe firmware update needed
 *              MESA_RC_ERROR                - i2c device error
 *              MESA_RC_OK                   - operation succeed
 *---------------------------------------------------------------------*/
static mesa_rc meba_poe_pd69200_ctrl_get_system_status(
    const meba_poe_ctrl_inst_t* const inst,
    uint16_t *pInterrupt_register)
{
    // Send request to get system status
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SYSTEM_STATUS_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    *pInterrupt_register = 0;

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s called line %d\n\r",  __FUNCTION__, __LINE__);

    char *fname = "GET SYSTEM STATUS";
    mesa_rc rc = pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname);
    if(rc != MESA_RC_OK)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "\n\r%s called line %d ,rc=%d\n\r", __FUNCTION__ ,__LINE__ ,rc);
        return rc;
    }

    *pInterrupt_register   = (buf[11] << 8) + buf[12];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "[%s] pInterrupt_register=%d",
          fname,
         *pInterrupt_register);

    return MESA_RC_OK;
}

/*---------------------------------------------------------------------
 *
 *    return:   MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED     - poe firmware update needed
 *              MESA_RC_ERROR                - i2c device error
 *              MESA_RC_OK                   - operation succeed
 *---------------------------------------------------------------------*/
static mesa_rc meba_poe_pd69200_bt_event_cause_get(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t *vmain_fault)
{
    // Send request to get bt event cause
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        BT_EVENT_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    *vmain_fault = 0;

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s called line %d\n\r",  __FUNCTION__, __LINE__);

    char *fname = "GET BT EVENT CAUSE";
    mesa_rc rc = pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname);
    if(rc != MESA_RC_OK)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "\n\r%s called line %d ,rc=%d\n\r", __FUNCTION__ ,__LINE__ ,rc);
        return rc;
    }

    uint8_t system_event   = buf[8];
    *vmain_fault = (system_event >> 1) & 1;

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "[%s] vmain fault=%d",
          fname,
         *vmain_fault);

    return MESA_RC_OK;
}


static
mesa_rc meba_poe_pd69200bt_ctrl_get_bt_system_status(
    const meba_poe_ctrl_inst_t* const inst)
    /*uint8_t* boot_up_error,
    uint8_t* cpu_status2_err_codes,
    uint8_t* fact_def_param_in_use,
    uint8_t* private_label,
    uint8_t* user_byte,
    uint8_t* found_devices,
    uint8_t* active_devices_found,
    uint8_t* event_exist)*/
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        BT_SYSTEM_STATUS_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s called line %d",  __FUNCTION__, __LINE__);
    char *fname = "GET_BT_SYSTEM_STATUS";
    return pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname);
}



static
mesa_rc meba_poe_pd69200_ctrl_get_software_version(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t* hw_version,
    uint8_t* prod_number,
    uint16_t* sw_version,
    uint8_t* param_number,
    uint8_t* build_number,
    uint16_t* internal_sw_version,
    uint16_t* asic_patch_number)
{
    // Send request to get sw version
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        VERSIONZ_KEY,
        SW_VERSION_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    *hw_version = 0;
    *prod_number = 0;
    *sw_version = 0;
    *param_number = 0;
    *build_number = 0;
    *internal_sw_version = 0;
    *asic_patch_number = 0;

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s called line %d",  __FUNCTION__, __LINE__);

    char *fname = "GET SOFTWARE VERSION";
    mesa_rc rc = pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname);
    if(rc != MESA_RC_OK)
    {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "\n\r%s called line %d ,rc=%d", __FUNCTION__ ,__LINE__ ,rc);
        return rc;
    }

    *hw_version          = buf[2];
    *prod_number         = buf[4];
    *sw_version          = (buf[5] << 8) + buf[6];
    *param_number        = buf[7];
    *build_number        = buf[8];
    *internal_sw_version = (buf[9] << 8) + buf[10];
    *asic_patch_number   = (buf[11] << 8) + buf[12];

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] HW ver=%d ,prod#=%d ,SW ver=%lu ,param#=%d ,build#=%d ,internal SW ver=%lu ,asic patch#=%lu",
          fname,
          *hw_version,
          *prod_number,
          *sw_version,
          *param_number,
          *build_number,
          *internal_sw_version,
          *asic_patch_number);

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200_ctrl_restore_factory_default(
    const meba_poe_ctrl_inst_t* const inst)
{
    // "pd69200_restore_factory_default - Section 4.1.2"

    uint8_t buf[PD_BUFFER_SIZE] =  {
        PROGRAM_KEY,
        DUMMY_SEQ_NUM,
        RESTORE_FACT_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "RESTORE_FACTORY_DEFAULT";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s called line %d\n",  __FUNCTION__, __LINE__);

    return MESA_RC_OK;
}

//***************************************************************************************************************
//  Code below is used to update the PoE chipset firmware. It is based upon microSemi TN-140_06-0024-081 document
// **************************************************************************************************************
// Send the enter command as described in sw conf guide section 5.2
static mesa_rc pd69200_sendEnter(const meba_poe_ctrl_inst_t* const inst)
{
    const uint8_t enter[] = { (uint8_t)'E', (uint8_t)'N', (uint8_t)'T', (uint8_t)'R' };

    //T_IG(VTSS_TRACE_GRP_CUSTOM, "Sending ENTR");

    (void)pd69200_wr(inst, (uint8_t*)&enter[0], 1, "E");
    VTSS_MSLEEP(10); // Section 5.2 - Keep at least 10 ms delay between each transmitted character.

    (void)pd69200_wr(inst, (uint8_t*)&enter[1], 1, "N");
    VTSS_MSLEEP(10); // Section 5.2 - Keep at least 10 ms delay between each transmitted character.

    (void)pd69200_wr(inst, (uint8_t*)&enter[2], 1, "T");
    VTSS_MSLEEP(10); // Section 5.2 - Keep at least 10 ms delay between each transmitted character.

    (void)pd69200_wr(inst, (uint8_t*)&enter[3], 1, "R");
    VTSS_MSLEEP(10); // Section 5.2 - Keep at least 10 ms delay between each transmitted character.

    return MESA_RC_OK;
}


static
mesa_rc meba_poe_pd69200_ctrl_get_adc_value(
    const meba_poe_ctrl_inst_t* const inst,
    uint16_t* sensor_reading)
{
    // Send request to get adc value
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SUPPLY_KEY,
        ADC_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    #ifndef POE_READ_ADC_PIN
    *sensor_reading = 0;
    return MESA_RC_OK;
    #endif

    char *fname = "GET_ADC_VALUE";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *sensor_reading = ((buf[2] << 8) + buf[3]) & 0xFFF;
    return MESA_RC_OK;
}



// Checking if PoE firmware is valid (Dor selecting the firmware upgrade process) - Get Software Version telemetry
static mesa_rc pd69200_is_firmware_valid(const meba_poe_ctrl_inst_t  *const inst)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        VERSIONZ_KEY,
        SW_VERSION_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET_SOFTWARE_VERSION";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    return MESA_RC_OK;
}




char* get_port_max_power_string(const meba_poe_ctrl_inst_t* const inst, meba_poe_port_max_power_t ePOE_PORT_MAX_POWER)
{
    switch (ePOE_PORT_MAX_POWER)
    {
        case MEBA_POE_PORT_MAX_POWER_15W:
        {
            return "15W";
        }

        case MEBA_POE_PORT_MAX_POWER_30W:
        {
            return "30W";
        }

        case MEBA_POE_PORT_MAX_POWER_60W:
        {
            return "60W";
        }

        case MEBA_POE_PORT_MAX_POWER_90W:
        {
            return "90W";
        }

    default:
        {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR,"Unable to determine port max power string. ePOE_PORT_MAX_POWER: %d \n", ePOE_PORT_MAX_POWER);
            return "";
        }
    }
}

void meba_poe_io_reset(const meba_poe_ctrl_inst_t* const inst)
{
    poe_driver_private_t *private_data = (poe_driver_private_t *)(inst->private_data);

    // no gpio for reseting poe mcu
    if (private_data->tPoE_parameters.reset_poe_gpio_number == 0xFF)
    {
        sleep(5); // wait 5 seconds and return without GPIO reset
        return;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Reseting PoE MCU - clear poe reset io pin - low state");

    //set poe io (pin_level) to '0' - reset mcu poe
    (void)mesa_gpio_write(NULL, 0, private_data->tPoE_parameters.reset_poe_gpio_number, FALSE);

    sleep(5); // reset poe and wait 5 seconds

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Release PoE MCU from reset - set poe reset io pin - high state");

    //set poe io (pin_level) to '1'  - release poe mcu from reset
    (void)mesa_gpio_write(NULL, 0, private_data->tPoE_parameters.reset_poe_gpio_number, TRUE);
}



// Checking if version of PoE firmware update candidate is identical to the current
// if identical returns true , otherwise returns false
static mesa_bool_t is_firmware_version_identical(const meba_poe_ctrl_inst_t* const inst, const char* microsemi_firmware)
{
    #define MAX_FIRMWARE_HEADER_LEN 300

    uint8_t    hw_version = 0;
    uint8_t    prod_number = 0;
    uint16_t   sw_version = 0;
    uint8_t    param_number = 0;
    uint8_t    build_number = 0;
    uint16_t   internal_sw_version = 0;
    uint16_t   asic_patch_number = 0;

    const char* swNum = "Software Number:";
    const char* param = "Param Number:";
    char* swNum_ptr, *param_ptr;
    uint8_t  prod_number_from_file = 0;
    uint16_t sw_ver_from_file = 0;
    uint8_t  param_from_file = 0;
    size_t   mapped_memory_size = 0;
    char* mapped_memory = NULL;
    mesa_rc rc = MESA_RC_OK;

    poe_driver_private_t *private_data = (poe_driver_private_t *)(inst->private_data);

    meba_poe_controller_type_t ePoE_detected_controller_type =  MEBA_POE_PD692X0_CONTROLLER_TYPE_AUTO_DETECTION;

    int fd = -1;

    private_data->status.global.prod_number_detected = 0;
    private_data->status.global.sw_version_detected = 0;
    private_data->status.global.param_number_detected = 0;
    private_data->status.global.prod_number_from_file = 0;
    private_data->status.global.sw_version_from_file = 0;
    private_data->status.global.param_number_from_file = 0;

    private_data->status.global.build_number        = 0;
    private_data->status.global.internal_sw_version = 0;
    private_data->status.global.asic_patch_number   = 0;

    VTSS_MSLEEP(500);

    //mesa_bool_t bIs_system_status = false;
    //Telemetry_at_Boot_Up_Error_e eTelemetry_at_Boot_Up_Error;
    //mesa_rc rc = check_for_poe_firmware_errors(inst, &bIs_system_status, &eTelemetry_at_Boot_Up_Error); // Download succeeded

    uint8_t buf_rx[PD_BUFFER_SIZE];
    mesa_bool_t                     ePOE_BOOL_Is_system_status = false;
    Telemetry_at_Boot_Up_Error_e    eTelemetry_at_Boot_Up_Error = eBoot_Unknown_error;

    // on startup we got single system status from boot with detailed boot error
    if ((private_data->eTelemetry_at_Boot_Up_Error != eBoot_Unknown_error) && (private_data->IsBootError == true))
    {
         memcpy(private_data->buf_rx , buf_rx , PD_BUFFER_SIZE);
         eTelemetry_at_Boot_Up_Error = private_data->eTelemetry_at_Boot_Up_Error;

         private_data->eTelemetry_at_Boot_Up_Error = eBoot_Unknown_error;
         private_data->IsBootError = false;

         rc = MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED;
         DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"BootError deteceted on startup.\n");
    }
    else // no error from boot - lets try to read PoE MCU RX buffer
    {
        // check for valid communication with PoE MCU
        rc = Get_15Bytes_CommProtocol_Reply(inst,
                       buf_rx,
                       255,
                       &ePOE_BOOL_Is_system_status,
                       &eTelemetry_at_Boot_Up_Error);

        // no answer from poe
        if ((rc != MESA_RC_OK) && (rc != MESA_RC_ERR_POE_RX_BUF_EMPTY))
        {
            // reset poe mcu by io so we can read the sent once telemetry - get system status on startup
            // and by this to know the status ot the boot
            meba_poe_io_reset(inst);

            VTSS_MSLEEP(5000);

            rc = Get_15Bytes_CommProtocol_Reply(inst,
                       buf_rx,
                       255,
                       &ePOE_BOOL_Is_system_status,
                       &eTelemetry_at_Boot_Up_Error);
        }

        DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Normal firmware flow.\n");
    }

    if (rc == MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED)
    {
        switch (eTelemetry_at_Boot_Up_Error)
        {
        case eBoot_error_Application_CRC_error_Download_is_required_for_PD69200:
        case eBoot_error_hW_error_from_Boot_try_to_program_a_PD69210_PD69220_firmware_into_PD69200_device:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69200_CONTROLLER_TYPE;
                break;
            }

        case eBoot_error_Application_CRC_error_Download_is_required_for_PD69210_PD69220:
        case eBoot_error_hw_error_from_Boot_try_to_program_a_PD69200_firmware_into_PD69210_PD69220_device:
        case eBoot_error_sys_type_error_from_APP_try_to_program_a_PD69220_firmware_into_PD69210_device:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69210_CONTROLLER_TYPE;
                break;
            }

        case eBoot_error_sys_type_error_from_APP_try_to_program_a_PD69210_firmware_into_PD69220_device:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69220_CONTROLLER_TYPE;
                break;
            }

        default:
            {
                DEBUG(inst, MEBA_TRACE_LVL_ERROR,"Unable to determine poe firmware.\n");
                break;
            }
        }

        // in case user select specific PoE controller - use it instead of the auto detected PoE controller and warn if different
        if (private_data->tPoE_parameters.ePoE_Controller_Type_default != MEBA_POE_PD692X0_CONTROLLER_TYPE_AUTO_DETECTION)
        {
             DEBUG(inst, MEBA_TRACE_LVL_WARNING,"Detected PoE controller: %d is different than USER selection: %d.\n", ePoE_detected_controller_type , MEBA_POE_PD692X0_CONTROLLER_TYPE_AUTO_DETECTION);
             ePoE_detected_controller_type = private_data->tPoE_parameters.ePoE_Controller_Type_default;
        }
    }
    else // RC timeout or OK - try to read the product number
    {
        rc = meba_poe_pd69200_ctrl_get_software_version(
            inst,
            &hw_version,
            &prod_number,
            &sw_version,
            &param_number,
            &build_number,
            &internal_sw_version,
            &asic_patch_number);

        // check if read firmware version from chip succeed
        if (rc != MESA_RC_OK) {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "Not able to read firmware version from chip.\n");
            return false;
        }

        private_data->status.global.prod_number_detected  = prod_number;
        private_data->status.global.sw_version_detected   = sw_version;
        private_data->status.global.param_number_detected = param_number;
        private_data->status.global.build_number          = build_number;
        private_data->status.global.internal_sw_version   = internal_sw_version;
        private_data->status.global.asic_patch_number     = asic_patch_number;

        // extract the assembled PoE Controller from product number - 4 PoE controllers: PD69200, PD69210, PD69220 (, PD69200M)
        switch(prod_number)
        {
            case ePD69200_AT:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69200_CONTROLLER_TYPE;
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_AT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: pd69200 AT firmware.");
                break;
            }
            case ePD69200_BT:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69200_CONTROLLER_TYPE;
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_BT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: pd69200 BT firmware.");
                break;
            }
            case ePD69210_AT:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69210_CONTROLLER_TYPE;
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_AT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: pd69210 AT firmware.");
                break;
            }
            case ePD69210_BT:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69210_CONTROLLER_TYPE;
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_BT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: pd69210 BT firmware.");
                break;
            }
            case ePD69220_AT:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69220_CONTROLLER_TYPE;
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_AT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: pd69220 AT firmware.");
                break;
            }
            case ePD69220_BT:
            {
                ePoE_detected_controller_type = MEBA_POE_PD69220_CONTROLLER_TYPE;
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_BT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: pd69220 BT firmware.");
                break;
            }
            case ePD69200M_AT:
            {
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_AT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: pd69200M AT firmware.");
                break;
            }
            case ePD69200M_BT:
            {
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_BT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: pd69200M BT firmware.");
                break;
            }
            default:
            {
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"Unknown detected poe firmware: %d .\n", prod_number);
                break;
            }
        }

        // if detected controller type is unknown - exit with error message
        if (ePoE_detected_controller_type == MEBA_POE_PD692X0_CONTROLLER_TYPE_AUTO_DETECTION)
        {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Controller product number error: %d.\n", prod_number);
//          S_E("SYS-BOOTING: Controller product number error: %d.\n", prod_number);
            private_data->status.global.prod_number_detected  = prod_number;
            private_data->status.global.sw_version_detected   = sw_version;
            private_data->status.global.param_number_detected = param_number;
            private_data->status.global.build_number          = build_number;
            private_data->status.global.internal_sw_version   = internal_sw_version;
            private_data->status.global.asic_patch_number     = asic_patch_number;
            return false;
        }
    }

    // set poe firmware file depend on controller type (PD69200, PD69210, PD69220) and software required BT/Legacy
    if (private_data->is_bt)
    {
        if(ePoE_detected_controller_type == MEBA_POE_PD69200_CONTROLLER_TYPE)
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "loaded poe firmware: pd69200 BT firmware.");
            private_data->builtin_firmware = "/etc/mscc/poe/firmware/pd69200_bt_firmware.s19";
            prod_number_from_file = ePD69200_BT;
        }
        else if (ePoE_detected_controller_type == MEBA_POE_PD69210_CONTROLLER_TYPE)
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "loaded poe firmware: pd69210 BT firmware.");
            private_data->builtin_firmware = "/etc/mscc/poe/firmware/pd69210_bt_firmware.s19";
            prod_number_from_file = ePD69210_BT;
        }
        else //if (ePoE_detected_controller_type == ePD69220_CONTROLLER_TYPE)
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "loaded poe firmware: pd69220 BT firmware.");
            private_data->builtin_firmware = "/etc/mscc/poe/firmware/pd69220_bt_firmware.s19";
            prod_number_from_file = ePD69220_BT;
        }
    }
    else // AT mode
    {
        if(ePoE_detected_controller_type == MEBA_POE_PD69200_CONTROLLER_TYPE)
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "loaded poe firmware: pd69200 AT firmware.");
            private_data->builtin_firmware = "/etc/mscc/poe/firmware/pd69200_at_firmware.s19";
            prod_number_from_file = ePD69200_AT;
        }
        else if(ePoE_detected_controller_type == MEBA_POE_PD69210_CONTROLLER_TYPE)
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "loaded poe firmware: pd69210 AT firmware.");
            private_data->builtin_firmware = "/etc/mscc/poe/firmware/pd69210_at_firmware.s19";
            prod_number_from_file = ePD69210_AT;
        }
        else //if(ePoE_detected_controller_type == MEBA_POE_PD69220_CONTROLLER_TYPE)
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "loaded poe firmware: pd69220 AT firmware.");
            private_data->builtin_firmware = "/etc/mscc/poe/firmware/pd69220_at_firmware.s19";
            prod_number_from_file = ePD69220_AT;
        }
    }

    private_data->status.global.prod_number_from_file = prod_number_from_file;

    if (rc != MESA_RC_OK)
    {
        //DEBUG(inst, MEBA_TRACE_LVL_INFO, "Not able to read firmware version from chip.\n");
        return false;
    }

    if (!microsemi_firmware)
    {
        struct stat st;

        // check valid builtin_firmware file
        if (private_data->builtin_firmware == NULL)
        {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Error: builtin_firmware is null.\n");
            return MESA_RC_ERROR;
        }

        if ((fd = open(private_data->builtin_firmware, O_RDONLY)) < 0) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Could not open %s for reading.\n", private_data->builtin_firmware);
            return MESA_RC_ERROR;
        }

        if (fstat(fd, &st) < 0) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Could not determine size of %s.\n",
                  private_data->builtin_firmware);
            close(fd);
            return MESA_RC_ERROR;
        }
        mapped_memory_size = (((st.st_size - 1) / getpagesize()) + 1) * getpagesize(); // Round up

        if ((mapped_memory = mmap(NULL, mapped_memory_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Could not map %s.\n", private_data->builtin_firmware);
        }
        microsemi_firmware = mapped_memory;
    }

    swNum_ptr = strstr(microsemi_firmware, swNum);
    if (swNum_ptr && (swNum_ptr - microsemi_firmware) < MAX_FIRMWARE_HEADER_LEN) {
        swNum_ptr += strlen(swNum) + 1;
        sw_ver_from_file = atoi(swNum_ptr);
    } else {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "Not able to read %s from upgrade image.\n", swNum);
        if (fd >= 0) {
            if (mapped_memory) {
                munmap(mapped_memory, mapped_memory_size);
            }
            close(fd);
        }
        return false;
    }

    param_ptr = strstr(microsemi_firmware, param);
    if (param_ptr && (param_ptr - microsemi_firmware) < MAX_FIRMWARE_HEADER_LEN) {
        param_ptr += strlen(param) + 1;
        param_from_file  = atoi(param_ptr);
    } else {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "Not able to read %s from upgrade image.\n", param);
        if (fd >= 0) {
            if (mapped_memory) {
                munmap(mapped_memory, mapped_memory_size);
            }
            close(fd);
        }
        return false;
    }

    if (fd >= 0) {
        if (mapped_memory) {
            munmap(mapped_memory, mapped_memory_size);
        }
        close(fd);
    }

    private_data->status.global.sw_version_from_file = sw_ver_from_file;
    private_data->status.global.param_number_from_file = param_from_file;

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "detected: %d - %d.%d , from_file: %d - %d.%d",
              prod_number, sw_version ,param_number , prod_number_from_file, sw_ver_from_file , param_from_file);

    if ((sw_ver_from_file == sw_version) &&
        (sw_version != 0) &&
        (param_from_file == param_number))
    {
        return true;
    }
    else
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "Different PoE MCU firmware versions, found %d - %d.%d ,expecting %d - %d.%d",
              prod_number, sw_version, param_number, prod_number_from_file, sw_ver_from_file, param_from_file);
        return false;
    }
}


// return values:
// - MESA_RC_OK                             : No PD69200 chip found, don't do anything
// - MESA_RC_ERR_POE_FIRMWARE_IS_UP_TO_DATE : firmware is up to date
// - MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED     : firmware update needed
static mesa_rc meba_poe_pd69200_prepare_firmware_upgrade(const meba_poe_ctrl_inst_t* const inst,
                                                         mesa_bool_t    version_check,
                                                         size_t         firmware_size,
                                                         const char     *microsemi_firmware)
{
    mesa_rc rc = meba_poe_pd69200_get_chipset(inst);
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Enter for instance %s state %d , version_check %d",  __FUNCTION__, inst->adapter_name, rc , version_check);
    if (rc != MEBA_POE_CHIPSET_FOUND)
    {
        DEBUG(inst, MEBA_TRACE_LVL_WARNING, "%s: No PD69200 chip found, don't do anything", inst->adapter_name);
        return MESA_RC_OK; // No PD69200 chip found, don't do anything
    }

    if (version_check)
    {
        if (is_firmware_version_identical(inst, microsemi_firmware))
        {
            DEBUG(inst, MEBA_TRACE_LVL_WARNING, "%s: Firmware upgrade not needed - versions identical", inst->adapter_name);
            return MESA_RC_ERR_POE_FIRMWARE_IS_UP_TO_DATE;
        }
    }

    meba_poe_pd69200_set_chipset(inst, MEBA_POE_FIRMWARE_UPGRADE);
    return MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED;
}


// return values:
// MESA_RC_OK : No PD69200 chip found, don't do anything
// MESA_RC_ERROR : firmware file or driver error
static mesa_rc meba_poe_pd69200_firmware_upgrade(const meba_poe_ctrl_inst_t* const inst,
                                                 mesa_bool_t reset,
                                                 size_t firmware_size,
                                                 const char* microsemi_firmware)
{
    mesa_rc rc = MESA_RC_ERROR;
    uint8_t      buf[PD_BUFFER_SIZE];
    uint32_t     byte_cnt = 0;
    uint8_t      progress = 0;
    uint8_t      prev_progress = 255;
    const char* byteArr;
    uint8_t      line[LINE_SIZE_MAX];
    uint8_t      line_index;
    int          fd = -1;
    size_t       mapped_memory_size = 0;
    char* mapped_memory = NULL;

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: Enter %d",  __FUNCTION__, meba_poe_pd69200_get_chipset(inst));

    if (MEBA_POE_FIRMWARE_UPGRADE != meba_poe_pd69200_get_chipset(inst))
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "No PoE chip was found, %s(): val: %d",__func__, meba_poe_pd69200_get_chipset(inst));
        return MESA_RC_OK; // No PD69200 chip found, don't do anything
    }

    // send get software version telemetry to check whether we have a valid firmware
    mesa_rc valid = pd69200_is_firmware_valid(inst);

    if (valid == MESA_RC_OK) { // Valid firmware exists
        // Section 5.1
        uint8_t download[] = { 0x01, 0x01, 0xFF, 0x99, 0x15, 0x16, 0x16, 0x99, DUMMY_BYTE, DUMMY_BYTE, DUMMY_BYTE, DUMMY_BYTE, DUMMY_BYTE, 0x03, 0xFA };
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Valid firmware - start download");
        char *fname = "DOWNLOAD_COMMAND";
        if (MESA_RC_OK != pd69200_tx(inst, __FUNCTION__, __LINE__, download, fname)) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "TX failed");
            return MESA_RC_ERROR;
        }
    } else { // Invalid or non-existing firmware
        pd69200_rd(inst, buf, PD_BUFFER_SIZE);  // clear RX buffer
        pd69200_rd(inst, buf, PD_BUFFER_SIZE);  // clear RX buffer
        // Section 5.2
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "Invalid firmware - start download");
        pd69200_sendEnter(inst);
    }

    VTSS_MSLEEP(2000); // Take a good long nap, otherwise the PoE module can cause the entire system to reset
    pd69200_firm_update_rd(inst, buf, 5); // read TPE\r\n - Section 5.1 - step 2
    if ((buf[0] != 'T') || (buf[1] != 'P') || (buf[2] != 'E')) {
        DEBUG(inst, MEBA_TRACE_LVL_WARNING, "No TPE!");
        // Reset - Section 5.1 - step 9
        //        goto out;
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Sending 'E' - erasing memory - Section 5.1 - step 3");
    buf[0] = 'E';
    (void)pd69200_wr(inst, buf, 1, "E");
    VTSS_MSLEEP(100);
    pd69200_firm_update_rd(inst, buf, 5); // read TOE\r\n - Section 5.1 - step 3;
    if ((buf[0] != 'T') || (buf[1] != 'O') || (buf[2] != 'E')) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "No TOE!");
        //        goto out;
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Erasure may last up to 5 seconds. - Section 5.1 - step 4");
    VTSS_MSLEEP(5000);

    pd69200_firm_update_rd(inst, buf, 4); // read TE\r\n - Section 5.1 - step 4
    if ((buf[0] != 'T') || (buf[1] != 'E')) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "No TE!");
        //        goto out;
    }
    VTSS_MSLEEP(100);

    pd69200_firm_update_rd(inst, buf, 5); // read TPE\r\n - Section 5.1 - step 4
    if ((buf[0] != 'T') || (buf[1] != 'P') || (buf[2] != 'E')) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "No TPE!");
        //        goto out;
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Sending 'P' - program memory - Section 5.1 - step 5");
    buf[0] = 'P';
    (void)pd69200_wr(inst, buf, 1, "P");
    VTSS_MSLEEP(100);
    pd69200_firm_update_rd(inst, buf, 5); // read TOP\r\n - Section 5.1 - step 5
    if ((buf[0] != 'T') || (buf[1] != 'O') || (buf[2] != 'P')) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "No TOP");
        //        goto out;
    }

    if (!microsemi_firmware) { // Use built-in firmware
        struct stat st;
        poe_driver_private_t* private_data =
            (poe_driver_private_t*)(inst->private_data);

        // check valid builtin_firmware file
        if (private_data->builtin_firmware == NULL)
        {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Error: builtin_firmware is null.\n");
            return MESA_RC_ERROR;
        }

        if ((fd = open(private_data->builtin_firmware, O_RDONLY)) < 0)
        {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Could not open %s for reading.\n",
                  private_data->builtin_firmware);
            return MESA_RC_ERROR;
        }

        if (fstat(fd, &st) < 0) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Could not determine size of %s.\n",
                  private_data->builtin_firmware);
            close(fd);
            return MESA_RC_ERROR;
        }
        firmware_size = st.st_size;

        mapped_memory_size = (((st.st_size - 1) / getpagesize()) + 1) * getpagesize(); // Round up

        if ((mapped_memory = mmap(NULL, mapped_memory_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Could not map %s.\n",
                  private_data->builtin_firmware);
            close(fd);
            return MESA_RC_ERROR;
        }
        microsemi_firmware = mapped_memory;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Updating PoE firmware...");

    // If greater than 127 then we have reached end of file
    while ((byte_cnt < firmware_size) && (*microsemi_firmware <= 127)) {

        byteArr = microsemi_firmware;

        // Print out progress
        progress = (byte_cnt * 10) / firmware_size;
        if (progress != prev_progress) {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "PoE Firmware update progress:%d %%", progress * 10);
            prev_progress = progress;
        }

        if (byteArr[0] == 10) {
            DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Skipping LF (Line Feed)");
            microsemi_firmware++;
            byte_cnt++;
            byteArr = microsemi_firmware;
        }

        if (byteArr[0] != 'S') {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Line should start with S byteArr[0]:0x%X", byteArr[0]);
            break;
        }

        if (byteArr[1] == '0') { //skip line that starts with "S0"
            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Skipping lines starting with S0");

            // If greater than 127 then we have reached end of file
            while (*microsemi_firmware != '\n' && *microsemi_firmware < 127 && byte_cnt <= firmware_size) {
                byte_cnt++;
                DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Skipping S0 lines microsemi_firmware:0x%X, byte_cnt:%u", *microsemi_firmware, byte_cnt);
                microsemi_firmware++;
            }

            // Lines Starting with S3 or S7
        } else if (byteArr[1] == '3' || byteArr[1] == '7') {
            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Lines Starting with S3 or S7 - Section 5.1 - step 6");

            line_index = 0;
            // If greater than 127 then we have reached end of file
            while (*microsemi_firmware != '\n' && *microsemi_firmware < 127 && byte_cnt <= firmware_size) {
                line[line_index++] = *microsemi_firmware;
                microsemi_firmware++;
                byte_cnt++;
            }
            microsemi_firmware++; // For the "\n"
            byte_cnt++;

            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Writing new line - byte_cnt=%u", byte_cnt);
            line[line_index++] = '\n';
            line[line_index] = 0;

            (void)pd69200_wr(inst, line, line_index, "line"); // Write the line - Section 5.1 - step 6
            //T_NG_HEX(VTSS_TRACE_GRP_CUSTOM, line, line_index);

            pd69200_firm_update_rd(inst, buf, 4); // reading T*\r\n or TP\r\n - Section 5.1 - step 6

            if (buf[0] == 'T' && buf[1] == '*') { // if read T*\r\n
                DEBUG(inst, MEBA_TRACE_LVL_NOISE, "NOT END of File");
            } else if (buf[0] == 'T' && buf[1] == 'P') { // if read TP\r\n
                DEBUG(inst, MEBA_TRACE_LVL_NOISE, "END of File");     // Reset - Section 5.1 - step 7
                DEBUG(inst, MEBA_TRACE_LVL_INFO ,"PoE Firmware update progress:100 %%\n");
                break; //end of file
            } else {
                DEBUG(inst, MEBA_TRACE_LVL_ERROR, "No Ack");
                rc = MESA_RC_ERROR;
                goto error_out;
            }

        } else {
            // Unknown Sx number
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Unknown start value S=%d", byteArr[1]);
            break;
        }
    }

    // Wait 400ms - Section 5.1 - step 8
    VTSS_MSLEEP(2000); // Take a good long nap, otherwise the PoE module can cause the entire system to reset

    // Reset - Section 5.1 - step 9
    buf[0] = 'R';
    buf[1] = 'S';
    buf[2] = 'T';
    MESA_RC(pd69200_wr(inst, buf, 3, "RST"));

    VTSS_MSLEEP(10000);
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Download succeeded");

    uint8_t buf_rx[PD_BUFFER_SIZE];
    mesa_bool_t                     ePOE_BOOL_Is_system_status = false;
    Telemetry_at_Boot_Up_Error_e    eTelemetry_at_Boot_Up_Error = eBoot_Unknown_error;

    // check for emerging system status
    rc = Get_15Bytes_CommProtocol_Reply(inst,
                   buf_rx,
                   255,
                   &ePOE_BOOL_Is_system_status,
                   &eTelemetry_at_Boot_Up_Error);

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "POE_BOOL_Is_system_status=%d ,Telemetry_at_Boot_Up_Error=%d", ePOE_BOOL_Is_system_status, eTelemetry_at_Boot_Up_Error);

    if (ePOE_BOOL_Is_system_status == true)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "System status emerging detected");

        if (eTelemetry_at_Boot_Up_Error != eBoot_Unknown_error)
        {
             DEBUG(inst, MEBA_TRACE_LVL_INFO, "Boot_Up_Error detected");

             poe_driver_private_t *private_data = (poe_driver_private_t *)(inst->private_data);
             private_data->IsBootError = true;
             private_data->eTelemetry_at_Boot_Up_Error = eTelemetry_at_Boot_Up_Error;
             memcpy(private_data->buf_rx , buf_rx , PD_BUFFER_SIZE);
        }
    }

    // check for error in case of missing poe chipset
    if (rc == MESA_RC_ERROR)
    {
        // This is where we end if there are no PoE board detected.
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "PD69200 No PoE chipset detected. rc=MESA_RC_ERROR");
        return MESA_RC_ERROR;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "PD69200 PoE chipset detected");

    meba_poe_pd69200_set_chipset(inst, MEBA_POE_CHIPSET_FOUND);

 error_out:
    if (fd >= 0) {
        if (mapped_memory) {
            munmap(mapped_memory, mapped_memory_size);
        }
        close(fd);
    }

    return rc;
}




/*********************
   Public Functions
**********************/


mesa_rc meba_poe_pd69200_ctrl_globals_cfg_set(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_global_cfg_t* cfg_global)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    meba_poe_global_cfg_t* current_global_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.global);

    current_global_cfg->global_ignore_pd_auto_class_request = cfg_global->global_ignore_pd_auto_class_request;
    current_global_cfg->global_legacy_pd_class_mode = cfg_global->global_legacy_pd_class_mode;

    if (//cfg_global->primary_max_power_w                    != 0 &&
        current_global_cfg->primary_max_power_w            == cfg_global->primary_max_power_w &&
        current_global_cfg->legacy_detect                  == cfg_global->legacy_detect)
    {
        return MESA_RC_OK;
    }

    current_global_cfg->primary_max_power_w    = cfg_global->primary_max_power_w;
    current_global_cfg->legacy_detect          = cfg_global->legacy_detect;

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "AF-AT Update configuration for controller");

    uint8_t supports_legacy_detection;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_SUPPORTS_LEGACY_DETECTION, &supports_legacy_detection, "supports_legacy_detection"));      // Supports Legacy detection.
    if (supports_legacy_detection != cfg_global->legacy_detect)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_AT_SUPPORTS_LEGACY_DETECTION, cfg_global->legacy_detect));
    }

    uint16_t  power_consumption_w;
    uint16_t  max_shutdown_voltage_dv;
    uint16_t  min_shutdown_voltage_dv;
    uint8_t   guard_band;
    uint8_t   bank;
    uint16_t  power_limit_w;

    MESA_RC(pd69200_get_power_supply_parameters(
                inst,
                &power_consumption_w,
                &max_shutdown_voltage_dv,
                &min_shutdown_voltage_dv,
                &guard_band,
                &bank,
                &power_limit_w));

    if ((guard_band != 0x2) || (power_limit_w != cfg_global->primary_max_power_w))
    {
        power_limit_w = cfg_global->primary_max_power_w;
        guard_band = 0x2;           // We set guard to 2W in order to get priority to take over as soon as possible.

        MESA_RC(meba_poe_pd69200_set_power_banks(
                inst,
                bank,
                power_limit_w,
                max_shutdown_voltage_dv,
                min_shutdown_voltage_dv,
                guard_band));
    }

    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_port_cfg_set(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t      handle,
    meba_poe_port_cfg_t         *req_port_cfg)
{
    uint8_t channel = handle;

    meba_poe_port_cfg_t* port_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.ports[handle]);

    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }
    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    // port < max poe ports
    if (handle >= inst->port_poe_length)
    {
        //DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_OK;
    }

    if ((port_cfg->enable == req_port_cfg->enable) &&
        (port_cfg->priority == req_port_cfg->priority) &&
        (port_cfg->legacy_support == req_port_cfg->legacy_support))
    {
        return MESA_RC_OK;
    }

    DEBUG(inst,
          MEBA_TRACE_LVL_INFO, "Update AF-AT configuration for controller port %2d , EnDis(%d->%d): %8s -> %8s , priority(%d->%d): %4s -> %4s , legacy support(%d->%d): %8s -> %8s",
          handle,
          port_cfg->enable,
          req_port_cfg->enable,
          port_cfg->enable ? "Enabled" : "Disabled",
          req_port_cfg->enable ? "Enabled" : "Disabled",
          port_cfg->priority,
          req_port_cfg->priority,
          (port_cfg->priority == MEBA_POE_PORT_PD_POWER_PRIORITY_CRITICAL) ? "crit" : (port_cfg->priority == MEBA_POE_PORT_PD_POWER_PRIORITY_HIGH) ? "high" : "low",
          (req_port_cfg->priority == MEBA_POE_PORT_PD_POWER_PRIORITY_CRITICAL) ? "crit" : (req_port_cfg->priority == MEBA_POE_PORT_PD_POWER_PRIORITY_HIGH) ? "high" : "low",
          port_cfg->legacy_support,
          req_port_cfg->legacy_support,
          (port_cfg->legacy_support) ?  "Enabled" : "Disabled",
          (req_port_cfg->legacy_support) ?  "Enabled" : "Disabled");

    /* mesa_poe_milliwatt_t power_pd69200  = req_port_cfg->max_power; */

    /* // Section 4.5.14 in user guide */
    /* uint max_port_power = pd69200_get_port_power_max(handle); */

    /* if (power_pd69200 > max_port_power) { */
    /*     power_pd69200 = max_port_power; */
    /* } */

    /* if (power_pd69200 > 0) { */
    /*     MESA_RC(meba_poe_pd69200_ctrl_set_power_limit_for_channels( */
    /*         inst, handle, power_pd69200)); */
    /* } */

    /* // Section 4.5.15 in user guide */
    /* MESA_RC(meba_poe_pd69200_ctrl_set_temporary_power_limit_for_channels( */
    /*     inst, handle, power_pd69200)); */

    uint8_t enable;
    if (req_port_cfg->enable == 0) {
        enable = 0; // Disable
    } else {
        enable = 1; // Disable
    }

    // port type:
    // 1 - IEEE802.3AF/AT operation
    // 2 - POH operation
    uint8_t port_type = (req_port_cfg->legacy_support ? 2 : 1);

    MESA_RC(meba_poe_pd69200_ctrl_set_enable_disable_channels(inst, channel, enable, port_type));

    uint8_t pd69200_prio = 3; // Default to low priority

    // Type conversion -- See section 4.5.16 in PD69200 user guide
    switch (req_port_cfg->priority) {
        case MEBA_POE_PORT_PD_POWER_PRIORITY_LOW :
            pd69200_prio = 3;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_HIGH:
            pd69200_prio = 2;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_CRITICAL:
            pd69200_prio = 1;
            break;
        default:
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Unknown priority: %d\n",  __FUNCTION__, req_port_cfg->priority);
    }

    MESA_RC(meba_poe_pd69200_ctrl_set_port_priority(inst, channel, pd69200_prio));

    *port_cfg = *req_port_cfg;
    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_do_reset(
    const meba_poe_ctrl_inst_t* const inst)
{
    // Empty i2c buffer.
    uint8_t dummy;
    int i = 30;
    while (i--) {
        pd69200_rd(inst, &dummy, 1);
    }

    MESA_RC(meba_poe_pd69200_ctrl_reset_command(inst));


    uint8_t buf[PD_BUFFER_SIZE];
    // After reset we look for the REPORT KEY to show up
    mesa_bool_t found = false;
    i = 50; // We do read maximum 50 bytes before giving up.
    while (i--) {
        if (pd69200_rd(inst, buf, 1) != MESA_RC_OK) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s: Read Failed", __FUNCTION__);
            found = false;
            break;
        }

        if (buf[0] == REPORT_KEY) {
            DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Found REPORT_KEY", __FUNCTION__);
            found = true;
            break;
        }

        VTSS_MSLEEP(100); // OK, not an expected byte, give PoE controller a little more time to come up, before checking again.
    }

    if (found) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Found PD69200", __FUNCTION__);
        // Read rest of the response in order to clear buffer
        if (pd69200_rd(inst, &buf[1], PD_BUFFER_SIZE - 1) != MESA_RC_OK) {
            found = false;
        }
    } else {
        char dbg_txt[PD_BUFFER_SIZE * 4];
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s: Invalid response: %s", __FUNCTION__,
              print_as_hex_string(buf, sizeof(buf), dbg_txt, sizeof(dbg_txt)));
    }

    (void)get_seq_num(true); // Reset the sequence number
    return (found ? MESA_RC_OK : MESA_RC_ERROR);
}

mesa_rc meba_poe_pd69200_ctrl_version_get(
    const meba_poe_ctrl_inst_t* const inst,
    uint32_t                        max_size,
    char* value)
{
    uint8_t   hw_version;
    uint8_t   prod_number;
    uint16_t  sw_version;
    uint8_t   param_number;
    uint8_t   build_number;
    uint16_t  internal_sw_version;
    uint16_t  asic_patch_number;

    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    MESA_RC(meba_poe_pd69200_ctrl_get_software_version(
                inst,
                &hw_version,
                &prod_number,
                &sw_version,
                &param_number,
                &build_number,
                &internal_sw_version,
                &asic_patch_number));

    snprintf(value, max_size,
             "HW Ver.:%d, Prod:%d, sw ver:%d, param:%d, build:%d, internal sw ver:%d, Asic Patch Num:%d",
             hw_version, prod_number, sw_version, param_number, build_number, internal_sw_version, asic_patch_number);

    return MESA_RC_OK;
}

mesa_rc print_im_at(const meba_poe_ctrl_inst_t* const inst, meba_poe_indv_mask_at_t *im_AT)
{
    // --------------------- individual mask configure by defaults -------------------- //

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "AF/AT individual masks:");

    // Turn off lowest priority port, when a higher priority has a PD connected, see section 4.5.10
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_IGNORE_HIGHER_PRIORITY, &im_AT->at_ignore_higher_priority, "ignore_higher_priority"));      // Ignore higher priority
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"ignore_higher_priority=%d", im_AT->at_ignore_higher_priority);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_SUPPORTS_LEGACY_DETECTION, &im_AT->at_supports_legacy_detection, "supports_legacy_detection"));      // Supports Legacy detection.
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"supports_legacy_detection=%d", im_AT->at_supports_legacy_detection);

    // Disable i2c ready interrupt
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_MESSAGE_READY_NOTIFY, &im_AT->at_message_ready_notify, "message_ready_notify"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"message_ready_notify=%d", im_AT->at_message_ready_notify);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_LAYER2_PRIORITY_BY_PD, &im_AT->at_layer2_priority_by_PD, "layer2_priority_by_PD")); // get Allow the priority to be fetched from lldp
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"layer2_priority_by_PD=%d", im_AT->at_layer2_priority_by_PD);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_MATRIX_SUPPORT_4P, &im_AT->at_matrix_support_4p, "matrix_support_4p")); // get matrix support 4p
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"matrix_support_4p=%d", im_AT->at_matrix_support_4p);

    // --------------------- individual mask configure by product -------------------- //

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_SUPPORTS_BACKOFF, &im_AT->at_supports_backoff, "Supports_backoff")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Supports_backoff=%d", im_AT->at_supports_backoff);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_LED_STREAM_TYPE, &im_AT->at_led_stream_type, "LED_stream_type")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"LED_stream_type=%d", im_AT->at_led_stream_type);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_PSE_POWERING_PSE_CHECKING, &im_AT->at_pse_powering_pse_checking, "PSE_powering_PSE_checking")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"PSE_powering_PSE_checking=%d", im_AT->at_pse_powering_pse_checking);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_xSYSTEM_OK_PIN_BEHAVIOR, &im_AT->at_xSystem_OK_pin_behavior, "xSystem_OK_pin_behavior")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"xSystem_OK_pin_behavior=%d", im_AT->at_xSystem_OK_pin_behavior);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_ENABLE_ASIC_REFRESH, &im_AT->at_enable_asic_refresh, "Enable_ASIC_Refresh")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Enable_ASIC_Refresh=%d", im_AT->at_enable_asic_refresh);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_LAYER2_LLDP_ENABLE, &im_AT->at_layer2_lldp_enable, "Layer2_LLDP_enable")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Layer2_LLDP_enable=%d", im_AT->at_layer2_lldp_enable);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_CLASS_0_EQUAL_AF, &im_AT->at_class_0_equal_af, "Class_0_equal_AF")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Class_0_equal_AF=%d", im_AT->at_class_0_equal_af);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_CLASS_1_2_3_EQUAL_AF, &im_AT->at_class_1_2_3_equal_af, "Class_1_2_3_equal_AF")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Class_1_2_3_equal_AF=%d", im_AT->at_class_1_2_3_equal_af);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_LLDP_BEST_EFFORT, &im_AT->at_lldp_best_effort, "LLDP_best_effort")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"LLDP_best_effort=%d", im_AT->at_lldp_best_effort);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_AUTO_ZONE2_PORT_ACTIVATION, &im_AT->at_auto_zone2_port_activation, "Auto_Zone2_port_activation")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Auto_Zone2_port_activation=%d", im_AT->at_auto_zone2_port_activation);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_HOCPP_HIGH_OVER_CURRENT_PULSE_PROTECTION, &im_AT->at_hocpp_high_over_current_pulse_protection, "HOCPP_high_over_current_pulse_protection")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"HOCPP_high_over_current_pulse_protection=%d", im_AT->at_hocpp_high_over_current_pulse_protection);

    return MESA_RC_OK;
}


mesa_rc print_im_bt(const meba_poe_ctrl_inst_t* const inst,  meba_poe_indv_mask_bt_t *im_BT)
{

    //------ BT individual masks - stay with defaults ------ //

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"BT individual masks:");

    // Turn off lowest priority port, when a higher priority has a PD connected.
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_IGNORE_HIGHER_PRIORITY, &im_BT->bt_ignore_high_priority, "ignore_high_priority"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"ignore_high_priority=%d", im_BT->bt_ignore_high_priority);

    // Support High res detection.
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_SUPPORT_HIGH_RES_DETECTION, &im_BT->bt_support_high_res_detection, "support_high_res_detection"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"support_high_res_detection=%d", im_BT->bt_support_high_res_detection);

    // I2C restart enable - Initializes the I2C module system after 10 seconds of inactivity.
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_I2C_RESTART_ENABLE, &im_BT->bt_i2c_restart_enable, "i2c_restart_enable"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"i2c_restart_enable=%d", im_BT->bt_i2c_restart_enable);

    // HOCPP - high_over Current Pulse Protection
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_HOCPP, &im_BT->bt_hocpp, "hocpp"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"hocpp=%d", im_BT->bt_hocpp);

    // PSE powering PSE checking
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_PSE_POWERING_PSE_CHECKING, &im_BT->bt_pse_powering_pse_checking, "pse_powering_pse_checking"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"pse_powering_pse_checking=%d", im_BT->bt_pse_powering_pse_checking);

    // Layer2 Power Allocation Limit.
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_LAYER2_POWER_ALLOCATION_LIMIT, &im_BT->bt_layer2_power_allocation_limit, "layer2_power_allocation_limit"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"layer2_power_allocation_limit=%d", im_BT->bt_layer2_power_allocation_limit);

    // Support adding lldp half priority.
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY, &im_BT->bt_support_lldp_half_priority, "support_lldp_half_priority"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"support_lldp_half_priority=%d", im_BT->bt_support_lldp_half_priority);

    //------ BT individual masks - configuration depends on product ---------//

    // Enable port poe led.
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_LED_STREAM_TYPE, &im_BT->bt_led_stream_type, "led_stream_type"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"led_stream_type=%d", im_BT->bt_led_stream_type);

    // Port LED Blinks at invalid signature or connection-check error.
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR, &im_BT->bt_blinks_at_invalid_signature, "blinks_at_invalid_signature"));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"blinks_at_invalid_signature=%d", im_BT->bt_blinks_at_invalid_signature);

    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_xSYSTEM_OK_PIN_BEHAVIOR, &im_BT->bt_xSystem_OK_pin_behavior, "xSystem_OK_pin_behavior")); // get
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"blinks_at_invalid_signature=%d", im_BT->bt_xSystem_OK_pin_behavior);

    return MESA_RC_OK;
}


mesa_bool_t bRunIndvMAskOnce = true;


static mesa_rc meba_poe_pd69200_ctrl_globals_status_get(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_status_t* status)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "chipset not found: %d", meba_poe_pd69200_get_chipset(inst));
        return MESA_RC_ERROR;
    }

    poe_driver_private_t *private_data = (poe_driver_private_t *)(inst->private_data);
    meba_poe_status_t* current_status = &(((poe_driver_private_t*)(inst->private_data))->status.global);

    current_status->poe_power_source        = MEBA_POE_POWER_SOURCE_PRIMARY;

    current_status->i2c_tx_error_counter    = private_data->status.global.i2c_tx_error_counter;

    current_status->prod_number_detected    = private_data->status.global.prod_number_detected;
    current_status->sw_version_detected     = private_data->status.global.sw_version_detected;
    current_status->param_number_detected   = private_data->status.global.param_number_detected;
    current_status->prod_number_from_file   = private_data->status.global.prod_number_from_file;
    current_status->sw_version_from_file    = private_data->status.global.sw_version_from_file;
    current_status->param_number_from_file  = private_data->status.global.param_number_from_file;

    current_status->build_number            = private_data->status.global.build_number;
    current_status->internal_sw_version     = private_data->status.global.internal_sw_version;
    current_status->asic_patch_number       = private_data->status.global.asic_patch_number;

    current_status->ePoE_Controller_Type    = private_data->status.global.ePoE_Controller_Type;
    current_status->is_bt                   = private_data->is_bt;

    current_status->adc_value = 0;

    // adc value supported only on PoE BT mode in versions above 3.55
    if(private_data->status.global.eDetected_poe_firmware_type == MEBA_POE_FIRMWARE_TYPE_BT)
    {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s ,get BT globals_status info", __FUNCTION__);

        uint8_t vmain_fault = 0;
        MESA_RC(meba_poe_pd69200_bt_event_cause_get(inst, &vmain_fault));
        current_status->vmain_out_of_range = vmain_fault;

        uint16_t adc_value = 0;

        //reading poe controller adc IO voltage
        mesa_rc rc = meba_poe_pd69200_ctrl_get_adc_value(inst, &adc_value);
        if (rc == MESA_RC_OK)
            current_status->adc_value = adc_value;

        MESA_RC(meba_poe_pd69200_ctrl_total_power_get(inst, true,
                                              &(current_status->power_consumption_w),
                                              &(current_status->calculated_power_w),
                                              &(current_status->available_power_w),
                                              &(current_status->power_limit_w),
                                              &(current_status->power_bank),
                                              &(current_status->vmain_voltage_dv)));

        if (bRunIndvMAskOnce)
        {
            bRunIndvMAskOnce = false;
            MESA_RC(print_im_bt(inst, &(current_status->tPoe_individual_mask_info.im_BT)));
        }
    }
    else // AT
    {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s ,get AT globals_status info", __FUNCTION__);

        uint16_t pInterrupt_register;
        MESA_RC(meba_poe_pd69200_ctrl_get_system_status(inst, &pInterrupt_register));  //, &cpu_status1, &cpu_status2, &factory_default,NULL, NULL, NULL, NULL, NULL, NULL, NULL);

        // Vmain fault bit 13
        current_status->vmain_out_of_range = (pInterrupt_register >> 13) & 1;

        MESA_RC(meba_poe_pd69200_ctrl_total_power_get(inst, false,
                                          &(current_status->power_consumption_w),
                                          &(current_status->calculated_power_w),
                                          &(current_status->available_power_w),
                                          &(current_status->power_limit_w),
                                          &(current_status->power_bank),
                                          &(current_status->vmain_voltage_dv)));

        MESA_RC(meba_poe_pd69200_ctrl_power_supply_measurements_get(inst,
                                          &(current_status->vmain_voltage_dv),
                                          &(current_status->imain_current_ma)));

        if (bRunIndvMAskOnce)
        {
            bRunIndvMAskOnce = false;
            MESA_RC(print_im_at(inst, &(current_status->tPoe_individual_mask_info.im_AT)));
        }
    }

    *status = *current_status;
    return MESA_RC_OK;
}


// true  - matrix is updated
// false - should update matrix
static mesa_rc pd69200_active_matrix_verify(const meba_poe_ctrl_inst_t* const inst, uint8_t prod_max_poe_ports)
{
    BOOL bNeedToSaveMatrix = FALSE;
    BOOL bMatrixUpdateNeeded = FALSE;

    BOOL continue_to_update = TRUE;

    for (uint8_t i = 0; (i < POE_MAX_LOGICAL_PORTS) && continue_to_update; i++)
    {
        uint8_t port_a, port_b;
        MESA_RC(meba_poe_pd69200_ctrl_get_active_matrix(inst, i, &port_a, &port_b));

        // in case of 2pair port - the port_b which not in use returns the value 78
        if (port_b == 78)
            port_b = 255;

        // check if actual ports matrix configure matches the ports map table - if not return error
        if( i < prod_max_poe_ports)
        {
            if (inst->port_map[i].capabilities & MEBA_POE_PORT_CAP_POE)
            {
                // if any of them are not matching - print it's index and return error
                if ((port_a != inst->port_map[i].phys_port_a) ||
                    (port_b != inst->port_map[i].phys_port_b))
                {
                    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s ,matrix param mismatch at logical port index=%d ,port_a(exist=%d ,required=%d) ,port_b(exist=%d ,required=%d)",
                       __FUNCTION__, i , port_a, inst->port_map[i].phys_port_a,  port_b, inst->port_map[i].phys_port_b);
                    bMatrixUpdateNeeded = TRUE;
                    port_a = inst->port_map[i].phys_port_a;
                    port_b = inst->port_map[i].phys_port_b;
                }
             }
             else // not PoE port - should be 255
             {
                // if any of them are in use - print it's index and return error
                if ((port_a != 255) || (port_b != 255))
                {
                    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s ,matrix param mismatch at logical port index=%d ,not a poe port, port_a(exist=%d, table=%d ,required=255) ,port_b(exist=%d, table=%d, required=255)",
                       __FUNCTION__, i , port_a, inst->port_map[i].phys_port_a,  port_b, inst->port_map[i].phys_port_b);
                    bMatrixUpdateNeeded = TRUE;
                    port_a = 255;
                    port_b = 255;
                }
             }
        }
        // check that the rest of the logical ports (max_prod_ports < iPort < 48 , covers all PoE firmware logical ports: 48) are ignores (255,255)
        // all of the them shuold be marked as not used
        else //  from prod_max_poe_ports to POE_MAX_LOGICAL_PORTS
        {
            // if any of them are in use - print it's index and return error
            if (port_a != 255 || (port_b != 255))
            {
                DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s ,matrix param mismatch at logical port index=%d ,not a poe port, port_a(exist=%d, required=255) ,port_b(exist=%d, required=255)",
                       __FUNCTION__, i , port_a,  port_b);

                bMatrixUpdateNeeded = TRUE;
                port_a = 255;
                port_b = 255;
            }
            else if (port_a == 255 && (port_b == 255))
            {
                 continue_to_update = FALSE;
            }
         }

         if (bMatrixUpdateNeeded)
         {
             bNeedToSaveMatrix = TRUE;
             bMatrixUpdateNeeded = FALSE;

             //DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s(%s): setting matrix, CH=%d ,port_a=%d ,port_b=%d", __FUNCTION__, inst->adapter_name, i ,port_a, port_b);
             MESA_RC(meba_poe_pd69200_ctrl_set_temporary_matrix(inst, i, port_a, port_b));
         }
    }

    if (bNeedToSaveMatrix)
    {
        return MESA_RC_ERROR;
    }
    else
    {
        return MESA_RC_OK;
    }
}



mesa_rc meba_poe_pd69200_do_detection(
    const meba_poe_ctrl_inst_t* const inst)
{
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s(%s)", __FUNCTION__, inst->adapter_name);
    meba_poe_pd69200_set_chipset(inst, MEBA_POE_NO_CHIPSET_FOUND);

    uint8_t buf_rx[PD_BUFFER_SIZE];
    mesa_bool_t                     ePOE_BOOL_Is_system_status = false;
    Telemetry_at_Boot_Up_Error_e    eTelemetry_at_Boot_Up_Error = eBoot_Unknown_error;

    // check for emerging system status
    mesa_rc rc = Get_15Bytes_CommProtocol_Reply(inst,
                   buf_rx,
                   255,
                   &ePOE_BOOL_Is_system_status,
                   &eTelemetry_at_Boot_Up_Error);

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "POE_BOOL_Is_system_status=%d ,Telemetry_at_Boot_Up_Error=%d ,rc=%d", ePOE_BOOL_Is_system_status, eTelemetry_at_Boot_Up_Error , rc);

    if (ePOE_BOOL_Is_system_status == true)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "System status on startup from app detected");

        // if poe boot sent error message - keep it for later use
        if (eTelemetry_at_Boot_Up_Error != eBoot_Unknown_error)
        {
             DEBUG(inst, MEBA_TRACE_LVL_INFO, "Boot_Up_Error detected");

             poe_driver_private_t *private_data = (poe_driver_private_t *)(inst->private_data);
             private_data->IsBootError = true;
             private_data->eTelemetry_at_Boot_Up_Error = eTelemetry_at_Boot_Up_Error;
             memcpy(private_data->buf_rx , buf_rx , PD_BUFFER_SIZE);
        }
    }

    // check for error in case of missing poe chipset
    if (rc == MESA_RC_ERROR)
    {
        // This is where we end if there are no PoE board detected.
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "PD69200 No PoE chipset detected. Reason: rc: %d", rc);
        return rc;
    }

    // now it can be on of the followed states:
    // - ok
    // - firmware update needed
    // - rx buffer is not empty
    // - communication error - MESA_RC_ERR_POE_COMM_PROT_ERR

    meba_poe_pd69200_set_chipset(inst, MEBA_POE_CHIPSET_FOUND);

    if (rc == MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "PD69200 Firmware update required");
        return rc;
    }

    uint8_t   hw_version;
    uint8_t   prod_number;
    uint16_t  sw_version;
    uint8_t   param_number;
    uint8_t   build_number;
    uint16_t  internal_sw_version;
    uint16_t  asic_patch_number;

    rc = meba_poe_pd69200_ctrl_get_software_version(
                inst,
                &hw_version,
                &prod_number,
                &sw_version,
                &param_number,
                &build_number,
                &internal_sw_version,
                &asic_patch_number);

    // check for error
    if (rc == MESA_RC_ERROR)
    {
        // This is where we end if there are no PoE board detected.
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "I2C driver error. Reason: rc: %d", rc);
        return rc;
    }

    // extract the assembled PoE Controller from product number - 4 PoE controllers: PD69200, PD69210, PD69220 (, PD69200M)
    if (rc == MESA_RC_OK)
    {
        poe_driver_private_t *private_data = (poe_driver_private_t *)(inst->private_data);

        switch(prod_number)
        {
            case ePD69200_AT:
            case ePD69210_AT:
            case ePD69220_AT:
            case ePD69200M_AT:
            {
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_AT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: AT firmware=%d", prod_number);

                uint16_t pInterrupt_register;
                rc = meba_poe_pd69200_ctrl_get_system_status(inst, &pInterrupt_register);

                break;
            }
            case ePD69200_BT:
            case ePD69210_BT:
            case ePD69220_BT:
            case ePD69200M_BT:
            {
                private_data->status.global.eDetected_poe_firmware_type = MEBA_POE_FIRMWARE_TYPE_BT;
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"detected poe firmware: BT firmware=%d", prod_number);

                rc = meba_poe_pd69200bt_ctrl_get_bt_system_status(inst);

                break;
            }
            default:
            {
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"Unknown detected poe firmware=%d .\n", prod_number);
                return MESA_RC_ERROR;
            }
        }

        switch(prod_number)
        {
            case ePD69200_AT:
            case ePD69200_BT:
            {
                private_data->status.global.ePoE_Controller_Type = MEBA_POE_PD69200_CONTROLLER_TYPE;
                break;
            }
            case ePD69210_AT:
            case ePD69210_BT:
            {
                private_data->status.global.ePoE_Controller_Type = MEBA_POE_PD69210_CONTROLLER_TYPE;
                break;
            }
            case ePD69220_AT:
            case ePD69220_BT:
            {
                private_data->status.global.ePoE_Controller_Type = MEBA_POE_PD69220_CONTROLLER_TYPE;
                break;
            }
            case ePD69200M_AT:
            case ePD69200M_BT:
            {
                private_data->status.global.ePoE_Controller_Type = MEBA_POE_PD69200M_CONTROLLER_TYPE;
                break;
            }
            default:
            {
                DEBUG(inst, MEBA_TRACE_LVL_INFO,"Unknown detected poe firmware=%d .\n", prod_number);
                return MESA_RC_ERROR;
            }
        }
    }

    // check return code from 'get system status'
    if (rc == MESA_RC_ERROR)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "I2C device driver error.");
        return rc;
    }
    else if (rc == MESA_RC_ERR_POE_FIRM_UPDATE_NEEDED)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "PD69200 Firmware update required");
    }
    else
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s(%s): STATUS OK", __FUNCTION__, inst->adapter_name);
        meba_poe_status_t* current_status = &(((poe_driver_private_t*)(inst->private_data))->status.global);
        MESA_RC(meba_poe_pd69200_ctrl_version_get(inst, MEBA_POE_VERSION_STRING_SIZE, current_status->version));

        MESA_RC(pd69200bt_get_serial_number(inst, &current_status->tSN ));
    }

    return MESA_RC_OK;
}



mesa_rc meba_poe_pd69200_chip_initialization(
    const meba_poe_ctrl_inst_t* const inst,
    mesa_bool_t interruptible_power,
    int16_t     restart_cause)
{
    mesa_bool_t bChangedFlag = false;
    mesa_bool_t bMatrixUpdatedFlag = false;

    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_ERROR;
    }

    meba_poe_parameters_t tPoE_parameters = ((poe_driver_private_t *)(inst->private_data))->tPoE_parameters;
    meba_poe_global_cfg_t* current_global_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.global);

#ifdef SYNC_MISC_POE_PARAMS

    // Disable i2c ready interrupt
    uint8_t message_ready_notify;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_MESSAGE_READY_NOTIFY, &message_ready_notify, "message_ready_notify"));
    if (message_ready_notify != tPoE_parameters.indv_mask_AT_message_ready_notify_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_AT_MESSAGE_READY_NOTIFY  ,tPoE_parameters.indv_mask_AT_message_ready_notify_default));
        bChangedFlag = true;
    }

    // Turn off lowest priority port, when a higher priority has a PD connected, see section 4.5.10
    uint8_t ignore_higher_priority;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_IGNORE_HIGHER_PRIORITY, &ignore_higher_priority, "ignore_higher_priority"));      // Ignore higher priority
    if (ignore_higher_priority != tPoE_parameters.indv_mask_AT_ignore_higher_priority_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_AT_IGNORE_HIGHER_PRIORITY, tPoE_parameters.indv_mask_AT_ignore_higher_priority_default));
        bChangedFlag = true;
    }

    uint8_t supports_legacy_detection;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_SUPPORTS_LEGACY_DETECTION, &supports_legacy_detection, "supports_legacy_detection"));      // Supports Legacy detection.
    if (supports_legacy_detection != tPoE_parameters.indv_mask_AT_supports_legact_detection_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_AT_SUPPORTS_LEGACY_DETECTION, tPoE_parameters.indv_mask_AT_supports_legact_detection_default));
        bChangedFlag = true;
    }

        // See table in section 4.5.9 in PD69200 user guide
    uint8_t enable_LLDP_mode;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_LAYER2_LLDP_ENABLE, &enable_LLDP_mode, "enable_LLDP_mode"));      // get Enable LLDP mode.
    if (enable_LLDP_mode != tPoE_parameters.indv_mask_AT_layer2_lldp_enable_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_AT_LAYER2_LLDP_ENABLE, tPoE_parameters.indv_mask_AT_layer2_lldp_enable_default)); // Enable LLDP mode.
        bChangedFlag = true;
    }

    uint8_t layer2_priority_by_PD;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_LAYER2_PRIORITY_BY_PD, &layer2_priority_by_PD, "layer2_priority_by_PD")); // get Allow the priority to be fetched from lldp
    if (layer2_priority_by_PD != tPoE_parameters.indv_mask_AT_layer2_priority_by_PD_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_AT_LAYER2_PRIORITY_BY_PD, tPoE_parameters.indv_mask_AT_layer2_priority_by_PD_default)); // Allow the priority to be fetched from lldp
        bChangedFlag = true;
    }


    uint8_t matrix_support_4p;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_AT_MATRIX_SUPPORT_4P, &matrix_support_4p, "matrix_support_4p")); // get matrix support 4p
    if (matrix_support_4p != tPoE_parameters.indv_mask_AT_matrix_support_4P_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_AT_MATRIX_SUPPORT_4P, tPoE_parameters.indv_mask_AT_matrix_support_4P_default)); // Allow matrix to support 4p
        bChangedFlag = true;
    }


    // Power Management mode of operation
    uint8_t pm1;
    uint8_t pm2;
    uint8_t pm3;
    MESA_RC(meba_poe_pd69200_get_pm_method(inst, &pm1, &pm2, &pm3));

    if ((pm1 != tPoE_parameters.AT_pm1_default) || (pm2 != tPoE_parameters.AT_PM2_default) || (pm3 != tPoE_parameters.AT_PM3_default))
    {
        MESA_RC(meba_poe_pd69200_set_pm_method(inst, tPoE_parameters.AT_pm1_default, tPoE_parameters.AT_PM2_default, tPoE_parameters.AT_PM3_default));
        bChangedFlag = true;
    }

#endif //SYNC_MISC_POE_PARAMS

    uint16_t  power_consumption_w;
    uint16_t  max_shutdown_voltage_dv;
    uint16_t  min_shutdown_voltage_dv;
    uint8_t   guard_band;
    uint8_t   bank;
    uint16_t  power_limit_w;

    MESA_RC(pd69200_get_power_supply_parameters(
                inst,
                &power_consumption_w,
                &max_shutdown_voltage_dv,
                &min_shutdown_voltage_dv,
                &guard_band,
                &bank,
                &power_limit_w));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: PwrSupply_MaxPwr=%d , power_limit_w=%d", __FUNCTION__, tPoE_parameters.poe_init_params.PwrSupply_MaxPwr, power_limit_w);
    current_global_cfg->primary_max_power_w = power_limit_w;

    // Read active matrix and compare with intended matrix before programming it.
    // Get physical port number from active matrix
    if (pd69200_active_matrix_verify(inst, inst->port_poe_length) != MESA_RC_OK)
    {
        bMatrixUpdatedFlag = true;
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s(%s): PROGRAM MATRIX", __FUNCTION__, inst->adapter_name);
        MESA_RC(pd69200_program_global_matrix(inst));
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s(%s): PROGRAM MATRIX DONE", __FUNCTION__, inst->adapter_name);
    }

     #ifdef POE_LLDP
    // update lldp pd data
    for (uint8_t i = 0; i < inst->port_map_length; i++)
    {
        if (inst->port_map[i].capabilities & MEBA_POE_PORT_CAP_POE)
        {
            MESA_RC(meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(inst, i, 3, 0, 0, 100, 0));
        }
    }
    #endif  //POE_LLDP

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s restart_cause= %d ,ChangedFlag= %d ,bMatrixUpdatedFlag: %d ",  __FUNCTION__,restart_cause , bChangedFlag, bMatrixUpdatedFlag);

    // save settings if:
    // matrix was changed - or -
    // cold start and somthing was modified
    if ( bMatrixUpdatedFlag ||
        ((restart_cause == 0) && (bChangedFlag == true))) // cold start and somthing was modified
    {
         MESA_RC(meba_poe_pd69200_ctrl_save_command(inst));
         DEBUG(inst, MEBA_TRACE_LVL_INFO, "Save PoE settings");
    }

    return MESA_RC_OK;
}



char* GetAT_TitleByPortsStatus(uint8_t bt_port_status)
{
    switch (bt_port_status)
    {
    case eAT_0x00_ON__LEGACY_PD_DET:
        return "0x06: LEGACY PD DET";
    case eAT_0x01_ON__802_2PAIR_3AF_DET:
        return "0x07: 802 2PAIR 3AF DET";
    case eAT_0x02_ON__802_4PAIR_DET:
        return "0x08: 802 4PAIR DET";
    case eAT_0x03_ON__802_2PAIR_POWER_SEQUENCE:
        return "0x0C: 802 2PAIR POWER SEQUENCE";
    case eAT_0x04_ON__802_4PAIR_POWER_SEQUENCE:
        return "0x11: 802 4PAIR POWER SEQUENCE";
    case eAT_0x06_OFF_MAIN_PS_TO_HIGH:
        return "0x12: MAIN PS TO HIGH";
    case eAT_0x07_OFF_MAIN_PS_TO_LOW:
        return "0x1A: MAIN PS TO LOW";
    case eAT_0x08_OFF_DIS_ALL_PORTS_PIN_ACT:
        return "0x1B: DIS ALL PORTS PIN ACT";
    case eAT_0x09_OFF_DERATING_TEMPERATURE_HIGH:
        return "0x1c: DERATING TEMPERATURE HIGH";
    case eAT_0x0C_OFF_NON_EXIST_PORT_NUM:
        return "0x1E: NON EXIST PORT NUM";
    case eAT_0x11_OFF_PWR_UP_IN_PROCESS:
        return "0x1F: PWR UP IN PROCESS";
    case eAT_0x12_OFF_INTERNAL_HW_FAULT:
        return "0x20: INTERNAL HW FAULT";
    case eAT_0x1A_OFF_USER_SETTING:
        return "0x22: USER SETTING";
    case eAT_0x1B_OFF_DET_IN_PROCESS:
        return "0x24: DET IN PROCESS";
    case eAT_0x1C_OFF_NON_802_3AF_PD:
        return "0x25: NON 802 3AF PD";
    case eAT_0x1D_OFF_SUCCESION_OF_OVL_AND_UDL:
        return "0x26: SUCCESION OF OVL AND UDL";
    case eAT_0x1E_OFF_UNDERLOAD_OR_CAP_TO_SMALL:
        return "0x34: UNDERLOAD OR CAP TO SMALL";
    case eAT_0x1F_OFF_OVERLOAD_OR_CAP_TO_BIG:
        return "0x35: OVERLOAD OR CAP TO BIG";
    case eAT_0x20_OFF_PWR_BUDGET_EXCEDDED:
        return "0x36: PWR BUDGET EXCEDDED";
    case eAT_0x21_OFF_INTERNAL_HW_ROUTING_ERROR:
        return "0x37: INTERNAL HW ROUTING ERROR";
    case eAT_0x24_OFF_EXT_VOLT_INJ_CAP_DET_MODE:
        return "0x3C: EXT VOLT INJ CAP DET MODE";
    case eAT_0x25_OFF_IMPROPER_CAP_DET_MODE:
        return "0x3D: IMPROPER CAP DET MODE";
    case eAT_0x26_OFF_DISCHARGED_LOAD_CAP_DET_MODE:
        return "0x41: DISCHARGED LOAD CAP DET MODE";
    case eAT_0x2B_ON__FORCE:
        return "0x43: FORCE";
	case eAT_0x2C_OFF_FORCE_ERROR:
		return "0x44: FORCE ERROR";
	case eAT_0x2D_OFF_FORCE_PS_TOO_HIGH:
		return "0x45: FORCE PS TOO HIGH";
	case eAT_0x2E_OFF_FORCE_PS_TOO_LOW:
		return "0x46: FORCE PS TOO LOW";
	case eAT_0x2F_OFF_FORCE_DIS_PDU_FLAG_WAS_RAISE:
		return "0x47: FORCE DIS PDU FLAG WAS RAISE";
	case eAT_0x30_OFF_FORCE_DIS_COMMAND_WAS_REC:
		return "0x48: FORCE DIS COMMAND WAS REC";
	case eAT_0x31_OFF_FORCE_802_3AF_OVERLOAD:
		return "0x49: FORCE 802 3AF OVERLOAD";
	case eAT_0x32_OFF_FORCE_OUT_OF_PWR_BUDGET:
		return "0x43: FORCE OUT OF PWR BUDGET";
	case eAT_0x33_UNKNOWN_FORCE_COMMUNICATION_ERR:
		return "0x43: UNKNOWN FORCE COMMUNICATION ERR";
	case eAT_0x34_OFF_SHORT_CONDITION:
		return "0x43: SHORT CONDITION";
    case eAT_0x35_OFF_OVER_TEMP_AT_PORT:
        return "0x80: OVER TEMP AT PORT";
    case eAT_0x36_OFF_DEVICE_TOO_HOT:
        return "0x81: DEVICE TOO HOT";
    case eAT_0x37_OFF_UNKNOWN_DEVICE_PORT_STATUS:
        return "0x82: UNKNOWN DEVICE PORT STATUS";
    case eAT_0x38_OFF_FORCE_PWR_ERR_SHORT_CIRCUIT:
        return "0x83: FORCE PWR ERR SHORT CIRCUIT";
    case eAT_0x39_OFF_FORCE_PWR_ERR_CH_OVER_TEMP:
        return "0x84: FORCE PWR ERR CH OVER TEMP";
    case eAT_0x3A_OFF_FORCE_PWR_ERR_CHIP_OVER_TEMP:
        return "0x85: FORCE PWR ERR CHIP OVER TEMP";
    case eAT_0x3C_OFF_PWR_MANAGEMENT_STATIC:
        return "0x86: PWR MANAGEMENT STATIC";
    case eAT_0x3D_OFF_PWR_MANAGEMENT_STATIC_OV:
        return "0x87: PWR MANAGEMENT STATIC OV";
    case eAT_0x3E_OFF_FORCE_PWR_ERR_MNGMNT_STAT:
        return "0x88: FORCE PWR ERR MNGMNT STAT";
    case eAT_0x3F_OFF_FORCE_PWR_ERR_MNGMNT_STAT_OV:
        return "0x89: FORCE PWR ERR MNGMNT STAT OV";
    case eAT_0x40_ON__HIGH_POWER_PORT_IS_ON:
        return "0x90: HIGH POWER PORT IS ON";
    case eAT_0x41_OFF_CHIP_OVER_POWER:
        return "0x91: CHIP OVER POWER";
    case eAT_0x42_OFF_FORCE_PWR_ERR_CHIP_OVR_PWR:
        return "0xA0: FORCE PWR ERR CHIP OVR PWR";
    case eAT_0x43_OFF_CLASS_ERROR:
        return "0xA7: CLASS ERROR";
    case eAT_0x44_OFF_DURING_HOST_CRASH:
        return "0xA8: DURING HOST CRASH";
    case eAT_0x45_OFF_FROM_DELIVERED_TO_HOST_SHUTDOWN:
        return "0xA8: FROM DELIVERED TO HOST SHUTDOWN";
    case eAT_0x46_OFF_FROM_ENABLED_TO_HOST_SHUTDOWN:
        return "0xA8: FROM ENABLED TO HOST SHUTDOWN";
    case eAT_0x47_OFF_FORCE_POWER_CRASH_ERROR:
        return "0xA8: FORCE POWER CRASH ERROR";
    case eAT_0x48_OFF_RECOVERY_UDL:
        return "0xA8: RECOVERY UDL";
    case eAT_0x49_OFF_RECOVERY_PG_EVENT:
        return "0xA8: RECOVERY PG EVENT";
    case eAT_0x4A_OFF_RECOVERY_OVL:
        return "0xA8: RECOVERY OVL";
    case eAT_0x4B_OFF_RECOVERY_SC:
        return "0xA8: RECOVERY SC";
    case eAT_0x4C_OFF_RECOVERY_VOLTAGE_INJECTION:
        return "0xA8: RECOVERY VOLTAGE INJECTION";
    case eAT_0x4D_OFF_DVDT_FAIL_DURING_STARTUP:
        return "0xA8: DVDT FAIL DURING STARTUP";
    default:
        {
            return "?????";
        }
    }
}



mesa_rc meba_poe_pd69200_ctrl_port_status_get(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_port_status_t* const port_status)
{
    if (port_status == NULL)  {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s port_status is NULL pointer", __FUNCTION__);
        return MESA_RC_ERROR;
    }
    port_status->chip_state = meba_poe_pd69200_get_chipset(inst);

    if (port_status->chip_state == MEBA_POE_FIRMWARE_UPGRADE) {
        DEBUG(inst, MEBA_TRACE_LVL_NOISE, "%s Firmware upgrading", __FUNCTION__);
        port_status->assigned_pd_class_a = -1;
        port_status->assigned_pd_class_b = -1;
        port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_NOT_PERFORMED;
        port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_DISABLED;
        port_status->power_mw = 0;
        port_status->current_ma = 0;
        port_status->voltage_mv = 0;
        port_status->power_requested_mw = 0;
        return MESA_RC_OK;
    }

    if (port_status->chip_state != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Device not ready for reading", __FUNCTION__);
        return MESA_RC_ERROR;
    }

    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid handle=%d", __FUNCTION__, handle);
        return MESA_RC_ERR_PARM;
    }

    // not a poe port
    if (!(inst->port_map[handle].capabilities & MEBA_POE_PORT_CAP_POE))
    {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Not PoE port=%d", __FUNCTION__, handle);
        return MESA_RC_ERR_PARM;
    }

    // port < max poe ports
    if (handle >= inst->port_poe_length)
    {
        //DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_OK;
    }

    uint8_t enable;
    uint8_t port_state;
    uint8_t force_power_enable;
    uint8_t latch;
    uint8_t pd_class;
    uint8_t af_at_poh;
    uint8_t four_pair_enable;

    MESA_RC(meba_poe_pd69200_ctrl_get_single_port_status(
                inst,
                handle,
                &enable,
                &port_state,
                &force_power_enable,
                &latch,
                &pd_class,
                &af_at_poh,
                &four_pair_enable));

    port_status->assigned_pd_class_a = pd_class;
    port_status->assigned_pd_class_b = -1;

    if (port_status->poe_internal_port_status != port_state)
    {
        strncpy( port_status->poe_port_status_description , GetAT_TitleByPortsStatus(port_state), MAX_STR_SIZE-1);
    }

    port_status->poe_internal_port_status = port_state;

    // See table 4 in the user guide for understanding the conversion - we do not support all status values.
    port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_NOT_PERFORMED;


    switch (port_state)
    {
        // Port is already providing power
        case eAT_0x00_ON__LEGACY_PD_DET:
        case eAT_0x02_ON__802_4PAIR_DET:
        case eAT_0x03_ON__802_2PAIR_POWER_SEQUENCE:
        case eAT_0x04_ON__802_4PAIR_POWER_SEQUENCE:
        case eAT_0x40_ON__HIGH_POWER_PORT_IS_ON:    // high power port
        {
            port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_DELIVERING_POWER;
            port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_2P_LEGACY;
            break;
        }

        case eAT_0x01_ON__802_2PAIR_3AF_DET:              // LED is ON (delivering power)
        {
            port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_DELIVERING_POWER;
            port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_2P_IEEE;
            break;
        }

        case eAT_0x1A_OFF_USER_SETTING:
        case eAT_0x08_OFF_DIS_ALL_PORTS_PIN_ACT:
        {
           port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_DISABLED;
           break;
        }

        // Port was forced to ON
        case eAT_0x2B_ON__FORCE:
            {
                port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_TEST;
                break;
            }

        // Port is enabled, at the moment a valid PD device will be connected it will get power
        case eAT_0x11_OFF_PWR_UP_IN_PROCESS:            // should not happend since HC08 starts faster
        case eAT_0x1B_OFF_DET_IN_PROCESS:               // Port Status #27 ------------ NORMAL SITUATION --------
        case eAT_0x1E_OFF_UNDERLOAD_OR_CAP_TO_SMALL:    // Port Status #30
        case eAT_0x48_OFF_RECOVERY_UDL:
            {
                port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_SEARCHING;
                break;
            }

        // Port was FORCED to ON, and due to some error  it enter to TEST-ERROR state, or usual errors
        case eAT_0x1F_OFF_OVERLOAD_OR_CAP_TO_BIG:
        case eAT_0x25_OFF_IMPROPER_CAP_DET_MODE:
        case eAT_0x31_OFF_FORCE_802_3AF_OVERLOAD:
        case eAT_0x34_OFF_SHORT_CONDITION:
        case eAT_0x38_OFF_FORCE_PWR_ERR_SHORT_CIRCUIT:
        case eAT_0x4A_OFF_RECOVERY_OVL:
        case eAT_0x4B_OFF_RECOVERY_SC:
        {
            port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_FAULT;
            break;
        }

        // All other fault conditions
        case eAT_0x06_OFF_MAIN_PS_TO_HIGH:
        case eAT_0x07_OFF_MAIN_PS_TO_LOW:
        case eAT_0x09_OFF_DERATING_TEMPERATURE_HIGH:
        case eAT_0x0C_OFF_NON_EXIST_PORT_NUM:
        case eAT_0x12_OFF_INTERNAL_HW_FAULT:
        case eAT_0x1C_OFF_NON_802_3AF_PD:
        case eAT_0x1D_OFF_SUCCESION_OF_OVL_AND_UDL:
        case eAT_0x20_OFF_PWR_BUDGET_EXCEDDED:
        case eAT_0x21_OFF_INTERNAL_HW_ROUTING_ERROR:
        case eAT_0x24_OFF_EXT_VOLT_INJ_CAP_DET_MODE:
        case eAT_0x26_OFF_DISCHARGED_LOAD_CAP_DET_MODE:
        case eAT_0x2C_OFF_FORCE_ERROR:
        case eAT_0x2D_OFF_FORCE_PS_TOO_HIGH:
        case eAT_0x2E_OFF_FORCE_PS_TOO_LOW:
        case eAT_0x2F_OFF_FORCE_DIS_PDU_FLAG_WAS_RAISE:
        case eAT_0x30_OFF_FORCE_DIS_COMMAND_WAS_REC:
        case eAT_0x32_OFF_FORCE_OUT_OF_PWR_BUDGET:
        case eAT_0x33_UNKNOWN_FORCE_COMMUNICATION_ERR:
        case eAT_0x35_OFF_OVER_TEMP_AT_PORT:
        case eAT_0x36_OFF_DEVICE_TOO_HOT:
        case eAT_0x37_OFF_UNKNOWN_DEVICE_PORT_STATUS:
        case eAT_0x39_OFF_FORCE_PWR_ERR_CH_OVER_TEMP:
        case eAT_0x3A_OFF_FORCE_PWR_ERR_CHIP_OVER_TEMP:
        case eAT_0x3C_OFF_PWR_MANAGEMENT_STATIC:        // Port Status #60 - LED blinks at 2Hz rate
        case eAT_0x3D_OFF_PWR_MANAGEMENT_STATIC_OV:     // Port Status #61 - LED blinks at 2Hz rate
        case eAT_0x3E_OFF_FORCE_PWR_ERR_MNGMNT_STAT:    // Port Status #62 - LED blinks at 2Hz rate
        case eAT_0x3F_OFF_FORCE_PWR_ERR_MNGMNT_STAT_OV: // Port Status #63 - LED blinks at 2Hz rate
        case eAT_0x41_OFF_CHIP_OVER_POWER:
        case eAT_0x42_OFF_FORCE_PWR_ERR_CHIP_OVR_PWR:
        case eAT_0x43_OFF_CLASS_ERROR:
        case eAT_0x44_OFF_DURING_HOST_CRASH:
        case eAT_0x45_OFF_FROM_DELIVERED_TO_HOST_SHUTDOWN:
        case eAT_0x46_OFF_FROM_ENABLED_TO_HOST_SHUTDOWN:
        case eAT_0x47_OFF_FORCE_POWER_CRASH_ERROR:
        case eAT_0x49_OFF_RECOVERY_PG_EVENT:
        case eAT_0x4C_OFF_RECOVERY_VOLTAGE_INJECTION:
        case eAT_0x4D_OFF_DVDT_FAIL_DURING_STARTUP:
        {
            port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_OTHER_FAULT;
            break;
        }

        default:
        {
            // This shall never happen all states should be covered.
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Port %d: Unknown port state= 0x%X", inst->port_map[handle].port_no, port_state);
            port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_OTHER_FAULT;
            break;
        }
    }



   // See table 4 in the user guide for understanding the conversion - we do not support all status values.
    switch (port_state)
    {
        case eAT_0x00_ON__LEGACY_PD_DET:
        case eAT_0x01_ON__802_2PAIR_3AF_DET:
        case eAT_0x02_ON__802_4PAIR_DET:
        case eAT_0x03_ON__802_2PAIR_POWER_SEQUENCE:
        case eAT_0x04_ON__802_4PAIR_POWER_SEQUENCE:
        case eAT_0x2B_ON__FORCE:
        case eAT_0x40_ON__HIGH_POWER_PORT_IS_ON:
        {
            // Note: MEBA_POE_PD_ON_POEBT doesent mapped in AT mode
            port_status->meba_poe_port_state = MEBA_POE_PD_ON;
            break;
        }

        case eAT_0x08_OFF_DIS_ALL_PORTS_PIN_ACT:
        case eAT_0x1A_OFF_USER_SETTING:
        {
            port_status->meba_poe_port_state = MEBA_POE_DISABLED;
            break;
        }

        // typical value when nothing is connected to the port
        // Port is enabled, at the moment a valid PD device will be connected it will get power
        case eAT_0x11_OFF_PWR_UP_IN_PROCESS:            // should not happend if PoE code starts faster
        case eAT_0x1B_OFF_DET_IN_PROCESS:               // NORMAL SITUATION
        case eAT_0x1E_OFF_UNDERLOAD_OR_CAP_TO_SMALL:
        case eAT_0x48_OFF_RECOVERY_UDL:
        {
            port_status->meba_poe_port_state = MEBA_POE_NO_PD_DETECTED;
            break;
        }

        case eAT_0x1F_OFF_OVERLOAD_OR_CAP_TO_BIG:
        case eAT_0x31_OFF_FORCE_802_3AF_OVERLOAD:
        case eAT_0x4A_OFF_RECOVERY_OVL:
        {
            port_status->meba_poe_port_state = MEBA_POE_PD_OVERLOAD;
            break;
        }

        case eAT_0x20_OFF_PWR_BUDGET_EXCEDDED:
        {
            port_status->meba_poe_port_state = MEBA_POE_POWER_BUDGET_EXCEEDED;
            break;
        }

        // Port is off due to PD reasones
        case eAT_0x1C_OFF_NON_802_3AF_PD:
        case eAT_0x1D_OFF_SUCCESION_OF_OVL_AND_UDL:
        case eAT_0x25_OFF_IMPROPER_CAP_DET_MODE:
        case eAT_0x26_OFF_DISCHARGED_LOAD_CAP_DET_MODE:
        case eAT_0x34_OFF_SHORT_CONDITION:
        case eAT_0x38_OFF_FORCE_PWR_ERR_SHORT_CIRCUIT:
        case eAT_0x4B_OFF_RECOVERY_SC:
        case eAT_0x4D_OFF_DVDT_FAIL_DURING_STARTUP:
        {
            port_status->meba_poe_port_state = MEBA_POE_PD_FAULT;  // PD fault
            break;
        }

        // Port is off due to PSE reasones
        case eAT_0x06_OFF_MAIN_PS_TO_HIGH:
        case eAT_0x07_OFF_MAIN_PS_TO_LOW:
        case eAT_0x09_OFF_DERATING_TEMPERATURE_HIGH:
        case eAT_0x0C_OFF_NON_EXIST_PORT_NUM:
        case eAT_0x12_OFF_INTERNAL_HW_FAULT:
        case eAT_0x21_OFF_INTERNAL_HW_ROUTING_ERROR:
        case eAT_0x24_OFF_EXT_VOLT_INJ_CAP_DET_MODE:
        case eAT_0x2C_OFF_FORCE_ERROR:
        case eAT_0x2D_OFF_FORCE_PS_TOO_HIGH:
        case eAT_0x2E_OFF_FORCE_PS_TOO_LOW:
        case eAT_0x2F_OFF_FORCE_DIS_PDU_FLAG_WAS_RAISE:
        case eAT_0x30_OFF_FORCE_DIS_COMMAND_WAS_REC:
        case eAT_0x32_OFF_FORCE_OUT_OF_PWR_BUDGET:
        case eAT_0x33_UNKNOWN_FORCE_COMMUNICATION_ERR:
        case eAT_0x35_OFF_OVER_TEMP_AT_PORT:
        case eAT_0x36_OFF_DEVICE_TOO_HOT:
        case eAT_0x37_OFF_UNKNOWN_DEVICE_PORT_STATUS:
        case eAT_0x39_OFF_FORCE_PWR_ERR_CH_OVER_TEMP:
        case eAT_0x3A_OFF_FORCE_PWR_ERR_CHIP_OVER_TEMP:
        case eAT_0x3C_OFF_PWR_MANAGEMENT_STATIC:
        case eAT_0x3D_OFF_PWR_MANAGEMENT_STATIC_OV:
        case eAT_0x3E_OFF_FORCE_PWR_ERR_MNGMNT_STAT:
        case eAT_0x3F_OFF_FORCE_PWR_ERR_MNGMNT_STAT_OV:
        case eAT_0x41_OFF_CHIP_OVER_POWER:
        case eAT_0x42_OFF_FORCE_PWR_ERR_CHIP_OVR_PWR:
        case eAT_0x43_OFF_CLASS_ERROR:
        case eAT_0x44_OFF_DURING_HOST_CRASH:
        case eAT_0x45_OFF_FROM_DELIVERED_TO_HOST_SHUTDOWN:
        case eAT_0x46_OFF_FROM_ENABLED_TO_HOST_SHUTDOWN:
        case eAT_0x47_OFF_FORCE_POWER_CRASH_ERROR:
        case eAT_0x49_OFF_RECOVERY_PG_EVENT:
        case eAT_0x4C_OFF_RECOVERY_VOLTAGE_INJECTION:
        {
            port_status->meba_poe_port_state = MEBA_POE_PSE_FAULT;
            break;
        }

        default:
        {
            // statuses to be mapped on higher software level:
            // MEBA_POE_NOT_SUPPORTED
            // MEBA_POE_UNKNOWN_STATE
            // MEBA_POE_DISABLED_INTERFACE_SHUTDOWN

            // This shall never happen all states should be covered.
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Port %d: Unknown port state= 0x%X",
                  inst->port_map[handle].port_no, port_state);
            port_status->meba_poe_port_state = MEBA_POE_UNKNOWN_STATE;
            break;
        }
    }

    if(( port_status->poe_internal_port_status == eAT_0x1C_OFF_NON_802_3AF_PD)
    || ( port_status->poe_internal_port_status == eAT_0x1E_OFF_UNDERLOAD_OR_CAP_TO_SMALL)
	|| ( port_status->poe_internal_port_status == eAT_0x25_OFF_IMPROPER_CAP_DET_MODE))
        port_status->is_fault_link_without_power = true;
    else
        port_status->is_fault_link_without_power = false;

    uint16_t ppl = 0;
    uint16_t tppl = 0;
    meba_poe_pd69200_ctrl_get_port_power_limit(inst, handle, &ppl, &tppl);
    port_status->power_requested_mw = tppl;

    uint16_t main_voltage = 0;
    uint16_t calculated_current = 0;
    uint16_t port_power_consumption = 0;
    uint16_t port_voltage = 0;

    uint8_t port_type_af_at_poh = 0;
    if (port_status->meba_poe_ieee_port_state == MEBA_POE_IEEE_PORT_STATE_DELIVERING_POWER)
    {
        meba_poe_pd69200_ctrl_port_measurements_get(
            inst,
            handle,
            &main_voltage,
            &calculated_current,
            &port_power_consumption,
            &port_voltage);
    }

    meba_poe_pd69200_ctrl_port_4Pair_Port_Parameters_get(
    inst,
    handle,
    &port_type_af_at_poh);

    uint16_t pse_allocated_power;
    uint16_t pd_requested_power;
    uint8_t  pse_power_type;
    uint8_t  power_class;
    uint8_t  pse_power_pair;
    uint8_t  mdi_power_status;
    uint8_t  cable_len;
    uint8_t  power_reserve_mode_active;
    uint8_t  layer2_request_pending;
    uint8_t  port_delivering_power_type;
    uint16_t port_power_consumption_dw;

    MESA_RC(meba_poe_pd69200_ctrl_get_port_layer2_lldp_pse_data(
                inst,
                handle,
                &pse_allocated_power,
                &pd_requested_power,
                &pse_power_type,
                &power_class,
                &pse_power_pair,
                &mdi_power_status,
                &cable_len,
                &power_reserve_mode_active,
                &layer2_request_pending,
                &port_delivering_power_type,
                &port_power_consumption_dw
                ));

    port_status->pse_data.pse_allocated_power_mw = pse_allocated_power;
    port_status->pse_data.pd_requested_power_mw  = pd_requested_power;
    port_status->pse_data.pse_power_type         = pse_power_type;
    port_status->pse_data.power_class            = power_class;
    port_status->pse_data.cable_len              = cable_len;
    port_status->pse_data.pse_power_pair         = pse_power_pair;
    port_status->pse_data.port_type_af_at_poh    = port_type_af_at_poh;

    port_status->power_mw = port_power_consumption;
    port_status->current_ma = calculated_current;
    port_status->voltage_mv = port_voltage * 100;

    //    power_indicator & 0x2000)
    //10 = Port is delivering power configured by CDP.
    //11 = Port is delivering power configured by LLDP or Port delivers power at reserve mode.
    if ((port_delivering_power_type == 2) || (port_delivering_power_type == 3)) {
        port_status->reserved_power_mw = port_status->power_requested_mw;
    } else {
        port_status->reserved_power_mw = port_status->power_mw;
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "CH=%d ,UNG status=%d ,int status=0x%X" ,handle ,port_status->meba_poe_port_state ,port_status->poe_internal_port_status);

    return MESA_RC_OK;
}



// utility functions
#define ALIGN_RESPONSE       "        "
#define POEBT_TITLE          "\n\r[POE ]" // Used for CLI printout header portion
#define POEBT_SYSLOG_HEADER  "[PoE]:"     // used as the left portion in PoE-BT syslog message. For example: [PoE-BT]: Port #00 status changed to 'Fault' (int code=0x25)


// Report key - See section 4.6 in the user guide
// expected_seq_num - The expected sequence number for the report
static mesa_bool_t check_report_key_ok(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t* rx_buf,
    uint8_t expected_seq_num,
    char* msg)
{
    //mesa_rc rc;
    mesa_bool_t report_key_ok_v = true;

    // First make sure that the checksum is correct
    if (pd69200_check_sum_ok(&rx_buf[0])) {
        if (rx_buf[0] != REPORT_KEY) {
            sprintf(msg ,"%sReport key error, rx0=%2X , REPORT_KEY=%2X \n\r",ALIGN_RESPONSE, rx_buf[0], REPORT_KEY);
            report_key_ok_v = false;
        } else if (rx_buf[2] == 0x00 && rx_buf[3] == 0x00) {
            sprintf(msg ,"%sCommand received/correctly executed \n\r", ALIGN_RESPONSE);
            report_key_ok_v = true;
        } else if  (rx_buf[2] == 0xFF && rx_buf[3] == 0xFF && rx_buf[4] == 0xFF && rx_buf[5] == 0xFF) {
            sprintf(msg ,"%sCommand Received/Wrong Checksum \n\r",ALIGN_RESPONSE);
            report_key_ok_v = false;
        } else if  (rx_buf[2] > 0x0  && rx_buf[3] < 0x80) {
            sprintf(msg ,"%sFailed Execution/Conflict in Subject Bytes\n\r",ALIGN_RESPONSE);
            report_key_ok_v = false;
        } else if  (rx_buf[2] > 0x80  && rx_buf[3] < 0x90) {
            sprintf(msg ,"%sFailed Execution/Wrong Data Byte Value \n\r",ALIGN_RESPONSE);
            report_key_ok_v = false;
        } else if  (rx_buf[2] == 0xFF  && rx_buf[3] == 0xFF) {
            sprintf(msg ,"%sFailed Execution/Undefined Key Value \n\r",ALIGN_RESPONSE);
            report_key_ok_v = false;
        } else {
            sprintf(msg ,"%sUndefined revieved Value: rx2:%2X , rx3:%2X \n\r",ALIGN_RESPONSE, rx_buf[2], rx_buf[3]);
            report_key_ok_v = true;
        }
    } else {sprintf(msg ,"%sCalculated checksum error \n\r",ALIGN_RESPONSE);
        report_key_ok_v = false;
    }

    return report_key_ok_v;
}



// Function that reads controller response ( reponds upon request ), and check the key and checksum.
// Returns false in case of error else true.
static mesa_rc check_controller_response(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t* rx_buf,
    uint8_t expected_seq_num,
    char* msg)
{
    //mesa_rc rc;

    // Check checksum
    if (!pd69200_check_sum_ok(rx_buf)) {
        char dbg_txt[PD_BUFFER_SIZE * 4];
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Invalid checksum: %s\n",  __FUNCTION__,
              print_as_hex_string(rx_buf, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));

        sprintf(msg ,"%sTelemetry: Rx message checksum test failed \n\r", ALIGN_RESPONSE);
        return MESA_RC_ERROR;
    }

    if  (rx_buf[0] != TELEMETRY_KEY) {
        char dbg_txt[PD_BUFFER_SIZE * 4];
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Invalid key (%d): %s\n",
              __FUNCTION__, rx_buf[0],
              print_as_hex_string(rx_buf, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));

        sprintf(msg ,"%sTelemetry: Invalid key rx0:%2X \n\r", ALIGN_RESPONSE , rx_buf[0]);
        return MESA_RC_ERROR;
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG ,"%sTelemetry succeed \n\r", ALIGN_RESPONSE);
    return MESA_RC_OK;
}


mesa_rc Check_reply_validation_debug(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t* tx_buf,
    uint8_t* rx_buf,
    char* msg)
{
    mesa_rc rc = MESA_RC_ERROR;

    // check report key
	if (((tx_buf[0] == COMMAND_KEY || tx_buf[0] == PROGRAM_KEY)) &&
        ( rx_buf[0] != REPORT_KEY ))
    {
        DEBUG(inst, MEBA_TRACE_LVL_WARNING, "%s COMMAND_KEY or PROGRAM_KEY should be answered with REPORT_KEY \n",  __FUNCTION__);
    }
    else if ((tx_buf[0] == REQUEST_KEY) &&
             ((rx_buf[0] != TELEMETRY_KEY ) && ( rx_buf[0] != REPORT_KEY )))
    {
        DEBUG(inst, MEBA_TRACE_LVL_WARNING, "%s REQUEST_KEY should be answered with TELEMETRY_KEY or REPORT_KEY \n",  __FUNCTION__);
    }

    // Section 4.6 in PD69200/G user guide - check report in case of command or program

    if (rx_buf[0] == REPORT_KEY)  // check report message
    {
        if (check_report_key_ok(inst, rx_buf , tx_buf[1], msg) )
        {
            rc = MESA_RC_OK;
        }
        else
        {
            //DEBUG(inst, MEBA_TRACE_LVL_WARNING, "%s failed\n",  __FUNCTION__);
        }
    }
    else if (rx_buf[0] == TELEMETRY_KEY) // check telemetry message
    {
        rc = check_controller_response(inst, rx_buf, tx_buf[1], msg);
    }
    else
    {
        //DEBUG(inst, MEBA_TRACE_LVL_WARNING, "%s Unknown RX message KEY: %2X \n",  __FUNCTION__ , rx_buf[0]);
    }

    return rc;
}

#include<ctype.h>
mesa_bool_t IsValidHexString(char *chars)
{
    int len = strlen(chars);

    for (int i=0;i<len;i++)
    {
        char c = chars[i];
        if (!isxdigit(c) && (c != ' '))
            return false;
    }
    return true;
}


void to_upper(char *s)
{
    for (int i = 0; s[i]!='\0'; i++)
    {
        if(s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = s[i] -32;
        }
    }
}


typedef enum
{
    eValidNum_InValid = 0,
    eValidNum_Decimal,
    eValidNum_Hex
}ValidNum_e;


// check whether the argument is: decimal , hexadeciml or not valid number
ValidNum_e checkArgument(char* s)
{
    // Size of string
    int n = strlen(s);

    ValidNum_e eValidNum = eValidNum_InValid;

    // Iterate over string
    for(int i = 0; i < n; i++)
    {
        char ch = s[i];

        if ((ch >= '0') && (ch <= '9'))
        {
            if (eValidNum == eValidNum_InValid)
            {
                eValidNum = eValidNum_Decimal;
            }
        }
        else if (((ch >= 'a') && (ch <= 'f')) ||
                 ((ch >= 'A') && (ch <= 'F')))
        {
             eValidNum = eValidNum_Hex;
        }
        else // if argument is not decimal and not hex - declare as invalid argument
        {
             return eValidNum_InValid;
        }
    }

    return eValidNum;
}



//* Hexadecimal number format:  0x22 , 0X22 , 0xFF ,0x00  - range: <0-0xFF>
//* Decimal number format:      223  , 46   , 255  , 0    - range: <0-255>
//
// there are 3 types of debug messages:
//
// 1.     debug poe pd69xxx access [iport <uint>] 0xXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  - 15bytes Hex with checksum
//   ex1: debug poe pd69xxx access iport 0 0x0200071E214E4E4E4E4E4E4E4E02B8
//   ex2: debug poe pd69xxx access 0x0200071E214E4E4E4E4E4E4E4E02B8
//
// 2.     debug poe pd69xxx access [iport <uint>] 0xXXXXXXXXXXXXXXXXXXXXXXXXXX  - 13bytes Hex without checksum
//   ex1: debug poe pd69xxx access iport 0 0x0200071E214E4E4E4E4E4E4E4E
//   ex2: debug poe pd69xxx access 0x0200071E214E4E4E4E4E4E4E4E
//
// 3.   Num - is any valid Decimal <0-255> or Hexadecimal <0x0-0xFF> number
//      debug poe pd69xxx access [iport <uint>] <Num> <Num> <Num> <Num> <Num> [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>]
//   ex1: debug poe pd69xxx access 0x02 0 0x07 0x1E 0x21 0x4
//
mesa_rc meba_poe_pd69200_ctrl_debug(
    const meba_poe_ctrl_inst_t* const inst,
    char     *var ,
    uint32_t str_len ,
    char* title ,
    char* tx_str ,
    char* rx_str ,
    char* msg,
    int max_msg_buf_size)
{
    mesa_rc rc = MESA_RC_OK;

    unsigned int args_buf[PD_BUFFER_SIZE];
    uint8_t      tx_buf[PD_BUFFER_SIZE];
    uint8_t      rx_buf[PD_BUFFER_SIZE];

    mesa_bool_t bUpdate_echo = FALSE;
    mesa_bool_t bUpdate_check_cum = FALSE;

    int args_count = 1, i = 0;

    // check input string validation
    if ((var == NULL) || (str_len < 8)) {
        strncpy(msg ,"  Error: Missing protocol arguments \n\r" ,max_msg_buf_size);
        return MESA_RC_ERROR;
    }

    // for easy string operations - make string upper case
    to_upper(var);

    // copy input arguments string to local char*
    char str_args[str_len+1];
    strncpy( str_args, var, str_len);
    str_args[str_len] = 0;

    // count the number of arguments inside argument string
    for (i = 0;str_args[i] != '\0';i++)
    {
        if (str_args[i] == ' ' && str_args[i+1] != ' ')
            args_count++;
    }

    // 0x0200071E214E4E4E4E4E4E4E4E02B8  - 15bytes with checksum
    // 0x0200071E214E4E4E4E4E4E4E4E      - 13bytes without checksum
    if (((str_len == 28) || (str_len == 32)) // 2 * 14 or 2 * 16
        && (args_count == 1)) // 13 or 15 bytes
    {
        // string must begin with 0x or 0X
        char *ret = strstr(str_args, "0X");
        if (ret != str_args)
        {
            strncpy(msg ,"  Error: string must begin with 0x or 0X \n\r" ,max_msg_buf_size);
            return MESA_RC_ERROR;
        }

        // skip the 0x (or 0X)
        char   *pStrTmp = str_args + 2;
        uint32_t args_str_len =  str_len - 2;

        // check if entered chars are valid hex or decimal number or space
        if(!IsValidHexString(pStrTmp))
        {
            strncpy(msg ,"  Arguments string is not valid Hex or Dec number \n\r" ,max_msg_buf_size);
            return MESA_RC_ERROR;
        }

        for (i = 0;pStrTmp[i] != '\0';i++)
        {
            if ((pStrTmp[i] == ' ') && (pStrTmp[i+1] != ' '))
                args_count++;
        }

        // extract arguments from string
        for (int i = 0; i < (args_str_len / 2); i++)
        {
            sscanf(pStrTmp + (2*i), "%02x", &args_buf[i]);
            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "args_buf %d: %02X", i, args_buf[i]);
        }

        // copy args to tx buffer
        for (int i=0;i<15;i++)
        {
            tx_buf[i] = (uint8_t)args_buf[i];
        }

        // adding ECHO
        if(tx_buf[1] == 0xFF)
        {
            bUpdate_echo = TRUE;
        }

        // Update checksum
        if(str_len == 28)
        {
           bUpdate_check_cum = TRUE;
        }
    }
    // <Num> <Num> <Num> <Num> <Num> [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>] [<Num>]
    else if ((args_count >= 5) && (args_count <= 15))
    {
        // skip the 0x
        char   *s = str_args;

        int i=0;

        //check validation of all string argumnets.
        for (char *p_arg = strtok(s," "); p_arg != NULL; p_arg = strtok(NULL, " "))
        {
            // check if argument conatains lower case: 0x
            char *p = strstr (p_arg,"0X");

            if (!p) // if argument doesn't includ the '0x' it will be considered as decimal number
            {
                ValidNum_e eValidNum = checkArgument(p_arg);
                if (eValidNum != eValidNum_Decimal)
                {
                    sprintf(msg ,"  Error: argument #%d: %s is not a decimal number \n\r" ,i+1 ,p_arg);
                    return MESA_RC_ERROR;
                }

                int dec_val = atoi(p_arg);

                if (dec_val > 0xFF)
                {
                    sprintf(msg ,"  Error: argument #%d: %s value is out of range (0xFF) \n\r" ,i+1 ,p_arg);
                    return MESA_RC_ERROR;
                }

                args_buf[i] = dec_val;
            }
            else // Hex
            {
                // can be  0x2D  0x22
                ValidNum_e eValidNum = checkArgument(p + 2);  // skip the 0x
                if ((eValidNum != eValidNum_Hex) && (eValidNum != eValidNum_Decimal))
                {
                    sprintf(msg ,"  Error: argument #%d: %s is not a hexadecimal number \n\r" ,i+1 , p_arg);
                    return MESA_RC_ERROR;
                }

                int dec_val;

                sscanf(p, "%X", &dec_val);

                args_buf[i] = dec_val;

                if (dec_val > 0xFF)
                {
                    sprintf(msg ,"  Error: argument #%d: %s value is out of range (0xFF) \n\r" ,i+1 ,p);
                    return MESA_RC_ERROR;
                }
            }

            i++;
        }

        // pad all remained 15bytes with value '0x4E'
        for (i = args_count; i < 13 ; i++)
        {
            args_buf[i] = 0x4E;
        }

        // copy all data to tx buffer
        for (int i=0 ; i<15 ; i++)
        {
            tx_buf[i] = (uint8_t)args_buf[i];
        }

        // adding ECHO
        if(tx_buf[1] == 0xFF)
        {
            bUpdate_echo = TRUE;
        }

        // Update checksum
        if (args_count < 15)
        {
           bUpdate_check_cum = TRUE;
        }

        //sprintf(msg ,"\n\rstr: %s: args_count:%d , str_len:%d \n\r", s, args_count , str_len);
    }
    else
    {
        sprintf(msg ,"    Invalid 15 bytes arguments !!! str len:%d , #args:%d \n\r", str_len, args_count);
        return MESA_RC_ERROR;
    }

    // update ECHO
    if (bUpdate_echo)
    {
        tx_buf[1] = get_seq_num(false);
    }

    // update checksum
    if (bUpdate_check_cum)
    {
        pd69200_update_check_sum(tx_buf);
    }

    sprintf(title ,"              -ky-ec-s1-s2-s3-d0-d1-d2-d3-d4-d5-d6-d7-c1-c2-");

    int iBufIndex = 15;
    sprintf(tx_str ,"        TX   : ");

    for (int i=0 ; ((i < PD_BUFFER_SIZE) && ((iBufIndex+3) < max_msg_buf_size)) ; i++)
    {
        sprintf(&(tx_str[iBufIndex]), "%02X ", tx_buf[i]);
        iBufIndex += 3;
    }

    MESA_RC(pd69200_wr(inst, tx_buf, PD_BUFFER_SIZE, "debug"));

    // Ok - Tx went well.
    // Get response -- Check that response is valid

    VTSS_MSLEEP(100);

    if (pd69200_rd(inst, rx_buf, PD_BUFFER_SIZE) == MESA_RC_OK)
    {
        iBufIndex = 15;
        //print_buffer(&rx_buf[0], PD_BUFFER_SIZE, __LINE__, trace);
        sprintf(rx_str ,"        RX   : ");
        for (int i = 0 ; ((i < PD_BUFFER_SIZE) && ((iBufIndex+3) < max_msg_buf_size)) ; i++)
        {
            sprintf(&(rx_str[iBufIndex]), "%02X ", rx_buf[i]);
            iBufIndex += 3;
        }

        rc = Check_reply_validation_debug(inst , tx_buf , rx_buf, msg);
    }
    else
    {
        sprintf(msg ,"%s Could not get 15bytes data from PoE MCU.", POEBT_TITLE);
        //T_WG_PORT(VTSS_TRACE_POEBT_GRP_CUSTOM, port_index, "%s", "Could not read response.");

        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s , Invalid response\n", __FUNCTION__ );
    }

    return rc;
}



mesa_rc meba_poe_pd69200_ctrl_port_capabilities_get(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_port_cap_t             *capabilities)
{
//    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
//        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Device not ready for reading", __FUNCTION__);
//        return MESA_RC_ERROR;
//    }

    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid handle: %d", __FUNCTION__, handle);
        return MESA_RC_ERR_PARM;
    }

    *capabilities = inst->port_map[handle].capabilities;
    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_firmware_upgrade(
    const meba_poe_ctrl_inst_t* const inst,
    mesa_bool_t                     reset,
    uint32_t                        size,
    const char* data)
{
    return meba_poe_pd69200_firmware_upgrade(inst, reset, size, data);
}

mesa_rc meba_poe_pd69200_ctrl_prepare_firmware_upgrade(
    const meba_poe_ctrl_inst_t* const inst,
    mesa_bool_t                     version_check,
    uint32_t                        size,
    const char                      *data)
{
    return meba_poe_pd69200_prepare_firmware_upgrade(inst, version_check, size, data);
}

mesa_rc meba_poe_pd69200_ctrl_port_pd_data_set(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_data_t* pd_data)
{
    uint8_t type = 0, source = 0, prio = 0;
    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_ERROR;
    }

    switch (pd_data->type) {
        case MEBA_POE_PORT_PD_POWER_TYPE2_PSE:
            type = 0;
            break;
        case MEBA_POE_PORT_PD_POWER_TYPE2_PD:
            type = 1;
            break;
        case MEBA_POE_PORT_PD_POWER_TYPE1_PSE:
            type = 2;
            break;
        case MEBA_POE_PORT_PD_POWER_TYPE1_PD:
            type = 3;
            break;
        default:
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid type parameter %d", __FUNCTION__, pd_data->type);
            return MESA_RC_ERR_PARM;
    }

    switch (pd_data->source) {
        case MEBA_POE_PORT_PD_PD_POWER_SOURCE_UNKNOWN:
        case MEBA_POE_PORT_PD_PSE_POWER_SOURCE_UNKNOWN:
            source = 0;
            break;
        case MEBA_POE_PORT_PD_PD_POWER_SOURCE_PSE:
        case MEBA_POE_PORT_PD_PSE_POWER_SOURCE_PRIMARY:
            source = 1;
            break;
        case MEBA_POE_PORT_PD_PD_POWER_SOURCE_RESERVED:
        case MEBA_POE_PORT_PD_PSE_POWER_SOURCE_BACKUP:
            source = 2;
            break;
        case MEBA_POE_PORT_PD_PD_POWER_SOURCE_PSE_LOCAL:
        case MEBA_POE_PORT_PD_PSE_POWER_SOURCE_RESERVED:
            source = 3;
            break;
        default:
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid source parameter %d", __FUNCTION__, pd_data->source);
            return MESA_RC_ERR_PARM;
    }

    switch (pd_data->prio) {
        case MEBA_POE_PORT_PD_POWER_PRIORITY_UNKNOWN:
            prio = 0;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_CRITICAL:
            prio = 1;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_HIGH:
            prio = 2;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_LOW:
            prio = 3;
            break;
        default:
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid prio parameter %d", __FUNCTION__, pd_data->prio);
            return MESA_RC_ERR_PARM;
    }

    return meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(
        inst,
        handle,
        type << 6 | source << 4 | prio,
        pd_data->pd_requested_power_mw  / 100, // convert from milliwatt to deciwatt
        pd_data->pse_allocated_power_mw / 100, // convert from milliwatt to deciwatt
        100,                                   // always set to 100 meters
        1);
}

mesa_rc meba_poe_pd69200_ctrl_port_pd_data_clear(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t          handle)
{
    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_ERROR;
    }

    meba_poe_port_cfg_t* port_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.ports[handle]);

    uint8_t pd69200_prio = 3; // Default to low priority

    // Type conversion -- See section 4.5.16 in PD69200 user guide
    switch (port_cfg->priority) {
        case MEBA_POE_PORT_PD_POWER_PRIORITY_LOW :
            pd69200_prio = 3;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_HIGH:
            pd69200_prio = 2;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_CRITICAL:
            pd69200_prio = 1;
            break;
        default:
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Unknown priority: %d\n",  __FUNCTION__, port_cfg->priority);
    }

    return meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(
        inst, handle, pd69200_prio, 0, 0, 0, 3);
}

mesa_rc meba_poe_pd69200_ctrl_port_pd_bt_data_set(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_bt_data_t* pd_data)
{
    return MESA_RC_OK;
}




void meba_pd69200_driver_init(
    meba_poe_ctrl_inst_t* inst,
    char const* adapter_name,
    int                         adapter_fd,
    meba_poe_ctrl_cap_t         capabilities,
    meba_poe_port_properties_t  *port_map,
    uint32_t                    port_map_length,
    meba_poe_psu_input_prob_t   *psu_map,
    uint32_t                    psu_map_length,
    meba_debug_t                debug,       //  Board debug output
    meba_poe_parameters_t       tMeba_poe_parameters)
{
    int i;
    if (adapter_fd <= 0) {

        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Invalid file handle (%d)",
              adapter_name,
              adapter_fd);
    }

    static meba_poe_ctrl_api_t meba_pd69200_api = {
        .meba_poe_ctrl_do_detection             = meba_poe_pd69200_do_detection,
        .meba_poe_ctrl_chip_initialization      = meba_poe_pd69200_chip_initialization,
        .meba_poe_ctrl_sync                     = meba_poe_pd69200_sync,
        .meba_poe_ctrl_reset_command            = meba_poe_pd69200_ctrl_reset_command,
        .meba_poe_ctrl_save_command             = meba_poe_pd69200_ctrl_save_command,
        .meba_poe_ctrl_version_get              = meba_poe_pd69200_ctrl_version_get,
        .meba_poe_ctrl_port_cfg_set             = meba_poe_pd69200_ctrl_port_cfg_set,
        .meba_poe_ctrl_port_status_get          = meba_poe_pd69200_ctrl_port_status_get,
        .meba_poe_ctrl_cfg_set                  = meba_poe_pd69200_ctrl_globals_cfg_set,
        .meba_poe_ctrl_status_get               = meba_poe_pd69200_ctrl_globals_status_get,
        .meba_poe_ctrl_debug                    = meba_poe_pd69200_ctrl_debug,
        .meba_poe_ctrl_firmware_upgrade         = meba_poe_pd69200_ctrl_firmware_upgrade,
        .meba_poe_ctrl_prepare_firmware_upgrade = meba_poe_pd69200_ctrl_prepare_firmware_upgrade,
        .meba_poe_ctrl_port_capabilities_get    = meba_poe_pd69200_ctrl_port_capabilities_get,
        .meba_poe_ctrl_port_pd_bt_data_set      = meba_poe_pd69200_ctrl_port_pd_bt_data_set,
        .meba_poe_ctrl_port_pd_data_set         = meba_poe_pd69200_ctrl_port_pd_data_set,
        .meba_poe_ctrl_port_pd_data_clear       = meba_poe_pd69200_ctrl_port_pd_data_clear,
    };

    poe_driver_private_t* private_data = malloc(sizeof(poe_driver_private_t));
    memset(private_data, 0, sizeof(poe_driver_private_t));

    private_data->is_bt = false;
    private_data->debug = debug;
    private_data->tPoE_parameters = tMeba_poe_parameters;
    private_data->cfg.ports = malloc(sizeof(meba_poe_port_cfg_t) * port_map_length);
    private_data->cfg_POEMCU.ports = malloc(sizeof(meba_poe_port_cfg_t) * port_map_length);
    private_data->status.ports = malloc(sizeof(meba_poe_port_private_status_t) * port_map_length);

    memset(private_data->cfg.ports        ,0 ,sizeof(*(private_data->cfg.ports)));
    memset(private_data->cfg_POEMCU.ports ,0 ,sizeof(*(private_data->cfg_POEMCU.ports)));
    memset(private_data->status.ports     ,0 ,sizeof(*(private_data->status.ports)));

    private_data->status.global.chip_state = MEBA_POE_CHIPSET_DETECTION;

    for (i = 0; i < port_map_length; ++i) {
        private_data->cfg.ports[i].cable_length = 255;
    }

    private_data->cfg.global.primary_max_power_w = tMeba_poe_parameters.poe_init_params.PwrSupply_MaxPwr;; // Make sure initial value is different from configured value as configuration only is applied when values are different.
    inst->api = &meba_pd69200_api;
    inst->private_data = private_data;
    inst->adapter_name = adapter_name;
    inst->adapter_fd = adapter_fd;
    inst->capabilities = capabilities;
    inst->port_poe_length = tMeba_poe_parameters.poe_init_params.Max_POE_Ch;
    inst->port_map = port_map;
    inst->port_map_length = port_map_length;
    inst->psu_map = psu_map;
    inst->psu_map_length = psu_map_length;
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Done", __FUNCTION__);

    //POE_MAX_LOGICAL_PORTS = (inst->port_map_length / 8) * 8;
    //POE_MAX_LOGICAL_PORTS += (inst->port_map_length % 8) ? 8 : 0;

    //DEBUG(inst, MEBA_TRACE_LVL_INFO, "POE MAX LOGICAL PORTS: %d", POE_MAX_LOGICAL_PORTS);

    return;
}



// PoE BT driver


mesa_rc meba_poe_pd69200_ctrl_port_dummy_method(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pse_data_t* pse_data)
{
    return MESA_RC_OK;
}


static
mesa_rc meba_poe_pd69200bt_ctrl_set_BT_port_parameters(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                     channel,
    uint8_t                     cfg1,
    uint8_t                     cfg2,
    uint8_t                     operation_mode,
    uint8_t                     add_power_for_port_mode,
    uint8_t                     priority)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_CONFIG1_KEY,
        channel,
        cfg1,
        cfg2,
        operation_mode,
        add_power_for_port_mode,
        priority,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "SET BT PORT PARAMETERS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,CFG1=%d ,CFG2=%d ,operation mode=0x%X ,add_power=%d ,priority=%d",
          fname,
          channel,
          cfg1,
          cfg2,
          operation_mode,
          add_power_for_port_mode,
          priority);

    return MESA_RC_OK;

}



static
mesa_rc meba_poe_pd69200bt_ctrl_get_BT_port_parameters(
    const meba_poe_ctrl_inst_t  *const inst,
    uint8_t                     handle,
    meba_poe_port_cfg_t         *cfg_POEMCU)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_CONFIG1_KEY,
        handle,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET_BT_PORT_PARAM";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    //    cfg_POEMCU->Port_Status                = buf[2] ;
    cfg_POEMCU->enable                     = ((buf[3] & 0xF) > 0) ? 1 : 0;   //bits[3..0] ? values 1,2
    cfg_POEMCU->ignored_inrush_check       = ((buf[3] & 0xF) == 2) ? 1 : 0;  //bits[3..0] ? value 2
    cfg_POEMCU->ignore_pd_auto_class_request = ((buf[3] >> 4) & 1);  //bit[4]

    cfg_POEMCU->bt_port_pm_mode            = buf[4] & 0xF;  //bits[3..0] ? BT port PM mode
    cfg_POEMCU->class_error_selection      = (buf[4] >> 4) & 0xF;  //bits[7..4] ? Class Error Operation Select

    cfg_POEMCU->bt_port_operation_mode     = buf[5] ;
    cfg_POEMCU->legacy_support             = (buf[5] > 0x03)? true : false;

    cfg_POEMCU->add_power_for_port_mode_dW = buf[6] ;
    cfg_POEMCU->priority                   = buf[7] ;

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,EnDis=%d ,IgInr=%d ,IgAuClass=%d ,PM_mode=0x%X ,CLS_err=0x%X ,Oper Mode=0x%X ,legacy=%d ,Add pwr=%d ,Priority=0x%X",
          fname,
          handle,
          cfg_POEMCU->enable,
          cfg_POEMCU->ignored_inrush_check,
          cfg_POEMCU->ignore_pd_auto_class_request,
          cfg_POEMCU->bt_port_pm_mode,
          cfg_POEMCU->class_error_selection,
          cfg_POEMCU->bt_port_operation_mode,
          cfg_POEMCU->legacy_support,
          cfg_POEMCU->add_power_for_port_mode_dW,
          cfg_POEMCU->priority);

    return MESA_RC_OK;
}



uint8_t get_port_type_operation_mode(uint8_t bt_pse_port_type ,uint8_t bt_en ,uint8_t legacy_pd_class_mode)
{
    uint8_t col_ind = 0; // colume 0 - bt
    if (!bt_en) // mode is legacy (col 1,2,3)
    {
        col_ind = legacy_pd_class_mode + 1;
    }

    return prod.port_type_operation_mode[bt_pse_port_type][col_ind]; // pse_type , bt/legacy
}


/********************************************************************
* Set_BT_ParamsByOperationMode()
*
*   This function fill the local product database for each port depend on it's classification (which result in port maximum power).
*   BT_PORT_MAX_POWER_DEFAULT is the enum for PoE port max power 15/30/60/90
*
* Return: void
*********************************************************************/
void Set_BT_ParamsByOperationMode(meba_poe_ctrl_inst_t* inst)
{
    meba_poe_parameters_t tPoE_parameters = ((poe_driver_private_t *)(inst->private_data))->tPoE_parameters;

    // 15W
    prod.port_type_operation_mode[0][0] = eBT_Compliant_4P_15w_2P_15w;               // BT 15W standard
    prod.port_type_operation_mode[0][1] = eBT_Non_Compliant_4P_15w_2P_15w_Legacy;    // BT 15W legacy
    prod.port_type_operation_mode[0][2] = eBT_Non_Compliant_4P_15w_2P_15w_Legacy;    // poh - BT 15W legacy
    prod.port_type_operation_mode[0][3] = eBT_Non_Compliant_4P_15w_2P_15w_Legacy;    // ignore-pd-class - BT 15W legacy

    // 30W
    prod.port_type_operation_mode[1][0] = eBT_Compliant_4P_30w_2P_30w;               // BT 30W standard
    prod.port_type_operation_mode[1][1] = eBT_Non_Compliant_4P_30w_2P_30w_Legacy;    // BT 30W legacy
    prod.port_type_operation_mode[1][2] = eBT_Non_Compliant_4P_30w_2P_30w_Legacy;    // poh - BT 30W legacy
    prod.port_type_operation_mode[1][3] = eBT_Non_Compliant_4P_30w_2P_30w_Legacy;    // ignore-pd-class - BT 30W legacy

    // 60W
    prod.port_type_operation_mode[2][0] = eBT_Compliant_4P_60w_2P_30w;               // BT 60W standard
    prod.port_type_operation_mode[2][1] = eBT_Non_Compliant_4P_60w_2P_30w_Legacy;    // BT 60W legacy
    prod.port_type_operation_mode[2][2] = eBT_Non_Compliant_4P_60w_2P_30w_Legacy;    // poh - BT 60W legacy
    prod.port_type_operation_mode[2][3] = tPoE_parameters.bt_operation_mode_legacy_60W_ignore_pd_class_default;  // ignore-pd-class

    // 90W standard
    prod.port_type_operation_mode[3][0] = eBT_Compliant_4P_90w_2P_30w;               // BT 90W standard
    prod.port_type_operation_mode[3][1] = eBT_Non_Compliant_4P_90w_2P_30w_Legacy;    // BT 90W legacy
    prod.port_type_operation_mode[3][2] = tPoE_parameters.bt_operation_mode_legacy_90W_poh_default;              // poh
    prod.port_type_operation_mode[3][3] = tPoE_parameters.bt_operation_mode_legacy_90W_ignore_pd_class_default;  // ignore-pd-class

    switch(tPoE_parameters.ePoE_port_max_power_default)
    {
	case MEBA_POE_PORT_MAX_POWER_15W:
	{
             prod.poe_port_mode_max_power_index    = 0;
             prod.poe_class_max_pwr                = ePOE_CLASS_MAX_PWR_15W;                   //  Class-3 = 15W
             prod.class_error_selection[0] = 0x1;  // legacy
             prod.class_error_selection[1] = 0;    // BT
             break;
	}

	case MEBA_POE_PORT_MAX_POWER_30W:
	{
             prod.poe_port_mode_max_power_index = 1;
             prod.poe_class_max_pwr           = ePOE_CLASS_MAX_PWR_30W;                    //  Class-4 = 30W
             prod.class_error_selection[0]    = 0x2;  // legacy
             prod.class_error_selection[1]    = 0;    // BT
             break;
	}

	case MEBA_POE_PORT_MAX_POWER_60W:
	{
             prod.poe_port_mode_max_power_index = 2;
             prod.poe_class_max_pwr           = ePOE_CLASS_MAX_PWR_60W;                    //  Class-6 = 60W
             prod.class_error_selection[0]    = 0x3;  // legacy
             prod.class_error_selection[1]    = 0;    // BT
             break;
	}

	case MEBA_POE_PORT_MAX_POWER_90W:
	{
             prod.poe_port_mode_max_power_index = 3;
             prod.poe_class_max_pwr           = ePOE_CLASS_MAX_PWR_90W;                    //  Class-8 = 90W
             prod.class_error_selection[0]    = 0x4;  // legacy
             prod.class_error_selection[1]    = 0;    // BT
             break;
	}

	default:
	{
             prod.poe_port_mode_max_power_index = 2;
             prod.poe_class_max_pwr           = ePOE_CLASS_MAX_PWR_60W;                    //  Class-6 = 60W
             break;
	}
    }

    prod.port_max_pwr_per_type_mW = ClassMode_MaxPower_W[prod.poe_port_mode_max_power_index] * 1000;
}


// 'Get BT Port Status' driver
static
mesa_rc meba_poe_pd69200bt_ctrl_get_BT_port_status(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                     channel,
    uint8_t* port_status,
    uint8_t* enable,
    uint8_t* assigned_class,
    uint16_t* measured_port_power,
    uint8_t* last_shutdown_error_status,
    uint8_t* port_event)
{
    uint8_t  buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_STATUS_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET BT PORT STATUS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *port_status                = buf[2];
    *enable                     = buf[3];
    *assigned_class             = buf[4];
    *measured_port_power        = (buf[5] << 8) + buf[6];
    *last_shutdown_error_status = buf[9];
    *port_event                 = buf[10];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "[%s] CH=%d ,port status=%d ,enable=%d ,assigned class=%d ,measured port pwr=%lu ,last shutdown err status=%d ,port event=%d",
          fname,
          channel,
         *port_status,
         *enable,
         *assigned_class,
         *measured_port_power,
         *last_shutdown_error_status,
         *port_event);

    return MESA_RC_OK;
}

// 'Get BT Port Class' driver
static
mesa_rc meba_poe_pd69200bt_ctrl_get_BT_port_class(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                     channel,
    uint8_t  *port_status,
    uint8_t  *port_phy_info,
    uint8_t  *measured_class,
    uint8_t  *requested_class,
    uint16_t *requested_power_dW,
    uint8_t  *assigned_class,
    uint16_t *assigned_power_dW,
    uint8_t  *auto_class_support,
    uint16_t *auto_class_measurement_dw)
{
    uint8_t  buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_CLASS_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET BT PORT CLASS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *port_status               = buf[2];
    *port_phy_info             = buf[3];
    *measured_class            = buf[4];
    *requested_class           = buf[5];
    *requested_power_dW        = (buf[6] << 8) + buf[7];
    *assigned_class            = buf[8];
    *assigned_power_dW         = (buf[9] << 8) + buf[10];
    uint16_t Auto_Class_Measurement_plus_Support_Result = (buf[11] << 8) + buf[12];

    *auto_class_measurement_dw = (Auto_Class_Measurement_plus_Support_Result & 0xFFF);       // AutoClass Measurement: Bits [11..0]
    *auto_class_support        = ((Auto_Class_Measurement_plus_Support_Result >> 12)& 0xF);  // AutoClass Support: Bits [15..12]

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "[%s] CH=%d ,port status=0x%X ,port phy info=0x%X ,measured class=0x%X ,requested class=0x%X ,requested pwr_dW=%lu ,assigned_class=0x%X, assigned_power_dW=%lu ,AutoClass measure=%lu ,AutoClass Support=%d",
          fname,
          channel,
          *port_status,
          *port_phy_info,
          *measured_class,
          *requested_class,
          *requested_power_dW,
          *assigned_class,
          *assigned_power_dW,
          *auto_class_measurement_dw,
          *auto_class_support);

    return MESA_RC_OK;
}

// 'Get BT Port Measurements' driver
mesa_rc meba_poe_pd69200bt_get_BT_port_measurements(
    const meba_poe_ctrl_inst_t* const inst,
    uint8_t                         channel,
    uint16_t* main_voltage_dv,
    uint32_t* calculated_current_mA,
    uint16_t* port_power_consumption_dW,
    uint16_t* port_voltage_dV)
{

    // Send request to get status
    unsigned char buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_MEASE_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET BT PORT MEASUREMENTS";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *main_voltage_dv          = (buf[2] << 8) + buf[3];
    *calculated_current_mA    = (buf[4] << 8) + buf[5];
    *port_power_consumption_dW = (buf[6] << 8) + buf[7];
    *port_voltage_dV          = (buf[9] << 8) + buf[10];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "[%s] CH=%d ,main voltage=%lu[dv] ,calculated current=%lu[mA] ,port pwr consumption=%lu[dW] ,port voltage=%lu[dV]",
          fname,
          channel,
          *main_voltage_dv,
          *calculated_current_mA,
          *port_power_consumption_dW,
          *port_voltage_dV);

    return MESA_RC_OK;
}


// configure the port parametes which sent to 'Set BT Port Parameters'
mesa_rc meba_poe_pd69200bt_ctrl_port_cfg_set(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t     handle,
    meba_poe_port_cfg_t        *req_port_cfg)
{
    meba_poe_global_cfg_t *global_cfg      = &(((poe_driver_private_t*)(inst->private_data))->cfg.global);
    meba_poe_port_cfg_t   *port_cfg        = &(((poe_driver_private_t*)(inst->private_data))->cfg.ports[handle]);
    meba_poe_port_cfg_t   *port_cfg_POEMCU = &(((poe_driver_private_t*)(inst->private_data))->cfg_POEMCU.ports[handle]);

    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    if (handle >= inst->port_map_length)
    {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    // port < max poe ports
    if (handle >= inst->port_poe_length)
    {
        //DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_OK;
    }

    // the req_cfg contains all updated config.
    // req_cfg overide the cfg (with exceptions)
    // and then it compares the cfg with cfg_POEMCU - then fix if needed

    // cable length is internal varible and not readed from POE MCU.
    if(req_port_cfg->cable_length != port_cfg->cable_length)
    {
        if (port_cfg->cable_length != 255)
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "driver updating cable_length on CH=%d changed from %d to %d", handle, port_cfg->cable_length, req_port_cfg->cable_length);
        else
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "driver cable_length on CH=%d is %d", handle, req_port_cfg->cable_length);

        port_cfg->cable_length = req_port_cfg->cable_length;
    }

    // use global flag to set ports ignore_pd_auto_class_request parameter
    req_port_cfg->ignore_pd_auto_class_request = global_cfg->global_ignore_pd_auto_class_request;

    // use static varible to check if global_cfg->global_legacy_pd_class_mode was changned (only for message purpose)
    static uint8_t global_legacy_pd_class_mode = 0;
    if (global_legacy_pd_class_mode != global_cfg->global_legacy_pd_class_mode)
    {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "global_legacy_pd_class_mode: %d ,cfg global_legacy_pd_class_mode: %d",global_legacy_pd_class_mode ,global_cfg->global_legacy_pd_class_mode);
        global_legacy_pd_class_mode = global_cfg->global_legacy_pd_class_mode;
    }

    // if port is disabled - there is no info for operation mode - stay with the last operation mode configuration
    uint8_t req_bt_port_operation_mode = port_cfg_POEMCU->bt_port_operation_mode;

    mesa_bool_t operation_mode_changed = false;

    // port is enabled so operation mode will be calculated and set
    if (req_port_cfg->enable)
    {
         req_bt_port_operation_mode  = get_port_type_operation_mode(req_port_cfg->bt_pse_port_type , !(req_port_cfg->legacy_support) ,global_cfg->global_legacy_pd_class_mode); // pse_type , bt/legacy , legacy_pd_class_mode

         // check if port_operation_mode was changed
         if(port_cfg_POEMCU->bt_port_operation_mode != req_bt_port_operation_mode)
         {
             DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "POEMCU->bt_port_operation_mode: 0x%X ,req_bt_port_operation_mode: 0x%X",port_cfg_POEMCU->bt_port_operation_mode ,req_bt_port_operation_mode);
             operation_mode_changed = true;
         }
    }
    else // port disabled
    {
        // keep the legacy_support setting
        req_port_cfg->legacy_support = port_cfg->legacy_support;
    }

    // in case port is disabled: req_bt_port_operation_mode will be port_cfg_POEMCU->bt_port_operation_mode
    // in case port is enabled : calculate operation mode
    port_cfg->bt_port_operation_mode = req_bt_port_operation_mode;

    // check if any parameter was change
    if ((port_cfg->enable == req_port_cfg->enable) &&
        (port_cfg->ignore_pd_auto_class_request == req_port_cfg->ignore_pd_auto_class_request) &&
        (port_cfg->bt_port_pm_mode              == req_port_cfg->bt_port_pm_mode) &&
        (port_cfg->legacy_support               == req_port_cfg->legacy_support) &&
        (port_cfg->bt_pse_port_type             == req_port_cfg->bt_pse_port_type) &&
        (port_cfg->priority                     == req_port_cfg->priority) &&
        (!operation_mode_changed)
        )
    {
        return MESA_RC_OK;
    }

    // read parameters from PoE
    MESA_RC(meba_poe_pd69200bt_ctrl_get_BT_port_parameters(
            inst ,handle,port_cfg_POEMCU));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[ReqGlobalCfg_____]       ,Legacy PD-Class Mode=%d ,oper mode changed=%d",
            global_cfg->global_legacy_pd_class_mode,
            operation_mode_changed);

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[ReqPortCfg_______] CH=%d ,EnDis=%d ,IgAutoClass=%d ,bt_pm_mode=%d ,legacy=%d ,type=%d ,Priority=%d ,oper mode: 0x%X",
            handle,
            req_port_cfg->enable,
            req_port_cfg->ignore_pd_auto_class_request,
            req_port_cfg->bt_port_pm_mode,
            req_port_cfg->legacy_support,
            req_port_cfg->bt_pse_port_type,
            req_port_cfg->priority,
            req_bt_port_operation_mode);

   DEBUG(inst, MEBA_TRACE_LVL_INFO, "[PortCfg__________] CH=%d ,EnDis=%d ,IgAutoClass=%d ,bt_pm_mode=%d ,legacy=%d ,type=%d ,Priority=%d ,oper mode: 0x%X",
            handle,
            port_cfg->enable,
            port_cfg->ignore_pd_auto_class_request,
            port_cfg->bt_port_pm_mode,
            port_cfg->legacy_support,
            port_cfg->bt_pse_port_type,
            port_cfg->priority,
            port_cfg_POEMCU->bt_port_operation_mode); // current bt_port_operation_mode

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Update ports configuration for controller port %d",  handle);

    mesa_bool_t bParamChanged = false;   // Flag which indicate that we need to update the change into the POEMCU. We need to send "Set BT Port Parameters"

    // No change values
    uint8_t CFG1 = 0;
    uint8_t Port_Enable_Modes = (uint8_t)ePort_EnDis_No_change;
    uint8_t Special_Port_Configuration_Bits_4_7 = 0;

    uint8_t CFG2 = 0;
    uint8_t BT_port_PM_mode = eBT_port_PM_mode_Do_not_change_settings;
    uint8_t Class_error_selection = eClass_error_Do_not_change_settings;

    uint8_t BT_port_Operation_Mode = eBT_Mode_No_change;

    uint8_t Add_power_for_port_mode_dW = 0;

    uint8_t Priority = ePORT_PRIORITY_NoChange;

    // params obtained by request
    port_cfg->enable                         = req_port_cfg->enable;
    port_cfg->bt_port_pm_mode                = eBT_port_PM_mode_Do_not_change_settings;
    port_cfg->bt_pse_port_type               = req_port_cfg->bt_pse_port_type;

    // update parameters which affected when port is enabled
    if (req_port_cfg->enable)
    {
        port_cfg->legacy_support             = req_port_cfg->legacy_support;
        port_cfg->bt_en                      = !(req_port_cfg->legacy_support);
        port_cfg->ignored_inrush_check       = req_port_cfg->legacy_support;
        port_cfg->bt_port_operation_mode     = req_bt_port_operation_mode;  // composed from: pse_type , bt/legacy , legacy_pd_class_mode
        port_cfg->class_error_selection      = prod.class_error_selection[port_cfg->bt_en];
    }

    port_cfg->bt_port_pm_mode                = req_port_cfg->bt_port_pm_mode;
    port_cfg->priority                       = req_port_cfg->priority;
    port_cfg->ignore_pd_auto_class_request   = req_port_cfg->ignore_pd_auto_class_request; //- set by AutoClass global var
    Special_Port_Configuration_Bits_4_7      = req_port_cfg->ignore_pd_auto_class_request;

    // BT / legacy
    port_cfg->add_power_for_port_mode_dW = MAX_ADDED_CLASS_POWER_dW;

    // check Port BT_port_Operation_mode for each port
    if(port_cfg_POEMCU->bt_port_operation_mode != port_cfg->bt_port_operation_mode)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Change POEMCU CH-%02d Op mode from 0x%X to 0x%X",
                    handle, port_cfg_POEMCU->bt_port_operation_mode, port_cfg->bt_port_operation_mode );

        BT_port_Operation_Mode = port_cfg->bt_port_operation_mode;

        bParamChanged = true;
    }

    // check Port En/Dis for each port
    if (( port_cfg_POEMCU->enable != port_cfg->enable ) ||
        ((port_cfg_POEMCU->ignored_inrush_check != port_cfg->ignored_inrush_check) && port_cfg->enable))
    {
        if (port_cfg_POEMCU->enable != port_cfg->enable)
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Change POEMCU CH-%02d ON/OFF from %d to %d",
                        handle, port_cfg_POEMCU->enable, port_cfg->enable);
        }

        if (port_cfg_POEMCU->ignored_inrush_check != port_cfg->ignored_inrush_check)
        {
            DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Change POEMCU CH-%02d Ignore inrush from %d to %d",
                        handle, port_cfg_POEMCU->ignored_inrush_check, port_cfg->ignored_inrush_check);
        }

        Port_Enable_Modes = port_cfg->enable;  // 0 or 1

        if ( port_cfg->enable && port_cfg->ignored_inrush_check )   // in case Enabled and Legacy - 2
            Port_Enable_Modes = ePort_Enable_with_ignored_inrush_check;

        bParamChanged = true;
    }


    //  Check if POEMCU POEBT PD Auto_Class request needs to be changed and saved to data base configuration
    if ( port_cfg_POEMCU->ignore_pd_auto_class_request != global_cfg->global_ignore_pd_auto_class_request )
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Change POEMCU CH-%02d Ignore Auto Class from %d to %d",
                    handle, port_cfg_POEMCU->ignore_pd_auto_class_request, global_cfg->global_ignore_pd_auto_class_request);
        bParamChanged = true;

        Special_Port_Configuration_Bits_4_7 = global_cfg->global_ignore_pd_auto_class_request ;
    }

    CFG1 = Port_Enable_Modes | (Special_Port_Configuration_Bits_4_7 << 4);


    // check Port BT_port_PM_mode for each port
    if ( port_cfg_POEMCU->bt_port_pm_mode != port_cfg->bt_port_pm_mode )
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Change POEMCU CH-%02d bt_port_pm_mode from %d to %d",
                        handle, port_cfg_POEMCU->bt_port_pm_mode , port_cfg->bt_port_pm_mode);

        BT_port_PM_mode = port_cfg->bt_port_pm_mode;
        bParamChanged = true;
    }

    if (port_cfg->enable) // update only if port is active - otherwise - set "no change"
    {
        if(( port_cfg_POEMCU->class_error_selection != prod.class_error_selection[port_cfg->bt_en] ) ||
           ( port_cfg->class_error_selection != prod.class_error_selection[port_cfg->bt_en] ))
        {
            if ( port_cfg_POEMCU->class_error_selection != prod.class_error_selection[port_cfg->bt_en] )
            {
                DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Change POEMCU CH-%02d class_error_selection from %d to %d",
                            handle,  port_cfg_POEMCU->class_error_selection, prod.class_error_selection[port_cfg->bt_en] );
            }

            if ( port_cfg->class_error_selection != prod.class_error_selection[port_cfg->bt_en] )
            {
                DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Set Config CH-%02d class_error_selection from %d to %d",
                            handle,  port_cfg->class_error_selection, prod.class_error_selection[port_cfg->bt_en] );
            }

            port_cfg->class_error_selection = prod.class_error_selection[port_cfg->bt_en];
            Class_error_selection = prod.class_error_selection[port_cfg->bt_en];

            bParamChanged = true;
        }
    }

    CFG2 = BT_port_PM_mode + (Class_error_selection << 4);

    // SET extra 0/2.5w (25deci) to port mode addition mode
    Add_power_for_port_mode_dW = port_cfg->add_power_for_port_mode_dW;

    //// check Port Additional_Power_for_Port_Mode for each port
    //if( port_cfg_POEMCU->add_power_for_port_mode_dW != port_cfg->add_power_for_port_mode_dW )
    //{
    //    DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Change POEMCU CH-%02d Additional_Power_for_Port_Mode from %d to %d",
    //                handle, port_cfg_POEMCU->add_power_for_port_mode_dW, port_cfg->add_power_for_port_mode_dW );
    //
    //    BT_port_Operation_Mode = port_cfg->port_operation_mode;
    //
    //    //bParamChanged = true;
    //}
    //else
    //{
    //    Add_power_for_port_mode_dW = port_cfg->add_power_for_port_mode_dW;
    //}

     // check Port priority for each port
     if ( port_cfg_POEMCU->priority != port_cfg->priority )
     {
         DEBUG(inst, MEBA_TRACE_LVL_INFO, "* Change POEMCU CH-%02d Priority from %d to %d",handle,
                     port_cfg_POEMCU->priority,
                     port_cfg->priority );

         Priority = port_cfg->priority;
         bParamChanged = true;
     }

    if(bParamChanged == true)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "[CFG-SET BT PORT PARAMS] CH=%d ,En=%d ,IgInChk=%d ,IgAuClass=%d ,PM_mode=%d ,Class err=%d ,Op mode=0x%X ,legacy=%d ,type=%d ,Add pwr=%d ,Priority=%d",
               handle,
               port_cfg->enable,
               port_cfg->ignored_inrush_check,
               port_cfg->ignore_pd_auto_class_request,
               port_cfg->bt_port_pm_mode,
               port_cfg->class_error_selection,
               port_cfg->bt_port_operation_mode,
               port_cfg->legacy_support,
               port_cfg->bt_pse_port_type,
               port_cfg->add_power_for_port_mode_dW,
               port_cfg->priority);

        // 4.3.6        Set BT Port Parameters
        MESA_RC(meba_poe_pd69200bt_ctrl_set_BT_port_parameters(
            inst,
            handle,
            CFG1,
            CFG2,
            BT_port_Operation_Mode,
            Add_power_for_port_mode_dW,
            Priority));

        // read parameters from PoE
        MESA_RC(meba_poe_pd69200bt_ctrl_get_BT_port_parameters(
            inst ,handle,port_cfg_POEMCU));

        MESA_RC(meba_poe_pd69200_ctrl_save_command(inst));
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "Save PoE settings");
    }

    return MESA_RC_OK;
}


static
mesa_rc meba_poe_pd69200bt_ctrl_set_port_layer2_lldp_pd_request(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      channel,
    uint16_t                    requested_power_single_dw,  // deciwatt
    uint16_t                    requested_power_dual_a_dw,  // deciwatt
    uint16_t                    requested_power_dual_b_dw,  // deciwatt
    uint8_t                     cable_len,
    uint8_t                     autoclass)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        LAYER2_BT_LLDP_PD_KEY,
        channel,
        ((requested_power_single_dw >> 8) & 0xFF),
        (requested_power_single_dw & 0xFF),
        ((requested_power_dual_a_dw >> 8) & 0xFF),
        (requested_power_dual_a_dw & 0xFF),
        ((requested_power_dual_b_dw >> 8) & 0xFF),
        (requested_power_dual_b_dw & 0xFF),
        (autoclass << 4) + cable_len,
        DUMMY_BYTE
    };

    char *fname = "SET BT PORT LAYER2 LLDP PD REQUEST";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "[%s] CH=%d ,req pwr single dw=%lu ,req pwr dual_a dw=%lu ,req pwr dual_b dw=%lu ,cable len=%d ,autoclass=%d",
          fname,
          channel,
          requested_power_single_dw,
          requested_power_dual_a_dw,
          requested_power_dual_b_dw,
          cable_len,
          autoclass);

    return MESA_RC_OK;
}

static
mesa_rc meba_poe_pd69200bt_ctrl_get_port_layer2_lldp_pse_data(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t      channel,
    uint16_t* pse_allocated_power_a_or_single_dw,
    uint16_t* pse_allocated_power_b_dw,
    uint16_t* pse_max_power_dw,
    uint8_t*  assigned_class,
    uint8_t*  status,
    uint8_t*  power_bits,
    uint8_t*  cable_length_in_use,
    uint8_t*  l2_cfg)
{
    uint8_t  buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        LAYER2_BT_LLDP_PSE_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    char *fname = "GET BT PORT LAYER2 LLDP PSE DATA";
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf, fname));

    *pse_allocated_power_a_or_single_dw = (buf[2] << 8) + buf[3];
    *pse_allocated_power_b_dw           = (buf[4] << 8) + buf[5];
    *pse_max_power_dw                   = (buf[6] << 8) + buf[7];
    *assigned_class                     =  buf[8];
    *status                             =  buf[9];
    *power_bits                         =  buf[10];
    *cable_length_in_use                =  buf[11];
    *l2_cfg                             =  buf[12];

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "[%s] CH=%d ,pse alloc pwr_a_or_single=%u [dW],pse_alloc_pwr_b=%u [dW],pse_max_pwr=%u [dW] ,assigned_class=%d ,status=%d ,pwr bits=%d ,cable len in use=%d ,l2_cfg=%d",
          fname,
          channel,
          *pse_allocated_power_a_or_single_dw,
          *pse_allocated_power_b_dw,
          *pse_max_power_dw,
          *assigned_class,
          *status,
          *power_bits,
          *cable_length_in_use,
          *l2_cfg);

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200bt_ctrl_globals_cfg_set(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_global_cfg_t* cfg_global)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    meba_poe_global_cfg_t* current_global_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.global);

    current_global_cfg->global_ignore_pd_auto_class_request = cfg_global->global_ignore_pd_auto_class_request;
    current_global_cfg->global_legacy_pd_class_mode = cfg_global->global_legacy_pd_class_mode;

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "meba_poe_pd69200bt_ctrl_globals_cfg_set, current_global_cfg->primary_max_power_w= %d , cfg_global->primary_max_power_w=%d",
          current_global_cfg->primary_max_power_w , cfg_global->primary_max_power_w);

    if ((current_global_cfg->primary_max_power_w == cfg_global->primary_max_power_w))
    {
        return MESA_RC_OK;
    }

    current_global_cfg->primary_max_power_w = cfg_global->primary_max_power_w;

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Update globals configuration for controller");

    uint16_t  power_consumption_w;
    uint16_t  max_shutdown_voltage_dv;
    uint16_t  min_shutdown_voltage_dv;
    uint8_t   guard_band;
    uint8_t   power_bank;      // The current active power bank
    uint16_t  power_limit_w;   // The disconnection power level of a specific power bank

    MESA_RC(pd69200_get_power_supply_parameters(
                inst,
                &power_consumption_w,
                &max_shutdown_voltage_dv,
                &min_shutdown_voltage_dv,
                &guard_band,
                &power_bank,
                &power_limit_w));

    if (power_limit_w != cfg_global->primary_max_power_w)
    {
        power_limit_w = cfg_global->primary_max_power_w;

        MESA_RC(meba_poe_pd69200_set_power_banks(
                inst,
                power_bank,
                power_limit_w,
                max_shutdown_voltage_dv,
                min_shutdown_voltage_dv,
                0));
    }

    return MESA_RC_OK;
}



char* GetBT_TitleByPortsStatus(uint8_t bt_port_status)
{
    switch (bt_port_status)
    {
        //--- Port off ---//
    case eBT_0x06_OFF_Main_supply_voltage_is_high:
        return "0x06: P.S Voltage to High";
    case eBT_0x07_OFF_Main_supply_voltage_is_low:
        return "0x07: P.S Voltage to Low";
    case eBT_0x08_OFF_Disable_all_ports_pin_is_active:
        return "0x08: Disable all Port by I/O pin";
    case eBT_0x0C_OFF_Non_existing_port_number:
        return "0x0C: Invalid Port Index";
    case eBT_0x11_OFF_Port_is_yet_undefined:
        return "0x11: Port is yet undefined";
    case eBT_0x12_OFF_Internal_hardware_fault:
        return "0x12: Internal Hardware Fault";
    case eBT_0x1A_OFF_User_setting:
        return "0x1A: Disable Command";
    case eBT_0x1B_OFF_Detection_is_in_process:
        return "0x1B: Detection in process (searching)";
    case eBT_0x1C_OFF_Non_802_3AF_AT_powered_device:
        return "0x1C: None-standard 802.3AF-AT PD";
    case eBT_0x1E_OFF_Underload_state:
        return "0x1E: Underload";
    case eBT_0x1F_OFF_Overload_state:
        return "0x1F: Overload";
    case eBT_0x20_OFF_Power_budget_exceeded:
        return "0x20: Exceeded Overall Power Budget";
    case eBT_0x21_OFF_Internal_hardware_routing_error:
        return "0x21: OFF Internal hardware routing error";
    case eBT_0x22_OFF_Configuration_change:
        return "0x22: Configuration Update In Procerss";
    case eBT_0x24_OFF_Voltage_injection_into_the_port:
        return "0x24: Ext Voltage Was injected";
    case eBT_0x25_OFF_Improper_Cap_Det_results_or_Det_val_indicating_short:
        return "0x25: PD Capacitor out of range";
    case eBT_0x26_OFF_Discharged_load:
        return "0x26: Discharged load";
    case eBT_0x34_OFF_Short_condition:
        return "0x34: Shortage";
    case eBT_0x35_OFF_Over_temperature_at_the_port:
        return "0x35: Port Over Temperature";
    case eBT_0x36_OFF_Device_is_too_hot:
        return "0x36: Silicon-Die Over Temperature";
    case eBT_0x37_Unknown_device_port_status:
        return "0x37: Unknown device port status";
    case eBT_0x3C_OFF_Power_Mng_Static_calc_pwr_exceed_pwr_limit:
        return "0x3C: Stat Pwr Management > Pwr Limit";
    case eBT_0x3D_OFF_Power_Management_Static_ovl:
        return "0x3D: PD Class > Port Max Pwr";
    case eBT_0x41_OFF_Power_denied_Hardware_power_limit:
        return "0x41: PD Class > PoE-IC max Class";
    case eBT_0x43_OFF_Class_Error:
        return "0x43: Class_Error";
	case eBT_0x44_OFF_Port_turn_off_during_host_crash:
		return "0x44: port turn off during host crash";
	case eBT_0x45_OFF_Delivering_power_forced_off_during_host_crash:
		return "0x45: pwr forced off during host crash";
	case eBT_0x46_OFF_Enabled_port_forced_off_during_host_crash:
		return "0x46: forced off during host crash";
	case eBT_0x47_OFF_Forced_power_crash_error:
		return "0x47: Forced power crash_error";
	case eBT_0x48_OFF_recovery_UDL:
		return "0x48: recovery UDL";
	case eBT_0x49_OFF_recovery_PG:
		return "0x49: recovery PG";
	case eBT_0x4A_OFF_recovery_OVL:
		return "0x43: recovery OVL";
	case eBT_0x4B_OFF_recovery_SC:
		return "0x43: recovery SC";
	case eBT_0x4C_OFF_recovery_voltage_injection:
		return "0x43: recovery voltage injection";
    case eBT_0x80_ON_2P_Port_delivering_non_IEEE:
        return "0x80: 2P None IEEE";
    case eBT_0x81_ON_2P_Port_delivering_IEEE:
        return "0x81: 2P IEEE";
    case eBT_0x82_ON_4P_Port_that_deliver_only_2_Pair_non_IEEE:
        return "0x82: 4P Pwr on 2P None IEEE";
    case eBT_0x83_ON_4P_Port_delivering_2P_non_IEEE:
        return "0x83: 4P Pwr on 2P None IEEE";
    case eBT_0x84_ON_4P_Port_delivering_4P_non_IEEE:
        return "0x84: 4P Pwr on 4P None IEEE";
    case eBT_0x85_ON_4P_Port_delivering_2P_IEEE_SSPD:
        return "0x85: 4P Pwr on 2P IEEE SSPD";
    case eBT_0x86_ON_4P_Port_delivering_4P_IEEE_SSPD:
        return "0x86: 4P Pwr on 4P IEEE SSPD";
    case eBT_0x87_ON_4P_Port_delivering_4P_IEEE_DSPD_1st_phase:
        return "0x87: 4P Pwr on 2P IEEE DSPD 1st-phase";
    case eBT_0x88_ON_4P_Port_delivering_2P_IEEE_DSPD:
        return "0x88: 4P Pwr on 2P IEEE DSPD";
    case eBT_0x89_ON_4P_Port_delivering_4P_IEEE_DSPD:
        return "0x89: 4P Pwr on 4P IEEE DSPD";
    case eBT_0x90_ON_Force_Power_BT_2P:
        return "0x90: 2P Force Power BT";
    case eBT_0x91_ON_Force_Power_BT_4P:
        return "0x91: 4P Force Power BT";
    case eBT_0xA0_OFF_Force_Power_BT_Error:
        return "0xA0: Force Pwr-BT Error";
    case eBT_0xA7_OFF_Connection_Check_error:
        return "0xA7: None PoE Ethernet Device";
    case eBT_0xA8_OFF_Open_Port_is_not_connected:
        return "0xA8: No Device (open)";
    default:
        {
            return "?????";
        }
    }
}


// * return values:
// * MESA_RC_ERROR
// * MESA_RC_OK
// * MESA_RC_ERR_PARM - invalid handle - out of scope or not poe port
mesa_rc meba_poe_pd69200bt_ctrl_port_status_get(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_port_status_t* const port_status)
{
    if (port_status == NULL)  {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s port_status is NULL pointer", __FUNCTION__);
        return MESA_RC_ERROR;
    }

    port_status->chip_state = meba_poe_pd69200_get_chipset(inst);

    if (port_status->chip_state == MEBA_POE_FIRMWARE_UPGRADE) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Firmware upgrading", __FUNCTION__);
        port_status->assigned_pd_class_a = -1;
        port_status->assigned_pd_class_b = -1;
        port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_NOT_PERFORMED;
        port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_DISABLED;
        port_status->power_mw = 0;
        port_status->current_ma = 0;
        port_status->voltage_mv = 0;
        port_status->power_requested_mw = 0;
        return MESA_RC_OK;
    }

    if (port_status->chip_state != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Device not ready for reading", __FUNCTION__);
        return MESA_RC_ERROR;
    }

    // handle out of ports scope
    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid handle= %d", __FUNCTION__, handle);
        return MESA_RC_ERR_PARM;
    }

    // not a poe port
    if (!(inst->port_map[handle].capabilities & MEBA_POE_PORT_CAP_POE))
    {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Not PoE port= %d", __FUNCTION__, handle);
        return MESA_RC_ERR_PARM;
    }

    // port < max poe ports
    if (handle >= inst->port_poe_length)
    {
        //DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_OK;
    }

    meba_poe_port_cfg_t *port_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.ports[handle]);
    meba_poe_port_private_status_t* current_port_status = &(((poe_driver_private_t*)(inst->private_data))->status.ports[handle]);
    meba_poe_port_cfg_t *port_cfg_POEMCU = &(((poe_driver_private_t*)(inst->private_data))->cfg_POEMCU.ports[handle]);

    meba_poe_port_handle_t channel = handle;
    uint8_t  port_state;
    uint8_t  enable;
    uint8_t  assigned_class;
    uint16_t measured_port_power;
    uint8_t  last_shutdown_error_status;
    uint8_t  port_event;

    MESA_RC(meba_poe_pd69200bt_ctrl_get_BT_port_status(
                inst,
                channel,
                &port_state,
                &enable,
                &assigned_class,
                &measured_port_power,
                &last_shutdown_error_status,
                &port_event));

    port_status->assigned_pd_class_a = (assigned_class & 0xF0) >> 4;
    port_status->assigned_pd_class_b = assigned_class & 0xF;

    if (port_status->poe_internal_port_status != port_state)
    {
        strncpy( port_status->poe_port_status_description , GetBT_TitleByPortsStatus(port_state), MAX_STR_SIZE-1);
    }

    port_status->poe_internal_port_status = port_state;

    if (port_status->assigned_pd_class_a == 0xC) {
        port_status->assigned_pd_class_a = -1;
    }
    if (port_status->assigned_pd_class_b == 0xC) {
        port_status->assigned_pd_class_b = -1;
    }
    port_status->power_mw = measured_port_power * 100;

    // See table 4 in the user guide for understanding the conversion - we do not support all status values.

    switch (port_status->poe_internal_port_status)
    {
        case  eBT_0x81_ON_2P_Port_delivering_IEEE:
        case  eBT_0x85_ON_4P_Port_delivering_2P_IEEE_SSPD:
        case  eBT_0x86_ON_4P_Port_delivering_4P_IEEE_SSPD:
        case  eBT_0x87_ON_4P_Port_delivering_4P_IEEE_DSPD_1st_phase:
        case  eBT_0x88_ON_4P_Port_delivering_2P_IEEE_DSPD:
        case  eBT_0x89_ON_4P_Port_delivering_4P_IEEE_DSPD:
        {
            port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_DELIVERING_POWER;  // POEBT
            port_status->is_poe_bt = true;
            break;
        }

        case  eBT_0x80_ON_2P_Port_delivering_non_IEEE:
        case  eBT_0x82_ON_4P_Port_that_deliver_only_2_Pair_non_IEEE:
        case  eBT_0x83_ON_4P_Port_delivering_2P_non_IEEE:
        case  eBT_0x84_ON_4P_Port_delivering_4P_non_IEEE:
        {
            port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_DELIVERING_POWER;  // LEGACY
            port_status->is_poe_bt = false;
            break;
        }

        case eBT_0x90_ON_Force_Power_BT_2P:
        case eBT_0x91_ON_Force_Power_BT_4P:
        {
                port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_TEST;
                break;
        }

        case eBT_0x08_OFF_Disable_all_ports_pin_is_active:
        case eBT_0x1A_OFF_User_setting:
        case eBT_0x22_OFF_Configuration_change:
        {
                port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_DISABLED;
                break;
        }

        // Interim state, detection going on  -     eOFF_Detection_is_in_process
        case eBT_0x1B_OFF_Detection_is_in_process:
        case eBT_0xA8_OFF_Open_Port_is_not_connected:  // typical value when nothing is connected to the port
        {
                port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_SEARCHING;
                break;
        }

        // Port is off due to miselenious reasones
        case eBT_0x1F_OFF_Overload_state:
        case eBT_0x34_OFF_Short_condition:
        case eBT_0x4A_OFF_recovery_OVL:
        case eBT_0x4B_OFF_recovery_SC:
        {
                port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_FAULT;
                break;
        }

        case eBT_0x06_OFF_Main_supply_voltage_is_high:
        case eBT_0x07_OFF_Main_supply_voltage_is_low:
        case eBT_0x0C_OFF_Non_existing_port_number:
        case eBT_0x11_OFF_Port_is_yet_undefined:
        case eBT_0x12_OFF_Internal_hardware_fault:
        case eBT_0x1C_OFF_Non_802_3AF_AT_powered_device: // Non-standart PD connected
        case eBT_0x1E_OFF_Underload_state:
        case eBT_0x20_OFF_Power_budget_exceeded:
        case eBT_0x21_OFF_Internal_hardware_routing_error:
        case eBT_0x24_OFF_Voltage_injection_into_the_port:
        case eBT_0x25_OFF_Improper_Cap_Det_results_or_Det_val_indicating_short:
        case eBT_0x26_OFF_Discharged_load:
        case eBT_0x35_OFF_Over_temperature_at_the_port:
        case eBT_0x36_OFF_Device_is_too_hot:
        case eBT_0x37_Unknown_device_port_status:
        case eBT_0x3C_OFF_Power_Mng_Static_calc_pwr_exceed_pwr_limit:
        case eBT_0x3D_OFF_Power_Management_Static_ovl:
        case eBT_0x41_OFF_Power_denied_Hardware_power_limit:
        case eBT_0x43_OFF_Class_Error:
        case eBT_0x44_OFF_Port_turn_off_during_host_crash:
        case eBT_0x45_OFF_Delivering_power_forced_off_during_host_crash:
        case eBT_0x46_OFF_Enabled_port_forced_off_during_host_crash:
        case eBT_0x47_OFF_Forced_power_crash_error:
        case eBT_0x48_OFF_recovery_UDL:
        case eBT_0x49_OFF_recovery_PG:
        case eBT_0x4C_OFF_recovery_voltage_injection:
        case eBT_0xA0_OFF_Force_Power_BT_Error:
        case eBT_0xA7_OFF_Connection_Check_error:      // normal status when Ethernet link as laptop is conencted to this port
        case eBT_0xFF_PORT_STATUS_ONKNOWN:
        {
            port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_OTHER_FAULT;
            break;
        }

        default:
        {
                // This shall never happen all states should be covered.
                DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Port %d: Unknown port state: 0x%X",
                      inst->port_map[handle].port_no, port_state);
                port_status->meba_poe_ieee_port_state = MEBA_POE_IEEE_PORT_STATE_OTHER_FAULT;
                break;
        }
    }


    switch (port_status->poe_internal_port_status)
    {
        case  eBT_0x81_ON_2P_Port_delivering_IEEE:
        case  eBT_0x85_ON_4P_Port_delivering_2P_IEEE_SSPD:
        case  eBT_0x86_ON_4P_Port_delivering_4P_IEEE_SSPD:
        case  eBT_0x87_ON_4P_Port_delivering_4P_IEEE_DSPD_1st_phase:
        case  eBT_0x88_ON_4P_Port_delivering_2P_IEEE_DSPD:
        case  eBT_0x89_ON_4P_Port_delivering_4P_IEEE_DSPD:
        {
            port_status->meba_poe_port_state = MEBA_POE_PD_ON;  // ON POEBT
            break;
        }

        case  eBT_0x80_ON_2P_Port_delivering_non_IEEE:
        case  eBT_0x82_ON_4P_Port_that_deliver_only_2_Pair_non_IEEE:
        case  eBT_0x83_ON_4P_Port_delivering_2P_non_IEEE:
        case  eBT_0x84_ON_4P_Port_delivering_4P_non_IEEE:
        {
            port_status->meba_poe_port_state = MEBA_POE_PD_ON;  // ON LEGACY
            break;
        }

        case eBT_0x08_OFF_Disable_all_ports_pin_is_active:
        case eBT_0x1A_OFF_User_setting:
        case eBT_0x22_OFF_Configuration_change:
        {
            port_status->meba_poe_port_state = MEBA_POE_DISABLED;
            break;
        }

        // Interim state, detection going on  -     eOFF_Detection_is_in_process
        case eBT_0x1B_OFF_Detection_is_in_process:
        case eBT_0xA8_OFF_Open_Port_is_not_connected:  // typical value when nothing is connected to the port
        {
            port_status->meba_poe_port_state = MEBA_POE_NO_PD_DETECTED;
            break;
        }

        case eBT_0x1F_OFF_Overload_state:
        {
            port_status->meba_poe_port_state = MEBA_POE_PD_OVERLOAD;
            break;
        }

        case eBT_0x20_OFF_Power_budget_exceeded:
        case eBT_0x4A_OFF_recovery_OVL:
        {
            port_status->meba_poe_port_state = MEBA_POE_POWER_BUDGET_EXCEEDED;
            break;
        }

        // Port is off due to miselenious reasones
        case eBT_0x1C_OFF_Non_802_3AF_AT_powered_device: // Non-standart PD connected
        case eBT_0x1E_OFF_Underload_state:
        case eBT_0x25_OFF_Improper_Cap_Det_results_or_Det_val_indicating_short:
        case eBT_0x34_OFF_Short_condition:
        case eBT_0x43_OFF_Class_Error:
        case eBT_0x48_OFF_recovery_UDL:
        case eBT_0x4B_OFF_recovery_SC:
        case eBT_0xA7_OFF_Connection_Check_error:      // normal status when Ethernet link as laptop is conencted to this port
        {
            port_status->meba_poe_port_state = MEBA_POE_PD_FAULT;
            break;
        }

        case eBT_0x06_OFF_Main_supply_voltage_is_high:
        case eBT_0x07_OFF_Main_supply_voltage_is_low:
        case eBT_0x11_OFF_Port_is_yet_undefined:
        case eBT_0x12_OFF_Internal_hardware_fault:
        case eBT_0x21_OFF_Internal_hardware_routing_error:
        case eBT_0x24_OFF_Voltage_injection_into_the_port:
        case eBT_0x26_OFF_Discharged_load:
        case eBT_0x35_OFF_Over_temperature_at_the_port:
        case eBT_0x36_OFF_Device_is_too_hot:
        case eBT_0x3C_OFF_Power_Mng_Static_calc_pwr_exceed_pwr_limit:
        case eBT_0x3D_OFF_Power_Management_Static_ovl:
        case eBT_0x41_OFF_Power_denied_Hardware_power_limit:
        case eBT_0x44_OFF_Port_turn_off_during_host_crash:
        case eBT_0x45_OFF_Delivering_power_forced_off_during_host_crash:
        case eBT_0x46_OFF_Enabled_port_forced_off_during_host_crash:
        case eBT_0x47_OFF_Forced_power_crash_error:
        case eBT_0x49_OFF_recovery_PG:
        case eBT_0x4C_OFF_recovery_voltage_injection:
        case eBT_0xA0_OFF_Force_Power_BT_Error:
        case eBT_0xFF_PORT_STATUS_ONKNOWN:
        {
            port_status->meba_poe_port_state = MEBA_POE_PSE_FAULT;
            break;
        }
        default:
        {
            // statuses to be mapped on higher software level:
            // MEBA_POE_NOT_SUPPORTED
            // MEBA_POE_UNKNOWN_STATE
            // MEBA_POE_DISABLED_INTERFACE_SHUTDOWN

            // This shall never happen all states should be covered.
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Port %d: Unknown port state: 0x%X",
                  inst->port_map[handle].port_no, port_state);
            port_status->meba_poe_port_state = MEBA_POE_UNKNOWN_STATE;
            break;
        }
    }

    if (port_status->meba_poe_port_state == MEBA_POE_PD_ON)
    {
        if((port_state == eBT_0x87_ON_4P_Port_delivering_4P_IEEE_DSPD_1st_phase) ||
           (port_state == eBT_0x88_ON_4P_Port_delivering_2P_IEEE_DSPD) ||
           (port_state == eBT_0x89_ON_4P_Port_delivering_4P_IEEE_DSPD)
          )
        {
		port_status->pd_type_sspd_dspd = 2;
        }
	else
        {
		port_status->pd_type_sspd_dspd = 1;
        }
	}
	else
    {
	     port_status->pd_type_sspd_dspd = 0;
    }

    if(( port_status->poe_internal_port_status == eBT_0x1C_OFF_Non_802_3AF_AT_powered_device)
    || ( port_status->poe_internal_port_status == eBT_0x1E_OFF_Underload_state)
    || ( port_status->poe_internal_port_status == eBT_0x25_OFF_Improper_Cap_Det_results_or_Det_val_indicating_short)
	|| ( port_status->poe_internal_port_status == eBT_0xA7_OFF_Connection_Check_error))
        port_status->is_fault_link_without_power = true;
    else
        port_status->is_fault_link_without_power = false;

    port_status->power_requested_mw = 0;
    //port_status->auto_class = 1 << 2; // We do support auto classanalyze

    // adding
    port_status->bt_port_operation_mode  = port_cfg_POEMCU->bt_port_operation_mode;
    port_status->bt_port_pm_mode         = port_cfg_POEMCU->bt_port_pm_mode;
    port_status->bt_pse_port_type        = port_cfg->bt_pse_port_type;

//    DEBUG(inst, MEBA_TRACE_LVL_INFO, "CH=%d ,bt_pse_port_type: 0x%X \n\r" ,handle ,port_status->bt_pse_port_type);

    if (port_status->meba_poe_ieee_port_state == MEBA_POE_IEEE_PORT_STATE_DELIVERING_POWER) {
        uint8_t  port_phy_info;
        uint8_t  measured_class;
        uint8_t  requested_class;
        uint16_t requested_power_dW;
        uint16_t assigned_power_dW = 0;
        uint8_t  auto_class_support;
        uint16_t auto_class_measurement_dw;

        // 'Get BT Class Power' driver
        MESA_RC(meba_poe_pd69200bt_ctrl_get_BT_port_class(
                    inst,
                    channel,
                    &port_state,
                    &port_phy_info,
                    &measured_class,
                    &requested_class,
                    &requested_power_dW,
                    &assigned_class,
                    &assigned_power_dW,
                    &auto_class_support,
                    &auto_class_measurement_dw));

        port_status->power_requested_mw = requested_power_dW * 100; // Convert from deciwatt to milliWatts
        port_status->pd_structure = port_phy_info & 0x0F;
        //port_status->poe_internal_port_status = port_state;

        port_status->power_assigned_mw = assigned_power_dW * 100; // Convert from deciwatt to milliWatts

        port_status->measured_pd_class_a = (measured_class & 0xF0) >> 4;
        if (port_status->measured_pd_class_a == 0xC) {
            port_status->measured_pd_class_a = -1;
        }

        port_status->measured_pd_class_b = measured_class & 0xF;
        if (port_status->measured_pd_class_b == 0xC) {
            port_status->measured_pd_class_b = -1;
        }

        port_status->requested_pd_class_a = (requested_class & 0xF0) >> 4;
        if (port_status->requested_pd_class_a == 0xC) {
            port_status->requested_pd_class_a = -1;
        }

        port_status->requested_pd_class_b = requested_class & 0xF;
        if (port_status->requested_pd_class_b == 0xC) {
            port_status->requested_pd_class_b = -1;
        }

        // auto_class_support = 0 : Autoclass detection not performed.
        // auto_class_support = 1 : The PD does not support physical auto class.
        // auto_class_support = 2 : The PD supports physical auto class.
        //port_status->autoclass_support = auto_class_support;

        if (auto_class_support == 0x2) {
            port_status->measured_autoclass_power_mw = auto_class_measurement_dw * 100; // Convert from deciwatt to milliWatts
        } else {
            port_status->measured_autoclass_power_mw = 0;
        }

        port_status->auto_class = auto_class_support ;
    }

    uint16_t main_voltage_dv = 0;
    mesa_poe_milliampere_t calculated_current_ma = 0;
    uint16_t port_power_consumption_dw = 0;
    uint16_t port_voltage_dv = 0;

    if (port_status->meba_poe_ieee_port_state == MEBA_POE_IEEE_PORT_STATE_DELIVERING_POWER) {
        meba_poe_pd69200bt_get_BT_port_measurements(
            inst,
            channel,
            &main_voltage_dv,
            &calculated_current_ma,
            &port_power_consumption_dw,
            &port_voltage_dv);
    }
    port_status->power_mw = port_power_consumption_dw * 100;  // dw -> mw
    port_status->current_ma = calculated_current_ma;
    port_status->voltage_mv = port_voltage_dv * 100;          // dv -> mv

    // Get BT Port Layer2 LLDP PSE Data
    uint16_t pse_allocated_power_a_or_single_dw;
    uint16_t pse_allocated_power_b_dw;
    uint16_t pse_max_power_dw;
    uint8_t  layer2_status;
    uint8_t  power_bits;
    uint8_t  cable_length_in_use;
    uint8_t  l2_cfg;

    MESA_RC(meba_poe_pd69200bt_ctrl_get_port_layer2_lldp_pse_data(
                inst,
                channel,
                &pse_allocated_power_a_or_single_dw,
                &pse_allocated_power_b_dw,
                &pse_max_power_dw,
                &assigned_class,
                &layer2_status,
                &power_bits,
                &cable_length_in_use,
                &l2_cfg));

    port_status->pse_data.power_pairs_control_ability = false;  // TODO assign real value
    port_status->pse_data.pse_max_avail_power_mw      = pse_max_power_dw * 100;
    port_status->pse_data.power_status                = (power_bits & 0x3) << 10 | (power_bits & 0xC) << 12;

    // update alt a,b and single allocated fields
    port_status->pse_data.pse_alloc_power_alt_a_mw = pse_allocated_power_a_or_single_dw * 100;
    port_status->pse_data.pse_alloc_power_alt_b_mw = pse_allocated_power_b_dw * 100;
    port_status->pse_data.pse_allocated_power_mw   = pse_allocated_power_a_or_single_dw * 100;

    // here we take the original requested power values we got from the lldp pd request packet
    port_status->pse_data.requested_power_mode_a_mw      = current_port_status->requested_power_mode_a_mw;
    port_status->pse_data.requested_power_mode_b_mw      = current_port_status->requested_power_mode_b_mw;
    port_status->pse_data.pd_requested_power_mw          = current_port_status->requested_power_single_mw;

    // These values are used to fill basic fields of LLDP frame
    switch (power_bits & 0x3) {
        case 0: // Undefined
            port_status->pse_data.pse_power_pair = 1;
            break;
        case 1: // Alternative A
            port_status->pse_data.pse_power_pair = 1;
            break;
        case 2: // Alternative B
            port_status->pse_data.pse_power_pair = 2;
            break;
        case 3: // Both alternatives
            port_status->pse_data.pse_power_pair = 1;
            break;
    }

    if (port_status->assigned_pd_class_a >= 4) {
        port_status->pse_data.power_class = 5; // Note: value 1:class=0. value 2:class=1, etc. 5 = Class 4 and above
    } else if (port_status->assigned_pd_class_a  < 0) {
        port_status->pse_data.power_class = 1;
    }

    // these values are used to fill DLL classification fields of LLDP frame

    // type << 6 | source << 4 | prio
    uint8_t type = 1; // alvays a PSE
    uint8_t source = 1; // Primary Power Souce

    port_status->pse_data.pse_power_type        =  type << 6 | source << 4 | port_cfg->priority;

    // I am not sure what to put here, so we use the sum

    // Proprietary parameter. Cable len in meters
    port_status->pse_data.cable_len             = cable_length_in_use;

//    Layer2 usage: Bits[3..0]
//        0x0 ? Port is not deliver power
//        0x1 ? Port deliver power, Using Layer1 (Assigned Class)
//        0x2 ? Port deliver power, Using Layer1 Autoclass
//        0x3 ? Port deliver power, using LLDP
//        0x4 ? Port deliver power, using LLDP Autoclass
//        0x5 ? Port deliver power, using CDP over 2P
//        0x6 ? Port deliver power, using CDP over 4P
//        0x7 ? Port is not deliver power and at reserve mode
//        0x8 ? Port deliver power, using reserve mode power

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "port_status->reserved_power_mw %d   port_status->power_mw=%d  port_status->pse_data.requested_power_single_mw =%d", port_status->reserved_power_mw ,port_status->power_mw , port_status->pse_data.pd_requested_power_mw);
    if ((layer2_status & 0xF) >= 3)
    {
        if(port_status->pd_type_sspd_dspd == 2) // DSPD
        {
            port_status->power_requested_mw = port_status->pse_data.requested_power_mode_a_mw + port_status->pse_data.requested_power_mode_b_mw;
            //printf("\n\r port_status->power_requested_mw=%d\n\r", port_status->power_requested_mw);
        }
        else //(port_status->pd_type_sspd_dspd == 1) // SSPD
        {
             port_status->power_requested_mw = port_status->pse_data.pd_requested_power_mw;
             //printf("\n\r port_status->pse_data.requested_power_single_mw=%d\n\r", port_status->pse_data.requested_power_single_mw);
        }
    }

    if ((layer2_status & 0xF) >= 3) {
        port_status->reserved_power_mw = port_status->power_requested_mw;
    } else {
        port_status->reserved_power_mw = port_status->power_mw;
    }

    port_status->system_setup = 2; // This value is specificed in Table 79-6f IEEE 803.2bt/D3.7  Type 3 PSE = 0. Type 4 PSE = 2.

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "CH=%d ,UNG status=%d ,intStatus=0x%X", handle , port_status->meba_poe_port_state , port_status->poe_internal_port_status);
    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200bt_ctrl_port_pd_data_set(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t     handle,
    meba_poe_pd_data_t         *pd_data)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    meba_poe_port_private_status_t* current_port_status = &(((poe_driver_private_t*)(inst->private_data))->status.ports[handle]);

    // Save requested power values in driver private data.
    // The request values are needed to construct LLDP to be sent to PD.
    current_port_status->requested_power_mode_a_mw = pd_data->pd_requested_power_mw;
    current_port_status->requested_power_mode_b_mw = pd_data->pd_requested_power_mw;
    current_port_status->requested_power_single_mw = pd_data->pd_requested_power_mw;

    meba_poe_port_cfg_t* port_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.ports[handle]);

    DEBUG(inst, MEBA_TRACE_LVL_INFO ,"UPDATE LLDP-AT: Set Max Power to %d mW. Cable length = %d meter\n\r",
           pd_data->pd_requested_power_mw, port_cfg->cable_length * 10);

    return meba_poe_pd69200bt_ctrl_set_port_layer2_lldp_pd_request(
        inst,
        handle,
        pd_data->pd_requested_power_mw / 100, // convert from milliwatt to deciwatt
        pd_data->pd_requested_power_mw / 100, // convert from milliwatt to deciwatt
        pd_data->pd_requested_power_mw / 100, // convert from milliwatt to deciwatt
        port_cfg->cable_length,               // 10 = 100m, 5=50m
        0);
}


mesa_rc meba_poe_pd69200bt_ctrl_port_pd_bt_data_set(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t     handle,
    meba_poe_pd_bt_data_t      *pd_data)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    meba_poe_port_cfg_t* port_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.ports[handle]);

    DEBUG(inst, MEBA_TRACE_LVL_INFO ,"UPDATE LLDP-BT: Set Max Power SINGLE=%d mW, ALT-A=%d mW, ALT-B=%d mW. Cable length = %d meter\n\r",
           pd_data->pd_requested_power_single_mw,
           pd_data->pd_requested_power_alt_a_mw,
           pd_data->pd_requested_power_alt_b_mw,
           port_cfg->cable_length * 10);

    meba_poe_port_private_status_t* current_port_status = &(((poe_driver_private_t*)(inst->private_data))->status.ports[handle]);

    // Save requested power values in driver private data.
    // The request values are needed to construct LLDP to be sent to PD.
    current_port_status->requested_power_mode_a_mw = pd_data->pd_requested_power_alt_a_mw;
    current_port_status->requested_power_mode_b_mw = pd_data->pd_requested_power_alt_b_mw;
    current_port_status->requested_power_single_mw = pd_data->pd_requested_power_single_mw;

    MESA_RC(meba_poe_pd69200bt_ctrl_set_port_layer2_lldp_pd_request(
                inst,
                handle,
                pd_data->pd_requested_power_single_mw / 100, // convert mW->dW
                pd_data->pd_requested_power_alt_a_mw / 100,  // convert mW->dW
                pd_data->pd_requested_power_alt_b_mw / 100,  // convert mW->dW
                port_cfg->cable_length,                      // 10 = 100m, 5=50m
                0));

    return MESA_RC_OK;

}

mesa_rc meba_poe_pd69200bt_ctrl_port_pd_data_clear(
    const meba_poe_ctrl_inst_t* const inst,
    meba_poe_port_handle_t          handle)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }
    
    meba_poe_port_cfg_t   *port_cfg   = &(((poe_driver_private_t*)(inst->private_data))->cfg.ports[handle]);

    // the Only way to disable LLDP is to disable PoE and then re-enable

    meba_poe_port_cfg_t req_port_cfg;

    req_port_cfg.enable           = false;
    req_port_cfg.bt_port_pm_mode  = port_cfg->bt_port_pm_mode;
    req_port_cfg.priority         = port_cfg->priority;
    req_port_cfg.legacy_support   = port_cfg->legacy_support;
    req_port_cfg.bt_pse_port_type = port_cfg->bt_pse_port_type;
    req_port_cfg.ignore_pd_auto_class_request = port_cfg->ignore_pd_auto_class_request;
    req_port_cfg.cable_length     = port_cfg->cable_length;

    // change only auto class state
    MESA_RC(meba_poe_pd69200bt_ctrl_port_cfg_set(
                inst,
                handle,
                &req_port_cfg));

    req_port_cfg.enable           = true;
    req_port_cfg.bt_port_pm_mode  = port_cfg->bt_port_pm_mode;
    req_port_cfg.priority         = port_cfg->priority;
    req_port_cfg.legacy_support   = port_cfg->legacy_support;
    req_port_cfg.bt_pse_port_type = port_cfg->bt_pse_port_type;
    req_port_cfg.ignore_pd_auto_class_request = port_cfg->ignore_pd_auto_class_request;
    req_port_cfg.cable_length     = port_cfg->cable_length;

     // change only auto class state
    MESA_RC(meba_poe_pd69200bt_ctrl_port_cfg_set(
                inst,
                handle,
                &req_port_cfg));

    meba_poe_port_private_status_t* current_port_status = &(((poe_driver_private_t*)(inst->private_data))->status.ports[handle]);

    current_port_status->requested_power_mode_a_mw = 0;
    current_port_status->requested_power_mode_b_mw = 0;
    current_port_status->requested_power_single_mw = 0;

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "port=%d clear requested_power_mode_a_mw = %d \n\r", handle, current_port_status->requested_power_single_mw);

    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200bt_chip_initialization(
    const meba_poe_ctrl_inst_t* const inst,
    mesa_bool_t interruptible_power,
    int16_t     restart_cause)
{
    mesa_bool_t bChangedFlag = false;
    mesa_bool_t bMatrixUpdatedFlag = false;

    meba_poe_global_cfg_t *current_global_cfg = &(((poe_driver_private_t*)(inst->private_data))->cfg.global);
    meba_poe_parameters_t tPoE_parameters = ((poe_driver_private_t *)(inst->private_data))->tPoE_parameters;

    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_ERROR;
    }

    // prod max poe ports must <= inst->port_map_length
    if( inst->port_poe_length > inst->port_map_length)
    {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s(%s): prod_max_poe_ports=%d is bigger then port_map_length=%d", __FUNCTION__, inst->adapter_name ,inst->port_poe_length ,inst->port_map_length);
        return MESA_RC_ERROR;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s: prod_max_poe_ports=%d", __FUNCTION__, inst->port_poe_length);
    uint16_t  power_consumption_w;
    uint16_t  max_shutdown_voltage_dv;
    uint16_t  min_shutdown_voltage_dv;
    uint8_t   guard_band;
    uint8_t   bank;
    uint16_t  power_limit_w;

    MESA_RC(pd69200_get_power_supply_parameters(
                inst,
                &power_consumption_w,
                &max_shutdown_voltage_dv,
                &min_shutdown_voltage_dv,
                &guard_band,
                &bank,
                &power_limit_w));

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s(%s): Prod_PwrSupply_MaxPwr=%d ,power_limit_w=%d ,current_global_cfg->primary_max_power_w=%d",
           __FUNCTION__, inst->adapter_name ,tPoE_parameters.poe_init_params.PwrSupply_MaxPwr ,power_limit_w,current_global_cfg->primary_max_power_w);

    current_global_cfg->primary_max_power_w = power_limit_w;

#ifdef SYNC_MISC_POE_PARAMS

  // I2C restart enable - Initializes the I2C module system after 10 seconds of inactivity.
    uint8_t i2c_restart_enable;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_I2C_RESTART_ENABLE, &i2c_restart_enable, "i2c_restart_enable"));
    if (i2c_restart_enable != tPoE_parameters.indv_mask_BT_i2c_restart_enable_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_I2C_RESTART_ENABLE, tPoE_parameters.indv_mask_BT_i2c_restart_enable_default));
        bChangedFlag = true;
    }

    // Turn off lowest priority port, when a higher priority has a PD connected.
    uint8_t ignore_high_priority;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_IGNORE_HIGHER_PRIORITY, &ignore_high_priority, "ignore_high_priority"));
    if (ignore_high_priority != tPoE_parameters.indv_mask_BT_ignore_higher_priority_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_IGNORE_HIGHER_PRIORITY, tPoE_parameters.indv_mask_BT_ignore_higher_priority_default));
        bChangedFlag = true;
    }

    // Support High res detection.
    uint8_t support_high_res_detection;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_SUPPORT_HIGH_RES_DETECTION, &support_high_res_detection, "support_high_res_detection"));
    if (support_high_res_detection != tPoE_parameters.indv_mask_BT_support_high_res_detection_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_SUPPORT_HIGH_RES_DETECTION, tPoE_parameters.indv_mask_BT_support_high_res_detection_default));
        bChangedFlag = true;
    }

    // Enable port poe led.
    uint8_t led_stream_type;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_LED_STREAM_TYPE, &led_stream_type, "led_stream_type"));
    if (led_stream_type != tPoE_parameters.indv_mask_BT_led_stream_type_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_LED_STREAM_TYPE, tPoE_parameters.indv_mask_BT_led_stream_type_default));
        bChangedFlag = true;
    }


    // HOCPP - high_over Current Pulse Protection
    uint8_t hocpp;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_HOCPP, &hocpp, "hocpp"));
    if (hocpp != tPoE_parameters.indv_mask_HOCPP_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_HOCPP, tPoE_parameters.indv_mask_HOCPP_default));
        bChangedFlag = true;
    }


    // PSE powering PSE checking
    uint8_t pse_powering_pse_checking;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_PSE_POWERING_PSE_CHECKING, &pse_powering_pse_checking, "pse_powering_pse_checking"));
    if (pse_powering_pse_checking != tPoE_parameters.indv_mask_PSE_powering_PSE_checking_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_PSE_POWERING_PSE_CHECKING, tPoE_parameters.indv_mask_PSE_powering_PSE_checking_default));
        bChangedFlag = true;
    }

    // Layer2 Power Allocation Limit.
    uint8_t layer2_power_allocation_limit;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_LAYER2_POWER_ALLOCATION_LIMIT, &layer2_power_allocation_limit, "layer2_power_allocation_limit"));
    if (layer2_power_allocation_limit != tPoE_parameters.indv_mask_layer2_power_allocation_limit_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_LAYER2_POWER_ALLOCATION_LIMIT, tPoE_parameters.indv_mask_layer2_power_allocation_limit_default));
        bChangedFlag = true;
    }

    // Port LED Blinks at invalid signature or connection-check error.
    uint8_t blinks_at_invalid_signature;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR, &blinks_at_invalid_signature, "blinks_at_invalid_signature"));
    if (blinks_at_invalid_signature != tPoE_parameters.indv_mask_Port_LED_blinks_at_invalid_signature_or_connection_check_error_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR, tPoE_parameters.indv_mask_Port_LED_blinks_at_invalid_signature_or_connection_check_error_default));
        bChangedFlag = true;
    }


    // Support adding lldp half priority.
    uint8_t support_lldp_half_priority;
    MESA_RC(meba_poe_pd69200_individual_mask_get(inst, INDV_MASK_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY, &support_lldp_half_priority, "support_lldp_half_priority"));
    if (support_lldp_half_priority != tPoE_parameters.indv_mask_support_adding_lldp_half_priority_default)
    {
        MESA_RC(meba_poe_pd69200_individual_mask_set(inst, INDV_MASK_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY, tPoE_parameters.indv_mask_support_adding_lldp_half_priority_default));
        bChangedFlag = true;
    }

#endif  //SYNC_MISC_POE_PARAMS

#ifdef POE_LLDP
    // update lldp pd data
    for (uint8_t i = 0; i < inst->port_map_length; i++)
    {
        if (inst->port_map[i].capabilities & MEBA_POE_PORT_CAP_POE)
        {
            //MESA_RC(meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(inst, i, 0, 0, 0, 0, 0));
            //MESA_RC(meba_poe_pd69200_ctrl_set_bt_port_layer2_lldp_pd_request(inst, i, 0, 0, 0, 0, 0));

            MESA_RC(meba_poe_pd69200bt_ctrl_set_port_layer2_lldp_pd_request(
                inst,
                i,
                0, // convert from milliwatt to deciwatt
                0, // convert from milliwatt to deciwatt
                0, // convert from milliwatt to deciwatt
                10, // corresponds to 100m
                3));
        }
    }
#endif  //POE_LLDP

    // Read active matrix and compare with intended matrix before programming it.
    // Get physical port number from active matrix
    if (pd69200_active_matrix_verify(inst, inst->port_poe_length) != MESA_RC_OK)
    {
        bMatrixUpdatedFlag = true;
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s(%s): PROGRAM MATRIX", __FUNCTION__, inst->adapter_name);
        MESA_RC(pd69200_program_global_matrix(inst));
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s(%s): PROGRAM MATRIX DONE", __FUNCTION__, inst->adapter_name);
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s restart_cause= %d ,ChangedFlag= %d ,bMatrixUpdatedFlag: %d ",  __FUNCTION__,restart_cause , bChangedFlag, bMatrixUpdatedFlag);

    // save settings if:
    // matrix was changed - or -
    // cold start and somthing was modified
    if ( bMatrixUpdatedFlag ||
        ((restart_cause == 0) && (bChangedFlag == true))) // cold start and somthing was modified
    {
         MESA_RC(meba_poe_pd69200_ctrl_save_command(inst));
         DEBUG(inst, MEBA_TRACE_LVL_INFO, "Save PoE settings");
    }

    if (interruptible_power)
    {
        uint8_t Port_Enable_Modes = (uint8_t)ePort_Disable;
        uint8_t Special_Port_Configuration_Bits_4_7 = current_global_cfg->global_ignore_pd_auto_class_request ;
        uint8_t CFG1 = Port_Enable_Modes | (Special_Port_Configuration_Bits_4_7 << 4);

        uint8_t BT_port_PM_mode = eBT_port_PM_mode_Do_not_change_settings;
        uint8_t Class_error_selection = eClass_error_Do_not_change_settings;
        uint8_t CFG2 = BT_port_PM_mode + (Class_error_selection << 4);

        uint8_t BT_port_Operation_Mode = eBT_Mode_No_change;
        uint8_t Add_power_for_port_mode_dW = MAX_ADDED_CLASS_POWER_dW;
        uint8_t Priority = ePORT_PRIORITY_NoChange;

        // 4.3.6        Set BT Port Parameters
        MESA_RC(meba_poe_pd69200bt_ctrl_set_BT_port_parameters(
            inst,
            0x80, // all ports
            CFG1,
            CFG2,
            BT_port_Operation_Mode,
            Add_power_for_port_mode_dW,
            Priority));

        /* Wait while ports turn off */
        VTSS_MSLEEP(INTERUPTIBLE_POE_OFF_TIME);
    }

    return MESA_RC_OK;
}

void meba_pd69200bt_driver_init(
    meba_poe_ctrl_inst_t* inst,
    char const* adapter_name,
    int                         adapter_fd,
    meba_poe_ctrl_cap_t         capabilities,
    meba_poe_port_properties_t* port_map,
    uint32_t                    port_map_length,
    meba_poe_psu_input_prob_t*  psu_map,
    uint32_t                    psu_map_length,
    meba_debug_t                debug,          // Board debug output
    meba_poe_parameters_t       tMeba_poe_parameters)
{
    int i;

    static meba_poe_ctrl_api_t meba_pd69200bt_api = {
        .meba_poe_ctrl_do_detection             = meba_poe_pd69200_do_detection,
        .meba_poe_ctrl_chip_initialization      = meba_poe_pd69200bt_chip_initialization,
        .meba_poe_ctrl_sync                     = meba_poe_pd69200_sync,
        .meba_poe_ctrl_reset_command            = meba_poe_pd69200_ctrl_reset_command,
        .meba_poe_ctrl_save_command             = meba_poe_pd69200_ctrl_save_command,
        .meba_poe_ctrl_version_get              = meba_poe_pd69200_ctrl_version_get,
        .meba_poe_ctrl_port_cfg_set             = meba_poe_pd69200bt_ctrl_port_cfg_set,
        .meba_poe_ctrl_port_status_get          = meba_poe_pd69200bt_ctrl_port_status_get,
        .meba_poe_ctrl_cfg_set                  = meba_poe_pd69200bt_ctrl_globals_cfg_set,
        .meba_poe_ctrl_status_get               = meba_poe_pd69200_ctrl_globals_status_get,
        .meba_poe_ctrl_debug                    = meba_poe_pd69200_ctrl_debug,
        .meba_poe_ctrl_firmware_upgrade         = meba_poe_pd69200_ctrl_firmware_upgrade,
        .meba_poe_ctrl_prepare_firmware_upgrade = meba_poe_pd69200_ctrl_prepare_firmware_upgrade,
        .meba_poe_ctrl_port_capabilities_get    = meba_poe_pd69200_ctrl_port_capabilities_get,
        .meba_poe_ctrl_port_pd_data_set         = meba_poe_pd69200bt_ctrl_port_pd_data_set,
        .meba_poe_ctrl_port_pd_bt_data_set      = meba_poe_pd69200bt_ctrl_port_pd_bt_data_set,
        .meba_poe_ctrl_port_pd_data_clear       = meba_poe_pd69200bt_ctrl_port_pd_data_clear,
    };

    poe_driver_private_t* private_data = malloc(sizeof(poe_driver_private_t));
    memset(private_data, 0, sizeof(*private_data));

    private_data->is_bt = true;
    private_data->debug = debug;
    private_data->tPoE_parameters = tMeba_poe_parameters;
    private_data->cfg.ports = malloc(sizeof(meba_poe_port_cfg_t) * port_map_length);
    private_data->cfg_POEMCU.ports = malloc(sizeof(meba_poe_port_cfg_t) * port_map_length);
    private_data->status.ports = malloc(sizeof(meba_poe_port_private_status_t) * port_map_length);

    memset(private_data->cfg.ports        ,0 ,sizeof(*(private_data->cfg.ports)));
    memset(private_data->cfg_POEMCU.ports ,0 ,sizeof(*(private_data->cfg_POEMCU.ports)));
    memset(private_data->status.ports     ,0 ,sizeof(*(private_data->status.ports)));

    private_data->status.global.chip_state = MEBA_POE_CHIPSET_DETECTION;

    for (i = 0; i < port_map_length; ++i) {
        private_data->cfg.ports[i].cable_length = 255;
    }

    private_data->cfg.global.primary_max_power_w = tMeba_poe_parameters.poe_init_params.PwrSupply_MaxPwr;; // Make sure initial value is different from configured value as configuration only is applied when values are different.
    inst->api = &meba_pd69200bt_api;
    inst->private_data = private_data;
    inst->adapter_fd = adapter_fd;
    inst->adapter_name = adapter_name;
    inst->capabilities = capabilities;
    inst->port_poe_length = tMeba_poe_parameters.poe_init_params.Max_POE_Ch;
    inst->port_map = port_map;
    inst->port_map_length = port_map_length;
    inst->psu_map = psu_map;
    inst->psu_map_length = psu_map_length;
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Done", __FUNCTION__);

    Set_BT_ParamsByOperationMode(inst);

    //POE_MAX_LOGICAL_PORTS = (inst->port_map_length / 8) * 8;
    //POE_MAX_LOGICAL_PORTS += (inst->port_map_length % 8) ? 8 : 0;

    //DEBUG(inst, MEBA_TRACE_LVL_INFO, "POE MAX LOGICAL PORTS= %d", POE_MAX_LOGICAL_PORTS);

    return;
}

