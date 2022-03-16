// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_VCAP
#include "vtss_ocelot_cil.h"

#if defined(VTSS_ARCH_OCELOT)

/* ================================================================= *
 *  TCAM properties
 * ================================================================= */

/* TCAM entries */
enum vtss_tcam_sel {
    VTSS_TCAM_SEL_ENTRY   = VTSS_BIT(0),
    VTSS_TCAM_SEL_ACTION  = VTSS_BIT(1),
    VTSS_TCAM_SEL_COUNTER = VTSS_BIT(2),
    VTSS_TCAM_SEL_ALL     = VTSS_BITMASK(3),
};

enum vtss_tcam_cmd {
    VTSS_TCAM_CMD_WRITE      = 0, /* Copy from Cache to TCAM */
    VTSS_TCAM_CMD_READ       = 1, /* Copy from TCAM to Cache */
    VTSS_TCAM_CMD_MOVE_UP    = 2, /* Move <count> up */
    VTSS_TCAM_CMD_MOVE_DOWN  = 3, /* Move <count> down */
    VTSS_TCAM_CMD_INITIALIZE = 4, /* Write all (from cache) */
};

enum vtss_tcam_bank {
    VTSS_TCAM_IS0,
    VTSS_TCAM_IS1,
    VTSS_TCAM_IS2,
    VTSS_TCAM_ES0
};

typedef struct {
    const char *name;        /* Symbolic name */
    u32 target;              /* Target offset */
    u16 tg_width;            /* Type-group width (in bits) */
    u16 sw_count;            /* Sub word count */
    u16 entry_count;         /* Entry count */
    u16 entry_words;         /* Number of entry words */
    u16 entry_width;         /* Entry width (in bits) */
    u16 action_count;        /* Action count */
    u16 action_words;        /* Number of action words */
    u16 action_width;        /* Action width (in bits) */
    u16 action_type_width;   /* Action type width (in bits) */
    u16 action_type_0_width; /* Action type 0 width (in bits) */
    u16 action_type_1_width; /* Action type 1 width (in bits) */
    u16 action_type_0_count; /* Action type 0 sub word count */
    u16 action_type_1_count; /* Action type 1 sub word count */
    u16 counter_words;       /* Number of counter words */
    u16 counter_width;       /* Counter width (in bits) */
} tcam_props_t;

#define BITS_TO_DWORD(x) (1+(((x)-1)/32))

/* Entry/action width (number of bits) */
#define IS0_ENTRY_WIDTH   152 // 2*76 (MLBS); longest of MLBS and MLL
#define IS0_ACTION_WIDTH  178
#define IS1_ENTRY_WIDTH   376
#define IS2_ENTRY_WIDTH   376
#define ES0_ENTRY_WIDTH   29
#define IS1_ACTION_WIDTH  312
#define IS2_ACTION_WIDTH  99
#define ES0_ACTION_WIDTH  72

static const tcam_props_t tcam_info[] = {
#if defined(VTSS_FEATURE_IS0)
    [VTSS_TCAM_IS0] = {
        .name = "IS0",
        .target = VTSS_TO_IS0,
        .tg_width = 2,
        .sw_count = 2,
        .entry_count = SRVL_IS0_CNT,
        .entry_words = BITS_TO_DWORD(IS0_ENTRY_WIDTH),
        .entry_width = IS0_ENTRY_WIDTH,
        .action_count = SRVL_IS0_CNT + 2,
        .action_words = BITS_TO_DWORD(IS0_ACTION_WIDTH),
        .action_width = IS0_ACTION_WIDTH,
        .action_type_width = 1,
        .action_type_0_width = 67,
        .action_type_1_width = 89,
        .action_type_0_count = 1,
        .action_type_1_count = 2,
        .counter_words = BITS_TO_DWORD(2),
        .counter_width = 1,
    },
#endif  /* VTSS_FEATURE_IS0 */
    [VTSS_TCAM_IS1] = {
        .name = "IS1",
        .target = VTSS_TO_S1,
        .tg_width = 2,
        .sw_count = 4,
        .entry_count = SRVL_IS1_CNT,
        .entry_words = BITS_TO_DWORD(IS1_ENTRY_WIDTH),
        .entry_width = IS1_ENTRY_WIDTH,
        .action_count = SRVL_IS1_CNT + 1,
        .action_words = BITS_TO_DWORD(IS1_ACTION_WIDTH),
        .action_width = IS1_ACTION_WIDTH,
        .action_type_width = 0,
        .action_type_0_width = (IS1_ACTION_WIDTH / 4),
        .action_type_1_width = 0,
        .action_type_0_count = 4,
        .action_type_1_count = 0,
        .counter_words = BITS_TO_DWORD(4),
        .counter_width = 1,
    },
    [VTSS_TCAM_IS2] = {
        .name = "IS2",
        .target = VTSS_TO_S2,
        .tg_width = 2,
        .sw_count = 4,
        .entry_count = SRVL_IS2_CNT,
        .entry_words = BITS_TO_DWORD(IS2_ENTRY_WIDTH),
        .entry_width = IS2_ENTRY_WIDTH,
        .action_count = (SRVL_IS2_CNT + VTSS_CHIP_PORTS + 2),
        .action_words = BITS_TO_DWORD(IS2_ACTION_WIDTH),
        .action_width = (IS2_ACTION_WIDTH),
        .action_type_width = 1,
        .action_type_0_width = (IS2_AO_ACL_ID + IS2_AL_ACL_ID),
        .action_type_1_width = 6,
        .action_type_0_count = 2,
        .action_type_1_count = 4,
        .counter_words = BITS_TO_DWORD(4*32),
        .counter_width = 32,
    },
    [VTSS_TCAM_ES0] = {
        .name = "ES0",
        .target = VTSS_TO_ES0,
        .tg_width = 1,
        .sw_count = 1,
        .entry_count = SRVL_ES0_CNT,
        .entry_words = BITS_TO_DWORD(ES0_ENTRY_WIDTH),
        .entry_width = ES0_ENTRY_WIDTH,
        .action_count = (SRVL_ES0_CNT + VTSS_CHIP_PORTS),
        .action_words = BITS_TO_DWORD(ES0_ACTION_WIDTH),
        .action_width = ES0_ACTION_WIDTH,
        .action_type_width = 0,
        .action_type_0_width = ES0_ACTION_WIDTH,
        .action_type_1_width = 0,
        .action_type_0_count = 1,
        .action_type_1_count = 0,
        .counter_words = BITS_TO_DWORD(1),
        .counter_width = 1,
    }
};

#define VTSS_TCAM_ENTRY_WIDTH   12 /* Max entry width (32bit words) */
#define VTSS_TCAM_COUNTER_WIDTH 4  /* Max counter width (32bit words) */

typedef struct {
    u32 entry[VTSS_TCAM_ENTRY_WIDTH];     /* ENTRY_DAT */
    u32 mask[VTSS_TCAM_ENTRY_WIDTH];      /* MASK_DAT */
    u32 action[VTSS_TCAM_ENTRY_WIDTH];    /* ACTION_DAT */
    u32 counter[VTSS_TCAM_COUNTER_WIDTH]; /* CNT_DAT */
    u32 tg;                               /* TG_DAT */
    u32 type;                             /* Action type */
    u32 tg_sw;                            /* Current type-group */
    u32 cnt;                              /* Current counter */
    u32 key_offset;                       /* Current entry offset */
    u32 action_offset;                    /* Current action offset */
    u32 counter_offset;                   /* Current counter offset */
    u32 tg_value;                         /* Current type-group value */
    u32 tg_mask;                          /* Current type-group mask */
} srvl_tcam_data_t;

typedef struct {
    BOOL                is_action;
    vtss_debug_printf_t pr;
    srvl_tcam_data_t    data;
} srvl_debug_info_t;

static void srvl_debug_bits(srvl_debug_info_t *info, const char *name, u32 offset, u32 len)
{
    vtss_debug_printf_t pr = info->pr;
    srvl_tcam_data_t    *data = &info->data;
    u32                 i,j;

    if (name)
        pr("%s: ", name);
    for (i = 0; i < len; i++) {
        j = (len - 1 - i);
        if (i != 0 && (j % 8) == 7)
            pr(".");
        j += (offset + (info->is_action ? data->action_offset : data->key_offset));
        pr("%c", info->is_action ? vtss_bs_bit_get(data->action, j) ? '1' : '0' :
           vtss_bs_bit_get(data->mask, j) ? 
           (vtss_bs_bit_get(data->entry, j) ? '1' : '0') : 'X');
    }
    pr(len > 24 ? "\n" : " ");
}

static void srvl_debug_bit(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bits(info, name, offset, 1);
}

/* Debug bytes in chunks of 32-bit data */
static void srvl_debug_bytes(srvl_debug_info_t *info, const char *name, u32 offset, u32 len)
{
    u32  i, n, count;
    char buf[64];
    
    n = (len % 32);
    if (n == 0)
        n = 32;
    if (len <= 32) {
        /* One chunk */
        srvl_debug_bits(info, name, offset, n);
    } else if (len <= 56) {
        /* Two chunks, use one output line */
        srvl_debug_bits(info, name, offset, n);
        srvl_debug_bits(info, NULL, offset + n, 32);
    } else {
        /* Three or more chunks, use one output line for each */
        count = VTSS_DIV_ROUND_UP(len, 32);
        for (i = 0; i < count; i++) {
            VTSS_SPRINTF(buf, "%s_%u", name, count - i - 1);
            srvl_debug_bits(info, buf, offset, n);
            if (n <= 24)
                info->pr("\n");
            offset += n;
            n = 32;
        }
    }
}

static void srvl_debug_u48(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bytes(info, name, offset, 48);
}

static void srvl_debug_u32(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bits(info, name, offset, 32);
}

static void srvl_debug_u128(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bytes(info, name, offset, 128);
}

static void srvl_debug_u12(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bits(info, name, offset, 12);
}

static void srvl_debug_u16(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bits(info, name, offset, 16);
}

static void srvl_debug_u8(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bits(info, name, offset, 8);
}

static void srvl_debug_u6(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bits(info, name, offset, 6);
}

static void srvl_debug_u3(srvl_debug_info_t *info, const char *name, u32 offset)
{
    srvl_debug_bits(info, name, offset, 3);
}

static u32 srvl_act_bs_get(srvl_debug_info_t *info, u32 offs, u32 len)
{
    return vtss_bs_get(info->data.action, offs + info->data.action_offset, len);
}

static u32 srvl_entry_bs_get(srvl_debug_info_t *info, u32 offs, u32 len)
{
    return vtss_bs_get(info->data.entry, offs + info->data.key_offset, len);
}

static void srvl_debug_action_len(srvl_debug_info_t *info,
                                  const char *name, u32 offs, u32 len, u32 offs_val, u32 len_val)
{
    vtss_debug_printf_t pr = info->pr;
    srvl_tcam_data_t    *data = &info->data;
    BOOL                enable, multi = 0;
    u32                 num = 0;
    int                 i, length = VTSS_STRLEN(name);

    if (offs_val != 0 && len != 1) {
        /* 'Enable' field consists of multiple bits */
        multi = 1;
        num = srvl_act_bs_get(info, offs, len);
        enable = (num ? 1 : 0);
    } else
        enable = vtss_bs_bit_get(data->action, offs + data->action_offset);
    
    for (i = 0; i < length; i++)
        pr("%c", enable ? toupper(name[i]) : tolower(name[i]));

    if (len_val) {
        pr(":");
        if (multi)
            pr("%u/", num);
        pr("%u", srvl_act_bs_get(info, offs_val, len_val));
    }
    pr(" ");
}

static void srvl_debug_action(srvl_debug_info_t *info,
                              const char *name, u32 offs, u32 offs_val, u32 len_val)
{
    srvl_debug_action_len(info, name, offs, offs_val - offs, offs_val, len_val);
}

static void srvl_debug_fld(srvl_debug_info_t *info, const char *name, u32 offs, u32 len)
{
    info->pr("%s:%u ", name, srvl_act_bs_get(info, offs, len));
}

/* ================================================================= *
 *  VCAP key processing
 * ================================================================= */

static void srvl_vcap_key_set(srvl_tcam_data_t *data, u32 offset, u32 width, 
                              u32 value, u32 mask)
{
    VTSS_N("offset: %u, key_offset: %u, width: %u, value: 0x%08x, mask: 0x%08x", 
           offset, data->key_offset, width, value, mask);

    if (width > 32) {
        VTSS_E("illegal width: %u, offset: %u", width, offset);
    } else { 
        vtss_bs_set(data->entry, offset + data->key_offset, width, value);
        vtss_bs_set(data->mask, offset + data->key_offset, width, mask);
    }
}

static void srvl_vcap_key_bit_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_bit_t fld)
{
    srvl_vcap_key_set(data, offset, 1, 
                      fld == VTSS_VCAP_BIT_1 ? 1 : 0, fld == VTSS_VCAP_BIT_ANY ? 0 : 1);  
}

static void srvl_vcap_key_bit_inv_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_bit_t fld)
{
    srvl_vcap_key_set(data, offset, 1, 
                      fld == VTSS_VCAP_BIT_0 ? 1 : 0, fld == VTSS_VCAP_BIT_ANY ? 0 : 1);  
}

static void srvl_vcap_key_ipv4_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_ip_t *fld)
{
    srvl_vcap_key_set(data, offset, 32, fld->value, fld->mask);  
}

static void srvl_vcap_key_u3_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_u8_t *fld)
{
    srvl_vcap_key_set(data, offset, 3, fld->value, fld->mask);  
}

static void srvl_vcap_key_u6_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_u8_t *fld)
{
    srvl_vcap_key_set(data, offset, 6, fld->value, fld->mask);  
}

static void srvl_vcap_key_u8_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_u8_t *fld)
{
    srvl_vcap_key_set(data, offset, 8, fld->value, fld->mask);  
}

static void srvl_vcap_key_bytes_set(srvl_tcam_data_t *data, u32 offset, 
                                    u8 *val, u8 *msk, u32 count)
{
    u32 i, j, n = 0, value = 0, mask = 0;
    
    /* Data wider than 32 bits are split up in chunks of maximum 32 bits.
       The 32 LSB of the data are written to the 32 MSB of the TCAM. */
    offset += (count * 8);
    for (i = 0; i < count; i++) {
        j = (count - i - 1);
        value += (val[j] << n);
        mask += (msk[j] << n);
        n += 8;
        if (n == 32 || (i + 1) == count) {
            offset -= n;
            srvl_vcap_key_set(data, offset, n, value, mask);  
            n = 0;
            value = 0;
            mask = 0;
        }
    }
}

static void srvl_vcap_key_u16_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_u16_t *fld)
{
    srvl_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 2);
}

static void srvl_vcap_key_u40_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_u40_t *fld)
{
    srvl_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 5);
}

static void srvl_vcap_key_u48_set(srvl_tcam_data_t *data, u32 offset, vtss_vcap_u48_t *fld)
{
    srvl_vcap_key_bytes_set(data, offset, fld->value, fld->mask, 6);
}

/* ================================================================= *
 *  VCAP action processing
 * ================================================================= */

static void srvl_vcap_action_set(srvl_tcam_data_t *data, u32 offset, u32 width, u32 value)
{
    VTSS_N("offset: %u, width: %u, value: 0x%08x", offset, width, value);
    
    if (width > 32) {
        VTSS_E("illegal width: %u, offset: %u", width, offset);
    } else { 
        vtss_bs_set(data->action, offset + data->action_offset, width, value);
    }
}

static void srvl_vcap_action_bit_set(srvl_tcam_data_t *data, u32 offset, u32 value)
{
    srvl_vcap_action_set(data, offset, 1, value ? 1 : 0);
}

/* ================================================================= *
 *  VCAP cache copy operations
 * ================================================================= */

static vtss_rc srvl_vcap_cmd(vtss_state_t *vtss_state,
                             const tcam_props_t *tcam, u16 ix, int cmd, int sel)
{
    u32 tgt = tcam->target;
    u32 value = (VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD(cmd) |
                 VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR(ix) |
                 VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT);

    if ((sel & VTSS_TCAM_SEL_ENTRY) && ix >= tcam->entry_count)
        return VTSS_RC_ERROR;

    if (!(sel & VTSS_TCAM_SEL_ENTRY))
        value |= VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS;

    if (!(sel & VTSS_TCAM_SEL_ACTION))
        value |= VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS;

    if (!(sel & VTSS_TCAM_SEL_COUNTER))
        value |= VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS;

    SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL(tgt), value);

    do {
        SRVL_RD(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL(tgt), &value);
    } while (value & VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT);

    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_entry2cache(vtss_state_t *vtss_state,
                                     const tcam_props_t *tcam, srvl_tcam_data_t *data)
{
    u32 i, tgt = tcam->target;

    for (i = 0; i < tcam->entry_words; i++) {
        SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tgt, i), data->entry[i]);
        SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tgt, i), ~data->mask[i]);
    }
    SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_TG_DAT(tgt), data->tg);
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_cache2entry(vtss_state_t *vtss_state,
                                     const tcam_props_t *tcam, srvl_tcam_data_t *data)
{
    u32 i, m, tgt = tcam->target;

    for (i = 0; i < tcam->entry_words; i++) {
        SRVL_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tgt, i), &data->entry[i]);
        SRVL_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tgt, i), &m);
        data->mask[i] = ~m;           /* Invert mask */
    }
    SRVL_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_TG_DAT(tgt), &data->tg);
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_action2cache(vtss_state_t *vtss_state,
                                      const tcam_props_t *tcam, srvl_tcam_data_t *data)
{
    u32 i, width, mask, tgt = tcam->target;
    
    /* Encode action type */
    width = tcam->action_type_width;
    if (width) {
        mask = VTSS_BITMASK(width);
        data->action[0] = ((data->action[0] & ~mask) | data->type);
    }

    for (i = 0; i < tcam->action_words; i++)
        SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(tgt, i), data->action[i]);
    for (i = 0; i < tcam->counter_words; i++)
        SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tgt, i), data->counter[i]);

    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_cache2action(vtss_state_t *vtss_state,
                                      const tcam_props_t *tcam, srvl_tcam_data_t *data)
{
    u32 i, width, tgt = tcam->target;

    for (i = 0; i < tcam->action_words; i++)
        SRVL_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(tgt, i), &data->action[i]);
    for (i = 0; i < tcam->counter_words; i++)
        SRVL_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tgt, i), &data->counter[i]);

    /* Extract action type */
    width = tcam->action_type_width;
    data->type = (width ? VTSS_EXTRACT_BITFIELD(data->action[0], 0, width) : 0);
        
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_initialize(vtss_state_t *vtss_state, int bank)
{
    const tcam_props_t *tcam = &tcam_info[bank];
    srvl_tcam_data_t   data;
    u32                tgt = tcam->target;

    VTSS_MEMSET(&data, 0, sizeof(data));
    
    /* First write entries */
    VTSS_RC(srvl_vcap_entry2cache(vtss_state, tcam, &data));
    SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tgt),
            VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(tcam->entry_count));
    VTSS_RC(srvl_vcap_cmd(vtss_state, tcam, 0, VTSS_TCAM_CMD_INITIALIZE, VTSS_TCAM_SEL_ENTRY));

    /* Then actions and counters */
    VTSS_RC(srvl_vcap_action2cache(vtss_state, tcam, &data));
    SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tgt),
            VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(tcam->action_count));
    VTSS_RC(srvl_vcap_cmd(vtss_state, tcam, 0, VTSS_TCAM_CMD_INITIALIZE, 
                          VTSS_TCAM_SEL_ACTION | VTSS_TCAM_SEL_COUNTER));

    return VTSS_RC_OK;
}

/* Convert from 0-based row to VCAP entry row and run command */
static vtss_rc srvl_vcap_row_cmd(vtss_state_t *vtss_state,
                                 const tcam_props_t *tcam, u32 row, int cmd, int sel)
{
    return srvl_vcap_cmd(vtss_state, tcam, tcam->entry_count - row - 1, cmd, sel);
}

/* Convert from 0-based port to VCAP entry row and run command */
static vtss_rc srvl_vcap_port_cmd(vtss_state_t *vtss_state,
                                  const tcam_props_t *tcam, u32 port, int cmd, int sel)
{
    return srvl_vcap_cmd(vtss_state, tcam, tcam->entry_count + port, cmd, sel);
}

/* ================================================================= *
 *  VCAP get/set/add/del/move utilities
 * ================================================================= */

/* Calculate offsets for entry */
static vtss_rc srvl_vcap_data_get(const tcam_props_t *tcam, vtss_vcap_idx_t *idx, 
                                  srvl_tcam_data_t *data)
{
    u32 i, col, offset, count, cnt, base, width = tcam->tg_width;
    
    VTSS_N("%s, row: %u, col: %u, key_size: %s",
            tcam->name, idx->row, idx->col, vtss_vcap_key_size2txt(idx->key_size));

    /* Calculate type-group value/mask */
    switch (idx->key_size) {
    case VTSS_VCAP_KEY_SIZE_FULL:
        count = 1;
        data->tg_sw = VCAP_TG_FULL;
        break;
    case VTSS_VCAP_KEY_SIZE_HALF:
        count = 2;
        data->tg_sw = VCAP_TG_HALF;
        break;
    case VTSS_VCAP_KEY_SIZE_QUARTER:
        count = 4;
        data->tg_sw = VCAP_TG_QUARTER;
        break;
    default:
        VTSS_E("illegal key size");
        return VTSS_RC_ERROR;
    }
    col = (count - idx->col - 1);
    cnt = (tcam->sw_count / count);
    base = (tcam->sw_count - idx->col * cnt - cnt);
    data->tg_value = 0;
    data->tg_mask = 0;
    for (i = 0; i < cnt; i++) {
        offset = ((base + i) * width);
        data->tg_value |= VTSS_ENCODE_BITFIELD(data->tg_sw, offset, width);
        data->tg_mask |= VTSS_ENCODE_BITMASK(offset, width);
    }
    
    /* Calculate key/action/counter offsets */
    data->key_offset = (base * tcam->entry_width)/tcam->sw_count;
    data->counter_offset = (cnt * col * tcam->counter_width);
    if (data->type) {
        width = tcam->action_type_1_width;
        cnt = tcam->action_type_1_count;
    } else {
        width = tcam->action_type_0_width;
        cnt = tcam->action_type_0_count;
    }
    data->action_offset = (((cnt * col * width) / count) + tcam->action_type_width);

    VTSS_N("tg_value: 0x%08x, tg_mask: 0x%08x",
            data->tg_value, data->tg_mask);
    VTSS_N("key_offset: %u, action_offset: %u, counter_offset: %u",
            data->key_offset, data->action_offset, data->counter_offset);
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_entry_get(vtss_state_t *vtss_state,
                                   const tcam_props_t *tcam, vtss_vcap_idx_t *idx, 
                                   srvl_tcam_data_t *data)
{
    VTSS_I("%s, row: %u", tcam->name, idx->row);

    /* Read row */
    VTSS_MEMSET(data, 0, sizeof(*data));
    VTSS_RC(srvl_vcap_row_cmd(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_ALL));
    VTSS_RC(srvl_vcap_cache2action(vtss_state, tcam, data));
    VTSS_RC(srvl_vcap_cache2entry(vtss_state, tcam, data));

    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_entry_data_get(vtss_state_t *vtss_state,
                                        const tcam_props_t *tcam, vtss_vcap_idx_t *idx, 
                                        srvl_tcam_data_t *data)
{
    /* Read row and calculate offsets */
    VTSS_RC(srvl_vcap_entry_get(vtss_state, tcam, idx, data));
    VTSS_RC(srvl_vcap_data_get(tcam, idx, data)); 

    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_entry_set(vtss_state_t *vtss_state,
                                   const tcam_props_t *tcam, vtss_vcap_idx_t *idx, 
                                   srvl_tcam_data_t *data)
{
    VTSS_I("%s, row: %u", tcam->name, idx->row);

    /* Write row */
    VTSS_RC(srvl_vcap_entry2cache(vtss_state, tcam, data));
    VTSS_RC(srvl_vcap_action2cache(vtss_state, tcam, data));
    VTSS_RC(srvl_vcap_row_cmd(vtss_state, tcam, idx->row, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ALL));

    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_counter_get(vtss_state_t *vtss_state,
                                     int bank, vtss_vcap_idx_t *idx, u32 *counter, BOOL clear) 
{
    const tcam_props_t *tcam = &tcam_info[bank];
    srvl_tcam_data_t   tcam_data, *data = &tcam_data;
    
    VTSS_I("%s, row: %u, col: %u, key_size: %s, clear: %u",
            tcam->name, idx->row, idx->col, vtss_vcap_key_size2txt(idx->key_size), clear);

    /* Read counter at row */
    VTSS_RC(srvl_vcap_row_cmd(vtss_state,
                              tcam, idx->row, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_COUNTER));
    VTSS_RC(srvl_vcap_cache2action(vtss_state, tcam, data));
    VTSS_RC(srvl_vcap_data_get(tcam, idx, data));
    *counter = vtss_bs_get(data->counter, data->counter_offset, tcam->counter_width);

    if (clear) {
        /* Clear counter at row */
        vtss_bs_set(data->counter, data->counter_offset, tcam->counter_width, 0);
        VTSS_RC(srvl_vcap_action2cache(vtss_state, tcam, data));
        VTSS_RC(srvl_vcap_row_cmd(vtss_state,
                                  tcam, idx->row, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_COUNTER));
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_entry_add(vtss_state_t *vtss_state,
                                   const tcam_props_t *tcam, vtss_vcap_idx_t *idx, 
                                   srvl_tcam_data_t *data)
{
    u32 type = data->type, cnt = data->cnt;

    VTSS_I("%s, row: %u, col: %u, key_size: %s, counter: %u",
            tcam->name, idx->row, idx->col, vtss_vcap_key_size2txt(idx->key_size), cnt);

    /* Read row */
    VTSS_RC(srvl_vcap_entry_get(vtss_state, tcam, idx, data));
    data->type = type;

    /* Encode type-group and counter */
    VTSS_RC(srvl_vcap_data_get(tcam, idx, data));
    data->tg = ((data->tg & ~data->tg_mask) | data->tg_value);
    vtss_bs_set(data->counter, data->counter_offset,  tcam->counter_width, cnt);
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_entry_del(vtss_state_t *vtss_state, int bank, vtss_vcap_idx_t *idx)
{
    const tcam_props_t *tcam = &tcam_info[bank];
    srvl_tcam_data_t   tcam_data, *data = &tcam_data;

    VTSS_I("%s, row: %u, col: %u, key_size: %s",
            tcam->name, idx->row, idx->col, vtss_vcap_key_size2txt(idx->key_size));

    /* Read row */
    VTSS_RC(srvl_vcap_entry_get(vtss_state, tcam, idx, data));

    /* Encode type-group */
    VTSS_RC(srvl_vcap_data_get(tcam, idx, data));
    data->tg = (data->tg & ~data->tg_mask);
    
    /* Write row */
    return srvl_vcap_entry_set(vtss_state, tcam, idx, data);
}

static void srvl_vcap_copy(u32 *src, u32 *dst, u32 src_offs, u32 dst_offs, u32 copy_len)
{
    u32 i, count, len, value;
    
    count = (copy_len / 32);
    len = 32;
    for (i = 0; i <= count; i++, src_offs += 32, dst_offs += 32) {
        if (i == count && (len = (copy_len % 32)) == 0)
            break;

        value = vtss_bs_get(src, src_offs, len);
        vtss_bs_set(dst, dst_offs, len, value);
    }
}

static void srvl_vcap_data_copy(srvl_tcam_data_t *src, srvl_tcam_data_t *dst, 
                                u32 key_len, u32 action_len, u32 counter_len)
{
    VTSS_N("src->key_offset: %u, key_len: %u, dst->key_offset: %u",
           src->key_offset, key_len, dst->key_offset);
    VTSS_N("src->action_offset: %u, action_len: %u, dst->action_offset: %u",
           src->action_offset, action_len, dst->action_offset);
    VTSS_N("src->counter_offset: %u, counter_len: %u, dst->counter_offset: %u",
           src->counter_offset, counter_len, dst->counter_offset);
    
    /* Copy key data */
    srvl_vcap_copy(src->entry, dst->entry, src->key_offset, dst->key_offset, key_len);
    srvl_vcap_copy(src->mask, dst->mask, src->key_offset, dst->key_offset, key_len);

    /* Copy action data */
    srvl_vcap_copy(src->action, dst->action, src->action_offset, dst->action_offset, action_len);

    /* Copy counter data */
    srvl_vcap_copy(src->counter, dst->counter, src->counter_offset, dst->counter_offset, 
                   counter_len);
}

static vtss_rc srvl_vcap_entry_move(vtss_state_t *vtss_state,
                                    int bank, vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    const tcam_props_t *tcam = &tcam_info[bank];
    srvl_tcam_data_t   data[2], *src = &data[0], *dst = &data[1], *tmp;
    vtss_vcap_idx_t    cur_idx;
    u32                col_count, rule_count = 0, tgw, key_len, action_len, counter_len, col;
    BOOL               smac_sip4 = (bank == VTSS_TCAM_IS2 && idx->key_size == VTSS_VCAP_KEY_SIZE_QUARTER);

    VTSS_I("%s, row: %u, col: %u, key_size: %s, count: %u, up: %u",
            tcam->name, idx->row, idx->col, vtss_vcap_key_size2txt(idx->key_size), count, up);

    /* Check key size and count */
    if (idx->key_size > VTSS_VCAP_KEY_SIZE_QUARTER || count == 0) {
        VTSS_E("illegal key_size: %s or count: %u",
                vtss_vcap_key_size2txt(idx->key_size), count);
        return VTSS_RC_ERROR;
    }

    /* Move FULL entries with hardware support. 
       MOVE_DOWN corresponds to 'up' seen from VCAP library */
    if (idx->key_size == VTSS_VCAP_KEY_SIZE_FULL) {
        SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(tcam->target),
                VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(1) |
                VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(count - 1));
        return srvl_vcap_row_cmd(vtss_state, tcam, 
                                 idx->row + count - 1, 
                                 up ? VTSS_TCAM_CMD_MOVE_DOWN : VTSS_TCAM_CMD_MOVE_UP,
                                 VTSS_TCAM_SEL_ALL);
    }
    
    /* Move HALF/QUARTER rules manually */
    cur_idx = *idx;
    idx = &cur_idx;
    col_count = vtss_vcap_key_rule_count(idx->key_size);
    key_len = (tcam->entry_width / col_count);
    action_len = (smac_sip4 ? tcam->action_type_1_width : (tcam->action_width / col_count));
    tgw = ((tcam->tg_width * tcam->sw_count) / col_count);
    counter_len = tcam->counter_width;

    VTSS_D("col_count: %u, key_len: %u, action_len: %u, tgw: %u, counter_len: %u",
            col_count, key_len, action_len, tgw, counter_len);

    if (up) {
        /* Move HALF/QUARTER rules up */

        /* Read source row */
        VTSS_RC(srvl_vcap_entry_get(vtss_state, tcam, idx, src));

        while (1) {
            if (idx->col == 0) {
                /* Destination is previous row */
                VTSS_D("previous, row: %u, col: %u", idx->row, idx->col);
                idx->row--;
                VTSS_RC(srvl_vcap_entry_get(vtss_state, tcam, idx, dst));
            } else {
                /* Move rules in current row up */
                col = MIN(col_count - idx->col, count - rule_count);
                VTSS_D("current, row: %u, col: %u, cnt: %u", 
                        idx->row, idx->col, col);
                idx->col += (col - 1);
                VTSS_RC(srvl_vcap_data_get(tcam, idx, src)); 
                *dst = *src;
                idx->col--;
                VTSS_RC(srvl_vcap_data_get(tcam, idx, dst)); 
                srvl_vcap_data_copy(src, dst, col*key_len, col*action_len, col*counter_len);
                VTSS_D("tg_pre: 0x%08x", dst->tg);
                dst->tg |= (dst->tg << tgw);
                dst->tg &= ~src->tg_mask;
                VTSS_D("tg_post: 0x%08x", dst->tg);
                rule_count += col;
                if (rule_count >= count)
                    return srvl_vcap_entry_set(vtss_state, tcam, idx, dst);
            }

            /* Copy first rule on next row to last rule in destination row */
            idx->row++;
            idx->col = 0;
            VTSS_RC(srvl_vcap_entry_data_get(vtss_state, tcam, idx, src));
            idx->row--;
            idx->col = (col_count - 1);
            VTSS_RC(srvl_vcap_data_get(tcam, idx, dst)); 
            srvl_vcap_data_copy(src, dst, key_len, action_len, counter_len);
            VTSS_D("tg_pre: 0x%08x", dst->tg);
            dst->tg = ((dst->tg & ~dst->tg_mask) | dst->tg_value);
            VTSS_D("tg_post: 0x%08x", dst->tg);
            VTSS_RC(srvl_vcap_entry_set(vtss_state, tcam, idx, dst));
            
            /* Step forward one row */
            idx->row++;
            idx->col = 1;
            rule_count++;
            if (rule_count >= count) {
                /* Delete last row */
                src->tg = VCAP_TG_NONE;
                return srvl_vcap_entry_set(vtss_state, tcam, idx, src);
            }
        }
    }

    /* Move HALF/QUARTER rules down */
    
    /* Read destination data at the end of the rule block */
    idx->row += (count / col_count);
    idx->col += (count % col_count);
    if (idx->col >= col_count) {
        idx->row++;
        idx->col -= col_count;
    }
    VTSS_RC(srvl_vcap_entry_get(vtss_state, tcam, idx, dst));
    if (bank == VTSS_TCAM_IS0 || smac_sip4) {
        /* MLBS/SMAC_SIP4 entry, action type 1 */
        dst->type = 1;
    }

    for (rule_count = 0; rule_count < count; rule_count++) {
        if (idx->col != 0) {
            /* Move rules in current row down */
            col = MIN(idx->col, count - rule_count);
            VTSS_D("current, row: %u, col: %u, cnt: %u, count: %u, rule_count: %u",
                   idx->row, idx->col, col, count, rule_count);
            VTSS_RC(srvl_vcap_data_get(tcam, idx, dst)); 
            *src = *dst;
            idx->col--;
            VTSS_RC(srvl_vcap_data_get(tcam, idx, src)); 
            srvl_vcap_data_copy(src, dst, col*key_len, col*action_len, col*counter_len);
            VTSS_D("tg_pre: 0x%08x", dst->tg);
            dst->tg |= (dst->tg >> tgw);
            VTSS_D("tg_post: 0x%08x", dst->tg);
            rule_count += col;
            if (rule_count >= count)
                return srvl_vcap_entry_set(vtss_state, tcam, idx, dst);
        }

        /* Copy last rule from previous row to first rule in destination row */
        VTSS_D("previous, row: %u, col: %u", idx->row, idx->col);
        idx->col = 0;
        VTSS_RC(srvl_vcap_data_get(tcam, idx, dst));
        idx->row--;
        idx->col = (col_count - 1);
        VTSS_RC(srvl_vcap_entry_data_get(vtss_state, tcam, idx, src));
        srvl_vcap_data_copy(src, dst, key_len, action_len, counter_len);
        dst->tg = ((dst->tg & ~dst->tg_mask) | dst->tg_value);
        idx->row++;
        VTSS_RC(srvl_vcap_entry_set(vtss_state, tcam, idx, dst));
        
        /* Swap source and destination pointers and step back one row */
        tmp = dst;
        dst = src;
        src = tmp;
        idx->row--;
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_port_get(vtss_state_t *vtss_state,
                                  int bank, u32 port, u32 *counter, BOOL clear) 
{
    const tcam_props_t *tcam = &tcam_info[bank];
    u32                tgt = tcam->target;

    /* Read counter at index */
    VTSS_RC(srvl_vcap_port_cmd(vtss_state, tcam, port, VTSS_TCAM_CMD_READ, VTSS_TCAM_SEL_COUNTER));
    SRVL_RD(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tgt, 0), counter);

    if (clear) {
        /* Clear counter at index */
        SRVL_WR(VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tgt, 0), 0);
        VTSS_RC(srvl_vcap_port_cmd(vtss_state,
                                   tcam, port, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_COUNTER));
    }
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  VCAP debug print utilities
 * ================================================================= */

#define SRVL_DEBUG_VCAP(pr, name, tgt) vtss_srvl_debug_reg(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CONST_##name(tgt), #name)

static vtss_rc srvl_debug_tcam(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const tcam_props_t *tcam, BOOL entry)
{
    u32 i, tgt = tcam->target;

    vtss_srvl_debug_reg_header(pr, "VCAP");

    /* Entry/mask */
    if (entry) {
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_TG_DAT(tgt), "TG_DAT");
        for (i = 0; i < tcam->entry_words; i++) {
            vtss_srvl_debug_reg_inst(vtss_state, pr,
                                VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(tgt, i),
                                i, "ENTRY_DAT");
            vtss_srvl_debug_reg_inst(vtss_state, pr,
                                VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(tgt, i),
                                i, "MASK_DAT");
        }
        pr("\n");
    }

    /* Action/counter */
    for (i = 0; i < tcam->action_words; i++)
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(tgt, i),
                            i, "ACTION_DAT");
    for (i = 0; i < tcam->counter_words; i++)
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(tgt, i),
                            i, "CNT_DAT");
    pr("\n");
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_vcap(vtss_state_t *vtss_state,
                               int bank,
                               const char *name,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t *const debug_info,
                               vtss_rc (* dbg)(srvl_debug_info_t *dbg_info))
{
    /*lint --e{454, 455, 456} */ // Due to VTSS_EXIT_ENTER
    const tcam_props_t *tcam = &tcam_info[bank];
    srvl_debug_info_t  info;
    srvl_tcam_data_t   *data = &info.data;
    int                i, j, k, sel, rule_index = 0;
    u32                tgt = tcam->target, action_width;
    const char         *txt;
    
    info.pr = pr;
    vtss_debug_print_header(pr, name);
    
    pr("tg_width           : %u\n", tcam->tg_width);
    pr("sw_count           : %u\n", tcam->sw_count);
    pr("entry_count        : %u\n", tcam->entry_count);
    pr("entry_words        : %u\n", tcam->entry_words);
    pr("entry_width        : %u\n", tcam->entry_width);
    pr("action_count       : %u = %u + %u\n", tcam->action_count, tcam->entry_count, 
       tcam->action_count - tcam->entry_count);
    pr("action_words       : %u\n", tcam->action_words);
    pr("action_width       : %u\n", tcam->action_width);
    pr("action_type_width  : %u\n", tcam->action_type_width);
    pr("action_type_0_width: %u\n", tcam->action_type_0_width);
    pr("action_type_1_width: %u\n", tcam->action_type_1_width);
    pr("action_type_0_count: %u\n", tcam->action_type_0_count);
    pr("action_type_1_count: %u\n", tcam->action_type_1_count);
    pr("counter_words      : %u\n", tcam->counter_words);
    pr("counter_width      : %u\n", tcam->counter_width);
    pr("\n");
    
    vtss_srvl_debug_reg_header(pr, "VCAP_CONST");
    SRVL_DEBUG_VCAP(pr, ENTRY_WIDTH, tgt);
    SRVL_DEBUG_VCAP(pr, ENTRY_CNT, tgt);
    SRVL_DEBUG_VCAP(pr, ENTRY_SWCNT, tgt);
    SRVL_DEBUG_VCAP(pr, ENTRY_TG_WIDTH, tgt);
    SRVL_DEBUG_VCAP(pr, ACTION_DEF_CNT, tgt);
    SRVL_DEBUG_VCAP(pr, ACTION_WIDTH, tgt);
    SRVL_DEBUG_VCAP(pr, CNT_WIDTH, tgt);
    pr("\n");
    
    for (i = (tcam->action_count - 1); i >= 0; i--) {
        /* Leave critical region briefly */
        VTSS_EXIT_ENTER();

        /* Read action and counter */
        sel = (VTSS_TCAM_SEL_ACTION | VTSS_TCAM_SEL_COUNTER);
        if (srvl_vcap_cmd(vtss_state, tcam, i, VTSS_TCAM_CMD_READ, sel) != VTSS_RC_OK ||
            srvl_vcap_cache2action(vtss_state, tcam, data) != VTSS_RC_OK)
            continue;
        
        /* Decode action type */
        data->action_offset = tcam->action_type_width;
        data->type = (data->action_offset ? 
                      VTSS_EXTRACT_BITFIELD(data->action[0], 0, data->action_offset) : 0);
        
        if (i >= tcam->entry_count) {
            /* Raw TCAM action/counter dump */
            if (debug_info->full)
                VTSS_RC(srvl_debug_tcam(vtss_state, pr, tcam, 0));

            /* Print default action */
            info.is_action = 1;
            data->cnt = vtss_bs_get(data->counter, 0, tcam->counter_width);
            pr("%d (port %d): ", i, i - tcam->entry_count);
            VTSS_RC(dbg(&info));
            pr("\n-------------------------------------------\n");
            continue;
        }
        
        /* Read entry */
        if (srvl_vcap_cmd(vtss_state, tcam, i, VTSS_TCAM_CMD_READ,
                          VTSS_TCAM_SEL_ENTRY) != VTSS_RC_OK ||
            srvl_vcap_cache2entry(vtss_state, tcam, data) != VTSS_RC_OK ||
            data->tg == VCAP_TG_NONE)
            continue;

        /* Raw TCAM entry/mask dump */
        if (debug_info->full)
            VTSS_RC(srvl_debug_tcam(vtss_state, pr, tcam, 1));

        for (j = (tcam->sw_count - 1); j >= 0; j--) {
            data->tg_sw = VTSS_EXTRACT_BITFIELD(data->tg, j*tcam->tg_width, tcam->tg_width);
            k = j;
            switch (data->tg_sw) {
            case VCAP_TG_FULL:
                txt = (j ? NULL : "FULL");
                break;
            case VCAP_TG_HALF:
                txt = (j == 0 || j == (tcam->sw_count/2) ? "HALF" : NULL);
                if (j)
                    k = ((data->type ? tcam->action_type_1_count : tcam->action_type_0_count)/2);
                break;
            case VCAP_TG_QUARTER:
                txt = "QUARTER";
                break;
            default:
                txt = NULL;
                break;
            }
            if (txt == NULL)
                continue;

            /* Print entry */
            info.is_action = 0;
            data->key_offset = (j*tcam->entry_width/tcam->sw_count);
            pr("%s ", txt);
            VTSS_RC(dbg(&info));
            pr("\n");
            
            /* Print action */
            info.is_action = 1;
            data->cnt = vtss_bs_get(data->counter, j*tcam->counter_width, tcam->counter_width);
            action_width = (data->type ? tcam->action_type_1_width : tcam->action_type_0_width);
            data->action_offset = (tcam->action_type_width + k*action_width);
            pr("%d-%d (rule %d): ", i, j, rule_index);
            VTSS_RC(dbg(&info));
            pr("\n-------------------------------------------\n");
            rule_index++;

            if (debug_info->clear) {
                /* Clear counter at row */
                vtss_bs_set(data->counter, j*tcam->counter_width, tcam->counter_width, 0);
                VTSS_RC(srvl_vcap_action2cache(vtss_state, tcam, data));
            }
        }

        if (debug_info->clear) {
            if (srvl_vcap_cmd(vtss_state, tcam, i, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_COUNTER) != VTSS_RC_OK)
                continue;
        }
    }
    pr("\n");
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_IS0)
/* ================================================================= *
 *  IS0 functions
 * ================================================================= */

static vtss_rc srvl_is0_entry_get(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, u32 *counter, BOOL clear)
{
    return srvl_vcap_counter_get(vtss_state, VTSS_TCAM_IS0, idx, counter, clear);
}

static vtss_rc srvl_is0_entry_add(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    const tcam_props_t     *tcam   = &tcam_info[VTSS_TCAM_IS0];
    srvl_tcam_data_t       tcam_data;
    srvl_tcam_data_t       *data   = &tcam_data;
    vtss_is0_data_t        *is0    = &vcap_data->u.is0;
    vtss_is0_entry_t       *entry  = is0->entry;
    vtss_is0_key_t         *key    = &entry->key;
    vtss_is0_action_t      *action = &entry->action;
    vtss_vcap_key_size_t   key_size;

    /* Check key size and type */
    switch (entry->type) {
    case VTSS_IS0_TYPE_MLL:
        data->type = 0;
        key_size = VTSS_VCAP_KEY_SIZE_FULL;
        break;
    case VTSS_IS0_TYPE_MLBS:
        data->type = 1;
        key_size = VTSS_VCAP_KEY_SIZE_HALF;
        break;
    default:
        VTSS_EG(VTSS_TRACE_GROUP_MPLS, "illegal key type 0x%x", entry->type);
        return VTSS_RC_ERROR;
    }

    if (idx->key_size != key_size) {
        VTSS_EG(VTSS_TRACE_GROUP_MPLS, "illegal key_size: %s, expected: %s",
                vtss_vcap_key_size2txt(idx->key_size), vtss_vcap_key_size2txt(key_size));
        return VTSS_RC_ERROR;
    }

    /* Get TCAM data */
    data->cnt = counter;
    VTSS_RC(srvl_vcap_entry_add(vtss_state, tcam, idx, data));


    switch (entry->type) {
    case VTSS_IS0_TYPE_MLL:
        {
            vtss_vcap_u48_t mac;
            u32             mask;

            // Key

#define MASK(expr, len) ((expr) ? 0 : VTSS_BITMASK(len))
            srvl_vcap_key_set(data, IS0_FKO_MLL_IGR_PORT, IS0_FKL_MLL_IGR_PORT, VTSS_CHIP_PORT(key->mll.ingress_port), MASK(key->mll.ingress_port_dontcare, IS0_FKL_MLL_IGR_PORT));
            srvl_vcap_key_set(data, IS0_FKO_MLL_TTYPE, IS0_FKL_MLL_TTYPE,       key->mll.tag_type,     MASK(key->mll.tag_type_dontcare,  IS0_FKL_MLL_TTYPE));
            srvl_vcap_key_set(data, IS0_FKO_MLL_BVID, IS0_FKL_MLL_BVID,         key->mll.b_vid,        MASK(key->mll.b_vid_dontcare || key->mll.tag_type == VTSS_IS0_TAGTYPE_UNTAGGED, IS0_FKL_MLL_BVID));
            srvl_vcap_key_set(data, IS0_FKO_MLL_E_TYPE, IS0_FKL_MLL_E_TYPE,     key->mll.ether_type,   MASK(key->mll.ether_type_dontcare, IS0_FKL_MLL_E_TYPE));
            VTSS_MEMCPY(mac.value, &key->mll.dmac, 6);  VTSS_MEMSET(mac.mask, key->mll.dmac_dontcare ? 0 : 0xff, sizeof(mac.mask));  srvl_vcap_key_u48_set(data, IS0_FKO_MLL_M_DMAC, &mac);
            VTSS_MEMCPY(mac.value, &key->mll.smac, 6);  VTSS_MEMSET(mac.mask, key->mll.smac_dontcare ? 0 : 0xff, sizeof(mac.mask));  srvl_vcap_key_u48_set(data, IS0_FKO_MLL_M_SMAC, &mac);
#undef MASK

            // Action
            mask = vtss_srvl_port_mask(vtss_state, action->mll.b_portlist.physical) | (action->mll.b_portlist.cpu ? (1 << VTSS_CHIP_PORT_CPU) : 0);

            srvl_vcap_action_set    (data, IS0_AO_MLL_LL_IDX,          IS0_AL_MLL_LL_IDX,          action->mll.linklayer_index);
            srvl_vcap_action_bit_set(data, IS0_AO_MLL_MPLS_FWD,                                    action->mll.mpls_forwarding);
            srvl_vcap_action_set    (data, IS0_AO_MLL_B_PM,            IS0_AL_MLL_B_PM,            mask);
            srvl_vcap_action_set    (data, IS0_AO_MLL_CPU_Q,           IS0_AL_MLL_CPU_Q,           action->mll.cpu_queue);
            srvl_vcap_action_set    (data, IS0_AO_MLL_ISDX,            IS0_AL_MLL_ISDX,            action->mll.isdx);
            srvl_vcap_action_set    (data, IS0_AO_MLL_VPROFILE_IDX,    IS0_AL_MLL_VPROFILE_IDX,    action->mll.vprofile_index);
            srvl_vcap_action_bit_set(data, IS0_AO_MLL_SCONFIG_ENA,                                 action->mll.use_service_config);
            srvl_vcap_action_set    (data, IS0_AO_MLL_CL_VID,          IS0_AL_MLL_CL_VID,          action->mll.classified_vid);
            srvl_vcap_action_set    (data, IS0_AO_MLL_QOS_DEFAULT_VAL, IS0_AL_MLL_QOS_DEFAULT_VAL, action->mll.qos);
            srvl_vcap_action_set    (data, IS0_AO_MLL_DP_DEFAULT_VAL,  IS0_AL_MLL_DP_DEFAULT_VAL,  action->mll.dp);
            srvl_vcap_action_set    (data, IS0_AO_MLL_OAM_ISDX,        IS0_AL_MLL_OAM_ISDX,        action->mll.oam_isdx);
            srvl_vcap_action_bit_set(data, IS0_AO_MLL_ISDX_ADD_REPL,                               action->mll.oam_isdx_add_replace);
        }
        break;
    case VTSS_IS0_TYPE_MLBS:
        {
            u32 mask;

            // Key
            srvl_vcap_key_set(data, IS0_HKO_MLBS_LL_IDX,    IS0_HKL_MLBS_LL_IDX,    key->mlbs.linklayer_index,      VTSS_BITMASK(IS0_HKL_MLBS_LL_IDX));
            srvl_vcap_key_set(data, IS0_HKO_MLBS_LBL_0_VAL, IS0_HKL_MLBS_LBL_0_VAL, key->mlbs.label_stack[0].value, key->mlbs.label_stack[0].value_mask);
            srvl_vcap_key_set(data, IS0_HKO_MLBS_LBL_1_VAL, IS0_HKL_MLBS_LBL_1_VAL, key->mlbs.label_stack[1].value, key->mlbs.label_stack[1].value_mask);
            srvl_vcap_key_set(data, IS0_HKO_MLBS_LBL_2_VAL, IS0_HKL_MLBS_LBL_2_VAL, key->mlbs.label_stack[2].value, key->mlbs.label_stack[2].value_mask);
            srvl_vcap_key_set(data, IS0_HKO_MLBS_LBL_0_TC,  IS0_HKL_MLBS_LBL_0_TC,  key->mlbs.label_stack[0].tc,    key->mlbs.label_stack[0].tc_mask);
            srvl_vcap_key_set(data, IS0_HKO_MLBS_LBL_1_TC,  IS0_HKL_MLBS_LBL_1_TC,  key->mlbs.label_stack[1].tc,    key->mlbs.label_stack[1].tc_mask);
            srvl_vcap_key_set(data, IS0_HKO_MLBS_LBL_2_TC,  IS0_HKL_MLBS_LBL_2_TC,  key->mlbs.label_stack[2].tc,    key->mlbs.label_stack[2].tc_mask);

            // Action
            mask = vtss_srvl_port_mask(vtss_state, action->mlbs.b_portlist.physical) | (action->mlbs.b_portlist.cpu ? (1 << VTSS_CHIP_PORT_CPU) : 0);

            srvl_vcap_action_set    (data, IS0_AO_MLBS_ISDX,         IS0_AL_MLBS_ISDX,         action->mlbs.isdx);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_B_PM,         IS0_AL_MLBS_B_PM,         mask);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_CPU_Q,        IS0_AL_MLBS_CPU_Q,        action->mlbs.cpu_queue);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_OAM_ENA,      IS0_AL_MLBS_OAM_ENA,      action->mlbs.oam);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_BURIED_MIP,                             action->mlbs.oam_buried_mip);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_RSVD_LBL_VAL, IS0_AL_MLBS_RSVD_LBL_VAL, action->mlbs.oam_reserved_label_value);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_RSVD_LBL_BOS,                           action->mlbs.oam_reserved_label_bottom_of_stack);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_CW_ENA,                                 action->mlbs.cw_enable);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_TC_LABEL,     IS0_AL_MLBS_TC_LABEL,     action->mlbs.tc_label_index);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_TTL_LABEL,    IS0_AL_MLBS_TTL_LABEL,    action->mlbs.ttl_label_index);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_SWAP_LABEL,   IS0_AL_MLBS_SWAP_LABEL,   action->mlbs.swap_label_index);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_TERMINATE_PW,                           action->mlbs.terminate_pw);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_POP_CNT,      IS0_AL_MLBS_POP_CNT,      action->mlbs.pop_count);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_E_LSP,                                  action->mlbs.e_lsp);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_TC_MAP,       IS0_AL_MLBS_TC_MAP,       action->mlbs.tc_maptable_index);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_L_LSP_COS,    IS0_AL_MLBS_L_LSP_COS,    action->mlbs.l_lsp_qos_class);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_INC_ISDX,                               action->mlbs.add_tc_to_isdx);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_OAM_ISDX,     IS0_AL_MLBS_OAM_ISDX,     action->mlbs.oam_isdx);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_ISDX_ADD_REPL,                          action->mlbs.oam_isdx_add_replace);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_SWAP_IS_BOS,                            action->mlbs.swap_is_bottom_of_stack);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_VPROFILE_IDX, IS0_AL_MLBS_VPROFILE_IDX, action->mlbs.vprofile_index);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_SCONFIG_ENA,                            action->mlbs.use_service_config);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_CL_VID,       IS0_AL_MLBS_CL_VID,       action->mlbs.classified_vid);
            srvl_vcap_action_set    (data, IS0_AO_MLBS_VLAN_PCP,     IS0_AL_MLBS_VLAN_PCP,     action->mlbs.pcp);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_VLAN_STAGD,                             action->mlbs.s_tag);
            srvl_vcap_action_bit_set(data, IS0_AO_MLBS_VLAN_DEI,                               action->mlbs.dei);
        }
        break;
    }

    /* Set TCAM data */
    return srvl_vcap_entry_set(vtss_state, tcam, idx, data);
}

static vtss_rc srvl_is0_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    return srvl_vcap_entry_del(vtss_state, VTSS_TCAM_IS0, idx);
}

static vtss_rc srvl_is0_entry_move(vtss_state_t *vtss_state,
                                   vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    return srvl_vcap_entry_move(vtss_state, VTSS_TCAM_IS0, idx, count, up);
}

static vtss_rc srvl_debug_is0(srvl_debug_info_t *info)
{
    vtss_debug_printf_t pr    = info->pr;
    srvl_tcam_data_t    *data = &info->data;

    if (data->tg_sw == VCAP_TG_FULL) {
        if (!info->is_action) {
            /* Print key */
            srvl_debug_bits(info, "MLL Key: Port",      IS0_FKO_MLL_IGR_PORT,       IS0_FKL_MLL_IGR_PORT);
            srvl_debug_bits(info, "TagType",            IS0_FKO_MLL_TTYPE,          IS0_FKL_MLL_TTYPE);
            srvl_debug_bits(info, "B_VID",              IS0_FKO_MLL_BVID,           IS0_FKL_MLL_BVID);
            srvl_debug_bits(info, "EType",              IS0_FKO_MLL_E_TYPE,         IS0_FKL_MLL_E_TYPE);
            pr("\n");
            srvl_debug_u48 (info, "DMAC",               IS0_FKO_MLL_M_DMAC);
            srvl_debug_u48 (info, "SMAC",               IS0_FKO_MLL_M_SMAC);
        }
        else {
            /* Print action */
            srvl_debug_bits(info, "MLL Action: LL_idx", IS0_AO_MLL_LL_IDX,          IS0_AL_MLL_LL_IDX);
            srvl_debug_bit (info, "MPLS_fwd?",          IS0_AO_MLL_MPLS_FWD);
            srvl_debug_bits(info, "B_portmask",         IS0_AO_MLL_B_PM,            IS0_AL_MLL_B_PM);
            srvl_debug_bits(info, "CPU_q",              IS0_AO_MLL_CPU_Q,           IS0_AL_MLL_CPU_Q);
            srvl_debug_bits(info, "ISDX",               IS0_AO_MLL_ISDX,            IS0_AL_MLL_ISDX);
            pr("\n");
            srvl_debug_bits(info, "VProfile_idx",       IS0_AO_MLL_VPROFILE_IDX,    IS0_AL_MLL_VPROFILE_IDX);
            srvl_debug_bit (info, "Service_cfg?",       IS0_AO_MLL_SCONFIG_ENA);
            srvl_debug_bits(info, "Clas._VID",          IS0_AO_MLL_CL_VID,          IS0_AL_MLL_CL_VID);
            srvl_debug_bits(info, "Def._QoS",           IS0_AO_MLL_QOS_DEFAULT_VAL, IS0_AL_MLL_QOS_DEFAULT_VAL);
            pr("\n");
            srvl_debug_bits(info, "Def._DP",            IS0_AO_MLL_DP_DEFAULT_VAL,  IS0_AL_MLL_DP_DEFAULT_VAL);
            srvl_debug_bits(info, "OAM_ISDX",           IS0_AO_MLL_OAM_ISDX,        IS0_AL_MLL_OAM_ISDX);
            srvl_debug_bit (info, "OAM_ISDX_add/rep?",  IS0_AO_MLL_ISDX_ADD_REPL);
            pr("hit:%u ", info->data.cnt);
        }
    }
    else if (data->tg_sw == VCAP_TG_HALF) {
        if (!info->is_action) {
            /* Print key */
            srvl_debug_bits(info, "MLBS Key: LL_idx",  IS0_HKO_MLBS_LL_IDX,      IS0_HKL_MLBS_LL_IDX);
            srvl_debug_bits(info, "L0",                IS0_HKO_MLBS_LBL_0_VAL,   IS0_HKL_MLBS_LBL_0_VAL);
            srvl_debug_bits(info, "TC0",               IS0_HKO_MLBS_LBL_0_TC,    IS0_HKL_MLBS_LBL_0_TC);
            pr("\n");
            srvl_debug_bits(info, "L1",                IS0_HKO_MLBS_LBL_1_VAL,   IS0_HKL_MLBS_LBL_1_VAL);
            srvl_debug_bits(info, "TC1",               IS0_HKO_MLBS_LBL_1_TC,    IS0_HKL_MLBS_LBL_1_TC);
            srvl_debug_bits(info, "L2",                IS0_HKO_MLBS_LBL_2_VAL,   IS0_HKL_MLBS_LBL_2_VAL);
            srvl_debug_bits(info, "TC2",               IS0_HKO_MLBS_LBL_2_TC,    IS0_HKL_MLBS_LBL_2_TC);
            pr("\n");
        }
        else {
            /* Print action */
            srvl_debug_bits(info, "MLBS Action: ISDX", IS0_AO_MLBS_ISDX,         IS0_AL_MLBS_ISDX);
            srvl_debug_bits(info, "B_portmask",        IS0_AO_MLBS_B_PM,         IS0_AL_MLBS_B_PM);
            srvl_debug_bits(info, "CPU_q",             IS0_AO_MLBS_CPU_Q,        IS0_AL_MLBS_CPU_Q);
            srvl_debug_bits(info, "OAM?",              IS0_AO_MLBS_OAM_ENA,      IS0_AL_MLBS_OAM_ENA);
            srvl_debug_bit (info, "Buried_MIP?",       IS0_AO_MLBS_BURIED_MIP);
            pr("\n");
            srvl_debug_bits(info, "Res_lbl",           IS0_AO_MLBS_RSVD_LBL_VAL, IS0_AL_MLBS_RSVD_LBL_VAL);
            srvl_debug_bit (info, "Res_lbl_BOS?",      IS0_AO_MLBS_RSVD_LBL_BOS);
            srvl_debug_bit (info, "CW?",               IS0_AO_MLBS_CW_ENA);
            pr("\n");
            srvl_debug_bits(info, "TC_lbl_idx",        IS0_AO_MLBS_TC_LABEL,     IS0_AL_MLBS_TC_LABEL);
            srvl_debug_bits(info, "TTL_lbl_idx",       IS0_AO_MLBS_TTL_LABEL,    IS0_AL_MLBS_TTL_LABEL);
            srvl_debug_bits(info, "Swap_lbl_idx",      IS0_AO_MLBS_SWAP_LABEL,   IS0_AL_MLBS_SWAP_LABEL);
            srvl_debug_bit (info, "Swap_is_BOS?",      IS0_AO_MLBS_SWAP_IS_BOS);
            pr("\n");
            srvl_debug_bit (info, "Term_PW?",          IS0_AO_MLBS_TERMINATE_PW);
            srvl_debug_bits(info, "Pop_cnt",           IS0_AO_MLBS_POP_CNT,      IS0_AL_MLBS_POP_CNT);
            srvl_debug_bit (info, "E_LSP?",            IS0_AO_MLBS_E_LSP);
            srvl_debug_bits(info, "TC_map_idx",        IS0_AO_MLBS_TC_MAP,       IS0_AL_MLBS_TC_MAP);
            srvl_debug_bits(info, "L_LSP_CoS",         IS0_AO_MLBS_L_LSP_COS,    IS0_AL_MLBS_L_LSP_COS);
            srvl_debug_bit (info, "Inc_ISDX_w_TC?",    IS0_AO_MLBS_INC_ISDX);
            pr("\n");
            srvl_debug_bits(info, "OAM_ISDX",          IS0_AO_MLBS_OAM_ISDX,     IS0_AL_MLBS_OAM_ISDX);
            srvl_debug_bit (info, "OAM_ISDX_add/rep?", IS0_AO_MLBS_ISDX_ADD_REPL);
            srvl_debug_bits(info, "VProfile_idx",      IS0_AO_MLBS_VPROFILE_IDX, IS0_AL_MLBS_VPROFILE_IDX);
            srvl_debug_bit (info, "Service_cfg?",      IS0_AO_MLBS_SCONFIG_ENA);
            pr("\n");
            srvl_debug_bits(info, "Clas._VID",         IS0_AO_MLBS_CL_VID,       IS0_AL_MLBS_CL_VID);
            srvl_debug_bit (info, "VLAN_S_tag?",       IS0_AO_MLBS_VLAN_STAGD);
            srvl_debug_bits(info, "VLAN_PCP",          IS0_AO_MLBS_VLAN_PCP,     IS0_AL_MLBS_VLAN_PCP);
            srvl_debug_bit (info, "VLAN_DEI?",         IS0_AO_MLBS_VLAN_DEI);
            pr("hit:%u ", info->data.cnt);
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_debug_is0_all(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    return srvl_debug_vcap(vtss_state, VTSS_TCAM_IS0, "IS0", pr, info, srvl_debug_is0);
}
#endif /* VTSS_FEATURE_IS0 */

/* ================================================================= *
 *  IS1 functions
 * ================================================================= */

static vtss_rc srvl_is1_entry_get(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, u32 *counter, BOOL clear) 
{
    VTSS_I("enter");
    
    return srvl_vcap_counter_get(vtss_state, VTSS_TCAM_IS1, idx, counter, clear);
}

/* IS1 key information common for some key types */
typedef struct {
    vtss_vcap_vid_t  vid;
    vtss_vcap_u16_t  etype;
    vtss_vcap_bit_t  etype_len;
    vtss_vcap_bit_t  ip_snap;
    vtss_vcap_bit_t  ip4;
    vtss_vcap_bit_t  ip_mc;
    vtss_vcap_bit_t  l3_fragment;
    vtss_vcap_bit_t  l3_options;
    vtss_vcap_u8_t   l3_dscp;
    vtss_vcap_ip_t   l3_ip4_sip;
    vtss_vcap_ip_t   l3_ip4_dip;
    vtss_vcap_bit_t  tcp_udp;
    vtss_vcap_bit_t  tcp;
    vtss_vcap_u16_t  l4_sport;
    vtss_vcap_u8_t   l4_range;
    vtss_vcap_u128_t l3_ip6_sip;
    vtss_vcap_u128_t l3_ip6_dip;
} srvl_is1_key_info_t;

static void srvl_is1_base_key_set(vtss_state_t *vtss_state,
                                  srvl_tcam_data_t *data, vtss_is1_data_t *is1, 
                                  srvl_is1_key_info_t *info, u32 offset)
{
    u32            mask, old_offset = data->key_offset;
    vtss_is1_key_t *key = &is1->entry->key;
    vtss_is1_tag_t *tag = &key->tag;
    
    data->key_offset += (offset - IS1_QKO_LOOKUP); /* Adjust offset */
    srvl_vcap_key_set(data, IS1_QKO_LOOKUP, IS1_QKL_LOOKUP, 
                      is1->lookup, VTSS_BITMASK(IS1_QKL_LOOKUP));
    mask = vtss_srvl_port_mask(vtss_state, key->port_list);
    srvl_vcap_key_set(data, IS1_QKO_IGR_PORT_MASK, IS1_QKL_IGR_PORT_MASK, 0, ~mask);
    srvl_vcap_key_set(data, IS1_QKO_ISDX, IS1_QKL_ISDX, 
                      (key->isdx.value[0] << 8) + key->isdx.value[1],
                      (key->isdx.mask[0] << 8) + key->isdx.mask[1]);
    srvl_vcap_key_bit_set(data, IS1_QKO_L2_MC, key->mac.dmac_mc);
    srvl_vcap_key_bit_set(data, IS1_QKO_L2_BC, key->mac.dmac_bc);
    srvl_vcap_key_bit_set(data, IS1_QKO_IP_MC, info->ip_mc);
    srvl_vcap_key_bit_set(data, IS1_QKO_VLAN_TAGGED, tag->tagged);
    srvl_vcap_key_bit_set(data, IS1_QKO_VLAN_DBL_TAGGED, key->inner_tag.tagged);
    srvl_vcap_key_bit_set(data, IS1_QKO_TPID, tag->s_tag);
    srvl_vcap_key_set(data, IS1_QKO_VID, IS1_QKL_VID, info->vid.value, info->vid.mask);
    srvl_vcap_key_bit_set(data, IS1_QKO_DEI, tag->dei);
    srvl_vcap_key_u3_set(data, IS1_QKO_PCP, &tag->pcp);
    data->key_offset = old_offset; /* Restore offset */
}

static void srvl_is1_inner_key_set(srvl_tcam_data_t *data, vtss_is1_data_t *is1, u32 offset)
{
    u32            old_offset = data->key_offset;
    vtss_is1_tag_t *tag = &is1->entry->key.inner_tag;
    BOOL           range = (tag->vid.type == VTSS_VCAP_VR_TYPE_VALUE_MASK ? 0 : 1);

    data->key_offset += (offset - IS1_QKO_INNER_TPID); /* Adjust offset */
    srvl_vcap_key_bit_set(data, IS1_QKO_INNER_TPID, tag->s_tag);
    srvl_vcap_key_set(data, IS1_QKO_INNER_VID, IS1_QKL_INNER_VID, 
                      range ? 0 : tag->vid.vr.v.value, range ? 0 : tag->vid.vr.v.mask);
    srvl_vcap_key_bit_set(data, IS1_QKO_INNER_DEI, tag->dei);
    srvl_vcap_key_u3_set(data, IS1_QKO_INNER_PCP, &tag->pcp);
    data->key_offset = old_offset; /* Restore offset */
}

static u32 srvl_u8_to_u32(u8 *p)
{
    return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static void srvl_is1_misc_key_set(srvl_tcam_data_t *data, srvl_is1_key_info_t *info, u32 offset) 
{
    u32 old_offset = data->key_offset;
    
    data->key_offset += (offset - IS1_QKO_ETYPE_LEN); /* Adjust offset */
    srvl_vcap_key_bit_set(data, IS1_QKO_ETYPE_LEN, info->etype_len);
    srvl_vcap_key_u16_set(data, IS1_QKO_ETYPE, &info->etype);
    srvl_vcap_key_bit_set(data, IS1_QKO_IP_SNAP, info->ip_snap);
    srvl_vcap_key_bit_set(data, IS1_QKO_IP4, info->ip4);
    srvl_vcap_key_bit_set(data, IS1_QKO_L3_FRAGMENT, info->l3_fragment);
    srvl_vcap_key_bit_set(data, IS1_QKO_L3_FRAG_OFS_GT0, VTSS_VCAP_BIT_ANY);
    srvl_vcap_key_bit_set(data, IS1_QKO_L3_OPTIONS, info->l3_options);
    srvl_vcap_key_u6_set(data, IS1_QKO_L3_DSCP, &info->l3_dscp);
    data->key_offset = old_offset; /* Restore offset */
}

static void srvl_is1_l4_key_set(srvl_tcam_data_t *data, srvl_is1_key_info_t *info, u32 offset) 
{
    u32 old_offset = data->key_offset;
    
    data->key_offset += (offset - IS1_HKO_NORMAL_TCP_UDP); /* Adjust offset */
    srvl_vcap_key_bit_set(data, IS1_HKO_NORMAL_TCP_UDP, info->tcp_udp);
    srvl_vcap_key_bit_set(data, IS1_HKO_NORMAL_TCP, info->tcp);
    srvl_vcap_key_u16_set(data, IS1_HKO_NORMAL_L4_SPORT, &info->l4_sport);
    srvl_vcap_key_u8_set(data, IS1_HKO_NORMAL_L4_RNG, &info->l4_range);
    data->key_offset = old_offset; /* Restore offset */
}

static void srvl_is1_range_update(vtss_vcap_vr_type_t type, u32 range, srvl_is1_key_info_t *info)
{
    u32 mask;

    if (type != VTSS_VCAP_VR_TYPE_VALUE_MASK && range != VTSS_VCAP_RANGE_CHK_NONE) {
        /* Range checker has been allocated */
        mask = (1 << range);
        info->l4_range.mask |= mask;
        if (type == VTSS_VCAP_VR_TYPE_RANGE_INCLUSIVE)
            info->l4_range.value |= mask;
    }
}

static void srvl_is1_l4port_update(vtss_vcap_vr_t *vr, u32 range, 
                                   vtss_vcap_u16_t *val, srvl_is1_key_info_t *info, BOOL *l4_used)
{
    u32 mask, value;
    
    if (vr->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
        /* Value/mask */
        mask = vr->vr.v.mask;
        value = vr->vr.v.value;
        if (mask != 0) {
            *l4_used = 1;
            val->value[0] = ((value >> 8) & 0xff);
            val->value[1] = (value & 0xff);
            val->mask[0] = ((mask >> 8) & 0xff);
            val->mask[1] = (mask & 0xff);
        }
    } else if (range != VTSS_VCAP_RANGE_CHK_NONE) {
        /* Range */
        *l4_used = 1;
        srvl_is1_range_update(vr->type, range, info);
    }
}

BOOL vtss_srvl_is1_oam_adv(vtss_state_t *vtss_state)
{
    BOOL oam_adv;

    /* Ocelot supports advanced OAM classification */
    oam_adv = TRUE;

    return oam_adv;
}

static vtss_rc srvl_is1_entry_add(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    const tcam_props_t     *tcam = &tcam_info[VTSS_TCAM_IS1];
    srvl_tcam_data_t       tcam_data, *data = &tcam_data;
    vtss_is1_data_t        *is1 = &vcap_data->u.is1;
    vtss_is1_key_t         *key = &is1->entry->key;
    vtss_is1_action_t      *action = &is1->entry->action;
    vtss_is1_frame_etype_t *etype = &key->frame.etype;
    vtss_is1_frame_llc_t   *llc = &key->frame.llc;
    vtss_is1_frame_snap_t  *snap = &key->frame.snap;
    vtss_is1_frame_ipv4_t  *ipv4 = &key->frame.ipv4;
    vtss_is1_frame_ipv6_t  *ipv6 = &key->frame.ipv6;
    vtss_vcap_u8_t         *proto = NULL;
    vtss_vcap_vr_t         *dscp, *sport, *dport, *vid;
    vtss_vcap_key_size_t   key_size;
    u32                    oam = 0, i, n, type = IS1_TYPE_NORMAL;
    srvl_is1_key_info_t    info;
    BOOL                   l4_used = 0, ip = 0;

    VTSS_I("enter");
    
    /* Check key size and type */
    switch (key->key_type) {
    case VTSS_VCAP_KEY_TYPE_DOUBLE_TAG:
        key_size = VTSS_VCAP_KEY_SIZE_QUARTER;
        break;
    case VTSS_VCAP_KEY_TYPE_NORMAL:
    case VTSS_VCAP_KEY_TYPE_IP_ADDR:
        key_size = VTSS_VCAP_KEY_SIZE_HALF;
        break;
    case VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR:
        key_size = VTSS_VCAP_KEY_SIZE_FULL;
        break;
    default:
        VTSS_E("illegal key type");
        return VTSS_RC_ERROR;
    }

    if (idx->key_size != key_size) {
        VTSS_E("illegal key_size: %s, expected: %s",
                vtss_vcap_key_size2txt(idx->key_size), vtss_vcap_key_size2txt(key_size));
        return VTSS_RC_ERROR;
    }

    /* Initialize IS1 info */
    VTSS_MEMSET(&info, 0, sizeof(info));

    /* VLAN value/range */
    vid = &key->tag.vid;
    if (vid->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
        info.vid.value = vid->vr.v.value;
        info.vid.mask = vid->vr.v.mask;
    } 
    srvl_is1_range_update(vid->type, is1->vid_range, &info);

    /* Frame type specific processing */
    switch (key->type) {
    case VTSS_IS1_TYPE_ANY:
        break;
    case VTSS_IS1_TYPE_ETYPE:
        info.etype_len = VTSS_VCAP_BIT_1;
        info.ip_snap = VTSS_VCAP_BIT_0;
        info.ip4 = VTSS_VCAP_BIT_0;
        info.etype = etype->etype;
        if (vtss_srvl_is1_oam_adv(vtss_state) &&
            info.etype.value[0] == 0x89 && info.etype.value[1] == 0x02 &&
            info.etype.mask[0] == 0xff && info.etype.mask[1] == 0xff) {
            /* Match OAM frames on using ISDX bit 9 */
            info.etype.value[1] = etype->mel.value;
            info.etype.mask[1] = etype->mel.mask;
            key->isdx.value[0] |= 0x02;
            key->isdx.mask[0] |= 0x02;
        }
        info.l3_ip4_sip.value = srvl_u8_to_u32(etype->data.value);
        info.l3_ip4_sip.mask = srvl_u8_to_u32(etype->data.mask);
        for (i = 0; i < 4; i++) {
            info.l3_ip6_sip.value[i + 8] = etype->data.value[i];
            info.l3_ip6_sip.mask[i + 8] = etype->data.mask[i];
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
        info.l3_ip4_sip.value = srvl_u8_to_u32(&llc->data.value[2]);
        info.l3_ip4_sip.mask = srvl_u8_to_u32(&llc->data.mask[2]);
        for (i = 2; i < 6; i++) {
            info.l3_ip6_sip.value[i + 6] = llc->data.value[i];
            info.l3_ip6_sip.mask[i + 6] = llc->data.mask[i];
        }
        break;
    case VTSS_IS1_TYPE_SNAP:
        info.etype_len = VTSS_VCAP_BIT_0;
        info.ip_snap = VTSS_VCAP_BIT_1;
        info.ip4 = VTSS_VCAP_BIT_0;
        info.etype.value[0] = snap->data.value[0];
        info.etype.mask[0] = snap->data.mask[0];
        info.etype.value[1] = snap->data.value[1];
        info.etype.mask[1] = snap->data.mask[1];
        info.l3_ip4_sip.value = srvl_u8_to_u32(&snap->data.value[2]);
        info.l3_ip4_sip.mask = srvl_u8_to_u32(&snap->data.mask[2]);
        for (i = 2; i < 6; i++) {
            info.l3_ip6_sip.value[i + 6] = snap->data.value[i];
            info.l3_ip6_sip.mask[i + 6] = snap->data.mask[i];
        }
        break;
    case VTSS_IS1_TYPE_IPV4:
    case VTSS_IS1_TYPE_IPV6:
        ip = 1;
        if (key->key_type == VTSS_VCAP_KEY_TYPE_IP_ADDR)
            type = IS1_TYPE_5TUPLE_IP4;
        info.etype_len = VTSS_VCAP_BIT_1;
        info.ip_snap = VTSS_VCAP_BIT_1;
        if (key->type == VTSS_IS1_TYPE_IPV4) {
            info.ip4 = VTSS_VCAP_BIT_1;
            info.ip_mc = ipv4->ip_mc;
            info.l3_fragment = ipv4->fragment;
            info.l3_options = ipv4->options;
            proto = &ipv4->proto;
            dscp = &ipv4->dscp;
            info.l3_ip4_sip = ipv4->sip;
            info.l3_ip4_dip = ipv4->dip;
            for (i = 12; i < 16; i++) {
                n = (15 - i)*8;
                info.l3_ip6_sip.value[i] = ((ipv4->sip.value >> n) & 0xff);
                info.l3_ip6_sip.mask[i] = ((ipv4->sip.mask >> n) & 0xff);
                info.l3_ip6_dip.value[i] = ((ipv4->dip.value >> n) & 0xff);
                info.l3_ip6_dip.mask[i] = ((ipv4->dip.mask >> n) & 0xff);
            }
            sport = &ipv4->sport;
            dport = &ipv4->dport;
        } else {
            info.ip4 = VTSS_VCAP_BIT_0;
            info.ip_mc = ipv6->ip_mc;
            proto = &ipv6->proto;
            dscp = &ipv6->dscp;
            info.l3_ip4_sip.value = srvl_u8_to_u32(&ipv6->sip.value[12]);
            info.l3_ip4_sip.mask = srvl_u8_to_u32(&ipv6->sip.mask[12]);
            info.l3_ip4_dip.value = srvl_u8_to_u32(&ipv6->dip.value[12]);
            info.l3_ip4_dip.mask = srvl_u8_to_u32(&ipv6->dip.mask[12]);
            info.l3_ip6_sip = ipv6->sip;
            info.l3_ip6_dip = ipv6->dip;
            sport = &ipv6->sport;
            dport = &ipv6->dport;
        }
        if (dscp->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
            info.l3_dscp.value = dscp->vr.v.value;
            info.l3_dscp.mask = dscp->vr.v.mask;
        }
        srvl_is1_range_update(dscp->type, is1->dscp_range, &info);
        if (vtss_vcap_udp_tcp_rule(proto)) {
            info.tcp_udp = VTSS_VCAP_BIT_1;
            info.tcp = (proto->value == 6 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);

            /* Destination port/range */
            srvl_is1_l4port_update(dport, is1->dport_range, &info.etype, &info, &l4_used);

            /* Source port/range */
            srvl_is1_l4port_update(sport, is1->sport_range, &info.l4_sport, &info, &l4_used);
            
            if (l4_used) {
                /* L4 used, ignore fragments and options */
                info.l3_fragment = VTSS_VCAP_BIT_0;
                info.l3_options = VTSS_VCAP_BIT_0;
            }
        } else if (proto->mask == 0xff) {
            /* Not UDP/TCP */
            info.tcp_udp = VTSS_VCAP_BIT_0;
            info.etype.value[1] = proto->value;
            info.etype.mask[1] = proto->mask;
        }
        break;
    default:
        VTSS_E("illegal frame type");
        return VTSS_RC_ERROR;
    }

    /* Get TCAM data */
    data->type = 0;
    data->cnt = counter;
    VTSS_RC(srvl_vcap_entry_add(vtss_state, tcam, idx, data));
    
    /* Setup key fields */
    if (idx->key_size == VTSS_VCAP_KEY_SIZE_QUARTER) {
        /* Quarter key */
        srvl_is1_base_key_set(vtss_state, data, is1, &info, IS1_QKO_LOOKUP);
        srvl_is1_inner_key_set(data, is1, IS1_QKO_INNER_TPID);
        srvl_is1_misc_key_set(data, &info, IS1_QKO_ETYPE_LEN);
        srvl_vcap_key_bit_set(data, IS1_QKO_TCP_UDP, info.tcp_udp);
        srvl_vcap_key_bit_set(data, IS1_QKO_TCP, info.tcp);
    } else if (idx->key_size == VTSS_VCAP_KEY_SIZE_HALF) {
        /* Half key */
        srvl_vcap_key_set(data, IS1_HKO_TYPE, IS1_HKL_TYPE, type,
                          key->type == VTSS_IS1_TYPE_ANY ? 0 : VTSS_BITMASK(IS1_HKL_TYPE));
        srvl_is1_base_key_set(vtss_state, data, is1, &info, IS1_HKO_LOOKUP);
        if (type == IS1_TYPE_NORMAL) {
            BOOL dmac_dip = FALSE;
            vtss_port_no_t first_port = vtss_cmn_first_port_no_get(vtss_state, key->port_list);
            if (first_port != VTSS_PORT_NO_NONE) {
                dmac_dip = vtss_state->vcap.dmac_dip_conf[first_port].dmac_dip[is1->lookup];
            }
            srvl_vcap_key_u48_set(data, IS1_HKO_NORMAL_L2_SMAC, dmac_dip ? &key->mac.dmac : &key->mac.smac);
            srvl_vcap_key_ipv4_set(data, IS1_HKO_NORMAL_L3_IP4_SIP, dmac_dip && ip ? &info.l3_ip4_dip : &info.l3_ip4_sip);
            srvl_is1_misc_key_set(data, &info, IS1_HKO_NORMAL_ETYPE_LEN);
            srvl_is1_l4_key_set(data, &info, IS1_HKO_NORMAL_TCP_UDP);
        } else {
            /* IS1_TYPE_5TUPLE_IP4 */
            srvl_is1_inner_key_set(data, is1, IS1_HKO_5TUPLE_IP4_INNER_TPID);
            srvl_vcap_key_bit_set(data, IS1_HKO_5TUPLE_IP4_IP4, info.ip4);
            srvl_vcap_key_bit_set(data, IS1_HKO_5TUPLE_IP4_L3_FRAGMENT, info.l3_fragment);
            srvl_vcap_key_bit_set(data, IS1_HKO_5TUPLE_IP4_L3_FRAG_OFS_GT0, VTSS_VCAP_BIT_ANY);
            srvl_vcap_key_bit_set(data, IS1_HKO_5TUPLE_IP4_L3_OPTIONS, info.l3_options);
            srvl_vcap_key_u6_set(data, IS1_HKO_5TUPLE_IP4_L3_DSCP, &info.l3_dscp);
            srvl_vcap_key_ipv4_set(data, IS1_HKO_5TUPLE_IP4_L3_IP4_DIP, &info.l3_ip4_dip);
            srvl_vcap_key_ipv4_set(data, IS1_HKO_5TUPLE_IP4_L3_IP4_SIP, &info.l3_ip4_sip);
            srvl_vcap_key_u8_set(data, IS1_HKO_5TUPLE_IP4_L3_IP_PROTO, proto);
            srvl_vcap_key_bit_set(data, IS1_HKO_5TUPLE_IP4_TCP_UDP, info.tcp_udp);
            srvl_vcap_key_bit_set(data, IS1_HKO_5TUPLE_IP4_TCP, info.tcp);
            srvl_vcap_key_u8_set(data, IS1_HKO_5TUPLE_IP4_L4_RNG, &info.l4_range);
            srvl_vcap_key_set(data, IS1_HKO_5TUPLE_IP4_IP_PAYLOAD, IS1_HKL_5TUPLE_IP4_IP_PAYLOAD,
                              0, 0);
        }
    } else {
        /* Full key */
        srvl_vcap_key_set(data, IS1_FKO_TYPE, IS1_FKL_TYPE, 
                          IS1_TYPE_7TUPLE, VTSS_BITMASK(IS1_FKL_TYPE));
        srvl_is1_base_key_set(vtss_state, data, is1, &info, IS1_FKO_LOOKUP);
        srvl_is1_inner_key_set(data, is1, IS1_FKO_INNER_TPID);
        srvl_vcap_key_u48_set(data, IS1_FKO_7TUPLE_L2_DMAC, &key->mac.dmac);
        srvl_vcap_key_u48_set(data, IS1_FKO_7TUPLE_L2_SMAC, &key->mac.smac);
        srvl_is1_misc_key_set(data, &info, IS1_FKO_7TUPLE_ETYPE_LEN);
        srvl_vcap_key_bytes_set(data, IS1_FKO_7TUPLE_L3_IP6_DIP_MSB,
                                info.l3_ip6_dip.value, info.l3_ip6_dip.mask, 4);
        srvl_vcap_key_bytes_set(data, IS1_FKO_7TUPLE_L3_IP6_DIP,
                                &info.l3_ip6_dip.value[8], &info.l3_ip6_dip.mask[8], 8);
        srvl_vcap_key_bytes_set(data, IS1_FKO_7TUPLE_L3_IP6_SIP_MSB,
                                info.l3_ip6_sip.value, info.l3_ip6_sip.mask, 4);
        srvl_vcap_key_bytes_set(data, IS1_FKO_7TUPLE_L3_IP6_SIP,
                                &info.l3_ip6_sip.value[8], &info.l3_ip6_sip.mask[8], 8);
        srvl_is1_l4_key_set(data, &info, IS1_FKO_7TUPLE_TCP_UDP);
    }

    /* Setup action fields */
    srvl_vcap_action_bit_set(data, IS1_AO_DSCP_ENA, action->dscp_enable);
    srvl_vcap_action_set(data, IS1_AO_DSCP_VAL, IS1_AL_DSCP_VAL, action->dscp);
    srvl_vcap_action_bit_set(data, IS1_AO_QOS_ENA, action->prio_enable);
    srvl_vcap_action_set(data, IS1_AO_QOS_VAL, IS1_AL_QOS_VAL, action->prio);
    srvl_vcap_action_bit_set(data, IS1_AO_DP_ENA, action->dp_enable);
    srvl_vcap_action_bit_set(data, IS1_AO_DP_VAL, action->dp);
    srvl_vcap_action_set(data, IS1_AO_PAG_OVERRIDE_MASK, IS1_AL_PAG_OVERRIDE_MASK, 
                         (action->oam_enable ? 0xc0  : 0) + (action->pag_enable ? 0x3f : 0));
#if defined(VTSS_FEATURE_VOP)
    oam = (action->oam_detect == VTSS_OAM_DETECT_UNTAGGED ? 1 :
           action->oam_detect == VTSS_OAM_DETECT_SINGLE_TAGGED ? 2 :
           action->oam_detect == VTSS_OAM_DETECT_DOUBLE_TAGGED ? 3 : 0);
#endif /* VTSS_FEATURE_VOP */
    srvl_vcap_action_set(data, IS1_AO_PAG_VAL, IS1_AL_PAG_VAL, (oam << 6) + (action->pag & 0x3f));
    srvl_vcap_action_bit_set(data, IS1_AO_ISDX_REPLACE_ENA, action->isdx_enable);
    srvl_vcap_action_set(data, IS1_AO_ISDX_ADD_VAL, IS1_AL_ISDX_ADD_VAL, action->isdx);
    srvl_vcap_action_bit_set(data, IS1_AO_VID_REPLACE_ENA, 
                             action->vid_enable || action->vid != VTSS_VID_NULL ? 1 : 0);
    srvl_vcap_action_set(data, IS1_AO_VID_ADD_VAL, IS1_AL_VID_ADD_VAL, action->vid);
    srvl_vcap_action_set(data, IS1_AO_FID_SEL, IS1_AL_FID_SEL, action->fid_sel);
    srvl_vcap_action_set(data, IS1_AO_FID_VAL, IS1_AL_FID_VAL, action->fid_val);
    srvl_vcap_action_bit_set(data, IS1_AO_PCP_DEI_ENA, action->pcp_dei_enable);
    srvl_vcap_action_set(data, IS1_AO_PCP_VAL, IS1_AL_PCP_VAL, action->pcp);
    srvl_vcap_action_bit_set(data, IS1_AO_DEI_VAL, action->dei);
    srvl_vcap_action_bit_set(data, IS1_AO_VLAN_POP_CNT_ENA, action->pop_enable);
    srvl_vcap_action_set(data, IS1_AO_VLAN_POP_CNT, IS1_AL_VLAN_POP_CNT, action->pop);
    srvl_vcap_action_set(data, IS1_AO_CUSTOM_ACE_TYPE_ENA, IS1_AL_CUSTOM_ACE_TYPE_ENA, 0);
    
    /* Set TCAM data */
    return srvl_vcap_entry_set(vtss_state, tcam, idx, data);
}

static vtss_rc srvl_is1_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    VTSS_I("enter");

    return srvl_vcap_entry_del(vtss_state, VTSS_TCAM_IS1, idx);
}

static vtss_rc srvl_is1_entry_move(vtss_state_t *vtss_state,
                                   vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    VTSS_I("enter");

    return srvl_vcap_entry_move(vtss_state, VTSS_TCAM_IS1, idx, count, up);
}

static void srvl_debug_is1_base(srvl_debug_info_t *info, u32 offset)
{
    u32                 old_offset = info->data.key_offset;
    vtss_debug_printf_t pr = info->pr;

    info->data.key_offset += (offset - IS1_QKO_LOOKUP); /* Adjust offset */
    srvl_debug_bits(info, "lookup", IS1_QKO_LOOKUP, IS1_QKL_LOOKUP);
    srvl_debug_bits(info, "igr_port_mask", IS1_QKO_IGR_PORT_MASK, IS1_QKL_IGR_PORT_MASK);
    srvl_debug_bits(info, "isdx", IS1_QKO_ISDX, IS1_QKL_ISDX);
    pr("\n");
    srvl_debug_bit(info, "l2_mc", IS1_QKO_L2_MC);
    srvl_debug_bit(info, "l2_bc", IS1_QKO_L2_BC);
    srvl_debug_bit(info, "ip_mc", IS1_QKO_IP_MC);
    srvl_debug_bit(info, "tagged", IS1_QKO_VLAN_TAGGED);
    srvl_debug_bit(info, "dbl_tagged", IS1_QKO_VLAN_DBL_TAGGED);
    pr("\n");
    srvl_debug_bit(info, "tpid", IS1_QKO_TPID);
    srvl_debug_u12(info, "vid", IS1_QKO_VID);
    srvl_debug_bit(info, "dei", IS1_QKO_DEI);
    srvl_debug_u3(info, "pcp", IS1_QKO_PCP);
    pr("\n");
    info->data.key_offset = old_offset; /* Restore offset */
}

static void srvl_debug_is1_inner(srvl_debug_info_t *info, u32 offset)
{
    u32 old_offset = info->data.key_offset;

    info->data.key_offset += (offset - IS1_QKO_INNER_TPID); /* Adjust offset */
    srvl_debug_bit(info, "in_tpid", IS1_QKO_INNER_TPID);
    srvl_debug_u12(info, "in_vid", IS1_QKO_INNER_VID);
    srvl_debug_bit(info, "in_dei", IS1_QKO_INNER_DEI);
    srvl_debug_u3(info, "in_pcp", IS1_QKO_INNER_PCP);
    info->pr("\n");
    info->data.key_offset = old_offset; /* Restore offset */
}

static void srvl_debug_is1_misc(srvl_debug_info_t *info, u32 offset)
{
    u32                 old_offset = info->data.key_offset;
    vtss_debug_printf_t pr = info->pr;

    info->data.key_offset += (offset - IS1_QKO_ETYPE_LEN); /* Adjust offset */
    srvl_debug_bit(info, "etype_len", IS1_QKO_ETYPE_LEN);
    srvl_debug_u16(info, "etype", IS1_QKO_ETYPE);
    srvl_debug_bit(info, "snap", IS1_QKO_IP_SNAP);
    srvl_debug_bit(info, "ip4", IS1_QKO_IP4);
    pr("\n");
    srvl_debug_bit(info, "l3_fragment", IS1_QKO_L3_FRAGMENT);
    srvl_debug_bit(info, "l3_fragoffs", IS1_QKO_L3_FRAG_OFS_GT0);
    srvl_debug_bit(info, "l3_options", IS1_QKO_L3_OPTIONS);
    srvl_debug_u6(info, "l3_dscp", IS1_QKO_L3_DSCP);
    pr("\n");
    info->data.key_offset = old_offset; /* Restore offset */
}

static void srvl_debug_is1_l4(srvl_debug_info_t *info, u32 offset)
{
    u32 old_offset = info->data.key_offset;

    info->data.key_offset += (offset - IS1_HKO_NORMAL_TCP_UDP); /* Adjust offset */
    srvl_debug_bit(info, "tcp_udp", IS1_HKO_NORMAL_TCP_UDP);
    srvl_debug_bit(info, "tcp", IS1_HKO_NORMAL_TCP);
    srvl_debug_u16(info, "l4_sport", IS1_HKO_NORMAL_L4_SPORT);
    srvl_debug_u8(info, "l4_rng", IS1_HKO_NORMAL_L4_RNG);
    info->pr("\n");
    info->data.key_offset = old_offset; /* Restore offset */
}

static vtss_rc srvl_debug_is1(srvl_debug_info_t *info)
{
    vtss_debug_printf_t pr = info->pr;
    srvl_tcam_data_t    *data = &info->data;
    u32                 type;

    if (info->is_action) {
        /* Print action */
        srvl_debug_action(info, "dscp", IS1_AO_DSCP_ENA, IS1_AO_DSCP_VAL, IS1_AL_DSCP_VAL);
        srvl_debug_action(info, "qos", IS1_AO_QOS_ENA, IS1_AO_QOS_VAL, IS1_AL_QOS_VAL);
        srvl_debug_action(info, "dp", IS1_AO_DP_ENA, IS1_AO_DP_VAL, IS1_AL_DP_VAL);
        srvl_debug_u8(info, "pag_mask", IS1_AO_PAG_OVERRIDE_MASK);
        srvl_debug_u8(info, "pag_val", IS1_AO_PAG_VAL);
        srvl_debug_action(info, "isdx", IS1_AO_ISDX_REPLACE_ENA, 
                          IS1_AO_ISDX_ADD_VAL, IS1_AL_ISDX_ADD_VAL);
        pr("\n");
        srvl_debug_action(info, "vid", IS1_AO_VID_REPLACE_ENA, 
                          IS1_AO_VID_ADD_VAL, IS1_AL_VID_ADD_VAL);
        srvl_debug_action(info, "pcp", IS1_AO_PCP_DEI_ENA, 
                          IS1_AO_PCP_VAL, IS1_AL_PCP_VAL);
        srvl_debug_action_len(info, "dei", IS1_AO_PCP_DEI_ENA, IS1_AL_PCP_DEI_ENA,
                              IS1_AO_DEI_VAL, IS1_AL_DEI_VAL);
        srvl_debug_action(info, "pop", IS1_AO_VLAN_POP_CNT_ENA, 
                          IS1_AO_VLAN_POP_CNT, IS1_AL_VLAN_POP_CNT);
        srvl_debug_action(info, "fid", IS1_AO_FID_SEL, IS1_AO_FID_VAL, IS1_AL_FID_VAL);
        srvl_debug_bits(info, "custom_ace_ena", 
                        IS1_AO_CUSTOM_ACE_TYPE_ENA, IS1_AL_CUSTOM_ACE_TYPE_ENA);
        pr("hit:%u ", info->data.cnt);
        return VTSS_RC_OK;
    }

    /* Print entry */
    if (data->tg_sw == VCAP_TG_QUARTER) {
        /* DBL_VID */
        srvl_debug_is1_base(info, IS1_QKO_LOOKUP);
        srvl_debug_is1_inner(info, IS1_QKO_INNER_TPID);
        srvl_debug_is1_misc(info, IS1_QKO_ETYPE_LEN);
        srvl_debug_bit(info, "tcp_udp", IS1_QKO_TCP_UDP);
        srvl_debug_bit(info, "tcp", IS1_QKO_TCP);
        pr("\n");
        return VTSS_RC_OK;
    } else if (data->tg_sw == VCAP_TG_HALF) {
        /* Common fields for half keys */
        srvl_debug_bits(info, "type", IS1_HKO_TYPE, IS1_HKL_TYPE);
        type = srvl_entry_bs_get(info, IS1_HKO_TYPE, IS1_HKL_TYPE);
        pr("(%s) ",
           type == IS1_TYPE_NORMAL ? "normal" :
           type == IS1_TYPE_5TUPLE_IP4 ? "5tuple_ip4" : "?");
        srvl_debug_is1_base(info, IS1_HKO_LOOKUP);

        /* Specific format for half keys */
        switch (type) {
        case IS1_TYPE_NORMAL:
            srvl_debug_u48(info, "l2_smac", IS1_HKO_NORMAL_L2_SMAC);
            srvl_debug_is1_misc(info, IS1_HKO_NORMAL_ETYPE_LEN);
            srvl_debug_u32(info, "l3_ip4_sip", IS1_HKO_NORMAL_L3_IP4_SIP);
            srvl_debug_is1_l4(info, IS1_HKO_NORMAL_TCP_UDP);
            break;
        case IS1_TYPE_5TUPLE_IP4:
            srvl_debug_is1_inner(info, IS1_HKO_5TUPLE_IP4_INNER_TPID);
            srvl_debug_bit(info, "ip4", IS1_HKO_5TUPLE_IP4_IP4);
            srvl_debug_bit(info, "l3_fragment", IS1_HKO_5TUPLE_IP4_L3_FRAGMENT);
            srvl_debug_bit(info, "l3_fragoffs", IS1_HKO_5TUPLE_IP4_L3_FRAG_OFS_GT0);
            srvl_debug_bit(info, "l3_options", IS1_HKO_5TUPLE_IP4_L3_OPTIONS);
            srvl_debug_u6(info, "l3_dscp", IS1_HKO_5TUPLE_IP4_L3_DSCP);
            pr("\n");
            srvl_debug_u32(info, "l3_ip4_dip", IS1_HKO_5TUPLE_IP4_L3_IP4_DIP);
            srvl_debug_u32(info, "l3_ip4_sip", IS1_HKO_5TUPLE_IP4_L3_IP4_SIP);
            srvl_debug_u8(info, "l3_proto", IS1_HKO_5TUPLE_IP4_L3_IP_PROTO);
            srvl_debug_bit(info, "tcp_udp", IS1_HKO_5TUPLE_IP4_TCP_UDP);
            srvl_debug_bit(info, "tcp", IS1_HKO_5TUPLE_IP4_TCP);
            srvl_debug_u8(info, "l4_rng", IS1_HKO_5TUPLE_IP4_L4_RNG);
            pr("\n");
            srvl_debug_u32(info, "ip_payload", IS1_HKO_5TUPLE_IP4_IP_PAYLOAD);
            break;
        default:
            break;
        }
        return VTSS_RC_OK;
    }

    /* VCAP_TG_FULL */
    srvl_debug_bits(info, "type", IS1_FKO_TYPE, IS1_FKL_TYPE);
    type = srvl_entry_bs_get(info, IS1_FKO_TYPE, IS1_FKL_TYPE);
    pr("(%s) ",
       type == IS1_TYPE_NORMAL_IP6 ? "normal_ip6" :
       type == IS1_TYPE_7TUPLE ? "7tuple" :
       type == IS1_TYPE_5TUPLE_IP6 ? "5tuple_ip6" : "?");

    /* Common format for full keys */
    srvl_debug_is1_base(info, IS1_FKO_LOOKUP);
    srvl_debug_is1_inner(info, IS1_FKO_INNER_TPID);

    /* Specific format for full keys */
    switch (type) {
    case IS1_TYPE_NORMAL_IP6:
        srvl_debug_u48(info, "l2_smac", IS1_FKO_NORMAL_IP6_L2_SMAC);
        srvl_debug_u6(info, "l3_dscp", IS1_FKO_NORMAL_IP6_L3_DSCP);
        srvl_debug_u128(info, "l3_ip6_sip", IS1_FKO_NORMAL_IP6_L3_IP6_SIP);
        srvl_debug_u8(info, "l3_proto", IS1_FKO_NORMAL_IP6_L3_IP_PROTO);
        srvl_debug_bit(info, "tcp_udp", IS1_FKO_NORMAL_IP6_TCP_UDP);
        srvl_debug_u8(info, "l4_rng", IS1_FKO_NORMAL_IP6_L4_RNG);
        srvl_debug_bytes(info, "ip_payload", IS1_FKO_NORMAL_IP6_IP_PAYLOAD, 
                         IS1_FKL_NORMAL_IP6_IP_PAYLOAD);
        break;
    case IS1_TYPE_7TUPLE:
        srvl_debug_u48(info, "l2_dmac", IS1_FKO_7TUPLE_L2_DMAC);
        srvl_debug_u48(info, "l2_smac", IS1_FKO_7TUPLE_L2_SMAC);
        srvl_debug_is1_misc(info, IS1_FKO_7TUPLE_ETYPE_LEN);
        srvl_debug_u16(info, "l3_ip6_dip_msb", IS1_FKO_7TUPLE_L3_IP6_DIP_MSB);
        pr("\n");
        srvl_debug_bytes(info, "l3_ip6_dip", IS1_FKO_7TUPLE_L3_IP6_DIP, IS1_FKL_7TUPLE_L3_IP6_DIP);
        srvl_debug_u16(info, "l3_ip6_sip_msb", IS1_FKO_7TUPLE_L3_IP6_SIP_MSB);
        pr("\n");
        srvl_debug_bytes(info, "l3_ip6_sip", IS1_FKO_7TUPLE_L3_IP6_SIP, IS1_FKL_7TUPLE_L3_IP6_SIP);
        srvl_debug_is1_l4(info, IS1_FKO_7TUPLE_TCP_UDP);
        break;
    case IS1_TYPE_5TUPLE_IP6:
        srvl_debug_u6(info, "l3_dscp", IS1_FKO_5TUPLE_IP6_L3_DSCP);
        srvl_debug_u128(info, "l3_ip6_dip", IS1_FKO_5TUPLE_IP6_L3_IP6_DIP);
        srvl_debug_u128(info, "l3_ip6_sip", IS1_FKO_5TUPLE_IP6_L3_IP6_SIP);
        srvl_debug_u8(info, "l3_proto", IS1_FKO_5TUPLE_IP6_L3_IP_PROTO);
        srvl_debug_bit(info, "tcp_udp", IS1_FKO_5TUPLE_IP6_TCP_UDP);
        srvl_debug_u8(info, "l4_rng", IS1_FKO_5TUPLE_IP6_L4_RNG);
        srvl_debug_u32(info, "ip_payload", IS1_FKO_5TUPLE_IP6_IP_PAYLOAD);
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_debug_is1_all(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    u32  port, i;
    BOOL header = 1;
    char buf[32];
    
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        if (vtss_cmn_port2port_no(vtss_state, info, port) == VTSS_PORT_NO_NONE)
            continue;
        if (header)
            vtss_srvl_debug_reg_header(pr, "ANA:PORT");
        header = 0;
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_VCAP_CFG(port), port, "VCAP_CFG");
        for (i = 0; i < 3; i++) {
            VTSS_SPRINTF(buf, "VCAP_S1_CFG_%u", port);
            vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_VCAP_S1_KEY_CFG(port, i), i, buf);
        }
    }
    if (!header)
        pr("\n");
    return srvl_debug_vcap(vtss_state, VTSS_TCAM_IS1, "IS1", pr, info, srvl_debug_is1);
}

/* ================================================================= *
 *  IS2 functions
 * ================================================================= */

static vtss_rc srvl_is2_entry_get(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, u32 *counter, BOOL clear) 
{
    VTSS_IG(VTSS_TRACE_GROUP_SECURITY, "enter");
    
    return srvl_vcap_counter_get(vtss_state, VTSS_TCAM_IS2, idx, counter, clear);
}

static vtss_rc srvl_is2_action_set(vtss_state_t *vtss_state,
                                   srvl_tcam_data_t *data, vtss_acl_action_t *action, BOOL host_match, u32 counter)
{
    vtss_acl_port_action_t act = action->port_action;
    vtss_acl_ptp_action_t  ptp = action->ptp_action;
    u32                    pol_idx, mask, discard;
    u32                    action_add_sub = 0;

    if (data->type == IS2_ACTION_TYPE_SMAC_SIP) {
        srvl_vcap_action_bit_set(data, IS2_AO_SMAC_SIP_CPU_COPY_ENA, 0);
        srvl_vcap_action_set(data, IS2_AO_SMAC_SIP_CPU_QU_NUM, IS2_AL_SMAC_SIP_CPU_QU_NUM, 0);
        srvl_vcap_action_bit_set(data, IS2_AO_SMAC_SIP_FWD_KILL_ENA, 0);
        srvl_vcap_action_bit_set(data, IS2_AO_SMAC_SIP_HOST_MATCH, host_match);
        return VTSS_RC_OK;
    }

    srvl_vcap_action_bit_set(data, IS2_AO_HIT_ME_ONCE, action->cpu_once);
    srvl_vcap_action_bit_set(data, IS2_AO_CPU_COPY_ENA, action->cpu);
    srvl_vcap_action_set(data, IS2_AO_CPU_QU_NUM, IS2_AL_CPU_QU_NUM, action->cpu_queue);
    srvl_vcap_action_bit_set(data, IS2_AO_MIRROR_ENA, action->mirror);
    srvl_vcap_action_bit_set(data, IS2_AO_LRN_DIS, action->learn ? 0 : 1);
    mask = vtss_srvl_port_mask(vtss_state, action->port_list);
    discard = (act != VTSS_ACL_PORT_ACTION_NONE && mask == 0 ? 1 : 0);
    if (discard && action->cpu_once == 0 && action->cpu == 0) {
        /* Forwarding and CPU copy disabled, discard using policer to avoid CPU copy */
        pol_idx = SRVL_POLICER_DISCARD;
        act = VTSS_ACL_PORT_ACTION_NONE; // Use mode 0 to make Rx red counters increase
    } else if (action->police) {
        pol_idx = (SRVL_POLICER_ACL + action->policer_no);
#if defined(SRVL_POLICER_EVC)
    } else if (action->evc_police) {
        pol_idx = (SRVL_POLICER_EVC + action->evc_policer_id);
#endif /* SRVL_POLICER_EVC */
    } else {
        pol_idx = 0;
    }
    srvl_vcap_action_set(data, IS2_AO_MASK_MODE, IS2_AL_MASK_MODE,
                         act == VTSS_ACL_PORT_ACTION_NONE ? IS2_ACT_MASK_MODE_NONE :
                         act == VTSS_ACL_PORT_ACTION_PGID ? IS2_ACT_MASK_MODE_POLICY :
                         act == VTSS_ACL_PORT_ACTION_FILTER ? IS2_ACT_MASK_MODE_FILTER :
                         IS2_ACT_MASK_MODE_REDIR);
    srvl_vcap_action_bit_set(data, IS2_AO_POLICE_ENA, pol_idx ? 1 : 0);
    srvl_vcap_action_set(data, IS2_AO_POLICE_IDX, IS2_AL_POLICE_IDX, pol_idx);
    srvl_vcap_action_bit_set(data, IS2_AO_POLICE_VCAP_ONLY, 0);
    if (act == VTSS_ACL_PORT_ACTION_REDIR) {
        mask &= vtss_srvl_port_mask(vtss_state, vtss_state->l2.tx_forward_aggr);
    }
    srvl_vcap_action_set(data, IS2_AO_PORT_MASK, IS2_AL_PORT_MASK, mask);

#if defined(VTSS_FEATURE_TIMESTAMP)
    if (vtss_state->ts.add_sub_option && (ptp == VTSS_ACL_PTP_ACTION_ONE_STEP ||
                                          ptp == VTSS_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY ||
                                          ptp == VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1 ||
                                          ptp == VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2)) {
        action_add_sub = IS2_ACT_REW_OP_PTP_ONE_ADD_SUB;
        VTSS_D("Setting option add_sub %x in ptp_action %d",action_add_sub, ptp);
    }
#endif /* VTSS_FEATURE_TIMESTAMP */
    srvl_vcap_action_set(
        data, IS2_AO_REW_OP, IS2_AL_REW_OP, 
        action_add_sub |
        (ptp == VTSS_ACL_PTP_ACTION_ONE_STEP ? IS2_ACT_REW_OP_PTP_ONE :
         ptp == VTSS_ACL_PTP_ACTION_TWO_STEP ? IS2_ACT_REW_OP_PTP_TWO :
         ptp == VTSS_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY ? IS2_ACT_REW_OP_PTP_ONE_ADD_DELAY :
         ptp == VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1 ? IS2_ACT_REW_OP_PTP_ONE_SUB_DELAY_1 :
         ptp == VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2 ? IS2_ACT_REW_OP_PTP_ONE_SUB_DELAY_2 :
         action->mac_swap ? IS2_ACT_REW_OP_SPECIAL : IS2_ACT_REW_OP_NONE));
    srvl_vcap_action_bit_set(data, IS2_AO_ISDX_ENA, 0);
    srvl_vcap_action_bit_set(data, IS2_AO_LM_CNT_DIS, action->lm_cnt_disable ? 1 : 0);
    srvl_vcap_action_set(data, IS2_AO_ACL_ID, IS2_AL_ACL_ID, action->ifh_flag ? 1 : 0);
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_is2_entry_add(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    const tcam_props_t    *tcam = &tcam_info[VTSS_TCAM_IS2];
    srvl_tcam_data_t      tcam_data, *data = &tcam_data;
    u32                   type, i, x, mask, count, type_mask = VTSS_BITMASK(IS2_HKL_TYPE);
    u32                   range, ptp_vm[2];
    vtss_is2_data_t       *is2 = &vcap_data->u.is2;
    vtss_ace_t            *ace = &is2->entry->ace;
    vtss_ace_frame_ipv4_t *ipv4 = &ace->frame.ipv4;
    vtss_ace_frame_ipv6_t *ipv6 = &ace->frame.ipv6;
    vtss_vcap_bit_t       ttl, tcp_fin, tcp_syn, tcp_rst, tcp_psh, tcp_ack, tcp_urg;
    vtss_vcap_bit_t       fragment, options, sip_eq_dip, sport_eq_dport, seq_zero, service_frm;
    vtss_vcap_u8_t        *proto = NULL, *ds;
    vtss_vcap_u48_t       *ip_data, *smac = NULL, *dmac = NULL, smac_data;
    vtss_vcap_udp_tcp_t   *sport, *dport;
    vtss_vcap_vid_t       sp, dp;
    vtss_ace_ptp_t        *ptp;
    u8                    *p, val[7], msk[7];
    vtss_vcap_ip_t        sip;
    vtss_ace_u40_t        llc;
    BOOL                  host_match = is2->entry->host_match;
    BOOL                  smac_sip6 = is2->entry->smac_sip6;
    
    VTSS_IG(VTSS_TRACE_GROUP_SECURITY, "enter");
    
    data->type = IS2_ACTION_TYPE_NORMAL;
    if (idx->key_size == VTSS_VCAP_KEY_SIZE_QUARTER) {
        /* SMAC_SIP4 rule */
        data->type = IS2_ACTION_TYPE_SMAC_SIP;
    } else if (smac_sip6) {
        /* SMAC_SIP6 rule */
        data->type = IS2_ACTION_TYPE_SMAC_SIP;
    }

    /* Get TCAM data */
    data->cnt = counter;
    VTSS_RC(srvl_vcap_entry_add(vtss_state, tcam, idx, data));

    if (data->type == IS2_ACTION_TYPE_SMAC_SIP) {
        /* Setup SMAC_SIP key fields */
        if (smac_sip6) {
            srvl_vcap_key_set(data, IS2_HKO_TYPE, IS2_HKL_TYPE, IS2_TYPE_SMAC_SIP6, type_mask);
        } else if (host_match) {
            srvl_vcap_key_set(data, IS2_QKO_IGR_PORT, IS2_QKL_IGR_PORT, 0, 0);
            for (i = 0; i < 6; i++) {
                smac_data.value[i] = ace->frame.ipv4.sip_smac.smac.addr[i];
                smac_data.mask[i] = 0xff;
            }
            srvl_vcap_key_u48_set(data, IS2_QKO_L2_SMAC, &smac_data);
            sip.value = ace->frame.ipv4.sip_smac.sip;
            sip.mask = 0xffffffff;
            srvl_vcap_key_ipv4_set(data, IS2_QKO_L3_IP4_SIP, &sip);
        }

        /* Setup action */
        VTSS_RC(srvl_is2_action_set(vtss_state, data, &ace->action, host_match, counter));
        
        /* Set TCAM data */
        return srvl_vcap_entry_set(vtss_state, tcam, idx, data);
    }

    mask = vtss_srvl_port_mask(vtss_state, ace->port_list);
    service_frm = (ace->isdx_enable ? VTSS_VCAP_BIT_1 :
                   (ace->isdx_disable || ace->vlan.vid.mask) ? VTSS_VCAP_BIT_0 : VTSS_VCAP_BIT_ANY);
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

    /* IPv4/IPv6: Encode PTP byte 0,1,4 and 6 in value/mask */
    for (i = 0; i < 2; i++) {
        p = (i ? &ptp->header.mask[0] : &ptp->header.value[0]);
        x = (((p[3] & 0x80) >> 5) | ((p[3] & 0x6) >> 1)); /* Bit 7,2,1 */
        ptp_vm[i] = ((p[0] & 0xf) +         /* messageType */
                     (x << 4) +             /* flagField, bit 7,2,1 */
                     (p[2] << 7) +          /* domainNumber */
                     ((p[1] & 0xf) << 15)); /* versionPTP */
    }

    sp.value = sport->low;
    sp.mask = (sport->in_range && sport->low == sport->high ? 0xffff : 0);
    dp.value = dport->low;
    dp.mask = (dport->in_range && dport->low == dport->high ? 0xffff : 0);
    range = ((is2->srange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->srange)) |
             (is2->drange == VTSS_VCAP_RANGE_CHK_NONE ? 0 : (1 << is2->drange)));

    if (idx->key_size == VTSS_VCAP_KEY_SIZE_FULL) {
        /* IPv6 full rule */
        srvl_vcap_key_bit_set(data, IS2_FKO_FIRST, ace->lookup ? VTSS_VCAP_BIT_0 : VTSS_VCAP_BIT_1);
        srvl_vcap_key_u8_set(data, IS2_FKO_PAG, &ace->policy);
        srvl_vcap_key_set(data, IS2_FKO_IGR_PORT_MASK, IS2_FKL_IGR_PORT_MASK, 0, ~mask);
        srvl_vcap_key_bit_set(data, IS2_FKO_SERVICE_FRM, service_frm);
        srvl_vcap_key_bit_set(data, IS2_FKO_HOST_MATCH, host_match ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_ANY);
        srvl_vcap_key_bit_set(data, IS2_FKO_L2_MC, ace->dmac_mc);
        srvl_vcap_key_bit_set(data, IS2_FKO_L2_BC, ace->dmac_bc);
        srvl_vcap_key_bit_set(data, IS2_FKO_VLAN_TAGGED, ace->vlan.tagged);
        srvl_vcap_key_set(data, IS2_FKO_VID, IS2_FKL_VID, ace->vlan.vid.value, ace->vlan.vid.mask);
        srvl_vcap_key_bit_set(data, IS2_FKO_DEI, ace->vlan.cfi);
        srvl_vcap_key_u3_set(data, IS2_FKO_PCP, &ace->vlan.usr_prio);
        type = IS2_TYPE_IP6_TCP_UDP;
        srvl_vcap_key_bit_set(data, IS2_FKO_L3_TTL_GT0, ttl);
        srvl_vcap_key_u8_set(data, IS2_FKO_L3_TOS, ds);
        srvl_vcap_key_bytes_set(data, IS2_FKO_L3_IP6_DIP, ipv6->dip.value, ipv6->dip.mask, 16);
        srvl_vcap_key_bytes_set(data, IS2_FKO_L3_IP6_SIP, ipv6->sip.value, ipv6->sip.mask, 16);
        srvl_vcap_key_bit_set(data, IS2_FKO_DIP_EQ_SIP, sip_eq_dip);

        type = IS2_TYPE_IP6_TCP_UDP;
        if (vtss_vcap_udp_tcp_rule(proto)) {
            /* UDP/TCP protocol match */
            srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_TCP,
                                  proto->value == 6 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            srvl_vcap_key_set(data, IS2_FKO_IP6_TCP_UDP_L4_DPORT, IS2_FKL_IP6_TCP_UDP_L4_DPORT, dp.value, dp.mask);
            srvl_vcap_key_set(data, IS2_FKO_IP6_TCP_UDP_L4_SPORT, IS2_FKL_IP6_TCP_UDP_L4_SPORT, sp.value, sp.mask);
            srvl_vcap_key_set(data, IS2_FKO_IP6_TCP_UDP_L4_RNG, IS2_FKL_IP6_TCP_UDP_L4_RNG, range, range);
            srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_SPORT_EQ_DPORT, sport_eq_dport);

            if (ptp->enable) {
                srvl_vcap_key_set(data, IS2_FKO_IP6_TCP_UDP_SEQUENCE_EQ0, 19, ptp_vm[0], ptp_vm[1]);
            } else {
                srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_SEQUENCE_EQ0, seq_zero);
                srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_L4_FIN, tcp_fin);
                srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_L4_SYN, tcp_syn);
                srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_L4_RST, tcp_rst);
                srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_L4_PSH, tcp_psh);
                srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_L4_ACK, tcp_ack);
                srvl_vcap_key_bit_set(data, IS2_FKO_IP6_TCP_UDP_L4_URG, tcp_urg);
                srvl_vcap_key_set(data, IS2_FKO_IP6_TCP_UDP_L4_1588_DOM, IS2_FKL_IP6_TCP_UDP_L4_1588_DOM, 0, 0);
                srvl_vcap_key_set(data, IS2_FKO_IP6_TCP_UDP_L4_1588_VER, IS2_FKL_IP6_TCP_UDP_L4_1588_VER, 0, 0);
            }
        } else if (proto->mask == 0) {
            /* Any IP protocol match */
            type_mask = IS2_TYPE_MASK_IP_ANY;
            srvl_vcap_key_set(data, IS2_FKO_IP6_OTHER_L3_PROTO, 32, 0, 0);
            srvl_vcap_key_set(data, IS2_FKO_IP6_OTHER_L3_PROTO + 32, 32, 0, 0);
        } else {
            /* Non-UDP/TCP protocol match */
            type = IS2_TYPE_IP6_OTHER;
            srvl_vcap_key_u8_set(data, IS2_FKO_IP6_OTHER_L3_PROTO, proto);
            for (i = 0; i < 7; i++) {
                val[i] = (i < 6 ? ip_data->value[i] : 0);
                msk[i] = (i < 6 ? ip_data->mask[i] : 0);
            }
            srvl_vcap_key_bytes_set(data, IS2_FKO_IP6_OTHER_L3_PAYLOAD, val, msk, 7);
        }
        srvl_vcap_key_set(data, IS2_FKO_TYPE, IS2_FKL_TYPE, type, type_mask);
        VTSS_RC(srvl_is2_action_set(vtss_state, data, &ace->action, 0, counter));
        return srvl_vcap_entry_set(vtss_state, tcam, idx, data);
    }

    /* Common half key fields */
    srvl_vcap_key_bit_set(data, IS2_HKO_FIRST, ace->lookup ? VTSS_VCAP_BIT_0 : VTSS_VCAP_BIT_1);
    srvl_vcap_key_u8_set(data, IS2_HKO_PAG, &ace->policy);
    srvl_vcap_key_set(data, IS2_HKO_IGR_PORT_MASK, IS2_HKL_IGR_PORT_MASK, 0, ~mask);
    srvl_vcap_key_bit_set(data, IS2_HKO_SERVICE_FRM, service_frm);
    srvl_vcap_key_bit_set(data, IS2_HKO_HOST_MATCH, host_match ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_ANY);
    srvl_vcap_key_bit_set(data, IS2_HKO_L2_MC, ace->dmac_mc);
    srvl_vcap_key_bit_set(data, IS2_HKO_L2_BC, ace->dmac_bc);
    srvl_vcap_key_bit_set(data, IS2_HKO_VLAN_TAGGED, ace->vlan.tagged);
    srvl_vcap_key_set(data, IS2_HKO_VID, IS2_HKL_VID, ace->vlan.vid.value, ace->vlan.vid.mask);
    srvl_vcap_key_bit_set(data, IS2_HKO_DEI, ace->vlan.cfi);
    srvl_vcap_key_u3_set(data, IS2_HKO_PCP, &ace->vlan.usr_prio);

    /* Type specific fields */
    switch (ace->type) {
    case VTSS_ACE_TYPE_ANY:
        type = IS2_TYPE_ETYPE;
        type_mask = 0;
        count = (tcam->entry_width / 2);
        for (i = (IS2_HKO_PCP + IS2_HKL_PCP); i < count; i += 32) {
            /* Clear entry data */
            srvl_vcap_key_set(data, i, MIN(32, count - i), 0, 0);
        }
        for (i = 0; i < 6; i++) {
            if (ace->frame.any.dmac.mask[i] != 0 || ace->frame.any.smac.mask[i] != 0) {
                /* Match ETYPE/LLC/SNAP frames with DMAC/SMAC filtering. ARP frames must be mapped to ETYPE */
                type_mask = 0xc;
                dmac = &ace->frame.any.dmac;
                smac = &ace->frame.any.smac;
                break;
            }
        }
        break;
    case VTSS_ACE_TYPE_ETYPE:
        type = IS2_TYPE_ETYPE;
        dmac = &ace->frame.etype.dmac;
        smac = &ace->frame.etype.smac;
        srvl_vcap_key_u16_set(data, IS2_HKO_MAC_ETYPE_ETYPE, &ace->frame.etype.etype);
        ptp = &ace->frame.etype.ptp;
        if (ptp->enable) {
            /* Encode PTP byte 0,1,4 and 6 in value/mask */
            for (i = 0; i < 2; i++) {
                p = (i ? &ptp->header.mask[0] : &ptp->header.value[0]);
                x = (((p[3] & 0x80) >> 5) | ((p[3] & 0x6) >> 1)); /* Bit 7,2,1 */
                ptp_vm[i] = (p[1] +         /* Byte 1 (versionPTP) */
                             (p[0] << 8) +  /* Byte 0 (messageType) */
                             (p[2] << 16) + /* Byte 4 (domainNumber) */
                             (x << 24));    /* Byte 6 (flagField, bit 7,2,1) */
            }
            srvl_vcap_key_set(data, IS2_HKO_MAC_ETYPE_L2_PAYLOAD, IS2_HKL_MAC_ETYPE_L2_PAYLOAD, ptp_vm[0], ptp_vm[1]);
        } else {
            srvl_vcap_key_u16_set(data, IS2_HKO_MAC_ETYPE_L2_PAYLOAD, &ace->frame.etype.data);
            srvl_vcap_key_set(data, IS2_HKO_MAC_ETYPE_L2_PAYLOAD + 16, 
                              IS2_HKL_MAC_ETYPE_L2_PAYLOAD - 16, 0, 0);
        }
        break;
    case VTSS_ACE_TYPE_LLC:
        type = IS2_TYPE_LLC;
        dmac = &ace->frame.llc.dmac;
        smac = &ace->frame.llc.smac;
        for (i = 0; i < 4; i++) {
            llc.value[i] = ace->frame.llc.llc.value[i];
            llc.mask[i] = ace->frame.llc.llc.mask[i];
        }
        llc.value[4] = 0;
        llc.mask[4] = 0;
        srvl_vcap_key_u40_set(data, IS2_HKO_MAC_LLC_L2_LLC, &llc);
        break;
    case VTSS_ACE_TYPE_SNAP:
        type = IS2_TYPE_SNAP;
        dmac = &ace->frame.snap.dmac;
        smac = &ace->frame.snap.smac;
        srvl_vcap_key_u40_set(data, IS2_HKO_MAC_SNAP_L2_SNAP, &ace->frame.snap.snap);
        break;
    case VTSS_ACE_TYPE_ARP:
        type = IS2_TYPE_ARP;
        srvl_vcap_key_u48_set(data, IS2_HKO_MAC_ARP_L2_SMAC, &ace->frame.arp.smac);
        srvl_vcap_key_bit_set(data, IS2_HKO_MAC_ARP_ARP_ADDR_SPACE_OK, ace->frame.arp.ethernet);
        srvl_vcap_key_bit_set(data, IS2_HKO_MAC_ARP_ARP_PROTO_SPACE_OK, ace->frame.arp.ip);
        srvl_vcap_key_bit_set(data, IS2_HKO_MAC_ARP_ARP_LEN_OK, ace->frame.arp.length);
        srvl_vcap_key_bit_set(data, IS2_HKO_MAC_ARP_ARP_TGT_MATCH, ace->frame.arp.dmac_match);
        srvl_vcap_key_bit_set(data, IS2_HKO_MAC_ARP_ARP_SENDER_MATCH, ace->frame.arp.smac_match);
        srvl_vcap_key_bit_set(data, IS2_HKO_MAC_ARP_ARP_OPCODE_UNKNOWN, ace->frame.arp.unknown);
        srvl_vcap_key_bit_inv_set(data, IS2_HKO_MAC_ARP_ARP_OPCODE, ace->frame.arp.req);
        srvl_vcap_key_bit_inv_set(data, IS2_HKO_MAC_ARP_ARP_OPCODE + 1, ace->frame.arp.arp);
        srvl_vcap_key_ipv4_set(data, IS2_HKO_MAC_ARP_L3_IP4_DIP, &ace->frame.arp.dip);
        srvl_vcap_key_ipv4_set(data, IS2_HKO_MAC_ARP_L3_IP4_SIP, &ace->frame.arp.sip);
        srvl_vcap_key_bit_set(data, IS2_HKO_MAC_ARP_DIP_EQ_SIP, VTSS_VCAP_BIT_ANY);
        break;
    case VTSS_ACE_TYPE_IPV4:
    case VTSS_ACE_TYPE_IPV6:
        srvl_vcap_key_bit_set(data, IS2_HKO_IP4, ipv4 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
        srvl_vcap_key_bit_set(data, IS2_HKO_L3_FRAGMENT, fragment);
        srvl_vcap_key_bit_set(data, IS2_HKO_L3_FRAG_OFS_GT0, VTSS_VCAP_BIT_ANY);
        srvl_vcap_key_bit_set(data, IS2_HKO_L3_OPTIONS, options);
        srvl_vcap_key_bit_set(data, IS2_HKO_L3_TTL_GT0, ttl);
        srvl_vcap_key_u8_set(data, IS2_HKO_L3_TOS, ds);
        if (ipv4) {
            srvl_vcap_key_ipv4_set(data, IS2_HKO_L3_IP4_DIP, &ipv4->dip);
            srvl_vcap_key_ipv4_set(data, IS2_HKO_L3_IP4_SIP, &ipv4->sip);
        } else if (ipv6) {
            srvl_vcap_key_bytes_set(data, IS2_HKO_L3_IP4_DIP, &ipv6->sip.value[8], 
                                    &ipv6->sip.mask[8], 8);
        }
        srvl_vcap_key_bit_set(data, IS2_HKO_DIP_EQ_SIP, sip_eq_dip);
        
        if (vtss_vcap_udp_tcp_rule(proto)) {
            /* UDP/TCP protocol match */
            type = IS2_TYPE_IP_UDP_TCP;
            srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_TCP, 
                                  proto->value == 6 ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
            srvl_vcap_key_set(data, IS2_HKO_IP4_TCP_UDP_L4_DPORT, IS2_HKL_IP4_TCP_UDP_L4_DPORT, dp.value, dp.mask);
            srvl_vcap_key_set(data, IS2_HKO_IP4_TCP_UDP_L4_SPORT, IS2_HKL_IP4_TCP_UDP_L4_SPORT, sp.value, sp.mask);
            srvl_vcap_key_set(data, IS2_HKO_IP4_TCP_UDP_L4_RNG, IS2_HKL_IP4_TCP_UDP_L4_RNG, range, range);
            srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_SPORT_EQ_DPORT, sport_eq_dport);
            
            if (ptp->enable) {
                srvl_vcap_key_set(data, IS2_HKO_IP4_TCP_UDP_SEQUENCE_EQ0, 19, ptp_vm[0], ptp_vm[1]);
            } else {
                srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_SEQUENCE_EQ0, seq_zero);
                srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_L4_FIN, tcp_fin);
                srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_L4_SYN, tcp_syn);
                srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_L4_RST, tcp_rst);
                srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_L4_PSH, tcp_psh);
                srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_L4_ACK, tcp_ack);
                srvl_vcap_key_bit_set(data, IS2_HKO_IP4_TCP_UDP_L4_URG, tcp_urg);
                srvl_vcap_key_set(data, IS2_HKO_IP4_TCP_UDP_L4_1588_DOM, IS2_HKL_IP4_TCP_UDP_L4_1588_DOM, 0, 0);
                srvl_vcap_key_set(data, IS2_HKO_IP4_TCP_UDP_L4_1588_VER, IS2_HKL_IP4_TCP_UDP_L4_1588_VER, 0, 0);
            }
        } else if (proto->mask == 0) {
            /* Any IP protocol match */
            type = IS2_TYPE_IP_UDP_TCP;
            type_mask = IS2_TYPE_MASK_IP_ANY;
            srvl_vcap_key_set(data, IS2_HKO_IP4_OTHER_L3_PROTO, 32, 0, 0);
            srvl_vcap_key_set(data, IS2_HKO_IP4_OTHER_L3_PROTO + 32, 32, 0, 0);
        } else {
            /* Non-UDP/TCP protocol match */
            type = IS2_TYPE_IP_OTHER;
            srvl_vcap_key_u8_set(data, IS2_HKO_IP4_OTHER_L3_PROTO, proto);
            for (i = 0; i < 7; i++) {
                val[i] = (i < 6 ? ip_data->value[i] : 0);
                msk[i] = (i < 6 ? ip_data->mask[i] : 0);
            }
            srvl_vcap_key_bytes_set(data, IS2_HKO_IP4_OTHER_L3_PAYLOAD, val, msk, 7);
        }
        break;
    default:
        VTSS_EG(VTSS_TRACE_GROUP_SECURITY, "illegal type: %d", ace->type);
        return VTSS_RC_ERROR;
    }
    
    if (smac != NULL && dmac != NULL) {
        srvl_vcap_key_u48_set(data, IS2_HKO_L2_DMAC, dmac);
        srvl_vcap_key_u48_set(data, IS2_HKO_L2_SMAC, smac);
    }

    /* Setup entry type */
    srvl_vcap_key_set(data, IS2_HKO_TYPE, IS2_HKL_TYPE, type, type_mask);

    /* Setup action */
    VTSS_RC(srvl_is2_action_set(vtss_state, data, &ace->action, 0, counter));

    /* Set TCAM data */
    return srvl_vcap_entry_set(vtss_state, tcam, idx, data);
}

static vtss_rc srvl_is2_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    VTSS_IG(VTSS_TRACE_GROUP_SECURITY, "enter");

    return srvl_vcap_entry_del(vtss_state, VTSS_TCAM_IS2, idx);
}

static vtss_rc srvl_is2_entry_move(vtss_state_t *vtss_state,
                                   vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    VTSS_IG(VTSS_TRACE_GROUP_SECURITY, "enter");

    return srvl_vcap_entry_move(vtss_state, VTSS_TCAM_IS2, idx, count, up);
}

static vtss_rc srvl_is2_entry_update(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, vtss_is2_data_t *is2)
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_IS2];
    srvl_tcam_data_t   tcam_data, *data = &tcam_data;
    vtss_port_no_t     port_no;
    BOOL               member[VTSS_PORTS];
    u32                mask;

    VTSS_I("row: %u, col: %u", idx->row, idx->col);
    VTSS_RC(srvl_vcap_entry_data_get(vtss_state, tcam, idx, data));
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        member[port_no] = (VTSS_PORT_BF_GET(is2->action.member, port_no) &&
                           vtss_state->l2.tx_forward_aggr[port_no]);
    }
    mask = vtss_srvl_port_mask(vtss_state, member);
    srvl_vcap_action_set(data, IS2_AO_PORT_MASK, IS2_AL_PORT_MASK, mask);
    VTSS_RC(srvl_vcap_entry_set(vtss_state, tcam, idx, data));
    return VTSS_RC_OK;
}

static void srvl_debug_is2_base(srvl_debug_info_t *info, u32 offset)
{
    vtss_debug_printf_t pr = info->pr;
    u32                 old_offset = info->data.key_offset;

    info->data.key_offset += (offset - IS2_FKO_PAG); /* Adjust offset */
    srvl_debug_bits(info, "pag", IS2_FKO_PAG, IS2_FKL_PAG);
    srvl_debug_bits(info, "igr_port_mask", IS2_FKO_IGR_PORT_MASK, IS2_FKL_IGR_PORT_MASK);
    pr("\n");
    srvl_debug_bit(info, "isdx_neq0", IS2_FKO_SERVICE_FRM);
    srvl_debug_bit(info, "host", IS2_FKO_HOST_MATCH);
    srvl_debug_bit(info, "l2_mc", IS2_FKO_L2_MC);
    srvl_debug_bit(info, "l2_bc", IS2_FKO_L2_BC);
    pr("\n");
    srvl_debug_bit(info, "tagged", IS2_FKO_VLAN_TAGGED);
    srvl_debug_u12(info, "vid", IS2_FKO_VID);
    srvl_debug_bit(info, "dei", IS2_FKO_DEI);
    srvl_debug_u3(info, "pcp", IS2_FKO_PCP);
    pr("\n");
    info->data.key_offset = old_offset; /* Restore offset */
}

static void srvl_debug_is2_l3(srvl_debug_info_t *info, u32 offset)
{
    u32 old_offset = info->data.key_offset;

    info->data.key_offset += (offset - IS2_HKO_IP4_OTHER_L3_PROTO); /* Adjust offset */
    srvl_debug_u8(info, "proto", IS2_HKO_IP4_OTHER_L3_PROTO);
    info->pr("\n");
    srvl_debug_bytes(info, "l3_payload",
                     IS2_HKO_IP4_OTHER_L3_PAYLOAD, IS2_HKL_IP4_OTHER_L3_PAYLOAD);
    info->data.key_offset = old_offset; /* Restore offset */
}

static void srvl_debug_is2_l4(srvl_debug_info_t *info, u32 offset)
{
    vtss_debug_printf_t pr = info->pr;
    u32                 old_offset = info->data.key_offset;

    info->data.key_offset += (offset - IS2_HKO_IP4_TCP_UDP_TCP); /* Adjust offset */
    srvl_debug_u16(info, "l4_dport", IS2_HKO_IP4_TCP_UDP_L4_DPORT);
    srvl_debug_u16(info, "l4_sport", IS2_HKO_IP4_TCP_UDP_L4_SPORT);
    srvl_debug_u8(info, "l4_rng", IS2_HKO_IP4_TCP_UDP_L4_RNG);
    pr("\n");
    srvl_debug_bit(info, "tcp", IS2_HKO_IP4_TCP_UDP_TCP);
    srvl_debug_u8(info, "1588_dom", IS2_HKO_IP4_TCP_UDP_L4_1588_DOM);
    srvl_debug_bits(info, "1588_ver", 
                    IS2_HKO_IP4_TCP_UDP_L4_1588_VER, IS2_HKL_IP4_TCP_UDP_L4_1588_VER);
    srvl_debug_bit(info, "sp_eq_dp", IS2_HKO_IP4_TCP_UDP_SPORT_EQ_DPORT);
    pr("\n");
    srvl_debug_bit(info, "seq_eq0", IS2_HKO_IP4_TCP_UDP_SEQUENCE_EQ0);
    srvl_debug_bit(info, "fin", IS2_HKO_IP4_TCP_UDP_L4_FIN);
    srvl_debug_bit(info, "syn", IS2_HKO_IP4_TCP_UDP_L4_SYN);
    srvl_debug_bit(info, "rst", IS2_HKO_IP4_TCP_UDP_L4_RST);
    srvl_debug_bit(info, "psh", IS2_HKO_IP4_TCP_UDP_L4_PSH);
    srvl_debug_bit(info, "ack", IS2_HKO_IP4_TCP_UDP_L4_ACK);
    srvl_debug_bit(info, "urg", IS2_HKO_IP4_TCP_UDP_L4_URG);
    pr("\n");
    info->data.key_offset = old_offset; /* Restore offset */
}

static vtss_rc srvl_debug_is2(srvl_debug_info_t *info)
{
    vtss_debug_printf_t pr = info->pr;
    srvl_tcam_data_t    *data = &info->data;
    u32                 type, x;
    
    if (info->is_action) {
        /* Print action */
        if (data->type == IS2_ACTION_TYPE_SMAC_SIP) {
            srvl_debug_action(info, "cpu", IS2_AO_SMAC_SIP_CPU_COPY_ENA, 
                              IS2_AO_SMAC_SIP_CPU_QU_NUM, IS2_AL_SMAC_SIP_CPU_QU_NUM);
            srvl_debug_action(info, "fwd_kill", IS2_AO_SMAC_SIP_FWD_KILL_ENA, 0, 0);
            srvl_debug_action(info, "host", IS2_AO_SMAC_SIP_HOST_MATCH, 0, 0);
        } else {
            /* IS2_ACTION_TYPE_NORMAL */
            x = srvl_act_bs_get(info, IS2_AO_MASK_MODE, IS2_AL_MASK_MODE);
            pr("mode:%u (%s) ",
               x,
               x == IS2_ACT_MASK_MODE_NONE ? "none" :
               x == IS2_ACT_MASK_MODE_FILTER ? "filter" :
               x == IS2_ACT_MASK_MODE_POLICY ? "policy" :
               x == IS2_ACT_MASK_MODE_REDIR ? "redir" : "?");
            srvl_debug_bits(info, "mask", IS2_AO_PORT_MASK, IS2_AL_PORT_MASK);
            srvl_debug_action(info, "hit", IS2_AO_HIT_ME_ONCE, 0, 0);
            srvl_debug_action(info, "cpu", IS2_AO_CPU_COPY_ENA, 
                              IS2_AO_CPU_QU_NUM, IS2_AL_CPU_QU_NUM);
            srvl_debug_action(info, "mir", IS2_AO_MIRROR_ENA, 0, 0);
            srvl_debug_action(info, "lrn", IS2_AO_LRN_DIS, 0, 0);
            pr("\n");
            srvl_debug_action(info, "pol", IS2_AO_POLICE_ENA, 
                              IS2_AO_POLICE_IDX, IS2_AL_POLICE_IDX);
            srvl_debug_action(info, "pol_vcap", IS2_AO_POLICE_VCAP_ONLY, 0, 0);
            x = srvl_act_bs_get(info, IS2_AO_REW_OP, 4); /* REW_OP[3:0] */
            pr("rew_op:%u (%s) ", 
               x,
               x == IS2_ACT_REW_OP_NONE ? "none" :
               (x & 0x3) == IS2_ACT_REW_OP_PTP_ONE ? "ptp_one" :
               x == IS2_ACT_REW_OP_PTP_TWO ? "ptp_two" :
               x == IS2_ACT_REW_OP_PTP_ORG ? "ptp_org" :
               x == IS2_ACT_REW_OP_SPECIAL ? "special" : "?");
            srvl_debug_bits(info, "rew_sub", IS2_AO_REW_OP + 3, 6); /* REW_OP[8:3] */
            srvl_debug_action(info, "isdx", IS2_AO_ISDX_ENA, 0, 0);
            srvl_debug_action(info, "lm_dis", IS2_AO_LM_CNT_DIS, 0, 0);
            srvl_debug_fld(info, "acl_id", IS2_AO_ACL_ID, IS2_AL_ACL_ID);
        }
        pr("cnt:%u ", data->cnt);
        return VTSS_RC_OK;
    }
        
    /* Print entry */
    if (data->tg_sw == VCAP_TG_QUARTER) {
        /* SMAC_SIP4 */
        srvl_debug_bits(info, "igr_port", IS2_QKO_IGR_PORT, IS2_QKL_IGR_PORT);
        srvl_debug_u32(info, "l3_ip4_sip", IS2_QKO_L3_IP4_SIP);
        srvl_debug_u48(info, "l2_smac", IS2_QKO_L2_SMAC);
        return VTSS_RC_OK;
    } else if (data->tg_sw == VCAP_TG_FULL) {
        /* Common format for full keys */
        srvl_debug_bits(info, "type", IS2_FKO_TYPE, IS2_FKL_TYPE);
        type = srvl_entry_bs_get(info, IS2_FKO_TYPE, IS2_FKL_TYPE);
        pr("(%s) ",
           type == IS2_TYPE_IP6_TCP_UDP ? "ip6_tcp_udp" :
           type == IS2_TYPE_IP6_OTHER ? "ip6_other" :
           type == IS2_TYPE_CUSTOM ? "custom" : "?");
        srvl_debug_bit(info, "first", IS2_FKO_FIRST);
        srvl_debug_is2_base(info, IS2_FKO_PAG);
        pr("\n");

        /* Specific format for full keys */
        switch (type) {
        case IS2_TYPE_IP6_TCP_UDP:
        case IS2_TYPE_IP6_OTHER:
            /* Common format for IP6 keys */
            srvl_debug_bit(info, "ttl",  IS2_FKO_L3_TTL_GT0);
            srvl_debug_u8(info, "l3_tos", IS2_FKO_L3_TOS);
            srvl_debug_bit(info, "dip_eq_sip", IS2_FKO_DIP_EQ_SIP);
            pr("\n");
            srvl_debug_u128(info, "l3_ip6_dip", IS2_FKO_L3_IP6_DIP);
            srvl_debug_u128(info, "l3_ip6_sip", IS2_FKO_L3_IP6_SIP);

            if (type == IS2_TYPE_IP6_TCP_UDP) {
                srvl_debug_is2_l4(info, IS2_FKO_IP6_TCP_UDP_TCP);
            } else {
                srvl_debug_is2_l3(info, IS2_FKO_IP6_OTHER_L3_PROTO);
            }
            break;
        case IS2_TYPE_CUSTOM:
            srvl_debug_bit(info, "custom_type", IS2_FKO_CUSTOM_CUSTOM_TYPE);
            srvl_debug_u128(info, "data", IS2_FKO_CUSTOM_CUSTOM); /* 128 bits for now */
            break;
        default:
            break;
        }
        return VTSS_RC_OK;
    }

    /* VCAP_TG_HALF */
    type = srvl_entry_bs_get(info, IS2_HKO_TYPE, IS2_HKL_TYPE);
    srvl_debug_bits(info, "type", IS2_HKO_TYPE, IS2_HKL_TYPE);
    pr("(%s) ", 
       vtss_bs_get(data->mask, IS2_HKO_TYPE + data->key_offset, IS2_HKL_TYPE) == 0 ? "any" :
       type == IS2_TYPE_ETYPE ? "etype" :
       type == IS2_TYPE_LLC ? "llc" :
       type == IS2_TYPE_SNAP ? "snap" :
       type == IS2_TYPE_ARP ? "arp" :
       type == IS2_TYPE_IP_UDP_TCP ? "udp_tcp" :
       type == IS2_TYPE_IP_OTHER ? "ip_other" :
       type == IS2_TYPE_IPV6 ? "ipv6" :
       type == IS2_TYPE_OAM ? "oam" : 
       type == IS2_TYPE_SMAC_SIP6 ? "smac_sip6" : "?");
    
    if (type == IS2_TYPE_SMAC_SIP6) {
        srvl_debug_bits(info, "igr_port", IS2_HKO_SMAC_SIP6_IGR_PORT, IS2_HKL_SMAC_SIP6_IGR_PORT);
        pr("\n");
        srvl_debug_u48(info, "l2_smac", IS2_HKO_SMAC_SIP6_L2_SMAC);
        srvl_debug_u128(info, "l3_ip6_sip", IS2_HKO_SMAC_SIP6_L3_IP6_SIP);
        return VTSS_RC_OK;
    }

    /* Common format for half keys */
    srvl_debug_bit(info, "first", IS2_HKO_FIRST);
    srvl_debug_is2_base(info, IS2_HKO_PAG);
    pr("\n");
    
    switch (type) {
    case IS2_TYPE_ETYPE:
    case IS2_TYPE_LLC:
    case IS2_TYPE_SNAP:
    case IS2_TYPE_OAM:
        /* Common format */
        srvl_debug_u48(info, "l2_dmac", IS2_HKO_L2_DMAC);
        srvl_debug_u48(info, "l2_smac", IS2_HKO_L2_SMAC);

        /* Specific format */
        if (type == IS2_TYPE_ETYPE) {
            srvl_debug_u16(info, "etype", IS2_HKO_MAC_ETYPE_ETYPE);
            srvl_debug_bits(info, "l2_payload", 
                            IS2_HKO_MAC_ETYPE_L2_PAYLOAD, IS2_HKL_MAC_ETYPE_L2_PAYLOAD);
        } else if (type == IS2_TYPE_LLC) {
            srvl_debug_bytes(info, "l2_llc", IS2_HKO_MAC_LLC_L2_LLC, IS2_HKL_MAC_LLC_L2_LLC);
        } else if (type == IS2_TYPE_SNAP) {
            srvl_debug_bytes(info, "l2_snap", IS2_HKO_MAC_SNAP_L2_SNAP, IS2_HKL_MAC_SNAP_L2_SNAP);
        } else if (type == IS2_TYPE_OAM) {
            srvl_debug_bits(info, "mel_flags", 
                            IS2_HKO_OAM_OAM_MEL_FLAGS, IS2_HKL_OAM_OAM_MEL_FLAGS);
            srvl_debug_bits(info, "ver", IS2_HKO_OAM_OAM_VER, IS2_HKL_OAM_OAM_VER);
            srvl_debug_u8(info, "opcode", IS2_HKO_OAM_OAM_OPCODE);
            srvl_debug_u8(info, "flags", IS2_HKO_OAM_OAM_FLAGS);
            pr("\n");
            srvl_debug_u16(info, "mepid", IS2_HKO_OAM_OAM_MEPID);
            srvl_debug_bit(info, "ccm_cnts_eq0", IS2_HKO_OAM_OAM_CCM_CNTS_EQ0);
        }
        break;
    case IS2_TYPE_ARP:
        srvl_debug_u48(info, "l2_smac", IS2_HKO_MAC_ARP_L2_SMAC);
        srvl_debug_bit(info, "addr_ok", IS2_HKO_MAC_ARP_ARP_ADDR_SPACE_OK);
        srvl_debug_bit(info, "proto_ok", IS2_HKO_MAC_ARP_ARP_PROTO_SPACE_OK);
        srvl_debug_bit(info, "len_ok", IS2_HKO_MAC_ARP_ARP_LEN_OK);
        pr("\n");
        srvl_debug_bit(info, "t_match", IS2_HKO_MAC_ARP_ARP_TGT_MATCH);
        srvl_debug_bit(info, "s_match", IS2_HKO_MAC_ARP_ARP_SENDER_MATCH);
        srvl_debug_bit(info, "op_unk", IS2_HKO_MAC_ARP_ARP_OPCODE_UNKNOWN);
        srvl_debug_bits(info, "op", IS2_HKO_MAC_ARP_ARP_OPCODE, IS2_HKL_MAC_ARP_ARP_OPCODE);
        srvl_debug_bit(info, "dip_eq_sip", IS2_HKO_MAC_ARP_DIP_EQ_SIP);
        pr("\n");
        srvl_debug_u32(info, "l3_ip4_dip", IS2_HKO_MAC_ARP_L3_IP4_DIP);
        srvl_debug_u32(info, "l3_ip4_sip", IS2_HKO_MAC_ARP_L3_IP4_SIP);
        break;
    case IS2_TYPE_IP_UDP_TCP:
    case IS2_TYPE_IP_OTHER:
        /* Common format for IP keys */
        srvl_debug_bit(info, "ip4", IS2_HKO_IP4);
        srvl_debug_bit(info, "l3_fragment", IS2_HKO_L3_FRAGMENT);
        srvl_debug_bit(info, "l3_fragoffs", IS2_HKO_L3_FRAG_OFS_GT0);
        srvl_debug_bit(info, "l3_options", IS2_HKO_L3_OPTIONS);
        srvl_debug_bit(info, "l3_ttl", IS2_HKO_L3_TTL_GT0);
        pr("\n");
        srvl_debug_u8(info, "l3_tos", IS2_HKO_L3_TOS);
        srvl_debug_bit(info, "dip_eq_sip", IS2_HKO_DIP_EQ_SIP);
        pr("\n");
        srvl_debug_u32(info, "l3_ip4_dip", IS2_HKO_L3_IP4_DIP);
        srvl_debug_u32(info, "l3_ip4_sip", IS2_HKO_L3_IP4_SIP);
        
        /* Specific format */
        if (type == IS2_TYPE_IP_UDP_TCP) {
            srvl_debug_is2_l4(info, IS2_HKO_IP4_TCP_UDP_TCP);
        } else {
            srvl_debug_is2_l3(info, IS2_HKO_IP4_OTHER_L3_PROTO);
        }
        break;
    case IS2_TYPE_IPV6:
        srvl_debug_u8(info, "proto", IS2_HKO_IP6_STD_L3_PROTO);
        srvl_debug_bit(info, "l3_ttl", IS2_HKO_IP6_STD_L3_TTL_GT0);
        pr("\n");
        srvl_debug_u128(info, "l3_ip6_sip", IS2_HKO_IP6_STD_L3_IP6_SIP);
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
    
static vtss_rc srvl_debug_is2_all(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    u32  port;
    BOOL header = 1;

    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        if (vtss_cmn_port2port_no(vtss_state, info, port) == VTSS_PORT_NO_NONE)
            continue;
        if (header)
            vtss_srvl_debug_reg_header(pr, "ANA:PORT");
        header = 0;
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_VCAP_CFG(port), port, "VCAP_CFG");
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_PORT_VCAP_S2_CFG(port), port, "VCAP_S2_CFG");
    }
    if (!header)
        pr("\n");
    return srvl_debug_vcap(vtss_state, VTSS_TCAM_IS2, "IS2", pr, info, srvl_debug_is2);
}

/* ================================================================= *
 *  ES0 functions
 * ================================================================= */

static vtss_rc srvl_es0_entry_get(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, u32 *counter, BOOL clear) 
{
    VTSS_I("enter");
    
    return srvl_vcap_counter_get(vtss_state, VTSS_TCAM_ES0, idx, counter, clear);
}

/* (Selection, value) pair */
typedef struct {
    u32 sel;
    u32 val;
} srvl_es0_sel_t;

/* ES0 tag related fields */
typedef struct {
    u32            tag_sel;
    u32            tpid_sel;
    srvl_es0_sel_t vid;
    srvl_es0_sel_t pcp;
    srvl_es0_sel_t dei;
} srvl_es0_tag_t;

static void srvl_es0_tag_get(vtss_es0_action_t *action, BOOL inner, srvl_es0_tag_t *tag)
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
    tag->tpid_sel = conf->tpid;
    tag->vid.sel = (conf->vid.sel ? 1 : 0);
    tag->vid.val = (conf->vid.sel ? conf->vid.val : 0);
    tag->pcp.sel = (conf->pcp.sel == VTSS_ES0_PCP_CLASS ? ES0_ACT_PCP_SEL_CL_PCP :
                    conf->pcp.sel == VTSS_ES0_PCP_ES0 ? ES0_ACT_PCP_SEL_PCP_ES0 :
                    conf->pcp.sel == VTSS_ES0_PCP_MAPPED ? ES0_ACT_PCP_SEL_MAPPED :
                    ES0_ACT_PCP_SEL_QOS);
    tag->pcp.val = conf->pcp.val;
    tag->dei.sel = (conf->dei.sel == VTSS_ES0_DEI_CLASS ? ES0_ACT_DEI_SEL_CL_DEI :
                    conf->dei.sel == VTSS_ES0_DEI_ES0 ? ES0_ACT_DEI_SEL_DEI_ES0 :
                    conf->dei.sel == VTSS_ES0_DEI_MAPPED ? ES0_ACT_DEI_SEL_MAPPED :
                    ES0_ACT_DEI_SEL_DP);
    tag->dei.val = (conf->dei.val ? 1 : 0);
}

static void srvl_es0_pcp_key_get(vtss_state_t *vtss_state,
                                 vtss_es0_data_t *es0, vtss_vcap_u8_t *pcp_key)
{
    u8 pcp;

    if (es0->flags & VTSS_ES0_FLAG_PCP_MAP) {
        /* Find PCP value mapping to ECE priority */
        for (pcp = 0; pcp < 8; pcp++) {
            if (vtss_state->qos.port_conf[es0->nni].qos_class_map[pcp][0] == es0->prio) {
                pcp_key->value = pcp;
                pcp_key->mask = 0x7;
                break;
            }
        }
    }
}

static vtss_rc srvl_es0_entry_add(vtss_state_t *vtss_state,
                                  vtss_vcap_idx_t *idx, vtss_vcap_data_t *vcap_data, u32 counter)
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_ES0];
    srvl_tcam_data_t   tcam_data, *data = &tcam_data;
    vtss_es0_data_t    *es0 = &vcap_data->u.es0;
    vtss_es0_key_t     *key = &es0->entry->key;
    vtss_es0_action_t  *action = &es0->entry->action;
    u32                port = 0, mask = 0;
    vtss_vcap_u8_t     pcp;
    srvl_es0_tag_t     tag;
    BOOL               key_isdx = (key->type == VTSS_ES0_TYPE_ISDX ? 1 : 0);
    
    /* Check key size */
    if (idx->key_size != VTSS_VCAP_KEY_SIZE_FULL) {
        VTSS_E("unsupported key_size: %s",
                vtss_vcap_key_size2txt(idx->key_size));
        return VTSS_RC_OK;
    }
    
    /* Get TCAM data */
    data->type = 0;
    data->cnt = counter;
    VTSS_RC(srvl_vcap_entry_add(vtss_state, tcam, idx, data));
    
    /* Setup key fields */
    if (key->port_no != VTSS_PORT_NO_NONE) {
        port = VTSS_CHIP_PORT(key->port_no);
        mask = VTSS_BITMASK(ES0_FKL_EGR_PORT);
    }
    srvl_vcap_key_set(data, ES0_FKO_EGR_PORT, ES0_FKL_EGR_PORT, port, mask);
    if (key->rx_port_no == VTSS_PORT_NO_NONE) {
        port = 0;
        mask = 0;
    } else {
        port = VTSS_CHIP_PORT(key->rx_port_no);
        mask = VTSS_BITMASK(ES0_FKL_IGR_PORT);
    }
    srvl_vcap_key_set(data, ES0_FKO_IGR_PORT, ES0_FKL_IGR_PORT, port, mask);
    srvl_vcap_key_bit_set(data, ES0_FKO_SERVICE_FRM, key->isdx_neq0);
    srvl_vcap_key_bit_set(data, ES0_FKO_KEY_ISDX, key_isdx ? VTSS_VCAP_BIT_1 : VTSS_VCAP_BIT_0);
    srvl_vcap_key_bit_set(data, ES0_FKO_L2_MC, VTSS_VCAP_BIT_ANY);
    srvl_vcap_key_bit_set(data, ES0_FKO_L2_BC, VTSS_VCAP_BIT_ANY);
    srvl_vcap_key_set(data, ES0_FKO_VID, ES0_FKL_VID, 
                      key_isdx ? key->data.isdx.isdx : key->data.vid.vid,
                      (!key_isdx && key->vid_any) ? 0 : VTSS_BITMASK(ES0_FKL_VID));
    srvl_vcap_key_bit_set(data, ES0_FKO_DEI, VTSS_VCAP_BIT_ANY);

    /* PCP key, may depend on QoS mapping for NNI */
    pcp = (key_isdx ? key->data.isdx.pcp : key->data.vid.pcp);
    srvl_es0_pcp_key_get(vtss_state, es0, &pcp);
    srvl_vcap_key_set(data, ES0_FKO_PCP, ES0_FKL_PCP, pcp.value, pcp.mask);

    /* Setup action fields - outer tag */
    vtss_cmn_es0_action_get(vtss_state, es0);
    srvl_es0_tag_get(action, 0, &tag);
    srvl_vcap_action_set(data, ES0_AO_PUSH_OUTER_TAG, ES0_AL_PUSH_OUTER_TAG, tag.tag_sel);
    srvl_vcap_action_set(data, ES0_AO_TAG_A_TPID_SEL, ES0_AL_TAG_A_TPID_SEL, tag.tpid_sel);
    srvl_vcap_action_bit_set(data, ES0_AO_TAG_A_VID_SEL, tag.vid.sel);
    srvl_vcap_action_set(data, ES0_AO_TAG_A_PCP_SEL, ES0_AL_TAG_A_PCP_SEL, tag.pcp.sel);
    srvl_vcap_action_set(data, ES0_AO_TAG_A_DEI_SEL, ES0_AL_TAG_A_DEI_SEL, tag.dei.sel);
    srvl_vcap_action_set(data, ES0_AO_VID_A_VAL, ES0_AL_VID_A_VAL, tag.vid.val);
    srvl_vcap_action_set(data, ES0_AO_PCP_A_VAL, ES0_AL_PCP_A_VAL, tag.pcp.val);
    srvl_vcap_action_bit_set(data, ES0_AO_DEI_A_VAL, tag.dei.val);
    
    /* Setup action fields - inner tag */
    srvl_es0_tag_get(action, 1, &tag);
    srvl_vcap_action_bit_set(data, ES0_AO_PUSH_INNER_TAG, tag.tag_sel);
    srvl_vcap_action_set(data, ES0_AO_TAG_B_TPID_SEL, ES0_AL_TAG_B_TPID_SEL, tag.tpid_sel);
    srvl_vcap_action_bit_set(data, ES0_AO_TAG_B_VID_SEL, tag.vid.sel);
    srvl_vcap_action_set(data, ES0_AO_TAG_B_PCP_SEL, ES0_AL_TAG_B_PCP_SEL, tag.pcp.sel);
    srvl_vcap_action_set(data, ES0_AO_TAG_B_DEI_SEL, ES0_AL_TAG_B_DEI_SEL, tag.dei.sel);
    srvl_vcap_action_set(data, ES0_AO_VID_B_VAL, ES0_AL_VID_B_VAL, tag.vid.val);
    srvl_vcap_action_set(data, ES0_AO_PCP_B_VAL, ES0_AL_PCP_B_VAL, tag.pcp.val);
    srvl_vcap_action_bit_set(data, ES0_AO_DEI_B_VAL, tag.dei.val);
    
    srvl_vcap_action_bit_set(data, ES0_AO_OAM_MEP_IDX_VLD, action->mep_idx_enable);
    srvl_vcap_action_set(data, ES0_AO_OAM_MEP_IDX, ES0_AL_OAM_MEP_IDX, action->mep_idx);

    /* Set TCAM data */
    return srvl_vcap_entry_set(vtss_state, tcam, idx, data);
}

static vtss_rc srvl_es0_entry_del(vtss_state_t *vtss_state, vtss_vcap_idx_t *idx)
{
    VTSS_I("enter");
    
    return srvl_vcap_entry_del(vtss_state, VTSS_TCAM_ES0, idx);
}

static vtss_rc srvl_es0_entry_move(vtss_state_t *vtss_state,
                                   vtss_vcap_idx_t *idx, u32 count, BOOL up)
{
    VTSS_I("enter");

    return srvl_vcap_entry_move(vtss_state, VTSS_TCAM_ES0, idx, count, up);
}

/* Update outer tag TPID for ES0 entry if VLAN port type has changed */
static vtss_rc srvl_es0_entry_update(vtss_state_t *vtss_state,
                                     vtss_vcap_idx_t *idx, vtss_es0_data_t *es0) 
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_ES0];
    srvl_tcam_data_t   tcam_data, *data = &tcam_data;
    vtss_es0_action_t  *action = &es0->entry->action;
    srvl_es0_tag_t     tag;
    vtss_vcap_u8_t     pcp;
    
    VTSS_I("row: %u, col: %u, port_no: %u, flags: 0x%x",
            idx->row, idx->col, es0->port_no, es0->flags);
    VTSS_RC(srvl_vcap_entry_data_get(vtss_state, tcam, idx, data));
    srvl_es0_tag_get(action, 0, &tag);
    if (es0->flags & VTSS_ES0_FLAG_OT_UVID) {
        srvl_vcap_action_set(data, ES0_AO_PUSH_OUTER_TAG, ES0_AL_PUSH_OUTER_TAG, tag.tag_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_TPID) {
        srvl_vcap_action_set(data, ES0_AO_TAG_A_TPID_SEL, ES0_AL_TAG_A_TPID_SEL, tag.tpid_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_PCP) {
        srvl_vcap_action_set(data, ES0_AO_TAG_A_PCP_SEL, ES0_AL_TAG_A_PCP_SEL, tag.pcp.sel);
        srvl_vcap_action_set(data, ES0_AO_PCP_A_VAL, ES0_AL_PCP_A_VAL, tag.pcp.val);
    }
    if (es0->flags & VTSS_ES0_FLAG_OT_DEI) {
        srvl_vcap_action_set(data, ES0_AO_TAG_A_DEI_SEL, ES0_AL_TAG_A_DEI_SEL, tag.dei.sel);
        srvl_vcap_action_bit_set(data, ES0_AO_DEI_A_VAL, tag.dei.val);
    }
    srvl_es0_tag_get(action, 1, &tag);
    if (es0->flags & VTSS_ES0_FLAG_IT_UVID) {
        srvl_vcap_action_set(data, ES0_AO_PUSH_INNER_TAG, ES0_AL_PUSH_INNER_TAG, tag.tag_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_TPID) {
        srvl_vcap_action_set(data, ES0_AO_TAG_B_TPID_SEL, ES0_AL_TAG_B_TPID_SEL, tag.tpid_sel);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_PCP) {
        srvl_vcap_action_set(data, ES0_AO_TAG_B_PCP_SEL, ES0_AL_TAG_B_PCP_SEL, tag.pcp.sel);
        srvl_vcap_action_set(data, ES0_AO_PCP_B_VAL, ES0_AL_PCP_B_VAL, tag.pcp.val);
    }
    if (es0->flags & VTSS_ES0_FLAG_IT_DEI) {
        srvl_vcap_action_set(data, ES0_AO_TAG_B_DEI_SEL, ES0_AL_TAG_B_DEI_SEL, tag.dei.sel);
        srvl_vcap_action_bit_set(data, ES0_AO_DEI_B_VAL, tag.dei.val);
    }
    if (es0->flags & VTSS_ES0_FLAG_PCP_MAP) {
        pcp.value = 0;
        pcp.mask = 0;
        srvl_es0_pcp_key_get(vtss_state, es0, &pcp);
        srvl_vcap_key_set(data, ES0_FKO_PCP, ES0_FKL_PCP, pcp.value, pcp.mask);
    }
    VTSS_RC(srvl_vcap_entry_set(vtss_state, tcam, idx, data));

    return VTSS_RC_OK;
}

static vtss_rc srvl_es0_eflow_update(vtss_state_t *vtss_state, const vtss_eflow_id_t flow_id)
{
    const tcam_props_t *tcam = &tcam_info[VTSS_TCAM_ES0];
    srvl_tcam_data_t   tcam_data, *data = &tcam_data;
    vtss_vcap_obj_t    *obj = &vtss_state->vcap.es0.obj;
    vtss_vcap_idx_t    idx;
    vtss_vcap_entry_t  *cur;
    vtss_eflow_entry_t *eflow = vtss_eflow_lookup(vtss_state, flow_id);
    u32                mep_ena = 0, mep_idx = 0;

    if (eflow != NULL && eflow->conf.voe_idx != VTSS_VOE_IDX_NONE) {
        mep_ena = 1;
        mep_idx = eflow->conf.voe_idx;
    }

    VTSS_MEMSET(&idx, 0, sizeof(idx));
    for (cur = obj->used; cur != NULL; cur = cur->next, idx.row++) {
        if (cur->data.u.es0.flow_id == flow_id) {
            /* Update action fields */
            VTSS_RC(srvl_vcap_entry_data_get(vtss_state, tcam, &idx, data));
            srvl_vcap_action_bit_set(data, ES0_AO_OAM_MEP_IDX_VLD, mep_ena);
            srvl_vcap_action_set(data, ES0_AO_OAM_MEP_IDX, ES0_AL_OAM_MEP_IDX, mep_idx);
            VTSS_RC(srvl_vcap_entry_set(vtss_state, tcam, &idx, data));
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_es0(srvl_debug_info_t *info)
{
    vtss_debug_printf_t pr = info->pr;
    u32                 i, x, offs;
    char                buf[20], buf_1[16];
    
    if (info->is_action) {
        /* Print action */
        x = srvl_act_bs_get(info, ES0_AO_PUSH_OUTER_TAG, ES0_AL_PUSH_OUTER_TAG);
        pr("outer:%u (%s) ", x,
           x == ES0_ACT_PUSH_OT_PORT_ENA ? "port_ena" :
           x == ES0_ACT_PUSH_OT_ES0 ? "es0" :
           x == ES0_ACT_PUSH_OT_PORT ? "port" :
           x == ES0_ACT_PUSH_OT_NONE ? "none" : "?");
        srvl_debug_bit(info, "inner", ES0_AO_PUSH_INNER_TAG);
        pr("\n");
        
        /* Loop over TAG_A/TAG_B fields */
        for (i = 0; i < 2; i++) {
            VTSS_SPRINTF(buf, "_%s", i ? "b" : "a");
            offs = (i ? (ES0_AO_TAG_B_TPID_SEL - ES0_AO_TAG_A_TPID_SEL) : 0);
            x = srvl_act_bs_get(info, ES0_AO_TAG_A_TPID_SEL + offs, ES0_AL_TAG_A_TPID_SEL);
            pr("tpid%s:%u (%s) ", buf, x,
               x == TAG_TPID_CFG_0x8100 ? "c" :
               x == TAG_TPID_CFG_0x88A8 ? "s" :
               x == TAG_TPID_CFG_PTPID ? "port" :
               x == TAG_TPID_CFG_PTPID_NC ? "port-c" : "?");

            x = srvl_act_bs_get(info, ES0_AO_TAG_A_VID_SEL + offs, ES0_AL_TAG_A_VID_SEL);
            pr("vid%s:%u (%svid%s_val) ", buf, x, x ? "" : "cl_vid+", buf);

            x = srvl_act_bs_get(info, ES0_AO_TAG_A_PCP_SEL + offs, ES0_AL_TAG_A_PCP_SEL);
            pr("pcp%s:%u (%s) ", buf, x,
               x == ES0_ACT_PCP_SEL_CL_PCP ? "cl_pcp" :
               x == ES0_ACT_PCP_SEL_PCP_ES0 ? "pcp_es0" :
               x == ES0_ACT_PCP_SEL_MAPPED ? "mapped" :
               x == ES0_ACT_PCP_SEL_QOS ? "qos" : "?");

            x = srvl_act_bs_get(info, ES0_AO_TAG_A_DEI_SEL + offs, ES0_AL_TAG_A_DEI_SEL);
            pr("dei%s:%u (%s)\n", buf, x,
               x == ES0_ACT_DEI_SEL_CL_DEI ? "cl_dei" :
               x == ES0_ACT_DEI_SEL_DEI_ES0 ? "dei_es0" :
               x == ES0_ACT_DEI_SEL_MAPPED ? "mapped" :
               x == ES0_ACT_DEI_SEL_DP ? "dp" : "?");
            
            offs = (i ? (ES0_AO_VID_B_VAL - ES0_AO_VID_A_VAL) : 0);
            VTSS_SPRINTF(buf_1, "_%s_val", i ? "b" : "a");
            VTSS_SPRINTF(buf, "vid%s", buf_1);
            srvl_debug_fld(info, buf, ES0_AO_VID_A_VAL + offs, ES0_AL_VID_A_VAL);
            VTSS_SPRINTF(buf, "pcp%s", buf_1);
            srvl_debug_fld(info, buf, ES0_AO_PCP_A_VAL + offs, ES0_AL_PCP_A_VAL);
            VTSS_SPRINTF(buf, "dei%s", buf_1);
            srvl_debug_fld(info, buf, ES0_AO_DEI_A_VAL + offs, ES0_AL_DEI_A_VAL);
            pr("\n");
        }
        pr("hit:%u ", info->data.cnt);
        return VTSS_RC_OK;
    }

    /* Print entry */
    srvl_debug_bits(info, "egr_port", ES0_FKO_EGR_PORT, ES0_FKL_EGR_PORT);
    srvl_debug_bits(info, "igr_port", ES0_FKO_IGR_PORT, ES0_FKL_IGR_PORT);
    pr("\n");
    srvl_debug_bit(info, "service_frm", ES0_FKO_SERVICE_FRM);
    srvl_debug_bit(info, "key_isdx", ES0_FKO_KEY_ISDX);
    srvl_debug_bit(info, "l2_mc", ES0_FKO_L2_MC);
    srvl_debug_bit(info, "l2_bc", ES0_FKO_L2_BC);
    srvl_debug_u12(info, "vid", ES0_FKO_VID);
    srvl_debug_bit(info, "dei", ES0_FKO_DEI);
    srvl_debug_u3(info, "pcp", ES0_FKO_PCP);
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_debug_es0_all(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    u32  port;
    BOOL header = 1;

    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        if (vtss_cmn_port2port_no(vtss_state, info, port) == VTSS_PORT_NO_NONE)
            continue;
        if (header)
            vtss_srvl_debug_reg_header(pr, "REW:PORT");
        header = 0;
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_REW_PORT_PORT_CFG(port), port, "PORT_CFG");
    }
    if (!header)
        pr("\n");
    return srvl_debug_vcap(vtss_state, VTSS_TCAM_ES0, "ES0", pr, info, srvl_debug_es0);
}

/* ================================================================= *
 *  ACL
 * ================================================================= */

static vtss_rc srvl_acl_policer_set(vtss_state_t *vtss_state,
                                    const vtss_acl_policer_no_t policer_no)
{
    vtss_acl_policer_conf_t  *conf = &vtss_state->vcap.acl_policer_conf[policer_no];
    vtss_policer_conf_t      pol_conf;
    
    VTSS_MEMSET(&pol_conf, 0, sizeof(pol_conf));
    if (conf->bit_rate_enable) {
        pol_conf.eir = conf->bit_rate;
        pol_conf.ebs = 1; /* Minimum burst size */
    } else {
        pol_conf.frame_rate = 1;
        pol_conf.eir = conf->rate;
    }

    return vtss_srvl_qos_policer_conf_set(vtss_state, policer_no + SRVL_POLICER_ACL, &pol_conf);
}

static vtss_rc srvl_acl_port_conf_set(vtss_state_t *vtss_state,
                                      const vtss_port_no_t port_no)
{
    const tcam_props_t   *tcam = &tcam_info[VTSS_TCAM_IS2];
    srvl_tcam_data_t     data;
    vtss_acl_port_conf_t *conf = &vtss_state->vcap.acl_port_conf[port_no];
    u32                  ipv6, lookup = 0x1, port = VTSS_CHIP_PORT(port_no);
    u32                  enable = (conf->policy_no == VTSS_ACL_POLICY_NO_NONE ? 0 : 1);
    vtss_rc              rc;

    VTSS_I("port_no: %u, port: %u", port_no, port);

    /* Enable/disable S2 and set default PAG */
    ipv6 = (conf->key.ipv6 == VTSS_ACL_KEY_ETYPE ? 3 : conf->key.ipv6 == VTSS_ACL_KEY_EXT ? 0 : 2);
    SRVL_WRM(VTSS_ANA_PORT_VCAP_S2_CFG(port),
             (enable ? VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_ENA : 0) |
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_ARP_DIS(conf->key.arp == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS(conf->key.ipv4 == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_IP_OTHER_DIS(conf->key.ipv4 == VTSS_ACL_KEY_ETYPE ? lookup : 0) |
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_IP6_CFG(ipv6),
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_ENA |
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_ARP_DIS(lookup) |
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS(lookup) |
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_IP_OTHER_DIS(lookup) |
             VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_IP6_CFG(3));

    SRVL_WRM(VTSS_ANA_PORT_VCAP_CFG(port), 
             VTSS_F_ANA_PORT_VCAP_CFG_PAG_VAL(enable ? (conf->policy_no & 0x3f) : 0),
             VTSS_M_ANA_PORT_VCAP_CFG_PAG_VAL);
    
    /* Set action */
    VTSS_MEMSET(&data, 0, sizeof(data));
    data.action_offset = tcam->action_type_width;
    VTSS_RC(srvl_is2_action_set(vtss_state, &data, &conf->action, 0, 0));
    VTSS_RC(srvl_vcap_action2cache(vtss_state, tcam, &data));
    rc = srvl_vcap_port_cmd(vtss_state, tcam, port, VTSS_TCAM_CMD_WRITE, VTSS_TCAM_SEL_ACTION);
#ifdef VTSS_FEATURE_MPLS
    (void) vtss_srvl_mpls_vprofile_pw_port_sync(vtss_state, port_no);
#endif
    return rc;
}

static vtss_rc srvl_acl_port_counter_get(vtss_state_t *vtss_state,
                                         const vtss_port_no_t    port_no,
                                         vtss_acl_port_counter_t *const counter)
{
    return srvl_vcap_port_get(vtss_state, VTSS_TCAM_IS2, VTSS_CHIP_PORT(port_no), counter, 0);
}

static vtss_rc srvl_acl_port_counter_clear(vtss_state_t *vtss_state,
                                           const vtss_port_no_t port_no)
{
    u32 counter;
    
    return srvl_vcap_port_get(vtss_state, VTSS_TCAM_IS2, VTSS_CHIP_PORT(port_no), &counter, 1);
}

/* Default SMAC_SIP4 rule IDs */
#define SRVL_VCAP_ID_SMAC_SIP4_DEF 0x100000000
#define SRVL_VCAP_ID_SMAC_SIP6_DEF 0x200000000

static vtss_rc srvl_ace_add(vtss_state_t *vtss_state,
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

    /* Check the simple things */
    VTSS_RC(vtss_cmn_ace_add(vtss_state, ace_id, ace));

    if (ace->type == VTSS_ACE_TYPE_IPV6 && ace->type_ext) {
        /* Encode as IPv6 is full rule */
        key_size = VTSS_VCAP_KEY_SIZE_FULL;
    }

    /* Check that half entry can be added */
    VTSS_MEMSET(&chg, 0, sizeof(chg));
    chg.add_key[key_size] = 1;
    if (vtss_vcap_lookup(vtss_state, obj, user, ace->id, &data, NULL) == VTSS_RC_OK) {
        chg.del_key[data.key_size] = 1;
        
        /* Free any old range checkers */
        VTSS_RC(vtss_vcap_range_free(&range_new, is2->srange));
        VTSS_RC(vtss_vcap_range_free(&range_new, is2->drange));
        
        /* Lookup SIP/SMAC rule */
        if (vtss_vcap_lookup(vtss_state, obj, VTSS_IS2_USER_ACL_SIP, ace->id,
                             NULL, NULL) == VTSS_RC_OK) {
            sip_smac_old = 1;
            chg.del_key[VTSS_VCAP_KEY_SIZE_QUARTER] = 1;
        }
    }
    
    if (ace->type == VTSS_ACE_TYPE_IPV4) {
        if (ace->frame.ipv4.sip_smac.enable) {
            /* SMAC_SIP4 rule needed */
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
        /* Allocate new range checkers */
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->srange, sport, 1));
        VTSS_RC(vtss_vcap_udp_tcp_range_alloc(&range_new, &is2->drange, dport, 0));
    }

    /* Commit range checkers */
    VTSS_RC(vtss_vcap_range_commit(vtss_state, &range_new));

    /* Add main entry */
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

    /* Add/delete SIP/SMAC entry */
    user = VTSS_IS2_USER_ACL_SIP;
    if (sip_smac_new) {
        data.key_size = VTSS_VCAP_KEY_SIZE_QUARTER;
        VTSS_RC(vtss_vcap_add(vtss_state, obj, user, ace->id, SRVL_VCAP_ID_SMAC_SIP4_DEF, &data, 0));
    } else if (sip_smac_old) {
        VTSS_RC(vtss_vcap_del(vtss_state, obj, user, ace->id));
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_ace_del(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    /* Delete main entry */
    VTSS_RC(vtss_cmn_ace_del(vtss_state, ace_id));

    /* Delete SIP/SMAC entry */
    VTSS_RC(vtss_vcap_del(vtss_state, &vtss_state->vcap.is2.obj, VTSS_IS2_USER_ACL_SIP, ace_id));
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_range_commit(vtss_state_t *vtss_state)
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
        SRVL_WR(VTSS_ANA_COMMON_VCAP_RNG_TYPE_CFG(i),
                VTSS_F_ANA_COMMON_VCAP_RNG_TYPE_CFG_VCAP_RNG_CFG(type));
        SRVL_WR(VTSS_ANA_COMMON_VCAP_RNG_VAL_CFG(i),
                VTSS_F_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MIN_VAL(entry->min) |
                VTSS_F_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MAX_VAL(entry->max))
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_vcap_port_key_addr_set(vtss_state_t         *vtss_state,
                                           const vtss_port_no_t port_no,
                                           u8                   lookup,
                                           vtss_vcap_key_type_t key_new,
                                           vtss_vcap_key_type_t key_old,
                                           BOOL                 dmac_dip_new,
                                           BOOL                 dmac_dip_old)
{
    u32 ip4, ip6, other, port = VTSS_CHIP_PORT(port_no);
    u32 mask = VTSS_F_ANA_PORT_VCAP_CFG_S1_DMAC_DIP_ENA(1 << lookup);
    
    switch (key_new) {
    case VTSS_VCAP_KEY_TYPE_NORMAL:
        /* S1_NORMAL */
        ip4 = 0;
        ip6 = 0;
        other = 0;
        break;
    case VTSS_VCAP_KEY_TYPE_DOUBLE_TAG:
        /* S1_DBL_VID */
        ip4 = 3;
        ip6 = 5;
        other = 2;
        break;
    case VTSS_VCAP_KEY_TYPE_IP_ADDR:
        /* S1_5TUPLE_IP4/S1_NORMAL */
        ip4 = 2;
        ip6 = 2;
        other = 0;
        break;
    case VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR:
        /* S1_7TUPLE */
        ip4 = 1;
        ip6 = 1;
        other = 1;
        break;
    default:
        VTSS_E("illegal key_type, port_no: %u", port_no);
        return VTSS_RC_ERROR;
    }

    if ((key_new != key_old) || (dmac_dip_new != dmac_dip_old)) {
        vtss_res_t           res;
        u32                  step, add = 0;
        vtss_vcap_entry_t    *cur, *next;
        vtss_vcap_obj_t      *obj = &vtss_state->vcap.is1.obj;
        vtss_vcap_key_size_t key_size_new = vtss_vcap_key_type2size(key_new);
        vtss_vcap_key_size_t key_size_old = vtss_vcap_key_type2size(key_old);

        vtss_cmn_res_init(&res);
        for (step = 1; step < 3; step++) {
        /* Change key size in two steps:
           Step 1: Check if resources are available
           Step 2: Update resources */

            for (cur = obj->used; cur != NULL; cur = cur->next) {
                vtss_is1_entry_t *copy = cur->copy;

                if (copy == NULL) {
                    VTSS_E("VCAP %s: No saved copy", obj->name);
                    return VTSS_RC_ERROR;
                }
                if ((cur->data.u.is1.lookup != lookup) ||
                    (vtss_cmn_first_port_no_get(vtss_state, copy->key.port_list) != port_no)) {
                    /* Skip if lookup differs or not first port in port list */
                    continue;
                }
                if (step == 1) {
                    /* Update ressource information */
                    add = 1;
                    res.is1.add_key[key_size_new]++;
                    res.is1.del_key[key_size_old]++;
                } else { /* Step 2 */
                    /* Make local copies before modifying anything */
                    vtss_vcap_entry_t vcap_entry = *cur;
                    vtss_is1_entry_t  is1_entry = *copy;

                    vcap_entry.data.u.is1.entry = &is1_entry;
                    vcap_entry.data.key_size = key_size_new;
                    is1_entry.key.key_type = key_new;

                    /* Update IS1 entry */
                    next = cur->next;
                    VTSS_RC(vtss_vcap_add(vtss_state, obj, cur->user, cur->id,
                                          next && next->user == cur->user ? next->id : VTSS_VCAP_ID_LAST,
                                          &vcap_entry.data, 0));
                }
            }

            if (step == 1 && add) {
                /* Check if resources are available.
                   The resource change operation implemented above does not delete old rules
                   before adding new rules, so we need an extra row to be able to do the update. */
                res.is1.add++;
                VTSS_RC(vtss_cmn_res_check(vtss_state, &res));

                /* Even if the total resource consumption goes down, we need that extra row */
                vtss_cmn_res_init(&res);
                res.is1.add++;
                VTSS_RC(vtss_cmn_res_check(vtss_state, &res));
            }
        }
    }

    /* Setup port key */
    SRVL_WR(VTSS_ANA_PORT_VCAP_S1_KEY_CFG(port, lookup), 
            VTSS_F_ANA_PORT_VCAP_S1_KEY_CFG_S1_KEY_IP6_CFG(ip6) |
            VTSS_F_ANA_PORT_VCAP_S1_KEY_CFG_S1_KEY_IP4_CFG(ip4) |
            VTSS_F_ANA_PORT_VCAP_S1_KEY_CFG_S1_KEY_OTHER_CFG(other));

    /* Select between SMAC/SIP or DMAC/DIP in the IS1 lookup */
    SRVL_WRM(VTSS_ANA_PORT_VCAP_CFG(port), dmac_dip_new ? mask : 0, mask);

#ifdef VTSS_FEATURE_MPLS
    (void) vtss_srvl_mpls_vprofile_pw_port_sync(vtss_state, port_no);
#endif

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_vcap_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_vcl_port_conf_t *conf = &vtss_state->l2.vcl_port_conf[port_no];
    BOOL                 dmac_dip_new = conf->dmac_dip;
    vtss_vcap_key_type_t key_old = vtss_state->l2.vcl_port_conf_old.key_type;
    vtss_vcap_key_type_t key_new = conf->key_type;

    /* Setup first IS1 lookup */
    return vtss_srvl_vcap_port_key_addr_set(vtss_state, port_no, 0, key_new, key_old, dmac_dip_new);
}

vtss_rc vtss_srvl_vcap_port_key_addr_set(vtss_state_t         *vtss_state,
                                         const vtss_port_no_t port_no,
                                         u8                   lookup,
                                         vtss_vcap_key_type_t key_new,
                                         vtss_vcap_key_type_t key_old,
                                         BOOL                 dmac_dip_new)
{
    vtss_rc rc;
    BOOL    dmac_dip_old = vtss_state->vcap.dmac_dip_conf[port_no].dmac_dip[lookup];

    VTSS_I("port_no: %u, lookup: %u, key_new: %u, key_old: %u, dmac_dip_new: %d, dmac_dip_old: %d",
           port_no, lookup, key_new, key_old, dmac_dip_new, dmac_dip_old);

    if (lookup > 2) {
        VTSS_E("illegal lookup: %u, port_no: %u", lookup, port_no);
        return VTSS_RC_ERROR;
    }

    vtss_state->vcap.dmac_dip_conf[port_no].dmac_dip[lookup] = dmac_dip_new;
    rc = srvl_vcap_port_key_addr_set(vtss_state,
                                     port_no,
                                     lookup,
                                     key_new,
                                     key_old,
                                     dmac_dip_new,
                                     dmac_dip_old);

    if (rc != VTSS_RC_OK) {
        vtss_state->vcap.dmac_dip_conf[port_no].dmac_dip[lookup] = dmac_dip_old; /* Restore old configuration */
    }
    return rc;
}


/* - Debug print --------------------------------------------------- */

vtss_rc vtss_srvl_debug_range_checkers(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       const vtss_debug_info_t   *const info)
{
    u32 i;
    
    vtss_srvl_debug_reg_header(pr, "Range Checkers");
    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_COMMON_VCAP_RNG_TYPE_CFG(i), i, "RNG_TYPE_CFG");
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_ANA_COMMON_VCAP_RNG_VAL_CFG(i), i, "RNG_VAL_CFG");
    }
    pr("\n");
    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_acl(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_srvl_debug_range_checkers(vtss_state, pr, info));
    return srvl_debug_is2_all(vtss_state, pr, info);
}

vtss_rc vtss_srvl_vcap_debug_print(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_ACL, srvl_debug_acl, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc srvl_vcap_init(vtss_state_t *vtss_state)
{
    u32              i, port, value;
    vtss_vcap_obj_t  *obj = &vtss_state->vcap.is2.obj;
    vtss_vcap_user_t user = VTSS_IS2_USER_ACL_SIP;
    vtss_vcap_data_t data;
    vtss_is2_entry_t entry;
    
    if (!vtss_state->warm_start_cur) {
        /* Initialize TCAMs */
#if defined(VTSS_FEATURE_IS0)
        VTSS_RC(srvl_vcap_initialize(vtss_state, VTSS_TCAM_IS0));
#endif /* VTSS_FEATURE_IS0 */
        VTSS_RC(srvl_vcap_initialize(vtss_state, VTSS_TCAM_IS1));
        VTSS_RC(srvl_vcap_initialize(vtss_state, VTSS_TCAM_IS2));
        VTSS_RC(srvl_vcap_initialize(vtss_state, VTSS_TCAM_ES0));
    }

    // IPv6: IP4_TCP_UDP/IP4_OTHER(2) in first lookup, IP6_TCP_UDP/IP6_OTHER(0) in second lookup
    value = (VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_ENA | VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_IP6_CFG(2));
    value |= VTSS_F_ANA_PORT_VCAP_S2_CFG_S2_OAM_DIS(0x3);

    /* Initialize VCAP port setup */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        /* Enable IS1 */
        SRVL_WR(VTSS_ANA_PORT_VCAP_CFG(port), VTSS_F_ANA_PORT_VCAP_CFG_S1_ENA);

        /* Enable IS2, treat IPv6 as IPv4 and treat OAM as ETYPE */
        SRVL_WR(VTSS_ANA_PORT_VCAP_S2_CFG(port), value);

        /* Enable ES0 */
        SRVL_WRM_SET(VTSS_REW_PORT_PORT_CFG(port), VTSS_F_REW_PORT_PORT_CFG_ES0_ENA);
    }

    /* Add default SMAC_SIP rules to avoid default action port 0 counter incrementing */
    vtss_vcap_is2_init(&data, &entry);
    data.key_size = VTSS_VCAP_KEY_SIZE_QUARTER;
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, SRVL_VCAP_ID_SMAC_SIP4_DEF, VTSS_VCAP_ID_LAST, &data, 0));

    data.key_size = VTSS_VCAP_KEY_SIZE_HALF;
    entry.smac_sip6 = 1;
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, SRVL_VCAP_ID_SMAC_SIP6_DEF, VTSS_VCAP_ID_LAST, &data, 0));
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, SRVL_VCAP_ID_SMAC_SIP6_DEF + 1, VTSS_VCAP_ID_LAST, &data, 0));

    // Read range checkers to preserve allocations for warm start
    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        vtss_vcap_range_chk_t *entry = &vtss_state->vcap.range.entry[i];
        SRVL_RD(VTSS_ANA_COMMON_VCAP_RNG_TYPE_CFG(i), &value);
        switch (VTSS_X_ANA_COMMON_VCAP_RNG_TYPE_CFG_VCAP_RNG_CFG(value)) {
        case 1:
            entry->type = VTSS_VCAP_RANGE_TYPE_DPORT;
            break;
        case 2:
            entry->type = VTSS_VCAP_RANGE_TYPE_SPORT;
            break;
        case 3:
            entry->type = VTSS_VCAP_RANGE_TYPE_SDPORT;
            break;
        case 4:
            entry->type = VTSS_VCAP_RANGE_TYPE_VID;
            break;
        case 5:
            entry->type = VTSS_VCAP_RANGE_TYPE_DSCP;
            break;
        default:
            entry->type = VTSS_VCAP_RANGE_TYPE_IDLE;
            break;
        }
        SRVL_RD(VTSS_ANA_COMMON_VCAP_RNG_VAL_CFG(i), &value);
        entry->min = VTSS_X_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MIN_VAL(value);
        entry->max = VTSS_X_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MAX_VAL(value);
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_vcap_state_t *state = &vtss_state->vcap;
#if defined(VTSS_FEATURE_IS0)
    vtss_vcap_obj_t   *is0 = &state->is0.obj;
#endif /* VTSS_FEATURE_IS0 */
    vtss_vcap_obj_t   *is1 = &state->is1.obj;
    vtss_vcap_obj_t   *is2 = &state->is2.obj;
    vtss_vcap_obj_t   *es0 = &state->es0.obj;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
#if defined(VTSS_FEATURE_IS0)
        /* IS0 */
        is0->max_count = SRVL_IS0_CNT;
        is0->max_rule_count = VTSS_SRVL_IS0_CNT;
        is0->entry_get = srvl_is0_entry_get;
        is0->entry_add = srvl_is0_entry_add;
        is0->entry_del = srvl_is0_entry_del;
        is0->entry_move = srvl_is0_entry_move;
#endif /* VTSS_FEATURE_IS0 */
        
        /* IS1 */
        is1->max_count = SRVL_IS1_CNT;
        is1->max_rule_count = VTSS_SRVL_IS1_CNT;
        is1->entry_get = srvl_is1_entry_get;
        is1->entry_add = srvl_is1_entry_add;
        is1->entry_del = srvl_is1_entry_del;
        is1->entry_move = srvl_is1_entry_move;
        
        /* IS2 */
        is2->max_count = SRVL_IS2_CNT;
        is2->max_rule_count = VTSS_SRVL_IS2_CNT;
        is2->entry_get = srvl_is2_entry_get;
        is2->entry_add = srvl_is2_entry_add;
        is2->entry_del = srvl_is2_entry_del;
        is2->entry_move = srvl_is2_entry_move;
        state->is2_entry_update = srvl_is2_entry_update;
        
        /* ES0 */
        es0->max_count = SRVL_ES0_CNT;
        es0->max_rule_count = VTSS_SRVL_ES0_CNT;
        es0->entry_get = srvl_es0_entry_get;
        es0->entry_add = srvl_es0_entry_add;
        es0->entry_del = srvl_es0_entry_del;
        es0->entry_move = srvl_es0_entry_move;
        state->es0_entry_update = srvl_es0_entry_update;
        state->es0_eflow_update = srvl_es0_eflow_update;
        
        /* ACL */
        state->acl_policer_set = srvl_acl_policer_set;
        state->acl_port_set = srvl_acl_port_conf_set;
        state->acl_port_counter_get = srvl_acl_port_counter_get;
        state->acl_port_counter_clear = srvl_acl_port_counter_clear;
        state->acl_ace_add = srvl_ace_add;
        state->acl_ace_del = srvl_ace_del;
        state->acl_ace_counter_get = vtss_cmn_ace_counter_get;
        state->acl_ace_counter_clear = vtss_cmn_ace_counter_clear;
        state->range_commit = srvl_vcap_range_commit;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(srvl_vcap_init(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_OCELOT */
