// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _OCELOT_POE_HW_CFG_H_
#define _OCELOT_POE_HW_CFG_H_

#include <stdio.h>
#include "microchip/ethernet/board/api.h"
#include "meba_poe_generic.h"
#include "poe_driver.h"

// ocelot has both BT and AT implementations

//--------------------------------------------------------------------------------------//
//------------------------------    general parameters   -------------------------------//
//--------------------------------------------------------------------------------------//

// This firmware can be used with the PD692x0 family of PoE controllers (PD69210, PD69220, and PD69200).
// please choose 'ePoE_Controller_Type_Unknown' for automatic firmware detection or force specific PD692x0 PoE controller
//
// MEBA_POE_PD692X0_CONTROLLER_TYPE_AUTO_DETECTION
// MEBA_POE_PD69200_CONTROLLER_TYPE ,
// MEBA_POE_PD69210_CONTROLLER_TYPE ,
// MEBA_POE_PD69220_CONTROLLER_TYPE ,
#define OCELOT_POE_PD692x0_CONTROLLER_TYPE_DEFAULT           MEBA_POE_PD692X0_CONTROLLER_TYPE_AUTO_DETECTION


// Set system mode BT or AT firmware:
// MEBA_POE_FIRMWARE_TYPE_AT - AF/AT mode
// MEBA_POE_FIRMWARE_TYPE_BT - BT mode
#define OCELOT_POE_FIRMWARE_TYPE_DEFAULT                      MEBA_POE_FIRMWARE_TYPE_BT


// Set unit max power as fixed or variable through Web & CLI
// User Conig 1=Yes,0=No
#define OCELOT_POE_UNIT_MAX_POWER_USER_CONFIG_DEFAULT         1


// Power Suply maximum Power (W)
#define OCELOT_POE_UNIT_MAX_POWER_W_DEFAULT                   150


// Power Suply default-Capability Power (W)
#define OCELOT_POE_UNIT_DEF_POWER_W_DEFAULT                   150


// set the PoE MCU controller I2C address (0x1 - 0xFE)
#define OCELOT_POE_I2C_ADDRESS                                0x20


// poe gpio reset pin number
// 0xFF   - no gpio use for reset poe ports.
// 0-0xFE - GPIO number used for reset poe ports.
#define OCELOT_RESET_POE_GPIO_NUMBER                          0xFF


//----------------- port map Customizations starts here ------------------//

// BT capability
#define PD69200BT_CAP  MEBA_POE_PORT_CAP_POE    | \
                       MEBA_POE_PORT_CAP_TYPE_1 | \
                       MEBA_POE_PORT_CAP_TYPE_2 | \
                       MEBA_POE_PORT_CAP_TYPE_3 | \
                       MEBA_POE_PORT_CAP_TYPE_4 | \
                       MEBA_POE_PORT_CAP_4PAIR  | \
                       MEBA_POE_PORT_CAP_FORCE_ON

// AT capability
#define PD69200AT_CAP   MEBA_POE_PORT_CAP_POE    | \
                        MEBA_POE_PORT_CAP_TYPE_1 | \
                        MEBA_POE_PORT_CAP_TYPE_2 | \
                        MEBA_POE_PORT_CAP_TYPE_3 | \
                        MEBA_POE_PORT_CAP_FORCE_ON

#define PD69200_CAP ((OCELOT_POE_FIRMWARE_TYPE_DEFAULT == MEBA_POE_FIRMWARE_TYPE_BT) ? PD69200BT_CAP : PD69200AT_CAP)

// pd69200 - AT mapping - 8 PoE ports 2-pairs
meba_poe_port_properties_t ocelot_pd69200AT_port_map[] =
{
//  PoE         | Max   | App-Log | PoE-Log | PoE Pair-A   | PoE Pair-B
//  Capability  | PWR   | Port-ID | Port-ID | Phys Port-ID | Phys Port-ID
//---------------------------------------------------------------------------
  { PD69200_CAP , 24000 , 0       , 0       , 3            , 255         },
  { PD69200_CAP , 24000 , 1       , 1       , 1            , 255         },
  { PD69200_CAP , 24000 , 2       , 2       , 7            , 255         },
  { PD69200_CAP , 24000 , 3       , 3       , 5            , 255         },
  { PD69200_CAP , 24000 , 4       , 4       , 4            , 255         },
  { PD69200_CAP , 24000 , 5       , 5       , 6            , 255         },
  { PD69200_CAP , 24000 , 6       , 6       , 0            , 255         },
  { PD69200_CAP , 24000 , 7       , 7       , 2            , 255         }
};

//------------------- cap and port map Customizations ends here --------------------//


//--------------------------------------------------------------------------------------//
//-------------------------    BT parameters    ----------------------------------------//
//--------------------------------------------------------------------------------------//


// BT System has 4 modes = 15/30/60/90 (applicable for all poe ports)
// MEBA_POE_PORT_MAX_POWER_15W
// MEBA_POE_PORT_MAX_POWER_30W
// MEBA_POE_PORT_MAX_POWER_60W
// MEBA_POE_PORT_MAX_POWER_90W
#define OCELOT_BT_PORT_MAX_POWER_DEFAULT                     MEBA_POE_PORT_MAX_POWER_30W


// Port Operation Mode for legacy
// This parameter sets a combination of various port behaviors: Legacy detection, port power, classification fingers, and 4-pair operation.
// see Microchip PD692x0 BT Serial Communication Protocol Table 3-5. 4-Pair/2-Pair Non-Compliant Modes

#define OCELOT_BT_OPERATION_MODE_LEGACY_90W_POH_DEFAULT              0x25  // Lagacy + PoH 45/90W + BT. No demotion in class 4 or 4,4
#define OCELOT_BT_OPERATION_MODE_LEGACY_60W_IGNORE_PD_CLASS_DEFAULT  0x21  // Lagacy + IGNORE_PD_CLASS 60W
#define OCELOT_BT_OPERATION_MODE_LEGACY_90W_IGNORE_PD_CLASS_DEFAULT  0x26  // Lagacy + IGNORE_PD_CLASS 90W


// '0' The allocation logic before classification sums the delivering power ports with
//     lower priority and adds the result to the available power. After classification, the
//     disconnection function executes and may disconnect lower priority ports to free
//     power for the higher priority port.
// '1' If power is not available for powering-up any port, any new connected port
//     power-up is denied, regardless of its priority.
#define OCELOT_INDV_MASK_BT_IGNORE_HIGHER_PRIORITY_DEFAULT     0


// '0' Resistor detection range at normal range, according to the IEEE 802.3bt.
// '1' Open the upper range to 55 K? at 2-pair logical port only.
//     Notes:
//     - This feature will not operate on any 4-pair logical port.
//     - When this mask is set, the capability of PSE Connected to PSE Protection function is reduced.
#define OCELOT_INDV_MASK_BT_SUPPORT_HIGH_RES_DETECTION_DEFAULT 1


// '0' Do not initialize the I2C module in case of inactivity.
// '1' Initializes the I2C module system after 10 seconds of inactivity.
#define OCELOT_INDV_MASK_BT_I2C_RESTART_ENABLE_DEFAULT         1


// 0 LED stream is disabled.
// 1 LED stream supports unicolor BT.
// 2 LED stream supports Bicolor BT.
// 3 For Microchip internal use only (NTGR).
// 4 For Microchip internal use only (Direct).
// 5 Reserved for future:
//   Direct led function (for 1 port Midspan products).
//   Vmain LED is driven from the PD692x0 (xSYS_OK, pin 32), and Port LED
//   is driven from the PD69208 LED port (PD69200 BT LED definitions internal document).
// 6 Direct led function from PD69208 LED ports (for 1 port Midspan products).
//   3 LEDs in the same package.
// 7 Direct led function from PD69208 LED ports (for 1 port Midspan products).
//   1 package for 2P and 4P LED operation.
//   Another package for SYS OK pin.
#define OCELOT_INDV_MASK_BT_LED_STREAM_TYPE_DEFAULT            2


// HOCPP - High Over Current Pulse Protection
// 0 = Internal port startup check duration is 500 ms and HOCPP is enabled immediately (0 ms) after port power-up.
// 1 = Internal port startup check duration is 500 ms and HOCPP is enabled at the end of this time duration.
// 2 = Internal port startup check duration is 1000 ms and HOCPP is enabled at the end of this time duration.
// 3 = Internal port startup check duration is 1500 ms and HOCPP is enabled at the end of this time duration.
// 4 = Internal port startup check duration is 2000 ms and HOCPP is enabled at the end of this time duration.
#define OCELOT_INDV_MASK_BT_HOCPP_DEFAULT                 2


//PSE powering PSE checking
// 0 = PSE powering PSE condition does not deny powering new valid ports.
// 1 = In case PSE powering PSE condition occurs, no additional ports are poweredup, until this problem is resolved.
#define OCELOT_INDV_MASK_BT_PSE_POWERING_PSE_CHECKING_DEFAULT          1


// Layer2 Power Allocation Limit
// 0 = Power allocation limit up to requested class (non-BT compliant).
// 1 = Power allocation limit up to minimum between the requested class and the operation mode (BT compliant).
#define OCELOT_INDV_MASK_BT_LAYER2_POWER_ALLOCATION_LIMIT_DEFAULT      1


// Port LED Blinks at invalid signature or connection-check error
// 0 = When port detects invalid signature or connection-check error, LED stays off.
// 1 = When port detects invalid signature or connection-check error, LED blinks.
#define OCELOT_INDV_MASK_BT_PORT_LED_BLINKS_AT_INVALID_SIGNATURE_OR_CONNECTION_CHECK_ERROR_DEFAULT 0


// Support_adding lldp_half_priority
// 0 = Port at LLDP does not have additional half priority.
// 1 = Port at LLDP has additional half priority compared to non LLDP port at the same priority settings.
#define OCELOT_INDV_MASK_BT_SUPPORT_ADDING_LLDP_HALF_PRIORITY_DEFAULT   1


//--------------------------------------------------------------------------------------//
//-------------------------    AT parameters    ----------------------------------------//
//--------------------------------------------------------------------------------------//


// '0' If higher priority port powers up and its power exceeds power limit,
//     a lowest priority port will be disconnected instead.
// '1' If power is not available for powering up any port,
//     any new connected port power up will be denied, regardless of its priority.
#define OCELOT_INDV_MASK_AT_IGNORE_HIGHER_PRIORITY_DEFAULT     0


// '0' Don?t support legacy detection.
// '1' Support legacy detection.
#define OCELOT_INDV_MASK_AT_SUPPORTS_LEGACY_DETECTION_DEFAULT  0


// '0' Disables notification.
// '1' MESSAGE_READY pin, can be used to notify the host that a reply message is ready.
//     Refer to PD69200 datasheet or PD69200M shared memory documentation.
#define OCELOT_INDV_MASK_AT_MESSAGE_READY_NOTIFY_DEFAULT       0


// '0' Layer 2 PD commands will be Ignored and Layer 2 PSE requests will return with zero allocation.
// '1' Layer 2 operation is enabled. Layer 2 commands are processed.
#define OCELOT_INDV_MASK_AT_LAYER2_LLDP_ENABLE_DEFAULT         1


// '0' Priority information received from LLDP/CDP PD message is ignored. (Mask 0x2E must be '1').
// '1' Port Priority can be defined by PD. (Mask 0x2E must be '1').
#define OCELOT_INDV_MASK_AT_LAYER2_PRIORITY_BY_PD_DEFAULT      1


// '0' Uses old matrix command (2-pair).
// '1' Uses new 4-pair matrix commands.
#define OCELOT_INDV_MASK_AT_MATRIX_SUPPORT_4P_DEFAULT          1


// -----------  Legacy Power Management mode of operation  ----------------------//

// PM1: Selects the method of calculating total power consumption.
// PM2: Selects the power limit at the port (maximum or according to class or predefined).
// PM3: Selects the start condition. (Not recommended for new designs, keep 0x00).

// PM-1 How to calculate system power
//  0x00 - Full Dynamics (Consumption).
//  0x01 - LLDP & Classes 1 to 3 = Static power (TPPL), Classes 0,4 = Dynamic.
//  0x02 - LLDP & Classes 0 to 3 = Static power (TPPL), Class 4 = Dynamic.
//  0x03 - LLDP & Classes 1 to 4 Static power (TPPL), Class 0 = Dynamic.
//  0x04 - LLDP & Classes 0 to 4 = Static power (TPPL).
//  0x05 - LLDP = Static power (TPPL), Non LLDP = Dynamic.
//  0x06 - LLDP & classes 4 = Static power (TPPL), Classes 0 to 3 = Dynamic.
//  0x80 - User defined per port (See 4.3.12, Sum_as_TPPL field).
#define OCELOT_PM1_AT_DEFAULT             0x05


//PM-2 Port Power Limit
//  0 - Table set by the user (PPL)
//  1 - Class power Limit ? (*)
//      Port Behavior Equal AF: Class 1 power = 5w or 4w
//          Class 2 power = 8w or 7w
//          Class 0,3,4 power = 16.4w or 15.4w Port Behavior Equal AT:
//          Class 0 to 4 power = 33w or 32w or 30w
//      Port Behavior Equal POH:
//          Class 0 to 4 power = 48.7w
// Note: 1. In 4-pair delivering port, the above power values are doubled.
//       2. The power values are pre-defined as part of the release and may change between releases.
//  2 - ICUT Max (According to port behavior) ? (*)
//      AF - 375mA
//      AT ? 644mA
//      POH ? 995mA
// Note: (*). In 4-pair delivering port, the above power values are doubled.
//  3 - PPL_Class_Max (The maximum value between PPL and Class).
//  0x80 - User defined per port (See 4.3.12, PortPM2 nibble field).
#define OCELOT_PM2_AT_DEFAULT             0x01


//PM-3 Start up conditions: The port will not start up in case detected class power is higher than PPL Value
//  0 - No Condition   Capability
//  1 - Condition on Classes 1 to 3
//  2 - Condition on Classes 0 to 3
//  3 - Condition on Classes 1 to 4
//  4 - Condition on Classes 0 to 4
//  0x80 ? User defined per port (See 4.3.12, PortPM3 nibble field)
//Note: 1. Class power for startup condition is according to the class power
//         parameters in the release_DB regardless of other masks settings.
//      2. Other values for this field will be ignored, maintaining the last configuration.
#define OCELOT_PM3_AT_DEFAULT             0x00

#endif // _OCELOT_POE_HW_CFG_H_
