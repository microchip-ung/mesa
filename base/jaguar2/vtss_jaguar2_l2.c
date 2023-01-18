// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L2
#include "vtss_jaguar2_cil.h"

#if defined(VTSS_ARCH_JAGUAR_2)

/* - CIL functions ------------------------------------------------- */

/* Wait until the MAC operation is finsished */
/* Polling method is used, the sticky interrupt is not used */
static vtss_rc jr2_mac_table_idle(vtss_state_t *vtss_state)
{
    u32 cmd;    
    while (1) {
        JR2_RD(VTSS_LRN_COMMON_COMMON_ACCESS_CTRL, &cmd); 
        if ((VTSS_M_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT & cmd) == 0)
            break;
    }
    return VTSS_RC_OK;
}
 
vtss_rc vtss_jr2_pgid_table_write_adv(vtss_state_t *vtss_state,
                                      u32                    pgid, 
                                      u64                    pmask, 
                                      BOOL                   cpu_copy, 
                                      vtss_packet_rx_queue_t cpu_queue, 
                                      BOOL                   stack_type_ena)
{
    JR2_WRX_PMASK(VTSS_ANA_AC_PGID_PGID_CFG, pgid, pmask);
    JR2_WR(VTSS_ANA_AC_PGID_PGID_MISC_CFG(pgid), 
           VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(cpu_copy) |
           VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_STACK_TYPE_ENA(stack_type_ena) |
           VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU(cpu_queue));
    return VTSS_RC_OK;
}

static vtss_rc jr2_pgid_table_write(vtss_state_t *vtss_state,
                                    u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[pgid];
    u64               pmask = vtss_jr2_port_mask(vtss_state, member);

    return vtss_jr2_pgid_table_write_adv(vtss_state,
                                         vtss_jr2_chip_pgid(vtss_state, pgid),
                                         pmask,
                                         pgid_entry->cpu_copy,
                                         pgid_entry->cpu_queue,
                                         0);
}

static vtss_rc jr2_src_table_write(vtss_state_t *vtss_state,
                                    vtss_port_no_t port_no, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    u64 pmask = vtss_jr2_port_mask(vtss_state, member);
    u32 port = VTSS_CHIP_PORT(port_no);

    JR2_WRX_PMASK(VTSS_ANA_AC_SRC_SRC_CFG, port, pmask);
    return VTSS_RC_OK;
}

static vtss_rc jr2_aggr_mode_set(vtss_state_t *vtss_state)
{
    vtss_aggr_mode_t *mode = &vtss_state->l2.aggr_mode;

    JR2_WRM(VTSS_ANA_CL_COMMON_AGGR_CFG,
            VTSS_F_ANA_CL_COMMON_AGGR_CFG_AGGR_SMAC_ENA(mode->smac_enable) |
            VTSS_F_ANA_CL_COMMON_AGGR_CFG_AGGR_DMAC_ENA(mode->dmac_enable) |
            VTSS_F_ANA_CL_COMMON_AGGR_CFG_AGGR_IP4_SIPDIP_ENA(mode->sip_dip_enable) |
            VTSS_F_ANA_CL_COMMON_AGGR_CFG_AGGR_IP6_SIPDIP_ENA(mode->sip_dip_enable) |
            VTSS_F_ANA_CL_COMMON_AGGR_CFG_AGGR_IP4_TCPUDP_PORT_ENA(mode->sport_dport_enable) |
            VTSS_F_ANA_CL_COMMON_AGGR_CFG_AGGR_IP6_TCPUDP_PORT_ENA(mode->sport_dport_enable),
            VTSS_M_ANA_CL_COMMON_AGGR_CFG_AGGR_SMAC_ENA            |
            VTSS_M_ANA_CL_COMMON_AGGR_CFG_AGGR_DMAC_ENA            |
            VTSS_M_ANA_CL_COMMON_AGGR_CFG_AGGR_IP4_SIPDIP_ENA      |
            VTSS_M_ANA_CL_COMMON_AGGR_CFG_AGGR_IP6_SIPDIP_ENA      |
            VTSS_M_ANA_CL_COMMON_AGGR_CFG_AGGR_IP4_TCPUDP_PORT_ENA |
            VTSS_M_ANA_CL_COMMON_AGGR_CFG_AGGR_IP6_TCPUDP_PORT_ENA);
    return VTSS_RC_OK;
}

/* Update PGID state for reserved entry and update chip */
static vtss_rc jr2_pgid_update(vtss_state_t *vtss_state,
                               u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_port_no_t    port_no;
    vtss_pgid_entry_t *pgid_entry;
    
    pgid = vtss_jr2_vtss_pgid(vtss_state, pgid);
    pgid_entry = &vtss_state->l2.pgid_table[pgid];
    pgid_entry->resv = 1;
    pgid_entry->references = 1;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
        pgid_entry->member[port_no] = member[port_no];
    return jr2_pgid_table_write(vtss_state, pgid, member);
}

static vtss_rc jr2_pmap_table_write(vtss_state_t *vtss_state,
                                    vtss_port_no_t port_no, vtss_port_no_t l_port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 lport = VTSS_CHIP_PORT(l_port_no);

    JR2_WR(VTSS_ANA_CL_PORT_PORT_ID_CFG(port), VTSS_F_ANA_CL_PORT_PORT_ID_CFG_LPORT_NUM(lport));
    return VTSS_RC_OK;
}

static vtss_rc jr2_learn_state_set(vtss_state_t *vtss_state,
                                   const BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_port_no_t    port;
    BOOL              lrn[VTSS_PORTS];
    vtss_mstp_entry_t *mstp = &vtss_state->l2.mstp_table[0];

    for (port = 0; port < vtss_state->port_count; port++) {
        // Include MSTP instance 0 state
        lrn[port] = (member[port] && mstp->state[port] != VTSS_STP_STATE_DISCARDING);
    }

    /* Setup learn mask */
    u64 pmask = vtss_jr2_port_mask(vtss_state, lrn);

    JR2_WRX_PMASK(VTSS_ANA_L3_MSTP_MSTP_LRN_CFG, 0, pmask);
    return VTSS_RC_OK;
}

static vtss_rc jr2_mstp_state_set(vtss_state_t *vtss_state,
                                  const vtss_port_no_t port_no,
                                  const vtss_msti_t msti)
{
    BOOL             fwd[VTSS_PORTS], lrn[VTSS_PORTS];
    vtss_port_no_t   port;
    vtss_stp_state_t state;
    u64              pmask;

    for (port = 0; port < vtss_state->port_count; port++) {
        state = vtss_state->l2.mstp_table[msti].state[port];
        fwd[port] = (state == VTSS_STP_STATE_FORWARDING ? 1 : 0);
        lrn[port] = (state == VTSS_STP_STATE_DISCARDING ? 0 : 1);
        if (msti == 0 && vtss_state->l2.learn[port] == 0) {
            // Include port learn state for MSTI 0
            lrn[port] = 0;
        }
    }
    pmask = vtss_jr2_port_mask(vtss_state, fwd);
    JR2_WRX_PMASK(VTSS_ANA_L3_MSTP_MSTP_FWD_CFG, msti, pmask);
    pmask = vtss_jr2_port_mask(vtss_state, lrn);
    JR2_WRX_PMASK(VTSS_ANA_L3_MSTP_MSTP_LRN_CFG, msti, pmask);

    return vtss_cmn_mstp_state_set(vtss_state, port_no, msti);
}

static u32 jr2_port2upsid(vtss_state_t *vtss_state, u32 *port)
{
    u32 upsid = 0;

    /* Convert local chip port to local UPSID */
    if (*port > 31) {
        *port = (*port - 32);
        upsid++;
    }
    return upsid;
}

/* VLAN is considered managed if the broadcast address is added with CPU copy flag set */
static vtss_rc jr2_vlan_management_update(vtss_state_t *vtss_state,
                                          const vtss_vid_mac_t *const vid_mac, BOOL cpu_copy)
{
    vtss_vlan_entry_t *vlan_entry = &vtss_state->l2.vlan_table[vid_mac->vid];
    u32               i;
    BOOL              mgmt = cpu_copy;

    for (i = 0; i < 6; i++) {
        if (vid_mac->mac.addr[i] != 0xff) {
            return VTSS_RC_OK;
        }
    }
    if (vlan_entry->mgmt != mgmt) {
        /* Management flag changed */
        vlan_entry->mgmt = mgmt;
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_mac_table_add(vtss_state_t *vtss_state,
                                 const vtss_mac_table_entry_t *const entry, u32 pgid)
{
    u32 mach, macl, cfg2, addr, upsid = 0, aged = 0, fwd_kill = 0, addr_type;
    u32 copy_to_cpu = entry->copy_to_cpu_smac;

    vtss_mach_macl_get(&entry->vid_mac, &mach, &macl);
   
    /* Set FWD_KILL to make the switch discard frames in SMAC lookup */
    fwd_kill = (copy_to_cpu || (pgid != vtss_state->l2.pgid_drop) ? 0 : 1);

    addr = vtss_jr2_chip_pgid(vtss_state, pgid);
    if (addr >= VTSS_CHIP_PORTS) {
        /* Multicast PGID */
        addr_type = MAC_ENTRY_ADDR_TYPE_MC_IDX;
        addr -= VTSS_CHIP_PORTS;
    } else {
        /* Use local (UPSID, UPSPN) */
        addr_type = MAC_ENTRY_ADDR_TYPE_UPSID_PN;
        upsid = jr2_port2upsid(vtss_state, &addr);
    }
    cfg2 = (VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(addr + (upsid << 5)) |
            VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(addr_type) |
            VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_SRC_KILL_FWD(fwd_kill) |
            VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_COPY(copy_to_cpu) |
            VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_QU(entry->cpu_queue) |
            VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_FLAG(aged) |
            VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_LOCKED(entry->locked) |
            VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_VLD(1));

    /* Insert/learn new entry into the MAC table  */
    VTSS_D("mach: 0x%08x, macl:  0x%08x, cfg2: 0x%08x", mach, macl, cfg2);
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_0, mach);
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_1, macl);
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_2, cfg2);
    JR2_WR(VTSS_LRN_COMMON_COMMON_ACCESS_CTRL, 
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_LEARN) |
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    /* Update VLAN management */
    VTSS_RC(jr2_vlan_management_update(vtss_state, &entry->vid_mac, entry->copy_to_cpu));

    /* Wait until MAC operation is finished */
    return jr2_mac_table_idle(vtss_state);
}

static vtss_rc jr2_mac_table_del(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac)
{
    u32 mach, macl;
    
    vtss_mach_macl_get(vid_mac, &mach, &macl);
    VTSS_D("mach: 0x%08x, macl: 0x%08x", mach, macl);
    
    /* Delete/unlearn the given MAC entry */
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_0, mach);
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_1, macl);
    JR2_WR(VTSS_LRN_COMMON_COMMON_ACCESS_CTRL, 
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_UNLEARN) |
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    /* Update VLAN management */
    VTSS_RC(jr2_vlan_management_update(vtss_state, vid_mac, FALSE));

    /* Wait until MAC operation is finished */
    return jr2_mac_table_idle(vtss_state);
}

/* Analyze the result in the MAC table */
static vtss_rc jr2_mac_table_result(vtss_state_t *vtss_state, vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32                cfg2, mach, macl, addr, type;
    vtss_vstax_upsid_t my_upsid, upsid;
 
    JR2_RD(VTSS_LRN_COMMON_MAC_ACCESS_CFG_2, &cfg2);
    /* Check if entry is valid */
    if (!(cfg2 & VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_VLD)) {
        VTSS_D("not valid");
        return VTSS_RC_ERROR;
    }
    JR2_RD(VTSS_LRN_COMMON_MAC_ACCESS_CFG_0, &mach);
    JR2_RD(VTSS_LRN_COMMON_MAC_ACCESS_CFG_1, &macl);
    VTSS_D("mach: 0x%08x, macl: 0x%08x, cfg2: 0x%08x", mach, macl, cfg2);

    /* Extract fields from Jaguar registers */
    VTSS_MEMSET(entry, 0, sizeof(*entry));
    entry->aged        = VTSS_BOOL(VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_FLAG(cfg2));
    entry->copy_to_cpu = 0;
    entry->copy_to_cpu_smac = VTSS_BOOL(cfg2 & VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_COPY);
    entry->cpu_queue   = VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_QU(cfg2);
    entry->locked      = VTSS_BOOL(cfg2 & VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_LOCKED);
    addr               = VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(cfg2);
    type               = VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(cfg2);
    entry->vid_mac.vid = ((mach>>16) & 0xfff);
    entry->vid_mac.mac.addr[0] = ((mach>>8)  & 0xff);
    entry->vid_mac.mac.addr[1] = ((mach>>0)  & 0xff);
    entry->vid_mac.mac.addr[2] = ((macl>>24) & 0xff);
    entry->vid_mac.mac.addr[3] = ((macl>>16) & 0xff);
    entry->vid_mac.mac.addr[4] = ((macl>>8)  & 0xff);
    entry->vid_mac.mac.addr[5] = ((macl>>0)  & 0xff);

    switch (type) {
    case MAC_ENTRY_ADDR_TYPE_UPSID_PN:
        my_upsid = 0;
        upsid = ((addr >> 5) & 0x1f);
        *pgid = vtss_jr2_vtss_pgid(vtss_state, (addr & 0x1f) + (upsid == (my_upsid + 1) ? 32 : 0));
        break;
    case MAC_ENTRY_ADDR_TYPE_MC_IDX:
        /* Multicast PGID */
        *pgid = vtss_jr2_vtss_pgid(vtss_state, addr + VTSS_CHIP_PORTS);
        break;
    default:
        VTSS_E("unsupported addr type: %u", type);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_mac_table_get(vtss_state_t *vtss_state, vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32 mach, macl;

    vtss_mach_macl_get(&entry->vid_mac, &mach, &macl);
    VTSS_D("address 0x%08x%08x", mach, macl);
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_0, mach);
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_1, macl);

    /* Do a lookup */
    JR2_WR(VTSS_LRN_COMMON_COMMON_ACCESS_CTRL, 
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_LOOKUP) |
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    VTSS_RC(jr2_mac_table_idle(vtss_state));

    return jr2_mac_table_result(vtss_state, entry, pgid);
}

static vtss_rc jr2_mac_table_get_next(vtss_state_t *vtss_state, vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32               mach, macl;
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[VTSS_PGID_NONE];

    /* Clear PGID entry for IPMC/GLAG entries */
    VTSS_MEMSET(pgid_entry, 0, sizeof(*pgid_entry));

    vtss_mach_macl_get(&entry->vid_mac, &mach, &macl);
    VTSS_D("address 0x%08x%08x", mach, macl);

    /* Ensure that no filtering is active */
    JR2_WR(VTSS_LRN_COMMON_SCAN_NEXT_CFG, 
           VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_UNTIL_FOUND_ENA(1));
    /* Static entries are left out due to a bug */

    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_0, mach);
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_1, macl);

    /* Do a get next lookup */
    JR2_WR(VTSS_LRN_COMMON_COMMON_ACCESS_CTRL, 
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_FIND_SMALLEST) |
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    VTSS_RC(jr2_mac_table_idle(vtss_state));

    return jr2_mac_table_result(vtss_state, entry, pgid);
}

static vtss_rc jr2_mac_table_age_time_set(vtss_state_t *vtss_state)
{
    u32 time, units;

    /* Scan two times per age time */
    time = vtss_state->l2.mac_age_time;
    if (time <= 1) {
        units = 0; /* 0: disable ageing */
        time = 0; 
    } else {
        units = 3;                   /* 3: unit = 1 s. */
        time = (time/2);             /* age between T/2 and T */
        time = MIN(time, 0xfffffff); /* period_val is 28 bits wide */
    }
    VTSS_D("time %d, units %d", time, units);

    /* Stop aging and set counters to a low value */
    JR2_WR(VTSS_LRN_COMMON_AUTOAGE_CFG(0), 
           VTSS_F_LRN_COMMON_AUTOAGE_CFG_UNIT_SIZE(1)  |
           VTSS_F_LRN_COMMON_AUTOAGE_CFG_PERIOD_VAL(1));
    JR2_WRM(VTSS_LRN_COMMON_AUTOAGE_CFG_1, 
            VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_FORCE_IDLE_ENA(1) |
            VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT(1),
            VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_FORCE_IDLE_ENA |
            VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT);
    
    JR2_WR(VTSS_LRN_COMMON_AUTOAGE_CFG(0), 
           VTSS_F_LRN_COMMON_AUTOAGE_CFG_UNIT_SIZE(units)  |
           VTSS_F_LRN_COMMON_AUTOAGE_CFG_PERIOD_VAL(time));
    JR2_WRM(VTSS_LRN_COMMON_AUTOAGE_CFG_1, 
            VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_FORCE_IDLE_ENA(!units) |
            VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT(1),
            VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_FORCE_IDLE_ENA |
            VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT);
    return VTSS_RC_OK;
}

static vtss_rc jr2_mac_table_age_cmd(vtss_state_t *vtss_state,
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
            addr = ((jr2_port2upsid(vtss_state, &port) << 5) + port);
        } else {
            /* GLAG ageing */
            addr = ((pgid - vtss_state->l2.pgid_glag_dest) & 0x1f);
            addr_type = MAC_ENTRY_ADDR_TYPE_GLAG;
        }
    }

    VTSS_D("pgid_age %u, addr %u, vid_age %u, vid %u", pgid_age, addr, vid_age, vid);
    
    /* Selective aging */
    JR2_WR(VTSS_LRN_COMMON_SCAN_NEXT_CFG, 
           VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_FID_FILTER_ENA(vid_age) |
           VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_ADDR_FILTER_ENA(pgid_age) |
           VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_INTERVAL_MASK(0xf) |
           VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_REMOVE_FOUND_ENA(1) |
           VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_INC_AGE_BITS_ENA(age));
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_0, VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_0_MAC_ENTRY_FID(fid == 0 ? vid : fid));
    JR2_WR(VTSS_LRN_COMMON_MAC_ACCESS_CFG_2, 
           VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(addr) |
           VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(addr_type));

    /* Do the aging */
    JR2_WR(VTSS_LRN_COMMON_COMMON_ACCESS_CTRL, 
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(MAC_CMD_SCAN) |
           VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(1));

    /* Wait until MAC operation is finished */
    return jr2_mac_table_idle(vtss_state);
}

static vtss_rc jr2_mac_table_age(vtss_state_t *vtss_state,
                                 BOOL             pgid_age, 
                                 u32              pgid,
                                 BOOL             vid_age,
                                 const vtss_vid_t vid)
{
    return jr2_mac_table_age_cmd(vtss_state, pgid_age, pgid, vid_age, vid, 1);
}

static vtss_rc jr2_mac_table_status_get(vtss_state_t *vtss_state, vtss_mac_table_status_t *status) 
{
    VTSS_MEMSET(status, 0, sizeof(*status));

    u32 value;
    
    /* Detect port move events */
    JR2_RD(VTSS_ANA_L2_STICKY_STICKY, &value);
    value &= (VTSS_M_ANA_L2_STICKY_STICKY_LOCAL_TO_REMOTE_PORTMOVE_STICKY  |
              VTSS_M_ANA_L2_STICKY_STICKY_REMOTE_TO_LOCAL_PORTMOVE_STICKY  |
              VTSS_M_ANA_L2_STICKY_STICKY_REMOTE_TO_REMOTE_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_STICKY_GLOBAL_TO_GLOBAL_PORTMOVE_STICKY |
              VTSS_M_ANA_L2_STICKY_STICKY_GLOBAL_TO_LOCAL_PORTMOVE_STICKY  |
              VTSS_M_ANA_L2_STICKY_STICKY_LOCAL_TO_GLOBAL_PORTMOVE_STICKY  |
              VTSS_M_ANA_L2_STICKY_STICKY_LOCAL_TO_LOCAL_PORTMOVE_STICKY);
    JR2_WR(VTSS_ANA_L2_STICKY_STICKY, value);
    if (value)
        status->moved = 1;

    /* Read and clear sticky register */
    JR2_RD(VTSS_LRN_COMMON_EVENT_STICKY, &value);
    JR2_WR(VTSS_LRN_COMMON_EVENT_STICKY, value & 
           (VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY |
            VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_INSERT_STICKY |
            VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_REMOVE_STICKY |
            VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_AGED_STICKY));
    
    /* Detect learn events */
    if (value & VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_INSERT_STICKY)
        status->learned = 1;

    /* Detect replace events */
    if (value & VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY)
        status->replaced = 1;

    /* Detect age events (both aged and removed event is used */
    if (value & (VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_AGED_STICKY |
                 VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_REMOVE_STICKY))
        status->aged = 1;

    return VTSS_RC_OK;
}

static vtss_rc jr2_learn_port_mode_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_learn_mode_t *mode = &vtss_state->l2.learn_mode[port_no];
    u64               pmask = vtss_jr2_pmask(VTSS_CHIP_PORT(port_no)), pmask_zero = 0;
    vtss_port_no_t    port_iter;
    u32               cnt = 0;

    JR2_WRM_PMASK(VTSS_ANA_L2_COMMON_LRN_SECUR_CFG,        (mode->discard   ? pmask : pmask_zero), pmask); // Drop unknown smac
    JR2_WRM_PMASK(VTSS_ANA_L2_COMMON_LRN_SECUR_LOCKED_CFG,                    pmask,               pmask); // Always drop move of locked entries
    JR2_WRM_PMASK(VTSS_ANA_L2_COMMON_AUTO_LRN_CFG,         (mode->automatic ? pmask : pmask_zero), pmask); // Enable H/W-based learning
    JR2_WRM_PMASK(VTSS_ANA_L2_COMMON_LRN_COPY_CFG,         (mode->cpu       ? pmask : pmask_zero), pmask); // Copy incoming learn frames to CPU

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

    JR2_WRM(VTSS_ANA_L2_COMMON_LRN_CFG,
            VTSS_F_ANA_L2_COMMON_LRN_CFG_LOCKED_PORTMOVE_COPY_ENA(cnt < 2 ? 0 : 1),
            VTSS_M_ANA_L2_COMMON_LRN_CFG_LOCKED_PORTMOVE_COPY_ENA);

    /* If automatic ageing is disabled, flush entries previously learned on port */
    return (mode->automatic ? VTSS_RC_OK : jr2_mac_table_age_cmd(vtss_state, 1, port_no, 0, 0, 0));
}

/* ================================================================= *
 *  Layer 2 - VLAN 
 * ================================================================= */

static vtss_rc jr2_vlan_conf_set(vtss_state_t *vtss_state)
{
    u32 etype = vtss_state->l2.vlan_conf.s_etype;

    /* Configure alternative S-tag Ethernet Type */
    JR2_WR(VTSS_ANA_CL_COMMON_VLAN_STAG_CFG(0), VTSS_F_ANA_CL_COMMON_VLAN_STAG_CFG_STAG_ETYPE_VAL(etype));
    JR2_WR(VTSS_REW_COMMON_TPID_CFG(0), VTSS_F_REW_COMMON_TPID_CFG_TPID_VAL(etype));
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_vlan_update(vtss_state_t *vtss_state, vtss_vid_t vid)
{
    vtss_vlan_entry_t *e = &vtss_state->l2.vlan_table[vid];
    u32               value, mask, vmid_cfg, vlan_idx;

    value = (VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_MSTP_PTR(e->msti) |
             VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_FID(e->fid == 0 ? vid : e->fid) |
             VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_IGR_FILTER_ENA(e->flags & VLAN_FLAGS_FILTER ? 1 : 0) |
             VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_FLOOD_DIS(e->flags & VLAN_FLAGS_FLOOD ? 0 : 1) |
             VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_LRN_DIS(e->flags & VLAN_FLAGS_LEARN ? 0 : 1) |
             VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_RLEG_ENA(e->rl_enable) |
             VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_PRIVATE_ENA(e->flags & VLAN_FLAGS_ISOLATED ? 1 : 0) |
             VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_MIRROR_ENA(e->flags & VLAN_FLAGS_MIRROR ? 1 : 0));
    mask = (VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_MSTP_PTR |
            VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_FID |
            VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_IGR_FILTER_ENA |
            VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_FLOOD_DIS |
            VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_LRN_DIS |
            VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_RLEG_ENA |
            VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_PRIVATE_ENA |
            VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_MIRROR_ENA);
    vmid_cfg = VTSS_F_ANA_L3_VLAN_VMID_CFG_VMID(e->rl_id);

    /* Setup VID entry */
    JR2_WRM(VTSS_ANA_L3_VLAN_VLAN_CFG(vid), value, mask);
    JR2_WR(VTSS_ANA_L3_VLAN_VMID_CFG(vid), vmid_cfg);

    if (e->vsi_enable && e->vsi != NULL) {
        /* Setup VSI entry */
        vlan_idx = (VTSS_VIDS + e->vsi->vsi);
        JR2_WRM(VTSS_ANA_L3_VLAN_VLAN_CFG(vlan_idx), value, mask);
        JR2_WR(VTSS_ANA_L3_VLAN_VMID_CFG(vlan_idx), vmid_cfg);
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_vlan_mask_apply(vtss_state_t *vtss_state, vtss_vid_t vid, u64 pmask)
{
    vtss_vlan_entry_t *vlan_entry = &vtss_state->l2.vlan_table[vid];
    u32               vlan_idx;

    if (vlan_entry->vsi_enable && vlan_entry->vsi != NULL) {
        /* Setup VSI port mask */
        vlan_idx = (VTSS_VIDS + vlan_entry->vsi->vsi);
        JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, vlan_idx, pmask);
        if (vlan_entry->vsi_vlan_forward_disable) {
            pmask = 0; /* Avoid normal VLAN forwarding when VSI is used */
        }
    }
 
    /* Setup VID port mask */
    JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, vid, pmask);

    /* Setup other VLAN fields */
    return vtss_jr2_vlan_update(vtss_state, vid);
}

static vtss_rc jr2_vlan_mask_update(vtss_state_t *vtss_state,
                                    vtss_vid_t   vid, 
                                    BOOL         member[VTSS_PORT_ARRAY_SIZE]) 
{
    u64 pmask;

    /* Update VLAN port mask */
    pmask = vtss_jr2_port_mask(vtss_state, member);
    return jr2_vlan_mask_apply(vtss_state, vid, pmask);
}

vtss_rc vtss_jr2_vlan_port_conf_apply(vtss_state_t          *vtss_state,
                                      u32                   port, 
                                      vtss_vlan_port_conf_t *conf,
                                      BOOL                  l3_dt)
{
    BOOL       aware = 1, c_port = 0, s_port = 0, s_custom_port = 0;
    vtss_vid_t uvid = conf->untagged_vid;
    u32        value = 0, tpid = 0, aware_dis;
    u64        pmask;

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
    JR2_WRM(VTSS_ANA_CL_PORT_VLAN_CTRL(port),
            VTSS_F_ANA_CL_PORT_VLAN_CTRL_PORT_VID(conf->pvid) | 
            VTSS_F_ANA_CL_PORT_VLAN_CTRL_VLAN_POP_CNT(aware ? 1 : 0) |
            VTSS_F_ANA_CL_PORT_VLAN_CTRL_VLAN_AWARE_ENA(aware),
            VTSS_M_ANA_CL_PORT_VLAN_CTRL_PORT_VID |
            VTSS_M_ANA_CL_PORT_VLAN_CTRL_VLAN_POP_CNT |
            VTSS_M_ANA_CL_PORT_VLAN_CTRL_VLAN_AWARE_ENA);

    aware_dis = 0x7fff;
    if (aware) {
        aware_dis -= (1 << tpid);
        if (l3_dt) {
            aware_dis -= (1 << (tpid + 5));
        }
    }
    JR2_WR(VTSS_ANA_CL_PORT_VLAN_TPID_CTRL(port),
           VTSS_F_ANA_CL_PORT_VLAN_TPID_CTRL_BASIC_TPID_AWARE_DIS(aware_dis) |
           VTSS_F_ANA_CL_PORT_VLAN_TPID_CTRL_RT_TAG_CTRL(l3_dt ? 7 : 3));

    /* Drop Configuration based on port type and frame type */
    if (conf->frame_type == VTSS_VLAN_FRAME_TAGGED && aware) {
        /* Discard untagged and priority-tagged if aware and tagged-only allowed */
        value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_TAG_REQUIRED_ENA;
        value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_PRIO_CTAG_DIS;
        value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_PRIO_STAG_DIS;
        value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_PRIO_CUST1_STAG_DIS;
        if (!c_port) {
            /* Discard C-tagged unless C-port */
            value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_CTAG_DIS;
        }
        if (!s_port) {
            /* Discard S-tagged unless S-port */
            value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_STAG_DIS;
        }
        if (!s_custom_port) {
            /* Discard S-custom-tagged unless S-custom port */
            value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_CUST1_STAG_DIS;
        }
    }

    if (conf->frame_type == VTSS_VLAN_FRAME_UNTAGGED) {
        if (c_port) {
            /* Discard C-tagged if C-port */
            value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_CTAG_DIS;
        }
        if (s_port) {
            /* Discard S-tagged if S-port */
            value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_STAG_DIS;
        }
        if (s_custom_port) {
            /* Discard S-custom-tagged if S-custom port */
            value |= VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_CUST1_STAG_DIS;
        }
    }

    JR2_WRM(VTSS_ANA_CL_PORT_VLAN_FILTER_CTRL(port, 0), value,
            VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_TAG_REQUIRED_ENA |
            VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_PRIO_CTAG_DIS |
            VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_PRIO_STAG_DIS |
            VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_PRIO_CUST1_STAG_DIS |
            VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_CTAG_DIS |
            VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_STAG_DIS |
            VTSS_M_ANA_CL_PORT_VLAN_FILTER_CTRL_CUST1_STAG_DIS);

    /* Ingress filtering */
    pmask = vtss_jr2_pmask(port);
    JR2_WRM_PMASK(VTSS_ANA_L3_COMMON_VLAN_FILTER_CTRL, (conf->ingress_filter ? pmask : 0ULL), pmask);

    /* Rewriter VLAN tag configuration */
    JR2_WRM(VTSS_REW_PORT_TAG_CTRL(port),
            VTSS_F_REW_PORT_TAG_CTRL_TAG_CFG(uvid == VTSS_VID_ALL ? 0 : uvid == VTSS_VID_NULL ? 2 : 1) |
            VTSS_F_REW_PORT_TAG_CTRL_TAG_TPID_CFG(tpid),
            VTSS_M_REW_PORT_TAG_CTRL_TAG_CFG |
            VTSS_M_REW_PORT_TAG_CTRL_TAG_TPID_CFG);

    JR2_WRM(VTSS_REW_PORT_PORT_VLAN_CFG(port),
            VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_VID(uvid),
            VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_VID);
            
    return VTSS_RC_OK;
}

static vtss_rc jr2_vlan_port_conf_update(vtss_state_t *vtss_state,
                                         vtss_port_no_t port_no, vtss_vlan_port_conf_t *conf)
{
    u32 port = VTSS_CHIP_PORT(port_no);

    /* Update VLAN port configuration */
    VTSS_RC(vtss_jr2_vlan_port_conf_apply(vtss_state, port, conf, vtss_state->l2.l3_dt[port_no]));

    /* Update default ES0 rule */
    VTSS_RC(vtss_jr2_vcap_port_l2_update(vtss_state, port_no));

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
static vtss_rc jr2_vlan_counters_update(vtss_state_t         *vtss_state,
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
        JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(vid, i), &lsb);
        JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT(vid, i), &msb);
        vtss_cmn_counter_40_update(lsb, msb, &chip_counter->bytes, clear);

        /* Update frame counter */
        JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(vid, i + 3), &lsb);
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

static vtss_rc jr2_vlan_counters_get(vtss_state_t *vtss_state, vtss_vid_t vid, vtss_vlan_counters_t *counters)
{
    return jr2_vlan_counters_update(vtss_state, vid, counters, FALSE);
}

static vtss_rc jr2_vlan_counters_clear(vtss_state_t *vtss_state, vtss_vid_t vid)
{
    return jr2_vlan_counters_update(vtss_state, vid, NULL, TRUE);
}
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

static vtss_rc jr2_vcl_port_conf_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_vcl_port_conf_t *conf = &vtss_state->l2.vcl_port_conf[port_no];

    VTSS_RC(vtss_cmn_vcl_port_conf_set(vtss_state, port_no));

    /* Set port key */
    return vtss_jr2_vcap_port_key_set(vtss_state, port_no, 2, conf->key_type, conf->dmac_dip, FALSE);
}

vtss_rc vtss_jr2_isdx_set(vtss_state_t *vtss_state, vtss_sdx_entry_t *sdx, u64 pmask,
                          u32 l2cp_idx, u32 voe_idx, u32 mip_idx, BOOL vsi_enable, u32 vsi, BOOL independent_mel)
{
    u32 isdx = sdx->sdx;

    JR2_WRX_PMASK(VTSS_ANA_L2_ISDX_PORT_MASK_CFG, isdx, pmask);

    /* Use ISDX key in ES0 */
    JR2_WR(VTSS_ANA_L2_ISDX_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_ISDX_SERVICE_CTRL_ES0_ISDX_KEY_ENA(0));

    /* DLB/ISDX mappings */
    VTSS_RC(vtss_jr2_isdx_update(vtss_state, sdx));

    /* L2CP IDX */
    JR2_WR(VTSS_ANA_CL_IPT_ISDX_CFG(isdx), VTSS_F_ANA_CL_IPT_ISDX_CFG_L2CP_IDX(l2cp_idx));

    /* Independent_mel */
    JR2_WRM(VTSS_ANA_CL_IPT_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_IPT_OAM_MEP_CFG_INDEPENDENT_MEL_ENA(independent_mel),
            VTSS_M_ANA_CL_IPT_OAM_MEP_CFG_INDEPENDENT_MEL_ENA);

    /* VOE reference */
    JR2_WRM(VTSS_ANA_CL_IPT_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_IPT_OAM_MEP_CFG_MEP_IDX_ENA((voe_idx == VTSS_VOE_IDX_NONE) || (voe_idx >= VTSS_PORT_VOE_BASE_IDX) ? 0 : 1),    /* Do not point to a Port VOE */
            VTSS_M_ANA_CL_IPT_OAM_MEP_CFG_MEP_IDX_ENA);

    JR2_WRM(VTSS_ANA_CL_IPT_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_IPT_OAM_MEP_CFG_MEP_IDX((voe_idx == VTSS_VOE_IDX_NONE) || (voe_idx >= VTSS_PORT_VOE_BASE_IDX) ? 0 : voe_idx),
            VTSS_M_ANA_CL_IPT_OAM_MEP_CFG_MEP_IDX);

    /* MIP reference */
    JR2_WRM(VTSS_ANA_CL_IPT_ISDX_CFG(isdx),
            VTSS_F_ANA_CL_IPT_ISDX_CFG_MIP_IDX(mip_idx == VTSS_VOI_IDX_NONE ? 0 : mip_idx),
            VTSS_M_ANA_CL_IPT_ISDX_CFG_MIP_IDX);

    /* VSI */
    JR2_WR(VTSS_ANA_CL_IPT_VSI_CFG(isdx),
        VTSS_F_ANA_CL_IPT_VSI_CFG_VSI_ENA(vsi_enable) |
        VTSS_F_ANA_CL_IPT_VSI_CFG_VSI_VAL(vsi));
    return VTSS_RC_OK;
}

static vtss_rc jr2_iflow_conf_set(vtss_state_t *vtss_state, const vtss_iflow_id_t id)
{
    vtss_sdx_entry_t *sdx = vtss_iflow_lookup(vtss_state, id);
    u64              pmask = 0xffffffffffffffff;

    if (sdx == NULL) {
        return VTSS_RC_ERROR;
    }

    return vtss_jr2_isdx_set(vtss_state, sdx, pmask, 0, sdx->conf.voe_idx, vtss_j2_voi_idx_to_mip_idx(sdx->conf.voi_idx), 0, 0,
                             (sdx->conf.voe_idx == VTSS_VOE_IDX_NONE) ? TRUE : FALSE);    /* Independent MEL when no pointer to active VOE */
}

static vtss_rc jr2_icnt_get(vtss_state_t *vtss_state, u16 idx, vtss_ingress_counters_t *counters)
{
    vtss_stat_idx_t     sidx;
    vtss_evc_counters_t cnt;

    VTSS_MEMSET(&cnt, 0, sizeof(cnt));
    sidx.idx = idx;
    sidx.edx = 0;
    VTSS_RC(vtss_jr2_sdx_counters_update(vtss_state, &sidx, &cnt, counters == NULL));

    if (counters != NULL) {
        counters->rx_green = cnt.rx_green;
        counters->rx_yellow = cnt.rx_yellow;
        counters->rx_red = cnt.rx_red;
        counters->rx_discard = cnt.rx_discard;
        counters->tx_discard = cnt.tx_discard;
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_ecnt_get(vtss_state_t *vtss_state, u16 idx, vtss_egress_counters_t *counters)
{
    vtss_stat_idx_t     sidx;
    vtss_evc_counters_t cnt;

    VTSS_MEMSET(&cnt, 0, sizeof(cnt));
    sidx.idx = 0;
    sidx.edx = idx;
    VTSS_RC(vtss_jr2_sdx_counters_update(vtss_state, &sidx, &cnt, counters == NULL));

    if (counters != NULL) {
        counters->tx_green = cnt.tx_green;
        counters->tx_yellow = cnt.tx_yellow;
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_evc_policer_update(vtss_state_t *vtss_state, u16 idx)
{
    return vtss_jr2_policer_conf_set(vtss_state, idx, &vtss_state->l2.pol_conf[idx]);
}

static vtss_rc jr2_evc_counters_update(vtss_state_t *vtss_state,
                                       vtss_stat_idx_t *stat_idx,
                                       BOOL clear)
{
    return vtss_jr2_sdx_counters_update(vtss_state, stat_idx, NULL, clear);
}


/* ================================================================= *
 *  Layer 2 - PVLAN / Isolated ports
 * ================================================================= */

static vtss_rc jr2_isolated_port_members_set(vtss_state_t *vtss_state)
{
    u64 pmask = vtss_jr2_port_mask(vtss_state, vtss_state->l2.isolated_port);

    JR2_WR_PMASK(VTSS_ANA_L3_COMMON_VLAN_ISOLATED_CFG, pmask);
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - IP Multicast
 * ================================================================= */

static vtss_rc jr2_flood_conf_set(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    BOOL           member[VTSS_PORT_ARRAY_SIZE];

    /* Unicast flood mask */
    VTSS_RC(jr2_pgid_update(vtss_state, PGID_UC_FLOOD, vtss_state->l2.uc_flood));

    /* Multicast flood mask */
    VTSS_RC(jr2_pgid_update(vtss_state, PGID_MC_FLOOD, vtss_state->l2.mc_flood));

    /* IPv4 multicast control flood mask */
    VTSS_RC(jr2_pgid_update(vtss_state, PGID_IPV4_MC_CTRL, vtss_state->l2.mc_flood));

    /* IPv4 multicast data flood mask */
    VTSS_RC(jr2_pgid_update(vtss_state, PGID_IPV4_MC_DATA, vtss_state->l2.ipv4_mc_flood));

    /* IPv6 multicast control flood mask */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
        member[port_no] = (vtss_state->l2.ipv6_mc_scope ? vtss_state->l2.ipv6_mc_flood[port_no] : 
                           vtss_state->l2.mc_flood[port_no]);
    VTSS_RC(jr2_pgid_update(vtss_state, PGID_IPV6_MC_CTRL, member));
    
    /* Setup IPv6 MC data flood mask */
    return jr2_pgid_update(vtss_state, PGID_IPV6_MC_DATA, vtss_state->l2.ipv6_mc_flood);
}

/* ================================================================= *
 *  Layer 2 - Mirror
 * ================================================================= */

/* Find first port enabled in mask */
static u32 jr2_first_port(u64 pmask)
{
    u64 i, port = 0;

    for (i = 0; i < 64; i++) {
        if (pmask & vtss_jr2_pmask(i)) {
            port = i;
            break;
        }
    }
    return port;
}

/* Setup mirroring for chip */
static vtss_rc jr2_mirror_conf_set(vtss_state_t *vtss_state)
{
    vtss_mirror_conf_t *conf = &vtss_state->l2.mirror_conf;
    vtss_port_no_t     port_no;
    u32                probe, port = 0, dir, vlan_mode, tx_port, rx_cpu, cpu_set;
    u64                pmask = 0, pmask_probe;
    BOOL               member[VTSS_PORTS];

    /* Mirror port and mask */
    if (conf->port_no != VTSS_PORT_NO_NONE && vtss_state->l2.tx_forward_aggr[conf->port_no]) {
        port = VTSS_CHIP_PORT(conf->port_no);
        pmask |= vtss_jr2_pmask(port);
    }

    /* Setup all probes */
    for (probe = JR2_MIRROR_PROBE_RX; probe <= JR2_MIRROR_PROBE_VLAN; probe++) {
        dir = 2;
        vlan_mode = 0;
        tx_port = 0;
        rx_cpu = 0;
        cpu_set = 0;
        pmask_probe = 0;
        if (probe == JR2_MIRROR_PROBE_RX) {
            /* Ingress probe */
            if (pmask) {
                pmask_probe = vtss_jr2_port_mask(vtss_state, vtss_state->l2.mirror_ingress);
                if (vtss_state->l2.mirror_cpu_ingress) {
                    rx_cpu = 0x3; /* Enable Rx mirror from both CPU ports */
                }
            }
        } else if (probe == JR2_MIRROR_PROBE_TX) {
            /* Egress probe */
            dir = 1;
            if (pmask) {
                pmask_probe = vtss_jr2_port_mask(vtss_state, vtss_state->l2.mirror_egress);
                tx_port = jr2_first_port(pmask_probe); /* The first egress port is used in the rewriter */
                if (vtss_state->l2.mirror_cpu_egress) {
                    cpu_set = 0xff;
                }
            }
        } else {
            /* VLAN probe */
            vlan_mode = 1;
            if (pmask) {
                for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                    member[port_no] = 1;
                }
                pmask_probe = vtss_jr2_port_mask(vtss_state, member);
            }
        }

        /* QFWD frame copy */
        JR2_WR(VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(QFWD_FRAME_COPY_CFG_MIRROR_PROBE(probe)),
               VTSS_F_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL(port));

        /* ANA_AC probe */
        JR2_WR(VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG(probe),
               VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_RX_CPU_AND_VD(rx_cpu) |
               VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_CPU_SET(cpu_set) |
               VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_VLAN_MODE(vlan_mode) |
               VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_DIRECTION(dir));
        JR2_WRX_PMASK(VTSS_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG, probe, pmask_probe);

        /* REW probe */
        JR2_WR(VTSS_REW_COMMON_MIRROR_TAG_A_CFG(probe),
               VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_PCP_SEL(1) |
               VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_PCP_VAL(conf->pcp) |
               VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_DEI_VAL(conf->dei) |
               VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_VID_VAL(conf->vid) |
               VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL(
                   conf->tag == VTSS_MIRROR_TAG_S ? 1 : conf->tag == VTSS_MIRROR_TAG_S_CUSTOM ? 2 : 0));
        JR2_WR(VTSS_REW_COMMON_MIRROR_PROBE_CFG(probe),
               VTSS_F_REW_COMMON_MIRROR_PROBE_CFG_MIRROR_TX_PORT(tx_port) |
               VTSS_F_REW_COMMON_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG(conf->tag == VTSS_MIRROR_TAG_NONE ? 0 : 1));
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_ip_mc_update(vtss_state_t *vtss_state,
                                vtss_ipmc_data_t *ipmc, vtss_ipmc_cmd_t cmd)
{
    vtss_vcap_obj_t       *obj = &vtss_state->vcap.is2.obj;
    int                   user = (ipmc->src.ssm ? VTSS_IS2_USER_SSM : VTSS_IS2_USER_ASM);
    vtss_vcap_key_size_t  key_size = (ipmc->ipv6 ? VTSS_VCAP_KEY_SIZE_HALF : VTSS_VCAP_KEY_SIZE_QUARTER);
    vtss_res_chg_t        res;
    vtss_vcap_data_t      data;
    vtss_is2_entry_t      entry;
    vtss_ace_t            *ace = &entry.ace;
    vtss_ace_frame_ipv4_t *ipv4 = &ace->frame.ipv4;
    vtss_ace_frame_ipv6_t *ipv6 = &ace->frame.ipv6;
    vtss_port_no_t        port_no;
    int                   i;

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
    ace->vlan.vid.value = ipmc->src.vid;
    ace->vlan.vid.mask = 0xfff;
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
    ace->action.learn = TRUE;
    ace->action.port_action = VTSS_ACL_PORT_ACTION_PGID;
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        ace->action.port_list[port_no] = VTSS_PORT_BF_GET(ipmc->dst.member, port_no);
    }
    return vtss_vcap_add(vtss_state, obj, user, ipmc->dst.id, ipmc->id_next, &data, 0);
}

static vtss_rc jr2_mirror_port_set(vtss_state_t *vtss_state)
{
    /* Update all VLANs */
    VTSS_RC(vtss_cmn_vlan_update_all(vtss_state));

    return jr2_mirror_conf_set(vtss_state);
}

static vtss_rc jr2_mirror_ingress_set(vtss_state_t *vtss_state)
{
    return jr2_mirror_conf_set(vtss_state);
}

static vtss_rc jr2_mirror_egress_set(vtss_state_t *vtss_state)
{
    return jr2_mirror_conf_set(vtss_state);
}

/* CPU Ingress ports subjects for mirroring */
static vtss_rc jr2_mirror_cpu_ingress_set(vtss_state_t *vtss_state)
{
    return jr2_mirror_conf_set(vtss_state);
}

/* CPU Egress ports subjects for mirroring */
static vtss_rc jr2_mirror_cpu_egress_set(vtss_state_t *vtss_state)
{
    return jr2_mirror_conf_set(vtss_state);
}

static vtss_rc jr2_aggr_table_write(vtss_state_t *vtss_state,
                                    u32 ac, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    u64 pmask = vtss_jr2_port_mask(vtss_state, member);

    JR2_WRX_PMASK(VTSS_ANA_AC_AGGR_AGGR_CFG, ac, pmask);

    /* Setup mirroring when the first aggregation mask is setup */
    return (ac == 0 ? jr2_mirror_conf_set(vtss_state) : VTSS_RC_OK);
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

static u32 jr2_sflow_hw_rate(const u32 desired_sw_rate, u32 *const realizable_sw_rate)
{
    u32 hw_rate         = desired_sw_rate ? MAX(VTSS_ROUNDING_DIVISION(JR2_SFLOW_MAX_SAMPLE_RATE, desired_sw_rate), JR2_SFLOW_MIN_SAMPLE_RATE) : 0;
    *realizable_sw_rate = hw_rate         ?     VTSS_ROUNDING_DIVISION(JR2_SFLOW_MAX_SAMPLE_RATE, hw_rate) : 0;
    return hw_rate;
}

static vtss_rc jr2_sflow_sampling_rate_convert(struct vtss_state_s *const state, const BOOL power2, const u32 rate_in, u32 *const rate_out)
{
    u32 modified_rate_in;
    // Could happen that two threads call this function simultaneously at boot, but we take the risk.
    // Once sflow_max_power_of_two has been computed, it's no longer a problem with simultaneous access.
    u32 sflow_max_power_of_two = state->l2.sflow_max_power_of_two;

    if (sflow_max_power_of_two == 0) {
        sflow_max_power_of_two = next_power_of_two(JR2_SFLOW_MAX_SAMPLE_RATE);
        if ((JR2_SFLOW_MAX_SAMPLE_RATE & sflow_max_power_of_two) == 0) {
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

    (void)jr2_sflow_hw_rate(modified_rate_in, rate_out);
    return VTSS_RC_OK;
}

// Note that Jaguar2 has a sFlow-related bug, ref bug#12246
static vtss_rc jr2_sflow_port_conf_set(vtss_state_t *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const vtss_sflow_port_conf_t *const new_conf)
{
#define JR2_SFLOW_ENABLED(_conf_) ((_conf_)->sampling_rate > 0 && (_conf_)->type != VTSS_SFLOW_TYPE_NONE)
    vtss_sflow_port_conf_t *cur_conf = &vtss_state->l2.sflow_conf[port_no];
    u32                    hw_rate;
    BOOL                   globally_enable;

    globally_enable = vtss_state->l2.sflow_ena_cnt > 0;

    if (JR2_SFLOW_ENABLED(new_conf) && !JR2_SFLOW_ENABLED(cur_conf)) {
        if (vtss_state->l2.sflow_ena_cnt == VTSS_PORTS) {
            VTSS_E("sFlow enable counter out of sync");
        }
        if (vtss_state->l2.sflow_ena_cnt++ == 0) {
            globally_enable = TRUE;
        }
    } else if (!JR2_SFLOW_ENABLED(new_conf) && JR2_SFLOW_ENABLED(cur_conf)) {
        if (vtss_state->l2.sflow_ena_cnt == 0) {
            VTSS_E("sFlow enable counter out of sync");
        } else  if (--vtss_state->l2.sflow_ena_cnt == 0) {
            globally_enable = FALSE;
        }
    }

    *cur_conf = *new_conf;

    JR2_WRM(VTSS_ANA_AC_PS_COMMON_PS_COMMON_CFG, 
            VTSS_F_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA(globally_enable),
            VTSS_M_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA);

    JR2_WRM(VTSS_ANA_AC_PS_COMMON_PS_COMMON_CFG, 
            VTSS_F_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_SMPL_ID_IN_STAMP_ENA(globally_enable),
            VTSS_M_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_SMPL_ID_IN_STAMP_ENA);

    // Compute the actual sampling rate given the user input.
    // If the user requires power-of-two sampling rates, he is supposed to have provided
    // such a sampling rate in #new_conf.
    // We must ensure that power-of-two input sampling rates gives the same power-of-two
    // output sampling rate.
    hw_rate = jr2_sflow_hw_rate(new_conf->sampling_rate, &cur_conf->sampling_rate);

    JR2_WRM(VTSS_ANA_AC_SFLOW_SFLOW_CTRL(VTSS_CHIP_PORT(port_no)),
            VTSS_F_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_DIR_SEL(
                new_conf->type == VTSS_SFLOW_TYPE_NONE ? 0 :
                new_conf->type == VTSS_SFLOW_TYPE_RX   ? 1 :
                new_conf->type == VTSS_SFLOW_TYPE_TX   ? 2 : 3) |
            VTSS_F_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_SAMPLE_RATE(hw_rate),
            VTSS_M_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_DIR_SEL |
            VTSS_M_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_SAMPLE_RATE);
            
    return VTSS_RC_OK;
#undef JR_SFLOW_ENABLED
}

/* - Debug print --------------------------------------------------- */

static void jr2_debug_pmask_header(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%-34s", name == NULL ? "Port" : name);
    vtss_jr2_debug_print_port_header(vtss_state, pr, buf);

}

static void jr2_debug_pmask(const vtss_debug_printf_t pr, const char *name, u64 pmask)
{
    pr("%-34s", name);
    vtss_jr2_debug_print_pmask(pr, pmask);
}

#define JR2_DEBUG_VLAN(pr, addr, name) JR2_DEBUG_REG_NAME(pr, ANA_L3, COMMON_VLAN_##addr, "VLAN_"name);

static vtss_rc jr2_debug_vlan_entry(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    vtss_vid_t vid,
                                    vtss_vid_t vlan_idx,
                                    BOOL header)
{
    u32  value;
    u64  pmask;
    char buf[64];

    JR2_RDX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, vlan_idx, &pmask);
    JR2_RD(VTSS_ANA_L3_VLAN_VLAN_CFG(vlan_idx), &value);

    if (header) {
        jr2_debug_pmask_header(vtss_state, pr, "VID  IDX   FID  MSTI  L/F/M/F/P");
    }
    VTSS_SPRINTF(buf, "%-5u%-6u%-5u%-6u%u/%u/%u/%u/%u",
            vid,
            vlan_idx,
            VTSS_X_ANA_L3_VLAN_VLAN_CFG_VLAN_FID(value),
            VTSS_X_ANA_L3_VLAN_VLAN_CFG_VLAN_MSTP_PTR(value),
            VTSS_X_ANA_L3_VLAN_VLAN_CFG_VLAN_LRN_DIS(value) ? 0 : 1,
            VTSS_X_ANA_L3_VLAN_VLAN_CFG_VLAN_FLOOD_DIS(value) ? 0 : 1,
            VTSS_X_ANA_L3_VLAN_VLAN_CFG_VLAN_MIRROR_ENA(value),
            VTSS_X_ANA_L3_VLAN_VLAN_CFG_VLAN_IGR_FILTER_ENA(value),
            VTSS_X_ANA_L3_VLAN_VLAN_CFG_VLAN_PRIVATE_ENA(value));
    jr2_debug_pmask(pr, buf, pmask);

    return VTSS_RC_OK;
}

static void jr2_debug_vlan_cfg(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               vtss_vid_t vid,
                               BOOL header)
{
    if (header) {
        vtss_jr2_debug_reg_header(pr, "ANA_L3");
    }
    vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_L3_VLAN_VLAN_CFG(vid), vid, "VLAN_CFG");
}

static vtss_rc jr2_debug_vlan(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455} */ // Due to VTSS_EXIT_ENTER
    vtss_port_no_t    port_no;
    vtss_vid_t        vid;
    vtss_vlan_entry_t *vlan_entry;
    BOOL              header = 1;
    u32               port;
    u64               pmask = 0;
    char              buf[32];
    
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0)
            continue;
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_jr2_debug_reg_header(pr, buf);
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_PORT_VLAN_FILTER_CTRL(port, 0), port, "ANA:VLAN_FILTER_CTRL");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_PORT_VLAN_CTRL(port),      port, "ANA:VLAN_CTRL");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_PORT_VLAN_TPID_CTRL(port), port, "ANA:TPID_CTRL");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_REW_PORT_PORT_VLAN_CFG(port),     port, "REW:PORT_VLAN_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_REW_PORT_TAG_CTRL(port),          port, "REW:TAG_CTRL");
        pr("\n");
    }
        
    vtss_jr2_debug_reg_header(pr, "VLAN COMMON");
    JR2_DEBUG_VLAN(pr, CTRL, "CTRL");
    JR2_DEBUG_REG_NAME(pr, ANA_CL, COMMON_VLAN_STAG_CFG(0), "VLAN_STAG_CFG(0)");
    JR2_DEBUG_REG_NAME(pr, ANA_CL, COMMON_VLAN_STAG_CFG(1), "VLAN_STAG_CFG(1)");
    JR2_DEBUG_REG_NAME(pr, ANA_CL, COMMON_VLAN_STAG_CFG(2), "VLAN_STAG_CFG(2)");
    pr("\n");

    jr2_debug_pmask_header(vtss_state, pr, NULL);
    JR2_RD_PMASK(VTSS_ANA_L3_COMMON_VLAN_FILTER_CTRL, &pmask);
    jr2_debug_pmask(pr, "FILTER_CTRL", pmask);
    JR2_RD_PMASK(VTSS_ANA_L3_COMMON_VLAN_ISOLATED_CFG, &pmask);
    jr2_debug_pmask(pr, "ISOLATED_CFG", pmask);
    JR2_RD_PMASK(VTSS_ANA_L3_COMMON_VLAN_COMMUNITY_CFG, &pmask);
    jr2_debug_pmask(pr, "COMMUNITY_CFG", pmask);
    pr("\n");

    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if (info->full || (vlan_entry->flags & VLAN_FLAGS_ENABLED)) {
            VTSS_RC(jr2_debug_vlan_entry(vtss_state, pr, vid, vid, header));
            header = 0;
            if ((vlan_entry->vsi_enable) && (vlan_entry->vsi != NULL)) {
                VTSS_RC(jr2_debug_vlan_entry(vtss_state, pr, vid, VTSS_VIDS + vlan_entry->vsi->vsi, header));
            }
            /* Leave critical region briefly */
            VTSS_EXIT_ENTER();
        }
    }
    if (!header)
        pr("\n");
    
    header = 1;
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if (info->full || (vlan_entry->flags & VLAN_FLAGS_ENABLED)) {
            jr2_debug_vlan_cfg(vtss_state, pr, vid, header);
            header = 0;
            if ((vlan_entry->vsi_enable) && (vlan_entry->vsi != NULL)) {
                jr2_debug_vlan_cfg(vtss_state, pr, VTSS_VIDS + vlan_entry->vsi->vsi, header);
            }
            /* Leave critical region briefly */
            VTSS_EXIT_ENTER();
        }
    }
    if (!header)
        pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_src_table(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    u32 port;
    u64 pmask;
    char buf[32];

    vtss_debug_print_header(pr, "Source Masks");
    jr2_debug_pmask_header(vtss_state, pr, NULL);
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        JR2_RDX_PMASK(VTSS_ANA_AC_SRC_SRC_CFG, port, &pmask);
        VTSS_SPRINTF(buf, "%u", port);
        jr2_debug_pmask(pr, buf, pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_aggr_table(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    u32 ac;
    u64 pmask;
    char buf[32];

    vtss_debug_print_header(pr, "Aggregation Masks");
    jr2_debug_pmask_header(vtss_state, pr, "AC");
    for (ac = 0; ac < 16; ac++) {
        JR2_RDX_PMASK(VTSS_ANA_AC_AGGR_AGGR_CFG, ac, &pmask);
        VTSS_SPRINTF(buf, "%u", ac);
        jr2_debug_pmask(pr, buf, pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_pgid_table(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info,
                                    u32 pgid_start,
                                    u32 pgid_end,
                                    BOOL *header)
{
    u32  pgid, value, cpu_copy;
    u64  pmask;
    char buf[32];

    if (!header || *header) {
        vtss_debug_print_header(pr, "Destination Masks");
        jr2_debug_pmask_header(vtss_state, pr, "PGID            CPU  Que  Stack");

        if (header) {
            *header = 0;
        }
    }

    for (pgid = pgid_start; pgid < pgid_end; pgid++) {
        JR2_RDX_PMASK(VTSS_ANA_AC_PGID_PGID_CFG, pgid, &pmask);
        JR2_RD(VTSS_ANA_AC_PGID_PGID_MISC_CFG(pgid), &value);
        cpu_copy = VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(value);
        if (pgid > 60 && pmask == 0 && !cpu_copy && !info->full)
            continue;
        VTSS_SPRINTF(buf, "%-5u%-11s%-5u%-5u%-5u", pgid,
                pgid == PGID_UC_FLOOD ? "UC" :
                pgid == PGID_MC_FLOOD ? "MC" :
                pgid == PGID_IPV4_MC_DATA ? "IPv4 Data" :
                pgid == PGID_IPV4_MC_CTRL ? "IPv4 Ctrl" :
                pgid == PGID_IPV6_MC_DATA ? "IPv6 Data" :
                pgid == PGID_IPV6_MC_CTRL ? "IPv6 Ctrl" :
                pgid == PGID_DROP ? "DROP" : 
                pgid == PGID_FLOOD ? "FLOOD" :
                (pgid >= PGID_GLAG_START) && (pgid < PGID_GLAG_START+VTSS_GLAGS*VTSS_GLAG_PORTS) ? "GLAG" : "",
                cpu_copy,
                VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU(value),
                VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_STACK_TYPE_ENA(value));
        jr2_debug_pmask(pr, buf, pmask);
    }

    if (!header) {
        pr("\n");
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_pvlan(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    u64 pmask;

    jr2_debug_pmask_header(vtss_state, pr, NULL);
    JR2_RD_PMASK(VTSS_ANA_L3_COMMON_VLAN_ISOLATED_CFG, &pmask);
    jr2_debug_pmask(pr, "ISOLATED_CFG", pmask);
    JR2_RD_PMASK(VTSS_ANA_L3_COMMON_VLAN_COMMUNITY_CFG, &pmask);
    jr2_debug_pmask(pr, "COMMUNITY_CFG", pmask);
    pr("\n");

    return jr2_debug_src_table(vtss_state, pr, info);
}

static vtss_rc jr2_debug_mac_table(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455} */ // Due to VTSS_EXIT_ENTER
    vtss_mac_entry_t       *entry;
    vtss_mac_table_entry_t mac_entry;
    BOOL                   header = 1;
    u32                    pgid, chip_pgid, value;
    u64                    pmask;
    u8                     pgids_to_print[VTSS_BF_SIZE(VTSS_PGIDS)];

    VTSS_MEMSET(pgids_to_print, 0, sizeof(pgids_to_print));

    /* Dump MAC address table */
    VTSS_MEMSET(&mac_entry, 0, sizeof(mac_entry));

    while (jr2_mac_table_get_next(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK) {
        chip_pgid = vtss_jr2_chip_pgid(vtss_state, pgid);
        VTSS_BF_SET(pgids_to_print, chip_pgid, 1);

        JR2_RD(VTSS_ANA_AC_PGID_PGID_MISC_CFG(chip_pgid), &value);
        mac_entry.copy_to_cpu = VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(value);

        vtss_debug_print_mac_entry(pr, "Dynamic Entries (GET_NEXT)", &header, &mac_entry, chip_pgid);
        VTSS_EXIT_ENTER();
    }

    if (!header) {
        pr("\n");
    }

    /* Dump static entries not returned by the get_next function */
    header = 1;
    for (entry = vtss_state->l2.mac_list_used; entry != NULL; entry = entry->next) {
        vtss_mach_macl_set(&mac_entry.vid_mac, entry->mach, entry->macl);
        if (jr2_mac_table_get(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK) {
            chip_pgid = vtss_jr2_chip_pgid(vtss_state, pgid);
            VTSS_BF_SET(pgids_to_print, chip_pgid, 1);

            JR2_RD(VTSS_ANA_AC_PGID_PGID_MISC_CFG(chip_pgid), &value);
            mac_entry.copy_to_cpu = VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(value);

            vtss_debug_print_mac_entry(pr, "Static Entries (GET)", &header, &mac_entry, chip_pgid);
        }
        VTSS_EXIT_ENTER();
    }

    if (!header) {
        pr("\n");
    }

    header = 1;
    for (chip_pgid = 0; chip_pgid < VTSS_PGIDS; chip_pgid++) {
        if (VTSS_BF_GET(pgids_to_print, chip_pgid)) {
            VTSS_RC(jr2_debug_pgid_table(vtss_state, pr, info, chip_pgid, chip_pgid + 1, &header));
        }
    }

    if (!header) {
        pr("\n");
    }

    vtss_jr2_debug_reg_header(pr, "LRN:COMMON");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_COMMON_ACCESS_CTRL, "COMMON_ACCESS_CTRL");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_MAC_ACCESS_CFG_0,   "MAC_ACCESS_CFG_0");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_MAC_ACCESS_CFG_1,   "MAC_ACCESS_CFG_1");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_MAC_ACCESS_CFG_2,   "MAC_ACCESS_CFG_2");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_SCAN_NEXT_CFG,      "SCAN_NEXT_CFG");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_SCAN_NEXT_CFG_1,    "SCAN_NEXT_CFG_1");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_SCAN_NEXT_CNT,      "SCAN_NEXT_CNT");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_AUTOAGE_CFG(0),     "AUTOAGE_CFG(0)");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_AUTOAGE_CFG(1),     "AUTOAGE_CFG(1)");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_AUTOAGE_CFG(2),     "AUTOAGE_CFG(2)");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_AUTOAGE_CFG(3),     "AUTOAGE_CFG(3)");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_AUTOAGE_CFG_1,      "AUTOAGE_CFG_1");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_AUTOAGE_CFG_2,      "AUTOAGE_CFG_2");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_AUTO_LRN_CFG,       "AUTO_LRN_CFG");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_L2_COMMON_LRN_CFG,         "L2:LRN_CFG");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_LRN_COMMON_LATEST_POS_STATUS,  "LATEST_POS_STATUS");

    pr("\n");
    jr2_debug_pmask_header(vtss_state, pr, NULL);
    JR2_RD_PMASK(VTSS_ANA_L2_COMMON_LRN_SECUR_CFG, &pmask);
    jr2_debug_pmask(pr, "LRN_SECUR_CFG", pmask);
    JR2_RD_PMASK(VTSS_ANA_L2_COMMON_LRN_SECUR_LOCKED_CFG, &pmask);
    jr2_debug_pmask(pr, "LRN_SECUR_LOCKED_CFG", pmask);
    JR2_RD_PMASK(VTSS_ANA_L2_COMMON_AUTO_LRN_CFG, &pmask);
    jr2_debug_pmask(pr, "AUTO_LRN_CFG", pmask);
    JR2_RD_PMASK(VTSS_ANA_L2_COMMON_LRN_COPY_CFG, &pmask);
    jr2_debug_pmask(pr, "LRN_COPY_CFG", pmask);
    pr("\n");

    /* Read and clear sticky bits */
    if (info->full) {
        vtss_jr2_debug_reg_header(pr, "STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_FILTER_STICKY,         "ANA_CL:FILTER_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_VLAN_FILTER_STICKY(0), "ANA_CL:VLAN_FILTER_STICKY(0)");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_VLAN_FILTER_STICKY(1), "ANA_CL:VLAN_FILTER_STICKY(1)");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_VLAN_FILTER_STICKY(2), "ANA_CL:VLAN_FILTER_STICKY(2)");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_CLASS_STICKY,          "ANA_CL:CLASS_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_CAT_STICKY,            "ANA_CL:CAT_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_ADV_CL_MPLS_STICKY,    "ANA_CL:ADV_CL_MPLS_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_ADV_CL_STICKY,         "ANA_CL:ADV_CL_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_MIP_STICKY,            "ANA_CL:MIP_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_CL_STICKY_IP_HDR_CHK_STICKY,     "ANA_CL:IP_HDR_CHK_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_L2_STICKY_STICKY,                "ANA_L2:L2_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_AC_PS_STICKY_STICKY,             "ANA_AC:PS_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_LRN_COMMON_EVENT_STICKY,             "LRN:EVENT_STICKY");
        pr("\n");
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_vxlat(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    VTSS_RC(vtss_jr2_debug_clm_b(vtss_state, pr, info));
    VTSS_RC(vtss_jr2_debug_es0(vtss_state, pr, info));
    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_aggr(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32 port;

    vtss_jr2_debug_reg_header(pr, "Logical Ports");
    for (port = 0; port < VTSS_CHIP_PORTS_ALL; port++) {
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_PORT_PORT_ID_CFG(port), port, "PORT_ID_CFG");
    }
    pr("\n");

    VTSS_RC(jr2_debug_src_table(vtss_state, pr, info));
    VTSS_RC(jr2_debug_aggr_table(vtss_state, pr, info));
    VTSS_RC(jr2_debug_pgid_table(vtss_state, pr, info, 0, VTSS_PGID_JAGUAR_2, NULL));

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_stp(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    u32 msti;
    u64 pmask;
    char buf[16];

    jr2_debug_pmask_header(vtss_state, pr, NULL);
    for (msti = VTSS_MSTI_START; msti < VTSS_MSTI_END; msti++) {
        JR2_RDX_PMASK(VTSS_ANA_L3_MSTP_MSTP_LRN_CFG, msti, &pmask);
        VTSS_SPRINTF(buf, "MSTP_LRN_CFG_%u", msti);
        jr2_debug_pmask(pr, buf, pmask);
        JR2_RDX_PMASK(VTSS_ANA_L3_MSTP_MSTP_FWD_CFG, msti, &pmask);
        VTSS_SPRINTF(buf, "MSTP_FWD_CFG_%u", msti);
        jr2_debug_pmask(pr, buf, pmask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_mirror(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    u32  i, j;
    u64  pmask;
    char buf[32];

    for (i = 0; i < 3; i++) {
        VTSS_SPRINTF(buf, "%s Probe", i == JR2_MIRROR_PROBE_RX ? "Rx" : i == JR2_MIRROR_PROBE_TX ? "Tx" : "VLAN");
        vtss_jr2_debug_reg_header(pr, buf);
        j = QFWD_FRAME_COPY_CFG_MIRROR_PROBE(i);
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(j),          j, "QFWD:FRAME_COPY_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_REW_COMMON_MIRROR_PROBE_CFG(i),         i, "REW:PROBE_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_REW_COMMON_MIRROR_TAG_A_CFG(i),         i, "REW:TAG_A_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_REW_COMMON_MIRROR_TAG_B_CFG(i),         i, "REW:TAG_B_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG(i),       i, "ANA_AC:PROBE_CFG");
        pr("\n");

        jr2_debug_pmask_header(vtss_state, pr, NULL);
        JR2_RDX_PMASK(VTSS_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG, i, &pmask);
        VTSS_SPRINTF(buf, "PROBE_PORT_CFG_%u", i);
        jr2_debug_pmask(pr, buf, pmask);
        pr("\n");
    }

    jr2_debug_pmask_header(vtss_state, pr, NULL);
    JR2_RD_PMASK(VTSS_ANA_AC_PS_COMMON_VSTAX_GMIRROR_CFG, &pmask);
    jr2_debug_pmask(pr, "ANA_AC:GMIRROR_CFG", pmask);
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_stack(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    vtss_vstax_upsid_t       upsid;

    vtss_jr2_debug_reg_header(pr, "ANA_L2/ANA_CL");
    JR2_DEBUG_REG(pr, ANA_L2, COMMON_VSTAX_CTRL);
    JR2_DEBUG_REG(pr, ANA_CL, COMMON_UPSID_CFG);
    pr("\n");

    vtss_jr2_debug_reg_header(pr, "REW");
    JR2_DEBUG_REG_NAME(pr, REW, COMMON_VSTAX_PORT_GRP_CFG(0), "PORT_GRP_CFG(0)");
    JR2_DEBUG_REG_NAME(pr, REW, COMMON_VSTAX_PORT_GRP_CFG(1), "PORT_GRP_CFG(1)");
    pr("\n");
    
    vtss_jr2_debug_reg_header(pr, "ANA_AC");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_AC_PS_COMMON_STACK_A_CFG, "STACK_A_CFG");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_AC_PS_COMMON_STACK_CFG, "STACK_CFG");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG, "LINK_TTL_CFG");
    for (upsid = VTSS_VSTAX_UPSID_MIN; upsid <= VTSS_VSTAX_UPSID_MAX; upsid++) {
        JR2_DEBUG_REG(pr, ANA_AC, UPSID_UPSID_CFG(upsid));
    }
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_l2_debug_print(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VLAN,      jr2_debug_vlan,      vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PVLAN,     jr2_debug_pvlan,     vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MAC_TABLE, jr2_debug_mac_table, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VXLAT,     jr2_debug_vxlat,     vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_AGGR,      jr2_debug_aggr,      vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_STP,       jr2_debug_stp,       vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MIRROR,    jr2_debug_mirror,    vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_STACK,     jr2_debug_stack,     vtss_state, pr, info));

    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc jr2_l2_port_map_set(vtss_state_t *vtss_state)
{
    vtss_l2_state_t   *state = &vtss_state->l2;
    vtss_port_no_t    port_no;
    u32               pgid;
    BOOL              member[VTSS_PORT_ARRAY_SIZE];
    vtss_pgid_entry_t *pgid_entry;
    
    /* We only need to setup the no of avail pgids */
    state->pgid_count = (VTSS_PGID_JAGUAR_2 - VTSS_CHIP_PORTS + vtss_state->port_count);
    
    /* And then reserve PGIDs for flood masks */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
        member[port_no] = 1;

    for (pgid = PGID_UC_FLOOD; pgid <= PGID_IPV6_MC_CTRL; pgid++) {
        VTSS_RC(jr2_pgid_update(vtss_state, pgid, member));
    }
    
    /* Drop entry */
    pgid = vtss_jr2_vtss_pgid(vtss_state, PGID_DROP);
    state->pgid_drop = pgid;
    state->pgid_table[pgid].references = 1;

    /* Flood entry */
    pgid = vtss_jr2_vtss_pgid(vtss_state, PGID_FLOOD);
    state->pgid_flood = pgid;
    pgid_entry = &state->pgid_table[pgid];
    pgid_entry->references = 1;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) 
        pgid_entry->member[port_no] = 1;
    
#if !defined(VTSS_ARCH_JAGUAR_2_CE_MAC)
    /* GLAG entries */
    state->pgid_glag_dest = vtss_jr2_vtss_pgid(vtss_state, PGID_GLAG_START);
    
    /* Reserve entries for GLAG destinations */
    for (pgid = PGID_GLAG_START; pgid < (PGID_GLAG_START+VTSS_GLAG_PORTS*VTSS_GLAGS); pgid++) {
        state->pgid_table[vtss_jr2_vtss_pgid(vtss_state, pgid)].resv = 1;
    }
#endif /* !defined (VTSS_ARCH_JAGUAR_2_CE_MAC) */

    /* Update VLAN port configuration */
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(jr2_vlan_port_conf_update(vtss_state, port_no, &vtss_state->l2.vlan_port_conf[port_no]));
    }

    return VTSS_RC_OK;
}

static vtss_rc jr2_l2_init(vtss_state_t *vtss_state)
{
    vtss_l2_state_t *state = &vtss_state->l2;
    u32             port, msti;
    u64             port_mask_all = 0xffffffffffffffff;

    /* VLAN: Clear VID 0 and 4095 mask, enable VLAN and use default port config */
    JR2_WR(VTSS_ANA_L3_COMMON_VLAN_CTRL, 
           VTSS_F_ANA_L3_COMMON_VLAN_CTRL_VLAN_ENA(1));
    JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, 0, 0ULL);
    JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, 4095, 0ULL);
    VTSS_RC(jr2_vlan_mask_apply(vtss_state, 1, port_mask_all));
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        VTSS_RC(vtss_jr2_vlan_port_conf_apply(vtss_state, port, &state->vlan_port_conf[VTSS_PORT_NO_START], FALSE));
        JR2_WRM_CLR(VTSS_ANA_CL_PORT_FILTER_CTRL(port), VTSS_M_ANA_CL_PORT_FILTER_CTRL_FILTER_SMAC_MC_DIS);
    }

    /* Enable forwarding and learning */
    for (msti = VTSS_MSTI_START; msti < VTSS_MSTI_END; msti++) {
        JR2_WRX_PMASK(VTSS_ANA_L3_MSTP_MSTP_FWD_CFG, msti, msti ? 0 : port_mask_all);
        JR2_WRX_PMASK(VTSS_ANA_L3_MSTP_MSTP_LRN_CFG, msti, msti ? 0 : port_mask_all);
    }
    JR2_WR_PMASK(VTSS_ANA_L3_COMMON_PORT_FWD_CTRL, port_mask_all);
    JR2_WR_PMASK(VTSS_ANA_L3_COMMON_PORT_LRN_CTRL, port_mask_all);

    /* Disable learning in VLAN 0 (used for EVCs) */
    JR2_WRM(VTSS_ANA_L3_VLAN_VLAN_CFG(0), 
            VTSS_F_ANA_L3_VLAN_VLAN_CFG_VLAN_LRN_DIS(1),
            VTSS_M_ANA_L3_VLAN_VLAN_CFG_VLAN_LRN_DIS);

    /* Setup VLAN configuration */
    VTSS_RC(jr2_vlan_conf_set(vtss_state));

    /* Set MAC age time to default value */
    VTSS_RC(jr2_mac_table_age_time_set(vtss_state));

    /* Enable frame aging */
    JR2_WR(VTSS_QSYS_SYSTEM_FRM_AGING, 
           VTSS_F_QSYS_SYSTEM_FRM_AGING_MAX_AGE(500000/4)); /* Set tick to 0.5 sec */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        /* Enable aging in disassembler for each port */
        JR2_WRM(VTSS_DSM_CFG_BUF_CFG(port), 
                VTSS_F_DSM_CFG_BUF_CFG_AGING_ENA(1),
                VTSS_M_DSM_CFG_BUF_CFG_AGING_ENA);
    }

    /* Enable ISDX table */
    JR2_WRM(VTSS_ANA_L2_COMMON_FWD_CFG, 
            VTSS_F_ANA_L2_COMMON_FWD_CFG_ISDX_LOOKUP_ENA(1),
            VTSS_M_ANA_L2_COMMON_FWD_CFG_ISDX_LOOKUP_ENA);

    /* Force FID forwarding for MC service frames */
    JR2_WR(VTSS_ANA_L3_COMMON_SERVICE_CFG,
           VTSS_M_ANA_L3_COMMON_SERVICE_CFG_VSI_FORCE_MC_EFID_ENA |
           VTSS_M_ANA_L3_COMMON_SERVICE_CFG_ISDX_FORCE_MC_EFID_ENA);

    /* Disable advanced (VStaX) learning, that is, use basic learning */
    JR2_WRM(VTSS_ANA_L2_COMMON_LRN_CFG,
            VTSS_F_ANA_L2_COMMON_LRN_CFG_VSTAX_BASIC_LRN_MODE_ENA(1),
            VTSS_M_ANA_L2_COMMON_LRN_CFG_VSTAX_BASIC_LRN_MODE_ENA);

    return VTSS_RC_OK;
}

static vtss_rc jr2_l2_poll(vtss_state_t *vtss_state)
{
    vtss_l2_state_t *state = &vtss_state->l2;
    u32             i, idx;
    vtss_stat_idx_t stat_idx;
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
            VTSS_RC(vtss_jr2_sdx_counters_update(vtss_state, &stat_idx, NULL, FALSE));
            idx++;
            state->sdx_info.poll_idx = (idx < VTSS_EVC_STAT_CNT ? idx : 0);
        }
    } else {
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
        vtss_vlan_counter_info_t *vlan_info = &state->vlan_counters_info;
        
        /* For 100Gbps, 32-bit counter wrap time is about 26 seconds.
           We poll 200 VLAN counters per second, giving approximately 20 seconds between each poll */
        for (i = 0; i < 200; i++) {
            idx = (vlan_info->poll_idx + 1);
            vlan_info->poll_idx = (idx < (VTSS_VIDS - 1) ? idx : 0);
            VTSS_RC(jr2_vlan_counters_update(vtss_state, idx, NULL, FALSE));
        }
#endif
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_l2_state_t *state = &vtss_state->l2;
    
    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->mac_table_add               = jr2_mac_table_add;
        state->mac_table_del               = jr2_mac_table_del;
        state->mac_table_get               = jr2_mac_table_get;
        state->mac_table_get_next          = jr2_mac_table_get_next;
        state->mac_table_age_time_set      = jr2_mac_table_age_time_set;
        state->mac_table_age               = jr2_mac_table_age;
        state->mac_table_status_get        = jr2_mac_table_status_get;
        state->learn_port_mode_set         = jr2_learn_port_mode_set;
        state->learn_state_set             = jr2_learn_state_set;
        state->mstp_state_set              = jr2_mstp_state_set;
        state->mstp_vlan_msti_set          = vtss_cmn_vlan_members_set;
        state->erps_vlan_member_set        = vtss_cmn_erps_vlan_member_set;
        state->erps_port_state_set         = vtss_cmn_erps_port_state_set;
        state->pgid_table_write            = jr2_pgid_table_write;
        state->src_table_write             = jr2_src_table_write;
        state->aggr_table_write            = jr2_aggr_table_write;
        state->aggr_mode_set               = jr2_aggr_mode_set;
        state->pmap_table_write            = jr2_pmap_table_write;
        state->vlan_conf_set               = jr2_vlan_conf_set;
        state->vlan_port_conf_set          = vtss_cmn_vlan_port_conf_set;
        state->vlan_port_conf_update       = jr2_vlan_port_conf_update;
        state->vlan_port_members_set       = vtss_cmn_vlan_members_set;
        state->vlan_mask_update            = jr2_vlan_mask_update;
        state->vlan_tx_tag_set             = vtss_cmn_vlan_tx_tag_set;
        state->isolated_vlan_set           = vtss_cmn_vlan_members_set;
        state->isolated_port_members_set   = jr2_isolated_port_members_set;
        state->flood_conf_set              = jr2_flood_conf_set;
        state->ipv4_mc_add                 = vtss_cmn_ipv4_mc_add;
        state->ipv4_mc_del                 = vtss_cmn_ipv4_mc_del;
        state->ipv6_mc_add                 = vtss_cmn_ipv6_mc_add;
        state->ipv6_mc_del                 = vtss_cmn_ipv6_mc_del;
        state->ip_mc_update                = jr2_ip_mc_update;
        state->mirror_port_set             = jr2_mirror_port_set;
        state->mirror_ingress_set          = jr2_mirror_ingress_set;
        state->mirror_egress_set           = jr2_mirror_egress_set;
        state->mirror_cpu_ingress_set      = jr2_mirror_cpu_ingress_set;
        state->mirror_cpu_egress_set       = jr2_mirror_cpu_egress_set;
        state->eps_port_set                = vtss_cmn_eps_port_set;
        state->sflow_port_conf_set         = jr2_sflow_port_conf_set;
        state->sflow_sampling_rate_convert = jr2_sflow_sampling_rate_convert;
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
        state->vlan_counters_get           = jr2_vlan_counters_get;
        state->vlan_counters_clear         = jr2_vlan_counters_clear;
#endif /* VTSS_FEATURE_VLAN_COUNTERS */
        state->vcl_port_conf_set        = jr2_vcl_port_conf_set;
        state->vce_add                  = vtss_cmn_vce_add;
        state->vce_del                  = vtss_cmn_vce_del;
        state->vlan_trans_group_add     = vtss_cmn_vlan_trans_group_add;
        state->vlan_trans_group_del     = vtss_cmn_vlan_trans_group_del;
        state->vlan_trans_group_get     = vtss_cmn_vlan_trans_group_get;
        state->vlan_trans_port_conf_set = vtss_cmn_vlan_trans_port_conf_set;
        state->vlan_trans_port_conf_get = vtss_cmn_vlan_trans_port_conf_get;
        state->iflow_conf_set = jr2_iflow_conf_set;
        state->icnt_get = jr2_icnt_get;
        state->ecnt_get = jr2_ecnt_get;
        state->ac_count = JR2_ACS;
        state->vsi_info.max_count = VTSS_VSI_CNT;
        state->policer_update = jr2_evc_policer_update;
        state->counters_update = jr2_evc_counters_update;
        state->isdx_update = vtss_jr2_isdx_update;
        state->sdx_info.max_count = VTSS_SDX_CNT;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(jr2_l2_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(jr2_l2_port_map_set(vtss_state));
        break;
    case VTSS_INIT_CMD_POLL:
        VTSS_RC(jr2_l2_poll(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_JAGUAR_2 */
