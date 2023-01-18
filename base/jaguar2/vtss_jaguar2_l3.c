// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L3
#include "vtss_jaguar2_cil.h"

#if defined(VTSS_ARCH_JAGUAR_2) && defined(VTSS_FEATURE_LAYER3)

/* Enable ingress routing edit of SMAC/DMAC */
#define JR2_L3_INGRESS_MAC_UPDATE


/* - CIL functions ------------------------------------------------- */

/* L3 counter indices */
#define JR2_L3_CNT_IP_UC_PACKETS 0
#define JR2_L3_CNT_IP_UC_BYTES   1
#define JR2_L3_CNT_IP_MC_PACKETS 2
#define JR2_L3_CNT_IP_MC_BYTES   3

static vtss_rc jr2_l3_common_set(vtss_state_t *vtss_state,
                                 const vtss_l3_common_conf_t * const conf)
{
    const u8 *addr = conf->base_address.addr;
    u32      type_sel = 2;
    u32      msb = ((addr[0] << 16) | (addr[1] << 8) | addr[2]);
    u32      lsb = ((addr[3] << 16) | (addr[4] << 8) | addr[5]);
    u64      port_mask = 0xffffffffffffffff;
    
    /* Setup router leg MAC address and type */
    JR2_WR(VTSS_ANA_L3_COMMON_RLEG_CFG_0, VTSS_F_ANA_L3_COMMON_RLEG_CFG_0_RLEG_MAC_LSB(lsb));
    JR2_WR(VTSS_ANA_L3_COMMON_RLEG_CFG_1,
           VTSS_F_ANA_L3_COMMON_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(type_sel) |
           VTSS_F_ANA_L3_COMMON_RLEG_CFG_1_RLEG_MAC_MSB(msb));
#if !defined(JR2_L3_INGRESS_MAC_UPDATE)
    JR2_WR(VTSS_REW_COMMON_RLEG_CFG_0, VTSS_F_REW_COMMON_RLEG_CFG_0_RLEG_MAC_LSB(lsb));
    JR2_WR(VTSS_REW_COMMON_RLEG_CFG_1,
           VTSS_F_REW_COMMON_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(type_sel) |
           VTSS_F_REW_COMMON_RLEG_CFG_1_RLEG_MAC_MSB(msb));
#endif

    /* Enable/disable routing */
    JR2_WR_PMASK(VTSS_ANA_L3_COMMON_L3_UC_ENA, port_mask);
    JR2_WR_PMASK(VTSS_ANA_L3_COMMON_L3_MC_ENA, port_mask);

    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_rleg_counter_update(vtss_state_t *vtss_state,
                                          BOOL rx, u32 i, u32 j, u64 *prev, u64 *counter)
{
    vtss_chip_counter_t chip_counter;
    u32                 lsb, msb;

    /* Copy counter state */
    chip_counter.prev = *prev;
    chip_counter.value = *counter;

    if (rx) {
        /* Read IRLEG counter */
        JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_LSB_CNT(i, j), &lsb);
        JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_MSB_CNT(i, j), &msb);
    } else {
        /* Read ERLEG counter */
        JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_LSB_CNT(i, j), &lsb);
        JR2_RD(VTSS_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_MSB_CNT(i, j), &msb);
    }

    /* Update counter */
    vtss_cmn_counter_40_update(lsb, msb, &chip_counter, FALSE);
    *prev = chip_counter.prev;
    *counter = chip_counter.value;

    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_rleg_hw_stat_poll(vtss_state_t *vtss_state,
                                        vtss_l3_rleg_id_t rleg)
{
    vtss_l3_counters_t *prev = &vtss_state->l3.statistics.interface_shadow_counter[rleg];
    vtss_l3_counters_t *counter = &vtss_state->l3.statistics.interface_counter[rleg];

    /* IPv4 UC counters */
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, TRUE, rleg, JR2_L3_CNT_IP_UC_PACKETS,
                                       &prev->ipv4uc_received_frames, &counter->ipv4uc_received_frames));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, TRUE, rleg, JR2_L3_CNT_IP_UC_BYTES,
                                       &prev->ipv4uc_received_octets, &counter->ipv4uc_received_octets));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, FALSE, rleg, JR2_L3_CNT_IP_UC_PACKETS,
                                       &prev->ipv4uc_transmitted_frames, &counter->ipv4uc_transmitted_frames));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, FALSE, rleg, JR2_L3_CNT_IP_UC_BYTES,
                                       &prev->ipv4uc_transmitted_octets, &counter->ipv4uc_transmitted_octets));
    /* IPv4 MC counters */
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, TRUE, rleg, JR2_L3_CNT_IP_MC_PACKETS,
                                       &prev->ipv4mc_received_frames, &counter->ipv4mc_received_frames));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, TRUE, rleg, JR2_L3_CNT_IP_MC_BYTES,
                                       &prev->ipv4mc_received_octets, &counter->ipv4mc_received_octets));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, FALSE, rleg, JR2_L3_CNT_IP_MC_PACKETS,
                                       &prev->ipv4mc_transmitted_frames, &counter->ipv4mc_transmitted_frames));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, FALSE, rleg, JR2_L3_CNT_IP_MC_BYTES,
                                       &prev->ipv4mc_transmitted_octets, &counter->ipv4mc_transmitted_octets));


    /* IPv6 UC counters */
    rleg += VTSS_RLEG_STAT_CNT;
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, TRUE, rleg, JR2_L3_CNT_IP_UC_PACKETS,
                                       &prev->ipv6uc_received_frames, &counter->ipv6uc_received_frames));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, TRUE, rleg, JR2_L3_CNT_IP_UC_BYTES,
                                       &prev->ipv6uc_received_octets, &counter->ipv6uc_received_octets));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, FALSE, rleg, JR2_L3_CNT_IP_UC_PACKETS,
                                       &prev->ipv6uc_transmitted_frames, &counter->ipv6uc_transmitted_frames));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, FALSE, rleg, JR2_L3_CNT_IP_UC_BYTES,
                                       &prev->ipv6uc_transmitted_octets, &counter->ipv6uc_transmitted_octets));
    /* IPv6 MC counters */
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, TRUE, rleg, JR2_L3_CNT_IP_MC_PACKETS,
                                       &prev->ipv6mc_received_frames, &counter->ipv6mc_received_frames));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, TRUE, rleg, JR2_L3_CNT_IP_MC_BYTES,
                                       &prev->ipv6mc_received_octets, &counter->ipv6mc_received_octets));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, FALSE, rleg, JR2_L3_CNT_IP_MC_PACKETS,
                                       &prev->ipv6mc_transmitted_frames, &counter->ipv6mc_transmitted_frames));
    VTSS_RC(jr2_l3_rleg_counter_update(vtss_state, FALSE, rleg, JR2_L3_CNT_IP_MC_BYTES,
                                       &prev->ipv6mc_transmitted_octets, &counter->ipv6mc_transmitted_octets));


    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_rleg_stat_reset(vtss_state_t *vtss_state)
{
    u32 i, j;

    for (i = 0; i < (2*VTSS_RLEG_STAT_CNT); i++) {
        for (j = 0; j < 4; j++) {
            JR2_WR(VTSS_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_MSB_CNT(i, j), 0);
            JR2_WR(VTSS_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_LSB_CNT(i, j), 0);
            JR2_WR(VTSS_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_MSB_CNT(i, j), 0);
            JR2_WR(VTSS_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_LSB_CNT(i, j), 0);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_rleg_set(vtss_state_t *vtss_state,
                               const vtss_l3_rleg_id_t   rleg,
                               const vtss_l3_rleg_conf_t *const conf)
{
    BOOL vrid_enable = (conf->vrid0_enable || conf->vrid1_enable);
    u32  i, vrid;

    JR2_WR(VTSS_ANA_L3_VMID_RLEG_CTRL(rleg),
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_EVID(conf->vlan) |
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_IP6_UC_ENA(conf->ipv6_unicast_enable) |
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_IP4_UC_ENA(conf->ipv4_unicast_enable) |
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_IP6_MC_ENA(conf->ipv6_multicast_enable) |
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_IP4_MC_ENA(conf->ipv4_multicast_enable) |
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_IP6_ICMP_REDIR_ENA(conf->ipv6_icmp_redirect_enable) |
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_IP4_ICMP_REDIR_ENA(conf->ipv4_icmp_redirect_enable) |
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_IP6_VRID_ENA(vrid_enable) |
           VTSS_F_ANA_L3_VMID_RLEG_CTRL_RLEG_IP4_VRID_ENA(vrid_enable));

    JR2_WRM(VTSS_ANA_L3_VMID_VMID_MC(rleg),
            VTSS_F_ANA_L3_VMID_VMID_MC_RLEG_IP6_MC_TTL(conf->mc_ttl_limit_enable ? conf->mc_ttl_limit : 0) |
            VTSS_F_ANA_L3_VMID_VMID_MC_RLEG_IP4_MC_TTL(conf->mc_ttl_limit_enable ? conf->mc_ttl_limit : 0),
            VTSS_M_ANA_L3_VMID_VMID_MC_RLEG_IP6_MC_TTL |
            VTSS_M_ANA_L3_VMID_VMID_MC_RLEG_IP4_MC_TTL);

    /* If only one VRID is enabled, both are set to the same value */
    for (i = 0; i < 2; i++) {
        vrid = (i == 0 ? (conf->vrid0_enable ? conf->vrid0 : conf->vrid1) :
                (conf->vrid1_enable ? conf->vrid1 : conf->vrid0));
        JR2_WR(VTSS_ANA_L3_VMID_VRRP_CFG(rleg, i),
               VTSS_F_ANA_L3_VMID_VRRP_CFG_RLEG_IP6_VRID(vrid) |
               VTSS_F_ANA_L3_VMID_VRRP_CFG_RLEG_IP4_VRID(vrid));
    }

    JR2_WR(VTSS_REW_VMID_RLEG_CTRL(rleg), VTSS_F_REW_VMID_RLEG_CTRL_RLEG_EVID(conf->vlan));

    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_vlan_set(vtss_state_t *vtss_state,
                               const vtss_l3_rleg_id_t rleg_id,
                               const vtss_vid_t        vid,
                               const BOOL              enable)
{
    vtss_vlan_entry_t *vlan_entry = &vtss_state->l2.vlan_table[vid];

    vlan_entry->rl_enable = enable;
    vlan_entry->rl_id = rleg_id;
    return vtss_jr2_vlan_update(vtss_state, vid);
}

static u32 jr2_l3_cpu_queue(vtss_state_t *vtss_state, vtss_ip_addr_t *dip)
{
    vtss_packet_rx_queue_map_t *map = &vtss_state->packet.rx_conf.map;
    BOOL                       dip_zero = TRUE;
    int                        i;

    if (dip->type == VTSS_IP_TYPE_IPV6) {
        for (i = 0; i < 16; i++) {
            if (dip->addr.ipv6.addr[i]) {
                dip_zero = FALSE;
                break;
            }
        }
    } else if (dip->addr.ipv4 != 0) {
        dip_zero = FALSE;
    }
    /* Use L3 UC queue if direct route */
    return (dip_zero ? map->l3_uc_queue : map->l3_other_queue);
}

static vtss_rc jr2_l3_mc_rt_rleg_add(vtss_state_t *vtss_state, vtss_l3_mc_rt_t *grp)
{
    vtss_l3_mc_tbl_t *tbl = &vtss_state->l3.mc_tbl[grp->tbl];

#if defined(VTSS_ARCH_SERVAL_T)
        JR2_WRM(VTSS_ANA_L3_L3MC_EVMID_MASK_CFG(grp->tbl),
                VTSS_F_ANA_L3_L3MC_EVMID_MASK_CFG_EVMID_MASK(tbl->rlegs[0]),
                VTSS_M_ANA_L3_L3MC_EVMID_MASK_CFG_EVMID_MASK);
#else
        for (u16 i = 0; i < 4; i++) {
            JR2_WRM(VTSS_ANA_L3_L3MC_EVMID_MASK_CFG(grp->tbl, i),
                    VTSS_F_ANA_L3_L3MC_EVMID_MASK_CFG_EVMID_MASK(tbl->rlegs[i]),
                    VTSS_M_ANA_L3_L3MC_EVMID_MASK_CFG_EVMID_MASK);

        }
#endif
    JR2_WRM(VTSS_ANA_L3_L3MC_L3MC_CTRL(grp->tbl),
            VTSS_F_ANA_L3_L3MC_L3MC_CTRL_RPF_CHK_ENA(tbl->rpf == VTSS_L3_MC_RPF_DIS ? 0 : 1) |
            VTSS_F_ANA_L3_L3MC_L3MC_CTRL_RPF_VMID(tbl->rpf == VTSS_L3_MC_RPF_DIS ? 0 : tbl->rpf),
            VTSS_M_ANA_L3_L3MC_L3MC_CTRL_RPF_CHK_ENA |
            VTSS_M_ANA_L3_L3MC_L3MC_CTRL_RPF_VMID);

    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_mc_rt_add(vtss_state_t *vtss_state, vtss_l3_mc_rt_t *rt)
{
    vtss_vcap_obj_t   *obj = &vtss_state->vcap.lpm.obj;
    vtss_vcap_data_t  data;
    vtss_lpm_entry_t  entry;
    vtss_lpm_key_t    *key = &entry.key;
    vtss_lpm_action_t *action = &entry.action;
    vtss_ip_addr_t    *addr = &rt->network;
    vtss_ip_addr_t    *sip = &rt->sip;
    u32               i, sum = 0;
    u8                sip_mask;

    VTSS_MEMSET(&data, 0, sizeof(data));
    VTSS_MEMSET(&entry, 0, sizeof(entry));
    data.u.lpm.entry = &entry;

    VTSS_RC(jr2_l3_mc_rt_rleg_add(vtss_state, rt));

    /* Key */
    if (addr->type == VTSS_IP_TYPE_IPV4) {
        /* IPv4 multicast */
        data.key_size = VTSS_VCAP_KEY_SIZE_EIGHTH;
        key->type = VTSS_LPM_KEY_DBL_IP4;
        key->data.dbl_ip4.dip.value = addr->addr.ipv4;
        key->data.dbl_ip4.dip.mask = 0xFFFFFFFF;
        key->data.dbl_ip4.sip.value = sip->addr.ipv4;
        key->data.dbl_ip4.sip.mask = (sip->addr.ipv4 == 0) ? 0 : 0xFFFFFFFF;
    } else {
        /* IPv6 multicast */
        data.key_size = VTSS_VCAP_KEY_SIZE_HALF;
        key->type = VTSS_LPM_KEY_DBL_IP6;
        for (i = 0; i < 16; i++) {
            sum += sip->addr.ipv6.addr[i];
        }
        sip_mask = sum == 0 ? 0 : 0xFF;
        for (i = 0; i < 16; i++) {
            key->data.dbl_ip6.dip.value[i] = addr->addr.ipv6.addr[i];
            key->data.dbl_ip6.dip.mask[i] = 0xFF;
            key->data.dbl_ip6.sip.value[i] = sip->addr.ipv6.addr[i];
            key->data.dbl_ip6.sip.mask[i] = sip_mask;
        }
    }

    /* Action */
    action->type = LPM_TYPE_L3MC_PTR;
    action->data.l3mc_idx = rt->tbl;

    return vtss_vcap_add(vtss_state, obj, VTSS_LPM_USER_L3_MC, rt->id,
                         rt->next == NULL ? VTSS_VCAP_ID_LAST : rt->next->id,
                         &data, 0);
}

static vtss_rc jr2_l3_rt_add(vtss_state_t *vtss_state,
                             vtss_l3_net_t *net, vtss_l3_nb_t *nb, u32 cnt)
{
    vtss_vcap_obj_t   *obj = &vtss_state->vcap.lpm.obj;
    vtss_vcap_data_t  data;
    vtss_lpm_entry_t  entry;
    vtss_lpm_key_t    *key = &entry.key;
    vtss_lpm_action_t *action = &entry.action;
    vtss_ip_addr_t    *addr = &net->network;
    u32               i, j, n, mask = 0, len = net->prefix_size;

    VTSS_MEMSET(&data, 0, sizeof(data));
    VTSS_MEMSET(&entry, 0, sizeof(entry));
    data.u.lpm.entry = &entry;
    if (addr->type == VTSS_IP_TYPE_IPV4) {
        data.key_size = VTSS_VCAP_KEY_SIZE_SIXTEENTH;
        key->type = VTSS_LPM_KEY_SGL_IP4;
        key->data.sgl_ip4.dst_ena = 1;
        key->data.sgl_ip4.xip.value = addr->addr.ipv4;
        for (i = 0; i < 32; i++) {
            mask <<= 1;
            if (i < len) {
                mask |= 1;
            }
        }
        key->data.sgl_ip4.xip.mask = mask;
    } else {
        data.key_size = VTSS_VCAP_KEY_SIZE_QUARTER;
        key->type = VTSS_LPM_KEY_SGL_IP6;
        key->data.sgl_ip6.dst_ena = 1;
        for (i = 0; i < 16; i++) {
            key->data.sgl_ip6.xip.value[i] = addr->addr.ipv6.addr[i];
            n = 8 * i;
            mask = 0;
            for (j = 0; j < 8; j++) {
                mask <<= 1;
                if ((n + j) < len) {
                    mask |= 1;
                }
            }
            key->data.sgl_ip6.xip.mask[i] = mask;
        }
    }
    if (net->grp == NULL) {
        action->type = LPM_TYPE_ARP_ENTRY;
        action->data.arp_entry.mac = nb->dmac;
        action->data.arp_entry.vmid = nb->rleg;
        action->data.arp_entry.cpu_queue = jr2_l3_cpu_queue(vtss_state, &net->nh.dip);
        action->data.arp_entry.arp_ena = 1;
    } else {
        action->type = LPM_TYPE_ARP_PTR;
        action->data.arp_ptr.arp_ptr = net->grp->idx;
        action->data.arp_ptr.ecmp_cnt = (cnt - 1);
    }

    return vtss_vcap_add(vtss_state, obj, VTSS_LPM_USER_L3, net->id,
                         net->next == NULL ? VTSS_VCAP_ID_LAST : net->next->id,
                         &data, 0);
}

static vtss_rc jr2_l3_rt_del(vtss_state_t *vtss_state,
                             vtss_l3_net_t *net)
{
    vtss_vcap_obj_t *obj = &vtss_state->vcap.lpm.obj;
    return vtss_vcap_del(vtss_state, obj, VTSS_LPM_USER_L3, net->id);
}

static vtss_rc jr2_l3_mc_rt_del(vtss_state_t *vtss_state,
                                vtss_l3_mc_rt_t *rt)
{
    vtss_vcap_obj_t *obj = &vtss_state->vcap.lpm.obj;
    return vtss_vcap_del(vtss_state, obj, VTSS_LPM_USER_L3_MC, rt->id);
}

static vtss_rc jr2_l3_arp_set(vtss_state_t *vtss_state,
                              u32 idx, vtss_l3_nb_t *nb)
{
    const u8 *addr = nb->dmac.addr;
    u32      msb = ((addr[0] << 8) | addr[1]);
    u32      lsb = ((addr[2] << 24) | (addr[3] << 16) | (addr[4] << 8) | addr[5]);
    u32      queue = vtss_state->packet.rx_conf.map.l3_other_queue;

    JR2_WR(VTSS_ANA_L3_ARP_ARP_CFG_0(idx),
           VTSS_F_ANA_L3_ARP_ARP_CFG_0_MAC_MSB(msb) |
           VTSS_F_ANA_L3_ARP_ARP_CFG_0_ARP_VMID(nb->rleg) |
           VTSS_F_ANA_L3_ARP_ARP_CFG_0_ZERO_DMAC_CPU_QU(queue) |
           VTSS_F_ANA_L3_ARP_ARP_CFG_0_ARP_ENA(1));
    JR2_WR(VTSS_ANA_L3_ARP_ARP_CFG_1(idx), lsb);

    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_debug_sticky_clear(vtss_state_t *vtss_state)
{
    u32 value = 0xffffffff;

    JR2_WR(VTSS_ANA_L3_LPM_REMAP_STICKY_L3_LPM_REMAP_STICKY, value);
    JR2_WR(VTSS_ANA_L3_VLAN_ARP_L3MC_STICKY_VLAN_STICKY, value);
    JR2_WR(VTSS_ANA_L3_VLAN_ARP_L3MC_STICKY_L3_ARP_IPMC_STICKY, value);

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static void jr2_l3_debug_cnt(const vtss_debug_printf_t pr, const char *name, u64 rx_cnt, u64 tx_cnt)
{
    vtss_chip_counter_t c1, c2;

    c1.value = rx_cnt;
    c2.value = tx_cnt;

    vtss_jr2_debug_cnt(pr, name, "", &c1, &c2);
}

vtss_rc vtss_jr2_l3_debug_print(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    BOOL               header = 1, found = 0;
    vtss_vid_t         vid;
    u32                i, value, enable, cfg0, cfg1, v[4];
    char               buf0[16], buf1[16];
    vtss_l3_counters_t *cnt;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_L3)) {
        return VTSS_RC_OK;
    }

    vtss_jr2_debug_reg_header(pr, "ANA_L3");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_L3_COMMON_ROUTING_CFG, "ROUTING_CFG");
    pr("\n");

    JR2_RD(VTSS_ANA_L3_COMMON_RLEG_CFG_0, &cfg0);
    JR2_RD(VTSS_ANA_L3_COMMON_RLEG_CFG_1, &cfg1);
    pr("Router MAC: %06x-%06x (Type %u)\n\n",
       VTSS_X_ANA_L3_COMMON_RLEG_CFG_1_RLEG_MAC_MSB(cfg1),
       VTSS_X_ANA_L3_COMMON_RLEG_CFG_0_RLEG_MAC_LSB(cfg0),
       VTSS_X_ANA_L3_COMMON_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(cfg1));
    
    for (i = 0; i < VTSS_RLEG_STAT_CNT; i++) {
        if (i < VTSS_RLEG_CNT && vtss_state->l3.rleg_conf[i].vlan == 0 && !info->full) {
            continue;
        }
        
        if (header) {
            pr("RLEG  VID   IP4_UC  IP6_UC  IP4_MC  IP6_MC  IP4_REDIR  IP6_REDIR  IP4_VRID     IP6_VRID    MC_TTL\n");
            header = 0;
        }
        JR2_RD(VTSS_ANA_L3_VMID_RLEG_CTRL(i), &value);
        JR2_RD(VTSS_ANA_L3_VMID_VRRP_CFG(i, 0), &cfg0);
        JR2_RD(VTSS_ANA_L3_VMID_VRRP_CFG(i, 1), &cfg1);
        VTSS_SPRINTF(buf0, "%u (%u/%u)",
                VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_IP4_VRID_ENA(value),
                VTSS_X_ANA_L3_VMID_VRRP_CFG_RLEG_IP4_VRID(cfg0),
                VTSS_X_ANA_L3_VMID_VRRP_CFG_RLEG_IP4_VRID(cfg1));
        VTSS_SPRINTF(buf1, "%u (%u/%u)",
                VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_IP6_VRID_ENA(value),
                VTSS_X_ANA_L3_VMID_VRRP_CFG_RLEG_IP6_VRID(cfg0),
                VTSS_X_ANA_L3_VMID_VRRP_CFG_RLEG_IP6_VRID(cfg1));
        pr("%-6u%-6u%-8u%-8u%-8u%-8u%-11u%-11u%-13s%-13s",
           i,
           VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_EVID(value),
           VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_IP4_UC_ENA(value),
           VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_IP6_UC_ENA(value),
           VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_IP4_MC_ENA(value),
           VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_IP6_MC_ENA(value),
           VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_IP4_ICMP_REDIR_ENA(value),
           VTSS_X_ANA_L3_VMID_RLEG_CTRL_RLEG_IP6_ICMP_REDIR_ENA(value),
           buf0,
           buf1);

        JR2_RD(VTSS_ANA_L3_VMID_VMID_MC(i), &value);
        pr("%-12d\n", VTSS_X_ANA_L3_VMID_VMID_MC_RLEG_IP4_MC_TTL(value));
    }
    if (!header) {
        pr("\n");
        header = 1;
    }

    for (vid = VTSS_VID_NULL; vid < VTSS_VIDS; vid++) {
        if (!(vtss_state->l2.vlan_table[vid].flags & VLAN_FLAGS_ENABLED) && !info->full) {
            continue;
        }
        
        if (header) {
            pr("VID   RLEG_ENA  VMID\n");
            header = 0;
        }
        JR2_RD(VTSS_ANA_L3_VLAN_VLAN_CFG(vid), &value);
        enable = VTSS_X_ANA_L3_VLAN_VLAN_CFG_VLAN_RLEG_ENA(value);
        if (!enable && !info->full) {
            continue;
        }
        JR2_RD(VTSS_ANA_L3_VLAN_VMID_CFG(vid), &value);
        pr("%-6u%-10u%-4u\n", vid, enable, VTSS_X_ANA_L3_VLAN_VMID_CFG_VMID(value));
        
        /* Leave critical region briefly */
        VTSS_EXIT_ENTER();
    }
    if (!header) {
        pr("\n");
        header = 1;
    }

    VTSS_RC(vtss_jr2_debug_lpm(vtss_state, pr, info));

    for (i = 0; i < VTSS_ARP_CNT; i++) {
        JR2_RD(VTSS_ANA_L3_ARP_ARP_CFG_0(i), &cfg0);
        if (VTSS_X_ANA_L3_ARP_ARP_CFG_0_ARP_ENA(cfg0) == 0 && !info->full) {
            continue;
        }

        JR2_RD(VTSS_ANA_L3_ARP_ARP_CFG_1(i), &cfg1);
        if (header) {
            pr("IDX   MAC           VMID\n");
            header = 0;
        }
        pr("%-6u%04x%08x  %u\n",
           i,
           VTSS_X_ANA_L3_ARP_ARP_CFG_0_MAC_MSB(cfg0),
           cfg1,
           VTSS_X_ANA_L3_ARP_ARP_CFG_0_ARP_VMID(cfg0));
    }
    if (!header) {
        pr("\n");
    }


    header = 1;
    for (i = 0; i < VTSS_MC_TBL_CNT; i++) {
#if defined(VTSS_ARCH_SERVAL_T)
        JR2_RD(VTSS_ANA_L3_L3MC_EVMID_MASK_CFG(i), &v[0]);
        if (v[0] > 0) {
            found = 1;
        }
#else
        for (u16 a = 0; a < 4; a++) {
            JR2_RD(VTSS_ANA_L3_L3MC_EVMID_MASK_CFG(i, a), &v[a]);
            if (v[a] > 0) {
                found = 1;
            }
        }
#endif

        if (header) {
            pr("MC Router leg mask table:\n");
            pr("ID      indx 0  indx 1 indx 2 indx 3\n");
            header = 0;
        }
        if (found) {
            pr("%d       0x%x     0x%x    0x%x    0x%x\n",i,v[0],v[1],v[2],v[3]);
            found = 0;
        }
    }
    if (!header) {
        pr("\n");
    }

    if (info->clear || info->full) {
        /* Read and clear sticky bits */
        vtss_jr2_debug_reg_header(pr, "ANA_L3:STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_L3_LPM_REMAP_STICKY_L3_LPM_REMAP_STICKY, "LPM_REMAP_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_L3_VLAN_ARP_L3MC_STICKY_VLAN_STICKY, "VLAN_STICKY");
        vtss_jr2_debug_sticky(vtss_state, pr, VTSS_ANA_L3_VLAN_ARP_L3MC_STICKY_L3_ARP_IPMC_STICKY, "ARP_IPMC_STICKY");
    }

    for (i = 0; i < VTSS_RLEG_STAT_CNT; i++) {
        if ((i < VTSS_RLEG_CNT && vtss_state->l3.rleg_conf[i].vlan == 0 && !info->full) ||
            jr2_l3_rleg_hw_stat_poll(vtss_state, i) != VTSS_RC_OK) {
            continue;
        }

        pr("RLEG %u counters:\n\n", i);
        cnt = &vtss_state->l3.statistics.interface_counter[i];
        jr2_l3_debug_cnt(pr, "ipv4_uc_packets", cnt->ipv4uc_received_frames, cnt->ipv4uc_transmitted_frames);
        jr2_l3_debug_cnt(pr, "ipv4_uc_bytes", cnt->ipv4uc_received_octets, cnt->ipv4uc_transmitted_octets);
        jr2_l3_debug_cnt(pr, "ipv6_uc_packets", cnt->ipv6uc_received_frames, cnt->ipv6uc_transmitted_frames);
        jr2_l3_debug_cnt(pr, "ipv6_uc_bytes", cnt->ipv6uc_received_octets, cnt->ipv6uc_transmitted_octets);

        jr2_l3_debug_cnt(pr, "ipv4_mc_packets", cnt->ipv4mc_received_frames, cnt->ipv4mc_transmitted_frames);
        jr2_l3_debug_cnt(pr, "ipv4_mc_bytes", cnt->ipv4mc_received_octets, cnt->ipv4mc_transmitted_octets);
        jr2_l3_debug_cnt(pr, "ipv6_mc_packets", cnt->ipv6mc_received_frames, cnt->ipv6mc_transmitted_frames);
        jr2_l3_debug_cnt(pr, "ipv6_mc_bytes", cnt->ipv6mc_received_octets, cnt->ipv6mc_transmitted_octets);
        pr("\n");
    }

    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc jr2_l3_init_counter(vtss_state_t *vtss_state, u32 idx, u32 cnt_byte, u32 event_ir, u32 event_er)
{
    u32 frame_type = 1;     /* Events with no FCS errors */

    /* IRLEG counters */
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_GLOBAL_CNT_FRM_TYPE_CFG(idx),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_IRLEG_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(frame_type));
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_CFG(idx),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(cnt_byte));
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_EVENT_MASK(idx),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(1 << event_ir));

    /* ERLEG counters */
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_GLOBAL_CNT_FRM_TYPE_CFG(idx),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ERLEG_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(frame_type));
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_CFG(idx),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(cnt_byte));
    JR2_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_EVENT_MASK(idx),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(1 << event_er));

    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_init(vtss_state_t *vtss_state)
{
    u32 mask;

    VTSS_RC(jr2_l3_init_counter(vtss_state, JR2_L3_CNT_IP_UC_PACKETS, 0, 3, 1));
    VTSS_RC(jr2_l3_init_counter(vtss_state, JR2_L3_CNT_IP_UC_BYTES,   1, 3, 1));
    VTSS_RC(jr2_l3_init_counter(vtss_state, JR2_L3_CNT_IP_MC_PACKETS, 0, 4, 2));
    VTSS_RC(jr2_l3_init_counter(vtss_state, JR2_L3_CNT_IP_MC_BYTES,   1, 4, 2));

    mask = (VTSS_M_ANA_L3_COMMON_ROUTING_CFG_CPU_RLEG_IP_HDR_FAIL_REDIR_ENA |
            VTSS_M_ANA_L3_COMMON_ROUTING_CFG_CPU_IP6_HOPBYHOP_REDIR_ENA |
            VTSS_M_ANA_L3_COMMON_ROUTING_CFG_CPU_IP4_OPTIONS_REDIR_ENA);
    JR2_WRM(VTSS_ANA_L3_COMMON_ROUTING_CFG, mask, mask);
#if defined(JR2_L3_INGRESS_MAC_UPDATE)
    JR2_WRM_SET(VTSS_ANA_L3_COMMON_ROUTING_CFG,
                VTSS_M_ANA_L3_COMMON_ROUTING_CFG_RT_SMAC_UPDATE_ENA);
    JR2_WRM(VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL,
            VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_SEL(1),
            VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_SEL);
#endif

    return VTSS_RC_OK;
}

static vtss_rc jr2_l3_poll(vtss_state_t *vtss_state)
{
    /* Poll counters for one router leg every second to avoid counter wrapping.
       The worst case is a 40-bit byte counter, which would wrap in about 900 seconds at 10 Gbps */
    VTSS_RC(jr2_l3_rleg_hw_stat_poll(vtss_state, vtss_state->l3.statistics.rleg));
    vtss_state->l3.statistics.rleg++;
    if (vtss_state->l3.statistics.rleg >= VTSS_RLEG_STAT_CNT) {
        vtss_state->l3.statistics.rleg = 0;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_l3_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_l3_state_t *state = &vtss_state->l3;
    
    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->common_set = jr2_l3_common_set;
        state->rleg_counters_get = jr2_l3_rleg_hw_stat_poll;
        state->rleg_counters_reset = jr2_l3_rleg_stat_reset;
        state->rleg_set = jr2_l3_rleg_set;
        state->vlan_set = jr2_l3_vlan_set;
        state->rt_add = jr2_l3_rt_add;
        state->rt_del = jr2_l3_rt_del;
        state->mc_rt_add = jr2_l3_mc_rt_add;
        state->mc_rt_del = jr2_l3_mc_rt_del;
        state->mc_rt_rleg_add = jr2_l3_mc_rt_rleg_add;
        state->arp_set = jr2_l3_arp_set;
        state->debug_sticky_clear = jr2_l3_debug_sticky_clear;
        vtss_l3_integrity_update(vtss_state);
        break;
    case VTSS_INIT_CMD_INIT:
        vtss_l3_integrity_check(vtss_state, __FILE__, __LINE__);
        VTSS_RC(jr2_l3_init(vtss_state));
        vtss_l3_integrity_update(vtss_state);
        break;
    case VTSS_INIT_CMD_POLL:
        vtss_l3_integrity_check(vtss_state, __FILE__, __LINE__);
        VTSS_RC(jr2_l3_poll(vtss_state));
        vtss_l3_integrity_update(vtss_state);
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_JAGUAR_2 && VTSS_FEATURE_LAYER3 */
