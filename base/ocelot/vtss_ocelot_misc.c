// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_ocelot_cil.h"

#if defined(VTSS_ARCH_OCELOT)

// Avoid Lint Warning 572: Excessive shift value (precision 1 shifted right by 2), which occurs
// in this file because (t) - VTSS_IO_ORIGIN1_OFFSET == 0 for t = VTSS_TO_CFG (i.e. ICPU_CFG), and 0 >> 2 gives a lint warning.
/*lint --e{572} */

/* - CIL functions ------------------------------------------------- */

/* =================================================================
 *  EEE - Energy Efficient Ethernet
 * =================================================================*/
static vtss_rc srvl_eee_port_conf_set(vtss_state_t *vtss_state,
                                      const vtss_port_no_t       port_no, 
                                      const vtss_eee_port_conf_t *const conf)
{
    u32            closest_match_index, closest_match, i, requested_time;
    u32            eee_cfg_reg = 0x0; // SYS::EEE_CFG register value.
    vtss_port_no_t chip_port = VTSS_CHIP_PORT(port_no);

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
        VTSS_E("Out of bounds: chip_port:%d, VTSS_PORT_ARRAY_SIZE:%d", port_no, VTSS_PORT_ARRAY_SIZE);
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
            VTSS_I("Link partner doesn't support EEE - Keeping EEE disabled. Port:%d", chip_port);
        } else if (!vtss_state->port.conf[port_no].fdx) {
            // EEE and Half duplex are not supposed to work together, so we disables EEE in the case where the port is in HDX mode.
            VTSS_I("EEE disabled due to that port is in HDX mode, port:%d", chip_port);
        } else {
            eee_cfg_reg |= VTSS_F_DEV_PORT_MODE_EEE_CFG_EEE_ENA;
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

    eee_cfg_reg |= VTSS_F_DEV_PORT_MODE_EEE_CFG_EEE_TIMER_WAKEUP(closest_match_index);


    // EEE holdoff timer
    eee_cfg_reg |= VTSS_F_DEV_PORT_MODE_EEE_CFG_EEE_TIMER_HOLDOFF(0x5) | VTSS_F_DEV_PORT_MODE_EEE_CFG_EEE_TIMER_AGE(0x23);


    // Registers write
    SRVL_WR(VTSS_DEV_PORT_MODE_EEE_CFG(VTSS_TO_DEV(chip_port)), eee_cfg_reg);

    // EEE fast queues
    eee_cfg_reg = VTSS_F_QSYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES(conf->eee_fast_queues);

    VTSS_N("eee_cfg_reg = 0x%X, conf->tx_tw = %d", eee_cfg_reg, conf->tx_tw);
    SRVL_WR(VTSS_QSYS_SYSTEM_EEE_CFG(chip_port), eee_cfg_reg);

    // Setting Buffer size to 3 Kbyte & 255 frames.
    SRVL_WR(VTSS_QSYS_SYSTEM_EEE_THRES, 0x3EFF);

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_FAN)
/* =================================================================
 * FAN speed control
 * =================================================================*/
static vtss_rc srvl_fan_controller_init(vtss_state_t *vtss_state,
                                        const vtss_fan_conf_t *const spec)
{
    // Calculated from 156.25MHz/fan_pwm_freq/256
    u32 pwm_freq[] = {
           24, // 25kHz
         5086, // 120Hz
         6104, // 100Hz
         7629, // 80Hz
        10173, // 60Hz
        15259, // 40Hz
        30518, // 20Hz
        61035, // 10Hz
    };

    // Set GPIO alternate functions. TACHO is bit 20 - See Ocelot Datasheet Table 163.
    VTSS_RC(vtss_srvl_gpio_mode(vtss_state, 0, 20, VTSS_GPIO_ALT_1));
    // Set GPIO alternate functions. PWM is bit 21 - See Ocelot Datasheet Table 163.
    VTSS_RC(vtss_srvl_gpio_mode(vtss_state, 0, 21, VTSS_GPIO_ALT_1));

    // Set PWM frequency
    if (spec->fan_pwm_freq < (sizeof(pwm_freq)/sizeof(pwm_freq[0]))) {
        SRVL_WR(VTSS_DEVCPU_GCB_FAN_CTRL_PWM_FREQ, pwm_freq[spec->fan_pwm_freq]);
    } else {
        VTSS_E("spec.fan_pwm_freq = %u is out of range 0..%u", spec->fan_pwm_freq, (u32)(sizeof(pwm_freq)/sizeof(pwm_freq[0]) - 1));
    }

    // Set PWM polarity
    SRVL_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
             spec->fan_low_pol ? VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_INV_POL : 0,
             VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_INV_POL);

    // Set PWM open collector
    SRVL_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
             spec->fan_open_col ? VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_PWM_OPEN_COL_ENA : 0,
             VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_PWM_OPEN_COL_ENA);

    // Set fan speed measurement
    if (spec->type == VTSS_FAN_3_WIRE_TYPE) {
        // Enable gating for 3-wire fan types.
        SRVL_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
                 VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_GATE_ENA,
                 VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_GATE_ENA);
    } else {
        // For 4-wire fan types we need to disable gating (2-wire types doesn't matter)
        SRVL_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
                 0,
                 VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_GATE_ENA);
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_fan_cool_lvl_set(vtss_state_t *vtss_state, u8 lvl)
{
    // Set PWM duty cycle (fan speed)
    SRVL_WRM(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG,
             VTSS_F_DEVCPU_GCB_FAN_CTRL_FAN_CFG_DUTY_CYCLE(lvl),
             VTSS_M_DEVCPU_GCB_FAN_CTRL_FAN_CFG_DUTY_CYCLE);

    return VTSS_RC_OK;
}

static vtss_rc srvl_fan_cool_lvl_get(vtss_state_t *vtss_state, u8 *duty_cycle)
{
    u32 fan_cfg_reg;

    // Read the register
    SRVL_RD(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG, &fan_cfg_reg);

    // Get PWM duty cycle
    *duty_cycle = VTSS_X_DEVCPU_GCB_FAN_CTRL_FAN_CFG_DUTY_CYCLE(fan_cfg_reg);

    return VTSS_RC_OK;
}

/*
 * Help function for keeping track of the fan rotation speed. This function mist be called every one second with update = TRUE. 
 *
 * In :  update -  When the function is called with update = TRUE, the fan rotation count is read and the count for the last second is stored.
 * 
 *       value  - Only needed when update is set to FALSE. The cnt for the last second is store in this pointer.
 *
 * Return : VTSS_OK if count was updated correctly, or value contains valid data, else error code
 *
 */
static vtss_rc srvl_fan_rotation(vtss_state_t *vtss_state, BOOL update, u32 *value) {
    static u32 last_cnt = 0, one_sec_cnt = 0;
    u32  cnt = 0;
    
    if (update) { 
        SRVL_RD(VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CNT, &cnt);
        one_sec_cnt = cnt - last_cnt;
        VTSS_N("one_sec_cnt:%d, last_cnt:%d, cnt:%d", one_sec_cnt, last_cnt, cnt);
        last_cnt = cnt;
        return VTSS_RC_OK;
    } 
    
    if (value == NULL) {
        return VTSS_RC_ERR_INVALID_NULL_PTR;
    }

    *value = one_sec_cnt;

    return VTSS_RC_OK;
}


/*
 * Get FAN rotation count. 
 *
 * In : fan_spec - Pointer to fan specification, e.g. type of fan.
 * 
 * In/Out - rotation_count - Pointer to where to put the rotation count.
 *
 * Return : VTSS_OK if rotation was found else error code.
 */
static vtss_rc srvl_fan_rotation_get(vtss_state_t *vtss_state,
                                    vtss_fan_conf_t *fan_spec, u32 *rotation_count)
{
    return srvl_fan_rotation(vtss_state, FALSE, rotation_count);
}

/*
 * Help function for keeping track of the fan rotation speed. Must be called every one second.
 *
 * Return : VTSS_OK if count was updated correctly.
 *
 */
static vtss_rc srvl_fan_rotation_update(vtss_state_t *vtss_state)
{
    return srvl_fan_rotation(vtss_state, TRUE, NULL);
}
#endif /* VTSS_FEATURE_FAN */

/* ================================================================= *
 *  Miscellaneous
 * ================================================================= */

static vtss_rc srvl_reg_read(vtss_state_t *vtss_state,
                             const vtss_chip_no_t chip_no, const u32 addr, u32 * const value)
{
    return vtss_srvl_rd(vtss_state, addr, value);
}

static vtss_rc srvl_reg_write(vtss_state_t *vtss_state,
                              const vtss_chip_no_t chip_no, const u32 addr, const u32 value)
{
    return vtss_srvl_wr(vtss_state, addr, value);
}

vtss_rc vtss_srvl_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id)
{
    u32 value;

    SRVL_RD(VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID, &value);

    if (value == 0 || value == 0xffffffff) {
        VTSS_E("CPU interface error, chipid: 0x%08x", value);
        return VTSS_RC_ERROR;
    }

    chip_id->part_number = VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID(value);
    chip_id->revision = VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID(value);

    return VTSS_RC_OK;
}

vtss_rc srvl_isdx_table_idle(vtss_state_t *vtss_state)
{
    u32 value;
    
    do {
        SRVL_RD(VTSS_ANA_ANA_TABLES_ISDXACCESS, &value);
    } while (VTSS_X_ANA_ANA_TABLES_ISDXACCESS_ISDX_TBL_CMD(value) != ISDX_CMD_IDLE);

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_isdx_update(vtss_state_t *vtss_state,
                              BOOL isdx_ena, u32 isdx, u32 isdx_mask, u32 pol_idx, u32 voe_idx)
{
    /* Write to ISDX table */
    SRVL_WR(VTSS_ANA_ANA_TABLES_ISDXTIDX,
            (isdx_ena ? VTSS_F_ANA_ANA_TABLES_ISDXTIDX_ISDX_ES0_KEY_ENA : 0) |
            VTSS_F_ANA_ANA_TABLES_ISDXTIDX_ISDX_SDLBI(pol_idx) |
            VTSS_F_ANA_ANA_TABLES_ISDXTIDX_ISDX_INDEX(isdx));
    SRVL_WR(VTSS_ANA_ANA_TABLES_ISDXACCESS,
            VTSS_F_ANA_ANA_TABLES_ISDXACCESS_ISDX_PORT_MASK(isdx_mask) |
            VTSS_F_ANA_ANA_TABLES_ISDXACCESS_ISDX_TBL_CMD(ISDX_CMD_WRITE));
    
    /* Write VOE mapping to IPT table */
    SRVL_WR(VTSS_ANA_IPT_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_IPT_OAM_MEP_CFG_MEP_IDX(voe_idx) |
            VTSS_F_ANA_IPT_OAM_MEP_CFG_MEP_IDX_P(voe_idx) |
            ((voe_idx == VTSS_VOE_IDX_NONE) || (voe_idx >= VTSS_PORT_VOE_BASE_IDX) ? 0 : VTSS_F_ANA_IPT_OAM_MEP_CFG_MEP_IDX_ENA));      /* Do not point to a Port VOE */

    return srvl_isdx_table_idle(vtss_state);
}

vtss_rc vtss_srvl_isdx_update_es0(vtss_state_t *vtss_state,
                                  BOOL isdx_ena, u32 isdx, u32 isdx_mask)
{
    /* Write to ISDX table */
    SRVL_WR(VTSS_ANA_ANA_TABLES_ISDXTIDX,
            (isdx_ena ? VTSS_F_ANA_ANA_TABLES_ISDXTIDX_ISDX_ES0_KEY_ENA : 0) |
            VTSS_F_ANA_ANA_TABLES_ISDXTIDX_ISDX_SDLBI(0)                     |
            VTSS_F_ANA_ANA_TABLES_ISDXTIDX_ISDX_INDEX(isdx));
    SRVL_WR(VTSS_ANA_ANA_TABLES_ISDXACCESS,
            VTSS_F_ANA_ANA_TABLES_ISDXACCESS_ISDX_PORT_MASK(isdx_mask) |
            VTSS_F_ANA_ANA_TABLES_ISDXACCESS_ISDX_TBL_CMD(ISDX_CMD_WRITE));

    return srvl_isdx_table_idle(vtss_state);
}


static vtss_rc srvl_ptp_event_poll(vtss_state_t *vtss_state, vtss_ptp_event_type_t *ev_mask)
{
    u32 sticky, mask;

    /* PTP events */
    *ev_mask = 0;
    SRVL_RD(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR, &sticky);
    SRVL_WR(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR, sticky);
    SRVL_RD(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA, &mask);
    sticky &= mask;      /* Only handle enabled sources */

    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_INTR_PTP(1<<0)) ?  VTSS_PTP_PIN_0_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_INTR_PTP(1<<1)) ?  VTSS_PTP_PIN_1_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_INTR_PTP(1<<2)) ? VTSS_PTP_PIN_2_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_INTR_PTP(1<<3)) ?  VTSS_PTP_PIN_3_SYNC_EV : 0;
    VTSS_D("sticky: 0x%x, ev_mask 0x%x", sticky, *ev_mask);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ptp_event_enable(vtss_state_t *vtss_state,
                                     vtss_ptp_event_type_t ev_mask, BOOL enable)
{
    VTSS_D("ev_mask 0x%x, enable: %d", ev_mask, enable);
    if (ev_mask & VTSS_PTP_PIN_0_SYNC_EV) {
        SRVL_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<0 : 0),
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<0));
    }
    if (ev_mask & VTSS_PTP_PIN_1_SYNC_EV) {
        SRVL_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<1 : 0),
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<1));
    }
    if (ev_mask & VTSS_PTP_PIN_2_SYNC_EV) {
        SRVL_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<2 : 0),
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<2));
    }
    if (ev_mask & VTSS_PTP_PIN_3_SYNC_EV) {
        SRVL_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<3 : 0),
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<3));
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_dev_all_event_poll(vtss_state_t *vtss_state,
                                       vtss_dev_all_event_poll_t poll_type,
                                       vtss_dev_all_event_type_t  *ev_mask)
{
    u32 ident=0, chip_port;
    vtss_port_no_t api_port;

    /* Read the active interrupt sources (the product of sticky & enable) */
    SRVL_RD(VTSS_ICPU_CFG_INTR_DEV_INTR_IDENT, &ident);

    for (api_port = VTSS_PORT_NO_START; api_port < vtss_state->port_count; api_port++) {
        ev_mask[api_port] = 0;
        chip_port = VTSS_CHIP_PORT(api_port);
        if (ident & (1 << chip_port)) {
            ev_mask[api_port] = VTSS_DEV_ALL_LINK_EV;
        }
    }
    /* Clear the icpu_dev sticky */
    SRVL_WR(VTSS_ICPU_CFG_INTR_DEV_INTR_STICKY, ident);

    /* The (4) internal phy interrupt is mapped to ICPU_DEV_INTR index 11-15 */
    /* Here they are mapped back to ev_mask with the corresponding API index */
    for (api_port = VTSS_PORT_NO_START; api_port < vtss_state->port_count; api_port++) {
        chip_port = VTSS_CHIP_PORT(api_port);
        if ((chip_port < 4) && (vtss_state->port.conf[api_port].if_type == VTSS_PORT_INTERFACE_SGMII)) {
            if (ident & (1 << (chip_port + 11))) {
                ev_mask[api_port] = VTSS_DEV_ALL_LINK_EV;
            }
        }
    }

    return VTSS_RC_OK;
}


static vtss_rc srvl_dev_all_event_enable(vtss_state_t *vtss_state,
                                         vtss_port_no_t port_no, vtss_dev_all_event_type_t ev_mask, BOOL enable)
{
    u32 chip_port = VTSS_CHIP_PORT(port_no), mask = VTSS_BIT(chip_port), dev_intr = chip_port;

    if (!(ev_mask & VTSS_DEV_ALL_LINK_EV)) {
        VTSS_D("DEV event supported: 0x%x", ev_mask);
        return VTSS_RC_ERROR;
    }

    /* The (4) internal phy interrupt is mapped to ICPU_DEV_INTR index 11-15 */
    if (chip_port < 4) {
        if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII) {
            dev_intr = chip_port + 11;
        }
        mask |= VTSS_BIT(chip_port + 11);
    }

    /* Enable/disable ICPU device interrupt */
    SRVL_WRM(VTSS_ICPU_CFG_INTR_DEV_INTR_ENA, VTSS_ENCODE_BITFIELD(enable,dev_intr,1), mask);

    /* Clear ICPU sticky bit */
    SRVL_WR(VTSS_ICPU_CFG_INTR_DEV_INTR_STICKY, mask);

    return VTSS_RC_OK;
}

static vtss_rc srvl_intr_cfg(vtss_state_t *vtss_state,
                             const u32  intr_mask, const BOOL polarity, const BOOL enable)
{
    return VTSS_RC_OK;
}

static vtss_rc srvl_intr_pol_negation(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

#ifdef VTSS_FEATURE_IRQ_CONTROL


#define SRVL1_IRQ_DEV_ALL       (0)
#define SRVL1_IRQ_EXT0          (1)
#define SRVL1_IRQ_EXT1          (2)
#define SRVL1_IRQ_TIMER0        (3)
#define SRVL1_IRQ_TIMER1        (4)
#define SRVL1_IRQ_TIMER2        (5)
#define SRVL1_IRQ_UART          (6)
#define SRVL1_IRQ_UART2         (7)
#define SRVL1_IRQ_TWI           (8)
#define SRVL1_IRQ_SIMC          (9)
#define SRVL1_IRQ_SW0           (10)
#define SRVL1_IRQ_SW1           (11)
#define SRVL1_IRQ_SGPIO         (12)
#define SRVL1_IRQ_GPIO          (13)
#define SRVL1_IRQ_MIIM0_INTR    (14)
#define SRVL1_IRQ_MIIM1_INTR    (15)
#define SRVL1_IRQ_FDMA          (16)
#define SRVL1_IRQ_OAM_MEP       (17)
#define SRVL1_IRQ_PTP_RDY       (18)
#define SRVL1_IRQ_PTP_SYNC      (19)
#define SRVL1_IRQ_INTEGRITY     (20)
#define SRVL1_IRQ_XTR_RDY       (21)
#define SRVL1_IRQ_INJ_RDY       (22)
#define SRVL1_IRQ_PCIE          (23)

#define SRVL_IRQ_DEST_CPU0      0 /* IRQ destination CPU0 */
#define SRVL_IRQ_DEST_CPU1      1 /* IRQ destination CPU1 */
#define SRVL_IRQ_DEST_EXT0      2 /* IRQ destination EXT0 */
#define SRVL_IRQ_DEST_EXT1      3 /* IRQ destination EXT1 */

#define IRQ_DEST(conf) ((u32) ((conf->external ? SRVL_IRQ_DEST_EXT0 : SRVL_IRQ_DEST_CPU0) + conf->destination))

static vtss_rc srvl_misc_irq_destination(vtss_state_t *vtss_state, 
                                         u32 mask, 
                                         u32 destination)
{
    SRVL_WRM_CLR(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(SRVL_IRQ_DEST_CPU0), mask);
    SRVL_WRM_CLR(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(SRVL_IRQ_DEST_CPU1), mask);
    SRVL_WRM_CLR(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(SRVL_IRQ_DEST_EXT0), mask);
    SRVL_WRM_CLR(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(SRVL_IRQ_DEST_EXT1), mask);
    SRVL_WRM_SET(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(destination), mask);
    return VTSS_RC_OK;
}

static vtss_rc srvl_misc_irq_remap(vtss_state_t *vtss_state, 
                                   u32 mask,
                                   const vtss_irq_conf_t *const conf)
{
    u32 destination = IRQ_DEST(conf);
    u32 ix;

    /* Map to requested (single) destination) */
    VTSS_RC(srvl_misc_irq_destination(vtss_state, mask, destination));

    /* Always use sticky IRQ's */
    SRVL_WRM_CLR(VTSS_ICPU_CFG_INTR_INTR_BYPASS, mask);

    /* Set up derived registers - PCIe */
    if (vtss_state->sys_config.using_pcie) {
        u32 external0, external1;
        // Enable PCIe IRQ
        SRVL_WRM_CLR(VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG,
                     VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA);
        // Read current ext0 / ext1 mapping
        SRVL_RD(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(SRVL_IRQ_DEST_EXT0), &external0);
        SRVL_RD(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(SRVL_IRQ_DEST_EXT1), &external1);
        // Configure IRQ if external has a dest
        SRVL_WRM_CTL(VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG(0), (external0 != 0),
                     VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_FALLING_ENA |
                     VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_RISING_ENA);
        SRVL_WRM_CTL(VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG(1), (external1 != 0),
                     VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_FALLING_ENA |
                     VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_RISING_ENA);
        // Select EXT_DST1 if JR2_IRQ_DEST_EXT1 non-zero
        SRVL_WRM_CTL(VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG, (external1 != 0),
                     VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL);
        // Enable PCIe if
        SRVL_WRM_CTL(VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG, (external0|external1),
                     VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA);
    }

    /* Set up derived registers - EXT drive & dir */
    for (ix = 0; ix < 2; ix++) {
        u32 external;
        SRVL_RD(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(SRVL_IRQ_DEST_EXT0 + ix), &external);
        SRVL_WRM_CTL(VTSS_ICPU_CFG_INTR_EXT_DST_INTR_DRV, external != 0,
                     VTSS_F_ICPU_CFG_INTR_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(VTSS_BIT(ix)));
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_misc_irq_cfg(vtss_state_t *vtss_state,
                                 const vtss_irq_t irq,
                                 const vtss_irq_conf_t *const conf)
{
    vtss_rc rc = VTSS_RC_ERROR;
    if (conf->destination > 1) {
        rc = VTSS_RC_ERROR;
    } else {
        switch (irq) {
            case VTSS_IRQ_XTR:
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_XTR_RDY), conf);
                break;
            case VTSS_IRQ_FDMA_XTR:     /* NB: XTR and INJ are lumped together*/
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_FDMA), conf);
                break;
            case VTSS_IRQ_SOFTWARE:
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_SW0)|VTSS_BIT(SRVL1_IRQ_SW1), conf);
                break;
            case VTSS_IRQ_PTP_RDY:
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_PTP_RDY), conf);
                break;
            case VTSS_IRQ_PTP_SYNC:
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_PTP_SYNC), conf);
                break;
            case VTSS_IRQ_EXT0:
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_EXT0), conf);
                break;
	    case VTSS_IRQ_EXT1:
#if defined (VTSS_OPSYS_ECOS)
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_EXT1), conf);
#elif defined (VTSS_OPSYS_LINUX)
                /* EXT1_IRQ is handled in the linux kernel */
#endif  /* VTSS_OPSYS_ECOS */
                break;
            case VTSS_IRQ_OAM:
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_OAM_MEP), conf);
                break;
            case VTSS_IRQ_SGPIO:
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_SGPIO), conf);
                break;
            case VTSS_IRQ_DEV_ALL:
                rc = srvl_misc_irq_remap(vtss_state, VTSS_BIT(SRVL1_IRQ_DEV_ALL), conf);
                break;
            default:
	        rc = VTSS_RC_ERROR;
	        break;
	}
    }
    return rc;
}

static vtss_rc srvl_misc_irq_status(vtss_state_t *vtss_state, vtss_irq_status_t *status)
{
    u32 val, uio_irqs, dest;

    VTSS_MEMSET(status, 0, sizeof(*status));

    // Which interrupts are taken care of in user-space?
    if (vtss_state->sys_config.using_pcie) {
        // If running on an external CPU connected via PCIe, either external IRQ0 or
        // external IRQ1 may be routed through the PCIe interrupt. Which one
        // can be read from ICPU_CFG:PCIE:PCIE_INTR_COMMON_CFG.LEGACY_MODE_INTR_SEL.
        SRVL_RD(VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG, &val);
        dest = (val & VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL) == 0 ? SRVL_IRQ_DEST_EXT0 : SRVL_IRQ_DEST_EXT1;
    } else {
        // When running on the internal CPU, SRVL_IRQ_DEST_CPU1 is - by convention and in
        // agreement with the kernel - used in user-space.
        dest = SRVL_IRQ_DEST_CPU1;
    }

    SRVL_RD(VTSS_ICPU_CFG_INTR_DST_INTR_MAP(dest), &uio_irqs);

    // Who's interrupting?
    SRVL_RD(VTSS_ICPU_CFG_INTR_INTR_IDENT, &val);

    // Only consider UIO interrupts
    val &= uio_irqs;

    status->raw_ident = val;
    SRVL_RD(VTSS_ICPU_CFG_INTR_INTR_RAW, &status->raw_status);
    SRVL_RD(VTSS_ICPU_CFG_INTR_INTR_ENA, &status->raw_mask);
    SRVL_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_CLR, val);
    status->raw_status &= uio_irqs;
    status->raw_mask   &= uio_irqs;

    if (val & VTSS_BIT(SRVL1_IRQ_FDMA)) {
        u32 man_intr;
        SRVL_RD(VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR, &man_intr);
        if (man_intr & VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_XTR_ANY_RDY) {
            status->active |= VTSS_BIT(VTSS_IRQ_FDMA_XTR);
        }
    }

    if (val & (VTSS_BIT(SRVL1_IRQ_XTR_RDY))) {
        status->active |= VTSS_BIT(VTSS_IRQ_XTR);
    }

    if (val & (VTSS_BIT(SRVL1_IRQ_SW0)|VTSS_BIT(SRVL1_IRQ_SW1))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SOFTWARE);
    }

    if (val & VTSS_BIT(SRVL1_IRQ_EXT0)) {
        status->active |= VTSS_BIT(VTSS_IRQ_EXT0);
    }

    if(val & VTSS_BIT(SRVL1_IRQ_EXT1)) {
#if defined (VTSS_OPSYS_ECOS)
        status->active |= VTSS_BIT(VTSS_IRQ_EXT1);
#elif defined (VTSS_OPSYS_LINUX)
        /* EXT1_IRQ handled in linux kernel */
#endif  /* VTSS_OPSYS_ECOS */
    }

    if(val & (VTSS_BIT(SRVL1_IRQ_PTP_RDY))) {
        status->active |= VTSS_BIT(VTSS_IRQ_PTP_RDY);
    }

    if(val & (VTSS_BIT(SRVL1_IRQ_PTP_SYNC))) {
        status->active |= VTSS_BIT(VTSS_IRQ_PTP_SYNC);
    }

    if(val & (VTSS_BIT(SRVL1_IRQ_OAM_MEP))) {
        status->active |= VTSS_BIT(VTSS_IRQ_OAM);
    }

    if(val & VTSS_BIT(SRVL1_IRQ_SGPIO)) {
        status->active |= VTSS_BIT(VTSS_IRQ_SGPIO);
    }

    if (val & (VTSS_BIT(SRVL1_IRQ_DEV_ALL))) {
        status->active |= VTSS_BIT(VTSS_IRQ_DEV_ALL);
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_misc_irq_enable(vtss_state_t *vtss_state,
                                    const vtss_irq_t irq,
                                    const BOOL enable)
{
    u32 mask = 0;
    switch (irq) {
    case VTSS_IRQ_XTR:
        mask = VTSS_BIT(SRVL1_IRQ_XTR_RDY);
        break;
    case VTSS_IRQ_FDMA_XTR:
        SRVL_WRM_CTL(VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA, enable,
                     VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_XTR_ANY_RDY_ENA);
        mask = VTSS_BIT(SRVL1_IRQ_FDMA);
        break;
    case VTSS_IRQ_SOFTWARE:
        mask = VTSS_BIT(SRVL1_IRQ_SW0)|VTSS_BIT(SRVL1_IRQ_SW1);
        break;
    case VTSS_IRQ_PTP_RDY:
        mask = VTSS_BIT(SRVL1_IRQ_PTP_RDY);
        break;
    case VTSS_IRQ_PTP_SYNC:
        mask = VTSS_BIT(SRVL1_IRQ_PTP_SYNC);
        break;
    case VTSS_IRQ_EXT0:
        mask = VTSS_BIT(SRVL1_IRQ_EXT0);
        break;
    case VTSS_IRQ_EXT1:
#if defined (VTSS_OPSYS_ECOS)
        mask = VTSS_BIT(SRVL1_IRQ_EXT1);
#elif defined (VTSS_OPSYS_LINUX)
        /* EXT1_IRQ handled in linux kernel */
#endif  /* VTSS_OPSYS_ECOS */
        break;
    case VTSS_IRQ_OAM:
        mask = VTSS_BIT(SRVL1_IRQ_OAM_MEP);
        break;
    case VTSS_IRQ_SGPIO:
        mask = VTSS_BIT(SRVL1_IRQ_SGPIO);
        break;
    case VTSS_IRQ_DEV_ALL:
        mask = VTSS_BIT(SRVL1_IRQ_DEV_ALL);
        break;
    default:
        return VTSS_RC_ERROR;
    }

    /* Ack sticky bits */
    SRVL_WR(VTSS_ICPU_CFG_INTR_INTR_STICKY, mask);
    if (irq == VTSS_IRQ_FDMA_XTR) {
        SRVL_WRM_CTL(VTSS_ICPU_CFG_FDMA_FDMA_INTR_ENA, enable, 1); /* Always using ch 1 */
        SRVL_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_SET, mask); /* Always enable top FDMA (cascading) IRQ */
    } else {
        if(enable) {
            SRVL_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_SET, mask);
        } else {
            SRVL_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_CLR, mask);
        }
    }
    u32 mc;
    SRVL_RD(VTSS_ICPU_CFG_INTR_INTR_ENA, &mc);
    return VTSS_RC_OK;
}

#endif  /* VTSS_FEATURE_IRQ_CONTROL */

/* =================================================================
 *  Miscellaneous - GPIO
 * =================================================================*/

#if defined(VTSS_GPIOS)
vtss_rc vtss_srvl_gpio_mode(vtss_state_t *vtss_state,
                            const vtss_chip_no_t   chip_no,
                            const vtss_gpio_no_t   gpio_no,
                            const vtss_gpio_mode_t mode)
{
    u32 mask = VTSS_BIT(gpio_no), alt_0 = 0, alt_1 = 0;

    SRVL_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, mask); /* Disable IRQ */
    switch (mode) {
    case VTSS_GPIO_OUT:
    case VTSS_GPIO_IN:
    case VTSS_GPIO_IN_INT:
        SRVL_WRM_CTL(VTSS_DEVCPU_GCB_GPIO_GPIO_OE, mode == VTSS_GPIO_OUT, mask);
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
    SRVL_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(0), alt_0, mask);
    SRVL_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(1), alt_1, mask);
    if (mode == VTSS_GPIO_IN_INT)
        SRVL_WRM_SET(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, mask);
    return VTSS_RC_OK;
}

static vtss_rc srvl_gpio_read(vtss_state_t *vtss_state,
                              const vtss_chip_no_t  chip_no,
                              const vtss_gpio_no_t  gpio_no,
                              BOOL                  *const value)
{
    u32 val, mask = VTSS_BIT(gpio_no);

    SRVL_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_IN, &val);
    *value = VTSS_BOOL(val & mask);
    return VTSS_RC_OK;
}

static vtss_rc srvl_gpio_write(vtss_state_t *vtss_state,
                               const vtss_chip_no_t  chip_no,
                               const vtss_gpio_no_t  gpio_no,
                               const BOOL            value)
{
    u32 mask = VTSS_BIT(gpio_no);

    if (value) {
        SRVL_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_SET, mask);
    } else {
        SRVL_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_CLR, mask);
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_gpio_event_enable(vtss_state_t          *vtss_state,
                                      const vtss_chip_no_t  chip_no,
                                      const vtss_gpio_no_t  gpio_no,
                                      const BOOL            enable)
{
    u32 mask = VTSS_BIT(gpio_no);

    SRVL_WRM_CTL(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, enable, mask);
    return VTSS_RC_OK;
}

static vtss_rc srvl_gpio_event_poll(vtss_state_t          *vtss_state,
                                    const vtss_chip_no_t  chip_no,
                                    BOOL                  *const events)
{
    u32 pending, mask, i;

    SRVL_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR, &pending);
    SRVL_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, &mask);
    pending &= mask;
    SRVL_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR, pending);
    for (i = 0; i < 32; i++) {
        events[i] = (pending & VTSS_BIT(i) ? TRUE : FALSE);
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_sgpio_event_poll(vtss_state_t *vtss_state,
                                     const vtss_chip_no_t     chip_no,
                                     const vtss_sgpio_group_t group,
                                     const u32                bit,
                                     BOOL                     *const events)
{
    u32 i, val;

    SRVL_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR(bit), &val);
    SRVL_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR(bit), val);  /* Clear pending */

    /* Setup serial IO port enable register */
    for (i = 0; i < 32; i++) {
        events[i] = VTSS_BOOL(val & (1<<i));
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_GPIOS */

#if defined(VTSS_FEATURE_SERIAL_GPIO)
static vtss_rc srvl_sgpio_event_enable(vtss_state_t *vtss_state,
                                       const vtss_chip_no_t     chip_no,
                                       const vtss_sgpio_group_t group,
                                       const u32                port,
                                       const u32                bit,
                                       const BOOL               enable)
{
    u32 i, mask = (1 << port);

    if (enable) {
        VTSS_D("group:%d mask:0x%X, bit:0x%X, 0x%X", group, mask, bit, VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit));
        SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR(bit), mask, mask); // Clear any pending interrupts, so we don't get any spurious interrupt when we enable.

        SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_ENA, mask, mask);

        // Enable only the bit in question, plus the master SIO
        SRVL_WRM_SET(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG,
                     VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_MASTER_INTR_ENA |
                     VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit));

        /* Enable rising edge triggered interrupt - From datasheet 11: Interrupt is rising-edge-triggered*/
        SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_TRIGGER0(bit), mask, mask);
        SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_TRIGGER1(bit), mask, mask);

    } else {

        VTSS_D("Disable port:%d, group:%d, bit:%d", port, group, bit);
        SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_ENA, 0, mask);
        for (i=0; i<32; ++i) {
            if (vtss_state->misc.sgpio_event_enabled[chip_no][group].enable[i][bit]) {
                break;
            }
        }
        if (i == 32) {
            SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG,
                    0,
                    VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_GPIO_INTR_ENA(1 << bit)); // Clear only the bit in question.
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_sgpio_conf_set(vtss_state_t *vtss_state,
                                   const vtss_chip_no_t     chip_no,
                                   const vtss_sgpio_group_t group,
                                   const vtss_sgpio_conf_t  *const conf)
{
    u32  i, port, val = 0, pol = 0, bmode[2], bit_idx, value, mask;

    /* Setup serial IO port enable register */
    for (port = 0; port < 32; port++) {
        if (conf->port_conf[port].enabled)
            val |= VTSS_BIT(port);
    }

    SRVL_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_ENA, val);

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
            if (i == 1) {
                VTSS_E("blink mode 1 does not support 1.25 Hz");
                return VTSS_RC_ERROR;
            }
            bmode[i] = 2;
            break;
        case VTSS_SGPIO_BMODE_2_5:
            if (i == 1) {
                VTSS_E("blink mode 1 does not support 2.5 Hz");
                return VTSS_RC_ERROR;
            }
            bmode[i] = 1;
            break;
        case VTSS_SGPIO_BMODE_5:
            if (i == 0) {
                bmode[i] = 0;
            } else {
                bmode[i] = 2;
            }
            break;
        default:
            return VTSS_RC_ERROR;
        }
    }

    value = (VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BMODE_0(bmode[0]) |
             VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BMODE_1(bmode[1]) |
             VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BURST_GAP(3) |
             VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_PORT_WIDTH(conf->bit_count - 1) |
             VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_AUTO_REPEAT);
    mask = (VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BMODE_0 |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BMODE_1 |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_BURST_GAP |
            VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_PORT_WIDTH |
            VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CFG_SIO_AUTO_REPEAT);
    SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CFG, value, mask);
    SRVL_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK,
            VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ(0x14) |
            VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SYS_CLK_PERIOD(0x40));

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
        for (bit_idx = 0; bit_idx < 4; bit_idx++) {
            /* Set output bit n */
            if (conf->port_conf[port].mode[bit_idx] != VTSS_SGPIO_MODE_NO_CHANGE) {
                if (conf->port_conf[port].mode[bit_idx] == VTSS_SGPIO_MODE_0_ACTIVITY_INV) {
                    val = VTSS_SGPIO_MODE_0_ACTIVITY;
                    pol = 1; // Inverse polarity
                } else if (conf->port_conf[port].mode[bit_idx] == VTSS_SGPIO_MODE_1_ACTIVITY_INV) {
                    val = VTSS_SGPIO_MODE_1_ACTIVITY;
                    pol = 1; // Inverse polarity
                } else {
                    val = conf->port_conf[port].mode[bit_idx];
                    pol = 0;
                }

                value = VTSS_ENCODE_BITFIELD(val, (bit_idx * 3), 3);
                mask = VTSS_ENCODE_BITMASK((bit_idx * 3), 3);
                SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG(port),
                         VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_SOURCE(value) |
                         VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_POLARITY(pol << bit_idx),
                         VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_SOURCE(mask) |
                         VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CFG_BIT_POLARITY(1 << bit_idx));
            }

            /* Setup the interrupt polarity */
            BOOL pol_high = conf->port_conf[port].int_pol_high[bit_idx];
            mask = VTSS_BIT(port);
            value = (pol_high ? 0 : mask);
            SRVL_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_POL(bit_idx), value, mask);
            VTSS_D("group:%d, port:%d, bit_idx:%d, int_pol_high:%d", group, port, bit_idx, pol_high);
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_sgpio_read(vtss_state_t *vtss_state,
                               const vtss_chip_no_t     chip_no,
                               const vtss_sgpio_group_t group,
                               vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS])
{
    u32 i, port, value;

    for (i = 0; i < 4; i++) {
        SRVL_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INPUT_DATA(i), &value);
        for (port = 0; port < 32; port++) {
            data[port].value[i] = VTSS_BOOL(value & (1 << port));
        }
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_SERIAL_GPIO */

/* - Debug print --------------------------------------------------- */

static void srvl_debug_tgt(const vtss_debug_printf_t pr, const char *name, u32 to)
{
    u32 tgt = ((to >> 16) & 0x3f);
    pr("%-10s  0x%02x (%u)\n", name, tgt, tgt);
}

#define SRVL_DEBUG_TGT(pr, name) srvl_debug_tgt(pr, #name, VTSS_TO_##name)
#define SRVL_DEBUG_GPIO(pr, addr, name) vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_GPIO_GPIO_##addr, "GPIO_"name)
#define SRVL_DEBUG_SIO(pr, addr, name) vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_SIO_CTRL_SIO_##addr, "SIO_"name)
#define SRVL_DEBUG_SIO_INST(pr, addr, i, name) vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_DEVCPU_GCB_SIO_CTRL_SIO_##addr, i, "SIO_"name)

static vtss_rc srvl_debug_misc(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    u32  i;
    char buf[32];

    pr("Name        Target\n");
    SRVL_DEBUG_TGT(pr, DEVCPU_ORG);
    SRVL_DEBUG_TGT(pr, SYS);
    SRVL_DEBUG_TGT(pr, REW);
    SRVL_DEBUG_TGT(pr, ES0);
    SRVL_DEBUG_TGT(pr, S1);
    SRVL_DEBUG_TGT(pr, S2);
    SRVL_DEBUG_TGT(pr, DEVCPU_GCB);
    SRVL_DEBUG_TGT(pr, DEVCPU_QS);
#ifdef VTSS_TO_HSIO
    SRVL_DEBUG_TGT(pr, HSIO);
#endif  /* VTSS_TO_HSIO */
#ifdef VTSS_TO_IS0
    SRVL_DEBUG_TGT(pr, IS0);
#endif  /* VTSS_TO_IS0 */
#ifdef VTSS_TO_OAM_MEP
    SRVL_DEBUG_TGT(pr, OAM_MEP);
#endif  /* VTSS_TO_OAM_MEP */
    for (i = 0; i < VTSS_CHIP_PORTS; i++) {
        VTSS_SPRINTF(buf, "DEV_%u", i);
        srvl_debug_tgt(pr, buf, VTSS_TO_DEV(i));
    }
    pr("\n");
    SRVL_DEBUG_TGT(pr, QSYS);
    SRVL_DEBUG_TGT(pr, ANA);

    vtss_srvl_debug_reg_header(pr, "GPIOs");
    SRVL_DEBUG_GPIO(pr, OUT, "OUT");
    SRVL_DEBUG_GPIO(pr, IN, "IN");
    SRVL_DEBUG_GPIO(pr, OE, "OE");
    SRVL_DEBUG_GPIO(pr, INTR, "INTR");
    SRVL_DEBUG_GPIO(pr, INTR_ENA, "INTR_ENA");
    SRVL_DEBUG_GPIO(pr, INTR_IDENT, "INTR_IDENT");
    SRVL_DEBUG_GPIO(pr, ALT(0), "ALT_0");
    SRVL_DEBUG_GPIO(pr, ALT(1), "ALT_1");
    pr("\n");

    vtss_srvl_debug_reg_header(pr, "SGPIO");
    for (i = 0; i < 4; i++)
        SRVL_DEBUG_SIO_INST(pr, INPUT_DATA(i), i, "INPUT_DATA");
    SRVL_DEBUG_SIO(pr, CFG, "CFG");
    SRVL_DEBUG_SIO(pr, CLOCK, "CLOCK");
    for (i = 0; i < 32; i++)
        SRVL_DEBUG_SIO_INST(pr, PORT_CFG(i), i, "PORT_CFG");
    SRVL_DEBUG_SIO(pr, PORT_ENA, "PORT_ENA");
    for (i = 0; i < 3; i++)
        SRVL_DEBUG_SIO_INST(pr, PWM_CFG(i), i, "PWM_CFG");
    for (i = 0; i < 4; i++)
        SRVL_DEBUG_SIO_INST(pr, INTR_POL(i), i, "INTR_POL");
    for (i = 0; i < 4; i++)
        SRVL_DEBUG_SIO_INST(pr, INTR_RAW(i), i, "INTR_RAW");
    for (i = 0; i < 4; i++)
        SRVL_DEBUG_SIO_INST(pr, INTR_TRIGGER0(i), i, "INTR_TRIGGER0");
    for (i = 0; i < 4; i++)
        SRVL_DEBUG_SIO_INST(pr, INTR_TRIGGER1(i), i, "INTR_TRIGGER1");
    for (i = 0; i < 4; i++)
        SRVL_DEBUG_SIO_INST(pr, INTR(i), i, "INTR");
    SRVL_DEBUG_SIO(pr, INTR_ENA, "INTR_ENA");
    for (i = 0; i < 4; i++)
        SRVL_DEBUG_SIO_INST(pr, INTR_IDENT(i), i, "INTR_IDENT");
    pr("\n");
    
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT, "GENERAL_STAT");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_INTR_INTR_IDENT, "INTR_IDENT");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_INTR_INTR_RAW, "INTR_RAW");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_INTR_INTR_ENA, "INTR_ENA");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_INTR_INTR_BYPASS, "INTR_BYPASS");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_FDMA_FDMA_INTR_IDENT, "FDMA_INTR_IDENT");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_FDMA_FDMA_INTR_ENA, "FDMA_INTR_ENA");
    for (i = 0; i < 4; i++) {
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ICPU_CFG_INTR_DST_INTR_MAP(i), i, "DST_INTR_MAP");
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ICPU_CFG_INTR_DST_INTR_IDENT(i), i, "DST_INTR_IDENT");
    }
    // DEV_ALL IRQ
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_INTR_DEV_INTR_RAW, "DEV_INTR_RAW");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_INTR_DEV_INTR_STICKY, "DEV_INTR_STICKY");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_INTR_DEV_INTR_ENA, "DEV_INTR_ENA");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_INTR_DEV_INTR_IDENT, "DEV_INTR_IDENT");
    if (vtss_state->sys_config.using_pcie) {
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_PCIE_PCIE_CFG, "PCIE_CFG");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_PCIE_PCIE_STAT, "PCIE_STAT");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_PCIE_PCIE_AUX_CFG, "PCIE_AUX_CFG");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_PCIE_PCIE_INTR, "PCIE_INTR");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_PCIE_PCIE_INTR_ENA, "PCIE_INTR_ENA");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_PCIE_PCIE_INTR_IDENT, "PCIE_INTR_IDENT");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG, "PCIE_INTR_COMMON_CFG");
        for (i = 0; i < 2; i++)
            vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG(i), i, "PCIE_INTR_CFG");
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_misc_debug_print(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_MISC, srvl_debug_misc, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc srvl_misc_poll_1sec(vtss_state_t *vtss_state)
{
    vtss_rc rc = VTSS_RC_OK;
    u32     port, bit, enable;

    SRVL_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INTR_ENA, &enable);
    for (port=0; port<32; ++port)
        if (!(enable & 1<<port))
            for (bit=0; bit<4; ++bit)    /* port is not enabled - check if it is configured to be */
                if (vtss_state->misc.sgpio_event_enabled[0][0].enable[port][bit]) {
                    rc = srvl_sgpio_event_enable(vtss_state, 0, 0, port, bit, TRUE);  /* this port,bit is configured to be enabled - try and enable */
                }
#if defined(VTSS_FEATURE_FAN)
    VTSS_RC(srvl_fan_rotation_update(vtss_state));
#endif /* VTSS_FEATURE_FAN */

    return rc;
}

static vtss_rc srvl_poll_1sec(vtss_state_t *vtss_state)
{
    /* Poll function groups */
    return vtss_srvl_init_groups(vtss_state, VTSS_INIT_CMD_POLL);
}

vtss_rc vtss_srvl_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_misc_state_t *state = &vtss_state->misc;

    if (cmd == VTSS_INIT_CMD_CREATE) {
        state->reg_read = srvl_reg_read;
        state->reg_write = srvl_reg_write;
        state->chip_id_get = vtss_srvl_chip_id_get;
        state->poll_1sec = srvl_poll_1sec;
        state->gpio_mode = vtss_srvl_gpio_mode;
        state->gpio_read = srvl_gpio_read;
        state->gpio_write = srvl_gpio_write;
        state->gpio_event_enable = srvl_gpio_event_enable;
        state->gpio_event_poll = srvl_gpio_event_poll;
        state->sgpio_conf_set = srvl_sgpio_conf_set;
        state->sgpio_read = srvl_sgpio_read;
        state->sgpio_event_enable = srvl_sgpio_event_enable;
        state->sgpio_event_poll = srvl_sgpio_event_poll;
        state->gpio_count = SRVL_GPIOS;
        state->sgpio_group_count = SRVL_SGPIO_GROUPS;
        state->dev_all_event_poll = srvl_dev_all_event_poll;
        state->dev_all_event_enable = srvl_dev_all_event_enable;
        state->intr_cfg = srvl_intr_cfg;
        state->intr_pol_negation = srvl_intr_pol_negation;
        state->ptp_event_poll = srvl_ptp_event_poll;
        state->ptp_event_enable = srvl_ptp_event_enable;
#ifdef VTSS_FEATURE_IRQ_CONTROL
        vtss_state->misc.irq_cfg = srvl_misc_irq_cfg;
        vtss_state->misc.irq_status = srvl_misc_irq_status;
        vtss_state->misc.irq_enable = srvl_misc_irq_enable;
#endif  /* VTSS_FEATURE_IRQ_CONTROL */

        /* EEE */
        vtss_state->eee.port_conf_set   = srvl_eee_port_conf_set;

#if defined(VTSS_FEATURE_FAN)
        vtss_state->fan.controller_init = srvl_fan_controller_init;
        vtss_state->fan.cool_lvl_get    = srvl_fan_cool_lvl_get;
        vtss_state->fan.cool_lvl_set    = srvl_fan_cool_lvl_set;
        vtss_state->fan.rotation_get    = srvl_fan_rotation_get;
#endif /* VTSS_FEATURE_FAN */
    }

    if (cmd == VTSS_INIT_CMD_POLL) {
        VTSS_RC(srvl_misc_poll_1sec(vtss_state));
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_OCELOT */
