// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L2
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

/* Convert to PGID in chip */
static u32 lan966x_chip_pgid(vtss_state_t *vtss_state, u32 pgid)
{
    if (pgid < vtss_state->port_count) {
        return VTSS_CHIP_PORT(pgid);
    } else {
        return (pgid + VTSS_CHIP_PORTS - vtss_state->port_count);
    }
}

/* Convert from PGID in chip */
static u32 lan966x_vtss_pgid(vtss_state_t *vtss_state, u32 pgid)
{
    vtss_port_no_t port_no;

    if (pgid < VTSS_CHIP_PORTS) {
        for (port_no = 0; port_no < vtss_state->port_count; port_no++)
            if (VTSS_CHIP_PORT(port_no) == pgid)
                break;
        return port_no;
    } else {
        return (vtss_state->port_count + pgid - VTSS_CHIP_PORTS);
    }
}

static vtss_rc lan966x_pgid_mask_write(vtss_state_t *vtss_state,
                                       u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE],
                                       BOOL cpu_copy, vtss_packet_rx_queue_t cpu_queue)
{
    u32 mask = vtss_lan966x_port_mask(vtss_state, member);
    u32 queue = 0;

    if (cpu_copy) {
        mask |= VTSS_BIT(VTSS_CHIP_PORT_CPU);
        queue = cpu_queue;
    }
    REG_WR(ANA_PGID(pgid),
           ANA_PGID_PGID(mask) |
           ANA_PGID_CPUQ_DST_PGID(queue));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_pgid_table_write(vtss_state_t *vtss_state,
                                        u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[pgid];

    return lan966x_pgid_mask_write(vtss_state, lan966x_chip_pgid(vtss_state, pgid), member,
                                   pgid_entry->cpu_copy, pgid_entry->cpu_queue);
}

static vtss_rc lan966x_pgid_update(vtss_state_t *vtss_state, u32 pgid, BOOL member[])
{
    vtss_port_no_t    port_no;
    vtss_pgid_entry_t *pgid_entry;

    pgid = lan966x_vtss_pgid(vtss_state, pgid);
    pgid_entry = &vtss_state->l2.pgid_table[pgid];
    pgid_entry->resv = 1;
    pgid_entry->references = 1;
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        pgid_entry->member[port_no] = member[port_no];
    }
    return lan966x_pgid_table_write(vtss_state, pgid, member);
}

static vtss_rc lan966x_aggr_table_write(vtss_state_t *vtss_state,
                                        u32 ac, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return lan966x_pgid_mask_write(vtss_state, PGID_AGGR + ac, member, 0, 0);
}

static vtss_rc lan966x_src_table_write(vtss_state_t *vtss_state,
                                       vtss_port_no_t port_no, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return lan966x_pgid_mask_write(vtss_state, PGID_SRC + VTSS_CHIP_PORT(port_no), member, 0, 0);
}

static vtss_rc lan966x_aggr_mode_set(vtss_state_t *vtss_state)
{
    vtss_aggr_mode_t *mode = &vtss_state->l2.aggr_mode;

    REG_WR(ANA_AGGR_CFG,
           (mode->sip_dip_enable ? ANA_AGGR_CFG_AC_IP4_SIPDIP_ENA_M : 0) |
           (mode->sport_dport_enable ? ANA_AGGR_CFG_AC_IP4_TCPUDP_ENA_M : 0) |
           (mode->dmac_enable ? ANA_AGGR_CFG_AC_DMAC_ENA_M : 0) |
           (mode->smac_enable ? ANA_AGGR_CFG_AC_SMAC_ENA_M : 0));
    return VTSS_RC_OK;
}

static vtss_rc lan966x_pmap_table_write(vtss_state_t *vtss_state,
                                        vtss_port_no_t port_no, vtss_port_no_t l_port_no)
{
    REG_WRM(ANA_PORT_CFG(VTSS_CHIP_PORT(port_no)),
             ANA_PORT_CFG_PORTID_VAL(VTSS_CHIP_PORT(l_port_no)),
             ANA_PORT_CFG_PORTID_VAL_M);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_learn_state_set(vtss_state_t *vtss_state,
                                       const BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_port_no_t port_no;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        REG_WRM_CTL(ANA_PORT_CFG(VTSS_CHIP_PORT(port_no)),
                    member[port_no], ANA_PORT_CFG_LEARN_ENA_M);
    }
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  MAC address table
 * ================================================================= */
#define MAC_TYPE_NORMAL  0 /* Normal entry */
#define MAC_TYPE_LOCKED  1 /* Locked entry */
#define MAC_TYPE_IPV4_MC 2 /* IPv4 MC entry */
#define MAC_TYPE_IPV6_MC 3 /* IPv6 MC entry */

static vtss_rc lan966x_mac_table_idle(vtss_state_t *vtss_state)
{
    u32 cmd, cnt = 0;

    do {
        REG_RD(ANA_MACACCESS, &cmd);
        cnt++;
        if (cnt == 100000) {
            VTSS_E("Timeout! cmd =  %u", cmd);
        }
    } while (ANA_MACACCESS_MAC_TABLE_CMD_X(cmd) != MACACCESS_CMD_IDLE);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mac_table_add(vtss_state_t *vtss_state,
                                     const vtss_mac_table_entry_t *const entry, u32 pgid)
{
    u32  mach, macl, mask, idx = 0, aged = 0, fwd_kill = 0, type;
    BOOL copy_to_cpu = entry->copy_to_cpu_smac;

    vtss_mach_macl_get(&entry->vid_mac, &mach, &macl);
    VTSS_D("address 0x%08x%08x", mach, macl);

    if (pgid == VTSS_PGID_NONE) {
        /* IPv4/IPv6 MC entry, encode port mask directly */
        mask = vtss_lan966x_port_mask(vtss_state, vtss_state->l2.pgid_table[pgid].member);
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
        idx = lan966x_chip_pgid(vtss_state, pgid);
        type = (entry->locked ? MAC_TYPE_LOCKED : MAC_TYPE_NORMAL);
    }

    /* Insert/learn new entry into the MAC table  */
    REG_WR(ANA_MACHDATA, mach);
    REG_WR(ANA_MACLDATA, macl);
    REG_WR(ANA_MACACCESS,
           (copy_to_cpu ? ANA_MACACCESS_MAC_CPU_COPY_M : 0) |
           (fwd_kill ? ANA_MACACCESS_SRC_KILL_M : 0) |
           (aged ? ANA_MACACCESS_AGED_FLAG_M : 0) |
           ANA_MACACCESS_VALID_M |
           ANA_MACACCESS_ENTRYTYPE(type) |
           ANA_MACACCESS_DEST_IDX(idx) |
           ANA_MACACCESS_MAC_TABLE_CMD(MACACCESS_CMD_LEARN));

    /* Wait until MAC operation is finished */
    return lan966x_mac_table_idle(vtss_state);
}

static u32 lan966x_mac_type(const vtss_vid_mac_t *vid_mac)
{
    return (VTSS_MAC_IPV4_MC(vid_mac->mac.addr) ? MAC_TYPE_IPV4_MC :
            VTSS_MAC_IPV6_MC(vid_mac->mac.addr) ? MAC_TYPE_IPV6_MC : MAC_TYPE_NORMAL);
}

static vtss_rc lan966x_mac_table_cmd(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac, u32 type, u32 cmd)
{
    u32 mach, macl;

    vtss_mach_macl_get(vid_mac, &mach, &macl);
    VTSS_D("cmd: %u, address 0x%08x%08x", cmd, mach, macl);

    /* Run command for MAC entry */
    REG_WR(ANA_MACHDATA, mach);
    REG_WR(ANA_MACLDATA, macl);
    REG_WR(ANA_MACACCESS,
           ANA_MACACCESS_VALID_M |
           ANA_MACACCESS_ENTRYTYPE(type) |
           ANA_MACACCESS_MAC_TABLE_CMD(cmd));

    /* Wait until MAC operation is finished */
    return lan966x_mac_table_idle(vtss_state);
}

static vtss_rc lan966x_mac_table_del(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac)
{
    u32 type = lan966x_mac_type(vid_mac);

    VTSS_RC(lan966x_mac_table_cmd(vtss_state, vid_mac, type, MACACCESS_CMD_FORGET));
    if (type != MAC_TYPE_NORMAL) {
        /* IPMC entries may be encoded as NORMAL */
        VTSS_RC(lan966x_mac_table_cmd(vtss_state, vid_mac, MAC_TYPE_NORMAL, MACACCESS_CMD_FORGET));
    }

    /* Wait until MAC operation is finished */
    return lan966x_mac_table_idle(vtss_state);
}

static vtss_rc lan966x_mac_table_result(vtss_state_t *vtss_state,
                                        vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32               value, mask, mach, macl, idx, type;
    vtss_port_no_t    port_no;
    vtss_pgid_entry_t *pgid_entry;
    u8                *mac = &entry->vid_mac.mac.addr[0];

    REG_RD(ANA_MACACCESS, &value);

    /* Check if entry is valid */
    if (!(value & ANA_MACACCESS_VALID_M)) {
        VTSS_D("not valid");
        return VTSS_RC_ERROR;
    }

    type = ANA_MACACCESS_ENTRYTYPE_X(value);
    idx = ANA_MACACCESS_DEST_IDX_X(value);
    entry->aged = VTSS_BOOL(value & ANA_MACACCESS_AGED_FLAG_M);
    entry->copy_to_cpu = 0;
    entry->copy_to_cpu_smac = VTSS_BOOL(value & ANA_MACACCESS_MAC_CPU_COPY_M);
    entry->locked = (type == MAC_TYPE_NORMAL ? 0 : 1);

    REG_RD(ANA_MACHDATA, &mach);
    REG_RD(ANA_MACLDATA, &macl);
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
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            pgid_entry->member[port_no] = VTSS_BOOL(mask & (1 << VTSS_CHIP_PORT(port_no)));
        }
    } else {
        *pgid = lan966x_vtss_pgid(vtss_state, idx);
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

static vtss_rc lan966x_mac_table_get(vtss_state_t *vtss_state,
                                     vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    vtss_rc rc;
    u32     type = lan966x_mac_type(&entry->vid_mac);

    VTSS_RC(lan966x_mac_table_cmd(vtss_state, &entry->vid_mac, type, MACACCESS_CMD_READ));
    rc = lan966x_mac_table_result(vtss_state, entry, pgid);
    if (type != MAC_TYPE_NORMAL && rc != VTSS_RC_OK) {
        /* IPMC entries may be encoded as NORMAL */
        VTSS_RC(lan966x_mac_table_cmd(vtss_state, &entry->vid_mac, MAC_TYPE_NORMAL, MACACCESS_CMD_READ));
        rc = lan966x_mac_table_result(vtss_state, entry, pgid);
    }
    return rc;
}

static vtss_rc lan966x_mac_table_get_next(vtss_state_t *vtss_state,
                                          vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    VTSS_RC(lan966x_mac_table_cmd(vtss_state, &entry->vid_mac, MAC_TYPE_NORMAL, MACACCESS_CMD_GET_NEXT));
    return lan966x_mac_table_result(vtss_state, entry, pgid);
}

static vtss_rc lan966x_mac_table_age_time_set(vtss_state_t *vtss_state)
{
    u32 time;

    /* Scan two times per age time */
    time = (vtss_state->l2.mac_age_time/2);
    if (time > 0xfffff)
        time = 0xfffff;
    REG_WR(ANA_AUTOAGE, ANA_AUTOAGE_AGE_PERIOD(time));
    return VTSS_RC_OK;
}

/* Maximum FID value */
#define LAN966X_FID_MAX 63

static vtss_rc lan966x_mac_table_age(vtss_state_t *vtss_state,
                                     BOOL             pgid_age,
                                     u32              pgid,
                                     BOOL             vid_age,
                                     const vtss_vid_t vid)
{
    vtss_vid_t fid = vtss_state->l2.vlan_table[vid].conf.fid;

    if (fid == 0 || fid > LAN966X_FID_MAX) {
        fid = vid;
    }

    /* Selective aging */
    REG_WR(ANA_ANAGEFIL,
           (pgid_age ? ANA_ANAGEFIL_PID_EN_M : 0) |
           (vid_age ? ANA_ANAGEFIL_VID_EN_M : 0) |
           ANA_ANAGEFIL_PID_VAL(lan966x_chip_pgid(vtss_state, pgid)) |
           ANA_ANAGEFIL_VID_VAL(fid));

    /* Do the aging */
    REG_WR(ANA_MACACCESS,
           ANA_MACACCESS_MAC_TABLE_CMD(MACACCESS_CMD_AGE));
    VTSS_RC(lan966x_mac_table_idle(vtss_state));

    /* Clear age filter again to avoid affecting automatic ageing */
    REG_WR(ANA_ANAGEFIL, 0);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mac_table_status_get(vtss_state_t *vtss_state,
                                            vtss_mac_table_status_t *status)
{
    u32 value;

    /* Read and clear sticky register */
    REG_RD(ANA_ANEVENTS, &value);
    REG_WR(ANA_ANEVENTS,
           value & (ANA_ANEVENTS_AUTO_MOVED_M |
                    ANA_ANEVENTS_AUTO_LEARNED_M |
                    ANA_ANEVENTS_LEARN_REMOVE_M |
                    ANA_ANEVENTS_AGED_ENTRY_M));

    /* Detect events */
    status->learned = VTSS_BOOL(value & ANA_ANEVENTS_AUTO_LEARNED_M);
    status->replaced = VTSS_BOOL(value & ANA_ANEVENTS_LEARN_REMOVE_M);
    status->moved = VTSS_BOOL(value & ANA_ANEVENTS_AUTO_MOVED_M);
    status->aged = VTSS_BOOL(value & ANA_ANEVENTS_AGED_ENTRY_M);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_learn_port_mode_set(vtss_state_t *vtss_state,
                                           const vtss_port_no_t port_no)
{
    vtss_learn_mode_t *mode = &vtss_state->l2.learn_mode[port_no];
    u32               value, port = VTSS_CHIP_PORT(port_no);

    REG_WRM(ANA_PORT_CFG(port),
            (mode->discard ? ANA_PORT_CFG_LEARNDROP_M : 0) |
            (mode->automatic ? ANA_PORT_CFG_LEARNAUTO_M : ANA_PORT_CFG_LOCKED_PORTMOVE_CPU_M) |
            (mode->cpu ? ANA_PORT_CFG_LEARNCPU_M : 0) |
            ANA_PORT_CFG_LOCKED_PORTMOVE_DROP_M,
            ANA_PORT_CFG_LEARNDROP_M |
            ANA_PORT_CFG_LEARNAUTO_M |
            ANA_PORT_CFG_LOCKED_PORTMOVE_CPU_M |
            ANA_PORT_CFG_LEARNCPU_M |
            ANA_PORT_CFG_LOCKED_PORTMOVE_DROP_M);

    if (!mode->automatic) {
        /* Flush entries previously learned on port to avoid continuous refreshing */
        REG_RD(ANA_PORT_CFG(port), &value);
        REG_WRM_CLR(ANA_PORT_CFG(port), ANA_PORT_CFG_LEARN_ENA_M);
        VTSS_RC(lan966x_mac_table_age(vtss_state, 1, port_no, 0, 0));
        VTSS_RC(lan966x_mac_table_age(vtss_state, 1, port_no, 0, 0));
        REG_WR(ANA_PORT_CFG(port), value);
    }
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - VLAN
 * ================================================================= */

static vtss_rc lan966x_vlan_conf_apply(vtss_state_t *vtss_state, BOOL ports)
{
    u32            etype = vtss_state->l2.vlan_conf.s_etype;
    vtss_port_no_t port_no;

    /* BZ4513: Type 0x8100 can not be used so we use 0x88a8 */
    if (etype == VTSS_ETYPE_TAG_C)
        etype = VTSS_ETYPE_TAG_S;
    REG_WR(ANA_VLAN_ETYPE_CFG, ANA_VLAN_ETYPE_CFG_S_TAG_VAL(etype));

    /* Update ports */
    for (port_no = 0; ports && port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(vtss_cmn_vlan_port_conf_set(vtss_state, port_no));
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_vlan_conf_set(vtss_state_t *vtss_state)
{
    return lan966x_vlan_conf_apply(vtss_state, 1);
}

/* Types for REW:TAG_CFG:TAG_CFG */
#define TAG_CFG_DISABLE       0 /* Port tagging disabled */
#define TAG_CFG_ALL_NPV_NNUL  1 /* Tag all frames, except when VID=PORT_VLAN_CFG.PORT_VID or VID=0 */
#define TAG_CFG_ALL_NNUL      2 /* Tag all frames, except when VID=0 */
#define TAG_CFG_ALL           3 /* Tag all frames */

/* Types for REW_PORT:TAG_CFG:TAG_TPID_CFG */
#define TAG_TPID_CFG_0x8100   0  /* Use 0x8100 */
#define TAG_TPID_CFG_0x88A8   1  /* Use 0x88A8 */
#define TAG_TPID_CFG_PTPID    2  /* Use custom from PORT_VLAN_CFG.PORT_TPID */
#define TAG_TPID_CFG_PTPID_NC 3  /* As above, but unless ingress tag was a C-tag */

static vtss_rc lan966x_vlan_port_conf_apply(vtss_state_t *vtss_state,
                                            u32                   port,
                                            vtss_vlan_port_conf_t *conf)
{
    u32                   tpid = TAG_TPID_CFG_0x8100;
    u32                   value, etype = vtss_state->l2.vlan_conf.s_etype;
    vtss_vid_t            uvid = conf->untagged_vid;
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
    REG_WRM(ANA_VLAN_CFG(port),
            ANA_VLAN_CFG_VLAN_VID(conf->pvid) |
            (aware ? ANA_VLAN_CFG_VLAN_AWARE_ENA_M : 0) |
            ANA_VLAN_CFG_VLAN_POP_CNT(aware ? 1 : 0),
            ANA_VLAN_CFG_VLAN_VID_M |
            ANA_VLAN_CFG_VLAN_AWARE_ENA_M |
            ANA_VLAN_CFG_VLAN_POP_CNT_M);

    /* Drop Configuration based on port type and frame type */
    tagged = (conf->frame_type == VTSS_VLAN_FRAME_TAGGED);
    untagged = (conf->frame_type == VTSS_VLAN_FRAME_UNTAGGED);
    value = ANA_DROP_CFG_DROP_MC_SMAC_ENA_M;
    if (tagged && aware) {
        /* Discard untagged and priority-tagged if aware and tagged-only allowed */
        value |= ANA_DROP_CFG_DROP_UNTAGGED_ENA_M;
        value |= ANA_DROP_CFG_DROP_PRIO_C_TAGGED_ENA_M;
        value |= ANA_DROP_CFG_DROP_PRIO_S_TAGGED_ENA_M;
    }
    if ((untagged && c_port) || (tagged && s_port)) {
        /* Discard C-tagged if C-port and untagged-only OR S-port and tagged-only */
        value |= ANA_DROP_CFG_DROP_C_TAGGED_ENA_M;
    }
    if ((untagged && s_port) || (tagged && c_port)) {
        /* Discard S-tagged if S-port and untagged-only OR C-port and tagged-only */
        value |= ANA_DROP_CFG_DROP_S_TAGGED_ENA_M;
    }
    REG_WR(ANA_DROP_CFG(port), value);

    /* Ingress filtering */
    REG_WRM_CTL(ANA_VLANMASK, conf->ingress_filter, 1 << port);

    /* Rewriter VLAN tag configuration */
    value = (REW_TAG_CFG_TAG_TPID_CFG(tpid) |
             REW_TAG_CFG_TAG_CFG(
                 uvid == VTSS_VID_ALL ? TAG_CFG_DISABLE :
                 uvid == VTSS_VID_NULL ? TAG_CFG_ALL : TAG_CFG_ALL_NPV_NNUL));
    REG_WRM(REW_TAG_CFG(port), value,
            REW_TAG_CFG_TAG_TPID_CFG_M |
            REW_TAG_CFG_TAG_CFG_M);
    REG_WRM(REW_PORT_VLAN_CFG(port),
            REW_PORT_VLAN_CFG_PORT_TPID(conf->s_etype ? conf->s_etype : etype) |
            REW_PORT_VLAN_CFG_PORT_VID(uvid),
            REW_PORT_VLAN_CFG_PORT_TPID_M |
            REW_PORT_VLAN_CFG_PORT_VID_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_vlan_port_conf_update(vtss_state_t *vtss_state,
                                             vtss_port_no_t port_no, vtss_vlan_port_conf_t *conf)
{
    /* Update maximum tags allowed */
    VTSS_RC(vtss_lan966x_port_max_tags_set(vtss_state, port_no));
    return lan966x_vlan_port_conf_apply(vtss_state, VTSS_CHIP_PORT(port_no), conf);
}

static vtss_rc lan966x_vlan_table_idle(vtss_state_t *vtss_state)
{
    u32 value;

    do {
        REG_RD(ANA_VLANACCESS, &value);
    } while (ANA_VLANACCESS_VLAN_TBL_CMD_X(value) != VLANACCESS_CMD_IDLE);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_vlan_mask_update(vtss_state_t *vtss_state,
                                        vtss_vid_t vid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_vlan_entry_t    *vlan_entry = &vtss_state->l2.vlan_table[vid];
    vtss_vlan_vid_conf_t *conf = &vlan_entry->conf;
    BOOL                 learning = (vlan_entry->evc_learning && conf->learning ? 1 : 0);

    /* Index and properties */
    REG_WR(ANA_VLANTIDX,
           ANA_VLANTIDX_V_INDEX(vid) |
           (vlan_entry->isolated ? ANA_VLANTIDX_VLAN_PRIV_VLAN_M : 0) |
           (learning ? 0 : ANA_VLANTIDX_VLAN_LEARN_DISABLED_M) |
           (conf->mirror ? ANA_VLANTIDX_VLAN_MIRROR_M : 0));

    /* VLAN mask */
    REG_WR(ANA_VLANACCESS,
           ANA_VLANACCESS_VLAN_PORT_MASK(vtss_lan966x_port_mask(vtss_state, member)) |
           ANA_VLANACCESS_VLAN_TBL_CMD(VLANACCESS_CMD_WRITE));

    /* FID */
    REG_WR(ANA_FID_MAP(vid),
           ANA_FID_MAP_FID_VAL(conf->fid > LAN966X_FID_MAX ? 0 : conf->fid));

    return lan966x_vlan_table_idle(vtss_state);
}

/* ================================================================= *
 *  Layer 2 - PVLAN / Isolated ports
 * ================================================================= */

static vtss_rc lan966x_isolated_port_members_set(vtss_state_t *vtss_state)
{
    u32 mask = vtss_lan966x_port_mask(vtss_state, vtss_state->l2.isolated_port);

    /* Isolated ports: cleared (add CPU as not isolated) */
    mask = ((~mask) & VTSS_CHIP_PORT_MASK) | VTSS_BIT(VTSS_CHIP_PORT_CPU);
    REG_WR(ANA_ISOLATED_PORTS, mask);
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - IP Multicast
 * ================================================================= */

static vtss_rc lan966x_flood_conf_set(vtss_state_t *vtss_state)
{
    u32 pgid = (vtss_state->l2.ipv6_mc_scope ? PGID_MCIPV6 : PGID_MC);

    /* Unicast flood mask */
    VTSS_RC(lan966x_pgid_update(vtss_state, PGID_UC, vtss_state->l2.uc_flood));

    /* Multicast flood mask */
    VTSS_RC(lan966x_pgid_update(vtss_state, PGID_MC, vtss_state->l2.mc_flood));

    /* IPv4 flood mask */
    VTSS_RC(lan966x_pgid_update(vtss_state, PGID_MCIPV4, vtss_state->l2.ipv4_mc_flood));

    /* IPv6 flood mask */
    VTSS_RC(lan966x_pgid_update(vtss_state, PGID_MCIPV6, vtss_state->l2.ipv6_mc_flood));

    /* IPv6 flood scope */
    REG_WRM(ANA_FLOODING_IPMC,
            ANA_FLOODING_IPMC_FLD_MC6_CTRL(pgid),
            ANA_FLOODING_IPMC_FLD_MC6_CTRL_M);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ip_mc_update(vtss_state_t *vtss_state,
                                    vtss_ipmc_data_t *ipmc, vtss_ipmc_cmd_t cmd)
{
    // TBD
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - Mirror
 * ================================================================= */

static vtss_rc lan966x_mirror_cpu_ingress_set(vtss_state_t *vtss_state)
{
    REG_WRM_CTL(ANA_PORT_CFG(VTSS_CHIP_PORT_CPU), vtss_state->l2.mirror_cpu_ingress, ANA_PORT_CFG_SRC_MIRROR_ENA_M);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mirror_cpu_egress_set(vtss_state_t *vtss_state)
{
    REG_WRM_CTL(ANA_AGENCTRL, vtss_state->l2.mirror_cpu_egress, ANA_AGENCTRL_MIRROR_CPU_M);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mirror_port_set(vtss_state_t *vtss_state)
{
    BOOL           member[VTSS_PORT_ARRAY_SIZE];
    vtss_port_no_t port_no;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        member[port_no] = (port_no == vtss_state->l2.mirror_conf.port_no);
    }
    REG_WR(ANA_MIRRORPORTS, vtss_lan966x_port_mask(vtss_state, member));

    /* Update all VLANs */
    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc lan966x_mirror_ingress_set(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    u32            port;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        REG_WRM_CTL(ANA_PORT_CFG(port), vtss_state->l2.mirror_ingress[port_no], ANA_PORT_CFG_SRC_MIRROR_ENA_M);
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mirror_egress_set(vtss_state_t *vtss_state)
{
    REG_WR(ANA_EMIRRORPORTS, vtss_lan966x_port_mask(vtss_state, vtss_state->l2.mirror_egress));
    return VTSS_RC_OK;
}

#if 0
static vtss_rc lan966x_vcap_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_iflow_conf_set(vtss_state_t *vtss_state, const vtss_iflow_id_t id)
{
    return VTSS_RC_OK;
}
#endif

/* ================================================================= *
 *  SFLOW
 * ================================================================= */

/* sFlow H/W-related min/max */
#define LAN966X_SFLOW_MIN_SAMPLE_RATE    0 /**< Minimum allowable sampling rate for sFlow */
#define LAN966X_SFLOW_MAX_SAMPLE_RATE 4095 /**< Maximum allowable sampling rate for sFlow */

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

static u32 lan966x_sflow_hw_rate(const u32 desired_sw_rate, u32 *const realizable_sw_rate)
{
    u32 hw_rate = desired_sw_rate ? VTSS_ROUNDING_DIVISION(LAN966X_SFLOW_MAX_SAMPLE_RATE + 1, desired_sw_rate) : 0;
    hw_rate = (hw_rate > LAN966X_SFLOW_MIN_SAMPLE_RATE ? hw_rate - 1 : hw_rate);
    *realizable_sw_rate = VTSS_ROUNDING_DIVISION(LAN966X_SFLOW_MAX_SAMPLE_RATE + 1, hw_rate + 1);
    return hw_rate;
}

static vtss_rc lan966x_sflow_sampling_rate_convert(struct vtss_state_s *const state,
                                                   const BOOL power2, const u32 rate_in, u32 *const rate_out)
{
    u32 modified_rate_in;
    // Could happen that two threads call this function simultaneously at boot, but we take the risk.
    // Once sflow_max_power_of_two has been computed, it's no longer a problem with simultaneous access.
    u32 sflow_max_power_of_two = state->l2.sflow_max_power_of_two;

    if (sflow_max_power_of_two == 0) {
        sflow_max_power_of_two = next_power_of_two(LAN966X_SFLOW_MAX_SAMPLE_RATE);
        if ((LAN966X_SFLOW_MAX_SAMPLE_RATE & sflow_max_power_of_two) == 0) {
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

    (void)lan966x_sflow_hw_rate(modified_rate_in, rate_out);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_sflow_port_conf_set(vtss_state_t *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const vtss_sflow_port_conf_t *const new_conf)
{
    u32 hw_rate, value;
    vtss_sflow_port_conf_t *cur_conf = &vtss_state->l2.sflow_conf[port_no];
    vtss_sflow_type_t type = (new_conf->sampling_rate == 0 ? VTSS_SFLOW_TYPE_NONE : new_conf->type);

    *cur_conf = *new_conf;
    hw_rate = lan966x_sflow_hw_rate(new_conf->sampling_rate, &cur_conf->sampling_rate);
    value  = ANA_SFLOW_CFG_SF_RATE(hw_rate);
    value |= (type == VTSS_SFLOW_TYPE_ALL || type == VTSS_SFLOW_TYPE_RX ? ANA_SFLOW_CFG_SF_SAMPLE_RX_M : 0);
    value |= (type == VTSS_SFLOW_TYPE_ALL || type == VTSS_SFLOW_TYPE_TX ? ANA_SFLOW_CFG_SF_SAMPLE_TX_M : 0);
    REG_WR(ANA_SFLOW_CFG(VTSS_CHIP_PORT(port_no)), value);
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

vtss_rc vtss_lan966x_l2_debug_print(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_l2_port_map_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_l2_init(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_l2_state_t *state = &vtss_state->l2;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->mac_table_add = lan966x_mac_table_add;
        state->mac_table_del = lan966x_mac_table_del;
        state->mac_table_get = lan966x_mac_table_get;
        state->mac_table_get_next = lan966x_mac_table_get_next;
        state->mac_table_age_time_set = lan966x_mac_table_age_time_set;
        state->mac_table_age = lan966x_mac_table_age;
        state->mac_table_status_get = lan966x_mac_table_status_get;
        state->learn_port_mode_set = lan966x_learn_port_mode_set;
        state->learn_state_set = lan966x_learn_state_set;
        state->mstp_state_set = vtss_cmn_mstp_state_set;
        state->mstp_vlan_msti_set = vtss_cmn_vlan_members_set;
        state->erps_vlan_member_set = vtss_cmn_erps_vlan_member_set;
        state->erps_port_state_set = vtss_cmn_erps_port_state_set;
        state->pgid_table_write = lan966x_pgid_table_write;
        state->src_table_write = lan966x_src_table_write;
        state->aggr_table_write = lan966x_aggr_table_write;
        state->aggr_mode_set = lan966x_aggr_mode_set;
        state->pmap_table_write = lan966x_pmap_table_write;
        state->vlan_conf_set = lan966x_vlan_conf_set;
        state->vlan_port_conf_set = vtss_cmn_vlan_port_conf_set;
        state->vlan_port_conf_update = lan966x_vlan_port_conf_update;
        state->vlan_port_members_set = vtss_cmn_vlan_members_set;
        state->vlan_mask_update = lan966x_vlan_mask_update;
        state->vlan_tx_tag_set = vtss_cmn_vlan_tx_tag_set;
        state->isolated_vlan_set = vtss_cmn_vlan_members_set;
        state->isolated_port_members_set = lan966x_isolated_port_members_set;
        state->flood_conf_set = lan966x_flood_conf_set;
        state->ipv4_mc_add = vtss_cmn_ipv4_mc_add;
        state->ipv4_mc_del = vtss_cmn_ipv4_mc_del;
        state->ipv6_mc_add = vtss_cmn_ipv6_mc_add;
        state->ipv6_mc_del = vtss_cmn_ipv6_mc_del;
        state->ip_mc_update = lan966x_ip_mc_update;
        state->mirror_port_set = lan966x_mirror_port_set;
        state->mirror_ingress_set = lan966x_mirror_ingress_set;
        state->mirror_egress_set = lan966x_mirror_egress_set;
        state->mirror_cpu_ingress_set = lan966x_mirror_cpu_ingress_set;
        state->mirror_cpu_egress_set = lan966x_mirror_cpu_egress_set;
        state->eps_port_set = vtss_cmn_eps_port_set;
        state->sflow_port_conf_set         = lan966x_sflow_port_conf_set;
        state->sflow_sampling_rate_convert = lan966x_sflow_sampling_rate_convert;
        // TBD: state->vcl_port_conf_set = vtss_lan966x_vcap_port_conf_set;
        state->vce_add = vtss_cmn_vce_add;
        state->vce_del = vtss_cmn_vce_del;
        state->vlan_trans_group_add = vtss_cmn_vlan_trans_group_add;
        state->vlan_trans_group_del = vtss_cmn_vlan_trans_group_del;
        state->vlan_trans_group_get = vtss_cmn_vlan_trans_group_get;
        state->vlan_trans_port_conf_set  = vtss_cmn_vlan_trans_port_conf_set;
        state->vlan_trans_port_conf_get  = vtss_cmn_vlan_trans_port_conf_get;
        // TBD: state->vcap_port_conf_set = lan966x_vcap_port_conf_set;
        // TBD: state->iflow_conf_set = lan966x_iflow_conf_set;
        state->ac_count = LAN966X_ACS;
        // TBD: state->sdx_info.max_count = LAN966X_EVC_CNT;
        // TBD: if (state->sdx_info.max_count > VTSS_LAN966X_SDX_CNT)
        // TBD      state->sdx_info.max_count = VTSS_LAN966X_SDX_CNT;
        break;

    case VTSS_INIT_CMD_INIT:
        if (!vtss_state->warm_start_cur) {
            VTSS_RC(lan966x_l2_init(vtss_state));
        }
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(lan966x_l2_port_map_set(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
