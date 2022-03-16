// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_VCAP
#include "vtss_luton26_cil.h"

#if defined(VTSS_ARCH_LUTON26)

/* - CIL functions ------------------------------------------------- */

/* TCAM entries */
enum vtss_tcam_sel {
    VTSS_TCAM_SEL_ENTRY   = VTSS_BIT(0),
    VTSS_TCAM_SEL_ACTION  = VTSS_BIT(1),
    VTSS_TCAM_SEL_COUNTER = VTSS_BIT(2),
    VTSS_TCAM_SEL_ALL     = VTSS_BITMASK(3),
}; 

enum vtss_tcam_cmd {
    VTSS_TCAM_CMD_WRITE       = 0, /* Copy from Cache to TCAM */
    VTSS_TCAM_CMD_READ        = 1, /* Copy from TCAM to Cache */
    VTSS_TCAM_CMD_MOVE_UP     = 2, /* Move <count> up */
    VTSS_TCAM_CMD_MOVE_DOWN   = 3, /* Move <count> down */
    VTSS_TCAM_CMD_INITIALIZE  = 4, /* Write all (from cache) */
};

enum vtss_tcam_bank {
    VTSS_TCAM_S1 = 0,           /* S1 */
    VTSS_TCAM_S2,               /* S2 */
    VTSS_TCAM_ES0               /* ES0 */
};

typedef struct {
    u32 target;                 /* Target offset */
    u16 entries;                /* # of entries */
    u16 actions;                /* # of actions */
    u8  entry_width;            /* Width of entry (in dwords) */
    u8  action_width;           /* Width of entry (in dwords) */
} tcam_props_t;

#define BITS_TO_DWORD(x) (1+((x-1)/32))

static const tcam_props_t tcam_info[] = {
    [VTSS_TCAM_S1] = {
        .target = VTSS_TO_S1,
        .entries = VTSS_L26_IS1_CNT,
        .actions = VTSS_L26_IS1_CNT + 1,
        .entry_width = BITS_TO_DWORD(184), /* 188 - 2 from TG_DAT */
        .action_width = BITS_TO_DWORD(60),
    },
    [VTSS_TCAM_S2] = {
        .target = VTSS_TO_S2,
        .entries = VTSS_L26_IS2_CNT,
        .actions =  VTSS_L26_IS2_CNT + 28,
        .entry_width = BITS_TO_DWORD(195), /* 196 - 1 from TG_DAT */
        .action_width = BITS_TO_DWORD(46),
    },
    [VTSS_TCAM_ES0] = {
        .target = VTSS_TO_ES0,
        .entries = VTSS_L26_ES0_CNT,
        .actions = VTSS_L26_ES0_CNT + 26,
        .entry_width = BITS_TO_DWORD(28), /* 29 - 1 from TG_DAT */
        .action_width = BITS_TO_DWORD(37),
    },
};

#define VTSS_TCAM_ENTRY_WIDTH 8 /* Max entry width (32bit words) */

#define L26_ACL_FIELD(off, wid, val, msk, ent_bits, msk_bits)          \
    {                                                                  \
        vtss_bs_set(ent_bits, off, wid, val);                          \
        vtss_bs_set(msk_bits, off, wid, msk);                          \
    }

#define L26_ACL_CFIELD(off, wid, val, msk, ent_bits, msk_bits)         \
    {                                                                  \
        if(msk)                                                        \
            L26_ACL_FIELD(off, wid, val, msk, ent_bits, msk_bits);     \
    }

#define L26_ACL_BITSET(off, val, ent_bits, msk_bits)                   \
    {                                                                  \
        vtss_bs_set(ent_bits, off, 1, val);                            \
        vtss_bs_set(msk_bits, off, 1, 1);                              \
    }

#define L26_ACL_CBITSET(off, bval, ent_bits, msk_bits)                  \
    {                                                                   \
        if(bval != ((int) VTSS_ACE_BIT_ANY))                            \
            L26_ACL_BITSET(off, bval == ((int) VTSS_ACE_BIT_1), ent_bits, msk_bits); \
    }

#define L26_ACL_CBITSET_INV(off, bval, ent_bits, msk_bits)              \
    {                                                                   \
        if(bval != ((int) VTSS_ACE_BIT_ANY))                            \
            L26_ACL_BITSET(off, bval == ((int)VTSS_ACE_BIT_0), ent_bits, msk_bits); \
    }

static u32
l26_get_bytes(u8 *data, int nbytes)
{
    u32 val = 0;
    int i;
    for(i = 0; i < nbytes; i++)
        val = (data[i] + (val << 8));
    return val;
}

static void
l26_acl_bytes(int off, int bytes, 
              u8 *val, u8 *msk,
              void *ent_val, void *ent_msk)
{
    while (bytes) {
        u8 nbytes = MIN(4, bytes); /* At most 4 bytes a time */
        u32 wd = l26_get_bytes(msk, nbytes);
        if (wd) {                    /* Something set in mask? */
            vtss_bs_set(ent_msk, off, nbytes*8, wd);
            /* Add value part to look for */
            wd = l26_get_bytes(val, nbytes);
            vtss_bs_set(ent_val, off, nbytes*8, wd);
        }
        bytes -= nbytes;
    }
}

#define L26_ACE_MAC(off, mac, ent_bits, msk_bits)                       \
    /* MAC_HIGH */                                                        \
    l26_acl_bytes(off, 2, mac.value, mac.mask, ent_bits, msk_bits); \
    /* MAC_LOW */                                                        \
    l26_acl_bytes(off + 16, 4, mac.value + 2, mac.mask + 2, ent_bits, msk_bits);

static vtss_rc l26_vcap_command(vtss_state_t *vtss_state,
                                const tcam_props_t *tcam,
                                u16 ix, 
                                int cmd, 
                                int sel)
{
    u32 value = 
        VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD(cmd) |
        VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR(ix) |
        VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT;

    if((sel & VTSS_TCAM_SEL_ENTRY) && ix >= tcam->entries)
        return VTSS_RC_ERROR;

    if(!(sel & VTSS_TCAM_SEL_ENTRY))
        value |= VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS;

    if(!(sel & VTSS_TCAM_SEL_ACTION))
        value |= VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS;

    if(!(sel & VTSS_TCAM_SEL_COUNTER))
        value |= VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS;

    L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL(tcam->target), value);           

    do {
        L26_RD(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL(tcam->target), &value);
    } while(value & VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT);

    return VTSS_RC_OK;
}

static vtss_rc l26_vcap_entry2cache(vtss_state_t *vtss_state, 
                                    const tcam_props_t *tcam,
                                    u32 typegroup,
                                    u32 *entry,
                                    u32 *mask)
{
    int i;
    L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_TG_DAT(tcam->target), typegroup);
    for(i = 0; i < tcam->entry_width; i++) {
        L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tcam->target, i), entry ? entry[i] : 0);
        L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tcam->target, i), mask ? ~mask[i] : ~0);
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_vcap_cache2entry(vtss_state_t *vtss_state,
                                    const tcam_props_t *tcam,
                                    u32 *entry,
                                    u32 *mask)
{
    int i;
    for(i = 0; i < tcam->entry_width; i++) {
        u32 m;
        L26_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tcam->target, i), &entry[i]);
        L26_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tcam->target, i), &m);
        mask[i] = ~m;           /* Invert mask */
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_vcap_action2cache(vtss_state_t *vtss_state,
                                     const tcam_props_t *tcam,
                                     const u32 *entry,
                                     u32 counter)
{
    int i;
    for(i = 0; i < tcam->action_width; i++)
        L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(tcam->target, i), entry ? entry[i] : 0);
    L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tcam->target, 0), counter);
    return VTSS_RC_OK;
}

static vtss_rc l26_vcap_cache2action(vtss_state_t *vtss_state,
                                     const tcam_props_t *tcam,
                                     u32 *entry)
{
    int i;
    for(i = 0; i < tcam->action_width; i++)
        L26_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(tcam->target, i), &entry[i]);
    return VTSS_RC_OK;
}

static vtss_rc l26_vcap_initialize(vtss_state_t *vtss_state, const tcam_props_t *tcam)
{
    /* First write entries */
    VTSS_RC(l26_vcap_entry2cache(vtss_state, tcam, 0, NULL, NULL));
    L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tcam->target),
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(tcam->entries));
    VTSS_RC(l26_vcap_command(vtss_state, tcam, 0, VTSS_TCAM_CMD_INITIALIZE, VTSS_TCAM_SEL_ENTRY));

    /* Then actions and counters */
    VTSS_RC(l26_vcap_action2cache(vtss_state, tcam, NULL, 0));
    L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tcam->target),
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(tcam->actions));
    VTSS_RC(l26_vcap_command(vtss_state, tcam, 0, VTSS_TCAM_CMD_INITIALIZE, VTSS_TCAM_SEL_ACTION|VTSS_TCAM_SEL_COUNTER));

    return VTSS_RC_OK;
}

/* Convert from 0-based index to VCAP entry index and run command */
static vtss_rc l26_vcap_index_command(vtss_state_t *vtss_state,
                                      const tcam_props_t *tcam,
                                      u16 ix, 
                                      int cmd, 
                                      int sel)
{
    return l26_vcap_command(vtss_state, tcam, tcam->entries - ix - 1, cmd, sel);
}

/* Convert from 0-based port to VCAP entry index and run command */
static vtss_rc l26_vcap_port_command(vtss_state_t *vtss_state,
                                     const tcam_props_t *tcam,
                                     u16 port, 
                                     int cmd, 
                                     int sel)
{
    return l26_vcap_command(vtss_state, tcam, tcam->entries + port, cmd, sel);
}

static vtss_rc l26_vcap_entry_get(vtss_state_t *vtss_state,
                                  int bank, u32 ix, u32 *counter, BOOL clear) 
{
    const tcam_props_t *tcam = &tcam_info[bank];
    
    /* Read counter at index */
    VTSS_RC(l26_vcap_index_command(vtss_state, tcam, ix, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_COUNTER));
    L26_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tcam->target, 0), counter);
    if (!clear)
        return VTSS_RC_OK;

    /* Clear counter at index */
    L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tcam->target, 0), 0);
    return l26_vcap_index_command(vtss_state, tcam, ix, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_COUNTER);
}

static vtss_rc l26_vcap_port_get(vtss_state_t *vtss_state,
                                 int bank, u32 port, u32 *counter, BOOL clear) 
{
    const tcam_props_t *tcam = &tcam_info[bank];
    
    /* Read counter at index */
    VTSS_RC(l26_vcap_port_command(vtss_state, tcam, port, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_COUNTER));
    L26_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tcam->target, 0), counter);
    if (!clear)
        return VTSS_RC_OK;

    /* Clear counter at index */
    L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tcam->target, 0), 0);
    return l26_vcap_port_command(vtss_state, tcam, port, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_COUNTER);
}

static vtss_rc l26_vcap_entry_del(vtss_state_t *vtss_state, int bank, u32 ix)
{
    const tcam_props_t *tcam = &tcam_info[bank];

    /* Delete entry at index */
    VTSS_RC(l26_vcap_entry2cache(vtss_state, tcam, 0, NULL, NULL));
    VTSS_RC(l26_vcap_action2cache(vtss_state, tcam, NULL, 0));
    return l26_vcap_index_command(vtss_state, tcam, ix, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ALL);
}

static vtss_rc l26_vcap_entry_move(vtss_state_t *vtss_state, int bank, u32 ix, u32 count, BOOL up)
{
    const tcam_props_t *tcam = &tcam_info[bank];
    u32                i, cmd;

    if (up) {
        /* Moving up corresponds to move down command and must be done one entry at a time */
        cmd = VTSS_TCAM_CMD_MOVE_DOWN;
        L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tcam->target),
               VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(1) |
               VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(0));
        for (i = 0; i < count; i++) {
            VTSS_RC(l26_vcap_index_command(vtss_state, tcam, ix + i, cmd, VTSS_TCAM_SEL_ALL));
        }
    } else {
        /* Moving down corresponds to move up command */
        cmd = VTSS_TCAM_CMD_MOVE_UP;
        L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tcam->target),
               VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(1) |
               VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(count - 1));
        VTSS_RC(l26_vcap_index_command(vtss_state, tcam, ix + count - 1, cmd, VTSS_TCAM_SEL_ALL));
    }

    /* Move block starting at index */
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  IS1 functions
 * ================================================================= */

static BOOL l26_vcap_is_udp_tcp(vtss_vcap_u8_t *proto)
{
    return (proto->mask == 0xff && (proto->value == 6 || proto->value == 17));
}

static u32 l26_u8_to_u32(u8 *p)
{
    return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static vtss_rc l26_is1_prepare_action(vtss_state_t *vtss_state,
                                      const tcam_props_t *tcam,
                                      vtss_is1_data_t *is1,
                                      u32 counter)
{
    u32               entry[VTSS_TCAM_ENTRY_WIDTH];
    vtss_is1_action_t *action = &is1->entry->action;
    
    VTSS_MEMSET(entry, 0, sizeof(entry));
    if (is1->entry->key.type == VTSS_IS1_TYPE_SMAC_SIP) {
        vtss_bs_set(entry, 0, 2, IS1_ACTION_TYPE_SMAC_SIP4); /* Type */
        /* SIP/SMAC action */
        if (action->host_match) 
            vtss_bs_bit_set(entry, 2, 1); /* HOST_MATCH */
    } else {
        vtss_bs_set(entry, 0, 2, IS1_ACTION_TYPE_NORMAL); /* Type */

        /* Normal action */
        if (action->dscp_enable) {
            vtss_bs_bit_set(entry, 2, 1); /* DSCP_ENA */
            vtss_bs_set(entry, 3, 6, action->dscp);
        }
        if (action->dp_enable) {
            vtss_bs_bit_set(entry, 9, 1); /* DP_ENA */
            vtss_bs_bit_set(entry, 10, action->dp); /* DP_VAL */
        }
        if (action->prio_enable) {
            vtss_bs_bit_set(entry, 11, 1); /* QOS_ENA */
            vtss_bs_set(entry, 12, 3, action->prio); /* QOS_VAL */
        }
        if (action->pag_enable) {
            vtss_bs_bit_set(entry, 15, 1); /* PAG_ENA */
            vtss_bs_set(entry, 16, 8, action->pag); /* PAG_VAL */
        }
        if (action->vid) {
            vtss_bs_bit_set(entry, 24, 1); /* VID_REPLACE_ENA */
            vtss_bs_set(entry, 25, 12, action->vid); /* VID_ADD_VAL */
        }
        if (action->pcp_dei_enable) {
            vtss_bs_bit_set(entry, 51, 1); /* PCP_DEI_ENA */
            vtss_bs_set(entry, 52, 3, action->pcp); /* PCP_VAL */
            vtss_bs_bit_set(entry, 55, action->dei); /* DEI_VAL */
        }
        if (action->pop_enable) {
            vtss_bs_bit_set(entry, 56, 1); /* VLAN_POP_CNT_ENA */
            vtss_bs_set(entry, 57, 2, action->pop); /* VLAN_POP_CNT */
        }
        if (action->host_match)
            vtss_bs_bit_set(entry, 59, 1); /* HOST_MATCH */
        if (action->fid_sel) {
            vtss_bs_set(entry, 37, 2, action->fid_sel);     /* FID_SEL */
            vtss_bs_set(entry, 39, 12, action->fid_val);    /* FID_VAL */
        }
    }
    
    return l26_vcap_action2cache(vtss_state, tcam, entry, counter);
}

static vtss_rc l26_is1_prepare_key(vtss_state_t *vtss_state,
                                   const tcam_props_t *tcam, vtss_is1_data_t *is1) 
{
    u32                 entry[VTSS_TCAM_ENTRY_WIDTH];
    u32                 mask[VTSS_TCAM_ENTRY_WIDTH];
    vtss_is1_key_t      *key = &is1->entry->key;
    vtss_is1_tag_t      *tag = &key->tag;
    u32                 port, port_mask, etype_len, ip_snap, ip4 = 0, tcp_udp = 0, tcp = 0;
    u32                 l4_used = 0, msk;
    vtss_vcap_ip_t      sip;
    vtss_vcap_u8_t      *proto = NULL;
    vtss_vcap_vr_t      *dscp = NULL, *sport = NULL, *dport = NULL;
    vtss_vcap_u16_t     etype;
    u8                  range_value = 0, range_mask = 0;
    vtss_vcap_u48_t     smac;
    int                 i;
    vtss_vcap_bit_t     vcap_bit;

    VTSS_MEMSET(entry, 0, sizeof(entry));
    VTSS_MEMSET(mask, 0, sizeof(mask));
    VTSS_MEMSET(&etype, 0, sizeof(etype));
    
    if (key->type == VTSS_IS1_TYPE_SMAC_SIP) {
        /* SMAC/SIP entry */
        if (key->frame.smac_sip.port_no != VTSS_PORT_NO_NONE) {
            port = VTSS_CHIP_PORT(key->frame.smac_sip.port_no);
            L26_ACL_FIELD(0, 5, port, ACL_MASK_ONES, entry, mask); /* IGR_PORT */
        }
        for (i = 0; i < 6; i++) {
            smac.value[i] = key->frame.smac_sip.smac.addr[i];
            smac.mask[i] = 0xff;
        }
        L26_ACE_MAC(5, smac, entry, mask);     /* L2_SMAC */
        L26_ACL_FIELD(53, 32, key->frame.smac_sip.sip, ACL_MASK_ONES, entry, mask); /* L3_IP4_SIP */
        return l26_vcap_entry2cache(vtss_state, tcam, VCAP_TG_VAL_IS1_IP4, entry, mask);
    }
    
    /* Common fields */
    L26_ACL_BITSET(0, 0, entry, mask);                  /* IS1_TYPE */
    L26_ACL_BITSET(1, is1->lookup ? 0 : 1, entry, mask);         /* FIRST */
    port_mask = vtss_l26_port_mask(vtss_state, key->port_list);
    /* Inverse match - Match *zeroes* in port mask - enables multiple ports */
    L26_ACL_FIELD(2, 27, 0, ~port_mask, entry, mask);   /* IGR_PORT_MASK */
    L26_ACL_CBITSET(29, tag->tagged, entry, mask); /* VLAN_TAGGED */
    L26_ACL_CBITSET(30, key->inner_tag.tagged, entry, mask); /* VLAN_DBL_TAGGED */
    L26_ACL_CBITSET(31, tag->s_tag, entry, mask);  /* TPID */
    if (key->tag.vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK)
        L26_ACL_CFIELD(32, 12, tag->vid.vr.v.value, tag->vid.vr.v.mask, entry, mask); /* VID */
    if (is1->vid_range != VTSS_VCAP_RANGE_CHK_NONE) {
        range_mask |= (1<<is1->vid_range);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_RANGE_INCLUSIVE)
            range_value |= (1<<is1->vid_range);
    }
    L26_ACL_CBITSET(44, tag->dei, entry, mask);    /* DEI */
    L26_ACL_CFIELD(45, 3, tag->pcp.value, tag->pcp.mask, entry, mask);  /* PCP */
    L26_ACE_MAC(48, key->mac.smac, entry, mask);        /* L2_SMAC */
    L26_ACL_CBITSET(96, key->mac.dmac_mc, entry, mask); /* L2_MC */
    L26_ACL_CBITSET(97, key->mac.dmac_bc, entry, mask); /* L2_BC */

    switch (key->type) {
    case VTSS_IS1_TYPE_ANY:
        /* Only common fields and range are valid */
        L26_ACL_CFIELD(176, 8, range_value, range_mask, entry, mask);                      /* L4_RNG */
        return l26_vcap_entry2cache(vtss_state, tcam, VCAP_TG_VAL_IS1_IS1, entry, mask);
    case VTSS_IS1_TYPE_ETYPE:
        etype_len = 1;
        ip_snap = 0;
        ip4 = 0;
        etype = key->frame.etype.etype;
        sip.value = l26_u8_to_u32(key->frame.etype.data.value);
        sip.mask = l26_u8_to_u32(key->frame.etype.data.mask);
        break;
    case VTSS_IS1_TYPE_LLC:
        etype_len = 0;
        ip_snap = 0;
        ip4 = 0;
        etype.value[0] = key->frame.llc.data.value[0];
        etype.mask[0] = key->frame.llc.data.mask[0];
        etype.value[1] = key->frame.llc.data.value[1];
        etype.mask[1] = key->frame.llc.data.mask[1];
        sip.value = l26_u8_to_u32(&key->frame.llc.data.value[2]);
        sip.mask = l26_u8_to_u32(&key->frame.llc.data.mask[2]);
        break;
    case VTSS_IS1_TYPE_SNAP:
        etype_len = 0;
        ip_snap = 1;
        ip4 = 0;
        etype.value[0] = key->frame.snap.data.value[0];
        etype.mask[0] = key->frame.snap.data.mask[0];
        etype.value[1] = key->frame.snap.data.value[1];
        etype.mask[1] = key->frame.snap.data.mask[1];
        sip.value = l26_u8_to_u32(&key->frame.snap.data.value[2]);
        sip.mask = l26_u8_to_u32(&key->frame.snap.data.mask[2]);
        break;
    case VTSS_IS1_TYPE_IPV4:
    case VTSS_IS1_TYPE_IPV6:
        etype_len = 1;
        ip_snap = 1;
        if (key->type == VTSS_IS1_TYPE_IPV4) {
            ip4 = 1;
            vcap_bit = key->frame.ipv4.ip_mc;
            proto = &key->frame.ipv4.proto;
            dscp = &key->frame.ipv4.dscp;
            sip = key->frame.ipv4.sip;
            sport = &key->frame.ipv4.sport;
            dport = &key->frame.ipv4.dport;
        } else {
            ip4 = 0;
            vcap_bit = key->frame.ipv6.ip_mc;
            proto = &key->frame.ipv6.proto;
            dscp = &key->frame.ipv6.dscp;
            sip.value = l26_u8_to_u32(&key->frame.ipv6.sip.value[12]);
            sip.mask = l26_u8_to_u32(&key->frame.ipv6.sip.mask[12]);
            sport = &key->frame.ipv6.sport;
            dport = &key->frame.ipv6.dport;
        }
        L26_ACL_CBITSET(98, vcap_bit, entry, mask); /* IP_MC */
        if (l26_vcap_is_udp_tcp(proto)) {
            tcp_udp = 1;
            tcp = VTSS_BOOL(proto->value == 6);
            if (dport->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
                msk = dport->vr.v.mask;
                etype.value[0] = ((dport->vr.v.value >> 8) & 0xff);
                etype.value[1] = (dport->vr.v.value & 0xff);
                etype.mask[0] = ((msk >> 8) & 0xff);
                etype.mask[1] = (msk & 0xff);
                if (msk)
                    l4_used = 1;
            }
        } else {
            etype.value[1] = proto->value;
            etype.mask[1] = proto->mask;
        }
        break;
    default:
        VTSS_E("illegal type: %d", key->type);
        return VTSS_RC_ERROR;
    }

    L26_ACL_BITSET(99, etype_len, entry, mask);                                        /* ETYPE_LEN */
    l26_acl_bytes(100, 2, etype.value, etype.mask, entry, mask);                       /* ETYPE */
    L26_ACL_BITSET(116, ip_snap, entry, mask);                                         /* IP_SNAP */

    if (dscp != NULL) {
        if (dscp->type == VTSS_VCAP_VR_TYPE_VALUE_MASK)
            L26_ACL_CFIELD(120, 6, dscp->vr.v.value, dscp->vr.v.mask, entry, mask);    /* L3_DSCP */
        if (is1->dscp_range != VTSS_VCAP_RANGE_CHK_NONE) {
            range_mask |= (1<<is1->dscp_range);
            if (dscp->type == VTSS_VCAP_VR_TYPE_RANGE_INCLUSIVE)
                range_value |= (1<<is1->dscp_range);
        }
    }
    L26_ACL_CFIELD(126, 32, sip.value, sip.mask, entry, mask);                         /* L3_SIP */
    if (tcp_udp) {
        L26_ACL_BITSET(158, tcp_udp, entry, mask);                                     /* TCP_UDP */
        L26_ACL_BITSET(159, tcp, entry, mask);                                         /* TCP */
        if (sport != NULL && sport->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            msk = sport->vr.v.mask;
            L26_ACL_CFIELD(160, 16, sport->vr.v.value, msk, entry, mask); /* L4_SPORT */
            if (msk)
                l4_used = 1;
        }
        if (is1->sport_range != VTSS_VCAP_RANGE_CHK_NONE) {
            range_mask |= (1<<is1->sport_range);
            if (sport != NULL && sport->type == VTSS_VCAP_VR_TYPE_RANGE_INCLUSIVE)
                range_value |= (1<<is1->sport_range);
            l4_used = 1;
        }
        if (is1->dport_range != VTSS_VCAP_RANGE_CHK_NONE) {
            range_mask |= (1<<is1->dport_range);
            if (dport != NULL && dport->type == VTSS_VCAP_VR_TYPE_RANGE_INCLUSIVE)
                range_value |= (1<<is1->dport_range);
            l4_used = 1;
        }
    }
    if ((key->type == VTSS_IS1_TYPE_IPV4) || (key->type == VTSS_IS1_TYPE_IPV6)) {
        L26_ACL_BITSET(117, ip4, entry, mask);                                         /* IP4 */
        if (ip4) {
            /* If L4 filtering is used, IPv4 frame must not be fragment or have options */
            vcap_bit = (l4_used ? VTSS_VCAP_BIT_0 : key->frame.ipv4.fragment);
            L26_ACL_CBITSET(118, vcap_bit, entry, mask);               /* L3_FRAGMENT */
            vcap_bit = (l4_used ? VTSS_VCAP_BIT_0 : key->frame.ipv4.options);
            L26_ACL_CBITSET(119, vcap_bit, entry, mask);                /* L3_OPTIONS */
        }
    }
    L26_ACL_CFIELD(176, 8, range_value, range_mask, entry, mask);                      /* L4_RNG */
    
    return l26_vcap_entry2cache(vtss_state, tcam, VCAP_TG_VAL_IS1_IS1, entry, mask);
}

static vtss_rc l26_is1_entry_get(vtss_state_t *vtss_state,
                                 vtss_vcap_idx_t *idx, u32 *counter, BOOL clear) 
{
    VTSS_I("row: %u", idx->row);

    return l26_vcap_entry_get(vtss_state, VTSS_TCAM_S1, idx->row, counter, clear);
}

static vtss_rc l26_is1_entry_add(vtss_state_t *vtss_state,
                                 vtss_vcap_idx_t *idx, vtss_vcap_data_t *data, u32 counter)
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_S1];
    
    VTSS_I("row: %u", idx->row);
    
    /* Write entry at index */
    VTSS_RC(l26_is1_prepare_key(vtss_state, tcam, &data->u.is1));
    VTSS_RC(l26_is1_prepare_action(vtss_state, tcam, &data->u.is1, counter));

    return l26_vcap_index_command(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ALL);
}

static vtss_rc l26_is1_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    VTSS_I("row: %u", idx->row);
    
    return l26_vcap_entry_del(vtss_state, VTSS_TCAM_S1, idx->row);
}

static vtss_rc l26_is1_entry_move(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    VTSS_I("row: %u, count: %u, up: %u", idx->row, count, up);
    
    return l26_vcap_entry_move(vtss_state, VTSS_TCAM_S1, idx->row, count, up);
}

/* ================================================================= *
 *  IS2 functions
 * ================================================================= */

/* Setup action */
static vtss_rc l26_is2_prepare_action(vtss_state_t *vtss_state,
                                      const tcam_props_t *tcam,
                                      vtss_acl_action_t *action,
                                      u32 counter)
{
    u32 entry[VTSS_TCAM_ENTRY_WIDTH];
    u32 mode = 0, policer_ena = 0, policer = 0, mask;
    
    VTSS_MEMSET(entry, 0, sizeof(entry));

    if (action->cpu_once)
        entry[0] |= VTSS_BIT(0); /* HIT_ME_ONCE */
    if (action->cpu)
        entry[0] |= VTSS_BIT(1); /* CPU_COPY_ENA */
    if (action->cpu_once || action->cpu) /* CPU_QU_NUM */
        entry[0] |= VTSS_ENCODE_BITFIELD(action->cpu_queue - VTSS_PACKET_RX_QUEUE_START, 2, 3);

    /* MASK_MODE */
    switch (action->port_action) {
    case VTSS_ACL_PORT_ACTION_NONE:
        mode = 0;
        break;
    case VTSS_ACL_PORT_ACTION_FILTER:
        mode = 1;
        break;
    case VTSS_ACL_PORT_ACTION_REDIR:
        mode = 3;
        break;
    default:
        VTSS_E("unknown port_action");
        return VTSS_RC_ERROR;
    }
    
    if (action->mirror)
        entry[0] |= VTSS_BIT(7); /* MIRROR_ENA */
        
    if (!action->learn)
        entry[0] |= VTSS_BIT(8); /* LRN_DIS */

    mask = vtss_l26_port_mask(vtss_state, action->port_list);
    if (mode != 0 && mask == 0 && action->cpu_once == 0 && action->cpu == 0) {
        /* Forwarding and CPU copy disabled, discard using policer to avoid CPU copy */
        policer_ena = 1;
        policer = L26_ACL_POLICER_DISC;
        mode = 0; // Use mode 0 to make Rx red counters increase
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
    } else if (action->evc_police) {
        policer_ena = 1;
        policer = vtss_state->qos.evc_policer_alloc[action->evc_policer_id].policer;
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
    } else if (action->police) {
        policer_ena = 1;
        policer = vtss_state->vcap.acl_policer_alloc[action->policer_no].policer;
    }
    entry[0] |= VTSS_ENCODE_BITFIELD(mode, 5, 2);
    if (policer_ena)
        entry[0] |= (VTSS_BIT(9) | /* POLICE_ENA */
                     VTSS_ENCODE_BITFIELD(policer, 10, 8)); /* POLICE_IDX */
    /* PORT_MASK */
    if (mode) {
        if (action->port_action == VTSS_ACL_PORT_ACTION_REDIR) {
            mask &= vtss_l26_port_mask(vtss_state, vtss_state->l2.tx_forward_aggr);
        }
        vtss_bs_set(entry, 18, 26, mask);
    }
    /* PTP_ENA */
    switch (action->ptp_action) {
    case VTSS_ACL_PTP_ACTION_NONE:
        mode = 0;
        break;
    case VTSS_ACL_PTP_ACTION_ONE_STEP:
        mode = 1;
        break;
    case VTSS_ACL_PTP_ACTION_TWO_STEP:
        mode = 2;
        break;
    case VTSS_ACL_PTP_ACTION_ONE_AND_TWO_STEP:
        mode = 3;
        break;
    default:
        VTSS_E("unknown ptp_action");
        return VTSS_RC_ERROR;
    }
    vtss_bs_set(entry, 44, 2, mode);

    return l26_vcap_action2cache(vtss_state, tcam, entry, counter);
}

static vtss_rc l26_is2_prepare_key(vtss_state_t *vtss_state,
                                   const tcam_props_t *tcam, vtss_is2_data_t *is2) 
{
    u32                entry[VTSS_TCAM_ENTRY_WIDTH];
    u32                mask[VTSS_TCAM_ENTRY_WIDTH], port_mask;
    BOOL               ipv4 = FALSE;
    u32                type, type_mask = 0x7;
    vtss_ace_t         *ace = &is2->entry->ace;
    vtss_ace_udp_tcp_t *sport, *dport;
    u8                 range = 0, i, mac_valid = 0;
    vtss_ace_u48_t     smac, dmac;
    vtss_ace_u16_t     mac_data;
    vtss_ace_u8_t      *proto;
    vtss_ace_bit_t     *ttl, *tcp_fin, *tcp_syn, *tcp_rst, *tcp_psh, *tcp_ack, *tcp_urg;
    vtss_ace_bit_t     *sip_eq_dip, *sport_eq_dport, *seq_zero;
    vtss_ace_u8_t      *ds;
    vtss_ace_ip_t      sip, dip;
    vtss_ace_u48_t     ip_data;
    vtss_ace_ptp_t     *ptp;
    vtss_ace_u128_t    *sipv6;
    
    VTSS_MEMSET(entry, 0, sizeof(entry));
    VTSS_MEMSET(mask, 0, sizeof(mask));

    switch (ace->type) {
    case VTSS_ACE_TYPE_ANY:
        type = ACL_TYPE_ANY;
        break;
    case VTSS_ACE_TYPE_ETYPE:
        type = ACL_TYPE_ETYPE;
        break;
    case VTSS_ACE_TYPE_LLC:
        type = ACL_TYPE_LLC;
        break;
    case VTSS_ACE_TYPE_SNAP:
        type = ACL_TYPE_SNAP;
        break;
    case VTSS_ACE_TYPE_ARP:
        type = ACL_TYPE_ARP;
        break;
    case VTSS_ACE_TYPE_IPV4:
    case VTSS_ACE_TYPE_IPV6:
        if (ace->type == VTSS_ACE_TYPE_IPV4) {
            ipv4 = TRUE;
            proto = &ace->frame.ipv4.proto;
        } else 
            proto = &ace->frame.ipv6.proto;
        if (l26_vcap_is_udp_tcp(proto)) {
            /* UDP/TCP */
            type = ACL_TYPE_UDP_TCP;
        } else {
            /* IPv4 */
            type = ACL_TYPE_IPV4;
        }
        break;
    default:
        VTSS_E("illegal type: %d", ace->type);
        return VTSS_RC_ERROR;
    }

    /* Common Fields */
    L26_ACL_BITSET(3, is2->entry->first, entry, mask); /* FIRST */
    
    L26_ACL_FIELD(4, 8, ace->policy.value, ace->policy.mask, entry, mask); /* PAG */

    /* Inverse match - Match *zeroes* in port mask - enables multiple ports */
    port_mask = vtss_l26_port_mask(vtss_state, ace->port_list);
    L26_ACL_FIELD(12, 27, 0, ~port_mask, entry, mask); /* IGR_PORT_MASK */

    L26_ACL_CBITSET(39, ace->vlan.tagged, entry, mask); /* VLAN_TAGGED */
    if (is2->entry->host_match)
        L26_ACL_BITSET(40, TRUE, entry, mask); /* HOST_MATCH */
    /* VID */
    L26_ACL_CFIELD(41, 12, ace->vlan.vid.value, ace->vlan.vid.mask, entry, mask);
    /* DEI (formerly CFI) */
    L26_ACL_CBITSET(53, ace->vlan.cfi, entry, mask); 
    /* PCP (formerly UPRIO) */
    L26_ACL_CFIELD(54, 3, ace->vlan.usr_prio.value, ace->vlan.usr_prio.mask, entry, mask);
    switch (type) {
    case ACL_TYPE_ANY:
        type = ACL_TYPE_ETYPE;
        type_mask = 0;
        mac_valid = (ace->dmac_mc != VTSS_ACE_BIT_ANY || ace->dmac_bc != VTSS_ACE_BIT_ANY ? 1 : 0);
        for (i = 0; i < 6; i++) {
            if (ace->frame.any.dmac.mask[i] != 0 || ace->frame.any.smac.mask[i] != 0) {
                mac_valid = 1;
                break;
            }
        }
        if (mac_valid) {
            /* Match ETYPE/LLC/SNAP frames with DMAC/SMAC filtering. ARP frames must be mapped to ETYPE */
            type_mask = 0x4;
            dmac = ace->frame.any.dmac;
            smac = ace->frame.any.smac;
        }
        break;
    case ACL_TYPE_ETYPE:
        mac_valid = 1;
        dmac = ace->frame.etype.dmac;
        smac = ace->frame.etype.smac;
        mac_data = ace->frame.etype.data;
        ptp = &ace->frame.etype.ptp;
        if (ptp->enable) {
            /* PTP header filtering, byte 0, 1, 4 and 6 */
            mac_data.value[0] = ptp->header.value[0]; /* PTP byte 0 */
            mac_data.mask[0] = ptp->header.mask[0];   /* PTP byte 0 */
            mac_data.value[1] = ptp->header.value[1]; /* PTP byte 1 */
            mac_data.mask[1] = ptp->header.mask[1];   /* PTP byte 1 */
            if (!is2->entry->first) {
                /* Override SMAC byte 2 and 4 in second lookup */
                VTSS_MEMSET(&smac, 0, sizeof(smac));
                smac.value[2] = ptp->header.value[2]; /* PTP byte 4 */
                smac.mask[2] = ptp->header.mask[2];   /* PTP byte 4 */
                smac.value[4] = ptp->header.value[3]; /* PTP byte 6 */
                smac.mask[4] = ptp->header.mask[3];   /* PTP byte 6 */
            }
        }
        /* ETYPE */
        l26_acl_bytes(155, 2, ace->frame.etype.etype.value, ace->frame.etype.etype.mask, entry, mask);
        /* L2_PAYLOAD */
        l26_acl_bytes(171, 2, mac_data.value, mac_data.mask, entry, mask);
        break;
    case ACL_TYPE_LLC:
        mac_valid = 1;
        dmac = ace->frame.llc.dmac;
        smac = ace->frame.llc.smac;
        /* L2_LLC */
        l26_acl_bytes(155, 4, ace->frame.llc.llc.value, ace->frame.llc.llc.mask, entry, mask);
        break;
    case ACL_TYPE_SNAP:
        mac_valid = 1;
        dmac = ace->frame.snap.dmac;
        smac = ace->frame.snap.smac;
        /* L2_SNAP byte 0 */
        l26_acl_bytes(155, 1, ace->frame.snap.snap.value, ace->frame.snap.snap.mask, entry, mask);
        /* L2_SNAP bytes 1-4 */
        l26_acl_bytes(163, 4, ace->frame.snap.snap.value + 1, ace->frame.snap.snap.mask + 1, entry, mask);
        break;
    case ACL_TYPE_ARP:
        L26_ACE_MAC(57, ace->frame.arp.smac, entry, mask); /* L2_SMAC */
        L26_ACL_CBITSET(105, ace->dmac_mc, entry, mask); /* L2_MC */
        L26_ACL_CBITSET(106, ace->dmac_bc, entry, mask); /* L2_BC */
        L26_ACL_CBITSET(107, ace->frame.arp.ethernet, entry, mask); /* ARP_ADDR_SPACE_OK */
        L26_ACL_CBITSET(108, ace->frame.arp.ip, entry, mask); /* ARP_PROTO_SPACE_OK */
        L26_ACL_CBITSET(109, ace->frame.arp.length, entry, mask); /* ARP_LEN_OK */
        L26_ACL_CBITSET(110, ace->frame.arp.dmac_match, entry, mask); /* ARP_TARGET_MATCH */
        L26_ACL_CBITSET(111, ace->frame.arp.smac_match, entry, mask); /* ARP_SENDER_MATCH */
        L26_ACL_CBITSET(112, ace->frame.arp.unknown, entry, mask); /* ARP_UNKNOWN_OPCODE */
        L26_ACL_CBITSET_INV(113, ace->frame.arp.req, entry, mask); /* ARP_OPCODE */
        L26_ACL_CBITSET_INV(114, ace->frame.arp.arp, entry, mask); /* ARP_OPCODE */
        L26_ACL_CFIELD(115, 32, ace->frame.arp.dip.value, ace->frame.arp.dip.mask, entry, mask);
        L26_ACL_CFIELD(147, 32, ace->frame.arp.sip.value, ace->frame.arp.sip.mask, entry, mask);
        /* ARP_DIP_EQ_SIP (bit 179): Not supported */
        break;
    case ACL_TYPE_UDP_TCP:
    case ACL_TYPE_IPV4:
        if (ipv4) {
            /* IPv4 */
            ttl = &ace->frame.ipv4.ttl;
            ds = &ace->frame.ipv4.ds;
            proto = &ace->frame.ipv4.proto;
            sip = ace->frame.ipv4.sip;
            dip = ace->frame.ipv4.dip;
            ip_data = ace->frame.ipv4.data;
            sport = &ace->frame.ipv4.sport;
            dport = &ace->frame.ipv4.dport;
            tcp_fin = &ace->frame.ipv4.tcp_fin;
            tcp_syn = &ace->frame.ipv4.tcp_syn;
            tcp_rst = &ace->frame.ipv4.tcp_rst;
            tcp_psh = &ace->frame.ipv4.tcp_psh;
            tcp_ack = &ace->frame.ipv4.tcp_ack;
            tcp_urg = &ace->frame.ipv4.tcp_urg;
            sip_eq_dip = &ace->frame.ipv4.sip_eq_dip;
            sport_eq_dport = &ace->frame.ipv4.sport_eq_dport;
            seq_zero = &ace->frame.ipv4.seq_zero;
            ptp = &ace->frame.ipv4.ptp;
            if (is2->entry->host_match) {
                sip.value = ace->frame.ipv4.sip_smac.sip;
                sip.mask = ACL_MASK_ONES;
            }
        } else {
            /* IPv6 */
            proto = &ace->frame.ipv6.proto;
            ttl = &ace->frame.ipv6.ttl;
            ds = &ace->frame.ipv6.ds;
            sipv6 = &ace->frame.ipv6.sip;
            sip.value = l26_u8_to_u32(&sipv6->value[12]);
            sip.mask = l26_u8_to_u32(&sipv6->mask[12]);
            dip.value = l26_u8_to_u32(&sipv6->value[8]);
            dip.mask = l26_u8_to_u32(&sipv6->mask[8]);
            ip_data = ace->frame.ipv6.data;
            sport = &ace->frame.ipv6.sport;
            dport = &ace->frame.ipv6.dport;
            tcp_fin = &ace->frame.ipv6.tcp_fin;
            tcp_syn = &ace->frame.ipv6.tcp_syn;
            tcp_rst = &ace->frame.ipv6.tcp_rst;
            tcp_psh = &ace->frame.ipv6.tcp_psh;
            tcp_ack = &ace->frame.ipv6.tcp_ack;
            tcp_urg = &ace->frame.ipv6.tcp_urg;
            sip_eq_dip = &ace->frame.ipv6.sip_eq_dip;
            sport_eq_dport = &ace->frame.ipv6.sport_eq_dport;
            seq_zero = &ace->frame.ipv6.seq_zero;
            ptp = &ace->frame.ipv6.ptp;
        }
        
        /* Common format */
        L26_ACL_CBITSET(57, ace->dmac_mc, entry, mask); /* L2_MC */
        L26_ACL_CBITSET(58, ace->dmac_bc, entry, mask); /* L2_BC */
        if (is2->entry->first && !ipv4 && ace->type_ext) {
            /* Encode as IP6_STD rule */
            type = ACL_TYPE_IPV6;
            L26_ACL_CFIELD(59, 8, proto->value, proto->mask, entry, mask);
            for (i = 0; i < 4; i++) {
                sip.value = l26_u8_to_u32(&sipv6->value[i * 4]);
                sip.mask = l26_u8_to_u32(&sipv6->mask[i * 4]);
                L26_ACL_CFIELD(67 + i * 32, 32, sip.value, sip.mask, entry, mask);
            }
            break;
        }

        L26_ACL_BITSET(59, ipv4, entry, mask); /* IP4 */
        if (ipv4) {
            L26_ACL_CBITSET(60, ace->frame.ipv4.fragment, entry, mask); /* L3_FRAGMENT */
            /* L3_FRAG_OFS_GT0 (bit 61): Not supported */
            L26_ACL_CBITSET(62, ace->frame.ipv4.options, entry, mask); /* L3_OPTIONS */
        }
        L26_ACL_CBITSET(63, *ttl, entry, mask); /* L3_TTL_GT0 */
        /* L3_TOS */
        L26_ACL_CFIELD(64, 8, ds->value, ds->mask, entry, mask);
        if(type == ACL_TYPE_UDP_TCP) {
            /* Specific format - Bit 72 FF */
            if (!is2->entry->udp_tcp_any)
                L26_ACL_BITSET(72, proto->value == 6, entry, mask); /* TCP */
            /* L4_1588_DOM (bit 73): Not supported */

            /* L3_IP4_DIP */
            L26_ACL_CFIELD(81, 32, dip.value, dip.mask, entry, mask);
            /* L3_IP4_SIP */
            if (ptp->enable && !is2->entry->first) {
                /* Override SIP in second lookup */
                l26_acl_bytes(113, 4, ptp->header.value, ptp->header.mask, entry, mask);
            } else {
                L26_ACL_CFIELD(113, 32, sip.value, sip.mask, entry, mask);
            }
            L26_ACL_CBITSET(145, *sip_eq_dip, entry, mask); /* DIP_EQ_SIP */
            
            /* L3_DPORT */
            if (dport->in_range && dport->low == dport->high)
                L26_ACL_FIELD(146, 16, dport->low, ACL_MASK_ONES, entry, mask);
            /* L3_SPORT */
            if(sport->in_range && sport->low == sport->high)
                L26_ACL_FIELD(162, 16, sport->low, ACL_MASK_ONES, entry, mask);
            /* L4_RNG */
            if (is2->srange != VTSS_VCAP_RANGE_CHK_NONE)
                range |= (1<<is2->srange);
            if (is2->drange != VTSS_VCAP_RANGE_CHK_NONE)
                range |= (1<<is2->drange);
            L26_ACL_CFIELD(178, 8, range, range, entry, mask);
            L26_ACL_CBITSET(186, *sport_eq_dport, entry, mask); /* SPORT_EQ_DPORT */
            L26_ACL_CBITSET(187, *seq_zero, entry, mask); /* SEQUENCE_EQ0 */
            L26_ACL_CBITSET(188, *tcp_fin, entry, mask); /* L4_FIN */
            L26_ACL_CBITSET(189, *tcp_syn, entry, mask); /* L4_SYN */
            L26_ACL_CBITSET(190, *tcp_rst, entry, mask); /* L4_RST */
            L26_ACL_CBITSET(191, *tcp_psh, entry, mask); /* L4_PSH */
            L26_ACL_CBITSET(192, *tcp_ack, entry, mask); /* L4_ACK */
            L26_ACL_CBITSET(193, *tcp_urg, entry, mask); /* L4_URG */
        } else {            /* ACL_TYPE_IPV4 */
            /* Specific format - Bit 72 FF */
            /* L3_PROTO */
            L26_ACL_CFIELD(72, 8, proto->value, proto->mask, entry, mask);
            /* L3_IP4_DIP */
            L26_ACL_CFIELD(80, 32, dip.value, dip.mask, entry, mask);
            /* L3_IP4_SIP */
            L26_ACL_CFIELD(112, 32, sip.value, sip.mask, entry, mask);
            L26_ACL_CBITSET(144, *sip_eq_dip, entry, mask); /* DIP_EQ_SIP */

            /* L3_PAYLOAD */
            L26_ACE_MAC(145, ip_data, entry, mask);
        }
        break;
    default:
        VTSS_E("illegal type: %d", type);
        return VTSS_RC_ERROR;
    }
    L26_ACL_FIELD(0, 3, type, type_mask, entry, mask); /* IS2_TYPE */
    if (mac_valid) {
        L26_ACE_MAC(57, dmac, entry, mask); /* L2_DMAC */
        L26_ACE_MAC(105, smac, entry, mask); /* L2_SMAC */
        L26_ACL_CBITSET(153, ace->dmac_mc, entry, mask); /* L2_MC */
        L26_ACL_CBITSET(154, ace->dmac_bc, entry, mask); /* L2_BC */
    }
    return l26_vcap_entry2cache(vtss_state, tcam, VCAP_TG_VAL_IS2, entry, mask);
}

static vtss_rc l26_is2_entry_get(vtss_state_t *vtss_state,
                                 vtss_vcap_idx_t *idx, u32 *counter, BOOL clear) 
{
    VTSS_I("row: %u", idx->row);

    return l26_vcap_entry_get(vtss_state, VTSS_TCAM_S2, idx->row, counter, clear);
}

static vtss_rc l26_is2_entry_add(vtss_state_t *vtss_state,
                                 vtss_vcap_idx_t *idx, vtss_vcap_data_t *data, u32 counter)
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_S2];
    
    VTSS_I("row: %u", idx->row);
    
    /* Write entry at index */
    VTSS_RC(l26_is2_prepare_key(vtss_state, tcam, &data->u.is2));
    VTSS_RC(l26_is2_prepare_action(vtss_state, tcam, &data->u.is2.entry->ace.action, counter));
    return l26_vcap_index_command(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ALL);
}

static vtss_rc l26_is2_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    VTSS_I("row: %u", idx->row);
    
    return l26_vcap_entry_del(vtss_state, VTSS_TCAM_S2, idx->row);
}

static vtss_rc l26_is2_entry_move(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    VTSS_I("row: %u, count: %u, up: %u", idx->row, count, up);
    
    return l26_vcap_entry_move(vtss_state, VTSS_TCAM_S2, idx->row, count, up);
}

static vtss_rc l26_is2_entry_update(vtss_state_t *vtss_state,
                                    vtss_vcap_idx_t *idx, vtss_is2_data_t *is2)
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_S2];
    u32                entry[VTSS_TCAM_ENTRY_WIDTH];
    vtss_port_no_t     port_no;
    BOOL               member[VTSS_PORTS];
    u32                mask;

    VTSS_I("row: %u", idx->row);
    VTSS_RC(l26_vcap_index_command(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_ACTION));
    VTSS_RC(l26_vcap_cache2action(vtss_state, tcam, entry));
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        member[port_no] = (VTSS_PORT_BF_GET(is2->action.member, port_no) &&
                           vtss_state->l2.tx_forward_aggr[port_no]);
    }
    mask = vtss_l26_port_mask(vtss_state, member);
    vtss_bs_set(entry, 18, 26, mask);
    VTSS_RC(l26_vcap_action2cache(vtss_state, tcam, entry, 0));
    VTSS_RC(l26_vcap_index_command(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ACTION));
    return VTSS_RC_OK;
}

static vtss_rc l26_is2_port_get(vtss_state_t *vtss_state, u32 port, u32 *counter, BOOL clear)
{
    return l26_vcap_port_get(vtss_state, VTSS_TCAM_S2, port, counter, clear);
}

/* ================================================================= *
 *  ES0 functions
 * ================================================================= */

/* Setup action */
static vtss_rc l26_es0_prepare_action(vtss_state_t *vtss_state,
                                      const tcam_props_t *tcam,
                                      vtss_es0_action_t *action,
                                      u32 counter)
{
    u32 entry[VTSS_TCAM_ENTRY_WIDTH];

    VTSS_MEMSET(entry, 0, sizeof(entry));
    vtss_bs_set(entry, 0, 1, 1);               /* VLD */
    vtss_bs_set(entry, 1, 2, action->tag);     /* TAG_ES0 */
    vtss_bs_set(entry, 3, 2, action->tpid);    /* TAG_TPID_SEL */
    vtss_bs_set(entry, 5, 2, action->vid_b ? 2 : 0); /* TAG_VID_SEL */
    vtss_bs_set(entry, 7, 12, action->vid_a);  /* VID_A_VAL */
    vtss_bs_set(entry, 19, 12, action->vid_b); /* VID_B_VAL */
    vtss_bs_set(entry, 31, 2, action->qos);    /* QOS_SRC_SEL */
    vtss_bs_set(entry, 33, 3, action->pcp);    /* PCP_VAL */
    vtss_bs_set(entry, 36, 1, action->dei);    /* DEI_VAL */
    
    return l26_vcap_action2cache(vtss_state, tcam, entry, counter);
}

static vtss_rc l26_es0_prepare_key(vtss_state_t *vtss_state,
                                   const tcam_props_t *tcam, vtss_es0_key_t *key) 
{
    u32 entry[VTSS_TCAM_ENTRY_WIDTH];
    u32 mask[VTSS_TCAM_ENTRY_WIDTH];
    u32 port;

    VTSS_MEMSET(entry, 0, sizeof(entry));
    VTSS_MEMSET(mask, 0, sizeof(mask));
    
    if (key->port_no != VTSS_PORT_NO_NONE) {
        port = VTSS_CHIP_PORT(key->port_no);
        L26_ACL_FIELD(0, 5, port, ACL_MASK_ONES, entry, mask); /* EGR_PORT */
    }
    L26_ACL_FIELD(10, 12, key->data.vid.vid, key->vid_any ? 0 : ACL_MASK_ONES, entry, mask); /* VID */
    return l26_vcap_entry2cache(vtss_state, tcam, VCAP_TG_VAL_ES0, entry, mask);
}

static vtss_rc l26_es0_entry_add(vtss_state_t *vtss_state,
                                 vtss_vcap_idx_t *idx, vtss_vcap_data_t *data, u32 counter)
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_ES0];
    vtss_es0_data_t    *es0 = &data->u.es0;
    vtss_es0_action_t  *action = &es0->entry->action;

    VTSS_I("row: %u", idx->row);
    
    /* Write entry at index */
    vtss_cmn_es0_action_get(vtss_state, es0);
    VTSS_RC(l26_es0_prepare_key(vtss_state, tcam, &es0->entry->key));
    VTSS_RC(l26_es0_prepare_action(vtss_state, tcam, action, counter));
    return l26_vcap_index_command(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ALL);
}

static vtss_rc l26_es0_entry_get(vtss_state_t *vtss_state,
                                 vtss_vcap_idx_t *idx, u32 *counter, BOOL clear) 
{
    VTSS_I("row: %u", idx->row);

    return l26_vcap_entry_get(vtss_state, VTSS_TCAM_ES0, idx->row, counter, clear);
}

static vtss_rc l26_es0_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    VTSS_I("row: %u", idx->row);
    
    return l26_vcap_entry_del(vtss_state, VTSS_TCAM_ES0, idx->row);
}

static vtss_rc l26_es0_entry_move(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    VTSS_I("row: %u, count: %u, up: %u", idx->row, count, up);
    
    return l26_vcap_entry_move(vtss_state, VTSS_TCAM_ES0, idx->row, count, up);
}

/* Update outer tag TPID for ES0 entry if VLAN port type has changed */
static vtss_rc l26_es0_entry_update(vtss_state_t *vtss_state,
                                    vtss_vcap_idx_t *idx, vtss_es0_data_t *es0) 
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_ES0];
    u32                entry[VTSS_TCAM_ENTRY_WIDTH];
    vtss_es0_action_t  *action = &es0->entry->action;

    VTSS_RC(l26_vcap_index_command(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_ACTION));
    VTSS_RC(l26_vcap_cache2action(vtss_state, tcam, entry));
    if (es0->flags & VTSS_ES0_FLAG_OT_TPID) {
        vtss_bs_set(entry, 3, 2, action->tpid); /* TAG_TPID_SEL */
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_QOS) {
        vtss_bs_set(entry, 31, 2, action->qos); /* QOS_SRC_SEL */
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_PCP) {
        vtss_bs_set(entry, 33, 3, action->pcp); /* PCP_VAL */
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_DEI) {
        vtss_bs_set(entry, 36, 1, action->dei); /* DEI_VAL */
    }
    VTSS_RC(l26_vcap_action2cache(vtss_state, tcam, entry, 0));
    VTSS_RC(l26_vcap_index_command(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ACTION));

    return VTSS_RC_OK;
}

/* ================================================================= *
 *  ACL
 * ================================================================= */

static vtss_rc l26_acl_policer_set(vtss_state_t *vtss_state,
                                   const vtss_acl_policer_no_t policer_no)
{
    u32                     policer = (policer_no - VTSS_ACL_POLICER_NO_START);
    vtss_acl_policer_conf_t *conf = &vtss_state->vcap.acl_policer_conf[policer];
    vtss_policer_alloc_t    *pol_alloc = &vtss_state->vcap.acl_policer_alloc[policer];
    vtss_l26_policer_conf_t cfg;
    
    /* Only setup policer if allocated */
    if (pol_alloc->count == 0)
        return VTSS_RC_OK;

    VTSS_MEMSET(&cfg, 0, sizeof(cfg));
    if (conf->bit_rate_enable) {
        cfg.eir = conf->bit_rate;
        cfg.ebs = 4*1024; /* 4 kB burst size */
    } else {
        cfg.frame_rate = 1;
        cfg.eir = conf->rate;
    }
    
    return vtss_l26_policer_conf_set(vtss_state, VTSS_POLICER_USER_ACL, pol_alloc->policer, 1, &cfg);
}

static vtss_rc l26_is2_port_action_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    const tcam_props_t   *tcam = &tcam_info[VTSS_TCAM_S2];
    vtss_acl_port_conf_t *conf = &vtss_state->vcap.acl_port_conf[port_no];
    u32                  port = VTSS_CHIP_PORT(port_no);

    VTSS_RC(l26_is2_prepare_action(vtss_state, tcam, &conf->action, 0));
    return l26_vcap_port_command(vtss_state, tcam, port, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ACTION);
}

static vtss_rc l26_action_check(const vtss_acl_action_t *action)
{
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
    if (action->police && action->evc_police) {
        VTSS_E("ACL policer and EVC policer can not both be enabled");
        return VTSS_RC_ERROR;
    }
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
    return VTSS_RC_OK;
}

static vtss_policer_alloc_t *l26_acl_alloc_get(vtss_state_t *vtss_state,
                                               const vtss_acl_action_t *action,
                                               vtss_policer_user_t *user)
{
    if (action->police) {
        *user = VTSS_POLICER_USER_ACL;
        return &vtss_state->vcap.acl_policer_alloc[action->policer_no];
    }
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
    if (action->evc_police) {
        *user = VTSS_POLICER_USER_EVC;
        return &vtss_state->qos.evc_policer_alloc[action->evc_policer_id];
    }
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
    return NULL;
}

static vtss_rc l26_acl_policer_free(vtss_state_t *vtss_state, vtss_acl_action_t *action)
{
    vtss_policer_alloc_t *pol_alloc;
    vtss_policer_user_t  user;

    /* If policer is disabled, nothing is done */
    if ((pol_alloc = l26_acl_alloc_get(vtss_state, action, &user)) == NULL)
        return VTSS_RC_OK;
    
    if (pol_alloc->count == 0) {
        VTSS_E("policer %u already free", pol_alloc->policer);
        return VTSS_RC_ERROR;
    }
    pol_alloc->count--;
    if (pol_alloc->count == 0) {
        VTSS_RC(vtss_l26_policer_conf_set(vtss_state, user, pol_alloc->policer, 0, NULL));
    }
    return VTSS_RC_OK;
}

/* Allocate new ACL policer */
static vtss_rc l26_acl_policer_alloc(vtss_state_t *vtss_state, const vtss_acl_action_t *action)
{
    vtss_policer_alloc_t *pol_alloc;
    vtss_policer_user_t  user;

    /* If policer is disabled, nothing is done */
    if ((pol_alloc = l26_acl_alloc_get(vtss_state, action, &user)) == NULL)
        return VTSS_RC_OK;

    /* If policer is already allocated, just increment reference count */
    if (pol_alloc->count != 0) {
        pol_alloc->count++;
        return VTSS_RC_OK;
    }

    /* First reference, look for free policer */
    if (vtss_l26_policer_free_get(vtss_state, &pol_alloc->policer) == VTSS_RC_OK) {
        pol_alloc->count++;
        if (user == VTSS_POLICER_USER_ACL)
            return l26_acl_policer_set(vtss_state, action->policer_no);
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
        if (user == VTSS_POLICER_USER_EVC)
            return vtss_l26_evc_policer_conf_set(vtss_state, action->evc_policer_id);
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
    }
    VTSS_I("no more policers");
    return VTSS_RC_ERROR;
}

vtss_rc vtss_l26_acl_policer_move(vtss_state_t *vtss_state, u32 policer)
{
    vtss_policer_alloc_t *pol_alloc;
    u32                  policer_id;
    
    VTSS_I("policer: %u", policer);

    /* Look for the ACL policer mapping to this Luton26 policer */
    for (policer_id = 0; policer_id < VTSS_ACL_POLICERS; policer_id++) {
        pol_alloc = &vtss_state->vcap.acl_policer_alloc[policer_id];
        if (pol_alloc->count && pol_alloc->policer == policer) {
            VTSS_I("ACL policer: %u", policer_id);
            
            /* Find new free policer */
            VTSS_RC(vtss_l26_policer_free_get(vtss_state, &pol_alloc->policer));

            /* Update new ACL policer */
            VTSS_RC(l26_acl_policer_set(vtss_state, policer_id));

            /* Update rules to point to new policer */
            VTSS_RC(vtss_l26_acl_evc_policer_move(vtss_state, VTSS_POLICER_USER_ACL, policer_id,
                                                  policer, pol_alloc->policer));
            break;
        }
    }
    return VTSS_RC_OK;
}

/* Move references to new policer */
vtss_rc vtss_l26_acl_evc_policer_move(vtss_state_t *vtss_state,
                                      vtss_policer_user_t user, u32 policer_id,
                                      u16 policer_old, u16 policer_new)
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_S2];
    u32                entry[VTSS_TCAM_ENTRY_WIDTH];
    vtss_port_no_t     port_no;
    vtss_vcap_obj_t    *obj = &vtss_state->vcap.is2.obj;
    vtss_vcap_entry_t  *cur;
    vtss_is2_data_t    *is2;
    u32                i;
    
    VTSS_I("user: %u, old: %u, new: %u", user, policer_old, policer_new);

    /* Update default port actions for all ports */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(l26_is2_port_action_update(vtss_state, port_no));
    }

    /* Update IS2 entries using old policer */
    for (cur = obj->used, i = 0; cur != NULL; cur = cur->next, i++) {
        is2 = &cur->data.u.is2;
        if (cur->user == VTSS_IS2_USER_ACL && is2->policer_type != VTSS_L26_POLICER_NONE &&
            is2->policer == policer_id) {
            VTSS_I("move IS2 index %u", i);
            VTSS_RC(l26_vcap_index_command(vtss_state, tcam, i, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_ACTION));
            VTSS_RC(l26_vcap_cache2action(vtss_state, tcam, entry));
            vtss_bs_set(entry, 10, 8, policer_new);
            VTSS_RC(l26_vcap_action2cache(vtss_state, tcam, entry, 0));
            VTSS_RC(l26_vcap_index_command(vtss_state, tcam, i, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ACTION));
        }
    }

    /* Free old policer */
    return vtss_l26_policer_conf_set(vtss_state, user, policer_old, 0, NULL);
}

static vtss_rc l26_acl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_acl_port_conf_t *conf = &vtss_state->vcap.acl_port_conf[port_no];
    u32                  port = VTSS_CHIP_PORT(port_no), lookup = 0x1; // First lookup
    u32                  enable = (conf->policy_no == VTSS_ACL_POLICY_NO_NONE ? 0 : 1);

    /* Check if action is valid */
    VTSS_RC(l26_action_check(&conf->action));

    /* Free old policer and allocate new policer */
    VTSS_RC(l26_acl_policer_free(vtss_state, &vtss_state->vcap.acl_old_port_conf.action));
    VTSS_RC(l26_acl_policer_alloc(vtss_state, &conf->action));

    /* Enable/disable S2, set policy # */
    L26_WRM(VTSS_ANA_PORT_VCAP_CFG(port),
            (enable ? VTSS_F_ANA_PORT_VCAP_CFG_S2_ENA : 0) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_ARP_DIS(conf->key.arp == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_IP_TCPUDP_DIS(conf->key.ipv4 == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_IP_OTHER_DIS(conf->key.ipv4 == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_IP6_STD_DIS(conf->key.ipv6 == VTSS_ACL_KEY_EXT ? 0 : lookup) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_IP6_TCPUDP_OTHER_DIS(conf->key.ipv6 == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
            VTSS_F_ANA_PORT_VCAP_CFG_PAG_VAL(enable ? conf->policy_no : 0),
            VTSS_F_ANA_PORT_VCAP_CFG_S2_ENA |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_ARP_DIS(lookup) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_IP_TCPUDP_DIS(lookup) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_IP_OTHER_DIS(lookup) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_IP6_STD_DIS(lookup) |
            VTSS_F_ANA_PORT_VCAP_CFG_S2_IP6_TCPUDP_OTHER_DIS(lookup) |
            VTSS_M_ANA_PORT_VCAP_CFG_PAG_VAL);
    return l26_is2_port_action_update(vtss_state, port_no);
}

static vtss_rc l26_acl_port_counter_get(vtss_state_t *vtss_state,
                                        const vtss_port_no_t    port_no,
                                        vtss_acl_port_counter_t *const counter)
{
    return l26_is2_port_get(vtss_state, VTSS_CHIP_PORT(port_no), counter, 0);
}

static vtss_rc l26_acl_port_counter_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 counter;
    
    return l26_is2_port_get(vtss_state, VTSS_CHIP_PORT(port_no), &counter, 1);
}

/* Offset added to extra IP entry */
#define VTSS_ACE_ID_IP 0x100000000LL

static vtss_rc l26_is2_policer_free(vtss_state_t *vtss_state, vtss_is2_data_t *is2)
{
    vtss_acl_action_t action;
    
    if (is2->policer_type == VTSS_L26_POLICER_NONE)
        return VTSS_RC_OK;
    
    /* Convert IS2 policer data to ACL action */
    VTSS_MEMSET(&action, 0, sizeof(action));
    if (is2->policer_type == VTSS_L26_POLICER_ACL) {
        action.police = 1;
        action.policer_no = is2->policer;
    } else {
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
        action.evc_police = 1;
        action.evc_policer_id = is2->policer;
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
    }
    return l26_acl_policer_free(vtss_state, &action);
}

/* Add ACE */
static vtss_rc l26_ace_add(vtss_state_t *vtss_state,
                           const vtss_ace_id_t ace_id, const vtss_ace_t *const ace)
{
    vtss_vcap_obj_t             *is1_obj = &vtss_state->vcap.is1.obj;
    vtss_vcap_user_t            is1_user = VTSS_IS1_USER_ACL;
    vtss_vcap_obj_t             *is2_obj = &vtss_state->vcap.is2.obj;
    vtss_vcap_user_t            is2_user = VTSS_IS2_USER_ACL;
    vtss_vcap_data_t            data;
    vtss_is2_data_t             *is2 = &data.u.is2;
    vtss_is2_entry_t            entry;
    vtss_ace_t                  *ace_copy = &entry.ace;
    const vtss_ace_udp_tcp_t    *sport = NULL, *dport = NULL;
    vtss_vcap_id_t              id, id_next;
    u32                         old = 0, old_ptp = 0, old_ip = 0, new_ptp = 0, new_ip = 0;
    vtss_vcap_range_chk_table_t range_new = vtss_state->vcap.range; 
    u8                          policer_type;
    vtss_port_no_t              port_no;
    
    /*** Step 1: Check the simple things */
    VTSS_RC(l26_action_check(&ace->action));
    VTSS_RC(vtss_cmn_ace_add(vtss_state, ace_id, ace));

    /*** Step 2: Check if IS2 entries can be added */

    /* Initialize entry data */
    vtss_vcap_is2_init(&data, &entry);
    
    /* Check if main entry exists */
    if (vtss_vcap_lookup(vtss_state, is2_obj, is2_user, ace->id, &data, NULL) == VTSS_RC_OK) {
        is2->entry = &entry; /* NOTE: Restore entry pointer which was overwritten by vtss_vcap_lookup() */
        old = 1;
    }

    /* Check if PTP entry exists */
    if (vtss_vcap_lookup(vtss_state, is2_obj, VTSS_IS2_USER_ACL_PTP, ace->id,
                         NULL, NULL) == VTSS_RC_OK)
        old_ptp = 1;

    /* Check if extra IP entry exists */
    id = (ace->id + VTSS_ACE_ID_IP);
    if (vtss_vcap_lookup(vtss_state, is2_obj, is2_user, id, NULL, NULL) == VTSS_RC_OK)
        old_ip = 1;
    
    /* Check if PTP entry must be added */
    if ((ace->type == VTSS_ACE_TYPE_ETYPE && ace->frame.etype.ptp.enable) ||
        (ace->type == VTSS_ACE_TYPE_IPV4 && ace->frame.ipv4.ptp.enable) ||
        (ace->type == VTSS_ACE_TYPE_IPV6 && ace->frame.ipv6.ptp.enable))
        new_ptp = 1;
    
    /* Check if extra IP entry must be added */
    if ((ace->type == VTSS_ACE_TYPE_IPV4 && ace->frame.ipv4.proto.mask != 0xff) ||
        (ace->type == VTSS_ACE_TYPE_IPV6 && ace->frame.ipv6.proto.mask != 0xff))
        new_ip = 1;

    if ((is2_obj->count + new_ptp + new_ip) >= (is2_obj->max_count + old + old_ptp + old_ip)) {
        VTSS_I("IS2 is full");
        return VTSS_RC_ERROR;
    }

    /* Calculate next ID and check that it exists */
    id = (ace_id + VTSS_ACE_ID_IP);
    id_next = (vtss_vcap_lookup(vtss_state, is2_obj, is2_user, id, NULL, NULL) == VTSS_RC_OK ?
               id : ace_id);
    VTSS_RC(vtss_vcap_add(vtss_state, is2_obj, is2_user, ace->id, id_next, NULL, 0));
    
    /*** Step 3: Check if IS1 entry can be added */
    if (ace->type == VTSS_ACE_TYPE_IPV4 && ace->frame.ipv4.sip_smac.enable) {
        entry.host_match = 1;
        VTSS_RC(vtss_vcap_add(vtss_state, is1_obj, is1_user, ace->id, VTSS_ACE_ID_LAST, NULL, 0));
    }

    /*** Step 4: Allocate range checkers */
    /* Free any old range checkers */
    VTSS_RC(vtss_vcap_range_free(&range_new, is2->srange));
    VTSS_RC(vtss_vcap_range_free(&range_new, is2->drange));
    is2->srange = VTSS_VCAP_RANGE_CHK_NONE;
    is2->drange = VTSS_VCAP_RANGE_CHK_NONE;

    if (ace->type == VTSS_ACE_TYPE_IPV4 && vtss_vcap_udp_tcp_rule(&ace->frame.ipv4.proto)) {
        sport = &ace->frame.ipv4.sport;
        dport = &ace->frame.ipv4.dport;
    } 
    if (ace->type == VTSS_ACE_TYPE_IPV6 && vtss_vcap_udp_tcp_rule(&ace->frame.ipv6.proto)) {
        sport = &ace->frame.ipv6.sport;
        dport = &ace->frame.ipv6.dport;
    }

    if (sport && dport) {
        /* Allocate new range checkers */
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->srange, sport, 1));
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->drange, dport, 0));
    }

    /* Free old policer and allocate new policer */
    VTSS_RC(l26_is2_policer_free(vtss_state, is2));
    VTSS_RC(l26_acl_policer_alloc(vtss_state, &ace->action));

    /* Convert action to IS2 policer data */
    if (ace->action.police) {
        is2->policer_type = VTSS_L26_POLICER_ACL;
        is2->policer = ace->action.policer_no;
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
    } else if (ace->action.evc_police) {
        is2->policer_type = VTSS_L26_POLICER_EVC;
        is2->policer = ace->action.evc_policer_id;
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
    } else
        is2->policer_type = VTSS_L26_POLICER_NONE;
    policer_type = is2->policer_type;

    /* Commit range checkers */
    VTSS_RC(vtss_vcap_range_commit(vtss_state, &range_new));

    /*** Step 5: Add IS2 entries */

    /* Add main entry */
    *ace_copy = *ace;
    is2->entry = &entry;
    entry.first = 1;
    VTSS_MEMSET(&is2->action, 0, sizeof(is2->action));
    if (ace->action.port_action == VTSS_ACL_PORT_ACTION_REDIR) {
        is2->action.redir = 1;
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (ace->action.port_list[port_no]) {
                VTSS_PORT_BF_SET(is2->action.member, port_no, 1);
            }
        }
    }
    if (new_ptp) {
        /* Neutral actions for first PTP lookup */
        is2->action.redir = 0;
        is2->policer_type = VTSS_L26_POLICER_NONE;
        VTSS_MEMSET(&ace_copy->action, 0, sizeof(vtss_acl_action_t));
        ace_copy->action.learn = 1;
    }
    VTSS_RC(vtss_vcap_add(vtss_state, is2_obj, is2_user, ace->id, id_next, &data, 0));

    /* Check if PTP entry must be added */
    if (new_ptp) {
        /* Find next ID value */
        VTSS_RC(vtss_vcap_get_next_id(is2_obj, is2_user, VTSS_IS2_USER_ACL_PTP, ace->id, &id));
        
        /* Restore actions and add PTP entry */
        *ace_copy = *ace;
        entry.first = 0;
        is2->action.redir = (ace->action.port_action == VTSS_ACL_PORT_ACTION_REDIR);
        is2->policer_type = policer_type;
        VTSS_RC(vtss_vcap_add(vtss_state, is2_obj, VTSS_IS2_USER_ACL_PTP, ace->id, id, &data, 0));
    } else if (old_ptp) {
        /* Delete old PTP entry */
        VTSS_RC(vtss_vcap_del(vtss_state, is2_obj, VTSS_IS2_USER_ACL_PTP, ace->id));
    }

    /* Check if extra IP entry must be added */
    id = (ace->id + VTSS_ACE_ID_IP);
    if (new_ip) {
        vtss_ace_u8_t *proto = (ace->type == VTSS_ACE_TYPE_IPV4 ? 
                                &ace_copy->frame.ipv4.proto : &ace_copy->frame.ipv6.proto);
        entry.first = 1;
        entry.udp_tcp_any = 1;
        proto->mask = 0xff;
        proto->value = 6;
        VTSS_RC(vtss_vcap_add(vtss_state, is2_obj, is2_user, id, ace->id, &data, 0));
    } else if (old_ip) {
        /* Delete old IP entry */
        VTSS_RC(vtss_vcap_del(vtss_state, is2_obj, is2_user, id));
    }
    
    /*** Step 6: Add IS1 entry */
    if (entry.host_match) {
        vtss_is1_entry_t is1_entry;

        vtss_vcap_is1_init(&data, &is1_entry);
        is1_entry.key.type = VTSS_IS1_TYPE_SMAC_SIP;
        is1_entry.key.frame.smac_sip.port_no = VTSS_PORT_NO_NONE;
        is1_entry.key.frame.smac_sip.smac = ace->frame.ipv4.sip_smac.smac;
        is1_entry.key.frame.smac_sip.sip = ace->frame.ipv4.sip_smac.sip;
        is1_entry.action.host_match = 1;
        VTSS_RC(vtss_vcap_add(vtss_state, is1_obj, is1_user, ace->id, VTSS_ACE_ID_LAST, &data, 0));
    }   

    return VTSS_RC_OK;
}

/* Delete ACE */
static vtss_rc l26_ace_del(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    vtss_vcap_obj_t  *obj = &vtss_state->vcap.is2.obj;
    vtss_vcap_data_t data;
    
    /* Lookup main entry and free old policer */
    VTSS_RC(vtss_vcap_lookup(vtss_state, obj, VTSS_IS2_USER_ACL, ace_id, &data, NULL));
    VTSS_RC(l26_is2_policer_free(vtss_state, &data.u.is2));

    /* Delete main entry */
    VTSS_RC(vtss_cmn_ace_del(vtss_state, ace_id));

    /* Delete PTP entry */
    VTSS_RC(vtss_vcap_del(vtss_state, obj, VTSS_IS2_USER_ACL_PTP, ace_id));

    /* Delete extra IP entry */
    VTSS_RC(vtss_vcap_del(vtss_state, obj, VTSS_IS2_USER_ACL, ace_id + VTSS_ACE_ID_IP));

    /* Delete SMAC/SIP entry in IS1 */
    VTSS_RC(vtss_vcap_del(vtss_state, &vtss_state->vcap.is1.obj, VTSS_IS1_USER_ACL, ace_id));

    return VTSS_RC_OK;
}

/* Get/clear counter for extra IP ACE */
static vtss_rc l26_ace_get(vtss_state_t *vtss_state,
                           const vtss_ace_id_t ace_id, 
                           vtss_ace_counter_t *const counter, 
                           BOOL clear)
{
    vtss_vcap_obj_t *obj = &vtss_state->vcap.is2.obj;
    u32             cnt = 0;
    vtss_vcap_idx_t idx;

    /* Add/clear counter from extra IP entry */
    if (vtss_vcap_lookup(vtss_state, obj, VTSS_IS2_USER_ACL, ace_id + VTSS_ACE_ID_IP,
                         NULL, &idx) == VTSS_RC_OK) {
        VTSS_RC(obj->entry_get(vtss_state, &idx, &cnt, clear));
        if (counter != NULL)
            *counter += cnt;
    }

    return VTSS_RC_OK;
}

/* Get ACE counter */
static vtss_rc l26_ace_counter_get(vtss_state_t *vtss_state,
                                   const vtss_ace_id_t ace_id, vtss_ace_counter_t *const counter)
{
    VTSS_RC(vtss_cmn_ace_counter_get(vtss_state, ace_id, counter));
    return l26_ace_get(vtss_state, ace_id, counter, 0);
}

/* Clear ACE counter */
static vtss_rc l26_ace_counter_clear(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    VTSS_RC(vtss_cmn_ace_counter_clear(vtss_state, ace_id));
    return l26_ace_get(vtss_state, ace_id, NULL, 1);
}

/* Commit VCAP range checkers */
static vtss_rc l26_vcap_range_commit(vtss_state_t *vtss_state)
{
    u32                   i, type;
    vtss_vcap_range_chk_t *entry;
    
    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        entry = &vtss_state->vcap.range.entry[i];
        if (entry->count == 0)
            continue;
        switch (entry->type) {
        case VTSS_VCAP_RANGE_TYPE_SPORT:
            type = 2;
            break;
        case VTSS_VCAP_RANGE_TYPE_DPORT:
            type = 1;
            break;
        case VTSS_VCAP_RANGE_TYPE_SDPORT:
            type = 3;
            break;
        case VTSS_VCAP_RANGE_TYPE_VID:
            type = 4;
            break;
        case VTSS_VCAP_RANGE_TYPE_DSCP:
            type = 5;
            break;
        default:
            VTSS_E("illegal type: %d", entry->type);
            return VTSS_RC_ERROR;
        }
        L26_WR(VTSS_ANA_COMMON_VCAP_RNG_TYPE_CFG(i),
               VTSS_F_ANA_COMMON_VCAP_RNG_TYPE_CFG_VCAP_RNG_CFG(type));
        L26_WR(VTSS_ANA_COMMON_VCAP_RNG_VAL_CFG(i),
               VTSS_F_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MIN_VAL(entry->min) |
               VTSS_F_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MAX_VAL(entry->max))
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_ace_status_get(vtss_state_t *vtss_state,
                                  const vtss_ace_id_t ace_id, vtss_ace_status_t *const status)
{
    vtss_vcap_id_t    id = ace_id;
    vtss_vcap_entry_t *cur;
    u16               idx = 1, idx_0 = VTSS_ACE_IDX_NONE, idx_1 = VTSS_ACE_IDX_NONE;

    for (cur = vtss_state->vcap.is2.obj.used; cur != NULL; cur = cur->next, idx++) {
        if (cur->id == id) {
            if (cur->user == VTSS_IS2_USER_ACL_PTP) {
                /* Extra PTP entry */
                idx_1 = idx;
            } else {
                /* Normal entry */
                idx_0 = idx;
            }
        } else if (cur->id == (id + VTSS_ACE_ID_IP)) {
            /* Extra IP entry */
            idx_1 = idx;
        }
    }
    status->idx[0] = (idx_0 == VTSS_ACE_IDX_NONE ? idx_0 : (VTSS_L26_IS2_CNT - idx_0));
    status->idx[1] = (idx_1 == VTSS_ACE_IDX_NONE ? idx_1 : (VTSS_L26_IS2_CNT - idx_1));
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static void l26_debug_bits(const vtss_debug_printf_t pr, 
                           const char *name, u32 *entry, u32 *mask, u32 offset, u32 len)
{
    u32 i,j;

    if (name)
        pr("%s: ", name);
    for (i = 0; i < len; i++) {
        j = (len - 1 - i);
        if (i != 0 && (j % 8) == 7)
            pr(".");
        j += offset;
        pr("%c", mask == NULL || vtss_bs_bit_get(mask, j) ? 
           (vtss_bs_bit_get(entry, j) ? '1' : '0') : 'X');
    }
    pr(len > 23 ? "\n" : " ");
}

static void l26_debug_bit(const vtss_debug_printf_t pr, 
                          const char *name, u32 *entry, u32 *mask, u32 offset)
{
    l26_debug_bits(pr, name, entry, mask, offset, 1);
}

static void l26_debug_mac_bits(const vtss_debug_printf_t pr, 
                               const char *name, u32 *entry, u32 *mask, u32 offset)
{
    l26_debug_bits(pr, name, entry, mask, offset, 16);      /* MAC_HIGH */
    l26_debug_bits(pr, NULL, entry, mask, offset + 16, 32); /* MAC_LOW */
}

static void l26_debug_action(const vtss_debug_printf_t pr, 
                             const char *name, u32 *entry, u32 offs, u32 offs_val, u32 len)
{
    BOOL enable, multi = 0;
    u32  num = 0;
    int  i, length = VTSS_STRLEN(name);

    if (offs_val && (offs_val - offs) != 1) {
        /* 'Enable' field consists of multiple bits */
        multi = 1;
        num = vtss_bs_get(entry, offs, offs_val - offs);
        enable = (num ? 1 : 0);
    } else
        enable = vtss_bs_bit_get(entry, offs);
    
    for (i = 0; i < length; i++)
        pr("%c", enable ? toupper(name[i]) : tolower(name[i]));

    if (len) {
        pr(":");
        if (multi)
            pr("%u/", num);
        pr("%u", vtss_bs_get(entry, offs_val, len));
    }
    pr(" ");
}

static void l26_debug_fld(const vtss_debug_printf_t pr, 
                          const char *name, u32 *entry, u32 offs, u32 len)
{
    pr("%s:%u ", name, vtss_bs_get(entry, offs, len));
}

static vtss_rc l26_debug_is1(vtss_state_t *vtss_state,
                             u32 *entry, u32 *mask, u32 typegroup, u32 cnt, 
                             const vtss_debug_printf_t pr)
{
    if (mask == NULL) {
        /* Print action */
        if (vtss_bs_get(entry, 0, 2) == IS1_ACTION_TYPE_NORMAL) {
            /* Normal IS1 action */
            l26_debug_action(pr, "dscp", entry, 2, 3, 6);   /* DSCP_ENA/DSCP_VAL */
            l26_debug_action(pr, "dp", entry, 9, 10, 1);    /* DP_ENA/DP_VAL */
            l26_debug_action(pr, "qos", entry, 11, 12, 3);  /* QOS_ENA/QOS_VAL */
            l26_debug_action(pr, "pag", entry, 15, 16, 8);  /* PAG_ENA/PAG_VAL */
            l26_debug_action(pr, "vid", entry, 24, 25, 12); /* VID_ENA/VID_VAL */
            l26_debug_action(pr, "pcp", entry, 51, 52, 3);  /* PCP_DEI_ENA/PCP_VAL */
            l26_debug_action(pr, "dei", entry, 55, 0, 0);   /* DEI_VAL */
            l26_debug_action(pr, "pop", entry, 56, 57, 2);  /* POP_ENA/POP_VAL */
            l26_debug_action(pr, "hm", entry, 59, 0, 0);    /* HOST_MATCH */
            l26_debug_action(pr, "fid", entry, 37, 39, 12); /* FID_SEL & FID_VAL */
        } else {
            /* SMAC/SIP action */
            l26_debug_action(pr, "hm", entry, 2, 0, 0); /* HOST_MATCH */
        }
        pr("cnt:%u", cnt);                             /* HIT_STICKY */
        return VTSS_RC_OK;
    }
    
    /* Print entry */
    if (typegroup == VCAP_TG_VAL_IS1_IP4) {
        /* SMAC/SIP4 entry */
        l26_debug_bits(pr, "igr_port", entry, mask, 0, 5);
        pr("\n");
        l26_debug_mac_bits(pr, "l2_smac", entry, mask, 5);
        l26_debug_bits(pr, "l3_ip_sip", entry, mask, 53, 32);
        return VTSS_RC_OK;
    }

    l26_debug_bit(pr, "is1_type", entry, mask, 0);
    if (vtss_bs_get(entry, 0, 1)) {
        /* SMAC/SIP6 entry */
        l26_debug_bits(pr, "igr_port", entry, mask, 1, 5);
        pr("\n");
        l26_debug_mac_bits(pr, "l2_smac", entry, mask, 6);
        l26_debug_bits(pr, "sip_3", entry, mask, 54, 32);
        l26_debug_bits(pr, "sip_2", entry, mask, 86, 32);
        l26_debug_bits(pr, "sip_1", entry, mask, 118, 32);
        l26_debug_bits(pr, "sip_0", entry, mask, 150, 32);
        return VTSS_RC_OK;
    }

    l26_debug_bit(pr, "first", entry, mask, 1);
    l26_debug_bits(pr, "igr_port_mask", entry, mask, 2, 27);
    l26_debug_bit(pr, "vlan_tagged", entry, mask, 29);
    l26_debug_bit(pr, "vlan_dbl_tagged", entry, mask, 30);
    l26_debug_bit(pr, "tpid", entry, mask, 31);
    pr("\n");
    l26_debug_bits(pr, "vid", entry, mask, 32, 12);
    l26_debug_bit(pr, "dei", entry, mask, 44);
    l26_debug_bits(pr, "pcp", entry, mask, 45, 3);
    pr("\n");
    l26_debug_mac_bits(pr, "l2_smac", entry, mask, 48);
    l26_debug_bit(pr, "l2_mc", entry, mask, 96);
    l26_debug_bit(pr, "l2_bc", entry, mask, 97);
    l26_debug_bit(pr, "ip_mc", entry, mask, 98);
    pr("\n");
    l26_debug_bits(pr, "etype", entry, mask, 100, 16);
    pr("\n");
    l26_debug_bit(pr, "etype_len", entry, mask, 99);
    l26_debug_bit(pr, "ip_snap", entry, mask, 116);
    l26_debug_bit(pr, "ip4", entry, mask, 117);
    pr("\n");
    l26_debug_bit(pr, "l3_fragment", entry, mask, 118);
    l26_debug_bit(pr, "l3_options", entry, mask, 119);
    l26_debug_bits(pr, "l3_dscp", entry, mask, 120, 6);
    pr("\n");
    l26_debug_bits(pr, "l3_ip4_sip", entry, mask, 126, 32);
    l26_debug_bit(pr, "tcp_udp", entry, mask, 158);
    l26_debug_bit(pr, "tcp", entry, mask, 159);
    l26_debug_bits(pr, "l4_sport", entry, mask, 160, 16);
    l26_debug_bits(pr, "l4_rng", entry, mask, 176, 8);
    pr("\n");
    
    return VTSS_RC_OK;
}

static vtss_rc l26_debug_is2(vtss_state_t *vtss_state,
                             u32 *entry, u32 *mask, u32 typegroup, u32 cnt, 
                             const vtss_debug_printf_t pr)
{
    u32 is2type, mode;

    if (mask == NULL) {
        /* Print action */
        mode = vtss_bs_get(entry, 5, 2);              /* MASK_MODE */
        pr("mode:%u (%s) ", 
           mode, 
           mode == 0 ? "none" : mode == 1 ? "filter" : mode == 2 ? "policy" : "redir");
        l26_debug_bits(pr, "mask", entry, NULL, 18, 26); /* PORT_MASK */
        l26_debug_action(pr, "hit", entry, 0, 0, 0);  /* HIT_ME_ONCE */
        l26_debug_action(pr, "cpu", entry, 1, 2, 3);  /* CPU_COPY_ENA/CPU_QU_NUM */
        l26_debug_action(pr, "mir", entry, 7, 0, 0);  /* MIRROR_ENA */
        l26_debug_action(pr, "lrn", entry, 8, 0, 0);  /* LRN_DIS */
        l26_debug_action(pr, "pol", entry, 9, 10, 8); /* POLICER_ENA/POLICE_IDX */
        l26_debug_action(pr, "one", entry, 44, 0, 0); /* PTP_ENA[0] */
        l26_debug_action(pr, "two", entry, 45, 0, 0); /* PTP_ENA[1] */
        pr("cnt:%u ", cnt);                          /* HIT_CNT */
        return VTSS_RC_OK;
    }
    
    /* Print entry */
    l26_debug_bits(pr, "type", entry, mask, 0, 3);
    is2type = vtss_bs_get(entry, 0, 3);
    pr("(%s) ", 
       vtss_bs_get(mask, 0, 3) == 0 ? "any" :
       is2type == ACL_TYPE_ETYPE ? "etype" :
       is2type == ACL_TYPE_LLC ? "llc" :
       is2type == ACL_TYPE_SNAP ? "snap" :
       is2type == ACL_TYPE_ARP ? "arp" :
       is2type == ACL_TYPE_UDP_TCP ? "udp_tcp" :
       is2type == ACL_TYPE_IPV4 ? "ipv4" :
       is2type == ACL_TYPE_IPV6 ? "ipv6" : "?");
    l26_debug_bit(pr, "first", entry, mask, 3);
    l26_debug_bits(pr, "pag", entry, mask, 4, 8);
    l26_debug_bits(pr, "igr", entry, mask, 12, 27);
    l26_debug_bit(pr, "vlan", entry, mask, 39);
    l26_debug_bit(pr, "host", entry, mask, 40);
    l26_debug_bits(pr, "vid", entry, mask, 41, 12);
    l26_debug_bit(pr, "dei", entry, mask, 53);
    l26_debug_bits(pr, "pcp", entry, mask, 54, 3);
    pr("\n");
    
    switch(is2type) {
    case ACL_TYPE_ETYPE:
    case ACL_TYPE_LLC:
    case ACL_TYPE_SNAP:
        /* Common format */
        l26_debug_mac_bits(pr, "l2_dmac", entry, mask, 57);
        l26_debug_mac_bits(pr, "l2_smac", entry, mask, 105);
        l26_debug_bit(pr, "l2_mc", entry, mask, 153);
        l26_debug_bit(pr, "l2_bc", entry, mask, 154);
        pr("\n");
        
        /* Specific format */
        switch (is2type) {
        case ACL_TYPE_ETYPE:
            l26_debug_bits(pr, "etype", entry, mask, 155, 16);
            l26_debug_bits(pr, "l2_payload", entry, mask, 171, 16);
            pr("\n");
            break;
        case ACL_TYPE_LLC:
            l26_debug_bits(pr, "l2_llc", entry, mask, 155, 32);
            break;
        case ACL_TYPE_SNAP:
            l26_debug_bits(pr, "l2_snap", entry, mask, 155, 8);
            l26_debug_bits(pr, NULL, entry, mask, 163, 32);
            break;
        }
        break;
    case ACL_TYPE_ARP:
        l26_debug_mac_bits(pr, "l2_smac", entry, mask, 57);
        l26_debug_bit(pr, "l2_mc", entry, mask, 105);
        l26_debug_bit(pr, "l2_bc", entry, mask, 106);
        l26_debug_bit(pr, "addr_ok", entry, mask, 107);
        l26_debug_bit(pr, "proto_ok", entry, mask, 108);
        l26_debug_bit(pr, "len_ok", entry, mask, 109);
        pr("\n");
        l26_debug_bit(pr, "t_match", entry, mask, 110);
        l26_debug_bit(pr, "s_match", entry, mask, 111);
        l26_debug_bit(pr, "op_unk", entry, mask, 112);
        l26_debug_bits(pr, "op", entry, mask, 113, 2);
        l26_debug_bit(pr, "dip_eq_sip", entry, mask, 179);
        pr("\n");
        l26_debug_bits(pr, "l3_ip4_dip", entry, mask, 115, 32);
        l26_debug_bits(pr, "l3_ip4_sip", entry, mask, 147, 32);
        break;
    case ACL_TYPE_UDP_TCP:
    case ACL_TYPE_IPV4:
        /* Common format */
        l26_debug_bit(pr, "l2_mc", entry, mask, 57);
        l26_debug_bit(pr, "l2_bc", entry, mask, 58);
        l26_debug_bit(pr, "ip4", entry, mask, 59);
        l26_debug_bit(pr, "l3_fragment", entry, mask, 60);
        l26_debug_bit(pr, "l3_fragoffs", entry, mask, 61);
        l26_debug_bit(pr, "l3_options", entry, mask, 62);
        l26_debug_bit(pr, "l3_ttl", entry, mask, 63);
        pr("\n");
        l26_debug_bits(pr, "l3_tos", entry, mask, 64, 8);
        
        /* Specific format */
        if (is2type == ACL_TYPE_UDP_TCP) {
            pr("\n");
            l26_debug_bits(pr, "l3_ip4_dip", entry, mask, 81, 32);
            l26_debug_bits(pr, "l3_ip4_sip", entry, mask, 113, 32);
            l26_debug_bits(pr, "l4_dport", entry, mask, 146, 16);
            l26_debug_bits(pr, "l4_sport", entry, mask, 162, 16);
            l26_debug_bits(pr, "l4_rng", entry, mask, 178, 8);
            pr("\n");
            l26_debug_bit(pr, "tcp", entry, mask, 72);
            l26_debug_bits(pr, "1588_dom", entry, mask, 73, 8);
            l26_debug_bit(pr, "dip_eq_sip", entry, mask, 145);
            l26_debug_bit(pr, "sp_eq_dp", entry, mask, 186);
            pr("\n");
            l26_debug_bit(pr, "seq_eq0", entry, mask, 187);
            l26_debug_bit(pr, "fin", entry, mask, 188);
            l26_debug_bit(pr, "syn", entry, mask, 189);
            l26_debug_bit(pr, "rst", entry, mask, 190);
            l26_debug_bit(pr, "psh", entry, mask, 191);
            l26_debug_bit(pr, "ack", entry, mask, 192);
            l26_debug_bit(pr, "urg", entry, mask, 193);
            pr("\n");
        } else {
            l26_debug_bits(pr, "proto", entry, mask, 72, 8);
            l26_debug_bit(pr, "dip_eq_sip", entry, mask, 144);
            pr("\n");
            l26_debug_bits(pr, "l3_ip4_dip", entry, mask, 80, 32);
            l26_debug_bits(pr, "l3_ip4_sip", entry, mask, 112, 32);
            l26_debug_mac_bits(pr, "l3_payload", entry, mask, 145);
        }
        break;
    case ACL_TYPE_IPV6:
        l26_debug_bit(pr, "l2_mc", entry, mask, 57);
        l26_debug_bit(pr, "l2_bc", entry, mask, 58);
        l26_debug_bits(pr, "proto", entry, mask, 59, 8);
        pr("\n");
        l26_debug_bits(pr, "sip_3", entry, mask, 67, 32);
        l26_debug_bits(pr, "sip_2", entry, mask, 99, 32);
        l26_debug_bits(pr, "sip_1", entry, mask, 131, 32);
        l26_debug_bits(pr, "sip_0", entry, mask, 163, 32);
        break;
    default:
        VTSS_E("Invalid IS2 type: %d", is2type);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}
    
static vtss_rc l26_debug_es0(vtss_state_t *vtss_state,
                             u32 *entry, u32 *mask, u32 typegroup, u32 cnt, 
                             const vtss_debug_printf_t pr)
{
    u32 val;

    if (mask == NULL) {
        /* Print action */
        l26_debug_bit(pr, "vld", entry, NULL, 0); /* VLD */
        val = vtss_bs_get(entry, 1, 2);           /* TAG_ES0 */
        pr("tag_es0:%u (%s) ", 
           val, 
           val == VTSS_ES0_TAG_NONE ? "none" : val == VTSS_ES0_TAG_ES0 ? "es0" : 
           val == VTSS_ES0_TAG_PORT ? "port" : "both");
        val = vtss_bs_get(entry, 3, 2);               /* TAG_TPID_SEL */
        pr("tag_tpid_sel:%u (%s) ",
           val,
           val == VTSS_ES0_TPID_C ? "c" : val == VTSS_ES0_TPID_S ? "s" : 
           val == VTSS_ES0_TPID_PORT ? "port" : "c/port");
        l26_debug_fld(pr, "tag_vid_sel", entry, 5, 2); /* TAG_VID_SEL */
        pr("\n");
        l26_debug_fld(pr, "vid_a", entry, 7, 12);      /* VID_A_VAL */
        l26_debug_fld(pr, "vid_b", entry, 19, 12);     /* VID_B_VAL */
        val = vtss_bs_get(entry, 31, 2);               /* QOS_SRC_SEL */
        pr("qos_src_sel:%u (%s) ",
           val,
           val == VTSS_ES0_QOS_CLASS ? "class" : val == VTSS_ES0_QOS_ES0 ? "es0" :
           val == VTSS_ES0_QOS_PORT ? "port" : "mapped");
        l26_debug_fld(pr, "pcp", entry, 33, 3);    /* PCP_VAL */
        l26_debug_bit(pr, "dei", entry, NULL, 36); /* DEI_VAL */
        pr("cnt:%u ", cnt);                       /* HIT_CNT */
        return VTSS_RC_OK;
    }
    
    /* Print entry */
    l26_debug_bits(pr, "egr_port", entry, mask, 0, 5);
    l26_debug_bits(pr, "igr_port", entry, mask, 5, 5);
    pr("\n");
    l26_debug_bits(pr, "vid", entry, mask, 10, 12);
    l26_debug_bit(pr, "dei", entry, mask, 22);
    l26_debug_bits(pr, "pcp", entry, mask, 23, 3);
    l26_debug_bit(pr, "l2_mc", entry, mask, 26);
    l26_debug_bit(pr, "l2_bc", entry, mask, 27);
    pr("\n");
    
    return VTSS_RC_OK;
}
    
#define L26_DEBUG_VCAP(pr, name, tgt) vtss_l26_debug_reg(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CONST_##name(tgt), #name)

static vtss_rc l26_debug_vcap(vtss_state_t *vtss_state,
                              int bank,
                              const char *name,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info,
                              vtss_rc (* dbg)(vtss_state_t *vtss_state,
                                              u32 *entry, u32 *mask, u32 typegroup, u32 cnt,
                                              const vtss_debug_printf_t pr))
{
    /*lint --e{454, 455, 456) */ // Due to VTSS_EXIT_ENTER
    const tcam_props_t *tcam = &tcam_info[bank];
    u32                entry[VTSS_TCAM_ENTRY_WIDTH];
    u32                mask[VTSS_TCAM_ENTRY_WIDTH];
    int                i, j, sel;
    u32                cnt, typegroup, tgt;
    BOOL               is_entry;
    
    vtss_debug_print_header(pr, name);
    
    vtss_l26_debug_reg_header(pr, "VCAP_CONST");
    tgt = tcam->target;
    L26_DEBUG_VCAP(pr, ENTRY_WIDTH, tgt);
    L26_DEBUG_VCAP(pr, ENTRY_CNT, tgt);
    L26_DEBUG_VCAP(pr, ENTRY_SWCNT, tgt);
    L26_DEBUG_VCAP(pr, ENTRY_TG_WIDTH, tgt);
    L26_DEBUG_VCAP(pr, ACTION_DEF_CNT, tgt);
    L26_DEBUG_VCAP(pr, ACTION_WIDTH, tgt);
    L26_DEBUG_VCAP(pr, CNT_WIDTH, tgt);
    pr("\n");
    
    for (i = (tcam->actions - 1); i >= 0; i--) {
        /* Leave critical region briefly */
        VTSS_EXIT_ENTER();

        /* Read entry */
        is_entry = (i < tcam->entries);
        if (is_entry &&
            l26_vcap_command(vtss_state, tcam, i, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_ENTRY) == VTSS_RC_OK &&
            l26_vcap_cache2entry(vtss_state, tcam, entry, mask) == VTSS_RC_OK) {
            L26_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_TG_DAT(tcam->target), &typegroup);
            
            /* Skip invalid entries */
            if (typegroup == 0)
                continue;

            /* Print entry */
            VTSS_RC(dbg(vtss_state, entry, mask, typegroup, 0, pr));
            pr("\n");

            if (info->full) {
                vtss_l26_debug_reg_header(pr, "VCAP");
                vtss_l26_debug_reg(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_TG_DAT(tcam->target), "TG_DAT");
                for (j = 0; j < tcam->entry_width; j++) {
                    vtss_l26_debug_reg_inst(vtss_state, pr,VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tcam->target, j), j, "ENTRY_DAT");
                    vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tcam->target, j), j, "ENTRY_MASK");
                }
                pr("\n");
            }
        } else
            typegroup = 0;
        
        /* Read action and counter */
        sel = (VTSS_TCAM_SEL_ACTION | VTSS_TCAM_SEL_COUNTER);
        if (l26_vcap_command(vtss_state, tcam, i, VTSS_TCAM_CMD_READ, sel) != VTSS_RC_OK ||
            l26_vcap_cache2action(vtss_state, tcam, entry) != VTSS_RC_OK)
            continue;
        L26_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tcam->target, 0), &cnt);

        /* Clear counter and write back */
        if (info->full) {
            L26_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tcam->target, 0), 0);
            if (l26_vcap_command(vtss_state, tcam, i, VTSS_TCAM_CMD_WRITE, sel) != VTSS_RC_OK)
                continue;
        }
        
        /* Print action */
        pr("%d (%s %d): ", i, is_entry ? "rule" : "port", 
           is_entry ? (tcam->entries - i - 1) : (i - tcam->entries));
        VTSS_RC(dbg(vtss_state, entry, NULL, typegroup, cnt, pr));
        pr("\n-------------------------------------------\n");
    }
    pr("\n");
    return VTSS_RC_OK;
}
    
vtss_rc vtss_l26_debug_vcap_is1(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    return l26_debug_vcap(vtss_state, VTSS_TCAM_S1, "IS1", pr, info, l26_debug_is1);
}

vtss_rc vtss_l26_debug_vcap_es0(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    return l26_debug_vcap(vtss_state, VTSS_TCAM_ES0, "ES0", pr, info, l26_debug_es0);
}

vtss_rc vtss_l26_debug_range_checkers(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    u32 i;
    
    vtss_l26_debug_reg_header(pr, "Range Checkers");
    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_COMMON_VCAP_RNG_TYPE_CFG(i), i, "RNG_TYPE_CFG");
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_COMMON_VCAP_RNG_VAL_CFG(i), i, "RNG_VAL_CFG");
    }
    pr("\n");
    return VTSS_RC_OK;
}

vtss_rc vtss_l26_debug_vcap_port(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    u32 port;
    
    vtss_l26_debug_reg_header(pr, "ANA:VCAP_CFG");
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_VCAP_CFG(port), port, "VCAP_CFG");
    }
    pr("\n");
    return VTSS_RC_OK;
}

static vtss_rc l26_debug_acl(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_l26_debug_range_checkers(vtss_state, pr, info));
    VTSS_RC(vtss_l26_debug_vcap_port(vtss_state, pr, info));
    VTSS_RC(vtss_l26_debug_vcap_is1(vtss_state, pr, info));
    VTSS_RC(l26_debug_vcap(vtss_state, VTSS_TCAM_S2, "IS2", pr, info, l26_debug_is2));
    
    return VTSS_RC_OK;
}

vtss_rc vtss_l26_vcap_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_ACL, l26_debug_acl, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc l26_vcap_init(vtss_state_t *vtss_state)
{
    u32 port;

    /* Disable Port ACLs */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        L26_WRM_CLR(VTSS_ANA_PORT_VCAP_CFG(port), 
                    VTSS_F_ANA_PORT_VCAP_CFG_S1_ENA|
                    VTSS_F_ANA_PORT_VCAP_CFG_S2_ENA); /* Disable S1/S2 VCAP */
        L26_WRM_CLR(VTSS_REW_PORT_PORT_CFG(port),
                    VTSS_F_REW_PORT_PORT_CFG_ES0_ENA); /* Disable ES0 */
    }
    /* Clear ACL table */
    VTSS_RC(l26_vcap_initialize(vtss_state, &tcam_info[VTSS_TCAM_S1]));
    VTSS_RC(l26_vcap_initialize(vtss_state, &tcam_info[VTSS_TCAM_S2]));
    VTSS_RC(l26_vcap_initialize(vtss_state, &tcam_info[VTSS_TCAM_ES0]));

    /* Enable Port ACLs (no entries) */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        /* Enable S1 and S2, PTP in S2 second lookup and treat IPv6 as IPv4 in both S2 lookups */
        L26_WR(VTSS_ANA_PORT_VCAP_CFG(port), 
               VTSS_F_ANA_PORT_VCAP_CFG_S1_ENA |
               VTSS_F_ANA_PORT_VCAP_CFG_S2_UDP_PAYLOAD_ENA(2) |
               VTSS_F_ANA_PORT_VCAP_CFG_S2_ETYPE_PAYLOAD_ENA(2) |
               VTSS_F_ANA_PORT_VCAP_CFG_S2_ENA |
               VTSS_F_ANA_PORT_VCAP_CFG_S2_IP6_STD_DIS(3));
        L26_WRM_SET(VTSS_REW_PORT_PORT_CFG(port),
                    VTSS_F_REW_PORT_PORT_CFG_ES0_ENA); /* Enable ES0 */
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_vcap_state_t *state = &vtss_state->vcap;
    vtss_vcap_obj_t   *is1 = &state->is1.obj;
    vtss_vcap_obj_t   *is2 = &state->is2.obj;
    vtss_vcap_obj_t   *es0 = &state->es0.obj;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        /* IS1 */
        is1->max_count = VTSS_L26_IS1_CNT;
        is1->entry_get = l26_is1_entry_get;
        is1->entry_add = l26_is1_entry_add;
        is1->entry_del = l26_is1_entry_del;
        is1->entry_move = l26_is1_entry_move;
        
        /* IS2 */
        is2->max_count = VTSS_L26_IS2_CNT;
        is2->entry_get = l26_is2_entry_get;
        is2->entry_add = l26_is2_entry_add;
        is2->entry_del = l26_is2_entry_del;
        is2->entry_move = l26_is2_entry_move;
        state->is2_entry_update = l26_is2_entry_update;
        
        /* ES0 */
        es0->max_count = VTSS_L26_ES0_CNT;
        es0->entry_get = l26_es0_entry_get;
        es0->entry_add = l26_es0_entry_add;
        es0->entry_del = l26_es0_entry_del;
        es0->entry_move = l26_es0_entry_move;
        state->es0_entry_update = l26_es0_entry_update;

        /* ACL */
        state->acl_policer_set = l26_acl_policer_set;
        state->acl_port_set = l26_acl_port_conf_set;
        state->acl_port_counter_get = l26_acl_port_counter_get;
        state->acl_port_counter_clear = l26_acl_port_counter_clear;
        state->acl_ace_add = l26_ace_add;
        state->acl_ace_del = l26_ace_del;
        state->acl_ace_counter_get = l26_ace_counter_get;
        state->acl_ace_counter_clear = l26_ace_counter_clear;
        state->range_commit = l26_vcap_range_commit;
        state->acl_ace_status_get = l26_ace_status_get;

        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(l26_vcap_init(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LUTON26 */
