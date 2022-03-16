// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_jaguar2_cil.h"

#if defined(VTSS_ARCH_JAGUAR_2)

// Avoid Lint Warning 572: Excessive shift value (precision 1 shifted right by 2), which occurs
// in this file because (t) - VTSS_IO_ORIGIN1_OFFSET == 0 for t = VTSS_TO_CFG (i.e. ICPU_CFG), and 0 >> 2 gives a lint warning.
/*lint --e{572} */

/* - CIL functions ------------------------------------------------- */


#if defined(VTSS_FEATURE_EEE)
/* =================================================================
 *  EEE - Energy Efficient Ethernet
 * =================================================================*/
static vtss_rc jr2_eee_port_conf_set(vtss_state_t *vtss_state,
                                      const vtss_port_no_t       port_no, 
                                      const vtss_eee_port_conf_t *const conf)
{
    u32            closest_match_index, closest_match, i, requested_time;
    u32            eee_cfg_reg = 0x0; // SYS::EEE_CFG register value.
    vtss_port_no_t chip_port = VTSS_CHIP_PORT(port_no);
    u16            eee_timer_age;

    // The formula for the actual wake-up time given a
    // register value is non-linear (though periodic with
    // increasing base values).
    // The easiest way to find the closest match to a user-specified
    // value is to create a static lookup table that will have to be
    // traversed everytime.
    if (!vtss_state->eee.timer_table_initialized) {
        vtss_state->eee.timer_table_initialized = TRUE;
        for (i = 0; i < VTSS_EEE_TIMER_TABLE_CNT; i++) {
            vtss_state->eee.timer_table[i] = (1 << (2 * (i / 16UL))) * (i % 16UL);
        }
    }

    // Make sure that we don't get out of bound
    if (port_no >= VTSS_PORT_ARRAY_SIZE) {
        VTSS_E("Out of bounds: Port:%u, VTSS_PORT_ARRAY_SIZE:%d", port_no, VTSS_PORT_ARRAY_SIZE);
        return VTSS_RC_ERROR;
    }

    // EEE enable
    if (conf->eee_ena) {
        //LPI is really an old error code redefined to tell the link partner to go to
        // lower power or when removed to wakeup.
        // Some devices are seeing the error code and assuming there is a
        // problem causing the link to go down. A work around is to only enable EEE in the MAC (No LPI signal to the PHY)
        // when the PHY has auto negotiated and have found that the link partner supports EEE.
        if (conf->lp_advertisement == 0) {
            VTSS_D("Link partner doesn't support EEE - Keeping EEE disabled. Port:%u", chip_port);
        } else if (!(vtss_state->port.conf[port_no].fdx)) {
            // EEE and Half duplex are not supposed to work together, so we disables EEE in the case where the port is in HDX mode.
            VTSS_D("EEE disabled due to that port is in HDX mode, port:%u", chip_port);
        } else {
            eee_cfg_reg |= VTSS_M_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_ENA;
        }
    }


    // EEE wakeup timer (See datasheet for understanding calculation)
    closest_match_index = 0;
    closest_match       = 0xFFFFFFFFUL;
    requested_time      = conf->tx_tw;
    for (i = 0; i< VTSS_EEE_TIMER_TABLE_CNT; i++) {
        u32 table_val = vtss_state->eee.timer_table[i];
        if (table_val >= requested_time) {
            u32 diff = table_val - requested_time;
            if (diff < closest_match) {
                closest_match       = diff;
                closest_match_index = i;
                if (closest_match == 0) {
                    break;
                }
            }
        }
    }

    if (closest_match == 0xFFFFFFFFUL) {
        closest_match_index = 127;
    }

    eee_cfg_reg |= VTSS_F_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_WAKEUP(closest_match_index);
    
    // Set the latency depending upon what the user prefer (power saving vs. low traffic latency)
    if (conf->optimized_for_power) {
        eee_timer_age = 82; // Set timer age to 263 mSec.
    } else {
        eee_timer_age = 0x23; // Set timer age to 48 uSec.
    }

    // EEE holdoff timer
    eee_cfg_reg |= VTSS_F_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_HOLDOFF(0x5) | VTSS_F_DEV1G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_AGE(eee_timer_age);

    // EEE fast queues
    VTSS_N("eee_fast_queues:0x%X, to-dev:%d, chip_port:%d", conf->eee_fast_queues, VTSS_TO_DEV1G(chip_port), chip_port);
    JR2_WRM(VTSS_QSYS_SYSTEM_EEE_CFG(chip_port),  
            VTSS_F_QSYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES(conf->eee_fast_queues),
            VTSS_M_QSYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES);
            
    // Registers write
    VTSS_D("chip_port:%d, eee_cfg_reg:0x%X", chip_port, eee_cfg_reg);
    JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_EEE_CFG(VTSS_TO_DEV1G(chip_port)), eee_cfg_reg);
    VTSS_D("chip_port:%u, eee_cfg_reg = 0x%X, conf->tx_tw = %d, eee_timer_age:%d", chip_port, eee_cfg_reg, conf->tx_tw, eee_timer_age);

    // Setting Buffer size to 12.2 Kbyte & 255 frames.
    JR2_WR(VTSS_QSYS_SYSTEM_EEE_THRES, 0xFFFF);

    // Work-around of Bugzilla#18901     
    u32 dummy_reg, prio;
    for (prio = 0; prio < 8; prio++) {
        JR2_RD(VTSS_QRES_RES_CTRL_RES_STAT(2048 + 8 * port_no + prio), &dummy_reg);
    }
    
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_EEE */

#if defined(VTSS_FEATURE_FAN)
/* =================================================================
 * FAN speed control
 * =================================================================*/
static vtss_rc jr2_fan_controller_init(vtss_state_t *vtss_state,
                                        const vtss_fan_conf_t *const spec)
{

#if defined(VTSS_ARCH_SERVAL_T)
    // Set GPIO alternate functions. PWM is bit 17.- See Datasheet Table 287.
    VTSS_RC(vtss_jr2_gpio_mode(vtss_state, 0, 17, VTSS_GPIO_ALT_0));

    // Set GPIO alternate functions. ROTA is bit 16.- See Datasheet Table 287.
    VTSS_RC(vtss_jr2_gpio_mode(vtss_state, 0, 16, VTSS_GPIO_ALT_0));
#else // JR2
    // Set GPIO alternate functions. PWM is bit 23.
    VTSS_RC(vtss_jr2_gpio_mode(vtss_state, 0, 23, VTSS_GPIO_ALT_0));

    // Set GPIO alternate functions. ROTA is bit 22.
    VTSS_RC(vtss_jr2_gpio_mode(vtss_state, 0, 22, VTSS_GPIO_ALT_0));
#endif


    // Set PWM frequency 
    JR2_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
            VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_PWM_FREQ(spec->fan_pwm_freq),
            VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_PWM_FREQ);

    // Set PWM polarity 
    JR2_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
            spec->fan_low_pol ? VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_INV_POL : 0,
            VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_INV_POL);
    
    // Set PWM open collector 
    JR2_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
            spec->fan_open_col ? VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_INV_POL : 0,
            VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_PWM_OPEN_COL_ENA);

#ifdef VTSS_ARCH_JAGUAR_2_C
    // There is a chip issue, so we have to set the clk period to 40 - See Bugzilla#18887. This will (depending on the system clock) give some inaccuracy with the PWM frequency and RPM counter, but we will have to live with that.
    JR2_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
            VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_CLK_PERIOD(40),
            VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_CLK_PERIOD);
#endif


    // We always use the one sec update for rotation count.
    JR2_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
            0,
            VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_FAN_STAT_CFG);
           
    // Set fan speed measurement
    if (spec->type == VTSS_FAN_3_WIRE_TYPE) {
        // Enable gating for 3-wire fan types.
        JR2_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
               VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_GATE_ENA,
               VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_GATE_ENA);
    } else {
        //  For 4-wire fan types we need to disable gating (2-wire types doesn't matter)
        JR2_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
                0,
                VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_GATE_ENA);
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_fan_cool_lvl_set(vtss_state_t *vtss_state, u8 lvl)
{
    // Set PWM duty cycle (fan speed) 
    JR2_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
            VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_DUTY_CYCLE(lvl),
            VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_DUTY_CYCLE);

    return VTSS_RC_OK;
}

static vtss_rc jr2_fan_cool_lvl_get(vtss_state_t *vtss_state, u8 *duty_cycle)
{
    u32 fan_cfg_reg;
    
    // Read the register 
    JR2_RD(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG, &fan_cfg_reg);
    
    // Get PWM duty cycle
    *duty_cycle = VTSS_X_DEVCPU_GCB_FAN_CTRL_FAN_CFG_DUTY_CYCLE(fan_cfg_reg);
    
    return VTSS_RC_OK;
}

static vtss_rc jr2_fan_rotation_get(vtss_state_t *vtss_state, vtss_fan_conf_t *fan_spec, u32 *rotation_count)
{
    // Read the register 
    JR2_RD(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CNT, rotation_count);
   
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_FAN */

/* ================================================================= *
 *  Temperature Sensor
 * ================================================================= */
#if defined(VTSS_FEATURE_TEMP_SENSOR) && (defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C))
static vtss_rc jr2_temp_sensor_init(vtss_state_t *vtss_state,
                                    const BOOL enable) 
{
    // Enable/Disable
    JR2_WRM(VTSS_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_CTRL,
            enable ? 1 : 0,
            VTSS_M_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_CTRL_SAMPLE_ENA);
    return VTSS_RC_OK;
}

static vtss_rc jr2_temp_sensor_get(vtss_state_t *vtss_state,
                                   i16  *temp) 
{
    u32 status = 0;
    JR2_RD(VTSS_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_STAT, &status);

    // See data-sheet section 3.8.11
    *temp = (197400 - 953 * (i16)(status & VTSS_M_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_STAT_TEMP))/1000;
    
    // Check if the data is valid.
    if (status & VTSS_M_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_STAT_TEMP_VALID) {
        return VTSS_RC_OK;
    }
    
    return VTSS_RC_ERROR;
}

#endif /* VTSS_FEATURE_TEMP_SENSOR */

/* ================================================================= *
 *  Miscellaneous
 * ================================================================= */

static vtss_rc jr2_reg_read(vtss_state_t *vtss_state,
                             const vtss_chip_no_t chip_no, const u32 addr, u32 * const value)
{
    return vtss_jr2_rd(vtss_state, addr, value);
}

static vtss_rc jr2_reg_write(vtss_state_t *vtss_state,
                              const vtss_chip_no_t chip_no, const u32 addr, const u32 value)
{
    return vtss_jr2_wr(vtss_state, addr, value);
}

vtss_rc vtss_jr2_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id)
{
    u32 value;

    JR2_RD(VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID, &value);
    if (value == 0 || value == 0xffffffff) {
        VTSS_E("CPU interface[%u] error, chipid: 0x%08x", vtss_state->chip_no, value);
        return VTSS_RC_ERROR;
    }
    chip_id->part_number = VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID(value);
    chip_id->revision = VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID(value);
    return VTSS_RC_OK;
}

static vtss_rc jr2_ptp_event_poll(vtss_state_t *vtss_state, vtss_ptp_event_type_t *ev_mask)
{
    u32 sticky, mask;

    /* PTP events */
    *ev_mask = 0;
    JR2_RD(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR, &sticky);
    JR2_WR(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR, sticky);
    JR2_RD(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA, &mask);
    sticky &= mask;      /* Only handle enabled sources */

    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_INTR_PTP(1<<EXT_CLK_PIN)) ?  VTSS_PTP_PIN_0_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_INTR_PTP(1<<EXT_PPS_PIN)) ?  VTSS_PTP_PIN_1_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_INTR_PTP(1<<ALT_LDST_PIN)) ? VTSS_PTP_PIN_2_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_INTR_PTP(1<<ALT_PPS_PIN)) ?  VTSS_PTP_PIN_3_SYNC_EV : 0;
    VTSS_D("sticky: 0x%x, ev_mask 0x%x", sticky, *ev_mask);

    return VTSS_RC_OK;
}

static vtss_rc jr2_ptp_event_enable(vtss_state_t *vtss_state,
                                     vtss_ptp_event_type_t ev_mask, BOOL enable)
{
    /* PTP masks */

    VTSS_D("ev_mask 0x%x, enable: %d", ev_mask, enable);
    if (ev_mask & VTSS_PTP_PIN_0_SYNC_EV) {
        JR2_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<EXT_CLK_PIN : 0),
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<EXT_CLK_PIN));
    }
    if (ev_mask & VTSS_PTP_PIN_1_SYNC_EV) {
        JR2_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<EXT_PPS_PIN : 0),
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<EXT_PPS_PIN));
    }
    if (ev_mask & VTSS_PTP_PIN_2_SYNC_EV) {
        JR2_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<ALT_LDST_PIN : 0),
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<ALT_LDST_PIN));
    }
    if (ev_mask & VTSS_PTP_PIN_3_SYNC_EV) {
        JR2_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<ALT_PPS_PIN : 0),
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<ALT_PPS_PIN));
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_dev_all_event_poll(vtss_state_t *vtss_state,
                                     vtss_dev_all_event_poll_t poll_type,
                                     vtss_dev_all_event_type_t  *ev_mask)
{
    u32 ident=0, chip_port;
    vtss_port_no_t api_port;

    /* Read the active interrupt sources (the product of sticky & enable) */
    JR2_RD(VTSS_ICPU_CFG_INTR_DEV_INTR_IDENT, &ident);

    for (api_port = VTSS_PORT_NO_START; api_port < vtss_state->port_count; api_port++) {
        ev_mask[api_port] = 0;
        chip_port = VTSS_CHIP_PORT(api_port);
        if (ident & (1 << chip_port)) {
            if (VTSS_PORT_IS_1G(chip_port)) {
#if defined(VTSS_ARCH_SERVAL_T)
                /* Clear the dev sticky */
                JR2_WRM(VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR(VTSS_TO_DEV(chip_port)),
                        VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_DOWN_INTR_STICKY(1) |
                        VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_LINK_DOWN_INTR_STICKY(1),
                        VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_DOWN_INTR_STICKY |
                        VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_AN_LINK_DOWN_INTR_STICKY);
#else /* VTSS_ARCH_JAGUAR_2_C */
                /* Clear the dev sticky */
                JR2_WRM(VTSS_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR(VTSS_TO_DEV(chip_port)),
                        VTSS_F_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_LINK_DOWN_INTR_STICKY(1) |
                        VTSS_F_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_AN_LINK_DOWN_INTR_STICKY(1),
                        VTSS_M_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_LINK_DOWN_INTR_STICKY |
                        VTSS_M_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_AN_LINK_DOWN_INTR_STICKY);

#endif
            } else {
                JR2_WRM(VTSS_DEV10G_DEV_CFG_STATUS_INTR(VTSS_TO_DEV(chip_port)),
                        VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_LINK_DWN_INTR(1),
                        VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_LINK_DWN_INTR);
            }
            ev_mask[api_port] = VTSS_DEV_ALL_LINK_EV;
        }
    }
    /* Clear the icpu_dev sticky */
    JR2_WR(VTSS_ICPU_CFG_INTR_DEV_INTR_STICKY, ident);

#if defined(VTSS_ARCH_SERVAL_T)
    /* The internal phy interrupt is mapped to ICPU_DEV_INTR index 11 and 12 */
    /* Here they are mapped back to ev_mask with the corresponding API index */
    for (api_port = VTSS_PORT_NO_START; api_port < vtss_state->port_count; api_port++) {
        chip_port = VTSS_CHIP_PORT(api_port);
        if ((chip_port > 2) || (vtss_state->port.conf[api_port].if_type != VTSS_PORT_INTERFACE_SGMII)) {
            continue;
        }

        if (ident & (1 << (chip_port + 11))) {
            ev_mask[api_port] = VTSS_DEV_ALL_LINK_EV;
        }
    }
#endif /* VTSS_ARCH_SERVAL_T */

    return VTSS_RC_OK;
}


static vtss_rc jr2_dev_all_event_enable(vtss_state_t *vtss_state,
                                       vtss_port_no_t port_no, vtss_dev_all_event_type_t ev_mask, BOOL enable)
{
    u32 chip_port = VTSS_CHIP_PORT(port_no), mask = VTSS_BIT(chip_port), dev_intr = chip_port;

    if (!(ev_mask & VTSS_DEV_ALL_LINK_EV)) {
        VTSS_D("DEV event supported: 0x%x", ev_mask);
        return VTSS_RC_ERROR;
    }
#if defined(VTSS_ARCH_SERVAL_T)
    /* The internal phy interrupt is mapped to index 11 and 12 */
    if (chip_port < 2) {
        if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII) {
            dev_intr = chip_port + 11;
        }
        mask |= VTSS_BIT(chip_port + 11);
    }
#endif /* VTSS_ARCH_SERVAL_T */

    /* Enable/disable ICPU device interrupt */
    JR2_WRM(VTSS_ICPU_CFG_INTR_DEV_INTR_ENA, VTSS_ENCODE_BITFIELD(enable,dev_intr,1), mask);

#if defined(VTSS_ARCH_SERVAL_T)
    /* The internal phy interrupts are mapped to index 11 and 12 */
    if ((vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII) && (chip_port < 2)) {
        JR2_WR(VTSS_ICPU_CFG_INTR_DEV_INTR_STICKY, mask);
        return VTSS_RC_OK;
    }
#endif /* VTSS_ARCH_SERVAL_T */

    if (VTSS_PORT_IS_1G(chip_port)) {
#if defined(VTSS_ARCH_SERVAL_T)
    /* Enable/disable the dev interrupt */
    JR2_WRM(VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG(VTSS_TO_DEV(chip_port)),
            VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_DOWN_INTR_ENA(enable) |
            VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_LINK_DOWN_INTR_ENA(enable),
            VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_DOWN_INTR_ENA |
            VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_LINK_DOWN_INTR_ENA);
    /* Clear the sticky */
    JR2_WRM(VTSS_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR(VTSS_TO_DEV(chip_port)),
            VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_DOWN_INTR_ENA(1) |
            VTSS_F_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_DOWN_INTR_STICKY(1),
            VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_CFG_AN_LINK_DOWN_INTR_ENA |
            VTSS_M_DEV1G_DEV2G5_INTR_CFG_STATUS_DEV2G5_INTR_LINK_DOWN_INTR_STICKY);
#else /* VTSS_ARCH_JAGUAR_2_C */
    JR2_WRM(VTSS_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_CFG(VTSS_TO_DEV(chip_port)),
            VTSS_F_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_CFG_AN_LINK_DOWN_INTR_ENA(enable) |
            VTSS_F_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_CFG_LINK_DOWN_INTR_ENA(enable),
            VTSS_M_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_CFG_AN_LINK_DOWN_INTR_ENA |
            VTSS_M_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_CFG_LINK_DOWN_INTR_ENA);
    JR2_WRM(VTSS_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR(VTSS_TO_DEV(chip_port)),
            VTSS_F_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_CFG_AN_LINK_DOWN_INTR_ENA(1) |
            VTSS_F_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_LINK_DOWN_INTR_STICKY(1),
            VTSS_M_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_CFG_AN_LINK_DOWN_INTR_ENA |
            VTSS_M_DEV1G_DEV1G_INTR_CFG_STATUS_DEV1G_INTR_LINK_DOWN_INTR_STICKY);
#endif
    } else {
        JR2_WRM(VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA(VTSS_TO_DEV(chip_port)),
                VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_LINK_DWN_INTR_ENA(enable),
                VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_LINK_DWN_INTR_ENA);
        JR2_WRM(VTSS_DEV10G_DEV_CFG_STATUS_INTR(VTSS_TO_DEV(chip_port)),
                VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_LINK_DWN_INTR(enable),
                VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_LINK_DWN_INTR);
    }

    /* Clear ICPU sticky bit */
    JR2_WR(VTSS_ICPU_CFG_INTR_DEV_INTR_STICKY, mask);

    return VTSS_RC_OK;
}


static vtss_rc jr2_intr_cfg(vtss_state_t *vtss_state,
                             const u32  intr_mask, const BOOL polarity, const BOOL enable)
{
    // JR2-TBD: Stub
    return VTSS_RC_OK;
}

static vtss_rc jr2_intr_pol_negation(vtss_state_t *vtss_state)
{
    // JR2-TBD: Stub
    return VTSS_RC_OK;
}

#ifdef VTSS_FEATURE_IRQ_CONTROL

#define JR2_IRQ_DEV_ALL       (0)
#define JR2_IRQ_EXT0          (1)
#define JR2_IRQ_EXT1          (2)
#define JR2_IRQ_TIMER0        (3)
#define JR2_IRQ_TIMER1        (4)
#define JR2_IRQ_TIMER2        (5)
#define JR2_IRQ_UART          (6)
#define JR2_IRQ_UART2         (7)
#define JR2_IRQ_TWI           (8)
#define JR2_IRQ_TWI2          (9)
#define JR2_IRQ_SIMC          (10)
#define JR2_IRQ_SW0           (11)
#define JR2_IRQ_SW1           (12)
#define JR2_IRQ_SGPIO         (13)
#if defined(VTSS_ARCH_SERVAL_T)
#define JR2_IRQ_SGPIO1        (13)
#define JR2_IRQ_GPIO          (14)
#define JR2_IRQ_MIIM0_INTR    (15)
#define JR2_IRQ_MIIM1_INTR    (16)
#define JR2_IRQ_FDMA          (17)
#define JR2_IRQ_ANA           (18)
#define JR2_IRQ_PTP_RDY       (19)
#define JR2_IRQ_PTP_SYNC      (20)
#define JR2_IRQ_IGTR          (21)
#define JR2_IRQ_XTR_RDY       (22)
#define JR2_IRQ_INJ_RDY       (23)
#define JR2_IRQ_PCIE          (24)
#define JR2_IRQ_OAM_VOP       (25)
#else
#define JR2_IRQ_SGPIO1        (14)
#define JR2_IRQ_SGPIO2        (15)
#define JR2_IRQ_GPIO          (16)
#define JR2_IRQ_MIIM0_INTR    (17)
#define JR2_IRQ_MIIM1_INTR    (18)
#define JR2_IRQ_MIIM2_INTR    (19)
#define JR2_IRQ_FDMA          (20)
#define JR2_IRQ_ANA           (21)
#define JR2_IRQ_PTP_RDY       (22)
#define JR2_IRQ_PTP_SYNC      (23)
#define JR2_IRQ_IGTR          (24)
#define JR2_IRQ_XTR_RDY       (25)
#define JR2_IRQ_INJ_RDY       (26)
#define JR2_IRQ_PCIE          (27)
#define JR2_IRQ_OAM_VOP       (28)
#endif


#define JR2_IRQ_DEST_CPU0      0 /* IRQ destination CPU0 */
#define JR2_IRQ_DEST_CPU1      1 /* IRQ destination CPU1 */
#define JR2_IRQ_DEST_EXT0      2 /* IRQ destination EXT0 */
#define JR2_IRQ_DEST_EXT1      3 /* IRQ destination EXT1 */

#define IRQ_DEST(conf) ((u32) ((conf->external ? JR2_IRQ_DEST_EXT0 : JR2_IRQ_DEST_CPU0) + conf->destination))

static vtss_rc jr2_misc_irq_destination(vtss_state_t *vtss_state,
                                        u32 mask,
                                        u32 destination)
{
    JR2_WRM_CLR(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(JR2_IRQ_DEST_CPU0), mask);
    JR2_WRM_CLR(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(JR2_IRQ_DEST_CPU1), mask);
    JR2_WRM_CLR(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(JR2_IRQ_DEST_EXT0), mask);
    JR2_WRM_CLR(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(JR2_IRQ_DEST_EXT1), mask);
    JR2_WRM_SET(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(destination), mask);
    return VTSS_RC_OK;
}

static vtss_rc jr2_misc_irq_remap(vtss_state_t *vtss_state,
                                  u32 mask,
                                  const vtss_irq_conf_t *const conf)
{
    u32 destination = IRQ_DEST(conf);

    /* Map to requested (single) destination */
    VTSS_RC(jr2_misc_irq_destination(vtss_state, mask, destination));

    /* Always use sticky IRQ's */
    JR2_WRM_CLR(VTSS_ICPU_CFG_INTR_INTR_BYPASS, mask);

    /* Set up derived registers - PCIe */
    if (vtss_state->sys_config.using_pcie) {
        u32 external0, external1;
        // Enable PCIe IRQ
        JR2_WRM_CLR(VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG,
                    VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA);
        // Read current ext0 / ext1 mapping
        JR2_RD(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(JR2_IRQ_DEST_EXT0), &external0);
        JR2_RD(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(JR2_IRQ_DEST_EXT1), &external1);
        // Configure IRQ if external has a dest
        JR2_WRM_CTL(VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG(0), (external0 != 0),
                    VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_FALLING_ENA(1)|
                    VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_RISING_ENA(1));
        JR2_WRM_CTL(VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG(1), (external1 != 0),
                    VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_FALLING_ENA(1)|
                    VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_RISING_ENA(1));
        // Select EXT_DST1 if JR2_IRQ_DEST_EXT1 non-zero
        JR2_WRM_CTL(VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG, (external1 != 0),
                    VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL(1));
        // Enable PCIe if
        JR2_WRM_CTL(VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG, (external0|external1),
                    VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA(1));
    }

    /* TBD - EXT  IRQ */

    return VTSS_RC_OK;
}

static vtss_rc jr2_misc_irq_cfg(vtss_state_t *vtss_state,
                                const vtss_irq_t irq,
                                const vtss_irq_conf_t *const conf)
{
    vtss_rc rc = VTSS_RC_OK;
    if (conf->destination > 1) {
        rc = VTSS_RC_ERROR;
    } else {
        switch (irq) {
            case VTSS_IRQ_XTR:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_XTR_RDY), conf);
                break;
            case VTSS_IRQ_FDMA_XTR:    /* NB: XTR and INJ are lumped together */
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_FDMA), conf);
                break;
            case VTSS_IRQ_SOFTWARE:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_SW0)|VTSS_BIT(JR2_IRQ_SW1), conf);
                break;
            case VTSS_IRQ_PTP_RDY:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_PTP_RDY), conf);
                break;
            case VTSS_IRQ_PTP_SYNC:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_PTP_SYNC), conf);
                break;
            case VTSS_IRQ_EXT0:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_EXT0), conf);
                break;
            case VTSS_IRQ_SGPIO:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_SGPIO1), conf);
                break;
#if !defined(VTSS_ARCH_SERVAL_T)
            case VTSS_IRQ_SGPIO2:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_SGPIO2), conf);
                break;
#endif
            case VTSS_IRQ_EXT1:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_EXT1), conf);
                break;
            case VTSS_IRQ_OAM:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_OAM_VOP), conf);
                break;
            case VTSS_IRQ_GPIO:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_GPIO), conf);
                break;
            case VTSS_IRQ_DEV_ALL:
                rc = jr2_misc_irq_remap(vtss_state, VTSS_BIT(JR2_IRQ_DEV_ALL), conf);
                break;
            default:
                rc = VTSS_RC_ERROR;
        }
    }
    return rc;
}

static vtss_rc jr2_misc_irq_status(vtss_state_t *vtss_state, vtss_irq_status_t *status)
{
    u32 val, uio_irqs, dest;

    VTSS_MEMSET(status, 0, sizeof(*status));

    // Which interrupts are taken care of in user-space?
    if (vtss_state->sys_config.using_pcie) {
        // If running on an external CPU connected via PCIe, either external IRQ0 or
        // external IRQ1 may be routed through the PCIe interrupt. Which one
        // can be read from ICPU_CFG:PCIE:PCIE_INTR_COMMON_CFG.LEGACY_MODE_INTR_SEL.
        JR2_RD(VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG, &val);
        dest = VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL(val) == 0 ? JR2_IRQ_DEST_EXT0 : JR2_IRQ_DEST_EXT1;
    } else {
        // When running on the internal CPU, JR_IRQ_DEST_CPU1 is - by convention and in
        // agreement with the kernel - used in user-space.
        dest = JR2_IRQ_DEST_CPU1;
    }

    JR2_RD(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(dest), &uio_irqs);

    // Who's interrupting?
    JR2_RD(VTSS_ICPU_CFG_INTR_INTR_IDENT, &val);

    // Only consider UIO interrupts
    val &= uio_irqs;

    status->raw_ident = val;
    JR2_RD(VTSS_ICPU_CFG_INTR_INTR_RAW, &status->raw_status);
    JR2_RD(VTSS_ICPU_CFG_INTR_INTR_ENA, &status->raw_mask);
    JR2_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_CLR, val);
    status->raw_status &= uio_irqs;
    status->raw_mask   &= uio_irqs;

    if (val & VTSS_BIT(JR2_IRQ_FDMA)) {
        u32 man_intr;
        JR2_RD(VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR, &man_intr);
        if (man_intr & VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_XTR_ANY_RDY) {
            status->active |= VTSS_BIT(VTSS_IRQ_FDMA_XTR);
        }
    }

    if (val & (VTSS_BIT(JR2_IRQ_SGPIO1))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SGPIO);
    }

#if !defined(VTSS_ARCH_SERVAL_T)
    if (val & (VTSS_BIT(JR2_IRQ_SGPIO2))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SGPIO2);
    }
#endif

    if (val & (VTSS_BIT(JR2_IRQ_EXT0))) {
        status->active |= VTSS_BIT(VTSS_IRQ_EXT0);
    }

    if (val & (VTSS_BIT(JR2_IRQ_EXT1))) {
        VTSS_I("val:0x%X", val);
        status->active |= VTSS_BIT(VTSS_IRQ_EXT1);
    }

    if (val & (VTSS_BIT(JR2_IRQ_XTR_RDY))) {
        status->active |= VTSS_BIT(VTSS_IRQ_XTR);
    }

    if(val & (VTSS_BIT(JR2_IRQ_SW0)|VTSS_BIT(JR2_IRQ_SW1))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SOFTWARE);
    }

    if(val & (VTSS_BIT(JR2_IRQ_PTP_RDY))) {
        status->active |= VTSS_BIT(VTSS_IRQ_PTP_RDY);
    }

    if (val & (VTSS_BIT(JR2_IRQ_PTP_SYNC))) {
        status->active |= VTSS_BIT(VTSS_IRQ_PTP_SYNC);
    }

    if (val & (VTSS_BIT(JR2_IRQ_OAM_VOP))) {
        status->active |= VTSS_BIT(VTSS_IRQ_OAM);
    }

    if (val & (VTSS_BIT(JR2_IRQ_GPIO))) {
        status->active |= VTSS_BIT(VTSS_IRQ_GPIO);
    }

    if (val & (VTSS_BIT(JR2_IRQ_DEV_ALL))) {
        status->active |= VTSS_BIT(VTSS_IRQ_DEV_ALL);
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_misc_irq_enable(vtss_state_t *vtss_state,
                                    const vtss_irq_t irq,
                                    const BOOL enable)
{
    u32 mask = 0;
    switch (irq) {
        case VTSS_IRQ_XTR:
            mask = VTSS_BIT(JR2_IRQ_XTR_RDY);
            break;
        case VTSS_IRQ_FDMA_XTR:
            JR2_WRM_CTL(VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA, enable,
                        VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_XTR_ANY_RDY_ENA);
            mask = VTSS_BIT(JR2_IRQ_FDMA);
            break;
        case VTSS_IRQ_SOFTWARE:
            mask = VTSS_BIT(JR2_IRQ_SW0)|VTSS_BIT(JR2_IRQ_SW1);
            break;
        case VTSS_IRQ_PTP_RDY:
            mask = VTSS_BIT(JR2_IRQ_PTP_RDY);
            break;
        case VTSS_IRQ_PTP_SYNC:
            mask = VTSS_BIT(JR2_IRQ_PTP_SYNC);
            break;
        case VTSS_IRQ_EXT0:
            mask = VTSS_BIT(JR2_IRQ_EXT0);
            break;
        case VTSS_IRQ_EXT1:
            mask = VTSS_BIT(JR2_IRQ_EXT1);
            VTSS_D("enable:%d, mask:0x%X", enable, mask);
            break;
        case VTSS_IRQ_SGPIO:
            mask = VTSS_BIT(JR2_IRQ_SGPIO1);
            VTSS_D("enable:%d, mask:0x%X", enable, mask);
            break;
#if !defined(VTSS_ARCH_SERVAL_T)
        case VTSS_IRQ_SGPIO2:
            mask = VTSS_BIT(JR2_IRQ_SGPIO2);
            VTSS_D("enable:%d, mask:0x%X", enable, mask);
            break;
#endif
        case VTSS_IRQ_OAM:
            mask = VTSS_BIT(JR2_IRQ_OAM_VOP);
            break;
        case VTSS_IRQ_GPIO:
            mask = VTSS_BIT(JR2_IRQ_GPIO);
            break;
        case VTSS_IRQ_DEV_ALL:
            mask = VTSS_BIT(JR2_IRQ_DEV_ALL);
            break;
        default:
            return VTSS_RC_ERROR;
    }
    /* Ack sticky bits */
    JR2_WR(VTSS_ICPU_CFG_INTR_INTR_STICKY, mask);
    if (irq == VTSS_IRQ_FDMA_XTR) {
        JR2_WRM_CTL(VTSS_ICPU_CFG_FDMA_FDMA_INTR_ENA, enable, 1); /* Always using ch 1 */
        JR2_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_SET, mask); /* Always enable top FDMA (cascading) IRQ */
    } else {
        if(enable) {
            JR2_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_SET, mask);
        } else {
            JR2_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_CLR, mask);
        }
    }
    return VTSS_RC_OK;
}
#endif  /* VTSS_FEATURE_IRQ_CONTROL */

static vtss_rc jr2_poll_1sec(vtss_state_t *vtss_state)
{
    /* Poll function groups */
    return vtss_jr2_init_groups(vtss_state, VTSS_INIT_CMD_POLL);
}

/* =================================================================
 *  Miscellaneous - GPIO
 * =================================================================*/

vtss_rc vtss_jr2_gpio_mode(vtss_state_t *vtss_state,
                            const vtss_chip_no_t   chip_no,
                            const vtss_gpio_no_t   gpio_no,
                            const vtss_gpio_mode_t mode)
{
    u32 mask, alt_0 = 0, alt_1 = 0;

    if (gpio_no >= 32) {
        mask = VTSS_BIT(gpio_no - 32);
    } else {
        mask = VTSS_BIT(gpio_no);
    }

    // Disable IRQ
    if (gpio_no >= 32) {
        JR2_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA1, mask);
    } else {
        JR2_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, mask);
    }
    switch (mode) {
    case VTSS_GPIO_OUT:
    case VTSS_GPIO_IN:
    case VTSS_GPIO_IN_INT:
        if (gpio_no >= 32) {
            JR2_WRM_CTL(VTSS_DEVCPU_GCB_GPIO_GPIO_OE1, mode == VTSS_GPIO_OUT, mask);
        } else {
            JR2_WRM_CTL(VTSS_DEVCPU_GCB_GPIO_GPIO_OE, mode == VTSS_GPIO_OUT, mask);
        }
        break;
    case VTSS_GPIO_ALT_0:
        alt_0 = mask;
        break;
    case VTSS_GPIO_ALT_1:
        alt_1 = mask;
        break;
    case VTSS_GPIO_ALT_2:
        alt_0 = mask;
        alt_1 = mask;
        break;
    default:
        VTSS_E("illegal mode");
        return VTSS_RC_ERROR;
    }
    if (gpio_no >= 32) {
        JR2_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT1(0), alt_0, mask);
        JR2_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT1(1), alt_1, mask);
    } else {
        JR2_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(0), alt_0, mask);
        JR2_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(1), alt_1, mask);
    }
    if (mode == VTSS_GPIO_IN_INT) {
        if (gpio_no >= 32) {
            JR2_WRM_SET(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA1, mask);
        } else {
            JR2_WRM_SET(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, mask);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_gpio_read(vtss_state_t *vtss_state,
                              const vtss_chip_no_t  chip_no,
                              const vtss_gpio_no_t  gpio_no,
                              BOOL                  *const value)
{
    u32 val, mask;

    if (gpio_no >= 32) {
        mask = VTSS_BIT(gpio_no - 32);
        JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_IN1, &val);
    } else {
        mask = VTSS_BIT(gpio_no);
        JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_IN, &val);
    }

    *value = VTSS_BOOL(val & mask);
    return VTSS_RC_OK;
}

static vtss_rc jr2_gpio_write(vtss_state_t *vtss_state,
                               const vtss_chip_no_t  chip_no,
                               const vtss_gpio_no_t  gpio_no,
                               const BOOL            value)
{
    u32 mask;

    if (gpio_no >= 32) {
        mask = VTSS_BIT(gpio_no - 32);
        if (value) {
            JR2_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_SET1, mask);
        } else {
            JR2_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_CLR1, mask);
        }
    } else {
        mask = VTSS_BIT(gpio_no);
        if (value) {
            JR2_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_SET, mask);
        } else {
            JR2_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_CLR, mask);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_gpio_event_poll(vtss_state_t          *vtss_state,
                                   const vtss_chip_no_t  chip_no,
                                   BOOL                  *const events)
{
    u32 pending, mask, i;

    JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR, &pending);
    JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, &mask);
    pending &= mask;
    JR2_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR, pending);

    for (i = 0; i < 32; i++) {
        events[i] = (pending & 1 << i) ? TRUE : FALSE;
    }

    JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR1, &pending);
    JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA1, &mask);
    pending &= mask;
    JR2_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR1, pending);

    for (i = 32; i < VTSS_GPIOS; i++) {
        events[i] = (pending & 1 << (i - 32)) ? TRUE : FALSE;
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_gpio_event_enable(vtss_state_t          *vtss_state,
                                    const vtss_chip_no_t  chip_no,
                                    const vtss_gpio_no_t  gpio_no,
                                    const BOOL            enable)
{

    u32 mask;

    if (gpio_no >= 32) {
        mask = VTSS_BIT(gpio_no - 32);
        JR2_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA1, enable << (gpio_no - 32), mask);
    } else {
        mask = VTSS_BIT(gpio_no);
        JR2_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, enable << gpio_no, mask);
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_sgpio_init(vtss_state_t *vtss_state)
{
    u32  grp, bit;

    // Gotta change the interrupt type for all SGPIOs from its default,
    // which is level, to something else to avoid spurious interrupts
    // when failing or unable (due to board layout) to initialize the
    // polarity of the level interrupts correct.
    for (grp = 0; grp < vtss_state->misc.sgpio_group_count; grp++) {
        for (bit = 0; bit < 4; bit++) {
            // Enable rising edge triggered interrupt
#if defined(VTSS_ARCH_SERVAL_T)
            JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_TRIGGER0(bit), 0xFFFFFFFF);
            JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_TRIGGER1(bit), 0xFFFFFFFF);
#else
            JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_TRIGGER0(grp, bit), 0xFFFFFFFF);
            JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_TRIGGER1(grp, bit), 0xFFFFFFFF);
#endif
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_sgpio_event_poll(vtss_state_t             *vtss_state,
                                    const vtss_chip_no_t     chip_no,
                                    const vtss_sgpio_group_t group,
                                    const u32                bit,
                                    BOOL                     *const events)
{
    u32 i, val;

#if defined(VTSS_ARCH_SERVAL_T)
    JR2_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_IDENT(bit), &val);
    JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR(bit), val);  /* Clear pending */
#else
    JR2_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_IDENT(group, bit), &val);
    JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR(group, bit), val);  /* Clear pending */
#endif

    VTSS_I("SGPIO%u Interrupt ident for bit %u: 0x%08x", group, bit, val);

    /* Setup serial IO port enable register */
    for (i = 0; i < 32; i++) {
        events[i] = VTSS_BOOL(val & (1<<i));
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_sgpio_event_enable(vtss_state_t             *vtss_state,
                                      const vtss_chip_no_t     chip_no,
                                      const vtss_sgpio_group_t group,
                                      const u32                port,
                                      const u32                bit,
                                      const BOOL               enable)
{
    u32 i, mask = (1 << port);

    if (enable) {
        VTSS_D("group:%d mask:0x%X, bit:0x%X, 0x%X", group, mask, bit, VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit));
#if defined(VTSS_ARCH_SERVAL_T)
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR(bit), mask, mask); // Clear any pending interrupts, so we don't get any spurious interrupt when we enable.
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_ENA, mask, mask);
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG,
                VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit),
                VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit)); // Enable only the bit in question.
#else
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR(group, bit), mask, mask); // Clear any pending interrupts, so we don't get any spurious interrupt when we enable.
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_ENA(group), mask, mask);  // Enable only the bit in question.
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG(group),
                VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit),
                VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit)); // Enable only the bit in question.
#endif /* VTSS_ARCH_SERVAL_T */

    } else {

        VTSS_D("Disable port:%d, group:%d, bit:%d", port, group, bit);
#if defined(VTSS_ARCH_SERVAL_T)
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_ENA, 0, mask);
#else
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_ENA(group), 0, mask);
#endif /* VTSS_ARCH_SERVAL_T */
        for (i=0; i<32; ++i) {
            if (vtss_state->misc.sgpio_event_enabled[chip_no][group].enable[i][bit]) {
                break;
            }
        }
        if (i == 32) {
#if defined(VTSS_ARCH_SERVAL_T)
            JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG,
                    0,
                    VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit)); // Clear only the bit in question.
#else
            JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG(group),
                    0,
                    VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit)); // Clear only the bit in question.
#endif /* VTSS_ARCH_SERVAL_T */
        }
    }

    return VTSS_RC_OK;

}

static vtss_rc jr2_sgpio_conf_set(vtss_state_t *vtss_state,
                                   const vtss_chip_no_t     chip_no,
                                   const vtss_sgpio_group_t group,
                                   const vtss_sgpio_conf_t  *const conf)
{
    u32  i, port, val = 0, pol = 0, bmode[2], bit_idx, value, mask;
    BOOL pol_high;

    /* Setup serial IO port enable register */
    for (port = 0; port < 32; port++) {
        if (conf->port_conf[port].enabled)
            val |= VTSS_BIT(port);
    }

#if defined(VTSS_ARCH_SERVAL_T)
    JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_ENA, val);
#else
    JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_ENA(group), val);
#endif /* VTSS_ARCH_SERVAL_T */

    /*
     * Setup general configuration register
     *
     * The burst gap is 0x1f(33.55ms)
     * The load signal is active low
     * The auto burst repeat function is on
     * The SIO reverse output is off
     */
    for (i = 0; i < 2; i++) {
        switch (conf->bmode[i]) {
        case VTSS_SGPIO_BMODE_TOGGLE:
            if (i == 0) {
                VTSS_E("blink mode 0 does not support TOGGLE (group:%d)",group);
                return VTSS_RC_ERROR;
            }
            bmode[i] = 3;
            break;
        case VTSS_SGPIO_BMODE_0_625:
            if (i == 1) {
                VTSS_E("blink mode 1 does not support 0.625 Hz");
                return VTSS_RC_ERROR;
            }
            bmode[i] = 3;
            break;
        case VTSS_SGPIO_BMODE_1_25:
            bmode[i] = 2;
            break;
        case VTSS_SGPIO_BMODE_2_5:
            bmode[i] = 1;
            break;
        case VTSS_SGPIO_BMODE_5:
            bmode[i] = 0;
            break;
        default:
            return VTSS_RC_ERROR;
        }
    }

    value = (VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BMODE_0(bmode[0]) |
             VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BMODE_1(bmode[1]) |
             VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BURST_GAP(0) |
             VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_PORT_WIDTH(conf->bit_count - 1) |
             VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_AUTO_REPEAT(1));
    mask = (VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BMODE_0 |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BMODE_1 |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BURST_GAP |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_PORT_WIDTH |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_AUTO_REPEAT);
#if defined(VTSS_ARCH_SERVAL_T)
    JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG, value, mask);
    JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK, /* 12.5MHz (0x14) */
            VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ(0x14) |
            VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SYS_CLK_PERIOD(0x40),
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SYS_CLK_PERIOD);
#endif /* VTSS_ARCH_SERVAL_T */
#if defined(VTSS_ARCH_JAGUAR_2_C)
    JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG(group), value, mask);
    JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK(group), /* 12.5MHz (0x14) */
            VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ(0x14) |
            VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SYS_CLK_PERIOD(0x40),
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SYS_CLK_PERIOD);
#endif /* VTSS_ARCH_JAGUAR_2_C */
#if defined(VTSS_ARCH_JAGUAR_2_B)
    JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG(group), value, mask);
    JR2_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK(group), 0x14); /* 12.5MHz (0x14) */
#endif /* VTSS_ARCH_JAGUAR_2_B */

    /*
     * Configuration of output data values
     * The placement of the source select bits for each output bit in the register:
     * Output bit0 : (2 downto 0)
     * Output bit1 : (5 downto 3)
     * Output bit2 : (8 downto 6)
     * Output bit3 : (11 downto 9)
    */

    /* The VTSS_SGPIO_MODE_*_ACTIVITY_INV modes are not directly supported in the BIT_SOURCE field */
    /* Instead, the INV can be accomplished through the polarity bit */

    for (port = 0; port < 32; port++) {
        mask = (1 << port);
        for (pol = 0, val = 0, bit_idx = 0; bit_idx < 4; bit_idx++) {
            /* Set output bit n */
            if (conf->port_conf[port].mode[bit_idx] == VTSS_SGPIO_MODE_0_ACTIVITY_INV) {
                val |= VTSS_ENCODE_BITFIELD(VTSS_SGPIO_MODE_0_ACTIVITY, (bit_idx * 3), 3);
                pol |= (1 << bit_idx); // Inversed polarity
            } else if (conf->port_conf[port].mode[bit_idx] == VTSS_SGPIO_MODE_1_ACTIVITY_INV) {
                val |= VTSS_ENCODE_BITFIELD(VTSS_SGPIO_MODE_1_ACTIVITY, (bit_idx * 3), 3);
                pol |= (1 << bit_idx); // Inversed polarity
            } else {
                val |= VTSS_ENCODE_BITFIELD(conf->port_conf[port].mode[bit_idx], (bit_idx * 3), 3);
            }

            // Setup the interrupt polarity
            pol_high = conf->port_conf[port].int_pol_high[bit_idx];
            value = (pol_high ? 0 : mask);
#if defined(VTSS_ARCH_SERVAL_T)
            JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_POL(bit_idx), value, mask);
#else
            JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_POL(group, bit_idx), value, mask);
#endif /* VTSS_ARCH_SERVAL_T */
            VTSS_N("group:%d, port:%d, bit_idx:%d, int_pol_high:%d", group, port, bit_idx, pol_high);
        }

        value = VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_SOURCE(val);
        mask = VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_SOURCE;
#if defined(VTSS_ARCH_SERVAL_T)
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG(port), value, mask);
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG(port),
                VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_POLARITY(pol),
                VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_POLARITY);
#else
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG(group, port), value, mask);
        JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG(group, port),
                VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_POLARITY(pol),
                VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_POLARITY);

#endif /* VTSS_ARCH_SERVAL_T */
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_sgpio_read(vtss_state_t *vtss_state,
                               const vtss_chip_no_t     chip_no,
                               const vtss_sgpio_group_t group,
                               vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS])
{
    u32 i, port, value;

    for (i = 0; i < 4; i++) {
#if defined(VTSS_ARCH_SERVAL_T)
        JR2_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INPUT_DATA(i), &value);
#else
        JR2_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INPUT_DATA(group, i), &value);
#endif /* VTSS_ARCH_SERVAL_T */
        for (port = 0; port < 32; port++) {
            data[port].value[i] = VTSS_BOOL(value & (1 << port));
        }
    }
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

/* - Debug print --------------------------------------------------- */

#define JR_DEBUG_GPIO(pr, addr, name) JR2_DEBUG_REG_NAME(pr, DEVCPU_GCB, GPIO_GPIO_##addr, "GPIO_"name)
#define JR_DEBUG_SIO(pr, addr, name) JR2_DEBUG_REG_NAME(pr, DEVCPU_GCB, SIO_CTRL_SIO_##addr, "SIO_"name)
#define JR_DEBUG_SIO_INST(pr, addr, i, name) vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_DEVCPU_GCB_SIO_CTRL_SIO_##addr, i, "SIO_"name)


#define JR_DEBUG_TGT(pr, name) jr_debug_tgt(pr, #name, VTSS_TO_##name)


static vtss_rc jr2_debug_misc(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32  i, g, count;
    char name[32];
    pr("Name          Target\n");

    vtss_jr2_debug_reg_header(pr, "GPIOs");
    JR_DEBUG_GPIO(pr, OUT, "OUT");
    JR_DEBUG_GPIO(pr, OUT1, "OUT1");
    JR_DEBUG_GPIO(pr, OE, "OE");
    JR_DEBUG_GPIO(pr, OE1, "OE1");
    JR_DEBUG_GPIO(pr, IN, "IN");
    JR_DEBUG_GPIO(pr, IN1, "IN1");
    JR_DEBUG_GPIO(pr, INTR, "INTR");
    JR_DEBUG_GPIO(pr, INTR_ENA, "INTR_ENA");
    JR_DEBUG_GPIO(pr, INTR_IDENT, "INTR_IDENT");
    JR_DEBUG_GPIO(pr, ALT(0), "ALT_0(0-31)");
    JR_DEBUG_GPIO(pr, ALT(1), "ALT_1(0-31)");
    JR_DEBUG_GPIO(pr, ALT1(0), "ALT1_0(32-63)");
    JR_DEBUG_GPIO(pr, ALT1(1), "ALT1_1(32-63)");

    /* pr("\n"); */
    /* vtss_jr2_debug_reg_header(pr, "I2C/TWI"); */
    /* JR2_DEBUG_REG_NAME(pr, TWI, TWI_CFG(VTSS_TO_TWI),       "TWI_CFG"); */
    /* JR2_DEBUG_REG_NAME(pr, TWI, TWI_TAR(VTSS_TO_TWI),       "TWI_TAR"); */
    /* JR2_DEBUG_REG_NAME(pr, TWI, TWI_INTR_STAT(VTSS_TO_TWI), "INTR_STAT"); */
    /* JR2_DEBUG_REG_NAME(pr, TWI, TWI_INTR_MASK(VTSS_TO_TWI), "INTR_MASK"); */
    /* JR2_DEBUG_REG_NAME(pr, TWI, TWI_STAT(VTSS_TO_TWI),      "TWI_STAT"); */
    /* JR2_DEBUG_REG_NAME(pr, TWI, TWI_TXFLR(VTSS_TO_TWI),     "TWI_TXFLR"); */
    /* JR2_DEBUG_REG_NAME(pr, TWI, TWI_RXFLR(VTSS_TO_TWI),     "TWI_RXFLR"); */

    pr("\n");

#if defined(VTSS_ARCH_SERVAL_T)
    count = 1;
#else
    count = 3;
#endif /* VTSS_ARCH_SERVAL_T */
    for (g = 0; g < count; g++) {
        VTSS_SPRINTF(name, "SGPIOs Group:%u", g);
        vtss_jr2_debug_reg_header(pr, name);
#if defined(VTSS_ARCH_SERVAL_T)
        for (i = 0; i < 4; i++) {
            JR_DEBUG_SIO_INST(pr, INPUT_DATA(i), i, "INPUT_DATA");
            JR_DEBUG_SIO_INST(pr, INTR_POL(i), i, "INTR_POL");
            JR_DEBUG_SIO_INST(pr, INTR(i), i, "INTR");
        }
        JR_DEBUG_SIO(pr, INTR_ENA, "INTR_ENA");
        JR_DEBUG_SIO(pr, PORT_ENA, "PORT_ENA");
        JR_DEBUG_SIO(pr, CFG, "CFG");
        JR_DEBUG_SIO(pr, CLOCK, "CLOCK");
        for (i = 0; i < 32; i++) {
            JR_DEBUG_SIO_INST(pr, PORT_CFG(i), i, "PORT_CFG");
        }
#else
        for (i = 0; i < 4; i++) {
            JR_DEBUG_SIO_INST(pr, INPUT_DATA(g,i), i, "INPUT_DATA");
            JR_DEBUG_SIO_INST(pr, INTR_POL(g,i), i, "INTR_POL");
            JR_DEBUG_SIO_INST(pr, INTR(g,i), i, "INTR");
        }
        JR_DEBUG_SIO(pr, INTR_ENA(g), "INTR_ENA");
        JR_DEBUG_SIO(pr, PORT_ENA(g), "PORT_ENA");
        JR_DEBUG_SIO(pr, CFG(g), "CFG");
        JR_DEBUG_SIO(pr, CLOCK(g), "CLOCK");
        for (i = 0; i < 32; i++) {
            JR_DEBUG_SIO_INST(pr, PORT_CFG(g,i), i, "PORT_CFG");
        }
#endif /* VTSS_ARCH_SERVAL_T */
        pr("\n");
    }

    vtss_jr2_debug_reg_header(pr, "IRQs");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_RAW, "INTR_RAW");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_TRIGGER(0), "INTR_TRIGGER(0)");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_FORCE, "INTR_FORCE");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_STICKY, "INTR_STICKY");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_BYPASS, "INTR_BYPASS");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_ENA, "INTR_ENA");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_ENA_CLR, "INTR_ENA_CLR");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_ENA_SET, "INTR_ENA_SET");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_IDENT, "INTR_IDENT");

    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, DEV_INTR_ENA, "DEV_INTR_ENA");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, DEV_INTR_STICKY, "DEV_INTR_STICKY");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, DEV_INTR_IDENT, "DEV_INTR_IDENT");

    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, DST_INTR_MAP(0), "DST_INTR_MAP(0)");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, DST_INTR_IDENT(0), "DST_INTR_IDENT(0)");

    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, EXT_SRC_INTR_POL, "EXT_SRC_INTR_POL");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, EXT_DST_INTR_POL, "EXT_DST_INTR_POL");
    JR2_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, EXT_DST_INTR_DRV, "EXT_DST_INTR_DRV");


    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_misc_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MISC, jr2_debug_misc, vtss_state, pr, info));
    return VTSS_RC_OK;
}



/* - Initialization ------------------------------------------------ */

vtss_rc vtss_jr2_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_misc_state_t *state = &vtss_state->misc;

    if (cmd == VTSS_INIT_CMD_CREATE) {
        state->reg_read = jr2_reg_read;
        state->reg_write = jr2_reg_write;
        state->chip_id_get = vtss_jr2_chip_id_get;
        state->poll_1sec = jr2_poll_1sec;
        state->gpio_mode = vtss_jr2_gpio_mode;
        state->gpio_read = jr2_gpio_read;
        state->gpio_write = jr2_gpio_write;
        state->sgpio_conf_set = jr2_sgpio_conf_set;
        state->sgpio_read = jr2_sgpio_read;
        state->sgpio_event_enable = jr2_sgpio_event_enable;
        state->sgpio_event_poll = jr2_sgpio_event_poll;
        state->gpio_event_enable = jr2_gpio_event_enable;
        state->gpio_event_poll = jr2_gpio_event_poll;
        state->ptp_event_poll = jr2_ptp_event_poll;
        state->ptp_event_enable = jr2_ptp_event_enable;
        state->dev_all_event_poll = jr2_dev_all_event_poll;
        state->dev_all_event_enable = jr2_dev_all_event_enable;
        state->intr_cfg = jr2_intr_cfg;
        state->intr_pol_negation = jr2_intr_pol_negation;
#ifdef VTSS_FEATURE_IRQ_CONTROL
        vtss_state->misc.irq_cfg = jr2_misc_irq_cfg;
        vtss_state->misc.irq_status = jr2_misc_irq_status;
        vtss_state->misc.irq_enable = jr2_misc_irq_enable;
#endif  /* VTSS_FEATURE_IRQ_CONTROL */
        state->gpio_count = JR2_GPIOS;
        state->sgpio_group_count = JR2_SGPIO_GROUPS;

#if defined(VTSS_FEATURE_EEE)
        vtss_state->eee.port_conf_set   = jr2_eee_port_conf_set;
#endif /* VTSS_FEATURE_EEE */
#if defined(VTSS_FEATURE_FAN)
        vtss_state->fan.controller_init = jr2_fan_controller_init;
        vtss_state->fan.cool_lvl_get    = jr2_fan_cool_lvl_get;
        vtss_state->fan.cool_lvl_set    = jr2_fan_cool_lvl_set;
        vtss_state->fan.rotation_get    = jr2_fan_rotation_get;
#endif /* VTSS_FEATURE_FAN */

#if defined(VTSS_FEATURE_TEMP_SENSOR) && (defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C))
        vtss_state->temp_sensor.chip_temp_init = jr2_temp_sensor_init;
        vtss_state->temp_sensor.chip_temp_get  = jr2_temp_sensor_get;
#endif /* VTSS_FEATURE_TEMP_SENSOR */
    } else if (cmd == VTSS_INIT_CMD_INIT) {
        VTSS_RC(jr2_sgpio_init(vtss_state));
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_JAGUAR_2 */
