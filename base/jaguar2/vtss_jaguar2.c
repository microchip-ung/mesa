// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

//#include <cyg/infra/diag.h>
#include "vtss_jaguar2_cil.h"
#if defined(VTSS_FEATURE_CLOCK)
#include "../omega/vtss_omega_clock_cil.h"
#endif
// Avoid Lint Warning 572: Excessive shift value (precision 1 shifted right by 2), which occurs
// in this file because (t) - VTSS_IO_ORIGIN1_OFFSET == 0 for t = VTSS_TO_CFG (i.e. ICPU_CFG), and 0 >> 2 gives a lint warning.
/*lint --e{572} */
#if defined(VTSS_ARCH_JAGUAR_2)

static vtss_rc jr2_wr_indirect(vtss_state_t *vtss_state, u32 addr, u32 value);
static vtss_rc jr2_rd_indirect(vtss_state_t *vtss_state, u32 addr, u32 *value);

vtss_rc (*vtss_jr2_wr)(vtss_state_t *vtss_state, u32 addr, u32 value) = jr2_wr_indirect;
vtss_rc (*vtss_jr2_rd)(vtss_state_t *vtss_state, u32 addr, u32 *value) = jr2_rd_indirect;

/* Read target register using current CPU interface */
static inline vtss_rc jr2_rd_direct(vtss_state_t *vtss_state, u32 reg, u32 *value)
{
    return vtss_state->init_conf.reg_read(0, reg, value);
}

/* Write target register using current CPU interface */
static inline vtss_rc jr2_wr_direct(vtss_state_t *vtss_state, u32 reg, u32 value)
{
    return vtss_state->init_conf.reg_write(0, reg, value);
}

static inline BOOL jr2_reg_directly_accessible(vtss_state_t *vtss_state, u32 addr)
{
    /* Using SPI, VCoreIII registers require indirect access.
     * Otherwise, all registers are directly accessible.
     */
    return vtss_state->init_conf.spi_bus ?
            (addr >= ((VTSS_IO_ORIGIN2_OFFSET - VTSS_IO_ORIGIN1_OFFSET) >> 2)) :
            TRUE;
}

/* Read or write register indirectly */
static vtss_rc jr2_reg_indirect_access(vtss_state_t *vtss_state, u32 addr, u32 *value, BOOL is_write)
{
    /* The following access must be executed atomically, and since this function may be called
     * without the API lock taken, we have to disable the scheduler */
    /*lint --e{529} */ // Avoid "Symbol 'flags' not subsequently referenced" Lint warning
    VTSS_OS_SCHEDULER_FLAGS flags = 0;
    u32 ctrl;
    vtss_rc result;

    /* The @addr is an address suitable for the read or write callout function installed by
     * the application, i.e. it's a 32-bit address suitable for presentation on a PI
     * address bus, i.e. it's not suitable for presentation on the VCore-III shared bus.
     * In order to make it suitable for presentation on the VCore-III shared bus, it must
     * be made an 8-bit address, so we multiply by 4, and it must be offset by the base
     * address of the switch core registers, so we add VTSS_IO_ORIGIN1_OFFSET.
     */
    addr <<= 2;
    addr += VTSS_IO_ORIGIN1_OFFSET;

    VTSS_OS_SCHEDULER_LOCK(flags);

    if ((result = vtss_jr2_wr(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_ADDR, addr)) != VTSS_RC_OK) {
        goto do_exit;
    }
    if (is_write) {
        if ((result = vtss_jr2_wr(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA, *value)) != VTSS_RC_OK) {
            goto do_exit;
        }
        // Wait for operation to complete
        do {
            if ((result = vtss_jr2_rd(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL, &ctrl)) != VTSS_RC_OK) {
                goto do_exit;
            }
        } while (ctrl & VTSS_M_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_BUSY);
    } else {
        // Dummy read to initiate access
        if ((result = vtss_jr2_rd(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA, value)) != VTSS_RC_OK) {
            goto do_exit;
        }
        // Wait for operation to complete
        do {
            if ((result = vtss_jr2_rd(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL, &ctrl)) != VTSS_RC_OK) {
                goto do_exit;
            }
        } while (ctrl & VTSS_M_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_BUSY);
        if ((result = vtss_jr2_rd(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA, value)) != VTSS_RC_OK) {
            goto do_exit;
        }
    }

do_exit:
    VTSS_OS_SCHEDULER_UNLOCK(flags);
    return result;
}

/* Read target register using current CPU interface */
static vtss_rc jr2_rd_indirect(vtss_state_t *vtss_state, u32 reg, u32 *value)
{
    if (jr2_reg_directly_accessible(vtss_state, reg)) {
        return vtss_state->init_conf.reg_read(0, reg, value);
    } else {
        return jr2_reg_indirect_access(vtss_state, reg, value, FALSE);
    }
}

/* Write target register using current CPU interface */
static vtss_rc jr2_wr_indirect(vtss_state_t *vtss_state, u32 reg, u32 value)
{
    if (jr2_reg_directly_accessible(vtss_state, reg)) {
        return vtss_state->init_conf.reg_write(0, reg, value);
    } else {
        return jr2_reg_indirect_access(vtss_state, reg, &value, TRUE);
    }
}

/* Read-modify-write target register using current CPU interface */
vtss_rc vtss_jr2_wrm(vtss_state_t *vtss_state, u32 reg, u32 value, u32 mask)
{
    vtss_rc rc;
    u32     val;

    if ((rc = vtss_jr2_rd(vtss_state, reg, &val)) == VTSS_RC_OK) {
        val = ((val & ~mask) | (value & mask));
        rc = vtss_jr2_wr(vtss_state, reg, val);
    }
    return rc;
}

/* ================================================================= *
 *  Utility functions
 * ================================================================= */

u64 vtss_jr2_pmask(u32 port)
{
    u64 mask = 1;

    return (mask << port);
}

u64 vtss_jr2_port_mask(vtss_state_t *vtss_state,
                       const BOOL member[])
{
    vtss_port_no_t port_no;
    u64            pmask = 0;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (member[port_no]) {
            pmask |= vtss_jr2_pmask(VTSS_CHIP_PORT(port_no));
        }
    }
    return pmask;
} // vtss_jr2_port_mask

/* Convert to PGID in chip */
u32 vtss_jr2_chip_pgid(vtss_state_t *vtss_state, u32 pgid)
{
    if (pgid < vtss_state->port_count) {
        return VTSS_CHIP_PORT(pgid);
    } else {
        return (pgid + VTSS_CHIP_PORTS - vtss_state->port_count);
    }
} // vtss_jr2_chip_pgid

/* Convert from PGID in chip */
u32 vtss_jr2_vtss_pgid(const vtss_state_t *const state, u32 pgid)
{
    vtss_port_no_t        port_no;
    const vtss_port_map_t *pmap;

    if (pgid < VTSS_CHIP_PORTS) {
        for (port_no = VTSS_PORT_NO_START; port_no < state->port_count; port_no++) {
            pmap = &state->port.map[port_no];
            if (pmap->chip_port == pgid)
                break;
        }
        return port_no;
    } else {
        return (state->port_count + pgid - VTSS_CHIP_PORTS);
    }
} // vtss_jr2_vtss_pgid

#if defined(VTSS_SDX_CNT)
static void jr2_evc_counter_update(u32 frames, u32 lsb, u32 msb, vtss_chip_counter_pair_t *chip_counter,
                                   vtss_counter_pair_t *evc_counter, BOOL clear)
{
   vtss_cmn_counter_32_update(frames, &chip_counter->frames, clear);
   vtss_cmn_counter_40_update(lsb, msb, &chip_counter->bytes, clear);

    if (evc_counter != NULL) {
        evc_counter->frames += chip_counter->frames.value;
        evc_counter->bytes += chip_counter->bytes.value;
    }
}

static vtss_rc jr2_evc_isdx_counter_update(vtss_state_t *vtss_state,
                                           u32 idx, u32 i, vtss_chip_counter_pair_t *chip_counter,
                                           vtss_counter_pair_t *evc_counter, BOOL clear)
{
    u32 frames, lsb, msb;

    /* Read frame and byte counters */
    JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(idx, i + 3), &frames);
    JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(idx, i), &lsb);
    JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT(idx, i), &msb);

    /* Update counters */
    jr2_evc_counter_update(frames, lsb, msb, chip_counter, evc_counter, clear);

    return VTSS_RC_OK;
}

static vtss_rc jr2_evc_qsys_counter_update(vtss_state_t *vtss_state,
                                           u32 addr, vtss_chip_counter_pair_t *chip_counter,
                                           vtss_counter_pair_t *evc_counter, BOOL clear)
{
    u32 frames, lsb, msb;

    /* Read frame and byte counters */
#if defined(VTSS_ARCH_JAGUAR_2_C)
    JR2_RD(VTSS_XQS_STAT_CNT(addr), &frames);
    JR2_RD(VTSS_XQS_STAT_CNT(addr + 64), &lsb);
    JR2_RD(VTSS_XQS_STAT_CNT(addr + 128), &msb);
#else
    JR2_RD(VTSS_QSYS_STAT_CNT(addr), &frames);
    JR2_RD(VTSS_QSYS_STAT_CNT(addr + 64), &lsb);
    JR2_RD(VTSS_QSYS_STAT_CNT(addr + 128), &msb);
#endif /* VTSS_ARCH_JAGUAR_2_C */
    /* Update counters */
    jr2_evc_counter_update(frames, lsb, msb, chip_counter, evc_counter, clear);

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_sdx_counters_update(vtss_state_t *vtss_state, vtss_stat_idx_t *stat_idx, vtss_evc_counters_t *const cnt, BOOL clr)
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
        VTSS_RC(jr2_evc_isdx_counter_update(vtss_state, idx, 0, &c->rx_green, cnt == NULL ? NULL : &cnt->rx_green, clr));
        VTSS_RC(jr2_evc_isdx_counter_update(vtss_state, idx, 1, &c->rx_yellow, cnt == NULL ? NULL : &cnt->rx_yellow, clr));
        VTSS_RC(jr2_evc_isdx_counter_update(vtss_state, idx, 2, &c->rx_red, cnt == NULL ? NULL : &cnt->rx_red, clr));

        /* QSYS counters */
#if defined(VTSS_ARCH_JAGUAR_2_C)
        JR2_WR(VTSS_XQS_SYSTEM_STAT_CFG, VTSS_F_XQS_SYSTEM_STAT_CFG_STAT_VIEW(idx));
#else
        JR2_WR(VTSS_QSYS_SYSTEM_STAT_CFG, VTSS_F_QSYS_SYSTEM_STAT_CFG_STAT_VIEW(idx));
#endif
        VTSS_RC(jr2_evc_qsys_counter_update(vtss_state, 512, &c->rx_discard, cnt == NULL ? NULL : &cnt->rx_discard, clr));
        VTSS_RC(jr2_evc_qsys_counter_update(vtss_state, 513, &c->tx_discard, cnt == NULL ? NULL : &cnt->rx_discard, clr));
    }

    /* Update egress counters, if active */
    idx = stat_idx->edx;
    row = &vtss_state->l2.estat_table.row[idx / 8];
    if (row->size != 0 && row->col[row->size * ((idx % 8) / row->size)].used) {
        c = &vtss_state->l2.sdx_info.sdx_table[idx];
#if defined(VTSS_ARCH_JAGUAR_2_C)
        JR2_WR(VTSS_XQS_SYSTEM_STAT_CFG, VTSS_F_XQS_SYSTEM_STAT_CFG_STAT_VIEW(idx));
#else
        JR2_WR(VTSS_QSYS_SYSTEM_STAT_CFG, VTSS_F_QSYS_SYSTEM_STAT_CFG_STAT_VIEW(idx));
#endif
        VTSS_RC(jr2_evc_qsys_counter_update(vtss_state, 768, &c->tx_green, cnt == NULL ? NULL : &cnt->tx_green, clr));
        VTSS_RC(jr2_evc_qsys_counter_update(vtss_state, 769, &c->tx_yellow, cnt == NULL ? NULL : &cnt->tx_yellow, clr));
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_isdx_update(vtss_state_t *vtss_state, vtss_sdx_entry_t *sdx)
{
    u32 cosid, isdx = sdx->sdx;
    u32 pol_max = (sdx->pol_cnt ? (sdx->pol_cnt - 1) : 0);
    u32 stat_max = (sdx->stat_cnt ? (sdx->stat_cnt - 1) : 0);

    JR2_WR(VTSS_ANA_L2_ISDX_DLB_CFG(isdx), VTSS_F_ANA_L2_ISDX_DLB_CFG_DLB_IDX(sdx->pol_idx));
    JR2_WR(VTSS_ANA_L2_ISDX_ISDX_BASE_CFG(isdx), VTSS_F_ANA_L2_ISDX_ISDX_BASE_CFG_ISDX_BASE_ADDR(sdx->stat_idx));
    for (cosid = 0; cosid < 8; cosid++) {
        JR2_WR(VTSS_ANA_L2_ISDX_DLB_COS_CFG(isdx, cosid), VTSS_F_ANA_L2_ISDX_DLB_COS_CFG_DLB_COS_OFFSET(cosid <= pol_max ? cosid : pol_max));
        JR2_WR(VTSS_ANA_L2_ISDX_ISDX_COS_CFG(isdx, cosid), VTSS_F_ANA_L2_ISDX_ISDX_COS_CFG_ISDX_COS_OFFSET(cosid <= stat_max ? cosid : stat_max));
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_SDX_CNT */

/* ================================================================= *
 *  Debug print utility functions
 * ================================================================= */

void vtss_jr2_debug_print_port_header(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr, const char *txt)
{
    vtss_debug_print_port_header(vtss_state, pr, txt, VTSS_CHIP_PORTS + 1, 1);
}

void vtss_jr2_debug_print_pmask(const vtss_debug_printf_t pr, u64 pmask)
{
    u32 port;

    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        pr("%s%s", port == 0 || (port & 7) ? "" : ".", (vtss_jr2_pmask(port) & pmask) ? "1" : "0");
    }
    pr("\n");
}

void vtss_jr2_debug_reg_header(const vtss_debug_printf_t pr, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%-32s  Tgt   Addr  ", name);
    vtss_debug_print_reg_header(pr, buf);
}

void vtss_jr2_debug_reg(vtss_state_t *vtss_state,
                        const vtss_debug_printf_t pr, u32 addr, const char *name)
{
    u32 value;
    char buf[100];

    if (vtss_jr2_rd(vtss_state, addr, &value) == VTSS_RC_OK) {
        VTSS_SPRINTF(buf, "%-32s  0x%02x  0x%04x", name, (addr >> 14) & 0x3f, addr & 0x3fff);
        vtss_debug_print_reg(pr, buf, value);
    }
}

void vtss_jr2_debug_reg_inst(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%s_%u", name, i);
    vtss_jr2_debug_reg(vtss_state, pr, addr, buf);
}

void vtss_jr2_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
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


static void jr2_debug_reg_clr(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr, u32 addr, const char *name, BOOL clr)
{
    u32  value, tgt;
    char buf[64];

    if (vtss_jr2_rd(vtss_state, addr, &value) == VTSS_RC_OK &&
        (clr == 0 || vtss_jr2_wr(vtss_state, addr, value) == VTSS_RC_OK)) {
        tgt = ((addr >> 14) & 0xff);
        if (tgt < 128) {
            /* 14 bit address */
            addr &= 0x3fff;
        } else if (tgt < 192) {
            /* 17 bit address */
            tgt &= 0xf8;
            addr &= 0x1ffff;
        } else {
            /* 18 bit address */
            tgt &= 0xf0;
            addr &= 0x3ffff;
        }
        VTSS_SPRINTF(buf, "%-32s  0x%02x 0x%05x", name, tgt, addr);
        vtss_debug_print_reg(pr, buf, value);
    }
} // jr2_debug_reg_clr


void vtss_jr2_debug_sticky(vtss_state_t *vtss_state,
                           const vtss_debug_printf_t pr, u32 addr, const char *name)
{
    jr2_debug_reg_clr(vtss_state, pr, addr, name, 1);
} // vtss_jr2_debug_sticky

static vtss_rc jr2_debug_info_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_jr2_misc_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_jr2_port_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_jr2_l2_debug_print(vtss_state, pr, info));
#if defined(VTSS_FEATURE_LAYER3)
    VTSS_RC(vtss_jr2_l3_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_LAYER3 */
    VTSS_RC(vtss_jr2_vcap_debug_print(vtss_state, pr, info));
#if defined(VTSS_FEATURE_QOS)
    VTSS_RC(vtss_jr2_qos_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_QOS */
    VTSS_RC(vtss_jr2_packet_debug_print(vtss_state, pr, info));
#if defined(VTSS_FEATURE_AFI_SWC)
    VTSS_RC(vtss_jr2_afi_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_AFI_SWC */
#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_jr2_ts_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_TIMESTAMP */
#if defined(VTSS_FEATURE_VOP)
    VTSS_RC(vtss_jr2_oam_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_VOP */
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    VTSS_N("Enter");

    /* Initialize ports */
    VTSS_RC(vtss_jr2_port_init(vtss_state, cmd));

    /* Initialize miscellaneous */
    VTSS_RC(vtss_jr2_misc_init(vtss_state, cmd));

    /* Initialize packet before L2 to ensure that VLAN table clear does not break VRAP access */
    VTSS_RC(vtss_jr2_packet_init(vtss_state, cmd));

#if defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_AFI_V2)
    VTSS_RC(vtss_jr2_afi_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_AFI_SWC&& VTSS_AFI_V2 */

    /* Initialize L2 */
    VTSS_RC(vtss_jr2_l2_init(vtss_state, cmd));

#if defined(VTSS_FEATURE_LAYER3)
    /* Initialize L3 */
    VTSS_RC(vtss_jr2_l3_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_LAYER3 */

#if defined(VTSS_FEATURE_VCAP)
    VTSS_RC(vtss_jr2_vcap_init(vtss_state, cmd));
#endif

#if defined(VTSS_FEATURE_QOS)
    VTSS_RC(vtss_jr2_qos_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_QOS */

#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_jr2_ts_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_TIMESTAMP */

#if defined(VTSS_FEATURE_VOP)
    VTSS_RC(vtss_jr2_oam_init(vtss_state, cmd));
#endif

#if defined(VTSS_FEATURE_CLOCK)
    VTSS_RC(vtss_es6514_clock_init(vtss_state, cmd));
#endif

    return VTSS_RC_OK;
}

typedef enum {
    JR2_CAL_SPEED_NONE = 0,
    JR2_CAL_SPEED_1G   = 1,
    JR2_CAL_SPEED_2G5  = 2,
    JR2_CAL_SPEED_10G  = 3,
} jr2_cal_speed_t;

static jr2_cal_speed_t jr2_cal_speed_get(vtss_state_t *vtss_state, vtss_port_no_t port_no, i32 *port)
{
    vtss_internal_bw_t max_bw;

    if (port_no >= VTSS_PORTS) {
        // It's a special port (CPU0, CPU1, VD0, or VD1). Give it 1G
        *port = (VTSS_CHIP_PORT_CPU + port_no - VTSS_PORTS);
        return JR2_CAL_SPEED_1G;
    }

    // Switch port. Use the port map.
    if ((*port = VTSS_CHIP_PORT(port_no)) == CHIP_PORT_UNUSED) {
        return JR2_CAL_SPEED_NONE;
    }

    max_bw = vtss_state->port.map[port_no].max_bw;

    VTSS_D("port = %u (chip_port = %u): max_bw = %u", port_no, *port, max_bw);
    switch (max_bw) {
        case VTSS_BW_DEFAULT:
            if (VTSS_PORT_IS_10G(*port)) {
                return JR2_CAL_SPEED_10G;
            } else if (*port >= VTSS_CHIP_PORT_2_5G_START) {
                return JR2_CAL_SPEED_2G5;
            }

            return JR2_CAL_SPEED_1G;

        case VTSS_BW_1G:
            return JR2_CAL_SPEED_1G;

        case VTSS_BW_2G5:
            return JR2_CAL_SPEED_2G5;

        case VTSS_BW_10G:
            return JR2_CAL_SPEED_10G;

        case VTSS_BW_UNDEFINED:
        default:
            VTSS_E("port_no = %u (chip_port = %u): In the port map, but with undefined B/W.", port_no, *port);
            break;
    }

    return JR2_CAL_SPEED_NONE;
}

// Auto configure the calendar based on port-map
static vtss_rc jr2_calendar_auto(vtss_state_t *vtss_state)
{
    u32                cal[4], value, bw = 0, this_bw;
    jr2_cal_speed_t    spd;
#if !defined(VTSS_ARCH_SERVAL_T)
    u32                i;
#endif /* VTSS_ARCH_SERVAL_T */
    vtss_port_no_t     port_no;
    i32                port;

    VTSS_I("Using Auto calendar");

    // Setup the calendar, i.e. the BW to each device
    VTSS_MEMSET(cal, 0, sizeof(cal));
    for (port_no = 0; port_no < (VTSS_PORTS + 4); port_no++) {
        spd = jr2_cal_speed_get(vtss_state, port_no, &port);
        if (port == CHIP_PORT_UNUSED || spd == JR2_CAL_SPEED_NONE) {
            continue;
        }

        this_bw = (spd == JR2_CAL_SPEED_1G ? 1000 : spd == JR2_CAL_SPEED_2G5 ? 2500 : 10000);
        bw += this_bw;
        VTSS_D("chip_port = %u, this_bw = %u, summed bw = %u", port, this_bw, bw);
        cal[port/16] += (spd << ((port % 16)*2));
    }

    if (vtss_state->create.target == VTSS_TARGET_SPARX_IV_90) {
        if (bw > 94000) {
            VTSS_E("The configured BW (%d) is above limit",bw);
        }
    } else {
        if (bw > 84000) {
            VTSS_E("The configured BW (%d) is above limit",bw);
        }
    }

    /* Use auto calendar mode for calendar calculation */
#if defined(VTSS_ARCH_SERVAL_T)
    JR2_WR(VTSS_QSYS_CALCFG_CAL_AUTO, cal[0]);
#else
    for (i = 0; i < 4; i++) {
        JR2_WR(VTSS_QSYS_CALCFG_CAL_AUTO(i), cal[i]);
    }
#endif /* VTSS_ARCH_SERVAL_T */

#if defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SERVAL_T)
    JR2_WRM(VTSS_QSYS_CALCFG_CAL_CTRL,
            VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_GRANT_RATE(671), /* 672->671, BZ19678 */
            VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_GRANT_RATE);

    /* Grant idle usage to VD1 */
    JR2_WR(VTSS_HSCH_HSCH_MISC_OUTB_SHARE_ENA(3),
           VTSS_F_HSCH_HSCH_MISC_OUTB_SHARE_ENA_OUTB_SHARE_ENA(10));
#endif /* (VTSS_ARCH_JAGUAR_2_C) || (VTSS_ARCH_SERVAL_T) */

    JR2_WRM(VTSS_QSYS_CALCFG_CAL_CTRL,
            VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_MODE(8),
            VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_MODE);

    /* Verify successful calendar config */
    JR2_RD(VTSS_QSYS_CALCFG_CAL_CTRL, &value);
    if (VTSS_X_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_ERROR(value)) {
        VTSS_E("Calendar auto error");
    }
    return VTSS_RC_OK;
 }

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_calendar_do_set(vtss_state_t *vtss_state, u8 *cal, u32 length, BOOL grant_idle_to_vd1, BOOL dynamic)
{
    u32 i;

    // This function is used when applying a pre-computed calendar on JR2B, when the
    // calendar calculation function fails and a pre-computed calendar for JR2C is
    // needed, or when applying a on-target-calculated calendar.

#if defined(VTSS_ARCH_JAGUAR_2_B)
    /* Halt the calendar + allow idle usage to Virtual ports */
    JR2_WRM(VTSS_QSYS_CALCFG_CAL_CTRL,
            VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_MODE(10) |
            VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_VD_USE_IDLE_ENA(1),
            VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_MODE |
            VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_VD_USE_IDLE_ENA);
#else
    // JR2C + ServalT

    /* Halt the calendar */
    JR2_WRM(VTSS_QSYS_CALCFG_CAL_CTRL,
            VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_MODE(10),
            VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_MODE);

    if (grant_idle_to_vd1) {
        /* Grant idle usage to VD1 */
        JR2_WR(VTSS_HSCH_HSCH_MISC_OUTB_SHARE_ENA(3),
               VTSS_F_HSCH_HSCH_MISC_OUTB_SHARE_ENA_OUTB_SHARE_ENA(10));
    }
#endif

    /* Enable calendar update */
    JR2_WRM(VTSS_QSYS_CALCFG_CAL_SEQ,
            VTSS_F_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_ENA(1),
            VTSS_M_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_ENA);

    VTSS_NSLEEP(100);

    /* Update according to the above table */
    for (i = 0; i < length; i++) {
        JR2_WRM(VTSS_QSYS_CALCFG_CAL_SEQ,
                VTSS_F_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_LEN(i) |
                VTSS_F_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_VAL(cal[i]),
                VTSS_M_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_LEN |
                VTSS_M_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_VAL);

        VTSS_NSLEEP(100);
    }

     /* Press start */
    JR2_WRM(VTSS_QSYS_CALCFG_CAL_CTRL,
            VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_MODE(9),
            VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_MODE);

    // Transfer calendar to vtss_state, so that it can be printed on request.
    VTSS_MEMCPY(vtss_state->port.calendar.cbc, cal, length);
    vtss_state->port.calendar.len     = length;
    vtss_state->port.calendar.manual  = TRUE;
    vtss_state->port.calendar.dynamic = dynamic;

    VTSS_I("Manual calendar applied");
    return VTSS_RC_OK;
}
#endif /* defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_ARCH_JAGUAR_2_B)
// Auto calendar does not supports rates close to 80Gb.  Those must be manually configured.
static vtss_rc jr2_calendar_set(vtss_state_t *vtss_state)
{
    u32 cal_length = 335;
    u8 *cal_p;

    /* Calendar of length 335 found for configuration "TOP_CFG=10" (4x10G 16x2.5G 1x1G): (from TOE) */
    u8 cal_1[] = {
        63,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,    51,49,50,52,18,11,17,10,20, 51,49,50,52,9,16,8,48,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,56, 51,49,50,52,18,11,17,10,    51,49,50,52,9,16,20,8,54,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,63,    51,49,50,52,18,11,21,10,20, 51,49,50,52,17,9,16,8,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,48, 51,49,50,52,18,11,17,10,    51,49,50,52,9,16,20,8,53,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,    51,49,50,52,18,11,17,10,20, 51,49,50,52,9,16,8,63,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,56, 51,49,50,52,18,11,17,10,    51,49,50,52,9,16,20,8,48,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,    51,49,50,52,18,11,17,10,20, 51,49,50,52,9,16,8,54,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,63, 51,49,50,52,18,11,17,10,    51,49,50,52,9,16,20,8,48,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,    51,49,50,52,18,11,17,10,20, 51,49,50,52,9,16,8,56,
        51,49,50,52,15,19,14,23, 51,49,50,52,13,22,12,21,53, 51,49,50,52,18,11,17,10,    51,49,50,52,9,16,20,8};

    /* Calendar of length 335 found for configuration "TOP_CFG=11" (2x10G 24x2.5G 1x1G): (from TOE) */
    u8 cal_2[] = {
        63,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,    49,50,26,22,25,17,9,21,29, 49,50,24,20,28,16,8,48,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,56, 49,50,26,22,25,17,9,21,    49,50,24,29,20,28,16,8,54,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,63,    49,50,10,26,22,25,17,9,21, 49,50,24,29,20,28,16,8,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,48, 49,50,26,22,25,17,9,21,    49,50,24,29,20,28,16,8,53,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,    49,50,26,22,25,17,9,21,29, 49,50,24,20,28,16,8,63,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,56, 49,50,26,22,25,17,9,21,    49,50,24,29,20,28,16,8,48,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,    49,50,26,22,25,17,9,21,29, 49,50,24,20,28,16,8,54,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,63, 49,50,26,22,25,17,9,21,    49,50,24,29,20,28,16,8,48,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,    49,50,26,22,25,17,9,21,29, 49,50,24,20,28,16,8,56,
        49,50,15,19,14,31,13,23, 49,50,27,12,30,11,18,10,53, 49,50,26,22,25,17,9,21,    49,50,24,29,20,28,16,8};

    if (vtss_state->init_conf.mux_mode == VTSS_PORT_MUX_MODE_0) {
        VTSS_I("4x10 + 16x2.5 + NPI is configured for calendar (VTSS_PORT_MUX_MODE_0)");
        cal_p = cal_1; // VTSS_PORT_MUX_MODE_0, 4x10 + 16x2.5 + NPI
    } else {
        VTSS_I("2x10 + 24x2.5 + NPI is configured for calendar (VTSS_PORT_MUX_MODE_1)");
        cal_p = cal_2; // VTSS_PORT_MUX_MODE_1, 2x10 + 24x2.5 + NPI
    }

    return jr2_calendar_do_set(vtss_state, cal_p, cal_length, TRUE, FALSE);
}
#endif /* VTSS_ARCH_JAGUAR_2_B */

#if defined(VTSS_ARCH_JAGUAR_2_C)
static vtss_rc jr2_calendar_set(vtss_state_t *vtss_state)
{
    u32 cal_length;
    u8 *cal_p;

    /* Calendar (from TOE) of length 335 for 4x10G 16x2.5G 1x1G CPU0(53)=750Mb + CPU1(54)=250Mb + VD0(55)=0 VD1(56)=750Mb  */
    u8 cal_1[] = {63,
                  51,49,50,52,15,19,14,23,51,49,50,52,13,22,12,21,51,49,50,52,18,11,17,10,20,
                  51,49,50,52,9,16,8,48,51,49,50,52,15,19,14,23,51,49,50,52,13,22,12,21,53,
                  51,49,50,52,18,11,17,10,51,49,50,52,9,16,20,8,56,51,49,50,52,15,19,14,23,
                  51,49,50,52,13,22,12,63,51,49,50,52,18,11,21,10,20,51,49,50,52,17,9,16,8,
                  51,49,50,52,15,19,14,23,51,49,50,52,13,22,12,21,48,51,49,50,52,18,11,17,10,
                  51,49,50,52,9,16,20,8,56,51,49,50,52,15,19,14,23,51,49,50,52,13,22,12,21,
                  51,49,50,52,18,11,17,10,20,51,49,50,52,9,16,8,63,51,49,50,52,15,19,14,23,
                  51,49,50,52,13,22,12,21,53,51,49,50,52,18,11,17,10,51,49,50,52,9,16,20,8,48,
                  51,49,50,52,15,19,14,23,51,49,50,52,13,22,12,21,51,49,50,52,18,11,17,10,20,
                  51,49,50,52,9,16,8,54,51,49,50,52,15,19,14,23,51,49,50,52,13,22,12,21,63,
                  51,49,50,52,18,11,17,10,51,49,50,52,9,16,20,8,48,51,49,50,52,15,19,14,23,
                  51,49,50,52,13,22,12,21,51,49,50,52,18,11,17,10,20,51,49,50,52,9,16,8,53,
                  51,49,50,52,15,19,14,23,51,49,50,52,13,22,12,21,56,51,49,50,52,18,11,17,10,
                  51,49,50,52,9,16,20,8};

    /* Calendar (from TOE) of length 335 for 2x10G 24x2.5G 1x1G CPU0(53)=750Mb + CPU1(54)=250Mb + VD0(55)=0 VD1(56)=750Mb  */
    u8 cal_2[] = {63,
                  49,50,15,19,14,31,13,23,49,50,27,12,30,11,18,10,49,50,26,22,25,17,9,21,29,
                  49,50,24,20,28,16,8,48,49,50,15,19,14,31,13,23,49,50,27,12,30,11,18,10,56,
                  49,50,26,22,25,17,9,21,49,50,24,29,20,28,16,8,53,49,50,15,19,14,31,13,23,
                  49,50,27,12,30,11,18,63,49,50,10,26,22,25,17,9,21,49,50,24,29,20,28,16,8,
                  49,50,15,19,14,31,13,23,49,50,27,12,30,11,18,10,48,49,50,26,22,25,17,9,21,
                  49,50,24,29,20,28,16,8,53,49,50,15,19,14,31,13,23,49,50,27,12,30,11,18,10,
                  49,50,26,22,25,17,9,21,29,49,50,24,20,28,16,8,63,49,50,15,19,14,31,13,23,
                  49,50,27,12,30,11,18,10,56,49,50,26,22,25,17,9,21,49,50,24,29,20,28,16,8,48,
                  49,50,15,19,14,31,13,23,49,50,27,12,30,11,18,10,49,50,26,22,25,17,9,21,29,
                  49,50,24,20,28,16,8,54,49,50,15,19,14,31,13,23,49,50,27,12,30,11,18,10,63,
                  49,50,26,22,25,17,9,21,49,50,24,29,20,28,16,8,48,49,50,15,19,14,31,13,23,
                  49,50,27,12,30,11,18,10,49,50,26,22,25,17,9,21,29,49,50,24,20,28,16,8,56,
                  49,50,15,19,14,31,13,23,49,50,27,12,30,11,18,10,53,49,50,26,22,25,17,9,21,
                  49,50,24,29,20,28,16,8};

    /* Calendar (from TOE) of length 373 for 4x10G + 48x1G + NPI + CPU0(53)=750Mb + CPU1(54)=250Mb + VD0(55)/VD1(56)=1G.  */
    u8 cal_3[] = {63,
                  51,49,50,52,15,35,39,47,38,51,49,50,52,46,34,14,33,37,51,49,50,52,13,45,48,36,12,
                  51,49,50,52,44,32,43,23,27,7,51,49,50,52,3,19,31,11,22,51,49,50,52,42,6,26,2,30,
                  51,49,50,52,18,10,5,25,17,9,51,49,50,52,29,21,41,1,8,51,49,50,52,55,4,0,28,56,
                  51,49,50,52,40,16,20,53,24,63,51,49,50,52,15,35,39,47,38,51,49,50,52,46,34,14,33,37,
                  51,49,50,52,13,45,48,36,12,54,51,49,50,52,44,32,43,23,27,51,49,50,52,7,3,19,31,11,
                  51,49,50,52,42,22,6,26,2,30,51,49,50,52,18,10,5,25,9,51,49,50,52,17,21,29,41,1,
                  51,49,50,52,8,55,4,0,28,56,51,49,50,52,40,16,20,53,63,51,49,50,52,15,35,39,47,38,
                  51,49,50,52,46,34,14,33,37,24,51,49,50,52,13,45,48,36,12,51,49,50,52,44,32,43,23,27,
                  51,49,50,52,7,3,19,31,11,22,51,49,50,52,42,6,26,2,30,51,49,50,52,18,10,5,25,9,
                  51,49,50,52,17,21,29,41,1,8,51,49,50,52,55,4,0,28,56,51,49,50,52,40,16,20,53,63,
                  51,49,50,52,15,35,39,47,38,24,51,49,50,52,46,34,14,33,37,51,49,50,52,13,45,48,36,12,
                  51,49,50,52,44,32,43,23,27,7,51,49,50,52,3,19,31,11,22,51,49,50,52,42,6,26,2,30,
                  51,49,50,52,18,10,5,25,17,9,51,49,50,52,29,21,41,1,8,51,49,50,52,55,4,0,28,
                  56,51,49,50,52,40,16,20,53,24};

    if (vtss_state->init_conf.mux_mode == VTSS_PORT_MUX_MODE_0) {
        VTSS_I("4x10 + 16x2.5 + NPI is configured for calendar (VTSS_PORT_MUX_MODE_0)");
        cal_length = 335;
        cal_p = cal_1;
    } else if (vtss_state->init_conf.mux_mode == VTSS_PORT_MUX_MODE_1) {
        VTSS_I("2x10 + 24x2.5 + NPI is configured for calendar (VTSS_PORT_MUX_MODE_1)");
        cal_length = 335;
        cal_p = cal_2;
    } else if (vtss_state->init_conf.mux_mode == VTSS_PORT_MUX_MODE_2) {
        VTSS_I("4x10 + 48x1 + NPI is configured for calendar (VTSS_PORT_MUX_MODE_2)");
        cal_length = 373;
        cal_p = cal_3;
    } else {
        VTSS_E("Calendar '%d' not supported",vtss_state->init_conf.mux_mode);
        return VTSS_RC_ERROR;
    }

    return jr2_calendar_do_set(vtss_state, cal_p, cal_length, TRUE, FALSE);
}
#endif /* VTSS_ARCH_JAGUAR_2_C */

#if defined(VTSS_CALENDAR_CALC)
#if defined(VTSS_ARCH_SERVAL_T)
#define CBC_IDLE 15
#elif defined(VTSS_ARCH_JAGUAR_2_C)
#define CBC_IDLE 63
#endif /* defined(VTSS_ARCH_SERVAL_T/VTSS_ARCH_JAGUAR_2_C) */
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
typedef enum {
    CBC_PORT_TYPE_ETH,
    CBC_PORT_TYPE_VD,
    CBC_PORT_TYPE_CPU,
    CBC_PORT_TYPE_IDLE,
    CBC_PORT_TYPE_LAST
} cbc_port_type_t;
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
typedef enum {
    CBC_SPEED_NA,
    CBC_SPEED_1000,
    CBC_SPEED_2500,
    CBC_SPEED_10000,
    CBC_SPEED_LAST
} cbc_speed_t;
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
typedef struct {
    u32             taxi_num;
    cbc_port_type_t port_type;
    u32             min_slot_dist;
    u32             max_line_speed; // Mbps
    u32             min_cbc_bw;     // Mbps
    u32             max_cbc_bw;     // Mbps
    BOOL            best_effort;
} cbc_rtl_port_cfg_t;
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
typedef struct {
    u32                fc_latency_cycles;
    u32                cbc_len;
    u32                max_bw;
    u32                clk_period_ps;
    u32                dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_LAST][CBC_SPEED_LAST]; // Scaled by a factor 100
    u32                dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_LAST][CBC_SPEED_LAST]; // Scaled by a factor 100
    cbc_rtl_port_cfg_t port_cfg[CBC_IDLE + 1];
} cbc_rtl_cfg_t;
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
typedef struct cbc_req_port_cfg_s {
    u32  bw; // Requested B/W in Mbps in steps of 250 Mbps

    // Filled in by calculator
    u32                       slot_cnt;
    cbc_port_type_t           port_type;
    u32                       ideal_slot_dist_mul_1000; // Multiplied by 1000 to get rid of decimals
    u32                       eth_speed; // Mbps
    u32                       chip_port;
    struct cbc_req_port_cfg_s *next_port_in_grp;
    struct cbc_req_port_cfg_s *next_port_in_taxi;
} cbc_req_port_cfg_t;
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
typedef struct {
    cbc_req_port_cfg_t port_cfg[CBC_IDLE + 1];
} cbc_req_cfg_t;
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
#define CBC_SLOT_FREE 255
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
#if defined(VTSS_ARCH_SERVAL_T)
static vtss_rc jr2_calendar_rtl_cfg_get(vtss_state_t *vtss_state, cbc_rtl_cfg_t *rtl_cfg)
{
    u32                 max_bw_1g, max_bw_2g5, min_slot_dist_default = 5;
    cbc_rtl_port_cfg_t  *port_cfg;
    vtss_phys_port_no_t chip_port;

    VTSS_MEMSET(rtl_cfg, 0, sizeof(*rtl_cfg));
    rtl_cfg->fc_latency_cycles = 57;
    rtl_cfg->cbc_len           = 209; // 4 * 52.5 - 1
    rtl_cfg->max_bw            = 52250;
    rtl_cfg->clk_period_ps     = 6400; // 156.25 MHz

#define FFL_DSM_BUF_WM_1G    117
#define FFL_DSM_BUF_WM_2G5   117
#define FFL_DSM_BUF_WM_10G   201
#define FFL_DSM_BUF_SIZE_1G  288
#define FFL_DSM_BUF_SIZE_2G5 288
#define FFL_DSM_BUF_SIZE_10G 576
    // This is scaled by a factor of 100.
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_1000]  =   4 * 100 * FFL_DSM_BUF_WM_1G;
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_2500]  =   4 * 100 * FFL_DSM_BUF_WM_2G5;
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_10000] =   4 * 100 * FFL_DSM_BUF_WM_10G;
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_VD] [CBC_SPEED_NA]    = 512 * 100; // 16 * 64 / 2
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_CPU][CBC_SPEED_NA]    =   4 * 100 * FFL_DSM_BUF_WM_1G;

    // This is scaled by a factor of 100.
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_1000]  = (4 * 100 * (FFL_DSM_BUF_SIZE_1G  - FFL_DSM_BUF_WM_1G))  / 208; // (4 * (288 - 117)) / 208 = 1.75
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_2500]  = (4 * 100 * (FFL_DSM_BUF_SIZE_2G5 - FFL_DSM_BUF_WM_2G5)) / 208; // (4 * (288 - 117)) / 208 = 1.75
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_10000] = (4 * 100 * (FFL_DSM_BUF_SIZE_10G - FFL_DSM_BUF_WM_10G)) / 208; // (4 * (576 - 201)) / 208 = 7.2115
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_VD] [CBC_SPEED_NA]    =  8 * 100; // 16 / 2
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_CPU][CBC_SPEED_NA]    = (4 * 100 * (FFL_DSM_BUF_SIZE_1G  - FFL_DSM_BUF_WM_1G))  / 208; // (4 * (288 - 117)) / 208 = 1.75
#undef FFL_DSM_BUF_WM_1G
#undef FFL_DSM_BUF_WM_2G5
#undef FFL_DSM_BUF_WM_10G
#undef FFL_DSM_BUF_SIZE_1G
#undef FFL_DSM_BUF_SIZE_2G5
#undef FFL_DSM_BUF_SIZE_10G

#define MAX_SPEED_FACTOR 1367 /* 64 / ((172 - 28 + 1 - 42) / 2) * 1.1 = 1.36699 */
    max_bw_1g  = (1000 * MAX_SPEED_FACTOR) / 1000;
    max_bw_2g5 = (2500 * MAX_SPEED_FACTOR) / 1000;
#undef MAX_SPEED_FACTOR

    for (chip_port = 0; chip_port <= 10; chip_port++) {
        port_cfg = &rtl_cfg->port_cfg[chip_port];

        port_cfg->port_type     = CBC_PORT_TYPE_ETH;
        port_cfg->min_slot_dist = min_slot_dist_default;

        if (chip_port == 2 || chip_port == 3 || chip_port == 7 || chip_port == 8 || chip_port == 10) {
            port_cfg->taxi_num = 1;
        } else {
            port_cfg->taxi_num = 0;
        }

        if (chip_port >= 9) {
            port_cfg->max_line_speed = 10000;
            port_cfg->max_cbc_bw     = rtl_cfg->max_bw / port_cfg->min_slot_dist;
        } else if (chip_port >= 2) {
            port_cfg->max_line_speed = 2500;
            port_cfg->max_cbc_bw     = max_bw_2g5;
        } else {
            port_cfg->max_line_speed = 1000;
            port_cfg->max_cbc_bw     = max_bw_1g;
        }
    }

    port_cfg = &rtl_cfg->port_cfg[VTSS_CHIP_PORT_CPU_0];
    port_cfg->taxi_num       =    2;
    port_cfg->port_type      = CBC_PORT_TYPE_CPU;
    port_cfg->min_slot_dist  = min_slot_dist_default;
    port_cfg->max_line_speed = 1000;
    port_cfg->max_cbc_bw     = 1000;
    port_cfg->min_cbc_bw     =  750;

    port_cfg = &rtl_cfg->port_cfg[VTSS_CHIP_PORT_CPU_1];
    port_cfg->taxi_num       =    2;
    port_cfg->port_type      = CBC_PORT_TYPE_CPU;
    port_cfg->min_slot_dist  = min_slot_dist_default;
    port_cfg->max_line_speed = 1000;
    port_cfg->max_cbc_bw     = 1000;

    port_cfg = &rtl_cfg->port_cfg[VTSS_CHIP_PORT_VD0];
    port_cfg->taxi_num       =   90;
    port_cfg->port_type      = CBC_PORT_TYPE_VD;
    port_cfg->min_slot_dist  =   14;
    port_cfg->max_line_speed = rtl_cfg->max_bw / port_cfg->min_slot_dist; // 7464
    port_cfg->max_cbc_bw     = port_cfg->max_line_speed;
    port_cfg->best_effort    = TRUE;

    port_cfg = &rtl_cfg->port_cfg[VTSS_CHIP_PORT_VD1];
    port_cfg->taxi_num       =   91;
    port_cfg->port_type      = CBC_PORT_TYPE_VD;
    port_cfg->min_slot_dist  = min_slot_dist_default;
    port_cfg->max_line_speed = rtl_cfg->max_bw / port_cfg->min_slot_dist; // 10450
    port_cfg->max_cbc_bw     = port_cfg->max_line_speed;
    port_cfg->best_effort    = TRUE;

    port_cfg = &rtl_cfg->port_cfg[CBC_IDLE];
    port_cfg->taxi_num       =    92;
    port_cfg->port_type      = CBC_PORT_TYPE_IDLE;
    port_cfg->min_slot_dist  =     1;
    port_cfg->max_line_speed = 10000;
    port_cfg->max_cbc_bw     = 10000;

    return VTSS_RC_OK;
}
#else
// JR2
static vtss_rc jr2_calendar_rtl_cfg_get(vtss_state_t *vtss_state, cbc_rtl_cfg_t *rtl_cfg)
{
    u32                 max_bw_1g, max_bw_2g5, min_slot_dist_default = 7;
    cbc_rtl_port_cfg_t  *port_cfg;
    vtss_phys_port_no_t chip_port;

    VTSS_MEMSET(rtl_cfg, 0, sizeof(*rtl_cfg));

    rtl_cfg->fc_latency_cycles = 40;
    rtl_cfg->cbc_len           = 335;
    rtl_cfg->max_bw            = 83750;
    rtl_cfg->clk_period_ps     = 4000; // Default to 250MHz

#if defined(VTSS_ARCH_JAGUAR_2_C)
    if (vtss_state->create.target == VTSS_TARGET_SPARX_IV_90) {
        // Override a few of the default values
        rtl_cfg->cbc_len       = 373;
        rtl_cfg->max_bw        = 93250;
        rtl_cfg->clk_period_ps = 3600; // ~278 MHz
    }
#endif

    // This is rounded to nearest integer.
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_1000]  = 29867; // 14 * 512 / (8 * 3) = 298.6667
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_2500]  = 29867; // 14 * 512 / (8 * 3) = 298.6667
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_10000] = 49067; // 23 * 512 / (8 * 3) = 490.6667
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_VD] [CBC_SPEED_NA]    = 34133; // 16 *  64 / (1 * 3) = 341.3333
    rtl_cfg->dsm_bytes_below_wm_mul_100[CBC_PORT_TYPE_CPU][CBC_SPEED_NA]    = 29867; // 14 * 512 / (8 * 3) = 298.6667

    // This is scaled by a factor of 100.
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_1000]  =  287; // 14 * 512 * 2 / (8 * 208 * 3) =  2.8718
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_2500]  =  287; // 14 * 512 * 2 / (8 * 208 * 3) =  2.8718
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_ETH][CBC_SPEED_10000] =  472; // 23 * 512 * 2 / (8 * 208 * 3) =  4.7179
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_VD] [CBC_SPEED_NA]    = 1067; // 16       * 2 / (          3) = 10.6667
    rtl_cfg->dsm_cells_above_wm_mul_100[CBC_PORT_TYPE_CPU][CBC_SPEED_NA]    = 1067; // 16       * 2 / (          3) = 10.6667

#define MAX_SPEED_FACTOR 1367 /* 64 / ((172 - 28 + 1 - 42) / 2) * 1.1 = 1.36699 */
    max_bw_1g  = (1000 * MAX_SPEED_FACTOR) / 1000;
    max_bw_2g5 = (2500 * MAX_SPEED_FACTOR) / 1000;
#undef MAX_SPEED_FACTOR

    for (chip_port = 0; chip_port <= 52; chip_port++) {
        port_cfg = &rtl_cfg->port_cfg[chip_port];

        port_cfg->port_type     = CBC_PORT_TYPE_ETH;
        port_cfg->min_slot_dist = min_slot_dist_default;

        if (chip_port >= 8 && chip_port <= 11) {
            port_cfg->taxi_num = 3;
        } else if (chip_port >= 44 && chip_port <= 47) {
            port_cfg->taxi_num = 2;
        } else if (chip_port == 48) {
            port_cfg->taxi_num = 7;
        } else if (chip_port == 49) {
            port_cfg->taxi_num = 6;
        } else if (chip_port == 50) {
            port_cfg->taxi_num = 7;
        } else if (chip_port == 51) {
            port_cfg->taxi_num = 4;
        } else if (chip_port == 52) {
            port_cfg->taxi_num = 5;
        } else if (chip_port >= 32) {
           port_cfg->taxi_num = (chip_port - 32) / 4;
        } else {
           port_cfg->taxi_num = chip_port / 4;
        }

        if (chip_port >= 8 && chip_port <= 31) {
            port_cfg->max_line_speed = 2500;
            port_cfg->max_cbc_bw     = max_bw_2g5;
        } else if (chip_port >= 49) {
            port_cfg->max_line_speed = 10000;
            port_cfg->max_cbc_bw     = rtl_cfg->max_bw / port_cfg->min_slot_dist; // Make it independent of clock speed by calculating it.
        } else {
            port_cfg->max_line_speed = 1000;
            port_cfg->max_cbc_bw     = max_bw_1g;
        }
    }

    port_cfg = &rtl_cfg->port_cfg[VTSS_CHIP_PORT_CPU_0];
    port_cfg->taxi_num       =    8;
    port_cfg->port_type      = CBC_PORT_TYPE_CPU;
    port_cfg->min_slot_dist  = min_slot_dist_default;
    port_cfg->max_line_speed = 1000;
    port_cfg->min_cbc_bw     =  750;
    port_cfg->max_cbc_bw     = 1000;

    port_cfg = &rtl_cfg->port_cfg[VTSS_CHIP_PORT_CPU_1];
    port_cfg->taxi_num       =    8;
    port_cfg->port_type      = CBC_PORT_TYPE_CPU;
    port_cfg->min_slot_dist  = min_slot_dist_default;
    port_cfg->max_line_speed = 1000;
    port_cfg->max_cbc_bw     = 1000;

    port_cfg = &rtl_cfg->port_cfg[VTSS_CHIP_PORT_VD0];
    port_cfg->taxi_num       =   90;
    port_cfg->port_type      = CBC_PORT_TYPE_VD;
    port_cfg->min_slot_dist  =    9;
    port_cfg->max_line_speed = 9333;
    port_cfg->max_cbc_bw     = rtl_cfg->max_bw / port_cfg->min_slot_dist; // Make it independent of clock speed by calculating it.
    port_cfg->best_effort    = TRUE;

    port_cfg = &rtl_cfg->port_cfg[VTSS_CHIP_PORT_VD1];
    port_cfg->taxi_num       =   91;
    port_cfg->port_type      = CBC_PORT_TYPE_VD;
    port_cfg->min_slot_dist  = min_slot_dist_default;
    port_cfg->max_line_speed = 12000;
    port_cfg->max_cbc_bw     = rtl_cfg->max_bw / port_cfg->min_slot_dist; // Make it independent of clock speed by calculating it.
    port_cfg->best_effort    = TRUE;

    port_cfg = &rtl_cfg->port_cfg[CBC_IDLE];
    port_cfg->taxi_num       =    92;
    port_cfg->port_type      = CBC_PORT_TYPE_IDLE;
    port_cfg->min_slot_dist  =     1;
    port_cfg->max_line_speed = 10000;
    port_cfg->max_cbc_bw     = 10000;

    return VTSS_RC_OK;
}
#endif /* (!)defined(VTSS_ARCH_SERVAL_T) */
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_calendar_req_cfg_init(vtss_state_t *vtss_state, cbc_req_cfg_t *req_cfg)
{
    u32 vd1_bw = vtss_state->init_conf.loopback_bw_mbps;

    VTSS_MEMSET(req_cfg, 0, sizeof(*req_cfg));

    // Add IDLE B/W. This is to ensure the CPU time for register access.
    req_cfg->port_cfg[CBC_IDLE].bw             = 1000;

    // Also the CPU must be assigned some B/W. We cannot extract with more than
    // 750 Mbps, so no need to set the higher. VTSS_CHIP_PORT_CPU_1 is used when
    // VTSS_CHIP_PORT_CPU_0 is overwhelmed with frames (throttling), so let's
    // flush with 250 Mbps.
    req_cfg->port_cfg[VTSS_CHIP_PORT_CPU_0].bw =  750;
    req_cfg->port_cfg[VTSS_CHIP_PORT_CPU_1].bw =  250;

    // Add user-requested loopback B/W to VD1. Must be in multiples of 250 Mbps
    req_cfg->port_cfg[VTSS_CHIP_PORT_VD1].bw = 250 * (vd1_bw / 250);

    // When it comes to VD0 (multicast), we don't assign anything in the calendar,
    // because that could lead to failure to calculate a new calendar. Instead,
    // we assign the idle periods of the calendar to VD0. We do that when the
    // calendar is successfully applied.

    // (Update) Due to BZ#24522 we must assign at least 1 slot to VD0
    req_cfg->port_cfg[VTSS_CHIP_PORT_VD0].bw = 250;

    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_calendar_req_cfg_get(vtss_state_t *vtss_state, cbc_rtl_cfg_t *rtl_cfg, cbc_req_cfg_t *req_cfg)
{
    vtss_port_no_t port_no;

    // Get CPU_0, CPU_1, and VD1 B/Ws.
    VTSS_RC(jr2_calendar_req_cfg_init(vtss_state, req_cfg));

    // Look into the port map to get the front port B/Ws.
    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        jr2_cal_speed_t spd;
        i32             chip_port;

        spd = jr2_cal_speed_get(vtss_state, port_no, &chip_port);

        if (chip_port == CHIP_PORT_UNUSED || spd == JR2_CAL_SPEED_NONE) {
            continue;
        }

        req_cfg->port_cfg[chip_port].bw = spd == JR2_CAL_SPEED_1G ? 1000 : spd == JR2_CAL_SPEED_2G5 ? 2500 : 10000;
    }

    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static BOOL jr2_cbc_slot_free(vtss_calendar_t *cbc, u32 pos)
{
    return (cbc->cbc[pos] == CBC_SLOT_FREE);
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static u32 jr2_cbc_pos_calc(int cbc_len, int pos)
{
    pos += cbc_len;

    // Do looped modulus on SIGNED integers, because pos may be -1 here.
    // If we did it unsigned, it would take quite some time for the
    // following loop to terminate.
    while (pos >= cbc_len) {
        pos -= cbc_len;
    }

    return pos;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_cbc_dist(cbc_rtl_cfg_t *rtl_cfg, vtss_calendar_t *cbc, cbc_req_port_cfg_t *port_cfg, u32 pos_left, u32 pos_right, u32 *dist)
{
    if (!jr2_cbc_slot_free(cbc, pos_left) && cbc->cbc[pos_left] != port_cfg->chip_port) {
        VTSS_E("Internal Error: port = %u, CBC[port_left] = %hu", port_cfg->chip_port, cbc->cbc[pos_left]);
        return VTSS_RC_ERROR;
    }

    if (pos_right == pos_left) {
        *dist = 0;
        return VTSS_RC_OK;
    }

    // Normal distance calculation
    if (pos_right > pos_left) {
        *dist = pos_right - pos_left;
    } else {
        *dist = rtl_cfg->cbc_len + pos_right - pos_left;
    }

    if (*dist > rtl_cfg->cbc_len / 2) {
        *dist = rtl_cfg->cbc_len - *dist;
    }

    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_cbc_slot_acceptable(cbc_rtl_cfg_t *rtl_cfg, cbc_req_port_cfg_t *port_cfg, vtss_calendar_t *cbc, u32 pos, BOOL *acceptable)
{
    u32 taxi_num = rtl_cfg->port_cfg[port_cfg->chip_port].taxi_num;
    u32 pos_prv  = jr2_cbc_pos_calc(rtl_cfg->cbc_len, pos - 1);
    u32 pos_nxt  = jr2_cbc_pos_calc(rtl_cfg->cbc_len, pos + 1);
    u32 i;

    // Taxi check
    if (cbc->cbc[pos_prv] != CBC_SLOT_FREE && rtl_cfg->port_cfg[cbc->cbc[pos_prv]].taxi_num == taxi_num) {
        // Taxi number conflict with previous slot
        *acceptable = FALSE;
        return VTSS_RC_OK;
    }

    if (cbc->cbc[pos_nxt] != CBC_SLOT_FREE && rtl_cfg->port_cfg[cbc->cbc[pos_nxt]].taxi_num == taxi_num) {
        // Taxi number conflict with next slot
        *acceptable = FALSE;
        return VTSS_RC_OK;
    }

    // MIN_SLOT_DIST check
    for (i = 0; i < rtl_cfg->cbc_len; i++) {
        if (cbc->cbc[i] == port_cfg->chip_port) {
            u32 dist;

            VTSS_RC(jr2_cbc_dist(rtl_cfg, cbc, port_cfg, pos, i, &dist));
            if (dist < rtl_cfg->port_cfg[port_cfg->chip_port].min_slot_dist) {
                *acceptable = FALSE;
                return VTSS_RC_OK;
            }
        }
    }

    *acceptable = TRUE;
    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_cbc_assign_slot(cbc_req_port_cfg_t *port_cfg, vtss_calendar_t *cbc, u32 pos)
{
    VTSS_D("Assigning cbc[%u] = %u", pos, port_cfg->chip_port);
    cbc->cbc[pos] = port_cfg->chip_port;
    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_cbc_find_slot(cbc_rtl_cfg_t *rtl_cfg, cbc_req_port_cfg_t *port_cfg, vtss_calendar_t *cbc, u32 pos_ideal, u32 pos_prv, u32 *pos_found)
{
    // Find acceptable slot and return slot number.
    BOOL best_effort = rtl_cfg->port_cfg[port_cfg->chip_port].best_effort, acceptable;
    u32  dist_from_ideal, dist_from_ideal_max;

    // Round dist_from_ideal up to gain some flexibility.
    // This may result in illegal CBC, but that should be caught by acceptance check.
    dist_from_ideal_max = (port_cfg->ideal_slot_dist_mul_1000 + 999 - rtl_cfg->port_cfg[port_cfg->chip_port].min_slot_dist * 1000) / 1000;
    if (best_effort) {
        dist_from_ideal_max = rtl_cfg->cbc_len / 2;
    }

    VTSS_D("ideal_slot_dist_mul_1000 = %u, MIN_SLOT_DIST=%u, port=%u, pos_ideal=%u, dist_from_ideal_max=%u ", port_cfg->ideal_slot_dist_mul_1000, rtl_cfg->port_cfg[port_cfg->chip_port].min_slot_dist, port_cfg->chip_port, pos_ideal, dist_from_ideal_max);

    for (dist_from_ideal = 1; dist_from_ideal <= dist_from_ideal_max; dist_from_ideal++) {
        int i;

        // For each dist_from_ideal, try both pos_ideal, pos_ideal - dist_from_ideal and pos_ideal + dist_from_ideal
        for (i = 0; i < 3; i++) {
            u32 pos;

            if (i == 0 && dist_from_ideal > 1) {
                // pos_ideal already checked in very first iteration
                continue;
            }

            pos = jr2_cbc_pos_calc(rtl_cfg->cbc_len, i == 0 ? pos_ideal : i == 1 ? (pos_ideal - dist_from_ideal) : (pos_ideal + dist_from_ideal));

            VTSS_D("Trying %u", pos);

            if (jr2_cbc_slot_free(cbc, pos)) {
                VTSS_RC(jr2_cbc_slot_acceptable(rtl_cfg, port_cfg, cbc, pos, &acceptable));
                if (acceptable) {
                    *pos_found = pos;
                    return VTSS_RC_OK;
                }
            }
        }
    }

    // If we get here, no position was found, but caller wants us to return VTSS_RC_OK because we #accept_failure.
    *pos_found = -1;
    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_cbc_free_port_slots(cbc_rtl_cfg_t *rtl_cfg, cbc_req_port_cfg_t *port_cfg, vtss_calendar_t *cbc)
{
    int pos;

    for (pos = 0; pos < rtl_cfg->cbc_len; pos++) {
        if (cbc->cbc[pos] == port_cfg->chip_port) {
            cbc->cbc[pos] = CBC_SLOT_FREE;
        }
    }

    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static int jr2_cbc_next_free_slot(cbc_rtl_cfg_t *rtl_cfg, vtss_calendar_t *cbc, int pos)
{
    int i;

    if (++pos < 0 || pos >= rtl_cfg->cbc_len) {
        return -1;
    }

    for (i = pos; i < rtl_cfg->cbc_len; i++) {
        if (jr2_cbc_slot_free(cbc, i)) {
            return i;
        }
    }

    return -1;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_cbc_assign_slots(cbc_rtl_cfg_t *rtl_cfg, cbc_req_port_cfg_t *port_cfg, vtss_calendar_t *cbc)
{
    u32 ideal_slot_dist_mul_1000 = port_cfg->ideal_slot_dist_mul_1000, attempts = 0;
    int pos_start = -1;

    VTSS_D_HEX(cbc->cbc, rtl_cfg->cbc_len);

    while ((pos_start = jr2_cbc_next_free_slot(rtl_cfg, cbc, pos_start)) >= 0) {
        u32  pos_prv, assign_cnt = 1, slot_cnt = port_cfg->slot_cnt;
        BOOL done = TRUE, acceptable;

        attempts++;

        // First slot
        VTSS_RC(jr2_cbc_slot_acceptable(rtl_cfg, port_cfg, cbc, pos_start, &acceptable));
        if (!acceptable) {
            continue;
        }

        VTSS_RC(jr2_cbc_assign_slot(port_cfg, cbc, pos_start));
        slot_cnt--;

        pos_prv = pos_start;
        while (slot_cnt) {
            u32 pos_ideal = jr2_cbc_pos_calc(rtl_cfg->cbc_len, pos_start + (ideal_slot_dist_mul_1000 * assign_cnt) / 1000);
            u32 pos_found = -1;

            VTSS_RC(jr2_cbc_find_slot(rtl_cfg, port_cfg, cbc, pos_ideal, pos_prv, &pos_found));

            if (pos_found != -1) {
                VTSS_RC(jr2_cbc_assign_slot(port_cfg, cbc, pos_found));
                slot_cnt--;
                assign_cnt++;
                pos_prv = pos_found;
            } else {
                VTSS_RC(jr2_cbc_free_port_slots(rtl_cfg, port_cfg, cbc));
                VTSS_D("Failed for port %u in attempt #%u with pos_start = %d", port_cfg->chip_port, attempts, pos_start);
                done = FALSE;
                break;
            }
        }

        if (done) {
            return VTSS_RC_OK;
        }
    }

    // If we get here, we couldn't fit the slots for this port into the cbc.
    VTSS_E("Port %u: Failed to find a free slot in %u attempts", port_cfg->chip_port, attempts);
    return VTSS_RC_ERROR;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static cbc_speed_t jr2_cbc_speed_to_enum(cbc_port_type_t port_type, u32 line_speed)
{
    if (port_type != CBC_PORT_TYPE_ETH) {
        // This is the expected enumeration to return when
        // dsm_bytes_below_wm_mul_100[] and dsm_cells_above_wm_mul_100[] are
        // indexed for non-ethernet ports (CPU and VD ports).
        return CBC_SPEED_NA;
    }

    // For Ethernet ports, we support three speeds.
    switch (line_speed) {
    case 1000:
        return CBC_SPEED_1000;

    case 2500:
        return CBC_SPEED_2500;

    case 10000:
        return CBC_SPEED_10000;

    default:
        VTSS_E("Unable to convert %u to a speed enum. Assuming CBC_SPEED_1G", line_speed);
        return CBC_SPEED_1000;
    }
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_calendar_do_calc(cbc_rtl_cfg_t *rtl_cfg, cbc_req_cfg_t *req_cfg, vtss_calendar_t *cbc)
{
    typedef struct {
        u32 use_cnt;
        cbc_req_port_cfg_t *port_list;
    } taxi_ports_t;

    typedef struct {
        u32 bw;
        cbc_req_port_cfg_t *port_list;
    } cbc_grp_t;

    u32                 tot_bw = 0, bw, min_cbc_bw, max_cbc_bw, tot_slot_cnt = 0, port_cnt_1g = 0, port_cnt_2g5 = 0, port_cnt_10g = 0, port_cnt_vd = 0, port_cnt_cpu = 0, port_cnt_idle = 0;
    vtss_phys_port_no_t chip_port;
    cbc_req_port_cfg_t  *port_cfg, *p;
    cbc_grp_t           cbc_grps[CBC_IDLE + 1], *cbc_grp; // We can in principle have CBC_IDLE different B/Ws.
    int                 i, j;

    if (rtl_cfg->cbc_len > VTSS_CALENDAR_LEN_MAX) {
        VTSS_E("CBC Length");
        return VTSS_RC_ERROR;
    }

    // Check that port BW does not exceed MAX_CBC_BW
    // and that port BW is not below MIN_CBC_BW (if specified).
    // Also calculate the number of slots for each port and check
    // that this is an integer.
    for (chip_port = 0; chip_port <= CBC_IDLE; chip_port++) {
        port_cfg = &req_cfg->port_cfg[chip_port];

        // Save the chip port number for later, where it's put into a list.
        port_cfg->chip_port = chip_port;

        bw = port_cfg->bw;

        if (!bw) {
            // Port doesn't request any B/W
            continue;
        }

        // Check that we get an integral number of slots.
        // The req_cfg->port_cfg[].bw must be specified in steps of 250 Mbps.
        if (((bw * rtl_cfg->cbc_len) % rtl_cfg->max_bw) != 0) {
            VTSS_E("Either CBC_LEN (%u) is not set to match MAX_BW (%u) or specified BW (%u) for port %u is not in steps of 250 Mbps", rtl_cfg->cbc_len, rtl_cfg->max_bw, bw, chip_port);
            return VTSS_RC_ERROR;
        }

        min_cbc_bw = rtl_cfg->port_cfg[chip_port].min_cbc_bw;
        max_cbc_bw = rtl_cfg->port_cfg[chip_port].max_cbc_bw;

        if (min_cbc_bw && bw < min_cbc_bw) {
            VTSS_E("Port %u: Bandwidth (%u) is below MIN_CBC_BW = %u", chip_port, bw, min_cbc_bw);
            return VTSS_RC_ERROR;
        }

        if (bw > max_cbc_bw) {
            VTSS_E("Port %u: Bandwidth (%u) exceeds MAX_CBC_BW = %u", chip_port, bw, max_cbc_bw);
            return VTSS_RC_ERROR;
        }

        port_cfg->eth_speed                = bw >= 10000 ? 10000 : bw >= 2500 ? 2500 : 1000;
        port_cfg->slot_cnt                 = (bw * rtl_cfg->cbc_len) / rtl_cfg->max_bw;
        port_cfg->port_type                = rtl_cfg->port_cfg[chip_port].port_type;
        port_cfg->ideal_slot_dist_mul_1000 = (1000 * rtl_cfg->cbc_len) / port_cfg->slot_cnt;

        tot_slot_cnt += port_cfg->slot_cnt;

        switch (port_cfg->port_type) {
        case CBC_PORT_TYPE_ETH:
            switch (port_cfg->eth_speed) {
            case 1000:
               port_cnt_1g++;
               break;

             case 2500:
                 port_cnt_2g5++;
                 break;

             case 10000:
                 port_cnt_10g++;
                 break;

             default:
                 VTSS_E("Internal error (port = %u)", chip_port);
                 return VTSS_RC_ERROR;
             }

             break;

        case CBC_PORT_TYPE_VD:
            port_cnt_vd++;
            break;

        case CBC_PORT_TYPE_CPU:
            port_cnt_cpu++;
            break;

        case CBC_PORT_TYPE_IDLE:
            port_cnt_idle++;
            break;

        default:
            VTSS_E("Unknown port type (%d)", port_cfg->port_type);
            return VTSS_RC_ERROR;
        }

        tot_bw += bw;
        VTSS_D("Port %u contributes with %u Mbps. Total B/W so far = %u", chip_port, bw, tot_bw);
    }

    VTSS_I("Total/Max B/W = %u/%u Mbps. Distribution: %ux10G, %ux2.5G, %ux1G, %uxCPU, %uxVD, %uxIDLE", tot_bw, rtl_cfg->max_bw, port_cnt_10g, port_cnt_2g5, port_cnt_1g, port_cnt_cpu, port_cnt_vd, port_cnt_idle);
    VTSS_I("VD0 = %u Mbps, VD1 = %u Mbps, CPU0 = %u Mbps, CPU1 = %u Mbps, IDLE = %u Mbps", req_cfg->port_cfg[VTSS_CHIP_PORT_VD0].bw, req_cfg->port_cfg[VTSS_CHIP_PORT_VD1].bw, req_cfg->port_cfg[VTSS_CHIP_PORT_CPU_0].bw, req_cfg->port_cfg[VTSS_CHIP_PORT_CPU_1].bw, req_cfg->port_cfg[CBC_IDLE].bw);

    // Check total BW
    if (tot_bw > rtl_cfg->max_bw) {
        VTSS_E("Total bandwidth (%u) exceeds MAX_BW = %u", tot_bw, rtl_cfg->max_bw);
        return VTSS_RC_ERROR;
    }

    if (tot_slot_cnt != (rtl_cfg->cbc_len * tot_bw) / rtl_cfg->max_bw) {
        VTSS_E("Internal Error: tot_slot_cnt = %u, cbc_len = %u, tot_bw = %u, max_bw = %u", tot_slot_cnt, rtl_cfg->cbc_len, tot_bw, rtl_cfg->max_bw);
        return VTSS_RC_ERROR;
    }

    // Initialize all CBC slots to -1 (=unassigned)
    VTSS_MEMSET(cbc->cbc, CBC_SLOT_FREE, sizeof(cbc->cbc));

    // Assign bandwidths in reverse numerical order.
    VTSS_MEMSET(cbc_grps, 0, sizeof(cbc_grps));

    // Populate cbc_grps. First one is IDLE
    cbc_grps[0].bw        =  req_cfg->port_cfg[CBC_IDLE].bw;
    cbc_grps[0].port_list = &req_cfg->port_cfg[CBC_IDLE];

    for (chip_port = 0; chip_port < CBC_IDLE /* do not include IDLE */; chip_port++) {
        BOOL inserted = FALSE;

        port_cfg = &req_cfg->port_cfg[chip_port];
        bw       = port_cfg->bw;

        if (!bw) {
            continue;
        }

        // Search for insertion point.
        for (i = 1; i < VTSS_ARRSZ(cbc_grps); i++) {
            cbc_grp = &cbc_grps[i];

            if (!cbc_grp->bw) {
                // End of list without any matches. Stop.
                break;
            }

            if (bw == cbc_grp->bw) {
                // Append this port to the list. It would have been faster to
                // prepend, but in order to be able to match the result with
                // an offline-tool (which appends), we do the same.
                p = cbc_grp->port_list;

                while (p->next_port_in_grp) {
                    p = p->next_port_in_grp;
                }

                p->next_port_in_grp = port_cfg;
                inserted = TRUE;
                break;
            }
        }

        if (!inserted) {
            // Find insertion place
            for (i = 1; i < VTSS_ARRSZ(cbc_grps); i++) {
                cbc_grp = &cbc_grps[i];

                if (bw > cbc_grp->bw) {
                    // Insert here. First move the rest.
                    for (j = VTSS_ARRSZ(cbc_grps) - 1; j > i; j--) {
                        cbc_grp_t *g = &cbc_grps[j];
                        *g = cbc_grps[j - 1];
                    }

                    // And use the now vacant entry
                    cbc_grp->bw = bw;
                    cbc_grp->port_list = port_cfg;
                    break;
                }
            }
        }
    }

    // Print some trace
    for (i = 0; i < VTSS_ARRSZ(cbc_grps); i++) {
        cbc_grp = &cbc_grps[i];

        if (!cbc_grp->bw) {
           break;
        }

        VTSS_D("cbc_grp[%d].bw = %u", i, cbc_grp->bw);

        port_cfg = cbc_grp->port_list;
        while (port_cfg) {
            VTSS_D("  Port %u", port_cfg->chip_port);
            port_cfg = port_cfg->next_port_in_grp;
        }
    }

    // Process groups
    for (i = 0; i < VTSS_ARRSZ(cbc_grps); i++) {
        taxi_ports_t taxi_ports[100], *t;
        u32          taxi_num, total_use_cnt = 0;
        int          taxi_num_prv;

        cbc_grp = &cbc_grps[i];

        if (!cbc_grp->bw) {
            // Done.
            break;
        }

        VTSS_MEMSET(taxi_ports, 0, sizeof(taxi_ports));

        // Within group, further group ports according to which Taxi ring they belong to
        p = cbc_grp->port_list;
        while (p) {
            // Just insert by taxi-num, so that we get the same behavior as the offline tool
            taxi_num = rtl_cfg->port_cfg[p->chip_port].taxi_num;

            if (taxi_num >= VTSS_ARRSZ(taxi_ports)) {
                VTSS_E("Found a taxi number (%u) greater than the allocated array (%u entries)", taxi_num, (u32)VTSS_ARRSZ(taxi_ports));
                return VTSS_RC_ERROR;
            }

            t = &taxi_ports[taxi_num];
            t->use_cnt++;
            total_use_cnt++;

            // Prepend this port to the list to resemble what
            // the offline tool does (it pops from an array, which
            // means that it takes the last element first). Below,
            // we take the first element, so we prepend rather
            // than append.
            p->next_port_in_taxi = t->port_list;
            t->port_list = p;

            // Prepare for next iteration
            p = p->next_port_in_grp;
        }

        // Print some trace
        for (j = 0; j < VTSS_ARRSZ(taxi_ports); j++) {
            t = &taxi_ports[j];
            if (!t->use_cnt) {
                break;
            }

            VTSS_D("taxi_num = %u, use_cnt = %u, (total_use_cnt = %u)", j, t->use_cnt, total_use_cnt);
            port_cfg = t->port_list;
            while (port_cfg) {
                VTSS_D("  Port %u", port_cfg->chip_port);
                port_cfg = port_cfg->next_port_in_taxi;
            }
        }

        // Assign CBC slots
        port_cfg = cbc_grp->port_list;
        taxi_num_prv = -1;
        while (total_use_cnt) {
            u32 taxi_port_cnt_max = 0;
            int taxi_num_nxt = -1;

            // Prioritize taxi rings with the most remaining ports, whilst
            // avoiding assigning for the same taxi-num twice.
            for (j = 0; j < VTSS_ARRSZ(taxi_ports); j++) {
                // Do not break in this loop, because the list
                // may get full of holes as we travese it.
                t = &taxi_ports[j];

                if (t->use_cnt > taxi_port_cnt_max && (taxi_num_prv == -1 || j != taxi_num_prv)) {
                    taxi_port_cnt_max = t->use_cnt;
                    taxi_num_nxt = j;
                }
            }

            if (taxi_num_nxt == -1) {
                // Need to pick taxi_num_prv
                if (taxi_num_prv == -1) {
                    VTSS_E("Internal Error");
                    return VTSS_RC_ERROR;
                }

                taxi_num_nxt = taxi_num_prv;
            }

            if (taxi_num_nxt < 0) {
                // Satisfy Coverity
                VTSS_E("Internal Error");
                return VTSS_RC_ERROR;
            }

            t = &taxi_ports[taxi_num_nxt];
            if (!t->port_list) {
                VTSS_E("Internal Error. port_list is NULL");
                return VTSS_RC_ERROR;
            }

            if (!t->use_cnt) {
                VTSS_E("Internal Error. use_cnt is NULL");
                return VTSS_RC_ERROR;
            }

            port_cfg = t->port_list;
            t->port_list = port_cfg->next_port_in_taxi;
            t->use_cnt--;
            bw = port_cfg->bw;

            VTSS_D("Adding port %u (%u Mbps) to CBC for which taxi_num = %u, use_cnt = %u, slot_cnt = %u", port_cfg->chip_port, port_cfg->bw, taxi_num_nxt, t->use_cnt, port_cfg->slot_cnt);
            VTSS_RC(jr2_cbc_assign_slots(rtl_cfg, port_cfg, cbc));
            taxi_num_prv = taxi_num_nxt;
            total_use_cnt--;
        }
    }

    // Convert unused slots to IDLE
    for (i = 0; i < rtl_cfg->cbc_len; i++) {
        if (cbc->cbc[i] == CBC_SLOT_FREE) {
            cbc->cbc[i] = CBC_IDLE;
        }
    }

    VTSS_I("Calendar of length %u found", rtl_cfg->cbc_len);
    VTSS_I_HEX(cbc->cbc, rtl_cfg->cbc_len);

    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_calendar_check(cbc_rtl_cfg_t *rtl_cfg, cbc_req_cfg_t *req_cfg, vtss_calendar_t *cbc)
{
    u32                 slot_cnt[CBC_IDLE + 1], first_slot[CBC_IDLE + 1], latest_slot[CBC_IDLE + 1], i, pos, dist, base, offset;
    vtss_phys_port_no_t chip_port;
    cbc_req_port_cfg_t  *port_cfg;

    VTSS_MEMSET(slot_cnt, 0, sizeof(slot_cnt));
    VTSS_MEMSET(first_slot, -1, sizeof(first_slot));
    VTSS_MEMSET(latest_slot, -1, sizeof(latest_slot));

    // Create per-port slot count and minimum distances
    for (i = 0; i < rtl_cfg->cbc_len; i++) {
        chip_port = cbc->cbc[i];

        if (chip_port >= VTSS_ARRSZ(rtl_cfg->port_cfg)) {
            VTSS_E("Invalid calendar. Unknown port (%u) in calendar position %u", chip_port, i);
            return VTSS_RC_ERROR;
        }

        slot_cnt[chip_port]++;

        if (first_slot[chip_port] == -1) {
            first_slot[chip_port] = i;
        }

        // MIN_SLOT_DIST compliance - non-wrap-around
        if (latest_slot[chip_port] != -1) {
            VTSS_RC(jr2_cbc_dist(rtl_cfg, cbc, &req_cfg->port_cfg[chip_port], latest_slot[chip_port], i, &dist));
            if (dist < rtl_cfg->port_cfg[chip_port].min_slot_dist) {
                VTSS_E("Port %u has slots %u and %u, which are distanced less than %u slots apart", chip_port, latest_slot[chip_port], i, rtl_cfg->port_cfg[chip_port].min_slot_dist);
                return VTSS_RC_ERROR;
            }
        }

        latest_slot[chip_port] = i;
    }

    // MIN_SLOT_DIST compliance - wrap-around
    // Slot count compliance
    for (chip_port = 0; chip_port <= CBC_IDLE; chip_port++) {
        port_cfg = &req_cfg->port_cfg[chip_port];

        if (first_slot[chip_port] != -1 && latest_slot[chip_port] != -1 && first_slot[chip_port] != latest_slot[chip_port]) {
            VTSS_RC(jr2_cbc_dist(rtl_cfg, cbc, &req_cfg->port_cfg[chip_port], first_slot[chip_port], latest_slot[chip_port], &dist));
            if (dist < rtl_cfg->port_cfg[chip_port].min_slot_dist) {
                VTSS_E("Port %u has slots %u and %u, which are distanced less than %u slots apart", chip_port, first_slot[chip_port], latest_slot[chip_port], rtl_cfg->port_cfg[chip_port].min_slot_dist);
                return VTSS_RC_ERROR;
            }
        }

        if ((chip_port != CBC_IDLE && slot_cnt[chip_port] != port_cfg->slot_cnt) ||
            (chip_port == CBC_IDLE && slot_cnt[chip_port] < port_cfg->slot_cnt)) {
            VTSS_E("Port %u: Found %u slots, expected %u", chip_port, slot_cnt[chip_port], port_cfg->slot_cnt);
            return VTSS_RC_ERROR;
        }
    }

    // Neighboring slots must belong to different Taxi busses
    // Neighboring slots must be assigned to different ports
    for (pos = 0; pos < rtl_cfg->cbc_len; pos++) {
        u32 pos_nxt;
        u32 taxi_num, taxi_num_nxt, chip_port_nxt;

        chip_port = cbc->cbc[pos];

        if (chip_port == CBC_IDLE) {
            continue;
        }

        pos_nxt       = jr2_cbc_pos_calc(rtl_cfg->cbc_len, pos + 1);
        chip_port_nxt = cbc->cbc[pos_nxt];

        if (chip_port == chip_port_nxt) {
            VTSS_E("Positions %u and %u both belong to port %u", pos, pos_nxt, chip_port);
            return VTSS_RC_ERROR;
        }

        taxi_num     = rtl_cfg->port_cfg[chip_port].taxi_num;
        taxi_num_nxt = rtl_cfg->port_cfg[chip_port_nxt].taxi_num;

        if (taxi_num_nxt == taxi_num) {
            VTSS_E("Positions %u and %u both belong to Taxi %u", pos, pos_nxt, taxi_num);
            return VTSS_RC_ERROR;
        }
    }

    // Check cell stop assertion (tail problem)

    // Check that DSM has room for worst case tail
    // For a sliding window of FC_LATENCY_CYCLES / 2 slots in CBC, check
    // that no port has more than dsm_cells_above_wm_mul_100 + 1 slots.
    for (pos = 0; pos < rtl_cfg->cbc_len; pos++) {
        u32 range_end = pos + rtl_cfg->fc_latency_cycles / 2 - 1;

        VTSS_D("Checking range [%u; %u]", pos, range_end);

        // Count slots per port in the range
        VTSS_MEMSET(slot_cnt, 0, sizeof(slot_cnt));
        for (offset = pos; offset <= range_end; offset++) {
            chip_port = cbc->cbc[offset >= rtl_cfg->cbc_len ? offset - rtl_cfg->cbc_len : offset];
            slot_cnt[chip_port]++;
        }

        // Check slot count for each port found in this range
        for (chip_port = 0; chip_port < CBC_IDLE /* exclude IDLE */; chip_port++) {
            u32             line_speed, max_slots_mul_100, slot_cnt_mul_100;
            cbc_port_type_t port_type;

            if (slot_cnt[chip_port] == 0) {
                // Not assigned.
                continue;
            }

            line_speed         = rtl_cfg->port_cfg[chip_port].max_line_speed;
            port_type          = rtl_cfg->port_cfg[chip_port].port_type;
            max_slots_mul_100  = rtl_cfg->dsm_cells_above_wm_mul_100[port_type][jr2_cbc_speed_to_enum(port_type, line_speed)] + 1 * 100;
            slot_cnt_mul_100   = slot_cnt[chip_port] * 100;

            VTSS_D("Cell Stop Assertion: slot_cnt[%u] * 100 = %u, max_slots * 100 = %u", chip_port, slot_cnt_mul_100, max_slots_mul_100);

            if (slot_cnt_mul_100 > max_slots_mul_100) {
                VTSS_E("Port %u has (%u / 100) slots in CBC[%u:%u], max (%u / 100) slots allowed.", chip_port, slot_cnt_mul_100, pos, range_end, max_slots_mul_100);
                return VTSS_RC_ERROR;
            }
        }
    }

    // Check cell_stop deassertion scenario

    // For each port, verify that
    //   FC_LATENCY_CYCLES + <max SD> <= DSM_MAX_STARTUP_CYCLES
    // where
    //   DSM_MAX_STARTUP_CYCLES is calculated based on port speed and DSM_BYTES_BELOW_WM.
    //   <max SD> is maximum slot distance for port.
    for (chip_port = 0; chip_port < CBC_IDLE /* exclude IDLE */; chip_port++) {
        u32             bytes_mul_100, speed, dsm_max_startup_cycles_mul_100, sd_max, res_mul_100;
        cbc_port_type_t port_type;

        port_cfg = &req_cfg->port_cfg[chip_port];
        if (port_cfg->bw == 0) {
            // Not assigned
            continue;
        }

        port_type = rtl_cfg->port_cfg[chip_port].port_type;

        if (port_type == CBC_PORT_TYPE_ETH) {
            speed = port_cfg->eth_speed;
        } else {
            speed = port_cfg->bw;
        }

        bytes_mul_100 = rtl_cfg->dsm_bytes_below_wm_mul_100[port_type][jr2_cbc_speed_to_enum(port_type, speed)];
        // Clock cycles per second = ccps = 1E12 / clk_period_ps.
        // bits = 8 * bytes_mul_100
        // bps = 1E6 * speed in Mbps
        // cycles = ccps * bits / bps
        // u32 or u64? #bytes_mul_100 is at most 100000, so #bits <= 800000. 1E12 (ps->s) / 1E6 (Mbps->bps) = 1E6. 1E6 * 800000 = 8E11 > u32, so u64,
        // but the result needs not be stored in an u64.
        dsm_max_startup_cycles_mul_100 = (u64)(8LLU * bytes_mul_100 * 1000000LLU) / ((u64)speed * rtl_cfg->clk_period_ps);

        sd_max = 0;
        for (base = 0; base < rtl_cfg->cbc_len; base++) {
            if (cbc->cbc[base] == chip_port) {
                u32 sd = 0;

                for (offset = base + 1; offset < base + 1 + rtl_cfg->cbc_len; offset++) {
                    sd++;
                    if (cbc->cbc[offset >= rtl_cfg->cbc_len ? offset - rtl_cfg->cbc_len : offset] == chip_port) {
                        break;
                    }
                }

                if (sd > sd_max) {
                    sd_max = sd;
                }
            }
        }

        res_mul_100 = (sd_max + rtl_cfg->fc_latency_cycles) * 100;
        VTSS_D("port %2u: speed = %u, bytes_mul_100 = %u => dsm_max_startup_cycles_mul_100 = %u, (sd_max + fc_latency_cycles) * 100 = %u", chip_port, speed, bytes_mul_100, dsm_max_startup_cycles_mul_100, res_mul_100);

        if (res_mul_100 > dsm_max_startup_cycles_mul_100) {
            VTSS_E("Port %u: (sd_max (%u) + latency (%u)) * 100 = %u violates startup * 100 = %u", chip_port, sd_max, rtl_cfg->fc_latency_cycles, res_mul_100, dsm_max_startup_cycles_mul_100);
            return VTSS_RC_ERROR;
        }
    }

    VTSS_I("Calendar passed acceptance check");

    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

#if defined(VTSS_CALENDAR_CALC)
static vtss_rc jr2_calendar_calc_and_apply(vtss_state_t *vtss_state)
{
    cbc_rtl_cfg_t   rtl_cfg;
    cbc_req_cfg_t   req_cfg;
    vtss_calendar_t cal;
    vtss_rc         rc;

    // Get the chip's capabilities
    VTSS_RC(jr2_calendar_rtl_cfg_get(vtss_state, &rtl_cfg));

    // Get the actual port requirements based on the port map.
    VTSS_RC(jr2_calendar_req_cfg_get(vtss_state, &rtl_cfg, &req_cfg));

    // Combine the two to obtain a calendar - if possible
    if ((rc = jr2_calendar_do_calc(&rtl_cfg, &req_cfg, &cal)) != VTSS_RC_OK) {
        VTSS_E("Unable to generate calendar. Using auto\n");
        return rc;
    }

    // Perform calendar check
    if ((rc = jr2_calendar_check(&rtl_cfg, &req_cfg, &cal)) != VTSS_RC_OK) {
        VTSS_E("Calendar failed acceptance check. Using auto\n");
        return rc;
    }

    // Apply the calendar. The last argument controls whether idle periods
    // should be assigned to VD1 or not. We set it to FALSE, because we've
    // already taken VD1 into the calculated calendar.
    if ((rc = jr2_calendar_do_set(vtss_state, cal.cbc, rtl_cfg.cbc_len, FALSE, TRUE)) != VTSS_RC_OK) {
        return rc;
    }

    // Finally, grant idle periods to VD0. In the above, we have not include VD0
    // in the calculations, because doing so could cause the calendar calculations
    // to fail. In order to grant some B/W to VD0, we therefore allow it to use
    // idle periods.
    JR2_WR(VTSS_HSCH_HSCH_MISC_OUTB_SHARE_ENA(2), VTSS_F_HSCH_HSCH_MISC_OUTB_SHARE_ENA_OUTB_SHARE_ENA(rtl_cfg.port_cfg[VTSS_CHIP_PORT_VD0].min_slot_dist));

    return VTSS_RC_OK;
}
#endif /* defined(VTSS_CALENDAR_CALC) */

static vtss_rc jr2_port_map_set(vtss_state_t *vtss_state)
{
    vtss_rc rc = VTSS_RC_ERROR;

#if defined(VTSS_CALENDAR_CALC)
    rc = jr2_calendar_calc_and_apply(vtss_state);
#endif

    if (rc != VTSS_RC_OK) {
        if (vtss_state->init_conf.mux_mode == VTSS_PORT_MUX_MODE_AUTO) {
            VTSS_RC(jr2_calendar_auto(vtss_state));
        } else {
#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C)
            VTSS_RC(jr2_calendar_set(vtss_state));
#endif /* VTSS_ARCH_JAGUAR_2_B || VTSS_ARCH_JAGUAR_2_C*/
        }
    }

    return vtss_jr2_init_groups(vtss_state, VTSS_INIT_CMD_PORT_MAP);
}

#define JR2_API_VERSION 1

static vtss_rc jr2_restart_conf_set(vtss_state_t *vtss_state)
{
    // JR2-TBD: Stub
    return VTSS_RC_OK;
}


static vtss_rc vtss_lc_pll5g_setup(vtss_state_t *vtss_state)
{
    /* Setup the 5G LC-PLLs incl restart */
    vtss_pll5g_setup_args_t pll5g_args;
    vtss_rc rc;
    u32 i;

    rc = vtss_pll5g_setup_args_init(&pll5g_args);
    pll5g_args.f_ref_kHz = 125000;
    for (i = 0; i < 2; i++) {
#if defined(VTSS_ARCH_SERVAL_T)
        pll5g_args.chip_name = VTSS_PLL5G_CHIP_SERVALT;
        rc |= vtss_servalt_pll5g_setup(vtss_state, pll5g_args, i);
#elif defined(VTSS_ARCH_JAGUAR_2_C)
        pll5g_args.chip_name = VTSS_PLL5G_CHIP_JAGUAR2C;
        rc |= vtss_jaguar2c_pll5g_setup(vtss_state, pll5g_args, i);
#else
        pll5g_args.chip_name = VTSS_PLL5G_CHIP_JAGUAR2;
        rc |= vtss_jaguar2_pll5g_setup(vtss_state, pll5g_args, i);
#endif
    }
    return rc;
}


static vtss_rc jr2_init_conf_set(vtss_state_t *vtss_state)
{
    /*lint -esym(459, vtss_jr2_rd, vtss_jr2_wr) */
    u32 value, pending, j, i;
    u32 gpio_oe, gpio_oe1, gpio_out, gpio_out1, if_ctrl = 0, if_cfgstat = 0;
#if defined(VTSS_ARCH_JAGUAR_2_C) || VTSS_OPT_TRACE
    u16 revision;
#endif

    // Note; by design - all gazwrap init registers have the same field layout
    struct {
        BOOL gazwrap;
        u32  init_reg;
        u32  init_val;
    } r,
              ram_init_list[] = {
            {FALSE, VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET, VTSS_M_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET_RESET},
            {FALSE, VTSS_ASM_CFG_STAT_CFG, VTSS_M_ASM_CFG_STAT_CFG_STAT_CNT_CLR_SHOT},
            {TRUE,  VTSS_QSYS_RAM_CTRL_RAM_INIT, 0},
            {TRUE,  VTSS_REW_RAM_CTRL_RAM_INIT, 0},
            {TRUE,  VTSS_VOP_RAM_CTRL_RAM_INIT, 0},
            {TRUE,  VTSS_ANA_AC_RAM_CTRL_RAM_INIT, 0},
            {TRUE,  VTSS_ASM_RAM_CTRL_RAM_INIT, 0},
            {TRUE,  VTSS_DSM_RAM_CTRL_RAM_INIT, 0}};

#define INIT_CNT (sizeof(ram_init_list)/sizeof(ram_init_list[0]))

    if (!vtss_state->init_conf.spi_bus) {
        vtss_jr2_rd = jr2_rd_direct;
        vtss_jr2_wr = jr2_wr_direct;
    }

    if (!vtss_state->init_conf.skip_switch_reset) {
        /* Save GPIO state */
        JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_OE, &gpio_oe);
        JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_OE1, &gpio_oe1);
        JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT, &gpio_out);
        JR2_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT1, &gpio_out1);

        /* Save SPI configuration */
        JR2_RD(VTSS_DEVCPU_ORG_DEVCPU_ORG_IF_CTRL, &if_ctrl);
        JR2_RD(VTSS_DEVCPU_ORG_DEVCPU_ORG_IF_CFGSTAT, &if_cfgstat);
        VTSS_D("if_ctrl 0x%08x, if_cfgstat ox%08x", if_ctrl, if_cfgstat);

        /* Reset switch core only */
        VTSS_I("resetting switch core");
        JR2_WR(VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET, VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_PROTECT);
        JR2_WR(VTSS_DEVCPU_GCB_CHIP_REGS_SOFT_RST, VTSS_M_DEVCPU_GCB_CHIP_REGS_SOFT_RST_SOFT_SWC_RST);
        for (i=0; ; i++) {
            if (VTSS_X_DEVCPU_ORG_DEVCPU_ORG_IF_CFGSTAT_IF_NUM(if_cfgstat) == 2) {
                /* Restore SPI configuration */
                JR2_WR(VTSS_DEVCPU_ORG_DEVCPU_ORG_IF_CTRL, if_ctrl);
                JR2_WR(VTSS_DEVCPU_ORG_DEVCPU_ORG_IF_CFGSTAT, if_cfgstat);
            }

            /* Poll for switch core reset done */
            JR2_RD(VTSS_DEVCPU_GCB_CHIP_REGS_SOFT_RST, &value);
            if (value & VTSS_M_DEVCPU_GCB_CHIP_REGS_SOFT_RST_SOFT_SWC_RST) {
                VTSS_MSLEEP(1);
            }
            else {
                break;
            }
            if (i == 100) {
                VTSS_E("switch core reset failed");
                return VTSS_RC_ERROR;
            }
        }
        VTSS_I("reset switch core done");
    }

    if (VTSS_X_DEVCPU_ORG_DEVCPU_ORG_IF_CFGSTAT_IF_NUM(if_cfgstat) == 2) {
        /* Restore SPI configuration */
        JR2_WR(VTSS_DEVCPU_ORG_DEVCPU_ORG_IF_CTRL, if_ctrl);
        JR2_WR(VTSS_DEVCPU_ORG_DEVCPU_ORG_IF_CFGSTAT, if_cfgstat);
    }

    /* Read chip ID to check CPU interface */
    VTSS_RC(vtss_jr2_chip_id_get(vtss_state, &vtss_state->misc.chip_id));
#if defined(VTSS_ARCH_JAGUAR_2_C) || VTSS_OPT_TRACE
    revision = vtss_state->misc.chip_id.revision;
#endif
    VTSS_I("chip_id: 0x%04x, revision: 0x%04x",
           vtss_state->misc.chip_id.part_number, revision);
#if !defined(VTSS_ARCH_SERVAL_T)
    vtss_state->misc.jr2_a = (revision == 0 ? 1 : 0);
#endif /* VTSS_ARCH_SERVAL_T */

#if defined(VTSS_ARCH_JAGUAR_2_C)
    if (revision < 2) {
        VTSS_E("The chip architechture (JR-RevC) does not match with the chip revision (rev %d)", revision);
        return VTSS_RC_ERROR;
    } else if (revision < 4) {
        /* Reduced number of EVC policers and ES0 rules for revision C/D */
        vtss_vcap_obj_t *obj = &vtss_state->vcap.es0.obj;

        vtss_state->l2.pol_table.hdr.max_count /= 2;
        obj->max_count /= 2;
        obj->max_rule_count /= 2;
        for (i = 0; i < obj->max_rule_count; i++) {
            obj->free = obj->free->next;
        }
    }
#endif /* VTSS_ARCH_JAGUAR_2_C */

#if defined(VTSS_ARCH_JAGUAR_2_B)
    if (revision > 1) {
        VTSS_E("The chip architechture (JR-RevB) does not match with the chip revision (rev %d)", revision);
        return VTSS_RC_ERROR;
    }
#endif /* VTSS_ARCH_JAGUAR_2_B */

    if (!vtss_state->init_conf.skip_switch_reset) {
        /* Restore GPIO state */
#define NZ_RESTORE(r, v) do { if (v) { JR2_WR(r, v); } } while(0)
        NZ_RESTORE(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT, gpio_out);
        NZ_RESTORE(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT1, gpio_out1);
        NZ_RESTORE(VTSS_DEVCPU_GCB_GPIO_GPIO_OE, gpio_oe);
        NZ_RESTORE(VTSS_DEVCPU_GCB_GPIO_GPIO_OE1, gpio_oe1);
#undef NZ_RESTORE
    }

    /* Initialize memories, if not done already */
    JR2_RD(VTSS_QSYS_SYSTEM_RESET_CFG, &value);

    if (!(value & VTSS_M_QSYS_SYSTEM_RESET_CFG_CORE_ENA)) {
        for (i=0; i<10; i++) {
            pending=INIT_CNT;
            for (j=0; j<INIT_CNT; j++) {
                r = ram_init_list[j];
                if (r.gazwrap) r.init_val=VTSS_M_QSYS_RAM_CTRL_RAM_INIT_RAM_INIT | VTSS_M_QSYS_RAM_CTRL_RAM_INIT_RAM_ENA;

                if (i==0) {
                    JR2_WRM_SET(r.init_reg, r.init_val);
                } else {
                    JR2_RD(r.init_reg, &value);
                    if ((value & r.init_val) != r.init_val) {
                        pending--;
                    }
                }
            }
            if (!pending)
                break;
            VTSS_MSLEEP(1);
        }

        if (pending>0) {
            /* Still initializing, should be complete in less than 1ms */
            VTSS_E("Memory initialization error");
            return VTSS_RC_ERROR;
        }
    }

    /* Initialize the LC-PLL */
    if (vtss_lc_pll5g_setup(vtss_state) != VTSS_RC_OK) {
         VTSS_E("LC-PLL5G initialization error");
    }
#if (defined VTSS_ARCH_JAGUAR_2_B) || (defined VTSS_ARCH_JAGUAR_2_C) || (defined VTSS_ARCH_SERVAL_T)
    /* Enable i2c glitch filter */
    JR2_WR(VTSS_ICPU_CFG_TWI_SPIKE_FILTER_TWI_SPIKE_FILTER_CFG, 5);
#endif /* VTSS_ARCH_JAGUAR_2_B || VTSS_ARCH_JAGUAR_2_C || VTSS_ARCH_SERVAL_T */

    /* Enable switch core and queue system */
    JR2_WR(VTSS_QSYS_SYSTEM_RESET_CFG, VTSS_F_QSYS_SYSTEM_RESET_CFG_CORE_ENA(1));
    for (i = VTSS_CHIP_PORTS; i < VTSS_CHIP_PORTS_ALL; i++) {
        JR2_WRM_SET(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(i),
                    VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);
    }

#if defined(VTSS_ARCH_JAGUAR_2_C)
    if (vtss_state->create.target == VTSS_TARGET_SPARX_IV_90) {
        // Configuring core clock to run 278MHz
        for(i = 0;i < 2; i++) {
            JR2_WRM(VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0(i),
                    VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_CORE_CLK_DIV(3),
                    VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_CORE_CLK_DIV);
        }

        // Adapt other blocks to the new core speed (TN1267, Chapter 2.2)
        JR2_WRM(VTSS_ANA_AC_POL_COMMON_SDLB_DLB_CTRL,
                VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_CLK_PERIOD_01NS(36),
                VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_CLK_PERIOD_01NS);

        JR2_WRM(VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL,
                VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS(36),
                VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS);

        JR2_WRM(VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL,
                VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS(36),
                VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS);

        JR2_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG,
                VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT(693),
                VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT);

        JR2_WRM(VTSS_LRN_COMMON_AUTOAGE_CFG_1,
                VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_CLK_PERIOD_01NS(36),
                VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_CLK_PERIOD_01NS);

        for(i = 0;i < 2; i++) {
            JR2_WRM(VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK(i),
                    VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SYS_CLK_PERIOD(36),
                    VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SYS_CLK_PERIOD);
        }

        // VTSS_DEVCPU_GCB_FAN_CTRL_FAN_CFG::CLK_PERIOD stays at default

        JR2_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG_PTP_SYS_CLK_PER_NS(3),
                VTSS_M_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG_PTP_SYS_CLK_PER_NS);

        JR2_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG,
                VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG_PTP_SYS_CLK_PER_PS100(6),
                VTSS_M_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG_PTP_SYS_CLK_PER_PS100);

        JR2_WRM(VTSS_HSCH_HSCH_MISC_SYS_CLK_PER,
                VTSS_F_HSCH_HSCH_MISC_SYS_CLK_PER_SYS_CLK_PER_100PS(36),
                VTSS_M_HSCH_HSCH_MISC_SYS_CLK_PER_SYS_CLK_PER_100PS);

        JR2_WRM(VTSS_VOP_COMMON_LOC_CTRL,
                VTSS_F_VOP_COMMON_LOC_CTRL_LOC_BASE_TICK_CNT(28), // 100/3.6
                VTSS_M_VOP_COMMON_LOC_CTRL_LOC_BASE_TICK_CNT);

        JR2_WRM(VTSS_AFI_TTI_TICKS_TTI_TICK_BASE,
                VTSS_F_AFI_TTI_TICKS_TTI_TICK_BASE_BASE_LEN(14444), // 52us/3.6ns
                VTSS_M_AFI_TTI_TICKS_TTI_TICK_BASE_BASE_LEN);
    }
#endif /*  VTSS_ARCH_JAGUAR_2_C */

#if !defined(VTSS_ARCH_SERVAL_T)
    // Enable 250 MHz CLKOUT2 for 1588
    JR2_WRM(VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3(1),
            VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_CLKOUT2_SEL(3),
            VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_CLKOUT2_SEL);
#endif /* VTSS_ARCH_SERVAL_T */

    /* Set ASM/DSM watermarks for cpu traffic */
    JR2_WRM(VTSS_DSM_CFG_SCH_STOP_WM_CFG(VTSS_CHIP_PORT_CPU_0),
            VTSS_F_DSM_CFG_SCH_STOP_WM_CFG_SCH_STOP_WM(64),
            VTSS_M_DSM_CFG_SCH_STOP_WM_CFG_SCH_STOP_WM);

    JR2_WRM(VTSS_DSM_CFG_SCH_STOP_WM_CFG(VTSS_CHIP_PORT_CPU_1),
            VTSS_F_DSM_CFG_SCH_STOP_WM_CFG_SCH_STOP_WM(64),
            VTSS_M_DSM_CFG_SCH_STOP_WM_CFG_SCH_STOP_WM);

    JR2_WRM(VTSS_ASM_CFG_CPU_FC_CFG,
            VTSS_F_ASM_CFG_CPU_FC_CFG_CPU_FC_WM(2)| VTSS_F_ASM_CFG_CPU_FC_CFG_CPU_FC_ENA(1),
            VTSS_M_ASM_CFG_CPU_FC_CFG_CPU_FC_WM   | VTSS_M_ASM_CFG_CPU_FC_CFG_CPU_FC_ENA);

    JR2_RD(VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT, &value);
    vtss_state->sys_config.vcore_cfg = VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_VCORE_CFG(value);

    /* See datasheet, Table 253 VCore-III Configurations,
       vcore_cfg == 14 added as a special case */

    vtss_state->sys_config.using_vcoreiii =
        (vtss_state->sys_config.vcore_cfg == 0 || vtss_state->sys_config.vcore_cfg == 12);
#if defined(VTSS_OPT_VRAP_ACCESS)
    vtss_state->sys_config.using_vrap = (vtss_state->sys_config.vcore_cfg >= 1 &&
                                         vtss_state->sys_config.vcore_cfg <= 8);
#else
    vtss_state->sys_config.using_vrap = 0;
#endif //VTSS_OPT_VRAP_ACCESS
#if defined(VTSS_OPT_PCIE_ACCESS)
    vtss_state->sys_config.using_pcie = ((vtss_state->sys_config.vcore_cfg >= 1 &&
                                          vtss_state->sys_config.vcore_cfg <= 7) ||
                                          vtss_state->sys_config.vcore_cfg == 9 ||
                                          vtss_state->sys_config.vcore_cfg == 14);
#else
    vtss_state->sys_config.using_pcie = 0;
#endif //VTSS_OPT_PCIe_ACCESS
    VTSS_I("Vcore_cfg: 0x%04x, VCOREIII: %d, VRAP: %d, PCIe: %d",
           vtss_state->sys_config.vcore_cfg,
           vtss_state->sys_config.using_vcoreiii,
           vtss_state->sys_config.using_vrap,
           vtss_state->sys_config.using_pcie);

    /* Initialize function groups */
    VTSS_RC(vtss_jr2_init_groups(vtss_state, VTSS_INIT_CMD_INIT));

    return VTSS_RC_OK;
}

static vtss_rc jr2_register_access_mode_set(vtss_state_t *vtss_state)
{
    if (vtss_state->init_conf.spi_bus) {
        vtss_jr2_rd = jr2_rd_indirect;
        vtss_jr2_wr = jr2_wr_indirect;
    } else {
        vtss_jr2_rd = jr2_rd_direct;
        vtss_jr2_wr = jr2_wr_direct;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_jaguar2_inst_create(vtss_state_t *vtss_state)
{
    /* Initialization */
    vtss_state->cil.init_conf_set = jr2_init_conf_set;
    vtss_state->cil.register_access_mode_set = jr2_register_access_mode_set;
    vtss_state->cil.restart_conf_set = jr2_restart_conf_set;
    vtss_state->cil.debug_info_print = jr2_debug_info_print;
    vtss_state->port.map_set = jr2_port_map_set;

    /* Create function groups */
    return vtss_jr2_init_groups(vtss_state, VTSS_INIT_CMD_CREATE);
}

#endif /* VTSS_ARCH_JAGUAR_2 */
