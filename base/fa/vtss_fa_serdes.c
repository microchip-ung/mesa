/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_fa_cil.h"
#include "vtss_fa_sd10g28_setup.h"
#include "vtss_fa_sd25g28_setup.h"

#if defined(VTSS_ARCH_FA)

u32 vtss_to_sd6g_lane(u32 indx)
{
    switch (indx) {
    case 0:  return VTSS_TO_SD6G_LANE_0;
    case 1:  return VTSS_TO_SD6G_LANE_1;
    case 2:  return VTSS_TO_SD6G_LANE_2;
    case 3:  return VTSS_TO_SD6G_LANE_3;
    case 4:  return VTSS_TO_SD6G_LANE_4;
    case 5:  return VTSS_TO_SD6G_LANE_5;
    case 6:  return VTSS_TO_SD6G_LANE_6;
    case 7:  return VTSS_TO_SD6G_LANE_7;
    case 8:  return VTSS_TO_SD6G_LANE_8;
    case 9:  return VTSS_TO_SD6G_LANE_9;
    case 10: return VTSS_TO_SD6G_LANE_10;
    case 11: return VTSS_TO_SD6G_LANE_11;
    case 12: return VTSS_TO_SD6G_LANE_12;
    default:
        VTSS_E("illegal 6G_lane index %d",indx);
        return 0;
    }
}

u32 vtss_to_sd10g_lane(u32 indx)
{
    switch (indx) {
    case 0:  return VTSS_TO_SD10G_LANE_0;
    case 1:  return VTSS_TO_SD10G_LANE_1;
    case 2:  return VTSS_TO_SD10G_LANE_2;
    case 3:  return VTSS_TO_SD10G_LANE_3;
    case 4:  return VTSS_TO_SD10G_LANE_4;
    case 5:  return VTSS_TO_SD10G_LANE_5;
    case 6:  return VTSS_TO_SD10G_LANE_6;
    case 7:  return VTSS_TO_SD10G_LANE_7;
    case 8:  return VTSS_TO_SD10G_LANE_8;
    case 9:  return VTSS_TO_SD10G_LANE_9;
    case 10: return VTSS_TO_SD10G_LANE_10;
    case 11: return VTSS_TO_SD10G_LANE_11;
    default:
        VTSS_E("illegal 10G_lane index %d",indx);
        return 0;
    }

}

u32 vtss_to_sd25g_lane(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD25G_LANE_0;
    case 1: return VTSS_TO_SD25G_LANE_1;
    case 2: return VTSS_TO_SD25G_LANE_2;
    case 3: return VTSS_TO_SD25G_LANE_3;
    case 4: return VTSS_TO_SD25G_LANE_4;
    case 5: return VTSS_TO_SD25G_LANE_5;
    case 6: return VTSS_TO_SD25G_LANE_6;
    case 7: return VTSS_TO_SD25G_LANE_7;
    default:
        VTSS_E("illegal 25G_lane index %d",indx);
        return 0;
    }
}

u32 vtss_to_sd_cmu(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD_CMU_0;
    case 1: return VTSS_TO_SD_CMU_1;
    case 2: return VTSS_TO_SD_CMU_2;
    case 3: return VTSS_TO_SD_CMU_3;
    case 4: return VTSS_TO_SD_CMU_4;
    case 5: return VTSS_TO_SD_CMU_5;
    case 6: return VTSS_TO_SD_CMU_6;
    case 7: return VTSS_TO_SD_CMU_7;
    case 8: return VTSS_TO_SD_CMU_8;
    case 9: return VTSS_TO_SD_CMU_9;
    case 10: return VTSS_TO_SD_CMU_10;
    case 11: return VTSS_TO_SD_CMU_11;
    case 12: return VTSS_TO_SD_CMU_12;
    case 13: return VTSS_TO_SD_CMU_13;
    default:
        VTSS_E("illegal sd_cmu index %d",indx);
        return 0;
    }
}

u32 vtss_to_sd_cmu_cfg(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD_CMU_CFG_0;
    case 1: return VTSS_TO_SD_CMU_CFG_1;
    case 2: return VTSS_TO_SD_CMU_CFG_2;
    case 3: return VTSS_TO_SD_CMU_CFG_3;
    case 4: return VTSS_TO_SD_CMU_CFG_4;
    case 5: return VTSS_TO_SD_CMU_CFG_5;
    case 6: return VTSS_TO_SD_CMU_CFG_6;
    case 7: return VTSS_TO_SD_CMU_CFG_7;
    case 8: return VTSS_TO_SD_CMU_CFG_8;
    case 9: return VTSS_TO_SD_CMU_CFG_9;
    case 10: return VTSS_TO_SD_CMU_CFG_10;
    case 11: return VTSS_TO_SD_CMU_CFG_11;
    case 12: return VTSS_TO_SD_CMU_CFG_12;
    case 13: return VTSS_TO_SD_CMU_CFG_13;
    default:
        VTSS_E("illegal sd_cmu index %d",indx);
        return 0;
    }
}

u32 vtss_to_sd_lane(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD_LANE_0;
    case 1: return VTSS_TO_SD_LANE_1;
    case 2: return VTSS_TO_SD_LANE_2;
    case 3: return VTSS_TO_SD_LANE_3;
    case 4: return VTSS_TO_SD_LANE_4;
    case 5: return VTSS_TO_SD_LANE_5;
    case 6: return VTSS_TO_SD_LANE_6;
    case 7: return VTSS_TO_SD_LANE_7;
    case 8: return VTSS_TO_SD_LANE_8;
    case 9: return VTSS_TO_SD_LANE_9;
    case 10: return VTSS_TO_SD_LANE_10;
    case 11: return VTSS_TO_SD_LANE_11;
    case 12: return VTSS_TO_SD_LANE_12;
    case 13: return VTSS_TO_SD_LANE_13;
    case 14: return VTSS_TO_SD_LANE_14;
    case 15: return VTSS_TO_SD_LANE_15;
    case 16: return VTSS_TO_SD_LANE_16;
    case 17: return VTSS_TO_SD_LANE_17;
    case 18: return VTSS_TO_SD_LANE_18;
    case 19: return VTSS_TO_SD_LANE_19;
    case 20: return VTSS_TO_SD_LANE_20;
    case 21: return VTSS_TO_SD_LANE_21;
    case 22: return VTSS_TO_SD_LANE_22;
    case 23: return VTSS_TO_SD_LANE_23;
    case 24: return VTSS_TO_SD_LANE_24;
    case 25: return VTSS_TO_SD_LANE_25;
    case 26: return VTSS_TO_SD_LANE_26;
    case 27: return VTSS_TO_SD_LANE_27;
    case 28: return VTSS_TO_SD_LANE_28;
    case 29: return VTSS_TO_SD_LANE_29;
    case 30: return VTSS_TO_SD_LANE_30;
    case 31: return VTSS_TO_SD_LANE_31;
    case 32: return VTSS_TO_SD_LANE_32;
    default:
        VTSS_E("illegal sd_lane index %d",indx);
        return 0;
    }
}

u32 vtss_fa_sd10g28_get_cmu (vtss_state_t *vtss_state, vtss_sd10g28_cmu_t cmu_type, vtss_port_no_t port_no) {

    u32 serdes_no;
    u32 sd_type;

    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &serdes_no, &sd_type));

    if (cmu_type == 0) {
        // Main CMU of FA
        if (serdes_no < 8 ) {
            return 2;
        } else if (serdes_no < 16 ) {
            return 5;
        } else if (serdes_no == 16) {
            return 8;
        } else {
            return 11;
        }
    } else if ( cmu_type == 1) {
        // AUX1 CMU of FA
        if (serdes_no < 2 ) {
            return 0;
        } else if (serdes_no < 10 ) {
            return 3;
        } else if (serdes_no < 16) {
            return 6;
        } else if (serdes_no < 19) {
            return 9;
        } else {
            return 12;
        }
    } else {
        // AUX2 CMU of FA
        if (serdes_no < 4 ) {
            return 1;
        } else if (serdes_no < 12 ) {
            return 4;
        } else if (serdes_no < 17) {
            return 7;
        } else if (serdes_no < 21) {
            return 10;
        } else {
            return 13;
        }
    }
}

#define FA_DEBUG_LANE(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_SD10G_LANE_TARGET_LANE_##addr, i,\
(sd_type == FA_SERDES_TYPE_10G) ? "VTSS_SD10G_LANE_TARGET_LANE_"name : "VTSS_SD6G_LANE_TARGET_LANE_"name)
#define FA_DEBUG_25G_LANE(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_SD25G_TARGET_CMU_##addr, i, "VTSS_SD25G_TARGET_CMU_"name)

vtss_rc fa_debug_chip_serdes(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info,
                             vtss_port_no_t port_no)
{

    u32  sd_type, indx, sd_tgt;

    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &sd_type));

    if (sd_type == FA_SERDES_TYPE_6G) {
        sd_tgt = VTSS_TO_SD6G_LANE(indx);
    } else if (sd_type == FA_SERDES_TYPE_10G) {
        sd_tgt = VTSS_TO_SD10G_LANE(indx);
    } else {
        sd_tgt = VTSS_TO_SD25G_LANE(indx);
    }

    if (sd_type == FA_SERDES_TYPE_25G) {
        FA_DEBUG_25G_LANE(pr, FF(sd_tgt), indx, "FF");
        FA_DEBUG_25G_LANE(pr, 31(sd_tgt), indx, "31");
        FA_DEBUG_25G_LANE(pr, 1A(sd_tgt), indx, "1A");
        FA_DEBUG_25G_LANE(pr, 40(sd_tgt), indx, "40");
        FA_DEBUG_25G_LANE(pr, 46(sd_tgt), indx, "46");
        FA_DEBUG_25G_LANE(pr, 45(sd_tgt), indx, "45");
        FA_DEBUG_25G_LANE(pr, 0B(sd_tgt), indx, "0B");
        FA_DEBUG_25G_LANE(pr, 19(sd_tgt), indx, "19");
        FA_DEBUG_25G_LANE(pr, 18(sd_tgt), indx, "18");
        FA_DEBUG_25G_LANE(pr, 1A(sd_tgt), indx, "1A");
        FA_DEBUG_25G_LANE(pr, 30(sd_tgt), indx, "30");
        FA_DEBUG_25G_LANE(pr, 0C(sd_tgt), indx, "0C");
        FA_DEBUG_25G_LANE(pr, 0D(sd_tgt), indx, "0D");
        FA_DEBUG_25G_LANE(pr, 0E(sd_tgt), indx, "0E");
        FA_DEBUG_25G_LANE(pr, 01(sd_tgt), indx, "01");
        FA_DEBUG_25G_LANE(pr, 18(sd_tgt), indx, "18");
        FA_DEBUG_25G_LANE(pr, 2C(sd_tgt), indx, "2C");
        FA_DEBUG_25G_LANE(pr, 28(sd_tgt), indx, "28");
        FA_DEBUG_25G_LANE(pr, 01(sd_tgt), indx, "01");
        FA_DEBUG_25G_LANE(pr, 0F(sd_tgt), indx, "0F");
        FA_DEBUG_25G_LANE(pr, 1D(sd_tgt), indx, "1D");
        FA_DEBUG_25G_LANE(pr, 19(sd_tgt), indx, "19");
        FA_DEBUG_25G_LANE(pr, 01(sd_tgt), indx, "01");
        FA_DEBUG_25G_LANE(pr, 03(sd_tgt), indx, "03");
        FA_DEBUG_25G_LANE(pr, 06(sd_tgt), indx, "06");
        FA_DEBUG_25G_LANE(pr, 07(sd_tgt), indx, "07");
        FA_DEBUG_25G_LANE(pr, 43(sd_tgt), indx, "43");
        FA_DEBUG_25G_LANE(pr, 43(sd_tgt), indx, "42");
        FA_DEBUG_25G_LANE(pr, 05(sd_tgt), indx, "05");
        FA_DEBUG_25G_LANE(pr, 0A(sd_tgt), indx, "0A");
        FA_DEBUG_25G_LANE(pr, 09(sd_tgt), indx, "09");
        FA_DEBUG_25G_LANE(pr, 1B(sd_tgt), indx, "09");
        FA_DEBUG_25G_LANE(pr, 2E(sd_tgt), indx, "2E");
        FA_DEBUG_25G_LANE(pr, 44(sd_tgt), indx, "44");
        FA_DEBUG_25G_LANE(pr, 22(sd_tgt), indx, "22");
        FA_DEBUG_25G_LANE(pr, 1C(sd_tgt), indx, "1C");
        FA_DEBUG_25G_LANE(pr, 1E(sd_tgt), indx, "1E");
        FA_DEBUG_25G_LANE(pr, 25(sd_tgt), indx, "25");
        FA_DEBUG_25G_LANE(pr, 26(sd_tgt), indx, "26");
        FA_DEBUG_25G_LANE(pr, 18(sd_tgt), indx, "18");
        FA_DEBUG_25G_LANE(pr, 40(sd_tgt), indx, "40");
        FA_DEBUG_25G_LANE(pr, 04(sd_tgt), indx, "04");
        FA_DEBUG_25G_LANE(pr, 1E(sd_tgt), indx, "1E");
        FA_DEBUG_25G_LANE(pr, 2E(sd_tgt), indx, "2E");
        FA_DEBUG_25G_LANE(pr, 1C(sd_tgt), indx, "1C");
        FA_DEBUG_25G_LANE(pr, C0(sd_tgt), indx, "C0");

    } else {

        FA_DEBUG_LANE(pr, 93(sd_tgt), indx, "93");
        FA_DEBUG_LANE(pr, 94(sd_tgt), indx, "94");
        FA_DEBUG_LANE(pr, 9E(sd_tgt), indx, "9E");
        FA_DEBUG_LANE(pr, A1(sd_tgt), indx, "A1");
        FA_DEBUG_LANE(pr, 50(sd_tgt), indx, "50");
        FA_DEBUG_LANE(pr, 35(sd_tgt), indx, "35");
        FA_DEBUG_LANE(pr, 01(sd_tgt), indx, "01");
        FA_DEBUG_LANE(pr, 30(sd_tgt), indx, "30");
        FA_DEBUG_LANE(pr, A2(sd_tgt), indx, "A2");
        FA_DEBUG_LANE(pr, 13(sd_tgt), indx, "13");
        FA_DEBUG_LANE(pr, 23(sd_tgt), indx, "23");
        FA_DEBUG_LANE(pr, 22(sd_tgt), indx, "22");
        FA_DEBUG_LANE(pr, 1A(sd_tgt), indx, "1A");
        FA_DEBUG_LANE(pr, 02(sd_tgt), indx, "02");
        FA_DEBUG_LANE(pr, 03(sd_tgt), indx, "03");
        FA_DEBUG_LANE(pr, 04(sd_tgt), indx, "04");
        FA_DEBUG_LANE(pr, 2F(sd_tgt), indx, "2F");
        FA_DEBUG_LANE(pr, 0B(sd_tgt), indx, "0B");
        FA_DEBUG_LANE(pr, 0D(sd_tgt), indx, "0D");
        FA_DEBUG_LANE(pr, 0E(sd_tgt), indx, "0E");
        FA_DEBUG_LANE(pr, 23(sd_tgt), indx, "23");
        FA_DEBUG_LANE(pr, 06(sd_tgt), indx, "06");
        FA_DEBUG_LANE(pr, 33(sd_tgt), indx, "33");
        FA_DEBUG_LANE(pr, 52(sd_tgt), indx, "52");
        FA_DEBUG_LANE(pr, 37(sd_tgt), indx, "37");
        FA_DEBUG_LANE(pr, 3C(sd_tgt), indx, "3C");
        FA_DEBUG_LANE(pr, 39(sd_tgt), indx, "39");
        FA_DEBUG_LANE(pr, 1A(sd_tgt), indx, "1A");
        FA_DEBUG_LANE(pr, 16(sd_tgt), indx, "16");
        FA_DEBUG_LANE(pr, 15(sd_tgt), indx, "15");
        FA_DEBUG_LANE(pr, 26(sd_tgt), indx, "26");
        FA_DEBUG_LANE(pr, 42(sd_tgt), indx, "42");
        FA_DEBUG_LANE(pr, 0F(sd_tgt), indx, "0F");
        FA_DEBUG_LANE(pr, 24(sd_tgt), indx, "24");
        FA_DEBUG_LANE(pr, 14(sd_tgt), indx, "14");
        FA_DEBUG_LANE(pr, 3A(sd_tgt), indx, "3A");
        FA_DEBUG_LANE(pr, 31(sd_tgt), indx, "31");
        FA_DEBUG_LANE(pr, 48(sd_tgt), indx, "48");
        FA_DEBUG_LANE(pr, 36(sd_tgt), indx, "36");
        FA_DEBUG_LANE(pr, 32(sd_tgt), indx, "32");
        FA_DEBUG_LANE(pr, 37(sd_tgt), indx, "37");
        FA_DEBUG_LANE(pr, 41(sd_tgt), indx, "41");
        FA_DEBUG_LANE(pr, 9E(sd_tgt), indx, "9E");
        FA_DEBUG_LANE(pr, 0C(sd_tgt), indx, "0C");
        FA_DEBUG_LANE(pr, 0B(sd_tgt), indx, "0B");
        FA_DEBUG_LANE(pr, 83(sd_tgt), indx, "83");
        FA_DEBUG_LANE(pr, 06(sd_tgt), indx, "06");
        FA_DEBUG_LANE(pr, 9E(sd_tgt), indx, "9E");
        FA_DEBUG_LANE(pr, 83(sd_tgt), indx, "83");
        FA_DEBUG_LANE(pr, 50(sd_tgt), indx, "50");
        FA_DEBUG_LANE(pr, 34(sd_tgt), indx, "34");
    }
    return VTSS_RC_OK;
}


vtss_rc vtss_fa_port2sd(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *sd_indx, u32 *sd_type)
{
    u32 p = VTSS_CHIP_PORT(port_no);

    switch (vtss_state->port.conf[port_no].if_type) {
    case VTSS_PORT_INTERFACE_QSGMII:
        if (p <= 47) {
            u32 Q = (p -  p % 4) / 4;
            *sd_indx = Q;
            *sd_type = FA_SERDES_TYPE_10G;
            VTSS_D("(Q QUAD 1G SD) QSGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
        }
        break;
    case VTSS_PORT_INTERFACE_USGMII:
        if (p <= 47) {
            u32 X = (p - p % 8) / 8;
            *sd_indx = X + 4;
            *sd_type = FA_SERDES_TYPE_10G;
            VTSS_D("(X OCTAL 1G SD) USGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
        }
        break;
    case VTSS_PORT_INTERFACE_QXGMII: /* QXGMII:    4x2G5 devices. Mode 'R'. */
        if (p <= 63) {
            int R = (p < 16) ? p : (p < 32) ? p - 16 : (p < 48) ? p - 32 : p - 48;
            if (R < 8) {
                *sd_indx = R + 4;
                *sd_type = FA_SERDES_TYPE_10G;
                VTSS_D("(R QUAD 2G5 SD) 10USXGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
            } else {
                *sd_indx = R - 8;
                *sd_type = FA_SERDES_TYPE_25G;
                VTSS_D("(R QUAD 2G5 SD) 10USXGMII p:%d SD25G_LANE index: %d",p, *sd_indx);
            }
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: /* DXGMII_10G: 2x5G devices. Mode 'U'.*/
        if (p <= 63 && (p <= 15 || p >= 48)) {
            int U = (p < 16) ? p : p - 48;
            if (U < 8) {
                *sd_indx = U + 4;
                *sd_type = FA_SERDES_TYPE_10G;
                VTSS_D("(U DUAL 5G SD) 10USXGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
            } else {
                *sd_indx = U - 8;
                *sd_type = FA_SERDES_TYPE_25G;
                VTSS_D("(U DUAL 5G SD) 10USXGMII p:%d SD25G_LANE index: %d",p, *sd_indx);
            }
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_5G: /* DXGMII_5G: 2x2G5 devices. Mode 'F'.*/
        if (p <= 63) {
            int F = (p < 32) ? p :  p - 32;
            if (F < 12) {
                *sd_indx = F + 1;
                *sd_type = FA_SERDES_TYPE_6G;
                VTSS_D("(F DUAL 2G5 SD) 5USXGMII p:%d SD6G_LANE index: %d",p, *sd_indx);
            } else if (F < 24) {
                *sd_indx = F - 12;
                *sd_type = FA_SERDES_TYPE_10G;
                VTSS_D("(F DUAL 2G5 SD) 5USXGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
            } else {
                *sd_indx = F - 24;
                *sd_type = FA_SERDES_TYPE_25G;
                VTSS_D("(F DUAL 2G5 SD) 5USXGMII p:%d SD25G_LANE index: %d",p, *sd_indx);
            }
        }
        break;
    default:
        if (p < 12) {
            *sd_indx = p + 1;
            *sd_type = FA_SERDES_TYPE_6G;
            VTSS_D("Single Serdes p:%d SD6G_LANE index: %d",p, *sd_indx);
            return VTSS_TO_SD6G_LANE(p + 1);
        } else if (p >= 12 && p < 16) {
            *sd_indx = p - 12;
            *sd_type = FA_SERDES_TYPE_10G;
            VTSS_D("Single Serdes p:%d SD10_LANE index: %d",p, *sd_indx);
        } else if (p >= 48 && p < 56) {
            *sd_indx = p - 44;
            *sd_type = FA_SERDES_TYPE_10G;
            VTSS_D("Single Serdes p:%d SD10_LANE index: %d",p, *sd_indx);
        } else if (p >= 56 && p < 64) {
            *sd_indx = p - 56;
            *sd_type = FA_SERDES_TYPE_25G;
            VTSS_D("Single Serdes p:%d SD25_LANE index: %d",p, *sd_indx);
        } else if (p == 64) {
            *sd_indx = 0;
            *sd_type = FA_SERDES_TYPE_6G;
            VTSS_D("Single Serdes p:%d SD6G_LANE index: %d",p, *sd_indx);
        } else {
            VTSS_E("illegal port/interface mode");
            return VTSS_RC_ERROR;
        }
    }
    return VTSS_RC_OK;
}

/* Returns index 0-12 for 6G ports  */
/* Returns index 0-11 for 10G ports */
/* Returns index 0-7  for 25G ports  */
u32 vtss_fa_port2sd_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 sd_indx = 0, sd_type;
    (void)vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type);
    return sd_indx;
}


static vtss_sd10g28_preset_t serdes2preset(vtss_serdes_mode_t m)
{
    switch (m) {
    case VTSS_SD10G_MEDIA_SR:     return(VTSS_SD10G28_SR);
    case VTSS_SD10G_MEDIA_ZR:     return(VTSS_SD10G28_ZR);
    case VTSS_SD10G_MEDIA_DAC:    return(VTSS_SD10G28_DAC3M);
    case VTSS_SD10G_MEDIA_DAC_5M: return(VTSS_SD10G28_DAC5M);
    case VTSS_SD10G_MEDIA_BP:     return(VTSS_SD10G28_KR);
    case VTSS_SD10G_MEDIA_B2B:    return(VTSS_SD10G28_KR);
    case VTSS_SD10G_MEDIA_10G_KR: return(VTSS_SD10G28_KR);
    default:
    return(VTSS_SD10G28_PRESET_NONE);
    }
}

static vtss_rc fa_sd25g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_serdes_mode_t mode)
{
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;
    vtss_sd25g28_setup_args_t sd_cfg = {0};

    sd_cfg.chip_name = VTSS_SD25G28_CHIP_ANT;
    sd_cfg.txinvert = 0;
    sd_cfg.rxinvert = 1;
    sd_cfg.txswing = 240;
    sd_cfg.reg_ctrl = 1;

     /* Apply the serdes mode */
    switch (mode) {
        case VTSS_SERDES_MODE_IDLE:
        case VTSS_SERDES_MODE_SFI_DAC:
        case VTSS_SERDES_MODE_SFI_SR:
        case VTSS_SERDES_MODE_SFI_ZR:
        case VTSS_SERDES_MODE_SFI_BP:
        case VTSS_SERDES_MODE_SFI_B2B:
        case VTSS_SERDES_MODE_SFI_PR_NONE:
        case VTSS_SERDES_MODE_SFI_KR:
        case VTSS_SERDES_MODE_SFI: {
            if (speed == VTSS_SPEED_25G) {
                sd_cfg.mode = VTSS_SD25G28_MODE_25G_LAN;
            } else if (speed == VTSS_SPEED_10G) {
                sd_cfg.mode = VTSS_SD25G28_MODE_10G_LAN;
            } else if (speed == VTSS_SPEED_5G) {
                sd_cfg.mode = VTSS_SD25G28_MODE_5G_LAN;
            } else {
                VTSS_E("Illegal speed");
            }
            break;
        }
        case VTSS_SERDES_MODE_USXGMII: {
            if (speed == VTSS_SPEED_10G) {
                sd_cfg.mode = VTSS_SD25G28_MODE_10G_DSXGMII;
            } else if (speed == VTSS_SPEED_5G) {
                sd_cfg.mode = VTSS_SD25G28_MODE_5G_USXGMII;
            }
            break;
        }
        case VTSS_SERDES_MODE_2G5: {
            sd_cfg.mode = VTSS_SD25G28_MODE_SGMII2G5;
            break;
        }
        case VTSS_SERDES_MODE_SGMII:
        case VTSS_SERDES_MODE_1000BaseX: {
            sd_cfg.mode = VTSS_SD25G28_MODE_SGMII;
            break;
        }

        case VTSS_SERDES_MODE_QSGMII: {
            sd_cfg.mode = VTSS_SD25G28_MODE_10G_QSXGMII;
            break;
        }
        case VTSS_SERDES_MODE_100FX: {
            sd_cfg.mode = VTSS_SD25G28_MODE_FX100;
            break;
        }
        default: {
            VTSS_E("Serdes mode (%d) not supported",mode);
            return VTSS_RC_ERROR;
        }
    }

    if (vtss_ant_sd25g28_setup_lane(vtss_state, sd_cfg, port_no) != VTSS_RC_OK) {
        VTSS_E("Could not configure Serdes mode (%d) at port:%d",mode,port_no);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_sd10g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no,  vtss_serdes_mode_t mode, u32 sd_type)
{
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;
    vtss_sd10g28_setup_args_t sd_cfg = {0};

    sd_cfg.chip_name = VTSS_SD10G28_CHIP_ANT;
    sd_cfg.is_6g =  sd_type == FA_SERDES_TYPE_6G ? TRUE : FALSE;
    sd_cfg.txinvert = 0;
    sd_cfg.rxinvert = 1;
    sd_cfg.txswing = 240;
    sd_cfg.preset = VTSS_SD10G28_PRESET_NONE;

    /* Apply the serdes mode */
    switch (mode) {
        case VTSS_SERDES_MODE_IDLE:
        case VTSS_SERDES_MODE_SFI_DAC:
        case VTSS_SERDES_MODE_SFI_SR:
        case VTSS_SERDES_MODE_SFI_ZR:
        case VTSS_SERDES_MODE_SFI_BP:
        case VTSS_SERDES_MODE_SFI_B2B:
        case VTSS_SERDES_MODE_SFI_PR_NONE:
        case VTSS_SERDES_MODE_SFI_KR:
        case VTSS_SERDES_MODE_SFI: {
            sd_cfg.preset = serdes2preset(vtss_state->port.conf[port_no].serdes.media_type);
            if (speed == VTSS_SPEED_10G) {
                sd_cfg.mode = VTSS_SD10G28_MODE_10G_LAN;
                 } else if (speed == VTSS_SPEED_5G) {
                sd_cfg.mode = VTSS_SD10G28_MODE_5G_LAN;
            } else {
                VTSS_E("Illegal speed");
            }
            break;
        }
        case VTSS_SERDES_MODE_2G5: {
            sd_cfg.mode = VTSS_SD10G28_MODE_SGMII2G5;
            break;
        }
        case VTSS_SERDES_MODE_SGMII:
        case VTSS_SERDES_MODE_1000BaseX: {
            sd_cfg.mode = VTSS_SD10G28_MODE_SGMII;
            break;
        }
        case VTSS_SERDES_MODE_USXGMII: {
            if (speed == VTSS_SPEED_10G) {
                sd_cfg.mode = VTSS_SD10G28_MODE_10G_DSXGMII;
            } else if (speed == VTSS_SPEED_5G) {
                sd_cfg.mode = VTSS_SD10G28_MODE_5G_USXGMII;
            }
            break;
        }
        case VTSS_SERDES_MODE_USGMII: {
            sd_cfg.mode = VTSS_SD10G28_MODE_10G_USGMII;
            break;
        }
        case VTSS_SERDES_MODE_QSGMII: {
            sd_cfg.mode = VTSS_SD10G28_MODE_QSGMII;
            break;
        }
        case VTSS_SERDES_MODE_100FX: {
            sd_cfg.mode = VTSS_SD10G28_MODE_FX100;
            break;
        }
        default: {
            VTSS_E("Serdes mode (%d) not supported",mode);
            return VTSS_RC_ERROR;
        }
    }
    if (vtss_ant_sd10g28_setup_lane(vtss_state, sd_cfg, port_no) != VTSS_RC_OK) {
        VTSS_E("Could not configure Serdes mode (%d) at port:%d",mode,port_no);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_sd_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no,  vtss_serdes_mode_t mode)
{
    u32 sd_indx, sd_type;


    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type));

    if (sd_type == FA_SERDES_TYPE_25G) {
        VTSS_RC(fa_sd25g_cfg(vtss_state, port_no,  mode));
    } else {
        VTSS_RC(fa_sd10g_cfg(vtss_state, port_no,  mode, sd_type));
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_cmu_init(vtss_state_t *vtss_state)
{
    for (u32 cmu = 0; cmu < 14; cmu++) {
        vtss_ant_sd10g28_cmu_reg_cfg(vtss_state, cmu);
    }

    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_FA */
