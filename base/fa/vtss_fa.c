// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)

#if defined(VTSS_FEATURE_CLOCK)
#include "../omega/vtss_omega_clock_cil.h"
#endif

// Various defines needed to calculate the DSM calendar for LAN969x.
#define DEV_10G_IDX   0
#define DEV_5G_IDX    1
#define DEV_2G5_IDX   2
#define DEV_OTHER_IDX 3 // 1G or less
#define DEV_IDX_CNT   4

#define SPEED2IDX(speed) (speed == 10000 ? DEV_10G_IDX : speed == 5000 ? DEV_5G_IDX : speed == 2500 ? DEV_2G5_IDX : DEV_OTHER_IDX)
#define IDX2SPEED(idx)   (idx == DEV_10G_IDX ? 10000 : idx == DEV_5G_IDX ? 5000 : idx == DEV_2G5_IDX ? 2500 : 1000)

// We use two different values in the calendar for unused slots: One for slots
// that are unused because of the requirement of unused slots for the interlink
// device (TAXI_SLOT_UNUSED_BUT_LOCKED) and one for unused and free to use slots
// (UNUSED).
#define TAXI_SLOT_UNUSED            RT_DSM_CAL_MAX_DEVS_PER_TAXI
#define TAXI_SLOT_UNUSED_BUT_LOCKED (TAXI_SLOT_UNUSED + 1) // It's OK to use a value greater than the max, because it gives the same when writing

void vtss_fa_reg_error(const char *file, int line, char *txt) {
#if VTSS_OPT_TRACE
    vtss_callout_trace_printf(VTSS_TRACE_LAYER, VTSS_TRACE_GROUP_DEFAULT,
                              VTSS_TRACE_LEVEL_ERROR, file, line, file, txt);
#endif
}

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

#if VTSS_OPT_DEBUG_PRINT
void vtss_fa_debug_print_port_header(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr, const char *txt)
{
    vtss_debug_print_port_header(vtss_state, pr, txt, RT_CHIP_PORTS, 1);
}

void vtss_fa_debug_print_pmask(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, vtss_port_mask_t *pmask)
{
    u32 port;

    for (port = 0; port < RT_CHIP_PORTS; port++) {
        pr("%s%u", port == 0 || (port & 7) ? "" : ".", pmask->m[port / 32] & VTSS_BIT(port % 32) ? 1 : 0);
    }
    pr("\n");
}

void vtss_fa_debug_print_reg_header(const vtss_debug_printf_t pr, const char *name)
{
    pr("%-43s  31    24.23    16.15     8.7      0 Hex\n", name);
}


void vtss_fa_debug_reg_header(const vtss_debug_printf_t pr, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%-34s", name);
    vtss_fa_debug_print_reg_header(pr, buf);
}

static void fa_debug_reg_clr(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr, u32 addr, const char *name, BOOL clr)
{
    u32 value;
    char buf[100];

    if (vtss_fa_rd(vtss_state, addr, &value) == VTSS_RC_OK &&
        (clr == 0 || vtss_fa_wr(vtss_state, addr, value) == VTSS_RC_OK)) {
        VTSS_SPRINTF(buf, "%-32s  0x%07x", name, addr);
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
#endif

#if defined(VTSS_ARCH_LAN969X)
/* Read or write register indirectly */
static vtss_rc lag_reg_indirect_access(vtss_state_t *vtss_state,
                                       u32 addr, u32 *value, BOOL is_write)
{
    u32 ctrl;
    vtss_rc result;

    /* The @addr is an address suitable for the read or write callout function installed by
     * the application, i.e. it's a 32-bit address suitable for presentation on a PI
     * address bus, i.e. it's not suitable for presentation on the VCore-III shared bus.
     * In order to make it suitable for presentation on the VCore-III shared bus, it must
     * be made an 8-bit address, so we multiply by 4, and it must be offset by the base
     * address of the switch core registers, so we add VTSS_IO_ORIGIN1_OFFSET.
     */

    if ((result = vtss_fa_wr(vtss_state, REG_ADDR(VTSS_DEVCPU_GCB_VA_ADDR), addr)) != VTSS_RC_OK) {
        goto do_exit;
    }
    if (is_write) {
        if ((result = vtss_fa_wr(vtss_state, REG_ADDR(VTSS_DEVCPU_GCB_VA_DATA), *value)) != VTSS_RC_OK) {
            goto do_exit;
        }
        // Wait for operation to complete
        do {
            if ((result = vtss_fa_rd(vtss_state, REG_ADDR(VTSS_DEVCPU_GCB_VA_CTRL), &ctrl)) != VTSS_RC_OK) {
                goto do_exit;
            }
        } while (ctrl & VTSS_M_DEVCPU_GCB_VA_CTRL_VA_BUSY);
    } else {
        // Dummy read to initiate access
        if ((result = vtss_fa_rd(vtss_state, REG_ADDR(VTSS_DEVCPU_GCB_VA_DATA), value)) != VTSS_RC_OK) {
            goto do_exit;
        }
        // Wait for operation to complete
        do {
            if ((result = vtss_fa_rd(vtss_state, REG_ADDR(VTSS_DEVCPU_GCB_VA_CTRL), &ctrl)) != VTSS_RC_OK) {
                goto do_exit;
            }
        } while (ctrl & VTSS_M_DEVCPU_GCB_VA_CTRL_VA_BUSY);
        if ((result = vtss_fa_rd(vtss_state, REG_ADDR(VTSS_DEVCPU_GCB_VA_DATA), value)) != VTSS_RC_OK) {
            goto do_exit;
        }
    }

do_exit:
    return result;
}
#endif

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

vtss_rc vtss_cil_l2_isdx_update(vtss_state_t *vtss_state, vtss_sdx_entry_t *sdx)
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

#endif /* VTSS_SDX_CNT */

// Return clk period in NS
u32 vtss_fa_clk_period(vtss_core_clock_freq_t clock)
{
    switch (clock) {
    case VTSS_CORE_CLOCK_180MHZ: return 5564;
    case VTSS_CORE_CLOCK_250MHZ: return 4000;
    case VTSS_CORE_CLOCK_328MHZ: return 3047;
    case VTSS_CORE_CLOCK_500MHZ: return 2000;
    case VTSS_CORE_CLOCK_625MHZ:
    default: {};
    }
    return 1600; // Default
}

BOOL fa_is_target(vtss_state_t *vtss_state)
{
    switch (vtss_state->create.target) {
    case VTSS_TARGET_7546:
    case VTSS_TARGET_7549:
    case VTSS_TARGET_7552:
    case VTSS_TARGET_7556:
    case VTSS_TARGET_7558:
    case VTSS_TARGET_7546TSN:
    case VTSS_TARGET_7549TSN:
    case VTSS_TARGET_7552TSN:
    case VTSS_TARGET_7556TSN:
    case VTSS_TARGET_7558TSN:
        return TRUE;
    default:
        return FALSE;
    }
}

/* ================================================================= *
 *  Debug print utility functions
 * ================================================================= */

#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_cil_debug_info_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_fa_misc_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_fa_port_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_fa_l2_debug_print(vtss_state, pr, info));
#if defined(VTSS_FEATURE_LAYER3)
    VTSS_RC(vtss_fa_l3_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_LAYER3 */
#if defined(VTSS_FEATURE_IS2)
    VTSS_RC(vtss_fa_vcap_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_IS2 */
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
#if defined(VTSS_FEATURE_MRP)
    VTSS_RC(vtss_lan969x_mrp_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_MRP */
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
#endif

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

#if defined(VTSS_FEATURE_MRP)
    VTSS_RC(vtss_lan969x_mrp_init(vtss_state, cmd));
#endif

#if defined(VTSS_FEATURE_CLOCK)
    VTSS_RC(vtss_es6514_clock_init(vtss_state, cmd));
#endif
    return VTSS_RC_OK;
}

static u32 fa_target_bw(vtss_state_t *vtss_state)
{
    switch (vtss_state->create.target) {
    // Fireant:
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
    // Laguna:
    case VTSS_TARGET_LAN9691VAO:
        return 46000;
    case VTSS_TARGET_LAN9694RED:
    case VTSS_TARGET_LAN9694TSN:
    case VTSS_TARGET_LAN9694:
        return 48000;
    case VTSS_TARGET_LAN9696RED:
    case VTSS_TARGET_LAN9696TSN:
    case VTSS_TARGET_LAN9692VAO:
    case VTSS_TARGET_LAN9696:
        return 66000;
    case VTSS_TARGET_LAN9698RED:
    case VTSS_TARGET_LAN9698TSN:
    case VTSS_TARGET_LAN9693VAO:
    case VTSS_TARGET_LAN9698:
        return 102000;

    default: {}
    }
    return 0;
}

#if defined(VTSS_ARCH_LAN969X)
static vtss_rc fa_core_ref_clk_config(vtss_state_t *vtss_state)
{
    vtss_core_ref_clk_t r_freq = vtss_state->init_conf.core_clock.ref_freq;
    vtss_core_clock_freq_t c_freq = vtss_state->init_conf.core_clock.freq;
    u32 val, poll_cnt = 0, clk_sel = 0, divr = 0, divq = 0, divfi = 0, divff = 0;

    if (r_freq == VTSS_CORE_REF_CLK_25MHZ &&
        c_freq == VTSS_CORE_CLOCK_328MHZ) {
        divfi = 64;
        divq = 10;
        divff = 10707062;
        clk_sel = 2;
        divr = 3;
    } else if (r_freq == VTSS_CORE_REF_CLK_39MHZ &&
               c_freq == VTSS_CORE_CLOCK_328MHZ) {
        divfi = 72;
        divq = 10;
        divff = 8635233;
        clk_sel = 1;
        divr = 6;
    } else if (r_freq == VTSS_CORE_REF_CLK_25MHZ &&
               c_freq == VTSS_CORE_CLOCK_180MHZ) {
        divfi = 70;
        divq = 20;
        divff = 14922442;
        clk_sel = 2;
        divr = 3;
    } else if (r_freq == VTSS_CORE_REF_CLK_39MHZ &&
               c_freq == VTSS_CORE_CLOCK_180MHZ) {
        divfi = 79;
        divq = 20;
        divff = 8660072;
        clk_sel = 1;
        divr = 6;
    } else {
        VTSS_E("Clock config not supported");
        return VTSS_RC_ERROR;
    }
    REG_WRM(VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG,
            VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_BYPASS_ENA(1),
            VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_BYPASS_ENA);

    REG_WRM(VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG,
            VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFI(divfi) |
            VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFF(divff),
            VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFI |
            VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFF);

    REG_WRM(VTSS_CHIP_TOP_SPARE_PLL_CFG,
            VTSS_F_CHIP_TOP_SPARE_PLL_CFG_REF_CLK_SEL(clk_sel) |
            VTSS_F_CHIP_TOP_SPARE_PLL_CFG_DIVQ(divq) |
            VTSS_F_CHIP_TOP_SPARE_PLL_CFG_DIVR(divr),
            VTSS_M_CHIP_TOP_SPARE_PLL_CFG_REF_CLK_SEL |
            VTSS_M_CHIP_TOP_SPARE_PLL_CFG_DIVQ |
            VTSS_M_CHIP_TOP_SPARE_PLL_CFG_DIVR);

    REG_WRM(VTSS_CHIP_TOP_SPARE_PLL_CFG,
            VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ENA_CFG(1),
            VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ENA_CFG);

    REG_WRM(VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG,
            VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_BYPASS_ENA(0),
            VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_BYPASS_ENA);

    // Verify PLL lock
    poll_cnt = 0;
    while(1) {
        VTSS_NSLEEP(10000); // 10usec
        REG_RD(VTSS_CHIP_TOP_SPARE_PLL_CFG, &val);
        if (VTSS_X_CHIP_TOP_SPARE_PLL_CFG_LOCK_STAT(val)) {
            break;
        }
        poll_cnt++;
        if (poll_cnt > 100) {
            VTSS_E("Spare PLL could not get into lock");
            break;
        }
    }
    // Shift to use spare PLL for core clock
    REG_WRM(VTSS_CHIP_TOP_SPARE_PLL_CFG,
            VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE(1),
            VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE);

    //
    // Now configure Core PLL identically and switch back to it
    //
    REG_WRM(VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG,
            VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_BYPASS_ENA(1),
            VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_BYPASS_ENA);

    REG_WRM(VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG,
            VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFI(divfi) |
            VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFF(divff),
            VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFI |
            VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFF);

    REG_WRM(VTSS_CHIP_TOP_CORE_PLL_CFG,
            VTSS_F_CHIP_TOP_CORE_PLL_CFG_REF_CLK_SEL(clk_sel) |
            VTSS_F_CHIP_TOP_CORE_PLL_CFG_DIVQ(divq) |
            VTSS_F_CHIP_TOP_CORE_PLL_CFG_DIVR(divr),
            VTSS_M_CHIP_TOP_CORE_PLL_CFG_REF_CLK_SEL |
            VTSS_M_CHIP_TOP_CORE_PLL_CFG_DIVQ |
            VTSS_M_CHIP_TOP_CORE_PLL_CFG_DIVR);

    REG_WRM(VTSS_CHIP_TOP_CORE_PLL_CFG,
            VTSS_F_CHIP_TOP_CORE_PLL_CFG_ENA_CFG(1),
            VTSS_M_CHIP_TOP_CORE_PLL_CFG_ENA_CFG);

    REG_WRM(VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG,
            VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_BYPASS_ENA(0),
            VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_BYPASS_ENA);

    // Verify PLL lock
    poll_cnt = 0;
    while(1) {
        VTSS_NSLEEP(10000); // 10usec
        REG_RD(VTSS_CHIP_TOP_CORE_PLL_CFG, &val);
        if (VTSS_X_CHIP_TOP_CORE_PLL_CFG_LOCK_STAT(val)) {
            break;
        }
        poll_cnt++;
        if (poll_cnt > 100) {
            VTSS_E("Core PLL could not get into lock");
            break;
        }
    }

    REG_WRM(VTSS_CHIP_TOP_SPARE_PLL_CFG,
            VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE(0),
            VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE);

    return VTSS_RC_OK;
}
#endif

static vtss_rc fa_core_clock_config(vtss_state_t *vtss_state)
{
    vtss_core_clock_freq_t freq, f = vtss_state->init_conf.core_clock.freq;
    freq = f;
    u32 clk_period, pol_upd_int, val;

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
    case VTSS_TARGET_LAN9694RED:
    case VTSS_TARGET_LAN9694TSN:
    case VTSS_TARGET_LAN9691VAO:
    case VTSS_TARGET_LAN9694:
    case VTSS_TARGET_LAN9696RED:
    case VTSS_TARGET_LAN9696TSN:
    case VTSS_TARGET_LAN9692VAO:
    case VTSS_TARGET_LAN9696:
    case VTSS_TARGET_LAN9698RED:
    case VTSS_TARGET_LAN9698TSN:
    case VTSS_TARGET_LAN9693VAO:
    case VTSS_TARGET_LAN9698:
        if (f == VTSS_CORE_CLOCK_DEFAULT) {
            freq = VTSS_CORE_CLOCK_328MHZ; // Default laguna clock
        } else if (f != VTSS_CORE_CLOCK_328MHZ) {
            VTSS_E("Frequency (%d) not supported",f);
            freq = 0; // Not supported
        }
        break;

    default:
        VTSS_E("Target (%x) not supported",vtss_state->create.target);
        return VTSS_RC_ERROR;
    }

    /* Update state with chosen frequency */
    vtss_state->init_conf.core_clock.freq = freq;

#if defined(VTSS_ARCH_SPARX5)
    {
        u32 clk_div;

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
    }
#else
    {
        // Laguna only: Configure REF+CORE PLLs
        // If VTSS_CORE_REF_CLK_DEFAULT then pin strappings controls the Ref clock
        // with: 0 = 25Mhz, 1 = 39Mh
        if (vtss_state->init_conf.core_clock.ref_freq == VTSS_CORE_REF_CLK_DEFAULT) {
            REG_RD(VTSS_CHIP_TOP_HW_STAT, &val);
            if (VTSS_X_CHIP_TOP_HW_STAT_REFCLK_SEL(val) == 1) {
                vtss_state->init_conf.core_clock.ref_freq = VTSS_CORE_REF_CLK_39MHZ;
            } else {
                vtss_state->init_conf.core_clock.ref_freq = VTSS_CORE_REF_CLK_25MHZ;
            }
        }
        VTSS_RC(fa_core_ref_clk_config(vtss_state));

        pol_upd_int = 820; // Laguna default

        REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG,
                VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(0),
                VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA);

        // Time of day clock configuration (is re-written in TS module)
        // CLK_PERIOD * 2^27 / 1000 = 409095634
        REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(0, 1), 409095634);
        REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG,
                VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(1),
                VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA);
    }
#endif

    clk_period = vtss_fa_clk_period(freq);
    val = (clk_period / 100);

#if defined(VTSS_ARCH_SPARX5)
    REG_WRM(VTSS_HSCH_SYS_CLK_PER,
            VTSS_F_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS(val),
            VTSS_M_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS);
#endif

    REG_WRM(VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL,
            VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS(val),
            VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS);

    REG_WRM(VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL,
            VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS(val),
            VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS);

    REG_WRM(VTSS_LRN_AUTOAGE_CFG_1,
            VTSS_F_LRN_AUTOAGE_CFG_1_CLK_PERIOD_01NS(val),
            VTSS_M_LRN_AUTOAGE_CFG_1_CLK_PERIOD_01NS);

#if defined(VTSS_ARCH_SPARX5)
    for(u8 i = 0; i < 3; i++) {
        REG_WRM(VTSS_DEVCPU_GCB_SIO_CLOCK(i),
                VTSS_F_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD(val),
                VTSS_M_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD);
    }
#else
    REG_WRM(VTSS_DEVCPU_GCB_SIO_CLOCK,
            VTSS_F_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD(val),
            VTSS_M_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD);
#endif

    REG_WRM(VTSS_HSCH_TAS_STATEMACHINE_CFG,
            VTSS_F_HSCH_TAS_STATEMACHINE_CFG_REVISIT_DLY((256 * 1000) / clk_period),
            VTSS_M_HSCH_TAS_STATEMACHINE_CFG_REVISIT_DLY);

    REG_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG,
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT(pol_upd_int),
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT);
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
        {FALSE, REG_ADDR(VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET),
         VTSS_M_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET_RESET},
        {FALSE, REG_ADDR(VTSS_ASM_STAT_CFG), VTSS_M_ASM_STAT_CFG_STAT_CNT_CLR_SHOT},
        {TRUE,  REG_ADDR(VTSS_QSYS_RAM_INIT), 0},
        {TRUE,  REG_ADDR(VTSS_REW_RAM_INIT), 0},
        {TRUE,  REG_ADDR(VTSS_VOP_RAM_INIT), 0},
        {TRUE,  REG_ADDR(VTSS_ANA_AC_RAM_CTRL_RAM_INIT), 0},
        {TRUE,  REG_ADDR(VTSS_ASM_RAM_INIT), 0},
        {TRUE,  REG_ADDR(VTSS_EACL_RAM_INIT), 0},
        {TRUE,  REG_ADDR(VTSS_VCAP_SUPER_RAM_INIT), 0},
        {TRUE,  REG_ADDR(VTSS_DSM_RAM_INIT), 0}};

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
                        vtss_fa_wr(vtss_state, r.init_reg, r.init_val);
                    } else {
                        vtss_fa_wrm(vtss_state, r.init_reg, r.init_val, r.init_val);
                    }
                } else {
                    vtss_fa_rd(vtss_state, r.init_reg, &value);
                    if ((value & r.init_val) != r.init_val) {
                        pending--;
                    }
                }
            }
            if (!pending) {
                break;
            }
            VTSS_NSLEEP(100000);
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

static vtss_rc vtss_fa_verify_target(vtss_state_t *vtss_state)
{
#if defined(VTSS_ARCH_SPARX5)
    return VTSS_RC_OK;
#else
    u32 chip_id = vtss_state->misc.chip_id.part_number;

    switch (vtss_state->create.target) {
    case VTSS_TARGET_LAN9698RED: // Laguna-100-RED
        if (chip_id == VTSS_TARGET_LAN9698RED) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9696RED: // Laguna-60-RED
        if (chip_id == VTSS_TARGET_LAN9696RED ||
            chip_id == VTSS_TARGET_LAN9698RED) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9694RED: // Laguna-40-RED
        if (chip_id == VTSS_TARGET_LAN9694RED ||
            chip_id == VTSS_TARGET_LAN9696RED ||
            chip_id == VTSS_TARGET_LAN9698RED) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9698TSN: // Laguna-100-TSN
        if (chip_id == VTSS_TARGET_LAN9698TSN ||
            chip_id == VTSS_TARGET_LAN9698RED) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9696TSN: // Laguna-60-TSN
        if (chip_id == VTSS_TARGET_LAN9696TSN ||
            chip_id == VTSS_TARGET_LAN9698TSN ||
            chip_id == VTSS_TARGET_LAN9696RED ||
            chip_id == VTSS_TARGET_LAN9698RED) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9694TSN: // Laguna-40-TSN
        if (chip_id == VTSS_TARGET_LAN9694TSN ||
            chip_id == VTSS_TARGET_LAN9696TSN ||
            chip_id == VTSS_TARGET_LAN9698TSN ||
            chip_id == VTSS_TARGET_LAN9694RED ||
            chip_id == VTSS_TARGET_LAN9696RED ||
            chip_id == VTSS_TARGET_LAN9698RED) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9693VAO: // Laguna-100-VAO
        if (chip_id == VTSS_TARGET_LAN9693VAO ||
            chip_id == VTSS_TARGET_LAN9698RED ||
            chip_id == VTSS_TARGET_LAN9698TSN) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9692VAO: // Laguna-65-VAO
        if (chip_id == VTSS_TARGET_LAN9692VAO ||
            chip_id == VTSS_TARGET_LAN9693VAO ||
            chip_id == VTSS_TARGET_LAN9696RED ||
            chip_id == VTSS_TARGET_LAN9698RED ||
            chip_id == VTSS_TARGET_LAN9696TSN ||
            chip_id == VTSS_TARGET_LAN9698TSN) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9691VAO: // Laguna-40-VAO
        if (chip_id == VTSS_TARGET_LAN9691VAO ||
            chip_id == VTSS_TARGET_LAN9692VAO ||
            chip_id == VTSS_TARGET_LAN9693VAO ||
            chip_id == VTSS_TARGET_LAN9694TSN ||
            chip_id == VTSS_TARGET_LAN9696TSN ||
            chip_id == VTSS_TARGET_LAN9698TSN ||
            chip_id == VTSS_TARGET_LAN9694RED ||
            chip_id == VTSS_TARGET_LAN9696RED ||
            chip_id == VTSS_TARGET_LAN9698RED) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9698: // Laguna-100
        if (chip_id == VTSS_TARGET_LAN9698 ||
            chip_id == VTSS_TARGET_LAN9693VAO ||
            chip_id == VTSS_TARGET_LAN9698RED ||
            chip_id == VTSS_TARGET_LAN9698TSN) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9696: // Laguna-60
        if (chip_id == VTSS_TARGET_LAN9696 ||
            chip_id == VTSS_TARGET_LAN9698 ||
            chip_id == VTSS_TARGET_LAN9692VAO ||
            chip_id == VTSS_TARGET_LAN9693VAO ||
            chip_id == VTSS_TARGET_LAN9696RED ||
            chip_id == VTSS_TARGET_LAN9698RED ||
            chip_id == VTSS_TARGET_LAN9696TSN ||
            chip_id == VTSS_TARGET_LAN9698TSN) {
            return VTSS_RC_OK;
        }
        goto err_exit;
    case VTSS_TARGET_LAN9694: // Laguna-40
        return VTSS_RC_OK;
    default:
        VTSS_E("Target (%x) not supported",vtss_state->create.target);
        return VTSS_RC_ERROR;
    }

err_exit:
    VTSS_E("Chip:'0x%x' does not support the target:'0x%x'",chip_id, vtss_state->create.target);
    return VTSS_RC_ERROR;
#endif
}

vtss_rc vtss_cil_init_conf_set(vtss_state_t *vtss_state)
{
    u32 i;

    VTSS_PROF_ENTER(LM_PROF_ID_MESA_INIT, 1);
    // Reset switch core if using SPI from external CPU
    VTSS_PROF_ENTER(LM_PROF_ID_MESA_INIT, 2);
#if defined(VTSS_ARCH_LAN969X)
    if (vtss_state->init_conf.spi_bus) {
        REG_WR(VTSS_DEVCPU_GCB_SOFT_RST, VTSS_F_DEVCPU_GCB_SOFT_RST_SOFT_SWC_RST(1));
        VTSS_MSLEEP(100);
        u32 val = 0;
        lag_reg_indirect_access(vtss_state, 0xE00C008C, &val, 1);
    }
#endif

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
    for (i = RT_CHIP_PORTS; i < RT_CHIP_PORTS_ALL; i++) {
        REG_WRM_SET(VTSS_QFWD_SWITCH_PORT_MODE(i),
                    VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA);
    }
    VTSS_PROF_EXIT(LM_PROF_ID_MESA_INIT, 2);

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

    /* Compare API target with chip part number */
    VTSS_RC(vtss_fa_verify_target(vtss_state));

    /* Initialize function groups */
    VTSS_RC(vtss_fa_init_groups(vtss_state, VTSS_INIT_CMD_INIT));
    VTSS_PROF_EXIT(LM_PROF_ID_MESA_INIT, 1);
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

    if (port_no >= RT_CHIP_PORTS) {
        // Internal ports
        *port = (RT_CHIP_PORT_CPU + port_no - RT_CHIP_PORTS);
        if (port_no == RT_CHIP_PORT_CPU_0 || port_no == RT_CHIP_PORT_CPU_1) {
            return FA_CAL_SPEED_2G5; // Equals 1.25G
        } else if (port_no == RT_CHIP_PORT_VD0) {
            // IPMC only idle BW
            return FA_CAL_SPEED_NONE;
        } else if (port_no == RT_CHIP_PORT_VD1) {
#if defined(VTSS_ARCH_SPARX5)
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
#else
            return FA_CAL_SPEED_NONE; // OAM idles only
#endif
        } else if (port_no == RT_CHIP_PORT_VD2) {
            // IPinIP gets only idle BW
            return FA_CAL_SPEED_NONE;
        } else {
            // Unknown internal port
            return FA_CAL_SPEED_NONE;
        }
    }

    if (port_no >= VTSS_PORTS) {
        // Switch port outside port map
        *port = CHIP_PORT_UNUSED;
        return FA_CAL_SPEED_NONE;
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
    case VTSS_BW_NONE: return FA_CAL_SPEED_NONE;
    case VTSS_BW_UNDEFINED:
        default:
            VTSS_E("port_no = %u (chip_port = %u): In the port map, but with undefined B/W ().", port_no, *port);
            break;
    }

    return FA_CAL_SPEED_NONE;
}

static i32 clock2bw(vtss_core_clock_freq_t freq) {
    if (freq == VTSS_CORE_CLOCK_250MHZ) {
        return 83000; /* 250000 / 3 = 83Gb */
    } else if (freq == VTSS_CORE_CLOCK_328MHZ) {
        return 109375; /* 328125 / 3 = 109Gb */
    } else if (freq == VTSS_CORE_CLOCK_500MHZ) {
        return 166000; /* 500000 / 3 = 166Gb */
    } else if (freq == VTSS_CORE_CLOCK_625MHZ) {
        return  208000; /* 625000 / 3 = 208Gb */
    } else {
        VTSS_E("Core clock not supported");
    }
    return 0;
}

static vtss_internal_bw_t cal2bw(fa_cal_speed_t cal_spd) {
    switch (cal_spd) {
    case FA_CAL_SPEED_1G:   return VTSS_BW_1G;
    case FA_CAL_SPEED_2G5:  return VTSS_BW_2G5;
    case FA_CAL_SPEED_5G:   return VTSS_BW_5G;
    case FA_CAL_SPEED_10G:  return VTSS_BW_10G;
    case FA_CAL_SPEED_25G:  return VTSS_BW_25G;
    case FA_CAL_SPEED_NONE: return VTSS_BW_NONE;
    }
    return VTSS_BW_NONE;
}

// Auto configure the calendar based on port-map
vtss_rc fa_cell_calendar_auto(vtss_state_t *vtss_state)
{
    u32                cal[7], value;
    fa_cal_speed_t     spd;
    u32                i;
    vtss_port_no_t     port_no;
    i32                port, this_bw, max_core_bw, bw = 0, port_bw = 0;
    u32                replicator = fa_is_target(vtss_state) ? 7 : 4;

    VTSS_I("Using Auto calendar");
    max_core_bw = clock2bw(vtss_state->init_conf.core_clock.freq);
    // Setup the calendar, i.e. the BW to each device
    VTSS_MEMSET(cal, 0, sizeof(cal));
    for (port_no = 0; port_no < RT_CHIP_PORTS_ALL; port_no++) {
        spd = fa_cal_speed_get(vtss_state, port_no, &port, bw, max_core_bw);
        if (port == CHIP_PORT_UNUSED || spd == FA_CAL_SPEED_NONE) {
            continue;
        }
        this_bw = (spd == FA_CAL_SPEED_1G ? 1000 : spd == FA_CAL_SPEED_2G5 ? 2500 :
                   spd == FA_CAL_SPEED_5G ? 5000 : spd == FA_CAL_SPEED_10G ? 10000 : 25000);

        if (port < RT_CHIP_PORTS) {
            port_bw += this_bw;
        }

        if (port_no >= RT_CHIP_PORTS) {
            this_bw = this_bw/2; // Internal ports are granted half the value
        }
        bw += this_bw;
        VTSS_D("chip_port = %u, this_bw = %u, summed bw = %u", port, this_bw, bw);
        cal[port/10] += (spd << ((port % 10) * 3));

        if (port_no < VTSS_PORTS) {
            vtss_state->port.map[port_no].max_bw = cal2bw(spd); // Update with the actual given BW.
        }
    }

    if (port_bw > fa_target_bw(vtss_state)) {
        VTSS_E("The configured port BW (%d) is above BW supported by target (d%x / %d Mbps)",
               port_bw, vtss_state->create.target, fa_target_bw(vtss_state));
        return VTSS_RC_ERROR;
    }

    if (bw > max_core_bw) {
        VTSS_E("The configured BW (%d) is above switch core BW (%d)", bw, max_core_bw);
        return VTSS_RC_ERROR;
    }

    if (FA_TGT) {
        /* Halt the calendar while changing it (only needed on a oversubscribed calendar) */
        REG_WRM(VTSS_QSYS_CAL_CTRL,
                VTSS_F_QSYS_CAL_CTRL_CAL_MODE(10),
                VTSS_M_QSYS_CAL_CTRL_CAL_MODE);
    }

    /* Assign device BW to auto calendar */
    for (i = 0; i < replicator; i++) {
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

#define FA_DSM_CAL_BW_LOSS            553
#define FA_DSM_CAL_MAX_DEVS_PER_TAXI  13
#define FA_DSM_CAL_TAXIS              8
#define FA_DSM_CAL_LEN                64
#define FA_DSM_CAL_EMPTY              0xFFFF

static u32 dsm_cal_len(vtss_state_t *vtss_state, u32 *cal)
{
    u32 i = 0, len = 0;
    while(i < FA_DSM_CAL_LEN) {
        if (cal[i] != FA_DSM_CAL_EMPTY)
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

static u32 dsm_cp_cal(vtss_state_t *vtss_state, u32 *sched)
{
    u32 i = 0, tmp;
    while(i < FA_DSM_CAL_LEN) {
        if (sched[i] != FA_DSM_CAL_EMPTY) {
            tmp = sched[i];
            sched[i] = FA_DSM_CAL_EMPTY;
            return tmp;
        }
        i++;
    }
    return FA_DSM_CAL_EMPTY;
}

static BOOL fa_dsm_cmp_calendar(vtss_state_t *vtss_state, u32 taxi, u32 *calendar)
{
    u32 len = dsm_cal_len(vtss_state, calendar), val;

    for (u32 i = 0; i < len; i++) {
        REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_F_DSM_TAXI_CAL_CFG_CAL_IDX(i),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_IDX);
        REG_RD(VTSS_DSM_TAXI_CAL_CFG(taxi), &val);
        val = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_VAL(val);

        if (calendar[i] != val) {
            return FALSE;
        }
    }
    return TRUE;
}

static vtss_rc fa_dsm_set_calendar(vtss_state_t *vtss_state, u32 taxi, u32 *calendar, u32 len)
{
    u32 val;

#if defined(VTSS_ARCH_LAN969X)
    REG_RD(VTSS_DSM_TAXI_CAL_CFG(taxi), &val);
    u32 active_calendar = VTSS_X_DSM_TAXI_CAL_CFG_CAL_SEL_STAT(val);
    REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
            VTSS_F_DSM_TAXI_CAL_CFG_CAL_PGM_SEL(!active_calendar),
            VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_SEL);
#endif

    REG_WRM_SET(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_ENA);

    for (u32 i = 0; i < len; i++) {
        REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_F_DSM_TAXI_CAL_CFG_CAL_IDX(i),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_IDX);
        REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_F_DSM_TAXI_CAL_CFG_CAL_PGM_VAL(calendar[i]),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_VAL);
    }

    REG_WRM_CLR(VTSS_DSM_TAXI_CAL_CFG(taxi),
                VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_ENA);
    REG_RD(VTSS_DSM_TAXI_CAL_CFG(taxi), &val);
    val = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_LEN(val);
    if (val != len - 1) {
        VTSS_E("Calendar length is not correct (%d)",val);
    }
#if defined(VTSS_ARCH_LAN969X)
    REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
            VTSS_F_DSM_TAXI_CAL_CFG_CAL_SWITCH(1),
            VTSS_M_DSM_TAXI_CAL_CFG_CAL_SWITCH);
#endif
    return VTSS_RC_OK;
}

static vtss_rc fa_dsm_chk_calendar(vtss_state_t *vtss_state, u32 *calendar, i32 *avg_dist)
{
    u32 num_of_slots, slot_indices[FA_DSM_CAL_LEN], distances[FA_DSM_CAL_LEN];
    int cnt, i, j, max_dist;
    u32 cal_length = dsm_cal_len(vtss_state, calendar);

    for (u32 port = 0; port < RT_DSM_CAL_MAX_DEVS_PER_TAXI; port++) {
        num_of_slots = 0;
        max_dist = avg_dist[port];
        for (i = 0; i < FA_DSM_CAL_LEN; i++) {
            slot_indices[i] = FA_DSM_CAL_EMPTY;
            distances[i] = FA_DSM_CAL_EMPTY;
        }

        for (i = 0; i < cal_length; i++) {
            if (calendar[i] == port) {
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

#define FA_CHIP_PORTS_ALL (65 + 5)

/* MESA-641. Function ported from verification/TCL to manually calculate fifo size for DSM calendar */
u32 vtss_get_fifo_size(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
#if defined(VTSS_ARCH_SPARX5)
    u32 sys_clk = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);
    u32 mac_width = 8;
    u32 fifo_width = 16;
    u32 addition = 0;
    u32 mac_per = 6400, tmp1, tmp2, tmp3, tmp4;
    u32 port   = VTSS_CHIP_PORT(port_no);
    u32 taxi_dist[FA_CHIP_PORTS_ALL] = {6,8,10,6,8,10,6,8,10,6,8,10, \
                                        4,4,4,4,                        \
                                        11,12,13,14,15,16,17,18,        \
                                        11,12,13,14,15,16,17,18,        \
                                        11,12,13,14,15,16,17,18,        \
                                        11,12,13,14,15,16,17,18,        \
                                        4,6,8,4,6,8,6,8,                \
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
    tmp4 = (tmp3 + 2000 + 999) / 1000 + addition;
    return tmp4;
#else
    switch (conf->speed) {
    case VTSS_SPEED_100M:
    case VTSS_SPEED_10M:
        return 1;
    default:
        return 0;
    }
#endif
}

#if VTSS_OPT_DEBUG_PRINT
static char *cal2txt(vtss_state_t *vtss_state, u32 port, fa_cal_speed_t spd) {
    switch (spd) {
    case FA_CAL_SPEED_1G:
        if (port < RT_CHIP_PORTS) {
            return "1G";
        } else {
            return "500M";
        }
    case FA_CAL_SPEED_2G5:
        if (port < RT_CHIP_PORTS) {
            return "2G5";
        } else {
            return "1.25G";
        }
    case FA_CAL_SPEED_5G:
        if (port < RT_CHIP_PORTS) {
            return "5G";
        } else {
            return "2G5";
        }
    case FA_CAL_SPEED_10G:
        if (port < RT_CHIP_PORTS) {
            return "10G";
        } else {
            return "5G";
        }
    case FA_CAL_SPEED_25G:
        if (port < RT_CHIP_PORTS) {
            return "25G";
        } else {
            return "12.5G";
        }
    default:
        break;
    }
    return "?";
}
#endif

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

static u32 bwd2int(vtss_internal_bw_t bw) {
    switch (bw) {
    case VTSS_BW_1G:  return 1000;
    case VTSS_BW_2G5: return 2500;
    case VTSS_BW_5G:  return 5000;
    case VTSS_BW_10G: return 10000;
    case VTSS_BW_25G: return 25000;
    default:
        break;
    }
    return 0;
}


static void taxi2ports(vtss_state_t *vtss_state, u32 taxi, u32 *port_ptr) {
    static const u32 fa_taxi_ports[FA_DSM_CAL_TAXIS][FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {
        {57,12,0,1,2,16,17,18,19,20,21,22,23},
        {58,13,3,4,5,24,25,26,27,28,29,30,31},
        {59,14,6,7,8,32,33,34,35,36,37,38,39},
        {60,15,9,10,11,40,41,42,43,44,45,46,47},
        {61,48,49,50,99,99,99,99,99,99,99,99,99},
        {62,51,52,53,99,99,99,99,99,99,99,99,99},
        {56,63,54,55,99,99,99,99,99,99,99,99,99},
        {64,99,99,99,99,99,99,99,99,99,99,99,99}};
    static const u32 la_taxi_ports[FA_DSM_CAL_TAXIS][FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {
        {0,4,1,2,3,5,6,7,28,29},
        {8,12,9,13,10,11,14,15,99,99},
        {16,20,17,21,18,19,22,23,99,99},
        {24,25,99,99,99,99,99,99,99,99},
        {26,27,99,99,99,99,99,99,99,99}};

    if (FA_TGT) {
        VTSS_MEMCPY(port_ptr,  &fa_taxi_ports[taxi],
                    sizeof(u32) * RT_DSM_CAL_MAX_DEVS_PER_TAXI);

    } else {
        VTSS_MEMCPY(port_ptr, &la_taxi_ports[taxi],
                    sizeof(u32) * RT_DSM_CAL_MAX_DEVS_PER_TAXI);
    }
}

#ifdef VTSS_FEATURE_REDBOX
// When a given taxi bus' RedBox is enabled AND one of the LRE ports is
// connected to the neighboring RedBox, a bug in the chip requires us to create
// a special DSM calendar that makes sure that a calendar slot X slots after the
// RedBox's interlink port's slot is unused. The 'X' depends on the delay
// through the taxi bus from start to end. 5G and 10G devices add a delay of 2.
// 2.5G devices add a delay of 1. This delay is there whether or not the device
// is part of the port map.
// Also, if a 5G or 10G device is configured with a speed lower than 5G, that
// device adds one to the delay through the taxi bus. This is not included in
// the table here:
static const u32 la_taxi_bus_delays[FA_DSM_CAL_TAXIS][FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {
    {2 /* D0  */, 2 /* D4  */, 1 /* D1  */, 1 /* D2  */, 1 /* D3  */, 1 /* D5  */, 1 /* D6  */, 1 /* D7  */, 1 /* D28 */, 1 /* D29 */},
    {2 /* D8  */, 2 /* D12 */, 2 /* D9  */, 2 /* D13 */, 1 /* D10 */, 1 /* D11 */, 1 /* D14 */, 1 /* D15 */},
    {2 /* D16 */, 2 /* D20 */, 2 /* D17 */, 2 /* D21 */, 1 /* D18 */, 1 /* D19 */, 1 /* D22 */, 1 /* D23 */},
    {2 /* D24 */, 2 /* D25 */},
    {2 /* D26 */, 2 /* D27 */},
};
#endif

vtss_rc vtss_fa_port2taxi(vtss_state_t *vtss_state,
                          u32 taxi, vtss_port_no_t port_no, u32 *taxi_port)
{
    u32 taxi_ports[FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {0};
    u32 i, port = VTSS_CHIP_PORT(port_no);

    taxi2ports(vtss_state, taxi, taxi_ports);
    for (i = 0; i < RT_DSM_CAL_MAX_DEVS_PER_TAXI; i++) {
        if (taxi_ports[i] == port) {
            // Found chip port at taxi port
            *taxi_port = i;
            return VTSS_RC_OK;
        }
    }
    return VTSS_RC_ERROR;
}

static vtss_rc fa_dsm_calc_calendar(vtss_state_t *vtss_state, u32 taxi, u32 *schedule, i32 *avg_dist) {
    u32 gcd, k, i, a, sum = 0, min = 25000, factor, adjusted_speed;
    u32 num_of_slots, slot_spd, raw_spd, spd, empty_slots;
    u32 indices_len, act, ts, cal_spd, port_spd;
    i32 port = 0, cnt;
    u32 num_of_old_slots, num_of_new_slots, tgt_score;
    u32 taxi_bw, clk_period_ps;
    u32 port_speeds[FA_CHIP_PORTS_ALL] = {0};
    u32 taxi_ports[FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {0};
    u32 taxi_speeds[FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {0};
    u32 dev_slots[FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {0};
    u32 new_slots[FA_DSM_CAL_LEN] = {0};
    u32 indices[FA_DSM_CAL_LEN] = {0};
    u32 short_list[FA_DSM_CAL_LEN] = {0};
    u32 long_list[FA_DSM_CAL_LEN] = {0};
    u32 temp_sched[FA_DSM_CAL_LEN] = {0};

    clk_period_ps = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);
    taxi_bw = 128 * 1000000 / clk_period_ps;
    taxi2ports(vtss_state, taxi, taxi_ports);

    for (i = 0; i < FA_DSM_CAL_LEN; i++) {
        new_slots[i] = FA_DSM_CAL_EMPTY;
        schedule[i] = FA_DSM_CAL_EMPTY;
        temp_sched[i] = FA_DSM_CAL_EMPTY;
    }
    // Default empty calendar
    schedule[0] = FA_DSM_CAL_MAX_DEVS_PER_TAXI;

    for (u32 p = 0; p < vtss_state->port_count; p++) {
        cal_spd = fa_cal_speed_get(vtss_state, p, &port, 0, 0);
        port_spd = calspd2int(cal_spd);
        port_speeds[port] = port_spd;
    }
    // Map ports to taxi positions
    for (u32 i = 0; i < RT_DSM_CAL_MAX_DEVS_PER_TAXI; i++) {
        port = taxi_ports[i];
        if (port < RT_CHIP_PORTS_ALL) {
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
        return VTSS_RC_OK; // Empty calendar
    }
    // Make room for overhead traffic
    factor = 100 * 100 * 1000 / (100 * 100 - FA_DSM_CAL_BW_LOSS);

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
        slot_spd = raw_spd * factor;
        num_of_slots = taxi_bw * 1000 / slot_spd;
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
        if (FA_TGT) {
            /* Improved and allowed in Laguna, i.e. this check can be skipped  */
            u32 slow_mode = clk_period_ps > 2000 ? 1 : 0;
            if (spd != 25000 && (spd != 10000 || !slow_mode)) {
                if (num_of_slots < (5 * dev_slots[i])) {
                    VTSS_E("Port spd %d taxi %d cannot not be scheduled with min. separation of 5 slots",spd, taxi);
                    return VTSS_RC_ERROR;
                }
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
        schedule[i] = RT_DSM_CAL_MAX_DEVS_PER_TAXI;
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

        for (a = 0; a < FA_DSM_CAL_LEN; a++) {
            if (schedule[a] == FA_DSM_CAL_EMPTY)
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

        while(dsm_cal_len(vtss_state, short_list) > 0 || dsm_cal_len(vtss_state, long_list) > 0) {
            act = 0;
            if (dsm_cal_len(vtss_state, short_list) > 0) {
                temp_sched[ts] = dsm_cp_cal(vtss_state, short_list);
                ts++;
                cnt += 100000;
                act = 1;
            }
            while (dsm_cal_len(vtss_state, long_list) > 0 && cnt > 0) {
                temp_sched[ts] = dsm_cp_cal(vtss_state, long_list);
                ts++;
                cnt -= tgt_score;
                act = 1;
            }
            if (act == 0) {
                VTSS_E("Error in DSM calculation");
                return VTSS_RC_ERROR;
            }
        }

        for (a = 0; a < FA_DSM_CAL_LEN; a++) {
            if (temp_sched[a] == FA_DSM_CAL_EMPTY) {
                break;
            }
        }
        for (a = 0; a < FA_DSM_CAL_LEN; a++) {
            schedule[a] = temp_sched[a];
            temp_sched[a] = FA_DSM_CAL_EMPTY;
            new_slots[a] = FA_DSM_CAL_EMPTY;
        }
    }
    return VTSS_RC_OK;
}

#if VTSS_OPT_DEBUG_PRINT
// Dump the dsm taxi calendar
vtss_rc vtss_fa_dsm_cal_debug(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr)
{
    u32 len, val, port;
    u32 taxi_ports[FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {0};

    for (u32 taxi = 0; taxi < RT_DSM_CAL_TAXIS; taxi++) {
        taxi2ports(vtss_state, taxi, taxi_ports);
        REG_RD(VTSS_DSM_TAXI_CAL_CFG(taxi), &len);
        len = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_LEN(len) + 1;
        pr("Taxi:%d, Len:%d, Cal:\n", taxi, len);
        for (u32 i = 0; i < len; i++) {
            REG_WRM(VTSS_DSM_TAXI_CAL_CFG(taxi),
                    VTSS_F_DSM_TAXI_CAL_CFG_CAL_IDX(i),
                    VTSS_M_DSM_TAXI_CAL_CFG_CAL_IDX);
            REG_RD(VTSS_DSM_TAXI_CAL_CFG(taxi), &val);
            val = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_VAL(val);
            if (val < RT_DSM_CAL_MAX_DEVS_PER_TAXI) {
                port = taxi_ports[val];
                pr(" %d ",port);
            } else if (FA_TGT) {
                pr(" - ");
            } else {
                // LAN969x
                pr(" %c ", val == TAXI_SLOT_UNUSED_BUT_LOCKED ? 'L' : '-');
            }

            if ((i > 0 && (i % 32 == 0)) || (i == len - 1)) {
                pr("\n");
            }
        }
    }
    return VTSS_RC_OK;
}

// Dump the auto calendar
vtss_rc vtss_fa_cell_cal_debug(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr)
{
    u32 cal, bw = 0, this_bw = 0, val,  port_bw = 0;
    fa_cal_speed_t spd;

    for (u32 port = 0; port < RT_CHIP_PORTS_ALL; port++) {
        REG_RD(VTSS_QSYS_CAL_AUTO(port/10), &cal);
        spd = (cal >> ((port % 10) * 3)) & 0x7;
        if (spd == 0) {
            continue;
        }
        pr("port:%d gets reserved spd:%s %s\n",
           port,
           cal2txt(vtss_state, port, spd),
           port == RT_CHIP_PORT_CPU_0 ? "(CPU0)" :
           port == RT_CHIP_PORT_CPU_1 ? "(CPU1)" :
           port == RT_CHIP_PORT_VD0 ? "(IPMC)" :
           port == RT_CHIP_PORT_VD1 ? "(AFI/OAM)" :
           port == RT_CHIP_PORT_VD2 ? "(IPinIP)" : "");
        this_bw = (spd == FA_CAL_SPEED_1G ? 1000 : spd == FA_CAL_SPEED_2G5 ? 2500 :
                   spd == FA_CAL_SPEED_5G ? 5000 : spd == FA_CAL_SPEED_10G ? 10000 : 25000);
        if (port < RT_CHIP_PORTS) {
            port_bw += this_bw;
        } else {
            this_bw = this_bw/2; // Internal ports are granted half the value
        }
        bw += this_bw;
    }

    for (u32 i = 0; i < 5; i++) {
        REG_RD(VTSS_HSCH_OUTB_SHARE_ENA(i), &val);
        if (VTSS_X_HSCH_OUTB_SHARE_ENA_OUTB_SHARE_ENA(val) > 0) {
            pr("Internal port:%d gets idle traffic ",RT_CHIP_PORTS+i);
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

    pr("Total assigned port BW:%d Mb\n",port_bw);
    pr("Total allowed port BW :%d Mb\n",fa_target_bw(vtss_state));
    pr("Total assigned BW     :%d Mb\n",bw);
    pr("Max switchcore BW     :%d Mb\n",clock2bw(vtss_state->init_conf.core_clock.freq));

    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_REDBOX)
/******************************************************************************/
// la_dsm_cal_delay_get()
// This function calculates the delay through the taxi bus, based on the
// following:
//   2 x FastDevCnt + SlowDevCnt + ShadowDevCnt + 2.
// Where
//   FastDev is a device that supports >= 5G,
//   SlowDev is a device that supports < 5G,
//   ShadowDev is a shadow device inserted on the taxi bus when a FastDev is
//   configured to run less than 5G,
//   The last "+ 2" is the delay through the RedBox.
//
// The returned delay is only non-zero if the RedBox is enabled AND it is using
// the neighboring redbox as one of the LRE ports.
/******************************************************************************/
static vtss_rc la_dsm_cal_delay_get(vtss_state_t *vtss_state, u32 taxi_bus, u32 dev_cnt, u32 interlink_dev, const u32 *dev_speeds_from_port_map, const BOOL *dev_speeds_5g_or_higher, u32 *delay)
{
    u32  dev;
    BOOL interlink_dev_used = FALSE;

    if (!vtss_state->vtss_features[FEATURE_REDBOX]) {
        *delay = 0;
        return VTSS_RC_OK;
    }

    *delay = 2; // Through the RedBox.

    for (dev = 0; dev < dev_cnt; dev++) {
        // There is a fixed overhead on the delay through a given taxi bus. This
        // is given by the la_taxi_bus_delays[][] array.
        *delay += la_taxi_bus_delays[taxi_bus][dev];

        if (dev == interlink_dev) {
            interlink_dev_used = TRUE;
        }

        // On top of the fixed overhead delay comes one delay per 5G and 10G
        // port that operates in less than 5G mode due to insertion of a
        // so-called shadow device on the taxi bus.
        // We can distinguish 5G and 10G ports from 2.5G ports by them having a
        // delay of 2 in the delay table.
        if (la_taxi_bus_delays[taxi_bus][dev] > 1) {
            // This is physically a 5G or 10G port.
            if (dev_speeds_from_port_map[dev] > 0 && !dev_speeds_5g_or_higher[dev]) {
                // And it is indeed in the port map and is running less than 5G
                (*delay)++;
            }
        }
    }

    // If the interlink_dev was not used in the above calculations, return a
    // delay of 0, because it doesn't matter.
    if (!interlink_dev_used) {
        *delay = 0;
    }

    return VTSS_RC_OK;
}
#endif

/******************************************************************************/
// la_dsm_cal_idx_set()
// Helper function that both checks that the calendar index is within limits and
// indeeds sets an unused slot. If both fulfilled, it sets the calendar index to
// dev.
/******************************************************************************/
static vtss_rc la_dsm_cal_idx_set(vtss_state_t *vtss_state, u32 taxi_bus, u32 *calendar, u32 cal_len, u32 cal_idx, u32 dev)
{
    if (cal_idx >= cal_len) {
        VTSS_E("Taxi %u, dev = %u: cal_idx (%u) is out of bounds (must be smaller than %u)", taxi_bus, dev, cal_idx, cal_len);
        return VTSS_RC_ERROR;
    }

    if (calendar[cal_idx] != TAXI_SLOT_UNUSED) {
        VTSS_E("Taxi %u, dev = %u: calendar[%u] is not unused (%u), but %u", taxi_bus, dev, cal_idx, TAXI_SLOT_UNUSED, calendar[cal_idx]);
        return VTSS_RC_ERROR;
    }

    calendar[cal_idx] = dev;
    return VTSS_RC_OK;
}

/******************************************************************************/
// la_dsm_cal_idx_find_next_free()
// Helper function that finds the next free calendar entry, starting with
// cal_idx, which is both an in and out parameter.
/******************************************************************************/
static vtss_rc la_dsm_cal_idx_find_next_free(vtss_state_t *vtss_state, u32 taxi_bus, u32 *calendar, u32 cal_len, u32 *cal_idx, u32 dev)
{
    if (*cal_idx >= cal_len) {
        VTSS_E("Taxi %u, dev %u: cal_idx (%u) >= cal_len (%u) on entry to function", taxi_bus, dev, *cal_idx, cal_len);
        return VTSS_RC_ERROR;
    }

    do {
        if (calendar[*cal_idx] == TAXI_SLOT_UNUSED) {
            return VTSS_RC_OK;
        }

        (*cal_idx)++;
    } while (*cal_idx < cal_len);

    VTSS_E("Taxi %u, dev %u: No free entries found in calendar of length %u", taxi_bus, dev, cal_len);
    return VTSS_RC_ERROR;
}

/******************************************************************************/
// la_dsm_calc_calendar()
// dev_speeds_from_port_map[] is an array, where the first dev_cnt entries are
// set to the requested B/W from the port map.
// dev_cnt always corresponds to the number of devices attached to this taxi
// bus. Unused ports will have a requested B/W of 0.
//
// interlink_dev is RT_DSM_CAL_MAX_DEVS_PER_TAXI if the RedBox of this taxi bus
// is not enabled or the RedBox doesn't use the neighboring RedBox as one of its
// LRE ports. Otherwise it is the index of the device thatis the RedBox'
// interlink port.
//
// taxi_bw is the taxi bus' bandwidth measured in Mbps.
//
// cal and cal_len are the results of this function.
//
// If force is true, we always calculate a new calendar. Otherwise, the function
// may return VTSS_RC_OK if the calendar hasn't changed, in which case
// *cal_changed is set to FALSE.
/******************************************************************************/
static vtss_rc la_dsm_calc_calendar(vtss_state_t *vtss_state, u32 taxi_bus, u32 dev_cnt, u32 interlink_dev, const u32 *dev_speeds_from_port_map, const BOOL *dev_speeds_5g_or_higher, u32 taxi_bw, BOOL force, u32 *calendar, u32 *calendar_len, BOOL *cal_changed)
{
#define CAL_IDX_SET(_cal_idx_, _dev_)            VTSS_RC(la_dsm_cal_idx_set(vtss_state, taxi_bus, calendar, cal_len, _cal_idx_, _dev_))
#define CAL_IDX_FIND_NEXT_FREE(_cal_idx_, _dev_) VTSS_RC(la_dsm_cal_idx_find_next_free(vtss_state, taxi_bus, calendar, cal_len, &_cal_idx_, _dev_))

    // Each entry in the following struct defines properties for a given speed
    // (10G, 5G, 2.5G, or 1G or less).
    typedef struct {
        // Number of devices that requires this speed
        u32 dev_cnt;

        // List of devices that requires this speed. Only first 'dev_cnt' are
        // valid.
        u32 devs[FA_DSM_CAL_MAX_DEVS_PER_TAXI];

        // Number of slots required for one device running this speed
        u32 slots_required;

        // Number of slots between two slots for one device running this speed.
        u32 slots_between_repeats;
    } dev_per_speed_t;

    dev_per_speed_t dev_per_speed[DEV_IDX_CNT] = {}, *d;
    u32             dev, delay, required_bw, cal_len, speed, idx, cal_idx, active_dev_cnt;
    u32             bw_per_slot, slots_required;
    char            buf[4 * FA_DSM_CAL_MAX_DEVS_PER_TAXI];
    int             sz;
    BOOL            interlink_active = FALSE, works;

#if defined(VTSS_FEATURE_REDBOX)
    // Get the required delay and bandwidth.
    VTSS_RC(la_dsm_cal_delay_get(vtss_state, taxi_bus, dev_cnt, interlink_dev, dev_speeds_from_port_map, dev_speeds_5g_or_higher, &delay));

    // If the delay has now changed or if we are forced to, compute a new
    // calendar.
    *cal_changed = delay != vtss_state->taxi_delay[taxi_bus] || force;

    // Save it for next calendar change call.
    vtss_state->taxi_delay[taxi_bus] = delay;
#else
    delay = 0;
    *cal_changed = force;
#endif

    if (!*cal_changed) {
        // Nothing to do. Caller knows not to apply a new calendar.
        return VTSS_RC_OK;
    }

    // Figure out how many device types (10G, 5G, 2.5G, <= 1G) are in the port
    // map for this taxi bus.
    active_dev_cnt = 0;
    required_bw    = 0;
    for (dev = 0; dev < dev_cnt; dev++) {
        speed = dev_speeds_from_port_map[dev];

        if (speed == 0) {
            // Unused port
            continue;
        }

        required_bw += speed;

        idx = SPEED2IDX(speed);
        d = &dev_per_speed[idx];
        d->devs[d->dev_cnt++] = dev;
        active_dev_cnt++;

        if (dev == interlink_dev) {
            // If this taxi bus' RedBox is enabled, its interlink port requires
            // double bandwidth, because there must be an unused slot for every
            // slot the interlink port has in the calendar.
            d->devs[d->dev_cnt++] = TAXI_SLOT_UNUSED_BUT_LOCKED;
            interlink_active = TRUE;
            required_bw += speed;
        }
    }

    VTSS_I("Taxi %u: %u devices, required B/W = %u Mbps, taxi B/W = %u Mbps, interlink_dev = %u, delay = %u", taxi_bus, dev_cnt, required_bw, taxi_bw, interlink_dev, delay);

    if (required_bw > taxi_bw) {
        VTSS_E("Taxi: %u: Required B/W (%u Mbps) cannot exceed the taxi bus' B/W (%u Mbps)", taxi_bus, required_bw, taxi_bw);
        return VTSS_RC_ERROR;
    }

    if (active_dev_cnt == 0) {
        // No devices used on this taxi bus.
        *calendar_len = 1;
        calendar[0] = TAXI_SLOT_UNUSED;
        return VTSS_RC_OK;
    }

    // The calendar needs at least one slot per device.
    cal_len = active_dev_cnt;

    // And it needs to be at least one longer than the delay.
    if (cal_len < delay) {
        cal_len = delay + 1;
    }

    // Search for a calendar length that fits all active devices
    bw_per_slot = 0;
    while (cal_len < FA_DSM_CAL_LEN) {
        // Use truncating division here
        bw_per_slot = taxi_bw / cal_len;

        slots_required = 0;
        works = TRUE;
        for (idx = 0; idx < DEV_IDX_CNT; idx++) {
             d = &dev_per_speed[idx];

             if (d->dev_cnt == 0) {
                 continue;
             }

            required_bw = IDX2SPEED(idx);

            d->slots_required = VTSS_DIV_ROUND_UP(required_bw, bw_per_slot);

            if (d->slots_required) {
                d->slots_between_repeats = VTSS_DIV_ROUND_UP(cal_len, d->slots_required);

                // delay and slots_between_repeats may not be the same.
                if (d->slots_between_repeats == delay) {
                    // Calendar length doesn't work.
                    cal_len++;
                    works = FALSE;
                    break;
                }

                slots_required += d->dev_cnt * d->slots_required;
            } else {
                d->slots_between_repeats = 0;
            }
        }

        if (!works) {
            continue;
        }

        if (slots_required <= cal_len) {
            // Found a suitable calendar length
            break;
        }

        // Not good enough yet.
        cal_len = slots_required;
    }

    if (cal_len > FA_DSM_CAL_LEN) {
        VTSS_E("Taxi %u: Computed calendar length (%u) is greater than the amount of slots in H/W (%u)", taxi_bus, cal_len, FA_DSM_CAL_LEN);
        return VTSS_RC_ERROR;
    }

    VTSS_I("Taxi %u: active_dev_cnt = %u, cal_len = %u, bw_per_slot = %u", taxi_bus, active_dev_cnt, cal_len, bw_per_slot);
    for (idx = 0; idx < DEV_IDX_CNT; idx++) {
        d = &dev_per_speed[idx];

        sz = 0;
        buf[0] = '\0';
        for (dev = 0; dev < d->dev_cnt; dev++) {
            sz += VTSS_SNPRINTF(buf + sz, sizeof(buf) - sz, " %u ", d->devs[dev]);
        }

        VTSS_I("idx = %u: speed = %5u, dev_cnt = %u, slots_required = %u, slots_between_repeats = %u, devs = %s", idx, IDX2SPEED(idx), d->dev_cnt, d->slots_required, d->slots_between_repeats, buf);
    }

    for (cal_idx = 0; cal_idx < cal_len; cal_idx++) {
       calendar[cal_idx] = TAXI_SLOT_UNUSED;
    }

    // Start by placing the interlink device and its associated unused slots.
    if (interlink_active) {
        // Figure out how many slots the interlink port requires.
        idx = SPEED2IDX(dev_speeds_from_port_map[interlink_dev]);
        d = &dev_per_speed[idx];

        for (slots_required = 0; slots_required < d->slots_required; slots_required++) {
            // Space them evenly.
            cal_idx = slots_required * d->slots_between_repeats;
            CAL_IDX_SET(cal_idx, interlink_dev);

            // Add an unused slot 'delay' slots after.
            CAL_IDX_SET((cal_idx + delay) % cal_len, TAXI_SLOT_UNUSED_BUT_LOCKED);
        }
    }

    // Place the remaining devices. Start with the fastest.
    for (idx = 0; idx < DEV_IDX_CNT; idx++) {
        d = &dev_per_speed[idx];

        for (dev = 0; dev < d->dev_cnt; dev++) {
            if (d->devs[dev] == interlink_dev || d->devs[dev] == TAXI_SLOT_UNUSED_BUT_LOCKED) {
                // Already placed
                continue;
            }

            cal_idx = 0;
            for (slots_required = 0; slots_required < d->slots_required; slots_required++) {
                CAL_IDX_FIND_NEXT_FREE(cal_idx, d->devs[dev]);
                CAL_IDX_SET(cal_idx, d->devs[dev]);
                cal_idx += d->slots_between_repeats;
            }
        }
    }

    *calendar_len = cal_len;
    return VTSS_RC_OK;
}

/******************************************************************************/
// fa_dsm_calc_and_apply_calendar()
/******************************************************************************/
vtss_rc fa_dsm_calc_and_apply_calendar(vtss_state_t *vtss_state, BOOL force)
{
    u32 calendar[FA_DSM_CAL_LEN], taxi;

    if (FA_TGT) {
        i32 avg_len[FA_DSM_CAL_LEN];

        for (taxi = 0; taxi < RT_DSM_CAL_TAXIS; taxi++) {
            VTSS_RC(fa_dsm_calc_calendar(vtss_state, taxi, calendar, avg_len));
            VTSS_RC(fa_dsm_chk_calendar(vtss_state, calendar, avg_len));
            if (!fa_dsm_cmp_calendar(vtss_state, taxi, calendar)) {
                VTSS_RC(fa_dsm_set_calendar(vtss_state, taxi, calendar, dsm_cal_len(vtss_state, calendar)));
            }
        }
    } else {
        u32                 cal_len, p;
        u32                 dev_speeds_from_port_map[FA_DSM_CAL_MAX_DEVS_PER_TAXI] = {};
        BOOL                dev_speeds_5g_or_higher[FA_DSM_CAL_MAX_DEVS_PER_TAXI]  = {};
        u32                 taxi_ports[FA_DSM_CAL_MAX_DEVS_PER_TAXI]               = {};
        u32                 port_speeds[VTSS_PORTS]                                = {};
        BOOL                port_speeds_5g_or_higher[VTSS_PORTS]                   = {};
        u32                 freq_mhz = 328; // Currently only supported frequency
        u32                 taxi_bw;
        u32                 interlink_dev, dev;
        BOOL                first, cal_changed;
        char                buf[2 * FA_DSM_CAL_LEN];
        int                 sz;
        vtss_phys_port_no_t interlink_chip_port;

#if defined(VTSS_FEATURE_REDBOX)
        vtss_rb_conf_t *rb_conf;
#endif

        // Each taxi bus has a certain bandwidth that depends on the configured
        // core clock frequency (freq_mhz).
        // This B/W is 128 bits/taxiword * freq_mhz.
        // If, however, 71 byte frames are sent back-to-back on a 1G port, the
        // required B/W for that 1G port is more than 1G. In fact, it is 1.055
        // times higher.
        // Therefore, we pretend that the total available bandwidth on the taxi
        // bus is 1.055 times lower than actually and use that for all
        // calculations despite actually requested port B/W.
        // Division by 1.055 is roughly the same as multiplication by 0.948.
        taxi_bw = (freq_mhz * 128 /* bits per taxi word */ * 948) / 1000;

        for (p = 0; p < vtss_state->port_count; p++) {
            port_speeds[VTSS_CHIP_PORT(p)] = bwd2int(vtss_state->port.map[p].max_bw);

            // Computes whether the configured speed is >= 5G similarly to
            // fa_change_device(). A false TRUE on a 2.5G with configured speed
            // set to UNDEFINED doesn't matter, because the function that
            // utilizes this array only looks at 5G or 10G ports.
            port_speeds_5g_or_higher[VTSS_CHIP_PORT(p)] = vtss_state->port.conf[p].speed >= VTSS_SPEED_5G || vtss_state->port.conf[p].speed == VTSS_SPEED_UNDEFINED;
        }

        for (taxi = 0; taxi < RT_DSM_CAL_TAXIS; taxi++) {
            // Make taxi_ports[] contain the chip ports on this taxi bus. Not
            // all chip ports may be used in the port map.
            taxi2ports(vtss_state, taxi, taxi_ports);

#if defined(VTSS_FEATURE_REDBOX)
            // The RedBoxes are numbered the same was as the taxi busses, so we
            // can index the rb_conf[] directly with the taxi bus number.
            rb_conf = &vtss_state->l2.rb_conf[taxi];

            if (vtss_state->vtss_features[FEATURE_REDBOX] && rb_conf->mode != VTSS_RB_MODE_DISABLED && (rb_conf->port_a == VTSS_PORT_NO_NONE || rb_conf->port_b == VTSS_PORT_NO_NONE)) {
                // This SKU has the RedBox feature active, the RedBox is
                // enabled and either port_a or port_b is interconnected with
                // the neighboring RedBox. The interlink is the port that has a
                // value != VTSS_PORT_NO_NONE.
                interlink_chip_port = VTSS_CHIP_PORT(rb_conf->port_b == VTSS_PORT_NO_NONE ? rb_conf->port_a : rb_conf->port_b);
            } else {
                interlink_chip_port = VTSS_PORT_NO_NONE;
            }
#else
            interlink_chip_port = VTSS_PORT_NO_NONE;
#endif

            // Initialize the port that identifies this taxi bus' RedBox'
            // interlink port to an unused calendar value.
            interlink_dev = RT_DSM_CAL_MAX_DEVS_PER_TAXI;
            for (p = 0; p < RT_DSM_CAL_MAX_DEVS_PER_TAXI; p++) {
                if (taxi_ports[p] < RT_CHIP_PORTS_ALL) {
                    dev_speeds_from_port_map[p] = port_speeds[taxi_ports[p]];
                    dev_speeds_5g_or_higher[p]  = port_speeds_5g_or_higher[taxi_ports[p]];

                    if (taxi_ports[p] == interlink_chip_port) {
                        // This device is the interlink of an enabled RedBox
                        // with an internal connection to the neighboring
                        // RedBox.
                        interlink_dev = p;
                    }
                } else {
                    // Done with this taxi. p now holds the number of port
                    // devices on this taxi bus.
                    break;
                }
            }

            VTSS_RC(la_dsm_calc_calendar(vtss_state, taxi, p, interlink_dev, dev_speeds_from_port_map, dev_speeds_5g_or_higher, taxi_bw, force, calendar, &cal_len, &cal_changed));

            if (force || cal_changed) {
                // Print calendar
                first = TRUE;
                sz = 0;
                buf[0] = '\0';
                for (p = 0; p < cal_len; p++) {
                    dev = calendar[p];
                    if (dev == TAXI_SLOT_UNUSED || dev == TAXI_SLOT_UNUSED_BUT_LOCKED) {
                        sz += VTSS_SNPRINTF(buf + sz, sizeof(buf) - sz, "%s%c", first ? "" : " ", dev == TAXI_SLOT_UNUSED ? '-' : 'L');
                    } else {
                        sz += VTSS_SNPRINTF(buf + sz, sizeof(buf) - sz, "%s%u", first ? "" : " ", dev);
                    }

                    first = FALSE;
                }

                VTSS_I("Taxi: %u, calendar length: %u, calendar: %s\n", taxi, cal_len, buf);

                // Set calendar
                VTSS_RC(fa_dsm_set_calendar(vtss_state, taxi, calendar, cal_len));
            } else {
                VTSS_I("Taxi: %u: Calendar unchanged", taxi);
            }
        }
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_restart_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_map_set(vtss_state_t *vtss_state)
{
    vtss_rc rc;

    VTSS_PROF_ENTER(LM_PROF_ID_MESA_PMAP, 1);
    VTSS_RC(fa_cell_calendar_auto(vtss_state));

    /* Calculate and configure the DSM calendar */
    if (fa_dsm_calc_and_apply_calendar(vtss_state, TRUE /* force a new calendar */) != VTSS_RC_OK) {
        VTSS_E("DSM Calendar calc failed");
    }

    rc = vtss_fa_init_groups(vtss_state, VTSS_INIT_CMD_PORT_MAP);
    VTSS_PROF_EXIT(LM_PROF_ID_MESA_PMAP, 1);
    return rc;
}

/* Initilize features based on target */
static vtss_rc fa_feature_init(vtss_state_t *vtss_state)
{
    switch (vtss_state->create.target) {
    case VTSS_TARGET_7546:
    case VTSS_TARGET_7549:
    case VTSS_TARGET_7552:
    case VTSS_TARGET_7556:
    case VTSS_TARGET_7558:
        vtss_state->vtss_features[FEATURE_VLAN_COUNTERS] = TRUE;
        vtss_state->vtss_features[FEATURE_TIMESTAMP] = TRUE;
        break;
    case VTSS_TARGET_7546TSN:
    case VTSS_TARGET_7549TSN:
    case VTSS_TARGET_7552TSN:
    case VTSS_TARGET_7556TSN:
    case VTSS_TARGET_7558TSN:
        vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION] = TRUE;
        vtss_state->vtss_features[FEATURE_SYNCE] = TRUE;
        vtss_state->vtss_features[FEATURE_FRER]  = TRUE;
        vtss_state->vtss_features[FEATURE_PSFP]  = TRUE;
        vtss_state->vtss_features[FEATURE_TIMESTAMP] = TRUE;
        break;
    case VTSS_TARGET_LAN9694:
    case VTSS_TARGET_LAN9696:
    case VTSS_TARGET_LAN9698:
        vtss_state->vtss_features[FEATURE_VLAN_COUNTERS] = TRUE;
        vtss_state->vtss_features[FEATURE_MAC_INDEX_TABLE] = TRUE;
        break;
    case VTSS_TARGET_LAN9691VAO:
    case VTSS_TARGET_LAN9692VAO:
    case VTSS_TARGET_LAN9693VAO:
        vtss_state->vtss_features[FEATURE_MAC_INDEX_TABLE] = TRUE;
        vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION] = TRUE;
        vtss_state->vtss_features[FEATURE_SYNCE] = TRUE;
        vtss_state->vtss_features[FEATURE_FRER] = TRUE;
        vtss_state->vtss_features[FEATURE_PSFP] = TRUE;
        vtss_state->vtss_features[FEATURE_TIMESTAMP] = TRUE;
        break;
    case VTSS_TARGET_LAN9694TSN:
    case VTSS_TARGET_LAN9696TSN:
    case VTSS_TARGET_LAN9698TSN:
        vtss_state->vtss_features[FEATURE_MAC_INDEX_TABLE] = TRUE;
        vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION] = TRUE;
        vtss_state->vtss_features[FEATURE_SYNCE] = TRUE;
        vtss_state->vtss_features[FEATURE_FRER] = TRUE;
        vtss_state->vtss_features[FEATURE_PSFP] = TRUE;
        vtss_state->vtss_features[FEATURE_QOS_OT] = TRUE;
        vtss_state->vtss_features[FEATURE_MRP] = TRUE;
        vtss_state->vtss_features[FEATURE_MRP_V1] = TRUE;
        vtss_state->vtss_features[FEATURE_TIMESTAMP] = TRUE;
        break;
    case VTSS_TARGET_LAN9694RED:
    case VTSS_TARGET_LAN9696RED:
    case VTSS_TARGET_LAN9698RED:
        vtss_state->vtss_features[FEATURE_MAC_INDEX_TABLE] = TRUE;
        vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION] = TRUE;
        vtss_state->vtss_features[FEATURE_SYNCE] = TRUE;
        vtss_state->vtss_features[FEATURE_FRER] = TRUE;
        vtss_state->vtss_features[FEATURE_PSFP] = TRUE;
        vtss_state->vtss_features[FEATURE_QOS_OT] = TRUE;
        vtss_state->vtss_features[FEATURE_MRP] = TRUE;
        vtss_state->vtss_features[FEATURE_MRP_V1] = TRUE;
        vtss_state->vtss_features[FEATURE_TIMESTAMP] = TRUE;
        vtss_state->vtss_features[FEATURE_REDBOX] = TRUE;
        break;
    default:
        return VTSS_RC_ERROR;
    }

    // Features disabled at compile-time are always disabled at run-time
#if !defined(VTSS_FEATURE_VLAN_COUNTERS)
    vtss_state->vtss_features[FEATURE_VLAN_COUNTERS] = FALSE;
#endif
#if !defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION] = FALSE;
#endif
#if !defined(VTSS_FEATURE_SYNCE)
    vtss_state->vtss_features[FEATURE_SYNCE] = FALSE;
#endif
#if !defined(VTSS_FEATURE_FRER)
    vtss_state->vtss_features[FEATURE_FRER] = FALSE;
#endif
#if !defined(VTSS_FEATURE_PSFP)
    vtss_state->vtss_features[FEATURE_PSFP] = FALSE;
#endif
#if !defined(VTSS_FEATURE_REDBOX)
    vtss_state->vtss_features[FEATURE_REDBOX] = FALSE;
#endif
#if !defined(VTSS_FEATURE_QOS_OT)
    vtss_state->vtss_features[FEATURE_QOS_OT] = FALSE;
#endif
#if !defined(VTSS_FEATURE_MRP)
    vtss_state->vtss_features[FEATURE_MRP] = FALSE;
#endif
#if !defined(VTSS_FEATURE_MRP_V1)
    vtss_state->vtss_features[FEATURE_MRP_V1] = FALSE;
#endif
#if !defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    vtss_state->vtss_features[FEATURE_MAC_INDEX_TABLE] = FALSE;
#endif
#if !defined(VTSS_FEATURE_TIMESTAMP)
    vtss_state->vtss_features[FEATURE_TIMESTAMP] = FALSE;
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_inst_create(vtss_state_t *vtss_state)
{
    /* Initialization */
    VTSS_RC(fa_feature_init(vtss_state));

#if defined(VTSS_OPT_EMUL)
    VTSS_RC(vtss_fa_emul_init(vtss_state));
#endif

    /* Create function groups */
    return vtss_fa_init_groups(vtss_state, VTSS_INIT_CMD_CREATE);
}

#endif /* VTSS_ARCH_FA */
