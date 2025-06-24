// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

/* =================================================================
 *  EEE - Energy Efficient Ethernet
 * =================================================================*/

#if defined(VTSS_FEATURE_EEE)
vtss_rc vtss_cil_eee_port_conf_set(vtss_state_t                     *vtss_state,
                                   const vtss_port_no_t              port_no,
                                   const vtss_eee_port_conf_t *const conf)
{
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_FAN)
vtss_rc vtss_cil_fan_controller_init(vtss_state_t *vtss_state, const vtss_fan_conf_t *const spec)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_fan_cool_lvl_set(vtss_state_t *vtss_state, u8 lvl) { return VTSS_RC_OK; }

vtss_rc vtss_cil_fan_cool_lvl_get(vtss_state_t *vtss_state, u8 *duty_cycle) { return VTSS_RC_OK; }

vtss_rc vtss_cil_fan_rotation_get(vtss_state_t    *vtss_state,
                                  vtss_fan_conf_t *fan_spec,
                                  u32             *rotation_count)
{
    return VTSS_RC_OK;
}
#endif
/* ================================================================= *
 *  Temperature Sensor
 * ================================================================= */
#if defined(VTSS_FEATURE_TEMP_SENSOR)
vtss_rc vtss_cil_chip_temp_init(vtss_state_t *vtss_state, const BOOL enable)
{
    // Enable/Disable
    REG_WRM(CHIP_TOP_PVT_SENSOR_CFG, enable ? CHIP_TOP_PVT_SENSOR_CFG_SAMPLE_ENA_M : 0,
            CHIP_TOP_PVT_SENSOR_CFG_SAMPLE_ENA_M);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_chip_temp_get(vtss_state_t *vtss_state, i16 *temp_celsius)
{
    u32     val;
    int64_t x, r;
    int64_t scale = 1e+15; // Scale factor for calculations

    REG_RD(CHIP_TOP_PVT_SENSOR_STAT, &val);
    val = CHIP_TOP_PVT_SENSOR_STAT_DATA(val);

    // Convert val to int64_t
    x = (int64_t)val;

    // Calculate as according to sensor spec
    r = -34627;                 // -3.4627E-11 * 10^15
    r = (r * x) + 110230000;    //  1.1023E-7  * 10^15
    r = (r * x) - 191650000000; // -1.9165E-4  * 10^15
    r = (r * x) + 3.0604e+14;   //  3.0604E-1  * 10^15
    r = (r * x) - 5.6197e+16;   // -5.6197E1   * 10^15

    // Convert r back to an integer for temp_celsius
    *temp_celsius = (i16)(r / scale);

    return VTSS_RC_OK;
}
#endif
/* ================================================================= *
 *  Miscellaneous
 * ================================================================= */

vtss_rc vtss_cil_misc_reg_read(vtss_state_t        *vtss_state,
                               const vtss_chip_no_t chip_no,
                               const u32            addr,
                               u32 *const           value)
{
#if defined(GCB_VA_ADDR)
    u32 ctrl;

    REG_WR(GCB_VA_ADDR, addr);
    REG_RD(GCB_VA_DATA, value);
    REG_RD(GCB_VA_CTRL, &ctrl);
    REG_RD(GCB_VA_DATA, value);
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_reg_write(vtss_state_t        *vtss_state,
                                const vtss_chip_no_t chip_no,
                                const u32            addr,
                                const u32            value)
{
#if defined(GCB_VA_ADDR)
    u32 ctrl;

    REG_WR(GCB_VA_ADDR, addr);
    REG_WR(GCB_VA_DATA, value);
    REG_RD(GCB_VA_CTRL, &ctrl);
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id)
{
#if defined(GCB_CHIP_ID)
    u32 val;

    REG_RD(GCB_CHIP_ID, &val);
    if (val == 0 || val == 0xffffffff) {
        VTSS_E("CPU interface error, chipid: 0x%08x", val);
        return VTSS_RC_ERROR;
    }
    chip_id->part_number = GCB_CHIP_ID_PART_ID_X(val);
    chip_id->revision = GCB_CHIP_ID_REV_ID_X(val);
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_ptp_event_poll(vtss_state_t *vtss_state, vtss_ptp_event_type_t *ev_mask)
{
    u32 sticky, mask;

    // PTP events
    REG_RD(PTP_PIN_INTR, &sticky);
    REG_WR(PTP_PIN_INTR, sticky);
    REG_RD(PTP_PIN_INTR_ENA, &mask);
    sticky &= mask; // Only handle enabled sources

    *ev_mask = 0;
    *ev_mask |= (sticky & (1 << 0) ? VTSS_PTP_PIN_0_SYNC_EV : 0);
    *ev_mask |= (sticky & (1 << 1) ? VTSS_PTP_PIN_1_SYNC_EV : 0);
    *ev_mask |= (sticky & (1 << 2) ? VTSS_PTP_PIN_2_SYNC_EV : 0);
    *ev_mask |= (sticky & (1 << 3) ? VTSS_PTP_PIN_3_SYNC_EV : 0);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_ptp_event_enable(vtss_state_t         *vtss_state,
                                       vtss_ptp_event_type_t ev_mask,
                                       BOOL                  enable)
{
    u32 val = 0, msk = 0, ena = VTSS_BOOL(enable);

    if (ev_mask & VTSS_PTP_PIN_0_SYNC_EV) {
        val |= (ena << 0);
        msk |= (1 << 0);
    }
    if (ev_mask & VTSS_PTP_PIN_1_SYNC_EV) {
        val |= (ena << 1);
        msk |= (1 << 1);
    }
    if (ev_mask & VTSS_PTP_PIN_2_SYNC_EV) {
        val |= (ena << 2);
        msk |= (1 << 2);
    }
    if (ev_mask & VTSS_PTP_PIN_3_SYNC_EV) {
        val |= (ena << 3);
        msk |= (1 << 3);
    }
    if (msk) {
        REG_WRM(PTP_PIN_INTR_ENA, PTP_PIN_INTR_ENA_INTR_ENA(val), PTP_PIN_INTR_ENA_INTR_ENA(msk));
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_dev_all_event_poll(vtss_state_t              *vtss_state,
                                         vtss_dev_all_event_poll_t  poll_type,
                                         vtss_dev_all_event_type_t *ev_mask)
{
#if defined(CPU_DEV_INTR_IDENT)
    u32            ident, port;
    vtss_port_no_t port_no;

    // Read the active interrupt sources (sticky and enabled)
    REG_RD(CPU_DEV_INTR_IDENT, &ident);
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        ev_mask[port_no] = (ident & VTSS_BIT(port) ? VTSS_DEV_ALL_LINK_EV : 0);
    }
    REG_WR(CPU_DEV_INTR_STICKY, ident); // Clear sticky
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_dev_all_event_enable(vtss_state_t             *vtss_state,
                                           vtss_port_no_t            port_no,
                                           vtss_dev_all_event_type_t ev_mask,
                                           BOOL                      enable)
{
#if defined(CPU_DEV_INTR_ENA)
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 msk = VTSS_BIT(port);

    if (ev_mask & VTSS_DEV_ALL_LINK_EV) {
        REG_WRM(CPU_DEV_INTR_ENA, enable ? msk : 0, msk);
        REG_WR(CPU_DEV_INTR_STICKY, msk); // Clear sticky
    }
#endif
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_INTERRUPTS)
vtss_rc vtss_cil_misc_intr_cfg(vtss_state_t *vtss_state,
                               const u32     intr_mask,
                               const BOOL    polarity,
                               const BOOL    enable)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_intr_pol_negation(vtss_state_t *vtss_state) { return VTSS_RC_OK; }
#endif

#if defined(VTSS_FEATURE_IRQ_CONTROL)
vtss_rc vtss_cil_misc_irq_cfg(vtss_state_t                *vtss_state,
                              const vtss_irq_t             irq,
                              const vtss_irq_conf_t *const conf)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_irq_status(vtss_state_t *vtss_state, vtss_irq_status_t *status)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_irq_enable(vtss_state_t *vtss_state, const vtss_irq_t irq, const BOOL enable)
{
    return VTSS_RC_OK;
}
#endif

/* =================================================================
 *  Miscellaneous - GPIO
 * =================================================================*/

vtss_rc vtss_lan966x_gpio_mode(vtss_state_t          *vtss_state,
                               const vtss_chip_no_t   chip_no,
                               const vtss_gpio_no_t   gpio_no,
                               const vtss_gpio_mode_t mode)
{
#if defined(GCB_GPIO_OUT_SET2)
    u32 msk = VTSS_BIT(gpio_no % 32), alt = 0, alt_0, alt_1, alt_2;

    switch (mode) {
    case VTSS_GPIO_OUT:
    case VTSS_GPIO_IN:
    case VTSS_GPIO_IN_INT: break;
    case VTSS_GPIO_ALT_0: // ALT1 in data sheet
    case VTSS_GPIO_ALT_1: // ALT2 in data sheet
    case VTSS_GPIO_ALT_2: // ALT3 in data sheet
    case VTSS_GPIO_ALT_3: // ALT4 in data sheet
    case VTSS_GPIO_ALT_4: // ALT5 in data sheet
    case VTSS_GPIO_ALT_5: // ALT6 in data sheet
        alt = (mode - VTSS_GPIO_ALT_0 + 1);
        break;
    default: VTSS_E("illegal mode"); return VTSS_RC_ERROR;
    }
    alt_0 = (alt & 1 ? msk : 0);
    alt_1 = (alt & 2 ? msk : 0);
    alt_2 = (alt & 4 ? msk : 0);

    if (gpio_no < 32) {
        REG_WRM_CLR(GCB_GPIO_INTR_ENA, msk);
        REG_WRM_CTL(GCB_GPIO_OE, mode == VTSS_GPIO_OUT, msk);
        REG_WRM(GCB_GPIO_ALT(0), alt_0, msk);
        REG_WRM(GCB_GPIO_ALT(1), alt_1, msk);
        REG_WRM(GCB_GPIO_ALT(2), alt_2, msk);
        if (mode == VTSS_GPIO_IN_INT) {
            REG_WRM_SET(GCB_GPIO_INTR_ENA, msk);
        }
    } else if (gpio_no < 64) {
        REG_WRM_CLR(GCB_GPIO_INTR_ENA1, msk);
        REG_WRM_CTL(GCB_GPIO_OE1, mode == VTSS_GPIO_OUT, msk);
        REG_WRM(GCB_GPIO_ALT1(0), alt_0, msk);
        REG_WRM(GCB_GPIO_ALT1(1), alt_1, msk);
        REG_WRM(GCB_GPIO_ALT1(2), alt_2, msk);
        if (mode == VTSS_GPIO_IN_INT) {
            REG_WRM_SET(GCB_GPIO_INTR_ENA1, msk);
        }
    } else {
        REG_WRM_CLR(GCB_GPIO_INTR_ENA2, msk);
        REG_WRM_CTL(GCB_GPIO_OE2, mode == VTSS_GPIO_OUT, msk);
        REG_WRM(GCB_GPIO_ALT2(0), alt_0, msk);
        REG_WRM(GCB_GPIO_ALT2(1), alt_1, msk);
        REG_WRM(GCB_GPIO_ALT2(2), alt_2, msk);
        if (mode == VTSS_GPIO_IN_INT) {
            REG_WRM_SET(GCB_GPIO_INTR_ENA2, msk);
        }
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_gpio_mode(vtss_state_t          *vtss_state,
                                const vtss_chip_no_t   chip_no,
                                const vtss_gpio_no_t   gpio_no,
                                const vtss_gpio_mode_t mode)
{
    return vtss_lan966x_gpio_mode(vtss_state, chip_no, gpio_no, mode);
}

vtss_rc vtss_cil_misc_gpio_read(vtss_state_t        *vtss_state,
                                const vtss_chip_no_t chip_no,
                                const vtss_gpio_no_t gpio_no,
                                BOOL *const          value)
{
#if defined(GCB_GPIO_IN2)
    u32 val, msk = VTSS_BIT(gpio_no % 32);

    if (gpio_no < 32) {
        REG_RD(GCB_GPIO_IN, &val);
    } else if (gpio_no < 64) {
        REG_RD(GCB_GPIO_IN1, &val);
    } else {
        REG_RD(GCB_GPIO_IN2, &val);
    }
    *value = VTSS_BOOL(val & msk);
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_gpio_write(vtss_state_t        *vtss_state,
                                 const vtss_chip_no_t chip_no,
                                 const vtss_gpio_no_t gpio_no,
                                 const BOOL           value)
{
#if defined(GCB_GPIO_OUT_SET2)
    u32 msk = VTSS_BIT(gpio_no % 32);

    if (gpio_no < 32) {
        if (value) {
            REG_WR(GCB_GPIO_OUT_SET, msk);
        } else {
            REG_WR(GCB_GPIO_OUT_CLR, msk);
        }
    } else if (gpio_no < 64) {
        if (value) {
            REG_WR(GCB_GPIO_OUT_SET1, msk);
        } else {
            REG_WR(GCB_GPIO_OUT_CLR1, msk);
        }
    } else {
        if (value) {
            REG_WR(GCB_GPIO_OUT_SET2, msk);
        } else {
            REG_WR(GCB_GPIO_OUT_CLR2, msk);
        }
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_gpio_event_enable(vtss_state_t        *vtss_state,
                                        const vtss_chip_no_t chip_no,
                                        const vtss_gpio_no_t gpio_no,
                                        const BOOL           enable)
{
#if defined(GCB_GPIO_INTR_ENA2)
    u32 msk = VTSS_BIT(gpio_no % 32);

    if (gpio_no < 32) {
        REG_WRM(GCB_GPIO_INTR_ENA, enable ? msk : 0, msk);
    } else if (gpio_no < 64) {
        REG_WRM(GCB_GPIO_INTR_ENA1, enable ? msk : 0, msk);
    } else {
        REG_WRM(GCB_GPIO_INTR_ENA2, enable ? msk : 0, msk);
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_gpio_event_poll(vtss_state_t        *vtss_state,
                                      const vtss_chip_no_t chip_no,
                                      BOOL *const          events)
{
#if defined(GCB_GPIO_INTR2)
    u32 msk[3], i;

    // Read and clear pending interrupts
    REG_RD(GCB_GPIO_INTR_IDENT, &msk[0]);
    REG_WR(GCB_GPIO_INTR, msk[0]);
    REG_RD(GCB_GPIO_INTR_IDENT1, &msk[1]);
    REG_WR(GCB_GPIO_INTR1, msk[1]);
    REG_RD(GCB_GPIO_INTR_IDENT2, &msk[2]);
    REG_WR(GCB_GPIO_INTR2, msk[2]);
    for (i = 0; i < VTSS_GPIOS; i++) {
        events[i] = (msk[i / 32] & (1 << (i % 32)) ? 1 : 0);
    }
#endif
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SERIAL_GPIO)
vtss_rc vtss_cil_misc_sgpio_event_poll(vtss_state_t            *vtss_state,
                                       const vtss_chip_no_t     chip_no,
                                       const vtss_sgpio_group_t group,
                                       const u32                bit,
                                       BOOL *const              events)
{
#if defined(GCB_SIO_CFG)
    u32 i, val;

    // Clear pending interrupts
    REG_RD(GCB_SIO_INTR(bit), &val);
    REG_WR(GCB_SIO_INTR(bit), val);

    for (i = 0; i < 32; i++) {
        events[i] = VTSS_BOOL(val & (1 << i));
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_sgpio_event_enable(vtss_state_t            *vtss_state,
                                         const vtss_chip_no_t     chip_no,
                                         const vtss_sgpio_group_t group,
                                         const u32                port,
                                         const u32                bit,
                                         const BOOL               enable)
{
#if defined(GCB_SIO_CFG)
    u32 msk = (1 << port);

    if (enable) {
        // Clear any pending interrupts to avoid spurious interrupt when we enable
        REG_WRM(GCB_SIO_INTR(bit), msk, msk);
        REG_WRM(GCB_SIO_INTR_ENA(bit), msk, msk);
        REG_WRM_SET(GCB_SIO_CFG, GCB_SIO_CFG_SIO_GLOB_INTR_ENA_M);

        // Enable rising edge triggered interrupt
        REG_WRM(GCB_SIO_INTR_TRIGGER0(bit), msk, msk);
        REG_WRM(GCB_SIO_INTR_TRIGGER1(bit), msk, msk);
    } else {
        REG_WRM(GCB_SIO_INTR_ENA(bit), 0, msk);
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_sgpio_conf_set(vtss_state_t                  *vtss_state,
                                     const vtss_chip_no_t           chip_no,
                                     const vtss_sgpio_group_t       group,
                                     const vtss_sgpio_conf_t *const conf)
{
#if defined(GCB_SIO_CFG)
    u32  i, port, val = 0, msk, bmode[2], bit_idx, cfg;
    bool change = TRUE;

    // Serial IO port enable register
    for (port = 0; port < 32; port++) {
        if (conf->port_conf[port].enabled)
            val |= VTSS_BIT(port);
    }
    REG_WR(GCB_SIO_PORT_ENA, val);

    // Burst mode
    for (i = 0; i < 2; i++) {
        switch (conf->bmode[i]) {
        case VTSS_SGPIO_BMODE_TOGGLE:
            if (i == 0) {
                VTSS_E("blink mode 0 does not support TOGGLE (group:%d)", group);
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
        case VTSS_SGPIO_BMODE_5: bmode[i] = (i == 0 ? 0 : 2); break;
        default:                 return VTSS_RC_ERROR;
        }
    }
    REG_WRM(GCB_SIO_CFG,
            GCB_SIO_CFG_SIO_BMODE_1(bmode[1]) | GCB_SIO_CFG_SIO_BMODE_0(bmode[0]) |
                GCB_SIO_CFG_SIO_BURST_GAP(3) | GCB_SIO_CFG_SIO_AUTO_REPEAT(1) |
                GCB_SIO_CFG_SIO_PORT_WIDTH(conf->bit_count - 1),
            GCB_SIO_CFG_SIO_BMODE_1_M | GCB_SIO_CFG_SIO_BMODE_0_M | GCB_SIO_CFG_SIO_BURST_GAP_M |
                GCB_SIO_CFG_SIO_AUTO_REPEAT_M | GCB_SIO_CFG_SIO_PORT_WIDTH_M);
    REG_WR(GCB_SIO_CLOCK,
           GCB_SIO_CLOCK_SIO_CLK_FREQ(20) |
               GCB_SIO_CLOCK_SYS_CLK_PERIOD(vtss_lan966x_clk_period_ps(vtss_state) / 100));

    for (port = 0; port < 32; port++) {
        change = TRUE;
        cfg = GCB_SIO_PORT_CFG_PWM_SOURCE(0);
        for (bit_idx = 0; bit_idx < 4; bit_idx++) {
            val = conf->port_conf[port].mode[bit_idx];
            switch (val) {
            case VTSS_SGPIO_MODE_NO_CHANGE: change = FALSE; break;
            case VTSS_SGPIO_MODE_0_ACTIVITY_INV:
            case VTSS_SGPIO_MODE_1_ACTIVITY_INV:
                val -= 2;
                cfg |= GCB_SIO_PORT_CFG_BIT_POLARITY(1 << bit_idx);
                /* fall-through */
            default:
                val = VTSS_ENCODE_BITFIELD(val, (bit_idx * 3), 3);
                cfg |= GCB_SIO_PORT_CFG_BIT_SOURCE(val);
                break;
            }
            msk = VTSS_BIT(port);
            val = (conf->port_conf[port].int_pol_high[bit_idx] ? 0 : msk);
            REG_WRM(GCB_SIO_INTR_POL(bit_idx), val, msk);
        }

        if (change) {
            REG_WR(GCB_SIO_PORT_CFG(port), cfg);
        }
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_sgpio_read(vtss_state_t            *vtss_state,
                                 const vtss_chip_no_t     chip_no,
                                 const vtss_sgpio_group_t group,
                                 vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS])
{
#if defined(GCB_SIO_CFG)
    u32 i, port, val;

    for (i = 0; i < 4; i++) {
        REG_RD(GCB_SIO_INPUT_DATA(i), &val);
        for (port = 0; port < 32; port++) {
            data[port].value[i] = VTSS_BOOL(val & (1 << port));
        }
    }
#endif
    return VTSS_RC_OK;
}
#endif

// Switch Device PCS signal detect to SGPIO bit mapping.
// No static SD SIO to DEV mapping.
// The SIO to DEV (SD) mapping must be set in the below function
static vtss_rc lan966x_sgpio_sd_map_set(vtss_state_t *vtss_state)
{
#if defined(GCB_HW_SGPIO_TO_SD_MAP_CFG)
    vtss_port_no_t         port_no;
    vtss_port_sgpio_map_t *sd_map;
    u32                    bit_index;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        sd_map = &vtss_state->port.map[port_no].sd_map;
        if (sd_map->action == VTSS_SD_SGPIO_MAP_IGNORE) {
            // Igonore means default, SD is bit 0 for each SGPIO port
            bit_index = VTSS_CHIP_PORT(port_no) * 4;
        } else {
            /* Each device can be mapped to any of the bit in the SGPIOs which
               consist of: 1  group, 32 ports in each group and 4 bits for each
               port = 128 bits */
            bit_index = sd_map->port * 4 + sd_map->bit;
        }
        if (bit_index > 128) {
            VTSS_E("sgpio index %d out of bounds", bit_index);
            return VTSS_RC_ERROR;
        }
        REG_WR(GCB_HW_SGPIO_TO_SD_MAP_CFG(VTSS_CHIP_PORT(port_no)), bit_index);
    }
#endif
    return VTSS_RC_OK;
}

/* PCS signal detect to GPIO SD mapping  */
/* Note the map functionality needs to be enabled through GPIO ALT mode */
static vtss_rc lan966x_gpio_sd_map_set(vtss_state_t *vtss_state)
{
#if defined(GCB_GPIO_SD_DEV_MAP)
    vtss_port_no_t      port_no;
    vtss_gpio_sd_map_t *sd_map;
    ;
    u32 port;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        sd_map = &vtss_state->port.map[port_no].sd_gpio_map;
        if (!sd_map->enable) {
            continue;
        }
        port = vtss_state->port.map[port_no].chip_port;
        if (sd_map->sfp_sd > 5) {
            VTSS_E("SD index %d not supported", sd_map->sfp_sd);
            return VTSS_RC_ERROR;
        }
        REG_WR(GCB_GPIO_SD_DEV_MAP(sd_map->sfp_sd), port);
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_mdio_conf_set(vtss_state_t                 *vtss_state,
                                    u8                            ctrl_id,
                                    const vtss_mdio_conf_t *const conf)
{
    return VTSS_RC_ERROR;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc lan966x_debug_misc(vtss_state_t                  *vtss_state,
                                  lmu_ss_t                      *ss,
                                  const vtss_debug_info_t *const info)
{
#if defined(GCB_GPIO_OUT_SET2)
    pr("%-34s  31    24.23    16.15     8.7      0\n", "GPIO 0-31");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_INTR_ENA), "GPIO_INTR_ENA");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_OE), "GPIO_OE");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_OUT), "GPIO_OUT");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_IN), "GPIO_IN");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT(0)), "GPIO_ALT(0)");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT(1)), "GPIO_ALT(1)");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT(2)), "GPIO_ALT(2)");
    pr("\n");

    pr("%-34s  63    56.55    48.47    40.39    32\n", "GPIO 32-63");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_INTR_ENA1), "GPIO_INTR_ENA1");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_OE1), "GPIO_OE1");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_OUT1), "GPIO_OUT1");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_IN1), "GPIO_IN1");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT1(0)), "GPIO_ALT1(0)");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT1(1)), "GPIO_ALT1(1)");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT1(2)), "GPIO_ALT1(2)");
    pr("\n");

    pr("%-34s  95    88.87    80.79    72.71    64\n", "GPIO 64-77");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_INTR_ENA2), "GPIO_INTR_ENA2");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_OE2), "GPIO_OE2");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_OUT2), "GPIO_OUT2");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_IN2), "GPIO_IN2");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT2(0)), "GPIO_ALT2(0)");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT2(1)), "GPIO_ALT2(1)");
    vtss_lan966x_debug_reg(vtss_state, ss, REG_ADDR(GCB_GPIO_ALT2(2)), "GPIO_ALT2(2)");
    pr("\n");
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_misc_debug_print(vtss_state_t                  *vtss_state,
                                      lmu_ss_t                      *ss,
                                      const vtss_debug_info_t *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_MISC, lan966x_debug_misc, vtss_state, ss, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_misc_poll_1sec(vtss_state_t *vtss_state)
{
#if defined(VTSS_FEATURE_STORM_POLICER_DROP_COUNTER)
    u32 i, value;
    for (i = 0; i < 3; ++i) { /* If any storm policer has counted since last
                                 time then the storm event is set active */
        REG_RD(QSYS_STORMLIM_STAT(i), &value);
        if (vtss_state->qos.storm_policer_drop_counter[i] != value) {
            vtss_state->qos.storm = TRUE;
        }
        vtss_state->qos.storm_policer_drop_counter[i] = value;
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_misc_poll_1sec(vtss_state_t *vtss_state)
{
    /* Poll function groups */
    return vtss_lan966x_init_groups(vtss_state, VTSS_INIT_CMD_POLL);
}

vtss_rc vtss_lan966x_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    switch (cmd) {
    case VTSS_INIT_CMD_CREATE: break;

    case VTSS_INIT_CMD_POLL: VTSS_RC(lan966x_misc_poll_1sec(vtss_state)); break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(lan966x_sgpio_sd_map_set(vtss_state));
        VTSS_RC(lan966x_gpio_sd_map_set(vtss_state));
        break;
    default: break;
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
