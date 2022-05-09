// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L2
#include "vtss_ocelot_cil.h"

#if defined(VTSS_ARCH_OCELOT)

/* - CIL functions ------------------------------------------------- */

/* Convert to PGID in chip */
static u32 srvl_chip_pgid(vtss_state_t *vtss_state, u32 pgid)
{
    if (pgid < vtss_state->port_count) {
        return VTSS_CHIP_PORT(pgid);
    } else {
        return (pgid + VTSS_CHIP_PORTS - vtss_state->port_count);
    }
}

/* Convert from PGID in chip */
static u32 srvl_vtss_pgid(vtss_state_t *vtss_state, u32 pgid)
{
    vtss_port_no_t port_no;
    
    if (pgid < VTSS_CHIP_PORTS) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            if (VTSS_CHIP_PORT(port_no) == pgid)
                break;
        return port_no;
    } else {
        return (vtss_state->port_count + pgid - VTSS_CHIP_PORTS);
    }
}

static vtss_rc srvl_pgid_mask_write(vtss_state_t *vtss_state,
                                    u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE],
                                    BOOL cpu_copy, vtss_packet_rx_queue_t cpu_queue)
{
    u32 mask = vtss_srvl_port_mask(vtss_state, member);
    u32 queue = 0;
    
    if (cpu_copy) {
        mask |= VTSS_BIT(VTSS_CHIP_PORT_CPU);
        queue = cpu_queue;
    }
    SRVL_WR(VTSS_ANA_PGID_PGID(pgid),
            VTSS_F_ANA_PGID_PGID_PGID(mask) |
            VTSS_F_ANA_PGID_PGID_CPUQ_DST_PGID(queue));

    return VTSS_RC_OK;
}

static vtss_rc srvl_pgid_table_write(vtss_state_t *vtss_state,
                                     u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[pgid];

    return srvl_pgid_mask_write(vtss_state, srvl_chip_pgid(vtss_state, pgid), member, 
                                pgid_entry->cpu_copy, pgid_entry->cpu_queue);
}

static vtss_rc srvl_pgid_update(vtss_state_t *vtss_state, u32 pgid, BOOL member[])
{
    vtss_port_no_t    port_no;
    vtss_pgid_entry_t *pgid_entry;
    
    pgid = srvl_vtss_pgid(vtss_state, pgid);
    pgid_entry = &vtss_state->l2.pgid_table[pgid];
    pgid_entry->resv = 1;
    pgid_entry->references = 1;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
        pgid_entry->member[port_no] = member[port_no];
    
    return srvl_pgid_table_write(vtss_state, pgid, member);
}

static vtss_rc srvl_aggr_table_write(vtss_state_t *vtss_state,
                                     u32 ac, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return srvl_pgid_mask_write(vtss_state, PGID_AGGR + ac, member, 0, 0);
}

static vtss_rc srvl_src_table_write(vtss_state_t *vtss_state,
                                    vtss_port_no_t port_no, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return srvl_pgid_mask_write(vtss_state, PGID_SRC + VTSS_CHIP_PORT(port_no), member, 0, 0);
}

static vtss_rc srvl_aggr_mode_set(vtss_state_t *vtss_state)
{
    vtss_aggr_mode_t *mode = &vtss_state->l2.aggr_mode;

    SRVL_WR(VTSS_ANA_COMMON_AGGR_CFG,
            (mode->sip_dip_enable     ? VTSS_F_ANA_COMMON_AGGR_CFG_AC_IP4_SIPDIP_ENA : 0) |
            (mode->sport_dport_enable ? VTSS_F_ANA_COMMON_AGGR_CFG_AC_IP4_TCPUDP_ENA : 0) |
            (mode->dmac_enable        ? VTSS_F_ANA_COMMON_AGGR_CFG_AC_DMAC_ENA       : 0) |
            (mode->smac_enable        ? VTSS_F_ANA_COMMON_AGGR_CFG_AC_SMAC_ENA       : 0));
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_pmap_table_write(vtss_state_t *vtss_state,
                                     vtss_port_no_t port_no, vtss_port_no_t l_port_no)
{
    SRVL_WRM(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT(port_no)), 
             VTSS_F_ANA_PORT_PORT_CFG_PORTID_VAL(VTSS_CHIP_PORT(l_port_no)), 
             VTSS_M_ANA_PORT_PORT_CFG_PORTID_VAL);

    return VTSS_RC_OK;
}

static vtss_rc srvl_learn_state_set(vtss_state_t *vtss_state,
                                    const BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_port_no_t port_no;
    
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        SRVL_WRM_CTL(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT(port_no)), 
                     member[port_no], VTSS_F_ANA_PORT_PORT_CFG_LEARN_ENA);
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_mac_table_idle(vtss_state_t *vtss_state)
{
    u32 cmd, cnt = 0;

    do {
        SRVL_RD(VTSS_ANA_ANA_TABLES_MACACCESS, &cmd);
        cnt++;
        if (cnt == 100000) {
            VTSS_E("Timeout! cmd =  %u", cmd);
        }
    } while (VTSS_X_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(cmd) != MAC_CMD_IDLE);

    return VTSS_RC_OK;
}

static vtss_rc srvl_mac_table_add(vtss_state_t *vtss_state,
                                  const vtss_mac_table_entry_t *const entry, u32 pgid)
{
    u32  value, mach, macl, mask, idx = 0, aged = 0, fwd_kill = 0, type;
    BOOL copy_to_cpu = entry->copy_to_cpu_smac;
    
    vtss_mach_macl_get(&entry->vid_mac, &mach, &macl);
    VTSS_D("address 0x%08x%08x", mach, macl);
    
    if (pgid == VTSS_PGID_NONE) {
        /* IPv4/IPv6 MC entry, encode port mask directly */
        mask = vtss_srvl_port_mask(vtss_state, vtss_state->l2.pgid_table[pgid].member); 
        if (entry->vid_mac.mac.addr[0] == 0x01) {
            type = MAC_TYPE_IPV4_MC;
            macl = ((macl & 0x00ffffff) | ((mask << 24) & 0xff000000));
            mach = ((mach & 0xffff0000) | ((mask >> 8) & 0x0000ffff));
        } else {
            type = MAC_TYPE_IPV6_MC;
            mach = ((mach & 0xffff0000) | (mask & 0x0000ffff));
        }
    } else {
        /* Not IP MC entry */
        /* Set FWD_KILL to make the switch discard frames in SMAC lookup */
        fwd_kill = (copy_to_cpu || pgid != vtss_state->l2.pgid_drop ? 0 : 1);
        idx = srvl_chip_pgid(vtss_state, pgid);
        type = (entry->locked ? MAC_TYPE_LOCKED : MAC_TYPE_NORMAL);
    }

    /* Insert/learn new entry into the MAC table  */
    SRVL_WR(VTSS_ANA_ANA_TABLES_MACHDATA, mach);
    SRVL_WR(VTSS_ANA_ANA_TABLES_MACLDATA, macl);    

    value = ((copy_to_cpu        ? VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_CPU_COPY : 0) |
             (fwd_kill           ? VTSS_F_ANA_ANA_TABLES_MACACCESS_SRC_KILL     : 0) |
             (aged               ? VTSS_F_ANA_ANA_TABLES_MACACCESS_AGED_FLAG    : 0) |
             VTSS_F_ANA_ANA_TABLES_MACACCESS_VALID                                   |
             VTSS_F_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE(type)                        |
             VTSS_F_ANA_ANA_TABLES_MACACCESS_DEST_IDX(idx)                           |
             VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MAC_CMD_LEARN));
    SRVL_WR(VTSS_ANA_ANA_TABLES_MACACCESS, value);

    /* Wait until MAC operation is finished */
    return srvl_mac_table_idle(vtss_state);
}

static u32 srvl_mac_type(const vtss_vid_mac_t *vid_mac)
{
    return (VTSS_MAC_IPV4_MC(vid_mac->mac.addr) ? MAC_TYPE_IPV4_MC :
            VTSS_MAC_IPV6_MC(vid_mac->mac.addr) ? MAC_TYPE_IPV6_MC : MAC_TYPE_NORMAL);
}

static vtss_rc srvl_mac_table_cmd(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac, u32 type, u32 cmd)
{
    u32 mach, macl;
    
    vtss_mach_macl_get(vid_mac, &mach, &macl);
    VTSS_D("cmd: %u, address 0x%08x%08x", cmd, mach, macl);
    
    /* Run command for MAC entry */
    SRVL_WR(VTSS_ANA_ANA_TABLES_MACHDATA, mach);
    SRVL_WR(VTSS_ANA_ANA_TABLES_MACLDATA, macl);    
    SRVL_WR(VTSS_ANA_ANA_TABLES_MACACCESS, 
            VTSS_F_ANA_ANA_TABLES_MACACCESS_VALID |
            VTSS_F_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE(type) |
            VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(cmd));
    
    /* Wait until MAC operation is finished */
    return srvl_mac_table_idle(vtss_state);
}

static vtss_rc srvl_mac_table_del(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac)
{
    u32 type = srvl_mac_type(vid_mac);

    VTSS_RC(srvl_mac_table_cmd(vtss_state, vid_mac, type, MAC_CMD_FORGET));
    if (type != MAC_TYPE_NORMAL) {
        /* IPMC entries may be encoded as NORMAL */
        VTSS_RC(srvl_mac_table_cmd(vtss_state, vid_mac, MAC_TYPE_NORMAL, MAC_CMD_FORGET));
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_mac_table_result(vtss_state_t *vtss_state,
                                     vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32               value, mask, mach, macl, idx, type;
    vtss_port_no_t    port_no;
    vtss_pgid_entry_t *pgid_entry;
    u8                *mac = &entry->vid_mac.mac.addr[0];
    
    SRVL_RD(VTSS_ANA_ANA_TABLES_MACACCESS, &value);        

    /* Check if entry is valid */
    if (!(value & VTSS_F_ANA_ANA_TABLES_MACACCESS_VALID)) {
        VTSS_D("not valid");
        return VTSS_RC_ERROR;
    }

    type               = VTSS_X_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE(value);
    idx                = VTSS_X_ANA_ANA_TABLES_MACACCESS_DEST_IDX(value); 
    entry->aged        = VTSS_BOOL(value & VTSS_F_ANA_ANA_TABLES_MACACCESS_AGED_FLAG);
    entry->copy_to_cpu = 0;
    entry->copy_to_cpu_smac = VTSS_BOOL(value & VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_CPU_COPY);
    entry->locked      = (type == MAC_TYPE_NORMAL ? 0 : 1);

    SRVL_RD(VTSS_ANA_ANA_TABLES_MACHDATA, &mach);
    SRVL_RD(VTSS_ANA_ANA_TABLES_MACLDATA, &macl);

    if (type == MAC_TYPE_IPV4_MC || type == MAC_TYPE_IPV6_MC) {
        /* IPv4/IPv6 MC entry, decode port mask from entry */
        *pgid = VTSS_PGID_NONE;
        if (type == MAC_TYPE_IPV6_MC) {
            mask = (mach & 0xffff);
            mach = ((mach & 0xffff0000) | 0x00003333);
        } else {
            mask = (((mach << 8) & 0xffff00) | ((macl >> 24) & 0xff));
            mach = ((mach & 0xffff0000) | 0x00000100);
            macl = ((macl & 0x00ffffff) | 0x5e000000);
        }    

        /* Convert port mask */
        pgid_entry = &vtss_state->l2.pgid_table[*pgid];
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            pgid_entry->member[port_no] = VTSS_BOOL(mask & (1 << VTSS_CHIP_PORT(port_no)));
    } else {
        *pgid = srvl_vtss_pgid(vtss_state, idx);
    }
    entry->vid_mac.vid = ((mach>>16) & 0xFFF);
    mac[0] = ((mach>>8)  & 0xff);
    mac[1] = ((mach>>0)  & 0xff);
    mac[2] = ((macl>>24) & 0xff);
    mac[3] = ((macl>>16) & 0xff);
    mac[4] = ((macl>>8)  & 0xff);
    mac[5] = ((macl>>0)  & 0xff);
    VTSS_D("found 0x%08x%08x", mach, macl);

    return VTSS_RC_OK;
}

static vtss_rc srvl_mac_table_get(vtss_state_t *vtss_state,
                                  vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    vtss_rc rc;
    u32     type = srvl_mac_type(&entry->vid_mac);

    VTSS_RC(srvl_mac_table_cmd(vtss_state, &entry->vid_mac, type, MAC_CMD_READ));
    rc = srvl_mac_table_result(vtss_state, entry, pgid);
    if (type != MAC_TYPE_NORMAL && rc != VTSS_RC_OK) {
        /* IPMC entries may be encoded as NORMAL */
        VTSS_RC(srvl_mac_table_cmd(vtss_state, &entry->vid_mac, MAC_TYPE_NORMAL, MAC_CMD_READ));
        rc = srvl_mac_table_result(vtss_state, entry, pgid);
    }
    return rc;
}

static vtss_rc srvl_mac_table_get_next(vtss_state_t *vtss_state,
                                       vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    VTSS_RC(srvl_mac_table_cmd(vtss_state, &entry->vid_mac, MAC_TYPE_NORMAL, MAC_CMD_GET_NEXT));
    return srvl_mac_table_result(vtss_state, entry, pgid);
}

static vtss_rc srvl_mac_table_age_time_set(vtss_state_t *vtss_state)
{
    u32 time;
    
    /* Scan two times per age time */
    time = (vtss_state->l2.mac_age_time/2);
    if (time > 0xfffff)
        time = 0xfffff;
    SRVL_WR(VTSS_ANA_ANA_AUTOAGE, VTSS_F_ANA_ANA_AUTOAGE_AGE_PERIOD(time));
    
    return VTSS_RC_OK;
}

/* Maximum FID value */
#define SRVL_FID_MAX 63

static vtss_rc srvl_mac_table_age(vtss_state_t *vtss_state,
                                  BOOL             pgid_age, 
                                  u32              pgid,
                                  BOOL             vid_age,
                                  const vtss_vid_t vid)
{
    vtss_vid_t fid;

#if defined(VTSS_FEATURE_VLAN_SVL)
    /* Age on FID, if possible */
    fid = vtss_state->l2.vlan_table[vid].fid;
    if (fid == 0 || fid > SRVL_FID_MAX) {
        fid = vid;
    }
#else
    fid = vid;
#endif /* VTSS_FEATURE_VLAN_SVL */

    /* Selective aging */
    SRVL_WR(VTSS_ANA_ANA_ANAGEFIL, 
            (pgid_age ? VTSS_F_ANA_ANA_ANAGEFIL_PID_EN : 0) |
            (vid_age ? VTSS_F_ANA_ANA_ANAGEFIL_VID_EN  : 0) |
            VTSS_F_ANA_ANA_ANAGEFIL_PID_VAL(srvl_chip_pgid(vtss_state, pgid)) |
            VTSS_F_ANA_ANA_ANAGEFIL_VID_VAL(fid));
    
    /* Do the aging */
    SRVL_WR(VTSS_ANA_ANA_TABLES_MACACCESS, 
            VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MAC_CMD_TABLE_AGE));
    
    VTSS_RC(srvl_mac_table_idle(vtss_state));

    /* Clear age filter again to avoid affecting automatic ageing */
    SRVL_WR(VTSS_ANA_ANA_ANAGEFIL, 0);

    return VTSS_RC_OK;
}

static vtss_rc srvl_mac_table_status_get(vtss_state_t *vtss_state,
                                         vtss_mac_table_status_t *status) 
{
    u32 value;

    /* Read and clear sticky register */
    SRVL_RD(VTSS_ANA_ANA_ANEVENTS, &value);
    SRVL_WR(VTSS_ANA_ANA_ANEVENTS, value & 
            (VTSS_F_ANA_ANA_ANEVENTS_AUTO_MOVED   |
             VTSS_F_ANA_ANA_ANEVENTS_AUTO_LEARNED |
             VTSS_F_ANA_ANA_ANEVENTS_LEARN_REMOVE |
             VTSS_F_ANA_ANA_ANEVENTS_AGED_ENTRY));

   
    /* Detect learn events */
    status->learned = VTSS_BOOL(value & VTSS_F_ANA_ANA_ANEVENTS_AUTO_LEARNED);
    
    /* Detect replace events */
    status->replaced = VTSS_BOOL(value & VTSS_F_ANA_ANA_ANEVENTS_LEARN_REMOVE);

    /* Detect port move events */
    status->moved = VTSS_BOOL(value & (VTSS_F_ANA_ANA_ANEVENTS_AUTO_MOVED));
    
    /* Detect age events */
    status->aged = VTSS_BOOL(value & VTSS_F_ANA_ANA_ANEVENTS_AGED_ENTRY);

    return VTSS_RC_OK;
}

static vtss_rc srvl_learn_port_mode_set(vtss_state_t *vtss_state,
                                        const vtss_port_no_t port_no)
{
    vtss_learn_mode_t *mode = &vtss_state->l2.learn_mode[port_no];
    u32               value, port = VTSS_CHIP_PORT(port_no);

    SRVL_WRM(VTSS_ANA_PORT_PORT_CFG(port), 
             (mode->discard   ? VTSS_F_ANA_PORT_PORT_CFG_LEARNDROP : 0) |
             (mode->automatic ? VTSS_F_ANA_PORT_PORT_CFG_LEARNAUTO : VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_CPU) |
             (mode->cpu       ? VTSS_F_ANA_PORT_PORT_CFG_LEARNCPU  : 0) |
             VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_DROP,
             (VTSS_F_ANA_PORT_PORT_CFG_LEARNDROP            |
              VTSS_F_ANA_PORT_PORT_CFG_LEARNAUTO            |
              VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_CPU  |
              VTSS_F_ANA_PORT_PORT_CFG_LEARNCPU             |
              VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_DROP));
    
    if (!mode->automatic) {
        /* Flush entries previously learned on port to avoid continuous refreshing */
        SRVL_RD(VTSS_ANA_PORT_PORT_CFG(port), &value);
        SRVL_WRM_CLR(VTSS_ANA_PORT_PORT_CFG(port), VTSS_F_ANA_PORT_PORT_CFG_LEARN_ENA);
        VTSS_RC(srvl_mac_table_age(vtss_state, 1, port_no, 0, 0));
        VTSS_RC(srvl_mac_table_age(vtss_state, 1, port_no, 0, 0));
        SRVL_WR(VTSS_ANA_PORT_PORT_CFG(port), value);
    }

    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - VLAN 
 * ================================================================= */

static vtss_rc srvl_vlan_conf_apply(vtss_state_t *vtss_state, BOOL ports)
{
    u32            etype = vtss_state->l2.vlan_conf.s_etype;
    vtss_port_no_t port_no;

    /* BZ 4513: Type 0x8100 can not be used so we use 0x88a8 */
    if (etype == VTSS_ETYPE_TAG_C)
        etype = VTSS_ETYPE_TAG_S;

    SRVL_WR(VTSS_SYS_SYSTEM_VLAN_ETYPE_CFG, etype);

    /* Update ports */
    for (port_no = VTSS_PORT_NO_START; ports && port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(vtss_cmn_vlan_port_conf_set(vtss_state, port_no));
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_vlan_conf_set(vtss_state_t *vtss_state)
{
    return srvl_vlan_conf_apply(vtss_state, 1);
}

static vtss_rc srvl_vlan_port_conf_apply(vtss_state_t *vtss_state,
                                         u32                   port, 
                                         vtss_vlan_port_conf_t *conf)
{
    u32                   tpid = TAG_TPID_CFG_0x8100;
    u32                   value, etype = vtss_state->l2.vlan_conf.s_etype;
    BOOL                  tagged, untagged, aware = 1, c_port = 0, s_port = 0;
    vtss_vlan_port_type_t type = conf->port_type;
    
    /* BZ4513: If the custom TPID is 0x8100, we treat S-custom ports as C-ports */
    if (etype == VTSS_ETYPE_TAG_C && type == VTSS_VLAN_PORT_TYPE_S_CUSTOM)
        type = VTSS_VLAN_PORT_TYPE_C;

    /* Check port type */
    switch (type) {
    case VTSS_VLAN_PORT_TYPE_UNAWARE:
        aware = 0;
        break;
    case VTSS_VLAN_PORT_TYPE_C:
        c_port = 1;
        break;
    case VTSS_VLAN_PORT_TYPE_S:
        s_port = 1;
        tpid = TAG_TPID_CFG_0x88A8;
        break;
    case VTSS_VLAN_PORT_TYPE_S_CUSTOM:
        s_port = 1;
        tpid = TAG_TPID_CFG_PTPID;
        break;
    default:
        return VTSS_RC_ERROR;
    }

    /* Port VLAN Configuration */
    value = VTSS_F_ANA_PORT_VLAN_CFG_VLAN_VID(conf->pvid); /* Port VLAN */
    if (aware) {
        /* VLAN aware, pop outer tag */
        value |= VTSS_F_ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA; 
        value |= VTSS_F_ANA_PORT_VLAN_CFG_VLAN_POP_CNT(1);
    }
    SRVL_WRM(VTSS_ANA_PORT_VLAN_CFG(port), value,
             VTSS_M_ANA_PORT_VLAN_CFG_VLAN_VID |
             VTSS_F_ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA |
             VTSS_M_ANA_PORT_VLAN_CFG_VLAN_POP_CNT);
    
    /* Drop Configuration based on port type and frame type */
    tagged = (conf->frame_type == VTSS_VLAN_FRAME_TAGGED);
    untagged = (conf->frame_type == VTSS_VLAN_FRAME_UNTAGGED);
    value = VTSS_F_ANA_PORT_DROP_CFG_DROP_MC_SMAC_ENA;
    if (tagged && aware) {
        /* Discard untagged and priority-tagged if aware and tagged-only allowed */
        value |= VTSS_F_ANA_PORT_DROP_CFG_DROP_UNTAGGED_ENA;
        value |= VTSS_F_ANA_PORT_DROP_CFG_DROP_PRIO_C_TAGGED_ENA;
        value |= VTSS_F_ANA_PORT_DROP_CFG_DROP_PRIO_S_TAGGED_ENA;
    }
    if ((untagged && c_port) || (tagged && s_port)) {
        /* Discard C-tagged if C-port and untagged-only OR S-port and tagged-only */
        value |= VTSS_F_ANA_PORT_DROP_CFG_DROP_C_TAGGED_ENA;
    }
    if ((untagged && s_port) || (tagged && c_port)) {
        /* Discard S-tagged if S-port and untagged-only OR C-port and tagged-only */
        value |= VTSS_F_ANA_PORT_DROP_CFG_DROP_S_TAGGED_ENA;
    }
    SRVL_WR(VTSS_ANA_PORT_DROP_CFG(port), value);
    
    /* Ingress filtering */
    SRVL_WRM(VTSS_ANA_ANA_VLANMASK, (conf->ingress_filter ? 1 : 0) << port, 1 << port);

    /* Rewriter VLAN tag configuration */
    value = (VTSS_F_REW_PORT_TAG_CFG_TAG_TPID_CFG(tpid) |
             VTSS_F_REW_PORT_TAG_CFG_TAG_CFG(
                 conf->untagged_vid == VTSS_VID_ALL ? TAG_CFG_DISABLE :
                 conf->untagged_vid == VTSS_VID_NULL ? TAG_CFG_ALL_NNUL : TAG_CFG_ALL_NPV_NNUL));
    SRVL_WRM(VTSS_REW_PORT_TAG_CFG(port), value, 
             VTSS_M_REW_PORT_TAG_CFG_TAG_TPID_CFG | 
             VTSS_M_REW_PORT_TAG_CFG_TAG_CFG);
    SRVL_WRM(VTSS_REW_PORT_PORT_VLAN_CFG(port), 
             VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_TPID(conf->s_etype ? conf->s_etype : etype) |
             VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_VID(conf->untagged_vid),
             VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_TPID |
             VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_VID);

    return VTSS_RC_OK;
}

static vtss_rc srvl_vlan_port_conf_update(vtss_state_t *vtss_state,
                                          vtss_port_no_t port_no, vtss_vlan_port_conf_t *conf)
{
    /* Update maximum tags allowed */
    VTSS_RC(vtss_srvl_port_max_tags_set(vtss_state, port_no));

    return srvl_vlan_port_conf_apply(vtss_state, VTSS_CHIP_PORT(port_no), conf);
}

static vtss_rc srvl_vlan_table_idle(vtss_state_t *vtss_state)
{
    u32 value;
    
    do {
        SRVL_RD(VTSS_ANA_ANA_TABLES_VLANACCESS, &value);
    } while (VTSS_X_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(value) != VLAN_CMD_IDLE);

    return VTSS_RC_OK;
}

static vtss_rc srvl_vlan_mask_update(vtss_state_t *vtss_state,
                                     vtss_vid_t vid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_vlan_entry_t *e = &vtss_state->l2.vlan_table[vid];

    /* Index and properties */
    SRVL_WR(VTSS_ANA_ANA_TABLES_VLANTIDX, 
            VTSS_F_ANA_ANA_TABLES_VLANTIDX_V_INDEX(vid) |
            (e->flags & VLAN_FLAGS_ISOLATED ? VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_PRIV_VLAN : 0) |
            (e->flags & VLAN_FLAGS_LEARN ? 0 : VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_LEARN_DISABLED) |
            (e->flags & VLAN_FLAGS_MIRROR ? VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_MIRROR : 0) |
            (e->flags & VLAN_FLAGS_FILTER ? VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_SRC_CHK : 0));

    /* VLAN mask */
    SRVL_WR(VTSS_ANA_ANA_TABLES_VLANACCESS,
            VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_PORT_MASK(vtss_srvl_port_mask(vtss_state, member)) |
            VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_CMD_WRITE));

#if defined(VTSS_FEATURE_VLAN_SVL)
    /* FID */
    SRVL_WR(VTSS_ANA_FID_MAP_FID_MAP(vid),
            VTSS_F_ANA_FID_MAP_FID_MAP_FID_C_VAL(e->fid > SRVL_FID_MAX ? 0 : e->fid));
#endif /* VTSS_FEATURE_VLAN_SVL */

    return srvl_vlan_table_idle(vtss_state);
}

/* ================================================================= *
 *  Layer 2 - PVLAN / Isolated ports
 * ================================================================= */

static vtss_rc srvl_isolated_port_members_set(vtss_state_t *vtss_state)
{
    u32 mask = vtss_srvl_port_mask(vtss_state, vtss_state->l2.isolated_port);

    /* Isolated ports: cleared (add CPU as not isolated) */
    mask = ((~mask) & VTSS_CHIP_PORT_MASK) | VTSS_BIT(VTSS_CHIP_PORT_CPU);
    SRVL_WR(VTSS_ANA_ANA_ISOLATED_PORTS, mask);
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - IP Multicast
 * ================================================================= */

static vtss_rc srvl_flood_conf_set(vtss_state_t *vtss_state)
{
    u32 pgid = (vtss_state->l2.ipv6_mc_scope ? PGID_MCIPV6 : PGID_MC);

    /* Unicast flood mask */
    VTSS_RC(srvl_pgid_update(vtss_state, PGID_UC, vtss_state->l2.uc_flood));
    
    /* Multicast flood mask */
    VTSS_RC(srvl_pgid_update(vtss_state, PGID_MC, vtss_state->l2.mc_flood));
    
    /* IPv4 flood mask */
    VTSS_RC(srvl_pgid_update(vtss_state, PGID_MCIPV4, vtss_state->l2.ipv4_mc_flood));

    /* IPv6 flood mask */
    VTSS_RC(srvl_pgid_update(vtss_state, PGID_MCIPV6, vtss_state->l2.ipv6_mc_flood));

    /* IPv6 flood scope */
    SRVL_WRM(VTSS_ANA_ANA_FLOODING_IPMC, 
             VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL(pgid),
             VTSS_M_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ip_mc_update(vtss_state_t *vtss_state,
                                 vtss_ipmc_data_t *ipmc, vtss_ipmc_cmd_t cmd)
{
    vtss_vcap_obj_t       *obj = &vtss_state->vcap.is2.obj;
    int                   i, user = (ipmc->src.ssm ? VTSS_IS2_USER_SSM : VTSS_IS2_USER_ASM);
    vtss_vcap_key_size_t  key_size = (ipmc->ipv6 ? VTSS_VCAP_KEY_SIZE_FULL : VTSS_VCAP_KEY_SIZE_HALF);
    vtss_res_chg_t        res;
    vtss_vcap_data_t      data;
    vtss_is2_entry_t      entry;
    vtss_ace_t            *ace = &entry.ace;
    vtss_ace_frame_ipv4_t *ipv4 = &ace->frame.ipv4;
    vtss_ace_frame_ipv6_t *ipv6 = &ace->frame.ipv6;
    vtss_port_no_t        port_no;

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
    ace->lookup = 1;
    ace->vlan.vid.value = ipmc->src.vid;
    ace->vlan.vid.mask = 0xfff;
    if (ipmc->ipv6) {
        ace->type = VTSS_ACE_TYPE_IPV6;
        for (i = 0; i < 16; i++) {
            ipv6->sip.value[i] = ipmc->src.sip.ipv6.addr[i];
            ipv6->sip.mask[i] = (ipmc->src.ssm ? 0xff : 0);
            ipv6->dip.value[i] = ipmc->dst.dip.ipv6.addr[i];
            ipv6->dip.mask[i] = 0xff;
        }
    } else {
        ace->type = VTSS_ACE_TYPE_IPV4;
        ipv4->sip.value = ipmc->src.sip.ipv4;
        ipv4->sip.mask = (ipmc->src.ssm ? 0xffffffff : 0);
        ipv4->dip.value = ipmc->dst.dip.ipv4;
        ipv4->dip.mask = 0xffffffff;
    }
    ace->action.learn = TRUE;
    ace->action.port_action = VTSS_ACL_PORT_ACTION_PGID;
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        ace->port_list[port_no] = 1;
        ace->action.port_list[port_no] = VTSS_PORT_BF_GET(ipmc->dst.member, port_no);
    }
    return vtss_vcap_add(vtss_state, obj, user, ipmc->dst.id, ipmc->id_next, &data, 0);
}

/* ================================================================= *
 *  Layer 2 - Mirror
 * ================================================================= */

#ifdef VTSS_FEATURE_MIRROR_CPU
/* CPU Ingress ports subjects for mirroring */
static vtss_rc srvl_mirror_cpu_ingress_set(vtss_state_t *vtss_state)
{
    BOOL enabled = vtss_state->l2.mirror_cpu_ingress;
    
    SRVL_WRM(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT_CPU),
            (enabled ? VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA : 0), VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA);
   return VTSS_RC_OK;
}

/* CPU Egress ports subjects for mirroring */
static vtss_rc srvl_mirror_cpu_egress_set(vtss_state_t *vtss_state)
{
    BOOL enabled = vtss_state->l2.mirror_cpu_egress;

    SRVL_WRM(VTSS_ANA_ANA_AGENCTRL, enabled ? VTSS_F_ANA_ANA_AGENCTRL_MIRROR_CPU : 0 , VTSS_F_ANA_ANA_AGENCTRL_MIRROR_CPU);
    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_MIRROR_CPU

static vtss_rc srvl_mirror_port_set(vtss_state_t *vtss_state)
{
    BOOL           member[VTSS_PORT_ARRAY_SIZE];
    vtss_port_no_t port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        member[port_no] = (port_no == vtss_state->l2.mirror_conf.port_no);
    }
    SRVL_WR(VTSS_ANA_ANA_MIRRORPORTS, vtss_srvl_port_mask(vtss_state, member));    

    /* Update all VLANs */
    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc srvl_mirror_ingress_set(vtss_state_t *vtss_state)
{
#if defined (VTSS_FEATURE_MPLS)
    vtss_port_no_t           port_no;
    vtss_mpls_vprofile_idx_t vp_idx;
    BOOL                     set[VTSS_MPLS_VPROFILE_CNT];

    /* The ingress mirror bit is per virtual port profile. This means that if
     * we have MPLS enabled, the ingress mirroring setup must be applied for all
     * VProfiles (except the static and shared entries for OAM and LSR; ingress
     * mirroring won't work for those since they may be used with multiple
     * ports.)
     */

    VTSS_MEMSET(set, 0, sizeof(set));
    for (vp_idx = VTSS_MPLS_VPROFILE_RESERVED_CNT; vp_idx < VTSS_MPLS_VPROFILE_CNT; vp_idx++) {
        vtss_mpls_vprofile_t *vp = &VP_P(vp_idx);
        set[vp_idx] = (vp->port < vtss_state->port_count)  &&  vtss_state->l2.mirror_ingress[vp->port];
    }

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        set[VTSS_CHIP_PORT(port_no)] = vtss_state->l2.mirror_ingress[port_no];
    }

    for (vp_idx = 0; vp_idx < VTSS_MPLS_VPROFILE_CNT; vp_idx++) {
        SRVL_WRM_CTL(VTSS_ANA_PORT_PORT_CFG(vp_idx), set[vp_idx], VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA);
    }
#else
    vtss_port_no_t port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_I("vtss_state->l2.mirror_ingress[port_no]:%d, port_no:%d, chip_port:%d", vtss_state->l2.mirror_ingress[port_no], port_no, VTSS_CHIP_PORT(port_no));
        SRVL_WRM_CTL(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT(port_no)),
                     vtss_state->l2.mirror_ingress[port_no],
                     VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA);
    }
#endif /* VTSS_FEATURE_MPLS */
    return VTSS_RC_OK;
}

static vtss_rc srvl_mirror_egress_set(vtss_state_t *vtss_state)
{
    SRVL_WR(VTSS_ANA_ANA_EMIRRORPORTS, vtss_srvl_port_mask(vtss_state, vtss_state->l2.mirror_egress));
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_vcap_port_conf_t *conf = &vtss_state->vcap.port_conf[port_no];
    BOOL                  dmac_dip_new = conf->dmac_dip_1;
    vtss_vcap_key_type_t  key_old = vtss_state->vcap.port_conf_old.key_type_is1_1;
    vtss_vcap_key_type_t  key_new = conf->key_type_is1_1;

    /* Setup second IS1 lookup */
    return vtss_srvl_vcap_port_key_addr_set(vtss_state, port_no, 1, key_new, key_old, dmac_dip_new);
}

static vtss_rc srvl_iflow_conf_set(vtss_state_t *vtss_state, const vtss_iflow_id_t id)
{
    vtss_sdx_entry_t *sdx = vtss_iflow_lookup(vtss_state, id);

    return (sdx == NULL ? VTSS_RC_ERROR :
            vtss_srvl_isdx_update(vtss_state,
                                  sdx->conf.voe_idx == VTSS_VOE_IDX_NONE ? FALSE : TRUE,  /* isdx_ena */
                                  sdx->sdx, 0xffffffff, 0,
                                  sdx->conf.voe_idx));  /* voe_idx */
}

/* ================================================================= *
 *  SFLOW
 * ================================================================= */

/* sFlow H/W-related min/max */
#define SRVL_SFLOW_MIN_SAMPLE_RATE    0 /**< Minimum allowable sampling rate for sFlow */
#define SRVL_SFLOW_MAX_SAMPLE_RATE 4095 /**< Maximum allowable sampling rate for sFlow */

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

/**
 * srvl_sflow_hw_rate()
 */
static u32 srvl_sflow_hw_rate(const u32 desired_sw_rate, u32 *const realizable_sw_rate)
{
    u32 hw_rate         = desired_sw_rate ? VTSS_ROUNDING_DIVISION(SRVL_SFLOW_MAX_SAMPLE_RATE + 1, desired_sw_rate) : 0;
    hw_rate             = hw_rate > SRVL_SFLOW_MIN_SAMPLE_RATE ? hw_rate - 1 : hw_rate;
    *realizable_sw_rate = VTSS_ROUNDING_DIVISION(SRVL_SFLOW_MAX_SAMPLE_RATE + 1, hw_rate + 1);
    return hw_rate;
}

/**
 * srvl_sflow_sampling_rate_convert()
 */
static vtss_rc srvl_sflow_sampling_rate_convert(struct vtss_state_s *const state, const BOOL power2, const u32 rate_in, u32 *const rate_out)
{
    u32 modified_rate_in;
    // Could happen that two threads call this function simultaneously at boot, but we take the risk.
    // Once sflow_max_power_of_two has been computed, it's no longer a problem with simultaneous access.
    u32 sflow_max_power_of_two = state->l2.sflow_max_power_of_two;

    if (sflow_max_power_of_two == 0) {
        sflow_max_power_of_two = next_power_of_two(SRVL_SFLOW_MAX_SAMPLE_RATE);
        if ((SRVL_SFLOW_MAX_SAMPLE_RATE & sflow_max_power_of_two) == 0) {
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

    (void)srvl_sflow_hw_rate(modified_rate_in, rate_out);
    return VTSS_RC_OK;
}

/**
 * srvl_sflow_port_conf_set()
 */
static vtss_rc srvl_sflow_port_conf_set(vtss_state_t *vtss_state,
                                        const vtss_port_no_t port_no,
                                        const vtss_sflow_port_conf_t *const new_conf)
{
    u32 hw_rate, value;
    vtss_sflow_port_conf_t *cur_conf = &vtss_state->l2.sflow_conf[port_no];

    *cur_conf = *new_conf;
    hw_rate = srvl_sflow_hw_rate(new_conf->sampling_rate, &cur_conf->sampling_rate);

    value  = VTSS_F_ANA_ANA_SFLOW_CFG_SF_RATE(hw_rate);
    value |= new_conf->sampling_rate != 0 && (new_conf->type == VTSS_SFLOW_TYPE_ALL || new_conf->type == VTSS_SFLOW_TYPE_RX) ? VTSS_F_ANA_ANA_SFLOW_CFG_SF_SAMPLE_RX : 0;
    value |= new_conf->sampling_rate != 0 && (new_conf->type == VTSS_SFLOW_TYPE_ALL || new_conf->type == VTSS_SFLOW_TYPE_TX) ? VTSS_F_ANA_ANA_SFLOW_CFG_SF_SAMPLE_TX : 0;
    SRVL_WR(VTSS_ANA_ANA_SFLOW_CFG(VTSS_CHIP_PORT(port_no)), value);

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc srvl_debug_mac_table(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    u32  value, port;
    BOOL header = 1;

    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        if (vtss_cmn_port2port_no(vtss_state, info, port) == VTSS_PORT_NO_NONE)
            continue;
        if (header)
            pr("Port  ID  Learn  L_Auto  L_CPU  L_DROP  PM_DROP PM_CPU Mirror\n");
        header = 0;

        SRVL_RD(VTSS_ANA_PORT_PORT_CFG(port), &value);
        pr("%-4u  %-2u  %-5u  %-6u  %-5u  %-6u  %-7u  %-6u  %u\n",
           port,
           VTSS_X_ANA_PORT_PORT_CFG_PORTID_VAL(value),
           VTSS_BOOL(value & VTSS_F_ANA_PORT_PORT_CFG_LEARN_ENA),
           VTSS_BOOL(value & VTSS_F_ANA_PORT_PORT_CFG_LEARNAUTO),
           VTSS_BOOL(value & VTSS_F_ANA_PORT_PORT_CFG_LEARNCPU),
           VTSS_BOOL(value & VTSS_F_ANA_PORT_PORT_CFG_LEARNDROP),
           VTSS_BOOL(value & VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_DROP),
           VTSS_BOOL(value & VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_CPU),
           VTSS_BOOL(value & VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA));
    }

    if (!header)
        pr("\n");

    /* Read and clear analyzer sticky bits */
    SRVL_RD(VTSS_ANA_ANA_ANEVENTS, &value);
    SRVL_WR(VTSS_ANA_ANA_ANEVENTS, value);

    vtss_debug_print_sticky(pr, "AUTOAGE", value, VTSS_F_ANA_ANA_ANEVENTS_AUTOAGE);
    vtss_debug_print_sticky(pr, "STORM_DROP", value, VTSS_F_ANA_ANA_ANEVENTS_STORM_DROP);
    vtss_debug_print_sticky(pr, "LEARN_DROP", value, VTSS_F_ANA_ANA_ANEVENTS_LEARN_DROP);
    vtss_debug_print_sticky(pr, "AGED_ENTRY", value, VTSS_F_ANA_ANA_ANEVENTS_AGED_ENTRY);
    vtss_debug_print_sticky(pr, "CPU_LEARN_FAILED", value, VTSS_F_ANA_ANA_ANEVENTS_CPU_LEARN_FAILED);
    vtss_debug_print_sticky(pr, "AUTO_LEARN_FAILED", value, VTSS_F_ANA_ANA_ANEVENTS_AUTO_LEARN_FAILED);
    vtss_debug_print_sticky(pr, "LEARN_REMOVE", value, VTSS_F_ANA_ANA_ANEVENTS_LEARN_REMOVE);
    vtss_debug_print_sticky(pr, "AUTO_LEARNED", value, VTSS_F_ANA_ANA_ANEVENTS_AUTO_LEARNED);
    vtss_debug_print_sticky(pr, "AUTO_MOVED", value, VTSS_F_ANA_ANA_ANEVENTS_AUTO_MOVED);
    vtss_debug_print_sticky(pr, "CLASSIFIED_DROP", value, VTSS_F_ANA_ANA_ANEVENTS_CLASSIFIED_DROP);
    vtss_debug_print_sticky(pr, "CLASSIFIED_COPY", value, VTSS_F_ANA_ANA_ANEVENTS_CLASSIFIED_COPY);
    vtss_debug_print_sticky(pr, "VLAN_DISCARD", value, VTSS_F_ANA_ANA_ANEVENTS_VLAN_DISCARD);
    vtss_debug_print_sticky(pr, "FWD_DISCARD", value, VTSS_F_ANA_ANA_ANEVENTS_FWD_DISCARD);
    vtss_debug_print_sticky(pr, "MULTICAST_FLOOD", value, VTSS_F_ANA_ANA_ANEVENTS_MULTICAST_FLOOD);
    vtss_debug_print_sticky(pr, "UNICAST_FLOOD", value, VTSS_F_ANA_ANA_ANEVENTS_UNICAST_FLOOD);
    vtss_debug_print_sticky(pr, "DEST_KNOWN", value, VTSS_F_ANA_ANA_ANEVENTS_DEST_KNOWN);
    vtss_debug_print_sticky(pr, "BUCKET3_MATCH", value, VTSS_F_ANA_ANA_ANEVENTS_BUCKET3_MATCH);
    vtss_debug_print_sticky(pr, "BUCKET2_MATCH", value, VTSS_F_ANA_ANA_ANEVENTS_BUCKET2_MATCH);
    vtss_debug_print_sticky(pr, "BUCKET1_MATCH", value, VTSS_F_ANA_ANA_ANEVENTS_BUCKET1_MATCH);
    vtss_debug_print_sticky(pr, "BUCKET0_MATCH", value, VTSS_F_ANA_ANA_ANEVENTS_BUCKET0_MATCH);
    vtss_debug_print_sticky(pr, "CPU_OPERATION", value, VTSS_F_ANA_ANA_ANEVENTS_CPU_OPERATION);
    vtss_debug_print_sticky(pr, "DMAC_LOOKUP", value, VTSS_F_ANA_ANA_ANEVENTS_DMAC_LOOKUP);
    vtss_debug_print_sticky(pr, "SMAC_LOOKUP", value, VTSS_F_ANA_ANA_ANEVENTS_SMAC_LOOKUP);
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_src_table(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    u32 port, mask;

    vtss_debug_print_header(pr, "Source Masks");
    vtss_srvl_debug_print_port_header(vtss_state, pr, "Port  ");
    for (port = 0; port <= VTSS_CHIP_PORTS;  port++) {
        SRVL_RD(VTSS_ANA_PGID_PGID(PGID_SRC + port), &mask);
        mask = VTSS_X_ANA_PGID_PGID_PGID(mask);
        pr("%-4u  ", port);
        vtss_srvl_debug_print_mask(pr, mask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_aggr(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    u32 ac, pgid, mask, value;
    
    VTSS_RC(srvl_debug_src_table(vtss_state, pr, info));
    
    vtss_debug_print_header(pr, "Aggregation Masks");
    vtss_srvl_debug_print_port_header(vtss_state, pr, "AC    ");
    for (ac = 0; ac < SRVL_ACS; ac++) {
        SRVL_RD(VTSS_ANA_PGID_PGID(PGID_AGGR + ac), &mask);
        mask = VTSS_X_ANA_PGID_PGID_PGID(mask);
        pr("%-4u  ", ac);
        vtss_srvl_debug_print_mask(pr, mask);
    }
    pr("\n");
    
    vtss_debug_print_header(pr, "Destination Masks");
    vtss_srvl_debug_print_port_header(vtss_state, pr, "PGID  CPU  Queue  ");
    for (pgid = 0; pgid < VTSS_PGID_LUTON26; pgid++) {
        SRVL_RD(VTSS_ANA_PGID_PGID(pgid), &value);
        mask = VTSS_X_ANA_PGID_PGID_PGID(value);
        pr("%-4u  %-3u  %-5u  ", pgid, mask & VTSS_BIT(VTSS_CHIP_PORT_CPU) ? 1 : 0,
           VTSS_X_ANA_PGID_PGID_CPUQ_DST_PGID(value));
        vtss_srvl_debug_print_mask(pr, mask);
    }
    pr("\n");
    
    vtss_debug_print_header(pr, "Flooding PGIDs");
    SRVL_RD(VTSS_ANA_ANA_FLOODING, &value);
    pr("UNICAST    : %u\n", VTSS_X_ANA_ANA_FLOODING_FLD_UNICAST(value));
    pr("MULTICAST  : %u\n", VTSS_X_ANA_ANA_FLOODING_FLD_MULTICAST(value));
    SRVL_RD(VTSS_ANA_ANA_FLOODING_IPMC, &value);
    pr("MC4_CTRL   : %u\n", VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC4_CTRL(value));
    pr("MC4_DATA   : %u\n", VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC4_DATA(value));
    pr("MC6_CTRL   : %u\n", VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL(value));
    pr("MC6_DATA   : %u\n", VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC6_DATA(value));
    pr("\n");

    vtss_srvl_debug_reg_header(pr, "Aggr. Mode");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_COMMON_AGGR_CFG, "AGGR_CFG");
    pr("\n");
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_stp(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32  port;
    BOOL header = 1;

    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        if (vtss_cmn_port2port_no(vtss_state, info, port) == VTSS_PORT_NO_NONE)
            continue;
        if (header)
            vtss_srvl_debug_reg_header(pr, "ANA");
        header = 0;
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_PORT_CFG(port), port, "PORT_CFG");
    }
    if (!header)
        pr("\n");
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_vxlat(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    BOOL header = 1;

    VTSS_RC(vtss_srvl_debug_is1_all(vtss_state, pr, info));
    VTSS_RC(vtss_srvl_debug_es0_all(vtss_state, pr, info));
    VTSS_RC(vtss_srvl_debug_isdx_list(vtss_state, pr, vtss_state->l2.sdx_info.iflow, 0, &header, FALSE));

    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_vlan(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455} */ // Due to VTSS_EXIT_ENTER
    vtss_vid_t        vid;
    vtss_vlan_entry_t *vlan_entry;
    BOOL              header = 1;
    vtss_port_no_t    port_no;
    u32               port, value, mask = 0, fid;
    char              buf[32];

    for (port = 0; port < (VTSS_CHIP_PORTS + 2); port++) {
        if (port < VTSS_CHIP_PORTS) {
            /* Normal ports */
            if ((port_no = vtss_cmn_port2port_no(vtss_state, info, port)) == VTSS_PORT_NO_NONE)
                continue;
            VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        } else {
            /* CPU ports */
            if (!info->full)
                continue;
            VTSS_SPRINTF(buf, "Port %u (CPU)", port);
        }

        vtss_srvl_debug_reg_header(pr, buf);
        if (port != VTSS_CHIP_PORT_CPU_1) {
            vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_VLAN_CFG(port), port, "ANA:VLAN_CFG");
            vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_DROP_CFG(port), port, "ANA:DROP_CFG");
        }
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_REW_PORT_PORT_VLAN_CFG(port), port, "REW:VLAN_CFG");
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_REW_PORT_TAG_CFG(port), port, "REW:TAG_CFG");
        pr("\n");
    }
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_SYS_SYSTEM_VLAN_ETYPE_CFG, "ETYPE_CFG");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_ANA_ADVLEARN, "ADVLEARN");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_ANA_VLANMASK, "VLANMASK");
    pr("\n");
    
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if (!(vlan_entry->flags & VLAN_FLAGS_ENABLED) && !info->full)
            continue;

        SRVL_WR(VTSS_ANA_ANA_TABLES_VLANTIDX, VTSS_F_ANA_ANA_TABLES_VLANTIDX_V_INDEX(vid));
        SRVL_WR(VTSS_ANA_ANA_TABLES_VLANACCESS, 
                VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_CMD_READ));
        if (srvl_vlan_table_idle(vtss_state) != VTSS_RC_OK)
            continue;
        SRVL_RD(VTSS_ANA_ANA_TABLES_VLANACCESS, &value);
        mask = VTSS_X_ANA_ANA_TABLES_VLANACCESS_VLAN_PORT_MASK(value);
        SRVL_RD(VTSS_ANA_ANA_TABLES_VLANTIDX, &value);
#if defined(VTSS_FEATURE_VLAN_SVL)
        SRVL_RD(VTSS_ANA_FID_MAP_FID_MAP(vid), &fid);
        fid = VTSS_X_ANA_FID_MAP_FID_MAP_FID_C_VAL(fid);
#else
        fid = vid;
#endif /* VTSS_FEATURE_VLAN_SVL */
        if (header)
            vtss_srvl_debug_print_port_header(vtss_state, pr, "VID   FID  Lrn  Mir  Flt  Prv  ");
        header = 0;

        pr("%-6u%-5u%-5u%-5u%-5u%-5u", vid, fid,
           value & VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_LEARN_DISABLED ? 0 : 1,
           value & VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_MIRROR ? 1 : 0,
           value & VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_SRC_CHK ? 1 : 0,
           value & VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_PRIV_VLAN ? 1 : 0);
        vtss_srvl_debug_print_mask(pr, mask);

        /* Leave critical region briefly */
        VTSS_EXIT_ENTER();
    }
    if (!header)
        pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_pvlan(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    vtss_srvl_debug_reg_header(pr, "ANA");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_ANA_ISOLATED_PORTS, "ISOLATED_PORTS");
    pr("\n");
    
    return srvl_debug_src_table(vtss_state, pr, info);
}

static vtss_rc srvl_debug_mirror(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    u32 port, value, mask = 0;
    
    /* Calculate ingress mirror mask */
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        SRVL_RD(VTSS_ANA_PORT_PORT_CFG(port), &value);
        if (value & VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA)
            mask |= VTSS_BIT(port);
    }
    vtss_srvl_debug_print_port_header(vtss_state, pr, "Mirror   ");
    pr("Ingress  ");
    vtss_srvl_debug_print_mask(pr, mask);
    SRVL_RD(VTSS_ANA_ANA_EMIRRORPORTS, &mask);
    pr("Egress   ");
    vtss_srvl_debug_print_mask(pr, mask);
    SRVL_RD(VTSS_ANA_ANA_MIRRORPORTS, &mask);
    pr("Ports    ");
    vtss_srvl_debug_print_mask(pr, mask);
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_l2_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VLAN, srvl_debug_vlan, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PVLAN, srvl_debug_pvlan, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MAC_TABLE, srvl_debug_mac_table, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VXLAT, srvl_debug_vxlat, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_AGGR, srvl_debug_aggr, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_STP, srvl_debug_stp, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MIRROR, srvl_debug_mirror, vtss_state, pr, info));

    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc srvl_l2_port_map_set(vtss_state_t *vtss_state)
{
    /* We only need to setup the no of avail pgids */
    vtss_state->l2.pgid_count = (VTSS_PGID_LUTON26 - VTSS_CHIP_PORTS + vtss_state->port_count);
    
    /* And then claim some for flooding */
    VTSS_RC(srvl_flood_conf_set(vtss_state));

    /* Setup flooding PGIDs */
    SRVL_WR(VTSS_ANA_ANA_FLOODING, 
            VTSS_F_ANA_ANA_FLOODING_FLD_UNICAST(PGID_UC) |
            VTSS_F_ANA_ANA_FLOODING_FLD_BROADCAST(PGID_MC) |
            VTSS_F_ANA_ANA_FLOODING_FLD_MULTICAST(PGID_MC));
    
    SRVL_WR(VTSS_ANA_ANA_FLOODING_IPMC, 
            VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC4_CTRL(PGID_MC) |
            VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC4_DATA(PGID_MCIPV4) |
            VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL(PGID_MC) |
            VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC6_DATA(PGID_MCIPV6));

    return VTSS_RC_OK;
}

static vtss_rc srvl_l2_init(vtss_state_t *vtss_state)
{
    vtss_vid_t vid;
    u32        port;
    
    /* Clear MAC table */
    SRVL_WR(VTSS_ANA_ANA_TABLES_MACACCESS,
            VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MAC_CMD_TABLE_CLEAR));

    /* Clear VLAN table */
    SRVL_WR(VTSS_ANA_ANA_TABLES_VLANACCESS,
            VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_CMD_TABLE_CLEAR));
    
        /* Setup chip ports */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        /* Default VLAN port configuration */
        VTSS_RC(srvl_vlan_port_conf_apply(vtss_state, port, 
                                          &vtss_state->l2.vlan_port_conf[VTSS_PORT_NO_START]));
    }

    /* Clear VLAN table masks. This is done after changing the CPU port PVID above 
       to ensure that VRAP access is still working */
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        if (vid == VTSS_VID_DEFAULT) /* Default VLAN includes all ports */
            continue;
        SRVL_WR(VTSS_ANA_ANA_TABLES_VLANTIDX,
                VTSS_F_ANA_ANA_TABLES_VLANTIDX_V_INDEX(vid));
        SRVL_WR(VTSS_ANA_ANA_TABLES_VLANACCESS,
                VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_CMD_WRITE));
        VTSS_RC(srvl_vlan_table_idle(vtss_state));
    }

    /* Setup VLAN configuration */
    VTSS_RC(srvl_vlan_conf_apply(vtss_state, 0));

    /* Setup aggregation mode */
    VTSS_RC(srvl_aggr_mode_set(vtss_state));
    
    /* Set MAC age time to default value */
    VTSS_RC(srvl_mac_table_age_time_set(vtss_state));

    /* Disable learning for frames discarded by VLAN ingress filtering */
    SRVL_WR(VTSS_ANA_ANA_ADVLEARN, VTSS_F_ANA_ANA_ADVLEARN_VLAN_CHK);

    /* Ignore CPU copy flag in DMAC lookup */
    SRVL_WRM_SET(VTSS_ANA_ANA_AGENCTRL, VTSS_F_ANA_ANA_AGENCTRL_IGNORE_DMAC_FLAGS);

    /* Setup frame ageing - fixed value "2 sec" - in 6.5 us units */
    SRVL_WR(VTSS_SYS_SYSTEM_FRM_AGING, 
            VTSS_F_SYS_SYSTEM_FRM_AGING_AGE_TX_ENA | 
            VTSS_F_SYS_SYSTEM_FRM_AGING_MAX_AGE(2*2000000/13));

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_l2_state_t *state = &vtss_state->l2;
    
    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->mac_table_add = srvl_mac_table_add;
        state->mac_table_del = srvl_mac_table_del;
        state->mac_table_get = srvl_mac_table_get;
        state->mac_table_get_next = srvl_mac_table_get_next;
        state->mac_table_age_time_set = srvl_mac_table_age_time_set;
        state->mac_table_age = srvl_mac_table_age;
        state->mac_table_status_get = srvl_mac_table_status_get;
        state->learn_port_mode_set = srvl_learn_port_mode_set;
        state->learn_state_set = srvl_learn_state_set;
        state->mstp_state_set = vtss_cmn_mstp_state_set;
        state->mstp_vlan_msti_set = vtss_cmn_vlan_members_set;
        state->erps_vlan_member_set = vtss_cmn_erps_vlan_member_set;
        state->erps_port_state_set = vtss_cmn_erps_port_state_set;
        state->pgid_table_write = srvl_pgid_table_write;
        state->src_table_write = srvl_src_table_write;
        state->aggr_table_write = srvl_aggr_table_write;
        state->aggr_mode_set = srvl_aggr_mode_set;
        state->pmap_table_write = srvl_pmap_table_write;
        state->vlan_conf_set = srvl_vlan_conf_set;
        state->vlan_port_conf_set = vtss_cmn_vlan_port_conf_set;
        state->vlan_port_conf_update = srvl_vlan_port_conf_update;
        state->vlan_port_members_set = vtss_cmn_vlan_members_set;
        state->vlan_mask_update = srvl_vlan_mask_update;
        state->vlan_tx_tag_set = vtss_cmn_vlan_tx_tag_set;
        state->isolated_vlan_set = vtss_cmn_vlan_members_set;
        state->isolated_port_members_set = srvl_isolated_port_members_set;
        state->flood_conf_set = srvl_flood_conf_set;
        state->ipv4_mc_add = vtss_cmn_ipv4_mc_add;
        state->ipv4_mc_del = vtss_cmn_ipv4_mc_del;
#if defined(VTSS_FEATURE_IPV6_MC_SIP)
        state->ipv6_mc_add = vtss_cmn_ipv6_mc_add;
        state->ipv6_mc_del = vtss_cmn_ipv6_mc_del;
#endif
        state->ip_mc_update = srvl_ip_mc_update;
        state->mirror_port_set = srvl_mirror_port_set;
        state->mirror_ingress_set = srvl_mirror_ingress_set;
        state->mirror_egress_set = srvl_mirror_egress_set;
#ifdef VTSS_FEATURE_MIRROR_CPU
        state->mirror_cpu_ingress_set = srvl_mirror_cpu_ingress_set;
        state->mirror_cpu_egress_set = srvl_mirror_cpu_egress_set;
#endif //VTSS_FEATURE_MIRROR_CPU
        state->eps_port_set = vtss_cmn_eps_port_set;
        state->sflow_port_conf_set         = srvl_sflow_port_conf_set;
        state->sflow_sampling_rate_convert = srvl_sflow_sampling_rate_convert;
        state->vcl_port_conf_set = vtss_srvl_vcap_port_conf_set;
        state->vce_add = vtss_cmn_vce_add;
        state->vce_del = vtss_cmn_vce_del;
        state->vlan_trans_group_add = vtss_cmn_vlan_trans_group_add;
        state->vlan_trans_group_del = vtss_cmn_vlan_trans_group_del;
        state->vlan_trans_group_get = vtss_cmn_vlan_trans_group_get;
        state->vlan_trans_port_conf_set  = vtss_cmn_vlan_trans_port_conf_set;
        state->vlan_trans_port_conf_get  = vtss_cmn_vlan_trans_port_conf_get;
        state->vcap_port_conf_set = srvl_vcap_port_conf_set;
        state->iflow_conf_set = srvl_iflow_conf_set;
        state->ac_count = SRVL_ACS;
        state->sdx_info.max_count = SRVL_EVC_CNT;
        if (state->sdx_info.max_count > VTSS_SRVL_SDX_CNT)
            state->sdx_info.max_count = VTSS_SRVL_SDX_CNT;
        break;
    case VTSS_INIT_CMD_INIT:
        if (!vtss_state->warm_start_cur) {
            VTSS_RC(srvl_l2_init(vtss_state));
        }
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(srvl_l2_port_map_set(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_OCELOT */
