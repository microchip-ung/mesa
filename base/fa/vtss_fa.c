/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/
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

    sprintf(buf, "%-34s", name);
    vtss_debug_print_reg_header(pr, buf);
}

static void fa_debug_reg_clr(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr, u32 addr, const char *name, BOOL clr)
{
    u32 value;
    char buf[64];

    if (vtss_fa_rd(vtss_state, addr, &value) == VTSS_RC_OK &&
        (clr == 0 || vtss_fa_wr(vtss_state, addr, value) == VTSS_RC_OK)) {
        sprintf(buf, "%-34s", name);
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

    sprintf(buf, "%s_%u", name, i);
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

    sprintf(buf, "rx_%s:", col1);
    pr("%-28s%10" PRIu64 "   ", buf, c1->value);
    if (col2 != NULL) {
        sprintf(buf, "tx_%s:", strlen(col2) ? col2 : col1);
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
    REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(idx, i * 2 + 1), &frames);
    REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(idx, i * 2), &lsb);
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
    return VTSS_RC_OK;
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
//    VTSS_RC(vtss_fa_oam_debug_print(vtss_state, pr, info));
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
//    VTSS_RC(vtss_fa_oam_init(vtss_state, cmd));
#endif

#if defined(VTSS_FEATURE_CLOCK)
    VTSS_RC(vtss_es6514_clock_init(vtss_state, cmd));
#endif

    return VTSS_RC_OK;
}

static vtss_rc fa_core_clock_config(vtss_state_t *vtss_state)
{
    u32 clk_div;
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
    case VTSS_TARGET_7558_04:
        if (f == VTSS_CORE_CLOCK_DEFAULT) {
            freq = VTSS_CORE_CLOCK_625MHZ;
        } else if (f != VTSS_CORE_CLOCK_625MHZ) {
            freq = 0; // Not supported
        }
        break;
    case VTSS_TARGET_7546_04:
        if (f == VTSS_CORE_CLOCK_DEFAULT) {
            freq = VTSS_CORE_CLOCK_625MHZ;
        }
        break;
    case VTSS_TARGET_7549_04:
    case VTSS_TARGET_7552_04:
    case VTSS_TARGET_7556_04:
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
    case VTSS_CORE_CLOCK_250MHZ: clk_div = 10; break;
    case VTSS_CORE_CLOCK_500MHZ: clk_div = 5;  break;
    case VTSS_CORE_CLOCK_625MHZ: clk_div = 4;  break;
    default:
        VTSS_E("Frequency (%d) not supported on target (%x)",f, vtss_state->create.target);
        return VTSS_RC_OK;
    }

    /* Update state with chosen frequency */
    vtss_state->init_conf.core_clock.freq = freq;

    /* Configure the LCPLL */
    REG_WRM(VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG,
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_DIV(clk_div) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_PRE_DIV(0) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_DIR(0) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_SEL(0) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_ENA(0) |
            VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_ENA(1),
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_PRE_DIV |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_DIR |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_SEL |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_ENA |
            VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_ENA);

#if 0 // TBD need info from frontend, below is copied from JR2 - TBD-BJO
    // Adapt other blocks to the new core speed
    REG_WRM(VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL,
            VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS(36),
            VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS);

    REG_WRM(VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL,
            VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS(36),
            VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS);

    REG_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG,
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT(693),
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT);

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
        {TRUE,  VTSS_VOP_RAM_INIT, 0},
        {TRUE,  VTSS_DSM_RAM_INIT, 0}};

    u32 init_cnt = (sizeof(ram_init_list)/sizeof(ram_init_list[0]));

    u32 gpio_oe, gpio_oe1, gpio_out, gpio_out1;
    /* Save GPIO state */
    REG_RD(VTSS_DEVCPU_GCB_GPIO_OE, &gpio_oe);
    REG_RD(VTSS_DEVCPU_GCB_GPIO_OE1, &gpio_oe1);
    REG_RD(VTSS_DEVCPU_GCB_GPIO_OUT, &gpio_out);
    REG_RD(VTSS_DEVCPU_GCB_GPIO_OUT1, &gpio_out1);
    /* Reset switch core only, protect the Serdes and Vcore */
#if !defined(VTSS_OPT_EMUL)
    VTSS_I("Resetting switch core..");
    REG_WRM(VTSS_CPU_RESET_PROT_STAT,
            VTSS_F_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE(1),
            VTSS_M_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE);
#endif
    REG_WRM(VTSS_DEVCPU_GCB_SOFT_RST,
            VTSS_F_DEVCPU_GCB_SOFT_RST_SOFT_SWC_RST(1),
            VTSS_M_DEVCPU_GCB_SOFT_RST_SOFT_SWC_RST);
    for (i=0; ; i++) {
        REG_RD(VTSS_DEVCPU_GCB_SOFT_RST, &value);
        if (value & VTSS_M_DEVCPU_GCB_SOFT_RST_SOFT_SWC_RST) {
            VTSS_MSLEEP(1);
        } else {
            break;
        }
        if (i == 100) {
            VTSS_E("Switch core reset failed");
            return VTSS_RC_ERROR;
        }
    }

    /* Restore GPIO state */
#define NZ_RESTORE(r, v) do { if (v) { REG_WR(r, v); } } while(0)
    NZ_RESTORE(VTSS_DEVCPU_GCB_GPIO_OUT, gpio_out);
    NZ_RESTORE(VTSS_DEVCPU_GCB_GPIO_OUT1, gpio_out1);
    NZ_RESTORE(VTSS_DEVCPU_GCB_GPIO_OE, gpio_oe);
    NZ_RESTORE(VTSS_DEVCPU_GCB_GPIO_OE1, gpio_oe1);
#undef NZ_RESTORE

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
                    REG_WRM_SET(r.init_reg, r.init_val);
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
    u32 value, i;
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
        // Internal ports
        *port = (VTSS_CHIP_PORT_CPU + port_no - VTSS_PORTS);
        if (port_no == VTSS_CHIP_PORT_CPU_0 || port_no == VTSS_CHIP_PORT_CPU_1) {
            return FA_CAL_SPEED_2G5; // Equals 1.25G
        } else if (port_no == VTSS_CHIP_PORT_VD0) {
            return FA_CAL_SPEED_2G5; // IPMC, equals 1.25G
        } else if (port_no == VTSS_CHIP_PORT_VD1) {
            if (max_bw - used_bw >= 25000) {
                return FA_CAL_SPEED_25G; // OAM equals 12.5G
            } else if (max_bw - used_bw >= 10000) {
                return FA_CAL_SPEED_10G; // OAM equals 5G
            } else {
                return FA_CAL_SPEED_5G;  // OAM equals 2G5
            }
        } else {
            // IPinIP gets only idle BW
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

// Auto configure the calendar based on port-map
static vtss_rc fa_calendar_auto(vtss_state_t *vtss_state)
{
    u32                cal[7], value;
    fa_cal_speed_t     spd;
    u32                i;
    vtss_port_no_t     port_no;
    i32                port, this_bw, max_bw, bw = 0;

    VTSS_I("Using Auto calendar");

    if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_250MHZ) {
        max_bw = 83000; /* 250000 / 3 */
    } else if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_500MHZ) {
        max_bw = 166000; /* 500000 / 3 */
    } else if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_625MHZ) {
        max_bw = 208000; /* 625000 / 3 */
    } else {
        VTSS_E("Core clock not supported");
        return VTSS_RC_ERROR;
    }

    // Setup the calendar, i.e. the BW to each device
    memset(cal, 0, sizeof(cal));
    for (port_no = 0; port_no < VTSS_CHIP_PORTS_ALL; port_no++) {
        spd = fa_cal_speed_get(vtss_state, port_no, &port, bw, max_bw);
        if (port == CHIP_PORT_UNUSED || spd == FA_CAL_SPEED_NONE) {
            continue;
        }

        this_bw = (spd == FA_CAL_SPEED_1G ? 1000 : spd == FA_CAL_SPEED_2G5 ? 2500 :
                   spd == FA_CAL_SPEED_5G ? 5000 : spd == FA_CAL_SPEED_10G ? 10000 : 25000);
        if (port_no >= VTSS_PORTS) {
            this_bw = this_bw/2; // Internal ports are granted half the value
        }
        bw += this_bw;
        VTSS_D("chip_port = %u, this_bw = %u, summed bw = %u", port, this_bw, bw);
        cal[port/10] += (spd << ((port % 10) * 3));
    }

    if (bw > max_bw) {
        VTSS_E("The configured BW (%d) is above limit (%d)",bw,max_bw);
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

static vtss_rc fa_restart_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_port_map_set(vtss_state_t *vtss_state)
{
    VTSS_RC(fa_calendar_auto(vtss_state));
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
