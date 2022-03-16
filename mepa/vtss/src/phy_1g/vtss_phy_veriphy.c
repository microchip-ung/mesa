// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// Avoid "options.h not used in module vtss_phy_veriphy.c"
/*lint --e{766} */

#include <vtss_phy_api.h>

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_PHY_OPT_VERIPHY)

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#include "../ts/vtss_phy_ts.h"
#endif

#include "../common/vtss_phy_common.h"

#define SmiWrite(vtss_state, phy, reg, val) vtss_phy_wr(vtss_state, phy, reg, val)

/*- ExtMiiWrite is not applicable to Mustang VSC8201 PHY chips */
#define ExtMiiWrite(vtss_state, phy, reg, val) (void) SmiWrite(vtss_state, phy, 31, VTSS_PHY_PAGE_EXTENDED); (void) SmiWrite(vtss_state, phy, reg, val)
/*- GpioMiiWrite is only used to access Micro-Pages on PHY chips */
#define GpioMiiWrite(vtss_state, phy, reg, val) (void) SmiWrite(vtss_state, phy, 31, VTSS_PHY_PAGE_GPIO); (void) SmiWrite(vtss_state, phy, reg, val)

#define VTSS_PHY_1_GEN_DSP(port_no) ((port_family(vtss_state, port_no) == VTSS_PHY_FAMILY_MUSTANG) || \
                                     (port_family(vtss_state, port_no) == VTSS_PHY_FAMILY_COBRA))

/*  **************************************** */
/*  Veriphy settings                         */
/*  **************************************** */
#define MAX_SIGN_FLIP_ITERATIONS   100      // Orig=100

//#define VTSS_PHY_GEN_2_DSP(port_no) (FALSE) // Force Phy API veriPHY OFF
//#define VTSS_PHY_GEN_2_DSP(port_no) (TRUE)  // Force Phy API veriPHY ON
#define VTSS_PHY_GEN_2_DSP(port_no) ((port_family(vtss_state, port_no) == VTSS_PHY_FAMILY_NANO)) // Only on for NANO, other 65nm products have internal 8051

//#define USE_8051_RESET    // YES - Reset Internal 8051 so that it is not trying to run Veriphy Internally at the same time as Phy API
#undef USE_8051_RESET       // NO
/*  **************************************** */

static unsigned char xcSearchCoeffReadAveraging  = 3 << 3;// was hard-coded in Rev. A

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
extern FILE   *fp;
#endif

static int SmiRead(vtss_state_t *vtss_state, int port_no, int reg)
{
    u16 rv;
    (void) vtss_phy_rd(vtss_state, port_no, reg, &rv);
    return rv;
}

/* Local functions */
static int ExtMiiReadBits(vtss_state_t *vtss_state,
                          const vtss_port_no_t port, char reg, char msb, char lsb)
{
    int x;

    VTSS_RC(vtss_phy_page_ext(vtss_state, port));
    x = SmiRead(vtss_state, port, reg);
    if (msb < 15) {
        x &= (1 << (msb + 1)) - 1;
    }
    x = (int)((unsigned int) x >> lsb);

    return x;
}

static int MiiReadBits(vtss_state_t *vtss_state,
                       const vtss_port_no_t port, char reg, char msb, char lsb)
{
    int x;

    (void) vtss_phy_page_std(vtss_state, port);
    x = SmiRead(vtss_state, port, reg);
    if (msb < 15) {
        x &= (1 << (msb + 1)) - 1;
    }
    x = (int)((unsigned int) x >> lsb);

    return x;
}

static void MiiWriteBits(vtss_state_t *vtss_state,
                         const vtss_port_no_t port, char reg, char msb, char lsb, i8 value)
{
    int x;
    unsigned int t = 1, mask;

    (void)vtss_phy_page_std(vtss_state, port);
    x = SmiRead(vtss_state, port, reg);
    mask = (((t << (msb - lsb + 1)) - t) << lsb);
    x = ((value << lsb) & mask) | (x & (~mask));
    (void) SmiWrite(vtss_state, port, reg, x);
}

static int TpReadBits(vtss_state_t *vtss_state,
                      const vtss_port_no_t port, char reg, char msb, char lsb)
{
    int x;

    (void) vtss_phy_page_test(vtss_state, port);
    x = SmiRead(vtss_state, port, reg);
    if (msb < 15) {
        x &= (1 << (msb + 1)) - 1;
    }
    x = (int)((unsigned int) x >> lsb);

    return x;
}

static void TpWriteBit(vtss_state_t *vtss_state,
                       const vtss_port_no_t port, i8 TpReg, i8 bitNum, i8 value)
{
    short val;

    (void) vtss_phy_page_test(vtss_state, port);
    val = SmiRead(vtss_state, port, TpReg);
    if (value) {
        val = val | (1 << bitNum);
    } else {
        val = val & ~(1 << bitNum);
    }
    (void) vtss_phy_wr(vtss_state, port, TpReg, val);
}

/* PHY family */
static vtss_phy_family_t port_family(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_state->phy_state[port_no].family;
}

static vtss_rc tr_raw_read(vtss_state_t *vtss_state,
                           const vtss_port_no_t port, const u16 TrSubchanNodeAddr, u32 *tr_raw_data)
{
    u16 x;
    mepa_mtimer_t timer;
    u32 base;

    /* Determine base address */
    /* base = (port_family(port) == VTSS_PHY_FAMILY_MUSTANG ? 0 : 16); */
    base = VTSS_PHY_1_GEN_DSP(port) ? 0 : 16;
    VTSS_RC(vtss_phy_wr(vtss_state, port, base, (5 << 13) | TrSubchanNodeAddr));
    MEPA_MTIMER_START(&timer, 500);

    while (1) {
        VTSS_RC(vtss_phy_rd(vtss_state, port, base, &x));
        if (x & 0x8000) {
            break;
        }
        if (MEPA_MTIMER_TIMEOUT(&timer)) {
            MEPA_MTIMER_CANCEL(&timer);
            return VTSS_RC_ERROR; /*- should not happen */
        }
    }
    MEPA_MTIMER_CANCEL(&timer);

    VTSS_RC(vtss_phy_rd(vtss_state, port, base + 2, &x)); /*- high part */
    *tr_raw_data = (u32) x << 16;
    VTSS_RC(vtss_phy_rd(vtss_state, port, base + 1, &x)); /*- low part */
    *tr_raw_data |= x;

    return VTSS_RC_OK;
}

static vtss_rc tr_raw_write(vtss_state_t *vtss_state,
                            u8 port_no, u16 ctrl_word, u32 val)
{
    u32 base;

    /* Determine base address */
    /* base = (port_family(port_no) == VTSS_PHY_FAMILY_MUSTANG ? 0 : 16); */
    base = VTSS_PHY_1_GEN_DSP(port_no) ? 0 : 16;

    VTSS_RC(vtss_phy_wr(vtss_state, port_no, base + 2, val >> 16));   /*- high part */
    VTSS_RC(vtss_phy_wr(vtss_state, port_no, base + 1, (u16) val));  /*- low part */
    VTSS_RC(vtss_phy_wr(vtss_state, port_no, base, (4 << 13) | ctrl_word));

    return VTSS_RC_OK;
}

/*- Function issues a "long read" command to read Token Ring Registers */
/*- in the VSC8201 Mustang PHY. Results appear in Token Ring Registers 1-20 -*/
static vtss_rc tr_raw_long_read(vtss_state_t *vtss_state,
                                u8 subchan_phy, const u16 TrSubchanNode)
{
    u16 x, phy_num;
    mepa_mtimer_t timer;

    phy_num = subchan_phy & 0x3f;
    VTSS_RC(vtss_phy_page_tr(vtss_state, phy_num));
    VTSS_RC(vtss_phy_wr(vtss_state, phy_num, 0, TrSubchanNode));

    MEPA_MTIMER_START(&timer, 500);
    while (1) {
        VTSS_RC(vtss_phy_rd(vtss_state, phy_num, 0, &x));
        if (x & 0x8000) {
            break;
        }
        if (MEPA_MTIMER_TIMEOUT(&timer)) {
            MEPA_MTIMER_CANCEL(&timer);
            return VTSS_RC_ERROR; /*- should not happen */
        }
    }
    MEPA_MTIMER_CANCEL(&timer);
    return VTSS_RC_OK;
}

/*- Processes the Result from reading an EC debug node */
static vtss_rc process_ec_result(vtss_state_t *vtss_state,
                                 u8 subchan_phy, u16 tap, u32 *tr_raw_data)
{
    u16 reg_beg, reg_end, reg_beg_msb, reg_end_lsb;
    u16 x, y, phy_num;
    u32 ret;
    u16 firstbit, bitwidth;
    phy_num = subchan_phy & 0x3f;

    firstbit = (subchan_phy >> 6) * 68;
    bitwidth = 15;

    if (tap < 16) {
        bitwidth = 20;
    } else {
        firstbit += 20;
        if (tap < 32) {
            bitwidth = 18;
        } else {
            firstbit += 18;
            if (tap >= 48) {
                firstbit += 15;
            }
        }
    }
    reg_beg = 20 - (firstbit >> 4);
    reg_beg_msb = 15 - (firstbit & 0xf);
    reg_end = 20 - ((firstbit + bitwidth - 1) >> 4);
    reg_end_lsb = 15 - ((firstbit + bitwidth - 1) & 0xf);

    if (reg_beg == reg_end) {
        VTSS_RC(vtss_phy_rd(vtss_state, phy_num, reg_beg, &x));
        x &= (1 << (reg_beg_msb + 1)) - 1;
        ret = x >> reg_end_lsb;
    } else if (reg_beg == (reg_end + 1)) {
        VTSS_RC(vtss_phy_rd(vtss_state, phy_num, reg_beg, &x));
        x &= (1 << (reg_beg_msb + 1)) - 1;
        ret = (u32)x << (16 - reg_end_lsb);
        VTSS_RC(vtss_phy_rd(vtss_state, phy_num, reg_end, &y));
        y >>= reg_end_lsb;
        ret += y;
    } else {
        /*- This case cannot happen -*/
        return -1;
    }
    if (ret >= (u32)(1L << (bitwidth - 1))) {
        ret -= (1L << bitwidth);
    }

    *tr_raw_data = ret;

    return VTSS_RC_OK;
}

/*- Processes the result from reading an ECVar/NC debug node */
static vtss_rc process_var_result(vtss_state_t *vtss_state,
                                  u8 subchan_phy, u16 flt, u32 *tr_raw_data)
{
    u16 reg_beg, reg_end, reg_beg_msb, reg_end_lsb;
    u16 x, y, phy_num, sub_chan, scl = 0;
    u16 firstbit, bitwidth;

    reg_beg = reg_end = reg_beg_msb = reg_end_lsb = x = 0;
    phy_num = subchan_phy & 0x3f;
    sub_chan =     subchan_phy >> 6;
    bitwidth = 15;

    switch (flt) {
    case 0:        /*- NC1 -*/
    case 1:        /*- NC2 -*/
    case 2:        /*- NC3 -*/
        scl = (sub_chan << 2) - sub_chan + flt;
        break;
    case 3:        /*- ECVar -*/
        scl = sub_chan + (((flt + 1) << 2) - (flt + 1));
        break;
    default:    /*- will never get here -*/
        break;
    }
    firstbit = (scl << 4) - scl;

    reg_beg = 20 - (firstbit >> 4);
    reg_beg_msb = 15 - (firstbit & 0xf);
    reg_end = 20 - ((firstbit + bitwidth - 1) >> 4);
    reg_end_lsb = 15 - ((firstbit + bitwidth - 1) & 0xf);

    if (reg_beg == reg_end) {
        VTSS_RC(vtss_phy_rd(vtss_state, phy_num, reg_beg, &x));
        x &= (u16)((1L << (reg_beg_msb + 1)) - 1);
        x >>= reg_end_lsb;
    } else if (reg_beg == (reg_end + 1)) {
        VTSS_RC(vtss_phy_rd(vtss_state, phy_num, reg_beg, &x));
        x &= (u16)((1L << (reg_beg_msb + 1)) - 1);
        x <<= 16 - reg_end_lsb;
        VTSS_RC(vtss_phy_rd(vtss_state, phy_num, reg_end, &y));
        y >>= reg_end_lsb;
        x += y;
    } else {
        /*- This case cannot happen -*/
        return -1;
    }
    if (x >= (1 << (bitwidth - 1))) {
        x -= (1 << bitwidth);
    }

    *tr_raw_data = (u32)((long)((short)x));

    return VTSS_RC_OK;
}
static vtss_rc vtss_phy_1_gen_pre_veriphy(vtss_state_t *vtss_state,
                                          vtss_phy_family_t family, vtss_veriphy_task_t c51_idata *tsk)
{
    u32 x;
    BOOL conf_none;

    tsk->saveReg = 0;
    tsk->tokenReg = 0;

    VTSS_D("family = %d ", family);
    if (family == VTSS_PHY_FAMILY_MUSTANG) {
        /*- MII Registers 0, 9, 28 saved and modified */
        /*- TP[5.4:3], MII [28.2], MII[9.12:11], MII[0] - 21 bits */
        tsk->saveReg |= SmiRead(vtss_state, tsk->port, 0);
        tsk->saveReg |= ((MiiReadBits(vtss_state, tsk->port, 9, 12, 11)) << 16);
        tsk->saveReg |= ((MiiReadBits(vtss_state, tsk->port, 28, 2, 2)) << 18);
        MiiWriteBits(vtss_state, tsk->port, 28, 2, 2, 1);    /*- SMI Register priority select */
        tsk->saveReg |= ((TpReadBits(vtss_state, tsk->port, 5, 4, 3)) << 19);
    } else { /* family == VTSS_PHY_FAMILY_COBRA */
        /*- MII Register 0, 4, 9 saved */
        /*- MII [23.15:12], MII [23.3:2], MII [9.12:8], MII [4.11:5], MII [0.14:6]  - 27 bits */
        tsk->saveReg |= (MiiReadBits(vtss_state, tsk->port, 0, 14, 6));
        tsk->saveReg |= ((MiiReadBits(vtss_state, tsk->port, 4, 11, 5)) << 9);
        tsk->saveReg |= ((MiiReadBits(vtss_state, tsk->port, 9, 12, 8)) << 16);
        tsk->saveReg |= ((MiiReadBits(vtss_state, tsk->port, 23, 2, 1)) << 21);
        tsk->saveReg |= ((MiiReadBits(vtss_state, tsk->port, 23, 15, 12)) << 23);

        VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
        /*
        tsk->saveReg = SmiRead(vtss_state, tsk->port, 23) & 0xf006;
        tsk->saveReg = (tsk->saveReg & 0xf000) | ((tsk->saveReg & 6) << 9);
        tsk->saveReg = tsk->saveReg << 10;
        */

        VTSS_RC(vtss_phy_wr_masked(vtss_state, tsk->port, 23, 0x1004, 0xf006));
        conf_none = vtss_state->phy_state[tsk->port].conf_none;
        vtss_state->phy_state[tsk->port].conf_none = 0;
        VTSS_RC(vtss_phy_reset_private(vtss_state, tsk->port));
        vtss_state->phy_state[tsk->port].conf_none = conf_none;
        VTSS_RC(vtss_phy_wr_masked(vtss_state, tsk->port, 28, 0x0000, 0x0040));
    }
    MiiWriteBits(vtss_state, tsk->port, 9, 12, 11, 3);    /*- Forced Master */
    VTSS_RC(SmiWrite(vtss_state, tsk->port, 0, 0x0140));           /*- Force 1000 Base-T Duplex */

    /*- Test Page Registers 5, 8 saved and modified */
    VTSS_RC(vtss_phy_page_test(vtss_state, tsk->port));
    TpWriteBit(vtss_state, tsk->port, 5, 4, 1);     /*- Force MDIX */
    TpWriteBit(vtss_state, tsk->port, 5, 3, 1);

    /*- Some Token Ring Values modified are saved for Mustang only */
    /*- Token ring values are saved as follows: */
    /*- Bit [5:0] XcDecRateForce/Val, [8:6] NcUpdGainForce/Val, */
    /*- Bit [11:9] EcUpdGainForce/Val - 0x1680*/
    /*- Bit [13:12] EcLoadNew32_63Force/Val, [18:14] EcLoadNew0_15Force/Val, */
    /*- Bit [20:19] EcShiftBy16Force/Val, [22:21] EnableECvarDelayForce/Val - 0x0f86 */
    /*- Bit [24:23] EcTailClearForceVal - 0x0f82 */
    /*- Bit [28:25] VgaStartupGain - 0xfa0*/
    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));

    /*- Force ECdisabLast48Force/Val, DigPhaseForce/Val */
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xf8a /*1, 0xf, 5*/, &x));
    x = (x & ~0x1fc) | 0x108;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xf8a, x));

    /*- EcUpdGainForce/Val, NcUpdGainForce/Val, XcDecRateForce/Val */
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x1680 /*2, 0xd, 0*/, &x));
    if (family == VTSS_PHY_FAMILY_MUSTANG) {
        tsk->tokenReg = ((x >> 11) & 0xfff);
    }
    x = (x & ~0x3ffc00L) | 0x3ffc00L;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x1680, x));

    /*- EcLoadNew32_63Force/Val, EcLoadNew0_15Force/Val, */
    /*- EcShiftBy16Force/Val, EnableECvarDelayForce/Val */
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xf86 /* 1, 0xf, 3 */, &x));
    if (family == VTSS_PHY_FAMILY_MUSTANG) {
        tsk->tokenReg |= ((x >> 11) & 0x7ff) << 12;
    }
    x = (x & ~0x3ff800L) | 0x3a1000L;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xf86, x));

    /*- SlicerSelForce/Val, SignalDetectEnableForce/Val */
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xf88 /*01, 0xf, 4*/, &x));
    x = (x & ~0x1f00) | 0x1200;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xf88, x));

    /*- EcTailClearForce/Val */
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xf82 /* 1, 0xf, 1 */, &x));
    if (family == VTSS_PHY_FAMILY_MUSTANG) {
        tsk->tokenReg |= ((x >> 3) & 3) << 23;
    }
    x = (x & ~0x180) | 0x100;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xf82, x));

    /*- VgaStartupGain and set VgaAFreezeForceVal */
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xfa0 /*1, 0xf, 0x10*/, &x));
    if (family == VTSS_PHY_FAMILY_MUSTANG) {
        tsk->tokenReg |= ((x >> 8) & 0x1f) << 25;
    }
    x = (x & ~0x7f00) | 0x6800;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xfa0, x));

    /*- VgaBFreezeForceVal, VgaCFreezeForceVal,VgaDFreezeForceVal */
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xfa2 /*1, 0xf, 0x11 */, &x));
    x = (x & ~0x30303) | 0x30303;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xfa2, x));

    /*- Ffe[A-D]ForceUpdateDisab, Ffe[A-D]ForceGainswapDisab */
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x240 /*0, 4, 0x20 */, &x));
    x = (x & ~0xff) | 0xff;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x240, x));

    /*- DSPReadyForceVal */
    if (family == VTSS_PHY_FAMILY_MUSTANG) {
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x770 /*0, 0xe, 0x38*/, &x));
        x = (x & ~0x0c) | 8;
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x770, x));
    } else { /* family == VTSS_PHY_FAMILY_COBRA) */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x708, &x));
        x = (x & ~0xff0) | 0xaa0;
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x708, x));
    }

    /* TpWriteBit(vtss_state, tsk->port, 8, 9, 1); */
    VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
    MiiWriteBits(vtss_state, tsk->port, 0, 11, 11, 1);        /*- Power-down */
    MiiWriteBits(vtss_state, tsk->port, 0, 11, 11, 0);        /*- Power-up */

    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
    /*- DSPclear[A-D}*/
    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x1684, /* 2, 0xd, 2 */&x));
    x = (x & ~0x3fc000L) | 0x3c0000L;
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x1684, x));

    /*- Save SignalDetectForceVal */
    if (family == VTSS_PHY_FAMILY_MUSTANG) {
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x0770 /* 0, 0x0e, 0x38 */, &x));
        x = (x & ~3) | 3;
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0770, x));
    } else { /*- family == VTSS_PHY_FAMILY_COBRA */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x708, &x));
        x = (x & ~0x0c) | 0x0c;
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x708, x));
    }
    return vtss_phy_page_std(vtss_state, tsk->port);
}

static vtss_rc vtss_phy_1_gen_post_veriphy(vtss_state_t *vtss_state,
                                           vtss_phy_family_t family, vtss_veriphy_task_t c51_idata *tsk)
{
    u32 x;
    BOOL conf_none;
    VTSS_I("Family:%d", family);
    if (family == VTSS_PHY_FAMILY_MUSTANG) {
        /*- Token ring values are saved as follows: */
        /*- Bit [5:0] XcDecRateForce/Val, [8:6] NcUpdGainForce/Val, */
        /*- Bit [11:9] EcUpdGainForce/Val - 0x1680*/
        /*- Bit [13:12] EcLoadNew32_63Force/Val, [18:14] EcLoadNew0_15Force/Val, */
        /*- Bit [20:19] EcShiftBy16Force/Val, [22:21] EnableECvarDelayForce/Val - 0x0f86 */
        /*- Bit [24:23] EcTailClearForce/Val - 0x0f82 */
        /*- Bit [29:25] VgaStartupGain - 0xfa0*/

        VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
        /*- Unforce SignalDetectForce/Val, DSPReadyForce/Val */
        \
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x770 /*0, 0xe, 0x38 */, &x));
        x = (x & ~0xf);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x770, x));

        /*- Unforce ECdisabLast48Force/Val, DigPhaseForce/Val    */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xf8a, &x));
        x = (x & ~0x1fc);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xf8a, x));

        /*- Restore EcUpdGainForce/Val, NCUpdGainForce/Val, XcDecRateForce/Val */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x1680, &x));
        x = (x & ~0x3ffc00) | ((tsk->tokenReg  & 0xfff) << 10);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x1680, x));

        /*- Restore EcLoadNew32_63Force/Val, EcLoadNew0_15Force/Val, */
        /*- EcShiftBy16Force/Val, EnbleECvarDelayForce/Val */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xf86, &x));
        x = (x & ~0x3ff800) | (((tsk->tokenReg >> 12) & 0x7ff) << 11);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xf86, x));

        /*- Unforce SignalDetectEnableForceVal, SlicerSelForceVal */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xf88, &x));
        x = (x & ~0x1f00);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xf88, x));

        /*- Restore EcTailClearForceVal */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xf82, &x));
        x = (x & ~0x18) | (((tsk->tokenReg >> 23) & 0x3) << 3);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xf82, x));
        /*- Restore original VgaStartupGain & unforce VgaAFreezeForce/Val */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xfa0, &x));
        x = (x & ~0x7f00) | (((tsk->tokenReg >> 25) & 0x1f) << 8);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xfa0, x));

        /*- Unforce VgaBFreezeForceVal, VgaCFreezeForceVal, VgaDFreezeForceVal */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0xfa2, &x));
        x = (x & ~0x30303);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0xfa2, x));

        /*- Unforce Ffe[A-D]ForceUpdateDisab, Ffe[A-D]ForceGainswapDisab */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x240, &x));
        x = (x & ~0xff);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x240, x));

        /*- Unforce DSPclear[A-D] */
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x1684, &x));
        x = (x & ~0x3fc000L);
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x1684, x));

        /*- Restore Test Page [5] and MII [28, 9 ,0] Register settings */
        TpWriteBit(vtss_state, tsk->port, 5, 4, ((tsk->saveReg >> 20) & 1));
        TpWriteBit(vtss_state, tsk->port, 5, 3, ((tsk->saveReg >> 19) & 1));
        MiiWriteBits(vtss_state, tsk->port, 9, 12, 11, ((tsk->saveReg >> 16) & 3));
        VTSS_RC(SmiWrite(vtss_state, tsk->port, 0, (tsk->saveReg & 0xffff)));
        MiiWriteBits(vtss_state, tsk->port, 28, 2, 2, ((tsk->saveReg >> 18) & 1));
        MiiWriteBits(vtss_state, tsk->port, 0, 11, 11, 1);        /*- Power-down */
        MiiWriteBits(vtss_state, tsk->port, 0, 11, 11, 0);        /*- Power-up */
    } else { /* (family == VTSS_PHY_FAMILY_COBRA) */
        u16 reg23 = 0;

        VTSS_RC(vtss_phy_page_test(vtss_state, tsk->port));
        VTSS_RC(vtss_phy_wr_masked(vtss_state, tsk->port, 8, 0, 0x0002));
        VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
        VTSS_RC(vtss_phy_wr_masked(vtss_state, tsk->port, 22, 0, 0x0200));
        /* tsk->saveReg = ((tsk->saveReg & 0x3c00000L) >> 10) | ((tsk->saveReg & 0x0300000L) >> 19); */

        /*- MII [23.15:12], MII [23.3:2], MII [9.12:8], MII [4.11:5], MII [0.14:6]  - 27 bits */
        reg23 = ((tsk->saveReg & 0x7800000L) >> 11) | ((tsk->saveReg & 0x600000L) >> 20);
        VTSS_RC(vtss_phy_wr_masked(vtss_state, tsk->port, 23, reg23, 0xf006));

        conf_none = vtss_state->phy_state[tsk->port].conf_none;
        vtss_state->phy_state[tsk->port].conf_none = 0;
        VTSS_RC(vtss_phy_reset_private(vtss_state, tsk->port));
        vtss_state->phy_state[tsk->port].conf_none = conf_none;

        VTSS_RC(vtss_phy_wr_masked(vtss_state, tsk->port, 9, ((tsk->saveReg & 0x1f0000L) >> 8), 0x1f00));
        VTSS_RC(vtss_phy_wr_masked(vtss_state, tsk->port, 4, (((tsk->saveReg & 0xfe00L) >> 9) << 5), 0xfe0));
        VTSS_RC(vtss_phy_wr_masked(vtss_state, tsk->port, 0, ((tsk->saveReg & 0x1ffL) << 6), 0x7fc0));
    }
    return vtss_phy_page_std(vtss_state, tsk->port);
}

/*- get_anom_thresh: determines threshold as a function of tap and EC/NC */
static void get_anom_thresh(vtss_veriphy_task_t c51_idata *tsk, u8 tap)
{
    short log2ThreshX256;
    register i8 sh;

    log2ThreshX256 = 542 - (8 * (short)tap) + tsk->log2VGAx256;
    if (tsk->nc != 0) {
        log2ThreshX256 -= 500;
    }
    tsk->thresh[0] = 256 + (log2ThreshX256 & 255);
    sh = (i8)(log2ThreshX256 >> 8);
    if (sh >= 0) {
        tsk->thresh[0] <<= sh;
    } else {
        tsk->thresh[0] >>= -sh;
        if (tsk->thresh[0] < 23) {
            tsk->thresh[0] = 23;
        }
    }

    if (tsk->flags & VERIPHY_FLAGS_LINKUP) {
        tsk->thresh[1]  = tsk->thresh[0] >> 1;    /*- anomaly = 1/2 open/short when link up   */
    } else {
        u8 idx;

        tsk->thresh[1] = 0;
        for (idx = 0; idx < 5; ++idx) { /*- anomaly = 1/3 open/short when link down */
            tsk->thresh[1] = (tsk->thresh[1] + tsk->thresh[0] + 2) >> 2;
        }
    }
    if (tsk->thresh[1] < 15) {
        tsk->thresh[1] = 15;
    }

    /*- Limit anomaly threshold to 12 lsbs less than tap range for each EC & NC tap */
    if ((tsk->thresh[1] > 1012) && ((tsk->nc > 0) || (tap >= 32))) {
        tsk->thresh[1] = 1012;
    } else if ((tsk->thresh[1] > 4084) && (tap >= 16)) {
        tsk->thresh[1] = 4084;
    } else if (tsk->thresh[1] > 8180) {
        tsk->thresh[1] = 8180;
    }
    VTSS_D("get_anom_thresh, thresh[0]=%d, thresh[1]=%d ", tsk->thresh[0], tsk->thresh[1]);
}


/* ********************************************************* */
/*               65 Nano-meter products                      */
/* ********************************************************* */
/* getAnomThresh_65nm: determines threshold as a function of tap and EC/NC for 65 nano-meter products */

static void getAnomThresh_65nm(vtss_veriphy_task_t c51_idata *tsk, u8 tap)
{
    short log2ThreshX256;
    register i8 sh;

    log2ThreshX256 = 450 - (9 * (short)tap) + tsk->log2VGAx256;
    VTSS_N("getAnomThresh_65nm - Entry: nc: %d, Flags: 0x%x, tsk->log2VGAx256= %d, log2ThreshX256=%d ",
           tsk->nc, tsk->flags, tsk->log2VGAx256, log2ThreshX256);

    if (tsk->nc != 0) {
        log2ThreshX256 -= 300;
    }

    tsk->thresh[0] = 256 + (log2ThreshX256 & 255);
    sh = (i8)(log2ThreshX256 >> 8);
    VTSS_N("getAnomThresh_65nm - thresh[0]=%d, log2ThreshX256=%d,   sh=%d ", tsk->thresh[0], log2ThreshX256, sh);

    if (sh >= 0) {
        tsk->thresh[0] <<= sh;
    } else {
        tsk->thresh[0] >>= -sh;
        if (tsk->thresh[0] < 23) {
            tsk->thresh[0] = 23;
        }
    }

    if (tsk->flags & VERIPHY_FLAGS_LINKUP) {
        tsk->thresh[1]  = tsk->thresh[0] >> 1;    /* anomaly = 1/2 open/short when link up   */
        VTSS_N("getAnomThresh_65nm - LinkUP (Thresh1 is half of Thresh0) - thresh[1]=%d, thresh[0]=%d ", tsk->thresh[1], tsk->thresh[0]);
    } else {
        u8 idx;

        tsk->thresh[1] = 0;
        for (idx = 0; idx < 5; ++idx) { /* anomaly = 1/3 open/short when link down */
            tsk->thresh[1] = (tsk->thresh[1] + tsk->thresh[0] + 2) >> 2;
        }
        VTSS_N("getAnomThresh_65nm - LinkDN - thresh[1]=%d, thresh[0]=%d ", tsk->thresh[1], tsk->thresh[0]);
    }

    if (tsk->thresh[1] < 17) {
        tsk->thresh[1] = 17;
        VTSS_N("getAnomThresh_65nm - FORCING: thresh[1]=%d ", tsk->thresh[1]);
    }

    /* Limit anomaly threshold to 12 lsbs less than tap range for each EC & NC tap */
    if ((tsk->thresh[1] > 1012) && ((tsk->nc > 0) || (tap >= 32))) {
        tsk->thresh[1] = 1012;
    } else if ((tsk->thresh[1] > 4084) && (tap >= 16)) {
        tsk->thresh[1] = 4084;
    } else if (tsk->thresh[1] > 8180) {
        tsk->thresh[1] = 8180;
    }
    VTSS_D("getAnomThresh_65nm - Exit thresh[0]=%d, thresh[1]=%d ", tsk->thresh[0], tsk->thresh[1]);
}

/*- readAvgECNCECVar: reads averaged echo/NEXT-canceller coefficients */
/*- numCoeffs must be less than or equal to 12 */
/*- rpt can be 1, 2, 3, 4, or 8! */
static short c51_idata *readAvgECNCECVar(vtss_state_t *vtss_state,
                                         u8 subchan_phy, u8 first, u8 rpt_numCoeffs)
{
    VTSS_D("readAvgECNCECVar(%d%c, %d #%d, rpt %d, discard=%d) ", subchan_phy & 0x3f, ('A' + (subchan_phy >> 6)), first,
           rpt_numCoeffs & 15, ((rpt_numCoeffs >> 4) & 7) + 1, (rpt_numCoeffs & DISCARD) ? 1 : 0);

    /* if (port_family(subchan_phy & 0x3f) == VTSS_PHY_FAMILY_MUSTANG) { */
    if (VTSS_PHY_1_GEN_DSP(subchan_phy & 0x3f)) {
        long c;
        u8 i, j, discrd_flg = 0, flt, numRpt = 0;
        i8 preScale;
        u16 TrSubchanNode = 0, SubchanNode = 0;
        u32 tr_raw_data = 0;

        VTSS_N("readAvgECNCECVar(%d%c, %d #%d, %d) returns ", subchan_phy & 0x3f, ('A' + (subchan_phy >> 6)), first, rpt_numCoeffs & 7, rpt_numCoeffs >> 3);
        vtss_state->phy_inst_state.maxAbsCoeff = c = 0;
        numRpt = ((rpt_numCoeffs >> 4) & 7) + 1;

        if (rpt_numCoeffs & DISCARD) {
            discrd_flg = 1;
            rpt_numCoeffs &= ~DISCARD;
        }

        if (!discrd_flg) {
            /*- Clear coefficients to be averaged */
            for (j = 0; j < 12; ++j) {
                vtss_state->phy_inst_state.coeff[j] = 0;
            }
        }

        /*- Figure out whether we are dealing with EC, ECVar or NCn -*/
        if (first & 0x80) {
            flt = first >> 6;
            if (flt == 2) {    /*- EC -*/
                SubchanNode = 7 << 13;
                VTSS_D("ECHO CANCELER, Sub-channel=%d, first tap=%d ", (subchan_phy >> 6), (first & 0x3f));
            } else if (flt == 3) { /* ECVar */
                SubchanNode = 0x1c1 << 7;
                VTSS_D("ECVar, Sub-channel=%d, first tap=%d ", (subchan_phy >> 6), (first & 0x3f));
            }
        } else { /*- NC -*/
            flt = first >> 5;
            SubchanNode = 0x1c1 << 7;
            VTSS_D("NC%d, Sub-channel=%d, first tap=%d ", (flt + 1), (subchan_phy >> 6), (first & 0x1f));
        }

        /*- Compute variable prescale factor -*/
        preScale = 0;
        if ((first & 0x80) && (flt == 2)) {        /*- EC -*/
            if ((first & 0x3f) < 16) {
                if (numRpt > 4) {
                    preScale = 3;
                } else if (numRpt > 2) {
                    preScale = 2;
                } else if (numRpt > 1) {
                    preScale = 1;
                }
            } else if ((first & 0x3f) < 32) {
                if (numRpt > 4 ) {
                    preScale = 1;
                }
            }
        }

        /*- Accumulate coefficients -*/
        for (i = 0; i < numRpt; ++i) {
            for (j = 0; j < (rpt_numCoeffs & 0x0f); ++j) {
                if ((first & 0x80) && (flt == 2)) {    /*- EC -*/
                    TrSubchanNode = SubchanNode | ((32 + ((first + j) & 0xf)) << 1);
                    (void) tr_raw_long_read(vtss_state, subchan_phy, TrSubchanNode);
                    (void) process_ec_result(vtss_state, subchan_phy, (first & 0x3f) + j, &tr_raw_data);
                } else {    /*- NC and ECVar -*/
                    TrSubchanNode = SubchanNode | ((32 + ((first & 0x1f) + j)) << 1);
                    (void) tr_raw_long_read(vtss_state, subchan_phy, TrSubchanNode);
                    (void) process_var_result(vtss_state, subchan_phy, flt, &tr_raw_data);
                }

                /*- Scale 8201 coefficients so they all fit w/in 16-bit word -*/
                c = (long)tr_raw_data;

                if (c > 0) {
                    if ((c >> 4) > vtss_state->phy_inst_state.maxAbsCoeff) {
                        vtss_state->phy_inst_state.maxAbsCoeff = c >> 4;
                    }
                } else if (-(c >> 4) > vtss_state->phy_inst_state.maxAbsCoeff) {
                    vtss_state->phy_inst_state.maxAbsCoeff = -(c >> 4);
                }

                if (!discrd_flg) {
                    /*- Must add pre-scale and post-scale as appropriate for c -*/
                    /*- Length of c is one of 16, 14, or 11 bits (after >> 4) -*/
                    vtss_state->phy_inst_state.coeff[j] += (c + (1 << (3 + preScale))) >> (4 + preScale);
                }
            }
        }

        /*- Compute Average Coefficient Values -*/
        if (!discrd_flg) {
            if (numRpt == 3) {
                for (j = 0; j <= (rpt_numCoeffs & 0xf); ++j) {
                    c = ((long)vtss_state->phy_inst_state.coeff[j]) << preScale;
                    for (i = 0; i < 4; ++i) {
                        c = (c >> 2) + ((long)vtss_state->phy_inst_state.coeff[j] << preScale);
                    }
                    vtss_state->phy_inst_state.coeff[j] = (c + 2) >> 2;
                }
            } else {      /*- Repeat == 1/2/4/8 -*/
                for (i = -preScale, j = numRpt; j > 1; ++i, j = j >> 1) {
                    ;
                }

                if (i > 0) {
                    for (j = 0; j <= (rpt_numCoeffs & 0xf ); ++j) {
                        vtss_state->phy_inst_state.coeff[j] = (vtss_state->phy_inst_state.coeff[j] + (1 << (i - 1))) >> i;
                    }
                }
            }
        }

        VTSS_D("{");
        for (j = 0; j < (rpt_numCoeffs & 0xf); ++j) {
            VTSS_D(" %d", vtss_state->phy_inst_state.coeff[j]);
        }
        VTSS_D(" }, ");
        VTSS_D("MaxAbsCoeff = %d ", vtss_state->phy_inst_state.maxAbsCoeff);
    } else {
        /* Not Mustang family */
        i8 i, preScale = 0;
        short c;
        u8 j, numRpt;
        u32 tr_raw_data;
        BOOL discrd_flg = 0;

        VTSS_N("readAvgECNCECVar(%d%c, %d #%d, rpt %d, discard=%d) ", subchan_phy & 0x3f, ('A' + (subchan_phy >> 6)), first, rpt_numCoeffs & 15, ((rpt_numCoeffs >> 4) & 7) + 1, (rpt_numCoeffs & DISCARD) ? 1 : 0);
        //**printf("readAvgECNCECVar(%d%c, %d #%d, rpt %d, discard=%d) \n", subchan_phy & 0x3f, ('A' + (subchan_phy >> 6)), first, rpt_numCoeffs & 15, ((rpt_numCoeffs >> 4) & 7) + 1, (rpt_numCoeffs & DISCARD) ? 1 : 0);

        vtss_state->phy_inst_state.maxAbsCoeff = 0;
        numRpt = ((rpt_numCoeffs >> 4) & 7) + 1;

        if (rpt_numCoeffs & DISCARD) {
            preScale = -1;
            discrd_flg = 1;
            rpt_numCoeffs &= ~DISCARD;
        }

        if (!discrd_flg) {
            /*- Normal read & store coefficients -*/
            preScale = (first < 16 && numRpt >= 8) ? 1 : 0;

            /*- Clear coefficients to be averaged -*/
            for (j = 0; j < 8; ++j) {
                vtss_state->phy_inst_state.coeff[j] = 0;
            }
        }

        /*- Accumulate coefficients (pre-scaling when necessay for dynamic range) -*/
        for (i = 0; i < numRpt; ++i) {
            for (j = 0; j < (rpt_numCoeffs & 15); ++j) {
                (void) tr_raw_read(vtss_state, subchan_phy & 0x3f, ((u16)(subchan_phy & 0xc0) << 5)
                                   | ((u16)(j + first) << 1), &tr_raw_data);
                if (tr_raw_data & 0x2000 ) {
                    c = 0xc000 | (short)tr_raw_data;
                } else {
                    c = (short)tr_raw_data;
                }

                if (c > 0) {
                    if (c > vtss_state->phy_inst_state.maxAbsCoeff) {
                        vtss_state->phy_inst_state.maxAbsCoeff = c;
                    }
                } else if (-c > vtss_state->phy_inst_state.maxAbsCoeff) {
                    vtss_state->phy_inst_state.maxAbsCoeff = -c;
                }

                if (preScale >= 0) {
                    vtss_state->phy_inst_state.coeff[j] += c >> preScale;
                }
            }
        }

        if (preScale >= 0) {
            if (numRpt == 3) {
                /*- Complete averaging by scaling coefficients -*/
                for (j = 0; j < (rpt_numCoeffs & 15); ++j) {
                    c = vtss_state->phy_inst_state.coeff[j];
                    for (i = 0; i < 4; ++i) {
                        c = (c >> 2) + vtss_state->phy_inst_state.coeff[j];
                    }
                    vtss_state->phy_inst_state.coeff[j] = (c + 2) >> 2;
                }
            } else {
                /*- Determine averaging scale-factor accounting for pre-scale -*/
                for (i = 0, j = numRpt >> preScale; j > 1; ++i, j = j >> 1) {
                    ;
                }

                /*- Complete averaging by scaling coefficients -*/
                for (j = 0; j < (rpt_numCoeffs & 15); ++j) {
                    vtss_state->phy_inst_state.coeff[j] = vtss_state->phy_inst_state.coeff[j] >> i;
                }
            }
            VTSS_D("{");
            for (j = 0; j < (rpt_numCoeffs & 15); ++j) {
                VTSS_D(" %d", vtss_state->phy_inst_state.coeff[j]);
            }
            VTSS_D(" }, ");
        }
        VTSS_D("MaxAbsCoeff = %d ", vtss_state->phy_inst_state.maxAbsCoeff);
    }
    /*- Return pointer to first coefficient that was read */
    return &vtss_state->phy_inst_state.coeff[0];
}

/* ********************************************************* */
/*               65 Nano-meter products                      */
/* ********************************************************* */
/* readAvgECNCECVar_65nm: reads averaged echo/NEXT-canceller coefficients for 65 nano-meter products */
/* numCoeffs must be less than or equal to 8 */
/* rpt can be 1, 2, 3, 4, or 8! */
static short c51_idata *readAvgECNCECVar_65nm(vtss_state_t *vtss_state,
                                              vtss_veriphy_task_t c51_idata *tsk,
                                              u8 first,
                                              i8 rpt_numCoeffsM1)
{
    BOOL discardCoeffs;
    i8 i;
    short c;
    u8 j;
    u32 tr_raw_data = 0;
    u8 phy_port = tsk->port;
    u16 subchan_phy = tsk->subchan;


    //maxAbsCoeff = 0;
    vtss_state->phy_inst_state.maxAbsCoeff = c = 0;

    // subchan_phy = A, B, C, D == Pair
    VTSS_D("readAvgECNCECVar_65nm(Port:%d, ch:%c, first:%d M1#%d, rpt %d, discard=%d) ", phy_port, ('A' + subchan_phy), first, rpt_numCoeffsM1, ((rpt_numCoeffsM1 >> 4) & 7) + 1, (rpt_numCoeffsM1 & DISCARD) ? 1 : 0);
    //printf("readAvgECNCECVar_65nm(Port:%d, ch:%c, first:%d M1#%d, rpt %d, discard=%d) \n", phy_port, ('A' + subchan_phy), first, rpt_numCoeffsM1, ((rpt_numCoeffsM1 >> 4) & 7) + 1, (rpt_numCoeffsM1 & DISCARD) ? 1 : 0);

    //T(TR_MOD_PORT,TR_LVL_CRIT,"VeriPHY readAvgECNCECVar_65nm(subchan %c, %d #%d, %d)", ('A'+subchan), first, rpt_numCoeffsM1 & 7, rpt_numCoeffsM1 >> 3);

    if (rpt_numCoeffsM1 < 0) {
        /* Discard coefficients after reading for maxAbsCoeff */
        discardCoeffs = TRUE;
        rpt_numCoeffsM1 = (rpt_numCoeffsM1 ^ 0xf8) + 0x08;
    } else {
        /* Normal read & store coefficients */
        discardCoeffs = FALSE;

        /* Clear coefficients to be averaged */
        for (j = 0; j < VTSS_PHY_INST_STATE_MAX_COEFF; ++j) {
            // coeff[j] = 0;
            vtss_state->phy_inst_state.coeff[j] = 0;
        }
    }

    /* Accumulate coefficients (pre-scaling when necessay for dynamic range) */
    /* Accumulate coefficients (pre-scaling when necessay for dynamic range) */
    //printf("readAvgECNCECVar_65nm(Port:%d, ch:%c, rpt_numCoeffM1 >> 3: %d, rpt_numCoeffM1 & 7 = %d) \n", phy_port, ('A' + subchan_phy), (rpt_numCoeffsM1 >> 3), (rpt_numCoeffsM1 & 7));
    (void) vtss_phy_page_tr(vtss_state, tsk->port);
    for (i = 0; i < (rpt_numCoeffsM1 >> 3); ++i) {
        for (j = 0; j <= (rpt_numCoeffsM1 & 7); ++j) {
            // TrRawRead(((unsigned short)subchan << 11) | ((unsigned short)(j + first) << 1));
            /*
             * <<<< NEED TO REALLY UNDERSTAND THIS READ AND MAKE SURE IT IS READING THE RIGHT PLACE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
             * subchan_phy = 0...3
             */
            (void) tr_raw_read(vtss_state, phy_port,
                               ((subchan_phy << 11) | ((unsigned short)(j + first) << 1)), &tr_raw_data);

            //printf("tr_raw_read(Port:%d, Addr: 0x%x,  Value: 0x%0x)\n", phy_port, (((unsigned short)subchan_phy << 11) | ((unsigned short)(j + first) << 1)), tr_raw_data);

            if (tr_raw_data & 0x2000 ) {
                c = 0xc000 | (short)tr_raw_data;
            } else {
                c = (short)tr_raw_data;
            }

            if (c > 0) {
                if (c > vtss_state->phy_inst_state.maxAbsCoeff) {
                    vtss_state->phy_inst_state.maxAbsCoeff = c;
                }
            } else if (-c > vtss_state->phy_inst_state.maxAbsCoeff) {
                vtss_state->phy_inst_state.maxAbsCoeff = -c;
            }

            if (!discardCoeffs) {
                //coeff[j] += c;
                vtss_state->phy_inst_state.coeff[j] += c;
            }
        }
    }

    if (!discardCoeffs) {
        if ((rpt_numCoeffsM1 & 0xf8) == (3 << 3)) {      /* 3 << 3 = 24 */
            /* Complete averaging by scaling coefficients */
            for (j = 0; j <= (rpt_numCoeffsM1 & 7); ++j) {
                // c = coeff[j];
                c = vtss_state->phy_inst_state.coeff[j];
                for (i = 0; i < 4; ++i) {
                    // c = (c >> 2) + coeff[j];
                    c = (c >> 2) + vtss_state->phy_inst_state.coeff[j];
                }
                // coeff[j] = (c + 2) >> 2;
                vtss_state->phy_inst_state.coeff[j] = (c + 2) >> 2;
            }
        } else {
            /* Determine averaging scale-factor accounting for pre-scale */  // What Exactly is this loop doing... just Incrementing i?
            for (i = 0, j = rpt_numCoeffsM1 >> 3; j > 1; ++i, j = j >> 1)
                ;

            /* Complete averaging by scaling coefficients */
            for (j = 0; j <= (rpt_numCoeffsM1 & 7); ++j) {
                // coeff[j] = coeff[j] >> i;
                vtss_state->phy_inst_state.coeff[j] = vtss_state->phy_inst_state.coeff[j] >> i;
            }
        }
    }

    //T(TR_MOD_PORT,TR_LVL_CRIT,"VeriPHY readAvgECNCECVar_65nm returns %03d, coeff = { %d, %d, %d, %d, %d, %d, %d, %d  }", maxAbsCoeff, coeff[0], coeff[1], coeff[2], coeff[3], coeff[4], coeff[5], coeff[6], coeff[7]);

    /* Return pointer to first coefficient that was read */
    //return &coeff[0];

    VTSS_D("readAvgECNCECVar_65nm: Port: %d, Ch: %c, St: 0x%x, 1st: %d, NC: %d, pthresh: %d, thresh: %d, coeff:,  %d, %d, %d, %d, %d, %d, %d, %d ",
           tsk->port, (tsk->subchan + 'A'), tsk->task_state, first, tsk->nc, tsk->thresh[1], tsk->thresh[0],
           vtss_state->phy_inst_state.coeff[0], vtss_state->phy_inst_state.coeff[1],
           vtss_state->phy_inst_state.coeff[2], vtss_state->phy_inst_state.coeff[3],
           vtss_state->phy_inst_state.coeff[4], vtss_state->phy_inst_state.coeff[5],
           vtss_state->phy_inst_state.coeff[6], vtss_state->phy_inst_state.coeff[7]);
    //**printf("readAvgECNCECVar_65nm: Port: %d, Ch: %c, St: 0x%x, 1st: %d, NC: %d, pthresh: %d, thresh: %d, coeff:,  %d, %d, %d, %d, %d, %d, %d, %d \n", tsk->port, (tsk->subchan + 'A'), tsk->task_state, first, tsk->nc, tsk->thresh[1], tsk->thresh[0], vtss_state->phy_inst_state.coeff[0], vtss_state->phy_inst_state.coeff[1], vtss_state->phy_inst_state.coeff[2], vtss_state->phy_inst_state.coeff[3], vtss_state->phy_inst_state.coeff[4], vtss_state->phy_inst_state.coeff[5], vtss_state->phy_inst_state.coeff[6], vtss_state->phy_inst_state.coeff[7]);


    return &vtss_state->phy_inst_state.coeff[0];
}


/*- checkValidity: checks the validity of results in case of far-end turn-on or near-end bug -*/
static BOOL checkValidity(vtss_state_t *vtss_state,
                          vtss_veriphy_task_t c51_idata *tsk, short noiseLimit)
{
    mepa_mtimer_t timer;
    i8 timeout = 0;
    vtss_phy_family_t family;

    if (tsk->flags & VERIPHY_FLAGS_LINKUP) {
        return 1;
    }

    family = port_family(vtss_state, tsk->port);

    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
    if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
        /* if (family == VTSS_PHY_FAMILY_MUSTANG) { */
        /*- EcVarForceDelayVal = 255 - 64, EcVarForceDelay = 1 , EcVarForceIdle = 1 then 0 */
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, (((255 - 64) << 2) | 3)));
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, (((255 - 64) << 2) | 2))); /*- EcVarForceIdle = 0 */
    }

    if (family == VTSS_PHY_FAMILY_QUATTRO ||
        family == VTSS_PHY_FAMILY_SPYDER ||
        family == VTSS_PHY_FAMILY_ENZO) {
        /*- EcVarForceDelayVal = 232 - 72, EcVarForceDelay = 1 */
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, (tsk->tr_raw0188 & 0xfffe00) | (160 << 1) | 1));
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0x02 << tsk->subchan)); /*- EcVar<subchan>ForceIdle = 1 */
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0)); /*- EcVar<subchan>ForceIdle = 0 */
    }

    MEPA_MSLEEP(1);
    /* if (family != VTSS_PHY_FAMILY_MUSTANG) { */
    if (!VTSS_PHY_1_GEN_DSP(tsk->port)) {
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, tsk->tr_raw0188)); /*- restore */
    }
    MEPA_MTIMER_START(&timer, 200);
    while (1) {
        if ((readAvgECNCECVar(vtss_state,
                              (tsk->subchan << 6) | tsk->port,
                              /* family == VTSS_PHY_FAMILY_MUSTANG ? 192 : 72, */
                              VTSS_PHY_1_GEN_DSP(tsk->port) ? 192 : 72,
                              0xb8), vtss_state->phy_inst_state.maxAbsCoeff) >= ((tsk->stat[(int)tsk->subchan] == 0) ? 4 : 1)) {
            break;
        }
        if (MEPA_MTIMER_TIMEOUT(&timer)) {
            timeout = 1;
            break;
        }
    }
    MEPA_MTIMER_CANCEL(&timer);
    /* if (family == VTSS_PHY_FAMILY_MUSTANG) { */
    if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, tsk->tr_raw0188 | 1)); /*- EcVarForceIdle = 1 */
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, tsk->tr_raw0188 | 0)); /*- EcVarForceIdle = 0 */
    } else {
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0x02 << tsk->subchan)); /*- EcVar<subchan>ForceIdle = 1 */
        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0)); /*- EcVar<subchan>ForceIdle = 0 */
    }

    if (timeout) {
        if (tsk->stat[(int)tsk->subchan] != 0) {  /*- Anomaly found, but invalid! */
            tsk->stat[(int)tsk->subchan]      = 0;
            tsk->loc[(int)tsk->subchan]       = 0;
            tsk->strength[(int)tsk->subchan]  = 0;
            VTSS_D("Invalid Anomaly Found");
        }
        return 0;
    } else if (vtss_state->phy_inst_state.maxAbsCoeff > noiseLimit) {
        if (tsk->stat[(int)tsk->subchan] == 0) {  /*- Length measurement invalid? */
            tsk->loc[(int)tsk->subchan] = 255;    /*- Block this subchannel's contribution */
            tsk->strength[(int)tsk->subchan] = vtss_state->phy_inst_state.maxAbsCoeff;
            VTSS_D("Length Invalid??? Block off this channel contribution...");
        } else {                      /*- Anomaly found, but invalid! */
            tsk->stat[(int)tsk->subchan]      = 0;
            tsk->loc[(int)tsk->subchan]       = 0;
            tsk->strength[(int)tsk->subchan]  = 0;
            VTSS_D("Invalid Anomaly");
        }
        return 0;
    } else if (tsk->stat[(int)tsk->subchan] == 0 && (vtss_state->phy_inst_state.maxAbsCoeff + 2) >= ABS(tsk->strength[(int)tsk->subchan]))  {
        tsk->thresh[(int)tsk->subchan]   = (vtss_state->phy_inst_state.maxAbsCoeff + 2);
        tsk->loc[(int)tsk->subchan]      = 0;
        tsk->strength[(int)tsk->subchan] = 0;
        VTSS_D(" thresh[%d] = %d, loc[%d] =0", (int)tsk->subchan, vtss_state->phy_inst_state.maxAbsCoeff + 2, (int)tsk->subchan);
        return 1;
    } else {
        return 10;
        VTSS_D(" Returning 10:  thresh[%d] = %d, loc[%d] =0 ", (int)tsk->subchan, vtss_state->phy_inst_state.maxAbsCoeff + 2, (int)tsk->subchan);
    }
    return 1;
}


/* ********************************************************* */
/*               65 Nano-meter products                      */
/* ********************************************************* */
/* checkValidity_65nm: checks the validity of results in case of far-end turn-on or near-end bug  */
/* If we detect something (160taps + base taps), and look for high levels of noise and then mark  */
/* the Anomoly that we just found has to be set as invalid. Cause is this channel or adjacent one */
static BOOL checkValidity_65nm(vtss_state_t *vtss_state,
                               vtss_veriphy_task_t c51_idata *tsk,
                               unsigned char noiseLimit)
{
    mepa_mtimer_t timer;
    int  retryCnt = 0;
    i8 timeout = 0;

    if (tsk->flags & VERIPHY_FLAGS_LINKUP) {
        VTSS_D("checkValidity_65nm: Link is UP!  Returning! ");
        return TRUE;
    }

    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));

    //TrRawData[0] = ((232 - 72) << 1) | 1;
    //TrRawData[1] = (tsk->TrRaw0188[1] & ~0x01) | ((232 - 72) >> 7);
    //TrRawData[2] = tsk->TrRaw0188[2];
    /*- EcVarForceDelayVal = 232 - 72, EcVarForceDelay = 1 */
    /*- Set the delay value for 160meter cable length, EcVarForeceDelay = set delay on ALL sub-chan A,B,C,D */
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, (tsk->tr_raw0188 & 0xfffe00) | (160 << 1) | 1));
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, (0x02 << (int)tsk->subchan))); /*- EcVar<subchan>ForceIdle = 1 */
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0));                      /*- EcVar<subchan>ForceIdle = 0 */

    MEPA_MSLEEP(1);

    /*- Restore the previous states */
    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, tsk->tr_raw0188));

    retryCnt = 0;
    MEPA_MTIMER_START(&timer, 200);  // Originally 200
    while (1) {
        /*- We are getting silence on the line, Retry until we get something that is not too quiet  */
        /*- Maybe there is spurious noise, Was this a length measurement or a Anomolous measurement */
        if ((readAvgECNCECVar_65nm(vtss_state,
                                   tsk,
                                   72,
                                   (i8)((u8)(-8) << 3) | 7),  // Don't clobber the coeff that we have
             vtss_state->phy_inst_state.maxAbsCoeff) < ((tsk->stat[(int)tsk->subchan] == 0) ? 4 : 1)) {
            MEPA_MSLEEP(2);   // Originally 2
            break;
        }
        if (MEPA_MTIMER_TIMEOUT(&timer)) {
            timeout = 1;
            break;
        }
        retryCnt++;
    }
    MEPA_MTIMER_CANCEL(&timer);

    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, (0x02 << (int)tsk->subchan))); /*- EcVar<subchan>ForceIdle = 1 */
    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0));                      /*- EcVar<subchan>ForceIdle = 0 */

    if (timeout) {
        VTSS_D("%s invalidated due to ZEROS (Timeout)!, RetryCnt= %d", (tsk->stat[tsk->subchan] >= 4) ? ((tsk->stat[tsk->subchan] >= 8) ? "Cross-pair short" : "Anomaly") : ((tsk->stat[tsk->subchan] >= 2) ? "Short" : ((tsk->stat[tsk->subchan] >= 1) ? "Open" : "Length")), retryCnt);
#if 0
        if (tsk->stat[(int)tsk->subchan] != 0) {  /* Only if we are doing an Anomoly search & found, but invalid! */
            tsk->stat[(int)tsk->subchan]      = 0;
            tsk->loc[(int)tsk->subchan]       = 0;
            tsk->strength[(int)tsk->subchan]  = 0;
            VTSS_D("Invalid Anomaly Found");
            printf("Timeout - Invalid Anomaly Found\n");
        }
#endif
        VTSS_D("Timeout - Anomaly Found - Not Invalidating");
        //printf("Timeout - Anomaly Found - Not Invalidating\n");
        return FALSE;

    } else if (vtss_state->phy_inst_state.maxAbsCoeff > (short)((unsigned short)noiseLimit)) {
        VTSS_D("%s invalidated due to noise, maxAbsCoeff = %d > %d", (tsk->stat[tsk->subchan] >= 4) ? ((tsk->stat[tsk->subchan] >= 8) ? "Cross-pair short" : "Anomaly") : ((tsk->stat[tsk->subchan] >= 2) ? "Short" : ((tsk->stat[tsk->subchan] >= 1) ? "Open" : "Length")), vtss_state->phy_inst_state.maxAbsCoeff, (int)noiseLimit);
        if (tsk->stat[(int)tsk->subchan] == 0) {  /* Length measurement invalid? */
            tsk->loc[(int)tsk->subchan] = 255;    /* Block this subchannel's contribution */
            tsk->strength[(int)tsk->subchan] = vtss_state->phy_inst_state.maxAbsCoeff;
            VTSS_D("Length Invalid??? Block off this channel contribution...");
        } else {                                  /* Anomaly found, but invalid! */
            tsk->stat[(int)tsk->subchan]      = 0;
            tsk->loc[(int)tsk->subchan]       = 0;
            tsk->strength[(int)tsk->subchan]  = 0;
            VTSS_D("Invalid Anomaly Found");
        }
        return FALSE;

    } else if (tsk->stat[(int)tsk->subchan] == 0 &&
               (vtss_state->phy_inst_state.maxAbsCoeff + 2) >= ABS(tsk->strength[(int)tsk->subchan]))  {
        VTSS_D("Adjusting threshold up from %d to %d", tsk->thresh[tsk->subchan], (vtss_state->phy_inst_state.maxAbsCoeff + 3));
        tsk->thresh[(int)tsk->subchan]   = (vtss_state->phy_inst_state.maxAbsCoeff + 2);
        tsk->loc[(int)tsk->subchan]      = 0;
        tsk->strength[(int)tsk->subchan] = 0;
        VTSS_D(" thresh[%d] = %d, loc[%d] =0", (int)tsk->subchan, vtss_state->phy_inst_state.maxAbsCoeff + 2, (int)tsk->subchan);
        return TRUE; /*- This is Valid, However, the threshold has been adjusted up in this case */

    } else {
        VTSS_D("\t%s is valid, maxAbsCoeff = %d <= %d ", (tsk->stat[(int)tsk->subchan] >= 4) ? ((tsk->stat[(int)tsk->subchan] >= 8) ? "Cross-pair short" : "Anomaly") : ((tsk->stat[(int)tsk->subchan] >= 2) ? "Short" : ((tsk->stat[(int)tsk->subchan] >= 1) ? "Open" : "Length")), vtss_state->phy_inst_state.maxAbsCoeff, (int)noiseLimit);
        //return (10);
        return TRUE; /*- This is Valid */
    }

    return TRUE;
}



/*- `: search for anomalous echo/cross-coupled pair within 8-tap range of EC/NC */
static void xc_search(vtss_state_t *vtss_state,
                      vtss_veriphy_task_t c51_idata *tsk, u8 locFirst, u8 prefix)
{
    u8 idx;
    short s;
    short c51_idata *c;

    VTSS_D("xc_search: locFirst = %d, prefix = %d ", locFirst, prefix);
    (void) vtss_phy_page_tr(vtss_state, tsk->port);
    c = readAvgECNCECVar(vtss_state, (tsk->subchan << 6) | tsk->port, tsk->firstCoeff,
                         (3 << 4) | tsk->numCoeffs);

    for (idx = (tsk->numCoeffs - 1), c += (tsk->numCoeffs - 1); (i8)idx >= 0; --idx, --c) {

        s = (short)(32L * (long) * c / (long)tsk->thresh[1]);
        VTSS_D("xc_search: Strength = %d", s);

        if (ABS(*c) > tsk->thresh[1]) {
            if ((ABS(s) <= ABS(tsk->strength[(int)tsk->subchan]))) {
                if ((tsk->signFlip < 0) && (tsk->stat[(int)tsk->subchan] < 4)
                    && (tsk->loc[(int)tsk->subchan] <= (locFirst + idx + 3))) {
                    if ((*c > 0) && (tsk->strength[(int)tsk->subchan] < 0)) {
                        tsk->stat[(int)tsk->subchan] = 2;
                        tsk->signFlip = 2;
                        if ((locFirst + idx) < prefix) {
                            tsk->loc[(int)tsk->subchan] = locFirst + idx;
                        }
                        VTSS_D("\txc_search: Open-->short flip @ tap %d, strength = %d", locFirst + idx, s);
                    } else if ((*c < 0) && (tsk->strength[(int)tsk->subchan] > 0)) {
                        tsk->stat[(int)tsk->subchan] = 1;
                        tsk->signFlip = 2;
                        if ((locFirst + idx) < prefix) {
                            tsk->loc[(int)tsk->subchan] = locFirst + idx;
                        }
                        VTSS_D("\txc_search: Short-->open flip @ tap %d, strength = %d", locFirst + idx, s);
                    }
                }
            } else if (((locFirst + idx) >= prefix) || /* Or, implies ((locFirst + idx) < prefix) && .. */
                       ((tsk->loc[(int)tsk->subchan] <= (locFirst + idx + 3)) &&
                        (tsk->stat[(int)tsk->subchan] > 0) && (tsk->stat[(int)tsk->subchan] <= 4))) {
                /*- magnitude is largest seen so far */
                if (*c < -tsk->thresh[0]) {
                    if ((tsk->loc[(int)tsk->subchan] <= (locFirst + idx + 3)) &&
                        (tsk->strength[(int)tsk->subchan] > 0) &&
                        (tsk->strength[(int)tsk->subchan] > (-s >> 1))) {
                        tsk->signFlip = 2;
                    }
                    tsk->stat[(int)tsk->subchan] = 1;
                    VTSS_D("\txc_search: Open  @ tap %d, strength = %d < -thresh = -%d", locFirst + idx, s, tsk->thresh[0]);
                } else if (*c > tsk->thresh[0]) {
                    if ((tsk->loc[(int)tsk->subchan] <= (locFirst + idx + 3)) &&
                        (tsk->strength[(int)tsk->subchan] < 0) &&
                        (-tsk->strength[(int)tsk->subchan] > (s >> 1))) {
                        tsk->signFlip = 2;
                    }
                    tsk->stat[(int)tsk->subchan] = 2;
                    VTSS_D("\txc_search: Short @ tap %d, strength = %d > +thresh = %d", locFirst + idx, s, tsk->thresh[0]);
                } else {
                    tsk->stat[(int)tsk->subchan] = 4;
                    VTSS_D("\txc_search: Anom. @ tap %d, strength = %d > thresh = %d", locFirst + idx, s, tsk->thresh[1]);
                }
                tsk->loc[(int)tsk->subchan] = locFirst + idx;
                tsk->strength[(int)tsk->subchan] = s;
            }
        }                       /*- end if (ABS(*c) > tsk->thresh[1]) */
        tsk->signFlip = tsk->signFlip - 1;
    }                           /*- end for ( idx = numCoeffsM1: (i8)idx >= 0; --idx, --c ) */
}


/* ********************************************************* */
/*               65 Nano-meter products                      */
/* ********************************************************* */
/*- xc_search_65nm: search for anomalous echo/cross-coupled pair within 8-tap range  */
/*- of EC/NC for 65 nano-meter products                                              */
/*- blip cancellor is being searched,  signFLip gets set to 2 to go 2 taps back      */
/*- the blip cancellor should have settled on the Max blip and we try and back off   */
/*- if we are looking a the echo cancellor, we are looking for continuity between    */
/*- groups of 8 taps.                                                                */
/*- 0-71 = Fixed Echo Cancellors, 72-79=blip cancellors, 80-95, 96-111, 112-127 are Next Cancellors */
static void xc_search_65nm(vtss_state_t *vtss_state, vtss_veriphy_task_t c51_idata *tsk, u8 locFirst, u8 prefix)
{
    unsigned char idx;
    short s;
    short c51_idata *c;

    VTSS_D("xc_search_65nm: locFirst = %d, prefix = %d", locFirst, prefix);
    (void) vtss_phy_page_tr(vtss_state, tsk->port);
    /*- Get the Values for this tap */
    //c = readAvgECNCECVar(tsk->subchan, tsk->firstCoeff, xcSearchCoeffReadAveraging | tsk->numCoeffsM1);
    c = readAvgECNCECVar_65nm(vtss_state, tsk, tsk->firstCoeff, (xcSearchCoeffReadAveraging | tsk->numCoeffs));
    VTSS_N("xc_search_65nm: numCoeffs: %d ", tsk->numCoeffs);
    for (idx = tsk->numCoeffs, c += tsk->numCoeffs; (signed char)idx >= 0; --idx, --c) {
        VTSS_N("xc_search_65nm: idx: %d, *c = x%x, thresh[1]= x%x", idx, ABS(*c), tsk->thresh[1]);
        /*- Is the value from the tap is above the threshold */
        if (ABS(*c) > tsk->thresh[1]) {
            /*- compute the relative strength, relative to anomolous threshold */
            s = (short)(32L * (long) * c / (long)tsk->thresh[1]);
            VTSS_N("xc_search_65nm: Strength = %d ", s);

            /*- if the strength of this tap is less than the relative strength I already found */
            /*- Prefix is usually 0 except for the first group, trying to mask off the Hybrid at the start */
            if ((ABS(s) <= ABS(tsk->strength[(int)tsk->subchan])
                 || ((locFirst + idx) < prefix))) {

                if ((tsk->signFlip < 0) &&
                    (tsk->stat[(int)tsk->subchan] < VTSS_VERIPHY_STATUS_ABNORM) &&
                    (tsk->loc[(int)tsk->subchan] <= (locFirst + idx + 3))) {

                    if ((*c > 0) && (tsk->strength[(int)tsk->subchan] < 0)) {
                        tsk->stat[(int)tsk->subchan] = VTSS_VERIPHY_STATUS_SHORT;
                        tsk->signFlip = 2;
                        if ((locFirst + idx) < prefix) {
                            tsk->loc[(int)tsk->subchan] = locFirst + idx;
                        }
                        VTSS_D("xc_search_65nm: Open-->short flip @ tap %d, strength = %d", locFirst + idx, s);
                    } else if ((*c < 0) && (tsk->strength[(int)tsk->subchan] > 0)) {
                        tsk->stat[(int)tsk->subchan] = VTSS_VERIPHY_STATUS_OPEN;
                        tsk->signFlip = 2;
                        if ((locFirst + idx) < prefix) {
                            tsk->loc[(int)tsk->subchan] = locFirst + idx;
                        }
                        VTSS_D("xc_search_65nm: Short-->open flip @ tap %d, strength = %d", locFirst + idx, s);
                    }
                }
            } else {   /* magnitude is largest seen so far & not in prefix taps, i.e. the closest taps */
                if (*c < -tsk->thresh[0]) {
                    /*- If the value at this location is greater than value 3 locations back */
                    /*- This is a sign flip, This is the current threshold crossing */
                    if ((tsk->loc[(int)tsk->subchan] <= (locFirst + idx + 3)) &&
                        (tsk->strength[(int)tsk->subchan] > 0)) {
                        tsk->signFlip = 2;
                    }
                    tsk->stat[(int)tsk->subchan] = VTSS_VERIPHY_STATUS_OPEN;
                    VTSS_D("xc_search_65nm: Open  @ tap %d, strength = %d < -thresh = -%d", locFirst + idx, s, tsk->thresh[0]);
                } else if (*c > tsk->thresh[0]) {
                    if ((tsk->loc[(int)tsk->subchan] <= (locFirst + idx + 3)) &&
                        (tsk->strength[(int)tsk->subchan] < 0)) {
                        tsk->signFlip = 2;
                    }
                    tsk->stat[(int)tsk->subchan] = VTSS_VERIPHY_STATUS_SHORT;
                    VTSS_D("xc_search_65nm: Short @ tap %d, strength = %d > +thresh = %d", locFirst + idx, s, tsk->thresh[0]);
                } else {
                    tsk->stat[tsk->subchan] = VTSS_VERIPHY_STATUS_ABNORM;
                    VTSS_D("xc_search_65nmAnom. @ tap %d, strength = %d > thresh = %d", locFirst + idx, s, tsk->thresh[1]);
                }
                tsk->loc[(int)tsk->subchan] = locFirst + idx; /*- Save the location of the anomoly */
                tsk->strength[(int)tsk->subchan] = s;         /*- Save the strength of the anomoly */
                VTSS_D("xc_search_65nm: idx: %d, loc[%d]: %d,  strength[%d]: %d ",
                       idx, (int)tsk->subchan, tsk->loc[(int)tsk->subchan], (int)tsk->subchan, tsk->strength[(int)tsk->subchan]);
            }
        }                       /* end if (ABS(*c) > tsk->thresh[1]) */
        tsk->signFlip = tsk->signFlip - 1;
        VTSS_N("xc_search_65nm: signFlip = %d ", tsk->signFlip);
    }                           /* end for ( idx = numCoeffsM1: (signed char)idx >= 0; --idx, --c ) */
}


static const int c51_code FFEinit4_7search[2][4] = {
    {  1,   3,  -3,  -1 }, /*- coeff-set for anomSearch */
    { 10,  30, -30, -10 }  /*- coeff-set for lengthSearch */
};


/*- FFEinit4_7: Initializes FFE taps 4-7 from selected table and taps 0-3 & 8-15 are cleared */
static void FFEinit4_7(vtss_state_t *vtss_state,
                       vtss_veriphy_task_t c51_idata *tsk, i8 taps4_7select)
{
    i8 idx, max;
    /* vtss_phy_family_t family;

    family = port_family(tsk->port);

    if (family == VTSS_PHY_FAMILY_MUSTANG) { */
    if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
        VTSS_D("In FFEinit4_7 PHY_1_GEN_DSP");
        max = 28;
        (void) tr_raw_write(vtss_state, tsk->port, 0x0240/*0, 3, 2*/, 0); /*- EcVar<subchan>ForceIdle = 0 */
    } else {
        max = 16;
        (void) tr_raw_write(vtss_state, tsk->port, 0x0240/*0, 4, 0x20*/, 0x100); /*- Set FfeWriteAllSubchans */
    }

    for (idx = 0; idx < max; ++idx) {      /*- Clear FFE except for taps 4-7 */
        (void) tr_raw_write(vtss_state, tsk->port, 0x0200 | (idx << 1)/*0, 4, idx*/, 0);
        if (idx == 3) {
            idx = 7;
        }
    }
    for (idx = 0; idx < 4; ++idx) {
        /* if (family == VTSS_PHY_FAMILY_MUSTANG) { */
        if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
            (void) tr_raw_write(vtss_state, tsk->port, 0x0200 | ((4 + idx) << 1)/*0, 4, 4+idx*/, ((long)FFEinit4_7search[(int)taps4_7select][(int)idx]) << 16);
        } else {
            (void) tr_raw_write(vtss_state, tsk->port, 0x0200 | ((4 + idx) << 1)/*0, 4, 4+idx*/, FFEinit4_7search[(int)taps4_7select][(int)idx] << 9);
        }
    }
    /* if (family == VTSS_PHY_FAMILY_MUSTANG) { */
    if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
        (void) tr_raw_write(vtss_state, tsk->port, 0x0240/*0, 4, 0x20*/, 0x0ff);        /*- Clear FfeWriteAllSubchans */
    } else {
        (void) tr_raw_write(vtss_state, tsk->port, 0x0240/*0, 4, 0x20*/, 0);      /*- Clear FfeWriteAllSubchans */
    }
}

/* ********************************************************* */
/*               65 Nano-meter products                      */
/* ********************************************************* */
#define FFEinit4_7anomSearch_65nm   1
#define FFEinit4_7lengthSearch_65nm 5
/* basis coeff-set for anomSearch */
static const signed char c51_code FFEinit4_7search_basis[4] = { 1,   3,  -3,  -1 };

/* FFEinit4_7_65nm: Initializes FFE taps 4-7 from selected table and taps 0-3 & 8-15 are cleared for 65 nano-meter prods*/
static void FFEinit4_7_65nm(vtss_state_t *vtss_state,
                            vtss_veriphy_task_t c51_idata *tsk, char tapScaleFactor)
{
    unsigned char idx;
    signed   char val;
    u32      trRawData = 0;

    VTSS_D("FFEinit4_7_65nm: ScaleFactor: %d", tapScaleFactor);
    trRawData = 0x100;
    (void) tr_raw_write(vtss_state, tsk->port, 0x0240/*0, 4, 0x20*/, trRawData); /*- Set FfeWriteAllSubchans */

    trRawData = 0x0;
    for (idx = 0; idx < 16; ++idx) {      /* Clear FFE except for taps 4-7 */
        //TrRawWrite(0x0200 | (idx << 1)/*0, 4, idx*/);
        /*- Clear FFE except for taps 4-7 */
        (void) tr_raw_write(vtss_state, tsk->port, (0x0200 | (idx << 1))/*0, 4, idx*/, trRawData);
        VTSS_N("FFEinit4_7_65nm: port: %d, idx: 0x%x, value: 0x%x", tsk->port, (0x200 | (idx << 1)), trRawData);
        if (idx == 3) {
            idx = 7;
        }
    }
#ifdef _DEBUG_PHY_API_
    for (idx = 4; idx < 8; ++idx) {      /* Read taps 4-7 */
        (void) tr_raw_read(vtss_state, tsk->port, (0x0200 | (idx << 1))/*0, 4, idx*/, &trRawData);
        VTSS_N("FFEinit4_7_65nm: Reading: port: %d, idx: %d, idx1: 0x%x, value: 0x%x",
               tsk->port, idx, (0x200 | (idx << 1)), trRawData);
    }
#endif

    for (idx = 0; idx < 4; ++idx) {
        val = FFEinit4_7search_basis[idx] * tapScaleFactor;
        trRawData = 0;
        trRawData |= (val << 1) << 8;
        trRawData |= (val >> 7) << 16;
        //TrRawWrite(0x0200 | ((4+idx) << 1)/*0, 4, 4+idx*/);
        (void) tr_raw_write(vtss_state, tsk->port, 0x0200 | ((4 + idx) << 1) /*0, 4, 4+idx*/, trRawData); /*-  */
        VTSS_D("FFEinit4_7_65nm: Writing: port: %d, idx: %d, idx1: 0x%x, val: x%x,  Writing trRawData: 0x%x",
               tsk->port, idx, (0x200 | ((4 + idx) << 1)), val, trRawData);
    }

    trRawData = 0;
    //TrRawWrite(0x0240/*0, 4, 0x20*/);      /* Clear FfeWriteAllSubchans */
    (void) tr_raw_write(vtss_state, tsk->port, 0x0240/*0, 4, x20*/, trRawData); /*- Set FfeWriteAllSubchans*/
}

/* ********************************************************* */
/*               Start VeriPHY - Setup Phase                 */
/* ********************************************************* */
vtss_rc vtss_phy_veriphy_task_start(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 mode)
{
    vtss_phy_port_state_t         *ps = &vtss_state->phy_state[port_no];
    vtss_veriphy_task_t c51_idata *tsk;
    vtss_phy_family_t             family;
    u16                           reg23;

    tsk = &ps->veriphy;
    memset (tsk, 0, sizeof(vtss_veriphy_task_t));
    family = port_family(vtss_state, port_no);

        if (family == VTSS_PHY_FAMILY_MUSTANG ||
            family == VTSS_PHY_FAMILY_COBRA   ||
            family == VTSS_PHY_FAMILY_QUATTRO ||
            family == VTSS_PHY_FAMILY_LUTON   ||
            family == VTSS_PHY_FAMILY_LUTON_E ||
            family == VTSS_PHY_FAMILY_LUTON24 ||
            family == VTSS_PHY_FAMILY_COOPER  ||
            family == VTSS_PHY_FAMILY_SPYDER  ||
            family == VTSS_PHY_FAMILY_ENZO    ||
            family == VTSS_PHY_FAMILY_NANO    ||
            VTSS_PHY_GEN_2_DSP(port_no) ) {

            tsk->task_state = (u8) ((vtss_veriphy_task_state_t) VERIPHY_STATE_INIT_0);
            tsk->port = port_no;
            tsk->flags = mode << 6;
            VTSS_D("PHY_API: VeriPHY algorithm initialized, Port=%d, State=%d", tsk->port, tsk->task_state);
            //**printf("PHY_API: VeriPHY algorithm in PHY API initialized, Port=%d, State=%d\n", tsk->port, tsk->task_state);
            //fprintf(fp,"VeriPHY algorithm in PHY API initialized, Port=%d, State=%d\n", tsk->port, tsk->task_state);
            MEPA_MTIMER_START(&tsk->timeout, 1); /*- start now */

            /* Save Reg23 - to be restored after VeriPHY completes */
            /* select copper */
            VTSS_RC(vtss_phy_rd(vtss_state, tsk->port, 23, &reg23));
            ps->SaveMediaSelect = (reg23 >> 6) & 3;
            reg23 = (reg23 & 0xff3f) | 0x0080;
            VTSS_RC(vtss_phy_wr(vtss_state, tsk->port, 23, reg23));
        } else if (family == VTSS_PHY_FAMILY_LUTON26 ||
                   family == VTSS_PHY_FAMILY_ATOM ||
                   family == VTSS_PHY_FAMILY_TESLA ||
                   family == VTSS_PHY_FAMILY_ELISE ||
                   family == VTSS_PHY_FAMILY_VIPER) {

            VTSS_D("Embedded VeriPHY algorithm initialized, Port=%d, State=%d", tsk->port, tsk->task_state);
            //**printf("Embedded VeriPHY algorithm initialized, Port=%d, State=%d\n", tsk->port, tsk->task_state);
            //Bugzilla#6769 - Ports get stuck if running Verify at port that is disabled.
            if (ps->setup.mode != VTSS_PHY_MODE_POWER_DOWN) {
                tsk->task_state = (u8) ((vtss_veriphy_task_state_t) VERIPHY_STATE_INIT_0);
                tsk->port = port_no;

                //signal to API the veriphy is running for this port
                VTSS_RC(vtss_phy_veriphy_running(vtss_state, tsk->port, TRUE, TRUE));

                // Micro patch must be suspended while veriphy is running.
                VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, TRUE));

                // Starting Veriphy
                VTSS_I("Starting VeriPhY, port_no = %d", port_no);
                VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_VERIPHY_CTRL_REG1, VTSS_F_PHY_VERIPHY_CTRL_REG1_TRIGGER));
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            }
            MEPA_MTIMER_START(&tsk->timeout, 60000); /*- Run for max 60 sec. */
        }

    return VTSS_RC_OK;
}

/* ***************************************************************************************** */
/*               RUN VeriPHY - Iterative running Phase                                       */
/*                                                                                           */
/* Note: For the Embedded 8051 version, registers are checked to determine when VeriPHY      */
/*       has completed and to obtain the results                                             */
/*       For the API version, VeriPHY iterates thru the VeriPHY state machine with each      */
/*       call to vtss_phy_veriphy_get() until it has completed and obtains the results       */
/*                                                                                           */
/* \brief Run 1 Iteration of the VeriPHY process.                                            */
/*                                                                                           */
/* \param vtss_state [IN]      Target State instance reference.                              */
/* \param tsk        [IN/OUT]  VeriPHY Iterative info & result.                              */
/*                                                                                           */
/* \return Return code.                                                                      */
/* ***************************************************************************************** */
vtss_rc vtss_phy_veriphy(vtss_state_t *vtss_state, vtss_veriphy_task_t c51_idata *tsk)
{
    u8                      idx = 0;
    u32                     tr_raw_data = 0;
    vtss_phy_family_t       family;
    u16                     reg_val = 0;
    vtss_phy_port_state_t  *ps = &vtss_state->phy_state[tsk->port];
    BOOL AlwaysCheckEC;

    family = port_family(vtss_state, tsk->port);
    //fprintf(fp, " *********************************************\n");
    //fprintf(fp, "---> Initial Entry VeriPHY state of port %d is: 0x%02x\n", tsk->port, tsk->task_state);
    //fflush(fp);
    //fflush(cp);
    VTSS_N("--->>>> Initial Entry VeriPHY state of port %d is: 0x%02x <<<<<<<----", tsk->port, tsk->task_state);
    //**printf("--->>>> Initial Entry VeriPHY state of port %d is: 0x%02x <<<<<<<----\n", tsk->port, tsk->task_state);

    /* Veriphy is run Internally on embedded 8051 for the following platforms */
    if ((family == VTSS_PHY_FAMILY_ATOM ||
         family == VTSS_PHY_FAMILY_LUTON26 ||
         family == VTSS_PHY_FAMILY_TESLA ||
         family == VTSS_PHY_FAMILY_ELISE ||
         family == VTSS_PHY_FAMILY_VIPER) && !VTSS_PHY_GEN_2_DSP(tsk->port)) {
        // Most 65nm products have Veriphy running on internal 8051, except NANO
        VTSS_RC(vtss_phy_page_ext(vtss_state, tsk->port));
        VTSS_RC(PHY_RD_PAGE(vtss_state, tsk->port, VTSS_PHY_VERIPHY_CTRL_REG1, &reg_val));
        VTSS_N("VeriPhY Complete reg24E1:0x%X, port = %d", reg_val, tsk->port);
        //**printf("VeriPhY Complete reg24E1:0x%X, port = %d\n", reg_val, tsk->port);
        if (ps->setup.mode == VTSS_PHY_MODE_POWER_DOWN) {
            VTSS_I("Bugzilla#6769 - Ports get stuck if running Verify at port that is disabled.");
            tsk->loc[0] = 0;
            tsk->loc[1] = 0;
            tsk->loc[2] = 0;
            tsk->loc[3] = 0;
            tsk->stat[3] = VTSS_VERIPHY_STATUS_OPEN;
            tsk->stat[2] = VTSS_VERIPHY_STATUS_OPEN;
            tsk->stat[1] = VTSS_VERIPHY_STATUS_OPEN;
            tsk->stat[0] = VTSS_VERIPHY_STATUS_OPEN;
            tsk->flags = VERIPHY_FLAGS_VALID; // Signal Veriphy result valid
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            //printf("VeriPhY Done, port:%d\n", tsk->port);
            //fprintf(fp,"VeriPhY Done, port:%d\n", tsk->port);
            return VTSS_RC_OK; // Signal Veriphy Done

        } else if ((reg_val & VTSS_F_PHY_VERIPHY_CTRL_REG1_TRIGGER) == 0x0) {
            // Multiply by 3 because resolution is 3 meters // See datasheet
            VTSS_I("VeriPhY Complete reg24E1:0x%X, port = %d", reg_val, tsk->port);
            //**printf("VeriPhY Complete reg24E1:0x%X, port = %d \n", reg_val, tsk->port);
            tsk->loc[0] = ((reg_val & VTSS_M_PHY_VERIPHY_CTRL_REG1_PAIR_A_DISTANCE) >> 8) * 3;
            tsk->loc[1] = (reg_val & VTSS_M_PHY_VERIPHY_CTRL_REG1_PAIR_B_DISTANCE) * 3;

            VTSS_RC(PHY_RD_PAGE(vtss_state, tsk->port, VTSS_PHY_VERIPHY_CTRL_REG2, &reg_val));
            VTSS_I("VeriPhY Complete reg25E1:0x%X, port = %d", reg_val, tsk->port);
            //**printf("VeriPhY Complete reg25E1:0x%X, port = %d \n", reg_val, tsk->port);
            tsk->loc[2] = ((reg_val & VTSS_M_PHY_VERIPHY_CTRL_REG2_PAIR_C_DISTANCE) >> 8) * 3;
            tsk->loc[3] = (reg_val & VTSS_M_PHY_VERIPHY_CTRL_REG2_PAIR_D_DISTANCE) * 3;

            VTSS_RC(PHY_RD_PAGE(vtss_state, tsk->port, VTSS_PHY_VERIPHY_CTRL_REG3, &reg_val));
            VTSS_I("VeriPhY Complete reg26E1:0x%X, port = %d", reg_val, tsk->port);
            //**printf("VeriPhY Complete reg26E1:0x%X, port = %d \n", reg_val, tsk->port);
            tsk->stat[3] =  reg_val & VTSS_M_PHY_VERIPHY_CTRL_REG3_PAIR_D_TERMINATION_STATUS;
            tsk->stat[2] = (reg_val & VTSS_M_PHY_VERIPHY_CTRL_REG3_PAIR_C_TERMINATION_STATUS) >> 4;
            tsk->stat[1] = (reg_val & VTSS_M_PHY_VERIPHY_CTRL_REG3_PAIR_B_TERMINATION_STATUS) >> 8;
            tsk->stat[0] = (reg_val & VTSS_M_PHY_VERIPHY_CTRL_REG3_PAIR_A_TERMINATION_STATUS) >> 12;

            tsk->flags = VERIPHY_FLAGS_VALID; // Signal Veriphy result valid

            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));

            //signal to API the veriphy isn't running for this port
            VTSS_RC(vtss_phy_veriphy_running(vtss_state, tsk->port, TRUE, FALSE));

            // Ok veriphy done we can resume the micro patchning.
            VTSS_RC(vtss_atom_patch_suspend(vtss_state, tsk->port, FALSE));

            VTSS_I("VeriPhY Complete, port = %d, loc[0]: %d, loc[1]: %d, loc[2]: %d, loc[3]: %d",
                   tsk->port, tsk->loc[0], tsk->loc[1], tsk->loc[2], tsk->loc[3]);
            VTSS_I("VeriPhY Complete, port = %d, stat[0]: %d, stat[1]: %d, stat[2]: %d, stat[3]: %d",
                   tsk->port, tsk->stat[0], tsk->stat[1], tsk->stat[2], tsk->stat[3]);
            //**printf("VeriPhY Complete, port = %d, loc[0]: %d, loc[1]: %d, loc[2]: %d, loc[3]: %d\n", tsk->port, tsk->loc[0], tsk->loc[1], tsk->loc[2], tsk->loc[3]);
            //**printf("VeriPhY Complete, port = %d, stat[0]: %d, stat[1]: %d, stat[2]: %d, stat[3]: %d\n", tsk->port, tsk->stat[0], tsk->stat[1], tsk->stat[2], tsk->stat[3]);

            return VTSS_RC_OK; // Signal Veriphy Done

        } else if (MEPA_MTIMER_TIMEOUT(&tsk->timeout)) {
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            VTSS_I("VeriPhY Returning ERROR, port:%d", tsk->port);
            //printf("VeriPhY ERROR, port:%d\n", tsk->port);
            //fprintf(fp,"VeriPhY ERROR, port:%d\n", tsk->port);
            return VTSS_RC_ERROR;
        } else {
            VTSS_N("VeriPhY Running, port:%d, reg:0x%X", tsk->port, reg_val);
            //printf("VeriPhY Running, port:%d, reg:0x%X\n", tsk->port, reg_val);
            //fprintf(fp,"VeriPhY Running, port:%d, reg:0x%X\n", tsk->port, reg_val);
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            return VTSS_RC_INCOMPLETE; // Signaling that veriphy is still running
        }
    }


    /* Veriphy is run Externally via the API for the following platforms */
    if (!MEPA_MTIMER_TIMEOUT(&tsk->timeout)) {
        //printf("VeriPhY Timeout, port:%d \n", tsk->port);
        //fprintf(fp, " >>>>> VeriPhY Timeout, port:%d \n", tsk->port);
        VTSS_N(" >>>>> VeriPhY Timeout, port:%d ", tsk->port);
        return VTSS_RC_INCOMPLETE;
    }

    VTSS_D("---> ENTER VeriPHY state of port %d is: 0x%02x", tsk->port, tsk->task_state);
    VTSS_D("---> statA[%d], statB[%d], statC[%d], statD[%d] ", tsk->stat[0], tsk->stat[1], tsk->stat[2], tsk->stat[3]);
    //**printf("---> ENTER VeriPHY state of port %d is: 0x%02x \n", tsk->port, tsk->task_state);
    //**printf("---> statA[%d], statB[%d], statC[%d], statD[%d] \n", tsk->stat[0], tsk->stat[1], tsk->stat[2], tsk->stat[3]);
    //fprintf(fp,"---> ENTER VeriPHY state of port %d is: 0x%02x\n", tsk->port, tsk->task_state);
    //fprintf(fp,"---> statA[%d], statB[%d], statC[%d], statD[%d] ", tsk->stat[0], tsk->stat[1], tsk->stat[2], tsk->stat[3]);

    /*- Handle cleanup for VeriPHY task abort */
    if (tsk->task_state & VTSS_VERIPHY_STATE_DONEBIT) {
        if (tsk->task_state == VERIPHY_STATE_FINISH) {
            VTSS_D("Handle cleanup for VeriPHY task Finishing");
            //printf("Handle cleanup for VeriPHY task Finishing\n");
            //fprintf(fp,"Handle cleanup for VeriPHY task Finishing\n");
        } else {
            VTSS_D("Handle cleanup for VeriPHY task Done - Abort");
            //printf("Handle cleanup for VeriPHY task Done - Abort\n");
            //fprintf(fp,"Handle cleanup for VeriPHY task Done - Abort\n");
        }

        switch (tsk->task_state & ~VTSS_VERIPHY_STATE_DONEBIT) {

        case VERIPHY_STATE_IDLE : /*- Nothing to abort from Idle state */
            //printf("VeriPhY IDLE, port:%d\n", tsk->port);
            //fprintf(fp,"VeriPhY IDLE, port:%d\n", tsk->port);
            break;

        default :
            VTSS_N("VeriPhY DEFAULT, port:%d,  task_state: x%x", tsk->port, tsk->task_state);
            //printf("VeriPhY DEFAULT, port:%d,  task_state: x%x\n", tsk->port, tsk->task_state);
            //fprintf(fp,"VeriPhY DEFAULT, port:%d,  task_state: x%x\n", tsk->port, tsk->task_state);
            /*- Restore PHY to normal (non-VeriPHY) operation */

            /*- Restore blip-searches to default:  EcVarTrainingTime = 244, */
            /*-            EcVarTrainingGain = 1, EcVarShowtimeGain = 3    */

            VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
            /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
            if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b4/*0, 1, 1a*/, 0x1e8ed));
            } else {
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0190/*0, 3, 8*/, 0xf47));
            }

            if (family == VTSS_PHY_FAMILY_QUATTRO) {
                /*- Force H/W VeriPHY state machine to final state: VeriphyDisable = 1, */
                /*-   VeriPhyStateForce = 1, VeriPhyStateForceVal = 0x10, others default */
                VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0400/*0,  8, 0x00*/, 0x1dec00));
            }

            /*- If VeriPHY operated in link-down mode, ... */
            if ((tsk->flags & VERIPHY_FLAGS_LINKUP) == 0) {
                /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
                if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                    VTSS_RC(vtss_phy_1_gen_post_veriphy(vtss_state, family, tsk));
                } else {
                    /*- Clear EnableECvarDelayForce/Val */
                    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
                    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x0f86/*1, 15, 0x03*/, &tr_raw_data));
                    tr_raw_data &= ~0x300000;
                    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0f86/*1, 15, 0x03*/, tr_raw_data));
                }

                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    for (idx = 0; idx < 4; ++idx) {
                        if (tsk->loc[idx] == 0 && tsk->stat[idx] == 4) {
                            if (tsk->strength[idx] < 0) {
                                tsk->stat[idx] = 2;
                            } else {
                                tsk->stat[idx] = 1;
                            }
                        }
                    }
                }
            } else { /* link-up mode */
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    /* On link-up runs, change open/shorts to anomalous */
                    for (idx = 0; idx < 4; ++idx) {
                        if (tsk->stat[idx] >= 1 && tsk->stat[idx] <= 2) {
                            tsk->stat[idx] = 4;
                        }
                    }
                }
            }


            if (family == VTSS_PHY_FAMILY_LUTON24) {
                /*- Write-back VeriPHY results to Spyder registers and signal VeriPHY completion */
                ExtMiiWrite(vtss_state, tsk->port, 26, ((u16)tsk->stat[0] << 12) |
                            ((u16)(tsk->stat[1] & 0xf) << 8) |
                            ((u16)(tsk->stat[2] & 0xf) << 4) |
                            (u16)(tsk->stat[3] & 0xf) );
                ExtMiiWrite(vtss_state, tsk->port, 25, ((u16)(tsk->loc[2] & 0x3f) << 8) |
                            (u16)(tsk->loc[3] & 0x3f) |
                            ((u16)(tsk->flags & VERIPHY_FLAGS_LINKUP) << 15) );
                ExtMiiWrite(vtss_state, tsk->port, 24, ((u16)(tsk->loc[0] & 0x3f) << 8) |
                            (u16)(tsk->loc[1] & 0x3f) |
                            (u16)(tsk->flags & 0xc0) | 0x8000 );
            }

            if (family == VTSS_PHY_FAMILY_SPYDER ||
                family == VTSS_PHY_FAMILY_ENZO ||
                family == VTSS_PHY_FAMILY_LUTON ||
                family == VTSS_PHY_FAMILY_LUTON_E ||
                family == VTSS_PHY_FAMILY_LUTON24 ||
                family == VTSS_PHY_FAMILY_COOPER) {
                /*- Signal completion of VeriPHY operation for Luton/Spyder */
                TpWriteBit(vtss_state, tsk->port, 12, 0, 1);
            }

            /*- Link-up mode VeriPHY now completed, read valid bit! */
            if (tsk->flags & VERIPHY_FLAGS_LINKUP) {
                MEPA_MSLEEP(10);              /*- Wait for valid flag to complete */

                if ((family == VTSS_PHY_FAMILY_MUSTANG) ||
                    (family == VTSS_PHY_FAMILY_COBRA) ||
                    (family == VTSS_PHY_FAMILY_COOPER)) {
                    /*- Conditionally set valid bit */
                    tsk->flags |= (MiiReadBits(vtss_state, tsk->port, 17, 13, 13) ^ 1) << 1;
                } else if (family == VTSS_PHY_FAMILY_LUTON ||
                           family == VTSS_PHY_FAMILY_LUTON_E ||
                           family == VTSS_PHY_FAMILY_SPYDER ||
                           family == VTSS_PHY_FAMILY_ENZO) {
                    tsk->flags |= ExtMiiReadBits(vtss_state, tsk->port, 24, 14, 14) << 1; /*- Set valid bit */
                    //printf("VeriPhY Read 24, 14, 14 on port:%d,  Flags: 0x%x \n", tsk->port, tsk->flags);
                } else {
                    tsk->flags |= ExtMiiReadBits(vtss_state, tsk->port, 25, 14, 14) << 1; /*- Set valid bit */
                    //printf("VeriPhY Read 25, 14, 14 on port:%d,  Flags: 0x%x \n", tsk->port, tsk->flags);
                    //fprintf(fp,"VeriPhY Read 25, 14, 14 on port:%d,  Flags: 0x%x \n", tsk->port, tsk->flags);
                }
            } else { /*- Results always valid in link-down mode (avoids AMS problem) */
                tsk->flags |= VERIPHY_FLAGS_VALID;    /*- Set valid bit */
                //printf("VeriPhY Link-Down Setting VERIPHY_FLAGS_VALID for port:%d,  Flags: 0x%x \n", tsk->port, tsk->flags);
                //fprintf(fp,"VeriPhY Link-Down Setting VERIPHY_FLAGS_VALID for port:%d,  Flags: 0x%x \n", tsk->port, tsk->flags);
            }

            if (family == VTSS_PHY_FAMILY_LUTON24) {
                /*- Restore original ams_force_* (VeriPHY must force cu) */
                MiiWriteBits(vtss_state, tsk->port, 23, 7, 6, tsk->flags2 & 3);
            }

            if (family == VTSS_PHY_FAMILY_LUTON ||
                family == VTSS_PHY_FAMILY_LUTON_E) {
                /*- Restore original ActiPHY enable state */
                MiiWriteBits(vtss_state, tsk->port, 28, 6, 6, tsk->flags2 & 1);
            }

            if (family == VTSS_PHY_FAMILY_COOPER) {
                /*- Restore original ActiPHY enable state */
                MiiWriteBits(vtss_state, tsk->port, 23, 5, 5, tsk->flags2 & 1);
            }

            /*- Re-enable RClk125 gating */
            TpWriteBit(vtss_state, tsk->port, 8, 9, 0);

            /*- Switch page back to main page */
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
        }   /* switch (tsk->task_state & ~VTSS_VERIPHY_STATE_DONEBIT) */

        {
            u16 reg23;
            /* restore mediaselect */
            VTSS_RC(vtss_phy_rd(vtss_state, tsk->port, 23, &reg23));
            reg23 = (reg23 & 0xff3f) | (ps->SaveMediaSelect << 6);
            VTSS_RC(vtss_phy_wr(vtss_state, tsk->port, 23, reg23));
        }

        if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
            // Multiply by 3 because resolution is 3 meters // See datasheet
            VTSS_I("VeriPhY Complete, port = %d", tsk->port);
            //printf("VeriPhY Complete, Reg23= 0x%x,  port = %d \n", reg_val, tsk->port);
            //fprintf(fp,"VeriPhY Complete, Reg23= 0x%x,  port = %d \n", reg_val, tsk->port);

            tsk->loc[0] = tsk->loc[0] * 3;
            tsk->loc[1] = tsk->loc[1] * 3;
            tsk->loc[2] = tsk->loc[2] * 3;
            tsk->loc[3] = tsk->loc[3] * 3;

            tsk->flags = VERIPHY_FLAGS_VALID; // Signal Veriphy result valid
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
        }

        for (idx = 0; idx < 4; ++idx) {
            VTSS_D("Returning:  Location/Status/Strength - Index = %d, loc = %d, stat = %d, strength = %d", idx,
                   tsk->loc[idx], tsk->stat[idx], tsk->strength[idx]);
            //**printf("Returning:  Location/Status/Strength - Index = %d, loc = %d, stat = %d, strength = %d\n", idx, tsk->loc[idx], tsk->stat[idx], tsk->strength[idx]);
        }

        /*- Return to idle state */
        tsk->task_state = VERIPHY_STATE_IDLE;
        //printf("VeriPhY Returning IDLE State & OK Status, port:%d\n", tsk->port);
        //fprintf(fp,"VeriPhY Returning IDLE State & OK Status, port:%d\n", tsk->port);
        return VTSS_RC_OK;
    }  /*- if ABORT */

    switch (tsk->task_state) {
    case VERIPHY_STATE_HALT:
        VTSS_D("VERIPHY_STATE_HALT");
        //printf("VERIPHY_STATE_HALT\n");
        //fprintf(fp,"VERIPHY_STATE_HALT\n");
        break;
    /*- VeriPHY task is idle. Check for pending VeriPHY request */
    case VERIPHY_STATE_IDLE :
        VTSS_D("VERIPHY_STATE_IDLE");
        //printf("VERIPHY_STATE_IDLE\n");
        //fprintf(fp,"VERIPHY_STATE_IDLE\n");
        if (family == VTSS_PHY_FAMILY_LUTON24) {
            for (idx = 0; idx < 8; ++idx) {
                /*- Begin search with PHY after last PHY which ran VeriPHY (fairness) */
                tsk->port = (tsk->port + 1) & 7;
                VTSS_RC(vtss_phy_page_ext(vtss_state, tsk->port));
                tsk->thresh[0] = SmiRead(vtss_state, tsk->port, 24);
                if (tsk->thresh[0] & 0x8000) {
                    VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
                    tsk->flags = (unsigned char)(tsk->thresh[0] & 0xc0); /*- VeriPHY operating mode */
                    tsk->thresh[0] = SmiRead(vtss_state, tsk->port, 23);
                    tsk->flags2 = (tsk->thresh[0] >> 6) & 3; /*- Save state of ams_force_* */
                    tsk->thresh[0] = (tsk->thresh[0] & 0xff3f) | 0x0080; /*- ams_force_cu=1, ams_force_fi=0 */
                    VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
                    VTSS_RC(SmiWrite(vtss_state, tsk->port, 23, tsk->thresh[0]));

                    tsk->task_state = VERIPHY_STATE_INIT_0;
                    break;
                }
            }
        }
        break;

    /*- Configure for VeriPHY operation, and if successful, run VeriPHY algo. */
    case VERIPHY_STATE_INIT_0 :
        VTSS_D("VERIPHY_STATE_INIT_0");
        //printf("VERIPHY_STATE_INIT_0\n");
        //fprintf(fp,"VERIPHY_STATE_INIT_0\n");
        /*- Initialize globals for VeriPHY search */
        /* if (family == VTSS_PHY_FAMILY_MUSTANG) { */
        if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
            tsk->numCoeffs = 12;
        } else {
            if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                tsk->numCoeffs = 7;
            } else {
                tsk->numCoeffs = 8;
            }
        }

        for (idx = 0; idx < 4; ++idx) {
            tsk->stat[idx]     = 0;
            tsk->loc[idx]      = 0;
            tsk->strength[idx] = 0;
        }

        VTSS_D("VeriPHY init - Disable RCLK125 Gating - TpWriteBit(%d, 8, 9, 1), NumCoeffs: %d", tsk->port, tsk->numCoeffs);
        //printf("VeriPHY init - Disable RCLK125 Gating -TpWriteBit(%d, 8, 9, 1),   NumCoeffs: %d\n", tsk->port, tsk->numCoeffs);
        //fprintf(fp,"VeriPHY init - Disable RCLK125 Gating - TpWriteBit(%d, 8, 9, 1),   NumCoeffs: %d\n", tsk->port, tsk->numCoeffs);
        TpWriteBit(vtss_state, tsk->port, 8, 9, 1);   /*- Disable RClk125 gating */

        /* Initialize the PHY Veriphy Coeff structs */
        vtss_state->phy_inst_state.maxAbsCoeff = 0;
        for (idx = 0; idx < VTSS_PHY_INST_STATE_MAX_COEFF; ++idx) {
            vtss_state->phy_inst_state.coeff[idx] = 0;
        }

        if (family == VTSS_PHY_FAMILY_QUATTRO) {
            /*- Hold H/W VeriPHY state machine in the IDLE state: VeriphyDisable = 1, */
            /*-      VeriPhyStateForce = 1, VeriPhyStateForceVal = 0, others default */
            VTSS_D("VeriPHY init - TrRawWrite(%d, 0, 8, 0x00, 0x1de800)", tsk->port);
            VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
            VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0400/*0,  8, 0x00*/, 0x1de800));
        }

        /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
        if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
            /*- Prepare to use VeriPHY on Mustang which has no internal VeriPHY trigger logic */
            /*- Starting VeriPHY requires determining whether 1000-Base-T link is up or not */
            tsk->flags |= MiiReadBits(vtss_state, tsk->port, 17, 12, 12);
            if (tsk->flags & VERIPHY_FLAGS_LINKUP) { /*- 1000-Base-T link is up */
                /*- maybe more to do later */;
            } else { /*- 1000-Base-T link is down */
                VTSS_RC(vtss_phy_1_gen_pre_veriphy(vtss_state, family, tsk));
            }
        } else {
            VTSS_D("VeriPHY init - Triggering Veriphy - ExtMiiWrite(%d, 24, 0x8000)", tsk->port);
            //printf ("VeriPHY init - Triggering Veriphy - ExtMiiWrite(%d, 24, 0x8000) \n", tsk->port);
            //fprintf (fp,"VeriPHY init - Triggering Veriphy - ExtMiiWrite(%d, 24, 0x8000) \n", tsk->port);

#ifdef USE_8051_RESET
            if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                u16 regVal = 0;
                SmiWrite(vtss_state, tsk->port, 31, VTSS_PHY_PAGE_GPIO);  /* Setup to Read/Write the GPIO Pages */
                regVal = SmiRead(vtss_state, tsk->port, 0);               /* Read Micro-Page */
                regVal &= 0x7fff;                                         /* Clear Bit 15 to Reset the 8051 */
                GpioMiiWrite(vtss_state, tsk->port, 0, regVal);           /*- Reset the on-board 8051 */
                VTSS_D("VeriPHY init - Resetting 8051 on port: %d ", tsk->port);
                //**printf ("VeriPHY init - Resetting 8051 on port: %d\n", tsk->port);
                //fprintf (fp,"VeriPHY init - Resetting 8051 on port: %d \n", tsk->port);
            }
#endif
            ExtMiiWrite(vtss_state, tsk->port, 24, 0x8000);           /*- Trigger VeriPHY */
        }

        if (family == VTSS_PHY_FAMILY_LUTON24) {
            /*- Save state of ams_force_* and set ams_force_cu=1, ams_force_fi=0 */
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            tsk->thresh[0] = SmiRead(vtss_state, tsk->port, 23);
            tsk->flags2 = (tsk->thresh[0] >> 6) & 3;
            tsk->thresh[0] = (tsk->thresh[0] & 0xff3f) | 0x0080;
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            VTSS_RC(SmiWrite(vtss_state, tsk->port, 23, tsk->thresh[0]));
        }

        if (family == VTSS_PHY_FAMILY_LUTON ||
            family == VTSS_PHY_FAMILY_LUTON_E) {
            /*- Save state of ActiPHY enable state and disable ActiPHY */
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            tsk->thresh[0] = SmiRead(vtss_state, tsk->port, 28);
            tsk->flags2 = (tsk->thresh[0] >> 6) & 1;
            tsk->thresh[0] = tsk->thresh[0] & 0xffbf;
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            VTSS_RC(SmiWrite(vtss_state, tsk->port, 28, tsk->thresh[0]));
        }

        /* Check how it changes the value of Reg23 before and after */
        if (family == VTSS_PHY_FAMILY_COOPER) {
            /*- Save state of ActiPHY enable state and disable ActiPHY */
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            tsk->thresh[0] = SmiRead(vtss_state, tsk->port, 23);
            tsk->flags2 = (tsk->thresh[0] >> 5) & 1;
            tsk->thresh[0] = tsk->thresh[0] & 0xffdf;
            VTSS_RC(vtss_phy_page_std(vtss_state, tsk->port));
            VTSS_RC(SmiWrite(vtss_state, tsk->port, 23, tsk->thresh[0]));
        }

        /* if (family != VTSS_PHY_FAMILY_MUSTANG) { */
        /* Delay for 750ms to allow link to transition (ANEG to complete) */
        if (!VTSS_PHY_1_GEN_DSP(tsk->port)) {
            /*- T(TR_MOD_PORT,TR_LVL_CRIT,"VeriPHY delay 750ms"); */
            /*- Wait for 750 ms for locRcvrStatus fall to propagate to link-down */
            MEPA_MTIMER_START(&tsk->timeout, 750); /*- 150 ticks or x 5 ms/tick = 750 ms delay */
        }

        VTSS_D("VERIPHY_STATE_INIT_0: flags:0x%x, flags2: 0x%x, thresh[0]: %d, thresh[1]: %d, numCoeffs: %d",
               tsk->flags, tsk->flags2, tsk->thresh[0], tsk->thresh[1], tsk->numCoeffs);
        //**printf("VERIPHY_STATE_INIT_0: flags:0x%x, flags2: 0x%x, thresh[0]: %d, thresh[1]: %d, numCoeffs: %d\n", tsk->flags, tsk->flags2, tsk->thresh[0], tsk->thresh[1], tsk->numCoeffs);


        tsk->task_state = VERIPHY_STATE_INIT_1;
        break;

    /*- Continue configuration for VeriPHY operation (after 750 ms delay) */
    case VERIPHY_STATE_INIT_1 :
        VTSS_D("VERIPHY_STATE_INIT_1");
        //printf("VERIPHY_STATE_INIT_1\n");
        //fprintf(fp,"VERIPHY_STATE_INIT_1\n");
        /* if (family != VTSS_PHY_FAMILY_MUSTANG) { */
        if (!VTSS_PHY_1_GEN_DSP(tsk->port)) {
            /* Get Gigbit Link status */
            tsk->flags |= MiiReadBits(vtss_state, tsk->port, 17, 12, 12);
            VTSS_D("VeriPHY init - 1000BaseT Link Status: flags: 0x%x, vphy_linkup = %d", tsk->flags, tsk->flags & VERIPHY_FLAGS_LINKUP);
            //printf("VeriPHY init - 10000BaseT Link Status: flags: 0x%x,  vphy_linkup = %d \n", tsk->flags, tsk->flags & VERIPHY_FLAGS_LINKUP);
            //fprintf(fp,"VeriPHY init - 1000BaseT Link Status: flags: 0x%x,  vphy_linkup = %d \n", tsk->flags, tsk->flags & VERIPHY_FLAGS_LINKUP);
            if (ExtMiiReadBits(vtss_state, tsk->port, 24, 15, 15) == 0) {
                /*- Link was up, but has gone down after trigger */
                VTSS_D("VeriPHY Init failed: Link DOWN since Veriphy Trigger, (ABORT) ExtMiiReadBits(tsk->port, 24, 15, 15) == 0");
                //printf("VeriPHY Init failed: (ABORT) ExtMiiReadBits(tsk->port, 24, 15, 15) == 0\n");
                //fprintf(fp,"VeriPHY Init failed: Link DN since Veriphy Trigger, (ABORT) ExtMiiReadBits(tsk->port, 24, 15, 15) == 0\n");
                tsk->task_state |= VERIPHY_STATE_ABORT; /*- Abort VeriPHY task */
                break;
            }
        }

        if (tsk->flags & VERIPHY_FLAGS_LINKUP) {
            i8  vgaGain;
            int temp;

            /*- Speed up blip-searches:  EcVarTrainingTime = 56 (32 for VSC8201), */
            /*  However the trade-off is that the algorythm is less accurate when faster */
            /*-   EcVarTrainingGain = 1, EcVarShowtimeGain = 3 */
            VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
            /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
            if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b4/*0, 1, 1a*/, 0x40ed));
                //fprintf(fp,"Setting up GEN1 Blip Cancellor Training time: 0x40ed \n");
            } else {
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0190/*0, 3, 8*/, 0x0387));
                //fprintf(fp,"Setting up 65nm Blip Cancellor Training time: 0x0387 \n");
            }

            /*- Read VGA state for all four subchannels, extract VGA gain for A */
            /*- VgaGain is 5 bits and 2's compliment */
            VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x0ff0/*1, 15, 0x38*/, &tr_raw_data));
            VTSS_D("VeriPHY Raw VGA Gain, tr_raw_data: 0x%x ", tr_raw_data);

            if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                /*- Field of interest is bits 8:4, so discard 0:3 */
                vgaGain = (i8)((tr_raw_data & 0xff) >> 4);
                //fprintf(fp,"VGA Gain: %d \n", vgaGain);

                /*- Getting bit 8 and extracting the sign bit */
                if (tr_raw_data & 0x100) {
                    vgaGain -= 16;
                    //fprintf(fp,"Dropping VGA Gain: %d \n", vgaGain);
                }
                temp = 32;
            } else {
                vgaGain = (i8)(tr_raw_data >> 4) & 0x0f;

                if (tr_raw_data & 0x100) {
                    vgaGain -= 16;
                }
                temp = 26;
            }

            /*- The 900 is from emperical determination */
            tsk->log2VGAx256 = 900 + (temp * (int)vgaGain);

            tsk->task_state = VERIPHY_STATE_INIT_ANOMSEARCH_0;
            VTSS_D("VeriPHY link-up setting state = VERIPHY_STATE_INIT_ANOMSEARCH_0, tsk->log2VGAx256= %d ", tsk->log2VGAx256);
            //fprintf(fp,"VeriPHY link-up setting state = VERIPHY_STATE_INIT_ANOMSEARCH_0, vgaGain: %d, tsk->log2VGAx256= %d \n", vgaGain, tsk->log2VGAx256);
            VTSS_D("VERIPHY_STATE_INIT_1: flags:0x%x, flags2: 0x%x, thresh[0]: %d, thresh[1]: %d, numCoeffs: %d", tsk->flags, tsk->flags2, tsk->thresh[0], tsk->thresh[1], tsk->numCoeffs);
        } else {
            tsk->thresh[0]   = 400;                /*- N: Setup timeout after N*5 ms of LinkControl1000 asserted */
            MEPA_MTIMER_START(&tsk->timeout, 10);  /*- Sleep for 2 Ticks or 10ms before polling MrSpeedStatus the first time */

            tsk->task_state  = VERIPHY_STATE_INIT3_LINKDOWN;
            VTSS_D("VeriPHY link-dn setting state = VERIPHY_STATE_INIT3_LINKDOWN ");
            //printf("VeriPHY link-dn setting state = VERIPHY_STATE_INIT3_LINKDOWN \n");
            //fprintf(fp,"VeriPHY link-dn setting state = VERIPHY_STATE_INIT3_LINKDOWN \n");
        }
        break;

    /*- Continue configuration for link-down VeriPHY */
    case VERIPHY_STATE_INIT3_LINKDOWN :
        VTSS_D("VERIPHY_STATE_INIT3_LINKDOWN");
        //printf("VERIPHY_STATE_INIT3_LINKDOWN\n");
        //fprintf(fp,"VERIPHY_STATE_INIT3_LINKDOWN\n");
        /*- Wait for MrSpeedStatus[1:0] to become 2 (LinkControl1000 asserted) */
        /*- Bit defn: 00 = 10Mbit, 01=100Mbit, 10=1Gigbit, 11=unused */
        if (MiiReadBits(vtss_state, tsk->port, 28, 4, 3) == 2) {
            /*- Initialize FFE for link-down operation */
            VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));  /* Setup to Write to Token Ring Pages */
            if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                FFEinit4_7_65nm(vtss_state, tsk, FFEinit4_7anomSearch_65nm);
            } else {
                FFEinit4_7(vtss_state, tsk, FFEinit4_7anomSearch);
            }

            /*- Speed up blip-searches:  EcVarTrainingTime = 56 (32 for VSC8201), */
            /*-   EcVarTrainingGain = 0, EcVarShowtimeGain = 0 */
            /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
            if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b4/*0, 1, 1a*/, 0x400d));
            } else {
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0190/*0, 3, 8*/, 0x3c2));
                } else {
                    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0190/*0, 3, 8*/, 0x381));
                }
            }
            VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x0f86/*1, 15, 0x03*/, &tr_raw_data));    /*- Set EnableECvarDelayForce/Val */
            tr_raw_data |= 0x300000;
            VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0f86/*1, 15, 0x03*/, tr_raw_data));
            tsk->log2VGAx256 = 0;

            VTSS_D("VeriPHY link-down anomalySearch");
            if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                tsk->task_state  = VERIPHY_STATE_INIT4_LINKDOWN;
                MEPA_MTIMER_START(&tsk->timeout, 20); /*- Sleep for (ECretrain_time=4 ticks or 20ms before polling MrSpeedStatus again */
            } else {
                tsk->task_state = VERIPHY_STATE_INIT_ANOMSEARCH_0;
            }
        } else if (--(tsk->thresh[0]) > 0) { /* Threshold is being used as a timer/counter for timeout */
            MEPA_MTIMER_START(&tsk->timeout, 5); /*- Sleep for 5ms before polling MrSpeedStatus again */
        } else { /*- timed out waiting for MrSpeedStatus to indicate LinkControl1000 asserted! */
            //tsk->task_state |= 0x80; /*- Abort VeriPHY task */
            tsk->task_state |= VERIPHY_STATE_ABORT; /*- Abort VeriPHY task */
            VTSS_D("VeriPHY %d: VERIPHY_STATE_INIT3_LINKDOWN ** ABORT!", tsk->port);
        }
        break;

    case VERIPHY_STATE_INIT4_LINKDOWN:
        /* ***** Note: This state is only executed for 65nm Products..ie NANO. Not executed for 130nm ****** */
        VTSS_D("VERIPHY_STATE_INIT4_LINKDOWN, tsk->log2VGAx256= %d", tsk->log2VGAx256);
        //fprintf(fp,"VERIPHY_STATE_INIT4_LINKDOWN, tsk->log2VGAx256= %d\n", tsk->log2VGAx256);
        // Get MSE for pairs A&B
        VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
        VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x03c0 /*0, 7, 32 */, &tr_raw_data));    /*- Set EnableECvarDelayForce/Val */

        //printf("VERIPHY_STATE_INIT4_LINKDOWN,(0x03c0):   0x%x\n", tr_raw_data);
        // If MSE A & B worse than -42.1dB (which is what we desire since,
        // if things are too quiet, we will not train xc properly) - Crude Auto Gain Control for link down mode
        // if (TrRawData[2] != 0 && ((TrRawData[1] & 0x0f) != 0 || TrRawData[0] >= 16))
        //    TrRawRead(0x03c2/*0, 7, 33*/); // Get MSE for pairs C&D, since A&B are OK
        if (((tr_raw_data & 0xff0000) != 0) && (((((tr_raw_data & 0xff00) >> 8) & 0x0f) != 0) || (tr_raw_data >= 16))) {
            VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x03c2 /*0, 7, 33 */, &tr_raw_data));  // Get MSE for pairs C&D, since A&B are OK
            //printf("VERIPHY_STATE_INIT4_LINKDOWN,(0x03c2):   0x%x\n", tr_raw_data);
        }
        // Retest A&B if they are too quiet, or test C&D if A&B were OK
        // if ((TrRawData[2] == 0 || ((TrRawData[1] & 0x0f) == 0 && TrRawData[0] < 16)) && tsk->log2VGAx256 < 512)
        //printf("VERIPHY_STATE_INIT4_LINKDOWN, tr_raw_data:  0x%x,   log2VGAx256: 0x%x\n", tr_raw_data, tsk->log2VGAx256);
        //fprintf(fp,"VERIPHY_STATE_INIT4_LINKDOWN, tr_raw_data:  0x%x,   log2VGAx256: 0x%x\n", tr_raw_data, tsk->log2VGAx256);

        if ((((tr_raw_data & 0xff0000) == 0) ||
             (((((tr_raw_data & 0xff00) >> 8) & 0x0f) == 0) && ((tr_raw_data & 0xff) < 16))) && (tsk->log2VGAx256 < 512)) {
            // Boost FFE up and compensate w/log2VGAx256 so thresholds don't change!
            tsk->log2VGAx256 += 256;
            VTSS_D("VERIPHY_STATE_INIT4_LINKDOWN, Boosting  log2VGAx256: %d", tsk->log2VGAx256);
            FFEinit4_7_65nm(vtss_state, tsk, (FFEinit4_7anomSearch_65nm << (tsk->log2VGAx256 >> 8)) );
            MEPA_MTIMER_START(&tsk->timeout, 20); /*- Sleep for (ECretrain_time=4 ticks or 20ms before polling MrSpeedStatus again */
            break;
        }
        /* fall-through */
    case VERIPHY_STATE_INIT_ANOMSEARCH_0:
        VTSS_D("VERIPHY_STATE_INIT_ANOMSEARCH_0: chan: %d,    nc: %d,   flags: 0x%x", tsk->subchan, tsk->nc, tsk->flags);
        //fprintf(fp,"VERIPHY_STATE_INIT_ANOMSEARCH_0: chan: %d,    nc: %d,   flags: 0x%x\n", tsk->subchan, tsk->nc, tsk->flags);

        if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
            if (tsk->flags & 0x80) {      /* Veriphy Operating Mode: VERIPHY_MODE_ANOM_ONLY - Anomoly Search Only */
                if (tsk->flags & 0x40) {  /* Veriphy Operating Mode: VERIPHY_MODE_ANOM_XPAIR - Anomoly Search w/o X-Pair Flag */
                    // Skip body of VeriPHY operation in test mode!
                    tsk->stat[0] = 3; // False status for test - Undefined or UNHANDLED
                    tsk->stat[1] = 5; // False status for test - Undefined or UNHANDLED
                    tsk->stat[2] = 6; // False status for test - Undefined or UNHANDLED
                    tsk->stat[3] = 7; // False status for test - Undefined or UNHANDLED
                    tsk->loc[0] = 0x30; // False loc for test - 48
                    tsk->loc[1] = 0x60; // False loc for test - 96
                    tsk->loc[2] = 0x90; // False loc for test - 144
                    tsk->loc[3] = 0xc0; // False loc for test - 196
                    tsk->task_state = VERIPHY_STATE_PAIRSWAP;
                    //printf("Anomoly Search Only, state moved to VERIPHY_STATE_PAIRSWAP\n");
                    break;
                } else {
                    tsk->nc = 0; // Skip the Nxt Cancellor, only do Echo Cancellor
                    //printf("VERIPHY_STATE_INIT_ANOMSEARCH_0: Anomoly Search w/o x-pair only, Setting nc = %d\n", tsk->nc);
                }
            } else {
                tsk->nc = 3;
                //printf("VERIPHY_STATE_INIT_ANOMSEARCH_0: Setting nc = %d\n", tsk->nc);
            }
            tsk->thresh[2] = 0; // Clear EC invalid count accumulator
        } else {
            tsk->nc = (tsk->flags & 0x80) ? 0 : 3;   /* VERIPHY_MODE_ANOM_ONLY */
            tsk->thresh[2] = 0; /*- Clear EC invalid count accumulator */
            if (tsk->flags & 0x80) {
                VTSS_D("VERIPHY_STATE_INIT_ANOMSEARCH_0: VERIPHY_MODE_ANOM_ONLY - Setting nc = %d", tsk->nc);
            }
        }
        /* fall-through */
    // Fall through to the InitAnomSearch_1 state!

    case VERIPHY_STATE_INIT_ANOMSEARCH_1 :
        VTSS_D("VERIPHY_STATE_INIT_ANOMSEARCH_1: chan: %d,  nc: %d,  flags: 0x%x", tsk->subchan, tsk->nc, tsk->flags);
        //fprintf(fp,"VERIPHY_STATE_INIT_ANOMSEARCH_1: chan: %d,    nc: %d,   flags: 0x%x\n", tsk->subchan, tsk->nc, tsk->flags);
        tsk->thresh[1] = 0; /*- Clear EC invalid count (previous value) */
        tsk->thresh[0] = 0; /*- Clear EC invalid count (current value) */
        /* fall-through */
    /*- fall through into VERIPHY_STATE_ANOMSEARCH_0 state */

    /*- Search for anomalous pair-coupling, pair-shorts, anomalous termination */
    /*- impedance, open-circuits, or short-circuits on all four twisted-pairs. */
    /*- Hardware is searching for anomolies by starting at the end and then looks backwards */
    /*- If the Hardware finds an anomoly, it remembers the location and then repeats */
    /*- This sets up the Hardware for the search */
    case VERIPHY_STATE_ANOMSEARCH_0 :
        VTSS_D("VERIPHY_STATE_ANOMSEARCH_0: chan: %d,  nc: %d,  flags: 0x%x, tsk->thresh[0]: %d",
               tsk->subchan, tsk->nc, tsk->flags, tsk->thresh[0]);
        //fprintf(fp,"VERIPHY_STATE_ANOMSEARCH_0: chan: %d,    nc: %d,   flags: 0x%x, tsk->thresh[0]: %d\n", tsk->subchan, tsk->nc, tsk->flags, tsk->thresh[0]);
        /*- EC invalid count prev = current */
        tsk->thresh[1] = tsk->thresh[0];

        /* if (family == VTSS_PHY_FAMILY_MUSTANG) { */
        if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
            /*- EcVar does not have an input-select on Mustang, but still need */
            /*- to record that there is no forced-delay (bit 1)                */
            tsk->tr_raw0188 = 0;
            /*- allow EC blip time to train to anomaly location */
            if (tsk->nc == 0) {
                MEPA_MTIMER_START(&tsk->timeout, 500);
            }
        } else {
            VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
            VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0x01)); /*- EcVarForceIdle = 1 */

            /* Select Input to BC's from end of NC's */
            /*- EcVar[A-D]InputSel = nc */
            //    tsk->tr_raw0188 = 0; /* bits 0-7 = 0 */
            //    tsk->tr_raw0188 |= ((tsk->nc << 7) | (tsk->nc << 5)) << 8;  /* bits 8-15  */
            //    tsk->tr_raw0188 |= ((tsk->nc << 3) | (tsk->nc << 1) | (tsk->nc >> 1)) << 16;  /* bits 16-23  */
            // The code line, nc * 0x0aa000, provides the same result as the above bit-shifting 8051 code
            tsk->tr_raw0188 = (long)tsk->nc * 0x0aa000;

            VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, tsk->tr_raw0188));
            VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0)); /*- EcVarForceIdle = 0 */
            //printf("VERIPHY_STATE_ANOMSEARCH_0: writing to TR_Addr 0x0188 value of: 0x%x ", tsk->tr_raw0188);
            //fprintf(fp,"VERIPHY_STATE_ANOMSEARCH_0: writing to TR_Addr 0x0188 value of: 0x%x ", tsk->tr_raw0188);

            /*- This allowing the Hardware State machine to settle -*/
            /* If we don't find an anomoly within 500ms, then give up, because the anomoly doesn't exist */
            /*- allow blip time to train to anomaly location */
            MEPA_MTIMER_START(&tsk->timeout, 500);/*- Sleep for 100 ticks or 500ms before polling MrSpeedStatus again */
        }
        tsk->task_state = VERIPHY_STATE_ANOMSEARCH_1;
        break;

    /*- Validate at start of anomaly search that all subchannels are active */
    /*- Get the results from the Hardware Anomoly Search - This gets the data from the Hardware search */
    case VERIPHY_STATE_ANOMSEARCH_1 :
        VTSS_D("VERIPHY_STATE_ANOMSEARCH_1: chan: %d,  nc: %d, thresh[0]: %d", tsk->subchan, tsk->nc, tsk->thresh[0]);
        //fprintf(fp, "VERIPHY_STATE_ANOMSEARCH_1: chan: %d,    nc: %d,  thresh[0]: %d\n", tsk->subchan, tsk->nc, tsk->thresh[0]);
        VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
        /* if (family == VTSS_PHY_FAMILY_MUSTANG) { */
        if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
            VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x0ba/*0, 1, 0x1d*/, &tr_raw_data));
            if (((tr_raw_data & 0xff0080) == 0xf00080)) {
                /*- EC invalid count current = prev count + 1 */
                tsk->thresh[0] = tsk->thresh[1] + 1;

                VTSS_D("VeriPHY %d%c: %s, blip is ZERO at all delays!", tsk->port, idx + 'A', (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"));
                //printf("VeriPHY %d%c: %s, blip is ZERO at all delays! \n", tsk->port, idx + 'A', (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"));
                //fprintf(fp,"VeriPHY %d%c: %s, blip is ZERO at all delays! \n", tsk->port, idx + 'A', (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"));
                /*- Clear any anomaly found under this errant condition */
                /*- idx is the subchannel which represents each twisted pair */
                for (idx = 0; idx < 4; ++idx) {
                    tsk->stat[idx]      = 0;
                    tsk->loc[idx]       = 0;
                    tsk->strength[idx]  = 0;
                }
            }
        } else {
            /* Start of Searching All Pairs for EC Invalid condition */
            /*- idx is the subchannel which represents each twisted pair */
            /* Read EC State */
            for (idx = 0; idx < 4; ++idx) {
                /* The search settled on a NULL Result, which is bogus, ecInvalid  */
                VTSS_RC(tr_raw_read(vtss_state, tsk->port, (idx << 11) | 0x01c0/*idx, 3, 0x20*/, &tr_raw_data));
                /* Settled to location 0xf0, which is bogus, 0x80 is the done state, so it has settled and done */
                if (((tr_raw_data & 0xff0080) == 0xf00080)) {    // same as: if ((TrRawData[2] == 0xf0) && (TrRawData[0] & 128))
                    //fprintf(fp,"idx: %d, tr_raw_data: 0x%x  - Clearing Anomoly\n", idx, tr_raw_data);
                    /*- EC invalid count current = prev count + 1 */
                    tsk->thresh[0] = tsk->thresh[1] + 1;  /* Increment the failure count */

                    VTSS_D("VeriPHY %d%c: %s, blip is ZERO at all delays!", tsk->port, idx + 'A', (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"));
                    //printf("VeriPHY %d%c: %s, blip is ZERO at all delays! \n", tsk->port, idx + 'A', (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"));
                    //fprintf(fp,"VeriPHY %d%c: %s, blip is ZERO at all delays! \n", tsk->port, idx + 'A', (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"));
                    /*- Clear any anomaly found under this errant condition */
                    tsk->stat[idx]      = 0;
                    tsk->loc[idx]       = 0;
                    tsk->strength[idx]  = 0;
                }
                //fprintf(fp,"idx: %d, tr_raw_data: 0x%x\n", idx, tr_raw_data);
            }
            /* End of Searching All Pairs for EC Invalid condition */
        }

        /*- If any invalid EC blips have been found, ... Results you thought were valid for other pairs may not be good */
        if (tsk->thresh[0] != 0) {
            //printf("VERIPHY_STATE_ANOMSEARCH_1: subchan: %d,    nc: %d\n", tsk->subchan, tsk->nc);
            /*- If the most recent test had no invalid EC blips, ... */
            //printf("flags: 0x%x, thresh[0]: %d,   thresh[1]:%d,   thresh[2]: %d\n", tsk->flags, tsk->thresh[0], tsk->thresh[1], tsk->thresh[2]);
            //fprintf(fp,"VERIPHY_STATE_ANOMSEARCH_1: subchan: %d,    nc: %d\n", tsk->subchan, tsk->nc);
            //fprintf(fp,"flags: 0x%x, thresh[0]: %d,   thresh[1]:%d,   thresh[2]: %d\n", tsk->flags, tsk->thresh[0], tsk->thresh[1], tsk->thresh[2]);

            /*- If the most recent test had no invalid EC blips, ... */
            /*- If we are at the beginning and encountered the f0 search, give it more time to settle ... */
            /*- If we in the middle of the search and encountered the f0 search, we want to start over and give time ... */
            if (tsk->thresh[0] == tsk->thresh[1]) {
                /*- If the anomaly search is just starting (NC == 3), ... */
                if (tsk->nc == ((tsk->flags & 0x80) ? 0 : 3)) {    /* Veriphy mode = VERIPHY_MODE_ANOM_ONLY */
                    if (tsk->flags & 0x80) {
                        VTSS_D("VERIPHY_STATE_INIT_ANOMSEARCH_1: Starting VERIPHY_MODE_ANOM_ONLY - Setting nc = %d", tsk->nc);
                    }
                    /*- Accumulate invalid EC blip count for timeouts */
                    tsk->thresh[2] += tsk->thresh[0] - 1;

                    /*- Continue on w/the anomaly search */
                    MEPA_MTIMER_START(&tsk->timeout, 200); /*- 200 Was 500, Ticks=200/5, Allow blip time to train to anomaly location */
                    tsk->subchan     = 0;     /*- Start search with subchannel A */
                    tsk->task_state  = VERIPHY_STATE_ANOMSEARCH_2;
                    VTSS_D("VeriPHY %d: Anomoly Search just starting, nc= %d, Next: VERIPHY_STATE_ANOMSEARCH_2: subchan: %d!", tsk->port, tsk->nc, tsk->subchan);
                    //fprintf(fp,"VeriPHY %d: Anomoly Search just starting, nc= %d, Next: VERIPHY_STATE_ANOMSEARCH_2: subchan: %d!\n", tsk->port, tsk->nc, tsk->subchan);
                } else { /*- in the middle of anomaly search, ... */
                    /*- Restart with NEXT canceller anomaly search */
                    tsk->nc = (tsk->flags & 0x80) ? 0 : 3;    /* Veriphy mode = VERIPHY_MODE_ANOM_ONLY */
                    if (tsk->flags & 0x80) {
                        VTSS_D("VERIPHY_STATE_INIT_ANOMSEARCH_1: Restart VERIPHY_MODE_ANOM_ONLY - Setting nc = %d", tsk->nc);
                    }

                    /*- EC invalid count current = prev count + 1 */
                    tsk->thresh[0] = tsk->thresh[1] + 1;
                    VTSS_D("VeriPHY Port:%d: After blip is ZERO at all delays, Restart Search, reset to NC: %d !", tsk->port, tsk->nc);
                    //printf("VeriPHY %d: After blip is ZERO at all delays, Restart Search, reset to NC: %d!\n", tsk->port, tsk->nc);
                    //fprintf(fp,"VeriPHY %d: After blip is ZERO at all delays, Restart Search, reset to NC: %d!\n", tsk->port, tsk->nc);

                    /*- delay before restarting anomaly search on NC 3 */
                    MEPA_MTIMER_START(&tsk->timeout, 500); /*- 100 ticks or x 5 ms/tick = 500 ms delay */
                    tsk->task_state  = VERIPHY_STATE_ANOMSEARCH_0;
                }
            }
            /*- else the most recent test had an invalid EC blip, */
            /*-      if the accumulated EC blip counts < timeout limit, ... */
            else if ((tsk->thresh[2] + tsk->thresh[0]) < 10) {
                /*- Loop back to wait for all valid EC blips or future timeout */
                tsk->task_state = VERIPHY_STATE_ANOMSEARCH_0;
                VTSS_D("VeriPHY %d: Invalid EC Blip, Setting to VERIPHY_STATE_ANOMSEARCH_0: subchan: %d,   nc: %d!", tsk->port, tsk->subchan, tsk->nc);
                //fprintf(fp,"VeriPHY %d: Invalid EC Blip, Setting to VERIPHY_STATE_ANOMSEARCH_0: subchan: %d,   nc: %d!\n", tsk->port, tsk->subchan, tsk->nc);
            } else { /*- more than 10 accumulated invalid EC blips, ... */
                //tsk->task_state |= 0x80; /*- Abort VeriPHY task */
                tsk->task_state |= VERIPHY_STATE_ABORT; /*- Abort VeriPHY task */
                VTSS_D("VeriPHY %d: More than 10 Invalid EC Blips, VERIPHY_STATE_ANOMSEARCH_1 ** ABORT!", tsk->port);
                //fprintf(fp,"VeriPHY %d: More than 10 Invalid EC Blips, VERIPHY_STATE_ANOMSEARCH_1 ** ABORT!\n", tsk->port);
            }

            /*- The f0 state is normally in link-down mode, so If running in link-down mode, reinitialize FFE */
            if ((tsk->flags & VERIPHY_FLAGS_LINKUP) == 0) {
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    FFEinit4_7_65nm(vtss_state, tsk, (FFEinit4_7anomSearch_65nm << (tsk->log2VGAx256 >> 8)) );
                } else {
                    FFEinit4_7(vtss_state, tsk, FFEinit4_7anomSearch);
                }
            }
        } else { /*- no invalid EC blips have been found */
            /*- Continue on w/the anomaly search */
            /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
            if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                MEPA_MTIMER_START(&tsk->timeout, 200);/*- Allow blip time to train to anomaly location */
            } else {
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    MEPA_MTIMER_START(&tsk->timeout, 200);    /*- Orig=200, Ticks=200/5, Allow blip time to train to anomaly location */
                    VTSS_D("VeriPHY %d: No Invalid EC Blips, Continue Anomoly Search, subchan: %d, nc: %d!", tsk->port, tsk->subchan, tsk->nc);
                } else {
                    if (tsk->nc == 0) {
                        MEPA_MTIMER_START(&tsk->timeout, 200);    /*- Allow blip time to train to anomaly location */
                        VTSS_D("VeriPHY %d: No Invalid EC Blips, Continue Anomoly Search, subchan: %d, nc: %d!", tsk->port, tsk->subchan, tsk->nc);
                    }
                }
            }

            tsk->subchan     = 0;     /*- Start search with subchannel A */

            tsk->task_state  = VERIPHY_STATE_ANOMSEARCH_2;
            //printf("VeriPHY %d: Next State: VERIPHY_STATE_ANOMSEARCH_2: subchan: %d!\n", tsk->port, tsk->subchan);
            //fprintf(fp,"VeriPHY %d: Next State: VERIPHY_STATE_ANOMSEARCH_2: subchan: %d!\n", tsk->port, tsk->subchan);
        }
        VTSS_D("VERIPHY_STATE_ANOMSEARCH_1: subchan: %d, nc: %d, flags: 0x%x, thresh[0]: %d, thresh[1]:%d, thresh[2]: %d", tsk->subchan, tsk->nc, tsk->flags, tsk->thresh[0], tsk->thresh[1], tsk->thresh[2]);

        break;

    /*- All subchannels are now known to be active, commence anomaly search */
    /*- Allowed time for the blip cancellor to search                       */
    /*- It searches for Anomolous echoes and cross-pair coupling            */
    case VERIPHY_STATE_ANOMSEARCH_2 :
        VTSS_D("VERIPHY_STATE_ANOMSEARCH_2: chan: %d    nc: %d", tsk->subchan, tsk->nc);
        //fprintf(fp,"VERIPHY_STATE_ANOMSEARCH_2: chan: %d    nc: %d\n", tsk->subchan, tsk->nc);
        AlwaysCheckEC = FALSE;

        if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
            AlwaysCheckEC = TRUE;
        }
        /*- Save current status as previous status */
        tsk->stat[(int)tsk->subchan] = (tsk->stat[(int)tsk->subchan] << 4) | (tsk->stat[(int)tsk->subchan] & 0x0f);

        /*- If we are looking at a Next Cancellor or we have a cross-pair short on this subchannel.. */
        /*- you already found a cross-pair short on this pair, don't over-write the existing anomoly */
        /*- Keep cross-pair shorts over shorts and opens */
        /*- The AlwaysCheckEC that surpasses all the elseif's */
        if ((AlwaysCheckEC) || tsk->nc != 0 || (tsk->stat[(int)tsk->subchan] & 0xc0) != 0x80) {
            tsk->signFlip = 0;
            VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));

            /* if (family != VTSS_PHY_FAMILY_MUSTANG || tsk->nc == 0)  */
            if ((!VTSS_PHY_1_GEN_DSP(tsk->port)) || (tsk->nc == 0)) {
                /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
                if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                    VTSS_D("VERIPHY_STATE_ANOMSEARCH_2 PHY_1_GEN_DSP");
                    VTSS_RC(tr_raw_read(vtss_state, tsk->port, 0x00ba/*0, 1, 0x1d*/, &tr_raw_data));
                    VTSS_D("tr_raw_data (&0x00ba) = 0x%x\n", tr_raw_data);
                } else {
                    short  value = (tsk->subchan << 11) | 0x1c0;
                    VTSS_RC(tr_raw_read(vtss_state, tsk->port, value/*- tsk->subchan, 3, 0x20*/, &tr_raw_data));
                    VTSS_D("Read ECVar State: Port: %d, subChan: %d, value: x%x, tr_raw_data: 0x%x", tsk->port, tsk->subchan, value, tr_raw_data);
                }

                VTSS_D("Read ECVar State: Port: %d, subChan: %d, tr_raw_data (AlwaysChk) = 0x%x", tsk->port, tsk->subchan, tr_raw_data);
                //fprintf(fp,"Read ECVar State: Port: %d, subChan: %d, tr_raw_data (AlwaysChk) = 0x%x\n", tsk->port, tsk->subchan, tr_raw_data);

                if (tr_raw_data & 0x80) {    /*- found anything? */
                    /*- ecVarBestDelay signals something really found (maybe < thresh) */
                    /*- ^^^^^^^^^^^^^^ ---------> vvvvvvvvvvvv */
                    /*- if (family == VTSS_PHY_FAMILY_MUSTANG)  */
                    if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                        idx = 64 + (tr_raw_data >> 16); /*- Mustang only can append ECvar onto the end of EC, not NC */
                    } else {
                        /*- The 16=base taps for Next Cancellor or the 72=base for taps for Echo Chancellor  */
                        idx = ((tsk->nc > 0) ? 16 : 72) + ((tr_raw_data & 0xff0000 ) >> 16); /* Calculate tap location */
                    }

                    VTSS_D("VeriPHY %d%c: BC Start: %s, blip @ tap %d", tsk->port, tsk->subchan + 'A', (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"), idx);
                    VTSS_D("possible anomaly near tap %d\n", idx);

                    /*- The GEN_2_DSP is for 65nm parts, MUSTANG Family is not 65nm */
                    if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                        /*- The thresh is a fixed value as a function of tap,    */
                        /*- but VGA gain acts as a scale factor                  */
                        /*- The further down the cable, the more attenuation     */
                        /*- 8 tap blip cancellor, pick the tap in the middle */
                        getAnomThresh_65nm(tsk, idx + 4);
                        /*- tsk->firstCoeff = (family == VTSS_PHY_FAMILY_MUSTANG ? 192 : 72); */
                        /*- 0-71 = Fixed Echo Cancellors, 72-79=blip cancellors, 80-95, 96-111, 112-127 are Next Cancellors */
                        tsk->firstCoeff = 72;
                        /*- The 16=base taps for Next Cancellor or the 72=base for taps for Echo Chancellor  */
                        /*- xc_search sets the status */
                        xc_search_65nm(vtss_state, tsk, idx, 0);

                        /*- Check to see if you found something, and if it is the first time you found an anomoly on this subchannel */
                        if (tsk->stat[(int)tsk->subchan] > 0 && tsk->stat[(int)tsk->subchan] <= 0x0f) {
                            /*- If something was found and it was the first time, check Validity */
                            /*- Check Validity checks for excessive noise */
                            (void) checkValidity_65nm(vtss_state, tsk, MAX_ABS_COEFF_ANOM_INVALID_NOISE);

                            /*- Update previous status to match current status after validity check */
                            tsk->stat[(int)tsk->subchan] = (tsk->stat[(int)tsk->subchan] << 4) |
                                                           (tsk->stat[(int)tsk->subchan] & 0x0f);
                        }
                    } else {
                        get_anom_thresh(tsk, idx + (tsk->numCoeffs >> 1));
                        /* tsk->firstCoeff = (family == VTSS_PHY_FAMILY_MUSTANG ? 192 : 72); */
                        tsk->firstCoeff = VTSS_PHY_1_GEN_DSP(tsk->port) ? 192 : 72;

                        xc_search(vtss_state, tsk, idx, 0);
                        if (tsk->stat[(int)tsk->subchan] > 0 && tsk->stat[(int)tsk->subchan] <= 0x0f) {
                            (void) checkValidity(vtss_state, tsk, MAX_ABS_COEFF_ANOM_INVALID_NOISE);

                            /*- Update previous status to match current status after validity check */
                            tsk->stat[(int)tsk->subchan] = (tsk->stat[(int)tsk->subchan] << 4) | (tsk->stat[(int)tsk->subchan] & 0x0f);
                        }
                    }
                    VTSS_D("VeriPHY %d%c: %s ", tsk->port, tsk->subchan + 'A',
                           (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"));

                } else {
                    /*- Didn't find anything - so there doesn't appear to be an anomoly */
                    VTSS_D("VeriPHY %d%c: %s (no blip)", tsk->port, tsk->subchan + 'A',
                           (tsk->nc >= 2) ? ((tsk->nc > 2) ? "NC3" : "NC2") : ((tsk->nc > 0) ? "NC1" : "EC"));
                }
            }

            /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
            if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                tsk->firstCoeff = (tsk->nc > 0) ? ((tsk->nc << 5) - 20) : 0xb4;
            } else {
                /*- Calculating the last group or block of 8 to address the next coeff */
                /*- we are going to examine of the EC or the NC  */
                /*- 64 = base addr of last group of 8 EC's. */
                /*- 0-71 = Fixed Echo Cancellors, 72-79=blip cancellors, */
                /*- 80-95, 96-111, 112-127 are Next Cancellors */
                tsk->firstCoeff = (tsk->nc > 0) ? ((tsk->nc << 4) + 72) : 64;
            }

            tsk->task_state = VERIPHY_STATE_ANOMSEARCH_3;
            VTSS_D("Going to VERIPHY_STATE_ANOMSEARCH_3; VeriPHY %d-%c: firstCoeff: %d", tsk->port, tsk->subchan + 'A', tsk->firstCoeff);
        } else if (tsk->subchan < 3) { /*- Move on to next subchannel, if not done */
            (tsk->subchan)++; /*- Re-enter in the same state for next subchannel */
            VTSS_D("VERIPHY_STATE_ANOMSEARCH_2; VeriPHY %d-%c: nc: %d, Incr subchan, firstCoeff: %d", tsk->port, tsk->subchan + 'A', tsk->nc, tsk->firstCoeff);
        } else if (tsk->nc > 0) { /*- Completed sweep of all 4 subchannels, move to next NC or EC */
            (tsk->nc)--;
            tsk->task_state = VERIPHY_STATE_INIT_ANOMSEARCH_1;
            VTSS_D("VERIPHY_STATE_ANOMSEARCH_2; VeriPHY %d-%c: nc: %d, Decr NC, firstCoeff: %d", tsk->port, tsk->subchan + 'A', tsk->nc, tsk->firstCoeff);
        } else { /*- Completed sweep of EC, exit anomaly search */
            tsk->task_state = VERIPHY_STATE_INIT_CABLELEN;
            tsk->subchan = 0;
        }

        VTSS_D("..End of VERIPHY_STATE_ANOMSEARCH_2 %d-%c: firstCoeff: x%x, subchan: x%x, nc: x%x, Nxt state: x%x ",
               tsk->port, tsk->subchan + 'A', tsk->firstCoeff, tsk->subchan, tsk->nc, tsk->task_state);

        break;

    /*- Continue anomaly search by sweeping through fixed EC/NC @ tsk->firstCoeff */
    /*- The tsk->firstCoeff is the first tap of the group of 8 */
    case VERIPHY_STATE_ANOMSEARCH_3:
        VTSS_D("VERIPHY_STATE_ANOMSEARCH_3: chan: %d,    nc: %d,  firstCoeff: x%x", tsk->subchan, tsk->nc, tsk->firstCoeff);
        //**printf("VERIPHY_STATE_ANOMSEARCH_3: chan: %d,    nc: %d,  firstCoeff: x%x \n", tsk->subchan, tsk->nc, tsk->firstCoeff);
        if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
            if (tsk->firstCoeff >= 0x80) { /*- if searching EC */
                idx = tsk->firstCoeff - 0x80;
            } else { /*- searching NC1..3 */
                idx = tsk->firstCoeff & 0x1f;
            }
        } else {
            if (tsk->firstCoeff < 80) { /*- if searching EC */
                idx = tsk->firstCoeff;
            } else { /*- searching NC1..3 */
                idx = tsk->firstCoeff & 0x0f;
            }
        }

        VTSS_D("VERIPHY_STATE_ANOMSEARCH_3: idx: %d, chan: %d,    nc: %d", idx, (i8)tsk->subchan, tsk->nc);
        //**printf("VERIPHY_STATE_ANOMSEARCH_3: idx: %d, chan: %d,    nc: %d\n", idx, (i8)tsk->subchan, tsk->nc);

        if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
            short ECtaps3_7_prefix = 5;

            getAnomThresh_65nm(tsk, idx + ((tsk->numCoeffs + 1) >> 1));
            xc_search_65nm(vtss_state, tsk, idx, (idx == 3) ? ECtaps3_7_prefix : 0);

            if (tsk->stat[(int)tsk->subchan] > 0 && tsk->stat[(int)tsk->subchan] <= 0x0f) {
                (void) checkValidity_65nm(vtss_state, tsk, MAX_ABS_COEFF_ANOM_INVALID_NOISE);

                /*- Update previous status to match current status after validity check */
                tsk->stat[(int)tsk->subchan] = (tsk->stat[(int)tsk->subchan] << 4) | (tsk->stat[(int)tsk->subchan] & 0x0f);
                //printf("VERIPHY_STATE_ANOMSEARCH_3: Updating stat[%d]: %d\n", (i8)tsk->subchan, tsk->stat[(int)tsk->subchan]);
                //fprintf(fp,"VERIPHY_STATE_ANOMSEARCH_3: Updating stat[%d]: %d\n", (i8)tsk->subchan, tsk->stat[(int)tsk->subchan]);
            }
        } else {
            get_anom_thresh(tsk, idx + (tsk->numCoeffs >> 1));
            xc_search(vtss_state, tsk, idx, (idx == 4) ? 6 : 0);
            if (tsk->stat[(int)tsk->subchan] > 0 && tsk->stat[(int)tsk->subchan] <= 0x0f) {
                (void) checkValidity(vtss_state, tsk, MAX_ABS_COEFF_ANOM_INVALID_NOISE);

                /*- Update previous status to match current status after validity check */
                tsk->stat[(int)tsk->subchan] = (tsk->stat[(int)tsk->subchan] << 4) | (tsk->stat[(int)tsk->subchan] & 0x0f);
            }
        }

        //printf("VERIPHY_STATE_ANOMSEARCH_3, nc: %d, idx: %d, subChan: %d, firstCoeff: 0x%x, numCoeffs: %d \n", tsk->nc, idx, (i8)tsk->subchan, (u8)tsk->firstCoeff, (u8)tsk->numCoeffs);
        //fprintf(fp,"VERIPHY_STATE_ANOMSEARCH_3, nc: %d, idx: %d, subChan: %d, firstCoeff: 0x%x, numCoeffs: %d \n", tsk->nc, idx, (i8)tsk->subchan, (u8)tsk->firstCoeff, (u8)tsk->numCoeffs);

        if (tsk->nc > 0) {
            if (idx > 0) {
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    tsk->firstCoeff -= 8;
                } else {
                    tsk->firstCoeff -= tsk->numCoeffs;
                }
            } else {
                /*- Recode NC-anomalies as cross-pair anomalies at end-of-search */
                if ((tsk->stat[(int)tsk->subchan] & 0x0f) > 0 && (tsk->stat[(int)tsk->subchan] & 0x08) == 0) {
                    tsk->stat[(int)tsk->subchan] = (tsk->stat[(int)tsk->subchan] & 0xf4) | 8;
                    if (tsk->nc != tsk->subchan) {
                        tsk->stat[(int)tsk->subchan] += tsk->nc;
                    }
                }
            }
            //fprintf(fp,"VERIPHY_STATE_ANOMSEARCH_3 #2, nc: %d, idx: %d, subChan: %d, firstCoeff: 0x%x, numCoeffs: %d \n", tsk->nc, idx, (i8)tsk->subchan, (u8)tsk->firstCoeff, (u8)tsk->numCoeffs);
        } else { /*- for EC, conditionally extend search down to 6th tap */
            if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                if (idx > 16) {
                    tsk->firstCoeff -= tsk->numCoeffs;
                } else if (idx == 16) {
                    tsk->firstCoeff  = 0x80 | 5;
                    tsk->numCoeffs = 11;
                } else {
                    tsk->numCoeffs = 12; /*- Restore to default of 12 coeffs */
                    idx = 0; /*- Walk to next state */
                }
            } else {
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    if (idx > 8) {
                        tsk->firstCoeff -= 8;
                    } else if (idx == 8) {
                        tsk->firstCoeff  = 3;
                        tsk->numCoeffs = 4;
                    } else {
                        tsk->numCoeffs = 7; /*- Restore to default of 8 coeffs */
                        idx = 0; /*- Walk to next state */
                    }
                } else {
                    if (idx > 8) {
                        tsk->firstCoeff -= tsk->numCoeffs;
                    } else if (idx == 8) {
                        tsk->firstCoeff  = 4;
                        tsk->numCoeffs = 4;
                    } else {
                        tsk->numCoeffs = 8; /*- Restore to default of 8 coeffs */
                        idx = 0; /*- Walk to next state */
                    }
                }
            }
        }

        //fprintf(fp,"VERIPHY_STATE_ANOMSEARCH_3 #3, ======> subChan: %d, nc: %d <========  idx: %d,  firstCoeff: 0x%x, numCoeffs: %d \n", (i8)tsk->subchan, tsk->nc, idx, (u8)tsk->firstCoeff, (u8)tsk->numCoeffs);

        if (idx == 0) {
            if (tsk->subchan < 3) { /*- Move on to next subchannel, if not done */
                VTSS_D("n++++++ prev chan=%d ++++++++++++++++++++++++++++++++++++++++++++++++", tsk->subchan);
                (tsk->subchan)++;
                VTSS_D("++++++++++++++++++++++++++++++ nxt chan=%d ++++++++++++++++++++++++++", tsk->subchan);
                tsk->task_state = VERIPHY_STATE_ANOMSEARCH_2;
                VTSS_D("...... Going back to VERIPHY_STATE_ANOMSEARCH_2, Increasing subChan: %x ", tsk->subchan);
            } else if (tsk->nc > 0) { /*- Completed sweep of all 4 subchannels, move to next NC or EC */
                VTSS_D(".......prev nc=%d....................................................", tsk->nc);
                (tsk->nc)--;
                VTSS_D("................................. nxt nc=%d..........................", tsk->nc);
                tsk->task_state = VERIPHY_STATE_INIT_ANOMSEARCH_1;
                VTSS_D("...... Going back to VERIPHY_STATE_ANOMSEARCH_1, Decreasing NC or EC: %x ", tsk->nc);
            } else { /*- Completed sweep of EC, exit anomaly search */
                tsk->task_state = VERIPHY_STATE_INIT_CABLELEN;
                tsk->subchan = 0;
                VTSS_D("------ ALL DONE!  chan=%d ------------------------------------------------", tsk->subchan);
                VTSS_D("Completed EC Sweep, Proceeding to VERIPHY_STATE_INIT_CABLELEN ");
            }
        }

        break;

    /*- Initialize getCableLength search */
    /*- If there are any Non-Anomolous pairs, then do length.  */
    /*- If there are Anomolies on all 4 pairs, we set loc=255 and exit out */
    case VERIPHY_STATE_INIT_CABLELEN :
        VTSS_D("VERIPHY_STATE_INIT_CABLELEN: chan: %d,    nc: %d    flags: 0x%x", tsk->subchan, tsk->nc, tsk->flags);
        //**printf("VERIPHY_STATE_INIT_CABLELEN: chan: %d,    nc: %d    flags: 0x%x \n", tsk->subchan, tsk->nc, tsk->flags);

        //for (idx = 0; (tsk->flags & 0xc0) == 0 && idx < 4; ++idx)
        for (idx = 0; idx < 4; ++idx) {
            tsk->stat[idx] &= 0x0f;
            if (tsk->stat[idx] == 0) {
                if ((tsk->flags & 0xc0) != 0) {
                    tsk->loc[idx] = 255;    /*- Set to unknown location, if cable length not measured */
                } else {
                    tsk->flags |= VERIPHY_FLAGS_GETCBLLENDONE;
                }
            }
        }

        if ((tsk->flags & 0xc0) != 0 || (tsk->flags & VERIPHY_FLAGS_GETCBLLENDONE) == 0) { /*- Anoamlies found on all four pairs */
            tsk->task_state = VERIPHY_STATE_PAIRSWAP;
            VTSS_D("Exitting VERIPHY_STATE_INIT_CABLELEN: chan: %d,    nc: %d    flags: 0x%x", tsk->subchan, tsk->nc, tsk->flags);

        } else { /*- Initialize for measuring cable length */
            VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
            VTSS_D("VeriPHY getCableLength - calling FFEinit");
            if ((tsk->flags & VERIPHY_FLAGS_LINKUP) == 0) {/*- If link-down, gain up FFE to make blip easier to spot! */
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    FFEinit4_7_65nm(vtss_state, tsk, (short)FFEinit4_7lengthSearch_65nm);
                } else {
                    FFEinit4_7(vtss_state, tsk, FFEinit4_7lengthSearch);
                }
                /*- Smooth EcVar training: EcVarTrainingTime = 75, EcVarShowtimeGain = 1 */
                if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b4/*0, 1, 1a*/, 0x96ad));
                } else {
                    VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x190/*0, 3, 8*/, 0x04b5));
                }
            }

            if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                /*- EcVarForceDelayVal = 232 - 64, EcVarForceDelay = 1, EcVarForceIdle=1 */
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, (((232 - 64) << 2) | 3)));
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, (((232 - 64) << 2) | 2))); /*- EcVarForceIdle = 0 */
            } else {
                u32 trRawData = 0;
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {

                    trRawData = (((232 - 72) << 1) | 1);     /* TrRawData[0], (0xA0 << 1) | 1  = 0x1 0100 0001 = 0x141 */
                    trRawData |= ((232 - 72) >> 7) << 8;      /* (0xA0 >> 7) << 8 = 0x1 0000 0000 = 0x100 */
                } else {
                    trRawData = ((232 - 72) << 1) | 1;       /* (0xA0 << 1) | 1 = 0x141 */
                }
                /*- EcVarForceDelayVal = 232 - 72, EcVarForceDelay = 1 */
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, trRawData));
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0x01));   /*- EcVarForceIdle = 1 */
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0));   /*- EcVarForceIdle = 0 */
            }

            MEPA_MTIMER_START(&tsk->timeout, 10);    /*- Orig=10, 2 Tick Delay = 10ms, Allow blip time to train to anomaly location */
            tsk->task_state = VERIPHY_STATE_INIT_CABLELEN2;
        }
        break;

    /*- Initialize getCableLength search */
    case VERIPHY_STATE_INIT_CABLELEN2 :
        VTSS_D("VERIPHY_STATE_INIT_CABLELEN2: chan: %d,    nc: %d    flags: 0x%x", tsk->subchan, tsk->nc, tsk->flags);
        //**printf("VERIPHY_STATE_INIT_CABLELEN2: chan: %d,    nc: %d    flags: 0x%x\n", tsk->subchan, tsk->nc, tsk->flags);
        idx = 0xff;
        for (tsk->subchan = 0; tsk->subchan < 4; ++(tsk->subchan)) {
            if (tsk->stat[(int)tsk->subchan] != 0) {
                tsk->thresh[(int)tsk->subchan] = 0;
            } else {
                int limit;

                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    limit =  4;
                } else {
                    limit =  ((tsk->flags & VERIPHY_FLAGS_LINKUP) ? 1 : 4);
                }
                for (tsk->signFlip = 0,
                     vtss_state->phy_inst_state.maxAbsCoeff = 0;
                     ((vtss_state->phy_inst_state.maxAbsCoeff < limit) && (tsk->signFlip < MAX_SIGN_FLIP_ITERATIONS));
                     ++(tsk->signFlip)) {
                    /*- ECVar Tap=0, Discard =1, Rpt = 8, numCoeffs=8 */

                    if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                        //(void) readAvgECNCECVar_65nm(vtss_state, (tsk->subchan << 6) | tsk->port, 72, 0xf8);
                        (void) readAvgECNCECVar_65nm(vtss_state, tsk, 72, (i8)(((u8)(-8) << 3) | 7));
                        if (vtss_state->phy_inst_state.maxAbsCoeff < 4) {
                            MEPA_MTIMER_START(&tsk->timeout, 2);    /*- Orig=2, 2ms, Allow blip time to train to anomaly location */
                        } else {
                            tsk->thresh[(int)tsk->subchan] = vtss_state->phy_inst_state.maxAbsCoeff;
                        }
                    } else {
                        (void) readAvgECNCECVar(vtss_state, (tsk->subchan << 6) | tsk->port,
                                                family == VTSS_PHY_1_GEN_DSP(tsk->port) ? 192 : 72,
                                                0xf8);

                        if (vtss_state->phy_inst_state.maxAbsCoeff < ((tsk->flags & VERIPHY_FLAGS_LINKUP) ? 1 : 4)) {
                            MEPA_MTIMER_START(&tsk->timeout, 2);    /*- Orig=2, 2ms, Allow blip time to train to anomaly location */
                        } else {
                            tsk->thresh[(int)tsk->subchan] = vtss_state->phy_inst_state.maxAbsCoeff;
                        }
                    }
                }

                if (tsk->signFlip > 1) {
                    VTSS_D("VeriPHY %d%c: maxAbsC(tsk->thresh) = %d took %d attempts! ",
                           tsk->port, tsk->subchan + 'A', tsk->thresh[(int)tsk->subchan], tsk->signFlip);
                    //printf("VeriPHY %d%c: maxAbsC(tsk->thresh) = %d took %d attempts! \n", tsk->port, tsk->subchan + 'A', tsk->thresh[(int)tsk->subchan], tsk->signFlip);
                    //fprintf(fp,"VeriPHY %d%c: maxAbsC(tsk->thresh) = %d took %d attempts! \n", tsk->port, tsk->subchan + 'A', tsk->thresh[(int)tsk->subchan], tsk->signFlip);
                }

                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    if ((tsk->thresh[(int)tsk->subchan] + CABLE_LEN_SEARCH_THRESH_INCR) < MIN_CABLE_LEN_SEARCH_THRESH) {
                        tsk->thresh[(int)tsk->subchan] = MIN_CABLE_LEN_SEARCH_THRESH;
                    } else {
                        tsk->thresh[(int)tsk->subchan] += CABLE_LEN_SEARCH_THRESH_INCR;
                    }

                    VTSS_D("VeriPHY %d-%c: tsk->thresh[%d] = %d  MAX_NOISE limit of: %d!", tsk->port, tsk->subchan + 'A', tsk->subchan,
                           tsk->thresh[(int)tsk->subchan], (short) MAX_ABS_COEFF_LEN_INVALID_NOISE);

                    if (tsk->thresh[(int)tsk->subchan] > (short) MAX_ABS_COEFF_LEN_INVALID_NOISE) {
                        VTSS_D("VeriPHY %d%c: tsk->thresh[%d] = %d > noise limit of %d!", tsk->port, tsk->subchan + 'A', tsk->subchan,
                               tsk->thresh[(int)tsk->subchan], (short) MAX_ABS_COEFF_LEN_INVALID_NOISE);

                        tsk->loc[(int)tsk->subchan] = 255;
                        tsk->strength[(int)tsk->subchan] = tsk->thresh[(int)tsk->subchan];
                    } else if (idx == 0xff) {
                        idx = (tsk->subchan << 2) | tsk->subchan;
                        VTSS_D("VeriPHY001 %d-%c: idx: %d, tsk->subchan: x%x!", tsk->port, tsk->subchan + 'A', idx, tsk->subchan);
                    } else if (tsk->thresh[(int)tsk->subchan] > tsk->thresh[idx >> 2]) {
                        idx = tsk->subchan << 2 | (idx & 3);
                        VTSS_D("VeriPHY002 %d-%c: idx: %d, tsk->subchan: x%x!", tsk->port, tsk->subchan + 'A', idx, tsk->subchan);
                    } else {
                        VTSS_D("VeriPHY003 %d-%c: idx: %d, tsk->subchan: x%x!", tsk->port, tsk->subchan + 'A', idx, tsk->subchan);
                    }

                    if (idx != 0xff && tsk->thresh[(int)tsk->subchan] < tsk->thresh[idx & 3]) {
                        idx = (idx & 0x0c) | tsk->subchan;
                        VTSS_D("VeriPHY004 %d-%c: idx: %d, tsk->subchan: x%x!", tsk->port, tsk->subchan + 'A', idx, tsk->subchan);
                    }
                } else {
                    if (tsk->thresh[(int)tsk->subchan] < 14) {
                        tsk->thresh[(int)tsk->subchan] = 20;
                    } else {
                        tsk->thresh[(int)tsk->subchan] += 6;
                    }
                    if (tsk->thresh[(int)tsk->subchan] > MAX_ABS_COEFF_LEN_INVALID_NOISE) {
                        VTSS_D("VeriPHY %d%c: maxAbsC(tsk->thresh) = %d > noise limit of %d!",
                               tsk->port, tsk->subchan + 'A', tsk->thresh[(int)tsk->subchan], MAX_ABS_COEFF_LEN_INVALID_NOISE);
                        tsk->loc[(int)tsk->subchan] = 255;
                        tsk->strength[(int)tsk->subchan] = tsk->thresh[(int)tsk->subchan];
                    } else if (idx == 0xff) {
                        idx = (tsk->subchan << 2) | tsk->subchan;
                    } else if (tsk->thresh[(int)tsk->subchan] > tsk->thresh[idx >> 2]) {
                        idx = tsk->subchan << 2 | (idx & 3);
                    }
                    if (idx != 0xff && tsk->thresh[(int)tsk->subchan] < tsk->thresh[idx & 3]) {
                        idx = (idx & 0x0c) | tsk->subchan;
                    }
                }
            }
        } /*- End of Loop */

        /*- if max(tsk->thresh) >= 1.5*min(tsk->thresh), the max subchan may be unreliable */
        if (idx != 0xff && (tsk->thresh[idx >> 2] >= (tsk->thresh[idx & 3] + (tsk->thresh[idx & 3] >> 1)))) {
            tsk->flags = ((idx << 2) & 0x30) | 0x08 | (tsk->flags & 0xc7);
        } else {
            tsk->flags = (tsk->flags & 0xc7);
        }

        //printf("VeriPHY005 %d-%c: idx: %d, tsk->subchan: %d,  Flags: 0x%x!\n", tsk->port, tsk->subchan+'A', idx, tsk->subchan, tsk->flags);
        //fprintf(fp,"VeriPHY005 %d-%c: idx: %d, tsk->subchan: %d,  Flags: 0x%x!\n", tsk->port, tsk->subchan+'A', idx, tsk->subchan, tsk->flags);

        VTSS_D("VeriPHY %d: tsk->thresh = { %d, %d, %d, %d }, unreliablePtr = %d", tsk->port, tsk->thresh[0], tsk->thresh[1], tsk->thresh[2], tsk->thresh[3], (((tsk->flags >> 4) & 3) + (tsk->flags & 8)));
        //**printf("VeriPHY %d: tsk->thresh = { %d, %d, %d, %d }, unreliablePtr = %d \n", tsk->port, tsk->thresh[0], tsk->thresh[1], tsk->thresh[2], tsk->thresh[3], (((tsk->flags >> 4) & 3) + (tsk->flags & 8)));
        //printf("VeriPHY %d: tsk->thresh = { %d, %d, %d, %d }, unreliablePtr = %d\n", tsk->port, tsk->thresh[0], tsk->thresh[1], tsk->thresh[2], tsk->thresh[3], (((tsk->flags >> 4) & 3) + (tsk->flags & 8)));
        //fprintf(fp,"VeriPHY %d: tsk->thresh = { %d, %d, %d, %d }, unreliablePtr = %d\n", tsk->port, tsk->thresh[0], tsk->thresh[1], tsk->thresh[2], tsk->thresh[3], (((tsk->flags >> 4) & 3) + (tsk->flags & 8)));


        tsk->flags &= ~VERIPHY_FLAGS_GETCBLLENDONE; /*- Clear done flag */
        tsk->signFlip = 0;

        /* if (family == VTSS_PHY_FAMILY_MUSTANG) */
        if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
            tsk->tr_raw0188 = (168 << 2) | 2;
            tsk->firstCoeff = 192;
        } else {
            tsk->firstCoeff = 72;
            if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                tsk->tr_raw0188 = (152 << 1) | 1;
                tsk->tr_raw0188 |= (152 >> 7) << 8;

                VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, tsk->tr_raw0188));
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0x01));   /*- EcVarForceIdle = 1 */
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0));      /*- EcVarForceIdle = 0 */
            } else {
                tsk->tr_raw0188 = (160 << 1) | 1;
            }
        }

        MEPA_MTIMER_START(&tsk->timeout, 2);    /*- Orig=2 2ms, Allow blip time to train to anomaly location */
        tsk->task_state = VERIPHY_STATE_GETCABLELEN_0;
        break;

    /*- start getCableLength search */
    case VERIPHY_STATE_GETCABLELEN_0 :
        VTSS_D("VERIPHY_STATE_GET_CABLELEN_0");
        VTSS_D("VERIPHY_STATE_GET_CABLELEN_0: chan: %d,    nc: %d    flags: 0x%x", tsk->subchan, tsk->nc, tsk->flags);
        //**printf("VERIPHY_STATE_GET_CABLELEN_0: chan: %d,    nc: %d    flags: 0x%x\n", tsk->subchan, tsk->nc, tsk->flags);
        if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
            short c51_idata *c = NULL;
            unsigned char cnt;

            if (tsk->firstCoeff == 72) {
                //idx = (tsk->TrRaw0188[0] >> 1) | (tsk->TrRaw0188[1] << 7);
                idx = ((tsk->tr_raw0188 & 0xff) >> 1) | (((tsk->tr_raw0188 & 0xff00) >> 8) << 7);
                idx += 72; // Make idx indicate coefficient tap #
            } else {
                idx = tsk->firstCoeff; // Make idx indicate coefficient tap #
            }

            /*- delay done by 8 taps to scan 8 taps past 1st detection to refine length estimate */
            if ((tsk->loc[0] > 0) && (tsk->loc[1] > 0) && (tsk->loc[2] > 0) && (tsk->loc[3] > 0)) {
                tsk->flags |= VERIPHY_FLAGS_GETCBLLENDONE; // Set done flag
            }

            for (tsk->subchan = 0; tsk->subchan < 4; ++(tsk->subchan)) {
                /*- only measure length on non-anomalous subchans */
                if (tsk->stat[tsk->subchan] == 0 && ((idx + 12) > tsk->loc[tsk->subchan])) {
                    c = readAvgECNCECVar_65nm(vtss_state, tsk, tsk->firstCoeff, LEN_SEARCH_COEFF_READAVG_LEN);

                    //**printf("VeriPHY %d%c: tap %d..%d = %5d %5d %5d %5d %5d %5d %5d %5d\n", (int)tsk->flg_phy, (int)(tsk->subchan + 'A'), (int)idx, (int)idx + 7, c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
                    c   += 8;
                    idx += 8;
                    cnt  = 8;
                    do {
                        --idx;
                        --c;
                        if (((tsk->signFlip >> (int)tsk->subchan) & 1) != 0) {
                            if (tsk->loc[tsk->subchan] == (idx + 1)) {
                                if ( (tsk->strength[(int)tsk->subchan] < 0 && *c < tsk->strength[(int)tsk->subchan]) ||
                                     (tsk->strength[(int)tsk->subchan] > 0 && *c > tsk->strength[(int)tsk->subchan]) ) {
                                    tsk->loc[(int)tsk->subchan] = idx;
                                    tsk->strength[(int)tsk->subchan] = *c;
                                    //T(TR_MOD_PORT,TR_LVL_CRIT,"\tsign-move 2 tap %d, strength = %d", (int)tsk->loc[tsk->subchan], tsk->strength[tsk->subchan]);
                                }
                            }
                        } else if (ABS(*c) > tsk->thresh[(int)tsk->subchan]) {
                            if ((tsk->strength[(int)tsk->subchan] == 0) ||
                                ((tsk->loc[(int)tsk->subchan] <= (idx + 3)) && // In the Neighborhood of Anomoly
                                 (((tsk->strength[(int)tsk->subchan] > 0) && (tsk->strength[(int)tsk->subchan] <= *c)) ||
                                  ((tsk->strength[(int)tsk->subchan] < 0) && (tsk->strength[(int)tsk->subchan] >= *c))))) {

                                if (tsk->strength[(int)tsk->subchan] == 0) { /* Test validity 1st detection only */
                                    tsk->strength[(int)tsk->subchan] = *c;
                                    tsk->loc[(int)tsk->subchan] = idx;
                                    //checkValidity_65nm(tsk, MaxAbsCoeffLenInvalidNoise);
                                    (void) checkValidity_65nm(vtss_state, tsk, MAX_ABS_COEFF_LEN_INVALID_NOISE);
                                    if (tsk->strength[(int)tsk->subchan] != 0) {
                                        //T(TR_MOD_PORT,TR_LVL_CRIT,"\tblip-det. @ tap %d, strength = %d", idx, *c);
                                    }
                                } else {
                                    tsk->strength[(int)tsk->subchan] = *c;
                                    tsk->loc[(int)tsk->subchan] = idx;
                                    //T(TR_MOD_PORT,TR_LVL_CRIT,"\tblip-move 2 tap %d, strength = %d", idx, *c);
                                }

                            } else if ((tsk->loc[(int)tsk->subchan] <= (idx + 5)) &&
                                       (((tsk->strength[(int)tsk->subchan] > 0) &&
                                         /*- Same Strength or a litle weaker (7/8th strength) */
                                         /*- but opposite of sign                             */
                                         ((-tsk->strength[(int)tsk->subchan] + (tsk->strength[(int)tsk->subchan] >> 3)) >= *c))
                                        || ((tsk->strength[(int)tsk->subchan] < 0) &&
                                            ((-tsk->strength[(int)tsk->subchan] + (tsk->strength[(int)tsk->subchan] >> 3)) <= *c))
                                       )) {
                                tsk->loc[(int)tsk->subchan] = idx;
                                tsk->strength[(int)tsk->subchan] = *c;
                                tsk->signFlip |= 1 << (int)tsk->subchan;
                                //T(TR_MOD_PORT,TR_LVL_CRIT,"\tsign-flip @ tap %d, strength = %d", tsk->loc[tsk->subchan], tsk->strength[tsk->subchan]);
                            }
                        }
                    } while (--cnt != 0);
                }
            }  /*-  end for ( tsk->subchan = 0; tsk->subchan < 4; ++(tsk->subchan) ) */

            if (tsk->flags & VERIPHY_FLAGS_GETCBLLENDONE) {
                tsk->task_state = VERIPHY_STATE_GETCABLELEN_1;
            }

            if ((tsk->flags & VERIPHY_FLAGS_GETCBLLENDONE) || (tsk->firstCoeff == 72)) {
                if ((tsk->flags & VERIPHY_FLAGS_GETCBLLENDONE) == 0 && (idx > 72)) {
                    idx -= (72 + 8);
                    tsk->tr_raw0188 = (idx << 1) | 1;
                    tsk->tr_raw0188 |= ((tsk->tr_raw0188 & 0xff00) >> 7) << 8;
                } else { /*- End blip scan; restore blip canceller to normal operation */
                    /*- EcVarForceDelayVal = 0, EcVarForceDelay = 0 */
                    tsk->tr_raw0188 = 0;
                    tsk->firstCoeff = 64;

                    /* Scale up threshold to avoid false triggers */
                    for (idx = 0; idx < 4; ++idx) {
                        tsk->thresh[idx] = tsk->thresh[idx] + (tsk->thresh[idx] >> 2);
                    }
                }

                VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, tsk->tr_raw0188));
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 1));     /*- EcVarForceIdle = 1 */
                VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0));     /*- EcVarForceIdle = 0 */
                //tsk->delay_ticks = 2;
                MEPA_MTIMER_START(&tsk->timeout, 10);   // Orig_value = 10

            } else if (tsk->firstCoeff != 0) {
                tsk->firstCoeff -= 8;
            } else {
                tsk->task_state = VERIPHY_STATE_GETCABLELEN_1;
            }
        } else {  /*- ********* End of 65nm ****  Start of 130nm *********** */
            if (((tsk->flags & 4) == 0) && ((tsk->firstCoeff & 0x7f) >= tsk->numCoeffs)) {
                /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
                if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                    if (tsk->firstCoeff == 192) {
                        idx = tsk->tr_raw0188 >> 2;
                        if (idx > 0) {
                            /*- EcVarForceDelayVal = current delay, EcVarForceDelay = 1 */
                            idx -= tsk->numCoeffs;
                            tsk->tr_raw0188 = (idx << 2) | 2;
                            idx += 64; /*- Make idx indicate coefficient tap # */
                        } else { /*- End blip scan; restore blip canceller to normal operation */
                            /*- EcVarForceDelayVal = 0, EcVarForceDelay = 0 */
                            tsk->tr_raw0188 = 0;
                            tsk->firstCoeff = 0x80 | 52;

                            /*- Scale up threshold to avoid false triggers */
                            for (idx = 0; idx < 4; ++idx) {
                                tsk->thresh[idx] = tsk->thresh[idx] + (tsk->thresh[idx] >> 2);
                            }
                            idx = tsk->firstCoeff & 0x3f; /*- Make idx indicate coefficient tap # */
                        }

                        VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, tsk->tr_raw0188 | 1)); /*- EcVarForceIdle = 1 */
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, tsk->tr_raw0188));     /*- EcVarForceIdle = 0 */
                    } else {
                        tsk->firstCoeff -= tsk->numCoeffs;
                        idx = tsk->firstCoeff & 0x3f; /*- Make idx indicate coefficient tap # */
                    }
                } else {
                    if (tsk->firstCoeff == 72) {
                        idx = tsk->tr_raw0188 >> 1;
                        if (idx > 0) {
                            /*- EcVarForceDelayVal = current delay, EcVarForceDelay = 1 */
                            idx -= tsk->numCoeffs;
                            tsk->tr_raw0188 = (idx << 1) | 1;
                            idx += 72; /*- Make idx indicate coefficient tap # */
                        } else { /*- End blip scan; restore blip canceller to normal operation */
                            /*- EcVarForceDelayVal = 0, EcVarForceDelay = 0 */
                            tsk->tr_raw0188 = 0;
                            tsk->firstCoeff = 64;

                            /*- Scale up threshold to avoid false triggers */
                            for (idx = 0; idx < 4; ++idx) {
                                tsk->thresh[idx] = tsk->thresh[idx] + (tsk->thresh[idx] >> 2);
                            }
                            idx = tsk->firstCoeff; /*- Make idx indicate coefficient tap # */
                        }

                        VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, tsk->tr_raw0188));
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 1));     /*- EcVarForceIdle = 1 */
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0));     /*- EcVarForceIdle = 0 */
                    } else {
                        tsk->firstCoeff -= tsk->numCoeffs;
                        idx = tsk->firstCoeff; /*- Make idx indicate coefficient tap # */
                    }
                }

                VTSS_D("probing for cable length at tap %d ", idx);
                //fprintf(fp,"probing for cable length at tap %d\n", idx);
                /*- delay done by numCoeffs taps to scan numCoeffs taps past 1st detection to refine length estimate */
                if ((tsk->loc[0] > 0) && (tsk->loc[1] > 0) && (tsk->loc[2] > 0) && (tsk->loc[3] > 0)) {
                    tsk->flags |= 4;    /*- Set done flag */
                }

                for (tsk->subchan = 0; tsk->subchan < 4; ++(tsk->subchan)) {
                    /*- only measure length on non-anomalous subchans */
                    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
                    if (tsk->stat[(int)tsk->subchan] == 0 && ((idx + 12) > tsk->loc[(int)tsk->subchan])) {
                        short c51_idata *c = readAvgECNCECVar(vtss_state, (tsk->subchan << 6) | tsk->port,
                                                              tsk->firstCoeff, 0x20 | tsk->numCoeffs);
                        u8 cnt;

                        c   += tsk->numCoeffs;
                        idx += tsk->numCoeffs;
                        cnt  = tsk->numCoeffs;
                        do {
                            --idx;
                            --c;
                            if (((tsk->signFlip >> tsk->subchan) & 1) != 0) {
                                if (tsk->loc[(int)tsk->subchan] == (idx + 1)) {
                                    if ( (tsk->strength[(int)tsk->subchan] < 0 && *c < tsk->strength[(int)tsk->subchan]) ||
                                         (tsk->strength[(int)tsk->subchan] > 0 && *c > tsk->strength[(int)tsk->subchan]) ) {
                                        tsk->loc[(int)tsk->subchan] = idx;
                                        tsk->strength[(int)tsk->subchan] = *c;
                                        VTSS_D("VeriPHY %d%c: ", (int)tsk->port, (int)(tsk->subchan + 'A'));
                                        VTSS_D("sign-move 2 tap %d, strength = %d ", (int)tsk->loc[(int)tsk->subchan], tsk->strength[(int)tsk->subchan]);
                                        //fprintf(fp,"VeriPHY %d%c: sign-move 2 tap %d, strength = %d\n", (int)tsk->port, (int)(tsk->subchan + 'A'), (int)tsk->loc[(int)tsk->subchan], tsk->strength[(int)tsk->subchan]);
                                    }
                                }
                            } else if (ABS(*c) > tsk->thresh[(int)tsk->subchan]) {
                                if ((tsk->strength[(int)tsk->subchan] == 0) ||
                                    ((tsk->loc[(int)tsk->subchan] <= (idx + 3)) &&
                                     (((tsk->strength[(int)tsk->subchan] > 0) &&
                                       (tsk->strength[(int)tsk->subchan] <= *c)) ||
                                      ((tsk->strength[(int)tsk->subchan] < 0) &&
                                       (tsk->strength[(int)tsk->subchan] >= *c)))
                                    )) {
                                    if (tsk->strength[(int)tsk->subchan] == 0) { /*- Test validity 1st detection only */
                                        tsk->strength[(int)tsk->subchan] = *c;
                                        tsk->loc[(int)tsk->subchan] = idx;
                                        (void) checkValidity(vtss_state, tsk, MAX_ABS_COEFF_LEN_INVALID_NOISE);
                                        if (tsk->strength[(int)tsk->subchan] != 0) {
                                            VTSS_D("VeriPHY %d%c: ", (int)tsk->port, (int)(tsk->subchan + 'A'));
                                            VTSS_D("blip-det. @ tap %d, strength = %d ", idx, *c);
                                            //fprintf(fp,"Veriphy %d%c: blip-det. @ tap %d, strength = %d\n", (int)tsk->port, (int)(tsk->subchan + 'A'), idx, *c);
                                        }
                                    } else {
                                        tsk->strength[(int)tsk->subchan] = *c;
                                        tsk->loc[(int)tsk->subchan] = idx;
                                        VTSS_D("VeriPHY %d%c: ", (int)tsk->port, (int)(tsk->subchan + 'A'));
                                        VTSS_D("blip-move 2 tap %d, strength = %d ", idx, *c);
                                        //fprintf(fp,"Veriphy %d%c, blip-move 2 tap %d, strength = %d\n", (int)tsk->port, (int)(tsk->subchan + 'A'), idx, *c);
                                    }
                                } else if ((tsk->loc[(int)tsk->subchan] <= (idx + 5)) &&
                                           (((tsk->strength[(int)tsk->subchan] > 0) &&
                                             ((-tsk->strength[(int)tsk->subchan] + (tsk->strength[(int)tsk->subchan] >> 3)) >= *c))
                                            || ((tsk->strength[(int)tsk->subchan] < 0) &&
                                                ((-tsk->strength[(int)tsk->subchan] + (tsk->strength[(int)tsk->subchan] >> 3)) <= *c))
                                           )) {
                                    tsk->loc[(int)tsk->subchan] = idx;
                                    tsk->strength[(int)tsk->subchan] = *c;
                                    tsk->signFlip |= 1 << tsk->subchan;
                                    VTSS_D("VeriPHY %d%c: ", (int)tsk->port, (int)(tsk->subchan + 'A'));
                                    VTSS_D("sign-flip @ tap %d, strength = %d ", tsk->loc[(int)tsk->subchan], tsk->strength[(int)tsk->subchan]);
                                    //fprintf(fp,"Veriphy %d%c: sign-flip @ tap %d, strength = %d\n", (int)tsk->port, (int)(tsk->subchan + 'A'), tsk->loc[(int)tsk->subchan], tsk->strength[(int)tsk->subchan]);
                                }
                            }
                        } while (--cnt != 0);
                    }
                }                   /*- end for ( tsk->subchan = 0; tsk->subchan < 4; ++(tsk->subchan) ) */
                if (tsk->flags & 4) {
                    tsk->task_state = VERIPHY_STATE_GETCABLELEN_1;
                    VTSS_RC(vtss_phy_page_tr(vtss_state, tsk->port));
                    /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
                    if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, 1)); /*- EcVarForceDelay = 0, EcVarForceIdle = 1 */
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0b6/*0, 1, 1b*/, 0)); /*- EcVarForceIdle = 0 */
                    } else {
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0188/*0, 3, 4*/, 0)); /*- EcVarForceDelay = 0 */
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 1)); /*- EcVarForceIdle = 1 */
                        VTSS_RC(tr_raw_write(vtss_state, tsk->port, 0x0184/*0, 3, 2*/, 0)); /*- EcVarForceIdle = 0 */
                    }
                }
            } else {
                tsk->task_state = VERIPHY_STATE_GETCABLELEN_1;
            }
        }
        break;

    /*- getCableLength search state 2 */
    case VERIPHY_STATE_GETCABLELEN_1 :
        VTSS_D("VERIPHY_STATE_GET_CABLELEN_1");
        //**printf("VERIPHY_STATE_GET_CABLELEN_1\n");
        /*- Length estimate to be the average of medians of computed loc's */
        {
            u8 maxptr, minptr, max2ptr, min2ptr, endloc;

            max2ptr = min2ptr = endloc = 0;
            maxptr = minptr = 8;

            for (idx = 0; idx < 4; ++idx) {
                if (tsk->stat[idx] == 0 && tsk->loc[idx] < 255) {
                    short s;

                    if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                        getAnomThresh_65nm(tsk, tsk->loc[idx]);
                    } else {
                        get_anom_thresh(tsk, tsk->loc[idx]);
                    }

                    if (tsk->loc[idx] <= 8) {
                        s = 0;    /*- Don't change blips on <2m loops anomalous */
                        VTSS_D("VeriPHY %d%c: Don't Change! (s = %d )", tsk->port, idx + 'A', s);
                    } else if (tsk->flags & VERIPHY_FLAGS_LINKUP) { /*- if in link-up mode, ... */
                        s = (3 * tsk->strength[idx] + 2) >> 2;    /*- 3/4  of strength link-up */
                        VTSS_D("VeriPHY %d%c: LinkUP - 3/4 of Strength! (s = %d )", tsk->port, idx + 'A', s);
                    } else { /*- else in link-down mode */
                        s = (3 * tsk->strength[idx] + 16) >> 5;    /*- 3/32 of strength link-down */
                        VTSS_D("VeriPHY %d%c: LinkDN - 3/32 of Strength! (s = %d )", tsk->port, idx + 'A', s);
                    }

                    VTSS_D("VeriPHY %d%c: (s = %d > thresh[0]= %d)", tsk->port, idx + 'A', s, tsk->thresh[0]);
                    //**printf("VeriPHY %d%c: (s = %d > thresh[0]= %d) \n", tsk->port, idx + 'A', s, tsk->thresh[0]);

                    //if ((s > tsk->thresh[0]) || (s == 0)) {             // Changed_BY_JBH
                    if (s > tsk->thresh[0]) {
                        tsk->stat[idx] = VTSS_VERIPHY_STATUS_SHORT;
                        VTSS_D("VeriPHY %d%c: changing length (%d) to SHORT (%d > %d)!", tsk->port, idx + 'A', endloc, s, tsk->thresh[0]);
                        //**printf("VeriPHY %d%c: changing length (%d) to SHORT (%d > %d)!\n", tsk->port, idx + 'A', endloc, s, tsk->thresh[0]);
                    } else if (s < -tsk->thresh[0]) {
                        tsk->stat[idx] = VTSS_VERIPHY_STATUS_OPEN;
                        VTSS_D("VeriPHY %d%c: changing length (%d) to OPEN (%d < -%d)!", tsk->port, idx + 'A', endloc, s, tsk->thresh[0]);
                        //**printf("VeriPHY %d%c: changing length (%d) to OPEN (%d < -%d)!\n", tsk->port, idx + 'A', endloc, s, tsk->thresh[0]);
                    } else if (ABS(s) > tsk->thresh[1]) {
                        tsk->stat[idx] = VTSS_VERIPHY_STATUS_ABNORM;
                        VTSS_D("VeriPHY %d%c: changing length (%d) to ANOMOLY (ABS(%d) > %d)!", tsk->port, idx + 'A', endloc, s, tsk->thresh[1]);
                        //**printf("VeriPHY %d%c: changing length (%d) to ANOMOLY (ABS(%d) > %d)!\n", tsk->port, idx + 'A', endloc, s, tsk->thresh[1]);
                    } else if (((tsk->signFlip >> idx) & 1) == 0) { /*- if no sign flip detected, */
                        /* if (family == VTSS_PHY_FAMILY_MUSTANG)  */
                        if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                            tsk->loc[idx] = tsk->loc[idx] - 3;      /*- reduce estimated tap by 3 */
                        } else {
                            tsk->loc[idx] = tsk->loc[idx] - 1;      /*- reduce estimated tap by 1 */
                            VTSS_D("VeriPHY %d%c: (signFlip)", tsk->port, idx + 'A');
                        }
                    }

                    if (((tsk->flags & 8) == 0 || idx != ((tsk->flags >> 4) & 3)) && ((minptr >= 4) || (tsk->loc[idx] < tsk->loc[minptr]))) {
                        minptr = idx;
                    }
                    if (((tsk->flags & 8) == 0 || idx != ((tsk->flags >> 4) & 3)) && ((maxptr >= 4) || (tsk->loc[idx] > tsk->loc[maxptr]))) {
                        maxptr = idx;
                    }
                    VTSS_D("subchan %c, loc = %d, minptr: %d, maxptr: %d", idx + 'A', tsk->loc[idx], minptr, maxptr);
                    //**printf("subchan %c, loc = %d, minptr: %d, maxptr: %d\n", idx + 'A', tsk->loc[idx], minptr, maxptr);
                }
            } /*- End of For Loop */

            if (minptr == 8) {
                /*- Only use unreliablePtr length as a last resort */
                if (tsk->flags & 8) {
                    endloc = tsk->loc[(tsk->flags >> 4) & 3];
                    VTSS_D("VeriPHY %d: unreliable endloc = %d is only available!", tsk->port, endloc);
                } else {
                    endloc = 255;
                    VTSS_D("VeriPHY %d: No length (endloc = 255) is available!", tsk->port);
                }
            } else {
                /*- Rehabilitate the unreliablePtr if result is reasonable before median search */
                if ((tsk->flags & 8) && tsk->loc[(tsk->flags >> 4) & 3] >= (tsk->loc[minptr] - 1)) {
                    if (tsk->loc[(tsk->flags >> 4) & 3] == (tsk->loc[minptr] - 1)) {
                        minptr = (tsk->flags >> 4) & 3;
                        tsk->flags &= ~8;
                    } else if (tsk->loc[(tsk->flags >> 4) & 3] <= (tsk->loc[maxptr] + 1)) {
                        if (tsk->loc[(tsk->flags >> 4) & 3] == (tsk->loc[maxptr] + 1)) {
                            maxptr = (tsk->flags >> 4) & 3;
                        }
                        tsk->flags &= ~8;
                    }
                }

                /*- Find the middle 2 results (may point to the same item, min, or max) */
                min2ptr = maxptr;
                max2ptr = minptr;
                for (idx = 0; idx < 4; ++idx) {
                    if (tsk->stat[idx] == 0 && tsk->loc[idx] < 255 && ((tsk->flags & 8) == 0 || idx != ((tsk->flags >> 4) & 3))) {
                        if ((idx != minptr) && (tsk->loc[idx] < tsk->loc[min2ptr])) {
                            min2ptr = idx;
                        }
                        if ((idx != maxptr) && (tsk->loc[idx] > tsk->loc[max2ptr])) {
                            max2ptr = idx;
                        }
                    }
                }

                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    endloc = (max2ptr == minptr) ? tsk->loc[maxptr] : tsk->loc[max2ptr];
                } else {
                    endloc = (max2ptr == minptr) ? tsk->loc[maxptr] : (u8)(((u32)tsk->loc[min2ptr] + tsk->loc[max2ptr]) >> 1);
                }
                VTSS_D("VeriPHY %d: max/minptr = %d/%d, max2/min2ptr = %d/%d, endloc = %d! ",
                       tsk->port, maxptr, minptr, max2ptr, min2ptr, endloc);
            }

            for (idx = 0; idx < 4; ++idx) {
                if (tsk->stat[idx] == 0) {
                    VTSS_D("VeriPHY loc[%d] = %d --> %d", idx, tsk->loc[idx], endloc);
                    //**printf("VeriPHY loc[%d] = %d --> %d\n", idx, tsk->loc[idx], endloc);
                    tsk->loc[idx] = endloc;
                }
            }
            tsk->task_state = VERIPHY_STATE_PAIRSWAP;
        }
        break;

    /*- PairSwap & VeriPHY finish-up state */
    case VERIPHY_STATE_PAIRSWAP :
        VTSS_D("VERIPHY_STATE_PAIRSWAP");
        /*- Swap pairs as appropriate to represent pairs at connector */
        /*- (up to now, it was subchan) */
        VTSS_D("VeriPHY swapPairs");
        {
            i8 MDIX_CDpairSwap;
            u8 ubtemp;
            short stemp;

            /*- Read MDI/MDIX, bit[1], and CD-pair-swap, bit [0] */
            MDIX_CDpairSwap = MiiReadBits(vtss_state, tsk->port, 28, 13, 12 );

            VTSS_D("VERIPHY_STATE_PAIRSWAP: MDIX_CDPairSwap: x%x", MDIX_CDpairSwap);

            if (MDIX_CDpairSwap < 2) {
                /*- Swap pairs A & B */
                stemp            = tsk->strength[1];
                tsk->strength[1] = tsk->strength[0];
                tsk->strength[0] = stemp;
                ubtemp           = tsk->stat[1];
                tsk->stat[1]     = tsk->stat[0];
                tsk->stat[0]     = ubtemp;
                ubtemp           = tsk->loc[1];
                tsk->loc[1]      = tsk->loc[0];
                tsk->loc[0]      = ubtemp;

                /*- Recode cross-pair status for pairs A & B */
                for (idx = 0; idx < 4; ++idx) {
                    if ( (tsk->stat[idx] & 10) == 8 ) {
                        tsk->stat[idx] = tsk->stat[idx] ^ 1;
                    }
                }
            }

            /*- AB Pair swap or CD Pair Swap */
            if ((MDIX_CDpairSwap == 0) || (MDIX_CDpairSwap == 3)) {
                /*- Swap pairs C & D */
                stemp            = tsk->strength[3];
                tsk->strength[3] = tsk->strength[2];
                tsk->strength[2] = stemp;
                ubtemp           = tsk->stat[3];
                tsk->stat[3]     = tsk->stat[2];
                tsk->stat[2]     = ubtemp;
                ubtemp           = tsk->loc[3];
                tsk->loc[3]      = tsk->loc[2];
                tsk->loc[2]      = ubtemp;

                /*- Recode cross-pair status for pairs C & D */
                for (idx = 0; idx < 4; ++idx) {
                    if ( (tsk->stat[idx] & 10) == 10 ) {
                        tsk->stat[idx] = tsk->stat[idx] ^ 1;
                    }
                }
            }
        }

        /*- There is a difference in Tap scaling between 130nm and 65nm products */
        /*- 130nm: Convert tap numbers into length in meters for return to user */
        /*- 65nm: Convert tap numbers into length in 3-meter increments for return to user */
        for (idx = 0; idx < 4; ++idx) {
            u8 loc = tsk->loc[idx];
            VTSS_D("Tap Location - loc[%d] = %d ", idx, tsk->loc[idx]);

            if (loc <= 7) {
                tsk->loc[idx] = 0;
            } else if (loc < 255) {
                /*- Initial taps that are close to zero, differing FFE spreading effects, */
                /*- scale factor is slightly different in Mustang */
                if (VTSS_PHY_1_GEN_DSP(tsk->port)) {
                    if (tsk->flags & VERIPHY_FLAGS_LINKUP) {
                        if (family == VTSS_PHY_FAMILY_MUSTANG) {
                            loc -= 13;
                        } else {
                            loc -= 7;
                        }
                    } else {
                        loc -= 7;
                    }
                } else {
                    if (tsk->flags & VERIPHY_FLAGS_LINKUP) {
                        loc -= 7; /*- Fudge Factor, Zero Location, Re-Alignment of Zero Meter Location */
                    } else {
                        loc -= 6; /*- Fudge Factor, Zero Location, Re-Alignment of Zero Meter Location */
                    }
                }

                //printf("Tap Location - loc= %d\n", loc);
                //fprintf(fp,"Tap Location - loc= %d\n", loc);
                /*- The following is different than what was found in embedded func */
                if (VTSS_PHY_GEN_2_DSP(tsk->port)) {
                    loc = ((loc >> 1) + (loc >> 4) + (loc >> 6) + 1) >> 1;  // This is just a divide by 3
                    //fprintf(fp,"- loc= %d\n", loc);
                    if (loc > 62) {
                        tsk->loc[idx] = 62;  // 62 * 3 = 186 meters; 63 = NOT_A_LOCATION, largest number less than 63
                    } else {
                        tsk->loc[idx] = loc;
                    }
                } else {
                    loc = loc - ((((loc + (loc >> 4)) >> 2) + 1) >> 1);
                    tsk->loc[idx] = loc;

                    if ((tsk->stat[idx] == 2) && (loc < 5)) {
                        tsk->stat[idx] = 4;
                    }
                }
            }
        }

        for (idx = 0; idx < 4; ++idx) {
            VTSS_D("Location/Status/Strength - Index = %d, loc = %d, 3xloc: %d, stat = %d, strength = %d", idx,
                   tsk->loc[idx], tsk->loc[idx] * 3, tsk->stat[idx], tsk->strength[idx]);
        }

        tsk->task_state = VERIPHY_STATE_FINISH;
        break;
    }

    if (tsk->task_state == VERIPHY_STATE_IDLE) { /*- also covers FINISH state */
        VTSS_D("<--- Cancelling Timer - VeriPHY state of port %d is: 0x%02x", tsk->port, tsk->task_state);
        MEPA_MTIMER_CANCEL(&tsk->timeout);
    }

    VTSS_D("<--- EXIT VeriPHY state of port %d is: 0x%02x", tsk->port, tsk->task_state);
    VTSS_D("<--- VeriPHY Return Status is: %d",  (tsk->task_state == VERIPHY_STATE_IDLE) ? VTSS_RC_OK : VTSS_RC_INCOMPLETE);

    return (tsk->task_state == VERIPHY_STATE_IDLE) ? VTSS_RC_OK : VTSS_RC_INCOMPLETE;
}

#endif /* VTSS_PHY_OPT_VERIPHY */
#endif // VTSS_CHIP_CU_PHY
