// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

//#include <cyg/infra/diag.h>
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)

#if defined(VTSS_FEATURE_CLOCK)
#include "../omega/vtss_omega_clock_cil.h"
#endif

/* Read target register using current CPU interface */
static inline vtss_rc reg_rd_direct(vtss_state_t *vtss_state, u32 reg, u32 *value)
{
#if defined(VTSS_OPT_EMUL)
    if (vtss_state->init_conf.reg_read == NULL) {
        return vtss_fa_emul_rd(reg, value);
    }
#endif
    return vtss_state->init_conf.reg_read(0, reg, value);
}

/* Write target register using current CPU interface */
static inline vtss_rc reg_wr_direct(vtss_state_t *vtss_state, u32 reg, u32 value)
{
#if defined(VTSS_OPT_EMUL)
    if (vtss_state->init_conf.reg_write == NULL) {
        return vtss_fa_emul_wr(reg, value);
    }
#endif
    return vtss_state->init_conf.reg_write(0, reg, value);
}

vtss_rc (*vtss_fa_wr)(vtss_state_t *vtss_state, u32 addr, u32 value) = reg_wr_direct;
vtss_rc (*vtss_fa_rd)(vtss_state_t *vtss_state, u32 addr, u32 *value) = reg_rd_direct;

/* Read-modify-write target register using current CPU interface */
vtss_rc vtss_fa_wrm(vtss_state_t *vtss_state, u32 addr, u32 value, u32 mask)
{
    vtss_rc rc;
    u32     val;

    if ((rc = vtss_fa_rd(vtss_state, addr, &val)) == VTSS_RC_OK) {
        val = ((val & ~mask) | (value & mask));
        rc = vtss_fa_wr(vtss_state, addr, val);
    }
    return rc;
}

void vtss_fa_debug_print_port_header(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr, const char *txt)
{
    vtss_debug_print_port_header(vtss_state, pr, txt, VTSS_CHIP_PORTS, 1);
}

void vtss_fa_debug_print_pmask(const vtss_debug_printf_t pr, vtss_port_mask_t *pmask)
{
    u32 port;

    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        pr("%s%u", port == 0 || (port & 7) ? "" : ".", pmask->m[port / 32] & VTSS_BIT(port % 32) ? 1 : 0);
    }
    pr("\n");
}

void vtss_fa_debug_reg_header(const vtss_debug_printf_t pr, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%-34s", name);
    vtss_debug_print_reg_header(pr, buf);
}

static void fa_debug_reg_clr(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr, u32 addr, const char *name, BOOL clr)
{
    u32 value;
    char buf[64];

    if (vtss_fa_rd(vtss_state, addr, &value) == VTSS_RC_OK &&
        (clr == 0 || vtss_fa_wr(vtss_state, addr, value) == VTSS_RC_OK)) {
        VTSS_SPRINTF(buf, "%-34s", name);
        vtss_debug_print_reg(pr, buf, value);
    }
}

void vtss_fa_debug_reg(vtss_state_t *vtss_state,
                       const vtss_debug_printf_t pr, u32 addr, const char *name)
{
    fa_debug_reg_clr(vtss_state, pr, addr, name, 0);
}

void vtss_fa_debug_reg_inst(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%s_%u", name, i);
    vtss_fa_debug_reg(vtss_state, pr, addr, buf);
}

void vtss_fa_debug_sticky(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr, u32 addr, const char *name)
{
    fa_debug_reg_clr(vtss_state, pr, addr, name, 1);
}

void vtss_fa_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                       vtss_chip_counter_t *c1, vtss_chip_counter_t *c2)
{
    char buf[80];

    if (col1 == NULL) {
        pr("%-41s", "");
    } else {
        VTSS_SPRINTF(buf, "rx_%s:", col1);
        pr("%-28s%10" PRIu64 "   ", buf, c1->value);
    }
    if (col2 != NULL) {
        VTSS_SPRINTF(buf, "tx_%s:", VTSS_STRLEN(col2) ? col2 : col1);
        pr("%-28s%10" PRIu64, buf, c2->value);
    }
    pr("\n");
}

#if defined(VTSS_SDX_CNT)
static void fa_evc_counter_update(u32 frames, u32 lsb, u32 msb, vtss_chip_counter_pair_t *chip_counter,
                                  vtss_counter_pair_t *evc_counter, BOOL clear)
{
   vtss_cmn_counter_32_update(frames, &chip_counter->frames, clear);
   vtss_cmn_counter_40_update(lsb, msb, &chip_counter->bytes, clear);

    if (evc_counter != NULL) {
        evc_counter->frames += chip_counter->frames.value;
        evc_counter->bytes += chip_counter->bytes.value;
    }
}

static vtss_rc fa_evc_isdx_counter_update(vtss_state_t *vtss_state,
                                          u32 idx, u32 i, vtss_chip_counter_pair_t *chip_counter,
                                          vtss_counter_pair_t *evc_counter, BOOL clear)
{
    u32 frames, lsb, msb;

    /* Read frame and byte counters */
    REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(idx, i + 3), &frames);
    REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(idx, i), &lsb);
    REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT(idx, i), &msb);

    /* Update counters */
    fa_evc_counter_update(frames, lsb, msb, chip_counter, evc_counter, clear);

    return VTSS_RC_OK;
}

static vtss_rc fa_evc_qsys_counter_update(vtss_state_t *vtss_state,
                                          u32 addr, vtss_chip_counter_pair_t *chip_counter,
                                          vtss_counter_pair_t *evc_counter, BOOL clear)
{
    u32 frames, lsb, msb;

    /* Read frame and byte counters */
    REG_RD(VTSS_XQS_CNT(addr), &frames);
    REG_RD(VTSS_XQS_CNT(addr + 64), &lsb);
    REG_RD(VTSS_XQS_CNT(addr + 128), &msb);
    /* Update counters */
    fa_evc_counter_update(frames, lsb, msb, chip_counter, evc_counter, clear);

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_sdx_counters_update(vtss_state_t *vtss_state, vtss_stat_idx_t *stat_idx, vtss_evc_counters_t *const cnt, BOOL clr)
{
    u16                 idx;
    vtss_sdx_counters_t *c;
    vtss_xrow_entry_t   *row;

    /* Update ingress counters, if active */
    idx = stat_idx->idx;
    row = &vtss_state->l2.istat_table.row[idx / 8];
    if (row->size != 0 && row->col[row->size * ((idx % 8) / row->size)].used) {
        /* ISDX counters */
        c = &vtss_state->l2.sdx_info.sdx_table[idx];
        VTSS_RC(fa_evc_isdx_counter_update(vtss_state, idx, 0, &c->rx_green, cnt == NULL ? NULL : &cnt->rx_green, clr));
        VTSS_RC(fa_evc_isdx_counter_update(vtss_state, idx, 1, &c->rx_yellow, cnt == NULL ? NULL : &cnt->rx_yellow, clr));
        VTSS_RC(fa_evc_isdx_counter_update(vtss_state, idx, 2, &c->rx_red, cnt == NULL ? NULL : &cnt->rx_red, clr));

        /* QSYS counters */
        REG_WR(VTSS_XQS_STAT_CFG, VTSS_F_XQS_STAT_CFG_STAT_VIEW(idx));
        VTSS_RC(fa_evc_qsys_counter_update(vtss_state, 512, &c->rx_discard, cnt == NULL ? NULL : &cnt->rx_discard, clr));
        VTSS_RC(fa_evc_qsys_counter_update(vtss_state, 513, &c->tx_discard, cnt == NULL ? NULL : &cnt->rx_discard, clr));
    }

    /* Update egress counters, if active */
    idx = stat_idx->edx;
    row = &vtss_state->l2.estat_table.row[idx / 8];
    if (row->size != 0 && row->col[row->size * ((idx % 8) / row->size)].used) {
        c = &vtss_state->l2.sdx_info.sdx_table[idx];
        REG_WR(VTSS_XQS_STAT_CFG, VTSS_F_XQS_STAT_CFG_STAT_VIEW(idx));
        VTSS_RC(fa_evc_qsys_counter_update(vtss_state, 768, &c->tx_green, cnt == NULL ? NULL : &cnt->tx_green, clr));
        VTSS_RC(fa_evc_qsys_counter_update(vtss_state, 769, &c->tx_yellow, cnt == NULL ? NULL : &cnt->tx_yellow, clr));
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_isdx_update(vtss_state_t *vtss_state, vtss_sdx_entry_t *sdx)
{
    u32 cosid, isdx = sdx->sdx;
    u32 pol_max = (sdx->pol_cnt ? (sdx->pol_cnt - 1) : 0);
    u32 stat_max = (sdx->stat_cnt ? (sdx->stat_cnt - 1) : 0);

    REG_WR(VTSS_ANA_L2_DLB_CFG(isdx), VTSS_F_ANA_L2_DLB_CFG_DLB_IDX(sdx->pol_idx));
    REG_WR(VTSS_ANA_L2_ISDX_BASE_CFG(isdx), VTSS_F_ANA_L2_ISDX_BASE_CFG_ISDX_BASE_ADDR(sdx->stat_idx));
    for (cosid = 0; cosid < 8; cosid++) {
        REG_WR(VTSS_ANA_L2_DLB_COS_CFG(isdx, cosid), VTSS_F_ANA_L2_DLB_COS_CFG_DLB_COS_OFFSET(cosid <= pol_max ? cosid : pol_max));
        REG_WR(VTSS_ANA_L2_ISDX_COS_CFG(isdx, cosid), VTSS_F_ANA_L2_ISDX_COS_CFG_ISDX_COS_OFFSET(cosid <= stat_max ? cosid : stat_max));
    }
    REG_WR(VTSS_EACL_FRER_FIRST_MEMBER(isdx), sdx->ms_idx);
    return VTSS_RC_OK;
}

/* Clock period in picoseconds */
u32 vtss_fa_clk_period(vtss_core_clock_freq_t clock)
{
    switch (clock) {
    case VTSS_CORE_CLOCK_250MHZ: return 4000;
    case VTSS_CORE_CLOCK_500MHZ: return 2000;
    case VTSS_CORE_CLOCK_625MHZ:
    default: {};
    }
    return 1600; // Default
}


#endif /* VTSS_SDX_CNT */

/* ================================================================= *
 *  Debug print utility functions
 * ================================================================= */

static vtss_rc fa_debug_info_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_fa_misc_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_fa_port_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_fa_l2_debug_print(vtss_state, pr, info));
#if defined(VTSS_FEATURE_LAYER3)
    VTSS_RC(vtss_fa_l3_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_LAYER3 */
#if defined(VTSS_FEATURE_VCAP)
    VTSS_RC(vtss_fa_vcap_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_VCAP */
#if defined(VTSS_FEATURE_QOS)
    VTSS_RC(vtss_fa_qos_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_QOS */
    VTSS_RC(vtss_fa_packet_debug_print(vtss_state, pr, info));
#if defined(VTSS_FEATURE_AFI_SWC)
    VTSS_RC(vtss_fa_afi_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_AFI_SWC */
#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_fa_ts_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_TIMESTAMP */
#if defined(VTSS_FEATURE_VOP)
    VTSS_RC(vtss_fa_vop_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_VOP */
#if defined(VTSS_FEATURE_FDMA) && VTSS_OPT_FDMA
    if (vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_FDMA)) {
        if (vtss_state->fdma_state.fdma_func.fdma_debug_print != NULL) {
            return vtss_state->fdma_state.fdma_func.fdma_debug_print(vtss_state, pr, info);
        } else {
            return VTSS_RC_ERROR;
        }
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    VTSS_N("Enter");

    /* Initialize ports */
    VTSS_RC(vtss_fa_port_init(vtss_state, cmd));

    /* Initialize miscellaneous */
    VTSS_RC(vtss_fa_misc_init(vtss_state, cmd));

    /* Initialize packet before L2 to ensure that VLAN table clear does not break VRAP access */
    VTSS_RC(vtss_fa_packet_init(vtss_state, cmd));

#if defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_AFI_V2)
    VTSS_RC(vtss_fa_afi_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_AFI_SWC&& VTSS_AFI_V2 */

    /* Initialize L2 */
    VTSS_RC(vtss_fa_l2_init(vtss_state, cmd));

#if defined(VTSS_FEATURE_LAYER3)
    /* Initialize L3 */
    VTSS_RC(vtss_fa_l3_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_LAYER3 */

#if defined(VTSS_FEATURE_VCAP)
    VTSS_RC(vtss_fa_vcap_init(vtss_state, cmd));
#endif

#if defined(VTSS_FEATURE_QOS)
    VTSS_RC(vtss_fa_qos_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_QOS */

#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_fa_ts_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_TIMESTAMP */

#if defined(VTSS_FEATURE_VOP)
    VTSS_RC(vtss_fa_vop_init(vtss_state, cmd));
#endif

#if defined(VTSS_FEATURE_CLOCK)
    VTSS_RC(vtss_es6514_clock_init(vtss_state, cmd));
#endif

    return VTSS_RC_OK;
}

static u32 fa_target_bw(vtss_state_t *vtss_state)
{
    switch (vtss_state->create.target) {
    case VTSS_TARGET_7546:
    case VTSS_TARGET_7546TSN:
        return 65000;
    case VTSS_TARGET_7549:
    case VTSS_TARGET_7549TSN:
        return 91000;
    case VTSS_TARGET_7552:
    case VTSS_TARGET_7552TSN:
        return 129000;
    case VTSS_TARGET_7556:
    case VTSS_TARGET_7556TSN:
        return 161000;
    case VTSS_TARGET_7558:
    case VTSS_TARGET_7558TSN:
        return 201000;
    default: {}
    }
    return 0;
}

static vtss_rc fa_core_clock_config(vtss_state_t *vtss_state)
{
    u32 clk_div, clk_period, pol_upd_int, val;
    vtss_core_clock_freq_t freq, f = vtss_state->init_conf.core_clock.freq;
    freq = f;

    /* Verify if core clock frequency is supported on target */
    /* If 'VTSS_CORE_CLOCK_DEFAULT' then the highest supported freq. is used */
    switch (vtss_state->create.target) {
    case VTSS_TARGET_7546:
        if (f == VTSS_CORE_CLOCK_DEFAULT) {
            freq = VTSS_CORE_CLOCK_250MHZ;
        } else if (f != VTSS_CORE_CLOCK_250MHZ) {
            freq = 0; // Not supported
        }
        break;
    case VTSS_TARGET_7549:
    case VTSS_TARGET_7552:
    case VTSS_TARGET_7556:
        if (f == VTSS_CORE_CLOCK_DEFAULT) {
            freq = VTSS_CORE_CLOCK_500MHZ;
        } else if (f != VTSS_CORE_CLOCK_500MHZ) {
            freq = 0; // Not supported
        }
        break;
    case VTSS_TARGET_7558:
    case VTSS_TARGET_7558TSN:
        if (f == VTSS_CORE_CLOCK_DEFAULT) {
            freq = VTSS_CORE_CLOCK_625MHZ;
        } else if (f != VTSS_CORE_CLOCK_625MHZ) {
            freq = 0; // Not supported
        }
        break;
    case VTSS_TARGET_7546TSN:
        if (f == VTSS_CORE_CLOCK_DEFAULT) {
            freq = VTSS_CORE_CLOCK_625MHZ;
        }
        break;
    case VTSS_TARGET_7549TSN:
    case VTSS_TARGET_7552TSN:
    case VTSS_TARGET_7556TSN:
        if (f == VTSS_CORE_CLOCK_DEFAULT) {
            freq = VTSS_CORE_CLOCK_625MHZ;
        } else if (f == VTSS_CORE_CLOCK_250MHZ) {
            freq = 0; // Not supported
        }
        break;
    default:
        VTSS_E("Target (%x) not supported",vtss_state->create.target);
        return VTSS_RC_ERROR;
    }

    switch (freq) {
    case VTSS_CORE_CLOCK_250MHZ:
        clk_div = 10;
        pol_upd_int = 312;
        break;
    case VTSS_CORE_CLOCK_500MHZ:
        clk_div = 5;
        pol_upd_int = 624;
        break;
    case VTSS_CORE_CLOCK_625MHZ:
        clk_div = 4;
        pol_upd_int = 780;
        break;
    default:
        VTSS_E("Frequency (%d) not supported on target (%x)",f, vtss_state->create.target);
        return VTSS_RC_OK;
    }

    /* Update state with chosen frequency */
    vtss_state->init_conf.core_clock.freq = freq;

    /* Enable DPLL fractional mode (if not enabled already, MESA-825) */
    REG_RD(VTSS_LCPLL28_LCPLL_CONFIG2, &val);
    if (VTSS_X_LCPLL28_LCPLL_CONFIG2_F(val) == 0) {
        REG_RD(VTSS_DEVCPU_GCB_HW_STAT, &val);

        switch (VTSS_X_DEVCPU_GCB_HW_STAT_PLL0_CONF(val)) {
        case 0: val = 80;  break;  /* 125Mhz   */
        case 1: val = 64;  break;  /* 156.2Mhz */
        case 4: val = 400; break;  /* 25Mhz    */
        default:
            VTSS_E("PLL0 value not supported");
            return VTSS_RC_ERROR;
        }
        REG_WRM(VTSS_LCPLL28_LCPLL_CONFIG2,
                VTSS_F_LCPLL28_LCPLL_CONFIG2_F(val),
                VTSS_M_LCPLL28_LCPLL_CONFIG2_F);

        REG_WRM(VTSS_LCPLL28_LCPLL_CONFIG3,
                VTSS_F_LCPLL28_LCPLL_CONFIG3_R(511),
                VTSS_M_LCPLL28_LCPLL_CONFIG3_R);

        REG_WRM(VTSS_LCPLL28_LCPLL_CONFIG3,
                VTSS_F_LCPLL28_LCPLL_CONFIG3_PDSIG(0),
                VTSS_M_LCPLL28_LCPLL_CONFIG3_PDSIG);
    }

    /* Configure the LCPLL */
    REG_WRM(VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG,
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_DIV(clk_div) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_PRE_DIV(0) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_DIR(0) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_SEL(0) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_ENA(0) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_ENA(1),
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_DIV |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_PRE_DIV |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_DIR |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_SEL |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_ENA |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_ENA);

    clk_period = vtss_fa_clk_period(freq);
    REG_WRM(VTSS_HSCH_SYS_CLK_PER,
            VTSS_F_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS(clk_period/100),
            VTSS_M_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS);

    REG_WRM(VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL,
            VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS(clk_period/100),
            VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS);

    REG_WRM(VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL,
            VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS(clk_period/100),
            VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS);

    REG_WRM(VTSS_LRN_AUTOAGE_CFG_1,
            VTSS_F_LRN_AUTOAGE_CFG_1_CLK_PERIOD_01NS(clk_period/100),
            VTSS_M_LRN_AUTOAGE_CFG_1_CLK_PERIOD_01NS);

    for(u8 i = 0; i < 3; i++) {
        REG_WRM(VTSS_DEVCPU_GCB_SIO_CLOCK(i),
                VTSS_F_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD(clk_period/100),
                VTSS_M_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD);
    }

    REG_WRM(VTSS_HSCH_TAS_STATEMACHINE_CFG,
            VTSS_F_HSCH_TAS_STATEMACHINE_CFG_REVISIT_DLY((256 * 1000) / clk_period),
            VTSS_M_HSCH_TAS_STATEMACHINE_CFG_REVISIT_DLY);

    REG_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG,
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT(pol_upd_int),
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT);

#if 0 // TBD need info from frontend, below is copied from JR2 - TBD-BJO
    // Adapt other blocks to the new core speed
    REG_WRM(VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL,
            VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS(36),
            VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS);

    REG_WRM(VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL,
            VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS(36),
            VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS);

    REG_WRM(VTSS_LRN_AUTOAGE_CFG_1,
            VTSS_F_LRN_AUTOAGE_CFG_1_CLK_PERIOD_01NS(36),
            VTSS_M_LRN_AUTOAGE_CFG_1_CLK_PERIOD_01NS);

    REG_WRM(VTSS_HSCH_SYS_CLK_PER,
            VTSS_F_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS(36),
            VTSS_M_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS);

    REG_WRM(VTSS_VOP_LOC_CTRL,
            VTSS_F_VOP_LOC_CTRL_LOC_BASE_TICK_CNT(28), // 100/3.6
            VTSS_M_VOP_LOC_CTRL_LOC_BASE_TICK_CNT);

    REG_WRM(VTSS_AFI_TTI_TICK_BASE,
            VTSS_F_AFI_TTI_TICK_BASE_BASE_LEN(14444), // 52us/3.6ns
            VTSS_M_AFI_TTI_TICK_BASE_BASE_LEN);
#endif

    VTSS_I("Setting Core Clock - done");
    return VTSS_RC_OK;
}

static vtss_rc fa_init_switchcore(vtss_state_t *vtss_state)
{
    u32 value, pending, j, i;

   // Note; by design - all gazwrap init registers have the same field layout
    struct {
        BOOL gazwrap;
        u32  init_reg;
        u32  init_val;
    } r, ram_init_list[] = {
        {FALSE, VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET,
         VTSS_M_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET_RESET},
        {FALSE, VTSS_ASM_STAT_CFG, VTSS_M_ASM_STAT_CFG_STAT_CNT_CLR_SHOT},
        {TRUE,  VTSS_QSYS_RAM_INIT, 0},
        {TRUE,  VTSS_REW_RAM_INIT, 0},
        {TRUE,  VTSS_VOP_RAM_INIT, 0},
        {TRUE,  VTSS_ANA_AC_RAM_CTRL_RAM_INIT, 0},
        {TRUE,  VTSS_ASM_RAM_INIT, 0},
        {TRUE,  VTSS_EACL_RAM_INIT, 0},
        {TRUE,  VTSS_VCAP_SUPER_RAM_INIT, 0},
        {TRUE,  VTSS_DSM_RAM_INIT, 0}};

    u32 init_cnt = (sizeof(ram_init_list)/sizeof(ram_init_list[0]));

    REG_WRM(VTSS_EACL_POL_EACL_CFG,
            VTSS_F_EACL_POL_EACL_CFG_EACL_FORCE_INIT(1),
            VTSS_M_EACL_POL_EACL_CFG_EACL_FORCE_INIT);

    REG_WRM(VTSS_EACL_POL_EACL_CFG,
            VTSS_F_EACL_POL_EACL_CFG_EACL_FORCE_INIT(0),
            VTSS_M_EACL_POL_EACL_CFG_EACL_FORCE_INIT);

    /* Initialize memories, if not done already */
    REG_RD(VTSS_HSCH_RESET_CFG, &value);

    if (!(value & VTSS_M_HSCH_RESET_CFG_CORE_ENA)) {
        for (i=0; i<10; i++) {
            pending = init_cnt;
            for (j = 0; j < init_cnt; j++) {
                r = ram_init_list[j];
                if (r.gazwrap) {
                    r.init_val = VTSS_M_QSYS_RAM_INIT_RAM_INIT;
                }

                if (i == 0) {
                    if (r.gazwrap) {
                        REG_WR(r.init_reg, r.init_val);
                    } else {
                        REG_WRM_SET(r.init_reg, r.init_val);
                    }
                } else {
                    REG_RD(r.init_reg, &value);
                    if ((value & r.init_val) != r.init_val) {
                        pending--;
                    }
                }
            }
            if (!pending) {
                break;
            }
            VTSS_MSLEEP(1);
        }

        if (pending > 0) {
            /* Still initializing, should be complete in less than 1ms */
            VTSS_E("Memory initialization error");
            return VTSS_RC_ERROR;
        }
    }
    VTSS_I("Resetting switch core and memories - done");
    return VTSS_RC_OK;
}

static vtss_rc fa_init_conf_set(vtss_state_t *vtss_state)
{
    u32 i;

    /* Initialize Switchcore and internal RAMs */
    if (fa_init_switchcore(vtss_state) != VTSS_RC_OK) {
        VTSS_E("Switchcore initialization error");
        return VTSS_RC_ERROR;
    }

    /* Initialize the LC-PLL (core clock) and set affected registers */
    if (fa_core_clock_config(vtss_state) != VTSS_RC_OK) {
         VTSS_E("LC-PLL initialization error");
    }

    /* Enable switch core and queue system */
    REG_WR(VTSS_HSCH_RESET_CFG, VTSS_F_HSCH_RESET_CFG_CORE_ENA(1));
    for (i = VTSS_CHIP_PORTS; i < VTSS_CHIP_PORTS_ALL; i++) {
        REG_WRM_SET(VTSS_QFWD_SWITCH_PORT_MODE(i),
                    VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA);
    }

    /* Set ASM/DSM watermarks for cpu traffic (see JR2) - needed here or handled by wm function ? TBD-BJO */
#if !defined(VTSS_OPT_EMUL)
    u32 value;
    REG_RD(VTSS_CPU_GENERAL_STAT, &value);
    vtss_state->sys_config.vcore_cfg = VTSS_X_CPU_GENERAL_STAT_VCORE_CFG(value);

    /* DS1241: 5 (8-12) available VCORE boot modes */
    vtss_state->sys_config.using_vcoreiii = (vtss_state->sys_config.vcore_cfg >= 8 &&
                                             vtss_state->sys_config.vcore_cfg <= 12);

#if defined(VTSS_OPT_VRAP_ACCESS)
    /* DS1241: 8 (0-7) available VRAP boot modes */
    vtss_state->sys_config.using_vrap = (vtss_state->sys_config.vcore_cfg >= 0 &&
                                         vtss_state->sys_config.vcore_cfg <= 7);
#else
    vtss_state->sys_config.using_vrap = 0;
#endif //VTSS_OPT_VRAP_ACCESS

#if defined(VTSS_OPT_PCIE_ACCESS)
    /* DS1241: 8 (0-7) available boot modes */
    vtss_state->sys_config.using_pcie = ((vtss_state->sys_config.vcore_cfg >= 0 &&
                                          vtss_state->sys_config.vcore_cfg <= 7);
#else
    vtss_state->sys_config.using_pcie = 0;
#endif //VTSS_OPT_PCIe_ACCESS
    VTSS_I("Vcore_cfg: 0x%04x, VCOREIII: %d, VRAP: %d, PCIe: %d",
           vtss_state->sys_config.vcore_cfg,
           vtss_state->sys_config.using_vcoreiii,
           vtss_state->sys_config.using_vrap,
           vtss_state->sys_config.using_pcie);
#endif /* VTSS_OPT_EMUL */
    /* Read chip ID to check CPU interface */
    VTSS_FUNC_RC(misc.chip_id_get, &vtss_state->misc.chip_id);
    VTSS_I("chip_id: 0x%04x, revision: 0x%04x",
           vtss_state->misc.chip_id.part_number, vtss_state->misc.chip_id.revision);

    /* Initialize function groups */
    VTSS_RC(vtss_fa_init_groups(vtss_state, VTSS_INIT_CMD_INIT));

    return VTSS_RC_OK;
}

/* Enum value maps directly to register bw value */
typedef enum {
    FA_CAL_SPEED_NONE = 0,
    FA_CAL_SPEED_1G   = 1,
    FA_CAL_SPEED_2G5  = 2,
    FA_CAL_SPEED_5G   = 3,
    FA_CAL_SPEED_10G  = 4,
    FA_CAL_SPEED_25G  = 5
} fa_cal_speed_t;

static fa_cal_speed_t fa_cal_speed_get(vtss_state_t *vtss_state, vtss_port_no_t port_no, i32 *port, i32 used_bw, i32 max_bw)
{
    vtss_internal_bw_t max_port_bw;

    if (port_no >= VTSS_PORTS) {
        // Internal ports (and ports outside of port map)
        *port = (VTSS_CHIP_PORT_CPU + port_no - VTSS_CHIP_PORTS);
        if (port_no == VTSS_CHIP_PORT_CPU_0 || port_no == VTSS_CHIP_PORT_CPU_1) {
            return FA_CAL_SPEED_2G5; // Equals 1.25G
        } else if (port_no == VTSS_CHIP_PORT_VD0) {
            // IPMC only idle BW
            return FA_CAL_SPEED_NONE;
        } else if (port_no == VTSS_CHIP_PORT_VD1) {
            if (max_bw - used_bw >= 25000) {
                return FA_CAL_SPEED_25G; // OAM equals 12.5G
            } else if (max_bw - used_bw >= 10000) {
                return FA_CAL_SPEED_10G; // OAM equals 5G
            } else if (max_bw - used_bw >= 5000) {
                return FA_CAL_SPEED_5G;  // OAM equals 2G5
            } else if (max_bw - used_bw >= 2500) {
                return FA_CAL_SPEED_2G5;  // OAM equals 1.25G
            } else {
                return FA_CAL_SPEED_1G;
            }
        } else if (port_no == VTSS_CHIP_PORT_VD2) {
            // IPinIP gets only idle BW
            return FA_CAL_SPEED_NONE;
        } else {
            // not in port map
            return FA_CAL_SPEED_NONE;
        }
    }

    // Switch port. Use the port map.
    if ((*port = VTSS_CHIP_PORT(port_no)) == CHIP_PORT_UNUSED) {
        return FA_CAL_SPEED_NONE;
    }

    max_port_bw = vtss_state->port.map[port_no].max_bw;

    VTSS_D("port = %u (chip_port = %u): max_bw = %u", port_no, *port, max_bw);
    switch (max_port_bw) {
    case VTSS_BW_DEFAULT:
        return (VTSS_PORT_IS_2G5(*port) ? FA_CAL_SPEED_2G5 : VTSS_PORT_IS_5G(*port) ? FA_CAL_SPEED_5G :
        VTSS_PORT_IS_10G(*port) ? FA_CAL_SPEED_10G : FA_CAL_SPEED_25G);
        break;
        case VTSS_BW_1G:   return FA_CAL_SPEED_1G;
        case VTSS_BW_2G5:  return FA_CAL_SPEED_2G5;
        case VTSS_BW_5G:   return FA_CAL_SPEED_5G;
        case VTSS_BW_10G:  return FA_CAL_SPEED_10G;
        case VTSS_BW_25G:  return FA_CAL_SPEED_25G;
        case VTSS_BW_UNDEFINED:
        default:
            VTSS_E("port_no = %u (chip_port = %u): In the port map, but with undefined B/W ().", port_no, *port);
            break;
    }

    return FA_CAL_SPEED_NONE;
}


static i32 clock2bw(vtss_core_clock_freq_t freq) {
    if (freq == VTSS_CORE_CLOCK_250MHZ) {
        return 83000; /* 250000 / 3 */
    } else if (freq == VTSS_CORE_CLOCK_500MHZ) {
        return 166000; /* 500000 / 3 */
    } else if (freq == VTSS_CORE_CLOCK_625MHZ) {
        return  208000; /* 625000 / 3 */
    } else {
        VTSS_E("Core clock not supported");
    }
    return 0;
}

// Auto configure the calendar based on port-map
static vtss_rc fa_calendar_auto(vtss_state_t *vtss_state)
{
    u32                cal[7], value;
    fa_cal_speed_t     spd;
    u32                i;
    vtss_port_no_t     port_no;
    i32                port, this_bw, max_core_bw, bw = 0, port_bw = 0;

    VTSS_I("Using Auto calendar");
    max_core_bw = clock2bw(vtss_state->init_conf.core_clock.freq);
    // Setup the calendar, i.e. the BW to each device
    VTSS_MEMSET(cal, 0, sizeof(cal));
    for (port_no = 0; port_no < VTSS_CHIP_PORTS_ALL; port_no++) {
        spd = fa_cal_speed_get(vtss_state, port_no, &port, bw, max_core_bw);
        if (port == CHIP_PORT_UNUSED || spd == FA_CAL_SPEED_NONE) {
            continue;
        }

        this_bw = (spd == FA_CAL_SPEED_1G ? 1000 : spd == FA_CAL_SPEED_2G5 ? 2500 :
                   spd == FA_CAL_SPEED_5G ? 5000 : spd == FA_CAL_SPEED_10G ? 10000 : 25000);

        if (port_no < VTSS_PORTS) {
            port_bw += this_bw;
        }

        if (port_no >= VTSS_PORTS) {
            this_bw = this_bw/2; // Internal ports are granted half the value
        }
        bw += this_bw;
        VTSS_D("chip_port = %u, this_bw = %u, summed bw = %u", port, this_bw, bw);
        cal[port/10] += (spd << ((port % 10) * 3));
    }

    if (port_bw > fa_target_bw(vtss_state)) {
        VTSS_E("The configured port BW (%d) is above BW supported by target (VSC%x / %d Mbps)",
               port_bw, vtss_state->create.target, fa_target_bw(vtss_state));
        return VTSS_RC_ERROR;
    }

    if (bw > max_core_bw) {
        VTSS_E("The configured BW (%d) is above switch core BW (%d)", bw, max_core_bw);
        return VTSS_RC_ERROR;
    }

    /* Halt the calendar while changing it */
    REG_WRM(VTSS_QSYS_CAL_CTRL,
            VTSS_F_QSYS_CAL_CTRL_CAL_MODE(10),
            VTSS_M_QSYS_CAL_CTRL_CAL_MODE);

    /* Assign device BW to auto calendar */
    for (i = 0; i < 7; i++) {
        REG_WR(VTSS_QSYS_CAL_AUTO(i), cal[i]);
    }

    /* Increase grant rate of all ports to account for core clock ppm deviations */
    REG_WRM(VTSS_QSYS_CAL_CTRL,
            VTSS_F_QSYS_CAL_CTRL_CAL_AUTO_GRANT_RATE(671), /* 672->671, BZ19678 */
            VTSS_M_QSYS_CAL_CTRL_CAL_AUTO_GRANT_RATE);

    /* Grant idle usage to VD0-2 */
    for (i = 2; i < 5; i++) {
        REG_WR(VTSS_HSCH_OUTB_SHARE_ENA(i),
               VTSS_F_HSCH_OUTB_SHARE_ENA_OUTB_SHARE_ENA(12));
    }

    /* Enable Auto mode */
    REG_WRM(VTSS_QSYS_CAL_CTRL,
            VTSS_F_QSYS_CAL_CTRL_CAL_MODE(8),
            VTSS_M_QSYS_CAL_CTRL_CAL_MODE);

    /* Verify successful calendar config */
    REG_RD(VTSS_QSYS_CAL_CTRL, &value);
    if (VTSS_X_QSYS_CAL_CTRL_CAL_AUTO_ERROR(value)) {
        VTSS_E("Calendar auto error");
    }

    VTSS_I("Auto calendar - Done");

    return VTSS_RC_OK;
}
// Defines for DSM calender calculation
#define DSM_CAL_LEN 64
#define DSM_CAL_EMPTY 0xFFFF
#define DSM_CAL_MAX_DEVS_PER_TAXI 13
#define DSM_CAL_TAXIS 8
#define DSM_CAL_BW_LOSS 553

static u32 dsm_cal_len(u32 *cal)
{
    u32 i = 0, len = 0;
    while(i < DSM_CAL_LEN) {
        if (cal[i] != DSM_CAL_EMPTY)
            len++;
        i++;
    }
    return len;
}

static u32 dsm_exb_gcd(u32 a, u32 b)

{
    if (b == 0) {
        return a;
    }
    return dsm_exb_gcd(b, a % b);
}

static u32 dsm_cp_cal(u32 *sched)
{
    u32 i = 0, tmp;
    while(i < DSM_CAL_LEN) {
        if (sched[i] != DSM_CAL_EMPTY) {
            tmp = sched[i];
            sched[i] = DSM_CAL_EMPTY;
            return tmp;
        }
        i++;
    }
    return DSM_CAL_EMPTY;
}

static vtss_rc fa_dsm_set_calendar(vtss_state_t *vtss_state, u32 taxi, u32 *calender)
{
    u32 len = dsm_cal_len(calender), val;

    REG_WRM_SET(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_ENA);
    for (u32 i = 0; i < len; i++) {
        REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_F_DSM_TAXI_CAL_CFG_CAL_IDX(i),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_IDX);

        REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_F_DSM_TAXI_CAL_CFG_CAL_PGM_VAL(calender[i]),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_VAL);
    }

    REG_WRM_CLR(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_ENA);
    REG_RD(VTSS_DSM_TAXI_CAL_CFG(taxi), &val);
    val = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_LEN(val);
    if (val != len - 1) {
        VTSS_E("Calender length is not correct (%d)",val);
    }
    return VTSS_RC_OK;
}


static vtss_rc fa_dsm_chk_calender(vtss_state_t *vtss_state, u32 *calender, i32 *avg_dist)
{
    u32 num_of_slots, slot_indices[DSM_CAL_LEN], distances[DSM_CAL_LEN];
    int cnt, i, j, max_dist;
    u32 cal_length = dsm_cal_len(calender);

    for (u32 port = 0; port < DSM_CAL_MAX_DEVS_PER_TAXI; port++) {
        num_of_slots = 0;
        max_dist = avg_dist[port];
        for (i = 0; i < DSM_CAL_LEN; i++) {
            slot_indices[i] = DSM_CAL_EMPTY;
            distances[i] = DSM_CAL_EMPTY;
        }

        for (i = 0; i < cal_length; i++) {
            if (calender[i] == port) {
                slot_indices[num_of_slots] = i;
                num_of_slots++;
            }
        }

        slot_indices[num_of_slots] = slot_indices[0] + cal_length;

        for (i = 0; i < num_of_slots; i++) {
            distances[i] = (slot_indices[i+1] - slot_indices[i]) * 10;
        }

        for (i = 0; i < num_of_slots; i++) {
            cnt = distances[i] - max_dist;
            if (cnt < 0)
                cnt *= -1;
            u32 a = 0;
            for (j = (i + 1) % num_of_slots; j != i; j = (j + 1) % num_of_slots, a++) {
                cnt =  cnt + distances[j] - max_dist;
                if (cnt < 0)
                    cnt *= -1;
                if (cnt > max_dist) {
                    VTSS_E("Max distance violation for port %d cnt:%d max_dist:%d\n",port,cnt,max_dist);
                    return 1;
                }
            }
        }
    }
    return VTSS_RC_OK;
}

/* MESA-641. Function ported from verification/TCL to manually calculate fifo size for DSM calender */
u32 vtss_get_fifo_size(vtss_state_t *vtss_state, vtss_port_no_t port_no) {
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    u32 sys_clk = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);
    u32 mac_width = 8;
    u32 fifo_width = 16;
    u32 addition = 0;
    u32 mac_per = 6400, tmp1, tmp2, tmp3;
    u32 port   = VTSS_CHIP_PORT(port_no);
    u32 taxi_dist[VTSS_CHIP_PORTS_ALL] = {6,8,10,6,8,10,6,8,10,6,8,10,\
                                          4,4,4,4,\
                                          11,12,13,14,15,16,17,18, \
                                          11,12,13,14,15,16,17,18,\
                                          11,12,13,14,15,16,17,18,\
                                          11,12,13,14,15,16,17,18,\
                                          4,6,8,4,6,8,6,8,\
                                          2,2,2,2,2,2,2,4,2};
    switch (conf->speed) {
    case VTSS_SPEED_25G:
        return 0;
        break;
    case VTSS_SPEED_10G:
        mac_per = 6400;
        mac_width = 8;
        addition = 1;
        break;
    case VTSS_SPEED_5G:
        mac_per = 12800;
        mac_width = 8;
        addition = 0;
        break;
    case VTSS_SPEED_2500M:
        mac_per = 3200;
        mac_width = 1;
        addition = 0;
        break;
    case VTSS_SPEED_1G:
        mac_per =  8000;
        mac_width = 1;
        addition = 0;
        break;
    case VTSS_SPEED_100M:
    case VTSS_SPEED_10M:
        return 1;
    default:{}
    }

    tmp1 = 1000 * mac_width / fifo_width;
    tmp2 = 3000 + ((12000 + 2 * taxi_dist[port] * 1000) * sys_clk / mac_per);
    tmp3 = tmp1 * tmp2 / 1000;
    return  (tmp3 + 2000 + 999) / 1000 + addition;
}


static char *cal2txt(u32 port, fa_cal_speed_t spd) {
    switch (spd) {
    case FA_CAL_SPEED_1G:
        if (port < 65) {
            return "1G";
        } else {
            return "500M";
        }
    case FA_CAL_SPEED_2G5:
        if (port < 65) {
            return "2G5";
        } else {
            return "1.25G";
        }
    case FA_CAL_SPEED_5G:
        if (port < 65) {
            return "5G";
        } else {
            return "2G5";
        }
    case FA_CAL_SPEED_10G:
        if (port < 65) {
            return "10G";
        } else {
            return "5G";
        }
    case FA_CAL_SPEED_25G:
        if (port < 65) {
            return "25G";
        } else {
            return "12.5G";
        }
    default:
        break;
    }
    return "?";
}

static u32 calspd2int(fa_cal_speed_t spd) {
    switch (spd) {
    case FA_CAL_SPEED_1G:  return 1000;
    case FA_CAL_SPEED_2G5: return 2500;
    case FA_CAL_SPEED_5G:  return 5000;
    case FA_CAL_SPEED_10G: return 10000;
    case FA_CAL_SPEED_25G: return 25000;
    default:
        break;
    }
    return 0;
}

static void taxi2ports(u32 taxi, u32 *port_ptr) {
    u32 taxi_ports[DSM_CAL_TAXIS][DSM_CAL_MAX_DEVS_PER_TAXI] = {
        {57,12,0,1,2,16,17,18,19,20,21,22,23},
        {58,13,3,4,5,24,25,26,27,28,29,30,31},
        {59,14,6,7,8,32,33,34,35,36,37,38,39},
        {60,15,9,10,11,40,41,42,43,44,45,46,47},
        {61,48,49,50,99,99,99,99,99,99,99,99,99},
        {62,51,52,53,99,99,99,99,99,99,99,99,99},
        {56,63,54,55,99,99,99,99,99,99,99,99,99},
        {64,99,99,99,99,99,99,99,99,99,99,99,99},
    };
    VTSS_MEMCPY(port_ptr, &taxi_ports[taxi], sizeof(u32) * DSM_CAL_MAX_DEVS_PER_TAXI);
}


static vtss_rc fa_dsm_calc_calender(vtss_state_t *vtss_state, u32 taxi, u32 *schedule, i32 *avg_dist) {
    u32 gcd, k, i, a, sum = 0, min = 25000, factor, adjusted_speed;
    u32 num_of_slots, slot_spd, raw_spd, spd, empty_slots;
    u32 indices_len, act, ts, cal_spd, port_spd;
    i32 port = 0, cnt;
    u32 num_of_old_slots, num_of_new_slots, tgt_score;
    u32 taxi_bw, slow_mode, clk_period_ps;
    u32 port_speeds[VTSS_CHIP_PORTS_ALL] = {0};
    u32 taxi_ports[DSM_CAL_MAX_DEVS_PER_TAXI] = {0};
    u32 taxi_speeds[DSM_CAL_MAX_DEVS_PER_TAXI] = {0};
    u32 dev_slots[DSM_CAL_MAX_DEVS_PER_TAXI] = {0};
    u32 new_slots[DSM_CAL_LEN] = {0};
    u32 indices[DSM_CAL_LEN] = {0};
    u32 short_list[DSM_CAL_LEN] = {0};
    u32 long_list[DSM_CAL_LEN] = {0};
    u32 temp_sched[DSM_CAL_LEN] = {0};

    clk_period_ps = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);
    taxi_bw = 128 * 1000000 / clk_period_ps;
    slow_mode = clk_period_ps > 2000 ? 1 : 0;
    taxi2ports(taxi, taxi_ports);

    for (i = 0; i < DSM_CAL_LEN; i++) {
        new_slots[i] = DSM_CAL_EMPTY;
        schedule[i] = DSM_CAL_EMPTY;
        temp_sched[i] = DSM_CAL_EMPTY;
    }
    // Default empty calender
    schedule[0] = DSM_CAL_MAX_DEVS_PER_TAXI;

    for (u32 p = 0; p < vtss_state->port_count; p++) {
        cal_spd = fa_cal_speed_get(vtss_state, p, &port, 0, 0);
        port_spd = calspd2int(cal_spd);
        port_speeds[port] = port_spd;
    }
    // Map ports to taxi positions
    for (u32 i = 0; i < DSM_CAL_MAX_DEVS_PER_TAXI; i++) {
        port = taxi_ports[i];
        if (port < 70) {
            taxi_speeds[i] = port_speeds[port];
        } else {
            taxi_speeds[i] = 0;
        }
    }

    for (i = 0; i < VTSS_ARRSZ(taxi_speeds); i++) {
        sum += taxi_speeds[i];
        if ((taxi_speeds[i] < min) && (taxi_speeds[i] != 0)) {
            min = taxi_speeds[i];
        }
        gcd = min;
        for (a = 0; a < VTSS_ARRSZ(taxi_speeds); a++) {
            gcd = dsm_exb_gcd(gcd, taxi_speeds[a]);
        }
    }

    if (sum == 0) {
        return VTSS_RC_OK; // Empty calender
    }
    // Make room for overhead traffic
    factor = 100 * 100 * 1000 / (100 * 100 - DSM_CAL_BW_LOSS);

    if (sum * factor > (taxi_bw * 1000)) {
        VTSS_E("Taxi bw %d Gbps, not enough for taxi %d. Req. MBps: %d\n",taxi_bw, taxi, sum);
        return VTSS_RC_ERROR;
    }
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            raw_spd = gcd/5;
        } else if (i == 1) {
            raw_spd = gcd/2;
        } else if (i == 2) {
            raw_spd = gcd;
        } else {
            raw_spd = min;
        }
        slot_spd = raw_spd * factor / 1000;
        num_of_slots = taxi_bw / slot_spd;
        if (num_of_slots <= 64) {
            break;
        }
    }

    num_of_slots = num_of_slots > 64 ? 64 : num_of_slots;
    slot_spd = taxi_bw / num_of_slots;

    sum = 0;
    for (i = 0; i < VTSS_ARRSZ(taxi_speeds); i++) {
        spd = taxi_speeds[i];
        adjusted_speed = taxi_speeds[i] * factor / 1000;
        if (adjusted_speed > 0) {
            avg_dist[i] = (128 * 1000000 * 10)/(adjusted_speed * clk_period_ps);
        } else {
            avg_dist[i] = -1;
        }
        dev_slots[i] = ((spd * factor / slot_spd) + 999) / 1000;
        if (spd != 25000 && (spd != 10000 || !slow_mode)) {
            if (num_of_slots < (5 * dev_slots[i])) {
                VTSS_E("Port spd %d taxi %d cannot not be scheduled with min. separation of 5 slots.",spd, taxi);
                return VTSS_RC_ERROR;
            }
        }
        sum += dev_slots[i];
        if (sum > num_of_slots) {
            VTSS_E("Could not schedule taxi %d with overhead factor %d.\n",taxi, factor);
            return VTSS_RC_ERROR;
        }
    }

    empty_slots = num_of_slots - sum;

    for (i = 0; i < empty_slots; i++) {
        schedule[i] = DSM_CAL_MAX_DEVS_PER_TAXI;
    }

    for (i = 1; i < num_of_slots; i++) {
        indices_len = 0;
        for (a = 0; a < VTSS_ARRSZ(dev_slots); a++) {
            if (dev_slots[a] == i) {
                indices[indices_len] = a;
                indices_len++;
            }
        }
        if (indices_len == 0) {
            continue;
        }
        k = 0;
        for (a = 0; a < i; a++) {
            for (u32 j = 0; j < indices_len; j++, k++) {
                new_slots[k] = indices[j];
            }
        }

        for (a = 0; a < DSM_CAL_LEN; a++) {
            if (schedule[a] == DSM_CAL_EMPTY)
                break;
        }

        num_of_old_slots =  a;
        num_of_new_slots =  k;
        cnt = 0;
        ts = 0;

        if (num_of_new_slots > num_of_old_slots) {
            VTSS_MEMCPY(short_list, schedule, sizeof(short_list));
            VTSS_MEMCPY(long_list, new_slots, sizeof(long_list));
            tgt_score = 100000 * num_of_old_slots / num_of_new_slots;
        } else {
            VTSS_MEMCPY(short_list, new_slots, sizeof(short_list));
            VTSS_MEMCPY(long_list, schedule, sizeof(long_list));
            tgt_score = 100000 * num_of_new_slots / num_of_old_slots;
        }

        while(dsm_cal_len(short_list) > 0 || dsm_cal_len(long_list) > 0) {
            act = 0;
            if (dsm_cal_len(short_list) > 0) {
                temp_sched[ts] = dsm_cp_cal(short_list);
                ts++;
                cnt += 100000;
                act = 1;
            }
            while (dsm_cal_len(long_list) > 0 && cnt > 0) {
                temp_sched[ts] = dsm_cp_cal(long_list);
                ts++;
                cnt -= tgt_score;
                act = 1;
            }
            if (act == 0) {
                VTSS_E("Error in DSM calculation");
                return VTSS_RC_ERROR;
            }
        }

        for (a = 0; a < DSM_CAL_LEN; a++) {
            if (temp_sched[a] == DSM_CAL_EMPTY) {
                break;
            }
        }
        for (a = 0; a < DSM_CAL_LEN; a++) {
            schedule[a] = temp_sched[a];
            temp_sched[a] = DSM_CAL_EMPTY;
            new_slots[a] = DSM_CAL_EMPTY;
        }
    }

    return VTSS_RC_OK;
}

// Dump the dsm taxi calender
vtss_rc vtss_fa_dsm_cal_debug(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr)
{
    u32 len, val, port;
    u32 taxi_ports[DSM_CAL_MAX_DEVS_PER_TAXI] = {0};

    for (u32 taxi = 0; taxi < DSM_CAL_TAXIS; taxi++) {
        taxi2ports(taxi, taxi_ports);
        REG_RD(VTSS_DSM_TAXI_CAL_CFG(taxi), &len);
        len = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_LEN(len) + 1;
        pr("Taxi:%d, Len:%d:\n",taxi, len);
        for (u32 i = 0; i < len; i++) {
            REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
                    VTSS_F_DSM_TAXI_CAL_CFG_CAL_IDX(i),
                    VTSS_M_DSM_TAXI_CAL_CFG_CAL_IDX);
            REG_RD(VTSS_DSM_TAXI_CAL_CFG(taxi), &val);
            val = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_VAL(val);
            if (val < DSM_CAL_MAX_DEVS_PER_TAXI) {
                port = taxi_ports[val];
                pr(" %d ",port);
            } else {
                pr(" - ");
            }

            if ((i > 0 && (i % 16 == 0)) || (i == len - 1)) {
                pr("\n");
            }
        }
    }
    return VTSS_RC_OK;
}

// Dump the auto calender
vtss_rc vtss_fa_cell_cal_debug(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr)
{
    u32 cal, bw = 0, this_bw = 0, val;
    fa_cal_speed_t spd;

    for (u32 port = 0; port < VTSS_CHIP_PORTS_ALL; port++) {
        REG_RD(VTSS_QSYS_CAL_AUTO(port/10), &cal);
        spd = (cal >> ((port % 10) * 3)) & 0x7;
        if (spd == 0) {
            continue;
        }
        pr("port:%d gets reserved spd:%s %s\n",port, cal2txt(port, spd), port == 65 ? "(CPU1)" : port == 66 ? "(CPU2)" :
           port == 67 ? "(IPMC)" : port == 68 ? "(AFI/OAM)" : port == 69 ? "(ipinip" : "");
        this_bw = (spd == FA_CAL_SPEED_1G ? 1000 : spd == FA_CAL_SPEED_2G5 ? 2500 :
                   spd == FA_CAL_SPEED_5G ? 5000 : spd == FA_CAL_SPEED_10G ? 10000 : 25000);
        if (port >= VTSS_CHIP_PORTS) {
            this_bw = this_bw/2; // Internal ports are granted half the value
        }
        bw += this_bw;
    }

    for (u32 i = 0; i < 5; i++) {
        REG_RD(VTSS_HSCH_OUTB_SHARE_ENA(i), &val);
        if (VTSS_X_HSCH_OUTB_SHARE_ENA_OUTB_SHARE_ENA(val) > 0) {
            pr("Internal port:%d gets idle traffic ",VTSS_CHIP_PORTS+i);
            if (i == 0) {
                pr("(CPU1)\n");
            } else if (i == 1) {
                pr("(CPU2)\n");
            } else if (i == 2) {
                pr("(IPMC)\n");
            } else if (i == 3) {
                pr("(AFI/OAM)\n");
            } else {
                pr("(IpinIP)\n");
            }
        }
    }

    pr("Total assigned BW:%d Mb\n",bw);
    pr("Max core BW:%d Mb\n",clock2bw(vtss_state->init_conf.core_clock.freq));

    return VTSS_RC_OK;
}


// Configure the DSM calendar based on port-map
static vtss_rc fa_dsm_calc_and_apply_calender(vtss_state_t *vtss_state)
{
    u32 calender[DSM_CAL_LEN];
    i32 avg_len[DSM_CAL_LEN];

    for (u32 taxi = 0; taxi < DSM_CAL_TAXIS; taxi++) {
        VTSS_RC(fa_dsm_calc_calender(vtss_state, taxi, calender, avg_len));
        VTSS_RC(fa_dsm_chk_calender(vtss_state, calender, avg_len));
        VTSS_RC(fa_dsm_set_calendar(vtss_state, taxi, calender));
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_restart_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_port_map_set(vtss_state_t *vtss_state)
{
    VTSS_RC(fa_calendar_auto(vtss_state));

    /* Calculate and configure the DSM calender */
    if (fa_dsm_calc_and_apply_calender(vtss_state) != VTSS_RC_OK) {
         VTSS_E("DSM Calender calc failed");
    }

    return vtss_fa_init_groups(vtss_state, VTSS_INIT_CMD_PORT_MAP);
}

vtss_rc vtss_fa_inst_create(vtss_state_t *vtss_state)
{
    /* Initialization */
    vtss_state->cil.init_conf_set    = fa_init_conf_set;
    vtss_state->cil.restart_conf_set = fa_restart_conf_set;
    vtss_state->cil.debug_info_print = fa_debug_info_print;
    vtss_state->port.map_set         = fa_port_map_set;

#if defined(VTSS_OPT_EMUL)
    VTSS_RC(vtss_fa_emul_init(vtss_state));
#endif

    /* Create function groups */
    return vtss_fa_init_groups(vtss_state, VTSS_INIT_CMD_CREATE);
}

#endif /* VTSS_ARCH_FA */
