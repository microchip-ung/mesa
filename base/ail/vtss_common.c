// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"
#include "vtss_util.h" // For VTSS_ENCODE_BITFIELD

/* Default mapping of PCP to QoS Class */
/* Can also be used for default mapping of QoS class to PCP */
/* This is the IEEE802.1Q-2011 recommended priority to traffic class mappings */
u32 vtss_cmn_pcp2qos(u32 pcp)
{
    u32 ret;
    switch (pcp) {
    case 0U: ret = 1U; break;
    case 1U: ret = 0U; break;
    case 2U:
    case 3U:
    case 4U:
    case 5U:
    case 6U:
    case 7U: ret = pcp; break;
    default:
        VTSS_E("Invalid PCP (%u)", pcp);
        ret = 0;
        break;
    }
    return ret;
}

const char *vtss_func;

vtss_rc vtss_port_no_check(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    if (port_no >= vtss_state->port_count) {
        VTSS_E("%s: illegal port_no: %u.  port_count: %u", vtss_func ? vtss_func : "?", port_no,
               vtss_state->port_count);
        return VTSS_RC_ERROR;
    }

#if defined(VTSS_FEATURE_PORT_CONTROL)
    /* Set currently selected device using port map */
    VTSS_SELECT_CHIP_PORT_NO(port_no);
#endif /* VTSS_FEATURE_PORT_CONTROL */

    return VTSS_RC_OK;
}

vtss_rc vtss_port_no_none_check(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return (port_no == VTSS_PORT_NO_NONE ? VTSS_RC_OK : vtss_port_no_check(vtss_state, port_no));
}

vtss_rc vtss_cmn_restart_update(vtss_state_t *vtss_state, u32 value)
{
    vtss_init_conf_t *conf = &vtss_state->init_conf;
    u32               bitfield;

    /* Return if restart has already been updated */
    if (vtss_state->restart_updated) {
        return VTSS_RC_OK;
    }
    vtss_state->restart_updated = TRUE;

    bitfield = VTSS_EXTRACT_BITFIELD(value, VTSS_RESTART_TYPE_OFFSET, VTSS_RESTART_TYPE_WIDTH);
    vtss_state->restart_prev = (bitfield == 0U)   ? VTSS_RESTART_COLD
                               : (bitfield == 1U) ? VTSS_RESTART_COOL
                                                  : VTSS_RESTART_WARM;
    vtss_state->version_prev =
        (u16)VTSS_EXTRACT_BITFIELD(value, VTSS_RESTART_VERSION_OFFSET, VTSS_RESTART_VERSION_WIDTH);
    vtss_state->restart_cur = vtss_state->restart_prev;
    vtss_state->version_cur = VTSS_API_VERSION;
    switch (vtss_state->restart_cur) {
    case VTSS_RESTART_COLD: VTSS_I("cold start detected"); break;
    case VTSS_RESTART_COOL: VTSS_I("cool start detected"); break;
    case VTSS_RESTART_WARM:
        VTSS_I("warm start detected");
        if (conf->warm_start_enable) {
            if (vtss_state->version_prev > vtss_state->version_cur) {
                VTSS_I("downgrade from version %u to %u", vtss_state->version_prev,
                       vtss_state->version_cur);
            } else {
                vtss_state->warm_start_cur = TRUE;
                VTSS_I("warm starting");
                return VTSS_RC_OK;
            }
        } else {
            VTSS_I("warm start disabled");
        }
        /* Fall back to cool start */
        vtss_state->restart_cur = VTSS_RESTART_COOL;
        vtss_state->restart_prev = VTSS_RESTART_COOL;
        break;
    default: VTSS_I("unknown restart type"); break;
    }
    return VTSS_RC_OK;
}

u32 vtss_cmn_restart_value_get(vtss_state_t *vtss_state)
{
    return (VTSS_ENCODE_BITFIELD(vtss_state->restart_cur, VTSS_RESTART_TYPE_OFFSET,
                                 VTSS_RESTART_TYPE_WIDTH) |
            VTSS_ENCODE_BITFIELD(VTSS_API_VERSION, VTSS_RESTART_VERSION_OFFSET,
                                 VTSS_RESTART_VERSION_WIDTH));
}

#if defined(VTSS_FEATURE_PORT_CONTROL) || defined(VTSS_ARCH_OCELOT)
/* Rebase 64-bit counter, i.e. discard changes since last update, based on 8-bit
 * chip counter */
void vtss_cmn_counter_8_rebase(u8 new_base_value, vtss_chip_counter_t *counter)
{
    counter->prev = new_base_value;
}

/* Clear/increment 64-bit counter based on 8 bit chip counter */
void vtss_cmn_counter_8_update(u8 value, vtss_chip_counter_t *counter, BOOL clear)
{
    u64 add = 0, new = value;

    if (clear) {
        /* Clear counter */
        counter->value = 0;
    } else {
        /* Accumulate counter */
        if (new < counter->prev) {
            add = (1ULL << 8U); /* Wrapped */
        }
        counter->value += (new + add - counter->prev);
    }
    counter->prev = new;
}

/* Rebase 64-bit counter, i.e. discard changes since last update, based on
 * 16-bit chip counter */
void vtss_cmn_counter_16_rebase(u16 new_base_value, vtss_chip_counter_t *counter)
{
    counter->prev = new_base_value;
}

/* Clear/increment 64-bit counter based on 16 bit chip counter */
void vtss_cmn_counter_16_update(u16 value, vtss_chip_counter_t *counter, BOOL clear)
{
    u64 add = 0, new = value;

    if (clear) {
        /* Clear counter */
        counter->value = 0;
    } else {
        /* Accumulate counter */
        if (new < counter->prev) {
            add = (1ULL << 16U); /* Wrapped */
        }
        counter->value += (new + add - counter->prev);
    }
    counter->prev = new;
}

/* Rebase 64-bit counter, i.e. discard changes since last update, based on
 * 32-bit chip counter */
void vtss_cmn_counter_32_rebase(u32 new_base_value, vtss_chip_counter_t *counter)
{
    counter->prev = new_base_value;
}

/* Clear/increment 64-bit counter based on 32 bit chip counter */
void vtss_cmn_counter_32_update(u32 value, vtss_chip_counter_t *counter, BOOL clear)
{
    vtss_cmn_counter_32_cmd(value, counter,
                            clear ? VTSS_COUNTER_CMD_CLEAR : VTSS_COUNTER_CMD_UPDATE);
}

void vtss_cmn_counter_32_cmd(u32 value, vtss_chip_counter_t *counter, vtss_counter_cmd_t cmd)
{
    u64 add = 0, new = value;

    switch (cmd) {
    case VTSS_COUNTER_CMD_CLEAR:
        /* Clear counter */
        counter->value = 0;
        break;
    case VTSS_COUNTER_CMD_UPDATE:
        /* Accumulate counter */
        if (new < counter->prev) {
            add = (1ULL << 32U); /* Wrapped */
        }
        counter->value += (new + add - counter->prev);
        break;
    default:
        /* Counter rebase - do nothing */
        break;
    }
    counter->prev = new;
}

void vtss_cmn_counter_dual_cmd(u32                  emac,
                               u32                  pmac,
                               vtss_dual_counter_t *counter,
                               vtss_counter_cmd_t   cmd)
{
    u64 add = 0;

    switch (cmd) {
    case VTSS_COUNTER_CMD_CLEAR:
        /* Clear counter */
        counter->value = 0;
        break;
    case VTSS_COUNTER_CMD_UPDATE:
        /* Accumulate EMAC/PMAC counter */
        add += emac;
        add += (emac < counter->emac ? (1ULL << 32U) : 0ULL);
        add -= counter->emac;
        add += pmac;
        add += (pmac < counter->pmac ? (1ULL << 32U) : 0ULL);
        add -= counter->pmac;
        counter->value += add;
        break;
    default:
        /* Counter rebase - do nothing */
        break;
    }
    counter->emac = emac;
    counter->pmac = pmac;
}

/* Rebase 64-bit counter, i.e. discard changes since last update, based on
 * 40-bit chip counter */
void vtss_cmn_counter_40_rebase(u32 new_lsb, u32 new_msb, vtss_chip_counter_t *counter)
{
    counter->prev = new_msb;
    counter->prev = ((counter->prev << 32U) + new_lsb);
}

/* Clear/increment 64-bit counter based on 40 bit chip counter */
void vtss_cmn_counter_40_update(u32 lsb, u32 msb, vtss_chip_counter_t *counter, BOOL clear)
{
    u64 add = 0, new = msb;

    new = ((new << 32U) + lsb);
    if (clear) {
        /* Clear counter */
        counter->value = 0;
    } else {
        /* Accumulate counter */
        if (new < counter->prev) {
            add = (1ULL << 40U); /* Wrapped */
        }
        counter->value += (new + add - counter->prev);
    }
    counter->prev = new;
}

const char *vtss_serdes_mode_txt(vtss_serdes_mode_t mode)
{
    return (mode == VTSS_SERDES_MODE_DISABLE     ? "DISABLE"
            : mode == VTSS_SERDES_MODE_XAUI_12G  ? "XAUI_12G"
            : mode == VTSS_SERDES_MODE_XAUI      ? "XAUI"
            : mode == VTSS_SERDES_MODE_RXAUI_12G ? "RXAUI_12G"
            : mode == VTSS_SERDES_MODE_RXAUI     ? "RXAUI"
            : mode == VTSS_SERDES_MODE_2G5       ? "2G5"
            : mode == VTSS_SERDES_MODE_QSGMII    ? "QSGMII"
            : mode == VTSS_SERDES_MODE_SGMII     ? "SGMII"
            : mode == VTSS_SERDES_MODE_100FX     ? "100FX"
            : mode == VTSS_SERDES_MODE_1000BaseX ? "1000BX"
                                                 : "?");
}
#endif
#if defined(VTSS_FEATURE_CORE_CLOCK)
static const char *vtss_core_freq_to_txt(vtss_core_clock_freq_t freq)
{
    return (freq == VTSS_CORE_CLOCK_180MHZ   ? "180MHZ"
            : freq == VTSS_CORE_CLOCK_250MHZ ? "250MHZ"
            : freq == VTSS_CORE_CLOCK_328MHZ ? "328MHZ"
            : freq == VTSS_CORE_CLOCK_500MHZ ? "500MHZ"
            : freq == VTSS_CORE_CLOCK_625MHZ ? "625MHZ"
                                             : "?");
}

static const char *vtss_ref_freq_to_txt(vtss_core_ref_clk_t freq)
{
    return (freq == VTSS_CORE_REF_CLK_25MHZ   ? "25MHZ"
            : freq == VTSS_CORE_REF_CLK_39MHZ ? "39MHZ"
                                              : "-");
}
#endif
/* ================================================================= *
 *  Debug print
 * ================================================================= */

const char *vtss_bool_txt(BOOL enabled) { return (enabled ? "Enabled" : "Disabled"); }

char *vtss_mac_txt(vtss_mac_t *mac)
{
    static char   str[18];
    u8           *p = mac->addr;
    lmu_fmt_buf_t buf;

    VTSS_FMT(buf, "%02x-%02x-%02x-%02x-%02x-%02x", p[0], p[1], p[2], p[3], p[4], p[5]);
    lmu_czstrcpy(str, buf.s);
    return str;
}

void vtss_debug_print_header_underlined(lmu_ss_t *ss, const char *header, BOOL layer)
{
    u64 i, len = VTSS_STRLEN(header);

    pr("%s\n", header);
    for (i = 0U; i < len; i++) {
        pr(layer ? "=" : "-");
    }
    pr("\n\n");
}

void vtss_debug_print_header(lmu_ss_t *ss, const char *header) { pr("%s:\n\n", header); }

static const char *const vtss_debug_group_name[VTSS_DEBUG_GROUP_COUNT] = {
    [VTSS_DEBUG_GROUP_ALL] = "All", /**< All groups */
    [VTSS_DEBUG_GROUP_INIT] = "Initialization",
    [VTSS_DEBUG_GROUP_MISC] = "Miscellaneous",
    [VTSS_DEBUG_GROUP_PORT] = "Port",
    [VTSS_DEBUG_GROUP_PORT_CNT] = "Port Counters",
    [VTSS_DEBUG_GROUP_PHY] = "PHY",
    [VTSS_DEBUG_GROUP_VLAN] = "VLAN",
    [VTSS_DEBUG_GROUP_PVLAN] = "PVLAN",
    [VTSS_DEBUG_GROUP_MAC_TABLE] = "MAC Table",
    [VTSS_DEBUG_GROUP_ACL] = "ACL",
    [VTSS_DEBUG_GROUP_QOS] = "QoS",
    [VTSS_DEBUG_GROUP_HQOS] = "HQoS",
    [VTSS_DEBUG_GROUP_AGGR] = "Aggregation",
    [VTSS_DEBUG_GROUP_GLAG] = "Global aggregation",
    [VTSS_DEBUG_GROUP_STP] = "Spanning Tree",
    [VTSS_DEBUG_GROUP_MIRROR] = "Mirroring",
    [VTSS_DEBUG_GROUP_EVC] = "EVC",
    [VTSS_DEBUG_GROUP_ERPS] = "ERPS",
    [VTSS_DEBUG_GROUP_EPS] = "EPS",
    [VTSS_DEBUG_GROUP_SR] = "Seamless Redundancy",
    [VTSS_DEBUG_GROUP_REDBOX] = "RedBox",
    [VTSS_DEBUG_GROUP_PACKET] = "Packet",
    [VTSS_DEBUG_GROUP_FDMA] = "FDMA (obsoleted)",
    [VTSS_DEBUG_GROUP_TS] = "Timestamping",
    [VTSS_DEBUG_GROUP_WM] = "Watermarks",
    [VTSS_DEBUG_GROUP_LRN] = "LRN:COMMON (DEPRECATED)",
    [VTSS_DEBUG_GROUP_IPMC] = "IP Multicast",
    [VTSS_DEBUG_GROUP_STACK] = "Stacking",
    [VTSS_DEBUG_GROUP_CMEF] = "Congestion Management",
    [VTSS_DEBUG_GROUP_HOST] = "Host Configuration",
#if defined(VTSS_FEATURE_MPLS)
    [VTSS_DEBUG_GROUP_MPLS] = "MPLS",
#endif
#if defined(VTSS_FEATURE_HW_PROT)
    [VTSS_DEBUG_GROUP_HW_PROT] = "HW Protection",
#endif
    [VTSS_DEBUG_GROUP_VXLAT] = "VLAN Translation",
    [VTSS_DEBUG_GROUP_SER_GPIO] = "Serial GPIO",
#if defined(VTSS_FEATURE_VOP)
    [VTSS_DEBUG_GROUP_OAM] = "OAM",
#endif
#if defined(VTSS_FEATURE_MRP)
    [VTSS_DEBUG_GROUP_MRP] = "MRP",
#endif
#if defined(VTSS_FEATURE_LAYER3)
    [VTSS_DEBUG_GROUP_L3] = "L3",
#endif /* VTSS_FEATURE_LAYER3 */
#if defined(VTSS_FEATURE_AFI_SWC)
    [VTSS_DEBUG_GROUP_AFI] = "AFI",
#endif /* VTSS_FEATURE_AFI_SWC */
    [VTSS_DEBUG_GROUP_SERDES] = "Serdes",
    [VTSS_DEBUG_GROUP_KR] = "KR",
    [VTSS_DEBUG_GROUP_MUX] = "MUX",
};

BOOL vtss_debug_group_enabled(lmu_ss_t                      *ss,
                              const vtss_debug_info_t *const info,
                              const vtss_debug_group_t       group)
{
    if (info->group == VTSS_DEBUG_GROUP_ALL || info->group == group) {
        vtss_debug_print_header_underlined(ss,
                                           (group < VTSS_DEBUG_GROUP_COUNT)
                                               ? vtss_debug_group_name[group]
                                               : "?",
                                           FALSE);
        return TRUE;
    }
    return FALSE;
}

vtss_rc vtss_debug_print_group(const vtss_debug_group_t group,
                               vtss_rc (*dbg)(vtss_state_t                  *vtss_state,
                                              lmu_ss_t                      *ss,
                                              const vtss_debug_info_t *const info),
                               vtss_state_t                  *vtss_state,
                               lmu_ss_t                      *ss,
                               const vtss_debug_info_t *const info)
{
    if (!vtss_debug_group_enabled(ss, info, group)) {
        return VTSS_RC_OK;
    }

    return dbg(vtss_state, ss, info);
}

void vtss_debug_print_sticky(lmu_ss_t *ss, const char *name, u32 value, u32 mask)
{
    pr("%-32s: %u\n", name, VTSS_BOOL((value & mask) != 0U));
}

void vtss_debug_print_value(lmu_ss_t *ss, const char *name, u32 value)
{
    pr("%-32s: %u\n", name, value);
}

void vtss_debug_print_reg_header(lmu_ss_t *ss, const char *name)
{
    pr("%-32s  31    24.23    16.15     8.7      0 Hex\n", name);
}

void vtss_debug_print_reg(lmu_ss_t *ss, const char *name, u32 value)
{
    u32 i, val, dot;

    pr("%-32s: ", name);
    for (i = 0U; i < 32U; i++) {
        val = ((value & ((u32)1U << (31U - i))) != 0U) ? 1U : 0U;
        dot = ((i == 0U) || ((i % 8U) != 0U)) ? 0U : 1U;
        pr("%s%u", (dot == 0U) ? "" : ".", val);
    }
    pr(" 0x%08x\n", value);
}

static void vtss_debug_print_init(vtss_state_t                  *vtss_state,
                                  lmu_ss_t                      *ss,
                                  const vtss_debug_info_t *const info)
{
    if (!vtss_debug_group_enabled(ss, info, VTSS_DEBUG_GROUP_INIT)) {
        return;
    }

    pr("Target     : 0x%04X\n", vtss_state->create.target);
    pr("Chip / Rev : 0x%04X / %d\n", vtss_state->misc.chip_id.part_number,
       vtss_state->misc.chip_id.revision);
#if defined(VTSS_FEATURE_PORT_MUX)
    pr("Mux mode   : 0x%04x\n", vtss_state->init_conf.mux_mode);
#endif /* VTSS_FEATURE_PORT_MUX */
#if defined(VTSS_FEATURE_CORE_CLOCK)
    pr("Core clock : %s / %s\n", vtss_core_freq_to_txt(vtss_state->init_conf.core_clock.freq),
       vtss_ref_freq_to_txt(vtss_state->init_conf.core_clock.ref_freq));
#endif /* VTSS_FEATURE_PORT_MUX */
    pr("VTSS_PORTS : %d\n", VTSS_PORTS);
    pr("State Size : %zu\n", sizeof(*vtss_state));
#if defined(VTSS_FEATURE_MISC)
    pr("Misc Size  : %zu\n", sizeof(vtss_state->misc));
#endif /* VTSS_FEATURE_MISC */
#if defined(VTSS_FEATURE_PORT_CONTROL)
    pr("Port Size  : %zu\n", sizeof(vtss_state->port));
#endif /* VTSS_FEATURE_PORT_CONTROL */
#if defined(VTSS_FEATURE_QOS)
    pr("QoS Size   : %zu\n", sizeof(vtss_state->qos));
#endif /* VTSS_FEATURE_QOS */
#if defined(VTSS_FEATURE_PACKET)
    pr("Packet Size: %zu\n", sizeof(vtss_state->packet));
#endif /* VTSS_FEATURE_PACKET */
#if defined(VTSS_FEATURE_LAYER2)
    pr("L2 Size    : %zu\n", sizeof(vtss_state->l2));
#endif /* VTSS_FEATURE_LAYER2 */
#if defined(VTSS_FEATURE_LAYER3)
    pr("L3 Size    : %zu\n", sizeof(vtss_state->l3));
#endif /* VTSS_FEATURE_LAYER3 */
#if defined(VTSS_FEATURE_VCAP)
    pr("VCAP Size  : %zu\n", sizeof(vtss_state->vcap));
#endif /* VTSS_FEATURE_VCAP */
#if defined(VTSS_FEATURE_TIMESTAMP)
    pr("TS Size    : %zu\n", sizeof(vtss_state->ts));
#endif /* VTSS_FEATURE_TIMESTAMP */
#if defined(VTSS_FEATURE_CLOCK)
    pr("Clock Size : %zu\n", sizeof(vtss_state->clock));
#endif /* VTSS_FEATURE_CLOCK */
#if defined(VTSS_FEATURE_VOP)
    pr("OAM Size   : %zu\n", sizeof(vtss_state->oam));
#endif /* VTSS_FEATURE_VOP */
#if defined(VTSS_FEATURE_MRP)
    pr("MRP Size   : %zu\n", sizeof(vtss_state->mrp));
#endif /* VTSS_FEATURE_VOP */
#if defined(VTSS_FEATURE_SYNCE)
    pr("SyncE Size : %zu\n", sizeof(vtss_state->synce));
#endif /* VTSS_FEATURE_SYNCE */
#if defined(VTSS_FEATURE_FAN)
    pr("Fan Size   : %zu\n", sizeof(vtss_state->fan));
#endif /* VTSS_FEATURE_FAN */
#if defined(VTSS_FEATURE_EEE)
    pr("EEE Size   : %zu\n", sizeof(vtss_state->eee));
#endif /* VTSS_FEATURE_EEE */
#if defined(VTSS_AFI_V2)
    pr("AFI Size   : %zu\n", sizeof(vtss_state->afi));
#endif
    pr("\n");
}

/* Print port header, e.g, "0      7.8     15.16    23.24  28" */
void vtss_debug_print_port_header(vtss_state_t *vtss_state,
                                  lmu_ss_t     *ss,
                                  const char   *txt,
                                  u32           count,
                                  BOOL          nl)
{
    u32 i, port;

    if (count == 0U) {
        count = vtss_state->port_count;
    }
    if (txt != NULL) {
        pr("%s", txt);
    }
    for (port = 0U; port < count; port++) {
        i = (port & 7U);
        if (i == 0U || i == 7U || (port == (count - 1U) && i > 2U)) {
            pr("%s%u", port != 0 && i == 0 ? "." : "", port);
        } else {
            if (port < 10U || i > 2U) {
                pr(" ");
            }
        }
    }
    if (nl) {
        pr("\n");
    }
}

void vtss_debug_print_ports(vtss_state_t *vtss_state, lmu_ss_t *ss, u8 *member, BOOL nl)
{
    vtss_port_no_t port_no;
    u32            val, dot;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        val = (VTSS_PORT_BF_GET(member, port_no) != 0U) ? 1U : 0U;
        dot = ((port_no == 0U) || ((port_no & 7U) != 0U)) ? 0U : 1U;
        pr("%s%s", (dot == 0) ? "" : ".", (val != 0) ? "1" : "0");
    }
    if (nl) {
        pr("\n");
    }
}

void vtss_debug_print_port_members(vtss_state_t *vtss_state,
                                   lmu_ss_t     *ss,
                                   BOOL          port_member[VTSS_PORT_ARRAY_SIZE],
                                   BOOL          nl)
{
    vtss_port_no_t port_no;
    u8             member[VTSS_PORT_BF_SIZE];

    VTSS_PORT_BF_CLR(member);
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_PORT_BF_SET(member, port_no, (port_member[port_no] == TRUE));
    }
    vtss_debug_print_ports(vtss_state, ss, member, nl);
}

#if defined(VTSS_FEATURE_AFI_SWC)
static void vtss_debug_print_afi(vtss_state_t                  *vtss_state,
                                 lmu_ss_t                      *ss,
                                 const vtss_debug_info_t *const info)
{
#if defined(VTSS_AFI_V1)
    u32 slot, cnt = 0;

    if (!vtss_debug_group_enabled(ss, info, VTSS_DEBUG_GROUP_AFI)) {
        return;
    }

    // Print the DCB layout of the frames that are currently being injected.
    pr("Automatic Frame Injector\n");
    pr("ID   State    Frames/sec Port Timer\n");
    pr("---- -------- ---------- ---- -----\n");

    for (slot = 0; slot < VTSS_ARRSZ(vtss_state->afi.slots); slot++) {
        vtss_afi_slot_conf_t  *slot_conf = &vtss_state->afi.slots[slot];
        vtss_afi_timer_conf_t *timer_conf;

        if (slot_conf->state == VTSS_AFI_SLOT_STATE_FREE) {
            continue;
        }

        cnt++;
        timer_conf = &vtss_state->afi.timers[slot_conf->timer_idx];

        pr("%4u %-8s %10u %4u %5u\n", slot,
           slot_conf->state == VTSS_AFI_SLOT_STATE_RESERVED  ? "Reserved"
           : slot_conf->state == VTSS_AFI_SLOT_STATE_ENABLED ? "Enabled"
           : slot_conf->state == VTSS_AFI_SLOT_STATE_PAUSED  ? "Paused"
                                                             : "Unknown",
           timer_conf->fps, slot_conf->port_no, slot_conf->timer_idx);
    }

    if (cnt == 0) {
        pr("<none>\n");
    }
    pr("\n");
#endif
}
#endif

/* Print Application Interface Layer state */
static vtss_rc vtss_debug_ail_print(vtss_state_t                  *vtss_state,
                                    lmu_ss_t                      *ss,
                                    const vtss_debug_info_t *const info)
{
    if (info->layer != VTSS_DEBUG_LAYER_ALL && info->layer != VTSS_DEBUG_LAYER_AIL) {
        return VTSS_RC_OK;
    }

    vtss_debug_print_header_underlined(ss, "Application Interface Layer", TRUE);

    vtss_debug_print_init(vtss_state, ss, info);

#if defined(VTSS_FEATURE_MISC)
    vtss_misc_debug_print(vtss_state, ss, info);
#endif /* VTSS_FEATURE_MISC */

#if defined(VTSS_FEATURE_PORT_CONTROL)
    vtss_port_debug_print(vtss_state, ss, info);
#endif /* VTSS_FEATURE_PORT_CONTROL */

#if defined(VTSS_FEATURE_LAYER2)
    vtss_l2_debug_print(vtss_state, ss, info);
#endif /* VTSS_FEATURE_LAYER2 */

#if defined(VTSS_FEATURE_VCAP)
    vtss_vcap_debug_print_acl(vtss_state, ss, info);
#endif /* VTSS_FEATURE_VCAP */

#if defined(VTSS_FEATURE_QOS)
    vtss_qos_debug_print(vtss_state, ss, info);
#endif /* VTSS_FEATURE_QOS */

#if defined(VTSS_FEATURE_HQOS)
    vtss_hqos_debug_print(vtss_state, ss, info);
#endif /* VTSS_FEATURE_HQOS */

#if defined(VTSS_FEATURE_EVC_POLICERS)
    if (vtss_debug_group_enabled(ss, info, VTSS_DEBUG_GROUP_EVC)) {
        vtss_qos_debug_print_dlb(vtss_state, ss, info);
    }
#endif

#if defined(VTSS_FEATURE_PACKET)
    vtss_packet_debug_print(vtss_state, ss, info);
#endif /* VTSS_FEATURE_PACKET */

#if defined(VTSS_AFI_V2)
    vtss_afi_debug_print(vtss_state, ss, info);
#endif /* VTSS_AFI_V2 */

#if defined(VTSS_FEATURE_TIMESTAMP)
    vtss_ts_debug_print(vtss_state, ss, info);
#endif /* VTSS_FEATURE_TIMESTAMP */

#if defined(VTSS_FEATURE_VOP)
    vtss_oam_debug_print(vtss_state, ss, info);
#endif

#if defined(VTSS_FEATURE_MRP)
    vtss_mrp_debug_print(vtss_state, ss, info);
#endif

#if defined(VTSS_FEATURE_LAYER3)
    if (vtss_debug_group_enabled(ss, info, VTSS_DEBUG_GROUP_L3)) {
        vtss_debug_print_l3(vtss_state, ss, info);
    }
#endif /* VTSS_FEATURE_LAYER3 */

#if defined(VTSS_FEATURE_AFI_SWC)
    vtss_debug_print_afi(vtss_state, ss, info);
#endif

    return VTSS_RC_OK;
}

/* Print Chip Interface Layer state */
static vtss_rc vtss_debug_cil_print(vtss_state_t                  *vtss_state,
                                    lmu_ss_t                      *ss,
                                    const vtss_debug_info_t *const info)
{
    vtss_rc        rc = VTSS_RC_OK;
    lmu_fmt_buf_t  buf;
    vtss_chip_no_t chip_no;

    if (info->layer != VTSS_DEBUG_LAYER_ALL && info->layer != VTSS_DEBUG_LAYER_CIL) {
        return VTSS_RC_OK;
    }

    /* Print CIL information for all devices */
    for (chip_no = 0U; chip_no < vtss_state->chip_count; chip_no++) {
        if (info->chip_no != VTSS_CHIP_NO_ALL && chip_no != info->chip_no) {
            continue;
        }
        VTSS_SELECT_CHIP(chip_no);
        VTSS_FMT(buf, "Chip Interface Layer[%u]", chip_no);
        vtss_debug_print_header_underlined(ss, buf.s, TRUE);
        rc = vtss_cil_debug_info_print(vtss_state, ss, info);
    }
    return rc;
}

vtss_rc vtss_cmn_debug_info_print(vtss_state_t                  *vtss_state,
                                  lmu_ss_t                      *ss,
                                  const vtss_debug_info_t *const info)
{
    VTSS_RC(vtss_debug_ail_print(vtss_state, ss, info));
    return vtss_debug_cil_print(vtss_state, ss, info);
}

vtss_rc vtss_cmn_bit_from_one_hot_mask64(u64 mask, u32 *bit_pos)
{
    u32 msw = (u32)(mask >> 32U), lsw = (u32)mask;

    // Exactly one bit must be set in #mask.
    if ((msw == 0U && lsw == 0U) || (msw != 0U && lsw != 0U)) {
        // Either both are 0 or both are non-zero, hence can't be a one-hot.
        goto err;
    }

    if (msw == 0U) {
        *bit_pos = (u32)VTSS_OS_CTZ(lsw);
        lsw &= ~VTSS_BIT(*bit_pos);
        if (lsw != 0U) {
            // Two or more bits set in lsw
            goto err;
        }
    } else {
        *bit_pos = (u32)VTSS_OS_CTZ(msw);
        msw &= ~VTSS_BIT(*bit_pos);
        if (msw != 0U) {
            // Two or more bits set in msw
            goto err;
        }
        *bit_pos += 32U;
    }
    return VTSS_RC_OK;

err:
    VTSS_E("0x%" PRIx64 " is not a one-hot mask", mask);
    return VTSS_RC_ERROR;
}
