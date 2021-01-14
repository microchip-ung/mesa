// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_MRP
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X) && defined(VTSS_FEATURE_MRP)

#define MRP_FWD_NOP     0
#define MRP_FWD_COPY    1
#define MRP_FWD_REDIR   2
#define MRP_FWD_DISC    3

#define CONFIG_TEST     0
#define CONFIG_ITEST    1

static vtss_rc mrp_counter_update(vtss_state_t         *vtss_state,
                                  const vtss_mrp_idx_t  mrp_idx,
                                  const u32             clear_mask)
{
/*
 * These macros will aid in reading and optionally clearing counter registers.
 * The clear operation will be triggered by matching the 'clear_mask' with both a
 * counter type (ctype) and a counter direction (cdir - TX or RX).
 */
#define CHIPREAD(reg, cnt) { REG_RD(reg, &v); vtss_cmn_counter_32_update(v, cnt, (clear_mask  != 0)); }

    vtss_mrp_data_t               *mrp_data = &vtss_state->mrp.data[mrp_idx];
    u32                           v;
    vtss_mrp_internal_counters_t  *p_chipcnt = &mrp_data->p_counters;
    vtss_mrp_internal_counters_t  *s_chipcnt = &mrp_data->s_counters;
    u32                           p_chip_port;
    u32                           s_chip_port;

    if (!mrp_data->active || (mrp_data->conf.p_port >= VTSS_PORTS) || (mrp_data->conf.s_port >= VTSS_PORTS)) {
        return VTSS_RC_OK;
    }

    p_chip_port = VTSS_CHIP_PORT(mrp_data->conf.p_port);
    s_chip_port = VTSS_CHIP_PORT(mrp_data->conf.s_port);

    /* P port counter update */
    CHIPREAD(MEP_TST_RX_CNT(p_chip_port), &p_chipcnt->tst_rx_count);
    CHIPREAD(MEP_ITST_RX_CNT(p_chip_port), &p_chipcnt->itst_rx_count);

    /* S port counter update */
    CHIPREAD(MEP_TST_RX_CNT(s_chip_port), &s_chipcnt->tst_rx_count);
    CHIPREAD(MEP_ITST_RX_CNT(s_chip_port), &s_chipcnt->itst_rx_count);

    return VTSS_RC_OK;
#undef CHIPREAD
}

static void mrp_instance_default(vtss_state_t *vtss_state,  vtss_mrp_data_t *mrp)
{
    mrp->active = FALSE;
    mrp->ring_state = VTSS_MRP_RING_STATE_OPEN;
    mrp->tst_loc_idx = 0;
    mrp->event_mask = 0;

    mrp->tst_loc.tst_interval = 3500; /* 3.5 ms */
    mrp->tst_loc.tst_mon_count = 3;
    mrp->tst_loc.itst_interval = 3500; /* 3.5 ms */
    mrp->tst_loc.itst_mon_count = 3;

    mrp->copy_tst.tst_clear_loc = FALSE;
    mrp->copy_tst.itst_clear_loc = FALSE;

    mrp->conf.ring_role = VTSS_MRP_RING_ROLE_DISABLED;
    mrp->conf.p_port = VTSS_PORT_NO_NONE;
    mrp->conf.s_port = VTSS_PORT_NO_NONE;
}

static u32 ring_state_calc(vtss_mrp_ring_state_t state)
{
    switch (state) {
    case VTSS_MRP_RING_STATE_CLOSED: return 1;
    case VTSS_MRP_RING_STATE_OPEN:   return 0;
    }

    VTSS_D("Unknown ring state");
    return(0);
}

static vtss_rc mrp_init_port(vtss_state_t *vtss_state,  vtss_port_no_t port, u32 port_role)
{
    u32 chip_port = VTSS_CHIP_PORT(port);

    /* Enable MEP and LOC_SCAN */
    REG_WRM(MEP_MEP_CTRL,
            MEP_MEP_CTRL_LOC_SCAN_ENA(1) | MEP_MEP_CTRL_MEP_ENA(1),
            MEP_MEP_CTRL_LOC_SCAN_ENA_M | MEP_MEP_CTRL_MEP_ENA_M);

    /* Enable Analyzer to process MRP frames */
    REG_WRM(ANA_OAM_CFG(chip_port), ANA_OAM_CFG_MRP_ENA(1), ANA_OAM_CFG_MRP_ENA_M);

    /* ???? TBD what this means - taken from Linux driver */
    REG_WRM(ANA_VCAP_CFG(chip_port), ANA_VCAP_CFG_PAG_VAL(VTSS_BIT(6)), ANA_VCAP_CFG_PAG_VAL_M);

    /* Enable MEP to process Y.1731 frames */
    REG_WRM(ANA_OAM_CFG(chip_port), ANA_OAM_CFG_OAM_CFG(1), ANA_OAM_CFG_OAM_CFG_M);

    /* Activate MRP endpoint */
    REG_WRM(MEP_MRP_CTRL(chip_port),
            MEP_MRP_CTRL_MRP_ENA(1) | MEP_MRP_CTRL_TST_CHK_SEQ_ENA(1) | MEP_MRP_CTRL_CHK_DMAC_ENA(1) | MEP_MRP_CTRL_CHK_VERSION_ENA(1),
            MEP_MRP_CTRL_MRP_ENA_M | MEP_MRP_CTRL_TST_CHK_SEQ_ENA_M | MEP_MRP_CTRL_CHK_DMAC_ENA_M | MEP_MRP_CTRL_CHK_VERSION_ENA_M);

    /* Set ring state to default OPEN */
	REG_WRM(REW_MRP_TX_CFG(chip_port, CONFIG_TEST), REW_MRP_TX_CFG_MRP_STATE(0), REW_MRP_TX_CFG_MRP_STATE_M);

    /* Update the port role in HW for TST frames. These
     * values will be applied to the frame only if the bit MRO_MISC_UPD_ENA
     * is set */
    REG_WRM(REW_MRP_TX_CFG(chip_port, CONFIG_TEST), REW_MRP_TX_CFG_MRP_PORTROLE(port_role), REW_MRP_TX_CFG_MRP_PORTROLE_M);

    return VTSS_RC_OK;
}

static vtss_rc mrp_uninit_port(vtss_state_t *vtss_state,  vtss_port_no_t port)
{
    u32 chip_port = VTSS_CHIP_PORT(port);

    REG_WRM(MEP_TST_FWD_CTRL(chip_port),
            MEP_TST_FWD_CTRL_NXT_LOC_CPU_HITME(0),
            MEP_TST_FWD_CTRL_NXT_LOC_CPU_HITME_M);

    REG_WRM(MEP_ITST_FWD_CTRL(chip_port),
            MEP_ITST_FWD_CTRL_NXT_LOC_CPU_HITME(0),
            MEP_ITST_FWD_CTRL_NXT_LOC_CPU_HITME_M);

    /* Disable MEP to process MRP frames */
    REG_WRM(ANA_OAM_CFG(chip_port), ANA_OAM_CFG_MRP_ENA(0), ANA_OAM_CFG_MRP_ENA_M);

    /* Disactivate MRP endpoint */
    REG_WRM(MEP_MRP_CTRL(chip_port), MEP_MRP_CTRL_MRP_ENA(0), MEP_MRP_CTRL_MRP_ENA_M);

    return VTSS_RC_OK;
}

static vtss_rc mrp_port_update_mac(vtss_state_t *vtss_state,  vtss_port_no_t port, const u8 *mac)
{
    u32 macl = 0, mach = 0;
    u32 chip_port = VTSS_CHIP_PORT(port);

    mach |= mac[0] << 8;
    mach |= mac[1] << 0;
    macl |= mac[2] << 24;
    macl |= mac[3] << 16;
    macl |= mac[4] << 8;
    macl |= mac[5] << 0;

    REG_WR(MEP_MRP_MAC_LSB(chip_port), macl);
    REG_WR(MEP_MRP_MAC_MSB(chip_port), mach);

    return VTSS_RC_OK;
}

/* All the frames except the TST and ITST will be copied to the CPU */
static vtss_rc mrp_control_forwarding(vtss_state_t *vtss_state,  vtss_port_no_t port,  vtss_mrp_ring_role_t  role)
{
    u32 chip_port = VTSS_CHIP_PORT(port);
    u32 fwd_sel = (role == VTSS_MRP_RING_ROLE_MRM)? 2 : 1;

    /* All the frames except Test and IntTest frames need to be redirected
     * to CPU and allow SW to process and forward the frames
     */
    REG_WRM(MEP_MRP_FWD_CTRL(chip_port),
            MEP_MRP_FWD_CTRL_ERR_FWD_SEL(fwd_sel) | MEP_MRP_FWD_CTRL_MRP_TPM_FWD_SEL(fwd_sel) |
            MEP_MRP_FWD_CTRL_MRP_LD_FWD_SEL(fwd_sel) | MEP_MRP_FWD_CTRL_MRP_LU_FWD_SEL(fwd_sel) |
            MEP_MRP_FWD_CTRL_MRP_TC_FWD_SEL(fwd_sel) | MEP_MRP_FWD_CTRL_MRP_ITC_FWD_SEL(fwd_sel) |
            MEP_MRP_FWD_CTRL_MRP_ILD_FWD_SEL(fwd_sel) | MEP_MRP_FWD_CTRL_MRP_ILU_FWD_SEL(fwd_sel) |
            MEP_MRP_FWD_CTRL_MRP_ILSP_FWD_SEL(fwd_sel) | MEP_MRP_FWD_CTRL_OTHER_FWD_SEL(fwd_sel),
            MEP_MRP_FWD_CTRL_ERR_FWD_SEL_M | MEP_MRP_FWD_CTRL_MRP_TPM_FWD_SEL_M |
            MEP_MRP_FWD_CTRL_MRP_LD_FWD_SEL_M | MEP_MRP_FWD_CTRL_MRP_LU_FWD_SEL_M |
            MEP_MRP_FWD_CTRL_MRP_TC_FWD_SEL_M | MEP_MRP_FWD_CTRL_MRP_ITC_FWD_SEL_M |
            MEP_MRP_FWD_CTRL_MRP_ILD_FWD_SEL_M | MEP_MRP_FWD_CTRL_MRP_ILU_FWD_SEL_M |
            MEP_MRP_FWD_CTRL_MRP_ILSP_FWD_SEL_M | MEP_MRP_FWD_CTRL_OTHER_FWD_SEL_M);

    return VTSS_RC_OK;
}

static vtss_rc mrp_terminate_ring_test(vtss_state_t *vtss_state,  vtss_mrp_data_t *mrp)
{
    u32 p_chip_port = VTSS_CHIP_PORT(mrp->conf.p_port);
    u32 s_chip_port = VTSS_CHIP_PORT(mrp->conf.s_port);

    /* The TST forwarding control that is in use when TST processing is enabled. */
    /* This is always TST discard */
    REG_WRM(MEP_TST_FWD_CTRL(p_chip_port),
            MEP_TST_FWD_CTRL_REM_FWD_SEL(3) | MEP_TST_FWD_CTRL_OWN_FWD_SEL(3) |
            MEP_TST_FWD_CTRL_LO_PRIO_FWD_SEL(3) | MEP_TST_FWD_CTRL_HI_PRIO_FWD_SEL(3),
            MEP_TST_FWD_CTRL_REM_FWD_SEL_M | MEP_TST_FWD_CTRL_OWN_FWD_SEL_M |
            MEP_TST_FWD_CTRL_LO_PRIO_FWD_SEL_M | MEP_TST_FWD_CTRL_HI_PRIO_FWD_SEL_M);

    REG_WRM(MEP_TST_FWD_CTRL(s_chip_port),
            MEP_TST_FWD_CTRL_REM_FWD_SEL(3) | MEP_TST_FWD_CTRL_OWN_FWD_SEL(3) |
            MEP_TST_FWD_CTRL_LO_PRIO_FWD_SEL(3) | MEP_TST_FWD_CTRL_HI_PRIO_FWD_SEL(3),
            MEP_TST_FWD_CTRL_REM_FWD_SEL_M | MEP_TST_FWD_CTRL_OWN_FWD_SEL_M |
            MEP_TST_FWD_CTRL_LO_PRIO_FWD_SEL_M | MEP_TST_FWD_CTRL_HI_PRIO_FWD_SEL_M);

    return VTSS_RC_OK;
}

static vtss_rc mrp_forward_ring_test(vtss_state_t *vtss_state,  vtss_mrp_data_t *mrp,  BOOL forward,  u32 fwd_op)
{
    u32 p_chip_port = VTSS_CHIP_PORT(mrp->conf.p_port);
    u32 s_chip_port = VTSS_CHIP_PORT(mrp->conf.s_port);
    u32 mask;

    /* The TST forwarding control that is in use when TST processing is disabled. */
    /* This is configured depending on parameters */

    mask = VTSS_BIT(s_chip_port);

    REG_WRM(MEP_RING_MASK_CFG(p_chip_port), MEP_RING_MASK_CFG_RING_PORTMASK(mask), MEP_RING_MASK_CFG_RING_PORTMASK_M);

    REG_WRM(MEP_MRP_FWD_CTRL(p_chip_port),
            MEP_MRP_FWD_CTRL_MRP_TST_FWD_SEL(fwd_op) | MEP_MRP_FWD_CTRL_RING_MASK_ENA(forward ? 1 : 0),
            MEP_MRP_FWD_CTRL_MRP_TST_FWD_SEL_M | MEP_MRP_FWD_CTRL_RING_MASK_ENA_M);

    mask = VTSS_BIT(p_chip_port);

    REG_WRM(MEP_RING_MASK_CFG(s_chip_port), MEP_RING_MASK_CFG_RING_PORTMASK(mask), MEP_RING_MASK_CFG_RING_PORTMASK_M);

    REG_WRM(MEP_MRP_FWD_CTRL(s_chip_port),
            MEP_MRP_FWD_CTRL_MRP_TST_FWD_SEL(fwd_op) | MEP_MRP_FWD_CTRL_RING_MASK_ENA(forward ? 1 : 0),
            MEP_MRP_FWD_CTRL_MRP_TST_FWD_SEL_M | MEP_MRP_FWD_CTRL_RING_MASK_ENA_M);

    return VTSS_RC_OK;
}

static vtss_rc mrp_rewrite_ring_test(vtss_state_t *vtss_state,  vtss_mrp_data_t *mrp, BOOL update)
{
    u32 p_chip_port = VTSS_CHIP_PORT(mrp->conf.p_port);
    u32 s_chip_port = VTSS_CHIP_PORT(mrp->conf.s_port);

    REG_WRM(REW_MRP_TX_CFG(p_chip_port, 0),
            REW_MRP_TX_CFG_MRP_TIMESTAMP_UPD(update ? 1 : 0) | REW_MRP_TX_CFG_MRP_SEQ_UPD(update ? 1 : 0) | REW_MRP_TX_CFG_MRP_MISC_UPD(update ? 1 : 0),
            REW_MRP_TX_CFG_MRP_TIMESTAMP_UPD_M | REW_MRP_TX_CFG_MRP_SEQ_UPD_M | REW_MRP_TX_CFG_MRP_MISC_UPD_M);

    REG_WRM(REW_MRP_TX_CFG(s_chip_port, 0),
            REW_MRP_TX_CFG_MRP_TIMESTAMP_UPD(update ? 1 : 0) | REW_MRP_TX_CFG_MRP_SEQ_UPD(update ? 1 : 0) | REW_MRP_TX_CFG_MRP_MISC_UPD(update ? 1 : 0),
            REW_MRP_TX_CFG_MRP_TIMESTAMP_UPD_M | REW_MRP_TX_CFG_MRP_SEQ_UPD_M | REW_MRP_TX_CFG_MRP_MISC_UPD_M);

    return VTSS_RC_OK;
}

static vtss_rc mrp_loc_configure(vtss_state_t *vtss_state,  vtss_mrp_data_t *mrp,  BOOL process)
{
    u32  value, clk_period_in_ps, base_tick_ps, interval_in_ps;
    u32  p_chip_port = VTSS_CHIP_PORT(mrp->conf.p_port);
    u32  s_chip_port = VTSS_CHIP_PORT(mrp->conf.s_port);

    /* Calculate the LOC period base tick count and LOC interval in picoseconds */
    REG_RD(MEP_LOC_CTRL, &value);
    value = MEP_LOC_CTRL_BASE_TICK_CNT_X(value);    /* This is the LOC base tick in clock cycles */
    clk_period_in_ps = vtss_lan966x_clk_period_ps(vtss_state);  /* Get the clock period in picoseconds */
    base_tick_ps = clk_period_in_ps * value;
    interval_in_ps = mrp->tst_loc.tst_interval * 1000;

    /* Configure LOC periods used for TST LOC. */
    value = (interval_in_ps / base_tick_ps) + ((interval_in_ps % base_tick_ps) ? 1 : 0);
    REG_WR(MEP_LOC_PERIOD_CFG(mrp->tst_loc_idx), value);

    /* Configure LOC */
    REG_WRM(MEP_TST_CFG(p_chip_port),
            MEP_TST_CFG_MAX_MISS_CNT(mrp->tst_loc.tst_mon_count) |
            MEP_TST_CFG_CLR_MISS_CNT_ENA(process ? 1 : 0) |
            MEP_TST_CFG_MISS_CNT(0) |
            MEP_TST_CFG_LOC_PERIOD(mrp->tst_loc_idx),
            MEP_TST_CFG_CLR_MISS_CNT_ENA_M | MEP_TST_CFG_LOC_PERIOD_M | MEP_TST_CFG_MAX_MISS_CNT_M | MEP_TST_CFG_MISS_CNT_M);

    REG_WRM(MEP_TST_CFG(s_chip_port),
            MEP_TST_CFG_MAX_MISS_CNT(mrp->tst_loc.tst_mon_count) |
            MEP_TST_CFG_CLR_MISS_CNT_ENA(process ? 1 : 0) |
            MEP_TST_CFG_MISS_CNT(0) |
            MEP_TST_CFG_LOC_PERIOD(mrp->tst_loc_idx),
            MEP_TST_CFG_CLR_MISS_CNT_ENA_M | MEP_TST_CFG_LOC_PERIOD_M | MEP_TST_CFG_MAX_MISS_CNT_M | MEP_TST_CFG_MISS_CNT_M);

    return VTSS_RC_OK;
}

static vtss_rc mrp_process_ring_test(vtss_state_t *vtss_state,  vtss_mrp_data_t *mrp,  BOOL process)
{
    u32  p_chip_port = VTSS_CHIP_PORT(mrp->conf.p_port);
    u32  s_chip_port = VTSS_CHIP_PORT(mrp->conf.s_port);

    /* Configure processing of the frame */
    REG_WRM(MEP_MRP_CTRL(p_chip_port), MEP_MRP_CTRL_MRP_TST_ENA(process ? 1 : 0), MEP_MRP_CTRL_MRP_TST_ENA_M);
    REG_WRM(MEP_MRP_CTRL(s_chip_port), MEP_MRP_CTRL_MRP_TST_ENA(process ? 1 : 0), MEP_MRP_CTRL_MRP_TST_ENA_M);

    /* Configure the TST LOC */
    if (mrp_loc_configure(vtss_state, mrp, process) != VTSS_RC_OK) {
        VTSS_D("mrp_loc_configure failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc mrp_update_forwarding(vtss_state_t *vtss_state,  vtss_mrp_data_t *mrp)
{
    if (mrp_control_forwarding(vtss_state, mrp->conf.p_port, mrp->conf.ring_role) != VTSS_RC_OK) {
        VTSS_D("mrp_mc_control_forwarding failed port %u", mrp->conf.p_port);
        return VTSS_RC_ERROR;
    }
    if (mrp_control_forwarding(vtss_state, mrp->conf.s_port, mrp->conf.ring_role) != VTSS_RC_OK) {
        VTSS_D("mrp_mc_control_forwarding failed port %u", mrp->conf.s_port);
        return VTSS_RC_ERROR;
    }

    if (mrp->conf.ring_role == VTSS_MRP_RING_ROLE_MRM) {
        if (mrp_terminate_ring_test(vtss_state, mrp) != VTSS_RC_OK) {
            VTSS_D("mrp_terminate_ring_test failed");
            return VTSS_RC_ERROR;
        }
        if (mrp_forward_ring_test(vtss_state, mrp, FALSE, MRP_FWD_NOP) != VTSS_RC_OK) {    /* Strange - when TST handling is enabled NOP means DISC. See VML MRP_TST_FWD_SEL */
            VTSS_D("mrp_forward_ring_test failed");
            return VTSS_RC_ERROR;
        }
    }

    if ((mrp->conf.ring_role == VTSS_MRP_RING_ROLE_MRC) || (mrp->conf.ring_role == VTSS_MRP_RING_ROLE_DISABLED)){
        if (mrp_forward_ring_test(vtss_state, mrp, TRUE, MRP_FWD_NOP) != VTSS_RC_OK) {
            VTSS_D("mrp_forward_ring_test failed");
            return VTSS_RC_ERROR;
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_add(vtss_state_t           *vtss_state,
                               const vtss_mrp_idx_t   mrp_idx,
                               const vtss_mrp_conf_t  *const conf)
{
    u32             i;
    vtss_mrp_data_t mrp_data = vtss_state->mrp.data[mrp_idx];
    vtss_mrp_data_t *mrp_array = vtss_state->mrp.data;

    VTSS_D("Enter");

    if (mrp_data.active) {
        VTSS_E("MRP instance already active");
        return VTSS_RC_ERROR;
    }
    if (conf->p_port == conf->s_port) {
        VTSS_E("Illegal port combination");
        return VTSS_RC_ERROR;
    }
    for (i=0; i<VTSS_MRP_CNT; ++i) {
        if (!mrp_array[i].active) {
            continue;
        }
        if ((conf->p_port == mrp_array[i].conf.p_port) || (conf->p_port == mrp_array[i].conf.s_port)) {
            VTSS_E("Primary port already in use");
            return VTSS_RC_ERROR;
        }
        if ((conf->s_port == mrp_array[i].conf.p_port) || (conf->s_port == mrp_array[i].conf.s_port)) {
            VTSS_E("Secondary port already in use");
            return VTSS_RC_ERROR;
        }
    }

    /* Allocate a TST LOC timer. */
    BOOL timer_used[10];
    memset(timer_used, 0, sizeof(timer_used));
    for (i=0; i<VTSS_MRP_CNT; ++i) {
        if (!mrp_array[i].active) {
            continue;
        }
        timer_used[mrp_array[i].tst_loc_idx] = TRUE;
    }
    for (i=4; i<10; ++i) {  /* Note that VOP is using this first four timers */
        if (!timer_used[i]) {
            break;
        }
    }
    if (i >= 10) { /* Unused LOC timer NOT found */
        VTSS_E("No unused LOC timer found");
        return VTSS_RC_ERROR;
    }
    mrp_data.tst_loc_idx = i;

    /* Initialize port to enable MRP */
    if (mrp_init_port(vtss_state, conf->p_port, 0) != VTSS_RC_OK) {
        VTSS_E("mrp_init_port failed");
        return VTSS_RC_ERROR;
    }
    if (mrp_init_port(vtss_state, conf->s_port, 1) != VTSS_RC_OK) {
        VTSS_E("mrp_init_port failed");
        return VTSS_RC_ERROR;
    }

    /* Configure port with requested MAC address */
    if (mrp_port_update_mac(vtss_state, conf->p_port, conf->p_mac.addr) != VTSS_RC_OK) {
        VTSS_E("mrp_port_update_mac failed");
        return VTSS_RC_ERROR;
    }
    if (mrp_port_update_mac(vtss_state, conf->s_port, conf->s_mac.addr) != VTSS_RC_OK) {
        VTSS_E("mrp_port_update_mac failed");
        return VTSS_RC_ERROR;
    }

    /* Generate active copy of instance data */
    mrp_data.active = TRUE;
    mrp_data.conf = *conf;

    /* Configure MRP frame forwarding */
    if (mrp_update_forwarding(vtss_state, &mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_update_forwarding failed");
        return VTSS_RC_ERROR;
    }

    /* Configure rewrite of Test frames */
    if (mrp_rewrite_ring_test(vtss_state, &mrp_data, (conf->ring_role == VTSS_MRP_RING_ROLE_MRM)) != VTSS_RC_OK) {
        VTSS_E("mrp_rewrite_ring_test failed");
        return VTSS_RC_ERROR;
    }

    /* Configure processing of Test frames */
    if (mrp_process_ring_test(vtss_state, &mrp_data, (conf->ring_role == VTSS_MRP_RING_ROLE_MRM)) != VTSS_RC_OK) {
        VTSS_E("mrp_process_ring_test failed");
        return VTSS_RC_ERROR;
    }

    /* Everything went fine - Update internals */
    vtss_state->mrp.data[mrp_idx].tst_loc_idx = i;
    vtss_state->mrp.data[mrp_idx].active = TRUE;

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_del(vtss_state_t           *vtss_state,
                               const vtss_mrp_idx_t   mrp_idx)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];

    VTSS_D("Enter");

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

// This is in Linux implementation but the assumption is that it is not necessary
//    if (mrp_update_forwarding(vtss_state, mrp_data) != VTSS_RC_OK) {
//        VTSS_E("mrp_update_forwarding failed");
//        return VTSS_RC_ERROR;
//    }

    if (mrp_uninit_port(vtss_state, mrp_data->conf.p_port) != VTSS_RC_OK) {
        VTSS_E("mrp_uninit_port failed");
    }
    if (mrp_uninit_port(vtss_state, mrp_data->conf.s_port) != VTSS_RC_OK) {
        VTSS_E("mrp_uninit_port failed");
    }

    /* Set instance to default */
    mrp_instance_default(vtss_state, mrp_data);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_ring_role_set(vtss_state_t                *vtss_state,
                                         const vtss_mrp_idx_t        mrp_idx,
                                         const vtss_mrp_ring_role_t  role)
{
    vtss_mrp_data_t mrp_data = vtss_state->mrp.data[mrp_idx];

    VTSS_D("Enter");

    if (!mrp_data.active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }
    if (mrp_data.conf.ring_role == role) {
        VTSS_D("MRP role is unchanged");
        return VTSS_RC_OK;
    }

    mrp_data.conf.ring_role = role;    /* The following is using the MRP data.ring_role */

    /* Update MRP frame forwarding */
    if (mrp_update_forwarding(vtss_state, &mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_update_forwarding failed");
        return VTSS_RC_ERROR;
    }

    /* Configure rewrite of Test frames */
    if (mrp_rewrite_ring_test(vtss_state, &mrp_data, (role == VTSS_MRP_RING_ROLE_MRM)) != VTSS_RC_OK) {
        VTSS_E("mrp_rewrite_ring_test failed");
        return VTSS_RC_ERROR;
    }

    /* Configure processing of Test frames */
    if (mrp_process_ring_test(vtss_state, &mrp_data, (role == VTSS_MRP_RING_ROLE_MRM)) != VTSS_RC_OK) {
        VTSS_E("mrp_process_ring_test failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_ports_set(vtss_state_t            *vtss_state,
                                     const vtss_mrp_idx_t    mrp_idx,
                                     const vtss_mrp_ports_t  *const ports)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];

    VTSS_D("Enter  p_port %u  s_port %u", ports->p_port, ports->s_port);

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }
    if (ports->p_port == ports->s_port) {
        VTSS_E("Illegal port combination");
        return VTSS_RC_ERROR;
    }
    if (((ports->p_port != mrp_data->conf.p_port) && (ports->p_port != mrp_data->conf.s_port)) ||     /* It is not allowed to configure any new port, only swapping or the same */
        ((ports->s_port != mrp_data->conf.p_port) && (ports->s_port != mrp_data->conf.s_port))) {
        VTSS_E("Illegal port combination");
        return VTSS_RC_ERROR;
    }

    /* Update the port role in HW for TST frames. These
     * values will be applied to the frame only if the bit MRP_MISC_UPD_ENA
     * is set */
    REG_WRM(REW_MRP_TX_CFG(ports->p_port, CONFIG_TEST), REW_MRP_TX_CFG_MRP_PORTROLE(0), REW_MRP_TX_CFG_MRP_PORTROLE_M);
    REG_WRM(REW_MRP_TX_CFG(ports->s_port, CONFIG_TEST), REW_MRP_TX_CFG_MRP_PORTROLE(1), REW_MRP_TX_CFG_MRP_PORTROLE_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_ring_state_set(vtss_state_t                 *vtss_state,
                                          const vtss_mrp_idx_t         mrp_idx,
                                          const vtss_mrp_ring_state_t  state)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    u32             p_chip_port = VTSS_CHIP_PORT(mrp_data->conf.p_port);
    u32             s_chip_port = VTSS_CHIP_PORT(mrp_data->conf.s_port);

    VTSS_D("Enter");

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    /* Set ring state to be updated into transmitted TST frames */
	REG_WRM(REW_MRP_TX_CFG(p_chip_port, CONFIG_TEST),
            REW_MRP_TX_CFG_MRP_STATE(ring_state_calc(state)),
            REW_MRP_TX_CFG_MRP_STATE_M);

	REG_WRM(REW_MRP_TX_CFG(s_chip_port, CONFIG_TEST),
            REW_MRP_TX_CFG_MRP_STATE(ring_state_calc(state)),
            REW_MRP_TX_CFG_MRP_STATE_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_tst_loc_set(vtss_state_t              *vtss_state,
                                       const vtss_mrp_idx_t      mrp_idx,
                                       const vtss_mrp_tst_loc_t  *const tst_loc)
{
    vtss_mrp_data_t mrp_data = vtss_state->mrp.data[mrp_idx];

    VTSS_D("Enter");

    if (!mrp_data.active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    mrp_data.tst_loc = *tst_loc;

    /* Configure the TST LOC */
    if (mrp_loc_configure(vtss_state, &mrp_data, TRUE) != VTSS_RC_OK) {
        VTSS_D("mrp_loc_configure failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_copy_tst_set(vtss_state_t               *vtss_state,
                                        const vtss_mrp_idx_t       mrp_idx,
                                        const vtss_mrp_copy_tst_t  *const copy_tst)
{
    vtss_mrp_data_t  *mrp_data = &vtss_state->mrp.data[mrp_idx];
    u32              p_chip_port = VTSS_CHIP_PORT(mrp_data->conf.p_port);
    u32              s_chip_port = VTSS_CHIP_PORT(mrp_data->conf.s_port);

    VTSS_D("Enter");

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    REG_WRM(MEP_TST_FWD_CTRL(p_chip_port),
            MEP_TST_FWD_CTRL_NXT_LOC_CPU_HITME(copy_tst->tst_clear_loc ? 1 : 0),
            MEP_TST_FWD_CTRL_NXT_LOC_CPU_HITME_M);

    REG_WRM(MEP_TST_FWD_CTRL(s_chip_port),
            MEP_TST_FWD_CTRL_NXT_LOC_CPU_HITME(copy_tst->tst_clear_loc ? 1 : 0),
            MEP_TST_FWD_CTRL_NXT_LOC_CPU_HITME_M);

    REG_WRM(MEP_ITST_FWD_CTRL(p_chip_port),
            MEP_ITST_FWD_CTRL_NXT_LOC_CPU_HITME(copy_tst->itst_clear_loc ? 1 : 0),
            MEP_ITST_FWD_CTRL_NXT_LOC_CPU_HITME_M);

    REG_WRM(MEP_ITST_FWD_CTRL(s_chip_port),
            MEP_ITST_FWD_CTRL_NXT_LOC_CPU_HITME(copy_tst->itst_clear_loc ? 1 : 0),
            MEP_ITST_FWD_CTRL_NXT_LOC_CPU_HITME_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_status_get(vtss_state_t          *vtss_state,
                                      const vtss_mrp_idx_t  mrp_idx,
                                      vtss_mrp_status_t     *const status)
{
    vtss_mrp_data_t  *mrp_data = &vtss_state->mrp.data[mrp_idx];
    u32              p_chip_port = VTSS_CHIP_PORT(mrp_data->conf.p_port);
    u32              s_chip_port = VTSS_CHIP_PORT(mrp_data->conf.s_port);
    u32              value;

    VTSS_D("Enter");

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    memset(status, 0, sizeof(*status));

    /* Poll so we get the most recent counter values */
    if (mrp_counter_update(vtss_state, mrp_idx, 0) != VTSS_RC_OK) {
        VTSS_D("mrp_counter_update failed");
        return VTSS_RC_ERROR;
    }

    /* Get P port LOC status */
    REG_RD(MEP_TST_CFG(p_chip_port), &value);
    status->p_status.tst_loc = (MEP_TST_CFG_MISS_CNT_X(value) == MEP_TST_CFG_MAX_MISS_CNT_X(value));
    REG_RD(MEP_ITST_CFG(p_chip_port), &value);
    status->p_status.itst_loc = (MEP_TST_CFG_MISS_CNT_X(value) == MEP_TST_CFG_MAX_MISS_CNT_X(value));

    /* Get S port LOC status */
    REG_RD(MEP_TST_CFG(s_chip_port), &value);
    status->s_status.tst_loc = (MEP_TST_CFG_MISS_CNT_X(value) == MEP_TST_CFG_MAX_MISS_CNT_X(value));
    REG_RD(MEP_ITST_CFG(s_chip_port), &value);
    status->s_status.itst_loc = (MEP_TST_CFG_MISS_CNT_X(value) == MEP_TST_CFG_MAX_MISS_CNT_X(value));

    /* Get the P port seen status */
    REG_RD(MEP_MRP_STICKY(p_chip_port), &value);
    status->p_status.mrp_seen = MEP_MRP_STICKY_MRP_RX_STICKY_X(value) ? TRUE : FALSE;
    status->p_status.mrp_proc_seen = MEP_MRP_STICKY_MRP_RX_PROC_STICKY_X(value) ? TRUE : FALSE;
    status->p_status.dmac_err_seen = MEP_MRP_STICKY_DMAC_ERR_STICKY_X(value) ? TRUE : FALSE;
    status->p_status.vers_err_seen = MEP_MRP_STICKY_VERSION_ERR_STICKY_X(value) ? TRUE : FALSE;
    status->p_status.seq_err_seen = MEP_MRP_STICKY_RX_SEQ_ERR_STICKY_X(value) ? TRUE : FALSE;

    /* Clear the sticky bits that has been detected */
    value = value &
            (MEP_MRP_STICKY_MRP_RX_STICKY_M | MEP_MRP_STICKY_MRP_RX_PROC_STICKY_M   |
             MEP_MRP_STICKY_DMAC_ERR_STICKY_M | MEP_MRP_STICKY_VERSION_ERR_STICKY_M   |
             MEP_MRP_STICKY_RX_SEQ_ERR_STICKY_M);
    REG_WR(MEP_MRP_STICKY(p_chip_port), value);

    /* Get the S port seen status */
    REG_RD(MEP_MRP_STICKY(s_chip_port), &value);
    status->s_status.mrp_seen = MEP_MRP_STICKY_MRP_RX_STICKY_X(value) ? TRUE : FALSE;
    status->s_status.mrp_proc_seen = MEP_MRP_STICKY_MRP_RX_PROC_STICKY_X(value) ? TRUE : FALSE;
    status->s_status.dmac_err_seen = MEP_MRP_STICKY_DMAC_ERR_STICKY_X(value) ? TRUE : FALSE;
    status->s_status.vers_err_seen = MEP_MRP_STICKY_VERSION_ERR_STICKY_X(value) ? TRUE : FALSE;
    status->s_status.seq_err_seen = MEP_MRP_STICKY_RX_SEQ_ERR_STICKY_X(value) ? TRUE : FALSE;

    /* Clear the sticky bits that has been detected */
    value = value &
            (MEP_MRP_STICKY_MRP_RX_STICKY_M | MEP_MRP_STICKY_MRP_RX_PROC_STICKY_M   |
             MEP_MRP_STICKY_DMAC_ERR_STICKY_M | MEP_MRP_STICKY_VERSION_ERR_STICKY_M   |
             MEP_MRP_STICKY_RX_SEQ_ERR_STICKY_M);
    REG_WR(MEP_MRP_STICKY(s_chip_port), value);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_counters_get(vtss_state_t          *vtss_state,
                                        const vtss_mrp_idx_t  mrp_idx,
                                        vtss_mrp_counters_t   *const counters)
{
    vtss_mrp_data_t  *mrp_data = &vtss_state->mrp.data[mrp_idx];

    VTSS_D("Enter");

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    memset(counters, 0, sizeof(*counters));

    /* Poll so we get the most recent counter values */
    if (mrp_counter_update(vtss_state, mrp_idx, 0) != VTSS_RC_OK) {
        VTSS_D("mrp_counter_update failed");
        return VTSS_RC_ERROR;
    }

    /* Get the counters */
    counters->p_counters.tst_rx_count = mrp_data->p_counters.tst_rx_count.value;
    counters->p_counters.itst_rx_count = mrp_data->p_counters.itst_rx_count.value;
    counters->s_counters.tst_rx_count = mrp_data->s_counters.tst_rx_count.value;
    counters->s_counters.itst_rx_count = mrp_data->s_counters.itst_rx_count.value;

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_counters_clear(vtss_state_t          *vtss_state,
                                          const vtss_mrp_idx_t  mrp_idx)
{
    vtss_mrp_data_t  *mrp_data = &vtss_state->mrp.data[mrp_idx];

    VTSS_D("Enter");

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    /* Clear counter values */
    if (mrp_counter_update(vtss_state, mrp_idx, 1) != VTSS_RC_OK) {
        VTSS_D("mrp_counter_update failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_event_mask_set(vtss_state_t          *vtss_state,
                                          const vtss_mrp_idx_t  mrp_idx,
                                          const u32             mask,
                                          const BOOL            enable)
{
    vtss_mrp_data_t  *mrp_data = &vtss_state->mrp.data[mrp_idx];
    u32              p_chip_port = VTSS_CHIP_PORT(mrp_data->conf.p_port);
    u32              s_chip_port = VTSS_CHIP_PORT(mrp_data->conf.s_port);
    u32              enable_mask, reg_mask;

    VTSS_D("Enter  mrp_idx %u  mask %u  enable %u", mrp_idx, mask, enable);

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    /* Read the P port interrupt enable mask */
    REG_RD(MEP_MRP_INTR_ENA(p_chip_port), &enable_mask);

    /* Translate the input mask to register mask */
    reg_mask = ((mask & VTSS_MRP_EVENT_MASK_ITST_LOC)      ? MEP_MRP_INTR_ENA_ITST_LOC_INTR_ENA(1) : 0) |
               ((mask & VTSS_MRP_EVENT_MASK_TST_LOC)       ? MEP_MRP_INTR_ENA_TST_LOC_INTR_ENA(1)  : 0);

    /* Calculate new enable mask */
    enable_mask = enable ? (enable_mask | reg_mask) : (enable_mask & ~reg_mask);

    /* Write back the P port interrupt enable mask */
    REG_WR(MEP_MRP_INTR_ENA(p_chip_port), enable_mask);

    /* Read the S port interrupt enable mask */
    REG_RD(MEP_MRP_INTR_ENA(s_chip_port), &enable_mask);

    /* Translate the input mask to register mask */
    reg_mask = ((mask & VTSS_MRP_EVENT_MASK_ITST_LOC)      ? MEP_MRP_INTR_ENA_ITST_LOC_INTR_ENA(1) : 0) |
               ((mask & VTSS_MRP_EVENT_MASK_TST_LOC)       ? MEP_MRP_INTR_ENA_TST_LOC_INTR_ENA(1)  : 0);

    /* Calculate new enable mask */
    enable_mask = enable ? (enable_mask | reg_mask) : (enable_mask & ~reg_mask);

    /* Write back the S port interrupt enable mask */
    REG_WR(MEP_MRP_INTR_ENA(s_chip_port), enable_mask);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_event_get(vtss_state_t          *vtss_state,
                                     const vtss_mrp_idx_t  mrp_idx,
                                     vtss_mrp_event_t      *const events)
{
    vtss_mrp_data_t  *mrp_data = &vtss_state->mrp.data[mrp_idx];
    u32              p_chip_port = VTSS_CHIP_PORT(mrp_data->conf.p_port);
    u32              s_chip_port = VTSS_CHIP_PORT(mrp_data->conf.s_port);
    u32              enable_mask, sticky_mask;

    VTSS_D("Enter  mrp_idx %u", mrp_idx);

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    memset(events, 0, sizeof(*events));

    /* Read the P port interrupt enable mask */
    REG_RD(MEP_MRP_INTR_ENA(p_chip_port), &enable_mask);

    /* Read the P port sticky bits and clear the enabled ones */
    REG_RD(MEP_MRP_STICKY(p_chip_port), &sticky_mask);
    sticky_mask &= enable_mask;
    REG_WR(MEP_MRP_STICKY(p_chip_port), sticky_mask); /* Sticky bits cleared by writing 1 to them */

    /* Translate P port sticky mask to returned event mask */
    events->p_mask = ((MEP_MRP_STICKY_ITST_LOC_STICKY_X(sticky_mask) != 0) ? VTSS_MRP_EVENT_MASK_ITST_LOC : 0) |
                     ((MEP_MRP_STICKY_TST_LOC_STICKY_X(sticky_mask) != 0)  ? VTSS_MRP_EVENT_MASK_TST_LOC  : 0);

    /* Read the S port interrupt enable mask */
    REG_RD(MEP_MRP_INTR_ENA(s_chip_port), &enable_mask);

    /* Read the S port sticky bits and clear the enabled ones */
    REG_RD(MEP_MRP_STICKY(s_chip_port), &sticky_mask);
    sticky_mask &= enable_mask;
    REG_WR(MEP_MRP_STICKY(s_chip_port), sticky_mask); /* Sticky bits cleared by writing 1 to them */

    /* Translate S port sticky mask to returned event mask */
    events->s_mask = ((MEP_MRP_STICKY_ITST_LOC_STICKY_X(sticky_mask) != 0) ? VTSS_MRP_EVENT_MASK_ITST_LOC : 0) |
                     ((MEP_MRP_STICKY_TST_LOC_STICKY_X(sticky_mask) != 0)  ? VTSS_MRP_EVENT_MASK_TST_LOC  : 0);

    VTSS_D("Exit  p_mask %X  s_mask %X", events->p_mask, events->s_mask);

    return VTSS_RC_OK;
}

// D_COM: Debug COMmon; DR_COM: Debug Read COMmon. _I for Instance. Etc.
#define D_REG(pr, name)            vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(name), name)
#define D_REG_I(pr, name, i)       vtss_lan966x_debug_reg_inst(vtss_state, pr, name, (i), name)

static vtss_rc lan966x_debug_mrp(vtss_state_t               *vtss_state,
                                 const vtss_debug_printf_t  pr,
                                 const vtss_debug_info_t    *const info)
{
    u32   i, v, div, mrp_idx;
    char  buf[80];
    BOOL  show, mrp, status;

    div = 0;
    mrp_idx = 0;
    show = mrp = status = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show = (info->action == 0) ? TRUE : FALSE;

        if (info->action > 0) { /* This potentially a MRP config or MRP status action */
            for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
                mrp = (info->action / div == 1) ? TRUE : FALSE;
                status = (info->action / div == 2) ? TRUE : FALSE;
                if (mrp || status) {
                    break;
                }
            }
            if (mrp || status) {    /* Calculate the possible MRP index */
                mrp_idx = info->action % div;
            }
        }
    }

    VTSS_D("show %u  mrp %u  status %u", show, mrp, status);

    if (show) {
        pr("MRP Debug Group action:\n");
        pr("    0: Show possible actions\n");
        pr("    1XXXX: Print MRP XXXX configurations. Without XXXX all MRPs are printed\n");
        pr("    2XXXX: Print MRP XXXX status. Without XXXX all MRPs are printed\n");
        pr("\n");
    }

    if (!info->has_action || mrp) { /* MRP configuration must be printed */
        pr("MRP Config:\n\n");

        for (i=0; i<VTSS_MRP_CNT; ++i) {
            if (mrp && (div > 1) && (mrp_idx != i)) {   /* A specific MRP must be printed - this is not the one */
                continue;
            }

            REG_RD(MEP_MRP_CTRL(i), &v);
            if (info->full  ||  MEP_MRP_CTRL_MRP_ENA_X(v)) {
                sprintf(buf, "MRP %u", i);
                vtss_lan966x_debug_reg_header(pr, buf);
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_MRP_CTRL(i)), i, "MEP_MRP_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_MRP_FWD_CTRL(i)), i, "MEP_MRP_FWD_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_RING_MASK_CFG(i)), i, "MEP_RING_MASK_CFG");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_TST_FWD_CTRL(i)), i, "MEP_TST_FWD_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_TST_CFG(i)), i, "MEP_TST_CFG");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_ITST_FWD_CTRL(i)), i, "MEP_ITST_FWD_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_ITST_CFG(i)), i, "MEP_ITST_CFG");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_MRP_MAC_LSB(i)), i, "MEP_MRP_MAC_LSB");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_MRP_MAC_MSB(i)), i, "MEP_MRP_MAC_MSB");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_MRP_INTR_ENA(i)), i, "MEP_MRP_INTR_ENA");

                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(REW_MRP_TX_CFG(i,0)), i, "REW_MRP_TX_CFG[0]");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(REW_MRP_TX_CFG(i,1)), i, "REW_MRP_TX_CFG[1]");
                pr("\n");
            }
        }
    }
    pr("\n");

    if (!info->has_action || status) { /* MRP status must be printed */
        pr("MRP Status:\n\n");

        for (i=0; i<VTSS_MRP_CNT; ++i) {
            if (status && (div > 1) && (mrp_idx != i)) {   /* A specific MRP must be printed - this is not the one */
                continue;
            }

            REG_RD(MEP_MRP_CTRL(i), &v);
            if (info->full  ||  MEP_MRP_CTRL_MRP_ENA_X(v)) {
                sprintf(buf, "MRP %u", i);
                vtss_lan966x_debug_reg_header(pr, buf);
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_MRP_STICKY(i)), i, "MEP_MRP_STICKY");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_TST_RX_CNT(i)), i, "MEP_TST_RX_CNT");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_ITST_RX_CNT(i)), i, "MEP_ITST_RX_CNT");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_TST_CFG(i)), i, "MEP_TST_CFG");
                pr("\n");
            }
        }
    }
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_mrp_debug_print(vtss_state_t               *vtss_state,
                                     const vtss_debug_printf_t  pr,
                                     const vtss_debug_info_t    *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_MRP, lan966x_debug_mrp, vtss_state, pr, info);
}

#undef D_REG
#undef D_REG_I

static vtss_rc lan966x_mrp_poll_1sec(vtss_state_t *vtss_state)
{
    vtss_mrp_idx_t *idx = &(vtss_state->mrp.mrp_poll_idx);  /* For readability */

    VTSS_RC(mrp_counter_update(vtss_state, *idx, 0));
    *idx = (*idx == VTSS_MRP_CNT - 1) ? 0 : *idx + 1;

    return VTSS_RC_OK;
}

static vtss_rc lan966x_mrp_init(vtss_state_t *vtss_state)
{
    u32 i;

    /* Set instances to default */
    memset(vtss_state->mrp.data, 0, sizeof(vtss_state->mrp.data));
    for (i=0; i<VTSS_MRP_CNT; ++i) {
        mrp_instance_default(vtss_state, &vtss_state->mrp.data[i]);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_mrp_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_mrp_state_t *state = &vtss_state->mrp;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->mrp_add = lan966x_mrp_add;
        state->mrp_del = lan966x_mrp_del;
        state->mrp_ports_set = lan966x_mrp_ports_set;
        state->mrp_ring_role_set = lan966x_mrp_ring_role_set;
        state->mrp_ring_state_set = lan966x_mrp_ring_state_set;
        state->mrp_tst_loc_set = lan966x_mrp_tst_loc_set;
        state->mrp_copy_tst_set = lan966x_mrp_copy_tst_set;
        state->mrp_status_get = lan966x_mrp_status_get;
        state->mrp_counters_get = lan966x_mrp_counters_get;
        state->mrp_counters_clear = lan966x_mrp_counters_clear;
        state->mrp_event_mask_set = lan966x_mrp_event_mask_set;
        state->mrp_event_get = lan966x_mrp_event_get;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan966x_mrp_init(vtss_state));
        break;

    case VTSS_INIT_CMD_POLL:
        VTSS_RC(lan966x_mrp_poll_1sec(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
