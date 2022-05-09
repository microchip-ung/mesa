// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_VCAP

#include "vtss_jaguar2_cil.h"

#if defined(VTSS_ARCH_JAGUAR_2)

#define JR2_VCAP_ENTRY_WIDTH 32 /* Max entry/data width (32bit words) */

typedef struct {
    vtss_vcap_type_t vcap_type;          /* VCAP type */
    u32 entry[JR2_VCAP_ENTRY_WIDTH];     /* ENTRY_DAT */
    u32 mask[JR2_VCAP_ENTRY_WIDTH];      /* MASK_DAT */
    u32 action[JR2_VCAP_ENTRY_WIDTH];    /* ACTION_DAT */
    u32 counter;                         /* CNT_DAT */
    u32 tg;                              /* TG_DAT */
    u32 type;                            /* Action type */

    /* Debug print fields */
    BOOL                is_action;
    vtss_debug_printf_t pr;
} jr2_vcap_data_t;

typedef struct {
    const char *name;         /* Symbolic name */
    u32  target;              /* Target offset */
    BOOL version_new;         /* TRUE if version 2 (VCAP_VER = 1) */
    u16  sw_count;            /* Subword count */
    u16  entry_count;         /* Row count */
    u16  entry_width;         /* Entry width */
    u16  entry_words;         /* Number of entry words */
    u16  action_count;        /* Action count */
    u16  action_width;        /* Action width */
    u16  action_words;        /* Number of action words */
} jr2_vcap_props_t;

enum jr2_vcap_bank {
    JR2_VCAP_SUPER,
    JR2_VCAP_ES0
};

#define JR2_BITS_TO_WORDS(x) (((x)+31)/32)

/* CLM: One default action per lookup (6) per port (57)
   IS2: One default action per port (57) in first lookup
   IS2: One default action for second lookup
   LPM: No default action */
#define JR2_VCAP_SUPER_SW_COUNT     16
#if defined(VTSS_ARCH_SERVAL_T)
#define JR2_VCAP_SUPER_BLK_COUNT    6
#else
#define JR2_VCAP_SUPER_BLK_COUNT    8
#endif /* VTSS_ARCH_SERVAL_T */
#define JR2_VCAP_SUPER_ENTRY_COUNT  (JR2_VCAP_SUPER_BLK_COUNT * VTSS_VCAP_SUPER_ROW_CNT)
#define JR2_VCAP_SUPER_ACTION_COUNT (JR2_VCAP_SUPER_ENTRY_COUNT + 7*VTSS_CHIP_PORTS_ALL + 1)

#define JR2_VCAP_SUPER_CLM_A_ACTION_BASE JR2_VCAP_SUPER_ENTRY_COUNT
#define JR2_VCAP_SUPER_CLM_B_ACTION_BASE (JR2_VCAP_SUPER_CLM_A_ACTION_BASE + 2*VTSS_CHIP_PORTS_ALL)
#define JR2_VCAP_SUPER_CLM_C_ACTION_BASE (JR2_VCAP_SUPER_CLM_B_ACTION_BASE + 2*VTSS_CHIP_PORTS_ALL)
#define JR2_VCAP_SUPER_IS2_ACTION_BASE   (JR2_VCAP_SUPER_CLM_C_ACTION_BASE + 2*VTSS_CHIP_PORTS_ALL)

#if defined(VTSS_ARCH_JAGUAR_2_B)
#define JR2_VCAP_SUPER_ACT_WIDTH 64
#define JR2_VCAP_ES0_KEY_WIDTH   35
#define JR2_VCAP_ES0_ACT_WIDTH   271
#endif /* VTSS_ARCH_JAGUAR_2_B */

#if defined(VTSS_ARCH_JAGUAR_2_C)
#define JR2_VCAP_SUPER_ACT_WIDTH 73
#define JR2_VCAP_ES0_KEY_WIDTH   35
#define JR2_VCAP_ES0_ACT_WIDTH   308
#endif /* VTSS_ARCH_JAGUAR_2_C */

#if defined(VTSS_ARCH_SERVAL_T)
#define JR2_VCAP_SUPER_ACT_WIDTH 70
#define JR2_VCAP_ES0_KEY_WIDTH   30
#define JR2_VCAP_ES0_ACT_WIDTH   285
#endif /* VTSS_ARCH_SERVAL_T */

static const jr2_vcap_props_t jr2_vcap_info[] = {
    [JR2_VCAP_SUPER] = {
        .name = "VCAP_SUPER",
        .target = VTSS_TO_VCAP_SUPER,
        .version_new = TRUE,
        .sw_count = JR2_VCAP_SUPER_SW_COUNT,
        .entry_count = JR2_VCAP_SUPER_ENTRY_COUNT,
        .entry_width = 36,
        .entry_words = JR2_BITS_TO_WORDS(16*36), /* 16 X1 entries */
        .action_count = JR2_VCAP_SUPER_ACTION_COUNT,
        .action_width = JR2_VCAP_SUPER_ACT_WIDTH,
        .action_words = JR2_BITS_TO_WORDS(4*JR2_VCAP_SUPER_ACT_WIDTH), /* 4 X4 actions */
    },
    [JR2_VCAP_ES0] = {
        .name = "VCAP_ES0",
        .target = VTSS_TO_VCAP_ES0,
        .version_new = FALSE,
        .sw_count = 1,
        .entry_count = VTSS_JR2_ES0_CNT,
        .entry_width = JR2_VCAP_ES0_KEY_WIDTH,
        .entry_words = JR2_BITS_TO_WORDS(JR2_VCAP_ES0_KEY_WIDTH),
        .action_count = (VTSS_JR2_ES0_CNT + VTSS_CHIP_PORTS),
        .action_width = JR2_VCAP_ES0_ACT_WIDTH,
        .action_words = JR2_BITS_TO_WORDS(JR2_VCAP_ES0_ACT_WIDTH),
    },
};

/* TG values */
#define JR2_VCAP_TG_NONE 0x00
#define JR2_VCAP_TG_X1   0x01
#define JR2_VCAP_TG_X2   0x02
#define JR2_VCAP_TG_X4   0x04
#define JR2_VCAP_TG_X8   0x08
#define JR2_VCAP_TG_X16  0x10

/* VCAP types */
#define JR2_VCAP_TYPE_NONE  0
#define JR2_VCAP_TYPE_CLM_A 1
#define JR2_VCAP_TYPE_CLM_B 2
#define JR2_VCAP_TYPE_CLM_C 3
#define JR2_VCAP_TYPE_IS2   4
#define JR2_VCAP_TYPE_LPM   5
#define JR2_VCAP_TYPE_ES0   6 /* Pseudo type, not part of VCAP_SUPER */

/* VCAP type properties */
typedef struct {
    const char *name;       /* Symbolic name */
    u32        tg_width;    /* Key type-group width */
    u32        type_width;  /* Action type-group width */
} jr2_vcap_type_props_t;

static const jr2_vcap_type_props_t jr2_vcap_type_info[] = {
    [JR2_VCAP_TYPE_CLM_A] = {
        .name = "CLM-A",
        .tg_width = 5,
        .type_width = 3,
    },
    [JR2_VCAP_TYPE_CLM_B] = {
        .name = "CLM-B",
        .tg_width = 5,
        .type_width = 3,
    },
    [JR2_VCAP_TYPE_CLM_C] = {
        .name = "CLM-C",
        .tg_width = 5,
        .type_width = 3,
    },
    [JR2_VCAP_TYPE_IS2] = {
        .name = "IS2",
        .tg_width = 3,
        .type_width = 0,
    },
    [JR2_VCAP_TYPE_LPM] = {
        .name = "LPM",
        .tg_width = 4,
        .type_width = 0,
    },
    [JR2_VCAP_TYPE_ES0] = {
        .name = "ES0",
        .tg_width = 0,
        .type_width = 0,
    },
};

/* VCAP data selection */
#define JR2_VCAP_SEL_ENTRY   0x01 /* Select entry */
#define JR2_VCAP_SEL_ACTION  0x02 /* Select action */
#define JR2_VCAP_SEL_COUNTER 0x04 /* Select counter */
#define JR2_VCAP_SEL_ALL     0xff /* Select all */

/* VCAP commands */
#define JR2_VCAP_CMD_WRITE      0 /* Copy from Cache to VCAP */
#define JR2_VCAP_CMD_READ       1 /* Copy from VCAP to Cache */
#define JR2_VCAP_CMD_MOVE_DOWN  2 /* Move <count> down */
#define JR2_VCAP_CMD_MOVE_UP    3 /* Move <count> up */
#define JR2_VCAP_CMD_INITIALIZE 4 /* Write all (from cache) */

/* - VCAP ---------------------------------------------------------- */

static vtss_rc jr2_vcap_cmd(vtss_state_t *vtss_state, const jr2_vcap_props_t *vcap, u32 addr, u32 cmd, u32 sel)
{
    u32 tgt = vcap->target;
    u32 value = (VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD(cmd) |
                 (sel & JR2_VCAP_SEL_ENTRY ? 0 : VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS) |
                 (sel & JR2_VCAP_SEL_ACTION ? 0 : VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS) |
                 (sel & JR2_VCAP_SEL_COUNTER ? 0 : VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS) |
                 VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR(addr) |
                 (cmd == JR2_VCAP_CMD_INITIALIZE ? VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_CLEAR_CACHE : 0) |
                 VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT);

    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL(tgt), value);
    do {
        JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL(tgt), &value);
    } while (value & VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT);

    return VTSS_RC_OK;
}

static vtss_rc jr2_vcap_initialize(vtss_state_t *vtss_state, int bank)
{
    const jr2_vcap_props_t *vcap = &jr2_vcap_info[bank];
    u32                    tgt = vcap->target;

    VTSS_I("init %s, entry_count: %u, action_count: %u", vcap->name, vcap->entry_count, vcap->action_count);

    /* First write entries */
    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tgt),
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(vcap->entry_count * vcap->sw_count));
    VTSS_RC(jr2_vcap_cmd(vtss_state, vcap, 0, JR2_VCAP_CMD_INITIALIZE, JR2_VCAP_SEL_ALL));

    /* Then actions and counters */
    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tgt),
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(vcap->action_count * vcap->sw_count));
    VTSS_RC(jr2_vcap_cmd(vtss_state, vcap, 0, JR2_VCAP_CMD_INITIALIZE, JR2_VCAP_SEL_ACTION | JR2_VCAP_SEL_COUNTER));

    return VTSS_RC_OK;
}

static u32 jr2_vcap_type(vtss_vcap_type_t type)
{
    return (type == VTSS_VCAP_TYPE_CLM_A ? JR2_VCAP_TYPE_CLM_A :
            type == VTSS_VCAP_TYPE_CLM_B ? JR2_VCAP_TYPE_CLM_B :
            type == VTSS_VCAP_TYPE_CLM_C ? JR2_VCAP_TYPE_CLM_C :
            type == VTSS_VCAP_TYPE_IS2 ? JR2_VCAP_TYPE_IS2 :
            type == VTSS_VCAP_TYPE_LPM ? JR2_VCAP_TYPE_LPM :
            type == VTSS_VCAP_TYPE_ES0 ? JR2_VCAP_TYPE_ES0 : JR2_VCAP_TYPE_NONE);
}

static u32 jr2_vcap_key_type(vtss_vcap_key_size_t key_size)
{
    return (key_size == VTSS_VCAP_KEY_SIZE_SIXTEENTH ? JR2_VCAP_TG_X1 :
            key_size == VTSS_VCAP_KEY_SIZE_EIGHTH ? JR2_VCAP_TG_X2 :
            key_size == VTSS_VCAP_KEY_SIZE_QUARTER ? JR2_VCAP_TG_X4 :
            key_size == VTSS_VCAP_KEY_SIZE_HALF ? JR2_VCAP_TG_X8 : JR2_VCAP_TG_X16);
}

static u32 jr2_vcap_action_addr(vtss_vcap_type_t type, u32 port, u32 lookup)
{
    u32 base = (type == VTSS_VCAP_TYPE_IS2 ? JR2_VCAP_SUPER_IS2_ACTION_BASE :
                type == VTSS_VCAP_TYPE_CLM_A ? JR2_VCAP_SUPER_CLM_A_ACTION_BASE :
                type == VTSS_VCAP_TYPE_CLM_B ? JR2_VCAP_SUPER_CLM_B_ACTION_BASE :
                type == VTSS_VCAP_TYPE_CLM_C ? JR2_VCAP_SUPER_CLM_C_ACTION_BASE :
                type == VTSS_VCAP_TYPE_ES0 ? VTSS_JR2_ES0_CNT : 0);
    u32 sw_cnt = (type == VTSS_VCAP_TYPE_ES0 ? 1 : JR2_VCAP_SUPER_SW_COUNT);

    return ((base + lookup * VTSS_CHIP_PORTS_ALL + port) * sw_cnt);
}

static const jr2_vcap_props_t *jr2_vcap_type2info(vtss_vcap_type_t type)
{
    return &jr2_vcap_info[type == VTSS_VCAP_TYPE_ES0 ? JR2_VCAP_ES0 : JR2_VCAP_SUPER];
}

static u32 jr2_vcap_entry_addr(vtss_state_t *vtss_state, vtss_vcap_type_t type, vtss_vcap_idx_t *idx)
{
    const jr2_vcap_props_t *vcap = jr2_vcap_type2info(type);
    vtss_vcap_super_obj_t  *vcap_super = &vtss_state->vcap.vcap_super;
    u32                    i, addr = idx->row;
    BOOL                   found = FALSE;

    if (vcap->version_new) {
        for (i = 0; i < vcap_super->block.max_count; i++) {
            if (vcap_super->block_type[i] == type) {
                found = TRUE;
                break;
            }
            addr += vcap_super->row_count;
        }
        if (!found) {
            VTSS_E("%s not found", vtss_vcap_type_txt(type));
            return 0;
        }
        addr *= vcap->sw_count;
        if (vtss_state->misc.jr2_a) {
            /* Revision A, use last column */
            addr += vcap->sw_count;
        } else {
            /* Revision B, use specified column */
            addr += ((idx->col + 1) * vcap->sw_count/vtss_vcap_key_rule_count(idx->key_size));
        }
    } else {
        addr++;
    }
    return (vcap->entry_count * vcap->sw_count - addr);
}

static vtss_rc jr2_vcap_entry_cmd(vtss_state_t *vtss_state,
                                  jr2_vcap_data_t *data, u32 addr_base, u32 addr_count, u32 cmd, u32 sel)
{
    const jr2_vcap_props_t      *vcap = jr2_vcap_type2info(data->vcap_type);
    const jr2_vcap_type_props_t *type_props;
    u32                         addr, i, j, count, jr2_type, tg, tgw, w, value, mask, cnt;
    u32                         action_offs = 0, entry_offs = 0, tgt = vcap->target;
    BOOL                        is2;

    if ((jr2_type = jr2_vcap_type(data->vcap_type)) == JR2_VCAP_TYPE_NONE) {
        VTSS_E("unknown VCAP type");
        return VTSS_RC_ERROR;
    }
    type_props = &jr2_vcap_type_info[jr2_type];

    is2 = (jr2_type == JR2_VCAP_TYPE_IS2 ? 1 : 0);

    /* Process subwords */
    for (i = 0; i < addr_count; i++) {
        addr = (addr_base + i);
        if (cmd == JR2_VCAP_CMD_READ) {
            VTSS_RC(jr2_vcap_cmd(vtss_state, vcap, addr, cmd, sel));
        }

        /* Entry */
        if (sel & JR2_VCAP_SEL_ENTRY) {
            count = JR2_BITS_TO_WORDS(vcap->entry_width);
            for (j = 0; j < count; j++) {
                if (cmd == JR2_VCAP_CMD_READ && i == 0 && j == 0) {
                    /* Read TG for first word in base address */
                    if (type_props->tg_width) {
                        JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tgt, j), &value);
                        JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tgt, j), &mask);
                        tgw = ((addr % 16) == 0 ? type_props->tg_width :   /* Offset 16 */
                               (addr % 8) == 0 ? (is2 ? 2 : 4) :           /* Offset 8 */
                               (addr % 4) == 0 ? (is2 ? 1 : 3) :           /* Offset 4,12 */
                               (addr % 2) == 0 ? (is2 ? 0 : 2) :           /* Offset 2,6,10,14 */
                               (is2 ? 0 : 1));                             /* Offset 1,3,5,7,9,11,13,15 */
                        tg = (VTSS_EXTRACT_BITFIELD(value, 0, tgw) & ~mask);
                        tg = (is2 ? (tg << 2) : tg);
                    } else {
                        JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_RULE_ENA(tgt), &tg);
                    }
                    data->tg = ((tg & JR2_VCAP_TG_X1) ? JR2_VCAP_TG_X1 :
                                (tg & JR2_VCAP_TG_X2) ? JR2_VCAP_TG_X2 :
                                (tg & JR2_VCAP_TG_X4) ? JR2_VCAP_TG_X4 :
                                (tg & JR2_VCAP_TG_X8) ? JR2_VCAP_TG_X8 :
                                (tg & JR2_VCAP_TG_X16) ? JR2_VCAP_TG_X16 : JR2_VCAP_TG_NONE);
                }

                /* Calculate data and TG width */
                tg = data->tg;
                tgw = ((j != 0 || type_props->tg_width == 0 || tg == JR2_VCAP_TG_NONE) ? 0 :
                       (tg > JR2_VCAP_TG_X8 && (addr % 16) == 0) ? 5 :
                       (tg > JR2_VCAP_TG_X4 && (addr % 8) == 0) ? 4 :
                       (tg > JR2_VCAP_TG_X2 && (addr % 4) == 0) ? 3 :
                       (tg > JR2_VCAP_TG_X1 && (addr % 2) == 0) ? 2 : 1);
                tgw = (is2 ? (tgw < 2 ? 0 : tgw - 2) : tgw);
                w = (vcap->entry_width % 32);
                w = ((j == (count - 1) && w != 0 ? w : 32) - tgw);
                if (cmd == JR2_VCAP_CMD_READ) {
                    /* Read from entry cache */
                    JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tgt, j), &value);
                    JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tgt, j), &mask);
                    JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tgt, 0), &cnt);
                    VTSS_N("addr: %u, j: %u, value/mask: 0x%08x/%08x, cnt: %u", addr, j, value, mask, cnt);
                    vtss_bs_set(data->entry, entry_offs, w, value >> tgw);
                    vtss_bs_set(data->mask, entry_offs, w, ~mask >> tgw);
                } else {
                    /* Write to entry cache */
                    tg = (is2 ? (data->tg >> 2) : data->tg);
                    value = ((vtss_bs_get(data->entry, entry_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(tg, 0, tgw));
                    mask = ((vtss_bs_get(data->mask, entry_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(0xff, 0, tgw));
                    VTSS_N("addr: %u, j: %u, value/mask: 0x%08x/%08x", addr, j, value, ~mask);
                    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tgt, j), value);
                    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tgt, j), ~mask);
                    if (type_props->tg_width == 0 && j == 0) {
                        JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_RULE_ENA(tgt), tg);
                    }
                }
                entry_offs += w;
            }
        }

        /* Action */
        if ((sel & JR2_VCAP_SEL_ACTION) && (i == 0 || i < data->type)) {
            count = JR2_BITS_TO_WORDS(vcap->action_width);
            for (j = 0; j < count; j++) {
                if (cmd == JR2_VCAP_CMD_READ && i == 0 && j == 0) {
                    /* Read TG for first word in base address */
                    if (type_props->type_width) {
                        tgw = ((addr % 4) == 0 ? 3 : (addr % 2) == 0 ? 2 : 1);
                        JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(tgt, j), &value);
                        tg = VTSS_EXTRACT_BITFIELD(value, 0, tgw);
                        data->type = ((tg & JR2_VCAP_TG_X1) ? JR2_VCAP_TG_X1 :
                                      (tg & JR2_VCAP_TG_X2) ? JR2_VCAP_TG_X2 :
                                      (tg & JR2_VCAP_TG_X4) ? JR2_VCAP_TG_X4 : JR2_VCAP_TG_NONE);
                    } else {
                        data->type = (is2 ? JR2_VCAP_TG_X4 : JR2_VCAP_TG_X1);
                    }
                }

                /* Calculate data and TG width */
                tgw = 0;
                if (j == 0 && type_props->type_width != 0) {
                    tgw = (((addr & 1) || data->type == JR2_VCAP_TG_X1) ? 1 :
                           ((addr % 4) == 0 && data->type == JR2_VCAP_TG_X4) ? 3 : 2);
                }
                w = (vcap->action_width % 32);
                w = ((j == (count - 1) && w != 0 ? w : 32) - tgw);
                if (cmd == JR2_VCAP_CMD_READ) {
                    /* Read from action cache */
                    JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(tgt, j), &value);
                    VTSS_N("addr: %u, j: %u, action: 0x%08x", addr, j, value);
                    vtss_bs_set(data->action, action_offs, w, value >> tgw);
                } else {
                    /* Write to action cache */
                    value = ((vtss_bs_get(data->action, action_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(data->type, 0, tgw));
                    VTSS_N("addr: %u, j: %u, action: 0x%08x", addr, j, value);
                    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(tgt, j), value);
                }
                action_offs += w;
            }
        }

        if ((sel & JR2_VCAP_SEL_COUNTER) && i == 0) {
            if (cmd == JR2_VCAP_CMD_READ) {
                JR2_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tgt, 0), &data->counter);
            } else {
                JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tgt, 0), data->counter);
            }
        }

        if (cmd == JR2_VCAP_CMD_WRITE) {
            VTSS_RC(jr2_vcap_cmd(vtss_state, vcap, addr, cmd, sel));
        }
    } /* Address loop */
    if (vcap->version_new && vtss_state->misc.jr2_a) {
        /* Revision A: Dummy read of unused subword in column 15 */
        VTSS_RC(jr2_vcap_cmd(vtss_state, vcap, 15, JR2_VCAP_CMD_READ, sel));
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_vcap_entry_del(vtss_state_t *vtss_state, vtss_vcap_type_t type, vtss_vcap_idx_t *idx)
{
    const jr2_vcap_props_t *vcap = jr2_vcap_type2info(type);
    u32                    addr = jr2_vcap_entry_addr(vtss_state, type, idx);
    u32                    size = (vcap->version_new ? jr2_vcap_key_type(idx->key_size) : JR2_VCAP_TG_X1);

    VTSS_I("%s, row: %u, col: %u, addr: %u", vcap->name, idx->row, idx->col, addr);
    if (!vcap->version_new) {
        JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_RULE_ENA(vcap->target), 0);
    }
    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(vcap->target),
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(size - 1));
    return jr2_vcap_cmd(vtss_state, vcap, addr, JR2_VCAP_CMD_INITIALIZE, JR2_VCAP_SEL_ALL);
}

static vtss_rc jr2_vcap_entry_move(vtss_state_t *vtss_state,
                                   vtss_vcap_type_t type, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    const jr2_vcap_props_t *vcap = jr2_vcap_type2info(type);
    u32                    addr, cnt = (vcap->sw_count/vtss_vcap_key_rule_count(idx->key_size));

    if (count == 0) {
        VTSS_E("illegal count zero");
        return VTSS_RC_ERROR;
    }
    addr = (jr2_vcap_entry_addr(vtss_state, type, idx) - (count - 1) * cnt);
    VTSS_I("%s, row: %u, col: %u, %s, count: %u, up: %u, addr: %u",
           vcap->name, idx->row, idx->col, vtss_vcap_key_size2txt(idx->key_size), count, up, addr);
    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(vcap->target),
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(vcap->version_new ? (cnt - 1) : 1) |
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(count * cnt - 1));
    return jr2_vcap_cmd(vtss_state, vcap, addr, up ? JR2_VCAP_CMD_MOVE_UP : JR2_VCAP_CMD_MOVE_DOWN, JR2_VCAP_SEL_ALL);
}

static vtss_rc jr2_vcap_entry_get(vtss_state_t *vtss_state,
                                  vtss_vcap_type_t type, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    const jr2_vcap_props_t *vcap = jr2_vcap_type2info(type);
    u32                    addr;
    jr2_vcap_data_t        data;

    addr = jr2_vcap_entry_addr(vtss_state, type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u", vcap->name, idx->row, idx->col, addr);
    data.vcap_type = type;
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, &data, addr, 1, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_COUNTER));
    *counter = data.counter;
    if (clear) {
        data.counter = 0;
        VTSS_RC(jr2_vcap_entry_cmd(vtss_state, &data, addr, 1, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_COUNTER));
    }
    return jr2_vcap_cmd(vtss_state, vcap, addr, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_COUNTER);
}

/* - VCAP_SUPER ---------------------------------------------------- */

static vtss_rc jr2_vcap_super_block_map(vtss_state_t *vtss_state, u32 block, vtss_vcap_type_t type)
{
    u32 max_count = vtss_state->vcap.vcap_super.block.max_count;
    u32 tgt = jr2_vcap_info[JR2_VCAP_SUPER].target;

    VTSS_I("block: %i, type: %s", block, vtss_vcap_type_txt(type));

    if (block >= max_count) {
        VTSS_E("block: %u, max_count: %u", block, max_count);
        return VTSS_RC_ERROR;
    }
    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_IDX(tgt),
           VTSS_F_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_IDX_CORE_IDX(JR2_VCAP_SUPER_BLK_COUNT - block - 1));
    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_MAP(tgt),
           VTSS_F_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_MAP_CORE_MAP(jr2_vcap_type(type)));
    return VTSS_RC_OK;
}

static vtss_rc jr2_vcap_super_block_move(vtss_state_t *vtss_state, u32 block, BOOL up)
{
    const jr2_vcap_props_t *vcap = &jr2_vcap_info[JR2_VCAP_SUPER];
    vtss_vcap_super_obj_t  *vcap_super = &vtss_state->vcap.vcap_super;
    u32                    addr, cnt, max_count = vtss_state->vcap.vcap_super.block.max_count;

    if (block >= max_count) {
        VTSS_E("block: %u, max_count: %u", block, max_count);
        return VTSS_RC_ERROR;
    }
    cnt = (vcap_super->row_count * vcap->sw_count);
    addr = ((JR2_VCAP_SUPER_BLK_COUNT - block - 1) * cnt);
    VTSS_I("block: %i, up: %u, addr: %u, cnt: %u", block, up, addr, cnt);

    JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(vcap->target),
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(cnt - 1) |
           VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(cnt - 1));
    VTSS_RC(jr2_vcap_cmd(vtss_state, vcap, addr, up ? JR2_VCAP_CMD_MOVE_UP : JR2_VCAP_CMD_MOVE_DOWN, JR2_VCAP_SEL_ALL));

    return VTSS_RC_OK;
}

/* - VCAP ---------------------------------------------------------- */

static u32 jr2_act_get(jr2_vcap_data_t *data, u32 offs, u32 len)
{
    return vtss_bs_get(data->action, offs, len);
}

static void jr2_act_set(jr2_vcap_data_t *data, u32 offs, u32 len, u32 value)
{
    vtss_bs_set(data->action, offs, len, len == 1 ? (value ? 1 : 0) : value);
}

static void jr2_act_ena_set(jr2_vcap_data_t *data, u32 offs_ena, u32 offs, u32 len, u32 enable, u32 value)
{
    vtss_bs_set(data->action, offs_ena, 1, enable ? 1 : 0);
    vtss_bs_set(data->action, offs, len, enable ? value : 0);
}

static u32 jr2_entry_bs_get(jr2_vcap_data_t *data, u32 offs, u32 len)
{
    return vtss_bs_get(data->entry, offs, len);
}

static u32 jr2_mask_bs_get(jr2_vcap_data_t *data, u32 offs, u32 len)
{
    return vtss_bs_get(data->mask, offs, len);
}

static void jr2_vcap_key_set(jr2_vcap_data_t *data, u32 offset, u32 width, u32 value, u32 mask)
{
    VTSS_N("offset: %u, width: %u, value: 0x%08x, mask: 0x%08x", offset, width, value, mask);

    if (width > 32) {
        VTSS_E("illegal width: %u, offset: %u", width, offset);
    } else {
        vtss_bs_set(data->entry, offset, width, value & mask); /* Avoid 'match-off' */
        vtss_bs_set(data->mask, offset , width, mask);
    }
}

static void jr2_vcap_key_bytes_set(jr2_vcap_data_t *data, u32 offset, u8 *val, u8 *msk, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++) {
        jr2_vcap_key_set(data, offset + (count - i - 1) * 8, 8, val[i], msk[i]);
    }
}

static void jr2_vcap_key_bit_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_bit_t fld)
{
    jr2_vcap_key_set(data, offset, 1, fld == VTSS_VCAP_BIT_1 ? 1 : 0, fld == VTSS_VCAP_BIT_ANY ? 0 : 1);
}

static void jr2_ace_key_bit_set(jr2_vcap_data_t *data, u32 offset, vtss_ace_bit_t fld)
{
    jr2_vcap_key_set(data, offset, 1, fld == VTSS_ACE_BIT_1 ? 1 : 0, fld == VTSS_ACE_BIT_ANY ? 0 : 1);
}

static void jr2_ace_key_bit_inv_set(jr2_vcap_data_t *data, u32 offset, vtss_ace_bit_t fld)
{
    jr2_vcap_key_set(data, offset, 1, fld == VTSS_ACE_BIT_0 ? 1 : 0, fld == VTSS_ACE_BIT_ANY ? 0 : 1);
}

static void jr2_vcap_key_u3_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_u8_t *fld)
{
    jr2_vcap_key_set(data, offset, 3, fld->value, fld->mask);
}

static void jr2_vcap_key_u8_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_u8_t *fld)
{
    jr2_vcap_key_set(data, offset, 8, fld->value, fld->mask);
}

static void jr2_vcap_key_u16_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_u16_t *fld)
{
    jr2_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 2);
}

static void jr2_vcap_key_u32_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_u32_t *fld)
{
    jr2_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 4);
}

static void jr2_vcap_key_u40_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_u40_t *fld)
{
    jr2_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 5);
}

static void jr2_vcap_key_u48_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_u48_t *fld)
{
    jr2_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 6);
}

static void jr2_vcap_key_vid_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_vid_t *fld)
{
    jr2_vcap_key_set(data, offset, 12, fld->value, fld->mask);
}

static void jr2_vcap_key_ipv4_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_ip_t *fld)
{
    jr2_vcap_key_set(data, offset, 32, fld->value, fld->mask);
}

static void jr2_vcap_key_u128_set(jr2_vcap_data_t *data, u32 offset, vtss_vcap_u128_t *fld)
{
    jr2_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 16);
}

static void jr2_debug_bits(jr2_vcap_data_t *data, const char *name, u32 offset, u32 len)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 i,j;
    int                 n;

    pr("%s:", name);
    for (i = 0; i < len; i++) {
        j = (len - 1 - i);
        if (i != 0) {
            if (len > 63 && (j % 32) == 31) {
                n = (VTSS_STRLEN(name) + 1);
                pr("\n%-*s", n, "");
            } else if ((j % 8) == 7)
                pr(".");
        }
        j += offset;
        pr("%c", data->is_action ? vtss_bs_bit_get(data->action, j) ? '1' : '0' :
           vtss_bs_bit_get(data->mask, j) ? (vtss_bs_bit_get(data->entry, j) ? '1' : '0') :
           vtss_bs_bit_get(data->entry, j) ? 'N' : 'X');
    }
    pr(len > 24 ? "\n" : " ");
}

static void jr2_debug_action_ena(jr2_vcap_data_t *data, const char *name, u32 offs, u32 offs_val, u32 len)
{
    vtss_debug_printf_t pr = data->pr;
    BOOL                enable, multi = 0;
    u32                 num = 0;
    int                 i, length = VTSS_STRLEN(name);

    if (offs_val && (offs_val - offs) != 1) {
        /* 'Enable' field consists of multiple bits */
        multi = 1;
        num = jr2_act_get(data, offs, offs_val - offs);
        enable = (num ? 1 : 0);
    } else
        enable = vtss_bs_bit_get(data->action, offs);

    for (i = 0; i < length; i++)
        pr("%c", enable ? toupper(name[i]) : tolower(name[i]));

    if (len) {
        pr(":");
        if (multi)
            pr("%u/", num);
        pr("%u", jr2_act_get(data, offs_val, len));
    }
    pr(" ");
}

/* VCAP set macros */
#define JR2_ACT_SET(vcap, fld, val)          jr2_act_set(data, vcap##_AO_##fld, vcap##_AL_##fld, val)
#define JR2_ACT_ENA_SET(vcap, fld, ena, val) jr2_act_ena_set(data, vcap##_AO_##fld##_ENA, vcap##_AO_##fld##_VAL, vcap##_AL_##fld##_VAL, ena, val)

/* VCAP debug macros */
#define JR2_DEBUG_ACT(vcap, name, fld)      jr2_debug_action(data, name, vcap##_AO_##fld, vcap##_AL_##fld)
#define JR2_DEBUG_ACT_ENA(vcap, name, fld)  jr2_debug_action_ena(data, name, vcap##_AO_##fld##_ENA, vcap##_AO_##fld##_VAL, vcap##_AL_##fld##_VAL)
#define JR2_DEBUG_ACT_BITS(vcap, name, fld) jr2_debug_bits(data, name, vcap##_AO_##fld, vcap##_AL_##fld)
#define JR2_DEBUG_BITS(vcap, name, fld)     jr2_debug_bits(data, name, vcap##_KO_##fld, vcap##_KL_##fld)

static vtss_rc jr2_is2_cnt_get(vtss_state_t *vtss_state, u32 cnt_id, u32 *counter)
{
    JR2_RD(VTSS_ANA_ACL_CNT_TBL_CNT(cnt_id), counter);
    return VTSS_RC_OK;
}

static vtss_rc jr2_is2_cnt_set(vtss_state_t *vtss_state, u32 cnt_id, u32 counter)
{
    JR2_WR(VTSS_ANA_ACL_CNT_TBL_CNT(cnt_id), counter);
    return VTSS_RC_OK;
}

static void jr2_debug_action(jr2_vcap_data_t *data, const char *name, u32 offs, u32 len)
{
    data->pr("%s:%u ", name, jr2_act_get(data, offs, len));
}

#define JR2_DEBUG_VCAP(pr, name, tgt) vtss_jr2_debug_reg(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CONST_##name(tgt), #name)

static vtss_rc jr2_debug_vcap(vtss_state_t *vtss_state,
                              vtss_vcap_type_t type,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t *const info,
                              vtss_rc (* dbg)(vtss_state_t *vtss_state, jr2_vcap_data_t *data))
{
    /*lint --e{454, 455, 456} */ // Due to VTSS_EXIT_ENTER
    const jr2_vcap_props_t *vcap = jr2_vcap_type2info(type);
    jr2_vcap_data_t        data;
    u32                    addr, count, offset, blk, port, skip, rule_index = 0, tgt = vcap->target;
    vtss_port_no_t         port_no;
    int                    i, j;
    BOOL                   mpls_terse = info->has_action && info->action & 0x0010;
    BOOL                   hits_only  = info->has_action && info->action & 0x0040;

    if (jr2_vcap_type(type) == JR2_VCAP_TYPE_NONE) {
        VTSS_E("unknown VCAP type");
        return VTSS_RC_ERROR;
    }

    vtss_debug_print_header(pr, vcap->name);

    if (info->full) {
        vtss_jr2_debug_reg_header(pr, "VCAP_CONST");
        JR2_DEBUG_VCAP(pr, VCAP_VER, tgt);
        JR2_DEBUG_VCAP(pr, ENTRY_WIDTH, tgt);
        JR2_DEBUG_VCAP(pr, ENTRY_CNT, tgt);
        JR2_DEBUG_VCAP(pr, ENTRY_SWCNT, tgt);
        JR2_DEBUG_VCAP(pr, ENTRY_TG_WIDTH, tgt);
        JR2_DEBUG_VCAP(pr, ACTION_DEF_CNT, tgt);
        JR2_DEBUG_VCAP(pr, ACTION_WIDTH, tgt);
        JR2_DEBUG_VCAP(pr, CNT_WIDTH, tgt);
        JR2_DEBUG_VCAP(pr, CORE_CNT, tgt);
        JR2_DEBUG_VCAP(pr, IF_CNT, tgt);
        pr("\n");
    }

    if (vcap->version_new && !mpls_terse) {
        vtss_jr2_debug_reg_header(pr, "VCAP_SUPER");
        for (i = 0; i < JR2_VCAP_SUPER_BLK_COUNT; i++) {
            JR2_WR(VTSS_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_IDX(tgt), i);
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_MAP(tgt), i, "CORE_MAP");
        }
        pr("\n");
    }

    data.pr = pr;

    for (i = (vcap->action_count - 1); i >= 0; i--) {
        /* Leave critical region briefly */
        VTSS_EXIT_ENTER();

        addr = (i * vcap->sw_count);
        if (i >= vcap->entry_count && !mpls_terse) {
            /* Default action */
            offset = (i - vcap->entry_count);
            blk = (offset / VTSS_CHIP_PORTS_ALL);
            if (vcap->version_new) {
                count = 4;
                if (blk < 2) {
                    data.vcap_type = VTSS_VCAP_TYPE_CLM_A;
                } else if (blk < 4) {
                    data.vcap_type = VTSS_VCAP_TYPE_CLM_B;
                } else if (blk < 6) {
                    data.vcap_type = VTSS_VCAP_TYPE_CLM_C;
                } else {
                    data.vcap_type = VTSS_VCAP_TYPE_IS2;
                }
            } else {
                count = 1;
                data.vcap_type = VTSS_VCAP_TYPE_ES0;
            }

            if (type != data.vcap_type)
                continue;

            port = (offset % VTSS_CHIP_PORTS_ALL);
            port_no = VTSS_PORT_NO_NONE;
            if (blk < 7 && !info->full) {
                /* Skip default port actions not included in port map and port list */
                skip = 1;
                for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
                    if (VTSS_CHIP_PORT(port_no) == port && info->port_list[port_no]) {
                        skip = 0;
                        break;
                    }
                }
                if (skip)
                    continue;
            }

            if (jr2_vcap_entry_cmd(vtss_state, &data, addr, count, JR2_VCAP_CMD_READ,
                                   JR2_VCAP_SEL_ACTION | JR2_VCAP_SEL_COUNTER) != VTSS_RC_OK)
                continue;

            if (hits_only && data.counter == 0)
                continue;

            /* Print default action */
            data.is_action = 1;
            pr("---------------------------------------------------------------\n");
            pr("%u-%u, %s[%u,%u]", addr, addr + count - 1, vtss_vcap_type_txt(data.vcap_type), blk & 1, port);
            if (port_no != VTSS_PORT_NO_NONE) {
                pr(" (port %u)", port_no);
            }
            pr("\n---------------------------------------------------------------\n");
            pr("X%u ", data.type);
            VTSS_RC(dbg(vtss_state, &data));
            pr("\n");

            if (info->clear) {
                data.counter = 0;
                VTSS_RC(jr2_vcap_entry_cmd(vtss_state, &data, addr, 1, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_COUNTER));
            }
            continue;
        }

        /* Entry/mask */
        if (vcap->version_new) {
            blk = ((vcap->entry_count - i - 1)/VTSS_VCAP_SUPER_ROW_CNT);
            data.vcap_type = vtss_state->vcap.vcap_super.block_type[blk];
        } else {
            data.vcap_type = VTSS_VCAP_TYPE_ES0;
        }

        /* Skip other VCAP types */
        if (type != data.vcap_type)
            continue;

        /* Read each subword until a valid TG is found, then read whole entry */
        for (j = (vcap->sw_count - 1); j >= 0; j--) {
            addr = (i * vcap->sw_count + j);
            if (jr2_vcap_entry_cmd(vtss_state, &data, addr, 1, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ALL) != VTSS_RC_OK ||
                data.tg == JR2_VCAP_TG_NONE)
                continue;

            count = data.tg;
            if (jr2_vcap_entry_cmd(vtss_state, &data, addr, count, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ALL) != VTSS_RC_OK)
                continue;

            if (hits_only && data.counter == 0)
                continue;

            /* Print entry */
            data.is_action = 0;
            pr("---------------------------------------------------------------\n");
            pr("%u-%u (rule %u): ", addr, addr + count - 1, rule_index);
            pr("\n---------------------------------------------------------------\n");
            pr("X%u ", data.tg);
            rule_index++;
            VTSS_RC(dbg(vtss_state, &data));
            pr("\n");

            /* Print action */
            data.is_action = 1;
            pr("X%u ", data.type);
            VTSS_RC(dbg(vtss_state, &data));
            pr("\n");

            if (info->clear) {
                data.counter = 0;
                VTSS_RC(jr2_vcap_entry_cmd(vtss_state, &data, addr, 1, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_COUNTER));
            }
        }
    }
    pr("\n");
    return VTSS_RC_OK;
}

/* - CLM ----------------------------------------------------------- */

typedef struct {
    vtss_vcap_u8_t   range;
    vtss_vcap_u16_t  etype;
    vtss_vcap_bit_t  etype_len;
    vtss_vcap_bit_t  ip_snap;
    vtss_vcap_bit_t  ip4;
    vtss_vcap_bit_t  ip_mc;
    vtss_vcap_ip_t   sip;
    vtss_vcap_ip_t   dip;
    vtss_vcap_bit_t  fragment;
    vtss_vcap_bit_t  options;
    vtss_vcap_u8_t   dscp;
    vtss_vcap_bit_t  tcp_udp;
    vtss_vcap_bit_t  tcp;
    vtss_vcap_u16_t  sport;
    vtss_vcap_u128_t sipv6;
    vtss_vcap_u128_t dipv6;
} jr2_clm_key_info_t;

static u32 jr2_u8_to_u32(u8 *p)
{
    return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static void jr2_u32_to_u8(u8 *p, u32 value)
{
    u32 i;

    for (i = 0; i < 4; i++) {
        p[i] = (value >> (24 - i*8));
    }
}

static void jr2_clm_range_update(vtss_vcap_vr_type_t type, u32 range, jr2_clm_key_info_t *info)
{
    u32 mask;

    if (type != VTSS_VCAP_VR_TYPE_VALUE_MASK && range != VTSS_VCAP_RANGE_CHK_NONE) {
        /* Range checker has been allocated */
        mask = (1 << range);
        info->range.mask |= mask;
        if (type == VTSS_VCAP_VR_TYPE_RANGE_INCLUSIVE)
            info->range.value |= mask;
    }
}

static void jr2_clm_l4port_update(vtss_vcap_vr_t *vr, u32 range, vtss_vcap_u16_t *val, jr2_clm_key_info_t *info)
{
    u32 mask, value;
    BOOL l4_used = 0;

    if (vr->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
        /* Value/mask */
        mask = vr->vr.v.mask;
        value = vr->vr.v.value;
        if (mask != 0) {
            l4_used = 1;
            val->value[0] = ((value >> 8) & 0xff);
            val->value[1] = (value & 0xff);
            val->mask[0] = ((mask >> 8) & 0xff);
            val->mask[1] = (mask & 0xff);
        }
    } else if (range != VTSS_VCAP_RANGE_CHK_NONE) {
        /* Range */
        l4_used = 1;
        jr2_clm_range_update(vr->type, range, info);
    }
    if (l4_used && info->ip4 == VTSS_VCAP_BIT_1) {
        /* L4 used, ignore IPv4 fragments and options */
        info->fragment = VTSS_VCAP_BIT_0;
        info->options = VTSS_VCAP_BIT_0;
    }
}

static void jr2_clm_tpid_set(jr2_vcap_data_t *data, u32 offset, u32 len, vtss_is1_tag_t *tag)
{
    /* Match all frames by default */
    u32 value = CLM_TPID_UNTAG;
    u32 mask = 0;

    if (tag->tagged == VTSS_VCAP_BIT_0) {
        /* Match untagged */
        mask = 0x7;
    } else if (tag->tagged == VTSS_VCAP_BIT_1) {
        if (tag->s_tag == VTSS_VCAP_BIT_1) {
            /* Match S-tagged or S-custom (CUSTOM_1) tagged */
            value = CLM_TPID_S_TAG;
            mask = 0x6;
        } else if (tag->s_tag == VTSS_VCAP_BIT_0) {
            /* Match C-tagged */
            value = CLM_TPID_C_TAG;
            mask = 0x7;
        } else {
            /* Matching any C/S/S-custom tagged frames is not possible, so we match everything.
               Matching a specific VID may be done to avoid matching untagged and priority-tagged frames. */
        }
    }
    jr2_vcap_key_set(data, offset, len, value, mask);
}

static void jr2_clm_qos_action_update(vtss_state_t *vtss_state,
                                      jr2_vcap_data_t *data, vtss_qos_ingress_map_id_t map_id, BOOL inner_tag)
{
    u32 sel = 0, idx = 0, key = 0, ix;

    if (map_id < VTSS_QOS_INGRESS_MAP_IDS &&
        (ix = vtss_state->qos.imap.id.entry[map_id].ix) < VTSS_QOS_INGRESS_MAP_ROWS) {
        sel = 1; /* QoS ingress map table lookup #0 */
        idx = ix;
        switch (vtss_state->qos.imap.ix[0].entry[idx].key) {
        case VTSS_QOS_INGRESS_MAP_KEY_PCP:
            key = 4;
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI:
            key = (inner_tag ? 1 : 0);
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_DSCP:
            key = 6;
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI:
            key = 7;
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC:
            key = 3;
            break;
        default:
            break;
        }
    }

    if (data->tg == JR2_VCAP_TG_X1) {
        // MLBS
        if (map_id == VTSS_QOS_INGRESS_MAP_ID_NONE) {
            JR2_ACT_SET(CLM, X1_MAP_SEL, 0);
        } else {
            // Key is hardwired to TC.
            // The chip will calculate the QoS map index as (MSB..LSB): DP_ENA:1 << 8 | QOS_VAL:3 << 5 | QOS_ENA:1 << 4 | COSID_VAL:3 << 1 | COSID_ENA:1.
            JR2_ACT_SET(CLM, X1_MAP_SEL, sel);
            JR2_ACT_SET(CLM, X1_COSID_ENA, (idx >> 0) & 0x01);
            JR2_ACT_SET(CLM, X1_COSID_VAL, (idx >> 1) & 0x07);
            JR2_ACT_SET(CLM, X1_QOS_ENA,   (idx >> 4) & 0x01);
            JR2_ACT_SET(CLM, X1_QOS_VAL,   (idx >> 5) & 0x07);
            JR2_ACT_SET(CLM, X1_DP_VAL,    (idx >> 8) & 0x01);
        }
    } else if (data->tg == JR2_VCAP_TG_X2) {
        JR2_ACT_SET(CLM, CLAS_MAP_SEL, sel);
        JR2_ACT_SET(CLM, CLAS_MAP_IDX, idx);
        JR2_ACT_SET(CLM, CLAS_MAP_KEY, key);
    } else {
        JR2_ACT_SET(CLM, X4_MAP_SEL, sel);
        JR2_ACT_SET(CLM, X4_MAP_IDX, idx);
        JR2_ACT_SET(CLM, X4_MAP_KEY, key);
    }
}

static void jr2_clm_action_update(vtss_state_t *vtss_state, jr2_vcap_data_t *data, vtss_is1_data_t *is1)
{
    BOOL                      inner_tag = (is1->flags & VTSS_IS1_FLAG_MAP_INNER ? 1 : 0);
    vtss_qos_ingress_map_id_t map_id = (is1->flags & VTSS_IS1_FLAG_MAP_ID ? is1->map_id : VTSS_QOS_INGRESS_MAP_ID_NONE);
    jr2_clm_qos_action_update(vtss_state, data, map_id, inner_tag);
}

static void jr2_clm_port_sel_update(jr2_vcap_data_t *data, vtss_is1_key_t *key)
{
    VTSS_D("key %p  port_hit %u  looped %u  masqueraded %u", key, key->port_hit, key->looped, key->masqueraded);

    /* If no specific match type (port_hit - masqueraded - looped) is selected, matching is done on port and masqueraded frames */
    /* If a specific match type (port_hit - masqueraded - looped) is selected, matching is done on port or masqueraded or looped frames */
    u32 value = key->port_hit ? 0 : key->looped ? 1 : 2;
    u32 mask = (key->port_hit || key->masqueraded || key->looped) ? 0x03 : 0x01;

    if (data->tg == JR2_VCAP_TG_X16) {
        jr2_vcap_key_set(data, CLM_KO_X16_PORT_SEL, CLM_KL_X16_PORT_SEL, value, mask);
    } else {
        jr2_vcap_key_set(data, CLM_KO_X8_PORT_SEL, CLM_KL_X8_PORT_SEL, value, mask);
    }
}

static vtss_rc jr2_clm_entry_add(vtss_state_t *vtss_state,
                                 vtss_vcap_type_t type, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    jr2_vcap_data_t        jr2_data, *data = &jr2_data;
    u32                    addr, port, oam = 0;
    u32                    x8_type = CLM_X8_TYPE_NORMAL;
    u32                    x8_mask = VTSS_BITMASK(CLM_KL_X8_TYPE);
    vtss_is1_data_t        *is1 = &vcap_data->u.is1;
    vtss_is1_key_t         *key = &is1->entry->key;
    vtss_is1_tag_t         *tag;
    vtss_is1_action_t      *action = &is1->entry->action;
    vtss_is1_frame_etype_t *etype = &key->frame.etype;
    vtss_is1_frame_llc_t   *llc = &key->frame.llc;
    vtss_is1_frame_snap_t  *snap = &key->frame.snap;
    vtss_is1_frame_ipv4_t  *ipv4 = &key->frame.ipv4;
    vtss_is1_frame_ipv6_t  *ipv6 = &key->frame.ipv6;
    vtss_vcap_u8_t         *proto = NULL;
    vtss_vcap_vr_t         *dscp, *sport, *dport;
    vtss_vcap_vid_t        g_idx = key->g_idx;
    vtss_vcap_bit_t        g_idx_isdx = (g_idx.mask ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_ANY);
    vtss_port_no_t         port_no;
    jr2_clm_key_info_t     info;
    BOOL                   sipv6_copy = 0, y1731 = FALSE, ip = 0;

    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = type;

    if (key->type == VTSS_IS1_TYPE_MPLS_MLL) {
        data->tg   = JR2_VCAP_TG_X4;
        data->type = JR2_VCAP_TG_X4;
    } else if (key->type == VTSS_IS1_TYPE_MPLS_MLBS) {
        data->tg   = JR2_VCAP_TG_X1;
        data->type = JR2_VCAP_TG_X1;
    } else if (key->key_type == VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR) {
        /* Full key (Jaguar-2 revision B or later) */
        data->tg   = JR2_VCAP_TG_X16;
        data->type = JR2_VCAP_TG_X4;
    } else if (key->key_type == VTSS_VCAP_KEY_TYPE_DOUBLE_TAG) {
        data->tg   = JR2_VCAP_TG_X2;
        data->type = JR2_VCAP_TG_X2;
    } else {
        data->tg   = JR2_VCAP_TG_X8;
        data->type = JR2_VCAP_TG_X4;
    }

    addr = jr2_vcap_entry_addr(vtss_state, type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u", vtss_vcap_type_txt(type), idx->row, idx->col, addr);

    /* Save this key values to be used by jr2_clm_entry_update_masq_hit_ena later */
    vcap_data->port_hit = key->port_hit;
    vcap_data->looped = key->looped;
    vcap_data->masqueraded = key->masqueraded;

    /* Setup key fields */
    VTSS_MEMSET(&info, 0, sizeof(info));
    switch (key->type) {
    case VTSS_IS1_TYPE_ANY:
        if (key->key_type == VTSS_VCAP_KEY_TYPE_IP_ADDR) {
            x8_mask = 0;
        }
        break;
    case VTSS_IS1_TYPE_ETYPE:
        info.etype_len = VTSS_VCAP_BIT_1;
        info.ip_snap = VTSS_VCAP_BIT_0;
        info.ip4 = VTSS_VCAP_BIT_0;
        info.etype = etype->etype;
        info.sip.value = jr2_u8_to_u32(etype->data.value);
        info.sip.mask = jr2_u8_to_u32(etype->data.mask);
        sipv6_copy = 1;
        if ((etype->etype.value[0] == 0x89) && (etype->etype.value[1] == 0x02) && (etype->etype.mask[0] == 0xFF) && (etype->etype.mask[1] == 0xFF)) {   /* This is OAM catching rule */
            y1731 = TRUE;
            info.tcp_udp = VTSS_VCAP_BIT_1;     /* This must be set to indicate Y.1731 frame */
            info.sport.value[1] = etype->mel.value;
            info.sport.mask[1] = etype->mel.mask;
        }
        break;
    case VTSS_IS1_TYPE_LLC:
        info.etype_len = VTSS_VCAP_BIT_0;
        info.ip_snap = VTSS_VCAP_BIT_0;
        info.ip4 = VTSS_VCAP_BIT_0;
        info.etype.value[0] = llc->data.value[0];
        info.etype.mask[0] = llc->data.mask[0];
        info.etype.value[1] = llc->data.value[1];
        info.etype.mask[1] = llc->data.mask[1];
        info.sip.value = jr2_u8_to_u32(&llc->data.value[2]);
        info.sip.mask = jr2_u8_to_u32(&llc->data.mask[2]);
        sipv6_copy = 1;
        break;
    case VTSS_IS1_TYPE_SNAP:
        info.etype_len = VTSS_VCAP_BIT_0;
        info.ip_snap = VTSS_VCAP_BIT_1;
        info.ip4 = VTSS_VCAP_BIT_0;
        info.etype.value[0] = snap->data.value[0];
        info.etype.mask[0] = snap->data.mask[0];
        info.etype.value[1] = snap->data.value[1];
        info.etype.mask[1] = snap->data.mask[1];
        info.sip.value = jr2_u8_to_u32(&snap->data.value[2]);
        info.sip.mask = jr2_u8_to_u32(&snap->data.mask[2]);
        sipv6_copy = 1;
        break;
    case VTSS_IS1_TYPE_IPV4:
    case VTSS_IS1_TYPE_IPV6:
        ip = 1;
        if (key->key_type == VTSS_VCAP_KEY_TYPE_IP_ADDR) {
            x8_type = CLM_X8_TYPE_5TUPLE_IP4;
        }
        info.etype_len = VTSS_VCAP_BIT_1;
        info.ip_snap = VTSS_VCAP_BIT_1;
        if (key->type == VTSS_IS1_TYPE_IPV4) {
            info.ip4 = VTSS_VCAP_BIT_1;
            info.ip_mc = ipv4->ip_mc;
            info.fragment = ipv4->fragment;
            info.options = ipv4->options;
            proto = &ipv4->proto;
            dscp = &ipv4->dscp;
            info.sip = ipv4->sip;
            info.dip = ipv4->dip;
            jr2_u32_to_u8(&info.sipv6.value[12], ipv4->sip.value);
            jr2_u32_to_u8(&info.sipv6.mask[12], ipv4->sip.mask);
            jr2_u32_to_u8(&info.dipv6.value[12], ipv4->dip.value);
            jr2_u32_to_u8(&info.dipv6.mask[12], ipv4->dip.mask);
            sport = &ipv4->sport;
            dport = &ipv4->dport;
        } else {
            info.ip4 = VTSS_VCAP_BIT_0;
            info.ip_mc = ipv6->ip_mc;
            proto = &ipv6->proto;
            dscp = &ipv6->dscp;
            info.sip.value = jr2_u8_to_u32(&ipv6->sip.value[12]);
            info.sip.mask = jr2_u8_to_u32(&ipv6->sip.mask[12]);
            info.dip.value = jr2_u8_to_u32(&ipv6->dip.value[12]);
            info.dip.mask = jr2_u8_to_u32(&ipv6->dip.mask[12]);
            info.sipv6 = ipv6->sip;
            info.dipv6 = ipv6->dip;
            sport = &ipv6->sport;
            dport = &ipv6->dport;
        }
        if (dscp->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            info.dscp.value = dscp->vr.v.value;
            info.dscp.mask = dscp->vr.v.mask;
        }
        jr2_clm_range_update(dscp->type, is1->dscp_range, &info);
        if (vtss_vcap_udp_tcp_rule(proto)) {
            info.tcp_udp = VTSS_VCAP_BIT_1;
            info.tcp = (proto->value == 6 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);

            /* Destination port/range */
            jr2_clm_l4port_update(dport, is1->dport_range, &info.etype, &info);

            /* Source port/range */
            jr2_clm_l4port_update(sport, is1->sport_range, &info.sport, &info);
        } else if (proto->mask == 0xff) {
            /* Not UDP/TCP */
            info.tcp_udp = VTSS_VCAP_BIT_0;
            info.etype.value[1] = proto->value;
            info.etype.mask[1] = proto->mask;
        }
        break;
    case VTSS_IS1_TYPE_MPLS_MLL:
        break;
    case VTSS_IS1_TYPE_MPLS_MLBS:
        break;
    default:
        VTSS_E("illegal frame type");
        return VTSS_RC_ERROR;
    }

    if (sipv6_copy) {
        /* Copy ETYPE/LLC/SNAP data to IPv6 SIP field */
        jr2_u32_to_u8(&info.sipv6.value[0], info.sip.value);
        jr2_u32_to_u8(&info.sipv6.mask[0], info.sip.mask);
    }

    if (data->tg == JR2_VCAP_TG_X1) {
        /* X1 key: MLBS */
        jr2_vcap_key_set    (data, CLM_KO_X1_G_IDX,    CLM_KL_X1_G_IDX, key->g_idx.value, key->g_idx.mask);
        jr2_vcap_key_bit_set(data, CLM_KO_X1_FIRST,    is1->lookup == 0 ? VTSS_VCAP_BIT_0 : (is1->lookup == 1 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_ANY));
        if (key->frame.mlbs.label != 0) {
            jr2_vcap_key_set(data, CLM_KO_X1_LBL0,     CLM_KL_X1_LBL0, key->frame.mlbs.label, VTSS_BITMASK(CLM_KL_X1_LBL0));
        } else {
            jr2_vcap_key_set(data, CLM_KO_X1_LBL0,     CLM_KL_X1_LBL0, 0, 0);   // Wildcard
        }
        jr2_vcap_key_bit_set(data, CLM_KO_X1_SBIT0,    key->frame.mlbs.s_bit);
        jr2_vcap_key_bit_set(data, CLM_KO_X1_TTL0_EXP, key->frame.mlbs.ttl_expiry);
    } else if (data->tg == JR2_VCAP_TG_X2 && (is1->flags & VTSS_IS1_FLAG_TRI_VID)) {
        /* X2 key, TRI_VID */
        jr2_vcap_key_set(data, CLM_KO_X2_TYPE, CLM_KL_X2_TYPE, CLM_X2_TYPE_TRI_VID, VTSS_BITMASK(CLM_KL_X2_TYPE));
        jr2_vcap_key_bit_set(data, CLM_KO_X2_FIRST, is1->lookup ? VTSS_VCAP_BIT_0 : VTSS_VCAP_BIT_1);
        if ((port_no = vtss_cmn_first_port_no_get(vtss_state, key->port_list)) != VTSS_PORT_NO_NONE) {
            port = VTSS_CHIP_PORT(port_no);
            jr2_vcap_key_set(data, CLM_KO_TRI_VID_IGR_PORT, CLM_KL_TRI_VID_IGR_PORT, port, VTSS_BITMASK(CLM_KL_TRI_VID_IGR_PORT));
        }

        /* Outer tag */
        tag = &key->tag;
        jr2_clm_tpid_set(data, CLM_KO_TRI_VID_TPID0, CLM_KL_TRI_VID_TPID0, tag);
        jr2_vcap_key_u3_set(data, CLM_KO_TRI_VID_PCP0, &tag->pcp);
        jr2_vcap_key_bit_set(data, CLM_KO_TRI_VID_DEI0, tag->dei);
        jr2_vcap_key_set(data, CLM_KO_TRI_VID_VID0, CLM_KL_TRI_VID_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);

        /* Inner tag */
        tag = &key->inner_tag;
        jr2_clm_tpid_set(data, CLM_KO_TRI_VID_TPID1, CLM_KL_TRI_VID_TPID1, tag);
        jr2_vcap_key_u3_set(data, CLM_KO_TRI_VID_PCP1, &tag->pcp);
        jr2_vcap_key_bit_set(data, CLM_KO_TRI_VID_DEI1, tag->dei);
        jr2_vcap_key_set(data, CLM_KO_TRI_VID_VID1, CLM_KL_TRI_VID_VID1, tag->vid.vr.v.value, tag->vid.vr.v.mask);

        if (y1731) {
            /* Y1731 entry with MEG level */
            jr2_vcap_key_set(data, CLM_KO_TRI_VID_ETYPE, CLM_KL_TRI_VID_ETYPE, 5, VTSS_BITMASK(CLM_KL_TRI_VID_ETYPE));
            jr2_vcap_key_set(data, CLM_KO_TRI_VID_VID2, CLM_KL_TRI_VID_VID2, etype->mel.value, etype->mel.mask);
        }
    } else if (data->tg == JR2_VCAP_TG_X2) {
        /* X2 key, TRI_VID_IDX */
        jr2_vcap_key_set(data, CLM_KO_X2_TYPE, CLM_KL_X2_TYPE, CLM_X2_TYPE_TRI_VID_IDX, VTSS_BITMASK(CLM_KL_X2_TYPE));
        jr2_vcap_key_bit_set(data, CLM_KO_X2_FIRST, is1->lookup ? VTSS_VCAP_BIT_0 : VTSS_VCAP_BIT_1);
        if (g_idx_isdx == VTSS_VCAP_BIT_ANY && ((port_no = vtss_cmn_first_port_no_get(vtss_state, key->port_list)) != VTSS_PORT_NO_NONE || key->cpu_port)) {
            /* G_IDX is used to match port number */
            g_idx_isdx = VTSS_VCAP_BIT_0;
            g_idx.value = (key->cpu_port ? VTSS_CHIP_PORT_CPU : VTSS_CHIP_PORT(port_no));
            g_idx.mask = 0xfff;
        }
        jr2_vcap_key_bit_set(data, CLM_KO_TRI_VID_IDX_G_IDX_ISDX, g_idx_isdx);
        jr2_vcap_key_set(data, CLM_KO_TRI_VID_IDX_G_IDX, CLM_KL_TRI_VID_IDX_G_IDX, g_idx.value, g_idx.mask);

        /* Outer tag */
        tag = &key->tag;
        jr2_clm_tpid_set(data, CLM_KO_TRI_VID_IDX_TPID0, CLM_KL_TRI_VID_IDX_TPID0, tag);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            jr2_vcap_key_set(data, CLM_KO_TRI_VID_IDX_VID0, CLM_KL_TRI_VID_IDX_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);
        }

        /* Inner tag */
        tag = &key->inner_tag;
        jr2_clm_tpid_set(data, CLM_KO_TRI_VID_IDX_TPID1, CLM_KL_TRI_VID_IDX_TPID1, tag);
        jr2_vcap_key_set(data, CLM_KO_TRI_VID_IDX_VID1, CLM_KL_TRI_VID_IDX_VID1, tag->vid.vr.v.value, tag->vid.vr.v.mask);

        /* Y1731 entry with MEG level */
        jr2_vcap_key_bit_set(data, CLM_KO_TRI_VID_IDX_Y1731, y1731 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_ANY);
        jr2_vcap_key_set(data, CLM_KO_TRI_VID_IDX_MEL_FLAG, CLM_KL_TRI_VID_IDX_MEL_FLAG, etype->mel.value, etype->mel.mask);
    } else if (data->tg == JR2_VCAP_TG_X4) {
        /* X4 key: MLL */
        jr2_vcap_key_set(data, CLM_KO_X4_TYPE, CLM_KL_X4_TYPE, CLM_X4_TYPE_MLL, VTSS_BITMASK(CLM_KL_X4_TYPE));

        if ((port_no = vtss_cmn_first_port_no_get(vtss_state, key->port_list)) != VTSS_PORT_NO_NONE) {
            port = VTSS_CHIP_PORT(port_no);
            jr2_vcap_key_set(data, CLM_KO_MLL_IGR_PORT, CLM_KL_MLL_IGR_PORT, port, VTSS_BITMASK(CLM_KL_MLL_IGR_PORT));
        }

        tag = &key->tag;
        jr2_clm_tpid_set(data, CLM_KO_MLL_TPID0, CLM_KL_MLL_TPID0, tag);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            jr2_vcap_key_set(data, CLM_KO_MLL_VID0, CLM_KL_MLL_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);
        }

        jr2_vcap_key_u48_set(data, CLM_KO_MLL_DMAC, &key->mac.dmac);
        jr2_vcap_key_u48_set(data, CLM_KO_MLL_SMAC, &key->mac.smac);
        jr2_vcap_key_set    (data, CLM_KO_MLL_ETYPE, CLM_KL_MLL_ETYPE, key->frame.mll.upstream ? 2 : 1, VTSS_BITMASK(CLM_KL_MLL_ETYPE));
    } else if (data->tg == JR2_VCAP_TG_X8) {
        /* X8 key */
        jr2_vcap_key_set(data, CLM_KO_X8_TYPE, CLM_KL_X8_TYPE, x8_type, x8_mask);
        jr2_vcap_key_bit_set(data, CLM_KO_X8_FIRST, is1->lookup ? VTSS_VCAP_BIT_0 : VTSS_VCAP_BIT_1);
        jr2_vcap_key_bit_set(data, CLM_KO_X8_G_IDX_ISDX, g_idx_isdx);
        jr2_vcap_key_set(data, CLM_KO_X8_G_IDX, CLM_KL_X8_G_IDX, g_idx.value, g_idx.mask);
        jr2_clm_port_sel_update(data, key);
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (key->port_list[port_no] == 0) {
                port = VTSS_CHIP_PORT(port_no);
                jr2_vcap_key_bit_set(data, CLM_KO_X8_PORT_MASK + port, VTSS_VCAP_BIT_0);
            }
        }
        jr2_vcap_key_bit_set(data, CLM_KO_X8_L2_MC, key->mac.dmac_mc);
        jr2_vcap_key_bit_set(data, CLM_KO_X8_L2_BC, key->mac.dmac_bc);

        /* Outer tag */
        tag = &key->tag;
        jr2_clm_tpid_set(data, CLM_KO_X8_TPID0, CLM_KL_X8_TPID0, tag);
        jr2_vcap_key_u3_set(data, CLM_KO_X8_PCP0, &tag->pcp);
        jr2_vcap_key_bit_set(data, CLM_KO_X8_DEI0, tag->dei);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            jr2_vcap_key_set(data, CLM_KO_X8_VID0, CLM_KL_X8_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);
        }
        jr2_clm_range_update(tag->vid.type, is1->vid_range, &info);

        /* Inner tag */
        tag = &key->inner_tag;
        jr2_clm_tpid_set(data, CLM_KO_X8_TPID1, CLM_KL_X8_TPID1, tag);
        jr2_vcap_key_u3_set(data, CLM_KO_X8_PCP1, &tag->pcp);
        jr2_vcap_key_bit_set(data, CLM_KO_X8_DEI1, tag->dei);
        jr2_vcap_key_set(data, CLM_KO_X8_VID1, CLM_KL_X8_VID1, tag->vid.vr.v.value, tag->vid.vr.v.mask);

        if (x8_mask == 0) {
            /* Match any frame */
        } else if (x8_type == CLM_X8_TYPE_NORMAL) {
            /* Match source or destination addresses */
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_DST_ENTRY, key->dmac_dip ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            jr2_vcap_key_u48_set(data, CLM_KO_NORMAL_SMAC, key->dmac_dip ? &key->mac.dmac : &key->mac.smac);
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_IP_MC, info.ip_mc);
            jr2_vcap_key_u16_set(data, CLM_KO_NORMAL_ETYPE, &info.etype);
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_ETYPE_LEN, info.etype_len);
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_IP_SNAP, info.ip_snap);
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_IP4, info.ip4);
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_FRAGMENT, info.fragment);
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_OPTIONS, info.options);
            jr2_vcap_key_set(data, CLM_KO_NORMAL_DSCP, CLM_KL_NORMAL_DSCP, info.dscp.value, info.dscp.mask);
            jr2_vcap_key_ipv4_set(data, CLM_KO_NORMAL_SIP, key->dmac_dip && ip ? &info.dip : &info.sip);
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_TCP_UDP, info.tcp_udp);
            jr2_vcap_key_bit_set(data, CLM_KO_NORMAL_TCP, info.tcp);
            jr2_vcap_key_u16_set(data, CLM_KO_NORMAL_SPORT, &info.sport);
            jr2_vcap_key_u8_set(data, CLM_KO_NORMAL_RANGE, &info.range);
        } else {
            jr2_vcap_key_bit_set(data, CLM_KO_5TUPLE_IP4_IP_MC, info.ip_mc);
            jr2_vcap_key_bit_set(data, CLM_KO_5TUPLE_IP4_IP4, info.ip4);
            jr2_vcap_key_bit_set(data, CLM_KO_5TUPLE_IP4_FRAGMENT, info.fragment);
            jr2_vcap_key_bit_set(data, CLM_KO_5TUPLE_IP4_OPTIONS, info.options);
            jr2_vcap_key_set(data, CLM_KO_5TUPLE_IP4_DSCP, CLM_KL_NORMAL_DSCP, info.dscp.value, info.dscp.mask);
            jr2_vcap_key_ipv4_set(data, CLM_KO_5TUPLE_IP4_DIP, &info.dip);
            jr2_vcap_key_ipv4_set(data, CLM_KO_5TUPLE_IP4_SIP, &info.sip);
            jr2_vcap_key_u8_set(data, CLM_KO_5TUPLE_IP4_PROTO, proto);
            jr2_vcap_key_bit_set(data, CLM_KO_5TUPLE_IP4_TCP_UDP, info.tcp_udp);
            jr2_vcap_key_bit_set(data, CLM_KO_5TUPLE_IP4_TCP, info.tcp);
            jr2_vcap_key_u8_set(data, CLM_KO_5TUPLE_IP4_RANGE, &info.range);
        }
    } else {
        /* X16 key */
        jr2_vcap_key_set(data, CLM_KO_X16_TYPE, CLM_KL_X16_TYPE, CLM_X16_TYPE_7TUPLE, VTSS_BITMASK(CLM_KL_X16_TYPE));
        jr2_vcap_key_bit_set(data, CLM_KO_X16_FIRST, is1->lookup ? VTSS_VCAP_BIT_0 : VTSS_VCAP_BIT_1);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_G_IDX_ISDX, g_idx_isdx);
        jr2_vcap_key_set(data, CLM_KO_X16_G_IDX, CLM_KL_X16_G_IDX, g_idx.value, g_idx.mask);
        jr2_clm_port_sel_update(data, key);
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (key->port_list[port_no] == 0) {
                port = VTSS_CHIP_PORT(port_no);
                jr2_vcap_key_bit_set(data, CLM_KO_X16_PORT_MASK + port, VTSS_VCAP_BIT_0);
            }
        }
        jr2_vcap_key_bit_set(data, CLM_KO_X16_L2_MC, key->mac.dmac_mc);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_L2_BC, key->mac.dmac_bc);

        /* Outer tag */
        tag = &key->tag;
        jr2_clm_tpid_set(data, CLM_KO_X16_TPID0, CLM_KL_X16_TPID0, tag);
        jr2_vcap_key_u3_set(data, CLM_KO_X16_PCP0, &tag->pcp);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_DEI0, tag->dei);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            jr2_vcap_key_set(data, CLM_KO_X16_VID0, CLM_KL_X16_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);
        }
        jr2_clm_range_update(tag->vid.type, is1->vid_range, &info);

        /* Inner tag */
        tag = &key->inner_tag;
        jr2_clm_tpid_set(data, CLM_KO_X16_TPID1, CLM_KL_X16_TPID1, tag);
        jr2_vcap_key_u3_set(data, CLM_KO_X16_PCP1, &tag->pcp);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_DEI1, tag->dei);
        jr2_vcap_key_set(data, CLM_KO_X16_VID1, CLM_KL_X16_VID1, tag->vid.vr.v.value, tag->vid.vr.v.mask);

        /* Match source and destination addresses */
        jr2_vcap_key_u48_set(data, CLM_KO_X16_DMAC, &key->mac.dmac);
        jr2_vcap_key_u48_set(data, CLM_KO_X16_SMAC, &key->mac.smac);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_IP_MC, info.ip_mc);
        jr2_vcap_key_u16_set(data, CLM_KO_X16_ETYPE, &info.etype);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_ETYPE_LEN, info.etype_len);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_IP_SNAP, info.ip_snap);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_IP4, info.ip4);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_FRAGMENT, info.fragment);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_OPTIONS, info.options);
        jr2_vcap_key_set(data, CLM_KO_X16_DSCP, CLM_KL_NORMAL_DSCP, info.dscp.value, info.dscp.mask);
        jr2_vcap_key_u128_set(data, CLM_KO_X16_SIP, &info.sipv6);
        jr2_vcap_key_u128_set(data, CLM_KO_X16_DIP, &info.dipv6);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_TCP_UDP, info.tcp_udp);
        jr2_vcap_key_bit_set(data, CLM_KO_X16_TCP, info.tcp);
        jr2_vcap_key_u16_set(data, CLM_KO_X16_SPORT, &info.sport);
        jr2_vcap_key_u8_set(data, CLM_KO_X16_RANGE, &info.range);
    }

    /*
     * Setup action fields
     */

    if (data->type == JR2_VCAP_TG_X1) {
        /* X1: MLBS */

        static const u8 fwd_to_next_key_map[] = {
            15,     // None       -> CLM done
            5,      // Term. PW   -> TRI_VID_IDX (this is what EVC expects)
            15,     // Label swap -> CLM done
            2,      // Label pop  -> MLBS; next is also a label
            15      // Ctrl PDU   -> CLM done
        };

        JR2_ACT_ENA_SET(CLM, X1_ISDX, action->isdx_enable, action->isdx);
        JR2_ACT_SET(CLM, X1_FWD_DIS, (action->fwd_disable ? 1 : 0));
        JR2_ACT_SET(CLM, X1_FWD_TYPE, action->mpls_fwd_type);
        JR2_ACT_SET(CLM, X1_CPU_VAL, action->cpu_queue);
        JR2_ACT_SET(CLM, X1_TC_ENA, (action->mpls_tc_enable ? 1 : 0));
        JR2_ACT_SET(CLM, X1_TTL_ENA, (action->mpls_ttl_enable ? 1 : 0));
        JR2_ACT_SET(CLM, X1_MPLS_OAM_TYPE, action->mpls_oam_detect);
        JR2_ACT_SET(CLM, X1_MPLS_MEP_ENA, (action->mpls_mep_enable ? 1 : 0));
        JR2_ACT_SET(CLM, X1_MPLS_MIP_ENA, (action->mpls_mip_enable ? 1 : 0));
        JR2_ACT_SET(CLM, X1_MPLS_OAM_FLVR, (action->mpls_oam_flavor_1 ? 1 : 0));
        JR2_ACT_SET(CLM, X1_MPLS_IP_CTRL, (action->mpls_ip_enable ? 1 : 0));
        JR2_ACT_SET(CLM, X1_PL_ENA, action->pipe_enable);
        JR2_ACT_SET(CLM, X1_PL_PT, action->pipe_pt);
        JR2_ACT_ENA_SET(CLM, X1_ISDX, action->isdx_enable, action->isdx);
        JR2_ACT_SET(CLM, X1_NXT_KEY, fwd_to_next_key_map[action->mpls_fwd_type]);
        JR2_ACT_SET(CLM, X1_NXT_W32_OFFS, 1);
        JR2_ACT_SET(CLM, X1_NXT_NORMALIZE, 1);
        JR2_ACT_SET(CLM, X1_NXT_IDX_CTRL, (action->nxt_idx_enable ? 3 : 0));        // 3: G_IDX is an ISDX, sets is-service bit which is then used by EVC TRI_VID_IDX keys
        JR2_ACT_SET(CLM, X1_NXT_IDX, action->nxt_idx);
        if (action->mpls_fwd_type == VTSS_MPLS_FWD_TYPE_TERMINATE_PW) {
            JR2_ACT_SET(CLM, X1_NXT_PROT_OFFS, (action->mpls_cw_enable ? 1 : 0));
        } else {
            JR2_ACT_SET(CLM, X1_NXT_PROT_OFFS, 2);  // Terminate/forward LSP
        }
        if ((is1->flags & VTSS_IS1_FLAG_MAP_ID) == 0) {
            // No QoS ingress map
            JR2_ACT_ENA_SET(CLM, X1_COSID, action->cosid_enable, action->cosid);
            JR2_ACT_ENA_SET(CLM, X1_QOS, action->prio_enable, action->prio);
            JR2_ACT_ENA_SET(CLM, X1_DP, action->dp_enable, action->dp);
        }
    } else if (data->type == JR2_VCAP_TG_X2) {
        /* X2 */

        JR2_ACT_SET(CLM, X2_TYPE, CLM_X2_TYPE_CLASS);
        JR2_ACT_ENA_SET(CLM, X2_COSID, 0, 0);
        JR2_ACT_ENA_SET(CLM, X2_QOS, action->prio_enable, action->prio);
        JR2_ACT_ENA_SET(CLM, X2_DP, action->dp_enable, action->dp);
        JR2_ACT_ENA_SET(CLM, CLAS_DEI, action->dei_enable, action->dei);
        JR2_ACT_ENA_SET(CLM, CLAS_PCP, action->pcp_enable, action->pcp);
#if defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_ACT_ENA_SET(CLM, CLAS_VID, action->vid, action->vid);
#else
        if (action->vid_enable || action->vid != VTSS_VID_NULL) {
            JR2_ACT_SET(CLM, CLAS_VID_SEL, (action->vid == VTSS_VID_SECOND) ? 2 : (action->vid == VTSS_VID_THIRD) ? 3 : 1);
            JR2_ACT_SET(CLM, CLAS_VID_VAL, ((action->vid == VTSS_VID_SECOND) || (action->vid == VTSS_VID_THIRD)) ? 0 : action->vid);
        }
#endif /* VTSS_ARCH_JAGUAR_2_B */
        JR2_ACT_ENA_SET(CLM, CLAS_POP, action->pop_enable, action->pop);
        JR2_ACT_ENA_SET(CLM, CLAS_ISDX, action->isdx_enable, action->isdx);
        JR2_ACT_SET(CLM, CLAS_FWD_DIS, (action->fwd_disable ? 1 : 0));
        JR2_ACT_SET(CLM, CLAS_MIP_SEL, (action->mip_enable ? 1 : 0));
        oam = (action->oam_detect == VTSS_OAM_DETECT_UNTAGGED ? 2 :
            action->oam_detect == VTSS_OAM_DETECT_SINGLE_TAGGED ? 3 :
            action->oam_detect == VTSS_OAM_DETECT_DOUBLE_TAGGED ? 4 :
            action->oam_detect == VTSS_OAM_DETECT_TRIPLE_TAGGED ? 5 : 0);
        JR2_ACT_SET(CLM, CLAS_OAM_SEL, oam);
        if (action->pag_enable) {
            JR2_ACT_SET(CLM, CLAS_PAG_MASK, VTSS_BITMASK(CLM_AL_CLAS_PAG_MASK - 1)); /* PAG(7) reserved */
            JR2_ACT_SET(CLM, CLAS_PAG, action->pag);
        }
        JR2_ACT_SET(CLM, CLAS_PL_ENA, action->pipe_enable);
        JR2_ACT_SET(CLM, CLAS_PL_PT, action->pipe_pt);
        JR2_ACT_SET(CLM, CLAS_NXT_KEY, action->nxt_key_type);
        JR2_ACT_SET(CLM, CLAS_NXT_IDX_CTRL, (action->nxt_idx_enable ? 1 : 0));
        JR2_ACT_SET(CLM, CLAS_NXT_IDX, action->nxt_idx);
    } else {
        /* X4 */

        JR2_ACT_ENA_SET(CLM, X4_ISDX, action->isdx_enable, action->isdx);
        JR2_ACT_SET(CLM, X4_NXT_IDX_CTRL, (action->nxt_idx_enable ? 1 : 0));
        JR2_ACT_SET(CLM, X4_NXT_IDX, action->nxt_idx);
        JR2_ACT_SET(CLM, X4_PL_ENA, action->pipe_enable);
        JR2_ACT_SET(CLM, X4_PL_PT, action->pipe_pt);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_ACT_SET(CLM, X4_PL_ACT_SEL, action->pipe_sel);
#endif /* VTSS_ARCH_JAGUAR_2_B */
        JR2_ACT_SET(CLM, X4_CPU_VAL, action->cpu_queue);

        if (key->type == VTSS_IS1_TYPE_MPLS_MLL) {
            /* Special for MLL */
            JR2_ACT_SET(CLM, X4_FWD_TYPE, action->mpls_fwd_type);
            JR2_ACT_SET(CLM, X4_MPLS_OAM_TYPE, action->mpls_oam_detect);
            JR2_ACT_SET(CLM, X4_MPLS_MEP_ENA, action->mpls_mep_enable ? 1 : 0);
            JR2_ACT_SET(CLM, X4_MPLS_MIP_ENA, action->mpls_mip_enable ? 1 : 0);       // Should usually be 0, as we don't do MIP for MLL
            JR2_ACT_SET(CLM, X4_MPLS_OAM_FLVR, (action->mpls_oam_flavor_1 ? 1 : 0));
            JR2_ACT_SET(CLM, X4_RSV_VAL, action->mpls_rsvd_lbl);
            JR2_ACT_SET(CLM, X4_NXT_KEY, 2);            // SGL_MLBS
            JR2_ACT_SET(CLM, X4_NXT_NORMALIZE, 1);
            JR2_ACT_SET(CLM, X4_NXT_W16_OFFS, 0);
            JR2_ACT_SET(CLM, X4_NXT_PROT_OFFS, 2);      // MPLS, always
            JR2_ACT_SET(CLM, X4_TC_LABEL, 3);
            JR2_ACT_SET(CLM, X4_TTL_LABEL, 3);
        } else {
            JR2_ACT_ENA_SET(CLM, X4_DSCP, action->dscp_enable, action->dscp);
            JR2_ACT_ENA_SET(CLM, X4_COSID, 0, 0);
            JR2_ACT_ENA_SET(CLM, X4_QOS, action->prio_enable, action->prio);
            JR2_ACT_ENA_SET(CLM, X4_DP, action->dp_enable, action->dp);
            if (action->pag_enable) {
                JR2_ACT_SET(CLM, X4_PAG_MASK, VTSS_BITMASK(CLM_AL_X4_PAG_MASK - 1)); /* PAG(7) reserved */
                JR2_ACT_SET(CLM, X4_PAG, action->pag);
            }
#if defined(VTSS_ARCH_JAGUAR_2_B)
            JR2_ACT_ENA_SET(CLM, X4_VID, action->vid, action->vid);
#else
            if (action->vid_enable || action->vid != VTSS_VID_NULL) {
                JR2_ACT_SET(CLM, X4_VID_SEL, (action->vid == VTSS_VID_SECOND) ? 2 : (action->vid == VTSS_VID_THIRD) ? 3 : 1);
                JR2_ACT_SET(CLM, X4_VID_VAL, ((action->vid == VTSS_VID_SECOND) || (action->vid == VTSS_VID_THIRD)) ? 0 : action->vid);
             }
#endif /* VTSS_ARCH_JAGUAR_2_B */
            JR2_ACT_ENA_SET(CLM, X4_PCP, action->pcp_enable, action->pcp);
            JR2_ACT_ENA_SET(CLM, X4_DEI, action->dei_enable, action->dei);
            JR2_ACT_ENA_SET(CLM, X4_POP, action->pop_enable, action->pop);
            JR2_ACT_SET(CLM, X4_RT_SEL, action->rt_sel);
            oam = (action->oam_detect == VTSS_OAM_DETECT_UNTAGGED ? 2 :
                action->oam_detect == VTSS_OAM_DETECT_SINGLE_TAGGED ? 3 :
                action->oam_detect == VTSS_OAM_DETECT_DOUBLE_TAGGED ? 4 :
                action->oam_detect == VTSS_OAM_DETECT_TRIPLE_TAGGED ? 5 : 0);
            JR2_ACT_SET(CLM, X4_OAM_SEL, oam);
            JR2_ACT_SET(CLM, X4_MIP_SEL, (action->mip_enable ? 1 : 0));
            JR2_ACT_SET(CLM, X4_MASK_MODE, (action->fwd_disable ? 2 : 0));  /* In order to disable forwarding but to make frame be handled through all analyser, the Mask Mode must be REPLACE_PGID. The AND_VLANMASK will make analyser stop handling the frame and therefore not be able to hit any VOE */ 
            JR2_ACT_SET(CLM, X4_NXT_KEY, action->nxt_key_type);
        }
    }

    /* Update action fields based on ingress QoS mapping */
    jr2_clm_action_update(vtss_state, data, is1);

    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ALL);
}

static vtss_rc jr2_clm_entry_update(vtss_state_t *vtss_state,
                                    vtss_vcap_type_t type, vtss_vcap_idx_t *idx, vtss_is1_data_t *is1)
{
#if VTSS_OPT_TRACE
    const jr2_vcap_props_t *vcap = &jr2_vcap_info[JR2_VCAP_SUPER];
#endif
    jr2_vcap_data_t        jr2_data, *data = &jr2_data;
    u32                    addr;

    data->vcap_type = type;
    data->tg = jr2_vcap_key_type(idx->key_size); //(idx->key_size == VTSS_VCAP_KEY_SIZE_FULL ? JR2_VCAP_TG_X16 : JR2_VCAP_TG_X8);
    addr = jr2_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u, map_id: %u, flags: 0x%x",
           vcap->name, idx->row, idx->col, addr, is1->map_id, is1->flags);

    /* Read action */
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));

    /* Update action fields based on ingress QoS mapping */
    jr2_clm_action_update(vtss_state, data, is1);

    /* Write action */
    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION);
}

/* Updating a CLM entry action with specified Pipeline Point forced enable. The 'enable' parameter controls if Y.1731 hitting this entry is enabled */
static vtss_rc jr2_clm_entry_update_masq_hit_ena(vtss_state_t *vtss_state,
                                                 vtss_vcap_type_t type, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, BOOL enable)
{
#if VTSS_OPT_TRACE
    const jr2_vcap_props_t *vcap = &jr2_vcap_info[JR2_VCAP_SUPER];
#endif
    vtss_is1_key_t         key;
    jr2_vcap_data_t        jr2_data, *data = &jr2_data;
    u32                    addr;

    data->vcap_type = type;
    data->tg = jr2_vcap_key_type(idx->key_size);
    addr = jr2_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u, enable %u", vcap->name, idx->row, idx->col, addr, enable);

    /* Read action */
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ENTRY));

    if ((idx->key_size == VTSS_VCAP_KEY_SIZE_FULL) || (idx->key_size == VTSS_VCAP_KEY_SIZE_HALF)) {     /* This is the "old" implementation with full or half size keys. Hitting the rule was disable by preventing hit by masqueraded frames. */
        if (enable) {   /* Enable means restore the "original" IGR_PORT_MASK_SEL key based on AIL key */
            VTSS_MEMSET(&key, 0, sizeof(key));
            key.port_hit = vcap_data->port_hit;
            key.looped = vcap_data->looped;
            key.masqueraded = vcap_data->masqueraded;
            jr2_clm_port_sel_update(data, &key);
        } else {    /* Disable means set IGR_PORT_MASK_SEL to "not hit masqueraded" key */
            if (idx->key_size == VTSS_VCAP_KEY_SIZE_FULL) {
                jr2_vcap_key_set(data, CLM_KO_X16_PORT_SEL, CLM_KL_X16_PORT_SEL, 0, 0x03);  /* This will be hit by frames from port. In case of SAT an CLM entry in front of this will discard frames from port */
            } else {
                jr2_vcap_key_set(data, CLM_KO_X8_PORT_SEL, CLM_KL_X8_PORT_SEL, 0, 0x03);  /* This will be hit by frames from port. In case of SAT an CLM entry in front of this will discard frames from port */
            }
        }
    } else if (idx->key_size == VTSS_VCAP_KEY_SIZE_EIGHTH) {
        vtss_is1_frame_etype_t *etype = &vcap_data->u.is1.entry->key.frame.etype;
        BOOL y1731 = ((etype->etype.value[0] == 0x89) && (etype->etype.value[1] == 0x02) && (etype->etype.mask[0] == 0xFF) && (etype->etype.mask[1] == 0xFF)) ? TRUE : FALSE;   /* Calculate if this is Y.1731 catching rule */
        jr2_vcap_key_bit_set(data, CLM_KO_TRI_VID_IDX_Y1731, enable ? (y1731 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_ANY) : VTSS_VCAP_BIT_0);  /* Enable means restore the original key */
                                                                                                                                         /* Disable means that Y.1731 frames cannot hit this entry */
    }

    /* Write action */
    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ENTRY);
}

/* - CLM-A --------------------------------------------------------- */

static vtss_rc jr2_clm_a_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return jr2_clm_entry_add(vtss_state, VTSS_VCAP_TYPE_CLM_A, idx, vcap_data, counter);
}

static vtss_rc jr2_clm_a_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return jr2_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_CLM_A, idx);
}

static vtss_rc jr2_clm_a_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return jr2_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_CLM_A, idx, count, up);
}

static vtss_rc jr2_clm_a_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return jr2_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_CLM_A, idx, counter, clear);
}

/* - CLM-B --------------------------------------------------------- */

static vtss_rc jr2_clm_b_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return jr2_clm_entry_add(vtss_state, VTSS_VCAP_TYPE_CLM_B, idx, vcap_data, counter);
}

static vtss_rc jr2_clm_b_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return jr2_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_CLM_B, idx);
}

static vtss_rc jr2_clm_b_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return jr2_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_CLM_B, idx, count, up);
}

static vtss_rc jr2_clm_b_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return jr2_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_CLM_B, idx, counter, clear);
}

/* - CLM-C --------------------------------------------------------- */

static vtss_rc jr2_clm_c_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return jr2_clm_entry_add(vtss_state, VTSS_VCAP_TYPE_CLM_C, idx, vcap_data, counter);
}

static vtss_rc jr2_clm_c_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return jr2_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_CLM_C, idx);
}

static vtss_rc jr2_clm_c_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return jr2_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_CLM_C, idx, count, up);
}

static vtss_rc jr2_clm_c_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return jr2_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_CLM_C, idx, counter, clear);
}

/* - CLM debug ----------------------------------------------------- */

static vtss_rc jr2_debug_clm(vtss_state_t *vtss_state, jr2_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 type, mask;
    BOOL                nl = 1;

    /* Check VCAP type */
    switch (data->vcap_type) {
    case VTSS_VCAP_TYPE_CLM_A:
    case VTSS_VCAP_TYPE_CLM_B:
    case VTSS_VCAP_TYPE_CLM_C:
        break;
    default:
        VTSS_E("not TYPE_CLM");
        return VTSS_RC_ERROR;
    }

    if (data->is_action) {
        /* Show action fields */
        switch (data->type) {
        case JR2_VCAP_TG_NONE:
            /* Default action is cleared after initialization */
            break;

        case JR2_VCAP_TG_X1:
            JR2_DEBUG_ACT_ENA(CLM, "cosid", X1_COSID);
            JR2_DEBUG_ACT_ENA(CLM, "qos", X1_QOS);
            JR2_DEBUG_ACT_ENA(CLM, "dp", X1_DP);
            JR2_DEBUG_ACT(CLM, "map_sel", X1_MAP_SEL);
            JR2_DEBUG_ACT_BITS(CLM, "fwd_dis", X1_FWD_DIS);
            JR2_DEBUG_ACT_ENA(CLM, "cpu", X1_CPU);
#if defined(VTSS_ARCH_JAGUAR_2_B)
            JR2_DEBUG_ACT(CLM, "oam_sel", X1_OAM_SEL);
#else
            JR2_DEBUG_ACT_ENA(CLM, "isdx", X1_ISDX);
#endif /* VTSS_ARCH_JAGUAR_2_B */
            pr("\n");
            JR2_DEBUG_ACT_BITS(CLM, "tc_ena", X1_TC_ENA);
            JR2_DEBUG_ACT_BITS(CLM, "ttl_ena", X1_TTL_ENA);
            JR2_DEBUG_ACT(CLM, "fwd_type", X1_FWD_TYPE);
            JR2_DEBUG_ACT(CLM, "oam_type", X1_MPLS_OAM_TYPE);
#if defined(VTSS_ARCH_JAGUAR_2_B)
            JR2_DEBUG_ACT_BITS(CLM, "ttl_cpu", X1_MPLS_TTL_CPU);
#else
            JR2_DEBUG_ACT(CLM, "mep_ena", X1_MPLS_MEP_ENA);
            JR2_DEBUG_ACT(CLM, "mip_ena", X1_MPLS_MIP_ENA);
            pr("\n");
            JR2_DEBUG_ACT(CLM, "oam_flvr", X1_MPLS_OAM_FLVR);
            JR2_DEBUG_ACT(CLM, "ip_ctrl", X1_MPLS_IP_CTRL);
#endif /* VTSS_ARCH_JAGUAR_2_B */
            JR2_DEBUG_ACT(CLM, "pl_ena", X1_PL_ENA);
            JR2_DEBUG_ACT(CLM, "pl_pt", X1_PL_PT);
            pr("\n");
            JR2_DEBUG_ACT(CLM, "next_key", X1_NXT_KEY);
            JR2_DEBUG_ACT(CLM, "next_prot_offs", X1_NXT_PROT_OFFS);
#if defined(VTSS_ARCH_JAGUAR_2_B)
            JR2_DEBUG_ACT(CLM, "next_w16_offs", X1_NXT_W16_OFFS);
            JR2_DEBUG_ACT(CLM, "next_type_offs", X1_NXT_TYPE_OFFS);
#else
            JR2_DEBUG_ACT(CLM, "next_w32_offs", X1_NXT_W32_OFFS);
#endif /* VTSS_ARCH_JAGUAR_2_B */
            pr("\n");
            JR2_DEBUG_ACT_BITS(CLM, "next_normalize", X1_NXT_NORMALIZE);
            JR2_DEBUG_ACT(CLM, "next_idx_ctrl", X1_NXT_IDX_CTRL);
            JR2_DEBUG_ACT(CLM, "next_idx", X1_NXT_IDX);
            break;

        case JR2_VCAP_TG_X2:
            type = jr2_act_get(data, CLM_AO_X2_TYPE, CLM_AL_X2_TYPE);
            pr("type:%u (%s) ", type, type == CLM_X2_TYPE_MLBS ? "mlbs" : "classified");
            JR2_DEBUG_ACT_ENA(CLM, "cosid", X2_COSID);
            JR2_DEBUG_ACT_ENA(CLM, "qos", X2_QOS);
            JR2_DEBUG_ACT_ENA(CLM, "dp", X2_DP);
            if (type == CLM_X2_TYPE_MLBS) {
                JR2_DEBUG_ACT(CLM, "map_sel", MLBS_MAP_SEL);
                JR2_DEBUG_ACT(CLM, "map_key", MLBS_MAP_KEY);
                JR2_DEBUG_ACT(CLM, "map_idx", MLBS_MAP_IDX);
                pr("\n");
#if defined(VTSS_ARCH_JAGUAR_2_B)
                JR2_DEBUG_ACT_ENA(CLM, "vid", MLBS_VID);
#else
                JR2_DEBUG_ACT(CLM, "vid_sel", MLBS_VID_SEL);
                JR2_DEBUG_ACT(CLM, "vid_val", MLBS_VID_VAL);
#endif /* VTSS_ARCH_JAGUAR_2_B */
                JR2_DEBUG_ACT_ENA(CLM, "isdx", MLBS_ISDX);
                JR2_DEBUG_ACT_BITS(CLM, "fwd_dis", MLBS_FWD_DIS);
                JR2_DEBUG_ACT_ENA(CLM, "cpu", MLBS_CPU);
                JR2_DEBUG_ACT(CLM, "oam_sel", MLBS_OAM_SEL);
                JR2_DEBUG_ACT(CLM, "tc_lbl", MLBS_TC_LABEL);
                JR2_DEBUG_ACT(CLM, "ttl_lbl", MLBS_TTL_LABEL);
                JR2_DEBUG_ACT(CLM, "num_lbls", MLBS_NUM_LABELS);
                pr("\n");
                JR2_DEBUG_ACT(CLM, "fwd_type", MLBS_FWD_TYPE);
                JR2_DEBUG_ACT(CLM, "oam_type", MLBS_MPLS_OAM_TYPE);
#if defined(VTSS_ARCH_JAGUAR_2_B)
                JR2_DEBUG_ACT_BITS(CLM, "ttl_cpu", MLBS_MPLS_TTL_CPU);
#endif /* VTSS_ARCH_JAGUAR_2_B */
                JR2_DEBUG_ACT(CLM, "pag_mask", MLBS_PAG_MASK);
                JR2_DEBUG_ACT(CLM, "pag", MLBS_PAG);
                JR2_DEBUG_ACT(CLM, "pl_ena", MLBS_PL_ENA);
                JR2_DEBUG_ACT(CLM, "pl_pt", MLBS_PL_PT);
                pr("\n");
                JR2_DEBUG_ACT(CLM, "next_key", MLBS_NXT_KEY);
                JR2_DEBUG_ACT(CLM, "next_w16_offs", MLBS_NXT_W16_OFFS);
                JR2_DEBUG_ACT(CLM, "next_type_offs", MLBS_NXT_TYPE_OFFS);
                JR2_DEBUG_ACT(CLM, "next_prot_offs", MLBS_NXT_PROT_OFFS);
                pr("\n");
                JR2_DEBUG_ACT_BITS(CLM, "next_normalize", MLBS_NXT_NORMALIZE);
                JR2_DEBUG_ACT(CLM, "next_idx_ctrl", MLBS_NXT_IDX_CTRL);
                JR2_DEBUG_ACT(CLM, "next_idx", MLBS_NXT_IDX);
            } else {
                JR2_DEBUG_ACT_ENA(CLM, "dei", CLAS_DEI);
                JR2_DEBUG_ACT_ENA(CLM, "pcp", CLAS_PCP);
                pr("\n");
                JR2_DEBUG_ACT(CLM, "map_sel", CLAS_MAP_SEL);
                JR2_DEBUG_ACT(CLM, "map_key", CLAS_MAP_KEY);
                JR2_DEBUG_ACT(CLM, "map_idx", CLAS_MAP_IDX);
#if defined(VTSS_ARCH_JAGUAR_2_B)
                JR2_DEBUG_ACT_ENA(CLM, "vid", CLAS_VID);
#else
                JR2_DEBUG_ACT(CLM, "vid_sel", CLAS_VID_SEL);
                JR2_DEBUG_ACT(CLM, "vid_val", CLAS_VID_VAL);
#endif /* VTSS_ARCH_JAGUAR_2_B */
                JR2_DEBUG_ACT_ENA(CLM, "pop", CLAS_POP);
                JR2_DEBUG_ACT(CLM, "was_tagged", CLAS_WAS_TAGGED);
                JR2_DEBUG_ACT_ENA(CLM, "isdx", CLAS_ISDX);
                pr("\n");
                JR2_DEBUG_ACT_BITS(CLM, "fwd_dis", CLAS_FWD_DIS);
                JR2_DEBUG_ACT_ENA(CLM, "cpu", CLAS_CPU);
                JR2_DEBUG_ACT(CLM, "mip_sel", CLAS_MIP_SEL);
                JR2_DEBUG_ACT(CLM, "oam_sel", CLAS_OAM_SEL);
                JR2_DEBUG_ACT(CLM, "pag_mask", CLAS_PAG_MASK);
                JR2_DEBUG_ACT(CLM, "pag", CLAS_PAG);
                JR2_DEBUG_ACT(CLM, "pl_ena", CLAS_PL_ENA);
                JR2_DEBUG_ACT(CLM, "pl_pt", CLAS_PL_PT);
                pr("\n");
                JR2_DEBUG_ACT(CLM, "next_key", CLAS_NXT_KEY);
                JR2_DEBUG_ACT(CLM, "next_w16_offs", CLAS_NXT_W16_OFFS);
                JR2_DEBUG_ACT(CLM, "next_type_offs", CLAS_NXT_TYPE_OFFS);
                JR2_DEBUG_ACT(CLM, "next_prot_offs", CLAS_NXT_PROT_OFFS);
                pr("\n");
                JR2_DEBUG_ACT_BITS(CLM, "next_normalize", CLAS_NXT_NORMALIZE);
                JR2_DEBUG_ACT(CLM, "next_idx_ctrl", CLAS_NXT_IDX_CTRL);
                JR2_DEBUG_ACT(CLM, "next_idx", CLAS_NXT_IDX);
            }
            break;

        case JR2_VCAP_TG_X4:
            JR2_DEBUG_ACT_ENA(CLM, "dscp", X4_DSCP);
            JR2_DEBUG_ACT_ENA(CLM, "cosid", X4_COSID);
            JR2_DEBUG_ACT_ENA(CLM, "qos", X4_QOS);
            JR2_DEBUG_ACT_ENA(CLM, "dp", X4_DP);
            JR2_DEBUG_ACT_ENA(CLM, "dei", X4_DEI);
            JR2_DEBUG_ACT_ENA(CLM, "pcp", X4_PCP);
            JR2_DEBUG_ACT(CLM, "map_sel", X4_MAP_SEL);
            JR2_DEBUG_ACT(CLM, "map_key", X4_MAP_KEY);
            JR2_DEBUG_ACT(CLM, "map_idx", X4_MAP_IDX);
            pr("\n");
#if defined(VTSS_ARCH_JAGUAR_2_B)
            JR2_DEBUG_ACT_ENA(CLM, "vid", X4_VID);
#else
            JR2_DEBUG_ACT(CLM, "vid_sel", X4_VID_SEL);
            JR2_DEBUG_ACT(CLM, "vid_val", X4_VID_VAL);
#endif /* VTSS_ARCH_JAGUAR_2_B */
            JR2_DEBUG_ACT_ENA(CLM, "pop", X4_POP);
            JR2_DEBUG_ACT(CLM, "was_tagged", X4_WAS_TAGGED);
            JR2_DEBUG_ACT_ENA(CLM, "isdx", X4_ISDX);
            JR2_DEBUG_ACT(CLM, "mask_mode", X4_MASK_MODE);
            pr("\n");
            JR2_DEBUG_ACT_BITS(CLM, "port_mask", X4_PORT_MASK);
            JR2_DEBUG_ACT(CLM, "rt_sel", X4_RT_SEL);
            JR2_DEBUG_ACT_ENA(CLM, "cpu", X4_CPU);
            JR2_DEBUG_ACT(CLM, "mip_sel", X4_MIP_SEL);
            JR2_DEBUG_ACT(CLM, "oam_sel", X4_OAM_SEL);
            JR2_DEBUG_ACT(CLM, "fwd_type", X4_FWD_TYPE);
#if defined(VTSS_ARCH_JAGUAR_2_B)
            JR2_DEBUG_ACT_BITS(CLM, "ttl_cpu", X4_MPLS_TTL_CPU);
#endif /* VTSS_ARCH_JAGUAR_2_B */
            JR2_DEBUG_ACT(CLM, "cust_en", X4_CUSTOM_ENA);
            JR2_DEBUG_ACT(CLM, "cust_offs", X4_CUSTOM_OFFSET);
            pr("\n");
            JR2_DEBUG_ACT(CLM, "pag_mask", X4_PAG_MASK);
            JR2_DEBUG_ACT(CLM, "pag", X4_PAG);
            JR2_DEBUG_ACT(CLM, "reserved", X4_RESERVED);
            JR2_DEBUG_ACT(CLM, "match_id", X4_MATCH_ID);
            JR2_DEBUG_ACT(CLM, "match_mask", X4_MATCH_MASK);
            JR2_DEBUG_ACT(CLM, "pl_ena", X4_PL_ENA);
            JR2_DEBUG_ACT(CLM, "pl_pt", X4_PL_PT);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
            JR2_DEBUG_ACT(CLM, "pl_sel", X4_PL_ACT_SEL);
#endif /* VTSS_ARCH_JAGUAR_2_B */
            pr("\nMPLS: ");
            JR2_DEBUG_ACT(CLM, "oam_typ", X4_MPLS_OAM_TYPE);
            JR2_DEBUG_ACT(CLM, "oam_flvr", X4_MPLS_OAM_FLVR);
            JR2_DEBUG_ACT(CLM, "mep", X4_MPLS_MEP_ENA);
            JR2_DEBUG_ACT(CLM, "mip", X4_MPLS_MIP_ENA);
            JR2_DEBUG_ACT(CLM, "resv", X4_RSV_VAL);
            JR2_DEBUG_ACT(CLM, "tc_lbl", X4_TC_LABEL);
            JR2_DEBUG_ACT(CLM, "ttl_lbl", X4_TTL_LABEL);
            JR2_DEBUG_ACT(CLM, "num_lbl", X4_NUM_LABELS);
            pr("\n");
            JR2_DEBUG_ACT(CLM, "next_key", X4_NXT_KEY);
            JR2_DEBUG_ACT(CLM, "next_w16_offs", X4_NXT_W16_OFFS);
            JR2_DEBUG_ACT(CLM, "next_type_offs", X4_NXT_TYPE_OFFS);
            JR2_DEBUG_ACT(CLM, "next_prot_offs", X4_NXT_PROT_OFFS);
            pr("\n");
            JR2_DEBUG_ACT_BITS(CLM, "next_normalize", X4_NXT_NORMALIZE);
            JR2_DEBUG_ACT(CLM, "next_idx_ctrl", X4_NXT_IDX_CTRL);
            JR2_DEBUG_ACT(CLM, "next_idx", X4_NXT_IDX);
            JR2_DEBUG_ACT(CLM, "lport_ena", X4_LPORT_ENA);
            JR2_DEBUG_ACT(CLM, "lport", X4_LPORT);
            break;

        default:
            VTSS_E("not X1/X2/X4");
            return VTSS_RC_ERROR;
        }
        pr("\ncnt: %u", data->counter);
        return VTSS_RC_OK;
    }

    /* Show key fields */
    switch (data->tg) {
    case JR2_VCAP_TG_X1:
        JR2_DEBUG_BITS(CLM, "first", X1_FIRST);
        JR2_DEBUG_BITS(CLM, "g_idx", X1_G_IDX);
        JR2_DEBUG_BITS(CLM, "lbl0", X1_LBL0);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "sbit0", X1_SBIT0);
        JR2_DEBUG_BITS(CLM, "ttl0_exp", X1_TTL0_EXP);
        break;
    case JR2_VCAP_TG_X2:
        JR2_DEBUG_BITS(CLM, "type", X2_TYPE);
        type = jr2_entry_bs_get(data, CLM_KO_X2_TYPE, CLM_KL_X2_TYPE);
        pr("(%s) ", (type == CLM_X2_TYPE_TRI_VID) ? "tri_vid" : (type == CLM_X2_TYPE_TRI_VID_IDX) ? "tri_vid_idx" : "dbl_mlbs");
        JR2_DEBUG_BITS(CLM, "first", X2_FIRST);
        if (type == CLM_X2_TYPE_TRI_VID) {
            JR2_DEBUG_BITS(CLM, "igr_port", TRI_VID_IGR_PORT);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid0", TRI_VID_TPID0);
            JR2_DEBUG_BITS(CLM, "pcp0", TRI_VID_PCP0);
            JR2_DEBUG_BITS(CLM, "dei0", TRI_VID_DEI0);
            JR2_DEBUG_BITS(CLM, "vid0", TRI_VID_VID0);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid1", TRI_VID_TPID1);
            JR2_DEBUG_BITS(CLM, "pcp1", TRI_VID_PCP1);
            JR2_DEBUG_BITS(CLM, "dei1", TRI_VID_DEI1);
            JR2_DEBUG_BITS(CLM, "vid1", TRI_VID_VID1);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid2", TRI_VID_TPID2);
            JR2_DEBUG_BITS(CLM, "pcp2", TRI_VID_PCP2);
            JR2_DEBUG_BITS(CLM, "dei2", TRI_VID_DEI2);
            JR2_DEBUG_BITS(CLM, "vid2", TRI_VID_VID2);
            JR2_DEBUG_BITS(CLM, "etype", TRI_VID_ETYPE);
         } else if (type == CLM_X2_TYPE_TRI_VID_IDX) {
            JR2_DEBUG_BITS(CLM, "g_idx_isdx", TRI_VID_IDX_G_IDX_ISDX);
            JR2_DEBUG_BITS(CLM, "g_idx", TRI_VID_IDX_G_IDX);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid0", TRI_VID_IDX_TPID0);
            JR2_DEBUG_BITS(CLM, "vid0", TRI_VID_IDX_VID0);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid1", TRI_VID_IDX_TPID1);
            JR2_DEBUG_BITS(CLM, "vid1", TRI_VID_IDX_VID1);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid2", TRI_VID_IDX_TPID2);
            JR2_DEBUG_BITS(CLM, "vid2", TRI_VID_IDX_VID2);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "y1731", TRI_VID_IDX_Y1731);
            JR2_DEBUG_BITS(CLM, "mel_flag", TRI_VID_IDX_MEL_FLAG);
        } else {
            JR2_DEBUG_BITS(CLM, "g_idx", DBL_MLBS_G_IDX);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "lbl0", DBL_MLBS_LBL0);
            JR2_DEBUG_BITS(CLM, "tc0", DBL_MLBS_TC0);
            JR2_DEBUG_BITS(CLM, "sbit0", DBL_MLBS_SBIT0);
            JR2_DEBUG_BITS(CLM, "ttl0_exp", DBL_MLBS_TTL0_EXP);
            JR2_DEBUG_BITS(CLM, "rsv_pos", DBL_MLBS_RSV_POS);
        }
        break;
    case JR2_VCAP_TG_X4:
        JR2_DEBUG_BITS(CLM, "type", X4_TYPE);
        type = jr2_entry_bs_get(data, CLM_KO_X4_TYPE, CLM_KL_X4_TYPE);
        pr("(%s) ",
           type == CLM_X4_TYPE_MLL ? "mll" :
           type == CLM_X4_TYPE_TRI_MLBS ? "tri_mlbs" :
           type == CLM_X4_TYPE_5TUPLE_IP4 ? "5tuple_ip4" : "custom_4");
        if (type == CLM_X4_TYPE_MLL) {
            JR2_DEBUG_BITS(CLM, "igr_port", MLL_IGR_PORT);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "dmac", MLL_DMAC);
            JR2_DEBUG_BITS(CLM, "smac", MLL_SMAC);
            JR2_DEBUG_BITS(CLM, "tpid0", MLL_TPID0);
            JR2_DEBUG_BITS(CLM, "vid0", MLL_VID0);
            JR2_DEBUG_BITS(CLM, "tpid1", MLL_TPID1);
            JR2_DEBUG_BITS(CLM, "vid1", MLL_VID1);
            JR2_DEBUG_BITS(CLM, "etype", MLL_ETYPE);
        } else if (type == CLM_X4_TYPE_TRI_MLBS) {
            JR2_DEBUG_BITS(CLM, "first", X4_FIRST);
            JR2_DEBUG_BITS(CLM, "g_idx", TRI_MLBS_G_IDX);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "lbl0", TRI_MLBS_LBL0);
            JR2_DEBUG_BITS(CLM, "tc0", TRI_MLBS_TC0);
            JR2_DEBUG_BITS(CLM, "sbit0", TRI_MLBS_SBIT0);
            JR2_DEBUG_BITS(CLM, "ttl0_exp", TRI_MLBS_TTL0_EXP);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "lbl1", TRI_MLBS_LBL1);
            JR2_DEBUG_BITS(CLM, "tc1", TRI_MLBS_TC1);
            JR2_DEBUG_BITS(CLM, "sbit1", TRI_MLBS_SBIT1);
            JR2_DEBUG_BITS(CLM, "ttl1_exp", TRI_MLBS_TTL1_EXP);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "lbl2", TRI_MLBS_LBL2);
            JR2_DEBUG_BITS(CLM, "tc2", TRI_MLBS_TC2);
            JR2_DEBUG_BITS(CLM, "sbit2", TRI_MLBS_SBIT2);
            JR2_DEBUG_BITS(CLM, "ttl2_exp", TRI_MLBS_TTL2_EXP);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "rsv_val", TRI_MLBS_RSV_VAL);
            JR2_DEBUG_BITS(CLM, "rsv_pos", TRI_MLBS_RSV_POS);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "cw_ach", TRI_MLBS_CW_ACH);
        } else {
            pr("type not supported");
        }
        break;
    case JR2_VCAP_TG_X8:
        JR2_DEBUG_BITS(CLM, "type", X8_TYPE);
        type = jr2_entry_bs_get(data, CLM_KO_X8_TYPE, CLM_KL_X8_TYPE);
        mask = jr2_mask_bs_get(data, CLM_KO_X8_TYPE, CLM_KL_X8_TYPE);
        pr("(%s) ",
           mask == 0 ? "any" :
           type == CLM_X8_TYPE_LL_FULL ? "ll_full" :
           type == CLM_X8_TYPE_NORMAL ? "normal" :
           type == CLM_X8_TYPE_5TUPLE_IP4 ? "5tuple_ip4" : "custom_2");
        JR2_DEBUG_BITS(CLM, "first", X8_FIRST);
        if (mask != 0 && type == CLM_X8_TYPE_LL_FULL) {
            JR2_DEBUG_BITS(CLM, "igr_port", LL_FULL_IGR_PORT);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid0", LL_FULL_TPID0);
            JR2_DEBUG_BITS(CLM, "pcp0", LL_FULL_PCP0);
            JR2_DEBUG_BITS(CLM, "dei0", LL_FULL_DEI0);
            JR2_DEBUG_BITS(CLM, "vid0", LL_FULL_VID0);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid1", LL_FULL_TPID1);
            JR2_DEBUG_BITS(CLM, "pcp1", LL_FULL_PCP1);
            JR2_DEBUG_BITS(CLM, "dei1", LL_FULL_DEI1);
            JR2_DEBUG_BITS(CLM, "vid1", LL_FULL_VID1);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "tpid2", LL_FULL_TPID2);
            JR2_DEBUG_BITS(CLM, "pcp2", LL_FULL_PCP2);
            JR2_DEBUG_BITS(CLM, "dei2", LL_FULL_DEI2);
            JR2_DEBUG_BITS(CLM, "vid2", LL_FULL_VID2);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "dmac", LL_FULL_DMAC);
            JR2_DEBUG_BITS(CLM, "smac", LL_FULL_SMAC);
            JR2_DEBUG_BITS(CLM, "etype_len", LL_FULL_ETYPE_LEN);
            JR2_DEBUG_BITS(CLM, "etype", LL_FULL_ETYPE);
            JR2_DEBUG_BITS(CLM, "ip_snap", LL_FULL_IP_SNAP);
            JR2_DEBUG_BITS(CLM, "ip4", LL_FULL_IP4);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "fragment", LL_FULL_FRAGMENT);
            JR2_DEBUG_BITS(CLM, "frag_offs", LL_FULL_FRAG_OFFS);
            JR2_DEBUG_BITS(CLM, "options", LL_FULL_OPTIONS);
            JR2_DEBUG_BITS(CLM, "dscp", LL_FULL_DSCP);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "dip", LL_FULL_DIP);
            JR2_DEBUG_BITS(CLM, "sip", LL_FULL_SIP);
            JR2_DEBUG_BITS(CLM, "tcp_udp", LL_FULL_TCP_UDP);
            JR2_DEBUG_BITS(CLM, "tcp", LL_FULL_TCP);
            JR2_DEBUG_BITS(CLM, "sport", LL_FULL_SPORT);
            break;
        }

        /* Common fields for other X8 rules */
        JR2_DEBUG_BITS(CLM, "g_idx_isdx", X8_G_IDX_ISDX);
        JR2_DEBUG_BITS(CLM, "g_idx", X8_G_IDX);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "l2_mc", X8_L2_MC);
        JR2_DEBUG_BITS(CLM, "l2_bc", X8_L2_BC);
        JR2_DEBUG_BITS(CLM, "port_sel", X8_PORT_SEL);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "port_mask", X8_PORT_MASK);
        JR2_DEBUG_BITS(CLM, "tpid0", X8_TPID0);
        JR2_DEBUG_BITS(CLM, "pcp0", X8_PCP0);
        JR2_DEBUG_BITS(CLM, "dei0", X8_DEI0);
        JR2_DEBUG_BITS(CLM, "vid0", X8_VID0);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "tpid1", X8_TPID1);
        JR2_DEBUG_BITS(CLM, "pcp1", X8_PCP1);
        JR2_DEBUG_BITS(CLM, "dei1", X8_DEI1);
        JR2_DEBUG_BITS(CLM, "vid1", X8_VID1);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "tpid2", X8_TPID2);
        JR2_DEBUG_BITS(CLM, "pcp2", X8_PCP2);
        JR2_DEBUG_BITS(CLM, "dei2", X8_DEI2);
        JR2_DEBUG_BITS(CLM, "vid2", X8_VID2);
        pr("\n");
        if (mask == 0) {
            /* No more common fields */
            nl = 0;
        } else if (type == CLM_X8_TYPE_NORMAL) {
            JR2_DEBUG_BITS(CLM, "smac", NORMAL_SMAC);
            JR2_DEBUG_BITS(CLM, "dst_entry", NORMAL_DST_ENTRY);
            JR2_DEBUG_BITS(CLM, "ip_mc", NORMAL_IP_MC);
            JR2_DEBUG_BITS(CLM, "etype_len", NORMAL_ETYPE_LEN);
            JR2_DEBUG_BITS(CLM, "etype", NORMAL_ETYPE);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "ip_snap", NORMAL_IP_SNAP);
            JR2_DEBUG_BITS(CLM, "ip4", NORMAL_IP4);
            JR2_DEBUG_BITS(CLM, "fragment", NORMAL_FRAGMENT);
            JR2_DEBUG_BITS(CLM, "frag_offs", NORMAL_FRAG_OFFS);
            JR2_DEBUG_BITS(CLM, "options", NORMAL_OPTIONS);
            JR2_DEBUG_BITS(CLM, "dscp", NORMAL_DSCP);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "sip", NORMAL_SIP);
            JR2_DEBUG_BITS(CLM, "tcp_udp", NORMAL_TCP_UDP);
            JR2_DEBUG_BITS(CLM, "tcp", NORMAL_TCP);
            JR2_DEBUG_BITS(CLM, "sport", NORMAL_SPORT);
            JR2_DEBUG_BITS(CLM, "range", NORMAL_RANGE);
        } else if (type == CLM_X8_TYPE_5TUPLE_IP4) {
            JR2_DEBUG_BITS(CLM, "ip_mc", 5TUPLE_IP4_IP_MC);
            JR2_DEBUG_BITS(CLM, "ip4", 5TUPLE_IP4_IP4);
            JR2_DEBUG_BITS(CLM, "fragment", 5TUPLE_IP4_FRAGMENT);
            JR2_DEBUG_BITS(CLM, "frag_offs", 5TUPLE_IP4_FRAG_OFFS);
            JR2_DEBUG_BITS(CLM, "options", 5TUPLE_IP4_OPTIONS);
            JR2_DEBUG_BITS(CLM, "dscp", 5TUPLE_IP4_DSCP);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "dip", 5TUPLE_IP4_DIP);
            JR2_DEBUG_BITS(CLM, "sip", 5TUPLE_IP4_SIP);
            JR2_DEBUG_BITS(CLM, "proto", 5TUPLE_IP4_PROTO);
            JR2_DEBUG_BITS(CLM, "tcp_udp", 5TUPLE_IP4_TCP_UDP);
            JR2_DEBUG_BITS(CLM, "tcp", 5TUPLE_IP4_TCP);
            JR2_DEBUG_BITS(CLM, "range", 5TUPLE_IP4_RANGE);
            pr("\n");
            JR2_DEBUG_BITS(CLM, "payload", 5TUPLE_IP4_PAYLOAD);
            nl = 0;
        } else {
            pr("type not supported");
        }
        break;
    case JR2_VCAP_TG_X16:
        JR2_DEBUG_BITS(CLM, "type", X16_TYPE);
        type = jr2_entry_bs_get(data, CLM_KO_X16_TYPE, CLM_KL_X16_TYPE);
        pr("(%s) ", type == CLM_X16_TYPE_7TUPLE ? "7tuple" : "custom_1");
        JR2_DEBUG_BITS(CLM, "first", X16_FIRST);
        JR2_DEBUG_BITS(CLM, "g_idx_isdx", X16_G_IDX_ISDX);
        JR2_DEBUG_BITS(CLM, "g_idx", X16_G_IDX);
        pr("\n");
        if (type == CLM_X16_TYPE_CUSTOM_1) {
            pr("type not supported");
            break;
        }

        JR2_DEBUG_BITS(CLM, "l2_mc", X16_L2_MC);
        JR2_DEBUG_BITS(CLM, "l2_bc", X16_L2_BC);
        JR2_DEBUG_BITS(CLM, "port_sel", X16_PORT_SEL);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "port_mask", X16_PORT_MASK);
        JR2_DEBUG_BITS(CLM, "tpid0", X16_TPID0);
        JR2_DEBUG_BITS(CLM, "pcp0", X16_PCP0);
        JR2_DEBUG_BITS(CLM, "dei0", X16_DEI0);
        JR2_DEBUG_BITS(CLM, "vid0", X16_VID0);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "tpid1", X16_TPID1);
        JR2_DEBUG_BITS(CLM, "pcp1", X16_PCP1);
        JR2_DEBUG_BITS(CLM, "dei1", X16_DEI1);
        JR2_DEBUG_BITS(CLM, "vid1", X16_VID1);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "tpid2", X16_TPID2);
        JR2_DEBUG_BITS(CLM, "pcp2", X16_PCP2);
        JR2_DEBUG_BITS(CLM, "dei2", X16_DEI2);
        JR2_DEBUG_BITS(CLM, "vid2", X16_VID2);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "dmac", X16_DMAC);
        JR2_DEBUG_BITS(CLM, "smac", X16_SMAC);
        JR2_DEBUG_BITS(CLM, "ip_mc", X16_IP_MC);
        JR2_DEBUG_BITS(CLM, "etype_len", X16_ETYPE_LEN);
        JR2_DEBUG_BITS(CLM, "etype", X16_ETYPE);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "ip_snap", X16_IP_SNAP);
        JR2_DEBUG_BITS(CLM, "ip4", X16_IP4);
        JR2_DEBUG_BITS(CLM, "fragment", X16_FRAGMENT);
        JR2_DEBUG_BITS(CLM, "frag_offs", X16_FRAG_OFFS);
        JR2_DEBUG_BITS(CLM, "options", X16_OPTIONS);
        JR2_DEBUG_BITS(CLM, "dscp", X16_DSCP);
        pr("\n");
        JR2_DEBUG_BITS(CLM, "dip", X16_DIP);
        JR2_DEBUG_BITS(CLM, "sip", X16_SIP);
        JR2_DEBUG_BITS(CLM, "tcp_udp", X16_TCP_UDP);
        JR2_DEBUG_BITS(CLM, "tcp", X16_TCP);
        JR2_DEBUG_BITS(CLM, "sport", X16_SPORT);
        JR2_DEBUG_BITS(CLM, "range", X16_RANGE);
        break;
    default:
        VTSS_E("not X1/X2/X4/X8/X16");
        return VTSS_RC_ERROR;
    }
    if (nl) {
        pr("\n");
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_debug_clm_all(vtss_state_t *vtss_state,
                                 vtss_vcap_type_t type,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    vtss_port_no_t port_no;
    u32            port, i, j;
    char           buf[32];

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0)
            continue;
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_jr2_debug_reg_header(pr, buf);
        for (i = 0; i < 2; i++) {
            j = ((type == VTSS_VCAP_TYPE_CLM_A ? 0 : type == VTSS_VCAP_TYPE_CLM_B ? 2 : 4) + i);
            VTSS_SPRINTF(buf, "ADV_CL_CFG_%u", port);
            vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_PORT_ADV_CL_CFG(port, j), j, buf);
        }
        pr("\n");
    }
    return jr2_debug_vcap(vtss_state, type, pr, info, jr2_debug_clm);
}

vtss_rc vtss_jr2_debug_clm_a(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    return jr2_debug_clm_all(vtss_state, VTSS_VCAP_TYPE_CLM_A, pr, info);
}

vtss_rc vtss_jr2_debug_clm_b(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    return jr2_debug_clm_all(vtss_state, VTSS_VCAP_TYPE_CLM_B, pr, info);
}

vtss_rc vtss_jr2_debug_clm_c(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    return jr2_debug_clm_all(vtss_state, VTSS_VCAP_TYPE_CLM_C, pr, info);
}

/* - LPM ----------------------------------------------------------- */

static vtss_rc jr2_lpm_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    jr2_vcap_data_t      jr2_data, *data = &jr2_data;
    vtss_lpm_entry_t     *entry = vcap_data->u.lpm.entry;
    vtss_lpm_key_t       *key = &entry->key;
    vtss_lpm_action_t    *action = &entry->action;
    vtss_lpm_arp_entry_t *arp_entry = &action->data.arp_entry;
    vtss_lpm_arp_ptr_t   *arp_ptr = &action->data.arp_ptr;
    vtss_vid_mac_t       vid_mac;
    u32                  addr, mach, macl;

    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = VTSS_VCAP_TYPE_LPM;
    addr = jr2_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u", idx->row, idx->col, addr);

    /* Setup key fields */
    switch (key->type) {
    case VTSS_LPM_KEY_SGL_IP4:
        data->tg = JR2_VCAP_TG_X1;
        jr2_vcap_key_bit_set(data, LPM_KO_X1_DST_FLAG, key->data.sgl_ip4.dst_ena ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        jr2_vcap_key_ipv4_set(data, LPM_KO_X1_IP4_XIP, &key->data.sgl_ip4.xip);
        break;
    case VTSS_LPM_KEY_DBL_IP4:
        data->tg = JR2_VCAP_TG_X2;
        jr2_vcap_key_ipv4_set(data, LPM_KO_X2_IP4_SIP, &key->data.dbl_ip4.sip);
        jr2_vcap_key_ipv4_set(data, LPM_KO_X2_IP4_DIP, &key->data.dbl_ip4.dip);
        break;
    case VTSS_LPM_KEY_SGL_IP6:
        data->tg = JR2_VCAP_TG_X4;
        jr2_vcap_key_bit_set(data, LPM_KO_X4_DST_FLAG, key->data.sgl_ip6.dst_ena ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        jr2_vcap_key_u128_set(data, LPM_KO_X4_IP6_XIP, &key->data.sgl_ip6.xip);
        break;
    case VTSS_LPM_KEY_DBL_IP6:
        data->tg = JR2_VCAP_TG_X8;
        jr2_vcap_key_u128_set(data, LPM_KO_X8_IP6_SIP, &key->data.dbl_ip6.sip);
        jr2_vcap_key_u128_set(data, LPM_KO_X8_IP6_DIP, &key->data.dbl_ip6.dip);
        break;
    default:
        VTSS_E("illegal key type");
        return VTSS_RC_ERROR;
    }

    /* Setup action fields */
    switch (action->type) {
    case LPM_TYPE_ARP_ENTRY:
        vid_mac.vid = 0;
        vid_mac.mac = arp_entry->mac;
        vtss_mach_macl_get(&vid_mac, &mach, &macl);
        JR2_ACT_SET(LPM, ARP_ENTRY_MAC_MSB, mach);
        JR2_ACT_SET(LPM, ARP_ENTRY_MAC_LSB, macl);
        JR2_ACT_SET(LPM, ARP_ENTRY_VMID, arp_entry->vmid);
        JR2_ACT_SET(LPM, ARP_ENTRY_ZERO_DMAC_CPU_QUEUE, arp_entry->cpu_queue);
        JR2_ACT_SET(LPM, ARP_ENTRY_SECUR_MATCH_MAC_ENA, arp_entry->secur_match_mac_ena);
        JR2_ACT_SET(LPM, ARP_ENTRY_ARP_ENA, arp_entry->arp_ena);
        break;
    case LPM_TYPE_ARP_PTR:
        JR2_ACT_SET(LPM, ARP_PTR_ARP_PTR, arp_ptr->arp_ptr);
        JR2_ACT_SET(LPM, ARP_PTR_ECMP_CNT, arp_ptr->ecmp_cnt);
        JR2_ACT_SET(LPM, ARP_PTR_RGID, arp_ptr->rgid);
        break;
    case LPM_TYPE_L3MC_PTR:
        JR2_ACT_SET(LPM, L3MC_PTR, action->data.l3mc_idx);
        break;
    default:
        VTSS_E("illegal key type");
        return VTSS_RC_ERROR;
    }
    JR2_ACT_SET(LPM, TYPE, action->type);

    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ALL);
}

static vtss_rc jr2_lpm_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return jr2_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_LPM, idx);
}

static vtss_rc jr2_lpm_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return jr2_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_LPM, idx, count, up);
}

static vtss_rc jr2_lpm_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return jr2_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_LPM, idx, counter, clear);
}

static vtss_rc jr2_debug_lpm(vtss_state_t *vtss_state, jr2_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 type;

    if (data->is_action) {
        /* Show action fields */
        type = jr2_act_get(data, LPM_AO_TYPE, LPM_AL_TYPE);
        pr("type:%u (%s) ", type,
           type == LPM_TYPE_ARP_PTR ? "arp_ptr" :
           type == LPM_TYPE_L3MC_PTR ? "l3mc_ptr" :
           type == LPM_TYPE_ARP_ENTRY ? "arp_entry" : "?");

        switch (type) {
        case LPM_TYPE_ARP_PTR:
            JR2_DEBUG_ACT(LPM, "arp_ptr", ARP_PTR_ARP_PTR);
            JR2_DEBUG_ACT(LPM, "ecmp_cnt", ARP_PTR_ECMP_CNT);
            JR2_DEBUG_ACT(LPM, "remap_ena", ARP_PTR_REMAP_ENA);
            JR2_DEBUG_ACT(LPM, "rgid", ARP_PTR_RGID);
            break;
        case LPM_TYPE_L3MC_PTR:
            JR2_DEBUG_ACT(LPM, "l3mc_ptr", L3MC_PTR);
            break;
        case LPM_TYPE_ARP_ENTRY:
            JR2_DEBUG_ACT_BITS(LPM, "mac_msb", ARP_ENTRY_MAC_MSB);
            JR2_DEBUG_ACT_BITS(LPM, "mac_lsb", ARP_ENTRY_MAC_LSB);
            JR2_DEBUG_ACT(LPM, "vmid", ARP_ENTRY_VMID);
            JR2_DEBUG_ACT(LPM, "cpu_queue", ARP_ENTRY_ZERO_DMAC_CPU_QUEUE);
            JR2_DEBUG_ACT(LPM, "sip_rpf_ena", ARP_ENTRY_SIP_RPF_ENA);
            JR2_DEBUG_ACT(LPM, "secur_vmid_ena", ARP_ENTRY_SECUR_MATCH_VMID_ENA);
            JR2_DEBUG_ACT(LPM, "secur_mac_ena", ARP_ENTRY_SECUR_MATCH_MAC_ENA);
            JR2_DEBUG_ACT(LPM, "arp_ena", ARP_ENTRY_ARP_ENA);
            break;
        default:
            VTSS_E("unknown action type");
            return VTSS_RC_ERROR;
        }
        pr("\ncnt: %u", data->counter);
        return VTSS_RC_OK;
    }

    /* Show key fields */
    switch (data->tg) {
    case JR2_VCAP_TG_X1:
        JR2_DEBUG_BITS(LPM, "dst_flag", X1_DST_FLAG);
        JR2_DEBUG_BITS(LPM, "ip4_xip", X1_IP4_XIP);
        break;
    case JR2_VCAP_TG_X2:
        JR2_DEBUG_BITS(LPM, "ip4_sip", X2_IP4_SIP);
        JR2_DEBUG_BITS(LPM, "ip4_dip", X2_IP4_DIP);
        break;
    case JR2_VCAP_TG_X4:
        JR2_DEBUG_BITS(LPM, "dst_flag", X4_DST_FLAG);
        pr("\n");
        JR2_DEBUG_BITS(LPM, "ip6_xip", X4_IP6_XIP);
        break;
    case JR2_VCAP_TG_X8:
        JR2_DEBUG_BITS(LPM, "ip6_sip", X8_IP6_SIP);
        JR2_DEBUG_BITS(LPM, "ip6_dip", X8_IP6_DIP);
        break;
    default:
        VTSS_E("not X1/X2/X4/X8");
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_debug_lpm(vtss_state_t *vtss_state,
                           const vtss_debug_printf_t pr,
                           const vtss_debug_info_t   *const info)
{
    return jr2_debug_vcap(vtss_state, VTSS_VCAP_TYPE_LPM, pr, info, jr2_debug_lpm);
}

/* - IS2 ----------------------------------------------------------- */

/* The first counters are used for port default actions. For convenience, ACE counters start from 100 */
#define JR2_ACE_CNT_ID_BASE 100

static vtss_rc jr2_is2_action_set(vtss_state_t *vtss_state, jr2_vcap_data_t *data, vtss_acl_action_t *action, u32 cnt_id, u32 counter)
{
    vtss_acl_port_action_t     act = action->port_action;
    vtss_acl_ptp_action_conf_t *ptp = &action->ptp;
    vtss_port_no_t             port_no;
    u32                        discard = 0, port, ptp_cmd, ptp_delay, ptp_seq_ts, dlb_offset = 0;
    u32                        rt_mode, mach, macl, sam_seq_ena = 0, tcp_udp_ena = 0, match_id, match_mask;
    vtss_vid_mac_t             vid_mac;
    BOOL                       swap_mac = action->mac_swap;

    data->type = JR2_VCAP_TG_X4;
    data->vcap_type = VTSS_VCAP_TYPE_IS2;
    JR2_ACT_SET(IS2, IS_INNER_ACL, action->cpu && act == VTSS_ACL_PORT_ACTION_REDIR); /* CPU copy/redirect (e.g. service policing/stats still applied) */
    JR2_ACT_SET(IS2, HIT_ME_ONCE, action->cpu_once);
    JR2_ACT_SET(IS2, CPU_ENA, action->cpu);
    JR2_ACT_SET(IS2, CPU_VAL, action->cpu_queue);
    if (act != VTSS_ACL_PORT_ACTION_NONE) {
        /* Port filter or redirect */
        discard = 1;
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (action->port_list[port_no]) {
                discard = 0;
                port = VTSS_CHIP_PORT(port_no);
                if (act != VTSS_ACL_PORT_ACTION_REDIR || vtss_state->l2.tx_forward_aggr[port_no]) {
                    jr2_act_set(data, IS2_AO_PORT_MASK + port, 1, 1);
                }
            }
        }
    }
    JR2_ACT_SET(IS2, MASK_MODE,
                act == VTSS_ACL_PORT_ACTION_PGID ? IS2_MASK_MODE_REPLACE_PGID :
                (act == VTSS_ACL_PORT_ACTION_REDIR || discard) ? IS2_MASK_MODE_REPLACE_ALL :
                act == VTSS_ACL_PORT_ACTION_FILTER ? IS2_MASK_MODE_AND_VLANMASK : IS2_MASK_MODE_OR_DSTMASK);
    /* If forwarding disabled, avoid CPU copy and signal ACL drop */
    JR2_ACT_SET(IS2, CPU_DIS, discard || action->cpu_disable ? 1 : 0);
    match_id = (JR2_IFH_CL_RSLT_ACL_HIT | (action->ifh_flag ? JR2_IFH_CL_RSLT_ACL_FLAG : 0));
    match_mask = match_id;
    JR2_ACT_SET(IS2, LRN_DIS, action->learn ? 0 : 1);
    JR2_ACT_SET(IS2, RT_DIS, discard);
    JR2_ACT_SET(IS2, MIRROR_PROBE, action->mirror ? (JR2_MIRROR_PROBE_RX + 1) : 0);
    JR2_ACT_ENA_SET(IS2, POLICE, action->police, action->policer_no);

    /* PTP actions */
    ptp_delay = IS2_REW_DELAY_NONE;
    switch (action->ptp_action) {
    case VTSS_ACL_PTP_ACTION_ONE_STEP:
        ptp_cmd = IS2_REW_PTP_ONE;
        break;
    case VTSS_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY:
        ptp_cmd = IS2_REW_PTP_ONE;
        ptp_delay = IS2_REW_DELAY_EGR;
        break;
    case VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1:
        ptp_cmd = IS2_REW_PTP_ONE;
        ptp_delay = IS2_REW_DELAY_IGR1;
        break;
    case VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2:
        ptp_cmd = IS2_REW_PTP_ONE;
        ptp_delay = IS2_REW_DELAY_IGR2;
        break;
    case VTSS_ACL_PTP_ACTION_TWO_STEP:
        ptp_cmd = IS2_REW_PTP_TWO;
        break;
    default:
        ptp_cmd = IS2_REW_PTP_NONE;
        break;
    }
    switch (action->ptp.response) {
    case VTSS_ACL_PTP_RSP_DLY_REQ_RSP_TS_UPD:
        ptp_seq_ts = IS2_REW_SEQ_TS_RSP_TS;
        break;
    case VTSS_ACL_PTP_RSP_DLY_REQ_RSP_NO_TS:
        ptp_seq_ts = IS2_REW_SEQ_TS_RSP_NONE;
        break;
    default:
        ptp_seq_ts = IS2_REW_SEQ_TS_NONE;
        break;
    }
    if (ptp_seq_ts != IS2_REW_SEQ_TS_NONE) {
        /* Log message interval encoded in SWAP_MAC_ENA and DLB_OFFSET */
        swap_mac = (ptp->log_message_interval < 0 ? 1 : 0);
        dlb_offset = (ptp->log_message_interval & 0x7);
        match_id = ptp->dport;
        match_mask = ptp->sport;
        tcp_udp_ena = 1;
    }

    /* MAC address update */
    rt_mode = (1 << 3); /* Swapping mode by default */
    switch (action->addr.update) {
    case VTSS_ACL_ADDR_UPDATE_MAC_SWAP:
        rt_mode += 2;
        break;
    case VTSS_ACL_ADDR_UPDATE_MAC_IP_SWAP_UC:
        rt_mode += 5;
        JR2_ACT_SET(IS2, POLICE_VAL, action->addr.sip_idx);
        break;
    case VTSS_ACL_ADDR_UPDATE_DMAC_REPLACE:
        break;
    case VTSS_ACL_ADDR_UPDATE_DMAC_REPLACE_MSB:
        sam_seq_ena = 1;
        break;
    default:
        rt_mode = 0; /* Routing mode */
        break;
    }
    vid_mac.vid = 0;
    vid_mac.mac = action->addr.mac;
    vtss_mach_macl_get(&vid_mac, &mach, &macl);

    JR2_ACT_SET(IS2, REW_PTP, ptp_cmd);
    JR2_ACT_SET(IS2, REW_DELAY, ptp_delay);
    JR2_ACT_SET(IS2, REW_SEQ_TS, ptp_seq_ts);
    JR2_ACT_SET(IS2, REW_DMAC, ptp->copy_smac_to_dmac);
    JR2_ACT_SET(IS2, REW_SMAC, ptp->set_smac_to_port_mac);
    JR2_ACT_SET(IS2, SWAP_MAC, swap_mac);
    JR2_ACT_SET(IS2, DLB_OFFSET, dlb_offset);
    JR2_ACT_SET(IS2, PTP_DOM, ptp->dom_sel);
    JR2_ACT_SET(IS2, MATCH_ID, match_id);
    JR2_ACT_SET(IS2, MATCH_MASK, match_mask);
    JR2_ACT_SET(IS2, ACL_RT_MODE, rt_mode);
    JR2_ACT_SET(IS2, SAM_SEQ_ENA, sam_seq_ena);
    JR2_ACT_SET(IS2, TCP_UDP_ENA, tcp_udp_ena);
    jr2_act_set(data, IS2_AO_ACL_MAC, 32, macl);
    jr2_act_set(data, IS2_AO_ACL_MAC + 32, 16, mach);
    JR2_ACT_SET(IS2, CNT_ID, cnt_id);

    /* Write ACE counter only */
    return (cnt_id < JR2_ACE_CNT_ID_BASE ? VTSS_RC_OK : jr2_is2_cnt_set(vtss_state, cnt_id, counter));
}

static void jr2_is2_ptp_key_set(jr2_vcap_data_t *data, u32 offset, vtss_ace_u32_t *ptp)
{
    int i, j;
    u8  val[8], msk[8];

    for (i = 0; i < 8; i++) {
        j = (i < 2 ? i :  /* PTP byte 0-1 */
             i == 4 ? 2 : /* PTP byte 4 */
             i == 6 ? 3 : /* PTP byte 6 */
             8);          /* Wildcard */
        val[i] = (j < 4 ? ptp->value[j] : 0);
        msk[i] = (j < 4 ? ptp->mask[j] : 0);
    }
    jr2_vcap_key_bytes_set(data, offset, val, msk, 8);
}

static vtss_rc jr2_is2_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    jr2_vcap_data_t        data;
    vtss_is2_data_t        *is2 = &vcap_data->u.is2;
    vtss_is2_entry_t       *entry = is2->entry;
    vtss_ace_t             *ace = &entry->ace;
    vtss_port_no_t         port_no;
    u32                    addr, port, i, n, range, type = IS2_X8_TYPE_ETYPE, mask = VTSS_BITMASK(IS2_KL_X8_TYPE);
    vtss_ace_frame_any_t   *any = &ace->frame.any;
    vtss_ace_frame_etype_t *etype = &ace->frame.etype;
    vtss_ace_frame_llc_t   *llc = &ace->frame.llc;
    vtss_ace_frame_snap_t  *snap = &ace->frame.snap;
    vtss_ace_frame_arp_t   *arp = &ace->frame.arp;
    vtss_ace_frame_ipv4_t  *ipv4 = &ace->frame.ipv4;
    vtss_ace_frame_ipv6_t  *ipv6 = &ace->frame.ipv6;
    vtss_vcap_u8_t         *proto = NULL, policy = ace->policy;
    vtss_vcap_udp_tcp_t    *sport, *dport;
    vtss_vcap_vid_t        sp, dp;
    vtss_vcap_u128_t       sip, dip;
    u8                     m;
    vtss_ace_u32_t         *ptp;
    BOOL                   tcp, found = 0;
    vtss_vcap_bit_t        oam;

    VTSS_MEMSET(&data, 0, sizeof(data));
    data.tg = (vcap_data->key_size == VTSS_VCAP_KEY_SIZE_FULL ? JR2_VCAP_TG_X16 :
               vcap_data->key_size == VTSS_VCAP_KEY_SIZE_HALF ? JR2_VCAP_TG_X8 : JR2_VCAP_TG_X4);
    addr = jr2_vcap_entry_addr(vtss_state, VTSS_VCAP_TYPE_IS2, idx);
    VTSS_I("row: %u, col: %u, addr: %u, type: %u", idx->row, idx->col, addr, ace->type);

    if (entry->ipmc) {
        /* IPMC rule */
        if (data.tg == JR2_VCAP_TG_X4) {
            jr2_vcap_key_bit_set(&data, IS2_KO_X4_FIRST, VTSS_VCAP_BIT_0);
            jr2_vcap_key_vid_set(&data, IS2_KO_X4_VID, &ace->vlan.vid);
            jr2_vcap_key_ipv4_set(&data, IS2_KO_X4_DIP, &ipv4->dip);
            jr2_vcap_key_ipv4_set(&data, IS2_KO_X4_SIP, &ipv4->sip);
        } else {
            jr2_vcap_key_set(&data, IS2_KO_X8_TYPE, IS2_KL_X8_TYPE, IS2_X8_TYPE_IP6_VID, mask);
            jr2_vcap_key_bit_set(&data, IS2_KO_X8_FIRST, VTSS_VCAP_BIT_0);
            jr2_vcap_key_vid_set(&data, IS2_KO_IP6_VID_VID, &ace->vlan.vid);
            jr2_vcap_key_u128_set(&data, IS2_KO_IP6_VID_DIP, &ipv6->dip);
            jr2_vcap_key_u128_set(&data, IS2_KO_IP6_VID_SIP, &ipv6->sip);
        }
        is2->cnt_id = (JR2_ACE_CNT_ID_BASE - 1); /* Common counter for all IPMC rules */
        VTSS_RC(jr2_is2_action_set(vtss_state, &data, &ace->action, is2->cnt_id, counter));
        return jr2_vcap_entry_cmd(vtss_state, &data, addr, data.tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ALL);
    }

    policy.mask &= VTSS_ACL_POLICY_NO_MAX;
    if (ace->type == VTSS_ACE_TYPE_IPV4) {
        /* IPv4 */
        proto = &ipv4->proto;
        sport = &ipv4->sport;
        dport = &ipv4->dport;
        ptp = (ipv4->ptp.enable ? &ipv4->ptp.header : NULL);
    } else {
        /* IPv6 */
        ipv4 = NULL;
        proto = &ipv6->proto;
        sport = &ipv6->sport;
        dport = &ipv6->dport;
        ptp = (ipv6->ptp.enable ? &ipv6->ptp.header : NULL);
    }
    sp.value = sport->low;
    sp.mask = (sport->in_range && sport->low == sport->high ? 0xffff : 0);
    dp.value = dport->low;
    dp.mask = (dport->in_range && dport->low == dport->high ? 0xffff : 0);
    range = ((is2->srange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->srange)) |
             (is2->drange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->drange)));

    if (data.tg == JR2_VCAP_TG_X16) {
        jr2_vcap_key_set(&data, IS2_KO_X16_TYPE, IS2_KL_X16_TYPE, IS2_X16_TYPE_IP7_TUPLE, 0x3);
        jr2_vcap_key_bit_set(&data, IS2_KO_X16_FIRST, VTSS_VCAP_BIT_1);
        jr2_vcap_key_u8_set(&data, IS2_KO_X16_PAG, &policy);
        jr2_vcap_key_set(&data, IS2_KO_X16_PORT_SEL, IS2_KL_X16_PORT_SEL, 0, 0x3);
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (ace->port_list[port_no] == 0) {
                port = VTSS_CHIP_PORT(port_no);
                jr2_vcap_key_bit_set(&data, IS2_KO_X16_PORT_MASK + port, VTSS_VCAP_BIT_0);
            }
        }
        jr2_ace_key_bit_set(&data, IS2_KO_X16_L2_MC, ace->dmac_mc);
        jr2_ace_key_bit_set(&data, IS2_KO_X16_L2_BC, ace->dmac_bc);
        jr2_vcap_key_bit_set(&data, IS2_KO_X16_SERVICE_FRM, VTSS_VCAP_BIT_ANY);
        jr2_ace_key_bit_set(&data, IS2_KO_X16_VLAN_TAGGED, ace->vlan.tagged);
        jr2_vcap_key_vid_set(&data, IS2_KO_X16_VID, &ace->vlan.vid);
        jr2_vcap_key_u3_set(&data, IS2_KO_X16_PCP, &ace->vlan.usr_prio);
        jr2_ace_key_bit_set(&data, IS2_KO_X16_DEI, ace->vlan.cfi);
        if (is2->entry->host_match) {
            /* Host match for IPv4 */
            jr2_vcap_key_bit_set(&data, IS2_KO_X16_SMAC_SIP, VTSS_VCAP_BIT_1);
        }
        jr2_vcap_key_u48_set(&data, IS2_KO_X16_DMAC, ipv4 ? &ipv4->dmac : &ipv6->dmac);
        jr2_vcap_key_u48_set(&data, IS2_KO_X16_SMAC, ipv4 ? &ipv4->smac : &ipv6->smac);
        jr2_vcap_key_bit_set(&data, IS2_KO_X16_IP4, ipv4 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        jr2_ace_key_bit_set(&data, IS2_KO_X16_TTL, ipv4 ? ipv4->ttl : ipv6->ttl);
        if (ipv4) {
            /* IPv4 */
            VTSS_MEMSET(&sip, 0, sizeof(sip));
            VTSS_MEMSET(&dip, 0, sizeof(dip));
            if (ipv4->fragment != VTSS_ACE_BIT_ANY) {
                // DIP bit 127 is L3_FRAGMENT
                m = (1 << 7);
                dip.value[0] |= (ipv4->fragment == VTSS_ACE_BIT_1 ? m : 0);
                dip.mask[0] |= m;
            }
            if (ipv4->options != VTSS_ACE_BIT_ANY) {
                // DIP bit 125 is L3_OPTIONS
                m = (1 << 5);
                dip.value[0] |= (ipv4->options == VTSS_ACE_BIT_1 ? m : 0);
                dip.mask[0] |= m;
            }
            for (i = 12; i < 16; i++) {
                n = (15 - i)*8;
                sip.value[i] = ((ipv4->sip.value >> n) & 0xff);
                sip.mask[i] = ((ipv4->sip.mask >> n) & 0xff);
                dip.value[i] = ((ipv4->dip.value >> n) & 0xff);
                dip.mask[i] = ((ipv4->dip.mask >> n) & 0xff);
            }
        } else {
            /* IPv6 */
            sip = ipv6->sip;
            dip = ipv6->dip;
        }
        jr2_vcap_key_u8_set(&data, IS2_KO_X16_TOS, ipv4 ? &ipv4->ds : &ipv6->ds);
        jr2_vcap_key_u128_set(&data, IS2_KO_X16_DIP, &dip);
        jr2_vcap_key_u128_set(&data, IS2_KO_X16_SIP, &sip);
        jr2_ace_key_bit_set(&data, IS2_KO_X16_DIP_EQ_SIP, ipv4 ? ipv4->sip_eq_dip : ipv6->sip_eq_dip);

        if (vtss_vcap_udp_tcp_rule(proto)) {
            /* UDP/TCP protocol match */
            tcp = (proto->value == 6 ? 1 : 0);
            jr2_vcap_key_bit_set(&data, IS2_KO_X16_TCP_UDP, VTSS_VCAP_BIT_1);
            jr2_vcap_key_bit_set(&data, IS2_KO_X16_TCP, tcp ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            jr2_vcap_key_set(&data, IS2_KO_X16_DPORT, IS2_KL_X16_DPORT, dp.value, dp.mask);
            jr2_vcap_key_set(&data, IS2_KO_X16_SPORT, IS2_KL_X16_SPORT, sp.value, sp.mask);
            jr2_vcap_key_set(&data, IS2_KO_X16_RANGE, IS2_KL_X16_RANGE, range, range);
            jr2_ace_key_bit_set(&data, IS2_KO_X16_SP_EQ_DP, ipv4 ? ipv4->sport_eq_dport : ipv6->sport_eq_dport);
            if (tcp) {
                jr2_ace_key_bit_set(&data, IS2_KO_X16_SEQ_EQ0, ipv4 ? ipv4->seq_zero : ipv6->seq_zero);
                jr2_ace_key_bit_set(&data, IS2_KO_X16_FIN, ipv4 ? ipv4->tcp_fin : ipv6->tcp_fin);
                jr2_ace_key_bit_set(&data, IS2_KO_X16_SYN, ipv4 ? ipv4->tcp_syn : ipv6->tcp_syn);
                jr2_ace_key_bit_set(&data, IS2_KO_X16_RST, ipv4 ? ipv4->tcp_rst : ipv6->tcp_rst);
                jr2_ace_key_bit_set(&data, IS2_KO_X16_PSH, ipv4 ? ipv4->tcp_psh : ipv6->tcp_psh);
                jr2_ace_key_bit_set(&data, IS2_KO_X16_ACK, ipv4 ? ipv4->tcp_ack : ipv6->tcp_ack);
                jr2_ace_key_bit_set(&data, IS2_KO_X16_URG, ipv4 ? ipv4->tcp_urg : ipv6->tcp_urg);
            }
            if (ptp != NULL) {
                jr2_is2_ptp_key_set(&data, IS2_KO_X16_PAYLOAD, ptp);
            }
        } else if (proto->mask) {
            /* Non-UDP/TCP protocol match */
            jr2_vcap_key_bit_set(&data, IS2_KO_X16_TCP_UDP, VTSS_VCAP_BIT_0);
            jr2_vcap_key_set(&data, IS2_KO_X16_DPORT, IS2_KL_X16_DPORT, proto->value, proto->mask);
            jr2_vcap_key_u48_set(&data, IS2_KO_X16_PAYLOAD + 16, ipv4 ? &ipv4->data : &ipv6->data);
        }
        VTSS_RC(jr2_is2_action_set(vtss_state, &data, &ace->action, is2->cnt_id, counter));
        return jr2_vcap_entry_cmd(vtss_state, &data, addr, data.tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ALL);
    }

    /* Half rule, determine type and mask */
    switch (ace->type) {
    case VTSS_ACE_TYPE_ANY:
        for (i = 0; i < 6; i++) {
            if (any->dmac.mask[i] != 0 || any->smac.mask[i] != 0) {
                found = 1;
                break;
            }
        }
        if (found) {
            /* Match ETYPE/LLC/SNAP frames with DMAC/SMAC filtering */
            jr2_vcap_key_u48_set(&data, IS2_KO_ETYPE_DMAC, &any->dmac);
            jr2_vcap_key_u48_set(&data, IS2_KO_ETYPE_SMAC, &any->smac);
        } else {
            /* Match all frames */
            mask = 0;
        }
        break;
    case VTSS_ACE_TYPE_ETYPE:
        jr2_vcap_key_u48_set(&data, IS2_KO_ETYPE_DMAC, &etype->dmac);
        jr2_vcap_key_u48_set(&data, IS2_KO_ETYPE_SMAC, &etype->smac);
        jr2_vcap_key_bit_set(&data, IS2_KO_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_1);
        oam = (etype->etype.mask[0] == 0xff && etype->etype.mask[1] == 0xff ?
               (etype->etype.value[0] == 0x89 && etype->etype.value[1] == 0x02 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0) :
               VTSS_VCAP_BIT_ANY);
        jr2_vcap_key_bit_set(&data, IS2_KO_ETYPE_OAM, oam);
        if (oam != VTSS_VCAP_BIT_1) {
            jr2_vcap_key_u16_set(&data, IS2_KO_ETYPE_ETYPE, &etype->etype);
        }
        if (etype->ptp.enable) {
            jr2_is2_ptp_key_set(&data, IS2_KO_ETYPE_PAYLOAD, &etype->ptp.header);
        } else {
            jr2_vcap_key_u16_set(&data, IS2_KO_ETYPE_PAYLOAD + 48, &etype->data);
        }
        break;
    case VTSS_ACE_TYPE_LLC:
        jr2_vcap_key_u48_set(&data, IS2_KO_ETYPE_DMAC, &llc->dmac);
        jr2_vcap_key_u48_set(&data, IS2_KO_ETYPE_SMAC, &llc->smac);
        jr2_vcap_key_bit_set(&data, IS2_KO_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_0);
        jr2_vcap_key_u32_set(&data, IS2_KO_ETYPE_PAYLOAD + 32, &llc->llc);
        break;
    case VTSS_ACE_TYPE_SNAP:
        jr2_vcap_key_u48_set(&data, IS2_KO_ETYPE_DMAC, &snap->dmac);
        jr2_vcap_key_u48_set(&data, IS2_KO_ETYPE_SMAC, &snap->smac);
        jr2_vcap_key_bit_set(&data, IS2_KO_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_0);
        for (i = 0; i < 3; i++) {
            /* SNAP header */
            jr2_vcap_key_set(&data, IS2_KO_ETYPE_PAYLOAD + 40 + i*8, 8, i == 0 ? 0x03 : 0xaa, 0xff);
        }
        jr2_vcap_key_u40_set(&data, IS2_KO_ETYPE_PAYLOAD, &snap->snap);
        break;
    case VTSS_ACE_TYPE_ARP:
        type = IS2_X8_TYPE_ARP;
        jr2_vcap_key_u48_set(&data, IS2_KO_ARP_SMAC, &arp->smac);
        jr2_ace_key_bit_set(&data, IS2_KO_ARP_ADDR_OK, arp->ethernet);
        jr2_ace_key_bit_set(&data, IS2_KO_ARP_PROTO_OK, arp->ip);
        jr2_ace_key_bit_set(&data, IS2_KO_ARP_LEN_OK, arp->length);
        jr2_ace_key_bit_set(&data, IS2_KO_ARP_TARGET_MATCH, arp->dmac_match);
        jr2_ace_key_bit_set(&data, IS2_KO_ARP_SENDER_MATCH, arp->smac_match);
        jr2_ace_key_bit_set(&data, IS2_KO_ARP_OPCODE_UNKN, arp->unknown);
        jr2_ace_key_bit_inv_set(&data, IS2_KO_ARP_OPCODE, arp->req);
        jr2_ace_key_bit_inv_set(&data, IS2_KO_ARP_OPCODE + 1, arp->arp);
        jr2_vcap_key_ipv4_set(&data, IS2_KO_ARP_DIP, &arp->dip);
        jr2_vcap_key_ipv4_set(&data, IS2_KO_ARP_SIP, &arp->sip);
        break;
    case VTSS_ACE_TYPE_IPV4:
    case VTSS_ACE_TYPE_IPV6:
        if (ipv4) {
            /* IPv4 */
            jr2_vcap_key_bit_set(&data, IS2_KO_IP4_IP4, VTSS_VCAP_BIT_1);
            jr2_ace_key_bit_set(&data, IS2_KO_IP4_FRAGMENT, ipv4->fragment);
            jr2_ace_key_bit_set(&data, IS2_KO_IP4_OPTIONS, ipv4->options);
            jr2_ace_key_bit_set(&data, IS2_KO_IP4_TTL, ipv4->ttl);
        } else {
            /* IPv6 */
            jr2_vcap_key_bit_set(&data, IS2_KO_IP4_IP4, VTSS_VCAP_BIT_0);
            jr2_ace_key_bit_set(&data, IS2_KO_IP4_TTL, ipv6->ttl);
        }
        jr2_vcap_key_u8_set(&data, IS2_KO_IP4_TOS, ipv4 ? &ipv4->ds : &ipv6->ds);
        if (ipv4) {
            jr2_vcap_key_ipv4_set(&data, IS2_KO_IP4_DIP, &ipv4->dip);
            jr2_vcap_key_ipv4_set(&data, IS2_KO_IP4_SIP, &ipv4->sip);
        } else {
            jr2_vcap_key_bytes_set(&data, IS2_KO_IP4_DIP, &ipv6->sip.value[8], &ipv6->sip.mask[8], 4);
            jr2_vcap_key_bytes_set(&data, IS2_KO_IP4_SIP, &ipv6->sip.value[12], &ipv6->sip.mask[12], 4);
        }
        jr2_ace_key_bit_set(&data, IS2_KO_IP4_DIP_EQ_SIP, ipv4 ? ipv4->sip_eq_dip : ipv6->sip_eq_dip);

        if (vtss_vcap_udp_tcp_rule(proto)) {
            /* UDP/TCP protocol match */
            type = IS2_X8_TYPE_IP_UDP_TCP;
            tcp = (proto->value == 6 ? 1 : 0);
            jr2_vcap_key_bit_set(&data, IS2_KO_IP4_TU_TCP, tcp ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            jr2_vcap_key_set(&data, IS2_KO_IP4_TU_DPORT, IS2_KL_IP4_TU_DPORT, dp.value, dp.mask);
            jr2_vcap_key_set(&data, IS2_KO_IP4_TU_SPORT, IS2_KL_IP4_TU_SPORT, sp.value, sp.mask);
            jr2_vcap_key_set(&data, IS2_KO_IP4_TU_RANGE, IS2_KL_IP4_TU_RANGE, range, range);
            jr2_ace_key_bit_set(&data, IS2_KO_IP4_TU_SP_EQ_DP, ipv4 ? ipv4->sport_eq_dport : ipv6->sport_eq_dport);
            if (tcp) {
                jr2_ace_key_bit_set(&data, IS2_KO_IP4_TU_SEQ_EQ0, ipv4 ? ipv4->seq_zero : ipv6->seq_zero);
                jr2_ace_key_bit_set(&data, IS2_KO_IP4_TU_FIN, ipv4 ? ipv4->tcp_fin : ipv6->tcp_fin);
                jr2_ace_key_bit_set(&data, IS2_KO_IP4_TU_SYN, ipv4 ? ipv4->tcp_syn : ipv6->tcp_syn);
                jr2_ace_key_bit_set(&data, IS2_KO_IP4_TU_RST, ipv4 ? ipv4->tcp_rst : ipv6->tcp_rst);
                jr2_ace_key_bit_set(&data, IS2_KO_IP4_TU_PSH, ipv4 ? ipv4->tcp_psh : ipv6->tcp_psh);
                jr2_ace_key_bit_set(&data, IS2_KO_IP4_TU_ACK, ipv4 ? ipv4->tcp_ack : ipv6->tcp_ack);
                jr2_ace_key_bit_set(&data, IS2_KO_IP4_TU_URG, ipv4 ? ipv4->tcp_urg : ipv6->tcp_urg);
            }
            if (ptp != NULL) {
                jr2_is2_ptp_key_set(&data, IS2_KO_IP4_TU_PAYLOAD, ptp);
            }
        } else if (proto->mask == 0) {
            /* Any IP protocol match */
            type = (IS2_X8_TYPE_IP_UDP_TCP & IS2_X8_TYPE_IP_OTHER);
            mask = type;
        } else {
            /* Non-UDP/TCP protocol match */
            type = IS2_X8_TYPE_IP_OTHER;
            jr2_vcap_key_u8_set(&data, IS2_KO_IP4_OTHER_PROTO, proto);
            jr2_vcap_key_u48_set(&data, IS2_KO_IP4_OTHER_PAYLOAD + 48, ipv4 ? &ipv4->data : &ipv6->data);
        }
        break;
    default:
        VTSS_E("unknown type: %u", ace->type);
        return VTSS_RC_ERROR;
    }

    /* Common key fields */
    jr2_vcap_key_set(&data, IS2_KO_X8_TYPE, IS2_KL_X8_TYPE, type, mask);
    jr2_vcap_key_bit_set(&data, IS2_KO_X8_FIRST, VTSS_VCAP_BIT_1);
    jr2_vcap_key_u8_set(&data, IS2_KO_X8_PAG, &policy);
    jr2_vcap_key_set(&data, IS2_KO_X8_PORT_SEL, IS2_KL_X8_PORT_SEL, 0, 0x3);
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        if (ace->port_list[port_no] == 0) {
            port = VTSS_CHIP_PORT(port_no);
            jr2_vcap_key_bit_set(&data, IS2_KO_X8_PORT_MASK + port, VTSS_VCAP_BIT_0);
        }
    }
    jr2_ace_key_bit_set(&data, IS2_KO_X8_L2_MC, ace->dmac_mc);
    jr2_ace_key_bit_set(&data, IS2_KO_X8_L2_BC, ace->dmac_bc);
    jr2_vcap_key_bit_set(&data, IS2_KO_X8_SERVICE_FRM, VTSS_VCAP_BIT_ANY);
    jr2_ace_key_bit_set(&data, IS2_KO_X8_VLAN_TAGGED, ace->vlan.tagged);
    jr2_vcap_key_vid_set(&data, IS2_KO_X8_VID, &ace->vlan.vid);
    jr2_vcap_key_u3_set(&data, IS2_KO_X8_PCP, &ace->vlan.usr_prio);
    jr2_ace_key_bit_set(&data, IS2_KO_X8_DEI, ace->vlan.cfi);
    if (is2->entry->host_match) {
        /* Host match for IPv4 */
        jr2_vcap_key_bit_set(&data, IS2_KO_X8_SMAC_SIP, VTSS_VCAP_BIT_1);
    }

    /* Setup action */
    VTSS_RC(jr2_is2_action_set(vtss_state, &data, &ace->action, is2->cnt_id, counter));

    return jr2_vcap_entry_cmd(vtss_state, &data, addr, data.tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ALL);
}

static vtss_rc jr2_is2_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return jr2_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_IS2, idx);
}

static vtss_rc jr2_is2_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return jr2_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_IS2, idx, count, up);
}

static vtss_rc jr2_is2_entry_get(vtss_state_t *vtss_state,
                                 vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    jr2_vcap_data_t data;
    u32             addr, cnt_id;

    VTSS_MEMSET(&data, 0, sizeof(data));
    data.vcap_type = VTSS_VCAP_TYPE_IS2;
    data.tg = JR2_VCAP_TG_X8;
    data.type = JR2_VCAP_TG_X4;
    addr = jr2_vcap_entry_addr(vtss_state, data.vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u", idx->row, idx->col, addr);
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, &data, addr, data.tg, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));
    cnt_id = jr2_act_get(&data, IS2_AO_CNT_ID, IS2_AL_CNT_ID);
    VTSS_RC(jr2_is2_cnt_get(vtss_state, cnt_id, counter));
    return (clear ? jr2_is2_cnt_set(vtss_state, cnt_id, 0) : VTSS_RC_OK);
}

static vtss_rc jr2_is2_entry_update(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_is2_data_t *is2)
{
#if VTSS_OPT_TRACE
    const jr2_vcap_props_t *vcap = &jr2_vcap_info[JR2_VCAP_SUPER];
#endif
    jr2_vcap_data_t        jr2_data, *data = &jr2_data;
    vtss_port_no_t         port_no;
    u32                    addr, port, member;

    data->vcap_type = VTSS_VCAP_TYPE_IS2;
    data->tg = JR2_VCAP_TG_X1;
    addr = jr2_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u", vcap->name, idx->row, idx->col, addr);

    /* Read action */
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));

    /* Update action fields */
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        member = (VTSS_PORT_BF_GET(is2->action.member, port_no) && vtss_state->l2.tx_forward_aggr[port_no]);
        jr2_act_set(data, IS2_AO_PORT_MASK + port, 1, member);
    }

    /* Write action */
    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION);
}

static vtss_rc jr2_debug_is2(vtss_state_t *vtss_state, jr2_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 type, cnt_id, cnt;

    if (data->vcap_type != VTSS_VCAP_TYPE_IS2) {
        VTSS_E("not TYPE_IS2");
        return VTSS_RC_ERROR;
    }

    if (data->is_action) {
        /* Show action fields */
        JR2_DEBUG_ACT_BITS(IS2, "is_inner_acl", IS_INNER_ACL);
        JR2_DEBUG_ACT_ENA(IS2, "pipeline", PL);
        JR2_DEBUG_ACT_BITS(IS2, "intr_ena", INTR_ENA);
        JR2_DEBUG_ACT_BITS(IS2, "hit", HIT_ME_ONCE);
        JR2_DEBUG_ACT_ENA(IS2, "cpu", CPU);
        JR2_DEBUG_ACT_BITS(IS2, "cpu_dis", CPU_DIS);
        pr("\n");
        JR2_DEBUG_ACT_BITS(IS2, "lrn_dis", LRN_DIS);
        JR2_DEBUG_ACT_BITS(IS2, "rt_dis", RT_DIS);
        JR2_DEBUG_ACT_ENA(IS2, "police", POLICE);
        JR2_DEBUG_ACT_BITS(IS2, "ignore_pl_ctrl", IGNORE_PL_CTRL);
        JR2_DEBUG_ACT(IS2, "dlb_offset", DLB_OFFSET);
        JR2_DEBUG_ACT(IS2, "mask_mode", MASK_MODE);
        pr("\n");
        JR2_DEBUG_ACT_BITS(IS2, "port_mask", PORT_MASK);
        JR2_DEBUG_ACT(IS2, "mirror_probe", MIRROR_PROBE);
        JR2_DEBUG_ACT(IS2, "rew_ptp", REW_PTP);
        JR2_DEBUG_ACT(IS2, "rew_delay", REW_DELAY);
        JR2_DEBUG_ACT(IS2, "rew_seq_ts", REW_SEQ_TS);
        JR2_DEBUG_ACT_BITS(IS2, "rew_dmac", REW_DMAC);
        JR2_DEBUG_ACT_BITS(IS2, "rew_smac", REW_SMAC);
        pr("\n");
        JR2_DEBUG_ACT_BITS(IS2, "ttl_update", TTL_UPDATE);
        JR2_DEBUG_ACT_BITS(IS2, "sam_seq_ena", SAM_SEQ_ENA);
        JR2_DEBUG_ACT_BITS(IS2, "tcp_udp_ena", TCP_UDP_ENA);
        JR2_DEBUG_ACT(IS2, "match_id", MATCH_ID);
        JR2_DEBUG_ACT(IS2, "match_mask", MATCH_MASK);
        JR2_DEBUG_ACT(IS2, "cnt_id", CNT_ID);
        pr("\n");
        JR2_DEBUG_ACT_BITS(IS2, "swap_mac", SWAP_MAC);
        JR2_DEBUG_ACT(IS2, "acl_rt_mode", ACL_RT_MODE);
        JR2_DEBUG_ACT(IS2, "ptp_dom", PTP_DOM);
        pr("\n");
        JR2_DEBUG_ACT_BITS(IS2, "acl_mac", ACL_MAC);
        cnt_id = jr2_act_get(data, IS2_AO_CNT_ID, IS2_AL_CNT_ID);
        VTSS_RC(jr2_is2_cnt_get(vtss_state, cnt_id, &cnt));
        pr("cnt[%u]: %u, cnt: %u", cnt_id, cnt, data->counter);
        return VTSS_RC_OK;
    }

    /* Show key fields */
    if (data->tg == JR2_VCAP_TG_X4) {
        JR2_DEBUG_BITS(IS2, "first", X4_FIRST);
        JR2_DEBUG_BITS(IS2, "pag", X4_PAG);
        JR2_DEBUG_BITS(IS2, "vid", X4_VID);
        JR2_DEBUG_BITS(IS2, "smac_sip", X4_SMAC_SIP);
        JR2_DEBUG_BITS(IS2, "dmac_dip", X4_DMAC_DIP);
        JR2_DEBUG_BITS(IS2, "l3_rt", X4_L3_RT);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "dip", X4_DIP);
        JR2_DEBUG_BITS(IS2, "sip", X4_SIP);
        return VTSS_RC_OK;
    }

    if (data->tg == JR2_VCAP_TG_X16) {
        JR2_DEBUG_BITS(IS2, "type", X16_TYPE);
        type = jr2_entry_bs_get(data, IS2_KO_X16_TYPE, IS2_KL_X16_TYPE);
        pr("(%s) ",
           type == IS2_X16_TYPE_IP7_TUPLE ? "ip7_tuple" :
           type == IS2_X16_TYPE_CUSTOM_1 ? "custom_2" : "?");
        JR2_DEBUG_BITS(IS2, "first", X16_FIRST);
        JR2_DEBUG_BITS(IS2, "pag", X16_PAG);
        JR2_DEBUG_BITS(IS2, "igr_sel", X16_PORT_SEL);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "igr_mask", X16_PORT_MASK);
        JR2_DEBUG_BITS(IS2, "l2_mc", X16_L2_MC);
        JR2_DEBUG_BITS(IS2, "l2_bc", X16_L2_BC);
        JR2_DEBUG_BITS(IS2, "service_frm", X16_SERVICE_FRM);
        JR2_DEBUG_BITS(IS2, "l2_fwd", X16_L2_FWD);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "tagged", X16_VLAN_TAGGED);
        JR2_DEBUG_BITS(IS2, "vid", X16_VID);
        JR2_DEBUG_BITS(IS2, "pcp", X16_PCP);
        JR2_DEBUG_BITS(IS2, "dei", X16_DEI);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "smac_sip", X16_SMAC_SIP);
        JR2_DEBUG_BITS(IS2, "dmac_dip", X16_DMAC_DIP);
        if (type != IS2_X16_TYPE_IP7_TUPLE) {
            return VTSS_RC_OK;
        }
        JR2_DEBUG_BITS(IS2, "l3_rt", X16_L3_RT);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "dmac", X16_DMAC);
        JR2_DEBUG_BITS(IS2, "smac", X16_SMAC);
        JR2_DEBUG_BITS(IS2, "ip4", X16_IP4);
        JR2_DEBUG_BITS(IS2, "ttl", X16_TTL);
        JR2_DEBUG_BITS(IS2, "tos", X16_TOS);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "dip", X16_DIP);
        JR2_DEBUG_BITS(IS2, "sip", X16_SIP);
        JR2_DEBUG_BITS(IS2, "dip_eq_sip", X16_DIP_EQ_SIP);
        JR2_DEBUG_BITS(IS2, "tcp_udp", X16_TCP_UDP);
        JR2_DEBUG_BITS(IS2, "tcp", X16_TCP);
        JR2_DEBUG_BITS(IS2, "dport", X16_DPORT);
        JR2_DEBUG_BITS(IS2, "sport", X16_SPORT);
        JR2_DEBUG_BITS(IS2, "range", X16_RANGE);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "sp_eq_dp", X16_SP_EQ_DP);
        JR2_DEBUG_BITS(IS2, "seq_eq0", X16_SEQ_EQ0);
        JR2_DEBUG_BITS(IS2, "fin", X16_FIN);
        JR2_DEBUG_BITS(IS2, "syn", X16_SYN);
        JR2_DEBUG_BITS(IS2, "rst", X16_RST);
        JR2_DEBUG_BITS(IS2, "psh", X16_PSH);
        JR2_DEBUG_BITS(IS2, "ack", X16_ACK);
        JR2_DEBUG_BITS(IS2, "urg", X16_URG);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "payload", X16_PAYLOAD);
        return VTSS_RC_OK;
    }

    if (data->tg != JR2_VCAP_TG_X8) {
        VTSS_E("not TG_X8: %u", data->tg);
        return VTSS_RC_ERROR;
    }

    JR2_DEBUG_BITS(IS2, "type", X8_TYPE);
    type = jr2_entry_bs_get(data, IS2_KO_X8_TYPE, IS2_KL_X8_TYPE);
    pr("(%s) ",
       jr2_mask_bs_get(data, IS2_KO_X8_TYPE, IS2_KL_X8_TYPE) == 0 ? "any" :
       type == IS2_X8_TYPE_ETYPE ? "etype" :
       type == IS2_X8_TYPE_ARP ? "arp" :
       type == IS2_X8_TYPE_IP_UDP_TCP ? "ip_udp_tcp" :
       type == IS2_X8_TYPE_IP_OTHER ? "ip_other" :
       type == IS2_X8_TYPE_CUSTOM_2 ? "custom_2" :
       type == IS2_X8_TYPE_IP6_VID ? "ip6_vid" : "?");
    JR2_DEBUG_BITS(IS2, "first", X8_FIRST);
    JR2_DEBUG_BITS(IS2, "pag", X8_PAG);

    switch (type) {
    case IS2_X8_TYPE_ETYPE:
    case IS2_X8_TYPE_ARP:
    case IS2_X8_TYPE_IP_UDP_TCP:
    case IS2_X8_TYPE_IP_OTHER:
    case IS2_X8_TYPE_CUSTOM_2:
        JR2_DEBUG_BITS(IS2, "igr_sel", X8_PORT_SEL);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "igr_mask", X8_PORT_MASK);
        JR2_DEBUG_BITS(IS2, "l2_mc", X8_L2_MC);
        JR2_DEBUG_BITS(IS2, "l2_bc", X8_L2_BC);
        JR2_DEBUG_BITS(IS2, "service_frm", X8_SERVICE_FRM);
        JR2_DEBUG_BITS(IS2, "l2_fwd", X8_L2_FWD);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "tagged", X8_VLAN_TAGGED);
        JR2_DEBUG_BITS(IS2, "vid", X8_VID);
        JR2_DEBUG_BITS(IS2, "pcp", X8_PCP);
        JR2_DEBUG_BITS(IS2, "dei", X8_DEI);
        pr("\n");
        if (type == IS2_X8_TYPE_ARP) {
            JR2_DEBUG_BITS(IS2, "smac", ARP_SMAC);
            JR2_DEBUG_BITS(IS2, "addr_ok", ARP_ADDR_OK);
            JR2_DEBUG_BITS(IS2, "proto_ok", ARP_PROTO_OK);
            JR2_DEBUG_BITS(IS2, "len_ok", ARP_LEN_OK);
            JR2_DEBUG_BITS(IS2, "target_match", ARP_TARGET_MATCH);
            JR2_DEBUG_BITS(IS2, "sender_match", ARP_SENDER_MATCH);
            pr("\n");
            JR2_DEBUG_BITS(IS2, "opcode_unkn", ARP_OPCODE_UNKN);
            JR2_DEBUG_BITS(IS2, "opcode", ARP_OPCODE);
            JR2_DEBUG_BITS(IS2, "dip_eq_sip", ARP_DIP_EQ_SIP);
            pr("\n");
            JR2_DEBUG_BITS(IS2, "dip", ARP_DIP);
            JR2_DEBUG_BITS(IS2, "sip", ARP_SIP);
            break;
        }
        JR2_DEBUG_BITS(IS2, "smac_sip", X8_SMAC_SIP);
        JR2_DEBUG_BITS(IS2, "dmac_dip", X8_DMAC_DIP);
        JR2_DEBUG_BITS(IS2, "l3_rt", X8_L3_RT);
        pr("\n");
        if (type == IS2_X8_TYPE_ETYPE) {
            JR2_DEBUG_BITS(IS2, "dmac", ETYPE_DMAC);
            JR2_DEBUG_BITS(IS2, "smac", ETYPE_SMAC);
            JR2_DEBUG_BITS(IS2, "etype_len", ETYPE_ETYPE_LEN);
            JR2_DEBUG_BITS(IS2, "etype", ETYPE_ETYPE);
            JR2_DEBUG_BITS(IS2, "ccm_cnt_eq0", ETYPE_CCM_CNT_EQ0);
            JR2_DEBUG_BITS(IS2, "oam", ETYPE_OAM);
            pr("\n");
            JR2_DEBUG_BITS(IS2, "payload", ETYPE_PAYLOAD);
        } else if (type == IS2_X8_TYPE_CUSTOM_2) {
            JR2_DEBUG_BITS(IS2, "payload", CUSTOM_2_PAYLOAD);
        } else {
            /* IP_OTHER or IP_UDP_TCP */
            JR2_DEBUG_BITS(IS2, "ip4", IP4_IP4);
            JR2_DEBUG_BITS(IS2, "frag", IP4_FRAGMENT);
            JR2_DEBUG_BITS(IS2, "frag_offs", IP4_FRAG_OFFS);
            JR2_DEBUG_BITS(IS2, "options", IP4_OPTIONS);
            JR2_DEBUG_BITS(IS2, "ttl", IP4_TTL);
            JR2_DEBUG_BITS(IS2, "tos", IP4_TOS);
            JR2_DEBUG_BITS(IS2, "dip_eq_sip", IP4_DIP_EQ_SIP);
            pr("\n");
            JR2_DEBUG_BITS(IS2, "dip", IP4_DIP);
            JR2_DEBUG_BITS(IS2, "sip", IP4_SIP);
            if (type == IS2_X8_TYPE_IP_OTHER) {
                JR2_DEBUG_BITS(IS2, "proto", IP4_OTHER_PROTO);
                pr("\n");
                JR2_DEBUG_BITS(IS2, "payload", IP4_OTHER_PAYLOAD);
            } else {
                JR2_DEBUG_BITS(IS2, "tcp", IP4_TU_TCP);
                JR2_DEBUG_BITS(IS2, "dport", IP4_TU_DPORT);
                JR2_DEBUG_BITS(IS2, "sport", IP4_TU_SPORT);
                JR2_DEBUG_BITS(IS2, "range", IP4_TU_RANGE);
                pr("\n");
                JR2_DEBUG_BITS(IS2, "sp_eq_dp", IP4_TU_SP_EQ_DP);
                JR2_DEBUG_BITS(IS2, "seq_eq0", IP4_TU_SEQ_EQ0);
                JR2_DEBUG_BITS(IS2, "fin", IP4_TU_FIN);
                JR2_DEBUG_BITS(IS2, "syn", IP4_TU_SYN);
                JR2_DEBUG_BITS(IS2, "rst", IP4_TU_RST);
                JR2_DEBUG_BITS(IS2, "psh", IP4_TU_PSH);
                JR2_DEBUG_BITS(IS2, "ack", IP4_TU_ACK);
                JR2_DEBUG_BITS(IS2, "urg", IP4_TU_URG);
                pr("\n");
                JR2_DEBUG_BITS(IS2, "payload", IP4_TU_PAYLOAD);
            }
        }
        break;
    case IS2_X8_TYPE_IP6_VID:
        pr("\n");
        JR2_DEBUG_BITS(IS2, "vid", IP6_VID_VID);
        JR2_DEBUG_BITS(IS2, "smac_sip", IP6_VID_SMAC_SIP);
        JR2_DEBUG_BITS(IS2, "dmac_dip", IP6_VID_DMAC_DIP);
        JR2_DEBUG_BITS(IS2, "l3_rt", IP6_VID_L3_RT);
        pr("\n");
        JR2_DEBUG_BITS(IS2, "dip", IP6_VID_DIP);
        JR2_DEBUG_BITS(IS2, "sip", IP6_VID_SIP);
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

/* - ES0 ----------------------------------------------------------- */

/* (Selection, value) pair */
typedef struct {
    u32 sel;
    u32 val;
} jr2_es0_sel_t;

/* ES0 tag related fields */
typedef struct {
    u32           tag_sel;
    u32           tpid_sel;
    jr2_es0_sel_t vid;
    jr2_es0_sel_t pcp;
    jr2_es0_sel_t dei;
} jr2_es0_tag_t;

static void jr2_es0_tag_get(vtss_es0_action_t *action, BOOL inner, jr2_es0_tag_t *tag)
{
    vtss_es0_tag_conf_t *conf;

    if (inner) {
        conf = &action->inner_tag;
        tag->tag_sel = (conf->tag == VTSS_ES0_TAG_NONE ? 0 : 1);
    } else {
        conf = &action->outer_tag;
        tag->tag_sel = (conf->tag == VTSS_ES0_TAG_NONE ? ES0_ACT_PUSH_OT_NONE :
                        conf->tag == VTSS_ES0_TAG_ES0 ? ES0_ACT_PUSH_OT_ES0 :
                        ES0_ACT_PUSH_OT_PORT_ENA);
    }
    tag->tpid_sel = (conf->tpid == VTSS_ES0_TPID_C ? ES0_ACT_TPID_SEL_C :
                     conf->tpid == VTSS_ES0_TPID_S ? ES0_ACT_TPID_SEL_S : ES0_ACT_TPID_SEL_CUSTOM_1);
    tag->vid.sel = (conf->vid.sel ? 1 : 0);
    tag->vid.val = (conf->vid.sel ? conf->vid.val : 0);
    /* Mapped PCP (VTSS_ES0_PCP_MAPPED) is not supported by the device */
    tag->pcp.sel = (conf->pcp.sel == VTSS_ES0_PCP_CLASS ? ES0_ACT_PCP_SEL_CL_PCP : ES0_ACT_PCP_SEL_PCP_ES0);
    tag->pcp.val = conf->pcp.val;
    tag->dei.sel = (conf->dei.sel == VTSS_ES0_DEI_CLASS ? ES0_ACT_DEI_SEL_CL_DEI :
                    conf->dei.sel == VTSS_ES0_DEI_ES0 ? ES0_ACT_DEI_SEL_DEI_ES0 : ES0_ACT_DEI_SEL_MAPPED);
    tag->dei.val = (conf->dei.val ? 1 : 0);
}

typedef struct {
    u32 idx;
    u32 res;
    u32 key;
    u32 act;
} jr2_es0_map_t;

static BOOL jr2_es0_map_update(vtss_state_t *vtss_state, vtss_qos_egress_map_id_t map_id, jr2_es0_map_t *map)
{
    VTSS_MEMSET(map, 0, sizeof(*map));
    if (map_id < VTSS_QOS_EGRESS_MAP_IDS) {
        const vtss_qos_map_adm_t *const m = &vtss_state->qos.emap;

        map->idx = m->id.entry[map_id].ix;  // Index bits 11:3 in VCAP_ES0 MAP_n_IDX

        if (map->idx == VTSS_QOS_EGRESS_MAP_ID_NONE) {
            map->idx = 0;
            return FALSE; // Trying to use an undefined map
        }

        map->res = m->id.entry[map_id].res; // 0 = Resource A, 1 = Resource B

        switch (m->ix[map->res].entry[map->idx].key) { // Remap to index bits 2:0 in VCAP_ES0 MAP_n_KEY
        case VTSS_QOS_EGRESS_MAP_KEY_COSID:
            map->key = 13;
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_COSID_DPL:
            map->key = 14;
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_DSCP:
            map->key = 2;
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_DSCP_DPL:
            map->key = 3;
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC:
            map->key = 8;
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL:
            map->key = 9;
            break;
        default:
            VTSS_E("illegal egress map key");
            return FALSE;
        }

        map->act = m->ix[map->res].entry[map->idx].flags;  // Actions from configuration defined by VTSS_QOS_EGRESS_MAP_ACTION_xxxx
        return TRUE;
    }
    return FALSE;
}

#if defined(VTSS_FEATURE_MPLS)
// Update MPLS encap's per-label TC_SEL to the same as the ES0 entry (if the label TC_SELs are configured for
// mapping, of course). We do this per EVC, fully realizing that there is a conflict if multiple EVCs
// use the same encap but with different maps. It's up to the application to ensure this isn't the case.
static vtss_rc jr2_mpls_encap_tc_sel_update(vtss_state_t *vtss_state, u32 encap_idx, u32 tc_sel)
{
    u32 val, labels;

    if (encap_idx > 0) {
        // Label stack
        JR2_RD(VTSS_REW_ENCAP_MPLS_LABEL_CFG(encap_idx), &val);
        labels = VTSS_X_REW_ENCAP_MPLS_LABEL_CFG_LABEL_CNT(val);
        for (; labels > 0; labels--) {
            JR2_RD(VTSS_REW_ENCAP_MPLS_REMARK_CFG(encap_idx, labels - 1), &val);
            val = VTSS_X_REW_ENCAP_MPLS_REMARK_CFG_TC_SEL(val);
            if (val != ES0_ACT_TC_SEL_ES0) {
                // Overwrite Classified or Mapped TC_SEL. Fixed isn't updated, that comes from Pipe tunnel mode
                JR2_WRM(VTSS_REW_ENCAP_MPLS_REMARK_CFG(encap_idx, labels - 1), VTSS_F_REW_ENCAP_MPLS_REMARK_CFG_TC_SEL(tc_sel), VTSS_M_REW_ENCAP_MPLS_REMARK_CFG_TC_SEL);
            }
        }
        // Reserved label
        JR2_RD(VTSS_REW_ENCAP_RSV_LABEL_CFG(encap_idx), &val);
        val = VTSS_F_REW_ENCAP_RSV_LABEL_CFG_RSV_TC_SEL(val);
        if (val != ES0_ACT_TC_SEL_ES0) {
            JR2_WRM(VTSS_REW_ENCAP_RSV_LABEL_CFG(encap_idx), VTSS_F_REW_ENCAP_RSV_LABEL_CFG_RSV_TC_SEL(tc_sel), VTSS_M_REW_ENCAP_RSV_LABEL_CFG_RSV_TC_SEL);
        }
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_MPLS */

static vtss_rc jr2_es0_action_update(vtss_state_t *vtss_state, jr2_vcap_data_t *data, vtss_es0_data_t *es0)
{
    vtss_es0_action_t        *action = &es0->entry->action;
    jr2_es0_map_t            map;
    vtss_qos_egress_map_id_t map_id;
    u32                      dscp_sel = ES0_ACT_DSCP_SEL_PORT;
    u32                      tc_sel   = ES0_ACT_TC_SEL_CL;        // Default: Use classified TC if mapping is desired but there's no usable mapping
    jr2_es0_tag_t            tag;

    jr2_es0_tag_get(action, 0, &tag);
    map_id = (es0->flags & VTSS_ES0_FLAG_MAP_ID_OT ? es0->map_id_ot :
              es0->flags & VTSS_ES0_FLAG_OT_QOS ? vtss_state->qos.port_conf[es0->port_no].egress_map :
              VTSS_QOS_EGRESS_MAP_ID_NONE);

    VTSS_I("ot map: %u", map_id);
    if (jr2_es0_map_update(vtss_state, map_id, &map)) {
        /* Outer tag map ID used */
        if ((map.act & VTSS_QOS_EGRESS_MAP_ACTION_PCP) && (es0->flags & (VTSS_ES0_FLAG_MAP_OT_PCP | VTSS_ES0_FLAG_OT_PCP))) {
            tag.pcp.sel = (map.res ? ES0_ACT_PCP_SEL_MAP_2 : ES0_ACT_PCP_SEL_MAP_0);
        }
        if ((map.act & VTSS_QOS_EGRESS_MAP_ACTION_DEI) && (es0->flags & (VTSS_ES0_FLAG_MAP_OT_DEI | VTSS_ES0_FLAG_OT_DEI))) {
            tag.dei.sel = (map.res ? ES0_ACT_DEI_SEL_MAP_2 : ES0_ACT_DEI_SEL_MAP_0);
        }
        if (map.act & VTSS_QOS_EGRESS_MAP_ACTION_DSCP) {
            dscp_sel = (map.res ? ES0_ACT_DSCP_SEL_MAP_2 : ES0_ACT_DSCP_SEL_MAP_0);
        }
        if (map.act & VTSS_QOS_EGRESS_MAP_ACTION_MPLS_TC) {
            tc_sel = (map.res ? ES0_ACT_TC_SEL_MAP_2 : ES0_ACT_TC_SEL_MAP_0);
        }
    }
    JR2_ACT_SET(ES0, TAG_A_PCP_SEL, tag.pcp.sel);
    JR2_ACT_SET(ES0, TAG_A_DEI_SEL, tag.dei.sel);
    JR2_ACT_SET(ES0, MAP_0_IDX, map.idx);
    JR2_ACT_SET(ES0, MAP_0_KEY, map.key);
    JR2_ACT_SET(ES0, MAP_2_IDX, map.idx);
    JR2_ACT_SET(ES0, MAP_2_KEY, map.key);
    JR2_ACT_SET(ES0, DSCP_SEL,  dscp_sel);
    JR2_ACT_SET(ES0, ESDX_BASE, es0->esdx ? es0->esdx : 1); // Avoid using esdx_base 0 as default

    jr2_es0_tag_get(action, 1, &tag);
    map_id = (es0->flags & VTSS_ES0_FLAG_MAP_ID_IT ? es0->map_id_it :
              es0->flags & VTSS_ES0_FLAG_IT_QOS ? vtss_state->qos.port_conf[es0->port_no].egress_map :
              VTSS_QOS_EGRESS_MAP_ID_NONE);
    VTSS_I("it map: %u", map_id);
    if (jr2_es0_map_update(vtss_state, map_id, &map)) {
        /* Inner tag map ID used */
        if ((map.act & VTSS_QOS_EGRESS_MAP_ACTION_PCP) && (es0->flags & (VTSS_ES0_FLAG_MAP_IT_PCP | VTSS_ES0_FLAG_IT_PCP))) {
            tag.pcp.sel = (map.res ? ES0_ACT_PCP_SEL_MAP_3 : ES0_ACT_PCP_SEL_MAP_1);
        }
        if ((map.act & VTSS_QOS_EGRESS_MAP_ACTION_DEI) && (es0->flags & (VTSS_ES0_FLAG_MAP_IT_DEI | VTSS_ES0_FLAG_IT_DEI))) {
            tag.dei.sel = (map.res ? ES0_ACT_DEI_SEL_MAP_3 : ES0_ACT_DEI_SEL_MAP_1);
        }
        if (map.act & VTSS_QOS_EGRESS_MAP_ACTION_MPLS_TC) {
            tc_sel = (map.res ? ES0_ACT_TC_SEL_MAP_3 : ES0_ACT_TC_SEL_MAP_1);        // Inner tag wins, in case both try to set
        }
    }
    JR2_ACT_SET(ES0, TAG_B_PCP_SEL, tag.pcp.sel);
    JR2_ACT_SET(ES0, TAG_B_DEI_SEL, tag.dei.sel);
    JR2_ACT_SET(ES0, MAP_1_IDX, map.idx);
    JR2_ACT_SET(ES0, MAP_1_KEY, map.key);
    JR2_ACT_SET(ES0, MAP_3_IDX, map.idx);
    JR2_ACT_SET(ES0, MAP_3_KEY, map.key);

#if defined(VTSS_FEATURE_MPLS)
    if (es0->flags & VTSS_ES0_FLAG_MAP_ID_TC) {
        VTSS_I("MPLS TC setup: SEL %u encap %d", tc_sel, es0->mpls_encap_idx);
        JR2_ACT_SET(ES0, TC_SEL, tc_sel);
        (void) jr2_mpls_encap_tc_sel_update(vtss_state,  es0->mpls_encap_idx, tc_sel);
    }
#else
    if (tc_sel) { /* Kill compiler warning */ }
#endif /* VTSS_FEATURE_MPLS */
    return VTSS_RC_OK;
}

static void jr2_es0_outer_tag_update(vtss_state_t *vtss_state, jr2_vcap_data_t *data, jr2_es0_tag_t *tag)
{
    JR2_ACT_SET(ES0, PUSH_OUTER_TAG, tag->tag_sel);
    JR2_ACT_SET(ES0, TAG_A_TPID_SEL, tag->tpid_sel);
    JR2_ACT_SET(ES0, TAG_A_VID_SEL, tag->vid.sel);
    JR2_ACT_SET(ES0, VID_A_VAL, tag->vid.val);
    JR2_ACT_SET(ES0, TAG_A_PCP_SEL, tag->pcp.sel);
    JR2_ACT_SET(ES0, PCP_A_VAL, tag->pcp.val);
    JR2_ACT_SET(ES0, TAG_A_DEI_SEL, tag->dei.sel);
    JR2_ACT_SET(ES0, DEI_A_VAL, tag->dei.val);
}

static vtss_rc jr2_es0_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    jr2_vcap_data_t   jr2_data, *data = &jr2_data;
    vtss_es0_data_t   *es0 = &vcap_data->u.es0;
    vtss_es0_key_t    *key = &es0->entry->key;
    vtss_es0_action_t *action = &es0->entry->action;
    jr2_es0_tag_t     tag;
    u32               addr, port = 0, mask = 0, vid_isdx;
    BOOL              key_isdx = (key->type == VTSS_ES0_TYPE_ISDX ? 1 : 0);

    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    data->tg = JR2_VCAP_TG_X1;
    data->type = JR2_VCAP_TG_X1;
    addr = jr2_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u", idx->row, idx->col, addr);

    /* Key fields */
    jr2_vcap_key_set(data, ES0_KO_TYPE, ES0_KL_TYPE, key_isdx ? ES0_TYPE_ISDX : ES0_TYPE_VID, VTSS_BITMASK(ES0_KL_TYPE));
    if (key->port_no != VTSS_PORT_NO_NONE) {
        port = VTSS_CHIP_PORT(key->port_no);
        mask = VTSS_BITMASK(ES0_KL_EGR_PORT);
    }
    jr2_vcap_key_set(data, ES0_KO_EGR_PORT, ES0_KL_EGR_PORT, port, mask);
    jr2_vcap_key_set(data, ES0_KO_VSI, ES0_KL_VSI, key->vsi, key->vsi_enable ? VTSS_BITMASK(ES0_KL_VSI) : 0);
    jr2_vcap_key_bit_set(data, ES0_KO_SERVICE_FRM, key->isdx_neq0);
    mask = VTSS_BITMASK(ES0_KL_VID_ISDX);
    if (key_isdx) {
        vid_isdx = key->data.isdx.isdx;
        if (!key->data.isdx.isdx_enable) {
            /* Match all ISDX values */
            mask = 0;
        }
    } else {
        vid_isdx = key->data.vid.vid;
        if (vid_isdx == VTSS_VID_ALL || key->vid_any) {
            /* Match all VID values */
            mask = 0;
        }
    }
    jr2_vcap_key_set(data, ES0_KO_VID_ISDX, ES0_KL_VID_ISDX, vid_isdx, mask);

    /* Action fields */
    /* Outer tag */
    vtss_cmn_es0_action_get(vtss_state, es0);
    jr2_es0_tag_get(action, 0, &tag);
    jr2_es0_outer_tag_update(vtss_state, data, &tag);

    /* Inner tag */
    jr2_es0_tag_get(action, 1, &tag);
    JR2_ACT_SET(ES0, PUSH_INNER_TAG, tag.tag_sel);
    JR2_ACT_SET(ES0, TAG_B_TPID_SEL, tag.tpid_sel);
    JR2_ACT_SET(ES0, TAG_B_VID_SEL, tag.vid.sel);
    JR2_ACT_SET(ES0, VID_B_VAL, tag.vid.val);
    JR2_ACT_SET(ES0, TAG_B_PCP_SEL, tag.pcp.sel);
    JR2_ACT_SET(ES0, PCP_B_VAL, tag.pcp.val);
    JR2_ACT_SET(ES0, TAG_B_DEI_SEL, tag.dei.sel);
    JR2_ACT_SET(ES0, DEI_B_VAL, tag.dei.val);

    JR2_ACT_SET(ES0, POP_VAL, action->pop_cnt);
    JR2_ACT_ENA_SET(ES0, OAM_MEP, action->mep_idx_enable, action->mep_idx);
    JR2_ACT_SET(ES0, ESDX_COSID_OFFS, action->esdx_cosid_offset);

    JR2_ACT_SET(ES0, MIP_IDX, vtss_j2_voi_idx_to_mip_idx(action->voi_idx));
    JR2_ACT_SET(ES0, FWD_SEL, action->forward_sel);
    JR2_ACT_SET(ES0, PL_PT, action->pipe_pt);
    JR2_ACT_SET(ES0, CPU_QUEUE, action->cpu_queue);
    JR2_ACT_SET(ES0, INDEP_MEL_ENA, action->independent_mel);

    /* MPLS-specific */
    JR2_ACT_SET(ES0, ENCAP_ID, action->mpls_encap_idx);
    JR2_ACT_SET(ES0, LABEL_SEL, action->mpls_label_sel);
    JR2_ACT_SET(ES0, TC_SEL, action->mpls_tc_sel);
    JR2_ACT_SET(ES0, SBIT_SEL, action->mpls_sbit_sel);
    JR2_ACT_SET(ES0, TTL_SEL, action->mpls_ttl_sel);
    JR2_ACT_SET(ES0, MPLS_LABEL, action->mpls_label_val);
    JR2_ACT_SET(ES0, TC_VAL, action->mpls_tc_val);
    JR2_ACT_SET(ES0, SBIT_VAL, action->mpls_sbit_val);
    JR2_ACT_SET(ES0, TTL_VAL, action->mpls_ttl_val);
    JR2_ACT_SET(ES0, CW_DIS, action->mpls_cw_disable ? 1 : 0);

#if !defined(VTSS_ARCH_JAGUAR_2_B)
    JR2_ACT_SET(ES0, PL_ACT, action->pipe_act);
    JR2_ACT_SET(ES0, SWAP_MAC_ENA, action->mac_swap_enable);
#endif /* VTSS_ARCH_JAGUAR_2_B */

    /* Update action fields based on egress QoS mapping */
    VTSS_RC(jr2_es0_action_update(vtss_state, data, es0));

    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ALL);
}

static vtss_rc jr2_es0_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return jr2_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_ES0, idx);
}

static vtss_rc jr2_es0_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return jr2_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_ES0, idx, count, up);
}

static vtss_rc jr2_es0_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return jr2_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_ES0, idx, counter, clear);
}

/* Update outer tag TPID for ES0 entry if VLAN port type has changed */
static vtss_rc jr2_es0_entry_update(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_es0_data_t *es0)
{
#if VTSS_OPT_TRACE
    const jr2_vcap_props_t *vcap = &jr2_vcap_info[JR2_VCAP_ES0];
#endif
    jr2_vcap_data_t        jr2_data, *data = &jr2_data;
    vtss_es0_action_t      *action = &es0->entry->action;
    jr2_es0_tag_t          tag;
    u32                    addr;

    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    data->tg = JR2_VCAP_TG_X1;
    addr = jr2_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u, port_no: %u, flags: 0x%x", vcap->name, idx->row, idx->col, addr, es0->port_no, es0->flags);

    /* Read action */
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));

    /* Update action fields */
    jr2_es0_tag_get(action, 0, &tag);
    if (es0->flags & VTSS_ES0_FLAG_OT_UVID) {
        JR2_ACT_SET(ES0, PUSH_OUTER_TAG, tag.tag_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_TPID) {
        JR2_ACT_SET(ES0, TAG_A_TPID_SEL, tag.tpid_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_PCP) {
        JR2_ACT_SET(ES0, PCP_A_VAL, tag.pcp.val);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_DEI) {
        JR2_ACT_SET(ES0, DEI_A_VAL, tag.dei.val);
    }
    jr2_es0_tag_get(action, 1, &tag);
    if (es0->flags & VTSS_ES0_FLAG_IT_UVID) {
        JR2_ACT_SET(ES0, PUSH_INNER_TAG, tag.tag_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_TPID) {
        JR2_ACT_SET(ES0, TAG_B_TPID_SEL, tag.tpid_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_PCP) {
        JR2_ACT_SET(ES0, PCP_B_VAL, tag.pcp.val);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_DEI) {
        JR2_ACT_SET(ES0, DEI_B_VAL, tag.dei.val);
    }

    /* Update action fields based on egress QoS mapping */
    VTSS_RC(jr2_es0_action_update(vtss_state, data, es0));

    /* Write action */
    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION);
}

static void jr2_debug_es0_tag(const char *name, jr2_vcap_data_t *data,
                              u32 tpid_sel, u32 vid_sel, u32 pcp_sel, u32 dei_sel, u32 vid_val, u32 pcp_val, u32 dei_val)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 x;
    char                buf[16];

    x = jr2_act_get(data, tpid_sel, ES0_AL_TAG_A_TPID_SEL);
    pr("tpid_%s_sel:%u (%s) ", name, x,
       x == ES0_ACT_TPID_SEL_C ? "c" :
       x == ES0_ACT_TPID_SEL_S ? "s" :
       x == ES0_ACT_TPID_SEL_CUSTOM_1 ? "c1" :
       x == ES0_ACT_TPID_SEL_CUSTOM_2 ? "c2" :
       x == ES0_ACT_TPID_SEL_CUSTOM_3 ? "c3" :
       x == ES0_ACT_TPID_SEL_CLASS ? "class" : "?");

    VTSS_SPRINTF(buf, "vid_%s", name);
    x = jr2_act_get(data, vid_sel, ES0_AL_TAG_A_VID_SEL);
    pr("%s_sel:%u (%s) ", buf, x, x ? "vid" : vid_sel == ES0_AO_TAG_C_VID_SEL ? "cl_vid" : "vid+cl_vid");
    jr2_debug_action(data, buf, vid_val, ES0_AL_VID_A_VAL);
    pr("\n");

    VTSS_SPRINTF(buf, "pcp_%s", name);
    x = jr2_act_get(data, pcp_sel, ES0_AL_TAG_A_PCP_SEL);
    pr("%s_sel:%u (%s) ", buf, x,
       x == ES0_ACT_PCP_SEL_CL_PCP ? "cl-pcp" :
       x == ES0_ACT_PCP_SEL_PCP_ES0 ? "es0" :
       x == ES0_ACT_PCP_SEL_POPPED ? "popped" :
       x == ES0_ACT_PCP_SEL_MAP_0 ? "map_0" :
       x == ES0_ACT_PCP_SEL_MAP_1 ? "map_1" :
       x == ES0_ACT_PCP_SEL_MAP_2 ? "map_3" :
       x == ES0_ACT_PCP_SEL_MAP_3 ? "map_3" : "?");
    jr2_debug_action(data, buf, pcp_val, ES0_AL_PCP_A_VAL);

    VTSS_SPRINTF(buf, "dei_%s", name);
    x = jr2_act_get(data, dei_sel, ES0_AL_TAG_A_DEI_SEL);
    pr("%s_sel:%u (%s) ", buf, x,
       x == ES0_ACT_DEI_SEL_CL_DEI ? "cl-dei" :
       x == ES0_ACT_DEI_SEL_DEI_ES0 ? "es0" :
       x == ES0_ACT_DEI_SEL_MAPPED ? "mapped" :
       x == ES0_ACT_DEI_SEL_POPPED ? "popped" :
       x == ES0_ACT_DEI_SEL_MAP_0 ? "map_0" :
       x == ES0_ACT_DEI_SEL_MAP_1 ? "map_1" :
       x == ES0_ACT_DEI_SEL_MAP_2 ? "map_2" :
       x == ES0_ACT_DEI_SEL_MAP_3 ? "map_3" : "?");
    jr2_debug_action(data, buf, dei_val, ES0_AL_DEI_A_VAL);
    pr("\n");
}

static vtss_rc jr2_debug_es0(vtss_state_t *vtss_state, jr2_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 x;
    const               char *txt;

    if (data->is_action) {
        /* Show action fields */
        JR2_DEBUG_ACT(ES0, "push_outer", PUSH_OUTER_TAG);
        x = jr2_act_get(data, ES0_AO_PUSH_OUTER_TAG, ES0_AL_PUSH_OUTER_TAG);
        pr("(%s) ",
           x == ES0_ACT_PUSH_OT_PORT_ENA ? "port" :
           x == ES0_ACT_PUSH_OT_ES0 ? "tag_a" :
           x == ES0_ACT_PUSH_OT_PORT ? "port_force" : "none");
        JR2_DEBUG_ACT(ES0, "push_inner", PUSH_INNER_TAG);
        pr("(%s) ", jr2_act_get(data, ES0_AO_PUSH_INNER_TAG, ES0_AL_PUSH_INNER_TAG) ? "tag_b" : "none");
        JR2_DEBUG_ACT(ES0, "push_tag_c", PUSH_TAG_C);
        JR2_DEBUG_ACT(ES0, "untag_vid_ena", UNTAG_VID_ENA);
        pr("\n");
        jr2_debug_es0_tag("a", data, ES0_AO_TAG_A_TPID_SEL, ES0_AO_TAG_A_VID_SEL, ES0_AO_TAG_A_PCP_SEL, ES0_AO_TAG_A_DEI_SEL,
                          ES0_AO_VID_A_VAL, ES0_AO_PCP_A_VAL, ES0_AO_DEI_A_VAL);
        jr2_debug_es0_tag("b", data, ES0_AO_TAG_B_TPID_SEL, ES0_AO_TAG_B_VID_SEL, ES0_AO_TAG_B_PCP_SEL, ES0_AO_TAG_B_DEI_SEL,
                          ES0_AO_VID_B_VAL, ES0_AO_PCP_B_VAL, ES0_AO_DEI_B_VAL);
        jr2_debug_es0_tag("c", data, ES0_AO_TAG_C_TPID_SEL, ES0_AO_TAG_C_VID_SEL, ES0_AO_TAG_C_PCP_SEL, ES0_AO_TAG_C_DEI_SEL,
                          ES0_AO_VID_C_VAL, ES0_AO_PCP_C_VAL, ES0_AO_DEI_C_VAL);
        JR2_DEBUG_ACT(ES0, "pop_val", POP_VAL);
        JR2_DEBUG_ACT(ES0, "dscp_sel", DSCP_SEL);
        JR2_DEBUG_ACT(ES0, "dscp_val", DSCP_VAL);
        JR2_DEBUG_ACT(ES0, "label_sel", LABEL_SEL);
        JR2_DEBUG_ACT(ES0, "mpls_label", MPLS_LABEL);
        JR2_DEBUG_ACT(ES0, "tc_sel", TC_SEL);
        JR2_DEBUG_ACT(ES0, "tc_val", TC_VAL);
        pr("\n");
        JR2_DEBUG_ACT(ES0, "sbit_sel", SBIT_SEL);
        JR2_DEBUG_ACT(ES0, "sbit_val", SBIT_VAL);
        JR2_DEBUG_ACT(ES0, "ttl_sel", TTL_SEL);
        JR2_DEBUG_ACT(ES0, "ttl_val", TTL_VAL);
        JR2_DEBUG_ACT(ES0, "cw_dis", CW_DIS);
        JR2_DEBUG_ACT(ES0, "encap_id", ENCAP_ID);
        pr("\n");
        JR2_DEBUG_ACT(ES0, "pop_cnt", POP_CNT);
        JR2_DEBUG_ACT(ES0, "esdx_base", ESDX_BASE);
        JR2_DEBUG_ACT_BITS(ES0, "esdx_cosid_offs", ESDX_COSID_OFFS);
        pr("\n");
        JR2_DEBUG_ACT(ES0, "map_0_idx", MAP_0_IDX);
        JR2_DEBUG_ACT(ES0, "map_1_idx", MAP_1_IDX);
        JR2_DEBUG_ACT(ES0, "map_2_idx", MAP_2_IDX);
        JR2_DEBUG_ACT(ES0, "map_3_idx", MAP_3_IDX);
        pr("\n");
        JR2_DEBUG_ACT(ES0, "map_0_key", MAP_0_KEY);
        JR2_DEBUG_ACT(ES0, "map_1_key", MAP_1_KEY);
        JR2_DEBUG_ACT(ES0, "map_2_key", MAP_2_KEY);
        JR2_DEBUG_ACT(ES0, "map_3_key", MAP_3_KEY);
        pr("\n");
        JR2_DEBUG_ACT_ENA(ES0, "oam_mep", OAM_MEP);
        JR2_DEBUG_ACT(ES0, "oam_lm_color_sel", OAM_LM_COLOR_SEL);
        JR2_DEBUG_ACT(ES0, "oam_indep_mel_ena", INDEP_MEL_ENA);
        JR2_DEBUG_ACT(ES0, "mip_idx", MIP_IDX);
        pr("\n");
        JR2_DEBUG_ACT(ES0, "fwd_sel", FWD_SEL);
        JR2_DEBUG_ACT(ES0, "cpu_queue", CPU_QUEUE);
        JR2_DEBUG_ACT(ES0, "pl_pt", PL_PT);
#if !defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_DEBUG_ACT(ES0, "pl_act", PL_ACT);
        JR2_DEBUG_ACT(ES0, "mac_sw", SWAP_MAC_ENA);
#endif
        JR2_DEBUG_ACT(ES0, "loop_ena", LOOP_ENA);
        pr("\ncnt: %u", data->counter);
    } else {
        /* Show key fields */
        JR2_DEBUG_BITS(ES0, "type", TYPE);
        txt = (jr2_entry_bs_get(data, ES0_KO_TYPE, ES0_KL_TYPE)  == ES0_TYPE_VID ? "vid" : "isdx");
        pr("(%s) ",txt);
        JR2_DEBUG_BITS(ES0, "egr_port", EGR_PORT);
        JR2_DEBUG_BITS(ES0, "prot_act", PROT_ACT);
        JR2_DEBUG_BITS(ES0, "vsi", VSI);
        pr("\n");
        JR2_DEBUG_BITS(ES0, "cosid", COSID);
        JR2_DEBUG_BITS(ES0, "color", COLOR);
        JR2_DEBUG_BITS(ES0, "service_frm", SERVICE_FRM);
        JR2_DEBUG_BITS(ES0, txt, VID_ISDX);
        pr("\n");
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_debug_es0(vtss_state_t *vtss_state,
                           const vtss_debug_printf_t pr,
                           const vtss_debug_info_t   *const info)
{
    vtss_jr2_debug_reg_header(pr, "REW");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_COMMON_ES0_CTRL, "ES0_CTRL");
    pr("\n");

    return jr2_debug_vcap(vtss_state, VTSS_VCAP_TYPE_ES0, pr, info, jr2_debug_es0);
}

/* - ACL ----------------------------------------------------------- */

static vtss_rc jr2_acl_policer_set(vtss_state_t *vtss_state, const vtss_acl_policer_no_t policer_no)
{
    u32                     rate, i = (policer_no - VTSS_ACL_POLICER_NO_START);
    vtss_acl_policer_conf_t *conf = &vtss_state->vcap.acl_policer_conf[i];

    if (conf->bit_rate_enable) {
        /* Bit rate in 25040 bps, API rate in 1000 bps, 1000/25040 = 25/626, round up */
        rate = (((conf->bit_rate + 1) * 25)/626);
    } else {
        /* Frame rate in 10 fps */
        rate = (conf->rate / 10);
    }
    rate = MIN(VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE, rate);
    JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG(i), VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE(rate));

    /* Minimum  threshold */
    JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG(i), VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG_ACL_THRES(1));

    /* Frame or line rate policing */
    JR2_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL(i),
           VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_GAP_VALUE(20) |
           VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_ACL_TRAFFIC_TYPE_MASK(3) |
           VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_FRAME_RATE_ENA(conf->bit_rate_enable ? 0 : 1));
    return VTSS_RC_OK;
}

static vtss_rc jr2_acl_sip_set(vtss_state_t *vtss_state, const vtss_acl_sip_idx_t idx)
{
    vtss_ip_addr_t *sip = &vtss_state->vcap.acl_sip_table[idx].sip;
    u32            i, j, addr;

    if (sip->type == VTSS_IP_TYPE_IPV4) {
        JR2_WR(VTSS_ANA_ACL_VCAP_S2_SWAP_SIP(idx), sip->addr.ipv4);
    } else {
        for (i = 0; i < 4; i++) {
            for (addr = 0, j = 0; j < 4; j++) {
                addr += (sip->addr.ipv6.addr[15 - 4*i - j] << (j*8));
            }
            JR2_WR(VTSS_ANA_ACL_VCAP_S2_SWAP_SIP(idx + i), addr);
        }
    }
    return VTSS_RC_OK;
}

static u32 jr2_acl_port_cnt_id(u32 port)
{
    /* By default, many rules map to counter 0, so we start with counter 1 */
    return (port + 1);
}

static u32 jr2_ace_cnt_id_alloc(vtss_state_t *vtss_state)
{
    u32 cnt_id;

    for (cnt_id = JR2_ACE_CNT_ID_BASE; cnt_id < VTSS_ACL_CNT_SIZE; cnt_id++) {
        if (VTSS_BF_GET(vtss_state->vcap.acl_cnt_alloc, cnt_id) == 0) {
            VTSS_BF_SET(vtss_state->vcap.acl_cnt_alloc, cnt_id, 1);
            return cnt_id;
        }
    }
    return 0;
}

static vtss_rc jr2_ace_cnt_id_free(vtss_state_t *vtss_state, u32 cnt_id)
{
    if (VTSS_BF_GET(vtss_state->vcap.acl_cnt_alloc, cnt_id) == 0) {
        VTSS_E("ACE counter %u already free", cnt_id);
        return VTSS_RC_ERROR;
    }
    VTSS_BF_SET(vtss_state->vcap.acl_cnt_alloc, cnt_id, 0);
    return VTSS_RC_OK;
}

static vtss_rc jr2_acl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_acl_port_conf_t *conf = &vtss_state->vcap.acl_port_conf[port_no];
    jr2_vcap_data_t      vcap_data, *data = &vcap_data;
    u32                  addr, lookup = 0x01, port = VTSS_CHIP_PORT(port_no);
    u32                  ipv4, ipv6, value, mask, enable = (conf->policy_no == VTSS_ACL_POLICY_NO_NONE ? 0 : 1);

    /* PAG setup in CLM_A */
    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = VTSS_VCAP_TYPE_CLM_A;
    addr = jr2_vcap_action_addr(data->vcap_type, port, 0);
    VTSS_I("addr: %u", addr);
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, JR2_VCAP_TG_X4, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));
    data->type = JR2_VCAP_TG_X4;
    mask = VTSS_BITMASK(CLM_AL_X4_PAG_MASK);
    JR2_ACT_SET(CLM, X4_PAG_MASK, mask);
    JR2_ACT_SET(CLM, X4_PAG, 0x80 | (enable ? conf->policy_no : 0)); /* PAG(7) indicates IS2 VID filtering */
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->type, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION));

    // IPv4 and IPv6 keys can not be controlled completely independently, but 8 of 9 combinations will be correct.
    // The combination not working is (ipv4, ipv6) = (ETYPE, DEF), which will be (ipv4, ipv6) = (ETYPE, ETYPE).
    ipv4 = (conf->key.ipv4 == VTSS_ACL_KEY_EXT ? 2 : conf->key.ipv4 == VTSS_ACL_KEY_DEFAULT ? 1 : 0);
    ipv6 = (conf->key.ipv6 == VTSS_ACL_KEY_EXT ? 1 : 0);
    JR2_WR(VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL(port, lookup - 1),
           VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP4_MC_KEY_SEL(ipv4) |
           VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP4_UC_KEY_SEL(ipv4) |
           VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP6_MC_KEY_SEL(ipv6) |
           VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP6_UC_KEY_SEL(ipv6) |
           VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_ARP_KEY_SEL(conf->key.arp == VTSS_ACL_KEY_ETYPE ? 0 : 1));
    ipv4 = (conf->key.ipv4 == VTSS_ACL_KEY_ETYPE || conf->key.ipv6 == VTSS_ACL_KEY_ETYPE ? 0 : 1);
    value = (VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_TCPUDP_OTHER_ENA(lookup) |
             VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_TCPUDP_ENA(lookup) |
             VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_OTHER_ENA(lookup));
    mask = VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_ENA(lookup);
    JR2_WRM(VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG(port), (ipv4 ? value : 0) | (enable ? mask : 0), value | mask);

    /* Setup action */
    VTSS_MEMSET(data, 0, sizeof(*data));
    VTSS_RC(jr2_is2_action_set(vtss_state, data, &conf->action, jr2_acl_port_cnt_id(port), 0));
    addr = jr2_vcap_action_addr(VTSS_VCAP_TYPE_IS2, port, 0);
    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->type, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION);
}

static vtss_rc jr2_acl_port_counter_get(vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_acl_port_counter_t *const counter)
{
    u32 cnt_id = jr2_acl_port_cnt_id(VTSS_CHIP_PORT(port_no));

    return jr2_is2_cnt_get(vtss_state, cnt_id, counter);
}

static vtss_rc jr2_acl_port_counter_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 cnt_id = jr2_acl_port_cnt_id(VTSS_CHIP_PORT(port_no));

    return jr2_is2_cnt_set(vtss_state, cnt_id, 0);
}

static vtss_rc jr2_ace_add(vtss_state_t *vtss_state,
                           const vtss_ace_id_t ace_id, const vtss_ace_t *const ace)
{
    vtss_vcap_obj_t             *obj = &vtss_state->vcap.is2.obj;
    vtss_vcap_obj_t             *obj_lpm = &vtss_state->vcap.lpm.obj;
    vtss_vcap_user_t            user = VTSS_IS2_USER_ACL;
    vtss_vcap_user_t            user_lpm = VTSS_LPM_USER_ACL;
    vtss_vcap_data_t            data;
    vtss_is2_data_t             *is2 = &data.u.is2;
    vtss_is2_entry_t            entry;
    vtss_lpm_entry_t            entry_lpm;
    vtss_res_t                  res;
    const vtss_ace_frame_ipv4_t *ipv4 = &ace->frame.ipv4;
    const vtss_ace_frame_ipv6_t *ipv6 = &ace->frame.ipv6;
    const vtss_ace_udp_tcp_t    *sport = NULL, *dport = NULL;
    vtss_vcap_range_chk_table_t range_new = vtss_state->vcap.range;
    u32                         i, cnt_id = 0;
    vtss_vcap_key_size_t        key_size, key_lpm;
    BOOL                        sip_smac_new = 0, sip_smac_old = 0;
    vtss_port_no_t              port_no;

    /* Check the simple things */
    VTSS_RC(vtss_cmn_ace_add(vtss_state, ace_id, ace));

    key_size = VTSS_VCAP_KEY_SIZE_HALF;
    key_lpm = VTSS_VCAP_KEY_SIZE_SIXTEENTH;
    if (ace->type_ext && (ace->type == VTSS_ACE_TYPE_IPV4 || ace->type == VTSS_ACE_TYPE_IPV6)) {
        /* Encode as IPv4/IPv6 full rule */
        key_size = VTSS_VCAP_KEY_SIZE_FULL;
    }

    /* Check that entry can be added */
    vtss_cmn_res_init(&res);
    res.is2.add_key[key_size] = 1;
    if (vtss_vcap_lookup(vtss_state, obj, user, ace->id, &data, NULL) == VTSS_RC_OK) {
        res.is2.del_key[data.key_size] = 1;

        /* Free any old range checkers */
        VTSS_RC(vtss_vcap_range_free(&range_new, is2->srange));
        VTSS_RC(vtss_vcap_range_free(&range_new, is2->drange));

        cnt_id = is2->cnt_id;

        /* Check if SIP/SMAC entry already exists */
        if (vtss_vcap_lookup(vtss_state, obj_lpm, user_lpm, ace->id, &data, NULL) == VTSS_RC_OK) {
            sip_smac_old = 1;
            res.lpm.del_key[data.key_size] = 1;
        }
    } else if ((cnt_id = jr2_ace_cnt_id_alloc(vtss_state)) == 0) {
        VTSS_E("no ACE counter free");
        return VTSS_RC_ERROR;
    }
    if (ace->type == VTSS_ACE_TYPE_IPV4) {
        if (ipv4->sip_smac.enable) {
            /* SIP/SMAC entry needed */
            sip_smac_new = 1;
            res.lpm.add_key[key_lpm] = 1;
        }
        if (vtss_vcap_udp_tcp_rule(&ipv4->proto)) {
            sport = &ipv4->sport;
            dport = &ipv4->dport;
        }
    } else if (ace->type == VTSS_ACE_TYPE_IPV6 && vtss_vcap_udp_tcp_rule(&ipv6->proto)) {
        sport = &ipv6->sport;
        dport = &ipv6->dport;
    }
    VTSS_RC(vtss_cmn_res_check(vtss_state, &res));

    vtss_vcap_is2_init(&data, &entry);
    is2->cnt_id = cnt_id;
    entry.ace = *ace;
    data.key_size = key_size;
    if (ace->action.port_action == VTSS_ACL_PORT_ACTION_REDIR) {
        is2->action.redir = 1;
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (ace->action.port_list[port_no]) {
                VTSS_PORT_BF_SET(is2->action.member, port_no, 1);
            }
        }
    }
    if (sip_smac_new) {
        entry.host_match = 1;
        entry.ace.frame.ipv4.sip.value = ipv4->sip_smac.sip;
        entry.ace.frame.ipv4.sip.mask = 0xffffffff;
    }

    /* Allocate and commit new range checkers */
    if (sport && dport) {
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->srange, sport, 1));
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->drange, dport, 0));
    }
    VTSS_RC(vtss_vcap_range_commit(vtss_state, &range_new));

    /* Add main entry */
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, ace->id, ace_id, &data, 0));

    /* Add/delete SIP/SMAC entry */
    if (sip_smac_new) {
        VTSS_MEMSET(&data, 0, sizeof(data));
        VTSS_MEMSET(&entry_lpm, 0, sizeof(entry_lpm));
        data.u.lpm.entry = &entry_lpm;
        data.key_size = key_lpm;
        entry_lpm.key.type = VTSS_LPM_KEY_SGL_IP4;
        entry_lpm.key.data.sgl_ip4.xip = entry.ace.frame.ipv4.sip;
        entry_lpm.action.type = LPM_TYPE_ARP_ENTRY;
        entry_lpm.action.data.arp_entry.secur_match_mac_ena = 1;
        for (i = 0; i < 6; i++) {
            entry_lpm.action.data.arp_entry.mac.addr[i] = ipv4->sip_smac.smac.addr[i];
        }
        VTSS_RC(vtss_vcap_add(vtss_state, obj_lpm, user_lpm, ace->id, VTSS_VCAP_ID_LAST, &data, 0));
    } else if (sip_smac_old) {
        VTSS_RC(vtss_vcap_del(vtss_state, obj_lpm, user_lpm, ace->id));
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_ace_del(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    vtss_vcap_data_t data;

    /* Free counter */
    if (vtss_vcap_lookup(vtss_state, &vtss_state->vcap.is2.obj, VTSS_IS2_USER_ACL, ace_id, &data, NULL) == VTSS_RC_OK) {
        VTSS_RC(jr2_ace_cnt_id_free(vtss_state, data.u.is2.cnt_id));
    }

    /* Delete main entry */
    VTSS_RC(vtss_cmn_ace_del(vtss_state, ace_id));

    /* Delete SMAC/SIP entry */
    return vtss_vcap_del(vtss_state, &vtss_state->vcap.lpm.obj, VTSS_LPM_USER_ACL, ace_id);
}

static vtss_rc jr2_vcap_range_commit(vtss_state_t *vtss_state)
{
    u32                   i, type;
    vtss_vcap_range_chk_t *entry;

    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        entry = &vtss_state->vcap.range.entry[i];
        if (entry->count == 0)
            continue;
        switch (entry->type) {
        case VTSS_VCAP_RANGE_TYPE_DPORT:
            type = 1;
            break;
        case VTSS_VCAP_RANGE_TYPE_SPORT:
            type = 2;
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
        /* For now, the CLM and IS2 range checkers are treated as a single pool like for other platforms */
        JR2_WR(VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_CTRL(i),
               VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_RNG_CTRL_RNG_TYPE_SEL(type));
        JR2_WR(VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG(i),
               VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG_RNG_MIN_VALUE(entry->min) |
               VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG_RNG_MAX_VALUE(entry->max));
        JR2_WR(VTSS_ANA_CL_COMMON_ADV_RNG_CTRL(i),
               VTSS_F_ANA_CL_COMMON_ADV_RNG_CTRL_RNG_TYPE_SEL(type));
        JR2_WR(VTSS_ANA_CL_COMMON_ADV_RNG_VALUE_CFG(i),
               VTSS_F_ANA_CL_COMMON_ADV_RNG_VALUE_CFG_RNG_MIN_VALUE(entry->min) |
               VTSS_F_ANA_CL_COMMON_ADV_RNG_VALUE_CFG_RNG_MAX_VALUE(entry->max));
    }
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc jr2_debug_acl(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    vtss_port_no_t port_no;
    u32            port, i;
    char           buf[32];

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0)
            continue;
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_jr2_debug_reg_header(pr, buf);
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG(port), port, "VCAP_S2_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL(port, 0), port, "S2_KEY_SEL_0");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL(port, 1), port, "S2_KEY_SEL_1");
        pr("\n");
    }

    for (i = 0; i < VTSS_ACL_POLICERS; i++) {
        VTSS_SPRINTF(buf, "Policer %u", i);
        vtss_jr2_debug_reg_header(pr, buf);
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL(i), i, "ACL_CTRL");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG(i), i, "ACL_RATE_CFG");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG(i), i, "ACL_THRES_CFG");
        pr("\n");
    }

    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        VTSS_SPRINTF(buf, "Range %u", i);
        vtss_jr2_debug_reg_header(pr, buf);
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_CTRL(i), i, "S2_RNG_CTRL");
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG(i), i, "S2_RNG_VAL");
        pr("\n");
    }

    vtss_jr2_debug_reg_header(pr, "SIP Table");
    for (i = 0; i < VTSS_ACL_SIP_CNT; i++) {
        vtss_jr2_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_SWAP_SIP(i), i, "SWAP_SIP");
    }
    pr("\n");

    VTSS_RC(jr2_debug_vcap(vtss_state, VTSS_VCAP_TYPE_CLM_A, pr, info, jr2_debug_clm)); /* Default PAG in CLM_A */
    VTSS_RC(vtss_jr2_debug_lpm(vtss_state, pr, info)); /* SIP/SMAC check in LPM */
    VTSS_RC(jr2_debug_vcap(vtss_state, VTSS_VCAP_TYPE_IS2, pr, info, jr2_debug_is2));
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_vcap_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_ACL, jr2_debug_acl, vtss_state, pr, info);
}

/* - VCAP/QoS ------------------------------------------------------ */

vtss_rc vtss_jr2_vcap_port_l2_update(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    jr2_vcap_data_t          vcap_data, *data = &vcap_data;
    u32                      addr, port = VTSS_CHIP_PORT(port_no), dscp_sel = ES0_ACT_DSCP_SEL_PORT;
    jr2_es0_map_t            map;
    vtss_qos_egress_map_id_t map_id = vtss_state->qos.port_conf[port_no].egress_map;
    jr2_es0_tag_t            tag;
    vtss_vlan_port_conf_t    *conf = &vtss_state->l2.vlan_port_conf[port_no];
    BOOL                     port_tag = FALSE;

    /* Egress QoS map setup using ES0 default action */
    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    addr = jr2_vcap_action_addr(data->vcap_type, port, 0);
    VTSS_I("port_no: %u, port: %u, addr: %u, map: %u", port_no, port, addr, map_id);
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, JR2_VCAP_TG_X1, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));
    data->type = JR2_VCAP_TG_X1;

    /* Setup TAG_C */
    VTSS_MEMSET(&tag, 0, sizeof(tag));
    if (jr2_es0_map_update(vtss_state, map_id, &map)) {
        VTSS_I("map_act: %u", map.act);
        /* Egress QoS map used, push TAG_C */
        if (conf->untagged_vid != VTSS_VID_ALL) {
            tag.tag_sel = 3;
            tag.vid.val = conf->untagged_vid;
            tag.tpid_sel = (conf->port_type == VTSS_VLAN_PORT_TYPE_S ? ES0_ACT_TPID_SEL_S :
                            conf->port_type == VTSS_VLAN_PORT_TYPE_C ? ES0_ACT_TPID_SEL_C : ES0_ACT_TPID_SEL_CUSTOM_1);
            if (map.act & VTSS_QOS_EGRESS_MAP_ACTION_PCP) {
                tag.pcp.sel = (map.res ? ES0_ACT_PCP_SEL_MAP_2 : ES0_ACT_PCP_SEL_MAP_0);
            }
            if (map.act & VTSS_QOS_EGRESS_MAP_ACTION_DEI) {
                tag.dei.sel = (map.res ? ES0_ACT_DEI_SEL_MAP_2 : ES0_ACT_DEI_SEL_MAP_0);
            }
        }
        if (map.act & VTSS_QOS_EGRESS_MAP_ACTION_DSCP) {
            dscp_sel = (map.res ? ES0_ACT_DSCP_SEL_MAP_2 : ES0_ACT_DSCP_SEL_MAP_0);
        }
    } else {
        /* Egress QoS map not used, use port tag */
        port_tag = TRUE;
    }
    JR2_ACT_SET(ES0, UNTAG_VID_ENA, conf->untagged_vid == VTSS_VID_NULL ? 0 : 1);
    JR2_ACT_SET(ES0, PUSH_TAG_C, tag.tag_sel);
    JR2_ACT_SET(ES0, TAG_C_TPID_SEL, tag.tpid_sel);
    JR2_ACT_SET(ES0, TAG_C_VID_SEL, tag.vid.sel);
    JR2_ACT_SET(ES0, VID_C_VAL, tag.vid.val);
    JR2_ACT_SET(ES0, TAG_C_PCP_SEL, tag.pcp.sel);
    JR2_ACT_SET(ES0, PCP_C_VAL, tag.pcp.val);
    JR2_ACT_SET(ES0, TAG_C_DEI_SEL, tag.dei.sel);
    JR2_ACT_SET(ES0, DEI_C_VAL, tag.dei.val);

    /* Setup TAG_A */
    VTSS_MEMSET(&tag, 0, sizeof(tag));
    tag.tag_sel = (port_tag ? ES0_ACT_PUSH_OT_PORT_ENA : ES0_ACT_PUSH_OT_NONE);
    jr2_es0_outer_tag_update(vtss_state, data, &tag);

    JR2_ACT_SET(ES0, MAP_0_IDX, map.idx);
    JR2_ACT_SET(ES0, MAP_0_KEY, map.key);
    JR2_ACT_SET(ES0, MAP_2_IDX, map.idx);
    JR2_ACT_SET(ES0, MAP_2_KEY, map.key);
    JR2_ACT_SET(ES0, DSCP_SEL,  dscp_sel);
    JR2_ACT_SET(ES0, ESDX_BASE, 1);
    JR2_ACT_SET(ES0, INDEP_MEL_ENA, 1); // By default, get Port VOE to see frames as data frames
    return jr2_vcap_entry_cmd(vtss_state, data, addr, data->type, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION);
}

vtss_rc vtss_jr2_vcap_port_qos_update(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t *conf = &vtss_state->qos.port_conf[port_no];
    jr2_vcap_data_t      vcap_data, *data = &vcap_data;
    u32                  addr, port = VTSS_CHIP_PORT(port_no);

    /* Ingress map setup in CLM_A0 */
    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = VTSS_VCAP_TYPE_CLM_A;
    addr = jr2_vcap_action_addr(data->vcap_type, port, 0);
    VTSS_I("port_no: %u, port: %u, addr: %u", port_no, port, addr);
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, JR2_VCAP_TG_X4, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));
    data->type = JR2_VCAP_TG_X4;
    jr2_clm_qos_action_update(vtss_state, data, conf->ingress_map, 0);
    JR2_ACT_ENA_SET(CLM, X4_COSID, 1, conf->cosid);
    VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->type, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION));

    /* Egress map setup in ES0 */
    return vtss_jr2_vcap_port_l2_update(vtss_state, port_no);
}

static vtss_rc jr2_es0_esdx_update(vtss_state_t *vtss_state, u16 esdx_old, u16 esdx_new)
{
#if VTSS_OPT_TRACE
    const jr2_vcap_props_t *vcap = &jr2_vcap_info[JR2_VCAP_ES0];
#endif
    jr2_vcap_data_t        jr2_data, *data = &jr2_data;
    u32                    addr;
    vtss_vcap_obj_t        *obj = &vtss_state->vcap.es0.obj;
    vtss_es0_data_t        *es0;
    vtss_vcap_idx_t        idx;
    vtss_vcap_entry_t      *cur;

    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    data->tg = JR2_VCAP_TG_X1;
    VTSS_MEMSET(&idx, 0, sizeof(idx));
    for (cur = obj->used; cur != NULL; cur = cur->next, idx.row++) {
        es0 = &cur->data.u.es0;
        if (es0->esdx != esdx_old) {
            continue;
        }
        es0->esdx = esdx_new;

        addr = jr2_vcap_entry_addr(vtss_state, data->vcap_type, &idx);
        VTSS_I("%s, row: %u, col: %u, addr: %u, esdx: %u",
               vcap->name, idx.row, idx.col, addr, esdx_new);

        /* Read action */
        VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));

        /* Update action fields */
        JR2_ACT_SET(ES0, ESDX_BASE, es0->esdx ? es0->esdx : 1); // Avoid using esdx_base 0 as default

        /* Write action */
        VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION));
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_es0_eflow_update(vtss_state_t *vtss_state, const vtss_eflow_id_t flow_id)
{
#if VTSS_OPT_TRACE
    const jr2_vcap_props_t *vcap = &jr2_vcap_info[JR2_VCAP_ES0];
#endif
    jr2_vcap_data_t        jr2_data, *data = &jr2_data;
    u32                    addr;
    vtss_vcap_obj_t        *obj = &vtss_state->vcap.es0.obj;
    vtss_es0_data_t        *es0;
    vtss_vcap_idx_t        idx;
    vtss_vcap_entry_t      *cur;
    vtss_eflow_entry_t     *eflow = vtss_eflow_lookup(vtss_state, flow_id);
    vtss_xstat_entry_t     *stat;
    u32                    cosid, mep_ena = 0, mep_idx = 0, mip_idx = 0, esdx = 0, cosid_offset = 0;

    if (eflow != NULL) {
        if (eflow->conf.voe_idx < VTSS_PORT_VOE_BASE_IDX) {      /* Do not point to a Port VOE */
            mep_ena = 1;
            mep_idx = eflow->conf.voe_idx;
        }
        if (eflow->conf.voi_idx != VTSS_VOI_IDX_NONE) {
            mip_idx = vtss_j2_voi_idx_to_mip_idx(eflow->conf.voi_idx);
        }
        if (eflow->conf.cnt_enable && (stat = vtss_estat_lookup(vtss_state, eflow->conf.cnt_id)) != NULL) {
            esdx = stat->idx;
            for (cosid = 0; cosid < 8; cosid++) {
                cosid_offset |= ((cosid < stat->cnt ? cosid : (stat->cnt - 1))<< (cosid * 3));
            }
        }
    }

    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    data->tg = JR2_VCAP_TG_X1;
    VTSS_MEMSET(&idx, 0, sizeof(idx));
    for (cur = obj->used; cur != NULL; cur = cur->next, idx.row++) {
        es0 = &cur->data.u.es0;
        if (es0->flow_id == flow_id) {
            es0->esdx = esdx;
            addr = jr2_vcap_entry_addr(vtss_state, data->vcap_type, &idx);
            VTSS_I("%s, row: %u, col: %u, addr: %u, flow_id: %u",
                   vcap->name, idx.row, idx.col, addr, flow_id);

            /* Read action */
            VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_READ, JR2_VCAP_SEL_ACTION));

            /* Update action fields */
            JR2_ACT_ENA_SET(ES0, OAM_MEP, mep_ena, mep_idx);
            JR2_ACT_SET(ES0, MIP_IDX, mip_idx);
            JR2_ACT_SET(ES0, ESDX_BASE, esdx ? esdx : 1); // Avoid using esdx_base 0 as default
            JR2_ACT_SET(ES0, ESDX_COSID_OFFS, cosid_offset);

            /* Write action */
            VTSS_RC(jr2_vcap_entry_cmd(vtss_state, data, addr, data->tg, JR2_VCAP_CMD_WRITE, JR2_VCAP_SEL_ACTION));
        }
    }
    return VTSS_RC_OK;
}

/* - MPLS ---------------------------------------------------------- */

#if defined(VTSS_FEATURE_MPLS)

// JR2 rev C only; no attempt to adjust for rev B.
static vtss_rc jr2_debug_clm_raw(vtss_state_t *vtss_state, jr2_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 ofs;
    u32                 len;
    char                name[20];

    /* Check VCAP type */
    switch (data->vcap_type) {
    case VTSS_VCAP_TYPE_CLM_A:
    case VTSS_VCAP_TYPE_CLM_B:
    case VTSS_VCAP_TYPE_CLM_C:
        break;
    default:
        VTSS_E("not TYPE_CLM");
        return VTSS_RC_ERROR;
    }

    // All lengths are max lengths

    if (data->is_action) {
        /* Show action fields */
        switch (data->type) {
        case JR2_VCAP_TG_NONE:
            len = 0;
            break;
        case JR2_VCAP_TG_X1:
            len = 72;
            break;
        case JR2_VCAP_TG_X2:
            len = 127;
            break;
        case JR2_VCAP_TG_X4:
            len = 250;
            break;
        default:
            VTSS_E("not X1/X2/X4");
            return VTSS_RC_ERROR;
        }
        for (ofs = len; ofs > 0; ofs--) {
            pr("%d", jr2_act_get(data, ofs - 1, 1));        // One bit at a time
        }

        pr("\ncnt: %u", data->counter);
        return VTSS_RC_OK;
    }

    /* Show key fields */
    switch (data->tg) {
    case JR2_VCAP_TG_X1:
        len = 35;
        break;
    case JR2_VCAP_TG_X2:
        len = 69;
        break;
    case JR2_VCAP_TG_X4:
        len = 137;
        break;
    case JR2_VCAP_TG_X8:
        len = 272;
        break;
    case JR2_VCAP_TG_X16:
        len = 536;
        break;
    default:
        VTSS_E("not X1/X2/X4/X8/X16");
        return VTSS_RC_ERROR;
    }
    for (ofs = 0; ofs < len; ofs += 32) {
        VTSS_SPRINTF(name, "%3u", ofs);
        jr2_debug_bits(data, name, ofs, (ofs + 32 > len ? len - ofs : 32));
        pr("\n");
    }
    return VTSS_RC_OK;
}


vtss_rc vtss_jr2_debug_vcap_mpls(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    u32 action = 0xffffffff & ~(0x0004 | 0x0020);  // Turn off CLM-C, raw by default
    vtss_rc (*dbg)(vtss_state_t *vtss_state, jr2_vcap_data_t *data);

    if (info->has_action) {
        if (info->action == 0) {
            pr("Actions: 0=this help. OR-mask: 0x0001=CLM-A; 0x0002=CLM-B; 0x0004=CLM-C; 0x0008=ES0; 0x0010=terse; 0x0020=raw (not for ES0); 0x0040=show hit entries only\n");
            pr("Raw CLM action fields are shown with rightmost bit 0. Max action length per type (X1, etc) is shown.\n");
            return VTSS_RC_OK;
        }
        action = info->action;
    }

    dbg = (action & 0x0020) ? jr2_debug_clm_raw : jr2_debug_clm;

    if (action & 0x0001) { (void) jr2_debug_vcap(vtss_state, VTSS_VCAP_TYPE_CLM_A, pr, info, dbg); }
    if (action & 0x0002) { (void) jr2_debug_vcap(vtss_state, VTSS_VCAP_TYPE_CLM_B, pr, info, dbg); }
    if (action & 0x0004) { (void) jr2_debug_vcap(vtss_state, VTSS_VCAP_TYPE_CLM_C, pr, info, dbg); }
    if (action & 0x0008) { (void) jr2_debug_vcap(vtss_state, VTSS_VCAP_TYPE_ES0,   pr, info, jr2_debug_es0); }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_MPLS */

vtss_rc vtss_jr2_vcap_port_key_set(vtss_state_t *vtss_state, vtss_port_no_t port_no,
                                   u32 lookup, vtss_vcap_key_type_t key_type, BOOL dmac_dip, BOOL tri_vid_idx)
{
    u32 etype_sel, ip_sel, port = VTSS_CHIP_PORT(port_no);

    ip_sel = (key_type == VTSS_VCAP_KEY_TYPE_IP_ADDR ? 10 : 0);   // NORMAL_5TUPLE_IP4 or follow ETYPE
    etype_sel = (key_type == VTSS_VCAP_KEY_TYPE_DOUBLE_TAG ? 5 :  // TRI_VID_IDX
                 key_type == VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR ? 9 : // NORMAL_7TUPLE
                 dmac_dip ? 8 : 7);                               // NORMAL_DST or NORMAL_SRC
    JR2_WRM(VTSS_ANA_CL_PORT_ADV_CL_CFG(port, lookup),
            VTSS_F_ANA_CL_PORT_ADV_CL_CFG_IP4_CLM_KEY_SEL(ip_sel) |
            VTSS_F_ANA_CL_PORT_ADV_CL_CFG_IP6_CLM_KEY_SEL(ip_sel) |
            VTSS_F_ANA_CL_PORT_ADV_CL_CFG_ETYPE_CLM_KEY_SEL(etype_sel),
            VTSS_M_ANA_CL_PORT_ADV_CL_CFG_IP4_CLM_KEY_SEL |
            VTSS_M_ANA_CL_PORT_ADV_CL_CFG_IP6_CLM_KEY_SEL |
            VTSS_M_ANA_CL_PORT_ADV_CL_CFG_ETYPE_CLM_KEY_SEL);
    JR2_WR(VTSS_ANA_CL_COMMON_CLM_KEY_CFG(lookup),
           VTSS_F_ANA_CL_COMMON_CLM_KEY_CFG_CLM_TRI_VID_SEL(tri_vid_idx));

    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc jr2_vcap_init(vtss_state_t *vtss_state)
{
    VTSS_RC(jr2_vcap_initialize(vtss_state, JR2_VCAP_SUPER));
    VTSS_RC(jr2_vcap_initialize(vtss_state, JR2_VCAP_ES0));

    //JR2_WRM(VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL, 0, VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_SI_OWNER);
    return VTSS_RC_OK;
}

static vtss_rc jr2_vcap_port_map(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    u32            port, i, key_sel, mask, lookup = 0x2;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        for (i = 0; i < 6; i++) {
            if (i == 2) {
                /* NORMAL_SRC for CLM-B[0] (VCL/VTR) */
                key_sel = 7;
            } else if (i > 3) {
                /* TRI_VID_IDX for CLM-C[0+1] (EVC/OAM) */
                key_sel = 5;    /* TRI_VID */
                JR2_WR(VTSS_ANA_CL_COMMON_CLM_KEY_CFG(i), VTSS_F_ANA_CL_COMMON_CLM_KEY_CFG_CLM_TRI_VID_SEL(1)); /* TRI_VID is selected as TRI_VID_IDX version */
            } else {
                /* NORMAL_7TUPLE for CLM-A, CLM-B[1] (QCL) */
                key_sel = 9;
            }
            JR2_WR(VTSS_ANA_CL_PORT_ADV_CL_CFG(port, i),
                   VTSS_F_ANA_CL_PORT_ADV_CL_CFG_ETYPE_CLM_KEY_SEL(key_sel) |
                   VTSS_M_ANA_CL_PORT_ADV_CL_CFG_LOOKUP_ENA);
        }
        VTSS_RC(jr2_acl_port_conf_set(vtss_state, port_no));

        /* IPMC: Enable IP4_VID/IP6_VID in second IS2 lookup */
        mask = (VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_VID_ENA(lookup) |
                VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_VID_ENA(lookup) |
                VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_ENA(lookup));
        JR2_WRM(VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG(port), mask, mask);

        /* MPLS: CLM-A[0] is used for MLL; from there on it's the actions that select next key type.
         * CLM-A[1] and CLM-B[0,1] are used for single-label MLBS entries.
         *
         * We've found an issue where X1 action NXT_KEY=15 doesn't stop MPLS label stack processing
         * for swap labels, but just skips one lookup and starts doing lookups again. In those cases
         * it'll use the MLBS_CLM_KEY_SEL field from the config in ANA_CL:PORT:ADV_CL_CFG.
         * So, we'll set that field to 15, "no lookup" for all non-MLL lookups, i.e. also in CLM-C.
         */
        JR2_WRM(VTSS_ANA_CL_PORT_ADV_CL_CFG(port, 0),
                VTSS_F_ANA_CL_PORT_ADV_CL_CFG_MPLS_UC_CLM_KEY_SEL(1) |
                VTSS_F_ANA_CL_PORT_ADV_CL_CFG_MPLS_MC_CLM_KEY_SEL(1),
                VTSS_M_ANA_CL_PORT_ADV_CL_CFG_MPLS_UC_CLM_KEY_SEL |
                VTSS_M_ANA_CL_PORT_ADV_CL_CFG_MPLS_MC_CLM_KEY_SEL);
        for (i = 1; i < 6; i++) {
            JR2_WRM(VTSS_ANA_CL_PORT_ADV_CL_CFG(port, i),
                    VTSS_F_ANA_CL_PORT_ADV_CL_CFG_MLBS_CLM_KEY_SEL(15),
                    VTSS_M_ANA_CL_PORT_ADV_CL_CFG_MLBS_CLM_KEY_SEL);
        }
    }

    /* Enable CLM-C[0] (EVC) for CPU port with TRI_VID_IDX */
    JR2_WR(VTSS_ANA_CL_PORT_ADV_CL_CFG(VTSS_CHIP_PORT_CPU, 4),
           VTSS_F_ANA_CL_PORT_ADV_CL_CFG_ETYPE_CLM_KEY_SEL(5) |
           VTSS_M_ANA_CL_PORT_ADV_CL_CFG_LOOKUP_ENA);

    /* Enable LPM on all ports */
    JR2_WR(VTSS_ANA_L3_COMMON_SIP_SECURE_ENA, 0xffffffff);
#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C)
    JR2_WR(VTSS_ANA_L3_COMMON_SIP_SECURE_ENA1, 0xffffffff);
#endif /* VTSS_ARCH_JAGUAR_2_B/C */

    /* Enable ES0 and use VID key for ISDX 0 */
    JR2_WRM_SET(VTSS_REW_COMMON_ES0_CTRL, VTSS_M_REW_COMMON_ES0_CTRL_ES0_LU_ENA);
    JR2_WRM_CLR(VTSS_ANA_L2_ISDX_SERVICE_CTRL(0), VTSS_M_ANA_L2_ISDX_SERVICE_CTRL_ES0_ISDX_KEY_ENA);

    /* 40-bit DMAC replace operation */
    JR2_WRM(VTSS_ANA_ACL_VCAP_S2_SWAP_IP_CTRL,
            VTSS_F_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_DMAC_REPL_OFFSET_VAL(8),
            VTSS_M_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_DMAC_REPL_OFFSET_VAL);

#if defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SERVAL_T)
    /* Force IS2 VID filtering for service frames */
    JR2_WRM_SET(VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL, VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_PAG_FORCE_VID_ENA);
#endif /* VTSS_ARCH_JAGUAR_2_C/SERVAL_T */

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_vcap_state_t     *state = &vtss_state->vcap;
    vtss_vcap_super_obj_t *vcap_super = &state->vcap_super;
    vtss_vcap_obj_t       *clm_a = &state->clm_a.obj;
    vtss_vcap_obj_t       *clm_b = &state->clm_b.obj;
    vtss_vcap_obj_t       *clm_c = &state->clm_c.obj;
    vtss_vcap_obj_t       *lpm = &state->lpm.obj;
    vtss_vcap_obj_t       *is2 = &state->is2.obj;
    vtss_vcap_obj_t       *es0 = &state->es0.obj;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        /* VCAP_SUPER */
        vcap_super->block_map = jr2_vcap_super_block_map;
        vcap_super->block_move = jr2_vcap_super_block_move;

        /* CLM_A */
        clm_a->entry_add = jr2_clm_a_entry_add;
        clm_a->entry_del = jr2_clm_a_entry_del;
        clm_a->entry_move = jr2_clm_a_entry_move;
        clm_a->entry_get = jr2_clm_a_entry_get;
        clm_a->vcap_super = vcap_super;

        /* CLM_B */
        clm_b->entry_add = jr2_clm_b_entry_add;
        clm_b->entry_del = jr2_clm_b_entry_del;
        clm_b->entry_move = jr2_clm_b_entry_move;
        clm_b->entry_get = jr2_clm_b_entry_get;
        clm_b->vcap_super = vcap_super;

        /* CLM_C */
        clm_c->entry_add = jr2_clm_c_entry_add;
        clm_c->entry_del = jr2_clm_c_entry_del;
        clm_c->entry_move = jr2_clm_c_entry_move;
        clm_c->entry_get = jr2_clm_c_entry_get;
        clm_c->vcap_super = vcap_super;
        state->clm_entry_update = jr2_clm_entry_update;
        state->clm_entry_update_masq_hit_ena = jr2_clm_entry_update_masq_hit_ena;

        /* LPM */
        lpm->entry_add = jr2_lpm_entry_add;
        lpm->entry_del = jr2_lpm_entry_del;
        lpm->entry_move = jr2_lpm_entry_move;
        lpm->entry_get = jr2_lpm_entry_get;
        lpm->vcap_super = vcap_super;

        /* IS2 */
        is2->entry_add = jr2_is2_entry_add;
        is2->entry_del = jr2_is2_entry_del;
        is2->entry_move = jr2_is2_entry_move;
        is2->entry_get = jr2_is2_entry_get;
        is2->vcap_super = vcap_super;
        state->is2_entry_update = jr2_is2_entry_update;

        /* ES0 */
        es0->max_count = VTSS_JR2_ES0_CNT;
        es0->entry_add = jr2_es0_entry_add;
        es0->entry_del = jr2_es0_entry_del;
        es0->entry_move = jr2_es0_entry_move;
        es0->entry_get = jr2_es0_entry_get;
        state->es0_entry_update = jr2_es0_entry_update;
        state->es0_esdx_update = jr2_es0_esdx_update;
        state->es0_eflow_update = jr2_es0_eflow_update;

        /* ACL */
        state->acl_policer_set = jr2_acl_policer_set;
        state->acl_sip_set = jr2_acl_sip_set;
        state->acl_port_set = jr2_acl_port_conf_set;
        state->acl_port_counter_get = jr2_acl_port_counter_get;
        state->acl_port_counter_clear = jr2_acl_port_counter_clear;
        state->acl_ace_add = jr2_ace_add;
        state->acl_ace_del = jr2_ace_del;
        state->acl_ace_counter_get = vtss_cmn_ace_counter_get;
        state->acl_ace_counter_clear = vtss_cmn_ace_counter_clear;
        state->range_commit = jr2_vcap_range_commit;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(jr2_vcap_init(vtss_state));
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(jr2_vcap_port_map(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_JAGUAR_2 */
