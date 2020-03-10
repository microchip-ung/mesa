// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_VCAP
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

#include "vtss_lan966x_vcap_ag_api.h"

// VCAP data selection
#define LAN966X_VCAP_SEL_ENTRY   0x01 // Select entry
#define LAN966X_VCAP_SEL_ACTION  0x02 // Select action
#define LAN966X_VCAP_SEL_COUNTER 0x04 // Select counter
#define LAN966X_VCAP_SEL_ALL     0xff // Select all

// VCAP commands
#define LAN966X_VCAP_CMD_WRITE     0 // Write from cache to VCAP
#define LAN966X_VCAP_CMD_READ      1 // Read from VCAP to cache
#define LAN966X_VCAP_CMD_MOVE_DOWN 2 // Move <count> down
#define LAN966X_VCAP_CMD_MOVE_UP   3 // Move <count> up
#define LAN966X_VCAP_CMD_INIT      4 // Write all (from cache)

/* TG values */
#define LAN966X_VCAP_TG_NONE 0x00
#define LAN966X_VCAP_TG_X1   0x01
#define LAN966X_VCAP_TG_X2   0x02
#define LAN966X_VCAP_TG_X4   0x04

/* ================================================================= *
 *  VCAP control
 * ================================================================= */

typedef struct {
    enum vtss_lan966x_vcap        vcap;
    struct vtss_lan966x_vcap_data data;
    u32                           cmd;
    u32                           sel;
    u32                           addr;
    u32                           mv_size;
    u32                           mv_pos;
    u32                           key_tg;
    u32                           act_tg;
    u32                           cnt;
    BOOL                          is_action;
    vtss_debug_printf_t           pr;
} lan966x_vcap_info_t;

static vtss_rc lan966x_vcap_cmd(vtss_state_t *vtss_state, lan966x_vcap_info_t *info)
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(info->vcap);
    u32          value, tgt = va->instance;

    REG_WR(VCAP_MV_CFG(tgt),
           VCAP_MV_CFG_MV_NUM_POS(info->mv_pos) |
           VCAP_MV_CFG_MV_SIZE(info->mv_size));
    REG_WR(VCAP_UPDATE_CTRL(tgt),
           VCAP_UPDATE_CTRL_UPDATE_CMD(info->cmd) |
           VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(info->sel & LAN966X_VCAP_SEL_ENTRY ? 0 : 1) |
           VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(info->sel & LAN966X_VCAP_SEL_ACTION ? 0 : 1) |
           VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(info->sel & LAN966X_VCAP_SEL_COUNTER ? 0 : 1) |
           VCAP_UPDATE_CTRL_UPDATE_ADDR(info->addr) |
           VCAP_UPDATE_CTRL_CLEAR_CACHE(info->cmd == LAN966X_VCAP_CMD_INIT ? 1 : 0) |
           VCAP_UPDATE_CTRL_UPDATE_SHOT_M);
    do {
        REG_RD(VCAP_UPDATE_CTRL(tgt), &value);
    } while (value & VCAP_UPDATE_CTRL_UPDATE_SHOT_M);

    return VTSS_RC_OK;
}

#define LAN966X_BITS_TO_WORDS(x) (((x)+31)/32)

static u32 lan966x_vcap_tg_count(u32 tg)
{
    return tg;
}

static const char *lan966x_vcap_tg_txt(u8 tg)
{
    return (tg == LAN966X_VCAP_TG_X1 ? "X1" :
            tg == LAN966X_VCAP_TG_X2 ? "X2" :
            tg == LAN966X_VCAP_TG_X4 ? "X4" : "XX");
}

static u32 lan966x_vcap_entry_addr(enum vtss_lan966x_vcap vcap, vtss_vcap_idx_t *idx)
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(vcap);
    u32                                  addr;

    addr = (idx->row * va->sw_count + (idx->col + 1) * va->sw_count/vtss_vcap_key_rule_count(idx->key_size));
    return (va->rows * va->sw_count - addr);
}

static u32 lan966x_vcap_key_type(enum vtss_lan966x_vcap vcap, vtss_vcap_key_size_t key_size)
{
    return (key_size == VTSS_VCAP_KEY_SIZE_QUARTER || vcap == VTSS_LAN966X_VCAP_ES0 ? LAN966X_VCAP_TG_X1 :
            key_size == VTSS_VCAP_KEY_SIZE_HALF ? LAN966X_VCAP_TG_X2 : LAN966X_VCAP_TG_X4);
}

static vtss_rc lan966x_vcap_entry_cmd(vtss_state_t *vtss_state, lan966x_vcap_info_t *info)
{
    const struct vtss_lan966x_vcap_attrs     *va = vtss_lan966x_vcap_attrs_get(info->vcap);
    const struct vtss_lan966x_vcap_tgs_attrs *ta = vtss_lan966x_vcap_key_tgs_attrs_get(info->vcap, va->sw_count);
    u32                                      i, j, sw_cnt, val, msk, w, tg, tgw, tgt = va->instance;
    u32                                      key_sw_cnt = 0, key_reg_cnt = 0, key_tgw = 0, key_offs = 0;
    u32                                      act_sw_cnt = 0, act_reg_cnt = 0, act_tgw = 0, act_offs = 0;
    u32                                      addr_old = info->addr;

    if (info->sel & LAN966X_VCAP_SEL_ENTRY) {
        key_sw_cnt = lan966x_vcap_tg_count(info->key_tg);
        key_reg_cnt = LAN966X_BITS_TO_WORDS(va->sw_width);
        key_tgw = ta->tg_width;
    }

    if (info->sel & LAN966X_VCAP_SEL_ACTION) {
        act_sw_cnt = lan966x_vcap_tg_count(info->act_tg);
        act_reg_cnt = LAN966X_BITS_TO_WORDS(va->act_width);
        act_tgw = (info->vcap == VTSS_LAN966X_VCAP_IS2 ? 2 : 0);
    }

    sw_cnt = MAX(key_sw_cnt, act_sw_cnt);
    sw_cnt = MAX(sw_cnt, info->sel & LAN966X_VCAP_SEL_COUNTER ? 1 : 0);
    VTSS_N("sw_cnt: %u, key_sw_cnt: %u, act_sw_cnt: %u", sw_cnt, key_sw_cnt, act_sw_cnt);
    for (i = 0; i < sw_cnt; i++, info->addr++) {
        if (info->cmd == LAN966X_VCAP_CMD_READ) {
            // Read from cache
            VTSS_RC(lan966x_vcap_cmd(vtss_state, info));
        }

        // Key
        for (j = 0; j < key_reg_cnt && i < key_sw_cnt; j++) {
            if (info->cmd == LAN966X_VCAP_CMD_READ && i == 0 && j == 0) {
                // Read TG for first word in base address
                REG_RD(VCAP_ENTRY_DAT(tgt, j), &val);
                REG_RD(VCAP_MASK_DAT(tgt, j), &msk);
                if ((val & 1) == 1 && (msk & 1) == 1) {
                    // Match-off means that entry is disabled
                    info->key_tg = LAN966X_VCAP_TG_NONE;
                } else if (key_tgw) {
                    // IS1/IS2 key, width 3/2/1
                    tgw = ((info->addr % 4) == 0 ? 3 : (info->addr % 2) == 0 ? 2 : 1);
                    tg = (VTSS_EXTRACT_BITFIELD(val, 0, tgw) & ~msk);
                    info->key_tg = ((tg & LAN966X_VCAP_TG_X1) ? LAN966X_VCAP_TG_X1 :
                                    (tg & LAN966X_VCAP_TG_X2) ? LAN966X_VCAP_TG_X2 :
                                    (tg & LAN966X_VCAP_TG_X4) ? LAN966X_VCAP_TG_X4 : LAN966X_VCAP_TG_NONE);
                } else {
                    // ES0 key, width 0
                    info->key_tg = LAN966X_VCAP_TG_X1;
                }
            }

            // Calculate data and TG width
            tg = info->key_tg;
            tgw = ((j != 0 || ta->tg_width == 0 || tg == LAN966X_VCAP_TG_NONE) ? 0 :
                   (tg > LAN966X_VCAP_TG_X2 && (info->addr % 4) == 0) ? 3 :
                   (tg > LAN966X_VCAP_TG_X1 && (info->addr % 2) == 0) ? 2 : 1);
            w = (va->sw_width % 32);
            w = ((j == (key_reg_cnt - 1) && w != 0 ? w : 32) - tgw);

            // Read/write key
            if (info->cmd == LAN966X_VCAP_CMD_READ) {
                REG_RD(VCAP_ENTRY_DAT(tgt, j), &val);
                REG_RD(VCAP_MASK_DAT(tgt, j), &msk);
                vtss_bs_set(info->data.entry, key_offs, w, val >> tgw);
                vtss_bs_set(info->data.mask, key_offs, w, ~msk >> tgw);
            } else {
                val = ((vtss_bs_get(info->data.entry, key_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(tg, 0, tgw));
                msk = ((vtss_bs_get(info->data.mask, key_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(0xff, 0, tgw));
                msk = ~msk;
                REG_WR(VCAP_ENTRY_DAT(tgt, j), val);
                REG_WR(VCAP_MASK_DAT(tgt, j), msk);
            }
            VTSS_N("addr: %u, j: %u, val/msk: 0x%08x/%08x", info->addr, j, val, msk);
            key_offs += w;
        }

        // Action
        for (j = 0; j < act_reg_cnt && i < act_sw_cnt; j++) {
            if (info->cmd == LAN966X_VCAP_CMD_READ && i == 0 && j == 0) {
                // Read TG for first word in base address
                if (act_tgw) {
                    // IS2 action, width 2/1
                    REG_RD(VCAP_ACTION_DAT(tgt, j), &val);
                    tgw = ((info->addr % 2) == 0 ? 2 : 1);
                    tg = VTSS_EXTRACT_BITFIELD(val, 0, tgw);
                    info->act_tg = ((tg & LAN966X_VCAP_TG_X1) ? LAN966X_VCAP_TG_X1 :
                                    (tg & LAN966X_VCAP_TG_X2) ? LAN966X_VCAP_TG_X2 : LAN966X_VCAP_TG_NONE);
                } else {
                    // IS1/ES0 action, width 0
                    info->act_tg = LAN966X_VCAP_TG_X1;
                }
            }

            // Calculate data and TG width
            tg = info->act_tg;
            tgw = ((j != 0 || act_tgw == 0 || tg == LAN966X_VCAP_TG_NONE) ? 0 :
                   (tg > LAN966X_VCAP_TG_X1 && (info->addr % 2) == 0) ? 2 : 1);
            w = (va->act_width % 32);
            w = ((j == (act_reg_cnt - 1) && w != 0 ? w : 32) - tgw);

            // Read/write action
            if (info->cmd == LAN966X_VCAP_CMD_READ) {
                REG_RD(VCAP_ACTION_DAT(tgt, j), &val);
                vtss_bs_set(info->data.action, act_offs, w, val >> tgw);
            } else {
                val = ((vtss_bs_get(info->data.action, act_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(tg, 0, tgw));
                REG_WR(VCAP_ACTION_DAT(tgt, j), val);
            }
            VTSS_N("addr: %u, j: %u, val: 0x%08x", info->addr, j, val);
            act_offs += w;
        }

        // Counter
        if ((info->sel & LAN966X_VCAP_SEL_COUNTER) && i == 0) {
            if (info->cmd == LAN966X_VCAP_CMD_READ) {
                REG_RD(VCAP_CNT_DAT(tgt, 0), &info->cnt);
            } else {
                REG_WR(VCAP_CNT_DAT(tgt, 0), info->cnt);
            }
        }

        if (info->cmd == LAN966X_VCAP_CMD_WRITE) {
            // Write to cache
            VTSS_RC(lan966x_vcap_cmd(vtss_state, info));
        }
    }
    info->addr = addr_old; // Restore original address
    return VTSS_RC_OK;
}

static vtss_rc lan966x_vcap_entry_del(vtss_state_t *vtss_state, enum vtss_lan966x_vcap vcap, vtss_vcap_idx_t *idx)
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(vcap);
    lan966x_vcap_info_t                  info = {0};

    info.vcap = vcap;
    info.cmd = LAN966X_VCAP_CMD_INIT;
    info.sel = LAN966X_VCAP_SEL_ALL;
    info.addr = lan966x_vcap_entry_addr(vcap, idx);
    info.mv_size = (lan966x_vcap_tg_count(lan966x_vcap_key_type(vcap, idx->key_size)) - 1);
    VTSS_I("%s, row: %u, col: %u, addr: %u", va->name, idx->row, idx->col, info.addr);
    return lan966x_vcap_cmd(vtss_state, &info);
}

static vtss_rc lan966x_vcap_entry_move(vtss_state_t *vtss_state,
                                       enum vtss_lan966x_vcap vcap, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(vcap);
    lan966x_vcap_info_t                  info = {0};
    u32                                  cnt = (va->sw_count/vtss_vcap_key_rule_count(idx->key_size));

    if (count == 0) {
        VTSS_E("illegal count zero");
        return VTSS_RC_ERROR;
    }
    info.vcap = vcap;
    info.cmd = (up ? LAN966X_VCAP_CMD_MOVE_UP : LAN966X_VCAP_CMD_MOVE_DOWN);
    info.sel = LAN966X_VCAP_SEL_ALL;
    info.addr = (lan966x_vcap_entry_addr(vcap, idx) - (count - 1) * cnt);
    info.mv_size = (count * cnt - 1);
    info.mv_pos = (cnt - 1);
    VTSS_I("%s, row: %u, col: %u, %s, count: %u, up: %u, addr: %u",
           va->name, idx->row, idx->col, vtss_vcap_key_size2txt(idx->key_size), count, up, info.addr);
    return lan966x_vcap_cmd(vtss_state, &info);
}

static vtss_rc lan966x_vcap_entry_get(vtss_state_t *vtss_state,
                                      enum vtss_lan966x_vcap vcap, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(vcap);
    lan966x_vcap_info_t                  info = {0};

    info.vcap = vcap;
    info.cmd = LAN966X_VCAP_CMD_READ;
    info.sel = LAN966X_VCAP_SEL_COUNTER;
    info.addr = lan966x_vcap_entry_addr(vcap, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u", va->name, idx->row, idx->col, info.addr);
    VTSS_RC(lan966x_vcap_entry_cmd(vtss_state, &info));
    *counter = info.cnt;
    if (clear) {
        info.cmd = LAN966X_VCAP_CMD_WRITE;
        info.cnt = 0;
        VTSS_RC(lan966x_vcap_entry_cmd(vtss_state, &info));
    }
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Utilities
 * ================================================================= */

void vtss_lan966x_vcap_key_set(struct vtss_lan966x_vcap_data *data, u32 offset, u32 width, u32 value, u32 mask)
{
    if (width > 32) {
        VTSS_E("illegal width: %u, offset: %u", width, offset);
    } else {
        vtss_bs_set(data->entry, offset, width, value & mask); /* Avoid 'match-off' */
        vtss_bs_set(data->mask, offset , width, mask);
    }
}

void vtss_lan966x_vcap_key_bytes_set(struct vtss_lan966x_vcap_data *data, u32 offset, u8 *val, u8 *msk, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++) {
        vtss_lan966x_vcap_key_set(data, offset + (count - i - 1) * 8, 8, val[i], msk[i]);
    }
}

void vtss_lan966x_vcap_key_bit_set(struct vtss_lan966x_vcap_data *data, u32 offset, enum vtss_lan966x_vcap_bit val)
{
    vtss_lan966x_vcap_key_set(data, offset, 1,
                              val == VTSS_LAN966X_VCAP_BIT_1 ? 1 : 0,
                              val == VTSS_LAN966X_VCAP_BIT_ANY ? 0 : 1);
}

void vtss_lan966x_vcap_action_set(struct vtss_lan966x_vcap_data *data, u32 offset, u32 width, u32 value)
{
    vtss_bs_set(data->action, offset, width, width == 1 ? (value ? 1 : 0) : value);
}

void vtss_lan966x_vcap_action_bit_set(struct vtss_lan966x_vcap_data *data, u32 offset, u32 value)
{
    vtss_lan966x_vcap_action_set(data, offset, 1, value ? 1 : 0);
}

void vtss_lan966x_vcap_bit_set(enum vtss_lan966x_vcap_bit *out, vtss_vcap_bit_t in)
{
    *out = (in == VTSS_VCAP_BIT_0 ? VTSS_LAN966X_VCAP_BIT_0 :
            in == VTSS_VCAP_BIT_1 ? VTSS_LAN966X_VCAP_BIT_1 : VTSS_LAN966X_VCAP_BIT_ANY);
}

static void lan966x_vcap_u8_set(struct vtss_lan966x_vcap_u8 *out, vtss_vcap_u8_t *in)
{
    out->value = in->value;
    out->mask = in->mask;
}

static void lan966x_vcap_u16_set(struct vtss_lan966x_vcap_u16 *out, vtss_vcap_u16_t *in)
{
    int i;

    memset(out, 0, sizeof(*out));
    for (i = 0; i < 2; i++) {
        out->value = ((out->value << 8) + in->value[i]);
        out->mask = ((out->mask << 8) + in->mask[i]);
    }
}

static void lan966x_vcap_u32_set(struct vtss_lan966x_vcap_u32 *out, vtss_vcap_u32_t *in)
{
    int i;

    memset(out, 0, sizeof(*out));
    for (i = 0; i < 4; i++) {
        out->value = ((out->value << 8) + in->value[i]);
        out->mask = ((out->mask << 8) + in->mask[i]);
    }
}

static void lan966x_vcap_u48_set(struct vtss_lan966x_vcap_u48 *out, vtss_vcap_u48_t *in)
{
    int i, j;

    for (i = 0; i < 6; i++) {
        j = (i < 4 ? (i + 2) : (i - 4)); // 32-bit chunk mapping
        out->value[i] = in->value[j];
        out->mask[i] = in->mask[j];
    }
}

static void lan966x_vcap_u128_set(struct vtss_lan966x_vcap_u128 *out, vtss_vcap_u128_t *in)
{
    int i, j;

    for (i = 0; i < 16; i++) {
        j = (i < 4 ? (i + 12) : i < 8 ? (i + 4) : i < 12 ? (i - 4) : (i - 12)); // 32-bit chunk mapping
        out->value[i] = in->value[j];
        out->mask[i] = in->mask[j];
    }
}

static void lan966x_vcap_ipv4_set(struct vtss_lan966x_vcap_u32 *out, vtss_vcap_ip_t *in)
{
    out->value = in->value;
    out->mask = in->mask;
}

/* ================================================================= *
 *  Debug print utilities
 * ================================================================= */

static u32 lan966x_act_get(lan966x_vcap_info_t *info, u32 offs, u32 len)
{
    return vtss_bs_get(info->data.action, offs, len);
}

static void lan966x_debug_action(lan966x_vcap_info_t *info, const char *name, u32 offs, u32 len)
{
    info->pr("%s:%u ", name, lan966x_act_get(info, offs, len));
}

static void lan966x_debug_bits(lan966x_vcap_info_t *info, const char *name, u32 offset, u32 len)
{
    vtss_debug_printf_t pr = info->pr;
    u32                 i,j, v, m;

    if (name) {
        pr("%s:", name);
    }
    if (len > 32)  {
        // Recursive print of 32-bit chunks
        lan966x_debug_bits(info, NULL, offset, len - 32);
        lan966x_debug_bits(info, NULL, offset + len - 32, 32);
    } else {
        for (i = 0; i < len; i++) {
            j = (len - 1 - i);
            if (i != 0 && (j % 8) == 7) {
                pr(".");
            }
            j += offset;
            if (info->is_action) {
                v = vtss_bs_bit_get(info->data.action, j);
                m = 1;
            } else {
                v = vtss_bs_bit_get(info->data.entry, j);
                m = vtss_bs_bit_get(info->data.mask, j);
            }
            pr("%c", m ? (v ? '1' : '0') : (v ? 'N' : 'X'));
        }
    }
    pr(name == NULL ? (len > 32 ? "" : ".") : (len > 24 ? "\n" : " "));
}

static void lan966x_debug_action_ena(lan966x_vcap_info_t *info, const char *name, u32 offs, u32 offs_val, u32 len)
{
    vtss_debug_printf_t pr = info->pr;
    int                 i, length = strlen(name);
    BOOL                enable = vtss_bs_bit_get(info->data.action, offs);

    for (i = 0; i < length; i++) {
        pr("%c", enable ? toupper(name[i]) : tolower(name[i]));
    }
    pr(":%u ", lan966x_act_get(info, offs_val, len));
}

#define LAN966X_DEBUG_ACT(vcap, name, fld)        lan966x_debug_action(info, name, \
                                                                       VTSS_LAN966X_VCAP_##vcap##_ACTION_##fld##_O, \
                                                                       VTSS_LAN966X_VCAP_##vcap##_ACTION_##fld##_L)
#define LAN966X_DEBUG_ACT_ENA(vcap, name, f1, f2) lan966x_debug_action_ena(info, name, \
                                                                           VTSS_LAN966X_VCAP_##vcap##_ACTION_##f1##_O, \
                                                                           VTSS_LAN966X_VCAP_##vcap##_ACTION_##f2##_O, \
                                                                           VTSS_LAN966X_VCAP_##vcap##_ACTION_##f2##_L)
#define LAN966X_DEBUG_ACT_BITS(vcap, name, fld)   lan966x_debug_bits(info, name, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_ACTION_##fld##_O, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_ACTION_##fld##_L)
#define LAN966X_DEBUG_BITS(vcap, name, fld)       lan966x_debug_bits(info, name, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_KEY_##fld##_O, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_KEY_##fld##_L)

#define LAN966X_VCAP_ACT_GET(vcap, fld)           vtss_bs_get(info->data.action, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_ACTION_##fld##_O, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_ACTION_##fld##_L)
#define LAN966X_VCAP_ENTRY_GET(vcap, fld)         vtss_bs_get(info->data.entry, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_KEY_##fld##_O, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_KEY_##fld##_L)
#define LAN966X_VCAP_MASK_GET(vcap, fld)          vtss_bs_get(info->data.mask, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_KEY_##fld##_O, \
                                                                     VTSS_LAN966X_VCAP_##vcap##_KEY_##fld##_L)

/* ================================================================= *
 *  IS1
 * ================================================================= */

static vtss_rc lan966x_is1_entry_get(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is1_entry_add(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is1_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is1_entry_move(vtss_state_t *vtss_state,
                                      vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_is1_entry_update(vtss_state_t *vtss_state,
                                        vtss_vcap_idx_t *idx, vtss_is1_action_t *act)
{
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  IS2
 * ================================================================= */

static vtss_rc lan966x_is2_action_set(vtss_state_t *vtss_state, lan966x_vcap_info_t *info, vtss_acl_action_t *action)
{
    struct vtss_lan966x_vcap_is2_action_fields    f = {0};
    struct vtss_lan966x_vcap_is2_action_base_type *a = &f.u.base_type;
    vtss_acl_port_action_t                        act = action->port_action;
    u32                                           mask, pol_idx;

    if (info->act_tg == LAN966X_VCAP_TG_X1) {
        f.action = VTSS_LAN966X_VCAP_IS2_ACTION_SMAC_SIP;
        f.u.smac_sip.host_match = 1;
    } else {
        f.action = VTSS_LAN966X_VCAP_IS2_ACTION_BASE_TYPE;
        a->hit_me_once = action->cpu_once;
        a->cpu_copy_ena = action->cpu;
        a->cpu_qu_num = action->cpu_queue;
        a->mask_mode = (act == VTSS_ACL_PORT_ACTION_FILTER ? 1 :
                        act == VTSS_ACL_PORT_ACTION_REDIR ? 3 : 0);
        a->mirror_ena = action->mirror;
        a->lrn_dis = (action->learn ? 0 : 1);
        mask = vtss_lan966x_port_mask(vtss_state, action->port_list);
        if (act != VTSS_ACL_PORT_ACTION_NONE &&
            mask == 0 &&
            action->cpu_once == 0 &&
            action->cpu == 0) {
            /* Forwarding and CPU copy disabled, discard using policer to avoid CPU copy */
            pol_idx = LAN966X_POLICER_DISC;
        } else if (action->police) {
            pol_idx = (LAN966X_POLICER_ACL + action->policer_no);
        } else {
            pol_idx = 0;
        }
        a->police_ena = (pol_idx ? 1 : 0);
        a->police_idx = pol_idx;
        if (act == VTSS_ACL_PORT_ACTION_REDIR) {
            mask &= vtss_lan966x_port_mask(vtss_state, vtss_state->l2.tx_forward_aggr);
        }
        a->port_mask = mask;
        a->rew_op = 0; // TBD: PTP actions
        a->acl_id = (action->ifh_flag ? 1 : 0);
    }
    return (vtss_lan966x_vcap_is2_action_pack(&f, &info->data) ? VTSS_RC_ERROR : VTSS_RC_OK);
}

static vtss_rc lan966x_is2_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return lan966x_vcap_entry_get(vtss_state, VTSS_LAN966X_VCAP_IS2, idx, counter, clear);
}

static vtss_vcap_bit_t lan966x_ptp_bit_get(vtss_ace_ptp_t *ptp, u8 idx, u8 offs)
{
    u8 msk = (1 << offs);

    return ((ptp->header.mask[idx] & msk) == 0 ? VTSS_VCAP_BIT_ANY :
            (ptp->header.value[idx] & msk) ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
}

static vtss_rc lan966x_is2_entry_add(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    const struct vtss_lan966x_vcap_attrs         *va = vtss_lan966x_vcap_attrs_get(VTSS_LAN966X_VCAP_IS2);
    struct vtss_lan966x_vcap_is2_key_fields      f = {0};
    struct vtss_lan966x_vcap_is2_key_ip6_tcp_udp def = {0};
    lan966x_vcap_info_t                          info = {0};
    vtss_is2_data_t                              *is2 = &vcap_data->u.is2;
    vtss_is2_entry_t                             *entry = is2->entry;
    vtss_ace_t                                   *ace = &entry->ace;
    vtss_ace_frame_ipv4_t                        *ipv4 = &ace->frame.ipv4;
    vtss_ace_frame_ipv6_t                        *ipv6 = &ace->frame.ipv6;
    vtss_vcap_u8_t                               *proto = NULL, *ds, l2_pl1, l2_pl2;
    vtss_vcap_u16_t                              l2_pl0;
    vtss_vcap_u32_t                              data, sip, dip, l3_pl0, l3_pl1;
    vtss_vcap_u48_t                              *ip_data, smac;
    vtss_vcap_udp_tcp_t                          *sport, *dport;
    vtss_vcap_bit_t                              ttl, tcp_fin, tcp_syn, tcp_rst, tcp_psh, tcp_ack, tcp_urg;
    vtss_vcap_bit_t                              fragment, options, sip_eq_dip, sport_eq_dport, seq_zero;
    vtss_ace_ptp_t                               *ptp;
    u32                                          i, val, msk;

    info.vcap = VTSS_LAN966X_VCAP_IS2;
    info.cmd = LAN966X_VCAP_CMD_WRITE;
    info.sel = LAN966X_VCAP_SEL_ALL;
    info.addr = lan966x_vcap_entry_addr(info.vcap, idx);
    info.cnt = counter;
    VTSS_I("%s, row: %u, col: %u, addr: %u", va->name, idx->row, idx->col, info.addr);

    // Common fields placed in default struct
    def.first = (entry->first ? VTSS_LAN966X_VCAP_BIT_1 : VTSS_LAN966X_VCAP_BIT_0);
    lan966x_vcap_u8_set(&def.pag, &ace->policy);
    def.igr_port_mask.mask = ~vtss_lan966x_port_mask(vtss_state, ace->port_list);
    def.host_match = (entry->host_match ? VTSS_LAN966X_VCAP_BIT_1 : VTSS_LAN966X_VCAP_BIT_ANY);
    vtss_lan966x_vcap_bit_set(&def.l2_mc, ace->dmac_mc);
    vtss_lan966x_vcap_bit_set(&def.l2_bc, ace->dmac_bc);
    vtss_lan966x_vcap_bit_set(&def.vlan_tagged, ace->vlan.tagged);
    def.vid.value = ace->vlan.vid.value;
    def.vid.mask = ace->vlan.vid.mask;
    vtss_lan966x_vcap_bit_set(&def.dei, ace->vlan.cfi);
    lan966x_vcap_u8_set(&def.pcp, &ace->vlan.usr_prio);

    // IP fields placed in default struct
    if (ace->type == VTSS_ACE_TYPE_IPV4) {
        /* IPv4 */
        ipv4 = &ace->frame.ipv4;
        proto = &ipv4->proto;
        ttl = ipv4->ttl;
        fragment = ipv4->fragment;
        options = ipv4->options;
        ds = &ipv4->ds;
        ip_data = &ipv4->data;
        sport = &ipv4->sport;
        dport = &ipv4->dport;
        tcp_fin = ipv4->tcp_fin;
        tcp_syn = ipv4->tcp_syn;
        tcp_rst = ipv4->tcp_rst;
        tcp_psh = ipv4->tcp_psh;
        tcp_ack = ipv4->tcp_ack;
        tcp_urg = ipv4->tcp_urg;
        sip_eq_dip = ipv4->sip_eq_dip;
        sport_eq_dport = ipv4->sport_eq_dport;
        seq_zero = ipv4->seq_zero;
        ptp = &ipv4->ptp;
    } else {
        /* IPv6 */
        ipv4 = NULL;
        proto = &ipv6->proto;
        ttl = ipv6->ttl;
        fragment = VTSS_VCAP_BIT_ANY;
        options = VTSS_VCAP_BIT_ANY;
        ds = &ipv6->ds;
        ip_data = &ipv6->data;
        sport = &ipv6->sport;
        dport = &ipv6->dport;
        tcp_fin = ipv6->tcp_fin;
        tcp_syn = ipv6->tcp_syn;
        tcp_rst = ipv6->tcp_rst;
        tcp_psh = ipv6->tcp_psh;
        tcp_ack = ipv6->tcp_ack;
        tcp_urg = ipv6->tcp_urg;
        sip_eq_dip = ipv6->sip_eq_dip;
        sport_eq_dport = ipv6->sport_eq_dport;
        seq_zero = ipv6->seq_zero;
        ptp = &ipv6->ptp;
    }
    vtss_lan966x_vcap_bit_set(&def.l3_ttl_gt0, ttl);
    lan966x_vcap_u8_set(&def.l3_tos, ds);
    lan966x_vcap_u128_set(&def.l3_ip6_dip, &ipv6->dip);
    lan966x_vcap_u128_set(&def.l3_ip6_sip, &ipv6->sip);
    vtss_lan966x_vcap_bit_set(&def.dip_eq_sip, sip_eq_dip);
    def.tcp = (proto->value == 6 ? VTSS_LAN966X_VCAP_BIT_1 : VTSS_LAN966X_VCAP_BIT_0);
    def.l4_dport.value = dport->low;
    def.l4_dport.mask = (dport->in_range && dport->low == dport->high ? 0xffff : 0);
    def.l4_sport.value = sport->low;
    def.l4_sport.mask = (sport->in_range && sport->low == sport->high ? 0xffff : 0);
    def.l4_rng.value = ((is2->srange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->srange)) |
                        (is2->drange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->drange)));
    def.l4_rng.mask = def.l4_rng.value;
    vtss_lan966x_vcap_bit_set(&def.sport_eq_dport, sport_eq_dport);
    if (ptp->enable) {
        seq_zero = lan966x_ptp_bit_get(ptp, 0, 0);
        tcp_fin = lan966x_ptp_bit_get(ptp, 0, 1);
        tcp_syn = lan966x_ptp_bit_get(ptp, 0, 2);
        tcp_rst = lan966x_ptp_bit_get(ptp, 0, 3);
        tcp_psh = lan966x_ptp_bit_get(ptp, 3, 1);
        tcp_ack = lan966x_ptp_bit_get(ptp, 3, 2);
        tcp_urg = lan966x_ptp_bit_get(ptp, 3, 7);
        f.u.ip6_tcp_udp.l4_1588_dom.value = ptp->header.value[2];
        f.u.ip6_tcp_udp.l4_1588_dom.mask = ptp->header.mask[2];
        f.u.ip6_tcp_udp.l4_1588_ver.value = ptp->header.value[1];
        f.u.ip6_tcp_udp.l4_1588_ver.mask = ptp->header.mask[1];
    }
    vtss_lan966x_vcap_bit_set(&def.sequence_eq0, seq_zero);
    vtss_lan966x_vcap_bit_set(&def.l4_fin, tcp_fin);
    vtss_lan966x_vcap_bit_set(&def.l4_syn, tcp_syn);
    vtss_lan966x_vcap_bit_set(&def.l4_rst, tcp_rst);
    vtss_lan966x_vcap_bit_set(&def.l4_psh, tcp_psh);
    vtss_lan966x_vcap_bit_set(&def.l4_ack, tcp_ack);
    vtss_lan966x_vcap_bit_set(&def.l4_urg, tcp_urg);

    // IP data, upper 24 bits
    for (i = 0; i < 4; i++) {
        l3_pl1.value[i] = (i ? ip_data->value[i - 1] : 0);
        l3_pl1.mask[i] = (i ? ip_data->mask[i - 1] : 0);
    }
    // IP data, lower 24 bits
    for (i = 0; i < 4; i++) {
        l3_pl0.value[i] = (i < 3 ? ip_data->value[i + 3] : 0);
        l3_pl0.mask[i] = (i < 3 ? ip_data->mask[i + 3] : 0);
    }

    if (idx->key_size == VTSS_VCAP_KEY_SIZE_QUARTER) {
        // SMAC_SIP4 rule
        info.key_tg = LAN966X_VCAP_TG_X1;
        info.act_tg = LAN966X_VCAP_TG_X1;
        f.key = VTSS_LAN966X_VCAP_IS2_KEY_SMAC_SIP4;
        for (i = 0; i < 6; i++) {
            smac.value[i] = ace->frame.ipv4.sip_smac.smac.addr[i];
            smac.mask[i] = 0xff;
        }
        lan966x_vcap_u48_set(&f.u.smac_sip4.l2_smac, &smac);
        f.u.smac_sip4.l3_ip4_sip.value = ace->frame.ipv4.sip_smac.sip;
        f.u.smac_sip4.l3_ip4_sip.mask = 0xffffffff;
    } else if (idx->key_size == VTSS_VCAP_KEY_SIZE_FULL) {
        // IPv6 full rule
        info.key_tg = LAN966X_VCAP_TG_X4;
        info.act_tg = LAN966X_VCAP_TG_X2;

        // Common fields for IP6_TCP_UDP/IP6_OTHER
        f.key = VTSS_LAN966X_VCAP_IS2_KEY_IP6_TCP_UDP;
        f.u.ip6_tcp_udp.first = def.first;
        f.u.ip6_tcp_udp.pag = def.pag;
        f.u.ip6_tcp_udp.igr_port_mask = def.igr_port_mask;
        f.u.ip6_tcp_udp.host_match = def.host_match;
        f.u.ip6_tcp_udp.l2_mc = def.l2_mc;
        f.u.ip6_tcp_udp.l2_bc = def.l2_bc;
        f.u.ip6_tcp_udp.vlan_tagged = def.vlan_tagged;
        f.u.ip6_tcp_udp.vid = def.vid;
        f.u.ip6_tcp_udp.dei = def.dei;
        f.u.ip6_tcp_udp.pcp = def.pcp;
        f.u.ip6_tcp_udp.l3_ttl_gt0 = def.l3_ttl_gt0;
        f.u.ip6_tcp_udp.l3_tos = def.l3_tos;
        f.u.ip6_tcp_udp.l3_ip6_dip = def.l3_ip6_dip;
        f.u.ip6_tcp_udp.l3_ip6_sip = def.l3_ip6_sip;
        f.u.ip6_tcp_udp.dip_eq_sip = def.dip_eq_sip;

        if (vtss_vcap_udp_tcp_rule(proto)) {
            // UDP/TCP
            f.u.ip6_tcp_udp.tcp = def.tcp;
            f.u.ip6_tcp_udp.l4_dport = def.l4_dport;
            f.u.ip6_tcp_udp.l4_sport = def.l4_sport;
            f.u.ip6_tcp_udp.l4_rng = def.l4_rng;
            f.u.ip6_tcp_udp.sport_eq_dport = def.sport_eq_dport;
            f.u.ip6_tcp_udp.sequence_eq0 = def.sequence_eq0;
            f.u.ip6_tcp_udp.l4_fin = def.l4_fin;
            f.u.ip6_tcp_udp.l4_syn = def.l4_syn;
            f.u.ip6_tcp_udp.l4_rst = def.l4_rst;
            f.u.ip6_tcp_udp.l4_psh = def.l4_psh;
            f.u.ip6_tcp_udp.l4_ack = def.l4_ack;
            f.u.ip6_tcp_udp.l4_urg = def.l4_urg;
            f.u.ip6_tcp_udp.l4_1588_dom = def.l4_1588_dom;
            f.u.ip6_tcp_udp.l4_1588_ver = def.l4_1588_ver;
        } else if (proto->mask == 0) {
            // Any protocol
            f.u.ip6_tcp_udp.type.mask = 0x2;
        } else {
            // Non-UDP/TCP protocol
            f.key = VTSS_LAN966X_VCAP_IS2_KEY_IP6_OTHER;
            lan966x_vcap_u8_set(&f.u.ip6_other.l3_proto, proto);
            lan966x_vcap_u32_set(&f.u.ip6_other.l3_payload_1, &l3_pl1);
            lan966x_vcap_u32_set(&f.u.ip6_other.l3_payload_0, &l3_pl0);
        }
    } else {
        // Half rule
        info.key_tg = LAN966X_VCAP_TG_X2;
        info.act_tg = LAN966X_VCAP_TG_X2;

        // Common fields
        f.u.mac_etype.first = def.first;
        f.u.mac_etype.pag = def.pag;
        f.u.mac_etype.igr_port_mask = def.igr_port_mask;
        f.u.mac_etype.host_match = def.host_match;
        f.u.mac_etype.l2_mc = def.l2_mc;
        f.u.mac_etype.l2_bc = def.l2_bc;
        f.u.mac_etype.vlan_tagged = def.vlan_tagged;
        f.u.mac_etype.vid = def.vid;
        f.u.mac_etype.dei = def.dei;
        f.u.mac_etype.pcp = def.pcp;

        switch (ace->type) {
        case VTSS_ACE_TYPE_ANY:
            f.key = VTSS_LAN966X_VCAP_IS2_KEY_MAC_ETYPE;
            f.u.mac_etype.type.value = VTSS_LAN966X_VCAP_IS2_KEY_MAC_ETYPE_TYPE_ID;
            f.u.mac_etype.type.mask = 0x80; // Override default type
            lan966x_vcap_u48_set(&f.u.mac_etype.l2_dmac, &ace->frame.any.dmac);
            lan966x_vcap_u48_set(&f.u.mac_etype.l2_smac, &ace->frame.any.smac);
            for (i = 0; i < 6; i++) {
                if (ace->frame.any.dmac.mask[i] != 0 || ace->frame.any.smac.mask[i] != 0) {
                    // Match ETYPE/LLC/SNAP frames with DMAC/SMAC filtering. ARP frames must be mapped to ETYPE
                    f.u.mac_etype.type.mask = 0xc;
                    break;
                }
            }
            break;
        case VTSS_ACE_TYPE_ETYPE:
            f.key = VTSS_LAN966X_VCAP_IS2_KEY_MAC_ETYPE;
            lan966x_vcap_u48_set(&f.u.mac_etype.l2_dmac, &ace->frame.etype.dmac);
            lan966x_vcap_u48_set(&f.u.mac_etype.l2_smac, &ace->frame.etype.smac);
            lan966x_vcap_u16_set(&f.u.mac_etype.etype, &ace->frame.etype.etype);
            ptp = &ace->frame.etype.ptp;
            if (ptp->enable) {
                for (i = 0; i < 2; i++) {
                    l2_pl0.value[i] = ptp->header.value[i];
                    l2_pl0.mask[i] = ptp->header.mask[i];
                }
                l2_pl1.value = ptp->header.value[2];
                l2_pl1.mask = ptp->header.mask[2];
                lan966x_vcap_u8_set(&f.u.mac_etype.l2_payload1, &l2_pl1);
                val = ptp->header.value[3];
                msk = ptp->header.mask[3];
                l2_pl2.value = (((val & 0x80) >> 5) | (val & 0x6) >> 1); // Bit 7,2,1
                l2_pl2.mask  = (((msk & 0x80) >> 5) | (msk & 0x6) >> 1); // Bit 7,2,1
                lan966x_vcap_u8_set(&f.u.mac_etype.l2_payload2, &l2_pl2);
            } else {
                l2_pl0 = ace->frame.etype.data;
            }
            lan966x_vcap_u16_set(&f.u.mac_etype.l2_payload0, &l2_pl0);
            break;
        case VTSS_ACE_TYPE_LLC:
            f.key = VTSS_LAN966X_VCAP_IS2_KEY_MAC_LLC;
            lan966x_vcap_u48_set(&f.u.mac_llc.l2_dmac, &ace->frame.llc.dmac);
            lan966x_vcap_u48_set(&f.u.mac_llc.l2_smac, &ace->frame.llc.smac);
            f.u.mac_llc.l2_llc_1.value = ace->frame.llc.llc.value[0];
            f.u.mac_llc.l2_llc_1.mask = ace->frame.llc.llc.mask[0];
            for (i = 0; i < 4; i++) {
                data.value[i] = (i < 3 ? ace->frame.llc.llc.value[i + 1] : 0);
                data.mask[i] = (i < 3 ? ace->frame.llc.llc.mask[i + 1] : 0);
            }
            lan966x_vcap_u32_set(&f.u.mac_llc.l2_llc_0, &data);
            break;
        case VTSS_ACE_TYPE_SNAP:
            f.key = VTSS_LAN966X_VCAP_IS2_KEY_MAC_SNAP;
            lan966x_vcap_u48_set(&f.u.mac_snap.l2_dmac, &ace->frame.snap.dmac);
            lan966x_vcap_u48_set(&f.u.mac_snap.l2_smac, &ace->frame.snap.smac);
            f.u.mac_snap.l2_snap_1.value = ace->frame.snap.snap.value[0];
            f.u.mac_snap.l2_snap_1.mask = ace->frame.snap.snap.mask[0];
            for (i = 0; i < 4; i++) {
                data.value[i] = ace->frame.snap.snap.value[i + 1];
                data.mask[i] = ace->frame.snap.snap.mask[i + 1];
            }
            lan966x_vcap_u32_set(&f.u.mac_snap.l2_snap_0, &data);
            break;
        case VTSS_ACE_TYPE_ARP:
            f.key = VTSS_LAN966X_VCAP_IS2_KEY_ARP;
            lan966x_vcap_u48_set(&f.u.arp.l2_smac, &ace->frame.arp.smac);
            vtss_lan966x_vcap_bit_set(&f.u.arp.arp_addr_space_ok, ace->frame.arp.ethernet);
            vtss_lan966x_vcap_bit_set(&f.u.arp.arp_proto_space_ok, ace->frame.arp.ip);
            vtss_lan966x_vcap_bit_set(&f.u.arp.arp_len_ok, ace->frame.arp.length);
            vtss_lan966x_vcap_bit_set(&f.u.arp.arp_tgt_match, ace->frame.arp.dmac_match);
            vtss_lan966x_vcap_bit_set(&f.u.arp.arp_sender_match, ace->frame.arp.smac_match);
            vtss_lan966x_vcap_bit_set(&f.u.arp.arp_opcode_unknown, ace->frame.arp.unknown);
            // Opcode bit 1: RARP flag
            f.u.arp.arp_opcode.mask |= (ace->frame.arp.arp == VTSS_ACE_BIT_ANY ? 0 : 0x2);
            f.u.arp.arp_opcode.value |= (ace->frame.arp.arp == VTSS_ACE_BIT_0 ? 0x2 :0);
            // Opcode bit 0: Reply flag
            f.u.arp.arp_opcode.mask |= (ace->frame.arp.req == VTSS_ACE_BIT_ANY ? 0 : 0x1);
            f.u.arp.arp_opcode.value |= (ace->frame.arp.req == VTSS_ACE_BIT_0 ? 0x1 :0);
            lan966x_vcap_ipv4_set(&f.u.arp.l3_ip4_dip, &ace->frame.arp.dip);
            lan966x_vcap_ipv4_set(&f.u.arp.l3_ip4_sip, &ace->frame.arp.sip);
            break;
        case VTSS_ACE_TYPE_IPV4:
        case VTSS_ACE_TYPE_IPV6:
            f.key = VTSS_LAN966X_VCAP_IS2_KEY_IP4_TCP_UDP;
            vtss_lan966x_vcap_bit_set(&f.u.ip4_tcp_udp.ip4, ipv4 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            vtss_lan966x_vcap_bit_set(&f.u.ip4_tcp_udp.l3_fragment, fragment);
            vtss_lan966x_vcap_bit_set(&f.u.ip4_tcp_udp.l3_options, options);
            f.u.ip4_tcp_udp.l3_ttl_gt0 = def.l3_ttl_gt0;
            f.u.ip4_tcp_udp.l3_tos = def.l3_tos;
            f.u.ip4_tcp_udp.dip_eq_sip = def.dip_eq_sip;
            if (ipv4) {
                lan966x_vcap_ipv4_set(&f.u.ip4_tcp_udp.l3_ip4_dip, &ipv4->dip);
                lan966x_vcap_ipv4_set(&f.u.ip4_tcp_udp.l3_ip4_sip, &ipv4->sip);
            } else {
                for (i = 0; i < 4; i++) {
                    sip.value[i] = ipv6->sip.value[i + 12];
                    sip.mask[i] = ipv6->sip.mask[i + 12];
                    dip.value[i] = ipv6->sip.value[i + 8];
                    dip.mask[i] = ipv6->sip.mask[i + 8];
                }
                lan966x_vcap_u32_set(&f.u.ip4_tcp_udp.l3_ip4_dip, &dip);
                lan966x_vcap_u32_set(&f.u.ip4_tcp_udp.l3_ip4_sip, &sip);
            }

            if (vtss_vcap_udp_tcp_rule(proto)) {
                // UDP/TCP
                f.u.ip4_tcp_udp.tcp = def.tcp;
                f.u.ip4_tcp_udp.l4_dport = def.l4_dport;
                f.u.ip4_tcp_udp.l4_sport = def.l4_sport;
                f.u.ip4_tcp_udp.l4_rng = def.l4_rng;
                f.u.ip4_tcp_udp.sport_eq_dport = def.sport_eq_dport;
                f.u.ip4_tcp_udp.sequence_eq0 = def.sequence_eq0;
                f.u.ip4_tcp_udp.l4_fin = def.l4_fin;
                f.u.ip4_tcp_udp.l4_syn = def.l4_syn;
                f.u.ip4_tcp_udp.l4_rst = def.l4_rst;
                f.u.ip4_tcp_udp.l4_psh = def.l4_psh;
                f.u.ip4_tcp_udp.l4_ack = def.l4_ack;
                f.u.ip4_tcp_udp.l4_urg = def.l4_urg;
                f.u.ip4_tcp_udp.l4_1588_dom = def.l4_1588_dom;
                f.u.ip4_tcp_udp.l4_1588_ver = def.l4_1588_ver;
            } else if (proto->mask == 0) {
                // Any protocol
                f.u.ip4_tcp_udp.type.value = VTSS_LAN966X_VCAP_IS2_KEY_IP4_TCP_UDP_TYPE_ID;
                f.u.ip4_tcp_udp.type.mask = 0xe;
            } else {
                // Non-UDP/TCP protocol
                f.key = VTSS_LAN966X_VCAP_IS2_KEY_IP4_OTHER;
                lan966x_vcap_u8_set(&f.u.ip4_other.l3_proto, proto);
                lan966x_vcap_u32_set(&f.u.ip4_other.l3_payload_1, &l3_pl1);
                lan966x_vcap_u32_set(&f.u.ip4_other.l3_payload_0, &l3_pl0);
            }
            break;
        default:
            break;
        }
    }
    VTSS_RC(lan966x_is2_action_set(vtss_state, &info, &ace->action));
    return (vtss_lan966x_vcap_is2_key_pack(&f, &info.data) < 0 ? VTSS_RC_ERROR :
            lan966x_vcap_entry_cmd(vtss_state, &info));
}

static vtss_rc lan966x_is2_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return lan966x_vcap_entry_del(vtss_state, VTSS_LAN966X_VCAP_IS2, idx);
}

static vtss_rc lan966x_is2_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return lan966x_vcap_entry_move(vtss_state, VTSS_LAN966X_VCAP_IS2, idx, count, up);
}

static vtss_rc lan966x_is2_entry_update(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_is2_data_t *is2)
{
    lan966x_vcap_info_t info = {0};
    vtss_port_no_t      port_no;
    BOOL                member[VTSS_PORTS];

    // Read-modify-write action port mask
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        member[port_no] = (VTSS_PORT_BF_GET(is2->action.member, port_no) &&
                           vtss_state->l2.tx_forward_aggr[port_no]);
    }
    info.vcap = VTSS_LAN966X_VCAP_IS2;
    info.cmd = LAN966X_VCAP_CMD_READ;
    info.sel = LAN966X_VCAP_SEL_ACTION;
    info.addr = lan966x_vcap_entry_addr(info.vcap, idx);
    info.act_tg = LAN966X_VCAP_TG_X2;
    VTSS_I("row: %u, col: %u, addr: %u", idx->row, idx->col, info.addr);
    VTSS_RC(lan966x_vcap_entry_cmd(vtss_state, &info));
    vtss_lan966x_vcap_action_set(&info.data,
                                 VTSS_LAN966X_VCAP_IS2_ACTION_BASE_TYPE_FLD_PORT_MASK_O,
                                 VTSS_LAN966X_VCAP_IS2_ACTION_BASE_TYPE_FLD_PORT_MASK_L,
                                 vtss_lan966x_port_mask(vtss_state, member));
    info.cmd = LAN966X_VCAP_CMD_WRITE;
    return lan966x_vcap_entry_cmd(vtss_state, &info);
}

/* ================================================================= *
 *  ES0
 * ================================================================= */

static vtss_rc lan966x_es0_entry_get(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_entry_add(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_entry_move(vtss_state_t *vtss_state,
                                      vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_entry_update(vtss_state_t *vtss_state,
                                        vtss_vcap_idx_t *idx, vtss_es0_data_t *es0)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_es0_eflow_update(vtss_state_t *vtss_state, const vtss_eflow_id_t flow_id)
{
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  ACL
 * ================================================================= */

static vtss_rc lan966x_acl_policer_set(vtss_state_t *vtss_state, const vtss_acl_policer_no_t policer_no)
{
    vtss_acl_policer_conf_t *conf = &vtss_state->vcap.acl_policer_conf[policer_no];
    vtss_policer_conf_t     pol_conf;

    memset(&pol_conf, 0, sizeof(pol_conf));
    if (conf->bit_rate_enable) {
        pol_conf.eir = conf->bit_rate;
        pol_conf.ebs = 1; /* Minimum burst size */
    } else {
        pol_conf.frame_rate = 1;
        pol_conf.eir = conf->rate;
    }
    return vtss_lan966x_qos_policer_conf_set(vtss_state, policer_no + LAN966X_POLICER_ACL, &pol_conf);
}

static vtss_rc lan966x_acl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(VTSS_LAN966X_VCAP_IS2);
    lan966x_vcap_info_t                  info = {0};
    vtss_acl_port_conf_t                 *conf = &vtss_state->vcap.acl_port_conf[port_no];
    vtss_acl_frame_key_t                 *key = &conf->key;
    u32                                  ipv6, lookup = 0x1, port = VTSS_CHIP_PORT(port_no);
    u32                                  enable = (conf->policy_no == VTSS_ACL_POLICY_NO_NONE ? 0 : 1);

    VTSS_I("port_no: %u, port: %u", port_no, port);

    /* Enable/disable S2 and set default PAG */
    ipv6 = (key->ipv6 == VTSS_ACL_KEY_ETYPE ? 3 : key->ipv6 == VTSS_ACL_KEY_EXT ? 0 : 2);
    REG_WR(ANA_VCAP_S2_CFG(port),
           ANA_VCAP_S2_CFG_ENA(enable) |
           ANA_VCAP_S2_CFG_ARP_DIS(key->arp == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
           ANA_VCAP_S2_CFG_IP_TCPUDP_DIS(key->ipv4 == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
           ANA_VCAP_S2_CFG_IP_OTHER_DIS(key->ipv4 == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
           ANA_VCAP_S2_CFG_IP6_CFG(ipv6));

    REG_WRM(ANA_VCAP_CFG(port),
            ANA_VCAP_CFG_PAG_VAL(enable ? conf->policy_no & 0x3f : 0),
            ANA_VCAP_CFG_PAG_VAL_M);

    info.act_tg = LAN966X_VCAP_TG_X2;
    VTSS_RC(lan966x_is2_action_set(vtss_state, &info, &conf->action));
    info.vcap = VTSS_LAN966X_VCAP_IS2;
    info.cmd = LAN966X_VCAP_CMD_WRITE;
    info.sel = LAN966X_VCAP_SEL_ACTION;
    info.addr = ((va->rows + port) * va->sw_count);
    VTSS_I("port: %u, addr: %u", port, info.addr);
    return lan966x_vcap_entry_cmd(vtss_state, &info);
}

static vtss_rc lan966x_acl_port_counter(vtss_state_t *vtss_state,
                                        const vtss_port_no_t    port_no,
                                        vtss_acl_port_counter_t *const counter)
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(VTSS_LAN966X_VCAP_IS2);
    lan966x_vcap_info_t                  info = {0};
    u32                                  port = VTSS_CHIP_PORT(port_no);

    info.vcap = VTSS_LAN966X_VCAP_IS2;
    info.cmd = (counter ? LAN966X_VCAP_CMD_READ : LAN966X_VCAP_CMD_WRITE);
    info.sel = LAN966X_VCAP_SEL_COUNTER;
    info.addr = ((va->rows + port) * va->sw_count);
    VTSS_RC(lan966x_vcap_entry_cmd(vtss_state, &info));
    if (counter) {
        *counter = info.cnt;
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_acl_port_counter_get(vtss_state_t *vtss_state,
                                            const vtss_port_no_t    port_no,
                                            vtss_acl_port_counter_t *const counter)
{
    return lan966x_acl_port_counter(vtss_state, port_no, counter);
}

static vtss_rc lan966x_acl_port_counter_clear(vtss_state_t *vtss_state,
                                              const vtss_port_no_t port_no)
{
    return lan966x_acl_port_counter(vtss_state, port_no, NULL);
}

static vtss_rc lan966x_ace_add(vtss_state_t *vtss_state,
                               const vtss_ace_id_t ace_id, const vtss_ace_t *const ace)
{
    vtss_vcap_obj_t             *obj = &vtss_state->vcap.is2.obj;
    vtss_vcap_user_t            user = VTSS_IS2_USER_ACL;
    vtss_vcap_data_t            data;
    vtss_is2_data_t             *is2 = &data.u.is2;
    vtss_is2_entry_t            entry;
    vtss_res_chg_t              chg;
    const vtss_ace_udp_tcp_t    *sport = NULL, *dport = NULL;
    vtss_vcap_range_chk_table_t range_new = vtss_state->vcap.range;
    BOOL                        sip_smac_new = 0, sip_smac_old = 0;
    vtss_port_no_t              port_no;
    vtss_vcap_key_size_t        key_size = VTSS_VCAP_KEY_SIZE_HALF;

    // Check the simple things
    VTSS_RC(vtss_cmn_ace_add(vtss_state, ace_id, ace));

    if (ace->type == VTSS_ACE_TYPE_IPV6 && ace->type_ext) {
        // Encode as IPv6 is full rule
        key_size = VTSS_VCAP_KEY_SIZE_FULL;
    }

    // Check that half entry can be added
    memset(&chg, 0, sizeof(chg));
    chg.add_key[key_size] = 1;
    if (vtss_vcap_lookup(vtss_state, obj, user, ace->id, &data, NULL) == VTSS_RC_OK) {
        chg.del_key[data.key_size] = 1;

        // Free any old range checkers
        VTSS_RC(vtss_vcap_range_free(&range_new, is2->srange));
        VTSS_RC(vtss_vcap_range_free(&range_new, is2->drange));

        // Lookup SIP/SMAC rule
        if (vtss_vcap_lookup(vtss_state, obj, VTSS_IS2_USER_ACL_SIP, ace->id,
                             NULL, NULL) == VTSS_RC_OK) {
            sip_smac_old = 1;
            chg.del_key[VTSS_VCAP_KEY_SIZE_QUARTER] = 1;
        }
    }

    if (ace->type == VTSS_ACE_TYPE_IPV4) {
        if (ace->frame.ipv4.sip_smac.enable) {
            // SMAC_SIP4 rule needed
            sip_smac_new = 1;
            chg.add_key[VTSS_VCAP_KEY_SIZE_QUARTER] = 1;
        }
        if (vtss_vcap_udp_tcp_rule(&ace->frame.ipv4.proto)) {
            sport = &ace->frame.ipv4.sport;
            dport = &ace->frame.ipv4.dport;
        }
    }
    if (ace->type == VTSS_ACE_TYPE_IPV6 && vtss_vcap_udp_tcp_rule(&ace->frame.ipv6.proto)) {
        sport = &ace->frame.ipv6.sport;
        dport = &ace->frame.ipv6.dport;
    }
    VTSS_RC(vtss_cmn_vcap_res_check(obj, &chg));

    vtss_vcap_is2_init(&data, &entry);
    if (sport && dport) {
        // Allocate new range checkers
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->srange, sport, 1));
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->drange, dport, 0));
    }

    // Commit range checkers
    VTSS_RC(vtss_vcap_range_commit(vtss_state, &range_new));

    // Add main entry
    entry.first = 1;
    entry.ace = *ace;
    if (sip_smac_new) {
        entry.host_match = 1;
        entry.ace.frame.ipv4.sip.value = ace->frame.ipv4.sip_smac.sip;
        entry.ace.frame.ipv4.sip.mask = 0xffffffff;
    }
    data.key_size = key_size;
    if (ace->action.port_action == VTSS_ACL_PORT_ACTION_REDIR) {
        is2->action.redir = 1;
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (ace->action.port_list[port_no]) {
                VTSS_PORT_BF_SET(is2->action.member, port_no, 1);
            }
        }
    }
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, ace->id, ace_id, &data, 0));
    is2->action.redir = 0;

    // Add/delete SIP/SMAC entry
    user = VTSS_IS2_USER_ACL_SIP;
    if (sip_smac_new) {
        data.key_size = VTSS_VCAP_KEY_SIZE_QUARTER;
        VTSS_RC(vtss_vcap_add(vtss_state, obj, user, ace->id, VTSS_VCAP_ID_LAST, &data, 0));
    } else if (sip_smac_old) {
        VTSS_RC(vtss_vcap_del(vtss_state, obj, user, ace->id));
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ace_del(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    // Delete main entry
    VTSS_RC(vtss_cmn_ace_del(vtss_state, ace_id));

    // Delete SIP/SMAC entry
    VTSS_RC(vtss_vcap_del(vtss_state, &vtss_state->vcap.is2.obj, VTSS_IS2_USER_ACL_SIP, ace_id));
    return VTSS_RC_OK;
}

static vtss_rc lan966x_vcap_range_commit(vtss_state_t *vtss_state)
{
    u32                   i, type;
    vtss_vcap_range_chk_t *entry;

    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        entry = &vtss_state->vcap.range.entry[i];
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
            if (entry->count == 0) {
                type = 0;
                break;
            } else {
                VTSS_E("illegal type: %d", entry->type);
                return VTSS_RC_ERROR;
            }
        }
        REG_WR(ANA_VCAP_RNG_CFG(i), ANA_VCAP_RNG_CFG_CFG(type));
        REG_WR(ANA_VCAP_RNG_VAL_CFG(i),
               ANA_VCAP_RNG_VAL_CFG_MIN_VAL(entry->min) |
               ANA_VCAP_RNG_VAL_CFG_MAX_VAL(entry->max));
    }
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

vtss_rc vtss_lan966x_debug_is1_all(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_debug_range_checkers(vtss_state_t *vtss_state,
                                          const vtss_debug_printf_t pr,
                                          const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_debug_is2(vtss_state_t *vtss_state, lan966x_vcap_info_t *info)
{
    vtss_debug_printf_t pr = info->pr;
    u32                 val, msk;

    if (info->is_action) {
        if (info->act_tg == LAN966X_VCAP_TG_X2) {
            LAN966X_DEBUG_ACT(IS2, "hit_me_once", BASE_TYPE_FLD_HIT_ME_ONCE);
            LAN966X_DEBUG_ACT_ENA(IS2, "cpu_copy", BASE_TYPE_FLD_CPU_COPY_ENA, BASE_TYPE_FLD_CPU_QU_NUM);
            LAN966X_DEBUG_ACT(IS2, "mirror", BASE_TYPE_FLD_MIRROR_ENA);
            LAN966X_DEBUG_ACT(IS2, "lrn_dis", BASE_TYPE_FLD_LRN_DIS);
            LAN966X_DEBUG_ACT(IS2, "isdx", BASE_TYPE_FLD_ISDX_ENA);
            LAN966X_DEBUG_ACT(IS2, "acl_id", BASE_TYPE_FLD_ACL_ID);
            pr("\n");
            LAN966X_DEBUG_ACT_ENA(IS2, "police", BASE_TYPE_FLD_POLICE_ENA, BASE_TYPE_FLD_POLICE_IDX);
            LAN966X_DEBUG_ACT(IS2, "police_vcap_only", BASE_TYPE_FLD_POLICE_VCAP_ONLY);
            LAN966X_DEBUG_ACT(IS2, "mask_mode", BASE_TYPE_FLD_MASK_MODE);
            LAN966X_DEBUG_ACT_BITS(IS2, "port_mask", BASE_TYPE_FLD_PORT_MASK);
        } else if (info->act_tg == LAN966X_VCAP_TG_X1) {
            LAN966X_DEBUG_ACT_ENA(IS2, "cpu_copy", SMAC_SIP_FLD_CPU_COPY_ENA, SMAC_SIP_FLD_CPU_QU_NUM);
            LAN966X_DEBUG_ACT(IS2, "fwd_kill", SMAC_SIP_FLD_FWD_KILL_ENA);
            LAN966X_DEBUG_ACT(IS2, "host_match", SMAC_SIP_FLD_HOST_MATCH);
        } else {
            return VTSS_RC_OK;
        }
        pr("\ncnt: %u", info->cnt);
        return VTSS_RC_OK;
    }

    // Quarter key
    if (info->key_tg == LAN966X_VCAP_TG_X1) {
        LAN966X_DEBUG_BITS(IS2, "igr_port", SMAC_SIP4_FLD_IGR_PORT);
        LAN966X_DEBUG_BITS(IS2, "smac", SMAC_SIP4_FLD_L2_SMAC);
        LAN966X_DEBUG_BITS(IS2, "sip", SMAC_SIP4_FLD_L3_IP4_SIP);
        return VTSS_RC_OK;
    }

    // Full key
    if (info->key_tg == LAN966X_VCAP_TG_X4) {
        LAN966X_DEBUG_BITS(IS2, "type", CUSTOM_FLD_TYPE);
        val = LAN966X_VCAP_ENTRY_GET(IS2, CUSTOM_FLD_TYPE);
        msk = LAN966X_VCAP_MASK_GET(IS2, CUSTOM_FLD_TYPE);
        pr("(%s) ",
           msk == 0 ? "any" :
           val == VTSS_LAN966X_VCAP_IS2_KEY_IP6_TCP_UDP_TYPE_ID ? "ip6_udp_tcp" :
           val == VTSS_LAN966X_VCAP_IS2_KEY_IP6_OTHER_TYPE_ID ? "ip6_other" :
           val == VTSS_LAN966X_VCAP_IS2_KEY_CUSTOM_TYPE_ID ? "custom" : "?");
        LAN966X_DEBUG_BITS(IS2, "first", CUSTOM_FLD_FIRST);
        LAN966X_DEBUG_BITS(IS2, "pag", CUSTOM_FLD_PAG);
        LAN966X_DEBUG_BITS(IS2, "port_mask", CUSTOM_FLD_IGR_PORT_MASK);
        pr("\n");
        LAN966X_DEBUG_BITS(IS2, "isdx_gt0", CUSTOM_FLD_ISDX_GT0);
        LAN966X_DEBUG_BITS(IS2, "host_match", CUSTOM_FLD_HOST_MATCH);
        LAN966X_DEBUG_BITS(IS2, "l2_mc", CUSTOM_FLD_L2_MC);
        LAN966X_DEBUG_BITS(IS2, "l2_bc", CUSTOM_FLD_L2_BC);
        LAN966X_DEBUG_BITS(IS2, "vlan_tagged", CUSTOM_FLD_VLAN_TAGGED);
        LAN966X_DEBUG_BITS(IS2, "vid", CUSTOM_FLD_VID);
        LAN966X_DEBUG_BITS(IS2, "pcp", CUSTOM_FLD_PCP);
        LAN966X_DEBUG_BITS(IS2, "dei", CUSTOM_FLD_DEI);
        pr("\n");

        if (val == VTSS_LAN966X_VCAP_IS2_KEY_IP6_TCP_UDP_TYPE_ID) {
            LAN966X_DEBUG_BITS(IS2, "dip", IP6_TCP_UDP_FLD_L3_IP6_DIP);
            LAN966X_DEBUG_BITS(IS2, "sip", IP6_TCP_UDP_FLD_L3_IP6_SIP);
            LAN966X_DEBUG_BITS(IS2, "ttl_gt0", IP6_TCP_UDP_FLD_L3_TTL_GT0);
            LAN966X_DEBUG_BITS(IS2, "tos", IP6_TCP_UDP_FLD_L3_TOS);
            LAN966X_DEBUG_BITS(IS2, "dip_eq_sip", IP6_TCP_UDP_FLD_DIP_EQ_SIP);
            LAN966X_DEBUG_BITS(IS2, "tcp", IP6_TCP_UDP_FLD_TCP);
            LAN966X_DEBUG_BITS(IS2, "dport", IP6_TCP_UDP_FLD_L4_DPORT);
            LAN966X_DEBUG_BITS(IS2, "sport", IP6_TCP_UDP_FLD_L4_SPORT);
            LAN966X_DEBUG_BITS(IS2, "rng", IP6_TCP_UDP_FLD_L4_RNG);
            pr("\n");
            LAN966X_DEBUG_BITS(IS2, "sp_eq_dp", IP6_TCP_UDP_FLD_SPORT_EQ_DPORT);
            LAN966X_DEBUG_BITS(IS2, "seq0", IP6_TCP_UDP_FLD_SEQUENCE_EQ0);
            LAN966X_DEBUG_BITS(IS2, "fin", IP6_TCP_UDP_FLD_L4_FIN);
            LAN966X_DEBUG_BITS(IS2, "syn", IP6_TCP_UDP_FLD_L4_SYN);
            LAN966X_DEBUG_BITS(IS2, "rst", IP6_TCP_UDP_FLD_L4_RST);
            LAN966X_DEBUG_BITS(IS2, "psh", IP6_TCP_UDP_FLD_L4_PSH);
            LAN966X_DEBUG_BITS(IS2, "ack", IP6_TCP_UDP_FLD_L4_ACK);
            LAN966X_DEBUG_BITS(IS2, "urg", IP6_TCP_UDP_FLD_L4_URG);
            LAN966X_DEBUG_BITS(IS2, "1588_dom", IP6_TCP_UDP_FLD_L4_1588_DOM);
            LAN966X_DEBUG_BITS(IS2, "1588_ver", IP6_TCP_UDP_FLD_L4_1588_VER);
        } else if (val == VTSS_LAN966X_VCAP_IS2_KEY_IP6_OTHER_TYPE_ID) {
            LAN966X_DEBUG_BITS(IS2, "ttl_gt0", IP6_OTHER_FLD_L3_TTL_GT0);
            LAN966X_DEBUG_BITS(IS2, "tos", IP6_OTHER_FLD_L3_TOS);
            LAN966X_DEBUG_BITS(IS2, "dip", IP6_OTHER_FLD_L3_IP6_DIP);
            LAN966X_DEBUG_BITS(IS2, "sip", IP6_OTHER_FLD_L3_IP6_SIP);
            LAN966X_DEBUG_BITS(IS2, "dip_eq_sip", IP6_OTHER_FLD_DIP_EQ_SIP);
            LAN966X_DEBUG_BITS(IS2, "proto", IP6_OTHER_FLD_L3_PROTO);
            LAN966X_DEBUG_BITS(IS2, "payload1", IP6_OTHER_FLD_L3_PAYLOAD_1);
            LAN966X_DEBUG_BITS(IS2, "payload0", IP6_OTHER_FLD_L3_PAYLOAD_0);
            LAN966X_DEBUG_BITS(IS2, "spare", IP6_OTHER_FLD_SPARE);
        }
        pr("\n");
        return VTSS_RC_OK;
    }

    // Half key
    LAN966X_DEBUG_BITS(IS2, "type", MAC_ETYPE_FLD_TYPE);
    val = LAN966X_VCAP_ENTRY_GET(IS2, MAC_ETYPE_FLD_TYPE);
    msk = LAN966X_VCAP_MASK_GET(IS2, MAC_ETYPE_FLD_TYPE);
    pr("(%s) ",
       msk == 0 ? "any" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_MAC_ETYPE_TYPE_ID ? "etype" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_MAC_LLC_TYPE_ID ? "llc" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_MAC_SNAP_TYPE_ID ? "snap" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_ARP_TYPE_ID ? "arp" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_IP4_TCP_UDP_TYPE_ID ? "ip4_udp_tcp" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_IP4_OTHER_TYPE_ID ? "ip4_other" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_IP6_STD_TYPE_ID ? "ip6_std" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_OAM_TYPE_ID ? "oam" :
       val == VTSS_LAN966X_VCAP_IS2_KEY_SMAC_SIP6_TYPE_ID ? "smac_sip6" : "?");

    if (val == VTSS_LAN966X_VCAP_IS2_KEY_SMAC_SIP6_TYPE_ID) {
        LAN966X_DEBUG_BITS(IS2, "igr_port", SMAC_SIP6_FLD_IGR_PORT);
        LAN966X_DEBUG_BITS(IS2, "smac", SMAC_SIP6_FLD_L2_SMAC);
        LAN966X_DEBUG_BITS(IS2, "sip", SMAC_SIP6_FLD_L3_IP6_SIP);
        return VTSS_RC_OK;
    }

    // Common half key fields
    LAN966X_DEBUG_BITS(IS2, "first", MAC_ETYPE_FLD_FIRST);
    LAN966X_DEBUG_BITS(IS2, "pag", MAC_ETYPE_FLD_PAG);
    LAN966X_DEBUG_BITS(IS2, "port_mask", MAC_ETYPE_FLD_IGR_PORT_MASK);
    pr("\n");
    LAN966X_DEBUG_BITS(IS2, "isdx_gt0", MAC_ETYPE_FLD_ISDX_GT0);
    LAN966X_DEBUG_BITS(IS2, "host_match", MAC_ETYPE_FLD_HOST_MATCH);
    LAN966X_DEBUG_BITS(IS2, "l2_mc", MAC_ETYPE_FLD_L2_MC);
    LAN966X_DEBUG_BITS(IS2, "l2_bc", MAC_ETYPE_FLD_L2_BC);
    LAN966X_DEBUG_BITS(IS2, "vlan_tagged", MAC_ETYPE_FLD_VLAN_TAGGED);
    LAN966X_DEBUG_BITS(IS2, "vid", MAC_ETYPE_FLD_VID);
    LAN966X_DEBUG_BITS(IS2, "pcp", MAC_ETYPE_FLD_PCP);
    LAN966X_DEBUG_BITS(IS2, "dei", MAC_ETYPE_FLD_DEI);
    pr("\n");

    if (val == VTSS_LAN966X_VCAP_IS2_KEY_MAC_ETYPE_TYPE_ID) {
        LAN966X_DEBUG_BITS(IS2, "dmac", MAC_ETYPE_FLD_L2_DMAC);
        LAN966X_DEBUG_BITS(IS2, "smac", MAC_ETYPE_FLD_L2_SMAC);
        LAN966X_DEBUG_BITS(IS2, "etype", MAC_ETYPE_FLD_ETYPE);
        LAN966X_DEBUG_BITS(IS2, "frm_type", MAC_ETYPE_FLD_L2_FRM_TYPE);
        LAN966X_DEBUG_BITS(IS2, "payload0", MAC_ETYPE_FLD_L2_PAYLOAD0);
        LAN966X_DEBUG_BITS(IS2, "payload1", MAC_ETYPE_FLD_L2_PAYLOAD1);
        LAN966X_DEBUG_BITS(IS2, "payload2", MAC_ETYPE_FLD_L2_PAYLOAD2);
    } else if (val == VTSS_LAN966X_VCAP_IS2_KEY_MAC_LLC_TYPE_ID) {
        LAN966X_DEBUG_BITS(IS2, "dmac", MAC_LLC_FLD_L2_DMAC);
        LAN966X_DEBUG_BITS(IS2, "smac", MAC_LLC_FLD_L2_SMAC);
        LAN966X_DEBUG_BITS(IS2, "llc1", MAC_LLC_FLD_L2_LLC_1);
        LAN966X_DEBUG_BITS(IS2, "llc0", MAC_LLC_FLD_L2_LLC_0);
    } else if (val == VTSS_LAN966X_VCAP_IS2_KEY_MAC_SNAP_TYPE_ID) {
        LAN966X_DEBUG_BITS(IS2, "dmac", MAC_SNAP_FLD_L2_DMAC);
        LAN966X_DEBUG_BITS(IS2, "smac", MAC_SNAP_FLD_L2_SMAC);
        LAN966X_DEBUG_BITS(IS2, "snap1", MAC_SNAP_FLD_L2_SNAP_1);
        LAN966X_DEBUG_BITS(IS2, "snap0", MAC_SNAP_FLD_L2_SNAP_0);
    } else if (val == VTSS_LAN966X_VCAP_IS2_KEY_ARP_TYPE_ID) {
        LAN966X_DEBUG_BITS(IS2, "smac", ARP_FLD_L2_SMAC);
        LAN966X_DEBUG_BITS(IS2, "addr_ok", ARP_FLD_ARP_ADDR_SPACE_OK);
        LAN966X_DEBUG_BITS(IS2, "proto_ok", ARP_FLD_ARP_PROTO_SPACE_OK);
        LAN966X_DEBUG_BITS(IS2, "len_ok", ARP_FLD_ARP_LEN_OK);
        LAN966X_DEBUG_BITS(IS2, "tgt_match", ARP_FLD_ARP_TGT_MATCH);
        LAN966X_DEBUG_BITS(IS2, "sender_match", ARP_FLD_ARP_SENDER_MATCH);
        LAN966X_DEBUG_BITS(IS2, "opcode_unk", ARP_FLD_ARP_OPCODE_UNKNOWN);
        LAN966X_DEBUG_BITS(IS2, "opcode", ARP_FLD_ARP_OPCODE);
        pr("\n");
        LAN966X_DEBUG_BITS(IS2, "dip", ARP_FLD_L3_IP4_DIP);
        LAN966X_DEBUG_BITS(IS2, "sip", ARP_FLD_L3_IP4_SIP);
        LAN966X_DEBUG_BITS(IS2, "dip_eq_sip", ARP_FLD_DIP_EQ_SIP);
    } else if (val == VTSS_LAN966X_VCAP_IS2_KEY_IP4_TCP_UDP_TYPE_ID ||
               val == VTSS_LAN966X_VCAP_IS2_KEY_IP4_OTHER_TYPE_ID) {
        // IP4_TCP_UDP/IP4_OTHER
        LAN966X_DEBUG_BITS(IS2, "ip4", IP4_TCP_UDP_FLD_IP4);
        LAN966X_DEBUG_BITS(IS2, "fragment", IP4_TCP_UDP_FLD_L3_FRAGMENT);
        LAN966X_DEBUG_BITS(IS2, "frag_ofs", IP4_TCP_UDP_FLD_L3_FRAG_OFS_GT0);
        LAN966X_DEBUG_BITS(IS2, "options", IP4_TCP_UDP_FLD_L3_OPTIONS);
        LAN966X_DEBUG_BITS(IS2, "ttl", IP4_TCP_UDP_FLD_L3_TTL_GT0);
        LAN966X_DEBUG_BITS(IS2, "tos", IP4_TCP_UDP_FLD_L3_TOS);
        pr("\n");
        LAN966X_DEBUG_BITS(IS2, "dip", IP4_TCP_UDP_FLD_L3_IP4_DIP);
        LAN966X_DEBUG_BITS(IS2, "sip", IP4_TCP_UDP_FLD_L3_IP4_SIP);
        LAN966X_DEBUG_BITS(IS2, "dip_eq_sip", IP4_TCP_UDP_FLD_DIP_EQ_SIP);
        if (val == VTSS_LAN966X_VCAP_IS2_KEY_IP4_TCP_UDP_TYPE_ID) {
            LAN966X_DEBUG_BITS(IS2, "tcp", IP4_TCP_UDP_FLD_TCP);
            LAN966X_DEBUG_BITS(IS2, "l4_dport", IP4_TCP_UDP_FLD_L4_DPORT);
            LAN966X_DEBUG_BITS(IS2, "l4_sport", IP4_TCP_UDP_FLD_L4_SPORT);
            pr("\n");
            LAN966X_DEBUG_BITS(IS2, "l4_rng", IP4_TCP_UDP_FLD_L4_RNG);
            LAN966X_DEBUG_BITS(IS2, "fin", IP4_TCP_UDP_FLD_L4_FIN);
            LAN966X_DEBUG_BITS(IS2, "syn", IP4_TCP_UDP_FLD_L4_SYN);
            LAN966X_DEBUG_BITS(IS2, "rst", IP4_TCP_UDP_FLD_L4_RST);
            LAN966X_DEBUG_BITS(IS2, "psh", IP4_TCP_UDP_FLD_L4_PSH);
            LAN966X_DEBUG_BITS(IS2, "ack", IP4_TCP_UDP_FLD_L4_ACK);
            LAN966X_DEBUG_BITS(IS2, "urg", IP4_TCP_UDP_FLD_L4_URG);
            LAN966X_DEBUG_BITS(IS2, "1588_dom", IP4_TCP_UDP_FLD_L4_1588_DOM);
            LAN966X_DEBUG_BITS(IS2, "1588_ver", IP4_TCP_UDP_FLD_L4_1588_VER);
        } else {
            LAN966X_DEBUG_BITS(IS2, "proto", IP4_OTHER_FLD_L3_PROTO);
            LAN966X_DEBUG_BITS(IS2, "payload1", IP4_OTHER_FLD_L3_PAYLOAD_1);
            LAN966X_DEBUG_BITS(IS2, "payload0", IP4_OTHER_FLD_L3_PAYLOAD_0);
        }
    } else if (val == VTSS_LAN966X_VCAP_IS2_KEY_IP6_STD_TYPE_ID) {
        LAN966X_DEBUG_BITS(IS2, "ttl", IP6_STD_FLD_L3_TTL_GT0);
        LAN966X_DEBUG_BITS(IS2, "sip", IP6_STD_FLD_L3_IP6_SIP);
        LAN966X_DEBUG_BITS(IS2, "proto", IP6_STD_FLD_L3_PROTO);
    }
    pr("\n");
    return VTSS_RC_OK;
}

static vtss_rc lan966x_debug_vcap(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t *const debug_info,
                                  enum vtss_lan966x_vcap vcap,
                                  vtss_rc (* dbg)(vtss_state_t *vtss_state,
                                                  lan966x_vcap_info_t *info))
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(vcap);
    lan966x_vcap_info_t                  info = {0};
    u32                                  port, cnt, tgt = va->instance, rule_index = 0;
    int                                  i, j, found;

    pr("Name     : %s\n", va->name);
    pr("Instance : %u\n", tgt);
    pr("Rows     : %u\n", va->rows);
    pr("Sw_cnt   : %u\n", va->sw_count);
    pr("Sw_width : %u\n", va->sw_width);
    pr("Cnt_width: %u\n", va->sticky_width);
    pr("Act_width: %u\n", va->act_width);
    pr("Def_cnt  : %u\n\n", va->default_cnt);

    vtss_lan966x_debug_reg_header(pr, va->name);
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_VER(tgt)), "VER");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_ENTRY_WIDTH(tgt)), "ENTRY_WIDTH");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_ENTRY_CNT(tgt)), "ENTRY_CNT");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_ENTRY_SWCNT(tgt)), "ENTRY_SWCNT");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_ENTRY_TG_WIDTH(tgt)), "ENTRY_TG_WIDTH");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_ACTION_DEF_CNT(tgt)), "ACTION_DEF_CNT");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_ACTION_WIDTH(tgt)), "ACTION_WIDTH");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_CNT_WIDTH(tgt)), "CNT_WIDTH");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_CORE_CNT(tgt)), "CORE_CNT");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(VCAP_IF_CNT(tgt)), "IF_CNT");
    pr("\n");

    info.vcap = vcap;
    info.pr = pr;
    for (i = (va->rows + va->default_cnt - 1); i >= 0; i--) {
        if (i >= va->rows) {
            // Default action
            info.cmd = LAN966X_VCAP_CMD_READ;
            info.sel = (LAN966X_VCAP_SEL_ACTION | LAN966X_VCAP_SEL_COUNTER);
            info.addr = (i * va->sw_count);
            info.act_tg = LAN966X_VCAP_TG_X2;
            info.is_action = TRUE;
            if (lan966x_vcap_entry_cmd(vtss_state, &info) != VTSS_RC_OK) {
                continue;
            }
            port = (i - va->rows);
            pr("---------------------------------------------------------------\n");
            cnt = (info.act_tg == LAN966X_VCAP_TG_NONE ? 1 : lan966x_vcap_tg_count(info.act_tg));
            pr("%u-%u (port %u)", info.addr, info.addr + cnt - 1, port);
            pr("\n---------------------------------------------------------------\n");
            pr("%s ", lan966x_vcap_tg_txt(info.act_tg));
            VTSS_RC(dbg(vtss_state, &info));
            pr("\n");
            if (debug_info->clear) {
                info.cnt = 0;
                info.cmd = LAN966X_VCAP_CMD_WRITE;
                info.sel = LAN966X_VCAP_SEL_COUNTER;
                VTSS_RC(lan966x_vcap_entry_cmd(vtss_state, &info));
            }
            continue;
        }

        // Read each subword until a valid TG is found, the read the whole entry
        found = 0;
        cnt = 1;
        for (j = (va->sw_count - 1); j >= 0; ) {
            info.cmd = LAN966X_VCAP_CMD_READ;
            info.sel = LAN966X_VCAP_SEL_ALL;
            info.addr = (i * va->sw_count + j);
            info.key_tg = LAN966X_VCAP_TG_X1;
            info.act_tg = LAN966X_VCAP_TG_X1;
            if (lan966x_vcap_entry_cmd(vtss_state, &info) != VTSS_RC_OK ||
                info.key_tg == LAN966X_VCAP_TG_NONE ||
                lan966x_vcap_entry_cmd(vtss_state, &info) != VTSS_RC_OK) {
                j -= cnt;
                continue;
            }
            cnt = lan966x_vcap_tg_count(info.key_tg);
            j -= cnt;
            found = 1;

            // Print entry
            info.is_action = 0;
            pr("---------------------------------------------------------------\n");
            pr("%u-%u (rule %u): ", info.addr, info.addr + cnt - 1, rule_index);
            pr("\n---------------------------------------------------------------\n");
            pr("%s ", lan966x_vcap_tg_txt(info.key_tg));
            rule_index++;
            VTSS_RC(dbg(vtss_state, &info));
            pr("\n");

            // Print action
            info.is_action = 1;
            pr("%s ", lan966x_vcap_tg_txt(info.act_tg));
            VTSS_RC(dbg(vtss_state, &info));
            pr("\n");

            if (debug_info->clear) {
                info.cnt = 0;
                info.cmd = LAN966X_VCAP_CMD_WRITE;
                info.sel = LAN966X_VCAP_SEL_COUNTER;
                VTSS_RC(lan966x_vcap_entry_cmd(vtss_state, &info));
            }
        }
        if (!found && !debug_info->full) {
            break;
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_debug_acl(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    u32  port;
    BOOL header = 1;

    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        if (vtss_cmn_port2port_no(vtss_state, info, port) == VTSS_PORT_NO_NONE)
            continue;
        if (header)
            vtss_lan966x_debug_reg_header(pr, "ANA");
        header = 0;
        vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(ANA_VCAP_S2_CFG(port)), port, "S2_CFG");
    }
    if (!header)
        pr("\n");
    VTSS_RC(lan966x_debug_vcap(vtss_state, pr, info, VTSS_LAN966X_VCAP_IS2, lan966x_debug_is2));
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_vcap_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_ACL, lan966x_debug_acl, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_vcap_initialize(vtss_state_t *vtss_state, enum vtss_lan966x_vcap vcap)
{
    const struct vtss_lan966x_vcap_attrs *va = vtss_lan966x_vcap_attrs_get(vcap);
    lan966x_vcap_info_t                  info = {0};

    // Initialize entries
    info.vcap = vcap;
    info.cmd = LAN966X_VCAP_CMD_INIT;
    info.sel = LAN966X_VCAP_SEL_ENTRY;
    info.mv_size = (va->rows * va->sw_count);
    VTSS_RC(lan966x_vcap_cmd(vtss_state, &info));

    // Initialize actions and counters
    info.sel = (LAN966X_VCAP_SEL_ACTION | LAN966X_VCAP_SEL_COUNTER);
    info.mv_size = ((va->rows + va->default_cnt) * va->sw_count);
    VTSS_RC(lan966x_vcap_cmd(vtss_state, &info));

    // Enable core
    REG_WR(VCAP_CORE_MAP(va->instance), VCAP_CORE_MAP_CORE_MAP(1));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_vcap_init(vtss_state_t *vtss_state)
{
    lan966x_vcap_initialize(vtss_state, VTSS_LAN966X_VCAP_IS2);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_vcap_port_map(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        VTSS_RC(lan966x_acl_port_conf_set(vtss_state, port_no));
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_vcap_state_t *state = &vtss_state->vcap;
    vtss_vcap_obj_t   *is1 = &state->is1.obj;
    vtss_vcap_obj_t   *is2 = &state->is2.obj;
    vtss_vcap_obj_t   *es0 = &state->es0.obj;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        // IS1
        is1->max_count = (VTSS_LAN966X_IS1_CNT / 4);
        is1->max_rule_count = VTSS_LAN966X_IS1_CNT;
        is1->entry_get = lan966x_is1_entry_get;
        is1->entry_add = lan966x_is1_entry_add;
        is1->entry_del = lan966x_is1_entry_del;
        is1->entry_move = lan966x_is1_entry_move;
        state->is1_entry_update = lan966x_is1_entry_update;

        // IS2
        is2->max_count = (VTSS_LAN966X_IS2_CNT / 4);
        is2->max_rule_count = VTSS_LAN966X_IS2_CNT;
        is2->entry_get = lan966x_is2_entry_get;
        is2->entry_add = lan966x_is2_entry_add;
        is2->entry_del = lan966x_is2_entry_del;
        is2->entry_move = lan966x_is2_entry_move;
        state->is2_entry_update = lan966x_is2_entry_update;

        // ES0
        es0->max_count = VTSS_LAN966X_ES0_CNT;
        es0->max_rule_count = VTSS_LAN966X_ES0_CNT;
        es0->entry_get = lan966x_es0_entry_get;
        es0->entry_add = lan966x_es0_entry_add;
        es0->entry_del = lan966x_es0_entry_del;
        es0->entry_move = lan966x_es0_entry_move;
        state->es0_entry_update = lan966x_es0_entry_update;
        state->es0_eflow_update = lan966x_es0_eflow_update;

        // ACL
        state->acl_policer_set = lan966x_acl_policer_set;
        state->acl_port_set = lan966x_acl_port_conf_set;
        state->acl_port_counter_get = lan966x_acl_port_counter_get;
        state->acl_port_counter_clear = lan966x_acl_port_counter_clear;
        state->acl_ace_add = lan966x_ace_add;
        state->acl_ace_del = lan966x_ace_del;
        state->acl_ace_counter_get = vtss_cmn_ace_counter_get;
        state->acl_ace_counter_clear = vtss_cmn_ace_counter_clear;
        state->range_commit = lan966x_vcap_range_commit;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan966x_vcap_init(vtss_state));
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(lan966x_vcap_port_map(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
