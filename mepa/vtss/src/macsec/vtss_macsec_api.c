// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// Avoid "vtss_api.h not used in module vtss_macsec_api.c"
/*lint --e{766} */
#include "vtss_phy_api.h"

#if defined(VTSS_FEATURE_MACSEC)

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_MACSEC // Must come before #include "vtss_state.h"
#include "../common/vtss_phy_common.h"
#if defined (VTSS_OPT_PHY_TIMESTAMP)
#include "../ts/vtss_phy_ts.h"
#endif /* VTSS_OPT_PHY_TIMESTAMP */
#include "../phy_10g/chips/malibu/vtss_malibu_regs.h"
#define MACSEC_INGR              0x0000
#define MACSEC_EGR               0x8000
#define FC_BUFFER                0xF000
#define HOST_MAC                 0xF100
#define LINE_MAC                 0xF200
#define PROC_ID_0                0x9000
#define PROC_ID_2                0x9200
#define MACSEC_10G_INGR_LATENCY  60
#define MACSEC_10G_EGR_LATENCY   56
#define MACSEC_1G_INGR_LATENCY   57
#define MACSEC_1G_EGR_LATENCY    40
#define MACSEC_NOT_IN_USE        0xFFFF
#define MACSEC_SECY_NONE         0xFFFF
#define MACSEC_ENABLE            1
#define MACSEC_DISABLE           0
#define INGRESS                  0
#define EGRESS                   1
#define MACSEC_REVB_REPLAY_WINDOW_SIZE 0x40000000
#define VTSS_MACSEC_FIFO_OVERFLOW_WORKAROUND 1

#define VTSS_MACSEC_ASSERT(x,_txt) if((x)) { VTSS_E("%s",_txt); return VTSS_RC_ERROR;}
#define PST_DIR(front,egr,back) (egr ? front##_MACSEC_EGR_##back : front##_MACSEC_INGR_##back)
#define MACSEC_BS(x) ((x>>8 & 0x00FF) | (x<<8 & 0xFF00))
#if defined(VTSS_IOREG)
#undef VTSS_IOREG
#endif

#define VTSS_IOREG(dev, is32, off)  _ioreg(&vtss_state->io_var, (dev), (is32), (off))

#define MACADDRESS_FMT "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
#define MACADDRESS_ARG(X) (X).addr[0], (X).addr[1], (X).addr[2], \
                          (X).addr[3], (X).addr[4], (X).addr[5]
#define SCI_FMT MACADDRESS_FMT"#%u"
#define SCI_ARG(X) MACADDRESS_ARG((X).mac_addr), (X).port_id
#define MACSEC_PORT_FMT "%u/%u/%u"
#define MACSEC_PORT_ARG(X) (X)->port_no, (X)->service_id, (X)->port_id

#define MPORT_SCI_AN_FMT "Port: "MACSEC_PORT_FMT", SCI: "SCI_FMT", an:%u"
#define MPORT_SCI_AN_ARG(P, S, A) MACSEC_PORT_ARG((&P)), SCI_ARG(S), A

#define MPORT_SCI_FMT "Port: "MACSEC_PORT_FMT", SCI: "SCI_FMT
#define MPORT_SCI_ARG(P, S) MACSEC_PORT_ARG((&P)), SCI_ARG(S)

#define MPORT_AN_FMT "Port: "MACSEC_PORT_FMT", an:%u"
#define MPORT_AN_ARG(P, A) MACSEC_PORT_ARG((&P)), A

#define MPORT_FMT "Port: "MACSEC_PORT_FMT
#define MPORT_ARG(P) MACSEC_PORT_ARG((&P))


#define BOOL_ARG(X) (X) ? "TRUE":"FALSE"

#define MACSEC_RX_SC_CONF_FMT                            \
    "{validate_frames:%u, replay_protect:%s, "           \
    "replay_window:%u, confidentiality_offset:%u}"

#define MACSEC_RX_SC_CONF_ARG(X)                         \
    (X)->validate_frames, BOOL_ARG((X)->replay_protect), \
    (X)->replay_window, (X)->confidentiality_offset

#define MACSEC_PORT_STATUS_FMT \
    "{mac_enabled:%s, mac_operational:%s, oper_point_to_point_mac:%s}"

#define MACSEC_PORT_STATUS_ARG(X)             \
    BOOL_ARG((X).mac_enabled),                \
    BOOL_ARG((X).mac_operational),            \
    BOOL_ARG((X).oper_point_to_point_mac)

#define MACSEC_SECY_PORT_STATUS_FMT           \
    "{controlled:"MACSEC_PORT_STATUS_FMT      \
    ", uncontrolled:"MACSEC_PORT_STATUS_FMT   \
    ", common:"MACSEC_PORT_STATUS_FMT"}"

#define MACSEC_SECY_PORT_STATUS_ARG(X)        \
    MACSEC_PORT_STATUS_ARG((X).controlled),   \
    MACSEC_PORT_STATUS_ARG((X).uncontrolled), \
    MACSEC_PORT_STATUS_ARG((X).common)

#define MACSEC_TX_SC_CONF_FMT \
    "{protect_frames:%s, always_include_sci:%s, use_es:%s, use_scb:%s, " \
    "confidentiality_offset:%u}"

#define MACSEC_TX_SC_CONF_ARG(X) \
    BOOL_ARG((X).protect_frames), \
    BOOL_ARG((X).always_include_sci), \
    BOOL_ARG((X).use_es), \
    BOOL_ARG((X).use_scb), \
    (X).confidentiality_offset

#define MACSEC_TX_SC_STATUS_FMT \
    "{sci:"SCI_FMT", transmitting:%s, encoding_sa:%u, enciphering_sa:%u, " \
    "created_time:%u, started_time:%u, stopped_time:%u}"


#define MACSEC_TX_SC_STATUS_ARG(X)    \
    SCI_ARG((X).sci),                 \
    BOOL_ARG((X).transmitting),       \
    (X).encoding_sa,                  \
    (X).enciphering_sa,               \
    (X).created_time,                 \
    (X).started_time,                 \
    (X).stopped_time

#define MACSEC_RX_SA_STATUS_FMT                                                \
    "{in_use:%s, next_pn:%u, lowest_pn:%u, created_time:%u, started_time:%u, " \
    "stopped_time:%u}"

#define MACSEC_RX_SA_STATUS_ARG(X) \
    BOOL_ARG((X).in_use),          \
    (X).next_pn,                   \
    (X).lowest_pn,                 \
    (X).created_time,              \
    (X).started_time,              \
    (X).stopped_time

#define MACSEC_TX_SA_STATUS_FMT \
    "{in_use:%s, next_pn:%u, created_time:%u, started_time:%u, stopped_time:%u}"

#define MACSEC_TX_SA_STATUS_ARG(X) \
    BOOL_ARG((X).in_use),          \
    (X).next_pn, \
    (X).created_time, \
    (X).started_time, \
    (X).stopped_time


#define PRINTF(...)                                         \
    if (size - s > 0) {                                     \
        int res = snprintf(buf + s, size - s, __VA_ARGS__); \
        if (res >0 ) {                                      \
            s += res;                                       \
        }                                                   \
    }

// Macro for reading two 32 bits counter registers into a 64 bit software counter
#define MACSEC_CNT64_RD(port_no, reg_low, reg_up, value)        \
    {                                                           \
       ioreg_blk reg_addr = *reg_low;                           \
       vtss_rc __rc = _csr_rd_64(vtss_state, port_no, &reg_addr, reg_up, &value); \
       if (__rc != VTSS_RC_OK)                                  \
           return __rc;                                         \
    }

/* Macro for writing 64-bit number to two 32-bit registers */
#define MACSEC_CNT64_WR(port_no, reg_low, reg_up, value)        \
    {                                                           \
       ioreg_blk reg_addr = *reg_low;                           \
       vtss_rc __rc = _csr_wr_64(vtss_state, port_no, &reg_addr, reg_up, value); \
        if (__rc != VTSS_RC_OK)                                 \
            return __rc;                                        \
    }

// Old Macros for reading two 32 bits counter registers into a 64 bit software counter
/*#define MACSEC_CNT64_RD(port_no, reg_low, reg_up, cnt)  \
    {                                                   \
        u32 lower, upper;                               \
A
        CSR_RD(port_no, reg_low, &lower);               \
        CSR_RD(port_no, reg_up, &upper);                \
        VTSS_N("low:%u, up:%u", lower, upper);          \
        cnt = ((u64)upper << 32) + lower;               \
    }*/

/* Macro for writing 64-bit number to two 32-bit registers */
/*#define MACSEC_CNT64_WR(port_no, reg_low, reg_up, cnt)  \
    {                                                   \
        u32 lower, upper;                               \
        lower = (u32)cnt;                               \
        upper = (u32)(cnt >> 32);                       \
        VTSS_N("low:%u, up:%u", lower, upper);          \
        CSR_WR(port_no, reg_low, lower);                \
        CSR_WR(port_no, reg_up, upper);                 \
    }*/
#define VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK VTSS_BIT(3)
#define VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK VTSS_BIT(3)

#ifdef VTSS_CHIP_CU_PHY
#define VTSS_PHY_WARM_WR(vtss_state, port_no, page_addr, value) vtss_phy_wr_page(vtss_state, port_no, page_addr, value, __LINE__)
#define PHY_RD_PAGE(vtss_state, port_no, page_addr, value) vtss_phy_rd_page(vtss_state, port_no, page_addr, value, __LINE__)
#define PHY_WR_PAGE(vtss_state, port_no, page_addr, value) vtss_phy_wr_page(vtss_state, port_no, page_addr, value, __LINE__)
vtss_rc vtss_macsec_store_sa(vtss_state_t *vtss_state,
                             const vtss_port_no_t port_no, BOOL store);
#endif

#ifdef VTSS_MACSEC_FIFO_OVERFLOW_WORKAROUND
vtss_rc vtss_macsec_reconfigure(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
#endif

static vtss_rc vtss_macsec_init_set_priv(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                                         const vtss_macsec_init_t *const init);
static vtss_rc vtss_macsec_hmac_counters_get_priv(vtss_state_t                      *vtss_state,
                                                  const vtss_port_no_t              port_no,
                                                  vtss_macsec_mac_counters_t        *const counters,
                                                  const BOOL                        clear);
static vtss_rc vtss_macsec_lmac_counters_get_priv(vtss_state_t                      *vtss_state,
                                                  const vtss_port_no_t              port_no,
                                                  vtss_macsec_mac_counters_t        *const counters,
                                                  const BOOL                        clear);
static BOOL one_tx_an_in_use(vtss_macsec_internal_secy_t *secy);
static int vtss_macsec_match_pattern_to_txt(char                              *buf,
                                            int                                size,
                                            const vtss_macsec_match_pattern_t *const p)
{
    int s = 0;
    PRINTF("{priority:%u", p->priority);

    if (p->match & VTSS_MACSEC_MATCH_IS_CONTROL) {
        PRINTF(" is_control:%s", p->is_control ? "true" : "false");
    }

    if (p->match & VTSS_MACSEC_MATCH_HAS_VLAN) {
        PRINTF(" has_vlan:%s", p->has_vlan_tag ? "true" : "false");
    }

    if (p->match & VTSS_MACSEC_MATCH_HAS_VLAN_INNER) {
        PRINTF(" has_vlan_inner:%s", p->has_vlan_inner_tag ? "true" : "false");
    }

    if (p->match & VTSS_MACSEC_MATCH_ETYPE) {
        PRINTF(" etype:0x%04x", p->etype);
    }

    if (p->match & VTSS_MACSEC_MATCH_VLAN_ID) {
        PRINTF(" vlan:0x%04x", p->vid);
    }

    if (p->match & VTSS_MACSEC_MATCH_VLAN_ID_INNER) {
        PRINTF(" vlan_inner:0x%04x", p->vid_inner);
    }

    if (p->match & VTSS_MACSEC_MATCH_DISABLE) {
        PRINTF(" Disabled");
    }

    if (p->match == 0) {
        PRINTF(" Nothing");
    }

    if (p->match & VTSS_MACSEC_MATCH_BYPASS_HDR) {
        int i;

        PRINTF(" mpls_hdr:");
        for (i = 0; i < 8; ++i) {
            PRINTF(" %02x", p->hdr[i]);
        }
        PRINTF(" mpls_hdr_mask:");
        for (i = 0; i < 8; ++i) {
            PRINTF(" %02x", p->hdr_mask[i]);
        }
    }

    PRINTF("}");

    return s;
}
static int vtss_macsec_frame_match_to_txt(char                                         *buf,
                                          int                                          size,
                                          const vtss_macsec_control_frame_match_conf_t *const p)
{
    int s = 0;

    PRINTF("{");
    if (p->match & VTSS_MACSEC_MATCH_ETYPE) {
        PRINTF(" etype:0x%04x", p->etype);
    }

    if (p->match & VTSS_MACSEC_MATCH_DMAC) {
        PRINTF(" dmac:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
               p->dmac.addr[0], p->dmac.addr[1], p->dmac.addr[2], p->dmac.addr[3], p->dmac.addr[4], p->dmac.addr[5]);
    }

    PRINTF("}");

    return s;
}

#undef PRINTF


static BOOL phy_is_1g(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    BOOL                       clause45 = FALSE;
    vtss_rc __rc__ = phy_type_get(vtss_state, port_no, &clause45);
    if (__rc__ < VTSS_RC_OK) {
        VTSS_D("phy_type_get returned %x", __rc__);
    }
    return !clause45;
}

static BOOL is_reg_32(u32 dev, u32 addr)
{
    if (dev == 1) {
        if (addr >= 0xF000) {
            return 1;
        }
    } else if (dev == 3) {
        if (addr >= FC_BUFFER) {
            return 1;
        }
    } else if (dev == 30) {
        if (addr >= PROC_ID_0) {
            return 1;
        }
    } else if (dev == 31) {
        return 1;
    }
    return 0;
}

static u32 get_new_context_id(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL egr, u32 record)
{
    u32 ctxt_id = 0;
    u64 ingr_flow_map = vtss_state->macsec_conf[port_no].glb.ingr_flow_map;

    /* For egress, Set Context-id to record always. For ingress, Set the context id values
       from sets {0-63} or {64-127}. Alternate context id values between record and (record + 64). */
    if (egr) {
        ctxt_id = record;
    } else {
        ctxt_id = (ingr_flow_map & (1 << record)) > 0 ? (record + VTSS_MACSEC_10G_MAX_SA) : record;
        ingr_flow_map = ingr_flow_map ^ (1 << record);
    }
    vtss_state->macsec_conf[port_no].glb.ingr_flow_map = ingr_flow_map;

    return ctxt_id;
}
/* Update ingress flow map in vtss_state reading hardware */
static void update_flow_map_hw(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 record)
{
    u32 ctxt_id = 0;
    u64 ingr_flow_map = vtss_state->macsec_conf[port_no].glb.ingr_flow_map;

    csr_rd(vtss_state, port_no, 0x1f, 1, (0x1 | (record * 32)), &ctxt_id);

    if (ctxt_id == record) {
        ingr_flow_map = ingr_flow_map | (1 << record);
    } else {
        ingr_flow_map = ingr_flow_map & (~(1 << record));
    }
    vtss_state->macsec_conf[port_no].glb.ingr_flow_map = ingr_flow_map;
}

/* ================================================================= *
 *  Warm Start Functions
 * ================================================================= */

#define MACSEC_RC_COLD(expr) (vtss_state->sync_calling_private ? VTSS_RC_OK : (expr))
#ifdef CSR_WARM_WRM
#undef CSR_WARM_WRM
#endif
#define CSR_WARM_WRM(p, io_reg, value, mask) \
    { \
        vtss_rc __rc = _csr_warm_wrm_macsec(vtss_state, p, io_reg, value, mask, 0xFFFFFFFF, __FUNCTION__, __LINE__); \
        if (__rc != VTSS_RC_OK)                  \
            return __rc;                         \
    }

#ifdef CSR_WARM_WR
#undef CSR_WARM_WR
#endif
#define CSR_WARM_WR(p, io_reg, value)                 \
    {\
        vtss_rc __rc = _csr_warm_wr_macsec(vtss_state, p, io_reg, value, __FUNCTION__, __LINE__); \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    }

#define CSR_WARM_WRM_CHK_MASK(p, io_reg, value, mask, chk_mask)   \
    { \
        vtss_rc __rc = _csr_warm_wrm_macsec(vtss_state, p, io_reg, value, mask, chk_mask, __FUNCTION__, __LINE__); \
        if (__rc != VTSS_RC_OK)                  \
            return __rc;                         \
    }

static vtss_rc _csr_warm_wrm_macsec(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *io, u32 value,
                                    u32 mask, u32 chk_mask, const char *function, const u16 line)
{
    u32  curr_val;
    vtss_macsec_internal_glb_t *macsec = &vtss_state->macsec_conf[port_no].glb;
    if (vtss_state->sync_calling_private) {
        /* Read the current register value and compare with requested */
        VTSS_RC(csr_rd(vtss_state, port_no, io->mmd, io->is32, io->addr, &curr_val));
        if ((curr_val ^ value) & mask & chk_mask) { /* Change in bit field */
            VTSS_I("Warm start synch. field changed: Port:%u MMD:%d Register:0x%X", port_no, io->mmd, io->addr);
            VTSS_I("Mask:0x%X Chip value:0x%X API value:0x%X", mask, curr_val, value);
            VTSS_I("Function:%s, Line:%d (chk_mask:0x%X)", function, line, chk_mask);
            macsec->warm_start_reg_changed = TRUE; // Signaling that a register for this port has changed.
            VTSS_RC(csr_wrm(vtss_state, port_no, io->mmd, io->is32, io->addr, value, mask));
        }
    } else {
        /* Normal write */
        VTSS_RC(csr_wrm(vtss_state, port_no, io->mmd, io->is32, io->addr, value, mask));
    }
    return VTSS_RC_OK;
}
static vtss_rc _csr_warm_wr_macsec(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *io, u32 value, const char *function, const u16 line)
{
    return _csr_warm_wrm_macsec(vtss_state, port_no, io, value, 0xFFFFFFFF, 0xFFFFFFFF, function, line);
}
/* ================================================================= *
 *  Local functions
 * ================================================================= */
// Function for counting the number of return code errors.
// IN/OUT : vtss_state - Internal API state containing the error counters
// IN     : port_no    - The port in question for updating the counters
// IN     : rc         - The return code to count
static vtss_rc dbg_counter_incr(vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_rc rc)
{
    switch (rc) {
    case VTSS_RC_ERR_MACSEC_INVALID_SCI_MACADDR:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.invalid_sci_macaddr++;
        break;

    case VTSS_RC_ERR_MACSEC_NOT_ENABLED:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.macsec_not_enabled++;
        break;

    case VTSS_RC_ERR_MACSEC_SECY_ALREADY_IN_USE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.secy_already_in_use++;
        break;

    case VTSS_RC_ERR_MACSEC_NO_SECY_FOUND:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.no_secy_found++;
        break;

    case VTSS_RC_ERR_MACSEC_NO_SECY_VACANCY:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.no_secy_vacency++;
        break;

    case VTSS_RC_ERR_MACSEC_INVALID_VALIDATE_FRM:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.invalid_validate_frm++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_prg_sa_match++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_prg_sa_flow++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_ena_sa++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_set_sa++;
        break;

    case VTSS_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.invalid_hdr_bypass_len++;
        break;

    case VTSS_RC_ERR_MACSEC_SC_NOT_FOUND:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.sc_not_found++;
        break;

    case VTSS_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.no_ctrl_frm_match++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_set_pattern++;
        break;

    case VTSS_RC_ERR_MACSEC_TIMEOUT_ISSUE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.timeout_issue++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_empty_egress++;
        break;

    case VTSS_RC_ERR_MACSEC_AN_NOT_CREATED:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.an_not_created++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_empty_ingress++;
        break;

    case VTSS_RC_ERR_MACSEC_TX_SC_NOT_EXIST:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.tx_sc_not_exist++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_disable_sa++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_del_tx_sa++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_del_tx_sa++;
        break;

    case VTSS_RC_ERR_MACSEC_PATTERN_NOT_SET:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.pattern_not_set++;
        break;

    case VTSS_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.hw_resource_exhusted++;
        break;

    case VTSS_RC_ERR_MACSEC_SCI_ALREADY_EXISTS:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.sci_already_exist++;
        break;

    case VTSS_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.sc_resource_not_found++;
        break;

    case VTSS_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.rx_an_already_in_use++;
        break;

    case VTSS_RC_ERR_MACSEC_EMPTY_RECORD:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.empty_record++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_prg_xform++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_toggle_sa++;
        break;

    case VTSS_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.tx_an_already_in_use++;
        break;

    case VTSS_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.all_available_sa_in_use++;
        break;

    case VTSS_RC_ERR_MACSEC_MATCH_DISABLE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.match_disable++;
        break;

    case VTSS_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.all_cp_rules_in_use++;
        break;

    case VTSS_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.pattern_prio_not_valid++;
        break;

    case VTSS_RC_ERR_MACSEC_BUFFER_TOO_SMALL:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.buffer_too_small++;
        break;

    case VTSS_RC_ERR_MACSEC_FRAME_TOO_LONG:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.frm_too_long++;
        break;

    case VTSS_RC_ERR_MACSEC_FRAME_TRUNCATED:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.frm_truncated++;
        break;

    case VTSS_RC_ERR_MACSEC_PHY_POWERED_DOWN:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.phy_powered_down++;
        break;

    case VTSS_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.phy_not_macsec_capable++;
        break;

    case VTSS_RC_ERR_MACSEC_AN_NOT_EXIST:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.an_not_exist++;
        break;

    case VTSS_RC_ERR_MACSEC_NO_PATTERN_CFG:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.no_pattern_cfg++;
        break;

    case VTSS_RC_ERR_MACSEC_MAX_MTU:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.max_mtu++;
        break;

    case VTSS_RC_ERR_MACSEC_UNEXPECT_CP_MODE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.unexpected_cp_mode++;
        break;

    case VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.could_not_disable_an++;
        break;

    case VTSS_RC_ERR_MACSEC_RULE_OUT_OF_RANGE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.rule_out_of_range++;
        break;

    case VTSS_RC_ERR_MACSEC_RULE_NOT_EXIST:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.rule_not_exit++;
        break;

    case VTSS_RC_ERR_MACSEC_CSR_READ:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.csr_read++;
        break;

    case VTSS_RC_ERR_MACSEC_CSR_WRITE:
        vtss_state->macsec_conf[port_no].rc_dbg_counters.csr_write++;
        break;

    default:
        VTSS_E("Un-expect Error Return Code:%d", rc);
        vtss_state->macsec_conf[port_no].rc_dbg_counters.unknown_rc_code++;
        return VTSS_RC_ERROR;

    }
    return rc;
}


// Function for getting the RC error counters for a specific port
// IN  : vtss_state - Internal API state containing the error counters
// IN  : port_no    - The port in question for clearing the counters
// OUT : counters   - Pointer to where to put the counters.
static vtss_rc dbg_counter_get_private(const vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_macsec_rc_dbg_counters_t *counters)
{
    memcpy(counters, &vtss_state->macsec_conf[port_no].rc_dbg_counters, sizeof(vtss_macsec_rc_dbg_counters_t));
    return VTSS_RC_OK;
}

// Function for clearing the RC error counters for a specific port
// IN/OUT : vtss_state - Internal API state containing the error counters
// IN     : port_no    - The port in question for clearing the counters
static vtss_rc dbg_counter_clr(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    memset(&vtss_state->macsec_conf[port_no].rc_dbg_counters, 0, sizeof(vtss_macsec_rc_dbg_counters_t));
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_verify_port(const vtss_inst_t                inst,
                                       const vtss_port_no_t             port_no,
                                       u32                              *id)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    BOOL              phy10g;
    u32 value;

    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (!is_macsec_capable(vtss_state, port_no)) {
            return VTSS_RC_ERROR;
        }
        VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
        if (!phy10g) {
#ifdef VTSS_CHIP_CU_PHY
            if (vtss_state->phy_state[port_no].setup.mode == VTSS_PHY_MODE_POWER_DOWN) {
                return VTSS_RC_ERROR;
            }
            *id = vtss_state->phy_state[port_no].type.part_number;
#endif /* VTSS_CHIP_CU_PHY */
        } else {
#ifdef VTSS_CHIP_10G_PHY
            *id = vtss_state->phy_10g_state[port_no].type;
#endif
        }
        if (!vtss_state->macsec_conf[port_no].glb.init.enable) {
            CSR_RD(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG, &value);
            if ((VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA & value) == 0) {
                return VTSS_RC_ERROR; // Chip and API disabled
            }
        }
    }
    return rc;
}


// Return VTSS_RC if the sci is valid, else error code.
static vtss_rc is_sci_valid(vtss_state_t *vtss_state, vtss_port_no_t port_no, const vtss_macsec_sci_t *sci)
{
    vtss_mac_t boardcast = {.addr = MAC_ADDR_BROADCAST};

    // IEEE 802.1AE-2006, section 9.9 - The 64-bit value FF-FF-FF-FF-FF-FF is never used as an SCI and is reserved for use by implementations to indicate the absence of an SC or an SCI in contexts where an SC can be present */
    if (memcmp(&sci->mac_addr, &boardcast, sizeof(boardcast)) == 0) {
        VTSS_I("Broadcast MAC address should not be used");
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_INVALID_SCI_MACADDR);
    }

    return VTSS_RC_OK;
}

static BOOL sci_cmp(const vtss_macsec_sci_t *a, const vtss_macsec_sci_t *b)
{
    u32 i;

    if (b == NULL || a == NULL) {
        return FALSE;
    }

    if (a->port_id != b->port_id) {
        return FALSE;
    }

    for (i = 0; i < 6; ++i) {
        if (a->mac_addr.addr[i] != b->mac_addr.addr[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

static BOOL sci_larger(const vtss_macsec_sci_t *a, const vtss_macsec_sci_t *b)
{
    u32 i;
    if (b == NULL) {
        return TRUE;
    }
    for (i = 0; i < 6; i++) {
        if (a->mac_addr.addr[i] > b->mac_addr.addr[i]) {
            return TRUE;
        } else if (a->mac_addr.addr[i] < b->mac_addr.addr[i]) {
            return FALSE;
        }
    }
    if (a->port_id > b->port_id) {
        return TRUE;
    }
    return FALSE;
}


static void sci_cpy(vtss_macsec_sci_t *const dst, const vtss_macsec_sci_t *const src)
{
    u32 i;
    dst->port_id = src->port_id;
    for (i = 0; i < 6; ++i) {
        dst->mac_addr.addr[i] = src->mac_addr.addr[i];
    }
}

static void prnt_sak(const vtss_macsec_sak_t *const sak)
{
    u32 i, buf_used = 0, hbuf_used = 0;
    char buf[100];
    char h_buf[100];

    memset(buf, 0, sizeof(*buf) * 100);
    memset(h_buf, 0, sizeof(*h_buf) * 100);
    for (i = 0; i < sak->len; i++) {
        buf_used += sprintf(buf + buf_used, "%s%02hhx", i == 0 ? "" : ":", sak->buf[i]);
        if (i < 16) {
            hbuf_used += sprintf(h_buf + hbuf_used, "%s%02hhx", i == 0 ? "" : ":", sak->h_buf[i]);
        }
    }
    VTSS_I("buf:%s", buf);
    VTSS_I("h_buf:%s", h_buf);
}

typedef struct {
    u32 secy_id;
    u32 next_index;
} macsec_secy_in_use_iter_t;

static void macsec_secy_in_use_inter_init(macsec_secy_in_use_iter_t *in_use_inter)
{
    in_use_inter->secy_id = 0;
    in_use_inter->next_index    = 0;
}


static BOOL macsec_secy_in_use_inter_getnext(vtss_state_t        *vtss_state,
                                             const vtss_port_no_t      port_no,
                                             macsec_secy_in_use_iter_t *in_use_inter)
{
    u32 i, max_secy = VTSS_MACSEC_1G_MAX_SECY;
    vtss_macsec_internal_secy_t *secy;

    if (phy_is_1g(vtss_state, port_no)) {
        max_secy = VTSS_MACSEC_1G_MAX_SECY;
#if defined(VTSS_CHIP_10G_PHY)
    } else {
        max_secy = VTSS_MACSEC_10G_MAX_SECY;
#endif
    }

    for (i = in_use_inter->next_index; i < max_secy; i++) {
        in_use_inter->next_index++;
        secy = &vtss_state->macsec_conf[port_no].secy[i];
        if (!secy->in_use) {
            continue;
        }
        in_use_inter->secy_id = i;
        return TRUE;
    }
    return FALSE; // Indicate no more secy's that is in use
}


static vtss_rc sc_from_sci_get(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_macsec_internal_secy_t *secy, const vtss_macsec_sci_t *sci, u32 *sc)
{
    u32 i, max_sc_rx;

    if (phy_is_1g(vtss_state, port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    for (i = 0; i < max_sc_rx; i++) {
        if (secy->rx_sc[i] == NULL) {
            continue;
        }
        if (secy->rx_sc[i]->in_use) {
            if (sci_cmp(sci, &secy->rx_sc[i]->sci)) {
                *sc = i;
                return VTSS_RC_OK;
            }
        }
    }
    VTSS_I("Error-i:%u", i);
    return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_SC_NOT_FOUND);
}

static u32 get_u32(const u8 *const buf)
{
    return *(buf) | (*(buf + 1) << 8) | (*(buf + 2) << 16) | (*(buf + 3) << 24);
}

static BOOL check_resources(vtss_state_t *vtss_state,
                            vtss_port_no_t port_no, BOOL is_sc, u32 secy_id)
{
    vtss_macsec_internal_secy_t *secy;
    u32 num_of_sa_rsrv = 0, num_of_rx_sa_inuse = 0, i, sc, sa;
    BOOL found_sc = 0, found_sa = 0, secy_in_use = 0;
    u32 macsec_max_port_sa = phy_is_1g(vtss_state, port_no) ? VTSS_MACSEC_1G_MAX_SA : VTSS_MACSEC_10G_MAX_SA;
    u32 macsec_max_sc_rx = macsec_max_port_sa / 2;
    u32 macsec_max_secy = macsec_max_sc_rx;

    num_of_sa_rsrv += VTSS_MACSEC_SA_PER_SC_MIN;

    for (i = 0; i < macsec_max_secy; i++) {
        secy = &vtss_state->macsec_conf[port_no].secy[i];
        found_sc = 0;
        if (secy->in_use) {
            secy_in_use++;
            for (sc = 0; sc < macsec_max_sc_rx; sc++) {
                if (secy->rx_sc[sc] != NULL) {
                    found_sc = 1;
                    break;
                }
            }
            if (!found_sc) { /* No SC installed yet */
                if (!(is_sc && (secy_id == i))) {
                    num_of_sa_rsrv += VTSS_MACSEC_SA_PER_SC_MIN;
                }
            }
        }
    }
    if (!is_sc && (secy_in_use == macsec_max_secy)) {
        return 0;
    }

    for (sc = 0; sc < macsec_max_sc_rx; sc++) {
        if (vtss_state->macsec_conf[port_no].rx_sc[sc].in_use) {
            for (sa = 0; sa < VTSS_MACSEC_SA_PER_SC; sa++) {
                if (vtss_state->macsec_conf[port_no].rx_sc[sc].sa[sa] != NULL) {
                    found_sa = 1;
                    break;
                }
            }
            if (!found_sa) { /* No SA installed yet */
                num_of_sa_rsrv += VTSS_MACSEC_SA_PER_SC_MIN;
            }
        }
    }

    for (sa = 0; sa < macsec_max_port_sa; sa++) {
        if (vtss_state->macsec_conf[port_no].rx_sa[sa].in_use) {
            num_of_rx_sa_inuse++;
        }
    }

    return (num_of_rx_sa_inuse + num_of_sa_rsrv <= macsec_max_port_sa);
}

static vtss_rc is_ssci_valid(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL egr,
                             const vtss_macsec_sci_t *sci, const vtss_macsec_ssci_t *ssci, const vtss_macsec_sak_t *sak)
{
    u32 an, sc, max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    vtss_macsec_internal_secy_t *secy;
    macsec_secy_in_use_iter_t in_use_inter;

    if ((ssci == NULL) || (sak == NULL)) {
        VTSS_E("Invalid SSCI or SAK");
        return VTSS_RC_ERROR;
    }
    if (sci == NULL) {
        VTSS_E("Invalid SCI");
        return VTSS_RC_ERROR;
    }
    if (phy_is_1g(vtss_state, port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    /* Loop through all the SA's to check for same SAK and SCI */
    macsec_secy_in_use_inter_init(&in_use_inter);
    while (macsec_secy_in_use_inter_getnext(vtss_state, port_no, &in_use_inter)) {
        secy = &vtss_state->macsec_conf[port_no].secy[in_use_inter.secy_id];
        if (egr) {
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                if (secy->tx_sc.sa[an] == NULL || !secy->tx_sc.sa[an]->in_use) {
                    continue;
                }
                if (!memcmp(ssci, &secy->tx_sc.sa[an]->ssci, sizeof(vtss_macsec_ssci_t))) {
                    if (!memcmp(sak, &secy->tx_sc.sa[an]->sak, sizeof(vtss_macsec_sak_t))) {
                        if (!memcmp(sci, &secy->sci, sizeof(vtss_macsec_sci_t))) {
                            VTSS_E("Tx SSCI duplicated for "SCI_FMT" an:%u", SCI_ARG(secy->sci), an);
                            return VTSS_RC_ERROR;
                        }
                    }
                }
            }
        } else {
            for (sc = 0; sc < max_sc_rx; sc++) {
                if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
                    continue;
                }
                for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                    if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
                        continue;
                    }
                    if (!memcmp(ssci, &secy->rx_sc[sc]->sa[an]->ssci, sizeof(vtss_macsec_ssci_t))) {
                        if (!memcmp(sci, &secy->rx_sc[sc]->sci, sizeof(vtss_macsec_sci_t))) {
                            if (!memcmp(sak, &secy->rx_sc[sc]->sa[an]->sak, sizeof(vtss_macsec_sak_t))) {
                                VTSS_E("Rx SSCI duplicated for "SCI_FMT" an:%u", SCI_ARG(secy->rx_sc[sc]->sci), an);
                                return VTSS_RC_ERROR;
                            }
                        }
                    }
                }
            }
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc macsec_update_glb_validate(vtss_state_t *vtss_state, vtss_port_no_t p)
{
    macsec_secy_in_use_iter_t in_use_inter;
    vtss_validate_frames_t val = VTSS_MACSEC_VALIDATE_FRAMES_STRICT;
    u32 sc, max_sc_rx;
    vtss_macsec_internal_secy_t *secy;

    macsec_secy_in_use_inter_init(&in_use_inter);

    if (phy_is_1g(vtss_state, p)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    while (macsec_secy_in_use_inter_getnext(vtss_state, p, &in_use_inter)) {
        secy = &vtss_state->macsec_conf[p].secy[in_use_inter.secy_id];
        if (secy) {
            for (sc = 0; sc < max_sc_rx; sc++) {
                if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
                    continue;
                }
                if (secy->rx_sc[sc]->conf.validate_frames < val) {
                    val = secy->rx_sc[sc]->conf.validate_frames;
                }
            }
        }
    }
    CSR_WARM_WRM(p, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL,
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES(val),
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES);
    return VTSS_RC_OK;
}

#ifdef VTSS_MACSEC_FIFO_OVERFLOW_WORKAROUND
//static vtss_rc vtss_macsec_fifo_overflow_status_get(vtss_state_t *vtss_state,
//                                                    const vtss_port_no_t port_no,
//                                                    BOOL *const status)
//{
//    u32 value;
//
//    *status = FALSE;
//    CSR_RD(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY, &value);
//    VTSS_D("Port:%d, EGR STICKY Reg value:0x%X", port_no, value);
//    if (VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_PKT64TO128_FIFO_OVERFLOW_STICKY & value) {
//        *status = TRUE;
//        CSR_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY, value);
//        /* Clear Ingress Sticky */
//        CSR_RD(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY, &value);
//        VTSS_D("Port:%d, EGR-INGR STICKY Reg value:0x%X", port_no, value);
//        CSR_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY, value);
//        return VTSS_RC_OK;
//    } else {
//        CSR_RD(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY, &value);
//        VTSS_D("Port:%d, INGR STICKY Reg value:0x%X", port_no, value);
//        if (VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY_PKT64TO128_FIFO_OVERFLOW_STICKY & value) {
//            *status = TRUE;
//            CSR_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_STICKY, value);
//            return VTSS_RC_OK;
//        }
//    }
//    return VTSS_RC_OK;
//}
#endif

/* ================================================================= *
 *  Private functions - Start
 * ================================================================= */
static vtss_rc vtss_macsec_port_check (vtss_inst_t inst, vtss_state_t **vtss_state,
                                       vtss_macsec_port_t port, BOOL create, u32 *secy_id)
{
    BOOL secy_vacancy = 0;
    u16 i, max_secy;
    vtss_macsec_internal_secy_t *secy;
    VTSS_RC(vtss_inst_port_no_check(inst, vtss_state, port.port_no));

    if ((*vtss_state)->macsec_conf[port.port_no].glb.init.enable == 0) {
        VTSS_E("MacSec API port:%u not enabled", port.port_no);
        return dbg_counter_incr(*vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_NOT_ENABLED);
    }

    if (phy_is_1g(*vtss_state, port.port_no)) {
        max_secy = VTSS_MACSEC_1G_MAX_SECY;
    } else {
        max_secy = VTSS_MACSEC_10G_MAX_SECY;
    }

    for (i = 0; i < max_secy; i++) {
        secy = &(*vtss_state)->macsec_conf[port.port_no].secy[i];

        if ((create && secy->in_use) && (secy->sci.port_id == port.port_id) && (secy->service_id == port.service_id)) {
            VTSS_E("SecY already in use. (port_no:%u port_id:%u service_id:%u)", port.port_no, port.port_id, port.service_id);
            return dbg_counter_incr(*vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_SECY_ALREADY_IN_USE);
        }
        if ((!create && secy->in_use) && (secy->sci.port_id == port.port_id) && (secy->service_id == port.service_id)) {
            *secy_id = i;
            return VTSS_RC_OK;
        }
        if (create && !secy->in_use) {
            *secy_id = i;
            secy_vacancy = 1;
            break;
        }
    }
    if (!create) {
        VTSS_E("No SecY found (port_no:%u port_id:%u service_id:%u found)", port.port_no, port.port_id, port.service_id);
        return dbg_counter_incr(*vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_NO_SECY_FOUND);
    }
    if (create && !secy_vacancy) {
        VTSS_E("No secy vacancy, port_no:%d, port_id:%d, service_id:%d, secy_id:%d ", port.port_no, port.port_id, port.service_id, *secy_id);
        return dbg_counter_incr(*vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_NO_SECY_VACANCY);
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_inst_macsec_port_no_check(vtss_inst_t inst,  vtss_state_t **vtss_state, vtss_port_no_t port_no)
{
    VTSS_RC(vtss_inst_port_no_check(inst, vtss_state, port_no));

    if ((*vtss_state)->macsec_conf[port_no].glb.init.enable == 0) {
        VTSS_E("MacSec not enabled, port_no:%d\n", port_no);
        return dbg_counter_incr(*vtss_state, port_no, VTSS_RC_ERR_MACSEC_NOT_ENABLED);
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_default_action_set_priv(vtss_state_t                             *vtss_state,
                                                   const vtss_port_no_t                      port_no,
                                                   const vtss_macsec_default_action_policy_t *const pattern)
{
    BOOL drop;
    /* Ingress. Not control and not macsec tagged */
    drop = (pattern->ingress_non_control_and_non_macsec == VTSS_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,
                 (drop ? VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT(3) |          // bypass to uncontrolled port
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_FLOW_TYPE |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION);
    /* Ingress. Not control but macsec tagged */
    drop = (pattern->ingress_non_control_and_macsec == VTSS_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,
                 (drop ? VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT(3) |          // bypass to uncontrolled port
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_FLOW_TYPE |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION);
    /* Bad Tag */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_FLOW_TYPE |             // DROP
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT(3) |          // bypass to uncontrolled port
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_FLOW_TYPE |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION);
    /* Kay Tag */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,
                 (drop ? VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT(3) |          // bypass to uncontrolled port
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_FLOW_TYPE |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION);

    /* Ingress. Control and macsec tagged */
    drop = (pattern->ingress_control_and_macsec == VTSS_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,
                 (drop ? VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT(3) |          // bypass to uncontrolled port
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_FLOW_TYPE |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION);
    /* Bad Tag is handled as macsec tagged */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_FLOW_TYPE |             // DROP
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT(3) |          // bypass to uncontrolled port
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_FLOW_TYPE |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION);
    /* Kay is handled as macsec taggged */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,
                 (drop ? VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT(3) |          // bypass to uncontrolled port
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_FLOW_TYPE |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION);

    /* Ingress. Control and not macsec tagged */
    drop = (pattern->ingress_control_and_non_macsec == VTSS_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,
                 (drop ? VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT(3) |          // bypass to uncontrolled port
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_FLOW_TYPE |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT |
                 VTSS_M_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION);

    /* Egress. Non-control frames */
    drop = (pattern->egress_non_control == VTSS_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,
                 (drop ? VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT(0) |          // bypass to common port
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_FLOW_TYPE |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DEST_PORT |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_UNTAGGED_DROP_ACTION);
    /* Tagged is handled as above */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,
                 (drop ? VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT(0) |          // bypass to common port
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_FLOW_TYPE |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DEST_PORT |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_TAGGED_DROP_ACTION);
    /* Bad Tag is handled as above */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_FLOW_TYPE |             // DROP
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT(0) |          // bypass to common port
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_FLOW_TYPE |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DEST_PORT |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_BADTAG_DROP_ACTION);
    /* Kay is handled as above */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,
                 (drop ? VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT(0) |          // bypass to common port
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_FLOW_TYPE |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DEST_PORT |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP_NCP_KAY_DROP_ACTION);

    /* Egress. Control frames */
    drop = (pattern->egress_control == VTSS_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,
                 (drop ? VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT(0) |          // bypass to commom port
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_FLOW_TYPE |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DEST_PORT |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_UNTAGGED_DROP_ACTION);
    /* Tagged is handled as above */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,
                 (drop ? VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT(0) |          // bypass to commom port
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_FLOW_TYPE |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DEST_PORT |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_TAGGED_DROP_ACTION);
    /* Bad Tagged is handled as above */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_FLOW_TYPE |             // DROP
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT(0) |          // bypass to commom port
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_FLOW_TYPE |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DEST_PORT |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_BADTAG_DROP_ACTION);
    /* KAY is handled as above */
    CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,
                 (drop ? VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_FLOW_TYPE : 0) |// bypass / drop
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT(0) |          // bypass to commom port
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION(2),         // drop silently
                 VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_FLOW_TYPE |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DEST_PORT |
                 VTSS_M_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP_CP_KAY_DROP_ACTION);

    return VTSS_RC_OK;
}

// Function for setting registers depending upon speed configuration for a specific port.
// This is not a function which is public for the application, but need to be public for other API files.
// enable = 0, means MacSec block gets disable (during speed change)
vtss_rc vtss_macsec_speed_conf_priv(vtss_state_t                      *vtss_state,
                                    const vtss_port_no_t              port_no,
                                    const BOOL                        enable,
                                    const BOOL                        speed_recfg)
{
    u8 value;
    vtss_port_speed_t     speed = VTSS_SPEED_UNDEFINED;
    BOOL phy10g;
    vtss_rc rc = VTSS_RC_OK;
    u32 reg_value;
#ifdef VTSS_CHIP_CU_PHY
    vtss_phy_port_state_t *ps      = &vtss_state->phy_state[port_no];
    vtss_port_status_t    *status  = &ps->status;
    vtss_phy_conf_t       *conf    = &ps->setup;
#endif

    if (!vtss_state->macsec_conf[port_no].glb.init.enable) {
        return VTSS_RC_OK; /* Not enabled, return silently */
    }
    if ((vtss_state->warm_start_cur) ||
        (vtss_state->sync_calling_private)) {
        return VTSS_RC_OK; /* Warm start mode, return silently */
    }

    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));

    // From the register description
    // * 000: 10G
    // * 001: 10G_1G
    // * 101: 1G
    // * 110: 1G_100M
    // * 111: 1G_10M
    // * others: illegal
    value = 0; // Default to 10g
#ifdef VTSS_CHIP_10G_PHY
    if (phy10g) {
        if (vtss_state->phy_10g_state[port_no].mode.oper_mode == VTSS_PHY_1G_MODE) {
            value = 1; // * 001: 10G_1G
        } else {
            // Every other modes are 10G modes.
            value = 0; // * 000: 10G
        }
    } else {
#endif
#ifdef VTSS_CHIP_CU_PHY
        // Determine speed.
        if (conf->mode == VTSS_PHY_MODE_ANEG) {
            speed = status->speed;
        } else {
            // Forced speed
            speed = conf->forced.speed;
        }

        // Determine register value according to the description of the register
        switch (speed) {
        case VTSS_SPEED_1G:
            value = 0x5;     // * 101: 1G
            break;

        case VTSS_SPEED_100M:
            value = 0x6;     // * 110: 1G_100M
            break;

        case VTSS_SPEED_10M:
            value = 0x7;     // * 111: 1G_10M
            break;

        default:
            // This is completely OK, because the API returns undefined speed if the port is down.
            VTSS_I("Speed is undefined");
            return VTSS_RC_OK;
        }

        VTSS_D("port_no:%d, Speed mode:0x%X enable:%d", port_no, value, enable);
#endif
#ifdef VTSS_CHIP_10G_PHY
    }
#endif

    if (!enable) {
        /* Set ING_MACSEC_ENA = 0 */
        CSR_WRM(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                0,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA );

        /* Set EGR_MACSEC_ENA = 0 */
        CSR_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                0,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA);

        return VTSS_RC_OK;
    } else {
        /* Set ING_MACSEC_ENA = 1 */
        CSR_WRM(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA );
        /* Set EGR_MACSEC_ENA = 1 */
        CSR_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA);
    }

    /* If we are not going to change the SPEED_MODE value then
       we should not do anything in this function. */
    CSR_RD(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG, &reg_value);
    if ((VTSS_X_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(reg_value)) != value) {

        /* Initilize/toggle MAC after speed change */
        /* Set LMAC and HMAC RX_ENA = 0 */
        CSR_WRM(port_no, VTSS_LINE_MAC_CONFIG_MAC_ENA_CFG,
                0,
                VTSS_F_LINE_MAC_CONFIG_MAC_ENA_CFG_RX_ENA);
        CSR_WRM(port_no, VTSS_HOST_MAC_CONFIG_MAC_ENA_CFG,
                0,
                VTSS_F_HOST_MAC_CONFIG_MAC_ENA_CFG_RX_ENA);

        /* Set ING_MACSEC_ENA = 0 */
        CSR_WRM(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                0,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA );

        /* Set EGR_MACSEC_ENA = 0 */
        CSR_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                0,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA);

        /* Change the speed Ingress */
        CSR_WRM(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(value),
                VTSS_M_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE);

        /* Change the speed Egress */
        CSR_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(value),
                VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE);

        /* Set ING_MACSEC_ENA = 1 */
        CSR_WRM(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA );
        /* Set EGR_MACSEC_ENA = 1 */
        CSR_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA);

        CSR_WRM(port_no, VTSS_LINE_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL,
                (speed == VTSS_SPEED_10M || speed == VTSS_SPEED_100M) ?
                VTSS_F_LINE_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL_MAC_RX_PRE_CRC_MODE : 0,
                VTSS_F_LINE_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL_MAC_RX_PRE_CRC_MODE);
    }

#ifdef VTSS_MACSEC_FIFO_OVERFLOW_WORKAROUND
    /* Workaround for MACsec Speed change from 100 Mbps to 1G */
    if (speed_recfg) {
        //if ((rc = vtss_macsec_fifo_overflow_status_get(vtss_state, port_no, &fifo_status)) == VTSS_RC_OK) {
        /* Reconfigure without checking for fifo overflow status*/
        if (enable) {
            VTSS_D("MACsec Re-config Begin on port:%d", port_no);
            /* Ingress */
            CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                        VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                        VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST);

            /* Egress */
            CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                        VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                        VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST);

            CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                        VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST);


            CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                        VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST);


            VTSS_D("MACsec Block Enable SW_RESET on Port:%u", port_no);

            CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                        VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                        VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST);

            /* Egress */
            CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                        VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                        VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST);

            /* Enable Ingress MacSec block */
            CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                        VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                        VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(phy10g ? 0 : value));

            /* Enable Egress MacSec block */
            CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                        VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                        VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(phy10g ? 0 : value));
            VTSS_D("MACsec Block Out of SW_RESET on Port:%u", port_no);
            vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg = TRUE;
            vtss_state->macsec_conf[port_no].glb.recfg_speed = value;

            rc = vtss_macsec_init_set_priv(vtss_state, port_no, &vtss_state->macsec_conf[port_no].glb.init);

            if (rc != VTSS_RC_OK) {
                VTSS_E("vtss_macsec_init_set_priv port(%d) return rc(0x%04x)", port_no, rc);
                return VTSS_RC_OK;
            }

            /* Re-Configure macsec using private functions  */
            VTSS_D("Port:%d, Re-config MACsec Block\n", port_no);
            if ((rc = vtss_macsec_reconfigure(vtss_state, port_no)) != VTSS_RC_OK) {
                VTSS_E("vtss_macsec_reconfig port(%d) return rc(0x%04X)", port_no, rc);
                return VTSS_RC_ERROR;
            }
        }
    } /* End of Enable */
#endif /* VTSS_MACSEC_FIFO_OVERFLOW_WORKAROUND*/

    return VTSS_RC_OK;
}


// Function for setting registers to set 4 byte preamble.
// This is not a function should be called from 1588 API.
vtss_rc vtss_macsec_preamble_shrink_set_priv(vtss_state_t          *vtss_state,
                                             const vtss_port_no_t   port_no,
                                             const BOOL             enable)
{
    BOOL phy10g;

    if (!vtss_state->macsec_conf[port_no].glb.init.enable) {
        return VTSS_RC_OK; /* Not enabled, return silently */
    }

    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));

    /* Enable 4 byte preamble */
    CSR_WRM(port_no, VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG,
            (enable ? (phy10g ? VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_ENABLE_4BYTE_PREAMBLE : VTSS_BIT(31)) : 0),
            (phy10g ? VTSS_F_LINE_MAC_CONFIG_MAC_PKTINF_CFG_ENABLE_4BYTE_PREAMBLE : VTSS_BIT(31)));


    return VTSS_RC_OK;
}

static vtss_rc vtss_mac_block_mtu_get_priv(vtss_state_t *vtss_state,
                                           const vtss_port_no_t port_no,
                                           u16 *mtu_value,
                                           BOOL *mtu_tag_check)
{
    u32 host_mtu;
    u32 line_mtu;

    VTSS_D("Port:%d", port_no);

    /* Host MAC MTU size */
    CSR_RD(port_no, VTSS_HOST_MAC_CONFIG_MAC_MAXLEN_CFG, &host_mtu);
    CSR_RD(port_no, VTSS_LINE_MAC_CONFIG_MAC_MAXLEN_CFG, &line_mtu);
    if (host_mtu == line_mtu) {
        if (host_mtu & VTSS_F_HOST_MAC_CONFIG_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK) {
            *mtu_tag_check = TRUE;
        } else {
            *mtu_tag_check = FALSE;
        }
        /* MTU size */
        *mtu_value = (u16) host_mtu;
    } else {
        *mtu_value = 0;
        *mtu_tag_check = FALSE;
        VTSS_E("Mismatch Line MAC MTU(%d) and Host MAC MTU(%d) size", line_mtu, host_mtu);
        return VTSS_RC_ERROR;
    }
    VTSS_D("Port:%d, MTU:%d, Tag:%d\n", port_no, *mtu_value, *mtu_tag_check);

    return VTSS_RC_OK;
}

static vtss_rc vtss_mac_block_mtu_set_priv(vtss_state_t *vtss_state,
                                           const vtss_port_no_t port_no,
                                           u16 mtu_value,
                                           BOOL mtu_tag_check)
{
    u32 mac_maxlen_cfg = 0;

    VTSS_D("Port:%d, MTU:%d, Tag_check:%d", port_no, mtu_value, mtu_tag_check);

    vtss_state->macsec_conf[port_no].glb.mac_block_mtu = mtu_value;

    if (mtu_tag_check) {
        mac_maxlen_cfg = (VTSS_F_HOST_MAC_CONFIG_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK |
                          mtu_value);
        /* Host MAC MTU size */
        CSR_COLD_WR(port_no, VTSS_HOST_MAC_CONFIG_MAC_MAXLEN_CFG, mac_maxlen_cfg);
        /* Line MAC MTU size */
        CSR_COLD_WR(port_no, VTSS_LINE_MAC_CONFIG_MAC_MAXLEN_CFG, mac_maxlen_cfg);
    } else {
        /* Host MAC MTU size */
        CSR_COLD_WR(port_no, VTSS_HOST_MAC_CONFIG_MAC_MAXLEN_CFG, mtu_value);
        /* Line MAC MTU size */
        CSR_COLD_WR(port_no, VTSS_LINE_MAC_CONFIG_MAC_MAXLEN_CFG, mtu_value);

    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_mtu_set_priv(vtss_state_t         *vtss_state,
                                        const vtss_port_no_t port_no)
{
    u8  i;
    u32 mtu_value = vtss_state->macsec_conf[port_no].glb.mtu_conf.mtu;
    BOOL drop     = vtss_state->macsec_conf[port_no].glb.mtu_conf.drop;
    BOOL vlan_unaware_en = vtss_state->macsec_conf[port_no].glb.mtu_conf.vlan_unaware_en;

    if (mtu_value > VTSS_MACSEC_MTU_MAX) {
        VTSS_E("Maximum MTU allowed is %d (+ 4 bytes for VLAN), was:%d", VTSS_MACSEC_MTU_MAX, mtu_value);
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_MAX_MTU);
    }

    VTSS_I("max MTU:%d, vlan_unaware:%d, drop:%d, val:0x%X", mtu_value, vlan_unaware_en, drop,
           VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(mtu_value) |
           (drop ? VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMP_DROP : 0));

    CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK,
                VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(mtu_value) |
                (drop ? VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMP_DROP : 0));

    CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK,
                VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(mtu_value) |
                (drop ? VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_NON_VLAN_MTU_CHECK_NV_MTU_COMP_DROP : 0));

    /* In VLAN aware mode, VLAN_MTU_CHECK == (NON_VLAN_MTU_CHECK + 4) bytes,
       In VLAN unaware mode, NON_VLAN_MTU_CHECK == VLAN_MTU_CHECK bytes */
    if (!vlan_unaware_en) {
        mtu_value += 4;
    }

    for (i = 0; i < 8; i++) {
        CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK(i),
                    VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMPARE(mtu_value) |
                    (drop ? VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMP_DROP : 0));

        CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK(i),
                    VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMPARE(mtu_value) |
                    (drop ? VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_VLAN_MTU_CHECK_MTU_COMP_DROP : 0));
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_init_set_priv(vtss_state_t                      *vtss_state,
                                         const vtss_port_no_t              port_no,
                                         const vtss_macsec_init_t          *const init)
{
    BOOL              phy10g;
    u32               latency, i, record = 0;
    vtss_macsec_default_action_policy_t policy = {0, 0, 0, 0, 0, 0};
    vtss_macsec_mac_counters_t mac_cntrs;
    BOOL dis_nm = init->dis_ing_nm_macsec_en;
    u8   xform_rec_size;

    /* While configuring macsec, enable macsec block first and then enable
       Mac blocks. While removing macsec configuration, disable Mac block
       first and then disable Macsec block. This is to ensure that bulk data
       in transit does not affect Macsec block during enabling/disabling. */
    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
    if ( phy10g) {
#ifdef VTSS_CHIP_10G_PHY
        VTSS_RC(phy_10g_macsec_clk_en(vtss_state, port_no, init->enable));
        /* In Macsec Rev-B 10G phys,i.e. Malibu and Venice-C, if 'MAC_ENA' bit
           is not set, Macsec configuration does not take effect. This setting is added
           here only for applying Macsec configuration */
        if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE &&
            init->enable) {
            CSR_WARM_WRM(port_no, VTSS_LINE_PMA_MAC_ENABLE_MAC_ENA,
                         VTSS_F_LINE_PMA_MAC_ENABLE_MAC_ENA_MAC_ENA,
                         VTSS_F_LINE_PMA_MAC_ENABLE_MAC_ENA_MAC_ENA);
        }
        if (vtss_state->phy_10g_state[port_no].mode.oper_mode != VTSS_PHY_1G_MODE && !init->enable) {
            //lint -e539
            VTSS_RC(phy_10g_mac_conf(vtss_state, port_no, 0, 0));
        }
#endif
    } else {
        if (!init->enable) {
            VTSS_RC(phy_10g_mac_conf(vtss_state, port_no, 0, 0));
        }
    }


#if defined (VTSS_OPT_PHY_TIMESTAMP)
    VTSS_RC(vtss_phy_ts_macsec_mode_change(vtss_state, port_no, init->enable));
#endif /* VTSS_OPT_PHY_TIMESTAMP */


    VTSS_D("Enable:%d", init->enable);
    if (init->enable) {
        /* Ingress MacSec block Enable Clock */
        CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                    VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                    VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST);


        /* Egress MacSec Enable Clock */
        CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                    VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                    VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST);

        /* Ingress MacSec block Out of SW Reset and Enable Clock */
        CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                    VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA);


        /* Egress MacSec block Out of SW Reset and Enable Clock */
        CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                    VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA);

        /* Set the context */
        if ( !vtss_state -> sync_calling_private ) {
            CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL, 0xE5880214);
            latency = phy10g ? MACSEC_10G_INGR_LATENCY : MACSEC_1G_INGR_LATENCY;
            CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL,
                        VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_MC_LATENCY_FIX(latency) |
                        (dis_nm ? 0 : VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_NM_MACSEC_EN) |
                        VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE(1));
        }

        /* Non-matched frames are dropped, destination:controlled port */
        if (!vtss_state->sync_calling_private) {
            CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP, 0x0);
            CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP, 0x0);
            CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP, 0x0);
            CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP, 0x0);
            VTSS_RC(vtss_macsec_default_action_set_priv(vtss_state, port_no, &policy));
        }

        /* CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP, 0x89898989); */
        /* CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,  0x89898989); */

        /* Counters are clear on read */
        CSR_WARM_WRM(port_no, VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL,
                     VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_AUTO_CNTR_RESET,
                     VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_AUTO_CNTR_RESET);

        /* Set default constency rules to pass unmatched frames */
        CSR_WARM_WRM(port_no, VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL,
                     VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL_NON_MATCH_CTRL_ACT |
                     VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL_NON_MATCH_ACT,
                     VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL_NON_MATCH_CTRL_ACT |
                     VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CC_CONTROL_NON_MATCH_ACT);

        /* Egress */
        if (!vtss_state -> sync_calling_private) {
            if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
                CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL, 0xE5880218);
                xform_rec_size = 2;
            } else {
                CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_CONTEXT_CTRL, 0xE5880214);
                xform_rec_size = 1;
            }
            latency = phy10g ? MACSEC_10G_EGR_LATENCY : MACSEC_1G_EGR_LATENCY;
            CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL,
                        VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_MC_LATENCY_FIX(latency) |
                        VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE(xform_rec_size));
        }
        /* Non-matched frames are dropped, destination:common port */
        /* CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP,  0x81818181); */
        /* CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP,   0x81818181); */

        /* Counters are clear on read */
        CSR_WARM_WRM(port_no, VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL,
                     VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_AUTO_CNTR_RESET,
                     VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_AUTO_CNTR_RESET);

        /* Enable VLAN tag parsing */
        CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG,
                    VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_STAG |
                    VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_QTAG |
                    VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_QINQ);

        CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG,
                    VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_STAG |
                    VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_QTAG |
                    VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_CP_TAG_PARSE_QINQ);

        CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG,
                    VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_PARSE_QTAG |
                    VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_PARSE_STAG |
                    VTSS_F_MACSEC_INGR_IG_CC_PARAMS2_IG_CP_TAG_PARSE_QINQ);

        /* Enable octet incrment mode to increment validated/decrypted counter even when validate frames is disabled */
        if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
            CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL,
                        VTSS_F_MACSEC_EGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL_MACSEC_OCTET_INCR_MODE);
            CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL,
                        VTSS_F_MACSEC_INGR_POST_PROC_CTL_DEBUG_REGS_PP_CTRL_MACSEC_OCTET_INCR_MODE);
        }

        /* BLOCK_CTX_UPDATE::BLOCK_CTX_UPDATES should be programmed to 0x3 */
        CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_BLOCK_CTX_UPDATE, 0x3);
        CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_BLOCK_CTX_UPDATE, 0x3);

        /* Making both threshold and rollover event as zero */
        if (!vtss_state->sync_calling_private) {
            CSR_WARM_WRM(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS, 0x00000000, 0x00300000);
            if (!vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg) {
                /* Clear Mac block counters */
                VTSS_RC(vtss_macsec_lmac_counters_get_priv(vtss_state, port_no, &mac_cntrs, TRUE));
                VTSS_RC(vtss_macsec_hmac_counters_get_priv(vtss_state, port_no, &mac_cntrs, TRUE));
            }
            if (!vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg) {
                // Do not initialize if this is a warm start boot.
                /* We set MTU to maximum, because we don't know which frame size the MAC/Switch supports.*/
                vtss_state->macsec_conf[port_no].glb.mtu_conf.mtu  = VTSS_MACSEC_MTU_MAX;
                vtss_state->macsec_conf[port_no].glb.mtu_conf.drop = TRUE;
                VTSS_RC(vtss_macsec_mtu_set_priv(vtss_state, port_no));

                for (i = 0; i < VTSS_MACSEC_CP_RULES; i++) {
                    VTSS_N("Disable i:%d", i);
                    vtss_state->macsec_conf[port_no].glb.control_match[i].match = VTSS_MACSEC_MATCH_DISABLE;
                    vtss_state->macsec_conf[port_no].glb.egr_bypass_record[i] = MACSEC_NOT_IN_USE;
                }
            } else {
                for (i = 0; i < VTSS_MACSEC_CP_RULES; i++) {
                    if (vtss_state->macsec_conf[port_no].glb.egr_bypass_record[i] == MACSEC_NOT_IN_USE) {
                        continue;
                    }
                    // Since SA flows shall be reallocated for CP again, the resource shall be released again
                    record = vtss_state->macsec_conf[port_no].glb.egr_bypass_record[i];
                    memset(&(vtss_state->macsec_conf[port_no].tx_sa[record]), 0, sizeof(vtss_macsec_internal_tx_sa_t));
                    vtss_state->macsec_conf[port_no].glb.egr_bypass_record[i] = MACSEC_NOT_IN_USE;
                }
            }
        }
        CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_FC_CFG, 0x64411);
        /* Enable Ingress MacSec block */
        CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                     VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                     VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA,
                     VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                     VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST |
                     VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA |
                     VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA);

        if (!vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg) {
            CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                         VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(phy10g ? 0 : 0x5),
                         VTSS_M_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE);
        } else {
            CSR_COLD_WRM(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                         VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(vtss_state->macsec_conf[port_no].glb.recfg_speed),
                         VTSS_M_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE);
        }
        /* Enable Egress MacSec block */
        CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                     VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                     VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA,
                     VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                     VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST |
                     VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA |
                     VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA);
        if (!vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg) {
            CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                         VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(phy10g ? 0 : 0x5),
                         VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE);
        } else {
            CSR_COLD_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                         VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(vtss_state->macsec_conf[port_no].glb.recfg_speed),
                         VTSS_M_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE);
        }

    } else {

        /* Ingress */
        CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                    VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                    VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST |
                    VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA);

        /* Egress */
        CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                    VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                    VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST |
                    VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA);

        /* Ingress */
        CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                    VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST |
                    VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA);

        /* Egress */
        CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                    VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST |
                    VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA);

        /* Clear the internals */
        memset(&vtss_state->macsec_conf[port_no], 0, sizeof(vtss_state->macsec_conf[port_no]));

    }

    return VTSS_RC_OK;
}

static vtss_rc macsec_sa_flow_set(vtss_state_t *vtss_state, vtss_port_no_t p, BOOL egr, u32 record,
                                  vtss_macsec_internal_secy_t *secy, u16 an, u32 sc, vtss_macsec_match_action_t action)
{
    u32 tag_bypass = 0, offset = 0, validate = 0, dest_port = 0, flow_type = (egr ? 3 : 2), chk_mask = 0;
    BOOL conf = 0, incl_sci = 0, use_es = 0, use_scb = 0, rp = 0, protect_frm = 0;

    if (action == VTSS_MACSEC_MATCH_ACTION_DROP) {
        flow_type = 1; // Destination: Drop
    } else if (action == VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT) {
        dest_port = 2; // Destination: Controlled port
    } else {
        dest_port = 3; // Destination: Uncontrolled port
        flow_type = 0;
    }
    if (secy != NULL) {
        if (egr) {
            conf = secy->tx_sc.sa[an]->confidentiality;
            protect_frm = secy->conf.protect_frames;
            incl_sci = secy->conf.always_include_sci;
            use_es = secy->conf.use_es;
            use_scb = secy->conf.use_scb;
            offset = secy->conf.confidentiality_offset;
        } else {
            rp = secy->rx_sc[sc]->conf.replay_protect;
            offset = secy->rx_sc[sc]->conf.confidentiality_offset;
            if (secy->rx_sc[sc]->conf.validate_frames == VTSS_MACSEC_VALIDATE_FRAMES_DISABLED) {
                validate = 0;
            } else if (secy->rx_sc[sc]->conf.validate_frames == VTSS_MACSEC_VALIDATE_FRAMES_CHECK) {
                validate = 1;
            } else if (secy->rx_sc[sc]->conf.validate_frames == VTSS_MACSEC_VALIDATE_FRAMES_STRICT) {
                validate = 2;
            } else {
                VTSS_E("validate_frames value invalid, sc:%d, an:%d", sc, an);
                return dbg_counter_incr(vtss_state, p, VTSS_RC_ERR_MACSEC_INVALID_VALIDATE_FRM);
            }
            /* Update the global 'validate frames' */
            /* The value is the least of all validate_frames entires of all SecYs, i.e. disabled/check/strict */
            VTSS_RC(macsec_update_glb_validate(vtss_state, p));
        }
        if (secy->tag_bypass == VTSS_MACSEC_BYPASS_TAG_ONE) {
            tag_bypass = 1;
        } else if (secy->tag_bypass == VTSS_MACSEC_BYPASS_TAG_TWO) {
            tag_bypass = 2;
        }
    }
    if (egr) {
        VTSS_D("Egress (sa:%d): prot:%d, incl_sci:%d use_es:%d use_scb:%d confidentiality:%d action:%s",
               record, protect_frm, incl_sci, use_es, use_scb, conf,
               flow_type == 0 ? "Bypass" : flow_type == 1 ? "Drop" : flow_type == 2 ? "Ingress" : flow_type == 3 ? "Egress" : "");
        chk_mask = VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_SA_IN_USE ^ 0xFFFFFFFF;
        CSR_WARM_WRM_CHK_MASK(p, VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR(record),
                              VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DROP_ACTION(2) |                   // Drop action=Drop
                              VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_FLOW_TYPE(flow_type) |             // MacSec egress
                              VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DEST_PORT(dest_port) |             // Controlled port
                              (protect_frm ? VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_PROTECT_FRAME : 0) |// Protect frame
                              (incl_sci ? VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_INCLUDE_SCI : 0) |     // Incl.SCI
                              (use_es ? VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_USE_ES : 0) |            // Use ES
                              (use_scb ? VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_USE_SCB : 0) |          // Use SCB
                              VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_TAG_BYPASS_SIZE(tag_bypass) |      // VLAN Tags to bypass
                              VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_CONFIDENTIALITY_OFFSET(offset) |   // Conf.Offset
                              //             VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_SA_IN_USE |                        // Inuse --> in an separate func
                              (conf ? VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_CONF_PROTECT : 0),        // Confidentiality
                              0xFFFFFFFF, chk_mask); // For Warm Start
    } else {
        VTSS_D("Ingress (sa:%d): rp:%d validate:%d, offset:%d action:%s", record, rp, validate, offset,
               flow_type == 0 ? "Bypass" : flow_type == 1 ? "Drop" : flow_type == 2 ? "Ingress" : flow_type == 3 ? "Egress" : "");
        chk_mask = VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_SA_IN_USE ^ 0xFFFFFFFF;
        CSR_WARM_WRM_CHK_MASK(p, VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR(record),
                              VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DROP_ACTION(2) |                  // Drop action=Drop
                              VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_FLOW_TYPE(flow_type) |            // MacSec ingress
                              VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DEST_PORT(dest_port) |            // Controlled port
                              (rp ? VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_REPLAY_PROTECT : 0) |       // Replay protect
                              (VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_VALIDATE_FRAMES(validate) |      // Validate
                               //              VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_SA_IN_USE |                      // Inuse --> in an separate func
                               VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_CONFIDENTIALITY_OFFSET(offset)), // Conf. offset
                              0xFFFFFFFF, chk_mask); // For Warm Start
    }

    return VTSS_RC_OK;
}

static vtss_rc macsec_sa_match_set(vtss_state_t *vtss_state, vtss_port_no_t p, BOOL egr, u32 record, vtss_macsec_match_pattern_t *pattern,
                                   vtss_macsec_internal_secy_t *secy, BOOL sci, u32 sc, u32 an, BOOL untagged)
{
    u16 mac_addr_lo = 0;
    /*  For each 'pattern->match' a pattern is configured and a the corresponding mask is set.  */
    /*  To match a frame to this record (SA) all configured patterns must be matched */

    VTSS_D("SA:%u  Dir:%s  Match idx:0x%x", record, egr ? "Egress" : "Ingress", pattern->match);

    if (!(pattern->match & VTSS_MACSEC_MATCH_IS_CONTROL)) {
        /* Match all non-control packets - as default */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(record)), 0,
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_CONTROL_PACKET));
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_CTL_PACKET_MASK),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_CTL_PACKET_MASK));
    }

    if (egr) {
        /* Match macsec tag/untagged frames */
        CSR_WARM_WRM(p,
                     VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(record),
                     VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_UNTAGGED,
                     VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_UNTAGGED |
                     VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_BAD_TAG |
                     VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_KAY_TAG |
                     VTSS_F_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_TAGGED);
    } else {
        CSR_WARM_WRM(p,
                     VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(record),
                     (untagged ? VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_UNTAGGED : 0) |
                     VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_TAGGED,
                     VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_UNTAGGED |
                     VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_BAD_TAG |
                     VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_KAY_TAG |
                     VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH_TAGGED);
    }

    if (!egr && sci) {
        VTSS_MACSEC_ASSERT(secy == NULL, "SecY is invalid");

        /* Match Explicit SCI at ingress, i.e. SCI in the SecTag */
        /* Configure SCI even if it is not used for matching. During warmstart,
           SCI can be used for correct SA mapping. */
        CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_LO(record), get_u32(&secy->rx_sc[sc]->sci.mac_addr.addr[0]));
        CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_HI(record), secy->rx_sc[sc]->sci.mac_addr.addr[4] |
                    (secy->rx_sc[sc]->sci.mac_addr.addr[5] << 8) | (MACSEC_BS(secy->rx_sc[sc]->sci.port_id) << 16));

        if (secy->conf.always_include_sci) {
            /* Enable SCI mask */
            CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK(record),
                         VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MACSEC_SCI_MASK,
                         VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MACSEC_SCI_MASK);

            /* The SC bit should be set in TCI field */
            CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(record),
                         VTSS_ENCODE_BITFIELD(1, 29, 1),
                         VTSS_ENCODE_BITMASK(29, 1));

            /* SCI Availability mask */
            CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK(record),
                         VTSS_ENCODE_BITMASK(29, 1),
                         VTSS_ENCODE_BITMASK(29, 1));
        } else {
            /* We are on P2P line.  Do not match on SCI - at all.  All macsec frames are directed into the SC */
            /* /\* Match Implicit SCI at ingress, i.e. the SMAC of the frame *\/ */
            /* CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_LO(record), get_u32(&secy->rx_sc[sc]->sci.mac_addr.addr[0])); */
            /* CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(record), */
            /*         secy->rx_sc[sc]->sci.mac_addr.addr[4] | (secy->rx_sc[sc]->sci.mac_addr.addr[5] << 8), */
            /*         VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0); */

            /* /\* Enable SA Mask *\/ */
            /* CSR_WARM_WRM(p, */
            /*         VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK(record), */
            /*         VTSS_F_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK(0x3F), */
            /*         VTSS_M_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK); */

            /* /\* SC bit should cleared in TCI field *\/ */
            /* CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(record), 0, VTSS_ENCODE_BITMASK(29, 1)); */
            /* SCI Availability mask */
            /* CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK(record), */
            /*         VTSS_ENCODE_BITMASK(29, 1), */
            /*         VTSS_ENCODE_BITMASK(29, 1)); */
        }

        /* Match AN  */
        CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(record),
                     VTSS_ENCODE_BITFIELD(an, 24, 2),
                     VTSS_ENCODE_BITMASK(24, 2));

        /* AN mask */
        CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK(record),
                     VTSS_ENCODE_BITMASK(24, 2),
                     VTSS_ENCODE_BITMASK(24, 2));

    }

    if (pattern->match & VTSS_MACSEC_MATCH_ETYPE) {
        /* Etype */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE(MACSEC_BS(pattern->etype))),
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE));
        /* Enable Etype mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_ETYPE_MASK),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_ETYPE_MASK));

    }

    VTSS_D("Match : 0x%X, Record : %d", pattern->match, record);
    if (pattern->match & VTSS_MACSEC_MATCH_SMAC) {
        VTSS_D("SRC MAC : %02X:%02X:%02X:%02X:%02X:%02X",
               pattern->src_mac.addr[0], pattern->src_mac.addr[1],
               pattern->src_mac.addr[2], pattern->src_mac.addr[3],
               pattern->src_mac.addr[4], pattern->src_mac.addr[5]);

        /* Source MAC address */
        CSR_WARM_WR(p,
                    PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_LO(record)),
                    get_u32(&pattern->src_mac.addr[0]));
        mac_addr_lo = (pattern->src_mac.addr[4] | (pattern->src_mac.addr[5] << 8));
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(record)),
                     mac_addr_lo,
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0));

        /* Enable source mac mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK),
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK));
    }

    if (pattern->match & VTSS_MACSEC_MATCH_DMAC) {
        VTSS_D("DEST MAC : %02X:%02X:%02X:%02X:%02X:%02X",
               pattern->dest_mac.addr[0], pattern->dest_mac.addr[1],
               pattern->dest_mac.addr[2], pattern->dest_mac.addr[3],
               pattern->dest_mac.addr[4], pattern->dest_mac.addr[5]);

        /* Destination MAC address */
        CSR_WARM_WR(p,
                    PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_LO(record)),
                    get_u32(&pattern->dest_mac.addr[0]));
        mac_addr_lo = (pattern->dest_mac.addr[4] | (pattern->dest_mac.addr[5] << 8));
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI(record)),
                     mac_addr_lo,
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_MAC_DA_MATCH_15_TO_0));

        /* Enable destination mac mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK),
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK));
    }

    if (pattern->match & VTSS_MACSEC_MATCH_VLAN_ID) {
        /* VLAN id */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID(pattern->vid)),
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID));

        /* Enable VLAN mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_MASK),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_MASK));

        /* VLAN valid */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_VALID),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_VALID));

        /* Enable VLAN valid mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_VLD_MASK),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_VLD_MASK));
    }

    if (pattern->match & VTSS_MACSEC_MATCH_VLAN_ID_INNER) {
        /* VLAN id inner */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_EXT_MATCH(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER(pattern->vid_inner)),
                     PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER));

        /* Enable VLAN inner mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_INNER_MASK),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_INNER_MASK));
    }

    if (pattern->match & VTSS_MACSEC_MATCH_BYPASS_HDR) {
        if (egr) {
            CSR_WARM_WR(p, VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH1(record), get_u32(&pattern->hdr[0]));
            CSR_WARM_WR(p, VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH2(record), get_u32(&pattern->hdr[4]));
            CSR_WARM_WR(p, VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK1(record),  get_u32(&pattern->hdr_mask[0]));
            CSR_WARM_WR(p, VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK2(record),  get_u32(&pattern->hdr_mask[4]));
        } else {
            CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH1(record), get_u32(&pattern->hdr[0]));
            CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH2(record), get_u32(&pattern->hdr[4]));
            CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK1(record),  get_u32(&pattern->hdr_mask[0]));
            CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK2(record),  get_u32(&pattern->hdr_mask[4]));
        }
    }

    if (pattern->match & VTSS_MACSEC_MATCH_IS_CONTROL) {
        /* Control frame  */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(record)),
                     pattern->is_control ? PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_CONTROL_PACKET) : 0,
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_CONTROL_PACKET));

        /* Enable Control frame mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_CTL_PACKET_MASK),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_CTL_PACKET_MASK));
    }

    if (pattern->match & VTSS_MACSEC_MATCH_HAS_VLAN) {
        /* Has VLAN (QTAG or STAG)  */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(record)),
                     pattern->has_vlan_tag ? PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_VALID) : 0,
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_VALID));

        /* Enable VLAN valid mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_VLD_MASK),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_VLD_MASK));
    }

    if (pattern->match & VTSS_MACSEC_MATCH_HAS_VLAN_INNER) {
        /* Has vlan inner tag  */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(record)),
                     pattern->has_vlan_inner_tag ? PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_QINQ_FOUND) : 0,
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_QINQ_FOUND));

        /* Enable VLAN inner tag mask */
        CSR_WARM_WRM(p,
                     PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(record)),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_QINQ_FOUND_MASK),
                     PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_QINQ_FOUND_MASK));
    }

    /* Set the priority */
    CSR_WARM_WRM(p,
                 PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(record)),
                 PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY(15 - pattern->priority)),
                 PST_DIR(VTSS_M, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY));

    return VTSS_RC_OK;
}

static vtss_rc macsec_sa_match_reset(vtss_state_t *vtss_state,
                                     vtss_port_no_t p,
                                     BOOL egr,
                                     u32 record)
{
    VTSS_D("SA:%u  Dir:%s  Record:%u", record, egr ? "Egress" : "Ingress", record);

    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_LO(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_LO(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MASK(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_EXT_MATCH(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH2(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK1(record)), 0);
    CSR_WARM_WR(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK2(record)), 0);
    if (!egr) {
        CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_LO(record), 0);
        CSR_WARM_WR(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_HI(record), 0);
    }

    return VTSS_RC_OK;
}

// Used for finding installed records during warm_start
static vtss_rc macsec_sa_match_warm_start_get(vtss_state_t *vtss_state, vtss_port_no_t p, BOOL egr, vtss_macsec_match_pattern_t *pattern, u32 *record)
{

    u32 sa, max_sa, value;
    u16 mac_addr;
    if (phy_is_1g(vtss_state, p)) {
        max_sa = VTSS_MACSEC_1G_MAX_SA;
    } else {
        max_sa = VTSS_MACSEC_10G_MAX_SA;
    }

    for (sa = 0; sa < max_sa; sa++) {
        VTSS_D("SA:%u  Dir:%s  Match idx:0x%x", sa, egr ? "Egress" : "Ingress", pattern->match);

        /* Disabled SAs are ignored */
        if (egr) {
            if (sa < 32) {
                CSR_RD(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1, &value);
                if ((VTSS_BIT(sa) & value) == 0) { // Not enabled
                    continue;
                }
            } else {
                CSR_RD(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE2, &value);
                if ((VTSS_BIT(sa - 32) & value) == 0) { // Not enabled
                    continue;
                }
            }
        } else {
            if (sa < 32) {
                CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1, &value);
                if ((VTSS_BIT(sa) & value) == 0) { // Not enabled
                    continue;
                }
            } else {
                CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE2, &value);
                if ((VTSS_BIT(sa - 32) & value) == 0) { // Not enabled
                    continue;
                }
            }
        }

        if (egr) {
            CSR_RD(p, VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR(sa), &value);
            if (VTSS_X_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DEST_PORT(value) == 2) {
                continue;     // ignore SA's for controlled port
            }
        } else {
            CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR(sa), &value);
            if (VTSS_X_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DEST_PORT(value) == 2) {
                continue;
            }
        }

        if (pattern->match & VTSS_MACSEC_MATCH_ETYPE) {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(sa)), &value);
            if (PST_DIR(VTSS_X, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_ETHER_TYPE(value)) != MACSEC_BS(pattern->etype)) {
                continue;
            }
        } else {
            CSR_RD(p,  PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(sa)), &value);
            if (PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_ETYPE_MASK) & value) {
                continue;
            }
        }

        if (pattern->match & VTSS_MACSEC_MATCH_VLAN_ID) {
            CSR_RD(p, PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI(sa)), &value);
            if (PST_DIR(VTSS_X, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_VLAN_ID(value)) != pattern->vid) {
                continue;
            }
        } else {
            CSR_RD(p, PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(sa)), &value);
            if (PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_MASK) & value) {
                continue;
            }
        }

        if (pattern->match & VTSS_MACSEC_MATCH_VLAN_ID_INNER) {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_EXT_MATCH(sa)), &value);
            if (PST_DIR(VTSS_X, egr, SA_MATCH_PARAMS_SAM_EXT_MATCH_VLAN_ID_INNER(value)) != pattern->vid_inner) {
                continue;
            }
        } else {
            CSR_RD(p, PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(sa)), &value);
            if (PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_VLAN_ID_INNER_MASK) & value) {
                continue;
            }
        }

        if (pattern->match & VTSS_MACSEC_MATCH_BYPASS_HDR) {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH1(sa)), &value);
            if (value != get_u32(&pattern->hdr[0])) {
                continue;
            }
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MATCH2(sa)), &value);
            if (value != get_u32(&pattern->hdr[4])) {
                continue;
            }

            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK1(sa)), &value);
            if (value != get_u32(&pattern->hdr_mask[0])) {
                continue;
            }

            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK2(sa)), &value);
            if (value != get_u32(&pattern->hdr_mask[4])) {
                continue;
            }
        } else {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK1(sa)), &value);
            if (value > 0) {
                continue;
            }
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_HDR_BYPASS_MASK2(sa)), &value);
            if (value > 0) {
                continue;
            }
        }

        if (pattern->match & VTSS_MACSEC_MATCH_IS_CONTROL) {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(sa)), &value);
            if (VTSS_BOOL((PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_CONTROL_PACKET) & value)) != pattern->is_control) {
                continue;

            }
        }
        if (pattern->match & VTSS_MACSEC_MATCH_HAS_VLAN) {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(sa)), &value);
            if (VTSS_BOOL((PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_VLAN_VALID) & value)) != pattern->has_vlan_tag) {
                continue;
            }
        }

        if (pattern->match & VTSS_MACSEC_MATCH_HAS_VLAN_INNER) {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(sa)), &value);
            if (VTSS_BOOL((PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_QINQ_FOUND) & value)) != pattern->has_vlan_inner_tag) {
                continue;
            }
        } else {
            CSR_RD(p, PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MASK(sa)), &value);
            if (PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_QINQ_FOUND_MASK) & value) {
                continue;
            }
        }

        CSR_RD(p, PST_DIR(VTSS,   egr, SA_MATCH_PARAMS_SAM_MISC_MATCH(sa)), &value);
        if ((u8)(PST_DIR(VTSS_X, egr, SA_MATCH_PARAMS_SAM_MISC_MATCH_MATCH_PRIORITY(value))) != (15 - pattern->priority)) {
            continue;
        }

        if (pattern->match & VTSS_MACSEC_MATCH_SMAC) {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_LO(sa)), &value);
            if (value != get_u32(&pattern->src_mac.addr[0])) {
                VTSS_D("Source MAC Lo not match, SA:%d", sa);
                continue;
            }

            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(sa)), &value);
            mac_addr = (pattern->src_mac.addr[5] << 8) | pattern->src_mac.addr[4];
            if (PST_DIR(VTSS_X, egr, SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI_MAC_SA_MATCH_15_TO_0(value)) != mac_addr) {
                VTSS_D("Source MAC Hi not match, SA:%d", sa);
                continue;
            }

        } else {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MASK(sa)), &value);
            if (PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_SA_MASK(value)) & value) {
                continue;
            }
        }

        if (pattern->match & VTSS_MACSEC_MATCH_DMAC) {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_LO(sa)), &value);
            if (value != get_u32(&pattern->dest_mac.addr[0])) {
                VTSS_D("Destination MAC Lo not match, SA:%d", sa);
                continue;
            }

            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI(sa)), &value);
            mac_addr = (pattern->dest_mac.addr[5] << 8) | pattern->dest_mac.addr[4];
            if (PST_DIR(VTSS_X,   egr, SA_MATCH_PARAMS_SAM_MAC_DA_MATCH_HI_MAC_DA_MATCH_15_TO_0(value)) != mac_addr) {
                VTSS_D("Destination MAC Hi not match, SA:%d", sa);
                continue;
            }
        } else {
            CSR_RD(p, PST_DIR(VTSS, egr, SA_MATCH_PARAMS_SAM_MASK(sa)), &value);
            if (PST_DIR(VTSS_F, egr, SA_MATCH_PARAMS_SAM_MASK_MAC_DA_MASK(value)) & value) {
                continue;
            }
        }

        VTSS_I("Found record:%d", sa);
        *record = sa;
        break;
    } // for each sa

    if (sa == max_sa) {
        VTSS_E("Record (sa) not found during warm start!");
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc record_empty_get(vtss_state_t *vtss_state,
                                vtss_port_no_t port_no, u32 *id, BOOL tx)
{
    u32 sa, max_sa;
    if (phy_is_1g(vtss_state, port_no)) {
        max_sa = VTSS_MACSEC_1G_MAX_SA;
    } else {
        max_sa = VTSS_MACSEC_10G_MAX_SA;
    }
    if (tx) {
        for (sa = 0; sa < max_sa; sa++) {
            if (!vtss_state->macsec_conf[port_no].tx_sa[sa].in_use) {
                *id = sa;
                return VTSS_RC_OK;
            }
        }
    } else {
        for (sa = 0; sa < max_sa; sa++) {
            if (!vtss_state->macsec_conf[port_no].rx_sa[sa].in_use) {
                *id = sa;
                return VTSS_RC_OK;
            }
        }
    }

    VTSS_D("All available SA's are in use");
    return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE);
}

static vtss_rc cp_rule_id_get(vtss_state_t *vtss_state, vtss_port_no_t port_no, const vtss_macsec_control_frame_match_conf_t *const conf,
                              u32 *indx, u32 *const rule, BOOL store)
{

    u32 i, etype_index;
    *indx = 0;
    if (phy_is_1g(vtss_state, port_no)) {
        etype_index = 10; // 8 Etypes for Viper
    } else {
        etype_index = 18; // 16 Etypes for Venice
    }

    if (!store) { /* find the index to be deleted */
        if (*rule < 2) {
            *indx = 8 + *rule;
        } else if (*rule < 18) {
            if (*rule < 10) {
                *indx = *rule - 2;
            } else {
                *indx = *rule;
            }
        } else {
            *indx =  *rule - 18;
        }
        return VTSS_RC_OK;
    }

    VTSS_N("conf->match:%d", conf->match);

    if ((conf->match & VTSS_MACSEC_MATCH_ETYPE) && (conf->match & VTSS_MACSEC_MATCH_DMAC)) {
        for (i = 0; i < 2; i++) {
            if (vtss_state->macsec_conf[port_no].glb.control_match[i].match == VTSS_MACSEC_MATCH_DISABLE) {
                if (rule != NULL) {
                    *rule = i;
                }
                *indx = 8 + i; // DMAC/ETYPE index 8-9
                return VTSS_RC_OK;
            }
        }
    } else if (conf->match & VTSS_MACSEC_MATCH_ETYPE)  {
        for (i = 2; i < etype_index; i++) {
            if (vtss_state->macsec_conf[port_no].glb.control_match[i].match == VTSS_MACSEC_MATCH_DISABLE) {
                if (rule != NULL) {
                    *rule = i;
                }
                if (i < 10) {
                    *indx = i - 2;  // ETYPE 0-7
                } else {
                    *indx = i;      // ETYPE 10-17
                }
                return VTSS_RC_OK;
            }
        }
    } else if (conf->match & VTSS_MACSEC_MATCH_DMAC) {
        for (i = 18; i < 26; i++) {
            if (vtss_state->macsec_conf[port_no].glb.control_match[i].match == VTSS_MACSEC_MATCH_DISABLE) {
                if (rule != NULL) {
                    *rule = i;
                }
                *indx =  i - 18; // DMAC 18-25
                return VTSS_RC_OK;
            }
        }
    } else if (conf->match & VTSS_MACSEC_MATCH_DISABLE) {
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_MATCH_DISABLE);
    } else {
        VTSS_E("Unexpected CP mode %u", conf->match);
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_UNEXPECT_CP_MODE);
    }

    VTSS_E("All CP rules of type '%s' are in use, rule:%d", (conf->match == VTSS_MACSEC_MATCH_ETYPE) ? "Etype" :
           (conf->match == VTSS_MACSEC_MATCH_DMAC) ? "DMAC" : "DMAC/Etype", *rule);
    return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE);
}


static u32 get_xform_value(vtss_state_t *vtss_state, vtss_port_no_t p, u32 i, BOOL egr, BOOL aes_128, vtss_macsec_internal_secy_t *secy, u16 an, u32 sc, u16 record)
{
    vtss_macsec_sak_t      *sak;

    if (egr) {
        sak = &secy->tx_sc.sa[an]->sak;
    } else {
        sak = &secy->rx_sc[sc]->sa[an]->sak;
    }

    if (i == 0) {
        if (egr) {
            return (0x9241E066 | ((aes_128 ? 0xB : 0xF) << 16) | (an << 26));
        } else {
            return (0xD241E06F | ((aes_128 ? 0xB : 0xF) << 16));
        }
    } else if (i == 1) {
        return get_new_context_id(vtss_state, p, egr, record);
    } else {
        if (aes_128) {
            if (i <= 5) {
                return get_u32(&sak->buf[0] + ((i - 2) * 4)); // AES Key 0-3, Record 2-5
            } else if (i <= 9) {
                return get_u32(&sak->h_buf[0] + ((i - 6) * 4)); // AES Hash 0-3 Record 6-9
            } else if (i == 10) {
                if (egr) {
                    return secy->tx_sc.sa[an]->status.next_pn; // Sequence / Next PN, Record 10
                } else {
                    // Sequence / lowest_pn = next_pn - replay_window, Record 10
                    return secy->rx_sc[sc]->sa[an]->status.lowest_pn + secy->rx_sc[sc]->conf.replay_window;
                }
            } else if (i == 11) {
                if (egr) {
                    return get_u32(&secy->sci.mac_addr.addr[0]); // SCI #0 / egr / Record 11
                } else {
                    return secy->rx_sc[sc]->conf.replay_window; // Replay window / ingr / Record 11
                }
            } else if (i == 12) {
                if (egr) {
                    return (secy->sci.mac_addr.addr[4] |
                            (secy->sci.mac_addr.addr[5] << 8) |
                            (MACSEC_BS(secy->sci.port_id) << 16)); // SCI #1 (egr) / Record 12
                } else {
                    return get_u32(&secy->rx_sc[sc]->sci.mac_addr.addr[0]); // SCI #0 / ingr / Record 12
                }
            } else if (i == 13 && !egr) {
                return (secy->rx_sc[sc]->sci.mac_addr.addr[4] |
                        (secy->rx_sc[sc]->sci.mac_addr.addr[5] << 8) |
                        (MACSEC_BS(secy->rx_sc[sc]->sci.port_id) << 16)); // SCI #1 / ingr / Record 13
            } else {
                return 0;
            }
        } else {
            // AES 256
            if (i <= 9) {
                return get_u32(&sak->buf[0] + ((i - 2) * 4)); // AES Key 0-7, Record 2-9
            } else if (i <= 13) {
                return get_u32(&sak->h_buf[0] + ((i - 10) * 4)); // AES Hash 0-3 Record 10-13
            } else if (i == 14) {
                if (egr) {
                    return secy->tx_sc.sa[an]->status.next_pn; // Sequence / Next PN, Record 14
                } else {
                    return secy->rx_sc[sc]->sa[an]->status.lowest_pn + secy->rx_sc[sc]->conf.replay_window;// Sequence / Lowest PN, Record 14
                }
            } else if (i == 15) {
                if (egr) {
                    return get_u32(&secy->sci.mac_addr.addr[0]); // SCI/IV #0
                } else {
                    return secy->rx_sc[sc]->conf.replay_window; // Replay window / ingr / Record 15
                }
            } else if (i == 16) {
                if (egr) {
                    return (secy->sci.mac_addr.addr[4] |
                            (secy->sci.mac_addr.addr[5] << 8) |
                            (MACSEC_BS(secy->sci.port_id) << 16)); // SCI #1 (egr)
                } else {
                    return get_u32(&secy->rx_sc[sc]->sci.mac_addr.addr[0]); // SCI #0
                }
            } else if (i == 17 && !egr) {
                return (secy->rx_sc[sc]->sci.mac_addr.addr[4] |
                        (secy->rx_sc[sc]->sci.mac_addr.addr[5] << 8) |
                        (MACSEC_BS(secy->rx_sc[sc]->sci.port_id) << 16)); // SCI #1 (ingr)
            } else {
                return 0;
            }
        }
    }
}

static u32 get_xform_value_64(vtss_state_t *vtss_state, vtss_port_no_t p, u32 i, BOOL egr, BOOL aes_128, vtss_macsec_internal_secy_t *secy, u16 an, u32 sc, u16 record)
{
    vtss_macsec_sak_t *sak;
    u64               temp2;

    if (egr) {
        sak = &secy->tx_sc.sa[an]->sak;
    } else {
        sak = &secy->rx_sc[sc]->sa[an]->sak;
    }

    if (i == 0) {
        if (egr) {
            return (0xA241E066 | ((aes_128 ? 0xB : 0xF) << 16) | (an << 26));
        } else {
            return (0xE241A0EF | ((aes_128 ? 0xB : 0xF) << 16));
        }
    } else if (i == 1) {
        return get_new_context_id(vtss_state, p, egr, record);
    } else {
        if (aes_128) {
            if (i <= 5) {
                return get_u32(&sak->buf[0] + ((i - 2) * 4)); // AES Key 0-3, Record 2-5
            } else if (i <= 9) {
                return get_u32(&sak->h_buf[0] + ((i - 6) * 4)); // AES Hash 0-3 Record 6-9
            } else if (i == 10) {
                if (egr) {
                    return (u32)secy->tx_sc.sa[an]->status.pn_status.next_pn.xpn;// Sequence / Next PN, LSW, Record 10
                } else {
                    temp2 = secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn.xpn + secy->rx_sc[sc]->conf.replay_window;
                    return (u32)temp2; // Next PN, LSW, Record 10
                }
            } else if (i == 11) {
                if (egr) {
                    return (u32)(secy->tx_sc.sa[an]->status.pn_status.next_pn.xpn >> 32);// Sequence / Next PN, MSW, Record 11
                } else {
                    temp2 = secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn.xpn + secy->rx_sc[sc]->conf.replay_window;
                    return (u32)(temp2 >> 32); //Next PN, MSW, Record 11
                }
            } else if (i == 12) {
                if (egr) {
                    return 0;
                } else {
                    if (secy->rx_sc[sc]->conf.replay_window <= MACSEC_REVB_REPLAY_WINDOW_SIZE) { /* Replay window size should not exceed 2^30 */
                        return secy->rx_sc[sc]->conf.replay_window; // Mask, replay window, Record 12
                    } else {
                        return 0;
                    }
                }
            } else if (i == 13) {
                if (egr) {
                    return get_u32(sak->salt.buf) ^ get_u32(secy->tx_sc.sa[an]->ssci.buf); //IS0, IV0, context salt, Record 13
                } else {
                    return get_u32(sak->salt.buf) ^ get_u32(secy->rx_sc[sc]->sa[an]->ssci.buf);
                }
            } else if (i == 14) {
                return get_u32(&sak->salt.buf[4]); //IS1, IV1, context salt, Record 14
            } else if (i == 15) {
                return get_u32(&sak->salt.buf[8]); //IS2, IV2, context salt, Record 15
            } else if (i == 16 && egr) {
                return get_u32(&secy->sci.mac_addr.addr[0]); // SCI #0
            } else if (i == 17 && egr) {
                return (secy->sci.mac_addr.addr[4] |
                        (secy->sci.mac_addr.addr[5] << 8) |
                        (MACSEC_BS(secy->sci.port_id) << 16)); // SCI #1 (egr)
            } else {
                return 0;
            }
        } else {
            // AES 256
            if (i <= 9) {
                return get_u32(&sak->buf[0] + ((i - 2) * 4)); // AES Key 0-7, Record 2-9
            } else if (i <= 13) {
                return get_u32(&sak->h_buf[0] + ((i - 10) * 4)); // AES Hash 0-3 Record 10-13
            } else if (i == 14) {
                if (egr) {
                    return (u32)secy->tx_sc.sa[an]->status.pn_status.next_pn.xpn;// Sequence / Next PN, LSW, Record 14
                } else {
                    temp2 = secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn.xpn + secy->rx_sc[sc]->conf.replay_window;
                    return (u32)temp2; // Sequence / Next PN, LSW, Record 14
                }
            } else if (i == 15) {
                if (egr) {
                    return (u32)(secy->tx_sc.sa[an]->status.pn_status.next_pn.xpn >> 32); // Sequence / Next PN, MSW, Record 15
                } else {
                    temp2 = secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn.xpn + secy->rx_sc[sc]->conf.replay_window;
                    return (u32)(temp2 >> 32); //Sequence, MSW, Record 15
                }
            } else if (i == 16) {
                if (egr) {
                    return 0;
                } else {
                    if (secy->rx_sc[sc]->conf.replay_window <= MACSEC_REVB_REPLAY_WINDOW_SIZE) { /* Replay window size should not exceed 2^30 */
                        return secy->rx_sc[sc]->conf.replay_window; //Mask, Replay window
                    } else {
                        return 0;
                    }
                }
            } else if (i == 17) {
                if (egr) {
                    return get_u32(sak->salt.buf) ^ get_u32(secy->tx_sc.sa[an]->ssci.buf); //IS0, IV0, context salt, Record 13
                } else {
                    return get_u32(sak->salt.buf) ^ get_u32(secy->rx_sc[sc]->sa[an]->ssci.buf);
                }
            } else if (i == 18) {
                return get_u32(&sak->salt.buf[4]); // IS1, IV1, context salt
            } else if (i == 19) {
                return get_u32(&sak->salt.buf[8]); // IS2, IV2, context salt
            } else if (i == 20 && egr) {
                return get_u32(&secy->sci.mac_addr.addr[0]); // SCI #0
            } else if (i == 21 && egr) {
                return (secy->sci.mac_addr.addr[4] |
                        (secy->sci.mac_addr.addr[5] << 8) |
                        (MACSEC_BS(secy->sci.port_id) << 16)); // SCI #1 (egr)
            } else {
                return 0;
            }
        }
    }
}

static vtss_rc macsec_sa_xform_set(vtss_state_t *vtss_state, vtss_port_no_t p, BOOL egr, u32 record,
                                   vtss_macsec_internal_secy_t *secy, u16 an, u32 sc)
{
    BOOL aes_128;
    BOOL xpn = FALSE;
    u32 i;
    u8 xform_rec_size = (egr & vtss_state->macsec_conf[p].glb.macsec_revb) ? 24 : 20;

    VTSS_D("Record:%u SC:%u SA:%u  Dir:%s ", record, sc, an, egr ? "Egress" : "Ingress");

    if (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
        secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) {
        xpn = TRUE;
    }
    if (vtss_state->sync_calling_private ||
        vtss_state->macsec_conf[p].glb.spd_change_macsec_recfg) {
        return VTSS_RC_OK;
    }
    if (xpn != TRUE) {
        aes_128 = (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128) ? 1 : 0;

        for (i = 0; i < xform_rec_size; i++) {
            if (egr) {
                VTSS_RC(csr_wr(vtss_state, p, 0x1f, 1, ((0x8000 + i) | (record * 32)), get_xform_value(vtss_state, p, i, egr, aes_128, secy, an, sc, record)));
            } else {
                VTSS_RC(csr_wr(vtss_state, p, 0x1f, 1, ((0x0000 + i) | (record * 32)), get_xform_value(vtss_state, p, i, egr, aes_128, secy, an, sc, record)));
            }
        }
    } else {
        aes_128 = (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ? TRUE : FALSE;

        for (i = 0; i < 24; i++) {
            if (egr) {
                VTSS_RC(csr_wr(vtss_state, p, 0x1f, 1, ((0x8000 + i) | (record * 32)), get_xform_value_64(vtss_state, p, i, egr, aes_128, secy, an, sc, record)));
            } else {
                if (i >= 20 ) {
                    break;
                }
                VTSS_RC(csr_wr(vtss_state, p, 0x1f, 1, ((0x0000 + i) | (record * 32)), get_xform_value_64(vtss_state, p, i, egr, aes_128, secy, an, sc, record)));
            }
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc macsec_sa_xform_reset(vtss_state_t *vtss_state,
                                     vtss_port_no_t p,
                                     BOOL egr,
                                     u32 record,
                                     vtss_macsec_internal_secy_t *secy,
                                     u16 an,
                                     u32 sc)
{
    u32 i, count = 0;

    VTSS_D("Record:%u SC:%u SA:%u  Dir:%s ", record, sc, an, egr ? "Egress" : "Ingress");

    if (vtss_state->sync_calling_private) {
        return VTSS_RC_OK;
    }

    if (egr & (vtss_state->macsec_conf[p].glb.macsec_revb == TRUE)) {
        count = 24;
    } else {
        count = 20;
    }
    for (i = 0; i < count; i++) {
        if (egr) {
            VTSS_RC(csr_wr(vtss_state, p, 0x1f, 1, ((0x8000 + i) | (record * 32)), 0));
        } else {
            VTSS_RC(csr_wr(vtss_state, p, 0x1f, 1, ((0x0000 + i) | (record * 32)), 0));
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc record_inuse_get(vtss_state_t *vtss_state, vtss_port_no_t p, BOOL egr,
                                vtss_macsec_internal_secy_t *secy, u16 an, u32 sc, u32 *record)
{
    BOOL aes_128 = FALSE;
    BOOL found = FALSE;
    u32 i, max_sa, sa, value, xform_val = 0;
    BOOL xpn = FALSE;

#ifdef VTSS_CHIP_CU_PHY
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[p];
    BOOL is_phy_1g = (ps->type.part_number != VTSS_PHY_TYPE_NONE);

    CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1, &value);
    if ((is_phy_1g) && (value == 0)) {
         vtss_macsec_store_sa(vtss_state, p, 0);
    }
#endif

    if (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
        secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) {
        xpn = TRUE;
    }
    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128)) {
        aes_128 = TRUE;
    }

    if (phy_is_1g(vtss_state, p)) {
        max_sa = VTSS_MACSEC_1G_MAX_SA;
    } else {
        max_sa = VTSS_MACSEC_10G_MAX_SA;
    }

    for (sa = 0; sa < max_sa; sa++) {
        if (egr) {
            if (vtss_state->macsec_conf[p].tx_sa[sa].in_use) {
                continue;
            }

            CSR_RD(p, VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR(sa), &value);
            if (VTSS_X_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_DEST_PORT(value) != 2) {
                continue;
            }
            /* Use SCI to find out record used before warmstart */
            VTSS_RC(csr_rd(vtss_state, p, 0x1f, 1, (0x8000 + ((xpn ? (aes_128 ? 16 : 20) : (aes_128 ? 11 : 15)) | (sa * 32))), &value));
            xform_val = (xpn == TRUE ? get_xform_value_64(vtss_state, p, aes_128 ? 16 : 20, egr, aes_128, secy, an, sc, sa) :
                         get_xform_value(vtss_state, p, aes_128 ? 11 : 15, egr, aes_128, secy, an, sc, sa));
            if (xform_val != value) {
                continue;
            }
            VTSS_RC(csr_rd(vtss_state, p, 0x1f, 1, (0x8000 + ((xpn ? (aes_128 ? 17 : 21) : (aes_128 ? 12 : 16)) | (sa * 32))), &value));
            xform_val = (xpn == TRUE ? get_xform_value_64(vtss_state, p, aes_128 ? 17 : 21, egr, aes_128, secy, an, sc, sa) :
                         get_xform_value(vtss_state, p, aes_128 ? 12 : 16, egr, aes_128, secy, an, sc, sa));
            if (xform_val != value) {
                continue;
            }
            /* Use AN to match record having same SCI */
            VTSS_RC(csr_rd(vtss_state, p, 0x1f, 1, (0x8000 | (sa * 32)), & value));
            xform_val = (xpn ? get_xform_value_64(vtss_state, p, 0, egr, aes_128, secy, an, sc, sa) :
                         get_xform_value(vtss_state, p, 0, egr, aes_128, secy, an, sc, sa));
            if (xform_val != value) {
                continue;
            }
        } else {
            if (vtss_state->macsec_conf[p].rx_sa[sa].in_use) {
                continue;
            }
            if (sa < 32) {
                CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1, &value);
                if ((VTSS_BIT(sa) & value) == 0) { // Not enabled
                    continue;
                }
            } else {
                CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE2, &value);
                if ((VTSS_BIT(sa - 32) & value) == 0) { // Not enabled
                    continue;
                }
            }
            CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR(sa), &value);
            if (VTSS_X_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_DEST_PORT(value) != 2) {
                continue;
            }
            /* Use SCI to find out record used before warmstart */
            CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_LO(sa), &value);
            if (value != get_u32(&secy->rx_sc[sc]->sci.mac_addr.addr[0])) {
                continue;
            }
            CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_SCI_MATCH_HI(sa), &value);
            xform_val = (secy->rx_sc[sc]->sci.mac_addr.addr[4] | (secy->rx_sc[sc]->sci.mac_addr.addr[5] << 8)
                         | (MACSEC_BS(secy->rx_sc[sc]->sci.port_id) << 16));
            if (value != xform_val) {
                continue;
            }
            /* Use AN to match record having same SCI */
            CSR_RD(p, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(sa), &value);
            if (an != VTSS_EXTRACT_BITFIELD(value, 24, 2)) {
                continue;
            }
        }

        found = 1;
        if (xpn == FALSE) {
            for (i = 0; i < 20; i++) {
                if (i == 1) {
                    continue;
                }
                if ((aes_128 && (i == 10)) || (!aes_128 && (i == 14))) {
                    continue;
                }
                VTSS_RC(csr_rd(vtss_state, p, 0x1f, 1, (((egr ? 0x8000 : 0) + i) | (sa * 32)), &value));
                if (get_xform_value(vtss_state, p, i, egr, aes_128, secy, an, sc, sa) != value) {
                    found = 0;
                    break;
                }
            }
        } else { /* Rev B Transform comparison */
            for (i = 0; i < 24; i++) {
                if (!egr && i >= 20) {
                    break;
                }
                if (i == 1) {
                    continue;
                }
                if ((aes_128 && ((i == 10) || (i == 11))) || (!aes_128 && ((i == 14) || (i == 15)))) {
                    continue;
                }
                VTSS_RC(csr_rd(vtss_state, p, 0x1f, 1, (((egr ? 0x8000 : 0) + i) | (sa * 32)), &value));
                if (get_xform_value_64(vtss_state, p, i, egr, aes_128, secy, an, sc, 0) != value) {
                    found = 0;
                    break;
                }
            }
        }

        if (found) {
            /* Update ingress flow map from hardware in vtss_state during warmstart */
            if (!egr) {
                update_flow_map_hw(vtss_state, p, sa);
            }
            *record = sa;
            VTSS_I("Found in use record:%d", sa);
            return VTSS_RC_OK;
        }
    }
    VTSS_E("NO record found");
    return VTSS_RC_ERROR;
}


static vtss_rc macsec_sa_enable(vtss_state_t *vtss_state, vtss_port_no_t p, u32 record, BOOL egr, BOOL enable)
{
    VTSS_D("%s sa:%u dir:%s", enable ? "Enable" : "Disable", record, egr ? "egr" : "ingr" );
    if (enable) {
        if (egr) {
            if (record < 32) {
                CSR_COLD_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET1, (1 << record));
            } else {
                CSR_COLD_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET2, (1 << (record - 32)));
                CSR_COLD_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET1, 0); // SAs above 31 requires 2 writes
            }
        } else {
            if (record < 32) {
                CSR_COLD_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET1, (1 << record));
            } else {
                CSR_COLD_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET2, (1 << (record - 32)));
                CSR_COLD_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_SET1, 0); // SAs above 31 requires 2 writes
            }
        }
    } else {
        if (egr) {
            if (record < 32) {
                CSR_COLD_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR1, (1 << record));
            } else {
                CSR_COLD_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR2, (1 << (record - 32)));
                CSR_COLD_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR1, 0); // SAs above 31 requires 2 writes
            }
        } else {
            if (record < 32) {
                CSR_COLD_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR1, (1 << record));
            } else {
                CSR_COLD_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR2, (1 << (record - 32)));
                CSR_COLD_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR1, 0); // SAs above 31 requires 2 writes
            }
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc macsec_sa_inuse(vtss_state_t *vtss_state, vtss_port_no_t p, u32 record, BOOL egr, BOOL enable)
{
    VTSS_D("Set sa_inuse bit: sa:%d dir:%s enable:%d", record, egr ? "egr" : "ingr", enable );
    if (egr) {
        CSR_WARM_WRM(p, VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR(record),
                     (enable ? VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_SA_IN_USE : 0),
                     VTSS_F_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR_SA_IN_USE);
    } else {
        CSR_WARM_WRM(p, VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR(record),
                     (enable ? VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_SA_IN_USE : 0),
                     VTSS_F_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR_SA_IN_USE);
    }
    return VTSS_RC_OK;
}

static vtss_rc macsec_sa_toggle(vtss_state_t *vtss_state, vtss_port_no_t p, u32 new_record, u32 old_record, BOOL egr)
{

    VTSS_D("Toggle old tx sa:%u -> new tx sa:%u dir:%s", old_record, new_record, egr ? "egr" : "ingr" );
    if (!egr) { /* INGRESS */
        if ((old_record < 32 && new_record < 32) ||  (old_record >= 32 && new_record >= 32)) {
            /* Deactivate the old SA and activate new SA in one atomic write */
            if (old_record < 32) {
                CSR_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1,
                       ((1 << old_record) | (1 << new_record)));
            } else {
                CSR_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE2,
                       ((1 << (old_record - 32)) | (1 << (new_record - 32))));
                CSR_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1, 0);
            }
        } else {
            /* The SA's are not accessable through a single register - 2 writes are needed */
            if (old_record < 32) {
                CSR_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE2,
                       1 << (new_record - 32 ));
                CSR_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1,
                       1 << (old_record ));
            } else {
                CSR_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE2,
                       1 << (old_record - 32 ));
                CSR_WR(p, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1,
                       1 << (new_record ));
            }
        }
    } else {   /* EGRESS */
        if ((old_record < 32 && new_record < 32) ||  (old_record >= 32 && new_record >= 32)) {
            /* Deactivate the old SA and activate new SA in one atomic write */
            if (old_record < 32) {
                CSR_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1,
                       ((1 << old_record) | (1 << new_record)));
            } else {
                CSR_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE2,
                       ((1 << (old_record - 32)) | (1 << (new_record - 32))));
                CSR_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1, 0);
            }
        } else {
            /* The SA's are not accessable through a single register - 2 writes are needed */
            if (old_record < 32) {
                CSR_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE2,
                       1 << (new_record - 32 ));
                CSR_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1,
                       1 << (old_record ));
            } else {
                CSR_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE2,
                       1 << (old_record - 32 ));
                CSR_WR(p, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_TOGGLE1,
                       1 << (new_record ));
            }
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_pattern_set_priv(vtss_state_t                       *vtss_state,
                                            const vtss_port_no_t               port_no,
                                            const u32                          secy_id,
                                            const vtss_macsec_direction_t      direction,
                                            const vtss_macsec_match_action_t   action,
                                            const vtss_macsec_match_pattern_t  *const pattern,
                                            u32                                 rule_id)
{
    vtss_macsec_internal_secy_t *secy = (secy_id == MACSEC_SECY_NONE) ? NULL : &vtss_state->macsec_conf[port_no].secy[secy_id];
    BOOL egr = (direction == VTSS_MACSEC_DIRECTION_EGRESS) ? 1 : 0;
    u32 record, i;
    vtss_macsec_match_pattern_t match = *pattern;

    if (pattern->match == 0) {
        return VTSS_RC_OK; // Nothing to do
    }
    if ((secy != NULL) && (secy->pattern_record[action][direction] != MACSEC_NOT_IN_USE) && (!vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg)) {
        VTSS_E("Pattern already in use for port:%d secy_id:%d egr:%d action:%d\n", port_no, secy_id, egr, action);
        return VTSS_RC_ERROR;
    }

    /* In case of VLAN tag as ether type for CP, must replace IS_CONTROL with HAS_VLAN - only ingress */
    if (!egr) {
        for (i = 0; i < VTSS_MACSEC_CP_RULES; i++) {
            if ((vtss_state->macsec_conf[port_no].glb.control_match[i].etype == 0x8100) &&
                (vtss_state->macsec_conf[port_no].glb.control_match[i].match == VTSS_MACSEC_MATCH_ETYPE)) {
                match.match = (match.match | VTSS_MACSEC_MATCH_HAS_VLAN) & (0xFFFFFFFF ^ (VTSS_MACSEC_MATCH_IS_CONTROL));
                match.has_vlan_tag = 1;
            }
        }
    }

    if (vtss_state->sync_calling_private) {
        // Find a matching record
        if (macsec_sa_match_warm_start_get(vtss_state, port_no, egr, &match, &record) != VTSS_RC_OK) {
            vtss_state->macsec_conf[port_no].glb.warm_start_reg_changed = TRUE; // Signaling that a register for this port has changed.
        }
    } else {
        if (vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg) {
            if (secy != NULL) {
                record = secy->pattern_record[action][direction];
            } else {
                if (record_empty_get(vtss_state, port_no, &record, egr) != VTSS_RC_OK) {
                    VTSS_E("Could not get an empty record");
                    return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_EMPTY_RECORD);
                }
            }
        } else {
            if (record_empty_get(vtss_state, port_no, &record, egr) != VTSS_RC_OK) {
                VTSS_E("Could not get an empty record");
                return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_EMPTY_RECORD);
            }
        }
    }

    if (pattern->priority > VTSS_MACSEC_MATCH_PRIORITY_LOWEST) {
        VTSS_E("The pattern priority is not valid");
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID);
    }
    VTSS_D("SA:%u Action:%s Dir:%s", record, (action == 0) ? "Drop" : (action == 1) ? "Ctrl" : "Unctrl",  egr ? "egr" : "ingr");

    if (egr) {
        vtss_state->macsec_conf[port_no].tx_sa[record].record = record;
        vtss_state->macsec_conf[port_no].tx_sa[record].in_use = 1;
    } else {
        vtss_state->macsec_conf[port_no].rx_sa[record].record = record;
        vtss_state->macsec_conf[port_no].rx_sa[record].in_use = 1;
    }
    if (secy != NULL) {
        secy->pattern_record[action][direction] = record;
    } else {
        vtss_state->macsec_conf[port_no].glb.egr_bypass_record[rule_id] = record;
    }

    if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
        if (macsec_sa_match_set(vtss_state, port_no, egr, record, &match, secy, 0, 0, 0,
                                (action == 1 ? 0 : 1)) != VTSS_RC_OK) {
            VTSS_E("Could not program the SA match, port_no:%d  secy_id:%d", port_no, secy_id);
            return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
        }
    } else {
        if (macsec_sa_match_set(vtss_state, port_no, egr, record, &match, secy, 0, 0, 0,
                                0) != VTSS_RC_OK) {
            VTSS_E("Could not program the SA match, port_no:%d  secy_id:%d", port_no, secy_id);
            return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
        }
    }

    if (macsec_sa_flow_set(vtss_state, port_no, egr, record, NULL, 0, 0, action) != VTSS_RC_OK) {
        VTSS_E("Could not program the SA flow, port_no:%d, secy_id:%d", port_no, secy_id);
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }
    if (macsec_sa_enable(vtss_state, port_no, record, egr, MACSEC_ENABLE) != VTSS_RC_OK) {
        VTSS_E("Could not enable the SA:%u, port_no:%d, secy_id:%d", record, port_no, secy_id);
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }
    if (macsec_sa_inuse(vtss_state, port_no, record, egr, MACSEC_ENABLE) != VTSS_RC_OK) {
        VTSS_E("Could not set SA:%u to 'in_use, port_no:%d, secy_id:%d", record, port_no, secy_id);
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_bypass_mode_set_priv(vtss_state_t                     *vtss_state,
                                                const vtss_port_no_t             port_no,
                                                const vtss_macsec_bypass_mode_t  *const bypass)
{
    if (bypass->mode == VTSS_MACSEC_BYPASS_HDR) {
        if (bypass->hdr_bypass_len > 16 || bypass->hdr_bypass_len == 0 || (bypass->hdr_bypass_len % 2)) {
            VTSS_E("Invalid header bypass length:%d, port_no:%d", bypass->hdr_bypass_len, port_no);
            return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN);
        }
        CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL,
                    VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_ETYPE_MATCH(MACSEC_BS(bypass->hdr_etype)) |
                    VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HDR_BYPASS_LEN(bypass->hdr_bypass_len / 2 + 7) | /* len is 8-15 */
                    VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_E_TYPE_MATCH_EN);

        CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL,
                    VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_ETYPE_MATCH(MACSEC_BS(bypass->hdr_etype)) |
                    VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HDR_BYPASS_LEN(bypass->hdr_bypass_len / 2 + 7) | /* len is 8-15 */
                    VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_HB_E_TYPE_MATCH_EN);

    } else if (bypass->mode == VTSS_MACSEC_BYPASS_TAG) {
        CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL,
                    VTSS_F_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_SECTAG_AFTER_VLAN);

        CSR_WARM_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL,
                    VTSS_F_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_HDR_EXT_CTRL_SECTAG_AFTER_VLAN);
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_rx_sa_disable_priv(vtss_state_t              *vtss_state,
                                              const u32                 secy_id,
                                              const vtss_macsec_port_t  port,
                                              const vtss_macsec_sci_t   *const sci,
                                              const u16                 an)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 sc;
    mepa_timeofday_t tod;
    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    VTSS_RC(sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc));

    VTSS_MACSEC_ASSERT(secy->rx_sc[sc] == NULL, "SC does not exist");

    if (secy->rx_sc[sc]->sa[an] == NULL) {
        VTSS_I("AN:%d does not exist, secyid:%d, port_no:%d", an, secy_id, port.port_no);
        VTSS_RC(dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_AN_NOT_EXIST));
    }

    if (macsec_sa_inuse(vtss_state, port.port_no, secy->rx_sc[sc]->sa[an]->record, INGRESS, MACSEC_DISABLE) != VTSS_RC_OK) {
        VTSS_E("Could not set SA:%u to 'in_use, port_no:%d, secy_id:%d", secy->rx_sc[sc]->sa[an]->record, port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }

    secy->rx_sc[sc]->sa[an]->status.in_use = 0;
    secy->rx_sc[sc]->sa[an]->enabled = 0;

    MEPA_TIME_OF_DAY(tod);
    secy->rx_sc[sc]->sa[an]->status.stopped_time = tod.sec; // TimeOfDay in seconds
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_tx_sa_disable_priv(vtss_state_t              *vtss_state,
                                              const u32                 secy_id,
                                              const vtss_macsec_port_t  port,
                                              const u16                 an)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    mepa_timeofday_t tod;

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    if (secy->tx_sc.sa[an] == NULL) {
        VTSS_I("AN:%d does not exist, secyid:%d, port_no:%d", an, secy_id, port.port_no);
        VTSS_RC(dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_AN_NOT_EXIST));
    }

    /* Disable chip SA Flow */
    if (macsec_sa_enable(vtss_state, port.port_no, secy->tx_sc.sa[an]->record, EGRESS, MACSEC_DISABLE) != VTSS_RC_OK) {
        VTSS_E("Could not disable the AN:%u", an);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN);
    }
    if (macsec_sa_inuse(vtss_state, port.port_no, secy->tx_sc.sa[an]->record, EGRESS, MACSEC_DISABLE) != VTSS_RC_OK) {
        VTSS_E("Could not set SA:%u to 'in_use, port_no:%d, secy_id:%d", secy->tx_sc.sa[an]->record, port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }

    // Update TX SA/SC/SecY counters
    secy->tx_sc.sa[an]->status.in_use = 0;
    secy->tx_sc.sa[an]->enabled = 0;
    if (an == secy->tx_sc.status.encoding_sa) {
        secy->tx_sc.status.encoding_sa = 0;
        secy->tx_sc.status.enciphering_sa = 0;
    }
    MEPA_TIME_OF_DAY(tod);
    secy->tx_sc.sa[an]->status.stopped_time = tod.sec; // TimeOfDay in seconds
    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_control_frame_match_conf_set_priv(vtss_state_t                                 *vtss_state,
                                                             const vtss_port_no_t                         port_no,
                                                             const vtss_macsec_control_frame_match_conf_t *const conf,
                                                             u32                                          *const rule_id,
                                                             BOOL                                          store)
{
    u32 i, parsed_etype = 1, indx, record;

    /* Get the next available index for CP rule */
    if (vtss_state->sync_calling_private ||
        vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg) {
        VTSS_RC(cp_rule_id_get(vtss_state, port_no, conf, &indx, rule_id, 0)); // Already have the rule, get the rule indx
    } else {
        VTSS_RC(cp_rule_id_get(vtss_state, port_no, conf, &indx, rule_id, store));
    }

    if (vtss_state->warm_start_cur) {
        return VTSS_RC_OK;
    }

    if ((vtss_state->macsec_conf[port_no].glb.bypass_mode.mode == VTSS_MACSEC_BYPASS_HDR) ||
        ((conf->match & VTSS_MACSEC_MATCH_ETYPE) && (conf->etype == 0x8100))) {
        parsed_etype = 0;
    }

    /* Apply to both ingress and egress */
    for (i = 0; i < 2; i++) {
        if (conf->match & VTSS_MACSEC_MATCH_ETYPE) {
            /* Use parsed Etype, after VLAN (if there is one) expect for configurations as above */
            if (indx < 10) {
                CSR_WARM_WRM(port_no,
                             PST_DIR(VTSS, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE),
                             PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_9_TO_0(parsed_etype ? VTSS_BIT(indx) : 0)),
                             PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_9_TO_0(parsed_etype ? VTSS_BIT(indx) : 0)));
            } else {
                CSR_WARM_WRM(port_no,
                             PST_DIR(VTSS, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE),
                             PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_17_TO_10(parsed_etype ? VTSS_BIT(indx - 10) : 0)),
                             PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_MODE_ETYPE_SEL_17_TO_10(parsed_etype ? VTSS_BIT(indx - 10) : 0)));
            }
        }

        if ((conf->match & VTSS_MACSEC_MATCH_ETYPE) && (conf->match & VTSS_MACSEC_MATCH_DMAC)) {
            /* DMAC AND Etype => index 8-9 */
            CSR_WARM_WR(port_no,
                        PST_DIR(VTSS, i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_MATCH(indx)), get_u32(&conf->dmac.addr[0]));

            CSR_WARM_WR(port_no,
                        PST_DIR(VTSS,   i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH(indx)),
                        PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0(conf->dmac.addr[5] << 8  | conf->dmac.addr[4])) |
                        PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(MACSEC_BS(conf->etype))));

            /* Enable */
            CSR_WARM_WRM(port_no,
                         PST_DIR(VTSS, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE),
                         (!store ? 0 : PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_COMB_ENABLE_9_TO_8(indx == 8 ? 1 : 2))),
                         PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_COMB_ENABLE_9_TO_8(indx == 8 ? 1 : 2)));

        } else if (conf->match & VTSS_MACSEC_MATCH_ETYPE) {
            /* Etype ONLY => use index 0-7,10-17 */
            if (indx < 8) {
                /* /\* Etype *\/ */
                CSR_WARM_WRM(port_no,
                             PST_DIR(VTSS,   i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH(indx)),
                             PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(MACSEC_BS(conf->etype))),
                             PST_DIR(VTSS_M, i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH));

                /* Enable */
                CSR_WARM_WRM(port_no,
                             PST_DIR(VTSS, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE),
                             (!store ? 0 : PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_7_TO_0(VTSS_BIT(indx)))),
                             PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_7_TO_0(VTSS_BIT(indx))));
            } else {
                /* Etype */
                CSR_WARM_WR(port_no, VTSS_IOREG(0x1f, 1, (i ? 0x9e14 : 0x1e14) + (indx - 10)), // Workaround for a bug in Register List
                            VTSS_F_MACSEC_INGR_CTL_PACKET_CLASS_PARAMS_CP_MAC_ET_MATCH_ETHER_TYPE(MACSEC_BS(conf->etype)));

                /* Enable */
                CSR_WARM_WRM(port_no,
                             PST_DIR(VTSS, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE),
                             (!store ? 0 : PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_17_TO_10(VTSS_BIT(indx - 10)))),
                             PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_ETYPE_ENABLE_17_TO_10(VTSS_BIT(indx - 10))));
            }
        } else if (conf->match & VTSS_MACSEC_MATCH_DMAC) {
            /* DMAC ONLY => use index 0-7 */
            CSR_WARM_WR(port_no,
                        PST_DIR(VTSS, i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_MATCH(indx)), get_u32(&conf->dmac.addr[0]));

            CSR_WARM_WRM(port_no,
                         PST_DIR(VTSS,   i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH(indx)),
                         PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0(conf->dmac.addr[5] << 8 | conf->dmac.addr[4])),
                         PST_DIR(VTSS_M, i, CTL_PACKET_CLASS_PARAMS_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_TO_0));

            /* Enable */
            CSR_WARM_WRM(port_no,
                         PST_DIR(VTSS, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE),
                         (!store ? 0 : PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_MAC_DA_ENABLE_7_TO_0(VTSS_BIT(indx)))),
                         PST_DIR(VTSS_F, i, CTL_PACKET_CLASS_PARAMS2_CP_MATCH_ENABLE_MAC_DA_ENABLE_7_TO_0(VTSS_BIT(indx))));
        } else if (conf->match & VTSS_MACSEC_MATCH_DISABLE) {
            VTSS_E("Use vtss_macsec_control_frame_match_conf_del() to delete a rule");
            return VTSS_RC_ERROR;
        } else {
            VTSS_E("No control frame match, port_no:%d", port_no);
            return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH);
        }
    }

    if (vtss_state->macsec_conf[port_no].glb.macsec_revb != TRUE) {
        /* Workaround for Tagged frames with matching ETYPE in Rev A*/
        if (store && conf->match == VTSS_MACSEC_MATCH_ETYPE) {
            vtss_macsec_match_pattern_t pattern;
            memset(&pattern, 0, sizeof(pattern));
            if (conf->etype == 0x8100) {
                pattern.match = VTSS_MACSEC_MATCH_HAS_VLAN;
                pattern.has_vlan_tag = 1;
            } else {
                pattern.match = VTSS_MACSEC_MATCH_ETYPE |  VTSS_MACSEC_MATCH_HAS_VLAN;
                pattern.etype = conf->etype;
                pattern.has_vlan_tag = 1;
            }
            pattern.priority = 0;
            if ((vtss_macsec_pattern_set_priv(vtss_state, port_no, MACSEC_SECY_NONE, VTSS_MACSEC_DIRECTION_EGRESS,
                                              VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT, &pattern, *rule_id)) != VTSS_RC_OK) {
                VTSS_E("Could no set bypass pattern for CP rule");
                return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN);
            }
        }
        /* Remove the workaround and delete the API internals  */
        if (!store && vtss_state->macsec_conf[port_no].glb.egr_bypass_record[*rule_id] != MACSEC_NOT_IN_USE) {
            record = vtss_state->macsec_conf[port_no].glb.egr_bypass_record[*rule_id];
            if (macsec_sa_enable(vtss_state, port_no, record, EGRESS, MACSEC_DISABLE) != VTSS_RC_OK) {
                VTSS_E("Could not enable the SA, port_no:%d, record:%d", port_no, record);
                return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
            }
            if (macsec_sa_inuse(vtss_state, port_no, record, EGRESS, MACSEC_DISABLE) != VTSS_RC_OK) {
                VTSS_E("Could not set SA:%u to 'in_use, port_no:%d", record, port_no);
                return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
            }

            vtss_state->macsec_conf[port_no].tx_sa[record].in_use = 0;
            vtss_state->macsec_conf[port_no].glb.egr_bypass_record[*rule_id] = MACSEC_NOT_IN_USE;
            vtss_state->macsec_conf[port_no].glb.control_match[*rule_id].match = VTSS_MACSEC_MATCH_DISABLE;
        }
    }

    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_rx_sa_get_priv(vtss_state_t                  *vtss_state,
                                          const u32                     secy_id,
                                          const vtss_macsec_port_t      port,
                                          const vtss_macsec_sci_t       *const sci,
                                          const u16                     an,
                                          vtss_macsec_pkt_num_t         *const lowest_pn,
                                          vtss_macsec_sak_t             *const sak,
                                          BOOL                          *const active,
                                          vtss_macsec_ssci_t            *const ssci)

{
    u32 sc, record, val;
    BOOL aes_128 = FALSE;
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    BOOL xpn = FALSE;
    u64 value;
    BOOL phy10g = FALSE;

    VTSS_RC(phy_type_get(vtss_state, port.port_no, &phy10g));
    if (phy10g) {
#ifdef VTSS_CHIP_10G_PHY
        if (vtss_state->phy_10g_state[port.port_no].power) {
            VTSS_E("Port:%u power down, cannot access registers", port.port_no);
            return VTSS_RC_ERROR;
        }
#endif
    } else {
#ifdef VTSS_CHIP_CU_PHY
        if (vtss_state->phy_state[port.port_no].setup.mode == VTSS_PHY_MODE_POWER_DOWN) {
            VTSS_E("Port:%u power down, cannot access registers", port.port_no);
            return VTSS_RC_ERROR;
        }
#endif
    }

    VTSS_RC(sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc));
    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    if (secy->rx_sc[sc]->sa[an] == NULL) {
        VTSS_I("AN:%d does not exist, secyid:%d, port_no:%d", an, secy_id, port.port_no);
        VTSS_RC(dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_AN_NOT_EXIST));
    }
    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128)) {
        xpn = TRUE;
    }
    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128)) {
        aes_128 = TRUE;
    }
    record = secy->rx_sc[sc]->sa[an]->record;

    if (xpn) {
        if (aes_128) {
            MACSEC_CNT64_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(record),
                            VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA11(record), value);
        } else {
            MACSEC_CNT64_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(record),
                            VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA15(record), value);
        }
        if (value > secy->rx_sc[sc]->conf.replay_window) {
            lowest_pn->xpn = value - secy->rx_sc[sc]->conf.replay_window;
        } else {
            lowest_pn->xpn = 0;
        }
    } else {
        if (aes_128) {
            CSR_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(record), &val);
        } else {
            CSR_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(record), &val);
        }
        if (val > secy->rx_sc[sc]->conf.replay_window) {
            lowest_pn->pn = val - secy->rx_sc[sc]->conf.replay_window;
        } else {
            lowest_pn->pn = 0;
        }
    }
    VTSS_I("SC:%d, Record:%d, Lowest PN:%d", sc, record, lowest_pn->pn);
    *sak = secy->rx_sc[sc]->sa[an]->sak;
    *active = secy->rx_sc[sc]->sa[an]->status.in_use;
    *ssci = secy->rx_sc[sc]->sa[an]->ssci;

    return VTSS_RC_OK;
}


// ** TX_SA counters **
static vtss_rc vtss_macsec_tx_sa_counters_get_priv(vtss_state_t                    *vtss_state,
                                                   const vtss_port_no_t            port_no,
                                                   const u16                       an,
                                                   vtss_macsec_tx_sa_counters_t    *const counters,
                                                   u32                              secy_id)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    u64 cnt;
    u32 record;
    u64 out_pkts_encrypted = 0;

    memset(counters, 0, sizeof(vtss_macsec_tx_sa_counters_t));

    if (!secy->tx_sc.in_use) {
        VTSS_I("TX_SC does not exist");
        return VTSS_RC_OK;
    }

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    if (!secy->tx_sc.sa[an]) {
        return VTSS_RC_OK;
    }
    record = secy->tx_sc.sa[an]->record;

    // Encrypted and protected shares the same counters. Which once that is using the counters depends upon confidentiality
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_LOWER(record),
                    VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_UPPER(record),
                    cnt);

    VTSS_N("encrypted cnt:%" PRIu64 ", %" PRIu64 ", an:%u, secy_id:%u", cnt, secy->tx_sc.sa[an]->cnt.out_pkts_encrypted, an, secy_id);
    if (secy->tx_sc.sa[an]->confidentiality) {
        secy->tx_sc.sa[an]->cnt.out_pkts_encrypted += cnt;
        secy->tx_sc.sa[an]->cnt.out_pkts_protected = 0;
        out_pkts_encrypted = cnt;
    } else {
        secy->tx_sc.sa[an]->cnt.out_pkts_encrypted = 0;
        secy->tx_sc.sa[an]->cnt.out_pkts_protected += cnt;
    }

    /* Update SC Octets counters, Not available in SA */
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_LOWER(record),
                    VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER(record),
                    cnt);

    if (secy->conf.protect_frames == FALSE && vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
        secy->tx_sc.out_octets_untagged += cnt;
    } else if (secy->tx_sc.sa[an]->confidentiality) {
        if (cnt > (out_pkts_encrypted * secy->conf.confidentiality_offset)) {
            secy->tx_sc.cnt.out_octets_encrypted += cnt - (out_pkts_encrypted * secy->conf.confidentiality_offset);
            secy->tx_sc.cnt.out_octets_protected += (out_pkts_encrypted * secy->conf.confidentiality_offset);
        } else {
            secy->tx_sc.cnt.out_octets_protected += cnt;
        }
    } else {
        secy->tx_sc.cnt.out_octets_protected += cnt;
    }

    /* Update SecY counters */
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_LOWER(record),
                    VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_UPPER(record),
                    cnt);
    secy->secy_cnt.out_pkts_too_long += cnt;

    /* Update SecY Controlled Port counters for RevB */
    if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
        MACSEC_CNT64_RD(port_no, VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_LOWER(record),
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_UPPER(record), cnt);
        secy->controlled_cnt.if_out_ucast_pkts += cnt;

        MACSEC_CNT64_RD(port_no, VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_LOWER(record),
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_UPPER(record), cnt);
        secy->controlled_cnt.if_out_multicast_pkts += cnt;

        MACSEC_CNT64_RD(port_no, VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_LOWER(record),
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_UPPER(record), cnt);
        secy->controlled_cnt.if_out_broadcast_pkts += cnt;
    }

    VTSS_D("encrypted cnt:%" PRIu64 ", %" PRIu64 ", an:%u, secy_id:%u", cnt, secy->tx_sc.sa[an]->cnt.out_pkts_encrypted, an, secy_id);
    // Pass the counters
    memcpy(counters, &secy->tx_sc.sa[an]->cnt, sizeof(vtss_macsec_tx_sa_counters_t));
    return VTSS_RC_OK;
}
// ** TX_SC counters **
static vtss_rc vtss_macsec_tx_sc_counters_get_priv(vtss_state_t                    *vtss_state,
                                                   const vtss_port_no_t            port_no,
                                                   vtss_macsec_tx_sc_counters_t    *const counters,
                                                   u32                              secy_id)
{
    u32 an;
    vtss_macsec_tx_sa_counters_t tx_sa_counters;
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port_no].secy[secy_id];

    /* Donot clear SC Octets counters*/
    vtss_state->macsec_conf[port_no].secy[secy_id].tx_sc.cnt.out_pkts_encrypted = 0;
    vtss_state->macsec_conf[port_no].secy[secy_id].tx_sc.cnt.out_pkts_protected = 0;

    memset(counters, 0, sizeof(vtss_macsec_tx_sc_counters_t));

    for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an ++ ) {
        /* SA counters get will update corresponding SC counters aswell */
        VTSS_RC(vtss_macsec_tx_sa_counters_get_priv(vtss_state, port_no, an, &tx_sa_counters, secy_id));
        VTSS_N("encrypted cnt:%" PRIu64 ", %" PRIu64 "", vtss_state->macsec_conf[port_no].secy[secy_id].tx_sc.cnt.out_pkts_encrypted, tx_sa_counters.out_pkts_encrypted);
        secy->tx_sc.cnt.out_pkts_encrypted += tx_sa_counters.out_pkts_encrypted;
        secy->tx_sc.cnt.out_pkts_protected += tx_sa_counters.out_pkts_protected;
    }
    /* Update deleted SA counters  for this SC*/
    secy->tx_sc.cnt.out_pkts_encrypted   += secy->tx_sc.del_tx_sa_cnt.out_pkts_encrypted;
    secy->tx_sc.cnt.out_pkts_protected   += secy->tx_sc.del_tx_sa_cnt.out_pkts_protected;
    // Pass the counters
    memcpy(counters, &vtss_state->macsec_conf[port_no].secy[secy_id].tx_sc.cnt, sizeof(vtss_macsec_tx_sc_counters_t));
    return VTSS_RC_OK;
}

static vtss_rc sa_sam_in_flight(vtss_state_t  *vtss_state, vtss_port_no_t port_no,  BOOL egr)
{
    u32 val, count = 0;
    do {
        if (egr) {
            CSR_RD(port_no, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT, &val);
        } else {
            CSR_RD(port_no, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT, &val);
        }
        MEPA_MSLEEP(1);
        count++;
        if (count == 100) {
            VTSS_E("timeout, bailing out");
            return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_TIMEOUT_ISSUE);
        }
    } while (VTSS_F_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_IN_FLIGHT_UNSAFE(val));
    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_tx_sa_del_priv(vtss_state_t              *vtss_state,
                                          const u32                 secy_id,
                                          const vtss_macsec_port_t  port,
                                          const u16                 an)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 record, i, sa_in_use = 0;
    vtss_macsec_tx_sa_counters_t tx_sa_counters;

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    VTSS_MACSEC_ASSERT(secy->tx_sc.sa[an] == NULL, "AN is not existing");

    record = secy->tx_sc.sa[an]->record;

    // Wait until the unsafe field has reached zero, i.e. while there are packet in the system
    if (sa_sam_in_flight(vtss_state, port.port_no, EGRESS) != VTSS_RC_OK) {
        VTSS_E("Could not empty the egress pipeline");
        (void)dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS);
    }

    // Update SC counters before the SA is deleted.
    tx_sa_counters.out_pkts_encrypted = 0;
    tx_sa_counters.out_pkts_protected = 0;
    if ((vtss_macsec_tx_sa_counters_get_priv(vtss_state, port.port_no, an, &tx_sa_counters, secy_id)) == VTSS_RC_OK) {
        secy->tx_sc.del_tx_sa_cnt.out_pkts_encrypted += tx_sa_counters.out_pkts_encrypted;
        secy->tx_sc.del_tx_sa_cnt.out_pkts_protected += tx_sa_counters.out_pkts_protected;
    }

    for (i = 0; i < VTSS_MACSEC_SA_PER_SC_MAX; i++ ) {
        if (secy->tx_sc.sa[i] == NULL || (i == an)) {
            continue;
        }
        if (secy->tx_sc.sa[i]->in_use) {
            sa_in_use = 1;
            break;
        }
    }
    if (!sa_in_use) {
        /* Last SA in use, must update the SC stopped_time */
        secy->tx_sc.status.stopped_time = secy->tx_sc.sa[an]->status.stopped_time;
    }

    memset(&vtss_state->macsec_conf[port.port_no].tx_sa[record], 0, sizeof(vtss_state->macsec_conf[port.port_no].tx_sa[record]));
    secy->tx_sc.sa[an] = NULL;
    /* Clear Hardware config registers */
    VTSS_D("Port:%d, secy_id:%u AN:%u, Record:%u, Hardware Registers clear", port.port_no, secy_id, an, record);
    CSR_WARM_WR(port.port_no, VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK(record), 0);
    CSR_WARM_WR(port.port_no, VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR(record), 0);
    if (macsec_sa_match_reset(vtss_state, port.port_no, 1, record) !=  VTSS_RC_OK) {
        VTSS_E("Could not reset the SA match, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (macsec_sa_xform_reset(vtss_state, port.port_no, 1, record, secy, an, 0) != VTSS_RC_OK) {
        VTSS_E("Could not reset the SA flow, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }
    secy->tx_sc.sa[an] = NULL;

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_secy_counters_get_priv(vtss_state_t                  *vtss_state,
                                                  const vtss_port_no_t          port_no,
                                                  vtss_macsec_secy_counters_t   *const counters,
                                                  u32                           secy_id)
{
    u16 an;
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    u32 record;
    u64 cnt;
    BOOL ev_bit = FALSE;
    u16 sc, max_sc_rx;
    u64 out_pkts_encrypt = 0;
    u64 in_ok_pkts = 0;
    u64 out_ok_pkts = 0;
    macsec_secy_in_use_iter_t in_use_inter;

    // TX an
    for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an ++ ) {
        if (secy->tx_sc.sa[an] == NULL || !secy->tx_sc.in_use) {
            continue;
        }
        record = secy->tx_sc.sa[an]->record;

        // Too long
        MACSEC_CNT64_RD(port_no,
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_LOWER(record),
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_TOO_LONG_UPPER(record),
                        cnt);

        secy->secy_cnt.out_pkts_too_long += cnt;

        MACSEC_CNT64_RD(port_no,
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_LOWER(record),
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_PKTS_ENCRYPTED_UPPER(record),
                        cnt);

        if (secy->tx_sc.sa[an]->confidentiality) {
            secy->tx_sc.sa[an]->cnt.out_pkts_encrypted += cnt;
            secy->tx_sc.sa[an]->cnt.out_pkts_protected = 0;
            /* The out_ok_pkts represent encrypted packets. But, there is another counter 'out_pkts_encrypt' which represent
               both encrypted and protected */
            out_ok_pkts = cnt;
        } else {
            secy->tx_sc.sa[an]->cnt.out_pkts_encrypted = 0;
            secy->tx_sc.sa[an]->cnt.out_pkts_protected += cnt;
        }
        out_pkts_encrypt += secy->tx_sc.sa[an]->cnt.out_pkts_protected + secy->tx_sc.sa[an]->cnt.out_pkts_encrypted;

        // Encrypted and protected shares the same counters.
        // Which once that is using the counters depends upon confidentiality (tp.ebit)
        MACSEC_CNT64_RD(port_no,
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_LOWER(record),
                        VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_OCTETS_ENCRYPTED_FIRST_CNTR_UPPER(record),
                        cnt);
        if (secy->conf.protect_frames == FALSE && vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
            secy->tx_sc.out_octets_untagged += cnt;
        } else {
            if (secy->tx_sc.sa[an]->confidentiality) {
                if (cnt > (out_ok_pkts * secy->conf.confidentiality_offset)) {
                    secy->tx_sc.cnt.out_octets_encrypted += cnt - (out_ok_pkts * secy->conf.confidentiality_offset);
                    secy->tx_sc.cnt.out_octets_protected += (out_ok_pkts * secy->conf.confidentiality_offset);
                } else {
                    secy->tx_sc.cnt.out_octets_protected += cnt;
                }
            } else {
                secy->tx_sc.cnt.out_octets_protected += cnt;
            }
        }

        VTSS_D("secy->tx_sc.sa[%d]->confidentiality:%u, cnt:%" PRIu64 "", an, secy->tx_sc.sa[an]->confidentiality, cnt);
        if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
            MACSEC_CNT64_RD(port_no, VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_LOWER(record),
                            VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_UNICAST_PKTS_UPPER(record), cnt);
            vtss_state->macsec_conf[port_no].secy[secy_id].controlled_cnt.if_out_ucast_pkts += cnt;
            MACSEC_CNT64_RD(port_no, VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_LOWER(record),
                            VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_MULTICAST_PKTS_UPPER(record), cnt);
            vtss_state->macsec_conf[port_no].secy[secy_id].controlled_cnt.if_out_multicast_pkts += cnt;
            MACSEC_CNT64_RD(port_no, VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_LOWER(record),
                            VTSS_MACSEC_EGR_SA_STATS_EGR_OUT_BROADCAST_PKTS_UPPER(record), cnt);
            vtss_state->macsec_conf[port_no].secy[secy_id].controlled_cnt.if_out_broadcast_pkts += cnt;
        }

        // Generally the peer device will always send all frames on an SA with confidentiality (rv.ebit == 1) or without confidentiality (rv.ebit == 0).Hence in principal the hardware only needs to implement one counter.
        // For a given SecY, it is known through management if
        //      a)  Confidentiality will be used or not.
        //      b)  If confidentiality is used, what offset is used.
        // Such an information is given through management variable "confidentiality offset".
        //        Per 9.7.1 of 802.1X 2010 :
        // "A participant that believes itself to be the Key Server and its KaY's principal actor encodes the following
        // information with each MACsec SAK that it distributes,

        // The following information is also distributed with each MACsec SAK:
        //   b) Confidentiality Offset, indicating whether confidentiality is to be provided, and whether an offset of
        //  0, 30, or 50 octets is used (see IEEE Std 802.1AE-2006)."

        // Per table 11-6 of 802.1X-2010, the following is the encoding of confidentiality offset.
        // Confidentiality Offset 2-bit
        //    0 if confidentiality not used, 1 if confidentiality with no offset, 2 if offset = 30, 3 if offset = 50.
        //  Hence, SW needs to use  this information (whether confidentiality will be used or not) to distinguish between the counters.
        // Looking at the 802.1X standard I conclude that, you can also use this information from TX direction from any of an active SA, but keep in mind that the "an" values are different in TX and RX direction
        ev_bit = secy->tx_sc.sa[an]->confidentiality; // Note - only one TX AN in use at the time.
    }

    if (secy->conf.protect_frames == FALSE && vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
        secy->secy_cnt.out_pkts_untagged = (secy->controlled_cnt.if_out_ucast_pkts + secy->controlled_cnt.if_out_multicast_pkts +
                                            secy->controlled_cnt.if_out_broadcast_pkts) -
                                           (out_pkts_encrypt + secy->secy_cnt.out_pkts_too_long);
    }
    secy->secy_cnt.out_octets_encrypted = secy->tx_sc.cnt.out_octets_encrypted;
    secy->secy_cnt.out_octets_protected = secy->tx_sc.cnt.out_octets_protected;

    VTSS_N("ev_bit:%d", ev_bit);

    if (phy_is_1g(vtss_state, port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    // RX an
    /* Octets validated are now maintained in respective SC, hence clearing before updation */
    secy->secy_cnt.in_octets_validated = 0;
    secy->secy_cnt.in_octets_decrypted  = 0;
    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
            continue;
        }

        for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an ++ ) {
            if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
                continue;
            }

            record = secy->rx_sc[sc]->sa[an]->record;

            /* Get the OK packets counter for calculating decrypted and validated bytes */
            MACSEC_CNT64_RD(port_no,
                            VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_LOWER(record),
                            VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_UPPER(record),
                            cnt);

            secy->rx_sc[sc]->sa[an]->cnt.in_pkts_ok += cnt;
            in_ok_pkts = cnt;

            // Decrypted and validated shares the same counters.
            MACSEC_CNT64_RD(port_no,
                            VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_LOWER(record),
                            VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER(record),
                            cnt);

            VTSS_N("secy->conf.validate_frames:%u, secy->conf.protect_frames:%u, ev_bit:%d", secy->conf.validate_frames, secy->conf.protect_frames, ev_bit);

            // (From 802.1AE figure 10.5) if ((validateFrames != Disabled) && !rv.ebit) { rv.Valid = integrity_check(rv);
            // (From 802.1AE figure 10.5)    InOctetsValidated += #Plaintext_octets;};
            if (secy->conf.validate_frames != VTSS_MACSEC_VALIDATE_FRAMES_DISABLED && !ev_bit) {
                secy->rx_sc[sc]->cnt.in_octets_validated += cnt;
            }

            if (secy->conf.validate_frames != VTSS_MACSEC_VALIDATE_FRAMES_DISABLED && ev_bit) {
                // (From 802.1AE figure 10.5) if ((validateFrames != Disabled) && rv.ebit) { rv.Valid = integrity_check_and_decrypt(rv);
                // (From 802.1AE figure 10.5)     InOctetsDecrypted += #Plaintext_octets;};
                if (cnt > (in_ok_pkts * secy->conf.confidentiality_offset)) {
                    secy->rx_sc[sc]->cnt.in_octets_decrypted += cnt - (in_ok_pkts * secy->conf.confidentiality_offset);
                    secy->rx_sc[sc]->cnt.in_octets_validated += in_ok_pkts * secy->conf.confidentiality_offset;
                } else {
                    secy->rx_sc[sc]->cnt.in_octets_validated += cnt;
                }
            }
            if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
                if (secy->conf.validate_frames == VTSS_MACSEC_VALIDATE_FRAMES_DISABLED) {
                    secy->rx_sc[sc]->in_octets_validation_disabled += cnt;
                }
            }
        }
        secy->secy_cnt.in_octets_validated += secy->rx_sc[sc]->cnt.in_octets_validated;
        secy->secy_cnt.in_octets_decrypted += secy->rx_sc[sc]->cnt.in_octets_decrypted;

    }

    // in_pkts_no_sci
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_SCI_LOWER,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_SCI_UPPER,
                    cnt);

    counters->in_pkts_no_sci = cnt;

    //in_pkts_unknown_sci
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNKNOWN_SCI_LOWER,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNKNOWN_SCI_UPPER,
                    cnt);

    counters->in_pkts_unknown_sci = cnt;

    // in_pkts_bad_tag
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_BAD_TAG_LOWER,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_BAD_TAG_UPPER,
                    cnt);

    counters->in_pkts_bad_tag = cnt;

    // Untagged
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNTAGGED_LOWER,
                    VTSS_MACSEC_EGR_GLOBAL_STATS_EGR_OUT_PKTS_UNTAGGED_UPPER,
                    cnt);


    if (vtss_state->macsec_conf[port_no].glb.macsec_revb != TRUE) {
        counters->out_pkts_untagged = cnt;
    }

    //  in_pkts_no_tag
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_TAG_LOWER,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_NO_TAG_UPPER,
                    cnt);

    counters->in_pkts_no_tag = cnt;

    //in_pkts_untagged
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_LOWER,
                    VTSS_MACSEC_INGR_GLOBAL_STATS_IGR_IN_PKTS_UNTAGGED_UPPER,
                    cnt);

    counters->in_pkts_untagged = cnt;

    // Overrun - condition does not occur, report as zero (page 78 in HW3)  .'
    counters->in_pkts_overrun = 0;

    /* Global counters are updated for every secy */
    macsec_secy_in_use_inter_init(&in_use_inter);
    while (macsec_secy_in_use_inter_getnext(vtss_state, port_no, &in_use_inter)) {
        vtss_state->macsec_conf[port_no].secy[in_use_inter.secy_id].secy_cnt.in_pkts_no_sci += counters->in_pkts_no_sci;
        vtss_state->macsec_conf[port_no].secy[in_use_inter.secy_id].secy_cnt.in_pkts_unknown_sci += counters->in_pkts_unknown_sci;
        vtss_state->macsec_conf[port_no].secy[in_use_inter.secy_id].secy_cnt.in_pkts_bad_tag += counters->in_pkts_bad_tag;
        if (vtss_state->macsec_conf[port_no].glb.macsec_revb != TRUE) {
            vtss_state->macsec_conf[port_no].secy[in_use_inter.secy_id].secy_cnt.out_pkts_untagged += counters->out_pkts_untagged;
        }
        vtss_state->macsec_conf[port_no].secy[in_use_inter.secy_id].secy_cnt.in_pkts_no_tag += counters->in_pkts_no_tag;
        vtss_state->macsec_conf[port_no].secy[in_use_inter.secy_id].secy_cnt.in_pkts_untagged += counters->in_pkts_untagged;
        vtss_state->macsec_conf[port_no].secy[in_use_inter.secy_id].secy_cnt.in_pkts_overrun += counters->in_pkts_overrun;
    }
    memcpy(counters, &vtss_state->macsec_conf[port_no].secy[secy_id].secy_cnt, sizeof(*counters));

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_secy_cnt_update(vtss_state_t             *vtss_state,
                                           const vtss_port_no_t     port_no,
                                           u32                      secy_id)
{
    vtss_macsec_secy_counters_t  dummy_counters;
    VTSS_RC(vtss_macsec_secy_counters_get_priv(vtss_state,
                                               port_no,
                                               &dummy_counters,
                                               secy_id));
    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_rx_sa_counters_get_priv(vtss_state_t                 *vtss_state,
                                                   const vtss_port_no_t         port_no,
                                                   const vtss_macsec_sci_t      *const sci,
                                                   const u16                    an,
                                                   vtss_macsec_rx_sa_counters_t *const counters,
                                                   u32                          secy_id)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    u32 sc;
    u32 record;
    u64 cnt;
    BOOL ev_bit = FALSE;
    u16  txan;
    u64 in_ok_pkts = 0;
    memset(counters, 0, sizeof(vtss_macsec_rx_sa_counters_t));

    // Update the counter for this secy_id
    VTSS_RC(vtss_macsec_secy_cnt_update(vtss_state, port_no, secy_id));

    VTSS_RC(sc_from_sci_get(vtss_state, port_no, secy, sci, &sc));

    if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use || secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
        return VTSS_RC_OK;
    }

    VTSS_MACSEC_ASSERT(secy->rx_sc[sc] == NULL, "SC does not exist");
    VTSS_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");
    record = secy->rx_sc[sc]->sa[an]->record;
    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_OK_UPPER(record),
                    cnt);

    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_ok += cnt;
    in_ok_pkts = cnt;
    VTSS_N("cnt:%" PRIu64 ", record:%u", cnt, record);

    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_INVALID_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_INVALID_UPPER(record),
                    cnt);

    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_invalid += cnt;

    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_VALID_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_VALID_UPPER(record),
                    cnt);

    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_not_valid += cnt;

    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_USING_SA_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_NOT_USING_SA_UPPER(record),
                    cnt);

    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_not_using_sa += cnt;
    VTSS_N("in_pkts_not_using_sa:%" PRIu64, cnt);

    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNUSED_SA_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNUSED_SA_UPPER(record),
                    cnt);

    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_unused_sa += cnt;


    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNCHECKED_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_UNCHECKED_UPPER(record),
                    cnt);

    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_unchecked += cnt;

    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_DELAYED_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_DELAYED_UPPER(record),
                    cnt);
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_delayed += cnt;

    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_LATE_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_PKTS_LATE_UPPER(record),
                    cnt);
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_late += cnt;
    VTSS_D("rx_sa_counters.in_pkts_late:%" PRIu64 "", secy->rx_sc[sc]->sa[an]->cnt.in_pkts_late);

    /* Update SC Specific  counters */

    MACSEC_CNT64_RD(port_no,
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_LOWER(record),
                    VTSS_MACSEC_INGR_SA_STATS_IGR_IN_OCTETS_DECRYPTED_FIRST_CNTR_UPPER(record),
                    cnt);

    txan = secy->tx_sc.status.encoding_sa;

    if ((secy->tx_sc.in_use) && (secy->tx_sc.sa[txan] != NULL)) {
        ev_bit = secy->tx_sc.sa[txan]->confidentiality;
    }

    if (secy->conf.validate_frames != VTSS_MACSEC_VALIDATE_FRAMES_DISABLED && !ev_bit) {
        secy->rx_sc[sc]->cnt.in_octets_validated += cnt;
    }

    if (secy->conf.validate_frames != VTSS_MACSEC_VALIDATE_FRAMES_DISABLED && ev_bit) {
        if (cnt > (in_ok_pkts * secy->conf.confidentiality_offset)) {
            secy->rx_sc[sc]->cnt.in_octets_decrypted += cnt - (in_ok_pkts * secy->conf.confidentiality_offset);
            secy->rx_sc[sc]->cnt.in_octets_validated += in_ok_pkts * secy->conf.confidentiality_offset;
        } else {
            secy->rx_sc[sc]->cnt.in_octets_validated += cnt;
        }
    }

    if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE &&
        secy->conf.validate_frames == VTSS_MACSEC_VALIDATE_FRAMES_DISABLED) {
        secy->rx_sc[sc]->in_octets_validation_disabled += cnt;
    }
    /* Rx Unicast, multicast and broadcast counters are available only for Rev B*/
    if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
        MACSEC_CNT64_RD(port_no, VTSS_MACSEC_INGR_SA_STATS_IGR_IN_UNICAST_PKTS_LOWER(record),
                        VTSS_MACSEC_INGR_SA_STATS_IGR_IN_UNICAST_PKTS_UPPER(record), cnt);
        secy->controlled_cnt.if_in_ucast_pkts += cnt;
        MACSEC_CNT64_RD(port_no, VTSS_MACSEC_INGR_SA_STATS_IGR_IN_MULTICAST_PKTS_LOWER(record),
                        VTSS_MACSEC_INGR_SA_STATS_IGR_IN_MULTICAST_PKTS_UPPER(record), cnt);
        secy->controlled_cnt.if_in_multicast_pkts += cnt;
        MACSEC_CNT64_RD(port_no, VTSS_MACSEC_INGR_SA_STATS_IGR_IN_BROADCAST_PKTS_LOWER(record),
                        VTSS_MACSEC_INGR_SA_STATS_IGR_IN_BROADCAST_PKTS_UPPER(record), cnt);
        secy->controlled_cnt.if_in_broadcast_pkts += cnt;
    }
    // Pass the counters
    memcpy(counters, &secy->rx_sc[sc]->sa[an]->cnt, sizeof(vtss_macsec_rx_sa_counters_t));
    return VTSS_RC_OK;
}

// ** RX_SC counters **
static vtss_rc vtss_macsec_rx_sc_counters_get_priv(vtss_state_t                    *vtss_state,
                                                   const vtss_port_no_t            port_no,
                                                   const vtss_macsec_sci_t         *const sci,
                                                   vtss_macsec_rx_sc_counters_t    *const counters,
                                                   u32                              secy_id)
{
    u32 sc;
    u32 an;

    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    vtss_macsec_rx_sa_counters_t rx_sa_counters;

    VTSS_RC(sc_from_sci_get(vtss_state, port_no, secy, sci, &sc));

    VTSS_MACSEC_ASSERT(secy->rx_sc[sc] == NULL, "SC does not exist");

    /* Clear counters maintained in SA's Donot clear Octets counters*/
    secy->rx_sc[sc]->cnt.in_pkts_ok             = 0;
    secy->rx_sc[sc]->cnt.in_pkts_invalid        = 0;
    secy->rx_sc[sc]->cnt.in_pkts_not_valid      = 0;
    secy->rx_sc[sc]->cnt.in_pkts_not_using_sa   = 0;
    secy->rx_sc[sc]->cnt.in_pkts_unused_sa      = 0;
    secy->rx_sc[sc]->cnt.in_pkts_unchecked      = 0;
    secy->rx_sc[sc]->cnt.in_pkts_delayed        = 0;
    secy->rx_sc[sc]->cnt.in_pkts_late           = 0;

    for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an ++ ) {
        if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
            continue;
        }

        VTSS_RC(vtss_macsec_rx_sa_counters_get_priv(vtss_state, port_no, sci, an, &rx_sa_counters, secy_id));

        secy->rx_sc[sc]->cnt.in_pkts_ok            += rx_sa_counters.in_pkts_ok;
        secy->rx_sc[sc]->cnt.in_pkts_invalid       += rx_sa_counters.in_pkts_invalid;
        secy->rx_sc[sc]->cnt.in_pkts_not_valid     += rx_sa_counters.in_pkts_not_valid;
        secy->rx_sc[sc]->cnt.in_pkts_not_using_sa  += rx_sa_counters.in_pkts_not_using_sa;
        secy->rx_sc[sc]->cnt.in_pkts_unused_sa     += rx_sa_counters.in_pkts_unused_sa;
        secy->rx_sc[sc]->cnt.in_pkts_unchecked     += rx_sa_counters.in_pkts_unchecked;
        secy->rx_sc[sc]->cnt.in_pkts_delayed       += rx_sa_counters.in_pkts_delayed;
        secy->rx_sc[sc]->cnt.in_pkts_late          += rx_sa_counters.in_pkts_late;
        VTSS_D("rx_sa_counters.in_pkts_late:%" PRIu64 "", rx_sa_counters.in_pkts_late);
    }

    /* Update deleted Rx SA counters for this SC */
    secy->rx_sc[sc]->cnt.in_pkts_ok            += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_ok;
    secy->rx_sc[sc]->cnt.in_pkts_invalid       += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_invalid;
    secy->rx_sc[sc]->cnt.in_pkts_not_valid     += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_not_valid;
    secy->rx_sc[sc]->cnt.in_pkts_not_using_sa  += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_not_using_sa;
    secy->rx_sc[sc]->cnt.in_pkts_unused_sa     += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_unused_sa;
    secy->rx_sc[sc]->cnt.in_pkts_unchecked     += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_unchecked;
    secy->rx_sc[sc]->cnt.in_pkts_delayed       += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_delayed;
    secy->rx_sc[sc]->cnt.in_pkts_late          += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_late;

    // Pass the counters
    memcpy(counters, &secy->rx_sc[sc]->cnt, sizeof(vtss_macsec_rx_sc_counters_t));
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_rx_sa_del_priv(vtss_state_t              *vtss_state,
                                          const u32                 secy_id,
                                          const vtss_macsec_port_t  port,
                                          const vtss_macsec_sci_t   *const sci,
                                          const u16                 an)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 sc, record, sa_in_use = 0, i;
    vtss_macsec_rx_sa_counters_t rx_sa_counters;

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    VTSS_RC(sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc));

    VTSS_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");
    if (!secy->rx_sc[sc]->sa[an]) {
        VTSS_E("AN not created. AN=%u, port_no:%d, port_id:%d, secy_id:%d", an, port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_AN_NOT_CREATED);
    }
    record = secy->rx_sc[sc]->sa[an]->record;

    /* Disable chip SA Flow */
    if (macsec_sa_enable(vtss_state, port.port_no, record, INGRESS, MACSEC_DISABLE) != VTSS_RC_OK) {
        VTSS_E("Could not Enable the SA:%u", an);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }

    // Wait until the unsafe field has reached zero, i.e. while there are packet in the system
    if (sa_sam_in_flight(vtss_state, port.port_no, INGRESS) != VTSS_RC_OK) {
        VTSS_E("Could not empty the ingress pipeline");
        (void)dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS);
    }

    /* Get Rx Sa counters going to be deleted.., and just ignore even if there is a error on reading */
    if ((vtss_macsec_rx_sa_counters_get_priv(vtss_state, port.port_no, sci, an, &rx_sa_counters, secy_id)) == VTSS_RC_OK) {
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_ok            += rx_sa_counters.in_pkts_ok;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_invalid       += rx_sa_counters.in_pkts_invalid;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_not_valid     += rx_sa_counters.in_pkts_not_valid;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_not_using_sa  += rx_sa_counters.in_pkts_not_using_sa;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_unused_sa     += rx_sa_counters.in_pkts_unused_sa;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_unchecked     += rx_sa_counters.in_pkts_unchecked;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_delayed       += rx_sa_counters.in_pkts_delayed;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_late          += rx_sa_counters.in_pkts_late;
    }

    for (i = 0; i < VTSS_MACSEC_SA_PER_SC_MAX; i++ ) {
        if (secy->rx_sc[sc]->sa[i] == NULL || (i == an)) {
            continue;
        }
        if (secy->rx_sc[sc]->sa[i]->in_use) {
            sa_in_use = 1;
            break;
        }
    }

    if (!sa_in_use) {
        secy->rx_sc[sc]->status.stopped_time = secy->rx_sc[sc]->sa[an]->status.stopped_time;
    }
    memset(&vtss_state->macsec_conf[port.port_no].rx_sa[record], 0, sizeof(vtss_state->macsec_conf[port.port_no].rx_sa[record]));
    secy->rx_sc[sc]->sa[an] = NULL;

    /* Clear Hardware config registers */
    VTSS_D("Port:%d, secy_id:%u AN:%u, Record:%u, Hardware Registers clear", port.port_no, secy_id, an, record);

    CSR_WARM_WR(port.port_no, VTSS_MACSEC_INGR_SA_MATCH_PARAMS_SAM_MASK(record), 0);
    CSR_WARM_WR(port.port_no, VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR(record), 0);
    if (macsec_sa_match_reset(vtss_state, port.port_no, 0, record) !=  VTSS_RC_OK) {
        VTSS_E("Could not reset the SA match, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (macsec_sa_xform_reset(vtss_state, port.port_no, 0, record, secy, an, 0) != VTSS_RC_OK) {
        VTSS_E("Could not reset the SA flow, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_rx_sc_del_priv(vtss_state_t              *vtss_state,
                                          const vtss_macsec_port_t  port,
                                          const vtss_macsec_sci_t   *sci,
                                          const u32                 secy_id)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 sc, sa;
    VTSS_RC(sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc))

    for (sa = 0; sa < VTSS_MACSEC_SA_PER_SC; sa++) {
        if (secy->rx_sc[sc]->sa[sa] != NULL) {

            if (secy->rx_sc[sc]->sa[sa]->status.in_use) {
                if (vtss_macsec_rx_sa_disable_priv(vtss_state, secy_id, port, sci, sa) != VTSS_RC_OK) {
                    VTSS_E("Could not disable sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                    return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                }
            }
            if (vtss_macsec_rx_sa_del_priv(vtss_state, secy_id, port, sci, sa)) {
                VTSS_E("Could not delete rx sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA);
            }
        }
    }
    memset(secy->rx_sc[sc], 0, sizeof(*secy->rx_sc[sc]));
    secy->rx_sc[sc] = NULL;
    VTSS_RC(macsec_update_glb_validate(vtss_state, port.port_no));
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_tx_sc_del_priv(vtss_state_t              *vtss_state,
                                          const vtss_macsec_port_t  port,
                                          const u32                 secy_id)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 sa;

    if (!secy->tx_sc.in_use) {
        VTSS_E("TX_SC does not exist");
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_TX_SC_NOT_EXIST);
    }

    for (sa = 0; sa < VTSS_MACSEC_SA_PER_SC; sa++) {
        if (secy->tx_sc.sa[sa] != NULL) {
            if (vtss_macsec_tx_sa_disable_priv(vtss_state, secy_id, port, sa)) {
                VTSS_E("Could not disable sa:%u", sa);
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
            }
            if (vtss_macsec_tx_sa_del_priv(vtss_state, secy_id, port, sa)) {
                VTSS_E("Could not delete tx sa:%u, port_no:%d port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA);
            }
        }
    }
    memset(&secy->tx_sc, 0, sizeof(secy->tx_sc));
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_pattern_del_priv(vtss_state_t                       *vtss_state,
                                            const vtss_macsec_port_t           port,
                                            const u32                          secy_id,
                                            const vtss_macsec_direction_t      direction,
                                            const vtss_macsec_match_action_t   action)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    BOOL egr = (direction == VTSS_MACSEC_DIRECTION_EGRESS) ? 1 : 0;
    u32 record;
    record = secy->pattern_record[action][direction];

    if (record == MACSEC_NOT_IN_USE) {
        VTSS_E("Pattern not set. port_no:%d, port_id:%d, secy_id:%d, direction:%d", port.port_no, port.port_id, secy_id, direction);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_PATTERN_NOT_SET);
    }
    /* Disable the SA */
    if (macsec_sa_enable(vtss_state, port.port_no, record, egr, MACSEC_DISABLE) != VTSS_RC_OK) {
        VTSS_E("Could not disable the SA, port_no:%d, port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
    }
    if (macsec_sa_inuse(vtss_state, port.port_no, record, egr, MACSEC_DISABLE) != VTSS_RC_OK) {
        VTSS_E("Could not set SA:%u to 'in_use, port_no:%d", record, port.port_no);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }
    if (egr) {
        vtss_state->macsec_conf[port.port_no].tx_sa[record].in_use = 0;
        /* Clear Hardware config registers */
        VTSS_D("Port:%d, secy_id:%u Record:%u, Hardware Registers clear", port.port_no, secy_id, record);
        CSR_WARM_WR(port.port_no, VTSS_MACSEC_EGR_SA_MATCH_FLOW_CONTROL_PARAMS_EGR_SAM_FLOW_CTRL_EGR(record), 0);
        if (macsec_sa_match_reset(vtss_state, port.port_no, 1, record) !=  VTSS_RC_OK) {
            VTSS_E("Could not reset the SA match, port_no:%d  secy_id:%d", port.port_no, secy_id);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
        }
    } else {
        vtss_state->macsec_conf[port.port_no].rx_sa[record].in_use = 0;
        /* Clear Hardware config registers */
        VTSS_D("Port:%d, secy_id:%u Record:%u, Hardware Registers clear", port.port_no, secy_id, record);
        CSR_WARM_WR(port.port_no, VTSS_MACSEC_INGR_SA_MATCH_FLOW_CONTROL_PARAMS_IGR_SAM_FLOW_CTRL_IGR(record), 0);
        if (macsec_sa_match_reset(vtss_state, port.port_no, 0, record) !=  VTSS_RC_OK) {
            VTSS_E("Could not reset the SA match, port_no:%d  secy_id:%d", port.port_no, secy_id);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
        }
    }
    secy->pattern_record[action][direction] = MACSEC_NOT_IN_USE;
    secy->pattern[action][direction].match = VTSS_MACSEC_MATCH_DISABLE;
    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_secy_conf_del_priv(vtss_state_t *vtss_state,
                                              const vtss_macsec_port_t port, const u32 secy_id)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u16 sc, max_sc_rx;

    if (secy->tx_sc.in_use) {
        VTSS_RC(vtss_macsec_tx_sc_del_priv(vtss_state, port, secy_id));
    }

    if (phy_is_1g(vtss_state, port.port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL) {
            continue;
        }
        VTSS_RC(vtss_macsec_rx_sc_del_priv(vtss_state, port, &secy->rx_sc[sc]->sci, secy_id));
    }

    if (secy->pattern_record[VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT][VTSS_MACSEC_DIRECTION_INGRESS] != MACSEC_NOT_IN_USE) {
        VTSS_RC(vtss_macsec_pattern_del_priv(vtss_state, port, secy_id, VTSS_MACSEC_DIRECTION_INGRESS, VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT));
    }
    if (secy->pattern_record[VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT][VTSS_MACSEC_DIRECTION_INGRESS] != MACSEC_NOT_IN_USE) {
        VTSS_RC(vtss_macsec_pattern_del_priv(vtss_state, port, secy_id, VTSS_MACSEC_DIRECTION_INGRESS, VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT));
    }
    if (secy->pattern_record[VTSS_MACSEC_MATCH_ACTION_DROP][VTSS_MACSEC_DIRECTION_INGRESS] != MACSEC_NOT_IN_USE) {
        VTSS_RC(vtss_macsec_pattern_del_priv(vtss_state, port, secy_id, VTSS_MACSEC_DIRECTION_INGRESS, VTSS_MACSEC_MATCH_ACTION_DROP));
    }

    if (secy->pattern_record[VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT][VTSS_MACSEC_DIRECTION_EGRESS] != MACSEC_NOT_IN_USE) {
        VTSS_RC(vtss_macsec_pattern_del_priv(vtss_state, port, secy_id, VTSS_MACSEC_DIRECTION_EGRESS, VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT));
    }
    if (secy->pattern_record[VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT][VTSS_MACSEC_DIRECTION_EGRESS] != MACSEC_NOT_IN_USE) {
        VTSS_RC(vtss_macsec_pattern_del_priv(vtss_state, port, secy_id, VTSS_MACSEC_DIRECTION_EGRESS, VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT));
    }
    if (secy->pattern_record[VTSS_MACSEC_MATCH_ACTION_DROP][VTSS_MACSEC_DIRECTION_EGRESS] != MACSEC_NOT_IN_USE) {
        VTSS_RC(vtss_macsec_pattern_del_priv(vtss_state, port, secy_id, VTSS_MACSEC_DIRECTION_EGRESS, VTSS_MACSEC_MATCH_ACTION_DROP));
    }

    memset(secy, 0, sizeof(*secy));
    for (sc = 0; sc < max_sc_rx; sc++) {
        secy->rx_sc[sc] = NULL;
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_secy_controlled_set_priv(vtss_state_t              *vtss_state,
                                                    const vtss_macsec_port_t  port,
                                                    const BOOL                enable,
                                                    const u32                 secy_id)
{
    vtss_macsec_internal_secy_t *secy;
    u32 sa, sc;
    u32 max_sc_rx;
    secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];

    if (secy->controlled_port_enabled == enable) {
        return VTSS_RC_OK; // Nothing to do
    }

    if (phy_is_1g(vtss_state, port.port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }
    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL) {
            continue;
        }
        for (sa = 0; sa < VTSS_MACSEC_SA_PER_SC; sa++) {
            if (secy->rx_sc[sc]->sa[sa] == NULL) {
                continue;
            }
            if (secy->rx_sc[sc]->sa[sa]->enabled) {
                if (macsec_sa_enable(vtss_state, port.port_no, secy->rx_sc[sc]->sa[sa]->record, INGRESS, enable) != VTSS_RC_OK) {
                    VTSS_E("Could not disable/enable Rx sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                    return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                }
            }
        }
    }

    for (sa = 0; sa < VTSS_MACSEC_SA_PER_SC; sa++) {
        if (secy->tx_sc.sa[sa] != NULL) {
            if (secy->tx_sc.sa[sa]->enabled) {
                if (macsec_sa_enable(vtss_state, port.port_no, secy->tx_sc.sa[sa]->record, EGRESS, enable) != VTSS_RC_OK) {
                    VTSS_E("Could not disable/enable Tx sa:%u", sa);
                    return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                }
            }
        }
    }

    secy->controlled_port_enabled = enable;
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_tx_sa_status_get_priv(vtss_state_t                *vtss_state,
                                                 u32                         secy_id,
                                                 const vtss_macsec_port_t    port,
                                                 const u16                   an)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 val, record;
    BOOL aes_128;
    BOOL xpn = FALSE;
    u64 value = 0;

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    VTSS_MACSEC_ASSERT(secy->tx_sc.sa[an] == NULL, "AN does not exist");
    record = secy->tx_sc.sa[an]->record;

    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        xpn = TRUE;
    }
    aes_128 = (xpn != TRUE ? ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128) ? 1 : 0) :
               ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ? 1 : 0));

    if (xpn) {
        if (aes_128) {
            MACSEC_CNT64_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(record),
                            VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA11(record), value);
        } else {
            MACSEC_CNT64_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(record),
                            VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA15(record), value);
        }
        /* Workaround for Packet Number Transmit (i.e. NextPN - 1) */
        value += 1;
        secy->tx_sc.sa[an]->status.pn_status.next_pn.xpn = value;
    } else {
        if (aes_128) {
            CSR_RD(port.port_no, VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(record), &val);
        } else {
            CSR_RD(port.port_no, VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(record), &val);
        }
        /* Workaround for Packet Number Transmit (i.e. NextPN - 1) */
        val += 1;
        secy->tx_sc.sa[an]->status.next_pn = val;
        secy->tx_sc.sa[an]->status.pn_status.next_pn.pn = val;
    }

    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_secy_port_status_get_priv(vtss_state_t                      *vtss_state,
                                                     const vtss_macsec_port_t          port,
                                                     vtss_macsec_secy_port_status_t    *const status,
                                                     const u32                         secy_id,
                                                     BOOL                              fdx)
{
    vtss_macsec_internal_secy_t *secy;
    BOOL transmitting = 0, strict = 0;
    u32 sc_in_use = 0, sc, an;
    u32 max_sc_rx;
    int tx_an = -1;
    secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];

    if (secy->conf.validate_frames == VTSS_MACSEC_VALIDATE_FRAMES_STRICT) {
        strict = 1;
    }

    if (phy_is_1g(vtss_state, port.port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL) {
            continue;
        }
        for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
            if (secy->rx_sc[sc]->sa[an] == NULL) {
                continue;
            }
            if (secy->rx_sc[sc]->sa[an]->in_use) {
                sc_in_use++;
                break;
            }
        }
    }
    for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
        if (secy->tx_sc.sa[an] == NULL) {
            continue;
        }
        if (secy->tx_sc.sa[an]->in_use) {
            transmitting = 1;
            tx_an = an;
        }
    }

    if (tx_an != -1) {
        (void)vtss_macsec_tx_sa_status_get_priv(vtss_state, secy_id, port, tx_an);
    }
    // 802.1AE 10.7.2
    status->common.mac_enabled = 1;               // The common MAC is always enabled
    status->common.mac_operational = 1;           // The common MAC is always operational
    status->common.oper_point_to_point_mac = fdx; // Duplex as reported by the Phy

    // 802.1AE 10.7.2
    status->uncontrolled = status->common;

    // 802.1AE 10.7.4
    status->controlled.mac_enabled = secy->controlled_port_enabled && status->common.mac_enabled && transmitting && (sc_in_use > 0);

    if ((tx_an != -1) && (secy->tx_sc.sa[tx_an]->status.next_pn == 0xFFFFFFFF || secy->tx_sc.sa[tx_an]->status.next_pn == 0)) {
        status->controlled.mac_operational = 0;
    } else {
        status->controlled.mac_operational = status->controlled.mac_enabled && status->common.mac_operational;
    }
    status->controlled.oper_point_to_point_mac = (strict && (sc_in_use < 2)) || (!strict && status->common.oper_point_to_point_mac);
    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_secy_controlled_get_priv(vtss_state_t              *vtss_state,
                                                    const vtss_macsec_port_t  port,
                                                    BOOL                      *const enable,
                                                    const u32                 secy_id)
{
    vtss_macsec_internal_secy_t *secy;
    secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];

    *enable = secy->controlled_port_enabled;
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_rx_sc_add_priv(vtss_state_t              *vtss_state,
                                          const vtss_macsec_port_t  port,
                                          const vtss_macsec_sci_t   *sci,
                                          const u32                 secy_id)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u16 sc_secy = 0, sc_conf = 0, sc;
    u16 max_sc_rx;
    BOOL found_sc_in_secy = 0, found_sc_in_conf = 0;
    mepa_timeofday_t tod;

    if (!check_resources(vtss_state, port.port_no, 1, secy_id)) {
        VTSS_E("HW resources exhausted, port_no:%d  port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED);
    }

    VTSS_RC(is_sci_valid(vtss_state, port.port_no, sci));

    if (phy_is_1g(vtss_state, port.port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    for (sc = 0; sc < max_sc_rx; sc++) {
        if (sci_cmp(sci, &vtss_state->macsec_conf[port.port_no].rx_sc[sc].sci)) {
            VTSS_E("SCI already exists, port_no:%d  port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_SCI_ALREADY_EXISTS);
        }

    }

    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL && !found_sc_in_secy) {
            sc_secy = sc;
            found_sc_in_secy = 1;
        }
        if (!vtss_state->macsec_conf[port.port_no].rx_sc[sc].in_use && !found_sc_in_conf) {
            sc_conf = sc;
            found_sc_in_conf = 1;
        }
    }

    if (!(found_sc_in_secy && found_sc_in_conf)) {
        VTSS_E("Could not find SC resources, port_no:%d  port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND);
    }

    VTSS_I("Adding new RX-SC: Port: "MACSEC_PORT_FMT " SCI: "SCI_FMT
           ", sc-in-secy:%u",
           MACSEC_PORT_ARG(&port), SCI_ARG(*sci), sc_secy);

    secy->rx_sc[sc_secy] = &vtss_state->macsec_conf[port.port_no].rx_sc[sc_conf];
    sci_cpy(&secy->rx_sc[sc_secy]->sci, sci);

    // The RxSC inherits the SecY configuration
    secy->rx_sc[sc_secy]->conf.validate_frames = secy->conf.validate_frames;
    secy->rx_sc[sc_secy]->conf.replay_protect = secy->conf.replay_protect;
    secy->rx_sc[sc_secy]->conf.replay_window = secy->conf.replay_window;
    secy->rx_sc[sc_secy]->conf.confidentiality_offset = secy->conf.confidentiality_offset;
    MEPA_TIME_OF_DAY(tod);
    secy->rx_sc[sc_secy]->status.created_time = tod.sec; // TimeOfDay in seconds
    secy->rx_sc[sc_secy]->in_use = 1;

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_tx_sc_set_priv(vtss_state_t              *vtss_state,
                                          const vtss_macsec_port_t  port,
                                          const u32                 secy_id)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    mepa_timeofday_t tod;

    VTSS_RC(is_sci_valid(vtss_state, port.port_no, &secy->sci));

    MEPA_TIME_OF_DAY(tod);
    secy->tx_sc.status.created_time = tod.sec; // 802.1AE 10.7.12
    secy->tx_sc.status.started_time = tod.sec; // 802.1AE 10.7.12
    secy->tx_sc.status.stopped_time = 0;       // 802.1AE 10.7.12
    secy->tx_sc.in_use = 1;
    memcpy(&secy->tx_sc.status.sci,  &secy->sci, sizeof(vtss_macsec_sci_t));
    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_rx_sa_set_priv(vtss_state_t                  *vtss_state,
                                          const u32                     secy_id,
                                          const vtss_macsec_port_t      port,
                                          const vtss_macsec_sci_t       *const sci,
                                          const u16                     an,
                                          const vtss_macsec_pkt_num_t   lowest_pn,
                                          const vtss_macsec_sak_t       *const sak,
                                          const vtss_macsec_ssci_t      *const ssci)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    vtss_macsec_match_pattern_t *match = &secy->pattern[VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT][VTSS_MACSEC_DIRECTION_INGRESS];
    u32 sc, record = 0;
    mepa_timeofday_t tod;
    BOOL create_record = 1;
    vtss_macsec_internal_secy_t secy_tmp;
    vtss_macsec_internal_rx_sa_t sa_tmp;

    VTSS_RC(sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc));
    VTSS_I("port_no: %u, secy: %u, sc:%u, an:%u", port.port_no, secy_id, sc, an);
    VTSS_I(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_RC(is_sci_valid(vtss_state, port.port_no, sci));
    VTSS_I("sync_calling: %u, speed_change: %u, warm_start: %u",
           vtss_state->sync_calling_private, vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg,
           vtss_state->warm_start_cur);
    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        if ( (!vtss_state->sync_calling_private) &&
             (!vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg) ) {
            VTSS_RC(is_ssci_valid(vtss_state, port.port_no, FALSE, sci, ssci, sak));
        }
    }
    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    if (vtss_state->sync_calling_private) {
        if (secy->rx_sc[sc]->sa[an] == NULL) {
            return VTSS_RC_OK;
        }
    }

    if (!vtss_state->sync_calling_private) {
        if ((secy->rx_sc[sc]->sa[an] != NULL) &&
            (!vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg)) {
            VTSS_E("Rx AN:%u is in use", an);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE);
        } else if (vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg &&
                   (secy->rx_sc[sc]->sa[an] == NULL) &&
                   (!vtss_state->warm_start_cur)) {
            VTSS_I("port_no: %u, secy->rx_sc[%u]->sa[%u] is NULL", port.port_no, sc, an);
            return VTSS_RC_OK;
        }

        if (vtss_state->warm_start_cur) {
            VTSS_I("port_no: %u, Warm Start", port.port_no);
            secy_tmp = *secy;
            secy_tmp.rx_sc[sc]->sa[an] = &sa_tmp;
            secy_tmp.rx_sc[sc]->sa[an]->sak = *sak;
            secy_tmp.rx_sc[sc]->sa[an]->status.lowest_pn = lowest_pn.pn;
            secy_tmp.rx_sc[sc]->sa[an]->status.pn_status.lowest_pn = lowest_pn;
            if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
                (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
                memcpy(secy_tmp.rx_sc[sc]->sa[an]->ssci.buf, ssci->buf, sizeof(vtss_macsec_ssci_t));
            }
            if (record_inuse_get(vtss_state, port.port_no, INGRESS, &secy_tmp, an, sc, &record) != VTSS_RC_OK) {
                vtss_state->macsec_conf[port.port_no].glb.warm_start_reg_changed = TRUE; // Signaling that a register for this port has changed.
                create_record = 1;
            } else {
                create_record = 0;
            }
        } else if (vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg) {
            VTSS_I("port_no: %u, MACsec Reconfiguration", port.port_no);
            create_record = 0;
            record = secy->rx_sc[sc]->sa[an]->record;
        }

        if (create_record && (record_empty_get(vtss_state, port.port_no, &record, INGRESS) != VTSS_RC_OK)) {
            VTSS_E("Could not get an empty record, port_no:%d  port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_EMPTY_RECORD);
        }

        secy->rx_sc[sc]->sa[an] = &vtss_state->macsec_conf[port.port_no].rx_sa[record];
        secy->rx_sc[sc]->sa[an]->record = record;
        if (!vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg) {
            secy->rx_sc[sc]->sa[an]->sak = *sak;
            if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
                (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
                memcpy(secy->rx_sc[sc]->sa[an]->ssci.buf, ssci->buf, sizeof(vtss_macsec_ssci_t));
            }
        }
        secy->rx_sc[sc]->sa[an]->status.lowest_pn = lowest_pn.pn;
        secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn = lowest_pn; // Rev-B
        secy->rx_sc[sc]->sa[an]->in_use = 1;
        MEPA_TIME_OF_DAY(tod);
        secy->rx_sc[sc]->sa[an]->status.created_time = tod.sec; // TimeOfDay in seconds
    }

    if (vtss_state->warm_start_cur) {
        return VTSS_RC_OK;
    }

    if (macsec_sa_match_set(vtss_state, port.port_no, INGRESS,
                            secy->rx_sc[sc]->sa[an]->record, match, secy, 1, sc, an, 0) != VTSS_RC_OK) {
        VTSS_E("Could not program the SA match, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (macsec_sa_flow_set(vtss_state, port.port_no, INGRESS,
                           secy->rx_sc[sc]->sa[an]->record, secy, an, sc, VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT) != VTSS_RC_OK) {
        VTSS_E("Could not program the SA flow, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }
    if (macsec_sa_xform_set(vtss_state, port.port_no, INGRESS, secy->rx_sc[sc]->sa[an]->record, secy, an, sc) != VTSS_RC_OK) {
        VTSS_E("Could not program the xform record, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM);
    }
    /* Enable chip SA Flow */
    if (macsec_sa_enable(vtss_state, port.port_no, secy->rx_sc[sc]->sa[an]->record, INGRESS, MACSEC_ENABLE) != VTSS_RC_OK) {
        VTSS_E("Could not Enable the SA:%u", an);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }


    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_rx_sa_status_get_priv(vtss_state_t                *vtss_state,
                                                 const u32                   secy_id,
                                                 const vtss_macsec_port_t    port,
                                                 const vtss_macsec_sci_t     *const sci,
                                                 const u16                   an,
                                                 vtss_macsec_rx_sa_status_t  *const status)
{
    u32 next_pn, sc, record;
    BOOL aes_128;
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    BOOL xpn = FALSE;
    u64 value = 0;

    if (sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc) != VTSS_RC_OK) {
        VTSS_E("No SC found");
        return VTSS_RC_OK;
    }
    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    VTSS_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");
    VTSS_MACSEC_ASSERT(!secy->rx_sc[sc]->sa[an]->in_use, "AN is not active");

    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        xpn = TRUE;
    }
    aes_128 = (xpn != TRUE ? ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128) ? 1 : 0) :
               ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ? 1 : 0));

    record = secy->rx_sc[sc]->sa[an]->record;
    if (xpn) {
        if (aes_128) {
            MACSEC_CNT64_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(record),
                            VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA11(record), value);
        } else {
            MACSEC_CNT64_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(record),
                            VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA15(record), value);
        }
        secy->rx_sc[sc]->sa[an]->status.pn_status.next_pn.xpn = value;
        secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn.xpn = (secy->rx_sc[sc]->conf.replay_window >= value) ?
                                                                  1 : (value - secy->rx_sc[sc]->conf.replay_window);
    } else {
        /* Read the next PN */
        if (aes_128) {
            CSR_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(record), &next_pn);
        } else {
            CSR_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(record), &next_pn);
        }
        secy->rx_sc[sc]->sa[an]->status.next_pn = next_pn;
        secy->rx_sc[sc]->sa[an]->status.lowest_pn = (secy->rx_sc[sc]->conf.replay_window >= next_pn) ?
                                                    1 : (next_pn - secy->rx_sc[sc]->conf.replay_window);
    }

    *status = secy->rx_sc[sc]->sa[an]->status;
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_rx_sa_next_pn_update_priv(vtss_state_t                  *vtss_state,
                                                     const u32                     secy_id,
                                                     const vtss_macsec_port_t      port,
                                                     const vtss_macsec_pkt_num_t   next_pn,
                                                     const u32                     record)
{
    u32 ctxt_addr, value = 0;
    BOOL xpn = FALSE;
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];

    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        xpn = TRUE;
    }
    /* Update the next pn */
    if (xpn == TRUE) {
        MACSEC_CNT64_WR(port.port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_LOWER,
                        VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_UPPER, next_pn.xpn);
    } else {
        CSR_WR(port.port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_LOWER, next_pn.pn);
    }
    CSR_WR(port.port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CONTEXT_ID, record);

    /* Next_pn_ctx_addr = ((Index of SA * Offset between SAs in bytes) + (Position of SeqNum word * 4)) >> 4 */
    /* Offset between SA's = context size * 4 bytes */
    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128)) {
        ctxt_addr = ((record * (20 * 4)) + (10 * 4)) >> 4;
        value = VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_CTX_ADDR(ctxt_addr) |
                (xpn ? VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_SEQ_NUM_SIZE : 0);
        CSR_WR(port.port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL, value);
    } else {
        ctxt_addr = ((record * (20 * 4)) + (14 * 4)) >> 4;
        value = VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_CTX_ADDR(ctxt_addr) |
                (xpn ? VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_SEQ_NUM_SIZE : 0);
        CSR_WR(port.port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL, value);
    }
    /* Make the update effective */
    value = VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_ENABLE_UPDATE;
    CSR_WRM(port.port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL, value, value);

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_rx_sa_lowest_pn_update_priv(vtss_state_t                  *vtss_state,
                                                       const u32                     secy_id,
                                                       const vtss_macsec_port_t      port,
                                                       const vtss_macsec_sci_t       *const sci,
                                                       const u16                     an,
                                                       const vtss_macsec_pkt_num_t   lowest_pn)
{
    u32 next_pn, sc, record;
    BOOL aes_128, xpn = FALSE;
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    vtss_macsec_pkt_num_t pkt_num;

    if (sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc) != VTSS_RC_OK) {
        VTSS_E("No SC found");
        return VTSS_RC_OK;
    }

    VTSS_RC(is_sci_valid(vtss_state, port.port_no, sci));

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    VTSS_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");
    VTSS_MACSEC_ASSERT(!secy->rx_sc[sc]->sa[an]->in_use, "AN is not active");
    record = secy->rx_sc[sc]->sa[an]->record;
    if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb == TRUE) {
        if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
            (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
            xpn = TRUE;
        }
        if (xpn == TRUE) {
            pkt_num.xpn = lowest_pn.xpn + secy->conf.replay_window;
        } else {
            pkt_num.pn = lowest_pn.pn + secy->conf.replay_window;
        }

        if (vtss_macsec_rx_sa_next_pn_update_priv(vtss_state, secy_id, port, pkt_num, record) != VTSS_RC_OK) {
            VTSS_E("Could not update Next PN");
            return VTSS_RC_ERROR;
        }
        CSR_RD(port.port_no, VTSS_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL, &next_pn);
        if (!(!(next_pn & VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_ENABLE_UPDATE) &&
              (next_pn & VTSS_F_MACSEC_INGR_CRYPTO_CTRL_STATUS_REGS_NEXT_PN_CTRL_NEXT_PN_WRITTEN))) {
            VTSS_D("Next PN not yet updated");
        }
    } else {
        aes_128 = (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128) ? 1 : 0;
        /* Read the next PN */
        if (aes_128) {
            CSR_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA10(record), &next_pn);
        } else {
            CSR_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA14(record), &next_pn);
        }

        if (lowest_pn.pn > (next_pn + secy->conf.replay_window)) {
            u32 new_record;
            vtss_macsec_match_pattern_t *match = &secy->pattern[VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT][VTSS_MACSEC_DIRECTION_INGRESS];
            VTSS_D("SA must be changed! (lowest_pn > next_pn + replay_window). Lowest_pn:%u next_pn:%u replay_window:%u",
                   lowest_pn.pn, next_pn, secy->conf.replay_window);
            /* The exisiting SA must be replaced by an new SA */
            secy->rx_sc[sc]->sa[an]->status.lowest_pn = lowest_pn.pn;

            if (record_empty_get(vtss_state, port.port_no, &new_record, INGRESS) != VTSS_RC_OK) {
                VTSS_E("Could not get an empty record");
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_EMPTY_RECORD);
            }

            memcpy(&vtss_state->macsec_conf[port.port_no].rx_sa[new_record],
                   &vtss_state->macsec_conf[port.port_no].rx_sa[record], sizeof(vtss_macsec_internal_rx_sa_t));
            memset(&vtss_state->macsec_conf[port.port_no].rx_sa[record], 0, sizeof(vtss_state->macsec_conf[port.port_no].rx_sa[record]));
            secy->rx_sc[sc]->sa[an] = &vtss_state->macsec_conf[port.port_no].rx_sa[new_record];
            secy->rx_sc[sc]->sa[an]->record = new_record;

            if (macsec_sa_match_set(vtss_state, port.port_no, INGRESS, new_record, match, secy, 1, sc, an, 0) != VTSS_RC_OK) {
                VTSS_E("Could not program the SA match");
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
            }
            if (macsec_sa_flow_set(vtss_state, port.port_no, INGRESS, new_record, secy, an, sc,
                                   VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT) != VTSS_RC_OK) {
                VTSS_E("Could not program the SA flow");
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
            }
            if (macsec_sa_xform_set(vtss_state, port.port_no, INGRESS, new_record, secy, an, sc) != VTSS_RC_OK) {
                VTSS_E("Could not program the xform record");
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM);
            }
            if (macsec_sa_toggle(vtss_state, port.port_no, new_record, record, INGRESS) != VTSS_RC_OK) {
                VTSS_E("Could not toggle SA:%u -> %u", record, new_record);
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA);
            }
            if (macsec_sa_inuse(vtss_state, port.port_no, new_record, INGRESS, MACSEC_ENABLE) != VTSS_RC_OK) {
                VTSS_E("Could not set SA:%u to 'in_use'", record);
                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
            }

        }

    }
    return VTSS_RC_OK;
}

vtss_rc vtss_macsec_rx_seca_set(const vtss_inst_t             inst,
                                const vtss_macsec_port_t      port,
                                const vtss_macsec_sci_t       *const sci,
                                const u16                     an,
                                const vtss_macsec_pkt_num_t   lowest_pn,
                                const vtss_macsec_sak_t       *const sak,
                                const vtss_macsec_ssci_t      *const ssci)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_set_priv(vtss_state, secy_id, port, sci, an, lowest_pn, sak, ssci);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_seca_get(const vtss_inst_t             inst,
                                const vtss_macsec_port_t      port,
                                const vtss_macsec_sci_t       *const sci,
                                const u16                     an,
                                vtss_macsec_pkt_num_t         *const lowest_pn,
                                vtss_macsec_sak_t             *const sak,
                                BOOL                          *const active,
                                vtss_macsec_ssci_t            *const ssci)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_D(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_get_priv(vtss_state, secy_id, port, sci, an, lowest_pn, sak, active, ssci);
    }
    VTSS_EXIT();

    if (rc == VTSS_RC_OK) {
        VTSS_D("-> pn:%"PRIu64", active:%s", lowest_pn->xpn, BOOL_ARG(*active));
    }
    return rc;
}

vtss_rc vtss_macsec_rx_seca_lowest_pn_update(const vtss_inst_t            inst,
                                             const vtss_macsec_port_t     port,
                                             const vtss_macsec_sci_t      *const sci,
                                             const u16                    an,
                                             const vtss_macsec_pkt_num_t  lowest_pn)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_SCI_AN_FMT", pn: %"PRIu64, MPORT_SCI_AN_ARG(port, *sci, an),
           lowest_pn.xpn);
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_lowest_pn_update_priv(vtss_state, secy_id, port, sci, an, lowest_pn);
    }
    VTSS_EXIT();
    return rc;
}

static BOOL one_tx_an_in_use(vtss_macsec_internal_secy_t *secy)
{
    u32 an;

    an = secy->tx_sc.status.encoding_sa;
    if (secy->tx_sc.sa[an] == NULL) {
        return 0;
    }
    if ((secy->tx_sc.sa[an]->in_use) && (secy->tx_sc.sa[an]->enabled)) {
        return 1;
    }

    return 0;
}

static vtss_rc vtss_macsec_tx_sa_set_priv(vtss_state_t                   *vtss_state,
                                          const u32                      secy_id,
                                          const vtss_macsec_port_t       port,
                                          const u16                      an,
                                          const vtss_macsec_pkt_num_t    next_pn,
                                          const BOOL                     confidentiality,
                                          const vtss_macsec_sak_t        *const sak,
                                          const vtss_macsec_ssci_t       *const ssci)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    vtss_macsec_match_pattern_t *match = &secy->pattern[VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT][VTSS_MACSEC_DIRECTION_EGRESS];
    u32 record = 0;
    mepa_timeofday_t tod;
    BOOL create_record = 1;
    vtss_macsec_internal_secy_t secy_tmp;
    vtss_macsec_internal_tx_sa_t sa_tmp;

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    VTSS_MACSEC_ASSERT(!secy->tx_sc.in_use,             "No TxSC installed");

    if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        if ( (!vtss_state->sync_calling_private) &&
             (!vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg)) {
            VTSS_RC(is_ssci_valid(vtss_state, port.port_no, TRUE, &secy->sci, ssci, sak));
        }
    }
    VTSS_I("sync_calling: %u, speed_change: %u, warm_start: %u",
           vtss_state->sync_calling_private, vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg,
           vtss_state->warm_start_cur);
    if (vtss_state->sync_calling_private) {
        if (secy->tx_sc.sa[an] == NULL) {
            return VTSS_RC_OK;
        }
        record = secy->tx_sc.sa[an]->record;
    }

    if (!vtss_state->sync_calling_private) {
        if ((secy->tx_sc.sa[an] != NULL) &&
            (!vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg)) {
            VTSS_E("Tx AN:%u is in use", an);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE);
        } else if (vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg &&
                   (secy->tx_sc.sa[an] == NULL) &&
                   (!vtss_state->warm_start_cur)) {
            return VTSS_RC_OK;
        }
        if (vtss_state->warm_start_cur) {
            secy_tmp = *secy;
            secy_tmp.tx_sc.sa[an] = &sa_tmp;
            secy_tmp.tx_sc.sa[an]->sak = *sak;
            secy_tmp.tx_sc.sa[an]->status.pn_status.next_pn = next_pn;
            if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
                (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
                memcpy(secy_tmp.tx_sc.sa[an]->ssci.buf, ssci->buf, sizeof(vtss_macsec_ssci_t));
            }
            if (record_inuse_get(vtss_state, port.port_no, EGRESS, &secy_tmp, an, 0, &record) != VTSS_RC_OK) {
                vtss_state->macsec_conf[port.port_no].glb.warm_start_reg_changed = TRUE; // Signaling that a register for this port has changed.
                create_record = 1;
            } else {
                create_record = 0;
            }
        } else if (vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg) {
            create_record = 0;
            record = secy->tx_sc.sa[an]->record;
        }
        if (create_record && (record_empty_get(vtss_state, port.port_no, &record, EGRESS) != VTSS_RC_OK)) {
            VTSS_E("Could not get an empty record");
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_EMPTY_RECORD);
        }

        secy->tx_sc.sa[an] = &vtss_state->macsec_conf[port.port_no].tx_sa[record];
        secy->tx_sc.sa[an]->record = record;
        if (!vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg) {
            secy->tx_sc.sa[an]->sak = *sak;
            secy->tx_sc.sa[an]->confidentiality = confidentiality;
            if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
                (secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
                memcpy(secy->tx_sc.sa[an]->ssci.buf, ssci->buf, sizeof(vtss_macsec_ssci_t));
            }
        }
        /* Workaround for Packet Number Transmit (i.e. NextPN - 1) */
        if (vtss_state->warm_start_cur ||
            vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg) {
            secy->tx_sc.sa[an]->status.next_pn = next_pn.pn;
        } else {
            VTSS_MACSEC_ASSERT(next_pn.pn < 1, "NextPN should not be zero (0)");
            secy->tx_sc.sa[an]->status.next_pn = next_pn.pn - 1;
        }
        secy->tx_sc.sa[an]->status.pn_status.next_pn = next_pn;
        secy->tx_sc.sa[an]->in_use = 1;
        MEPA_TIME_OF_DAY(tod);
        secy->tx_sc.sa[an]->status.created_time = tod.sec; // TimeOfDay in seconds
    }
    if (vtss_state->warm_start_cur) {
        return VTSS_RC_OK;
    }

    if (macsec_sa_match_set(vtss_state, port.port_no, EGRESS, record, match, secy, 0, 0, 0, 0) != VTSS_RC_OK) {
        VTSS_E("Could not program the SA match");
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (macsec_sa_flow_set(vtss_state, port.port_no, EGRESS, record, secy, an, 0,
                           VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT) != VTSS_RC_OK) {
        VTSS_E("Could not program the SA flow");
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }
    if (macsec_sa_xform_set(vtss_state, port.port_no, EGRESS, record, secy, an, 0) != VTSS_RC_OK) {
        VTSS_E("Could not program the xform record");
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM);
    }

    if (!one_tx_an_in_use(secy)) { /* When more than one AN are in use we use 'toggle' to change between SA's  */
        if (macsec_sa_enable(vtss_state, port.port_no, record, EGRESS, MACSEC_ENABLE) != VTSS_RC_OK) {
            VTSS_E("Could not enable the SA, record:%d, port_no:%d, port_id:%d, secy_id:%d", record, port.port_no, port.port_id, secy_id);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_tx_sa_activate_priv(vtss_state_t                  *vtss_state,
                                               const u32                     secy_id,
                                               const vtss_macsec_port_t      port,
                                               const u16                     an)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    mepa_timeofday_t tod;
    u32 old_an, i;
    BOOL an_in_use = 0;

    if (vtss_state->sync_calling_private) {
        if (secy->tx_sc.sa[an] == NULL) {
            return VTSS_RC_OK;
        }
        if (!secy->tx_sc.sa[an]->enabled) {
            return VTSS_RC_OK;
        }
    } else if ((!vtss_state->sync_calling_private) &&
               (secy->tx_sc.sa[an] == NULL) &&
               (vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg)) {
        return VTSS_RC_OK;
    }

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    VTSS_MACSEC_ASSERT(secy->tx_sc.sa[an] == NULL, "AN does not exist");
    VTSS_MACSEC_ASSERT(!secy->tx_sc.sa[an]->in_use, "AN is not in use");

    old_an = secy->tx_sc.status.encoding_sa;
    if (secy->tx_sc.sa[old_an] != NULL) {
        an_in_use = secy->tx_sc.sa[old_an]->enabled;
    }

    /* Activate chip SA Flow */
    if (an_in_use && (old_an < VTSS_MACSEC_SA_PER_SC_MAX) && (old_an != an)) {
        if (VTSS_RC_COLD(macsec_sa_inuse(vtss_state, port.port_no, secy->tx_sc.sa[an]->record, EGRESS, MACSEC_ENABLE)) != VTSS_RC_OK) {
            VTSS_E("Could not set SA:%u to 'in_use'", secy->tx_sc.sa[an]->record);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
        }
        if (VTSS_RC_COLD(macsec_sa_toggle(vtss_state, port.port_no, secy->tx_sc.sa[an]->record, secy->tx_sc.sa[old_an]->record, EGRESS)) != VTSS_RC_OK) {
            VTSS_E("Could not toggle SA:%u -> %u", an, old_an);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA);
        }
    } else {
        if (VTSS_RC_COLD(macsec_sa_inuse(vtss_state, port.port_no, secy->tx_sc.sa[an]->record, EGRESS, MACSEC_ENABLE)) != VTSS_RC_OK) {
            VTSS_E("Could not set SA:%u to 'in_use'", secy->tx_sc.sa[an]->record);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
        }
        /* Enable chip SA Flow */
        if (macsec_sa_enable(vtss_state, port.port_no, secy->tx_sc.sa[an]->record, EGRESS, MACSEC_ENABLE) != VTSS_RC_OK) {
            VTSS_E("Could not enable the SA, record:%d, port_no:%d, port_id:%d, secy_id:%d", secy->tx_sc.sa[an]->record, port.port_no, port.port_id, secy_id);
            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
        }

    }
    if (vtss_state->sync_calling_private) {
        return VTSS_RC_OK;
    }
    if (an_in_use && (old_an < VTSS_MACSEC_SA_PER_SC_MAX)) {
        secy->tx_sc.sa[old_an]->enabled = 0;
        secy->tx_sc.sa[old_an]->status.in_use = 0;
    }

    MEPA_TIME_OF_DAY(tod);
    secy->tx_sc.sa[an]->status.started_time = tod.sec; // TimeOfDay in seconds
    secy->tx_sc.sa[an]->enabled = 1;
    secy->tx_sc.sa[an]->status.in_use = 1;

    an_in_use = 0;
    for (i = 0; i < VTSS_MACSEC_SA_PER_SC_MAX; i++ ) {
        if (secy->tx_sc.sa[i] == NULL || (i == an)) {
            continue;
        }
        if (secy->tx_sc.sa[i]->in_use) {
            an_in_use = 1;
            break;
        }
    }

    if (!an_in_use) {
        secy->tx_sc.status.started_time = tod.sec;
    }
    secy->tx_sc.status.encoding_sa = an;
    secy->tx_sc.status.enciphering_sa = an;
    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_rx_sa_activate_priv(vtss_state_t                  *vtss_state,
                                               const u32                     secy_id,
                                               const vtss_macsec_port_t      port,
                                               const vtss_macsec_sci_t       *const sci,
                                               const u16                     an)
{
    mepa_timeofday_t tod;
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 sc, i, sa_in_use = 0;

    VTSS_RC(sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc));

    if (vtss_state->sync_calling_private) {
        if (secy->rx_sc[sc]->sa[an] == NULL) {
            return VTSS_RC_OK;
        }
        if (!secy->rx_sc[sc]->sa[an]->status.in_use) {
            return VTSS_RC_OK;
        }
    } else if ((!vtss_state->sync_calling_private) &&
               (secy->rx_sc[sc]->sa[an] == NULL) &&
               (vtss_state->macsec_conf[port.port_no].glb.spd_change_macsec_recfg)) {
        return VTSS_RC_OK;
    }

    VTSS_RC(is_sci_valid(vtss_state, port.port_no, sci));
    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    VTSS_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");

    /* Activate chip SA Flow */
    if (VTSS_RC_COLD(macsec_sa_inuse(vtss_state, port.port_no, secy->rx_sc[sc]->sa[an]->record, INGRESS, MACSEC_ENABLE)) != VTSS_RC_OK) {
        VTSS_E("Could not set SA:%u to 'in_use'", secy->rx_sc[sc]->sa[an]->record);
        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }

    if (vtss_state->sync_calling_private) {
        return VTSS_RC_OK;
    }

    MEPA_TIME_OF_DAY(tod);
    secy->rx_sc[sc]->sa[an]->status.started_time = tod.sec; // TimeOfDay in seconds
    secy->rx_sc[sc]->sa[an]->status.in_use = 1;
    secy->rx_sc[sc]->sa[an]->enabled = 1;

    for (i = 0; i < VTSS_MACSEC_SA_PER_SC_MAX; i++ ) {
        if (secy->rx_sc[sc]->sa[i] == NULL || (i == an)) {
            continue;
        }
        if (secy->rx_sc[sc]->sa[i]->in_use) {
            sa_in_use = 1;
            break;
        }
    }
    if (!sa_in_use) {
        secy->rx_sc[sc]->status.started_time = tod.sec;
    }
    return VTSS_RC_OK;
}

// Function for setting sequencing number threshold
// In/out - Same as vtss_macsec_event_seq_threshold_set (except inst), See vtss_macsec_api.h
static vtss_rc vtss_macsec_event_seq_threshold_set_priv(vtss_state_t         *vtss_state,
                                                        const vtss_port_no_t port_no,
                                                        const u32            threshold)
{
    CSR_WARM_WR(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_SEQ_NUM_THRESH, threshold);
    return VTSS_RC_OK;
}


// Function for getting sequencing number threshold
// In/out - Same as vtss_macsec_event_seq_threshold_get (except inst), See vtss_macsec_api.h
static vtss_rc vtss_macsec_event_seq_threshold_get_priv(vtss_state_t         *vtss_state,
                                                        const vtss_port_no_t port_no,
                                                        u32                  *threshold)
{
    CSR_RD(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_SEQ_NUM_THRESH, threshold);
    return VTSS_RC_OK;
}

#define VTSS_MACSEC_THRESHOLD_EVENT_ENABLE_BIT 20 //See vtss_venice_reg_macsec_egr.h "Sequence Number Threshold"
#define VTSS_MACSEC_ROLLOVER_EVENT_ENABLE_BIT 21 //See vtss_venice_reg_macsec_egr.h "Sequence Number roll-over" 

#define VTSS_MACSEC_THRESHOLD_EVENT_STATUS_BIT 4 //See vtss_venice_reg_macsec_egr.h "Sequence Number Threshold"
#define VTSS_MACSEC_ROLLOVER_EVENT_STATUS_BIT 5 //See vtss_venice_reg_macsec_egr.h "Sequence Number roll-over" 

#ifdef VTSS_CHIP_10G_PHY
#define MALIBU_MAX_CHANNEL_ID 4
#endif
// Function for setting interrupt events
// In/out - Same as vtss_macsec_event_enable_set (except inst), See vtss_macsec_api.h
static vtss_rc vtss_macsec_event_enable_set_priv(vtss_state_t              *vtss_state,
                                                 const vtss_port_no_t      port_no,
                                                 const vtss_macsec_event_t ev_mask,
                                                 const BOOL                enable)
{
    u32 mask  = 0;
    u32 value = 0;
    BOOL    phy10g;
#ifdef VTSS_CHIP_10G_PHY
    u8 channel_id;
#endif
    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));

    if ( phy10g) {
#ifdef VTSS_CHIP_10G_PHY
        if (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU) {
            /*  Route to AGGR Interrupt '0' for Malibu Family */
            /*  Currently only Egress interrupts enabled */
            CSR_WARM_WRM(port_no, VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR(1),
                         VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_MSEC_EGR_INTR_EN,
                         VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_MSEC_EGR_INTR_EN);
            for (channel_id  = 0; channel_id < MALIBU_MAX_CHANNEL_ID; channel_id++) {
                CSR_WARM_WRM(port_no, VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN(0),
                             VTSS_BIT((2 * channel_id) + 1), VTSS_BIT((2 * channel_id) + 1));
            }
        }
#endif
    }
    if (ev_mask & VTSS_MACSEC_SEQ_THRESHOLD_EVENT) {
        mask |= 1 << VTSS_MACSEC_THRESHOLD_EVENT_ENABLE_BIT;
        if (enable) {
            value |= 1 << VTSS_MACSEC_THRESHOLD_EVENT_ENABLE_BIT;
        } else {
            value &= ~(1 << VTSS_MACSEC_THRESHOLD_EVENT_STATUS_BIT);
        }
    }

    if (ev_mask & VTSS_MACSEC_SEQ_ROLLOVER_EVENT) {
        mask |= 1 << VTSS_MACSEC_ROLLOVER_EVENT_ENABLE_BIT;
        if (enable) {
            value |= 1 << VTSS_MACSEC_ROLLOVER_EVENT_ENABLE_BIT;
        } else {
            value &= ~(1 << VTSS_MACSEC_ROLLOVER_EVENT_STATUS_BIT);
        }

    }
    /* Enable interrupt propagation on egress side */
    if (enable) {
        if (ev_mask) {
            CSR_WARM_WRM(port_no, VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL,
                         VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL_ENABLE_CONTROL(0xF),
                         VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CTRL_ENABLE_CONTROL);

            CSR_WARM_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK,
                         VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK,
                         VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK);
        }
    } else {
        CSR_WARM_WRM(port_no, VTSS_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR,
                     VTSS_F_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR_INTERRUPT_DISABLE(0xF),
                     VTSS_M_MACSEC_EGR_ADV_INTR_CTRL_REGS_AIC_ENABLE_CLR_INTERRUPT_DISABLE);
        CSR_WARM_WRM(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK,
                     0, VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK);
    }
    CSR_WARM_WRM(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS, value, mask);
    VTSS_I("value:0x%X, mask:0x%X", value, mask);
    return VTSS_RC_OK;
}

// Function for getting interrupt events
// In/out - Same as vtss_macsec_event_enable_get (except inst), See vtss_macsec_api.h
static vtss_rc vtss_macsec_event_enable_get_priv(vtss_state_t              *vtss_state,
                                                 const vtss_port_no_t      port_no,
                                                 vtss_macsec_event_t       *ev_mask)
{

    u32 value;
    CSR_RD(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS, &value);

    *ev_mask = 0;

    if (value & (1 << VTSS_MACSEC_THRESHOLD_EVENT_ENABLE_BIT)) {
        *ev_mask |= VTSS_MACSEC_SEQ_THRESHOLD_EVENT;
    }

    if (value & (1 << VTSS_MACSEC_ROLLOVER_EVENT_ENABLE_BIT)) {
        *ev_mask |= VTSS_MACSEC_SEQ_ROLLOVER_EVENT;
    }

    VTSS_I("value:0x%X, ev_mask:0x%X", value, *ev_mask);
    return VTSS_RC_OK;
}

// Function for getting polling events
// In/out - Same as vtss_macsec_event_poll (except inst), See vtss_macsec_api.h
static vtss_rc vtss_macsec_event_poll_priv(vtss_state_t              *vtss_state,
                                           const vtss_port_no_t      port_no,
                                           vtss_macsec_event_t       *ev_mask)
{

    u32 value, val = 0;
    BOOL    phy10g;
#ifdef VTSS_CHIP_10G_PHY
    u8 aggr_int;
    u32 aggr_int_chip[4], channel_int;
    u32 aggr_int_1 = 0;
#endif

    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
    if (phy10g) {
#ifdef VTSS_CHIP_10G_PHY
        if (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU) {
            /*Read all the aggr_int[i], Malibu interrupts supported at aggr_intr[0]*/
            VTSS_D("Enter %s\n", __func__);
            memset (aggr_int_chip, 0, sizeof(aggr_int_chip));
            for (aggr_int = 0; aggr_int < 4; aggr_int++) {
                CSR_RD(port_no, VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT(aggr_int), &aggr_int_chip[aggr_int]);
            }
            aggr_int_1 = aggr_int_chip[0];
            /* interrupt on CH0_INTR1_STAT/CH1_INTR1_STAT/CH2_INTR1_STAT/CH0_INTR1_STAT */
            if ((aggr_int_1 & 0x2) || (aggr_int_1 & 0x8) || (aggr_int_1 & 0x20) || (aggr_int_1 & 0x80)) {
                CSR_RD(port_no, VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT(1), &channel_int);
                /*read status at intr0*/
                if (!(channel_int & 0x40)) {
                    VTSS_I("No Macsec events on Malibu PHY port::%d", port_no);
                    return VTSS_RC_OK;
                }
            }
        }
#endif
    }
    CSR_RD(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS, &value);
    val = value;
    *ev_mask = 0;

    if (value & (1 << VTSS_MACSEC_THRESHOLD_EVENT_STATUS_BIT)) {
        VTSS_I("value:0x%X, ev_mask:0x%X", value, *ev_mask);
        val = (val & (~(1 << VTSS_MACSEC_THRESHOLD_EVENT_STATUS_BIT)));
        *ev_mask |= VTSS_MACSEC_SEQ_THRESHOLD_EVENT;
    }

    if (value & (1 << VTSS_MACSEC_ROLLOVER_EVENT_STATUS_BIT)) {
        *ev_mask |= VTSS_MACSEC_SEQ_ROLLOVER_EVENT;
        val = (val & (~(1 << VTSS_MACSEC_ROLLOVER_EVENT_STATUS_BIT)));
        VTSS_I("value:0x%X, ev_mask:0x%X", value, *ev_mask);
    }
    /* Clear the status */
    CSR_WR(port_no, VTSS_MACSEC_EGR_CRYPTO_CTRL_STATUS_REGS_INTR_CTRL_STATUS, val);
//    VTSS_I("value:0x%X, ev_mask:0x%X", value, *ev_mask);
    return VTSS_RC_OK;
}



// Function for configuring capture FIFO
// In/out - Same as vtss_macsec_frame_capture_set (except inst), See vtss_macsec_api.h

// Procedure for capturing frames.
// 1)   Decide the SIDE and MAX_PKT_SIZE and program in CAPT_DEBUG_CTRL.
// 2)   Enable the SA on which you want to capture the first packet. For enabling capture on any SA, program CAPT_DEBUG_TRIGGER_SA1/SA2 = 0xFFFFFFFF. Or if you want to enable capture on SA index [0], then program CAPT_DEBUG_TRIGGER_SA1 = 0x1
// 3)   Enable the capture by programming CAPT_DEBUG_TRIGGER.ENABLE = 1.
// 4)   Send frames.
// 5)   Keep polling CAPT_DEBUG_STATUS to see if any frames have been captured (PKT_COUNT, FULL, WR_PTR).
// 6)   If PKT_COUNT > 0, then frames have been captured, read CAPT_DEBUG_TRIGGER_SA1/SA2 to confirm if the packet for that SA has been captured. Bits will fall back to 0b automatically when a packet was indeed captured, for the SA for which packet was enabled.
// 7)   Stop the capture by programming CAPT_DEBUG_TRIGGER.ENABLE = 0. This is to enable SW to access the fifo.
// 8)   Read CAPT_DEBUG_DATA (0 to 127) to read the packet from capture fifo.

static vtss_rc vtss_macsec_frame_capture_set_priv(vtss_state_t                        *vtss_state,
                                                  const vtss_port_no_t                port_no,
                                                  const vtss_macsec_frame_capture_t   capture)
{
    BOOL  phy10g;

    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
    /* VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA2 does not exist for 1G devices,
     this offset in 1G corresponds to VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER for 1G devices*/

    // We disables all triggers
    CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA1, 0x0);
    CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA2, 0x0);

    if (phy10g) {
        CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER, 0x0);
    }

    if (capture != VTSS_MACSEC_FRAME_CAPTURE_DISABLE) {
        VTSS_I("Capture %s, Max packet size = %u Bytes",
               capture == VTSS_MACSEC_FRAME_CAPTURE_INGRESS ? "ingress" : "egress", VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX);

        // Select ingress/egress side + Max pkt size
        CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL,
               (capture == VTSS_MACSEC_FRAME_CAPTURE_INGRESS ? VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL_SIDE : 0) |
               VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_CTRL_MAX_PKT_SIZE(VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX / 8));


        VTSS_I("Enabling capturing of all SA indexes, %s capturing", capture == VTSS_MACSEC_FRAME_CAPTURE_DISABLE ? "Disabling" : "Enabling");

        // We enables all triggers

        if (phy10g) {
            CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA1, 0xFFFFFFFF);
            CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA2, 0xFFFFFFFF);
            CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER, VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_ENABLE);
        } else {
            CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA1, 0xFFFF);
            CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA2, VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_ENABLE);
        }

    }

    return VTSS_RC_OK;
}

// Function for getting one frame from the capture FIFO
// In/out - Same as vtss_macsec_frame_get (except inst), See vtss_macsec_api.h
static vtss_rc vtss_macsec_frame_get_priv(vtss_state_t                  *vtss_state,
                                          const vtss_port_no_t          port_no,
                                          const u32                     buf_length,
                                          u32                           *const frm_length,
                                          u8                            *const frame)
{
    const u8 header_size = 2; // Header size (in 32bits)
    u8 i;
    u32 value = 1;
    u8 wr_ptr;
    BOOL truncated;
    u32 adm_hdr0;
    u32 adm_hdr1;
    u32  frm_data_i;
    u8 frm_cnt; // Number of frame in the capture buffer
    BOOL phy10g;

    *frm_length = 0;

    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));

    // Get the amount of data in the FIFO
    CSR_RD(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS, &value);

    wr_ptr = VTSS_X_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_WR_PTR(value);
    frm_cnt = VTSS_X_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_STATUS_PKT_COUNT(value);

    if (frm_cnt == 0) { // No frames captured
        return VTSS_RC_OK;
    }

    if (buf_length < VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX) {
        VTSS_E("Buffer must be greater than %u bytes, buf_length:%d, port_no:%d, frm_cnt:%d, wr_ptr:%d", VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX, buf_length, port_no, frm_cnt, wr_ptr);
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_BUFFER_TOO_SMALL);
    }

    // Disable the triggers in order to be able to read the FIFO.
    if (phy10g) {
        CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER, 0);
    }
    CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA2, 0);
    CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA1, 0);


    // The first 64bits of the frame captured is an administration header with consist of two 32bits words, namde ADM_HDR0 and ADM_HDR1
    // The Administration header contains the packet size which indicates where the next packet would start.
    // The format of Administration header is
    // ADM_HDR0 = {22bits reserved, 1-bit truncated, 9-bit pkt_size}
    // Truncated (1-bit) -> Indicates the packet is truncated and only a part of the packet is captured.
    // The captured packet could be truncated because the packet could be bigger than the "MAX_PKT_SIZE" programmed by software to capture.
    // Pkt_size (9-bits) -> Indicates the size of the captured packet in bytes. Add 8 to the pkt_size to reach to the next packet.
    // ADM_HDR1 = 32-bit security fail debug code.
    CSR_RD(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_DATA(0), &adm_hdr0);
    CSR_RD(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_DATA(1), &adm_hdr1);

    truncated = (adm_hdr0 & 0x200) ? TRUE : FALSE;      // Determine if frame is truncated
    *frm_length = (adm_hdr0 & 0x1FF); //9 bits packet size.

    VTSS_I("Frame size:%u, truncated:%u, adm_hdr1:0x%X, adm_hdr0:0x%X, wr_ptr:%u, value:0x%X", *frm_length, truncated, adm_hdr1, adm_hdr0, wr_ptr, value);

    // Make sure that frame length is not greater than the amount of data in fifo, which should never happen (wr_ptr uses step of 8 bytes)
    if ((u32)(*frm_length + header_size) >= (u32)(wr_ptr * 8))  {
        VTSS_E("Frame length (%u bytes) is supposed to be less than the amount of data in the fifo (%u bytes), header_size:%d",
               *frm_length, wr_ptr * 8, header_size);
        *frm_length = wr_ptr;
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_FRAME_TOO_LONG);
    }

    // Get the frame data from the FIFO
    frm_data_i = 0;
    for (i = header_size; i <= *frm_length / 4 + header_size; i++) {
        CSR_RD(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_DATA(i), &value);
        frame[frm_data_i++] = value & 0x00000FF;
        frame[frm_data_i++] = (value & 0x0000FF00) >> 8;
        frame[frm_data_i++] = (value & 0x00FF0000) >> 16;
        frame[frm_data_i++] = (value & 0xFF000000) >> 24;
        VTSS_I("Getting FIFO data:0x%X, i:%d", value, i);
    }

    // Re-enable capture in order to capture next frame.

    if (phy10g) {
        CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER, VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_ENABLE);
        CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA2, 0xFFFFFFFF);
        CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA1, 0xFFFFFFFF);
    } else {
        CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA2, VTSS_F_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_ENABLE);
        CSR_WR(port_no, VTSS_MACSEC_EGR_CAPT_DEBUG_REGS_CAPT_DEBUG_TRIGGER_SA1, 0xFFFF);
    }

    // We use error state to signal that frame is not valid
    if (truncated) {
        VTSS_E("Frame is Truncated, port_no:%d, frm_length:%d, header_size:%d", port_no, *frm_length, header_size);
        return dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_FRAME_TRUNCATED);
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_controlled_counters_get_priv(vtss_state_t                      *vtss_state,
                                                        const vtss_macsec_port_t          port,
                                                        vtss_macsec_secy_port_counters_t  *const counters,
                                                        u32                               secy_id)
{
    u16 an;
    u32 sc, max_sc_rx;
    vtss_macsec_secy_counters_t  secy_counters;
    vtss_macsec_internal_secy_t  *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    vtss_macsec_rx_sa_counters_t rx_sa_counters;
    vtss_macsec_tx_sa_counters_t tx_sa_counters;
    vtss_macsec_rx_sc_counters_t rx_sc_cnt;
    u64                          in_pkts_not_valid = 0;
    u64                          in_pkts_not_using_sa = 0;
    macsec_secy_in_use_iter_t in_use_inter;

    // Get Secy counters
    u64 in_pkts_bad_tag  = 0;
    u64 in_pkts_no_sci   = 0;
    u64 in_pkts_no_tag   = 0;
    u64 in_pkts_overrun  = 0;
    u64 out_pkts_too_long = 0;
    u64 if_out_octets    = 0;
    u8  octets_add       = 0;
    u64 in_octets_validation_disabled = 0;

    memset(counters, 0, sizeof(vtss_macsec_secy_port_counters_t));
    memset(&rx_sc_cnt, 0, sizeof(vtss_macsec_rx_sc_counters_t));
    memset(&secy_counters, 0, sizeof(vtss_macsec_secy_counters_t));

    vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_out_octets = 0;

    // Call the read of hardware counters in order to update the software counters
    VTSS_RC(vtss_macsec_secy_counters_get_priv(vtss_state, port.port_no, &secy_counters, secy_id));

    in_pkts_bad_tag   += secy_counters.in_pkts_bad_tag;
    in_pkts_no_sci    += secy_counters.in_pkts_no_sci;
    in_pkts_no_tag    += secy_counters.in_pkts_no_tag;
    in_pkts_overrun   += secy_counters.in_pkts_overrun;
    out_pkts_too_long += secy_counters.out_pkts_too_long;
    if_out_octets     += secy_counters.out_octets_protected + secy_counters.out_octets_encrypted;
    if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb == TRUE) {
        if_out_octets += vtss_state->macsec_conf[port.port_no].secy[secy_id].tx_sc.out_octets_untagged;
    }

    vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_pkts  = 0;
    vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_out_pkts = 0;

    VTSS_N("if_in_octets:%" PRIu64 "", counters->if_in_octets);

    if (phy_is_1g(vtss_state, port.port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    if (secy != NULL && secy->in_use) {
        VTSS_N("secy_id:%u, in_use:%u", secy_id, secy->in_use);
        VTSS_N("Calculate RX SA counters");
        for (sc = 0; sc < max_sc_rx; sc++) {
            if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
                continue;
            }
            VTSS_D("rx_sc[sc] i_use");

            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
                    continue;
                }
                VTSS_I("sc:%u an:%u, in_use:%u", sc, an, secy->rx_sc[sc]->sa[an]->in_use);
                VTSS_RC(vtss_macsec_rx_sa_counters_get_priv(vtss_state, port.port_no, &secy->rx_sc[sc]->sci, an, &rx_sa_counters, secy_id));
                vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_pkts += rx_sa_counters.in_pkts_ok + rx_sa_counters.in_pkts_invalid + rx_sa_counters.in_pkts_not_using_sa + rx_sa_counters.in_pkts_unused_sa + rx_sa_counters.in_pkts_unchecked + rx_sa_counters.in_pkts_delayed + rx_sa_counters.in_pkts_late;
            }
            if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb == TRUE) {
                in_octets_validation_disabled += secy->rx_sc[sc]->in_octets_validation_disabled;
            }
        }
        VTSS_N("Calculate TX SA counters");
        for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
            if (secy->tx_sc.sa[an] == NULL || !secy->tx_sc.in_use) {
                continue;
            }
            VTSS_RC(vtss_macsec_tx_sa_counters_get_priv(vtss_state, port.port_no, an, &tx_sa_counters, secy_id));

            vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_out_pkts += tx_sa_counters.out_pkts_encrypted + tx_sa_counters.out_pkts_protected;
            VTSS_D("if_out_pkts:%" PRIu64 "", vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_out_pkts);
        }
        if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb == TRUE) {
            vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_out_pkts += secy_counters.out_pkts_untagged;
        }

        // Controlled.if_in_octets is the sum of SA.InOctetsDecrypted/InOctetsValidated + 12/16/20/x (12 - standard mode, 16 or 20 - vlan tag bypass, x - MPLS header bypass mode)
        // Controlled.if_out_octets = sum of SA.OutOctetsEncrypted/OutOctetsProtected + 12/16/20/x (12 - standard mode, 16 or 20 - vlan tag bypass, x - MPLS header bypass mode) for that SecY.
        octets_add = 12; // This 12 bytes are the DMAC and SMAC

        if (vtss_state->macsec_conf[port.port_no].glb.bypass_mode.mode == VTSS_MACSEC_BYPASS_TAG) {
            if (secy->tag_bypass == VTSS_MACSEC_BYPASS_TAG_ONE) {
                octets_add += 4; // This is the 16 (12+4) in calculation above
            } else if (secy->tag_bypass == VTSS_MACSEC_BYPASS_TAG_TWO) {
                octets_add += 8; // This is the 20 (12+8) in calculation above
            }
        } else if (vtss_state->macsec_conf[port.port_no].glb.bypass_mode.mode == VTSS_MACSEC_BYPASS_HDR) {
            // This is the x (12+8) in calculation above
            octets_add += vtss_state->macsec_conf[port.port_no].glb.bypass_mode.hdr_bypass_len;
        }

        vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_out_octets += if_out_octets + (vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_out_pkts * octets_add);

        if ((secy->conf.validate_frames != VTSS_MACSEC_VALIDATE_FRAMES_DISABLED) ||
            ((secy->conf.validate_frames == VTSS_MACSEC_VALIDATE_FRAMES_DISABLED) &&
             (vtss_state->macsec_conf[port.port_no].glb.macsec_revb == TRUE))) {
            vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_octets = secy_counters.in_octets_validated + secy_counters.in_octets_decrypted + in_octets_validation_disabled + octets_add * vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_pkts;
        } else {
            // Work-around for Bugzilla#12752/Errata 012. This shall only be done for revision A when validate_frames is disabled.
            vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_octets = 0;
        }

        VTSS_D("if_in_octets:%" PRIu64 ", octets_add:%d, vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_pkts:%" PRIu64 ", validated:%" PRIu64 ", decrypt:%" PRIu64 "",
               vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_octets,
               octets_add, vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_pkts,
               secy_counters.in_octets_validated, secy_counters.in_octets_decrypted);

        // Get rx_sc counter
        for (sc = 0; sc < max_sc_rx; sc++) {
            if (secy->rx_sc[sc] == NULL) {
                continue;
            }

            VTSS_RC(vtss_macsec_rx_sc_counters_get_priv(vtss_state,
                                                        port.port_no,
                                                        &secy->rx_sc[sc]->sci,
                                                        &rx_sc_cnt,
                                                        secy_id));

            in_pkts_not_valid    += rx_sc_cnt.in_pkts_not_valid;
            in_pkts_not_using_sa += rx_sc_cnt.in_pkts_not_using_sa;
        }

        // From IEEE 802.1AE-2006, page 57- The ifOutErrors count is equal to the OutPktsTooLong count (Figure 10-4).
        vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_out_errors = out_pkts_too_long;


        VTSS_D("secy_id:%u, in_use:%u", secy_id, secy->in_use);
        // From IEEE 802.1AE-2006, page 57 - The ifInErrors count is the sum of all the
        // InPktsBadTag,
        // InPktsNoSCI,
        // InPktsNotUsingSA, and
        // InPktsNotValid
        macsec_secy_in_use_inter_init(&in_use_inter);
        while (macsec_secy_in_use_inter_getnext(vtss_state, port.port_no, &in_use_inter)) {
            if (in_use_inter.secy_id != secy_id) {
                /* The below set of 4 counters are read from global registers. So, they are common for all Secys */
                VTSS_RC(vtss_macsec_secy_counters_get_priv(vtss_state, port.port_no, &secy_counters, in_use_inter.secy_id));
                in_pkts_bad_tag = (in_pkts_bad_tag >= secy_counters.in_pkts_bad_tag) ? in_pkts_bad_tag : secy_counters.in_pkts_bad_tag;
                in_pkts_no_sci  = (in_pkts_no_sci >= secy_counters.in_pkts_no_sci) ? in_pkts_no_sci : secy_counters.in_pkts_no_sci;
                in_pkts_no_tag  = (in_pkts_no_tag >= secy_counters.in_pkts_no_tag) ? in_pkts_no_tag : secy_counters.in_pkts_no_tag;
                in_pkts_overrun = (in_pkts_overrun >= secy_counters.in_pkts_overrun) ? in_pkts_overrun : secy_counters.in_pkts_overrun;
            }
        }
        vtss_state->macsec_conf[port.port_no].glb.common_cnt.if_in_errors =
            in_pkts_bad_tag +
            in_pkts_no_sci +
            in_pkts_not_valid +
            in_pkts_not_using_sa;

        // From IEEE 802.1AE-2006, page 57 - The ifInDiscards count is the sum of all the
        // InPktsNoTag,
        // InPktsLate, and
        // InPktsOverrun counts.
        VTSS_D("in_pkts_no_tag:%" PRIu64 ", rx_sc_cnt.in_pkts_late:%" PRIu64 ", in_pkts_overrun:%" PRIu64 "", in_pkts_no_tag, rx_sc_cnt.in_pkts_late, in_pkts_overrun);

        vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt.if_in_discards =
            in_pkts_no_tag +
            rx_sc_cnt.in_pkts_late +
            in_pkts_overrun;

        memcpy(counters, &vtss_state->macsec_conf[port.port_no].secy[secy_id].controlled_cnt, sizeof(vtss_macsec_secy_port_counters_t));
    }
    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_common_counters_get_priv(vtss_state_t                      *vtss_state,
                                                    const vtss_port_no_t              port_no,
                                                    vtss_macsec_common_counters_t     *const counters,
                                                    BOOL                              clear)
{

    //
    // First update counters
    //
    u32 rx_uc_cnt;
    u32 rx_bc_cnt;
    u32 rx_mc_cnt;
    u64 rx_ok_cnt;
    u64 tx_ok_cnt;
    u32 tx_uc_cnt;
    u32 tx_bc_cnt;
    u32 tx_mc_cnt;
    u32 msb;
    u32 lsb;

    // Secy counters
    u64 in_pkts_bad_tag      = 0;
    u64 in_pkts_no_sci       = 0;
    u64 in_pkts_no_tag       = 0;
    u64 in_pkts_overrun      = 0;
    u64 out_pkts_too_long    = 0;
    u64 in_pkts_not_valid    = 0;
    u64 in_pkts_not_using_sa = 0;
    u64 in_pkts_late         = 0;

    macsec_secy_in_use_iter_t in_use_inter;
    vtss_macsec_secy_counters_t   secy_counters;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_OK_BYTES_CNT, &lsb);
    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT, &msb);
    rx_ok_cnt = (((u64)msb << 32) + lsb);

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_UC_CNT, &rx_uc_cnt);
    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_MC_CNT, &rx_mc_cnt);
    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_BC_CNT, &rx_bc_cnt);

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT, &lsb);
    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT, &msb);
    tx_ok_cnt = (((u64)msb << 32) + lsb);

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_UC_CNT, &tx_uc_cnt);
    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_MC_CNT, &tx_mc_cnt);
    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_BC_CNT, &tx_bc_cnt);

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT, &lsb);
    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT, &msb);

    // Since HW doesn't support clear on read, we need to remember the counter value whenever
    // the user to clear the counters, in order to be able to compensate for the hw counter are not cleared.
    if (clear) {
        vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_octets          = rx_ok_cnt;
        vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_ucast_pkts      = rx_uc_cnt;
        vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_multicast_pkts  = rx_mc_cnt;
        vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_broadcast_pkts  = rx_bc_cnt;
        vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_octets         = tx_ok_cnt;
        vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_ucast_pkts     = tx_uc_cnt;
        vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_multicast_pkts = tx_mc_cnt;
        vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_broadcast_pkts = tx_bc_cnt;
        vtss_state->macsec_conf[port_no].glb.rmon_counters_clr = FALSE;
    }

    // Compensate for hw counters can't be cleared on read.
    if ((rx_ok_cnt >= vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_octets) &&
        (vtss_state->macsec_conf[port_no].glb.rmon_counters_clr == FALSE)) {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_octets = rx_ok_cnt - vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_octets;
    } else {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_octets = rx_ok_cnt;
    }

    if ((rx_uc_cnt >=  vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_ucast_pkts) &&
        (vtss_state->macsec_conf[port_no].glb.rmon_counters_clr == FALSE)) {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_ucast_pkts = rx_uc_cnt - vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_ucast_pkts;
    } else {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_ucast_pkts = rx_uc_cnt;
    }

    if ((rx_mc_cnt >= vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_multicast_pkts) &&
        (vtss_state->macsec_conf[port_no].glb.rmon_counters_clr == FALSE)) {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_multicast_pkts = rx_mc_cnt - vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_multicast_pkts;
    } else {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_multicast_pkts = rx_mc_cnt;
    }

    if ((rx_bc_cnt >= vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_broadcast_pkts) &&
        (vtss_state->macsec_conf[port_no].glb.rmon_counters_clr == FALSE)) {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_broadcast_pkts = rx_bc_cnt - vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_broadcast_pkts;
    } else {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_broadcast_pkts = rx_bc_cnt;
    }

    if ((tx_ok_cnt >= vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_octets) &&
        (vtss_state->macsec_conf[port_no].glb.rmon_counters_clr == FALSE)) {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_octets = tx_ok_cnt - vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_octets;
    } else {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_octets = tx_ok_cnt;
    }

    if ((tx_uc_cnt >= vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_ucast_pkts) &&
        (vtss_state->macsec_conf[port_no].glb.rmon_counters_clr == FALSE)) {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_ucast_pkts = tx_uc_cnt - vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_ucast_pkts;
    } else {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_ucast_pkts = tx_uc_cnt;
    }

    if ((tx_mc_cnt >= vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_multicast_pkts) &&
        (vtss_state->macsec_conf[port_no].glb.rmon_counters_clr == FALSE)) {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_multicast_pkts = tx_mc_cnt - vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_multicast_pkts;
    } else {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_multicast_pkts = tx_mc_cnt;
    }

    if ((tx_bc_cnt >= vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_broadcast_pkts) &&
        (vtss_state->macsec_conf[port_no].glb.rmon_counters_clr == FALSE)) {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_broadcast_pkts = tx_bc_cnt - vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_out_broadcast_pkts;
    } else {
        vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_broadcast_pkts = tx_bc_cnt;
    }

    // From IEEE 802.1AE-2006, page 57- The ifOutErrors count is equal to the OutPktsTooLong count (Figure 10-4).
    vtss_state->macsec_conf[port_no].glb.common_cnt.if_out_errors = out_pkts_too_long;


    VTSS_N("Ok bytes:%" PRIu64 ", clr:%" PRIu64 ", port:%u, lsb:%u, msb:%u",
           vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_octets,
           vtss_state->macsec_conf[port_no].glb.common_cnt_clr_val.if_in_octets,
           port_no, lsb, msb);


    macsec_secy_in_use_inter_init(&in_use_inter);

    while (macsec_secy_in_use_inter_getnext(vtss_state, port_no, &in_use_inter)) {
        // Call the read of hardware counters in order to update the software counters
        VTSS_RC(vtss_macsec_secy_counters_get_priv(vtss_state, port_no, &secy_counters, in_use_inter.secy_id));
        /* The below set of 4 counters are read from global registers. So, they are common for all Secys */
        in_pkts_bad_tag = (in_pkts_bad_tag >= secy_counters.in_pkts_bad_tag) ? in_pkts_bad_tag : secy_counters.in_pkts_bad_tag;
        in_pkts_no_sci  = (in_pkts_no_sci >= secy_counters.in_pkts_no_sci) ? in_pkts_no_sci : secy_counters.in_pkts_no_sci;
        in_pkts_no_tag  = (in_pkts_no_tag >= secy_counters.in_pkts_no_tag) ? in_pkts_no_tag : secy_counters.in_pkts_no_tag;
        in_pkts_overrun = (in_pkts_overrun >= secy_counters.in_pkts_overrun) ? in_pkts_overrun : secy_counters.in_pkts_overrun;

        out_pkts_too_long += secy_counters.out_pkts_too_long;
    }

    // From IEEE 802.1AE-2006, page 57 - The ifInErrors count is the sum of all the
    // InPktsBadTag,
    // InPktsNoSCI,
    // InPktsNotUsingSA, and
    // InPktsNotValid
    vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_errors =
        in_pkts_bad_tag +
        in_pkts_no_sci +
        in_pkts_not_valid +
        in_pkts_not_using_sa;

    // From IEEE 802.1AE-2006, page 57 - The ifInDiscards count is the sum of all the
    // InPktsNoTag,
    // InPktsLate, and
    // InPktsOverrun counts.
    vtss_state->macsec_conf[port_no].glb.common_cnt.if_in_discards =
        in_pkts_no_tag +
        in_pkts_late +
        in_pkts_overrun;


    //
    // 2nd, pass the counters back
    //
    memcpy(counters, &vtss_state->macsec_conf[port_no].glb.common_cnt, sizeof(*counters));
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_uncontrolled_counters_get_priv(vtss_state_t                        *vtss_state,
                                                          const vtss_port_no_t                port_no,
                                                          vtss_macsec_uncontrolled_counters_t *const counters)
{
    vtss_macsec_common_counters_t    common_counters;
    vtss_macsec_secy_port_counters_t controlled_counters;
    u32                              secy_id;
    u32                              max_secy;
    vtss_macsec_internal_secy_t      *secy;
    vtss_macsec_port_t                macsec_port;
    u64 ctrl_if_out_octets = 0;
#ifdef BYPASS_IEEE_SECTION_10_7_3
    u64 ctrl_if_in_octets  = 0;
#endif

    // From IEEE 802.1AE-2006 - Section 10.7.3 : The ifInDiscards and ifInErrors counts are zero, as the operation of the Uncontrolled Port provides no error checking or occasion to discard packets, beyond that
    //                                           provided by its users or by the entity supporting the Common Port.
    counters->if_in_discards = 0;
    counters->if_in_errors   = 0;

    // From IEEE 802.1AE-2006 - Section 10.7.3 : The ifOutErrorscount is zero, as no checking is applied to frames transmitted by the Uncontrolled Port.
    counters->if_out_errors  = 0;

    // Uncontrolled out counters are common counter minus the controlled counters.

    // We start be finding controlled counters.
    macsec_port.service_id = 0;
    macsec_port.port_id = 0;
    macsec_port.port_no = port_no;

    if (phy_is_1g(vtss_state, port_no)) {
        max_secy = VTSS_MACSEC_1G_MAX_SECY;
    } else {
        max_secy = VTSS_MACSEC_10G_MAX_SECY;
    }

    for (secy_id = 0; secy_id < max_secy; secy_id++) {
        secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
        if (secy != NULL && secy->in_use) {
            VTSS_RC(vtss_macsec_controlled_counters_get_priv(vtss_state, macsec_port, &controlled_counters, secy_id));

            if (secy->conf.protect_frames == FALSE && vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
                // Add only CRC for untagged packets
                ctrl_if_out_octets += controlled_counters.if_out_octets + (4 * controlled_counters.if_out_pkts);
            } else if (secy->conf.always_include_sci) {
                // Note : Sectag = 16, ICV = 16  ICV, 4 bytes CRC - These are not counter by the controlled counter, but must be subtracted when we later calculates the uncontrolled counters
                ctrl_if_out_octets += controlled_counters.if_out_octets + (16 + 16 + 4) * controlled_counters.if_out_pkts ;
            } else {
                // Note : Sectag = 8, ICV = 16  ICV, 4 bytes CRC - These are not counter by the controlled counter, but must be subtracted when we later calculates the uncontrolled counters
                ctrl_if_out_octets += controlled_counters.if_out_octets + (16 + 8 + 4) * controlled_counters.if_out_pkts ;
            }

#ifdef BYPASS_IEEE_SECTION_10_7_3
            ctrl_if_in_octets += controlled_counters.if_in_octets + 36 * ctrl_if_in_pkts;
#endif
        }
    }

    VTSS_RC(vtss_macsec_common_counters_get_priv(vtss_state, port_no, &common_counters, FALSE));

    // From IEEE 802.1AE-2006 - Section 10.7.3 : The ifInOctets, ifInUcastPkts, ifInMulticastPkts, and ifInBroadcastPkts counts are identical to those of Common Port and are not separately recorded,
    counters->if_in_octets         = common_counters.if_in_octets;
    counters->if_in_ucast_pkts     = common_counters.if_in_ucast_pkts;
    counters->if_in_multicast_pkts = common_counters.if_in_multicast_pkts;
    counters->if_in_broadcast_pkts = common_counters.if_in_broadcast_pkts;

    // From IEEE 802.1AE-2006 - Section 10.7.3 :  The ifOutOctets, ifOutUcastPkts, ifOutMulticastPkts, and ifOutBroadcastPkts counts are the same as those for the user of the Uncontrolled Port.
    // This is common_counters minus controlled_counters. Note : ifOutUcastPkts, ifOutMulticastPkts and ifOutBroadcastPkts are not supported
    if (common_counters.if_out_octets > ctrl_if_out_octets) {
        counters->if_out_octets = common_counters.if_out_octets -= ctrl_if_out_octets;
    } else {
        counters->if_out_octets = common_counters.if_out_octets;
    }

    // The above about uncontrolled rx counters doesn't make sense to us, so if we want use the same calculation as for the out counters, BYPASS_IEEE_SECTION_10_7_3 should be defined
#ifdef BYPASS_IEEE_SECTION_10_7_3
    if (counters->if_in_octets > ctrl_if_in_octets) {
        counters->if_in_octets -= ctrl_if_in_octets;
    } else {
        counters->if_in_octets = counters->if_in_octets;
    }
#endif
    memcpy(&vtss_state->macsec_conf[port_no].glb.uncontrolled_cnt, counters, sizeof(vtss_macsec_secy_port_counters_t));

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_counters_clear_priv(vtss_state_t                  *vtss_state,
                                               const vtss_port_no_t          port_no)
{
    u32 an, sc, secy_id;
    u32 max_sc_rx;
    vtss_macsec_internal_secy_t *secy;
    // Clear global counters
    vtss_macsec_common_counters_t common_counters;
    vtss_macsec_mac_counters_t mac_cntrs;

    VTSS_RC(vtss_macsec_common_counters_get_priv(vtss_state, port_no, &common_counters, TRUE));

    if (phy_is_1g(vtss_state, port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    /* Clear Mac block counters */
    VTSS_RC(vtss_macsec_lmac_counters_get_priv(vtss_state, port_no, &mac_cntrs, TRUE));
    VTSS_RC(vtss_macsec_hmac_counters_get_priv(vtss_state, port_no, &mac_cntrs, TRUE));


    memset(&vtss_state->macsec_conf[port_no].glb.uncontrolled_cnt, 0, sizeof(vtss_macsec_secy_port_counters_t));
    for (secy_id = 0; secy_id < max_sc_rx; secy_id++) {
        secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
        if (secy  == NULL) {
            continue;
        }

        // Clear SecY counters
        memset(&secy->secy_cnt, 0, sizeof(vtss_macsec_secy_counters_t));
        // Clear Egress counters
        memset(&secy->tx_sc.del_tx_sa_cnt, 0, sizeof(vtss_macsec_tx_sa_counters_t));
        memset(&secy->tx_sc.cnt, 0, sizeof(vtss_macsec_tx_sc_counters_t));
        for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
            if (secy->tx_sc.sa[an] != NULL) {
                memset(&secy->tx_sc.sa[an]->cnt, 0, sizeof(vtss_macsec_tx_sa_counters_t));
                // Clearing tx_sa counters
                memset(&vtss_state->macsec_conf[port_no].tx_sa[an].cnt, 0, sizeof(vtss_state->macsec_conf[port_no].tx_sa[an].cnt));
            }
        }
        memset(&vtss_state->macsec_conf[port_no].secy[secy_id].controlled_cnt, 0, sizeof(vtss_macsec_secy_port_counters_t));

        // Clear Ingress counters
        for (sc = 0; sc < max_sc_rx; sc++) {
            if (secy->rx_sc[sc] != NULL) {
                memset(&secy->rx_sc[sc]->del_rx_sa_cnt, 0, sizeof(vtss_macsec_rx_sa_counters_t));
                memset(&secy->rx_sc[sc]->cnt, 0, sizeof(vtss_macsec_rx_sc_counters_t));
                for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                    if (secy->rx_sc[sc]->sa[an] != NULL) {
                        memset(&secy->rx_sc[sc]->sa[an]->cnt, 0, sizeof(vtss_macsec_rx_sa_counters_t));
                    }
                }
            }
        }
    }

    /* Clear all counters in hardware */
    CSR_WRM(port_no, VTSS_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL,
            VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_RESET_ALL,
            VTSS_F_MACSEC_EGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_RESET_ALL);
    CSR_WRM(port_no, VTSS_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL,
            VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_RESET_ALL,
            VTSS_F_MACSEC_INGR_CNTR_CTRL_DEBUG_REGS_COUNT_CONTROL_RESET_ALL);

    return VTSS_RC_OK;
}

// Function for updating all MACSEC counters in vtss_state by calling the counter read functions.
static vtss_rc vtss_macsec_counters_update_priv(vtss_state_t                  *vtss_state,
                                                const vtss_port_no_t          port_no)
{
    macsec_secy_in_use_iter_t in_use_inter;

    // Dummy, because are only reading the counters in order to update software counters (read hw
    // counters in order to make sure they don't wraps around)
    vtss_macsec_secy_counters_t   dummy_counters;
    vtss_macsec_common_counters_t dummy_common_counters;

    macsec_secy_in_use_inter_init(&in_use_inter);

    while (macsec_secy_in_use_inter_getnext(vtss_state, port_no, &in_use_inter)) {
        // Call the read of hardware counters in order to update the software counters
        VTSS_RC(vtss_macsec_secy_counters_get_priv(vtss_state, port_no, &dummy_counters, in_use_inter.secy_id));
    }

    VTSS_RC(vtss_macsec_common_counters_get_priv(vtss_state, port_no, &dummy_common_counters, FALSE));

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_hmac_counters_get_priv(vtss_state_t                      *vtss_state,
                                                  const vtss_port_no_t              port_no,
                                                  vtss_macsec_mac_counters_t        *const counters,
                                                  const BOOL                        clear)

{
    u32 cnt;
    u64 cnt_64;

    VTSS_D("Port:%d, ClearStatus:%d", port_no, clear);

    /* Rx Macsec Block RMON Counters */
    /* Discard counters is not valid for RMON */
    counters->if_rx_discards = 0;

    /* Line  Rx Stats Octects = Bad Bytes Counts + OK Bytes Counts */
    MACSEC_CNT64_RD(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_CNT,
                    VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT, cnt_64);
    counters->if_rx_octets = cnt_64;

    MACSEC_CNT64_RD(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_CNT,
                    VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT, cnt_64);
    counters->if_rx_octets += cnt_64;

    MACSEC_CNT64_RD(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_CNT,
                    VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT, cnt_64);
    counters->if_rx_in_bytes = cnt_64;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_PAUSE_CNT, &cnt);
    counters->if_rx_pause_pkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_UC_CNT, &cnt);
    counters->if_rx_ucast_pkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_MC_CNT, &cnt);
    counters->if_rx_multicast_pkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_BC_CNT, &cnt);
    counters->if_rx_broadcast_pkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_CRC_ERR_CNT, &cnt);
    counters->if_rx_CRCAlignErrors = cnt;
    counters->if_rx_errors = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_UNDERSIZE_CNT, &cnt);
    counters->if_rx_UndersizePkts = cnt;
    counters->if_rx_errors += cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_FRAGMENTS_CNT, &cnt);
    counters->if_rx_Fragments = cnt;
    counters->if_rx_errors += cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_JABBERS_CNT, &cnt);
    counters->if_rx_Jabbers = cnt;
    counters->if_rx_errors += cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_OVERSIZE_CNT, &cnt);
    counters->if_rx_OversizePkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE64_CNT, &cnt);
    counters->if_rx_Pkts64Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE65TO127_CNT, &cnt);
    counters->if_rx_Pkts65to127Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE128TO255_CNT, &cnt);
    counters->if_rx_Pkts128to255Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE256TO511_CNT, &cnt);
    counters->if_rx_Pkts256to511Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE512TO1023_CNT, &cnt);
    counters->if_rx_Pkts512to1023Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT, &cnt);
    counters->if_rx_Pkts1024to1518Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT, &cnt);
    counters->if_rx_Pkts1519toMaxOctets = cnt;

    counters->if_rx_StatsPkts = ((u64)counters->if_rx_UndersizePkts        +
                                 (u64)counters->if_rx_OversizePkts         +
                                 (u64)counters->if_rx_Fragments            +
                                 (u64)counters->if_rx_Jabbers              +
                                 (u64)counters->if_rx_Pkts64Octets         +
                                 (u64)counters->if_rx_Pkts65to127Octets    +
                                 (u64)counters->if_rx_Pkts128to255Octets   +
                                 (u64)counters->if_rx_Pkts256to511Octets   +
                                 (u64)counters->if_rx_Pkts512to1023Octets  +
                                 (u64)counters->if_rx_Pkts1024to1518Octets +
                                 (u64)counters->if_rx_Pkts1519toMaxOctets);
#if 0
    printf("\nPort: %02d : Host Rx RMON Statistics Counters:", (port_no + 1));
    printf("\n\tif_rx_in_bytes             : %lld", counters->if_rx_in_bytes);
    printf("\n\tif_rx_octets               : %lld", counters->if_rx_octets);
    printf("\n\tif_rx_StatsPkts            : %lld", counters->if_rx_StatsPkts);
    printf("\n\tif_rx_ucast_pkts           : %d", counters->if_rx_ucast_pkts);
    printf("\n\tif_rx_multicast_pkts       : %d", counters->if_rx_multicast_pkts);
    printf("\n\tif_rx_broadcast_pkts       : %d", counters->if_rx_broadcast_pkts);
    printf("\n\tif_rx_CRCAlignErrors       : %d", counters->if_rx_CRCAlignErrors);
    printf("\n\tif_rx_UndersizePkts        : %d", counters->if_rx_UndersizePkts);
    printf("\n\tif_rx_Fragments            : %d", counters->if_rx_Fragments);
    printf("\n\tif_rx_Jabbers              : %d", counters->if_rx_Jabbers);
    printf("\n\tif_rx_OversizePkts         : %d", counters->if_rx_OversizePkts);
    printf("\n\tif_rx_Pkts64Octets         : %d", counters->if_rx_Pkts64Octets);
    printf("\n\tif_rx_Pkts65to127Octets    : %d", counters->if_rx_Pkts65to127Octets);
    printf("\n\tif_rx_Pkts128to255Octets   : %d", counters->if_rx_Pkts128to255Octets);
    printf("\n\tif_rx_Pkts256to511Octets   : %d", counters->if_rx_Pkts256to511Octets);
    printf("\n\tif_rx_Pkts512to1023Octets  : %d", counters->if_rx_Pkts512to1023Octets);
    printf("\n\tif_rx_Pkts1024to1518Octets : %d", counters->if_rx_Pkts1024to1518Octets);
    printf("\n\tif_rx_Pkts1519toMaxOctets  : %d", counters->if_rx_Pkts1519toMaxOctets);
    printf("\n");
#endif

    VTSS_D("\nPort: %02d : Host Rx RMON Statistics Counters: \
            \n\tif_rx_in_bytes             : %" PRIu64 " \
            \n\tif_rx_octets               : %" PRIu64 " \
            \n\tif_rx_StatsPkts            : %" PRIu64 " \
            \n\tif_rx_pause_pkts           : %d   \
            \n\tif_rx_ucast_pkts           : %d   \
            \n\tif_rx_multicast_pkts       : %d   \
            \n\tif_rx_broadcast_pkts       : %d   \
            \n\tif_rx_CRCAlignErrors       : %d   \
            \n\tif_rx_UndersizePkts        : %d   \
            \n\tif_rx_Fragments            : %d   \
            \n\tif_rx_Jabbers              : %d   \
            \n\tif_rx_OversizePkts         : %d   \
            \n\tif_rx_Pkts64Octets         : %d   \
            \n\tif_rx_Pkts65to127Octets    : %d   \
            \n\tif_rx_Pkts128to255Octets   : %d   \
            \n\tif_rx_Pkts256to511Octets   : %d   \
            \n\tif_rx_Pkts512to1023Octets  : %d   \
            \n\tif_rx_Pkts1024to1518Octets : %d   \
            \n\tif_rx_Pkts1519toMaxOctets  : %d", \
           (port_no + 1),                          \
           counters->if_rx_in_bytes,             \
           counters->if_rx_octets,               \
           counters->if_rx_StatsPkts,            \
           counters->if_rx_pause_pkts,           \
           counters->if_rx_ucast_pkts,           \
           counters->if_rx_multicast_pkts,       \
           counters->if_rx_broadcast_pkts,       \
           counters->if_rx_CRCAlignErrors,       \
           counters->if_rx_UndersizePkts,        \
           counters->if_rx_Fragments,            \
           counters->if_rx_Jabbers,              \
           counters->if_rx_OversizePkts,         \
           counters->if_rx_Pkts64Octets,         \
           counters->if_rx_Pkts65to127Octets,    \
           counters->if_rx_Pkts128to255Octets,   \
           counters->if_rx_Pkts256to511Octets,   \
           counters->if_rx_Pkts512to1023Octets,  \
           counters->if_rx_Pkts1024to1518Octets, \
           counters->if_rx_Pkts1519toMaxOctets);

    /* Tx Macsec Block RMON Counters */
    counters->if_tx_errors = 0;  /* Reports as 0 */
    counters->if_tx_DropEvents = 0;  /* Reports as 0 */
    counters->if_tx_Collisions = 0;  /* Full duplex MAC reports as 0 */

    /* Line  Tx Stats Octects are OK Bytes Counts only */
    MACSEC_CNT64_RD(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT,
                    VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT, cnt_64);
    counters->if_tx_octets = cnt_64;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_PAUSE_CNT, &cnt);
    counters->if_tx_pause_pkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_UC_CNT, &cnt);
    counters->if_tx_ucast_pkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_MC_CNT, &cnt);
    counters->if_tx_multicast_pkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_BC_CNT, &cnt);
    counters->if_tx_broadcast_pkts = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE64_CNT, &cnt);
    counters->if_tx_Pkts64Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE65TO127_CNT, &cnt);
    counters->if_tx_Pkts65to127Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE128TO255_CNT, &cnt);
    counters->if_tx_Pkts128to255Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE256TO511_CNT, &cnt);
    counters->if_tx_Pkts256to511Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE512TO1023_CNT, &cnt);
    counters->if_tx_Pkts512to1023Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT, &cnt);
    counters->if_tx_Pkts1024to1518Octets = cnt;

    CSR_RD(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT, &cnt);
    counters->if_tx_Pkts1519toMaxOctets = cnt;

    counters->if_tx_StatsPkts = ((u64)counters->if_tx_Pkts64Octets         +
                                 (u64)counters->if_tx_Pkts65to127Octets    +
                                 (u64)counters->if_tx_Pkts128to255Octets   +
                                 (u64)counters->if_tx_Pkts256to511Octets   +
                                 (u64)counters->if_tx_Pkts512to1023Octets  +
                                 (u64)counters->if_tx_Pkts1024to1518Octets +
                                 (u64)counters->if_tx_Pkts1519toMaxOctets);
#if 0
    printf("\nPort: %02d : Host Tx RMON Statistics Counters:", (port_no + 1));
    printf("\n\tif_tx_octets               : %lld", counters->if_tx_octets);
    printf("\n\tif_tx_StatsPkts            : %lld", counters->if_tx_StatsPkts);
    printf("\n\tif_tx_pause_pkts           : %d", counters->if_tx_pause_pkts);
    printf("\n\tif_tx_ucast_pkts           : %d", counters->if_tx_ucast_pkts);
    printf("\n\tif_tx_multicast_pkts       : %d", counters->if_tx_multicast_pkts);
    printf("\n\tif_tx_broadcast_pkts       : %d", counters->if_tx_broadcast_pkts);
    printf("\n\tif_tx_Pkts64Octets         : %d", counters->if_tx_Pkts64Octets);
    printf("\n\tif_tx_Pkts65to127Octets    : %d", counters->if_tx_Pkts65to127Octets);
    printf("\n\tif_tx_Pkts128to255Octets   : %d", counters->if_tx_Pkts128to255Octets);
    printf("\n\tif_tx_Pkts256to511Octets   : %d", counters->if_tx_Pkts256to511Octets);
    printf("\n\tif_tx_Pkts512to1023Octets  : %d", counters->if_tx_Pkts512to1023Octets);
    printf("\n\tif_tx_Pkts1024to1518Octets : %d", counters->if_tx_Pkts1024to1518Octets);
    printf("\n\tif_tx_Pkts1519toMaxOctets  : %d", counters->if_tx_Pkts1519toMaxOctets);
    printf("\n");
#endif

    VTSS_D("\nPort: %02d : Host Tx RMON Statistics Counters: \
            \n\tif_tx_octets               : %" PRIu64 " \
            \n\tif_tx_StatsPkts            : %" PRIu64 " \
            \n\tif_tx_pause_pkts           : %d   \
            \n\tif_tx_ucast_pkts           : %d   \
            \n\tif_tx_multicast_pkts       : %d   \
            \n\tif_tx_broadcast_pkts       : %d   \
            \n\tif_tx_Pkts64Octets         : %d   \
            \n\tif_tx_Pkts65to127Octets    : %d   \
            \n\tif_tx_Pkts128to255Octets   : %d   \
            \n\tif_tx_Pkts256to511Octets   : %d   \
            \n\tif_tx_Pkts512to1023Octets  : %d   \
            \n\tif_tx_Pkts1024to1518Octets : %d   \
            \n\tif_tx_Pkts1519toMaxOctets  : %d", \
           (port_no + 1),                          \
           counters->if_tx_octets,               \
           counters->if_tx_StatsPkts,            \
           counters->if_tx_pause_pkts,           \
           counters->if_tx_ucast_pkts,           \
           counters->if_tx_multicast_pkts,       \
           counters->if_tx_broadcast_pkts,       \
           counters->if_tx_Pkts64Octets,         \
           counters->if_tx_Pkts65to127Octets,    \
           counters->if_tx_Pkts128to255Octets,   \
           counters->if_tx_Pkts256to511Octets,   \
           counters->if_tx_Pkts512to1023Octets,  \
           counters->if_tx_Pkts1024to1518Octets, \
           counters->if_tx_Pkts1519toMaxOctets);

    if (clear) {
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_PAUSE_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_UC_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_MC_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_BC_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_CRC_ERR_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_UNDERSIZE_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_FRAGMENTS_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_JABBERS_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_OVERSIZE_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE64_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE65TO127_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE128TO255_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE256TO511_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE512TO1023_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT, 0);

        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_PAUSE_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_UC_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_MC_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_BC_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE64_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE65TO127_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE128TO255_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE256TO511_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE512TO1023_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT, 0);
        CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT, 0);
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_lmac_counters_get_priv(vtss_state_t                      *vtss_state,
                                                  const vtss_port_no_t              port_no,
                                                  vtss_macsec_mac_counters_t        *const counters,
                                                  const BOOL                        clear)

{
    u32 cnt;
    u64 cnt_64;

    VTSS_D("Port:%d, ClearStatus:%d", port_no, clear);

    /* Rx Macsec Block RMON Counters */

    /* Discard counters is not valid for RMON */
    counters->if_rx_discards = 0;

    /* Line  Rx Stats Octects = Bad Bytes Counts + OK Bytes Counts */
    MACSEC_CNT64_RD(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_OK_BYTES_CNT,
                    VTSS_LINE_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT, cnt_64);
    counters->if_rx_octets = cnt_64;

    MACSEC_CNT64_RD(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_BAD_BYTES_CNT,
                    VTSS_LINE_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT, cnt_64);
    counters->if_rx_octets += cnt_64;

    MACSEC_CNT64_RD(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_IN_BYTES_CNT,
                    VTSS_LINE_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT, cnt_64);
    counters->if_rx_in_bytes = cnt_64;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_PAUSE_CNT, &cnt);
    counters->if_rx_pause_pkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_UC_CNT, &cnt);
    counters->if_rx_ucast_pkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_MC_CNT, &cnt);
    counters->if_rx_multicast_pkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_BC_CNT, &cnt);
    counters->if_rx_broadcast_pkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_CRC_ERR_CNT, &cnt);
    counters->if_rx_CRCAlignErrors = cnt;
    counters->if_rx_errors = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_UNDERSIZE_CNT, &cnt);
    counters->if_rx_UndersizePkts = cnt;
    counters->if_rx_errors += cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_FRAGMENTS_CNT, &cnt);
    counters->if_rx_Fragments = cnt;
    counters->if_rx_errors += cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_JABBERS_CNT, &cnt);
    counters->if_rx_Jabbers = cnt;
    counters->if_rx_errors += cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_OVERSIZE_CNT, &cnt);
    counters->if_rx_OversizePkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE64_CNT, &cnt);
    counters->if_rx_Pkts64Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE65TO127_CNT, &cnt);
    counters->if_rx_Pkts65to127Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE128TO255_CNT, &cnt);
    counters->if_rx_Pkts128to255Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE256TO511_CNT, &cnt);
    counters->if_rx_Pkts256to511Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE512TO1023_CNT, &cnt);
    counters->if_rx_Pkts512to1023Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT, &cnt);
    counters->if_rx_Pkts1024to1518Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT, &cnt);
    counters->if_rx_Pkts1519toMaxOctets = cnt;

    counters->if_rx_StatsPkts = ((u64)counters->if_rx_UndersizePkts        +
                                 (u64)counters->if_rx_OversizePkts         +
                                 (u64)counters->if_rx_Fragments            +
                                 (u64)counters->if_rx_Jabbers              +
                                 (u64)counters->if_rx_Pkts64Octets         +
                                 (u64)counters->if_rx_Pkts65to127Octets    +
                                 (u64)counters->if_rx_Pkts128to255Octets   +
                                 (u64)counters->if_rx_Pkts256to511Octets   +
                                 (u64)counters->if_rx_Pkts512to1023Octets  +
                                 (u64)counters->if_rx_Pkts1024to1518Octets +
                                 (u64)counters->if_rx_Pkts1519toMaxOctets);

#if 0
    printf("\nPort: %02d : Line Rx RMON Statistics Counters:", (port_no + 1));
    printf("\n\tif_rx_in_bytes             : %lld", counters->if_rx_in_bytes);
    printf("\n\tif_rx_octets               : %lld", counters->if_rx_octets);
    printf("\n\tif_rx_StatsPkts            : %lld", counters->if_rx_StatsPkts);
    printf("\n\tif_rx_pause_pkts           : %d", counters->if_rx_pause_pkts);
    printf("\n\tif_rx_ucast_pkts           : %d", counters->if_rx_ucast_pkts);
    printf("\n\tif_rx_multicast_pkts       : %d", counters->if_rx_multicast_pkts);
    printf("\n\tif_rx_broadcast_pkts       : %d", counters->if_rx_broadcast_pkts);
    printf("\n\tif_rx_CRCAlignErrors       : %d", counters->if_rx_CRCAlignErrors);
    printf("\n\tif_rx_UndersizePkts        : %d", counters->if_rx_UndersizePkts);
    printf("\n\tif_rx_Fragments            : %d", counters->if_rx_Fragments);
    printf("\n\tif_rx_Jabbers              : %d", counters->if_rx_Jabbers);
    printf("\n\tif_rx_OversizePkts         : %d", counters->if_rx_OversizePkts);
    printf("\n\tif_rx_Pkts64Octets         : %d", counters->if_rx_Pkts64Octets);
    printf("\n\tif_rx_Pkts65to127Octets    : %d", counters->if_rx_Pkts65to127Octets);
    printf("\n\tif_rx_Pkts128to255Octets   : %d", counters->if_rx_Pkts128to255Octets);
    printf("\n\tif_rx_Pkts256to511Octets   : %d", counters->if_rx_Pkts256to511Octets);
    printf("\n\tif_rx_Pkts512to1023Octets  : %d", counters->if_rx_Pkts512to1023Octets);
    printf("\n\tif_rx_Pkts1024to1518Octets : %d", counters->if_rx_Pkts1024to1518Octets);
    printf("\n\tif_rx_Pkts1519toMaxOctets  : %d", counters->if_rx_Pkts1519toMaxOctets);
    printf("\n");
#endif

    VTSS_D("\nPort: %02d : Line Rx RMON Statistics Counters: \
            \n\tif_rx_in_bytes             : %" PRIu64 " \
            \n\tif_rx_octets               : %" PRIu64 " \
            \n\tif_rx_StatsPkts            : %" PRIu64 " \
            \n\tif_rx_pause_pkts           : %d   \
            \n\tif_rx_ucast_pkts           : %d   \
            \n\tif_rx_multicast_pkts       : %d   \
            \n\tif_rx_broadcast_pkts       : %d   \
            \n\tif_rx_CRCAlignErrors       : %d   \
            \n\tif_rx_UndersizePkts        : %d   \
            \n\tif_rx_Fragments            : %d   \
            \n\tif_rx_Jabbers              : %d   \
            \n\tif_rx_OversizePkts         : %d   \
            \n\tif_rx_Pkts64Octets         : %d   \
            \n\tif_rx_Pkts65to127Octets    : %d   \
            \n\tif_rx_Pkts128to255Octets   : %d   \
            \n\tif_rx_Pkts256to511Octets   : %d   \
            \n\tif_rx_Pkts512to1023Octets  : %d   \
            \n\tif_rx_Pkts1024to1518Octets : %d   \
            \n\tif_rx_Pkts1519toMaxOctets  : %d", \
           (port_no + 1),                          \
           counters->if_rx_in_bytes,             \
           counters->if_rx_octets,               \
           counters->if_rx_StatsPkts,            \
           counters->if_rx_pause_pkts,           \
           counters->if_rx_ucast_pkts,           \
           counters->if_rx_multicast_pkts,       \
           counters->if_rx_broadcast_pkts,       \
           counters->if_rx_CRCAlignErrors,       \
           counters->if_rx_UndersizePkts,        \
           counters->if_rx_Fragments,            \
           counters->if_rx_Jabbers,              \
           counters->if_rx_OversizePkts,         \
           counters->if_rx_Pkts64Octets,         \
           counters->if_rx_Pkts65to127Octets,    \
           counters->if_rx_Pkts128to255Octets,   \
           counters->if_rx_Pkts256to511Octets,   \
           counters->if_rx_Pkts512to1023Octets,  \
           counters->if_rx_Pkts1024to1518Octets, \
           counters->if_rx_Pkts1519toMaxOctets);

    /* Tx Macsec Block RMON Counters */
    counters->if_tx_errors = 0;  /* Reports as 0 */
    counters->if_tx_DropEvents = 0;  /* Reports as 0 */
    counters->if_tx_Collisions = 0;  /* Full duplex MAC reports as 0 */

    /* Line  Tx Stats Octects are OK Bytes Counts only */
    MACSEC_CNT64_RD(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT,
                    VTSS_LINE_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT, cnt_64);
    counters->if_tx_octets = cnt_64;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_PAUSE_CNT, &cnt);
    counters->if_tx_pause_pkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_UC_CNT, &cnt);
    counters->if_tx_ucast_pkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_MC_CNT, &cnt);
    counters->if_tx_multicast_pkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_BC_CNT, &cnt);
    counters->if_tx_broadcast_pkts = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE64_CNT, &cnt);
    counters->if_tx_Pkts64Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE65TO127_CNT, &cnt);
    counters->if_tx_Pkts65to127Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE128TO255_CNT, &cnt);
    counters->if_tx_Pkts128to255Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE256TO511_CNT, &cnt);
    counters->if_tx_Pkts256to511Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE512TO1023_CNT, &cnt);
    counters->if_tx_Pkts512to1023Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT, &cnt);
    counters->if_tx_Pkts1024to1518Octets = cnt;

    CSR_RD(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT, &cnt);
    counters->if_tx_Pkts1519toMaxOctets = cnt;

    counters->if_tx_StatsPkts = ((u64)counters->if_tx_Pkts64Octets         +
                                 (u64)counters->if_tx_Pkts65to127Octets    +
                                 (u64)counters->if_tx_Pkts128to255Octets   +
                                 (u64)counters->if_tx_Pkts256to511Octets   +
                                 (u64)counters->if_tx_Pkts512to1023Octets  +
                                 (u64)counters->if_tx_Pkts1024to1518Octets +
                                 (u64)counters->if_tx_Pkts1519toMaxOctets);

#if 0
    printf("\nPort: %02d : Line Tx RMON Statistics Counters:", (port_no + 1));
    printf("\n\tif_tx_octets               : %lld", counters->if_tx_octets);
    printf("\n\tif_tx_StatsPkts            : %lld", counters->if_tx_StatsPkts);
    printf("\n\tif_tx_pause_pkts           : %d", counters->if_tx_pause_pkts);
    printf("\n\tif_tx_ucast_pkts           : %d", counters->if_tx_ucast_pkts);
    printf("\n\tif_tx_multicast_pkts       : %d", counters->if_tx_multicast_pkts);
    printf("\n\tif_tx_broadcast_pkts       : %d", counters->if_tx_broadcast_pkts);
    printf("\n\tif_tx_Pkts64Octets         : %d", counters->if_tx_Pkts64Octets);
    printf("\n\tif_tx_Pkts65to127Octets    : %d", counters->if_tx_Pkts65to127Octets);
    printf("\n\tif_tx_Pkts128to255Octets   : %d", counters->if_tx_Pkts128to255Octets);
    printf("\n\tif_tx_Pkts256to511Octets   : %d", counters->if_tx_Pkts256to511Octets);
    printf("\n\tif_tx_Pkts512to1023Octets  : %d", counters->if_tx_Pkts512to1023Octets);
    printf("\n\tif_tx_Pkts1024to1518Octets : %d", counters->if_tx_Pkts1024to1518Octets);
    printf("\n\tif_tx_Pkts1519toMaxOctets  : %d", counters->if_tx_Pkts1519toMaxOctets);
    printf("\n");
#endif

    VTSS_D("\nPort: %02d : Line Tx RMON Statistics Counters: \
            \n\tif_tx_octets               : %" PRIu64 " \
            \n\tif_tx_StatsPkts            : %" PRIu64 " \
            \n\tif_tx_pause_pkts           : %d   \
            \n\tif_tx_ucast_pkts           : %d   \
            \n\tif_tx_multicast_pkts       : %d   \
            \n\tif_tx_broadcast_pkts       : %d   \
            \n\tif_tx_Pkts64Octets         : %d   \
            \n\tif_tx_Pkts65to127Octets    : %d   \
            \n\tif_tx_Pkts128to255Octets   : %d   \
            \n\tif_tx_Pkts256to511Octets   : %d   \
            \n\tif_tx_Pkts512to1023Octets  : %d   \
            \n\tif_tx_Pkts1024to1518Octets : %d   \
            \n\tif_tx_Pkts1519toMaxOctets  : %d", \
           (port_no + 1),                          \
           counters->if_tx_octets,               \
           counters->if_tx_StatsPkts,            \
           counters->if_tx_pause_pkts,           \
           counters->if_tx_ucast_pkts,           \
           counters->if_tx_multicast_pkts,       \
           counters->if_tx_broadcast_pkts,       \
           counters->if_tx_Pkts64Octets,         \
           counters->if_tx_Pkts65to127Octets,    \
           counters->if_tx_Pkts128to255Octets,   \
           counters->if_tx_Pkts256to511Octets,   \
           counters->if_tx_Pkts512to1023Octets,  \
           counters->if_tx_Pkts1024to1518Octets, \
           counters->if_tx_Pkts1519toMaxOctets);

    if (clear) {
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_IN_BYTES_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_OK_BYTES_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_BAD_BYTES_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_PAUSE_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_UC_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_MC_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_BC_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_CRC_ERR_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_UNDERSIZE_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_FRAGMENTS_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_JABBERS_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_OVERSIZE_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE64_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE65TO127_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE128TO255_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE256TO511_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE512TO1023_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT, 0);

        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_PAUSE_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_UC_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_MC_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_BC_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE64_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE65TO127_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE128TO255_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE256TO511_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE512TO1023_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT, 0);
        CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT, 0);

        vtss_state->macsec_conf[port_no].glb.rmon_counters_clr = TRUE;
    }

    return VTSS_RC_OK;
}

static vtss_rc macsec_rxsa_inst_count_get_priv(vtss_state_t             *vtss_state,
                                               const vtss_port_no_t     port_no,
                                               const u8                 secy_id,
                                               const u8                 sc_id,
                                               vtss_sc_inst_count_t     *sc_count)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    u8 rxsa_idx;

    VTSS_D("RxSA - Port:%d, SecY:%d, SC:%d", port_no, secy_id, sc_id);

    /* Rx SA Count */
    for (rxsa_idx = 0; rxsa_idx < VTSS_MACSEC_SA_PER_SC_MAX; rxsa_idx++) {
        if ((secy->rx_sc[sc_id]->sa[rxsa_idx] != NULL) && (secy->rx_sc[sc_id]->sa[rxsa_idx]->in_use == TRUE)) {
            VTSS_D("RxSA id:%d", rxsa_idx);
            sc_count->sa_id[sc_count->no_sa] = rxsa_idx;
            sc_count->no_sa++;
        }
    }
    VTSS_D("RxSA count:%d", sc_count->no_sa);

    return VTSS_RC_OK;
}

static vtss_rc macsec_txsa_inst_count_get_priv(vtss_state_t             *vtss_state,
                                               const vtss_port_no_t     port_no,
                                               const u8                 secy_id,
                                               const u8                 sc_id,
                                               vtss_sc_inst_count_t     *sc_count)
{
    vtss_macsec_internal_secy_t *secy;
    u8 txsa_idx;
    vtss_sc_inst_count_t *sc_inst_count = sc_count;

    VTSS_D("TxSA - Port:%d, SecY:%d, SC:%d", port_no, secy_id, sc_id);
    secy = &vtss_state->macsec_conf[port_no].secy[secy_id];

    /* Tx SA Count */
    for (txsa_idx = 0; txsa_idx < VTSS_MACSEC_SA_PER_SC_MAX; txsa_idx++) {
        if ((secy->tx_sc.sa[txsa_idx] != NULL) && (secy->tx_sc.sa[txsa_idx]->in_use == TRUE)) {
            VTSS_D("TxSA id:%d", txsa_idx);
            sc_inst_count->sa_id[sc_inst_count->no_sa] = txsa_idx;
            sc_inst_count->no_sa++;
        }
    }
    VTSS_D("TxSA count:%d", sc_inst_count->no_sa);

    return VTSS_RC_OK;
}

static vtss_rc macsec_rxsc_inst_count_get_priv(vtss_state_t             *vtss_state,
                                               const vtss_port_no_t     port_no,
                                               const u8                 secy_id,
                                               vtss_secy_inst_count_t   *secy_count)
{
    vtss_macsec_internal_secy_t *secy;
    u8 rxsc_idx;
    vtss_rc rc = VTSS_RC_OK;
    vtss_sc_inst_count_t *sc_inst_count;
    vtss_secy_inst_count_t *secy_inst_count = secy_count;

    VTSS_D("RxSC - Port:%d, SecY:%d", port_no, secy_id);
    secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    secy_inst_count->no_rxsc = 0;

    /* Rx SC Count */
    for (rxsc_idx = 0; rxsc_idx < VTSS_MACSEC_MAX_SC_RX; rxsc_idx++) {
        if ((secy->rx_sc[rxsc_idx] != NULL) && (secy->rx_sc[rxsc_idx]->in_use == TRUE)) {
            VTSS_D("RxSC id:%d", rxsc_idx);
            memcpy(&secy_inst_count->rx_sci[secy_inst_count->no_rxsc],
                   &secy->rx_sc[rxsc_idx]->sci, sizeof(vtss_macsec_sci_t));
            secy_inst_count->rxsc_id[secy_inst_count->no_rxsc] = rxsc_idx;
            secy_inst_count->no_rxsc++;
            sc_inst_count = &secy_inst_count->rxsc_inst_count[rxsc_idx];
            rc = macsec_rxsa_inst_count_get_priv(vtss_state, port_no, secy_id, rxsc_idx, sc_inst_count);
            if (rc != VTSS_RC_OK) {
                VTSS_E("RxSA Instance count access Error");
            }
        }
    }
    VTSS_D("RxSC count:%d", secy_inst_count->no_rxsc);

    return rc;
}

static vtss_rc macsec_inst_count_get_priv(vtss_state_t              *vtss_state,
                                          const vtss_port_no_t      port_no,
                                          vtss_macsec_inst_count_t *count)
{
    vtss_rc rc = VTSS_RC_OK;
    u8 secy_idx;
    u8 max_secy;
    vtss_macsec_internal_secy_t *secy;
    vtss_macsec_inst_count_t inst_counts;
    vtss_secy_inst_count_t *secy_inst_counts;

    VTSS_D("Macsec Instance - Port:%d", port_no);
    memset(&inst_counts, 0, sizeof(vtss_macsec_inst_count_t));

    if (phy_is_1g(vtss_state, port_no)) {
        max_secy = VTSS_MACSEC_1G_MAX_SECY;
    } else {
        max_secy = VTSS_MACSEC_10G_MAX_SECY;
    }

    for (secy_idx = 0; secy_idx < max_secy; secy_idx++) {
        secy = &vtss_state->macsec_conf[port_no].secy[secy_idx];
        if ((secy != NULL) && (secy->in_use)) {
            VTSS_D("SecY idx:%d, SecY VPort:%d", secy_idx, secy->sci.port_id);
            inst_counts.secy_vport[inst_counts.no_secy] = secy->sci.port_id;

            /* Tx SC Count */
            if (secy->tx_sc.in_use == TRUE) {
                VTSS_D("TxSC id:0");
                secy_inst_counts = &inst_counts.secy_inst_count[inst_counts.no_secy];
                memcpy(&secy_inst_counts->tx_sci,
                       (const void *)&secy->sci, sizeof(vtss_macsec_sci_t));
                secy_inst_counts->no_txsc += 1;
                secy_inst_counts->txsc_id = 0;
                rc = macsec_txsa_inst_count_get_priv(vtss_state, port_no, secy_idx, 0, &secy_inst_counts->txsc_inst_count);
                if (rc != VTSS_RC_OK) {
                    VTSS_E("TxSA Instance count access Error");
                }
            }
            VTSS_D("TxSC count:%d", inst_counts.secy_inst_count[inst_counts.no_secy].no_txsc);

            /* Rx SC Count */
            secy_inst_counts = &inst_counts.secy_inst_count[inst_counts.no_secy];
            rc = macsec_rxsc_inst_count_get_priv(vtss_state, port_no, secy_idx, secy_inst_counts);
            if (rc != VTSS_RC_OK) {
                VTSS_E("RxSC Instance count access Error");
            }
            VTSS_D("RxSC count:%d", inst_counts.secy_inst_count[inst_counts.no_secy].no_rxsc);
            inst_counts.no_secy++;
        }
    }
    VTSS_D("SecY count:%d", inst_counts.no_secy);

    memcpy(count, &inst_counts, sizeof(vtss_macsec_inst_count_t));
    if (inst_counts.no_secy == 0) {
        VTSS_D("SecYs not created");
        rc = VTSS_RC_OK;
    }
    return rc;
}

static vtss_rc vtss_macsec_egr_intr_sa_get_priv(vtss_state_t         *vtss_state,
                                                const vtss_port_no_t port_no,
                                                vtss_macsec_port_t   *const port,
                                                u16                  *const an)
{
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    vtss_macsec_port_t mport;
    u32 squence_threshold = 0;
    u32 next_pn = 0;
    u16 tx_an;
    u8 max_secy;
    u8 secy_idx;

    /* Initialize to unknow value */
    *an = 0xFF;
    port->port_id = 0xFF;
    port->port_no = port_no;

    /* Get the Configured Sequence number threshold */
    if ((rc = vtss_macsec_event_seq_threshold_get_priv(vtss_state, port_no, &squence_threshold)) != VTSS_RC_OK) {
        VTSS_E("Macsec Event sequence threshold get Error");
        return rc;
    }

    if (phy_is_1g(vtss_state, port_no)) {
        max_secy = VTSS_MACSEC_1G_MAX_SECY;
    } else {
        max_secy = VTSS_MACSEC_10G_MAX_SECY;
    }

    mport.port_no = port_no;
    for (secy_idx = 0; secy_idx < max_secy; secy_idx++) {
         secy = &vtss_state->macsec_conf[port_no].secy[secy_idx];
         if ((secy != NULL) && (secy->in_use) && (secy->tx_sc.in_use == TRUE)) {
              mport.port_id = secy->sci.port_id;
              for (tx_an = 0; tx_an < VTSS_MACSEC_SA_PER_SC_MAX; tx_an++) {
                   if ((secy->tx_sc.sa[tx_an] != NULL) && (secy->tx_sc.sa[tx_an]->enabled == TRUE)) {
                        rc = vtss_macsec_tx_sa_status_get_priv(vtss_state, secy_idx, mport, tx_an);
                        if (rc != VTSS_RC_OK) {
                            VTSS_E("Macsec tx sa status get");
                            return rc;
                        }
                        next_pn = secy->tx_sc.sa[tx_an]->status.pn_status.next_pn.pn;
                        /* Due to Workaround for Packet Number Transmit (i.e. NextPN - 1)
                           next_pn compare with "0". Otherwise next_pn compare with 0xFFFFFFFF */
                        if (((squence_threshold != 0) && (next_pn >= squence_threshold)) ||
                              ((squence_threshold == 0) && (next_pn == 0x0))) {
                                *an = tx_an;
                                port->port_id = mport.port_id;
                                port->service_id = 0;
                                return VTSS_RC_OK;
                        }
                   }
              }
         }
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_lmac_counters_clear_priv(vtss_state_t        *vtss_state,
                                                    const vtss_port_no_t  port_no)

{
    VTSS_D("%s: Port:%d", __FUNCTION__, port_no);

    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_IN_BYTES_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_OK_BYTES_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_BAD_BYTES_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_UC_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_MC_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_BC_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_CRC_ERR_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_UNDERSIZE_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_FRAGMENTS_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_JABBERS_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_OVERSIZE_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE64_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE65TO127_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE128TO255_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE256TO511_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE512TO1023_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT, 0);

    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_UC_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_MC_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_BC_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE64_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE65TO127_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE128TO255_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE256TO511_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE512TO1023_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT, 0);
    CSR_WR(port_no, VTSS_LINE_MAC_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT, 0);

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_hmac_counters_clear_priv(vtss_state_t        *vtss_state,
                                                    const vtss_port_no_t  port_no)
{
    VTSS_D("%s: Port:%d", __FUNCTION__, port_no);

    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_PAUSE_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_UC_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_MC_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_BC_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_CRC_ERR_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_UNDERSIZE_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_FRAGMENTS_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_JABBERS_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_OVERSIZE_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE64_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE65TO127_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE128TO255_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE256TO511_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE512TO1023_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT, 0);

    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_UC_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_MC_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_BC_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE64_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE65TO127_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE128TO255_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE256TO511_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE512TO1023_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT, 0);
    CSR_WR(port_no, VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT, 0);

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_uncontrolled_counters_clear_priv(vtss_state_t  *vtss_state,
                                                            const vtss_port_no_t  port_no)
{

    /* Clear SecY counters */
    memset(&vtss_state->macsec_conf[port_no].glb.uncontrolled_cnt, 0, sizeof(vtss_macsec_secy_port_counters_t));
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_controlled_counters_clear_priv(vtss_state_t  *vtss_state,
                                                          const vtss_port_no_t  port_no,
                                                          u32  secy_id)
{
    /* Clear SecY counters */
    memset(&vtss_state->macsec_conf[port_no].secy[secy_id].controlled_cnt, 0, sizeof(vtss_macsec_secy_port_counters_t));
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_rxsa_counters_clear_priv(vtss_state_t *vtss_state,
                                                    const vtss_port_no_t port_no,
                                                    const vtss_macsec_sci_t *const sci_id,
                                                    const u16 an,
                                                    u32 secy_id)
{
    vtss_macsec_internal_secy_t *secy;
    u32 rxsc_idx;

    secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    VTSS_RC(sc_from_sci_get(vtss_state, port_no, secy, sci_id, &rxsc_idx));

    if ((secy->rx_sc[rxsc_idx] == NULL) ||
        (secy->rx_sc[rxsc_idx]->in_use != TRUE)) {
        VTSS_D("Rx SC does not exist");
    }
    if ((secy->rx_sc[rxsc_idx]->sa[an] == NULL) ||
        (!secy->rx_sc[rxsc_idx]->sa[an]->in_use)) {
        VTSS_D("Rx SA does not exist");
    }

    /* Clear Rx SA counters */
    if ((secy->rx_sc[rxsc_idx] != NULL) &&
        (secy->rx_sc[rxsc_idx]->in_use == TRUE) &&
        (secy->rx_sc[rxsc_idx]->sa[an] != NULL) &&
        (secy->rx_sc[rxsc_idx]->sa[an]->in_use == TRUE) ) {
        memset(&secy->rx_sc[rxsc_idx]->sa[an]->cnt, 0, sizeof(vtss_macsec_rx_sa_counters_t));
        return VTSS_RC_OK;
    }
    return VTSS_RC_ERROR;
}

static vtss_rc vtss_macsec_rxsc_counters_clear_priv(vtss_state_t *vtss_state,
                                                    const vtss_port_no_t port_no,
                                                    const vtss_macsec_sci_t *const sci_id,
                                                    u32 secy_id)
{
    vtss_macsec_internal_secy_t *secy;
    u8 max_rxsc;
    u8 rxsc_idx;

    secy = &vtss_state->macsec_conf[port_no].secy[secy_id];

    if (phy_is_1g(vtss_state, port_no)) {
        max_rxsc = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_rxsc = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    /* Clear Rx SC counters */
    for (rxsc_idx = 0; rxsc_idx < max_rxsc; rxsc_idx++) {
        if ((secy->rx_sc[rxsc_idx] != NULL) &&
            (secy->rx_sc[rxsc_idx]->in_use)) {
            if (sci_cmp(sci_id, &secy->rx_sc[rxsc_idx]->sci)) {
                memset(&secy->rx_sc[rxsc_idx]->cnt, 0, sizeof(vtss_macsec_rx_sc_counters_t));
                memset(&secy->rx_sc[rxsc_idx]->del_rx_sa_cnt, 0, sizeof(vtss_macsec_rx_sa_counters_t));
                return VTSS_RC_OK;
            }
        }
    }
    return VTSS_RC_ERROR;
}

static vtss_rc vtss_macsec_txsa_counters_clear_priv(vtss_state_t  *vtss_state,
                                                    const vtss_port_no_t  port_no,
                                                    const u16  an,
                                                    u32  secy_id)
{
    vtss_macsec_internal_secy_t *secy;

    secy = &vtss_state->macsec_conf[port_no].secy[secy_id];

    if (secy->tx_sc.in_use != TRUE) {
        VTSS_D("Tx SC does not exist");
    }
    if ((secy->tx_sc.sa[an] == NULL) ||
        (!secy->tx_sc.sa[an]->in_use)) {
        VTSS_D("Tx SA does not exist");
    }

    /* Clear Tx SA counters */
    if ((secy->tx_sc.in_use == TRUE) &&
        (secy->tx_sc.sa[an] != NULL) &&
        (secy->tx_sc.sa[an]->in_use) ) {
        memset(&secy->tx_sc.sa[an]->cnt, 0, sizeof(vtss_macsec_tx_sa_counters_t));
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_txsc_counters_clear_priv(vtss_state_t  *vtss_state,
                                                    const vtss_port_no_t  port_no,
                                                    u32  secy_id)
{
    vtss_macsec_internal_secy_t *secy;

    secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    /* Clear Tx SC counters */
    memset(&secy->tx_sc.cnt, 0, sizeof(vtss_macsec_tx_sc_counters_t));
    memset(&secy->tx_sc.del_tx_sa_cnt, 0, sizeof(vtss_macsec_tx_sa_counters_t));

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_secy_counters_clear_priv(vtss_state_t  *vtss_state,
                                                    const vtss_port_no_t  port_no,
                                                    u32  secy_id)
{
    vtss_macsec_internal_secy_t *secy;

    secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
    /* Clear SecY counters */
    memset(&secy->secy_cnt, 0, sizeof(vtss_macsec_secy_counters_t));
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_rxsa_an_status_get_priv (vtss_state_t              *vtss_state,
                                                    const u32                 secy_id,
                                                    const vtss_macsec_port_t  port,
                                                    const vtss_macsec_sci_t   *const sci,
                                                    const u16                 an,
                                                    BOOL                      *status)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 sc;

    VTSS_RC(sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc));

    if ((secy->rx_sc[sc]->sa[an] == NULL) || (!secy->rx_sc[sc]->sa[an]->in_use)) {
        VTSS_D("AN not created. AN=%u, port_no:%d, port_id:%d, secy_id:%d", an, port.port_no, port.port_id, secy_id);
        *status = FALSE;
    } else {
        *status = TRUE;
    }
    return VTSS_RC_OK;
}


/* ================================================================= *
 *  Private functions - End
 * ================================================================= */

/* ================================================================= *
 *  Public functions for MacSec API
 * ================================================================= */
BOOL is_macsec_capable(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
#ifdef VTSS_CHIP_10G_PHY
    if (vtss_state->phy_10g_state[port_no].type != VTSS_PHY_TYPE_10G_NONE) {
        if (vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8490 ||
            vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8491 ||
            vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8258 ||
            vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8254) {
            return 1;
        }
    }
#endif
#ifdef VTSS_CHIP_CU_PHY
    VTSS_N("port:%d, macsec capable:%d", port_no, vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC));
    if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC)) {
        return 1;
    }
#endif
    return 0;
}

vtss_rc vtss_macsec_init_set(const vtss_inst_t                inst,
                             const vtss_port_no_t             port_no,
                             const vtss_macsec_init_t         *const init)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
#if defined(VTSS_CHIP_10G_PHY)
    vtss_phy_10g_power_t power_mode;
#endif
   u32 reg_val;
#ifdef VTSS_CHIP_CU_PHY
    vtss_phy_conf_t power;
    vtss_phy_type_t phy_1g_id;
    BOOL is_phy_1g  = (vtss_phy_id_get(inst, port_no, &phy_1g_id) == VTSS_RC_OK)  && (phy_1g_id.part_number != VTSS_PHY_TYPE_NONE);

    if (is_phy_1g) {
        VTSS_RC(vtss_phy_conf_get(inst,  port_no, &power));
        if (power.mode == VTSS_PHY_MODE_POWER_DOWN) {
            VTSS_E("Phy %u is powered down, i.e. the MacSec block is not accessible", port_no);
            return VTSS_RC_ERROR;
        }
    }
#endif /* VTSS_CHIP_CU_PHY */

#if defined(VTSS_CHIP_10G_PHY)
    if (vtss_phy_10G_is_valid(inst, port_no)) {
        if (vtss_phy_10g_power_get(inst, port_no, &power_mode) == VTSS_RC_OK) {
            if (power_mode == VTSS_PHY_10G_POWER_DISABLE) {
                VTSS_E("Phy %u is powered down, i.e. the MacSec block is not accessible", port_no);
                return VTSS_RC_ERROR;
            }
        }
    }
#endif /* VTSS_CHIP_10G_PHY */

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();

    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {

#if defined(VTSS_OPT_PHY_TIMESTAMP)
//#if defined(TESLA_ING_TS_ERRFIX) || defined(VIPER_B_FIFO_RESET)
#if defined(VIPER_B_FIFO_RESET)
        if((vtss_phy_ts_algo_execute_check(vtss_state, port_no)) ==  TRUE){
            VTSS_E("1588 is configured, MACsec configuration should be applied before 1588 configuration port_no %u", port_no);
            VTSS_EXIT();
            return VTSS_RC_ERROR;
        }
#endif
#endif
        if (!is_macsec_capable(vtss_state, port_no)) {
            VTSS_E("Port/Phy :%u is not MacSec capable", port_no);
            rc = dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE);
            VTSS_EXIT();
            return VTSS_RC_ERROR;
        } else if (init->bypass == MACSEC_INIT_BYPASS_ENABLE ||
                   init->bypass == MACSEC_INIT_BYPASS_DISABLE) {
            VTSS_D("Port:%u Macsec bypass %s", port_no, (init->bypass == MACSEC_INIT_BYPASS_ENABLE) ? "Enabled" : "Disabled");
            vtss_state->macsec_conf[port_no].glb.init.bypass = init->bypass;
            CSR_RD(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG, &reg_val);
            if (init->bypass == MACSEC_INIT_BYPASS_ENABLE) {
                reg_val &= ~VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA;
                reg_val |= VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA;
                CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG, reg_val);
            } else {
                reg_val |= VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA;
                reg_val &= ~VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA;
                CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG, reg_val);
            }

            /* Egress */
            CSR_RD(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG, &reg_val);
            if (init->bypass == MACSEC_INIT_BYPASS_ENABLE) {
                reg_val &= ~VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA;
                reg_val |= VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA;
                CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG, reg_val);
                vtss_state->macsec_conf[port_no].glb.init.enable = 0;
            } else {
                reg_val |= VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_ENA;
                reg_val &= ~VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA;
                CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG, reg_val);
                vtss_state->macsec_conf[port_no].glb.init.enable = 1;
            }

            VTSS_EXIT();
            return VTSS_RC_OK;
        } else {
#ifdef VTSS_CHIP_10G_PHY
            /* Macsec Rev B */
            if ((vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8258) || (vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8254) ||
                ((vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8490 || vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8491) && (vtss_state->phy_10g_state[port_no].revision > 0))) {
                vtss_state->macsec_conf[port_no].glb.macsec_revb = TRUE;
            }
#endif
#ifdef VTSS_CHIP_CU_PHY
            if ((vtss_state->phy_state[port_no].type.part_number == 8584 || vtss_state->phy_state[port_no].type.part_number == 8582 || vtss_state->phy_state[port_no].type.part_number == 8564
                 || vtss_state->phy_state[port_no].type.part_number == 8562 ) && (vtss_state->phy_state[port_no].type.revision > 0)) {
                vtss_state->macsec_conf[port_no].glb.macsec_revb = TRUE;
            }
#endif
            if ((vtss_state->macsec_conf[port_no].glb.init.enable != init->enable)) {
                vtss_macsec_init_t state_init;
                state_init = vtss_state->macsec_conf[port_no].glb.init;
                vtss_state->macsec_conf[port_no].glb.init = *init;
                if (vtss_state->warm_start_cur) {
                    u8 i;
                    for (i = 0; i < VTSS_MACSEC_CP_RULES; i++) {
                        VTSS_N("Disable i:%d", i);
                        vtss_state->macsec_conf[port_no].glb.control_match[i].match = VTSS_MACSEC_MATCH_DISABLE;
                        vtss_state->macsec_conf[port_no].glb.egr_bypass_record[i] = MACSEC_NOT_IN_USE;
                    }
                    rc = VTSS_RC_OK;
                } else {
                    rc = vtss_macsec_init_set_priv(vtss_state, port_no, init);
                    if (rc != VTSS_RC_OK) {
                        vtss_state->macsec_conf[port_no].glb.init = state_init;
                    }
                    vtss_state->macsec_conf[port_no].glb.mac_block_mtu = 10240; /* Default MAC Block MTU */
                }
            }
        }
    }

    if ((rc = MACSEC_RC_COLD(vtss_macsec_speed_conf_priv(vtss_state, port_no, MACSEC_ENABLE, FALSE))) != VTSS_RC_OK) {
        VTSS_E("Could not set speed on port:%u", port_no);
    }
    if (init->enable) {
        if ((rc = MACSEC_RC_COLD(phy_10g_mac_conf(vtss_state, port_no, 1, 1))) != VTSS_RC_OK) {
            VTSS_E("Could not set mac conf on port:%u", port_no);
        }
    }

    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_init_get(const vtss_inst_t                 inst,
                             const vtss_port_no_t              port_no,
                             vtss_macsec_init_t                *const init)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();

    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (!is_macsec_capable(vtss_state, port_no)) {
            VTSS_E("Port/Phy :%u is not MacSec capable", port_no);
            rc = dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE);
        } else {
            *init = vtss_state->macsec_conf[port_no].glb.init;
        }
    }
    VTSS_EXIT();
    return rc;
}

// See vtss_macsec_api.h
vtss_rc vtss_macsec_is_capable(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               BOOL                 *capable)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *capable = is_macsec_capable(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_secy_conf_add(const vtss_inst_t                 inst,
                                  const vtss_macsec_port_t          port,
                                  const vtss_macsec_secy_conf_t     *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0, i = 0;
    vtss_macsec_internal_secy_t *secy;

    VTSS_I("Port: %u/%u/%u. TxMAC:"MACADDRESS_FMT, MACSEC_PORT_ARG(&port), MACADDRESS_ARG(conf->mac_addr));
    VTSS_I("SecY prm: RP:%d RW:%d Prt frms:%d incl_sci:%d use_es:%d use_scb:%d cipher:%s%s confidentiality offset:%d",
           conf->replay_protect, conf->replay_window, conf->protect_frames, conf->always_include_sci, conf->use_es,
           conf->use_scb, conf->current_cipher_suite > VTSS_MACSEC_CIPHER_SUITE_GCM_AES_256 ? "XPN-" : "",
           (conf->current_cipher_suite % 2) == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128 ? "128" : "256", conf->confidentiality_offset);
    VTSS_MACSEC_ASSERT(conf->confidentiality_offset > 64, "Confidentiality offset value not supported");
    VTSS_ENTER();

    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 1, &secy_id)) == VTSS_RC_OK) {
        if (!check_resources(vtss_state, port.port_no, 0, 0)) {
            VTSS_E("HW resources exhausted");
            rc = dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED);
        } else {
            secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];

            if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb != TRUE) {
                if (conf->current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
                    conf->current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) {
                    VTSS_E("Extended packet numbering not supported on Macsec Rev A");
                    VTSS_EXIT();
                    return VTSS_RC_ERROR;
                }
            }
            if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb == TRUE) {
                if ((conf->current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
                     conf->current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) &&
                    conf->replay_window > MACSEC_REVB_REPLAY_WINDOW_SIZE) {
                    VTSS_E("Replay window size cannot be greater than 2^30 for extended packet numbering");
                    VTSS_EXIT();
                    return VTSS_RC_ERROR;
                }
            }
            secy->conf = *conf;
            secy->sci.port_id = port.port_id;
            secy->service_id = port.service_id;
            for (i = 0; i < 6; ++i) {
                secy->sci.mac_addr.addr[i] = secy->conf.mac_addr.addr[i];
            }

            for (i = 0; i < 3; ++i) {
                secy->pattern_record[i][0] = MACSEC_NOT_IN_USE;
                secy->pattern_record[i][1] = MACSEC_NOT_IN_USE;
                secy->pattern[i][0].match = VTSS_MACSEC_MATCH_DISABLE;
                secy->pattern[i][1].match = VTSS_MACSEC_MATCH_DISABLE;
            }
            secy->pattern[VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT][VTSS_MACSEC_DIRECTION_EGRESS].priority = VTSS_MACSEC_MATCH_PRIORITY_LOWEST;
            secy->pattern[VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT][VTSS_MACSEC_DIRECTION_INGRESS].priority = VTSS_MACSEC_MATCH_PRIORITY_LOWEST;
            if ((rc = is_sci_valid(vtss_state, port.port_no, &secy->sci)) == VTSS_RC_OK) {  // Update rc to return error code if sci is not valid
                secy->in_use = 1;
            } else {
                secy->in_use = 0;
            }
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_macsec_secy_conf_update(const vtss_inst_t                 inst,
                                     const vtss_macsec_port_t          port,
                                     const vtss_macsec_secy_conf_t     *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0, i = 0, sc = 0, sa = 0;
    u32 max_sc_rx;
    vtss_macsec_internal_secy_t *secy;

    VTSS_I("Port: %u/%u/%u. TxMAC:"MACADDRESS_FMT, MACSEC_PORT_ARG(&port), MACADDRESS_ARG(conf->mac_addr));
    VTSS_I("SecY prm: RP:%d RW:%d Prt frms:%d incl_sci:%d use_es:%d use_scb:%d cipher:%s%s confidentiality offset:%d",
           conf->replay_protect, conf->replay_window, conf->protect_frames, conf->always_include_sci, conf->use_es,
           conf->use_scb, conf->current_cipher_suite > VTSS_MACSEC_CIPHER_SUITE_GCM_AES_256 ? "XPN-" : "",
           (conf->current_cipher_suite % 2) == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128 ? "128" : "256", conf->confidentiality_offset);
    VTSS_MACSEC_ASSERT(conf->confidentiality_offset > 64, "Confidentiality offset value not supported");
    VTSS_ENTER();

    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb != TRUE) {
            if (conf->current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
                conf->current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) {
                VTSS_E("Extended packet numbering not supported on Macsec Rev A");
                VTSS_EXIT();
                return VTSS_RC_ERROR;
            }
        }
        if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb == TRUE) {
            if ((conf->current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
                 conf->current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) &&
                conf->replay_window > MACSEC_REVB_REPLAY_WINDOW_SIZE) {
                VTSS_E("Replay window size cannot be greater than 2^30 for extended packet numbering");
                VTSS_EXIT();
                return VTSS_RC_ERROR;
            }
        }
        secy->conf = *conf;
        for (i = 0; i < 6; ++i) {
            secy->sci.mac_addr.addr[i] = secy->conf.mac_addr.addr[i];
        }

        if (phy_is_1g(vtss_state, port.port_no)) {
            max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
        } else {
            max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
        }

        if (vtss_state->warm_start_cur) {
            /* Delete the SA configuration because Secy configuration has changed */
            for (sa = 0; sa < VTSS_MACSEC_SA_PER_SC; sa++) {
                if (secy->tx_sc.sa[sa] != NULL) {
                    if (vtss_macsec_tx_sa_disable_priv(vtss_state, secy_id, port, sa)) {
                        VTSS_E("Could not disable sa:%u", sa);
                        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                    }
                    if (vtss_macsec_tx_sa_del_priv(vtss_state, secy_id, port, sa)) {
                        VTSS_E("Could not delete tx sa:%u, port_no:%d port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                        return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA);
                    }
                }
            }
        }
        for (sc = 0; sc < max_sc_rx; sc++) {
            if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use || (rc = is_sci_valid(vtss_state, port.port_no, &secy->sci)) != VTSS_RC_OK) {
                continue;
            }
            secy->rx_sc[sc]->conf.validate_frames = conf->validate_frames;
            secy->rx_sc[sc]->conf.replay_protect = conf->replay_protect;
            secy->rx_sc[sc]->conf.replay_window = conf->replay_window;
            secy->rx_sc[sc]->conf.confidentiality_offset = conf->confidentiality_offset;

            if (vtss_state->warm_start_cur) {
                for (sa = 0; sa < VTSS_MACSEC_SA_PER_SC; sa++) {
                    if (secy->rx_sc[sc]->sa[sa] != NULL) {

                        if (secy->rx_sc[sc]->sa[sa]->status.in_use) {
                            if (vtss_macsec_rx_sa_disable_priv(vtss_state, secy_id, port, &secy->rx_sc[sc]->sci, sa) != VTSS_RC_OK) {
                                VTSS_E("Could not disable sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                                return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                            }
                        }
                        if (vtss_macsec_rx_sa_del_priv(vtss_state, secy_id, port, &secy->rx_sc[sc]->sci, sa)) {
                            VTSS_E("Could not delete rx sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                            return dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA);
                        }
                    }
                }
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_secy_conf_del(const vtss_inst_t                 inst,
                                  const vtss_macsec_port_t          port)

{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I("port_no: %u/%u/%u", port.port_no, port.port_id, port.service_id);
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_secy_conf_del_priv(vtss_state, port, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_secy_conf_get(const vtss_inst_t         inst,
                                  const vtss_macsec_port_t  port,
                                  vtss_macsec_secy_conf_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        *conf = vtss_state->macsec_conf[port.port_no].secy[secy_id].conf;
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_secy_controlled_set(const vtss_inst_t         inst,
                                        const vtss_macsec_port_t  port,
                                        const BOOL                enable)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;
    VTSS_I("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_secy_controlled_set_priv(vtss_state, port, enable, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_secy_controlled_get(const vtss_inst_t         inst,
                                        const vtss_macsec_port_t  port,
                                        BOOL                      *const enable)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_secy_controlled_get_priv(vtss_state, port, enable, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sc_add(const vtss_inst_t           inst,
                              const vtss_macsec_port_t    port,
                              const vtss_macsec_sci_t     *const sci)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_SCI_FMT, MPORT_SCI_ARG(port, *sci));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sc_add_priv(vtss_state, port, sci, secy_id);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_rx_sc_update(const vtss_inst_t              inst,
                                 const vtss_macsec_port_t       port,
                                 const vtss_macsec_sci_t        *const sci,
                                 const vtss_macsec_rx_sc_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_macsec_internal_secy_t *secy;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0, sc = 0;

    VTSS_I(MPORT_SCI_FMT", conf:"MACSEC_RX_SC_CONF_FMT,
           MPORT_SCI_ARG(port, *sci), MACSEC_RX_SC_CONF_ARG(conf));
    VTSS_MACSEC_ASSERT(conf->confidentiality_offset > 64, "Confidentiality offset value not supported");
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if ((rc = sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc)) != VTSS_RC_OK) {
            VTSS_E("Could not find SC (from sci)");
        } else {
            if (vtss_state->macsec_conf[port.port_no].glb.macsec_revb == TRUE) {
                if ((secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
                     secy->conf.current_cipher_suite == VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) &&
                    conf->replay_window > MACSEC_REVB_REPLAY_WINDOW_SIZE) {
                    VTSS_E("Replay window size cannot be greater than 2^30 while using extended packet numbering");
                    VTSS_EXIT();
                    return VTSS_RC_ERROR;
                }
            }
            secy->rx_sc[sc]->conf = *conf;
        }
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_rx_sc_del(const vtss_inst_t           inst,
                              const vtss_macsec_port_t    port,
                              const vtss_macsec_sci_t     *const sci)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_SCI_FMT, MPORT_SCI_ARG(port, *sci));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sc_del_priv(vtss_state, port, sci, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_secy_port_status_get(const vtss_inst_t                 inst,
                                         const vtss_macsec_port_t          port,
                                         vtss_macsec_secy_port_status_t    *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;
    BOOL fdx = 1;
#ifdef VTSS_CHIP_CU_PHY
    vtss_port_status_t phy_status;
    vtss_phy_type_t phy_1g_id;
    BOOL is_phy_1g  = (vtss_phy_id_get(inst, port.port_no, &phy_1g_id) == VTSS_RC_OK)  && (phy_1g_id.part_number != VTSS_PHY_TYPE_NONE);

    VTSS_D(MACSEC_PORT_FMT, MACSEC_PORT_ARG(&port));
    if (is_phy_1g) {
        VTSS_RC(vtss_phy_status_get(inst, port.port_no, &phy_status));
        fdx = phy_status.fdx;
    }
#endif /* VTSS_CHIP_CU_PHY */
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_secy_port_status_get_priv(vtss_state, port, status, secy_id, fdx);
    }
    VTSS_D("Common: Ena:%d P2P:%u Oper:%u", status->common.mac_enabled,
           status->common.oper_point_to_point_mac, status->common.mac_operational);
    VTSS_D("Contrl: Ena:%d P2P:%u Oper:%u", status->controlled.mac_enabled,
           status->controlled.oper_point_to_point_mac, status->controlled.mac_operational);
    VTSS_D("Uncontrl: Ena:%d P2P:%u Oper:%u", status->uncontrolled.mac_enabled,
           status->uncontrolled.oper_point_to_point_mac, status->uncontrolled.mac_operational);
    VTSS_EXIT();

    if (rc == VTSS_RC_OK) {
        VTSS_D(" -> "MACSEC_SECY_PORT_STATUS_FMT,
               MACSEC_SECY_PORT_STATUS_ARG(*status));
    }

    return rc;
}

static vtss_rc vtss_macsec_port_get_next_priv(vtss_state_t                *vtss_state,
                                              const vtss_port_no_t        port_no,
                                              const vtss_macsec_port_t    *const search_macsec_port,
                                              vtss_macsec_port_t          *const found_macsec_port,
                                              u32                         *const found_secy_id,
                                              vtss_macsec_internal_secy_t **found_secy)

{
    vtss_macsec_internal_secy_t *secy;
    u32 i, max_secy;
    BOOL found_port = 0;

    if (phy_is_1g(vtss_state, port_no)) {
        max_secy = VTSS_MACSEC_1G_MAX_SECY;
    } else {
        max_secy = VTSS_MACSEC_10G_MAX_SECY;
    }

    for (i = 0; i < max_secy; i++) {
        secy = &vtss_state->macsec_conf[port_no].secy[i];
        if (secy != NULL && secy->in_use) {
            if (search_macsec_port == NULL || found_port) {
                found_macsec_port->port_no = port_no;
                found_macsec_port->service_id = secy->service_id;
                found_macsec_port->port_id = secy->sci.port_id;
                break;
            } else {
                if (search_macsec_port->service_id == secy->service_id &&
                    search_macsec_port->port_id == secy->sci.port_id) {
                    found_port = 1; // found the search port, return the next
                }
            }
        }
    }

    if (max_secy == i) {
        return VTSS_RC_ERROR; // No more ports
    }
    if (found_secy_id != NULL) {
        *found_secy_id = i;
    }
    if (found_secy != NULL) {
        *found_secy = secy;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_macsec_port_get_next(const vtss_inst_t              inst,
                                  const vtss_port_no_t           port_no,
                                  const vtss_macsec_port_t       *const search_macsec_port,
                                  vtss_macsec_port_t             *const found_macsec_port)

{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_port_get_next_priv(vtss_state, port_no, search_macsec_port, found_macsec_port, NULL, NULL);
    }
    VTSS_EXIT();
    return rc;
}

static vtss_rc vtss_macsec_rx_sc_get_next_priv(vtss_state_t                *vtss_state,
                                               const vtss_macsec_port_t    port,
                                               const vtss_macsec_sci_t     *const search_sci,
                                               vtss_macsec_sci_t           *const found_sci,
                                               u32 secy_id)
{
    u32 i, max_sc_rx;
    vtss_macsec_internal_secy_t *secy;
    const vtss_macsec_sci_t *sci_p = search_sci;
    BOOL search_cont = 1, search_larger = 1;

    secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];

    if (sci_p != NULL) {
        VTSS_I("Search SCI:"SCI_FMT, SCI_ARG(*search_sci));
    } else {
        VTSS_I("Search SCI == NULL");
    }

    if (phy_is_1g(vtss_state, port.port_no)) {
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
    } else {
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
    }

    while (search_cont) {
        search_cont = 0;
        for (i = 0; i < max_sc_rx; i++) {
            if (secy->rx_sc[i] == NULL) {
                continue;
            }
            if (secy->rx_sc[i]->in_use) {
                if (sci_cmp(&secy->rx_sc[i]->sci, search_sci)) {
                    continue;
                }
                if (search_larger) {
                    if (sci_larger(&secy->rx_sc[i]->sci, sci_p)) {
                        sci_p = &secy->rx_sc[i]->sci;
                        search_cont = 1;
                        search_larger = 0;
                        break;
                    }
                } else {
                    if (sci_cmp(&secy->rx_sc[i]->sci, sci_p)) {
                        continue;
                    }
                    if (!sci_larger(&secy->rx_sc[i]->sci, search_sci)) {
                        continue;
                    }
                    if (!sci_larger(&secy->rx_sc[i]->sci, sci_p))  {
                        sci_p = &secy->rx_sc[i]->sci;
                        search_cont = 1;
                        break;
                    }
                }
            }
        }
    }
    if (sci_p != NULL && (found_sci != sci_p)) {
        *found_sci = *sci_p;
    }

    if (sci_p != NULL) {
        VTSS_I("Found SCI:"SCI_FMT, SCI_ARG(*sci_p));
    } else {
        VTSS_I("Found SCI == NULL");
    }

    return (search_sci == sci_p) ? VTSS_RC_ERROR : VTSS_RC_OK;

}

vtss_rc vtss_macsec_rx_sc_get_next(const vtss_inst_t              inst,
                                   const vtss_macsec_port_t       port,
                                   const vtss_macsec_sci_t        *const search_sci,
                                   vtss_macsec_sci_t              *const found_sci)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));

    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sc_get_next_priv(vtss_state, port, search_sci, found_sci, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sc_status_get(const vtss_inst_t               inst,
                                     const vtss_macsec_port_t        port,
                                     const vtss_macsec_sci_t         *const sci,
                                     vtss_macsec_rx_sc_status_t      *const status)
{
    vtss_macsec_internal_secy_t *secy;
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0, an = 0, sc = 0;

    VTSS_D(MPORT_FMT, MPORT_ARG(port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if ((rc = sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc)) != VTSS_RC_OK) {
            VTSS_E("Could not find SC (from sci)");
        } else {
            secy->rx_sc[sc]->status.receiving = 0;
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                if (secy->rx_sc[sc]->sa[an] == NULL) {
                    continue;
                }
                if (secy->rx_sc[sc]->sa[an]->in_use) {
                    secy->rx_sc[sc]->status.receiving = 1;
                }
            }
            *status = secy->rx_sc[sc]->status;
            VTSS_D("Status.receiving:%d created:%d started:%d stopped:%d",
                   status->receiving, status->created_time, status->started_time, status->stopped_time);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_tx_sc_set(const vtss_inst_t           inst,
                              const vtss_macsec_port_t    port)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_FMT, MPORT_ARG(port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sc_set_priv(vtss_state, port, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_tx_sc_update(const vtss_inst_t              inst,
                                 const vtss_macsec_port_t       port,
                                 const vtss_macsec_tx_sc_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    VTSS_I(MPORT_FMT" conf:"MACSEC_TX_SC_CONF_FMT, MPORT_ARG(port),
           MACSEC_TX_SC_CONF_ARG(*conf));
    VTSS_MACSEC_ASSERT(conf->confidentiality_offset > 64, "Confidentiality offset value not supported");
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (secy->tx_sc.in_use) {
            secy->conf.protect_frames         = conf->protect_frames;
            secy->conf.always_include_sci     = conf->always_include_sci;
            secy->conf.use_es                 = conf->use_es;
            secy->conf.use_scb                = conf->use_scb;
            secy->conf.confidentiality_offset = conf->confidentiality_offset;
        } else {
            VTSS_E("TX_SC does not exist");
            rc = dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_TX_SC_NOT_EXIST);
        }
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_tx_sc_del(const vtss_inst_t           inst,
                              const vtss_macsec_port_t    port)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_FMT, MPORT_ARG(port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sc_del_priv(vtss_state, port, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_tx_sc_status_get(const vtss_inst_t           inst,
                                     const vtss_macsec_port_t    port,
                                     vtss_macsec_tx_sc_status_t  *const status)
{
    vtss_macsec_internal_secy_t *secy;
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0, an = 0;

    VTSS_D(MPORT_FMT, MPORT_ARG(port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (secy->tx_sc.in_use) {
            secy->tx_sc.status.transmitting = 0;
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                if (secy->tx_sc.sa[an] == NULL) {
                    continue;
                }
                if (secy->tx_sc.sa[an]->in_use) {
                    secy->tx_sc.status.transmitting = 1;
                }
            }
            *status = secy->tx_sc.status;
            VTSS_D("Status enciphering:%d encoding:%d transmitting:%d created:%d started:%d stopped:%d", status->enciphering_sa, status->encoding_sa,
                   status->transmitting, status->created_time, status->started_time, status->stopped_time);
        } else {
            VTSS_E("TX_SC does not exist");
            rc = dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_TX_SC_NOT_EXIST);
        }
    }
    VTSS_EXIT();
    if (rc == VTSS_RC_OK) {
        VTSS_D(" -> status:"MACSEC_TX_SC_STATUS_FMT,
               MACSEC_TX_SC_STATUS_ARG(*status));
    }
    return rc;
}

vtss_rc vtss_macsec_tx_sc_get_conf(const vtss_inst_t              inst,
                                   const vtss_macsec_port_t       port,
                                   vtss_macsec_tx_sc_conf_t       *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    VTSS_I("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (secy->tx_sc.in_use) {
            conf->protect_frames         = secy->conf.protect_frames;
            conf->always_include_sci     = secy->conf.always_include_sci;
            conf->use_es                 = secy->conf.use_es;
            conf->use_scb                = secy->conf.use_scb;
            conf->confidentiality_offset = secy->conf.confidentiality_offset;
        } else {
            VTSS_I("TX_SC does not exist");
            rc = dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_TX_SC_NOT_EXIST);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sc_get_conf(const vtss_inst_t              inst,
                                   const vtss_macsec_port_t       port,
                                   const vtss_macsec_sci_t        *const sci,
                                   vtss_macsec_rx_sc_conf_t       *const conf)
{
    vtss_state_t *vtss_state;
    vtss_macsec_internal_secy_t *secy;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0, sc = 0;

    VTSS_I("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if ((rc = sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc)) != VTSS_RC_OK) {
            VTSS_I("Could not find SC (from sci)");
        } else {
            *conf = secy->rx_sc[sc]->conf;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sa_set(const vtss_inst_t             inst,
                              const vtss_macsec_port_t      port,
                              const vtss_macsec_sci_t       *const sci,
                              const u16                     an,
                              const u32                     lowest_pn,
                              const vtss_macsec_sak_t       *const sak)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;
    vtss_macsec_pkt_num_t pkt_num;

    pkt_num.pn = lowest_pn;
    VTSS_I(MPORT_SCI_AN_FMT", pn:%u cipher:%u", MPORT_SCI_AN_ARG(port, *sci, an), lowest_pn, sak->len == 16 ? 128 : 256);
    prnt_sak(sak);
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_set_priv(vtss_state, secy_id, port, sci, an, pkt_num, sak, NULL);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sa_get(const vtss_inst_t             inst,
                              const vtss_macsec_port_t      port,
                              const vtss_macsec_sci_t       *const sci,
                              const u16                     an,
                              u32                           *const lowest_pn,
                              vtss_macsec_sak_t             *const sak,
                              BOOL                          *const active)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;
    vtss_macsec_pkt_num_t pkt_num;
    vtss_macsec_ssci_t temp;

    VTSS_D(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_get_priv(vtss_state, secy_id, port, sci, an, &pkt_num, sak, active, &temp);
    }
    VTSS_EXIT();

    if (rc == VTSS_RC_OK) {
        *lowest_pn = pkt_num.pn;
        VTSS_D("-> pn:%u, active:%s", *lowest_pn, BOOL_ARG(*active));
    } else {
        *lowest_pn = 0;
    }
    return rc;
}

vtss_rc vtss_macsec_rx_sa_activate(const vtss_inst_t             inst,
                                   const vtss_macsec_port_t      port,
                                   const vtss_macsec_sci_t       *const sci,
                                   const u16                     an)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_activate_priv(vtss_state, secy_id, port, sci, an);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sa_disable(const vtss_inst_t         inst,
                                  const vtss_macsec_port_t  port,
                                  const vtss_macsec_sci_t   *const sci,
                                  const u16                 an)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_disable_priv(vtss_state, secy_id, port, sci, an);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sa_del(const vtss_inst_t         inst,
                              const vtss_macsec_port_t  port,
                              const vtss_macsec_sci_t   *const sci,
                              const u16                 an)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_del_priv(vtss_state, secy_id, port, sci, an);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sa_lowest_pn_update(const vtss_inst_t            inst,
                                           const vtss_macsec_port_t     port,
                                           const vtss_macsec_sci_t      *const sci,
                                           const u16                    an,
                                           const u32                    lowest_pn)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;
    vtss_macsec_pkt_num_t pkt_num;

    VTSS_I(MPORT_SCI_AN_FMT", an: %u", MPORT_SCI_AN_ARG(port, *sci, an),
           lowest_pn);
    pkt_num.pn = lowest_pn;
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_lowest_pn_update_priv(vtss_state, secy_id, port, sci, an, pkt_num);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_rx_sa_status_get(const vtss_inst_t           inst,
                                     const vtss_macsec_port_t    port,
                                     const vtss_macsec_sci_t     *const sci,
                                     const u16                   an,
                                     vtss_macsec_rx_sa_status_t  *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_D(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_status_get_priv(vtss_state, secy_id, port, sci, an, status);
    }
    VTSS_EXIT();

    if (rc == VTSS_RC_OK) {
        VTSS_D(" -> status:"MACSEC_RX_SA_STATUS_FMT, MACSEC_RX_SA_STATUS_ARG(*status));
    }
    return rc;
}

vtss_rc vtss_macsec_tx_sa_set(const vtss_inst_t              inst,
                              const vtss_macsec_port_t       port,
                              const u16                      an,
                              const u32                      next_pn,
                              const BOOL                     confidentiality,
                              const vtss_macsec_sak_t        *const sak)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;
    vtss_macsec_pkt_num_t pkt_num;

    VTSS_I(MPORT_AN_FMT" pn:%u, confidentiality:%d cipher:%u", MPORT_AN_ARG(port, an),
           next_pn, confidentiality, sak->len == 16 ? 128 : 256);
    prnt_sak(sak);
    pkt_num.pn = next_pn;
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sa_set_priv(vtss_state, secy_id, port, an, pkt_num, confidentiality, sak, NULL);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_tx_sa_get(const vtss_inst_t              inst,
                              const vtss_macsec_port_t       port,
                              const u16                      an,
                              u32                            *const next_pn,
                              BOOL                           *const confidentiality,
                              vtss_macsec_sak_t              *const sak,
                              BOOL                           *const active)
{
    vtss_macsec_internal_secy_t *secy;
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_D(MPORT_AN_FMT, MPORT_AN_ARG(port, an));
    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (secy->tx_sc.sa[an] == NULL) {
            VTSS_I("AN does not exist, port_no:%d, port_id:%d, an:%d", port.port_no, port.port_id, an);
            rc = dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_AN_NOT_EXIST);
            memset(sak, 0 , sizeof(*sak));
            *active          = FALSE;
            *confidentiality = FALSE;
            *next_pn         = 0;
        } else {
            *sak             = secy->tx_sc.sa[an]->sak;
            *active          = secy->tx_sc.sa[an]->enabled;
            *confidentiality = secy->tx_sc.sa[an]->confidentiality;
            *next_pn         = secy->tx_sc.sa[an]->status.next_pn;
        }
    }
    VTSS_EXIT();

    if (rc == VTSS_RC_OK) {
        VTSS_D(" -> pn:%u, confidentiality:%s, active:%s", *next_pn,
               BOOL_ARG(*confidentiality), BOOL_ARG(*active));
    }

    return rc;
}

vtss_rc vtss_macsec_tx_sa_activate(const vtss_inst_t         inst,
                                   const vtss_macsec_port_t  port,
                                   const u16                 an)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_AN_FMT, MPORT_AN_ARG(port, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sa_activate_priv(vtss_state, secy_id, port, an);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_tx_sa_disable(const vtss_inst_t         inst,
                                  const vtss_macsec_port_t  port,
                                  const u16                 an)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_AN_FMT, MPORT_AN_ARG(port, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sa_disable_priv(vtss_state, secy_id, port, an);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_tx_sa_del(const vtss_inst_t         inst,
                              const vtss_macsec_port_t  port,
                              const u16                 an)
{

    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_AN_FMT, MPORT_AN_ARG(port, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sa_del_priv(vtss_state, secy_id, port, an);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_tx_sa_status_get(const vtss_inst_t           inst,
                                     const vtss_macsec_port_t    port,
                                     const u16                   an,
                                     vtss_macsec_tx_sa_status_t  *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    VTSS_D(MPORT_AN_FMT, MPORT_AN_ARG(port, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        if ((rc = vtss_macsec_tx_sa_status_get_priv(vtss_state, secy_id, port, an)) == VTSS_RC_OK) {
            secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
            *status = secy->tx_sc.sa[an]->status;
        }
    }
    VTSS_EXIT();

    if (rc == VTSS_RC_OK) {
        VTSS_D(" -> status:"MACSEC_TX_SA_STATUS_FMT,
               MACSEC_TX_SA_STATUS_ARG(*status));
    }

    return rc;
}

vtss_rc vtss_macsec_tx_seca_set(const vtss_inst_t              inst,
                                const vtss_macsec_port_t       port,
                                const u16                      an,
                                const vtss_macsec_pkt_num_t    next_pn,
                                const BOOL                     confidentiality,
                                const vtss_macsec_sak_t        *const sak,
                                const vtss_macsec_ssci_t       *const ssci)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_AN_FMT" pn:%"PRIu64", confidentiality:%d cipher:%u, ssci:%c%c%c%c", MPORT_AN_ARG(port, an),
           next_pn.xpn, confidentiality, (sak->len == 16 ? 128 : 256),
           ssci->buf[3], ssci->buf[2], ssci->buf[1], ssci->buf[0]);
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sa_set_priv(vtss_state, secy_id, port, an, next_pn, confidentiality, sak, ssci);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_tx_seca_get(const vtss_inst_t              inst,
                                const vtss_macsec_port_t       port,
                                const u16                      an,
                                vtss_macsec_pkt_num_t          *const next_pn,
                                BOOL                           *const confidentiality,
                                vtss_macsec_sak_t              *const sak,
                                BOOL                           *const active,
                                vtss_macsec_ssci_t       *const ssci)
{
    vtss_macsec_internal_secy_t *secy;
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_D(MPORT_AN_FMT, MPORT_AN_ARG(port, an));
    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (secy->tx_sc.sa[an] == NULL) {
            VTSS_I("AN does not exist, port_no:%d, port_id:%d, an:%d", port.port_no, port.port_id, an);
            rc = dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_AN_NOT_EXIST);
            memset(sak, 0 , sizeof(*sak));
            *active          = FALSE;
            *confidentiality = FALSE;
            next_pn->xpn     = 0;
        } else {
            *sak             = secy->tx_sc.sa[an]->sak;
            *active          = secy->tx_sc.sa[an]->enabled;
            *confidentiality = secy->tx_sc.sa[an]->confidentiality;
            *next_pn         = secy->tx_sc.sa[an]->status.pn_status.next_pn;
            *ssci            = secy->tx_sc.sa[an]->ssci;
        }
    }
    VTSS_EXIT();

    if (rc == VTSS_RC_OK) {
        VTSS_D(" -> pn: %"PRIu64", confidentiality:%s, active:%s", next_pn->xpn,
               BOOL_ARG(*confidentiality), BOOL_ARG(*active));
    }

    return rc;

}
vtss_rc vtss_macsec_controlled_counters_get(const vtss_inst_t                  inst,
                                            const vtss_macsec_port_t           port,
                                            vtss_macsec_secy_port_counters_t  *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_id = 0;
    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));

    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_controlled_counters_get_priv(vtss_state, port, counters, secy_id);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_uncontrolled_counters_get(const vtss_inst_t                   inst,
                                              const vtss_port_no_t                port_no,
                                              vtss_macsec_uncontrolled_counters_t *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    VTSS_D("Port: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_uncontrolled_counters_get_priv(vtss_state, port_no, counters);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_common_counters_get(const vtss_inst_t               inst,
                                        const vtss_port_no_t            port_no,
                                        vtss_macsec_common_counters_t   *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    VTSS_D("Port: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_common_counters_get_priv(vtss_state, port_no, counters, FALSE);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_secy_cap_get(const vtss_inst_t             inst,
                                 const vtss_port_no_t          port_no,
                                 vtss_macsec_secy_cap_t        *const cap)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_D("Port: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (phy_is_1g(vtss_state, port_no)) {
            cap->max_peer_scs = VTSS_MACSEC_1G_MAX_SA / 2;
            cap->max_receive_keys = VTSS_MACSEC_1G_MAX_SA;
            cap->max_transmit_keys = VTSS_MACSEC_1G_MAX_SA;
        } else {
            cap->max_peer_scs = VTSS_MACSEC_10G_MAX_SA / 2;
            cap->max_receive_keys = VTSS_MACSEC_10G_MAX_SA;
            cap->max_transmit_keys = VTSS_MACSEC_10G_MAX_SA;
        }
    }
    cap->ciphersuite_cap = VTSS_MACSEC_CAP_GCM_AES_128 | VTSS_MACSEC_CAP_GCM_AES_256;

    if (vtss_state->macsec_conf[port_no].glb.macsec_revb == TRUE) {
        cap->ciphersuite_cap |= VTSS_MACSEC_CAP_GCM_AES_XPN_128 | VTSS_MACSEC_CAP_GCM_AES_XPN_256;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_secy_counters_get(const vtss_inst_t             inst,
                                      const vtss_macsec_port_t      port,
                                      vtss_macsec_secy_counters_t   *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_id = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_secy_counters_get_priv(vtss_state, port.port_no, counters, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_counters_update(const vtss_inst_t     inst,
                                    const vtss_port_no_t  port_no)

{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_counters_update_priv(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}
vtss_rc vtss_macsec_counters_clear(const vtss_inst_t     inst,
                                   const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_counters_clear_priv(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sc_counters_get(const vtss_inst_t               inst,
                                       const vtss_macsec_port_t        port,
                                       const vtss_macsec_sci_t         *const sci,
                                       vtss_macsec_rx_sc_counters_t    *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_id = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sc_counters_get_priv(vtss_state, port.port_no, sci, counters, secy_id);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_tx_sc_counters_get(const vtss_inst_t               inst,
                                       const vtss_macsec_port_t        port,
                                       vtss_macsec_tx_sc_counters_t    *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_id = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sc_counters_get_priv(vtss_state, port.port_no, counters, secy_id);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_tx_sa_counters_get(const vtss_inst_t               inst,
                                       const vtss_macsec_port_t        port,
                                       const u16                       an,
                                       vtss_macsec_tx_sa_counters_t    *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_id = 0;

    VTSS_D("Port: %u/%u/%u an:%u", MACSEC_PORT_ARG(&port), an);
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_tx_sa_counters_get_priv(vtss_state, port.port_no, an, counters, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rx_sa_counters_get(const vtss_inst_t            inst,
                                       const vtss_macsec_port_t     port,
                                       const vtss_macsec_sci_t      *const sci,
                                       const u16                    an,
                                       vtss_macsec_rx_sa_counters_t *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_id = 0;

    VTSS_D(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rx_sa_counters_get_priv(vtss_state, port.port_no, sci, an, counters, secy_id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_control_frame_match_conf_set(const vtss_inst_t                             inst,
                                                 const vtss_port_no_t                          port_no,
                                                 const vtss_macsec_control_frame_match_conf_t *const conf,
                                                 u32                                          *const rule_id)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_control_frame_match_conf_t match = *conf;
    u32 local_rule, *rule_id_p = NULL;

    {
        char buf[256];
        (void) vtss_macsec_frame_match_to_txt(buf, 256, conf);
        VTSS_I("port_no:%u. Control frame match: %s", port_no, buf);
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rule_id_p = (rule_id == NULL) ? &local_rule : rule_id;
        if ((rc = vtss_macsec_control_frame_match_conf_set_priv(vtss_state, port_no, &match, rule_id_p, 1)) == VTSS_RC_OK) {
            vtss_state->macsec_conf[port_no].glb.control_match[*rule_id_p] = *conf;
            VTSS_I("Rule_id used:%u match:%x", *rule_id_p, vtss_state->macsec_conf[port_no].glb.control_match[*rule_id_p].match);
        }
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_control_frame_match_conf_del(const vtss_inst_t                             inst,
                                                 const vtss_port_no_t                          port_no,
                                                 const u32                                     rule_id)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_control_frame_match_conf_t match;
    u32 rule = rule_id;

    VTSS_I("port_no: %u rule_id:%u", port_no, rule_id);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (rule_id >= VTSS_MACSEC_CP_RULES) {
            VTSS_E("Rule id is out of range");
            rc = dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_RULE_OUT_OF_RANGE);
        } else if (vtss_state->macsec_conf[port_no].glb.control_match[rule_id].match == VTSS_MACSEC_MATCH_DISABLE) {
            VTSS_E("Rule does not exist (id:%u)", rule_id);
            rc = dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_RULE_NOT_EXIST);
        } else {
            match = vtss_state->macsec_conf[port_no].glb.control_match[rule_id];
            rc = vtss_macsec_control_frame_match_conf_set_priv(vtss_state, port_no, &match, &rule, 0);
            memset(&vtss_state->macsec_conf[port_no].glb.control_match[rule_id], 0, sizeof(vtss_macsec_control_frame_match_conf_t));
            vtss_state->macsec_conf[port_no].glb.control_match[rule_id].match = VTSS_MACSEC_MATCH_DISABLE;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_control_frame_match_conf_get(const vtss_inst_t                             inst,
                                                 const vtss_port_no_t                          port_no,
                                                 vtss_macsec_control_frame_match_conf_t       *const conf,
                                                 u32                                           rule_id)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u rule_id:%u", port_no, rule_id);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (rule_id >= VTSS_MACSEC_CP_RULES) {
            VTSS_E("Rule id is out of range");
            rc = dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_RULE_OUT_OF_RANGE);
        } else {
            *conf = vtss_state->macsec_conf[port_no].glb.control_match[rule_id];
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_default_action_set(const vtss_inst_t                          inst,
                                       const vtss_port_no_t                       port_no,
                                       const vtss_macsec_default_action_policy_t *const policy)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_RC_COLD(vtss_macsec_default_action_set_priv(vtss_state, port_no, policy));
        vtss_state->macsec_conf[port_no].glb.default_action = *policy;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_default_action_get(const vtss_inst_t                          inst,
                                       const vtss_port_no_t                       port_no,
                                       vtss_macsec_default_action_policy_t       *const policy)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *policy = vtss_state->macsec_conf[port_no].glb.default_action;
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_pattern_set(const vtss_inst_t                  inst,
                                const vtss_macsec_port_t           port,
                                const vtss_macsec_direction_t      direction,
                                const vtss_macsec_match_action_t   action,
                                const vtss_macsec_match_pattern_t  *const pattern)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    {
        char buf[256];
        (void) vtss_macsec_match_pattern_to_txt(buf, 256, pattern);
        VTSS_I("port_no:%u action:%s dir:%s pattern match:%s",
               port.port_no, action == VTSS_MACSEC_MATCH_ACTION_DROP ? "drop"
               : action == VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT ? "ctrl" : "unctrl",
               direction == VTSS_MACSEC_DIRECTION_INGRESS ? "ingr" : "egr", buf);
    }

    VTSS_ENTER();
    do {
        if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) != VTSS_RC_OK) {
            break;
        }
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (action == VTSS_MACSEC_MATCH_ACTION_DROP || action == VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT) {
            if ((rc = VTSS_RC_COLD(vtss_macsec_pattern_set_priv(vtss_state, port.port_no, secy_id, direction, action, pattern, 0))) != VTSS_RC_OK) {
                break;
            }
        }
        secy->pattern[action][direction] = *pattern;
    } while (0);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_pattern_del(const vtss_inst_t                  inst,
                                const vtss_macsec_port_t           port,
                                const vtss_macsec_direction_t      direction,
                                const vtss_macsec_match_action_t   action)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    VTSS_I("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));

    VTSS_ENTER();
    do {
        if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) != VTSS_RC_OK) {
            break;
        }
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (action == VTSS_MACSEC_MATCH_ACTION_DROP || action == VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT) {
            if ((rc = vtss_macsec_pattern_del_priv(vtss_state, port, secy_id, direction, action)) != VTSS_RC_OK) {
                break;
            }
        }
        memset(&secy->pattern[action][direction], 0, sizeof(secy->pattern[action][direction]));
        secy->pattern[action][direction].match = VTSS_MACSEC_MATCH_DISABLE;
    } while (0);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_pattern_get(const vtss_inst_t                  inst,
                                const vtss_macsec_port_t           port,
                                const vtss_macsec_direction_t      direction,
                                const vtss_macsec_match_action_t   action,
                                vtss_macsec_match_pattern_t        *const pattern)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        if (secy->pattern[action][direction].match == VTSS_MACSEC_MATCH_DISABLE) {
            VTSS_I("No pattern is configured, port:%d, port_id:%d, direction:%d", port.port_no, port.port_id, direction);
            rc = dbg_counter_incr(vtss_state, port.port_no, VTSS_RC_ERR_MACSEC_NO_PATTERN_CFG);
        }
        *pattern = secy->pattern[action][direction];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_bypass_mode_set(const vtss_inst_t                inst,
                                    const vtss_port_no_t             port_no,
                                    const vtss_macsec_bypass_mode_t  *const bypass)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_RC_COLD(vtss_macsec_bypass_mode_set_priv(vtss_state, port_no, bypass));
        vtss_state->macsec_conf[port_no].glb.bypass_mode = *bypass;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_bypass_mode_get(const vtss_inst_t          inst,
                                    const vtss_port_no_t       port_no,
                                    vtss_macsec_bypass_mode_t  *const bypass)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *bypass = vtss_state->macsec_conf[port_no].glb.bypass_mode;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_bypass_tag_set(const vtss_inst_t              inst,
                                   const vtss_macsec_port_t       port,
                                   const vtss_macsec_tag_bypass_t tag)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    VTSS_I("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        secy->tag_bypass = tag;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_bypass_tag_get(const vtss_inst_t             inst,
                                   const vtss_macsec_port_t      port,
                                   vtss_macsec_tag_bypass_t      *const tag)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
        *tag = secy->tag_bypass;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_frame_capture_set(const vtss_inst_t                   inst,
                                      const vtss_port_no_t                port_no,
                                      const vtss_macsec_frame_capture_t   capture)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_frame_capture_set_priv(vtss_state, port_no, capture);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_frame_get(const vtss_inst_t             inst,
                              const vtss_port_no_t          port_no,
                              const u32                     buf_length,
                              u32                           *const frm_length,
                              u8                            *const frame)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_frame_get_priv(vtss_state, port_no, buf_length, frm_length, frame);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_event_enable_set(const vtss_inst_t           inst,
                                     const vtss_port_no_t        port_no,
                                     const vtss_macsec_event_t   ev_mask,
                                     const BOOL                  enable)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_event_enable_set_priv(vtss_state, port_no, ev_mask, enable);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_event_enable_get(const vtss_inst_t      inst,
                                     const vtss_port_no_t   port_no,
                                     vtss_macsec_event_t    *const ev_mask)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_event_enable_get_priv(vtss_state, port_no, ev_mask);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_event_poll(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_macsec_event_t  *const ev_mask)
{

    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

//    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_event_poll_priv(vtss_state, port_no, ev_mask);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_event_seq_threshold_set(const vtss_inst_t     inst,
                                            const vtss_port_no_t  port_no,
                                            const u32             threshold)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_event_seq_threshold_set_priv(vtss_state, port_no, threshold);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_event_seq_threshold_get(const vtss_inst_t     inst,
                                            const vtss_port_no_t  port_no,
                                            u32                   *const threshold)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_event_seq_threshold_get_priv(vtss_state, port_no, threshold);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_egr_intr_sa_get(const vtss_inst_t    inst,
                                    const vtss_port_no_t port_no,
                                    vtss_macsec_port_t   *const port,
                                    u16                  *const an)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_egr_intr_sa_get_priv(vtss_state, port_no, port, an);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_mtu_get(const vtss_inst_t       inst,
                            const vtss_port_no_t    port_no,
                            vtss_macsec_mtu_t       *mtu_conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *mtu_conf = vtss_state->macsec_conf[port_no].glb.mtu_conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_mtu_set(const vtss_inst_t       inst,
                            const vtss_port_no_t    port_no,
                            const vtss_macsec_mtu_t *const mtu_conf)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->macsec_conf[port_no].glb.mtu_conf.mtu  = mtu_conf->mtu;
        vtss_state->macsec_conf[port_no].glb.mtu_conf.drop = mtu_conf->drop;
        vtss_state->macsec_conf[port_no].glb.mtu_conf.vlan_unaware_en = mtu_conf->vlan_unaware_en;
        rc = VTSS_RC_COLD(vtss_macsec_mtu_set_priv(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_csr_read(const vtss_inst_t           inst,
                             const vtss_port_no_t        port_no,
                             const u16                   mmd,
                             const u32                   addr,
                             u32                         *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    BOOL is32 = is_reg_32(mmd, addr);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (csr_rd(vtss_state, port_no, mmd, is32, addr, value) != VTSS_RC_OK) {
            VTSS_E("Could not do CSR read, port_no:%d, mmd:%d,  addr:%d", port_no, mmd, addr);
            rc = dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_CSR_READ);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_csr_write(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              const u32                   mmd,
                              const u32                   addr,
                              const u32                   value)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    BOOL is32 = is_reg_32(mmd, addr);

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (csr_wr(vtss_state, port_no, mmd, is32, addr, value) != VTSS_RC_OK) {
            VTSS_E("Could not do CSR write, port_no:%d, mmd:%d, addr:%d, value:%d", port_no, mmd, addr, value);
            rc = dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_CSR_WRITE);
        }
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_hmac_counters_get(const vtss_inst_t           inst,
                                      const vtss_port_no_t        port_no,
                                      vtss_macsec_mac_counters_t  *const counters,
                                      const BOOL                  clear)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_hmac_counters_get_priv(vtss_state, port_no,  counters, clear);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_macsec_lmac_counters_get(const vtss_inst_t           inst,
                                      const vtss_port_no_t        port_no,
                                      vtss_macsec_mac_counters_t  *const counters,
                                      const BOOL                  clear)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_lmac_counters_get_priv(vtss_state, port_no,  counters, clear);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_fcbuf_frame_gap_comp_set(const vtss_inst_t     inst,
                                             const vtss_port_no_t  port_no,
                                             const u8              frm_gap)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (frm_gap >= 24 && frm_gap <= 56) {
            rc = vtss_fc_buffer_frm_gap_set(vtss_state, port_no, frm_gap);
        } else {
            VTSS_I("Frame gap compensation allowed range 24-56 bytes \n");
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_dbg_counter_get(const vtss_inst_t             inst,
                                    const vtss_port_no_t          port_no,
                                    vtss_macsec_rc_dbg_counters_t *const counters)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = dbg_counter_get_private(vtss_state, port_no, counters);
    }
    VTSS_EXIT();
    return rc;
}
/* Warm Start */
#define VTSS_SYNC_RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) {vtss_state->sync_calling_private = FALSE; return __rc__; }}
#define ACT_DROP   VTSS_MACSEC_MATCH_ACTION_DROP
#define ACT_CTRL   VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT
#define ACT_UNCTRL VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT
#define DIR_INGR   VTSS_MACSEC_DIRECTION_INGRESS
#define DIR_EGR    VTSS_MACSEC_DIRECTION_EGRESS
vtss_rc vtss_macsec_sync(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_macsec_internal_glb_t *ms = &vtss_state->macsec_conf[port_no].glb;
    u32 id = 0, phy_id = 0;
    vtss_macsec_port_t  *search_macsec_port, found_macsec_port;
    vtss_macsec_sci_t  *search_sci, found_sci;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id, an;
    vtss_macsec_pkt_num_t pkt_num;
    BOOL phy10g = FALSE;

    pkt_num.xpn = 0;
    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
    if (phy10g) {
#ifdef VTSS_CHIP_10G_PHY
        if (vtss_state->phy_10g_state[port_no].power ||
            !vtss_state->macsec_conf[port_no].glb.init.enable) {
            VTSS_I("Skipping macsec sync process in warmstart on port_no:%d id:VSC%d (Port disabled/MACsec disabled)", port_no, phy_id);
            return VTSS_RC_OK;
        }
#endif
    } else {
#ifdef VTSS_CHIP_CU_PHY
        if ((vtss_state->phy_state[port_no].setup.mode == VTSS_PHY_MODE_POWER_DOWN) ||
            (!vtss_state->macsec_conf[port_no].glb.init.enable)) {
            VTSS_I("Skipping macsec sync process in warmstart on port_no:%d id:VSC%d (Port disabled/MACsec disabled)", port_no, phy_id);
            return VTSS_RC_OK;
        }
#endif
    }

    if (vtss_macsec_verify_port(vtss_state, port_no, &phy_id) != VTSS_RC_OK) {
        VTSS_I("Skipping macsec warmstart on port_no:%d id:VSC%d (Not macsec capable or macsec disabled)", port_no, phy_id);
        return VTSS_RC_OK;
    }

    VTSS_I("vtss_macsec_sync - start port:%d id:VSC%d", port_no, phy_id);
    vtss_state->sync_calling_private = TRUE;
    ms->warm_start_reg_changed = FALSE;

    /* Sync all macsec private functions  */
    /* Macsec init set is intentionally commented here. Macsec initialisation requires specific sequence of
       order of enabling macsec configuration. This involves cold writes which may be executed again during
       warmstart. To avoid them, this function must not be called during warmstart. */
    //VTSS_SYNC_RC(vtss_macsec_init_set_priv(vtss_state, port_no, &ms->init));
    VTSS_SYNC_RC(vtss_macsec_default_action_set_priv(vtss_state, port_no, &ms->default_action));
    VTSS_SYNC_RC(vtss_macsec_bypass_mode_set_priv(vtss_state, port_no, &ms->bypass_mode));

    for (id = 0; id < VTSS_MACSEC_CP_RULES; id++) {
        if (ms->control_match[id].match != VTSS_MACSEC_MATCH_DISABLE) {
            VTSS_I("vtss_macsec_control_frame_match_conf_set_priv %d", ms->control_match[id].match);

            VTSS_SYNC_RC(vtss_macsec_control_frame_match_conf_set_priv(vtss_state, port_no, &ms->control_match[id], &id, 1));
        }
    }
    VTSS_SYNC_RC(vtss_macsec_mtu_set_priv(vtss_state, port_no));

    search_macsec_port = NULL;
    while (vtss_macsec_port_get_next_priv(vtss_state, port_no, search_macsec_port, &found_macsec_port, &secy_id, &secy) == VTSS_RC_OK) {
        search_macsec_port = &found_macsec_port;
        VTSS_I("Got macsec.port_id:%d service_id:%d secy_id:%d", found_macsec_port.port_id, found_macsec_port.service_id, secy_id);
        if (secy->pattern[ACT_UNCTRL][DIR_INGR].match != VTSS_MACSEC_MATCH_DISABLE) { // ACTION_UNCONTROLLED DIR_INGRESS
            VTSS_SYNC_RC(vtss_macsec_pattern_set_priv(vtss_state, port_no, secy_id, DIR_INGR, ACT_UNCTRL, &secy->pattern[ACT_UNCTRL][DIR_INGR], 0));
        }
        if (secy->pattern[ACT_UNCTRL][DIR_EGR].match != VTSS_MACSEC_MATCH_DISABLE) { // ACTION_UNCONTROLLED DIR_INGRESS
            VTSS_SYNC_RC(vtss_macsec_pattern_set_priv(vtss_state, port_no, secy_id, DIR_EGR, ACT_UNCTRL, &secy->pattern[ACT_UNCTRL][DIR_EGR], 0));
        }
        if (secy->pattern[ACT_DROP][DIR_INGR].match != VTSS_MACSEC_MATCH_DISABLE) { // ACTION_UNCONTROLLED DIR_INGRESS
            VTSS_SYNC_RC(vtss_macsec_pattern_set_priv(vtss_state, port_no, secy_id, DIR_INGR, ACT_DROP, &secy->pattern[ACT_DROP][DIR_INGR], 0));
        }
        if (secy->pattern[ACT_DROP][DIR_EGR].match != VTSS_MACSEC_MATCH_DISABLE) { // ACTION_UNCONTROLLED DIR_INGRESS
            VTSS_SYNC_RC(vtss_macsec_pattern_set_priv(vtss_state, port_no, secy_id, DIR_EGR, ACT_DROP, &secy->pattern[ACT_DROP][DIR_EGR], 0));
        }

        search_sci = NULL;
        while (vtss_macsec_rx_sc_get_next_priv(vtss_state, found_macsec_port, search_sci, &found_sci, secy_id) == VTSS_RC_OK) {
            VTSS_I(MPORT_SCI_FMT, MPORT_SCI_ARG(found_macsec_port, found_sci));
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                VTSS_SYNC_RC(vtss_macsec_rx_sa_set_priv(vtss_state, secy_id, found_macsec_port, &found_sci, an, pkt_num, NULL, NULL) != VTSS_RC_OK);
                VTSS_SYNC_RC(vtss_macsec_rx_sa_activate_priv(vtss_state, secy_id, found_macsec_port, &found_sci, an));
            }
            search_sci = &found_sci;
        }

        if (secy->tx_sc.in_use) {
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                VTSS_SYNC_RC(vtss_macsec_tx_sa_set_priv(vtss_state, secy_id, found_macsec_port, an, pkt_num, 0, NULL, NULL) != VTSS_RC_OK);
                VTSS_SYNC_RC(vtss_macsec_tx_sa_activate_priv(vtss_state, secy_id, found_macsec_port, an));
            }
        }
    }

    vtss_state->sync_calling_private = FALSE;
    VTSS_I("vtss_macsec_sync - end port:%d id:VSC%d\n", port_no, phy_id);
    return VTSS_RC_OK;
}

#ifdef VTSS_MACSEC_FIFO_OVERFLOW_WORKAROUND
vtss_rc vtss_macsec_reconfigure(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_macsec_internal_glb_t *ms = &vtss_state->macsec_conf[port_no].glb;
    u32 id = 0, phy_id = 0;
    vtss_macsec_port_t  *search_macsec_port, found_macsec_port;
    vtss_macsec_sci_t  *search_sci, found_sci;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id, an;
    vtss_macsec_pkt_num_t pkt_num;

    pkt_num.xpn = 0;
    if (vtss_macsec_verify_port(vtss_state, port_no, &phy_id) != VTSS_RC_OK) {
        VTSS_I("Skip reconfiguration on port_no:%d id:VSC%d (Not macsec capable or macsec disabled)", port_no, phy_id);
        return VTSS_RC_OK;
    }

    vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg = TRUE;
    VTSS_I("vtss_macsec_reconfigure_macsec - start port:%d id:VSC%d", port_no, phy_id);

    /* Re-Configure macsec using private functions  */
    (void)vtss_macsec_default_action_set_priv(vtss_state, port_no, &ms->default_action);
    (void)vtss_macsec_bypass_mode_set_priv(vtss_state, port_no, &ms->bypass_mode);

    for (id = 0; id < VTSS_MACSEC_CP_RULES; id++) {
        if (ms->control_match[id].match != VTSS_MACSEC_MATCH_DISABLE) {
            VTSS_I("vtss_macsec_control_frame_match_conf_set_priv %d", ms->control_match[id].match);
            (void)vtss_macsec_control_frame_match_conf_set_priv(vtss_state, port_no, &ms->control_match[id], &id, 1);
        }
    }
    (void)vtss_macsec_mtu_set_priv(vtss_state, port_no);

    search_macsec_port = NULL;
    while (vtss_macsec_port_get_next_priv(vtss_state, port_no, search_macsec_port, &found_macsec_port, &secy_id, &secy) == VTSS_RC_OK) {
        search_macsec_port = &found_macsec_port;
        VTSS_I("Got macsec.port_id:%d service_id:%d secy_id:%d", found_macsec_port.port_id, found_macsec_port.service_id, secy_id);
        if (secy->pattern[ACT_UNCTRL][DIR_INGR].match != VTSS_MACSEC_MATCH_DISABLE) { // ACTION_UNCONTROLLED DIR_INGRESS
            (void)vtss_macsec_pattern_set_priv(vtss_state, port_no, secy_id, DIR_INGR, ACT_UNCTRL, &secy->pattern[ACT_UNCTRL][DIR_INGR], 0);
        }
        if (secy->pattern[ACT_UNCTRL][DIR_EGR].match != VTSS_MACSEC_MATCH_DISABLE) { // ACTION_UNCONTROLLED DIR_INGRESS
            (void)vtss_macsec_pattern_set_priv(vtss_state, port_no, secy_id, DIR_EGR, ACT_UNCTRL, &secy->pattern[ACT_UNCTRL][DIR_EGR], 0);
        }
        if (secy->pattern[ACT_DROP][DIR_INGR].match != VTSS_MACSEC_MATCH_DISABLE) { // ACTION_UNCONTROLLED DIR_INGRESS
            (void)vtss_macsec_pattern_set_priv(vtss_state, port_no, secy_id, DIR_INGR, ACT_DROP, &secy->pattern[ACT_DROP][DIR_INGR], 0);
        }
        if (secy->pattern[ACT_DROP][DIR_EGR].match != VTSS_MACSEC_MATCH_DISABLE) { // ACTION_UNCONTROLLED DIR_INGRESS
            (void)vtss_macsec_pattern_set_priv(vtss_state, port_no, secy_id, DIR_EGR, ACT_DROP, &secy->pattern[ACT_DROP][DIR_EGR], 0);
        }

        search_sci = NULL;
        while (vtss_macsec_rx_sc_get_next_priv(vtss_state, found_macsec_port, search_sci, &found_sci, secy_id) == VTSS_RC_OK) {
            VTSS_I(MPORT_SCI_FMT, MPORT_SCI_ARG(found_macsec_port, found_sci));
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                (void)vtss_macsec_rx_sa_set_priv(vtss_state, secy_id, found_macsec_port, &found_sci, an, pkt_num, NULL, NULL);
                (void)vtss_macsec_rx_sa_activate_priv(vtss_state, secy_id, found_macsec_port, &found_sci, an);
            }
            search_sci = &found_sci;
        }
        if (secy->tx_sc.in_use) {
            secy->tx_sc.status.encoding_sa = 0;
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                (void)vtss_macsec_tx_sa_set_priv(vtss_state, secy_id, found_macsec_port, an, pkt_num, 0, NULL, NULL);
                (void)vtss_macsec_tx_sa_activate_priv(vtss_state, secy_id, found_macsec_port, an);
            }
        }
    }
    vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg = FALSE;
    VTSS_I("vtss_macsec_reconfig - end port:%d id:VSC%d\n", port_no, phy_id);

    return VTSS_RC_OK;
}
#endif

vtss_rc vtss_macsec_inst_count_get(const vtss_inst_t    inst,
                                   const vtss_port_no_t port_no,
                                   vtss_macsec_inst_count_t *counts)
{
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_state_t *vtss_state;

    VTSS_ENTER();

    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_state->macsec_conf[port_no].glb.init.enable == 0) {
            VTSS_E("MacSec API port:%u not enabled", port_no);
            rc =  dbg_counter_incr(vtss_state, port_no, VTSS_RC_ERR_MACSEC_NOT_ENABLED);
        } else {
            rc = macsec_inst_count_get_priv(vtss_state, port_no, counts);
            if (rc != VTSS_RC_OK) {
                VTSS_E("Macsec Instance Count access Error");
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_lmac_counters_clear(const vtss_inst_t  inst,
                                        const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_lmac_counters_clear_priv(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_hmac_counters_clear(const vtss_inst_t  inst,
                                        const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_hmac_counters_clear_priv(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_debug_counters_clear(const vtss_inst_t  inst,
                                         const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = dbg_counter_clr(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_common_counters_clear(const vtss_inst_t  inst,
                                          const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_macsec_common_counters_t counters;
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_common_counters_get_priv(vtss_state, port_no, &counters, TRUE);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_uncontrolled_counters_clear(const vtss_inst_t  inst,
                                                const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_uncontrolled_counters_clear_priv(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_controlled_counters_clear (const vtss_inst_t  inst,
                                               const vtss_macsec_port_t  port)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_idx = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_idx)) == VTSS_RC_OK) {
        rc = vtss_macsec_controlled_counters_clear_priv(vtss_state, port.port_no, secy_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rxsa_counters_clear(const vtss_inst_t  inst,
                                        const vtss_macsec_port_t  port,
                                        const vtss_macsec_sci_t  *const sci,
                                        const u16  an)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_idx = 0;

    VTSS_D(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_idx)) == VTSS_RC_OK) {
        rc = vtss_macsec_rxsa_counters_clear_priv(vtss_state, port.port_no, sci, an, secy_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rxsc_counters_clear(const vtss_inst_t  inst,
                                        const vtss_macsec_port_t  port,
                                        const vtss_macsec_sci_t  *const sci)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_idx = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_idx)) == VTSS_RC_OK) {
        rc = vtss_macsec_rxsc_counters_clear_priv(vtss_state, port.port_no, sci, secy_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_txsa_counters_clear(const vtss_inst_t  inst,
                                        const vtss_macsec_port_t  port,
                                        const u16  an)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_idx = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_idx)) == VTSS_RC_OK) {
        rc = vtss_macsec_txsa_counters_clear_priv(vtss_state, port.port_no, an, secy_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_txsc_counters_clear (const vtss_inst_t  inst,
                                         const vtss_macsec_port_t  port)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_idx = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_idx)) == VTSS_RC_OK) {
        rc = vtss_macsec_txsc_counters_clear_priv(vtss_state, port.port_no, secy_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_secy_counters_clear (const vtss_inst_t  inst,
                                         const vtss_macsec_port_t  port)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u32 secy_idx = 0;

    VTSS_D("Port: %u/%u/%u", MACSEC_PORT_ARG(&port));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_idx)) == VTSS_RC_OK) {
        rc = vtss_macsec_secy_counters_clear_priv(vtss_state, port.port_no, secy_idx);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_port_enable_status_get (const vtss_inst_t  inst,
                                            const vtss_port_no_t  port_no,
                                            BOOL  *status)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (!is_macsec_capable(vtss_state, port_no)) {
            VTSS_D("Port/Phy :%u is not MacSec capable", port_no);
            *status = FALSE;
        } else {
            if (vtss_state->macsec_conf[port_no].glb.init.enable == 0) {
                *status = FALSE;
//                VTSS_D("Macsec Port :%u Disabled", port_no);
            } else {
                *status = TRUE;
//                VTSS_D("Macsec Port :%u Enabled", port_no);
            }
        }
    } else {
        VTSS_E("Port Check Error on %u", port_no);
        rc = VTSS_RC_ERROR;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_rxsa_an_status_get (const vtss_inst_t        inst,
                                        const vtss_macsec_port_t port,
                                        const vtss_macsec_sci_t  *const sci,
                                        const u16                an,
                                        BOOL                     *status)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_MACSEC_ASSERT(an >= VTSS_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    VTSS_I(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_rxsa_an_status_get_priv(vtss_state, secy_id, port, sci, an, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_mac_block_mtu_get(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               u16 *const mtu_value,
                               BOOL *const mtu_tag_check)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u", port_no);

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_RC_COLD(vtss_mac_block_mtu_get_priv(vtss_state, port_no, mtu_value, mtu_tag_check));
    }
    VTSS_EXIT();
    return rc;
}
vtss_rc vtss_mac_block_mtu_set(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               const u16            mtu_value,
                               const BOOL           mtu_tag_check)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("port_no: %u, MTU:%d, Tag:%d", port_no, mtu_value, mtu_tag_check);

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
//        rc = VTSS_RC_COLD(vtss_mac_block_mtu_set_priv(vtss_state, port_no, mtu_value, mtu_tag_check));
        rc = vtss_mac_block_mtu_set_priv(vtss_state, port_no, mtu_value, mtu_tag_check);
    }
    VTSS_EXIT();
    return rc;
}

/* ================================================================= *
 *  Debug
 * ================================================================= */

// Function for printing the counter values in 2 rows (rx to the left, tx to the right).
// In: pr    - Pointer to print function.
//     name  - string with counter name
//     rx_cnt - RX counter value - Set to NULL if there is no RX counter
//     tx_cnt - TX counter value - Set to NULL if there is no TX counter
static void  vtss_macsec_debug_print_counter(const vtss_debug_printf_t pr,
                                             const char *name,
                                             const u64 *rx_cnt,
                                             const u64 *tx_cnt)
{
    if (rx_cnt != NULL) {
        pr("Rx %-25s %-25" PRIu64, name, *rx_cnt);
    } else {

        pr("   %-25s %-25s", "", ""); // Make the space to TX counters
    }

    if (tx_cnt != NULL) {
        pr("Tx %-25s %-25" PRIu64, name, *tx_cnt);
    }

    pr("\n");
}



// Function for printing the counter header.
// In: pr    - Pointer to print function.
//     name  - string with counter header name
static void  vtss_macsec_debug_print_counter_hdr(const vtss_debug_printf_t pr,
                                                 const char *name)
{
    pr("------------------------------ %-22s ------------------------------\n", name);
}


static void vtss_macsec_debug_print_sticky_dbg(const vtss_debug_printf_t pr,
                                               const char *name,
                                               const u32 value,
                                               const u32 val2,
                                               const u32 bit)
{
    if (value & VTSS_BIT(bit) || val2 & VTSS_BIT(bit)) {
        pr("%-25s  %-15d  %u\n", name, (value & VTSS_BIT(bit)) ? 1 : 0, (val2 & VTSS_BIT(bit)) ? 1 : 0);
    }
}


static void  vtss_macsec_debug_print_field_dbg(const vtss_debug_printf_t pr,
                                               const char *name,
                                               const u32 value,
                                               const u32 val2,
                                               const u32 o,
                                               const u32 w,
                                               BOOL hex)
{
    if (hex) {
        pr("%-26s 0x%-14x 0x%x\n", name, VTSS_EXTRACT_BITFIELD(value, o, w), VTSS_EXTRACT_BITFIELD(val2, o, w));
    } else {
        pr("%-26s %-14d   %u\n", name, VTSS_EXTRACT_BITFIELD(value, o, w), VTSS_EXTRACT_BITFIELD(val2, o, w));
    }
}

// Debug function for printing MACSEC configuration in vtss_state
static void vtss_debug_print_macsec_vtss_state(const vtss_state_t        *vtss_state,
                                               const vtss_debug_printf_t pr,
                                               const vtss_port_no_t      port_no)
{
    // MTU
    vtss_macsec_debug_print_counter_hdr(pr, "Vtss_state configuration");
    pr("mtu:%-5d  drop:%-5d vlan_unaware_en:%-5d\n", vtss_state->macsec_conf[port_no].glb.mtu_conf.mtu,
       vtss_state->macsec_conf[port_no].glb.mtu_conf.drop, vtss_state->macsec_conf[port_no].glb.mtu_conf.vlan_unaware_en);
}

// Function for printing debug return code error counters
static void  vtss_debug_print_rc_macsec_rc_dbg_counters(const vtss_debug_printf_t pr,
                                                        const char *name,
                                                        const u32  counter)
{

    pr("RC %-23s %d\n", name, counter);
}

// Function for printing debug return code error counters
static vtss_rc vtss_debug_print_macsec_rc_dbg_counters(const vtss_state_t        *vtss_state,
                                                       const vtss_debug_printf_t pr,
                                                       const vtss_debug_info_t   *const info,
                                                       const vtss_port_no_t       port_no)
{
    vtss_macsec_rc_dbg_counters_t counters;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_MACSEC)) {
        return VTSS_RC_OK;
    }
    vtss_macsec_debug_print_counter_hdr(pr, "Debug Return Code Counters");
    VTSS_RC(dbg_counter_get_private(vtss_state, port_no, &counters));
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "invalid_sci_macaddr",    counters.invalid_sci_macaddr);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "macsec_not_enabled",     counters.macsec_not_enabled);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "secy_already_in_use",    counters.secy_already_in_use);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "no_secy_found",          counters.no_secy_found);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "no_secy_vacency",        counters.no_secy_vacency);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "invalid_validate_frm",   counters.invalid_validate_frm);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "invalid_hdr_bypass_len", counters.invalid_hdr_bypass_len);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "sc_not_found",           counters.sc_not_found);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_prg_sa_match", counters.could_not_prg_sa_match);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_prg_sa_flow",  counters.could_not_prg_sa_flow);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_ena_sa",       counters.could_not_ena_sa);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_set_sa",       counters.could_not_set_sa);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "no_ctrl_frm_match",      counters.no_ctrl_frm_match);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_set_pattern",  counters.could_not_set_pattern);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "timeout_issue",          counters.timeout_issue);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_empty_egress", counters.could_not_empty_egress);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "an_not_created",         counters.an_not_created);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_empty_ingress", counters.could_not_empty_ingress);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "tx_sc_not_exist",        counters.tx_sc_not_exist);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_disable_sa",   counters.could_not_disable_sa);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_del_rx_sa",    counters.could_not_del_rx_sa);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_del_tx_sa",    counters.could_not_del_tx_sa);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "pattern_not_set",        counters.pattern_not_set);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "hw_resource_exhusted",   counters.hw_resource_exhusted);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "sci_already_exist",      counters.sci_already_exist);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "sc_resource_not_found",  counters.sc_resource_not_found);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "rx_an_already_in_use",   counters.rx_an_already_in_use);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "empty_record",           counters.empty_record);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_prg_xform",    counters.could_not_prg_xform);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_toggle_sa",    counters.could_not_toggle_sa);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "tx_an_already_in_use",   counters.tx_an_already_in_use);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "all_available_sa_in_use", counters.all_available_sa_in_use);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "match_disable",          counters.match_disable);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "all_cp_rules_in_use",    counters.all_cp_rules_in_use);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "pattern_prio_not_valid", counters.pattern_prio_not_valid);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "buffer_too_small",       counters.buffer_too_small);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "frm_too_long",           counters.frm_too_long);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "frm_truncated",          counters.frm_truncated);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "phy_powered_down",       counters.phy_powered_down);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "phy_not_macsec_capable", counters.phy_not_macsec_capable);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "an_not_exist",           counters.an_not_exist);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "phy_not_macsec_capable", counters.phy_not_macsec_capable);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "max_mtu",                counters.max_mtu);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "unexpected_cp_mode",     counters.unexpected_cp_mode);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "could_not_disable_an",   counters.could_not_disable_an);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "rule_out_of_range",      counters.rule_out_of_range);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "rule_not_exit",          counters.rule_not_exit);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "csr_read",               counters.csr_read);
    vtss_debug_print_rc_macsec_rc_dbg_counters(pr, "unknown_rc_code",        counters.unknown_rc_code);

    return VTSS_RC_OK;
}

// Debug function for printing MACSEC counters for a specific port
static vtss_rc vtss_debug_print_macsec_counters(vtss_state_t              *vtss_state,
                                                const vtss_debug_printf_t pr,
                                                const vtss_debug_info_t   *const info,
                                                const vtss_port_no_t      port_no)
{


    vtss_macsec_uncontrolled_counters_t uncontrolled_counters;
    vtss_macsec_secy_port_counters_t    controlled_counters;
    vtss_macsec_common_counters_t       common_counters;
    vtss_macsec_rx_sa_counters_t        rx_sa_counters;
    vtss_macsec_tx_sa_counters_t        tx_sa_counters;
    vtss_macsec_tx_sc_counters_t        tx_sc_counters;
    vtss_macsec_rx_sc_counters_t        rx_sc_counters;
    vtss_macsec_secy_counters_t         secy_counters;
    char                                str_buf[50];
    u32                                 an, sc;
    u32                                 max_sc_rx;
    vtss_macsec_internal_secy_t *secy;
    u32 secy_id, max_secy;
    vtss_macsec_port_t macsec_port;
    //
    // Common counters
    //
    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_MACSEC)) {
        return VTSS_RC_OK;
    }
    vtss_macsec_debug_print_counter_hdr(pr, "Common Counters");
    VTSS_RC(vtss_macsec_common_counters_get_priv(vtss_state, port_no, &common_counters, FALSE));

    vtss_macsec_debug_print_counter(pr, "Octets", &common_counters.if_in_octets, &common_counters.if_out_octets);
    vtss_macsec_debug_print_counter(pr, "Unicast", &common_counters.if_in_ucast_pkts, &common_counters.if_out_ucast_pkts);
    vtss_macsec_debug_print_counter(pr, "Multicast", &common_counters.if_in_multicast_pkts, &common_counters.if_out_multicast_pkts);
    vtss_macsec_debug_print_counter(pr, "Broadcast", &common_counters.if_in_broadcast_pkts, &common_counters.if_out_broadcast_pkts);

    vtss_macsec_debug_print_counter(pr, "Discards", &common_counters.if_in_discards, NULL);
    vtss_macsec_debug_print_counter(pr, "Errors", &common_counters.if_in_errors, &common_counters.if_out_errors);


    //
    // Uncontrolled counters
    //
    vtss_macsec_debug_print_counter_hdr(pr, "Uncontrolled Counters");
    VTSS_RC(vtss_macsec_uncontrolled_counters_get_priv(vtss_state, port_no, &uncontrolled_counters));
    vtss_macsec_debug_print_counter(pr, "Octets",    &uncontrolled_counters.if_in_octets, &uncontrolled_counters.if_out_octets);
    vtss_macsec_debug_print_counter(pr, "Unicast",   &uncontrolled_counters.if_in_ucast_pkts, NULL);
    vtss_macsec_debug_print_counter(pr, "Multicast", &uncontrolled_counters.if_in_multicast_pkts, NULL);
    vtss_macsec_debug_print_counter(pr, "Broadcast", &uncontrolled_counters.if_in_broadcast_pkts, NULL);

    vtss_macsec_debug_print_counter(pr, "Discards",  &uncontrolled_counters.if_in_discards, NULL);
    vtss_macsec_debug_print_counter(pr, "Errors",    &uncontrolled_counters.if_in_errors, &uncontrolled_counters.if_out_errors);

    //
    // Controlled counters
    //
    macsec_port.service_id = 0;
    macsec_port.port_id = 0;
    macsec_port.port_no = port_no;

    if (phy_is_1g(vtss_state, port_no)) {
        max_secy = VTSS_MACSEC_1G_MAX_SECY;
    } else {
        max_secy = VTSS_MACSEC_10G_MAX_SECY;
    }

    for (secy_id = 0; secy_id < max_secy; secy_id++) {
        secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
        if (secy != NULL && secy->in_use) {
            sprintf(&str_buf[0], "Controlled Counters - Secy:%u", secy_id);
            vtss_macsec_debug_print_counter_hdr(pr, &str_buf[0]);
            VTSS_RC(vtss_macsec_controlled_counters_get_priv(vtss_state, macsec_port, &controlled_counters, secy_id));
            vtss_macsec_debug_print_counter(pr, "Octets", &controlled_counters.if_in_octets, &controlled_counters.if_out_octets);

            vtss_macsec_debug_print_counter(pr, "Packets", &controlled_counters.if_in_pkts, &controlled_counters.if_out_pkts);
            vtss_macsec_debug_print_counter(pr, "Discards", &controlled_counters.if_in_discards, NULL);
            vtss_macsec_debug_print_counter(pr, "Errors", &controlled_counters.if_in_errors, &controlled_counters.if_out_errors);


            sprintf(&str_buf[0], "Secy Counters - Secy:%u", secy_id);
            vtss_macsec_debug_print_counter_hdr(pr, &str_buf[0]);

            VTSS_RC(vtss_macsec_secy_counters_get_priv(vtss_state, port_no, &secy_counters, secy_id));
            vtss_macsec_debug_print_counter(pr, "Packets untagged", &secy_counters.in_pkts_untagged, &secy_counters.out_pkts_untagged);
            vtss_macsec_debug_print_counter(pr, "Packets no tag", &secy_counters.in_pkts_no_tag, NULL);
            vtss_macsec_debug_print_counter(pr, "Packets bad tag", &secy_counters.in_pkts_bad_tag, NULL);
            vtss_macsec_debug_print_counter(pr, "Packets unknown sci", &secy_counters.in_pkts_unknown_sci, NULL);
            vtss_macsec_debug_print_counter(pr, "Packets no sci", &secy_counters.in_pkts_no_sci, NULL);
            vtss_macsec_debug_print_counter(pr, "Packets overrun", &secy_counters.in_pkts_overrun, NULL);

            vtss_macsec_debug_print_counter(pr, "Octets validated", &secy_counters.in_octets_validated, NULL);

            vtss_macsec_debug_print_counter(pr, "Octets decrypted", &secy_counters.in_octets_decrypted, NULL);

            vtss_macsec_debug_print_counter(pr, "Packets too long", NULL, &secy_counters.out_pkts_too_long);
            vtss_macsec_debug_print_counter(pr, "Octets protected", NULL, &secy_counters.out_octets_protected);
            vtss_macsec_debug_print_counter(pr, "Octets encrypted", NULL, &secy_counters.out_octets_encrypted);

            sprintf(&str_buf[0], "SC Counters - Secy:%u", secy_id);
            vtss_macsec_debug_print_counter_hdr(pr, &str_buf[0]);

            VTSS_RC(vtss_macsec_tx_sc_counters_get_priv(vtss_state, port_no, &tx_sc_counters, secy_id));
            vtss_macsec_debug_print_counter(pr, "Packets protected", NULL, &tx_sc_counters.out_pkts_protected);
            vtss_macsec_debug_print_counter(pr, "Packets encrypted", NULL, &tx_sc_counters.out_pkts_encrypted);

            //
            // Tx SA
            //
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                if (secy->tx_sc.sa[an] == NULL || !secy->tx_sc.sa[an]->in_use) {
                    VTSS_I("an:%u", an);
                    continue;
                }
                sprintf(&str_buf[0], "TX SA Counters - Secy:%u, an:%u", secy_id, an);
                vtss_macsec_debug_print_counter_hdr(pr, &str_buf[0]);

                VTSS_RC(vtss_macsec_tx_sa_counters_get_priv(vtss_state, port_no, an, &tx_sa_counters, secy_id));
                vtss_macsec_debug_print_counter(pr, "Packets protected", NULL, &tx_sa_counters.out_pkts_protected);
                vtss_macsec_debug_print_counter(pr, "Packets encrypted", NULL, &tx_sa_counters.out_pkts_encrypted);
            }

            if (phy_is_1g(vtss_state, port_no)) {
                max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
            } else {
                max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
            }
            //
            // Rx Secy
            //
            for (sc = 0; sc < max_sc_rx; sc++) {
                if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
                    continue;
                }

                sprintf(&str_buf[0], "SC Counters - SC:%u", sc);
                vtss_macsec_debug_print_counter_hdr(pr, &str_buf[0]);

                // Get rx_sc counter
                VTSS_RC(vtss_macsec_rx_sc_counters_get_priv(vtss_state,
                                                            port_no,
                                                            &secy->rx_sc[sc]->sci,
                                                            &rx_sc_counters,
                                                            secy_id));

                vtss_macsec_debug_print_counter(pr, "Packets unchecked", &rx_sc_counters.in_pkts_unchecked, NULL);
                vtss_macsec_debug_print_counter(pr, "Packets delayed", &rx_sc_counters.in_pkts_delayed, NULL);
                vtss_macsec_debug_print_counter(pr, "Packets late", &rx_sc_counters.in_pkts_late, NULL);
                vtss_macsec_debug_print_counter(pr, "Packets ok", &rx_sc_counters.in_pkts_ok, NULL);
                vtss_macsec_debug_print_counter(pr, "Packets invalid", &rx_sc_counters.in_pkts_invalid, NULL);
                vtss_macsec_debug_print_counter(pr, "Packets not valid", &rx_sc_counters.in_pkts_not_valid, NULL);
                vtss_macsec_debug_print_counter(pr, "Packets Not using SA", &rx_sc_counters.in_pkts_not_using_sa, NULL);
                vtss_macsec_debug_print_counter(pr, "Packets Unused SA", &rx_sc_counters.in_pkts_unused_sa, NULL);

                // Rx SA
                for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                    if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
                        VTSS_I("an:%u, NULL:%u", an, secy->rx_sc[sc]->sa[an] == NULL);
                        continue;
                    }
                    sprintf(&str_buf[0], "RX SA Counters - Secy:%u, an:%u", secy_id, an);
                    vtss_macsec_debug_print_counter_hdr(pr, &str_buf[0]);

                    VTSS_RC(vtss_macsec_rx_sa_counters_get_priv(vtss_state, port_no, &secy->rx_sc[sc]->sci, an, &rx_sa_counters, secy_id));
                    vtss_macsec_debug_print_counter(pr, "Packets Ok", &rx_sa_counters.in_pkts_ok, NULL);
                    vtss_macsec_debug_print_counter(pr, "Packets Invalid", &rx_sa_counters.in_pkts_invalid, NULL);
                    vtss_macsec_debug_print_counter(pr, "Packets Not valid", &rx_sa_counters.in_pkts_not_valid, NULL);
                    vtss_macsec_debug_print_counter(pr, "Packets Not using SA", &rx_sa_counters.in_pkts_not_using_sa, NULL);
                    vtss_macsec_debug_print_counter(pr, "Packets Unused SA", &rx_sa_counters.in_pkts_unused_sa, NULL);
                }
            }
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_debug_print_macsec_conf(vtss_state_t              *vtss_state,
                                            const vtss_debug_printf_t pr,
                                            const vtss_debug_info_t   *const info,
                                            const vtss_port_no_t      port_no)
{
    u32                                 an, sc;

    vtss_macsec_internal_secy_t *secy;
    u32 secy_id, i;
    u32 max_secy, max_sc_rx;
    u32 max_sa_rx;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_MACSEC)) {
        return VTSS_RC_OK;
    }
    if (phy_is_1g(vtss_state, port_no)) {
        max_secy = VTSS_MACSEC_1G_MAX_SECY;
        max_sc_rx = VTSS_MACSEC_1G_MAX_SC_RX;
        max_sa_rx = VTSS_MACSEC_1G_MAX_SA_RX;
    } else {
        max_secy = VTSS_MACSEC_10G_MAX_SECY;
        max_sc_rx = VTSS_MACSEC_10G_MAX_SC_RX;
        max_sa_rx = VTSS_MACSEC_10G_MAX_SA_RX;
    }

    for (secy_id = 0; secy_id < max_secy; secy_id++) {
        secy = &vtss_state->macsec_conf[port_no].secy[secy_id];
        if (secy != NULL && secy->in_use) {
            pr("************** API internals ************* \n");
            pr("SecY SCI: %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx - %d\n", MACADDRESS_ARG(secy->sci.mac_addr), secy->sci.port_id);
            for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                if (secy->tx_sc.sa[an] == NULL || !secy->tx_sc.sa[an]->in_use) {
                    continue;
                } else {
                    pr(" Tx an:%u in use (record:%d)\n", an, secy->tx_sc.sa[an]->record);
                }
            }

            for (sc = 0; sc < max_sc_rx; sc++) {
                if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
                    continue;
                }
                pr("  Rx SC SCI: %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx - %d\n",
                   MACADDRESS_ARG(secy->rx_sc[sc]->sci.mac_addr), secy->rx_sc[sc]->sci.port_id);
                for (an = 0; an < VTSS_MACSEC_SA_PER_SC_MAX; an++) {
                    if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
                        continue;
                    } else {
                        pr("    an:%u, in use (record:%d)\n", an, secy->rx_sc[sc]->sa[an]->record);
                    }
                }
            }
        }
    }
    for (i = 0; i < max_sa_rx; i++) {
        if (vtss_state->macsec_conf[port_no].tx_sa[i].in_use) {
            pr("Tx Record in use:%d\n", vtss_state->macsec_conf[port_no].tx_sa[i].record);
        }
        if (vtss_state->macsec_conf[port_no].rx_sa[i].in_use) {
            pr("Rx Record in use:%d\n", vtss_state->macsec_conf[port_no].rx_sa[i].record);
        }
    }
    return VTSS_RC_OK;
}



// Function for printing debug infomation
vtss_rc vtss_debug_print_macsec(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t *const info)
{
    vtss_port_no_t port_no;
    u32 i, value, val2;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_MACSEC)) {
        return VTSS_RC_OK;
    }



    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no]) {
            continue;
        }

        pr("\n****************************************** Port:%-2u ******************************************\n", port_no);

        if (!is_macsec_capable(vtss_state, port_no)) {
            pr("No MACSEC support\n");
            continue;
        }


        VTSS_N("info->clear:%u", info->clear);
        if (info->clear) {
            pr("Clearing MACSEC counters for port:%u\n", port_no);
            VTSS_RC(vtss_macsec_counters_clear_priv(vtss_state, port_no));

            pr("Clearing MACSEC debug counters for port:%u\n", port_no);
            VTSS_RC(dbg_counter_clr(vtss_state, port_no));

            continue;
        }


        VTSS_RC(vtss_debug_print_macsec_counters(vtss_state, pr, info, port_no));
        VTSS_RC(vtss_debug_print_macsec_conf(vtss_state, pr, info, port_no));

        if (info->full) {
            vtss_debug_print_macsec_vtss_state(vtss_state, pr, port_no);

            VTSS_RC(vtss_debug_print_macsec_rc_dbg_counters(vtss_state, pr, info, port_no));

            if (!vtss_state->macsec_conf[port_no].glb.init.enable) {
                pr("\nMacSec not enabled - Skipping registers printout\n");
                continue;
            }

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x802, &value));
            VTSS_RC(csr_wr(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x802, 0xFFFFFFFF));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x802, &val2));
            VTSS_RC(csr_wr(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x802, 0xFFFFFFFF));
            pr("                           INGRESS          EGRESS\n");
            vtss_macsec_debug_print_sticky_dbg(pr, "DROP_CLASS_STICKY", value, val2, 0);
            vtss_macsec_debug_print_sticky_dbg(pr, "DROP_PP_STICKY", value, val2, 1);
            vtss_macsec_debug_print_sticky_dbg(pr, "DROP_MTU_STICKY", value, val2, 2);
            vtss_macsec_debug_print_sticky_dbg(pr, "ENG_IRQ_STICKY", value, val2, 3);
            vtss_macsec_debug_print_sticky_dbg(pr, "DROP_IRQ_STICKY", value, val2, 4);
            vtss_macsec_debug_print_sticky_dbg(pr, "FIFO_OVERFLOW_STICKY", value, val2, 5);
            vtss_macsec_debug_print_sticky_dbg(pr, "SA_STORE_RAM_ERROR_STICKY", value, val2, 6);
            vtss_macsec_debug_print_sticky_dbg(pr, "STAT_RAM_ERROR_STICKY", value, val2, 7);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, 0x1f08, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f08, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "SA_MATCH_SA_HIT", value, val2, 23, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "SA_MATCH_SA_NR", value, val2, 16, 7, 0);
            vtss_macsec_debug_print_field_dbg(pr, "SA_MATCH_SOURCE_PORT", value, val2, 24, 2, 0);
            vtss_macsec_debug_print_field_dbg(pr, "SA_MATCH_MACSEC_CLASS", value, val2, 26, 2, 0);
            vtss_macsec_debug_print_field_dbg(pr, "SA_MATCH_CONTROL_PKT", value, val2, 28, 1, 0);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f10, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f10, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "SA Match raw 31_to_0", value, val2, 0, 31, 1);


            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, 0x1f11, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f11, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "SA Match raw 63_to_32", value, val2, 0, 31, 1);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, 0x1f20, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f20, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_PARSED_ETHERTYPE", value, val2, 0, 16, 1);
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_PARSED_VLAN", value, val2, 16, 12, 0);
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_PARSED_UP", value, val2, 28, 3, 0);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, 0x1f21, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f21, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_VALID", value, val2, 0, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_QINIQ_FOUND", value, val2, 1, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_STAG_VALID", value, val2, 2, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_QTAG_VALID", value, val2, 3, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_LPIDLE_PKT", value, val2, 4, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_ONE_WORD_PKT", value, val2, 5, 1, 0);


            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f22, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f22, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_PARSED_VLAN_INNER", value, val2, 0, 12, 0);
            vtss_macsec_debug_print_field_dbg(pr, "VLAN_PARSED_UP_INNER", value, val2, 12, 3, 0);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f00, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f00, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "CP_MATCH_STATE", value, val2, 0, 31, 1);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f40, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f40, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_MAC_DA_LO", value, val2, 0, 31, 1);
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f41, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f41, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_MAC_DA_HI", value, val2, 0, 16, 1);
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_ETYPE", value, val2, 16, 16, 1);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f42, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f42, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_MAC_SA_LO", value, val2, 0, 31, 1);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f43, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f43, &value));
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_MAC_SA_HI", value, val2, 0, 31, 1);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f44, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f44, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_SECTAG_LO", value, val2, 0, 31, 1);
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f45, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f45, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_SECTAG_HI", value, val2, 0, 31, 1);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f46, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f46, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_SCI_LO", value, val2, 0, 31, 1);
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f47, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f47, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "PARSED_SCI_HI", value, val2, 0, 31, 1);

            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f48, &value));
            VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f48, &val2));
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_TYPE (BP,DR,I,E)", value, val2, 0, 2, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_DEST_PORT (CM,R,C,U)", value, val2, 2, 2, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_DROP_ACTION", value, val2, 6, 2, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_PROTECT_FRAME", value, val2, 16, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_SA_IN_USE", value, val2, 17, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_INCLUDE_SCI", value, val2, 18, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_USE_ES", value, val2, 19, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_USE_SCB", value, val2, 20, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_TAG_BYPASS_SIZE", value, val2, 21, 2, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_CONF_OFFSET", value, val2, 24, 7, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_CONF_PROTECT", value, val2, 31, 1, 0);
            vtss_macsec_debug_print_field_dbg(pr, "FLOW_VALIDATE_FRAMES", value, val2, 19, 2, 0);

            CSR_RD(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL, &val2);
            val2 = VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_VALIDATE_FRAMES(val2);
            pr("GLOBAL_VALIDATE_FRAMES:%s\n", val2 == 0 ? "DISABLED" : val2 == 1 ? "CHECK" : "STRICT");

            for (i = 0; i < 4; i += 2) {
                VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f80 + i, &value));
                VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f80 + i, &val2));
                pr("SA %u\n", i / 2);
                vtss_macsec_debug_print_field_dbg(pr, " MAC_SMAC_MATCH_5_to_0", value, val2, 0, 6, 1);
                vtss_macsec_debug_print_field_dbg(pr, " MAC_DMAC_MATCH_5_to_0", value, val2, 6, 6, 1);
                vtss_macsec_debug_print_field_dbg(pr, " MAC_ETYPE_MATCH", value, val2, 12, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " VLAN_VLD_MATCH", value, val2, 13, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " QINQ_FOUND_MATCH", value, val2, 14, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " STAG_VLD_MATCH", value, val2, 15, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " QTAG_VLD_MATCH", value, val2, 16, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " QTAG_UP_MATCH", value, val2, 17, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " VLAN_ID_MATCH", value, val2, 18, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " SOURCE_PORT_MATCH", value, val2, 19, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " CTRL_PACKET_MATCH", value, val2, 20, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " MACSEC_TAG_MATCH", value, val2, 21, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " MACSEC_SCI_MATCH", value, val2, 23, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " TCI_AN_MATCH", value, val2, 24, 8, 1);
            }
            for (i = 0; i < 4; i += 2) {
                VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_INGR + 0x1f81 + i, &value));
                VTSS_RC(csr_rd(vtss_state, port_no, 0x1f, 1, MACSEC_EGR + 0x1f81 + i, &val2));
                pr("SA %u\n", i / 2);
                vtss_macsec_debug_print_field_dbg(pr, " VLAN_UP_INNER_MATCH", value, val2, 0, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " VLAN_ID_INNER_MATCH", value, val2, 1, 1, 0);
                vtss_macsec_debug_print_field_dbg(pr, " HDR_2B_16B_MATCH", value, val2, 2, 1, 0);
            }

            for (i = 0; i < 2; i++) {
                pr("SA %u:\n", i);
                CSR_RD(port_no, VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH(i), &val2);
                pr(" VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MISC_MATCH 0x%x\n", val2);

                CSR_RD(port_no, VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK(i), &val2);
                pr(" VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MASK 0x%x\n", val2);

                CSR_RD(port_no, VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI(i), &val2);
                pr(" VTSS_MACSEC_EGR_SA_MATCH_PARAMS_SAM_MAC_SA_MATCH_HI 0x%x\n", val2);
            }
        }
    }
    return VTSS_RC_OK;
}

#define VTSS_PHY_MS_DISP_CSR(p,d,a,v) \
                      csr_rd(vtss_state,p, 31, TRUE, a, v); \
                      pr("%-10u %-40s 0x%-10x 0x%-12x\n",p, d,a,*v) \
 
static vtss_rc vtss_macsec_dbg_ms_ctrl_reg_dump_priv(vtss_state_t *vtss_state,
                                                     const vtss_port_no_t port_no,
                                                     const vtss_debug_printf_t pr)
{
    u32             value;

    pr("\n\nMACSEC_CTL_REGS MACsec Ingress Control registers\n\n");

    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_ENA_CFG",           (u16)(0x800), &value);
    if (!(value && 1)) {
        csr_wr(vtss_state, port_no, 31, TRUE, (u16)(0x800), (value || 1));
    }
    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_CTL_CFG",           (u16)(0x801), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_STICKY",            (u16)(0x802), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_STICKY_MASK",       (u16)(0x803), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_IGR_LATENCY_CFG",   (u16)(0x804), &value);

    pr("\n\nMACSEC_CTL_REGS MACsec Egress Control registers\n\n");

    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_ENA_CFG",           (u16)(0x8800), &value);
    if (!(value && 1)) {
        csr_wr(vtss_state, port_no, 31, TRUE, (u16)(0x8800), (value || 1));
    }
    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_CTL_CFG",           (u16)(0x8801), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_STICKY",            (u16)(0x8802), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_STICKY_MASK",       (u16)(0x8803), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "MACSEC_IGR_LATENCY_CFG",   (u16)(0x8804), &value);

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_dbg_sa_ctrl_reg_dump_priv(vtss_state_t *vtss_state,
                                                     const vtss_port_no_t port_no,
                                                     const vtss_debug_printf_t pr)
{
    u32             value;

    pr("\n\nSA_MATCH_CTL_PARAMS - Ingress SA compare parameters\n\n");

    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_ENABLE1",    (u16)(0x1800), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_ENABLE2",    (u16)(0x1801), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_TOGGLE1",    (u16)(0x1804), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_TOGGLE2",    (u16)(0x1805), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_SET1",       (u16)(0x1808), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_SET2",       (u16)(0x1809), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_CLEAR1",     (u16)(0x180C), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_CLEAR2",     (u16)(0x180D), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_IN_FLIGHT",        (u16)(0x1810), &value);

    pr("\n\nSA_MATCH_CTL_PARAMS - Egress SA compare parameters\n\n");

    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_ENABLE1",    (u16)(0x9800), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_ENABLE2",    (u16)(0x9801), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_TOGGLE1",    (u16)(0x9804), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_TOGGLE2",    (u16)(0x9805), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_SET1",       (u16)(0x9808), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_SET2",       (u16)(0x9809), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_CLEAR1",     (u16)(0x980C), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_ENTRY_CLEAR2",     (u16)(0x980D), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_IN_FLIGHT",        (u16)(0x9810), &value);

    return VTSS_RC_OK;
}


static vtss_rc vtss_macsec_dbg_ctrl_pkt_class_reg_dump_priv(vtss_state_t *vtss_state,
                                                            const vtss_port_no_t port_no,
                                                            const vtss_debug_printf_t pr)
{
    u16             i;
    u32             value;

    pr("\n\nIngress CTL_PACKET_CLASS_PARAMS - Control packet classification parameters.\n\n");
    for (i = 0; i < 10; i++) {
        VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_MATCH",  (u16)(0x1E00 + (2 * i)), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_ET_MATCH",  (u16)(0x1E01 + (2 * i)), &value);
    }

    for (i = 0; i < 8; i++) {
        VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_ET_MATCH",  (u16)(0x1E14 + i ), &value);
    }
    pr("\n\nEgress CTL_PACKET_CLASS_PARAMS - Control packet classification parameters.\n\n");
    for (i = 0; i < 10; i++) {
        VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_MATCH",  (u16)(0x9E00 + (2 * i)), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_ET_MATCH",  (u16)(0x9E01 + (2 * i)), &value);
    }

    for (i = 0; i < 8; i++) {
        VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_ET_MATCH",  (u16)(0x9E14 + i ), &value);
    }
    return VTSS_RC_OK;
}
static vtss_rc vtss_macsec_dbg_sa_flow_ctrl_reg_dump_priv(vtss_state_t *vtss_state,
                                                          const vtss_port_no_t port_no,
                                                          const vtss_debug_printf_t pr)
{
    u16             i;
    u32             value;
    u8   no_entries = 0;
    BOOL phy10g = FALSE;
    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
    if (phy10g) {
        no_entries = VTSS_MACSEC_10G_MAX_SA;
    } else {
        no_entries = VTSS_MACSEC_1G_MAX_SA;
    }

    pr("\n\nIngress SA_MATCH_FLOW_CONTROL_PARAMS_IGR - 16/64 flow control words SA parameter set.\n\n");
    for (i = 0; i < no_entries; i++) {
        VTSS_PHY_MS_DISP_CSR(port_no, "SA MATCH FLOW CONTROL",  (u16)(0x1C00 + i), &value);
    }
    pr("\n\nEgress SA_MATCH_FLOW_CONTROL_PARAMS_IGR - 16/64 flow control words SA parameter set.\n\n");
    for (i = 0; i < no_entries; i++) {
        VTSS_PHY_MS_DISP_CSR(port_no, "SA MATCH FLOW CONTROL",  (u16)(0x9C00 + i), &value);
    }
    return VTSS_RC_OK;
}
static vtss_rc vtss_macsec_dbg_ctrl_pkt_class2_reg_dump_priv(vtss_state_t *vtss_state,
                                                             const vtss_port_no_t port_no,
                                                             const vtss_debug_printf_t pr)
{
    u32             value;

    pr("\n\nIngress CTL_PACKET_CLASS_PARAMS2 - Control packet classification parameters\n\n");

    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_START_LO",      (u16)(0x1E20), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_START_HI",      (u16)(0x1E21), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_END_LO",        (u16)(0x1E22), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_END_HI",        (u16)(0x1E23), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_44_BITS_LO",    (u16)(0x1E24), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_44_BITS_HI",    (u16)(0x1E25), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_48_BITS_LO",    (u16)(0x1E26), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_48_BITS_HI",    (u16)(0x1E27), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MATCH_MODE",           (u16)(0x1E3E), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MATCH_ENABLE",         (u16)(0x1E3F), &value);

    pr("\n\nEgress CTL_PACKET_CLASS_PARAMS2 - Control packet classification parameters\n\n");

    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_START_LO",      (u16)(0x9E20), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_START_HI",      (u16)(0x9E21), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_END_LO",        (u16)(0x9E22), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_END_HI",        (u16)(0x9E23), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_44_BITS_LO",    (u16)(0x9E24), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_44_BITS_HI",    (u16)(0x9E25), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_48_BITS_LO",    (u16)(0x9E26), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MAC_DA_48_BITS_HI",    (u16)(0x9E27), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MATCH_MODE",           (u16)(0x9E3E), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CP_MATCH_ENABLE",         (u16)(0x9E3F), &value);

    return VTSS_RC_OK;
}
static vtss_rc vtss_macsec_dbg_ctrl_frm_reg_dump_priv(vtss_state_t *vtss_state,
                                                      const vtss_port_no_t port_no,
                                                      const vtss_debug_printf_t pr)
{
    u32             value;

    pr("\n\nIngress FRAME_MATCHING_HANDLING_CTRL - Frame matching and handling control registers\n\n");

    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_CP_TAG",          (u16)(0x1E40), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_PP_TAGS",         (u16)(0x1E41), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_PP_TAGS2",        (u16)(0x1E42), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_CP_TAG2",         (u16)(0x1E43), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_NM_PARAMS",       (u16)(0x1E50), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_NM_FLOW_NCP",     (u16)(0x1E51), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_NM_FLOW_CP",      (u16)(0x1E52), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "MISC_CONTROL",        (u16)(0x1E5F), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "HDR_EXT_CTRL",        (u16)(0x1E60), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CRYPT_AUTH_CTRL",     (u16)(0x1E61), &value);

    pr("\n\nEgress FRAME_MATCHING_HANDLING_CTRL - Frame matching and handling control registers\n\n");

    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_CP_TAG",          (u16)(0x9E40), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_PP_TAGS",         (u16)(0x9E41), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_PP_TAGS2",        (u16)(0x9E42), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_CP_TAG2",         (u16)(0x9E43), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_NM_PARAMS",       (u16)(0x9E50), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_NM_FLOW_NCP",     (u16)(0x9E51), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "SAM_NM_FLOW_CP",      (u16)(0x9E52), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "MISC_CONTROL",        (u16)(0x9E5F), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "HDR_EXT_CTRL",        (u16)(0x9E60), &value);
    VTSS_PHY_MS_DISP_CSR(port_no, "CRYPT_AUTH_CTRL",     (u16)(0x9E61), &value);

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_dbg_sa_reg_dump_priv(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const vtss_debug_printf_t pr)
{
    u16  i;
    u32  value;
    u8   no_entries = 0;
    BOOL phy10g = FALSE;
    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
    if (phy10g) {
        no_entries = VTSS_MACSEC_10G_MAX_SA;
    } else {
        no_entries = VTSS_MACSEC_1G_MAX_SA;
    }
    pr("\n\nSA: Ingress SA Match Params\n\n");

    for (i = 0; i < no_entries; i++) {
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MAC_SA_MATCH_LO",  (u16)(0x1000 + (0x10 * i)), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MAC_SA_MATCH_HI",  (u16)(0x1000 + (0x10 * i) + 1), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MAC_DA_MATCH_LO",  (u16)(0x1000 + (0x10 * i) + 2), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MAC_DA_MATCH_HI",  (u16)(0x1000 + (0x10 * i) + 3), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MISC_MATCH",       (u16)(0x1000 + (0x10 * i) + 4), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_SCI_MATCH_LO",     (u16)(0x1000 + (0x10 * i) + 5), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_SCI_MATCH_HI",     (u16)(0x1000 + (0x10 * i) + 6), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MASK",             (u16)(0x1000 + (0x10 * i) + 7), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_EXT_MATCH",        (u16)(0x1000 + (0x10 * i) + 8), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_HDR_BYPASS_MATCH1", (u16)(0x1000 + (0x10 * i) + 9), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_HDR_BYPASS_MATCH2", (u16)(0x1000 + (0x10 * i) + 0xA), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_HDR_BYPASS_MASK1", (u16)(0x1000 + (0x10 * i) + 0xB), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_HDR_BYPASS_MASK2", (u16)(0x1000 + (0x10 * i) + 0xC), &value);
    }

    pr("\n\nSA: Egress SA Match Params\n\n");

    for (i = 0; i < no_entries; i++) {
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MAC_SA_MATCH_LO",  (u16)(0x9000 + (0x10 * i)), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MAC_SA_MATCH_HI",  (u16)(0x9000 + (0x10 * i) + 1), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MAC_DA_MATCH_LO",  (u16)(0x9000 + (0x10 * i) + 2), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MAC_DA_MATCH_HI",  (u16)(0x9000 + (0x10 * i) + 3), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MISC_MATCH",       (u16)(0x9000 + (0x10 * i) + 4), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_SCI_MATCH_LO",     (u16)(0x9000 + (0x10 * i) + 5), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_SCI_MATCH_HI",     (u16)(0x9000 + (0x10 * i) + 6), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_MASK",             (u16)(0x9000 + (0x10 * i) + 7), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_EXT_MATCH",        (u16)(0x9000 + (0x10 * i) + 8), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_HDR_BYPASS_MATCH1", (u16)(0x9000 + (0x10 * i) + 9), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_HDR_BYPASS_MATCH2", (u16)(0x9000 + (0x10 * i) + 0xA), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_HDR_BYPASS_MASK1", (u16)(0x9000 + (0x10 * i) + 0xB), &value);
        VTSS_PHY_MS_DISP_CSR(port_no, "SAM_HDR_BYPASS_MASK2", (u16)(0x9000 + (0x10 * i) + 0xC), &value);
    }
    return VTSS_RC_OK;
}
static vtss_rc vtss_macsec_dbg_xform_reg_dump_priv(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t port_no,
                                                   const vtss_debug_printf_t pr)
{
    u16             i, j;
    u32             value1, value2, value3, value4;
    u16             baseaddr, addr;
    u8              rec_size = 0, reg_num;
    u8   no_entries = 0;
    BOOL phy10g = FALSE;
    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
    if (phy10g) {
        no_entries = VTSS_MACSEC_10G_MAX_SA;
    } else {
        no_entries = VTSS_MACSEC_1G_MAX_SA;
    }
    pr("\n\nIngress XFORM_RECORD_REGS - Transform context records\n\n");
    CSR_RD(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL, &value1);
    rec_size = VTSS_X_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE(value1);
    reg_num = (rec_size == 1) ? 20 : ((rec_size == 2) ? 24 : 16);

    for (i = 0; i < no_entries; i++) {
        pr("Ingress XFORM Record -%u\n", (u32)(i + 1));
        baseaddr = (0x20 * i);
        for (j = 0; j < reg_num; j = j + 4) {
            addr = baseaddr + j;
            csr_rd(vtss_state, port_no, 31, TRUE, (u16)(addr), &value1);
            csr_rd(vtss_state, port_no, 31, TRUE, (u16)(addr + 1), &value2);
            csr_rd(vtss_state, port_no, 31, TRUE, (u16)(addr + 2), &value3);
            csr_rd(vtss_state, port_no, 31, TRUE, (u16)(addr + 3), &value4);
            pr("[ \t0x%-6x - 0x%-6x ] 0x%-12x  0x%-12x  0x%-12x  0x%-12x \n", addr, addr + 3, value1, value2, value3, value4);
        }
    }
    pr("\n\nEgress XFORM_RECORD_REGS - Transform context records\n\n");
    CSR_RD(port_no, VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL, &value1);
    rec_size = VTSS_X_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_MISC_CONTROL_XFORM_REC_SIZE(value1);
    reg_num = (rec_size == 1) ? 20 : ((rec_size == 2) ? 24 : 16);

    for (i = 0; i < no_entries; i++) {
        pr("Egress XFORM Record -%u\n", (u32)(i + 1));
        baseaddr = 0x8000 + (0x20 * i);
        for (j = 0; j < reg_num; j = j + 4) {
            addr = baseaddr + j;
            csr_rd(vtss_state, port_no, 31, TRUE, (u16)(addr), &value1);
            csr_rd(vtss_state, port_no, 31, TRUE, (u16)(addr + 1), &value2);
            csr_rd(vtss_state, port_no, 31, TRUE, (u16)(addr + 2), &value3);
            csr_rd(vtss_state, port_no, 31, TRUE, (u16)(addr + 3), &value4);
            pr("[ \t0x%-6x - 0x%-6x ] 0x%-12x  0x%-12x  0x%-12x  0x%-12x \n", addr, addr + 3, value1, value2, value3, value4);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_dbg_reg_dump_priv(vtss_state_t *vtss_state,
                                             const vtss_port_no_t port_no,
                                             const vtss_debug_printf_t pr)
{

    vtss_macsec_dbg_ms_ctrl_reg_dump_priv(vtss_state, port_no, pr);
    vtss_macsec_dbg_sa_ctrl_reg_dump_priv(vtss_state, port_no, pr);
    vtss_macsec_dbg_sa_flow_ctrl_reg_dump_priv(vtss_state, port_no, pr);
    vtss_macsec_dbg_ctrl_pkt_class_reg_dump_priv(vtss_state, port_no, pr);
    vtss_macsec_dbg_ctrl_pkt_class2_reg_dump_priv(vtss_state, port_no, pr);
    vtss_macsec_dbg_ctrl_frm_reg_dump_priv(vtss_state, port_no, pr);
    vtss_macsec_dbg_sa_reg_dump_priv(vtss_state, port_no, pr);
    vtss_macsec_dbg_xform_reg_dump_priv(vtss_state, port_no, pr);

    return VTSS_RC_OK;
}

static vtss_rc vtss_macsec_dbg_update_seq_set_priv(vtss_state_t             *vtss_state,
                                                   const u32                secy_id,
                                                   const vtss_macsec_port_t port,
                                                   const vtss_macsec_sci_t  *const sci,
                                                   u16                      an,
                                                   BOOL                     egr,
                                                   BOOL                     disable)
{
    vtss_macsec_internal_secy_t *secy = &vtss_state->macsec_conf[port.port_no].secy[secy_id];
    u32 seq_update;
    u32 record;
    u32 sc;

    VTSS_D("Port:%u, Egr:%d, AN:%d, Disable:%d", port.port_no, egr, an, disable);
    VTSS_RC(sc_from_sci_get(vtss_state, port.port_no, secy, sci, &sc));

    if (egr) {
        record = secy->tx_sc.sa[an]->record;
        CSR_RD(port.port_no, VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA0(record), &seq_update);
        if (disable)
            seq_update = seq_update & ~(1 << 13);
        else
            seq_update |= (1 << 13);
        CSR_WARM_WR(port.port_no, VTSS_MACSEC_EGR_XFORM_RECORD_REGS_XFORM_REC_DATA0(record), seq_update);
    } else {
        record = secy->rx_sc[sc]->sa[an]->record;
        CSR_RD(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA0(record), &seq_update);
        if (disable)
            seq_update = seq_update & ~(1 << 13);
        else
            seq_update |= (1 << 13);
        CSR_WARM_WR(port.port_no, VTSS_MACSEC_INGR_XFORM_RECORD_REGS_XFORM_REC_DATA0(record), seq_update);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_macsec_dbg_reg_dump(const vtss_inst_t             inst,
                                 const vtss_port_no_t          port_no,
                                 const vtss_debug_printf_t pr)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_dbg_reg_dump_priv(vtss_state, port_no, pr);
    }
    VTSS_EXIT();
    return rc;
}


#define CSR_RD_TST(p, txt, io_reg, value)     \
    {   \
       vtss_rc __rc = _csr_rd(vtss_state, p, io_reg, value); \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    } \
    pr("%s                   [0x%x] : 0x%x\n", txt,io_reg->addr, *value); \
 
static vtss_rc vtss_macsec_dbg_fcb_block_reg_dump_priv(vtss_state_t *vtss_state,
                                                       const vtss_port_no_t port_no,
                                                       const vtss_debug_printf_t pr)
{
    u32 value;

    pr("Host MAC Reg Dump : Port No: %d\n\n", port_no);

    CSR_RD_TST(port_no, "FC_ENA_CFG                         ", VTSS_IOREG(0x03, 1, 0xf000), &value);
    CSR_RD_TST(port_no, "FC_MODE_CFG                        ", VTSS_IOREG(0x03, 1, 0xf001), &value);
    CSR_RD_TST(port_no, "PPM_RATE_ADAPT_THRESH_CFG          ", VTSS_IOREG(0x03, 1, 0xf002), &value);
    CSR_RD_TST(port_no, "TX_CTRL_QUEUE_CFG                  ", VTSS_IOREG(0x03, 1, 0xf003), &value);
    CSR_RD_TST(port_no, "TX_DATA_QUEUE_CFG                  ", VTSS_IOREG(0x03, 1, 0xf004), &value);
    CSR_RD_TST(port_no, "RX_DATA_QUEUE_CFG                  ", VTSS_IOREG(0x03, 1, 0xf005), &value);
    CSR_RD_TST(port_no, "TX_BUFF_XON_XOFF_THRESH_CFG        ", VTSS_IOREG(0x03, 1, 0xf006), &value);
    CSR_RD_TST(port_no, "FC_READ_THRESH_CFG                 ", VTSS_IOREG(0x03, 1, 0xf007), &value);
    CSR_RD_TST(port_no, "TX_FRM_GAP_COMP                    ", VTSS_IOREG(0x03, 1, 0xf008), &value);

    CSR_RD_TST(port_no, "STATUS STICKY                      ", VTSS_IOREG(0x03, 1, 0xf009), &value);
    CSR_RD_TST(port_no, "STICKY_MASK                        ", VTSS_IOREG(0x03, 1, 0xf00A), &value);
    CSR_RD_TST(port_no, "TX_CTRL_QUEUE_OVERFLOW_DROP_CNT    ", VTSS_IOREG(0x03, 1, 0xf00B), &value);
    CSR_RD_TST(port_no, "TX_CTRL_QUEUE_UNDERFLOW_DROP_CNT   ", VTSS_IOREG(0x03, 1, 0xf00C), &value);
    CSR_RD_TST(port_no, "TX_CTRL_UNCORRECTED_FRM_DROP_CNT   ", VTSS_IOREG(0x03, 1, 0xf00D), &value);
    CSR_RD_TST(port_no, "TX_DATA_QUEUE_OVERFLOW_DROP_CNT    ", VTSS_IOREG(0x03, 1, 0xf00E), &value);
    CSR_RD_TST(port_no, "TX_DATA_QUEUE_UNDERFLOW_DROP_CNT   ", VTSS_IOREG(0x03, 1, 0xf00F), &value);
    CSR_RD_TST(port_no, "TX_DATA_UNCORRECTED_FRM_DROP_CNT   ", VTSS_IOREG(0x03, 1, 0xf010), &value);
    CSR_RD_TST(port_no, "RX_OVERFLOW_DROP_CNT               ", VTSS_IOREG(0x03, 1, 0xf011), &value);
    CSR_RD_TST(port_no, "RX_UNDERFLOW_DROP_CNT              ", VTSS_IOREG(0x03, 1, 0xf012), &value);
    CSR_RD_TST(port_no, "RX_UNCORRECTED_FRM_DROP_CNT        ", VTSS_IOREG(0x03, 1, 0xf013), &value);

    CSR_RD_TST(port_no, "EEE_CTRL_CFG                       ", VTSS_IOREG(0x03, 1, 0xf014), &value);
    CSR_RD_TST(port_no, "AGE_TIMER_CFG                      ", VTSS_IOREG(0x03, 1, 0xf015), &value);
    CSR_RD_TST(port_no, "WAKE_TIMER_CFG                     ", VTSS_IOREG(0x03, 1, 0xf016), &value);
    CSR_RD_TST(port_no, "HOLD_TIMER_CFG                     ", VTSS_IOREG(0x03, 1, 0xf017), &value);
    CSR_RD_TST(port_no, "SEC_TIMER_CFG                      ", VTSS_IOREG(0x03, 1, 0xf018), &value);
    CSR_RD_TST(port_no, "EEE_Q_HIGH_THRESH_CFG              ", VTSS_IOREG(0x03, 1, 0xf019), &value);
    CSR_RD_TST(port_no, "EEE_CTRL_STATUS_N_STICKY_REG       ", VTSS_IOREG(0x03, 1, 0xf01a), &value);
    CSR_RD_TST(port_no, "EEE_CTRL_STICKY_MASK_REG           ", VTSS_IOREG(0x03, 1, 0xf01b), &value);

    return VTSS_RC_OK;
}

vtss_rc vtss_macsec_dbg_fcb_block_reg_dump(const vtss_inst_t    inst,
                                           const vtss_port_no_t port_no,
                                           const vtss_debug_printf_t pr)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_I("MAC Block Register  Dump Port_no: %u\n", port_no);

    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_dbg_fcb_block_reg_dump_priv(vtss_state, port_no, pr);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_macsec_dbg_frm_match_handling_ctrl_reg_dump(const vtss_inst_t             inst,
                                                         const vtss_port_no_t          port_no,
                                                         const vtss_debug_printf_t     pr)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_dbg_ctrl_frm_reg_dump_priv(vtss_state, port_no, pr);
    }
    VTSS_EXIT();
    return rc;
}

#ifdef VTSS_MACSEC_FIFO_OVERFLOW_WORKAROUND
static vtss_rc vtss_macsec_dbg_reconfig_priv(vtss_state_t         *vtss_state,
                                             const vtss_port_no_t port_no)
{
    vtss_rc rc = VTSS_RC_ERROR;
    BOOL phy10g;
    u8 value;
    vtss_port_speed_t speed = VTSS_SPEED_UNDEFINED;
#ifdef VTSS_CHIP_CU_PHY
    vtss_phy_port_state_t *ps      = &vtss_state->phy_state[port_no];
    vtss_port_status_t    *status  = &ps->status;
    vtss_phy_conf_t       *conf    = &ps->setup;
#endif

    VTSS_RC(phy_type_get(vtss_state, port_no, &phy10g));
    // From the register description
    // * 000: 10G
    // * 001: 10G_1G
    // * 101: 1G
    // * 110: 1G_100M
    // * 111: 1G_10M
    // * others: illegal
    value = 0; // Default to 10g
#ifdef VTSS_CHIP_10G_PHY
    if (phy10g) {
        if (vtss_state->phy_10g_state[port_no].mode.oper_mode == VTSS_PHY_1G_MODE) {
            value = 1; // * 001: 10G_1G
        } else {
            // Every other modes are 10G modes.
            value = 0; // * 000: 10G
        }
    } else {
#endif
#ifdef VTSS_CHIP_CU_PHY
        // Determine speed.
        if (conf->mode == VTSS_PHY_MODE_ANEG) {
            speed = status->speed;
        } else {
            // Forced speed
            speed = conf->forced.speed;
        }

        // Determine register value according to the description of the register
        switch (speed) {
        case VTSS_SPEED_1G:
            value = 0x5;     // * 101: 1G
            break;

        case VTSS_SPEED_100M:
            value = 0x6;     // * 110: 1G_100M
            break;

        case VTSS_SPEED_10M:
            value = 0x7;     // * 111: 1G_10M
            break;

        default:
            // This is completely OK, because the API returns undefined speed if the port is down.
            VTSS_I("Speed is undefined");
            return VTSS_RC_OK;
        }

        VTSS_D("port_no:%d, Speed mode:0x%X", port_no, value);
#endif
#ifdef VTSS_CHIP_10G_PHY
    }
#endif

    /* Ingress */
    CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST |
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA);

    /* Egress */
    CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_SW_RST |
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA);
    VTSS_D("MACsec Block Enable SW_RESET on Port:%u", port_no);

    /* Enable Ingress MacSec block */
    CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                VTSS_F_MACSEC_INGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(phy10g ? 0 : value));

    /* Enable Egress MacSec block */
    CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG,
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_CLK_ENA |
                VTSS_F_MACSEC_EGR_MACSEC_CTL_REGS_MACSEC_ENA_CFG_MACSEC_SPEED_MODE(phy10g ? 0 : value));
    VTSS_D("MACsec Block Out of SW_RESET on Port:%u", port_no);
    vtss_state->macsec_conf[port_no].glb.spd_change_macsec_recfg = TRUE;
    VTSS_RC(vtss_macsec_init_set_priv(vtss_state, port_no, &vtss_state->macsec_conf[port_no].glb.init));

    /* Re-Configure macsec using private functions  */
    VTSS_D("Port:%d, Re-config MACsec Block", port_no);
    if ((rc = vtss_macsec_reconfigure(vtss_state, port_no)) != VTSS_RC_OK) {
        VTSS_E("vtss_macsec_reconfig port(%d) return rc(0x%04X)", port_no, rc);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_macsec_dbg_reconfig(const vtss_inst_t    inst,
                                 const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_macsec_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_macsec_dbg_reconfig_priv(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_MACSEC_FIFO_OVERFLOW_WORKAROUND */
vtss_rc vtss_macsec_drop_all_traffic_priv(vtss_state_t *vtss_state,
                                          const vtss_port_no_t port_no)
{
#if defined(VTSS_CHIP_CU_PHY)
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t    phy_id = ps->type;
    vtss_phy_conf_t conf = vtss_state->phy_state[port_no].setup;

    BOOL is_phy_1g  =  (phy_id.part_number != VTSS_PHY_TYPE_NONE);

    if (is_phy_1g) {
        if (conf.mode == VTSS_PHY_MODE_POWER_DOWN) {
            VTSS_I("Phy %u is powered down, i.e. the MacSec block is not accessible", port_no);
            return VTSS_RC_OK;
        }
    }

    CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP, 0x81818181);
    CSR_COLD_WR(port_no,VTSS_MACSEC_INGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP , 0x81818181);

    CSR_COLD_WR(port_no,VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_NCP , 0x81818181);
    CSR_COLD_WR(port_no,VTSS_MACSEC_EGR_FRAME_MATCHING_HANDLING_CTRL_SAM_NM_FLOW_CP , 0x81818181);

    CSR_COLD_WR(port_no, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR1, 0xFFFFFFFF);

    CSR_COLD_WR(port_no, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_CLEAR1, 0xFFFFFFFF);
#endif
    return VTSS_RC_OK;
}

#if defined(VTSS_CHIP_CU_PHY)
vtss_rc vtss_macsec_store_sa(vtss_state_t *vtss_state,
                             const vtss_port_no_t port_no, BOOL store) {
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t    phy_id = ps->type;
    vtss_phy_conf_t conf = vtss_state->phy_state[port_no].setup;
    u32                value;
    u16                reg;
    BOOL is_phy_1g  =  (phy_id.part_number != VTSS_PHY_TYPE_NONE);

    if (is_phy_1g) {
        if (conf.mode == VTSS_PHY_MODE_POWER_DOWN) {
            VTSS_I("Phy %u is powered down, i.e. the MacSec block is not accessible", port_no);
            return VTSS_RC_OK;
        }
    }
    if (store) {
        CSR_RD(port_no, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1, &value);
        reg = (u16)value;
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE, VTSS_PHY_PAGE_EXTENDED);
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_RESERVED_1_WS, reg);
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE, VTSS_PHY_PAGE_STANDARD );

        CSR_RD(port_no, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1, &value);
        reg = (u16)value;
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE, VTSS_PHY_PAGE_EXTENDED);
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_RESERVED_2_WS, reg);
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE, VTSS_PHY_PAGE_STANDARD );
    } else {
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE, VTSS_PHY_PAGE_EXTENDED);
        PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_RESERVED_1_WS, &reg);
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE, VTSS_PHY_PAGE_STANDARD );
        value = (u32)reg;
        CSR_WR(port_no, VTSS_MACSEC_EGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1, value);

        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE, VTSS_PHY_PAGE_EXTENDED);
        PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_RESERVED_2_WS, &reg);
        PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE, VTSS_PHY_PAGE_STANDARD );
        value = (u32)reg;
        CSR_WR(port_no, VTSS_MACSEC_INGR_SA_MATCH_CTL_PARAMS_SAM_ENTRY_ENABLE1, value);
    }
    return VTSS_RC_OK;
}
#endif
vtss_rc vtss_macsec_dbg_update_seq_set(const vtss_inst_t        inst,
                                       const vtss_macsec_port_t port,
                                       const vtss_macsec_sci_t  *const sci,
                                       u16                      an,
                                       BOOL                     egr,
                                       const BOOL               disable)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 secy_id = 0;

    VTSS_I(MPORT_SCI_AN_FMT, MPORT_SCI_AN_ARG(port, *sci, an));
    VTSS_ENTER();
    if ((rc = vtss_macsec_port_check(inst, &vtss_state, port, 0, &secy_id)) == VTSS_RC_OK) {
        rc = vtss_macsec_dbg_update_seq_set_priv(vtss_state, secy_id, port, sci, an, egr, disable);
    }
    VTSS_EXIT();
    return rc;
}




// ***************************************************************************
//
//  End of file.
//
// ***************************************************************************

#endif /*VTSS_FEATURE_MACSEC */
