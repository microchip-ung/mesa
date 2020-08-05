// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

/* =================================================================
 *  EEE - Energy Efficient Ethernet
 * =================================================================*/

#if defined(VTSS_FEATURE_EEE)
static vtss_rc lan966x_eee_port_conf_set(vtss_state_t *vtss_state,
                                         const vtss_port_no_t       port_no,
                                         const vtss_eee_port_conf_t *const conf)
{
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_FAN)
static vtss_rc lan966x_fan_controller_init(vtss_state_t *vtss_state,
                                           const vtss_fan_conf_t *const spec)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_fan_cool_lvl_set(vtss_state_t *vtss_state, u8 lvl)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_fan_cool_lvl_get(vtss_state_t *vtss_state, u8 *duty_cycle)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_fan_rotation_get(vtss_state_t *vtss_state,
                                        vtss_fan_conf_t *fan_spec, u32 *rotation_count)
{
    return VTSS_RC_OK;
}
#endif

/* ================================================================= *
 *  Miscellaneous
 * ================================================================= */

static vtss_rc lan966x_reg_read(vtss_state_t *vtss_state,
                                const vtss_chip_no_t chip_no, const u32 addr, u32 * const value)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_reg_write(vtss_state_t *vtss_state,
                                 const vtss_chip_no_t chip_no, const u32 addr, const u32 value)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ptp_event_poll(vtss_state_t *vtss_state, vtss_ptp_event_type_t *ev_mask)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ptp_event_enable(vtss_state_t *vtss_state,
                                        vtss_ptp_event_type_t ev_mask, BOOL enable)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_dev_all_event_poll(vtss_state_t *vtss_state,
                                          vtss_dev_all_event_poll_t poll_type,
                                          vtss_dev_all_event_type_t  *ev_mask)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_dev_all_event_enable(vtss_state_t *vtss_state,
                                            vtss_port_no_t port_no, vtss_dev_all_event_type_t ev_mask, BOOL enable)
{
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_INTERRUPTS)
static vtss_rc lan966x_intr_cfg(vtss_state_t *vtss_state,
                                const u32  intr_mask, const BOOL polarity, const BOOL enable)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_intr_pol_negation(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_IRQ_CONTROL)
static vtss_rc lan966x_misc_irq_cfg(vtss_state_t *vtss_state,
                                    const vtss_irq_t irq,
                                    const vtss_irq_conf_t *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_misc_irq_status(vtss_state_t *vtss_state, vtss_irq_status_t *status)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_misc_irq_enable(vtss_state_t *vtss_state,
                                       const vtss_irq_t irq,
                                       const BOOL enable)
{
    return VTSS_RC_OK;
}
#endif

/* =================================================================
 *  Miscellaneous - GPIO
 * =================================================================*/

vtss_rc vtss_lan966x_gpio_mode(vtss_state_t *vtss_state,
                               const vtss_chip_no_t   chip_no,
                               const vtss_gpio_no_t   gpio_no,
                               const vtss_gpio_mode_t mode)
{

#if defined(GCB_GPIO_OUT_SET2)
    u32 mask = VTSS_BIT(gpio_no % 32), alt_0 = 0, alt_1 = 0;

    switch (mode) {
    case VTSS_GPIO_OUT:
    case VTSS_GPIO_IN:
    case VTSS_GPIO_IN_INT:
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
    if (gpio_no < 32) {
        REG_WRM_CLR(GCB_GPIO_INTR_ENA, mask);
        REG_WRM_CTL(GCB_GPIO_OE, mode == VTSS_GPIO_OUT, mask);
        REG_WRM(GCB_GPIO_ALT(0), alt_0, mask);
        REG_WRM(GCB_GPIO_ALT(1), alt_1, mask);
        if (mode == VTSS_GPIO_IN_INT) {
            REG_WRM_SET(GCB_GPIO_INTR_ENA, mask);
        }
    } else if (gpio_no < 64) {
        REG_WRM_CLR(GCB_GPIO_INTR_ENA1, mask);
        REG_WRM_CTL(GCB_GPIO_OE1, mode == VTSS_GPIO_OUT, mask);
        REG_WRM(GCB_GPIO_ALT1(0), alt_0, mask);
        REG_WRM(GCB_GPIO_ALT1(1), alt_1, mask);
        if (mode == VTSS_GPIO_IN_INT) {
            REG_WRM_SET(GCB_GPIO_INTR_ENA1, mask);
        }
    } else {
        REG_WRM_CLR(GCB_GPIO_INTR_ENA2, mask);
        REG_WRM_CTL(GCB_GPIO_OE2, mode == VTSS_GPIO_OUT, mask);
        REG_WRM(GCB_GPIO_ALT2(0), alt_0, mask);
        REG_WRM(GCB_GPIO_ALT2(1), alt_1, mask);
        if (mode == VTSS_GPIO_IN_INT) {
            REG_WRM_SET(GCB_GPIO_INTR_ENA2, mask);
        }
    }
#endif
    return VTSS_RC_OK;
}

static vtss_rc lan966x_gpio_read(vtss_state_t *vtss_state,
                                 const vtss_chip_no_t  chip_no,
                                 const vtss_gpio_no_t  gpio_no,
                                 BOOL                  *const value)
{
#if defined(GCB_GPIO_IN2)
    u32 val, mask = VTSS_BIT(gpio_no % 32);

    if (gpio_no < 32) {
        REG_RD(GCB_GPIO_IN, &val);
    } else if (gpio_no < 64) {
        REG_RD(GCB_GPIO_IN1, &val);
    } else {
        REG_RD(GCB_GPIO_IN2, &val);
    }
    *value = VTSS_BOOL(val & mask);
#endif
    return VTSS_RC_OK;
}

static vtss_rc lan966x_gpio_write(vtss_state_t *vtss_state,
                                  const vtss_chip_no_t  chip_no,
                                  const vtss_gpio_no_t  gpio_no,
                                  const BOOL            value)
{
#if defined(GCB_GPIO_OUT_SET2)
    u32 mask = VTSS_BIT(gpio_no % 32);

    if (gpio_no < 32) {
        if (value) {
            REG_WR(GCB_GPIO_OUT_SET, mask);
        } else {
            REG_WR(GCB_GPIO_OUT_CLR, mask);
        }
    } else if (gpio_no < 64) {
        if (value) {
            REG_WR(GCB_GPIO_OUT_SET1, mask);
        } else {
            REG_WR(GCB_GPIO_OUT_CLR1, mask);
        }
    } else {
        if (value) {
            REG_WR(GCB_GPIO_OUT_SET2, mask);
        } else {
            REG_WR(GCB_GPIO_OUT_CLR2, mask);
        }
    }
#endif
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SERIAL_GPIO)
static vtss_rc lan966x_sgpio_event_poll(vtss_state_t *vtss_state,
                                        const vtss_chip_no_t     chip_no,
                                        const vtss_sgpio_group_t group,
                                        const u32                bit,
                                        BOOL                     *const events)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_sgpio_event_enable(vtss_state_t *vtss_state,
                                          const vtss_chip_no_t     chip_no,
                                          const vtss_sgpio_group_t group,
                                          const u32                port,
                                          const u32                bit,
                                          const BOOL               enable)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_sgpio_conf_set(vtss_state_t *vtss_state,
                                      const vtss_chip_no_t     chip_no,
                                      const vtss_sgpio_group_t group,
                                      const vtss_sgpio_conf_t  *const conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_sgpio_read(vtss_state_t *vtss_state,
                                  const vtss_chip_no_t     chip_no,
                                  const vtss_sgpio_group_t group,
                                  vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS])
{
    return VTSS_RC_OK;
}
#endif

/* - Debug print --------------------------------------------------- */

vtss_rc vtss_lan966x_misc_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_misc_poll_1sec(vtss_state_t *vtss_state)
{
#if defined(VTSS_FEATURE_STORM_POLICER_DROP_COUNTER)
    u32 i, value;
    for (i = 0; i < 3; ++i) {   /* If any storm policer has counted since last time then the storm event is set active */
        REG_RD(QSYS_STORMLIM_STAT(i), &value);
        if (vtss_state->qos.storm_policer_drop_counter[i] != value) {
            vtss_state->qos.storm = TRUE;
        }
        vtss_state->qos.storm_policer_drop_counter[i] = value;
    }
#endif
    return VTSS_RC_OK;
}

static vtss_rc lan966x_poll_1sec(vtss_state_t *vtss_state)
{
    /* Poll function groups */
    return vtss_lan966x_init_groups(vtss_state, VTSS_INIT_CMD_POLL);
}

vtss_rc vtss_lan966x_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_misc_state_t *state = &vtss_state->misc;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->reg_read = lan966x_reg_read;
        state->reg_write = lan966x_reg_write;
        state->chip_id_get = lan966x_chip_id_get;
        state->poll_1sec = lan966x_poll_1sec;
        state->gpio_mode = vtss_lan966x_gpio_mode;
        state->gpio_read = lan966x_gpio_read;
        state->gpio_write = lan966x_gpio_write;
#if defined(VTSS_FEATURE_SERIAL_GPIO)
        state->sgpio_conf_set = lan966x_sgpio_conf_set;
        state->sgpio_read = lan966x_sgpio_read;
        state->sgpio_event_enable = lan966x_sgpio_event_enable;
        state->sgpio_event_poll = lan966x_sgpio_event_poll;
        state->sgpio_group_count = LAN966X_SGPIO_GROUPS;
#endif
        //TBD: state->gpio_count = LAN966X_GPIOS;
        state->dev_all_event_poll = lan966x_dev_all_event_poll;
        state->dev_all_event_enable = lan966x_dev_all_event_enable;
#if defined(VTSS_FEATURE_INTERRUPTS)
        state->intr_cfg = lan966x_intr_cfg;
        state->intr_pol_negation = lan966x_intr_pol_negation;
#endif
        state->ptp_event_poll = lan966x_ptp_event_poll;
        state->ptp_event_enable = lan966x_ptp_event_enable;
#if defined(VTSS_FEATURE_IRQ_CONTROL)
        state->irq_cfg = lan966x_misc_irq_cfg;
        state->irq_status = lan966x_misc_irq_status;
        state->irq_enable = lan966x_misc_irq_enable;
#endif
#if defined(VTSS_FEATURE_EEE)
        vtss_state->eee.port_conf_set = lan966x_eee_port_conf_set;
#endif
#if defined(VTSS_FEATURE_FAN)
        vtss_state->fan.controller_init = lan966x_fan_controller_init;
        vtss_state->fan.cool_lvl_get = lan966x_fan_cool_lvl_get;
        vtss_state->fan.cool_lvl_set = lan966x_fan_cool_lvl_set;
        vtss_state->fan.rotation_get = lan966x_fan_rotation_get;
#endif
        state->gpio_count = VTSS_GPIOS;
        break;

    case VTSS_INIT_CMD_POLL:
        VTSS_RC(lan966x_misc_poll_1sec(vtss_state));
        break;

    default:
        break;
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
