// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_CLOCK
#include "vtss_omega_clock_cil.h"

#if defined(VTSS_FEATURE_CLOCK)

/* Register access */
/* Read, modify and write register */

/* Read register */
static vtss_rc vtss_es6514_rd(vtss_state_t *vtss_state, u32 addr, u32 *value)
{
    vtss_init_conf_t *conf = &vtss_state->init_conf;

    /* Use normal register read function by default */
    return (conf->clock_read ? conf->clock_read(addr, value) : conf->reg_read(0, addr, value));
}

/* Write register */
static vtss_rc vtss_es6514_wr(vtss_state_t *vtss_state, u32 addr, u32 value)
{
    vtss_init_conf_t *conf = &vtss_state->init_conf;

    /* Use normal register write function by default */
    return (conf->clock_write ? conf->clock_write(addr, value) : conf->reg_write(0, addr, value));
}

/* Read, Modify and Write register */
static vtss_rc vtss_es6514_wrm(vtss_state_t *vtss_state, u32 addr, u32 value, u32 mask)
{
    vtss_rc rc;
    u32     val;

    if ((rc = vtss_es6514_rd(vtss_state, addr, &val)) == VTSS_RC_OK)
        rc = vtss_es6514_wr(vtss_state, addr, (val & ~mask) | (value & mask));
    return rc;
}


typedef enum {
    rx,
    tx,
} rxtx_t;


static vtss_rc vtss_es6514_init(vtss_state_t *vtss_state)
{
#if !defined(VTSS_ARCH_SERVAL_T)
    int i;
    u32 tgt;
    u32 rd_val;

    /* It turned out that we have to enable the serdes for a short time because */
    /* otherwise there are two buffers driving the same net with different values. */
    /* This causes increased power consumption and device aging */
    if (vtss_state->clock.init_done == FALSE) {
        /* Currently I can't boot the system when the SPI cable to the es6514 is connected. */
        /* This is probably due to the pull down I need on the SSE line of the connection cable. */
        /* Therefore the CHIP_ID is read and only if I read the valid value, I know that the cable is connected */
        /* and I can do my initialization */
        ES6514_RDF(ES6514_CORE, ES6514_CORE_ES6514_ID, CHIP_ID,     &rd_val);
        if (rd_val == 0x6514) {
            for (i = 0; i < 2; i++) {
                tgt = VTSS_TO_SD10G65(i);
                ES6514_RDXB(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_BIAS_EN,  &rd_val);
                if (rd_val == 0) {
                    ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_BIAS_EN,  1);
                    ES6514_RDXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0, tgt, SYNTH_ENA,     &rd_val);
                    if (rd_val == 0) {
                        ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0, tgt, SYNTH_ENA,     1);
                        ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0, tgt, SYNTH_ENA,     0);
                    }
                    ES6514_RDXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_ENA,     &rd_val);
                    if (rd_val == 0) {
                        ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_ENA,     1);
                        ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_ENA,     0);
                    }
                    ES6514_RDXB(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2, tgt, PLL_ENA,       &rd_val);
                    if (rd_val == 0) {
                        ES6514_WRXB(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2, tgt, PLL_ENA,       1);
                        ES6514_WRXB(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2, tgt, PLL_ENA,       0);
                    }
                    ES6514_RDXB(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_ENA,       &rd_val);
                    if (rd_val == 0) {
                        ES6514_WRXB(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_ENA,       1);
                        ES6514_WRXB(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_ENA,       0);
                    }
                    ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_BIAS_EN,  0);
                }
            }
            vtss_state->clock.init_done = TRUE;
        }
    }
#endif //VTSS_ARCH_SERVAL_T
    return VTSS_RC_OK;
}


static BOOL es6514_check_pll_lock(vtss_state_t *vtss_state,
                                  const rxtx_t direction,
                                  const u8     clock)
{
    u8 i;
    u8 lock_found;
    u32 rd_val;
#if VTSS_OPT_TRACE
    u32 addr;
#endif

    for (i = 0; i < 30; i++) {
        /* wait 20 us */
        VTSS_NSLEEP(20000);
        if (direction == rx) { 
            ES6514_RDXB(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0, VTSS_TO_SD10G65(clock), PLLF_LOCK_STAT, &lock_found);
        } else {
            ES6514_RDXB(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0, VTSS_TO_SD10G65(clock), PLLF_LOCK_STAT, &lock_found);
        }
        if (lock_found == 1) {
            return TRUE;
        }
    }

    /* RC-PLL did not lock. Lets look at the status */        
    VTSS_E("%s-RCPLL in SD10G65_%d could not find lock\n", (direction == rx) ? ("RX") : ("TX"), clock);
    VTSS_E("lock_found is %u\n", lock_found);
    if (direction == rx) {
#if VTSS_OPT_TRACE
        addr = ES6514_ADDR_X(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0, VTSS_TO_SD10G65(clock));
#endif
        for (i = 0; i < 2; i++) {
            ES6514_RDX(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0, VTSS_TO_SD10G65(clock), &rd_val);
            VTSS_E("The content of SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
        }

#if VTSS_OPT_TRACE
        addr = ES6514_ADDR_X(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1, VTSS_TO_SD10G65(clock));
#endif
        for (i = 0; i < 2; i++) {
            ES6514_RDX(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1, VTSS_TO_SD10G65(clock), &rd_val);
            VTSS_E("The content of SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
        }
    } else { /* direction == tx */
#if VTSS_OPT_TRACE
        addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0, VTSS_TO_SD10G65(clock));
#endif
        for (i = 0; i < 2; i++) {
            ES6514_RDX(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0, VTSS_TO_SD10G65(clock), &rd_val);
            VTSS_E("The content of SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
        }

#if VTSS_OPT_TRACE
        addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1, VTSS_TO_SD10G65(clock));
#endif
        for (i = 0; i < 2; i++) {
            ES6514_RDX(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1, VTSS_TO_SD10G65(clock), &rd_val);
            VTSS_E("The content of SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
        }
    }
    return FALSE;
} 


/* function to map from SD10G65 interface width to configuration value */
static u8   es6514_get_iw_setting(vtss_state_t *vtss_state,
                                  const u8     interface_width) {
    switch (interface_width) {
        case 8: {
            return 0;
            break;
        }
        case 10: {
            return 1;
            break;
        }
        case 16: {
            return 2;
            break;
        }
        case 20: {
            return 3;
            break;
        }
        case 32: {
            return 4;
            break;
        }
        case 40: {
            return 5;
            break;
        }
        default : {
            VTSS_E("Illegal value %d for interface width\n", interface_width);
            return VTSS_RC_ERROR;
        }
    }
}

/* function to calculate the greatest common divisor using the euclidean algorithm */
static u64  es6414_calc_gcd(const u64 num_in,
                            const u64 div_in) {
    u64 rem;
    u64 num;
    u64 div;

    rem = VTSS_MOD64(num_in, div_in);
    div = div_in;
    while (rem != 0) {
        num = div;
        div = rem;
        rem = VTSS_MOD64(num, div);
    }
    return div;
}

static void es6514_calc_synth_settings(vtss_state_t *vtss_state,
                                       const u64    num_in,
                                       const u64    div_in,
                                       u16    *const freq_mult,
                                       u64    *const freqm,
                                       u64    *const freqn)
{
    u64 numerator;
    u64 gcd;

    *freq_mult = (u16)VTSS_DIV64((u64)8192 * num_in, div_in);

    /* check what was cut by the above formula */
     numerator = ((u64)8192 * num_in) - (*freq_mult * div_in); 
    if (numerator == 0) {
        *freqm = 0;
        *freqn = (u64)1 << 35;
    } else {
        /* calculate common divisor */
        gcd = es6414_calc_gcd(numerator, div_in);

        /* and cancel out numerator and divisor with the gcd */
        *freqm = VTSS_DIV64(numerator, gcd);
        *freqn = VTSS_DIV64(div_in, gcd);

        /* choose largest possible values to keep adaption time low;              */
        /* a 4G mode, that reqiured a 0.6 it showed, that the adaption time took  */
        /* several seconds when choosing 3 / 5 to get 0.6                         */
        /* SD error integ running at 312MHz takes ~32 seconds to reach zero.      */
        /* starting @~-2^35 when numerator is 3                                   */
        while (*freqn < ((u64)1 << 35)) {
            *freqm = ( *freqm << 1 );
            *freqn = ( *freqn << 1 );
        }
    }
    return;
}

static inline u16 es6514_tri_dec(u16 val_in)
{
    switch (val_in) {
    case 0: {return 6; break;}
    case 1: {return 7; break;}
    case 2: {return 4; break;}
    case 3: {return 0; break;}
    default: VTSS_E("es6514_tri_dec discovered invalid input value %d\n", val_in);
    }
    return 0;
}

static inline u16 es6514_bi_dec(u16 val_in)
{
    switch (val_in) {
    case 0: {return 3; break;}
    case 1: {return 1; break;}
    default: VTSS_E("es6514_bi_dec discovered invalid input value %d\n", val_in);
    }
    return 0;
}

static inline u16 es6514_lt_dec(u16 val_in)
{
    switch (val_in) {
    case 0: {return 0; break;}
    case 1: {return 6; break;}
    case 2: {return 5; break;}
    case 3: {return 4; break;}
    default: VTSS_E("es6514_lt_dec discovered invalid input value %d\n", val_in);
    }
    return 0;
}

static inline u16 es6514_ls_dec(u16 val_in)
{
    switch (val_in) {
    case 0: {return  8; break;}
    case 1: {return 10; break;}
    case 2: {return 12; break;}
    case 3: {return 14; break;}
    case 4: {return  7; break;}
    case 5: {return  5; break;}
    case 6: {return  3; break;}
    case 7: {return  1; break;}
    default: VTSS_E("es6514_ls_dec discovered invalid input value %d\n", val_in);
    }
    return 0;
}

/* For the following products the frequency decoder inside the SerDes has a flaw.
    "ES6514"
    "JAGUAR2"
    "JAGUAR2C""
    "VENICE"
    "VENICE_C"
    "MALIBU"
    "SERVALT"
    "ROLEX"
    Therefore we do SW decoding and bypass the frequency decoder */

static void es6514_calc_frec_dec_bypass(const u16  freq_mult_in,
                                        u16        *const freq_mult_out,
                                        u8         *const freq_mult_hi)
{
    u16 freq_sign;
    u16 freq_abs;
    u16 tri_2g5;
    u16 tri_625m;
    u16 tri_156m;
    u16 bi_39m;
    u16 tri_20m;
    u16 ls_5m;

    u16 ena_2g5_dec;
    u16 dir_2g5_dec;
    u16 spd_2g5_dec;

    u16 ena_625m_dec;
    u16 dir_625m_dec;
    u16 spd_625m_dec;

    u16 ena_156m_dec;
    u16 dir_156m_dec;
    u16 spd_156m_dec;

    u16 ena_39m_dec;
    u16 dir_39m_dec;

    u16 ena_20m_dec;
    u16 dir_20m_pre;
    u16 spd_20m_dec;

    u16 dir_5m_pre;
    u16 ena_2m5_dec;
    u16 ena_1m25_dec;
    u16 inv_sd_dec;

    u16 dir_ls_dec;
    u16 dir_20m_dec;

    freq_sign    = freq_mult_in >> 13;
    freq_abs     = (freq_sign == 1) ? (freq_mult_in & 0xfff) : (~freq_mult_in & 0xfff);

    tri_2g5      = es6514_tri_dec(((freq_abs - 684) >> 10) & 0x3);
    tri_625m     = es6514_tri_dec(((freq_abs - 172) >>  8) & 0x3);
    tri_156m     = es6514_tri_dec(((freq_abs -  44) >>  6) & 0x3);
    bi_39m       =  es6514_bi_dec(((freq_abs -  12) >>  5) & 0x1);
    tri_20m      =  es6514_lt_dec(((freq_abs +   4) >>  3) & 0x3);
    ls_5m        =  es6514_ls_dec(((freq_abs -   0) >>  0) & 0x7);

    ena_2g5_dec  =   ((tri_2g5  >> 2)                & 1);
    dir_2g5_dec  =  (((tri_2g5  >> 1) ^  ~freq_sign) & 1);
    spd_2g5_dec  =   ((tri_2g5  >> 0)                & 1);

    ena_625m_dec =   ((tri_625m >> 2)                & 1);
    dir_625m_dec =  (((tri_625m >> 1) ^  ~freq_sign) & 1);
    spd_625m_dec =   ((tri_625m >> 0)                & 1);

    ena_156m_dec =   ((tri_156m >> 2)                & 1);
    dir_156m_dec =  (((tri_156m >> 1) ^  ~freq_sign) & 1);
    spd_156m_dec =   ((tri_156m >> 0)                & 1);

    ena_39m_dec  =   ((bi_39m   >> 1)                & 1);
    dir_39m_dec  =  (((bi_39m   >> 0) ^  ~freq_sign) & 1);

    ena_20m_dec  =   ((tri_20m  >> 2)                & 1);
    dir_20m_pre  =  (((tri_20m  >> 1) ^  ~freq_sign) & 1);
    spd_20m_dec  =   ((tri_20m  >> 0)                & 1);

    dir_5m_pre   =  (((ls_5m    >> 3) ^  ~freq_sign) & 1);
    ena_2m5_dec  =   ((ls_5m    >> 2)                & 1);
    ena_1m25_dec =   ((ls_5m    >> 1)                & 1);
    inv_sd_dec   =  (((ls_5m    >> 0) ^  ~freq_sign) & 1);

    dir_ls_dec   =   dir_5m_pre;
    dir_20m_dec  =  (dir_20m_pre      ^ ~dir_5m_pre) & 1;

    *freq_mult_hi = ((ena_2g5_dec  <<  3) |
                     (dir_2g5_dec  <<  2) |
                     (spd_2g5_dec  <<  1) |
                     (ena_625m_dec <<  0)) ^ 0x4;

    *freq_mult_out = ((dir_625m_dec << 13) |
                      (spd_625m_dec << 12) |
                      (ena_156m_dec << 11) |
                      (dir_156m_dec << 10) |
                      (spd_156m_dec <<  9) |
                      (ena_39m_dec  <<  8) |
                      (dir_39m_dec  <<  7) |
                      (dir_ls_dec   <<  6) |
                      (ena_20m_dec  <<  5) |
                      (dir_20m_dec  <<  4) |
                      (spd_20m_dec  <<  3) |
                      (ena_2m5_dec  <<  2) |
                      (ena_1m25_dec <<  1) |
                      (inv_sd_dec   <<  0)) ^ 0x24D0;

    return;
}
                                  

/* ****************************************************************** *
 * Prdeclare functions used by other functions in this file  here     *
 * ****************************************************************** */
static vtss_rc es6514_clock_output_frequency_get(vtss_state_t                  *vtss_state,
                                                 const u8                      clock_output,
                                                 u32                           *const freq_khz,
                                                 u32                           *const par_freq_khz);

static vtss_rc es6514_clock_output_frequency_set(vtss_state_t                  *vtss_state,
        const u8                      clock_output,
        const u32                     freq_khz,
        const u32                     par_freq_khz);

static void es6514_delta_f_to_scaled_ppb(u32 value_h, u32 value_l, i64 *const offset)
{
    i64 tmp;
    /* offset is: value * 1e9 * 2**16 / 7 / 2**32 / 1024 */
    /* 1e9 = 1953125 * 2**9 */
    /* 1024 = 2**10 */
    /* 9 + 16 - 32 - 10 = -17 */
    if ( ((value_h >> 3) & 0x1) > 0) {
        /* value is negative */
        tmp = (i64)(-1) * ((((u64)(~value_h & 0x7)) << 32) + (u64)(~value_l) + 1);
    } else {
        tmp =              (((u64)(value_h & 0x7)) << 32) + (u64)value_l;
    }
    *offset = (tmp * 1953125 / 7) >> 17;
}

/* ****************************************************************** *
 * CIL functions accessible from AIL starts here                      *
 * ****************************************************************** */

// ***************************************************************************
//
//  Configuration 
//
// ***************************************************************************

/* Set global enable */
static vtss_rc es6514_clock_global_enable_set(vtss_state_t                      *vtss_state,
                                              const vtss_clock_global_enable_t  ena)
{
    u8 i,j,dpll;
    u32 omega_svn_id;

    /* The below init function is only needed here in the es6514 connected over the SPI cable, because */
    /* the cable is most likely disconnected during the time the vtss_es6514_clock_init function is called with */
    /* parameter VTSS_INIT_CMD_INIT */
    VTSS_RC(vtss_es6514_init(vtss_state));

    if (ena == TRUE) {
        /* Only perform this if we are not yet enabled */
        if (vtss_state->clock.global_enable != TRUE) {
            ES6514_WRB(OMG_MAIN, OMG_MAIN_OMG_MAIN_CFG, SW_ENA, 1);
            ES6514_WRB(OMG_MAIN, OMG_MAIN_OMG_MAIN_CFG, SW_RST, 0);

            /* After reset/initialization, the controller must have all sources disabled */
            for (dpll = 0; dpll < vtss_state->clock.dpll_cnt; dpll++) {
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_ENA, 0);
                /* Bugzilla 17881 Disable Auto-switch-back when prio 0 is disabled */
                if (vtss_state->clock.selection_conf[dpll].mode == VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE) {
                    ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_AUTO_SWITCH_BACK, 0);
                }
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO1_ENA, 0);
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO2_ENA, 0);
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO3_ENA, 0);
                for (i = 0; i < vtss_state->clock.clock_input_cnt; i++) {
                    vtss_state->clock.priority_selector[dpll][i].enable   = FALSE;
                }
            }
            
            ES6514_RD(OMG_MAIN, OMG_MAIN_OMG_SVN_ID, &omega_svn_id);
            if (omega_svn_id <= 0xa460) {
                /* We have the ES6514 buggy version */
                for (i = 0; i < vtss_state->clock.dpll_cnt; i++) {
                    /* !! Bugzilla #15547 only relevant for es6514: ho_filtshft must NOT be above 10 but reset value is 14*/
                    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, i, CTRL_HO_LPF_FILTSHFT, 10);
                }
                /* Bugzilla #16214 incorrect reference selection in controller if all reference inputs are invalid */
                /* Workaround: Enable channel 0 and generate alarm condition. LOL is active as long as the receiver is not enabled */
                ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, 0, QUAL_ENA,    1);
                ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, 0, QUAL_SW_RST, 0);
                ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG,  0, QUAL_LOL_CTRL_ALARM_ENA, 1);
                vtss_state->clock.input_conf[0].alarm_ena.lol   = TRUE;
            }
        }
    } else {
        ES6514_WRB(OMG_MAIN, OMG_MAIN_OMG_MAIN_CFG, SW_ENA, 0);
        ES6514_WRB(OMG_MAIN, OMG_MAIN_OMG_MAIN_CFG, SW_RST, 1);
        for (i = 0; i < vtss_state->clock.dpll_cnt; i++) {
            vtss_state->clock.selection_conf[i].mode = VTSS_CLOCK_SELECTION_MODE_DISABLED;
            vtss_state->clock.selection_conf[i].clock_input = 0;
            vtss_state->clock.dpll_conf[i].mode      = VTSS_CLOCK_OPERATION_MODE_DISABLED;
            vtss_state->clock.dpll_conf[i].holdoff   = 500;
            vtss_state->clock.dpll_conf[i].holdover  = 3000;
            vtss_state->clock.dpll_conf[i].wtr       = 10;
            vtss_state->clock.ho_stack_conf[i].ho_post_filtering_bw = 8898;
            vtss_state->clock.ho_stack_conf[i].ho_qual_time_conf    = 10;
            for (j = 0; j < 2; j++) {
                vtss_state->clock.priority_selector[i][j].priority = j;
                vtss_state->clock.priority_selector[i][j].enable   = TRUE;
            }
            for (j = 2; j < vtss_state->clock.clock_input_cnt; j++) {
                vtss_state->clock.priority_selector[i][j].priority = j;
                vtss_state->clock.priority_selector[i][j].enable   = FALSE;
            }
            ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0,   i,                           0);
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1,   i, DF_FRM_HIGH,              0);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1,   i, DF_FRM_UPDATE_ONE_SHOT,   1);
            vtss_state->clock.emulated_ho_state[i]   = FALSE;
        }

        for (i = 0; i < vtss_state->clock.clock_input_cnt; i++) {
            vtss_state->clock.input_frequency[i]                   = 0;
            vtss_state->clock.input_sample_freq_khz[i]             = 3250000; /* set to reasonable default value*/
            vtss_state->clock.use_internal_clock_src[i]            = 0;
            vtss_state->clock.input_frequency_ratio[i].num         = 1;
            vtss_state->clock.input_frequency_ratio[i].den         = 1;
            vtss_state->clock.serdes_rx_en[i]                      = FALSE;
            vtss_state->clock.cfm_conf[i].cfm_set_ppb              = 50000;
            vtss_state->clock.cfm_conf[i].cfm_clr_ppb              = 50000;
            vtss_state->clock.pfm_conf[i].pfm_set_ppb              = 213;
            vtss_state->clock.pfm_conf[i].pfm_clr_ppb              = 213;
            vtss_state->clock.gst_conf[i].disqualification_time_us = 100;
            vtss_state->clock.gst_conf[i].qualification_time_us    = 100;
            vtss_state->clock.gst_conf[i].los                      = FALSE;
            vtss_state->clock.gst_conf[i].pfm                      = FALSE;
            vtss_state->clock.gst_conf[i].cfm                      = FALSE;
            vtss_state->clock.gst_conf[i].scm                      = FALSE;
            vtss_state->clock.gst_conf[i].lol                      = FALSE;
            vtss_state->clock.input_conf[i].los_active_high        = TRUE;
            vtss_state->clock.input_conf[i].alarm_ena.los          = FALSE;
            vtss_state->clock.input_conf[i].alarm_ena.pfm          = FALSE;
            vtss_state->clock.input_conf[i].alarm_ena.cfm          = FALSE;
            vtss_state->clock.input_conf[i].alarm_ena.scm          = FALSE;
            vtss_state->clock.input_conf[i].alarm_ena.gst          = FALSE;
            vtss_state->clock.input_conf[i].alarm_ena.lol          = FALSE;
        }

        for (i = 0; i < vtss_state->clock.clock_output_cnt; i++) {
            vtss_state->clock.output_frequency[i]             = 0;
            vtss_state->clock.par_output_frequency[i]         = 0;
            vtss_state->clock.output_frequency_ratio[i].num   = 1;
            vtss_state->clock.output_frequency_ratio[i].den   = 1;
            vtss_state->clock.output_level[i]                 = 900;
            vtss_state->clock.adj_frequency[i]                = 0;
            vtss_state->clock.serdes_tx_en[i]                 = FALSE;
            vtss_state->clock.input_selector[i].input_type    = VTSS_CLOCK_INPUT_TYPE_DPLL;
            vtss_state->clock.input_selector[i].input_inst    = 0;
            vtss_state->clock.output_filter_bw[i]             = 0;
            vtss_state->clock.psl_conf[i].limit_ppb           = 0;
            vtss_state->clock.psl_conf[i].phase_build_out_ena = FALSE;
            vtss_state->clock.psl_conf[i].ho_based            = FALSE;
        }
    }
    vtss_state->clock.global_enable = ena;

    return VTSS_RC_OK;
}

/* Get global enable */
static vtss_rc es6514_clock_global_enable_get(vtss_state_t                *vtss_state,
                                              vtss_clock_global_enable_t  *const ena)
{
    u8  rd_val;
    ES6514_RDB(OMG_MAIN, OMG_MAIN_OMG_MAIN_CFG, SW_ENA, &rd_val);
    *ena = (rd_val != 1) ? FALSE : TRUE;
    if (*ena != vtss_state->clock.global_enable) {
        VTSS_E("Value stored in HW does not fit to value of SW state variable. HW: %u, SW: %u", (unsigned int) *ena, (unsigned int) vtss_state->clock.global_enable);
        return VTSS_RC_ERROR;
     }

    return VTSS_RC_OK;
}

/* Bring the selectors back into default state, so that the system can continue working after DPLL reset */
/* this setting is moved to the kernel, but it is kept here for the case that this API is used in an other environment */
static vtss_rc es6514_clock_shutdown(vtss_state_t                *vtss_state)
{
#if defined(VTSS_ARCH_SERVAL_T)
    /* set up PLL0 back to default */
    ES6514_WRXM(HSIO, PLL5G_CFG_PLL5G_CFG2, 0,
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG2, ENA_TEST_MODE, 0),
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG2, ENA_TEST_MODE));
    ES6514_WRXM(HSIO, PLL5G_CFG_PLL5G_CFG3, 0,
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG3, FBDIVSEL, 40),
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG3, FBDIVSEL));
    /* set up PLL0 to select signal from Refclk0 */
    ES6514_WRXM(HSIO, PLL5G_CFG_PLL5G_CFG6, 0,
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SEL_SRC, 0) |
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SEL , 0) |
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SRC , 0),
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SEL_SRC) |
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SEL) |
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SRC));

    /* select internal core/1588 clock from PLL0 (selected by PLL2_SEL strapping) */
    ES6514_WRF(HSIO, HW_CFGSTAT_CLK_CFG, SWC_CLK_SRC, 0);
#endif //VTSS_ARCH_SERVAL_T
    return VTSS_RC_OK;
}

/* Pull SW reset and release again */
static vtss_rc es6514_clock_global_sw_reset(vtss_state_t                *vtss_state)
{
    u8  rd_val;
    u8  i, j;

    if (VTSS_RC_OK != es6514_clock_shutdown(vtss_state)) {
        return VTSS_RC_ERROR;
    }
    ES6514_RDB(OMG_MAIN, OMG_MAIN_OMG_MAIN_CFG, SW_RST, &rd_val);
    if (rd_val == 0) {
        ES6514_WRB(OMG_MAIN, OMG_MAIN_OMG_MAIN_CFG, SW_RST, 1);
        ES6514_WRB(OMG_MAIN, OMG_MAIN_OMG_MAIN_CFG, SW_RST, 0);
    }
    for (i = 0; i < vtss_state->clock.dpll_cnt; i++) {
        vtss_state->clock.selection_conf[i].mode = VTSS_CLOCK_SELECTION_MODE_DISABLED;
        vtss_state->clock.selection_conf[i].clock_input = 0;
        vtss_state->clock.dpll_conf[i].mode      = VTSS_CLOCK_OPERATION_MODE_DISABLED;
        vtss_state->clock.dpll_conf[i].holdoff   = 500;
        vtss_state->clock.dpll_conf[i].holdover  = 3000;
        vtss_state->clock.dpll_conf[i].wtr       = 10;
        vtss_state->clock.ho_stack_conf[i].ho_post_filtering_bw = 8898;
        vtss_state->clock.ho_stack_conf[i].ho_qual_time_conf    = 10;
        for (j = 0; j < 2; j++) {
            vtss_state->clock.priority_selector[i][j].priority = j;
            vtss_state->clock.priority_selector[i][j].enable   = TRUE;
        }
        for (j = 2; j < vtss_state->clock.clock_input_cnt; j++) {
            vtss_state->clock.priority_selector[i][j].priority = j;
            vtss_state->clock.priority_selector[i][j].enable   = FALSE;
        }
        ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0,   i,                           0);
        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1,   i, DF_FRM_HIGH,              0);
        ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1,   i, DF_FRM_UPDATE_ONE_SHOT,   1);
        vtss_state->clock.emulated_ho_state[i]   = FALSE;
    }
#if defined(VTSS_ARCH_SERVAL_T)
    /* select internal core/1588 clock from DPLL1 which is first set up to generate 156,250MHz */
    if (VTSS_RC_OK != es6514_clock_output_frequency_set(vtss_state, 1, 0, 156250)) {
        return VTSS_RC_ERROR;
    }
    ES6514_WRF(HSIO, HW_CFGSTAT_CLK_CFG, SWC_CLK_SRC, 3);

    /* select internal reference clock from DPLL0 which is first set up to generate 100MHz */
    if (VTSS_RC_OK != es6514_clock_output_frequency_set(vtss_state, 0, 0, 100000)) {
        return VTSS_RC_ERROR;
    }
    /* set up PLL0 to expect 100MHz input */
    ES6514_WRXM(HSIO, PLL5G_CFG_PLL5G_CFG2, 0,
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG2, ENA_TEST_MODE, 1),
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG2, ENA_TEST_MODE));
    ES6514_WRXM(HSIO, PLL5G_CFG_PLL5G_CFG3, 0,
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG3, FBDIVSEL, 50),
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG3, FBDIVSEL));

    /* set up PLL0 to select signal from DPLL0 */
    ES6514_WRXM(HSIO, PLL5G_CFG_PLL5G_CFG6, 0,
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SEL_SRC, 1) |
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SEL , 2) |    // note that the reference to PLL0 is 156,25 MHz no matter what the clock output frequency is set to
                ES6514_PUT_FLD(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SRC , 1),
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SEL_SRC) |
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SEL) |
                ES6514_MSK(HSIO, PLL5G_CFG_PLL5G_CFG6, REFCLK_SRC));

#endif //VTSS_ARCH_SERVAL_T

    for (i = 0; i < vtss_state->clock.clock_input_cnt; i++) {
        vtss_state->clock.input_frequency[i]                   = 0;
        vtss_state->clock.input_sample_freq_khz[i]             = 3250000; /* set to reasonable default value*/
        vtss_state->clock.use_internal_clock_src[i]            = 0;
        vtss_state->clock.input_frequency_ratio[i].num         = 1;
        vtss_state->clock.input_frequency_ratio[i].den         = 1;
        vtss_state->clock.serdes_rx_en[i]                      = FALSE;
        vtss_state->clock.cfm_conf[i].cfm_set_ppb              = 50000;
        vtss_state->clock.cfm_conf[i].cfm_clr_ppb              = 50000;
        vtss_state->clock.pfm_conf[i].pfm_set_ppb              = 213;
        vtss_state->clock.pfm_conf[i].pfm_clr_ppb              = 213;
        vtss_state->clock.gst_conf[i].disqualification_time_us = 100;
        vtss_state->clock.gst_conf[i].qualification_time_us    = 100;
        vtss_state->clock.gst_conf[i].los                      = FALSE;
        vtss_state->clock.gst_conf[i].pfm                      = FALSE;
        vtss_state->clock.gst_conf[i].cfm                      = FALSE;
        vtss_state->clock.gst_conf[i].scm                      = FALSE;
        vtss_state->clock.gst_conf[i].lol                      = FALSE;
        vtss_state->clock.input_conf[i].los_active_high        = TRUE;
        vtss_state->clock.input_conf[i].alarm_ena.los          = FALSE;
        vtss_state->clock.input_conf[i].alarm_ena.pfm          = FALSE;
        vtss_state->clock.input_conf[i].alarm_ena.cfm          = FALSE;
        vtss_state->clock.input_conf[i].alarm_ena.scm          = FALSE;
        vtss_state->clock.input_conf[i].alarm_ena.gst          = FALSE;
        vtss_state->clock.input_conf[i].alarm_ena.lol          = FALSE;
    }

    for (i = 0; i < vtss_state->clock.clock_output_cnt; i++) {
        vtss_state->clock.output_frequency[i]             = 0;
        vtss_state->clock.par_output_frequency[i]         = 0;
        vtss_state->clock.output_frequency_ratio[i].num   = 1;
        vtss_state->clock.output_frequency_ratio[i].den   = 1;
        vtss_state->clock.output_level[i]                 = 900;
        vtss_state->clock.adj_frequency[i]                = 0;
        vtss_state->clock.serdes_tx_en[i]                 = FALSE;
        vtss_state->clock.input_selector[i].input_type    = VTSS_CLOCK_INPUT_TYPE_DPLL;
        vtss_state->clock.input_selector[i].input_inst    = 0;
        vtss_state->clock.output_filter_bw[i]             = 0;
        vtss_state->clock.psl_conf[i].limit_ppb           = 0;
        vtss_state->clock.psl_conf[i].phase_build_out_ena = FALSE;
        vtss_state->clock.psl_conf[i].ho_based            = FALSE;
    }

    return VTSS_RC_OK;
}

/* Set Clock selection mode. */
static vtss_rc es6514_clock_selection_mode_set(vtss_state_t *vtss_state,
                                               const vtss_clock_dpll_inst_t      dpll,
                                               const vtss_clock_selection_conf_t *const conf)
{
    u8  i;
    u32 rd_val, conf_value_l, conf_value_h;
    u8  ctrl_eec_state;

    if ((vtss_state->clock.selection_conf[dpll].mode        != conf->mode) ||
        (vtss_state->clock.selection_conf[dpll].clock_input != conf->clock_input)) {

        /* if we switch from DCO to non-DCO mode, we must remove the frequency offset: */
        if ((vtss_state->clock.selection_conf[dpll].mode == VTSS_CLOCK_SELECTION_MODE_FORCED_DCO) && 
            (conf->mode                                  != VTSS_CLOCK_SELECTION_MODE_FORCED_DCO)) {
            /* use the saved holdover value, when switching away from DCO mode */
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_SEL, 15);
            vtss_state->clock.dco_ho_offset[dpll] = 0LL;  /* clear the saved holdover value */
            for (i = 0; i < vtss_state->clock.clock_output_cnt; i++) {
                ES6514_RDXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, i, FILT_SRC_SEL, &rd_val);
                if (rd_val == (vtss_state->clock.clock_input_cnt + dpll)) {
                    /* This filter has selected the current dpll as source, now clear the respective DCO */
                    ES6514_WRX(OMG_MAIN,  OMG_FILT_OMG_FILTER_DCO_LOW,  i,                      0);
                    ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_DCO_HIGH, i, DCO_HIGH,            0);
                    ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_DCO_HIGH, i, DCO_UPDATE_ONE_SHOT, 1);
                }
            }
        }

        /* Now we can setup the mode */
        vtss_clock_selection_mode_t new_mode = conf->mode;
        switch (conf->mode) {
        case VTSS_CLOCK_SELECTION_MODE_DISABLED: {
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 0);
            ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0, dpll,                           0);
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_HIGH,              0);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_UPDATE_ONE_SHOT,   1);
            vtss_state->clock.emulated_ho_state[dpll] = FALSE;
            break;
        }

        case VTSS_CLOCK_SELECTION_MODE_MANUEL: {
            /* There is no explicite manual mode. Select auto mode and enable only 1 source */
            /* But Disable first, because we might at the momend already be in an auto mode and locked */
            /* AKR: Disabling causes freerun for approx. 1 sec. therefore this has been removed. */
            //ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE,          0);
            //ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL,   dpll,                        0);
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL,   dpll, CTRL_REFSEL_PRIO0_SEL, conf->clock_input);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL,   dpll, CTRL_REFSEL_PRIO0_ENA, 1);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL,   dpll, CTRL_REFSEL_PRIO1_ENA, 0);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL,   dpll, CTRL_REFSEL_PRIO2_ENA, 0);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL,   dpll, CTRL_REFSEL_PRIO3_ENA, 0);
            /* Auto mode = 3 */
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE,          3);
            vtss_state->clock.priority_selector[dpll][conf->clock_input].priority = 0;
            vtss_state->clock.priority_selector[dpll][conf->clock_input].enable   = TRUE;
            for (i = 0; i < vtss_state->clock.clock_input_cnt; i++) {
                if (i != conf->clock_input) {
                    vtss_state->clock.priority_selector[dpll][i].enable   = FALSE;
                }
            }
            ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0, dpll,                           0);
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_HIGH,              0);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_UPDATE_ONE_SHOT,   1);
            vtss_state->clock.emulated_ho_state[dpll] = FALSE;
            break;
        }

        case VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_NONREVERTIVE: {
            /* Auto mode = 3 */
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 3);
            /* Auto switch back = 0 */
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_AUTO_SWITCH_BACK, 0);
            break;
        }

        case VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE: {
            /* Auto mode = 3 */
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 3);
            /* Auto switch back = 1 */
            /* Bugzilla 17881 only enable Auto-switch-back when prio 0 is enabled */
            ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_ENA, &rd_val);
            if (rd_val == 1) {
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_AUTO_SWITCH_BACK, 1);
            } else {
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_AUTO_SWITCH_BACK, 0);
            }
            break;
        }

        case VTSS_CLOCK_SELECTION_MODE_FORCED_HOLDOVER: {
            /* Forced holdover mode = 2 */
            ES6514_RDX(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, dpll, &rd_val);
            ctrl_eec_state = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_EEC_STATE,   rd_val);
            if (ctrl_eec_state < 4) {
                /* The holdover stack is not yet filled. It does not make sense to go into FORCED_HOLDOVER mode */
                /* Instead we go into FORCED_FREE_RUN */
                new_mode = VTSS_CLOCK_SELECTION_MODE_FORCED_FREE_RUN;
                ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 1);
                VTSS_I("The clock_selection_mode_set was called with mode set to VTSS_CLOCK_SELECTION_MODE_FORCED_HOLDOVER, but holdover stack is not filled yet. Going into FORCED_FREE_RUN instead");
            } else {
                ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 2);
            }
            break;
        }

        case VTSS_CLOCK_SELECTION_MODE_FORCED_FREE_RUN: {
            /* Force freerun mode = 1*/
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 1);
            ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0, dpll,                           0);
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_HIGH,              0);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_UPDATE_ONE_SHOT,   1);
            vtss_state->clock.emulated_ho_state[dpll] = FALSE;
            break;
        }

        case VTSS_CLOCK_SELECTION_MODE_FORCED_DCO: {
            /* Force freerun mode = 1*/
            /* Switch to dco mode without any transients, this is done by saving the current holdover offset in the delta f registers */
            if(vtss_state->clock.emulated_ho_state[dpll]) {
                ES6514_RDX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0,        dpll,                           &conf_value_l);
                ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1,        dpll, DF_FRM_HIGH,              &conf_value_h);
            } else {
                ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_SEL, &rd_val);
                ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG,   dpll, CTRL_HO_RD_ADDR,          rd_val);
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG,   dpll, CTRL_HO_RD_STRB_ONE_SHOT, 1);
                ES6514_RDX( OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_STAT0, dpll,                           &conf_value_l);
                ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_STAT1, dpll, CTRL_HO_RD_DATA_HIGH,     &conf_value_h);
            }
            /* now conf_value_l, conf_value_h holds the current holdover value, this is saved so that following dco_frequency_offset_set is done relative to the holdover value */
            es6514_delta_f_to_scaled_ppb(conf_value_h, conf_value_l, &vtss_state->clock.dco_ho_offset[dpll]);
            VTSS_I("saved holdover offset is %" PRIi64 " scaled ppb\n", vtss_state->clock.dco_ho_offset[dpll]);
            /* The holdover is also saved in the free run delta f register and the holdover delta f register */
            ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0, dpll,                           conf_value_l);
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_HIGH,              conf_value_h);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_UPDATE_ONE_SHOT,   1);
            ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_HOM0, dpll,                           conf_value_l);
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_HOM1, dpll, DF_HOM_HIGH,              conf_value_h);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_HOM1, dpll, DF_HOM_UPDATE_ONE_SHOT,   1);
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG,   dpll, CTRL_OP_MODE, 1);
            vtss_state->clock.emulated_ho_state[dpll] = FALSE;
            // Note: It is expected that a dco value is setup separately by the adj_frequency_set function
            //       or by the es6514_clock_dco_frequency_offset_set.
            break;
        }

        default: {
            VTSS_E("illegal conf mode\n");
            return VTSS_RC_ERROR;
        }
        } /* switch (conf->mode) */
        vtss_state->clock.selection_conf[dpll].mode        = new_mode;
        vtss_state->clock.selection_conf[dpll].clock_input = conf->clock_input;
    }

    return VTSS_RC_OK;
}



/* Get Clock selection mode. */
static vtss_rc es6514_clock_selection_mode_get(vtss_state_t                  *vtss_state,
                                               const vtss_clock_dpll_inst_t  dpll,
                                               vtss_clock_selection_conf_t   *const conf)
{
    u8    read_from_hw;
    u8    swb_read_from_hw;
    u32   rd_val;
         
    conf->mode        = vtss_state->clock.selection_conf[dpll].mode;
    conf->clock_input = vtss_state->clock.selection_conf[dpll].clock_input;

    /* Check what is stored in the HW */
    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE,          &read_from_hw);
    ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_AUTO_SWITCH_BACK, &swb_read_from_hw);
    switch (conf->mode) {
    case VTSS_CLOCK_SELECTION_MODE_DISABLED: {
        if (read_from_hw != 0) {
            VTSS_E("SW expected CTRL_OP_MODE set to 0, but HW was set to %d\n", read_from_hw);
            return VTSS_RC_ERROR;
        }
        break;
    }

    case VTSS_CLOCK_SELECTION_MODE_MANUEL: {
        if (read_from_hw != 3) {
            VTSS_E("SW expected CTRL_OP_MODE set to 3, but HW was set to %d\n", read_from_hw);
            return VTSS_RC_ERROR;
        }
        break;
    }

    case VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_NONREVERTIVE: {
        if (read_from_hw != 3) {
            VTSS_E("SW expected CTRL_OP_MODE set to 3, but HW was set to %d\n", read_from_hw);
            return VTSS_RC_ERROR;
        }
        if (swb_read_from_hw != 0) {
            VTSS_E("SW expected CTRL_AUTO_SWITCH_BACK set to 0, but HW was set to %d\n", swb_read_from_hw);
            return VTSS_RC_ERROR;
        }
        break;
    }

    case VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE: {
        if (read_from_hw != 3) {
            VTSS_E("SW expected CTRL_OP_MODE set to 3, but HW was set to %d\n", read_from_hw);
            return VTSS_RC_ERROR;
        }
        /* Bugzilla 17881 only enable Auto-switch-back when prio 0 is enabled */
        ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_ENA, &rd_val);
        if (rd_val == 1) {
            if (swb_read_from_hw != 1) {
                VTSS_E("SW expected CTRL_AUTO_SWITCH_BACK set to 1, but HW was set to %d\n", swb_read_from_hw);
                return VTSS_RC_ERROR;
            }
        }
        break;
    }

    case VTSS_CLOCK_SELECTION_MODE_FORCED_HOLDOVER: {
        if (read_from_hw != 2) {
            VTSS_E("SW expected CTRL_OP_MODE set to 2, but HW was set to %d\n", read_from_hw);
            return VTSS_RC_ERROR;
        }
        break;
    }

    case VTSS_CLOCK_SELECTION_MODE_FORCED_FREE_RUN: {
        if (read_from_hw != 1) {
            VTSS_E("SW expected CTRL_OP_MODE set to 1, but HW was set to %d\n", read_from_hw);
            return VTSS_RC_ERROR;
        }
        break;
    }

    case VTSS_CLOCK_SELECTION_MODE_FORCED_DCO: {
        if (read_from_hw != 1) {
            VTSS_E("SW expected CTRL_OP_MODE set to 1, but HW was set to %d\n", read_from_hw);
            return VTSS_RC_ERROR;
        }
        break;
    }

    default: {
        VTSS_E("illegal conf mode\n");
        return VTSS_RC_ERROR;
    }
    } /* switch (conf->mode) */

     return VTSS_RC_OK;
}


/* Set Clock operation mode. */
static vtss_rc es6514_clock_operation_conf_set(vtss_state_t                      *vtss_state,
                                               const vtss_clock_dpll_inst_t      dpll,
                                               const vtss_clock_dpll_conf_t      *const conf)
{
    /* Paramtere range check */
    if (conf->holdover > ((1 << 17) - 1)) {
        VTSS_E("Value %u for holdover is to high, max value is %u\n", conf->holdover, ((1 << 17) - 1));
        return VTSS_RC_ERROR;
    }
    if (conf->wtr > ((1 << 10) - 1)) {
        VTSS_E("Value %u for wait to restore time (wtr) is to high, max value is %u\n", conf->wtr, ((1 << 10) - 1));
        return VTSS_RC_ERROR;
    }
    /* Mode */
    if (vtss_state->clock.dpll_conf[dpll].mode        != conf->mode) {
        switch(conf->mode) {
        case VTSS_CLOCK_OPERATION_MODE_DISABLED: {
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_SW_RST, 1);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_ENA,    0);
            break;
        }

        case VTSS_CLOCK_OPERATION_MODE_ENABLED: {
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_ENA,    1);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_SW_RST, 0);
            break;
        }

        default: {
            VTSS_E("illegal conf mode\n");
            return VTSS_RC_ERROR;
        }
        } /* switch(conf->mode) */
    }


    /* holdoff */
    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_TIMING_CFG0, dpll, CTRL_HOLD_OFF_TIME, conf->holdoff); 

    /* holdover */
    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_TIMING_CFG1, dpll, CTRL_HOLD_OVER_TIME, conf->holdover);

    /* wtr (wait-to-restore) */
    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_TIMING_CFG1, dpll, CTRL_WAIT_TO_RESTORE_TIME, conf->wtr);
    /* initial qualification timer has very similar meaning as wait-to-restore timer */
    /* From SW perspective We use the same parameter to set it up */
    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_TIMING_CFG0, dpll, CTRL_INI_QUAL_TIME,        conf->wtr);

    /* set state variable to configured values */
    vtss_state->clock.dpll_conf[dpll].mode        = conf->mode;
    vtss_state->clock.dpll_conf[dpll].holdoff     = conf->holdoff;
    vtss_state->clock.dpll_conf[dpll].holdover    = conf->holdover;
    vtss_state->clock.dpll_conf[dpll].wtr         = conf->wtr;

    return VTSS_RC_OK;
}

/* Get Clock operation mode. */
static vtss_rc es6514_clock_operation_conf_get(vtss_state_t                  *vtss_state,
                                               const vtss_clock_dpll_inst_t  dpll,
                                               vtss_clock_dpll_conf_t        *const conf)
{
    u32    rd_val;
    vtss_rc result = VTSS_RC_OK;   

    conf->mode        = vtss_state->clock.dpll_conf[dpll].mode;
    conf->holdoff     = vtss_state->clock.dpll_conf[dpll].holdoff;
    conf->holdover    = vtss_state->clock.dpll_conf[dpll].holdover;
    conf->wtr         = vtss_state->clock.dpll_conf[dpll].wtr;

    ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_ENA,    &rd_val);
    if ((conf->mode != VTSS_CLOCK_OPERATION_MODE_DISABLED && rd_val == 0) ||
        (conf->mode == VTSS_CLOCK_OPERATION_MODE_DISABLED && rd_val != 0)) {
        VTSS_E("SW and HW state for dpll_conf->mode do not match\n");
        result = VTSS_RC_ERROR;
    }

    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_TIMING_CFG0, dpll, CTRL_HOLD_OFF_TIME, &rd_val);
    if (rd_val != vtss_state->clock.dpll_conf[dpll].holdoff) {
        VTSS_E("SW and HW state for dpll_conf->holdoff do not match\n");
        result = VTSS_RC_ERROR;
    }

    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_TIMING_CFG1, dpll, CTRL_HOLD_OVER_TIME, &rd_val);
    if (rd_val != vtss_state->clock.dpll_conf[dpll].holdover) {
        VTSS_E("SW and HW state for dpll_conf->holdover do not match\n");
        result = VTSS_RC_ERROR;
    }

    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_TIMING_CFG1, dpll, CTRL_WAIT_TO_RESTORE_TIME, &rd_val);
    if (rd_val != vtss_state->clock.dpll_conf[dpll].wtr) {
        VTSS_E("SW and HW state for dpll_conf->wtr do not match\n");
        result = VTSS_RC_ERROR;
    }
    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_TIMING_CFG0, dpll, CTRL_INI_QUAL_TIME,        &rd_val);
    if (rd_val != vtss_state->clock.dpll_conf[dpll].wtr) {
        VTSS_E("SW and HW state for dpll_conf->wtr do not match when used for initial qualification time\n");
        result = VTSS_RC_ERROR;
    }

    return result;
}

/* Set holdover stack configuration */
static vtss_rc es6514_clock_ho_stack_conf_set(vtss_state_t                       *vtss_state,
                                              const vtss_clock_dpll_inst_t      dpll,
                                              const vtss_clock_ho_stack_conf_t  *const conf)
{
    u8 ho_filtshft = 27;
    u8 ho_filtcoef;
    u8 ho_filtdecim;
    u32 omega_svn_id;

    ES6514_RD(OMG_MAIN, OMG_MAIN_OMG_SVN_ID, &omega_svn_id);
    if (vtss_state->clock.ho_stack_conf[dpll].ho_post_filtering_bw != conf->ho_post_filtering_bw) {
        while ((((u64)(conf->ho_post_filtering_bw) << ho_filtshft) > ((u64)3110000 * 1000 * 15)) &&  (ho_filtshft > 5)) {
            ho_filtshft--;
        }
        ho_filtcoef = VTSS_DIV64(((u64)conf->ho_post_filtering_bw << ho_filtshft), 311000000); 
        ho_filtcoef = (ho_filtcoef+5)/10; /* rounding */
        if (ho_filtcoef == 0) {
            ho_filtcoef = 1;
        }
        if (ho_filtcoef > 15) {
            VTSS_E("Value for ho_post_filtering_bw is too high\n");
            return VTSS_RC_ERROR;
        }
        ho_filtshft  -= 5;
        ho_filtdecim  = 0;
        if (omega_svn_id <= 0xa460) {
            /* !! Bugzilla #15547 only relevant for es6514: ho_filtshft must NOT be above 10 */
            if (ho_filtshft > 10) {
                ho_filtdecim = ho_filtshft - 10;
            }
        } else {
            if (ho_filtshft > 15) {
                ho_filtdecim = ho_filtshft - 15;
            }
        }
        ho_filtshft -= ho_filtdecim;
        if(ho_filtdecim > 7) {
            /* ho_filtdecim exceeds allowed range, we have to reduce ho_filtcoef to get to a valid configuration*/
            ho_filtdecim = 7;
            ho_filtcoef  = VTSS_DIV64(((u64)conf->ho_post_filtering_bw << (5 + ho_filtshft + ho_filtdecim)), 311000000); 
            ho_filtcoef = (ho_filtcoef+5)/10; /* rounding */
            if (ho_filtcoef == 0) {
                ho_filtcoef = 1;
            }
        }
        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_LPF_DECIMPWR, ho_filtdecim);
        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_LPF_FILTSHFT, ho_filtshft);
        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_LPF_FILTCOEF, ho_filtcoef);
    }

    if (vtss_state->clock.ho_stack_conf[dpll].ho_qual_time_conf != conf->ho_qual_time_conf) {
        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_MIN_FILL_LVL, conf->ho_qual_time_conf);
        if (vtss_state->clock.ho_stack_conf[dpll].ho_qual_time_conf < conf->ho_qual_time_conf) {
            // when increasing the ho_qual_time_conf the ho_sel follows the ho_min_fill_lvl, otherwise it is kept unchanged
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_SEL,          conf->ho_qual_time_conf);
        }
        /* Bugzilla: #15547 a device different from es6514 which does not have the shifting bugs should also configure */
        if (omega_svn_id >  0xa460) {
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_AVG_CFG, 1);
        }
    }

    vtss_state->clock.ho_stack_conf[dpll].ho_post_filtering_bw = conf->ho_post_filtering_bw;
    vtss_state->clock.ho_stack_conf[dpll].ho_qual_time_conf    = conf->ho_qual_time_conf;

    return VTSS_RC_OK;
}


/* Get holdover stack configuration */
static vtss_rc es6514_clock_ho_stack_conf_get(vtss_state_t                       *vtss_state,
                                              const vtss_clock_dpll_inst_t      dpll,
                                              vtss_clock_ho_stack_conf_t        *const conf)
{
    u32 rd_val;
    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_MIN_FILL_LVL, &rd_val);
    if(rd_val != vtss_state->clock.ho_stack_conf[dpll].ho_qual_time_conf) {
        VTSS_E("SW and HW state for ho_qual_time_conf do not match\n");
        return VTSS_RC_ERROR;
    }
    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_SEL, &rd_val);
    if(rd_val != vtss_state->clock.ho_stack_conf[dpll].ho_qual_time_conf && 0 != vtss_state->clock.ho_stack_conf[dpll].ho_qual_time_conf) {
        VTSS_E("SW and HW state for ho_qual_time_conf do not match\n");
        return VTSS_RC_ERROR;
    }

    conf->ho_post_filtering_bw = vtss_state->clock.ho_stack_conf[dpll].ho_post_filtering_bw;
    conf->ho_qual_time_conf    = rd_val;

    return VTSS_RC_OK;
}

/* Get holdover stack content */
static vtss_rc es6514_clock_ho_stack_content_get(vtss_state_t                       *vtss_state,
                                              const vtss_clock_dpll_inst_t          dpll,
                                              vtss_clock_ho_stack_content_t         *const cont)
{
    u32 rd_val, rd_val_msb;
    u32 fill_level;
    i64 stack_value;
    for (fill_level = 0; fill_level < VTSS_CLOCK_HO_STACK_SIZE; fill_level++) {
        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG,   dpll, CTRL_HO_RD_ADDR,          fill_level);
        ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG,   dpll, CTRL_HO_RD_STRB_ONE_SHOT, 1);
        ES6514_RDX( OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_STAT0, dpll,                           &rd_val);
        ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_STAT1, dpll, CTRL_HO_RD_DATA_HIGH,     &rd_val_msb);
        es6514_delta_f_to_scaled_ppb(rd_val_msb, rd_val, &stack_value);
        // cont->stack_value[fill_level] is kept as an unsigned to keep backwards compatibility
        cont->stack_value[fill_level] = (u64)stack_value;
    }

    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_MIN_FILL_LVL, &rd_val);
    cont->ho_min_fill_lvl = rd_val;
    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_SEL, &rd_val);
    cont->ho_sel = rd_val;
    ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, dpll, CTRL_HO_FILLED, &rd_val);
    cont->ho_filled = rd_val;

    return VTSS_RC_OK;
}

/* Set Clock dpll frequency dco frequency offset */
static vtss_rc es6514_clock_dco_frequency_offset_set(vtss_state_t                  *vtss_state,
                                                     const vtss_clock_dpll_inst_t    dpll,
                                                     const i64                       offset)
{
    i64   conf_value;
    i64   limit;
    i64   my_offset;
    u8    conf_value_h;
    u32   conf_value_l;

    if (vtss_state->clock.dco_frequency_offset[dpll] != offset) {
        my_offset = offset + vtss_state->clock.dco_ho_offset[dpll];
        /* value should be: 7 * 2**32 * 1024 / 1e9 / 2**16 * offset */
        /* 1e9 = 1953125 * 2**9 */
        /* 1024 = 2**10 */
        /* 32 + 10 - 16 - 9 = 17 */

        limit = ((i64)1 << (63 - 17)) / 7;
        if (my_offset >= limit) {
            VTSS_E("selected value for offset is too high\n");
            return VTSS_RC_ERROR;
        } else if( my_offset <= -1 * limit) {
            VTSS_E("selected value for offset is too low\n");
            return VTSS_RC_ERROR;
        } 
        conf_value = 7 * ((i64)1 << 17) * my_offset / 1953125;
        limit = 7 * ((i64)1 << 32);
        if (conf_value > limit) {
            VTSS_E("conf_value is too high\n");
            return VTSS_RC_ERROR;
        } else if ( conf_value < -1 * limit ) {
            VTSS_E("conf_value is too low\n");
            return VTSS_RC_ERROR;
        }
        conf_value_h = (conf_value >> 32) & 0xf;
        conf_value_l = conf_value & 0xffffffff;
        ES6514_WRX(OMG_MAIN,  OMG_CTRL_OMG_CTRL_DF_FRM0, dpll,                         conf_value_l);
        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_HIGH,            conf_value_h);
        ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_UPDATE_ONE_SHOT,            1);

        vtss_state->clock.dco_frequency_offset[dpll] = offset;
    }

    return VTSS_RC_OK;
}

/* Get Clock dpll frequency adjustment. */
static vtss_rc es6514_clock_dco_frequency_offset_get(vtss_state_t                  *vtss_state,
                                                     const vtss_clock_dpll_inst_t  dpll,
                                                     i64                           *const offset)
{
    *offset =  vtss_state->clock.dco_frequency_offset[dpll];

    return VTSS_RC_OK;
}

/* Set Output Filter Bandwidth */
static vtss_rc es6514_clock_output_filter_bw_set(vtss_state_t                       *vtss_state,
                                                 const u8                           clock_output,
                                                 const u32                          bw_100uhz)
{
    const u32 core_freq     = 312500000; /* 312.5 MHz */
    const u32 pi_times_2p6  = 201;    /* PI * 2^6 */
    const u64 f_cut_off_1uhz_x2p32 = ((u64)core_freq * 10000) / pi_times_2p6; /* cut of frequncy in units of 100uHz multiplied by 2^32 */  
    const u32 tgt = VTSS_TO_SD10G65(clock_output);
    u8 i;
    u8 i_gr_1;
    u32 decoded_i;
    u32 current_f_cut;
    u32 last_f_cut = 0;
    u32 decision_threshold;

    if (vtss_state->clock.output_filter_bw[clock_output] != bw_100uhz) {
        if (bw_100uhz == 0) {
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_ENA, 0);
        } else {
            for(i=1; i<54;i++) {
                i_gr_1 = ((i >> 1) > 0) ? 1 : 0;
                decoded_i = (1 << (i >> 1)) + ((((i%2) * i_gr_1) << ((i >> 1) -1)));
                current_f_cut = (u32)((decoded_i * f_cut_off_1uhz_x2p32) >> 32);
                decision_threshold = (current_f_cut + last_f_cut) / 2;
                if (decision_threshold > bw_100uhz) {
                    /* FSEL for the filter and for the DF2F must be identical ! */
                    ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_SSC_CFG1, tgt, SYNC_CTRL_FSEL,  i-1);
                    ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_F_SEL, i-1);
                    ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_ENA, 1);
                    ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_CLR, 1);
                    ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_CLR, 0);
                    vtss_state->clock.output_filter_bw[clock_output] = bw_100uhz;
                    return VTSS_RC_OK;
                }
                last_f_cut = current_f_cut;
            }
            ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_F_SEL, 53);
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_ENA, 1);
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_CLR, 1);
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_CLR, 0);
        }
        vtss_state->clock.output_filter_bw[clock_output] = bw_100uhz;
    }
    return VTSS_RC_OK;
}

/* Get Output Filter Bandwidth */
static vtss_rc es6514_clock_output_filter_bw_get(vtss_state_t                       *vtss_state,
                                                 const u8                           clock_output,
                                                 u32                                *bw_100uhz)
{
    *bw_100uhz = vtss_state->clock.output_filter_bw[clock_output];
    return VTSS_RC_OK;
}


/* Trigger Output Filter to do a fast lock */
static vtss_rc es6514_clock_output_filter_lock_fast_set(vtss_state_t                       *vtss_state,
                                                        const u8                           clock_output)
{
    ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_SYNC_MODE,     0);
    ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_SYNC_ONE_SHOT, 1);
    /* Shortly enable the sync timer so that the new filter value is transfered to the DF2F */
    ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_SC,   clock_output, FILT_SC_SYNC_TIMER_SEL, 8);
    ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_SC,   clock_output, FILT_SC_SYNC_TIMER_SEL, 0);
    return VTSS_RC_OK;
}

/* Check, if fast lock has completed */
static vtss_rc es6514_clock_output_filter_lock_fast_get(vtss_state_t                       *vtss_state,
                                                        const u8                           clock_output,
                                                        BOOL                               *lock_completed)
{
    u32   rd_val;
    ES6514_RDXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_SYNC_ONE_SHOT, &rd_val);
    *lock_completed = (rd_val == 0) ? TRUE : FALSE;
    return VTSS_RC_OK;
}


/* Set Phase Slope Limit (PSL) */
static vtss_rc es6514_clock_output_psl_conf_set(vtss_state_t                       *vtss_state,
                                                const u8                           clock_output,
                                                const vtss_clock_psl_conf_t        *const conf)
{
    u64 limit_df; /* limit in units of deltaf i.e. integ2 units */
    u8  a, b;
    u16 cfg_val;

    if (vtss_state->clock.psl_conf[clock_output].limit_ppb != conf->limit_ppb) {
        if (conf->limit_ppb == 0) {
            /* Feature disaled */
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, clock_output, PSL_ENA, 0);
            vtss_state->clock.psl_conf[clock_output].limit_ppb = 0;
        } else if (conf->limit_ppb > 524000) {
            // chip supports up to 977000 ppb, but values >524000 will cause overflow in the calculation of limit_df
            VTSS_D("Selected value %u for psl_conf.limit_ppb is too high\n", conf->limit_ppb);
            return VTSS_RC_ERROR;
        } else {
            limit_df = VTSS_DIV64(((u64)7 << 42) * conf->limit_ppb, 1000000000LL);
            b = 20;
            while ( (limit_df >> (b - 1)) >= 63 ) {
              b++;
            }
            a = (limit_df >> b) + 
              ((limit_df >> (b-1)) & 1); /* round */
            cfg_val = (a << 5) + b;
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, clock_output, PSL_ENA, 1);
            ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, clock_output, PSL_LIMIT, cfg_val);
            vtss_state->clock.psl_conf[clock_output].limit_ppb = conf->limit_ppb;
        }
    }

    if (vtss_state->clock.psl_conf[clock_output].phase_build_out_ena != conf->phase_build_out_ena) {
        if(conf->phase_build_out_ena == TRUE) {
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, clock_output, PSL_PHS_BUILD_OUT_ENA, 1);
        } else {
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, clock_output, PSL_PHS_BUILD_OUT_ENA, 0);
        } 
        vtss_state->clock.psl_conf[clock_output].phase_build_out_ena = conf->phase_build_out_ena;
    }

    if (vtss_state->clock.psl_conf[clock_output].ho_based != conf->ho_based) {
        if(conf->ho_based == TRUE) {
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, clock_output, PSL_HO_BASED, 1);
        } else {
            ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, clock_output, PSL_HO_BASED, 0);
        }
        vtss_state->clock.psl_conf[clock_output].ho_based = conf->ho_based;
    }

    return VTSS_RC_OK;
}

/* Get Phase Slope Limit (PSL) */
static vtss_rc es6514_clock_output_psl_conf_get(vtss_state_t                       *vtss_state,
                                                const u8                           clock_output,
                                                vtss_clock_psl_conf_t              *const conf)
{
    u32  rd_val;

    u8   rd_bit;
    BOOL rd_bool;

    conf->limit_ppb = vtss_state->clock.psl_conf[clock_output].limit_ppb;

    ES6514_RDX(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, clock_output, &rd_val);

    rd_bit = ES6514_GET_BIT(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, PSL_PHS_BUILD_OUT_ENA, rd_val);
    if (rd_bit == 1) {
        rd_bool = TRUE;
    } else {
        rd_bool = FALSE;
    }
    if (rd_bool != vtss_state->clock.psl_conf[clock_output].phase_build_out_ena) {
        VTSS_E("SW and HW state for psl_conf->phase_build_out_ena, clock_output %u do not match\n", clock_output);
        return VTSS_RC_ERROR;
    } else {
        conf->phase_build_out_ena = vtss_state->clock.psl_conf[clock_output].phase_build_out_ena;
    }

    rd_bit = ES6514_GET_BIT(OMG_MAIN, OMG_FILT_OMG_FILTER_PSL, PSL_HO_BASED, rd_val);
    if (rd_bit == 1) {
        rd_bool = TRUE;
    } else {
        rd_bool = FALSE;
    }
    if (rd_bool != vtss_state->clock.psl_conf[clock_output].ho_based) {
        VTSS_E("SW and HW state for psl_conf->psl_ho_based, clock_output %u do not match\n", clock_output);
        return VTSS_RC_ERROR;
    } else {
        conf->ho_based = vtss_state->clock.psl_conf[clock_output].ho_based;
    }

    return VTSS_RC_OK;
}

/* Set Clock dpll frequency adjustment. */
static vtss_rc es6514_clock_adj_frequency_set(vtss_state_t                  *vtss_state,
                                              const u8                      clock_output,
                                              const i64                     adj)
{
    i64   conf_value;
    i64   limit;
    u8    conf_value_h;
    u32   conf_value_l;

    if (vtss_state->clock.adj_frequency[clock_output] != adj) {
        /* value should be: 7 * 2**32 * 1024 / 1e9 / 2**16 * adj */
        /* 1e9 = 1953125 * 2**9 */
        /* 1024 = 2**10 */
        /* 32 + 10 - 16 - 9 = 17 */

        limit = ((i64)1 << (63 - 17)) / 7;
        if (adj >= limit) {
            VTSS_E("selected value for adj is too high\n");
            return VTSS_RC_ERROR;
        } else if( adj <= -1 * limit) {
            VTSS_E("selected value for adj is too low\n");
            return VTSS_RC_ERROR;
        } 
        conf_value = 7 * ((i64)1 << 17) * adj / 1953125;
        limit = 7 * ((i64)1 << 32);
        if (conf_value > limit) {
            VTSS_E("conf_value is too high\n");
            return VTSS_RC_ERROR;
        } else if ( conf_value < -1 * limit ) {
            VTSS_E("conf_value is too low\n");
            return VTSS_RC_ERROR;
        }
        conf_value_h = (conf_value >> 32) & 0xf;
        conf_value_l = conf_value & 0xffffffff;
        ES6514_WRX(OMG_MAIN,  OMG_FILT_OMG_FILTER_DCO_LOW,  clock_output,                     conf_value_l);
        ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_DCO_HIGH, clock_output, DCO_HIGH,           conf_value_h);
        ES6514_WRXB(OMG_MAIN, OMG_FILT_OMG_FILTER_DCO_HIGH, clock_output, DCO_UPDATE_ONE_SHOT,           1);

        vtss_state->clock.adj_frequency[clock_output] = adj;
    }

    return VTSS_RC_OK;
}

/* Get Clock dpll frequency adjustment. */
static vtss_rc es6514_clock_adj_frequency_get(vtss_state_t                  *vtss_state,
                                              const u8                      clock_output,
                                              i64                           *const adj)
{
    *adj =  vtss_state->clock.adj_frequency[clock_output];

    return VTSS_RC_OK;
}

/* Set Clock dpll phase adjustment. */
static vtss_rc es6514_clock_adj_phase_set(vtss_state_t                  *vtss_state,
                                          const u8                      clock_output,
                                          const i32                     adj)
{
    vtss_rc rc = VTSS_RC_OK;
    u32   rd_val;
    u32   f_offset_ppb;
    u8    cfg_val;
    /* u32   output_freq_khz; */
    /* u32   delta_t_per_cycle_as; */ /* delta T per clock cycle in atto seconds */
    /* u64   num_hs_cycles; */
    u64   num_core_clock_cycles;
    u64   num_cycles_tmp;
    u32   adj_val = VTSS_LABS(adj);
    u8    adj_dir = (adj > 0) ? (1) : (0);
    u8    heart_beat_sel;
    u16   timer_cfg;
    u32 current_limit_ppb;
    int clock_idx;
    ES6514_RDB(OMG_MAIN, OMG_PSG_OMG_PS_GEN_MAIN_CFG, PSG_ONE_SHOT, &rd_val);
    if (rd_val != 0) {
        VTSS_E("Phase Shift generator busy\n");
        return VTSS_RC_ERROR;
    }
    /* find the lowest PSL value for the affected clock outputs */
    current_limit_ppb = vtss_state->clock.phase_shift_max_freq_offset;
    for (clock_idx = 0; clock_idx < OUTPUT_CNT; clock_idx++) {
        if (vtss_state->clock.psl_conf[clock_idx].limit_ppb > 0 && vtss_state->clock.psl_conf[clock_idx].limit_ppb < current_limit_ppb && (clock_output & (1<<clock_idx))) {
            current_limit_ppb = vtss_state->clock.psl_conf[clock_idx].limit_ppb;
        }
    }

    /* find config value for max frequency for phase shift */
    /* we can start with a cfg_val of 14 since lower numbers will always fail */
    for (cfg_val = 14; cfg_val < 34; cfg_val++) {
        /* Bitgroup description: f_offset [ppm] = DCO / (7 * 2**32) * 1e6/1024 ppm */
        f_offset_ppb = (u32)(VTSS_DIV64(((u64)1 << (cfg_val + 1)) * 1000000000, 7) >> (32 + 10));
        if(f_offset_ppb > current_limit_ppb) {
            break;
        }
    }
    f_offset_ppb = (u32)(VTSS_DIV64(((u64)1 << cfg_val) * 1000000000, 7) >> (32 + 10));
    VTSS_I("current_limit_ppb %u, f_offset_ppb %u, cfg_val %u\n", current_limit_ppb, f_offset_ppb, cfg_val);

    if (f_offset_ppb == 0) {
        /* Coverity finding. In case cfg_val is 14 which is theoretically possible, then f_offset_ppb is evaluated to zero */
        /* In the following f_offset_ppb is used as denominator - dividing by zero */
        VTSS_D("f_offset_ppb == 0");
        return VTSS_RC_ERROR;
    }

    /* rc = es6514_clock_output_frequency_get(vtss_state, clock_output, &output_freq_khz, &par_output_freq_khz); */
    /* if ((output_freq_khz < 1000) || (output_freq_khz > 250000)) {                                    */
    /*     VTSS_E("Invalid output frequncy %u detected\n", output_freq_khz);                            */
    /*     return VTSS_RC_ERROR;                                                                        */
    /* }                                                                                                */  
    /* delta_t_per_cycle_as = (u32)(VTSS_DIV64((u64)f_offset_ppb * 1000000, output_freq_khz));          */
    /* num_hs_cycles = VTSS_DIV64((u64)adj_val * 1000000000, (((u64)1 << 16) * delta_t_per_cycle_as));  */
    /* num_core_clock_cycles = VTSS_DIV64((num_hs_cycles * 312500), output_freq_khz);                   */

    /* The above 8 calculation lines can be simplified to the single line below */
    num_core_clock_cycles = (VTSS_DIV64((u64)adj_val * 9765625, f_offset_ppb)) >> 11;

    /* PSG_TIMER_CFG has 16 bit. Now check what can be configured in PSG_TIMER_CFG and what we have to push to PSG_HEART_BEAT_SEL_CFG */
    num_cycles_tmp = num_core_clock_cycles >> 15;
    heart_beat_sel = 0;
    while (num_cycles_tmp > 0) {
        num_cycles_tmp = num_cycles_tmp >> 1;
        heart_beat_sel++;
    }
    timer_cfg = (u16)((num_core_clock_cycles >> heart_beat_sel) +
                      ((num_core_clock_cycles >> (heart_beat_sel ? (heart_beat_sel-1):0)) & 0x1)); /* rounding */
    /*                                                                                             <-  num core clock cycles   -> <-core_clock_peri-> <- freq_offset -> */
    VTSS_I("Resulting phase shift after scaling to HW capabilities will be %" PRIi64 " as\n", VTSS_DIV64((((u64)timer_cfg << heart_beat_sel) *      3200         * f_offset_ppb) , 1000));
    
    ES6514_WRF(OMG_MAIN, OMG_PSG_OMG_PS_GEN_MAIN_CFG,  PSG_FREQ_OFFS_VAL_CFG,  cfg_val);
    ES6514_WRB(OMG_MAIN, OMG_PSG_OMG_PS_GEN_MAIN_CFG,  PSG_FREQ_OFFS_SIGN_CFG, adj_dir);
    ES6514_WRF(OMG_MAIN, OMG_PSG_OMG_PS_GEN_MAIN_CFG,  PSG_LANE_ENA_CFG,       clock_output);
    ES6514_WRF(OMG_MAIN, OMG_PSG_OMG_PS_GEN_TIMER_CFG, PSG_HEART_BEAT_SEL_CFG, heart_beat_sel);
    ES6514_WRF(OMG_MAIN, OMG_PSG_OMG_PS_GEN_TIMER_CFG, PSG_TIMER_CFG,          timer_cfg);
    ES6514_WRB(OMG_MAIN, OMG_PSG_OMG_PS_GEN_MAIN_CFG,  PSG_ENA,                1);    
    ES6514_WRB(OMG_MAIN, OMG_PSG_OMG_PS_GEN_MAIN_CFG,  PSG_ONE_SHOT,           1);    
    
    return rc;
}

/* Get Clock dpll phase adjustment. */
static vtss_rc es6514_clock_adj_phase_get(vtss_state_t                  *vtss_state,
                                          BOOL                          *const adj_ongoing)
{
    u8 rd_val;
    ES6514_RDB(OMG_MAIN, OMG_PSG_OMG_PS_GEN_MAIN_CFG, PSG_ONE_SHOT, &rd_val);
    *adj_ongoing = (rd_val != 0) ? TRUE : FALSE;

    /* Jt: Should we also check, if PSG_LANE_ENA_CFG for the repective clock_output is set? */
    return VTSS_RC_OK;
}

/* Set Clock input priority. */
static vtss_rc es6514_clock_priority_set(vtss_state_t                         *vtss_state,
                                         const vtss_clock_dpll_inst_t         dpll,
                                         const u8                             clock_input,
                                         const vtss_clock_priority_selector_t *const conf)
{
    u8  enable_as_int;
    u32 rd_val;
    u8  rd_sel;
    u8  rd_ena;
    u8  ena[4];
    u8  disable[4] = {0, 0, 0, 0};
    u8  ctrl_eec_state;
#if VTSS_OPT_TRACE
    u8  ctrl_eec_src_sel;
#endif
    u8  ctrl_inp_src_sel;
    u8  forced_flag = 0;

    enable_as_int = (conf->enable == TRUE) ? 1 : 0;
    if (conf->enable == TRUE) {
        switch (conf->priority){
        case 0: {
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_SEL, clock_input);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_ENA, enable_as_int);
            if (vtss_state->clock.selection_conf[dpll].mode == VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE) {
                /* Bugzilla 17881 Disable Auto-switch-back when prio 0 is disabled */
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_AUTO_SWITCH_BACK, 1);
                if(vtss_state->clock.emulated_ho_state[dpll] == TRUE) {
                    /* In case we are still pre locked_mode_ho restart the selection process to directly select the Prio0 source*/
                    ES6514_RDX(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, dpll, &rd_val);
                    ctrl_eec_state = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_EEC_STATE,   rd_val);
                    if (ctrl_eec_state < 4) {
                        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 1);
                        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 3);
                    }
                }
            }
            break;
        }
        case 1: {
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO1_SEL, clock_input);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO1_ENA, enable_as_int);
            break;
        }
        case 2: {
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO2_SEL, clock_input);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO2_ENA, enable_as_int);
            break;
        }
        case 3: {
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO3_SEL, clock_input);
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO3_ENA, enable_as_int);
            break;
        }
        default: {
            VTSS_E("Illegal value %u for priority\n", conf->priority);
            return VTSS_RC_ERROR;
        }
        } /* switch (priority) */

        /* Go through all other priorities and check whether the respective input is enabled on one of the priorities */
        /* If so, disable it since it will now be enabled on another priority */
        ES6514_RDX(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, &rd_val);
        /* prio 0 */
        if(conf->priority != 0) {
            rd_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO0_SEL, rd_val);
            rd_ena = ES6514_GET_BIT(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO0_ENA, rd_val);
            if ((rd_sel == clock_input) && (rd_ena == 1)) {
                 ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_ENA, 0);
                /* Bugzilla 17881 Disable Auto-switch-back when prio 0 is disabled */
                if (vtss_state->clock.selection_conf[dpll].mode == VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE) {
                    ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_AUTO_SWITCH_BACK, 0);
                }
            }
        }
        /* prio 1 */
        if(conf->priority != 1) {
            rd_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO1_SEL, rd_val);
            rd_ena = ES6514_GET_BIT(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO1_ENA, rd_val);
            if ((rd_sel == clock_input) && (rd_ena == 1)) {
                 ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO1_ENA, 0);
            }
        }
        /* prio 2 */
        if(conf->priority != 2) {
            rd_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO2_SEL, rd_val);
            rd_ena = ES6514_GET_BIT(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO2_ENA, rd_val);
            if ((rd_sel == clock_input) && (rd_ena == 1)) {
                 ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO2_ENA, 0);
            }
        }
        /* prio 3 */
        if(conf->priority != 3) {
            rd_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO3_SEL, rd_val);
            rd_ena = ES6514_GET_BIT(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO3_ENA, rd_val);
            if ((rd_sel == clock_input) && (rd_ena == 1)) {
                 ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO3_ENA, 0);
            }
        }
    } else {
        /* conf->enable is false */
        /* disregard the priority and disable the port on all priorities */
        ES6514_RDX(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, &rd_val);
        ena[0] = ES6514_GET_BIT(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO0_ENA, rd_val);
        ena[1] = ES6514_GET_BIT(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO1_ENA, rd_val);
        ena[2] = ES6514_GET_BIT(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO2_ENA, rd_val);
        ena[3] = ES6514_GET_BIT(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO3_ENA, rd_val);

        rd_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO0_SEL, rd_val);
        if ((rd_sel == clock_input) && (ena[0] == 1)) {
             ena[0] = 0;
             disable[0] = 1;
        }

        rd_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO1_SEL, rd_val);
        if ((rd_sel == clock_input) && (ena[1] == 1)) {
             ena[1] = 0;
             disable[1] = 1;
        }

        rd_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO2_SEL, rd_val);
        if ((rd_sel == clock_input) && (ena[2] == 1)) {
             ena[2] = 0;
             disable[2] = 1;
        }

        rd_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, CTRL_REFSEL_PRIO3_SEL, rd_val);
        if ((rd_sel == clock_input) && (ena[3] == 1)) {
             ena[3] = 0;
             disable[3] = 1;
        }

        /* Workaround for Bugzilla 17813, check if the disabled port is the currently selected port*/ 
        /* If so: Copy current HO value to DF value for free_run mode and restart the selection FSM */
        if ((vtss_state->clock.selection_conf[dpll].mode == VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_NONREVERTIVE) ||
            (vtss_state->clock.selection_conf[dpll].mode == VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE)) {
            ES6514_RDX(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, dpll, &rd_val);
            ctrl_inp_src_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_INP_SRC_SEL, rd_val);
#if VTSS_OPT_TRACE
            ctrl_eec_src_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_EEC_SRC_SEL, rd_val);
#endif
            ctrl_eec_state   = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_EEC_STATE,   rd_val);
            VTSS_I("dpll %d, clock_input %d, ctrl_inp_src_sel %d, ctrl_eec_src_sel %d, ctrl_eec_state %d", dpll, clock_input, ctrl_inp_src_sel, ctrl_eec_src_sel, ctrl_eec_state);
            if (ctrl_inp_src_sel == clock_input) {
                /* Check if we already have reached one of the HO states and copy the HO stack value to the DF value */
                if (ctrl_eec_state > 3) {
                    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG,   dpll, CTRL_HO_RD_ADDR,          vtss_state->clock.ho_stack_conf[dpll].ho_qual_time_conf);
                    ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG,   dpll, CTRL_HO_RD_STRB_ONE_SHOT, 1);
                    ES6514_RDX( OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_STAT0, dpll,                           &rd_val);
                    ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0,        dpll,                           rd_val);
                    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_STAT1, dpll, CTRL_HO_RD_DATA_HIGH,     &rd_val);
                    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1,        dpll, DF_FRM_HIGH,              rd_val);
                    ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1,        dpll, DF_FRM_UPDATE_ONE_SHOT,   1);

                    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 1);
                    forced_flag = 1;
                    vtss_state->clock.emulated_ho_state[dpll] = TRUE;
                } else {
                    /* If we are in locked_mode_acq waiting to get to locked_mode_ho and the port gets disabled we have to restart the search for a valid port */
                    /* Switch to force free run mode and immediatly after that switch back to auto mode */
                    ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 1);
                    forced_flag = 1;
                }
            }
        }


        if (disable[0] == 1) {
            ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_ENA, 0);
            /* Bugzilla 17881 Disable Auto-switch-back when prio 0 is disabled */
            if (vtss_state->clock.selection_conf[dpll].mode == VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE) {
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_AUTO_SWITCH_BACK, 0);
            }
        }
        if (disable[1] == 1) {
             ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO1_ENA, 0);
        }
        if (disable[2] == 1) {
             ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO2_ENA, 0);
        }
        if (disable[3] == 1) {
             ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO3_ENA, 0);
        }            

        /* Workaround for Bugzilla 17813, check if all sources are disabled */ 
        /* Switch back to auto mode */
        if (forced_flag == 1) {
            ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 3);
        }
        
    }

    vtss_state->clock.priority_selector[dpll][clock_input].priority = conf->priority;
    vtss_state->clock.priority_selector[dpll][clock_input].enable   = conf->enable;
    return VTSS_RC_OK;
}

/* Get Clock input priority. */
static vtss_rc es6514_clock_priority_get(vtss_state_t                    *vtss_state,
                                         const vtss_clock_dpll_inst_t    dpll,
                                         const u8                        clock_input,
                                         vtss_clock_priority_selector_t  *const conf)
{
    u8 rd_val;
    /* check for prio 0 */
    if ((vtss_state->clock.priority_selector[dpll][clock_input].priority == 0) &&
        (vtss_state->clock.priority_selector[dpll][clock_input].enable   == TRUE)) {
        ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_ENA,    &rd_val);
        if (rd_val == 1) {
            ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO0_SEL,    &rd_val);
            if (rd_val == clock_input) {
                conf->priority = 0; 
                conf->enable   = TRUE;
                return VTSS_RC_OK;
            } else {
                VTSS_E("SW and HW state for priority_selector dpll %u, clock_input %u, priority 0 do not match\n", dpll, clock_input);
                return VTSS_RC_ERROR;
            }
        } else {
            VTSS_E("SW and HW state for priority_selector dpll %u, clock_input %u, priority 0 do not match\n", dpll, clock_input);
            return VTSS_RC_ERROR;
        }
    /* check for prio 1 */
    } else if ((vtss_state->clock.priority_selector[dpll][clock_input].priority == 1) &&
               (vtss_state->clock.priority_selector[dpll][clock_input].enable   == TRUE)) {
        ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO1_ENA,    &rd_val);
        if (rd_val == 1) {
            ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO1_SEL,    &rd_val);
            if (rd_val == clock_input) {
                conf->priority = 1;
                conf->enable   = TRUE; 
                return VTSS_RC_OK;
            } else {
                VTSS_E("SW and HW state for priority_selector dpll %u, clock_input %u, priority 1 do not match\n", dpll, clock_input);
                return VTSS_RC_ERROR;
            }
        } else {
            VTSS_E("SW and HW state for priority_selector dpll %u, clock_input %u, priority 1 do not match\n", dpll, clock_input);
            return VTSS_RC_ERROR;
        }
    /* check for prio 2 */
    } else if ((vtss_state->clock.priority_selector[dpll][clock_input].priority == 2) &&
               (vtss_state->clock.priority_selector[dpll][clock_input].enable   == TRUE)) {
        ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO2_ENA,    &rd_val);
        if (rd_val == 1) {
            ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO2_SEL,    &rd_val);
            if (rd_val == clock_input) {
                conf->priority = 2;
                conf->enable   = TRUE; 
                return VTSS_RC_OK;
            } else {
                VTSS_E("SW and HW state for priority_selector dpll %u, clock_input %u, priority 2 do not match\n", dpll, clock_input);
                return VTSS_RC_ERROR;
            }
        } else {
            VTSS_E("SW and HW state for priority_selector dpll %u, clock_input %u, priority 2 do not match\n", dpll, clock_input);
            return VTSS_RC_ERROR;
        }
    /* check for prio 3 */
    } else if ((vtss_state->clock.priority_selector[dpll][clock_input].priority == 3) &&
               (vtss_state->clock.priority_selector[dpll][clock_input].enable   == TRUE)) {
        ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO3_ENA,    &rd_val);
        if (rd_val == 1) {
            ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, CTRL_REFSEL_PRIO3_SEL,    &rd_val);
            if (rd_val == clock_input) {
                conf->priority = 3;
                conf->enable   = TRUE; 
                return VTSS_RC_OK;
            } else {
                VTSS_E("SW and HW state for priority_selector dpll %u, clock_input %u, priority 3 do not match\n", dpll, clock_input);
                return VTSS_RC_ERROR;
            }
        } else {
            VTSS_E("SW and HW state for priority_selector dpll %u, clock_input %u, priority 3 do not match\n", dpll, clock_input);
            return VTSS_RC_ERROR;
        }
    }

    conf->enable   = FALSE; 

    return VTSS_RC_OK;
}

/* Set Clock input frequency with ratio. */
static vtss_rc es6514_clock_input_frequency_ratio_set(vtss_state_t                  *vtss_state,
                                                      const u8                      clock_input,
                                                      const u32                     freq_khz,
                                                      const vtss_clock_ratio_t      *const ratio,
                                                      const BOOL                    use_internal_clock_src)
{
    u32  tgt = VTSS_TO_SD10G65(clock_input);
    u32  dig_tgt = VTSS_TO_SD10G65_DIG(clock_input);
    u8   i;
    u32  rd_val;
    u8   side_detect;
    u8   interface_width;
    u8   side_detect_bit_sel;
    u8   ib_sig_det_clock_divider;
    BOOL found;
    u32  sample_freq_khz; /* sample frequency in kHz */
    u32  sample_freq_khz_w_ratio; /* sample frequency in kHz multiplied with ratio*/
    u32  ratio_num = ratio->num; /* ratio numerator */
    u32  ratio_den = ratio->den; /* ratio denominator */
    u32  freq_khz_w_ratio;
    u8   synth_speed_sel;
    u8   synth_fbdiv_sel;
    u8   synth_fb_step;
    u16  synth_freq_mult;
    u16  synth_freq_mult_wa;
    u8   synth_freq_mult_hi;
    u64  synth_freq_m;
    u64  synth_freq_n;
    u8   synth_freq_m_h;
    u8   synth_freq_n_h;
    u32  synth_freq_m_l;
    u32  synth_freq_n_l;
    u32  omega_svn_id;
    u32  rx_svn_id;

    if ((vtss_state->clock.input_frequency[clock_input]            != freq_khz) ||
        (vtss_state->clock.use_internal_clock_src[clock_input]     != use_internal_clock_src) ||
        (vtss_state->clock.input_frequency_ratio[clock_input].num  != ratio_num) ||
        (vtss_state->clock.input_frequency_ratio[clock_input].den  != ratio_den)) {
        freq_khz_w_ratio = (u32)(VTSS_DIV64((u64)freq_khz * ratio_num, ratio_den));
        if (freq_khz == 0) {
            /* Disable input */
            ES6514_WRXM_CLR(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, tgt, 
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_EQZ_ENA)     |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_SAM_ENA)     |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_IA_SDET_ENA) |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_IE_SDET_ENA) |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_IA_ENA)      |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_DFE_ENA));
            ES6514_WRXB(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2, tgt, PLL_ENA,     0);
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0, tgt, SYNTH_ENA,   0);
            ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, clock_input,  QUAL_ENA,    0);
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT,         tgt, F2DF_ENABLE, 0);
            /* Disable internal clock source */
            /* internal clock source is bit 1 of spare pool */
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG0,             tgt, IB_SIG_SEL,      0);
            ES6514_RDXF(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_SPARE_POOL, &rd_val);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_SPARE_POOL, rd_val & ~2);
            ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG10,            tgt, IB_LOOP_REC,     0);
            /* Check if we are allowed to switch of the SBUS_BIAS_EN */
            if(vtss_state->clock.serdes_tx_en[clock_input] == FALSE) {
                ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG, tgt, SBUS_BIAS_EN,  0);
            };
            /* Bugzilla #16214 incorrect reference selection in controller if all reference inputs are invalid in ES6514*/
            ES6514_RD(OMG_MAIN, OMG_MAIN_OMG_SVN_ID, &omega_svn_id);
            if ((clock_input != 0) || (omega_svn_id > 0xa460)) {
                /* Do not disable channel0 qualifier */
                ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, clock_input, QUAL_ENA,    0);
                ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, clock_input, QUAL_SW_RST, 1);
            } else {
                ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, clock_input, QUAL_LOL_CTRL_ALARM_ENA, 1);
                vtss_state->clock.input_conf[clock_input].alarm_ena.lol   = TRUE;
            }
            vtss_state->clock.serdes_rx_en[clock_input] = FALSE;
        } else if (freq_khz_w_ratio < 1000) {
            VTSS_E("Selected frequency %u kHz with ratio %u/%u to low.  Must be at least 1000 kHz\n", freq_khz, ratio_num, ratio_den);
            return VTSS_RC_ERROR;
        } else if (freq_khz_w_ratio > 250000) {
            VTSS_E("Selected frequency %u kHz with ratio %u/%u to high.  Must be not above 250000 kHz\n", freq_khz, ratio_num, ratio_den);
            return VTSS_RC_ERROR;
        } else {

            if (vtss_state->clock.serdes_rx_en[clock_input] == TRUE) {
                /* The clock frequency is changed from a former value */
                /* Disable F2DF, to get the I2 value in the connected qualifier cleared */
                ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_ENABLE,                  0);
            }

            /* Disable APC in case it was setup previously */
            ES6514_WRXF(SD10G65_DIG, SD10G65_APC_APC_COMMON_CFG0, dig_tgt, APC_MODE,       0);
            ES6514_WRXB(SD10G65_DIG, SD10G65_APC_APC_COMMON_CFG0, dig_tgt, APC_DIRECT_ENA, 0);

            /* internal clock source is bit 1 of spare pool */
            ES6514_RDXF(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_SPARE_POOL, &rd_val);
            if (use_internal_clock_src == TRUE) {
                ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG0,             tgt, IB_SIG_SEL,       2);
                ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_SPARE_POOL, (rd_val |  2));
                ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG10,            tgt, IB_LOOP_REC,      1);
            } else {
                ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG0,             tgt, IB_SIG_SEL,       0);
                ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_SPARE_POOL, (rd_val & ~2));
                ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG10,            tgt, IB_LOOP_REC,      0);
            }

            /* setup the frequency in the F2DF */
            /* select interface width and sample divider to give sample frequency between 2.5 and 4 GBps */
            found = FALSE;
            side_detect = 0;
            while ((side_detect < 8) && (found == FALSE)) {
                interface_width = 16;
                if ((freq_khz_w_ratio * interface_width * (1 << side_detect)) >= 2500000) {
                    found = TRUE;
                } else {
                    interface_width = 20;
                    if ((freq_khz_w_ratio * interface_width * (1 << side_detect)) >= 2500000) {
                        found = TRUE;
                    }
                }
                if (found == FALSE) {
                    side_detect++;
                }
            }

            /* select side_detect_bit_sel dependent on the sampling divider and the interface width */
            if (side_detect == 0) {
                side_detect_bit_sel = interface_width >> 2;
            } else if (side_detect == 1) {
                side_detect_bit_sel = interface_width >> 1;
            } else {
                side_detect_bit_sel = 0;
            }
            sample_freq_khz = freq_khz * interface_width * (1 << side_detect);
            sample_freq_khz_w_ratio = (u32)VTSS_DIV64((u64)freq_khz * ratio_num * interface_width * (1 << side_detect), ratio_den);
            vtss_state->clock.input_sample_freq_khz[clock_input] = sample_freq_khz_w_ratio;
            VTSS_I("side_detect= %u, interface_width= %u, sample_freq_khz= %u", side_detect, interface_width, sample_freq_khz_w_ratio);

            /* Now setup the macro for the respective sample frequency */
            if (((u64)sample_freq_khz * ratio_num) < VTSS_DIV64((u64)10000000*ratio_den,3)) {
                /* sample frequncy below 3.33GHz -> use 2/3 * 2G5 .. 4/3 * 2G5 */
                es6514_calc_synth_settings(vtss_state, (u64)sample_freq_khz * ratio_num,  (u64)2500000 * ratio_den, &synth_freq_mult, &synth_freq_m, &synth_freq_n);
                synth_fbdiv_sel = 0;
                synth_fb_step   = 3;
            } else if(((u64)sample_freq_khz * ratio_num) <VTSS_DIV64((u64)2*10000000*ratio_den,3)) {
                /* sample frequncy between 3.33GHz and 6.66Ghz -> use 2/3 * 5G .. 4/3 * 5G */
                es6514_calc_synth_settings(vtss_state, (u64)sample_freq_khz * ratio_num,  (u64)5000000 * ratio_den, &synth_freq_mult, &synth_freq_m, &synth_freq_n);
                synth_fbdiv_sel = 1;
                synth_fb_step   = 2;
            } else  {
                /* sample frequncy between 6.66GHz and 13.33Ghz -> use 2/3 *10G .. 4/3 * 5G */
                es6514_calc_synth_settings(vtss_state, (u64)sample_freq_khz * ratio_num, (u64)10000000 * ratio_den, &synth_freq_mult, &synth_freq_m, &synth_freq_n);
                synth_fbdiv_sel = 2;
                synth_fb_step   = 0;
            }
            if ((u64)sample_freq_khz * ratio_num < ((u64)5000000 * ratio_den)) {
                synth_speed_sel = 1;
            } else {
                synth_speed_sel = 0;
            }

            synth_freq_m_h  = (u8)(synth_freq_m >> 32);
            synth_freq_n_h  = (u8)(synth_freq_n >> 32);
            synth_freq_m_l  = (u32)(synth_freq_m & 0xffffffff);
            synth_freq_n_l  = (u32)(synth_freq_n & 0xffffffff);


            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0, tgt, SYNTH_SPEED_SEL,    synth_speed_sel);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0, tgt, SYNTH_FBDIV_SEL,    synth_fbdiv_sel);
            /* SW workarround: Bypass the frequency decoder inside the SerDes and calculate improved settings manually */
            ES6514_RDX(SD10G65, SD10G65_IB_SD10G65_RX_SVN_ID, tgt, &rx_svn_id);
            if (rx_svn_id <= 43022) {
                es6514_calc_frec_dec_bypass(synth_freq_mult, &synth_freq_mult_wa, &synth_freq_mult_hi);
                ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT_BYP, 1);
                ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT_HI,  synth_freq_mult_hi);
                ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT,     synth_freq_mult_wa);
            } else {
                ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT_BYP, 0);
                ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT_HI,  4);
                ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT,     synth_freq_mult);
            }
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1, tgt, SYNTH_FREQM_1,      synth_freq_m_h);
            ES6514_WRX(SD10G65,  SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3, tgt,                     synth_freq_m_l);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1, tgt, SYNTH_FREQN_1,      synth_freq_n_h);
            ES6514_WRX(SD10G65,  SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4, tgt,                     synth_freq_n_l);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0, tgt, SYNTH_FB_STEP,      synth_fb_step);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0, tgt, SYNTH_I2_STEP,      0);
            /* End synthesizer setup part 1*/

            /* Configure IB */
            ES6514_WRXM_SET(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, tgt, 
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_CLKDIV_ENA)  |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_EQZ_ENA)     |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_SAM_ENA)     |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_DFE_ENA)     |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_LD_ENA)      |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_IA_SDET_ENA) |
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, IB_VBULK_SEL));
            VTSS_D("set up input clock frequency tgt = %x", tgt);
            ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG3, tgt, IB_SDET_SEL,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG5, tgt, IB_OFFS_VALUE, 31);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, tgt, IB_RCML_ADJ,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG0, tgt, IB_RIB_ADJ,     0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG8, tgt, IB_CML_CURR,    0);
            ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG5, tgt, IB_CALMUX_ENA,  0);
            ES6514_WRXM_CLR(SD10G65, SD10G65_IB_SD10G65_IB_CFG10, tgt, 
                            ES6514_MSK_BIT(SD10G65, SD10G65_IB_SD10G65_IB_CFG10, IB_LOOP_DRV));

            if (use_internal_clock_src == TRUE) {
                /* For internal clock sources the signal detect logic is not used as it sits in the IB which is partly bypassed */
                /* => Force signal detect value */
                ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG3, tgt, IB_SET_SDET, 1);
            } else {
                ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG3, tgt, IB_SET_SDET, 0);
                /* Configure Signal detect clock divider */
                /* Signal Detect checks for edges in a defined window */
                /* Window size is par_clock_period * 2^(2*IB_SDET_CLK_DIV+1) */
                /* With targeted sample frequency and interface width, the par_clock_period is between 125Mhz and 250MHz */
                /* We add a factor of 4 as security */
                if (freq_khz < 4000) {
                    ib_sig_det_clock_divider = 5;
                } else if (freq_khz < 16000) {
                    ib_sig_det_clock_divider = 4;
                } else if (freq_khz < 64000) {
                    ib_sig_det_clock_divider = 3;
                } else {
                    ib_sig_det_clock_divider = 2;
                }
                ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG3, tgt, IB_SDET_CLK_DIV,  ib_sig_det_clock_divider);
                ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG3, tgt, IB_IA_SDET_LEVEL, 2);
                /* Manually calibrate the IB */
                ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG5, tgt, IB_OFFS_VALUE,  32);
                for (i=0; i<4; i++) {
                   ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG5, tgt, IB_OFFS_BLKSEL,     i);
                   ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG5, tgt, IB_IA_OFFS_CAL_ENA,  1);
                   ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_IB_CFG5, tgt, IB_IA_OFFS_CAL_ENA,  0);
                }
            }
            
            /* Configure SBUS */
            ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG, tgt, SBUS_BIAS_EN,  1); /* Note!! In es6514 SBUS_BIAS_EN(N) is responisible for RX_N and TX_N */
                                                                                         /*        In rolex  SBUS_BIAS_EN(N) is responisible for RX_N and RX_N+1 (N=0,2,4,6...) */
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG, tgt, SBUS_BIAS_SPEED_SEL,  3);
            vtss_state->clock.serdes_rx_en[clock_input] = TRUE;

            /* Configure DES */
            ES6514_WRXF(SD10G65, SD10G65_DES_SD10G65_MOEBDIV_CFG0, tgt, MOEBDIV_BW_CDR_SEL_A, 3);
            ES6514_WRXF(SD10G65, SD10G65_DES_SD10G65_MOEBDIV_CFG0, tgt, MOEBDIV_BW_CDR_SEL_B, 3);
            ES6514_WRXB(SD10G65, SD10G65_DES_SD10G65_MOEBDIV_CFG0, tgt, MOEBDIV_CPMD_SWAP,    0);
            ES6514_WRXB(SD10G65, SD10G65_DES_SD10G65_MOEBDIV_CFG0, tgt, MOEBDIV_DIS,          0);
            ES6514_WRXF(SD10G65, SD10G65_DES_SD10G65_DES_CFG0,     tgt, DES_IF_MODE_SEL, es6514_get_iw_setting(vtss_state, interface_width)); 

            /* Configure improved RCPLL values found during validation tests*/
            ES6514_WRXF(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2, tgt, PLL_VCO_CUR,  7);
            ES6514_WRXF(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2, tgt, PLL_VREG18,  10);

            /* Configure Synthesizer (Part 2) */
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0,  tgt, SYNTH_ENA,           1);
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2,  tgt, SYNTH_AUX_ENA,       1);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2,  tgt, SYNTH_DV_CTRL_I2E,   0); /* Has to be set to 0. F2DF logic generates data valid in F2DF mode */
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0,  tgt, SYNTH_I2_ENA,        1);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2,  tgt, SYNTH_PHASE_DATA,   64);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2,  tgt, SYNTH_PHASE_AUX,    42);
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0,  tgt, SYNTH_P_STEP,        1);
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0,  tgt, SYNTH_I1_STEP,       1);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2,  tgt, SYNTH_DV_CTRL_I1E,   0);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2,  tgt, SYNTH_DV_CTRL_I1M,   0);
            /* Overwritten by F2DF setup later on 
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG1_FSEL,   2);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG1_LIM,    2);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG1_MAX1,   2);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG2_FSEL,  47);
            */

            /* Configure RC-PLL */
            /* Only write PLL_ENA required. The other registers already have correct default values */
            ES6514_WRXB(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2, tgt, PLL_ENA, 1);
            /* Keep as well default values for SD10G65_RX_RCPLL_CFG0 */
            /* Value should be (((u32)interface_width * 512) / ((sample_freq_khz * 8) / 1000000))); to avoid rounding errors this has been simplified to the below formula */
            ES6514_WRXF(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1, tgt, PLLF_REF_CNT_END, (((u32)interface_width * 64 * 1000000) / sample_freq_khz_w_ratio));
            /* Wait 2 us */
            VTSS_NSLEEP(2000);
            ES6514_WRXB(SD10G65, SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0, tgt, PLLF_ENA, 1);
            /* End of setup RX */

            /* Do some input buffer updates for SD10G running in F2DF mode */
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG2,  tgt,  IB_EQZ_GAIN,  400);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,     IB_AMP_L,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,    IB_EQZ_L0,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,    IB_EQZ_L1,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,    IB_EQZ_L2,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,     IB_AGC_L,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,     IB_AMP_C,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,    IB_EQZ_C0,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,    IB_EQZ_C1,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG1,  tgt,    IB_EQZ_C2,    0);
            ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_IB_CFG9,  tgt, IB_DFE_COEF1,   96);

            /* Now do the remaining of the f2df setup */
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG1_LIM,   11);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG1_MAX0,  11);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG1_MAX1,  11);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG1_FSEL,  15);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG2_FSEL,  vtss_state->clock.f2df_integ2_fsel);
#if defined(VTSS_ARCH_SERVAL_T)
            /* During testchip (ES6514) validation it turned out that a third integrator is needed to avoid a phase offset as result of a frequency offset change. */
            /* Unfortunately this late change could not be added to the csr2spi bridge in the digital part of the device. */
            /* Therefore the new bitgroups are only writable but not readable and my not be part of the register list. */
            /* Other designs may simply do: */
            /*    ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, SYNTH_INTEG3_ENA,  1);*/
            /* See also Bugzilla #17486 */
            ES6514_RDX(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, &rd_val);
            ES6514_WRX(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF, tgt, rd_val | (u32)1 << 31);
#endif //VTSS_ARCH_SERVAL_T

            if (es6514_check_pll_lock(vtss_state, rx, clock_input) == FALSE) {
                VTSS_E("RC-PLL was not able to get in lock\n");
                return VTSS_RC_ERROR;
            }
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_SIDE_DET_BIT_SEL,        side_detect_bit_sel);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_SIDE_DET_ONES_WEIGHT,    0);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_SIDE_DET_ZEROS_WEIGHT,   4);
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_TOG_DET_CNT,            40);
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_DATA_VALID_PROPPER_SIDE, 1);
            /* ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_STICKY_CLR,              0); */ /* DBG register */
            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_SAMPLE_DIV,              side_detect);
#if defined(VTSS_ARCH_SERVAL_T)
            ES6514_WRXF(HSIO, HW_CFGSTAT_TIMEX_CH_CFG, clock_input , LOL_SRC, 0xb);
#endif //VTSS_ARCH_SERVAL_T


            /* setup the OMG part */
            ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, clock_input, QUAL_ENA,    1);
            ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, clock_input, QUAL_SW_RST, 1);
            ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, clock_input, QUAL_SW_RST, 0);
            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_SCM_CFG, clock_input, QUAL_SCM_IFW, es6514_get_iw_setting(vtss_state, interface_width));

            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_I2_CFG,     clock_input, QUAL_CPFM_SET_FSEL,  vtss_state->clock.f2df_integ2_fsel); 

            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, clock_input, QUAL_CPFM_I1_SCALESHFT, 7);
            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, clock_input, QUAL_CPFM_I1_SCALECOEF, 560 * 1000000 / sample_freq_khz_w_ratio);

            /* Set I1 Low Pass filter cut off frequency to 1044Hz */
            /* Note: So far nobody has prooven that this is a good value */
            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, clock_input, QUAL_CPFM_I1_LPF_FILTSHFT, 15);
            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, clock_input, QUAL_CPFM_I1_LPF_FILTCOEF, 11);

            /* Set DF Low Pass filter cut off frequency to 95 Hz */
            /* Note: So far nobody has prooven that this is a good value */
            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, clock_input, QUAL_CPFM_DF_LPF_FILTSHFT, 18);
            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, clock_input, QUAL_CPFM_DF_LPF_FILTCOEF, 8);

            /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            /* !!                                                                                           !! */
            /* TBD The validation team must find better, maybe frequncy dependend, values for QUAL_CPFM_CF_MAX */
            /* For now use 50 ppm => config = 50 / 2.1287e-3 */
            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG,   clock_input, QUAL_CPFM_CF_MAX, 0x5bc1);
            /* !!                                                                                           !! */
            /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            /* Don't use the automode since we do not know, if the clock is availbel when we setup the input frequncy */
            ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_SCM_CFG, clock_input, QUAL_SCM_AUTOMODE_ENA, 0);
            ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_SCM_CFG, clock_input, QUAL_SCM_OBJC_CLK_PERIOD, sample_freq_khz / freq_khz);
            /* Clear the sticky bits */
            ES6514_WRXM_SET(OMG_MAIN, OMG_QUAL_OMG_QUAL_SCM_STAT, clock_input, 
                            ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_SCM_STAT, QUAL_SCM_NOISE_ERR_STICKY)     |
                            ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_SCM_STAT, QUAL_SCM_MIS_CLK_ERR_STICKY)   |
                            ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_SCM_STAT, QUAL_SCM_DUTY_CYCLE_ERR_STICKY));

            ES6514_WRXF(SD10G65, SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL, tgt, SYNTH_SC_SYNC_TIMER_SEL, 0);

            /* Finally enable the f2df FSM, this allows the that the I2 will be released */
            /* This command should be the last in the input frequency setup function     */
            ES6514_WRXB(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_ENABLE,                  1);


        }



        vtss_state->clock.input_frequency[clock_input]        = freq_khz;
        vtss_state->clock.use_internal_clock_src[clock_input] = use_internal_clock_src;
        vtss_state->clock.input_frequency_ratio[clock_input].num  = ratio_num;
        vtss_state->clock.input_frequency_ratio[clock_input].den  = ratio_den;
    }

    return VTSS_RC_OK;
}

/* Set Clock input frequency. */
static vtss_rc es6514_clock_input_frequency_set(vtss_state_t                  *vtss_state,
                                                const u8                      clock_input,
                                                const u32                     freq_khz,
                                                const BOOL                    use_internal_clock_src)
{
    vtss_clock_ratio_t ratio;
    ratio.num = 1;
    ratio.den = 1;
    es6514_clock_input_frequency_ratio_set(vtss_state, clock_input, freq_khz, &ratio, use_internal_clock_src);
    return VTSS_RC_OK;
}

/* Get Clock input frequency with ratio */
static vtss_rc es6514_clock_input_frequency_ratio_get(vtss_state_t                  *vtss_state,
                                                      const u8                      clock_input,
                                                      u32                           *const freq_khz,
                                                      vtss_clock_ratio_t            *const ratio,
                                                      BOOL                          *const use_internal_clock_src)
{
    u32  tgt = VTSS_TO_SD10G65(clock_input);
    u32  rd_val;
    *freq_khz               = vtss_state->clock.input_frequency[clock_input];
    ratio->num              = vtss_state->clock.input_frequency_ratio[clock_input].num;
    ratio->den              = vtss_state->clock.input_frequency_ratio[clock_input].den;
    /* internal clock source is bit 1 of spare pool */
    ES6514_RDXF(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG,         tgt, SBUS_SPARE_POOL, &rd_val);
    rd_val = (rd_val & 2) >> 1;
    *use_internal_clock_src = (rd_val == 1) ? TRUE : FALSE; 
    return VTSS_RC_OK;
}

/* Get Clock input frequency. */
static vtss_rc es6514_clock_input_frequency_get(vtss_state_t                  *vtss_state,
                                                const u8                      clock_input,
                                                u32                           *const freq_khz,
                                                BOOL                          *const use_internal_clock_src)
{
    vtss_clock_ratio_t ratio;
    es6514_clock_input_frequency_ratio_get(vtss_state, clock_input, freq_khz, &ratio, use_internal_clock_src);
    return VTSS_RC_OK;
}


/* Set Clock output frequency with ratio. */
static vtss_rc es6514_clock_output_frequency_ratio_set(vtss_state_t                  *vtss_state,
                                                       const u8                      clock_output,
                                                       const u32                     freq_khz,
                                                       const u32                     par_freq_khz,
                                                       const vtss_clock_ratio_t      *const ratio)
{
    u8   i;
    u32  tgt = VTSS_TO_SD10G65(clock_output);
    u32  dig_tgt = VTSS_TO_SD10G65_DIG(clock_output);
    u8   num_periods;
    u8   dft_word_mode;
    u8   num_words = 5;
    u8   num_bits;
    BOOL use_clock_gen = FALSE;
    u32  sample_freq_khz = 10000000;
    u32  ratio_num = ratio->num; /* ratio numerator */
    u32  ratio_den = ratio->den; /* ratio denominator */
    u32  freq_khz_w_ratio;
    u8   pattern[16] = { 0 };
    u8   toggle;
    u8   incr;
    u8   interface_width = 40;
    u8   clock_gen_period_half = 4;
    // u32  multiplier;  /* 1e9 eq. 1*/
    // u64  multiplier64;  /* 1 eq. 1e9 * 2^13*/
    u8   synth_speed_sel;
    u8   synth_fbdiv_sel;
    u8   synth_ls_speed;
    u8   synth_cs_speed;
    u8   synth_half_rate_mode = 0;
    u16  synth_freq_mult;
    u16  synth_freq_mult_wa;
    u8   synth_freq_mult_hi;
    u64  synth_freq_n;
    u64  synth_freq_m;
    u8   synth_freq_m_h;
    u8   synth_freq_n_h;
    u32  synth_freq_m_l;
    u32  synth_freq_n_l;
    u32  tx_svn_id;

    u32  rd_val;
#if VTSS_OPT_TRACE
    u32  addr;
#endif

    if ((vtss_state->clock.output_frequency[clock_output]           != freq_khz) ||
        (vtss_state->clock.par_output_frequency[clock_output]       != par_freq_khz) ||
        (vtss_state->clock.output_frequency_ratio[clock_output].num != ratio->num) ||
        (vtss_state->clock.output_frequency_ratio[clock_output].den != ratio->den)) {
        VTSS_D("state %p, clock_output %d, Selected frequency %u kHz", vtss_state, clock_output, freq_khz);
        if ((freq_khz == 0) && (par_freq_khz == 0)) {
            /* Disable output */
            ES6514_WRXF(SD10G65_DIG, SD10G65_SYNC_CTRL_SYNC_CTRL_CFG, dig_tgt, LANE_SYNC_SRC, 3);
            ES6514_WRXM_CLR(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, 
                            ES6514_MSK_BIT(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, EN_OB));

            ES6514_WRXB(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_ENA,   0);
            ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_ENA, 0);

            /* Check if we are allowed to switch of the SBUS_BIAS_EN */
            if(vtss_state->clock.serdes_rx_en[clock_output] == FALSE) {
                ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG, tgt, SBUS_BIAS_EN,  0);
            };
            vtss_state->clock.serdes_tx_en[clock_output] = FALSE;
        } else if ((freq_khz > 0) && (par_freq_khz > 0)) {
            VTSS_E("Currently it is not supported to specify freq_khz and par_freq_khz different from 0 simulateneously. Only one can be enabled.\n");
            return VTSS_RC_ERROR;
        } else if (par_freq_khz == 0) {
            freq_khz_w_ratio = (u32)(VTSS_DIV64((u64)freq_khz * ratio_num, ratio_den));
            if (freq_khz_w_ratio < 1000) {
                VTSS_E("Selected frequency %u kHz with ratio %u/%u to low.  Must be at least 1000 kHz\n", freq_khz, ratio_num, ratio_den);
                return VTSS_RC_ERROR;
            } else if (freq_khz_w_ratio > 250000) {
                VTSS_E("Selected frequency %u kHz with ratio %u/%u to high.  Must be not above 250000 kHz\n", freq_khz, ratio_num, ratio_den);
                return VTSS_RC_ERROR;
            } else {
                /* to get low jitter use SER baudrate of 9..10.8GBps */
                if (freq_khz_w_ratio > 70312) {
                    /* use constant pattern generator */
                    /* min freq[Hz]: 9e9 / (128 / 2) = 140.625e6 */
                    use_clock_gen = FALSE;
                    if (freq_khz_w_ratio >= 140625) {
                        num_periods = 2;
                    } else {
                        num_periods = 1;
                    }
                    dft_word_mode = 8;
                    for (num_words = 5; num_words <= 16; num_words++) {
                        num_bits = num_words * dft_word_mode / num_periods;
                        if (freq_khz_w_ratio * num_bits >= 9000000) {
                            break;
                        }
                    }
                    sample_freq_khz = freq_khz * num_bits;
                    /* With dft_word_mode == 8 and num_periods [1..2], num_bits is always a multiple of 4 */
                    /* calculate the pattern to be stored in the const pattern generator */
                    /* We have either 1 or 2 periods stored */
                    /*                                                   */
                    /* exampel 4 one period:     exampel 4 two periods:  */
                    /*                                                   */
                    /*        0x00                     0x00              */
                    /*        0x00                     0xc0              */
                    /*        0x00                     0xff              */
                    /*        0xf0                     0x0f              */
                    /*        0xff                     0x00              */
                    /*        0xff                     0xfc              */
                    /*        0xff                     0xff              */
                    toggle = 0;
                    incr = 0;
                    for (i=0 ; i < num_words ; i++) {
                        switch ((8*(i+1)) % (num_bits / 2)) {
                        case 0: {
                            pattern[i] = 0x00 ^ toggle;
                            break;
                        }
                        case 2: {
                            pattern[i] = 0xc0 ^ toggle;
                            break;
                        }
                        case 4: {
                            pattern[i] = 0xf0 ^ toggle;
                            break;
                        }
                        case 6: {
                            pattern[i] = 0xfc ^ toggle;
                            break;
                        }
                        default : {
                            pattern[i] = 0x00 ^ toggle;
                        }
                        }
                        incr += 8;
                        if (incr >= (num_bits/2)) {
                            toggle ^= 0xff;
                            incr -= num_bits / 2;
                        }
                    }
                    interface_width = 32;
                } else {
                    /* new clock pattern generator */
                    use_clock_gen = TRUE;
                    interface_width = 32;
                    clock_gen_period_half = 2;
                    sample_freq_khz = freq_khz_w_ratio * interface_width * 2 * clock_gen_period_half;
                    while (sample_freq_khz < 9000000) {
                        interface_width = 40;
                        sample_freq_khz = freq_khz_w_ratio * interface_width * 2 * clock_gen_period_half;
                        if (sample_freq_khz < 9000000) {
                            clock_gen_period_half++;
                            interface_width = 32;
                            sample_freq_khz = freq_khz_w_ratio * interface_width * 2 * clock_gen_period_half;
                        }
                    }
                    sample_freq_khz = freq_khz * interface_width * 2 * clock_gen_period_half;
                }
                /* Power up the output buffer */
                ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, LEVN,      7);
                ES6514_WRXB(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, EN_DIRECT, 0);
                ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG2, tgt, D_FILTER,  0x7df820);
            }
        } else {
            /* par_freq_khz > 0 => we need to setup for parallel clock frequency */
            freq_khz_w_ratio = (u32)(VTSS_DIV64((u64)par_freq_khz * ratio_num, ratio_den));
            if (freq_khz_w_ratio < 31250) {
                VTSS_E("Selected parallel frequency %u kHz with ratio %u/%u to low.  Must be at least 31250 kHz\n", par_freq_khz, ratio_num, ratio_den);
                return VTSS_RC_ERROR;
            } else if (freq_khz_w_ratio > 400000) {
                VTSS_E("Selected parallel frequency %u kHz with ratio %u/%u to high.  Must be not above 400000 kHz\n", par_freq_khz, ratio_num, ratio_den);
                return VTSS_RC_ERROR;
            } else {
                if (freq_khz_w_ratio < 41667) {
                    /*  31.25 MHz .. 41.66 MHz: 1G25 mode @ 40bit IW */
                    interface_width = 40;
                    synth_half_rate_mode = 1;
                } else if (freq_khz_w_ratio < 83334) {
                    /*  41.66 MHz .. 83.33 MHz:  2G5 mode @ 40bit IW */
                    interface_width = 40;
                } else if (freq_khz_w_ratio < 166667) {
                    /*  83.33 MHz .. 166.6 MHZ:   5G mode @ 40bit IW */
                    interface_width = 40;
                } else if (freq_khz_w_ratio < 250000) {
                    /*  166.6 MHz .. 250.0 MHz:  10G mode @ 40bit IW */
                    interface_width = 40;
                } else if (freq_khz_w_ratio < 333334) {
                    /*  250.0 MHz .. 333.3 MHz:  10G mode @ 32bit IW */
                    interface_width = 32;
                } else {
                    /*  333.3 MHz .. 400.0 MHz:  10G mode @ 20bit IW */
                    interface_width = 20;
                }
                sample_freq_khz = par_freq_khz * interface_width * (1 + synth_half_rate_mode);
                /* Power down the output buffer */
                ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, LEVN,      31);
                ES6514_WRXB(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, EN_DIRECT, 1);
                ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG2, tgt, D_FILTER,  0);
            }
        }

        // The following is to setup the synthesizer. Valid for both, serial and parallel clock

#if defined(VTSS_ARCH_SERVAL_T)    
        /* Serval-T and probably also upcomming devices must set their sync_ctrl source to 1 to select the Omega sync_ctrl info */
        ES6514_WRXF(SD10G65_DIG, SD10G65_SYNC_CTRL_SYNC_CTRL_CFG, dig_tgt, LANE_SYNC_SRC, 1);
#else
#if defined(VTSS_CHIP_ES6514)
        /* ES6514 must set the sync ctrl to 2 to get the symc_ctrl info from omega */
        ES6514_WRXF(SD10G65_DIG, SD10G65_SYNC_CTRL_SYNC_CTRL_CFG, dig_tgt, LANE_SYNC_SRC, 2);
#else
        VTSS_E("Unknown design: Please check what LANE_SYNC_SRC configuration is needed in the design");
#endif //VTSS_CHIP_ES6514
#endif //VTSS_ARCH_SERVAL_T

        /* setup the tx macro with the calculated sample frequency and interface_width */
        /* setup the synthesizer in the tx macro */
        // multiplier   = sample_freq_khz * 400; /* = * 1000 / 2.5 */
        // multiplier64 = ((u64)(multiplier)) << 12;  /* synth_freq_mult has 12 fractional bit */
        // synth_freq_mult = (u16)(VTSS_DIV64(multiplier64, 1000000000));
        if (((u64)sample_freq_khz * ratio_num) < VTSS_DIV64((u64)10000000*ratio_den,3)) {
            /* sample frequncy below 3.33GHz -> use 2/3 * 2G5 .. 4/3 * 2G5 */
            es6514_calc_synth_settings(vtss_state, (u64)sample_freq_khz * ratio_num,  (u64)2500000 * ratio_den, &synth_freq_mult, &synth_freq_m, &synth_freq_n);
            synth_fbdiv_sel = 0;
            synth_ls_speed  = 0;
            synth_cs_speed  = 0;
        } else if(((u64)sample_freq_khz * ratio_num) <VTSS_DIV64((u64)2*10000000*ratio_den,3)) {
            /* sample frequncy between 3.33GHz and 6.66Ghz -> use 2/3 * 5G .. 4/3 * 5G */
            es6514_calc_synth_settings(vtss_state, (u64)sample_freq_khz * ratio_num,  (u64)5000000 * ratio_den, &synth_freq_mult, &synth_freq_m, &synth_freq_n);
            synth_fbdiv_sel = 1;
            synth_ls_speed  = 0;
            synth_cs_speed  = 1;
        } else  {
            /* sample frequncy between 6.66GHz and 13.33Ghz -> use 2/3 *10G .. 4/3 * 5G */
            es6514_calc_synth_settings(vtss_state, (u64)sample_freq_khz * ratio_num, (u64)10000000 * ratio_den, &synth_freq_mult, &synth_freq_m, &synth_freq_n);
            synth_fbdiv_sel = 2;
            synth_ls_speed  = 1;
            synth_cs_speed  = 1;
        }
        if ((u64)sample_freq_khz * ratio_num < ((u64)5000000 * ratio_den)) {
            synth_speed_sel = 1;
        } else {
            synth_speed_sel = 0;
        }

        synth_freq_m_h  = (u8)(synth_freq_m >> 32);
        synth_freq_n_h  = (u8)(synth_freq_n >> 32);
        synth_freq_m_l  = (u32)(synth_freq_m & 0xffffffff);
        synth_freq_n_l  = (u32)(synth_freq_n & 0xffffffff);


        ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_SPARE_POOL,   7);
        ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_SPEED_SEL,    synth_speed_sel);
        ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_FBDIV_SEL,    synth_fbdiv_sel);
        /* SW workarround: Bypass the frequency decoder inside the SerDes and calculate improved settings manually */
        ES6514_RDX(SD10G65, SD10G65_OB_SD10G65_TX_SVN_ID, tgt, &tx_svn_id);
        if (tx_svn_id <= 43022) {
            es6514_calc_frec_dec_bypass(synth_freq_mult, &synth_freq_mult_wa, &synth_freq_mult_hi);
            ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT_BYP, 1);
            ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT_HI,  synth_freq_mult_hi);
            ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT,     synth_freq_mult_wa);
        } else {
            ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT_BYP, 0);
            ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT_HI,  4);
            ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, SYNTH_FREQ_MULT,    synth_freq_mult);
        }
        ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, SYNTH_FREQM_1,      synth_freq_m_h);
        ES6514_WRX(SD10G65,  SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3, tgt,                     synth_freq_m_l);
        ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, SYNTH_FREQN_1,      synth_freq_n_h);
        ES6514_WRX(SD10G65,  SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4, tgt,                     synth_freq_n_l);
        ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_LS_SPEED,     synth_ls_speed);
        ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_CS_SPEED,     synth_cs_speed);
        ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_HRATE_ENA,    synth_half_rate_mode);

        ES6514_WRXB(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, SYNTH_ENA,          1);
        /* End synthesizer setup part 1*/

        /* Configure RC-PLL */
        /* Configure improved RCPLL values found during validation tests*/
        ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_VCO_CUR,  7);
        ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_VREG18,  10);

        /* Only write PLL_ENA required. The other registers already have correct default values */
        ES6514_WRXB(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_ENA,      1);
        if ((u64)sample_freq_khz * ratio_num > (u64)7000000 * ratio_den) {
            ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_LPF_CUR, 3);
            ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_LPF_RES, 10);
        } else if ((u64)sample_freq_khz * ratio_num> (u64)3000000 * ratio_den) {
            ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_LPF_CUR, 2);
            ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_LPF_RES, 15);
        } else {
            ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_LPF_CUR, 0);
            ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, PLL_LPF_RES, 10);
        }
        ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0, tgt, PLLF_START_CNT,     2);
        ES6514_WRXB(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0, tgt, PLLF_ENA,           0);

        /* Value should be (((u32)interface_width * 512) / ((sample_freq_khz * 8) / 1000000))); to avoid rounding errors this has been simplified to the below formula */
        ES6514_WRXF(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1, tgt, PLLF_REF_CNT_END, (((u32)interface_width * 64 * 1000000 ) / ((u32)(VTSS_DIV64((u64)sample_freq_khz * ratio_num, ratio_den)) >> synth_half_rate_mode)));
        /* Wait 2 us */
        VTSS_NSLEEP(2000);
        ES6514_WRXB(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0, tgt, PLLF_ENA, 1);
        /* End of setup RX */

        /* Configure SER / OB */
        ES6514_WRXB(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, EN_INP_LOOP, 0);
        ES6514_WRXB(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, EN_PAD_LOOP, 0);
        ES6514_WRXB(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, EN_OB,       1);
        ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, SEL_IFW,   es6514_get_iw_setting(vtss_state, interface_width));
        ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, LEVN,        7);


        ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG1, tgt, LEV_SHFT,      1);
        ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG1, tgt, PREDRV_R_CTRL, 3);
        ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG1, tgt, PREDRV_C_CTRL, 3);

        ES6514_WRX(SD10G65,  SD10G65_OB_SD10G65_OB_CFG2, tgt,                0x7DF820);

        /* Configure SBUS */
        /* !!!! Note: in es6514 RX and TX together form a macro -> RX is responsible for SBUS signals */
        ES6514_WRXB(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG, tgt, SBUS_BIAS_EN,        1);
        ES6514_WRXF(SD10G65, SD10G65_IB_SD10G65_SBUS_RX_CFG, tgt, SBUS_BIAS_SPEED_SEL, 3);
        vtss_state->clock.serdes_tx_en[clock_output] = TRUE;

        /* Configure the synchronization logic */
        ES6514_WRXM_SET(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, 
                        /* ES6514_MSK_BIT(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, SYNTH_ENA_SYNC_UNIT) | */ /* This register is marked debug */
                        /* ES6514_MSK_BIT(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, SYNTH_CONV_ENA)      | */ /* This register is marked debug */
                        ES6514_MSK_BIT(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, SYNTH_LS_ENA));
        ES6514_WRXM_CLR(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, 
                        /* ES6514_MSK_BIT(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, SYNTH_LS_DIR) | */ /* This register is marked debug */
                        /* ES6514_MSK_BIT(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, SYNTH_DS_DIR) | */ /* This register is marked debug */
                        ES6514_MSK_BIT(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, SYNTH_DS_SPEED)        |
                        ES6514_MSK_BIT(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, SYNTH_DS_ENA));

        /* FSEL for the filter and for the DF2F must be identical ! */
        /* Check if filter is already setup */
        ES6514_RDXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_ENA, &rd_val);
        if (rd_val == 1) {
            ES6514_RDXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_F_SEL, &rd_val);
            ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_SSC_CFG1, tgt, SYNC_CTRL_FSEL, rd_val);
        }
        /* End macro setup */

        /* Continue with df2f setup */
        if (es6514_check_pll_lock(vtss_state, tx, clock_output) == FALSE) {
            VTSS_E("RC-PLL was not able to get in lock\n");
            /* return some register values for debug */
#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 (addr 0x%04x) is 0x%08x\n", addr, rd_val);

#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4 (addr 0x%04x) is 0x%08x\n", addr, rd_val);

#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_SYNTH_SD10G65_SSC_CFG0, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_SYNTH_SD10G65_SSC_CFG0, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
#if VTSS_OPT_TRACE
            addr = ES6514_ADDR_X(SD10G65, SD10G65_TX_SYNTH_SD10G65_SSC_CFG1, tgt);
#endif
            ES6514_RDX(SD10G65, SD10G65_TX_SYNTH_SD10G65_SSC_CFG1, tgt, &rd_val);
            VTSS_E("The content of SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 (addr 0x%04x) is 0x%08x\n", addr, rd_val);
            return VTSS_RC_ERROR;
        }

        if (freq_khz > 0) {
            /* HQ serial clock only */
            if (use_clock_gen == TRUE) {
                /* use DF2F clock generator */ 
                ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_CLK_GEN_CFG, dig_tgt, CG_PER_CFG,  clock_gen_period_half);
                ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_CLK_GEN_CFG, dig_tgt, CG_DCD_CFG,  0);
                ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_CLK_GEN_CFG, dig_tgt, CG_MODE_CFG, 0);
                ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, OPATH_CFG,   2);
                ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, TX_WID_SEL_CFG,  es6514_get_iw_setting(vtss_state, interface_width));
                ES6514_WRXB(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, DFT_TX_ENA,  1);
            } else {
                /* use pattern generator */
                ES6514_WRXB(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, DFT_TX_ENA,       1);
                ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, TX_WID_SEL_CFG,  es6514_get_iw_setting(vtss_state, interface_width));
                ES6514_WRXB(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, TX_WORD_MODE_CFG, 0);
                ES6514_WRXB(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, IPATH_CFG,        0);
                ES6514_WRXB(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, SCRAM_INV_CFG,    0);
                for (i=0 ; i < num_words ; i++) {
                    /* pattern must be written highest address downto 0 */
                    ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_TX_PAT_CFG,      dig_tgt, STORE_ADDR_CFG,   num_words-i-1);
                    ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_TX_PAT_CFG,      dig_tgt, PATTERN_CFG,      pattern[i]);
                    ES6514_WRXB(SD10G65_DIG, SD10G65_DFT_DFT_TX_PAT_CFG,      dig_tgt, PAT_VLD_CFG,      1);
                    ES6514_WRXB(SD10G65_DIG, SD10G65_DFT_DFT_TX_PAT_CFG,      dig_tgt, PAT_VLD_CFG,      0);
                }
                ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_TX_PAT_CFG,  dig_tgt, MAX_ADDR_GEN_CFG,  num_words-1);
                ES6514_WRXF(SD10G65_DIG, SD10G65_DFT_DFT_TX_CFG,      dig_tgt, OPATH_CFG,         1);
            }
        }
        if ((freq_khz > 0) || (par_freq_khz > 0)) {
            /* shortly enable the sync timer so get the I2 value from filter transfered to the DF2F */
            /* Check if filter is already setup */
            ES6514_RDXB(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_ENA, &rd_val);
            if (rd_val == 1) {
                ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_SC,   clock_output, FILT_SC_SYNC_TIMER_SEL, 8);
            }
            ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_SC,   clock_output, FILT_SC_SYNC_TIMER_SEL, 0);
        }

        vtss_state->clock.output_frequency[clock_output] = freq_khz;
        vtss_state->clock.par_output_frequency[clock_output] = par_freq_khz;
        vtss_state->clock.output_frequency_ratio[clock_output].num = ratio->num;
        vtss_state->clock.output_frequency_ratio[clock_output].den = ratio->den;
    }
    return VTSS_RC_OK;
}

/* Set Clock output frequency */
static vtss_rc es6514_clock_output_frequency_set(vtss_state_t                  *vtss_state,
                                                 const u8                      clock_output,
                                                 const u32                     freq_khz,
                                                 const u32                     par_freq_khz)
{
    vtss_clock_ratio_t ratio;
    ratio.num = 1;
    ratio.den = 1;
    es6514_clock_output_frequency_ratio_set(vtss_state, clock_output, freq_khz, par_freq_khz, &ratio);
    return VTSS_RC_OK;
}

/* Get Clock output frequency ratio. */
static vtss_rc es6514_clock_output_frequency_ratio_get(vtss_state_t                  *vtss_state,
                                                       const u8                      clock_output,
                                                       u32                           *const freq_khz,
                                                       u32                           *const par_freq_khz,
                                                       vtss_clock_ratio_t            *const ratio)
{
    *freq_khz     = vtss_state->clock.output_frequency[clock_output];
    *par_freq_khz = vtss_state->clock.par_output_frequency[clock_output];
    ratio->num    = vtss_state->clock.output_frequency_ratio[clock_output].num;
    ratio->den    = vtss_state->clock.output_frequency_ratio[clock_output].den;
    return VTSS_RC_OK;
}

/* Get Clock output frequency. */
static vtss_rc es6514_clock_output_frequency_get(vtss_state_t                  *vtss_state,
                                                 const u8                      clock_output,
                                                 u32                           *const freq_khz,
                                                 u32                           *const par_freq_khz)
{
    vtss_clock_ratio_t ratio;
    es6514_clock_output_frequency_ratio_get(vtss_state, clock_output, freq_khz, par_freq_khz, &ratio);
    return VTSS_RC_OK;
}

/* Set Clock output voltage level. */
static vtss_rc es6514_clock_output_level_set(vtss_state_t           *vtss_state,
                                             const u8                        clock_output,
                                             const u16                       level_mv)
{
    u32  tgt = VTSS_TO_SD10G65(clock_output);
    u16  level_mv_div25_rounded = (level_mv + 12) / 25;

    if (level_mv > 1275) {
        VTSS_E("Selected output level of %u mV is to high.  Must be not above 1275 mV\n", level_mv);
        return VTSS_RC_ERROR;
    } else if (level_mv < 300) {
        VTSS_E("Selected output level of %u mV is to low.  Must be at least mV\n", level_mv);
        return VTSS_RC_ERROR;
    } else {
        if (vtss_state->clock.output_level[clock_output] != level_mv) {
            if (level_mv > 1075) {
                ES6514_WRXB(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, INCR_LEVN, 0);
                ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, LEVN, 20 + 31 - level_mv_div25_rounded);
            } else {
                ES6514_WRXB(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, INCR_LEVN, 1);
                ES6514_WRXF(SD10G65, SD10G65_OB_SD10G65_OB_CFG0, tgt, LEVN, 12 + 31 - level_mv_div25_rounded);
            }
            vtss_state->clock.output_level[clock_output] = level_mv;
        }
    }
    return VTSS_RC_OK;
}

/* Get Clock output voltage level. */
static vtss_rc es6514_clock_output_level_get(vtss_state_t                    *vtss_state,
                                             const u8                        clock_output,
                                             u16                             *const level_mv)
{
    *level_mv =  vtss_state->clock.output_level[clock_output];
    return VTSS_RC_OK;
}





/* Set Clock output selector. */
static vtss_rc es6514_clock_output_selector_set(vtss_state_t                      *vtss_state,
                                                const u8                          clock_output,
                                                const vtss_clock_input_selector_t *const input)
{
    switch(input->input_type) {
    case VTSS_CLOCK_INPUT_TYPE_DPLL: {
        ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_SRC_SEL, vtss_state->clock.clock_input_cnt + input->input_inst);
        break;
    }

    case VTSS_CLOCK_INPUT_TYPE_IN: {
        ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_SRC_SEL, input->input_inst);
        break;
    }

    case VTSS_CLOCK_INPUT_TYPE_PURE_DCO: {
        ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_SRC_SEL, vtss_state->clock.clock_input_cnt + vtss_state->clock.dpll_cnt);
        break;
    }

    default: {
        VTSS_E("illegal enumeration for vtss_clock_input_type_t\n");
        return VTSS_RC_ERROR;
    }
    }
    vtss_state->clock.input_selector[clock_output].input_type = input->input_type;
    vtss_state->clock.input_selector[clock_output].input_inst = input->input_inst;
    return VTSS_RC_OK;
}

/* Get Clock output selector. */
static vtss_rc es6514_clock_output_selector_get(vtss_state_t                  *vtss_state,
                                                const u8                      clock_output,
                                                vtss_clock_input_selector_t   *const input)
{
    u8 rd_val;
    ES6514_RDXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_SRC_SEL, &rd_val);
    if (rd_val < vtss_state->clock.clock_input_cnt) {
        input->input_type = VTSS_CLOCK_INPUT_TYPE_IN;
        input->input_inst = rd_val;
    } else if (rd_val < vtss_state->clock.clock_input_cnt + vtss_state->clock.dpll_cnt) {
        input->input_type = VTSS_CLOCK_INPUT_TYPE_DPLL;
        input->input_inst = rd_val - vtss_state->clock.clock_input_cnt;
    } else if (rd_val < vtss_state->clock.clock_input_cnt + vtss_state->clock.dpll_cnt + 1) {
        input->input_type = VTSS_CLOCK_INPUT_TYPE_PURE_DCO;
        input->input_inst = 0;
    } else {
        VTSS_E("illegal value for vtss_clock_input_type_t read from HW\n");
        return VTSS_RC_ERROR;
    }

    if ((input->input_type == vtss_state->clock.input_selector[clock_output].input_type) &&
        (input->input_inst == vtss_state->clock.input_selector[clock_output].input_inst)) {
        return VTSS_RC_OK;
    } else {
        VTSS_E("SW and HW state for output_selector clock_output %u,  do not match\n", clock_output);
        return VTSS_RC_ERROR;
    }

}

static vtss_rc es6514_clock_input_alarm_conf_set(vtss_state_t                  *vtss_state,
                                                 const u8                      clock_input,
                                                 const vtss_clock_input_conf_t *const conf)
{
    ES6514_WRXM(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, clock_input,
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_LOS_CTRL_ALARM_ENA, conf->alarm_ena.los) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_PFM_CTRL_ALARM_ENA, conf->alarm_ena.pfm) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_CFM_CTRL_ALARM_ENA, conf->alarm_ena.cfm) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_SCM_CTRL_ALARM_ENA, conf->alarm_ena.scm) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_GST_CTRL_ALARM_ENA, conf->alarm_ena.gst) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_LOL_CTRL_ALARM_ENA, conf->alarm_ena.lol),
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_LOS_CTRL_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_PFM_CTRL_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_CFM_CTRL_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_SCM_CTRL_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_GST_CTRL_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_LOL_CTRL_ALARM_ENA));
    ES6514_WRXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, clock_input, QUAL_EXT_LOS_INV, (conf->los_active_high ? 0 : 1));
    vtss_state->clock.input_conf[clock_input].los_active_high = conf->los_active_high;
    vtss_state->clock.input_conf[clock_input].alarm_ena.los   = conf->alarm_ena.los;
    vtss_state->clock.input_conf[clock_input].alarm_ena.pfm   = conf->alarm_ena.pfm;
    vtss_state->clock.input_conf[clock_input].alarm_ena.cfm   = conf->alarm_ena.cfm;
    vtss_state->clock.input_conf[clock_input].alarm_ena.scm   = conf->alarm_ena.scm;
    vtss_state->clock.input_conf[clock_input].alarm_ena.gst   = conf->alarm_ena.gst;
    vtss_state->clock.input_conf[clock_input].alarm_ena.lol   = conf->alarm_ena.lol;
    return VTSS_RC_OK;
}

static vtss_rc es6514_clock_input_alarm_conf_get(vtss_state_t                  *vtss_state,
                                                 const u8                      clock_input,
                                                 vtss_clock_input_conf_t       *const conf)
{
    u32 rd_val;
    u8  los_alarm_ena;
    u8  pfm_alarm_ena;
    u8  cfm_alarm_ena;
    u8  scm_alarm_ena;
    u8  gst_alarm_ena;
    u8  lol_alarm_ena;

    ES6514_RDX(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, clock_input, &rd_val);
    los_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_LOS_CTRL_ALARM_ENA, rd_val);
    pfm_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_PFM_CTRL_ALARM_ENA, rd_val);
    cfm_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_CFM_CTRL_ALARM_ENA, rd_val);
    scm_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_SCM_CTRL_ALARM_ENA, rd_val);
    gst_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_GST_CTRL_ALARM_ENA, rd_val);
    lol_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_LOL_CTRL_ALARM_ENA, rd_val);
    conf->alarm_ena.los = (los_alarm_ena == 1) ? TRUE : FALSE;
    conf->alarm_ena.pfm = (pfm_alarm_ena == 1) ? TRUE : FALSE;
    conf->alarm_ena.cfm = (cfm_alarm_ena == 1) ? TRUE : FALSE;
    conf->alarm_ena.scm = (scm_alarm_ena == 1) ? TRUE : FALSE;
    conf->alarm_ena.gst = (gst_alarm_ena == 1) ? TRUE : FALSE;
    conf->alarm_ena.lol = (lol_alarm_ena == 1) ? TRUE : FALSE;

    ES6514_RDXB(OMG_MAIN, OMG_QUAL_OMG_QUAL_COMMON_CFG, clock_input, QUAL_EXT_LOS_INV, &rd_val);
    conf->los_active_high = (rd_val == 1) ? FALSE : TRUE;

    if ((vtss_state->clock.input_conf[clock_input].los_active_high != conf->los_active_high) ||
        (vtss_state->clock.input_conf[clock_input].alarm_ena.los != conf->alarm_ena.los) ||
        (vtss_state->clock.input_conf[clock_input].alarm_ena.los != conf->alarm_ena.los) ||
        (vtss_state->clock.input_conf[clock_input].alarm_ena.pfm != conf->alarm_ena.pfm) ||
        (vtss_state->clock.input_conf[clock_input].alarm_ena.cfm != conf->alarm_ena.cfm) ||
        (vtss_state->clock.input_conf[clock_input].alarm_ena.scm != conf->alarm_ena.scm) ||
        (vtss_state->clock.input_conf[clock_input].alarm_ena.lol != conf->alarm_ena.lol)) {
        VTSS_E("SW and HW state for input_alarm_conf clock_input %u,  do not match\n", clock_input);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc es6514_clock_input_cfm_conf_set(vtss_state_t                 *vtss_state,
                                               const u8                     clock_input,
                                               const vtss_clock_cfm_conf_t  *const conf)
{
    u32 cfm_delta = conf->cfm_set_ppb - conf->cfm_clr_ppb;
    u32 cfm_max;
    u32 cfm_hyst;
    u32 rd_val;
    u8  i1_filtshft;
    u8  i1_filtcoef;
    u8  i2_fsel = vtss_state->clock.f2df_integ2_fsel;
    u32 stepsize_i1;
    u32 stepsize_i2;
    u32 cfm_step_offs; /* cfm_max needs to be increased in order to compensate for sawing of filtered I1/I2 values */

    if (conf->cfm_clr_ppb > conf->cfm_set_ppb) {
        VTSS_E("cfm_clr_pbb (%u) must not be larger then cfm_set_pbb (%u)\n", conf->cfm_clr_ppb, conf->cfm_set_ppb);
        return VTSS_RC_ERROR;
    }

    if ((vtss_state->clock.cfm_conf[clock_input].cfm_set_ppb != conf->cfm_set_ppb) ||
        (vtss_state->clock.cfm_conf[clock_input].cfm_clr_ppb != conf->cfm_clr_ppb)) {
        ES6514_RDX(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, clock_input, &rd_val);
        i1_filtshft = ES6514_GET_FLD(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, QUAL_CPFM_I1_LPF_FILTSHFT, rd_val);
        i1_filtcoef = ES6514_GET_FLD(OMG_MAIN, OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG, QUAL_CPFM_I1_LPF_FILTCOEF, rd_val);
        stepsize_i1 = (((u32)1 << (15 - i1_filtshft)) * i1_filtcoef * 4375000) / vtss_state->clock.input_sample_freq_khz[clock_input];
        stepsize_i2 = (((u32)1 << (i2_fsel/2)) + ((i2_fsel%2) * ((u32)1 << ((i2_fsel/2)-1)))) >> 16;
        cfm_step_offs = (stepsize_i1 + stepsize_i2) * 3 / 2;

        /* ppb -> conf_value factor is (7 * 2^16 * 512 * 10) / 5e9 == 7 * 2^17 / 5^9 */
        cfm_max  = (u32)VTSS_DIV64((u64)(conf->cfm_set_ppb - cfm_delta/2) * 7 * (1 << 17), 1953125) + cfm_step_offs; /* 1953125 = 5^9 */
        cfm_hyst = (u32)VTSS_DIV64((u64)(cfm_delta/2)                     * 7 * (1 << 17), 1953125); 
        ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG,   clock_input, QUAL_CPFM_CF_MAX,  cfm_max);
        ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG,   clock_input, QUAL_CPFM_CF_HYST, cfm_hyst);

        vtss_state->clock.cfm_conf[clock_input].cfm_set_ppb = conf->cfm_set_ppb;
        vtss_state->clock.cfm_conf[clock_input].cfm_clr_ppb = conf->cfm_clr_ppb;
    }
    return VTSS_RC_OK;
}

static vtss_rc es6514_clock_input_cfm_conf_get(vtss_state_t                 *vtss_state,
                                               const u8                     clock_input,
                                               vtss_clock_cfm_conf_t        *const conf)
{
    conf->cfm_set_ppb  = vtss_state->clock.cfm_conf[clock_input].cfm_set_ppb;
    conf->cfm_clr_ppb  = vtss_state->clock.cfm_conf[clock_input].cfm_clr_ppb;
    return VTSS_RC_OK;
}

static vtss_rc es6514_clock_input_pfm_conf_set(vtss_state_t                 *vtss_state,
                                               const u8                     clock_input,
                                               const vtss_clock_pfm_conf_t  *const conf)
{
    u32 pfm_delta = conf->pfm_set_ppb - conf->pfm_clr_ppb;
    u32 pfm_max;
    u32 pfm_hyst;
    if (conf->pfm_clr_ppb > conf->pfm_set_ppb) {
        VTSS_E("pfm_clr_pbb (%u) must not be larger then pfm_set_pbb (%u)\n", conf->pfm_clr_ppb, conf->pfm_set_ppb);
        return VTSS_RC_ERROR;
    }
    if ((vtss_state->clock.pfm_conf[clock_input].pfm_set_ppb != conf->pfm_set_ppb) ||
        (vtss_state->clock.pfm_conf[clock_input].pfm_clr_ppb != conf->pfm_clr_ppb)) {
        /* ppb -> conf_value factor is (7 * 2^16 * 512 * 10) / 5e9 == 7 * 2^17 / 5^9 */
        pfm_max  = (u32)VTSS_DIV64((u64)(conf->pfm_set_ppb - pfm_delta/2) * 7 * (1 << 17), 1953125); /* 1953125 = 5^9 */
        pfm_hyst = (u32)VTSS_DIV64((u64)(pfm_delta/2)                     * 7 * (1 << 17), 1953125); 
        ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG,   clock_input, QUAL_CPFM_PF_MAX,  pfm_max);
        ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG,   clock_input, QUAL_CPFM_PF_HYST, pfm_hyst);

        vtss_state->clock.pfm_conf[clock_input].pfm_set_ppb = conf->pfm_set_ppb;
        vtss_state->clock.pfm_conf[clock_input].pfm_clr_ppb = conf->pfm_clr_ppb;
    }
    return VTSS_RC_OK;
}

static vtss_rc es6514_clock_input_pfm_conf_get(vtss_state_t                 *vtss_state,
                                               const u8                     clock_input,
                                               vtss_clock_pfm_conf_t        *const conf)
{
    conf->pfm_set_ppb  = vtss_state->clock.pfm_conf[clock_input].pfm_set_ppb;
    conf->pfm_clr_ppb  = vtss_state->clock.pfm_conf[clock_input].pfm_clr_ppb;
    return VTSS_RC_OK;
}

static vtss_rc es6514_clock_input_gst_conf_set(vtss_state_t                 *vtss_state,
                                               const u8                     clock_input,
                                               const vtss_clock_gst_conf_t  *const conf)
{
    u32 min_time_us;
    u32 max_time_us;
    u64 prediv_tmp;
    u16 prediv;
    u32 thresh;
    u64 tmp;
    u64 incr_tmp;
    u64 decr_tmp;
    u16 incr;
    u16 decr;

    ES6514_WRXM(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, clock_input, 
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_LOS_ALARM_ENA, conf->los) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_PFM_ALARM_ENA, conf->pfm) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_CFM_ALARM_ENA, conf->cfm) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_SCM_ALARM_ENA, conf->scm) |
                ES6514_PUT_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_LOL_ALARM_ENA, conf->lol),
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_LOS_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_PFM_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_CFM_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_SCM_ALARM_ENA) |
                ES6514_MSK_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_LOL_ALARM_ENA));


    if (conf->qualification_time_us == 0) {
        VTSS_E("Value for qualification_time_us must be above 0\n");
        return VTSS_RC_ERROR;
    }
    if (conf->disqualification_time_us == 0) {
        VTSS_E("Value for disqualification_time_us must be above 0\n");
        return VTSS_RC_ERROR;
    }

    min_time_us = conf->disqualification_time_us;
    max_time_us = conf->disqualification_time_us;
    if (conf->qualification_time_us < min_time_us) {
        min_time_us = conf->qualification_time_us;
    }
    if (conf->qualification_time_us > max_time_us) {
        max_time_us = conf->qualification_time_us;
    }
    if ((u64)min_time_us*255 < (u64)max_time_us) {
        VTSS_E("Ratio between disqualification_time_us and qualification_time_us must be above 1/255 <= ratio <= 255\n");
        return VTSS_RC_ERROR;
    }

    if ((vtss_state->clock.gst_conf[clock_input].disqualification_time_us != conf->disqualification_time_us) ||
        (vtss_state->clock.gst_conf[clock_input].qualification_time_us    != conf->qualification_time_us)) {
        /* There are two ways finding the optimal settings: */
        /* If min and max values are close then select min value to generate a incr/decr around 255 and */
        /* the other incr/decr parameter for the max value calculates to somewhat below 255 */
        /* If min and max values differ by several factors then select the max value to generate a incr/decr of 1 and */
        /* the other incr/decr parameter for the min valus calculates to max_value/min_value */
        if(max_time_us < (min_time_us << 4)) {
            /* min and max are close. Use first method */
        
            /* prediv = min_time_us * 1e3 [us/ns] / 2**25 / 3.2 [ns] */
            /* 2**24 in above formula is selected to use the range of the threshold as good as possible */
            /* prediv_tmp = (VTSS_DIV64(((u64)min_time_us * 10000 * 256), 32)) >> 25; */
            prediv_tmp = ((u64)min_time_us * 10000 * 8) >> 25;
            if (prediv_tmp > (1 << 16)-1) {
                prediv = (1 << 16) -1;
            } else {
                prediv = (u16)prediv_tmp;
            }
            if (prediv == 0) {
                prediv = 1; /* avoid division by 0 */
                thresh = VTSS_DIV64(((u64)min_time_us * 10000 * 255), 32);
            } else {
                thresh = VTSS_DIV64(((u64)min_time_us * 10000 * 255), 32 * prediv);
            }
            /* In this case we try to have either incr or decr at its max value of 255, but to get to the full defined range we must search */
            /* for lower values, if prediv and thresh have already reached their max */
            if (thresh > (1<<25)-1) {
                thresh = (1<<25)-1;
                tmp = VTSS_DIV64(((u64)thresh * prediv * 32), (u64)min_time_us * 10000);
                if (tmp == 0) {
                    VTSS_E("Error in qualification time paramter %u to high. Value must be below %u\n", max_time_us, (1 <<25)-1); 
                    return VTSS_RC_ERROR;
                }
                thresh = VTSS_DIV64(((u64)min_time_us * 10000 * tmp), 32 * prediv);
            }
        } else {
            /* min and max are very different. Use second method */
            prediv_tmp = ((u64)max_time_us * 10000 * 8) >> 25;
            if (prediv_tmp > (1 << 16)-1) {
                prediv = (1 << 16) -1;
            } else {
                prediv = (u16)prediv_tmp;
            }
            if (prediv == 0) {
                prediv = 1; /* avoid division by 0 */
                thresh = VTSS_DIV64(((u64)max_time_us * 10000), 32);
            } else {
                thresh = VTSS_DIV64(((u64)max_time_us * 10000), 32 * prediv);
            }
            /* In this case we try to have either incr or decr at its min value of 1. If we still can't find a value for thresh */
            /* the given parameter is simply to high */
            if (thresh > (1<<25)-1) {
                printf("Error in qualification time paramter %u to high. Value must be below %u\n", max_time_us, (1 <<25)-1); 
                return VTSS_RC_ERROR;
            }
        }
        tmp = VTSS_DIV64(((u64)thresh * prediv * 32), 1000);
        incr_tmp  = VTSS_DIV64(tmp, (u64)conf->disqualification_time_us);
        incr = (incr_tmp / 10) + (((incr_tmp % 10) > 4) ? 1 : 0);
        if (incr > ((1 << 8)-1)) {
            incr = (1 << 8)-1;
        }
        if (incr == 0) {
            incr = 1;
        }
        decr_tmp  = VTSS_DIV64(tmp, (u64)conf->qualification_time_us);
        decr = (decr_tmp / 10) + (((decr_tmp % 10) > 4) ? 1 : 0);
        if (decr > ((1 << 8)-1)) {
            decr = (1 << 8)-1;
        }
        if (decr == 0) {
            decr = 1;
        }
        ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_TIM_CFG0, clock_input, QUAL_GST_QUAL_INCR, (u8)incr);
        ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_TIM_CFG0, clock_input, QUAL_GST_QUAL_DECR, (u8)decr);
        ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_TIM_CFG0, clock_input, QUAL_GST_QUAL_PREDIV, (u16)prediv);
        ES6514_WRXF(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_TIM_CFG1, clock_input, QUAL_GST_QUAL_THRESHOLD, thresh);
        vtss_state->clock.gst_conf[clock_input].disqualification_time_us = conf->disqualification_time_us;
        vtss_state->clock.gst_conf[clock_input].qualification_time_us    = conf->qualification_time_us;
    }
    vtss_state->clock.gst_conf[clock_input].los                      = conf->los;
    vtss_state->clock.gst_conf[clock_input].pfm                      = conf->pfm;
    vtss_state->clock.gst_conf[clock_input].cfm                      = conf->cfm;
    vtss_state->clock.gst_conf[clock_input].scm                      = conf->scm;
    vtss_state->clock.gst_conf[clock_input].lol                      = conf->lol;
    return VTSS_RC_OK;
}

static vtss_rc es6514_clock_input_gst_conf_get(vtss_state_t                 *vtss_state,
                                               const u8                     clock_input,
                                               vtss_clock_gst_conf_t        *const conf)
{
    u32 rd_val;
    u8  los_ena;
    u8  pfm_ena;
    u8  cfm_ena;
    u8  scm_ena;
    u8  lol_ena;

    ES6514_RDX(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, clock_input, &rd_val);
    los_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_LOS_ALARM_ENA, rd_val);
    pfm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_PFM_ALARM_ENA, rd_val);
    cfm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_CFM_ALARM_ENA, rd_val);
    scm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_SCM_ALARM_ENA, rd_val);
    lol_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_GST_ALARM_CFG, QUAL_GST_LOL_ALARM_ENA, rd_val);

    conf->disqualification_time_us = vtss_state->clock.gst_conf[clock_input].disqualification_time_us;
    conf->qualification_time_us    = vtss_state->clock.gst_conf[clock_input].qualification_time_us;
    conf->los = (los_ena == 1) ? TRUE : FALSE;
    conf->pfm = (pfm_ena == 1) ? TRUE : FALSE;
    conf->cfm = (cfm_ena == 1) ? TRUE : FALSE;
    conf->scm = (scm_ena == 1) ? TRUE : FALSE;
    conf->lol = (lol_ena == 1) ? TRUE : FALSE;

    if ((vtss_state->clock.gst_conf[clock_input].los != conf->los) ||
        (vtss_state->clock.gst_conf[clock_input].pfm != conf->pfm) ||
        (vtss_state->clock.gst_conf[clock_input].cfm != conf->cfm) ||
        (vtss_state->clock.gst_conf[clock_input].scm != conf->scm) ||
        (vtss_state->clock.gst_conf[clock_input].lol != conf->lol)) {
        VTSS_E("SW and HW state for input_gst_conf clock_input %u,  do not match\n", clock_input);
        /* return VTSS_RC_ERROR; */
    }
    return VTSS_RC_OK;
}

// ***************************************************************************
//
//  Status
//
// ***************************************************************************

/* Get Clock selector state. */
static vtss_rc es6514_clock_selector_state_get(vtss_state_t                  *vtss_state,
                                               const vtss_clock_dpll_inst_t  dpll,
                                               vtss_clock_selector_state_t   *const selector_state,
                                               u8                            *const clock_input)
{
    u8 i;
    u32 rd_val;
    u8 ctrl_eec_state;
    u8 ctrl_op_mode;
    u8 wd_cnt; /* watch dog counter to avoid stucking in while loop */
    u8 ctrl_inp_src_sel;
    u8 ctrl_eec_src_sel;
    u32 omg_ctrl_refsel;
    BOOL enabled_ref_found = FALSE;
    /* default value for clock_input */
    *clock_input = vtss_state->clock.clock_input_cnt; /* Return invalid number in case clock input is irrelevant */ 

    ctrl_eec_state = 6;
    wd_cnt = 0;
    while ((ctrl_eec_state == 6) && (wd_cnt < 10)) {
        ES6514_RDX(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, dpll, &rd_val);
        ctrl_eec_state = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_EEC_STATE, rd_val);
        /* Workaround for Bugzilla 17813, check if we are in emulated ho state */
        if (vtss_state->clock.emulated_ho_state[dpll] == TRUE) {
            if (ctrl_eec_state < 4) {
                *selector_state = VTSS_CLOCK_SELECTOR_STATE_HOLDOVER;
                return VTSS_RC_OK;
            } else {
                /* We are at or have have passed locked_mode_ho state -> emulated_ho_state is no longer needed*/
                ES6514_WRX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0, dpll,                           0);
                ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_HIGH,              0);
                ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1, dpll, DF_FRM_UPDATE_ONE_SHOT,   1);
                vtss_state->clock.emulated_ho_state[dpll] = FALSE;
            }
        }
        switch (ctrl_eec_state) {
        case 0: {
            ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, &ctrl_op_mode);

            if (ctrl_op_mode < 2) {
                /* Disabled or Forec Free Run */
                if (vtss_state->clock.selection_conf[dpll].mode == VTSS_CLOCK_SELECTION_MODE_FORCED_DCO) {
                    *selector_state = VTSS_CLOCK_SELECTOR_STATE_DCO;
                } else {
                    *selector_state = VTSS_CLOCK_SELECTOR_STATE_FREERUN;
                }
            } else if (ctrl_op_mode == 3) {
                /* AUTO */
                /* Check if there is a possible input */
                ES6514_RDX(OMG_MAIN, OMG_CTRL_OMG_CTRL_REFSEL, dpll, &omg_ctrl_refsel); 
                for (i = 0; i < vtss_state->clock.clock_input_cnt; i++) {
                    /* ena bit are located in 0, 3, 6, ... in omg_ctrl_refsel */
                    if (((omg_ctrl_refsel >> (3*i)) & 0x1) == 1) {
                        enabled_ref_found = TRUE;
                    }
                }
                if ((enabled_ref_found == TRUE) && (vtss_state->clock.selection_conf[dpll].mode != VTSS_CLOCK_SELECTION_MODE_DISABLED)) {
                    /* We have sources enabled, but still hang around in forced_free_run state */
                    /* This means, none of the enabled sources have a valid clock */
                    *selector_state = VTSS_CLOCK_SELECTOR_STATE_REF_FAILED;
                } else {
                    /* We have not enabled any of the sources so we hang around in forced_free_run state by intesion */ 
                    *selector_state = VTSS_CLOCK_SELECTOR_STATE_FREERUN;
                }
            } else {
                /* Force holdover */
                VTSS_I("DPLL op mode is FRC_HO_MODE, but FSM has not yet acquired an Input. Changing DPLL op mode to FRC_FREE_RUN\n");
                ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_MAIN_CFG, dpll, CTRL_OP_MODE, 1);
                *selector_state = VTSS_CLOCK_SELECTOR_STATE_FREERUN;
            }
            break;
        }

        case 1: {
            *selector_state = VTSS_CLOCK_SELECTOR_STATE_FREERUN;
            break;
        }
        case 2: {

            *selector_state = VTSS_CLOCK_SELECTOR_STATE_FREERUN;
            break;
        }

        case 3: {
            *selector_state = VTSS_CLOCK_SELECTOR_STATE_ACQUIRING;
            ctrl_inp_src_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_INP_SRC_SEL, rd_val);
            ctrl_eec_src_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_EEC_SRC_SEL, rd_val);
            if (ctrl_eec_src_sel == 1) {
                *clock_input = ctrl_inp_src_sel;
            } else {
                /* if the DELTA_F is not taken from the selected reference, then report either freerun or holdover */
                if (ctrl_eec_src_sel == 0) {
                    *selector_state = VTSS_CLOCK_SELECTOR_STATE_FREERUN;
                } else {
                    *selector_state = VTSS_CLOCK_SELECTOR_STATE_HOLDOVER;
                }
                *clock_input = vtss_state->clock.clock_input_cnt; /* Return invalid number to indicate error */
                /* ctrl_eec_src_sel is either 0: Delta-f taken from CTRL_DELTA_F_FRM (in free-run mode) or 2: Delta-f taken from Hold-over stack */
                VTSS_I("DPLL is in state locked_mode_acq, but selected source is from %s\n", (ctrl_eec_src_sel == 0) ? ("reference input: free-run mode") : ("hold over stack"));
            }
            break;
        }

        case 4: {
            *selector_state = VTSS_CLOCK_SELECTOR_STATE_LOCKED;
            ctrl_inp_src_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_INP_SRC_SEL, rd_val);
            ctrl_eec_src_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_EEC_SRC_SEL, rd_val);
            if (ctrl_eec_src_sel == 1) {
                *clock_input = ctrl_inp_src_sel;
            } else {
                *clock_input = vtss_state->clock.clock_input_cnt; /* Return invalid number to indicate error */
                /* ctrl_eec_src_sel is either 0: Delta-f taken from CTRL_DELTA_F_FRM (in free-run mode) or 2: Delta-f taken from Hold-over stack */
                VTSS_I("DPLL is in state locked_mode_ho, but selected source is from %s\n", (ctrl_eec_src_sel == 0) ? ("reference input: free-run mode") : ("hold over stack"));
            }
            break;
        }

        case 5: {
            ctrl_eec_src_sel = ES6514_GET_FLD(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, CTRL_EEC_SRC_SEL, rd_val);
            if (ctrl_eec_src_sel == 2) {
                *selector_state = VTSS_CLOCK_SELECTOR_STATE_HOLDOVER;
            } else {
                *selector_state = VTSS_CLOCK_SELECTOR_STATE_REF_FAILED;
            }
            break;
        }

        case 6: {
            /* This is not a stable state (fall through state) read status register once again */
            break;
        }

        case 7: {
            *selector_state = VTSS_CLOCK_SELECTOR_STATE_HOLDOVER;
            break;
        }
        // ctrl_eec_state is 3 bit wide, and all possible cases are handled above, therefore Coeveity complains ahat this is dead code
        //default: {
        //    VTSS_E("Invalid value %u read from field OMG_CTRL:OMG_CTRL_STAT.CTRL_EEC_STATE\n", ctrl_eec_state);
        //    return VTSS_RC_ERROR;
        //}
        }
        wd_cnt++;
    }
    if (wd_cnt > 9) {
       VTSS_E("For some reason it was not possible to read a stable state form OMG_CTRL:OMG_CTRL_STAT.CTRL_EEC_STATE\n");
       return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

/* Get Clock pll state. */
static vtss_rc es6514_clock_dpll_state_get(vtss_state_t                  *vtss_state,
                                           const vtss_clock_dpll_inst_t  dpll,
                                           vtss_clock_dpll_state_t       *const pll_state)
{
    u8  ctrl_inp_src_sel;
    u32 rd_val, rd_val2;
    u32 tgt = VTSS_TO_SD10G65(0);

    u8  qual_los_ctrl_alarm_ena;
    u8  qual_pfm_ctrl_alarm_ena;
    u8  qual_cfm_ctrl_alarm_ena;
    u8  qual_scm_ctrl_alarm_ena;
    u8  qual_gst_ctrl_alarm_ena;
    u8  qual_lol_ctrl_alarm_ena;

    u8  irq_ext_los_status;
    u8  irq_pfm_alarm_status;
    u8  irq_cfm_alarm_status;
    u8  irq_scm_alarm_status;
    u8  irq_gst_alarm_status;
    u8  irq_lol_alarm_status;

    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT,         dpll, CTRL_INP_SRC_SEL, &ctrl_inp_src_sel);

     /* pll_freq_lock */
    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, dpll, CTRL_EEC_STATE, &rd_val);
    if ((rd_val == 4) || (rd_val == 3)) {
        pll_state->pll_freq_lock = TRUE;
    } else {
        pll_state->pll_freq_lock = FALSE;
    }

    /* pll_phase_lock */
    /* phase lock is when EEC FSM is in one of the locked states and f2df FSM is in state 3 and the logic for phase error compendation is enabled */
    /* Note: The logic for phase error compensation is not implemented for ES6514, therefore it can never return TRUE for phase_lock */
    /* default value */
    pll_state->pll_phase_lock = FALSE;
    if ((rd_val == 4) || (rd_val == 3)) {
        pll_state->pll_phase_lock = FALSE;
        tgt = VTSS_TO_SD10G65(ctrl_inp_src_sel);
        ES6514_RDXF(SD10G65, SD10G65_RX_SYNTH_F2DF_CFG_STAT, tgt, F2DF_FSM_STATE, &rd_val);
        if (rd_val == 3) {
            /*  ES6514_RDXF(SD10G65, SD10G65_RX_SYNTH_<reg_to_enable_phase_error_compensation>, tgt, <fld_to_enable_phase_error_compensation>, &rd_val); */
            /*  if (rd_val == ??) { */
            /* pll_state->pll_phase_lock = TRUE; */
            /* } */
        }
    }

    /* pll_losx */
    ES6514_RDX(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, ctrl_inp_src_sel, &rd_val);
    qual_los_ctrl_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_LOS_CTRL_ALARM_ENA, rd_val);
    qual_pfm_ctrl_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_PFM_CTRL_ALARM_ENA, rd_val);
    qual_cfm_ctrl_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_CFM_CTRL_ALARM_ENA, rd_val);
    qual_scm_ctrl_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_SCM_CTRL_ALARM_ENA, rd_val);
    qual_gst_ctrl_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_GST_CTRL_ALARM_ENA, rd_val);
    qual_lol_ctrl_alarm_ena = ES6514_GET_BIT(OMG_MAIN, OMG_QUAL_OMG_QUAL_ALARM_CFG, QUAL_LOL_CTRL_ALARM_ENA, rd_val);

    ES6514_RDX(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, ctrl_inp_src_sel, &rd_val);
    irq_ext_los_status   = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_EXT_LOS_STATUS  , rd_val); 
    irq_pfm_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_PFM_ALARM_STATUS, rd_val);
    irq_cfm_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_CFM_ALARM_STATUS, rd_val);
    irq_scm_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_SCM_ALARM_STATUS, rd_val);
    irq_gst_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_GST_ALARM_STATUS, rd_val);
    irq_lol_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_LOL_ALARM_STATUS, rd_val);

    if (((qual_los_ctrl_alarm_ena & irq_ext_los_status  ) |
         (qual_pfm_ctrl_alarm_ena & irq_pfm_alarm_status) |
         (qual_cfm_ctrl_alarm_ena & irq_cfm_alarm_status) |
         (qual_scm_ctrl_alarm_ena & irq_scm_alarm_status) |
         (qual_gst_ctrl_alarm_ena & irq_gst_alarm_status)) != 0) {
        pll_state->pll_losx = TRUE;
    } else {
        pll_state->pll_losx = FALSE;
    }


    /* pll_lol */
    if ((qual_lol_ctrl_alarm_ena & irq_lol_alarm_status) != 0) {
        pll_state->pll_lol = TRUE;
    } else {
        pll_state->pll_lol = FALSE;
    }

    /* pll_dig_hold_vld */
    ES6514_RDXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_STAT, dpll, CTRL_HO_FILLED, &rd_val);
    ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_MIN_FILL_LVL, &rd_val2);
    
    pll_state->pll_dig_hold_vld = (rd_val == 1 && rd_val2 > 1) ? TRUE : FALSE;

    return VTSS_RC_OK;
}

/* get the frequncy offset stored in the HO stack */
static vtss_rc es6514_clock_ho_stack_frequency_offset_get(vtss_state_t                  *vtss_state,
                                                          const vtss_clock_dpll_inst_t  dpll,
                                                          i64                           *const offset)
{
    u8    conf_value_h;
    u32   conf_value_l;
    u32   rd_val;

    if(vtss_state->clock.emulated_ho_state[dpll] == TRUE) {
        ES6514_RDX( OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM0,        dpll,                           &conf_value_l);
        ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_DF_FRM1,        dpll, DF_FRM_HIGH,              &conf_value_h);
    } else {
        ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG, dpll, CTRL_HO_SEL, &rd_val);

        ES6514_WRXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG,   dpll, CTRL_HO_RD_ADDR,          rd_val);
        ES6514_WRXB(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_CFG,   dpll, CTRL_HO_RD_STRB_ONE_SHOT, 1);
        ES6514_RDX( OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_STAT0, dpll,                           &conf_value_l);
        ES6514_RDXF(OMG_MAIN, OMG_CTRL_OMG_CTRL_HO_STACK_STAT1, dpll, CTRL_HO_RD_DATA_HIGH,     &conf_value_h);
    }
    es6514_delta_f_to_scaled_ppb(conf_value_h, conf_value_l, offset);
    return VTSS_RC_OK;
}

/* Get Clock input state. */
static vtss_rc es6514_clock_input_state_get(vtss_state_t                  *vtss_state,
                                            const u8                      clock_input,
                                            vtss_clock_input_state_t      *const input_state)
{
    u32 rd_val;
    u8  irq_ext_los_status;
    u8  irq_pfm_alarm_status;
    u8  irq_cfm_alarm_status;
    u8  irq_scm_alarm_status;
    u8  irq_lol_alarm_status;

    ES6514_RDX(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, clock_input, &rd_val);
    irq_ext_los_status   = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_EXT_LOS_STATUS  , rd_val); 
    irq_pfm_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_PFM_ALARM_STATUS, rd_val);
    irq_cfm_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_CFM_ALARM_STATUS, rd_val);
    irq_scm_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_SCM_ALARM_STATUS, rd_val);
    irq_lol_alarm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_LOL_ALARM_STATUS, rd_val);

    input_state->los = (irq_ext_los_status   == 1) ? TRUE : FALSE;
    input_state->pfm = (irq_pfm_alarm_status == 1) ? TRUE : FALSE;
    input_state->cfm = (irq_cfm_alarm_status == 1) ? TRUE : FALSE;
    input_state->scm = (irq_scm_alarm_status == 1) ? TRUE : FALSE;
    input_state->lol = (irq_lol_alarm_status == 1) ? TRUE : FALSE;

    return VTSS_RC_OK;
}


// ***************************************************************************
//
//  Event (interrupt) handling
//
// ***************************************************************************

// /* Clock input event polling function called by interrupt or periodicly */
static vtss_rc es6514_clock_input_event_poll(vtss_state_t                    *vtss_state,
                                             const u8                        clock_input,
                                             vtss_clock_input_event_type_t   *const ev_mask)
{
    u32 pending, int_ena, int_ena_upd_set, int_ena_upd_clr;
    u32 status;
    u8  irq_los_status;
    u8  irq_pfm_status;
    u8  irq_cfm_status;
    u8  irq_scm_status;
    u8  irq_gst_status;
    u8  irq_lol_status;
    ES6514_RDX(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, clock_input, &int_ena);
    ES6514_RDX(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT,   clock_input, &pending);
    ES6514_RDX(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS,  clock_input, &status);
    irq_los_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_EXT_LOS_STATUS,   status); 
    irq_pfm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_PFM_ALARM_STATUS, status);
    irq_cfm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_CFM_ALARM_STATUS, status);
    irq_scm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_SCM_ALARM_STATUS, status);
    irq_gst_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_GST_ALARM_STATUS, status);
    irq_lol_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_LOL_ALARM_STATUS, status);

    /* update mask */
    int_ena_upd_set = 0;
    int_ena_upd_clr = 0;
    if ((ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_ACT_INT_ENA, int_ena) | 
         ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_CLR_INT_ENA, int_ena)) > 0) {
        int_ena_upd_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_CLR_INT_ENA)   *   irq_los_status)      |
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_ACT_INT_ENA)   * ((irq_los_status+1)%2));
        int_ena_upd_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_CLR_INT_ENA)   * ((irq_los_status+1)%2))|
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_ACT_INT_ENA)   *   irq_los_status);
    }
    if ((ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_ACT_INT_ENA, int_ena) | 
         ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_CLR_INT_ENA, int_ena)) > 0) {
        int_ena_upd_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_CLR_INT_ENA) *   irq_pfm_status)      |
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_ACT_INT_ENA) * ((irq_pfm_status+1)%2));
        int_ena_upd_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_CLR_INT_ENA) * ((irq_pfm_status+1)%2))|
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_ACT_INT_ENA) *   irq_pfm_status);
    }
    if ((ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_ACT_INT_ENA, int_ena) | 
         ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_CLR_INT_ENA, int_ena)) > 0) {
        int_ena_upd_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_CLR_INT_ENA) *   irq_cfm_status)      |
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_ACT_INT_ENA) * ((irq_cfm_status+1)%2));
        int_ena_upd_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_CLR_INT_ENA) * ((irq_cfm_status+1)%2))|
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_ACT_INT_ENA) *   irq_cfm_status);
    }
    if ((ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_ACT_INT_ENA, int_ena) | 
         ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_CLR_INT_ENA, int_ena)) > 0) {
        int_ena_upd_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_CLR_INT_ENA) *   irq_scm_status)      |
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_ACT_INT_ENA) * ((irq_scm_status+1)%2));
        int_ena_upd_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_CLR_INT_ENA) * ((irq_scm_status+1)%2))|
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_ACT_INT_ENA) *   irq_scm_status);
    }
    if ((ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_ACT_INT_ENA, int_ena) | 
         ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_CLR_INT_ENA, int_ena)) > 0) {
        int_ena_upd_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_CLR_INT_ENA) *   irq_gst_status)      |
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_ACT_INT_ENA) * ((irq_gst_status+1)%2));
        int_ena_upd_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_CLR_INT_ENA) * ((irq_gst_status+1)%2))|
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_ACT_INT_ENA) *   irq_gst_status);
    }
    if ((ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_ACT_INT_ENA, int_ena) | 
         ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_CLR_INT_ENA, int_ena)) > 0) {
        int_ena_upd_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_CLR_INT_ENA) *   irq_lol_status)      |
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_ACT_INT_ENA) * ((irq_lol_status+1)%2));
        int_ena_upd_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_CLR_INT_ENA) * ((irq_lol_status+1)%2))|
                           (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_ACT_INT_ENA) *   irq_lol_status);
    }
    ES6514_WRXM_SET(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, clock_input, int_ena_upd_set);
    ES6514_WRXM_CLR(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, clock_input, int_ena_upd_clr);

    pending &= int_ena_upd_set;

    /* clear sticky bits */
    ES6514_WRX(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT,   clock_input, pending);

    *ev_mask = 0;
    *ev_mask |= VTSS_CLOCK_INPUT_LOS_EV * (ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_EXT_LOS_ACT_STICKY, pending) | 
                                           ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_EXT_LOS_CLR_STICKY, pending));
    *ev_mask |= VTSS_CLOCK_INPUT_PFM_EV * (ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_PFM_ALARM_ACT_STICKY, pending) | 
                                           ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_PFM_ALARM_CLR_STICKY, pending));
    *ev_mask |= VTSS_CLOCK_INPUT_CFM_EV * (ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_CFM_ALARM_ACT_STICKY, pending) | 
                                           ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_CFM_ALARM_CLR_STICKY, pending));
    *ev_mask |= VTSS_CLOCK_INPUT_SCM_EV * (ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_SCM_ALARM_ACT_STICKY, pending) | 
                                           ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_SCM_ALARM_CLR_STICKY, pending));
    *ev_mask |= VTSS_CLOCK_INPUT_GST_EV * (ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_GST_ALARM_ACT_STICKY, pending) | 
                                           ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_GST_ALARM_CLR_STICKY, pending));
    *ev_mask |= VTSS_CLOCK_INPUT_LOL_EV * (ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_LOL_ALARM_ACT_STICKY, pending) | 
                                           ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_EVENT, IRQ_LOL_ALARM_CLR_STICKY, pending));

    return VTSS_RC_OK;
}

/* Enable clock input event generation for a specific event type */
static vtss_rc es6514_clock_input_event_enable(vtss_state_t                  *vtss_state,
                                      const u8                              clock_input,
                                      const vtss_clock_input_event_type_t   ev_mask,
                                      const BOOL                            enable)
{
    u32 status;
    u8  irq_los_status;
    u8  irq_pfm_status;
    u8  irq_cfm_status;
    u8  irq_scm_status;
    u8  irq_gst_status;
    u8  irq_lol_status;
    u32 mask_set = 0;
    u32 mask_clr = 0;

    ES6514_RDX(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, clock_input, &status);
    irq_los_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_EXT_LOS_STATUS,   status); 
    irq_pfm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_PFM_ALARM_STATUS, status);
    irq_cfm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_CFM_ALARM_STATUS, status);
    irq_scm_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_SCM_ALARM_STATUS, status);
    irq_gst_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_GST_ALARM_STATUS, status);
    irq_lol_status = ES6514_GET_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_STATUS, IRQ_LOL_ALARM_STATUS, status);

    if (enable) {
        if ((ev_mask & VTSS_CLOCK_INPUT_LOS_EV) > 0) {
            mask_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_CLR_INT_ENA)   *   irq_los_status)      |
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_ACT_INT_ENA)   * ((irq_los_status+1)%2));
            mask_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_CLR_INT_ENA)   * ((irq_los_status+1)%2))|
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_ACT_INT_ENA)   *   irq_los_status);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_PFM_EV) > 0) {
            mask_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_CLR_INT_ENA) *   irq_pfm_status)      |
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_ACT_INT_ENA) * ((irq_pfm_status+1)%2));
            mask_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_CLR_INT_ENA) * ((irq_pfm_status+1)%2))|
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_ACT_INT_ENA) *   irq_pfm_status);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_CFM_EV) > 0) {
            mask_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_CLR_INT_ENA) *   irq_cfm_status)      |
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_ACT_INT_ENA) * ((irq_cfm_status+1)%2));
            mask_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_CLR_INT_ENA) * ((irq_cfm_status+1)%2))|
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_ACT_INT_ENA) *   irq_cfm_status);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_SCM_EV) > 0) {
            mask_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_CLR_INT_ENA) *   irq_scm_status)      |
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_ACT_INT_ENA) * ((irq_scm_status+1)%2));
            mask_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_CLR_INT_ENA) * ((irq_scm_status+1)%2))|
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_ACT_INT_ENA) *   irq_scm_status);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_GST_EV) > 0) {
            mask_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_CLR_INT_ENA) *   irq_gst_status)      |
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_ACT_INT_ENA) * ((irq_gst_status+1)%2));
            mask_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_CLR_INT_ENA) * ((irq_gst_status+1)%2))|
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_ACT_INT_ENA) *   irq_gst_status);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_LOL_EV) > 0) {
            mask_set |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_CLR_INT_ENA) *   irq_lol_status)      |
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_ACT_INT_ENA) * ((irq_lol_status+1)%2));
            mask_clr |= (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_CLR_INT_ENA) * ((irq_lol_status+1)%2))|
                        (ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_ACT_INT_ENA) *   irq_lol_status);
        }
        ES6514_WRXM_SET(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, clock_input, mask_set);
        ES6514_WRXM_CLR(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, clock_input, mask_clr);
    } else {
        if ((ev_mask & VTSS_CLOCK_INPUT_LOS_EV) > 0) {
            mask_clr |= ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_ACT_INT_ENA)   |
                        ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_EXT_LOS_CLR_INT_ENA)  ;
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_PFM_EV) > 0) {
            mask_clr |= ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_ACT_INT_ENA) |
                        ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_PFM_ALARM_CLR_INT_ENA);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_CFM_EV) > 0) {
            mask_clr |= ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_ACT_INT_ENA) |
                        ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_CFM_ALARM_CLR_INT_ENA);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_SCM_EV) > 0) {
            mask_clr |= ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_ACT_INT_ENA) |
                        ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_SCM_ALARM_CLR_INT_ENA);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_GST_EV) > 0) {
            mask_clr |= ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_ACT_INT_ENA) |
                        ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_GST_ALARM_CLR_INT_ENA);
        }
        if ((ev_mask & VTSS_CLOCK_INPUT_LOL_EV) > 0) {
            mask_clr |= ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_ACT_INT_ENA) |
                        ES6514_MSK_BIT(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, IRQ_LOL_ALARM_CLR_INT_ENA);
        }
        ES6514_WRXM_CLR(OMG_MAIN, OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG, clock_input, mask_clr);
    }

    return VTSS_RC_OK;
}

/* Clock dpll event polling function called by interrupt or periodicly */
static vtss_rc es6514_clock_dpll_event_poll(vtss_state_t                   *vtss_state,
                                     const vtss_clock_dpll_inst_t   dpll,
                                     vtss_clock_dpll_event_type_t   *const ev_mask)
{
    VTSS_E("function dpll_event_poll is not supported for es6514\n");
    return VTSS_RC_ERROR;
}

/* Enable clock dpll event generation for a specific event type */
static vtss_rc es6514_clock_dpll_event_enable(vtss_state_t                       *vtss_state,
                                       const vtss_clock_dpll_inst_t       dpll,
                                       const vtss_clock_dpll_event_type_t ev_mask,
                                       const BOOL                         enable)
{
    VTSS_E("function dpll_event_enable is not supported for es6514\n");
    return VTSS_RC_ERROR;
}


/* Synchronize the filter settings to a connected SD10g65 output that operates in SerDes mode */
vtss_rc vtss_omega_clock_output_filter_bw_refresh(vtss_state_t                       *vtss_state,
                                                   const u8                           clock_output)
{
    const u32 tgt = VTSS_TO_SD10G65(clock_output);
    u32 filt_fsel;
    ES6514_RDXF(OMG_MAIN, OMG_FILT_OMG_FILTER_MAIN, clock_output, FILT_F_SEL, &filt_fsel);
    ES6514_WRXF(SD10G65, SD10G65_TX_SYNTH_SD10G65_SSC_CFG1, tgt, SYNC_CTRL_FSEL,  filt_fsel);
    ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_SC,   clock_output, FILT_SC_SYNC_TIMER_SEL, 8);
    ES6514_WRXF(OMG_MAIN, OMG_FILT_OMG_FILTER_SC,   clock_output, FILT_SC_SYNC_TIMER_SEL, 0);
    ES6514_WRXM_SET(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, tgt,
                    ES6514_MSK_BIT(SD10G65, SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0, SYNTH_LS_ENA));


    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

vtss_rc vtss_es6514_clock_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_clock_state_t *state = &vtss_state->clock;
    u8                 i,j;
#if defined(VTSS_ARCH_SERVAL_T)
    u32  dig_tgt;
    u8 clock_output;
#endif //defined(VTSS_ARCH_SERVAL_T)
    switch (cmd) {
        case VTSS_INIT_CMD_CREATE:
            VTSS_D("VTSS_INIT_CMD_CREATE");
            //  Register Access
            state->rd                          = vtss_es6514_rd;
            state->wr                          = vtss_es6514_wr;
            state->wrm                         = vtss_es6514_wrm;

            //  Configuration 
            state->global_enable_set           = es6514_clock_global_enable_set;
            state->global_enable_get           = es6514_clock_global_enable_get;
            state->global_sw_reset             = es6514_clock_global_sw_reset;
            state->clock_shutdown              = es6514_clock_shutdown;
            state->selection_mode_set          = es6514_clock_selection_mode_set;
            state->selection_mode_get          = es6514_clock_selection_mode_get;
            state->operation_conf_set          = es6514_clock_operation_conf_set;
            state->operation_conf_get          = es6514_clock_operation_conf_get;
            state->ho_stack_conf_set           = es6514_clock_ho_stack_conf_set;
            state->ho_stack_conf_get           = es6514_clock_ho_stack_conf_get;
            state->ho_stack_content_get        = es6514_clock_ho_stack_content_get;
            state->dco_frequency_offset_set    = es6514_clock_dco_frequency_offset_set;
            state->dco_frequency_offset_get    = es6514_clock_dco_frequency_offset_get;
            state->output_filter_bw_set        = es6514_clock_output_filter_bw_set;
            state->output_filter_bw_get        = es6514_clock_output_filter_bw_get;
            state->output_filter_lock_fast_set = es6514_clock_output_filter_lock_fast_set;
            state->output_filter_lock_fast_get = es6514_clock_output_filter_lock_fast_get;
            state->output_psl_conf_set         = es6514_clock_output_psl_conf_set;
            state->output_psl_conf_get         = es6514_clock_output_psl_conf_get;
            state->adj_frequency_set           = es6514_clock_adj_frequency_set;
            state->adj_frequency_get           = es6514_clock_adj_frequency_get;
            state->adj_phase_set               = es6514_clock_adj_phase_set;
            state->adj_phase_get               = es6514_clock_adj_phase_get;
            state->priority_set                = es6514_clock_priority_set;
            state->priority_get                = es6514_clock_priority_get;
            state->input_frequency_set         = es6514_clock_input_frequency_set;
            state->input_frequency_get         = es6514_clock_input_frequency_get;
            state->input_frequency_ratio_set   = es6514_clock_input_frequency_ratio_set;
            state->input_frequency_ratio_get   = es6514_clock_input_frequency_ratio_get;
            state->output_frequency_set        = es6514_clock_output_frequency_set;
            state->output_frequency_get        = es6514_clock_output_frequency_get;
            state->output_frequency_ratio_set  = es6514_clock_output_frequency_ratio_set;
            state->output_frequency_ratio_get  = es6514_clock_output_frequency_ratio_get;
            state->output_level_set            = es6514_clock_output_level_set;
            state->output_level_get            = es6514_clock_output_level_get;
            state->output_selector_set         = es6514_clock_output_selector_set;
            state->output_selector_get         = es6514_clock_output_selector_get;
            state->input_alarm_conf_set        = es6514_clock_input_alarm_conf_set;
            state->input_alarm_conf_get        = es6514_clock_input_alarm_conf_get;
            state->input_cfm_conf_set          = es6514_clock_input_cfm_conf_set;
            state->input_cfm_conf_get          = es6514_clock_input_cfm_conf_get;
            state->input_pfm_conf_set          = es6514_clock_input_pfm_conf_set;
            state->input_pfm_conf_get          = es6514_clock_input_pfm_conf_get;
            state->input_gst_conf_set          = es6514_clock_input_gst_conf_set;
            state->input_gst_conf_get          = es6514_clock_input_gst_conf_get;

            //  Status
            state->selector_state_get          = es6514_clock_selector_state_get;
            state->dpll_state_get              = es6514_clock_dpll_state_get;
            state->ho_stack_frequency_offset_get = es6514_clock_ho_stack_frequency_offset_get;
            state->input_state_get             = es6514_clock_input_state_get;

            //  Event (interrupt) handling
            state->input_event_poll            = es6514_clock_input_event_poll;
            state->input_event_enable          = es6514_clock_input_event_enable;
            state->dpll_event_poll             = es6514_clock_dpll_event_poll;
            state->dpll_event_enable           = es6514_clock_dpll_event_enable;


            /* initialize constants */
            /* Number of DPLLs i.e. controllers in omega*/
            state->dpll_cnt = 2;
            /* Number of clock inputs / sources */
            state->clock_input_cnt = 4;
            /* Number of clock outputs / generated clocks */
            state->clock_output_cnt = 4;

            /* Max frequency offset in ppb for phase sift */
            state->phase_shift_max_freq_offset = 10000;  /* 10 ppm */

            /* Initialize semiconstant paramters */
            state->f2df_integ2_fsel = 35;

            /* initialize state variables */
            state->init_done     = FALSE;
            state->global_enable = FALSE;
            for (i = 0; i < state->dpll_cnt; i++) {
                state->selection_conf[i].mode = VTSS_CLOCK_SELECTION_MODE_DISABLED;
                state->selection_conf[i].clock_input = 0;
                state->dpll_conf[i].mode      = VTSS_CLOCK_OPERATION_MODE_DISABLED;
                state->dpll_conf[i].holdoff   = 500;
                state->dpll_conf[i].holdover  = 3000;
                state->dpll_conf[i].wtr       = 10;
                state->ho_stack_conf[i].ho_post_filtering_bw = 8898;
                state->ho_stack_conf[i].ho_qual_time_conf    = 10;
                for (j = 0; j < 2; j++) {
                    state->priority_selector[i][j].priority = j;
                    state->priority_selector[i][j].enable   = TRUE;
                }
                for (j = 2; j < state->clock_input_cnt; j++) {
                    state->priority_selector[i][j].priority = j;
                    state->priority_selector[i][j].enable   = FALSE;
                }
                state->emulated_ho_state[i] = FALSE;
            }

            for (i = 0; i < state->clock_input_cnt; i++) {
                state->input_frequency[i]                   = 0;
                state->input_sample_freq_khz[i]             = 3250000; /* set to reasonable default value*/
                state->use_internal_clock_src[i]            = 0;
                state->input_frequency_ratio[i].num         = 1;
                state->input_frequency_ratio[i].den         = 1;
                state->serdes_rx_en[i]                      = FALSE;
                state->cfm_conf[i].cfm_set_ppb              = 50000;
                state->cfm_conf[i].cfm_clr_ppb              = 50000;
                state->pfm_conf[i].pfm_set_ppb              = 213;
                state->pfm_conf[i].pfm_clr_ppb              = 213;
                state->gst_conf[i].disqualification_time_us = 100;
                state->gst_conf[i].qualification_time_us    = 100;
                state->gst_conf[i].los                      = FALSE;
                state->gst_conf[i].pfm                      = FALSE;
                state->gst_conf[i].cfm                      = FALSE;
                state->gst_conf[i].scm                      = FALSE;
                state->gst_conf[i].lol                      = FALSE;
                state->input_conf[i].los_active_high        = TRUE;
                state->input_conf[i].alarm_ena.los          = FALSE;
                state->input_conf[i].alarm_ena.pfm          = FALSE;
                state->input_conf[i].alarm_ena.cfm          = FALSE;
                state->input_conf[i].alarm_ena.scm          = FALSE;
                state->input_conf[i].alarm_ena.gst          = FALSE;
                state->input_conf[i].alarm_ena.lol          = FALSE;
            }

            for (i = 0; i < state->clock_output_cnt; i++) {
                state->output_frequency[i]             = 0;
                state->par_output_frequency[i]         = 0;
                state->output_frequency_ratio[i].num   = 1;
                state->output_frequency_ratio[i].den   = 1;
                state->output_level[i]                 = 900;
                state->adj_frequency[i]                = 0;
                state->serdes_tx_en[i]                 = FALSE;
                state->input_selector[i].input_type    = VTSS_CLOCK_INPUT_TYPE_DPLL;
                state->input_selector[i].input_inst    = 0;
                state->output_filter_bw[i]             = 0;
                state->psl_conf[i].limit_ppb           = 0;
                state->psl_conf[i].phase_build_out_ena = FALSE;                  
                state->psl_conf[i].ho_based            = FALSE;                  
            }

            break;
        case VTSS_INIT_CMD_INIT:
            VTSS_D("VTSS_INIT_CMD_INIT");
            VTSS_RC(vtss_es6514_init(vtss_state));
            break;
        case VTSS_INIT_CMD_PORT_MAP:
            VTSS_D("VTSS_INIT_CMD_PORT_MAP");
#if defined(VTSS_ARCH_SERVAL_T)
            /* Enable Serdes blocks  */
            int clock_inst;
            for (clock_inst = 0; clock_inst < 2; clock_inst++) {
                u32  xfi_tgt = VTSS_TO_PLL_XFI(clock_inst);
                VTSS_D("enable serdes inputs clock inst %d, xfi_tgt 0x%x", clock_inst, xfi_tgt);
                ES6514_WRXB(XFI_SHELL, XFI_CONTROL_XFI_MODE, xfi_tgt, SW_RST, 0);
                ES6514_WRXB(XFI_SHELL, XFI_CONTROL_XFI_MODE, xfi_tgt, SW_ENA, 1);
                ES6514_WRXB(XFI_SHELL, XFI_CONTROL_XFI_MODE, xfi_tgt, TX_RESYNC_SHOT, 1);
            }
            /* Serval-T and probably also upcomming devices must set their sync_ctrl source to 1 to select the Omega sync_ctrl info */
            for (clock_output = 2; clock_output < state->clock_output_cnt; clock_output++) {
                dig_tgt = VTSS_TO_SD10G65_DIG(clock_output);
                ES6514_WRXF(SD10G65_DIG, SD10G65_SYNC_CTRL_SYNC_CTRL_CFG, dig_tgt, LANE_SYNC_SRC, 1);
            }

#endif //VTSS_ARCH_SERVAL_T
            break;
        case VTSS_INIT_CMD_POLL:
            break;
        default:
            break;
    }
    return VTSS_RC_OK;
}

// ***************************************************************************
//
//  End of file.
//
// ***************************************************************************
#endif //defined(VTSS_FEATURE_CLOCK)
