// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <microchip/ethernet/board/api.h>

#include "meba_aux.h"

#define SYNCE_STATION_CLOCK_IN_PIN  12  // GPIO used as station clock input
#define SYNCE_STATION_CLOCK_OUT_PIN 33  // GPIO used as station clock output
#define SYNCE_PTP_CLOCK_OUTPUT       1  // Clock output used for PTP independent Phase/Frequency adjustment
#define SYNCE_HO_POST_FILTERING_BW 8898 // Default holdover post filtering
#define SYNCE_CLOCK_DPLL             0  // DPLL number for the DPLL used for SYNCE
#define SYNCE_CLOCK_OUTPUT_CNT       4  // Number of clock output references, including 10G ports, which must be connected to the controller outputs
#define SYNCE_CLOCK_EEC_OPTION_CNT   2  // Number of EEC options that can be selected
#define SYNCE_RECVRD_CLK_SRC         5  // 22: Select GPIO reference 0(5+17) is added to this value to select REF_CLK0 from clock MUX
#define SYNCE_RECVRD_CLK_ID          3  // RCVRD_CLK3, configured by overlaid function SYNC_ETH_CFG[3]
#define SYNCE_RECVRD_CLK_3_PIN      36  // GPIO used as RCVRD_CLK3

/** \brief Number of Jaguar2 PTP pins, that can be used as 1PPS or clock output/input. */
#define VTSS_TS_IO_ARRAY_SIZE       4

/*
 *  The status LED is attached through the SGPIO interface, bits p6.2
 *  and p6.3 (green, red).
 */

#define STATUS_GREEN_PORT 6
#define STATUS_GREEN_BIT  2

#define STATUS_RED_PORT   6
#define STATUS_RED_BIT    3

#define MAX_PORTS         9

/* LED tower mode */
typedef enum {
    LED_TOWER_MODE_LINK_SPEED,      /**< Green: 1G link/activity; Orange: 10/100 link/activity */
    LED_TOWER_MODE_DUPLEX_SPEED,    /**< Green: FDX; Orange: HDX + Collisions */
    LED_TOWER_MODE_LINK_STATUS,     /**< Green: Link/activity; Orange: port disabled/errors */
    LED_TOWER_MODE_POWER_SAVE,      /**< Disabled to save power */
    LED_TOWER_MODE_CNT
} led_tower_mode_t;

typedef struct {
    meba_port_entry_t    map;
    mesa_port_counter_t  port_collision_cnt;
    mesa_port_status_t   status;
    mesa_bool_t          activity;
    led_tower_mode_t     led_tower_mode_old;
    mesa_bool_t          pre_collision_state, enable_old;
} servalt_port_info_t;

typedef struct meba_board_state {
    int                   port_cnt;
    int                   ports_1g, ports_2_5g, ports_10g;
    led_tower_mode_t      led_tower_mode;
    servalt_port_info_t   *port;
    const mesa_fan_conf_t *fan_spec;
    mepa_device_t        *phy_devices[MAX_PORTS];
} meba_board_state_t;

static const mesa_fan_conf_t fan_conf = {
    .fan_pwm_freq = MESA_FAN_PWM_FREQ_25KHZ,   // 25kHz
    .fan_low_pol = 0,                          // active low
    .fan_open_col = true,                      // Open collector
    .type = MESA_FAN_3_WIRE_TYPE,              // 3-wire
    .ppr = 2,                                  // 2 PPR
};

static const meba_ptp_rs422_conf_t rs422_conf = {
    .gpio_rs422_1588_mstoen = 14,
    .gpio_rs422_1588_slvoen = 15,
    .ptp_pin_ldst           = 2,
    .ptp_pin_ppso           = 3,
    .ptp_rs422_pps_int_id   = MEBA_EVENT_PTP_PIN_2,
    .ptp_rs422_ldsv_int_id  = MEBA_EVENT_PTP_PIN_3
};

static const uint32_t pin_conf[VTSS_TS_IO_ARRAY_SIZE] = {
(MEBA_PTP_IO_CAP_PIN_IN | MEBA_PTP_IO_CAP_PIN_OUT),
 MEBA_PTP_IO_CAP_PIN_IN,
(MEBA_PTP_IO_CAP_TIME_IF_IN | MEBA_PTP_IO_CAP_PIN_IN),
 MEBA_PTP_IO_CAP_TIME_IF_OUT
};

static const meba_event_t init_int_source_id[VTSS_TS_IO_ARRAY_SIZE] = {MEBA_EVENT_PTP_PIN_0, MEBA_EVENT_PTP_PIN_1, MEBA_EVENT_PTP_PIN_2, MEBA_EVENT_PTP_PIN_3};

/* SGPIO LED mapping */
typedef struct {
    uint8_t port;
    uint8_t bit;
} sgpio_mapping_t;

static const sgpio_mapping_t tower_led_mapping[4][2] = {
    {{2, 2} /* tower 0 green */, {2, 3} /* tower 0 yellow */},
    {{3, 2} /* tower 1 green */, {3, 3} /* tower 1 yellow */},
    {{4, 2} /* tower 2 green */, {4, 3} /* tower 2 yellow */},
    {{5, 2} /* tower 3 green */, {5, 3} /* tower 3 yellow */}
};

static uint32_t servalt_capability(meba_inst_t inst,
                                   int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_POE:
        case MEBA_CAP_1588_CLK_ADJ_DAC:
        case MEBA_CAP_1588_REF_CLK_SEL:
            return false;
        case MEBA_CAP_TEMP_SENSORS:
            return 1;
        case MEBA_CAP_BOARD_PORT_COUNT:
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            // On this platform port count and port map count are identical (no loop ports)
            return board->port_cnt;
        case MEBA_CAP_LED_MODES:
            return LED_TOWER_MODE_CNT;
        case MEBA_CAP_DYING_GASP:
            return true;
        case MEBA_CAP_FAN_SUPPORT:
            return false;
        case MEBA_CAP_LED_DIM_SUPPORT:
            return false;
        case MEBA_CAP_BOARD_HAS_PCB107_CPLD:
            return false;
        case MEBA_CAP_PCB107_CPLD_CS_VIA_MUX:
            return false;
        case MEBA_CAP_BOARD_HAS_PCB135_CPLD:
            return false;
        case MEBA_CAP_SYNCE_PTP_CLOCK_OUTPUT:
            return SYNCE_PTP_CLOCK_OUTPUT;
        case MEBA_CAP_SYNCE_HO_POST_FILTERING_BW:
            return SYNCE_HO_POST_FILTERING_BW;
        case MEBA_CAP_SYNCE_CLOCK_DPLL:
            return SYNCE_CLOCK_DPLL;
        case MEBA_CAP_SYNCE_CLOCK_OUTPUT_CNT:
            return SYNCE_CLOCK_OUTPUT_CNT;
        case MEBA_CAP_SYNCE_CLOCK_EEC_OPTION_CNT:
            return SYNCE_CLOCK_EEC_OPTION_CNT;
        case MEBA_CAP_ONE_PPS_INT_ID:
            return MEBA_EVENT_PTP_PIN_1;
        case MEBA_CAP_SYNCE_DPLL_MODE_SINGLE:      // ServalT supports single DPLL mode but Serval2 Lite does not
            if (MESA_CAP(MESA_CAP_CLOCK)) {
                return true;                       // Serval T
            } else {
                return false;                      // Serval2 Lite
            }
        case MEBA_CAP_SYNCE_DPLL_MODE_DUAL:        // ServalT and Serval2 Lite both support single DPLL mode
            return true;
        case MEBA_CAP_POE_BT:
            return false;
        case MEBA_CAP_SYNCE_STATION_CLOCK_MUX_SET:
            return false;
        case MEBA_CAP_CPU_PORTS_COUNT:
            return 0;
        case MEBA_CAP_BOARD_PORT_POE_COUNT:
            return 0;
        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc servalt_port_entry_init(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       meba_port_entry_t *entry)
{
    mesa_rc rc;
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called");
    if (port_no < board->port_cnt) {
        if (port_no < board->ports_1g) {
            entry->map.chip_port           = port_no;
            entry->map.max_bw              = MESA_BW_1G;
            if (port_no < 2) {
                /* Port 0-3: Copper ports, chip port 0-3 */
                entry->map.miim_addr       = port_no;
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_0;
                entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
                entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER | MEBA_PORT_CAP_INT_PHY;
                entry->cap                &= ~(MEBA_PORT_CAP_10M_HDX | MEBA_PORT_CAP_100M_HDX); // BZ20946: half-duplex not supported
            } else {
                entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
                entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
                entry->cap                 = MEBA_PORT_CAP_SFP_1G | MEBA_PORT_CAP_SFP_SD_HIGH;
            }
        } else if (port_no == board->port_cnt - 1) {
            /* Port 6/8/10: NPI port, chip port 4 */
            entry->map.chip_port       = 4;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_1;
            entry->map.miim_addr       = 28;
            entry->map.max_bw          = MESA_BW_1G;
            entry->mac_if              = MESA_PORT_INTERFACE_SGMII;
            entry->cap                 = MEBA_PORT_CAP_TRI_SPEED_COPPER;
        } else if (port_no < (board->ports_1g + board->ports_2_5g)) {
            /* Port 4-5 or 4-7: 2.5G SFP, chip port 5-6 or 5-8 */
            entry->map.chip_port       = port_no + 1;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_2G5;
            entry->mac_if              = MESA_PORT_INTERFACE_SERDES;
            entry->cap                 = MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_SFP_SD_HIGH;
        } else {
            /* Port 6-7 or 8-9: SFP+, chip port 9-10 */
            entry->map.chip_port       = port_no + 1 + board->ports_1g - board->ports_2_5g;
            entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
            entry->map.max_bw          = MESA_BW_10G; // 10G
            entry->mac_if              = MESA_PORT_INTERFACE_SFI;
            entry->cap                 = MEBA_PORT_CAP_10G_FDX | MEBA_PORT_CAP_SFP_2_5G | MEBA_PORT_CAP_FLOW_CTRL | MEBA_PORT_CAP_SFP_SD_HIGH | MEBA_PORT_CAP_SERDES_TX_INVERT;
        }
        rc = MESA_RC_OK;
    } else {
        rc = MESA_RC_ERROR;
    }
    return rc;
}

static mesa_rc servalt_port_entry_get(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      meba_port_entry_t *entry)
{
    mesa_rc rc;
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called");
    if (port_no < board->port_cnt) {
        *entry = board->port[port_no].map;
        rc = MESA_RC_OK;
    } else {
        rc = MESA_RC_ERROR;
    }
    T_N(inst, "Called(%d): rc %d - chip %d, miim bus %d, addr: %d", port_no, rc,
        entry->map.chip_port, entry->map.miim_controller, entry->map.miim_addr);
    return rc;
}

static mesa_rc servalt_reset(meba_inst_t inst,
                             meba_reset_point_t reset)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;
    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            {
                mesa_sgpio_conf_t conf;
                uint32_t port, gpio_no;

                // Configure GPIOs for MIIM/MDIO
                for (gpio_no = 22; gpio_no <= 23; gpio_no++) {
                    (void)mesa_gpio_mode_set(NULL, 0, gpio_no, MESA_GPIO_ALT_0);
                }

                /* GPIO pins 0-3 are used for SGPIOs. */
                (void)mesa_gpio_mode_set(NULL, 0, 0, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / CLK
                (void)mesa_gpio_mode_set(NULL, 0, 1, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DO
                (void)mesa_gpio_mode_set(NULL, 0, 2, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / DI
                (void)mesa_gpio_mode_set(NULL, 0, 3, MESA_GPIO_ALT_0);  // SGPIO Grp 0 / LD

                /* Setup SGPIO group 0          */
                /* Controls Port LEDs 1-8 + NPI */
                if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
                    /* The blink mode 0 is 5 HZ for link activity and collisions in half duplex. */
                    conf.bmode[0] = MESA_SGPIO_BMODE_5;
                    conf.bit_count = 4;
                    // Turn the LEDs initially off
                    for (port = 0; port <= 6; port++) {
                        conf.port_conf[port].enabled = true;
                        conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_OFF;
                        conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF;
                    }
                    for (port = 9; port <= 10; port++) {
                        conf.port_conf[port].enabled = true;
                        conf.port_conf[port].mode[0] =  MESA_SGPIO_MODE_OFF;
                        conf.port_conf[port].mode[1] =  MESA_SGPIO_MODE_OFF;
                    }
                    // Enable RateSel/TxDisable ports
                    for (port = 11; port <= 15; port++) {
                        conf.port_conf[port].enabled = true;
                    }

                    // Status LED ON
                    conf.port_conf[6].mode[2] =  MESA_SGPIO_MODE_ON;
                    conf.port_conf[6].mode[3] =  MESA_SGPIO_MODE_OFF;

                    /* SFP RateSel = enabled    */
                    conf.port_conf[12].mode[0] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[12].mode[1] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[12].mode[2] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[12].mode[3] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[13].mode[0] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[13].mode[1] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[13].mode[2] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[13].mode[3] = MESA_SGPIO_MODE_ON;

                    /* SFP TxDisable = enabled    */
                    conf.port_conf[14].mode[0] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[14].mode[1] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[14].mode[2] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[14].mode[3] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[15].mode[0] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[15].mode[1] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[15].mode[2] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[15].mode[3] = MESA_SGPIO_MODE_ON;

                    for (port = 0; port < 12; port++) {
                        if (port == 4 || (port > 6 && port < 9)) {
                            continue;
                        }

                        if (board->ports_10g == 0 && port > 8) {
                            continue;
                        }

                        conf.port_conf[port].int_pol_high[0] = true; // LOS is active high.
                        conf.port_conf[port].int_pol_high[1] = true; // TX_FAULT is active high.
                    }

                    conf.port_conf[4].int_pol_high[1] = true; // SFP10 TX_FAULT

                    rc =mesa_sgpio_conf_set(NULL, 0, 0, &conf);
                }
            }
            // Initialize GPIO, clock divider etc. used by the station clock input/output
            {
                mesa_synce_station_clock_out_t station_clk_conf;
                void *const CLOCK_API_INST = 0;

                // GPIO used for Station clock input
                if ((rc = mesa_gpio_mode_set(NULL, 0, SYNCE_STATION_CLOCK_IN_PIN, MESA_GPIO_ALT_0)) != MESA_RC_OK) {
                    T_W(inst, "Could not configure GPIO for station clock input. Error code was: %x", rc);
                }

                // GPIO used for Station clock output
                if ((rc = mesa_gpio_mode_set(NULL, 0, SYNCE_RECVRD_CLK_3_PIN, MESA_GPIO_ALT_0)) != MESA_RC_OK) {
                    T_W(inst, "Could not configure GPIO for station clock output. Error code was: %x", rc);
                }

                station_clk_conf.divider = MESA_SYNCE_DIVIDER_1;
                station_clk_conf.enable = true;
                station_clk_conf.dpll_out_no = SYNCE_RECVRD_CLK_SRC;
                if ((rc = mesa_synce_synce_station_clk_out_set(CLOCK_API_INST, SYNCE_RECVRD_CLK_ID, &station_clk_conf)) != MESA_RC_OK) {
                    T_W(inst, "Could not configure station clock output (divider, enable, etc.). Error code was: %x", rc);
                }
            }
            break;
        case MEBA_PORT_RESET:
            break;
        case MEBA_PORT_RESET_POST:
            rc = vtss_phy_post_reset(PHY_INST, 0);
            break;
        case MEBA_STATUS_LED_INITIALIZE:
        case MEBA_PORT_LED_INITIALIZE:
            break;
        case MEBA_FAN_INITIALIZE:
            rc = mesa_fan_controller_init(NULL, board->fan_spec);
            break;
        case MEBA_SENSOR_INITIALIZE:
            rc = vtss_phy_chip_temp_init(PHY_INST, 0);
            break;
        case MEBA_INTERRUPT_INITIALIZE:
            break;
        case MEBA_SYNCE_DPLL_INITIALIZE:
            {
                void *const CLOCK_API_INST = 0;
                mesa_rc rc;
                
                // initialize the OMEGA IP 
                if ((rc = mesa_clock_global_enable_set(CLOCK_API_INST, true)) != MESA_RC_OK) {
                    T_W(inst, "Could not do global clock enable. Error code was: %x", rc);
                }
        
                if ((rc = mesa_clock_global_sw_reset(CLOCK_API_INST)) != MESA_RC_OK) {
                    T_W(inst, "Could not do global clock sw reset. Error code was: %x", rc);
                }

                // enable DPLL 0 for synce use.
                mesa_clock_dpll_conf_t conf;
                conf.mode = MESA_CLOCK_OPERATION_MODE_ENABLED;
                conf.holdoff = 0;       // Holdoff disabled as default
                conf.holdover = 0;      // Not sure what it means ?
                conf.wtr = 0;           // default WTR value is 0 as it is not supported in ServalT rev 1
                if ((rc = mesa_clock_operation_conf_set(CLOCK_API_INST, SYNCE_CLOCK_DPLL, &conf)) != MESA_RC_OK) {
                    T_W(inst, "Could not do clock operation configuration set. Error code was: %x", rc);
                }
        
                // work around to avoid very long waiting time before entering Locked state
                mesa_clock_ho_stack_conf_t ho_conf;
                ho_conf.ho_post_filtering_bw = SYNCE_HO_POST_FILTERING_BW;
                ho_conf.ho_qual_time_conf = 0;
                if ((rc = mesa_clock_ho_stack_conf_set(CLOCK_API_INST, SYNCE_CLOCK_DPLL, &ho_conf)) != MESA_RC_OK) {
                    T_W(inst, "Could not do HO stack configuration set. Error code was: %x", rc);
                }
        
                // connect output 0 and 1 to DPLL 0
                mesa_clock_input_selector_t input;
                input.input_type = MESA_CLOCK_INPUT_TYPE_DPLL;
                input.input_inst = 0;
                uint8_t clock_out;
                for (clock_out = 0; clock_out < SYNCE_CLOCK_OUTPUT_CNT; clock_out++) {
                    input.input_type = (clock_out == SYNCE_PTP_CLOCK_OUTPUT) ? MESA_CLOCK_INPUT_TYPE_PURE_DCO : MESA_CLOCK_INPUT_TYPE_DPLL;
                    if ((rc = mesa_clock_output_selector_set(CLOCK_API_INST, clock_out, &input)) != MESA_RC_OK) {
                        T_W(inst, "Could not do clock output selector set for clock output %d. Error code was: %x", clock_out, rc);
                    }
                }
        
                // default clock input 0 and 1 frequency is 125 MHz
                // set alarm and GST configuration
                mesa_clock_input_conf_t alarm_conf;
                mesa_clock_gst_conf_t gst_conf;
                mesa_clock_pfm_conf_t pfm_conf;
                mesa_clock_cfm_conf_t cfm_conf;
                alarm_conf.los_active_high = true;
                alarm_conf.alarm_ena.los = true;
                alarm_conf.alarm_ena.pfm = true;
                alarm_conf.alarm_ena.cfm = true;
                alarm_conf.alarm_ena.scm = true;
                alarm_conf.alarm_ena.gst = true;
                alarm_conf.alarm_ena.lol = true;
                gst_conf.disqualification_time_us = 100;
                gst_conf.qualification_time_us = 100;
                gst_conf.los = true;
                gst_conf.pfm = true;
                gst_conf.cfm = true;
                gst_conf.scm = true;
                gst_conf.lol = true;
                pfm_conf.pfm_set_ppb =  9700;
                pfm_conf.pfm_clr_ppb =  9300;
                cfm_conf.cfm_set_ppb = 50000;
                cfm_conf.cfm_clr_ppb = 40000;
                uint8_t clock_in;
                for (clock_in = 0; clock_in < 2; clock_in++) {
                    if ((rc = mesa_clock_input_frequency_set(CLOCK_API_INST, clock_in, 125000, true)) != MESA_RC_OK) {
                        T_W(inst, "Could not do clock input frequency set for clock input %d. Error code was: %x", clock_in, rc);
                    }
                    if ((rc = mesa_clock_input_alarm_conf_set(CLOCK_API_INST, clock_in, &alarm_conf)) != MESA_RC_OK) {
                        T_W(inst, "Could not do clock input alarm configuration set for clock input %d. Error code was: %x", clock_in, rc);
                    }
                    if ((rc = mesa_clock_input_gst_conf_set(CLOCK_API_INST, clock_in, &gst_conf)) != MESA_RC_OK) {
                        T_W(inst, "Could not do clock input GST configuration set for clock input %d. Error code was: %x", clock_in, rc);
                    }
                    if ((rc = mesa_clock_input_pfm_conf_set(CLOCK_API_INST, clock_in, &pfm_conf)) != MESA_RC_OK) {
                        T_W(inst, "Could not do clock input PFM configuration set for clock input %d. Error code was: %x", clock_in, rc);
                    }
                    if ((rc = mesa_clock_input_cfm_conf_set(CLOCK_API_INST, clock_in, &cfm_conf)) != MESA_RC_OK) {
                        T_W(inst, "Could not do clock input CFM configuration set for clock input %d. Error code was: %x", clock_in, rc);
                    }
                }
            
                // Initialize GPIO, clock divider etc. used by the station clock input/output
                {
                    mesa_synce_station_clock_out_t station_clk_conf;
        
                    // GPIO used for Station clock input
                    if ((rc = mesa_gpio_mode_set(CLOCK_API_INST, 0, SYNCE_STATION_CLOCK_IN_PIN, MESA_GPIO_ALT_0)) != MESA_RC_OK) {
                        T_W(inst, "Could not configure GPIO for station clock input. Error code was: %x", rc);
                    }
                    
                    // GPIO used for Station clock output
                    if ((rc = mesa_gpio_mode_set(CLOCK_API_INST, 0, SYNCE_STATION_CLOCK_OUT_PIN, MESA_GPIO_ALT_0)) != MESA_RC_OK) {
                        T_W(inst, "Could not configure GPIO for station clock output. Error code was: %x", rc);
                    }
                    
                    // Divide by 5 because the output frequency is 100 MHz, and there is an exted divide by 2 in the HW, this results in 10MHz clock output
                    station_clk_conf.divider = MESA_SYNCE_DIVIDER_5;
                    station_clk_conf.enable = true;
                    station_clk_conf.dpll_out_no = 0; // use dpll output no 0, this output is also used as reference clocks for TX ports (< 10G)
                    if ((rc = mesa_synce_synce_station_clk_out_set(CLOCK_API_INST, 0, &station_clk_conf)) != MESA_RC_OK) {
                        T_W(inst, "Could not configure station clock output (divider, enable, etc.). Error code was: %x", rc);
                    }
                }
            }
            break;
        case MEBA_POE_INITIALIZE:
            break;
            case MEBA_PHY_INITIALIZE:
            inst->phy_devices = (mepa_device_t **)&board->phy_devices;
            inst->phy_device_cnt = board->port_cnt;
            meba_phy_driver_init(inst);
            break;
    }

    return rc;
}

static mesa_rc servalt_sensor_get(meba_inst_t inst,
                                  meba_sensor_t type,
                                  int six,
                                  int *value)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_ERROR;
    int16_t temp = 0;
    T_N(inst, "Called %d:%d", type, six);
    if ((type == MEBA_SENSOR_BOARD_TEMP && six == 0) ||
        (type == MEBA_SENSOR_PORT_TEMP && six < board->port_cnt)) {
        rc = vtss_phy_chip_temp_get(PHY_INST, 0, &temp);
    }
    if (rc == MESA_RC_OK) {
        *value = temp;    // Conversion
    }
    return rc;
}

static mesa_rc servalt_sfp_i2c_xfer(meba_inst_t inst,
                                    mesa_port_no_t port_no,
                                    mesa_bool_t write,
                                    uint8_t i2c_addr,
                                    uint8_t addr,
                                    uint8_t *data,
                                    uint8_t cnt,
                                    mesa_bool_t word_access)
{
    mesa_rc rc;
    T_N(inst, "Called");
    if (write) {    // cnt ignored
        uint8_t i2c_data[3];
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        rc = inst->iface.i2c_write(port_no, i2c_addr, i2c_data, 3);
    } else {
        rc = inst->iface.i2c_read(port_no, i2c_addr, addr, data, cnt);
    }
    T_D(inst, "i2c %s port %d - address 0x%02x:0x%02x, %d bytes return %d", write ? "write" : "read", port_no, i2c_addr, addr, cnt, rc);
    return rc;
}

typedef enum {
    SFP_DETECT,
    SFP_FAULT,
    SFP_LOS
} sfp_signal_t;

static mesa_bool_t get_sfp_status(meba_inst_t inst,
                                  mesa_port_no_t port_no,
                                  mesa_sgpio_port_data_t *data,
                                  sfp_signal_t sfp)
{
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t chip_port = board->port[port_no].map.map.chip_port;
    uint32_t indx = (sfp == SFP_DETECT) ? 2 : (sfp == SFP_FAULT) ? 1 : 0;

    switch (chip_port) {
        case 0:  return (sfp == SFP_DETECT) ? !data[0].value[indx] : data[0].value[indx];
        case 1:  return (sfp == SFP_DETECT) ? !data[1].value[indx] : data[1].value[indx];
        case 2:  return (sfp == SFP_DETECT) ? !data[2].value[indx] : data[2].value[indx];
        case 3:  return (sfp == SFP_DETECT) ? !data[3].value[indx] : data[3].value[indx];
        case 5:  return (sfp == SFP_DETECT) ? !data[5].value[indx] : data[5].value[indx];
        case 6:  return (sfp == SFP_DETECT) ? !data[6].value[indx] : data[6].value[indx];
        case 9:  return (sfp == SFP_DETECT) ? !data[9].value[indx] : data[9].value[indx];
        case 10: return (sfp == SFP_DETECT) ? !data[4].value[indx] : (sfp == SFP_FAULT) ? data[4].value[indx] : data[10].value[indx];
    }
    return false;
}

static mesa_rc servalt_sfp_insertion_status_get(meba_inst_t inst,
                                                mesa_port_list_t *present)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc;
    mesa_port_no_t port_no;
    mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];

    mesa_port_list_clear(present);

    if ((rc = mesa_sgpio_read(NULL, 0, 0, data)) == MESA_RC_OK) {
        /* The status in 'data' is inverted i.e. '0' means detected */
        /* We return '1' when a module is detected */
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            mesa_port_list_set(present, port_no, get_sfp_status(inst, port_no, data, SFP_DETECT));
        }
    }

    return rc;
}

static mesa_rc servalt_sfp_status_get(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      meba_sfp_status_t *status)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);
    if (port_no < board->port_cnt) {
        meba_port_entry_t *entry = &board->port[port_no].map;
        status->present  = false;
        status->los      = false;
        status->tx_fault = false;
        if ((entry->cap & MEBA_PORT_CAP_SFP_DETECT) || (entry->cap & MEBA_PORT_CAP_DUAL_SFP_DETECT)) {
            mesa_sgpio_port_data_t data[MESA_SGPIO_PORTS];
            if ((rc = mesa_sgpio_read(NULL, 0, 0, data)) == MESA_RC_OK) {
                status->present  = get_sfp_status(inst, port_no, data, SFP_DETECT);
                status->tx_fault = get_sfp_status(inst, port_no, data, SFP_FAULT);
                status->los      = get_sfp_status(inst, port_no, data, SFP_LOS);
            }
        }
    }
    T_N(inst, "port(%d): rc %d, present:%d los:%d tx_fault:%d", port_no, rc,
        status->present, status->los, status->tx_fault);
    return rc;
}

static mesa_rc servalt_port_admin_state_set(meba_inst_t inst,
                                            mesa_port_no_t port_no,
                                            const meba_port_admin_state_t *state)
{
    mesa_rc rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);

    if (port_no < board->port_cnt) {
        mesa_sgpio_conf_t  conf;
        mesa_sgpio_mode_t  sgpio_mode = (state->enable ? MESA_SGPIO_MODE_ON : MESA_SGPIO_MODE_OFF);
        uint32_t chip_port = board->port[port_no].map.map.chip_port;
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            // Configure SFP TxDisable
            switch (chip_port) {
                case 0: conf.port_conf[14].mode[0] = sgpio_mode; break;
                case 1: conf.port_conf[14].mode[1] = sgpio_mode; break;
                case 2: conf.port_conf[14].mode[2] = sgpio_mode; break;
                case 3: conf.port_conf[14].mode[3] = sgpio_mode; break;
                case 5: conf.port_conf[15].mode[0] = sgpio_mode; break;
                case 6: conf.port_conf[15].mode[1] = sgpio_mode; break;
                case 9: conf.port_conf[15].mode[2] = sgpio_mode; break;
                case 10: conf.port_conf[15].mode[3] = sgpio_mode; break;
                default:
                    return rc;
            }
            T_D(inst, "Port %d: bmode_0: %d, bmode_1: %d, bit_count: %d", port_no, conf.bmode[0], conf.bmode[1], conf.bit_count);
            T_D(inst, "Port %d: p6b2: %d", port_no, conf.port_conf[6].mode[2]);
            T_D(inst, "Port %d: p6b3: %d", port_no, conf.port_conf[6].mode[3]);
            rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
        }
    }
    return rc;
}

static mesa_bool_t port_activity(meba_inst_t inst,
                                 mesa_port_no_t port_no,
                                 const mesa_port_status_t *status)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_port_status_t *old_status = &board->port[port_no].status;
    mesa_bool_t link_activity = false;

    if (old_status->link  != status->link  ||
        old_status->speed != status->speed ||
        old_status->fdx   != status->fdx   ||
        old_status->fiber != status->fiber) {
        link_activity = true;
        *old_status = *status;
    }
    if (!link_activity && !board->port[port_no].activity) {
        return false; // No Activity
    }
    board->port[port_no].activity = link_activity;
    return true; // Activity
}

static mesa_rc servalt_status_led_set(meba_inst_t inst,
                                      meba_led_type_t type,
                                      meba_led_color_t color)
{
    mesa_rc rc = MESA_RC_ERROR;
    if (type == MEBA_LED_TYPE_FRONT && color < MEBA_LED_COLOR_COUNT) {
        mesa_sgpio_conf_t conf;
        T_I(inst, "LED:%d, color=%d", type, color);
        if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
            switch (color) {
                // Active high
                case MEBA_LED_COLOR_OFF:
                    conf.port_conf[STATUS_GREEN_PORT].mode[STATUS_GREEN_BIT] = MESA_SGPIO_MODE_OFF;
                    conf.port_conf[STATUS_RED_PORT  ].mode[STATUS_RED_BIT  ] = MESA_SGPIO_MODE_OFF;
                    break;
                case MEBA_LED_COLOR_GREEN:
                    conf.port_conf[STATUS_GREEN_PORT].mode[STATUS_GREEN_BIT] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[STATUS_RED_PORT  ].mode[STATUS_RED_BIT  ] = MESA_SGPIO_MODE_OFF;
                    break;
                case MEBA_LED_COLOR_RED:
                    conf.port_conf[STATUS_GREEN_PORT].mode[STATUS_GREEN_BIT] = MESA_SGPIO_MODE_OFF;
                    conf.port_conf[STATUS_RED_PORT  ].mode[STATUS_RED_BIT  ] = MESA_SGPIO_MODE_ON;
                    break;
                case MEBA_LED_COLOR_YELLOW:
                    conf.port_conf[STATUS_GREEN_PORT].mode[STATUS_GREEN_BIT] = MESA_SGPIO_MODE_ON;
                    conf.port_conf[STATUS_RED_PORT  ].mode[STATUS_RED_BIT  ] = MESA_SGPIO_MODE_ON;
                    break;
                default:
                    rc = MESA_RC_ERROR;
            }
            if (rc == MESA_RC_OK) {
                rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
            }
        }
    }
    return rc;
}

static mesa_rc servalt_port_led_update(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       const mesa_port_status_t *status,
                                       const mesa_port_counters_t *counters,
                                       const meba_port_admin_state_t *state)
{
    meba_board_state_t *board = INST2BOARD(inst);
    servalt_port_info_t *portinfo =  &board->port[port_no];
    uint32_t            chip_port = portinfo->map.map.chip_port;
    uint8_t             bit_green = 0, bit_yellow = 1;
    mesa_sgpio_conf_t   conf;
    mesa_sgpio_mode_t   mode_green = MESA_SGPIO_MODE_OFF, mode_yellow = MESA_SGPIO_MODE_OFF;
    mesa_rc             rc;
    mesa_bool_t         update_led, tower_mode_changed, collision = false;

    update_led = port_activity(inst, port_no, status);

    // find out if tower mode has changed since the last time the port was served.
    tower_mode_changed = (portinfo->led_tower_mode_old != board->led_tower_mode);
    portinfo->led_tower_mode_old = board->led_tower_mode;

    /* Clear port count database whatever the current link status */
    if (!counters->rmon.tx_etherStatsCollisions) {
        portinfo->port_collision_cnt = false;
    }

    if (board->led_tower_mode == LED_TOWER_MODE_DUPLEX_SPEED &&
        status->link &&
        !status->fdx &&
        portinfo->port_collision_cnt != counters->rmon.tx_etherStatsCollisions) {
        update_led = true;
        collision = true;
        portinfo->pre_collision_state = true;
    } else if (!status->link) {
        portinfo->port_collision_cnt = counters->rmon.tx_etherStatsCollisions;
        portinfo->pre_collision_state = false;
    }

    if (portinfo->pre_collision_state != collision) {
        portinfo->pre_collision_state = collision;
        update_led = true;
    }

    if (board->led_tower_mode == LED_TOWER_MODE_LINK_STATUS &&
        portinfo->enable_old != state->enable) {
        update_led = true;
    }

    portinfo->enable_old = state->enable;

    /* Return here if nothing has changed or in power saving mode */
    if ((!update_led && !tower_mode_changed) ||
        (!tower_mode_changed && board->led_tower_mode == LED_TOWER_MODE_POWER_SAVE)) {
        T_N(inst, "Port %d: DON'T NEED update led(update_led = %s, tower_mode_changed = %s, board->led_tower_mode = %d)",
                 port_no, update_led ? "TRUE" : "FALSE", tower_mode_changed ? "TRUE" : "FALSE", board->led_tower_mode);
        return MESA_RC_OK;
    }

    T_I(inst, "Port %d: update led", port_no);
    if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
        if (chip_port < 2 && update_led) {
            if (status->fiber) {
                // Turn off RJ45 LED
                conf.port_conf[chip_port].mode[bit_green] = mode_green;
                conf.port_conf[chip_port].mode[bit_yellow] = mode_yellow;
                T_D(inst, "Port %d: p%db%d: %d", port_no, chip_port, bit_green, conf.port_conf[chip_port].mode[bit_green]);
                T_D(inst, "Port %d: p%db%d: %d", port_no, chip_port, bit_yellow, conf.port_conf[chip_port].mode[bit_yellow]);

                // Dual port in Serdes mode
                bit_green = 2;
                bit_yellow = 3;
            } else {
                // Turn off SFP
                conf.port_conf[chip_port].mode[2] = mode_green;
                conf.port_conf[chip_port].mode[3] = mode_yellow;
                T_D(inst, "port %d: p%db%d: %d", port_no, chip_port, 2, conf.port_conf[chip_port].mode[2]);
                T_D(inst, "port %d: p%db%d: %d", port_no, chip_port, 3, conf.port_conf[chip_port].mode[3]);
            }
        }

        switch (board->led_tower_mode) {
            case LED_TOWER_MODE_LINK_SPEED:
                if (status->link) {
                    if (status->speed >= MESA_SPEED_1G) {
                        /* Green: 1G link/activity */
                        mode_green = MESA_SGPIO_MODE_0_ACTIVITY_INV;
                    } else {
                        /* Yellow: 100/10 link/activity */
                        mode_yellow = MESA_SGPIO_MODE_0_ACTIVITY_INV;
                    }
                }
                break;
            case LED_TOWER_MODE_DUPLEX_SPEED:
                if (status->link) {
                    if (status->fdx) {
                        /* Green: FDX */
                        mode_green = MESA_SGPIO_MODE_0_ACTIVITY_INV;
                    } else if (collision) {
                        /* Blink yellow: HDX with collision */
                        mode_yellow = MESA_SGPIO_MODE_0;
                    } else {
                        /* Yellow: HDX without collision */
                        mode_yellow = MESA_SGPIO_MODE_ON;
                    }
                }
                break;
            case LED_TOWER_MODE_LINK_STATUS:
                if (state->enable == false) {
                    mode_yellow = MESA_SGPIO_MODE_ON;
                } else if (status->link) {
                    /* Green: link on */
                    mode_green = MESA_SGPIO_MODE_ON;
                }
                break;
            case LED_TOWER_MODE_POWER_SAVE:
                break;
            default:
                break;
        }

        // one to one mapping between chip_port and sgpio_port
        conf.port_conf[chip_port].mode[bit_green] = mode_green;
        conf.port_conf[chip_port].mode[bit_yellow] = mode_yellow;
        T_D(inst, "Port %d: p%db%d: %d", port_no, chip_port, bit_green, conf.port_conf[chip_port].mode[bit_green]);
        T_D(inst, "Port %d: p%db%d: %d", port_no, chip_port, bit_yellow, conf.port_conf[chip_port].mode[bit_yellow]);
        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc;
}

static mesa_rc servalt_led_mode_set(meba_inst_t inst, uint32_t mode)
{
    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc;
    mesa_sgpio_conf_t conf;

    if (mode < LED_TOWER_MODE_CNT) {
        board->led_tower_mode = mode;
    } else {
        return MESA_RC_ERROR;
    }

    T_I(inst, "Update LED mode to %d", board->led_tower_mode);

    /*
     * LED tower:
     *  (top)       o  mode A (link/speed)
     *              o  mode B (link/duplex)
     *              o  mode C (synce)
     *  (button)    o  PWR save
     */
    if ((rc = mesa_sgpio_conf_get(NULL, 0, 0, &conf)) == MESA_RC_OK) {
        int i;
        for (i = 0; i < 4; i++) {
            conf.port_conf[tower_led_mapping[i][0].port].mode[tower_led_mapping[i][0].bit] =
                    conf.port_conf[tower_led_mapping[i][1].port].mode[tower_led_mapping[i][1].bit] =
                    MESA_SGPIO_MODE_OFF;
        }

        i = board->led_tower_mode;
        conf.port_conf[tower_led_mapping[i][0].port].mode[tower_led_mapping[i][0].bit] = MESA_SGPIO_MODE_ON;
        T_D(inst, "p%db%d : %d", tower_led_mapping[i][0].port, tower_led_mapping[i][0].bit, conf.port_conf[tower_led_mapping[i][0].port].mode[tower_led_mapping[i][0].bit]);
        rc = mesa_sgpio_conf_set(NULL, 0, 0, &conf);
    }
    return rc;
}

static mesa_rc servalt_led_intensity_set(meba_inst_t inst,
                                         vtss_phy_led_intensity intensity)
{
    return vtss_phy_led_intensity_set(PHY_INST, 0, intensity);
}

static mesa_rc servalt_fan_param_get(meba_inst_t inst,
                                     meba_fan_param_t *param)
{
    T_N(inst, "Called");
    param->start_time = 100;
    param->start_level = 60;
    param->min_pwm = 30;
    return MESA_RC_OK;
}

static mesa_rc servalt_fan_conf_get(meba_inst_t inst,
                                    mesa_fan_conf_t *conf)
{
    T_N(inst, "Called");
    meba_board_state_t *board = INST2BOARD(inst);
    *conf = *board->fan_spec;
    return MESA_RC_OK;
}

static mesa_rc servalt_ptp_rs422_conf_get(meba_inst_t inst,
        meba_ptp_rs422_conf_t *conf)
{
    mesa_rc rc = MESA_RC_OK;
    T_N(inst, "Called");
    *conf = rs422_conf;
    return rc;
}
static mesa_rc servalt_ptp_external_io_conf_get(meba_inst_t inst, uint32_t io_pin, meba_ptp_io_cap_t *const board_assignment, meba_event_t *const source_id)

{
    if (io_pin >= VTSS_TS_IO_ARRAY_SIZE) {
        return MESA_RC_ERROR;
    }
    *board_assignment = pin_conf[io_pin];
    *source_id = init_int_source_id[io_pin];
    return MESA_RC_OK;
}

static mesa_port_no_t srvlt_map_sgpio_to_port(meba_board_state_t *board,
                                              uint32_t sgpio_port)
{
    mesa_port_no_t port_no;

    /* SGPIO port 4,7 and 8 are not used */
    port_no = (sgpio_port < 4 ? sgpio_port :
               sgpio_port == 4 ? board->port_cnt :
               sgpio_port < 7 ? (sgpio_port - 1) :
               sgpio_port > 8 ? (sgpio_port - 3) : board->port_cnt);

    /* For some platforms, all ports are not used and the mapping
       above leads to a port above board->port_cnt.  In that
       case, we map to the last port (the NPI port), which does not
       support SFPs */
    if (port_no >= board->port_cnt) {
        port_no = (board->port_cnt - 1);
    }

    return port_no;
}

static mesa_rc servalt_event_enable(meba_inst_t inst,
                                    meba_event_t event_id,
                                    mesa_bool_t enable)
{
    mesa_rc               rc = MESA_RC_OK;
    meba_board_state_t    *board = INST2BOARD(inst);
    int                   gpio, sgpio;
    mesa_port_no_t        port_no;

    T_I(inst, "%sable event %d", enable ? "en" : "dis", event_id);

    switch (event_id) {
        case MEBA_EVENT_SYNC:
        case MEBA_EVENT_EXT_SYNC:
        case MEBA_EVENT_EXT_1_SYNC:
        case MEBA_EVENT_CLK_ADJ:
        case MEBA_EVENT_VOE:
            return rc;    // Dummy for now

        case MEBA_EVENT_LOS:
            for (sgpio = 0; sgpio < 11; sgpio++) {
                port_no = srvlt_map_sgpio_to_port(board, sgpio);
                if (is_sfp_port(board->port[port_no].map.cap)) {
                    T_D(inst, "port(%d) %sable LOS sgpio %d", port_no, enable ? "en" : "dis", sgpio);
                    // Enable SGPIOs for SFP LOS
                    if (mesa_sgpio_event_enable(NULL, 0, 0, sgpio, 0, enable) != MESA_RC_OK) {
                        T_E(inst, "Could not enable event for sgpio #%d", sgpio);
                    }
                }
            }
            break;

        case MEBA_EVENT_FLNK:
            for (port_no = 0; port_no < board->port_cnt; port_no++) {
                if (is_phy_internal(board->port[port_no].map.cap)) {
                    T_D(inst, "port(%d) %sable DEV_ALL", port_no, enable ? "en" : "dis");
                    if ((rc = mesa_dev_all_event_enable(NULL, port_no, MESA_DEV_ALL_LINK_EV, enable)) != MESA_RC_OK) {
                        T_E(inst, "Could not enable event for dev #%d = %d", port_no, rc);
                    }
                }
                if (is_phy_port(board->port[port_no].map.cap)) {
                    T_D(inst, "port(%d) %sable FLNK", port_no, enable ? "en" : "dis");
                    if ((rc = vtss_phy_event_enable_set(PHY_INST, port_no, VTSS_PHY_LINK_FFAIL_EV, enable)) != MESA_RC_OK) {
                        T_E(inst, "Could not enable event for dev #%d = %d", port_no, rc);
                    }
                }
            }
            break;

        case MEBA_EVENT_AMS:
            // Note - No AMS support in original interrupt_jaguar2.cxx code
            rc = MESA_RC_NOT_IMPLEMENTED;
            break;

        case MEBA_EVENT_PTP_PIN_0:
        case MEBA_EVENT_PTP_PIN_1:
        case MEBA_EVENT_PTP_PIN_2:
        case MEBA_EVENT_PTP_PIN_3:
        case MEBA_EVENT_CLK_TSTAMP:
            {
                mesa_ptp_event_type_t ptp_event = meba_generic_ptp_source_to_event(inst, event_id);
                if ((rc = mesa_ptp_event_enable(NULL, ptp_event, enable)) != MESA_RC_OK) {
                    T_E(inst, "mesa_ptp_event_enable = %d", rc);
                }
            }
            break;

        case MEBA_EVENT_PUSH_BUTTON:
            gpio = 13;
            if (gpio >= 0) {
                T_I(inst, "%sable Push_button(GPIO_%d) interrupt", enable ? "en" : "dis", gpio);
                if (mesa_gpio_event_enable(NULL, 0, gpio, enable) != MESA_RC_OK) {
                    T_E(inst, "Could not control event for gpio #%d", gpio);
                }
            }
            break;

        default:
            return MESA_RC_NOT_IMPLEMENTED;    // Will occur as part of probing
    }

    return rc;
}

static mesa_rc sgpio_handler(meba_inst_t inst,
                             meba_board_state_t *board,
                             meba_event_signal_t signal_notifier)
{
    uint32_t       sgpio_port, handled = 0;
    mesa_port_no_t port_no;
    mesa_rc        rc;
    mesa_bool_t    sgpio_events_bit[MESA_SGPIO_PORTS];

    // Getting SGPIO bit 0 (see UG1058 Table 15)
    if ((rc = mesa_sgpio_event_poll(NULL, 0, 0, 0, sgpio_events_bit)) != MESA_RC_OK) {
        T_E(inst, "mesa_sgpio_event_poll = %d", rc);
        return true;
    }

    for (sgpio_port = 0; sgpio_port < 11; sgpio_port++) {
        port_no = srvlt_map_sgpio_to_port(board, sgpio_port);
        if (is_sfp_port(board->port[port_no].map.cap) && sgpio_events_bit[sgpio_port]) {
            T_I(inst, "Event on sgpio_port %d (iport = %u)", sgpio_port, port_no);
            // Disable the interrupt while handling the event
            if ((rc = mesa_sgpio_event_enable(NULL, 0, 0, sgpio_port, 0, false)) != MESA_RC_OK) {
                T_E(inst, "mesa_sgpio_event_enable = %d", rc);
                // Go on anyway
            }
            signal_notifier(MEBA_EVENT_LOS, port_no);
            handled++;
        }
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc dev_all_handler(meba_inst_t inst,
                               meba_board_state_t *board,
                               meba_event_signal_t signal_notifier)
{
    mesa_dev_all_event_type_t  dev_all_events[MESA_CAP(MESA_CAP_PORT_CNT)];
    mesa_port_no_t port_no;
    int handled = 0;

    if (mesa_dev_all_event_poll(NULL, MESA_DEV_ALL_POLL_ALL, dev_all_events) != MESA_RC_OK) {
        T_E(inst, "mesa_dev_all_event_poll failed");
        return MESA_RC_ERROR;
    }

    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (dev_all_events[port_no] & MESA_DEV_ALL_LINK_EV) {
            T_I(inst, "DEV %d intr", port_no);
            if (mesa_dev_all_event_enable(NULL, port_no, dev_all_events[port_no], false) != MESA_RC_OK) {
                T_E(inst, "mesa_dev_all_event_enable failed");
            }
            if (is_phy_port(board->port[port_no].map.cap)) {
                if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                    T_D(inst, "port(%d) PHY IRQ handled", port_no);
                    handled++;
                }
            }
        }
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc ext1_handler(meba_inst_t inst,
                            meba_board_state_t *board,
                            meba_event_signal_t signal_notifier)
{
    int handled = 0;
    mesa_port_no_t port_no;
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        if (is_phy_port(board->port[port_no].map.cap)) {
            if (meba_generic_phy_event_check(inst, port_no, signal_notifier) == MESA_RC_OK) {
                T_D(inst, "port(%d) PHY IRQ handled", port_no);
                handled++;
            }
        }
    }
    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc gpio_handler(meba_inst_t inst, meba_board_state_t *board, meba_event_signal_t signal_notifier)
{
    mesa_bool_t gpio_events[MESA_CAP(MESA_CAP_MISC_GPIO_CNT)];
    mesa_rc     rc;
    int         handled = 0, gpio;

    if ((rc = mesa_gpio_event_poll(NULL, 0, gpio_events)) != MESA_RC_OK) {
        T_E(inst, "mesa_gpio_event_poll: %d", rc);
        return rc;
    }

    // Check GPIO pushbutton signal
    gpio = 13;
    if (gpio_events[gpio]) {
        mesa_bool_t state = false;
        (void) mesa_gpio_read(NULL, 0, gpio, &state);
        if (state) {    // Only IRQ on de-press (not de-press and release)
            if ((rc = mesa_gpio_event_enable(NULL, 0, gpio, false)) != MESA_RC_OK) {
                T_E(inst, "mesa_gpio_event_enable = %d", rc);
            }
            signal_notifier(MEBA_EVENT_PUSH_BUTTON, 0);
        }
        handled++;
    }

    return handled ? MESA_RC_OK : MESA_RC_ERROR;
}

static mesa_rc servalt_irq_handler(meba_inst_t inst,
                                   mesa_irq_t chip_irq,
                                   meba_event_signal_t signal_notifier)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_I(inst, "Called - irq %d", chip_irq);

    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
            return meba_generic_ptp_handler(inst, signal_notifier);
        case MESA_IRQ_PTP_RDY:
            signal_notifier(MEBA_EVENT_CLK_TSTAMP, 0);
            return MESA_RC_OK;
        case MESA_IRQ_OAM:
            signal_notifier(MEBA_EVENT_VOE, 0);
            return MESA_RC_OK;
        case MESA_IRQ_GPIO:
            return gpio_handler(inst, board, signal_notifier);
        case MESA_IRQ_SGPIO:
            return sgpio_handler(inst, board, signal_notifier);
        case MESA_IRQ_EXT1:
            return ext1_handler(inst, board, signal_notifier);
        case MESA_IRQ_DEV_ALL:
            return dev_all_handler(inst, board, signal_notifier);
        default:;
    }

    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc servalt_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    switch (chip_irq) {
        case MESA_IRQ_PTP_SYNC:
        case MESA_IRQ_PTP_RDY:
        case MESA_IRQ_OAM:
        case MESA_IRQ_GPIO:
        case MESA_IRQ_SGPIO:
        case MESA_IRQ_EXT1:
        case MESA_IRQ_DEV_ALL:
            rc = MESA_RC_OK;
        default:;
    }
    return rc;
}

meba_inst_t meba_initialize(size_t callouts_size, const meba_board_interface_t *callouts)
{
    meba_inst_t inst;
    meba_board_state_t *board;
    mesa_port_no_t port_no;

    if (callouts_size < sizeof(*callouts)) {
        fprintf(stderr, "Callouts size problem, expected %zd, got %zd\n",
                sizeof(*callouts), callouts_size);
        return NULL;
    }

    // Allocate pulic state
    if ((inst = meba_state_alloc(callouts,
                                 "Serval-T NID",
                                 MESA_TARGET_SERVAL_TE10,
                                 sizeof(*board))) == NULL) {
        return NULL;
    }

    // Initialize our state
    MEBA_ASSERT(inst->private_data != NULL);
    board = INST2BOARD(inst);
    board->ports_1g = 4;
    switch (inst->props.target) {
        case MESA_TARGET_SERVAL_T:      // 0x7410,  /**< Serval-T switch */
        case MESA_TARGET_SERVAL_TP:     // 0x7415,  /**< Serval-TP switch */
        case MESA_TARGET_SERVAL_TE:     // 0x7430,  /**< Serval-TE switch */
        case MESA_TARGET_SERVAL_TEP:    // 0x7435,  /**< Serval-TEP switch */
            board->ports_2_5g = 2;
            break;

        case MESA_TARGET_SERVAL_2_LITE: // 0x7436,  /**< Serval-2 Lite switch */
        case MESA_TARGET_SERVAL_TE10:   // 0x7437,  /**< Serval-TE10 switch */
        case MESA_TARGET_SPARX_IV_34:   // 0x7440,  /**< Sparx-IV-34 switch */
            board->ports_2_5g = 2;
            board->ports_10g  = 2;
            break;

        default:
            T_E(inst, "Unkown target %d", inst->props.target);
            MEBA_ASSERT(0);
    }

    // NPI + 1G + 2.5G + 10G
    board->port_cnt = 1 + board->ports_1g + board->ports_2_5g + board->ports_10g;
    inst->props.board_type = VTSS_BOARD_SERVALT_NID_REF;    // Exposed temporarily
    board->fan_spec = &fan_conf;
    board->port = (servalt_port_info_t*) calloc(board->port_cnt, sizeof(servalt_port_info_t));
    if (board->port == NULL) {
        fprintf(stderr, "Port table malloc failure\n");
        goto error_out;
    }
    T_I(inst, "Board: %s, target %4x, %d ports", inst->props.name, inst->props.target, board->port_cnt);

    /* Fill out port mapping table */
    for (port_no = 0; port_no < board->port_cnt; port_no++) {
        servalt_port_entry_init(inst, port_no, &board->port[port_no].map);
    }

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = servalt_capability;
    inst->api.meba_port_entry_get             = servalt_port_entry_get;
    inst->api.meba_reset                      = servalt_reset;
    inst->api.meba_sensor_get                 = servalt_sensor_get;
    inst->api.meba_sfp_i2c_xfer               = servalt_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = servalt_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = servalt_sfp_status_get;
    inst->api.meba_port_admin_state_set       = servalt_port_admin_state_set;
    inst->api.meba_status_led_set             = servalt_status_led_set;
    inst->api.meba_port_led_update            = servalt_port_led_update;
    inst->api.meba_led_mode_set               = servalt_led_mode_set;
    inst->api.meba_led_intensity_set          = servalt_led_intensity_set;
    inst->api.meba_fan_param_get              = servalt_fan_param_get;
    inst->api.meba_fan_conf_get               = servalt_fan_conf_get;
    inst->api.meba_irq_handler                = servalt_irq_handler;
    inst->api.meba_irq_requested              = servalt_irq_requested;
    inst->api.meba_event_enable               = servalt_event_enable;
    inst->api.meba_deinitialize               = meba_deinitialize;
    inst->api.meba_ptp_rs422_conf_get         = servalt_ptp_rs422_conf_get;
    inst->api.meba_ptp_external_io_conf_get   = servalt_ptp_external_io_conf_get;

    inst->api_synce = meba_synce_get();
    inst->api_tod = meba_tod_get();

    return inst;

error_out:
    free(inst);
    return NULL;
}
