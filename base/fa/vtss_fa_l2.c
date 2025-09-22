// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L2
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)

/* - CIL functions ------------------------------------------------- */

/* Convert from chip PGID to AIL PGID */
u32 vtss_fa_vtss_pgid(const vtss_state_t *const vtss_state, u32 pgid)
{
    vtss_port_no_t port_no;

    if (pgid < RT_CHIP_PORTS) {
        for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
            if (VTSS_CHIP_PORT(port_no) == pgid) {
                break;
            }
        }
        return port_no;
    } else {
        return (vtss_state->port_count + pgid - RT_CHIP_PORTS);
    }
}

/* Convert from AIL PGID to chip PGID */
static u32 fa_chip_pgid(vtss_state_t *vtss_state, u32 pgid)
{
    if (pgid < vtss_state->port_count) {
        return VTSS_CHIP_PORT(pgid);
    } else {
        return (pgid + RT_CHIP_PORTS - vtss_state->port_count);
    }
}

vtss_rc vtss_cil_l2_pgid_table_write(struct vtss_state_s *vtss_state,
                                     u32                  pgid,
                                     BOOL                 member[VTSS_PORTS])
{
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[pgid];
    vtss_port_mask_t   pmask;

    pgid = fa_chip_pgid(vtss_state, pgid);
    vtss_port_mask_get(vtss_state, member, &pmask);
    REG_WRX_PMASK(VTSS_ANA_AC_PGID_PGID_CFG, pgid, pmask);
    REG_WR(VTSS_ANA_AC_PGID_PGID_MISC_CFG(pgid),
           VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(pgid_entry->cpu_copy) |
               VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_STACK_TYPE_ENA(0) |
               VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU(pgid_entry->cpu_queue));
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_src_table_write(struct vtss_state_s *vtss_state,
                                    vtss_port_no_t       port_no,
                                    BOOL                 member[VTSS_PORTS])
{
    vtss_port_mask_t pmask;
    u32              port = VTSS_CHIP_PORT(port_no);

    vtss_port_mask_get(vtss_state, member, &pmask);
    REG_WRX_PMASK(VTSS_ANA_AC_SRC_SRC_CFG, port, pmask);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_aggr_mode_set(struct vtss_state_s *vtss_state)
{
    vtss_aggr_mode_t *mode = &vtss_state->l2.aggr_mode;

    REG_WRM(VTSS_ANA_CL_AGGR_CFG,
            VTSS_F_ANA_CL_AGGR_CFG_AGGR_SMAC_ENA(mode->smac_enable) |
                VTSS_F_ANA_CL_AGGR_CFG_AGGR_DMAC_ENA(mode->dmac_enable) |
                VTSS_F_ANA_CL_AGGR_CFG_AGGR_IP4_SIP_ENA(mode->sip_dip_enable) |
                VTSS_F_ANA_CL_AGGR_CFG_AGGR_IP4_DIP_ENA(mode->sip_dip_enable) |
                VTSS_F_ANA_CL_AGGR_CFG_AGGR_IP6_SIP_ENA(mode->sip_dip_enable) |
                VTSS_F_ANA_CL_AGGR_CFG_AGGR_IP6_DIP_ENA(mode->sip_dip_enable) |
                VTSS_F_ANA_CL_AGGR_CFG_AGGR_IP4_TCPUDP_PORT_ENA(mode->sport_dport_enable) |
                VTSS_F_ANA_CL_AGGR_CFG_AGGR_IP6_TCPUDP_PORT_ENA(mode->sport_dport_enable),
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_SMAC_ENA | VTSS_M_ANA_CL_AGGR_CFG_AGGR_DMAC_ENA |
                VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP4_SIP_ENA | VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP4_DIP_ENA |
                VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP6_SIP_ENA | VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP6_DIP_ENA |
                VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP4_TCPUDP_PORT_ENA |
                VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP6_TCPUDP_PORT_ENA);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_pmap_table_write(struct vtss_state_s *vtss_state,
                                     vtss_port_no_t       port_no,
                                     vtss_port_no_t       l_port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 lport = VTSS_CHIP_PORT(l_port_no);

    REG_WRM(VTSS_ANA_CL_PORT_ID_CFG(port), VTSS_F_ANA_CL_PORT_ID_CFG_LPORT_NUM(lport),
            VTSS_M_ANA_CL_PORT_ID_CFG_LPORT_NUM);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_learn_state_set(struct vtss_state_s *vtss_state, const BOOL member[VTSS_PORTS])
{
    vtss_port_mask_t pmask;
    vtss_port_no_t   port;
    BOOL             lrn[VTSS_PORTS];
#if defined(VTSS_FEATURE_L2_MSTP)
    vtss_mstp_entry_t *mstp = &vtss_state->l2.mstp_table[0];
#endif

    for (port = 0U; port < vtss_state->port_count; port++) {
        // Include MSTP instance 0 state
        lrn[port] = (member[port]
#if defined(VTSS_FEATURE_L2_MSTP)
                     && mstp->state[port] != VTSS_STP_STATE_DISCARDING
#endif
        );
    }

    vtss_port_mask_get(vtss_state, lrn, &pmask);
    REG_WRX_PMASK(VTSS_ANA_L3_MSTP_LRN_CFG, 0, pmask);
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_L2_MSTP)
vtss_rc vtss_cil_l2_mstp_state_set(vtss_state_t        *vtss_state,
                                   const vtss_port_no_t port_no,
                                   const vtss_msti_t    msti)
{
    BOOL             fwd[VTSS_PORTS], lrn[VTSS_PORTS];
    vtss_port_no_t   port;
    vtss_stp_state_t state;
    vtss_port_mask_t pmask;

    for (port = 0; port < vtss_state->port_count; port++) {
        state = vtss_state->l2.mstp_table[msti].state[port];
        fwd[port] = (state == VTSS_STP_STATE_FORWARDING ? 1 : 0);
        lrn[port] = (state == VTSS_STP_STATE_DISCARDING ? 0 : 1);
        if (msti == 0 && vtss_state->l2.learn[port] == 0) {
            // Include port learn state for MSTI 0
            lrn[port] = 0;
        }
    }
    vtss_port_mask_get(vtss_state, fwd, &pmask);
    REG_WRX_PMASK(VTSS_ANA_L3_MSTP_FWD_CFG, msti, pmask);
    vtss_port_mask_get(vtss_state, lrn, &pmask);
    REG_WRX_PMASK(VTSS_ANA_L3_MSTP_LRN_CFG, msti, pmask);
    return vtss_cmn_mstp_state_set(vtss_state, port_no, msti);
}
#endif

/* Wait until the MAC table operation is finsished */
static vtss_rc fa_mac_table_idle(vtss_state_t *vtss_state)
{
    u32 cmd;

    while (TRUE) {
        REG_RD(VTSS_LRN_COMMON_ACCESS_CTRL, &cmd);
        if ((VTSS_M_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT & cmd) == 0U) {
            break;
        }
    }
    return VTSS_RC_OK;
}

static u32 fa_port2upsid(vtss_state_t *vtss_state, u32 *port)
{
    u32 upsid = 0U;

    /* Convert local chip port to local UPSID */
    while (*port > 31U) {
        *port = (*port - 32U);
        upsid++;
    }
    return upsid;
}

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
#define PMACACCESS_CMD_IDLE  0
#define PMACACCESS_CMD_READ  1
#define PMACACCESS_CMD_WRITE 2
#define PMACACCESS_CMD_INIT  3
static vtss_rc fa_pmac_table_idle(vtss_state_t *vtss_state)
{
    u32 cmd;

    while (1) {
        REG_RD(VTSS_ANA_L2_PMAC_ACCESS_CTRL, &cmd);
        if (VTSS_X_ANA_L2_PMAC_ACCESS_CTRL_PMAC_ACCESS_CMD(cmd) == PMACACCESS_CMD_IDLE) {
            break;
        }
    }
    return VTSS_RC_OK;
}
#endif

vtss_rc vtss_cil_l2_mac_table_add(struct vtss_state_s                *vtss_state,
                                  const vtss_mac_table_entry_t *const entry,
                                  u32                                 pgid)
{
    u32  cfg0, cfg1, cfg2, addr, upsid, aged = 0U, fwd_kill, addr_type;
    BOOL copy_to_cpu = (entry->copy_to_cpu_smac ? TRUE : FALSE);

    /* Set FWD_KILL to make the switch discard frames in SMAC lookup */
    fwd_kill = (copy_to_cpu || (pgid != vtss_state->l2.pgid_drop) ? 0U : 1U);

    addr = fa_chip_pgid(vtss_state, pgid);
    if (addr >= RT_CHIP_PORTS) {
        /* Multicast PGID */
        addr_type = MAC_ENTRY_ADDR_TYPE_MC_IDX;
        addr -= RT_CHIP_PORTS;
    } else {
        /* Use local (UPSID, UPSPN) */
        addr_type = MAC_ENTRY_ADDR_TYPE_UPSID_PN;
        upsid = fa_port2upsid(vtss_state, &addr);
        addr += (upsid << 5U);
    }

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    if (entry->index_table) {
        REG_WR(VTSS_ANA_L2_PMAC_INDEX,
               VTSS_F_ANA_L2_PMAC_INDEX_PMAC_INDEX(vtss_state->l2.mac_index_table.idx_add));
        cfg2 = (VTSS_F_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_CPU_QU(0) |
                VTSS_F_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_CPU_COPY(0) |
                VTSS_F_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_VLAN_IGNORE(0) |
                VTSS_F_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_ADDR_TYPE(addr_type) |
                VTSS_F_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_ADDR(addr) |
                VTSS_F_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_VLD(1));
        REG_WR(VTSS_ANA_L2_PMAC_ACCESS_CFG_2, cfg2);
        REG_WR(VTSS_ANA_L2_PMAC_ACCESS_CTRL,
               VTSS_F_ANA_L2_PMAC_ACCESS_CTRL_PMAC_ACCESS_CMD(PMACACCESS_CMD_WRITE));
        return fa_pmac_table_idle(vtss_state);
    }
#endif

    vtss_mach_macl_get(&entry->vid_mac, &cfg0, &cfg1);
    cfg2 = (VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(addr) |
            VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(addr_type) |
            VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_SRC_KILL_FWD(fwd_kill) |
            VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_COPY(copy_to_cpu) |
            VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_QU(entry->cpu_queue) |
            VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_FLAG(aged) |
            VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_LOCKED(entry->locked) |
            VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_VLD(1));

    /* Insert/learn new entry into the MAC table  */
    VTSS_D("mach: 0x%08x, macl: 0x%08x, cfg2: 0x%08x", cfg0, cfg1, cfg2);
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_0, cfg0);
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_1, cfg1);
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_2, cfg2);
    REG_WR(VTSS_LRN_COMMON_ACCESS_CTRL,
           VTSS_F_LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_LEARN) |
               VTSS_F_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    return fa_mac_table_idle(vtss_state);
}

vtss_rc vtss_cil_l2_mac_table_del(struct vtss_state_s        *vtss_state,
                                  const vtss_vid_mac_t *const vid_mac)
{
    u32 cfg0, cfg1;
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    u32 idx = vtss_state->l2.mac_index_table.idx_get;

    if (idx <= VTSS_M_ANA_L2_PMAC_INDEX_PMAC_INDEX) {
        // Delete from index table
        REG_WR(VTSS_ANA_L2_PMAC_INDEX, VTSS_F_ANA_L2_PMAC_INDEX_PMAC_INDEX(idx));
        REG_WR(VTSS_ANA_L2_PMAC_ACCESS_CFG_2, VTSS_F_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_VLD(0));
        REG_WR(VTSS_ANA_L2_PMAC_ACCESS_CTRL,
               VTSS_F_ANA_L2_PMAC_ACCESS_CTRL_PMAC_ACCESS_CMD(PMACACCESS_CMD_WRITE));
        return fa_pmac_table_idle(vtss_state);
    }
#endif

    vtss_mach_macl_get(vid_mac, &cfg0, &cfg1);
    VTSS_D("mach: 0x%08x, macl: 0x%08x", cfg0, cfg1);

    /* Delete/unlearn the given MAC entry */
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_0, cfg0);
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_1, cfg1);
    REG_WR(VTSS_LRN_COMMON_ACCESS_CTRL,
           VTSS_F_LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_UNLEARN) |
               VTSS_F_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    return fa_mac_table_idle(vtss_state);
}

static vtss_rc fa_mac_type_addr_pgid_get(vtss_state_t *vtss_state, u32 type, u32 addr, u32 *pgid)
{
    vtss_rc rc = VTSS_RC_OK;
    switch (type) {
    case MAC_ENTRY_ADDR_TYPE_UPSID_PN: *pgid = vtss_fa_vtss_pgid(vtss_state, addr & 0x7fU); break;
    case MAC_ENTRY_ADDR_TYPE_MC_IDX:
        /* Multicast PGID */
        *pgid = vtss_fa_vtss_pgid(vtss_state, addr + RT_CHIP_PORTS);
        break;
    default:
        VTSS_E("unsupported addr type: %u", type);
        rc = VTSS_RC_ERROR;
        break;
    }
    return rc;
}

/* Return the result from MAC table get operations */
static vtss_rc fa_mac_table_result(vtss_state_t                 *vtss_state,
                                   vtss_mac_table_entry_t *const entry,
                                   u32                          *pgid)
{
    u32 cfg0, cfg1, cfg2, addr, type;

    REG_RD(VTSS_LRN_MAC_ACCESS_CFG_2, &cfg2);
    /* Check if entry is valid */
    if ((cfg2 & VTSS_M_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_VLD) == 0U) {
        VTSS_D("not valid");
        return VTSS_RC_ERROR;
    }
    REG_RD(VTSS_LRN_MAC_ACCESS_CFG_0, &cfg0);
    REG_RD(VTSS_LRN_MAC_ACCESS_CFG_1, &cfg1);
    VTSS_D("mach: 0x%08x, macl: 0x%08x, cfg2: 0x%08x", cfg0, cfg1, cfg2);

    /* Extract fields from Jaguar registers */
    VTSS_MEMSET(entry, 0, sizeof(*entry));
    entry->aged = VTSS_BOOL(VTSS_X_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_FLAG(cfg2));
    entry->copy_to_cpu = FALSE;
    entry->copy_to_cpu_smac = VTSS_BOOL(cfg2 & VTSS_M_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_COPY);
    entry->cpu_queue = entry->copy_to_cpu ? VTSS_X_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_QU(cfg2) : 0U;
    entry->locked = VTSS_BOOL(cfg2 & VTSS_M_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_LOCKED);
    addr = VTSS_X_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(cfg2);
    type = VTSS_X_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(cfg2);
    vtss_mach_macl_set(&entry->vid_mac, cfg0, cfg1);
    return fa_mac_type_addr_pgid_get(vtss_state, type, addr, pgid);
}

vtss_rc vtss_cil_l2_mac_table_get(struct vtss_state_s          *vtss_state,
                                  vtss_mac_table_entry_t *const entry,
                                  u32                          *pgid)
{
    u32 cfg0, cfg1;
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    u32 cfg2, type, addr;

    if (entry->index_table) {
        // Get from index table
        REG_WR(VTSS_ANA_L2_PMAC_INDEX,
               VTSS_F_ANA_L2_PMAC_INDEX_PMAC_INDEX(vtss_state->l2.mac_index_table.idx_get));
        REG_WR(VTSS_ANA_L2_PMAC_ACCESS_CTRL,
               VTSS_F_ANA_L2_PMAC_ACCESS_CTRL_PMAC_ACCESS_CMD(PMACACCESS_CMD_READ));
        VTSS_RC(fa_pmac_table_idle(vtss_state));
        REG_RD(VTSS_ANA_L2_PMAC_ACCESS_CFG_2, &cfg2);
        if (VTSS_X_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_VLD(cfg2) == 0) {
            return VTSS_RC_ERROR;
        }
        entry->copy_to_cpu = VTSS_X_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_CPU_COPY(cfg2);
        entry->copy_to_cpu_smac = 0;
        entry->locked = 1;
        entry->aged = 0;
        type = VTSS_X_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_ADDR_TYPE(cfg2);
        addr = VTSS_X_ANA_L2_PMAC_ACCESS_CFG_2_PMAC_ENTRY_ADDR(cfg2);
        return fa_mac_type_addr_pgid_get(vtss_state, type, addr, pgid);
    }
#endif

    /* Get entry */
    vtss_mach_macl_get(&entry->vid_mac, &cfg0, &cfg1);
    VTSS_D("address 0x%08x%08x", cfg0, cfg1);
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_0, cfg0);
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_1, cfg1);
    REG_WR(VTSS_LRN_COMMON_ACCESS_CTRL,
           VTSS_F_LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_LOOKUP) |
               VTSS_F_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    VTSS_RC(fa_mac_table_idle(vtss_state));

    return fa_mac_table_result(vtss_state, entry, pgid);
}

vtss_rc vtss_cil_l2_mac_table_get_next(struct vtss_state_s          *vtss_state,
                                       vtss_mac_table_entry_t *const entry,
                                       u32                          *pgid)
{
    u32                cfg0, cfg1;
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[VTSS_PGID_NONE];

    /* Clear PGID entry for IPMC/GLAG entries */
    VTSS_MEMSET(pgid_entry, 0, sizeof(*pgid_entry));

    vtss_mach_macl_get(&entry->vid_mac, &cfg0, &cfg1);
    VTSS_D("address 0x%08x%08x", cfg0, cfg1);

    /* Get next entry */
    REG_WR(VTSS_LRN_SCAN_NEXT_CFG, VTSS_F_LRN_SCAN_NEXT_CFG_SCAN_NEXT_UNTIL_FOUND_ENA(1));
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_0, cfg0);
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_1, cfg1);
    REG_WR(VTSS_LRN_COMMON_ACCESS_CTRL,
           VTSS_F_LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_FIND_SMALLEST) |
               VTSS_F_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    VTSS_RC(fa_mac_table_idle(vtss_state));

    return fa_mac_table_result(vtss_state, entry, pgid);
}

vtss_rc vtss_cil_l2_mac_table_age_time_set(struct vtss_state_s *vtss_state)
{
    u32 t, units;

    /* Scan two times per age time */
    t = vtss_state->l2.mac_age_time;
    if (t <= 1U) {
        units = 0U; /* 0: disable ageing */
        t = 0U;
    } else {
        units = 3U;             /* 3: unit = 1 sec */
        t = (t / 2U);           /* age between T/2 and T */
        t = MIN(t, 0xfffffffU); /* period_val is 28 bits wide */
    }
    VTSS_D("t %d, units %d", t, units);

    /* Stop aging and set counters to a low value */
    REG_WR(VTSS_LRN_AUTOAGE_CFG(0),
           VTSS_F_LRN_AUTOAGE_CFG_UNIT_SIZE(1) | VTSS_F_LRN_AUTOAGE_CFG_PERIOD_VAL(1));
    REG_WRM(VTSS_LRN_AUTOAGE_CFG_1,
            VTSS_F_LRN_AUTOAGE_CFG_1_FORCE_IDLE_ENA(1) |
                VTSS_F_LRN_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT(1),
            VTSS_M_LRN_AUTOAGE_CFG_1_FORCE_IDLE_ENA |
                VTSS_M_LRN_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT);

    REG_WR(VTSS_LRN_AUTOAGE_CFG(0),
           VTSS_F_LRN_AUTOAGE_CFG_UNIT_SIZE(units) | VTSS_F_LRN_AUTOAGE_CFG_PERIOD_VAL(t));
    REG_WRM(VTSS_LRN_AUTOAGE_CFG_1,
            VTSS_F_LRN_AUTOAGE_CFG_1_FORCE_IDLE_ENA(units == 0U) |
                VTSS_F_LRN_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT(1),
            VTSS_M_LRN_AUTOAGE_CFG_1_FORCE_IDLE_ENA |
                VTSS_M_LRN_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT);

    return VTSS_RC_OK;
}

static vtss_rc fa_mac_table_age_cmd(vtss_state_t    *vtss_state,
                                    BOOL             pgid_age,
                                    u32              pgid,
                                    BOOL             vid_age,
                                    const vtss_vid_t vid,
                                    BOOL             age)
{
    u32        port, addr = 0U, addr_type = MAC_ENTRY_ADDR_TYPE_UPSID_PN;
    vtss_vid_t fid = 0;

#if defined(VTSS_FEATURE_VLAN_SVL)
    fid = vtss_state->l2.vlan_table[vid].fid;
#endif

    if (pgid_age) {
        if (pgid < vtss_state->port_count) {
            /* Port specific ageing, find UPSID and UPSPN */
            port = VTSS_CHIP_PORT(pgid);
            addr = ((fa_port2upsid(vtss_state, &port) << 5U) + port);
        } else {
            /* GLAG ageing */
            addr = ((pgid - vtss_state->l2.pgid_glag_dest) & 0x1fU);
            addr_type = MAC_ENTRY_ADDR_TYPE_GLAG;
        }
    }

    VTSS_D("pgid_age %u, addr %u, vid_age %u, vid %u", pgid_age, addr, vid_age, vid);

    /* Selective aging */
    REG_WR(VTSS_LRN_SCAN_NEXT_CFG, VTSS_F_LRN_SCAN_NEXT_CFG_FID_FILTER_ENA(vid_age) |
                                       VTSS_F_LRN_SCAN_NEXT_CFG_ADDR_FILTER_ENA(pgid_age) |
                                       VTSS_F_LRN_SCAN_NEXT_CFG_SCAN_AGE_INTERVAL_MASK(0xf) |
                                       VTSS_F_LRN_SCAN_NEXT_CFG_SCAN_NEXT_REMOVE_FOUND_ENA(1) |
                                       VTSS_F_LRN_SCAN_NEXT_CFG_SCAN_NEXT_INC_AGE_BITS_ENA(age));
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_0,
           VTSS_F_LRN_MAC_ACCESS_CFG_0_MAC_ENTRY_FID(fid == 0U ? vid : fid));
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_2,
           VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(addr) |
               VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(addr_type));

    /* Do the aging */
    REG_WR(VTSS_LRN_COMMON_ACCESS_CTRL, VTSS_F_LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_SCAN) |
                                            VTSS_F_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    /* Wait until MAC operation is finished */
    return fa_mac_table_idle(vtss_state);
}

vtss_rc vtss_cil_l2_mac_table_age(struct vtss_state_s *vtss_state,
                                  BOOL                 pgid_age,
                                  u32                  pgid,
                                  BOOL                 vid_age,
                                  const vtss_vid_t     vid)
{
    return fa_mac_table_age_cmd(vtss_state, pgid_age, pgid, vid_age, vid, TRUE);
}

vtss_rc vtss_cil_l2_mac_table_status_get(struct vtss_state_s           *vtss_state,
                                         vtss_mac_table_status_t *const status)
{
    u32 value;

    VTSS_MEMSET(status, 0, sizeof(*status));

    /* Detect port move events */
    REG_RD(VTSS_ANA_L2_STICKY, &value);
    value &= (VTSS_M_ANA_L2_STICKY_LOCAL_TO_REMOTE_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_REMOTE_TO_LOCAL_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_REMOTE_TO_REMOTE_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_GLOBAL_TO_GLOBAL_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_GLOBAL_TO_LOCAL_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_LOCAL_TO_GLOBAL_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_LOCAL_TO_LOCAL_PORTMOVE_STICKY);
    REG_WR(VTSS_ANA_L2_STICKY, value);
    if (value > 0U) {
        status->moved = TRUE;
    }

    /* Read and clear sticky register */
    REG_RD(VTSS_LRN_EVENT_STICKY, &value);
    value &= (VTSS_M_LRN_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY |
              VTSS_M_LRN_EVENT_STICKY_AUTO_LRN_INSERT_STICKY |
              VTSS_M_LRN_EVENT_STICKY_AUTOAGE_REMOVE_STICKY |
              VTSS_M_LRN_EVENT_STICKY_AUTOAGE_AGED_STICKY);
    REG_WR(VTSS_LRN_EVENT_STICKY, value);

    /* Detect learn events */
    if ((value & VTSS_M_LRN_EVENT_STICKY_AUTO_LRN_INSERT_STICKY) > 0U) {
        status->learned = TRUE;
    }

    /* Detect replace events */
    if ((value & VTSS_M_LRN_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY) > 0U) {
        status->replaced = TRUE;
    }

    /* Detect age events (both aged and removed event is used */
    if ((value & (VTSS_M_LRN_EVENT_STICKY_AUTOAGE_AGED_STICKY |
                  VTSS_M_LRN_EVENT_STICKY_AUTOAGE_REMOVE_STICKY)) > 0U) {
        status->aged = TRUE;
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
vtss_rc vtss_cil_l2_mac_index_update(vtss_state_t *vtss_state)
{
    vtss_mac_index_table_t *t = &vtss_state->l2.mac_index_table;
    u32                     i, vid;

    REG_WR(VTSS_ANA_L2_PMAC_CFG, VTSS_F_ANA_L2_PMAC_CFG_PMAC_ENA(t->cnt ? 1 : 0) |
                                     VTSS_F_ANA_L2_PMAC_CFG_PMAC_OUI(t->oui));
    REG_WR(VTSS_ANA_L2_PMAC_CFG_2, VTSS_F_ANA_L2_PMAC_CFG_2_PMAC_CHK_DMAC_LSB_ENA(1));
    for (i = 0; i < VTSS_MAC_INDEX_VID_CNT; i++) {
        vid = t->e[i].vid;
        REG_WR(VTSS_ANA_L2_PMAC_VLAN_CFG(i),
               VTSS_F_ANA_L2_PMAC_VLAN_CFG_PMAC_VLAN_ENA(vid ? 1 : 0) |
                   VTSS_F_ANA_L2_PMAC_VLAN_CFG_PMAC_VLAN(vid));
    }
    return VTSS_RC_OK;
}
#endif

vtss_rc vtss_cil_l2_learn_port_mode_set(struct vtss_state_s *vtss_state,
                                        const vtss_port_no_t port_no)
{
    vtss_learn_mode_t *mode = &vtss_state->l2.learn_mode[port_no];
    vtss_port_mask_t   pmask, pmask_zero;
    vtss_port_no_t     port_iter;
    u32                cnt = 0U;
    u32                port = VTSS_CHIP_PORT(port_no);

    vtss_port_mask_port(vtss_state, port_no, &pmask);
    vtss_port_mask_clear(&pmask_zero);

    REG_WRM_PMASK(VTSS_ANA_L2_LRN_SECUR_CFG, mode->discard ? pmask : pmask_zero,
                  pmask); // Drop unknown smac
    REG_WRM_PMASK(VTSS_ANA_L2_LRN_SECUR_LOCKED_CFG, pmask,
                  pmask); // Always drop move of locked entries
    REG_WRM_PMASK(VTSS_ANA_L2_AUTO_LRN_CFG, mode->automatic ? pmask : pmask_zero,
                  pmask); // Enable H/W-based learning
    REG_WRM_PMASK(VTSS_ANA_L2_LRN_COPY_CFG, mode->cpu ? pmask : pmask_zero,
                  pmask); // Copy incoming learn frames to CPU
    REG_WRM(VTSS_ANA_L2_PORT_LIMIT_CTRL(port),
            VTSS_F_ANA_L2_PORT_LIMIT_CTRL_PORT_LRN_CNT_LIMIT(mode->learn_limit),
            VTSS_M_ANA_L2_PORT_LIMIT_CTRL_PORT_LRN_CNT_LIMIT); // Learn limit on
                                                               // this port

    // Unfortunately, it's not possible to control per port, whether we want
    // copies of frames whose MAC address is statically learned on another port
    // to the CPU. This is a global configuration. Instead, we need to check
    // whether at least two ports are enabled for secure learning, and if so
    // enable that configuration. If at most one port is enabled, we don't care
    // about such frames. The reason is that it must be possible for the
    // application to move MAC addresses learned on one secure port to another
    // secure port, but not from one secure port to a non-sercure port.
    for (port_iter = 0U; port_iter < vtss_state->port_count; port_iter++) {
        if (!vtss_state->l2.learn_mode[port_iter].automatic) {
            // Secure learning is enabled
            if (++cnt == 2U) {
                break;
            }
        }
    }

    REG_WRM(VTSS_ANA_L2_LRN_CFG, VTSS_F_ANA_L2_LRN_CFG_LOCKED_PORTMOVE_COPY_ENA(cnt < 2U ? 0U : 1U),
            VTSS_M_ANA_L2_LRN_CFG_LOCKED_PORTMOVE_COPY_ENA);

    /* If automatic ageing is disabled, flush entries previously learned on port
     */
    return (mode->automatic ? VTSS_RC_OK
                            : fa_mac_table_age_cmd(vtss_state, TRUE, port_no, FALSE, 0, FALSE));
}

/* ================================================================= *
 *  Layer 2 - VLAN
 * ================================================================= */

vtss_rc vtss_cil_l2_vlan_conf_set(struct vtss_state_s *vtss_state)
{
    u32 etype = vtss_state->l2.vlan_conf.s_etype;

    /* Configure alternative S-tag Ethernet Type */
    REG_WR(VTSS_ANA_CL_VLAN_STAG_CFG(0), VTSS_F_ANA_CL_VLAN_STAG_CFG_STAG_ETYPE_VAL(etype));
    REG_WR(VTSS_REW_TPID_CFG(0), VTSS_F_REW_TPID_CFG_TPID_VAL(etype));

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_vlan_update(vtss_state_t *vtss_state, vtss_vid_t vid)
{
    vtss_vlan_entry_t *e = &vtss_state->l2.vlan_table[vid];
    u32                msti = 0U, fid = 0U, rl_id = 0U;
    BOOL               rl_enable = FALSE;

#if defined(VTSS_FEATURE_L2_MSTP)
    msti = e->msti;
#endif
#if defined(VTSS_FEATURE_VLAN_SVL)
    fid = e->fid;
#endif
#if defined(VTSS_FEATURE_LAYER3)
    rl_enable = e->rl_enable;
    rl_id = e->rl_id;
#endif
    REG_WR(VTSS_ANA_L3_VLAN_CFG(vid),
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_MSTP_PTR(msti) |
               VTSS_F_ANA_L3_VLAN_CFG_VLAN_FID(fid == 0U ? vid : fid) |
               VTSS_F_ANA_L3_VLAN_CFG_VLAN_IGR_FILTER_ENA((e->flags & VLAN_FLAGS_FILTER) != 0U) |
               VTSS_F_ANA_L3_VLAN_CFG_VLAN_FLOOD_DIS((e->flags & VLAN_FLAGS_FLOOD) == 0U) |
               VTSS_F_ANA_L3_VLAN_CFG_VLAN_LRN_DIS((e->flags & VLAN_FLAGS_LEARN) == 0U) |
               VTSS_F_ANA_L3_VLAN_CFG_VLAN_RLEG_ENA(rl_enable) |
               VTSS_F_ANA_L3_VLAN_CFG_VLAN_PRIVATE_ENA((e->flags & VLAN_FLAGS_ISOLATED) != 0U) |
               VTSS_F_ANA_L3_VLAN_CFG_VLAN_MIRROR_ENA((e->flags & VLAN_FLAGS_MIRROR) != 0U));
    REG_WR(VTSS_ANA_L3_VMID_CFG(vid), VTSS_F_ANA_L3_VMID_CFG_VMID(rl_id));
#if defined(VTSS_FEATURE_QOS_OT)
    REG_WR(VTSS_ANA_L3_QGRP_CFG(vid),
           VTSS_F_ANA_L3_QGRP_CFG_QGRP_IDX(e->flags & VLAN_FLAGS_OT ? 1 : 0) |
               VTSS_F_ANA_L3_QGRP_CFG_QGRP_OAM_TYPE(0));
#endif
#if defined(VTSS_FEATURE_HQOS)
    REG_WR(VTSS_ANA_L3_QGRP_CFG(vid),
           VTSS_F_ANA_L3_QGRP_CFG_QGRP_IDX((e->hqos_id == VTSS_HQOS_ID_NONE) ? 0
                                                                             : (e->hqos_id + 1)) |
               VTSS_F_ANA_L3_QGRP_CFG_QGRP_OAM_TYPE(0));
#endif

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_vlan_mask_update(struct vtss_state_s *vtss_state,
                                     vtss_vid_t           vid,
                                     BOOL                 member[VTSS_PORTS])
{
    vtss_port_mask_t pmask;

    vtss_port_mask_get(vtss_state, member, &pmask);
    REG_WRX_PMASK(VTSS_ANA_L3_VLAN_MASK_CFG, vid, pmask);

    return vtss_fa_vlan_update(vtss_state, vid);
}

vtss_rc vtss_cil_l2_vlan_port_conf_update(struct vtss_state_s   *vtss_state,
                                          vtss_port_no_t         port_no,
                                          vtss_vlan_port_conf_t *conf)
{
    vtss_rc          rc = VTSS_RC_OK;
    BOOL             aware = TRUE, c_port = FALSE, s_port = FALSE, s_custom_port = FALSE;
    vtss_vid_t       uvid = conf->untagged_vid;
    u32              value = 0U, tpid = 0U, aware_dis, mask;
    vtss_port_mask_t pmask, pmask_zero;
    u32              port = VTSS_CHIP_PORT(port_no);

    /* Check port type */
    switch (conf->port_type) {
    case VTSS_VLAN_PORT_TYPE_UNAWARE: aware = FALSE; break;
    case VTSS_VLAN_PORT_TYPE_C:       c_port = TRUE; break;
    case VTSS_VLAN_PORT_TYPE_S:
        s_port = TRUE;
        tpid = 1U;
        break;
    case VTSS_VLAN_PORT_TYPE_S_CUSTOM:
        s_custom_port = TRUE;
        tpid = 2U;
        break;
    default: rc = VTSS_RC_ERROR; break;
    }
    VTSS_RC(rc);

    /* Port VLAN Configuration */
    REG_WRM(VTSS_ANA_CL_VLAN_CTRL(port),
            VTSS_F_ANA_CL_VLAN_CTRL_PORT_VID(conf->pvid) |
                VTSS_F_ANA_CL_VLAN_CTRL_VLAN_POP_CNT(aware ? 1U : 0U) |
                VTSS_F_ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA(aware),
            VTSS_M_ANA_CL_VLAN_CTRL_PORT_VID | VTSS_M_ANA_CL_VLAN_CTRL_VLAN_POP_CNT |
                VTSS_M_ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA);

    aware_dis = 0x7fffU;
    if (aware) {
        mask = 1U;
        mask <<= tpid;
        aware_dis -= mask;
    }
    REG_WR(VTSS_ANA_CL_VLAN_TPID_CTRL(port),
           VTSS_F_ANA_CL_VLAN_TPID_CTRL_BASIC_TPID_AWARE_DIS(aware_dis) |
               VTSS_F_ANA_CL_VLAN_TPID_CTRL_RT_TAG_CTRL(3));

    /* Drop Configuration based on port type and frame type */
    if (conf->frame_type == VTSS_VLAN_FRAME_TAGGED && aware) {
        /* Discard untagged and priority-tagged if aware and tagged-only allowed
         */
        value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_TAG_REQUIRED_ENA;
        value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_CTAG_DIS;
        value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_STAG_DIS;
        value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_CUST1_STAG_DIS;
        if (!c_port) {
            /* Discard C-tagged unless C-port */
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CTAG_DIS;
        }
        if (!s_port) {
            /* Discard S-tagged unless S-port */
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_STAG_DIS;
        }
        if (!s_custom_port) {
            /* Discard S-custom-tagged unless S-custom port */
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CUST1_STAG_DIS;
        }
    }

    if (conf->frame_type == VTSS_VLAN_FRAME_UNTAGGED) {
        if (c_port) {
            /* Discard C-tagged if C-port */
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CTAG_DIS;
        }
        if (s_port) {
            /* Discard S-tagged if S-port */
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_STAG_DIS;
        }
        if (s_custom_port) {
            /* Discard S-custom-tagged if S-custom port */
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CUST1_STAG_DIS;
        }
    }

    REG_WRM(VTSS_ANA_CL_VLAN_FILTER_CTRL(port, 0), value,
            VTSS_M_ANA_CL_VLAN_FILTER_CTRL_TAG_REQUIRED_ENA |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_CTAG_DIS |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_STAG_DIS |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_CUST1_STAG_DIS |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CTAG_DIS | VTSS_M_ANA_CL_VLAN_FILTER_CTRL_STAG_DIS |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CUST1_STAG_DIS);

    /* Second tag discard */
    value = 0U;
    if (aware) {
        if (conf->inner_tag_discard.no_tag) {
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_TAG_REQUIRED_ENA;
        }
        if (conf->inner_tag_discard.c_tag) {
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CTAG_DIS;
        }
        if (conf->inner_tag_discard.c_prio_tag) {
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_CTAG_DIS;
        }
        if (conf->inner_tag_discard.s_tag) {
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_STAG_DIS;
        }
        if (conf->inner_tag_discard.s_prio_tag) {
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_STAG_DIS;
        }
        if (conf->inner_tag_discard.s_custom_tag) {
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_STAG_DIS;
        }
        if (conf->inner_tag_discard.s_custom_prio_tag) {
            value |= VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CUST1_STAG_DIS;
        }
    }

    REG_WRM(VTSS_ANA_CL_VLAN_FILTER_CTRL(port, 1), value,
            VTSS_M_ANA_CL_VLAN_FILTER_CTRL_TAG_REQUIRED_ENA |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_CTAG_DIS |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_STAG_DIS |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_PRIO_CUST1_STAG_DIS |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CTAG_DIS | VTSS_M_ANA_CL_VLAN_FILTER_CTRL_STAG_DIS |
                VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CUST1_STAG_DIS);

    /* Ingress filtering */
    vtss_port_mask_clear(&pmask_zero);
    vtss_port_mask_port(vtss_state, port_no, &pmask);
    REG_WRM_PMASK(VTSS_ANA_L3_VLAN_FILTER_CTRL, conf->ingress_filter ? pmask : pmask_zero, pmask);

    /* Rewriter VLAN tag configuration */
    REG_WRM(VTSS_REW_TAG_CTRL(port),
            VTSS_F_REW_TAG_CTRL_TAG_CFG(uvid == VTSS_VID_ALL    ? 0
                                        : uvid == VTSS_VID_NULL ? 2
                                                                : 1) |
                VTSS_F_REW_TAG_CTRL_TAG_TPID_CFG(tpid),
            VTSS_M_REW_TAG_CTRL_TAG_CFG | VTSS_M_REW_TAG_CTRL_TAG_TPID_CFG);

    REG_WRM(VTSS_REW_PORT_VLAN_CFG(port), VTSS_F_REW_PORT_VLAN_CFG_PORT_VID(uvid),
            VTSS_M_REW_PORT_VLAN_CFG_PORT_VID);

#if defined(VTSS_FEATURE_VCAP) && defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    return vtss_fa_vcap_port_update(vtss_state, port_no);
#else
    return VTSS_RC_OK;
#endif
}

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
static vtss_rc fa_vlan_counters_update(vtss_state_t               *vtss_state,
                                       vtss_vid_t                  vid,
                                       vtss_vlan_counters_t *const counters,
                                       BOOL                        clear)
{
    vtss_vlan_chip_counters_t *cnt = &vtss_state->l2.vlan_counters_info.counters[vid];
    vtss_vlan_counter_types_t *vlan_counter;
    vtss_chip_counter_pair_t  *chip_counter;
    u32                        i, lsb, msb;

    if (!vtss_state->vtss_features[FEATURE_VLAN_COUNTERS]) {
        return VTSS_RC_ERROR;
    }

    if (vtss_state->init_conf.vlan_counters_disable) {
        return VTSS_RC_ERROR;
    }

    if (vid >= VTSS_EVC_STAT_CNT) {
        // Temporary workaround
        // Will be removed together with RT constants
        return VTSS_RC_OK;
    }

    for (i = 0; i < 3; i++) {
        chip_counter = (i == 0   ? &cnt->rx_unicast
                        : i == 1 ? &cnt->rx_multicast
                                 : &cnt->rx_broadcast);

        /* Update byte counter */
        REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(vid, i), &lsb);
        REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT(vid, i), &msb);
        vtss_cmn_counter_40_update(lsb, msb, &chip_counter->bytes, clear);

        /* Update frame counter */
        REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(vid, i + 3), &lsb);
        vtss_cmn_counter_32_update(lsb, &chip_counter->frames, clear);

        /* Update VLAN countes */
        if (counters != NULL) {
            vlan_counter = (i == 0   ? &counters->rx_vlan_unicast
                            : i == 1 ? &counters->rx_vlan_multicast
                                     : &counters->rx_vlan_broadcast);
            vlan_counter->frames = chip_counter->frames.value;
            vlan_counter->bytes = chip_counter->bytes.value;
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_vlan_counters_get(vtss_state_t         *vtss_state,
                                      vtss_vid_t            vid,
                                      vtss_vlan_counters_t *counters)
{
    return fa_vlan_counters_update(vtss_state, vid, counters, FALSE);
}

vtss_rc vtss_cil_l2_vlan_counters_clear(vtss_state_t *vtss_state, vtss_vid_t vid)
{
    return fa_vlan_counters_update(vtss_state, vid, NULL, TRUE);
}
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

#if defined(VTSS_FEATURE_VCAP)
vtss_rc vtss_cil_l2_vcl_port_conf_set(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no)
{
    vtss_vcl_port_conf_t *conf = &vtss_state->l2.vcl_port_conf[port_no];

    VTSS_RC(vtss_cmn_vcl_port_conf_set(vtss_state, port_no));

    /* Set port key */
    return vtss_fa_vcap_port_key_set(vtss_state, port_no, 2U, conf->key_type, conf->dmac_dip);
}
#endif

#if defined(VTSS_FEATURE_PSFP)
static u16 fa_psfp_sfid(const vtss_psfp_filter_id_t id) { return (id + 1U); }
#endif

#if defined(VTSS_FEATURE_XFLOW)
vtss_rc vtss_cil_l2_iflow_conf_set(struct vtss_state_s *vtss_state, const vtss_iflow_id_t id)
{

    vtss_sdx_entry_t  *sdx = vtss_iflow_lookup(vtss_state, id);
    vtss_port_mask_t   pmask;
    u32                isdx;
    vtss_iflow_conf_t *conf;
    BOOL               independent_mel = TRUE;
    BOOL               voe_valid = FALSE;
    vtss_voe_idx_t     voe_idx = 0U;

    if (sdx == NULL) {
        return VTSS_RC_ERROR;
    }
    vtss_port_mask_get(vtss_state, vtss_state->l2.port_all, &pmask);

    isdx = sdx->sdx;
    conf = &sdx->conf;
    REG_WRX_PMASK(VTSS_ANA_L2_PORT_MASK_CFG, isdx, pmask);

    REG_WR(VTSS_ANA_L2_MISC_CFG(isdx),
           VTSS_F_ANA_L2_MISC_CFG_CT_DIS(conf->cut_through_disable ? 1 : 0) |
               VTSS_F_ANA_L2_MISC_CFG_PIPELINE_PT(15));

    /* Use ISDX key in ES0 */
    REG_WR(VTSS_ANA_L2_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA(0));

#if defined(VTSS_FEATURE_QOS_OT)
    REG_WR(VTSS_ANA_L2_QGRP_CFG(isdx), VTSS_F_ANA_L2_QGRP_CFG_QGRP_ENA(conf->ot ? 1 : 0) |
                                           VTSS_F_ANA_L2_QGRP_CFG_QGRP_IDX(1) |
                                           VTSS_F_ANA_L2_QGRP_CFG_QGRP_OAM_TYPE(0));
#endif
#if defined(VTSS_FEATURE_HQOS)
    REG_WR(VTSS_ANA_L2_QGRP_CFG(isdx),
           VTSS_F_ANA_L2_QGRP_CFG_QGRP_ENA((conf->hqos_id == VTSS_HQOS_ID_NONE) ? 0 : 1) |
               VTSS_F_ANA_L2_QGRP_CFG_QGRP_IDX((conf->hqos_id == VTSS_HQOS_ID_NONE)
                                                   ? 0
                                                   : (conf->hqos_id + 1)) |
               VTSS_F_ANA_L2_QGRP_CFG_QGRP_OAM_TYPE(0));
#endif

    /* DLB/ISDX mappings */
    VTSS_RC(vtss_cil_l2_isdx_update(vtss_state, sdx));

#if defined(VTSS_FEATURE_VOP)
    if (conf->voe_idx < VTSS_PORT_VOE_BASE_IDX) {
        /* VOE reference, do not point at Port VOE */
        voe_idx = conf->voe_idx;
        voe_valid = TRUE;
    }
    if (conf->voe_idx != VTSS_VOE_IDX_NONE) {
        /* Independent MEL when no pointer to active VOE */
        independent_mel = FALSE;
    }
#endif
    REG_WR(VTSS_ANA_CL_OAM_MEP_CFG(isdx),
           VTSS_F_ANA_CL_OAM_MEP_CFG_MEP_IDX_ENA(voe_valid) |
               VTSS_F_ANA_CL_OAM_MEP_CFG_MEP_IDX(voe_idx) |
               VTSS_F_ANA_CL_OAM_MEP_CFG_INDEPENDENT_MEL_ENA(independent_mel));

#if defined(VTSS_FEATURE_VOP)
    /* MIP reference */
    REG_WR(VTSS_ANA_CL_ISDX_CFG(isdx),
           VTSS_F_ANA_CL_ISDX_CFG_MIP_IDX(conf->voi_idx == VTSS_EVC_MIP_IDX_NONE
                                              ? 0
                                              : vtss_fa_voi_idx_to_mip_idx(vtss_state,
                                                                           conf->voi_idx)));
#endif

#if defined(VTSS_FEATURE_FRER)
    if (vtss_state->vtss_features[FEATURE_FRER]) {
        REG_WR(VTSS_ANA_AC_FRER_GEN_FRER_GEN(isdx),
               VTSS_F_ANA_AC_FRER_GEN_FRER_GEN_RESET(1) |
                   VTSS_F_ANA_AC_FRER_GEN_FRER_GEN_ENABLE(conf->frer.generation));
        {
            vtss_xms_entry_t *ms;
            vtss_port_no_t    port_no;
            u32               port[8], cnt = 0;

            /* Build table of 8 FRER egress chip ports */
            if (conf->frer.mstream_enable) {
                ms = &vtss_state->l2.ms.table[conf->frer.mstream_id];
                if (ms->cnt > 0U) {
                    for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
                        if (VTSS_PORT_BF_GET(ms->port_list, port_no) && cnt < 8U) {
                            port[cnt] = VTSS_CHIP_PORT(port_no);
                            cnt++;
                        }
                    }
                }
            }
            for (; cnt < 8U; cnt++) {
                port[cnt] = 0x7f; /* Disable FRER for the rest */
            }
            REG_WR(VTSS_EACL_FRER_EGR_PORT(isdx, 0),
                   VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT0(port[0]) |
                       VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT1(port[1]) |
                       VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT2(port[2]) |
                       VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT3(port[3]));
            REG_WR(VTSS_EACL_FRER_EGR_PORT(isdx, 1),
                   VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT0(port[4]) |
                       VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT1(port[5]) |
                       VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT2(port[6]) |
                       VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT3(port[7]));
        }
    }
#endif

#if defined(VTSS_FEATURE_PSFP)
    if (vtss_state->vtss_features[FEATURE_PSFP]) {
        REG_WR(VTSS_ANA_L2_TSN_CFG(isdx),
               VTSS_F_ANA_L2_TSN_CFG_TSN_SFID(conf->psfp.filter_enable
                                                  ? fa_psfp_sfid(conf->psfp.filter_id)
                                                  : 0U));
    }
#endif
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_XSTAT)
vtss_rc vtss_cil_l2_icnt_get(struct vtss_state_s     *vtss_state,
                             u16                      idx,
                             vtss_ingress_counters_t *counters)
{
    vtss_stat_idx_t     sidx;
    vtss_evc_counters_t cnt;

    VTSS_MEMSET(&cnt, 0, sizeof(cnt));
    sidx.idx = idx;
    sidx.edx = 0;
    VTSS_RC(vtss_fa_sdx_counters_update(vtss_state, &sidx, &cnt, counters == NULL));

    if (counters != NULL) {
        VTSS_MEMSET(counters, 0, sizeof(*counters));
        counters->rx_green = cnt.rx_green;
        counters->rx_yellow = cnt.rx_yellow;
        counters->rx_red = cnt.rx_red;
        counters->rx_discard = cnt.rx_discard;
        counters->tx_discard = cnt.tx_discard;
#if defined(VTSS_FEATURE_PSFP)
        if (vtss_state->vtss_features[FEATURE_PSFP]) {
            if (vtss_state->init_conf.psfp_counters_enable) {
                counters->rx_match = counters->rx_green.bytes;
                counters->rx_green.bytes = 0;
                counters->rx_gate_discard = counters->rx_yellow.bytes;
                counters->rx_yellow.bytes = 0;
                counters->rx_sdu_discard = counters->rx_red.bytes;
                counters->rx_red.bytes = 0;
                if (LA_TGT) {
                    counters->rx_sdu_pass = (counters->rx_match - counters->rx_sdu_discard);
                    counters->rx_gate_pass = (counters->rx_sdu_pass - counters->rx_gate_discard);
                } else {
                    counters->rx_gate_pass = (counters->rx_match - counters->rx_gate_discard);
                    counters->rx_sdu_pass = (counters->rx_gate_pass - counters->rx_sdu_discard);
                }
            }
        }
#endif
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_ecnt_get(struct vtss_state_s    *vtss_state,
                             u16                     idx,
                             vtss_egress_counters_t *counters)
{
    vtss_stat_idx_t     sidx;
    vtss_evc_counters_t cnt;

    VTSS_MEMSET(&cnt, 0, sizeof(cnt));
    sidx.idx = 0;
    sidx.edx = idx;
    VTSS_RC(vtss_fa_sdx_counters_update(vtss_state, &sidx, &cnt, counters == NULL));

    if (counters != NULL) {
        counters->tx_green = cnt.tx_green;
        counters->tx_yellow = cnt.tx_yellow;
    }
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_EVC_STAT_CNT)
vtss_rc vtss_cil_l2_policer_update(struct vtss_state_s *vtss_state, const u16 idx)
{
// The vtss_fa_policer_conf_set() function is potentially changing members in
// the passed configuration to reflect what is actually written to hardware. On
// VELOCITYSP this is not accepted behaviour so a copy is passed.
#if VTSS_OPT_LIGHT
    vtss_dlb_policer_conf_t conf = vtss_state->l2.pol_conf[idx];
    return vtss_fa_policer_conf_set(vtss_state, idx, &conf);
#else
    return vtss_fa_policer_conf_set(vtss_state, idx, &vtss_state->l2.pol_conf[idx]);
#endif
}

vtss_rc vtss_cil_l2_counters_update(struct vtss_state_s *vtss_state,
                                    vtss_stat_idx_t     *sidx,
                                    BOOL                 clear)
{
    return vtss_fa_sdx_counters_update(vtss_state, sidx, NULL, clear);
}
#endif

/* ================================================================= *
 *  Layer 2 - PVLAN / Isolated ports
 * ================================================================= */

vtss_rc vtss_cil_l2_isolated_port_members_set(struct vtss_state_s *vtss_state)
{
    vtss_port_mask_t pmask;

    vtss_port_mask_get(vtss_state, vtss_state->l2.isolated_port, &pmask);
    REG_WR_PMASK(VTSS_ANA_L3_VLAN_ISOLATED_CFG, pmask);
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - IP Multicast
 * ================================================================= */

/* Update PGID state for reserved entry and update chip */
static vtss_rc fa_pgid_update(vtss_state_t *vtss_state, u32 pgid, BOOL member[VTSS_PORTS], BOOL resv)
{
    vtss_port_no_t     port_no;
    vtss_pgid_entry_t *pgid_entry;

    pgid = vtss_fa_vtss_pgid(vtss_state, pgid);
    pgid_entry = &vtss_state->l2.pgid_table[pgid];
    pgid_entry->resv = resv;
    pgid_entry->references = 1U;
    for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
        pgid_entry->member[port_no] = member[port_no];
    }
    return vtss_cil_l2_pgid_table_write(vtss_state, pgid, member);
}

vtss_rc vtss_cil_l2_flood_conf_set(struct vtss_state_s *vtss_state)
{
    vtss_l2_state_t *state = &vtss_state->l2;

    /* Unicast flood mask */
    VTSS_RC(fa_pgid_update(vtss_state, PGID_UC_FLOOD, state->uc_flood, TRUE));

    /* Multicast flood mask */
    VTSS_RC(fa_pgid_update(vtss_state, PGID_MC_FLOOD, state->mc_flood, TRUE));

    /* IPv4 multicast control flood mask */
    VTSS_RC(fa_pgid_update(vtss_state, PGID_IPV4_MC_CTRL, state->mc_flood, TRUE));

    /* IPv4 multicast data flood mask */
    VTSS_RC(fa_pgid_update(vtss_state, PGID_IPV4_MC_DATA, state->ipv4_mc_flood, TRUE));

    /* IPv6 multicast control flood mask */
    BOOL *p = (state->ipv6_mc_scope ? state->ipv6_mc_flood : state->mc_flood);
    VTSS_RC(fa_pgid_update(vtss_state, PGID_IPV6_MC_CTRL, p, TRUE));

    /* IPv6 MC data flood mask */
    VTSS_RC(fa_pgid_update(vtss_state, PGID_IPV6_MC_DATA, state->ipv6_mc_flood, TRUE));

    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - Mirror
 * ================================================================= */

/* Setup all mirroring */
vtss_rc vtss_cil_l2_mirror_conf_set(struct vtss_state_s *vtss_state)
{
    vtss_mirror_conf_t *conf = &vtss_state->l2.mirror_conf;
    vtss_port_no_t      port_no;
    u32                 probe, port = 0U, dir, vlan_mode, tx_port, rx_cpu, cpu_set, mask;
    vtss_port_mask_t    pmask;
    BOOL                member[VTSS_PORTS];

    /* Mirror port */
    if (conf->port_no != VTSS_PORT_NO_NONE) {
        port = VTSS_CHIP_PORT(conf->port_no);
    }

    /* Setup all probes */
    for (probe = FA_MIRROR_PROBE_RX; probe <= FA_MIRROR_PROBE_VLAN; probe++) {
        dir = 2U; /* Rx mirror by default */
        vlan_mode = 0U;
        tx_port = 0U;
        rx_cpu = 0U;
        cpu_set = 0U;

        if (conf->port_no == VTSS_PORT_NO_NONE || !vtss_state->l2.tx_forward_aggr[conf->port_no]) {
            /* Mirroring disabled or mirror port down */
            dir = 0U;
            vtss_port_mask_clear(&pmask);
        } else if (probe == FA_MIRROR_PROBE_RX) {
            /* Ingress probe */
            vtss_port_mask_get(vtss_state, vtss_state->l2.mirror_ingress, &pmask);
            if (vtss_state->l2.mirror_cpu_ingress) {
                rx_cpu = 0x3U; /* Enable Rx mirror from both CPU ports */
            }
        } else if (probe == FA_MIRROR_PROBE_TX) {
            /* Egress probe */
            dir = 1U;
            vtss_port_mask_get(vtss_state, vtss_state->l2.mirror_egress, &pmask);
            for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
                if (vtss_state->l2.mirror_egress[port_no]) {
                    /* The first egress port is used in the rewriter */
                    tx_port = VTSS_CHIP_PORT(port_no);
                    break;
                }
            }
            if (vtss_state->l2.mirror_cpu_egress) {
                cpu_set = 0xffU;
            }
        } else {
            /* VLAN probe */
            vlan_mode = 1U;
            for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
                member[port_no] = TRUE;
            }
            vtss_port_mask_get(vtss_state, member, &pmask);
        }

        /* QFWD frame copy */
        REG_WR(VTSS_QFWD_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_MIRROR_PROBE(probe)),
               VTSS_F_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL(port));

        /* Mirror Rx discards */
        mask = 1U;
        mask <<= probe;
        REG_WRM_CTL(VTSS_XQS_MIRROR_CFG, dir == 2U, VTSS_F_XQS_MIRROR_CFG_MIRROR_DISCARDS(mask));

        /* ANA_AC probe */
        REG_WR(VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG(probe),
               VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_RX_CPU_AND_VD(rx_cpu) |
                   VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_CPU_SET(cpu_set) |
                   VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_VLAN_MODE(vlan_mode) |
                   VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_DIRECTION(dir));
        REG_WRX_PMASK(VTSS_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG, probe, pmask);

        /* REW probe */
        REG_WR(VTSS_REW_MIRROR_TAG_A_CFG(probe),
               VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_PCP_SEL(1) |
                   VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_PCP_VAL(conf->pcp) |
                   VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_DEI_VAL(conf->dei) |
                   VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_VID_VAL(conf->vid) |
                   VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL(conf->tag == VTSS_MIRROR_TAG_S ? 1
                                                              : conf->tag ==
                                                                      VTSS_MIRROR_TAG_S_CUSTOM
                                                                  ? 2
                                                                  : 0));
        REG_WR(VTSS_REW_MIRROR_PROBE_CFG(probe),
               VTSS_F_REW_MIRROR_PROBE_CFG_MIRROR_TX_PORT(tx_port) |
                   VTSS_F_REW_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG(conf->tag == VTSS_MIRROR_TAG_NONE
                                                                     ? 0
                                                                     : 1));
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_IPV4_MC_SIP)
vtss_rc vtss_cil_l2_ip_mc_update(vtss_state_t     *vtss_state,
                                 vtss_ipmc_data_t *ipmc,
                                 vtss_ipmc_cmd_t   cmd)
{
    vtss_vcap_obj_t     *obj = &vtss_state->vcap.is2_b.obj;
    int                  user = (ipmc->src.ssm ? VTSS_IS2_USER_SSM : VTSS_IS2_USER_ASM);
    vtss_vcap_key_size_t key_size =
        (ipmc->ipv6 ? VTSS_VCAP_KEY_SIZE_HALF : VTSS_VCAP_KEY_SIZE_QUARTER);
    vtss_res_chg_t          res;
    vtss_vcap_data_t        data;
    vtss_is2_entry_t        entry;
    vtss_hace_t            *ace = &entry.ace;
    vtss_hace_frame_ipv4_t *ipv4 = &ace->key.ipv4;
    vtss_hace_frame_ipv6_t *ipv6 = &ace->key.ipv6;
    vtss_port_no_t          port_no;
    int                     i;

    if (cmd == VTSS_IPMC_CMD_CHECK) {
        VTSS_MEMSET(&res, 0, sizeof(res));
        if (ipmc->dst_add) {
            res.add_key[key_size] = 1;
        }
        return vtss_cmn_vcap_res_check(obj, &res);
    }

    if (cmd == VTSS_IPMC_CMD_DEL) {
        return vtss_vcap_del(vtss_state, obj, user, ipmc->dst.id);
    }

    /* Add entry */
    vtss_vcap_is2_init(&data, &entry);
    data.key_size = key_size;
    entry.ipmc = TRUE;
    ace->key.vlan.vid.value = ipmc->src.vid;
    ace->key.vlan.vid.mask = 0xfff;
    if (ipmc->ipv6) {
        for (i = 0; i < 16; i++) {
            ipv6->sip.value[i] = ipmc->src.sip.ipv6.addr[i];
            ipv6->sip.mask[i] = (ipmc->src.ssm ? 0xff : 0);
            ipv6->dip.value[i] = ipmc->dst.dip.ipv6.addr[i];
            ipv6->dip.mask[i] = 0xff;
        }
    } else {
        ipv4->sip.value = ipmc->src.sip.ipv4;
        ipv4->sip.mask = (ipmc->src.ssm ? 0xffffffff : 0);
        ipv4->dip.value = ipmc->dst.dip.ipv4;
        ipv4->dip.mask = 0xffffffff;
    }
    ace->action.port_action = VTSS_ACL_PORT_ACTION_PGID;
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        ace->action.port_list[port_no] = VTSS_PORT_BF_GET(ipmc->dst.member, port_no);
    }
    return vtss_vcap_add(vtss_state, obj, user, ipmc->dst.id, ipmc->id_next, &data, 0);
}
#endif

vtss_rc vtss_cil_l2_aggr_table_write(struct vtss_state_s *vtss_state,
                                     u32                  ac,
                                     BOOL                 member[VTSS_PORTS])
{
    vtss_port_mask_t pmask;

    vtss_port_mask_get(vtss_state, member, &pmask);
    REG_WRX_PMASK(VTSS_ANA_AC_AGGR_AGGR_CFG, ac, pmask);

    /* Setup mirroring when the first aggregation mask is setup */
    return (ac == 0U ? vtss_cil_l2_mirror_conf_set(vtss_state) : VTSS_RC_OK);
}

/* ================================================================= *
 *  SFLOW
 * ================================================================= */

static u32 next_power_of_two(u32 x)
{
    --x;
    x |= x >> 1U;
    x |= x >> 2U;
    x |= x >> 4U;
    x |= x >> 8U;
    x |= x >> 16U;
    x++;
    return x;
}

static u32 fa_sflow_hw_rate(const u32 desired_sw_rate, u32 *const realizable_sw_rate)
{
    u32 hw_rate = (desired_sw_rate > 0U
                       ? MAX(VTSS_ROUNDING_DIVISION(FA_SFLOW_MAX_SAMPLE_RATE, desired_sw_rate),
                             FA_SFLOW_MIN_SAMPLE_RATE)
                       : 0U);
    *realizable_sw_rate =
        (hw_rate > 0U ? VTSS_ROUNDING_DIVISION(FA_SFLOW_MAX_SAMPLE_RATE, hw_rate) : 0U);
    return hw_rate;
}

vtss_rc vtss_cil_l2_sflow_sampling_rate_convert(struct vtss_state_s *const state,
                                                const BOOL                 power2,
                                                const u32                  rate_in,
                                                u32 *const                 rate_out)
{
    u32 modified_rate_in;
    // Could happen that two threads call this function simultaneously at boot,
    // but we take the risk. Once sflow_max_power_of_two has been computed, it's
    // no longer a problem with simultaneous access.
    u32 sflow_max_power_of_two = state->l2.sflow_max_power_of_two;

    if (sflow_max_power_of_two == 0U) {
        sflow_max_power_of_two = next_power_of_two(FA_SFLOW_MAX_SAMPLE_RATE);
        if ((FA_SFLOW_MAX_SAMPLE_RATE & sflow_max_power_of_two) == 0U) {
            sflow_max_power_of_two >>= 1;
        }
        state->l2.sflow_max_power_of_two = sflow_max_power_of_two;
    }

    // Compute the actual sampling rate given the user input.
    if (rate_in != 0U && power2) {
        // Round off to the nearest power of two.
        u32 temp1 = next_power_of_two(rate_in);
        u32 temp2 = temp1 >> 1U;
        if (temp1 - rate_in < rate_in - temp2) {
            modified_rate_in = temp1;
        } else {
            modified_rate_in = temp2;
        }
        if (modified_rate_in == 0U) {
            modified_rate_in = 1U;
        } else if (modified_rate_in > sflow_max_power_of_two) {
            modified_rate_in = sflow_max_power_of_two;
        } else {
            // Empty on purpose
        }
    } else {
        modified_rate_in = rate_in;
    }

    (void)fa_sflow_hw_rate(modified_rate_in, rate_out);
    return VTSS_RC_OK;
}

// Note that Jaguar2 has a sFlow-related bug, ref bug#12246
vtss_rc vtss_cil_l2_sflow_port_conf_set(struct vtss_state_s                *vtss_state,
                                        const vtss_port_no_t                port_no,
                                        const vtss_sflow_port_conf_t *const conf)
{
#define FA_SFLOW_ENABLED(_conf_)                                                                   \
    ((_conf_)->sampling_rate > 0U && (_conf_)->type != VTSS_SFLOW_TYPE_NONE)
    vtss_sflow_port_conf_t *cur_conf = &vtss_state->l2.sflow_conf[port_no];
    u32                     hw_rate;
    BOOL                    globally_enable;

    globally_enable = vtss_state->l2.sflow_ena_cnt > 0U;

    if (FA_SFLOW_ENABLED(conf) && !FA_SFLOW_ENABLED(cur_conf)) {
        if (vtss_state->l2.sflow_ena_cnt == VTSS_PORTS) {
            VTSS_E("sFlow enable counter out of sync");
        }
        if (vtss_state->l2.sflow_ena_cnt++ == 0U) {
            globally_enable = TRUE;
        }
    } else if (!FA_SFLOW_ENABLED(conf) && FA_SFLOW_ENABLED(cur_conf)) {
        if (vtss_state->l2.sflow_ena_cnt == 0U) {
            VTSS_E("sFlow enable counter out of sync");
        } else if (--vtss_state->l2.sflow_ena_cnt == 0U) {
            globally_enable = FALSE;
        } else {
            // Empty on purpose
        }
    } else {
        // Empty on purpose
    }

    *cur_conf = *conf;

    REG_WRM(VTSS_ANA_AC_PS_COMMON_PS_COMMON_CFG,
            VTSS_F_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA(globally_enable),
            VTSS_M_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA);

    // Compute the actual sampling rate given the user input.
    // If the user requires power-of-two sampling rates, he is supposed to have
    // provided such a sampling rate in #conf. We must ensure that
    // power-of-two input sampling rates gives the same power-of-two output
    // sampling rate.
    hw_rate = fa_sflow_hw_rate(conf->sampling_rate, &cur_conf->sampling_rate);

    REG_WRM(VTSS_ANA_AC_SFLOW_SFLOW_CTRL(VTSS_CHIP_PORT(port_no)),
            VTSS_F_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_DIR_SEL(conf->type == VTSS_SFLOW_TYPE_NONE ? 0
                                                         : conf->type == VTSS_SFLOW_TYPE_RX ? 1
                                                         : conf->type == VTSS_SFLOW_TYPE_TX ? 2
                                                                                            : 3) |
                VTSS_F_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_SAMPLE_RATE(hw_rate),
            VTSS_M_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_DIR_SEL |
                VTSS_M_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_SAMPLE_RATE);

    return VTSS_RC_OK;
#undef FA_SFLOW_ENABLED
}

/* ================================================================= *
 *  FRER
 * ================================================================= */
#if defined(VTSS_FEATURE_FRER)
vtss_rc vtss_cil_l2_cstream_conf_set(struct vtss_state_s         *vtss_state,
                                     const vtss_frer_cstream_id_t id)
{
    vtss_frer_stream_conf_t *conf = &vtss_state->l2.cstream_conf[id];
    BOOL                     vector = (conf->alg == VTSS_FRER_RECOVERY_ALG_VECTOR);
    u32                      hlen = conf->hlen;

    if (!vtss_state->vtss_features[FEATURE_FRER]) {
        return VTSS_RC_ERROR;
    }

    REG_WR(VTSS_EACL_FRER_CFG_COMPOUND(id),
           VTSS_F_EACL_FRER_CFG_COMPOUND_TAKE_NO_SEQUENCE(conf->take_no_seq ? 1 : 0) |
               VTSS_F_EACL_FRER_CFG_COMPOUND_VECTOR_ALGORITHM(vector) |
               VTSS_F_EACL_FRER_CFG_COMPOUND_HISTORY_LENGTH(hlen < 2U ? 1U : (hlen - 1U)) |
               VTSS_F_EACL_FRER_CFG_COMPOUND_RESET_TICKS(conf->reset_time > 0U ? conf->reset_time
                                                                               : 1U) |
               VTSS_F_EACL_FRER_CFG_COMPOUND_RESET(1) |
               VTSS_F_EACL_FRER_CFG_COMPOUND_ENABLE(conf->recovery));
    if (conf->recovery) {
        vtss_state->l2.cs_counters[id].resets.value++;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_mstream_conf_set(struct vtss_state_s *vtss_state, const u16 idx)
{
    vtss_frer_stream_conf_t *conf = &vtss_state->l2.mstream_conf[idx];
    BOOL                     vector = (conf->alg == VTSS_FRER_RECOVERY_ALG_VECTOR);
    u32                      hlen = conf->hlen;

    if (!vtss_state->vtss_features[FEATURE_FRER]) {
        return VTSS_RC_ERROR;
    }

    REG_WR(VTSS_EACL_FRER_CFG_MEMBER(idx),
           VTSS_F_EACL_FRER_CFG_MEMBER_TAKE_NO_SEQUENCE(conf->take_no_seq ? 1 : 0) |
               VTSS_F_EACL_FRER_CFG_MEMBER_VECTOR_ALGORITHM(vector) |
               VTSS_F_EACL_FRER_CFG_MEMBER_HISTORY_LENGTH(hlen < 2U ? 1U : (hlen - 1U)) |
               VTSS_F_EACL_FRER_CFG_MEMBER_RESET_TICKS(conf->reset_time > 0U ? conf->reset_time
                                                                             : 1U) |
               VTSS_F_EACL_FRER_CFG_MEMBER_RESET(1) |
               VTSS_F_EACL_FRER_CFG_MEMBER_ENABLE(conf->recovery) |
               VTSS_F_EACL_FRER_CFG_MEMBER_COMPOUND_HANDLE(conf->cstream_id));
    if (conf->recovery) {
        vtss_state->l2.ms_counters[idx].resets.value++;
    }
    return VTSS_RC_OK;
}

#define FRER_CNT(name, i, cnt, clr)                                                                \
    {                                                                                              \
        u32 value;                                                                                 \
        REG_RD(VTSS_EACL_CNT_##name(i), &value);                                                   \
        vtss_cmn_counter_32_update(value, cnt, clr);                                               \
    }

static vtss_rc fa_frer_cnt_get(vtss_frer_chip_counters_t *c, vtss_frer_counters_t *counters)
{
    if (counters != NULL) {
        counters->out_of_order_packets = c->out_of_order_packets.value;
        counters->rogue_packets = c->rogue_packets.value;
        counters->passed_packets = c->passed_packets.value;
        counters->discarded_packets = c->discarded_packets.value;
        counters->lost_packets = c->lost_packets.value;
        counters->tagless_packets = c->tagless_packets.value;
        counters->resets = c->resets.value;
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_cstream_cnt_update(vtss_state_t                *vtss_state,
                                     const vtss_frer_cstream_id_t id,
                                     vtss_frer_counters_t        *counters,
                                     BOOL                         clr)
{
    vtss_frer_chip_counters_t *c = &vtss_state->l2.cs_counters[id];

    if (!vtss_state->vtss_features[FEATURE_FRER]) {
        return VTSS_RC_ERROR;
    }

    FRER_CNT(COMPOUND_OUTOFORDER, id, &c->out_of_order_packets, clr);
    FRER_CNT(COMPOUND_ROGUE, id, &c->rogue_packets, clr);
    FRER_CNT(COMPOUND_PASSED, id, &c->passed_packets, clr);
    FRER_CNT(COMPOUND_DISCARDED, id, &c->discarded_packets, clr);
    FRER_CNT(COMPOUND_LOST, id, &c->lost_packets, clr);
    FRER_CNT(COMPOUND_TAGLESS, id, &c->tagless_packets, clr);
    FRER_CNT(COMPOUND_RESETS, id, &c->resets, clr);
    return fa_frer_cnt_get(c, counters);
}

vtss_rc vtss_cil_l2_cstream_cnt_get(struct vtss_state_s         *vtss_state,
                                    const vtss_frer_cstream_id_t id,
                                    vtss_frer_counters_t        *counters)
{
    return fa_cstream_cnt_update(vtss_state, id, counters, counters == NULL);
}

static vtss_rc fa_mstream_cnt_update(vtss_state_t         *vtss_state,
                                     const u16             idx,
                                     vtss_frer_counters_t *counters,
                                     BOOL                  clr)
{
    vtss_frer_chip_counters_t *c = &vtss_state->l2.ms_counters[idx];

    if (!vtss_state->vtss_features[FEATURE_FRER]) {
        return VTSS_RC_ERROR;
    }

    FRER_CNT(MEMBER_OUTOFORDER, idx, &c->out_of_order_packets, clr);
    FRER_CNT(MEMBER_ROGUE, idx, &c->rogue_packets, clr);
    FRER_CNT(MEMBER_PASSED, idx, &c->passed_packets, clr);
    FRER_CNT(MEMBER_DISCARDED, idx, &c->discarded_packets, clr);
    FRER_CNT(MEMBER_LOST, idx, &c->lost_packets, clr);
    FRER_CNT(MEMBER_TAGLESS, idx, &c->tagless_packets, clr);
    FRER_CNT(MEMBER_RESETS, idx, &c->resets, clr);
    return fa_frer_cnt_get(c, counters);
}

vtss_rc vtss_cil_l2_mstream_cnt_get(struct vtss_state_s  *vtss_state,
                                    const u16             idx,
                                    vtss_frer_counters_t *counters)
{
    return fa_mstream_cnt_update(vtss_state, idx, counters, counters == NULL);
}
#endif

#if defined(VTSS_FEATURE_PSFP)
static u16 fa_psfp_sgid(const vtss_psfp_gate_id_t id) { return (id + 1U); }

static u32 fa_psfp_prio(vtss_opt_prio_t *prio)
{
    return (prio->value + (prio->enable ? 0x8U : 0U));
}

vtss_rc vtss_cil_l2_psfp_gate_conf_set(struct vtss_state_s      *vtss_state,
                                       const vtss_psfp_gate_id_t id)
{
    vtss_psfp_state_t     *psfp = &vtss_state->l2.psfp;
    vtss_psfp_gate_conf_t *conf = &psfp->gate[id];
    vtss_psfp_gcl_conf_t  *gcl_conf = &conf->config;
    vtss_psfp_gcl_t       *gcl = &psfp->admin_gcl[id];
    vtss_psfp_gce_t       *gce;
    u32                    i, t = 0U, sgid = fa_psfp_sgid(id);

    if (!vtss_state->vtss_features[FEATURE_PSFP]) {
        return VTSS_RC_ERROR;
    }

    REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL, VTSS_F_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL_SGID(sgid));
    REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_1,
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_1_BASE_TIME_NSEC(gcl_conf->base_time.nanoseconds));
    REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_2,
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_2_BASE_TIME_SEC_LSB(gcl_conf->base_time.seconds));
    REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3,
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_BASE_TIME_SEC_MSB(gcl_conf->base_time.sec_msb) |
               VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_LIST_LENGTH(gcl->gcl_length) |
               VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_GATE_ENABLE(conf->enable) |
               VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_INIT_IPS(fa_psfp_prio(&conf->prio)) |
               VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_INIT_GATE_STATE(conf->gate_open ? 1 : 0) |
               VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_INVALID_RX_ENA(conf->close_invalid_rx.enable
                                                                          ? 1
                                                                          : 0) |
               VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_INVALID_RX(conf->close_invalid_rx.value
                                                                      ? 1
                                                                      : 0) |
               VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_OCTETS_EXCEEDED_ENA(conf->close_octets_exceeded
                                                                                   .enable
                                                                               ? 1
                                                                               : 0) |
               VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_OCTETS_EXCEEDED(conf->close_octets_exceeded
                                                                               .value
                                                                           ? 1
                                                                           : 0));
    REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_4,
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_4_CYCLE_TIME(gcl_conf->cycle_time));
    REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_5,
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_5_CYCLE_TIME_EXT(gcl_conf->cycle_time_ext));
    for (i = 0U; i < gcl->gcl_length; i++) {
        gce = &gcl->gce[i];
        REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_GCL_GS_CONFIG(i),
               VTSS_F_ANA_AC_SG_CONFIG_SG_GCL_GS_CONFIG_IPS(fa_psfp_prio(&gce->prio)) |
                   VTSS_F_ANA_AC_SG_CONFIG_SG_GCL_GS_CONFIG_GATE_STATE(gce->gate_open ? 1 : 0));
        t += gce->time_interval;
        REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_GCL_TI_CONFIG(i),
               VTSS_F_ANA_AC_SG_CONFIG_SG_GCL_TI_CONFIG_TIME_INTERVAL(t));
        REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_GCL_OCT_CONFIG(i),
               VTSS_F_ANA_AC_SG_CONFIG_SG_GCL_OCT_CONFIG_INTERVAL_OCTET_MAX(gce->octet_max));
    }
    if (conf->enable && conf->config_change) {
        REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL,
               VTSS_F_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL_SGID(sgid) |
                   VTSS_F_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL_CONFIG_CHANGE(1));
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_psfp_gate_status_get(struct vtss_state_s           *vtss_state,
                                         const vtss_psfp_gate_id_t      id,
                                         vtss_psfp_gate_status_t *const status)
{
    u32 value, prio, sgid = fa_psfp_sgid(id);
    u64 tc;

    if (!vtss_state->vtss_features[FEATURE_PSFP]) {
        return VTSS_RC_ERROR;
    }

    REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL, VTSS_F_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL_SGID(sgid));
    REG_RD(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_1, &value);
    status->config_change_time.nanoseconds =
        VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_1_CFG_CHG_TIME_NSEC(value);
    REG_RD(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_2, &value);
    status->config_change_time.seconds =
        VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_2_CFG_CHG_TIME_SEC_LSB(value);
    REG_RD(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_3, &value);
    status->config_change_time.sec_msb =
        (u16)VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_3_CFG_CHG_TIME_SEC_MSB(value);
    status->gate_open = (VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_3_GATE_STATE(value) > 0U);
    prio = VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_3_IPS(value);
    status->prio.enable = ((prio & 0x8U) > 0U);
    status->prio.value = (prio & 0x7U);
    status->config_pending = (VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_3_CONFIG_PENDING(value) > 0U);
    REG_RD(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3, &value);
    status->close_invalid_rx = (VTSS_X_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_INVALID_RX(value) > 0U);
    status->close_octets_exceeded =
        (VTSS_X_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_OCTETS_EXCEEDED(value) > 0U);
    return _vtss_ts_domain_timeofday_get(vtss_state, vtss_state->ts.conf.tsn_domain,
                                         &status->current_time, &tc);
}

vtss_rc vtss_cil_l2_psfp_filter_conf_set(struct vtss_state_s        *vtss_state,
                                         const vtss_psfp_filter_id_t id)
{
    vtss_psfp_filter_conf_t *conf = &vtss_state->l2.psfp.filter[id];
    u32                      max_sdu =
        (conf->max_sdu > 0U ? conf->max_sdu : VTSS_M_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_MAX_SDU);

    if (!vtss_state->vtss_features[FEATURE_PSFP]) {
        return VTSS_RC_ERROR;
    }

    REG_WR(VTSS_ANA_AC_TSN_SF_CFG_TSN_SF_CFG(fa_psfp_sfid(id)),
           VTSS_F_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_SGID(conf->gate_enable
                                                            ? fa_psfp_sgid(conf->gate_id)
                                                            : 0U) |
               VTSS_F_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_MAX_SDU(max_sdu) |
               VTSS_F_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_STREAM_BLOCK_OVERSIZE_ENA(conf->block_oversize
                                                                                         .enable
                                                                                     ? 1
                                                                                     : 0) |
               VTSS_F_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_STREAM_BLOCK_OVERSIZE_STATE(
                   conf->block_oversize.value ? 1 : 0));

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_psfp_filter_status_get(struct vtss_state_s             *vtss_state,
                                           const vtss_psfp_filter_id_t      id,
                                           vtss_psfp_filter_status_t *const status)
{
    u32 value;

    if (!vtss_state->vtss_features[FEATURE_PSFP]) {
        return VTSS_RC_ERROR;
    }

    REG_RD(VTSS_ANA_AC_TSN_SF_CFG_TSN_SF_CFG(fa_psfp_sfid(id)), &value);
    value = VTSS_X_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_STREAM_BLOCK_OVERSIZE_STATE(value);
    status->block_oversize = (value > 0U);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_policer_status_get(struct vtss_state_s             *vtss_state,
                                       const u16                        idx,
                                       vtss_dlb_policer_status_t *const status)
{
    if (!vtss_state->vtss_features[FEATURE_PSFP]) {
        return VTSS_RC_ERROR;
    }

    *status = vtss_state->l2.pol_status[idx];
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_REDBOX)
static u32 fa_rb_tgt(const vtss_rb_id_t rb_id)
{
    u32 id = rb_id;
    return RB_TGT(id);
}

vtss_rc vtss_cil_l2_rb_cap_get(struct vtss_state_s *vtss_state,
                               const vtss_rb_id_t   rb_id,
                               vtss_rb_cap_t *const cap)
{
    vtss_port_no_t port_no;
    u32            port, id;

    for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
        if (!vtss_state->vtss_features[FEATURE_REDBOX]) {
            cap->port_list[port_no] = FALSE;
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        id = (port < 8U    ? 0U
              : port < 16U ? 1U
              : port < 24U ? 2U
              : port < 26U ? 3U
              : port < 28U ? 4U
                           : 0U);
        cap->port_list[port_no] = (id == rb_id);
    }
    return VTSS_RC_OK;
}

#define FA_RB_MODE_PRP_SAN 0U
#define FA_RB_MODE_HSR_SAN 1U
#define FA_RB_MODE_HSR_PRP 2U
#define FA_RB_MODE_HSR_HSR 3U

#define VTSS_RB_PORT_CNT 3U

// Age field
#define FA_RB_AGE_CNT REG_FLD_CNT(RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_0)

#define FA_RB_AGE_IDX_NT  0U
#define FA_RB_AGE_IDX_PNT 1U

// Host entry type
#define FA_HT_PROXY 0U
#define FA_HT_DAN   1U
#define FA_HT_SAN   2U
#define FA_HT_LOCAL 3U
#define FA_HT_NONE  4U

// Host table rows and columns
#define FA_HT_COL_CNT REG_FLD_CNT(RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL)
#define FA_HT_ROW_CNT REG_FLD_CNT(RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW)
#define FA_HT_CNT     (FA_HT_COL_CNT * FA_HT_ROW_CNT)

// Host table commands
#define FA_HT_CMD_LEARN   0U
#define FA_HT_CMD_UNLEARN 1U
#define FA_HT_CMD_LOOKUP  2U
#define FA_HT_CMD_READ    3U
#define FA_HT_CMD_WRITE   4U
#define FA_HT_CMD_CLEAR   7U

// Maximum number of reads in get-next before exit/enter
#define FA_HT_READ_MAX 64U

// Duplicate discard table rows and columns
#define FA_DT_COL_CNT REG_FLD_CNT(RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL)
#define FA_DT_ROW_CNT REG_FLD_CNT(RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW)
#define FA_DT_CNT     (FA_DT_COL_CNT * FA_DT_ROW_CNT)

// Duplicate discard table commands
#define FA_DT_CMD_READ  3U
#define FA_DT_CMD_CLEAR 7U

// Tag modes
#define FA_RB_TAG_NONE     0U
#define FA_RB_TAG_PRP_NONE 1U
#define FA_RB_TAG_HSR      2U
#define FA_RB_TAG_PRP      3U

// HSR tag filter
#define FA_RB_FLT_NONE    0U
#define FA_RB_FLT_HSR     1U
#define FA_RB_FLT_NOT_HSR 2U
#define FA_RB_FLT_REDIR   3U

// Supervision frame forwarding
#define FA_RB_SV_FORWARD  0U
#define FA_RB_SV_CPU_COPY 1U
#define FA_RB_SV_CPU_ONLY 2U
#define FA_RB_SV_DISCARD  3U

// Forwarding masks
#define FA_RB_MSK_NONE 0x0U // No ports
#define FA_RB_MSK_AB   0x3U // LRE ports (A/B)
#define FA_RB_MSK_C    0x4U // Interlink (C)
#define FA_RB_MSK_ALL  0x7U // All ports (A/B/C)

// PTP awareness
#define FA_RB_PTP_NONE 0U
#define FA_RB_PTP_ETH  1U
#define FA_RB_PTP_IPV4 2U
#define FA_RB_PTP_IPV6 3U

static u32 fa_rb_sv(vtss_rb_sv_t sv)
{
    return (sv == VTSS_RB_SV_DISCARD    ? FA_RB_SV_DISCARD
            : sv == VTSS_RB_SV_CPU_COPY ? FA_RB_SV_CPU_COPY
            : sv == VTSS_RB_SV_CPU_ONLY ? FA_RB_SV_CPU_ONLY
                                        : FA_RB_SV_FORWARD);
}

static u32 fa_rb_age_unit(u32 unit)
{
    return (unit == 0U ? 32U : unit == 1U ? 256U : unit == 2U ? 4096U : 65536U);
}

static vtss_rc fa_rb_host_cmd(vtss_state_t *vtss_state, const vtss_rb_id_t rb_id, u32 cmd, u32 idx)
{
    u32 val, tgt = fa_rb_tgt(rb_id);

    REG_WR(VTSS_RB_HOST_ACCESS_CTRL(tgt),
           VTSS_F_RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL(idx % FA_HT_COL_CNT) |
               VTSS_F_RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW(idx / FA_HT_COL_CNT) |
               VTSS_F_RB_HOST_ACCESS_CTRL_CPU_ACCESS_CMD(cmd) |
               VTSS_F_RB_HOST_ACCESS_CTRL_HOST_TABLE_ACCESS_SHOT(1));
    do {
        REG_RD(VTSS_RB_HOST_ACCESS_CTRL(tgt), &val);
    } while (VTSS_X_RB_HOST_ACCESS_CTRL_HOST_TABLE_ACCESS_SHOT(val) > 0U);
    return VTSS_RC_OK;
}

static vtss_rc fa_rb_port_conf_set(vtss_state_t      *vtss_state,
                                   const vtss_rb_id_t rb_id,
                                   u32                j,
                                   vtss_rb_conf_t    *conf)
{
    u32  tgt = fa_rb_tgt(rb_id);
    u32  tag_mode = FA_RB_TAG_NONE, ht = FA_HT_NONE;
    u32  age, trans_netid = 0U, hsr_filter = FA_RB_FLT_NONE, dupl_disc = 1U;
    u32  lan_id = conf->lan_id, netid = conf->net_id;
    u32  prxy_smac_msk = FA_RB_MSK_ALL, prxy_dmac_msk = FA_RB_MSK_ALL;
    u32  node_smac_msk = FA_RB_MSK_ALL, node_dmac_msk = FA_RB_MSK_ALL;
    u32  sv, pnt_ena = 1U;
    BOOL lre, hsr_aware = FALSE, prp_aware = FALSE;

    lre = (j < 2U);
    switch (conf->mode) {
    case VTSS_RB_MODE_PRP_SAN:
        if (lre) {
            tag_mode = FA_RB_TAG_PRP_NONE;
            prp_aware = TRUE;
            lan_id = (j & 1U);
            ht = FA_HT_SAN; // Learn SANs on LREs
            netid = 5U;
        } else {
            ht = FA_HT_PROXY; // Learn proxy nodes on Interlink
            dupl_disc = 0U;
        }
        break;
    case VTSS_RB_MODE_HSR_SAN:
        if (lre) {
            tag_mode = FA_RB_TAG_HSR;
            hsr_aware = TRUE;
            lan_id = (j & 1U);
            prxy_smac_msk = FA_RB_MSK_AB;   // Discard on Interlink if SMAC is proxy
            ht = FA_HT_DAN;                 // Learn nodes on LREs
            hsr_filter = FA_RB_FLT_NOT_HSR; // Discard non-HSR-tagged frames on LRE
        } else {
            prxy_dmac_msk = FA_RB_MSK_NONE; // Discard on LRE if DMAC is proxy
            ht = FA_HT_PROXY;               // Learn proxy nodes on Interlink
            hsr_filter = FA_RB_FLT_HSR;     // Discard HSR-tagged frames on Interlink
        }
        break;
    case VTSS_RB_MODE_HSR_PRP:
        if (lre) {
            tag_mode = FA_RB_TAG_HSR;
            hsr_aware = TRUE;
            prxy_smac_msk = FA_RB_MSK_AB;   // Discard on Interlink if SMAC is proxy
            ht = FA_HT_DAN;                 // Learn nodes on LREs
            hsr_filter = FA_RB_FLT_NOT_HSR; // Discard non-HSR-tagged frames on LRE
        } else {
            tag_mode = FA_RB_TAG_PRP_NONE;
            prp_aware = TRUE;
            prxy_dmac_msk = FA_RB_MSK_NONE; // Discard on LRE if DMAC is proxy
            ht = FA_HT_PROXY;               // Learn proxy nodes on Interlink
            hsr_filter = FA_RB_FLT_HSR;     // Discard HSR-tagged frames on Interlink
            netid = 5U;
        }
        break;
    case VTSS_RB_MODE_HSR_HSR:
        tag_mode = FA_RB_TAG_HSR;
        hsr_aware = TRUE;
        if (lre) {
            ht = FA_HT_DAN;                 // Learn nodes on LREs
            hsr_filter = FA_RB_FLT_NOT_HSR; // Discard non-HSR-tagged frames on LRE
        } else {
            trans_netid = conf->net_id;
            pnt_ena = 0U; // Don't enable PNT on interlink port
        }
        break;
    default:
        // Empty on purpose
        break;
    }

    if (hsr_aware && lre) {
        // Common forwarding rules for HSR aware LRE ports
        if (!conf->nt_dmac_disable) {
            node_dmac_msk = FA_RB_MSK_AB; // Discard on Interlink if DMAC is node
        }

        // If Mode U is enabled, forward frames with DMAC in PNT to I/L and
        // other LRE port. Otherwise only forward it to I/L.
        prxy_dmac_msk = conf->mode_u ? FA_RB_MSK_ALL : FA_RB_MSK_C;
    }

    age = (ht == FA_HT_PROXY ? FA_RB_AGE_IDX_PNT : FA_RB_AGE_IDX_NT);
    REG_WR(VTSS_RB_TBL_CFG(tgt, j),
           VTSS_F_RB_TBL_CFG_CLR_AGE_FLAG_DIS(1) | VTSS_F_RB_TBL_CFG_DUPL_DISC_ENA(dupl_disc) |
               VTSS_F_RB_TBL_CFG_HOST_TYPE(ht) | VTSS_F_RB_TBL_CFG_HOST_AGE_INTERVAL(age) |
               VTSS_F_RB_TBL_CFG_UPD_DISC_TBL_ENA(1) | VTSS_F_RB_TBL_CFG_UPD_HOST_TBL_ENA(pnt_ena) |
               VTSS_F_RB_TBL_CFG_UPD_SEQ_NUM_ENA(1) |
               VTSS_F_RB_TBL_CFG_NEW_HOST_TBL_DIS(ht == FA_HT_NONE ? 1 : 0));

    REG_WR(VTSS_RB_BPDU_CFG(tgt, j), VTSS_F_RB_BPDU_CFG_BPDU_REDIR_ENA(lre ? 0xffff : 0));

    REG_WR(VTSS_RB_FWD_CFG(tgt, j), VTSS_F_RB_FWD_CFG_FLD_DST_FWD_MASK(FA_RB_MSK_ALL) |
                                        VTSS_F_RB_FWD_CFG_SRC_FWD_MASK(FA_RB_MSK_ALL) |
                                        VTSS_F_RB_FWD_CFG_PROXY_DST_FWD_MASK(prxy_dmac_msk) |
                                        VTSS_F_RB_FWD_CFG_LOCAL_DST_FWD_MASK(prxy_dmac_msk) |
                                        VTSS_F_RB_FWD_CFG_NODE_DST_FWD_MASK(node_dmac_msk) |
                                        VTSS_F_RB_FWD_CFG_PROXY_SRC_FWD_MASK(prxy_smac_msk) |
                                        VTSS_F_RB_FWD_CFG_LOCAL_SRC_FWD_MASK(prxy_smac_msk) |
                                        VTSS_F_RB_FWD_CFG_NODE_SRC_FWD_MASK(node_smac_msk));

    // Supervision frames from Interlink may be discarded
    sv = (lre || !conf->sv_discard ? FA_RB_SV_FORWARD : FA_RB_SV_DISCARD);
    REG_WR(VTSS_RB_PORT_CFG(tgt, j),
           VTSS_F_RB_PORT_CFG_TAG_MODE(tag_mode) | VTSS_F_RB_PORT_CFG_HSR_FILTER_CFG(hsr_filter) |
               VTSS_F_RB_PORT_CFG_HSR_SPV_FWD_SEL(sv) | VTSS_F_RB_PORT_CFG_PRP_SPV_FWD_SEL(sv) |
               VTSS_F_RB_PORT_CFG_TRANS_NETID(trans_netid) |
               VTSS_F_RB_PORT_CFG_TRANS_NETID_SEL(trans_netid > 0U ? 2 : 0) |
               VTSS_F_RB_PORT_CFG_NETID(netid) | VTSS_F_RB_PORT_CFG_LANID(lan_id) |
               VTSS_F_RB_PORT_CFG_RING_LANID(lan_id) | VTSS_F_RB_PORT_CFG_HSR_AWARE_ENA(hsr_aware) |
               VTSS_F_RB_PORT_CFG_PRP_AWARE_ENA(prp_aware));

    // Enable PTP on LRE ports
    REG_WR(VTSS_RB_PTP_CFG(tgt, j), VTSS_F_RB_PTP_CFG_PTP_ENA(lre));

    return VTSS_RC_OK;
}

// Find Interlink port
#define FA_RB_PORT_C(_c)                                                                           \
    ((_c)->port_a != VTSS_PORT_NO_NONE ? (_c)->port_a                                              \
                                       : ((_c)->port_b != VTSS_PORT_NO_NONE ? (_c)->port_b : 0U))

vtss_rc vtss_fa_rb_port_update(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_rb_id_t    id;
    vtss_rb_conf_t *conf;
    vtss_port_no_t  port_c;
    u32             val, port;

    // Timestamp configuration is used by default
    switch (vtss_state->ts.port_conf[port_no].mode.rb_discard) {
    case VTSS_TS_RB_DISCARD_A: val = 2U; break;
    case VTSS_TS_RB_DISCARD_B: val = 3U; break;
    default:                   val = 0U; break;
    }

    // RedBox configuration may override the value
    for (id = 0; id < VTSS_REDBOX_CNT; id++) {
        conf = &vtss_state->l2.rb_conf[id];
        if (conf->mode != VTSS_RB_MODE_DISABLED) {
            port_c = FA_RB_PORT_C(conf);
            if (port_no == port_c) {
                // Port is interlink, override value
                val = (conf->mode == VTSS_RB_MODE_HSR_PRP ? (conf->lan_id > 0U ? 3U : 2U) : 0U);
            }
        }
    }

    // Update rewriter register
    port = VTSS_CHIP_PORT(port_no);
    REG_WRM(VTSS_REW_PTP_MISC_CFG(port), VTSS_F_REW_PTP_MISC_CFG_PTP_RB_PRP_LAN(val),
            VTSS_M_REW_PTP_MISC_CFG_PTP_RB_PRP_LAN);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_rb_conf_set(struct vtss_state_s *vtss_state, const vtss_rb_id_t rb_id)
{
    vtss_rb_conf_t *conf = &vtss_state->l2.rb_conf[rb_id];
    vtss_rb_conf_t *old = &vtss_state->l2.rb_conf_old;
    vtss_port_no_t  port_no;
    u32             tgt = fa_rb_tgt(rb_id);
    u32             mode, ct_ena = 0U;
    u32             port_a = 0U, port_b = 0U, next_a = 0U, next_b = 0U, net_id, j;
    u32             age, clk_period, val, msk, unit, mask = 0x4U, port, sv;
    u64             x64, y64;
    BOOL            ena = TRUE, hsr = FALSE;

    switch (conf->mode) {
    case VTSS_RB_MODE_PRP_SAN: mode = FA_RB_MODE_PRP_SAN; break;
    case VTSS_RB_MODE_HSR_SAN:
        mode = FA_RB_MODE_HSR_SAN;
        hsr = TRUE;
        ct_ena = 0x05U;
        break;
    case VTSS_RB_MODE_HSR_PRP:
        mode = FA_RB_MODE_HSR_PRP;
        hsr = TRUE;
        ct_ena = 0x05U;
        break;
    case VTSS_RB_MODE_HSR_HSR:
        mode = FA_RB_MODE_HSR_HSR;
        hsr = TRUE;
        ct_ena = 0x05U;
        break;
    default:
        ena = FALSE;
        mode = 0U;
        break;
    }

    if (ena) {
        if (conf->port_a == VTSS_PORT_NO_NONE || vtss_state->l2.port_state[conf->port_a]) {
            mask |= 0x1U;
        }
        if (conf->port_b == VTSS_PORT_NO_NONE || vtss_state->l2.port_state[conf->port_b]) {
            mask |= 0x2U;
        }
    }
    val = (VTSS_F_RB_RB_CFG_KEEP_PRP_ALL_ENA(1) | VTSS_F_RB_RB_CFG_ABORT_DISC_ENA(1) |
           VTSS_F_RB_RB_CFG_DEFAULT_FWD_MASK(mask) | VTSS_F_RB_RB_CFG_RCT_MISSING_DISC_ENA(1) |
           VTSS_F_RB_RB_CFG_RCT_VALIDATE_ENA(0) | VTSS_F_RB_RB_CFG_DAN_DETECT_ENA(1) |
           VTSS_F_RB_RB_CFG_IRI_ENA(1) | VTSS_F_RB_RB_CFG_KEEP_INT_ENA(hsr) |
           VTSS_F_RB_RB_CFG_HSR_TAG_SEL(1) | VTSS_F_RB_RB_CFG_RB_MODE(mode) |
           VTSS_F_RB_RB_CFG_RB_ENA(ena));
    msk = (VTSS_M_RB_RB_CFG_KEEP_PRP_ALL_ENA | VTSS_M_RB_RB_CFG_ABORT_DISC_ENA |
           VTSS_M_RB_RB_CFG_DEFAULT_FWD_MASK | VTSS_M_RB_RB_CFG_RCT_MISSING_DISC_ENA |
           VTSS_M_RB_RB_CFG_RCT_VALIDATE_ENA | VTSS_M_RB_RB_CFG_DAN_DETECT_ENA |
           VTSS_M_RB_RB_CFG_IRI_ENA | VTSS_M_RB_RB_CFG_KEEP_INT_ENA | VTSS_M_RB_RB_CFG_HSR_TAG_SEL |
           VTSS_M_RB_RB_CFG_RB_MODE | VTSS_M_RB_RB_CFG_RB_ENA);
    REG_WRM(VTSS_RB_RB_CFG(tgt), val, msk);
    if (ena) {
        if (conf->port_a == VTSS_PORT_NO_NONE) {
            next_a = 1U;
        } else {
            VTSS_RC(vtss_fa_port2taxi(vtss_state, rb_id, conf->port_a, &port_a));
        }
        if (conf->port_b == VTSS_PORT_NO_NONE) {
            next_b = 1U;
        } else {
            VTSS_RC(vtss_fa_port2taxi(vtss_state, rb_id, conf->port_b, &port_b));
        }
    }
    REG_WR(VTSS_RB_TAXI_IF_CFG(tgt), VTSS_F_RB_TAXI_IF_CFG_LREA_NEXT(next_a) |
                                         VTSS_F_RB_TAXI_IF_CFG_LREB_NEXT(next_b) |
                                         VTSS_F_RB_TAXI_IF_CFG_LREA_PORT_NO(port_a) |
                                         VTSS_F_RB_TAXI_IF_CFG_LREB_PORT_NO(port_b));
    if (old->mode != VTSS_RB_MODE_DISABLED) {
        // Disable IFH/preamble transfers for old interlink port
        port_no = FA_RB_PORT_C(old);
        port = VTSS_CHIP_PORT(port_no);
        REG_WRM_CLR(VTSS_ASM_PORT_CFG(port), VTSS_M_ASM_PORT_CFG_RB_ENA);
        REG_WRM_CLR(VTSS_REW_RTAG_ETAG_CTRL(port), VTSS_M_REW_RTAG_ETAG_CTRL_RB_ENA);
        REG_WRM_CLR(VTSS_REW_PTP_MISC_CFG(port), VTSS_M_REW_PTP_MISC_CFG_PTP_RB_TAG_DIS);
        VTSS_RC(vtss_fa_rb_port_update(vtss_state, port_no));
        if (!ena) {
            // Clear counters and host table
            VTSS_RC(vtss_cil_l2_rb_counters_update(vtss_state, rb_id, TRUE));
            VTSS_RC(fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_CLEAR, 0));
        }
    }
    if (ena) {
        // Enable IFH/preamble transfers for new interlink port
        port_no = FA_RB_PORT_C(conf);
        port = VTSS_CHIP_PORT(port_no);
        REG_WRM_SET(VTSS_ASM_PORT_CFG(port), VTSS_M_ASM_PORT_CFG_RB_ENA);
        REG_WRM_SET(VTSS_REW_RTAG_ETAG_CTRL(port), VTSS_M_REW_RTAG_ETAG_CTRL_RB_ENA);
        if (mode == FA_RB_MODE_PRP_SAN) {
            REG_WRM_SET(VTSS_REW_PTP_MISC_CFG(port), VTSS_M_REW_PTP_MISC_CFG_PTP_RB_TAG_DIS);
        }
        REG_WRM_SET(VTSS_QFWD_SWITCH_PORT_MODE(port), VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA);
        VTSS_RC(vtss_fa_rb_port_update(vtss_state, port_no));
    }

    // NetId filtering on Interlink
    net_id = (hsr ? conf->net_id : 0U);
    msk = 1U;
    msk <<= net_id;
    msk = (0xffU - msk);
    REG_WR(VTSS_RB_NETID_CFG(tgt),
           VTSS_F_RB_NETID_CFG_NETID_HOST_TBL_DIS(1) |
               VTSS_F_RB_NETID_CFG_NETID_FILTER_ENA(net_id == 0U ? 0U : 1U) |
               VTSS_F_RB_NETID_CFG_NETID_MASK(msk));

    // Supervision frames
    sv = fa_rb_sv(conf->sv);
    REG_WR(VTSS_RB_SPV_CFG(tgt),
           VTSS_F_RB_SPV_CFG_DMAC_ENA(0) | VTSS_F_RB_SPV_CFG_HSR_SPV_INT_FWD_SEL(sv) |
               VTSS_F_RB_SPV_CFG_HSR_MAC_LSB(0) | VTSS_F_RB_SPV_CFG_PRP_SPV_INT_FWD_SEL(sv) |
               VTSS_F_RB_SPV_CFG_PRP_MAC_LSB(0));

    // Cut-through setup in QSYS
    REG_WRM(VTSS_RB_QSYS_CFG(tgt), VTSS_F_RB_QSYS_CFG_QUE_CT_ENA(ct_ena),
            VTSS_M_RB_QSYS_CFG_QUE_CT_ENA);

    // Ageing
    clk_period = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);
    unit = 1U; // 256 clock cycles
    for (j = 0U; j < 2U; j++) {
        age = (j == FA_RB_AGE_IDX_NT ? conf->nt_age_time : conf->pnt_age_time);
        // Calculate PERIOD_VAL, avoiding u32 overflow
        x64 = 1000000;
        x64 *= x64;
        y64 = FA_RB_AGE_CNT;
        y64 *= fa_rb_age_unit(unit);
        y64 *= FA_HT_ROW_CNT;
        y64 *= clk_period;
        x64 = VTSS_DIV64(x64, y64);
        val = (u32)(x64 * age);
        REG_WR(VTSS_RB_HOST_AUTOAGE_CFG(tgt, j), VTSS_F_RB_HOST_AUTOAGE_CFG_UNIT_SIZE(unit) |
                                                     VTSS_F_RB_HOST_AUTOAGE_CFG_PERIOD_VAL(val));
        REG_WR(VTSS_RB_HOST_AUTOAGE_CFG_1(tgt, j),
               VTSS_F_RB_HOST_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA(age > 0U));
    }

    // Duplicate discard ageing
    age = (conf->dd_age_time > 0U ? conf->dd_age_time : 4U); // Milliseconds
    unit = 0U;                                               // 16 clock cycles
    val = 1000000000U;
    val = VTSS_DIV64(val, fa_rb_age_unit(unit) * FA_DT_ROW_CNT * FA_RB_AGE_CNT * clk_period);
    val *= age;
    REG_WR(VTSS_RB_DISC_AUTOAGE_CFG(tgt),
           VTSS_F_RB_DISC_AUTOAGE_CFG_UNIT_SIZE(unit) | VTSS_F_RB_DISC_AUTOAGE_CFG_PERIOD_VAL(val));
    REG_WR(VTSS_RB_DISC_AUTOAGE_CFG_1(tgt), VTSS_F_RB_DISC_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA(1));

    // Port configuration
    for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
        VTSS_RC(fa_rb_port_conf_set(vtss_state, rb_id, j, conf));
    }

    // We might need to change DSM Taxi calendar when changing a RedBox
    // configuration.
    return fa_dsm_calc_and_apply_calendar(vtss_state, FALSE /* don't force a new calendar */);
}

vtss_rc vtss_cil_l2_rb_ptp_conf_set(struct vtss_state_s *vtss_state, const vtss_rb_id_t rb_id)
{
    u32                 tgt = fa_rb_tgt(rb_id);
    vtss_rb_ptp_conf_t *conf = &vtss_state->l2.rb_ptp_conf[rb_id];
    u32                 mode, vid_sel, flt_sel, dd_dis = FA_RB_MSK_C;
    u32                 i, j, val, dport;

    if (conf->vid == VTSS_VID_NULL) {
        // Match untagged
        vid_sel = 0U;
        flt_sel = 0x00U;
    } else {
        // Match tagged
        vid_sel = 1U;
        flt_sel = 0x02U;
    }
    switch (conf->mode) {
    case VTSS_RB_PTP_MODE_ETHERNET:
        // DMAC ignored
        mode = FA_RB_PTP_ETH;
        break;
    case VTSS_RB_PTP_MODE_IPV4:
        // DMAC and DIP ignored
        mode = FA_RB_PTP_IPV4;
        flt_sel |= 0x10U;
        break;
    case VTSS_RB_PTP_MODE_IPV6:
        // DMAC and DIP ignored
        mode = FA_RB_PTP_IPV6;
        flt_sel |= 0x10U;
        break;
    default:
        mode = FA_RB_PTP_NONE;
        vid_sel = 0U;
        flt_sel = 0x00U;
        dd_dis = FA_RB_MSK_NONE;
        break;
    }
    REG_WRM(VTSS_RB_RB_CFG(tgt), VTSS_F_RB_RB_CFG_PTP_AWARE_SEL(mode),
            VTSS_M_RB_RB_CFG_PTP_AWARE_SEL);
    REG_WR(VTSS_RB_PTP_MISC_CFG(tgt), VTSS_F_RB_PTP_MISC_CFG_PTP_RCT_DIS(1) |
                                          VTSS_F_RB_PTP_MISC_CFG_PTP_REDIR_INT_ENA(1) |
                                          VTSS_F_RB_PTP_MISC_CFG_PTP_DUPL_DISC_DIS(dd_dis));
    for (i = 0U; i < 16U; i++) {
        if ((i % 2U) == 0U) {
            REG_WR(VTSS_RB_PTP_FILTER_CFG(tgt, i / 2U),
                   VTSS_F_RB_PTP_FILTER_CFG_PTP_HSR_SEL(1) |
                       VTSS_F_RB_PTP_FILTER_CFG_PTP_VID_SEL(vid_sel) |
                       VTSS_F_RB_PTP_FILTER_CFG_PTP_FILTER_SEL(flt_sel));
        }
        dport = (i < 8U ? 319U : 320U);
        val = 0U;
        if (mode == FA_RB_PTP_ETH) {
            j = (i % 2U);
        } else if (mode == FA_RB_PTP_IPV4) {
            j = (i % 4U);
            if (j == 3U) {
                val = dport;
            }
        } else if (mode == FA_RB_PTP_IPV6) {
            j = (i % 8U);
            if (j == 6U) {
                val = dport;
            }
        } else {
            j = 0U;
        }
        if (j == 1U) {
            val = conf->vid;
            val <<= 16U;
        }
        REG_WR(VTSS_RB_PTP_DATA(tgt, i), val);
    }
    return VTSS_RC_OK;
}

#define RB_CNT(name, i, j, cnt, clear)                                                             \
    {                                                                                              \
        u32 val;                                                                                   \
        REG_RD(name(i, j), &val);                                                                  \
        vtss_cmn_counter_32_update(val, cnt, clear);                                               \
    }

vtss_rc vtss_cil_l2_rb_counters_update(struct vtss_state_s *vtss_state,
                                       const vtss_rb_id_t   rb_id,
                                       BOOL                 clear)
{
    u32                 tgt = fa_rb_tgt(rb_id);
    vtss_rb_cnt_t      *cnt = &vtss_state->l2.rb_cnt[rb_id];
    vtss_rb_port_cnt_t *c;
    u32                 j;

    for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
        c = (j == 0U ? &cnt->port_a : j == 1U ? &cnt->port_b : &cnt->port_c);
        RB_CNT(VTSS_RB_CNT_TX_TAG, tgt, j, &c->tx_tagged, clear);
        RB_CNT(VTSS_RB_CNT_TX_UNT, tgt, j, &c->tx_untagged, clear);
        RB_CNT(VTSS_RB_CNT_TX_LL, tgt, j, &c->tx_local, clear);
        RB_CNT(VTSS_RB_CNT_RX_TAG, tgt, j, &c->rx_tagged, clear);
        RB_CNT(VTSS_RB_CNT_RX_UNT, tgt, j, &c->rx_untagged, clear);
        RB_CNT(VTSS_RB_CNT_RX_LL, tgt, j, &c->rx_local, clear);
        RB_CNT(VTSS_RB_CNT_RX_WRONG_LAN, tgt, j, &c->rx_wrong_lan, clear);
        RB_CNT(VTSS_RB_CNT_RX_OWN, tgt, j, &c->rx_own, clear);
        RB_CNT(VTSS_RB_CNT_DUPL_ZERO, tgt, j, &c->tx_dupl_zero, clear);
        RB_CNT(VTSS_RB_CNT_DUPL_ONE, tgt, j, &c->tx_dupl_one, clear);
        RB_CNT(VTSS_RB_CNT_DUPL_TWO, tgt, j, &c->tx_dupl_multi, clear);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_rb_disc_cmd(vtss_state_t *vtss_state, const vtss_rb_id_t rb_id, u32 cmd, u32 idx)
{
    u32 val, tgt = fa_rb_tgt(rb_id);

    REG_WR(VTSS_RB_DISC_ACCESS_CTRL(tgt),
           VTSS_F_RB_DISC_ACCESS_CTRL_AUTOLRN_REPLACE_RULE_ENA(0xe) |
               VTSS_F_RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL(idx % FA_DT_COL_CNT) |
               VTSS_F_RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW(idx / FA_DT_COL_CNT) |
               VTSS_F_RB_DISC_ACCESS_CTRL_CPU_ACCESS_CMD(cmd) |
               VTSS_F_RB_DISC_ACCESS_CTRL_DISC_TABLE_ACCESS_SHOT(1));
    do {
        REG_RD(VTSS_RB_DISC_ACCESS_CTRL(tgt), &val);
    } while (VTSS_X_RB_DISC_ACCESS_CTRL_DISC_TABLE_ACCESS_SHOT(val) > 0U);
    return VTSS_RC_OK;
}

static BOOL fa_rb_host_skip(u32 cfg2, BOOL proxy)
{
    BOOL rc;

    // Skip invalid entries
    if (VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_VLD(cfg2) == 0U) {
        return TRUE;
    }

    // Skip entries not matching table type
    switch (VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_TYPE(cfg2)) {
    case FA_HT_PROXY: rc = (proxy ? FALSE : TRUE); break;
    case FA_HT_DAN:
    case FA_HT_SAN:   rc = (proxy ? TRUE : FALSE); break;
    default:          rc = TRUE; break;
    }
    return rc;
}

static vtss_rc fa_rb_host_table_clear(vtss_state_t         *vtss_state,
                                      const vtss_rb_id_t    rb_id,
                                      const vtss_rb_clear_t clear,
                                      BOOL                  proxy)
{
    u32 tgt = fa_rb_tgt(rb_id), idx, cfg2, skip_locked;

    skip_locked = (clear == VTSS_RB_CLEAR_ALL ? 2U : clear == VTSS_RB_CLEAR_LOCKED ? 0U : 1U);
    for (idx = 0U; idx < FA_HT_CNT; idx++) {
        VTSS_RC(fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_READ, idx));
        REG_RD(VTSS_RB_HOST_ACCESS_CFG_2(tgt), &cfg2);
        if (fa_rb_host_skip(cfg2, proxy) ||
            VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_LOCKED(cfg2) == skip_locked) {
            continue;
        }
        VTSS_RC(fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_UNLEARN, 0));
    }
    return VTSS_RC_OK;
}

static void fa_mac_get(const vtss_mac_t *const mac, u32 *mach, u32 *macl)
{
    vtss_vid_mac_t vid_mac;

    vid_mac.vid = 0;
    vid_mac.mac = *mac;
    vtss_mach_macl_get(&vid_mac, mach, macl);
}

static void fa_mac_set(vtss_mac_t *const mac, u32 mach, u32 macl)
{
    vtss_vid_mac_t vid_mac;

    vtss_mach_macl_set(&vid_mac, mach, macl);
    *mac = vid_mac.mac;
}

static vtss_rc fa_rb_host_mac_set(vtss_state_t           *vtss_state,
                                  const vtss_rb_id_t      rb_id,
                                  const vtss_mac_t *const mac)
{
    u32 tgt = fa_rb_tgt(rb_id), mach, macl;

    fa_mac_get(mac, &mach, &macl);
    REG_WR(VTSS_RB_HOST_ACCESS_CFG_0(tgt), VTSS_F_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_MAC_MSB(mach));
    REG_WR(VTSS_RB_HOST_ACCESS_CFG_1(tgt), VTSS_F_RB_HOST_ACCESS_CFG_1_HOST_ENTRY_MAC_LSB(macl));
    return VTSS_RC_OK;
}

static vtss_rc fa_rb_host_add(vtss_state_t           *vtss_state,
                              const vtss_rb_id_t      rb_id,
                              const vtss_mac_t *const mac,
                              BOOL                    locked,
                              u32                     ht,
                              u32                     mask,
                              u32                     pdan)
{
    u32 tgt = fa_rb_tgt(rb_id);

    VTSS_RC(fa_rb_host_mac_set(vtss_state, rb_id, mac));
    REG_WR(VTSS_RB_HOST_ACCESS_CFG_2(tgt),
           VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PROXY_DAN(pdan) |
               VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_LOCKED(locked ? 1 : 0) |
               VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_VLD(1) |
               VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_TYPE(ht) |
               VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PORTMASK(mask));
    return fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_LEARN, 0U);
}

static vtss_rc fa_rb_host_del(vtss_state_t           *vtss_state,
                              const vtss_rb_id_t      rb_id,
                              const vtss_mac_t *const mac,
                              BOOL                    proxy)
{
    u32 tgt = fa_rb_tgt(rb_id), cfg2;

    VTSS_RC(fa_rb_host_mac_set(vtss_state, rb_id, mac));
    VTSS_RC(fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_LOOKUP, 0));
    REG_RD(VTSS_RB_HOST_ACCESS_CFG_2(tgt), &cfg2);
    return (fa_rb_host_skip(cfg2, proxy)
                ? VTSS_RC_OK
                : fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_UNLEARN, 0U));
}

typedef struct {
    u8   age;
    BOOL fwd;
    BOOL rct;
    u32  rx;
    u32  rx_wrong_lan;
} fa_rb_host_port_t;

typedef struct {
    vtss_mac_t        mac;
    u16               idx;
    BOOL              locked;
    u8                type;
    BOOL              pdan;
    u16               seq_no;
    fa_rb_host_port_t port[VTSS_RB_PORT_CNT];
} fa_rb_host_t;

static vtss_rc fa_rb_host_read(vtss_state_t      *vtss_state,
                               const vtss_rb_id_t rb_id,
                               BOOL               proxy,
                               fa_rb_host_t      *host)
{
    u32                tgt = fa_rb_tgt(rb_id), cfg0, cfg2, stat3, mask;
    fa_rb_host_port_t *p;

    // Extract fields for entry after read/lookup
    REG_RD(VTSS_RB_HOST_ACCESS_CFG_2(tgt), &cfg2);
    if (fa_rb_host_skip(cfg2, proxy)) {
        return VTSS_RC_ERROR;
    }

    REG_RD(VTSS_RB_HOST_ACCESS_CFG_0(tgt), &cfg0);
    host->seq_no = (u16)VTSS_X_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_SEQ_NO(cfg0);
    host->locked = (VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_LOCKED(cfg2) > 0U);
    host->type = (u8)VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_TYPE(cfg2);
    host->pdan = (VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PROXY_DAN(cfg2) > 0U);
    mask = VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PORTMASK(cfg2);
    REG_RD(VTSS_RB_HOST_ACCESS_STAT_3(tgt), &stat3);

    // Port 0
    p = &host->port[0];
    p->age = (u8)VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_0(cfg2);
    p->fwd = ((mask & 1U) > 0U);
    p->rct = (VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_VALID_0(cfg2) > 0U);
    REG_RD(VTSS_RB_HOST_ACCESS_STAT_0(tgt), &p->rx);
    p->rx_wrong_lan = VTSS_X_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_0(stat3);

    // Port 1
    p = &host->port[1];
    p->age = (u8)VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_1(cfg2);
    p->fwd = ((mask & 2U) > 0U);
    p->rct = (VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_VALID_1(cfg2) > 0U);
    REG_RD(VTSS_RB_HOST_ACCESS_STAT_1(tgt), &p->rx);
    p->rx_wrong_lan = VTSS_X_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_1(stat3);

    // Port 2
    p = &host->port[2];
    p->age = (u8)VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_2(cfg2);
    p->fwd = ((mask & 4U) > 0U);
    p->rct = (VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_MISSING(cfg2) > 0U);
    REG_RD(VTSS_RB_HOST_ACCESS_STAT_2(tgt), &p->rx);
    p->rx_wrong_lan = VTSS_X_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_2(stat3);

    return VTSS_RC_OK;
}

static vtss_rc fa_rb_host_get(vtss_state_t           *vtss_state,
                              const vtss_rb_id_t      rb_id,
                              const vtss_mac_t *const mac,
                              BOOL                    proxy,
                              fa_rb_host_t           *host)
{
    host->mac = *mac;
    host->idx = 0U;
    VTSS_RC(fa_rb_host_mac_set(vtss_state, rb_id, mac));
    VTSS_RC(fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_LOOKUP, 0));
    return fa_rb_host_read(vtss_state, rb_id, proxy, host);
}

static vtss_rc fa_rb_host_mac_read(vtss_state_t      *vtss_state,
                                   const vtss_rb_id_t rb_id,
                                   u32                idx,
                                   BOOL               proxy,
                                   BOOL              *skip,
                                   u32               *mach,
                                   u32               *macl)
{
    u32 tgt = fa_rb_tgt(rb_id), cfg2;

    VTSS_RC(fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_READ, idx));
    REG_RD(VTSS_RB_HOST_ACCESS_CFG_2(tgt), &cfg2);
    *skip = fa_rb_host_skip(cfg2, proxy);
    if (*skip == FALSE) {
        REG_RD(VTSS_RB_HOST_ACCESS_CFG_0(tgt), mach);
        *mach = VTSS_X_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_MAC_MSB(*mach);
        REG_RD(VTSS_RB_HOST_ACCESS_CFG_1(tgt), macl);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_rb_host_get_next(vtss_state_t           *vtss_state,
                                   BOOL                    proxy,
                                   const vtss_rb_id_t      rb_id,
                                   const vtss_mac_t *const mac,
                                   fa_rb_host_t           *host)
{
    u64  old, new = 0, cur;
    u16  idx, idx_next;
    u32  mach, macl;
    BOOL skip = FALSE;

    // Store old MAC address as 64-bit integer
    fa_mac_get(mac, &mach, &macl);
    old = mach;
    old = ((old << 32U) + macl);

    idx_next = FA_HT_CNT;
    for (idx = 0U; idx < FA_HT_CNT; idx++) {
        VTSS_RC(fa_rb_host_mac_read(vtss_state, rb_id, idx, proxy, &skip, &mach, &macl));
        if ((idx % FA_HT_READ_MAX) == (FA_HT_READ_MAX - 1U)) {
            VTSS_EXIT_ENTER();
        }
        if (skip) {
            continue;
        }
        cur = mach;
        cur = ((cur << 32U) + macl);
        if (cur > old && (idx_next == FA_HT_CNT || cur < new)) {
            // Found entry greater than specified MAC address
            idx_next = idx;
            new = cur;
        }
    }
    idx = idx_next;
    if (idx < FA_HT_CNT) {
        fa_mac_set(&host->mac, (u32)(new >> 32U), (u32) new);
        host->idx = (idx + 1U); // Return 1-based ID
        VTSS_RC(fa_rb_host_cmd(vtss_state, rb_id, FA_HT_CMD_READ, idx));
        return fa_rb_host_read(vtss_state, rb_id, proxy, host);
    }
    return VTSS_RC_ERROR;
}

static vtss_rc fa_rb_host_id_get_next(vtss_state_t      *vtss_state,
                                      BOOL               proxy,
                                      const vtss_rb_id_t rb_id,
                                      uint16_t           id,
                                      fa_rb_host_t      *host)
{
    u16  idx;
    u32  mach, macl;
    BOOL skip = FALSE;

    for (idx = id; idx < FA_HT_CNT; idx++) {
        VTSS_RC(fa_rb_host_mac_read(vtss_state, rb_id, idx, proxy, &skip, &mach, &macl));
        if (((idx - id) % FA_HT_READ_MAX) == (FA_HT_READ_MAX - 1U)) {
            VTSS_EXIT_ENTER();
        }
        if (skip) {
            continue;
        }
        fa_mac_set(&host->mac, mach, macl);
        host->idx = (idx + 1U); // Return 1-based ID
        return fa_rb_host_read(vtss_state, rb_id, proxy, host);
    }
    return VTSS_RC_ERROR;
}

vtss_rc vtss_cil_l2_rb_node_add(struct vtss_state_s             *vtss_state,
                                const vtss_rb_id_t               rb_id,
                                const vtss_mac_t *const          mac,
                                const vtss_rb_node_conf_t *const conf)
{
    u32 ht, mask;

    if (conf->type == VTSS_RB_NODE_TYPE_DAN) {
        ht = FA_HT_DAN;
        mask = 0x3U;
    } else {
        ht = FA_HT_SAN;
        mask = (conf->san_a ? 0x1U : 0x2U);
    }
    return fa_rb_host_add(vtss_state, rb_id, mac, conf->locked, ht, mask, 0U);
}

vtss_rc vtss_cil_l2_rb_node_del(struct vtss_state_s    *vtss_state,
                                const vtss_rb_id_t      rb_id,
                                const vtss_mac_t *const mac)
{
    return fa_rb_host_del(vtss_state, rb_id, mac, FALSE);
}

vtss_rc vtss_cil_l2_rb_node_table_clear(struct vtss_state_s  *vtss_state,
                                        const vtss_rb_id_t    rb_id,
                                        const vtss_rb_clear_t clear)
{
    return fa_rb_host_table_clear(vtss_state, rb_id, clear, FALSE);
}

static vtss_rc fa_rb_host2node(vtss_state_t         *vtss_state,
                               const vtss_rb_id_t    rb_id,
                               vtss_rb_node_t *const entry,
                               fa_rb_host_t         *host)
{
    vtss_rb_age_time_t   age_time = vtss_state->l2.rb_conf[rb_id].nt_age_time;
    vtss_rb_node_port_t *p;
    fa_rb_host_port_t   *h;
    int                  i;

    entry->mac = host->mac;
    entry->id = host->idx;
    entry->locked = host->locked;
    entry->type = (host->type == FA_HT_DAN ? VTSS_RB_NODE_TYPE_DAN : VTSS_RB_NODE_TYPE_SAN);
    for (i = 0; i < 2; i++) {
        p = (i > 0 ? &entry->port_b : &entry->port_a);
        h = &host->port[i];
        p->fwd = h->fwd;
        p->age = (age_time * h->age / FA_RB_AGE_CNT);
        p->cnt.rx = h->rx;
        p->cnt.rx_wrong_lan = h->rx_wrong_lan;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_rb_node_get(struct vtss_state_s    *vtss_state,
                                const vtss_rb_id_t      rb_id,
                                const vtss_mac_t *const mac,
                                vtss_rb_node_t *const   entry)
{
    fa_rb_host_t host;

    VTSS_RC(fa_rb_host_get(vtss_state, rb_id, mac, FALSE, &host));
    return fa_rb_host2node(vtss_state, rb_id, entry, &host);
}

vtss_rc vtss_cil_l2_rb_node_get_next(struct vtss_state_s    *vtss_state,
                                     const vtss_rb_id_t      rb_id,
                                     const vtss_mac_t *const mac,
                                     vtss_rb_node_t *const   entry)
{
    fa_rb_host_t host;

    VTSS_RC(fa_rb_host_get_next(vtss_state, FALSE, rb_id, mac, &host));
    return fa_rb_host2node(vtss_state, rb_id, entry, &host);
}

vtss_rc vtss_cil_l2_rb_node_id_get_next(struct vtss_state_s    *vtss_state,
                                        const vtss_rb_id_t      rb_id,
                                        const vtss_rb_node_id_t id,
                                        vtss_rb_node_t *const   entry)
{
    fa_rb_host_t host;

    VTSS_RC(fa_rb_host_id_get_next(vtss_state, FALSE, rb_id, id, &host));
    return fa_rb_host2node(vtss_state, rb_id, entry, &host);
}

vtss_rc vtss_cil_l2_rb_proxy_node_add(struct vtss_state_s                   *vtss_state,
                                      const vtss_rb_id_t                     rb_id,
                                      const vtss_mac_t *const                mac,
                                      const vtss_rb_proxy_node_conf_t *const conf)
{
    u32 pdan = (conf->type == VTSS_RB_PROXY_NODE_TYPE_DAN ? 1U : 0U);

    return fa_rb_host_add(vtss_state, rb_id, mac, conf->locked, FA_HT_PROXY, 0x4U, pdan);
}

vtss_rc vtss_cil_l2_rb_proxy_node_del(struct vtss_state_s    *vtss_state,
                                      const vtss_rb_id_t      rb_id,
                                      const vtss_mac_t *const mac)
{
    return fa_rb_host_del(vtss_state, rb_id, mac, TRUE);
}

vtss_rc vtss_cil_l2_rb_proxy_node_table_clear(struct vtss_state_s  *vtss_state,
                                              const vtss_rb_id_t    rb_id,
                                              const vtss_rb_clear_t clear)
{
    return fa_rb_host_table_clear(vtss_state, rb_id, clear, TRUE);
}

static vtss_rc fa_rb_host2proxy(vtss_state_t               *vtss_state,
                                const vtss_rb_id_t          rb_id,
                                vtss_rb_proxy_node_t *const entry,
                                fa_rb_host_t               *host)
{
    vtss_rb_age_time_t age_time = vtss_state->l2.rb_conf[rb_id].pnt_age_time;

    entry->mac = host->mac;
    entry->id = host->idx;
    entry->locked = host->locked;
    entry->type = (host->pdan ? VTSS_RB_PROXY_NODE_TYPE_DAN : VTSS_RB_PROXY_NODE_TYPE_SAN);
    entry->age = (age_time * host->port[2].age / FA_RB_AGE_CNT);
    entry->cnt.rx = host->port[2].rx;
    entry->cnt.rx_wrong_lan = host->port[2].rx_wrong_lan;
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_l2_rb_proxy_node_get(struct vtss_state_s        *vtss_state,
                                      const vtss_rb_id_t          rb_id,
                                      const vtss_mac_t *const     mac,
                                      vtss_rb_proxy_node_t *const entry)
{
    fa_rb_host_t host;

    VTSS_RC(fa_rb_host_get(vtss_state, rb_id, mac, TRUE, &host));
    return fa_rb_host2proxy(vtss_state, rb_id, entry, &host);
}

vtss_rc vtss_cil_l2_rb_proxy_node_get_next(struct vtss_state_s        *vtss_state,
                                           const vtss_rb_id_t          rb_id,
                                           const vtss_mac_t *const     mac,
                                           vtss_rb_proxy_node_t *const entry)
{
    fa_rb_host_t host;

    VTSS_RC(fa_rb_host_get_next(vtss_state, TRUE, rb_id, mac, &host));
    return fa_rb_host2proxy(vtss_state, rb_id, entry, &host);
}

vtss_rc vtss_cil_l2_rb_proxy_node_id_get_next(struct vtss_state_s          *vtss_state,
                                              const vtss_rb_id_t            rb_id,
                                              const vtss_rb_proxy_node_id_t id,
                                              vtss_rb_proxy_node_t *const   entry)
{
    fa_rb_host_t host;

    VTSS_RC(fa_rb_host_id_get_next(vtss_state, TRUE, rb_id, id, &host));
    return fa_rb_host2proxy(vtss_state, rb_id, entry, &host);
}
#endif

/* - Debug print --------------------------------------------------- */

static void fa_debug_pmask_header(vtss_state_t *vtss_state, lmu_ss_t *ss, const char *name)
{
    lmu_fmt_buf_t buf;

    VTSS_FMT(buf, "%-33s", name == NULL ? "Port" : name);
    vtss_fa_debug_print_port_header(vtss_state, ss, buf.s);
}

static void fa_debug_pmask(vtss_state_t     *vtss_state,
                           lmu_ss_t         *ss,
                           const char       *name,
                           vtss_port_mask_t *pmask)
{
    pr("%-33s", name);
    vtss_fa_debug_print_pmask(vtss_state, ss, pmask);
}

static vtss_rc fa_debug_vlan_entry(vtss_state_t *vtss_state,
                                   lmu_ss_t     *ss,
                                   vtss_vid_t    vid,
                                   BOOL          header)
{
    u32              value, qcfg;
    vtss_port_mask_t pmask;
    lmu_fmt_buf_t    buf;

    REG_RDX_PMASK(VTSS_ANA_L3_VLAN_MASK_CFG, vid, &pmask);
    REG_RD(VTSS_ANA_L3_VLAN_CFG(vid), &value);
    REG_RD(VTSS_ANA_L3_QGRP_CFG(vid), &qcfg);

    if (header) {
        fa_debug_pmask_header(vtss_state, ss, "VID   FID   MSTI  L/F/M/F/P  QGRP");
    }

    VTSS_FMT(buf, "%-6u%-6u%-6u%u/%u/%u/%u/%u  %u", vid, VTSS_X_ANA_L3_VLAN_CFG_VLAN_FID(value),
             VTSS_X_ANA_L3_VLAN_CFG_VLAN_MSTP_PTR(value),
             VTSS_X_ANA_L3_VLAN_CFG_VLAN_LRN_DIS(value) == 0U,
             VTSS_X_ANA_L3_VLAN_CFG_VLAN_FLOOD_DIS(value) == 0U,
             VTSS_X_ANA_L3_VLAN_CFG_VLAN_MIRROR_ENA(value),
             VTSS_X_ANA_L3_VLAN_CFG_VLAN_IGR_FILTER_ENA(value),
             VTSS_X_ANA_L3_VLAN_CFG_VLAN_PRIVATE_ENA(value), VTSS_X_ANA_L3_QGRP_CFG_QGRP_IDX(qcfg));
    fa_debug_pmask(vtss_state, ss, buf.s, &pmask);

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_vlan(vtss_state_t                  *vtss_state,
                             lmu_ss_t                      *ss,
                             const vtss_debug_info_t *const info)
{
    vtss_port_no_t     port_no;
    vtss_vid_t         vid;
    vtss_vlan_entry_t *vlan_entry;
    u32                port;
    vtss_port_mask_t   pmask;
    BOOL               header = TRUE;
    lmu_fmt_buf_t      buf;

    for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        VTSS_FMT(buf, "Port %u (%u)", port, port_no);
        vtss_fa_debug_reg_header(ss, buf.s);
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_VLAN_FILTER_CTRL(port, 0)),
                               port, "ANA:VLAN_FILTER_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_VLAN_CTRL(port)), port,
                               "ANA:VLAN_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_VLAN_TPID_CTRL(port)), port,
                               "ANA:TPID_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_REW_PORT_VLAN_CFG(port)), port,
                               "REW:PORT_VLAN_CFG");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_REW_TAG_CTRL(port)), port,
                               "REW:TAG_CTRL");
        pr("\n");
    }

    vtss_fa_debug_reg_header(ss, "VLAN COMMON");
    FA_DEBUG_REG_NAME(ss, ANA_L3, VLAN_CTRL, "VLAN_CTRL");
    FA_DEBUG_REG_NAME(ss, ANA_CL, VLAN_STAG_CFG(0), "VLAN_STAG_CFG(0)");
    FA_DEBUG_REG_NAME(ss, ANA_CL, VLAN_STAG_CFG(1), "VLAN_STAG_CFG(1)");
    FA_DEBUG_REG_NAME(ss, ANA_CL, VLAN_STAG_CFG(2), "VLAN_STAG_CFG(2)");
    pr("\n");

    fa_debug_pmask_header(vtss_state, ss, NULL);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_FILTER_CTRL, &pmask);
    fa_debug_pmask(vtss_state, ss, "FILTER_CTRL", &pmask);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_ISOLATED_CFG, &pmask);
    fa_debug_pmask(vtss_state, ss, "ISOLATED_CFG", &pmask);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_COMMUNITY_CFG, &pmask);
    fa_debug_pmask(vtss_state, ss, "COMMUNITY_CFG", &pmask);
    pr("\n");

    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if (info->full || (vlan_entry->flags & VLAN_FLAGS_ENABLED) > 0U) {
            VTSS_RC(fa_debug_vlan_entry(vtss_state, ss, vid, header));
            header = FALSE;
            /* Leave critical region briefly */
            VTSS_EXIT_ENTER();
        }
    }
    if (!header) {
        pr("\n");
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_src_table(vtss_state_t                  *vtss_state,
                                  lmu_ss_t                      *ss,
                                  const vtss_debug_info_t *const info)
{
    u32              port;
    vtss_port_mask_t pmask;
    lmu_fmt_buf_t    buf;

    vtss_debug_print_header(ss, "Source Masks");
    fa_debug_pmask_header(vtss_state, ss, NULL);
    for (port = 0U; port <= RT_CHIP_PORTS; port++) {
        REG_RDX_PMASK(VTSS_ANA_AC_SRC_SRC_CFG, port, &pmask);
        VTSS_FMT(buf, "%u", port);
        fa_debug_pmask(vtss_state, ss, buf.s, &pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_aggr_table(vtss_state_t                  *vtss_state,
                                   lmu_ss_t                      *ss,
                                   const vtss_debug_info_t *const info)
{
    u32              ac;
    vtss_port_mask_t pmask;
    lmu_fmt_buf_t    buf;

    vtss_debug_print_header(ss, "Aggregation Masks");
    fa_debug_pmask_header(vtss_state, ss, "AC");
    for (ac = 0U; ac < 16U; ac++) {
        REG_RDX_PMASK(VTSS_ANA_AC_AGGR_AGGR_CFG, ac, &pmask);
        VTSS_FMT(buf, "%u", ac);
        fa_debug_pmask(vtss_state, ss, buf.s, &pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_pgid_table(vtss_state_t                  *vtss_state,
                                   lmu_ss_t                      *ss,
                                   const vtss_debug_info_t *const info,
                                   u32                            pgid_start,
                                   u32                            pgid_end)
{
    u32              pgid, value;
    u8               x;
    vtss_port_mask_t pmask;
    lmu_fmt_buf_t    buf;

    vtss_debug_print_header(ss, "Destination Masks");
    fa_debug_pmask_header(vtss_state, ss, "PGID            CPU  Queue");
    for (pgid = pgid_start; pgid < pgid_end; pgid++) {
        REG_RDX_PMASK(VTSS_ANA_AC_PGID_PGID_CFG, pgid, &pmask);
        REG_RD(VTSS_ANA_AC_PGID_PGID_MISC_CFG(pgid), &value);
        if (pgid > 80U && pmask.m[0] == 0U && pmask.m[1] == 0U && pmask.m[2] == 0U && !info->full) {
            continue;
        }
        x = (pgid < 0xffU ? (u8)pgid : 0xffU);
        VTSS_FMT(buf, "%-5u%-11s%-5u%-5u", pgid,
                 x == PGID_UC_FLOOD       ? "UC"
                 : x == PGID_MC_FLOOD     ? "MC"
                 : x == PGID_IPV4_MC_DATA ? "IPv4 Data"
                 : x == PGID_IPV4_MC_CTRL ? "IPv4 Ctrl"
                 : x == PGID_IPV6_MC_DATA ? "IPv6 Data"
                 : x == PGID_IPV6_MC_CTRL ? "IPv6 Ctrl"
                 : x == PGID_DROP         ? "DROP"
                 : x == PGID_FLOOD        ? "FLOOD"
                                          : "",
                 VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(value),
                 VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU(value));
        fa_debug_pmask(vtss_state, ss, buf.s, &pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_pvlan(vtss_state_t                  *vtss_state,
                              lmu_ss_t                      *ss,
                              const vtss_debug_info_t *const info)
{
    vtss_port_mask_t pmask;

    fa_debug_pmask_header(vtss_state, ss, NULL);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_ISOLATED_CFG, &pmask);
    fa_debug_pmask(vtss_state, ss, "ISOLATED_CFG", &pmask);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_COMMUNITY_CFG, &pmask);
    fa_debug_pmask(vtss_state, ss, "COMMUNITY_CFG", &pmask);
    pr("\n");

    return fa_debug_src_table(vtss_state, ss, info);
}

static vtss_rc fa_debug_mac_table(vtss_state_t                  *vtss_state,
                                  lmu_ss_t                      *ss,
                                  const vtss_debug_info_t *const info)
{
    vtss_mac_entry_t      *entry;
    vtss_mac_table_entry_t mac_entry;
    BOOL                   header = TRUE;
    u32                    pgid;

    vtss_fa_debug_reg_header(ss, "LRN");
    FA_DEBUG_REGX_NAME(ss, LRN, AUTOAGE_CFG, 0, "AUTOAGE_CFG");
    FA_DEBUG_REG_NAME(ss, LRN, AUTOAGE_CFG_1, "AUTOAGE_CFG1");
    pr("\n");

    /* Dump MAC address table */
    VTSS_MEMSET(&mac_entry, 0, sizeof(mac_entry));

    while (vtss_cil_l2_mac_table_get_next(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK) {
        vtss_debug_print_mac_entry(ss, "Dynamic Entries (GET_NEXT)", &header, &mac_entry, pgid);
        VTSS_EXIT_ENTER();
    }
    if (!header) {
        pr("\n");
    }

    /* Dump static entries not returned by the get_next function */
    header = TRUE;
    for (entry = vtss_state->l2.mac_list_used; entry != NULL; entry = entry->next) {
        vtss_mach_macl_set(&mac_entry.vid_mac, entry->mach, entry->macl);
        if (vtss_cil_l2_mac_table_get(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK) {
            vtss_debug_print_mac_entry(ss, "Static Entries (GET)", &header, &mac_entry, pgid);
        }
        VTSS_EXIT_ENTER();
    }
    if (!header) {
        pr("\n");
    }

    /* Flood masks */
    VTSS_RC(fa_debug_pgid_table(vtss_state, ss, info, PGID_UC_FLOOD, PGID_IPV6_MC_CTRL + 1U));

#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    vtss_fa_debug_reg_header(ss, "PMAC");
    FA_DEBUG_REG_NAME(ss, ANA_L2, PMAC_CFG, "PMAC_CFG");
    FA_DEBUG_REG_NAME(ss, ANA_L2, PMAC_CFG_2, "PMAC_CFG_2");
    for (u32 i = 0; i < VTSS_MAC_INDEX_VID_CNT; i++) {
        FA_DEBUG_REGX_NAME(ss, ANA_L2, PMAC_VLAN_CFG, i, "PMAC_VLAN_CFG");
    }
    pr("\n");
#endif

    /* Read and clear sticky bits */
    if (info->full) {
        vtss_fa_debug_reg_header(ss, "STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_FILTER_STICKY),
                             "ANA_CL:FILTER_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_VLAN_FILTER_STICKY(0)),
                             "ANA_CL:VLAN_FILTER_STICKY(0)");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_VLAN_FILTER_STICKY(1)),
                             "ANA_CL:VLAN_FILTER_STICKY(1)");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_VLAN_FILTER_STICKY(2)),
                             "ANA_CL:VLAN_FILTER_STICKY(2)");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_CLASS_STICKY),
                             "ANA_CL:CLASS_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_CAT_STICKY), "ANA_CL:CAT_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_ADV_CL_MPLS_STICKY),
                             "ANA_CL:ADV_CL_MPLS_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_ADV_CL_STICKY),
                             "ANA_CL:ADV_CL_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_MIP_STICKY), "ANA_CL:MIP_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_IP_HDR_CHK_STICKY),
                             "ANA_CL:IP_HDR_CHK_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_L2_STICKY), "ANA_L2:L2_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_PS_STICKY_STICKY),
                             "ANA_AC:PS_STICKY");
        vtss_fa_debug_sticky(vtss_state, ss, REG_ADDR(VTSS_LRN_EVENT_STICKY), "LRN:EVENT_STICKY");
        pr("\n");
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_FRER)
static vtss_rc fa_debug_frer(vtss_state_t                  *vtss_state,
                             lmu_ss_t                      *ss,
                             const vtss_debug_info_t *const info)
{
    vtss_xms_entry_t *ms;
    vtss_port_no_t    port_no;
    u16               i, idx;
    lmu_fmt_buf_t     buf;

    for (i = 0; i < VTSS_MSTREAM_CNT; i++) {
        ms = &vtss_state->l2.ms.table[i];
        if (ms->cnt == 0U) {
            continue;
        }
        idx = ms->idx;
        for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
            if (VTSS_PORT_BF_GET(ms->port_list, port_no)) {
                VTSS_FMT(buf, "MSID %u, port %u", i, port_no);
                vtss_fa_debug_reg_header(ss, buf.s);
                vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_EACL_FRER_CFG_MEMBER(idx)),
                                       idx, "EACL:FRER_CFG_MEMBER");
                REG_WRM(VTSS_EACL_FRER_CFG, VTSS_F_EACL_FRER_CFG_ADDR(idx),
                        VTSS_M_EACL_FRER_CFG_ADDR);
                vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_EACL_FRER_STA_MEMBER), idx,
                                       "EACL:FRER_STA_MEMBER");
                vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_EACL_FRER_HST_MEMBER), idx,
                                       "EACL:FRER_HST_MEMBER");
                idx++;
                pr("\n");
            }
        }
    }
    for (i = 0; i < VTSS_CSTREAM_CNT; i++) {
        if (!vtss_state->l2.cstream_conf[i].recovery) {
            continue;
        }
        VTSS_FMT(buf, "CSID %u", i);
        vtss_fa_debug_reg_header(ss, buf.s);
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_EACL_FRER_CFG_COMPOUND(i)), i,
                               "EACL:FRER_CFG_COMPOUND");
        REG_WRM(VTSS_EACL_FRER_CFG, VTSS_F_EACL_FRER_CFG_ADDR(i), VTSS_M_EACL_FRER_CFG_ADDR);
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_EACL_FRER_STA_COMPOUND), i,
                               "EACL:FRER_STA_COMPOUND");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_EACL_FRER_HST_COMPOUND), i,
                               "EACL:FRER_HST_COMPOUND");
        pr("\n");
    }
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_PSFP)
static vtss_rc fa_debug_psfp(vtss_state_t                  *vtss_state,
                             lmu_ss_t                      *ss,
                             const vtss_debug_info_t *const info)
{
    u16           i, j;
    u32           id;
    lmu_fmt_buf_t buf;
    BOOL          first = TRUE;

    for (i = 0; i < VTSS_PSFP_FILTER_CNT; i++) {
        vtss_psfp_filter_conf_t *conf = &vtss_state->l2.psfp.filter[i];
        if (info->full || conf->gate_enable || conf->max_sdu > 0U || conf->block_oversize.enable) {
            if (first) {
                first = FALSE;
                vtss_fa_debug_reg_header(ss, "PSFP Filters");
            }
            id = fa_psfp_sfid(i);
            vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_TSN_SF_CFG_TSN_SF_CFG(id)),
                                   id, "TSN_SF_CFG");
        }
    }
    if (!first) {
        pr("\n");
    }

    for (i = 0; i < VTSS_PSFP_GATE_CNT; i++) {
        if (info->full || vtss_state->l2.psfp.gate[i].enable) {
            id = fa_psfp_sgid(i);
            VTSS_FMT(buf, "PSFP Gate %u (%u)", i, id);
            vtss_fa_debug_reg_header(ss, buf.s);
            REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL,
                   VTSS_F_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL_SGID(id));
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_1),
                              "CONFIG_REG_1");
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_2),
                              "CONFIG_REG_2");
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3),
                              "CONFIG_REG_3");
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_4),
                              "CONFIG_REG_4");
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_5),
                              "CONFIG_REG_5");
            for (j = 0U; j < 4U; j++) {
                vtss_fa_debug_reg_inst(vtss_state, ss,
                                       REG_ADDR(VTSS_ANA_AC_SG_CONFIG_SG_GCL_GS_CONFIG(j)), j,
                                       "GS_CONFIG");
                vtss_fa_debug_reg_inst(vtss_state, ss,
                                       REG_ADDR(VTSS_ANA_AC_SG_CONFIG_SG_GCL_TI_CONFIG(j)), j,
                                       "TI_CONFIG");
                vtss_fa_debug_reg_inst(vtss_state, ss,
                                       REG_ADDR(VTSS_ANA_AC_SG_CONFIG_SG_GCL_OCT_CONFIG(j)), j,
                                       "OCT_CONFIG");
            }
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_1),
                              "STATUS_REG_1");
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_2),
                              "STATUS_REG_2");
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_3),
                              "STATUS_REG_3");
            pr("\n");
        }
    }
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_VCAP)
static vtss_rc fa_debug_vxlat(vtss_state_t                  *vtss_state,
                              lmu_ss_t                      *ss,
                              const vtss_debug_info_t *const info)
{
    u32 a = info->action;

    if (a == 0U || a == 3U) {
        VTSS_RC(vtss_fa_debug_clm_b(vtss_state, ss, info));
    }
    if (a == 0U || a == 4U) {
        VTSS_RC(vtss_fa_debug_es0(vtss_state, ss, info));
    }
#if defined(VTSS_FEATURE_FRER)
    if (a == 0U || a == 10U) {
        if (vtss_state->vtss_features[FEATURE_FRER]) {
            VTSS_RC(fa_debug_frer(vtss_state, ss, info));
        }
    }
#endif
#if defined(VTSS_FEATURE_PSFP)
    if (a == 0U || a == 11U) {
        if (vtss_state->vtss_features[FEATURE_PSFP]) {
            VTSS_RC(fa_debug_psfp(vtss_state, ss, info));
        }
    }
#endif
    return VTSS_RC_OK;
}
#endif

static u32 fa_pgid_cnt(void)
{
#if (RT_PGID_FA < VTSS_PGIDS)
    return RT_PGID_FA;
#else
    return VTSS_PGIDS;
#endif
}

static vtss_rc fa_debug_aggr(vtss_state_t                  *vtss_state,
                             lmu_ss_t                      *ss,
                             const vtss_debug_info_t *const info)
{
    u32 port, cnt = fa_pgid_cnt();

    vtss_fa_debug_reg_header(ss, "Logical Ports");
    for (port = 0U; port < RT_CHIP_PORTS; port++) {
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_ANA_CL_PORT_ID_CFG(port)), port,
                               "PORT_ID_CFG");
    }
    pr("\n");

    VTSS_RC(fa_debug_src_table(vtss_state, ss, info));
    VTSS_RC(fa_debug_aggr_table(vtss_state, ss, info));
    VTSS_RC(fa_debug_pgid_table(vtss_state, ss, info, 0, cnt));

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_stp(vtss_state_t                  *vtss_state,
                            lmu_ss_t                      *ss,
                            const vtss_debug_info_t *const info)
{
    u32              msti, cnt = 1U;
    vtss_port_mask_t pmask;
    lmu_fmt_buf_t    buf;

    fa_debug_pmask_header(vtss_state, ss, NULL);
    REG_RD_PMASK(VTSS_ANA_L2_LRN_SECUR_CFG, &pmask);
    fa_debug_pmask(vtss_state, ss, "LRN_SECUR_CFG", &pmask);
    REG_RD_PMASK(VTSS_ANA_L2_AUTO_LRN_CFG, &pmask);
    fa_debug_pmask(vtss_state, ss, "AUTO_LRN_CFG", &pmask);
    REG_RD_PMASK(VTSS_ANA_L2_LRN_COPY_CFG, &pmask);
    fa_debug_pmask(vtss_state, ss, "LRN_COPY_CFG", &pmask);
    pr("\n");

#if defined(VTSS_FEATURE_L2_MSTP)
    cnt = VTSS_MSTIS;
#endif
    fa_debug_pmask_header(vtss_state, ss, NULL);
    for (msti = 0U; msti < cnt; msti++) {
        REG_RDX_PMASK(VTSS_ANA_L3_MSTP_LRN_CFG, msti, &pmask);
        VTSS_FMT(buf, "MSTP_LRN_CFG_%u", msti);
        fa_debug_pmask(vtss_state, ss, buf.s, &pmask);
        REG_RDX_PMASK(VTSS_ANA_L3_MSTP_FWD_CFG, msti, &pmask);
        VTSS_FMT(buf, "MSTP_FWD_CFG_%u", msti);
        fa_debug_pmask(vtss_state, ss, buf.s, &pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_mirror(vtss_state_t                  *vtss_state,
                               lmu_ss_t                      *ss,
                               const vtss_debug_info_t *const info)
{
    u32              i, j;
    vtss_port_mask_t pmask;
    lmu_fmt_buf_t    buf;

    for (i = 0U; i < 3U; i++) {
        VTSS_FMT(buf, "%s Probe",
                 i == FA_MIRROR_PROBE_RX   ? "Rx"
                 : i == FA_MIRROR_PROBE_TX ? "Tx"
                                           : "VLAN");
        vtss_fa_debug_reg_header(ss, buf.s);
        j = QFWD_FRAME_COPY_CFG_MIRROR_PROBE(i);
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_QFWD_FRAME_COPY_CFG(j)), j,
                               "QFWD:FRAME_COPY_CFG");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_REW_MIRROR_PROBE_CFG(i)), i,
                               "REW:PROBE_CFG");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_REW_MIRROR_TAG_A_CFG(i)), i,
                               "REW:TAG_A_CFG");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_REW_MIRROR_TAG_B_CFG(i)), i,
                               "REW:TAG_B_CFG");
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG(i)), i,
                               "ANA_AC:PROBE_CFG");
        pr("\n");

        fa_debug_pmask_header(vtss_state, ss, NULL);
        REG_RDX_PMASK(VTSS_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG, i, &pmask);
        VTSS_FMT(buf, "PROBE_PORT_CFG_%u", i);
        fa_debug_pmask(vtss_state, ss, buf.s, &pmask);
        pr("\n");
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_REDBOX)
static void fa_print_host_entry(lmu_ss_t *ss, const char *name, u32 *cnt, fa_rb_host_t *host)
{
    u8                 j;
    fa_rb_host_port_t *p;
    u16                idx = (host->idx - 1U); // Show 0-based IDX
    lmu_fmt_buf_t      buf;

    if (*cnt == 0U) {
        pr("%s\n\n", name);
        pr("MAC Address        IDX/Row/Col  Type       Lock  SeqNo  Port  Fwd  Age  RCT  RxWrongLan  Rx\n");
    }
    *cnt = (*cnt + 1U);
    VTSS_FMT(buf, "%u/%u/%u", idx, idx / FA_HT_COL_CNT, idx % FA_HT_COL_CNT);
    pr("%s  %-13s", vtss_mac_txt(&host->mac), &buf);
    VTSS_FMT(buf, "%s%s",
             host->type == FA_HT_PROXY ? "PROXY"
             : host->type == FA_HT_DAN ? "DAN"
             : host->type == FA_HT_SAN ? "SAN"
                                       : "LOCAL",
             host->type != FA_HT_PROXY ? ""
             : host->pdan              ? "-DAN"
                                       : "-SAN");
    pr("%-11s%-6u%-7u", &buf, host->locked, host->seq_no);
    for (j = 0; j < VTSS_RB_PORT_CNT; j++) {
        p = &host->port[j];
        if (j > 0U) {
            pr("-%-55s", "");
        }
        pr("%-6u%-5u%-5u%-5u%-12u%u\n", j, p->fwd, p->age, p->rct, p->rx_wrong_lan, p->rx);
    }
}

static vtss_rc fa_print_disc_entry(vtss_state_t *vtss_state, lmu_ss_t *ss, u8 i, u32 j, u32 *cnt)
{
    u32           tgt = fa_rb_tgt(i), cfg0, cfg1, cfg2, mask;
    vtss_mac_t    mac;
    lmu_fmt_buf_t buf;

    VTSS_RC(fa_rb_disc_cmd(vtss_state, i, FA_DT_CMD_READ, j));
    REG_RD(VTSS_RB_DISC_ACCESS_CFG_2(tgt), &cfg2);
    if (VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_VLD(cfg2) == 0U) {
        return VTSS_RC_OK;
    }
    REG_RD(VTSS_RB_DISC_ACCESS_CFG_0(tgt), &cfg0);
    REG_RD(VTSS_RB_DISC_ACCESS_CFG_1(tgt), &cfg1);
    if (*cnt == 0U) {
        pr("RedBox %u Duplicate Discard Table\n\n", i);
        pr("IDX/Row/Col  MAC Address        SeqNo  Age  A/B/C Mask  A/B/C Discards\n");
    }
    *cnt = (*cnt + 1U);
    fa_mac_set(&mac, cfg0, cfg1);
    VTSS_FMT(buf, "%u/%u/%u", j, j / FA_DT_COL_CNT, j % FA_DT_COL_CNT);
    mask = VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_PORTMASK(cfg2);
    pr("%-13s%s  %-7u%-5u%u/%u/%u%8u/%u/%u\n", &buf, vtss_mac_txt(&mac),
       VTSS_X_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SEQ_NO(cfg0),
       VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_AGE_FLAG(cfg2), (mask & 1U) > 0U, (mask & 2U) > 0U,
       (mask & 4U) > 0U, VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_CNT_0(cfg2),
       VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_CNT_1(cfg2), VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_CNT_2(cfg2));
    VTSS_EXIT_ENTER();
    return VTSS_RC_OK;
}

static void fa_debug_rb_fld(lmu_ss_t   *ss,
                            const u32  *val,
                            u32         mask,
                            const char *name,
                            const char *prefix,
                            BOOL        newline,
                            u32         cnt)
{
    u32           i, j, v, m;
    lmu_fmt_buf_t buf;
    char         *p;

    VTSS_FMT(buf, "%s%s", prefix != NULL ? prefix : "", name);
    for (p = buf.s; *p != '\0'; p++) {
        if (p[0] == '_' && p[1] == 'C' && p[2] == 'F' && p[3] == 'G' && p[4] == '_' &&
            (p[5] < '0' || p[5] > '9')) {
            p[4] = ':';
            break;
        }
    }
    pr("%-30s ", &buf);
    for (i = 0U; i < cnt; i++) {
        v = (val[i] & mask);
        for (j = 0U; j < 32U; j++) {
            m = 1U;
            m <<= j;
            if ((m & mask) > 0U) {
                v = (v >> j);
                break;
            }
        }
        VTSS_FMT(buf, v > 9U ? "0x%x" : "%u", v);
        pr(cnt == 1 ? "%-12s" : "%-8s", &buf);
    }
    if (newline) {
        pr("\n");
    }
}

static void fa_debug_rb_age(lmu_ss_t *ss, u32 val, u32 unit, u32 row_cnt, u32 clk)
{
    u64         x64 = val;
    u32         age;
    const char *str = "usec";

    unit = fa_rb_age_unit(unit);
    x64 *= unit;
    x64 *= FA_RB_AGE_CNT;
    x64 *= row_cnt;
    x64 *= clk;
    x64 = VTSS_DIV64(x64, 1000000U); // psec -> usec
    if (x64 > 100000U) {
        x64 = VTSS_DIV64(x64, 1000U); // usec -> msec
        str = "msec";
    }
    if (x64 > 100000U) {
        x64 = VTSS_DIV64(x64, 1000U); // msec -> sec
        str = "sec";
    }
    age = (u32)x64;
    pr("(0x%x * %u * %u * %u * %u psec = %u %s)\n", val, unit, FA_RB_AGE_CNT, row_cnt, clk, age,
       str);
}

#define FA_DEBUG_RB_FLD(val, fld)    fa_debug_rb_fld(ss, val, VTSS_M_RB_##fld, #fld, NULL, TRUE, 1)
#define FA_DEBUG_RB_FLD_NL(val, fld) fa_debug_rb_fld(ss, val, VTSS_M_RB_##fld, #fld, NULL, FALSE, 1)
#define FA_DEBUG_RB_PORT_FLD(val, fld)                                                             \
    fa_debug_rb_fld(ss, val, VTSS_M_RB_##fld, #fld, NULL, TRUE, 3)
#define FA_DEBUG_RB_PORT_FLD_NL(val, fld)                                                          \
    fa_debug_rb_fld(ss, val, VTSS_M_RB_##fld, #fld, NULL, FALSE, 3)
#define FA_DEBUG_RB_PORT_STICKY(val, fld)                                                          \
    fa_debug_rb_fld(ss, val, VTSS_M_RB_STICKY_##fld##_STICKY, #fld, "STICKY:", TRUE, 3)
#define FA_DEBUG_RB_REG(addr, name) vtss_fa_debug_reg(vtss_state, ss, addr, name)

static vtss_rc fa_debug_redbox(vtss_state_t                  *vtss_state,
                               lmu_ss_t                      *ss,
                               const vtss_debug_info_t *const info)
{
    vtss_rb_conf_t *conf;
    lmu_fmt_buf_t   buf;
    const char     *prefix;
    vtss_rb_id_t    i;
    u32             tgt, j, val, port, m, x[3], clk, cfg0, cfg1, cfg2, idx_next, cnt;
    u64             cur, new, old;
    fa_rb_host_t    host;
    vtss_rc         rc;
    BOOL            proxy;

    for (i = 0U; i < VTSS_REDBOX_CNT; i++) {
        tgt = fa_rb_tgt(i);
        REG_RD(VTSS_RB_RB_CFG(tgt), &val);
        m = VTSS_X_RB_RB_CFG_RB_ENA(val);
        if (m == 0U && !info->full) {
            continue;
        }
        m = (m > 0U ? VTSS_X_RB_RB_CFG_RB_MODE(val) : 10U);
        REG_RD(VTSS_RB_TAXI_IF_CFG(tgt), &val);
        conf = &vtss_state->l2.rb_conf[i];
        pr("RedBox %u (%s), port ", i,
           m == FA_RB_MODE_PRP_SAN   ? "PRP-SAN"
           : m == FA_RB_MODE_HSR_SAN ? "HSR-SAN"
           : m == FA_RB_MODE_HSR_PRP ? "HSR-PRP"
           : m == FA_RB_MODE_HSR_HSR ? "HSR-HSR"
                                     : "NONE");
        if (conf->port_a == VTSS_PORT_NO_NONE) {
            pr("-/");
        } else {
            pr("%u/", VTSS_CHIP_PORT(conf->port_a));
        }
        if (conf->port_b == VTSS_PORT_NO_NONE) {
            pr("-");
        } else {
            pr("%u", VTSS_CHIP_PORT(conf->port_b));
        }
        pr(", taxi %u/%u:\n\n", VTSS_X_RB_TAXI_IF_CFG_LREA_PORT_NO(val),
           VTSS_X_RB_TAXI_IF_CFG_LREB_PORT_NO(val));
        REG_RD(VTSS_RB_RB_CFG(tgt), &val);
        FA_DEBUG_RB_FLD(&val, RB_CFG_RB_ENA);
        FA_DEBUG_RB_FLD_NL(&val, RB_CFG_RB_MODE);
        pr("(%u:PRP-SAN, %u:HSR-SAN, %u:HSR-PRP, %u:HSR-HSR)\n", FA_RB_MODE_PRP_SAN,
           FA_RB_MODE_HSR_SAN, FA_RB_MODE_HSR_PRP, FA_RB_MODE_HSR_HSR);
        FA_DEBUG_RB_FLD(&val, RB_CFG_DEFAULT_FWD_MASK);
        FA_DEBUG_RB_FLD(&val, RB_CFG_RCT_MISSING_DISC_ENA);
        FA_DEBUG_RB_FLD(&val, RB_CFG_RCT_VALIDATE_ENA);
        FA_DEBUG_RB_FLD(&val, RB_CFG_DAN_DETECT_ENA);
        FA_DEBUG_RB_FLD(&val, RB_CFG_IRI_ENA);
        FA_DEBUG_RB_FLD_NL(&val, RB_CFG_PTP_AWARE_SEL);
        pr("(%u:NONE, %u:ETH, %u:IPV4, %u:IPV6)\n", FA_RB_PTP_NONE, FA_RB_PTP_ETH, FA_RB_PTP_IPV4,
           FA_RB_PTP_IPV6);
        FA_DEBUG_RB_FLD(&val, RB_CFG_KEEP_INT_ENA);
        FA_DEBUG_RB_FLD_NL(&val, RB_CFG_HSR_TAG_SEL);
        pr("(0:OUTER, 1:MIDDLE, 2:INNER, 3:RESV)\n");
        REG_RD(VTSS_RB_TAXI_IF_CFG(tgt), &val);
        FA_DEBUG_RB_FLD(&val, TAXI_IF_CFG_LREA_PORT_NO);
        FA_DEBUG_RB_FLD(&val, TAXI_IF_CFG_LREB_PORT_NO);
        FA_DEBUG_RB_FLD(&val, TAXI_IF_CFG_LREA_NEXT);
        FA_DEBUG_RB_FLD(&val, TAXI_IF_CFG_LREB_NEXT);
        REG_RD(VTSS_RB_NETID_CFG(tgt), &val);
        FA_DEBUG_RB_FLD(&val, NETID_CFG_NETID_HOST_TBL_DIS);
        FA_DEBUG_RB_FLD(&val, NETID_CFG_NETID_FILTER_ENA);
        FA_DEBUG_RB_FLD(&val, NETID_CFG_NETID_MASK);
        REG_RD(VTSS_RB_QSYS_CFG(tgt), &val);
        FA_DEBUG_RB_FLD(&val, QSYS_CFG_QUE_CT_ENA);
        FA_DEBUG_RB_FLD(&val, QSYS_CFG_QUE_EXPAND_ENA);
        FA_DEBUG_RB_FLD(&val, QSYS_CFG_QUE_DROP_STICKY);
        REG_RD(VTSS_RB_SPV_CFG(tgt), &val);
        FA_DEBUG_RB_FLD(&val, SPV_CFG_DMAC_ENA);
        FA_DEBUG_RB_FLD_NL(&val, SPV_CFG_HSR_SPV_INT_FWD_SEL);
        VTSS_FMT(buf, "(%u:NONE, %u:COPY, %u:REDIR, %u:DISCARD)\n", FA_RB_SV_FORWARD,
                 FA_RB_SV_CPU_COPY, FA_RB_SV_CPU_ONLY, FA_RB_SV_DISCARD);
        pr(buf.s);
        FA_DEBUG_RB_FLD(&val, SPV_CFG_HSR_MAC_LSB);
        FA_DEBUG_RB_FLD_NL(&val, SPV_CFG_PRP_SPV_INT_FWD_SEL);
        pr(buf.s);
        FA_DEBUG_RB_FLD(&val, SPV_CFG_PRP_MAC_LSB);
        REG_RD(VTSS_RB_DISC_ACCESS_CTRL(tgt), &val);
        fa_debug_rb_fld(ss, &val, VTSS_M_RB_DISC_ACCESS_CTRL_AUTOLRN_REPLACE_RULE_ENA,
                        "AUTO_REPLACE_RULE_ENA", "DISC:", FALSE, 1U);
        pr("(B0:DUPL_MULTI, B1:SEQ, B2:AGE, B3:RANDOM, B4:DUPL_ONE)\n");
        lmu_fmt_buf_init(&buf);
        for (j = 0U; j < 4U; j++) {
            LMU_SS_FMT(&buf.ss, "%s%u:%u%s", j == 0U ? "(" : "", j, fa_rb_age_unit(j),
                       j == 3U ? ")\n" : ", ");
        }
        clk = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);
        for (j = 0U; j < 2U; j++) {
            prefix = (j == FA_RB_AGE_IDX_NT ? "NT:" : "PNT:");
            REG_RD(VTSS_RB_HOST_AUTOAGE_CFG(tgt, j), &val);
            fa_debug_rb_fld(ss, &val, VTSS_M_RB_HOST_AUTOAGE_CFG_UNIT_SIZE, "UNIT_SIZE", prefix,
                            FALSE, 1U);
            pr(buf.s);
            fa_debug_rb_fld(ss, &val, VTSS_M_RB_HOST_AUTOAGE_CFG_PERIOD_VAL, "PERIOD_VAL", prefix,
                            FALSE, 1U);
            fa_debug_rb_age(ss, VTSS_X_RB_HOST_AUTOAGE_CFG_PERIOD_VAL(val),
                            VTSS_X_RB_HOST_AUTOAGE_CFG_UNIT_SIZE(val), FA_HT_ROW_CNT, clk);
            REG_RD(VTSS_RB_HOST_AUTOAGE_CFG_1(tgt, j), &val);
            fa_debug_rb_fld(ss, &val, VTSS_M_RB_HOST_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA,
                            "INTERVAL_ENA", prefix, TRUE, 1U);
        }
        prefix = "DDT:";
        REG_RD(VTSS_RB_DISC_AUTOAGE_CFG(tgt), &val);
        fa_debug_rb_fld(ss, &val, VTSS_M_RB_DISC_AUTOAGE_CFG_UNIT_SIZE, "UNIT_SIZE", prefix, FALSE,
                        1U);
        pr(buf.s);
        fa_debug_rb_fld(ss, &val, VTSS_M_RB_DISC_AUTOAGE_CFG_PERIOD_VAL, "PERIOD_VAL", prefix,
                        FALSE, 1U);
        fa_debug_rb_age(ss, VTSS_X_RB_DISC_AUTOAGE_CFG_PERIOD_VAL(val),
                        VTSS_X_RB_DISC_AUTOAGE_CFG_UNIT_SIZE(val), FA_DT_ROW_CNT, clk);
        REG_RD(VTSS_RB_DISC_AUTOAGE_CFG_1(tgt), &val);
        fa_debug_rb_fld(ss, &val, VTSS_M_RB_DISC_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA, "INTERVAL_ENA",
                        prefix, TRUE, 1U);
        pr("\n");

        for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
            x[j] = j;
        }
        VTSS_FMT(buf, "RedBox %u, port A/B/C:", i);
        fa_debug_rb_fld(ss, x, 0x3U, buf.s, NULL, TRUE, 3U);
        for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
            REG_RD(VTSS_RB_TBL_CFG(tgt, j), &x[j]);
        }
        FA_DEBUG_RB_PORT_FLD(x, TBL_CFG_DUPL_DISC_ENA);
        FA_DEBUG_RB_PORT_FLD_NL(x, TBL_CFG_HOST_TYPE);
        pr("(%u:PROXY, %u:DAN, %u:SAN, %u:LOCAL)\n", FA_HT_PROXY, FA_HT_DAN, FA_HT_SAN,
           FA_HT_LOCAL);
        FA_DEBUG_RB_PORT_FLD(x, TBL_CFG_UPD_HOST_TBL_ENA);
        FA_DEBUG_RB_PORT_FLD(x, TBL_CFG_UPD_DISC_TBL_ENA);
        FA_DEBUG_RB_PORT_FLD(x, TBL_CFG_UPD_SEQ_NUM_ENA);
        FA_DEBUG_RB_PORT_FLD(x, TBL_CFG_NEW_HOST_TBL_DIS);

        for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
            REG_RD(VTSS_RB_FWD_CFG(tgt, j), &x[j]);
        }
        FA_DEBUG_RB_PORT_FLD(x, FWD_CFG_FLD_DST_FWD_MASK);
        FA_DEBUG_RB_PORT_FLD(x, FWD_CFG_SRC_FWD_MASK);
        FA_DEBUG_RB_PORT_FLD(x, FWD_CFG_PROXY_DST_FWD_MASK);
        FA_DEBUG_RB_PORT_FLD(x, FWD_CFG_LOCAL_DST_FWD_MASK);
        FA_DEBUG_RB_PORT_FLD(x, FWD_CFG_NODE_DST_FWD_MASK);
        FA_DEBUG_RB_PORT_FLD(x, FWD_CFG_PROXY_SRC_FWD_MASK);
        FA_DEBUG_RB_PORT_FLD(x, FWD_CFG_LOCAL_SRC_FWD_MASK);
        FA_DEBUG_RB_PORT_FLD(x, FWD_CFG_NODE_SRC_FWD_MASK);

        for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
            REG_RD(VTSS_RB_PORT_CFG(tgt, j), &x[j]);
        }
        FA_DEBUG_RB_PORT_FLD(x, PORT_CFG_CT_EGR_ENA);
        FA_DEBUG_RB_PORT_FLD(x, PORT_CFG_CT_IGR_ENA);
        FA_DEBUG_RB_PORT_FLD_NL(x, PORT_CFG_TAG_MODE);
        pr("(%u:NONE, %u:PRP_NONE, %u:HSR, %u:PRP)\n", FA_RB_TAG_NONE, FA_RB_TAG_PRP_NONE,
           FA_RB_TAG_HSR, FA_RB_TAG_PRP);
        FA_DEBUG_RB_PORT_FLD_NL(x, PORT_CFG_HSR_FILTER_CFG);
        pr("(%u:NONE, %u:HSR, %u:NOT_HSR, %u:REDIR)\n", FA_RB_FLT_NONE, FA_RB_FLT_HSR,
           FA_RB_FLT_NOT_HSR, FA_RB_FLT_REDIR);
        FA_DEBUG_RB_PORT_FLD_NL(x, PORT_CFG_HSR_SPV_FWD_SEL);
        VTSS_FMT(buf, "(%u:NONE, %u:COPY, %u:REDIR, %u:DISCARD)\n", FA_RB_SV_FORWARD,
                 FA_RB_SV_CPU_COPY, FA_RB_SV_CPU_ONLY, FA_RB_SV_DISCARD);
        pr(buf.s);
        FA_DEBUG_RB_PORT_FLD_NL(x, PORT_CFG_PRP_SPV_FWD_SEL);
        pr(buf.s);
        FA_DEBUG_RB_PORT_FLD(x, PORT_CFG_TRANS_NETID);
        FA_DEBUG_RB_PORT_FLD_NL(x, PORT_CFG_TRANS_NETID_SEL);
        pr("(0:NONE, 1:TRANS, 2:ALL, 3:RESV)\n");
        FA_DEBUG_RB_PORT_FLD(x, PORT_CFG_NETID);
        FA_DEBUG_RB_PORT_FLD(x, PORT_CFG_LANID);
        FA_DEBUG_RB_PORT_FLD(x, PORT_CFG_HSR_AWARE_ENA);
        FA_DEBUG_RB_PORT_FLD(x, PORT_CFG_PRP_AWARE_ENA);

        for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
            REG_RD(VTSS_RB_PTP_CFG(tgt, j), &x[j]);
        }
        FA_DEBUG_RB_PORT_FLD(x, PTP_CFG_PTP_ENA);

        for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
            REG_RD(VTSS_RB_BPDU_CFG(tgt, j), &x[j]);
        }
        FA_DEBUG_RB_PORT_FLD(x, BPDU_CFG_BPDU_REDIR_ENA);

        for (j = 0U; j < 2U; j++) {
            x[j] = 0U;
            port = (j > 0U ? conf->port_b : conf->port_a);
            if (port != VTSS_PORT_NO_NONE) {
                port = VTSS_CHIP_PORT(port);
                REG_RD(VTSS_ASM_PORT_CFG(port), &x[j]);
            }
        }
        fa_debug_rb_fld(ss, x, VTSS_M_ASM_PORT_CFG_RB_ENA, "ASM:PORT_CFG_RB_ENA", NULL, TRUE, 2U);

        for (j = 0U; j < 2U; j++) {
            x[j] = 0U;
            port = (j > 0U ? conf->port_b : conf->port_a);
            if (port != VTSS_PORT_NO_NONE) {
                port = VTSS_CHIP_PORT(port);
                REG_RD(VTSS_REW_RTAG_ETAG_CTRL(port), &x[j]);
            }
        }
        fa_debug_rb_fld(ss, x, VTSS_M_REW_RTAG_ETAG_CTRL_RB_ENA, "REW:RTAG_ETAG_CTRL:RB_ENA", NULL,
                        TRUE, 2U);

        for (j = 0U; j < 2U; j++) {
            x[j] = 0U;
            port = (j > 0U ? conf->port_b : conf->port_a);
            if (port != VTSS_PORT_NO_NONE) {
                port = VTSS_CHIP_PORT(port);
                REG_RD(VTSS_REW_PTP_MISC_CFG(port), &x[j]);
            }
        }
        fa_debug_rb_fld(ss, x, VTSS_M_REW_PTP_MISC_CFG_PTP_RB_TAG_DIS,
                        "REW:PTP_MISC_CFG:PTP_TAG_DIS", NULL, TRUE, 2U);
        fa_debug_rb_fld(ss, x, VTSS_M_REW_PTP_MISC_CFG_PTP_RB_PRP_LAN,
                        "REW:PTP_MISC_CFG:PTP_PRP_LAN", NULL, TRUE, 2U);

        REG_RD(VTSS_RB_PTP_MISC_CFG(tgt), &val);
        FA_DEBUG_RB_FLD(&val, PTP_MISC_CFG_PTP_RCT_DIS);
        FA_DEBUG_RB_FLD(&val, PTP_MISC_CFG_PTP_REDIR_INT_ENA);
        FA_DEBUG_RB_FLD(&val, PTP_MISC_CFG_PTP_DUPL_DISC_DIS);
        for (j = 0U; j < 8U; j++) {
            REG_RD(VTSS_RB_PTP_FILTER_CFG(tgt, j), &val);
            VTSS_FMT(buf, "PTP_FILTER_CFG_%u:", j);
            fa_debug_rb_fld(ss, &val, VTSS_M_RB_PTP_FILTER_CFG_PTP_HSR_SEL, "HSR_SEL", buf.s, TRUE,
                            1U);
            fa_debug_rb_fld(ss, &val, VTSS_M_RB_PTP_FILTER_CFG_PTP_VID_SEL, "VID_SEL", buf.s, TRUE,
                            1U);
            fa_debug_rb_fld(ss, &val, VTSS_M_RB_PTP_FILTER_CFG_PTP_FILTER_SEL, "FILTER_SEL", buf.s,
                            FALSE, 1U);
            pr("B0:DMAC, B1:VID, B2:HSR, B3:DIP, B4:DPORT\n");
        }
        for (j = 0U; j < 16U; j++) {
            VTSS_FMT(buf, "PTP_DATA_%u", j);
            FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_PTP_DATA(tgt, j)), buf.s);
        }

        if (info->full) {
            for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
                REG_RD(VTSS_RB_STICKY(tgt, j), &x[j]);
            }
            FA_DEBUG_RB_PORT_STICKY(x, RCT_MISSING_DISC);
            FA_DEBUG_RB_PORT_STICKY(x, RCT_MISSING);
            FA_DEBUG_RB_PORT_STICKY(x, PTP_INT);
            FA_DEBUG_RB_PORT_STICKY(x, PTP_ETH);
            FA_DEBUG_RB_PORT_STICKY(x, PTP_IP4);
            FA_DEBUG_RB_PORT_STICKY(x, PTP_IP6);
            FA_DEBUG_RB_PORT_STICKY(x, HSR_LSDU_ERR);
            FA_DEBUG_RB_PORT_STICKY(x, MODE_T);
            FA_DEBUG_RB_PORT_STICKY(x, SEQUENCE);
            FA_DEBUG_RB_PORT_STICKY(x, PRP_ACCEPT);
            FA_DEBUG_RB_PORT_STICKY(x, PRP_SAN_LAN_MISMATCH);
            FA_DEBUG_RB_PORT_STICKY(x, PRP_DAN_FWD);
            FA_DEBUG_RB_PORT_STICKY(x, PRP_SAN_FWD);
            FA_DEBUG_RB_PORT_STICKY(x, FILTERING);
            FA_DEBUG_RB_PORT_STICKY(x, FORWARDING);
            FA_DEBUG_RB_PORT_STICKY(x, HSR_DUPL_DISC);
            FA_DEBUG_RB_PORT_STICKY(x, PRP_DUPL_DISC);
            FA_DEBUG_RB_PORT_STICKY(x, NETID_INT);
            FA_DEBUG_RB_PORT_STICKY(x, LOCAL_DST_REDIR);
            FA_DEBUG_RB_PORT_STICKY(x, HSR_FILTER);
            FA_DEBUG_RB_PORT_STICKY(x, BPDU_FILTER);
            FA_DEBUG_RB_PORT_STICKY(x, HSR_TAG);
            FA_DEBUG_RB_PORT_STICKY(x, PRP_TRAILER);
            FA_DEBUG_RB_PORT_STICKY(x, PRP_LANID_MISMATCH);
            pr("\n");

            VTSS_FMT(buf, "RedBox %u", i);
            vtss_fa_debug_reg_header(ss, buf.s);
            FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_RB_CFG(tgt)), "RB_CFG");
            FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_TAXI_IF_CFG(tgt)), "TAXI_IF_CFG");
            // FA_DEBUG_RB_REGREG_ADDR(VTSS_RB_QSYS_CFG(tgt), "QSYS_CFG");
            FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_NETID_CFG(tgt)), "NETID_CFG");
            FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CPU_CFG(tgt)), "CPU_CFG");
            FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_SPV_CFG(tgt)), "SPV_CFG");
            FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_HOST_EVENT_STICKY(tgt)), "HOST_STICKY");
            FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_DISC_EVENT_STICKY(tgt)), "DISC_STICKY");
            pr("\n");

            for (j = 0U; j < VTSS_RB_PORT_CNT; j++) {
                VTSS_FMT(buf, "Port %s", j == 0 ? "A" : j == 1 ? "B" : "C");
                vtss_fa_debug_reg_header(ss, buf.s);
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_TBL_CFG(tgt, j)), "TBL_CFG");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_BPDU_CFG(tgt, j)), "BPDU_CFG");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_FWD_CFG(tgt, j)), "FWD_CFG");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_PORT_CFG(tgt, j)), "PORT_CFG");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_STICKY(tgt, j)), "STICKY");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_RX_LL(tgt, j)), "CNT_RX_LL");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_RX_UNT(tgt, j)), "CNT_RX_UNT");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_RX_TAG(tgt, j)), "CNT_RX_TAG");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_RX_WRONG_LAN(tgt, j)), "CNT_RX_WRONG_LAN");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_RX_OWN(tgt, j)), "CNT_RX_OWN");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_TX_LL(tgt, j)), "CNT_TX_LL");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_TX_UNT(tgt, j)), "CNT_TX_UNT");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_TX_TAG(tgt, j)), "CNT_TX_TAG");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_DUPL_ZERO(tgt, j)), "CNT_DUPL_ZERO");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_DUPL_ONE(tgt, j)), "CNT_DUPL_ONE");
                FA_DEBUG_RB_REG(REG_ADDR(VTSS_RB_CNT_DUPL_TWO(tgt, j)), "CNT_DUPL_TWO");
                pr("\n");
            }
        } else {
            pr("\n");
        }

        // Node table and proxy node table
        for (j = 0U; j < 2U; j++) {
            VTSS_MEMSET(&host, 0, sizeof(host));
            cnt = 0U;
            proxy = (j > 0U);
            VTSS_FMT(buf, "RedBox %u %sNode Table", i, proxy ? "Proxy " : "");
            while (TRUE) {
                rc = (info->action > 0U
                          ? fa_rb_host_id_get_next(vtss_state, proxy, i, host.idx, &host)
                          : fa_rb_host_get_next(vtss_state, proxy, i, &host.mac, &host));
                if (rc != VTSS_RC_OK) {
                    break;
                }
                fa_print_host_entry(ss, buf.s, &cnt, &host);
                VTSS_EXIT_ENTER();
            }
            if (cnt > 0U) {
                pr("\nNumber of entries: %u\n\n", cnt);
            }
        }

        // Duplicate discard table
        cnt = 0U;
        if (info->action > 0U) {
            // Get-next based on index
            for (j = 0U; j < FA_DT_CNT; j++) {
                VTSS_RC(fa_print_disc_entry(vtss_state, ss, i, j, &cnt));
            }
        } else {
            // Get-next based on (MAC, seq_no)
            idx_next = FA_DT_CNT;
            old = 0;
            new = 0;
            j = 0U;
            while (TRUE) {
                VTSS_RC(fa_rb_disc_cmd(vtss_state, i, FA_DT_CMD_READ, j));
                REG_RD(VTSS_RB_DISC_ACCESS_CFG_2(tgt), &cfg2);
                if (VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_VLD(cfg2) > 0U) {
                    REG_RD(VTSS_RB_DISC_ACCESS_CFG_0(tgt), &cfg0);
                    REG_RD(VTSS_RB_DISC_ACCESS_CFG_1(tgt), &cfg1);
                    val = VTSS_X_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SMAC_MSB(cfg0);
                    cur = val;
                    cur <<= 32;
                    cur += VTSS_X_RB_DISC_ACCESS_CFG_1_DISC_ENTRY_SMAC_LSB(cfg1);
                    cur <<= 16;
                    val = VTSS_X_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SEQ_NO(cfg0);
                    cur += val;
                    if (cur > old && (idx_next == FA_DT_CNT || cur < new)) {
                        new = cur;
                        idx_next = j;
                    }
                }
                j++;
                if (j == FA_DT_CNT) {
                    if (idx_next == FA_DT_CNT) {
                        break;
                    }
                    VTSS_RC(fa_print_disc_entry(vtss_state, ss, i, idx_next, &cnt));
                    j = 0U;
                    idx_next = FA_DT_CNT;
                    old = new;
                }
            }
        }
        if (cnt > 0U) {
            pr("\nNumber of entries: %u\n\n", cnt);
        }
    }
    return VTSS_RC_OK;
}
#endif
vtss_rc vtss_fa_l2_debug_print(vtss_state_t                  *vtss_state,
                               lmu_ss_t                      *ss,
                               const vtss_debug_info_t *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VLAN, fa_debug_vlan, vtss_state, ss, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PVLAN, fa_debug_pvlan, vtss_state, ss, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MAC_TABLE, fa_debug_mac_table, vtss_state, ss,
                                   info));
#if defined(VTSS_FEATURE_VCAP)
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VXLAT, fa_debug_vxlat, vtss_state, ss, info));
#endif
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_AGGR, fa_debug_aggr, vtss_state, ss, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_STP, fa_debug_stp, vtss_state, ss, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MIRROR, fa_debug_mirror, vtss_state, ss, info));
#if defined(VTSS_FEATURE_REDBOX)
    if (vtss_state->vtss_features[FEATURE_REDBOX]) {
        VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_REDBOX, fa_debug_redbox, vtss_state, ss,
                                       info));
    }
#endif
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_l2_port_map_set(vtss_state_t *vtss_state)
{
    vtss_l2_state_t       *state = &vtss_state->l2;
    vtss_vlan_port_conf_t *conf = &state->vlan_port_conf[0];
    vtss_port_no_t         port_no;
    u32                    port, i, j, value;
    BOOL                   vlan_counters = vtss_vlan_counters_enabled(vtss_state);
    BOOL                   frames, psfp_counters = FALSE;

    /* Setup number of available PGIDs */
    state->pgid_count = (fa_pgid_cnt() + vtss_state->port_count - RT_CHIP_PORTS);

    /* Set flood masks */
    VTSS_RC(vtss_cil_l2_flood_conf_set(vtss_state));

    /* Drop entry */
    state->pgid_drop = vtss_fa_vtss_pgid(vtss_state, PGID_DROP);
    VTSS_RC(fa_pgid_update(vtss_state, PGID_DROP, state->port_none, FALSE));

    /* Flood entry */
    state->pgid_flood = vtss_fa_vtss_pgid(vtss_state, PGID_FLOOD);
    VTSS_RC(fa_pgid_update(vtss_state, PGID_FLOOD, state->port_all, FALSE));

    /* Enable VLAN processing */
    REG_WR(VTSS_ANA_L3_VLAN_CTRL, VTSS_F_ANA_L3_VLAN_CTRL_VLAN_ENA(1));

    /* Setup VLAN configuration */
    VTSS_RC(vtss_cil_l2_vlan_conf_set(vtss_state));

    /* Include all ports in VLAN 1, exclude all ports from VLAN 0 and 4095 */
    VTSS_RC(vtss_cil_l2_vlan_mask_update(vtss_state, 0, state->port_none));
    VTSS_RC(vtss_cil_l2_vlan_mask_update(vtss_state, 1, state->port_all));
    VTSS_RC(vtss_cil_l2_vlan_mask_update(vtss_state, 4095, state->port_none));

    // Avoid using FID zero for other VLANs
    for (i = 2U; i < 4095U; i++) {
        REG_WR(VTSS_ANA_L3_VLAN_CFG(i), VTSS_F_ANA_L3_VLAN_CFG_VLAN_FID(i));
    }

    /* Apply default VLAN configuration to all ports */
    for (port_no = 0U; port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(vtss_cil_l2_vlan_port_conf_update(vtss_state, port_no, conf));
        port = VTSS_CHIP_PORT(port_no);
        REG_WRM_CLR(VTSS_ANA_CL_FILTER_CTRL(port), VTSS_M_ANA_CL_FILTER_CTRL_FILTER_SMAC_MC_DIS);
    }

#if defined(VTSS_FEATURE_L2_MSTP)
    /* Update MSTP table */
    for (i = VTSS_MSTI_START; i < VTSS_MSTI_END; i++) {
        VTSS_RC(vtss_cil_l2_mstp_state_set(vtss_state, 0, i));
    }
#endif

    /* Set MAC age time to default value */
    VTSS_RC(vtss_cil_l2_mac_table_age_time_set(vtss_state));

    /* Enable frame aging */
    REG_WR(VTSS_QSYS_FRM_AGING,
           VTSS_F_QSYS_FRM_AGING_MAX_AGE(500000U / 4U)); /* Set tick to 0.5 sec */
    for (port = 0U; port < RT_CHIP_PORTS; port++) {
        /* Enable aging in disassembler for each port */
        REG_WRM(VTSS_DSM_BUF_CFG(port), VTSS_F_DSM_BUF_CFG_AGING_ENA(1),
                VTSS_M_DSM_BUF_CFG_AGING_ENA);
    }

    /* Disable advanced (VStaX) learning, that is, use basic learning */
    REG_WRM(VTSS_ANA_L2_LRN_CFG, VTSS_F_ANA_L2_LRN_CFG_VSTAX_BASIC_LRN_MODE_ENA(1),
            VTSS_M_ANA_L2_LRN_CFG_VSTAX_BASIC_LRN_MODE_ENA);

    /* Setup own UPSIDs */
#if defined(VTSS_ARCH_SPARX5)
    for (i = 0; i < 3; i++) {
        REG_WR(VTSS_ANA_AC_PS_COMMON_OWN_UPSID(i), i);
        REG_WR(VTSS_ANA_ACL_OWN_UPSID(i), i);
        REG_WR(VTSS_ANA_CL_OWN_UPSID(i), i);
        REG_WR(VTSS_ANA_L2_OWN_UPSID(i), i);
        REG_WR(VTSS_REW_OWN_UPSID(i), i);
    }
#else
    REG_WR(VTSS_ANA_AC_PS_COMMON_OWN_UPSID, 0);
    REG_WR(VTSS_ANA_ACL_OWN_UPSID, 0);
    REG_WR(VTSS_ANA_CL_OWN_UPSID, 0);
    REG_WR(VTSS_ANA_L2_OWN_UPSID, 0);
    REG_WR(VTSS_REW_OWN_UPSID, 0);
#endif

#if defined(VTSS_FEATURE_FRER)
    if (vtss_state->vtss_features[FEATURE_FRER]) {
        /* Enable R-tag awareness */
        REG_WR(VTSS_ANA_CL_RTAG_CFG, VTSS_F_ANA_CL_RTAG_CFG_RTAG_TPID_ENA(1));
        REG_WR(VTSS_EACL_RTAG_CFG, VTSS_F_EACL_RTAG_CFG_RTAG_TPID_ENA(1));
        REG_WR(VTSS_REW_COMMON_CTRL, VTSS_F_REW_COMMON_CTRL_RTAG_TPID_ENA(1));

        /* Set FRER TicksPerSecond to 1000 */
        i = (1000000000U /
             (8U * VTSS_MSTREAM_CNT * vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq)));
        REG_WR(VTSS_EACL_FRER_CFG, VTSS_F_EACL_FRER_CFG_WATCHDOG_PRESCALER(i));
    }
#endif

#if defined(VTSS_FEATURE_PSFP)
    if (vtss_state->vtss_features[FEATURE_PSFP]) {
        /* PSFP CycleTime polling every 10 usec */
        value = (10000000U / vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq));
        REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_CYCLETIME_UPDATE_PERIOD,
               VTSS_F_ANA_AC_SG_ACCESS_SG_CYCLETIME_UPDATE_PERIOD_SG_CT_CLKS(value) |
                   VTSS_F_ANA_AC_SG_ACCESS_SG_CYCLETIME_UPDATE_PERIOD_SG_CT_UPDATE_ENA(1));

        if (vtss_state->init_conf.psfp_counters_enable) {
            psfp_counters = TRUE;
        }
    }
#endif /* VTSS_FEATURE_PSFP */

    if (vlan_counters) {
        /* Enable VLAN counters */
        REG_WRM_SET(VTSS_ANA_AC_PS_COMMON_MISC_CTRL,
                    VTSS_M_ANA_AC_PS_COMMON_MISC_CTRL_USE_VID_AS_ISDX_ENA);
    }

    /* Setup ANA_AC SDX/VLAN statistics:
       - Counters (0,1,2) are byte counters (40-bit)
       - Counters (3,4,5) are frame counters (32-bit) */
    for (i = 0U; i < 6U; i++) {
        j = (i % 3U);
        if (vlan_counters) {
            // 0/3: UC, 1/4: MC, 2/5: BC
            j = (j == 0U ? 3U : j == 1U ? 4U : 6U);
        } else {
            // 0/3: Green, 1/4: Yellow, 2/5: Red
        }
        frames = (i > 2U);
        if (psfp_counters && !frames) {
            /* Enable PSFP counters */
            frames = TRUE;
            j += 7U; /* Match/GateDiscard/FilterDiscard */
        }
        value = 1U;
        value <<= j;
        REG_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG(i),
               VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(frames ? 0
                                                                                             : 1));
        REG_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK(i),
               VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(value));
    }
#if defined(VTSS_ARCH_LAN969X)
    // Include blocked frames in MaxSDU discard counter
    REG_WR(VTSS_ANA_AC_TSN_SF_TSN_SF, VTSS_F_ANA_AC_TSN_SF_TSN_SF_MAX_SDU_CNT_INCL_BLOCKED(1));
#endif
#if defined(VTSS_FEATURE_REDBOX)
    if (vtss_state->vtss_features[FEATURE_REDBOX]) {
        for (vtss_rb_id_t id = 0U; id < VTSS_REDBOX_CNT; id++) {
            VTSS_RC(fa_rb_host_cmd(vtss_state, id, FA_HT_CMD_CLEAR, 0));
            VTSS_RC(fa_rb_disc_cmd(vtss_state, id, FA_DT_CMD_CLEAR, 0));
            vtss_state->l2.rb_conf[id].dd_age_time = 4U;
        }
    }
#endif
    return VTSS_RC_OK;
}

static vtss_rc fa_l2_init(vtss_state_t *vtss_state)
{
    u32 isdx;

    // Disable ISDX based QGRP classification
    for (isdx = 0U; isdx < (VTSS_SDX_CNT + 1U); isdx++) {
        REG_WRM(VTSS_ANA_L2_QGRP_CFG(isdx), VTSS_F_ANA_L2_QGRP_CFG_QGRP_ENA(0),
                VTSS_M_ANA_L2_QGRP_CFG_QGRP_ENA);
    }
#if defined(VTSS_FEATURE_HQOS)
    for (u32 vid = 0; vid < VTSS_VIDS; vid++) {
        vtss_state->l2.vlan_table[vid].hqos_id = VTSS_HQOS_ID_NONE;
    }
#endif
    return VTSS_RC_OK;
}

static vtss_rc fa_l2_poll(vtss_state_t *vtss_state)
{
#if defined(VTSS_EVC_STAT_CNT)
    vtss_l2_state_t *state = &vtss_state->l2;
    vtss_stat_idx_t  stat_idx;
    u32              i, idx;

    if (!vtss_vlan_counters_enabled(vtss_state)) {
        /* Poll counters for 30 SDX entries, giving 8192/30 = 273 seconds between
           each poll. This ensures that any counter can wrap only once between
           each poll. The worst case is a 32-bit frame counter on a 10Gbps port,
           which takes about 0xffffffff/14.880.000.000 = 288 seconds to wrap. */
        for (i = 0U; i < 30U; i++) {
            idx = state->sdx_info.poll_idx;
            stat_idx.idx = (u16)idx;
            stat_idx.edx = (u16)idx;
            VTSS_RC(vtss_fa_sdx_counters_update(vtss_state, &stat_idx, NULL, FALSE));
            idx++;
            state->sdx_info.poll_idx = (idx < state->istat_table.hdr.max_count ? idx : 0U);
        }
    } else {
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
        vtss_vlan_counter_info_t *vlan_info = &vtss_state->l2.vlan_counters_info;

        /* For 100Gbps, 32-bit counter wrap time is about 26 seconds.
           We poll 200 VLAN counters per second, giving approximately 20 seconds
           between each poll */
        for (i = 0; i < 200; i++) {
            idx = (vlan_info->poll_idx + 1);
            vlan_info->poll_idx = (idx < (VTSS_VIDS - 1) ? idx : 0);
            if (fa_vlan_counters_update(vtss_state, idx, NULL, FALSE) != VTSS_RC_OK) {
                break;
            }
        }
#endif /* VTSS_FEATURE_VLAN_COUNTERS */
    }
#if defined(VTSS_FEATURE_FRER)
    if (vtss_state->vtss_features[FEATURE_FRER]) {
        /* Poll counters for 10 entries, giving 1536/10 = 153 seconds between
         * each poll */
        u32 mstream_cnt = VTSS_MSTREAM_CNT;
        u32 cstream_cnt = VTSS_CSTREAM_CNT;
        for (i = 0U; i < 10U; i++) {
            idx = state->poll_idx;
            if (idx < mstream_cnt) {
                if (vtss_state->l2.mstream_conf[idx].recovery) {
                    VTSS_RC(fa_mstream_cnt_update(vtss_state, (u16)idx, NULL, FALSE));
                }
            } else {
                u32 j = (idx - mstream_cnt);
                if (vtss_state->l2.cstream_conf[j].recovery) {
                    VTSS_RC(fa_cstream_cnt_update(vtss_state, (u16)j, NULL, FALSE));
                }
            }
            idx++;
            state->poll_idx = (idx < (mstream_cnt + cstream_cnt) ? idx : 0U);
        }
    }
#endif
#if defined(VTSS_FEATURE_PSFP)
    if (vtss_state->vtss_features[FEATURE_PSFP]) {
        // Detect up to 10 DLB state changes
        for (i = 0U; i < 10U; i++) {
            u32 value;

            REG_RD(VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET, &value);
            if (VTSS_X_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_VLD(value) > 0U) {
                idx = VTSS_X_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_LBSET(value);
                if (idx < VTSS_EVC_POL_CNT) {
                    vtss_state->l2.pol_status[idx].mark_all_red = TRUE;
                }
                VTSS_I("policer %u mark_all_red", idx);
                REG_WR(VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET,
                       VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_LBSET(idx) |
                           VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_VLD(0));
            }
        }
    }
#endif
#if defined(VTSS_FEATURE_REDBOX)
    if (vtss_state->vtss_features[FEATURE_REDBOX]) {
        // RedBox counters must also be polled at least every 288 seconds
        // (32-bit at 10 Gbps)
        idx = state->rb_poll_idx;
        if (idx < VTSS_REDBOX_CNT && state->rb_conf[idx].mode != VTSS_RB_MODE_DISABLED) {
            VTSS_RC(vtss_cil_l2_rb_counters_update(vtss_state, (u8)idx, FALSE));
        }
        state->rb_poll_idx = (idx < 288U ? (idx + 1U) : 0U);
    }
#endif
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_l2_state_t *state = &vtss_state->l2;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->ac_count = 16U;
        // FA-FIXME        state->vsi_info.max_count = VTSS_VSI_CNT;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_INIT, 40);
        VTSS_RC(fa_l2_init(vtss_state));
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_INIT, 40);
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_PMAP, 40);
        VTSS_RC(fa_l2_port_map_set(vtss_state));
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_PMAP, 40);
        break;
    case VTSS_INIT_CMD_POLL: VTSS_RC(fa_l2_poll(vtss_state)); break;
    default:
        // Empty on purpose
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_FA */
