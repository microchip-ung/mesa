// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>

#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#else
#include <vtss/api/types.h>
#include "vtss_state.h"
#endif

#include "vtss_sd6g40_procs.h"



vtss_rc vtss_sd6g40_get_conf_from_mode(vtss_sd6g40_mode_t        f_mode, BOOL ref125M,
                                           vtss_sd6g40_mode_args_t *const ret_val) {
    switch(f_mode) {
     case VTSS_SD6G40_MODE_QSGMII :   {
        ret_val->lane_10bit_sel = 0;
        if (ref125M) {
          ret_val->mpll_multiplier = 40;
          ret_val->ref_clkdiv2= 0x1;
          ret_val->tx_rate= 0x0;
          ret_val->rx_rate= 0x0;
        } else {
          ret_val->mpll_multiplier = 100;
          ret_val->ref_clkdiv2= 0x0;
          ret_val->tx_rate= 0x0;
          ret_val->rx_rate= 0x0;
        }
        VTSS_D ("Mode is QSGMII\n");
        break;
      }
     case VTSS_SD6G40_MODE_SGMII2G5 :   {
        ret_val->lane_10bit_sel = 1;
        if (ref125M) {
          ret_val->mpll_multiplier = 50;
          ret_val->ref_clkdiv2= 0x1;
          ret_val->tx_rate= 0x1;
          ret_val->rx_rate= 0x1;
        } else {
          ret_val->mpll_multiplier = 125;
          ret_val->ref_clkdiv2= 0x0;
          ret_val->tx_rate= 0x1;
          ret_val->rx_rate= 0x1;
        }
        VTSS_D ("Mode is SGMII2G5\n");
        break;
      }
      case VTSS_SD6G40_MODE_SGMII :
      case VTSS_SD6G40_MODE_1G_LAN :   {
        ret_val->lane_10bit_sel = 1;
        if (ref125M) {
          ret_val->mpll_multiplier = 40;
          ret_val->ref_clkdiv2= 0x1;
          ret_val->tx_rate= 0x2;
          ret_val->rx_rate= 0x2;
        } else {
          ret_val->mpll_multiplier = 100;
          ret_val->ref_clkdiv2= 0x0;
          ret_val->tx_rate= 0x2;
          ret_val->rx_rate= 0x2;
        }

        VTSS_D ("Mode is SGMII/1G LAN");
        break;
      }
      default :   {
        VTSS_E("vtss_sd6g40_get_conf_from_mode: invalid parameter value for f_mode\n");

        ret_val->lane_10bit_sel = 0;
        if (ref125M) {
          ret_val->mpll_multiplier = 40;
          ret_val->ref_clkdiv2= 0x1;
          ret_val->tx_rate= 0x0;
          ret_val->rx_rate= 0x0;
        } else {
          ret_val->mpll_multiplier = 100;
          ret_val->ref_clkdiv2= 0x0;
          ret_val->tx_rate= 0x0;
          ret_val->rx_rate= 0x0;
        }
        VTSS_D ("Mode is QSGMII\n");
        break;
      }
    }
    return VTSS_RC_OK;
}


/********************************************************************************
 ********************************************************************************
 ***     M A I N   F U N C T I O N S                                          ***
 ********************************************************************************
 ********************************************************************************/



/********************************************************************************
 ***                   vtss_calc_sd6g40_setup_lane                                  ***
 ********************************************************************************/
vtss_rc vtss_calc_sd6g40_setup_lane (const vtss_sd6g40_setup_args_t config,
                                   vtss_sd6g40_setup_struct_t     *const ret_val) {

    vtss_rc          rslt;
    vtss_sd6g40_mode_args_t sd6g40_mode;
    vtss_sd6g40_mode_args_t *mode_args = &sd6g40_mode;

    rslt = VTSS_RC_OK;
    rslt = vtss_sd6g40_get_conf_from_mode(config.mode, config.refclk125M, mode_args);

    ret_val->lane_10bit_sel[0]   =           mode_args->lane_10bit_sel;
    ret_val->rx_rate[0]   =                  mode_args->rx_rate;
    ret_val->tx_rate[0]   =                  mode_args->tx_rate;
    ret_val->mpll_multiplier[0] =            mode_args->mpll_multiplier;
    ret_val->ref_clkdiv2[0]   =              mode_args->ref_clkdiv2;
    ret_val->rx_eq[0]   =                    config.rx_eq;
    ret_val->rx_eq[0]   =                    config.tx_preemp;
    ret_val->rx_term_en[0]   =               0;

    if (config.tx2rx_loop == VTSS_SD6G40_LTX2RX) {
      ret_val->lane_loopbk_en[0]             = 1;
    } else if (config.tx2rx_loop == VTSS_SD6G40_TX2RX_LOOP_NONE) {
      ret_val->lane_loopbk_en[0]              = 0;
    }

    //TX invert
    if (config.txinvert) {
      ret_val->tx_invert[0]                =1;
    } else {
      ret_val->tx_invert[0]                =0;
    }
    //RX invert
    if (config.rxinvert) {
      ret_val->rx_invert[0]                =1;
    } else {
      ret_val->rx_invert[0]                =0;
    }
    return rslt;
}
/*
vtss_rc vtss_calc_sd6g40_lane_pwr_down (vtss_sd6g40_lane_pwr_down_t *const ret_val) {

    ret_val->r_iscan_reg[0]                 =   1;
    ret_val->r_txeq_reg[0]                  =   1;
    ret_val->r_misc_reg[0]                  =   1;
    ret_val->r_swing_reg[0]                 =   1;
    ret_val->r_reg_manual[0]                =   1;
    ret_val->r_dwidthctrl_from_hwt[0]       =   0;
    ret_val->r_auxcksel_from_hwt[0]         =   0;
    ret_val->r_lane_id_from_hwt[0]          =   0;
    ret_val->r_rx_pcie_gen12_from_hwt[0]    =   0;
    ret_val->r_ssc_from_hwt[0]              =   0;
    ret_val->r_cdr_from_hwt[0]              =   0;
    ret_val->r_pclk_gating_from_hwt[0]      =   1;
    ret_val->cfg_lane_id_2_0[0]             =   7;
    ret_val->cfg_dfetap_en_5_1[0]           =   1;
    ret_val->cfg_dfeck_en[0]                =   0;
    ret_val->cfg_dfe_pd[0]                  =   1;
    ret_val->cfg_erramp_pd[0]               =   1;
    ret_val->cfg_pi_dfe_en[0]               =   0;
    ret_val->cfg_pi_en[0]                   =   0;
    ret_val->cfg_pd_ctle[0]                 =   1;
    ret_val->cfg_summer_en[0]               =   0;
    ret_val->cfg_pd_rx_cktree[0]            =   0;
    ret_val->cfg_pd_clk[0]                  =   1;
    ret_val->cfg_pd_cml[0]                  =   1;
    ret_val->cfg_pd_driver[0]               =   1;
    ret_val->cfg_rx_reg_pu[0]               =   0;
    ret_val->cfg_cdrck_en[0]                =   0;
    ret_val->cfg_dcdr_pd[0]                 =   1;
    ret_val->cfg_pd_sq[0]                   =   1;
    ret_val->cfg_en_main[0]                 =   1;
    ret_val->cfg_en_adv[0]                  =   1;
    ret_val->cfg_en_dly[0]                  =   1;
    ret_val->cfg_tap_main[0]                =   1;
    ret_val->cfg_r50_en[0]                  =   1;
    ret_val->cfg_rxdet_en[0]                =   0;
    ret_val->cfg_rxdet_str[0]               =   0;
    ret_val->cfg_eid_lp[0]                  =   0;
    ret_val->r_txei[0]                      =   0;



    return VTSS_RC_OK;
}

*/



/* ******************************************************************************** */
/* ***                        E N D   O F    F I L E                            *** */
/* ******************************************************************************** */
