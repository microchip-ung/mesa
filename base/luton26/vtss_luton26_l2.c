// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L2
#include "vtss_luton26_cil.h"

#if defined(VTSS_ARCH_LUTON26)

/* - CIL functions ------------------------------------------------- */

/* Convert to PGID in chip */
static u32 l26_chip_pgid(vtss_state_t *vtss_state, u32 pgid)
{
    if (pgid < vtss_state->port_count) {
        return VTSS_CHIP_PORT(pgid);
    } else {
        return (pgid + VTSS_CHIP_PORTS - vtss_state->port_count);
    }
}

/* Convert from PGID in chip */
static u32 l26_vtss_pgid(vtss_state_t *vtss_state, u32 pgid)
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

static vtss_rc l26_pgid_mask_write(vtss_state_t *vtss_state, u32 pgid, BOOL member[],
                                   BOOL cpu_copy, vtss_packet_rx_queue_t cpu_queue)
{
    u32 mask = vtss_l26_port_mask(vtss_state, member);
    u32 queue = 0;
    
    if (cpu_copy) {
        mask |= VTSS_BIT(VTSS_CHIP_PORT_CPU);
        queue = cpu_queue;
    }
    L26_WR(VTSS_ANA_ANA_TABLES_PGID(pgid),
           VTSS_F_ANA_ANA_TABLES_PGID_PGID(mask) |
           VTSS_F_ANA_ANA_TABLES_PGID_CPUQ_DST_PGID(queue));
    return VTSS_RC_OK;
}

/* Write PGID entry */
static vtss_rc l26_pgid_table_write(vtss_state_t *vtss_state, u32 pgid, BOOL member[])
{
    vtss_pgid_entry_t *pgid_entry = &vtss_state->l2.pgid_table[pgid];

    return l26_pgid_mask_write(vtss_state, l26_chip_pgid(vtss_state, pgid), member, 
                               pgid_entry->cpu_copy, pgid_entry->cpu_queue);
}

/* Update PGID table for reserved entry */
static vtss_rc l26_pgid_update(vtss_state_t *vtss_state, u32 pgid, BOOL member[])
{
    vtss_port_no_t    port_no;
    vtss_pgid_entry_t *pgid_entry;
    
    pgid = l26_vtss_pgid(vtss_state, pgid);
    pgid_entry = &vtss_state->l2.pgid_table[pgid];
    pgid_entry->resv = 1;
    pgid_entry->references = 1;
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
        pgid_entry->member[port_no] = member[port_no];
    
    return l26_pgid_table_write(vtss_state, pgid, member);
}

/* Write the aggregation masks  */
static vtss_rc l26_aggr_table_write(vtss_state_t *vtss_state,
                                    u32 ac, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return l26_pgid_mask_write(vtss_state, PGID_AGGR + ac, member, 0, 0);
}

/* Write source mask */
static vtss_rc l26_src_table_write(vtss_state_t *vtss_state,
                                   vtss_port_no_t port_no, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return l26_pgid_mask_write(vtss_state, PGID_SRC + VTSS_CHIP_PORT(port_no), member, 0, 0);
}

/* Write the aggregation mode  */
static vtss_rc l26_aggr_mode_set(vtss_state_t *vtss_state)
{
    vtss_aggr_mode_t *mode = &vtss_state->l2.aggr_mode;

    L26_WR(VTSS_ANA_COMMON_AGGR_CFG,
           (mode->sip_dip_enable     ? VTSS_F_ANA_COMMON_AGGR_CFG_AC_IP4_SIPDIP_ENA : 0) |
           (mode->sport_dport_enable ? VTSS_F_ANA_COMMON_AGGR_CFG_AC_IP4_TCPUDP_ENA : 0) |
           (mode->dmac_enable        ? VTSS_F_ANA_COMMON_AGGR_CFG_AC_DMAC_ENA       : 0) |
           (mode->smac_enable        ? VTSS_F_ANA_COMMON_AGGR_CFG_AC_SMAC_ENA       : 0));
    return VTSS_RC_OK;
}

/* Write the common logical port of the aggr. group (lowest port no. of the group) */
static vtss_rc l26_pmap_table_write(vtss_state_t *vtss_state,
                                    vtss_port_no_t port_no, vtss_port_no_t l_port_no)
{
    L26_WRM(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT(port_no)), 
            VTSS_F_ANA_PORT_PORT_CFG_PORTID_VAL(VTSS_CHIP_PORT(l_port_no)), 
            VTSS_M_ANA_PORT_PORT_CFG_PORTID_VAL);

    return VTSS_RC_OK;
}

/* ================================================================= *
 *  IP Multicast
 * ================================================================= */

/* Allocate FID for IPMC SSM */
static vtss_rc l26_ip_mc_fid_alloc(vtss_state_t *vtss_state, vtss_vid_t *fid, BOOL ipv6, BOOL add)
{
    u8                mask = (ipv6 ? IPMC_USED_IPV6 : IPMC_USED_IPV4);
    vtss_vid_t        vid, fid_free = VTSS_VID_NULL;
    vtss_vlan_entry_t *vlan_entry;

    /* Search for free VID from 4094 -> 2 */
    for (vid = (VTSS_VID_RESERVED - 1); vid > VTSS_VID_DEFAULT; vid--) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if ((vlan_entry->flags & VLAN_FLAGS_ENABLED) || (vlan_entry->ipmc_used & mask) != 0)
            continue;
        
        if (vlan_entry->ipmc_used == IPMC_USED_NONE) {
            /* First completely free entry may be used */
            if (fid_free == VTSS_VID_NULL)
                fid_free = vid;
        } else {
            /* First entry used by the other IP version is preferred */
            fid_free = vid;
            break;
        }
    }

    if (fid_free != VTSS_VID_NULL) {
        /* Free FID was found */
        if (add)
            vtss_state->l2.vlan_table[fid_free].ipmc_used |= mask;
        *fid = fid_free;
        return VTSS_RC_OK;
    }

    VTSS_I("no more FIDs");
    return VTSS_RC_ERROR;
}

/* Free FID for IPMC SSM */
static vtss_rc l26_ip_mc_fid_free(vtss_state_t *vtss_state, vtss_vid_t fid, BOOL ipv6)
{
    u8                mask = (ipv6 ? IPMC_USED_IPV6 : IPMC_USED_IPV4);
    vtss_vlan_entry_t *vlan_entry = &vtss_state->l2.vlan_table[fid];

    if (vlan_entry->ipmc_used & mask) {
        vlan_entry->ipmc_used -= mask;
        return VTSS_RC_OK;
    }
    VTSS_E("FID %u already free for IPv%u", fid, ipv6 ? 6 : 4);
    return VTSS_RC_ERROR;
}

/* Convert DIP to MAC address */
static void l26_ip_mc_mac_get(vtss_vid_mac_t *vid_mac, vtss_ipmc_dst_data_t *dst, BOOL ipv6)
{
    u8 i, *mac_addr = &vid_mac->mac.addr[0];
    
    if (ipv6) {
        for (i = 0; i < 6; i++) {
            mac_addr[i] = (i < 2 ? 0x33 : dst->dip.ipv6.addr[10 + i]);
        }
    } else {
        mac_addr[0] = 0x01;
        mac_addr[1] = 0x00;
        mac_addr[2] = 0x5e;
        mac_addr[3] = ((dst->dip.ipv4 >> 16) & 0x7f);
        mac_addr[4] = ((dst->dip.ipv4 >> 8) & 0xff);
        mac_addr[5] = (dst->dip.ipv4 & 0xff);
    }
}

/* Calculate IS1 VCAP ID for source */
static vtss_vcap_id_t l26_ip_mc_vcap_id(vtss_ipmc_src_data_t *src, BOOL ipv6)
{
    vtss_vcap_id_t id = ipv6;
    
    id = ((id << 31) + src->vid);
    id = ((id << 32) + vtss_cmn_ip2u32(&src->sip, ipv6));
    return id;
}

/* Add IS1 entry for source */
static vtss_rc l26_ip_mc_is1_add(vtss_state_t *vtss_state, vtss_ipmc_src_data_t *src, BOOL ipv6)
{
    vtss_vcap_obj_t   *obj = &vtss_state->vcap.is1.obj;
    vtss_vcap_data_t  data;
    vtss_is1_entry_t  entry;
    vtss_is1_action_t *action = &entry.action;
    vtss_is1_key_t    *key = &entry.key;
    vtss_vcap_id_t    id = l26_ip_mc_vcap_id(src, ipv6);
    vtss_port_no_t    port_no;
    int               i;

    /* Initialize IS1 entry data */
    vtss_vcap_is1_init(&data, &entry);
    
    /* First Lookup */
    data.u.is1.lookup = 0;
    
    /* Action data */
    action->fid_sel = VTSS_FID_SEL_DMAC;
    action->fid_val = src->fid;
    
    /* Key data */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        key->port_list[port_no] = TRUE;
    }
    
    key->tag.vid.type = VTSS_VCAP_VR_TYPE_VALUE_MASK;
    key->tag.vid.vr.v.value = src->vid;
    key->tag.vid.vr.v.mask = 0xffff;
    
    if (ipv6) {
        key->type = VTSS_IS1_TYPE_IPV6;
        for (i = 12; i < 16; i++) {
            key->frame.ipv6.sip.value[i] = src->sip.ipv6.addr[i];
            key->frame.ipv6.sip.mask[i] = 0xff;
        }
        key->frame.ipv6.ip_mc = VTSS_VCAP_BIT_1;
    } else {
        key->type = VTSS_IS1_TYPE_IPV4;
        key->frame.ipv4.sip.value = src->sip.ipv4;
        key->frame.ipv4.sip.mask = 0xffffffff;
        key->frame.ipv4.ip_mc = VTSS_VCAP_BIT_1;
    }
    
    /* Add IS1 entry */
    VTSS_RC(vtss_vcap_add(vtss_state, obj, VTSS_IS1_USER_SSM, id, VTSS_VCAP_ID_LAST, &data, 0));
    
    return VTSS_RC_OK;
}

/* Update IP multicast entry */
static vtss_rc l26_ip_mc_update(vtss_state_t *vtss_state,
                                vtss_ipmc_data_t *ipmc, vtss_ipmc_cmd_t cmd)
{
    vtss_res_t             res;
    vtss_ipmc_obj_t        *ipmc_obj = &vtss_state->l2.ipmc.obj;
    vtss_vcap_obj_t        *is1_obj = &vtss_state->vcap.is1.obj;
    vtss_ipmc_src_t        *src, *src_asm = NULL;
    vtss_ipmc_dst_t        *dst, *dst_asm, *dst_asm_first = NULL, *dst_asm_last = NULL;
    vtss_vcap_id_t         id;
    u32                    mask, dip, dip_next, mac_count;
    u32                    port_count = vtss_state->port_count;
    BOOL                   src_found = 0, fid_add, dmac_found = 0;
    vtss_port_no_t         port_no;
    vtss_mac_table_entry_t mac_entry;
    vtss_vid_mac_t         *vid_mac = &mac_entry.vid_mac;
    
    VTSS_I("%s IPv%u %sSM, vid:%u, fid:%u, sip:0x%08x, dip:0x%08x",
           cmd == VTSS_IPMC_CMD_CHECK ? "CHK" :
           cmd == VTSS_IPMC_CMD_ADD ? "ADD" :
           cmd == VTSS_IPMC_CMD_DEL ? "DEL" : "?",
           ipmc->ipv6 ? 6 : 4, 
           ipmc->src.ssm ? "S" : "A", 
           ipmc->src.vid, 
           ipmc->src.fid,
           vtss_cmn_ip2u32(&ipmc->src.sip, ipmc->ipv6), 
           vtss_cmn_ip2u32(&ipmc->dst.dip, ipmc->ipv6));
        
    /* VCAP ID */
    id = l26_ip_mc_vcap_id(&ipmc->src, ipmc->ipv6);

    /* MAC address */
    VTSS_MEMSET(&mac_entry, 0, sizeof(mac_entry));
    mac_entry.locked = 1;
    l26_ip_mc_mac_get(vid_mac, &ipmc->dst, ipmc->ipv6);
    
    fid_add = (ipmc->src.ssm && ipmc->src.fid == 0 ? 1 : 0);
    if (cmd == VTSS_IPMC_CMD_CHECK) {
        /* Check that resources are available */

        /* Check source resources, if new SSM */
        if (fid_add) {
            /* Check IS1 resources */
            vtss_cmn_res_init(&res);
            res.is1.add = 1;
            VTSS_RC(vtss_cmn_res_check(vtss_state, &res));
            
            /* Check FID allocation */
            VTSS_RC(l26_ip_mc_fid_alloc(vtss_state, &ipmc->src.fid, ipmc->ipv6, 0));
        }

        /* Check MAC table resources */
        if (!ipmc->dst_add)
            return VTSS_RC_OK;

        mac_count = 1; /* One entry must always be added for ASM/SSM */
        for (src = ipmc_obj->src_used[ipmc->ipv6]; src != NULL; src = src->next) {
            if (ipmc->src.vid != src->data.vid)
                continue;
            
            if (ipmc->src.ssm) {
                /* Adding SSM destination */
                if (!src->data.ssm && fid_add) {
                    /* Up to one entry for each ASM DIP */
                    for (dst = src->dest; dst != NULL; dst = dst->next) {
                        mac_count++;
                    }
                }
                break;
            } 
            
            /* Adding ASM destination */
            if (src->data.ssm && 
                (src->next == NULL || src->next->data.fid != src->data.fid)) {
                /* Up to one entry for each SSM FID */
                mac_count++;
            }
        }
        VTSS_I("new dest needs %u, current: %u, max: %u",
               mac_count, vtss_state->l2.mac_table_count, vtss_state->l2.mac_table_max);
        
        if ((vtss_state->l2.mac_table_count + mac_count) > vtss_state->l2.mac_table_max) {
            VTSS_I("no more MAC entries");
            return VTSS_RC_ERROR;
        }
        return VTSS_RC_OK;
    } 

    if (cmd == VTSS_IPMC_CMD_ADD && fid_add) {
        /* Allocate FID  */
        VTSS_RC(l26_ip_mc_fid_alloc(vtss_state, &ipmc->src.fid, ipmc->ipv6, 1));

        /* Add IS1 entry */
        VTSS_RC(l26_ip_mc_is1_add(vtss_state, &ipmc->src, ipmc->ipv6));
    }

    /* We come to this point with VTSS_IPMC_CMD_ADD/DEL to add/delete resources */
    
    /* Add/delete MAC address entries */
    mask = (ipmc->ipv6 ? 0xffffffff : 0x007fffff);
    dip = (vtss_cmn_ip2u32(&ipmc->dst.dip, ipmc->ipv6) & mask);
    for (src = ipmc_obj->src_used[ipmc->ipv6]; src != NULL; src = src->next) {
        /* Skip sources not matching the VID */
        if (ipmc->src.vid != src->data.vid)
            continue;

        if (src->data.ssm == ipmc->src.ssm) {
            /* If adding/deleting SSM entry the FID must match */
            if (ipmc->src.ssm && src->data.fid != ipmc->src.fid)
                continue;
            src_found = 1;
        }

        /* Look for all DIPs mapping to the same DMAC */
        for (dst = src->dest; dst != NULL; dst = dst->next) {
            if ((vtss_cmn_ip2u32(&dst->data.dip, ipmc->ipv6) & mask) != dip)
                continue;
            dmac_found = 1;
            for (port_no = VTSS_PORT_NO_START; port_no < port_count; port_no++) {
                if (VTSS_PORT_BF_GET(dst->data.member, port_no)) {
                    mac_entry.destination[port_no] = 1;
                }
            }
            if (src->data.ssm) {
                /* SSM entry, clear ASM add flag if DIP matches */
                for (dst_asm = dst_asm_first; dst_asm != NULL; dst_asm = dst_asm->next) {
                    if (dst_asm->add && 
                        VTSS_MEMCMP(&dst->data.dip, &dst_asm->data.dip, sizeof(vtss_ip_addr_internal_t)) == 0)
                        dst_asm->add = 0;
                    if (dst_asm == dst_asm_last)
                        break;
                }
            } else {
                /* ASM entry, store pointers and set add flag */
                if (dst_asm_first == NULL)
                    dst_asm_first = dst;
                dst_asm_last = dst;
                dst->add = 1;
            }
        }

        /* Continue if the next source is using the same FID */
        if (src->next != NULL && src->next->data.fid == src->data.fid)
            continue;
        
        VTSS_I("%sSM, fid:%u, sip:0x%08x, dmac_found:%u",
               src->data.ssm ? "S" : "A", 
               src->data.fid, 
               vtss_cmn_ip2u32(&src->data.sip, ipmc->ipv6), 
               dmac_found);
        
        if (src->data.ssm) {
            /* For SSM entry, merge with the ASM destination set */
            for (dst = dst_asm_first; dst != NULL; dst = dst->next) {
                if (dst->add) {
                    dmac_found = 1;
                    for (port_no = VTSS_PORT_NO_START; port_no < port_count; port_no++) {
                        if (VTSS_PORT_BF_GET(dst->data.member, port_no)) {
                            mac_entry.destination[port_no] = 1;
                        }
                    }
                }
                dst->add = 1;
                if (dst == dst_asm_last)
                    break;
            }
        } else {
            /* Store ASM information */
            src_asm = src;
        }
        
        /* Add/delete MAC address entry (ignoring return codes) */
        vid_mac->vid = src->data.fid;
        if (dmac_found) {
            (void)vtss_mac_add(vtss_state, VTSS_MAC_USER_SSM, &mac_entry);
        } else {
            (void)vtss_mac_del(vtss_state, VTSS_MAC_USER_SSM, vid_mac);
        }
        
        /* Clear destination set */
        VTSS_MEMSET(mac_entry.destination, 0, port_count);
        dmac_found = 0;
    }
    
    /* No further processing if the source was found */
    if (src_found)
        return VTSS_RC_OK;

    /* If the source is deleted, the MAC entry must be deleted */
    vid_mac->vid = ipmc->src.fid;
    (void)vtss_mac_del(vtss_state, VTSS_MAC_USER_SSM, vid_mac);

    /* No further processing for ASM sources */
    if (!ipmc->src.ssm)
        return VTSS_RC_OK;

    /* Free FID */
    VTSS_RC(l26_ip_mc_fid_free(vtss_state, ipmc->src.fid, ipmc->ipv6));
        
    /* Delete IS1 entry */
    VTSS_RC(vtss_vcap_del(vtss_state, is1_obj, VTSS_IS1_USER_SSM, id));

    /* If SSM source is deleted, all ASM destinations must be deleted for SSM FID */
    if (src_asm != NULL && (dst = src_asm->dest) != NULL) {
        dip = (vtss_cmn_ip2u32(&dst->data.dip, ipmc->ipv6) & mask);
        while (dst != NULL) {
            /* Delete MAC address entry */
            l26_ip_mc_mac_get(vid_mac, &dst->data, ipmc->ipv6);
            (void)vtss_mac_del(vtss_state, VTSS_MAC_USER_SSM, vid_mac);

            /* Find next DIP mapping to another DMAC */
            for (dst = dst->next; dst != NULL; dst = dst->next) {
                dip_next = (vtss_cmn_ip2u32(&dst->data.dip, ipmc->ipv6) & mask);
                if (dip_next != dip) {
                    dip = dip_next;
                    break;
                }
            }
        }
    }
    return VTSS_RC_OK;
}

/* Update MAC address entries for source to a new FID */
static vtss_rc l26_ip_mc_mac_update(vtss_state_t *vtss_state,
                                    vtss_ipmc_src_t *src, vtss_vid_t old_fid, 
                                    vtss_vid_t new_fid, BOOL ipv6)
{
    vtss_mac_table_entry_t mac_entry;
    vtss_vid_mac_t         *vid_mac = &mac_entry.vid_mac;
    vtss_ipmc_dst_t        *dst;
    u32                    pgid;

    /* Update MAC address entries for all destinations */
    for (dst = src->dest; dst != NULL; dst = dst->next) {
        l26_ip_mc_mac_get(vid_mac, &dst->data, ipv6);
        vid_mac->vid = old_fid;
        if (vtss_mac_get(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK &&
            vtss_mac_del(vtss_state, VTSS_MAC_USER_SSM, vid_mac) == VTSS_RC_OK) {
            vid_mac->vid = new_fid;
            VTSS_RC(vtss_mac_add(vtss_state, VTSS_MAC_USER_SSM, &mac_entry));
        }
    }
    
    return VTSS_RC_OK;
}

/* Reallocate FID and update IP multicast entries accordingly */
static vtss_rc l26_ip_mc_fid_adjust(vtss_state_t *vtss_state, vtss_vid_t fid)
{
    vtss_ipmc_obj_t *obj = &vtss_state->l2.ipmc.obj;
    vtss_ipmc_src_t *src;
    vtss_vid_t      ipv4_fid = 0, ipv6_fid = 0, new_fid, asm_vid;
    int             add, ipv6;
    u8              ipmc_used = vtss_state->l2.vlan_table[fid].ipmc_used;
    
    /* Reallocate FIDs in two steps:
       1: Try to allocate IPv4/IPv6 FID
       2: Allocate and free IPv4/IPv6 FID */
    for (add = 0; add < 2; add++) {
        for (ipv6 = 0; ipv6 < 2; ipv6++) {
            if (ipmc_used & (ipv6 ? IPMC_USED_IPV6 : IPMC_USED_IPV4)) {
                /* Allocate new FID */
                VTSS_RC(l26_ip_mc_fid_alloc(vtss_state, ipv6 ? &ipv6_fid : &ipv4_fid, ipv6, add));
                
                if (add) {
                    /* Free old FID */
                    VTSS_RC(l26_ip_mc_fid_free(vtss_state, fid, ipv6));
                }
            }
        }
    }
    
    /* Update IS1 and MAC table entries */
    for (ipv6 = 0; ipv6 < 2; ipv6++) {
        if ((new_fid = (ipv6 ? ipv6_fid : ipv4_fid)) == 0)
            continue;

        /* SSM entries */
        asm_vid = VTSS_VID_NULL;
        for (src = obj->src_used[ipv6]; src != NULL; src = src->next) {
            if (src->data.ssm && src->data.fid == fid) {
                /* Update FID and add IS1 entry for source */
                asm_vid = src->data.vid;
                src->data.fid = new_fid;
                VTSS_RC(l26_ip_mc_is1_add(vtss_state, &src->data, ipv6));
                
                /* Update MAC address entries for all destinations */
                VTSS_RC(l26_ip_mc_mac_update(vtss_state, src, fid, new_fid, ipv6));
            }
        }
        

        /* ASM entries */
        if (asm_vid == VTSS_VID_NULL)
            continue;
        for (src = obj->src_used[ipv6]; src != NULL; src = src->next) {
            if (!src->data.ssm && src->data.vid == asm_vid) {
                /* Update MAC address entries for all destinations */
                VTSS_RC(l26_ip_mc_mac_update(vtss_state, src, fid, new_fid, ipv6));
                break;
            }
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_flood_conf_set(vtss_state_t *vtss_state)
{
    /* Unicast flood mask */
    VTSS_RC(l26_pgid_update(vtss_state, PGID_UC, vtss_state->l2.uc_flood));
    
    /* Multicast flood mask */
    VTSS_RC(l26_pgid_update(vtss_state, PGID_MC, vtss_state->l2.mc_flood));
    
    /* IPv4 flood mask */
    VTSS_RC(l26_pgid_update(vtss_state, PGID_MCIPV4, vtss_state->l2.ipv4_mc_flood));

    /* IPv6 flood mask */
    VTSS_RC(l26_pgid_update(vtss_state, PGID_MCIPV6, vtss_state->l2.ipv6_mc_flood));

    /* IPv6 flood scope */
    L26_WRM(VTSS_ANA_ANA_FLOODING_IPMC, 
            VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL(vtss_state->l2.ipv6_mc_scope ? PGID_MCIPV6 : PGID_MC),
            VTSS_M_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL);
    
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2
 * ================================================================= */

/* Set learn mask */
static vtss_rc l26_learn_state_set(vtss_state_t *vtss_state,
                                   const BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_port_no_t port_no;
    
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        L26_WRM_CTL(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT(port_no)), 
                    member[port_no], VTSS_F_ANA_PORT_PORT_CFG_LEARN_ENA);
    }
    return VTSS_RC_OK;
}

/* Wait until the MAC operation is finsished */
static vtss_rc l26_mac_table_idle(vtss_state_t *vtss_state)
{
    u32 cmd;    

    do {
        L26_RD(VTSS_ANA_ANA_TABLES_MACACCESS, &cmd);        
    } while (VTSS_X_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(cmd) != MAC_CMD_IDLE);

    return VTSS_RC_OK;
}

/* Add a given MAC entry */
static vtss_rc l26_mac_table_add(vtss_state_t *vtss_state,
                                 const vtss_mac_table_entry_t *const entry, u32 pgid)
{
    u32 mach, macl, mask, idx, aged = 0, fwd_kill = 0, ipv6_mask = 0, type;
    BOOL copy_to_cpu = entry->copy_to_cpu_smac;
    
    vtss_mach_macl_get(&entry->vid_mac, &mach, &macl);
    VTSS_D("address 0x%08x%08x", mach, macl);
    
    if (pgid == VTSS_PGID_NONE) {
        /* IPv4/IPv6 multicast entry */
        mask = vtss_l26_port_mask(vtss_state, vtss_state->l2.pgid_table[pgid].member); 
        if (entry->vid_mac.mac.addr[0] == 0x01) {
            /* IPv4 multicast entry */
            type = MAC_TYPE_IPV4_MC;
            /* Encode port mask directly */
            macl = ((macl & 0x00FFFFFF) | ((mask<<24) & 0xFF000000));
            mach = ((mach & 0xFFFF0000) | ((mask>>8) & 0x0000FFFF));
            idx = ((mask>>24) & 0x3); /* Ports 24-25 */

        } else {
            /* IPv6 multicast entry */
            type = MAC_TYPE_IPV6_MC;
            /* Encode port mask directly */
            mach = ((mach & 0xFFFF0000) | (mask & 0x0000FFFF)); /* ports 0-15  */
            idx = ((mask>>16) & 0x3F);                          /* ports 16-21 */
            ipv6_mask = ((mask>>22) & 0x7);                     /* ports 22-24 */
            aged = ((mask>>25) & 1);                            /* port 25     */

        }
    } else {
        /* Not IP multicast entry */
        /* Set FWD_KILL to make the switch discard frames in SMAC lookup */
        fwd_kill = (copy_to_cpu || pgid != vtss_state->l2.pgid_drop ? 0 : 1);
        idx = l26_chip_pgid(vtss_state, pgid);
        type = (entry->locked ? MAC_TYPE_LOCKED : MAC_TYPE_NORMAL);
        aged = 0;
    }

    /* Insert/learn new entry into the MAC table  */
    L26_WR(VTSS_ANA_ANA_TABLES_MACHDATA, mach);
    L26_WR(VTSS_ANA_ANA_TABLES_MACLDATA, macl);    

    L26_WR(VTSS_ANA_ANA_TABLES_MACACCESS, 
           VTSS_F_ANA_ANA_TABLES_MACACCESS_IP6_MASK(ipv6_mask)                     |
           (copy_to_cpu        ? VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_CPU_COPY : 0) |
           (fwd_kill           ? VTSS_F_ANA_ANA_TABLES_MACACCESS_SRC_KILL     : 0) |
           (aged               ? VTSS_F_ANA_ANA_TABLES_MACACCESS_AGED_FLAG    : 0) |
           VTSS_F_ANA_ANA_TABLES_MACACCESS_VALID                                   |
           VTSS_F_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE(type)                        |
           VTSS_F_ANA_ANA_TABLES_MACACCESS_DEST_IDX(idx)                           |
           VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MAC_CMD_LEARN));

    /* Wait until MAC operation is finished */
    return l26_mac_table_idle(vtss_state);
}

static u32 l26_mac_type(const vtss_vid_mac_t *vid_mac)
{
    return (VTSS_MAC_IPV4_MC(vid_mac->mac.addr) ? MAC_TYPE_IPV4_MC :
            VTSS_MAC_IPV6_MC(vid_mac->mac.addr) ? MAC_TYPE_IPV6_MC : MAC_TYPE_NORMAL);
}

static vtss_rc l26_mac_table_cmd(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac, u32 type, u32 cmd)
{
    u32 mach, macl;

    vtss_mach_macl_get(vid_mac, &mach, &macl);
    VTSS_D("cmd: %u, address 0x%08x%08x", cmd, mach, macl);

    /* Run command for MAC entry */
    L26_WR(VTSS_ANA_ANA_TABLES_MACHDATA, mach);
    L26_WR(VTSS_ANA_ANA_TABLES_MACLDATA, macl);    
    L26_WR(VTSS_ANA_ANA_TABLES_MACACCESS, 
           VTSS_F_ANA_ANA_TABLES_MACACCESS_VALID |
           VTSS_F_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE(type) |
           VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(cmd));

    /* Wait until MAC operation is finished */
    return l26_mac_table_idle(vtss_state);
}

/* Delete/unlearn a given MAC entry */
static vtss_rc l26_mac_table_del(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac)
{
    u32 type = l26_mac_type(vid_mac);

    VTSS_RC(l26_mac_table_cmd(vtss_state, vid_mac, type, MAC_CMD_FORGET));
    if (type != MAC_TYPE_NORMAL) {
        /* IPMC entries may be encoded as NORMAL */
        VTSS_RC(l26_mac_table_cmd(vtss_state, vid_mac, MAC_TYPE_NORMAL, MAC_CMD_FORGET));
    }
    return VTSS_RC_OK;
}

/* Analyze the result in the MAC table */
static vtss_rc l26_mac_table_result(vtss_state_t *vtss_state,
                                    vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    u32               value, mask, mach, macl, idx, type, aged;
    vtss_port_no_t    port_no;
    vtss_pgid_entry_t *pgid_entry;
    u8                *mac = &entry->vid_mac.mac.addr[0];
    
    L26_RD(VTSS_ANA_ANA_TABLES_MACACCESS, &value);        

    /* Check if entry is valid */
    if (!(value & VTSS_F_ANA_ANA_TABLES_MACACCESS_VALID)) {
        VTSS_D("not valid");
        return VTSS_RC_ERROR;
    }

    type               = VTSS_X_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE(value);
    idx                = VTSS_X_ANA_ANA_TABLES_MACACCESS_DEST_IDX(value); 
    aged = VTSS_BOOL(value & VTSS_F_ANA_ANA_TABLES_MACACCESS_AGED_FLAG);
    entry->aged        = aged;
    entry->copy_to_cpu = 0;
    entry->copy_to_cpu_smac = VTSS_BOOL(value & VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_CPU_COPY);
    entry->locked      = (type == MAC_TYPE_NORMAL ? 0 : 1);

    L26_RD(VTSS_ANA_ANA_TABLES_MACHDATA, &mach);
    L26_RD(VTSS_ANA_ANA_TABLES_MACLDATA, &macl);

    if (type == MAC_TYPE_IPV4_MC || type == MAC_TYPE_IPV6_MC) {
        /* IPv4/IPv6 multicast address */
        *pgid = VTSS_PGID_NONE;

        /* Read encoded port mask and update address registers */
        if (type == MAC_TYPE_IPV6_MC) {
            /* IPv6 entry  */
            /* Portmask:  25               24-22                21-16         15-0    */
            mask = (aged<<25  | (((value>>16) & 0x7)<<22) | (idx<<16) | (mach & 0xffff));
            mach = ((mach & 0xffff0000) | 0x00003333);
        } else {
            /* IPv4 entry */
            /* Portmask:25-24        23-0  */
            mask = ((idx<<24) | ((mach<<8) & 0xFFFF00) | ((macl>>24) & 0xff));
            mach = ((mach & 0xffff0000) | 0x00000100);
            macl = ((macl & 0x00ffffff) | 0x5e000000);
        }    

        /* Convert port mask */
        pgid_entry = &vtss_state->l2.pgid_table[*pgid];
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++)
            pgid_entry->member[port_no] = VTSS_BOOL(mask & (1 << VTSS_CHIP_PORT(port_no)));
    } else {
        *pgid = l26_vtss_pgid(vtss_state, idx);
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

static vtss_rc l26_mac_table_get(vtss_state_t *vtss_state,
                                 vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    vtss_rc rc;
    u32     type = l26_mac_type(&entry->vid_mac);

    VTSS_RC(l26_mac_table_cmd(vtss_state, &entry->vid_mac, type, MAC_CMD_READ));
    rc = l26_mac_table_result(vtss_state, entry, pgid);
    if (type != MAC_TYPE_NORMAL && rc != VTSS_RC_OK) {
        /* IPMC entries may be encoded as NORMAL */
        VTSS_RC(l26_mac_table_cmd(vtss_state, &entry->vid_mac, MAC_TYPE_NORMAL, MAC_CMD_READ));
        rc = l26_mac_table_result(vtss_state, entry, pgid);
    }
    return rc;
}

static vtss_rc l26_mac_table_get_next(vtss_state_t *vtss_state,
                                      vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    VTSS_RC(l26_mac_table_cmd(vtss_state, &entry->vid_mac, MAC_TYPE_NORMAL, MAC_CMD_GET_NEXT));
    return l26_mac_table_result(vtss_state, entry, pgid);
}

/* Normal auto aging in seconds */
static vtss_rc l26_mac_table_age_time_set(vtss_state_t *vtss_state)
{
    u32 time;
    
    /* Scan two times per age time */
    time = (vtss_state->l2.mac_age_time/2);
    if (time > 0xfffff)
        time = 0xfffff;
    L26_WR(VTSS_ANA_ANA_AUTOAGE, VTSS_F_ANA_ANA_AUTOAGE_AGE_PERIOD(time));
    return VTSS_RC_OK;
}

/* Selective aging based on port(s) and/or VLAN */
static vtss_rc l26_mac_table_age(vtss_state_t     *vtss_state,
                                 BOOL             pgid_age, 
                                 u32              pgid,
                                 BOOL             vid_age,
                                 const vtss_vid_t vid)
{
    /* Selective aging */
    L26_WR(VTSS_ANA_ANA_ANAGEFIL, 
           (pgid_age ? VTSS_F_ANA_ANA_ANAGEFIL_PID_EN : 0) |
           (vid_age ? VTSS_F_ANA_ANA_ANAGEFIL_VID_EN  : 0) |
           VTSS_F_ANA_ANA_ANAGEFIL_PID_VAL(l26_chip_pgid(vtss_state, pgid)) |
           VTSS_F_ANA_ANA_ANAGEFIL_VID_VAL(vid));

    /* Do the aging */
    L26_WR(VTSS_ANA_ANA_TABLES_MACACCESS, 
           VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MAC_CMD_TABLE_AGE));

    VTSS_RC(l26_mac_table_idle(vtss_state));

    /* Clear age filter again to avoid affecting automatic ageing */
    L26_WR(VTSS_ANA_ANA_ANAGEFIL, 0);

    return VTSS_RC_OK;
}

static vtss_rc l26_mac_table_status_get(vtss_state_t *vtss_state, vtss_mac_table_status_t *status) 
{
    u32 value;

    /* Read and clear sticky register */
    L26_RD(VTSS_ANA_ANA_ANEVENTS, &value);
    L26_WR(VTSS_ANA_ANA_ANEVENTS, value & 
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

static vtss_rc l26_learn_mode_set(vtss_state_t *vtss_state,
                                  u32 port, vtss_learn_mode_t *mode)
{
    L26_WRM(VTSS_ANA_PORT_PORT_CFG(port), 
            (mode->discard   ? VTSS_F_ANA_PORT_PORT_CFG_LEARNDROP : 0) |
            (mode->automatic ? VTSS_F_ANA_PORT_PORT_CFG_LEARNAUTO : VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_CPU) |
            (mode->cpu       ? VTSS_F_ANA_PORT_PORT_CFG_LEARNCPU  : 0) |
            VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_DROP,
            (VTSS_F_ANA_PORT_PORT_CFG_LEARNDROP            |
             VTSS_F_ANA_PORT_PORT_CFG_LEARNAUTO            |
             VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_CPU  |
             VTSS_F_ANA_PORT_PORT_CFG_LEARNCPU             |
             VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_DROP));

    return VTSS_RC_OK;
}

/* Learn mode: 'Learn frames dropped' / 'Autolearning' / 'Copy learn frame to CPU' */
static vtss_rc l26_learn_port_mode_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_learn_mode_t *mode = &vtss_state->l2.learn_mode[port_no];
    u32               value, port = VTSS_CHIP_PORT(port_no);

    VTSS_RC(l26_learn_mode_set(vtss_state, port, mode));
       
    if (!mode->automatic) {
        /* Flush entries previously learned on port to avoid continuous refreshing */
        L26_RD(VTSS_ANA_PORT_PORT_CFG(port), &value);
        L26_WRM_CLR(VTSS_ANA_PORT_PORT_CFG(port), VTSS_F_ANA_PORT_PORT_CFG_LEARN_ENA);
        VTSS_RC(l26_mac_table_age(vtss_state, 1, port_no, 0, 0));
        VTSS_RC(l26_mac_table_age(vtss_state, 1, port_no, 0, 0));
        L26_WR(VTSS_ANA_PORT_PORT_CFG(port), value);
    }
    return VTSS_RC_OK;
}


/* ================================================================= *
 *  Mirror
 * ================================================================= */

/* Mirror port, where a selected traffic is copied to */
static vtss_rc l26_mirror_port_set(vtss_state_t *vtss_state)
{
    BOOL                   member[VTSS_PORT_ARRAY_SIZE];
    vtss_port_no_t         port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        member[port_no] = (port_no == vtss_state->l2.mirror_conf.port_no);
    }
    L26_WR(VTSS_ANA_ANA_MIRRORPORTS, vtss_l26_port_mask(vtss_state, member));    

    /* Update VLAN port configuration for all ports */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(vtss_cmn_vlan_port_conf_set(vtss_state, port_no));
    }

    /* Update all VLANs */
    return vtss_cmn_vlan_update_all(vtss_state);
}

/* Ingress ports subjects for mirroring */
static vtss_rc l26_mirror_ingress_set(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    BOOL           enabled;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        enabled = vtss_state->l2.mirror_ingress[port_no];
        L26_WRM(VTSS_ANA_PORT_PORT_CFG(VTSS_CHIP_PORT(port_no)), 
                (enabled ? VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA : 0), VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA);
    }
    return VTSS_RC_OK;
}

/* Egress ports subjects for mirroring */
static vtss_rc l26_mirror_egress_set(vtss_state_t *vtss_state)
{
    L26_WR(VTSS_ANA_ANA_EMIRRORPORTS, vtss_l26_port_mask(vtss_state, vtss_state->l2.mirror_egress));
    return VTSS_RC_OK;
}

/* CPU Ingress ports subjects for mirroring */
static vtss_rc l26_mirror_cpu_ingress_set(vtss_state_t *vtss_state)
{
    BOOL           enabled = vtss_state->l2.mirror_cpu_ingress;

    L26_WRM(VTSS_ANA_PORT_PORT_CFG(26), 
            (enabled ? VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA : 0), VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA); // CPU port is port 26, 6See Table 98 in data sheet
    return VTSS_RC_OK;
}

/* CPU Egress ports subjects for mirroring */
static vtss_rc l26_mirror_cpu_egress_set(vtss_state_t *vtss_state)
{
    BOOL           enabled = vtss_state->l2.mirror_cpu_egress;

    L26_WRM(VTSS_ANA_ANA_AGENCTRL, enabled ? VTSS_F_ANA_ANA_AGENCTRL_MIRROR_CPU : 0 , VTSS_F_ANA_ANA_AGENCTRL_MIRROR_CPU);
    return VTSS_RC_OK;
}

static vtss_rc l26_vlan_conf_apply(vtss_state_t *vtss_state, BOOL ports)
{
    u32            etype = vtss_state->l2.vlan_conf.s_etype;
    vtss_port_no_t port_no;

    /* BZ 4513: Type 0x8100 can not be used so we use 0x88a8 */
    if (etype == VTSS_ETYPE_TAG_C)
        etype = VTSS_ETYPE_TAG_S;

    L26_WR(VTSS_SYS_SYSTEM_VLAN_ETYPE_CFG, etype);
    
    /* Update ports */
    for (port_no = VTSS_PORT_NO_START; ports && port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(vtss_cmn_vlan_port_conf_set(vtss_state, port_no));
    }

    return VTSS_RC_OK;
}

static vtss_rc l26_vlan_conf_set(vtss_state_t *vtss_state)
{
    return l26_vlan_conf_apply(vtss_state, 1);
}

static vtss_rc l26_vlan_port_conf_apply(vtss_state_t *vtss_state, 
                                        u32                   port, 
                                        vtss_vlan_port_conf_t *conf)
{
    u32                   value, tpid = TAG_TPID_CFG_0x8100;
    u32                   etype = vtss_state->l2.vlan_conf.s_etype;
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
    L26_WRM(VTSS_ANA_PORT_VLAN_CFG(port), value,
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
    L26_WR(VTSS_ANA_PORT_DROP_CFG(port), value);

    /* Ingress filtering */
    L26_WRM(VTSS_ANA_ANA_VLANMASK, (conf->ingress_filter ? 1 : 0) << port, 1 << port);

    /* Rewriter VLAN tag configuration */
    value = (VTSS_F_REW_PORT_TAG_CFG_TAG_TPID_CFG(tpid) |
             VTSS_F_REW_PORT_TAG_CFG_TAG_VID_CFG |
             VTSS_F_REW_PORT_TAG_CFG_TAG_CFG(
                 conf->untagged_vid == VTSS_VID_ALL ? TAG_CFG_DISABLE :
                 conf->untagged_vid == VTSS_VID_NULL ? TAG_CFG_ALL_NNUL : TAG_CFG_ALL_NPV_NNUL));
    L26_WRM(VTSS_REW_PORT_TAG_CFG(port), value, 
            VTSS_M_REW_PORT_TAG_CFG_TAG_TPID_CFG | 
            VTSS_F_REW_PORT_TAG_CFG_TAG_VID_CFG |
            VTSS_M_REW_PORT_TAG_CFG_TAG_CFG);
    L26_WRM(VTSS_REW_PORT_PORT_VLAN_CFG(port), 
            VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_TPID(etype) |
            VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_VID(conf->untagged_vid),
            VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_TPID |
            VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_VID);
    
    return VTSS_RC_OK;
}

static vtss_rc l26_vlan_port_conf_update(vtss_state_t *vtss_state,
                                         vtss_port_no_t port_no, vtss_vlan_port_conf_t *conf)
{
    /* Update maximum tags allowed */
    VTSS_RC(vtss_l26_port_max_tags_set(vtss_state, port_no));

    return l26_vlan_port_conf_apply(vtss_state, VTSS_CHIP_PORT(port_no), conf);
}

static vtss_rc l26_vlan_table_idle(vtss_state_t *vtss_state)
{
    u32 cmd;
    
    do {
        L26_RD(VTSS_ANA_ANA_TABLES_VLANACCESS, &cmd);
    } while (VTSS_X_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(cmd) != VLAN_CMD_IDLE);

    return VTSS_RC_OK;
}

static vtss_rc l26_vlan_mask_update(vtss_state_t *vtss_state,
                                    vtss_vid_t vid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    vtss_vlan_entry_t *e = &vtss_state->l2.vlan_table[vid];
    u32               value;

    /* Index and properties */
    value = VTSS_F_ANA_ANA_TABLES_VLANTIDX_V_INDEX(vid);
    if (e->flags & VLAN_FLAGS_ISOLATED)
        value |= VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_PRIV_VLAN;
    if (!(e->flags & VLAN_FLAGS_LEARN))
        value |= VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_LEARN_DISABLED;
    if (e->flags & VLAN_FLAGS_MIRROR)
        value |= VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_MIRROR;
    if (e->flags & VLAN_FLAGS_FILTER)
        value |= VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_SRC_CHK;
    L26_WR(VTSS_ANA_ANA_TABLES_VLANTIDX, value);

    /* VLAN mask */
    value = VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_PORT_MASK(vtss_l26_port_mask(vtss_state, member));
    value |= VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_CMD_WRITE);
    L26_WR(VTSS_ANA_ANA_TABLES_VLANACCESS, value);

    /* Adjust IP multicast entries if neccessary */
    if ((e->flags & VLAN_FLAGS_ENABLED) && e->ipmc_used) {
        VTSS_RC(l26_ip_mc_fid_adjust(vtss_state, vid));
    }

    return l26_vlan_table_idle(vtss_state);
}

/* ================================================================= *
 *  VCL
 * ================================================================= */

vtss_rc vtss_l26_vcl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    BOOL dmac_dip = vtss_state->l2.vcl_port_conf[port_no].dmac_dip;
    u32  mask = VTSS_F_ANA_PORT_VCAP_CFG_S1_DMAC_DIP_ENA(1);
    u32  port = VTSS_CHIP_PORT(port_no);
    
    /* Enable/disable DMAC/DIP match in first IS1 lookup */
    L26_WRM(VTSS_ANA_PORT_VCAP_CFG(port), dmac_dip ? mask : 0, mask);

    return VTSS_RC_OK;
}

/* ================================================================= *
 *  PVLAN / Isolated ports
 * ================================================================= */

static vtss_rc l26_isolated_port_members_set(vtss_state_t *vtss_state)
{
    u32 mask = vtss_l26_port_mask(vtss_state, vtss_state->l2.isolated_port);

    /* Isolated ports: cleared (add CPU as not isolated) */
    mask = ((~mask) & VTSS_CHIP_PORT_MASK) | VTSS_BIT(VTSS_CHIP_PORT_CPU);
    L26_WR(VTSS_ANA_ANA_ISOLATED_PORTS, mask);

    return VTSS_RC_OK;
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

/**
 * l26_sflow_hw_rate()
 */
static u32 l26_sflow_hw_rate(const u32 desired_sw_rate, u32 *const realizable_sw_rate)
{
    u32 hw_rate         = desired_sw_rate ? VTSS_ROUNDING_DIVISION(LU26_SFLOW_MAX_SAMPLE_RATE + 1, desired_sw_rate) : 0;
    hw_rate             = hw_rate > LU26_SFLOW_MIN_SAMPLE_RATE ? hw_rate - 1 : hw_rate;
    *realizable_sw_rate = VTSS_ROUNDING_DIVISION(LU26_SFLOW_MAX_SAMPLE_RATE + 1, hw_rate + 1);
    return hw_rate;
}

/**
 * l26_sflow_sampling_rate_convert()
 */
static vtss_rc l26_sflow_sampling_rate_convert(struct vtss_state_s *const state, const BOOL power2, const u32 rate_in, u32 *const rate_out)
{
    u32 modified_rate_in;
    // Could happen that two threads call this function simultaneously at boot, but we take the risk.
    // Once sflow_max_power_of_two has been computed, it's no longer a problem with simultaneous access.
    u32 sflow_max_power_of_two = state->l2.sflow_max_power_of_two;

    if (sflow_max_power_of_two == 0) {
        sflow_max_power_of_two = next_power_of_two(LU26_SFLOW_MAX_SAMPLE_RATE);
        if ((LU26_SFLOW_MAX_SAMPLE_RATE & sflow_max_power_of_two) == 0) {
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

    (void)l26_sflow_hw_rate(modified_rate_in, rate_out);
    return VTSS_RC_OK;
}

/**
 * l26_sflow_port_conf_set()
 */
static vtss_rc l26_sflow_port_conf_set(vtss_state_t *vtss_state,
                                       const vtss_port_no_t port_no, const vtss_sflow_port_conf_t *const new_conf)
{
    u32 hw_rate, value;
    vtss_sflow_port_conf_t *cur_conf = &vtss_state->l2.sflow_conf[port_no];

    *cur_conf = *new_conf;
    hw_rate = l26_sflow_hw_rate(new_conf->sampling_rate, &cur_conf->sampling_rate);

    value  = VTSS_F_ANA_ANA_SFLOW_CFG_SF_RATE(hw_rate);
    value |= new_conf->sampling_rate != 0 && (new_conf->type == VTSS_SFLOW_TYPE_ALL || new_conf->type == VTSS_SFLOW_TYPE_RX) ? VTSS_F_ANA_ANA_SFLOW_CFG_SF_SAMPLE_RX : 0;
    value |= new_conf->sampling_rate != 0 && (new_conf->type == VTSS_SFLOW_TYPE_ALL || new_conf->type == VTSS_SFLOW_TYPE_TX) ? VTSS_F_ANA_ANA_SFLOW_CFG_SF_SAMPLE_TX : 0;
    L26_WR(VTSS_ANA_ANA_SFLOW_CFG(VTSS_CHIP_PORT(port_no)), value);

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static void l26_debug_print_mask(const vtss_debug_printf_t pr, u32 mask)
{
    u32 port;
    
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        pr("%s%s", port == 0 || (port & 7) ? "" : ".", ((1<<port) & mask) ? "1" : "0");
    }
    pr("  0x%08x\n", mask);
}

static vtss_rc l26_debug_vlan(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455) */ // Due to VTSS_EXIT_ENTER
    vtss_vid_t        vid;
    vtss_vlan_entry_t *vlan_entry;
    BOOL              header = 1;
    u32               port, value, mask = 0;
    char              buf[32];

    for (port = 0; port <= VTSS_CHIP_PORT_CPU_1; port++) {
        VTSS_SPRINTF(buf, "Port %u", port);
        vtss_l26_debug_reg_header(pr, buf);
        if (port != VTSS_CHIP_PORT_CPU_1) {
            vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_VLAN_CFG(port), port, "ANA:VLAN_CFG");
            vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_DROP_CFG(port), port, "ANA:DROP_CFG");
        }
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_REW_PORT_PORT_VLAN_CFG(port), port, "REW:VLAN_CFG");
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_REW_PORT_TAG_CFG(port), port, "REW:TAG_CFG");
        pr("\n");
    }
    vtss_l26_debug_reg(vtss_state, pr, VTSS_SYS_SYSTEM_VLAN_ETYPE_CFG, "ETYPE_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_ANA_ANA_ADVLEARN, "ADVLEARN");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_ANA_ANA_VLANMASK, "VLANMASK");
    pr("\n");
    
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        vlan_entry = &vtss_state->l2.vlan_table[vid];
        if (!(vlan_entry->flags & VLAN_FLAGS_ENABLED) && !info->full)
            continue;

        L26_WR(VTSS_ANA_ANA_TABLES_VLANTIDX, VTSS_F_ANA_ANA_TABLES_VLANTIDX_V_INDEX(vid));
        L26_WR(VTSS_ANA_ANA_TABLES_VLANACCESS, 
               VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_CMD_READ));
        if (l26_vlan_table_idle(vtss_state) != VTSS_RC_OK)
            continue;
        L26_RD(VTSS_ANA_ANA_TABLES_VLANACCESS, &value);
        mask = VTSS_X_ANA_ANA_TABLES_VLANACCESS_VLAN_PORT_MASK(value);
        L26_RD(VTSS_ANA_ANA_TABLES_VLANTIDX, &value);

        if (header)
            vtss_l26_debug_print_port_header(vtss_state, pr, "VID   Lrn  Mir  Flt  Prv  ");
        header = 0;

        pr("%-6u%-5u%-5u%-5u%-5u", vid,
           value & VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_LEARN_DISABLED ? 0 : 1,
           value & VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_MIRROR ? 1 : 0,
           value & VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_SRC_CHK ? 1 : 0,
           value & VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_PRIV_VLAN ? 1 : 0);
        l26_debug_print_mask(pr, mask);

        /* Leave critical region briefly */
        VTSS_EXIT_ENTER();
    }
    if (!header)
        pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc l26_debug_src_table(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    u32 port, mask;

    vtss_debug_print_header(pr, "Source Masks");
    vtss_l26_debug_print_port_header(vtss_state, pr, "Port  ");
    for (port = 0; port <= VTSS_CHIP_PORTS;  port++) {
        L26_RD(VTSS_ANA_ANA_TABLES_PGID(PGID_SRC + port), &mask);
        mask = VTSS_X_ANA_ANA_TABLES_PGID_PGID(mask);
        pr("%-4u  ", port);
        l26_debug_print_mask(pr, mask);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc l26_debug_pvlan(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    vtss_l26_debug_reg_header(pr, "ANA");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_ANA_ANA_ISOLATED_PORTS, "ISOLATED_PORTS");
    pr("\n");

    return l26_debug_src_table(vtss_state, pr, info);
}

static vtss_rc l26_debug_mac_table(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    u32 value, port;

    pr("Port  ID  Learn  L_Auto  L_CPU  L_DROP  PM_DROP PM_CPU Mirror\n");
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        L26_RD(VTSS_ANA_PORT_PORT_CFG(port), &value);
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

    pr("\n");

    /* Read and clear analyzer sticky bits */
    L26_RD(VTSS_ANA_ANA_ANEVENTS, &value);
    L26_WR(VTSS_ANA_ANA_ANEVENTS, value);

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

static vtss_rc l26_debug_aggr(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32 ac, pgid, mask, value;
    
    VTSS_RC(l26_debug_src_table(vtss_state, pr, info));

    vtss_debug_print_header(pr, "Aggregation Masks");
    vtss_l26_debug_print_port_header(vtss_state, pr, "AC    ");
    for (ac = 0; ac < L26_ACS; ac++) {
        L26_RD(VTSS_ANA_ANA_TABLES_PGID(PGID_AGGR + ac), &mask);
        mask = VTSS_X_ANA_ANA_TABLES_PGID_PGID(mask);
        pr("%-4u  ", ac);
        l26_debug_print_mask(pr, mask);
    }
    pr("\n");
    
    vtss_debug_print_header(pr, "Destination Masks");
    vtss_l26_debug_print_port_header(vtss_state, pr, "PGID  CPU  Queue  ");
    for (pgid = 0; pgid < VTSS_PGID_LUTON26; pgid++) {
        L26_RD(VTSS_ANA_ANA_TABLES_PGID(pgid), &value);
        mask = VTSS_X_ANA_ANA_TABLES_PGID_PGID(value);
        pr("%-4u  %-3u  %-5u  ", pgid, mask & VTSS_BIT(VTSS_CHIP_PORT_CPU) ? 1 : 0,
           VTSS_X_ANA_ANA_TABLES_PGID_CPUQ_DST_PGID(value));
        l26_debug_print_mask(pr, mask);
    }
    pr("\n");
    

    vtss_debug_print_header(pr, "Flooding PGIDs");
    L26_RD(VTSS_ANA_ANA_FLOODING, &value);
    pr("UNICAST  : %u\n", VTSS_X_ANA_ANA_FLOODING_FLD_UNICAST(value));
    pr("MULTICAST: %u\n", VTSS_X_ANA_ANA_FLOODING_FLD_MULTICAST(value));
    L26_RD(VTSS_ANA_ANA_FLOODING_IPMC, &value);
    pr("MC4_CTRL : %u\n", VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC4_CTRL(value));
    pr("MC4_DATA : %u\n", VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC4_DATA(value));
    pr("MC6_CTRL : %u\n", VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL(value));
    pr("MC6_DATA : %u\n", VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC6_DATA(value));
    pr("\n");

    vtss_l26_debug_reg_header(pr, "Aggr. Mode");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_ANA_COMMON_AGGR_CFG, "AGGR_CFG");
    pr("\n");
    
    return VTSS_RC_OK;
}

static vtss_rc l26_debug_stp(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    u32 port;

    for (port = 0; port <= VTSS_CHIP_PORTS; port++)
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_PORT_CFG(port), port, "PORT_CFG");
    pr("\n");
    return VTSS_RC_OK;
}

static vtss_rc l26_debug_mirror(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    u32  port, value, mask = 0;
    
    /* Calculate ingress mirror mask */
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        L26_RD(VTSS_ANA_PORT_PORT_CFG(port), &value);
        if (value & VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA)
            mask |= VTSS_BIT(port);
    }
    vtss_l26_debug_print_port_header(vtss_state, pr, "Mirror   ");
    pr("Ingress  ");
    l26_debug_print_mask(pr, mask);
    L26_RD(VTSS_ANA_ANA_EMIRRORPORTS, &mask);
    pr("Egress   ");
    l26_debug_print_mask(pr, mask);
    L26_RD(VTSS_ANA_ANA_MIRRORPORTS, &mask);
    pr("Ports    ");
    l26_debug_print_mask(pr, mask);
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc l26_debug_ipmc(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455) */ // Due to VTSS_EXIT_ENTER
    vtss_mac_entry_t        *entry;
    vtss_vid_mac_t          vid_mac;
    vtss_mac_table_entry_t  mac_entry;
    u8                      *p = &vid_mac.mac.addr[0];
    BOOL                    header = TRUE;
    u32                     pgid;

    VTSS_RC(vtss_l26_debug_range_checkers(vtss_state, pr, info));
    VTSS_RC(vtss_l26_debug_vcap_port(vtss_state, pr, info));
    VTSS_RC(vtss_l26_debug_vcap_is1(vtss_state, pr, info));

    /* MAC address table in state */
    for (entry = vtss_state->l2.mac_list_used; entry != NULL; entry = entry->next) {
        if (header)
            vtss_debug_print_port_header(vtss_state, pr, "VID   MAC                CPU  User  ", 0, 1);
        header = FALSE;
        vtss_mach_macl_set(&vid_mac, entry->mach, entry->macl);
        pr("%-4u  %02x-%02x-%02x-%02x-%02x-%02x  %-3u  %-4x  ",
           vid_mac.vid, p[0], p[1], p[2], p[3], p[4], p[5], entry->cpu_copy, entry->user);
        vtss_debug_print_ports(vtss_state, pr, entry->member, 1);
        VTSS_EXIT_ENTER();
    }
    if (!header)
        pr("\n");

    /* MAC address table in chip */
    header = TRUE;
    VTSS_MEMSET(&mac_entry, 0, sizeof(mac_entry));
    p = &mac_entry.vid_mac.mac.addr[0];
    while (l26_mac_table_get_next(vtss_state, &mac_entry, &pgid) == VTSS_RC_OK) {
        if (header)
            pr("VID   MAC                PGID  CPU  Locked\n");
        header = FALSE;
        pr("%-4u  %02x-%02x-%02x-%02x-%02x-%02x  %-4u  %-3u  %u\n",
           mac_entry.vid_mac.vid, p[0], p[1], p[2], p[3], p[4], p[5],
           pgid, mac_entry.copy_to_cpu, mac_entry.locked);
        VTSS_EXIT_ENTER();
    }
    if (!header)
        pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc l26_debug_vxlat(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_l26_debug_vcap_is1(vtss_state, pr, info));
    VTSS_RC(vtss_l26_debug_vcap_es0(vtss_state, pr, info));
    
    return VTSS_RC_OK;
}

vtss_rc vtss_l26_l2_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VLAN, l26_debug_vlan, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PVLAN, l26_debug_pvlan, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MAC_TABLE, l26_debug_mac_table, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_AGGR, l26_debug_aggr, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_STP, l26_debug_stp, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MIRROR, l26_debug_mirror, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_VXLAT, l26_debug_vxlat, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_IPMC, l26_debug_ipmc, vtss_state, pr, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc l26_l2_init(vtss_state_t *vtss_state)
{
    vtss_vid_t vid;
    u32        port;

    /* Clear MAC table */
    L26_WR(VTSS_ANA_ANA_TABLES_MACACCESS,
           VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MAC_CMD_TABLE_CLEAR));

    /* Clear VLAN table */
    L26_WR(VTSS_ANA_ANA_TABLES_VLANACCESS,
           VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_CMD_TABLE_CLEAR));

    /* Clear VLAN table masks */
    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        if (vid == VTSS_VID_DEFAULT) /* Default VLAN includes all ports */
            continue;
        L26_WR(VTSS_ANA_ANA_TABLES_VLANTIDX,
               VTSS_F_ANA_ANA_TABLES_VLANTIDX_V_INDEX(vid));
        L26_WR(VTSS_ANA_ANA_TABLES_VLANACCESS,
               /* Zero port mask */
               VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_CMD_WRITE));
        VTSS_RC(l26_vlan_table_idle(vtss_state));
    }

    /* Setup VLAN configuration */
    VTSS_RC(l26_vlan_conf_apply(vtss_state, 0));

    /* Setup chip ports */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        /* Default VLAN port configuration */
        VTSS_RC(l26_vlan_port_conf_apply(vtss_state, port, 
                                         &vtss_state->l2.vlan_port_conf[VTSS_PORT_NO_START]));
    } /* Port loop */
    
    /* Setup aggregation mode */
    VTSS_RC(l26_aggr_mode_set(vtss_state));
    
    /* Set MAC age time to default value */
    VTSS_RC(l26_mac_table_age_time_set(vtss_state));

    /* Disable learning for frames discarded by VLAN ingress filtering */
    L26_WR(VTSS_ANA_ANA_ADVLEARN, VTSS_F_ANA_ANA_ADVLEARN_VLAN_CHK);

    /* Ignore CPU copy flag in DMAC lookup */
    L26_WRM_SET(VTSS_ANA_ANA_AGENCTRL, VTSS_F_ANA_ANA_AGENCTRL_IGNORE_DMAC_FLAGS);

    /* Setup frame ageing - fixed value "2 sec" - in 4ns units */
    L26_WR(VTSS_SYS_SYSTEM_FRM_AGING, (2 * 1000000 * 1000 / 4));

    return VTSS_RC_OK;
}

static vtss_rc l26_l2_port_map_set(vtss_state_t *vtss_state)
{
    /* We only need to setup the no of avail pgids */
    vtss_state->l2.pgid_count = (VTSS_PGID_LUTON26 - VTSS_CHIP_PORTS + vtss_state->port_count);

    /* And then claim some for flooding */
    VTSS_RC(l26_flood_conf_set(vtss_state));

    /* Setup flooding PGIDs */
    L26_WR(VTSS_ANA_ANA_FLOODING, 
           VTSS_F_ANA_ANA_FLOODING_FLD_UNICAST(PGID_UC) |
           VTSS_F_ANA_ANA_FLOODING_FLD_BROADCAST(PGID_MC) |
           VTSS_F_ANA_ANA_FLOODING_FLD_MULTICAST(PGID_MC));
    
    L26_WR(VTSS_ANA_ANA_FLOODING_IPMC, 
           VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC4_CTRL(PGID_MC) |
           VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC4_DATA(PGID_MCIPV4) |
           VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL(PGID_MC) |
           VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC6_DATA(PGID_MCIPV6));

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_l2_state_t *state = &vtss_state->l2;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->mac_table_add = l26_mac_table_add;
        state->mac_table_del = l26_mac_table_del;
        state->mac_table_get = l26_mac_table_get;
        state->mac_table_get_next = l26_mac_table_get_next;
        state->mac_table_age_time_set = l26_mac_table_age_time_set;
        state->mac_table_age = l26_mac_table_age;
        state->mac_table_status_get = l26_mac_table_status_get;
        state->learn_port_mode_set = l26_learn_port_mode_set;
        state->learn_state_set = l26_learn_state_set;
        state->mstp_state_set = vtss_cmn_mstp_state_set;
        state->mstp_vlan_msti_set = vtss_cmn_vlan_members_set;
        state->erps_vlan_member_set = vtss_cmn_erps_vlan_member_set;
        state->erps_port_state_set = vtss_cmn_erps_port_state_set;
        state->pgid_table_write = l26_pgid_table_write;
        state->src_table_write = l26_src_table_write;
        state->aggr_table_write = l26_aggr_table_write;
        state->aggr_mode_set = l26_aggr_mode_set;
        state->pmap_table_write = l26_pmap_table_write;
        state->vlan_conf_set = l26_vlan_conf_set;
        state->vlan_port_conf_set = vtss_cmn_vlan_port_conf_set;
        state->vlan_port_conf_update = l26_vlan_port_conf_update;
        state->vlan_port_members_set = vtss_cmn_vlan_members_set;
        state->vlan_mask_update = l26_vlan_mask_update;
        state->vlan_tx_tag_set = vtss_cmn_vlan_tx_tag_set;
        state->isolated_vlan_set = vtss_cmn_vlan_members_set;
        state->isolated_port_members_set = l26_isolated_port_members_set;
        state->flood_conf_set = l26_flood_conf_set;
        state->ipv4_mc_add = vtss_cmn_ipv4_mc_add;
        state->ipv4_mc_del = vtss_cmn_ipv4_mc_del;
        state->ipv6_mc_add = vtss_cmn_ipv6_mc_add;
        state->ipv6_mc_del = vtss_cmn_ipv6_mc_del;
        state->ip_mc_update = l26_ip_mc_update;
        state->mirror_port_set = l26_mirror_port_set;
        state->mirror_ingress_set = l26_mirror_ingress_set;
        state->mirror_egress_set = l26_mirror_egress_set;
        state->mirror_cpu_ingress_set = l26_mirror_cpu_ingress_set;
        state->mirror_cpu_egress_set = l26_mirror_cpu_egress_set;
        state->eps_port_set = vtss_cmn_eps_port_set;
        state->sflow_port_conf_set = l26_sflow_port_conf_set;
        state->sflow_sampling_rate_convert = l26_sflow_sampling_rate_convert;
        state->vcl_port_conf_set = vtss_l26_vcl_port_conf_set;
        state->vce_add = vtss_cmn_vce_add;
        state->vce_del = vtss_cmn_vce_del;
        state->vlan_trans_group_add = vtss_cmn_vlan_trans_group_add;
        state->vlan_trans_group_del = vtss_cmn_vlan_trans_group_del;
        state->vlan_trans_group_get = vtss_cmn_vlan_trans_group_get;
        state->vlan_trans_port_conf_set  = vtss_cmn_vlan_trans_port_conf_set;
        state->vlan_trans_port_conf_get  = vtss_cmn_vlan_trans_port_conf_get;
        state->ac_count = L26_ACS;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(l26_l2_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(l26_l2_port_map_set(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LUTON26 */
