// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_OAM
#include "vtss_jaguar2_cil.h"

#if defined(VTSS_ARCH_JAGUAR_2)

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

    JR2_RD(VTSS_VOP_VOE_CONF_OAM_HW_CTRL(voe_idx), &v);
    lb_hw_enabled  = (v & (VTSS_M_VOP_VOE_CONF_OAM_HW_CTRL_LBM_ENA | VTSS_M_VOP_VOE_CONF_OAM_HW_CTRL_LBR_ENA)) != 0;
    tst_hw_enabled = (v & VTSS_M_VOP_VOE_CONF_OAM_HW_CTRL_TST_ENA) != 0;

    *doing_lb  = lb_hw_enabled  && !tst_hw_enabled;
    *doing_tst = tst_hw_enabled && !lb_hw_enabled;

    return (VTSS_RC_OK);
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
    case VTSS_VOE_CCM_PERIOD_10_SEC:
        return 4;
    }
    VTSS_D("Invalid period for CC");
    return 0;
}

static u32 lm_loc_period_index(vtss_voe_ccm_period_t p)
{
    switch (p) {
    case VTSS_VOE_CCM_PERIOD_3_3_MS:
    case VTSS_VOE_CCM_PERIOD_10_SEC:
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
    case VTSS_VOE_CCM_PERIOD_10_SEC:
        return 5;
    }
    VTSS_D("Invalid period for CC");
    return 0;
}

static u32 raps_handling_value(vtss_oam_raps_handling_t handling)
{
    switch (handling) {
    case VTSS_OAM_RAPS_HANDLING_NONE:
        return 0;
    case VTSS_OAM_RAPS_HANDLING_COPY_CPU:
        return 1;
    case VTSS_OAM_RAPS_HANDLING_REDIR_CPU:
        return 2;
    case VTSS_OAM_RAPS_HANDLING_DISCARD:
        return 3;
    }
    VTSS_D("Invalid RAPS hendling");
    return 0;
}

u32 vtss_j2_voi_idx_to_mip_idx(vtss_voi_idx_t  voi_idx)
{
    if (voi_idx < VTSS_DOWN_VOI_CNT) {
        return (voi_idx);
    } else {
        return ((voi_idx - VTSS_DOWN_VOI_CNT) + 1); /* Up MIP instance 0 is not used as it cannot be addressed by ES0 action. */
    }
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
#define CHIPREAD(reg, cnt, ctype, cdir) { JR2_RD(reg, &v); vtss_cmn_counter_32_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }
#define UPDATE8(v, cnt, ctype, cdir)    { vtss_cmn_counter_8_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }
#define UPDATE16(v, cnt, ctype, cdir)   { vtss_cmn_counter_16_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }

    vtss_rc     rc = VTSS_RC_OK;
    u32         v;
    BOOL        doing_lb = 0, doing_tst = 0;
    vtss_oam_voe_internal_counters_t *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    /* CCM counter update */
    JR2_RD(VTSS_VOP_VOE_STAT_CCM_RX_FRM_CNT(voe_idx), &v);
    UPDATE16(VTSS_X_VOP_VOE_STAT_CCM_RX_FRM_CNT_CCM_RX_VLD_FC_CNT(v),    &chipcnt->ccm.rx_valid_counter,    VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    UPDATE16(VTSS_X_VOP_VOE_STAT_CCM_RX_FRM_CNT_CCM_RX_INVLD_FC_CNT(v),  &chipcnt->ccm.rx_invalid_counter,  VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_VOP_VOE_STAT_CCM_TX_SEQ_CFG(voe_idx),                  &chipcnt->ccm.tx_counter,          VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_TX);

    JR2_RD(VTSS_VOP_VOE_STAT_CCM_RX_WARNING(voe_idx), &v);
    UPDATE16(VTSS_X_VOP_VOE_STAT_CCM_RX_WARNING_CCM_RX_SEQNO_ERR_CNT(v),  &chipcnt->ccm.rx_oo_counter,      VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);

    /* LB counter update */
    VTSS_RC(doing_calculate(vtss_state, voe_idx, &doing_lb, &doing_tst));
    if (doing_lb || (clear_mask & VTSS_OAM_CNT_LB)) {
        CHIPREAD(VTSS_VOP_VOE_STAT_LBR_RX_FRM_CNT(voe_idx),         &chipcnt->lb.rx_lbr_counter,      VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_VOP_VOE_STAT_LBM_TX_TRANSID_CFG(voe_idx),     &chipcnt->lb.tx_lbm_counter,      VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_TX);
        CHIPREAD(VTSS_VOP_VOE_STAT_LBR_RX_TRANSID_ERR_CNT(voe_idx), &chipcnt->lb.rx_lbr_oo_counter,   VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_VOP_VOE_CRC_ERR_LBR_CRC_ERR_CNT(voe_idx),     &chipcnt->lb.rx_lbr_crc_counter,  VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_VOP_VOE_STAT_LBR_TX_FRM_CNT(voe_idx),         &chipcnt->lb.tx_lbr_counter,      VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_TX);
    }

    /* VOE counter update */
    CHIPREAD(VTSS_VOP_VOE_STAT_RX_SEL_OAM_CNT(voe_idx), &chipcnt->voe.rx_selected_counter,  VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_VOP_VOE_STAT_TX_SEL_OAM_CNT(voe_idx), &chipcnt->voe.tx_selected_counter,  VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_TX);
    CHIPREAD(VTSS_VOP_VOE_STAT_RX_OAM_FRM_CNT(voe_idx), &chipcnt->voe.rx_counter,           VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_VOP_VOE_STAT_TX_OAM_FRM_CNT(voe_idx), &chipcnt->voe.tx_counter,           VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_TX);
    CHIPREAD(VTSS_VOP_VOE_STAT_TX_OAM_DISCARD(voe_idx), &chipcnt->voe.tx_discard_counter,   VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_TX);
    CHIPREAD(VTSS_VOP_VOE_STAT_RX_OAM_DISCARD(voe_idx), &chipcnt->voe.rx_discard_counter,   VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_RX);

    return rc;
#undef CHIPREAD
#undef UPDATE8
#undef UPDATE16
}

static vtss_rc jr2_oam_vop_int_enable(vtss_state_t *vtss_state, BOOL enable)
{
    JR2_WRM(VTSS_VOP_COMMON_MASTER_INTR_CTRL, VTSS_F_VOP_COMMON_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA(enable ? 1 : 0), VTSS_M_VOP_COMMON_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA);

    return VTSS_RC_OK;
}

/* Determine VOP interrupt flag -- clear if no enabled VOEs have interrupts enabled */
static vtss_rc oam_vop_int_update(vtss_state_t *vtss_state)
{
    u32 i;
    u32 must_enable;

    for (i = 0, must_enable = 0; !must_enable && i < VTSS_VOE_CNT; ++i) {
        if (vtss_state->oam.voe_alloc_data[i].allocated) {
            JR2_RD(VTSS_VOP_VOE_STAT_INTR_ENA(i), &must_enable);
            must_enable &= 0x7ff;  /* Only bits 0-10 are valid */
        }
    }

    return jr2_oam_vop_int_enable(vtss_state, must_enable ? TRUE : FALSE);
}

static vtss_rc voe_default_set(vtss_state_t          *vtss_state,
                               const vtss_voe_idx_t  voe_idx);

static vtss_rc voi_default_set(vtss_state_t          *vtss_state,
                               const vtss_voe_idx_t  voe_idx);

/* - CIL functions ------------------------------------------------- */
/* - CIL functions ------------------------------------------------- */
/* - CIL functions ------------------------------------------------- */
/* - CIL functions ------------------------------------------------- */

static vtss_rc jr2_vop_conf_set(vtss_state_t            *vtss_state,
                                const vtss_vop_conf_t   *const conf)
{

    u32 value, i;

    VTSS_D("Enter");

    /* Multicast MAC configuration */
    value = (conf->multicast_dmac.addr[0] << 8) | conf->multicast_dmac.addr[1];
    JR2_WR(VTSS_VOP_COMMON_COMMON_MEP_MC_MAC_MSB, VTSS_F_VOP_COMMON_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB(value));

    value = (conf->multicast_dmac.addr[2] << 24) | (conf->multicast_dmac.addr[3] << 16) |
            (conf->multicast_dmac.addr[4] <<  8) | (conf->multicast_dmac.addr[5]);
    value >>= 4;   /* Value in reg. field doesn't include the lower 4 bits */
    JR2_WR(VTSS_VOP_COMMON_COMMON_MEP_MC_MAC_LSB, VTSS_F_VOP_COMMON_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB(value));

    /* CPU extraction queue configuration */
    value = (VTSS_F_VOP_COMMON_CPU_EXTR_CFG_CPU_ERR_QU(conf->voe_queue_err));
    JR2_WR(VTSS_VOP_COMMON_CPU_EXTR_CFG, value);

    value = (VTSS_F_VOP_COMMON_CPU_EXTR_CFG_1_CCM_CPU_QU(conf->voe_queue_ccm) |
         VTSS_F_VOP_COMMON_CPU_EXTR_CFG_1_LBM_CPU_QU(conf->voe_queue_lbm) |
         VTSS_F_VOP_COMMON_CPU_EXTR_CFG_1_LBR_CPU_QU(conf->voe_queue_lbr) |
         VTSS_F_VOP_COMMON_CPU_EXTR_CFG_1_LT_CPU_QU(conf->voe_queue_lt));
    JR2_WR(VTSS_VOP_COMMON_CPU_EXTR_CFG_1, value);

    for (i = 0; i < VTSS_DOWN_VOI_CNT; ++i) {   /* The number of Down and Up MIPs are the same in HW */
        JR2_WRM(VTSS_ANA_CL_MIP_TBL_MIP_CFG(i), VTSS_F_ANA_CL_MIP_TBL_MIP_CFG_CPU_MIP_QU(conf->voi_queue), VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_CPU_MIP_QU);
        JR2_WRM(VTSS_REW_MIP_TBL_MIP_CFG(i), VTSS_F_REW_MIP_TBL_MIP_CFG_CPU_MIP_QU(conf->voi_queue), VTSS_M_REW_MIP_TBL_MIP_CFG_CPU_MIP_QU);
    }

    /* Generic [GENERIC_OFFSET_LAPS] is used for LAPS */
    value = VTSS_F_VOP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU(conf->voe_queue_aps) |
            VTSS_F_VOP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL(39) |      /* LAPS opcode is 39 */
            VTSS_F_VOP_COMMON_OAM_GENERIC_CFG_GENERIC_DMAC_CHK_DIS(0);
    JR2_WR(VTSS_VOP_COMMON_OAM_GENERIC_CFG(GENERIC_OFFSET_LAPS), value);

#if !defined(VTSS_ARCH_JAGUAR_2_B)
    /* Always using all 8 HMO slots and HMO scan is initiated at half the configured time... So divide by 8 and multiply by 2. */
    JR2_WR(VTSS_VOP_COMMON_HMO_PERIOD_CFG(0), (((u64)conf->auto_copy_period[0]) * 1000) / LOC_BASE / (8 / 2));
    JR2_WR(VTSS_VOP_COMMON_HMO_PERIOD_CFG(1), (((u64)conf->auto_copy_period[1]) * 1000) / LOC_BASE / (8 / 2));

    JR2_WR(VTSS_VOP_COMMON_HMO_TIMER_CFG, (VTSS_F_VOP_COMMON_HMO_TIMER_CFG_HMO_RX_CCM_NXT_TIMER(conf->auto_copy_ccm_valid ? 1 : 0)       |
                                           VTSS_F_VOP_COMMON_HMO_TIMER_CFG_HMO_CCM_RX_TLV_NON_ZERO_TIMER(conf->auto_copy_ccm_tlv ? 1 :0) |
                                           VTSS_F_VOP_COMMON_HMO_TIMER_CFG_HMO_CCM_RX_BAD_NXT_TIMER(conf->auto_copy_ccm_err ? 1 : 0)     |
                                           VTSS_F_VOP_COMMON_HMO_TIMER_CFG_HMO_RX_TEST_FRM_NXT_TIMER(conf->auto_copy_lbr ? 1 : 0)));
#endif

    /* Enable VOP */
    value = VTSS_F_VOP_COMMON_VOP_CTRL_VOP_ENA(1) | VTSS_F_VOP_COMMON_VOP_CTRL_LOC_SCAN_ENA(1) | VTSS_F_VOP_COMMON_VOP_CTRL_CCM_RX_SRC_PORT_DETECT_CNT(3);
    JR2_WR(VTSS_VOP_COMMON_VOP_CTRL, value);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_event_active_get(vtss_state_t   *vtss_state,
                                        const u32      active_size,
                                        u32            *const active)
{
    VTSS_D("Enter  active_size %u", active_size);

    u32 i, v;

    VTSS_MEMSET(active, 0, sizeof(active_size));
    JR2_RD(VTSS_VOP_COMMON_MASTER_INTR_CTRL, &v);
    if (!VTSS_X_VOP_COMMON_MASTER_INTR_CTRL_OAM_MEP_INTR(v)) {
        VTSS_D("No interrupts are enabled");
        return VTSS_RC_OK;
    }

    /* just scan all VOEs: */
    for (i = 0; (i < active_size) && (i < VTSS_EVENT_MASK_ARRAY_SIZE); ++i) {
        JR2_RD(VTSS_VOP_COMMON_INTR(i), &active[i]);
    }

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_event_mask_set(vtss_state_t          *vtss_state,
                                      const vtss_voe_idx_t  voe_idx,
                                      const u32             mask,
                                      const BOOL            enable)
{
    u32 enable_mask, reg_mask;

    VTSS_D("Enter  voe_idx %u  mask %u  enable %u", voe_idx, mask, enable);

    /* Read the interrupt enable mask */
    JR2_RD(VTSS_VOP_VOE_STAT_INTR_ENA(voe_idx), &enable_mask);

    /* Translate the input mask to register mask */
    reg_mask = (((mask & VTSS_VOE_EVENT_MASK_CCM_SRC_PORT_MOVE)   ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_RX_SRC_PORT_DETECT_INTR_ENA : 0) |
#if !defined(VTSS_ARCH_JAGUAR_2_B)
                ((mask & VTSS_VOE_EVENT_MASK_CCM_TLV_PORT_STATUS) ? VTSS_M_VOP_VOE_STAT_INTR_ENA_TLV_PORT_STATUS_INTR_ENA : 0) |
                ((mask & VTSS_VOE_EVENT_MASK_CCM_TLV_IF_STATUS)   ? VTSS_M_VOP_VOE_STAT_INTR_ENA_TLV_INTERFACE_STATUS_INTR_ENA : 0) |
#endif
                ((mask & VTSS_VOE_EVENT_MASK_CCM_PERIOD)          ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_PERIOD_INTR_ENA : 0) |
                ((mask & VTSS_VOE_EVENT_MASK_CCM_PRIORITY)        ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_PRIO_INTR_ENA : 0) |
                ((mask & VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD)     ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_ZERO_PERIOD_INTR_ENA : 0) |
                ((mask & VTSS_VOE_EVENT_MASK_CCM_RX_RDI)          ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_RX_RDI_INTR_ENA : 0) |
                ((mask & VTSS_VOE_EVENT_MASK_CCM_LOC)             ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_LOC_INTR_ENA : 0) |
                ((mask & VTSS_VOE_EVENT_MASK_CCM_MEP_ID)          ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_MEPID_INTR_ENA : 0) |
                ((mask & VTSS_VOE_EVENT_MASK_CCM_MEG_ID)          ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_MEGID_INTR_ENA : 0) |
                ((mask & VTSS_VOE_EVENT_MASK_CCM_MEG_LEVEL)       ? VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_RX_MEL_LOW_INTR_ENA : 0));

    /* Calculate new enable mask */
    enable_mask = enable ? (enable_mask | reg_mask) : (enable_mask & ~reg_mask);

    /* Write back the interrupt enable mask */
    JR2_WR(VTSS_VOP_VOE_STAT_INTR_ENA(voe_idx), enable_mask);

    return enable_mask ? jr2_oam_vop_int_enable(vtss_state, TRUE) : oam_vop_int_update(vtss_state);
}

static vtss_rc jr2_voe_event_get(vtss_state_t          *vtss_state,
                                 const vtss_voe_idx_t  voe_idx,
                                 u32                   *const mask)
{
    u32 enable_mask, sticky_mask;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Read the interrupt enable mask */
    JR2_RD(VTSS_VOP_VOE_STAT_INTR_ENA(voe_idx), &enable_mask);

    /* Translate enable mask to sticky bit positions (yes, sticky bit position is not the same as enable bit position) */
    enable_mask = 
    (VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_RX_SRC_PORT_DETECT_STICKY((enable_mask & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_RX_SRC_PORT_DETECT_INTR_ENA)   ? 1 : 0) |
#if !defined(VTSS_ARCH_JAGUAR_2_B)
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_TLV_PORT_STATUS_STICKY((enable_mask        & VTSS_M_VOP_VOE_STAT_INTR_ENA_TLV_PORT_STATUS_INTR_ENA)          ? 1 : 0) |
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_TLV_INTERFACE_STATUS_STICKY((enable_mask   & VTSS_M_VOP_VOE_STAT_INTR_ENA_TLV_INTERFACE_STATUS_INTR_ENA)     ? 1 : 0) |
#endif
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_PERIOD_RX_ERR_STICKY((enable_mask      & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_PERIOD_INTR_ENA)               ? 1 : 0) |
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_PRIO_RX_ERR_STICKY((enable_mask        & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_PRIO_INTR_ENA)                 ? 1 : 0) |
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_ZERO_PERIOD_RX_ERR_STICKY((enable_mask & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_ZERO_PERIOD_INTR_ENA)          ? 1 : 0) |
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_RX_RDI_STICKY((enable_mask             & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_RX_RDI_INTR_ENA)               ? 1 : 0) |
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_LOC_STICKY((enable_mask                & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_LOC_INTR_ENA)                  ? 1 : 0) |
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_MEPID_RX_ERR_STICKY((enable_mask       & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_MEPID_INTR_ENA)                ? 1 : 0) |
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_MEGID_RX_ERR_STICKY((enable_mask       & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_MEGID_INTR_ENA)                ? 1 : 0) |
     VTSS_F_VOP_VOE_STAT_INTR_STICKY_CCM_RX_MEL_LOW_ERR_STICKY((enable_mask     & VTSS_M_VOP_VOE_STAT_INTR_ENA_CCM_RX_MEL_LOW_INTR_ENA)           ? 1 : 0));

    /* Read sticky bits and clear the enabled ones */
    JR2_RD(VTSS_VOP_VOE_STAT_INTR_STICKY(voe_idx), &sticky_mask);
    sticky_mask &= enable_mask;
    JR2_WR(VTSS_VOP_VOE_STAT_INTR_STICKY(voe_idx), sticky_mask); /* Sticky bits cleared by writing 1 to them */

    /* Translate sticky mask to returned event mask */
    *mask = ((VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_RX_SRC_PORT_DETECT_STICKY(sticky_mask) ? VTSS_VOE_EVENT_MASK_CCM_SRC_PORT_MOVE   : 0) |
#if !defined(VTSS_ARCH_JAGUAR_2_B)
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_TLV_PORT_STATUS_STICKY(sticky_mask)        ? VTSS_VOE_EVENT_MASK_CCM_TLV_PORT_STATUS : 0) |
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_TLV_INTERFACE_STATUS_STICKY(sticky_mask)   ? VTSS_VOE_EVENT_MASK_CCM_TLV_IF_STATUS   : 0) |
#endif
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_PERIOD_RX_ERR_STICKY(sticky_mask)      ? VTSS_VOE_EVENT_MASK_CCM_PERIOD          : 0) |
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_PRIO_RX_ERR_STICKY(sticky_mask)        ? VTSS_VOE_EVENT_MASK_CCM_PRIORITY        : 0) |
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_ZERO_PERIOD_RX_ERR_STICKY(sticky_mask) ? VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD     : 0) |
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_RX_RDI_STICKY(sticky_mask)             ? VTSS_VOE_EVENT_MASK_CCM_RX_RDI          : 0) |
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_LOC_STICKY(sticky_mask)                ? VTSS_VOE_EVENT_MASK_CCM_LOC             : 0) |
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_MEPID_RX_ERR_STICKY(sticky_mask)       ? VTSS_VOE_EVENT_MASK_CCM_MEP_ID          : 0) |
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_MEGID_RX_ERR_STICKY(sticky_mask)       ? VTSS_VOE_EVENT_MASK_CCM_MEG_ID          : 0) |
             (VTSS_X_VOP_VOE_STAT_INTR_STICKY_CCM_RX_MEL_LOW_ERR_STICKY(sticky_mask)     ? VTSS_VOE_EVENT_MASK_CCM_MEG_LEVEL       : 0));

    VTSS_D("Exit  mask %X", *mask);

    return (VTSS_RC_OK);
}

static u32 voe_alloc_idx;
static vtss_rc jr2_voe_alloc(vtss_state_t                *vtss_state,
                             const vtss_voe_type_t       type,
                             const vtss_port_no_t        port,
                             const vtss_oam_direction_t  direction,
                             vtss_voe_idx_t              *const voe_idx)
{
    u32 i, offset, v;

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
    JR2_WRM(VTSS_VOP_VOE_CONF_VOE_CTRL(*voe_idx), 0, VTSS_M_VOP_VOE_CONF_VOE_CTRL_VOE_ENA);

    /* Clear assorted counters: */
    JR2_WR(VTSS_VOP_VOE_STAT_RX_SEL_OAM_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_RX_OAM_FRM_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_TX_SEL_OAM_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_TX_OAM_FRM_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_CCM_RX_FRM_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_CCM_TX_SEQ_CFG(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_CCM_RX_SEQ_CFG(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_CCM_RX_WARNING(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_CCM_ERR(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_CCM_RX_ERR_1(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_LBM_TX_TRANSID_CFG(*voe_idx), 1);
    JR2_WR(VTSS_VOP_VOE_STAT_LBR_TX_FRM_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_LBR_RX_TRANSID_CFG(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_LBR_RX_FRM_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_LBR_RX_TRANSID_ERR_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_DM_PDU_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_LM_PDU_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_TX_OAM_DISCARD(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_RX_OAM_DISCARD(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_PDU_EXTRACT(*voe_idx), VTSS_M_VOP_VOE_STAT_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE);   /* Hit Me Once is default */
#if !defined(VTSS_ARCH_JAGUAR_2_B)
    JR2_WR(VTSS_VOP_VOE_STAT_AUTO_HIT_ME_ONCE(*voe_idx), 0);
#endif
    JR2_WR(VTSS_VOP_VOE_STAT_SYNLM_EXTRACT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_TX_STICKY(*voe_idx), VTSS_M_VOP_VOE_STAT_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY | VTSS_M_VOP_VOE_STAT_OAM_TX_STICKY_TX_SLM_PRIO_ERR_STICKY);
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(*voe_idx), 0xffffffff); /* sticky bits cleared by writing 1 to them */
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_RX_STICKY2(*voe_idx), 0xff);      /* sticky bits cleared by writing 1 to them */
    JR2_WR(VTSS_VOP_VOE_STAT_CCM_STAT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_CCM_RX_LAST(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_INTR_STICKY(*voe_idx), 0x7ff);        /* sticky bits cleared by writing 1 to them */
    JR2_WR(VTSS_VOP_VOE_STAT_INTR_ENA(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_STAT_SLM_TX_FRM_CNT(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_CCM_LM_CCM_TX_FCB_CFG(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_CCM_LM_CCM_RX_FCB_CFG(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_CRC_ERR_LBR_CRC_ERR_CNT(*voe_idx), 0);

    /* Clear LM counters and COSID_MAPs: */
    switch (type) {
    case VTSS_VOE_TYPE_SERVICE:
        offset = *voe_idx * VTSS_PRIO_ARRAY_SIZE;
        for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
            JR2_WR(VTSS_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB(offset + i), 0);
            JR2_WR(VTSS_REW_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB(offset + i), 0);
        }
        /* Default COSID_MAP_TABLE_ANA + COSID_MAP_TABLE_REW: */
        JR2_WR(VTSS_VOP_ANA_COSID_MAP_CONF_COSID_MAP_TABLE_ANA(*voe_idx), 0xfac688);
        JR2_WR(VTSS_VOP_REW_COSID_MAP_CONF_COSID_MAP_TABLE_REW(*voe_idx), 0xfac688);
        /* Default COSID_MAP_CFG_ANA: */
        v = (VTSS_F_VOP_ANA_COSID_MAP_CONF_COSID_MAP_CFG_ANA_COSID_SRC_SEL_ANA(0) |
             VTSS_F_VOP_ANA_COSID_MAP_CONF_COSID_MAP_CFG_ANA_COLOR_SRC_SEL_ANA(0) |
             VTSS_F_VOP_ANA_COSID_MAP_CONF_COSID_MAP_CFG_ANA_CNT_YELLOW_ANA(1));
        JR2_WR(VTSS_VOP_ANA_COSID_MAP_CONF_COSID_MAP_CFG_ANA(*voe_idx), v);
        /* Default COSID_MAP_CFG_REW: */
        v = (VTSS_F_VOP_REW_COSID_MAP_CONF_COSID_MAP_CFG_REW_COSID_SRC_SEL_REW(0) |
             VTSS_F_VOP_REW_COSID_MAP_CONF_COSID_MAP_CFG_REW_COLOR_SRC_SEL_REW(0) |
             VTSS_F_VOP_REW_COSID_MAP_CONF_COSID_MAP_CFG_REW_CNT_YELLOW_REW(1));
        JR2_WR(VTSS_VOP_REW_COSID_MAP_CONF_COSID_MAP_CFG_REW(*voe_idx), v);
        break;
    case VTSS_VOE_TYPE_PORT:
        offset = (*voe_idx - VTSS_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE;
        for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
            JR2_WR(VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB(offset + i), 0);
            JR2_WR(VTSS_REW_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB(offset + i), 0);
            /* TBD - the port count-all Rx/Tx counters have been left out */
        }
        /* Default PORT_RX_COSID_MAP + PORT_TX_COSID_MAP, DEI=0: */
        JR2_WR(VTSS_VOP_PORT_COSID_MAP_CONF_PORT_RX_COSID_MAP(*voe_idx - VTSS_PORT_VOE_BASE_IDX), 0);
        JR2_WR(VTSS_VOP_PORT_COSID_MAP_CONF_PORT_TX_COSID_MAP(*voe_idx - VTSS_PORT_VOE_BASE_IDX), 0);
        /* Default PORT_RX_COSID_MAP + PORT_TX_COSID_MAP, DEI=1: */
        JR2_WR(VTSS_VOP_PORT_COSID_MAP_CONF_PORT_RX_COSID_MAP1(*voe_idx - VTSS_PORT_VOE_BASE_IDX), 0);
        JR2_WR(VTSS_VOP_PORT_COSID_MAP_CONF_PORT_TX_COSID_MAP1(*voe_idx - VTSS_PORT_VOE_BASE_IDX), 0);
        break;
    }

    /* Clear Per COS counter configuration */
    JR2_WR(VTSS_VOP_VOE_CONF_SAM_COSID_SEQ_CFG(*voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_CONF_SAM_NON_OAM_SEQ_CFG(*voe_idx), 0);

    VTSS_D("Exit voe_idx %u", *voe_idx);

    return VTSS_RC_OK;
}

static vtss_rc jr2_voe_free(vtss_state_t          *vtss_state,
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

    return(ret_rc);
}

static vtss_rc jr2_voe_conf_set(vtss_state_t           *vtss_state,
                                const vtss_voe_idx_t   voe_idx,
                                const vtss_voe_conf_t  *const conf)
{
    u32                i, value, mask;
    vtss_voe_alloc_t   *alloc_data = &vtss_state->oam.voe_alloc_data[voe_idx];

    VTSS_D("Enter  voe_idx %u", voe_idx);

    if (((voe_idx < VTSS_PORT_VOE_BASE_IDX) && (alloc_data->type == VTSS_VOE_TYPE_PORT)) ||
        ((voe_idx >= VTSS_PORT_VOE_BASE_IDX) && (alloc_data->type == VTSS_VOE_TYPE_SERVICE))) {
        VTSS_E("voe_idx %u  type %u.  VOE index and type mismatch", voe_idx, alloc_data->type);
        return VTSS_RC_ERROR;
    }

    /* Configure the unicast MAC */
    value = VTSS_F_VOP_VOE_CONF_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB((conf->unicast_mac.addr[0] << 8) | conf->unicast_mac.addr[1]);
    JR2_WR(VTSS_VOP_VOE_CONF_MEP_UC_MAC_MSB(voe_idx), value);
    value = (conf->unicast_mac.addr[2] << 24) | (conf->unicast_mac.addr[3] << 16) |
        (conf->unicast_mac.addr[4] <<  8) | (conf->unicast_mac.addr[5]);
    JR2_WR(VTSS_VOP_VOE_CONF_MEP_UC_MAC_LSB(voe_idx), value);

    /* Configure MEG level and DMAC check and blocking of high MEL */
    value = VTSS_F_VOP_VOE_CONF_VOE_CTRL_MEL_VAL(conf->meg_level) |
            VTSS_F_VOP_VOE_CONF_VOE_CTRL_UPMEP_ENA(alloc_data->direction == VTSS_OAM_DIRECTION_UP ? 1 : 0) |
            VTSS_F_VOP_VOE_CONF_VOE_CTRL_VERIFY_VERSION_ENA(1) |
            VTSS_F_VOP_VOE_CONF_VOE_CTRL_BLOCK_MEL_HIGH_RX(conf->block_mel_high ? 1 : 0);
    switch (conf->dmac_check_type) {
    case VTSS_VOE_DMAC_CHECK_NONE:
        value |= VTSS_F_VOP_VOE_CONF_VOE_CTRL_RX_DMAC_CHK_SEL(0);
        break;
    case VTSS_VOE_DMAC_CHECK_UNICAST:
        value |= VTSS_F_VOP_VOE_CONF_VOE_CTRL_RX_DMAC_CHK_SEL(1);
        break;
    case VTSS_VOE_DMAC_CHECK_MULTICAST:
        value |= VTSS_F_VOP_VOE_CONF_VOE_CTRL_RX_DMAC_CHK_SEL(2);
        break;
    case VTSS_VOE_DMAC_CHECK_BOTH:
        value |= VTSS_F_VOP_VOE_CONF_VOE_CTRL_RX_DMAC_CHK_SEL(3);
        break;
    }
    mask = VTSS_M_VOP_VOE_CONF_VOE_CTRL_MEL_VAL |
           VTSS_M_VOP_VOE_CONF_VOE_CTRL_UPMEP_ENA |
           VTSS_M_VOP_VOE_CONF_VOE_CTRL_VERIFY_VERSION_ENA |
           VTSS_M_VOP_VOE_CONF_VOE_CTRL_BLOCK_MEL_HIGH_RX |
           VTSS_M_VOP_VOE_CONF_VOE_CTRL_RX_DMAC_CHK_SEL;
    JR2_WRM(VTSS_VOP_VOE_CONF_VOE_CTRL(voe_idx), value, mask);

    /* Configure VOE looped frames to hit ES0 using ISDX in case IFLOW is not none */
    value = VTSS_F_VOP_VOE_CONF_LOOPBACK_CFG_LB_ES0_ISDX_ENA((conf->loop_iflow_id == VTSS_IFLOW_ID_NONE) ? 0 : 1) |
            VTSS_F_VOP_VOE_CONF_LOOPBACK_CFG_LB_ISDX(conf->loop_iflow_id);
    JR2_WR(VTSS_VOP_VOE_CONF_LOOPBACK_CFG(voe_idx), value);

    /* Configure the Port VOE COS mapping. Mapping is set to 1:1, DEI=0: */
    if (alloc_data->type == VTSS_VOE_TYPE_PORT) {
        for (i = 0, value = 0x88888888; i < 8; ++i) { /* set all "CountEnable=1" */
            value |= (i & 7) << (4 * i);
        }
        JR2_WR(VTSS_VOP_PORT_COSID_MAP_CONF_PORT_RX_COSID_MAP(voe_idx - VTSS_PORT_VOE_BASE_IDX), value);
        JR2_WR(VTSS_VOP_PORT_COSID_MAP_CONF_PORT_TX_COSID_MAP(voe_idx - VTSS_PORT_VOE_BASE_IDX), value);
        /* PORT_RX_COSID_MAP + PORT_TX_COSID_MAP, DEI=1: */
        for (i = 0, value = 0x88888888; i < 8; ++i) { /* set all "CountEnable=1" */
            value |= (i & 7) << (4 * i);
        }
        JR2_WR(VTSS_VOP_PORT_COSID_MAP_CONF_PORT_RX_COSID_MAP1(voe_idx - VTSS_PORT_VOE_BASE_IDX), value);
        JR2_WR(VTSS_VOP_PORT_COSID_MAP_CONF_PORT_TX_COSID_MAP1(voe_idx - VTSS_PORT_VOE_BASE_IDX), value);
    }

    /*
     * we need to specifically disable the SLM configuration - otherwise the switch may
     * still respond to incoming SLM PDUs even though SLM is overall disabled.
     */
    JR2_WR(VTSS_VOP_VOE_CONF_SLM_CONFIG(voe_idx), 0);
    JR2_WR(VTSS_VOP_VOE_CONF_SLM_TEST_ID(voe_idx), 0);
    for (i = 0; i < 8; ++i) {
        JR2_WR(VTSS_VOP_VOE_CONF_SLM_PEER_LIST(voe_idx, i), 0);
    }

#if !defined(VTSS_ARCH_JAGUAR_2_B)
    /* Configure the used HMO slot */
    JR2_WRM(VTSS_VOP_VOE_STAT_AUTO_HIT_ME_ONCE(voe_idx), VTSS_F_VOP_VOE_STAT_AUTO_HIT_ME_ONCE_HMO_SLOT(voe_idx & 7), VTSS_M_VOP_VOE_STAT_AUTO_HIT_ME_ONCE_HMO_SLOT);    /* always using all 8 HMO slots */
#endif

    if (conf->enable) {
        JR2_RD(VTSS_VOP_VOE_CONF_VOE_CTRL(voe_idx), &value);
        if (VTSS_X_VOP_VOE_CONF_VOE_CTRL_VOE_ENA(value) == 0) {  /* VOE changed from disabled to enabled. */
            /* Clear the logical counters */
            VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_ALL | VTSS_OAM_CNT_DIR_BOTH));

            /* Disable CC */
            JR2_WRM(VTSS_VOP_VOE_CONF_OAM_HW_CTRL(voe_idx), VTSS_F_VOP_VOE_CONF_OAM_HW_CTRL_CCM_ENA(0), VTSS_M_VOP_VOE_CONF_OAM_HW_CTRL_CCM_ENA);
        }
    }

    /* Enable of sticky for MEL low and DMAC error and Version error on all PDU types. */
    /* If extract to CPU is enabled for this errors, all frames with this errors are send to CPU. Currently this is not the case */
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CPU_COPY_CTRL(voe_idx), VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_PDU_ERR_EXTRACT_CCM_ONLY(0), VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_PDU_ERR_EXTRACT_CCM_ONLY);

    /* Enable/Disable VOE */
    JR2_WRM(VTSS_VOP_VOE_CONF_VOE_CTRL(voe_idx), VTSS_F_VOP_VOE_CONF_VOE_CTRL_VOE_ENA(conf->enable ? 1 : 0), VTSS_M_VOP_VOE_CONF_VOE_CTRL_VOE_ENA);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_cc_conf_set(vtss_state_t              *vtss_state,
                                   const vtss_voe_idx_t      voe_idx,
                                   const vtss_voe_cc_conf_t  *const conf)
{
    u32                 i, value, mask;
    const u8            *p;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure the CPU copy */
    mask = VTSS_M_VOP_VOE_STAT_AUTO_HIT_ME_ONCE_HMO_CCM_RX_CCM_NXT      |   /* mask for VTSS_VOP_VOE_STAT_AUTO_HIT_ME_ONCE register */
           VTSS_M_VOP_VOE_STAT_AUTO_HIT_ME_ONCE_HMO_CCM_RX_TLV_NON_ZERO |
           VTSS_M_VOP_VOE_STAT_AUTO_HIT_ME_ONCE_HMO_CCM_RX_BAD_NXT;
    switch (conf->cpu_copy) {
    case VTSS_OAM_CPU_COPY_ALL:     /* Configure the CPU copy ALL */
        JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CPU_COPY_CTRL(voe_idx), VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA(conf->enable ? 1 : 0), VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_WRM(VTSS_VOP_VOE_STAT_AUTO_HIT_ME_ONCE(voe_idx), 0, mask);
#endif
        break;
    case VTSS_OAM_CPU_COPY_AUTO:    /* Configure the CPU copy AUTO */
        JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CPU_COPY_CTRL(voe_idx), VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA(0), VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
        value = conf->enable ? (VTSS_F_VOP_VOE_STAT_AUTO_HIT_ME_ONCE_HMO_CCM_RX_CCM_NXT(1)     |
                                VTSS_F_VOP_VOE_STAT_AUTO_HIT_ME_ONCE_HMO_CCM_RX_TLV_NON_ZERO(1) |
                                VTSS_F_VOP_VOE_STAT_AUTO_HIT_ME_ONCE_HMO_CCM_RX_BAD_NXT(1)) : 0;
        JR2_WRM(VTSS_VOP_VOE_STAT_AUTO_HIT_ME_ONCE(voe_idx), value, mask);
#endif
        break;
    case VTSS_OAM_CPU_COPY_NONE:    /* Configure the CPU copy NONE */
        JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CPU_COPY_CTRL(voe_idx), VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA(0), VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_WRM(VTSS_VOP_VOE_STAT_AUTO_HIT_ME_ONCE(voe_idx), 0, mask);
#endif
        break;
    }
#if !defined(VTSS_ARCH_JAGUAR_2_B)
    JR2_WR(VTSS_VOP_VOE_STAT_PDU_EXTRACT(voe_idx), 0);
#endif

    /* Clear sequence numbers and counters */
    JR2_RD(VTSS_VOP_VOE_CONF_OAM_HW_CTRL(voe_idx), &value);
    if (conf->enable && (VTSS_X_VOP_VOE_CONF_OAM_HW_CTRL_CCM_ENA(value) == 0)) {    /* CC is just enabled so clear */
        JR2_WR(VTSS_VOP_VOE_STAT_CCM_TX_SEQ_CFG(voe_idx), 0);
        JR2_WR(VTSS_VOP_VOE_STAT_CCM_RX_SEQ_CFG(voe_idx), 0);
        VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_CCM | VTSS_OAM_CNT_DIR_BOTH));
    }

    /* Configure seq_no_update, prio, period */
    value = (VTSS_F_VOP_VOE_CONF_CCM_CFG_CCM_SEQ_UPD_ENA((vtss_state->oam.voe_rdi_conf[voe_idx] || conf->seq_no_update) ? 1 : 0)  |
             VTSS_F_VOP_VOE_CONF_CCM_CFG_CCM_RX_SEQ_CHK_ENA(1)                                                                    |
             VTSS_F_VOP_VOE_CONF_CCM_CFG_CCM_PRIO(conf->expected_priority)                                                        |
             VTSS_F_VOP_VOE_CONF_CCM_CFG_CCM_PERIOD(loc_period_value(conf->expected_period))                                      |
             VTSS_F_VOP_VOE_CONF_CCM_CFG_CCM_MEGID_CHK_ENA(1)                                                                     |
             VTSS_F_VOP_VOE_CONF_CCM_CFG_CCM_MEPID_CHK_ENA(1));
    JR2_WR(VTSS_VOP_VOE_CONF_CCM_CFG(voe_idx), value);

    /* Configure MEG id */
    p = &conf->expected_megid[47];    // MSB
    for (i = 0; i < 12; ++i, p -= 4) {
        value = (*(p - 3) << 24) | (*(p - 2) << 16) | (*(p - 1) <<  8) | (*(p - 0));
        JR2_WR(VTSS_VOP_VOE_CONF_CCM_MEGID_CFG(voe_idx, i), value);
    }

    /* Configure count_as_selected */
    value = VTSS_F_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA((conf->enable && conf->count_as_selected) ? 1 : 0);
    mask = VTSS_M_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA;
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CNT_OAM_CTRL(voe_idx), value, mask);

#if defined(VTSS_ARCH_JAGUAR_2_B)
    /* Configure peer MEP id */
    JR2_WR(VTSS_VOP_VOE_CONF_CCM_MEPID_CFG(voe_idx), VTSS_F_VOP_VOE_CONF_CCM_MEPID_CFG_CCM_MEPID(conf->expected_peer_mepid));
#else
    /* Configure peer MEP id */
    JR2_WR(VTSS_VOP_VOE_CONF_PEER_MEPID_CFG(voe_idx), VTSS_F_VOP_VOE_CONF_PEER_MEPID_CFG_PEER_MEPID(conf->expected_peer_mepid));
#endif

    /* Enable/Disable CCM handling */
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_HW_CTRL(voe_idx), VTSS_F_VOP_VOE_CONF_OAM_HW_CTRL_CCM_ENA(conf->enable ? 1 : 0), VTSS_M_VOP_VOE_CONF_OAM_HW_CTRL_CCM_ENA);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_cc_rdi_set(vtss_state_t          *vtss_state,
                                  const vtss_voe_idx_t  voe_idx,
                                  const BOOL            rdi)
{
    u32 value, mask;

    VTSS_D("Enter  voe_idx %u  rdi %u", voe_idx, rdi);

    JR2_WRM(VTSS_VOP_VOE_STAT_CCM_STAT(voe_idx), VTSS_F_VOP_VOE_STAT_CCM_STAT_CCM_TX_RDI(rdi), VTSS_M_VOP_VOE_STAT_CCM_STAT_CCM_TX_RDI);

    /* Seems that sequence number update must be enabled in order to set the RDI bit */
    value = VTSS_F_VOP_VOE_CONF_CCM_CFG_CCM_SEQ_UPD_ENA((rdi || vtss_state->oam.voe_cc_conf[voe_idx].seq_no_update) ? 1 : 0);
    mask = VTSS_M_VOP_VOE_CONF_CCM_CFG_CCM_SEQ_UPD_ENA;
    JR2_WRM(VTSS_VOP_VOE_CONF_CCM_CFG(voe_idx), value, mask);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_cc_cpu_copy_next_set(vtss_state_t          *vtss_state,
                                            const vtss_voe_idx_t  voe_idx)
{
    u32 value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    value = VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE(1)         |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_CCM_RX_CCM_NXT_EXTR(1) |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_CCM_ZERO_PERIOD_RX_ERR_EXTR(1) |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_RX_MEL_LOW_ERR_EXTR(1) |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_DMAC_RX_ERR_EXTR(1) |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_PDU_VERSION_RX_ERR_EXTR(1) |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_CCM_MEGID_RX_ERR_EXTR(1)       |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_CCM_MEPID_RX_ERR_EXTR(1)       |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_CCM_PERIOD_RX_ERR_EXTR(1)      |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_CCM_PRIO_RX_ERR_EXTR(1)        |
            VTSS_F_VOP_VOE_STAT_PDU_EXTRACT_CCM_RX_TLV_NON_ZERO_EXTR(1);
    JR2_WR(VTSS_VOP_VOE_STAT_PDU_EXTRACT(voe_idx), value);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_lt_conf_set(vtss_state_t               *vtss_state,
                                   const vtss_voe_idx_t       voe_idx,
                                   const vtss_voe_lt_conf_t   *const conf)
{
    u32  value, mask;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure copy to CPU */
    value = VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA((conf->enable && conf->ltm_cpu_copy) ? 1 : 0) |
            VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA((conf->enable && conf->ltr_cpu_copy) ? 1 : 0);
    mask = VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA | VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA;
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CPU_COPY_CTRL(voe_idx), value, mask);

    /* Configure count_as_selected */
    value = VTSS_F_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA((conf->enable && conf->count_as_selected) ? 1 : 0) |
            VTSS_F_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA((conf->enable && conf->count_as_selected) ? 1 : 0);
    mask = VTSS_M_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA | VTSS_M_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA;
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CNT_OAM_CTRL(voe_idx), value, mask);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_lb_conf_set(vtss_state_t               *vtss_state,
                                   const vtss_voe_idx_t       voe_idx,
                                   const vtss_voe_lb_conf_t   *const conf)
{
    u32  value, mask, transaction_id;
    BOOL doing_lb = 0, doing_tst;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure copy to CPU */
    value = VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA((conf->enable && conf->lbm_cpu_copy) ? 1 : 0) |
            VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA((conf->enable && conf->lbr_cpu_copy) ? 1 : 0);
    mask = VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA | VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA;
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CPU_COPY_CTRL(voe_idx), value, mask);

    /* Configure count_as_selected */
    value = VTSS_F_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA(conf->count_as_selected ? 1 : 0) |
            VTSS_F_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA(conf->count_as_selected ? 1 : 0);
    mask = VTSS_M_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA | VTSS_M_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA;
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CNT_OAM_CTRL(voe_idx), value, mask);

    /* Configure transaction id */
    value = VTSS_F_VOP_VOE_CONF_TX_TRANSID_UPDATE_TST_UPDATE_ENA(conf->enable ? 1 : 0) | VTSS_F_VOP_VOE_CONF_TX_TRANSID_UPDATE_LBM_UPDATE_ENA(conf->enable ? 1 : 0);
    JR2_WR(VTSS_VOP_VOE_CONF_TX_TRANSID_UPDATE(voe_idx), value);
    if (conf->trans_id != VTSS_VOE_LBM_TRANSACTION_ID_NONE) {
        transaction_id = (conf->trans_id == 0) ? 1 : conf->trans_id;
        JR2_WR(VTSS_VOP_VOE_STAT_LBM_TX_TRANSID_CFG(voe_idx), transaction_id);
        JR2_WR(VTSS_VOP_VOE_STAT_LBR_RX_TRANSID_CFG(voe_idx), transaction_id - 1);
        vtss_cmn_counter_32_rebase(transaction_id, &vtss_state->oam.voe_internal[voe_idx].counters.lb.tx_lbm_counter);    /* Always re-base when transaction id is changed */
    }

    VTSS_RC(doing_calculate(vtss_state, voe_idx, &doing_lb, &doing_tst));

    /* Enable/Disable LBM/LBR handling */
    JR2_WR(VTSS_VOP_VOE_CONF_LOOPBACK_ENA(voe_idx), VTSS_F_VOP_VOE_CONF_LOOPBACK_ENA_LB_LBM_ENA(conf->enable ? 1 : 0));
    value = VTSS_F_VOP_VOE_CONF_OAM_HW_CTRL_LBM_ENA(conf->enable ? 1 : 0) | 
            VTSS_F_VOP_VOE_CONF_OAM_HW_CTRL_LBR_ENA(conf->enable ? 1 : 0) |
            VTSS_F_VOP_VOE_CONF_OAM_HW_CTRL_LBR_TLV_CRC_VERIFY_ENA(conf->enable ? 1 : 0);
    mask = VTSS_M_VOP_VOE_CONF_OAM_HW_CTRL_LBM_ENA | VTSS_M_VOP_VOE_CONF_OAM_HW_CTRL_LBR_ENA | VTSS_M_VOP_VOE_CONF_OAM_HW_CTRL_LBR_TLV_CRC_VERIFY_ENA;
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_HW_CTRL(voe_idx), value, mask);

    if (conf->enable && !doing_lb) {    /* In case LB is just enabled counters are cleared */
        VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_LB | VTSS_OAM_CNT_DIR_BOTH));
    }

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_laps_conf_set(vtss_state_t                 *vtss_state,
                                     const vtss_voe_idx_t         voe_idx,
                                     const vtss_voe_laps_conf_t   *const conf)
{
    u32  value, mask;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure CPU copy */
    /* Generic [GENERIC_OFFSET_LAPS] is used for LAPS */
    value = VTSS_F_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_GENERIC_COPY_MASK((conf->enable && conf->cpu_copy) ? GENERIC_MASK_LAPS : 0);
    mask = VTSS_M_VOP_VOE_CONF_OAM_CPU_COPY_CTRL_GENERIC_COPY_MASK;
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CPU_COPY_CTRL(voe_idx), value, mask);

    /* Configure count_as_selected */
    /* Generic [GENERIC_OFFSET_LAPS] is used for LAPS */
    value = VTSS_F_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK((conf->enable && conf->count_as_selected) ? GENERIC_MASK_LAPS : 0);
    mask = VTSS_M_VOP_VOE_CONF_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK;
    JR2_WRM(VTSS_VOP_VOE_CONF_OAM_CNT_OAM_CTRL(voe_idx), value, mask);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_status_get(vtss_state_t          *vtss_state,
                                  const vtss_voe_idx_t  voe_idx,
                                  vtss_voe_status_t     *const status)
{
    u32 value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    JR2_RD(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), &value);
    status->opcode_unexp_seen  = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY) != 0;
    status->dmac_unexp_seen    = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_DMAC_RX_ERR_STICKY) != 0;
    status->version_unexp_seen = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_PDU_VERSION_RX_ERR_STICKY) != 0;
    status->rx_level_low_seen  = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_RX_MEL_LOW_BLOCK_STICKY) != 0;
    status->rx_level_high_seen = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_RX_MEL_HIGH_BLOCK_STICKY) != 0;

    /* Clear the RX sticky bits that has been detected */
    value = value &
            (VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY       |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_DMAC_RX_ERR_STICKY         |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_PDU_VERSION_RX_ERR_STICKY  |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_RX_MEL_LOW_BLOCK_STICKY    |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_RX_MEL_HIGH_BLOCK_STICKY);
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), value);

    /* Calculate the 'xxx_seen' - read the TX sticky bits */
    JR2_RD(VTSS_VOP_VOE_STAT_OAM_TX_STICKY(voe_idx), &value);
    status->tx_level_low_seen  = (value & VTSS_M_VOP_VOE_STAT_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY) != 0;

    /* Clear the TX sticky bits that has been detected */
    value = value &
            (VTSS_M_VOP_VOE_STAT_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY);
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_TX_STICKY(voe_idx), value);

    return VTSS_RC_OK;
}

static vtss_rc jr2_voe_cc_status_get(vtss_state_t          *vtss_state,
                                     const vtss_voe_idx_t  voe_idx,
                                     vtss_voe_cc_status_t  *status)
{
    u32 value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate CCM received status */
    JR2_RD(VTSS_VOP_VOE_STAT_CCM_RX_LAST(voe_idx), &value);
    status->zero_period     = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_ZERO_PERIOD_ERR(value) != 0;
    status->rdi             = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_RX_RDI(value)          != 0;
    status->loc             = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_LOC_DEFECT(value)      != 0;
    status->period_unexp    = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_PERIOD_ERR(value)      != 0;
    status->priority_unexp  = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_PRIO_ERR(value)        != 0;
    status->mep_id_unexp    = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_MEPID_ERR(value)       != 0;
    status->meg_id_unexp    = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_MEGID_ERR(value)       != 0;
    status->mel_unexp       = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_RX_MEL_LOW_ERR(value)  != 0;
    status->rx_port         = vtss_api_port(vtss_state, VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_CCM_RX_SRC_PORT(value));
#if !defined(VTSS_ARCH_JAGUAR_2_B)
    status->port_status_tlv = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_TLV_PORT_STATUS(value);
    status->if_status_tlv   = VTSS_X_VOP_VOE_STAT_CCM_RX_LAST_TLV_INTERFACE_STATUS(value);
#endif

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    JR2_RD(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), &value);
    status->seen           = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_CCM_RX_STICKY) != 0;
    status->tlv_seen       = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_CCM_RX_TLV_NON_ZERO_STICKY) != 0;
    status->seq_unexp_seen = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY) != 0;

    /* Clear the sticky bits that has been detected */
    value = value &
            (VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_CCM_RX_STICKY               |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_CCM_RX_TLV_NON_ZERO_STICKY  |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY);
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), value);

    return VTSS_RC_OK;
}

static vtss_rc jr2_voe_lt_status_get(vtss_state_t           *vtss_state,
                                     const vtss_voe_idx_t   voe_idx,
                                     vtss_voe_lt_status_t   *status)
{
    u32  value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    JR2_RD(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), &value);
    status->ltm_seen  = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LTM_RX_STICKY) != 0;
    status->ltr_seen  = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LTR_RX_STICKY) != 0;

    /* Clear the sticky bits that has been detected */
    value = value &
            (VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LTM_RX_STICKY  |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LTR_RX_STICKY);
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), value);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_lb_status_get(vtss_state_t           *vtss_state,
                                     const vtss_voe_idx_t   voe_idx,
                                     vtss_voe_lb_status_t   *status)
{
    u32  value;
    BOOL doing_lb = 0, doing_tst = 0;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    JR2_RD(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), &value);
    status->lbm_seen          = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LBM_RX_STICKY) != 0;
    status->lbr_seen          = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LBR_RX_STICKY) != 0;
    status->trans_unexp_seen  = (value & VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY) != 0;

    /* Clear the sticky bits that has been detected */
    value = value &
            (VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LBM_RX_STICKY           |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY  |
             VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_LBR_RX_STICKY);
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), value);

    /* Get the LBM and LBR transaction id's */
    VTSS_RC(doing_calculate(vtss_state, voe_idx, &doing_lb, &doing_tst));
    if (doing_lb) {
        JR2_RD(VTSS_VOP_VOE_STAT_LBM_TX_TRANSID_CFG(voe_idx), &status->tx_trans_id);
        JR2_RD(VTSS_VOP_VOE_STAT_LBR_RX_TRANSID_CFG(voe_idx), &status->rx_trans_id);
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_voe_laps_status_get(vtss_state_t             *vtss_state,
                                       const vtss_voe_idx_t     voe_idx,
                                       vtss_voe_laps_status_t   *status)
{
    u32  value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    /* Generic [GENERIC_OFFSET_LAPS] is used for LAPS */
    JR2_RD(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), &value);
    status->seen  = (VTSS_X_VOP_VOE_STAT_OAM_RX_STICKY_GENERIC_RX_STICKY_MASK(value) & GENERIC_MASK_LAPS) != 0;

    /* Clear the sticky bits that has been detected */
    value = value &
            (VTSS_M_VOP_VOE_STAT_OAM_RX_STICKY_GENERIC_RX_STICKY_MASK);
    JR2_WR(VTSS_VOP_VOE_STAT_OAM_RX_STICKY(voe_idx), value);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_counters_get(vtss_state_t         *vtss_state,
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
    counters->rx_discard_counter  = chipcnt->voe.rx_discard_counter.value;
    counters->tx_discard_counter  = chipcnt->voe.tx_discard_counter.value;

    return rc;
}

static vtss_rc jr2_voe_cc_counters_get(vtss_state_t           *vtss_state,
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

static vtss_rc jr2_voe_lb_counters_get(vtss_state_t           *vtss_state,
                                       const vtss_voe_idx_t   voe_idx,
                                       vtss_voe_lb_counters_t *counters)
{
    vtss_rc                           rc;
    vtss_oam_voe_internal_counters_t  *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Poll so we get the most recent counter values */
    rc = voe_counter_update(vtss_state, voe_idx, 0);

    /* Get the counters */
    counters->rx_lbr_counter     = chipcnt->lb.rx_lbr_counter.value;
    counters->rx_lbr_oo_counter  = chipcnt->lb.rx_lbr_oo_counter.value;
    counters->rx_lbr_crc_counter = chipcnt->lb.rx_lbr_crc_counter.value;
    counters->tx_lbm_counter     = chipcnt->lb.tx_lbm_counter.value;
    counters->tx_lbr_counter     = chipcnt->lb.tx_lbr_counter.value;

    return rc;
}

static vtss_rc jr2_voe_counters_clear(vtss_state_t          *vtss_state,
                                      const vtss_voe_idx_t  voe_idx)
{
    VTSS_D("Enter  voe_idx %u", voe_idx);

    VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_VOE | VTSS_OAM_CNT_DIR_BOTH));

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_cc_counters_clear(vtss_state_t          *vtss_state,
                                         const vtss_voe_idx_t  voe_idx)
{
    VTSS_D("Enter  voe_idx %u", voe_idx);

    VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_CCM | VTSS_OAM_CNT_DIR_BOTH));

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voe_lb_counters_clear(vtss_state_t          *vtss_state,
                                         const vtss_voe_idx_t  voe_idx)
{
    VTSS_D("Enter  voe_idx %u", voe_idx);

    VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_LB | VTSS_OAM_CNT_DIR_BOTH));

    return (VTSS_RC_OK);
}

static u32 down_voi_alloc_offset = 0, up_voi_alloc_offset = 0;
static vtss_rc jr2_voi_alloc(vtss_state_t                *vtss_state,
                             const vtss_port_no_t        port,
                             const vtss_oam_direction_t  direction,
                             vtss_voi_idx_t              *const voi_idx)
{
    u32 i, start, count, *alloc_offset;

    VTSS_D("Enter  direction %u", direction);

    if (direction == VTSS_OAM_DIRECTION_DOWN) {
        start = 0;                      /* voi_idx == 0 is the first Down-VOI */
        count = VTSS_DOWN_VOI_CNT;
        alloc_offset = &down_voi_alloc_offset;
    } else {
        start = VTSS_DOWN_VOI_CNT;      /* voi_idx == VTSS_DOWN_VOI_CNT is the first Up-VOI */
        count = VTSS_UP_VOI_CNT;
        alloc_offset = &up_voi_alloc_offset;
    }

    for (i = 0; i < count && vtss_state->oam.voi_alloc_data[start + *alloc_offset].allocated; ++i) {
        *alloc_offset = (*alloc_offset + 1) % count;
    }
    if (i == count) {
        VTSS_E("No free %s VOI to allocate", (direction == VTSS_OAM_DIRECTION_DOWN) ? "Down" : "Up");
        return VTSS_RC_ERROR;
    }

    *voi_idx = start + *alloc_offset;

    vtss_state->oam.voi_alloc_data[*voi_idx].allocated = TRUE;
    vtss_state->oam.voi_alloc_data[*voi_idx].port = port;
    vtss_state->oam.voi_alloc_data[*voi_idx].direction = direction;

    VTSS_D("Exit  voi_idx %u", *voi_idx);

    return (VTSS_RC_OK);
}

static vtss_rc jr2_voi_free(vtss_state_t            *vtss_state,
                            const vtss_voi_idx_t    voi_idx)
{
    vtss_voi_alloc_t  *alloc_data;

    VTSS_D("Enter  voi_idx %u", voi_idx);

    if (voi_idx >= VTSS_VOI_CNT) {
        VTSS_E("Invalid  voi_idx %u", voi_idx);
        return (VTSS_RC_ERROR);
    }

    alloc_data = &vtss_state->oam.voi_alloc_data[voi_idx];

    if (!alloc_data->allocated) {
        VTSS_D("VOI not allocated  voi_idx %u", voi_idx);
        return (VTSS_RC_OK);
    }
    alloc_data->allocated = FALSE;

    return (voi_default_set(vtss_state, voi_idx));
}

static vtss_rc jr2_voi_conf_set(vtss_state_t            *vtss_state,
                                const vtss_voi_idx_t    voi_idx,
                                const vtss_voi_conf_t   *const conf)
{
    u32               value, mask, mip_idx;
    vtss_voi_alloc_t  *alloc_data;

    VTSS_D("Enter  voi_idx %u", voi_idx);

    if (voi_idx >= VTSS_VOI_CNT) {
        VTSS_E("Invalid  voi_idx %u", voi_idx);
        return (VTSS_RC_ERROR);
    }

    alloc_data = &vtss_state->oam.voi_alloc_data[voi_idx];
    mip_idx = vtss_j2_voi_idx_to_mip_idx(voi_idx);

    if (alloc_data->direction == VTSS_OAM_DIRECTION_DOWN) {
        value = conf->enable ? (VTSS_F_ANA_CL_MIP_TBL_MIP_CFG_MEL_VAL(conf->meg_level)                           |
                                VTSS_F_ANA_CL_MIP_TBL_MIP_CFG_LBM_REDIR_ENA(conf->lbm_cpu_redir ? 1 : 0)         |
                                VTSS_F_ANA_CL_MIP_TBL_MIP_CFG_LTM_REDIR_ENA(conf->ltm_cpu_redir ? 1 : 0)         |
                                VTSS_F_ANA_CL_MIP_TBL_MIP_CFG_RAPS_CFG(raps_handling_value(conf->raps_handling)) |
                                VTSS_F_ANA_CL_MIP_TBL_MIP_CFG_PIPELINE_PT(0)) : 0;      /* Currently only inner MIP is supported */
        mask = VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_MEL_VAL        |
               VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_LBM_REDIR_ENA  |
               VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_LTM_REDIR_ENA  |
               VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_RAPS_CFG       |
               VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_PIPELINE_PT;
        JR2_WRM(VTSS_ANA_CL_MIP_TBL_MIP_CFG(mip_idx), value, mask);

        value = VTSS_F_ANA_CL_MIP_TBL_LBM_MAC_HIGH_LBM_MAC_HIGH((conf->unicast_mac.addr[0] << 8) | conf->unicast_mac.addr[1]);
        JR2_WR(VTSS_ANA_CL_MIP_TBL_LBM_MAC_HIGH(mip_idx), value);
        value = (conf->unicast_mac.addr[2] << 24) | (conf->unicast_mac.addr[3] << 16) | (conf->unicast_mac.addr[4] << 8) | conf->unicast_mac.addr[5];
        JR2_WR(VTSS_ANA_CL_MIP_TBL_LBM_MAC_LOW(mip_idx), value);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_WR(VTSS_ANA_CL_MIP_TBL_CCM_HMO_CTRL(mip_idx), 0);
        JR2_WR(VTSS_ANA_CL_MIP_TBL_MIP_CL_VID_CTRL(mip_idx), 0);
#endif
    } else {
        value = conf->enable ? (VTSS_F_REW_MIP_TBL_MIP_CFG_MEL_VAL(conf->meg_level)                           |
                                VTSS_F_REW_MIP_TBL_MIP_CFG_LBM_REDIR_ENA(conf->lbm_cpu_redir ? 1 : 0)         |
                                VTSS_F_REW_MIP_TBL_MIP_CFG_LTM_REDIR_ENA(conf->ltm_cpu_redir ? 1 : 0)         |
                                VTSS_F_REW_MIP_TBL_MIP_CFG_RAPS_CFG(raps_handling_value(conf->raps_handling)) |
                                VTSS_F_REW_MIP_TBL_MIP_CFG_PIPELINE_PT(0)) : 0;      /* Currently only inner MIP is supported */
        mask = VTSS_M_REW_MIP_TBL_MIP_CFG_MEL_VAL        |
               VTSS_M_REW_MIP_TBL_MIP_CFG_LBM_REDIR_ENA  |
               VTSS_M_REW_MIP_TBL_MIP_CFG_LTM_REDIR_ENA  |
               VTSS_M_REW_MIP_TBL_MIP_CFG_RAPS_CFG       |
               VTSS_M_REW_MIP_TBL_MIP_CFG_PIPELINE_PT;
        JR2_WRM(VTSS_REW_MIP_TBL_MIP_CFG(mip_idx), value, mask);

        value = VTSS_F_REW_MIP_TBL_LBM_MAC_HIGH_LBM_MAC_HIGH((conf->unicast_mac.addr[0] << 8) | conf->unicast_mac.addr[1]);
        JR2_WR(VTSS_REW_MIP_TBL_LBM_MAC_HIGH(mip_idx), value);
        value = (conf->unicast_mac.addr[2] << 24) | (conf->unicast_mac.addr[3] << 16) | (conf->unicast_mac.addr[4] << 8) | conf->unicast_mac.addr[5];
        JR2_WR(VTSS_REW_MIP_TBL_LBM_MAC_LOW(mip_idx), value);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_WR(VTSS_REW_MIP_TBL_CCM_HMO_CTRL(mip_idx), 0);
        JR2_WR(VTSS_REW_MIP_TBL_MIP_VID_CTRL(mip_idx), 0);
#endif
    }

    return (VTSS_RC_OK);
}




/* - Debug print --------------------------------------------------- */
/* - Debug print --------------------------------------------------- */
/* - Debug print --------------------------------------------------- */
/* - Debug print --------------------------------------------------- */

// D_COM: Debug COMmon; DR_COM: Debug Read COMmon. _I for Instance. Etc.
#define D_COM(pr, name)            vtss_jr2_debug_reg(vtss_state, pr, VTSS_VOP_COMMON_##name,                    "COMMON:"#name)
#define D_COM_I(pr, name, i)       vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_VOP_COMMON_##name(i),      (i),  "COMMON:"#name)
#define D_VOE_I(pr, name, i)       vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_VOP_VOE_##name(i),         (i),  "VOE:"#name)
#define D_VOE_II(pr, name, i1, i2) vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_VOP_VOE_##name((i1),(i2)), (i2), "VOE:"#name)
#define DR_COM(name, v)            { JR2_RD(VTSS_VOP_COMMON_##name, &v); }
#define DR_COM_I(name, i, v)       { JR2_RD(VTSS_VOP_COMMON_##name(i), &v); }
#define DR_VOE_I(name, i, v)       { JR2_RD(VTSS_VOP_VOE_##name(i), &v); }
#define DR_VOE_II(name, i1, i2, v) { JR2_RD(VTSS_VOP_VOE_##name((i1),(i2)), &v); }
#define D_D_MIP_I(pr, name, i)       vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_MIP_TBL_##name(i),         (i),  "DOWN_MIP:"#name)
#define D_U_MIP_I(pr, name, i)       vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_REW_MIP_TBL_##name(i),         (i),  "UP_MIP:"#name)
#define D_D_MIP_S(pr, name)       vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_CL_STICKY_##name,  "DOWN_MIP:"#name)
#define D_U_MIP_S(pr, name)       vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_COMMON_##name,  "UP_MIP:"#name)

static vtss_rc jr2_debug_oam(vtss_state_t               *vtss_state,
                             const vtss_debug_printf_t  pr,
                             const vtss_debug_info_t    *const info)
{
    u32               i, k, v, w, voe_ctrl, voe_idx, div, tx_counter, rx_counter, voe_cnt, umip_cnt, dmip_cnt;
    char              buf[32];
    BOOL              show, vop, voe, status, clm, es0, isdx, lm_counters, d_mip, u_mip, mip_status, resources;

    div = 0;
    voe_idx = 0;
    tx_counter = 0;
    rx_counter = 0;
    voe_cnt = umip_cnt = dmip_cnt = 0;
    show = vop = voe = status = clm = es0 = isdx = lm_counters = d_mip = u_mip = mip_status = resources = FALSE;

    VTSS_D("has_action %u  action %u", info->has_action, info->action);

    if (info->has_action) { /* Action parameter is present */
        show = (info->action == 0) ? TRUE : FALSE;
        vop = (info->action == 1) ? TRUE : FALSE;
        mip_status = (info->action == 2) ? TRUE : FALSE;
        resources = (info->action == 3) ? TRUE : FALSE;

        if (info->action > 3) { /* This potentially a VOE config or VOE status action */
            for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
                voe = (info->action / div == 4) ? TRUE : FALSE;
                status = (info->action / div == 5) ? TRUE : FALSE;
                lm_counters = (info->action / div == 6) ? TRUE : FALSE;
                d_mip = (info->action / div == 7) ? TRUE : FALSE;
                u_mip = (info->action / div == 8) ? TRUE : FALSE;
                if (voe || status || lm_counters || d_mip || u_mip) {
                    break;
                }
            }
            if (voe || status || lm_counters || d_mip || u_mip) {    /* Calculate the possible VOE/MIP index */
                voe_idx = info->action % div;
            }
        }
    }

    VTSS_D("show %u  vop %u  voe %u  status %u  lm_counters %u  d_mip %u  u_mip %u  clm %u  es0 %u  isdx %u  mip_status  %u", show, vop, voe, status, lm_counters, d_mip, u_mip, clm, es0, isdx, mip_status);

    if (show) {
        pr("OAM Debug Group action:\n");
        pr("    0: Show possible actions\n");
        pr("    1: Print VOP configurations\n");
        pr("    2: Print MIP status.\n");
        pr("    3: Print allocated resources\n");
        pr("    4XXXX: Print VOE XXXX configurations. Without XXXX all VOEs are printed\n");
        pr("    5XXXX: Print VOE XXXX status. Without XXXX all VOEs are printed\n");
        pr("    6XXXX: Print VOE XXXX LM counters. Without XXXX all VOEs are printed\n");
        pr("    7XXXX: Print Down-MIP XXXX configurations. Without XXXX all MIPs are printed\n");
        pr("    8XXXX: Print Up-MIP XXXX configurations. Without XXXX all MIPs are printed\n");
        pr("\n");
    }

    if (!info->has_action || vop) { /* VOP configuration must be printed */
        vtss_jr2_debug_reg_header(pr, "VOP");
        D_COM(pr, VOP_CTRL);
        D_COM(pr, CPU_EXTR_CFG);
        D_COM(pr, CPU_EXTR_CFG_1);
        D_COM(pr, VERSION_CTRL);
        D_COM(pr, VERSION_CTRL_2);
        for (i = 0; i < 8; ++i) {
            D_COM_I(pr, OAM_GENERIC_CFG, i);
        }
        D_COM(pr, LOC_CTRL);
        for (i = 0; i < 7; ++i) {
            D_COM_I(pr, LOC_PERIOD_CFG, i);
        }
#if !defined(VTSS_ARCH_JAGUAR_2_B)
        for (i = 0; i < 2; ++i) {
            D_COM_I(pr, HMO_PERIOD_CFG, i);
        }
        for (i = 0; i < 2; ++i) {
            D_COM_I(pr, HMO_FORCE_SLOT_CFG, i);
        }
        D_COM(pr, HMO_TIMER_CFG);
#endif
        D_COM(pr, LOC_SCAN_STICKY);
        D_COM(pr, MASTER_INTR_CTRL);
#if defined(VTSS_ARCH_SERVAL_T)
        D_COM(pr, VOE32_INTR);
#endif
#if defined(VTSS_ARCH_JAGUAR_2_C)
        for (i = 0; i < 2; ++i) {
            D_COM_I(pr, VOE32_INTR, i);
        }
#endif
        for (i = 0; i < 7; ++i) {
            D_COM_I(pr, INTR, i);
        }
        D_COM(pr, COMMON_MEP_MC_MAC_LSB);
        D_COM(pr, COMMON_MEP_MC_MAC_MSB);
        pr("\n");
    } /* Print VOP configurations */

    if (!info->has_action || voe) { /* VOE configuration must be printed */
        for (i = 0; i < VTSS_VOE_CNT; ++i) {
            if (voe && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }
            DR_VOE_I(CONF_VOE_CTRL, i, v);
            if (info->full  ||  (v & VTSS_M_VOP_VOE_CONF_VOE_CTRL_VOE_ENA) != 0) {
                VTSS_SPRINTF(buf, "VOE_CONF %u", i);
                vtss_jr2_debug_reg_header(pr, buf);
                DR_VOE_I(CONF_REG_VOE_MISC_CONFIG, i, w);
                D_VOE_I(pr, CONF_REG_VOE_MISC_CONFIG, i);
                D_VOE_I(pr, CONF_VOE_CTRL, i);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
                D_VOE_I(pr, CONF_VOE_MEPID_CFG, i);
                D_VOE_I(pr, CONF_PEER_MEPID_CFG, i);
#endif
                D_VOE_I(pr, CONF_SAM_COSID_SEQ_CFG, i);
                D_VOE_I(pr, CONF_SAM_NON_OAM_SEQ_CFG, i);
                D_VOE_I(pr, CONF_PATH_VOE_CFG, i);
                D_VOE_I(pr, CONF_OAM_CPU_COPY_CTRL, i);
                D_VOE_I(pr, CONF_PDU_VOE_PASS, i);
                D_VOE_I(pr, CONF_OAM_CNT_OAM_CTRL, i);
                D_VOE_I(pr, CONF_OAM_CNT_DATA_CTRL, i);
                D_VOE_I(pr, CONF_MEP_UC_MAC_LSB, i);
                D_VOE_I(pr, CONF_MEP_UC_MAC_MSB, i);
                D_VOE_I(pr, CONF_OAM_HW_CTRL, i);
                D_VOE_I(pr, CONF_LOOPBACK_ENA, i);
                D_VOE_I(pr, CONF_LOOPBACK_CFG, i);
                D_VOE_I(pr, CONF_TX_TRANSID_UPDATE, i);
                D_VOE_I(pr, CONF_CCM_CFG, i);
                for (k = 0; k < 12; ++k) {
                    D_VOE_II(pr, CONF_CCM_MEGID_CFG, i, k);
                }
                D_VOE_I(pr, CONF_SLM_CONFIG, i);
                D_VOE_I(pr, CONF_SLM_TEST_ID, i);
                for (k = 0; k < 12; ++k) {
                    D_VOE_II(pr, CONF_SLM_PEER_LIST, i, k);
                }
#if defined(VTSS_ARCH_JAGUAR_2_CE) && !defined(VTSS_ARCH_JAGUAR_2_B)
                if (v & VTSS_M_VOP_VOE_CONF_VOE_CTRL_G_8113_1_ENA) {
                    D_VOE_I(pr, CONF_G_8113_1_CFG, i);
                    D_VOE_I(pr, CONF_G_8113_1_REMOTE_MIPID, i);
                    D_VOE_I(pr, CONF_G_8113_1_REMOTE_MIPID1, i);
                    D_VOE_I(pr, CONF_G_8113_1_REMOTE_MIPID2, i);
                    D_VOE_I(pr, CONF_G_8113_1_REMOTE_MIPID3, i);
                }
#endif
            }
        }
        pr("\n");
    } /* Print VOE configurations */

    if (!info->has_action || status) { /* VOE status must be printed */
        for (i = 0; i < VTSS_VOE_CNT; ++i) {
            if (status && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }
            DR_VOE_I(CONF_VOE_CTRL, i, v);
            DR_VOE_I(CONF_REG_VOE_MISC_CONFIG, i, w);
            if (info->full  ||  (v & VTSS_M_VOP_VOE_CONF_VOE_CTRL_VOE_ENA) != 0) {
                VTSS_SPRINTF(buf, "VOE_STAT %u", i);
                vtss_jr2_debug_reg_header(pr, buf);
                D_VOE_I(pr, STAT_RX_SEL_OAM_CNT, i);
                D_VOE_I(pr, STAT_RX_OAM_FRM_CNT, i);
                D_VOE_I(pr, STAT_TX_SEL_OAM_CNT, i);
                D_VOE_I(pr, STAT_TX_OAM_FRM_CNT, i);
                D_VOE_I(pr, STAT_CCM_RX_FRM_CNT, i);
                D_VOE_I(pr, STAT_CCM_TX_SEQ_CFG, i);
                D_VOE_I(pr, STAT_CCM_RX_SEQ_CFG, i);
                D_VOE_I(pr, STAT_CCM_RX_WARNING, i);
                D_VOE_I(pr, STAT_CCM_ERR, i);
                D_VOE_I(pr, STAT_CCM_RX_ERR_1, i);
                D_VOE_I(pr, STAT_LBM_TX_TRANSID_CFG, i);
                D_VOE_I(pr, STAT_LBR_TX_FRM_CNT, i);
                D_VOE_I(pr, STAT_LBR_RX_TRANSID_CFG, i);
                D_VOE_I(pr, STAT_LBR_RX_FRM_CNT, i);
                D_VOE_I(pr, STAT_LBR_RX_TRANSID_ERR_CNT, i);
                D_VOE_I(pr, STAT_DM_PDU_CNT, i);
                D_VOE_I(pr, STAT_LM_PDU_CNT, i);
                D_VOE_I(pr, STAT_TX_OAM_DISCARD, i);
                D_VOE_I(pr, STAT_RX_OAM_DISCARD, i);
                D_VOE_I(pr, STAT_PDU_EXTRACT, i);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
                D_VOE_I(pr, STAT_AUTO_HIT_ME_ONCE, i);
#endif
                D_VOE_I(pr, STAT_SYNLM_EXTRACT, i);
                D_VOE_I(pr, STAT_OAM_TX_STICKY, i);
                D_VOE_I(pr, STAT_OAM_RX_STICKY, i);
                D_VOE_I(pr, STAT_OAM_RX_STICKY2, i);
                D_VOE_I(pr, STAT_CCM_STAT, i);
                D_VOE_I(pr, STAT_CCM_RX_LAST, i);
                D_VOE_I(pr, STAT_INTR_STICKY, i);
                D_VOE_I(pr, STAT_INTR_ENA, i);
                D_VOE_I(pr, STAT_SLM_TX_FRM_CNT, i);
                D_VOE_I(pr, STAT_TX_OAM_DISCARD, i);
                D_VOE_I(pr, STAT_RX_OAM_DISCARD, i);
                D_VOE_I(pr, CCM_LM_CCM_TX_FCB_CFG, i);
                D_VOE_I(pr, CCM_LM_CCM_RX_FCB_CFG, i);
                D_VOE_I(pr, CRC_ERR_LBR_CRC_ERR_CNT, i);
            }
        }
        pr("\n");
    } /* Print VOE status */

    if (!info->has_action || lm_counters) { /* VOE LM counters must be printed */
        for (i = 0; i < VTSS_VOE_CNT; ++i) {
            if (lm_counters && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }
            DR_VOE_I(CONF_VOE_CTRL, i, voe_ctrl);
            if ((voe_ctrl & VTSS_M_VOP_VOE_CONF_VOE_CTRL_VOE_ENA) != 0) {  /* Only print for active VOEs */
                VTSS_SPRINTF(buf, "VOE_LM_COUNTERS %u", i);
                pr("VOE_LM_COUNTERS %u\n", i);
                pr("COS     TX counter      RX counter\n");
                for (k = 0; k < VTSS_PRIO_ARRAY_SIZE; ++k) { /* Print RX and TX count for each COS */
                    pr("%3u     ", k);
                    if ((voe_ctrl & VTSS_M_VOP_VOE_CONF_VOE_CTRL_UPMEP_ENA) != 0) { /* This an Up-MEP (Service instance) */
                        tx_counter = VTSS_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB((i * VTSS_PRIO_ARRAY_SIZE) + k);
                        rx_counter = VTSS_REW_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB((i * VTSS_PRIO_ARRAY_SIZE) + k);
                    } else {    /* This is Down-MEP */
                        if (i >= VTSS_PORT_VOE_BASE_IDX) {  /* This is port Down-MEP */
                            tx_counter = VTSS_REW_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB(((i - VTSS_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE) + k);
                            rx_counter = VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB(((i - VTSS_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE) + k);
                        } else {    /* This is a Service Down-MEP */
                            tx_counter = VTSS_REW_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB((i * VTSS_PRIO_ARRAY_SIZE) + k);
                            rx_counter = VTSS_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB((i * VTSS_PRIO_ARRAY_SIZE) + k);
                        }
                    }
                    JR2_RD(tx_counter, &v);
                    pr("%10u      ", v);
                    JR2_RD(rx_counter, &v);
                    pr("%10u\n", v);
                }
            }
        }
        pr("\n");
    } /* Print VOE LM counters */

    if (!info->has_action || resources) { /* Used resources must be printed */
        /* Print resource consumption */
        for (i = 0; i < VTSS_VOE_CNT; ++i) {
            DR_VOE_I(CONF_VOE_CTRL, i, v);
            if ((v & VTSS_M_VOP_VOE_CONF_VOE_CTRL_VOE_ENA) != 0) {
                voe_cnt++;
            }
        }
        for (i = 0; i < VTSS_DOWN_VOI_CNT; ++i) {
            JR2_RD(VTSS_ANA_CL_MIP_TBL_MIP_CFG(i), &v)
            if ((v & VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_LBM_REDIR_ENA) != 0) {
                dmip_cnt++;
            }
        }
        for (i = 1; i < (VTSS_UP_VOI_CNT + 1); ++i) {   /* Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB */
            JR2_RD(VTSS_REW_MIP_TBL_MIP_CFG(i), &v)
            if ((v & VTSS_M_REW_MIP_TBL_MIP_CFG_LBM_REDIR_ENA) != 0) {
                umip_cnt++;
            }
        }

        pr("Resource consumption:\n");
        pr("VOE: %u\n", voe_cnt);
        pr("UMIP: %u\n", umip_cnt);
        pr("DMIP: %u\n", dmip_cnt);
        pr("\n");
        pr("Maximum values:\n");
        pr("SERVICE-VOE-MAX: %u\n", VTSS_PATH_SERVICE_VOE_CNT);
        pr("PORT-VOE-MAX: %u\n", VTSS_PORT_VOE_CNT);
        pr("UP-MIP-MAX: %u\n", VTSS_UP_VOI_CNT);
        pr("DOWN-MIP-MAX: %u\n", VTSS_DOWN_VOI_CNT);
        pr("\n");
    } /* Print resource consumption */

    if (!info->has_action || d_mip) { /* Down-MIP must be printed */
        for (i = 0; i < VTSS_DOWN_VOI_CNT; ++i) {
            if (d_mip && (div > 1) && (voe_idx != i)) {   /* A specific Down-MIP must be printed - this is not the one */
                continue;
            }
            JR2_RD(VTSS_ANA_CL_MIP_TBL_MIP_CFG(i), &v)
#if defined(VTSS_ARCH_JAGUAR_2_C)
            if ((v & VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_LBM_REDIR_ENA) != 0) {  /* Only print for active MIPs */
                VTSS_SPRINTF(buf, "DOWN_MIP_CONF %u", i);
                vtss_jr2_debug_reg_header(pr, buf);
                D_D_MIP_I(pr, MIP_CFG, i);
                D_D_MIP_I(pr, CCM_HMO_CTRL, i);
                D_D_MIP_I(pr, MIP_CL_VID_CTRL, i);
                D_D_MIP_I(pr, LBM_MAC_HIGH, i);
                D_D_MIP_I(pr, LBM_MAC_LOW, i);
            }
#else
            if ((v & VTSS_M_ANA_CL_MIP_TBL_MIP_CFG_LBM_REDIR_ENA) != 0) {  /* Only print for active MIPs */
                VTSS_SPRINTF(buf, "DOWN_MIP_CONF %u", i);
                vtss_jr2_debug_reg_header(pr, buf);
                D_D_MIP_I(pr, MIP_CFG, i);
                D_D_MIP_I(pr, LBM_MAC_HIGH, i);
                D_D_MIP_I(pr, LBM_MAC_LOW, i);
            }
#endif
        }
    }

    if (!info->has_action || u_mip) { /* Up-MIP must be printed */
        for (i = 1; i < (VTSS_UP_VOI_CNT + 1); ++i) {   /* Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB */
            if (u_mip && (div > 1) && (voe_idx != i)) {   /* A specific Up-MIP must be printed - this is not the one */
                continue;
            }

            JR2_RD(VTSS_REW_MIP_TBL_MIP_CFG(i), &v)
#if defined(VTSS_ARCH_JAGUAR_2_C)
            if ((v & VTSS_M_REW_MIP_TBL_MIP_CFG_LBM_REDIR_ENA) != 0) {  /* Only print for active MIPs */
                VTSS_SPRINTF(buf, "UP_MIP_CONF %u", i);
                vtss_jr2_debug_reg_header(pr, buf);
                D_U_MIP_I(pr, MIP_CFG, i);
                D_U_MIP_I(pr, CCM_HMO_CTRL, i);
                D_U_MIP_I(pr, MIP_VID_CTRL, i);
                D_U_MIP_I(pr, LBM_MAC_HIGH, i);
                D_U_MIP_I(pr, LBM_MAC_LOW, i);
            }
#else
            if ((v & VTSS_M_REW_MIP_TBL_MIP_CFG_LBM_REDIR_ENA) != 0) {  /* Only print for active MIPs */
                VTSS_SPRINTF(buf, "UP_MIP_CONF %u", i);
                vtss_jr2_debug_reg_header(pr, buf);
                D_U_MIP_I(pr, MIP_CFG, i);
                D_U_MIP_I(pr, LBM_MAC_HIGH, i);
                D_U_MIP_I(pr, LBM_MAC_LOW, i);
            }
#endif
        }
    }

    if (!info->has_action || mip_status) { /* MIP status must be printed */
        VTSS_SPRINTF(buf, "DOWN_MIP_STAT");
        vtss_jr2_debug_reg_header(pr, buf);
        D_D_MIP_S(pr, MIP_STICKY);
        pr("\n");

        VTSS_SPRINTF(buf, "UP_MIP_STAT");
        vtss_jr2_debug_reg_header(pr, buf);
        D_U_MIP_S(pr, MIP_STICKY_EVENT);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_oam_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_OAM, jr2_debug_oam, vtss_state, pr, info);
}

#undef D_COM
#undef D_COM_I
#undef D_VOE_I
#undef D_VOE_II
#undef DR_COM
#undef DR_COM_I
#undef DR_VOE_I
#undef DR_VOE_II



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

    if ((rc = jr2_voe_event_mask_set(vtss_state, voe_idx, VTSS_VOE_EVENT_MASK_ALL, FALSE)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_cc_rdi_set(vtss_state, voe_idx, FALSE)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_cc_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_cc_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_lt_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_lt_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_lb_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_lb_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_laps_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_laps_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_counters_clear(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_cc_counters_clear(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_lb_counters_clear(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = jr2_voe_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }

    return(ret_rc);
}

static vtss_rc voi_default_set(vtss_state_t          *vtss_state,
                               const vtss_voe_idx_t  voe_idx)
{
    vtss_rc  rc;

    VTSS_MEMSET(&vtss_state->oam.voi_conf[voe_idx], 0, sizeof(vtss_state->oam.voi_conf[voe_idx]));

    rc = jr2_voi_conf_set(vtss_state, voe_idx, &vtss_state->oam.voi_conf[voe_idx]);

    return(rc);
}

static vtss_rc jr2_oam_voe_poll_1sec(vtss_state_t *vtss_state)
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

static vtss_rc jr2_init(vtss_state_t *vtss_state)
{
    /* All VOEs are disabled in hardware by default - Disable VOP */
    JR2_WR(VTSS_VOP_COMMON_VOP_CTRL, 0);

    /* Configure LOC periods used for CCM LOC: */
    JR2_WR(VTSS_VOP_COMMON_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_3_3_MS)), (     3333ULL * 1000) / LOC_BASE);
    JR2_WR(VTSS_VOP_COMMON_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_10_MS)),  (    10000ULL * 1000) / LOC_BASE);
    JR2_WR(VTSS_VOP_COMMON_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_100_MS)), (   100000ULL * 1000) / LOC_BASE);
    JR2_WR(VTSS_VOP_COMMON_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_1_SEC)),  (  1000000ULL * 1000) / LOC_BASE);
    JR2_WR(VTSS_VOP_COMMON_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_10_SEC)), ( 10000000ULL * 1000) / LOC_BASE);

    /* Configure LOC periods used for CCM LOC: */
    /* Configure LOC periods used for CCM-LM counter insertion (1 sec and 100 ms): */
    /* (must be configured with 2 x desired CCM-LM counter insertion period) */
    /* Use slightly slower CCM-LM counter insertion to make sure 1 sec and 100 ms CC frames always have LM counters inserted. */
    JR2_WR(VTSS_VOP_COMMON_LOC_PERIOD_CFG(lm_loc_period_index(VTSS_VOE_CCM_PERIOD_100_MS)), ( 2 * 99900ULL * 1000) / LOC_BASE); /* 2 x 100 ms */
    JR2_WR(VTSS_VOP_COMMON_LOC_PERIOD_CFG(lm_loc_period_index(VTSS_VOE_CCM_PERIOD_1_SEC)),  (2 * 999900ULL * 1000) / LOC_BASE); /* 2 x 1 sec */

    /* This is to make down VOE looping (ex. LBM->LBR) possible without port being member of the classified VLAN */
    JR2_WR(VTSS_ANA_ACL_VCAP_S2_VOE_LOOPBACK_CFG, 0);

    return VTSS_RC_OK;
}


vtss_rc vtss_jr2_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_oam_state_t *state = &vtss_state->oam;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->vop_conf_set = jr2_vop_conf_set;
        state->voe_event_active_get = jr2_voe_event_active_get;
        state->voe_event_mask_set = jr2_voe_event_mask_set;
        state->voe_event_get = jr2_voe_event_get;
        state->voe_alloc = jr2_voe_alloc;
        state->voe_free = jr2_voe_free;
        state->voe_conf_set = jr2_voe_conf_set;
        state->voe_cc_conf_set = jr2_voe_cc_conf_set;
        state->voe_cc_rdi_set = jr2_voe_cc_rdi_set;
        state->voe_cc_cpu_copy_next_set = jr2_voe_cc_cpu_copy_next_set;
        state->voe_lt_conf_set = jr2_voe_lt_conf_set;
        state->voe_lb_conf_set = jr2_voe_lb_conf_set;
        state->voe_laps_conf_set = jr2_voe_laps_conf_set;
        state->voe_status_get = jr2_voe_status_get;
        state->voe_cc_status_get = jr2_voe_cc_status_get;
        state->voe_lt_status_get = jr2_voe_lt_status_get;
        state->voe_lb_status_get = jr2_voe_lb_status_get;
        state->voe_laps_status_get = jr2_voe_laps_status_get;
        state->voe_counters_get = jr2_voe_counters_get;
        state->voe_cc_counters_get = jr2_voe_cc_counters_get;
        state->voe_lb_counters_get = jr2_voe_lb_counters_get;
        state->voe_counters_clear = jr2_voe_counters_clear;
        state->voe_cc_counters_clear = jr2_voe_cc_counters_clear;
        state->voe_lb_counters_clear = jr2_voe_lb_counters_clear;
        state->voi_alloc = jr2_voi_alloc;
        state->voi_free = jr2_voi_free;
        state->voi_conf_set = jr2_voi_conf_set;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(jr2_init(vtss_state));
        break;
    case VTSS_INIT_CMD_POLL:
        VTSS_RC(jr2_oam_voe_poll_1sec(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_VOP */

#endif /* VTSS_ARCH_JAGUAR_2 */
