// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_MRP
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA) && defined(VTSS_FEATURE_MRP)

#define FWD_NOP          0
#define FWD_COPY_CPU     1
#define FWD_REDIRECT_CPU 2
#define FWD_DISCARD      3

#define CONFIG_TEST     0
#define CONFIG_INTEST   1
#define LOC_PERIOD_CNT  10

static const char *sel2txt(u32 sel)
{
    switch (sel) {
    case FWD_NOP:
        return "NOP";
    case FWD_COPY_CPU:
        return "COPY_CPU";
    case FWD_REDIRECT_CPU:
        return "REDIRECT_CPU";
    case FWD_DISCARD:
        return "DISCARD";
    default:
        return "ERROR!";
    }
}

static const char *ring_role2txt(vtss_mrp_ring_role_t ring_role)
{
    switch (ring_role) {
    case VTSS_MRP_RING_ROLE_DISABLED:
        return "Disabled";
    case VTSS_MRP_RING_ROLE_CLIENT:
        return "Client";
    case VTSS_MRP_RING_ROLE_MANAGER:
        return "Manager";
    default:
        return "ERROR!";
    }
}

static const char *port_state2txt(vtss_mrp_port_state_t state)
{
    switch (state) {
    case VTSS_MRP_PORT_STATE_DISABLED:
        return "Disabled";
    case VTSS_MRP_PORT_STATE_BLOCKED:
        return "Blocked";
    case VTSS_MRP_PORT_STATE_FORWARDING:
        return "Forwarding";
    default:
        return "ERROR!";
    }
}

static vtss_rc mrp_counter_update(vtss_state_t         *vtss_state,
                                  const vtss_mrp_idx_t mrp_idx,
                                  const BOOL           clear)
{
    /*
     * These macros will aid in reading and optionally clearing counter registers.
     * The clear operation will be triggered by matching the 'clear_mask' with both a
     * counter type (ctype) and a counter direction (cdir - TX or RX).
     */
#define CHIPREAD(reg, cnt) { REG_RD(reg, &v); vtss_cmn_counter_32_update(v, cnt, clear); }

    vtss_mrp_data_t               *mrp_data = &vtss_state->mrp.data[mrp_idx];
    u32                           v;
    vtss_mrp_internal_counters_t  *p_chipcnt = &mrp_data->p_counters;
    vtss_mrp_internal_counters_t  *s_chipcnt = &mrp_data->s_counters;
    vtss_mrp_internal_counters_t  *i_chipcnt = &mrp_data->i_counters;
    vtss_voe_idx_t                p_voe_idx = 0;
    vtss_voe_idx_t                s_voe_idx = 0;
    vtss_voe_idx_t                i_voe_idx = 0;

    if (!mrp_data->active) {
        return VTSS_RC_OK;
    }

    p_voe_idx = mrp_data->p_voe_idx;
    s_voe_idx = mrp_data->s_voe_idx;
    if (mrp_data->conf.i_port < VTSS_PORTS) {
        i_voe_idx = mrp_data->i_voe_idx;
    }

    /* P port counter update */
    CHIPREAD(VTSS_VOP_MRP_TST_RX_CNT(p_voe_idx), &p_chipcnt->tst_rx_count);
    CHIPREAD(VTSS_VOP_MRP_ITST_RX_CNT(p_voe_idx), &p_chipcnt->itst_rx_count);

    /* S port counter update */
    CHIPREAD(VTSS_VOP_MRP_TST_RX_CNT(s_voe_idx), &s_chipcnt->tst_rx_count);
    CHIPREAD(VTSS_VOP_MRP_ITST_RX_CNT(s_voe_idx), &s_chipcnt->itst_rx_count);

    if (mrp_data->conf.i_port < VTSS_PORTS) {
        /* I port counter update */
        CHIPREAD(VTSS_VOP_MRP_TST_RX_CNT(i_voe_idx), &i_chipcnt->tst_rx_count);
        CHIPREAD(VTSS_VOP_MRP_ITST_RX_CNT(i_voe_idx), &i_chipcnt->itst_rx_count);
    }

    return VTSS_RC_OK;
#undef CHIPREAD
}

static void mrp_instance_default(vtss_state_t *vtss_state, vtss_mrp_data_t *mrp)
{
    memset(mrp, 0, sizeof(*mrp));
    mrp->ring_state    = VTSS_MRP_RING_STATE_OPEN;
    mrp->in_ring_state = VTSS_MRP_RING_STATE_OPEN;
    mrp->tst_loc_idx   = LOC_PERIOD_CNT;
    mrp->itst_loc_idx  = LOC_PERIOD_CNT;
    mrp->p_port_state  = VTSS_MRP_PORT_STATE_BLOCKED;
    mrp->s_port_state  = VTSS_MRP_PORT_STATE_BLOCKED;
    mrp->i_port_state  = VTSS_MRP_PORT_STATE_BLOCKED;
    mrp->p_voe_idx     = VTSS_VOE_IDX_NONE;
    mrp->s_voe_idx     = VTSS_VOE_IDX_NONE;
    mrp->i_voe_idx     = VTSS_VOE_IDX_NONE;

    mrp->tst_loc_conf.tst_interval   = 3500; /* 3.5 ms */
    mrp->tst_loc_conf.tst_mon_count  = 3;
    mrp->tst_loc_conf.itst_interval  = 3500; /* 3.5 ms */
    mrp->tst_loc_conf.itst_mon_count = 3;

    mrp->conf.ring_role    = VTSS_MRP_RING_ROLE_MANAGER;
    mrp->conf.in_ring_role = VTSS_MRP_RING_ROLE_DISABLED;
    mrp->conf.p_port       = VTSS_PORT_NO_NONE;
    mrp->conf.s_port       = VTSS_PORT_NO_NONE;
    mrp->conf.i_port       = VTSS_PORT_NO_NONE;
}

static u32 ring_state_calc(vtss_mrp_ring_state_t state)
{
    switch (state) {
    case VTSS_MRP_RING_STATE_CLOSED:
        return 1;
    case VTSS_MRP_RING_STATE_OPEN:
        return 0;
    }

    VTSS_D("Unknown ring state");
    return 0;
}

static vtss_rc mrp_init_port(vtss_state_t *vtss_state, vtss_voe_idx_t voe_idx, u32 port_role)
{
    int i;

    /* To assure default in registers */
    REG_WR(VTSS_VOP_MRP_VOE_COMMON_CFG(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_MRP_CTRL(voe_idx), VTSS_F_VOP_MRP_MRP_CTRL_MRP_VERSION(1));
    REG_WR(VTSS_VOP_MRP_MRP_FWD_CTRL(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_RING_MASK_CFG(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_ICON_MASK_CFG(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_TST_FWD_CTRL(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_TST_CFG(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_TST_PRIO_CFG(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_ITST_FWD_CTRL(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_ITST_CFG(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_MRP_MAC_LSB(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_MRP_MAC_MSB(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_BEST_MAC_LSB(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_BEST_MAC_MSB(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_MRP_TX_CFG(voe_idx, 0), 0);
    REG_WR(VTSS_VOP_MRP_MRP_TX_CFG(voe_idx, 1), 0);

    /* Enable MEP and LOC_SCAN */
    REG_WRM(VTSS_VOP_VOP_CTRL,
            VTSS_F_VOP_VOP_CTRL_LOC_SCAN_ENA(1) | VTSS_F_VOP_VOP_CTRL_VOP_ENA(1),
            VTSS_M_VOP_VOP_CTRL_LOC_SCAN_ENA | VTSS_M_VOP_VOP_CTRL_VOP_ENA);

    // Activate MRP endpoint
    // We do not enable sequence error detection, because then we cannot operate
    // with MRP partners that don't update the sequence number.
    REG_WRM(VTSS_VOP_MRP_MRP_CTRL(voe_idx),
            VTSS_F_VOP_MRP_MRP_CTRL_MRP_ENA(1) | VTSS_F_VOP_MRP_MRP_CTRL_CHK_DMAC_ENA(1) | VTSS_F_VOP_MRP_MRP_CTRL_CHK_VERSION_ENA(1),
            VTSS_M_VOP_MRP_MRP_CTRL_MRP_ENA | VTSS_M_VOP_MRP_MRP_CTRL_CHK_DMAC_ENA | VTSS_M_VOP_MRP_MRP_CTRL_CHK_VERSION_ENA);

    /* Enable VOE */
    REG_WRM(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), VTSS_F_VOP_VOE_MISC_CONFIG_VOE_ENA(4), VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA);

    for (i = 0; i < 2; i++) {
        // Default ring state, number of transitions and port role.
        // Used if REW_MRP_TX_CFG_MRP_MISC_UPD is set
        REG_WRM(VTSS_VOP_MRP_MRP_TX_CFG(voe_idx, i == 0 ? CONFIG_TEST : CONFIG_INTEST),
            VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_STATE(ring_state_calc(VTSS_MRP_RING_STATE_OPEN)) |
            VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_PORTROLE(port_role)                              |
            VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_TRANS(0),
            VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_STATE    |
            VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_PORTROLE |
            VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_TRANS);
    }

    /* Forward selection is default "forward" */
    REG_WR(VTSS_VOP_MRP_MRP_FWD_CTRL(voe_idx), 0);

    /* Start with sequence number zero */
    // RBNTBD: This is the expected Rx sequence number, not the Tx sequence
    // number inserted in the frame. According to the register list under
    // REW:PORT[0-9]:MRP_TX_CFG[0-1].MRP_SEQ_UPD_ENA, the register that holds
    // the next sequence number is selected by the IFH's SEQ_NUM field, which
    // points to one of the 256 entries in REW:PTP_SEQ_NO:PTP_SEQ_NO[0-255].
    // How can such an entry be allocated without interfering with PTP, CCM, and
    // DLR?
    // Also, how can this be conveyed to the application, so that it can insert
    // the correct number in IFH.SEQ_NUM? Sounds impractical.
    REG_WR(VTSS_VOP_MRP_MRP_RX_SEQ(voe_idx, 0), 0);
    REG_WR(VTSS_VOP_MRP_MRP_RX_SEQ(voe_idx, 1), 0);

    return VTSS_RC_OK;
}

static vtss_rc mrp_uninit_port(vtss_state_t *vtss_state, vtss_voe_idx_t voe_idx)
{
    REG_WRM(VTSS_VOP_MRP_NXT_LOC_HMO(voe_idx),
            VTSS_F_VOP_MRP_NXT_LOC_HMO_NXT_LOC_CPU_HITME_ONCE(0),
            VTSS_M_VOP_MRP_NXT_LOC_HMO_NXT_LOC_CPU_HITME_ONCE);

    REG_WRM(VTSS_VOP_MRP_ITST_NXT_LOC_HMO(voe_idx),
            VTSS_F_VOP_MRP_ITST_NXT_LOC_HMO_ITST_NXT_LOC_CPU_HITME_ONCE(0),
            VTSS_M_VOP_MRP_ITST_NXT_LOC_HMO_ITST_NXT_LOC_CPU_HITME_ONCE);

    /* Deactivate MRP endpoint */
    REG_WRM(VTSS_VOP_MRP_MRP_CTRL(voe_idx), VTSS_F_VOP_MRP_MRP_CTRL_MRP_ENA(0), VTSS_M_VOP_MRP_MRP_CTRL_MRP_ENA);

    /* Disable VOE */
    REG_WRM(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), VTSS_F_VOP_VOE_MISC_CONFIG_VOE_ENA(0), VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA);

    // Clear best MAC
    REG_WR(VTSS_VOP_MRP_BEST_MAC_LSB(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_BEST_MAC_MSB(voe_idx), 0);

    // Clear best priority
    REG_WRM(VTSS_VOP_MRP_TST_PRIO_STAT(voe_idx), VTSS_F_VOP_MRP_TST_PRIO_STAT_BEST_PRIO(0), VTSS_M_VOP_MRP_TST_PRIO_STAT_BEST_PRIO);

    // Clear sticky bits
    REG_WR(VTSS_VOP_MRP_MRP_STICKY(voe_idx), 0xFFFFFFFF);

    // Clear counters, by writing directly to the chip, because
    // mrp_counter_update() updates the shadow counter values, not the chip
    // counter values. The shadow counter values will be cleared by a memset()
    // in just a moment.
    REG_WR(VTSS_VOP_MRP_TST_RX_CNT(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_ITST_RX_CNT(voe_idx), 0);

    // Also clear these two, which are not directly visible to the user, but
    // available with a 'deb api cil mrp'.
    REG_WR(VTSS_VOP_MRP_TST_RX_LOC_CNT(voe_idx), 0);
    REG_WR(VTSS_VOP_MRP_ITST_RX_LOC_CNT(voe_idx), 0);

    return VTSS_RC_OK;
}

static vtss_rc mrp_port_update_mac(vtss_state_t *vtss_state, vtss_voe_idx_t voe_idx, const u8 *mac)
{
    u32 macl = 0, mach = 0;

    mach |= mac[0] << 8;
    mach |= mac[1] << 0;
    macl |= mac[2] << 24;
    macl |= mac[3] << 16;
    macl |= mac[4] << 8;
    macl |= mac[5] << 0;

    REG_WR(VTSS_VOP_MRP_MRP_MAC_LSB(voe_idx), macl);
    REG_WR(VTSS_VOP_MRP_MRP_MAC_MSB(voe_idx), mach);

    return VTSS_RC_OK;
}

static vtss_rc mrp_port_update_best_mrm(vtss_state_t *vtss_state, vtss_voe_idx_t voe_idx, const vtss_mrp_best_mrm_t *best)
{
    u32 macl = 0, mach = 0;

    mach |= best->mac.addr[0] << 8;
    mach |= best->mac.addr[1] << 0;
    macl |= best->mac.addr[2] << 24;
    macl |= best->mac.addr[3] << 16;
    macl |= best->mac.addr[4] << 8;
    macl |= best->mac.addr[5] << 0;

    REG_WR(VTSS_VOP_MRP_BEST_MAC_LSB(voe_idx), macl);
    REG_WR(VTSS_VOP_MRP_BEST_MAC_MSB(voe_idx), mach);
    REG_WRM(VTSS_VOP_MRP_TST_PRIO_STAT(voe_idx), VTSS_F_VOP_MRP_TST_PRIO_STAT_BEST_PRIO(best->prio), VTSS_M_VOP_MRP_TST_PRIO_STAT_BEST_PRIO);

    return VTSS_RC_OK;
}

static u32 mrp_fwd_sel(BOOL fwd, BOOL copy_to_cpu)
{
    if (fwd) {
        return copy_to_cpu ? FWD_COPY_CPU     : FWD_NOP;
    } else {
        return copy_to_cpu ? FWD_REDIRECT_CPU : FWD_DISCARD;
    }
}

static vtss_rc mrp_control_forwarding(vtss_state_t *vtss_state, vtss_mrp_data_t *mrp)
{
    BOOL has_ic      = mrp->conf.in_ring_role != VTSS_MRP_RING_ROLE_DISABLED;
    vtss_voe_idx_t p_voe_idx = mrp->p_voe_idx;
    vtss_voe_idx_t s_voe_idx = mrp->s_voe_idx;
    vtss_voe_idx_t i_voe_idx = has_ic ? mrp->i_voe_idx : 0;
    u32  p_chip_port = VTSS_CHIP_PORT(mrp->conf.p_port);
    u32  s_chip_port = VTSS_CHIP_PORT(mrp->conf.s_port);
    u32  i_chip_port = has_ic ? VTSS_CHIP_PORT(mrp->conf.i_port) : 0;
    BOOL p_fwd       = mrp->p_port_state == VTSS_MRP_PORT_STATE_FORWARDING;
    BOOL s_fwd       = mrp->s_port_state == VTSS_MRP_PORT_STATE_FORWARDING;
    BOOL i_fwd       = mrp->i_port_state == VTSS_MRP_PORT_STATE_FORWARDING && has_ic;
    BOOL test_r2r,   test_r2i,   test_i2r,   test_r2c,                 test_i2c;
    BOOL ctrl_r2r,   ctrl_r2i,   ctrl_i2r,   ctrl_r2c,                 ctrl_i2c;
    BOOL inctrl_r2r, inctrl_r2i, inctrl_i2r, inctrl_r2ct, inctrl_r2co, inctrl_i2c;
    BOOL test_p, ctrl_p, inctrl_p, test_c, ctrl_c, inctrl_ct, inctrl_co;
    BOOL intest_own_r2r, intest_own_r2i, intest_own_i2r, intest_own_r2c, intest_own_i2c;
    BOOL intest_rem_r2r, intest_rem_r2i, intest_rem_i2r, intest_rem_r2c, intest_rem_i2c;
    u32  test_sel, ctrl_sel, inctrl_t_sel, inctrl_o_sel, intest_own_fwd_sel, intest_rem_fwd_sel;
    u32  p_mask, s_mask, i_mask, ring_mask, icon_mask;
    int  p;

    VTSS_I("ring_role = %s, mra = %d, p_fwd = %s, s_fwd = %s, i_fwd = %s", ring_role2txt(mrp->conf.ring_role), mrp->conf.mra, port_state2txt(mrp->p_port_state), port_state2txt(mrp->s_port_state), port_state2txt(mrp->i_port_state));

    // The purpose of this function is to select whether to forward various MRP
    // PDU types between ring ports, from I/C port to a ring port or from a ring
    // port to an I/C port. We also figure out whether to copy these PDU types
    // to the CPU.

    // To begin with, we sort the PDU types into four categories:
    // MC_TEST, MC_CONTROL, MC_INTEST, and MC_INCONTROL (named after the
    // multicast DMAC of the individual PDU types), where:
    //
    // MC_TEST PDU types are:
    //   - MRP_Test
    //   - MRP_TestMgrNAck
    //   - MRP_TestPropagate
    //
    // MC_CONTROL PDU types are:
    //   - MRP_LinkChange (a.k.a. MRP_LinkUp and MRP_LinkDown)
    //   - MRP_TopologyChange
    //   - MRP_Option other than MRP_TestMgrNAck and MRP_TestPropagate
    //
    // MC_INTEST PDU types are:
    //   - MRP_InTest
    //
    // MC_INCONTROL PDU types are:
    //   - MRP_InLinkChange (a.k.a. MRP_InLinkUp and MRP_InLinkDown)
    //   - MRP_InLinkStatusPoll
    //   - MRP_InTopologyChange

    // The variables are named like this:
    // - xxx_r2r:  Forwarding of xxx MC type from ring port to ring port.
    // - xxx_r2i:  Forwarding of xxx MC type from ring port to I/C port.
    // - xxx_i2r:  Forwarding of xxx MC type from I/C port  to ring port.
    // - xxx_r2c:  Copying/redirection of xxx MC type from ring port to CPU.
    // - xxx_r2ct: Copying/redirection of MRP_InTopologyChange PDUs to the CPU.
    // - xxx_r2co: Copying/redirection of other MC_INCONTROL PDUs to the CPU.
    // - xxx_i2c:  Copying/redirection of xxx MC type from I/C port to CPU.

    // MC_TEST:

    // Forwarding and CPU copying of MRP_Test PDUs are handled in
    // mrp_process_ring_test(), but we must make sure to set it to FWD_NOP.
    // The following variables concern the remaining two MC_TEST PDU types,
    // MRP_TestMgrNAck and MRP_TestPropagate.

    // We forward between ring ports if we are currently acting as an MRC and
    // both ring ports are forwarding, but we never forward from a ring port to
    // the I/C port or vice versa.
    test_r2r = mrp->conf.ring_role == VTSS_MRP_RING_ROLE_CLIENT && p_fwd && s_fwd;
    test_r2i = FALSE;
    test_i2r = FALSE;

    // We get these PDUs to the CPU if we are an MRM or an MRC originally
    // configured as an MRA, but only if received on a ring port. If received on
    // the I/C port, we discard it.
    test_r2c = mrp->conf.ring_role == VTSS_MRP_RING_ROLE_MANAGER || mrp->conf.mra;
    test_i2c = FALSE;

    // MC_CONTROL:

    // Forwarding between ring ports and between ring port and I/C port is
    // identical to the MC_TEST PDUs.
    ctrl_r2r = test_r2r;
    ctrl_r2i = test_r2i;
    ctrl_i2r = test_i2r;

    // We always copy these PDUs to the CPU if received on ring ports and never
    // if received on the I/C port.
    ctrl_r2c = TRUE;
    ctrl_i2c = FALSE;

    // MC_INTEST:

    // By default, we don't copy any MRP_InTest PDUs to the CPU.
    intest_own_r2c = FALSE;
    intest_own_i2c = FALSE;
    intest_rem_r2c = FALSE;
    intest_rem_i2c = FALSE;

    if (mrp->conf.in_ring_role == VTSS_MRP_RING_ROLE_MANAGER) {
        // MIM-RC and MIM-LC.
        // MRP_InTest, own: Always processed (if RC) and discarded (both RC and
        // LC).
        intest_own_r2r = FALSE;
        intest_own_r2i = FALSE;
        intest_own_i2r = FALSE;

        // MRP_InTest, remote: The implementation supports multiple I/C rings,
        // where all of them are in RC-mode. It does, however, not support
        // multiple I/C rings, where at least one of them is in RC-mode.
        // Therefore, we don't really care what happens to remote MRP_InTest
        // PDUs, so we simply discard them, when we ourselves are a MIM.
        intest_rem_r2r = FALSE;
        intest_rem_r2i = FALSE;
        intest_rem_i2r = FALSE;

        // If requested to, we copy MRP_InTest from remote to CPU for multiple
        // MIMs detection.
        intest_rem_i2c = mrp->tst_copy_conf.itst_to_cpu;
        intest_rem_r2c = mrp->tst_copy_conf.itst_to_cpu;
    } else if (mrp->conf.in_ring_role == VTSS_MRP_RING_ROLE_CLIENT) {
        // MIC. Whether we are in LC- or RC-mode doesn't matter.
        // Never forward from ring port to other ring port, whether it's our
        // own or somebody else's MRP_InTest (in reality we should, but we only
        // support one interconnection ring if using RC-mode, in which case the
        // MIC will never forward from ring port to ring port).
        intest_own_r2r = FALSE;
        intest_rem_r2r = FALSE;

        // Forward from ring port to I/C port if it's forwarding. When we are a
        // MIC, there's no such thing as own MRP_InTest PDUs (and they are not
        // processed).
        intest_own_r2i = i_fwd;
        intest_rem_r2i = i_fwd;

        // Forward from I/C port to forwarding ring ports.
        intest_own_i2r = p_fwd || s_fwd;
        intest_rem_i2r = p_fwd || s_fwd;
    } else {
        // MRM/MRC without MIM/MIC.
        // Forward between ring ports if forwarding. When we don't have a
        // MIM/MIC role, there's no such thing as own MRP_InTest PDUs, and we
        // don't process them, just control forwarding.
        intest_own_r2r = p_fwd && s_fwd;
        intest_rem_r2r = p_fwd && s_fwd;

        // We don't have I/C port.
        intest_own_i2r = FALSE;
        intest_rem_i2r = FALSE;
        intest_own_r2i = FALSE;
        intest_rem_r2i = FALSE;
    }

    // Configure processing of MRP_InTest PDUs
    for (p = 0; p < 3; p++) {
        if (p == 2 && !has_ic) {
            continue;
        }

        intest_rem_fwd_sel = p == 2 ? mrp_fwd_sel(intest_rem_i2r, intest_rem_i2c) : mrp_fwd_sel(intest_rem_r2r, intest_rem_r2c);
        intest_own_fwd_sel = p == 2 ? mrp_fwd_sel(intest_own_i2r, intest_own_i2c) : mrp_fwd_sel(intest_own_r2r, intest_own_r2c);

        VTSS_I("p = %d. intest_rem_fwd_sel = %s, intest_own_fwd_sel = %s", p, sel2txt(intest_rem_fwd_sel), sel2txt(intest_own_fwd_sel));

        REG_WRM(VTSS_VOP_MRP_ITST_FWD_CTRL(p == 0 ? p_voe_idx : p == 1 ? s_voe_idx : i_voe_idx),
                VTSS_F_VOP_MRP_ITST_FWD_CTRL_ITST_REM_FWD_SEL(intest_rem_fwd_sel) |
                VTSS_F_VOP_MRP_ITST_FWD_CTRL_ITST_OWN_FWD_SEL(intest_own_fwd_sel),
                VTSS_M_VOP_MRP_ITST_FWD_CTRL_ITST_REM_FWD_SEL |
                VTSS_M_VOP_MRP_ITST_FWD_CTRL_ITST_OWN_FWD_SEL);
    }

    // MC_INCONTROL:

    // If we are a MIM or a MIC (whether in LC- or RC-mode), these PDUs are
    // always S/W forwarded in order to be able to support multiple
    // interconnections (three or more rings). The reason is that hardware
    // cannot match on these PDUs' IID (Interconnection ID), so it doesn't know
    // in which direction to forward them.
    // This also implies that we don't support RC-mode on two or more
    // interconnection rings (three or more MRP rings).
    if (mrp->conf.in_ring_role != VTSS_MRP_RING_ROLE_DISABLED) {
        // We are a MIM or a MIC. Copy them to the CPU and let S/W handle the
        // forwarding (based on IID).
        inctrl_r2r  = FALSE;
        inctrl_r2i  = FALSE;
        inctrl_i2r  = FALSE;
        inctrl_r2ct = TRUE;
        inctrl_r2co = TRUE;
        inctrl_i2c  = TRUE;
    } else {
        // We are an MRM/MRC w/o MIM/MIC. Forward blindly if both ring ports are
        // forwarding.
        // An MRM needs the MRP_InTopologyChange PDUs to possibly transmit
        // MRP_TopologyChange PDUs on its own ring.
        inctrl_r2r  = p_fwd && s_fwd;
        inctrl_r2i  = FALSE; // N/A, since we don't have an I/C port.
        inctrl_i2r  = FALSE; // N/A, since we don't have an I/C port.
        inctrl_r2ct = mrp->conf.ring_role == VTSS_MRP_RING_ROLE_MANAGER; // Only care about MRP_InTopologyChange PDUs
        inctrl_r2co = FALSE;                                             // Don't care about other MC_INCONTROL PDUs.
        inctrl_i2c  = FALSE; // N/A, since we don't have an I/C port.
    }

    // Configure forwarding/CPU copying of MRP PDUs received on a given port, p.
    for (p = 0; p < 3; p++) {
        if (p == 2 && !has_ic) {
            // Not using I/C port.
            continue;
        }

        if (p == 0 || p == 1) {
            // Forward from a ring port torwards some other port (ring or I/C)?
            // We forward MRP PDUs if they must go to either the other ring port
            // or to the I/C port.
            test_p   = test_r2r   || test_r2i;
            ctrl_p   = ctrl_r2r   || ctrl_r2i;
            inctrl_p = inctrl_r2r || inctrl_r2i;

            // Copy frames from ring port to CPU?
            test_c    = test_r2c;
            ctrl_c    = ctrl_r2c;
            inctrl_ct = inctrl_r2ct; // MRP_InTopologyChange PDUs
            inctrl_co = inctrl_r2co; // Other MC_INCONTROL PDUs
        } else {
            // Forward from I/C port to ring port?
            test_p   = test_i2r;
            ctrl_p   = ctrl_i2r;
            inctrl_p = inctrl_i2r;

            // Copy frames from I/C port to CPU?
            test_c    = test_i2c;
            ctrl_c    = ctrl_i2c;
            inctrl_ct = inctrl_i2c;
            inctrl_co = inctrl_i2c;
        }

        test_sel     = mrp_fwd_sel(test_p,   test_c);
        ctrl_sel     = mrp_fwd_sel(ctrl_p,   ctrl_c);
        inctrl_t_sel = mrp_fwd_sel(inctrl_p, inctrl_ct);
        inctrl_o_sel = mrp_fwd_sel(inctrl_p, inctrl_co);

        // A few fields in the register are controlled directly. These are:
        //   ICON_MASK_ENA:
        //     This is always set on all ports, which means that forwarding of
        //     MRP_InXxx PDUs is controlled by the  MRP_Ixxx_FWD_SEL fields of
        //     this register and the MEP_ICON_MASK_CFG register.
        //   RING_MASK_ENA:
        //     This is always set on ring ports, but never on the I/C port,
        //     because MRP_Xxx PDUs are not supposed to be forwarded across I/C
        //     ports. If set, the actual forwarding is controlled by the
        //     MRP_xxx_FWD_SEL fields of this register and the MEP_RING_MASK_CFG
        //     register.
        //   ERR_FWD_SEL:
        //     Frames received on any port that fail MAC, version or sequence
        //     check (if enabled) are silently discarded.
        //   MRP_TST_FWD_SEL:
        //     This must be set to FWD_NOP on ring ports, because otherwise, we
        //     end up receiving MRP_Test PDUs at the CPU whether or not we have
        //     asked for them, because it opens up a backdoor when MRP_TEST_ENA
        //     is set. The actual forwarding is controlled with the
        //     MEP_TST_FWD_CTRL register.
        //     It must be set to FWD_DISCARD on the I/C port, because we don't
        //     want MRP_Test PDUs to be forwarded anywhere (not even to the CPU)
        //     when received on the I/C port. On the I/C port MRP_TEST_ENA is
        //     cleared.
        //   MRP_ITST_FWD_SEL:
        //     This must be set to FWD_NOP, because otherwise, we end up
        //     receiving MRP_InTest PDUs at the CPU whether or not we have asked
        //     for them, because it opens up a backdoor. The actual forwarding
        //     is controlled with the MEP_ITST_FWD_CTRL register.
        //   OTHER_FWD_SEL:
        //     We silently discard MRP PDUs that we don't recognize the type of.
        REG_WRM(VTSS_VOP_MRP_MRP_FWD_CTRL(p == 0 ? p_voe_idx : p == 1 ? s_voe_idx : i_voe_idx),
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_ICON_MASK_ENA(   1)                              |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_RING_MASK_ENA(   p != 2)                         |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_ERR_FWD_SEL(     FWD_DISCARD)                    |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_TST_FWD_SEL( p == 2 ? FWD_DISCARD : FWD_NOP) |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_TPM_FWD_SEL( test_sel)                       |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_LD_FWD_SEL(  ctrl_sel)                       |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_LU_FWD_SEL(  ctrl_sel)                       |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_TC_FWD_SEL(  ctrl_sel)                       |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ITST_FWD_SEL(FWD_NOP)                        |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ITC_FWD_SEL( inctrl_t_sel)                   |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ILD_FWD_SEL( inctrl_o_sel)                   |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ILU_FWD_SEL( inctrl_o_sel)                   |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ILSP_FWD_SEL(inctrl_o_sel)                   |
                VTSS_F_VOP_MRP_MRP_FWD_CTRL_OTHER_FWD_SEL(  FWD_DISCARD),
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_ICON_MASK_ENA    |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_RING_MASK_ENA    |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_ERR_FWD_SEL      |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_TST_FWD_SEL  |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_TPM_FWD_SEL  |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_LD_FWD_SEL   |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_LU_FWD_SEL   |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_TC_FWD_SEL   |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ITST_FWD_SEL |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ITC_FWD_SEL  |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ILD_FWD_SEL  |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ILU_FWD_SEL  |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ILSP_FWD_SEL |
                VTSS_M_VOP_MRP_MRP_FWD_CTRL_OTHER_FWD_SEL);
    }

    // Configure destination ports for MRP PDUs.

    // A given mask will be zero if the port is not allowed to forward.
    p_mask = p_fwd           ? VTSS_BIT(p_chip_port) : 0;
    s_mask = s_fwd           ? VTSS_BIT(s_chip_port) : 0;
    i_mask = i_fwd && has_ic ? VTSS_BIT(i_chip_port) : 0;

    for (p = 0; p < 3; p++) {
        if (p == 2 && !has_ic) {
            // Not using I/C port.
            continue;
        }

        ring_mask = 0;
        icon_mask = 0;

        if (p == 0 || p == 1) {
            if (test_r2r || ctrl_r2r) {
                // Forwarding at least one MRP_Xxx PDU type from one ring port
                // to the opposite if that is forwarding.
                ring_mask |= p == 0 ? s_mask : p_mask;
            }

            if (intest_own_r2r || intest_rem_r2r || inctrl_r2r) {
                // Forwarding at least one MRP_InXxx PDU type from one ring port
                // to the opposite if that is forwarding.
                icon_mask |= p == 0 ? s_mask : p_mask;
            }

            if (test_r2i || ctrl_r2i) {
                // Forwarding at least one MRP_Xxx PDU type from a ring port to
                // the I/C port if forwarding.
                ring_mask |= i_mask;
            }

            if (intest_own_r2i || intest_rem_r2i || inctrl_r2i) {
                // Forwarding at least one MRP_InXxx PDU type from a ring port
                // to the I/C port if forwarding.
                icon_mask |= i_mask;
            }
        } else {
            if (test_i2r || ctrl_i2r) {
                // Forwarding at least one MRP_Xxx PDU type from the I/C port to
                // only-forwarding ring ports.
                ring_mask |= (p_mask | s_mask);
            }

            if (intest_own_i2r || intest_rem_i2r || inctrl_i2r) {
                // Forwarding at least one MRP_InXxx PDU type from the I/C port
                // to only-forwarding ring ports.
                icon_mask |= (p_mask | s_mask);
            }
        }

        REG_WR(VTSS_VOP_MRP_RING_MASK_CFG(p == 0 ? p_voe_idx : p == 1 ? s_voe_idx : i_voe_idx), ring_mask);
        REG_WR(VTSS_VOP_MRP_ICON_MASK_CFG(p == 0 ? p_voe_idx : p == 1 ? s_voe_idx : i_voe_idx), icon_mask);
    }

    return VTSS_RC_OK;
}

static vtss_rc mrp_rewrite_ring_test(vtss_state_t *vtss_state, vtss_mrp_data_t *mrp)
{
    vtss_voe_idx_t  p_voe_idx = mrp->p_voe_idx;
    vtss_voe_idx_t  s_voe_idx = mrp->s_voe_idx;
    BOOL update;
    int  p;

    update = mrp->conf.ring_role == VTSS_MRP_RING_ROLE_MANAGER;

    for (p = 0; p < 2; p++) {
        REG_WRM(VTSS_VOP_MRP_MRP_TX_CFG(p == 0 ? p_voe_idx : s_voe_idx, CONFIG_TEST),
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_TIMESTAMP_UPD_ENA(update ? 1 : 0) |
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_SEQ_UPD_ENA(      update ? 1 : 0) |
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_MISC_UPD_ENA(     update ? 1 : 0),
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_TIMESTAMP_UPD_ENA |
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_SEQ_UPD_ENA       |
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_MISC_UPD_ENA);
    }

    return VTSS_RC_OK;
}

static vtss_rc mrp_rewrite_in_test(vtss_state_t *vtss_state, vtss_mrp_data_t *mrp)
{
    vtss_voe_idx_t p_voe_idx = mrp->p_voe_idx;
    vtss_voe_idx_t s_voe_idx = mrp->s_voe_idx;
    vtss_voe_idx_t i_voe_idx = 0;
    int p;
    BOOL in_update;

    if (mrp->conf.i_port < VTSS_PORTS) {
        i_voe_idx = mrp->i_voe_idx;
    }

    in_update = mrp->conf.in_ring_role == VTSS_MRP_RING_ROLE_MANAGER && mrp->conf.in_rc_mode;

    for (p = 0; p < 3; p++) {
        if (mrp->conf.i_port >= VTSS_PORTS) {
            continue;
        }

        REG_WRM(VTSS_VOP_MRP_MRP_TX_CFG(p == 0 ? p_voe_idx : p == 1 ? s_voe_idx : i_voe_idx, CONFIG_INTEST),
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_TIMESTAMP_UPD_ENA(in_update ? 1 : 0) |
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_SEQ_UPD_ENA(      in_update ? 1 : 0) |
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_MISC_UPD_ENA(     in_update ? 1 : 0),
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_TIMESTAMP_UPD_ENA |
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_SEQ_UPD_ENA       |
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_MISC_UPD_ENA);
    }

    return VTSS_RC_OK;
}

static vtss_rc loc_period_configure(vtss_state_t *vtss_state, u32 loc_idx, u64 interval_in_us)
{
    u32 value, base_tick_ps;
    u64 interval_in_ps;

    VTSS_D("loc_idx %u  interval_in_us %" PRIu64 "", loc_idx, interval_in_us);

    // Calculate the LOC period base tick count and LOC interval in picoseconds
    REG_RD(VTSS_VOP_LOC_CTRL_2, &value);
    value = VTSS_X_VOP_LOC_CTRL_2_LOC_BASE_TICK_CNT(value);    /* This is the LOC base tick in clock cycles */
    u32 clk_period_in_ps = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);  /* Get the clock period in picoseconds */
    base_tick_ps = clk_period_in_ps * value;

    // Configure LOC period
    interval_in_ps = interval_in_us * 1000000;
    value = (interval_in_ps / base_tick_ps) + ((interval_in_ps % base_tick_ps) ? 1 : 0);
    REG_WR(VTSS_VOP_LOC_PERIOD_CFG(loc_idx), value);

    return VTSS_RC_OK;
}

static vtss_rc mrp_loc_configure(vtss_state_t *vtss_state, vtss_mrp_data_t *mrp)
{
    BOOL           process = mrp->conf.mra || mrp->conf.ring_role == VTSS_MRP_RING_ROLE_MANAGER;
    vtss_voe_idx_t voe_idx;
    int            p;

    // Configure LOC on ring ports
    for (p = 0; p < 2; p++) {
        voe_idx = p == 0 ? mrp->p_voe_idx : mrp->s_voe_idx;

        // Configure processing of MRP_Test PDUs
        REG_WRM(VTSS_VOP_MRP_MRP_CTRL(voe_idx),
                VTSS_F_VOP_MRP_MRP_CTRL_MRP_TST_ENA(process ? 1 : 0),
                VTSS_M_VOP_MRP_MRP_CTRL_MRP_TST_ENA);

        // Configure priority
        REG_WRM(VTSS_VOP_MRP_TST_PRIO_CFG(voe_idx),
                VTSS_F_VOP_MRP_TST_PRIO_CFG_OWN_PRIO(mrp->conf.mra_priority),
                VTSS_M_VOP_MRP_TST_PRIO_CFG_OWN_PRIO);

        // Configure LoC timer index.
        REG_WRM(VTSS_VOP_MRP_TST_CFG(voe_idx),
                VTSS_F_VOP_MRP_TST_CFG_CLR_MISS_CNT_ENA(process ? 1 : 0)                 |
                VTSS_F_VOP_MRP_TST_CFG_LOC_PERIOD(process ? mrp->tst_loc_idx + 1 : 0),
                VTSS_M_VOP_MRP_TST_CFG_CLR_MISS_CNT_ENA |
                VTSS_M_VOP_MRP_TST_CFG_LOC_PERIOD);

        REG_WRM(VTSS_VOP_MRP_TST_STAT(voe_idx),
                VTSS_F_VOP_MRP_TST_STAT_MAX_MISS_CNT(mrp->tst_loc_conf.tst_mon_count * 2) |
                VTSS_F_VOP_MRP_TST_STAT_MISS_CNT(0),
                VTSS_M_VOP_MRP_TST_STAT_MAX_MISS_CNT     |
                VTSS_M_VOP_MRP_TST_STAT_MISS_CNT);

        // Clear LoC sticky bit
        REG_WR(VTSS_VOP_MRP_MRP_STICKY(voe_idx), VTSS_M_VOP_MRP_MRP_STICKY_TST_LOC_STICKY);
    }

    if (mrp->tst_loc_idx != LOC_PERIOD_CNT) {
        VTSS_RC(loc_period_configure(vtss_state, mrp->tst_loc_idx, mrp->tst_loc_conf.tst_interval));
    }

    return VTSS_RC_OK;
}

static vtss_rc mrp_in_loc_configure(vtss_state_t *vtss_state, vtss_mrp_data_t *mrp)
{
    BOOL           process = mrp->conf.in_ring_role == VTSS_MRP_RING_ROLE_MANAGER && mrp->conf.in_rc_mode;
    vtss_voe_idx_t voe_idx, cnt;
    int            p;

    // Configure LOC on all ports
    for (p = 0; p < 3; p++) {
        if (p == 2 && mrp->conf.in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
            continue;
        }

        voe_idx = p == 0 ? mrp->p_voe_idx : p == 1 ? mrp->s_voe_idx : mrp->i_voe_idx;

        // Configure processing of MRP_InTest PDUs
        REG_WRM(VTSS_VOP_MRP_MRP_CTRL(voe_idx),
                VTSS_F_VOP_MRP_MRP_CTRL_MRP_ITST_ENA(process ? 1 : 0),
                VTSS_M_VOP_MRP_MRP_CTRL_MRP_ITST_ENA);

        // Chip bug: The standard's Table 61 says MRP_InTest monitoring count
        // must be 8 (independent of recovery profile). This means that we would
        // like to write 16 to the MAX_MISS_CNT field, but this field is only
        // four bits wide, so it'll become 0, causing LoC forever. We fix it
        // here, by writing 15 if itst_mon_count is > 7.
        // Perhaps a better fix is to use itst_mon_count as is, but modify the
        // LoC period to be twice the value specified in itst_interval.
        cnt = mrp->tst_loc_conf.itst_mon_count > 7 ? 15 : 2 * mrp->tst_loc_conf.itst_mon_count;

        // Configure LoC timer index.
        REG_WRM(VTSS_VOP_MRP_ITST_CFG(voe_idx),
                VTSS_F_VOP_MRP_ITST_CFG_ITST_CLR_MISS_CNT_ENA(process ? 1 : 0) |
                VTSS_F_VOP_MRP_ITST_CFG_ITST_LOC_PERIOD(process ? mrp->itst_loc_idx + 1 : 0),
                VTSS_M_VOP_MRP_ITST_CFG_ITST_CLR_MISS_CNT_ENA |
                VTSS_M_VOP_MRP_ITST_CFG_ITST_LOC_PERIOD);

        REG_WRM(VTSS_VOP_MRP_ITST_STAT(voe_idx),
                VTSS_F_VOP_MRP_ITST_STAT_ITST_MAX_MISS_CNT(cnt) |
                VTSS_F_VOP_MRP_ITST_STAT_ITST_MISS_CNT(0),
                VTSS_M_VOP_MRP_ITST_STAT_ITST_MAX_MISS_CNT      |
                VTSS_M_VOP_MRP_ITST_STAT_ITST_MISS_CNT);

        // Clear LoC sticky bit
        REG_WR(VTSS_VOP_MRP_MRP_STICKY(voe_idx), VTSS_M_VOP_MRP_MRP_STICKY_ITST_LOC_STICKY);
   }

    if (mrp->itst_loc_idx != LOC_PERIOD_CNT) {
        VTSS_RC(loc_period_configure(vtss_state, mrp->itst_loc_idx, mrp->tst_loc_conf.itst_interval));
    }

    return VTSS_RC_OK;
}

static vtss_rc mrp_process_ring_test(vtss_state_t *vtss_state, vtss_mrp_data_t *mrp)
{
    vtss_voe_idx_t  p_voe_idx = mrp->p_voe_idx;
    vtss_voe_idx_t  s_voe_idx = mrp->s_voe_idx;
    BOOL sample_hi_prio_ena, chk_best_mrm_ena, chk_rem_prio_ena;
    u32  lo_prio_fwd_sel, hi_prio_fwd_sel, rem_fwd_sel, own_fwd_sel;
    int  p;

    // What do we do with MRP_Test PDUs received from another MRM?
    if (mrp->conf.mra) {
        if (mrp->conf.ring_role == VTSS_MRP_RING_ROLE_CLIENT) {
            // MRC configured as MRA.
            // We let hardware check against best MAC and prio and by default,
            // we let the MRP_Test PDUs through.
            chk_best_mrm_ena = TRUE;
            chk_rem_prio_ena = TRUE;
            rem_fwd_sel      = FWD_NOP;

            // There are two cases to cover if the remote MRM has higher
            // priority than us:
            //   The remote MRM is the same as the current best MRM. This is the
            //   normal case, which keeps the LoC miss counter cleared. The CPU
            //   doesn't need these frames.
            //   The remote MRM is not the same as the current best MRM. If the
            //   current best MRM is still running, it will cease being MRM if
            //   the new remote MRM has higher priority than itself, which
            //   eventually will cause the LoC interrupt for us to occur. If
            //   the current best MRM has higher priority than the new MRM, the
            //   current best MRM will send MRP_TestMgrNAck PDUs to the new
            //   remote MRM, which will stop sending MRP_Test PDUs.
            // In either way, we don't need the PDUs to the CPU.
            hi_prio_fwd_sel = FWD_NOP;

            // There are two cases to cover if the remote MRM has lower priority
            // than us:
            //   The remote MRM is the same as the current best MRM, but it has
            //   changed priority to something lower than us. The H/W will not
            //   clear the miss count, and after some time, a LoC interrupt will
            //   occur, which will change us to MRM. So no need to to get it to
            //   the CPU.
            //   The remote MRM is not the same as the current best MRM. If the
            //   current best MRM is still running, it will take care of sending
            //   MRP_TestMgrNAck to the other MRM, and we shouldn't care. If the
            //   current best MRM is no longer running, we will eventually get a
            //   LoC interrupt, which will change us to MRM. So no need to get
            //   it to the CPU in this case either.
            lo_prio_fwd_sel = FWD_NOP;
        } else {
            // MRM configured as MRA.
            // We do not check against best MRM, because we think we are the
            // best. If we are not, we will get a MRP_TestMgrNAck and act
            // accordingly. When not checking against best MRM, hi_prio_fwd_sel
            // is not used for anything.
            chk_best_mrm_ena = FALSE;
            hi_prio_fwd_sel  = FWD_NOP;

            // Forwarding and CPU copying of other MRMs' MRP_Test PDUs works as
            // follows:
            // If the remote MRM has lower priority than us, we need its
            // MRP_Test PDUs to go to the CPU, so that we can send it an
            // MRP_TestMgrNAck PDU to stop it.
            chk_rem_prio_ena = TRUE;
            lo_prio_fwd_sel  = FWD_COPY_CPU;

            // If the remote MRM has higher priority than us, we don't need to
            // get the frames to the CPU, but will lean back and wait until the
            // remote MRM sends us an MRP_TestMgrNAck PDU.
            // If, however, the remote MRM is a true MRM and not an MRA in MRM
            // mode, it will never send that MRP_TestMgrNAck PDU back to us, and
            // we will have multiple MRMs on the ring.
            // If the application wants to check this condition and raise a
            // flag, we must copy these PDUs to the CPU.
            rem_fwd_sel = mrp->tst_copy_conf.tst_to_cpu ? FWD_COPY_CPU : FWD_NOP;
        }
    } else {
        if (mrp->conf.ring_role == VTSS_MRP_RING_ROLE_CLIENT) {
            // MRC configured as MRC.
            // We don't check for best MRM and we don't check for priority in
            // hardware, so lo_prio_fwd_sel and hi_prio_fwd_sel are not used.
            chk_best_mrm_ena = FALSE;
            chk_rem_prio_ena = FALSE;
            lo_prio_fwd_sel  = FWD_NOP;
            hi_prio_fwd_sel  = FWD_NOP;

            // We simply forward MRP_Test PDUs between ring ports if they are
            // forwarding (as set by mrp_control_forwarding()), and we don't
            // need these PDUs at the CPU.
            rem_fwd_sel = FWD_NOP;
        } else {
            // MRM configured as MRM.
            // We don't check for best MRM and we don't check for priority in
            // hardware, so lo_prio_fwd_sel and hi_prio_fwd_sel are not used.
            chk_best_mrm_ena = FALSE;
            chk_rem_prio_ena = FALSE;
            lo_prio_fwd_sel  = FWD_NOP;
            hi_prio_fwd_sel  = FWD_NOP;

            // If we are configured to send remote MRP_Test PDUs to the CPU in
            // order to let the application raise a "Multiple MRMs detected"
            // flag, we must do so.
            rem_fwd_sel = mrp->tst_copy_conf.tst_to_cpu ? FWD_COPY_CPU : FWD_NOP;
        }
    }

    // For the sake of debugging, we enable sampling of the best MRM's priority
    // (VTSS_VOP_MRP_TST_CFG_SAMPLE_HI_PRIO_ENA) into MEP_TST_PRIO_CFG_TEST_PRIO whenever
    // we check against the current best MRM.
    // This is safe, because it only overwrites it if it's coming from the MRM
    // currently marked as the best MAC and its priority is higher than our own.
    // Its value is not used by the chip itself for anything.
    sample_hi_prio_ena = chk_best_mrm_ena;

    // We always - whether or not we are an MRM - discard MRP_Test PDUs from
    // ourselves.
    own_fwd_sel = FWD_DISCARD;

    VTSS_I("ring_role = %s, mra = %d, p_fwd = %s, s_fwd = %s, i_fwd = %s", ring_role2txt(mrp->conf.ring_role), mrp->conf.mra, port_state2txt(mrp->p_port_state), port_state2txt(mrp->s_port_state), port_state2txt(mrp->i_port_state));
    VTSS_I("sample_hi_prio_ena = %d, chk_rem_prio_ena = %d, chk_best_mrm_ena = %d", sample_hi_prio_ena, chk_rem_prio_ena, chk_best_mrm_ena);
    VTSS_I("hi_prio_fwd_sel = %s, lo_prio_fwd_sel = %s, rem_fwd_sel = %s, own_fwd_sel = %s", sel2txt(hi_prio_fwd_sel), sel2txt(lo_prio_fwd_sel), sel2txt(rem_fwd_sel), sel2txt(own_fwd_sel));

    for (p = 0; p < 2; p++) {
        REG_WRM(VTSS_VOP_MRP_TST_CFG(p == 0 ? p_voe_idx : s_voe_idx),
                VTSS_F_VOP_MRP_TST_CFG_SAMPLE_HI_PRIO_ENA(sample_hi_prio_ena) |
                VTSS_F_VOP_MRP_TST_CFG_CHK_REM_PRIO_ENA(chk_rem_prio_ena)     |
                VTSS_F_VOP_MRP_TST_CFG_CHK_BEST_MRM_ENA(chk_best_mrm_ena),
                VTSS_M_VOP_MRP_TST_CFG_SAMPLE_HI_PRIO_ENA |
                VTSS_M_VOP_MRP_TST_CFG_CHK_BEST_MRM_ENA   |
                VTSS_M_VOP_MRP_TST_CFG_CHK_REM_PRIO_ENA);

        REG_WRM(VTSS_VOP_MRP_TST_FWD_CTRL(p == 0 ? p_voe_idx : s_voe_idx),
                VTSS_F_VOP_MRP_TST_FWD_CTRL_HI_PRIO_FWD_SEL(hi_prio_fwd_sel) |
                VTSS_F_VOP_MRP_TST_FWD_CTRL_LO_PRIO_FWD_SEL(lo_prio_fwd_sel) |
                VTSS_F_VOP_MRP_TST_FWD_CTRL_REM_FWD_SEL(rem_fwd_sel)         |
                VTSS_F_VOP_MRP_TST_FWD_CTRL_OWN_FWD_SEL(own_fwd_sel),
                VTSS_M_VOP_MRP_TST_FWD_CTRL_HI_PRIO_FWD_SEL |
                VTSS_M_VOP_MRP_TST_FWD_CTRL_LO_PRIO_FWD_SEL |
                VTSS_M_VOP_MRP_TST_FWD_CTRL_REM_FWD_SEL     |
                VTSS_M_VOP_MRP_TST_FWD_CTRL_OWN_FWD_SEL);
    }

    // Configure processing and LoC of MPR_InTest PDUs
    if (mrp_loc_configure(vtss_state, mrp) != VTSS_RC_OK) {
        VTSS_E("mrp_loc_configure failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc mrp_process_in_test(vtss_state_t *vtss_state, vtss_mrp_data_t *mrp)
{
    if (mrp_control_forwarding(vtss_state, mrp) != VTSS_RC_OK) {
        VTSS_E("mrp_control_forwarding failed");
        return VTSS_RC_ERROR;
    }

    // Configure processing and LoC of MPR_InTest PDUs
    if (mrp_in_loc_configure(vtss_state, mrp) != VTSS_RC_OK) {
        VTSS_E("mrp_in_loc_configure failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

u32 find_unused_loc_idx(vtss_mrp_data_t *mrp_array)
{
    u32  i;
    BOOL idx_used[LOC_PERIOD_CNT];
    memset(idx_used, 0, sizeof(idx_used));

    for (i = 0; i < VTSS_MRP_CNT; ++i) {
        if (!mrp_array[i].active) {
            continue;
        }
        if (mrp_array[i].tst_loc_idx != LOC_PERIOD_CNT) {
            idx_used[mrp_array[i].tst_loc_idx] = TRUE;
        }
        if (mrp_array[i].itst_loc_idx != LOC_PERIOD_CNT) {
            idx_used[mrp_array[i].itst_loc_idx] = TRUE;
        }
    }

    for (i = 7; i < LOC_PERIOD_CNT; ++i) { /* Note that VOP is using the first 7 timers */
        if (!idx_used[i]) {
            break;
        }
    }

    if (i >= LOC_PERIOD_CNT) { /* Unused LOC timer NOT found */
        return LOC_PERIOD_CNT;
    }

    return i;
}

static vtss_rc lan969x_mrp_del(vtss_state_t           *vtss_state,
                               const vtss_mrp_idx_t   mrp_idx)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_voe_idx_t  voe_idx;
    int             p;

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    for (p = 0; p < 3; p++) {
        if (p == 2 && mrp_data->conf.in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
            continue;
        }
        voe_idx = p == 0 ? mrp_data->p_voe_idx : p == 1 ? mrp_data->s_voe_idx : mrp_data->i_voe_idx;

        if (mrp_uninit_port(vtss_state, voe_idx) != VTSS_RC_OK) {
            VTSS_E("mrp_uninit_port(%d) failed", p);
        }

        if (vtss_fa_voe_free(vtss_state, VTSS_VOE_FUNCTION_MRP, voe_idx) != VTSS_RC_OK) {
            VTSS_E("vtss_fa_voe_free(%d) failed", voe_idx);
        }
    }

    // Set instance to default
    mrp_instance_default(vtss_state, mrp_data);

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_add(vtss_state_t          *vtss_state,
                               const vtss_mrp_idx_t  mrp_idx,
                               const vtss_mrp_conf_t *const conf)
{
    u32             i, p;
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_mrp_data_t *mrp_array = vtss_state->mrp.data;
    vtss_voe_idx_t  *voe_idx;
    vtss_rc         rc;

    VTSS_D("mra = %d, ring_role = %s, in_ring_role = %s, in_rc_mode = %d", conf->mra, ring_role2txt(conf->ring_role), ring_role2txt(conf->in_ring_role), conf->in_rc_mode);

    if (mrp_data->active) {
        VTSS_E("MRP instance already active");
        return VTSS_RC_ERROR;
    }

    if ((conf->p_port >= VTSS_PORTS) || (conf->s_port >= VTSS_PORTS)) {
        VTSS_E("Invalid Primary or Secondary port");
        return VTSS_RC_ERROR;
    }

    if (conf->ring_role != VTSS_MRP_RING_ROLE_MANAGER && conf->ring_role != VTSS_MRP_RING_ROLE_CLIENT) {
        VTSS_E("Ring role must be MRM or MRC, not %d", conf->ring_role);
        return VTSS_RC_ERROR;
    }

    if ((conf->in_ring_role != VTSS_MRP_RING_ROLE_DISABLED) && (conf->i_port >= VTSS_PORTS)) {
        VTSS_E("Invalid I/C port");
        return VTSS_RC_ERROR;
    }

    if ((conf->p_port == conf->s_port) || (conf->p_port == conf->i_port) || (conf->s_port == conf->i_port)) {
        VTSS_E("Illegal port combination");
        return VTSS_RC_ERROR;
    }

    for (i = 0; i < VTSS_MRP_CNT; ++i) {
        if (!mrp_array[i].active) {
            continue;
        }
        if ((conf->p_port == mrp_array[i].conf.p_port) || (conf->p_port == mrp_array[i].conf.s_port) || (conf->p_port == mrp_array[i].conf.i_port)) {
            VTSS_E("Primary port already in use");
            return VTSS_RC_ERROR;
        }
        if ((conf->s_port == mrp_array[i].conf.p_port) || (conf->s_port == mrp_array[i].conf.s_port) || (conf->s_port == mrp_array[i].conf.i_port)) {
            VTSS_E("Secondary port already in use");
            return VTSS_RC_ERROR;
        }
        if ((conf->in_ring_role != VTSS_MRP_RING_ROLE_DISABLED) &&
            ((conf->i_port == mrp_array[i].conf.p_port) || (conf->i_port == mrp_array[i].conf.s_port) || (conf->i_port == mrp_array[i].conf.i_port))) {
            VTSS_E("Interconnected port already in use");
            return VTSS_RC_ERROR;
        }
    }

    /* Allocate MRP Service VOE instances */
    for (p = 0; p < 3; p++) {
        if (p == 2 && conf->in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
            continue;
        }

        voe_idx = p == 0 ? &mrp_data->p_voe_idx : p == 1 ? &mrp_data->s_voe_idx : &mrp_data->i_voe_idx;
        *voe_idx = vtss_fa_service_voe_alloc(vtss_state, VTSS_VOE_FUNCTION_MRP);

        if (*voe_idx >= VTSS_PATH_SERVICE_VOE_CNT) {
            VTSS_E("No free Service VOE was allocate");
            rc = VTSS_RC_ERROR;
            goto do_exit;
        }
    }

    /* Initialize port to enable MRP */
    for (p = 0; p < 3; p++) {
        if (p == 2 && conf->in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
            continue;
        }

        voe_idx = p == 0 ? &mrp_data->p_voe_idx : p == 1 ? &mrp_data->s_voe_idx : &mrp_data->i_voe_idx;

        // MRP_PortRole encoding is exactly following "p":
        // p == 0 => Primary ring port
        // p == 1 => Secondary ring port
        // p == 2 => I/C port.
        if (mrp_init_port(vtss_state, *voe_idx, p) != VTSS_RC_OK) {
            VTSS_E("mrp_init_port(%u) failed", p);
            return VTSS_RC_ERROR;
        }

        /* Configure port with requested MAC address */
        if (mrp_port_update_mac(vtss_state, *voe_idx, conf->mac.addr) != VTSS_RC_OK) {
            VTSS_E("mrp_port_update_mac(%d) failed", p);
            return VTSS_RC_ERROR;
        }
    }

    // We must set it active here, because otherwise the find_unused_loc_idx()
    // will fail.
    mrp_data->active = TRUE;
    mrp_data->conf = *conf;
    rc = VTSS_RC_OK;

    if (conf->mra || conf->ring_role == VTSS_MRP_RING_ROLE_MANAGER) {
        /* Allocate a TST LOC timer index. */
        if ((mrp_data->tst_loc_idx = find_unused_loc_idx(mrp_array)) == LOC_PERIOD_CNT) {
            VTSS_E("No unused LOC timer found");
            rc = VTSS_RC_ERROR;
            goto do_exit;
        }
    }

    // Allocate an INTST LOC timer index if MIM-RC (not MIM-LC, because we don't
    // expect MRP_InTest PDUs in that case).
    if (conf->in_ring_role == VTSS_MRP_RING_ROLE_MANAGER && conf->in_rc_mode) {
        if ((mrp_data->itst_loc_idx = find_unused_loc_idx(mrp_array)) == LOC_PERIOD_CNT) {
            VTSS_E("No unused LOC timer found");
            rc = VTSS_RC_ERROR;
            goto do_exit;
        }
    }

    // Make sure that the remaining code in this module works if the user came
    // with a valid i_port, but has disabled I/C role (I/C role cannot be
    // changed dynamically).
    if (mrp_data->conf.in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
        mrp_data->conf.i_port = VTSS_PORT_NO_NONE;
    }

    /* Configure MRP frame forwarding */
    if (mrp_control_forwarding(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_control_forwarding failed");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    /* Configure rewrite of Test frames */
    if (mrp_rewrite_ring_test(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_rewrite_ring_test failed");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    /* Configure rewrite of Interconnected Test frames */
    if (mrp_rewrite_in_test(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_rewrite_in_ring_test failed");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    /* Configure processing of ring Test frames and enable LoC if needed */
    if (mrp_process_ring_test(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_process_ring_test failed");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    // Configure processing of interconnected ring Test frames and enable LoC
    // if needed.
    if (mrp_process_in_test(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_process_in_test failed");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

do_exit:
    if (rc != VTSS_RC_OK) {
       // Undo what we just did.
       lan969x_mrp_del(vtss_state, mrp_idx);
    }

    return rc;
}

static vtss_rc lan969x_mrp_ring_role_set(vtss_state_t               *vtss_state,
                                         const vtss_mrp_idx_t       mrp_idx,
                                         const vtss_mrp_ring_role_t role)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    if (!mrp_data->conf.mra) {
        VTSS_E("Change of ring role requires instance is configured as MRA");
        return VTSS_RC_ERROR;
    }

    if (mrp_data->conf.ring_role == role) {
        VTSS_D("MRP ring role is unchanged");
        return VTSS_RC_OK;
    }

    if (role != VTSS_MRP_RING_ROLE_MANAGER && role != VTSS_MRP_RING_ROLE_CLIENT) {
        VTSS_E("Ring role must be MRM or MRC, not %d", role);
        return VTSS_RC_ERROR;
    }

    if (mrp_data->tst_loc_idx == LOC_PERIOD_CNT) {
        VTSS_E("Internal error: We're active and configured as MRA, but no TST LOC timer index is allocated");
        return VTSS_RC_ERROR;
    }

    // Update conf now, because the following functions use it.
    mrp_data->conf.ring_role = role;

    /* Update MRP frame forwarding */
    if (mrp_control_forwarding(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_control__forwarding failed");
        return VTSS_RC_ERROR;
    }

    /* Configure rewrite of Test frames */
    if (mrp_rewrite_ring_test(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_rewrite_ring_test failed");
        return VTSS_RC_ERROR;
    }

    /* Configure processing of Test frames */
    if (mrp_process_ring_test(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_process_ring_test failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_primary_port_set(vtss_state_t         *vtss_state,
                                            const vtss_mrp_idx_t mrp_idx,
                                            const vtss_port_no_t port_no)
{
    vtss_mrp_data_t       *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_mrp_port_state_t save_port_state;
    vtss_port_no_t        save_port;
    vtss_voe_idx_t        p_voe_idx, s_voe_idx, save_voe_idx;
    int                   i, p;

    VTSS_D("Enter, p_port %u", port_no);

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    if (port_no >= VTSS_PORTS) {
        VTSS_E("Invalid port number (%u)", port_no);
        return VTSS_RC_ERROR;
    }

    if (port_no == mrp_data->conf.p_port) {
        VTSS_D("No change in primary port");
        return VTSS_RC_OK;
    }

    if (port_no != mrp_data->conf.s_port) {
        VTSS_E("New primary port (%u) not equal to current secondary port (%u)", port_no, mrp_data->conf.s_port);
        return VTSS_RC_ERROR;
    }

    // Swap port state
    save_port_state        = mrp_data->p_port_state;
    mrp_data->p_port_state = mrp_data->s_port_state;
    mrp_data->s_port_state = save_port_state;

    // Swap ports
    save_port             = mrp_data->conf.p_port;
    mrp_data->conf.p_port = port_no;
    mrp_data->conf.s_port = save_port;

    // Swap VOE indexes
    save_voe_idx          = mrp_data->p_voe_idx;
    mrp_data->p_voe_idx   = mrp_data->s_voe_idx;
    mrp_data->s_voe_idx   = save_voe_idx;

    p_voe_idx = mrp_data->p_voe_idx;
    s_voe_idx = mrp_data->s_voe_idx;

    // Update the port role in HW for MRP_Test and MRP_InTest frames. These
    // values will be applied to the frame only if the bit
    // REW_MRP_TX_CFG_MRP_MISC_UPD is set.
    for (p = 0; p < 2; p++) {
       // p counts ring port and is identical to new port role
       for (i = 0; i < 2; i++) {
           // i == 0 => MRP_Test port role, i == 1 => MRP_InTest port role
           REG_WRM(VTSS_VOP_MRP_MRP_TX_CFG(p == 0 ? p_voe_idx : s_voe_idx, i == 0 ? CONFIG_TEST : CONFIG_INTEST),
                   VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_PORTROLE(p),
                   VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_PORTROLE);
       }
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_ring_state_set(vtss_state_t                *vtss_state,
                                          const vtss_mrp_idx_t        mrp_idx,
                                          const vtss_mrp_ring_state_t state)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_voe_idx_t  p_voe_idx;
    vtss_voe_idx_t  s_voe_idx;
    int             p;

    VTSS_D("Enter, state = %d", state);

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    p_voe_idx = mrp_data->p_voe_idx;
    s_voe_idx = mrp_data->s_voe_idx;

    if (mrp_data->ring_state != state) {
        mrp_data->ring_transitions++;
    }

    mrp_data->ring_state = state;

    // Set ring state to be updated into transmitted MRP_Test PDUs
    for (p = 0; p < 2; p++) {
        REG_WRM(VTSS_VOP_MRP_MRP_TX_CFG(p == 0 ? p_voe_idx : s_voe_idx, CONFIG_TEST),
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_STATE(ring_state_calc(state)) |
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_TRANS(mrp_data->ring_transitions),
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_STATE |
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_TRANS);
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_in_ring_state_set(vtss_state_t                *vtss_state,
                                             const vtss_mrp_idx_t        mrp_idx,
                                             const vtss_mrp_ring_state_t state)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_voe_idx_t  p_voe_idx = mrp_data->p_voe_idx;
    vtss_voe_idx_t  s_voe_idx = mrp_data->s_voe_idx;
    vtss_voe_idx_t  i_voe_idx;
    int             p;

    VTSS_D("Enter, state = %d", state);

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    if (mrp_data->conf.in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
        VTSS_E("MRP instance has no interconnect role");
        return VTSS_RC_ERROR;
    }

    // Now, we know that i_port is valid, because in_ring_role is not disabled.
    i_voe_idx = mrp_data->i_voe_idx;

    if (mrp_data->in_ring_state != state) {
        mrp_data->in_ring_transitions++;
    }

    mrp_data->in_ring_state = state;

    // Set I/C ring state to be updated into transmitted MRP_InTest PDUs
    for (p = 0; p < 3; p++) {
        REG_WRM(VTSS_VOP_MRP_MRP_TX_CFG(p == 0 ? p_voe_idx : p == 1 ? s_voe_idx : i_voe_idx, CONFIG_INTEST),
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_STATE(ring_state_calc(state)) |
                VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_TRANS(mrp_data->in_ring_transitions),
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_STATE |
                VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_TRANS);
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_port_state_set(vtss_state_t                 *vtss_state,
                                          const vtss_mrp_idx_t         mrp_idx,
                                          const vtss_port_no_t         port,
                                          const vtss_mrp_port_state_t  state)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    if (mrp_data->conf.p_port == port && mrp_data->p_port_state == state) {
        VTSS_D("MRP Primary Port role is unchanged");
        return VTSS_RC_OK;
    }

    if (mrp_data->conf.s_port == port && mrp_data->s_port_state == state) {
        VTSS_D("MRP Secondary Port role is unchanged");
        return VTSS_RC_OK;
    }

    if (mrp_data->conf.i_port == port && mrp_data->i_port_state == state) {
        VTSS_D("MRP Interconnect Port role is unchanged");
        return VTSS_RC_OK;
    }

    if (port != mrp_data->conf.p_port && port != mrp_data->conf.s_port && port != mrp_data->conf.i_port) {
        VTSS_E("Invalid port number");
        return VTSS_RC_ERROR;
    }

    if (mrp_data->conf.p_port == port) {
        mrp_data->p_port_state = state;
    }

    if (mrp_data->conf.s_port == port) {
        mrp_data->s_port_state = state;
    }

    if (mrp_data->conf.i_port == port) {
        mrp_data->i_port_state = state;
    }

    /* Configure MRP frame forwarding */
    if (mrp_control_forwarding(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_control_forwarding failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_best_mrm_set(vtss_state_t              *vtss_state,
                                        const vtss_mrp_idx_t      mrp_idx,
                                        const vtss_mrp_best_mrm_t *best)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_voe_idx_t  voe_idx;
    int             p;

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    if (!mrp_data->conf.mra) {
        VTSS_E("MRP instance is not an MRA");
        return VTSS_RC_ERROR;
    }

    // Configure best MAC address and priority into the two ports
    for (p = 0; p < 2; p++) {
        voe_idx = p == 0 ? mrp_data->p_voe_idx : p == 1 ? mrp_data->s_voe_idx : mrp_data->i_voe_idx;
        if (mrp_port_update_best_mrm(vtss_state, voe_idx, best) != VTSS_RC_OK) {
            VTSS_E("mrp_port_update_best_mrm(%u) failed", voe_idx);
            return VTSS_RC_ERROR;
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_tst_loc_conf_set(vtss_state_t                  *vtss_state,
                                            const vtss_mrp_idx_t          mrp_idx,
                                            const vtss_mrp_tst_loc_conf_t *const tst_loc_conf)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    mrp_data->tst_loc_conf = *tst_loc_conf;

    // Configure MRP_Test LoC
    if (mrp_loc_configure(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_loc_configure failed");
        return VTSS_RC_ERROR;
    }

    // Configure MRP_InTest LoC
    if (mrp_in_loc_configure(vtss_state, mrp_data) != VTSS_RC_OK) {
        VTSS_E("mrp_in_loc_configure failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_tst_hitme_once(vtss_state_t         *vtss_state,
                                          const vtss_mrp_idx_t mrp_idx)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    int             p;

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    // Only set this on ring ports, not I/C port.
    for (p = 0; p < 2; p++) {
        REG_WRM(VTSS_VOP_MRP_NXT_LOC_HMO(p == 0 ? mrp_data->p_voe_idx : mrp_data->s_voe_idx),
                VTSS_F_VOP_MRP_NXT_LOC_HMO_NXT_LOC_CPU_HITME_ONCE(1),
                VTSS_M_VOP_MRP_NXT_LOC_HMO_NXT_LOC_CPU_HITME_ONCE);
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_itst_hitme_once(vtss_state_t         *vtss_state,
                                           const vtss_mrp_idx_t mrp_idx)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    int             p;

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    if (mrp_data->conf.in_ring_role != VTSS_MRP_RING_ROLE_MANAGER) {
        VTSS_E("I/C not active or not a MIM");
        return VTSS_RC_ERROR;
    }

    // This only works for MIM-RC.
    for (p = 0; p < 3; p++) {
        REG_WRM(VTSS_VOP_MRP_ITST_NXT_LOC_HMO(p == 0 ? mrp_data->p_voe_idx : p == 1 ? mrp_data->s_voe_idx : mrp_data->i_voe_idx),
                VTSS_F_VOP_MRP_ITST_NXT_LOC_HMO_ITST_NXT_LOC_CPU_HITME_ONCE(1),
                VTSS_M_VOP_MRP_ITST_NXT_LOC_HMO_ITST_NXT_LOC_CPU_HITME_ONCE);
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_tst_copy_conf_set(vtss_state_t                   *vtss_state,
                                             const vtss_mrp_idx_t           mrp_idx,
                                             const vtss_mrp_tst_copy_conf_t *const copy)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_voe_idx_t  p_voe_idx = mrp_data->p_voe_idx;
    vtss_voe_idx_t  s_voe_idx = mrp_data->s_voe_idx;
    vtss_voe_idx_t  i_voe_idx;
    u32             value, voe_idx;
    u32             rem_fwd_sel;
    BOOL            fwd;
    int             p;

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    // If currently MRM, set the copy conf now. Otherwise wait until the ring
    // role changes to MRM (see mrp_process_ring_test()).
    if (mrp_data->conf.ring_role == VTSS_MRP_RING_ROLE_MANAGER) {
        for (p = 0; p < 2; p++) {
            voe_idx = p == 0 ? p_voe_idx : s_voe_idx;

            // Modify the current copying to CPU.
            REG_RD(VTSS_VOP_MRP_TST_FWD_CTRL(voe_idx), &value);

            rem_fwd_sel = VTSS_X_VOP_MRP_TST_FWD_CTRL_REM_FWD_SEL(value);

            // Get whether currently forwarding between ring ports.
            fwd = rem_fwd_sel == FWD_NOP || rem_fwd_sel == FWD_COPY_CPU;

            // Compute new forward select
            rem_fwd_sel = mrp_fwd_sel(fwd, copy->tst_to_cpu);

            REG_WRM(VTSS_VOP_MRP_TST_FWD_CTRL(voe_idx),
                    VTSS_F_VOP_MRP_TST_FWD_CTRL_REM_FWD_SEL(rem_fwd_sel),
                    VTSS_M_VOP_MRP_TST_FWD_CTRL_REM_FWD_SEL);
        }
    }

    // If currently a MIM, set the MRP_InTest copy conf now. Otherwise wait
    // until we get a new interconnect role (see mrp_process_in_test() and
    // mrp_control_forwarding()).
    if (mrp_data->conf.i_port < VTSS_PORTS && mrp_data->conf.in_ring_role == VTSS_MRP_RING_ROLE_MANAGER) {
        i_voe_idx = mrp_data->i_voe_idx;

        for (p = 0; p < 3; p++) {
            voe_idx = p == 0 ? p_voe_idx : p == 1 ? s_voe_idx : i_voe_idx;
            // Modify the current copying to CPU.
            REG_RD(VTSS_VOP_MRP_ITST_FWD_CTRL(voe_idx), &value);

            rem_fwd_sel = VTSS_X_VOP_MRP_ITST_FWD_CTRL_ITST_REM_FWD_SEL(value);

            // Get whether this port is currently forwarding remote MRP_InTest
            // PDUs.
            fwd = rem_fwd_sel == FWD_NOP || rem_fwd_sel == FWD_COPY_CPU;

            // Compute new forward select
            rem_fwd_sel = mrp_fwd_sel(fwd, copy->itst_to_cpu);

            REG_WRM(VTSS_VOP_MRP_ITST_FWD_CTRL(voe_idx),
                    VTSS_F_VOP_MRP_ITST_FWD_CTRL_ITST_REM_FWD_SEL(rem_fwd_sel),
                    VTSS_M_VOP_MRP_ITST_FWD_CTRL_ITST_REM_FWD_SEL);
        }
    }

    mrp_data->tst_copy_conf = *copy;

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_status_get(vtss_state_t         *vtss_state,
                                      const vtss_mrp_idx_t mrp_idx,
                                      vtss_mrp_status_t    *const status)
{
    vtss_mrp_data_t        *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_mrp_port_status_t *port_status;
    vtss_voe_idx_t         p_voe_idx = mrp_data->p_voe_idx;
    vtss_voe_idx_t         s_voe_idx = mrp_data->s_voe_idx;
    vtss_voe_idx_t         i_voe_idx = 0;
    vtss_voe_idx_t         voe_idx;
    u32                    value, value1;
    int                    p;

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    if (mrp_data->conf.i_port < VTSS_PORTS) {
        i_voe_idx = mrp_data->i_voe_idx;
    }

    memset(status, 0, sizeof(*status));

    for (p = 0; p < 3; p++) {
        if (p == 2 && mrp_data->conf.in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
            continue;
        }

        voe_idx   = p == 0 ? p_voe_idx       : p == 1 ? s_voe_idx       : i_voe_idx;
        port_status = p == 0 ? &status->p_status : p == 1 ? &status->s_status : &status->i_status;

        // Get port LOC status
        REG_RD(VTSS_VOP_MRP_TST_CFG(voe_idx), &value);
        REG_RD(VTSS_VOP_MRP_TST_STAT(voe_idx), &value1);
        port_status->tst_loc = VTSS_X_VOP_MRP_TST_CFG_LOC_PERIOD(value) != 0 && VTSS_X_VOP_MRP_TST_STAT_MISS_CNT(value1) == VTSS_X_VOP_MRP_TST_STAT_MAX_MISS_CNT(value1);
        REG_RD(VTSS_VOP_MRP_ITST_CFG(p_voe_idx), &value);
        REG_RD(VTSS_VOP_MRP_ITST_STAT(p_voe_idx), &value1);
        port_status->itst_loc = VTSS_X_VOP_MRP_ITST_CFG_ITST_LOC_PERIOD(value) != 0 && VTSS_X_VOP_MRP_ITST_STAT_ITST_MISS_CNT(value1) == VTSS_X_VOP_MRP_ITST_STAT_ITST_MAX_MISS_CNT(value1);

        // Get port seen status
        // We cannot get seq_err_seen, because we never enable sequence error
        // detection.
        REG_RD(VTSS_VOP_MRP_MRP_STICKY(voe_idx), &value);
        port_status->mrp_seen      = VTSS_X_VOP_MRP_MRP_STICKY_MRP_RX_STICKY(value)      ? TRUE : FALSE;
        port_status->mrp_proc_seen = VTSS_X_VOP_MRP_MRP_STICKY_MRP_RX_PROC_STICKY(value) ? TRUE : FALSE;
        port_status->dmac_err_seen = VTSS_X_VOP_MRP_MRP_STICKY_DMAC_ERR_STICKY(value)    ? TRUE : FALSE;
        port_status->vers_err_seen = VTSS_X_VOP_MRP_MRP_STICKY_VERSION_ERR_STICKY(value) ? TRUE : FALSE;

        /* Clear the sticky bits that has been detected */
        value = value &
                (VTSS_M_VOP_MRP_MRP_STICKY_MRP_RX_STICKY   | VTSS_M_VOP_MRP_MRP_STICKY_MRP_RX_PROC_STICKY |
                 VTSS_M_VOP_MRP_MRP_STICKY_DMAC_ERR_STICKY | VTSS_M_VOP_MRP_MRP_STICKY_VERSION_ERR_STICKY);
        REG_WR(VTSS_VOP_MRP_MRP_STICKY(voe_idx), value);
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_counters_get(vtss_state_t          *vtss_state,
                                        const vtss_mrp_idx_t  mrp_idx,
                                        vtss_mrp_counters_t   *const counters)
{
    vtss_mrp_data_t  *mrp_data = &vtss_state->mrp.data[mrp_idx];

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    memset(counters, 0, sizeof(*counters));

    /* Poll so we get the most recent counter values */
    if (mrp_counter_update(vtss_state, mrp_idx, FALSE) != VTSS_RC_OK) {
        VTSS_D("mrp_counter_update failed");
        return VTSS_RC_ERROR;
    }

    /* Get the counters */
    counters->p_counters.tst_rx_count = mrp_data->p_counters.tst_rx_count.value;
    counters->p_counters.itst_rx_count = mrp_data->p_counters.itst_rx_count.value;
    counters->s_counters.tst_rx_count = mrp_data->s_counters.tst_rx_count.value;
    counters->s_counters.itst_rx_count = mrp_data->s_counters.itst_rx_count.value;
    counters->i_counters.tst_rx_count = mrp_data->i_counters.tst_rx_count.value;
    counters->i_counters.itst_rx_count = mrp_data->i_counters.itst_rx_count.value;

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_counters_clear(vtss_state_t          *vtss_state,
                                          const vtss_mrp_idx_t  mrp_idx)
{
    vtss_mrp_data_t  *mrp_data = &vtss_state->mrp.data[mrp_idx];

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    /* Clear counter values */
    if (mrp_counter_update(vtss_state, mrp_idx, TRUE) != VTSS_RC_OK) {
        VTSS_D("mrp_counter_update failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_event_mask_set(vtss_state_t         *vtss_state,
                                          const vtss_mrp_idx_t mrp_idx,
                                          const u32            mask,
                                          const BOOL           enable)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_voe_idx_t  voe_idx;
    u32             enable_mask, reg_mask;
    int             p;

    VTSS_D("Enter, mrp_idx = %u, mask = %u, enable = %u", mrp_idx, mask, enable);

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    for (p = 0; p < 3; p++) {
        if (p == 2 && mrp_data->conf.in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
            continue;
        }

        voe_idx = p == 0 ? mrp_data->p_voe_idx : p == 1 ? mrp_data->s_voe_idx : mrp_data->i_voe_idx;

        // Read the port's interrupt enable mask
        REG_RD(VTSS_VOP_MRP_MRP_INTR_ENA(voe_idx), &enable_mask);

        // Translate the input mask to register mask
        reg_mask = ((mask & VTSS_MRP_EVENT_MASK_TST_LOC)  ? VTSS_F_VOP_MRP_MRP_INTR_ENA_TST_LOC_INTR_ENA(1)  : 0) |
                   ((mask & VTSS_MRP_EVENT_MASK_ITST_LOC) ? VTSS_F_VOP_MRP_MRP_INTR_ENA_ITST_LOC_INTR_ENA(1) : 0);

        // Calculate new enable mask
        enable_mask = enable ? (enable_mask | reg_mask) : (enable_mask & ~reg_mask);

        // Write back the port's interrupt enable mask
        REG_WR(VTSS_VOP_MRP_MRP_INTR_ENA(voe_idx), enable_mask);
    }

    return vtss_fa_oam_vop_int_update(vtss_state);
}

static vtss_rc lan969x_mrp_event_get(vtss_state_t         *vtss_state,
                                     const vtss_mrp_idx_t mrp_idx,
                                     vtss_mrp_event_t     *const events)
{
    vtss_mrp_data_t *mrp_data = &vtss_state->mrp.data[mrp_idx];
    vtss_voe_idx_t  voe_idx;
    u32             enable_mask, sticky_mask;
    u32             *mask;
    int             p;

    VTSS_D("Enter, mrp_idx = %u", mrp_idx);

    if (!mrp_data->active) {
        VTSS_E("MRP instance not active");
        return VTSS_RC_ERROR;
    }

    memset(events, 0, sizeof(*events));

    for (p = 0; p < 3; p++) {
        if (p == 2 && mrp_data->conf.in_ring_role == VTSS_MRP_RING_ROLE_DISABLED) {
            continue;
        }

        voe_idx = p == 0 ? mrp_data->p_voe_idx : p == 1 ? mrp_data->s_voe_idx : mrp_data->i_voe_idx;
        mask = p == 0 ? &events->p_mask : p == 1 ? &events->s_mask : &events->i_mask;

        // Read the port's interrupt enable mask
        REG_RD(VTSS_VOP_MRP_MRP_INTR_ENA(voe_idx), &enable_mask);

        // Read the port's sticky bits and clear the enabled ones
        REG_RD(VTSS_VOP_MRP_MRP_STICKY(voe_idx), &sticky_mask);
        sticky_mask &= enable_mask;

        // Sticky bits cleared by writing 1 to them
        REG_WR(VTSS_VOP_MRP_MRP_STICKY(voe_idx), sticky_mask);

        // Translate port's sticky mask to returned event mask
        *mask = (VTSS_X_VOP_MRP_MRP_STICKY_TST_LOC_STICKY( sticky_mask) != 0 ? VTSS_MRP_EVENT_MASK_TST_LOC  : 0) |
                (VTSS_X_VOP_MRP_MRP_STICKY_ITST_LOC_STICKY(sticky_mask) != 0 ? VTSS_MRP_EVENT_MASK_ITST_LOC : 0);
    }

    VTSS_D("Exit, p_mask 0x%x, s_mask = 0x%x, i_mask 0x%x", events->p_mask, events->s_mask, events->i_mask);
    return VTSS_RC_OK;
}

static vtss_rc lan969x_debug_mrp(vtss_state_t               *vtss_state,
                                 const vtss_debug_printf_t  pr,
                                 const vtss_debug_info_t    *const info)
{
    u32   i, v, div, mrp_idx;
    char  buf[80];
    BOOL  show, mrp, status, internal;
    vtss_mrp_data_t *mrp_data;

    div = 0;
    mrp_idx = 0;
    show = mrp = status = internal = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show = info->action == 0;

        if (info->action > 0) { /* This potentially a MRP config or MRP status action */
            for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
                mrp      = info->action / div == 1;
                status   = info->action / div == 2;
                internal = info->action / div == 3;
                if (mrp || status || internal) {
                    break;
                }
            }

            if (mrp || status || internal) {    /* Calculate the possible MRP index */
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
        pr("    3XXXX: Print MRP XXXX internals. Without XXXX all MRPs are printed\n");
        pr("\n");
    }

    if (!info->has_action || mrp) { /* MRP configuration must be printed */
        pr("MRP Config:\n\n");

        for (i = 0; i < VTSS_PATH_SERVICE_VOE_CNT; ++i) {
            if (mrp && (div > 1) && (mrp_idx != i)) {   /* A specific MRP must be printed - this is not the one */
                continue;
            }

            REG_RD(VTSS_VOP_MRP_MRP_CTRL(i), &v);
            if (info->full  ||  VTSS_X_VOP_MRP_MRP_CTRL_MRP_ENA(v)) {
                VTSS_SPRINTF(buf, "MRP %u", i);
                vtss_fa_debug_reg_header(pr, buf);
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_CTRL(i)), i, "MEP_MRP_CTRL");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_FWD_CTRL(i)), i, "MEP_MRP_FWD_CTRL");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_RING_MASK_CFG(i)), i, "MEP_RING_MASK_CFG");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_ICON_MASK_CFG(i)), i, "MEP_ICON_MASK_CFG");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TST_FWD_CTRL(i)), i, "MEP_TST_FWD_CTRL");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TST_CFG(i)), i, "MEP_TST_CFG");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TST_PRIO_CFG(i)), i, "MEP_TST_PRIO_CFG");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_ITST_FWD_CTRL(i)), i, "MEP_ITST_FWD_CTRL");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_ITST_CFG(i)), i, "MEP_ITST_CFG");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_MAC_LSB(i)), i, "MEP_MRP_MAC_LSB");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_MAC_MSB(i)), i, "MEP_MRP_MAC_MSB");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_BEST_MAC_LSB(i)), i, "BEST_MRP_MAC_LSB");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_BEST_MAC_MSB(i)), i, "BEST_MRP_MAC_MSB");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_INTR_ENA(i)), i, "MEP_MRP_INTR_ENA");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_TX_CFG(i, 0)), i, "MRP_MRP_TX_CFG[0]");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_TX_CFG(i, 1)), i, "MRP_MRP_TX_CFG[1]");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TST_STAT(i)), i, "MRP_TST_STAT");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_ITST_STAT(i)), i, "MRP_ITST_STAT");
                pr("\n");
            }
        }

        VTSS_SPRINTF(buf, "Relevant VOP configuration %u", 0);
        vtss_fa_debug_reg_header(pr, buf);
        vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_TICK_CFG), 0, "VOP_TICK_CFG");
        vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TS_CFG), 0, "VOP_MRP_TS_CFG");
        vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_LOC_CTRL), 0, "VOP_LOC_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_VOP_CTRL), 0, "VOP_VOP_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_CPU_EXTR_MRP), 0, "VOP_CPU_EXTR_MRP");
        pr("\n");
    }
    pr("\n");

    if (!info->has_action || status) { /* MRP status must be printed */
        pr("MRP Status:\n\n");

        for (i = 0; i < VTSS_PATH_SERVICE_VOE_CNT; ++i) {
            if (status && (div > 1) && (mrp_idx != i)) {   /* A specific MRP must be printed - this is not the one */
                continue;
            }

            REG_RD(VTSS_VOP_MRP_MRP_CTRL(i), &v);
            if (info->full  ||  VTSS_X_VOP_MRP_MRP_CTRL_MRP_ENA(v)) {
                VTSS_SPRINTF(buf, "MRP %u", i);
                vtss_fa_debug_reg_header(pr, buf);
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_STICKY(i)), i, "MEP_MRP_STICKY");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TST_RX_CNT(i)), i, "VTSS_VOP_MRP_TST_RX_CNT");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TST_RX_LOC_CNT(i)), i, "MEP_TST_RX_LOC_CNT");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_ITST_RX_CNT(i)), i, "VTSS_VOP_MRP_ITST_RX_CNT");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_ITST_RX_LOC_CNT(i)), i, "MEP_ITST_RX_LOC_CNT");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TST_STAT(i)), i, "MRP_TST_STAT");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_ITST_STAT(i)), i, "MRP_ITST_STAT");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_TST_TX_TS(i)), i, "MRP_TST_TX_TS");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_ITST_TX_TS(i)), i, "MRP_ITST_TX_TS");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_TX_SEQ(i, 0)), i, "MRP_MRP_TX_SEQ");
                vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_MRP_MRP_TX_SEQ(i, 1)), i, "MRP_MRP_TX_SEQ");
                pr("\n");
            }
        }
    }
    pr("\n");

    if (!info->has_action || internal) { /* MRP internal must be printed */
        pr("MRP Internal:\n\n");

        for (i = 0; i < VTSS_MRP_CNT; ++i) {
            if (internal && (div > 1) && (mrp_idx != i)) {   /* A specific MRP must be printed - this is not the one */
                continue;
            }

            mrp_data = &vtss_state->mrp.data[i];
            if (info->full  ||  mrp_data->active) {
                pr("MRP %u\n", i);
                pr("active: %u\n", mrp_data->active);
                pr("tst_loc_idx: %u\n", mrp_data->tst_loc_idx);
                pr("itst_loc_idx: %u\n", mrp_data->itst_loc_idx);
                pr("ring_transitions: %u\n", mrp_data->ring_transitions);
                pr("in_ring_transitions: %u\n", mrp_data->in_ring_transitions);

                if (mrp_data->tst_loc_idx != LOC_PERIOD_CNT) {
                    vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_LOC_PERIOD_CFG(mrp_data->tst_loc_idx)), mrp_data->tst_loc_idx, "VOP_LOC_PERIOD_CFG");
                }

                if (mrp_data->itst_loc_idx != LOC_PERIOD_CNT) {
                    vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_VOP_LOC_PERIOD_CFG(mrp_data->itst_loc_idx)), mrp_data->itst_loc_idx, "VOP_LOC_PERIOD_CFG");
                }

                pr("\n");
            }
        }
    }
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_lan969x_mrp_debug_print(vtss_state_t               *vtss_state,
                                     const vtss_debug_printf_t  pr,
                                     const vtss_debug_info_t    *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_MRP, lan969x_debug_mrp, vtss_state, pr, info);
}

static vtss_rc lan969x_mrp_poll_1sec(vtss_state_t *vtss_state)
{
    vtss_mrp_idx_t *idx = &(vtss_state->mrp.mrp_poll_idx);  /* For readability */

    VTSS_RC(mrp_counter_update(vtss_state, *idx, 0));
    *idx = (*idx == VTSS_MRP_CNT - 1) ? 0 : *idx + 1;

    return VTSS_RC_OK;
}

static vtss_rc lan969x_mrp_init(vtss_state_t *vtss_state)
{
    u32 i;

    // Set all instances to default
    for (i = 0; i < VTSS_MRP_CNT; ++i) {
        mrp_instance_default(vtss_state, &vtss_state->mrp.data[i]);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_lan969x_mrp_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_mrp_state_t *state = &vtss_state->mrp;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->mrp_add               = lan969x_mrp_add;
        state->mrp_del               = lan969x_mrp_del;
        state->mrp_primary_port_set  = lan969x_mrp_primary_port_set;
        state->mrp_ring_role_set     = lan969x_mrp_ring_role_set;
        state->mrp_ring_state_set    = lan969x_mrp_ring_state_set;
        state->mrp_in_ring_state_set = lan969x_mrp_in_ring_state_set;
        state->mrp_port_state_set    = lan969x_mrp_port_state_set;
        state->mrp_best_mrm_set      = lan969x_mrp_best_mrm_set;
        state->mrp_tst_loc_conf_set  = lan969x_mrp_tst_loc_conf_set;
        state->mrp_tst_hitme_once    = lan969x_mrp_tst_hitme_once;
        state->mrp_itst_hitme_once   = lan969x_mrp_itst_hitme_once;
        state->mrp_tst_copy_conf_set = lan969x_mrp_tst_copy_conf_set;
        state->mrp_status_get        = lan969x_mrp_status_get;
        state->mrp_counters_get      = lan969x_mrp_counters_get;
        state->mrp_counters_clear    = lan969x_mrp_counters_clear;
        state->mrp_event_mask_set    = lan969x_mrp_event_mask_set;
        state->mrp_event_get         = lan969x_mrp_event_get;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan969x_mrp_init(vtss_state));
        break;

    case VTSS_INIT_CMD_POLL:
        VTSS_RC(lan969x_mrp_poll_1sec(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_MRP */
