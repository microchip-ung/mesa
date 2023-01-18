// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L2
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)

/* - CIL functions ------------------------------------------------- */

/* Convert from chip PGID to AIL PGID */
u32 vtss_fa_vtss_pgid(const vtss_state_t *const state, u32 pgid)
{
    vtss_port_no_t port_no;

    if (pgid < VTSS_CHIP_PORTS) {
        for (port_no = 0; port_no < state->port_count; port_no++) {
            if (state->port.map[port_no].chip_port == pgid) {
                break;
            }
        }
        return port_no;
    } else {
        return (state->port_count + pgid - VTSS_CHIP_PORTS);
    }
}

/* Convert from AIL PGID to chip PGID */
static u32 fa_chip_pgid(vtss_state_t *vtss_state, u32 pgid)
{
    if (pgid < vtss_state->port_count) {
        return VTSS_CHIP_PORT(pgid);
    } else {
        return (pgid + VTSS_CHIP_PORTS - vtss_state->port_count);
    }
}

static vtss_rc fa_pgid_table_write(vtss_state_t *vtss_state,
                                   u32 pgid, BOOL member[VTSS_PORTS])
{
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[pgid];
    vtss_port_mask_t  pmask;

    pgid = fa_chip_pgid(vtss_state, pgid);
    vtss_port_mask_get(vtss_state, member, &pmask);
    REG_WRX_PMASK(VTSS_ANA_AC_PGID_PGID_CFG, pgid, pmask);
    REG_WR(VTSS_ANA_AC_PGID_PGID_MISC_CFG(pgid),
           VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(pgid_entry->cpu_copy) |
           VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_STACK_TYPE_ENA(0) |
           VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU(pgid_entry->cpu_queue));
    return VTSS_RC_OK;
}

static vtss_rc fa_src_table_write(vtss_state_t *vtss_state,
                                  vtss_port_no_t port_no, BOOL member[VTSS_PORTS])
{
    vtss_port_mask_t pmask;
    u32              port = VTSS_CHIP_PORT(port_no);

    vtss_port_mask_get(vtss_state, member, &pmask);
    REG_WRX_PMASK(VTSS_ANA_AC_SRC_SRC_CFG, port, pmask);
    return VTSS_RC_OK;
}

static vtss_rc fa_aggr_mode_set(vtss_state_t *vtss_state)
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
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_SMAC_ENA            |
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_DMAC_ENA            |
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP4_SIP_ENA         |
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP4_DIP_ENA         |
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP6_SIP_ENA         |
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP6_DIP_ENA         |
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP4_TCPUDP_PORT_ENA |
            VTSS_M_ANA_CL_AGGR_CFG_AGGR_IP6_TCPUDP_PORT_ENA);
    return VTSS_RC_OK;
}

static vtss_rc fa_pmap_table_write(vtss_state_t *vtss_state,
                                   vtss_port_no_t port_no, vtss_port_no_t l_port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 lport = VTSS_CHIP_PORT(l_port_no);

    REG_WRM(VTSS_ANA_CL_PORT_ID_CFG(port),
            VTSS_F_ANA_CL_PORT_ID_CFG_LPORT_NUM(lport),
            VTSS_M_ANA_CL_PORT_ID_CFG_LPORT_NUM);
    return VTSS_RC_OK;
}

static vtss_rc fa_learn_state_set(vtss_state_t *vtss_state,
                                  const BOOL member[VTSS_PORTS])
{
    vtss_port_mask_t  pmask;
    vtss_port_no_t    port;
    BOOL              lrn[VTSS_PORTS];
    vtss_mstp_entry_t *mstp = &vtss_state->l2.mstp_table[0];

    for (port = 0; port < vtss_state->port_count; port++) {
        // Include MSTP instance 0 state
        lrn[port] = (member[port] && mstp->state[port] != VTSS_STP_STATE_DISCARDING);
    }

    vtss_port_mask_get(vtss_state, lrn, &pmask);
    REG_WRX_PMASK(VTSS_ANA_L3_MSTP_LRN_CFG, 0, pmask);
    return VTSS_RC_OK;
}

static vtss_rc fa_mstp_state_set(vtss_state_t *vtss_state,
                                 const vtss_port_no_t port_no,
                                 const vtss_msti_t msti)
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

/* Wait until the MAC table operation is finsished */
static vtss_rc fa_mac_table_idle(vtss_state_t *vtss_state)
{
    u32 cmd;

    while (1) {
        REG_RD(VTSS_LRN_COMMON_ACCESS_CTRL, &cmd);
        if ((VTSS_M_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT & cmd) == 0)
            break;
    }
    return VTSS_RC_OK;
}

static u32 fa_port2upsid(vtss_state_t *vtss_state, u32 *port)
{
    u32 upsid = 0;

    /* Convert local chip port to local UPSID */
    while (*port > 31) {
        *port = (*port - 32);
        upsid++;
    }
    return upsid;
}

static vtss_rc fa_mac_table_add(vtss_state_t *vtss_state,
                                 const vtss_mac_table_entry_t *const entry, u32 pgid)
{
    u32 cfg0, cfg1, cfg2, addr, upsid = 0, aged = 0, fwd_kill = 0, addr_type;
    u32 copy_to_cpu = entry->copy_to_cpu_smac;

    vtss_mach_macl_get(&entry->vid_mac, &cfg0, &cfg1);

    /* Set FWD_KILL to make the switch discard frames in SMAC lookup */
    fwd_kill = (copy_to_cpu || (pgid != vtss_state->l2.pgid_drop) ? 0 : 1);

    addr = fa_chip_pgid(vtss_state, pgid);
    if (addr >= VTSS_CHIP_PORTS) {
        /* Multicast PGID */
        addr_type = MAC_ENTRY_ADDR_TYPE_MC_IDX;
        addr -= VTSS_CHIP_PORTS;
    } else {
        /* Use local (UPSID, UPSPN) */
        addr_type = MAC_ENTRY_ADDR_TYPE_UPSID_PN;
        upsid = fa_port2upsid(vtss_state, &addr);
    }
    cfg2 = (VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(addr + (upsid << 5)) |
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

static vtss_rc fa_mac_table_del(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac)
{
    u32 cfg0, cfg1;

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

/* Return the result from MAC table get operations */
static vtss_rc fa_mac_table_result(vtss_state_t *vtss_state, vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32 cfg0, cfg1, cfg2, addr, type;

    REG_RD(VTSS_LRN_MAC_ACCESS_CFG_2, &cfg2);
    /* Check if entry is valid */
    if (!(cfg2 & VTSS_M_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_VLD)) {
        VTSS_D("not valid");
        return VTSS_RC_ERROR;
    }
    REG_RD(VTSS_LRN_MAC_ACCESS_CFG_0, &cfg0);
    REG_RD(VTSS_LRN_MAC_ACCESS_CFG_1, &cfg1);
    VTSS_D("mach: 0x%08x, macl: 0x%08x, cfg2: 0x%08x", cfg0, cfg1, cfg2);

    /* Extract fields from Jaguar registers */
    VTSS_MEMSET(entry, 0, sizeof(*entry));
    entry->aged        = VTSS_BOOL(VTSS_X_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_FLAG(cfg2));
    entry->copy_to_cpu = 0;
    entry->copy_to_cpu_smac = VTSS_BOOL(cfg2 & VTSS_M_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_COPY);
    entry->cpu_queue   = entry->copy_to_cpu ? VTSS_X_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_QU(cfg2) : 0;
    entry->locked      = VTSS_BOOL(cfg2 & VTSS_M_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_LOCKED);
    addr               = VTSS_X_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(cfg2);
    type               = VTSS_X_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(cfg2);
    entry->vid_mac.vid = ((cfg0 >> 16) & 0xfff);
    entry->vid_mac.mac.addr[0] = ((cfg0 >> 8)  & 0xff);
    entry->vid_mac.mac.addr[1] = ((cfg0 >> 0)  & 0xff);
    entry->vid_mac.mac.addr[2] = ((cfg1 >> 24) & 0xff);
    entry->vid_mac.mac.addr[3] = ((cfg1 >> 16) & 0xff);
    entry->vid_mac.mac.addr[4] = ((cfg1 >> 8)  & 0xff);
    entry->vid_mac.mac.addr[5] = ((cfg1 >> 0)  & 0xff);

    switch (type) {
    case MAC_ENTRY_ADDR_TYPE_UPSID_PN:
        *pgid = vtss_fa_vtss_pgid(vtss_state, addr & 0x7f);
        break;
    case MAC_ENTRY_ADDR_TYPE_MC_IDX:
        /* Multicast PGID */
        *pgid = vtss_fa_vtss_pgid(vtss_state, addr + VTSS_CHIP_PORTS);
        break;
    default:
        VTSS_E("unsupported addr type: %u", type);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_mac_table_get(vtss_state_t *vtss_state, vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32 cfg0, cfg1;

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

static vtss_rc fa_mac_table_get_next(vtss_state_t *vtss_state, vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32               cfg0, cfg1;
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[VTSS_PGID_NONE];

    /* Clear PGID entry for IPMC/GLAG entries */
    VTSS_MEMSET(pgid_entry, 0, sizeof(*pgid_entry));

    vtss_mach_macl_get(&entry->vid_mac, &cfg0, &cfg1);
    VTSS_D("address 0x%08x%08x", cfg0, cfg1);

    /* Get next entry */
    REG_WR(VTSS_LRN_SCAN_NEXT_CFG,
           VTSS_F_LRN_SCAN_NEXT_CFG_SCAN_NEXT_UNTIL_FOUND_ENA(1));
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_0, cfg0);
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_1, cfg1);
    REG_WR(VTSS_LRN_COMMON_ACCESS_CTRL,
           VTSS_F_LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_FIND_SMALLEST) |
           VTSS_F_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    VTSS_RC(fa_mac_table_idle(vtss_state));

    return fa_mac_table_result(vtss_state, entry, pgid);
}

static vtss_rc fa_mac_table_age_time_set(vtss_state_t *vtss_state)
{
    u32 time, units;

    /* Scan two times per age time */
    time = vtss_state->l2.mac_age_time;
    if (time <= 1) {
        units = 0; /* 0: disable ageing */
        time = 0;
    } else {
        units = 3;                   /* 3: unit = 1 sec */
        time = (time/2);             /* age between T/2 and T */
        time = MIN(time, 0xfffffff); /* period_val is 28 bits wide */
    }
    VTSS_D("time %d, units %d", time, units);

    /* Stop aging and set counters to a low value */
    REG_WR(VTSS_LRN_AUTOAGE_CFG(0),
           VTSS_F_LRN_AUTOAGE_CFG_UNIT_SIZE(1) |
           VTSS_F_LRN_AUTOAGE_CFG_PERIOD_VAL(1));
    REG_WRM(VTSS_LRN_AUTOAGE_CFG_1,
            VTSS_F_LRN_AUTOAGE_CFG_1_FORCE_IDLE_ENA(1) |
            VTSS_F_LRN_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT(1),
            VTSS_M_LRN_AUTOAGE_CFG_1_FORCE_IDLE_ENA |
            VTSS_M_LRN_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT);

    REG_WR(VTSS_LRN_AUTOAGE_CFG(0),
           VTSS_F_LRN_AUTOAGE_CFG_UNIT_SIZE(units) |
           VTSS_F_LRN_AUTOAGE_CFG_PERIOD_VAL(time));
    REG_WRM(VTSS_LRN_AUTOAGE_CFG_1,
            VTSS_F_LRN_AUTOAGE_CFG_1_FORCE_IDLE_ENA(!units) |
            VTSS_F_LRN_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT(1),
            VTSS_M_LRN_AUTOAGE_CFG_1_FORCE_IDLE_ENA |
            VTSS_M_LRN_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT);

    return VTSS_RC_OK;
}

static vtss_rc fa_mac_table_age_cmd(vtss_state_t *vtss_state,
                                    BOOL             pgid_age,
                                    u32              pgid,
                                    BOOL             vid_age,
                                    const vtss_vid_t vid,
                                    BOOL             age)
{
    u32        port, addr = 0, addr_type = MAC_ENTRY_ADDR_TYPE_UPSID_PN;
    vtss_vid_t fid = vtss_state->l2.vlan_table[vid].fid;

    if (pgid_age) {
        if (pgid < vtss_state->port_count) {
            /* Port specific ageing, find UPSID and UPSPN */
            port = VTSS_CHIP_PORT(pgid);
            addr = ((fa_port2upsid(vtss_state, &port) << 5) + port);
        } else {
            /* GLAG ageing */
            addr = ((pgid - vtss_state->l2.pgid_glag_dest) & 0x1f);
            addr_type = MAC_ENTRY_ADDR_TYPE_GLAG;
        }
    }

    VTSS_D("pgid_age %u, addr %u, vid_age %u, vid %u", pgid_age, addr, vid_age, vid);

    /* Selective aging */
    REG_WR(VTSS_LRN_SCAN_NEXT_CFG,
           VTSS_F_LRN_SCAN_NEXT_CFG_FID_FILTER_ENA(vid_age) |
           VTSS_F_LRN_SCAN_NEXT_CFG_ADDR_FILTER_ENA(pgid_age) |
           VTSS_F_LRN_SCAN_NEXT_CFG_SCAN_AGE_INTERVAL_MASK(0xf) |
           VTSS_F_LRN_SCAN_NEXT_CFG_SCAN_NEXT_REMOVE_FOUND_ENA(1) |
           VTSS_F_LRN_SCAN_NEXT_CFG_SCAN_NEXT_INC_AGE_BITS_ENA(age));
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_0, VTSS_F_LRN_MAC_ACCESS_CFG_0_MAC_ENTRY_FID(fid == 0 ? vid : fid));
    REG_WR(VTSS_LRN_MAC_ACCESS_CFG_2,
           VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(addr) |
           VTSS_F_LRN_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(addr_type));

    /* Do the aging */
    REG_WR(VTSS_LRN_COMMON_ACCESS_CTRL,
           VTSS_F_LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_SCAN) |
           VTSS_F_LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    /* Wait until MAC operation is finished */
    return fa_mac_table_idle(vtss_state);
}

static vtss_rc fa_mac_table_age(vtss_state_t *vtss_state,
                                BOOL             pgid_age,
                                u32              pgid,
                                BOOL             vid_age,
                                const vtss_vid_t vid)
{
    return fa_mac_table_age_cmd(vtss_state, pgid_age, pgid, vid_age, vid, 1);
}

static vtss_rc fa_mac_table_status_get(vtss_state_t *vtss_state, vtss_mac_table_status_t *status)
{
    u32 value;

    VTSS_MEMSET(status, 0, sizeof(*status));

    /* Detect port move events */
    REG_RD(VTSS_ANA_L2_STICKY, &value);
    value &= (VTSS_M_ANA_L2_STICKY_LOCAL_TO_REMOTE_PORTMOVE_STICKY  |
              VTSS_M_ANA_L2_STICKY_REMOTE_TO_LOCAL_PORTMOVE_STICKY  |
              VTSS_M_ANA_L2_STICKY_REMOTE_TO_REMOTE_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_GLOBAL_TO_GLOBAL_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_GLOBAL_TO_LOCAL_PORTMOVE_STICKY  |
              VTSS_M_ANA_L2_STICKY_LOCAL_TO_GLOBAL_PORTMOVE_STICKY  |
              VTSS_M_ANA_L2_STICKY_LOCAL_TO_LOCAL_PORTMOVE_STICKY);
    REG_WR(VTSS_ANA_L2_STICKY, value);
    if (value) {
        status->moved = 1;
    }

    /* Read and clear sticky register */
    REG_RD(VTSS_LRN_EVENT_STICKY, &value);
    value &= (VTSS_M_LRN_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY |
              VTSS_M_LRN_EVENT_STICKY_AUTO_LRN_INSERT_STICKY |
              VTSS_M_LRN_EVENT_STICKY_AUTOAGE_REMOVE_STICKY |
              VTSS_M_LRN_EVENT_STICKY_AUTOAGE_AGED_STICKY);
    REG_WR(VTSS_LRN_EVENT_STICKY, value);

    /* Detect learn events */
    if (value & VTSS_M_LRN_EVENT_STICKY_AUTO_LRN_INSERT_STICKY) {
        status->learned = 1;
    }

    /* Detect replace events */
    if (value & VTSS_M_LRN_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY) {
        status->replaced = 1;
    }

    /* Detect age events (both aged and removed event is used */
    if (value & (VTSS_M_LRN_EVENT_STICKY_AUTOAGE_AGED_STICKY |
                 VTSS_M_LRN_EVENT_STICKY_AUTOAGE_REMOVE_STICKY)) {
        status->aged = 1;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_learn_port_mode_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_learn_mode_t *mode = &vtss_state->l2.learn_mode[port_no];
    vtss_port_mask_t  pmask, pmask_zero;
    vtss_port_no_t    port_iter;
    u32               cnt = 0;

    vtss_port_mask_port(vtss_state, port_no, &pmask);
    vtss_port_mask_clear(&pmask_zero);

    REG_WRM_PMASK(VTSS_ANA_L2_LRN_SECUR_CFG,        mode->discard   ? pmask : pmask_zero, pmask); // Drop unknown smac
    REG_WRM_PMASK(VTSS_ANA_L2_LRN_SECUR_LOCKED_CFG,                   pmask,              pmask); // Always drop move of locked entries
    REG_WRM_PMASK(VTSS_ANA_L2_AUTO_LRN_CFG,         mode->automatic ? pmask : pmask_zero, pmask); // Enable H/W-based learning
    REG_WRM_PMASK(VTSS_ANA_L2_LRN_COPY_CFG,         mode->cpu       ? pmask : pmask_zero, pmask); // Copyy incoming learn frames to CPU

    // Unfortunately, it's not possible to control per port, whether we want
    // copies of frames whose MAC address is statically learned on another port
    // to the CPU. This is a global configuration. Instead, we need to check
    // whether at least two ports are enabled for secure learning, and if so
    // enable that configuration. If at most one port is enabled, we don't care
    // about such frames. The reason is that it must be possible for the
    // application to move MAC addresses learned on one secure port to another
    // secure port, but not from one secure port to a non-sercure port.
    for (port_iter = 0; port_iter < vtss_state->port_count; port_iter++) {
        if (!vtss_state->l2.learn_mode[port_iter].automatic) {
            // Secure learning is enabled
            if (++cnt == 2) {
                break;
            }
        }
    }

    REG_WRM(VTSS_ANA_L2_LRN_CFG,
            VTSS_F_ANA_L2_LRN_CFG_LOCKED_PORTMOVE_COPY_ENA(cnt < 2 ? 0 : 1),
            VTSS_M_ANA_L2_LRN_CFG_LOCKED_PORTMOVE_COPY_ENA);

    /* If automatic ageing is disabled, flush entries previously learned on port */
    return (mode->automatic ? VTSS_RC_OK : fa_mac_table_age_cmd(vtss_state, 1, port_no, 0, 0, 0));
}

/* ================================================================= *
 *  Layer 2 - VLAN
 * ================================================================= */

static vtss_rc fa_vlan_conf_set(vtss_state_t *vtss_state)
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

    REG_WR(VTSS_ANA_L3_VLAN_CFG(vid),
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_MSTP_PTR(e->msti) |
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_FID(e->fid == 0 ? vid : e->fid) |
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_IGR_FILTER_ENA(e->flags & VLAN_FLAGS_FILTER ? 1 : 0) |
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_FLOOD_DIS(e->flags & VLAN_FLAGS_FLOOD ? 0 : 1) |
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_LRN_DIS(e->flags & VLAN_FLAGS_LEARN ? 0 : 1) |
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_RLEG_ENA(e->rl_enable) |
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_PRIVATE_ENA(e->flags & VLAN_FLAGS_ISOLATED ? 1 : 0) |
           VTSS_F_ANA_L3_VLAN_CFG_VLAN_MIRROR_ENA(e->flags & VLAN_FLAGS_MIRROR ? 1 : 0));
    REG_WR(VTSS_ANA_L3_VMID_CFG(vid), VTSS_F_ANA_L3_VMID_CFG_VMID(e->rl_id));

    return VTSS_RC_OK;
}

static vtss_rc fa_vlan_mask_update(vtss_state_t *vtss_state,
                                   vtss_vid_t   vid,
                                   BOOL         member[VTSS_PORTS])
{
    vtss_port_mask_t pmask;

    vtss_port_mask_get(vtss_state, member, &pmask);
    REG_WRX_PMASK(VTSS_ANA_L3_VLAN_MASK_CFG, vid, pmask);

    return vtss_fa_vlan_update(vtss_state, vid);
}

static vtss_rc fa_vlan_port_conf_update(vtss_state_t *vtss_state,
                                        vtss_port_no_t port_no, vtss_vlan_port_conf_t *conf)
{
    BOOL             aware = 1, c_port = 0, s_port = 0, s_custom_port = 0;
    vtss_vid_t       uvid = conf->untagged_vid;
    u32              value = 0, tpid = 0, aware_dis;
    vtss_port_mask_t pmask, pmask_zero;
    u32              port = VTSS_CHIP_PORT(port_no);

    /* Check port type */
    switch (conf->port_type) {
    case VTSS_VLAN_PORT_TYPE_UNAWARE:
        aware = 0;
        break;
    case VTSS_VLAN_PORT_TYPE_C:
        c_port = 1;
        break;
    case VTSS_VLAN_PORT_TYPE_S:
        s_port = 1;
        tpid = 1;
        break;
    case VTSS_VLAN_PORT_TYPE_S_CUSTOM:
        s_custom_port = 1;
        tpid = 2;
        break;
    default:
        return VTSS_RC_ERROR;
    }

    /* Port VLAN Configuration */
    REG_WRM(VTSS_ANA_CL_VLAN_CTRL(port),
            VTSS_F_ANA_CL_VLAN_CTRL_PORT_VID(conf->pvid) |
            VTSS_F_ANA_CL_VLAN_CTRL_VLAN_POP_CNT(aware ? 1 : 0) |
            VTSS_F_ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA(aware),
            VTSS_M_ANA_CL_VLAN_CTRL_PORT_VID |
            VTSS_M_ANA_CL_VLAN_CTRL_VLAN_POP_CNT |
            VTSS_M_ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA);

    aware_dis = 0x7fff;
    if (aware) {
        aware_dis -= (1 << tpid);
    }
    REG_WR(VTSS_ANA_CL_VLAN_TPID_CTRL(port),
           VTSS_F_ANA_CL_VLAN_TPID_CTRL_BASIC_TPID_AWARE_DIS(aware_dis) |
           VTSS_F_ANA_CL_VLAN_TPID_CTRL_RT_TAG_CTRL(3));

    /* Drop Configuration based on port type and frame type */
    if (conf->frame_type == VTSS_VLAN_FRAME_TAGGED && aware) {
        /* Discard untagged and priority-tagged if aware and tagged-only allowed */
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
            VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CTAG_DIS |
            VTSS_M_ANA_CL_VLAN_FILTER_CTRL_STAG_DIS |
            VTSS_M_ANA_CL_VLAN_FILTER_CTRL_CUST1_STAG_DIS);

    /* Ingress filtering */
    vtss_port_mask_clear(&pmask_zero);
    vtss_port_mask_port(vtss_state, port_no, &pmask);
    REG_WRM_PMASK(VTSS_ANA_L3_VLAN_FILTER_CTRL, conf->ingress_filter ? pmask : pmask_zero, pmask);

    /* Rewriter VLAN tag configuration */
    REG_WRM(VTSS_REW_TAG_CTRL(port),
            VTSS_F_REW_TAG_CTRL_TAG_CFG(uvid == VTSS_VID_ALL ? 0 : uvid == VTSS_VID_NULL ? 2 : 1) |
            VTSS_F_REW_TAG_CTRL_TAG_TPID_CFG(tpid),
            VTSS_M_REW_TAG_CTRL_TAG_CFG |
            VTSS_M_REW_TAG_CTRL_TAG_TPID_CFG);

    REG_WRM(VTSS_REW_PORT_VLAN_CFG(port),
            VTSS_F_REW_PORT_VLAN_CFG_PORT_VID(uvid),
            VTSS_M_REW_PORT_VLAN_CFG_PORT_VID);

    return vtss_fa_vcap_port_update(vtss_state, port_no);
}

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
static vtss_rc fa_vlan_counters_update(vtss_state_t         *vtss_state,
                                       vtss_vid_t           vid,
                                       vtss_vlan_counters_t *const counters,
                                       BOOL                 clear)
{
    vtss_vlan_chip_counters_t *cnt = &vtss_state->l2.vlan_counters_info.counters[vid];
    vtss_vlan_counter_types_t *vlan_counter;
    vtss_chip_counter_pair_t  *chip_counter;
    u32                       i, lsb, msb;

    if (vtss_state->init_conf.vlan_counters_disable) {
        return VTSS_RC_ERROR;
    }

    for (i = 0; i < 3; i++) {
        chip_counter = (i == 0 ? &cnt->rx_unicast : i == 1 ? &cnt->rx_multicast : &cnt->rx_broadcast);

        /* Update byte counter */
        REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(vid, i), &lsb);
        REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT(vid, i), &msb);
        vtss_cmn_counter_40_update(lsb, msb, &chip_counter->bytes, clear);

        /* Update frame counter */
        REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(vid, i + 3), &lsb);
        vtss_cmn_counter_32_update(lsb, &chip_counter->frames, clear);

        /* Update VLAN countes */
        if (counters != NULL) {
            vlan_counter = (i == 0 ? &counters->rx_vlan_unicast :
                            i == 1 ? &counters->rx_vlan_multicast : &counters->rx_vlan_broadcast);
            vlan_counter->frames = chip_counter->frames.value;
            vlan_counter->bytes = chip_counter->bytes.value;
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_vlan_counters_get(vtss_state_t *vtss_state, vtss_vid_t vid, vtss_vlan_counters_t *counters)
{
    return fa_vlan_counters_update(vtss_state, vid, counters, FALSE);
}

static vtss_rc fa_vlan_counters_clear(vtss_state_t *vtss_state, vtss_vid_t vid)
{
    return fa_vlan_counters_update(vtss_state, vid, NULL, TRUE);
}
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

static vtss_rc fa_vcl_port_conf_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_vcl_port_conf_t *conf = &vtss_state->l2.vcl_port_conf[port_no];

    VTSS_RC(vtss_cmn_vcl_port_conf_set(vtss_state, port_no));

    /* Set port key */
    return vtss_fa_vcap_port_key_set(vtss_state, port_no, 2, conf->key_type, conf->dmac_dip);
}

#if defined(VTSS_FEATURE_PSFP)
static u32 fa_psfp_sfid(const vtss_psfp_filter_id_t id)
{
    return (id + 1);
}
#endif

static vtss_rc fa_iflow_conf_set(vtss_state_t *vtss_state, const vtss_iflow_id_t id)
{
    vtss_sdx_entry_t  *sdx = vtss_iflow_lookup(vtss_state, id);
    vtss_port_mask_t  pmask;
    u32               isdx, voe_valid;
    vtss_iflow_conf_t *conf;
    BOOL              independent_mel;

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

    /* DLB/ISDX mappings */
    VTSS_RC(vtss_fa_isdx_update(vtss_state, sdx));

    /* VOE reference, do not point at Port VOE */
    voe_valid = (conf->voe_idx != VTSS_EVC_VOE_IDX_NONE && conf->voe_idx < VTSS_PORT_VOE_BASE_IDX ? 1 : 0);
    independent_mel = (conf->voe_idx == VTSS_VOE_IDX_NONE) ? TRUE : FALSE;    /* Independent MEL when no pointer to active VOE */
    REG_WR(VTSS_ANA_CL_OAM_MEP_CFG(isdx),
           VTSS_F_ANA_CL_OAM_MEP_CFG_MEP_IDX_ENA(voe_valid) |
           VTSS_F_ANA_CL_OAM_MEP_CFG_MEP_IDX(voe_valid ? conf->voe_idx : 0) |
           VTSS_F_ANA_CL_OAM_MEP_CFG_INDEPENDENT_MEL_ENA(independent_mel));

    /* MIP reference */
    REG_WR(VTSS_ANA_CL_ISDX_CFG(isdx),
           VTSS_F_ANA_CL_ISDX_CFG_MIP_IDX(conf->voi_idx == VTSS_EVC_MIP_IDX_NONE ? 0 : vtss_fa_voi_idx_to_mip_idx(conf->voi_idx)));

#if defined(VTSS_FEATURE_FRER)
    REG_WR(VTSS_ANA_AC_FRER_GEN_FRER_GEN(isdx),
           VTSS_F_ANA_AC_FRER_GEN_FRER_GEN_RESET(1) |
           VTSS_F_ANA_AC_FRER_GEN_FRER_GEN_ENABLE(conf->frer.generation));
    {
        vtss_xms_entry_t *ms;
        vtss_port_no_t   port_no;
        u8               port[8], cnt = 0;

        /* Build table of 8 FRER egress chip ports */
        if (conf->frer.mstream_enable) {
            ms = &vtss_state->l2.ms.table[conf->frer.mstream_id];
            if (ms->cnt) {
                for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                    if (VTSS_PORT_BF_GET(ms->port_list, port_no) && cnt < 8) {
                        port[cnt] = VTSS_CHIP_PORT(port_no);
                        cnt++;
                    }
                }
            }
        }
        for (; cnt < 8; cnt++) {
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
#endif

#if defined(VTSS_FEATURE_PSFP)
    REG_WR(VTSS_ANA_L2_TSN_CFG(isdx),
           VTSS_F_ANA_L2_TSN_CFG_TSN_SFID(conf->psfp.filter_enable ? fa_psfp_sfid(conf->psfp.filter_id) : 0));
#endif

    return VTSS_RC_OK;
}

static vtss_rc fa_icnt_get(vtss_state_t *vtss_state, u16 idx, vtss_ingress_counters_t *counters)
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
        if (vtss_state->init_conf.psfp_counters_enable) {
            counters->rx_match = counters->rx_green.bytes;
            counters->rx_green.bytes = 0;
            counters->rx_gate_discard = counters->rx_yellow.bytes;
            counters->rx_yellow.bytes = 0;
            counters->rx_sdu_discard = counters->rx_red.bytes;
            counters->rx_red.bytes = 0;
            counters->rx_gate_pass = (counters->rx_match - counters->rx_gate_discard);
            counters->rx_sdu_pass = (counters->rx_gate_pass - counters->rx_sdu_discard);
        }
#endif
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_ecnt_get(vtss_state_t *vtss_state, u16 idx, vtss_egress_counters_t *counters)
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

static vtss_rc fa_evc_policer_update(vtss_state_t *vtss_state, u16 idx)
{
    return vtss_fa_policer_conf_set(vtss_state, idx, &vtss_state->l2.pol_conf[idx]);
}

static vtss_rc fa_evc_counters_update(vtss_state_t *vtss_state,
                                      vtss_stat_idx_t *stat_idx,
                                      BOOL clear)
{
    return vtss_fa_sdx_counters_update(vtss_state, stat_idx, NULL, clear);
}

/* ================================================================= *
 *  Layer 2 - PVLAN / Isolated ports
 * ================================================================= */

static vtss_rc fa_isolated_port_members_set(vtss_state_t *vtss_state)
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
static vtss_rc fa_pgid_update(vtss_state_t *vtss_state,
                              u32 pgid, BOOL member[VTSS_PORTS], BOOL resv)
{
    vtss_port_no_t    port_no;
    vtss_pgid_entry_t *pgid_entry;

    pgid = vtss_fa_vtss_pgid(vtss_state, pgid);
    pgid_entry = &vtss_state->l2.pgid_table[pgid];
    pgid_entry->resv = resv;
    pgid_entry->references = 1;
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        pgid_entry->member[port_no] = member[port_no];
    }
    return fa_pgid_table_write(vtss_state, pgid, member);
}

static vtss_rc fa_flood_conf_set(vtss_state_t *vtss_state)
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
    VTSS_RC(fa_pgid_update(vtss_state, PGID_IPV6_MC_CTRL,
                           state->ipv6_mc_scope ? state->ipv6_mc_flood : state->mc_flood, TRUE));

    /* IPv6 MC data flood mask */
    VTSS_RC(fa_pgid_update(vtss_state, PGID_IPV6_MC_DATA, state->ipv6_mc_flood, TRUE));

    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - Mirror
 * ================================================================= */

/* Setup all mirroring */
static vtss_rc fa_mirror_conf_set(vtss_state_t *vtss_state)
{
    vtss_mirror_conf_t *conf = &vtss_state->l2.mirror_conf;
    vtss_port_no_t     port_no;
    u32                probe, port = 0, dir, vlan_mode, tx_port, rx_cpu, cpu_set;
    vtss_port_mask_t   pmask;
    BOOL               member[VTSS_PORTS];

    /* Mirror port */
    if (conf->port_no != VTSS_PORT_NO_NONE) {
        port = VTSS_CHIP_PORT(conf->port_no);
    }

    /* Setup all probes */
    for (probe = FA_MIRROR_PROBE_RX; probe <= FA_MIRROR_PROBE_VLAN; probe++) {
        dir = 2; /* Rx mirror by default */
        vlan_mode = 0;
        tx_port = 0;
        rx_cpu = 0;
        cpu_set = 0;

        if (conf->port_no == VTSS_PORT_NO_NONE || vtss_state->l2.tx_forward_aggr[conf->port_no] == 0) {
            /* Mirroring disabled or mirror port down */
            dir = 0;
            vtss_port_mask_clear(&pmask);
        } else if (probe == FA_MIRROR_PROBE_RX) {
            /* Ingress probe */
            vtss_port_mask_get(vtss_state, vtss_state->l2.mirror_ingress, &pmask);
            if (vtss_state->l2.mirror_cpu_ingress) {
                rx_cpu = 0x3; /* Enable Rx mirror from both CPU ports */
            }
        } else if (probe == FA_MIRROR_PROBE_TX) {
            /* Egress probe */
            dir = 1;
            vtss_port_mask_get(vtss_state, vtss_state->l2.mirror_egress, &pmask);
            for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                if (vtss_state->l2.mirror_egress[port_no]) {
                    /* The first egress port is used in the rewriter */
                    tx_port = VTSS_CHIP_PORT(port_no);
                    break;
                }
            }
            if (vtss_state->l2.mirror_cpu_egress) {
                cpu_set = 0xff;
            }
        } else {
            /* VLAN probe */
            vlan_mode = 1;
            for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                member[port_no] = 1;
            }
            vtss_port_mask_get(vtss_state, member, &pmask);
        }

        /* QFWD frame copy */
        REG_WR(VTSS_QFWD_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_MIRROR_PROBE(probe)),
               VTSS_F_QFWD_FRAME_COPY_CFG_FRMC_PORT_VAL(port));

        /* Mirror Rx discards */
        REG_WRM_CTL(VTSS_XQS_MIRROR_CFG, dir == 2, VTSS_F_XQS_MIRROR_CFG_MIRROR_DISCARDS(1 << probe));

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
               VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL(
                   conf->tag == VTSS_MIRROR_TAG_S ? 1 : conf->tag == VTSS_MIRROR_TAG_S_CUSTOM ? 2 : 0));
        REG_WR(VTSS_REW_MIRROR_PROBE_CFG(probe),
               VTSS_F_REW_MIRROR_PROBE_CFG_MIRROR_TX_PORT(tx_port) |
               VTSS_F_REW_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG(conf->tag == VTSS_MIRROR_TAG_NONE ? 0 : 1));
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_ip_mc_update(vtss_state_t *vtss_state,
                               vtss_ipmc_data_t *ipmc, vtss_ipmc_cmd_t cmd)
{
    vtss_vcap_obj_t        *obj = &vtss_state->vcap.is2_b.obj;
    int                    user = (ipmc->src.ssm ? VTSS_IS2_USER_SSM : VTSS_IS2_USER_ASM);
    vtss_vcap_key_size_t   key_size = (ipmc->ipv6 ? VTSS_VCAP_KEY_SIZE_HALF : VTSS_VCAP_KEY_SIZE_QUARTER);
    vtss_res_chg_t         res;
    vtss_vcap_data_t       data;
    vtss_is2_entry_t       entry;
    vtss_hace_t            *ace = &entry.ace;
    vtss_hace_frame_ipv4_t *ipv4 = &ace->key.ipv4;
    vtss_hace_frame_ipv6_t *ipv6 = &ace->key.ipv6;
    vtss_port_no_t         port_no;
    int                    i;

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

static vtss_rc fa_mirror_port_set(vtss_state_t *vtss_state)
{
    VTSS_RC(vtss_cmn_vlan_update_all(vtss_state));

    return fa_mirror_conf_set(vtss_state);
}

static vtss_rc fa_mirror_ingress_set(vtss_state_t *vtss_state)
{
    return fa_mirror_conf_set(vtss_state);
}

static vtss_rc fa_mirror_egress_set(vtss_state_t *vtss_state)
{
    return fa_mirror_conf_set(vtss_state);
}

/* CPU Ingress ports subjects for mirroring */
static vtss_rc fa_mirror_cpu_ingress_set(vtss_state_t *vtss_state)
{
    return fa_mirror_conf_set(vtss_state);
}

/* CPU Egress ports subjects for mirroring */
static vtss_rc fa_mirror_cpu_egress_set(vtss_state_t *vtss_state)
{
    return fa_mirror_conf_set(vtss_state);
}

static vtss_rc fa_aggr_table_write(vtss_state_t *vtss_state,
                                   u32 ac, BOOL member[VTSS_PORTS])
{
    vtss_port_mask_t pmask;

    vtss_port_mask_get(vtss_state, member, &pmask);
    REG_WRX_PMASK(VTSS_ANA_AC_AGGR_AGGR_CFG, ac, pmask);

    /* Setup mirroring when the first aggregation mask is setup */
    return (ac == 0 ? fa_mirror_conf_set(vtss_state) : VTSS_RC_OK);
}

/* ================================================================= *
 *  SFLOW
 * ================================================================= */

static u32 next_power_of_two(u32 x)
{
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return ++x;
}

static u32 fa_sflow_hw_rate(const u32 desired_sw_rate, u32 *const realizable_sw_rate)
{
    u32 hw_rate         = desired_sw_rate ? MAX(VTSS_ROUNDING_DIVISION(FA_SFLOW_MAX_SAMPLE_RATE, desired_sw_rate), FA_SFLOW_MIN_SAMPLE_RATE) : 0;
    *realizable_sw_rate = hw_rate         ?     VTSS_ROUNDING_DIVISION(FA_SFLOW_MAX_SAMPLE_RATE, hw_rate) : 0;
    return hw_rate;
}

static vtss_rc fa_sflow_sampling_rate_convert(struct vtss_state_s *const state, const BOOL power2, const u32 rate_in, u32 *const rate_out)
{
    u32 modified_rate_in;
    // Could happen that two threads call this function simultaneously at boot, but we take the risk.
    // Once sflow_max_power_of_two has been computed, it's no longer a problem with simultaneous access.
    u32 sflow_max_power_of_two = state->l2.sflow_max_power_of_two;

    if (sflow_max_power_of_two == 0) {
        sflow_max_power_of_two = next_power_of_two(FA_SFLOW_MAX_SAMPLE_RATE);
        if ((FA_SFLOW_MAX_SAMPLE_RATE & sflow_max_power_of_two) == 0) {
            sflow_max_power_of_two >>= 1;
        }
        state->l2.sflow_max_power_of_two = sflow_max_power_of_two;
    }

    // Compute the actual sampling rate given the user input.
    if (rate_in != 0 && power2) {
        // Round off to the nearest power of two.
        u32 temp1 = next_power_of_two(rate_in);
        u32 temp2 = temp1 >> 1;
        if (temp1 - rate_in < rate_in-temp2) {
            modified_rate_in = temp1;
        } else {
            modified_rate_in = temp2;
        }
        if (modified_rate_in == 0) {
            modified_rate_in = 1;
        } else if (modified_rate_in > sflow_max_power_of_two) {
            modified_rate_in = sflow_max_power_of_two;
        }
    } else {
        modified_rate_in = rate_in;
    }

    (void)fa_sflow_hw_rate(modified_rate_in, rate_out);
    return VTSS_RC_OK;
}

// Note that Jaguar2 has a sFlow-related bug, ref bug#12246
static vtss_rc fa_sflow_port_conf_set(vtss_state_t *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const vtss_sflow_port_conf_t *const new_conf)
{
#define FA_SFLOW_ENABLED(_conf_) ((_conf_)->sampling_rate > 0 && (_conf_)->type != VTSS_SFLOW_TYPE_NONE)
    vtss_sflow_port_conf_t *cur_conf = &vtss_state->l2.sflow_conf[port_no];
    u32                    hw_rate;
    BOOL                   globally_enable;

    globally_enable = vtss_state->l2.sflow_ena_cnt > 0;

    if (FA_SFLOW_ENABLED(new_conf) && !FA_SFLOW_ENABLED(cur_conf)) {
        if (vtss_state->l2.sflow_ena_cnt == VTSS_PORTS) {
            VTSS_E("sFlow enable counter out of sync");
        }
        if (vtss_state->l2.sflow_ena_cnt++ == 0) {
            globally_enable = TRUE;
        }
    } else if (!FA_SFLOW_ENABLED(new_conf) && FA_SFLOW_ENABLED(cur_conf)) {
        if (vtss_state->l2.sflow_ena_cnt == 0) {
            VTSS_E("sFlow enable counter out of sync");
        } else  if (--vtss_state->l2.sflow_ena_cnt == 0) {
            globally_enable = FALSE;
        }
    }

    *cur_conf = *new_conf;

    REG_WRM(VTSS_ANA_AC_PS_COMMON_PS_COMMON_CFG,
            VTSS_F_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA(globally_enable),
            VTSS_M_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA);

    // Compute the actual sampling rate given the user input.
    // If the user requires power-of-two sampling rates, he is supposed to have provided
    // such a sampling rate in #new_conf.
    // We must ensure that power-of-two input sampling rates gives the same power-of-two
    // output sampling rate.
    hw_rate = fa_sflow_hw_rate(new_conf->sampling_rate, &cur_conf->sampling_rate);

    REG_WRM(VTSS_ANA_AC_SFLOW_SFLOW_CTRL(VTSS_CHIP_PORT(port_no)),
            VTSS_F_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_DIR_SEL(
                new_conf->type == VTSS_SFLOW_TYPE_NONE ? 0 :
                new_conf->type == VTSS_SFLOW_TYPE_RX   ? 1 :
                new_conf->type == VTSS_SFLOW_TYPE_TX   ? 2 : 3) |
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
static vtss_rc fa_cstream_conf_set(vtss_state_t *vtss_state, const vtss_frer_cstream_id_t id)
{
    vtss_frer_stream_conf_t *conf = &vtss_state->l2.cstream_conf[id];
    BOOL                    vector = (conf->alg == VTSS_FRER_RECOVERY_ALG_VECTOR);

    REG_WR(VTSS_EACL_FRER_CFG_COMPOUND(id),
           VTSS_F_EACL_FRER_CFG_COMPOUND_TAKE_NO_SEQUENCE(conf->take_no_seq ? 1 : 0) |
           VTSS_F_EACL_FRER_CFG_COMPOUND_VECTOR_ALGORITHM(vector) |
           VTSS_F_EACL_FRER_CFG_COMPOUND_HISTORY_LENGTH(conf->hlen < 2 ? 1 : (conf->hlen - 1)) |
           VTSS_F_EACL_FRER_CFG_COMPOUND_RESET_TICKS(conf->reset_time ? conf->reset_time : 1) |
           VTSS_F_EACL_FRER_CFG_COMPOUND_RESET(1) |
           VTSS_F_EACL_FRER_CFG_COMPOUND_ENABLE(conf->recovery));
    if (conf->recovery) {
        vtss_state->l2.cs_counters[id].resets.value++;
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_mstream_conf_set(vtss_state_t *vtss_state, const u16 idx)
{
    vtss_frer_stream_conf_t *conf = &vtss_state->l2.mstream_conf[idx];
    BOOL                    vector = (conf->alg == VTSS_FRER_RECOVERY_ALG_VECTOR);

    REG_WR(VTSS_EACL_FRER_CFG_MEMBER(idx),
           VTSS_F_EACL_FRER_CFG_MEMBER_TAKE_NO_SEQUENCE(conf->take_no_seq ? 1 : 0) |
           VTSS_F_EACL_FRER_CFG_MEMBER_VECTOR_ALGORITHM(vector) |
           VTSS_F_EACL_FRER_CFG_MEMBER_HISTORY_LENGTH(conf->hlen < 2 ? 1 : (conf->hlen - 1)) |
           VTSS_F_EACL_FRER_CFG_MEMBER_RESET_TICKS(conf->reset_time ? conf->reset_time : 1) |
           VTSS_F_EACL_FRER_CFG_MEMBER_RESET(1) |
           VTSS_F_EACL_FRER_CFG_MEMBER_ENABLE(conf->recovery) |
           VTSS_F_EACL_FRER_CFG_MEMBER_COMPOUND_HANDLE(conf->cstream_id));
    if (conf->recovery) {
        vtss_state->l2.ms_counters[idx].resets.value++;
    }
    return VTSS_RC_OK;
}

#define FRER_CNT(name, i, cnt, clr)              \
{                                                \
    u32 value;                                   \
    REG_RD(VTSS_EACL_CNT_##name(i), &value);   \
    vtss_cmn_counter_32_update(value, cnt, clr); \
}

static vtss_rc fa_frer_cnt_get(vtss_frer_chip_counters_t *c,
                               vtss_frer_counters_t *counters)
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

static vtss_rc fa_cstream_cnt_update(vtss_state_t *vtss_state,
                                     const vtss_frer_cstream_id_t id,
                                     vtss_frer_counters_t *counters,
                                     BOOL clr)
{
    vtss_frer_chip_counters_t *c = &vtss_state->l2.cs_counters[id];

    FRER_CNT(COMPOUND_OUTOFORDER, id, &c->out_of_order_packets, clr);
    FRER_CNT(COMPOUND_ROGUE, id, &c->rogue_packets, clr);
    FRER_CNT(COMPOUND_PASSED, id, &c->passed_packets, clr);
    FRER_CNT(COMPOUND_DISCARDED, id, &c->discarded_packets, clr);
    FRER_CNT(COMPOUND_LOST, id, &c->lost_packets, clr);
    FRER_CNT(COMPOUND_TAGLESS, id, &c->tagless_packets, clr);
    FRER_CNT(COMPOUND_RESETS, id, &c->resets, clr);
    return fa_frer_cnt_get(c, counters);
}

static vtss_rc fa_cstream_cnt_get(vtss_state_t *vtss_state,
                                  const vtss_frer_cstream_id_t id,
                                  vtss_frer_counters_t *counters)
{
    return fa_cstream_cnt_update(vtss_state, id, counters, counters == NULL);
}

static vtss_rc fa_mstream_cnt_update(vtss_state_t *vtss_state,
                                     const u16 idx,
                                     vtss_frer_counters_t *counters,
                                     BOOL clr)
{
    vtss_frer_chip_counters_t *c = &vtss_state->l2.ms_counters[idx];

    FRER_CNT(MEMBER_OUTOFORDER, idx, &c->out_of_order_packets, clr);
    FRER_CNT(MEMBER_ROGUE, idx, &c->rogue_packets, clr);
    FRER_CNT(MEMBER_PASSED, idx, &c->passed_packets, clr);
    FRER_CNT(MEMBER_DISCARDED, idx, &c->discarded_packets, clr);
    FRER_CNT(MEMBER_LOST, idx, &c->lost_packets, clr);
    FRER_CNT(MEMBER_TAGLESS, idx, &c->tagless_packets, clr);
    FRER_CNT(MEMBER_RESETS, idx, &c->resets, clr);
    return fa_frer_cnt_get(c, counters);
}

static vtss_rc fa_mstream_cnt_get(vtss_state_t *vtss_state,
                                  const u16 idx,
                                  vtss_frer_counters_t *counters)
{
    return fa_mstream_cnt_update(vtss_state, idx, counters, counters == NULL);
}
#endif

#if defined(VTSS_FEATURE_PSFP)
static u32 fa_psfp_sgid(const vtss_psfp_gate_id_t id)
{
    return (id + 1);
}

static u32 fa_psfp_prio(vtss_opt_prio_t *prio)
{
    return (prio->value + (prio->enable ? 0x8 : 0));
}

static vtss_rc fa_gate_conf_set(vtss_state_t *vtss_state, const vtss_psfp_gate_id_t id)
{
    vtss_psfp_state_t     *psfp = &vtss_state->l2.psfp;
    vtss_psfp_gate_conf_t *conf = &psfp->gate[id];
    vtss_psfp_gcl_conf_t  *gcl_conf = &conf->config;
    vtss_psfp_gcl_t       *gcl = &psfp->admin_gcl[id];
    vtss_psfp_gce_t       *gce;
    u32                   i, t = 0, sgid = fa_psfp_sgid(id);

    REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL,
           VTSS_F_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL_SGID(sgid));
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
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_INVALID_RX_ENA(conf->close_invalid_rx.enable ? 1 : 0) |
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_INVALID_RX(conf->close_invalid_rx.value ? 1 : 0) |
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_OCTETS_EXCEEDED_ENA(conf->close_octets_exceeded.enable ? 1 : 0) |
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_OCTETS_EXCEEDED(conf->close_octets_exceeded.value ? 1 : 0));
    REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_4,
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_4_CYCLE_TIME(gcl_conf->cycle_time));
    REG_WR(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_5,
           VTSS_F_ANA_AC_SG_CONFIG_SG_CONFIG_REG_5_CYCLE_TIME_EXT(gcl_conf->cycle_time_ext));
    for (i = 0; i < gcl->gcl_length; i++) {
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

static vtss_rc fa_gate_status_get(vtss_state_t *vtss_state,
                                  const vtss_psfp_gate_id_t id,
                                  vtss_psfp_gate_status_t *const status)
{
    u32 value, prio, sgid = fa_psfp_sgid(id);
    u64 tc;

    REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL,
           VTSS_F_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL_SGID(sgid));
    REG_RD(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_1, &value);
    status->config_change_time.nanoseconds = VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_1_CFG_CHG_TIME_NSEC(value);
    REG_RD(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_2, &value);
    status->config_change_time.seconds = VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_2_CFG_CHG_TIME_SEC_LSB(value);
    REG_RD(VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_3, &value);
    status->config_change_time.sec_msb = VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_3_CFG_CHG_TIME_SEC_MSB(value);
    status->gate_open = VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_3_GATE_STATE(value);
    prio = VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_3_IPS(value);
    status->prio.enable = (prio & 0x8 ? 1 : 0);
    status->prio.value = (prio & 0x7);
    status->config_pending = VTSS_X_ANA_AC_SG_STATUS_SG_STATUS_REG_3_CONFIG_PENDING(value);
    REG_RD(VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3, &value);
    status->close_invalid_rx = VTSS_X_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_INVALID_RX(value);
    status->close_octets_exceeded = VTSS_X_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3_OCTETS_EXCEEDED(value);
    return VTSS_FUNC(ts.timeofday_get, &status->current_time, &tc);
}

static vtss_rc fa_filter_conf_set(vtss_state_t *vtss_state, const vtss_psfp_filter_id_t id)
{
    vtss_psfp_filter_conf_t *conf = &vtss_state->l2.psfp.filter[id];
    u32                     max_sdu = (conf->max_sdu ? conf->max_sdu : VTSS_M_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_MAX_SDU);

    REG_WR(VTSS_ANA_AC_TSN_SF_CFG_TSN_SF_CFG(fa_psfp_sfid(id)),
           VTSS_F_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_SGID(conf->gate_enable ? fa_psfp_sgid(conf->gate_id) : 0) |
           VTSS_F_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_MAX_SDU(max_sdu) |
           VTSS_F_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_STREAM_BLOCK_OVERSIZE_ENA(conf->block_oversize.enable ? 1 : 0) |
           VTSS_F_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_STREAM_BLOCK_OVERSIZE_STATE(conf->block_oversize.value ? 1 : 0));

    return VTSS_RC_OK;
}

static vtss_rc fa_filter_status_get(vtss_state_t *vtss_state,
                                    const vtss_psfp_filter_id_t id,
                                    vtss_psfp_filter_status_t *const status)
{
    u32 value;

    REG_RD(VTSS_ANA_AC_TSN_SF_CFG_TSN_SF_CFG(fa_psfp_sfid(id)), &value);
    status->block_oversize = VTSS_X_ANA_AC_TSN_SF_CFG_TSN_SF_CFG_TSN_STREAM_BLOCK_OVERSIZE_STATE(value);
    return VTSS_RC_OK;
}

static vtss_rc fa_policer_status_get(vtss_state_t *vtss_state,
                                     const u16 idx,
                                     vtss_dlb_policer_status_t *status)
{
    *status = vtss_state->l2.pol_status[idx];
    return VTSS_RC_OK;
}
#endif

/* - Debug print --------------------------------------------------- */

static void fa_debug_pmask_header(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%-33s", name == NULL ? "Port" : name);
    vtss_fa_debug_print_port_header(vtss_state, pr, buf);
}

static void fa_debug_pmask(const vtss_debug_printf_t pr, const char *name, vtss_port_mask_t *pmask)
{
    pr("%-33s", name);
    vtss_fa_debug_print_pmask(pr, pmask);
}

static vtss_rc fa_debug_vlan_entry(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   vtss_vid_t vid,
                                   BOOL header)
{
    u32              value;
    vtss_port_mask_t pmask;
    char             buf[64];

    REG_RDX_PMASK(VTSS_ANA_L3_VLAN_MASK_CFG, vid, &pmask);
    REG_RD(VTSS_ANA_L3_VLAN_CFG(vid), &value);

    if (header) {
        fa_debug_pmask_header(vtss_state, pr, "VID   FID   MSTI  L/F/M/F/P");
    }
    VTSS_SPRINTF(buf, "%-6u%-6u%-6u%u/%u/%u/%u/%u",
            vid,
            VTSS_X_ANA_L3_VLAN_CFG_VLAN_FID(value),
            VTSS_X_ANA_L3_VLAN_CFG_VLAN_MSTP_PTR(value),
            VTSS_X_ANA_L3_VLAN_CFG_VLAN_LRN_DIS(value) ? 0 : 1,
            VTSS_X_ANA_L3_VLAN_CFG_VLAN_FLOOD_DIS(value) ? 0 : 1,
            VTSS_X_ANA_L3_VLAN_CFG_VLAN_MIRROR_ENA(value),
            VTSS_X_ANA_L3_VLAN_CFG_VLAN_IGR_FILTER_ENA(value),
            VTSS_X_ANA_L3_VLAN_CFG_VLAN_PRIVATE_ENA(value));
    fa_debug_pmask(pr, buf, &pmask);

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_vlan(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t *const info)
{
    vtss_port_no_t    port_no;
    vtss_vid_t        vid;
    vtss_vlan_entry_t *vlan_entry;
    u32               port;
    vtss_port_mask_t  pmask;
    BOOL              header = 1;
    char              buf[32];

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_fa_debug_reg_header(pr, buf);
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_VLAN_FILTER_CTRL(port, 0), port, "ANA:VLAN_FILTER_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_VLAN_CTRL(port),      port, "ANA:VLAN_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_VLAN_TPID_CTRL(port), port, "ANA:TPID_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_REW_PORT_VLAN_CFG(port),     port, "REW:PORT_VLAN_CFG");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_REW_TAG_CTRL(port),          port, "REW:TAG_CTRL");
        pr("\n");
    }

    vtss_fa_debug_reg_header(pr, "VLAN COMMON");
    FA_DEBUG_REG_NAME(pr, ANA_L3, VLAN_CTRL, "VLAN_CTRL");
    FA_DEBUG_REG_NAME(pr, ANA_CL, VLAN_STAG_CFG(0), "VLAN_STAG_CFG(0)");
    FA_DEBUG_REG_NAME(pr, ANA_CL, VLAN_STAG_CFG(1), "VLAN_STAG_CFG(1)");
    FA_DEBUG_REG_NAME(pr, ANA_CL, VLAN_STAG_CFG(2), "VLAN_STAG_CFG(2)");
    pr("\n");

    fa_debug_pmask_header(vtss_state, pr, NULL);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_FILTER_CTRL, &pmask);
    fa_debug_pmask(pr, "FILTER_CTRL", &pmask);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_ISOLATED_CFG, &pmask);
    fa_debug_pmask(pr, "ISOLATED_CFG", &pmask);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_COMMUNITY_CFG, &pmask);
    fa_debug_pmask(pr, "COMMUNITY_CFG", &pmask);
    pr("\n");

    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if (info->full || (vlan_entry->flags & VLAN_FLAGS_ENABLED)) {
            VTSS_RC(fa_debug_vlan_entry(vtss_state, pr, vid, header));
            header = 0;
            /* Leave critical region briefly */
            VTSS_EXIT_ENTER();
        }
    }
    if (!header)
        pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_src_table(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    u32              port;
    vtss_port_mask_t pmask;
    char             buf[32];

    vtss_debug_print_header(pr, "Source Masks");
    fa_debug_pmask_header(vtss_state, pr, NULL);
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        REG_RDX_PMASK(VTSS_ANA_AC_SRC_SRC_CFG, port, &pmask);
        VTSS_SPRINTF(buf, "%u", port);
        fa_debug_pmask(pr, buf, &pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_aggr_table(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    u32              ac;
    vtss_port_mask_t pmask;
    char             buf[32];

    vtss_debug_print_header(pr, "Aggregation Masks");
    fa_debug_pmask_header(vtss_state, pr, "AC");
    for (ac = 0; ac < 16; ac++) {
        REG_RDX_PMASK(VTSS_ANA_AC_AGGR_AGGR_CFG, ac, &pmask);
        VTSS_SPRINTF(buf, "%u", ac);
        fa_debug_pmask(pr, buf, &pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_pgid_table(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info,
                                   u32 pgid_start,
                                   u32 pgid_end)
{
    u32              pgid, value;
    vtss_port_mask_t pmask;
    char             buf[32];

    vtss_debug_print_header(pr, "Destination Masks");
    fa_debug_pmask_header(vtss_state, pr, "PGID            CPU  Queue");
    for (pgid = pgid_start; pgid < pgid_end; pgid++) {
        REG_RDX_PMASK(VTSS_ANA_AC_PGID_PGID_CFG, pgid, &pmask);
        REG_RD(VTSS_ANA_AC_PGID_PGID_MISC_CFG(pgid), &value);
        if (pgid > 80 && pmask.m[0] == 0 && pmask.m[1] == 0 && pmask.m[2] == 0 && !info->full) {
            continue;
        }
        VTSS_SPRINTF(buf, "%-5u%-11s%-5u%-5u",
                pgid,
                pgid == PGID_UC_FLOOD ? "UC" :
                pgid == PGID_MC_FLOOD ? "MC" :
                pgid == PGID_IPV4_MC_DATA ? "IPv4 Data" :
                pgid == PGID_IPV4_MC_CTRL ? "IPv4 Ctrl" :
                pgid == PGID_IPV6_MC_DATA ? "IPv6 Data" :
                pgid == PGID_IPV6_MC_CTRL ? "IPv6 Ctrl" :
                pgid == PGID_DROP ? "DROP" :
                pgid == PGID_FLOOD ? "FLOOD" : "",
                VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(value),
                VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU(value));
        fa_debug_pmask(pr, buf, &pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_pvlan(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t *const info)
{
    vtss_port_mask_t pmask;

    fa_debug_pmask_header(vtss_state, pr, NULL);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_ISOLATED_CFG, &pmask);
    fa_debug_pmask(pr, "ISOLATED_CFG", &pmask);
    REG_RD_PMASK(VTSS_ANA_L3_VLAN_COMMUNITY_CFG, &pmask);
    fa_debug_pmask(pr, "COMMUNITY_CFG", &pmask);
    pr("\n");

    return fa_debug_src_table(vtss_state, pr, info);
}

static vtss_rc fa_debug_mac_table(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t *const info)
{
    vtss_mac_entry_t       *entry;
    vtss_mac_table_entry_t mac_entry;
    BOOL                   header = 1;
    u32                    pgid;

    vtss_fa_debug_reg_header(pr, "LRN");
    FA_DEBUG_REGX_NAME(pr, LRN, AUTOAGE_CFG, 0, "AUTOAGE_CFG");
    FA_DEBUG_REG_NAME(pr, LRN, AUTOAGE_CFG_1, "AUTOAGE_CFG1");
    pr("\n");

    /* Dump MAC address table */
    VTSS_MEMSET(&mac_entry, 0, sizeof(mac_entry));

    while (fa_mac_table_get_next(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK) {
        vtss_debug_print_mac_entry(pr, "Dynamic Entries (GET_NEXT)", &header, &mac_entry, pgid);
        VTSS_EXIT_ENTER();
    }
    if (!header) {
        pr("\n");
    }

    /* Dump static entries not returned by the get_next function */
    header = 1;
    for (entry = vtss_state->l2.mac_list_used; entry != NULL; entry = entry->next) {
        vtss_mach_macl_set(&mac_entry.vid_mac, entry->mach, entry->macl);
        if (fa_mac_table_get(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK) {
            vtss_debug_print_mac_entry(pr, "Static Entries (GET)", &header, &mac_entry, pgid);
        }
        VTSS_EXIT_ENTER();
    }
    if (!header) {
        pr("\n");
    }

    /* Flood masks */
    VTSS_RC(fa_debug_pgid_table(vtss_state, pr, info, PGID_UC_FLOOD, PGID_IPV6_MC_CTRL + 1));

    /* Read and clear sticky bits */
    if (info->full) {
        vtss_fa_debug_reg_header(pr, "STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_FILTER_STICKY,         "ANA_CL:FILTER_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_VLAN_FILTER_STICKY(0), "ANA_CL:VLAN_FILTER_STICKY(0)");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_VLAN_FILTER_STICKY(1), "ANA_CL:VLAN_FILTER_STICKY(1)");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_VLAN_FILTER_STICKY(2), "ANA_CL:VLAN_FILTER_STICKY(2)");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_CLASS_STICKY,          "ANA_CL:CLASS_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_CAT_STICKY,            "ANA_CL:CAT_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_ADV_CL_MPLS_STICKY,    "ANA_CL:ADV_CL_MPLS_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_ADV_CL_STICKY,         "ANA_CL:ADV_CL_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_MIP_STICKY,            "ANA_CL:MIP_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_CL_IP_HDR_CHK_STICKY,     "ANA_CL:IP_HDR_CHK_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_L2_STICKY,                "ANA_L2:L2_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_ANA_AC_PS_STICKY_STICKY,      "ANA_AC:PS_STICKY");
        vtss_fa_debug_sticky(vtss_state, pr, VTSS_LRN_EVENT_STICKY,             "LRN:EVENT_STICKY");
        pr("\n");
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_FRER)
static vtss_rc fa_debug_frer(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t *const info)
{
    vtss_xms_entry_t *ms;
    vtss_port_no_t   port_no;
    u16              i, idx;
    char             buf[80];

    for (i = 0; i < VTSS_MSTREAM_CNT; i++) {
        ms = &vtss_state->l2.ms.table[i];
        if (ms->cnt == 0) {
            continue;
        }
        idx = ms->idx;
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (VTSS_PORT_BF_GET(ms->port_list, port_no)) {
                VTSS_SPRINTF(buf, "MSID %u, port %u", i, port_no);
                vtss_fa_debug_reg_header(pr, buf);
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_EACL_FRER_CFG_MEMBER(idx), idx, "EACL:FRER_CFG_MEMBER");
                REG_WRM(VTSS_EACL_FRER_CFG,
                        VTSS_F_EACL_FRER_CFG_ADDR(idx),
                        VTSS_M_EACL_FRER_CFG_ADDR);
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_EACL_FRER_STA_MEMBER, idx, "EACL:FRER_STA_MEMBER");
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_EACL_FRER_HST_MEMBER, idx, "EACL:FRER_HST_MEMBER");
                idx++;
                pr("\n");
            }
        }
    }
    for (i = 0; i < VTSS_CSTREAM_CNT; i++) {
        if (vtss_state->l2.cstream_conf[i].recovery == 0) {
            continue;
        }
        VTSS_SPRINTF(buf, "CSID %u", i);
        vtss_fa_debug_reg_header(pr, buf);
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_EACL_FRER_CFG_COMPOUND(i), i, "EACL:FRER_CFG_COMPOUND");
        REG_WRM(VTSS_EACL_FRER_CFG,
                VTSS_F_EACL_FRER_CFG_ADDR(i),
                VTSS_M_EACL_FRER_CFG_ADDR);
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_EACL_FRER_STA_COMPOUND, i, "EACL:FRER_STA_COMPOUND");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_EACL_FRER_HST_COMPOUND, i, "EACL:FRER_HST_COMPOUND");
        pr("\n");
    }
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_PSFP)
static vtss_rc fa_debug_psfp(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t *const info)
{
    u16  i, j, id;
    char buf[80];
    BOOL first = TRUE;
    
    for (i = 0; i < VTSS_PSFP_FILTER_CNT; i++) {
        vtss_psfp_filter_conf_t *conf = &vtss_state->l2.psfp.filter[i];
        if (info->full || conf->gate_enable || conf->max_sdu || conf->block_oversize.enable) {
            if (first) {
                first = FALSE;
                vtss_fa_debug_reg_header(pr, "PSFP Filters");
            }
            id = fa_psfp_sfid(i);
            vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_TSN_SF_CFG_TSN_SF_CFG(id), id, "TSN_SF_CFG");
        }
    }
    if (!first) {
        pr("\n");
    }

    for (i = 0; i < VTSS_PSFP_GATE_CNT; i++) {
        if (info->full || vtss_state->l2.psfp.gate[i].enable) {
            id = fa_psfp_sgid(i);
            VTSS_SPRINTF(buf, "PSFP Gate %u (%u)", i, id);
            vtss_fa_debug_reg_header(pr, buf);
            REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL,
                   VTSS_F_ANA_AC_SG_ACCESS_SG_ACCESS_CTRL_SGID(id));
            vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_1, "CONFIG_REG_1");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_2, "CONFIG_REG_2");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_3, "CONFIG_REG_3");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_4, "CONFIG_REG_4");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_AC_SG_CONFIG_SG_CONFIG_REG_5, "CONFIG_REG_5");
            for (j = 0; j < 4; j++) {
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_SG_CONFIG_SG_GCL_GS_CONFIG(j), j, "GS_CONFIG");
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_SG_CONFIG_SG_GCL_TI_CONFIG(j), j, "TI_CONFIG");
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_SG_CONFIG_SG_GCL_OCT_CONFIG(j), j, "OCT_CONFIG");
            }
            vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_1, "STATUS_REG_1");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_2, "STATUS_REG_2");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_AC_SG_STATUS_SG_STATUS_REG_3, "STATUS_REG_3");
            pr("\n");
        }
    }
    return VTSS_RC_OK;
}
#endif

static vtss_rc fa_debug_vxlat(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t *const info)
{
    VTSS_RC(vtss_fa_debug_clm_b(vtss_state, pr, info));
    VTSS_RC(vtss_fa_debug_es0(vtss_state, pr, info));
#if defined(VTSS_FEATURE_FRER)
    VTSS_RC(fa_debug_frer(vtss_state, pr, info));
#endif
#if defined(VTSS_FEATURE_PSFP)
    VTSS_RC(fa_debug_psfp(vtss_state, pr, info));
#endif
    return VTSS_RC_OK;
}

static vtss_rc fa_debug_aggr(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t *const info)
{
    u32 port;

    vtss_fa_debug_reg_header(pr, "Logical Ports");
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_PORT_ID_CFG(port), port, "PORT_ID_CFG");
    }
    pr("\n");

    VTSS_RC(fa_debug_src_table(vtss_state, pr, info));
    VTSS_RC(fa_debug_aggr_table(vtss_state, pr, info));
    VTSS_RC(fa_debug_pgid_table(vtss_state, pr, info, 0, VTSS_PGID_FA));

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_stp(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t *const info)
{
    u32              msti;
    vtss_port_mask_t pmask;
    char             buf[16];

    fa_debug_pmask_header(vtss_state, pr, NULL);
    REG_RD_PMASK(VTSS_ANA_L2_LRN_SECUR_CFG, &pmask);
    fa_debug_pmask(pr, "LRN_SECUR_CFG", &pmask);
    REG_RD_PMASK(VTSS_ANA_L2_AUTO_LRN_CFG, &pmask);
    fa_debug_pmask(pr, "AUTO_LRN_CFG", &pmask);
    REG_RD_PMASK(VTSS_ANA_L2_LRN_COPY_CFG, &pmask);
    fa_debug_pmask(pr, "LRN_COPY_CFG", &pmask);
    pr("\n");

    fa_debug_pmask_header(vtss_state, pr, NULL);
    for (msti = VTSS_MSTI_START; msti < VTSS_MSTI_END; msti++) {
        REG_RDX_PMASK(VTSS_ANA_L3_MSTP_LRN_CFG, msti, &pmask);
        VTSS_SPRINTF(buf, "MSTP_LRN_CFG_%u", msti);
        fa_debug_pmask(pr, buf, &pmask);
        REG_RDX_PMASK(VTSS_ANA_L3_MSTP_FWD_CFG, msti, &pmask);
        VTSS_SPRINTF(buf, "MSTP_FWD_CFG_%u", msti);
        fa_debug_pmask(pr, buf, &pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_mirror(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t *const info)
{
    u32              i, j;
    vtss_port_mask_t pmask;
    char             buf[32];

    for (i = 0; i < 3; i++) {
        VTSS_SPRINTF(buf, "%s Probe", i == FA_MIRROR_PROBE_RX ? "Rx" : i == FA_MIRROR_PROBE_TX ? "Tx" : "VLAN");
        vtss_fa_debug_reg_header(pr, buf);
        j = QFWD_FRAME_COPY_CFG_MIRROR_PROBE(i);
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_QFWD_FRAME_COPY_CFG(j),    j, "QFWD:FRAME_COPY_CFG");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_REW_MIRROR_PROBE_CFG(i),   i, "REW:PROBE_CFG");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_REW_MIRROR_TAG_A_CFG(i),   i, "REW:TAG_A_CFG");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_REW_MIRROR_TAG_B_CFG(i),   i, "REW:TAG_B_CFG");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG(i), i, "ANA_AC:PROBE_CFG");
        pr("\n");

        fa_debug_pmask_header(vtss_state, pr, NULL);
        REG_RDX_PMASK(VTSS_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG, i, &pmask);
        VTSS_SPRINTF(buf, "PROBE_PORT_CFG_%u", i);
        fa_debug_pmask(pr, buf, &pmask);
        pr("\n");
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_l2_debug_print(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VLAN,      fa_debug_vlan,      vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PVLAN,     fa_debug_pvlan,     vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MAC_TABLE, fa_debug_mac_table, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VXLAT,     fa_debug_vxlat,     vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_AGGR,      fa_debug_aggr,      vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_STP,       fa_debug_stp,       vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MIRROR,    fa_debug_mirror,    vtss_state, pr, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_l2_port_map_set(vtss_state_t *vtss_state)
{
    vtss_l2_state_t       *state = &vtss_state->l2;
    vtss_vlan_port_conf_t *conf = &state->vlan_port_conf[0];
    vtss_port_no_t        port_no;
    u32                   port, msti, i, j, value, frames;
    BOOL                  vlan_counters = FALSE;
    BOOL                  psfp_counters = FALSE;

    /* Setup number of available PGIDs */
    state->pgid_count = (VTSS_PGID_FA - VTSS_CHIP_PORTS + vtss_state->port_count);

    /* Set flood masks */
    VTSS_RC(fa_flood_conf_set(vtss_state));

    /* Drop entry */
    state->pgid_drop = vtss_fa_vtss_pgid(vtss_state, PGID_DROP);
    VTSS_RC(fa_pgid_update(vtss_state, PGID_DROP, state->port_none, FALSE));

    /* Flood entry */
    state->pgid_flood = vtss_fa_vtss_pgid(vtss_state, PGID_FLOOD);
    VTSS_RC(fa_pgid_update(vtss_state, PGID_FLOOD, state->port_all, FALSE));

    /* Enable VLAN processing */
    REG_WR(VTSS_ANA_L3_VLAN_CTRL,
           VTSS_F_ANA_L3_VLAN_CTRL_VLAN_ENA(1));

    /* Setup VLAN configuration */
    VTSS_RC(fa_vlan_conf_set(vtss_state));

    /* Include all ports in VLAN 1, exclude all ports from VLAN 0 and 4095 */
    VTSS_RC(fa_vlan_mask_update(vtss_state, 0, state->port_none));
    VTSS_RC(fa_vlan_mask_update(vtss_state, 1, state->port_all));
    VTSS_RC(fa_vlan_mask_update(vtss_state, 4095, state->port_none));

    /* Apply default VLAN configuration to all ports */
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(fa_vlan_port_conf_update(vtss_state, port_no, conf));
        port = VTSS_CHIP_PORT(port_no);
        REG_WRM_CLR(VTSS_ANA_CL_FILTER_CTRL(port), VTSS_M_ANA_CL_FILTER_CTRL_FILTER_SMAC_MC_DIS);
    }

    /* Update MSTP table */
    for (msti = VTSS_MSTI_START; msti < VTSS_MSTI_END; msti++) {
        VTSS_RC(fa_mstp_state_set(vtss_state, 0, msti));
    }

    /* Set MAC age time to default value */
    VTSS_RC(fa_mac_table_age_time_set(vtss_state));

    /* Enable frame aging */
    REG_WR(VTSS_QSYS_FRM_AGING,
           VTSS_F_QSYS_FRM_AGING_MAX_AGE(500000/4)); /* Set tick to 0.5 sec */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        /* Enable aging in disassembler for each port */
        REG_WRM(VTSS_DSM_BUF_CFG(port),
                VTSS_F_DSM_BUF_CFG_AGING_ENA(1),
                VTSS_M_DSM_BUF_CFG_AGING_ENA);
    }

    /* Disable advanced (VStaX) learning, that is, use basic learning */
    REG_WRM(VTSS_ANA_L2_LRN_CFG,
            VTSS_F_ANA_L2_LRN_CFG_VSTAX_BASIC_LRN_MODE_ENA(1),
            VTSS_M_ANA_L2_LRN_CFG_VSTAX_BASIC_LRN_MODE_ENA);

    /* Setup own UPSIDs */
    for (i = 0; i < 3; i++) {
        REG_WR(VTSS_ANA_AC_PS_COMMON_OWN_UPSID(i), i);
        REG_WR(VTSS_ANA_ACL_OWN_UPSID(i), i);
        REG_WR(VTSS_ANA_CL_OWN_UPSID(i), i);
        REG_WR(VTSS_ANA_L2_OWN_UPSID(i), i);
        REG_WR(VTSS_REW_OWN_UPSID(i), i);
    }

#if defined(VTSS_FEATURE_FRER)
    /* Enable R-tag awareness */
    REG_WR(VTSS_ANA_CL_RTAG_CFG, VTSS_F_ANA_CL_RTAG_CFG_RTAG_TPID_ENA(1));
    REG_WR(VTSS_EACL_RTAG_CFG, VTSS_F_EACL_RTAG_CFG_RTAG_TPID_ENA(1));
    REG_WR(VTSS_REW_COMMON_CTRL, VTSS_F_REW_COMMON_CTRL_RTAG_TPID_ENA(1));

    /* Set FRER TicksPerSecond to 1000 */
    i = (1000000000/(8*1024*vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq)));
    REG_WR(VTSS_EACL_FRER_CFG, VTSS_F_EACL_FRER_CFG_WATCHDOG_PRESCALER(i));
#endif

    /* VLAN counters */
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    if (!vtss_state->init_conf.vlan_counters_disable) {
        vlan_counters = TRUE;
    }
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

#if defined(VTSS_FEATURE_PSFP)
    /* PSFP CycleTime polling every 10 usec */
    value = (10000000 / vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq));
    REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_CYCLETIME_UPDATE_PERIOD,
           VTSS_F_ANA_AC_SG_ACCESS_SG_CYCLETIME_UPDATE_PERIOD_SG_CT_CLKS(value) |
           VTSS_F_ANA_AC_SG_ACCESS_SG_CYCLETIME_UPDATE_PERIOD_SG_CT_UPDATE_ENA(1));

    if (vtss_state->init_conf.psfp_counters_enable) {
        psfp_counters = TRUE;
    }
#endif /* VTSS_FEATURE_VLAN_COUNTERS */


    if (vlan_counters) {
        /* Enable VLAN counters */
        REG_WRM_SET(VTSS_ANA_AC_PS_COMMON_MISC_CTRL, VTSS_M_ANA_AC_PS_COMMON_MISC_CTRL_USE_VID_AS_ISDX_ENA);
    }

    /* Setup ANA_AC SDX/VLAN statistics:
       - Counters (0,1,2) are byte counters (40-bit)
       - Counters (3,4,5) are frame counters (32-bit) */
    for (i = 0; i < 6; i++) {
        j = (i % 3);
        if (vlan_counters) {
            // 0/3: UC, 1/4: MC, 2/5: BC
            j = (j == 0 ? 3 : j == 1 ? 4 : 6);
        } else {
            // 0/3: Green, 1/4: Yellow, 2/5: Red
        }
        frames = (i > 2);
        if (psfp_counters && !frames) {
            /* Enable PSFP counters */
            frames = TRUE;
            j += 7; /* Match/GateDiscard/FilterDiscard */
        }
        value = (1 << j);
        REG_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG(i),
               VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(frames ? 0 : 1));
        REG_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK(i),
               VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(value));
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_l2_init(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_l2_poll(vtss_state_t *vtss_state)
{
    vtss_l2_state_t *state = &vtss_state->l2;
    vtss_stat_idx_t stat_idx;
    u32             i, idx;
    BOOL            vlan_counters_disable = TRUE;

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    vlan_counters_disable = vtss_state->init_conf.vlan_counters_disable;
#endif

    if (vlan_counters_disable) {
        /* Poll counters for 30 SDX entries, giving 8192/30 = 273 seconds between each poll.
           This ensures that any counter can wrap only once between each poll.
           The worst case is a 32-bit frame counter on a 10Gbps port, which takes about
           0xffffffff/14.880.000.000 = 288 seconds to wrap. */
        for (i = 0; i < 30; i++) {
            idx = state->sdx_info.poll_idx;
            stat_idx.idx = idx;
            stat_idx.edx = idx;
            VTSS_RC(vtss_fa_sdx_counters_update(vtss_state, &stat_idx, NULL, FALSE));
            idx++;
            state->sdx_info.poll_idx = (idx < VTSS_EVC_STAT_CNT ? idx : 0);
        }
    } else {
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
        vtss_vlan_counter_info_t *vlan_info = &vtss_state->l2.vlan_counters_info;

        /* For 100Gbps, 32-bit counter wrap time is about 26 seconds.
           We poll 200 VLAN counters per second, giving approximately 20 seconds between each poll */
        for (i = 0; i < 200; i++) {
            idx = (vlan_info->poll_idx + 1);
            vlan_info->poll_idx = (idx < (VTSS_VIDS - 1) ? idx : 0);
            VTSS_RC(fa_vlan_counters_update(vtss_state, idx, NULL, FALSE));
        }
#endif /* VTSS_FEATURE_VLAN_COUNTERS */
    }
#if defined(VTSS_FEATURE_FRER)
    /* Poll counters for 10 entries, giving 1536/10 = 153 seconds between each poll */
    for (i = 0; i < 10; i++) {
        idx = state->poll_idx;
        if (idx < VTSS_MSTREAM_CNT) {
            if (vtss_state->l2.mstream_conf[idx].recovery) {
                VTSS_RC(fa_mstream_cnt_update(vtss_state, idx, NULL, FALSE));
            }
        } else {
            u32 j = (idx - VTSS_MSTREAM_CNT);
            if (vtss_state->l2.cstream_conf[j].recovery) {
                VTSS_RC(fa_cstream_cnt_update(vtss_state, j, NULL, FALSE));
            }
        }
        idx++;
        state->poll_idx = (idx < (VTSS_MSTREAM_CNT + VTSS_CSTREAM_CNT) ? idx : 0);
    }
#endif
#if defined(VTSS_FEATURE_PSFP)
    // Detect up to 10 DLB state changes
    for (i = 0; i < 10; i++) {
        u32 value;

        REG_RD(VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET, &value);
        if (VTSS_X_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_VLD(value)) {
            idx = VTSS_X_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_LBSET(value);
            if (idx < VTSS_EVC_POL_CNT) {
                vtss_state->l2.pol_status[idx].mark_all_red = 1;
            }
            VTSS_I("policer %u mark_all_red", idx);
            REG_WR(VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET,
                   VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_LBSET(idx) |
                   VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_VLD(0));
        }
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_l2_state_t *state = &vtss_state->l2;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->mac_table_add               = fa_mac_table_add;
        state->mac_table_del               = fa_mac_table_del;
        state->mac_table_get               = fa_mac_table_get;
        state->mac_table_get_next          = fa_mac_table_get_next;
        state->mac_table_age_time_set      = fa_mac_table_age_time_set;
        state->mac_table_age               = fa_mac_table_age;
        state->mac_table_status_get        = fa_mac_table_status_get;
        state->learn_port_mode_set         = fa_learn_port_mode_set;
        state->learn_state_set             = fa_learn_state_set;
        state->mstp_state_set              = fa_mstp_state_set;
        state->mstp_vlan_msti_set          = vtss_cmn_vlan_members_set;
        state->erps_vlan_member_set        = vtss_cmn_erps_vlan_member_set;
        state->erps_port_state_set         = vtss_cmn_erps_port_state_set;
        state->pgid_table_write            = fa_pgid_table_write;
        state->src_table_write             = fa_src_table_write;
        state->aggr_table_write            = fa_aggr_table_write;
        state->aggr_mode_set               = fa_aggr_mode_set;
        state->pmap_table_write            = fa_pmap_table_write;
        state->vlan_conf_set               = fa_vlan_conf_set;
        state->vlan_port_conf_set          = vtss_cmn_vlan_port_conf_set;
        state->vlan_port_conf_update       = fa_vlan_port_conf_update;
        state->vlan_port_members_set       = vtss_cmn_vlan_members_set;
        state->vlan_mask_update            = fa_vlan_mask_update;
        state->vlan_tx_tag_set             = vtss_cmn_vlan_tx_tag_set;
        state->isolated_vlan_set           = vtss_cmn_vlan_members_set;
        state->isolated_port_members_set   = fa_isolated_port_members_set;
        state->flood_conf_set              = fa_flood_conf_set;
        state->ipv4_mc_add                 = vtss_cmn_ipv4_mc_add;
        state->ipv4_mc_del                 = vtss_cmn_ipv4_mc_del;
        state->ipv6_mc_add                 = vtss_cmn_ipv6_mc_add;
        state->ipv6_mc_del                 = vtss_cmn_ipv6_mc_del;
        state->ip_mc_update                = fa_ip_mc_update;
        state->mirror_port_set             = fa_mirror_port_set;
        state->mirror_ingress_set          = fa_mirror_ingress_set;
        state->mirror_egress_set           = fa_mirror_egress_set;
        state->mirror_cpu_ingress_set      = fa_mirror_cpu_ingress_set;
        state->mirror_cpu_egress_set       = fa_mirror_cpu_egress_set;
        state->eps_port_set                = vtss_cmn_eps_port_set;
        state->sflow_port_conf_set         = fa_sflow_port_conf_set;
        state->sflow_sampling_rate_convert = fa_sflow_sampling_rate_convert;
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
        state->vlan_counters_get           = fa_vlan_counters_get;
        state->vlan_counters_clear         = fa_vlan_counters_clear;
#endif /* VTSS_FEATURE_VLAN_COUNTERS */
        state->vcl_port_conf_set        = fa_vcl_port_conf_set;
        state->vce_add                  = vtss_cmn_vce_add;
        state->vce_del                  = vtss_cmn_vce_del;
        state->vlan_trans_group_add     = vtss_cmn_vlan_trans_group_add;
        state->vlan_trans_group_del     = vtss_cmn_vlan_trans_group_del;
        state->vlan_trans_group_get     = vtss_cmn_vlan_trans_group_get;
        state->vlan_trans_port_conf_set = vtss_cmn_vlan_trans_port_conf_set;
        state->vlan_trans_port_conf_get = vtss_cmn_vlan_trans_port_conf_get;
        state->iflow_conf_set = fa_iflow_conf_set;
#if defined(VTSS_FEATURE_FRER)
        state->cstream_conf_set = fa_cstream_conf_set;
        state->mstream_conf_set = fa_mstream_conf_set;
        state->cstream_cnt_get = fa_cstream_cnt_get;
        state->mstream_cnt_get = fa_mstream_cnt_get;
#endif
#if defined(VTSS_FEATURE_PSFP)
        state->psfp_gate_conf_set = fa_gate_conf_set;
        state->psfp_gate_status_get = fa_gate_status_get;
        state->psfp_filter_conf_set = fa_filter_conf_set;
        state->psfp_filter_status_get = fa_filter_status_get;
        state->policer_status_get = fa_policer_status_get;
#endif
        state->icnt_get = fa_icnt_get;
        state->ecnt_get = fa_ecnt_get;
        state->ac_count = 16;
// FA-FIXME        state->vsi_info.max_count = VTSS_VSI_CNT;
        state->policer_update = fa_evc_policer_update;
        state->counters_update = fa_evc_counters_update;
        state->isdx_update = vtss_fa_isdx_update;
        state->sdx_info.max_count = VTSS_SDX_CNT;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(fa_l2_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(fa_l2_port_map_set(vtss_state));
        break;
    case VTSS_INIT_CMD_POLL:
        VTSS_RC(fa_l2_poll(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_FA */
