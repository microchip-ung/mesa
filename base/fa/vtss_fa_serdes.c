/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

vtss_rc vtss_fa_sd25g_init(vtss_state_t *vtss_state, u32 idx)
{

  /* erf_wr -u sd_lane_$idx2 sd_lane_cfg ext_cfg_rst 0 */
  /* exb_run $rst_dly_ps ps */

  /* # According to communication from GUC, this enables the L1_lol */
  /* # signal on dbg_obs[0]. */
  /* # Select CMU part of SD25G */
  /* erf_wr -u sd25g_lane_$idx cmu_ff register_table_index 0xff */
  /* erf_wr -u sd25g_lane_$idx cmu_2a r_dbg_lol_status 1 */
  /* # Select LANE part of SD25G */
  /* erf_wr -u sd25g_lane_$idx cmu_ff register_table_index 0x00 */
  /* erf_wr -u sd25g_lane_$idx lane_39 Ln_r_dlol_en 1 */

  /* erf_wr -u  sd_lane_$idx2 sd_lane_cfg macro_rst 0 */
  /* # ToDo: Anything more to do here? Pending GUC supplying needed info. */

return VTSS_RC_OK;

}

vtss_rc vtss_fa_cmu_cfg(vtss_state_t *vtss_state, u32 cmu_id)
{
    u32 cmu_tgt = VTSS_TO_SD_CMU(cmu_id);
    u32 cmu_cfg_tgt = VTSS_TO_SD_CMU_CFG(cmu_id);

 //  erf_wr -u  sd_cmu_cfg_$idx     sd_cmu_cfg  cmu_rst                   1
    REG_WRM(VTSS_SD_CMU_NONTERM_TARGET_SD_CMU_CFG(cmu_cfg_tgt),
            VTSS_F_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_CMU_RST(1),
            VTSS_M_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_CMU_RST);

//  erf_wr -u  sd_cmu_$idx          cmu_00      r_hwt_simulation_mode     1
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_00(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_00_R_HWT_SIMULATION_MODE(1),
            VTSS_M_SD10G_CMU_TARGET_CMU_00_R_HWT_SIMULATION_MODE);

//   erf_wr -u  sd_cmu_cfg_$idx     sd_cmu_cfg  cmu_rst                   0
    REG_WRM(VTSS_SD_CMU_NONTERM_TARGET_SD_CMU_CFG(cmu_cfg_tgt),
            VTSS_F_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_CMU_RST(0),
            VTSS_M_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_CMU_RST);

//  erf_wr -s  sd_cmu_$idx    cmu_45             r_en_ratechg_ctrl         0    ;#  bit 0 -- NON PCIE!!!
//  #@Tr: 1) => erf_wr -s  sd_cmu_$idx    cmu_45             r_DwidthCtrl_from_hwt     0    ;#  bit 1
//  erf_wr -s  sd_cmu_$idx    cmu_45             r_refck_ssc_en_from_hwt   0    ;#  bit 3
//  #@Tr: 3) => erf_wr -s  sd_cmu_$idx    cmu_45             r_link_buf_en_from_hwt    0    ;#  bit 5
//  #@Tr: 2) => erf_wr -s  sd_cmu_$idx    cmu_45             r_bias_en_from_hwt        0    ;#  bit 6
//  erf_wr -u  sd_cmu_$idx    cmu_45             r_auto_rst_tree_pd_man    1    ;#  bit 7
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_45(cmu_tgt),
        VTSS_F_SD10G_CMU_TARGET_CMU_45_R_REFCK_SSC_EN_FROM_HWT(0) |
        VTSS_F_SD10G_CMU_TARGET_CMU_45_R_LINK_BUF_EN_FROM_HWT(0) |
        VTSS_F_SD10G_CMU_TARGET_CMU_45_R_DWIDTHCTRL_FROM_HWT(0) |
        VTSS_F_SD10G_CMU_TARGET_CMU_45_R_AUTO_RST_TREE_PD_MAN(1) |
        VTSS_F_SD10G_CMU_TARGET_CMU_45_R_BIAS_EN_FROM_HWT(0) |
        VTSS_F_SD10G_CMU_TARGET_CMU_45_R_EN_RATECHG_CTRL(0),
        VTSS_M_SD10G_CMU_TARGET_CMU_45_R_REFCK_SSC_EN_FROM_HWT |
        VTSS_M_SD10G_CMU_TARGET_CMU_45_R_LINK_BUF_EN_FROM_HWT |
        VTSS_M_SD10G_CMU_TARGET_CMU_45_R_DWIDTHCTRL_FROM_HWT |
        VTSS_M_SD10G_CMU_TARGET_CMU_45_R_AUTO_RST_TREE_PD_MAN |
        VTSS_M_SD10G_CMU_TARGET_CMU_45_R_BIAS_EN_FROM_HWT |
        VTSS_M_SD10G_CMU_TARGET_CMU_45_R_EN_RATECHG_CTRL);

//  erf_wr -u  sd_cmu_$idx    cmu_1C             cfg_reserve_15_8           0    ;#  bit 0 = 0
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_1C(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_1C_CFG_RESERVE_15_8(0),
            VTSS_M_SD10G_CMU_TARGET_CMU_1C_CFG_RESERVE_15_8);

//  #@Tr: 1) => erf_wr -u  sd_cmu_$idx    cmu_47             r_pcs2pma_phymode         0    ;#  r_pcs2pma_phymode[4:0] (others)
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_47(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_47_R_PCS2PMA_PHYMODE_4_0(0),
            VTSS_M_SD10G_CMU_TARGET_CMU_47_R_PCS2PMA_PHYMODE_4_0);

//  #@Tr: 1) => erf_wr -u  sd_cmu_$idx    cmu_1A             cfg_refck_r_en            1    ;#
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_1A(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_1A_CFG_REFCK_R_EN(1),
            VTSS_M_SD10G_CMU_TARGET_CMU_1A_CFG_REFCK_R_EN);


  /* #erf_wr -u  sd_cmu_$idx    cmu_15             cfg_sel_div               0    ;# 5'b00000 : 64 */
  /* #                                                                                ;# 5'b00001 : 66 */
  /* #                                                                                ;# 5'b00010 : 80 */
  /* #                                                                                ;# 5'b00011 : 100 */
  /* #                                                                                ;# 5'b00100 : 120 */
  /* #                                                                                ;# 5'b01100 : 480 */
  /* #                                                                                ;# 5'b10100 : 240 */
  /* #                                                                                ;# Others :  not used */
  /* #@Tr: 1) => switch $idx { */
  /* #@Tr: 1) =>     0 - 3 - 6 { */
  /* #@Tr: 1) =>         # AUXCK1 CMU  10.00GHz   = 156.25MHz * 64 */
  /* #@Tr: 1) =>         erf_wr -u  sd_cmu_$idx    cmu_15     cfg_sel_div               0    ;# */
  /* #@Tr: 1) =>     } */
  /* #@Tr: 1) =>     1 - 4 - 7 { */
  /* #@Tr: 1) =>         # AUXCK2 CMU  12.50GHz   = 156.25MHz * 80 */
  /* #@Tr: 1) =>         erf_wr -u  sd_cmu_$idx    cmu_15     cfg_sel_div               2    ;# */
  /* #@Tr: 1) =>     } */
  /* #@Tr: 1) =>     default { */
  /* #@Tr: 1) =>         # MAIN CMU    10.3125GHz = 156.25MHz * 66 */
  /* #@Tr: 1) =>         erf_wr -u  sd_cmu_$idx    cmu_15     cfg_sel_div               1    ;# */
  /* #@Tr: 1) =>     } */
  /* #@Tr: 1) => } */


//  #@Tr: 1) => erf_wr -u  sd_cmu_$idx    cmu_0A             cfg_vco_div_mode          0    ;#  bit 2:0 1/1
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_0A(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_0A_CFG_VCO_DIV_MODE_2_0(0),
            VTSS_M_SD10G_CMU_TARGET_CMU_0A_CFG_VCO_DIV_MODE_2_0);

//  erf_wr -u  sd_cmu_$idx    cmu_22             cfg_refck_ssc_en          0    ;#  bit 0
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_22(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_EN(0),
            VTSS_M_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_EN);

  /* #@Tr: 3) => erf_wr -u  sd_cmu_$idx    cmu_20             cfg_link_buf_en           0    ;#  bit 0 */
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_20(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_20_CFG_LINK_BUF_EN(0),
            VTSS_M_SD10G_CMU_TARGET_CMU_20_CFG_LINK_BUF_EN);

    /* #@Tr: 2) => erf_wr -s  sd_cmu_$idx    cmu_1F             cfg_bias_dn_en            1    ;#  bit 0 */
    /* #@Tr: 2) => erf_wr -u  sd_cmu_$idx    cmu_1F             cfg_bias_up_en            1    ;#  bit 1 */
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_1F(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_UP_EN(1) |
            VTSS_F_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_DN_EN(1),
            VTSS_M_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_UP_EN |
            VTSS_M_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_DN_EN);

/* erf_wr -s  sd_cmu_$idx    cmu_09             cfg_en_tx_ck_up           1    ;#  bit 0 */
/* erf_wr -u  sd_cmu_$idx    cmu_09             cfg_en_tx_ck_dn           1    ;#  bit 1 */
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_09(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_DN(1) |
            VTSS_F_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_UP(1),
            VTSS_M_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_DN |
            VTSS_M_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_UP);

  /* erf_wr -u  sd_cmu_$idx    cmu_1F             cfg_vtune_sel             1    ;# */
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_1F(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_1F_CFG_VTUNE_SEL(1),
            VTSS_M_SD10G_CMU_TARGET_CMU_1F_CFG_VTUNE_SEL);

  /* erf_wr -u  sd_cmu_$idx    cmu_05             cfg_bias_tp_sel_1_0       3    ;#  bit 5:4 */
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_05(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_05_CFG_BIAS_TP_SEL_1_0(3),
            VTSS_M_SD10G_CMU_TARGET_CMU_05_CFG_BIAS_TP_SEL_1_0);

  /* erf_wr -u  sd_cmu_$idx    cmu_30             r_pll_dlol_en             1    ;#  bit 0 */
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_30(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_30_R_PLL_DLOL_EN(1),
            VTSS_M_SD10G_CMU_TARGET_CMU_30_R_PLL_DLOL_EN);

  /* #@Tr: 4) => erf_wr -u  sd_cmu_$idx    cmu_44             r_pll_rstn                0    ;#  bit 0 */
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_44(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_44_R_PLL_RSTN(0),
            VTSS_M_SD10G_CMU_TARGET_CMU_44_R_PLL_RSTN);

  /* #@Tr: 4) => erf_wr -u  sd_cmu_$idx    cmu_44             r_pll_rstn                1    ;#  bit 0 */
    REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_44(cmu_tgt),
            VTSS_F_SD10G_CMU_TARGET_CMU_44_R_PLL_RSTN(1),
            VTSS_M_SD10G_CMU_TARGET_CMU_44_R_PLL_RSTN);

    return VTSS_RC_OK;
}


static vtss_rc fa_sd25g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_serdes_mode_t mode, u32 sd_indx)
{
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;
    u32 sd_lane_tgt = 0;
    u32 pcs2pma_tx_speed = 0;
    u32 txfifo_ck_div = 0;
    u32 rxfifo_ck_div = 0;
    u32 hwt_cfg_sel_div = 0;
    u32 hwt_vco_div_sel = 0;
    u32 hwt_pre_divsel = 0;
    u32 pma_rxdiv_sel = 0;
    u32 data_width_sel = 0;
    u32 pma_txck_sel = 0;
    u32 txrate_sel = 0;
    u32 rxrate_sel = 0;

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
                /* 25.78125G 40-bit */
                pcs2pma_tx_speed = 2;
                txfifo_ck_div    = 0;
                rxfifo_ck_div    = 0;
                hwt_cfg_sel_div  = 0xf;
                hwt_vco_div_sel  = 0;
                hwt_pre_divsel   = 1;
                pma_rxdiv_sel    = 3;
                data_width_sel   = 4;
                pma_txck_sel     = 3;
                txrate_sel       = 0;
                rxrate_sel       = 0;
            } else if (speed == VTSS_SPEED_10G) {
                /* 10.3125G 64-bit */
                pcs2pma_tx_speed = 0;
                txfifo_ck_div    = 2;
                rxfifo_ck_div    = 2;
                hwt_cfg_sel_div  = 0x9;
                hwt_vco_div_sel  = 1;
                hwt_pre_divsel   = 0;
                pma_rxdiv_sel    = 0;
                data_width_sel   = 5;
                pma_txck_sel     = 0;
                txrate_sel       = 0;
                rxrate_sel       = 0;
            } else if (speed == VTSS_SPEED_5G) {

            }
            break;
        }
        case VTSS_SERDES_MODE_2G5: {
            /* 3.125G 10-bit */
            pcs2pma_tx_speed = 1;
            txfifo_ck_div    = 0;
            rxfifo_ck_div    = 0;
            hwt_cfg_sel_div  = 0x6;
            hwt_vco_div_sel  = 1;
            hwt_pre_divsel   = 0;
            pma_rxdiv_sel    = 11;
            data_width_sel   = 0;
            pma_txck_sel     = 11;
            txrate_sel       = 2;
            rxrate_sel       = 2;
            break;
        }
        case VTSS_SERDES_MODE_SGMII:
        case VTSS_SERDES_MODE_1000BaseX:
        case VTSS_SERDES_MODE_USXGMII:
        case VTSS_SERDES_MODE_USGMII:
        case VTSS_SERDES_MODE_QSGMII:
        case VTSS_SERDES_MODE_100FX:
        default: {
            VTSS_E("Serdes mode (%s) not supported",vtss_serdes_mode_txt(mode));
            return VTSS_RC_ERROR;
        }
    }
    sd_lane_tgt = VTSS_TO_SD_LANE(sd_indx + VTSS_SERDES_25G_START);

// Need a new VML drop to support the 25G serdes.
// To silence the compiler
    REG_WR(VTSS_SD_LANE_TARGET_SD_LANE_CFG(sd_lane_tgt),
            pcs2pma_tx_speed+txfifo_ck_div+rxfifo_ck_div+hwt_cfg_sel_div+hwt_vco_div_sel+
           hwt_pre_divsel+pma_rxdiv_sel+data_width_sel+ pma_txck_sel+txrate_sel+rxrate_sel);


  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 pcs2pma_tx_speed [lindex $sd_params 0] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 txfifo_ck_div    [lindex $sd_params 1] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 rxfifo_ck_div    [lindex $sd_params 2] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 hwt_cfg_sel_div  [lindex $sd_params 3] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 hwt_vco_div_sel  [lindex $sd_params 4] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 hwt_pre_divsel   [lindex $sd_params 5] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 pma_rxdiv_sel    [lindex $sd_params 6] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 data_width_sel   [lindex $sd_params 7] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 pma_txck_sel     [lindex $sd_params 8] */
  /* erf_wr -s sd_lane_$glb_idx sd_lane_cfg2 txrate_sel       [lindex $sd_params 9] */
  /* erf_wr -u sd_lane_$glb_idx sd_lane_cfg2 rxrate_sel       [lindex $sd_params 10] */

    return VTSS_RC_OK;
}

// body fflSerDesSD10G28::config_lane { type CMU  RATE  BITWIDTH } {
static vtss_rc fa_config_lane_10g(vtss_state_t *vtss_state, u32 sd_indx, u32 sd_type, u32 cmu, u32 rate, u32 width)
{
    u32 sd_tgt, sd_lane_tgt;
    u32 cmu_src, rate_src, rd_width_ctrl, bit_width;


    if (sd_type == FA_SERDES_TYPE_6G) {
        sd_tgt = VTSS_TO_SD6G_LANE(sd_indx);
        sd_lane_tgt = VTSS_TO_SD_LANE(sd_indx);
    } else if (sd_type == FA_SERDES_TYPE_10G) {
        sd_tgt = VTSS_TO_SD10G_LANE(sd_indx);
        sd_lane_tgt = VTSS_TO_SD_LANE(sd_indx + VTSS_SERDES_10G_START);
    } else {
        sd_tgt = VTSS_TO_SD25G_LANE(sd_indx);
        sd_lane_tgt = VTSS_TO_SD_LANE(sd_indx + VTSS_SERDES_25G_START);
    }

    switch (cmu) {
    case 103125: { cmu_src = 0; break; }
    case 10000:  { cmu_src = 1; break; }
    default:     { cmu_src = 3; }
    }

    switch (rate) {
    case 100: { rate_src = 0; break; } // 1/1
    case 50:  { rate_src = 1; break; } // 1/2
    case 25:  { rate_src = 2; break; } // 1/4
    case 12:  { rate_src = 3; break; } // 1/8
    default:  { rate_src = 1; }
    }

    switch (width) {
    case 10 : { rd_width_ctrl = 0; bit_width = 0; break; }
    case 16 : { rd_width_ctrl = 1; bit_width = 1; break; }
    case 20 : { rd_width_ctrl = 2; bit_width = 2; break; }
    case 32 : { rd_width_ctrl = 3; bit_width = 3; break; }
    case 40 : { rd_width_ctrl = 4; bit_width = 6; break; }
    case 64 : { rd_width_ctrl = 7; bit_width = 7; break; }
    default:  { rd_width_ctrl = 7; bit_width = 7;}
    }

   /* #erf_wr -u sd_lane_$glb_idx  sd_lane_cfg   macro_rst               1 */
   /* erf_wr -u $blk_name  lane_00              r_simulation_mode       1 */
   /* #erf_wr -u sd_lane_$glb_idx  sd_lane_cfg   macro_rst               0 */

   /* #@Tr: 1) => erf_wr -u $blk_name  lane_93              r_auxcksel_from_hwt      0  ;# */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_93(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_93_R_DWIDTHCTRL_FROM_HWT(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_93_R_DWIDTHCTRL_FROM_HWT);

   /* erf_wr -u $blk_name  lane_A1              r_ssc_from_hwt           0  ;# */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_A1(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_A1_R_SSC_FROM_HWT(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_A1_R_SSC_FROM_HWT);

   /* erf_wr -s sd_lane_$glb_idx  sd_lane_cfg  rx_ref_sel               $CMU_SRC */
   /* erf_wr -u sd_lane_$glb_idx  sd_lane_cfg  tx_ref_sel               $CMU_SRC */
    REG_WRM(VTSS_SD_LANE_TARGET_SD_LANE_CFG(sd_lane_tgt) ,
            VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_RX_REF_SEL(cmu_src) |
            VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_TX_REF_SEL(cmu_src),
            VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_RX_REF_SEL |
            VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_TX_REF_SEL);

   /* #@Tr: 1) => erf_wr -s $blk_name  lane_48              cfg_aux_rxck_sel         [expr int($CMU_SRC/2)]     ;# MSB: rx clock selection */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_48(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_48_CFG_AUX_RXCK_SEL(cmu_src/2),
            VTSS_M_SD10G_LANE_TARGET_LANE_48_CFG_AUX_RXCK_SEL);

   /* erf_wr -u $blk_name  lane_40              cfg_lane_reserve_7_0     [expr int($CMU_SRC%2)<<6]  ;# LSB: */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_40(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_40_CFG_LANE_RESERVE_7_0(cmu_src % 2 << 6),
            VTSS_M_SD10G_LANE_TARGET_LANE_40_CFG_LANE_RESERVE_7_0);

   /* erf_wr -s $blk_name  lane_50              cfg_ssc_rtl_clk_sel      [expr int($CMU_SRC/2)]     ;# MSB: */
   /* #@Tr: 1) => erf_wr -u $blk_name  lane_50              cfg_aux_txck_sel         [expr int($CMU_SRC%2)]     ;# LSB: tx resetb and tx clock */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_50(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RTL_CLK_SEL(cmu_src / 2) |
            VTSS_F_SD10G_LANE_TARGET_LANE_50_CFG_AUX_TXCK_SEL(cmu_src % 2),
            VTSS_M_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RTL_CLK_SEL |
            VTSS_M_SD10G_LANE_TARGET_LANE_50_CFG_AUX_TXCK_SEL);

   /* #@Tr: 1) => #                                                                                             ;# selection */
   /* erf_wr -u sd_lane_$glb_idx  sd_lane_cfg   macro_rst               0 */
    REG_WRM(VTSS_SD_LANE_TARGET_SD_LANE_CFG(sd_lane_tgt),
        VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_MACRO_RST(0),
        VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_MACRO_RST);

   /* erf_wr -u $blk_name  lane_93              r_reg_manual             1  ;# */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_93(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_93_R_REG_MANUAL(1),
        VTSS_M_SD10G_LANE_TARGET_LANE_93_R_REG_MANUAL);


   /* erf_wr -s $blk_name  lane_94              r_iscan_reg              1  ;# */
   /* erf_wr -s $blk_name  lane_94              r_txeq_reg               1  ;# */
   /* erf_wr -s $blk_name  lane_94              r_misc_reg               1  ;# */
   /* erf_wr -u $blk_name  lane_94              r_swing_reg              1  ;# */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_94(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_94_R_ISCAN_REG(1) |
        VTSS_F_SD10G_LANE_TARGET_LANE_94_R_TXEQ_REG(1) |
        VTSS_F_SD10G_LANE_TARGET_LANE_94_R_MISC_REG(1) |
        VTSS_F_SD10G_LANE_TARGET_LANE_94_R_SWING_REG(1),
        VTSS_M_SD10G_LANE_TARGET_LANE_94_R_ISCAN_REG |
        VTSS_M_SD10G_LANE_TARGET_LANE_94_R_TXEQ_REG |
        VTSS_M_SD10G_LANE_TARGET_LANE_94_R_MISC_REG |
        VTSS_M_SD10G_LANE_TARGET_LANE_94_R_SWING_REG);


   /* erf_wr -s $blk_name  lane_93              r_DwidthCtrl_from_hwt    0  ;# */
   /* erf_wr -s $blk_name  lane_93              r_lane_id_from_hwt       0  ;# */
   /* erf_wr -s $blk_name  lane_93              r_rx_pcie_gen12_from_hwt 0  ;# */
   /* erf_wr -u $blk_name  lane_93              r_en_ratechg_ctrl        0  ;#  bit 0 -- NON PCIE!!! */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_93(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_93_R_DWIDTHCTRL_FROM_HWT(0) |
        VTSS_F_SD10G_LANE_TARGET_LANE_93_R_LANE_ID_FROM_HWT(0) |
        VTSS_F_SD10G_LANE_TARGET_LANE_93_R_RX_PCIE_GEN12_FROM_HWT(0) |
        VTSS_F_SD10G_LANE_TARGET_LANE_93_R_EN_RATECHG_CTRL(0),
        VTSS_M_SD10G_LANE_TARGET_LANE_93_R_DWIDTHCTRL_FROM_HWT |
        VTSS_M_SD10G_LANE_TARGET_LANE_93_R_LANE_ID_FROM_HWT |
        VTSS_M_SD10G_LANE_TARGET_LANE_93_R_RX_PCIE_GEN12_FROM_HWT |
        VTSS_M_SD10G_LANE_TARGET_LANE_93_R_EN_RATECHG_CTRL);

   /* erf_wr -s $blk_name  lane_A1              r_cdr_from_hwt           0  ;# */
   /* erf_wr -u $blk_name  lane_A1              r_pclk_gating_from_hwt   1  ;# */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_A1(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_A1_R_CDR_FROM_HWT(0) |
        VTSS_F_SD10G_LANE_TARGET_LANE_A1_R_PCLK_GATING_FROM_HWT(1),
        VTSS_M_SD10G_LANE_TARGET_LANE_A1_R_CDR_FROM_HWT |
        VTSS_M_SD10G_LANE_TARGET_LANE_A1_R_PCLK_GATING_FROM_HWT);

   /* erf_wr -s $blk_name  lane_9E              r_auto_rst_tree_pd_man   1  ;# */
   /* erf_wr -u $blk_name  lane_9E              r_rxeq_reg               1  ;# */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_9E(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_9E_R_AUTO_RST_TREE_PD_MAN(1) |
        VTSS_F_SD10G_LANE_TARGET_LANE_9E_R_RXEQ_REG(1),
        VTSS_M_SD10G_LANE_TARGET_LANE_9E_R_AUTO_RST_TREE_PD_MAN |
        VTSS_M_SD10G_LANE_TARGET_LANE_9E_R_RXEQ_REG);


   /* # --- RX CDR Basix Setting			         		   */
   /* erf_wr -u $blk_name  lane_0F              r_cdr_m_gen1_7_0         2    ;#  CDR 1st order LP filter select GEN1 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_0F(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_0F_R_CDR_M_GEN1_7_0(2),
            VTSS_M_SD10G_LANE_TARGET_LANE_0F_R_CDR_M_GEN1_7_0);

   /* erf_wr -u $blk_name  lane_10              r_cdr_m_gen2_7_0         2    ;#  CDR 1st order LP filter select GEN2 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_10(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_11_R_CDR_M_GEN3_7_0(2),
            VTSS_M_SD10G_LANE_TARGET_LANE_11_R_CDR_M_GEN3_7_0);

   /* erf_wr -u $blk_name  lane_11              r_cdr_m_gen3_7_0         2    ;#  CDR 1st order LP filter select GEN3 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_11(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_11_R_CDR_M_GEN3_7_0(2),
            VTSS_M_SD10G_LANE_TARGET_LANE_11_R_CDR_M_GEN3_7_0);

    /* erf_wr -u $blk_name  lane_12              r_cdr_m_gen4_7_0         2    ;#  CDR 1st order LP filter select GEN4 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_12(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_12_R_CDR_M_GEN4_7_0(2),
            VTSS_M_SD10G_LANE_TARGET_LANE_12_R_CDR_M_GEN4_7_0);

   /* #@Tr: 2) => erf_wr -s $blk_name  lane_42              cfg_cdr_kf_gen1          1    ;#  CDR 1st order Gain Adjust GEN1 */
   /* #@Tr: 2) => erf_wr -u $blk_name  lane_42              cfg_cdr_kf_gen2          1    ;#  CDR 1st order Gain Adjust GEN2 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_42(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN1_2_0(1) |
        VTSS_F_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN2_2_0(1),
        VTSS_M_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN1_2_0 |
        VTSS_M_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN2_2_0);

   /* #@Tr: 2) => erf_wr -s $blk_name  lane_43              cfg_cdr_kf_gen3          1    ;#  CDR 1st order Gain Adjust GEN3 */
   /* #@Tr: 2) => erf_wr -u $blk_name  lane_43              cfg_cdr_kf_gen4          1    ;#  CDR 1st order Gain Adjust GEN4 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_43(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN3_2_0(1) |
        VTSS_F_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN4_2_0(1),
        VTSS_M_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN3_2_0 |
        VTSS_M_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN4_2_0);

   /* #@Tr: 2) => erf_wr -s $blk_name  lane_24              cfg_pi_bw_gen1           0    ;#  CDR PI BW Adj. GEN1 */
   /* #@Tr: 2) => erf_wr -u $blk_name  lane_24              cfg_pi_bw_gen2           0    ;#  CDR PI BW Adj. GEN2 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_24(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN1_3_0(0) |
        VTSS_F_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN2_3_0(0),
        VTSS_M_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN1_3_0 |
        VTSS_M_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN2_3_0);

   /* #@Tr: 2) => erf_wr -s $blk_name  lane_25              cfg_pi_bw_gen3           0    ;#  CDR PI BW Adj. GEN3 */
   /* #@Tr: 2) => erf_wr -u $blk_name  lane_25              cfg_pi_bw_gen4           0    ;#  CDR PI BW Adj. GEN4 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_25(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN3_3_0(0) |
        VTSS_F_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN4_3_0(0),
        VTSS_M_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN3_3_0 |
        VTSS_M_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN4_3_0);

   /* erf_wr -s $blk_name  lane_26              cfg_iscan_ext_dac_7_0    9    ;#  CDR clock phase tuning parameter */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_26(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_26_CFG_ISCAN_EXT_DAC_7_0(9),
            VTSS_M_SD10G_LANE_TARGET_LANE_26_CFG_ISCAN_EXT_DAC_7_0);

   /* # --- Lane Rate Setting 			    */
   /* erf_wr -u $blk_name  lane_14              cfg_pi_ext_dac_7_0       3    ;#  DFE clock phase tuning parameter */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_14(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_14_CFG_PI_EXT_DAC_7_0(3),
        VTSS_M_SD10G_LANE_TARGET_LANE_14_CFG_PI_EXT_DAC_7_0);

   /* erf_wr -u $blk_name  lane_a2              r_pcs2pma_phymode_4_0    0    ;#  Selection of application mode (SAS=4, KR=0) */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_A2(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_A2_R_PCS2PMA_PHYMODE_4_0(0),
        VTSS_M_SD10G_LANE_TARGET_LANE_A2_R_PCS2PMA_PHYMODE_4_0);

   /* erf_wr -u $blk_name  lane_0a              cfg_lane_id_2_0          0    ;#  Bias Trace Selection */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_0A(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_0A_CFG_LANE_ID_2_0(0),
        VTSS_M_SD10G_LANE_TARGET_LANE_0A_CFG_LANE_ID_2_0);

   /* erf_wr -s $blk_name  lane_35              cfg_txrate_1_0          $RATE_SRC */
   /* erf_wr -u $blk_name  lane_35              cfg_rxrate_1_0          $RATE_SRC */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_35(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_35_CFG_TXRATE_1_0(rate_src) |
            VTSS_F_SD10G_LANE_TARGET_LANE_35_CFG_RXRATE_1_0(rate_src),
            VTSS_M_SD10G_LANE_TARGET_LANE_35_CFG_TXRATE_1_0 |
            VTSS_M_SD10G_LANE_TARGET_LANE_35_CFG_RXRATE_1_0);

   /* erf_wr -u $blk_name  lane_94              r_DwidthCtrl_2_0         $RDWIDTHCTRL  ;#  UDL TX / RX data width selection: */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_94(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_94_R_DWIDTHCTRL_2_0(rd_width_ctrl),
            VTSS_M_SD10G_LANE_TARGET_LANE_94_R_DWIDTHCTRL_2_0);


   /* erf_wr -u $blk_name  lane_01              cfg_pma_tx_ck_bitwidth_2_0 $BIT_WIDTH    ;#  PMA Transmit clock pma_tx_ck_leaf frequency selection for different data width */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_01(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_01_CFG_PMA_TX_CK_BITWIDTH_2_0(bit_width),
            VTSS_M_SD10G_LANE_TARGET_LANE_01_CFG_PMA_TX_CK_BITWIDTH_2_0);

   /* erf_wr -u $blk_name  lane_30              cfg_rxdiv_sel_2_0        $BIT_WIDTH    ;#  PMA Receiver clock pma_rx_ ck_leaf frequency selection for different datawidth */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_30(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_30_CFG_RXDIV_SEL_2_0(bit_width),
            VTSS_M_SD10G_LANE_TARGET_LANE_30_CFG_RXDIV_SEL_2_0);

   /* # ---  Lane Basic Function Setting					    */
   /* #@Tr: 2) => erf_wr -u $blk_name  lane_2B              cfg_fom_sel              0    ;#  Figure of Merit(FOM) select */
   /* #@Tr: 2) => erf_wr -u $blk_name  lane_91              r_multi_lane_mode        0    ;#  Figure of Merit(FOM) select */
   /* #@Tr: 2) => erf_wr -u $blk_name  lane_2b              cfg_iscan_en             0    ;#  ISCAN_Enable */
   /* #@Tr: 2) => eerf_wr -s $blk_name  lane_01              cfg_rxdet_en             0    ;#  RXDet_Enable */
   /* #@Tr: 2) => eerf_wr -u $blk_name  lane_01              cfg_rxdet_str            0    ;#  Strobe the RXDET result */

   /* erf_wr -u $blk_name  lane_9E              r_en_auto_cdr_rstn       0    ;#  Lane CDR auto reset function enable */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_9E(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_9E_R_EN_AUTO_CDR_RSTN(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_9E_R_EN_AUTO_CDR_RSTN);

   /* #  ---  RX CDR Performance Parameters Setting				    */
   /* erf_wr -u $blk_name  lane_3c              cfg_dis_2ndOrder         0    ;#  2nd order CDR disable signal. */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_3C(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_3C_CFG_DIS_2NDORDER(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_3C_CFG_DIS_2NDORDER);

   /* erf_wr -u $blk_name  lane_39              cfg_rx_ssc_lh            1    ;#  CDR operation rate selection */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_39(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_39_CFG_RX_SSC_LH(1),
            VTSS_M_SD10G_LANE_TARGET_LANE_39_CFG_RX_SSC_LH);

   /* erf_wr -u $blk_name  lane_1A              cfg_pi_floop_steps_1_0   0    ;#  Frequency loop PI step selection */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1A(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_1A_CFG_PI_FLOOP_STEPS_1_0(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_FLOOP_STEPS_1_0);

   /* erf_wr -u $blk_name  lane_15              cfg_pi_ext_dac_15_8      2    ;#  2nd order CDR digital lowpass filter select */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_15(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_15_CFG_PI_EXT_DAC_15_8(2),
            VTSS_M_SD10G_LANE_TARGET_LANE_15_CFG_PI_EXT_DAC_15_8);

   /* erf_wr -u $blk_name  lane_16              cfg_pi_ext_dac_23_16     1    ;#  2nd order CDR digital lowpass filter select */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_15(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_16_CFG_PI_EXT_DAC_23_16(1),
            VTSS_M_SD10G_LANE_TARGET_LANE_16_CFG_PI_EXT_DAC_23_16);

   /* erf_wr -u $blk_name  lane_26              cfg_iscan_ext_dac_7_0    0    ;#  {cfg_iscan_ext_dac[14],cfg_iscan_ext_dac[7]} */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_26(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_26_CFG_ISCAN_EXT_DAC_7_0(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_26_CFG_ISCAN_EXT_DAC_7_0);
   /* #                                                                       ;#  CDR operation mode selection */
   /* erf_wr -u $blk_name  lane_27              cfg_iscan_ext_dac_15_8   0 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_27(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_27_CFG_ISCAN_EXT_DAC_15_8(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_27_CFG_ISCAN_EXT_DAC_15_8);

   /* # --- TX SSC  */
   /* erf_wr -u $blk_name  lane_4B              cfg_center_spreading     0  ;#  Lane SSC type selection */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_4B(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_4B_CFG_CENTER_SPREADING(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_4B_CFG_CENTER_SPREADING);

   /* erf_wr -u $blk_name  lane_4C              cfg_McntMaxVal_4_0      15  ;#  Lane SSC spreading range contrl */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_4C(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_4C_CFG_MCNTMAXVAL_4_0(15),
            VTSS_M_SD10G_LANE_TARGET_LANE_4C_CFG_MCNTMAXVAL_4_0);

    /* erf_wr -u $blk_name  lane_4D              cfg_ncntMaxVal_7_0      32 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_4D(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_4D_CFG_NCNTMAXVAL_7_0(32),
            VTSS_M_SD10G_LANE_TARGET_LANE_4D_CFG_NCNTMAXVAL_7_0);

    /* erf_wr -u $blk_name  lane_4E              cfg_ncntMaxVal_10_8      6 */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_4E(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_4E_CFG_NCNTMAXVAL_10_8(6),
            VTSS_M_SD10G_LANE_TARGET_LANE_4E_CFG_NCNTMAXVAL_10_8);

    /* erf_wr -s $blk_name  lane_4F              cfg_ssc_en               1  ;#  Lane SSC Enable */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_4F(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_4F_CFG_SSC_EN(1),
            VTSS_M_SD10G_LANE_TARGET_LANE_4F_CFG_SSC_EN);

    /* #@Tr: 2) => erf_wr -u $blk_name  lane_4F              cfg_ssc_pi_bw            0  ;#  SSC PI BW adjusting */
    /* #@Tr: 2) => erf_wr -s $blk_name  lane_50              cfg_ssc_pi_step          0  ;# */
    /* #@Tr: 2) => erf_wr -u $blk_name  lane_50              cfg_ssc_resetb           0  ;# */

    /* # --- TX Amplitude  */
    /* erf_wr -u $blk_name  lane_33              cfg_itx_ipdriver_base_2_0 3  ;#  8-bit for TX amplitude adjustment */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_33(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0(3),
        VTSS_M_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0);

    /* erf_wr -u $blk_name  lane_52              cfg_ibias_tune_reserve_5_0 8  ;# */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_52(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0(8),
        VTSS_M_SD10G_LANE_TARGET_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0);

    /* erf_wr -u $blk_name  lane_02              cfg_en_dly               1  ;#  Enable 1st stage post-equalization control of TX. */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_02(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_02_CFG_EN_DLY(1),
        VTSS_M_SD10G_LANE_TARGET_LANE_02_CFG_EN_DLY);

    /* erf_wr -u $blk_name  lane_32              cfg_itx_ipcml_base_1_0   0  ;#  TX predriver curent setting. */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_32(sd_tgt),
        VTSS_F_SD10G_LANE_TARGET_LANE_32_CFG_ITX_IPCML_BASE_1_0(0),
        VTSS_M_SD10G_LANE_TARGET_LANE_32_CFG_ITX_IPCML_BASE_1_0);

    /* # ---  Rset Lane                   */
    /* erf_wr -u $blk_name  lane_83              r_cdr_rstn               0  ;#  Reset signal for CDR, low active. */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_83(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_83_R_CDR_RSTN(0),
            VTSS_M_SD10G_LANE_TARGET_LANE_83_R_CDR_RSTN);

    /* erf_wr -u $blk_name  lane_83              r_cdr_rstn               1  ;#  Reset signal for CDR, low active. */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_83(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_83_R_CDR_RSTN(1),
            VTSS_M_SD10G_LANE_TARGET_LANE_83_R_CDR_RSTN);

    /* erf_wr -u $blk_name  lane_50              cfg_ssc_resetb           1  ;# */
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_50(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RESETB(1),
            VTSS_M_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RESETB);

    return VTSS_RC_OK;
}



static vtss_rc fa_sd10g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no,  vtss_serdes_mode_t mode, u32 sd_indx, u32 sd_type)
{
    u32 cmu_rate = 0, rate = 0, width = 0;
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;

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
            if (speed == VTSS_SPEED_10G) {
                cmu_rate = 103125;
                rate = 100;
                width = 64;
            } else {
                cmu_rate = 103125;
                rate = 50;
                width = 16;
            }
            break;
        }
        case VTSS_SERDES_MODE_2G5: {
            cmu_rate = 125000;
            rate = 25;
            width = 10;
            break;
        }
        case VTSS_SERDES_MODE_SGMII:
        case VTSS_SERDES_MODE_1000BaseX: {
            cmu_rate = 100000;
            rate = 12;
            width = 10;
            break;
        }
        case VTSS_SERDES_MODE_USXGMII: {
            if (speed == VTSS_SPEED_10G) {
                cmu_rate = 103125;
                rate = 100;
                width = 32;
            } else {
                cmu_rate = 103125;
                rate = 50;
                width = 16;
            }
            break;
        }
        case VTSS_SERDES_MODE_USGMII: {
            cmu_rate = 100000;
            rate = 100;
            width = 20;
            break;
        }
        case VTSS_SERDES_MODE_QSGMII: {
            cmu_rate = 100000;
            rate = 50;
            width = 20;
            break;
        }
        case VTSS_SERDES_MODE_100FX: {
            break;
        }
        default: {
            VTSS_E("Serdes mode (%d) not supported",mode);
            return VTSS_RC_ERROR;
        }
    }

    VTSS_RC(fa_config_lane_10g(vtss_state, sd_indx, sd_type, cmu_rate, rate, width));

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_sd_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no,  vtss_serdes_mode_t mode)
{
    u32 sd_indx, sd_type;

    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type));

    if (sd_type == FA_SERDES_TYPE_25G) {
        VTSS_RC(fa_sd25g_cfg(vtss_state, port_no,  mode, sd_indx));
    } else {
        VTSS_RC(fa_sd10g_cfg(vtss_state, port_no,  mode, sd_indx, sd_type));
    }

    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_FA */
