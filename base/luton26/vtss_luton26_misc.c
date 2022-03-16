// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_luton26_cil.h"

#if defined(VTSS_ARCH_LUTON26)

/* - CIL functions ------------------------------------------------- */

#ifdef VTSS_FEATURE_IRQ_CONTROL

#define LU26_IRQ_EXT0          (0)
#define LU26_IRQ_EXT1          (1)
#define LU26_IRQ_SW0           (2)
#define LU26_IRQ_SW1           (3)
#define LU26_IRQ_PI_SD0        (4)
#define LU26_IRQ_PI_SD1        (5)
#define LU26_IRQ_UART          (6)
#define LU26_IRQ_TIMER0        (7)
#define LU26_IRQ_TIMER1        (8)
#define LU26_IRQ_TIMER2        (9)
#define LU26_IRQ_FDMA          (10)
#define LU26_IRQ_TWI           (11)
#define LU26_IRQ_GPIO          (12)
#define LU26_IRQ_SGPIO         (13)
#define LU26_IRQ_DEV_ALL       (14)
#define LU26_IRQ_BLK_ANA       (15)
#define LU26_IRQ_XTR_RDY0      (16)
#define LU26_IRQ_XTR_RDY1      (17)
#define LU26_IRQ_XTR_RDY2      (18)
#define LU26_IRQ_XTR_RDY3      (19)
#define LU26_IRQ_INJ_RDY0      (20)
#define LU26_IRQ_INJ_RDY1      (21)
#define LU26_IRQ_INJ_RDY2      (22)
#define LU26_IRQ_INJ_RDY3      (23)
#define LU26_IRQ_INJ_RDY4      (24)
#define LU26_IRQ_INTEGRITY     (25)
#define LU26_IRQ_PTP_SYNC      (26)
#define LU26_IRQ_MIIM0_INTR    (27)
#define LU26_IRQ_MIIM1_INTR    (28)

#define LU26_IRQ_DEST_CPU0      0 /* IRQ destination CPU0 */
#define LU26_IRQ_DEST_CPU1      1 /* IRQ destination CPU1 */
#define LU26_IRQ_DEST_EXT0      2 /* IRQ destination EXT0 */
#define LU26_IRQ_DEST_EXT1      3 /* IRQ destination EXT1 */

#define IRQ_DEST(conf) ((u32) ((conf->external ? LU26_IRQ_DEST_EXT0 : LU26_IRQ_DEST_CPU0) + conf->destination))

static void lu26_misc_owner_mask_update(vtss_state_t *vtss_state, u32 destination, u32 mask)
{
    if (destination == LU26_IRQ_DEST_CPU1) {
        vtss_state->misc.irq_user_space_owned_mask |= mask;
    } else {
        vtss_state->misc.irq_user_space_owned_mask &= ~mask;
    }
}

static vtss_rc lu26_misc_irq_cfg(vtss_state_t *vtss_state,
                                const vtss_irq_t irq,
                                const vtss_irq_conf_t *const conf)
{
    vtss_rc rc = VTSS_RC_OK;
    if (conf->destination > 1) {
        rc = VTSS_RC_ERROR;
    } else {
        u32 destination = IRQ_DEST(conf);
        switch (irq) {
            case VTSS_IRQ_XTR:
                lu26_misc_owner_mask_update(vtss_state, destination, VTSS_BIT(LU26_IRQ_XTR_RDY0) | VTSS_BIT(LU26_IRQ_XTR_RDY1) | VTSS_BIT(LU26_IRQ_XTR_RDY2) | VTSS_BIT(LU26_IRQ_XTR_RDY3));
                L26_WRM(VTSS_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG, 
                        VTSS_F_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG_XTR_RDY0_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG_XTR_RDY0_INTR_SEL);
                L26_WRM(VTSS_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG, 
                        VTSS_F_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG_XTR_RDY1_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG_XTR_RDY1_INTR_SEL);
                L26_WRM(VTSS_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG, 
                        VTSS_F_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG_XTR_RDY2_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG_XTR_RDY2_INTR_SEL);
                L26_WRM(VTSS_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG, 
                        VTSS_F_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG_XTR_RDY3_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG_XTR_RDY3_INTR_SEL);
                break;

            case VTSS_IRQ_EXT0:
                lu26_misc_owner_mask_update(vtss_state, destination, VTSS_BIT(LU26_IRQ_EXT0));
                L26_WRM(VTSS_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG,
                        VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_SEL);
                break;

            case VTSS_IRQ_EXT1:
                lu26_misc_owner_mask_update(vtss_state, destination, VTSS_BIT(LU26_IRQ_EXT1));
                L26_WRM(VTSS_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG,
                        VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_SEL);
                break;

            case VTSS_IRQ_FDMA_XTR:     /* NB: XTR and INJ are lumped together */
                lu26_misc_owner_mask_update(vtss_state, destination, VTSS_BIT(LU26_IRQ_FDMA));
                L26_WRM(VTSS_ICPU_CFG_INTR_FDMA_INTR_CFG,
                        VTSS_F_ICPU_CFG_INTR_FDMA_INTR_CFG_FDMA_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_FDMA_INTR_CFG_FDMA_INTR_SEL);
                break;

            case VTSS_IRQ_SOFTWARE:
                lu26_misc_owner_mask_update(vtss_state, destination, VTSS_BIT(LU26_IRQ_SW0) | VTSS_BIT(LU26_IRQ_SW1));
                L26_WRM(VTSS_ICPU_CFG_INTR_SW0_INTR_CFG,
                        VTSS_F_ICPU_CFG_INTR_SW0_INTR_CFG_SW0_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_SW0_INTR_CFG_SW0_INTR_SEL);
                L26_WRM(VTSS_ICPU_CFG_INTR_SW1_INTR_CFG,
                        VTSS_F_ICPU_CFG_INTR_SW1_INTR_CFG_SW1_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_SW1_INTR_CFG_SW1_INTR_SEL);
                break;

            case VTSS_IRQ_PTP_SYNC:
                lu26_misc_owner_mask_update(vtss_state, destination, VTSS_BIT(LU26_IRQ_PTP_SYNC));
                L26_WRM(VTSS_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG,
                        VTSS_F_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG_PTP_SYNC_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG_PTP_SYNC_INTR_SEL);
                break;
            case VTSS_IRQ_SGPIO:
                lu26_misc_owner_mask_update(vtss_state, destination, VTSS_BIT(LU26_IRQ_SGPIO));
                L26_WRM(VTSS_ICPU_CFG_INTR_SGPIO_INTR_CFG,
                        VTSS_F_ICPU_CFG_INTR_SGPIO_INTR_CFG_SGPIO_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_SGPIO_INTR_CFG_SGPIO_INTR_SEL);
                break;
            case VTSS_IRQ_DEV_ALL:
                lu26_misc_owner_mask_update(vtss_state, destination, VTSS_BIT(LU26_IRQ_DEV_ALL));
                L26_WRM(VTSS_ICPU_CFG_INTR_DEV_ALL_INTR_CFG,
                        VTSS_F_ICPU_CFG_INTR_DEV_ALL_INTR_CFG_DEV_ALL_INTR_SEL(destination),
                        VTSS_M_ICPU_CFG_INTR_DEV_ALL_INTR_CFG_DEV_ALL_INTR_SEL);
                L26_WRM(VTSS_ICPU_CFG_INTR_DEV_ENA,
                        0xfff,0xfff);
                L26_WRM(VTSS_ICPU_CFG_INTR_DEV_POL,
                        0xfff,0xfff);
                L26_WRM(VTSS_ICPU_CFG_INTR_DEV_IDENT_STICKY,
                        0xfff,0xfff);
                break;
            default:
                rc = VTSS_RC_ERROR;
        }
    }
    return rc;
}

static vtss_rc lu26_misc_irq_status(vtss_state_t *vtss_state, vtss_irq_status_t *status)
{
    u32 val, uio_irqs;
    
    VTSS_MEMSET(status, 0, sizeof(*status));

    // Which interrupts are taken care of in user-space?
    uio_irqs = vtss_state->misc.irq_user_space_owned_mask;

    // Who's interrupting?
    L26_RD(VTSS_ICPU_CFG_INTR_INTR, &val);

    // Only consider UIO interrupts
    val &= uio_irqs;

    status->raw_ident = val;
    L26_RD(VTSS_ICPU_CFG_INTR_INTR_RAW, &status->raw_status);
    L26_RD(VTSS_ICPU_CFG_INTR_INTR_ENA, &status->raw_mask);
    L26_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_CLR, val);
    status->raw_status &= uio_irqs;
    status->raw_mask   &= uio_irqs;

    if (val & (VTSS_BIT(LU26_IRQ_XTR_RDY0)|VTSS_BIT(LU26_IRQ_XTR_RDY1)|VTSS_BIT(LU26_IRQ_XTR_RDY2)|VTSS_BIT(LU26_IRQ_XTR_RDY3))) {
        status->active |= VTSS_BIT(VTSS_IRQ_XTR);
    }

    if (val & VTSS_BIT(LU26_IRQ_FDMA)) {
        status->active |= VTSS_BIT(VTSS_IRQ_FDMA_XTR);
    }

    if (val & VTSS_BIT(LU26_IRQ_EXT0)) {
        status->active |= VTSS_BIT(VTSS_IRQ_EXT0);
    }

    if (val & VTSS_BIT(LU26_IRQ_EXT1)) {
        status->active |= VTSS_BIT(VTSS_IRQ_EXT1);
    }

    if (val & (VTSS_BIT(LU26_IRQ_SW0)|VTSS_BIT(LU26_IRQ_SW1))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SOFTWARE);
    }

    if (val & (VTSS_BIT(LU26_IRQ_PTP_SYNC))) {
        status->active |= VTSS_BIT(VTSS_IRQ_PTP_SYNC);
    }

    if (val & (VTSS_BIT(LU26_IRQ_SGPIO))) {
        status->active |= VTSS_BIT(VTSS_IRQ_SGPIO);
    }

    if (val & (VTSS_BIT(LU26_IRQ_DEV_ALL))) {
        status->active |= VTSS_BIT(VTSS_IRQ_DEV_ALL);
    }

    return VTSS_RC_OK;
}

static vtss_rc lu26_misc_irq_enable(vtss_state_t *vtss_state,
                                   const vtss_irq_t irq,
                                   const BOOL enable)
{
    u32 mask;
    VTSS_D("irq:%d, enable:%d", irq, enable);
    switch (irq) {
    case VTSS_IRQ_XTR:
        mask = VTSS_BIT(LU26_IRQ_XTR_RDY0)|VTSS_BIT(LU26_IRQ_XTR_RDY1)|VTSS_BIT(LU26_IRQ_XTR_RDY2)|VTSS_BIT(LU26_IRQ_XTR_RDY3);
        break;

    case VTSS_IRQ_EXT0:
        mask = VTSS_BIT(LU26_IRQ_EXT0);
        break;

    case VTSS_IRQ_EXT1:
        mask = VTSS_BIT(LU26_IRQ_EXT1);
        break;

    case VTSS_IRQ_FDMA_XTR:
        mask = VTSS_BIT(LU26_IRQ_FDMA);
        break;
    case VTSS_IRQ_SOFTWARE:
        mask = VTSS_BIT(LU26_IRQ_SW0)|VTSS_BIT(LU26_IRQ_SW1);
        break;
    case VTSS_IRQ_PTP_SYNC:
        mask = VTSS_BIT(LU26_IRQ_PTP_SYNC);
        break;

    case VTSS_IRQ_SGPIO:
        mask = VTSS_BIT(LU26_IRQ_SGPIO);
        break;
    case VTSS_IRQ_DEV_ALL:
        mask = VTSS_BIT(LU26_IRQ_DEV_ALL);
        break;
    default:
        return VTSS_RC_ERROR;
    }
    /* Ack sticky bits */
    L26_WR(VTSS_ICPU_CFG_INTR_INTR, mask);
    
    if(enable) {
        VTSS_D("irq:%d, enable:%d, mask:0x%X", irq, enable, mask);
        L26_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_SET, mask);
    } else {
        L26_WR(VTSS_ICPU_CFG_INTR_INTR_ENA_CLR, mask);
    }

    return VTSS_RC_OK;
}

#endif    /* VTSS_FEATURE_IRQ_CONTROL */ 

static vtss_rc l26_reg_read(vtss_state_t *vtss_state,
                            const vtss_chip_no_t chip_no, const u32 addr, u32 * const value)
{
    return vtss_l26_rd(vtss_state, addr, value);
}

static vtss_rc l26_reg_write(vtss_state_t *vtss_state,
                             const vtss_chip_no_t chip_no, const u32 addr, const u32 value)
{
    return vtss_l26_wr(vtss_state, addr, value);
}

vtss_rc vtss_l26_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id)
{
    u32 value;
    
    L26_RD(VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID, &value);
    
    if (value == 0 || value == 0xffffffff) {
        VTSS_E("CPU interface error, chipid: 0x%08x", value);
        return VTSS_RC_ERROR;
    }
    
    chip_id->part_number = VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID(value);
    chip_id->revision = VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID(value);
    
    return VTSS_RC_OK;
}


static vtss_rc l26_ptp_event_poll(vtss_state_t *vtss_state, vtss_ptp_event_type_t *ev_mask)
{
    u32 sticky, mask;
    
    /* PTP events */
    *ev_mask = 0;
    L26_RD(VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT, &sticky);
    L26_WR(VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT, sticky);
    L26_RD(VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG, &mask);
    mask |= VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_CLK_ADJ_UPD_STICKY; /* CLK ADJ event has no enable bit - do not generate interrupt */
    sticky &= mask;      /* Only handle enabled sources */

    *ev_mask |= (sticky & VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_SYNC_STAT) ? VTSS_PTP_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_EXT_SYNC_CURRENT_TIME_STICKY) ? VTSS_PTP_EXT_SYNC_EV : 0;
    *ev_mask |= (sticky & VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_CLK_ADJ_UPD_STICKY) ? VTSS_PTP_CLK_ADJ_EV : 0;
    VTSS_I("sticky: 0x%x, ev_mask 0x%x", sticky, *ev_mask);

    return VTSS_RC_OK;
}

static vtss_rc l26_ptp_event_enable(vtss_state_t *vtss_state,
                                    vtss_ptp_event_type_t ev_mask, BOOL enable)
{
    
    /* PTP masks */
    
    if (ev_mask & VTSS_PTP_SYNC_EV) {
        L26_WRM(VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG, 
            enable ? VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_SYNC_STAT_ENA : 0, 
            VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_SYNC_STAT_ENA);
    }
    if (ev_mask & VTSS_PTP_EXT_SYNC_EV) {
        L26_WRM(VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG, 
            enable ? VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_EXT_SYNC_CURRENT_TIME_ENA : 0, 
            VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_EXT_SYNC_CURRENT_TIME_ENA);
    }
    return VTSS_RC_OK;
}


// Function for setup interrupt
// In: intr_mask - The interrupt bit mask bit.
//     polarity  - The interrupt polarity.
//     enable    - Set to enable the interrupts        
static vtss_rc l26_intr_cfg(vtss_state_t *vtss_state, 
                            const u32                intr_mask,
                            const BOOL               polarity,
                            const BOOL               enable)
{
    u32 intr_bit;
    
    // Loop through the whole interrupt vector and setup the bits in the mask.
    for (intr_bit = 0; intr_bit < 32; intr_bit++) {
        // If the bit is set in the mask then setup interrupt
        if (intr_mask & (1 << intr_bit)) {
            
            // Setup interrupt polarity.
            L26_WRM(VTSS_ICPU_CFG_INTR_DEV_POL, polarity << intr_bit, 1 << intr_bit);
                
            // Enable / Disable the interrupt
            if (vtss_state->misc.chip_id.revision == 0x1 && intr_bit == 28) {
                // Bug in Rev. B (bugzilla#3995) PHY interrupt is stocked to 0, and should not be enabled.
                L26_WRM(VTSS_ICPU_CFG_INTR_DEV_ENA, 0, 1 << 28);
            } else {
                L26_WRM(VTSS_ICPU_CFG_INTR_DEV_ENA, enable << intr_bit, 1 << intr_bit);
                VTSS_D("enable:%d - 0x%X, intr_bit:%d, mask:0x%X, polarity:%d", enable, enable << intr_bit, intr_bit, intr_mask, polarity);
            }
        }
    }
    return VTSS_RC_OK;
}


static vtss_rc l26_intr_pol_negation(vtss_state_t *vtss_state)
{
    u32 ident, polarity;
    
    L26_RD(VTSS_ICPU_CFG_INTR_DEV_IDENT, &ident);           /* Get active interrupt indications on Fast Link Fail */
    ident &= 0xFFF;

    L26_RD(VTSS_ICPU_CFG_INTR_DEV_POL, &polarity);          /* Get polarity and negate the active ones */
    L26_WR(VTSS_ICPU_CFG_INTR_DEV_POL, polarity ^ ident );

    return VTSS_RC_OK;
}

static vtss_rc l26_dev_all_event_poll(vtss_state_t *vtss_state,
                                       vtss_dev_all_event_poll_t poll_type,
                                       vtss_dev_all_event_type_t  *ev_mask)
{
    u32 ident=0, chip_port;
    vtss_port_no_t api_port;

    /* Read the active interrupt sources (the product of sticky & enable) */
    L26_RD(VTSS_ICPU_CFG_INTR_DEV_IDENT, &ident);
    VTSS_I("ident: 0x%x", ident);

    for (api_port = VTSS_PORT_NO_START; api_port < vtss_state->port_count; api_port++) {
        ev_mask[api_port] = 0;
        chip_port = VTSS_CHIP_PORT(api_port);
        if (ident & (1 << chip_port)) {
            ev_mask[api_port] = VTSS_DEV_ALL_LINK_EV;
        }
    }

    /*
       There's a chip issue that DEV_ALL_INTR is asserted recursively when link state is up on RevB/RevC,
       so we must negate the active ones via setting polarity.
    */
    if (ident) {
        l26_intr_pol_negation(vtss_state);
    }

    /* Clear the icpu_dev sticky */
    L26_WR(VTSS_ICPU_CFG_INTR_DEV_IDENT_STICKY, ident);

    return VTSS_RC_OK;
}

static vtss_rc l26_dev_all_event_enable(vtss_state_t *vtss_state,
                                         vtss_port_no_t port_no, vtss_dev_all_event_type_t ev_mask, BOOL enable)
{
    u32 chip_port = VTSS_CHIP_PORT(port_no), mask = VTSS_BIT(chip_port), dev_intr = chip_port;

    if (!(ev_mask & VTSS_DEV_ALL_LINK_EV)) {
        VTSS_D("DEV event supported: 0x%x", ev_mask);
        return VTSS_RC_ERROR;
    }

    /* Enable/disable ICPU device interrupt */
    L26_WRM(VTSS_ICPU_CFG_INTR_DEV_ENA, VTSS_ENCODE_BITFIELD(enable,dev_intr,1), mask);

    /* Clear ICPU sticky bit */
    L26_WR(VTSS_ICPU_CFG_INTR_DEV_IDENT_STICKY, mask);

    return VTSS_RC_OK;
}

/* =================================================================
 *  Miscellaneous - GPIO
 * =================================================================*/

vtss_rc vtss_l26_gpio_mode(vtss_state_t           *vtss_state,
                           const vtss_chip_no_t   chip_no,
                           const vtss_gpio_no_t   gpio_no,
                           const vtss_gpio_mode_t mode)
{
    u32 mask = VTSS_BIT(gpio_no);
    L26_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, mask); /* Disable IRQ */
    switch(mode) {
    case VTSS_GPIO_OUT:
    case VTSS_GPIO_IN:
    case VTSS_GPIO_IN_INT:
        L26_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(0), mask); /* GPIO mode 0b00 */
        L26_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(1), mask); /* -"- */
        L26_WRM(VTSS_DEVCPU_GCB_GPIO_GPIO_OE, mode == VTSS_GPIO_OUT ? mask : 0, mask);
        if(mode == VTSS_GPIO_IN_INT)
            L26_WRM_SET(VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA, mask);
        return VTSS_RC_OK;
    case VTSS_GPIO_ALT_0:
        L26_WRM_SET(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(0), mask); /* GPIO mode 0b01 */
        L26_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(1), mask); /* -"- */
        return VTSS_RC_OK;
    case VTSS_GPIO_ALT_1:
        L26_WRM_CLR(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(0), mask); /* GPIO mode 0b10 */
        L26_WRM_SET(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(1), mask); /* -"- */
        return VTSS_RC_OK;
    default:
        break;
    }
    return VTSS_RC_ERROR;
}

static vtss_rc l26_gpio_read(vtss_state_t          *vtss_state,
                             const vtss_chip_no_t  chip_no,
                             const vtss_gpio_no_t  gpio_no,
                             BOOL                  *const value)
{
    u32 val,  mask = VTSS_BIT(gpio_no);
    L26_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_IN, &val);
    *value = VTSS_BOOL(val & mask);
    return VTSS_RC_OK;
}

static vtss_rc l26_gpio_write(vtss_state_t          *vtss_state,
                              const vtss_chip_no_t  chip_no,
                              const vtss_gpio_no_t  gpio_no, 
                              const BOOL            value)
{
    u32 mask = VTSS_BIT(gpio_no);
    if(value) {
        L26_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_SET, mask);
    } else {
        L26_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_CLR, mask);
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_sgpio_event_poll(vtss_state_t             *vtss_state, 
                                    const vtss_chip_no_t     chip_no,
                                    const vtss_sgpio_group_t group,
                                    const u32                bit,
                                    BOOL                     *const events)
{
    u32 i, val = 0;

    L26_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INT_REG(bit), &val);
    L26_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INT_REG(bit), val);     /* Clear pending */

    /* Setup serial IO port enable register */
    for (i=0; i<32; i++) {
        events[i] = (val & 1<<i) ? TRUE : FALSE;
    }

    return VTSS_RC_OK;
}


static vtss_rc l26_sgpio_event_enable(vtss_state_t             *vtss_state,
                                      const vtss_chip_no_t     chip_no,
                                      const vtss_sgpio_group_t group,
                                      const u32                port,
                                      const u32                bit,
                                      const BOOL               enable)
{
    u32 data, pol, i;

    if (enable) {
        L26_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INPUT_DATA(bit), &data);
        L26_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INT_POL(bit), &pol);
        pol = ~pol;     /* '0' means interrupt when input is one */
        data &= pol;    /* Now data '1' means active interrupt */
        if (!(data & 1<<port))    /* Only enable if not active interrupt - as interrupt pending cannot be cleared */
            L26_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_INT_ENA, 1<<port, 1<<port);
        L26_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG, VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA(1<<bit), VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA(1<<bit));
    }
    else {
        L26_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_INT_ENA, 0, 1<<port);
        for (i=0; i<32; ++i)
            if (vtss_state->misc.sgpio_event_enabled[0][group].enable[i][bit])      break;
        if (i == 32)
            L26_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG, 0, VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA(1<<bit));
    }

    return VTSS_RC_OK;
}

static vtss_rc l26_sgpio_conf_set(vtss_state_t             *vtss_state,
                                  const vtss_chip_no_t     chip_no,
                                  const vtss_sgpio_group_t group,
                                  const vtss_sgpio_conf_t  *const conf)
{
    u32 i, port, val = 0, bmode[2], bit_idx;

    /* Setup serial IO port enable register */
    for (port = 0; port < 32; port++) {
        if (conf->port_conf[port].enabled)
            val |= VTSS_BIT(port);
    }
    L26_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_ENABLE, val);

    /* 
     * Setup general configuration register
     *
     * The burst gap is 0x0(1.05ms)
     * The load signal is active low
     * The auto burst repeat function is on
     * The SIO reverse output is off
     */
    for (i = 0; i < 2; i++) {
        switch (conf->bmode[i]) {
        case VTSS_SGPIO_BMODE_TOGGLE:
            if (i == 0) {
                VTSS_E("blink mode 0 does not support TOGGLE");
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

    /* Configure "LD" polarity signal to 0 (active low) for input SGPIO */
    val = (VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_0(bmode[0]) |
           VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_1(bmode[1]) |
           VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP(0x0) |
           VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_PORT_WIDTH(conf->bit_count - 1) |
           VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_AUTO_REPEAT);
    L26_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG, val, ~VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA);

    /* Setup the serial IO clock frequency - 12.5MHz (0x14) */
    L26_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK, 0x14);

    /*
     * Configuration of output data values
     * The placement of the source select bits for each output bit in the register:
     * Output bit0 : (2 downto 0)
     * Output bit1 : (5 downto 3)
     * Output bit2 : (8 downto 6)
     * Output bit3 : (11 downto 9)
    */
    for (port = 0; port < 32; port++) {
        for (val = 0, bit_idx = 0; bit_idx < 4; bit_idx++) {
            /* Set output bit n */
            val |= VTSS_ENCODE_BITFIELD(conf->port_conf[port].mode[bit_idx], (bit_idx * 3), 3);
        }
        L26_WR(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG(port), val);
    }

    return VTSS_RC_OK;
}

static vtss_rc l26_sgpio_read(vtss_state_t             *vtss_state,
                              const vtss_chip_no_t     chip_no,
                              const vtss_sgpio_group_t group,
                              vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS])
{
    u32 i, port, value;

    for (i = 0; i < 4; i++) {
        L26_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INPUT_DATA(i), &value);
        for (port = 0; port < 32; port++) {
            data[port].value[i] = VTSS_BOOL(value & (1 << port));
        }
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_EEE)
/* =================================================================
 *  EEE - Energy Efficient Ethernet
 * =================================================================*/

/*
 * Set EEE configuration
 *
 * In :  port_no - The port number for which to set new configuration.
 *       conf    - New configuration for the port
 *
 * Return : VTSS_RC_OK if configuration done else error code.
 */
static vtss_rc l26_eee_port_conf_set(vtss_state_t *vtss_state,
                                     const vtss_port_no_t              port_no,
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

    if ((vtss_state->misc.chip_id.revision == 1) && (chip_port < 12) && (chip_port < VTSS_PORT_ARRAY_SIZE) && (vtss_state->eee.ena[port_no] != conf->eee_ena)) {
        vtss_state->eee.ena[port_no] = conf->eee_ena; // On RevB the Fast Link Fail signal interrupt from internal PHY (12 ports) must be disabled when EEE is enabled
        VTSS_N("conf->eee_ena:%d", conf->eee_ena);
        VTSS_RC(l26_intr_cfg(vtss_state, (0x01 << chip_port), 0, !conf->eee_ena));
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

        } else if ((vtss_state->port.conf[port_no].flow_control.obey || vtss_state->port.conf[port_no].flow_control.generate) &&
                   (vtss_state->misc.chip_id.revision == 0 ||  vtss_state->misc.chip_id.revision == 1)) {
            // For chip revision A and B Flow control and EEE doesn't work together.
            VTSS_D("EEE disabled due to bugzilla#4235, port:%d", chip_port);
        } else {
            eee_cfg_reg |= VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_ENA;
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

    eee_cfg_reg |= VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_TIMER_WAKEUP(closest_match_index);

    
    // Set the latency depending upon what the user prefer (power saving vs. low traffic latency)
    if (conf->optimized_for_power) {
        eee_timer_age = 82; // Set timer age to 263 mSec.
    } else {
        eee_timer_age = 0x23; // Set timer age to 48 uSec.
    }

    // EEE holdoff timer
    eee_cfg_reg |= VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_TIMER_HOLDOFF(0x5) | VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_TIMER_AGE(eee_timer_age);

    // EEE fast queues
    eee_cfg_reg |= VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES(conf->eee_fast_queues);

    // Registers write
    L26_WR(VTSS_SYS_SYSTEM_EEE_CFG(chip_port), eee_cfg_reg);

    VTSS_I("chip_port:%u, eee_cfg_reg = 0x%X, conf->tx_tw = %d, eee_timer_age:%d", chip_port, eee_cfg_reg, conf->tx_tw, eee_timer_age);

    // Setting Buffer size to 12.2 Kbyte & 255 frames.
    L26_WR(VTSS_SYS_SYSTEM_EEE_THRES, 0xFFFF);

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_EEE */

/* =================================================================
 * FAN speed control
* =================================================================*/
#if defined(VTSS_FEATURE_FAN) 

/*
 * Initialise FAN controller 
 *
 * In :  spec  - Fan specifications
 *
 */
static vtss_rc l26_fan_controller_init(vtss_state_t *vtss_state,
                                       const vtss_fan_conf_t * const spec)
{
    // Set GPIO alternate functions. PWM is bit 29.
    (void) vtss_l26_gpio_mode(vtss_state, 0, 29, VTSS_GPIO_ALT_0);

    // Set PWM frequency 
    L26_WRM(VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG,
           VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_FREQ(spec->fan_pwm_freq),
           VTSS_M_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_FREQ);

    // Set PWM polarity 
    L26_WRM(VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG,
           spec->fan_low_pol ? VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_INV_POL : 0,
           VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_INV_POL);

    // Set PWM open collector 
    L26_WRM(VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG,
           spec->fan_open_col ? VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_INV_POL : 0,
           VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_OPEN_COL_ENA);
           
    // Set fan speed measurement
    if (spec->type == VTSS_FAN_3_WIRE_TYPE) {
        // Enable gating for 3-wire fan types.
        L26_WRM(VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG,
               1,
               VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_GATE_ENA);
    } else {
        //  For 4-wire fan types we need to disable gating (2-wire types doesn't matter)
        L26_WRM(VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG,
                0,
                VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_GATE_ENA);
    }


    // Set GPIO alternate functions. ROTA is bit 4.
    (void) vtss_l26_gpio_mode(vtss_state, 0, 4, VTSS_GPIO_ALT_0);
 
    return VTSS_RC_OK;
}

/*
 * Set FAN cooling level
 *
 * In :  lvl - New fan cooling level, 0 = Fan is OFF, 0xFF = Fan constant ON.
 *
 * return : VTSS_RC_OK when configuration done else error code.
 */
static vtss_rc l26_fan_cool_lvl_set(vtss_state_t *vtss_state, u8 lvl)
{
    // Set PWM duty cycle (fan speed) 
    L26_WRM(VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG,
           VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE(lvl),
           VTSS_M_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE);

    return VTSS_RC_OK;
}

/*
 * Get FAN cooling level
 *
 * Return : Fan cooling level, 0 = Fan is OFF, 0xFF = Fan constant ON.
 *
 */

static vtss_rc l26_fan_cool_lvl_get(vtss_state_t *vtss_state, u8 *duty_cycle)
{
    u32 fan_cfg_reg;

    // Read the register 
    L26_RD(VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG,&fan_cfg_reg);

    // Get PWM duty cycle
    *duty_cycle = VTSS_X_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE(fan_cfg_reg);
    
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
static vtss_rc l26_fan_rotation(vtss_state_t *vtss_state, BOOL update, u32 *value) {
    static u32 last_cnt = 0, one_sec_cnt = 0;
    u32  cnt = 0;
    
    if (update) { 
        L26_RD(VTSS_DEVCPU_GCB_FAN_STAT_FAN_CNT, &cnt);
        one_sec_cnt = cnt - last_cnt;
        VTSS_I("one_sec_cnt:%d, last_cnt:%d, cnt:%d", one_sec_cnt, last_cnt, cnt);
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
static vtss_rc l26_fan_rotation_get(vtss_state_t *vtss_state,
                                    vtss_fan_conf_t *fan_spec, u32 *rotation_count)
{
    return l26_fan_rotation(vtss_state, FALSE, rotation_count);
}

/*
 * Help function for keeping track of the fan rotation speed. Must be called every one second.
 *
 * Return : VTSS_OK if count was updated correctly.
 *
 */
static vtss_rc l26_fan_rotation_update(vtss_state_t *vtss_state)
{
    return l26_fan_rotation(vtss_state, TRUE, NULL);
}

#endif /* VTSS_FEATURE_FAN */

/* - Debug print --------------------------------------------------- */

static void l26_debug_tgt(const vtss_debug_printf_t pr, const char *name, u32 to)
{
    u32 tgt = ((to >> 16) & 0x3f);
    pr("%-10s  0x%02x (%u)\n", name, tgt, tgt);
}

#define L26_DEBUG_TGT(pr, name) l26_debug_tgt(pr, #name, VTSS_TO_##name)
#define L26_DEBUG_GPIO(pr, addr, name) vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_GPIO_GPIO_##addr, "GPIO_"name)
#define L26_DEBUG_SIO(pr, addr, name) vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_SIO_CTRL_SIO_##addr, "SIO_"name)
#define L26_DEBUG_SIO_INST(pr, addr, i, name) vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_DEVCPU_GCB_SIO_CTRL_SIO_##addr, i, "SIO_"name)
#define L26_DEBUG_REG_NAME(pr, tgt, addr, name) \
    vtss_l26_debug_reg(vtss_state, pr, VTSS_##tgt##_##addr, name)

static vtss_rc l26_debug_misc(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32  port, i;
    char buf[32];
    
    pr("Name        Target\n");
    L26_DEBUG_TGT(pr, DEVCPU_ORG);
    L26_DEBUG_TGT(pr, SYS);
    L26_DEBUG_TGT(pr, ANA);
    L26_DEBUG_TGT(pr, REW);
    L26_DEBUG_TGT(pr, ES0);
    L26_DEBUG_TGT(pr, S1);
    L26_DEBUG_TGT(pr, S2);
    L26_DEBUG_TGT(pr, DEVCPU_GCB);
    L26_DEBUG_TGT(pr, DEVCPU_QS);
    L26_DEBUG_TGT(pr, DEVCPU_PI);
    L26_DEBUG_TGT(pr, MACRO_CTRL);
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "DEV_%u", port);
        l26_debug_tgt(pr, buf, VTSS_TO_DEV(port));
    }
    pr("\n");

    vtss_l26_debug_reg_header(pr, "GPIOs");
    L26_DEBUG_GPIO(pr, OUT, "OUT");
    L26_DEBUG_GPIO(pr, IN, "IN");
    L26_DEBUG_GPIO(pr, OE, "OE");
    L26_DEBUG_GPIO(pr, INTR, "INTR");
    L26_DEBUG_GPIO(pr, INTR_ENA, "INTR_ENA");
    L26_DEBUG_GPIO(pr, INTR_IDENT, "INTR_IDENT");
    L26_DEBUG_GPIO(pr, ALT(0), "ALT_0");
    L26_DEBUG_GPIO(pr, ALT(1), "ALT_1");
    pr("\n");
    
    vtss_l26_debug_reg_header(pr, "SGPIO");
    for (i = 0; i < 4; i++)
        L26_DEBUG_SIO_INST(pr, INPUT_DATA(i), i, "INPUT_DATA");
    for (i = 0; i < 4; i++)
        L26_DEBUG_SIO_INST(pr, INT_POL(i), i, "INT_POL");
    L26_DEBUG_SIO(pr, PORT_INT_ENA, "PORT_INT_ENA");
    for (i = 0; i < 32; i++)
        L26_DEBUG_SIO_INST(pr, PORT_CONFIG(i), i, "PORT_CONFIG");
    L26_DEBUG_SIO(pr, PORT_ENABLE, "PORT_ENABLE");
    L26_DEBUG_SIO(pr, CONFIG, "CONFIG");
    L26_DEBUG_SIO(pr, CLOCK, "CLOCK");
    for (i = 0; i < 4; i++)
        L26_DEBUG_SIO_INST(pr, INT_REG(i), i, "INT_REG");
    pr("\n");
    
    vtss_l26_debug_reg_header(pr, "IRQs");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR, "INTR_IDENT");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_RAW, "INTR_RAW");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, INTR_ENA, "INTR_ENA");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, ICPU_IRQ0_ENA,   "ICPU_IRQ0_ENA");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, ICPU_IRQ1_ENA,   "ICPU_IRQ1_ENA");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, ICPU_IRQ0_IDENT, "ICPU_IRQ0_IDENT");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, ICPU_IRQ1_IDENT, "ICPU_IRQ1_IDENT");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, EXT_IRQ0_ENA,   "EXT_IRQ0_ENA");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, EXT_IRQ1_ENA,   "EXT_IRQ1_ENA");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, EXT_IRQ0_IDENT, "EXT_IRQ0_IDENT");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, EXT_IRQ1_IDENT, "EXT_IRQ1_IDENT");

    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, XTR_RDY0_INTR_CFG, "XTR_RDY0_INTR_CFG");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, XTR_RDY1_INTR_CFG, "XTR_RDY1_INTR_CFG");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, XTR_RDY2_INTR_CFG, "XTR_RDY2_INTR_CFG");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, XTR_RDY3_INTR_CFG, "XTR_RDY3_INTR_CFG");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, FDMA_INTR_CFG, "FDMA_INTR_CFG");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, SW0_INTR_CFG, "SW0_INTR_CFG");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, SW1_INTR_CFG, "SW1_INTR_CFG");
    L26_DEBUG_REG_NAME(pr, ICPU_CFG_INTR, PTP_SYNC_INTR_CFG, "PTP_SYNC_INTR_CFG");

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_misc_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_MISC, l26_debug_misc, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc l26_misc_poll_1sec(vtss_state_t *vtss_state)
{
    u32 port, bit, enable, rc=VTSS_RC_OK;

    L26_RD(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_INT_ENA, &enable);
    for (port=0; port<32; ++port)
        if (!(enable & 1<<port))
            for (bit=0; bit<4; ++bit)    /* port is not enabled - check if it is configured to be */
                if (vtss_state->misc.sgpio_event_enabled[0][0].enable[port][bit]) {
                    rc = l26_sgpio_event_enable(vtss_state, 0, 0, port, bit, TRUE);  /* this port,bit is configured to be enabled - try and enable */
                }

    VTSS_RC(l26_fan_rotation_update(vtss_state));
    return rc;
}

static vtss_rc l26_poll_1sec(vtss_state_t *vtss_state)
{
    /* Poll function groups */
    return vtss_l26_init_groups(vtss_state, VTSS_INIT_CMD_POLL);
}


vtss_rc vtss_l26_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_misc_state_t *state = &vtss_state->misc;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->reg_read = l26_reg_read;
        state->reg_write = l26_reg_write;
        state->chip_id_get = vtss_l26_chip_id_get;
        state->poll_1sec = l26_poll_1sec;
        state->gpio_mode = vtss_l26_gpio_mode;
        state->gpio_read = l26_gpio_read;
        state->gpio_write = l26_gpio_write;
        state->sgpio_conf_set = l26_sgpio_conf_set;
        state->sgpio_read = l26_sgpio_read;
        state->sgpio_event_enable = l26_sgpio_event_enable;
        state->sgpio_event_poll = l26_sgpio_event_poll;
        state->ptp_event_poll = l26_ptp_event_poll;
        state->ptp_event_enable = l26_ptp_event_enable;
        state->dev_all_event_poll = l26_dev_all_event_poll;
        state->dev_all_event_enable = l26_dev_all_event_enable;
        state->intr_cfg = l26_intr_cfg;
        state->intr_pol_negation = l26_intr_pol_negation;

#if defined(VTSS_FEATURE_EEE)
    /* EEE */
        vtss_state->eee.port_conf_set = l26_eee_port_conf_set;
#endif    
        vtss_state->fan.controller_init = l26_fan_controller_init;
        vtss_state->fan.cool_lvl_get    = l26_fan_cool_lvl_get;
        vtss_state->fan.cool_lvl_set    = l26_fan_cool_lvl_set;
        vtss_state->fan.rotation_get    = l26_fan_rotation_get;
#ifdef VTSS_FEATURE_IRQ_CONTROL
        vtss_state->misc.irq_cfg = lu26_misc_irq_cfg;
        vtss_state->misc.irq_status = lu26_misc_irq_status;
        vtss_state->misc.irq_enable = lu26_misc_irq_enable;
#endif  /* VTSS_FEATURE_IRQ_CONTROL */

        /* State data */
        state->gpio_count = L26_GPIOS;
        state->sgpio_group_count = L26_SGPIO_GROUPS;
        break;
    case VTSS_INIT_CMD_INIT:
        break;
    case VTSS_INIT_CMD_POLL:
        VTSS_RC(l26_misc_poll_1sec(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LUTON26 */
