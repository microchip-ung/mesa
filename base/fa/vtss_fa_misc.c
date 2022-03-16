// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)

/* - CIL functions ------------------------------------------------- */

#if defined(VTSS_FEATURE_EEE)
/* =================================================================
 *  EEE - Energy Efficient Ethernet
 * =================================================================*/
static vtss_rc fa_eee_port_conf_set(vtss_state_t *vtss_state,
                                      const vtss_port_no_t       port_no,
                                      const vtss_eee_port_conf_t *const conf)
{
    u32            closest_match_index, closest_match, i, requested_time;
    u32            eee_cfg_reg = 0x0; // SYS::EEE_CFG register value.
    vtss_port_no_t chip_port = VTSS_CHIP_PORT(port_no);
    u16            eee_timer_age;
    u32            dev_tgt = vtss_fa_dev_tgt(vtss_state, port_no);

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
            eee_cfg_reg |= VTSS_M_DEV1G_EEE_CFG_EEE_ENA;
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

    eee_cfg_reg |= VTSS_F_DEV1G_EEE_CFG_EEE_TIMER_WAKEUP(closest_match_index);

    // Set the latency depending upon what the user prefer (power saving vs. low traffic latency)
    if (conf->optimized_for_power) {
        eee_timer_age = 82; // Set timer age to 263 mSec.
    } else {
        eee_timer_age = 0x23; // Set timer age to 48 uSec.
    }

    // EEE holdoff timer
    eee_cfg_reg |= VTSS_F_DEV1G_EEE_CFG_EEE_TIMER_HOLDOFF(0x5) | VTSS_F_DEV1G_EEE_CFG_EEE_TIMER_AGE(eee_timer_age);

    // EEE fast queues
    VTSS_N("eee_fast_queues:0x%X, to-dev:%d, chip_port:%d", conf->eee_fast_queues, dev_tgt, chip_port);
    REG_WRM(VTSS_QSYS_EEE_CFG(chip_port),
            VTSS_F_QSYS_EEE_CFG_EEE_FAST_QUEUES(conf->eee_fast_queues),
            VTSS_M_QSYS_EEE_CFG_EEE_FAST_QUEUES);

    // Registers write
    VTSS_D("chip_port:%d, eee_cfg_reg:0x%X", chip_port, eee_cfg_reg);
    REG_WR(VTSS_DEV1G_EEE_CFG(dev_tgt), eee_cfg_reg);
    VTSS_D("chip_port:%u, eee_cfg_reg = 0x%X, conf->tx_tw = %d, eee_timer_age:%d", chip_port, eee_cfg_reg, conf->tx_tw, eee_timer_age);

    // Setting Buffer size to 12.2 Kbyte & 255 frames.
    REG_WR(VTSS_QSYS_EEE_THRES, 0xFFFF);

    // Work-around of Bugzilla#18901
    u32 dummy_reg, prio;
    for (prio = 0; prio < 8; prio++) {
        REG_RD(VTSS_QRES_RES_STAT(2048 + 8 * port_no + prio), &dummy_reg);
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_EEE */

#if defined(VTSS_FEATURE_FAN)
/* =================================================================
 * FAN speed control
 * =================================================================*/
static vtss_rc fa_fan_controller_init(vtss_state_t *vtss_state,
                                        const vtss_fan_conf_t *const spec)
{
    u32 pwm_freq;
    u32 system_clock_freq = 625000000;
    vtss_core_clock_freq_t freq = vtss_state->init_conf.core_clock.freq;

    if (freq == VTSS_CORE_CLOCK_250MHZ) {
        system_clock_freq = 250000000;
    } else if (freq == VTSS_CORE_CLOCK_500MHZ) {
        system_clock_freq = 500000000;
    }

    switch (spec->fan_pwm_freq) {
    case VTSS_FAN_PWM_FREQ_25KHZ: pwm_freq = 25000; break;
    case VTSS_FAN_PWM_FREQ_120HZ: pwm_freq = 120; break;
    case VTSS_FAN_PWM_FREQ_100HZ: pwm_freq = 100; break;
    case VTSS_FAN_PWM_FREQ_80HZ:  pwm_freq = 80; break;
    case VTSS_FAN_PWM_FREQ_60HZ:  pwm_freq = 60; break;
    case VTSS_FAN_PWM_FREQ_40HZ:  pwm_freq = 40; break;
    case VTSS_FAN_PWM_FREQ_20HZ:  pwm_freq = 20; break;
    case VTSS_FAN_PWM_FREQ_10HZ:  pwm_freq = 10; break;
    default:
        return VTSS_RC_ERROR;
    }

    // TBD_FA_FAN
    // TBD_FA_POE
    // GPIO initialization is currently done in the API, but it does not really
    // belong here as it is board specific. Furthermore, once we have also PoE
    // support for FA, there will be an overlap between FAN and PoE for GPIO_23
    // Therefore the GPIO configuration should be moved over to the kernel through
    // device trees.
    // Set GPIO alternate functions.
    // PWM is GPIO_23, ALT_0.
    // TACHO is GPIO_21, ALT_1.
    VTSS_RC(vtss_fa_gpio_mode(vtss_state, 0, 23, VTSS_GPIO_ALT_0));
    VTSS_RC(vtss_fa_gpio_mode(vtss_state, 0, 21, VTSS_GPIO_ALT_1));

    // Set PWM frequency (System clock frequency)/(PWM frequency)/256)
    REG_WRM(VTSS_DEVCPU_GCB_PWM_FREQ,
            VTSS_F_DEVCPU_GCB_PWM_FREQ_PWM_FREQ(system_clock_freq/pwm_freq/256) |
            VTSS_F_DEVCPU_GCB_PWM_FREQ_CLK_CYCLES_10US(system_clock_freq/100000),
            VTSS_M_DEVCPU_GCB_PWM_FREQ_PWM_FREQ |
            VTSS_M_DEVCPU_GCB_PWM_FREQ_CLK_CYCLES_10US);

    // Set PWM polarity
    REG_WRM(VTSS_DEVCPU_GCB_FAN_CFG,
            spec->fan_low_pol ? VTSS_M_DEVCPU_GCB_FAN_CFG_INV_POL : 0,
            VTSS_M_DEVCPU_GCB_FAN_CFG_INV_POL);

    // Set PWM open collector
    REG_WRM(VTSS_DEVCPU_GCB_FAN_CFG,
            spec->fan_open_col ? VTSS_M_DEVCPU_GCB_FAN_CFG_PWM_OPEN_COL_ENA : 0,
            VTSS_M_DEVCPU_GCB_FAN_CFG_PWM_OPEN_COL_ENA);

    // We always use the one sec update for rotation count.
    REG_WRM(VTSS_DEVCPU_GCB_FAN_CFG,
            0,
            VTSS_M_DEVCPU_GCB_FAN_CFG_FAN_STAT_CFG);

    // Set fan speed measurement
    if (spec->type == VTSS_FAN_3_WIRE_TYPE) {
        // Enable gating for 3-wire fan types.
        REG_WRM(VTSS_DEVCPU_GCB_FAN_CFG,
               VTSS_M_DEVCPU_GCB_FAN_CFG_GATE_ENA,
               VTSS_M_DEVCPU_GCB_FAN_CFG_GATE_ENA);
    } else {
        //  For 4-wire fan types we need to disable gating (2-wire types doesn't matter)
        REG_WRM(VTSS_DEVCPU_GCB_FAN_CFG,
                0,
                VTSS_M_DEVCPU_GCB_FAN_CFG_GATE_ENA);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_fan_cool_lvl_set(vtss_state_t *vtss_state, u8 lvl)
{
    // Set PWM duty cycle (fan speed)
    REG_WRM(VTSS_DEVCPU_GCB_FAN_CFG,
            VTSS_F_DEVCPU_GCB_FAN_CFG_DUTY_CYCLE(lvl),
            VTSS_M_DEVCPU_GCB_FAN_CFG_DUTY_CYCLE);
    return VTSS_RC_OK;
}

static vtss_rc fa_fan_cool_lvl_get(vtss_state_t *vtss_state, u8 *duty_cycle)
{
    u32 fan_cfg_reg;

    // Read the register
    REG_RD(VTSS_DEVCPU_GCB_FAN_CFG, &fan_cfg_reg);

    // Get PWM duty cycle
    *duty_cycle = VTSS_X_DEVCPU_GCB_FAN_CFG_DUTY_CYCLE(fan_cfg_reg);

    return VTSS_RC_OK;
}

static vtss_rc fa_fan_rotation_get(vtss_state_t *vtss_state, vtss_fan_conf_t *fan_spec, u32 *rotation_count)
{
    // Read the register
    REG_RD(VTSS_DEVCPU_GCB_FAN_CNT, rotation_count);

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_FAN */

/* ================================================================= *
 *  Temperature Sensor
 * ================================================================= */
#if defined(VTSS_FEATURE_TEMP_SENSOR)
static vtss_rc fa_temp_sensor_init(vtss_state_t *vtss_state,
                                    const BOOL enable)
{
    u32 system_clock_freq_in_1us = 625;
    vtss_core_clock_freq_t freq = vtss_state->init_conf.core_clock.freq;

    if (freq == VTSS_CORE_CLOCK_250MHZ) {
        system_clock_freq_in_1us = 250;
    } else if (freq == VTSS_CORE_CLOCK_500MHZ) {
        system_clock_freq_in_1us = 500;
    }
    // Clock cycles per us
    REG_WRM(VTSS_HSIOWRAP_TEMP_SENSOR_CFG,
            VTSS_F_HSIOWRAP_TEMP_SENSOR_CFG_CLK_CYCLES_1US(system_clock_freq_in_1us),
            VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_CLK_CYCLES_1US);

    // Enable/Disable
    REG_WRM(VTSS_HSIOWRAP_TEMP_SENSOR_CFG,
            enable ? 1 : 0,
            VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_SAMPLE_ENA);

    return VTSS_RC_OK;
}

static vtss_rc fa_temp_sensor_get(vtss_state_t *vtss_state,
                                   i16  *temp_celsius)
{
    u32 val;
    REG_RD(VTSS_HSIOWRAP_TEMP_SENSOR_STAT, &val);

    // Check if the data is valid.
    if (!VTSS_X_HSIOWRAP_TEMP_SENSOR_STAT_TEMP_VALID(val)) {
        return VTSS_RC_ERROR;
    }

    // See VML:'
    *temp_celsius = ((i16)(VTSS_X_HSIOWRAP_TEMP_SENSOR_STAT_TEMP(val) * 3522 / 4096 - 1094) / 10);

    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_TEMP_SENSOR */

/* ================================================================= *
 *  Miscellaneous
 * ================================================================= */

static vtss_rc fa_reg_read(vtss_state_t *vtss_state,
                           const vtss_chip_no_t chip_no, const u32 addr, u32 * const value)
{
    return vtss_fa_rd(vtss_state, addr, value);
}

static vtss_rc fa_reg_write(vtss_state_t *vtss_state,
                            const vtss_chip_no_t chip_no, const u32 addr, const u32 value)
{
    return vtss_fa_wr(vtss_state, addr, value);
}

vtss_rc vtss_fa_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id)
{
    u32 value;

    REG_RD(VTSS_DEVCPU_GCB_CHIP_ID, &value);
    if (value == 0 || value == 0xffffffff) {
        VTSS_E("CPU interface[%u] error, chipid: 0x%08x", vtss_state->chip_no, value);
        return VTSS_RC_ERROR;
    }
    chip_id->part_number = VTSS_X_DEVCPU_GCB_CHIP_ID_PART_ID(value);
    chip_id->revision = VTSS_X_DEVCPU_GCB_CHIP_ID_REV_ID(value);
    return VTSS_RC_OK;
}

static vtss_rc fa_ptp_event_poll(vtss_state_t *vtss_state, vtss_ptp_event_type_t *ev_mask)
{
    u32 sticky, mask;

    /* PTP events */
    *ev_mask = 0;
    REG_RD(VTSS_DEVCPU_PTP_PTP_PIN_INTR, &sticky);
    REG_WR(VTSS_DEVCPU_PTP_PTP_PIN_INTR, sticky);
    REG_RD(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA, &mask);
    sticky &= mask;      /* Only handle enabled sources */

    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1<<0)) ?  VTSS_PTP_PIN_0_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1<<1)) ?  VTSS_PTP_PIN_1_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1<<2)) ? VTSS_PTP_PIN_2_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_X_DEVCPU_PTP_PTP_PIN_INTR_INTR_PTP(1<<3)) ?  VTSS_PTP_PIN_3_SYNC_EV : 0;
    VTSS_D("sticky: 0x%x, ev_mask 0x%x", sticky, *ev_mask);

    return VTSS_RC_OK;
}

static vtss_rc fa_ptp_event_enable(vtss_state_t *vtss_state,
                                     vtss_ptp_event_type_t ev_mask, BOOL enable)
{
    /* PTP masks */

    VTSS_D("ev_mask 0x%x, enable: %d", ev_mask, enable);
    if (ev_mask & VTSS_PTP_PIN_0_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<0 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<0));
    }
    if (ev_mask & VTSS_PTP_PIN_1_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<1 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<1));
    }
    if (ev_mask & VTSS_PTP_PIN_2_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<2 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<2));
    }
    if (ev_mask & VTSS_PTP_PIN_3_SYNC_EV) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA,
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(enable ? 1<<3 : 0),
                VTSS_F_DEVCPU_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1<<3));
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_dev_all_event_poll(vtss_state_t *vtss_state,
                                     vtss_dev_all_event_poll_t poll_type,
                                     vtss_dev_all_event_type_t  *ev_mask)
{
    VTSS_E("Not implemented");
    return VTSS_RC_ERROR;
}


static vtss_rc fa_dev_all_event_enable(vtss_state_t *vtss_state,
                                       vtss_port_no_t port_no, vtss_dev_all_event_type_t ev_mask, BOOL enable)
{
    VTSS_E("Not implemented");
    return VTSS_RC_ERROR;
}


static vtss_rc fa_intr_cfg(vtss_state_t *vtss_state,
                           const u32  intr_mask, const BOOL polarity, const BOOL enable)
{
    VTSS_E("Not implemented - use misc_irq_cfg");
    return VTSS_RC_ERROR;
}

static vtss_rc fa_intr_pol_negation(vtss_state_t *vtss_state)
{
    VTSS_E("Not implemented - use misc_irq_cfg");
    return VTSS_RC_OK;
}


#ifdef VTSS_FEATURE_IRQ_CONTROL

#define FA_IRQ_DEV_ALL       (0)
#define FA_IRQ_EXT0          (3)
#define FA_IRQ_EXT1          (4)
#define FA_IRQ_TIMER0        (9)
#define FA_IRQ_TIMER1        (10)
#define FA_IRQ_TIMER2        (11)
#define FA_IRQ_UART          (12)
#define FA_IRQ_UART2         (13)
#define FA_IRQ_TWI           (14)
#define FA_IRQ_TWI2          (15)
#define FA_IRQ_SIMC          (16)
#define FA_IRQ_SW0           (18)
#define FA_IRQ_SW1           (19)
#define FA_IRQ_SGPIO         (20)
#define FA_IRQ_SGPIO1        (21)
#define FA_IRQ_SGPIO2        (22)
#define FA_IRQ_GPIO          (23)
#define FA_IRQ_MIIM0_INTR    (24)
#define FA_IRQ_MIIM1_INTR    (25)
#define FA_IRQ_MIIM2_INTR    (26)
#define FA_IRQ_ANA           (29)
#define FA_IRQ_PTP_RDY       (30)
#define FA_IRQ_PTP_SYNC      (31)

#define FA_IRQ_DEST_EXT0      0 /* IRQ destination EXT0 */
#define FA_IRQ_DEST_EXT1      1 /* IRQ destination EXT1 */

#define IRQ_DEST(conf) ((u32) (FA_IRQ_DEST_EXT0 + conf->destination))

static vtss_rc fa_misc_irq_destination(vtss_state_t *vtss_state,
                                        u32 mask,
                                        u32 destination)
{
    REG_WRM_CLR(VTSS_CPU_DST_INTR_MAP(FA_IRQ_DEST_EXT0), mask);
    REG_WRM_CLR(VTSS_CPU_DST_INTR_MAP(FA_IRQ_DEST_EXT1), mask);
    REG_WRM_SET(VTSS_CPU_DST_INTR_MAP(destination), mask);
    return VTSS_RC_OK;
}

static vtss_rc fa_misc_irq_remap(vtss_state_t *vtss_state,
                                  u32 mask,
                                  const vtss_irq_conf_t *const conf)
{
    u32 destination = IRQ_DEST(conf);

    /* Map to requested (single) destination */
    VTSS_RC(fa_misc_irq_destination(vtss_state, mask, destination));

    /* Always use sticky IRQ's */
    REG_WRM_CLR(VTSS_CPU_INTR_BYPASS, mask);

    /* Set up derived registers - PCIe */
    if (vtss_state->sys_config.using_pcie) {
        u32 external0, external1;
        // Enable PCIe IRQ
        REG_WRM_CLR(VTSS_CPU_PCIE_INTR_COMMON_CFG(0),
                    VTSS_M_CPU_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA);
        // Read current ext0 / ext1 mapping
        REG_RD(VTSS_CPU_DST_INTR_MAP(FA_IRQ_DEST_EXT0), &external0);
        REG_RD(VTSS_CPU_DST_INTR_MAP(FA_IRQ_DEST_EXT1), &external1);
        // Configure IRQ if external has a dest
        REG_WRM_CTL(VTSS_CPU_PCIE_INTR_CFG(0), (external0 != 0),
                    VTSS_F_CPU_PCIE_INTR_CFG_INTR_FALLING_ENA(1)|
                    VTSS_F_CPU_PCIE_INTR_CFG_INTR_RISING_ENA(1));
        REG_WRM_CTL(VTSS_CPU_PCIE_INTR_CFG(1), (external1 != 0),
                    VTSS_F_CPU_PCIE_INTR_CFG_INTR_FALLING_ENA(1)|
                    VTSS_F_CPU_PCIE_INTR_CFG_INTR_RISING_ENA(1));
        // Select EXT_DST1 if FA_IRQ_DEST_EXT1 non-zero
        REG_WRM_CTL(VTSS_CPU_PCIE_INTR_COMMON_CFG(0), (external1 != 0),
                    VTSS_F_CPU_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL(1));
        // Enable PCIe if
        REG_WRM_CTL(VTSS_CPU_PCIE_INTR_COMMON_CFG(0), (external0|external1),
                    VTSS_F_CPU_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA(1));
    }

    /* TBD - EXT  IRQ */
    return VTSS_RC_OK;
}

static vtss_rc fa_misc_irq_cfg(vtss_state_t *vtss_state,
                                const vtss_irq_t irq,
                                const vtss_irq_conf_t *const conf)
{
    vtss_rc rc = VTSS_RC_OK;
    if (conf->destination > 1) {
        rc = VTSS_RC_ERROR;
    } else {
        switch (irq) {
            case VTSS_IRQ_SOFTWARE:
                rc = fa_misc_irq_remap(vtss_state, VTSS_BIT(FA_IRQ_SW0)|VTSS_BIT(FA_IRQ_SW1), conf);
                break;
            case VTSS_IRQ_PTP_RDY:
                rc = fa_misc_irq_remap(vtss_state, VTSS_BIT(FA_IRQ_PTP_RDY), conf);
                break;
            case VTSS_IRQ_PTP_SYNC:
                rc = fa_misc_irq_remap(vtss_state, VTSS_BIT(FA_IRQ_PTP_SYNC), conf);
                break;
            case VTSS_IRQ_EXT0:
                rc = fa_misc_irq_remap(vtss_state, VTSS_BIT(FA_IRQ_EXT0), conf);
                break;
            case VTSS_IRQ_SGPIO:
                rc = fa_misc_irq_remap(vtss_state, VTSS_BIT(FA_IRQ_SGPIO1), conf);
                break;
            case VTSS_IRQ_SGPIO2:
                rc = fa_misc_irq_remap(vtss_state, VTSS_BIT(FA_IRQ_SGPIO2), conf);
                break;
            case VTSS_IRQ_EXT1:
                rc = fa_misc_irq_remap(vtss_state, VTSS_BIT(FA_IRQ_EXT1), conf);
                break;
            case VTSS_IRQ_GPIO:
                rc = fa_misc_irq_remap(vtss_state, VTSS_BIT(FA_IRQ_GPIO), conf);
                break;
            case VTSS_IRQ_DEV_ALL:
            default:
                rc = VTSS_RC_ERROR;
        }
    }
    return rc;
}

static vtss_rc fa_misc_irq_status(vtss_state_t *vtss_state, vtss_irq_status_t *status)
{
    u32 val, uio_irqs, dest;

    VTSS_MEMSET(status, 0, sizeof(*status));

    // Which interrupts are taken care of in user-space?
    if (vtss_state->sys_config.using_pcie) {
        // If running on an external CPU connected via PCIe, either external IRQ0 or
        // external IRQ1 may be routed through the PCIe interrupt. Which one
        // can be read from CPU_CFG:PCIE:PCIE_INTR_COMMON_CFG.LEGACY_MODE_INTR_SEL.
        REG_RD(VTSS_CPU_PCIE_INTR_COMMON_CFG(0), &val);
        dest = VTSS_X_CPU_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL(val) == 0 ? FA_IRQ_DEST_EXT0 : FA_IRQ_DEST_EXT1;
    } else {
        // Internal CPU interrupts are handled directly in the kernel through device tree
        return VTSS_RC_OK;
    }

    REG_RD(VTSS_CPU_DST_INTR_MAP(dest), &uio_irqs);

    // Who's interrupting?
    REG_RD(VTSS_CPU_INTR_IDENT, &val);

    // Only consider UIO interrupts
    val &= uio_irqs;

    status->raw_ident = val;
    REG_RD(VTSS_CPU_INTR_RAW, &status->raw_status);
    REG_RD(VTSS_CPU_INTR_ENA, &status->raw_mask);
    REG_WR(VTSS_CPU_INTR_ENA_CLR, val);
    status->raw_status &= uio_irqs;
    status->raw_mask   &= uio_irqs;

    if (val & (VTSS_BIT(FA_IRQ_SGPIO1))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SGPIO);
    }

    if (val & (VTSS_BIT(FA_IRQ_SGPIO2))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SGPIO2);
    }

    if (val & (VTSS_BIT(FA_IRQ_EXT0))) {
        status->active |= VTSS_BIT(VTSS_IRQ_EXT0);
    }

    if (val & (VTSS_BIT(FA_IRQ_EXT1))) {
        status->active |= VTSS_BIT(VTSS_IRQ_EXT1);
    }

    if(val & (VTSS_BIT(FA_IRQ_SW0)|VTSS_BIT(FA_IRQ_SW1))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SOFTWARE);
    }

    if(val & (VTSS_BIT(FA_IRQ_PTP_RDY))) {
        status->active |= VTSS_BIT(VTSS_IRQ_PTP_RDY);
    }

    if (val & (VTSS_BIT(FA_IRQ_PTP_SYNC))) {
        status->active |= VTSS_BIT(VTSS_IRQ_PTP_SYNC);
    }

    if (val & (VTSS_BIT(FA_IRQ_GPIO))) {
        status->active |= VTSS_BIT(VTSS_IRQ_GPIO);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_misc_irq_enable(vtss_state_t *vtss_state,
                                    const vtss_irq_t irq,
                                    const BOOL enable)
{
    u32 mask = 0;
    switch (irq) {
        case VTSS_IRQ_SOFTWARE:
            mask = VTSS_BIT(FA_IRQ_SW0)|VTSS_BIT(FA_IRQ_SW1);
            break;
        case VTSS_IRQ_PTP_RDY:
            mask = VTSS_BIT(FA_IRQ_PTP_RDY);
            break;
        case VTSS_IRQ_PTP_SYNC:
            mask = VTSS_BIT(FA_IRQ_PTP_SYNC);
            break;
        case VTSS_IRQ_EXT0:
            mask = VTSS_BIT(FA_IRQ_EXT0);
            break;
        case VTSS_IRQ_EXT1:
            mask = VTSS_BIT(FA_IRQ_EXT1);
            VTSS_D("enable:%d, mask:0x%X", enable, mask);
            break;
        case VTSS_IRQ_SGPIO:
            mask = VTSS_BIT(FA_IRQ_SGPIO1);
            VTSS_D("enable:%d, mask:0x%X", enable, mask);
            break;
        case VTSS_IRQ_SGPIO2:
            mask = VTSS_BIT(FA_IRQ_SGPIO2);
            VTSS_D("enable:%d, mask:0x%X", enable, mask);
            break;
        case VTSS_IRQ_GPIO:
            mask = VTSS_BIT(FA_IRQ_GPIO);
            break;
        default:
            return VTSS_RC_ERROR;
    }
    /* Ack sticky bits */
    REG_WR(VTSS_CPU_INTR_STICKY, mask);
    if (irq == VTSS_IRQ_FDMA_XTR) {
        /* VML files not available */
        /* REG_WRM_CTL(VTSS_CPU_CFG_FDMA_FDMA_INTR_ENA, enable, 1); /\* Always using ch 1 *\/ */
        /* REG_WR(VTSS_CPU_INTR_ENA_SET, mask); /\* Always enable top FDMA (cascading) IRQ *\/ */
    } else {
        if(enable) {
            REG_WR(VTSS_CPU_INTR_ENA_SET, mask);
        } else {
            REG_WR(VTSS_CPU_INTR_ENA_CLR, mask);
        }
    }
    return VTSS_RC_OK;
}
#endif  /* VTSS_FEATURE_IRQ_CONTROL */



static vtss_rc fa_poll_1sec(vtss_state_t *vtss_state)
{
    return vtss_fa_init_groups(vtss_state, VTSS_INIT_CMD_POLL);
}

/* =================================================================
 *  Miscellaneous - GPIO
 * =================================================================*/

vtss_rc vtss_fa_gpio_mode(vtss_state_t *vtss_state,
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
        REG_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_INTR_ENA1, mask);
    } else {
        REG_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_INTR_ENA, mask);
    }
    switch (mode) {
    case VTSS_GPIO_OUT:
    case VTSS_GPIO_IN:
    case VTSS_GPIO_IN_INT:
        if (gpio_no >= 32) {
            REG_WRM_CTL(VTSS_DEVCPU_GCB_GPIO_OE1, mode == VTSS_GPIO_OUT, mask);
        } else {
            REG_WRM_CTL(VTSS_DEVCPU_GCB_GPIO_OE, mode == VTSS_GPIO_OUT, mask);
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
        REG_WRM(VTSS_DEVCPU_GCB_GPIO_ALT1(0), alt_0, mask);
        REG_WRM(VTSS_DEVCPU_GCB_GPIO_ALT1(1), alt_1, mask);
    } else {
        REG_WRM(VTSS_DEVCPU_GCB_GPIO_ALT(0), alt_0, mask);
        REG_WRM(VTSS_DEVCPU_GCB_GPIO_ALT(1), alt_1, mask);
    }
    if (mode == VTSS_GPIO_IN_INT) {
        if (gpio_no >= 32) {
            REG_WRM_SET(VTSS_DEVCPU_GCB_GPIO_INTR_ENA1, mask);
        } else {
            REG_WRM_SET(VTSS_DEVCPU_GCB_GPIO_INTR_ENA, mask);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_gpio_read(vtss_state_t *vtss_state,
                              const vtss_chip_no_t  chip_no,
                              const vtss_gpio_no_t  gpio_no,
                              BOOL                  *const value)
{
    u32 val, mask;

    if (gpio_no >= 32) {
        mask = VTSS_BIT(gpio_no - 32);
        REG_RD(VTSS_DEVCPU_GCB_GPIO_IN1, &val);
    } else {
        mask = VTSS_BIT(gpio_no);
        REG_RD(VTSS_DEVCPU_GCB_GPIO_IN, &val);
    }

    *value = VTSS_BOOL(val & mask);
    return VTSS_RC_OK;
}

static vtss_rc fa_gpio_write(vtss_state_t *vtss_state,
                               const vtss_chip_no_t  chip_no,
                               const vtss_gpio_no_t  gpio_no,
                               const BOOL            value)
{
    u32 mask;

    if (gpio_no >= 32) {
        mask = VTSS_BIT(gpio_no - 32);
        if (value) {
            REG_WR(VTSS_DEVCPU_GCB_GPIO_OUT_SET1, mask);
        } else {
            REG_WR(VTSS_DEVCPU_GCB_GPIO_OUT_CLR1, mask);
        }
    } else {
        mask = VTSS_BIT(gpio_no);
        if (value) {
            REG_WR(VTSS_DEVCPU_GCB_GPIO_OUT_SET, mask);
        } else {
            REG_WR(VTSS_DEVCPU_GCB_GPIO_OUT_CLR, mask);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_gpio_event_poll(vtss_state_t          *vtss_state,
                                   const vtss_chip_no_t  chip_no,
                                   BOOL                  *const events)
{
    u32 pending, mask, i;

    REG_RD(VTSS_DEVCPU_GCB_GPIO_INTR, &pending);
    REG_RD(VTSS_DEVCPU_GCB_GPIO_INTR_ENA, &mask);
    pending &= mask;
    REG_WR(VTSS_DEVCPU_GCB_GPIO_INTR, pending);

    for (i = 0; i < 32; i++) {
        events[i] = (pending & 1 << i) ? TRUE : FALSE;
    }

    REG_RD(VTSS_DEVCPU_GCB_GPIO_INTR1, &pending);
    REG_RD(VTSS_DEVCPU_GCB_GPIO_INTR_ENA1, &mask);
    pending &= mask;
    REG_WR(VTSS_DEVCPU_GCB_GPIO_INTR1, pending);

    for (i = 32; i < VTSS_GPIOS; i++) {
        events[i] = (pending & 1 << (i - 32)) ? TRUE : FALSE;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_gpio_event_enable(vtss_state_t          *vtss_state,
                                    const vtss_chip_no_t  chip_no,
                                    const vtss_gpio_no_t  gpio_no,
                                    const BOOL            enable)
{

    u32 mask;

    if (gpio_no >= 32) {
        mask = VTSS_BIT(gpio_no - 32);
        REG_WRM(VTSS_DEVCPU_GCB_GPIO_INTR_ENA1, enable << (gpio_no - 32), mask);
    } else {
        mask = VTSS_BIT(gpio_no);
        REG_WRM(VTSS_DEVCPU_GCB_GPIO_INTR_ENA, enable << gpio_no, mask);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_sgpio_init(vtss_state_t *vtss_state)
{
    u32  grp, bit;

    // Gotta change the interrupt type for all SGPIOs from its default,
    // which is level, to something else to avoid spurious interrupts
    // when failing or unable (due to board layout) to initialize the
    // polarity of the level interrupts correct.
    for (grp = 0; grp < vtss_state->misc.sgpio_group_count; grp++) {
        for (bit = 0; bit < 4; bit++) {
            // Enable rising edge triggered interrupt
            REG_WR(VTSS_DEVCPU_GCB_SIO_INTR_TRIGGER0(grp, bit), 0xFFFFFFFF);
            REG_WR(VTSS_DEVCPU_GCB_SIO_INTR_TRIGGER1(grp, bit), 0xFFFFFFFF);
        }
    }

    return VTSS_RC_OK;
}

/* PCS signal detect to SGPIO bit mapping  */
static vtss_rc fa_sgpio_sd_map_set(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    vtss_port_sgpio_map_t *sd_map;
    u32 bit_index;
    BOOL ena;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        sd_map = &vtss_state->port.map[port_no].sd_map;
        if (sd_map->action == VTSS_SD_SGPIO_MAP_IGNORE) {
            continue;
        }
        /* Enable/disable mapping globally */
        ena = sd_map->action == VTSS_SD_SGPIO_MAP_ENABLE ? TRUE : FALSE;
        REG_WRM(VTSS_DEVCPU_GCB_HW_SGPIO_SD_CFG,
                VTSS_F_DEVCPU_GCB_HW_SGPIO_SD_CFG_SD_MAP_SEL(ena),
                VTSS_M_DEVCPU_GCB_HW_SGPIO_SD_CFG_SD_MAP_SEL);

        if (!ena) {
            return VTSS_RC_OK;
        }
        /* Each device can be mapped to any of the bit in the SGPIOs which consist of:
           3 groups, 32 ports in each group and 4 bits for each port = 384 bits */
        bit_index = sd_map->group * 32 * 4 + sd_map->port * 4 + sd_map->bit;
        REG_WR(VTSS_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG(VTSS_CHIP_PORT(port_no)), bit_index);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_sgpio_event_poll(vtss_state_t             *vtss_state,
                                    const vtss_chip_no_t     chip_no,
                                    const vtss_sgpio_group_t group,
                                    const u32                bit,
                                    BOOL                     *const events)
{
    u32 i, val;

    REG_RD(VTSS_DEVCPU_GCB_SIO_INTR_IDENT(group, bit), &val);
    REG_WR(VTSS_DEVCPU_GCB_SIO_INTR(group, bit), val);  /* Clear pending */

    VTSS_I("SGPIO%u Interrupt ident for bit %u: 0x%08x", group, bit, val);

    /* Setup serial IO port enable register */
    for (i = 0; i < VTSS_SGPIO_PORTS; i++) {
        events[i] = VTSS_BOOL(val & (1<<i));
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_sgpio_event_enable(vtss_state_t             *vtss_state,
                                      const vtss_chip_no_t     chip_no,
                                      const vtss_sgpio_group_t group,
                                      const u32                port,
                                      const u32                bit,
                                      const BOOL               enable)
{
    u32 mask = (1 << port);

    if (enable) {
        VTSS_D("group:%d mask:0x%X, bit:0x%X, 0x%X", group, mask, bit, VTSS_F_DEVCPU_GCB_SIO_INTR_ENA_SIO_INTR_ENA(1 << bit));
        REG_WRM(VTSS_DEVCPU_GCB_SIO_INTR(group, bit), mask, mask); // Clear any pending interrupts, so we don't get any spurious interrupt when we enable.
        REG_WRM(VTSS_DEVCPU_GCB_SIO_INTR_ENA(group, bit), mask, mask);  // Enable only the group/bit in question.
    } else {
        VTSS_D("Disable port:%d, group:%d, bit:%d", port, group, bit);
        REG_WRM(VTSS_DEVCPU_GCB_SIO_INTR_ENA(group, bit), 0, mask);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_sgpio_conf_set(vtss_state_t *vtss_state,
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

    REG_WR(VTSS_DEVCPU_GCB_SIO_PORT_ENA(group), val);

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

    REG_WRM(VTSS_DEVCPU_GCB_SIO_CFG(group),
            VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_BMODE_0(bmode[0]) |
            VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_BMODE_1(bmode[1]) |
            VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_BURST_GAP(0) |
            VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_PORT_WIDTH(conf->bit_count - 1) |
            VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_AUTO_REPEAT(1),
            VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_BMODE_0 |
            VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_BMODE_1 |
            VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_BURST_GAP |
            VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_PORT_WIDTH |
            VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_AUTO_REPEAT);

    REG_WRM(VTSS_DEVCPU_GCB_SIO_CLOCK(group),
            // Configuring the denominator of the system clock frequency:
            // VTSS_CORE_CLOCK_250MHZ -> SIO clock = 250MHz / 50 =  5   MHz
            // VTSS_CORE_CLOCK_500MHZ -> SIO clock = 500MHz / 50 = 10   MHz
            // VTSS_CORE_CLOCK_625MHZ -> SIO clock = 625MHz / 50 = 12.5 MHz
            VTSS_F_DEVCPU_GCB_SIO_CLOCK_SIO_CLK_FREQ(50),
            VTSS_M_DEVCPU_GCB_SIO_CLOCK_SIO_CLK_FREQ);

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
            REG_WRM(VTSS_DEVCPU_GCB_SIO_INTR_POL(group, bit_idx), value, mask);
            VTSS_N("group:%d, port:%d, bit_idx:%d, int_pol_high:%d", group, port, bit_idx, pol_high);
        }

        REG_WRM(VTSS_DEVCPU_GCB_SIO_PORT_CFG(group, port),
                VTSS_F_DEVCPU_GCB_SIO_PORT_CFG_PWM_SOURCE(0) | // While PCB-134 is unstable
                VTSS_F_DEVCPU_GCB_SIO_PORT_CFG_BIT_POLARITY(pol) |
                VTSS_F_DEVCPU_GCB_SIO_PORT_CFG_BIT_SOURCE(val),
                VTSS_M_DEVCPU_GCB_SIO_PORT_CFG_PWM_SOURCE |
                VTSS_M_DEVCPU_GCB_SIO_PORT_CFG_BIT_POLARITY |
                VTSS_M_DEVCPU_GCB_SIO_PORT_CFG_BIT_SOURCE);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_sgpio_read(vtss_state_t *vtss_state,
                               const vtss_chip_no_t     chip_no,
                               const vtss_sgpio_group_t group,
                               vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS])
{
    u32 i, port, value;

    for (i = 0; i < 4; i++) {
        REG_RD(VTSS_DEVCPU_GCB_SIO_INPUT_DATA(group, i), &value);
        for (port = 0; port < 32; port++) {
            data[port].value[i] = VTSS_BOOL(value & (1 << port));
        }
    }
    return VTSS_RC_OK;
}


/* - Debug print --------------------------------------------------- */

#define FA_DEBUG_GPIO(pr, addr, name) FA_DEBUG_REG_NAME(pr, DEVCPU_GCB, GPIO_##addr, "GPIO_"name)
#define FA_DEBUG_SIO(pr, addr, name) FA_DEBUG_REG_NAME(pr, DEVCPU_GCB, SIO_##addr, "SIO_"name)
#define FA_DEBUG_SIO_INST(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEVCPU_GCB_SIO_##addr, i, "SIO_"name)


#define FA_DEBUG_TGT(pr, name) jr_debug_tgt(pr, #name, VTSS_TO_##name)


static vtss_rc fa_debug_misc(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32  i, g;
    char name[32];
    pr("Name          Target\n");

    vtss_fa_debug_reg_header(pr, "GPIOs");
    FA_DEBUG_GPIO(pr, OUT, "OUT");
    FA_DEBUG_GPIO(pr, OUT1, "OUT1");
    FA_DEBUG_GPIO(pr, OE, "OE");
    FA_DEBUG_GPIO(pr, OE1, "OE1");
    FA_DEBUG_GPIO(pr, IN, "IN");
    FA_DEBUG_GPIO(pr, IN1, "IN1");
    FA_DEBUG_GPIO(pr, INTR, "INTR");
    FA_DEBUG_GPIO(pr, INTR_ENA, "INTR_ENA");
    FA_DEBUG_GPIO(pr, INTR_IDENT, "INTR_IDENT");
    FA_DEBUG_GPIO(pr, ALT(0), "ALT_0(0-31)");
    FA_DEBUG_GPIO(pr, ALT(1), "ALT_1(0-31)");
    FA_DEBUG_GPIO(pr, ALT1(0), "ALT1_0(32-63)");
    FA_DEBUG_GPIO(pr, ALT1(1), "ALT1_1(32-63)");
    pr("\n");

    for (g = 0; g < VTSS_SGPIO_GROUPS; g++) {
        VTSS_SPRINTF(name, "SGPIOs Group:%u", g);
        vtss_fa_debug_reg_header(pr, name);
        for (i = 0; i < 4; i++) {
            FA_DEBUG_SIO_INST(pr, INPUT_DATA(g,i), i, "INPUT_DATA");
            FA_DEBUG_SIO_INST(pr, INTR_POL(g,i), i, "INTR_POL");
            FA_DEBUG_SIO_INST(pr, INTR(g,i), i, "INTR");
        }
        FA_DEBUG_SIO(pr, PORT_ENA(g), "PORT_ENA");
        FA_DEBUG_SIO(pr, CFG(g), "CFG");
        FA_DEBUG_SIO(pr, CLOCK(g), "CLOCK");
        for (i = 0; i < 32; i++) {
            FA_DEBUG_SIO_INST(pr, PORT_CFG(g,i), i, "PORT_CFG");
        }
        pr("\n");
    }

    vtss_fa_debug_reg_header(pr, "IRQs");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_RAW, "INTR_RAW");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_TRIGGER(0), "INTR_TRIGGER(0)");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_FORCE, "INTR_FORCE");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_STICKY, "INTR_STICKY");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_BYPASS, "INTR_BYPASS");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_ENA, "INTR_ENA");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_ENA_CLR, "INTR_ENA_CLR");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_ENA_SET, "INTR_ENA_SET");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_IDENT, "INTR_IDENT");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_ENA, "DEV_INTR_ENA");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_STICKY, "DEV_INTR_STICKY");
    FA_DEBUG_REG_NAME(pr, CPU, INTR_IDENT, "DEV_INTR_IDENT");
    FA_DEBUG_REG_NAME(pr, CPU, EXT_SRC_INTR_POL, "EXT_SRC_INTR_POL");
    FA_DEBUG_REG_NAME(pr, CPU, EXT_DST_INTR_POL, "EXT_DST_INTR_POL");
    FA_DEBUG_REG_NAME(pr, CPU, EXT_DST_INTR_DRV, "EXT_DST_INTR_DRV");

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_misc_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MISC, fa_debug_misc, vtss_state, pr, info));
    return VTSS_RC_OK;
}




/* - Initialization ------------------------------------------------ */

vtss_rc vtss_fa_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_misc_state_t *state = &vtss_state->misc;

    if (cmd == VTSS_INIT_CMD_CREATE) {
        state->reg_read = fa_reg_read;
        state->reg_write = fa_reg_write;
        state->chip_id_get = vtss_fa_chip_id_get;
        state->poll_1sec = fa_poll_1sec;
        state->gpio_mode = vtss_fa_gpio_mode;
        state->gpio_read = fa_gpio_read;
        state->gpio_write = fa_gpio_write;
        state->sgpio_conf_set = fa_sgpio_conf_set;
        state->sgpio_read = fa_sgpio_read;
        state->sgpio_event_enable = fa_sgpio_event_enable;
        state->sgpio_event_poll = fa_sgpio_event_poll;
        state->gpio_event_enable = fa_gpio_event_enable;
        state->gpio_event_poll = fa_gpio_event_poll;
        state->ptp_event_poll = fa_ptp_event_poll;
        state->ptp_event_enable = fa_ptp_event_enable;
        state->dev_all_event_poll = fa_dev_all_event_poll;
        state->dev_all_event_enable = fa_dev_all_event_enable;
        state->intr_cfg = fa_intr_cfg;
        state->intr_pol_negation = fa_intr_pol_negation;
#ifdef VTSS_FEATURE_IRQ_CONTROL
        /* Only external destinations (overlaid GPIOs) are configured here */
        /* Interrupt to the internal CPU is configured in the linux kernel */
        state->irq_cfg = fa_misc_irq_cfg;
        state->irq_status = fa_misc_irq_status;
        state->irq_enable = fa_misc_irq_enable;
#endif  /* VTSS_FEATURE_IRQ_CONTROL */
        state->gpio_count = VTSS_GPIOS;
        state->sgpio_group_count = VTSS_SGPIO_GROUPS;
#if defined(VTSS_FEATURE_EEE)
        vtss_state->eee.port_conf_set   = fa_eee_port_conf_set;
#endif /* VTSS_FEATURE_EEE */
#if defined(VTSS_FEATURE_FAN)
        vtss_state->fan.controller_init = fa_fan_controller_init;
        vtss_state->fan.cool_lvl_get    = fa_fan_cool_lvl_get;
        vtss_state->fan.cool_lvl_set    = fa_fan_cool_lvl_set;
        vtss_state->fan.rotation_get    = fa_fan_rotation_get;
#endif /* VTSS_FEATURE_FAN */

#if defined(VTSS_FEATURE_TEMP_SENSOR)
        vtss_state->temp_sensor.chip_temp_init = fa_temp_sensor_init;
        vtss_state->temp_sensor.chip_temp_get  = fa_temp_sensor_get;
#endif /* VTSS_FEATURE_TEMP_SENSOR */
    } else if (cmd == VTSS_INIT_CMD_INIT) {
        VTSS_RC(fa_sgpio_init(vtss_state));
    } else if (cmd == VTSS_INIT_CMD_PORT_MAP) {
        VTSS_RC(fa_sgpio_sd_map_set(vtss_state));
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_FA */
