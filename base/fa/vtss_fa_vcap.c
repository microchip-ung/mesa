// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_VCAP

#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)

/* TG values */
#define FA_VCAP_TG_NONE 0x00
#define FA_VCAP_TG_X1   0x01
#define FA_VCAP_TG_X2   0x02
#define FA_VCAP_TG_X3   0x04
#define FA_VCAP_TG_X6   0x08
#define FA_VCAP_TG_X12  0x10

/* VCAP types encoded in CORE_MAP */
typedef enum {
    /* Do not rearrange, numbers used in CORE_MAP register */
    FA_VCAP_TYPE_NONE,
    FA_VCAP_TYPE_CLM_A,
    FA_VCAP_TYPE_CLM_B,
    FA_VCAP_TYPE_CLM_C,
    FA_VCAP_TYPE_IS2_A,
    FA_VCAP_TYPE_IS2_B,
    FA_VCAP_TYPE_LPM,
    FA_VCAP_TYPE_ES0,   /* Pseudo type, not part of VCAP_SUPER */
    FA_VCAP_TYPE_ES2,   /* Pseudo type, not part of VCAP_SUPER */
    FA_VCAP_TYPE_IP6PFX /* Pseudo type, not part of VCAP_SUPER */
} fa_vcap_type_t;

#define FA_VCAP_ENTRY_WIDTH 32 /* Max entry/data width (32bit words) */

typedef struct {
    vtss_vcap_type_t vcap_type;       /* VCAP type */
    u32 entry[FA_VCAP_ENTRY_WIDTH];  /* ENTRY_DAT */
    u32 mask[FA_VCAP_ENTRY_WIDTH];   /* MASK_DAT */
    u32 action[FA_VCAP_ENTRY_WIDTH]; /* ACTION_DAT */
    u32 counter;                     /* CNT_DAT */
    u32 tg;                          /* TG_DAT */
    u32 type;                        /* Action type */

    /* Debug print fields */
    BOOL                is_action;
    vtss_debug_printf_t pr;
} fa_vcap_data_t;

typedef struct {
    const char *name;         /* Symbolic name */
    BOOL vcap_super;          /* VCAP_SUPER */
    u16  sw_count;            /* Subword count */
    u16  entry_count;         /* Row count */
    u16  entry_width;         /* Entry width */
    u16  action_count;        /* Action count */
    u16  action_width;        /* Action width */
} fa_vcap_props_t;

typedef enum {
    FA_VCAP_SUPER,
    FA_VCAP_ES0,
    FA_VCAP_ES2,
    FA_VCAP_IP6PFX
} fa_vcap_t;

#define FA_BITS_TO_WORDS(x) (((x)+31)/32)

/* CLM: One default action per lookup (6) per port (70)
   IS2: One default action per port (70) in first lookup
   IS2: One default action for second/third/fourth lookup
   LPM: No default action */
#define FA_VCAP_SUPER_SW_COUNT     12
#define FA_VCAP_SUPER_BLK_COUNT    10
#define FA_VCAP_SUPER_ENTRY_COUNT  (FA_VCAP_SUPER_BLK_COUNT * VTSS_VCAP_SUPER_ROW_CNT)
#define FA_VCAP_SUPER_ACTION_COUNT (FA_VCAP_SUPER_ENTRY_COUNT + 7*VTSS_CHIP_PORTS_ALL + 3)

#define FA_VCAP_SUPER_CLM_A_ACTION_BASE FA_VCAP_SUPER_ENTRY_COUNT
#define FA_VCAP_SUPER_CLM_B_ACTION_BASE (FA_VCAP_SUPER_CLM_A_ACTION_BASE + 2*VTSS_CHIP_PORTS_ALL)
#define FA_VCAP_SUPER_CLM_C_ACTION_BASE (FA_VCAP_SUPER_CLM_B_ACTION_BASE + 2*VTSS_CHIP_PORTS_ALL)
#define FA_VCAP_SUPER_IS2_ACTION_BASE   (FA_VCAP_SUPER_CLM_C_ACTION_BASE + 2*VTSS_CHIP_PORTS_ALL)

#define FA_ES2_CNT    1024 /* ES2   : 1024 entries with 12 subwords */
#define FA_IP6PFX_CNT 512  /* IP6PFX: 512 entries with 2 subwords */

static const fa_vcap_props_t fa_vcap_info[] = {
    [FA_VCAP_SUPER] = {
        .name = "VCAP_SUPER",
        .vcap_super = TRUE,
        .sw_count = FA_VCAP_SUPER_SW_COUNT,
        .entry_count = FA_VCAP_SUPER_ENTRY_COUNT,
        .entry_width = 52,
        .action_count = FA_VCAP_SUPER_ACTION_COUNT,
        .action_width = 110,
    },
    [FA_VCAP_ES0] = {
        .name = "VCAP_ES0",
        .vcap_super = FALSE,
        .sw_count = 1,
        .entry_count = VTSS_FA_ES0_CNT,
        .entry_width = 51,
        .action_count = (VTSS_FA_ES0_CNT + VTSS_CHIP_PORTS),
        .action_width = 489,
    },
    [FA_VCAP_ES2] = {
        .name = "VCAP_ES2",
        .vcap_super = FALSE,
        .sw_count = FA_VCAP_SUPER_SW_COUNT,
        .entry_count = FA_ES2_CNT,
        .entry_width = 52,
        .action_count = (FA_ES2_CNT + 74),
        .action_width = 21,
    },
    [FA_VCAP_IP6PFX] = {
        .name = "VCAP_IP6PFX",
        .vcap_super = FALSE,
        .sw_count = 2,
        .entry_count = FA_IP6PFX_CNT,
        .entry_width = 52,
        .action_count = FA_IP6PFX_CNT,
        .action_width = 10,
    }
};

/* VCAP type properties */
typedef struct {
    const char            *name;       /* Symbolic name */
    const fa_vcap_props_t *props;      /* Target properties */
    u32                   tg_width;    /* Key type-group width */
    u32                   type_width;  /* Action type-group width */
} fa_vcap_type_props_t;

static const fa_vcap_type_props_t fa_vcap_type_info[] = {
    [FA_VCAP_TYPE_CLM_A] = {
        .name = "CLM-A",
        .props = &fa_vcap_info[FA_VCAP_SUPER],
        .tg_width = 5,
        .type_width = 3,
    },
    [FA_VCAP_TYPE_CLM_B] = {
        .name = "CLM-B",
        .props = &fa_vcap_info[FA_VCAP_SUPER],
        .tg_width = 5,
        .type_width = 3,
    },
    [FA_VCAP_TYPE_CLM_C] = {
        .name = "CLM-C",
        .props = &fa_vcap_info[FA_VCAP_SUPER],
        .tg_width = 5,
        .type_width = 3,
    },
    [FA_VCAP_TYPE_IS2_A] = {
        .name = "IS2-A",
        .props = &fa_vcap_info[FA_VCAP_SUPER],
        .tg_width = 3,
        .type_width = 2,
    },
    [FA_VCAP_TYPE_IS2_B] = {
        .name = "IS2-B",
        .props = &fa_vcap_info[FA_VCAP_SUPER],
        .tg_width = 3,
        .type_width = 2,
    },
    [FA_VCAP_TYPE_LPM] = {
        .name = "LPM",
        .props = &fa_vcap_info[FA_VCAP_SUPER],
        .tg_width = 4,
        .type_width = 0,
    },
    [FA_VCAP_TYPE_ES0] = {
        .name = "ES0",
        .props = &fa_vcap_info[FA_VCAP_ES0],
        .tg_width = 0,
        .type_width = 0,
    },
    [FA_VCAP_TYPE_ES2] = {
        .name = "ES2",
        .props = &fa_vcap_info[FA_VCAP_ES2],
        .tg_width = 3,
        .type_width = 2,
    },
    [FA_VCAP_TYPE_IP6PFX] = {
        .name = "IP6PFX",
        .props = &fa_vcap_info[FA_VCAP_IP6PFX],
        .tg_width = 2,
        .type_width = 1,
    },
};

/* VCAP data selection */
#define FA_VCAP_SEL_ENTRY   0x01 /* Select entry */
#define FA_VCAP_SEL_ACTION  0x02 /* Select action */
#define FA_VCAP_SEL_COUNTER 0x04 /* Select counter */
#define FA_VCAP_SEL_ALL     0xff /* Select all */

/* VCAP commands */
#define FA_VCAP_CMD_WRITE      0 /* Copy from Cache to VCAP */
#define FA_VCAP_CMD_READ       1 /* Copy from VCAP to Cache */
#define FA_VCAP_CMD_MOVE_DOWN  2 /* Move <count> down */
#define FA_VCAP_CMD_MOVE_UP    3 /* Move <count> up */
#define FA_VCAP_CMD_INITIALIZE 4 /* Write all (from cache) */

/* - VCAP ---------------------------------------------------------- */

typedef struct {
    /* Input fields */
    fa_vcap_type_t bank;
    u32            update_addr;
    u32            update_cmd;
    u32            update_sel;
    u32            mv_size;
    u32            mv_pos;
    u32            ndx;

    /* Output fields */
    u32            update_ctrl;
    u32            update_ctrl_value;
    u32            update_ctrl_mask;
    u32            mv_cfg;
    u32            mv_cfg_value;
    u32            entry_dat;
    u32            mask_dat;
    u32            action_dat;
    u32            cnt_dat;
    u32            entry_width;
    u32            entry_cnt;
    u32            entry_swcnt;
    u32            action_def_cnt;
    u32            action_width;
    u32            cnt_width;
} vtss_fa_vcap_reg_info_t;

static vtss_rc fa_vcap_reg_info_get(vtss_fa_vcap_reg_info_t *info)
{
    BOOL ent_dis = (info->update_sel & FA_VCAP_SEL_ENTRY ? 0 : 1);
    BOOL act_dis = (info->update_sel & FA_VCAP_SEL_ACTION ? 0 : 1);
    BOOL cnt_dis = (info->update_sel & FA_VCAP_SEL_COUNTER ? 0 : 1);
    BOOL clear = (info->update_cmd == FA_VCAP_CMD_INITIALIZE);

    switch (info->bank) {
    case FA_VCAP_TYPE_CLM_A:
    case FA_VCAP_TYPE_CLM_B:
    case FA_VCAP_TYPE_CLM_C:
    case FA_VCAP_TYPE_IS2_A:
    case FA_VCAP_TYPE_IS2_B:
    case FA_VCAP_TYPE_LPM:
        info->update_ctrl = VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL;
        info->update_ctrl_value = (VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_CMD(info->update_cmd) |
                                   VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(ent_dis) |
                                   VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(act_dis) |
                                   VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(cnt_dis) |
                                   VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ADDR(info->update_addr) |
                                   VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_CLEAR_CACHE(clear) |
                                   VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_SHOT);
        info->update_ctrl_mask = VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_SHOT;
        info->mv_cfg = VTSS_VCAP_SUPER_VCAP_MV_CFG;
        info->mv_cfg_value = (VTSS_F_VCAP_SUPER_VCAP_MV_CFG_MV_NUM_POS(info->mv_pos) |
                              VTSS_F_VCAP_SUPER_VCAP_MV_CFG_MV_SIZE(info->mv_size));
        info->entry_dat = VTSS_VCAP_SUPER_VCAP_ENTRY_DAT(info->ndx);
        info->mask_dat = VTSS_VCAP_SUPER_VCAP_MASK_DAT(info->ndx);
        info->action_dat = VTSS_VCAP_SUPER_VCAP_ACTION_DAT(info->ndx);
        info->cnt_dat = VTSS_VCAP_SUPER_VCAP_CNT_DAT(0);
        info->entry_width = VTSS_VCAP_SUPER_ENTRY_WIDTH;
        info->entry_cnt = VTSS_VCAP_SUPER_ENTRY_CNT;
        info->entry_swcnt = VTSS_VCAP_SUPER_ENTRY_SWCNT;
        info->action_def_cnt = VTSS_VCAP_SUPER_ACTION_DEF_CNT;
        info->action_width = VTSS_VCAP_SUPER_ACTION_WIDTH;
        info->cnt_width = VTSS_VCAP_SUPER_CNT_WIDTH;
        break;
    case FA_VCAP_TYPE_ES0:
        info->update_ctrl = VTSS_VCAP_ES0_VCAP_UPDATE_CTRL;
        info->update_ctrl_value = (VTSS_F_VCAP_ES0_VCAP_UPDATE_CTRL_UPDATE_CMD(info->update_cmd) |
                                   VTSS_F_VCAP_ES0_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(ent_dis) |
                                   VTSS_F_VCAP_ES0_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(act_dis) |
                                   VTSS_F_VCAP_ES0_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(cnt_dis) |
                                   VTSS_F_VCAP_ES0_VCAP_UPDATE_CTRL_UPDATE_ADDR(info->update_addr) |
                                   VTSS_F_VCAP_ES0_VCAP_UPDATE_CTRL_CLEAR_CACHE(clear) |
                                   VTSS_M_VCAP_ES0_VCAP_UPDATE_CTRL_UPDATE_SHOT);
        info->update_ctrl_mask = VTSS_M_VCAP_ES0_VCAP_UPDATE_CTRL_UPDATE_SHOT;
        info->mv_cfg = VTSS_VCAP_ES0_VCAP_MV_CFG;
        info->mv_cfg_value = (VTSS_F_VCAP_ES0_VCAP_MV_CFG_MV_NUM_POS(info->mv_pos) |
                              VTSS_F_VCAP_ES0_VCAP_MV_CFG_MV_SIZE(info->mv_size));
        info->entry_dat = VTSS_VCAP_ES0_VCAP_ENTRY_DAT(info->ndx);
        info->mask_dat = VTSS_VCAP_ES0_VCAP_MASK_DAT(info->ndx);
        info->action_dat = VTSS_VCAP_ES0_VCAP_ACTION_DAT(info->ndx);
        info->cnt_dat = VTSS_VCAP_ES0_VCAP_CNT_DAT(0);
        info->entry_width = VTSS_VCAP_ES0_ENTRY_WIDTH;
        info->entry_cnt = VTSS_VCAP_ES0_ENTRY_CNT;
        info->entry_swcnt = VTSS_VCAP_ES0_ENTRY_SWCNT;
        info->action_def_cnt = VTSS_VCAP_ES0_ACTION_DEF_CNT;
        info->action_width = VTSS_VCAP_ES0_ACTION_WIDTH;
        info->cnt_width = VTSS_VCAP_ES0_CNT_WIDTH;
        break;
    case FA_VCAP_TYPE_ES2:
        info->update_ctrl = VTSS_VCAP_ES2_VCAP_UPDATE_CTRL;
        info->update_ctrl_value = (VTSS_F_VCAP_ES2_VCAP_UPDATE_CTRL_UPDATE_CMD(info->update_cmd) |
                                   VTSS_F_VCAP_ES2_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(ent_dis) |
                                   VTSS_F_VCAP_ES2_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(act_dis) |
                                   VTSS_F_VCAP_ES2_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(cnt_dis) |
                                   VTSS_F_VCAP_ES2_VCAP_UPDATE_CTRL_UPDATE_ADDR(info->update_addr) |
                                   VTSS_F_VCAP_ES2_VCAP_UPDATE_CTRL_CLEAR_CACHE(clear) |
                                   VTSS_M_VCAP_ES2_VCAP_UPDATE_CTRL_UPDATE_SHOT);
        info->update_ctrl_mask = VTSS_M_VCAP_ES2_VCAP_UPDATE_CTRL_UPDATE_SHOT;
        info->mv_cfg = VTSS_VCAP_ES2_VCAP_MV_CFG;
        info->mv_cfg_value = (VTSS_F_VCAP_ES2_VCAP_MV_CFG_MV_NUM_POS(info->mv_pos) |
                              VTSS_F_VCAP_ES2_VCAP_MV_CFG_MV_SIZE(info->mv_size));
        info->entry_dat = VTSS_VCAP_ES2_VCAP_ENTRY_DAT(info->ndx);
        info->mask_dat = VTSS_VCAP_ES2_VCAP_MASK_DAT(info->ndx);
        info->action_dat = VTSS_VCAP_ES2_VCAP_ACTION_DAT(info->ndx);
        info->cnt_dat = VTSS_VCAP_ES2_VCAP_CNT_DAT(0);
        info->entry_width = VTSS_VCAP_ES2_ENTRY_WIDTH;
        info->entry_cnt = VTSS_VCAP_ES2_ENTRY_CNT;
        info->entry_swcnt = VTSS_VCAP_ES2_ENTRY_SWCNT;
        info->action_def_cnt = VTSS_VCAP_ES2_ACTION_DEF_CNT;
        info->action_width = VTSS_VCAP_ES2_ACTION_WIDTH;
        info->cnt_width = VTSS_VCAP_ES2_CNT_WIDTH;
        break;
    case FA_VCAP_TYPE_IP6PFX:
        info->update_ctrl = VTSS_VCAP_IP6PFX_VCAP_UPDATE_CTRL;
        info->update_ctrl_value = (VTSS_F_VCAP_IP6PFX_VCAP_UPDATE_CTRL_UPDATE_CMD(info->update_cmd) |
                                   VTSS_F_VCAP_IP6PFX_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(ent_dis) |
                                   VTSS_F_VCAP_IP6PFX_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(act_dis) |
                                   VTSS_F_VCAP_IP6PFX_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(cnt_dis) |
                                   VTSS_F_VCAP_IP6PFX_VCAP_UPDATE_CTRL_UPDATE_ADDR(info->update_addr) |
                                   VTSS_F_VCAP_IP6PFX_VCAP_UPDATE_CTRL_CLEAR_CACHE(clear) |
                                   VTSS_M_VCAP_IP6PFX_VCAP_UPDATE_CTRL_UPDATE_SHOT);
        info->update_ctrl_mask = VTSS_M_VCAP_IP6PFX_VCAP_UPDATE_CTRL_UPDATE_SHOT;
        info->mv_cfg = VTSS_VCAP_IP6PFX_VCAP_MV_CFG;
        info->mv_cfg_value = (VTSS_F_VCAP_IP6PFX_VCAP_MV_CFG_MV_NUM_POS(info->mv_pos) |
                              VTSS_F_VCAP_IP6PFX_VCAP_MV_CFG_MV_SIZE(info->mv_size));
        info->entry_dat = VTSS_VCAP_IP6PFX_VCAP_ENTRY_DAT(info->ndx);
        info->mask_dat = VTSS_VCAP_IP6PFX_VCAP_MASK_DAT(info->ndx);
        info->action_dat = VTSS_VCAP_IP6PFX_VCAP_ACTION_DAT(info->ndx);
        info->cnt_dat = VTSS_VCAP_IP6PFX_VCAP_CNT_DAT(0);
        info->entry_width = VTSS_VCAP_IP6PFX_ENTRY_WIDTH;
        info->entry_cnt = VTSS_VCAP_IP6PFX_ENTRY_CNT;
        info->entry_swcnt = VTSS_VCAP_IP6PFX_ENTRY_SWCNT;
        info->action_def_cnt = VTSS_VCAP_IP6PFX_ACTION_DEF_CNT;
        info->action_width = VTSS_VCAP_IP6PFX_ACTION_WIDTH;
        info->cnt_width = VTSS_VCAP_IP6PFX_CNT_WIDTH;
        break;
    default:
        VTSS_E("unknown bank: %u", info->bank);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_vcap_cmd(vtss_state_t *vtss_state, vtss_fa_vcap_reg_info_t *info)
{
    u32 value;

    REG_WR(info->mv_cfg, info->mv_cfg_value);
    REG_WR(info->update_ctrl, info->update_ctrl_value);
    do {
        REG_RD(info->update_ctrl, &value);
    } while (value & info->update_ctrl_mask);

    return VTSS_RC_OK;
}

static vtss_rc fa_vcap_initialize(vtss_state_t *vtss_state, fa_vcap_type_t bank)
{
    const fa_vcap_props_t   *props = fa_vcap_type_info[bank].props;
    vtss_fa_vcap_reg_info_t info;

    VTSS_I("init %s, entry_count: %u, action_count: %u", props->name, props->entry_count, props->action_count);

    /* First write entries */
    VTSS_MEMSET(&info, 0, sizeof(info));
    info.bank = bank;
    info.update_cmd = FA_VCAP_CMD_INITIALIZE;
    info.update_sel = FA_VCAP_SEL_ALL;
    info.mv_size = (props->entry_count * props->sw_count);
    VTSS_RC(fa_vcap_reg_info_get(&info));
    VTSS_RC(fa_vcap_cmd(vtss_state, &info));

    /* Then actions and counters */
    info.update_sel = (FA_VCAP_SEL_ACTION | FA_VCAP_SEL_COUNTER);
    info.mv_size = (props->action_count * props->sw_count);
    VTSS_RC(fa_vcap_reg_info_get(&info));
    VTSS_RC(fa_vcap_cmd(vtss_state, &info));

    return VTSS_RC_OK;
}

static fa_vcap_type_t fa_vcap_type(vtss_vcap_type_t type)
{
    return (type == VTSS_VCAP_TYPE_CLM_A ? FA_VCAP_TYPE_CLM_A :
            type == VTSS_VCAP_TYPE_CLM_B ? FA_VCAP_TYPE_CLM_B :
            type == VTSS_VCAP_TYPE_CLM_C ? FA_VCAP_TYPE_CLM_C :
            type == VTSS_VCAP_TYPE_IS2 ? FA_VCAP_TYPE_IS2_A :
            type == VTSS_VCAP_TYPE_IS2_B ? FA_VCAP_TYPE_IS2_B :
            type == VTSS_VCAP_TYPE_ES2 ? FA_VCAP_TYPE_ES2 :
            type == VTSS_VCAP_TYPE_LPM ? FA_VCAP_TYPE_LPM :
            type == VTSS_VCAP_TYPE_ES0 ? FA_VCAP_TYPE_ES0 : FA_VCAP_TYPE_NONE);
}

static u32 fa_vcap_key_type(vtss_vcap_type_t type, vtss_vcap_key_size_t key_size)
{
    return (key_size == VTSS_VCAP_KEY_SIZE_TWELFTH || type == VTSS_VCAP_TYPE_ES0 ? FA_VCAP_TG_X1 :
            key_size == VTSS_VCAP_KEY_SIZE_SIXTH ? FA_VCAP_TG_X2 :
            key_size == VTSS_VCAP_KEY_SIZE_QUARTER ? FA_VCAP_TG_X3 :
            key_size == VTSS_VCAP_KEY_SIZE_HALF ? FA_VCAP_TG_X6 : FA_VCAP_TG_X12);
}

static u32 fa_vcap_action_addr(vtss_vcap_type_t type, u32 port, u32 lookup)
{
    u32 base = (type == VTSS_VCAP_TYPE_IS2 ? FA_VCAP_SUPER_IS2_ACTION_BASE :
                type == VTSS_VCAP_TYPE_CLM_A ? FA_VCAP_SUPER_CLM_A_ACTION_BASE :
                type == VTSS_VCAP_TYPE_CLM_B ? FA_VCAP_SUPER_CLM_B_ACTION_BASE :
                type == VTSS_VCAP_TYPE_CLM_C ? FA_VCAP_SUPER_CLM_C_ACTION_BASE :
                type == VTSS_VCAP_TYPE_ES2 ? FA_ES2_CNT :
                type == VTSS_VCAP_TYPE_ES0 ? VTSS_FA_ES0_CNT : 0);
    u32 sw_cnt = (type == VTSS_VCAP_TYPE_ES0 ? 1 : FA_VCAP_SUPER_SW_COUNT);

    return ((base + lookup * VTSS_CHIP_PORTS_ALL + port) * sw_cnt);
}

static u32 fa_vcap_entry_addr(vtss_state_t *vtss_state, vtss_vcap_type_t type, vtss_vcap_idx_t *idx)
{
    fa_vcap_type_t        bank = fa_vcap_type(type);
    const fa_vcap_props_t *props = fa_vcap_type_info[bank].props;
    vtss_vcap_super_obj_t *vcap_super = &vtss_state->vcap.vcap_super;
    u32                   i, addr = idx->row;
    BOOL                  found = FALSE;

    if (props->vcap_super) {
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
    }
    addr *= props->sw_count;
    addr += ((idx->col + 1) * props->sw_count/vtss_vcap_key_rule_count(idx->key_size));
    return (props->entry_count * props->sw_count - addr);
}

static u32 fa_vcap_tg_count(u32 tg)
{
    return (tg == FA_VCAP_TG_X12 ? 12 :
            tg == FA_VCAP_TG_X6 ? 6 :
            tg == FA_VCAP_TG_X3 ? 3 :
            tg == FA_VCAP_TG_X2 ? 2 :
            tg == FA_VCAP_TG_X1 ? 1 : 0);
}

static vtss_rc fa_vcap_entry_cmd(vtss_state_t *vtss_state,
                                 fa_vcap_data_t *data, u32 addr_base, u32 tg_in, u32 cmd, u32 sel)
{
    fa_vcap_type_t             bank = fa_vcap_type(data->vcap_type);
    const fa_vcap_type_props_t *props;
    u32                        addr, i, j, count, tg, tgw, w, value, mask, cnt;
    u32                        action_offs = 0, entry_offs = 0, addr_count;
    vtss_fa_vcap_reg_info_t    info;

    if (bank == FA_VCAP_TYPE_NONE) {
        VTSS_E("unknown VCAP type");
        return VTSS_RC_ERROR;
    }
    props = &fa_vcap_type_info[bank];

    /* Process subwords */
    addr_count = fa_vcap_tg_count(tg_in);
    for (i = 0; i < addr_count; i++) {
        addr = (addr_base + i);
        VTSS_MEMSET(&info, 0, sizeof(info));
        info.bank = bank;
        info.update_addr = addr;
        info.update_cmd = cmd;
        info.update_sel = sel;
        VTSS_RC(fa_vcap_reg_info_get(&info));
        if (cmd == FA_VCAP_CMD_READ) {
            VTSS_RC(fa_vcap_cmd(vtss_state, &info));
        }

        /* Entry */
        if (sel & FA_VCAP_SEL_ENTRY) {
            count = FA_BITS_TO_WORDS(props->props->entry_width);
            for (j = 0; j < count; j++) {
                info.ndx = j;
                VTSS_RC(fa_vcap_reg_info_get(&info));
                if (cmd == FA_VCAP_CMD_READ && i == 0 && j == 0) {
                    /* Read TG for first word in base address */
                    REG_RD(info.entry_dat, &value);
                    REG_RD(info.mask_dat, &mask);
                    if ((value & 1) == 1 && (mask & 1) == 1) {
                        /* Match-off means that entry is disabled */
                        tg = FA_VCAP_TG_NONE;
                    } else {
                        tg = FA_VCAP_TG_X1;
                        w = props->tg_width;
                        if (w) {
                            tgw = ((addr % 12) == 0 ? w :
                                   (addr % 6) == 0 ? (w > 3 ? 4 : 2) :
                                   (addr % 3) == 0 ? (w > 3 ? 3 : 1) :
                                   (addr % 2) == 0 ? (w == 3 ? 0 : 2) :
                                   (w > 3 ? 1 : 0));
                            tg = (VTSS_EXTRACT_BITFIELD(value, 0, tgw) & ~mask);
                            if (w == 3) {
                                /* IS2/ES2 */
                                tg = (tg << 2);
                            }
                        }
                    }
                    data->tg = ((tg & FA_VCAP_TG_X1) ? FA_VCAP_TG_X1 :
                                (tg & FA_VCAP_TG_X2) ? FA_VCAP_TG_X2 :
                                (tg & FA_VCAP_TG_X3) ? FA_VCAP_TG_X3 :
                                (tg & FA_VCAP_TG_X6) ? FA_VCAP_TG_X6 :
                                (tg & FA_VCAP_TG_X12) ? FA_VCAP_TG_X12 : FA_VCAP_TG_NONE);
                }

                /* Calculate data and TG width */
                tg = data->tg;
                tgw = ((j != 0 || props->tg_width == 0 || tg == FA_VCAP_TG_NONE) ? 0 :
                       (tg > FA_VCAP_TG_X6 && (addr % 12) == 0) ? 5 :
                       (tg > FA_VCAP_TG_X3 && (addr % 6) == 0) ? 4 :
                       (tg > FA_VCAP_TG_X2 && (addr % 3) == 0) ? 3 :
                       (tg > FA_VCAP_TG_X1 && (addr % 2) == 0) ? 2 :
                       (tg == FA_VCAP_TG_X3 ? 2 : 1));
                if (props->tg_width == 3) {
                    /* IS2/ES2 */
                    tgw = (tgw < 2 ? 0 : tgw - 2);
                    tg = (tg >> 2);
                }
                w = (props->props->entry_width % 32);
                w = ((j == (count - 1) && w != 0 ? w : 32) - tgw);
                if (cmd == FA_VCAP_CMD_READ) {
                    /* Read from entry cache */
                    REG_RD(info.entry_dat, &value);
                    REG_RD(info.mask_dat, &mask);
                    REG_RD(info.cnt_dat, &cnt);
                    VTSS_N("addr: %u, j: %u, value/mask: 0x%08x/%08x, cnt: %u", addr, j, value, mask, cnt);
                    vtss_bs_set(data->entry, entry_offs, w, value >> tgw);
                    vtss_bs_set(data->mask, entry_offs, w, ~mask >> tgw);
                } else {
                    /* Write to entry cache */
                    value = ((vtss_bs_get(data->entry, entry_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(tg, 0, tgw));
                    mask = ((vtss_bs_get(data->mask, entry_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(0xff, 0, tgw));
                    VTSS_N("addr: %u, j: %u, value/mask: 0x%08x/%08x", addr, j, value, ~mask);
                    REG_WR(info.entry_dat, value);
                    REG_WR(info.mask_dat, ~mask);
                }
                entry_offs += w;
            }
        }

        /* Action */
        if ((sel & FA_VCAP_SEL_ACTION) && (i == 0 || i < fa_vcap_tg_count(data->type))) {
            count = FA_BITS_TO_WORDS(props->props->action_width);
            for (j = 0; j < count; j++) {
                info.ndx = j;
                VTSS_RC(fa_vcap_reg_info_get(&info));
                if (cmd == FA_VCAP_CMD_READ && i == 0 && j == 0) {
                    /* Read TG for first word in base address */
                    data->type = FA_VCAP_TG_X1;
                    w = props->type_width;
                    if (w) {
                        tgw = ((addr % 3) == 0 ? w :
                               ((addr % 2) == 0 && w > 2) ? 2 : 1);
                        REG_RD(info.action_dat, &value);
                        tg = VTSS_EXTRACT_BITFIELD(value, 0, tgw);
                        if (w == 2) {
                            /* IS2/ES2 */
                            tg = (tg << 1);
                        }
                        data->type = ((tg & FA_VCAP_TG_X1) ? FA_VCAP_TG_X1 :
                                      (tg & FA_VCAP_TG_X2) ? FA_VCAP_TG_X2 :
                                      (tg & FA_VCAP_TG_X3) ? FA_VCAP_TG_X3 : FA_VCAP_TG_NONE);
                    }
                }

                /* Calculate data and TG width */
                tg = data->type;
                tgw = 0;
                if (j == 0 && props->type_width != 0) {
                    tgw = ((tg > FA_VCAP_TG_X2 && (addr % 3) == 0) ? 3 :
                           (tg > FA_VCAP_TG_X1 && (addr % 2) == 0) ? 2 :
                           (tg == FA_VCAP_TG_X3 ? 2 : 1));
                    if (props->type_width == 2) {
                        /* IS2/ES2 */
                        tgw = (tgw - 1);
                        tg = (tg >> 1);
                    }
                }
                w = (props->props->action_width % 32);
                w = ((j == (count - 1) && w != 0 ? w : 32) - tgw);
                if (cmd == FA_VCAP_CMD_READ) {
                    /* Read from action cache */
                    REG_RD(info.action_dat, &value);
                    VTSS_N("addr: %u, j: %u, action: 0x%08x", addr, j, value);
                    vtss_bs_set(data->action, action_offs, w, value >> tgw);
                } else {
                    /* Write to action cache */
                    value = ((vtss_bs_get(data->action, action_offs, w) << tgw) + VTSS_ENCODE_BITFIELD(tg, 0, tgw));
                    VTSS_N("addr: %u, j: %u, action: 0x%08x", addr, j, value);
                    REG_WR(info.action_dat, value);
                }
                action_offs += w;
            }
        }

        if ((sel & FA_VCAP_SEL_COUNTER) && i == 0) {
            if (cmd == FA_VCAP_CMD_READ) {
                REG_RD(info.cnt_dat, &data->counter);
            } else {
                REG_WR(info.cnt_dat, data->counter);
            }
        }

        if (cmd == FA_VCAP_CMD_WRITE) {
            VTSS_RC(fa_vcap_cmd(vtss_state, &info));
        }
    } /* Address loop */
    return VTSS_RC_OK;
}

static vtss_rc fa_vcap_entry_del(vtss_state_t *vtss_state, vtss_vcap_type_t type, vtss_vcap_idx_t *idx)
{
    fa_vcap_type_t             bank = fa_vcap_type(type);
#if VTSS_OPT_TRACE
    const fa_vcap_type_props_t *props = &fa_vcap_type_info[bank];
#endif
    u32                        addr = fa_vcap_entry_addr(vtss_state, type, idx);
    u32                        size = fa_vcap_tg_count(fa_vcap_key_type(type, idx->key_size));
    vtss_fa_vcap_reg_info_t    info;

    VTSS_I("%s, row: %u, col: %u, addr: %u", props->name, idx->row, idx->col, addr);
    VTSS_MEMSET(&info, 0, sizeof(info));
    info.bank = bank;
    info.update_addr = addr;
    info.update_cmd = FA_VCAP_CMD_INITIALIZE;
    info.update_sel = FA_VCAP_SEL_ALL;
    info.mv_size = (size - 1);
    VTSS_RC(fa_vcap_reg_info_get(&info));
    return fa_vcap_cmd(vtss_state, &info);
}

static vtss_rc fa_vcap_entry_move(vtss_state_t *vtss_state,
                                  vtss_vcap_type_t type, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    fa_vcap_type_t             bank = fa_vcap_type(type);
    const fa_vcap_type_props_t *props = &fa_vcap_type_info[bank];
    u32                        addr, cnt = (props->props->sw_count/vtss_vcap_key_rule_count(idx->key_size));
    vtss_fa_vcap_reg_info_t    info;

    if (count == 0) {
        VTSS_E("illegal count zero");
        return VTSS_RC_ERROR;
    }
    addr = (fa_vcap_entry_addr(vtss_state, type, idx) - (count - 1) * cnt);
    VTSS_I("%s, row: %u, col: %u, %s, count: %u, up: %u, addr: %u",
           props->name, idx->row, idx->col, vtss_vcap_key_size2txt(idx->key_size), count, up, addr);
    VTSS_MEMSET(&info, 0, sizeof(info));
    info.bank = bank;
    info.update_addr = addr;
    info.update_cmd = (up ? FA_VCAP_CMD_MOVE_UP : FA_VCAP_CMD_MOVE_DOWN);
    info.update_sel = FA_VCAP_SEL_ALL;
    info.mv_size = (count * cnt - 1);
    info.mv_pos = (cnt - 1);
    VTSS_RC(fa_vcap_reg_info_get(&info));
    return fa_vcap_cmd(vtss_state, &info);
}

static vtss_rc fa_vcap_entry_get(vtss_state_t *vtss_state,
                                 vtss_vcap_type_t type, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
#if VTSS_OPT_TRACE
    fa_vcap_type_t             bank = fa_vcap_type(type);
    const fa_vcap_type_props_t *props = &fa_vcap_type_info[bank];
#endif
    u32                        addr;
    fa_vcap_data_t             data;

    addr = fa_vcap_entry_addr(vtss_state, type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u", props->name, idx->row, idx->col, addr);
    data.vcap_type = type;
    VTSS_RC(fa_vcap_entry_cmd(vtss_state, &data, addr, FA_VCAP_TG_X1, FA_VCAP_CMD_READ, FA_VCAP_SEL_COUNTER));
    *counter = data.counter;
    if (clear) {
        data.counter = 0;
        VTSS_RC(fa_vcap_entry_cmd(vtss_state, &data, addr, FA_VCAP_TG_X1, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_COUNTER));
    }
    return VTSS_RC_OK;
}

/* - VCAP_SUPER ---------------------------------------------------- */

static vtss_rc fa_vcap_super_block_map(vtss_state_t *vtss_state, u32 block, vtss_vcap_type_t type)
{
    fa_vcap_type_t bank = fa_vcap_type(type);
    u32            max_count = vtss_state->vcap.vcap_super.block.max_count;

    VTSS_I("block: %i, type: %s", block, vtss_vcap_type_txt(type));

    if (block >= max_count) {
        VTSS_E("block: %u, max_count: %u", block, max_count);
        return VTSS_RC_ERROR;
    }
    REG_WR(VTSS_VCAP_SUPER_VCAP_CORE_IDX,
           VTSS_F_VCAP_SUPER_VCAP_CORE_IDX_CORE_IDX(FA_VCAP_SUPER_BLK_COUNT - block - 1));
    REG_WR(VTSS_VCAP_SUPER_VCAP_CORE_MAP,
           VTSS_F_VCAP_SUPER_VCAP_CORE_MAP_CORE_MAP(bank));
    return VTSS_RC_OK;
}

static vtss_rc fa_vcap_super_block_move(vtss_state_t *vtss_state, u32 block, BOOL up)
{
    vtss_vcap_super_obj_t   *vcap_super = &vtss_state->vcap.vcap_super;
    u32                     addr, cnt, max_count = vtss_state->vcap.vcap_super.block.max_count;
    vtss_fa_vcap_reg_info_t info;

    if (block >= max_count) {
        VTSS_E("block: %u, max_count: %u", block, max_count);
        return VTSS_RC_ERROR;
    }
    cnt = (vcap_super->row_count * FA_VCAP_SUPER_SW_COUNT);
    addr = ((FA_VCAP_SUPER_BLK_COUNT - block - 1) * cnt);
    VTSS_I("block: %i, up: %u, addr: %u, cnt: %u", block, up, addr, cnt);
    VTSS_MEMSET(&info, 0, sizeof(info));
    info.bank = FA_VCAP_TYPE_CLM_A; /* VCAP_SUPER */
    info.update_addr = addr;
    info.update_cmd = (up ? FA_VCAP_CMD_MOVE_UP : FA_VCAP_CMD_MOVE_DOWN);
    info.update_sel = FA_VCAP_SEL_ALL;
    info.mv_size = (cnt - 1);
    info.mv_pos = (cnt - 1);
    VTSS_RC(fa_vcap_reg_info_get(&info));
    return fa_vcap_cmd(vtss_state, &info);
}

/* - VCAP ---------------------------------------------------------- */

static vtss_vcap_range_chk_table_t *fa_vcap_range_get(vtss_state_t *vtss_state, vtss_vcap_type_t type)
{
    return (type == VTSS_VCAP_TYPE_IS2 || type == VTSS_VCAP_TYPE_IS2_B ? &vtss_state->vcap.is2_range :
            type == VTSS_VCAP_TYPE_ES2 ? &vtss_state->vcap.es2_range : &vtss_state->vcap.range);
}

static vtss_rc fa_vcap_range_commit(vtss_state_t *vtss_state, vtss_vcap_type_t vcap_type, vtss_vcap_range_chk_table_t *new_table)
{
    u32                         i, type;
    vtss_vcap_range_chk_t       *entry;
    vtss_vcap_range_chk_table_t *table = fa_vcap_range_get(vtss_state, vcap_type);

    if (new_table != NULL) {
        if (!VTSS_MEMCMP(table, new_table, sizeof(*table))) {
            /* Table unchanged */
            return VTSS_RC_OK;
        }
        *table = *new_table;
    }

    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        entry = &table->entry[i];
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
        switch (vcap_type) {
        case VTSS_VCAP_TYPE_IS2:
        case VTSS_VCAP_TYPE_IS2_B:
            /* IS2 */
            REG_WR(VTSS_ANA_ACL_VCAP_S2_RNG_CTRL(i),
                   VTSS_F_ANA_ACL_VCAP_S2_RNG_CTRL_RNG_TYPE_SEL(type));
            REG_WR(VTSS_ANA_ACL_VCAP_S2_RNG_VALUE_CFG(i),
                   VTSS_F_ANA_ACL_VCAP_S2_RNG_VALUE_CFG_RNG_MIN_VALUE(entry->min) |
                   VTSS_F_ANA_ACL_VCAP_S2_RNG_VALUE_CFG_RNG_MAX_VALUE(entry->max));
            break;
        case VTSS_VCAP_TYPE_ES2:
            /* ES2 */
            REG_WR(VTSS_EACL_VCAP_ES2_RNG_CTRL(i),
                   VTSS_F_EACL_VCAP_ES2_RNG_CTRL_RNG_TYPE_SEL(type));
            REG_WR(VTSS_EACL_VCAP_ES2_RNG_VALUE_CFG(i),
                   VTSS_F_EACL_VCAP_ES2_RNG_VALUE_CFG_RNG_MIN_VALUE(entry->min) |
                   VTSS_F_EACL_VCAP_ES2_RNG_VALUE_CFG_RNG_MAX_VALUE(entry->max));
            break;
        default:
            /* CLM */
            REG_WR(VTSS_ANA_CL_ADV_RNG_CTRL(i),
                   VTSS_F_ANA_CL_ADV_RNG_CTRL_RNG_TYPE_SEL(type == 4 ? 7 : type));
            REG_WR(VTSS_ANA_CL_ADV_RNG_VALUE_CFG(i),
                   VTSS_F_ANA_CL_ADV_RNG_VALUE_CFG_RNG_MIN_VALUE(entry->min) |
                   VTSS_F_ANA_CL_ADV_RNG_VALUE_CFG_RNG_MAX_VALUE(entry->max));
            break;
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_clm_range_commit(vtss_state_t *vtss_state)
{
    return fa_vcap_range_commit(vtss_state, VTSS_VCAP_TYPE_CLM_A, NULL);
}

static u32 fa_entry_bs_get(fa_vcap_data_t *data, u32 offs, u32 len)
{
    return vtss_bs_get(data->entry, offs, len);
}

static u32 fa_mask_bs_get(fa_vcap_data_t *data, u32 offs, u32 len)
{
    return vtss_bs_get(data->mask, offs, len);
}

static u32 fa_act_get(fa_vcap_data_t *data, u32 offs, u32 len)
{
    return vtss_bs_get(data->action, offs, len);
}

static void fa_act_set(fa_vcap_data_t *data, u32 offs, u32 len, u32 value)
{
    vtss_bs_set(data->action, offs, len, len == 1 ? (value ? 1 : 0) : value);
}

static void fa_act_ena_set(fa_vcap_data_t *data, u32 offs_ena, u32 offs, u32 len, u32 enable, u32 value)
{
    vtss_bs_set(data->action, offs_ena, 1, enable ? 1 : 0);
    vtss_bs_set(data->action, offs, len, enable ? value : 0);
}

static void fa_vcap_key_set(fa_vcap_data_t *data, u32 offset, u32 width, u32 value, u32 mask)
{
    VTSS_N("offset: %u, width: %u, value: 0x%08x, mask: 0x%08x", offset, width, value, mask);

    if (width > 32) {
        VTSS_E("illegal width: %u, offset: %u", width, offset);
    } else {
        vtss_bs_set(data->entry, offset, width, value & mask); /* Avoid 'match-off' */
        vtss_bs_set(data->mask, offset , width, mask);
    }
}

static void fa_vcap_key_bytes_set(fa_vcap_data_t *data, u32 offset, u8 *val, u8 *msk, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++) {
        fa_vcap_key_set(data, offset + (count - i - 1) * 8, 8, val[i], msk[i]);
    }
}

static void fa_vcap_key_bit_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_bit_t fld)
{
    fa_vcap_key_set(data, offset, 1, fld == VTSS_VCAP_BIT_1 ? 1 : 0, fld == VTSS_VCAP_BIT_ANY ? 0 : 1);
}

static void fa_vcap_key_u3_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_u8_t *fld)
{
    fa_vcap_key_set(data, offset, 3, fld->value, fld->mask);
}

static void fa_vcap_key_u8_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_u8_t *fld)
{
    fa_vcap_key_set(data, offset, 8, fld->value, fld->mask);
}

static void fa_vcap_key_u16_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_u16_t *fld)
{
    fa_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 2);
}

static void fa_vcap_key_u32_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_u32_t *fld)
{
    fa_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 4);
}

static void fa_vcap_key_u40_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_u40_t *fld)
{
    fa_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 5);
}

static void fa_vcap_key_u48_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_u48_t *fld)
{
    fa_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 6);
}

static void fa_vcap_key_ipv4_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_ip_t *fld)
{
    fa_vcap_key_set(data, offset, 32, fld->value, fld->mask);
}

static void fa_vcap_key_u128_set(fa_vcap_data_t *data, u32 offset, vtss_vcap_u128_t *fld)
{
    fa_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 16);
}

static void fa_debug_action(fa_vcap_data_t *data, const char *name, u32 offs, u32 len)
{
    data->pr("%s:%u ", name, fa_act_get(data, offs, len));
}

static void fa_debug_action_ena(fa_vcap_data_t *data, const char *name, u32 offs, u32 offs_val, u32 len)
{
    vtss_debug_printf_t pr = data->pr;
    int                 i, length = VTSS_STRLEN(name);
    BOOL                enable = vtss_bs_bit_get(data->action, offs);

    for (i = 0; i < length; i++) {
        pr("%c", enable ? toupper(name[i]) : tolower(name[i]));
    }
    pr(":%u ", fa_act_get(data, offs_val, len));
}

static void fa_debug_bits(fa_vcap_data_t *data, const char *name, u32 offset, u32 len)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 i,j;
    int                 n = VTSS_STRLEN(name);

    pr("%s:", name);
    for (i = 0; i < len; i++) {
        j = (len - 1 - i);
        if (i != 0) {
            if (len > 65 && (j % 32) == 31) {
                pr("\n%-*s", n + 1, "");
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

/* VCAP set macros */
#define FA_ACT_SET(vcap, fld, val)           fa_act_set(data, vcap##_AO_##fld, vcap##_AL_##fld, val)
#define FA_ACT_ENA_SET(vcap, fld, ena, val)  fa_act_ena_set(data, vcap##_AO_##fld##_ENA, vcap##_AO_##fld##_VAL, vcap##_AL_##fld##_VAL, ena, val)

#define FA_DEBUG_ACT(vcap, name, fld)        fa_debug_action(data, name, vcap##_AO_##fld, vcap##_AL_##fld)
#define FA_DEBUG_ACT_ENA(vcap, name, f1, f2) fa_debug_action_ena(data, name, vcap##_AO_##f1, vcap##_AO_##f2, vcap##_AL_##f2)
#define FA_DEBUG_ACT_BITS(vcap, name, fld)   fa_debug_bits(data, name, vcap##_AO_##fld, vcap##_AL_##fld)
#define FA_DEBUG_BITS(vcap, name, fld)       fa_debug_bits(data, name, vcap##_KO_##fld, vcap##_KL_##fld)
#define FA_DEBUG_MAC(vcap, name, fld)        fa_debug_bits(data, name, vcap##_KO_##fld, 48)
#define FA_DEBUG_BITS_64(vcap, name, fld)    fa_debug_bits(data, name, vcap##_KO_##fld, 64)
#define FA_DEBUG_BITS_96(vcap, name, fld)    fa_debug_bits(data, name, vcap##_KO_##fld, 96)
#define FA_DEBUG_IPV6(vcap, name, fld)       fa_debug_bits(data, name, vcap##_KO_##fld, 128)

static const char *fa_vcap_tg_txt(u8 tg)
{
    return (tg == FA_VCAP_TG_X1 ? "X1" :
            tg == FA_VCAP_TG_X2 ? "X2" :
            tg == FA_VCAP_TG_X3 ? "X3" :
            tg == FA_VCAP_TG_X6 ? "X6" :
            tg == FA_VCAP_TG_X12 ? "X12" : "XX");
}

static vtss_rc fa_debug_vcap(vtss_state_t *vtss_state,
                             vtss_vcap_type_t type,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t *const info,
                             vtss_rc (* dbg)(vtss_state_t *vtss_state, fa_vcap_data_t *data))
{
    fa_vcap_type_t             bank = fa_vcap_type(type);
    const fa_vcap_type_props_t *props = &fa_vcap_type_info[bank];
    vtss_fa_vcap_reg_info_t    reg_info;
    fa_vcap_data_t             data;
    u32                        addr, tg, offset, blk, port, skip, rule_index = 0;
    vtss_port_no_t             port_no;
    int                        i, j, found, cnt;
    BOOL                       mpls_terse = info->has_action && info->action & 0x0010;
    BOOL                       hits_only  = info->has_action && info->action & 0x0040;

    if (bank == FA_VCAP_TYPE_NONE) {
        VTSS_E("unknown VCAP type");
        return VTSS_RC_ERROR;
    }

    vtss_debug_print_header(pr, props->name);

    VTSS_MEMSET(&reg_info, 0, sizeof(reg_info));
    reg_info.bank = bank;
    VTSS_RC(fa_vcap_reg_info_get(&reg_info));

    if (info->full) {
        vtss_fa_debug_reg_header(pr, "VCAP_CONST");
        vtss_fa_debug_reg(vtss_state, pr, reg_info.entry_width, "ENTRY_WIDTH");
        vtss_fa_debug_reg(vtss_state, pr, reg_info.entry_cnt, "ENTRY_CNT");
        vtss_fa_debug_reg(vtss_state, pr, reg_info.entry_swcnt, "ENTRY_SWCNT");
        vtss_fa_debug_reg(vtss_state, pr, reg_info.action_def_cnt, "ACTION_DEF_CNT");
        vtss_fa_debug_reg(vtss_state, pr, reg_info.action_width, "ACTION_WIDTH");
        vtss_fa_debug_reg(vtss_state, pr, reg_info.cnt_width, "CNT_WIDTH");
        pr("\n");
    }

    if (props->props->vcap_super && !mpls_terse) {
        vtss_fa_debug_reg_header(pr, "VCAP_SUPER");
        for (i = 0; i < FA_VCAP_SUPER_BLK_COUNT; i++) {
            REG_WR(VTSS_VCAP_SUPER_VCAP_CORE_IDX, i);
            vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_VCAP_SUPER_VCAP_CORE_MAP, i, "CORE_MAP");
        }
        pr("\n");
    }

    data.pr = pr;

    for (i = (props->props->action_count - 1); i >= 0; i--) {
        /* Leave critical region briefly */
        VTSS_EXIT_ENTER();

        addr = (i * props->props->sw_count);
        if (i >= props->props->entry_count && !mpls_terse) {
            /* Default action */
            offset = (i - props->props->entry_count);
            blk = (offset / VTSS_CHIP_PORTS_ALL);
            tg = FA_VCAP_TG_X3;
            if (props->props->vcap_super) {
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
                data.vcap_type = type;
                if (type == VTSS_VCAP_TYPE_ES0) {
                    tg = FA_VCAP_TG_X1;
                }
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

            if (fa_vcap_entry_cmd(vtss_state, &data, addr, tg, FA_VCAP_CMD_READ,
                                   FA_VCAP_SEL_ACTION | FA_VCAP_SEL_COUNTER) != VTSS_RC_OK)
                continue;

            if (hits_only && data.counter == 0)
                continue;

            /* Print default action */
            data.is_action = 1;
            pr("---------------------------------------------------------------\n");
            pr("%u-%u, %s[%u,%u]", addr, addr + fa_vcap_tg_count(tg) - 1, vtss_vcap_type_txt(data.vcap_type), blk & 1, port);
            if (port_no != VTSS_PORT_NO_NONE) {
                pr(" (port %u)", port_no);
            }
            pr("\n---------------------------------------------------------------\n");
            pr("%s ", fa_vcap_tg_txt(data.type));
            VTSS_RC(dbg(vtss_state, &data));
            pr("\n");

            if (info->clear) {
                data.counter = 0;
                VTSS_RC(fa_vcap_entry_cmd(vtss_state, &data, addr, 1, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_COUNTER));
            }
            continue;
        }

        /* Entry/mask */
        if (props->props->vcap_super) {
            blk = ((props->props->entry_count - i - 1)/VTSS_VCAP_SUPER_ROW_CNT);
            data.vcap_type = vtss_state->vcap.vcap_super.block_type[blk];
        } else {
            data.vcap_type = type;
        }

        /* Skip other VCAP types */
        if (type != data.vcap_type)
            continue;

        /* Read each subword until a valid TG is found, then read whole entry */
        found = 0;
        cnt = 1;
        for (j = (props->props->sw_count - 1); j >= 0; ) {
            addr = (i * props->props->sw_count + j);

            if (fa_vcap_entry_cmd(vtss_state, &data, addr, FA_VCAP_TG_X1, FA_VCAP_CMD_READ, FA_VCAP_SEL_ENTRY) != VTSS_RC_OK ||
                data.tg == FA_VCAP_TG_NONE ||
                fa_vcap_entry_cmd(vtss_state, &data, addr, data.tg, FA_VCAP_CMD_READ, FA_VCAP_SEL_ALL) != VTSS_RC_OK) {
                j -= cnt;
                continue;
            }
            cnt = fa_vcap_tg_count(data.tg);
            j -= cnt;
            found = 1;

            if (hits_only && data.counter == 0)
                continue;

            /* Print entry */
            data.is_action = 0;
            pr("---------------------------------------------------------------\n");
            pr("%u-%u (rule %u): ", addr, addr + fa_vcap_tg_count(data.tg) - 1, rule_index);
            pr("\n---------------------------------------------------------------\n");
            pr("%s ", fa_vcap_tg_txt(data.tg));
            rule_index++;
            VTSS_RC(dbg(vtss_state, &data));
            pr("\n");

            /* Print action */
            data.is_action = 1;
            pr("%s ", fa_vcap_tg_txt(data.type));
            VTSS_RC(dbg(vtss_state, &data));
            pr("\n");

            if (info->clear) {
                data.counter = 0;
                VTSS_RC(fa_vcap_entry_cmd(vtss_state, &data, addr, FA_VCAP_TG_X1, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_COUNTER));
            }
        }
        if (!found && !info->full) {
            break;
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
} fa_clm_key_info_t;

static u32 fa_u8_to_u32(u8 *p)
{
    return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static void fa_u32_to_u8(u8 *p, u32 value)
{
    u32 i;

    for (i = 0; i < 4; i++) {
        p[i] = (value >> (24 - i*8));
    }
}

static void fa_clm_range_update(vtss_vcap_vr_type_t type, u32 range, fa_clm_key_info_t *info)
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

static void fa_clm_l4port_update(vtss_vcap_vr_t *vr, u32 range, vtss_vcap_u16_t *val, fa_clm_key_info_t *info)
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
        fa_clm_range_update(vr->type, range, info);
    }
    if (l4_used && info->ip4 == VTSS_VCAP_BIT_1) {
        /* L4 used, ignore IPv4 fragments and options */
        info->fragment = VTSS_VCAP_BIT_0;
        info->options = VTSS_VCAP_BIT_0;
    }
}

static void fa_clm_tpid_set(fa_vcap_data_t *data, u32 offset, u32 len, vtss_is1_tag_t *tag)
{
    /* Match all frames by default */
    u32 value = 0;
    u32 mask = 0;

    if (tag->tagged == VTSS_VCAP_BIT_0) {
        /* Match untagged */
        mask = 0x7;
    } else if (tag->tagged == VTSS_VCAP_BIT_1) {
        if (tag->s_tag == VTSS_VCAP_BIT_1) {
            /* Match S-tagged or S-custom (CUSTOM_1) tagged */
            value = 4;
            mask = 0x6;
        } else if (tag->s_tag == VTSS_VCAP_BIT_0) {
            /* Match C-tagged */
            value = 1;
            mask = 0x7;
        } else {
            /* Matching any C/S/S-custom tagged frames is not possible, so we match everything.
               Matching a specific VID may be done to avoid matching untagged and priority-tagged frames. */
        }
    }
    fa_vcap_key_set(data, offset, len, value, mask);
}

static void fa_clm_qos_action_update(vtss_state_t *vtss_state,
                                     fa_vcap_data_t *data, vtss_qos_ingress_map_id_t map_id, BOOL inner_tag)
{
    u32 sel = 0, idx = 0, key = 0, ix;

    if (map_id < VTSS_QOS_INGRESS_MAP_IDS &&
        (ix = vtss_state->qos.imap.id.entry[map_id].ix) < VTSS_QOS_INGRESS_MAP_ROWS) {
        sel = 1; /* QoS ingress map table lookup #0 */
        idx = ix;
        key = vtss_fa_imap_key2clm(vtss_state->qos.imap.ix[0].entry[idx].key, inner_tag);
    }

    if (data->tg == FA_VCAP_TG_X1) {
        // TBD_MPLS: MLBS
        if (map_id == VTSS_QOS_INGRESS_MAP_ID_NONE) {
            FA_ACT_SET(CLM, X1_MAP_LOOKUP_SEL, 0);
        } else {
            // Key is hardwired to TC.
            // The chip will calculate the QoS map index as (MSB..LSB): DP_ENA:1 << 8 | QOS_VAL:3 << 5 | QOS_ENA:1 << 4 | COSID_VAL:3 << 1 | COSID_ENA:1.
            FA_ACT_SET(CLM, X1_MAP_LOOKUP_SEL, sel);
            FA_ACT_SET(CLM, X1_COSID_ENA, (idx >> 0) & 0x01);
            FA_ACT_SET(CLM, X1_COSID_VAL, (idx >> 1) & 0x07);
            FA_ACT_SET(CLM, X1_QOS_ENA,   (idx >> 4) & 0x01);
            FA_ACT_SET(CLM, X1_QOS_VAL,   (idx >> 5) & 0x07);
            FA_ACT_SET(CLM, X1_DP_VAL,    (idx >> 8) & 0x01);
        }
    } else if (data->tg == FA_VCAP_TG_X2) {
        FA_ACT_SET(CLM, CLASSIFICATION_MAP_LOOKUP_SEL, sel);
        FA_ACT_SET(CLM, CLASSIFICATION_MAP_IDX, idx);
        FA_ACT_SET(CLM, CLASSIFICATION_MAP_KEY, key);
    } else {
        FA_ACT_SET(CLM, FULL_MAP_LOOKUP_SEL, sel);
        FA_ACT_SET(CLM, FULL_MAP_IDX, idx);
        FA_ACT_SET(CLM, FULL_MAP_KEY, key);
    }
}

static void fa_clm_action_update(vtss_state_t *vtss_state, fa_vcap_data_t *data, vtss_is1_data_t *is1)
{
    BOOL                      inner_tag = (is1->flags & VTSS_IS1_FLAG_MAP_INNER ? 1 : 0);
    vtss_qos_ingress_map_id_t map_id = (is1->flags & VTSS_IS1_FLAG_MAP_ID ? is1->map_id : VTSS_QOS_INGRESS_MAP_ID_NONE);

    fa_clm_qos_action_update(vtss_state, data, map_id, inner_tag);
}

static void fa_clm_port_sel_update(fa_vcap_data_t *data, vtss_is1_key_t *key)
{
    VTSS_D("port_hit: %u, looped: %u,  masqueraded: %u", key->port_hit, key->looped, key->masqueraded);

    /* If no specific match type (port_hit - masqueraded - looped) is selected, matching is done on port and masqueraded frames */
    /* If a specific match type (port_hit - masqueraded - looped) is selected, matching is done on port or masqueraded or looped frames */
    u32 value = key->port_hit ? 0 : key->looped ? 1 : 2;
    u32 mask = (key->port_hit || key->masqueraded || key->looped) ? 0x03 : 0x01;

    if (data->tg == FA_VCAP_TG_X12) {
        fa_vcap_key_set(data, CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_SEL, CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_SEL, value, mask);
    } else {
        fa_vcap_key_set(data, CLM_KO_X6_IGR_PORT_MASK_SEL, CLM_KL_X6_IGR_PORT_MASK_SEL, value, mask);
    }
}

static vtss_rc fa_clm_entry_add(vtss_state_t *vtss_state,
                                vtss_vcap_type_t type, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    fa_vcap_data_t         fa_data, *data = &fa_data;
    u32                    addr, port, oam, vid_sel = 0, vid_val = 0, gvid_sel = 0, pag_mask = 0, pag_val = 0;
    u32                    x6_type = CLM_X6_TYPE_NORMAL;
    u32                    x6_mask = VTSS_BITMASK(CLM_KL_X6_TYPE);
    vtss_is1_data_t        *is1 = &vcap_data->u.is1;
    vtss_is1_key_t         *key = &is1->entry->key;
    vtss_is1_tag_t         *tag;
    vtss_is1_action_t      *action = &is1->entry->action;
    vtss_is1_frame_etype_t *etype = &key->frame.etype;
    vtss_is1_frame_llc_t   *llc = &key->frame.llc;
    vtss_is1_frame_snap_t  *snap = &key->frame.snap;
    vtss_is1_frame_ipv4_t  *ipv4 = &key->frame.ipv4;
    vtss_is1_frame_ipv6_t  *ipv6 = &key->frame.ipv6;
    vtss_vcap_u8_t         *proto = NULL, g_idx_sel;
    vtss_vcap_vid_t        g_idx = key->g_idx;
    vtss_vcap_vr_t         *dscp, *sport, *dport;
    fa_clm_key_info_t      info;
    BOOL                   sipv6_copy = 0, ip = 0;
    vtss_vcap_bit_t        first, y1731 = VTSS_VCAP_BIT_ANY;
    vtss_port_no_t         port_no;

    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = type;

    if (key->type == VTSS_IS1_TYPE_MPLS_MLL) {
        data->tg   = FA_VCAP_TG_X3;
        data->type = FA_VCAP_TG_X3;
    } else if (key->type == VTSS_IS1_TYPE_MPLS_MLBS) {
        data->tg   = FA_VCAP_TG_X1;
        data->type = FA_VCAP_TG_X1;
    } else if (key->key_type == VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR) {
        data->tg   = FA_VCAP_TG_X12;
        data->type = FA_VCAP_TG_X3;
    } else if (key->key_type == VTSS_VCAP_KEY_TYPE_DOUBLE_TAG) {
        data->tg   = FA_VCAP_TG_X2;
        data->type = FA_VCAP_TG_X2;
    } else {
        data->tg   = FA_VCAP_TG_X6;
        data->type = FA_VCAP_TG_X3;
    }

    addr = fa_vcap_entry_addr(vtss_state, type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u", vtss_vcap_type_txt(type), idx->row, idx->col, addr);

    /* Setup key fields */
    VTSS_MEMSET(&info, 0, sizeof(info));
    switch (key->type) {
    case VTSS_IS1_TYPE_ANY:
        if (key->key_type == VTSS_VCAP_KEY_TYPE_IP_ADDR) {
            x6_mask = 0;
        }
        break;
    case VTSS_IS1_TYPE_ETYPE:
        info.etype_len = VTSS_VCAP_BIT_1;
        info.ip_snap = VTSS_VCAP_BIT_0;
        info.ip4 = VTSS_VCAP_BIT_0;
        info.etype = etype->etype;
        info.sip.value = fa_u8_to_u32(etype->data.value);
        info.sip.mask = fa_u8_to_u32(etype->data.mask);
        sipv6_copy = 1;
        if (etype->etype.value[0] == 0x89 && etype->etype.value[1] == 0x02 &&
            etype->etype.mask[0] == 0xff && etype->etype.mask[1] == 0xff) {
            /* Match OAM frame */
            y1731 = VTSS_VCAP_BIT_1;
            info.tcp_udp = VTSS_VCAP_BIT_1; /* This must be set to indicate Y.1731 frame */
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
        info.sip.value = fa_u8_to_u32(&llc->data.value[2]);
        info.sip.mask = fa_u8_to_u32(&llc->data.mask[2]);
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
        info.sip.value = fa_u8_to_u32(&snap->data.value[2]);
        info.sip.mask = fa_u8_to_u32(&snap->data.mask[2]);
        sipv6_copy = 1;
        break;
    case VTSS_IS1_TYPE_IPV4:
    case VTSS_IS1_TYPE_IPV6:
        ip = 1;
        if (key->key_type == VTSS_VCAP_KEY_TYPE_IP_ADDR) {
            x6_type = CLM_X6_TYPE_NORMAL_5TUPLE_IP4;
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
            fa_u32_to_u8(&info.sipv6.value[12], ipv4->sip.value);
            fa_u32_to_u8(&info.sipv6.mask[12], ipv4->sip.mask);
            fa_u32_to_u8(&info.dipv6.value[12], ipv4->dip.value);
            fa_u32_to_u8(&info.dipv6.mask[12], ipv4->dip.mask);
            sport = &ipv4->sport;
            dport = &ipv4->dport;
        } else {
            info.ip4 = VTSS_VCAP_BIT_0;
            info.ip_mc = ipv6->ip_mc;
            proto = &ipv6->proto;
            dscp = &ipv6->dscp;
            info.sip.value = fa_u8_to_u32(&ipv6->sip.value[12]);
            info.sip.mask = fa_u8_to_u32(&ipv6->sip.mask[12]);
            info.dip.value = fa_u8_to_u32(&ipv6->dip.value[12]);
            info.dip.mask = fa_u8_to_u32(&ipv6->dip.mask[12]);
            info.sipv6 = ipv6->sip;
            info.dipv6 = ipv6->dip;
            sport = &ipv6->sport;
            dport = &ipv6->dport;
        }
        if (dscp->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            info.dscp.value = dscp->vr.v.value;
            info.dscp.mask = dscp->vr.v.mask;
        }
        fa_clm_range_update(dscp->type, is1->dscp_range, &info);
        if (vtss_vcap_udp_tcp_rule(proto)) {
            /* UDP/TCP */
            info.tcp_udp = VTSS_VCAP_BIT_1;
            info.tcp = (proto->value == 6 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            fa_clm_l4port_update(dport, is1->dport_range, &info.etype, &info);
            fa_clm_l4port_update(sport, is1->sport_range, &info.sport, &info);
        } else if (proto->mask == 0xff) {
            /* Not UDP/TCP */
            info.tcp_udp = VTSS_VCAP_BIT_0;
            info.etype.value[1] = proto->value;
            info.etype.mask[1] = proto->mask;
        }
        break;
    case VTSS_IS1_TYPE_MPLS_MLL:
    case VTSS_IS1_TYPE_MPLS_MLBS:
        break;
    default:
        VTSS_E("illegal frame type");
        return VTSS_RC_ERROR;
    }

    if (sipv6_copy) {
        /* Copy ETYPE/LLC/SNAP data to IPv6 SIP field */
        fa_u32_to_u8(&info.sipv6.value[0], info.sip.value);
        fa_u32_to_u8(&info.sipv6.mask[0], info.sip.mask);
    }

    /* Lookup 0/1. Other values mean wildcard */
    first = (is1->lookup == 0 ? VTSS_VCAP_BIT_1 : (is1->lookup == 1 ? VTSS_VCAP_BIT_0 : VTSS_VCAP_BIT_ANY));

    if (g_idx.mask) {
        g_idx_sel.value = 1; /* Select G_IDX */
        g_idx_sel.mask = VTSS_BITMASK(CLM_KL_X1_G_IDX_SEL);
    } else {
        g_idx_sel.value = 0;
        g_idx_sel.mask = 0;
    }

    if (data->tg == FA_VCAP_TG_X1) {
        /* X1 key: SGL_MLBS */
        fa_vcap_key_set(data, CLM_KO_X1_TYPE, CLM_KL_X1_TYPE, CLM_X1_TYPE_SGL_MLBS, VTSS_BITMASK(CLM_KL_X1_TYPE));
        fa_vcap_key_bit_set(data, CLM_KO_X1_FIRST, first);
        fa_vcap_key_set(data, CLM_KO_X1_G_IDX_SEL, CLM_KL_X1_G_IDX_SEL, g_idx_sel.value, g_idx_sel.mask);
        fa_vcap_key_set(data, CLM_KO_X1_G_IDX, CLM_KL_X1_G_IDX, g_idx.value, g_idx.mask);
        if (key->frame.mlbs.label != 0) {
            fa_vcap_key_set(data, CLM_KO_SGL_MLBS_LBL0, CLM_KL_SGL_MLBS_LBL0, key->frame.mlbs.label, VTSS_BITMASK(CLM_KL_SGL_MLBS_LBL0));
        }
        fa_vcap_key_bit_set(data, CLM_KO_SGL_MLBS_SBIT0, key->frame.mlbs.s_bit);
        fa_vcap_key_bit_set(data, CLM_KO_SGL_MLBS_TTL0_EXPIRY, key->frame.mlbs.ttl_expiry);
    } else if (data->tg == FA_VCAP_TG_X2) {
        /* X2 key: TRI_VID */
        fa_vcap_key_set(data, CLM_KO_X2_TYPE, CLM_KL_X2_TYPE, CLM_X2_TYPE_TRI_VID, VTSS_BITMASK(CLM_KL_X2_TYPE));
        fa_vcap_key_bit_set(data, CLM_KO_X2_FIRST, first);
        if ((port_no = vtss_cmn_first_port_no_get(vtss_state, key->port_list)) != VTSS_PORT_NO_NONE || key->cpu_port) {
            /* Match ingress port */
            port = (key->cpu_port ? VTSS_CHIP_PORT_CPU : VTSS_CHIP_PORT(port_no));
            fa_vcap_key_set(data, CLM_KO_X2_IGR_PORT, CLM_KL_X2_IGR_PORT, port, VTSS_BITMASK(CLM_KL_X2_IGR_PORT));
        }
        fa_vcap_key_set(data, CLM_KO_TRI_VID_G_IDX_SEL, CLM_KL_TRI_VID_G_IDX_SEL, g_idx_sel.value, g_idx_sel.mask);
        fa_vcap_key_set(data, CLM_KO_TRI_VID_G_IDX, CLM_KL_TRI_VID_G_IDX, g_idx.value, g_idx.mask);

        /* Outer tag */
        tag = &key->tag;
        fa_clm_tpid_set(data, CLM_KO_TRI_VID_TPID0, CLM_KL_TRI_VID_TPID0, tag);
        fa_vcap_key_u3_set(data, CLM_KO_TRI_VID_PCP0, &tag->pcp);
        fa_vcap_key_bit_set(data, CLM_KO_TRI_VID_DEI0, tag->dei);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            fa_vcap_key_set(data, CLM_KO_TRI_VID_VID0, CLM_KL_TRI_VID_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);
        }
        fa_clm_range_update(tag->vid.type, is1->vid_range, &info);
        fa_vcap_key_u8_set(data, CLM_KO_TRI_VID_L4_RNG, &info.range);

        /* Inner tag */
        tag = &key->inner_tag;
        fa_clm_tpid_set(data, CLM_KO_TRI_VID_TPID1, CLM_KL_TRI_VID_TPID1, tag);
        fa_vcap_key_u3_set(data, CLM_KO_TRI_VID_PCP1, &tag->pcp);
        fa_vcap_key_bit_set(data, CLM_KO_TRI_VID_DEI1, tag->dei);
        fa_vcap_key_set(data, CLM_KO_TRI_VID_VID1, CLM_KL_TRI_VID_VID1, tag->vid.vr.v.value, tag->vid.vr.v.mask);

        /* Y1731 entry with MEG level */
        fa_vcap_key_bit_set(data, CLM_KO_TRI_VID_OAM_Y1731, y1731);
        fa_vcap_key_set(data, CLM_KO_TRI_VID_OAM_MEL_FLAGS, CLM_KL_TRI_VID_OAM_MEL_FLAGS, etype->mel.value, etype->mel.mask);
    } else if (data->tg == FA_VCAP_TG_X3) {
        /* X3 key: MLL */
        fa_vcap_key_set(data, CLM_KO_X3_TYPE, CLM_KL_X3_TYPE, CLM_X3_TYPE_MLL, VTSS_BITMASK(CLM_KL_X3_TYPE));
        fa_vcap_key_bit_set(data, CLM_KO_X3_FIRST, first);
        fa_vcap_key_set(data, CLM_KO_X3_G_IDX_SEL, CLM_KL_X3_G_IDX_SEL, g_idx_sel.value, g_idx_sel.mask);
        fa_vcap_key_set(data, CLM_KO_X3_G_IDX, CLM_KL_X3_G_IDX, g_idx.value, g_idx.mask);
        if ((port_no = vtss_cmn_first_port_no_get(vtss_state, key->port_list)) != VTSS_PORT_NO_NONE) {
            port = VTSS_CHIP_PORT(port_no);
            fa_vcap_key_set(data, CLM_KO_MLL_IGR_PORT, CLM_KL_MLL_IGR_PORT, port, VTSS_BITMASK(CLM_KL_MLL_IGR_PORT));
        }

        tag = &key->tag;
        fa_clm_tpid_set(data, CLM_KO_MLL_TPID0, CLM_KL_MLL_TPID0, tag);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            fa_vcap_key_set(data, CLM_KO_MLL_VID0, CLM_KL_MLL_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);
        }
        fa_clm_range_update(tag->vid.type, is1->vid_range, &info);
        fa_vcap_key_u8_set(data, CLM_KO_MLL_L4_RNG, &info.range);

        fa_vcap_key_u48_set(data, CLM_KO_MLL_L2_DMAC_0, &key->mac.dmac);
        fa_vcap_key_u48_set(data, CLM_KO_MLL_L2_SMAC_0, &key->mac.smac);
        fa_vcap_key_set(data, CLM_KO_MLL_ETYPE_MPLS, CLM_KL_MLL_ETYPE_MPLS, key->frame.mll.upstream ? 2 : 1, VTSS_BITMASK(CLM_KL_MLL_ETYPE_MPLS));
    } else if (data->tg == FA_VCAP_TG_X6) {
        /* X6 key */
        fa_vcap_key_set(data, CLM_KO_X6_TYPE, CLM_KL_X6_TYPE, x6_type, x6_mask);
        fa_vcap_key_bit_set(data, CLM_KO_X6_FIRST, first);
        fa_vcap_key_set(data, CLM_KO_X6_G_IDX_SEL, CLM_KL_X6_G_IDX_SEL, g_idx_sel.value, g_idx_sel.mask);
        fa_vcap_key_set(data, CLM_KO_X6_G_IDX, CLM_KL_X6_G_IDX, g_idx.value, g_idx.mask);

        fa_clm_port_sel_update(data, key);
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (key->port_list[port_no] == 0) {
                port = VTSS_CHIP_PORT(port_no);
                fa_vcap_key_bit_set(data, CLM_KO_X6_IGR_PORT_MASK_0 + port, VTSS_VCAP_BIT_0);
            }
        }
        fa_vcap_key_bit_set(data, CLM_KO_X6_L2_MC, key->mac.dmac_mc);
        fa_vcap_key_bit_set(data, CLM_KO_X6_L2_BC, key->mac.dmac_bc);

        /* Outer tag */
        tag = &key->tag;
        fa_clm_tpid_set(data, CLM_KO_X6_TPID0, CLM_KL_X6_TPID0, tag);
        fa_vcap_key_u3_set(data, CLM_KO_X6_PCP0, &tag->pcp);
        fa_vcap_key_bit_set(data, CLM_KO_X6_DEI0, tag->dei);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            fa_vcap_key_set(data, CLM_KO_X6_VID0, CLM_KL_X6_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);
        }
        fa_clm_range_update(tag->vid.type, is1->vid_range, &info);

        /* Inner tag */
        tag = &key->inner_tag;
        fa_clm_tpid_set(data, CLM_KO_X6_TPID1, CLM_KL_X6_TPID1, tag);
        fa_vcap_key_u3_set(data, CLM_KO_X6_PCP1, &tag->pcp);
        fa_vcap_key_bit_set(data, CLM_KO_X6_DEI1, tag->dei);
        fa_vcap_key_set(data, CLM_KO_X6_VID1, CLM_KL_X6_VID1, tag->vid.vr.v.value, tag->vid.vr.v.mask);

        if (x6_mask == 0) {
            /* Match any frame */
        } else if (x6_type == CLM_X6_TYPE_NORMAL) {
            /* Match source or destination addresses */
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_DST_ENTRY, key->dmac_dip ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            fa_vcap_key_u48_set(data, CLM_KO_NORMAL_L2_SMAC_0, key->dmac_dip ? &key->mac.dmac : &key->mac.smac);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_IP_MC, info.ip_mc);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_ETYPE_LEN, info.etype_len);
            fa_vcap_key_u16_set(data, CLM_KO_NORMAL_ETYPE, &info.etype);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_IP_SNAP, info.ip_snap);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_IP4, info.ip4);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_L3_FRAGMENT_TYPE, info.fragment);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_L3_OPTIONS, info.options);
            fa_vcap_key_set(data, CLM_KO_NORMAL_L3_DSCP, CLM_KL_NORMAL_L3_DSCP, info.dscp.value, info.dscp.mask);
            fa_vcap_key_ipv4_set(data, CLM_KO_NORMAL_L3_IP4_SIP, key->dmac_dip && ip ? &info.dip : &info.sip);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_TCP_UDP, info.tcp_udp);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_TCP, info.tcp);
            fa_vcap_key_u16_set(data, CLM_KO_NORMAL_L4_SPORT, &info.sport);
            fa_vcap_key_u8_set(data, CLM_KO_NORMAL_L4_RNG, &info.range);
        } else {
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_5TUPLE_IP4_IP_MC, info.ip_mc);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_5TUPLE_IP4_IP4, info.ip4);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_5TUPLE_IP4_L3_FRAGMENT_TYPE, info.fragment);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_5TUPLE_IP4_L3_OPTIONS, info.options);
            fa_vcap_key_set(data, CLM_KO_NORMAL_5TUPLE_IP4_L3_DSCP, CLM_KL_NORMAL_5TUPLE_IP4_L3_DSCP, info.dscp.value, info.dscp.mask);
            fa_vcap_key_ipv4_set(data, CLM_KO_NORMAL_5TUPLE_IP4_L3_IP4_DIP, &info.dip);
            fa_vcap_key_ipv4_set(data, CLM_KO_NORMAL_5TUPLE_IP4_L3_IP4_SIP, &info.sip);
            fa_vcap_key_u8_set(data, CLM_KO_NORMAL_5TUPLE_IP4_L3_IP_PROTO, proto);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_5TUPLE_IP4_TCP_UDP, info.tcp_udp);
            fa_vcap_key_bit_set(data, CLM_KO_NORMAL_5TUPLE_IP4_TCP, info.tcp);
            fa_vcap_key_u8_set(data, CLM_KO_NORMAL_5TUPLE_IP4_L4_RNG, &info.range);
        }
    } else {
        /* X12 key */
        fa_vcap_key_set(data, CLM_KO_X12_TYPE, CLM_KL_X12_TYPE, CLM_X12_TYPE_NORMAL_7TUPLE, VTSS_BITMASK(CLM_KL_X12_TYPE));
        fa_vcap_key_bit_set(data, CLM_KO_X12_FIRST, first);
        fa_vcap_key_set(data, CLM_KO_X12_G_IDX_SEL, CLM_KL_X12_G_IDX_SEL, g_idx_sel.value, g_idx_sel.mask);
        fa_vcap_key_set(data, CLM_KO_X12_G_IDX, CLM_KL_X12_G_IDX, g_idx.value, g_idx.mask);
        fa_clm_port_sel_update(data, key);
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (key->port_list[port_no] == 0) {
                port = VTSS_CHIP_PORT(port_no);
                fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_0 + port, VTSS_VCAP_BIT_0);
            }
        }
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_L2_MC, key->mac.dmac_mc);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_L2_BC, key->mac.dmac_bc);

        /* Outer tag */
        tag = &key->tag;
        fa_clm_tpid_set(data, CLM_KO_NORMAL_7TUPLE_TPID0, CLM_KL_NORMAL_7TUPLE_TPID0, tag);
        fa_vcap_key_u3_set(data, CLM_KO_NORMAL_7TUPLE_PCP0, &tag->pcp);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_DEI0, tag->dei);
        if (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            fa_vcap_key_set(data, CLM_KO_NORMAL_7TUPLE_VID0, CLM_KL_NORMAL_7TUPLE_VID0, tag->vid.vr.v.value, tag->vid.vr.v.mask);
        }
        fa_clm_range_update(tag->vid.type, is1->vid_range, &info);

        /* Inner tag */
        tag = &key->inner_tag;
        fa_clm_tpid_set(data, CLM_KO_NORMAL_7TUPLE_TPID1, CLM_KL_NORMAL_7TUPLE_TPID1, tag);
        fa_vcap_key_u3_set(data, CLM_KO_NORMAL_7TUPLE_PCP1, &tag->pcp);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_DEI1, tag->dei);
        fa_vcap_key_set(data, CLM_KO_NORMAL_7TUPLE_VID1, CLM_KL_NORMAL_7TUPLE_VID1, tag->vid.vr.v.value, tag->vid.vr.v.mask);

        /* Match source and destination addresses */
        fa_vcap_key_u48_set(data, CLM_KO_NORMAL_7TUPLE_L2_DMAC_0, &key->mac.dmac);
        fa_vcap_key_u48_set(data, CLM_KO_NORMAL_7TUPLE_L2_SMAC_0, &key->mac.smac);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_IP_MC, info.ip_mc);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_ETYPE_LEN, info.etype_len);
        fa_vcap_key_u16_set(data, CLM_KO_NORMAL_7TUPLE_ETYPE, &info.etype);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_IP_SNAP, info.ip_snap);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_IP4, info.ip4);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_L3_FRAGMENT_TYPE, info.fragment);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_L3_OPTIONS, info.options);
        fa_vcap_key_set(data, CLM_KO_NORMAL_7TUPLE_L3_DSCP, CLM_KL_NORMAL_L3_DSCP, info.dscp.value, info.dscp.mask);
        fa_vcap_key_u128_set(data, CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_0, &info.sipv6);
        fa_vcap_key_u128_set(data, CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_0, &info.dipv6);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_TCP_UDP, info.tcp_udp);
        fa_vcap_key_bit_set(data, CLM_KO_NORMAL_7TUPLE_TCP, info.tcp);
        fa_vcap_key_u16_set(data, CLM_KO_NORMAL_7TUPLE_L4_SPORT, &info.sport);
        fa_vcap_key_u8_set(data, CLM_KO_NORMAL_7TUPLE_L4_RNG, &info.range);
    }

    /* Setup action fields */
    if (action->vid != VTSS_VID_NULL) {
        vid_sel = 2;
        vid_val = action->vid;
    }
    if (action->gvid == VTSS_VID_SECOND) {
        gvid_sel = 4;
    } else if (action->gvid == VTSS_VID_THIRD) {
        gvid_sel = 5;
    }
    if (action->pag_enable) {
        pag_mask = VTSS_BITMASK(CLM_AL_CLASSIFICATION_PAG_OVERRIDE_MASK);
        pag_val = action->pag;
    }
    oam = (action->oam_detect == VTSS_OAM_DETECT_UNTAGGED ? 2 :
           action->oam_detect == VTSS_OAM_DETECT_SINGLE_TAGGED ? 3 :
           action->oam_detect == VTSS_OAM_DETECT_DOUBLE_TAGGED ? 4 :
           action->oam_detect == VTSS_OAM_DETECT_TRIPLE_TAGGED ? 5 : 0);
    if (data->type == FA_VCAP_TG_X1) {
        /* X1 action: MLBS_REDUCED */
        /* TBD_MPLS */
    } else if (data->type == FA_VCAP_TG_X2) {
        /* X2 action: CLASSIFICATION */
        FA_ACT_SET(CLM, X2_TYPE, CLM_X2_TYPE_CLASSIFICATION);
        FA_ACT_ENA_SET(CLM, CLASSIFICATION_DSCP, action->dscp_enable, action->dscp);
        FA_ACT_ENA_SET(CLM, CLASSIFICATION_QOS, action->prio_enable, action->prio);
        FA_ACT_ENA_SET(CLM, CLASSIFICATION_DP, action->dp_enable, action->dp);
        FA_ACT_ENA_SET(CLM, CLASSIFICATION_DEI, action->dei_enable, action->dei);
        FA_ACT_ENA_SET(CLM, CLASSIFICATION_PCP, action->pcp_enable, action->pcp);
        FA_ACT_SET(CLM, CLASSIFICATION_GVID_ADD_REPLACE_SEL, gvid_sel);
        FA_ACT_SET(CLM, CLASSIFICATION_XVID_ADD_REPLACE_SEL, vid_sel);
        FA_ACT_SET(CLM, CLASSIFICATION_VID_VAL, vid_val);
        FA_ACT_SET(CLM, CLASSIFICATION_VLAN_POP_CNT_ENA, action->pop_enable);
        FA_ACT_SET(CLM, CLASSIFICATION_VLAN_POP_CNT, action->pop);
        FA_ACT_SET(CLM, CLASSIFICATION_ISDX_ADD_REPLACE_SEL, action->isdx_enable);
        FA_ACT_SET(CLM, CLASSIFICATION_ISDX_VAL, action->isdx_enable ? action->isdx : 0);
        FA_ACT_SET(CLM, CLASSIFICATION_RT_SEL, action->rt_sel);
        FA_ACT_SET(CLM, CLASSIFICATION_FWD_DIS, action->fwd_disable);
        FA_ACT_SET(CLM, CLASSIFICATION_MIP_SEL, action->mip_enable ? 1 : 0);
        FA_ACT_SET(CLM, CLASSIFICATION_OAM_Y1731_SEL, oam);
        FA_ACT_SET(CLM, CLASSIFICATION_PAG_OVERRIDE_MASK, pag_mask);
        FA_ACT_SET(CLM, CLASSIFICATION_PAG_VAL, pag_val);
        FA_ACT_SET(CLM, CLASSIFICATION_PIPELINE_FORCE_ENA, action->pipe_enable);
        FA_ACT_SET(CLM, CLASSIFICATION_PIPELINE_ACT_SEL, action->pipe_sel);
        FA_ACT_SET(CLM, CLASSIFICATION_PIPELINE_PT, action->pipe_pt);
        FA_ACT_SET(CLM, CLASSIFICATION_NXT_KEY_TYPE, action->nxt_key_type);
        FA_ACT_SET(CLM, CLASSIFICATION_NXT_IDX_CTRL, action->nxt_idx_enable ? 1 : 0);
        FA_ACT_SET(CLM, CLASSIFICATION_NXT_IDX, action->nxt_idx);
    } else {
        /* X3 action: FULL */
        FA_ACT_ENA_SET(CLM, FULL_DSCP, action->dscp_enable, action->dscp);
        FA_ACT_ENA_SET(CLM, FULL_QOS, action->prio_enable, action->prio);
        FA_ACT_ENA_SET(CLM, FULL_DP, action->dp_enable, action->dp);
        FA_ACT_ENA_SET(CLM, FULL_DEI, action->dei_enable, action->dei);
        FA_ACT_ENA_SET(CLM, FULL_PCP, action->pcp_enable, action->pcp);
        FA_ACT_SET(CLM, FULL_GVID_ADD_REPLACE_SEL, gvid_sel);
        FA_ACT_SET(CLM, FULL_XVID_ADD_REPLACE_SEL, vid_sel);
        FA_ACT_SET(CLM, FULL_VID_VAL, vid_val);
        FA_ACT_SET(CLM, FULL_VLAN_POP_CNT_ENA, action->pop_enable);
        FA_ACT_SET(CLM, FULL_VLAN_POP_CNT, action->pop);
        FA_ACT_SET(CLM, FULL_ISDX_ADD_REPLACE_SEL, action->isdx_enable);
        FA_ACT_SET(CLM, FULL_ISDX_VAL, action->isdx_enable ? action->isdx : 0);
        FA_ACT_SET(CLM, FULL_MASK_MODE, action->fwd_disable ? 2 : 0); // REPLACE_PGID
        FA_ACT_SET(CLM, FULL_RT_SEL, action->rt_sel);
        FA_ACT_SET(CLM, FULL_CPU_Q, action->cpu_queue);
        FA_ACT_SET(CLM, FULL_MIP_SEL, action->mip_enable ? 1 : 0);
        FA_ACT_SET(CLM, FULL_OAM_Y1731_SEL, oam);
        FA_ACT_SET(CLM, FULL_PAG_OVERRIDE_MASK, pag_mask);
        FA_ACT_SET(CLM, FULL_PAG_VAL, pag_val);
        FA_ACT_SET(CLM, FULL_PIPELINE_FORCE_ENA, action->pipe_enable);
        FA_ACT_SET(CLM, FULL_PIPELINE_ACT_SEL, action->pipe_sel);
        FA_ACT_SET(CLM, FULL_PIPELINE_PT, action->pipe_pt);
        FA_ACT_SET(CLM, FULL_NXT_KEY_TYPE, action->nxt_key_type);
        FA_ACT_SET(CLM, FULL_NXT_IDX_CTRL, action->nxt_idx_enable ? 1 : 0);
        FA_ACT_SET(CLM, FULL_NXT_IDX, action->nxt_idx);

        /* TBD_MPLS */
        FA_ACT_SET(CLM, FULL_FWD_TYPE, action->mpls_fwd_type);
        FA_ACT_SET(CLM, FULL_MPLS_OAM_TYPE, action->mpls_oam_detect);
        FA_ACT_SET(CLM, FULL_MPLS_MEP_ENA, action->mpls_mep_enable);
        FA_ACT_SET(CLM, FULL_MPLS_MIP_ENA, action->mpls_mip_enable);
        FA_ACT_SET(CLM, FULL_MPLS_OAM_FLAVOR, action->mpls_oam_flavor_1);
        FA_ACT_SET(CLM, FULL_RSVD_LBL_VAL, action->mpls_rsvd_lbl);
        if (key->type == VTSS_IS1_TYPE_MPLS_MLL) {
            /* Special for MLL */
            FA_ACT_SET(CLM, FULL_NXT_KEY_TYPE, 2);          // SGL_MLBS
            FA_ACT_SET(CLM, FULL_NXT_NORMALIZE, 1);
            FA_ACT_SET(CLM, FULL_NXT_NORM_W16_OFFSET, 0);
            FA_ACT_SET(CLM, FULL_NXT_TYPE_AFTER_OFFSET, 2); // MPLS, always
            FA_ACT_SET(CLM, FULL_TC_LABEL, 7);              // No update
            FA_ACT_SET(CLM, FULL_TTL_LABEL, 7);             // No update
        }
    }

    /* Update action fields based on ingress QoS mapping */
    fa_clm_action_update(vtss_state, data, is1);

    return fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ALL);
}

static vtss_rc fa_clm_entry_update(vtss_state_t *vtss_state,
                                   vtss_vcap_type_t type, vtss_vcap_idx_t *idx, vtss_is1_data_t *is1)
{
    fa_vcap_data_t fa_data, *data = &fa_data;
    u32            addr;

    data->vcap_type = type;
    data->tg = fa_vcap_key_type(type, idx->key_size);
    addr = fa_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u, map_id: %u, flags: 0x%x",
           idx->row, idx->col, addr, is1->map_id, is1->flags);

    /* Read action */
    VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_READ, FA_VCAP_SEL_ACTION));

    /* Update action fields based on ingress QoS mapping */
    fa_clm_action_update(vtss_state, data, is1);

    /* Write action */
    return fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION);
}

/* - CLM-A --------------------------------------------------------- */

static vtss_rc fa_clm_a_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return fa_clm_entry_add(vtss_state, VTSS_VCAP_TYPE_CLM_A, idx, vcap_data, counter);
}

static vtss_rc fa_clm_a_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return fa_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_CLM_A, idx);
}

static vtss_rc fa_clm_a_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return fa_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_CLM_A, idx, count, up);
}

static vtss_rc fa_clm_a_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return fa_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_CLM_A, idx, counter, clear);
}

/* - CLM-B --------------------------------------------------------- */

static vtss_rc fa_clm_b_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return fa_clm_entry_add(vtss_state, VTSS_VCAP_TYPE_CLM_B, idx, vcap_data, counter);
}

static vtss_rc fa_clm_b_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return fa_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_CLM_B, idx);
}

static vtss_rc fa_clm_b_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return fa_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_CLM_B, idx, count, up);
}

static vtss_rc fa_clm_b_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return fa_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_CLM_B, idx, counter, clear);
}

/* - CLM-C --------------------------------------------------------- */

static vtss_rc fa_clm_c_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return fa_clm_entry_add(vtss_state, VTSS_VCAP_TYPE_CLM_C, idx, vcap_data, counter);
}

static vtss_rc fa_clm_c_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return fa_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_CLM_C, idx);
}

static vtss_rc fa_clm_c_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return fa_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_CLM_C, idx, count, up);
}

static vtss_rc fa_clm_c_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return fa_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_CLM_C, idx, counter, clear);
}

static vtss_rc fa_debug_clm(vtss_state_t *vtss_state, fa_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 type;

    if (data->is_action) {
        switch (data->type) {
        case FA_VCAP_TG_NONE:
            /* Default action is cleared after initialization */
            break;

        case FA_VCAP_TG_X1:
            /* TBD_MPLS */
            break;

        case FA_VCAP_TG_X2:
            type = fa_act_get(data, CLM_AO_X2_TYPE, CLM_AL_X2_TYPE);
            pr("type:%u (%s) ", type, type == CLM_X2_TYPE_MLBS ? "mlbs" : "classification");
            if (type == CLM_X2_TYPE_MLBS) {
                /* TBD_MPLS */
                break;
            }
            FA_DEBUG_ACT_ENA(CLM, "dscp", CLASSIFICATION_DSCP_ENA, CLASSIFICATION_DSCP_VAL);
            FA_DEBUG_ACT_ENA(CLM, "cosid", CLASSIFICATION_COSID_ENA, CLASSIFICATION_COSID_VAL);
            FA_DEBUG_ACT_ENA(CLM, "qos", CLASSIFICATION_QOS_ENA, CLASSIFICATION_QOS_VAL);
            FA_DEBUG_ACT_ENA(CLM, "dp", CLASSIFICATION_DP_ENA, CLASSIFICATION_DP_VAL);
            FA_DEBUG_ACT_ENA(CLM, "pcp", CLASSIFICATION_PCP_ENA, CLASSIFICATION_PCP_VAL);
            FA_DEBUG_ACT_ENA(CLM, "dei", CLASSIFICATION_DEI_ENA, CLASSIFICATION_DEI_VAL);
            pr("\n");
            FA_DEBUG_ACT(CLM, "map_sel", CLASSIFICATION_MAP_LOOKUP_SEL);
            FA_DEBUG_ACT(CLM, "map_key", CLASSIFICATION_MAP_KEY);
            FA_DEBUG_ACT(CLM, "map_idx", CLASSIFICATION_MAP_IDX);
            FA_DEBUG_ACT(CLM, "gvid_sel", CLASSIFICATION_GVID_ADD_REPLACE_SEL);
            FA_DEBUG_ACT(CLM, "xvid_sel", CLASSIFICATION_XVID_ADD_REPLACE_SEL);
            FA_DEBUG_ACT(CLM, "vid_val", CLASSIFICATION_VID_VAL);
            FA_DEBUG_ACT_ENA(CLM, "pop", CLASSIFICATION_VLAN_POP_CNT_ENA, CLASSIFICATION_VLAN_POP_CNT);
            pr("\n");
            FA_DEBUG_ACT_ENA(CLM, "push", CLASSIFICATION_VLAN_PUSH_CNT_ENA, CLASSIFICATION_VLAN_PUSH_CNT);
            FA_DEBUG_ACT(CLM, "tpid_sel", CLASSIFICATION_TPID_SEL);
            FA_DEBUG_ACT(CLM, "was_tagged", CLASSIFICATION_VLAN_WAS_TAGGED);
            FA_DEBUG_ACT(CLM, "isdx_sel", CLASSIFICATION_ISDX_ADD_REPLACE_SEL);
            FA_DEBUG_ACT(CLM, "isdx_val", CLASSIFICATION_ISDX_VAL);
            FA_DEBUG_ACT(CLM, "tr_sel", CLASSIFICATION_RT_SEL);
            FA_DEBUG_ACT_ENA(CLM, "lpm_affix", CLASSIFICATION_LPM_AFFIX_ENA, CLASSIFICATION_LPM_AFFIX_VAL);
            pr("\n");
            FA_DEBUG_ACT(CLM, "rleg_dmac_chk_dis", CLASSIFICATION_RLEG_DMAC_CHK_DIS);
            FA_DEBUG_ACT(CLM, "ttl_decr_dis", CLASSIFICATION_TTL_DECR_DIS);
            FA_DEBUG_ACT(CLM, "l3_mac_update_dis", CLASSIFICATION_L3_MAC_UPDATE_DIS);
            FA_DEBUG_ACT(CLM, "fwd_dis", CLASSIFICATION_FWD_DIS);
            pr("\n");
            FA_DEBUG_ACT_ENA(CLM, "cpu_q", CLASSIFICATION_CPU_ENA, CLASSIFICATION_CPU_Q);
            FA_DEBUG_ACT(CLM, "mip_sel", CLASSIFICATION_MIP_SEL);
            FA_DEBUG_ACT(CLM, "oam_y1731_sel", CLASSIFICATION_OAM_Y1731_SEL);
            FA_DEBUG_ACT(CLM, "oam_twamp_ena", CLASSIFICATION_OAM_TWAMP_ENA);
            FA_DEBUG_ACT(CLM, "oam_ip_pfd_ena", CLASSIFICATION_OAM_IP_BFD_ENA);
            pr("\n");
            FA_DEBUG_ACT(CLM, "pag_override_mask", CLASSIFICATION_PAG_OVERRIDE_MASK);
            FA_DEBUG_ACT(CLM, "pag_val", CLASSIFICATION_PAG_VAL);
            FA_DEBUG_ACT_ENA(CLM, "s2_kel_sel", CLASSIFICATION_S2_KEY_SEL_ENA, CLASSIFICATION_S2_KEY_SEL_IDX);
            FA_DEBUG_ACT_ENA(CLM, "inj_masq", CLASSIFICATION_INJ_MASQ_ENA, CLASSIFICATION_INJ_MASQ_PORT);
            FA_DEBUG_ACT_ENA(CLM, "lport", CLASSIFICATION_LPORT_ENA, CLASSIFICATION_INJ_MASQ_LPORT);
            pr("\n");
            FA_DEBUG_ACT(CLM, "pl_force_ena", CLASSIFICATION_PIPELINE_FORCE_ENA);
            FA_DEBUG_ACT(CLM, "pl_act_sel", CLASSIFICATION_PIPELINE_ACT_SEL);
            FA_DEBUG_ACT(CLM, "pl_pt", CLASSIFICATION_PIPELINE_PT);
            FA_DEBUG_ACT(CLM, "nxt_key_type", CLASSIFICATION_NXT_KEY_TYPE);
            pr("\n");
            FA_DEBUG_ACT(CLM, "nxt_norm_w16_offset", CLASSIFICATION_NXT_NORM_W16_OFFSET);
            FA_DEBUG_ACT(CLM, "nxt_offset_from_type", CLASSIFICATION_NXT_OFFSET_FROM_TYPE);
            FA_DEBUG_ACT(CLM, "nxt_type_after_offset", CLASSIFICATION_NXT_TYPE_AFTER_OFFSET);
            pr("\n");
            FA_DEBUG_ACT(CLM, "nxt_normalize", CLASSIFICATION_NXT_NORMALIZE);
            FA_DEBUG_ACT(CLM, "nxt_idx_ctrl", CLASSIFICATION_NXT_IDX_CTRL);
            FA_DEBUG_ACT(CLM, "nxt_idx", CLASSIFICATION_NXT_IDX_CTRL);
            break;

        case FA_VCAP_TG_X3:
            FA_DEBUG_ACT_ENA(CLM, "dscp", FULL_DSCP_ENA, FULL_DSCP_VAL);
            FA_DEBUG_ACT_ENA(CLM, "cosid", FULL_COSID_ENA, FULL_COSID_VAL);
            FA_DEBUG_ACT_ENA(CLM, "qos", FULL_QOS_ENA, FULL_QOS_VAL);
            FA_DEBUG_ACT_ENA(CLM, "dp", FULL_DP_ENA, FULL_DP_VAL);
            FA_DEBUG_ACT_ENA(CLM, "pcp", FULL_PCP_ENA, FULL_PCP_VAL);
            FA_DEBUG_ACT_ENA(CLM, "dei", FULL_DEI_ENA, FULL_DEI_VAL);
            pr("\n");
            FA_DEBUG_ACT(CLM, "map_sel", FULL_MAP_LOOKUP_SEL);
            FA_DEBUG_ACT(CLM, "map_key", FULL_MAP_KEY);
            FA_DEBUG_ACT(CLM, "map_idx", FULL_MAP_IDX);
            FA_DEBUG_ACT(CLM, "gvid_sel", FULL_GVID_ADD_REPLACE_SEL);
            FA_DEBUG_ACT(CLM, "xvid_sel", FULL_XVID_ADD_REPLACE_SEL);
            FA_DEBUG_ACT(CLM, "vid_val", FULL_VID_VAL);
            FA_DEBUG_ACT_ENA(CLM, "pop", FULL_VLAN_POP_CNT_ENA, FULL_VLAN_POP_CNT);
            pr("\n");
            FA_DEBUG_ACT_ENA(CLM, "push", FULL_VLAN_PUSH_CNT_ENA, FULL_VLAN_PUSH_CNT);
            FA_DEBUG_ACT(CLM, "tpid_sel", FULL_TPID_SEL);
            FA_DEBUG_ACT(CLM, "was_tagged", FULL_VLAN_WAS_TAGGED);
            FA_DEBUG_ACT(CLM, "isdx_sel", FULL_ISDX_ADD_REPLACE_SEL);
            FA_DEBUG_ACT(CLM, "isdx_val", FULL_ISDX_VAL);
            FA_DEBUG_ACT(CLM, "mask_mode", FULL_MASK_MODE);
            pr("\n");
            fa_debug_bits(data, "port_mask", CLM_AO_FULL_PORT_MASK_0, VTSS_CHIP_PORTS);
            FA_DEBUG_ACT(CLM, "rt_sel", FULL_RT_SEL);
            FA_DEBUG_ACT_ENA(CLM, "lpm_affix", FULL_LPM_AFFIX_ENA, FULL_LPM_AFFIX_VAL);
            FA_DEBUG_ACT(CLM, "rleg_dmac_chk_dis", FULL_RLEG_DMAC_CHK_DIS);
            FA_DEBUG_ACT(CLM, "ttl_decr_dis", FULL_TTL_DECR_DIS);
            FA_DEBUG_ACT(CLM, "l3_mac_update_dis", FULL_L3_MAC_UPDATE_DIS);
            pr("\n");
            FA_DEBUG_ACT_ENA(CLM, "cpu_q", FULL_CPU_ENA, FULL_CPU_Q);
            FA_DEBUG_ACT(CLM, "mip_sel", FULL_MIP_SEL);
            FA_DEBUG_ACT(CLM, "oam_y1731_sel", FULL_OAM_Y1731_SEL);
            FA_DEBUG_ACT(CLM, "oam_twamp_ena", FULL_OAM_TWAMP_ENA);
            FA_DEBUG_ACT(CLM, "oam_ip_pfd_ena", FULL_OAM_IP_BFD_ENA);
            pr("\n");
            FA_DEBUG_ACT(CLM, "rsvd_lbl_val", FULL_RSVD_LBL_VAL);
            FA_DEBUG_ACT(CLM, "tc_label", FULL_TC_LABEL);
            FA_DEBUG_ACT(CLM, "num_vld_labels", FULL_NUM_VLD_LABELS);
            FA_DEBUG_ACT(CLM, "fwd_type", FULL_FWD_TYPE);
            FA_DEBUG_ACT(CLM, "mpls_oam_type", FULL_MPLS_OAM_TYPE);
            pr("\n");
            FA_DEBUG_ACT(CLM, "mpls_mep_ena", FULL_MPLS_MEP_ENA);
            FA_DEBUG_ACT(CLM, "mpls_mip_ena", FULL_MPLS_MIP_ENA);
            FA_DEBUG_ACT(CLM, "mpls_oam_flavor", FULL_MPLS_OAM_FLAVOR);
            FA_DEBUG_ACT(CLM, "mpls_ip_ctrl_ena", FULL_MPLS_IP_CTRL_ENA);
            pr("\n");
            FA_DEBUG_ACT(CLM, "custom_ace_ena", FULL_CUSTOM_ACE_ENA);
            FA_DEBUG_ACT(CLM, "custom_ace_offset", FULL_CUSTOM_ACE_OFFSET);
            FA_DEBUG_ACT(CLM, "pag_override_mask", FULL_PAG_OVERRIDE_MASK);
            FA_DEBUG_ACT(CLM, "pag_val", FULL_PAG_VAL);
            pr("\n");
            FA_DEBUG_ACT_ENA(CLM, "s2_kel_sel", FULL_S2_KEY_SEL_ENA, FULL_S2_KEY_SEL_IDX);
            FA_DEBUG_ACT_ENA(CLM, "inj_masq", FULL_INJ_MASQ_ENA, FULL_INJ_MASQ_PORT);
            FA_DEBUG_ACT_ENA(CLM, "lport", FULL_LPORT_ENA, FULL_INJ_MASQ_LPORT);
            FA_DEBUG_ACT(CLM, "match_id", FULL_MATCH_ID);
            FA_DEBUG_ACT(CLM, "match_id_mask", FULL_MATCH_ID_MASK);
            pr("\n");
            FA_DEBUG_ACT(CLM, "pl_force_ena", FULL_PIPELINE_FORCE_ENA);
            FA_DEBUG_ACT(CLM, "pl_act_sel", FULL_PIPELINE_ACT_SEL);
            FA_DEBUG_ACT(CLM, "pl_pt", FULL_PIPELINE_PT);
            FA_DEBUG_ACT(CLM, "nxt_key_type", FULL_NXT_KEY_TYPE);
            pr("\n");
            FA_DEBUG_ACT(CLM, "nxt_norm_w16_offset", FULL_NXT_NORM_W16_OFFSET);
            FA_DEBUG_ACT(CLM, "nxt_offset_from_type", FULL_NXT_OFFSET_FROM_TYPE);
            FA_DEBUG_ACT(CLM, "nxt_type_after_offset", FULL_NXT_TYPE_AFTER_OFFSET);
            pr("\n");
            FA_DEBUG_ACT(CLM, "nxt_normalize", FULL_NXT_NORMALIZE);
            FA_DEBUG_ACT(CLM, "nxt_idx_ctrl", FULL_NXT_IDX_CTRL);
            FA_DEBUG_ACT(CLM, "nxt_idx", FULL_NXT_IDX_CTRL);
            break;

        default:
            VTSS_E("not X1/X2/X3");
            return VTSS_RC_ERROR;
        }
        pr("\ncnt: %u", data->counter);
        return VTSS_RC_OK;
    }

    switch (data->tg) {
    case FA_VCAP_TG_X1:
        /* TBD_MPLS */
        break;

    case FA_VCAP_TG_X2:
        type = fa_entry_bs_get(data, CLM_KO_X2_TYPE, CLM_KL_X2_TYPE);
        FA_DEBUG_BITS(CLM, "type", X2_TYPE);
        pr("(%s) ", type == CLM_X2_TYPE_TRI_VID ? "tri_vid" : type == CLM_X2_TYPE_DBL_MLBS ? "dbl_mlbs" : type == CLM_X2_TYPE_TRI_VID_IDX ? "tri_vid_idx" : "etag");
        FA_DEBUG_BITS(CLM, "first", X2_FIRST);
        if (type != CLM_X2_TYPE_TRI_VID) {
            /* TBD_MPLS */
            break;
        }
        FA_DEBUG_BITS(CLM, "igr_port", X2_IGR_PORT);
        FA_DEBUG_BITS(CLM, "g_idx_sel", TRI_VID_G_IDX_SEL);
        FA_DEBUG_BITS(CLM, "g_idx", TRI_VID_G_IDX);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid0", TRI_VID_TPID0);
        FA_DEBUG_BITS(CLM, "pcp0", TRI_VID_PCP0);
        FA_DEBUG_BITS(CLM, "dei0", TRI_VID_DEI0);
        FA_DEBUG_BITS(CLM, "vid0", TRI_VID_VID0);
        FA_DEBUG_BITS(CLM, "vlan_tags", TRI_VID_VLAN_TAGS);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid1", TRI_VID_TPID1);
        FA_DEBUG_BITS(CLM, "pcp1", TRI_VID_PCP1);
        FA_DEBUG_BITS(CLM, "dei1", TRI_VID_DEI1);
        FA_DEBUG_BITS(CLM, "vid1", TRI_VID_VID1);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid2", TRI_VID_TPID2);
        FA_DEBUG_BITS(CLM, "pcp2", TRI_VID_PCP2);
        FA_DEBUG_BITS(CLM, "dei2", TRI_VID_DEI2);
        FA_DEBUG_BITS(CLM, "vid2", TRI_VID_VID2);
        pr("\n");
        FA_DEBUG_BITS(CLM, "l4_rng", TRI_VID_L4_RNG);
        FA_DEBUG_BITS(CLM, "oam_y1731", TRI_VID_OAM_Y1731);
        FA_DEBUG_BITS(CLM, "oam_mel_flags", TRI_VID_OAM_MEL_FLAGS);
        break;

    case FA_VCAP_TG_X3:
        /* TBD_MPLS */
        break;

    case FA_VCAP_TG_X6:
        type = fa_entry_bs_get(data, CLM_KO_X6_TYPE, CLM_KL_X6_TYPE);
        FA_DEBUG_BITS(CLM, "type", X6_TYPE);
        pr("(%s) ", type == CLM_X6_TYPE_LL_FULL ? "ll_full" : type == CLM_X6_TYPE_NORMAL ? "normal" : type == CLM_X6_TYPE_NORMAL_5TUPLE_IP4 ? "5tuple_ip4" : "custom_2");
        FA_DEBUG_BITS(CLM, "first", X6_FIRST);
        if (type == CLM_X6_TYPE_LL_FULL) {
            /* TBD_MPLS */
            break;
        }
        FA_DEBUG_BITS(CLM, "g_idx_sel", X6_G_IDX_SEL);
        FA_DEBUG_BITS(CLM, "g_idx", X6_G_IDX);
        if (type == CLM_X6_TYPE_CUSTOM_2) {
            break;
        }
        FA_DEBUG_BITS(CLM, "port_mask_sel", X6_IGR_PORT_MASK_SEL);
        pr("\n");
        fa_debug_bits(data, "port_mask", CLM_KO_X6_IGR_PORT_MASK_0, VTSS_CHIP_PORTS);
        FA_DEBUG_BITS(CLM, "l2_mc", X6_L2_MC);
        FA_DEBUG_BITS(CLM, "l2_bc", X6_L2_BC);
        FA_DEBUG_BITS(CLM, "vlan_tags", X6_VLAN_TAGS);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid0", X6_TPID0);
        FA_DEBUG_BITS(CLM, "pcp0", X6_PCP0);
        FA_DEBUG_BITS(CLM, "dei0", X6_DEI0);
        FA_DEBUG_BITS(CLM, "vid0", X6_VID0);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid1", X6_TPID1);
        FA_DEBUG_BITS(CLM, "pcp1", X6_PCP1);
        FA_DEBUG_BITS(CLM, "dei1", X6_DEI1);
        FA_DEBUG_BITS(CLM, "vid1", X6_VID1);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid2", X6_TPID2);
        FA_DEBUG_BITS(CLM, "pcp2", X6_PCP2);
        FA_DEBUG_BITS(CLM, "dei2", X6_DEI2);
        FA_DEBUG_BITS(CLM, "vid2", X6_VID2);
        pr("\n");
        if (type == CLM_X6_TYPE_NORMAL) {
            FA_DEBUG_BITS(CLM, "dst_entry", NORMAL_DST_ENTRY);
            FA_DEBUG_MAC(CLM, "l2_smac", NORMAL_L2_SMAC_0);
            FA_DEBUG_BITS(CLM, "ip_mc", NORMAL_IP_MC);
            FA_DEBUG_BITS(CLM, "etype_len", NORMAL_ETYPE_LEN);
            FA_DEBUG_BITS(CLM, "etype", NORMAL_ETYPE);
            FA_DEBUG_BITS(CLM, "ip_snap", NORMAL_IP_SNAP);
            FA_DEBUG_BITS(CLM, "ip4", NORMAL_IP4);
            FA_DEBUG_BITS(CLM, "l3_fragment_type", NORMAL_L3_FRAGMENT_TYPE);
            pr("\n");
            FA_DEBUG_BITS(CLM, "l3_frag_invld_l4_len", NORMAL_L3_FRAG_INVLD_L4_LEN);
            FA_DEBUG_BITS(CLM, "l3_options", NORMAL_L3_OPTIONS);
            FA_DEBUG_BITS(CLM, "l3_dscp", NORMAL_L3_DSCP);
            pr("\n");
            FA_DEBUG_BITS(CLM, "l3_ip4_sip", NORMAL_L3_IP4_SIP);
            FA_DEBUG_BITS(CLM, "tcp_udp", NORMAL_TCP_UDP);
            FA_DEBUG_BITS(CLM, "tcp", NORMAL_TCP);
            FA_DEBUG_BITS(CLM, "l4_sport", NORMAL_L4_SPORT);
            FA_DEBUG_BITS(CLM, "l4_rng", NORMAL_L4_RNG);
            break;
        }
        /* CLM_X6_TYPE_NORMAL_5TUPLE_IP4K */
        FA_DEBUG_BITS(CLM, "ip_mc", NORMAL_5TUPLE_IP4_IP_MC);
        FA_DEBUG_BITS(CLM, "ip4", NORMAL_5TUPLE_IP4_IP4);
        FA_DEBUG_BITS(CLM, "l3_fragment_type", NORMAL_5TUPLE_IP4_L3_FRAGMENT_TYPE);
        FA_DEBUG_BITS(CLM, "l3_frag_invld_l4_len", NORMAL_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN);
        FA_DEBUG_BITS(CLM, "l3_options", NORMAL_5TUPLE_IP4_L3_OPTIONS);
        FA_DEBUG_BITS(CLM, "l3_dscp", NORMAL_5TUPLE_IP4_L3_DSCP);
        pr("\n");
        FA_DEBUG_BITS(CLM, "l3_ip4_dip", NORMAL_5TUPLE_IP4_L3_IP4_DIP);
        FA_DEBUG_BITS(CLM, "l3_ip4_sip", NORMAL_5TUPLE_IP4_L3_IP4_SIP);
        FA_DEBUG_BITS(CLM, "l3_ip_proto", NORMAL_5TUPLE_IP4_L3_IP_PROTO);
        FA_DEBUG_BITS(CLM, "tcp_udp", NORMAL_5TUPLE_IP4_TCP_UDP);
        FA_DEBUG_BITS(CLM, "tcp", NORMAL_5TUPLE_IP4_TCP);
        FA_DEBUG_BITS(CLM, "l4_rng", NORMAL_5TUPLE_IP4_L4_RNG);
        pr("\n");
        FA_DEBUG_BITS(CLM, "ip_payload", NORMAL_5TUPLE_IP4_IP_PAYLOAD_5TUPLE);
        break;

    case FA_VCAP_TG_X12:
        type = fa_entry_bs_get(data, CLM_KO_X12_TYPE, CLM_KL_X12_TYPE);
        FA_DEBUG_BITS(CLM, "type", X12_TYPE);
        pr("(%s) ", type == CLM_X12_TYPE_NORMAL_7TUPLE ? "7tuple" : "custom_1");
        FA_DEBUG_BITS(CLM, "first", X12_FIRST);
        FA_DEBUG_BITS(CLM, "g_idx_sel", X12_G_IDX_SEL);
        FA_DEBUG_BITS(CLM, "g_idx", X12_G_IDX);
        if (type == CLM_X12_TYPE_CUSTOM_1) {
            break;
        }
        FA_DEBUG_BITS(CLM, "port_mask_sel", NORMAL_7TUPLE_IGR_PORT_MASK_SEL);
        pr("\n");
        fa_debug_bits(data, "port_mask", CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_0, VTSS_CHIP_PORTS);
        FA_DEBUG_BITS(CLM, "l2_mc", NORMAL_7TUPLE_L2_MC);
        FA_DEBUG_BITS(CLM, "l2_bc", NORMAL_7TUPLE_L2_BC);
        FA_DEBUG_BITS(CLM, "vlan_tags", NORMAL_7TUPLE_VLAN_TAGS);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid0", NORMAL_7TUPLE_TPID0);
        FA_DEBUG_BITS(CLM, "pcp0", NORMAL_7TUPLE_PCP0);
        FA_DEBUG_BITS(CLM, "dei0", NORMAL_7TUPLE_DEI0);
        FA_DEBUG_BITS(CLM, "vid0", NORMAL_7TUPLE_VID0);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid1", NORMAL_7TUPLE_TPID1);
        FA_DEBUG_BITS(CLM, "pcp1", NORMAL_7TUPLE_PCP1);
        FA_DEBUG_BITS(CLM, "dei1", NORMAL_7TUPLE_DEI1);
        FA_DEBUG_BITS(CLM, "vid1", NORMAL_7TUPLE_VID1);
        pr("\n");
        FA_DEBUG_BITS(CLM, "tpid2", NORMAL_7TUPLE_TPID2);
        FA_DEBUG_BITS(CLM, "pcp2", NORMAL_7TUPLE_PCP2);
        FA_DEBUG_BITS(CLM, "dei2", NORMAL_7TUPLE_DEI2);
        FA_DEBUG_BITS(CLM, "vid2", NORMAL_7TUPLE_VID2);
        pr("\n");
        FA_DEBUG_MAC(CLM, "l2_dmac", NORMAL_7TUPLE_L2_DMAC_0);
        FA_DEBUG_MAC(CLM, "l2_smac", NORMAL_7TUPLE_L2_SMAC_0);
        FA_DEBUG_BITS(CLM, "ip_mc", NORMAL_7TUPLE_IP_MC);
        FA_DEBUG_BITS(CLM, "etype_len", NORMAL_7TUPLE_ETYPE_LEN);
        FA_DEBUG_BITS(CLM, "etype", NORMAL_7TUPLE_ETYPE);
        FA_DEBUG_BITS(CLM, "ip_snap", NORMAL_7TUPLE_IP_SNAP);
        FA_DEBUG_BITS(CLM, "ip4", NORMAL_7TUPLE_IP4);
        FA_DEBUG_BITS(CLM, "l3_fragment_type", NORMAL_7TUPLE_L3_FRAGMENT_TYPE);
        pr("\n");
        FA_DEBUG_BITS(CLM, "l3_frag_invld_l4_len", NORMAL_7TUPLE_L3_FRAG_INVLD_L4_LEN);
        FA_DEBUG_BITS(CLM, "l3_options", NORMAL_7TUPLE_L3_OPTIONS);
        FA_DEBUG_BITS(CLM, "l3_dscp", NORMAL_7TUPLE_L3_DSCP);
        pr("\n");
        FA_DEBUG_IPV6(CLM, "l3_ip6_dip", NORMAL_7TUPLE_L3_IP6_DIP_0);
        FA_DEBUG_IPV6(CLM, "l3_ip6_sip", NORMAL_7TUPLE_L3_IP6_SIP_0);
        FA_DEBUG_BITS(CLM, "tcp_udp", NORMAL_7TUPLE_TCP_UDP);
        FA_DEBUG_BITS(CLM, "tcp", NORMAL_7TUPLE_TCP);
        FA_DEBUG_BITS(CLM, "l4_sport", NORMAL_7TUPLE_L4_SPORT);
        FA_DEBUG_BITS(CLM, "l4_rng", NORMAL_7TUPLE_L4_RNG);
        break;

    default:
        VTSS_E("not X1/X2/X3/X6/X12");
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_debug_clm_all(vtss_state_t *vtss_state,
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
        vtss_fa_debug_reg_header(pr, buf);
        for (i = 0; i < 2; i++) {
            j = ((type == VTSS_VCAP_TYPE_CLM_A ? 0 : type == VTSS_VCAP_TYPE_CLM_B ? 2 : 4) + i);
            VTSS_SPRINTF(buf, "ADV_CL_CFG_%u", port);
            vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_ADV_CL_CFG(port, j), j, buf);
        }
        pr("\n");
    }
    return fa_debug_vcap(vtss_state, type, pr, info, fa_debug_clm);
}

vtss_rc vtss_fa_debug_clm_a(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info)
{
    return fa_debug_clm_all(vtss_state, VTSS_VCAP_TYPE_CLM_A, pr, info);
}

vtss_rc vtss_fa_debug_clm_b(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info)
{
    return fa_debug_clm_all(vtss_state, VTSS_VCAP_TYPE_CLM_B, pr, info);
}

vtss_rc vtss_fa_debug_clm_c(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info)
{
    return fa_debug_clm_all(vtss_state, VTSS_VCAP_TYPE_CLM_C, pr, info);
}

/* - LPM ----------------------------------------------------------- */

static vtss_rc fa_lpm_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    fa_vcap_data_t      fa_data, *data = &fa_data;
    vtss_lpm_entry_t     *entry = vcap_data->u.lpm.entry;
    vtss_lpm_key_t       *key = &entry->key;
    vtss_lpm_action_t    *action = &entry->action;
    vtss_lpm_arp_entry_t *arp_entry = &action->data.arp_entry;
    vtss_lpm_arp_ptr_t   *arp_ptr = &action->data.arp_ptr;
    vtss_vid_mac_t       vid_mac;
    u32                  addr, mach, macl;

    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = VTSS_VCAP_TYPE_LPM;
    addr = fa_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u", idx->row, idx->col, addr);

    /* Setup key fields */
    switch (key->type) {
    case VTSS_LPM_KEY_SGL_IP4:
        data->tg = FA_VCAP_TG_X1;
        fa_vcap_key_bit_set(data, LPM_KO_SGL_IP4_DST_FLAG, key->data.sgl_ip4.dst_ena ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        fa_vcap_key_ipv4_set(data, LPM_KO_SGL_IP4_IP4_XIP, &key->data.sgl_ip4.xip);
        break;
    case VTSS_LPM_KEY_DBL_IP4:
        data->tg = FA_VCAP_TG_X2;
        fa_vcap_key_bit_set(data, LPM_KO_X2_TYPE, VTSS_VCAP_BIT_0);
        fa_vcap_key_ipv4_set(data, LPM_KO_DBL_IP4_IP4_SIP, &key->data.dbl_ip4.sip);
        fa_vcap_key_ipv4_set(data, LPM_KO_DBL_IP4_IP4_DIP, &key->data.dbl_ip4.dip);
        break;
    case VTSS_LPM_KEY_SGL_IP6:
        data->tg = FA_VCAP_TG_X3;
        fa_vcap_key_bit_set(data, LPM_KO_SGL_IP6_DST_FLAG, key->data.sgl_ip6.dst_ena ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        fa_vcap_key_u128_set(data, LPM_KO_SGL_IP6_IP6_XIP_0, &key->data.sgl_ip6.xip);
        break;
    case VTSS_LPM_KEY_DBL_IP6:
        data->tg = FA_VCAP_TG_X6;
        fa_vcap_key_u128_set(data, LPM_KO_DBL_IP6_IP6_SIP_0, &key->data.dbl_ip6.sip);
        fa_vcap_key_u128_set(data, LPM_KO_DBL_IP6_IP6_DIP_0, &key->data.dbl_ip6.dip);
        break;
    default:
        VTSS_E("illegal key type");
        return VTSS_RC_ERROR;
    }

    /* Setup action fields */
    data->type = FA_VCAP_TG_X1;
    switch (action->type) {
    case LPM_X1_TYPE_ARP_PTR:
        FA_ACT_SET(LPM, ARP_PTR_ARP_PTR, arp_ptr->arp_ptr);
        FA_ACT_SET(LPM, ARP_PTR_ECMP_CNT, arp_ptr->ecmp_cnt);
        FA_ACT_SET(LPM, ARP_PTR_RGID, arp_ptr->rgid);
        break;
    case LPM_X1_TYPE_ARP_ENTRY:
        vid_mac.vid = 0;
        vid_mac.mac = arp_entry->mac;
        vtss_mach_macl_get(&vid_mac, &mach, &macl);
        FA_ACT_SET(LPM, ARP_ENTRY_MAC_MSB, mach);
        FA_ACT_SET(LPM, ARP_ENTRY_MAC_LSB, macl);
        FA_ACT_SET(LPM, ARP_ENTRY_ARP_VMID, arp_entry->vmid);
        FA_ACT_SET(LPM, ARP_ENTRY_ZERO_DMAC_CPU_QU, arp_entry->cpu_queue);
        FA_ACT_SET(LPM, ARP_ENTRY_SECUR_MATCH_MAC_ENA, arp_entry->secur_match_mac_ena);
        FA_ACT_SET(LPM, ARP_ENTRY_ARP_ENA, arp_entry->arp_ena);
        break;
    case LPM_X1_TYPE_L3MC_PTR:
        FA_ACT_SET(LPM, L3MC_PTR_L3MC_PTR, action->data.l3mc_idx);
        break;
    default:
        VTSS_E("illegal key type");
        return VTSS_RC_ERROR;
    }
    FA_ACT_SET(LPM, X1_TYPE, action->type);

    return fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ALL);
}

static vtss_rc fa_lpm_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return fa_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_LPM, idx);
}

static vtss_rc fa_lpm_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return fa_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_LPM, idx, count, up);
}

static vtss_rc fa_lpm_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return fa_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_LPM, idx, counter, clear);
}

static vtss_rc fa_debug_lpm(vtss_state_t *vtss_state, fa_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 type;

    if (data->is_action) {
        /* Show action fields */
        type = fa_act_get(data, LPM_AO_X1_TYPE, LPM_AL_X1_TYPE);
        pr("type:%u (%s) ", type,
           type == LPM_X1_TYPE_ARP_PTR ? "arp_ptr" :
           type == LPM_X1_TYPE_L3MC_PTR ? "l3mc_ptr" :
           type == LPM_X1_TYPE_ARP_ENTRY ? "arp_entry" : "?");

        switch (type) {
        case LPM_X1_TYPE_ARP_PTR:
            FA_DEBUG_ACT(LPM, "arp_ptr", ARP_PTR_ARP_PTR);
            FA_DEBUG_ACT(LPM, "remap_ena", ARP_PTR_ARP_PTR_REMAP_ENA);
            FA_DEBUG_ACT(LPM, "ecmp_cnt", ARP_PTR_ECMP_CNT);
            FA_DEBUG_ACT(LPM, "rgid", ARP_PTR_RGID);
            break;
        case LPM_X1_TYPE_L3MC_PTR:
            FA_DEBUG_ACT(LPM, "l3mc_ptr", L3MC_PTR_L3MC_PTR);
            break;
        case LPM_X1_TYPE_ARP_ENTRY:
            FA_DEBUG_ACT_BITS(LPM, "mac_msb", ARP_ENTRY_MAC_MSB);
            FA_DEBUG_ACT_BITS(LPM, "mac_lsb", ARP_ENTRY_MAC_LSB);
            FA_DEBUG_ACT(LPM, "vmid", ARP_ENTRY_ARP_VMID);
            FA_DEBUG_ACT(LPM, "cpu_queue", ARP_ENTRY_ZERO_DMAC_CPU_QU);
            FA_DEBUG_ACT(LPM, "sip_rpf_ena", ARP_ENTRY_SIP_RPF_ENA);
            FA_DEBUG_ACT(LPM, "secur_vmid_ena", ARP_ENTRY_SECUR_MATCH_VMID_ENA);
            FA_DEBUG_ACT(LPM, "secur_mac_ena", ARP_ENTRY_SECUR_MATCH_MAC_ENA);
            FA_DEBUG_ACT(LPM, "arp_ena", ARP_ENTRY_ARP_ENA);
            FA_DEBUG_ACT(LPM, "encap_id", ARP_ENTRY_ENCAP_ID);
            FA_DEBUG_ACT(LPM, "rsdx", ARP_ENTRY_RSDX);
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
    case FA_VCAP_TG_X1:
        FA_DEBUG_BITS(LPM, "dst_flag", SGL_IP4_DST_FLAG);
        FA_DEBUG_BITS(LPM, "affix", SGL_IP4_AFFIX);
        FA_DEBUG_BITS(LPM, "ip4_xip", SGL_IP4_IP4_XIP);
        break;
    case FA_VCAP_TG_X2:
        type = fa_entry_bs_get(data, LPM_KO_X2_TYPE, LPM_KL_X2_TYPE);
        pr("type:%u (%s) ", type, type == LPM_X2_TYPE_DBL_IP4 ? "dbl_ip4" : "ip6pfx_id");
        if (type == LPM_X2_TYPE_DBL_IP4) {
            FA_DEBUG_BITS(LPM, "affix", DBL_IP4_AFFIX);
            pr("\n");
            FA_DEBUG_BITS(LPM, "ip4_sip", DBL_IP4_IP4_SIP);
            FA_DEBUG_BITS(LPM, "ip4_dip", DBL_IP4_IP4_DIP);
        } else {
            FA_DEBUG_BITS(LPM, "dst_flag", IP6PFX_ID_DST_FLAG);
            FA_DEBUG_BITS(LPM, "affix", IP6PFX_ID_AFFIX);
            FA_DEBUG_BITS(LPM, "ip6pfx_id", IP6PFX_ID_IP6PFX_ID);
            pr("\n");
            FA_DEBUG_BITS_64(LPM, "ip6_xip", IP6PFX_ID_IP6_XIP_0_2);
        }
        break;
    case FA_VCAP_TG_X3:
        FA_DEBUG_BITS(LPM, "dst_flag", SGL_IP6_DST_FLAG);
        FA_DEBUG_BITS(LPM, "affix", SGL_IP6_AFFIX);
        pr("\n");
        FA_DEBUG_IPV6(LPM, "ip6_xip", SGL_IP6_IP6_XIP_0);
        break;
    case FA_VCAP_TG_X6:
        FA_DEBUG_BITS(LPM, "affix", DBL_IP6_AFFIX);
        pr("\n");
        FA_DEBUG_IPV6(LPM, "ip6_sip", DBL_IP6_IP6_SIP_0);
        FA_DEBUG_IPV6(LPM, "ip6_dip", DBL_IP6_IP6_DIP_0);
        break;
    default:
        VTSS_E("not X1/X2/X3/X6");
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_debug_lpm(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info)
{
    return fa_debug_vcap(vtss_state, VTSS_VCAP_TYPE_LPM, pr, info, fa_debug_lpm);
}

/* - IS2 ----------------------------------------------------------- */

/* Indices reserved for controlling RLEG statistics */
#define FA_RLEG_STAT_IRACL 0
#define FA_RLEG_STAT_ERACL 1

/* The first counters are used for port default actions. For convenience, ACE counters start from 100 */
#define FA_ACE_CNT_ID_BASE 100
#define FA_ACE_CNT_ID_IPMC (FA_ACE_CNT_ID_BASE - 1)
#define FA_ACE_CNT_ID_DEF  (FA_ACE_CNT_ID_BASE - 4)

static vtss_rc fa_is2_cnt_get(vtss_state_t *vtss_state, vtss_vcap_type_t type, u32 cnt_id, u32 *counter)
{
    if (type == VTSS_VCAP_TYPE_IS2) {
        REG_RD(VTSS_ANA_ACL_CNT_A(cnt_id), counter);
    } else {
        REG_RD(VTSS_ANA_ACL_CNT_B(cnt_id), counter);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_is2_cnt_set(vtss_state_t *vtss_state, vtss_vcap_type_t type, u32 cnt_id, u32 counter)
{
    if (type == VTSS_VCAP_TYPE_IS2) {
        REG_WR(VTSS_ANA_ACL_CNT_A(cnt_id), counter);
    } else {
        REG_WR(VTSS_ANA_ACL_CNT_B(cnt_id), counter);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_is2_action_set(vtss_state_t *vtss_state, fa_vcap_data_t *data, vtss_hacl_action_t *action, u32 cnt_id, u32 counter)
{
    vtss_acl_port_action_t     act = action->port_action;
    vtss_acl_ptp_action_conf_t *ptp = &action->ptp;
    vtss_port_no_t             port_no;
    u32                        discard = 0, port, ptp_cmd, ptp_add, ptp_opt;
    u32                        sip_idx = 0, rt_mode, mach, macl, dmac_offset_ena = 0, match_id, log_msg_int;
    vtss_vid_mac_t             vid_mac;

    data->type = FA_VCAP_TG_X3;
    FA_ACT_SET(IS2, BASE_TYPE_IS_INNER_ACL, action->cpu && act == VTSS_ACL_PORT_ACTION_REDIR); /* CPU copy/redirect (e.g. service policing/stats still applied) */
    /* Unused: BASE_TYPE_PIPELINE_FORCE_ENA */
    /* Unused: BASE_TYPE_PIPELINE_PT */
    FA_ACT_SET(IS2, BASE_TYPE_HIT_ME_ONCE, action->cpu_once);
    /* Unused: BASE_TYPE_INTR_ENA */
    FA_ACT_SET(IS2, BASE_TYPE_CPU_COPY_ENA, action->cpu);
    FA_ACT_SET(IS2, BASE_TYPE_CPU_QU_NUM, action->cpu_queue);
    if (act != VTSS_ACL_PORT_ACTION_NONE) {
        /* Port filter or redirect */
        discard = 1;
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (action->port_list[port_no]) {
                discard = 0;
                port = VTSS_CHIP_PORT(port_no);
                if (act != VTSS_ACL_PORT_ACTION_REDIR || vtss_state->l2.tx_forward_aggr[port_no]) {
                    fa_act_set(data, IS2_AO_BASE_TYPE_PORT_MASK_0 + port, 1, 1);
                }
            }
        }
    }
    FA_ACT_SET(IS2, BASE_TYPE_MASK_MODE,
               act == VTSS_ACL_PORT_ACTION_PGID ? 2 :               /* REPLACE_PGID */
               (act == VTSS_ACL_PORT_ACTION_REDIR || discard) ? 3 : /* REPLACE_ALL */
               act == VTSS_ACL_PORT_ACTION_FILTER ? 1 :             /* AND_VLANMASK */
               0);                                                  /* OR_DSTMASK */
    /* If forwarding disabled, avoid CPU copy and signal ACL drop */
    FA_ACT_SET(IS2, BASE_TYPE_CPU_DIS, discard || action->cpu_disable ? 1 : 0);
    FA_ACT_SET(IS2, BASE_TYPE_LRN_DIS, 0);
    FA_ACT_SET(IS2, BASE_TYPE_RT_DIS, discard);
    FA_ACT_SET(IS2, BASE_TYPE_POLICE_ENA, action->police);
    FA_ACT_SET(IS2, BASE_TYPE_POLICE_IDX, action->police ? action->policer_no : 0);
    /* Unused: BASE_TYPE_IGNORE_PIPELINE_CTRL */
    /* Unused: BASE_TYPE_DLB_OFFSET */
    /* Unused: BASE_TYPE_RSDX_ENA */
    /* Unused: BASE_TYPE_RSDX_VAL */
    FA_ACT_SET(IS2, BASE_TYPE_MIRROR_PROBE, action->mirror ? (FA_MIRROR_PROBE_RX + 1) : 0);

    /* PTP actions */
    ptp_cmd = 1;   /* ONE-STEP by default */
    ptp_add = 0;   /* No add to CF field by default */
    ptp_opt = 0;   /* No option bit by default */
    switch (action->ptp_action) {
    case VTSS_ACL_PTP_ACTION_ONE_STEP:
        break;
    case VTSS_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY:
        ptp_add = 1; /* Egress delay */
        break;
    case VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1:
        ptp_add = 2; /* Ingress delay 1 */
        break;
    case VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2:
        ptp_add = 3; /* Ingress delay 2 */
        break;
    case VTSS_ACL_PTP_ACTION_TWO_STEP:
        ptp_cmd = 0; /* TWO-STEP */
        ptp_opt = 1;
        break;
    default:
        ptp_cmd = 0;
        break;
    }
    switch (action->ptp.response) {
    case VTSS_ACL_PTP_RSP_DLY_REQ_RSP_TS_UPD:
    case VTSS_ACL_PTP_RSP_DLY_REQ_RSP_NO_TS:
        ptp_cmd = 2; /* Delay request responce */
        ptp_opt = 1;
        break;
    default:
        break;
    }
    FA_ACT_SET(IS2, BASE_TYPE_REW_CMD,
               ((ptp_cmd << 0) +
                (ptp_opt << 2) +
                (ptp_add << 3) +
                ((ptp->set_smac_to_port_mac ? 1 : 0) << 5) +
                (ptp->dom_sel << 6)));

    /* Unused: BASE_TYPE_TTL_UPDATE_ENA */
    /* Unused: BASE_TYPE_SAM_SEQ_ENA */
    if (action->ptp.response != VTSS_ACL_PTP_RSP_NONE) {
        FA_ACT_SET(IS2, BASE_TYPE_TCP_UDP_ENA, 1);
        FA_ACT_SET(IS2, BASE_TYPE_TCP_UDP_DPORT, ptp->dport);
        FA_ACT_SET(IS2, BASE_TYPE_TCP_UDP_SPORT, ptp->sport);
        log_msg_int = ((ptp->log_message_interval < 0 ? 0x8 : 0) + (ptp->log_message_interval & 0x7));
        FA_ACT_SET(IS2, BASE_TYPE_LOG_MSG_INTERVAL, log_msg_int);
    }
    match_id = (FA_IFH_CL_RSLT_ACL_HIT | (action->ifh_flag ? FA_IFH_CL_RSLT_ACL_FLAG : 0));
    FA_ACT_SET(IS2, BASE_TYPE_MATCH_ID, match_id);
    FA_ACT_SET(IS2, BASE_TYPE_MATCH_ID_MASK, match_id);
    FA_ACT_SET(IS2, BASE_TYPE_CNT_ID, cnt_id);
    FA_ACT_SET(IS2, BASE_TYPE_SWAP_MAC_ENA, 0);

    /* MAC address update */
    rt_mode = (1 << 3); /* Swapping mode by default */
    switch (action->addr.update) {
    case VTSS_ACL_ADDR_UPDATE_MAC_SWAP:
        rt_mode += 2;
        break;
    case VTSS_ACL_ADDR_UPDATE_MAC_IP_SWAP_UC:
        rt_mode += 5;
        sip_idx = action->addr.sip_idx;
        break;
    case VTSS_ACL_ADDR_UPDATE_DMAC_REPLACE:
        break;
    case VTSS_ACL_ADDR_UPDATE_DMAC_REPLACE_MSB:
        dmac_offset_ena = 1;
        break;
    default:
        rt_mode = 0; /* Routing mode */
        break;
    }
    FA_ACT_SET(IS2, BASE_TYPE_ACL_RT_MODE, rt_mode);

    vid_mac.vid = 0;
    vid_mac.mac = action->addr.mac;
    vtss_mach_macl_get(&vid_mac, &mach, &macl);
    FA_ACT_SET(IS2, BASE_TYPE_ACL_MAC_0, macl);
    FA_ACT_SET(IS2, BASE_TYPE_ACL_MAC_1, mach);
    FA_ACT_SET(IS2, BASE_TYPE_DMAC_OFFSET_ENA, dmac_offset_ena);
    FA_ACT_SET(IS2, BASE_TYPE_PTP_MASTER_SEL, ptp->dom_sel);
    FA_ACT_SET(IS2, BASE_TYPE_SIP_IDX, sip_idx);
    /* Unused: BASE_TYPE_RLEG_STAT_IDX */
    /* Unused:  BASE_TYPE_IGR_ACL_ENA */
    /* Unused:  BASE_TYPE_EGR_ACL_ENA */

    /* Write ACE counter only */
    return (cnt_id < FA_ACE_CNT_ID_BASE ? VTSS_RC_OK : fa_is2_cnt_set(vtss_state, data->vcap_type, cnt_id, counter));
}

static void fa_action_old2new(const vtss_acl_action_t *old, vtss_hacl_action_t *new)
{
    vtss_port_no_t port_no;

    new->port_action = old->port_action;
    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        new->port_list[port_no] = old->port_list[port_no];
    }
    new->cpu = old->cpu;
    new->cpu_once = old->cpu_once;
    new->cpu_disable = old->cpu_disable;
    new->cpu_queue = old->cpu_queue;
    new->police = old->police;
    new->policer_no = old->policer_no;
    new->mirror = old->mirror;
    new->ptp_action = old->ptp_action;
    new->ptp = old->ptp;
    new->addr = old->addr;
    if (old->mac_swap) {
        new->addr.update = VTSS_ACL_ADDR_UPDATE_MAC_SWAP;
    }
    new->ifh_flag = old->ifh_flag;
}

static void fa_ace_key_bit_set(fa_vcap_data_t *data, u32 offset, vtss_ace_bit_t fld)
{
    fa_vcap_key_set(data, offset, 1, fld == VTSS_ACE_BIT_1 ? 1 : 0, fld == VTSS_ACE_BIT_ANY ? 0 : 1);
}

static void fa_ace_key_bit_inv_set(fa_vcap_data_t *data, u32 offset, vtss_ace_bit_t fld)
{
    fa_vcap_key_set(data, offset, 1, fld == VTSS_ACE_BIT_0 ? 1 : 0, fld == VTSS_ACE_BIT_ANY ? 0 : 1);
}

static void fa_is2_ptp_key_set(fa_vcap_data_t *data, u32 offset, vtss_ace_u32_t *ptp)
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
    fa_vcap_key_bytes_set(data, offset, val, msk, 8);
}

static u32 fa_l4_port_mask(vtss_vcap_udp_tcp_t *l4_port)
{
    return (l4_port->in_range && l4_port->low == l4_port->high ? 0xffff : 0);
}

static vtss_rc fa_is2_entry_add(vtss_state_t *vtss_state, vtss_vcap_type_t vcap_type, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    fa_vcap_data_t          fa_data, *data = &fa_data;
    vtss_is2_data_t         *is2 = &vcap_data->u.is2;
    vtss_is2_entry_t        *entry = is2->entry;
    vtss_hace_t             *ace = &entry->ace;
    vtss_hace_key_t         *key = &ace->key;
    vtss_hace_frame_etype_t *etype = &key->etype;
    vtss_hace_frame_llc_t   *llc = &key->llc;
    vtss_hace_frame_snap_t  *snap = &key->snap;
    vtss_hace_frame_arp_t   *arp = &key->arp;
    vtss_hace_frame_ipv4_t  *ipv4 = &key->ipv4;
    vtss_hace_frame_ipv6_t  *ipv6 = &key->ipv6;
    vtss_vcap_u8_t          *proto = NULL;
    vtss_vcap_udp_tcp_t     *sport, *dport;
    vtss_vcap_u128_t        sip, dip;
    u32                     addr, i, n, l4_rng;
    u32                     type = IS2_X6_TYPE_MAC_ETYPE;
    u32                     mask = VTSS_BITMASK(IS2_KL_X6_TYPE);
    u8                      m;
    vtss_vcap_bit_t         oam, udp_tcp;
    BOOL                    tcp, found = 0, smac_dmac = 0;

    addr = fa_vcap_entry_addr(vtss_state, vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u, type: %u", idx->row, idx->col, addr, key->type);
    VTSS_MEMSET(data, 0, sizeof(*data));
    l4_rng = ((is2->srange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->srange)) |
              (is2->drange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->drange)));
    data->tg = (idx->key_size == VTSS_VCAP_KEY_SIZE_FULL ? FA_VCAP_TG_X12 :
                idx->key_size == VTSS_VCAP_KEY_SIZE_HALF ? FA_VCAP_TG_X6 : FA_VCAP_TG_X3);

    if (entry->ipmc) {
        /* IPMC rule, the 'FIRST' field is wildcard to allow matching in both IS2_B lookups */
        if (data->tg == FA_VCAP_TG_X3) {
            fa_vcap_key_set(data, IS2_KO_IP4_VID_XVID, IS2_KL_IP4_VID_XVID, key->vlan.vid.value, key->vlan.vid.mask);
            fa_vcap_key_ipv4_set(data, IS2_KO_IP4_VID_L3_IP4_DIP, &ipv4->dip);
            fa_vcap_key_ipv4_set(data, IS2_KO_IP4_VID_L3_IP4_SIP, &ipv4->sip);
        } else {
            fa_vcap_key_set(data, IS2_KO_X6_TYPE, IS2_KL_X6_TYPE, IS2_X6_TYPE_IP6_VID, mask);
            fa_vcap_key_set(data, IS2_KO_IP6_VID_XVID, IS2_KL_IP6_VID_XVID, key->vlan.vid.value, key->vlan.vid.mask);
            fa_vcap_key_u128_set(data, IS2_KO_IP6_VID_L3_IP6_DIP_0, &ipv6->dip);
            fa_vcap_key_u128_set(data, IS2_KO_IP6_VID_L3_IP6_SIP_0, &ipv6->sip);
        }
        is2->cnt_id = FA_ACE_CNT_ID_IPMC; /* Common counter for all IPMC rules */
        goto apply;
    }

    if (key->type == VTSS_ACE_TYPE_IPV4) {
        /* IPv4 */
        proto = &ipv4->proto;
        sport = &ipv4->sport;
        dport = &ipv4->dport;
    } else {
        /* IPv6 */
        ipv4 = NULL;
        proto = &ipv6->proto;
        sport = &ipv6->sport;
        dport = &ipv6->dport;
    }

    if (idx->key_size == VTSS_VCAP_KEY_SIZE_FULL) {
        /* X12 rule for IPv4/IPv6 */
        fa_vcap_key_set(data, IS2_KO_X12_TYPE, IS2_KL_X12_TYPE, IS2_X12_TYPE_IP_7TUPLE, VTSS_BITMASK(IS2_KL_X12_TYPE));
        fa_vcap_key_bit_set(data, IS2_KO_X12_FIRST, entry->first ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        fa_vcap_key_u8_set(data, IS2_KO_X12_PAG, &key->policy);
        fa_vcap_key_bit_set(data, IS2_KO_X12_IGR_PORT_MASK_L3,
                            vcap_type == VTSS_VCAP_TYPE_IS2_B ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        fa_vcap_key_set(data, IS2_KO_X12_IGR_PORT_MASK_RNG, IS2_KL_X12_IGR_PORT_MASK_RNG,
                        entry->rng, VTSS_BITMASK(IS2_KL_X12_IGR_PORT_MASK_RNG));
        fa_vcap_key_set(data, IS2_KO_X12_IGR_PORT_MASK_0, IS2_KL_X12_IGR_PORT_MASK_0, 0, ~entry->mask[0]);
        fa_vcap_key_set(data, IS2_KO_X12_IGR_PORT_MASK_1, IS2_KL_X12_IGR_PORT_MASK_1, 0, ~entry->mask[1]);
        fa_vcap_key_set(data, IS2_KO_X12_IGR_PORT_MASK_2, IS2_KL_X12_IGR_PORT_MASK_2, 0, ~entry->mask[2]);
        fa_ace_key_bit_set(data, IS2_KO_X12_L2_MC, key->dmac_mc);
        fa_ace_key_bit_set(data, IS2_KO_X12_L2_BC, key->dmac_bc);
        fa_ace_key_bit_set(data, IS2_KO_X12_VLAN_TAGGED, key->vlan.tagged);
        fa_vcap_key_set(data, IS2_KO_X12_XVID, IS2_KL_X12_XVID, key->vlan.vid.value, key->vlan.vid.mask & 0xfff);
        fa_vcap_key_u3_set(data, IS2_KO_X12_PCP, &key->vlan.usr_prio);
        fa_ace_key_bit_set(data, IS2_KO_X12_DEI, key->vlan.cfi);
        if (entry->host_match) {
            /* Host match for IPv4 */
            fa_vcap_key_bit_set(data, IS2_KO_X12_L3_SMAC_SIP_MATCH, VTSS_VCAP_BIT_1);
        }
        /* Unused: IS2_KO_X12_L3_RT */
        /* Unused: IS2_KO_X12_L3_DST */
        fa_vcap_key_u48_set(data, IS2_KO_X12_L2_DMAC_0, &key->dmac);
        fa_vcap_key_u48_set(data, IS2_KO_X12_L2_SMAC_0, &key->smac);
        fa_vcap_key_bit_set(data, IS2_KO_IP_7TUPLE_IP4, ipv4 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        fa_ace_key_bit_set(data, IS2_KO_IP_7TUPLE_L3_TTL_GT0, ipv4 ? ipv4->ttl : ipv6->ttl);
        fa_vcap_key_u8_set(data, IS2_KO_IP_7TUPLE_L3_TOS, ipv4 ? &ipv4->ds : &ipv6->ds);
        if (ipv4) {
            /* IPv4 */
            VTSS_MEMSET(&sip, 0, sizeof(sip));
            VTSS_MEMSET(&dip, 0, sizeof(dip));
            if (ipv4->fragment != VTSS_ACE_BIT_ANY) {
                // DIP bit 126-127 is L3_FRAGMENT_TYPE
                m = (1 << 6);
                dip.value[0] |= (ipv4->fragment == VTSS_ACE_BIT_1 ? m : 0);
                dip.mask[0] |= m;
            }
            if (ipv4->options != VTSS_ACE_BIT_ANY) {
                // DIP bit 124 is L3_OPTIONS
                m = (1 << 4);
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
        fa_vcap_key_u128_set(data, IS2_KO_IP_7TUPLE_L3_IP6_DIP_0, &dip);
        fa_vcap_key_u128_set(data, IS2_KO_IP_7TUPLE_L3_IP6_SIP_0, &sip);
        if (vtss_vcap_udp_tcp_rule(proto)) {
            /* UDP/TCP protocol match */
            udp_tcp = VTSS_VCAP_BIT_1;
            tcp = (proto->value == 6 ? 1 : 0);
            fa_vcap_key_bit_set(data, IS2_KO_IP_7TUPLE_TCP, tcp ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            fa_vcap_key_set(data, IS2_KO_IP_7TUPLE_L4_DPORT, IS2_KL_IP_7TUPLE_L4_DPORT,
                            dport->low, fa_l4_port_mask(dport));
            fa_vcap_key_set(data, IS2_KO_IP_7TUPLE_L4_SPORT, IS2_KL_IP_7TUPLE_L4_SPORT,
                            sport->low, fa_l4_port_mask(sport));
            fa_vcap_key_set(data, IS2_KO_IP_7TUPLE_L4_RNG, IS2_KL_IP_7TUPLE_L4_RNG, l4_rng, l4_rng);
            if (tcp) {
                fa_ace_key_bit_set(data, IS2_KO_IP_7TUPLE_L4_FIN, ipv4 ? ipv4->tcp_fin : ipv6->tcp_fin);
                fa_ace_key_bit_set(data, IS2_KO_IP_7TUPLE_L4_SYN, ipv4 ? ipv4->tcp_syn : ipv6->tcp_syn);
                fa_ace_key_bit_set(data, IS2_KO_IP_7TUPLE_L4_RST, ipv4 ? ipv4->tcp_rst : ipv6->tcp_rst);
                fa_ace_key_bit_set(data, IS2_KO_IP_7TUPLE_L4_PSH, ipv4 ? ipv4->tcp_psh : ipv6->tcp_psh);
                fa_ace_key_bit_set(data, IS2_KO_IP_7TUPLE_L4_ACK, ipv4 ? ipv4->tcp_ack : ipv6->tcp_ack);
                fa_ace_key_bit_set(data, IS2_KO_IP_7TUPLE_L4_URG, ipv4 ? ipv4->tcp_urg : ipv6->tcp_urg);
            } else if (key->ptp.enable) {
                fa_is2_ptp_key_set(data, IS2_KO_IP_7TUPLE_L4_PAYLOAD_0, &key->ptp.header);
            }
        } else if (proto->mask == 0) {
            /* Any IP protocol match */
            udp_tcp = VTSS_VCAP_BIT_ANY;
        } else {
            /* Non-UDP/TCP protocol match */
            udp_tcp = VTSS_VCAP_BIT_0;
            fa_vcap_key_set(data, IS2_KO_IP_7TUPLE_L4_DPORT, IS2_KL_IP_7TUPLE_L4_DPORT,
                            proto->value, proto->mask);
            fa_vcap_key_u48_set(data, IS2_KO_IP_7TUPLE_L4_PAYLOAD_0 + 16, ipv4 ? &ipv4->data : &ipv6->data);
        }
        fa_vcap_key_bit_set(data, IS2_KO_IP_7TUPLE_TCP_UDP, udp_tcp);
        goto apply;
    }

    /* X6 rule */
    switch (key->type) {
    case VTSS_ACE_TYPE_ANY:
        for (i = 0; i < 6; i++) {
            if (key->dmac.mask[i] != 0 || key->smac.mask[i] != 0) {
                found = 1;
                break;
            }
        }
        if (found) {
            /* Match ETYPE/LLC/SNAP frames with DMAC/SMAC filtering */
            smac_dmac = 1;
        } else {
            /* Match all frames */
            mask = 0;
        }
        break;
    case VTSS_ACE_TYPE_ETYPE:
        smac_dmac = 1;
        fa_vcap_key_bit_set(data, IS2_KO_MAC_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_1);
        oam = (etype->etype.mask[0] == 0xff && etype->etype.mask[1] == 0xff ?
               (etype->etype.value[0] == 0x89 && etype->etype.value[1] == 0x02 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0) :
               VTSS_VCAP_BIT_ANY);
        fa_vcap_key_bit_set(data, IS2_KO_MAC_ETYPE_OAM_Y1731, oam);
        if (oam != VTSS_VCAP_BIT_1) {
            fa_vcap_key_u16_set(data, IS2_KO_MAC_ETYPE_ETYPE, &etype->etype);
        }
        if (key->ptp.enable) {
            fa_is2_ptp_key_set(data, IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0, &key->ptp.header);
        } else {
            fa_vcap_key_u16_set(data, IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0 + 48, &etype->data);
        }
        break;
    case VTSS_ACE_TYPE_LLC:
        smac_dmac = 1;
        fa_vcap_key_bit_set(data, IS2_KO_MAC_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_0);
        fa_vcap_key_u32_set(data, IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0 + 32, &llc->llc);
        break;
    case VTSS_ACE_TYPE_SNAP:
        smac_dmac = 1;
        fa_vcap_key_bit_set(data, IS2_KO_MAC_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_0);
        for (i = 0; i < 3; i++) {
            /* SNAP header */
            fa_vcap_key_set(data, IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0 + 40 + i*8, 8, i == 0 ? 0x03 : 0xaa, 0xff);
        }
        fa_vcap_key_u40_set(data, IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0, &snap->snap);
        break;
    case VTSS_ACE_TYPE_ARP:
        type = IS2_X6_TYPE_ARP;
        fa_vcap_key_u48_set(data, IS2_KO_ARP_L2_SMAC_0, &key->smac);
        fa_ace_key_bit_set(data, IS2_KO_ARP_ARP_ADDR_SPACE_OK, arp->ethernet);
        fa_ace_key_bit_set(data, IS2_KO_ARP_ARP_PROTO_SPACE_OK, arp->ip);
        fa_ace_key_bit_set(data, IS2_KO_ARP_ARP_LEN_OK, arp->length);
        fa_ace_key_bit_set(data, IS2_KO_ARP_ARP_TGT_MATCH, arp->dmac_match);
        fa_ace_key_bit_set(data, IS2_KO_ARP_ARP_SENDER_MATCH, arp->smac_match);
        fa_ace_key_bit_set(data, IS2_KO_ARP_ARP_OPCODE_UNKNOWN, arp->unknown);
        fa_ace_key_bit_inv_set(data, IS2_KO_ARP_ARP_OPCODE, arp->req);
        fa_ace_key_bit_inv_set(data, IS2_KO_ARP_ARP_OPCODE + 1, arp->arp);
        fa_vcap_key_ipv4_set(data, IS2_KO_ARP_L3_IP4_DIP, &arp->dip);
        fa_vcap_key_ipv4_set(data, IS2_KO_ARP_L3_IP4_SIP, &arp->sip);
        break;
    case VTSS_ACE_TYPE_IPV4:
    case VTSS_ACE_TYPE_IPV6:
        fa_ace_key_bit_set(data, IS2_KO_X6_L3_TTL_GT0, ipv4 ? ipv4->ttl : ipv6->ttl);
        fa_vcap_key_bit_set(data, IS2_KO_X6_IP4, ipv4 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        fa_vcap_key_u8_set(data, IS2_KO_X6_L3_TOS, ipv4 ? &ipv4->ds : &ipv6->ds);
        if (ipv4) {
            fa_ace_key_bit_set(data, IS2_KO_X6_L3_FRAGMENT_TYPE, ipv4->fragment);
            fa_ace_key_bit_set(data, IS2_KO_X6_L3_OPTIONS, ipv4->options);
            fa_vcap_key_ipv4_set(data, IS2_KO_X6_L3_IP4_DIP, &ipv4->dip);
            fa_vcap_key_ipv4_set(data, IS2_KO_X6_L3_IP4_SIP, &ipv4->sip);
        } else {
            fa_vcap_key_bytes_set(data, IS2_KO_X6_L3_IP4_DIP, &ipv6->sip.value[8], &ipv6->sip.mask[8], 4);
            fa_vcap_key_bytes_set(data, IS2_KO_X6_L3_IP4_SIP, &ipv6->sip.value[12], &ipv6->sip.mask[12], 4);
        }

        if (vtss_vcap_udp_tcp_rule(proto)) {
            /* UDP/TCP protocol match */
            type = IS2_X6_TYPE_IP4_TCP_UDP;
            tcp = (proto->value == 6 ? 1 : 0);
            fa_vcap_key_bit_set(data, IS2_KO_IP4_TCP_UDP_TCP, tcp ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            fa_vcap_key_set(data, IS2_KO_IP4_TCP_UDP_L4_DPORT, IS2_KL_IP4_TCP_UDP_L4_DPORT,
                            dport->low, fa_l4_port_mask(dport));
            fa_vcap_key_set(data, IS2_KO_IP4_TCP_UDP_L4_SPORT, IS2_KL_IP4_TCP_UDP_L4_SPORT,
                            sport->low, fa_l4_port_mask(sport));
            fa_vcap_key_set(data, IS2_KO_IP4_TCP_UDP_L4_RNG, IS2_KL_IP4_TCP_UDP_L4_RNG, l4_rng, l4_rng);
            if (tcp) {
                fa_ace_key_bit_set(data, IS2_KO_IP4_TCP_UDP_L4_FIN, ipv4 ? ipv4->tcp_fin : ipv6->tcp_fin);
                fa_ace_key_bit_set(data, IS2_KO_IP4_TCP_UDP_L4_SYN, ipv4 ? ipv4->tcp_syn : ipv6->tcp_syn);
                fa_ace_key_bit_set(data, IS2_KO_IP4_TCP_UDP_L4_RST, ipv4 ? ipv4->tcp_rst : ipv6->tcp_rst);
                fa_ace_key_bit_set(data, IS2_KO_IP4_TCP_UDP_L4_PSH, ipv4 ? ipv4->tcp_psh : ipv6->tcp_psh);
                fa_ace_key_bit_set(data, IS2_KO_IP4_TCP_UDP_L4_ACK, ipv4 ? ipv4->tcp_ack : ipv6->tcp_ack);
                fa_ace_key_bit_set(data, IS2_KO_IP4_TCP_UDP_L4_URG, ipv4 ? ipv4->tcp_urg : ipv6->tcp_urg);
            } else if (key->ptp.enable) {
                fa_is2_ptp_key_set(data, IS2_KO_IP4_TCP_UDP_L4_PAYLOAD_0, &key->ptp.header);
            }
        } else if (proto->mask == 0) {
            /* Any IP protocol match */
            type = IS2_X6_TYPE_IP4_TCP_UDP;
            mask = 0xe; /* Match type 4/5: 010X */
        } else {
            /* Non-UDP/TCP protocol match */
            type = IS2_X6_TYPE_IP4_OTHER;
            fa_vcap_key_u8_set(data, IS2_KO_IP4_OTHER_L3_PROTO, proto);
            fa_vcap_key_u48_set(data, IS2_KO_IP4_OTHER_L3_PAYLOAD_0 + 48, ipv4 ? &ipv4->data : &ipv6->data);
        }
        break;
    default:
        VTSS_E("unknown type: %u", key->type);
        return VTSS_RC_ERROR;
    }

    /* Common fields */
    fa_vcap_key_set(data, IS2_KO_X6_TYPE, IS2_KL_X6_TYPE, type, mask);
    fa_vcap_key_bit_set(data, IS2_KO_X6_FIRST, entry->first ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
    fa_vcap_key_u8_set(data, IS2_KO_X6_PAG, &key->policy);
    fa_vcap_key_bit_set(data, IS2_KO_X6_IGR_PORT_MASK_L3,
                        vcap_type == VTSS_VCAP_TYPE_IS2_B ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
    fa_vcap_key_set(data, IS2_KO_X6_IGR_PORT_MASK_RNG, IS2_KL_X6_IGR_PORT_MASK_RNG, entry->rng, VTSS_BITMASK(IS2_KL_X6_IGR_PORT_MASK_RNG));
    /* Unused: IS2_KO_X6_IGR_PORT_MASK_SEL */
    fa_vcap_key_set(data, IS2_KO_X6_IGR_PORT_MASK_0, IS2_KL_X6_IGR_PORT_MASK_0, 0, ~entry->mask[0]);
    fa_ace_key_bit_set(data, IS2_KO_X6_L2_MC, key->dmac_mc);
    fa_ace_key_bit_set(data, IS2_KO_X6_L2_BC, key->dmac_bc);
    /* Unused: IS2_KO_X6_SERVICE_FRM */
    /* Unused: IS2_KO_X6_ISDX */
    fa_ace_key_bit_set(data, IS2_KO_X6_VLAN_TAGGED, key->vlan.tagged);
    fa_vcap_key_set(data, IS2_KO_X6_XVID, IS2_KL_X6_XVID, key->vlan.vid.value, key->vlan.vid.mask & 0xfff);
    fa_vcap_key_u3_set(data, IS2_KO_X6_PCP, &key->vlan.usr_prio);
    fa_ace_key_bit_set(data, IS2_KO_X6_DEI, key->vlan.cfi);
    /* Unused: IS2_KO_X6_L2_FWD */
    if (entry->host_match) {
        /* Host match for IPv4 */
        fa_vcap_key_bit_set(data, IS2_KO_X6_L3_SMAC_SIP_MATCH, VTSS_VCAP_BIT_1);
    }
    /* Unused: IS2_KO_X6_L3_DMAC_DIP_MATCH */
    /* Unused: IS2_KO_X6_L3_RT */
    /* Unused: IS2_KO_X6_L3_DST */
    if (smac_dmac) {
        fa_vcap_key_u48_set(data, IS2_KO_MAC_ETYPE_L2_DMAC_0, &key->dmac);
        fa_vcap_key_u48_set(data, IS2_KO_MAC_ETYPE_L2_SMAC_0, &key->smac);
    }

apply:
    /* Setup action */
    data->vcap_type = vcap_type;
    VTSS_RC(fa_is2_action_set(vtss_state, data, &ace->action, is2->cnt_id, counter));
    if (vcap_type == VTSS_VCAP_TYPE_IS2_B && !entry->ipmc) {
        FA_ACT_SET(IS2, BASE_TYPE_RLEG_STAT_IDX, (entry->first ? FA_RLEG_STAT_IRACL : FA_RLEG_STAT_ERACL) + 1);
        if (entry->first) {
            FA_ACT_SET(IS2, BASE_TYPE_IGR_ACL_ENA, 1);
        } else {
            FA_ACT_SET(IS2, BASE_TYPE_EGR_ACL_ENA, 1);
        }
    }

    return fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ALL);
}

static vtss_rc fa_is2_entry_get(vtss_state_t *vtss_state, vtss_vcap_type_t type, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    fa_vcap_data_t data;
    u32            addr, cnt_id;

    VTSS_MEMSET(&data, 0, sizeof(data));
    data.vcap_type = type;
    data.tg = FA_VCAP_TG_X6;
    data.type = FA_VCAP_TG_X3;
    addr = fa_vcap_entry_addr(vtss_state, data.vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u", idx->row, idx->col, addr);
    VTSS_RC(fa_vcap_entry_cmd(vtss_state, &data, addr, data.tg, FA_VCAP_CMD_READ, FA_VCAP_SEL_ACTION));
    cnt_id = fa_act_get(&data, IS2_AO_BASE_TYPE_CNT_ID, IS2_AL_BASE_TYPE_CNT_ID);
    VTSS_RC(fa_is2_cnt_get(vtss_state, type, cnt_id, counter));
    return (clear ? fa_is2_cnt_set(vtss_state, type, cnt_id, 0) : VTSS_RC_OK);
}

static vtss_rc fa_is2_a_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return fa_is2_entry_add(vtss_state, VTSS_VCAP_TYPE_IS2, idx, vcap_data, counter);
}

static vtss_rc fa_is2_a_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return fa_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_IS2, idx);
}

static vtss_rc fa_is2_a_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return fa_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_IS2, idx, count, up);
}

static vtss_rc fa_is2_a_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return fa_is2_entry_get(vtss_state, VTSS_VCAP_TYPE_IS2, idx, counter, clear);
}

static vtss_rc fa_is2_b_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    return fa_is2_entry_add(vtss_state, VTSS_VCAP_TYPE_IS2_B, idx, vcap_data, counter);
}

static vtss_rc fa_is2_b_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return fa_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_IS2_B, idx);
}

static vtss_rc fa_is2_b_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return fa_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_IS2_B, idx, count, up);
}

static vtss_rc fa_is2_b_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return fa_is2_entry_get(vtss_state, VTSS_VCAP_TYPE_IS2_B, idx, counter, clear);
}

static vtss_rc fa_is2_entry_update(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_is2_data_t *is2)
{
#if VTSS_OPT_TRACE
    const fa_vcap_props_t *vcap = &fa_vcap_info[FA_VCAP_SUPER];
#endif
    fa_vcap_data_t        fa_data, *data = &fa_data;
    vtss_port_no_t        port_no;
    u32                   addr, port, member;

    data->vcap_type = VTSS_VCAP_TYPE_IS2;
    data->tg = FA_VCAP_TG_X1;
    addr = fa_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u", vcap->name, idx->row, idx->col, addr);

    /* Read action */
    VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_READ, FA_VCAP_SEL_ACTION));

    /* Update action fields */
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        member = (VTSS_PORT_BF_GET(is2->action.member, port_no) && vtss_state->l2.tx_forward_aggr[port_no]);
        fa_act_set(data, IS2_AO_BASE_TYPE_PORT_MASK_0 + port, 1, member);
    }

    /* Write action */
    return fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION);
}

static vtss_rc fa_debug_is2(vtss_state_t *vtss_state, fa_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 cnt_id, cnt, type;
    const               char *str;

    if (data->vcap_type != VTSS_VCAP_TYPE_IS2 && data->vcap_type != VTSS_VCAP_TYPE_IS2_B) {
        VTSS_E("not TYPE_IS2");
        return VTSS_RC_ERROR;
    }

    if (data->is_action) {
        FA_DEBUG_ACT(IS2, "is_inner_acl", BASE_TYPE_IS_INNER_ACL);
        FA_DEBUG_ACT_ENA(IS2, "pipeline_pt", BASE_TYPE_PIPELINE_FORCE_ENA, BASE_TYPE_PIPELINE_PT);
        FA_DEBUG_ACT(IS2, "hit_me_once", BASE_TYPE_HIT_ME_ONCE);
        FA_DEBUG_ACT(IS2, "intr_ena", BASE_TYPE_INTR_ENA);
        FA_DEBUG_ACT_ENA(IS2, "cpu_copy", BASE_TYPE_CPU_COPY_ENA, BASE_TYPE_CPU_QU_NUM);
        FA_DEBUG_ACT(IS2, "cpu_dis", BASE_TYPE_CPU_DIS);
        pr("\n");
        FA_DEBUG_ACT(IS2, "lrn_dis", BASE_TYPE_LRN_DIS);
        FA_DEBUG_ACT(IS2, "rt_dis", BASE_TYPE_RT_DIS);
        FA_DEBUG_ACT_ENA(IS2, "police", BASE_TYPE_POLICE_ENA, BASE_TYPE_POLICE_IDX);
        FA_DEBUG_ACT(IS2, "ignore_pipeline_ctrl", BASE_TYPE_IGNORE_PIPELINE_CTRL);
        FA_DEBUG_ACT(IS2, "dlb_offset/resv", BASE_TYPE_DLB_OFFSET);
        FA_DEBUG_ACT(IS2, "mask_mode", BASE_TYPE_MASK_MODE);
        pr("\n");
        fa_debug_bits(data, "port_mask", IS2_AO_BASE_TYPE_PORT_MASK_0, VTSS_CHIP_PORTS);
        FA_DEBUG_ACT_ENA(IS2, "rsdx", BASE_TYPE_RSDX_ENA, BASE_TYPE_RSDX_VAL);
        FA_DEBUG_ACT(IS2, "mirror_probe", BASE_TYPE_MIRROR_PROBE);
        FA_DEBUG_ACT_BITS(IS2, "rew_cmd", BASE_TYPE_REW_CMD);
        FA_DEBUG_ACT(IS2, "ttl_update_ena", BASE_TYPE_TTL_UPDATE_ENA);
        FA_DEBUG_ACT(IS2, "sam_seq_ena", BASE_TYPE_SAM_SEQ_ENA);
        pr("\n");
        FA_DEBUG_ACT(IS2, "tcp_udp_ena", BASE_TYPE_TCP_UDP_ENA);
        FA_DEBUG_ACT(IS2, "tcp_udp_dport", BASE_TYPE_TCP_UDP_DPORT);
        FA_DEBUG_ACT(IS2, "tcp_udp_sport", BASE_TYPE_TCP_UDP_SPORT);
        pr("\n");
        FA_DEBUG_ACT_BITS(IS2, "match_id", BASE_TYPE_MATCH_ID);
        FA_DEBUG_ACT_BITS(IS2, "match_id_mask", BASE_TYPE_MATCH_ID_MASK);
        FA_DEBUG_ACT(IS2, "swap_mac_ena", BASE_TYPE_SWAP_MAC_ENA);
        FA_DEBUG_ACT(IS2, "acl_rt_mode", BASE_TYPE_ACL_RT_MODE);
        pr("\n");
        fa_debug_bits(data, "acl_mac", IS2_AO_BASE_TYPE_ACL_MAC_0, 48);
        FA_DEBUG_ACT(IS2, "dmac_offset_ena", BASE_TYPE_DMAC_OFFSET_ENA);
        FA_DEBUG_ACT(IS2, "ptp_master_sel", BASE_TYPE_PTP_MASTER_SEL);
        FA_DEBUG_ACT(IS2, "log_msg_interval", BASE_TYPE_LOG_MSG_INTERVAL);
        FA_DEBUG_ACT(IS2, "sip_idx", BASE_TYPE_SIP_IDX);
        pr("\n");
        FA_DEBUG_ACT(IS2, "rleg_stat_idx", BASE_TYPE_RLEG_STAT_IDX);
        FA_DEBUG_ACT(IS2, "igr_acl_ena", BASE_TYPE_IGR_ACL_ENA);
        FA_DEBUG_ACT(IS2, "egr_acl_ena", BASE_TYPE_EGR_ACL_ENA);
        cnt_id = fa_act_get(data, IS2_AO_BASE_TYPE_CNT_ID, IS2_AL_BASE_TYPE_CNT_ID);
        VTSS_RC(fa_is2_cnt_get(vtss_state, data->vcap_type, cnt_id, &cnt));
        pr("\ncnt[%u]: %u, cnt: %u", cnt_id, cnt, data->counter);
        return VTSS_RC_OK;
    }

    /* Show key fields */
    if (data->tg == FA_VCAP_TG_X3) {
        FA_DEBUG_BITS(IS2, "first", IP4_VID_FIRST);
        FA_DEBUG_BITS(IS2, "pag", IP4_VID_PAG);
        FA_DEBUG_BITS(IS2, "service_frm", IP4_VID_SERVICE_FRM);
        FA_DEBUG_BITS(IS2, "isdx", IP4_VID_ISDX);
        pr("\n");
        FA_DEBUG_BITS(IS2, "xvid", IP4_VID_XVID);
        pr("\n");
        FA_DEBUG_BITS(IS2, "l3_smac_sip_match", IP4_VID_L3_SMAC_SIP_MATCH);
        FA_DEBUG_BITS(IS2, "l3_dmac_dip_match", IP4_VID_L3_DMAC_DIP_MATCH);
        FA_DEBUG_BITS(IS2, "l3_rt", IP4_VID_L3_RT);
        FA_DEBUG_BITS(IS2, "l3_dst", IP4_VID_L3_DST);
        pr("\n");
        FA_DEBUG_BITS(IS2, "l3_ip4_dip", IP4_VID_L3_IP4_DIP);
        FA_DEBUG_BITS(IS2, "l3_ip4_sip", IP4_VID_L3_IP4_SIP);
        pr("\n");
        return VTSS_RC_OK;
    }

    if (data->tg == FA_VCAP_TG_X12) {
        FA_DEBUG_BITS(IS2, "type", X12_TYPE);
        type = fa_entry_bs_get(data, IS2_KO_X12_TYPE, IS2_KL_X12_TYPE);
        if ((str = (type == IS2_X12_TYPE_IP6_TCP_UDP ? "ip6_tcp_udp" :
                    type == IS2_X12_TYPE_IP_7TUPLE ? "ip_7tuple" :
                    type == IS2_X12_TYPE_CUSTOM_1 ? "custom_1" : NULL)) == NULL) {
            return VTSS_RC_OK;
        }
        pr("(%s) ", fa_mask_bs_get(data, IS2_KO_X12_TYPE, IS2_KL_X12_TYPE) == 0 ? "any" : str);
        FA_DEBUG_BITS(IS2, "first", X12_FIRST);
        FA_DEBUG_BITS(IS2, "pag", X12_PAG);
        FA_DEBUG_BITS(IS2, "igr_port_mask_l3", X12_IGR_PORT_MASK_L3);
        FA_DEBUG_BITS(IS2, "igr_port_mask_rng", X12_IGR_PORT_MASK_RNG);
        pr("\n");
        FA_DEBUG_BITS(IS2, "igr_port_mask_sel", X12_IGR_PORT_MASK_SEL);
        FA_DEBUG_BITS(IS2, "igr_port_mask", X12_IGR_PORT_MASK_0);
        FA_DEBUG_BITS(IS2, "l2_mc", X12_L2_MC);
        FA_DEBUG_BITS(IS2, "l2_bc", X12_L2_BC);
        FA_DEBUG_BITS(IS2, "vlan_tagged", X12_VLAN_TAGGED);
        FA_DEBUG_BITS(IS2, "service_frm", X12_SERVICE_FRM);
        FA_DEBUG_BITS(IS2, "isdx", X12_ISDX);
        pr("\n");
        FA_DEBUG_BITS(IS2, "xvid", X12_XVID);
        FA_DEBUG_BITS(IS2, "pcp", X12_PCP);
        FA_DEBUG_BITS(IS2, "dei", X12_DEI);
        FA_DEBUG_BITS(IS2, "l2_fwd", X12_L2_FWD);
        pr("\n");
        FA_DEBUG_BITS(IS2, "l3_smac_sip_match", X12_L3_SMAC_SIP_MATCH);
        FA_DEBUG_BITS(IS2, "l3_dmac_dip_match", X12_L3_DMAC_DIP_MATCH);
        FA_DEBUG_BITS(IS2, "l3_rt", X12_L3_RT);
        FA_DEBUG_BITS(IS2, "l3_dst", X12_L3_DST);
        pr("\n");
        if (type > IS2_X12_TYPE_IP_7TUPLE) {
            return VTSS_RC_OK;
        }

        FA_DEBUG_MAC(IS2, "dmac", X12_L2_DMAC_0);
        FA_DEBUG_MAC(IS2, "smac", X12_L2_SMAC_0);
        if (type != IS2_X12_TYPE_IP_7TUPLE) {
            return VTSS_RC_OK;
        }

        FA_DEBUG_BITS(IS2, "ip4", IP_7TUPLE_IP4);
        FA_DEBUG_BITS(IS2, "l3_ttl_gt0", IP_7TUPLE_L3_TTL_GT0);
        FA_DEBUG_BITS(IS2, "l3_tos", IP_7TUPLE_L3_TOS);
        FA_DEBUG_BITS(IS2, "dip_eq_sip", IP_7TUPLE_DIP_EQ_SIP);
        FA_DEBUG_BITS(IS2, "tcp_udp", IP_7TUPLE_TCP_UDP);
        FA_DEBUG_BITS(IS2, "tcp", IP_7TUPLE_TCP);
        pr("\n");
        FA_DEBUG_IPV6(IS2, "l3_ip6_dip", IP_7TUPLE_L3_IP6_DIP_0);
        FA_DEBUG_IPV6(IS2, "l3_ip6_sip", IP_7TUPLE_L3_IP6_SIP_0);

        FA_DEBUG_BITS(IS2, "l4_dport", IP_7TUPLE_L4_DPORT);
        FA_DEBUG_BITS(IS2, "l4_sport", IP_7TUPLE_L4_SPORT);
        FA_DEBUG_BITS(IS2, "l4_rng", IP_7TUPLE_L4_RNG);
        pr("\n");
        FA_DEBUG_BITS(IS2, "sport_eq_dport", IP_7TUPLE_SPORT_EQ_DPORT);
        FA_DEBUG_BITS(IS2, "sequence_eq0", IP_7TUPLE_SEQUENCE_EQ0);
        FA_DEBUG_BITS(IS2, "l4_fin", IP_7TUPLE_L4_FIN);
        FA_DEBUG_BITS(IS2, "l4_syn", IP_7TUPLE_L4_SYN);
        FA_DEBUG_BITS(IS2, "l4_rst", IP_7TUPLE_L4_RST);
        FA_DEBUG_BITS(IS2, "l4_psh", IP_7TUPLE_L4_PSH);
        FA_DEBUG_BITS(IS2, "l4_ack", IP_7TUPLE_L4_ACK);
        FA_DEBUG_BITS(IS2, "l4_urg", IP_7TUPLE_L4_URG);
        pr("\n");
        FA_DEBUG_BITS_64(IS2, "l4_payload", IP_7TUPLE_L4_PAYLOAD_0);
        return VTSS_RC_OK;
    }

    if (data->tg != FA_VCAP_TG_X6) {
        VTSS_E("not TG_X6: %u", data->tg);
        return VTSS_RC_ERROR;
    }

    FA_DEBUG_BITS(IS2, "type", X6_TYPE);
    type = fa_entry_bs_get(data, IS2_KO_X6_TYPE, IS2_KL_X6_TYPE);
    if ((str = (type == IS2_X6_TYPE_MAC_ETYPE ? "etype" :
                type == IS2_X6_TYPE_ARP ? "arp" :
                type == IS2_X6_TYPE_IP4_TCP_UDP ? "ip4_tcp_udp" :
                type == IS2_X6_TYPE_IP4_OTHER ? "ip4_other" :
                type == IS2_X6_TYPE_IP6_VID ? "ip6_vid" : NULL)) == NULL) {
        return VTSS_RC_OK;
    }

    pr("(%s) ", fa_mask_bs_get(data, IS2_KO_X6_TYPE, IS2_KL_X6_TYPE) == 0 ? "any" : str);
    FA_DEBUG_BITS(IS2, "first", X6_FIRST);
    FA_DEBUG_BITS(IS2, "pag", X6_PAG);

    if (type == IS2_X6_TYPE_IP6_VID) {
        FA_DEBUG_BITS(IS2, "service_frm", IP6_VID_SERVICE_FRM);
        FA_DEBUG_BITS(IS2, "isdx", IP6_VID_ISDX);
        pr("\n");
        FA_DEBUG_BITS(IS2, "xvid", IP6_VID_XVID);
        pr("\n");
        FA_DEBUG_BITS(IS2, "l3_smac_sip_match", IP6_VID_L3_SMAC_SIP_MATCH);
        FA_DEBUG_BITS(IS2, "l3_dmac_dip_match", IP6_VID_L3_DMAC_DIP_MATCH);
        FA_DEBUG_BITS(IS2, "l3_rt", IP6_VID_L3_RT);
        FA_DEBUG_BITS(IS2, "l3_dst", IP6_VID_L3_DST);
        pr("\n");
        FA_DEBUG_IPV6(IS2, "l3_ip6_dip", IP6_VID_L3_IP6_DIP_0);
        FA_DEBUG_IPV6(IS2, "l3_ip6_sip", IP6_VID_L3_IP6_SIP_0);
        return VTSS_RC_OK;
    }

    FA_DEBUG_BITS(IS2, "igr_port_mask_l3", X6_IGR_PORT_MASK_L3);
    FA_DEBUG_BITS(IS2, "igr_port_mask_rng", X6_IGR_PORT_MASK_RNG);
    pr("\n");
    FA_DEBUG_BITS(IS2, "igr_port_mask_sel", X6_IGR_PORT_MASK_SEL);
    FA_DEBUG_BITS(IS2, "igr_port_mask", X6_IGR_PORT_MASK_0);
    FA_DEBUG_BITS(IS2, "l2_mc", X6_L2_MC);
    FA_DEBUG_BITS(IS2, "l2_bc", X6_L2_BC);
    FA_DEBUG_BITS(IS2, "vlan_tagged", X6_VLAN_TAGGED);
    FA_DEBUG_BITS(IS2, "service_frm", X6_SERVICE_FRM);
    FA_DEBUG_BITS(IS2, "isdx", X6_ISDX);
    pr("\n");
    FA_DEBUG_BITS(IS2, "xvid", X6_XVID);
    FA_DEBUG_BITS(IS2, "pcp", X6_PCP);
    FA_DEBUG_BITS(IS2, "dei", X6_DEI);
    FA_DEBUG_BITS(IS2, "l2_fwd", X6_L2_FWD);
    pr("\n");
    if (type == IS2_X6_TYPE_ARP) {
        FA_DEBUG_MAC(IS2, "smac", ARP_L2_SMAC_0);
        FA_DEBUG_BITS(IS2, "addr_space_ok", ARP_ARP_ADDR_SPACE_OK);
        FA_DEBUG_BITS(IS2, "proto_space_ok", ARP_ARP_PROTO_SPACE_OK);
        FA_DEBUG_BITS(IS2, "len_ok", ARP_ARP_LEN_OK);
        FA_DEBUG_BITS(IS2, "tgt_match", ARP_ARP_TGT_MATCH);
        FA_DEBUG_BITS(IS2, "sender_match", ARP_ARP_SENDER_MATCH);
        FA_DEBUG_BITS(IS2, "opcode_unknown", ARP_ARP_OPCODE_UNKNOWN);
        FA_DEBUG_BITS(IS2, "opcode", ARP_ARP_OPCODE);
        pr("\n");
        FA_DEBUG_BITS(IS2, "l3_ip4_dip", ARP_L3_IP4_DIP);
        FA_DEBUG_BITS(IS2, "l3_ip4_sip", ARP_L3_IP4_SIP);
        FA_DEBUG_BITS(IS2, "dip_eq_sip", ARP_DIP_EQ_SIP);
        FA_DEBUG_BITS(IS2, "l4_rng", ARP_L4_RNG);
        return VTSS_RC_OK;
    }

    FA_DEBUG_BITS(IS2, "l3_smac_sip_match", X6_L3_SMAC_SIP_MATCH);
    FA_DEBUG_BITS(IS2, "l3_dmac_dip_match", X6_L3_DMAC_DIP_MATCH);
    FA_DEBUG_BITS(IS2, "l3_rt", X6_L3_RT);
    FA_DEBUG_BITS(IS2, "l3_dst", X6_L3_DST);
    pr("\n");
    if (type == IS2_X6_TYPE_MAC_ETYPE) {
        FA_DEBUG_MAC(IS2, "dmac", MAC_ETYPE_L2_DMAC_0);
        FA_DEBUG_MAC(IS2, "smac", MAC_ETYPE_L2_SMAC_0);
        FA_DEBUG_BITS(IS2, "etype_len", MAC_ETYPE_ETYPE_LEN);
        FA_DEBUG_BITS(IS2, "etype", MAC_ETYPE_ETYPE);
        pr("\n");
        FA_DEBUG_BITS_64(IS2, "l2_payload", MAC_ETYPE_L2_PAYLOAD_ETYPE_0);
        return VTSS_RC_OK;
    }

    FA_DEBUG_BITS(IS2, "ip4", X6_IP4);
    FA_DEBUG_BITS(IS2, "l3_fragment_type", X6_L3_FRAGMENT_TYPE);
    FA_DEBUG_BITS(IS2, "l3_frag_invld_l4_len", X6_L3_FRAG_INVLD_L4_LEN);
    FA_DEBUG_BITS(IS2, "l3_options", X6_L3_OPTIONS);
    FA_DEBUG_BITS(IS2, "l3_ttl_gt0", X6_L3_TTL_GT0);
    FA_DEBUG_BITS(IS2, "l3_tos", X6_L3_TOS);
    pr("\n");
    FA_DEBUG_BITS(IS2, "l3_ip4_dip", X6_L3_IP4_DIP);
    FA_DEBUG_BITS(IS2, "l3_ip4_sip", X6_L3_IP4_SIP);
    FA_DEBUG_BITS(IS2, "dip_eq_sip", X6_DIP_EQ_SIP);
    if (type == IS2_X6_TYPE_IP4_OTHER) {
        FA_DEBUG_BITS(IS2, "l3_proto", IP4_OTHER_L3_PROTO);
        FA_DEBUG_BITS(IS2, "l4_rng", IP4_OTHER_L4_RNG);
        pr("\n");
        FA_DEBUG_BITS_96(IS2, "l3_payload", IP4_OTHER_L3_PAYLOAD_0);
    } else {
        /* IS2_X6_TYPE_IP4_TCP_UDP */
        FA_DEBUG_BITS(IS2, "tcp", IP4_TCP_UDP_TCP);
        FA_DEBUG_BITS(IS2, "l4_dport", IP4_TCP_UDP_L4_DPORT);
        FA_DEBUG_BITS(IS2, "l4_sport", IP4_TCP_UDP_L4_SPORT);
        FA_DEBUG_BITS(IS2, "l4_rng", IP4_TCP_UDP_L4_RNG);
        pr("\n");
        FA_DEBUG_BITS(IS2, "sport_eq_dport", IP4_TCP_UDP_SPORT_EQ_DPORT);
        FA_DEBUG_BITS(IS2, "sequence_eq0", IP4_TCP_UDP_SEQUENCE_EQ0);
        FA_DEBUG_BITS(IS2, "l4_fin", IP4_TCP_UDP_L4_FIN);
        FA_DEBUG_BITS(IS2, "l4_syn", IP4_TCP_UDP_L4_SYN);
        FA_DEBUG_BITS(IS2, "l4_rst", IP4_TCP_UDP_L4_RST);
        FA_DEBUG_BITS(IS2, "l4_psh", IP4_TCP_UDP_L4_PSH);
        FA_DEBUG_BITS(IS2, "l4_ack", IP4_TCP_UDP_L4_ACK);
        FA_DEBUG_BITS(IS2, "l4_urg", IP4_TCP_UDP_L4_URG);
        pr("\n");
        FA_DEBUG_BITS_64(IS2, "l4_payload", IP4_TCP_UDP_L4_PAYLOAD_0);
    }
    return VTSS_RC_OK;
}

/* - ES2 ----------------------------------------------------------- */

static vtss_rc fa_es2_cnt_get(vtss_state_t *vtss_state, u32 cnt_id, u32 *counter)
{
    REG_RD(VTSS_EACL_ES2_CNT(cnt_id), counter);
    return VTSS_RC_OK;
}

static vtss_rc fa_es2_cnt_set(vtss_state_t *vtss_state, u32 cnt_id, u32 counter)
{
    REG_WR(VTSS_EACL_ES2_CNT(cnt_id), counter);
    return VTSS_RC_OK;
}

static vtss_rc fa_es2_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    fa_vcap_data_t          fa_data, *data = &fa_data;
    vtss_is2_data_t         *is2 = &vcap_data->u.is2;
    vtss_is2_entry_t        *entry = is2->entry;
    vtss_hace_t             *ace = &entry->ace;
    vtss_hace_key_t         *key = &ace->key;
    vtss_hace_frame_etype_t *etype = &key->etype;
    vtss_hace_frame_llc_t   *llc = &key->llc;
    vtss_hace_frame_snap_t  *snap = &key->snap;
    vtss_hace_frame_arp_t   *arp = &key->arp;
    vtss_hace_frame_ipv4_t  *ipv4 = NULL;
    vtss_hace_frame_ipv6_t  *ipv6 = &key->ipv6;
    vtss_vcap_u8_t          *proto = NULL;
    vtss_vcap_udp_tcp_t     *sport, *dport;
    u32                     addr, i, l4_rng;
    u32                     type = ES2_X6_TYPE_MAC_ETYPE;
    u32                     mask = VTSS_BITMASK(ES2_KL_X6_TYPE);
    vtss_vcap_bit_t         oam;
    BOOL                    tcp, found = 0, smac_dmac = 0;

    addr = fa_vcap_entry_addr(vtss_state, VTSS_VCAP_TYPE_ES2, idx);
    VTSS_I("row: %u, col: %u, addr: %u, type: %u", idx->row, idx->col, addr, key->type);

    /* X6 rule */
    VTSS_MEMSET(data, 0, sizeof(*data));
    data->tg = FA_VCAP_TG_X6;
    data->vcap_type = VTSS_VCAP_TYPE_ES2;
    switch (key->type) {
    case VTSS_ACE_TYPE_ANY:
        for (i = 0; i < 6; i++) {
            if (key->dmac.mask[i] != 0 || key->smac.mask[i] != 0) {
                found = 1;
                break;
            }
        }
        if (found) {
            /* Match ETYPE/LLC/SNAP frames with DMAC/SMAC filtering */
            smac_dmac = 1;
        } else {
            /* Match all frames */
            mask = 0;
        }
        break;
    case VTSS_ACE_TYPE_ETYPE:
        smac_dmac = 1;
        fa_vcap_key_bit_set(data, ES2_KO_MAC_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_1);
        oam = (etype->etype.mask[0] == 0xff && etype->etype.mask[1] == 0xff ?
               (etype->etype.value[0] == 0x89 && etype->etype.value[1] == 0x02 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0) :
               VTSS_VCAP_BIT_ANY);
        fa_vcap_key_bit_set(data, ES2_KO_MAC_ETYPE_OAM_Y1731, oam);
        if (oam != VTSS_VCAP_BIT_1) {
            fa_vcap_key_u16_set(data, ES2_KO_MAC_ETYPE_ETYPE, &etype->etype);
        }
        fa_vcap_key_u16_set(data, ES2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0 + 48, &etype->data);
        break;
    case VTSS_ACE_TYPE_LLC:
        smac_dmac = 1;
        fa_vcap_key_bit_set(data, ES2_KO_MAC_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_0);
        fa_vcap_key_u32_set(data, ES2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0 + 32, &llc->llc);
        break;
    case VTSS_ACE_TYPE_SNAP:
        smac_dmac = 1;
        fa_vcap_key_bit_set(data, ES2_KO_MAC_ETYPE_ETYPE_LEN, VTSS_VCAP_BIT_0);
        for (i = 0; i < 3; i++) {
            /* SNAP header */
            fa_vcap_key_set(data, ES2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0 + 40 + i*8, 8, i == 0 ? 0x03 : 0xaa, 0xff);
        }
        fa_vcap_key_u40_set(data, ES2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0, &snap->snap);
        break;
    case VTSS_ACE_TYPE_ARP:
        type = ES2_X6_TYPE_ARP;
        fa_vcap_key_u48_set(data, ES2_KO_ARP_L2_SMAC_0, &key->smac);
        fa_ace_key_bit_set(data, ES2_KO_ARP_ARP_ADDR_SPACE_OK, arp->ethernet);
        fa_ace_key_bit_set(data, ES2_KO_ARP_ARP_PROTO_SPACE_OK, arp->ip);
        fa_ace_key_bit_set(data, ES2_KO_ARP_ARP_LEN_OK, arp->length);
        /* Unused: ES2_KO_ARP_ARP_TGT_MATCH, differs from IS2 functionality */
        fa_ace_key_bit_set(data, ES2_KO_ARP_ARP_SENDER_MATCH, arp->smac_match);
        fa_ace_key_bit_set(data, ES2_KO_ARP_ARP_OPCODE_UNKNOWN, arp->unknown);
        fa_ace_key_bit_inv_set(data, ES2_KO_ARP_ARP_OPCODE, arp->req);
        fa_ace_key_bit_inv_set(data, ES2_KO_ARP_ARP_OPCODE + 1, arp->arp);
        fa_vcap_key_ipv4_set(data, ES2_KO_ARP_L3_IP4_DIP, &arp->dip);
        fa_vcap_key_ipv4_set(data, ES2_KO_ARP_L3_IP4_SIP, &arp->sip);
        break;
    case VTSS_ACE_TYPE_IPV4:
    case VTSS_ACE_TYPE_IPV6:
        if (key->type == VTSS_ACE_TYPE_IPV4) {
            /* IPv4 */
            ipv4 = &key->ipv4;
            proto = &ipv4->proto;
            sport = &ipv4->sport;
            dport = &ipv4->dport;
            fa_ace_key_bit_set(data, ES2_KO_X6_L3_FRAGMENT_TYPE, ipv4->fragment);
            fa_ace_key_bit_set(data, ES2_KO_X6_L3_OPTIONS, ipv4->options);
            fa_vcap_key_ipv4_set(data, ES2_KO_X6_L3_IP4_DIP, &ipv4->dip);
            fa_vcap_key_ipv4_set(data, ES2_KO_X6_L3_IP4_SIP, &ipv4->sip);
        } else {
            /* IPv6 */
            proto = &ipv6->proto;
            sport = &ipv6->sport;
            dport = &ipv6->dport;
            /* Unused: ES2_KO_X6_L3_IP4_DIP, matches DIP[31:0] */
            fa_vcap_key_bytes_set(data, ES2_KO_X6_L3_IP4_SIP, &ipv6->sip.value[12], &ipv6->sip.mask[12], 4);
        }
        fa_ace_key_bit_set(data, ES2_KO_X6_L3_TTL_GT0, ipv4 ? ipv4->ttl : ipv6->ttl);
        fa_vcap_key_bit_set(data, ES2_KO_X6_IP4, ipv4 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        fa_vcap_key_u8_set(data, ES2_KO_X6_L3_TOS, ipv4 ? &ipv4->ds : &ipv6->ds);

        if (vtss_vcap_udp_tcp_rule(proto)) {
            /* UDP/TCP protocol match */
            type = ES2_X6_TYPE_IP4_TCP_UDP;
            tcp = (proto->value == 6 ? 1 : 0);
            fa_vcap_key_bit_set(data, ES2_KO_IP4_TCP_UDP_TCP, tcp ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            fa_vcap_key_set(data, ES2_KO_IP4_TCP_UDP_L4_DPORT, ES2_KL_IP4_TCP_UDP_L4_DPORT,
                            dport->low, fa_l4_port_mask(dport));
            fa_vcap_key_set(data, ES2_KO_IP4_TCP_UDP_L4_SPORT, ES2_KL_IP4_TCP_UDP_L4_SPORT,
                            sport->low, fa_l4_port_mask(sport));
            l4_rng = ((is2->srange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->srange)) |
                      (is2->drange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->drange)));
            fa_vcap_key_set(data, ES2_KO_IP4_TCP_UDP_L4_RNG, ES2_KL_IP4_TCP_UDP_L4_RNG, l4_rng, l4_rng);
            if (tcp) {
                fa_ace_key_bit_set(data, ES2_KO_IP4_TCP_UDP_L4_FIN, ipv4 ? ipv4->tcp_fin : ipv6->tcp_fin);
                fa_ace_key_bit_set(data, ES2_KO_IP4_TCP_UDP_L4_SYN, ipv4 ? ipv4->tcp_syn : ipv6->tcp_syn);
                fa_ace_key_bit_set(data, ES2_KO_IP4_TCP_UDP_L4_RST, ipv4 ? ipv4->tcp_rst : ipv6->tcp_rst);
                fa_ace_key_bit_set(data, ES2_KO_IP4_TCP_UDP_L4_PSH, ipv4 ? ipv4->tcp_psh : ipv6->tcp_psh);
                fa_ace_key_bit_set(data, ES2_KO_IP4_TCP_UDP_L4_ACK, ipv4 ? ipv4->tcp_ack : ipv6->tcp_ack);
                fa_ace_key_bit_set(data, ES2_KO_IP4_TCP_UDP_L4_URG, ipv4 ? ipv4->tcp_urg : ipv6->tcp_urg);
            }
        } else if (proto->mask == 0) {
            /* Any IP protocol match */
            type = ES2_X6_TYPE_IP4_TCP_UDP;
            mask = 0x6; /* Match type 2/3: 01X */
        } else {
            /* Non-UDP/TCP protocol match */
            type = ES2_X6_TYPE_IP4_OTHER;
            fa_vcap_key_u8_set(data, ES2_KO_IP4_OTHER_L3_IP_PROTO, proto);
            fa_vcap_key_u48_set(data, ES2_KO_IP4_OTHER_L3_PAYLOAD_0 + 48, ipv4 ? &ipv4->data : &ipv6->data);
        }
        break;
    default:
        VTSS_E("unknown type: %u", key->type);
        return VTSS_RC_ERROR;
    }

    /* Common fields */
    fa_vcap_key_set(data, ES2_KO_X6_TYPE, ES2_KL_X6_TYPE, type, mask);
    fa_vcap_key_bit_set(data, ES2_KO_X6_FIRST, entry->first ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
    /* Unused: ES2_KO_X6_ACL_GRP_ID */
    /* Unused: ES2_KO_X6_PROT_ACTIVE */
    fa_ace_key_bit_set(data, ES2_KO_X6_L2_MC, key->dmac_mc);
    fa_ace_key_bit_set(data, ES2_KO_X6_L2_BC, key->dmac_bc);
    /* Unused: ES2_KO_X6_SERVICE_FRM */
    /* Unused: ES2_KO_X6_ISDX */
    fa_vcap_key_set(data, ES2_KO_X6_EGR_PORT_MASK_RNG, ES2_KL_X6_EGR_PORT_MASK_RNG, entry->rng, VTSS_BITMASK(ES2_KL_X6_EGR_PORT_MASK_RNG));
    /* Unused: ES2_KO_X6_EGR_PORT_MASK_SEL */
    fa_vcap_key_set(data, ES2_KO_X6_EGR_PORT_MASK, ES2_KL_X6_EGR_PORT_MASK, 0, ~entry->mask[0]);
    fa_ace_key_bit_set(data, ES2_KO_X6_VLAN_TAGGED, key->vlan.tagged);
    fa_vcap_key_set(data, ES2_KO_X6_XVID, ES2_KL_X6_XVID, key->vlan.vid.value, key->vlan.vid.mask & 0xfff);
    fa_vcap_key_u3_set(data, ES2_KO_X6_PCP, &key->vlan.usr_prio);
    fa_ace_key_bit_set(data, ES2_KO_X6_DEI, key->vlan.cfi);
    /* Unused: ES2_KO_X6_COSID */
    /* Unused: ES2_KO_X6_COLOR */
    /* Unused: ES2_KO_X6_L3_RT */
    /* Unused: ES2_KO_X6_ES0_ISDX_KEY_ENA */
    /* Unused: ES2_KO_X6_MIRROR_PROBE */

    if (smac_dmac) {
        fa_vcap_key_u48_set(data, ES2_KO_MAC_ETYPE_L2_DMAC_0, &key->dmac);
        fa_vcap_key_u48_set(data, ES2_KO_MAC_ETYPE_L2_SMAC_0, &key->smac);
    }

    /* Setup action */
    data->type = FA_VCAP_TG_X3;
    FA_ACT_SET(ES2, BASE_TYPE_FWD_MODE, ace->action.port_action == VTSS_ACL_PORT_ACTION_NONE ? 0 : 1);
    FA_ACT_SET(ES2, BASE_TYPE_CNT_ID, is2->cnt_id);
    VTSS_RC(fa_es2_cnt_set(vtss_state, is2->cnt_id, counter));

    return fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ALL);
}

static vtss_rc fa_es2_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return fa_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_ES2, idx);
}

static vtss_rc fa_es2_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return fa_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_ES2, idx, count, up);
}

static vtss_rc fa_es2_entry_get(vtss_state_t *vtss_state,
                                vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    fa_vcap_data_t data;
    u32            addr, cnt_id;

    VTSS_MEMSET(&data, 0, sizeof(data));
    data.vcap_type = VTSS_VCAP_TYPE_ES2;
    data.tg = FA_VCAP_TG_X6;
    data.type = FA_VCAP_TG_X3;
    addr = fa_vcap_entry_addr(vtss_state, data.vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u", idx->row, idx->col, addr);
    VTSS_RC(fa_vcap_entry_cmd(vtss_state, &data, addr, data.tg, FA_VCAP_CMD_READ, FA_VCAP_SEL_ACTION));
    cnt_id = fa_act_get(&data, ES2_AO_BASE_TYPE_CNT_ID, ES2_AL_BASE_TYPE_CNT_ID);
    VTSS_RC(fa_es2_cnt_get(vtss_state, cnt_id, counter));
    return (clear ? fa_es2_cnt_set(vtss_state, cnt_id, 0) : VTSS_RC_OK);
}

static vtss_rc fa_debug_es2(vtss_state_t *vtss_state, fa_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 cnt_id, cnt, type;
    const               char *str;

    if (data->vcap_type != VTSS_VCAP_TYPE_ES2) {
        VTSS_E("not TYPE_ES2");
        return VTSS_RC_ERROR;
    }

    if (data->is_action) {
        FA_DEBUG_ACT(ES2, "hit_me_once", BASE_TYPE_HIT_ME_ONCE);
        FA_DEBUG_ACT(ES2, "intr_ena", BASE_TYPE_INTR_ENA);
        FA_DEBUG_ACT(ES2, "fwd_mode", BASE_TYPE_FWD_MODE);
        FA_DEBUG_ACT(ES2, "copy_queue", BASE_TYPE_COPY_QUEUE_NUM);
        FA_DEBUG_ACT(ES2, "copy_port", BASE_TYPE_COPY_PORT_NUM);
        FA_DEBUG_ACT(ES2, "mirror_probe", BASE_TYPE_MIRROR_PROBE_ID);
        FA_DEBUG_ACT_ENA(ES2, "cpu_copy", BASE_TYPE_CPU_COPY, BASE_TYPE_CPU_QUEUE_NUM);
        pr("\n");
        FA_DEBUG_ACT_ENA(ES2, "police", BASE_TYPE_POLICE_ENA, BASE_TYPE_POLICE_IDX);
        FA_DEBUG_ACT(ES2, "police_remark", BASE_TYPE_POLICE_REMARK);
        FA_DEBUG_ACT(ES2, "rew_cmd", BASE_TYPE_ES2_REW_CMD);
        FA_DEBUG_ACT(ES2, "ignore_pipeline_ctrl", BASE_TYPE_IGNORE_PIPELINE_CTRL);
        cnt_id = fa_act_get(data, ES2_AO_BASE_TYPE_CNT_ID, ES2_AL_BASE_TYPE_CNT_ID);
        VTSS_RC(fa_es2_cnt_get(vtss_state, cnt_id, &cnt));
        pr("\ncnt[%u]: %u, cnt: %u", cnt_id, cnt, data->counter);
        return VTSS_RC_OK;
    }

    /* Show key fields */
    if (data->tg == FA_VCAP_TG_X3) {
        pr("\n");
        return VTSS_RC_OK;
    }
    if (data->tg != FA_VCAP_TG_X6) {
        VTSS_E("not TG_X6: %u", data->tg);
        return VTSS_RC_ERROR;
    }

    FA_DEBUG_BITS(ES2, "type", X6_TYPE);
    type = fa_entry_bs_get(data, ES2_KO_X6_TYPE, ES2_KL_X6_TYPE);
    if ((str = (type == ES2_X6_TYPE_MAC_ETYPE ? "etype" :
                type == ES2_X6_TYPE_ARP ? "arp" :
                type == ES2_X6_TYPE_IP4_TCP_UDP ? "ip4_tcp_udp" :
                type == ES2_X6_TYPE_IP4_OTHER ? "ip4_other" : NULL)) == NULL) {
        return VTSS_RC_OK;
    }

    pr("(%s) ", fa_mask_bs_get(data, ES2_KO_X6_TYPE, ES2_KL_X6_TYPE) == 0 ? "any" : str);
    FA_DEBUG_BITS(ES2, "first", X6_FIRST);
    FA_DEBUG_BITS(ES2, "acl_grp_id", X6_ACL_GRP_ID);
    FA_DEBUG_BITS(ES2, "prot_active", X6_PROT_ACTIVE);
    FA_DEBUG_BITS(ES2, "l2_mc", X6_L2_MC);
    FA_DEBUG_BITS(ES2, "l2_bc", X6_L2_BC);
    pr("\n");
    FA_DEBUG_BITS(ES2, "service_frm", X6_SERVICE_FRM);
    FA_DEBUG_BITS(ES2, "isdx", X6_ISDX);
    FA_DEBUG_BITS(ES2, "vlan_tagged", X6_VLAN_TAGGED);
    FA_DEBUG_BITS(ES2, "xvid", X6_XVID);
    FA_DEBUG_BITS(ES2, "pcp", X6_PCP);
    FA_DEBUG_BITS(ES2, "dei", X6_DEI);
    pr("\n");
    FA_DEBUG_BITS(ES2, "egr_port_mask_rng", X6_EGR_PORT_MASK_RNG);
    FA_DEBUG_BITS(ES2, "egr_port_mask", X6_EGR_PORT_MASK);
    FA_DEBUG_BITS(ES2, "igr_port_sel", X6_IGR_PORT_SEL);
    FA_DEBUG_BITS(ES2, "igr_port", X6_IGR_PORT);
    FA_DEBUG_BITS(ES2, "cosid", X6_COSID);
    FA_DEBUG_BITS(ES2, "color", X6_COLOR);
    if (type == ES2_X6_TYPE_ARP) {
        FA_DEBUG_BITS(ES2, "es0_isdx_key_ena", ARP_ES0_ISDX_KEY_ENA);
        FA_DEBUG_BITS(ES2, "mirror_probe", ARP_MIRROR_PROBE);
        pr("\n");
        FA_DEBUG_MAC(ES2, "smac", ARP_L2_SMAC_0);
        FA_DEBUG_BITS(ES2, "addr_space_ok", ARP_ARP_ADDR_SPACE_OK);
        FA_DEBUG_BITS(ES2, "proto_space_ok", ARP_ARP_PROTO_SPACE_OK);
        FA_DEBUG_BITS(ES2, "len_ok", ARP_ARP_LEN_OK);
        FA_DEBUG_BITS(ES2, "tgt_match", ARP_ARP_TGT_MATCH);
        FA_DEBUG_BITS(ES2, "sender_match", ARP_ARP_SENDER_MATCH);
        FA_DEBUG_BITS(ES2, "opcode_unknown", ARP_ARP_OPCODE_UNKNOWN);
        FA_DEBUG_BITS(ES2, "opcode", ARP_ARP_OPCODE);
        pr("\n");
        FA_DEBUG_BITS(ES2, "l3_ip4_dip", ARP_L3_IP4_DIP);
        FA_DEBUG_BITS(ES2, "l3_ip4_sip", ARP_L3_IP4_SIP);
        FA_DEBUG_BITS(ES2, "dip_eq_sip", ARP_DIP_EQ_SIP);
        return VTSS_RC_OK;
    }

    FA_DEBUG_BITS(ES2, "l3_rt", X6_L3_RT);
    FA_DEBUG_BITS(ES2, "es0_isdx_key_ena", X6_ES0_ISDX_KEY_ENA);
    FA_DEBUG_BITS(ES2, "mirror_probe", X6_MIRROR_PROBE);
    pr("\n");
    if (type == ES2_X6_TYPE_MAC_ETYPE) {
        FA_DEBUG_MAC(ES2, "dmac", MAC_ETYPE_L2_DMAC_0);
        FA_DEBUG_MAC(ES2, "smac", MAC_ETYPE_L2_SMAC_0);
        FA_DEBUG_BITS(ES2, "etype_len", MAC_ETYPE_ETYPE_LEN);
        FA_DEBUG_BITS(ES2, "etype", MAC_ETYPE_ETYPE);
        FA_DEBUG_BITS(ES2, "oam_ccm_cnts_eq0", MAC_ETYPE_OAM_CCM_CNTS_EQ0);
        FA_DEBUG_BITS(ES2, "oam_y1731", MAC_ETYPE_OAM_Y1731);
        pr("\n");
        FA_DEBUG_BITS_64(ES2, "l2_payload", MAC_ETYPE_L2_PAYLOAD_ETYPE_0);
        return VTSS_RC_OK;
    }

    FA_DEBUG_BITS(ES2, "ip4", X6_IP4);
    FA_DEBUG_BITS(ES2, "l3_fragment_type", X6_L3_FRAGMENT_TYPE);
    FA_DEBUG_BITS(ES2, "l3_options", X6_L3_OPTIONS);
    FA_DEBUG_BITS(ES2, "l3_ttl_gt0", X6_L3_TTL_GT0);
    FA_DEBUG_BITS(ES2, "l3_tos", X6_L3_TOS);
    pr("\n");
    FA_DEBUG_BITS(ES2, "l3_ip4_dip", X6_L3_IP4_DIP);
    FA_DEBUG_BITS(ES2, "l3_ip4_sip", X6_L3_IP4_SIP);
    FA_DEBUG_BITS(ES2, "dip_eq_sip", X6_DIP_EQ_SIP);
    if (type == ES2_X6_TYPE_IP4_OTHER) {
        FA_DEBUG_BITS(ES2, "l3_proto", IP4_OTHER_L3_IP_PROTO);
        pr("\n");
        FA_DEBUG_BITS_96(ES2, "l3_payload", IP4_OTHER_L3_PAYLOAD_0);
    } else {
        /* ES2_X6_TYPE_IP4_TCP_UDP */
        FA_DEBUG_BITS(ES2, "tcp", IP4_TCP_UDP_TCP);
        FA_DEBUG_BITS(ES2, "l4_dport", IP4_TCP_UDP_L4_DPORT);
        FA_DEBUG_BITS(ES2, "l4_sport", IP4_TCP_UDP_L4_SPORT);
        FA_DEBUG_BITS(ES2, "l4_rng", IP4_TCP_UDP_L4_RNG);
        pr("\n");
        FA_DEBUG_BITS(ES2, "sport_eq_dport", IP4_TCP_UDP_SPORT_EQ_DPORT);
        FA_DEBUG_BITS(ES2, "sequence_eq0", IP4_TCP_UDP_SEQUENCE_EQ0);
        FA_DEBUG_BITS(ES2, "l4_fin", IP4_TCP_UDP_L4_FIN);
        FA_DEBUG_BITS(ES2, "l4_syn", IP4_TCP_UDP_L4_SYN);
        FA_DEBUG_BITS(ES2, "l4_rst", IP4_TCP_UDP_L4_RST);
        FA_DEBUG_BITS(ES2, "l4_psh", IP4_TCP_UDP_L4_PSH);
        FA_DEBUG_BITS(ES2, "l4_ack", IP4_TCP_UDP_L4_ACK);
        FA_DEBUG_BITS(ES2, "l4_urg", IP4_TCP_UDP_L4_URG);
        pr("\n");
        FA_DEBUG_BITS_64(ES2, "l4_payload", IP4_TCP_UDP_L4_PAYLOAD_0);
    }
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc fa_debug_acl(vtss_state_t *vtss_state,
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
        vtss_fa_debug_reg_header(pr, buf);
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_CFG(port), port, "VCAP_S2_CFG");
        for (i = 0; i < 4; i++) {
            VTSS_SPRINTF(buf, "IS2_KEY_SEL_%u", i);
            vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_KEY_SEL(port, i), port, buf);
        }
        for (i = 0; i < 2; i++) {
            VTSS_SPRINTF(buf, "ES2_KEY_SEL_%u", i);
            vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_EACL_VCAP_ES2_KEY_SEL(port, i), port, buf);
        }
        pr("\n");
    }

    for (i = 0; i < VTSS_ACL_POLICERS; i++) {
        VTSS_SPRINTF(buf, "Policer %u", i);
        vtss_fa_debug_reg_header(pr, buf);
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL(i), i, "ACL_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG(i), i, "ACL_RATE_CFG");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG(i), i, "ACL_THRES_CFG");
        pr("\n");
    }

    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        VTSS_SPRINTF(buf, "Range %u", i);
        vtss_fa_debug_reg_header(pr, buf);
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_RNG_CTRL(i), i, "S2_RNG_CTRL");
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_RNG_VALUE_CFG(i), i, "S2_RNG_VAL");
        pr("\n");
    }

    vtss_fa_debug_reg_header(pr, "SIP Table");
    for (i = 0; i < VTSS_ACL_SIP_CNT; i++) {
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_ACL_SWAP_SIP(i), i, "SWAP_SIP");
    }
    pr("\n");

    VTSS_RC(vtss_fa_debug_lpm(vtss_state, pr, info)); /* SIP/SMAC check in LPM */
    VTSS_RC(fa_debug_vcap(vtss_state, VTSS_VCAP_TYPE_IS2, pr, info, fa_debug_is2));
    VTSS_RC(fa_debug_vcap(vtss_state, VTSS_VCAP_TYPE_IS2_B, pr, info, fa_debug_is2));
    VTSS_RC(fa_debug_vcap(vtss_state, VTSS_VCAP_TYPE_ES2, pr, info, fa_debug_es2));
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_vcap_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_ACL, fa_debug_acl, vtss_state, pr, info);
}

/* - ACL ----------------------------------------------------------- */

static u32 fa_acl_port_cnt_id(u32 port)
{
    /* By default, many rules map to counter 0, so we start with counter 1 */
    return (port + 1);
}

typedef struct {
    u8 *mem;
    u32 min;
    u32 max;
} vtss_fa_cnt_info_t;

static vtss_rc fa_acl_cnt_info_get(vtss_state_t *vtss_state, vtss_vcap_type_t type, vtss_fa_cnt_info_t *info)
{
    vtss_rc rc = VTSS_RC_OK;

    switch (type) {
    case VTSS_VCAP_TYPE_IS2:
        info->mem = vtss_state->vcap.acl_cnt_alloc;
        info->min = FA_ACE_CNT_ID_BASE;
        info->max = VTSS_ACL_CNT_SIZE;
        break;
    case VTSS_VCAP_TYPE_IS2_B:
        info->mem = vtss_state->vcap.is2b_cnt_alloc;
        info->min = FA_ACE_CNT_ID_BASE;
        info->max = VTSS_ACL_CNT_SIZE;
        break;
    case VTSS_VCAP_TYPE_ES2:
        info->mem = vtss_state->vcap.es2_cnt_alloc;
        info->min = 1; /* Start from 1, since counter zero is used by default rules */
        info->max = VTSS_ES2_CNT_SIZE;
        break;
    default:
        VTSS_E("illegal type");
        rc = VTSS_RC_ERROR;
        break;
    }
    return rc;
}

static u32 fa_ace_cnt_id_alloc(vtss_state_t *vtss_state, vtss_vcap_type_t type)
{
    u32                cnt_id;
    vtss_fa_cnt_info_t info;

    if (fa_acl_cnt_info_get(vtss_state, type, &info) == VTSS_RC_OK) {
        for (cnt_id = info.min; cnt_id < info.max; cnt_id++) {
            if (VTSS_BF_GET(info.mem, cnt_id) == 0) {
                VTSS_BF_SET(info.mem, cnt_id, 1);
                return cnt_id;
            }
        }
        VTSS_E("no %s counter free", vtss_vcap_type_txt(type));
    }
    return 0;
}

static vtss_rc fa_ace_cnt_id_free(vtss_state_t *vtss_state, vtss_vcap_type_t type, u32 cnt_id)
{
    vtss_fa_cnt_info_t info;

    if (fa_acl_cnt_info_get(vtss_state, type, &info) == VTSS_RC_OK) {
        if (VTSS_BF_GET(info.mem, cnt_id) == 0) {
            VTSS_E("%s counter %u already free", vtss_vcap_type_txt(type), cnt_id);
            return VTSS_RC_ERROR;
        }
        VTSS_BF_SET(info.mem, cnt_id, 0);
    }
    return VTSS_RC_OK;
}

/* ACE ID offset used to add/delete multiple IS2/ES2 rules per ACE */
#define FA_ACE_ID_OFFSET 0x100000000
#define FA_ACE_ID_MASK   0xffffffff

/* Maximum 16 IS2/ES2 rules per HACE */
#define FA_HACE_RULE_MAX 16

typedef struct {
    u8  rng;
    u32 mask[3];
} vtss_fa_prl_range_t;

static vtss_rc fa_hace_add(vtss_state_t *vtss_state,
                           const vtss_hacl_type_t type,
                           const vtss_ace_id_t ace_id_next,
                           const vtss_hace_t *const hace)
{
    vtss_vcap_entry_t            *cur;
    vtss_vcap_obj_t              *obj, *obj_lpm = &vtss_state->vcap.lpm.obj;
    vtss_vcap_user_t             user, user_lpm = VTSS_LPM_USER_ACL;
    vtss_res_t                   res;
    vtss_res_chg_t               *chg;
    vtss_vcap_data_t             data;
    vtss_is2_data_t              *is2 = &data.u.is2;
    vtss_is2_entry_t             entry;
    vtss_lpm_entry_t             entry_lpm;
    const vtss_hace_key_t        *key = &hace->key;
    const vtss_hace_frame_ipv4_t *ipv4 = &key->ipv4;
    const vtss_hace_frame_ipv6_t *ipv6 = &key->ipv6;
    const vtss_ace_udp_tcp_t     *sport = NULL, *dport = NULL;
    vtss_vcap_range_chk_table_t  *range_old, range_new = vtss_state->vcap.range;
    vtss_vcap_key_size_t         key_size = VTSS_VCAP_KEY_SIZE_HALF;
    vtss_vcap_key_size_t         key_lpm = VTSS_VCAP_KEY_SIZE_TWELFTH;
    int                          i, add_cnt = 0, del_cnt = 0, max, mod;
    u32                          cnt_id = 0;
    BOOL                         racl = FALSE, first;
    BOOL                         sip_smac_old = FALSE, sip_smac_new = FALSE, found = FALSE;
    vtss_port_mask_t             pmask;
    vtss_fa_prl_range_t          prl_range[FA_HACE_RULE_MAX], *prl;
    vtss_vcap_id_t               id, id_next = ace_id_next;
    vtss_port_no_t               port_no;

    /* Check ACE ID */
    if (hace->id == VTSS_ACE_ID_LAST || hace->id == ace_id_next) {
        VTSS_E("illegal ace id: %u", hace->id);
        return VTSS_RC_ERROR;
    }

    /* Check ACL type */
    switch (type) {
    case VTSS_HACL_TYPE_IPACL:
    case VTSS_HACL_TYPE_IVACL:
        obj = &vtss_state->vcap.is2.obj;
        chg = &res.is2;
        if (type == VTSS_HACL_TYPE_IPACL) {
            first = TRUE;
            user = VTSS_IS2_USER_IPACL;
        } else {
            first = FALSE;
            user = VTSS_IS2_USER_IVACL;
        }
        break;
    case VTSS_HACL_TYPE_IRACL:
    case VTSS_HACL_TYPE_ERACL:
        racl = TRUE;
        obj = &vtss_state->vcap.is2_b.obj;
        chg = &res.is2_b;
        if (type == VTSS_HACL_TYPE_IRACL) {
            first = TRUE;
            user = VTSS_IS2_USER_IRACL;
        } else {
            first = FALSE;
            user = VTSS_IS2_USER_ERACL;
        }
        break;
    case VTSS_HACL_TYPE_EVACL:
    case VTSS_HACL_TYPE_EPACL:
        obj = &vtss_state->vcap.es2.obj;
        chg = &res.es2;
        if (type == VTSS_HACL_TYPE_EVACL) {
            first = TRUE;
            user = VTSS_ES2_USER_EVACL;
        } else {
            first = FALSE;
            user = VTSS_ES2_USER_EPACL;
        }
        break;
    default:
        VTSS_E("illegal HACL type");
        return VTSS_RC_ERROR;
    }

    /* Check frame type */
    switch (key->type) {
    case VTSS_ACE_TYPE_ANY:
    case VTSS_ACE_TYPE_ETYPE:
    case VTSS_ACE_TYPE_LLC:
    case VTSS_ACE_TYPE_SNAP:
        if (racl) {
            VTSS_E("illegal frame type, only IPv4/IPv6 valid for RACL");
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_ACE_TYPE_ARP:
        if (type != VTSS_HACL_TYPE_IPACL && type != VTSS_HACL_TYPE_EPACL) {
            VTSS_E("illegal frame type, ARP only valid for PACL");
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_ACE_TYPE_IPV4:
    case VTSS_ACE_TYPE_IPV6:
        if (type == VTSS_HACL_TYPE_IVACL || type == VTSS_HACL_TYPE_EVACL) {
            VTSS_E("illegal frame type, IPv4/IPv6 not valid for VACL");
            return VTSS_RC_ERROR;
        }
        break;
    default:
        VTSS_E("illegal frame type: %d", hace->key.type);
        return VTSS_RC_ERROR;
    }

    /* Look for old rules */
    range_old = fa_vcap_range_get(vtss_state, obj->type);
    range_new = *range_old;
    vtss_cmn_res_init(&res);
    for (cur = obj->used; cur != NULL; cur = cur->next) {
        if (cur->user == user && (cur->id & FA_ACE_ID_MASK) == hace->id) {
            data = cur->data;
            chg->del_key[data.key_size]++;
            del_cnt++;
            if (del_cnt == 1) {
                /* Main entry */
                /* Free any old range checkers */
                VTSS_RC(vtss_vcap_range_free(&range_new, is2->srange));
                VTSS_RC(vtss_vcap_range_free(&range_new, is2->drange));

                /* Store counter ID */
                cnt_id = is2->cnt_id;
            }
        }
    }

    if (type == VTSS_HACL_TYPE_IPACL) {
        if (vtss_vcap_lookup(vtss_state, obj_lpm, user_lpm, hace->id, &data, NULL) == VTSS_RC_OK) {
            /* SIP/SMAC rule already exists */
            sip_smac_old = TRUE;
            res.lpm.del_key[data.key_size] = 1;
        }

        if (key->type == VTSS_ACE_TYPE_IPV4 && ipv4->sip_smac.enable) {
            /* SIP/SMAC rule is needed */
            sip_smac_new = TRUE;
            res.lpm.add_key[key_lpm] = 1;
        }
    }

    /* Check if counter can be allocated */
    if (cnt_id == 0 && (cnt_id = fa_ace_cnt_id_alloc(vtss_state, obj->type)) == 0) {
        VTSS_E("no ACE counter free");
        return VTSS_RC_ERROR;
    }

    /* Calculate number of new rules port masks */
    VTSS_MEMSET(prl_range, 0, sizeof(prl_range));
    if (racl) {
        if (key->type == VTSS_ACE_TYPE_IPV6) {
            /* IPv6 uses X12 rules with 64 router legs each */
            max = 64;
            key_size = VTSS_VCAP_KEY_SIZE_FULL;
        } else {
            /* IPv4 uses X6 rules with 32 router legs each */
            max = 32;
        }

        for (i = 0; i < VTSS_RLEG_CNT; i++) {
            mod = (i % max);
            if (mod == 0) {
                found = FALSE;
            }
            if (vtss_rleg_list_get(&key->rleg_list, i)) {
                if (!found) {
                    found = TRUE;
                    add_cnt++;
                }
                prl = &prl_range[add_cnt - 1];
                prl->rng = (i / max);
                prl->mask[mod / 32] |= VTSS_BIT(i % 32);
            }
        }
    } else {
        if (type == VTSS_HACL_TYPE_IPACL && key->type_ext &&
            (key->type == VTSS_ACE_TYPE_IPV4 || key->type == VTSS_ACE_TYPE_IPV6)) {
            /* I-PACL: Encode as IPv4/IPv6 full rule */
            key_size = VTSS_VCAP_KEY_SIZE_FULL;
        }
        vtss_port_mask_get(vtss_state, key->port_list, &pmask);
        for (i = 0; i < 3; i++) {
            prl = &prl_range[add_cnt];
            if (key_size == VTSS_VCAP_KEY_SIZE_FULL) {
                prl->mask[i] = pmask.m[i];
            } else if (pmask.m[i]) {
                prl->rng = i;
                prl->mask[0] = pmask.m[i];
                add_cnt++;
            }
        }
    }
    /* At least one rule is added */
    if (add_cnt == 0) {
        add_cnt = 1;
    }
    chg->add_key[key_size] = add_cnt;

    /* Check resources */
    VTSS_RC(vtss_cmn_res_check(vtss_state, &res));

    vtss_vcap_is2_init(&data, &entry);
    is2->cnt_id = cnt_id;
    entry.first = first;
    entry.type = type;
    entry.ace = *hace;
    data.key_size = key_size;
    if (hace->action.port_action == VTSS_ACL_PORT_ACTION_REDIR) {
        is2->action.redir = 1;
        for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
            if (hace->action.port_list[port_no]) {
                VTSS_PORT_BF_SET(is2->action.member, port_no, 1);
            }
        }
    }
    if (sip_smac_new) {
        entry.host_match = 1;
        entry.ace.key.ipv4.sip.value = ipv4->sip_smac.sip;
        entry.ace.key.ipv4.sip.mask = 0xffffffff;
    }

    /* Allocate and commit new range checkers */
    if (key->type == VTSS_ACE_TYPE_IPV4 && vtss_vcap_udp_tcp_rule(&ipv4->proto)) {
        sport = &ipv4->sport;
        dport = &ipv4->dport;
    } else if (key->type == VTSS_ACE_TYPE_IPV6 && vtss_vcap_udp_tcp_rule(&ipv6->proto)) {
        sport = &ipv6->sport;
        dport = &ipv6->dport;
    }
    if (sport && dport) {
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->srange, sport, 1));
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->drange, dport, 0));
    }
    VTSS_RC(fa_vcap_range_commit(vtss_state, obj->type, &range_new));

    /* Add/delete rules */
    max = MAX(add_cnt, del_cnt);
    for (i = (max - 1); i >= 0; i--) {
        id = (hace->id + i * FA_ACE_ID_OFFSET);
        if (i < add_cnt) {
            prl = &prl_range[i];
            entry.rng = prl->rng;
            entry.mask[0] = prl->mask[0];
            entry.mask[1] = prl->mask[1];
            VTSS_RC(vtss_vcap_add(vtss_state, obj, user, id, id_next, &data, 0));
            id_next = id;
        } else {
            VTSS_RC(vtss_vcap_del(vtss_state, obj, user, id));
        }
    }

    /* Add/delete SIP/SMAC entry */
    if (sip_smac_new) {
        VTSS_MEMSET(&data, 0, sizeof(data));
        VTSS_MEMSET(&entry_lpm, 0, sizeof(entry_lpm));
        data.u.lpm.entry = &entry_lpm;
        data.key_size = key_lpm;
        entry_lpm.key.type = VTSS_LPM_KEY_SGL_IP4;
        entry_lpm.key.data.sgl_ip4.xip = entry.ace.key.ipv4.sip;
        entry_lpm.action.type = LPM_X1_TYPE_ARP_ENTRY;
        entry_lpm.action.data.arp_entry.secur_match_mac_ena = 1;
        for (i = 0; i < 6; i++) {
            entry_lpm.action.data.arp_entry.mac.addr[i] = ipv4->sip_smac.smac.addr[i];
        }
        VTSS_RC(vtss_vcap_add(vtss_state, obj_lpm, user_lpm, hace->id, VTSS_VCAP_ID_LAST, &data, 0));
    } else if (sip_smac_old) {
        VTSS_RC(vtss_vcap_del(vtss_state, obj_lpm, user_lpm, hace->id));
    }
    return VTSS_RC_OK;
}

/* Delete/get/clear HACE */
static vtss_rc fa_hace_cmd(vtss_state_t *vtss_state,
                           const vtss_hacl_type_t type,
                           const vtss_ace_id_t ace_id,
                           vtss_ace_counter_t *const counter,
                           BOOL clear)
{
    vtss_vcap_obj_t             *obj;
    vtss_vcap_user_t            user;
    vtss_vcap_entry_t           *cur;
    vtss_vcap_idx_t             idx;
    vtss_vcap_id_t              id_table[FA_HACE_RULE_MAX];
    u32                         i, cnt = 0;
    vtss_is2_data_t             *is2;
    vtss_vcap_range_chk_table_t *range;

    /* Check ACL type */
    switch (type) {
    case VTSS_HACL_TYPE_IPACL:
    case VTSS_HACL_TYPE_IVACL:
        obj = &vtss_state->vcap.is2.obj;
        user = (type == VTSS_HACL_TYPE_IPACL ? VTSS_IS2_USER_IPACL : VTSS_IS2_USER_IVACL);
        break;
    case VTSS_HACL_TYPE_IRACL:
    case VTSS_HACL_TYPE_ERACL:
        obj = &vtss_state->vcap.is2_b.obj;
        user = (type == VTSS_HACL_TYPE_IRACL ? VTSS_IS2_USER_IRACL : VTSS_IS2_USER_ERACL);
        break;
    case VTSS_HACL_TYPE_EVACL:
    case VTSS_HACL_TYPE_EPACL:
        obj = &vtss_state->vcap.es2.obj;
        user = (type == VTSS_HACL_TYPE_EVACL ? VTSS_ES2_USER_EVACL : VTSS_ES2_USER_EPACL);
        break;
    default:
        VTSS_E("illegal HACL type");
        return VTSS_RC_ERROR;
    }

    if (counter == NULL) {
        /* Find all VCAP rules for HACE */
        range = fa_vcap_range_get(vtss_state, obj->type);
        for (cur = obj->used; cur != NULL; cur = cur->next) {
            if (cur->user == user && (cur->id & FA_ACE_ID_MASK) == ace_id) {
                if (cur->id == ace_id) {
                    /* Free counter and range checkers for main entry */
                    is2 = &cur->data.u.is2;
                    VTSS_RC(fa_ace_cnt_id_free(vtss_state, obj->type, is2->cnt_id));
                    VTSS_RC(vtss_vcap_range_free(range, is2->srange));
                    VTSS_RC(vtss_vcap_range_free(range, is2->drange));
                }
                id_table[cnt] = cur->id;
                cnt++;
            }
        }

        /* Delete rules */
        for (i = 0; i < cnt; i++) {
            VTSS_RC(vtss_vcap_del(vtss_state, obj, user, id_table[i]));
        }
    } else {
        /* Get/clear HACE counter */
        if (vtss_vcap_lookup(vtss_state, obj, user, ace_id, NULL, &idx) != VTSS_RC_OK) {
            VTSS_E("ace_id: %u not found", ace_id);
            return VTSS_RC_ERROR;
        }
        VTSS_RC(obj->entry_get(vtss_state, &idx, counter, clear));
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_hace_del(vtss_state_t *vtss_state,
                           const vtss_hacl_type_t type,
                           const vtss_ace_id_t ace_id)
{
    return fa_hace_cmd(vtss_state, type, ace_id, NULL, FALSE);
}

static vtss_rc fa_hace_counter_get(vtss_state_t *vtss_state,
                                   const vtss_hacl_type_t type,
                                   const vtss_ace_id_t ace_id,
                                   vtss_ace_counter_t *counter)
{
    return fa_hace_cmd(vtss_state, type, ace_id, counter, FALSE);
}

static vtss_rc fa_hace_counter_clear(vtss_state_t *vtss_state,
                                     const vtss_hacl_type_t type,
                                     const vtss_ace_id_t ace_id)
{
    vtss_ace_counter_t counter;

    return fa_hace_cmd(vtss_state, type, ace_id, &counter, TRUE);
}

static vtss_rc fa_acl_policer_set(vtss_state_t *vtss_state, const vtss_acl_policer_no_t policer_no)
{
    u32                     rate, i = (policer_no - VTSS_ACL_POLICER_NO_START);
    vtss_acl_policer_conf_t *conf = &vtss_state->vcap.acl_policer_conf[i];

    /* TBD_CPJ: Check core clock and POL_UPD_INT setting */
    if (conf->bit_rate_enable) {
        /* Bit rate in 25040 bps, API rate in 1000 bps, 1000/25040 = 25/626, round up */
        rate = (((conf->bit_rate + 1) * 25)/626);
    } else {
        /* Frame rate in 10 fps */
        rate = (conf->rate / 10);
    }
    rate = MIN(VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE, rate);
    REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG(i), VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE(rate));

    /* Minimum  threshold */
    REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG(i), VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG_ACL_THRES(1));

    /* Frame or line rate policing */
    REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL(i),
           VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_GAP_VALUE(20) |
           VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_ACL_TRAFFIC_TYPE_MASK(3) |
           VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_FRAME_RATE_ENA(conf->bit_rate_enable ? 0 : 1));
    return VTSS_RC_OK;
}

static vtss_rc fa_acl_sip_set(vtss_state_t *vtss_state, const vtss_acl_sip_idx_t idx)
{
    vtss_ip_addr_t *sip = &vtss_state->vcap.acl_sip_table[idx].sip;
    u32            i, j, addr;

    if (sip->type == VTSS_IP_TYPE_IPV4) {
        REG_WR(VTSS_ANA_ACL_SWAP_SIP(idx), sip->addr.ipv4);
    } else {
        for (i = 0; i < 4; i++) {
            for (addr = 0, j = 0; j < 4; j++) {
                addr += (sip->addr.ipv6.addr[15 - 4*i - j] << (j*8));
            }
            REG_WR(VTSS_ANA_ACL_SWAP_SIP(idx + i), addr);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_acl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_acl_port_conf_t *conf = &vtss_state->vcap.acl_port_conf[port_no];
    fa_vcap_data_t       vcap_data, *data = &vcap_data;
    u32                  ipv4, ipv6, lookup = 0, port = VTSS_CHIP_PORT(port_no);
    u32                  addr, enable = (conf->policy_no == VTSS_ACL_POLICY_NO_NONE ? 0 : 1);
    vtss_hacl_action_t   action;

    /* Policy */
    REG_WRM(VTSS_ANA_CL_PORT_ID_CFG(port),
            VTSS_F_ANA_CL_PORT_ID_CFG_PAG_VAL(enable ? conf->policy_no : 0),
            VTSS_M_ANA_CL_PORT_ID_CFG_PAG_VAL);

    /* Enable/disable IS2 lookup */
    REG_WRM_CTL(VTSS_ANA_ACL_VCAP_S2_CFG(port), enable, VTSS_F_ANA_ACL_VCAP_S2_CFG_SEC_ENA(1 << lookup));

    /* Key generation */
    ipv4 = (conf->key.ipv4 == VTSS_ACL_KEY_EXT ? 2 : conf->key.ipv4 == VTSS_ACL_KEY_DEFAULT ? 1 : 0);
    ipv6 = (conf->key.ipv6 == VTSS_ACL_KEY_EXT ? 1 : conf->key.ipv6 == VTSS_ACL_KEY_DEFAULT ? 3 : 0);
    REG_WR(VTSS_ANA_ACL_VCAP_S2_KEY_SEL(port, lookup),
           VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP4_MC_KEY_SEL(ipv4) |
           VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP4_UC_KEY_SEL(ipv4) |
           VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP6_MC_KEY_SEL(ipv6 == 3 ? 4 : ipv6) |
           VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP6_UC_KEY_SEL(ipv6) |
           VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_ARP_KEY_SEL(conf->key.arp == VTSS_ACL_KEY_ETYPE ? 0 : 1));

    /* Setup action */
    VTSS_MEMSET(data, 0, sizeof(*data));
    fa_action_old2new(&conf->action, &action);
    data->vcap_type = VTSS_VCAP_TYPE_IS2;
    VTSS_RC(fa_is2_action_set(vtss_state, data, &action, fa_acl_port_cnt_id(port), 0));
    addr = fa_vcap_action_addr(data->vcap_type, port, 0);
    return fa_vcap_entry_cmd(vtss_state, data, addr, data->type, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION);
}

static vtss_rc fa_acl_port_counter_get(vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_acl_port_counter_t *const counter)
{
    u32 cnt_id = fa_acl_port_cnt_id(VTSS_CHIP_PORT(port_no));

    return fa_is2_cnt_get(vtss_state, VTSS_VCAP_TYPE_IS2, cnt_id, counter);
}

static vtss_rc fa_acl_port_counter_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 cnt_id = fa_acl_port_cnt_id(VTSS_CHIP_PORT(port_no));

    return fa_is2_cnt_set(vtss_state, VTSS_VCAP_TYPE_IS2, cnt_id, 0);
}

static vtss_rc fa_ace_add(vtss_state_t *vtss_state,
                          const vtss_ace_id_t ace_id, const vtss_ace_t *const ace)
{
    vtss_hace_t                  hace;
    vtss_hace_key_t              *key = &hace.key;
    vtss_port_no_t               port_no;
    const vtss_ace_frame_any_t   *any = &ace->frame.any;
    const vtss_ace_frame_etype_t *etype = &ace->frame.etype;
    const vtss_ace_frame_llc_t   *llc = &ace->frame.llc;
    const vtss_ace_frame_snap_t  *snap = &ace->frame.snap;
    const vtss_ace_frame_arp_t   *arp = &ace->frame.arp;
    const vtss_ace_frame_ipv4_t  *ipv4 = &ace->frame.ipv4;
    const vtss_ace_frame_ipv6_t  *ipv6 = &ace->frame.ipv6;

    /* Convert from ACE to HACE structure */
    VTSS_RC(vtss_hace_init(NULL, ace->type, &hace));
    hace.id = ace->id;
    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        key->port_list[port_no] = ace->port_list[port_no];
    }
    key->policy = ace->policy;
    key->vlan = ace->vlan;
    key->dmac_mc = ace->dmac_mc;
    key->dmac_bc = ace->dmac_bc;
    key->type_ext = ace->type_ext;
    switch (ace->type) {
    case VTSS_ACE_TYPE_ANY:
        key->dmac = any->dmac;
        key->smac = any->smac;
        break;
    case VTSS_ACE_TYPE_ETYPE:
        key->dmac = etype->dmac;
        key->smac = etype->smac;
        key->etype.etype = etype->etype;
        key->etype.data = etype->data;
        key->ptp = etype->ptp;
        break;
    case VTSS_ACE_TYPE_LLC:
        key->dmac = llc->dmac;
        key->smac = llc->smac;
        key->llc.llc = llc->llc;
        break;
    case VTSS_ACE_TYPE_SNAP:
        key->dmac = snap->dmac;
        key->smac = snap->smac;
        key->snap.snap = snap->snap;
        break;
    case VTSS_ACE_TYPE_ARP:
        key->smac = arp->smac;
        key->arp.arp = arp->arp;
        key->arp.req = arp->req;
        key->arp.unknown = arp->unknown;
        key->arp.smac_match = arp->smac_match;
        key->arp.dmac_match = arp->dmac_match;
        key->arp.length = arp->length;
        key->arp.ip = arp->ip;
        key->arp.ethernet = arp->ethernet;
        key->arp.sip = arp->sip;
        key->arp.dip = arp->dip;
        break;
    case VTSS_ACE_TYPE_IPV4:
        key->dmac = ipv4->dmac;
        key->smac = ipv4->smac;
        key->ipv4.ttl = ipv4->ttl;
        key->ipv4.fragment = ipv4->fragment;
        key->ipv4.options = ipv4->options;
        key->ipv4.ds = ipv4->ds;
        key->ipv4.proto = ipv4->proto;
        key->ipv4.sip = ipv4->sip;
        key->ipv4.dip = ipv4->dip;
        key->ipv4.data = ipv4->data;
        key->ipv4.sport = ipv4->sport;
        key->ipv4.dport = ipv4->dport;
        key->ipv4.tcp_fin = ipv4->tcp_fin;
        key->ipv4.tcp_syn = ipv4->tcp_syn;
        key->ipv4.tcp_rst = ipv4->tcp_rst;
        key->ipv4.tcp_psh = ipv4->tcp_psh;
        key->ipv4.tcp_ack = ipv4->tcp_ack;
        key->ipv4.tcp_urg = ipv4->tcp_urg;
        key->ipv4.sip_smac = ipv4->sip_smac;
        key->ptp = ipv4->ptp;
        break;
    case VTSS_ACE_TYPE_IPV6:
        key->dmac = ipv6->dmac;
        key->smac = ipv6->smac;
        key->ipv6.ttl = ipv6->ttl;
        key->ipv6.ds = ipv6->ds;
        key->ipv6.proto = ipv6->proto;
        key->ipv6.sip = ipv6->sip;
        key->ipv6.dip = ipv6->dip;
        key->ipv6.data = ipv6->data;
        key->ipv6.sport = ipv6->sport;
        key->ipv6.dport = ipv6->dport;
        key->ipv6.tcp_fin = ipv6->tcp_fin;
        key->ipv6.tcp_syn = ipv6->tcp_syn;
        key->ipv6.tcp_rst = ipv6->tcp_rst;
        key->ipv6.tcp_psh = ipv6->tcp_psh;
        key->ipv6.tcp_ack = ipv6->tcp_ack;
        key->ipv6.tcp_urg = ipv6->tcp_urg;
        key->ptp = ipv6->ptp;
        break;
    default:
        break;
    }
    fa_action_old2new(&ace->action, &hace.action);
    return fa_hace_add(vtss_state, VTSS_HACL_TYPE_IPACL, ace_id, &hace);
}

static vtss_rc fa_ace_del(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    /* Delete rules */
    VTSS_RC(fa_hace_del(vtss_state, VTSS_HACL_TYPE_IPACL, ace_id));

    /* Delete SMAC/SIP entry */
    return vtss_vcap_del(vtss_state, &vtss_state->vcap.lpm.obj, VTSS_LPM_USER_ACL, ace_id);
}

/* - ES0 ----------------------------------------------------------- */

/* (Selection, value) pair */
typedef struct {
    u32 sel;
    u32 val;
} fa_es0_sel_t;

/* ES0 tag related fields */
typedef struct {
    u32           tag_sel;
    u32           tpid_sel;
    fa_es0_sel_t vid;
    fa_es0_sel_t pcp;
    fa_es0_sel_t dei;
} fa_es0_tag_t;

static void fa_es0_tag_get(vtss_es0_action_t *action, BOOL inner, fa_es0_tag_t *tag)
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
    tag->vid.sel = (conf->vid.sel ? ES0_ACT_VID_SEL_VID_ES0 : ES0_ACT_VID_SEL_CL_VID);
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
} fa_es0_map_t;

static BOOL fa_es0_map_update(vtss_state_t *vtss_state, vtss_qos_egress_map_id_t map_id, fa_es0_map_t *map)
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

static vtss_rc fa_es0_action_update(vtss_state_t *vtss_state, fa_vcap_data_t *data, vtss_es0_data_t *es0)
{
    vtss_es0_action_t        *action = &es0->entry->action;
    fa_es0_map_t             map;
    vtss_qos_egress_map_id_t map_id;
    u32                      dscp_sel = ES0_ACT_DSCP_SEL_PORT;
    fa_es0_tag_t             tag;

    fa_es0_tag_get(action, 0, &tag);
    map_id = (es0->flags & VTSS_ES0_FLAG_MAP_ID_OT ? es0->map_id_ot :
              es0->flags & VTSS_ES0_FLAG_OT_QOS ? vtss_state->qos.port_conf[es0->port_no].egress_map :
              VTSS_QOS_EGRESS_MAP_ID_NONE);

    VTSS_I("ot map: %u", map_id);
    if (fa_es0_map_update(vtss_state, map_id, &map)) {
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
    }
    FA_ACT_SET(ES0, ES0_TAG_A_PCP_SEL, tag.pcp.sel);
    FA_ACT_SET(ES0, ES0_TAG_A_DEI_SEL, tag.dei.sel);
    FA_ACT_SET(ES0, ES0_MAP_0_IDX, map.idx);
    FA_ACT_SET(ES0, ES0_MAP_0_KEY, map.key);
    FA_ACT_SET(ES0, ES0_MAP_2_IDX, map.idx);
    FA_ACT_SET(ES0, ES0_MAP_2_KEY, map.key);
    FA_ACT_SET(ES0, ES0_DSCP_SEL,  dscp_sel);
    FA_ACT_SET(ES0, ES0_ESDX_BASE, es0->esdx ? es0->esdx : 1); // Avoid using esdx_base 0 as default

    fa_es0_tag_get(action, 1, &tag);
    map_id = (es0->flags & VTSS_ES0_FLAG_MAP_ID_IT ? es0->map_id_it :
              es0->flags & VTSS_ES0_FLAG_IT_QOS ? vtss_state->qos.port_conf[es0->port_no].egress_map :
              VTSS_QOS_EGRESS_MAP_ID_NONE);
    VTSS_I("it map: %u", map_id);
    if (fa_es0_map_update(vtss_state, map_id, &map)) {
        /* Inner tag map ID used */
        if ((map.act & VTSS_QOS_EGRESS_MAP_ACTION_PCP) && (es0->flags & (VTSS_ES0_FLAG_MAP_IT_PCP | VTSS_ES0_FLAG_IT_PCP))) {
            tag.pcp.sel = (map.res ? ES0_ACT_PCP_SEL_MAP_3 : ES0_ACT_PCP_SEL_MAP_1);
        }
        if ((map.act & VTSS_QOS_EGRESS_MAP_ACTION_DEI) && (es0->flags & (VTSS_ES0_FLAG_MAP_IT_DEI | VTSS_ES0_FLAG_IT_DEI))) {
            tag.dei.sel = (map.res ? ES0_ACT_DEI_SEL_MAP_3 : ES0_ACT_DEI_SEL_MAP_1);
        }
    }
    FA_ACT_SET(ES0, ES0_TAG_B_PCP_SEL, tag.pcp.sel);
    FA_ACT_SET(ES0, ES0_TAG_B_DEI_SEL, tag.dei.sel);
    FA_ACT_SET(ES0, ES0_MAP_1_IDX, map.idx);
    FA_ACT_SET(ES0, ES0_MAP_1_KEY, map.key);
    FA_ACT_SET(ES0, ES0_MAP_3_IDX, map.idx);
    FA_ACT_SET(ES0, ES0_MAP_3_KEY, map.key);
    /* TBD_MPLS: TC_SEL setup */

    return VTSS_RC_OK;
}

static void fa_es0_outer_tag_update(vtss_state_t *vtss_state, fa_vcap_data_t *data, fa_es0_tag_t *tag)
{
    FA_ACT_SET(ES0, ES0_PUSH_OUTER_TAG, tag->tag_sel);
    FA_ACT_SET(ES0, ES0_TAG_A_TPID_SEL, tag->tpid_sel);
    FA_ACT_SET(ES0, ES0_TAG_A_VID_SEL, tag->vid.sel);
    FA_ACT_SET(ES0, ES0_VID_A_VAL, tag->vid.val);
    FA_ACT_SET(ES0, ES0_TAG_A_PCP_SEL, tag->pcp.sel);
    FA_ACT_SET(ES0, ES0_PCP_A_VAL, tag->pcp.val);
    FA_ACT_SET(ES0, ES0_TAG_A_DEI_SEL, tag->dei.sel);
    FA_ACT_SET(ES0, ES0_DEI_A_VAL, tag->dei.val);
}

static vtss_rc fa_es0_entry_add(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    fa_vcap_data_t    fa_data, *data = &fa_data;
    vtss_es0_data_t   *es0 = &vcap_data->u.es0;
    vtss_es0_key_t    *key = &es0->entry->key;
    vtss_es0_action_t *action = &es0->entry->action;
    fa_es0_tag_t      tag;
    u32               addr;
    BOOL              key_isdx = (key->type == VTSS_ES0_TYPE_ISDX ? 1 : 0);

    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    data->tg = FA_VCAP_TG_X1;
    data->type = FA_VCAP_TG_X1;
    addr = fa_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("row: %u, col: %u, addr: %u", idx->row, idx->col, addr);

    /* Key fields */
    fa_vcap_key_set(data, ES0_KO_X1_TYPE, ES0_KL_X1_TYPE, key_isdx ? ES0_X1_TYPE_ISDX : ES0_X1_TYPE_VID, VTSS_BITMASK(ES0_KL_X1_TYPE));
    if (key->port_no != VTSS_PORT_NO_NONE) {
        fa_vcap_key_set(data, ES0_KO_X1_EGR_PORT, ES0_KL_X1_EGR_PORT,
                        VTSS_CHIP_PORT(key->port_no), VTSS_BITMASK(ES0_KL_X1_EGR_PORT));
    }
    fa_vcap_key_bit_set(data, ES0_KO_X1_SERVICE_FRM, key->isdx_neq0);
    if (key_isdx) {
        fa_vcap_key_set(data, ES0_KO_ISDX_ISDX, ES0_KL_ISDX_ISDX,
                        key->data.isdx.isdx, key->data.isdx.isdx_enable ? VTSS_BITMASK(ES0_KL_ISDX_ISDX) : 0);
    } else {
        fa_vcap_key_set(data, ES0_KO_X1_XVID, ES0_KL_X1_XVID,
                        key->data.vid.vid, key->data.vid.vid == VTSS_VID_ALL || key->vid_any ? 0 : VTSS_BITMASK(ES0_KL_X1_XVID));
    }

    /* Action fields */
    /* Outer tag */
    vtss_cmn_es0_action_get(vtss_state, es0);
    fa_es0_tag_get(action, 0, &tag);
    fa_es0_outer_tag_update(vtss_state, data, &tag);

    /* Inner tag */
    fa_es0_tag_get(action, 1, &tag);
    FA_ACT_SET(ES0, ES0_PUSH_INNER_TAG, tag.tag_sel);
    FA_ACT_SET(ES0, ES0_TAG_B_TPID_SEL, tag.tpid_sel);
    FA_ACT_SET(ES0, ES0_TAG_B_VID_SEL, tag.vid.sel);
    FA_ACT_SET(ES0, ES0_VID_B_VAL, tag.vid.val);
    FA_ACT_SET(ES0, ES0_TAG_B_PCP_SEL, tag.pcp.sel);
    FA_ACT_SET(ES0, ES0_PCP_B_VAL, tag.pcp.val);
    FA_ACT_SET(ES0, ES0_TAG_B_DEI_SEL, tag.dei.sel);
    FA_ACT_SET(ES0, ES0_DEI_B_VAL, tag.dei.val);

    FA_ACT_SET(ES0, ES0_POP_VAL, action->pop_cnt);
    fa_act_ena_set(data, ES0_AO_ES0_OAM_MEP_IDX_VLD, ES0_AO_ES0_OAM_MEP_IDX, ES0_AL_ES0_OAM_MEP_IDX, action->mep_idx_enable, action->mep_idx);
    FA_ACT_SET(ES0, ES0_ESDX_COSID_OFFSET, action->esdx_cosid_offset);
    FA_ACT_SET(ES0, ES0_MIP_IDX, vtss_fa_voi_idx_to_mip_idx(action->voi_idx));
    FA_ACT_SET(ES0, ES0_FWD_SEL, action->forward_sel);
    FA_ACT_SET(ES0, ES0_PIPELINE_PT, action->pipe_pt);
    FA_ACT_SET(ES0, ES0_CPU_QU, action->cpu_queue);
    FA_ACT_SET(ES0, ES0_INDEPENDENT_MEL_ENA, action->independent_mel);
    FA_ACT_SET(ES0, ES0_PIPELINE_ACT, action->pipe_act);
    FA_ACT_SET(ES0, ES0_SWAP_MACS_ENA, action->mac_swap_enable);

#if defined(VTSS_FEATURE_FRER)
    FA_ACT_SET(ES0, ES0_RTAG_POP_ENA, action->rtag.pop);
    FA_ACT_SET(ES0, ES0_RTAG_PUSH_SEL, action->rtag.sel);
#endif

    /* Update action fields based on egress QoS mapping */
    VTSS_RC(fa_es0_action_update(vtss_state, data, es0));

    return fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ALL);
}

static vtss_rc fa_es0_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return fa_vcap_entry_del(vtss_state, VTSS_VCAP_TYPE_ES0, idx);
}

static vtss_rc fa_es0_entry_move(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return fa_vcap_entry_move(vtss_state, VTSS_VCAP_TYPE_ES0, idx, count, up);
}

static vtss_rc fa_es0_entry_get(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return fa_vcap_entry_get(vtss_state, VTSS_VCAP_TYPE_ES0, idx, counter, clear);
}

/* Update outer tag TPID for ES0 entry if VLAN port type has changed */
static vtss_rc fa_es0_entry_update(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx, vtss_es0_data_t *es0)
{
#if VTSS_OPT_TRACE
    const fa_vcap_props_t *vcap = &fa_vcap_info[FA_VCAP_ES0];
#endif
    fa_vcap_data_t        fa_data, *data = &fa_data;
    vtss_es0_action_t     *action = &es0->entry->action;
    fa_es0_tag_t          tag;
    u32                   addr;

    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    data->tg = FA_VCAP_TG_X1;
    addr = fa_vcap_entry_addr(vtss_state, data->vcap_type, idx);
    VTSS_I("%s, row: %u, col: %u, addr: %u, port_no: %u, flags: 0x%x", vcap->name, idx->row, idx->col, addr, es0->port_no, es0->flags);

    /* Read action */
    VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_READ, FA_VCAP_SEL_ACTION));

    /* Update action fields */
    fa_es0_tag_get(action, 0, &tag);
    if (es0->flags & VTSS_ES0_FLAG_OT_UVID) {
        FA_ACT_SET(ES0, ES0_PUSH_OUTER_TAG, tag.tag_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_TPID) {
        FA_ACT_SET(ES0, ES0_TAG_A_TPID_SEL, tag.tpid_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_PCP) {
        FA_ACT_SET(ES0, ES0_PCP_A_VAL, tag.pcp.val);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_DEI) {
        FA_ACT_SET(ES0, ES0_DEI_A_VAL, tag.dei.val);
    }
    fa_es0_tag_get(action, 1, &tag);
    if (es0->flags & VTSS_ES0_FLAG_IT_UVID) {
        FA_ACT_SET(ES0, ES0_PUSH_INNER_TAG, tag.tag_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_TPID) {
        FA_ACT_SET(ES0, ES0_TAG_B_TPID_SEL, tag.tpid_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_PCP) {
        FA_ACT_SET(ES0, ES0_PCP_B_VAL, tag.pcp.val);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_DEI) {
        FA_ACT_SET(ES0, ES0_DEI_B_VAL, tag.dei.val);
    }

    /* Update action fields based on egress QoS mapping */
    VTSS_RC(fa_es0_action_update(vtss_state, data, es0));

    /* Write action */
    return fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION);
}

vtss_rc vtss_fa_vcap_port_update(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    fa_vcap_data_t           vcap_data, *data = &vcap_data;
    u32                      addr, port = VTSS_CHIP_PORT(port_no), dscp_sel = ES0_ACT_DSCP_SEL_PORT;
    fa_es0_map_t             map;
    vtss_qos_egress_map_id_t map_id = vtss_state->qos.port_conf[port_no].egress_map;
    fa_es0_tag_t             tag;
    vtss_vlan_port_conf_t    *conf = &vtss_state->l2.vlan_port_conf[port_no];
    BOOL                     port_tag = FALSE;

    /* Egress QoS map setup using ES0 default action */
    VTSS_MEMSET(data, 0, sizeof(*data));
    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    addr = fa_vcap_action_addr(data->vcap_type, port, 0);
    VTSS_I("port_no: %u, port: %u, addr: %u, map: %u", port_no, port, addr, map_id);
    VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, FA_VCAP_TG_X1, FA_VCAP_CMD_READ, FA_VCAP_SEL_ACTION));
    data->type = FA_VCAP_TG_X1;

    /* Setup TAG_C */
    VTSS_MEMSET(&tag, 0, sizeof(tag));
    if (fa_es0_map_update(vtss_state, map_id, &map)) {
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
    FA_ACT_SET(ES0, ES0_UNTAG_VID_ENA, conf->untagged_vid == VTSS_VID_NULL ? 0 : 1);
    FA_ACT_SET(ES0, ES0_PUSH_CUSTOMER_TAG, tag.tag_sel);
    FA_ACT_SET(ES0, ES0_TAG_C_TPID_SEL, tag.tpid_sel);
    FA_ACT_SET(ES0, ES0_TAG_C_VID_SEL, tag.vid.sel);
    FA_ACT_SET(ES0, ES0_VID_C_VAL, tag.vid.val);
    FA_ACT_SET(ES0, ES0_TAG_C_PCP_SEL, tag.pcp.sel);
    FA_ACT_SET(ES0, ES0_PCP_C_VAL, tag.pcp.val);
    FA_ACT_SET(ES0, ES0_TAG_C_DEI_SEL, tag.dei.sel);
    FA_ACT_SET(ES0, ES0_DEI_C_VAL, tag.dei.val);

    /* Setup TAG_A */
    VTSS_MEMSET(&tag, 0, sizeof(tag));
    tag.tag_sel = (port_tag ? ES0_ACT_PUSH_OT_PORT_ENA : ES0_ACT_PUSH_OT_NONE);
    fa_es0_outer_tag_update(vtss_state, data, &tag);

    FA_ACT_SET(ES0, ES0_MAP_0_IDX, map.idx);
    FA_ACT_SET(ES0, ES0_MAP_0_KEY, map.key);
    FA_ACT_SET(ES0, ES0_MAP_2_IDX, map.idx);
    FA_ACT_SET(ES0, ES0_MAP_2_KEY, map.key);
    FA_ACT_SET(ES0, ES0_DSCP_SEL,  dscp_sel);
    FA_ACT_SET(ES0, ES0_ESDX_BASE, 1);
    FA_ACT_SET(ES0, ES0_INDEPENDENT_MEL_ENA, 1); // By default, get Port VOE to see frames as data frames

    return fa_vcap_entry_cmd(vtss_state, data, addr, data->type, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION);
}

static void fa_debug_es0_tag(const char *name, fa_vcap_data_t *data,
                              u32 tpid_sel, u32 vid_sel, u32 pcp_sel, u32 dei_sel, u32 vid_val, u32 pcp_val, u32 dei_val)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 x;
    char                buf[16];

    x = fa_act_get(data, tpid_sel, ES0_AL_ES0_TAG_A_TPID_SEL);
    pr("tpid_%s_sel:%u (%s) ", name, x,
       x == ES0_ACT_TPID_SEL_C ? "c" :
       x == ES0_ACT_TPID_SEL_S ? "s" :
       x == ES0_ACT_TPID_SEL_CUSTOM_1 ? "c1" :
       x == ES0_ACT_TPID_SEL_CUSTOM_2 ? "c2" :
       x == ES0_ACT_TPID_SEL_CUSTOM_3 ? "c3" :
       x == ES0_ACT_TPID_SEL_INGRESS ? "ingress" : "?");

    VTSS_SPRINTF(buf, "vid_%s", name);
    x = fa_act_get(data, vid_sel, ES0_AL_ES0_TAG_A_VID_SEL);
    pr("%s_sel:%u (%s) ", buf, x,
       x == ES0_ACT_VID_SEL_CL_VID ? "cl_vid" :
       x == ES0_ACT_VID_SEL_VID_ES0 ? "vid" :
       x == ES0_ACT_VID_SEL_GVID ? "gvid" : "?");
    fa_debug_action(data, buf, vid_val, ES0_AL_ES0_VID_A_VAL);
    pr("\n");

    VTSS_SPRINTF(buf, "pcp_%s", name);
    x = fa_act_get(data, pcp_sel, ES0_AL_ES0_TAG_A_PCP_SEL);
    pr("%s_sel:%u (%s) ", buf, x,
       x == ES0_ACT_PCP_SEL_CL_PCP ? "cl-pcp" :
       x == ES0_ACT_PCP_SEL_PCP_ES0 ? "es0" :
       x == ES0_ACT_PCP_SEL_POPPED ? "popped" :
       x == ES0_ACT_PCP_SEL_MAP_0 ? "map_0" :
       x == ES0_ACT_PCP_SEL_MAP_1 ? "map_1" :
       x == ES0_ACT_PCP_SEL_MAP_2 ? "map_3" :
       x == ES0_ACT_PCP_SEL_MAP_3 ? "map_3" : "?");
    fa_debug_action(data, buf, pcp_val, ES0_AL_ES0_PCP_A_VAL);

    VTSS_SPRINTF(buf, "dei_%s", name);
    x = fa_act_get(data, dei_sel, ES0_AL_ES0_TAG_A_DEI_SEL);
    pr("%s_sel:%u (%s) ", buf, x,
       x == ES0_ACT_DEI_SEL_CL_DEI ? "cl-dei" :
       x == ES0_ACT_DEI_SEL_DEI_ES0 ? "es0" :
       x == ES0_ACT_DEI_SEL_MAPPED ? "mapped" :
       x == ES0_ACT_DEI_SEL_POPPED ? "popped" :
       x == ES0_ACT_DEI_SEL_MAP_0 ? "map_0" :
       x == ES0_ACT_DEI_SEL_MAP_1 ? "map_1" :
       x == ES0_ACT_DEI_SEL_MAP_2 ? "map_2" :
       x == ES0_ACT_DEI_SEL_MAP_3 ? "map_3" : "?");
    fa_debug_action(data, buf, dei_val, ES0_AL_ES0_DEI_A_VAL);
    pr("\n");
}

static vtss_rc fa_debug_es0(vtss_state_t *vtss_state, fa_vcap_data_t *data)
{
    vtss_debug_printf_t pr = data->pr;
    u32                 x, type;

    if (data->is_action) {
        FA_DEBUG_ACT(ES0, "push_outer", ES0_PUSH_OUTER_TAG);
        x = fa_act_get(data, ES0_AO_ES0_PUSH_OUTER_TAG, ES0_AL_ES0_PUSH_OUTER_TAG);
        pr("(%s) ",
           x == ES0_ACT_PUSH_OT_PORT_ENA ? "port" :
           x == ES0_ACT_PUSH_OT_ES0 ? "tag_a" :
           x == ES0_ACT_PUSH_OT_PORT ? "port_force" : "none");
        FA_DEBUG_ACT(ES0, "push_inner", ES0_PUSH_INNER_TAG);
        pr("(%s) ", fa_act_get(data, ES0_AO_ES0_PUSH_INNER_TAG, ES0_AL_ES0_PUSH_INNER_TAG) ? "tag_b" : "none");
        FA_DEBUG_ACT(ES0, "push_tag_c", ES0_PUSH_CUSTOMER_TAG);
        pr("(%s) ", fa_act_get(data, ES0_AO_ES0_PUSH_CUSTOMER_TAG, ES0_AL_ES0_PUSH_CUSTOMER_TAG) ? "push" : "none");
        FA_DEBUG_ACT(ES0, "untag_vid_ena", ES0_UNTAG_VID_ENA);
        pr("\n");
        fa_debug_es0_tag("a", data, ES0_AO_ES0_TAG_A_TPID_SEL,
                         ES0_AO_ES0_TAG_A_VID_SEL, ES0_AO_ES0_TAG_A_PCP_SEL, ES0_AO_ES0_TAG_A_DEI_SEL,
                         ES0_AO_ES0_VID_A_VAL, ES0_AO_ES0_PCP_A_VAL, ES0_AO_ES0_DEI_A_VAL);
        fa_debug_es0_tag("b", data, ES0_AO_ES0_TAG_B_TPID_SEL,
                         ES0_AO_ES0_TAG_B_VID_SEL, ES0_AO_ES0_TAG_B_PCP_SEL, ES0_AO_ES0_TAG_B_DEI_SEL,
                         ES0_AO_ES0_VID_B_VAL, ES0_AO_ES0_PCP_B_VAL, ES0_AO_ES0_DEI_B_VAL);
        fa_debug_es0_tag("c", data, ES0_AO_ES0_TAG_C_TPID_SEL,
                         ES0_AO_ES0_TAG_C_VID_SEL, ES0_AO_ES0_TAG_C_PCP_SEL, ES0_AO_ES0_TAG_C_DEI_SEL,
                         ES0_AO_ES0_VID_C_VAL, ES0_AO_ES0_PCP_C_VAL, ES0_AO_ES0_DEI_C_VAL);
        FA_DEBUG_ACT(ES0, "pop_val", ES0_POP_VAL);
        FA_DEBUG_ACT(ES0, "dscp_sel", ES0_DSCP_SEL);
        FA_DEBUG_ACT(ES0, "dscp_val", ES0_DSCP_VAL);
        FA_DEBUG_ACT(ES0, "pop_cnt", ES0_POP_CNT);
        FA_DEBUG_ACT(ES0, "rtag_pop", ES0_RTAG_POP_ENA);
        FA_DEBUG_ACT(ES0, "rtag_push", ES0_RTAG_PUSH_SEL);
        pr("\n");
        FA_DEBUG_ACT(ES0, "esdx_base", ES0_ESDX_BASE);
        FA_DEBUG_ACT_BITS(ES0, "esdx_cosid_offs", ES0_ESDX_COSID_OFFSET);
        pr("\n");
        FA_DEBUG_ACT(ES0, "map_0_idx", ES0_MAP_0_IDX);
        FA_DEBUG_ACT(ES0, "map_1_idx", ES0_MAP_1_IDX);
        FA_DEBUG_ACT(ES0, "map_2_idx", ES0_MAP_2_IDX);
        FA_DEBUG_ACT(ES0, "map_3_idx", ES0_MAP_3_IDX);
        pr("\n");
        FA_DEBUG_ACT(ES0, "map_0_key", ES0_MAP_0_KEY);
        FA_DEBUG_ACT(ES0, "map_1_key", ES0_MAP_1_KEY);
        FA_DEBUG_ACT(ES0, "map_2_key", ES0_MAP_2_KEY);
        FA_DEBUG_ACT(ES0, "map_3_key", ES0_MAP_3_KEY);
        pr("\n");
        FA_DEBUG_ACT_ENA(ES0, "mep_idx", ES0_OAM_MEP_IDX_VLD, ES0_OAM_MEP_IDX);
        FA_DEBUG_ACT(ES0, "oam_indep_mel_ena", ES0_INDEPENDENT_MEL_ENA);
        FA_DEBUG_ACT(ES0, "mip_idx", ES0_MIP_IDX);
        FA_DEBUG_ACT(ES0, "fwd_sel", ES0_FWD_SEL);
        pr("\n");
        FA_DEBUG_ACT(ES0, "cpu_qu", ES0_CPU_QU);
        FA_DEBUG_ACT(ES0, "pipeline_pt", ES0_PIPELINE_PT);
        FA_DEBUG_ACT(ES0, "pipeline_act", ES0_PIPELINE_ACT);
        FA_DEBUG_ACT(ES0, "swap_macs_ena", ES0_SWAP_MACS_ENA);
        /* TBD_MPLS: MPLS action fields */
        pr("\ncnt: %u", data->counter);
        return VTSS_RC_OK;
    }
    type = fa_entry_bs_get(data, ES0_KO_X1_TYPE, ES0_KL_X1_TYPE);
    FA_DEBUG_BITS(ES0, "type", X1_TYPE);
    pr("(%s) ", type == ES0_X1_TYPE_ISDX ? "isdx" : "vid");
    FA_DEBUG_BITS(ES0, "egr_port", X1_EGR_PORT);
    FA_DEBUG_BITS(ES0, "xvid", X1_XVID);
    if (type == ES0_X1_TYPE_ISDX) {
        FA_DEBUG_BITS(ES0, "isdx", ISDX_ISDX);
    } else {
        FA_DEBUG_BITS(ES0, "gvid", VID_GVID);
    }
    pr("\n");
    FA_DEBUG_BITS(ES0, "cosid", X1_COSID);
    FA_DEBUG_BITS(ES0, "tpid", X1_TPID);
    FA_DEBUG_BITS(ES0, "color", X1_COLOR);
    FA_DEBUG_BITS(ES0, "service_frm", X1_SERVICE_FRM);
    FA_DEBUG_BITS(ES0, "prot_active", X1_PROT_ACTIVE);
    pr("\n");
    FA_DEBUG_BITS(ES0, "encap_id_ena", X1_ENCAP_ID_ENA);
    FA_DEBUG_BITS(ES0, "oam_y1731", X1_OAM_Y1731);
    FA_DEBUG_BITS(ES0, "oam_mel_flags", X1_OAM_MEL_FLAGS);
    pr("\n");
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_debug_es0(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info)
{
    vtss_fa_debug_reg_header(pr, "REW");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_ES0_CTRL, "ES0_CTRL");
    pr("\n");

    return fa_debug_vcap(vtss_state, VTSS_VCAP_TYPE_ES0, pr, info, fa_debug_es0);
}

static vtss_rc fa_es0_esdx_update(vtss_state_t *vtss_state, u16 esdx_old, u16 esdx_new)
{
#if VTSS_OPT_TRACE
    const fa_vcap_props_t *vcap = &fa_vcap_info[FA_VCAP_ES0];
#endif
    fa_vcap_data_t        fa_data, *data = &fa_data;
    u32                   addr;
    vtss_vcap_obj_t       *obj = &vtss_state->vcap.es0.obj;
    vtss_es0_data_t       *es0;
    vtss_vcap_idx_t       idx;
    vtss_vcap_entry_t     *cur;

    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    data->tg = FA_VCAP_TG_X1;
    VTSS_MEMSET(&idx, 0, sizeof(idx));
    for (cur = obj->used; cur != NULL; cur = cur->next, idx.row++) {
        es0 = &cur->data.u.es0;
        if (es0->esdx != esdx_old) {
            continue;
        }
        es0->esdx = esdx_new;

        addr = fa_vcap_entry_addr(vtss_state, data->vcap_type, &idx);
        VTSS_I("%s, row: %u, col: %u, addr: %u, esdx: %u",
               vcap->name, idx.row, idx.col, addr, esdx_new);

        /* Read action */
        VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_READ, FA_VCAP_SEL_ACTION));

        /* Update action fields */
        FA_ACT_SET(ES0, ES0_ESDX_BASE, es0->esdx ? es0->esdx : 1); // Avoid using esdx_base 0 as default

        /* Write action */
        VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION));
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_es0_eflow_update(vtss_state_t *vtss_state, const vtss_eflow_id_t flow_id)
{
#if VTSS_OPT_TRACE
    const fa_vcap_props_t *vcap = &fa_vcap_info[FA_VCAP_ES0];
#endif
    fa_vcap_data_t        fa_data, *data = &fa_data;
    u32                   addr;
    vtss_vcap_obj_t       *obj = &vtss_state->vcap.es0.obj;
    vtss_es0_data_t       *es0;
    vtss_vcap_idx_t       idx;
    vtss_vcap_entry_t     *cur;
    vtss_eflow_entry_t    *eflow = vtss_eflow_lookup(vtss_state, flow_id);
    vtss_xstat_entry_t    *stat;
    u32                   cosid, mep_ena = 0, mep_idx = 0, mip_idx = 0, esdx = 0, cosid_offset = 0;

    VTSS_D("Enter");

    if (eflow != NULL) {
        if (eflow->conf.voe_idx != VTSS_VOE_IDX_NONE) {
            mep_ena = 1;
            mep_idx = eflow->conf.voe_idx;
        }
        if (eflow->conf.voi_idx != VTSS_VOI_IDX_NONE) {
            mip_idx = vtss_fa_voi_idx_to_mip_idx(eflow->conf.voi_idx);
        }
        if (eflow->conf.cnt_enable && (stat = vtss_estat_lookup(vtss_state, eflow->conf.cnt_id)) != NULL) {
            esdx = stat->idx;
            for (cosid = 0; cosid < 8; cosid++) {
                cosid_offset |= ((cosid < stat->cnt ? cosid : (stat->cnt - 1))<< (cosid * 3));
            }
        }
    }

    data->vcap_type = VTSS_VCAP_TYPE_ES0;
    data->tg = FA_VCAP_TG_X1;
    VTSS_MEMSET(&idx, 0, sizeof(idx));
    for (cur = obj->used; cur != NULL; cur = cur->next, idx.row++) {
        es0 = &cur->data.u.es0;
        if (es0->flow_id == flow_id) {
            es0->esdx = esdx;
            addr = fa_vcap_entry_addr(vtss_state, data->vcap_type, &idx);
            VTSS_I("%s, row: %u, col: %u, addr: %u, flow_id: %u",
                   vcap->name, idx.row, idx.col, addr, flow_id);

            /* Read action */
            VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_READ, FA_VCAP_SEL_ACTION));

            /* Update action fields */
            fa_act_ena_set(data, ES0_AO_ES0_OAM_MEP_IDX_VLD, ES0_AO_ES0_OAM_MEP_IDX, ES0_AL_ES0_OAM_MEP_IDX, mep_ena, mep_idx);
            FA_ACT_SET(ES0, ES0_MIP_IDX, mip_idx);
            FA_ACT_SET(ES0, ES0_ESDX_BASE, esdx ? esdx : 1); // Avoid using esdx_base 0 as default
            FA_ACT_SET(ES0, ES0_ESDX_COSID_OFFSET, cosid_offset);

            /* Write action */
            VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->tg, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION));
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_vcap_port_key_set(vtss_state_t *vtss_state, vtss_port_no_t port_no,
                                  u32 lookup, vtss_vcap_key_type_t key_type, BOOL dmac_dip)
{
    u32 etype_sel, ip_sel, port = VTSS_CHIP_PORT(port_no);

    ip_sel = (key_type == VTSS_VCAP_KEY_TYPE_IP_ADDR ? 10 : 0);   // NORMAL_5TUPLE_IP4 or follow ETYPE
    etype_sel = (key_type == VTSS_VCAP_KEY_TYPE_DOUBLE_TAG ? 5 :  // TRI_VID
                 key_type == VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR ? 9 : // NORMAL_7TUPLE
                 dmac_dip ? 8 : 7);                               // NORMAL_DST or NORMAL_SRC
    REG_WRM(VTSS_ANA_CL_ADV_CL_CFG(port, lookup),
            VTSS_F_ANA_CL_ADV_CL_CFG_IP4_CLM_KEY_SEL(ip_sel) |
            VTSS_F_ANA_CL_ADV_CL_CFG_IP6_CLM_KEY_SEL(ip_sel) |
            VTSS_F_ANA_CL_ADV_CL_CFG_ETYPE_CLM_KEY_SEL(etype_sel),
            VTSS_M_ANA_CL_ADV_CL_CFG_IP4_CLM_KEY_SEL |
            VTSS_M_ANA_CL_ADV_CL_CFG_IP6_CLM_KEY_SEL |
            VTSS_M_ANA_CL_ADV_CL_CFG_ETYPE_CLM_KEY_SEL);

    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_vcap_init(vtss_state_t *vtss_state)
{
    VTSS_D("enter");
    VTSS_RC(fa_vcap_initialize(vtss_state, FA_VCAP_TYPE_CLM_A)); /* VCAP_SUPER */
    VTSS_RC(fa_vcap_initialize(vtss_state, FA_VCAP_TYPE_ES0));
    VTSS_RC(fa_vcap_initialize(vtss_state, FA_VCAP_TYPE_ES2));
    VTSS_RC(fa_vcap_initialize(vtss_state, FA_VCAP_TYPE_IP6PFX));
    VTSS_D("exit");

    return VTSS_RC_OK;
}

static vtss_rc fa_vcap_port_map(vtss_state_t *vtss_state)
{
    vtss_port_no_t   port_no;
    u32              addr, port, idx, i, j, key_sel, ip4_sel, ip6_sel, arp_sel;
    vtss_port_mask_t pmask;
    fa_vcap_data_t   vcap_data, *data = &vcap_data;
    struct {
        u8 ip4_mc;
        u8 ip4_uc;
        u8 ip6_mc;
        u8 ip6_uc;
        u8 arp;
    } is2_pacl, is2_vacl, is2_racl, is2_ipmc, *k;

    /* I-PACL key */
    is2_pacl.ip4_mc = 1; /* IP4 */
    is2_pacl.ip4_uc = 1; /* IP4 */
    is2_pacl.ip6_mc = 4; /* IP4 */
    is2_pacl.ip6_uc = 3; /* IP4 */
    is2_pacl.arp = 1;    /* ARP */

    /* I-VACL key: ETYPE */
    VTSS_MEMSET(&is2_vacl, 0, sizeof(is2_vacl));

    /* I-RACL/E-RACL key */
    is2_racl = is2_vacl;
    is2_racl.ip4_mc = 1; /* IP4 */
    is2_racl.ip4_uc = 1; /* IP4 */
    is2_racl.ip6_mc = 1; /* IP_7TUPLE */
    is2_racl.ip6_uc = 1; /* IP_7TUPLE */

    /* IPMC key */
    is2_ipmc = is2_vacl;
    is2_ipmc.ip4_mc = 3; /* IP4_VID */
    is2_ipmc.ip6_mc = 2; /* IP6_VID */

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        for (i = 0; i < 6; i++) {
            if (i == 2) {
                /* NORMAL_SRC for CLM-B[0] (VCL/VTR) */
                key_sel = 7;
            } else if (i > 3) {
                /* TRI_VID for CLM-C[0+1] (EVC/OAM) */
                key_sel = 5;
            } else {
                /* NORMAL_7TUPLE for CLM-A, CLM-B[1] (QCL) */
                key_sel = 9;
            }
            REG_WR(VTSS_ANA_CL_ADV_CL_CFG(port, i),
                   VTSS_F_ANA_CL_ADV_CL_CFG_ETYPE_CLM_KEY_SEL(key_sel) |
                   VTSS_M_ANA_CL_ADV_CL_CFG_LOOKUP_ENA);
        }
        for (i = 0; i < 4; i++) {
            k = (i == 0 ? &is2_pacl : i == 3 ? &is2_ipmc : &is2_vacl);
            REG_WR(VTSS_ANA_ACL_VCAP_S2_KEY_SEL(port, i),
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP4_MC_KEY_SEL(k->ip4_mc) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP4_UC_KEY_SEL(k->ip4_uc) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP6_MC_KEY_SEL(k->ip6_mc) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP6_UC_KEY_SEL(k->ip6_uc) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_ARP_KEY_SEL(k->arp));
        }
        for (i = 0; i < 2; i++) {
            /* Select ES2 lookup key per frame type */
            if (i == 0) {
                /* E-VACL */
                arp_sel = 0; /* ETYPE */
                ip4_sel = 0; /* ETYPE */
                ip6_sel = 0; /* ETYPE */
            } else {
                /* E-PACL */
                arp_sel = 1; /* ARP */
                ip4_sel = 3; /* IP4 */
                ip6_sel = 6; /* IP4 */
            }
            REG_WR(VTSS_EACL_VCAP_ES2_KEY_SEL(port, i),
                   VTSS_F_EACL_VCAP_ES2_KEY_SEL_IP4_KEY_SEL(ip4_sel) |
                   VTSS_F_EACL_VCAP_ES2_KEY_SEL_IP6_KEY_SEL(ip6_sel) |
                   VTSS_F_EACL_VCAP_ES2_KEY_SEL_ARP_KEY_SEL(arp_sel) |
                   VTSS_F_EACL_VCAP_ES2_KEY_SEL_KEY_ENA(1));
        }
        VTSS_RC(fa_acl_port_conf_set(vtss_state, port_no));

        /* Enable IS2 lookup 1-3 */
        REG_WRM_CTL(VTSS_ANA_ACL_VCAP_S2_CFG(port), 1, VTSS_F_ANA_ACL_VCAP_S2_CFG_SEC_ENA(0xe));
    }

    /* IS2 key base at index 70:
       (IS2-2, IRLEG): I-RACL (L3UC or L3MC first pass)
       (IS2-2, VD0)  : IPMC   (L3MC not first pass)
       (IS2-3, ERLEG): E-RACL (L3UC or L3MC not first pass)
       (IS2-3, IRLEG): IPMC   (L3MC first pass)
     */
    for (i = 2; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            idx = (i == 2 && j == 1 ? FA_VCAP_IS2_KEY_SEL_VD0 :
                   i == 3 && j == 0 ? FA_VCAP_IS2_KEY_SEL_ERLEG : FA_VCAP_IS2_KEY_SEL_IRLEG);
            k = (j == 0 ? &is2_racl : &is2_ipmc);
            REG_WR(VTSS_ANA_ACL_VCAP_S2_KEY_SEL(70 + idx, i),
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_KEY_SEL_ENA(1) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IGR_PORT_MASK_SEL(1) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP4_MC_KEY_SEL(k->ip4_mc) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP4_UC_KEY_SEL(k->ip4_uc) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP6_MC_KEY_SEL(k->ip6_mc) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_IP6_UC_KEY_SEL(k->ip6_uc) |
                   VTSS_F_ANA_ACL_VCAP_S2_KEY_SEL_ARP_KEY_SEL(k->arp));
        }
    }

    /* Initialize IS2 lookup 1-3 default actions */
    VTSS_MEMSET(data, 0, sizeof(*data));
    data->type = FA_VCAP_TG_X3;
    data->vcap_type = VTSS_VCAP_TYPE_IS2;
    for (port = 0; port < 3; port++) {
        FA_ACT_SET(IS2, BASE_TYPE_CNT_ID, FA_ACE_CNT_ID_DEF + port);
        addr = fa_vcap_action_addr(data->vcap_type, port, 1);
        VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->type, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION));
    }

    /* IPMC: Enable IS2-2 and IS2-3 lookup for VD0 */
    port = VTSS_CHIP_PORT_VD0;
    REG_WRM_CTL(VTSS_ANA_ACL_VCAP_S2_CFG(port), 1, VTSS_F_ANA_ACL_VCAP_S2_CFG_SEC_ENA(3 << 2));

    /* IPMC: Enable CLM-A0 lookup for VD0 */
    REG_WR(VTSS_ANA_CL_ADV_CL_CFG(port, 0),
           VTSS_F_ANA_CL_ADV_CL_CFG_ETYPE_CLM_KEY_SEL(9) |
           VTSS_M_ANA_CL_ADV_CL_CFG_LOOKUP_ENA);

    /* IPMC: Setup CLM-A0 default action for VD0 */
    VTSS_MEMSET(data, 0, sizeof(*data));
    data->type = FA_VCAP_TG_X3;
    data->vcap_type = VTSS_VCAP_TYPE_CLM_A;
    addr = fa_vcap_action_addr(data->vcap_type, port, 0);
    FA_ACT_SET(CLM, FULL_S2_KEY_SEL_ENA, 1);
    FA_ACT_SET(CLM, FULL_S2_KEY_SEL_IDX, FA_VCAP_IS2_KEY_SEL_VD0);
    VTSS_RC(fa_vcap_entry_cmd(vtss_state, data, addr, data->type, FA_VCAP_CMD_WRITE, FA_VCAP_SEL_ACTION));

    /* Enable LPM on all ports */
    vtss_port_mask_get(vtss_state, vtss_state->l2.port_all, &pmask);
    REG_WR_PMASK(VTSS_ANA_L3_SIP_SECURE_ENA, pmask);

    /* Enable ES0 and use VID key for ISDX 0 */
    REG_WRM_SET(VTSS_REW_ES0_CTRL, VTSS_M_REW_ES0_CTRL_ES0_LU_ENA);
    REG_WRM_CLR(VTSS_ANA_L2_SERVICE_CTRL(0), VTSS_M_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA);
    REG_WR(VTSS_VCAP_ES0_VCAP_CORE_MAP,
           VTSS_F_VCAP_ES0_VCAP_CORE_MAP_CORE_MAP(1));

    /* Enable ES2 */
    for (i = 0; i < 4; i++) {
        REG_WR(VTSS_VCAP_ES2_VCAP_CORE_IDX, VTSS_F_VCAP_ES2_VCAP_CORE_IDX_CORE_IDX(i));
        REG_WR(VTSS_VCAP_ES2_VCAP_CORE_MAP, VTSS_F_VCAP_ES2_VCAP_CORE_MAP_CORE_MAP(1));
    }

    /* Use Jaguar-2 style IPv4 fragment filtering in CLM/IS2/ES2 */
    REG_WRM_SET(VTSS_ANA_ACL_VCAP_S2_FRAGMENT_CFG, VTSS_M_ANA_ACL_VCAP_S2_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES_DIS);
    REG_WRM_SET(VTSS_ANA_CL_CLM_FRAGMENT_CFG, VTSS_M_ANA_CL_CLM_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES_DIS);
    REG_WRM_SET(VTSS_EACL_VCAP_ES2_FRAGMENT_CFG, VTSS_M_EACL_VCAP_ES2_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES_DIS);

    /* Replace 40 MSB of DMAC if enabled in IS2 action */
    REG_WRM(VTSS_ANA_ACL_SWAP_IP_CTRL,
            VTSS_F_ANA_ACL_SWAP_IP_CTRL_DMAC_REPL_OFFSET_VAL(8),
            VTSS_M_ANA_ACL_SWAP_IP_CTRL_DMAC_REPL_OFFSET_VAL);

    /* I-RACL discard: Disable IRLEG and ERLEG statistics */
    REG_WR(VTSS_ANA_ACL_VCAP_S2_RLEG_STAT(FA_RLEG_STAT_IRACL),
           VTSS_F_ANA_ACL_VCAP_S2_RLEG_STAT_IRLEG_STAT_MASK(0x3f) |
           VTSS_F_ANA_ACL_VCAP_S2_RLEG_STAT_ERLEG_STAT_MASK(0x3f));

    /* E-RACL discard: Disable ERLEG statistics */
    REG_WR(VTSS_ANA_ACL_VCAP_S2_RLEG_STAT(FA_RLEG_STAT_ERACL),
           VTSS_F_ANA_ACL_VCAP_S2_RLEG_STAT_IRLEG_STAT_MASK(0) |
           VTSS_F_ANA_ACL_VCAP_S2_RLEG_STAT_ERLEG_STAT_MASK(0x3f));

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_vcap_state_t     *state = &vtss_state->vcap;
    vtss_vcap_super_obj_t *vcap_super = &state->vcap_super;
    vtss_vcap_obj_t       *clm_a = &state->clm_a.obj;
    vtss_vcap_obj_t       *clm_b = &state->clm_b.obj;
    vtss_vcap_obj_t       *clm_c = &state->clm_c.obj;
    vtss_vcap_obj_t       *lpm = &state->lpm.obj;
    vtss_vcap_obj_t       *is2_a = &state->is2.obj;
    vtss_vcap_obj_t       *is2_b = &state->is2_b.obj;
    vtss_vcap_obj_t       *es0 = &state->es0.obj;
    vtss_vcap_obj_t       *es2 = &state->es2.obj;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        /* VCAP_SUPER */
        vcap_super->block_map = fa_vcap_super_block_map;
        vcap_super->block_move = fa_vcap_super_block_move;

        /* CLM_A */
        clm_a->entry_add = fa_clm_a_entry_add;
        clm_a->entry_del = fa_clm_a_entry_del;
        clm_a->entry_move = fa_clm_a_entry_move;
        clm_a->entry_get = fa_clm_a_entry_get;
        clm_a->vcap_super = vcap_super;

        /* CLM_B */
        clm_b->entry_add = fa_clm_b_entry_add;
        clm_b->entry_del = fa_clm_b_entry_del;
        clm_b->entry_move = fa_clm_b_entry_move;
        clm_b->entry_get = fa_clm_b_entry_get;
        clm_b->vcap_super = vcap_super;

        /* CLM_C */
        clm_c->entry_add = fa_clm_c_entry_add;
        clm_c->entry_del = fa_clm_c_entry_del;
        clm_c->entry_move = fa_clm_c_entry_move;
        clm_c->entry_get = fa_clm_c_entry_get;
        clm_c->vcap_super = vcap_super;
        state->clm_entry_update = fa_clm_entry_update;

        /* LPM */
        lpm->entry_add = fa_lpm_entry_add;
        lpm->entry_del = fa_lpm_entry_del;
        lpm->entry_move = fa_lpm_entry_move;
        lpm->entry_get = fa_lpm_entry_get;
        lpm->vcap_super = vcap_super;

        /* IS2_A */
        is2_a->entry_add = fa_is2_a_entry_add;
        is2_a->entry_del = fa_is2_a_entry_del;
        is2_a->entry_move = fa_is2_a_entry_move;
        is2_a->entry_get = fa_is2_a_entry_get;
        is2_a->vcap_super = vcap_super;

        /* IS2_B */
        is2_b->entry_add = fa_is2_b_entry_add;
        is2_b->entry_del = fa_is2_b_entry_del;
        is2_b->entry_move = fa_is2_b_entry_move;
        is2_b->entry_get = fa_is2_b_entry_get;
        is2_b->vcap_super = vcap_super;
        state->is2_entry_update = fa_is2_entry_update;

        /* ES0 */
        es0->max_count = VTSS_FA_ES0_CNT;
        es0->entry_add = fa_es0_entry_add;
        es0->entry_del = fa_es0_entry_del;
        es0->entry_move = fa_es0_entry_move;
        es0->entry_get = fa_es0_entry_get;
        state->es0_entry_update = fa_es0_entry_update;
        state->es0_esdx_update = fa_es0_esdx_update;
        state->es0_eflow_update = fa_es0_eflow_update;

        /* ES2 */
        es2->max_count = FA_ES2_CNT;
        es2->max_rule_count = VTSS_ES2_CNT;
        es2->entry_add = fa_es2_entry_add;
        es2->entry_del = fa_es2_entry_del;
        es2->entry_move = fa_es2_entry_move;
        es2->entry_get = fa_es2_entry_get;

        /* ACL */
        state->acl_policer_set = fa_acl_policer_set;
        state->acl_sip_set = fa_acl_sip_set;
        state->acl_port_set = fa_acl_port_conf_set;
        state->acl_port_counter_get = fa_acl_port_counter_get;
        state->acl_port_counter_clear = fa_acl_port_counter_clear;
        state->acl_ace_add = fa_ace_add;
        state->acl_ace_del = fa_ace_del;
        state->acl_ace_counter_get = vtss_cmn_ace_counter_get;
        state->acl_ace_counter_clear = vtss_cmn_ace_counter_clear;
        state->range_commit = fa_clm_range_commit;

        /* HACL */
        state->hace_add = fa_hace_add;
        state->hace_del = fa_hace_del;
        state->hace_counter_get = fa_hace_counter_get;
        state->hace_counter_clear = fa_hace_counter_clear;
        break;

    case VTSS_INIT_CMD_INIT:
        vtss_state->vcap.acl_user = VTSS_IS2_USER_IPACL;
        VTSS_RC(fa_vcap_init(vtss_state));
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(fa_vcap_port_map(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_FA */
