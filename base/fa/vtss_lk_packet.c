// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PACKET
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_LAIKA)
#include "vtss_lk_packet.h"

#define PIE_BD_PTR_SZ 24
#define PIE_BD_MASK   0x00FFFFFF
#define MIN_FLEN      64

#define SRX_PIE_CTRL_BIT_SRX_PIE_REMOVE_ROFH_Msk  0x00000001
#define SRX_PIE_CTRL_BIT_SRX_PIE_REMOVE_FCS_Msk   0x00000002
#define SRX_PIE_CTRL_BIT_SRX_PIE_PREPEND_ROFH_Msk 0x00000004
#define SRX_PIE_CTRL_BIT_SRX_PIE_CH_EN_Msk        0x00000008

#define STX_PIE_ABORT_MISS_TLAST_Msk      0x00000004
#define STX_PIE_ABORT_1CC_PKT_ERR_Msk     0x00000010
#define STX_PIE_ABORT_WRONG_TKEEP_Msk     0x00000020
#define STX_PIE_SIZE_CTRL_ADJT_FH_Msk     0x00001000
#define STX_PIE_SIZE_CTRL_ADJT_REM_FH_Msk 0x00002000

#define STX_PIE_INS_TOFH_Msk              0x00000002
#define STX_PIE_SRC_TOFH_Msk              0x00000004
#define STX_PIE_INS_VLAN_Msk              0x00000008
#define STX_PIE_SRC_VLAN_Msk              0x00000010
#define STX_PIE_INS_FCS_Msk               0x00000020
#define STX_PIE_SRC_PRIO_Msk              0x00000040
#define STX_PIE_SIZE_CTRL_USIZE_CH_EN_Msk 0x00000200
#define STX_PIE_SIZE_CTRL_OSIZE_CH_EN_Msk 0x00000400

#define STX_PIE_CH_EN_Msk             0x00000001
#define PIE_GEN_CFG_BIT_CHN_PI_EN_Msk 0x00000001
#define PIE_GEN_CFG_BIT_CHN_PE_EN_Msk 0x00010000

#define SRX_TAXI_ERROR_CH_CTRL_PIE_BIT_SRX_PIE_ABORT_MISS_EOF_Msk 0x00000001
#define SRX_TAXI_ERROR_CH_CTRL_PIE_BIT_SRX_PIE_ABORT_WRONG_UB_Msk 0x00000002

#define VTSS_TO_PIE   (0x04200000)
#define PIE_CHANNEL   0
#define PIE_REG(addr) __REG(VTSS_TO_PIE >> 2, addr >> 2, PIE_CHANNEL, 0x1000 >> 2, 0, 0, 32, 1)

#define PI_CB_DESC_CFG0 (0x000000c8)
#define PI_CB_DESC_CFG1 (0x000000cc)
#define PI_CB_DESC_CFG2 (0x000000d0)
#define PI_CB_DESC_CFG3 (0x000000d4)
#define PI_CB_DESC_CFG4 (0x000000d8)
#define PI_CB_DESC_CFG5 (0x000000dc)
#define PI_CB_DESC_CFG6 (0x000000e0)
#define PI_CB_DESC_STS0 (0x000000e4)

#define PE_CB_RDESC_CFG0 (0x00000104)
#define PE_CB_RDESC_CFG1 (0x00000108)
#define PE_CB_RDESC_CFG2 (0x0000010c)
#define PE_CB_RDESC_CFG3 (0x00000110)
#define PE_CB_RDESC_CFG4 (0x00000114)
#define PE_CB_RDESC_CFG5 (0x00000118)
#define PE_CB_RDESC_CFG6 (0x0000011c)
#define PE_CB_RDESC_STS0 (0x00000120)

#define PE_CB_EDESC_CFG0 (0x00000124)
#define PE_CB_EDESC_CFG1 (0x00000128)
#define PE_CB_EDESC_CFG2 (0x00000130)
#define PE_CB_EDESC_CFG3 (0x00000134)
#define PE_CB_EDESC_CFG4 (0x00000138)
#define PE_CB_EDESC_CFG5 (0x0000013c)
#define PE_CB_EDESC_CFG6 (0x00000140)
#define PE_CB_EDESC_CFG8 (0x00000144)
#define PE_CB_EDESC_STS0 (0x00000148)

#define STX_PIE_CTRL               (0x00000040)
#define STX_AXIS_ERR_CTRL_PIE      (0x00000044)
#define SRX_PIE_CTRL               (0x00000060)
#define SRX_TAXI_ERROR_CH_CTRL_PIE (0x00000064)
#define GEN_CFG0                   (0x00000080)
#define GEN_CFG1                   (0x00000088)
#define PIE_GEN_CFG                (0x000000c0)
#define PIE_0_INT                  (0x00000a0c)
#define PIE_1_INT                  (0x00000a10)
#define PIE_2_INT                  (0x00000a14)

#define PIE_DEFAULT_RX_DESCRIPTORS 4
#define PIE_DEFAULT_TX_DESCRIPTORS 4
#define MTU                        (LMU_FRAME_MAX_SIZE + VTSS_FA_RX_IFH_SIZE) // 1518 + 36
#define P64H_PIE_BUFF_ALIGN        32
#define CEIL_ALIGN(x, m)           (((((x) - 1) / m) + 1) * m)

struct lk_pie_rx_desc_t {
    u64 memory_addr : 50;
    u64 block_len   : 14;

    u64 valid       : 1;
    u64 owner       : 1;
    u64 rsvd1       : 3;
    u64 sop         : 1;
    u64 eop         : 1;
    u64 ifh_present : 1;

    u64 rofh_present     : 1;
    u64 checksum_checked : 1;
    u64 debug_id         : 5;
    u64 rsvd2            : 1;

    u64 ofh_present       : 1;
    u64 priority          : 3;
    u64 pkt_len           : 14;
    u64 checksum          : 16;
    u64 error_present     : 1;
    u64 err_invalid_isdx  : 1;
    u64 err_checksum      : 1;
    u64 err_missing_sof   : 1;
    u64 err_missing_eof   : 1;
    u64 err_1clock_pkt    : 1;
    u64 err_wrong_unused  : 1;
    u64 err_fifo_overflow : 1;
    u64 err_pkt_oversize  : 1;
    u64 rsvd3             : 5;
};
struct lk_pie_tx_desc_t {
    u64 memory_addr           : 50;
    u64 block_len             : 14;
    u64 valid                 : 1;
    u64 sop                   : 1;
    u64 eop                   : 1;
    u64 sge                   : 6;
    u64 vlan_en               : 1;
    u64 vlan_tpid             : 3;
    u64 vlan_id               : 12;
    u64 vlan_dei              : 1;
    u64 checksum_en           : 1;
    u64 checksum_is_ipv6      : 1;
    u64 start_byte_offset     : 7;
    u64 start_checksum_insert : 7;
    u64 tofh_insert_en        : 1;
    u64 tofh_insert_isdx      : 12;
    u64 insert_prio           : 3;
    u64 remain_bits           : 6;
};
typedef struct {
    u32 abort_miss_eof : 1; ///<  Assert an abort on missing EOF packets
    u32 abort_wrong_ub : 1; ///<  Assert an abort on packets with unused bytes non-null on non-EOP
                            ///<  words
    u32 remove_rofh : 1;    ///<  Enable/Disable ROFH removal from packets destined to the PIE path
    u32 remove_fcs  : 1;    ///<  Enable/Disable FCS removal from packets destined to the PIE path
    u32 prepend_rofh : 1; ///<  Enable/Disable prepend ROFH as a standalone word only if removing ROFH
} lk_pie_chnl_rx_cfg_t;
typedef struct {
    u32 abort_miss_tlast      : 1; ///<  Assert an abort on missing EOF packets
    u32 abort_1cc_pkt_err     : 1; ///<  Assert an abort on missing EOF packets
    u32 abort_wrong_tkeep     : 1; ///<  Assert an abort on missing EOF packets
    u32 size_ctrl_adjt_fh     : 1; ///<  adjust bytes based on TOFH insertion
    u32 size_ctrl_adjt_rem_fh : 1; ///<  Adjust bytes based on FCS insertion
    u32 ins_fcs               : 1; ///<  Assert an abort on missing EOF packets
    u32 ins_tofh              : 1; ///<  Assert an abort on missing EOF packets
    u32 src_tofh              : 1; ///<  Assert an abort on missing EOF packets
    u32 ins_vlan              : 1; ///< PIE insert VLAN
    u32 src_vlan              : 1; ///<  PIE source VLAN
    u32 src_prio              : 1; ///<  priority
    u32 size_ctrl_osize_ch_en : 1; ///<  enable oversize frames
    u32 size_ctrl_usize_ch_en : 1; ///<  enable undersize frames

    u32 priority_mask; ///< PIE channel priority mapping mask
    u32 dest_mask;     ///< PIE channel destination mapping mask
} lk_pie_chnl_tx_cfg_t;

vtss_lk_pie_chnl_t *lk_get_chnl(vtss_state_t *vtss_state)
{
    return &vtss_state->packet.lk.chnls[PIE_CHANNEL];
}

static inline u64 lk_pie_bd_ptr2addr(uint32_t base, uint32_t ptr, bool base_msb)
{
    uintptr_t addr;
    base += base_msb ? 0 : 1; // If the BD ring crosses a 16MB frontier (end msb != start msb), then
                              // end's msb must be start's msb + 1
    addr = base;
    addr <<= PIE_BD_PTR_SZ;
    addr |= ptr;
    return addr;
}

static inline uint32_t lk_pie_bd_msb(u64 addr) { return addr >> PIE_BD_PTR_SZ; }

static inline bool lk_pie_bd_msb_cmp(u64 addr, uint32_t msb) { return lk_pie_bd_msb(addr) == msb; }

static inline void lk_u64_to_u32(u32 *low, u32 *high, u64 val)
{
    *low = (uintptr_t)val;
    *high = val >> 32;
}

static inline vtss_rc lk_pie_rd(vtss_state_t *vtss_state, u64 *addr, u64 reg, bool is_rx)
{
    u32  ptr;
    u32  ring_msb;
    bool base_msb;
    REG_RD(PIE_REG(reg), &ptr);
    base_msb = !VTSS_EXTRACT_BITFIELD(ptr, PIE_BD_PTR_SZ, 1);
    vtss_lk_pie_chnl_t *c = lk_get_chnl(vtss_state);
    ring_msb = is_rx ? c->pc_rx_ring_msb : c->pc_tx_ring_msb;
    *addr = lk_pie_bd_ptr2addr(ring_msb, ptr, base_msb);
    return VTSS_RC_OK;
}

static inline vtss_rc lk_pie_update(vtss_state_t *vtss_state, u64 addr, u64 reg, bool is_rx)
{
    u32                 ring_msb;
    bool                is_end;
    vtss_lk_pie_chnl_t *c = lk_get_chnl(vtss_state);
    ring_msb = is_rx ? c->pc_rx_ring_msb : c->pc_tx_ring_msb;
    is_end = !lk_pie_bd_msb_cmp(addr, ring_msb);
    REG_WR(PIE_REG(reg), (addr & PIE_BD_MASK) | VTSS_ENCODE_BITFIELD(is_end, PIE_BD_PTR_SZ, 1));
    return VTSS_RC_OK;
}

// Reads
static inline vtss_rc lk_edesc_write_ptr_read(vtss_state_t *vtss_state, u64 *addr)
{
    return lk_pie_rd(vtss_state, addr, PE_CB_EDESC_STS0, TRUE);
}
static inline vtss_rc lk_edesc_read_ptr_read(vtss_state_t *vtss_state, u64 *addr)
{
    return lk_pie_rd(vtss_state, addr, PE_CB_EDESC_CFG6, TRUE);
}
static inline vtss_rc lk_rdesc_read_ptr_read(vtss_state_t *vtss_state, u64 *addr)
{
    return lk_pie_rd(vtss_state, addr, PE_CB_RDESC_STS0, TRUE);
}
static inline vtss_rc lk_rdesc_write_ptr_read(vtss_state_t *vtss_state, u64 *addr)
{
    return lk_pie_rd(vtss_state, addr, PE_CB_RDESC_CFG6, TRUE);
}
static inline vtss_rc lk_idesc_read_ptr_read(vtss_state_t *vtss_state, u64 *addr)
{
    return lk_pie_rd(vtss_state, addr, PI_CB_DESC_STS0, FALSE);
}
static inline vtss_rc lk_idesc_write_ptr_read(vtss_state_t *vtss_state, u64 *addr)
{
    return lk_pie_rd(vtss_state, addr, PI_CB_DESC_CFG6, FALSE);
}
// Updates
static inline vtss_rc lk_edesc_read_ptr_update(vtss_state_t *vtss_state, u64 addr)
{
    return lk_pie_update(vtss_state, addr, PE_CB_EDESC_CFG6, TRUE);
}
static inline vtss_rc lk_rdesc_write_ptr_update(vtss_state_t *vtss_state, u64 addr)
{
    return lk_pie_update(vtss_state, addr, PE_CB_RDESC_CFG6, TRUE);
}
static inline vtss_rc lk_idesc_write_ptr_update(vtss_state_t *vtss_state, u64 addr)
{
    return lk_pie_update(vtss_state, addr, PI_CB_DESC_CFG6, FALSE);
}

static inline vtss_rc lk_pi_desc_cfg(vtss_state_t *vtss_state, u64 start, u64 end)
{
    u32 low, high;
    lk_u64_to_u32(&low, &high, start);
    REG_WR(PIE_REG(PI_CB_DESC_CFG0), low);
    REG_WR(PIE_REG(PI_CB_DESC_CFG1), high);
    lk_u64_to_u32(&low, &high, end);
    REG_WR(PIE_REG(PI_CB_DESC_CFG2), low);
    REG_WR(PIE_REG(PI_CB_DESC_CFG3), high);
    return VTSS_RC_OK;
}

static inline vtss_rc lk_pe_desc_cfg(vtss_state_t *vtss_state, u64 start, u64 end)
{
    u32 low, high;
    lk_u64_to_u32(&low, &high, start);
    REG_WR(PIE_REG(PE_CB_RDESC_CFG0), low);
    REG_WR(PIE_REG(PE_CB_RDESC_CFG1), high);
    REG_WR(PIE_REG(PE_CB_EDESC_CFG0), low);
    REG_WR(PIE_REG(PE_CB_EDESC_CFG1), high);
    lk_u64_to_u32(&low, &high, end);
    REG_WR(PIE_REG(PE_CB_RDESC_CFG2), low);
    REG_WR(PIE_REG(PE_CB_RDESC_CFG3), high);
    REG_WR(PIE_REG(PE_CB_EDESC_CFG2), low);
    REG_WR(PIE_REG(PE_CB_EDESC_CFG3), high);
    return VTSS_RC_OK;
}

vtss_rc lk_debug_pkt(vtss_state_t *vtss_state, lmu_ss_t *ss, const vtss_debug_info_t *const info)
{
    u64 wptr, rptr;

    pr("PIE CHANNEL %u\n", PIE_CHANNEL);
    lk_idesc_write_ptr_read(vtss_state, &wptr);
    lk_idesc_read_ptr_read(vtss_state, &rptr);
    pr("%-33s SW_WR=0x%llx HW_RD=0x%llx\n", "PI DESC", wptr, rptr);
    lk_rdesc_write_ptr_read(vtss_state, &wptr);
    lk_rdesc_read_ptr_read(vtss_state, &rptr);
    pr("%-33s SW_WR=0x%llx HW_RD=0x%llx\n", "PE RDESC", wptr, rptr);
    lk_edesc_write_ptr_read(vtss_state, &wptr);
    lk_edesc_read_ptr_read(vtss_state, &rptr);
    pr("%-33s HW_WR=0x%llx SW_RD=0x%llx\n", "PE EDESC", wptr, rptr);

    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(PIE_REG(SRX_PIE_CTRL)), "SRX_PIE_CTRL");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(PIE_REG(STX_PIE_CTRL)), "STX_PIE_CTRL");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(PIE_REG(STX_AXIS_ERR_CTRL_PIE)),
                      "STX_AXIS_ERR_CTRL_PIE");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(PIE_REG(PIE_0_INT)), "PIE_0_INT");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(PIE_REG(PIE_1_INT)), "PIE_1_INT");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(PIE_REG(PIE_2_INT)), "PIE_2_INT");
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc lk_chn_traffic_enable(vtss_state_t *vtss_state, bool enable)
{
    REG_WRM(PIE_REG(SRX_PIE_CTRL), (enable ? SRX_PIE_CTRL_BIT_SRX_PIE_CH_EN_Msk : 0),
            SRX_PIE_CTRL_BIT_SRX_PIE_CH_EN_Msk);

    REG_WRM(PIE_REG(STX_PIE_CTRL), (enable ? STX_PIE_CH_EN_Msk : 0), STX_PIE_CH_EN_Msk);

    REG_WRM(PIE_REG(PIE_GEN_CFG),
            (enable ? (PIE_GEN_CFG_BIT_CHN_PI_EN_Msk | PIE_GEN_CFG_BIT_CHN_PE_EN_Msk) : 0),
            (PIE_GEN_CFG_BIT_CHN_PI_EN_Msk | PIE_GEN_CFG_BIT_CHN_PE_EN_Msk));
    return VTSS_RC_OK;
}

vtss_rc lk_setup_rx_thresholds(vtss_state_t *vtss_state)
{
    REG_WR(PIE_REG(PE_CB_EDESC_CFG4), 0); // CHN_PE_CB_EDESC_HI_THLD
    REG_WR(PIE_REG(PE_CB_EDESC_CFG5), 1); // CHN_PE_CB_EDESC_LO_THLD
    REG_WR(PIE_REG(PE_CB_EDESC_CFG8), 1); // CHN_PE_CB_EDESC_TIMER
    return VTSS_RC_OK;
}

vtss_rc lk_setup_rx_cfg(vtss_state_t *vtss_state, const lk_pie_chnl_rx_cfg_t *cfg)
{
    u32 val;
    val = (cfg->abort_miss_eof ? SRX_TAXI_ERROR_CH_CTRL_PIE_BIT_SRX_PIE_ABORT_MISS_EOF_Msk : 0) |
          (cfg->abort_wrong_ub ? SRX_TAXI_ERROR_CH_CTRL_PIE_BIT_SRX_PIE_ABORT_WRONG_UB_Msk : 0);
    REG_WRM(PIE_REG(SRX_TAXI_ERROR_CH_CTRL_PIE), val,
            (SRX_TAXI_ERROR_CH_CTRL_PIE_BIT_SRX_PIE_ABORT_MISS_EOF_Msk |
             SRX_TAXI_ERROR_CH_CTRL_PIE_BIT_SRX_PIE_ABORT_WRONG_UB_Msk));

    val = (cfg->remove_rofh ? SRX_PIE_CTRL_BIT_SRX_PIE_REMOVE_ROFH_Msk : 0) |
          (cfg->remove_fcs ? SRX_PIE_CTRL_BIT_SRX_PIE_REMOVE_FCS_Msk : 0) |
          (cfg->prepend_rofh ? SRX_PIE_CTRL_BIT_SRX_PIE_PREPEND_ROFH_Msk : 0);
    REG_WRM(PIE_REG(SRX_PIE_CTRL), val,
            (SRX_PIE_CTRL_BIT_SRX_PIE_REMOVE_ROFH_Msk | SRX_PIE_CTRL_BIT_SRX_PIE_REMOVE_FCS_Msk |
             SRX_PIE_CTRL_BIT_SRX_PIE_PREPEND_ROFH_Msk));
    lk_setup_rx_thresholds(vtss_state);
    return VTSS_RC_OK;
}

vtss_rc lk_setup_tx_cfg(vtss_state_t *vtss_state, const lk_pie_chnl_tx_cfg_t *cfg)
{
    REG_WRM(PIE_REG(STX_AXIS_ERR_CTRL_PIE),
            (cfg->abort_miss_tlast ? STX_PIE_ABORT_MISS_TLAST_Msk : 0),
            STX_PIE_ABORT_MISS_TLAST_Msk);
    REG_WRM(PIE_REG(STX_AXIS_ERR_CTRL_PIE),
            (cfg->abort_1cc_pkt_err ? STX_PIE_ABORT_1CC_PKT_ERR_Msk : 0),
            STX_PIE_ABORT_1CC_PKT_ERR_Msk);
    REG_WRM(PIE_REG(STX_AXIS_ERR_CTRL_PIE),
            (cfg->abort_wrong_tkeep ? STX_PIE_ABORT_WRONG_TKEEP_Msk : 0),
            STX_PIE_ABORT_WRONG_TKEEP_Msk);
    REG_WRM(PIE_REG(STX_AXIS_ERR_CTRL_PIE),
            (cfg->size_ctrl_adjt_fh ? STX_PIE_SIZE_CTRL_ADJT_FH_Msk : 0),
            STX_PIE_SIZE_CTRL_ADJT_FH_Msk);
    REG_WRM(PIE_REG(STX_AXIS_ERR_CTRL_PIE),
            (cfg->size_ctrl_adjt_rem_fh ? STX_PIE_SIZE_CTRL_ADJT_REM_FH_Msk : 0),
            STX_PIE_SIZE_CTRL_ADJT_REM_FH_Msk);

    REG_WRM(PIE_REG(STX_PIE_CTRL), (cfg->ins_fcs ? STX_PIE_INS_TOFH_Msk : 0), STX_PIE_INS_TOFH_Msk);
    REG_WRM(PIE_REG(STX_PIE_CTRL), (cfg->ins_tofh ? STX_PIE_SRC_TOFH_Msk : 0),
            STX_PIE_SRC_TOFH_Msk);
    REG_WRM(PIE_REG(STX_PIE_CTRL), (cfg->src_tofh ? STX_PIE_INS_VLAN_Msk : 0),
            STX_PIE_INS_VLAN_Msk);
    REG_WRM(PIE_REG(STX_PIE_CTRL), (cfg->ins_vlan ? STX_PIE_SRC_VLAN_Msk : 0),
            STX_PIE_SRC_VLAN_Msk);
    REG_WRM(PIE_REG(STX_PIE_CTRL), (cfg->src_vlan ? STX_PIE_INS_FCS_Msk : 0), STX_PIE_INS_FCS_Msk);
    REG_WRM(PIE_REG(STX_PIE_CTRL), (cfg->src_prio ? STX_PIE_SRC_PRIO_Msk : 0),
            STX_PIE_SRC_PRIO_Msk);
    REG_WRM(PIE_REG(STX_PIE_CTRL),
            (cfg->size_ctrl_osize_ch_en ? STX_PIE_SIZE_CTRL_USIZE_CH_EN_Msk : 0),
            STX_PIE_SIZE_CTRL_USIZE_CH_EN_Msk);
    REG_WRM(PIE_REG(STX_PIE_CTRL),
            (cfg->size_ctrl_usize_ch_en ? STX_PIE_SIZE_CTRL_OSIZE_CH_EN_Msk : 0),
            STX_PIE_SIZE_CTRL_OSIZE_CH_EN_Msk);

    REG_WR(PIE_REG(GEN_CFG0), cfg->dest_mask);
    REG_WR(PIE_REG(GEN_CFG1), cfg->priority_mask);
    return VTSS_RC_OK;
}

/********************* CIRCULAR BUFFER ********************/
static inline void lk_crc_init(vtss_circ_ring_ctl_t *r, vtss_circ_ring_idx_t size)
{
    r->crc_size = size;
    r->crc_rd_next = r->crc_wr_next = 0;
}

static inline vtss_circ_ring_idx_t lk_crc_size(const vtss_circ_ring_ctl_t *r)
{
    return r->crc_size;
}
static inline vtss_circ_ring_idx_t lk_crc_get_wr_idx(const vtss_circ_ring_ctl_t *r)
{
    return r->crc_wr_next;
}
static inline vtss_circ_ring_idx_t lk_crc_get_rd_idx(const vtss_circ_ring_ctl_t *r)
{
    return r->crc_rd_next;
}
static inline vtss_circ_ring_idx_t lk_crc_get_next(const vtss_circ_ring_ctl_t *r,
                                                   vtss_circ_ring_idx_t        idx)
{
    idx++;
    return idx >= r->crc_size ? 0 : idx;
}

static inline vtss_circ_ring_idx_t lk_crc_wr_next(vtss_circ_ring_ctl_t *r)
{
    r->crc_wr_next = lk_crc_get_next(r, r->crc_wr_next);
    return r->crc_wr_next;
}
static inline vtss_circ_ring_idx_t lk_crc_rd_next(vtss_circ_ring_ctl_t *r)
{
    r->crc_rd_next = lk_crc_get_next(r, r->crc_rd_next);
    return r->crc_rd_next;
}

static inline BOOL lk_crc_is_full(const vtss_circ_ring_ctl_t *r)
{
    return r->crc_rd_next == lk_crc_get_next(r, r->crc_wr_next);
}

static inline uint16_t lk_crc_nb_free(const vtss_circ_ring_ctl_t *r)
{
    vtss_circ_ring_idx_t dt = r->crc_wr_next - r->crc_rd_next;
    dt %= r->crc_size;
    return r->crc_size - dt - 1;
}

/****************************************************************/

static inline uint16_t lk_get_rx_ring_sz(const vtss_lk_pie_chnl_t *c)
{
    return lk_crc_size(&c->pc_rx_ring_ctl);
}
static inline uint16_t lk_get_tx_ring_sz(const vtss_lk_pie_chnl_t *c)
{
    return lk_crc_size(&c->pc_tx_ring_ctl);
}

/****************************************************************/

static vtss_rc lk_alloc_rx_bmem(vtss_state_t *vtss_state)
{
    vtss_lk_pie_chnl_t *c = lk_get_chnl(vtss_state);
    c->pc_rx_bmem = VTSS_OS_MALLOC((c->pc_buff_sz * lk_get_rx_ring_sz(c)), VTSS_MEM_FLAGS_DMA);
    if (!c->pc_rx_bmem) {
        VTSS_E("Failed memory Allocation RX");
        return VTSS_RC_ERROR;
    }
    c->pc_rx_bmem_dma = VTSS_OS_CPU_TO_DMA_ADDR(c->pc_rx_bmem);
    return VTSS_RC_OK;
}

static vtss_rc lk_alloc_tx_bmem(vtss_state_t *vtss_state)
{
    vtss_lk_pie_chnl_t *c = lk_get_chnl(vtss_state);
    c->pc_tx_bmem = VTSS_OS_MALLOC((c->pc_buff_sz * lk_get_tx_ring_sz(c)), VTSS_MEM_FLAGS_DMA);
    if (!c->pc_tx_bmem) {
        VTSS_E("Failed memory Allocation TX ");
        return VTSS_RC_ERROR;
    }
    c->pc_tx_bmem_dma = VTSS_OS_CPU_TO_DMA_ADDR(c->pc_tx_bmem);
    return VTSS_RC_OK;
}

static vtss_rc lk_xmit_update(vtss_state_t *vtss_state)
{
    vtss_circ_ring_idx_t begin, end;
    u64                  current;
    vtss_lk_pie_chnl_t  *c = lk_get_chnl(vtss_state);
    lk_idesc_read_ptr_read(vtss_state, &current);
    end = (current - c->pc_tx_ring_mem_dma) / sizeof(lk_pie_tx_desc_t);
    begin = lk_crc_get_rd_idx(&c->pc_tx_ring_ctl);
    while (begin != end) {
        VTSS_D("Pie finished sending frame at index %i", begin);
        begin = lk_crc_rd_next(&c->pc_tx_ring_ctl);
    }
    return VTSS_RC_OK;
}

static vtss_rc lk_tx_init(vtss_state_t *vtss_state)
{
    vtss_lk_pie_chnl_t *c = lk_get_chnl(vtss_state);
    size_t              size = sizeof(struct lk_pie_tx_desc_t) * PIE_DEFAULT_TX_DESCRIPTORS;
    lk_crc_init(&c->pc_tx_ring_ctl, PIE_DEFAULT_TX_DESCRIPTORS);
    c->pc_tx_ring_mem = VTSS_OS_MALLOC(size, VTSS_MEM_FLAGS_DMA);
    if (!c->pc_tx_ring_mem) {
        VTSS_E("Failed memory Allocation TX Init");
        return VTSS_RC_ERROR;
    }
    c->pc_tx_ring_mem_dma = VTSS_OS_CPU_TO_DMA_ADDR(c->pc_tx_ring_mem);
    c->pc_tx_ring_msb = lk_pie_bd_msb(c->pc_tx_ring_mem_dma);
    VTSS_MEMSET(c->pc_tx_ring_mem, 0, size);
    u64 start = c->pc_tx_ring_mem_dma; // init tx desc ring
    u64 end = c->pc_tx_ring_mem_dma +
              sizeof(struct lk_pie_tx_desc_t) * (lk_crc_size(&c->pc_tx_ring_ctl) - 1);
    lk_pi_desc_cfg(vtss_state, start, end);
    lk_idesc_write_ptr_update(vtss_state, start);
    return VTSS_RC_OK;
}

static vtss_rc pie_rx_fill_bp(vtss_state_t *vtss_state)
{
    vtss_lk_pie_chnl_t  *c = lk_get_chnl(vtss_state);
    lk_pie_rx_desc_t     desc = {};
    lk_pie_rx_desc_t    *pd;
    u64                  bmem_dma;
    bool                 update_hw = FALSE;
    vtss_circ_ring_idx_t id;

    VTSS_MEMSET(&desc, 0, sizeof(desc));
    desc.valid = 1;
    desc.owner = 0;
    desc.block_len = c->pc_buff_sz;

    id = lk_crc_get_wr_idx(&c->pc_rx_ring_ctl);
    pd = &c->pc_rx_ring_mem[id];
    while (!lk_crc_is_full(&c->pc_rx_ring_ctl)) {
        bmem_dma = c->pc_rx_bmem_dma + (id * c->pc_buff_sz);
        desc.memory_addr = bmem_dma;
        desc.valid = 1;
        desc.owner = 0;
        desc.block_len = c->pc_buff_sz;
        VTSS_D("Allocate RX packet at id=%i dma_addr=0x%lx ", id, bmem_dma);
        *pd = desc;
        update_hw = TRUE;
        lk_crc_wr_next(&c->pc_rx_ring_ctl);
        id = lk_crc_get_wr_idx(&c->pc_rx_ring_ctl);
        pd = &c->pc_rx_ring_mem[id];
    }
    if (update_hw) {
        lk_rdesc_write_ptr_update(vtss_state,
                                  c->pc_rx_ring_mem_dma + (sizeof(lk_pie_rx_desc_t) * id));
    }
    return VTSS_RC_OK;
}

static vtss_rc lk_rx_init(vtss_state_t *vtss_state)
{
    vtss_lk_pie_chnl_t *c = lk_get_chnl(vtss_state);
    size_t              size = sizeof(struct lk_pie_rx_desc_t) * PIE_DEFAULT_RX_DESCRIPTORS;
    lk_crc_init(&c->pc_rx_ring_ctl, PIE_DEFAULT_RX_DESCRIPTORS);
    c->pc_rx_ring_mem = VTSS_OS_MALLOC(size, VTSS_MEM_FLAGS_DMA);
    if (!c->pc_rx_ring_mem) {
        VTSS_E("Failed memory Allocation RX Init");
        return VTSS_RC_ERROR;
    }
    c->pc_rx_ring_mem_dma = VTSS_OS_CPU_TO_DMA_ADDR(c->pc_rx_ring_mem);
    c->pc_rx_ring_msb = lk_pie_bd_msb(c->pc_rx_ring_mem_dma);
    VTSS_MEMSET(c->pc_rx_ring_mem, 0, size);
    u64 start = c->pc_rx_ring_mem_dma;
    u64 end = c->pc_rx_ring_mem_dma +
              sizeof(struct lk_pie_rx_desc_t) * (lk_crc_size(&c->pc_rx_ring_ctl) - 1);
    lk_edesc_read_ptr_update(vtss_state, start);
    lk_rdesc_write_ptr_update(vtss_state, start);
    lk_pe_desc_cfg(vtss_state, start, end);
    return VTSS_RC_OK;
}

vtss_rc lk_init(vtss_state_t *vtss_state)
{
    vtss_rc             rc = VTSS_RC_INCOMPLETE;
    vtss_lk_pie_chnl_t *c = lk_get_chnl(vtss_state);
    VTSS_MEMSET(c, 0, sizeof(*c));

    const lk_pie_chnl_rx_cfg_t rx_cfg = {
        .remove_rofh = 0,
        .remove_fcs = 1,
        .prepend_rofh = 0,
        .abort_miss_eof = 1,
        .abort_wrong_ub = 1,
    };

    const lk_pie_chnl_tx_cfg_t tx_cfg = {
        .size_ctrl_adjt_fh = 1,
        .size_ctrl_adjt_rem_fh = 1,
        .ins_fcs = 1,
        .ins_tofh = 0,
        .src_tofh = 0,
    };
    c->pc_buff_sz = CEIL_ALIGN(MTU, P64H_PIE_BUFF_ALIGN);
    rc = lk_chn_traffic_enable(vtss_state, FALSE);
    rc = lk_tx_init(vtss_state);
    rc = lk_rx_init(vtss_state);
    rc = lk_setup_tx_cfg(vtss_state, &tx_cfg);
    rc = lk_setup_rx_cfg(vtss_state, &rx_cfg);
    rc = lk_chn_traffic_enable(vtss_state, TRUE);
    rc = lk_alloc_rx_bmem(vtss_state);
    rc = lk_alloc_tx_bmem(vtss_state);
    rc = pie_rx_fill_bp(vtss_state);
    return rc;
}

vtss_rc lk_pie_chnl_rx(vtss_state_t *vtss_state, void *data, const u32 buflen, u8 *ifh, u32 *pktlen)
{
    vtss_circ_ring_idx_t rxid, endid;
    lk_pie_rx_desc_t    *d;
    u8                  *pkt;
    u64                  end;
    vtss_lk_pie_chnl_t  *c = lk_get_chnl(vtss_state);
    lk_edesc_write_ptr_read(vtss_state, &end);
    endid = (end - c->pc_rx_ring_mem_dma) / sizeof(lk_pie_rx_desc_t);
    rxid = lk_crc_get_rd_idx(&c->pc_rx_ring_ctl);
    if (rxid == endid) {
        return VTSS_RC_INCOMPLETE;
    }
    d = &c->pc_rx_ring_mem[rxid];

    if (!d->valid) {
        VTSS_E("Received packet with no valid bit id=%i", rxid);
        return VTSS_RC_ERROR;
    }
    if (!d->owner) {
        VTSS_E("Received packet with invalid owner bit id=%i", rxid);
        return VTSS_RC_ERROR;
    }
    if (d->rofh_present) {
        VTSS_E("Received packet with rofh bit");
        return VTSS_RC_ERROR;
    }
    if (!d->sop || !d->eop) {
        VTSS_E("Received packet without sop or eop bit");
        return VTSS_RC_ERROR;
    }
    if (d->error_present || d->err_invalid_isdx || d->err_checksum || d->err_missing_sof ||
        d->err_missing_eof || d->err_1clock_pkt || d->err_wrong_unused || d->err_fifo_overflow ||
        d->err_pkt_oversize) {
        VTSS_E("Received packet an error bit set id=%i", rxid);
        return VTSS_RC_ERROR;
    }
    pkt = c->pc_rx_bmem + (rxid * c->pc_buff_sz);
    *pktlen = d->pkt_len;
    VTSS_D("Received packet, pkt_len=%i, block_len=%i", (uint32_t)d->pkt_len,
           (uint32_t)d->block_len);
    VTSS_N_HEX(pkt, d->pkt_len);
    VTSS_MEMCPY(ifh, pkt, VTSS_FA_RX_IFH_SIZE);
    if (buflen < d->pkt_len) {
        VTSS_E("laika rx buffer too small %d", buflen);
    }
    VTSS_MEMCPY(data, (pkt + VTSS_FA_RX_IFH_SIZE), MIN(buflen, d->pkt_len - VTSS_FA_RX_IFH_SIZE));
    rxid = lk_crc_rd_next(&c->pc_rx_ring_ctl);
    end = c->pc_rx_ring_mem_dma + rxid * sizeof(lk_pie_rx_desc_t);
    lk_edesc_read_ptr_update(vtss_state, end);
    pie_rx_fill_bp(vtss_state);
    return VTSS_RC_OK;
}

vtss_rc lk_pie_chnl_tx(vtss_state_t                     *vtss_state,
                       const void *const                 frame,
                       u16                               flen,
                       const vtss_packet_tx_ifh_t *const ifh)
{
    vtss_circ_ring_idx_t txid;
    lk_pie_tx_desc_t     tx_desc;
    uint8_t             *bp;
    u64                  end;
    vtss_lk_pie_chnl_t  *c = lk_get_chnl(vtss_state);

    if (ifh->length != VTSS_FA_RX_IFH_SIZE) {
        VTSS_E("IFH length mismatch");
        return VTSS_RC_ERROR;
    }

    if ((ifh->length + flen) > MTU) {
        VTSS_E("IFH length greater than MTU");
        return VTSS_RC_ERROR;
    }

    lk_xmit_update(vtss_state);
    if (!lk_crc_nb_free(&c->pc_tx_ring_ctl)) {
        VTSS_E("No free buffer to allocate for TX Segment");
        return VTSS_RC_ERROR;
    }

    txid = lk_crc_get_wr_idx(&c->pc_tx_ring_ctl);
    bp = c->pc_tx_bmem + (c->pc_buff_sz * txid);
    VTSS_MEMCPY(bp, ifh->ifh, ifh->length);
    if (flen < MIN_FLEN) {
        VTSS_MEMSET(bp + ifh->length, 0, MIN_FLEN); // if flen < 64 must pad frame with all zeros
        flen = MIN_FLEN;
    }
    VTSS_MEMCPY(bp + ifh->length, frame, flen);
    VTSS_MEMSET(&tx_desc, 0, sizeof(tx_desc));
    tx_desc.valid = 1;
    tx_desc.sop = 1;
    tx_desc.eop = 1;
    tx_desc.block_len = flen + ifh->length;
    tx_desc.memory_addr = c->pc_tx_bmem_dma + (c->pc_buff_sz * txid);
    VTSS_N_HEX(bp, tx_desc.block_len);
    VTSS_D("Queue packet id=%i dma_addr=0x%lx block_len=%i flen=%i ifh->length=%i", txid,
           (uint64_t)tx_desc.memory_addr, (uint32_t)tx_desc.block_len, flen, ifh->length);
    c->pc_tx_ring_mem[txid] = tx_desc;
    txid = lk_crc_wr_next(&c->pc_tx_ring_ctl);
    end = c->pc_tx_ring_mem_dma + (sizeof(lk_pie_tx_desc_t) * txid);
    lk_idesc_write_ptr_update(vtss_state, end);
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_LAIKA */
