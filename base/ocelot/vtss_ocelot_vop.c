// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_OAM
#include "vtss_ocelot_cil.h"

#if defined(VTSS_ARCH_OCELOT)

#if defined(VTSS_FEATURE_VOP)

#if defined(VTSS_ARCH_JAGUAR_2_B)
/* system clock is 4,0 ns (250 MHz) and LOC_BASE_TICK_CNT is default 50, i.e. 200 ns */
#define LOC_BASE 200 /* ns */
#elif defined(VTSS_ARCH_JAGUAR_2_C)
/* system clock is 4,0 ns (250 MHz) and LOC_BASE_TICK_CNT is default 25, i.e. 100 ns */
#define LOC_BASE 100 /* ns */
#elif defined(VTSS_ARCH_SERVAL_T)
/* system clock is 6,4 ns (156,25 MHz) and LOC_BASE_TICK_CNT is default 25, i.e. 160 ns */
#define LOC_BASE 160 /* ns */
#endif

#define GENERIC_MASK_LAPS     0x01
#define GENERIC_OFFSET_LAPS   0

/* Counter clear feature mask's */
#define VTSS_OAM_CNT_CCM      (1<<0)
#define VTSS_OAM_CNT_LM       (1<<1)
#define VTSS_OAM_CNT_LB       (1<<2)
#define VTSS_OAM_CNT_TST      (1<<3)
#define VTSS_OAM_CNT_VOE      (1<<4)
#define VTSS_OAM_CNT_DM       (1<<5)
#define VTSS_OAM_CNT_SL       (1<<6)
#define VTSS_OAM_CNT_ALL      (VTSS_BITMASK(6))

/* Counter clear direction mask's */
#define VTSS_OAM_CNT_DIR_TX    (1<<31)
#define VTSS_OAM_CNT_DIR_RX    (1<<30)
#define VTSS_OAM_CNT_DIR_BOTH  (VTSS_OAM_CNT_DIR_TX | VTSS_OAM_CNT_DIR_RX)



/* - Helper functions ------------------------------------------------- */
/* - Helper functions ------------------------------------------------- */
/* - Helper functions ------------------------------------------------- */
/* - Helper functions ------------------------------------------------- */

static vtss_rc doing_calculate(vtss_state_t *vtss_state,  u32 voe_idx,  BOOL *doing_lb,  BOOL *doing_tst)
{
    u32 v;
    BOOL lb_hw_enabled, tst_hw_enabled;

    SRVL_RD(VTSS_OAM_MEP_VOE_OAM_HW_CTRL(voe_idx), &v);
    lb_hw_enabled = (v & (VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LBM_ENA | VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LBR_ENA)) != 0;
    SRVL_RD(VTSS_OAM_MEP_VOE_OAM_FWD_CTRL(voe_idx), &v);
    tst_hw_enabled = (VTSS_X_OAM_MEP_VOE_OAM_FWD_CTRL_GENERIC_FWD_MASK(v) & (1<<6)) != 0;

    *doing_lb  = lb_hw_enabled && !tst_hw_enabled;
    *doing_tst = lb_hw_enabled &&  tst_hw_enabled;

    return(VTSS_RC_OK);
}

static u32 cc_loc_period_index(vtss_voe_ccm_period_t p)
{
    switch (p) {
    case VTSS_VOE_CCM_PERIOD_3_3_MS:
        return 0;
    case VTSS_VOE_CCM_PERIOD_10_MS:
        return 1;
    case VTSS_VOE_CCM_PERIOD_100_MS:
        return 2;
    case VTSS_VOE_CCM_PERIOD_1_SEC:
        return 3;
    }
    VTSS_D("Invalid period for CC");
    return 0;
}

static u32 lm_loc_period_index(vtss_voe_ccm_period_t p)
{
    switch (p) {
    case VTSS_VOE_CCM_PERIOD_3_3_MS:
    case VTSS_VOE_CCM_PERIOD_10_MS:
        VTSS_D("Invalid period for LM");
        return 5;
    case VTSS_VOE_CCM_PERIOD_100_MS:
        return 5;
    case VTSS_VOE_CCM_PERIOD_1_SEC:
        return 6;
    }
    VTSS_D("Invalid period for LM");
    return 5;
}

static u32 loc_period_value(vtss_voe_ccm_period_t p)
{
    switch (p) {
    case VTSS_VOE_CCM_PERIOD_3_3_MS:
        return 1;
    case VTSS_VOE_CCM_PERIOD_10_MS:
        return 2;
    case VTSS_VOE_CCM_PERIOD_100_MS:
        return 3;
    case VTSS_VOE_CCM_PERIOD_1_SEC:
        return 4;
    }
    VTSS_D("Invalid period for CC");
    return 0;
}

static vtss_rc voe_counter_update(vtss_state_t         *vtss_state,
                                  const vtss_voe_idx_t  voe_idx,
                                  const u32             clear_mask)
{
/*
 * These macros will aid in reading and optionally clearing counter registers.
 * The clear operation will be triggered by matching the 'clear_mask' with both a
 * counter type (ctype) and a counter direction (cdir - TX or RX).
 */
#define CHIPREAD(reg, cnt, ctype, cdir) { SRVL_RD(reg, &v); vtss_cmn_counter_32_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }
#define UPDATE8(v, cnt, ctype, cdir)    { vtss_cmn_counter_8_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }
#define UPDATE16(v, cnt, ctype, cdir)   { vtss_cmn_counter_16_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }

    vtss_rc     rc = VTSS_RC_OK;
    u32         v;
    BOOL        doing_lb = 0, doing_tst = 0;
    vtss_oam_voe_internal_counters_t *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    /* CCM counter update */
    CHIPREAD(VTSS_OAM_MEP_VOE_CCM_RX_VLD_FC_CNT(voe_idx),   &chipcnt->ccm.rx_valid_counter,   VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_OAM_MEP_VOE_CCM_RX_INVLD_FC_CNT(voe_idx), &chipcnt->ccm.rx_invalid_counter, VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_OAM_MEP_VOE_CCM_TX_SEQ_CFG(voe_idx),      &chipcnt->ccm.tx_counter,         VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_TX);

    /* CCM sequence number error counter is a one bit sticky. We need to read a sticky bit and internally accumulate the value. */
    SRVL_RD(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), &v);
    SRVL_WR(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY);
    v = (v & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY) ? 1 : 0;
    vtss_cmn_counter_32_update(v + chipcnt->ccm.rx_oo_counter.prev, &chipcnt->ccm.rx_oo_counter, (clear_mask & VTSS_OAM_CNT_CCM) != 0);

    /* LB counter update */
    VTSS_RC(doing_calculate(vtss_state, voe_idx, &doing_lb, &doing_tst));
    if (doing_lb || (clear_mask & VTSS_OAM_CNT_LB)) {
        CHIPREAD(VTSS_OAM_MEP_VOE_LBR_RX_FRM_CNT(voe_idx),         &chipcnt->lb.rx_lbr_counter,      VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_OAM_MEP_VOE_LBM_TX_TRANSID_CFG(voe_idx),     &chipcnt->lb.tx_lbm_counter,      VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_TX);

        /* LBR sequence number error counter is a one bit sticky. We need to read a sticky bit and internally accumulate the value. */
        SRVL_RD(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), &v);
        SRVL_WR(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY);
        v = (v & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY) ? 1 : 0;
        vtss_cmn_counter_32_update(v + chipcnt->lb.rx_lbr_oo_counter.prev, &chipcnt->lb.rx_lbr_oo_counter, (clear_mask & VTSS_OAM_CNT_LB) != 0);
    }

    /* VOE counter update */
    CHIPREAD(VTSS_OAM_MEP_VOE_RX_SEL_OAM_CNT(voe_idx), &chipcnt->voe.rx_selected_counter,  VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_OAM_MEP_VOE_TX_SEL_OAM_CNT(voe_idx), &chipcnt->voe.tx_selected_counter,  VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_TX);
    CHIPREAD(VTSS_OAM_MEP_VOE_RX_OAM_FRM_CNT(voe_idx), &chipcnt->voe.rx_counter,           VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_OAM_MEP_VOE_TX_OAM_FRM_CNT(voe_idx), &chipcnt->voe.tx_counter,           VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_TX);

    return rc;
#undef CHIPREAD
#undef UPDATE8
#undef UPDATE16
}

static vtss_rc srvl_oam_vop_int_enable(vtss_state_t *vtss_state, BOOL enable)
{
    SRVL_WRM(VTSS_OAM_MEP_COMMON_MASTER_INTR_CTRL, (enable ? VTSS_F_OAM_MEP_COMMON_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA : 0), VTSS_F_OAM_MEP_COMMON_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA);

    return VTSS_RC_OK;
}

/* Determine VOP interrupt flag -- clear if no enabled VOEs have interrupts enabled */
static vtss_rc oam_vop_int_update(vtss_state_t *vtss_state)
{
    u32 i;
    u32 must_enable;

    for (i = 0, must_enable = 0; !must_enable && i < VTSS_VOE_CNT; ++i) {
        if (vtss_state->oam.voe_alloc_data[i].allocated) {
            SRVL_RD(VTSS_OAM_MEP_VOE_INTR_ENA(i), &must_enable);
            must_enable &= 0x7ff;  /* Only bits 0-10 are valid */
        }
    }

    return srvl_oam_vop_int_enable(vtss_state, must_enable ? TRUE : FALSE);
}

static vtss_rc voe_default_set(vtss_state_t          *vtss_state,
                               const vtss_voe_idx_t  voe_idx);

/* - CIL functions ------------------------------------------------- */
/* - CIL functions ------------------------------------------------- */
/* - CIL functions ------------------------------------------------- */
/* - CIL functions ------------------------------------------------- */

static vtss_rc srvl_vop_conf_set(vtss_state_t            *vtss_state,
                                 const vtss_vop_conf_t   *const conf)
{
    BOOL  npi = vtss_state->packet.npi_conf.enable ? TRUE : FALSE;
    u32   value, npi_port = 0;

    VTSS_D("Enter");

    /* Multicast MAC configuration */
    value = (conf->multicast_dmac.addr[0] << 8) | conf->multicast_dmac.addr[1];
    SRVL_WR(VTSS_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_MSB, VTSS_F_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB(value));

    value = (conf->multicast_dmac.addr[2] << 24) | (conf->multicast_dmac.addr[3] << 16) |
            (conf->multicast_dmac.addr[4] <<  8) | (conf->multicast_dmac.addr[5]);
    value >>= 4;   /* Value in reg. field doesn't include the lower 4 bits */
    SRVL_WR(VTSS_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_LSB, VTSS_F_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB(value));

    /* CPU extraction queue configuration */
    if (vtss_state->packet.npi_conf.port_no != VTSS_PORT_NO_NONE) {
        npi_port = VTSS_CHIP_PORT(vtss_state->packet.npi_conf.port_no);
    }
    value = (npi ? VTSS_F_OAM_MEP_COMMON_CPU_CFG_DEF_EXT_PORT_ENA : 0) | VTSS_F_OAM_MEP_COMMON_CPU_CFG_DEF_COPY_QU(npi ? npi_port : conf->voe_queue_ccm)    |
            (npi ? VTSS_F_OAM_MEP_COMMON_CPU_CFG_CPU_ERR_EXT_PORT_ENA : 0) | VTSS_F_OAM_MEP_COMMON_CPU_CFG_CPU_ERR_QU(npi ? npi_port : conf->voe_queue_err) |
            (npi ? VTSS_F_OAM_MEP_COMMON_CPU_CFG_LBR_EXT_PORT_ENA : 0) | VTSS_F_OAM_MEP_COMMON_CPU_CFG_LBR_CPU_QU(npi ? npi_port : conf->voe_queue_lbr)     |
            (npi ? VTSS_F_OAM_MEP_COMMON_CPU_CFG_CCM_LM_EXT_PORT_ENA : 0) | VTSS_F_OAM_MEP_COMMON_CPU_CFG_CCM_LM_CPU_QU(npi ? npi_port : conf->voe_queue_ccm);
    SRVL_WR(VTSS_OAM_MEP_COMMON_CPU_CFG, value);

    value = (npi ? VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LT_EXT_PORT_ENA : 0) | VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LT_CPU_QU(npi ? npi_port : conf->voe_queue_lt)    |
            (npi ? VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LBM_EXT_PORT_ENA : 0) | VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LBM_CPU_QU(npi ? npi_port : conf->voe_queue_lbm) |
            (npi ? VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_CCM_EXT_PORT_ENA : 0) | VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_CCM_CPU_QU(npi ? npi_port : conf->voe_queue_ccm);
    SRVL_WR(VTSS_OAM_MEP_COMMON_CPU_CFG_1, value);

    /* Generic [GENERIC_OFFSET_LAPS] is used for LAPS */
    value = (npi ? VTSS_F_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_EXT_PORT_ENA : 0) | VTSS_F_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU(npi ? npi_port : conf->voe_queue_aps)  |
            VTSS_F_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL(39);      /* LAPS opcode is 39 */
    SRVL_WR(VTSS_OAM_MEP_COMMON_OAM_GENERIC_CFG(GENERIC_OFFSET_LAPS), value);

    /* Enable VOP */
    value = VTSS_F_OAM_MEP_COMMON_MEP_CTRL_MEP_ENA | VTSS_F_OAM_MEP_COMMON_MEP_CTRL_CCM_SCAN_ENA |
            VTSS_F_OAM_MEP_COMMON_MEP_CTRL_EXT_CPU_PORTMASK(npi ? (0x01 << npi_port) : 0);
    SRVL_WR(VTSS_OAM_MEP_COMMON_MEP_CTRL, value);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_event_active_get(vtss_state_t   *vtss_state,
                                         const u32      active_size,
                                         u32            *const active)
{
    VTSS_D("Enter  active_size %u", active_size);

    u32 i, v;

    VTSS_MEMSET(active, 0, sizeof(active_size));
    SRVL_RD(VTSS_OAM_MEP_COMMON_MASTER_INTR_CTRL, &v);
    if ((VTSS_F_OAM_MEP_COMMON_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA & v) == 0) {
        VTSS_D("No interrupts are enabled");
        return VTSS_RC_OK;
    }

    /* just scan all VOEs: */
    for (i = 0; (i < active_size) && (i < VTSS_EVENT_MASK_ARRAY_SIZE); ++i) {
        SRVL_RD(VTSS_OAM_MEP_COMMON_INTR(i), &active[i]);
    }

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_event_mask_set(vtss_state_t          *vtss_state,
                                       const vtss_voe_idx_t  voe_idx,
                                       const u32             mask,
                                       const BOOL            enable)
{
    u32 enable_mask, reg_mask;

    VTSS_D("Enter  voe_idx %u  mask %u  enable %u", voe_idx, mask, enable);

    /* Read the interrupt enable mask */
    SRVL_RD(VTSS_OAM_MEP_VOE_INTR_ENA(voe_idx), &enable_mask);

    /* Translate the input mask to register mask */
    reg_mask = ((mask & VTSS_VOE_EVENT_MASK_CCM_PERIOD)      ? VTSS_F_OAM_MEP_VOE_STICKY_CCM_PERIOD_STICKY      : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_PRIORITY)    ? VTSS_F_OAM_MEP_VOE_STICKY_CCM_PRIO_STICKY        : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD) ? VTSS_F_OAM_MEP_VOE_STICKY_CCM_ZERO_PERIOD_STICKY : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_RX_RDI)      ? VTSS_F_OAM_MEP_VOE_STICKY_CCM_RX_RDI_STICKY      : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_LOC)         ? VTSS_F_OAM_MEP_VOE_STICKY_CCM_LOC_STICKY         : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_MEP_ID)      ? VTSS_F_OAM_MEP_VOE_STICKY_CCM_MEPID_STICKY       : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_MEG_ID)      ? VTSS_F_OAM_MEP_VOE_STICKY_CCM_MEGID_STICKY       : 0);

    /* Calculate new enable mask */
    enable_mask = enable ? (enable_mask | reg_mask) : (enable_mask & ~reg_mask);

    /* Write back the interrupt enable mask */
    SRVL_WR(VTSS_OAM_MEP_VOE_INTR_ENA(voe_idx), enable_mask);

    return enable_mask ? srvl_oam_vop_int_enable(vtss_state, TRUE) : oam_vop_int_update(vtss_state);
}

static vtss_rc srvl_voe_event_get(vtss_state_t          *vtss_state,
                                  const vtss_voe_idx_t  voe_idx,
                                  u32                   *const mask)
{
    u32 enable_mask, sticky_mask;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Read the interrupt enable mask */
    SRVL_RD(VTSS_OAM_MEP_VOE_INTR_ENA(voe_idx), &enable_mask);

    /* Read sticky bits and clear the enabled ones */
    SRVL_RD(VTSS_OAM_MEP_VOE_STICKY(voe_idx), &sticky_mask);
    sticky_mask &= enable_mask;
    SRVL_WR(VTSS_OAM_MEP_VOE_STICKY(voe_idx), sticky_mask); /* Sticky bits cleared by writing 1 to them */

    /* Translate sticky mask to returned event mask */
    *mask = (((sticky_mask & VTSS_F_OAM_MEP_VOE_STICKY_CCM_PERIOD_STICKY) != 0)      ? VTSS_VOE_EVENT_MASK_CCM_PERIOD      : 0) |
            (((sticky_mask & VTSS_F_OAM_MEP_VOE_STICKY_CCM_PRIO_STICKY) != 0)        ? VTSS_VOE_EVENT_MASK_CCM_PRIORITY    : 0) |
            (((sticky_mask & VTSS_F_OAM_MEP_VOE_STICKY_CCM_ZERO_PERIOD_STICKY) != 0) ? VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD : 0) |
            (((sticky_mask & VTSS_F_OAM_MEP_VOE_STICKY_CCM_RX_RDI_STICKY) != 0)      ? VTSS_VOE_EVENT_MASK_CCM_RX_RDI      : 0) |
            (((sticky_mask & VTSS_F_OAM_MEP_VOE_STICKY_CCM_LOC_STICKY) != 0)         ? VTSS_VOE_EVENT_MASK_CCM_LOC         : 0) |
            (((sticky_mask & VTSS_F_OAM_MEP_VOE_STICKY_CCM_MEPID_STICKY) != 0)       ? VTSS_VOE_EVENT_MASK_CCM_MEP_ID      : 0) |
            (((sticky_mask & VTSS_F_OAM_MEP_VOE_STICKY_CCM_MEGID_STICKY) != 0)       ? VTSS_VOE_EVENT_MASK_CCM_MEG_ID      : 0);

    VTSS_D("Exit  mask %X", *mask);

    return (VTSS_RC_OK);
}

static u32 voe_alloc_idx;
static vtss_rc srvl_voe_alloc(vtss_state_t                *vtss_state,
                              const vtss_voe_type_t       type,
                              const vtss_port_no_t        port,
                              const vtss_oam_direction_t  direction,
                              vtss_voe_idx_t              *const voe_idx)
{
    u32 i, offset;

    VTSS_D("Enter  type %u  port %u  direction %u", type, port, direction);

    if (type == VTSS_VOE_TYPE_SERVICE) {
        for (i = 0; i < VTSS_PATH_SERVICE_VOE_CNT && vtss_state->oam.voe_alloc_data[voe_alloc_idx].allocated; ++i) {
            voe_alloc_idx = (voe_alloc_idx + 1) % VTSS_PATH_SERVICE_VOE_CNT;
        }
        if (i == VTSS_PATH_SERVICE_VOE_CNT) {
            VTSS_E("No free Service VOE to allocate");
            return VTSS_RC_ERROR;
        }
        i = voe_alloc_idx;
    } else {
        if (direction == VTSS_OAM_DIRECTION_UP) {
            VTSS_E("Port VOE cannot be up");
            return VTSS_RC_ERROR;
        }
        i = VTSS_CHIP_PORT(port) + VTSS_PORT_VOE_BASE_IDX;
        if (i >= VTSS_VOE_CNT  ||  vtss_state->oam.voe_alloc_data[i].allocated) {
            VTSS_E("No free Port VOE to allocate");
            return VTSS_RC_ERROR;
        }
    }

    *voe_idx = i;
    vtss_state->oam.voe_alloc_data[*voe_idx].allocated = TRUE;
    vtss_state->oam.voe_alloc_data[*voe_idx].type = type;
    vtss_state->oam.voe_alloc_data[*voe_idx].port = port;
    vtss_state->oam.voe_alloc_data[*voe_idx].direction = direction;

    /* Disable VOE */
    SRVL_WRM(VTSS_OAM_MEP_VOE_BASIC_CTRL(*voe_idx), 0, VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA);

    /* Clear assorted counters: */
    SRVL_WR(VTSS_OAM_MEP_VOE_CCM_RX_VLD_FC_CNT(*voe_idx), 0);       /* Clear assorted counters */
    SRVL_WR(VTSS_OAM_MEP_VOE_CCM_RX_INVLD_FC_CNT(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_CCM_TX_SEQ_CFG(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_CCM_RX_SEQ_CFG(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_CCM_CAP_TX_FCF(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_CCM_CAP_RX_FCL(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_LBM_TX_TRANSID_CFG(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_LBR_RX_TRANSID_CFG(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_LBR_RX_FRM_CNT(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_RX_SEL_OAM_CNT(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_TX_SEL_OAM_CNT(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_RX_OAM_FRM_CNT(*voe_idx), 0);
    SRVL_WR(VTSS_OAM_MEP_VOE_TX_OAM_FRM_CNT(*voe_idx), 0);

    SRVL_WR(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(*voe_idx), 0xffffff);   /* sticky bits cleared by writing 1 to them */
    SRVL_WR(VTSS_OAM_MEP_VOE_STICKY(*voe_idx), 0xff);              /* sticky bits cleared by writing 1 to them */
    SRVL_WR(VTSS_OAM_MEP_VOE_UPMEP_LM_CNT_STICKY(*voe_idx), 0x7);  /* sticky bits cleared by writing 1 to them */
    SRVL_WR(VTSS_OAM_MEP_VOE_INTR_ENA(*voe_idx), 0);

    /* Clear LM counters */
    switch (type) {
    case VTSS_VOE_TYPE_SERVICE:
        offset = *voe_idx * VTSS_PRIO_ARRAY_SIZE;
        for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
            SRVL_WR(VTSS_OAM_MEP_RX_VOE_PM_MEP_RX_FRM_CNT(offset + i), 0);
            SRVL_WR(VTSS_OAM_MEP_TX_VOE_PM_MEP_TX_FRM_CNT(offset + i), 0);
        }
        break;
    case VTSS_VOE_TYPE_PORT:
        offset = (*voe_idx - VTSS_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE;
        for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
            SRVL_WR(VTSS_OAM_MEP_PORT_PM_PORT_RX_FRM_CNT(offset + i), 0);
            SRVL_WR(VTSS_OAM_MEP_PORT_PM_PORT_TX_FRM_CNT(offset + i), 0);
            /* TBD - the port count-all Rx/Tx counters have been left out */
        }
        break;
    }

    VTSS_D("Exit voe_idx %u", *voe_idx);

    return VTSS_RC_OK;
}

static vtss_rc srvl_voe_free(vtss_state_t          *vtss_state,
                             const vtss_voe_idx_t  voe_idx)
{
    vtss_rc           rc, ret_rc = VTSS_RC_OK;
    vtss_voe_alloc_t  *alloc_data = &vtss_state->oam.voe_alloc_data[voe_idx];

    VTSS_D("Enter  voe_idx %u", voe_idx);

    if (!alloc_data->allocated) {
        VTSS_D("VOE not allocated  voe_idx %u", voe_idx);
        return (VTSS_RC_OK);
    }
    alloc_data->allocated = FALSE;

    if (voe_idx < VTSS_PATH_SERVICE_VOE_CNT) {
        voe_alloc_idx = voe_idx;
    }

    if ((rc = voe_default_set(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = oam_vop_int_update(vtss_state)) != VTSS_RC_OK) {
        ret_rc = rc;
    }

    return (ret_rc);
}

static vtss_rc srvl_voe_conf_set(vtss_state_t           *vtss_state,
                                 const vtss_voe_idx_t   voe_idx,
                                 const vtss_voe_conf_t  *const conf)
{
    u32               value, mask;
    vtss_voe_alloc_t  *alloc_data = &vtss_state->oam.voe_alloc_data[voe_idx];

    VTSS_D("Enter  voe_idx %u", voe_idx);

    if (((voe_idx < VTSS_PORT_VOE_BASE_IDX) && (alloc_data->type == VTSS_VOE_TYPE_PORT)) ||
        ((voe_idx >= VTSS_PORT_VOE_BASE_IDX) && (alloc_data->type == VTSS_VOE_TYPE_SERVICE))) {
        VTSS_E("voe_idx %u  type %u.  VOE index and type mismatch", voe_idx, alloc_data->type);
        return VTSS_RC_ERROR;
    }

    /* Configure CCM sequence numer to increment always as we use this for CCM TX counting */
    value = VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_SEQ_INCR_ENA;
    mask = VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_SEQ_INCR_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_CCM_CFG(voe_idx), value, mask);

    /* Configure the unicast MAC */
    value = VTSS_F_OAM_MEP_VOE_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB((conf->unicast_mac.addr[0] << 8) | conf->unicast_mac.addr[1]);
    SRVL_WR(VTSS_OAM_MEP_VOE_MEP_UC_MAC_MSB(voe_idx), value);
    value = (conf->unicast_mac.addr[2] << 24) | (conf->unicast_mac.addr[3] << 16) |
        (conf->unicast_mac.addr[4] <<  8) | (conf->unicast_mac.addr[5]);
    SRVL_WR(VTSS_OAM_MEP_VOE_MEP_UC_MAC_LSB(voe_idx), value);

    /* Configure MEG level and Up-MEP port mask and Up-MEP Loop Back mode */
    value = VTSS_F_OAM_MEP_VOE_MEL_CTRL_MEL_VAL(conf->meg_level) |
            ((alloc_data->direction == VTSS_OAM_DIRECTION_UP) ? VTSS_F_OAM_MEP_VOE_MEL_CTRL_MEP_PORTMASK(1 << VTSS_CHIP_PORT(alloc_data->port)) : 0);
    mask = VTSS_M_OAM_MEP_VOE_MEL_CTRL_MEL_VAL | VTSS_M_OAM_MEP_VOE_MEL_CTRL_MEP_PORTMASK;
    SRVL_WRM(VTSS_OAM_MEP_VOE_MEL_CTRL(voe_idx), value, mask);

    /* Configure Up-MEP */
    SRVL_WR(VTSS_OAM_MEP_COMMON_VOE_CFG(voe_idx), (alloc_data->direction == VTSS_OAM_DIRECTION_UP) ? VTSS_F_OAM_MEP_COMMON_VOE_CFG_UPMEP_VOE : 0);

    /* Configure the DMAC check type */
    switch (conf->dmac_check_type) {
    case VTSS_VOE_DMAC_CHECK_NONE:
        value = VTSS_F_OAM_MEP_VOE_BASIC_CTRL_RX_DMAC_CHK_SEL(0x01);
        break;
    case VTSS_VOE_DMAC_CHECK_UNICAST:
        value = VTSS_F_OAM_MEP_VOE_BASIC_CTRL_RX_DMAC_CHK_SEL(0x01);
        break;
    case VTSS_VOE_DMAC_CHECK_MULTICAST:
        value = VTSS_F_OAM_MEP_VOE_BASIC_CTRL_RX_DMAC_CHK_SEL(0x02);
        break;
    case VTSS_VOE_DMAC_CHECK_BOTH:
        value = VTSS_F_OAM_MEP_VOE_BASIC_CTRL_RX_DMAC_CHK_SEL(0x03);
        break;
    }
    mask = VTSS_M_OAM_MEP_VOE_BASIC_CTRL_RX_DMAC_CHK_SEL;
    SRVL_WRM(VTSS_OAM_MEP_VOE_BASIC_CTRL(voe_idx), value, mask);

    /* Configure VOE looped frames to hit ES0 using ISDX */
    value = VTSS_F_OAM_MEP_VOE_LOOPBACK_CTRL_LB_ISDX(conf->loop_iflow_id);
    mask = VTSS_M_OAM_MEP_VOE_LOOPBACK_CTRL_LB_ISDX;
    SRVL_WRM(VTSS_OAM_MEP_VOE_LOOPBACK_CTRL(voe_idx), value, mask);

    if (conf->enable) {
        SRVL_RD(VTSS_OAM_MEP_VOE_BASIC_CTRL(voe_idx), &value);
        if ((VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA & value) == 0) {  /* VOE changed from disabled to enabled. */
            /* Clear the logical counters */
            VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_ALL | VTSS_OAM_CNT_DIR_BOTH));

            /* Configure no HW control */
            SRVL_WR(VTSS_OAM_MEP_VOE_OAM_HW_CTRL(voe_idx), 0);

            /* Configure no forward */
            SRVL_WR(VTSS_OAM_MEP_VOE_OAM_FWD_CTRL(voe_idx), 0);

            /* Configure no CPU copy */
            SRVL_WR(VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL(voe_idx), 0);
        }
    }

    /* Enable/Disable VOE */
    SRVL_WRM(VTSS_OAM_MEP_VOE_BASIC_CTRL(voe_idx), (conf->enable ? VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA : 0), VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_cc_conf_set(vtss_state_t              *vtss_state,
                                    const vtss_voe_idx_t      voe_idx,
                                    const vtss_voe_cc_conf_t  *const conf)
{
    u32                 i, value, mask;
    const u8            *p;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure CPU copy */
    value = (conf->enable && (conf->cpu_copy == VTSS_OAM_CPU_COPY_ALL)) ? (VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA | VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_CCM_LM_CPU_COPY_ENA) : 0;
    mask = VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA | VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_CCM_LM_CPU_COPY_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL(voe_idx), value, mask);

    /* Clear sequence numbers */
    SRVL_RD(VTSS_OAM_MEP_VOE_BASIC_CTRL(voe_idx), &value);
    if (conf->enable && ((VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA & value) == 0)) {    /* The Tx and Rx sequence numbers are cleared when CC is enabled */
        SRVL_WR(VTSS_OAM_MEP_VOE_CCM_TX_SEQ_CFG(voe_idx), 0);
        SRVL_WR(VTSS_OAM_MEP_VOE_CCM_RX_SEQ_CFG(voe_idx), 0);
        vtss_cmn_counter_32_rebase(0, &vtss_state->oam.voe_internal[voe_idx].counters.ccm.tx_counter);    /* Always re-base when Tx sequence number is changed */
    }

    /* Configure seq_no_update, prio, period */
    value = (conf->seq_no_update ? VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_SEQ_UPD_ENA : 0)  |
             VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_RX_SEQ_CHK_ENA                                                                          |
             VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_PRIO(conf->expected_priority)                                                           |
             VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_PERIOD(loc_period_value(conf->expected_period))                                         |
             VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEGID_CHK_ENA                                                                           |
             VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEPID_CHK_ENA;
    mask = VTSS_M_OAM_MEP_VOE_CCM_CFG_CCM_LM_PERIOD |
           VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_SEQ_UPD_ENA |
           VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_RX_SEQ_CHK_ENA |
           VTSS_M_OAM_MEP_VOE_CCM_CFG_CCM_PRIO |
           VTSS_M_OAM_MEP_VOE_CCM_CFG_CCM_PERIOD |
           VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEGID_CHK_ENA |
           VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEPID_CHK_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_CCM_CFG(voe_idx), value, mask);

    /* Configure MEG id */
    p = &conf->expected_megid[47];    // MSB
    for (i = 0; i < 12; ++i, p -= 4) {
        value = (*(p - 3) << 24) | (*(p - 2) << 16) | (*(p - 1) <<  8) | (*(p - 0));
        SRVL_WR(VTSS_OAM_MEP_VOE_CCM_MEGID_CFG(voe_idx, i), value);
    }

    /* Configure count_as_selected */
    value = (conf->enable && conf->count_as_selected) ? (VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA | VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_CCM_LM_OAM_CNT_ENA) : 0;
    mask = VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA | VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_CCM_LM_OAM_CNT_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL(voe_idx), value, mask);

    /* Configure peer MEP id */
    SRVL_WR(VTSS_OAM_MEP_VOE_CCM_MEPID_CFG(voe_idx), VTSS_F_OAM_MEP_VOE_CCM_MEPID_CFG_CCM_MEPID(conf->expected_peer_mepid));

    /* Enable/Disable CCM handling */
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_HW_CTRL(voe_idx), (conf->enable ? VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_CCM_ENA : 0), VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_CCM_ENA);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_cc_rdi_set(vtss_state_t          *vtss_state,
                                   const vtss_voe_idx_t  voe_idx,
                                   const BOOL            rdi)
{
    VTSS_D("Enter  voe_idx %u  rdi %u", voe_idx, rdi);

    SRVL_WRM(VTSS_OAM_MEP_VOE_CCM_CFG(voe_idx), (rdi ? VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_TX_RDI : 0), VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_TX_RDI);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_cc_cpu_copy_next_set(vtss_state_t          *vtss_state,
                                             const vtss_voe_idx_t  voe_idx)
{
    u32 value, mask;

    value = VTSS_F_OAM_MEP_VOE_BASIC_CTRL_CPU_HITME_ONCE_CCM_TLV |
            VTSS_F_OAM_MEP_VOE_BASIC_CTRL_CCM_ERR_CPU_HITME_ONCE |
            VTSS_F_OAM_MEP_VOE_BASIC_CTRL_CCM_NXT_CPU_HITME_ONCE;
    mask = value;
    SRVL_WRM(VTSS_OAM_MEP_VOE_BASIC_CTRL(voe_idx), value, mask);

    value = VTSS_F_OAM_MEP_VOE_MEL_CTRL_CPU_HITME_ONCE_CCM_MEL_TOO_LOW;
    mask = value;
    SRVL_WRM(VTSS_OAM_MEP_VOE_MEL_CTRL(voe_idx), value, mask);

    return VTSS_RC_OK;
}

static vtss_rc srvl_voe_lt_conf_set(vtss_state_t               *vtss_state,
                                    const vtss_voe_idx_t       voe_idx,
                                    const vtss_voe_lt_conf_t   *const conf)
{
    u32  value, mask;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure copy to CPU */
    value = ((conf->enable && conf->ltm_cpu_copy) ? VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA : 0) |
            ((conf->enable && conf->ltr_cpu_copy) ? VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA : 0);
    mask = VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA | VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL(voe_idx), value, mask);

    /* Configure count_as_selected */
    value = (conf->enable && conf->count_as_selected) ? (VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA |
                                                         VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA) : 0;
    mask = VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA | VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL(voe_idx), value, mask);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_lb_conf_set(vtss_state_t               *vtss_state,
                                   const vtss_voe_idx_t       voe_idx,
                                   const vtss_voe_lb_conf_t   *const conf)
{
    u32  value, mask, transaction_id;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure copy to CPU */
    value = ((conf->enable && conf->lbm_cpu_copy) ? VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA : 0) |
            ((conf->enable && conf->lbr_cpu_copy) ? VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA : 0);
    mask = VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA | VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL(voe_idx), value, mask);

    /* Configure count_as_selected */
    value = (conf->enable && conf->count_as_selected) ? (VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA |
                                                         VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA) : 0;
    mask = VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA | VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL(voe_idx), value, mask);

    /* Configure transaction id */
    value = conf->enable ? VTSS_F_OAM_MEP_VOE_LBM_TX_TRANSID_UPDATE_LBM_TRANSID_UPDATE_ENA : 0;
    SRVL_WR(VTSS_OAM_MEP_VOE_LBM_TX_TRANSID_UPDATE(voe_idx), value);
    if (conf->trans_id != VTSS_VOE_LBM_TRANSACTION_ID_NONE) {
        transaction_id = (conf->trans_id == 0) ? 1 : conf->trans_id;
        transaction_id -= 1;  /* Serval increments transaction ID before inserting into frame */
        SRVL_WR(VTSS_OAM_MEP_VOE_LBM_TX_TRANSID_CFG(voe_idx), transaction_id);
        SRVL_WR(VTSS_OAM_MEP_VOE_LBR_RX_TRANSID_CFG(voe_idx), transaction_id);
        vtss_cmn_counter_32_rebase(transaction_id, &vtss_state->oam.voe_internal[voe_idx].counters.lb.tx_lbm_counter);    /* Always re-base when transaction id is changed */
    }

    /* Enable/Disable LBM/LBR handling */
    value = conf->enable ? (VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LBM_ENA | 
                            VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LBR_ENA) : 0;
    mask = VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LBM_ENA | VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LBR_ENA;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_HW_CTRL(voe_idx), value, mask);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_laps_conf_set(vtss_state_t                 *vtss_state,
                                     const vtss_voe_idx_t         voe_idx,
                                     const vtss_voe_laps_conf_t   *const conf)
{
    u32  value, mask;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure CPU copy */
    /* Generic [GENERIC_MASK_LAPS] is used for LAPS */
    value = VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_GENERIC_COPY_MASK((conf->enable && conf->cpu_copy) ? GENERIC_MASK_LAPS : 0);
    mask = VTSS_M_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_GENERIC_COPY_MASK;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL(voe_idx), value, mask);

    /* Configure count_as_selected */
    /* Generic [GENERIC_MASK_LAPS] is used for LAPS */
    value = VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK((conf->enable && conf->count_as_selected) ? GENERIC_MASK_LAPS : 0);
    mask = VTSS_M_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK;
    SRVL_WRM(VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL(voe_idx), value, mask);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_status_get(vtss_state_t          *vtss_state,
                                   const vtss_voe_idx_t  voe_idx,
                                   vtss_voe_status_t     *const status)
{
    u32 value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    SRVL_RD(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), &value);
    status->opcode_unexp_seen  = (value & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY) != 0;
    status->dmac_unexp_seen    = (value & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_MAC_ADDR_ERR_STICKY) != 0;
    status->tx_level_low_seen  = (value & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_MEP_EGR_BLOCK_STICKY) != 0;

    /* Clear the RX sticky bits that has been detected */
    value = value &
            (VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY  |
             VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_MAC_ADDR_ERR_STICKY   |
             VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_MEP_EGR_BLOCK_STICKY);
    SRVL_WR(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), value);

    return VTSS_RC_OK;
}

static vtss_rc srvl_voe_cc_status_get(vtss_state_t          *vtss_state,
                                     const vtss_voe_idx_t  voe_idx,
                                     vtss_voe_cc_status_t  *status)
{
    u32 value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate CCM received status */
    SRVL_RD(VTSS_OAM_MEP_VOE_CCM_CFG(voe_idx), &value);
    status->zero_period     = (value & VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_ZERO_PERIOD_ERR) != 0;
    status->rdi             = (value & VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_RX_RDI)          != 0;
    status->loc             = (VTSS_X_OAM_MEP_VOE_CCM_CFG_CCM_MISS_CNT(value) == 0x07) != 0;
    status->period_unexp    = (value & VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_PERIOD_ERR)      != 0;
    status->priority_unexp  = (value & VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_PRIO_ERR)        != 0;
    status->mep_id_unexp    = (value & VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEPID_ERR)       != 0;
    status->meg_id_unexp    = (value & VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEGID_ERR)       != 0;

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    SRVL_RD(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), &value);
    status->seen           = (value & (VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_RX_STICKY | VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_LM_RX_STICKY)) != 0;

    /* Clear the sticky bits that has been detected */
    value = value &
            (VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_RX_STICKY  |
             VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_LM_RX_STICKY);
    SRVL_WR(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), value);

    return VTSS_RC_OK;
}

static vtss_rc srvl_voe_lt_status_get(vtss_state_t           *vtss_state,
                                     const vtss_voe_idx_t   voe_idx,
                                     vtss_voe_lt_status_t   *status)
{
    u32  value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    SRVL_RD(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), &value);
    status->ltm_seen  = (value & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LTM_RX_STICKY) != 0;
    status->ltr_seen  = (value & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LTR_RX_STICKY) != 0;

    /* Clear the sticky bits that has been detected */
    value = value &
            (VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LTM_RX_STICKY  |
             VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LTR_RX_STICKY);
    SRVL_WR(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), value);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_lb_status_get(vtss_state_t         *vtss_state,
                                      const vtss_voe_idx_t voe_idx,
                                      vtss_voe_lb_status_t *status)
{
    u32  value;
    BOOL doing_lb = 0, doing_tst = 0;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    SRVL_RD(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), &value);
    status->lbm_seen          = (value & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBM_RX_STICKY) != 0;
    status->lbr_seen          = (value & VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBR_RX_STICKY) != 0;

    /* Clear the sticky bits that has been detected */
    value = value &
            (VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBM_RX_STICKY           |
             VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBR_RX_STICKY);
    SRVL_WR(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), value);

    /* Get the LBM and LBR transaction id's */
    VTSS_RC(doing_calculate(vtss_state, voe_idx, &doing_lb, &doing_tst));
    if (doing_lb) {
        SRVL_RD(VTSS_OAM_MEP_VOE_LBM_TX_TRANSID_CFG(voe_idx), &status->tx_trans_id);
        status->tx_trans_id += 1;     /* Serval increments transaction ID before inserting into frame */
        SRVL_RD(VTSS_OAM_MEP_VOE_LBR_RX_TRANSID_CFG(voe_idx), &status->rx_trans_id);
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_voe_laps_status_get(vtss_state_t             *vtss_state,
                                       const vtss_voe_idx_t     voe_idx,
                                       vtss_voe_laps_status_t   *status)
{
    u32  value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    /* Generic [GENERIC_OFFSET_LAPS] is used for LAPS */
    SRVL_RD(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), &value);
    status->seen  = (VTSS_X_OAM_MEP_VOE_OAM_RX_STICKY_GENERIC_RX_STICKY_MASK(value) & GENERIC_MASK_LAPS) != 0;

    /* Clear the sticky bits that has been detected */
    value = value &
            (VTSS_M_OAM_MEP_VOE_OAM_RX_STICKY_GENERIC_RX_STICKY_MASK);
    SRVL_WR(VTSS_OAM_MEP_VOE_OAM_RX_STICKY(voe_idx), value);

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_counters_get(vtss_state_t         *vtss_state,
                                     const vtss_voe_idx_t voe_idx,
                                     vtss_voe_counters_t  *const counters)
{
    vtss_rc                           rc;
    vtss_oam_voe_internal_counters_t  *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Poll so we get the most recent counter values */
    rc = voe_counter_update(vtss_state, voe_idx, 0);

    /* Get the counters */
    counters->rx_counter          = chipcnt->voe.rx_counter.value;
    counters->tx_counter          = chipcnt->voe.tx_counter.value;
    counters->rx_selected_counter = chipcnt->voe.rx_selected_counter.value;
    counters->tx_selected_counter = chipcnt->voe.tx_selected_counter.value;

    return rc;
}

static vtss_rc srvl_voe_cc_counters_get(vtss_state_t           *vtss_state,
                                        const vtss_voe_idx_t   voe_idx,
                                        vtss_voe_cc_counters_t *counters)
{
    vtss_rc                           rc;
    vtss_oam_voe_internal_counters_t  *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Poll so we get the most recent counter values */
    rc = voe_counter_update(vtss_state, voe_idx, 0);

    /* Get the counters */
    counters->rx_valid_counter   = chipcnt->ccm.rx_valid_counter.value;
    counters->rx_invalid_counter = chipcnt->ccm.rx_invalid_counter.value;
    counters->rx_oo_counter      = chipcnt->ccm.rx_oo_counter.value;
    counters->tx_counter         = chipcnt->ccm.tx_counter.value;

    return rc;
}

static vtss_rc srvl_voe_lb_counters_get(vtss_state_t           *vtss_state,
                                        const vtss_voe_idx_t   voe_idx,
                                        vtss_voe_lb_counters_t *counters)
{
    vtss_rc                           rc;
    vtss_oam_voe_internal_counters_t  *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Poll so we get the most recent counter values */
    rc = voe_counter_update(vtss_state, voe_idx, 0);

    /* Get the counters */
    counters->rx_lbr_counter    = chipcnt->lb.rx_lbr_counter.value;
    counters->rx_lbr_oo_counter = chipcnt->lb.rx_lbr_oo_counter.value;
    counters->tx_lbm_counter    = chipcnt->lb.tx_lbm_counter.value;

    return rc;
}

static vtss_rc srvl_voe_counters_clear(vtss_state_t          *vtss_state,
                                     const vtss_voe_idx_t  voe_idx)
{
    VTSS_D("Enter  voe_idx %u", voe_idx);

    VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_VOE | VTSS_OAM_CNT_DIR_BOTH));

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_cc_counters_clear(vtss_state_t          *vtss_state,
                                        const vtss_voe_idx_t  voe_idx)
{
    VTSS_D("Enter  voe_idx %u", voe_idx);

    VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_CCM | VTSS_OAM_CNT_DIR_BOTH));

    return (VTSS_RC_OK);
}

static vtss_rc srvl_voe_lb_counters_clear(vtss_state_t          *vtss_state,
                                         const vtss_voe_idx_t  voe_idx)
{
    VTSS_D("Enter  voe_idx %u", voe_idx);

    VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_LB | VTSS_OAM_CNT_DIR_BOTH));

    return (VTSS_RC_OK);
}





/* - Debug print --------------------------------------------------- */
/* - Debug print --------------------------------------------------- */
/* - Debug print --------------------------------------------------- */
/* - Debug print --------------------------------------------------- */

// D_COM: Debug COMmon; DR_COM: Debug Read COMmon. _I for Instance. Etc.
#define D_COM(pr, name)            vtss_srvl_debug_reg(vtss_state, pr, VTSS_OAM_MEP_COMMON_##name,                    "COMMON:"#name)
#define D_COM_I(pr, name, i)       vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_OAM_MEP_COMMON_##name(i),      (i),  "COMMON:"#name)
#define D_VOE_I(pr, name, i)       vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_OAM_MEP_VOE_##name(i),         (i),  "VOE:"#name)
#define D_VOE_II(pr, name, i1, i2) vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_OAM_MEP_VOE_##name((i1),(i2)), (i2), "VOE:"#name)
#define D_PORT_PM_I(pr, name, i, k)   vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_OAM_MEP_PORT_PM_##name(i),     ((i*8)+k),  "PORT_PM:"#name)
#define D_RX_VOE_PM_I(pr, name, i, k)   vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_OAM_MEP_RX_VOE_PM_##name(i),     ((i*8)+k),  "RX_VOE_PM:"#name)
#define D_TX_VOE_PM_I(pr, name, i, k)   vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_OAM_MEP_TX_VOE_PM_##name(i),     ((i*8)+k),  "TX_VOE_PM:"#name)
#define DR_VOE_I(name, i, v)       { SRVL_RD(VTSS_OAM_MEP_VOE_##name(i), &v); }

static vtss_rc srvl_debug_oam(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32              i, k, v, div, voe_idx, voe_cnt;
    char             buf[80];
    BOOL             show, vop, resources, voe, status, lm_counters;

    div = 0;
    voe_idx = 0;
    show = vop = voe = status = lm_counters = resources = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show = (info->action == 0) ? TRUE : FALSE;
        vop = (info->action == 1) ? TRUE : FALSE;
        resources = (info->action == 2) ? TRUE : FALSE;

        if (info->action > 2) { /* This potentially a VOE config or VOE status action */
            for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
                voe = (info->action / div == 4) ? TRUE : FALSE;
                status = (info->action / div == 5) ? TRUE : FALSE;
                lm_counters = (info->action / div == 6) ? TRUE : FALSE;
                if (voe || status || lm_counters) {
                    break;
                }
            }
            if (voe || status || lm_counters) {    /* Calculate the possible VOE/MIP index */
                voe_idx = info->action % div;
            }
        }
    }

    VTSS_D("show %u  vop %u  resources %u  voe %u  status %u  lm_counters %u", show, vop, resources, voe, status, lm_counters);

    if (show) {
        pr("OAM Debug Group action:\n");
        pr("    0: Show possible actions\n");
        pr("    1: Print VOP configurations\n");
        pr("    2: Print allocated resources\n");
        pr("    4XXXX: Print VOE XXXX configurations. Without XXXX all VOEs are printed\n");
        pr("    5XXXX: Print VOE XXXX status. Without XXXX all VOEs are printed\n");
        pr("    6XXXX: Print VOE XXXX LM counters. Without XXXX all VOEs are printed\n");
        pr("\n");
    }

    if (!info->has_action || vop) { /* VOP configuration must be printed */
        vtss_srvl_debug_reg_header(pr, "VOP");
        D_COM(pr, MEP_CTRL);
        D_COM(pr, CPU_CFG);
        D_COM(pr, CPU_CFG_1);
        D_COM(pr, OAM_SDLB_CPU_COPY);
        for (i=0; i<8; ++i)
            D_COM_I(pr, OAM_GENERIC_CFG, i);
        for (i=0; i<7; ++i)
            D_COM_I(pr, CCM_PERIOD_CFG, i);
        D_COM(pr, CCM_CTRL);
        D_COM(pr, CCM_SCAN_STICKY);
        D_COM(pr, MASTER_INTR_CTRL);
        for (i=0; i<3; ++i)
            D_COM_I(pr, INTR, i);
        D_COM(pr, COMMON_MEP_MC_MAC_MSB);
        D_COM(pr, COMMON_MEP_MC_MAC_LSB);
        pr("\n");
    }

    if (!info->has_action || voe) { /* VOE configuration must be printed */
        pr("VOE Config:\n\n");
    
        for (i=0; i<VTSS_VOE_CNT; ++i) {
            if (voe && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }

            DR_VOE_I(BASIC_CTRL, i, v);
            if (info->full  ||  (v & VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA) != 0) {
                VTSS_SPRINTF(buf, "VOE %u", i);
                vtss_srvl_debug_reg_header(pr, buf);
                D_COM_I(pr, VOE_CFG, i);
                D_COM_I(pr, UPMEP_LM_CNT_VLD, i);
                D_COM_I(pr, VOE_MAP_CTRL, i);
                D_COM_I(pr, VOE_CNT_CTRL, i);
                D_VOE_I(pr, BASIC_CTRL, i);
                D_VOE_I(pr, MEL_CTRL, i);
                D_VOE_I(pr, OAM_CPU_COPY_CTRL, i);
                D_VOE_I(pr, OAM_FWD_CTRL, i);
                D_VOE_I(pr, OAM_SDLB_CTRL, i);
                D_VOE_I(pr, OAM_CNT_OAM_CTRL, i);
                D_VOE_I(pr, OAM_CNT_DATA_CTRL, i);
                D_VOE_I(pr, MEP_UC_MAC_MSB, i);
                D_VOE_I(pr, MEP_UC_MAC_LSB, i);
                D_VOE_I(pr, OAM_HW_CTRL, i);
                D_VOE_I(pr, LOOPBACK_CTRL, i);
                D_VOE_I(pr, LBR_RX_TRANSID_CFG, i);
                D_VOE_I(pr, LBM_TX_TRANSID_UPDATE, i);
                D_VOE_I(pr, LBM_TX_TRANSID_CFG, i);
                D_VOE_I(pr, CCM_CFG, i);
                D_VOE_I(pr, CCM_TX_SEQ_CFG, i);
                D_VOE_I(pr, CCM_RX_SEQ_CFG, i);
                D_VOE_I(pr, CCM_MEPID_CFG, i);
                for (k=0; k<12; ++k)
                    D_VOE_II(pr, CCM_MEGID_CFG, i, 11-k);
                D_VOE_I(pr, INTR_ENA, i);
            }
        }
    }
    pr("\n");

    if (!info->has_action || status) { /* VOE status must be printed */
        pr("VOE Status:\n\n");
    
        for (i=0; i<VTSS_VOE_CNT; ++i) {
            if (status && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }

            DR_VOE_I(BASIC_CTRL, i, v);
            if (info->full  ||  (v & VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA) != 0) {
                VTSS_SPRINTF(buf, "VOE %u", i);
                vtss_srvl_debug_reg_header(pr, buf);
                D_VOE_I(pr, LBR_RX_FRM_CNT, i);
                D_VOE_I(pr, LBR_RX_TRANSID_CFG, i);
                D_VOE_I(pr, LBM_TX_TRANSID_CFG, i);
                D_VOE_I(pr, CCM_CFG, i);
                D_VOE_I(pr, CCM_RX_VLD_FC_CNT, i);
                D_VOE_I(pr, CCM_RX_INVLD_FC_CNT, i);
                D_VOE_I(pr, CCM_CAP_TX_FCF, i);
                D_VOE_I(pr, CCM_CAP_RX_FCL, i);
                D_VOE_I(pr, CCM_TX_SEQ_CFG, i);
                D_VOE_I(pr, CCM_RX_SEQ_CFG, i);
                D_VOE_I(pr, OAM_RX_STICKY, i);
                D_VOE_I(pr, STICKY, i);
                D_VOE_I(pr, UPMEP_LM_CNT_STICKY, i);
                D_VOE_I(pr, UPMEP_LMR_RX_LM_CNT, i);
                D_VOE_I(pr, RX_SEL_OAM_CNT, i);
                D_VOE_I(pr, TX_SEL_OAM_CNT, i);
                D_VOE_I(pr, RX_OAM_FRM_CNT, i);
                D_VOE_I(pr, TX_OAM_FRM_CNT, i);
                // Not included: PORT_OM, RX_VOE_OM, TX_VOE_PM
                //   -- too much output
            }
        }
    }
    pr("\n");

    if (!info->has_action || lm_counters) { /* VOE status must be printed */
        pr("VOE LM counters:\n\n");
    
        for (i=0; i<VTSS_VOE_CNT; ++i) {
            if (lm_counters && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }

            DR_VOE_I(BASIC_CTRL, i, v);
            if (info->full  ||  (v & VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA) != 0) {
                VTSS_SPRINTF(buf, "VOE %u", i);
                vtss_srvl_debug_reg_header(pr, buf);

                for (k = 0; k < VTSS_PRIO_ARRAY_SIZE; ++k) {
                    VTSS_SPRINTF(buf, "Priority %u", k);
                    if (i < VTSS_PATH_SERVICE_VOE_CNT) {
                        D_RX_VOE_PM_I(pr, MEP_RX_FRM_CNT, i, k);
                        D_TX_VOE_PM_I(pr, MEP_TX_FRM_CNT, i, k);
                    } else {
                        D_PORT_PM_I(pr, PORT_RX_FRM_CNT, i, k);
                        D_PORT_PM_I(pr, PORT_TX_FRM_CNT, i, k);
                    }
                }
            }
        }
    }
    pr("\n");

    if (!info->has_action || resources) { /* Used resources must be printed */
        /* Print resource consumption */
        for (voe_cnt = 0, i = 0; i < VTSS_VOE_CNT; ++i) {
            DR_VOE_I(BASIC_CTRL, i, v);
            if ((v & VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA) != 0) {
                voe_cnt++;
            }
        }

        pr("Resource consumption:\n");
        pr("VOE: %u\n", voe_cnt);
        pr("\n");
        pr("Maximum values:\n");
        pr("SERVICE-VOE-MAX: %u\n", VTSS_PATH_SERVICE_VOE_CNT);
        pr("PORT-VOE-MAX: %u\n", VTSS_PORT_VOE_CNT);
        pr("\n");
    } /* Print resource consumption */

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_oam_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_OAM, srvl_debug_oam, vtss_state, pr, info);
}

#undef D_COM
#undef D_COM_I
#undef D_VOE_I
#undef D_VOE_II
#undef DR_VOE_I



/* - Initialization ------------------------------------------------ */
/* - Initialization ------------------------------------------------ */
/* - Initialization ------------------------------------------------ */
/* - Initialization ------------------------------------------------ */


static vtss_rc voe_default_set(vtss_state_t          *vtss_state,
                               const vtss_voe_idx_t  voe_idx)
{
    vtss_rc  rc, ret_rc = VTSS_RC_OK;

    VTSS_MEMSET(&vtss_state->oam.voe_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_cc_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_cc_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_rdi_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_rdi_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_lt_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_lt_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_lb_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_lb_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_laps_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_laps_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_event_mask[voe_idx], 0, sizeof(vtss_state->oam.voe_event_mask[voe_idx]));

    if ((rc = srvl_voe_event_mask_set(vtss_state, voe_idx, VTSS_VOE_EVENT_MASK_ALL, FALSE)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_cc_rdi_set(vtss_state, voe_idx, FALSE)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_cc_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_cc_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_lt_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_lt_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_lb_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_lb_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_laps_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_laps_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_counters_clear(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_cc_counters_clear(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_lb_counters_clear(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = srvl_voe_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }

    return(ret_rc);
}

static vtss_rc srvl_oam_voe_poll_1sec(vtss_state_t *vtss_state)
{
    /* LM and DM PDU Tx/Rx counters are 8 bit
     * Some CCM PDU counters are 16 bit
     * Data frame counters are 32 bit
     * No byte counters
     * For a 32-bit frame counter at 10G, wrap happens after approx. 219s
     * For OAM PDU at 3.3 ms (CCM) 16-bit wrap happens after approx. 196s
     * For OAM PDU at 100 ms (LM/DM) 8-bit wrap happens after approx. 25s
     * I.e. worst case is 25s
     * Jaguar2 has 1077 VOEs to cover in 25s -> poll 44 at each tick
     * ServalT has  203 VOEs to cover in 25s -> poll 9 at each tick
     *
     * Bugzilla #23350: The original algorithm depended on a very accurate
     * timer to drive this poll. This turned out to be a false assumption.
     * We thus occasionally encountered DM counter overrun because the polling
     * sometimes took a bit longer. We have thus increased the number of VOEs
     * that is polled every second by setting the target "full circle" period
     * to 20 seconds instead of 25.
     */
    const u32 N = 1 + VTSS_VOE_CNT / 20;

    vtss_voe_idx_t *idx = &(vtss_state->oam.voe_poll_idx);  /* For readability */
    u32 i;

    for (i = 0; i < N; ++i) {
        VTSS_RC(voe_counter_update(vtss_state, *idx, 0));
        *idx = (*idx == VTSS_VOE_CNT - 1) ? 0 : *idx + 1;
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_init(vtss_state_t *vtss_state)
{
    u32 i;

    /* All VOEs are default enabled by hardware; we disable them here. */
    for (i=0; i < VTSS_VOE_CNT; ++i) {
        SRVL_WR(VTSS_OAM_MEP_VOE_BASIC_CTRL(i), 0);
    }

    /* Disable VOP */
    SRVL_WR(VTSS_OAM_MEP_COMMON_MEP_CTRL, 0);

    /* Configure LOC periods used for CCM LOC: */
    SRVL_WR(VTSS_OAM_MEP_COMMON_CCM_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_3_3_MS)),   16650);
    SRVL_WR(VTSS_OAM_MEP_COMMON_CCM_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_10_MS)),    50454);
    SRVL_WR(VTSS_OAM_MEP_COMMON_CCM_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_100_MS)),  504541);
    SRVL_WR(VTSS_OAM_MEP_COMMON_CCM_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_1_SEC)),  5045409);

    /* Configure LOC periods used for CCM LOC: */
    /* Configure LOC periods used for CCM-LM counter insertion (1 sec and 100 ms): */
    /* (must be configured with 2 x desired CCM-LM counter insertion period) */
    /* Use slightly slower CCM-LM counter insertion to make sure 1 sec and 100 ms CC frames always have LM counters inserted. */
    SRVL_WR(VTSS_OAM_MEP_COMMON_CCM_PERIOD_CFG(lm_loc_period_index(VTSS_VOE_CCM_PERIOD_100_MS)),  2*504541);
    SRVL_WR(VTSS_OAM_MEP_COMMON_CCM_PERIOD_CFG(lm_loc_period_index(VTSS_VOE_CCM_PERIOD_1_SEC)),  2*5045409);

    return VTSS_RC_OK;
}


vtss_rc vtss_srvl_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_oam_state_t *state = &vtss_state->oam;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->vop_conf_set = srvl_vop_conf_set;
        state->voe_event_active_get = srvl_voe_event_active_get;
        state->voe_event_mask_set = srvl_voe_event_mask_set;
        state->voe_event_get = srvl_voe_event_get;
        state->voe_alloc = srvl_voe_alloc;
        state->voe_free = srvl_voe_free;
        state->voe_conf_set = srvl_voe_conf_set;
        state->voe_cc_conf_set = srvl_voe_cc_conf_set;
        state->voe_cc_rdi_set = srvl_voe_cc_rdi_set;
        state->voe_cc_cpu_copy_next_set = srvl_voe_cc_cpu_copy_next_set;
        state->voe_lt_conf_set = srvl_voe_lt_conf_set;
        state->voe_lb_conf_set = srvl_voe_lb_conf_set;
        state->voe_laps_conf_set = srvl_voe_laps_conf_set;
        state->voe_status_get = srvl_voe_status_get;
        state->voe_cc_status_get = srvl_voe_cc_status_get;
        state->voe_lt_status_get = srvl_voe_lt_status_get;
        state->voe_lb_status_get = srvl_voe_lb_status_get;
        state->voe_laps_status_get = srvl_voe_laps_status_get;
        state->voe_counters_get = srvl_voe_counters_get;
        state->voe_cc_counters_get = srvl_voe_cc_counters_get;
        state->voe_lb_counters_get = srvl_voe_lb_counters_get;
        state->voe_counters_clear = srvl_voe_counters_clear;
        state->voe_cc_counters_clear = srvl_voe_cc_counters_clear;
        state->voe_lb_counters_clear = srvl_voe_lb_counters_clear;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(srvl_init(vtss_state));
        break;
    case VTSS_INIT_CMD_POLL:
        VTSS_RC(srvl_oam_voe_poll_1sec(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_VOP */

#endif /* VTSS_ARCH_OCELOT */
