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

#include "vtss_sd25g28_procs.h"

/* function to map from SD25G28 interface width to configuration value */
static u8 sd25g28_get_iw_setting(const u8 interface_width)
{
    u8 retval;

    VTSS_D(" sd25g28_get_iw_setting:  Interface width is %d bits \n", interface_width);
    switch (interface_width) {
    case 10U: {
        retval = 0U;
        break;
    }
    case 16U: {
        retval = 1U;
        break;
    }
        //        case 20: {
        //            return 2;
        //            break;
        //        }
    case 32U: {
        retval = 3U;
        break;
    }
    case 40U: {
        retval = 4U;
        break;
    }
    case 64U: {
        retval = 5U;
        break;
    }
    default: {
        VTSS_E("Illegal value %d for interface width\n", interface_width);
        retval = 0U;
        break;
    }
    }
    return retval;
}

vtss_rc vtss_sd25g28_get_conf_from_mode(vtss_sd25g28_mode_t             mode,
                                        vtss_sd25g28_mode_args_t *const ret_val)
{

    ret_val->txmargin = 0x0U;            // as per AN_0003
    ret_val->ln_cfg_ctle_rstn = 0U;      // Default; What does this setting do?
    ret_val->ln_r_dfe_rstn = 0U;         // Default;
    ret_val->ln_cfg_itx_ipcml_base = 0U; // Default;
    ret_val->com_pll_reserve = 0xfU;     // Default;
    ret_val->cfg_i_vco_3_0 = 6U;
    ret_val->cfg_icp_base_sel_3_0 = 3U;
    ret_val->cfg_icp_sel_2_0 = 3;
    ret_val->cfg_rsel_2_0 = 5U;
    ret_val->ln_cfg_cdr_m_7_0 = 6U;
    ret_val->ln_cfg_dis_2ndorder = 1U;
    ret_val->ln_cfg_filter2nd_yz_6_0 = 8U;
    switch (mode) {
    case VTSS_SD25G28_MODE_25G_ETH:
    case VTSS_SD25G28_MODE_25G_LAN: {
        // ret_val->datarate= 25.7813e9;
        // ret_val->bitwidth 40; //10G Devices
        ret_val->bitwidth = sd25g28_get_iw_setting(40);
        ret_val->tx_pre_div = 0U;
        ret_val->fifo_ck_div = 0U;
        ret_val->pre_divsel = 1U;
        ret_val->vco_div_mode = 0U;
        ret_val->sel_div = 15U;
        ret_val->ck_bitwidth = 3U;
        ret_val->subrate = 0U;
        ret_val->com_txcal_en = 0U;
        ret_val->com_tx_reserve_msb = (0x26U << 1U); // Default is 0x20<<1
        ret_val->com_tx_reserve_lsb = ((3U << 6U) + (3U << 4U));
        ret_val->ln_tx_reserve_msb =
            ((3U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (2U << 1U));
        ret_val->ln_tx_reserve_lsb = ((3U << 6U) + (3U << 4U) + (3U << 2U) + (2U << 0U));
        ret_val->ln_bw = 3U;
        ret_val->ln_rxterm = 0U;
        ret_val->dfe_enable = 1U;
        ret_val->dfe_tap = 0x1fU;
        ret_val->txmargin = 0x1U;
        ret_val->ln_cfg_ctle_rstn = 1U;
        ret_val->ln_r_dfe_rstn = 1U; // Default;
        ret_val->ln_cfg_pi_bw_3_0 = 0U;
        ret_val->ln_cfg_cdr_m_7_0 = 4U;
        ret_val->ln_cfg_dis_2ndorder = 0U;
        ret_val->ln_cfg_filter2nd_yz_6_0 = 0x3fU;

        ret_val->tx_tap_dly = 8U;
        ret_val->tx_tap_adv = 0xcU; // this depends on actual Si
        VTSS_D("Mode is 25G_LAN/ETH\n");
        break;
    }
    case VTSS_SD25G28_MODE_25G_KR: {
        // ret_val->datarate= 25.7813e9;
        // ret_val->bitwidth 40; //10G Devices
        ret_val->bitwidth = sd25g28_get_iw_setting(64);
        ret_val->tx_pre_div = 0U;
        ret_val->fifo_ck_div = 2U;
        ret_val->pre_divsel = 1U;
        ret_val->vco_div_mode = 0U;
        ret_val->sel_div = 15U;
        ret_val->ck_bitwidth = 0U;
        ret_val->subrate = 0U;
        ret_val->com_txcal_en = 0U;
        ret_val->com_tx_reserve_msb = (0x26U << 1U); // Default is 0x20<<1
        ret_val->com_tx_reserve_lsb = ((3U << 6U) + (3U << 4U));
        ret_val->ln_tx_reserve_msb =
            ((3U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (2U << 1U));
        ret_val->ln_tx_reserve_lsb = ((3U << 6U) + (3U << 4U) + (3U << 2U) + (2U << 0U));
        ret_val->ln_bw = 3U;
        ret_val->ln_rxterm = 0U;
        ret_val->dfe_enable = 1U;
        ret_val->dfe_tap = 0x1fU;
        ret_val->txmargin = 0x1U;
        ret_val->ln_cfg_ctle_rstn = 1U;
        ret_val->ln_r_dfe_rstn = 1U; // Default;
        ret_val->ln_cfg_pi_bw_3_0 = 0U;
        ret_val->ln_cfg_cdr_m_7_0 = 4U;
        ret_val->ln_cfg_dis_2ndorder = 0U;
        ret_val->ln_cfg_filter2nd_yz_6_0 = 0x3fU;

        ret_val->tx_tap_dly = 8U;
        ret_val->tx_tap_adv = 0xcU; // this depends on actual Si
        VTSS_D("Mode is 25G_LAN/ETH\n");
        break;
    }
    case VTSS_SD25G28_MODE_10G_QSXGMII:
    case VTSS_SD25G28_MODE_10G_DSXGMII: {
        // ret_val->datarate = 10.3125e9;
        // ret_val->bitwidth 32;
        ret_val->bitwidth = sd25g28_get_iw_setting(32);
        ret_val->tx_pre_div = 0U;
        ret_val->fifo_ck_div = 1U;
        ret_val->pre_divsel = 0U;   //=Fref
        ret_val->vco_div_mode = 1U; // div by 2
        ret_val->sel_div = 9U;      // *132
        ret_val->ck_bitwidth = 0U;
        ret_val->subrate = 0U;
        ret_val->com_txcal_en = 1U;
        ret_val->com_tx_reserve_msb = (0x20U << 1U); //
        ret_val->com_tx_reserve_lsb = ((1U << 6U) + (0U << 4U));
        ret_val->ln_tx_reserve_msb =
            ((1U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (2U << 1U));
        ret_val->ln_tx_reserve_lsb = ((1U << 6U) + (0U << 4U) + (1U << 2U) + (0U << 0U));
        ret_val->ln_cfg_pi_bw_3_0 = 0U;
        ret_val->ln_bw = 1U;
        ret_val->ln_rxterm = 0U;
        ret_val->dfe_enable = 1U;
        ret_val->dfe_tap = 0x1fU;
        ret_val->txmargin = 0x1U;
        ret_val->cfg_i_vco_3_0 = 10U;
        ret_val->cfg_icp_base_sel_3_0 = 5U;
        ret_val->cfg_icp_sel_2_0 = 4U;
        ret_val->cfg_rsel_2_0 = 6U;
        ret_val->ln_cfg_ctle_rstn = 1U;
        ret_val->ln_r_dfe_rstn = 1U; // This clears most CRC errors
        ret_val->tx_tap_dly = 0U;
        ret_val->tx_tap_adv = 0x0U; // this depends on actual Si
        VTSS_D("Mode is Q(D)SXGMII\n");
        break;
    }
    case VTSS_SD25G28_MODE_10G_ETH:
    case VTSS_SD25G28_MODE_10G_LAN: {
        // ret_val->datarate= 10.3125e9;
        // ret_val->bitwidth 64;
        ret_val->bitwidth = sd25g28_get_iw_setting(64);
        ret_val->tx_pre_div = 0U;
        ret_val->fifo_ck_div = 2U;
        ret_val->pre_divsel = 0U;   //=Fref
        ret_val->vco_div_mode = 1U; // div by 2
        ret_val->sel_div = 9U;      // *132
        ret_val->ck_bitwidth = 0U;
        ret_val->subrate = 0U;
        ret_val->com_txcal_en = 1U;
        ret_val->com_tx_reserve_msb = (0x20U << 1U); //
        ret_val->com_tx_reserve_lsb = ((1U << 6U) + (0U << 4U));
        ret_val->ln_tx_reserve_msb =
            ((1U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (2U << 1U));
        ret_val->ln_tx_reserve_lsb = ((1U << 6U) + (0U << 4U) + (1U << 2U) + (0U << 0U));
        ret_val->ln_bw = 3U;
        ret_val->ln_cfg_pi_bw_3_0 = 0U;
        ret_val->ln_rxterm = 3U; // Changed to 2 CTS 07/06/2019
        ret_val->cfg_i_vco_3_0 = 10U;
        ret_val->cfg_icp_base_sel_3_0 = 5U;
        ret_val->cfg_icp_sel_2_0 = 4U;
        ret_val->cfg_rsel_2_0 = 6U;
        ret_val->dfe_enable = 1U;
        ret_val->dfe_tap = 0x1fU;
        ret_val->ln_cfg_ctle_rstn = 1U;
        ret_val->ln_r_dfe_rstn = 1U; // This clears most CRC errors
        ret_val->tx_tap_dly = 0U;
        ret_val->tx_tap_adv = 0x0U; // this depends on actual Si
        VTSS_D("Mode is 10G_LAN/ETH\n");
        break;
    }
    case VTSS_SD25G28_MODE_5G_LAN: {
        // TODO: Need to handle DEV5G/DEV2G5 related serdes configuration
        // ret_val->datarate= 5.15625e9;
        // ret_val->bitwidth 64;
        ret_val->bitwidth = sd25g28_get_iw_setting(64);
        ret_val->tx_pre_div = 0U;
        ret_val->fifo_ck_div = 2U;
        ret_val->pre_divsel = 0U;   //=Fref
        ret_val->vco_div_mode = 2U; // div by 4
        ret_val->sel_div = 9U;      // *132
        ret_val->ck_bitwidth = 0U;
        ret_val->subrate = 0U;
        ret_val->com_txcal_en = 1U;
        ret_val->com_tx_reserve_msb = (0x20U << 1U); //
        ret_val->com_tx_reserve_lsb = ((0U << 6U) + (0U << 4U));
        ret_val->ln_tx_reserve_msb =
            ((0U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (3U << 1U));
        ret_val->ln_tx_reserve_lsb = ((2U << 6U) + (0U << 4U) + (0U << 2U) + (0U << 0U));
        ret_val->ln_bw = 0U;
        ret_val->ln_rxterm = 0U;
        ret_val->ln_cfg_pi_bw_3_0 = 6U;
        ret_val->cfg_i_vco_3_0 = 10U;
        ret_val->cfg_icp_base_sel_3_0 = 5U;
        ret_val->cfg_icp_sel_2_0 = 4U;
        ret_val->cfg_rsel_2_0 = 6U;
        ret_val->dfe_enable = 0U;
        ret_val->dfe_tap = 0x0U;

        ret_val->tx_tap_dly = 0U;
        ret_val->tx_tap_adv = 0x0U; // this depends on actual Si
        VTSS_D("Mode is 5G_LAN/ETH\n");
        break;
    }
    case VTSS_SD25G28_MODE_5G_USXGMII: {
        // ret_val->datarate= 5.15625e9;
        // ret_val->bitwidth 16;
        ret_val->bitwidth = sd25g28_get_iw_setting(16);
        ret_val->tx_pre_div = 0U;
        ret_val->fifo_ck_div = 0U;
        ret_val->pre_divsel = 0U;   //=Fref
        ret_val->vco_div_mode = 2U; // div by 4
        ret_val->sel_div = 9U;      // *132
        ret_val->ck_bitwidth = 0U;
        ret_val->subrate = 0U;
        ret_val->com_txcal_en = 1U;
        ret_val->com_tx_reserve_msb = (0x20U << 1U); //
        ret_val->com_tx_reserve_lsb = ((0U << 6U) + (0U << 4U));
        ret_val->ln_tx_reserve_msb =
            ((0U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (3U << 1U));
        ret_val->ln_tx_reserve_lsb = ((2U << 6U) + (0U << 4U) + (0U << 2U) + (0U << 0U));
        ret_val->ln_bw = 0U;
        ret_val->ln_cfg_pi_bw_3_0 = 6U;
        ret_val->ln_rxterm = 0U;
        ret_val->cfg_i_vco_3_0 = 10U;
        ret_val->cfg_icp_base_sel_3_0 = 5U;
        ret_val->cfg_icp_sel_2_0 = 4U;
        ret_val->cfg_rsel_2_0 = 6U;
        ret_val->dfe_enable = 0U;
        ret_val->dfe_tap = 0x0U;

        ret_val->tx_tap_dly = 0U;
        ret_val->tx_tap_adv = 0x0U; // this depends on actual Si
        VTSS_D("Mode is USXGMII5G\n");
        break;
    }
    case VTSS_SD25G28_MODE_SGMII2G5: {
        // ret_val->datarate= 3.125e9;
        // ret_val->bitwidth 10;
        ret_val->bitwidth = sd25g28_get_iw_setting(10);
        ret_val->tx_pre_div = 0U; //_004
        ret_val->fifo_ck_div = 0U;
        ret_val->pre_divsel = 0U;   //=Fref
        ret_val->vco_div_mode = 1U; // div by 2
        ret_val->sel_div = 6U;      // *160
        ret_val->ck_bitwidth = 3U;
        ret_val->subrate = 2U;
        ret_val->com_txcal_en = 1U;
        ret_val->com_tx_reserve_msb = (0x26U << 1U); // 08Jan mail [11:8] =0xc
        ret_val->com_tx_reserve_lsb = (0xfU << 4U);
        ret_val->ln_cfg_itx_ipcml_base = 2U; //;
        ret_val->ln_tx_reserve_msb =
            ((0U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (0U << 1U));
        ret_val->ln_tx_reserve_lsb = ((2U << 6U) + (0U << 4U) + (0xaU << 0U)); // 09Jan Mail
        ret_val->ln_bw = 0U;
        ret_val->ln_cfg_pi_bw_3_0 = 0U;   //_004
        ret_val->ln_rxterm = (1U << 2U); //_004
        ret_val->dfe_enable = 0U;
        ret_val->dfe_tap = 0U;

        ret_val->tx_tap_dly = 0U;
        ret_val->tx_tap_adv = 0x0U; // this depends on actual Si
        VTSS_D("Mode is SGMII2G5\n");
        break;
    }
    case VTSS_SD25G28_MODE_SGMII:
    case VTSS_SD25G28_MODE_1G_LAN: {
        // ret_val->datarate= 1.25e9;
        // ret_val->bitwidth 10;
        ret_val->bitwidth = sd25g28_get_iw_setting(10);
        ret_val->tx_pre_div = 0U; //=0 in _004; was 1;  it works for both
        ret_val->fifo_ck_div = 1U;
        ret_val->pre_divsel = 0U;   //=Fref
        ret_val->vco_div_mode = 1U; // div by 2
        ret_val->sel_div = 8U;      // *128
        ret_val->ck_bitwidth = 3U;
        ret_val->subrate = 3U;
        ret_val->com_txcal_en = 1U;
        ret_val->com_tx_reserve_msb = (0x26U << 1U); //
        ret_val->com_tx_reserve_lsb = ((3U << 6U) + (3U << 4U));
        ret_val->ln_tx_reserve_msb =
            ((0U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (0U << 1U));
        ret_val->ln_tx_reserve_lsb = ((3U << 6U) + (0U << 4U) + (3U << 2U) + (2U << 0U));
        ret_val->ln_bw = 0U;
        ret_val->ln_rxterm = 0U;
        ret_val->ln_cfg_pi_bw_3_0 = 0U; //=0 as per _004; was 6; it works for both
        ret_val->dfe_enable = 0U;
        ret_val->dfe_tap = 0U;

        ret_val->tx_tap_dly = 0U;
        ret_val->tx_tap_adv = 0x0U; // this depends on actual Si and channel

        VTSS_D("Mode is SGMII/1G LAN");
        break;
    }
    case VTSS_SD25G28_MODE_FX100:
    default:                      {
        VTSS_E("vtss_sd25g28_get_conf_from_mode: invalid parameter value for f_mode\n");
        // ret_val->datarate= 25.7813e9;
        // ret_val->bitwidth 40; //10G Devices
        ret_val->bitwidth = sd25g28_get_iw_setting(40);
        ret_val->tx_pre_div = 0;
        ret_val->fifo_ck_div = 0;
        ret_val->pre_divsel = 1;
        ret_val->vco_div_mode = 0;
        ret_val->sel_div = 15;
        ret_val->ck_bitwidth = 3;
        ret_val->subrate = 0;
        ret_val->com_txcal_en = 0;
        ret_val->com_tx_reserve_msb = (0x26U << 1U); //
        ret_val->com_tx_reserve_lsb = ((3U << 6U) + (3U << 4U));
        ret_val->ln_tx_reserve_msb =
            ((3U << 6U) + (0U << 5U) + (0U << 4U) + (1U << 3U) + (2U << 1U));
        ret_val->ln_tx_reserve_lsb = ((3U << 6U) + (3U << 4U) + (3U << 2U) + (2U << 0U));
        ret_val->ln_bw = 3;
        ret_val->ln_rxterm = 0;
        ret_val->dfe_enable = 1;
        ret_val->dfe_tap = 0x1f;
        ret_val->txmargin = 0x1;
        ret_val->ln_cfg_pi_bw_3_0 = 0;

        ret_val->tx_tap_dly = 8;
        ret_val->tx_tap_adv = 0xc; // this depends on actual Si and channel

        VTSS_D("Default: Mode is 25G_LAN/ETH\n");
        break;
    }
    }
    return VTSS_RC_OK;
}

/********************************************************************************
 ********************************************************************************
 ***     M A I N   F U N C T I O N S ***
 ********************************************************************************
 ********************************************************************************/

/********************************************************************************
 ***                   vtss_calc_sd25g28_setup_lane ***
 ********************************************************************************/
vtss_rc vtss_calc_sd25g28_setup_lane(const vtss_sd25g28_setup_args_t    config,
                                     vtss_sd25g28_setup_struct_t *const ret_val)
{

    vtss_rc rslt;
    // vtss_sd25g28_mode_args_t *mode_args =
    // (vtss_sd25g28_mode_args_t*)malloc(sizeof(vtss_sd25g28_mode_args_t));
    vtss_sd25g28_mode_args_t     sd25g28_mode;
    vtss_sd25g28_mode_args_t    *mode_args = &sd25g28_mode;
    vtss_sd25g28_preset_struct_t preset;

    rslt = vtss_sd25g28_get_conf_from_mode(config.mode, mode_args);

    ret_val->r_DwidthCtrl_2_0[0] = mode_args->bitwidth; // L1_data_width_sel[2;0]
    ret_val->r_txfifo_ck_div_pmad_2_0[0] =
        mode_args->fifo_ck_div; // L1_txfifo_ck_div; TX FIFO clock divider
    ret_val->r_rxfifo_ck_div_pmad_2_0[0] =
        mode_args->fifo_ck_div; // L1_rxfifo_ck_div; RX FIFO clock divider
    ret_val->cfg_vco_div_mode_1_0[0] =
        mode_args->vco_div_mode; // hwt_vco_div_sel; PMA divider setting or Reference
                                 // clock multiplying factor; 0:/1;1:/2;2:/4;3:/8
    ret_val->cfg_pre_divsel_1_0[0] = mode_args->pre_divsel; // hwt_pre_div_sel; Reference clk
                                                            // divide: 00:/1;01:/2;10:/4
    ret_val->cfg_sel_div_3_0[0] =
        mode_args->sel_div; // hwt_cfg_sel_div PLL multiplying factor (Fref*N);
                            // Application notes for more details and
                            // restrictions. Common settings:0110: Divide by 160
                            // 1111: Divide by 330
    ret_val->cfg_i_vco_3_0[0] = mode_args->cfg_i_vco_3_0;
    ret_val->cfg_icp_base_sel_3_0[0] = mode_args->cfg_icp_base_sel_3_0;
    ret_val->cfg_icp_sel_2_0[0] = mode_args->cfg_icp_sel_2_0;
    ret_val->cfg_rsel_2_0[0] = mode_args->cfg_rsel_2_0;
    ret_val->cfg_vco_start_code_3_0[0] = 0;
    ret_val->ln_cfg_pma_tx_ck_bitwidth_2_0[0] =
        mode_args->ck_bitwidth; // L1_pma_txck_sel; pma_tx_ck_leaf frequency
                                // selection
    ret_val->ln_cfg_tx_prediv_1_0[0] =
        mode_args->tx_pre_div; // L1_pcs2pma_tx_speed; TX subrate control
    ret_val->ln_cfg_rxdiv_sel_2_0[0] = mode_args->ck_bitwidth; // L1_pma_rxdiv_sel; pma_rx_ck_leaf
                                                               // frequency selection
    if ((config.chip_name != VTSS_SD25G28_CHIP_ANT)) {
        if ((config.preset == VTSS_SD25G28_ZR) || (config.preset == VTSS_SD25G28_10GDAC5M) ||
            (config.preset == VTSS_SD25G28_KR_HW)) {
            VTSS_E(
                "vtss_calc_sd25g28_setup_lane: Smart Control presets are not supported for the current Device");
        }
    }

    switch (config.preset) {
    case VTSS_SD25G28_10GSR: // ffe related signals
        preset.ln_cfg_en_adv = 1;
        preset.ln_cfg_en_main = 1;
        preset.ln_cfg_en_dly = 1;
        preset.ln_cfg_tap_adv_3_0 = 0;
        preset.ln_cfg_tap_main = 1;
        preset.ln_cfg_tap_dly_4_0 = 0x10;

        // ctle related signals

        preset.ln_cfg_eqC_force_3_0 = 0xf;
        preset.ln_cfg_vga_ctrl_byp_4_0 = 8;
        preset.ln_cfg_eqR_force_3_0 = 4;
        mode_args->dfe_enable = 0;
        preset.ln_cfg_alos_thr_2_0 = 0;

        break;
    case VTSS_SD25G28_10GDAC3M: // ffe related signals
        preset.ln_cfg_en_adv = 0;
        preset.ln_cfg_en_main = 1;
        preset.ln_cfg_en_dly = 0;
        preset.ln_cfg_tap_adv_3_0 = 0;
        preset.ln_cfg_tap_main = 1;
        preset.ln_cfg_tap_dly_4_0 = 0;

        // ctle related signals
        preset.ln_cfg_eqC_force_3_0 = 7;
        preset.ln_cfg_vga_ctrl_byp_4_0 = 10;
        preset.ln_cfg_eqR_force_3_0 = 7;
        preset.ln_cfg_alos_thr_2_0 = 0;

        break;
    case VTSS_SD25G28_10GDAC5M: // ffe related signals,NOT Tested
        preset.ln_cfg_en_adv = 0;
        preset.ln_cfg_en_main = 1;
        preset.ln_cfg_en_dly = 0;
        preset.ln_cfg_tap_adv_3_0 = 0;
        preset.ln_cfg_tap_main = 1;
        preset.ln_cfg_tap_dly_4_0 = 0;

        // ctle related signals

        preset.ln_cfg_eqC_force_3_0 = 7;
        preset.ln_cfg_vga_ctrl_byp_4_0 = 10;
        preset.ln_cfg_eqR_force_3_0 = 7;
        preset.ln_cfg_alos_thr_2_0 = 0;
        break;

    case VTSS_SD25G28_10GDAC1M: // ffe related signals,NOT Tested
        preset.ln_cfg_en_adv = 0;
        preset.ln_cfg_en_main = 1;
        preset.ln_cfg_en_dly = 0;
        preset.ln_cfg_tap_adv_3_0 = 0;
        preset.ln_cfg_tap_main = 1;
        preset.ln_cfg_tap_dly_4_0 = 0;

        // ctle related signals

        preset.ln_cfg_eqC_force_3_0 = 0xf;
        preset.ln_cfg_vga_ctrl_byp_4_0 = 8;
        preset.ln_cfg_eqR_force_3_0 = 0xc;
        preset.ln_cfg_alos_thr_2_0 = 0;

        break;
    case VTSS_SD25G28_10GDAC3M_PVT: // ffe related signals
        preset.ln_cfg_en_adv = 0;
        preset.ln_cfg_en_main = 1;
        preset.ln_cfg_en_dly = 0;
        preset.ln_cfg_tap_adv_3_0 = 0;
        preset.ln_cfg_tap_main = 1;
        preset.ln_cfg_tap_dly_4_0 = 0;

        // ctle related signals
        preset.ln_cfg_eqC_force_3_0 = 15; // pvt setup value 15, values work fine for stc 10 10 10 7
        preset.ln_cfg_vga_ctrl_byp_4_0 =
            4; // pvt setup value 4,  values work fine for stc 4  4  8  10
        preset.ln_cfg_eqR_force_3_0 = 12; // pvt setup value 12, values work fine for stc 2  3  6  7
        preset.ln_cfg_alos_thr_2_0 = 0;
        break;

    case VTSS_SD25G28_25GDAC2M: // ffe related signals,NOT Tested
        preset.ln_cfg_en_adv = 1;
        preset.ln_cfg_en_main = 1;
        preset.ln_cfg_en_dly = 1;
        preset.ln_cfg_tap_adv_3_0 = 0x8;
        preset.ln_cfg_tap_main = 1;
        preset.ln_cfg_tap_dly_4_0 = 0x12;

        // ctle related signals

        preset.ln_cfg_eqC_force_3_0 = 0x0;
        preset.ln_cfg_vga_ctrl_byp_4_0 = 0xf;
        preset.ln_cfg_eqR_force_3_0 = 0xf;
        preset.ln_cfg_alos_thr_2_0 = 0;

        break;

    case VTSS_SD25G28_25GSR: // ffe related signals,NOT Tested
        preset.ln_cfg_en_adv = 1;
        preset.ln_cfg_en_main = 1;
        preset.ln_cfg_en_dly = 1;
        preset.ln_cfg_tap_adv_3_0 = 0x8;
        preset.ln_cfg_tap_main = 1;
        preset.ln_cfg_tap_dly_4_0 = 0x12;
        preset.ln_cfg_alos_thr_2_0 = 0;

        // ctle related signals

        preset.ln_cfg_eqC_force_3_0 = 0x0;
        preset.ln_cfg_vga_ctrl_byp_4_0 = 0xf;
        preset.ln_cfg_eqR_force_3_0 = 0xf;
        mode_args->dfe_enable = 1;

        break;

    default: // ffe related signals
        preset.ln_cfg_en_adv = 0;
        preset.ln_cfg_en_main = 1;
        preset.ln_cfg_en_dly = 0;
        preset.ln_cfg_tap_adv_3_0 = 0;
        preset.ln_cfg_tap_main = 1;
        preset.ln_cfg_tap_dly_4_0 = 0;

        // ctle related signals

        preset.ln_cfg_eqC_force_3_0 = 0xf;
        preset.ln_cfg_vga_ctrl_byp_4_0 = 4;
        preset.ln_cfg_eqR_force_3_0 = 12;
        preset.ln_cfg_alos_thr_2_0 = 7;

        break;
    }

    ret_val->ln_cfg_tx_subrate_2_0[0] =
        mode_args->subrate; // L1_tx_rate_sel; pma_tx_ck_src full/subrate frequency
                            // selection; 00:full;01:1/2; 10:1/4; 11:1/8
    ret_val->ln_cfg_rx_subrate_2_0[0] = mode_args->subrate; // L1_rx_rate_sel; ln_pma_rx_ck
                                                            // full/subrate frequency selection;
    ret_val->r_multi_lane_mode[0] = 0U;
    ret_val->ln_cfg_cdrck_en[0] = 1U;                     // L1_pcs2pma_power_ctrl[0]
    ret_val->ln_cfg_dfeck_en[0] = mode_args->dfe_enable; // L1_pcs2pma_power_ctrl[1]
    // ret_val->ln_cfg_dfe_pd[0]   = 1;//L1_pcs2pma_power_ctrl[2]
    ret_val->ln_cfg_dfe_pd[0] = (mode_args->dfe_enable == 1U) ? 0U : 1U;
    ret_val->ln_cfg_dfedmx_pd[0] = 1U; // L1_pcs2pma_power_ctrl[3]
    ret_val->ln_cfg_dfetap_en_5_1[0] = mode_args->dfe_tap;
    ret_val->ln_cfg_dmux_pd[0] = 0U;     // L1_pcs2pma_power_ctrl[9]
    ret_val->ln_cfg_dmux_clk_pd[0] = 1U; // L1_pcs2pma_power_ctrl[10] change CTS 07/06/2019
    ret_val->ln_cfg_erramp_pd[0] = (mode_args->dfe_enable == 1U) ? 0U : 1U;
    ret_val->ln_cfg_pi_DFE_en[0] = mode_args->dfe_enable;
    ret_val->ln_cfg_pi_en[0] = 1U;      // L1_pcs2pma_power_ctrl[13]
    ret_val->ln_cfg_pd_ctle[0] = 0U;    // L1_pcs2pma_power_ctrl[14]
    ret_val->ln_cfg_summer_en[0] = 1U;  // L1_pcs2pma_power_ctrl[15]
    ret_val->ln_cfg_pmad_ck_pd[0] = 0U; // L1_pcs2pma_power_ctrl[16]
    ret_val->ln_cfg_pd_clk[0] = 0U;     // L1_pcs2pma_power_ctrl[17]
    ret_val->ln_cfg_pd_cml[0] = 0U;     // L1_pcs2pma_power_ctrl[18]
    ret_val->ln_cfg_pd_driver[0] = 0U;  // L1_pcs2pma_power_ctrl[19]
    ret_val->ln_cfg_rx_reg_pu[0] = 1U;  // L1_pcs2pma_power_ctrl[20]
    ret_val->ln_cfg_pd_rms_det[0] = 1U; // L1_pcs2pma_power_ctrl[21]
    ret_val->ln_cfg_dcdr_pd[0] = 0U;    // L1_pcs2pma_power_ctrl[22]
    ret_val->ln_cfg_ecdr_pd[0] = 1U;    // L1_pcs2pma_power_ctrl[23] change CTS 07/06/2019
    ret_val->ln_cfg_pd_sq[0] = 1U;      // L1_pcs2pma_power_ctrl[24]
    // TODO txswing related reg values this could depend on media, board and Si
    // ret_val->ln_cfg_itx_ipdriver_base_2_0[0]   = ((config.txswing)>>6);
    // //L1_pcs2pma_txmargin; used in KR/CR: Transmitter voltage level control
    ret_val->ln_cfg_itx_ipdriver_base_2_0[0] =
        mode_args->txmargin; // L1_pcs2pma_txmargin; used in KR/CR: Transmitter
                             // voltage level control
    // ret_val->ln_cfg_tap_dly_4_0[0]   = mode_args->tx_tap_dly; //
    // L1_pcs_tap_dly; pcs link train control
    ret_val->ln_cfg_tap_dly_4_0[0] = preset.ln_cfg_tap_dly_4_0;
    // ret_val->ln_cfg_tap_main[0]   =                            1; //similar;
    // PCS link train control
    ret_val->ln_cfg_tap_main[0] = preset.ln_cfg_tap_main;
    // ret_val->ln_cfg_en_main[0]   =                             1;
    // //similar;PCS link train control
    ret_val->ln_cfg_en_main[0] = preset.ln_cfg_en_main;
    // ret_val->ln_cfg_tap_adv_3_0[0]   = mode_args->tx_tap_adv ; //similar;PCS
    // link train control
    ret_val->ln_cfg_tap_adv_3_0[0] = preset.ln_cfg_tap_adv_3_0;
    // ret_val->ln_cfg_en_adv[0]   = (mode_args->tx_tap_adv > 0) ? 1: 0 ;
    // //similar;PCS link train control
    ret_val->ln_cfg_en_adv[0] = preset.ln_cfg_en_adv;
    // ret_val->ln_cfg_en_dly[0]   = (mode_args->tx_tap_dly > 0) ? 1: 0 ;
    // //similar;PCS link train control
    ret_val->ln_cfg_en_dly[0] = preset.ln_cfg_en_dly;
    ret_val->ln_cfg_iscan_en[0] = 0U;
    ret_val->l1_pcs_en_fast_iscan[0] = 0U;
    ret_val->l0_cfg_bw_1_0[0] = 0U;
    ret_val->cfg_en_dummy[0] = 0U;
    ret_val->cfg_pll_reserve_3_0[0] = mode_args->com_pll_reserve;
    ret_val->l0_cfg_txcal_en[0] = mode_args->com_txcal_en;
    ret_val->l0_cfg_tx_reserve_15_8[0] = mode_args->com_tx_reserve_msb;
    ret_val->l0_cfg_tx_reserve_7_0[0] = mode_args->com_tx_reserve_lsb;
    ret_val->ln_cfg_tx_reserve_15_8[0] = mode_args->ln_tx_reserve_msb;
    ret_val->ln_cfg_tx_reserve_7_0[0] = mode_args->ln_tx_reserve_lsb;
    ret_val->ln_cfg_bw_1_0[0] = mode_args->ln_bw;
    ret_val->ln_cfg_txcal_man_en[0] = 1U;
    ret_val->ln_cfg_phase_man_4_0[0] = 0U;
    ret_val->ln_cfg_quad_man_1_0[0] = 0U;
    ret_val->ln_cfg_txcal_shift_code_5_0[0] = 2U;
    ret_val->ln_cfg_txcal_valid_sel_3_0[0] = 4U;
    ret_val->ln_cfg_txcal_en[0] = 0U;
    ret_val->ln_cfg_cdr_kf_2_0[0] = 1U;
    ret_val->ln_cfg_cdr_m_7_0[0] = mode_args->ln_cfg_cdr_m_7_0;
    ret_val->ln_cfg_pi_bw_3_0[0] = mode_args->ln_cfg_pi_bw_3_0;
    // ret_val->ln_cfg_pi_bw_3_0[0]   =                           0;//Changed
    // from 0 to 6 CTS 07/06/2019
    ret_val->ln_cfg_pi_steps_1_0[0] = 0U;
    ret_val->ln_cfg_dis_2ndorder[0] = mode_args->ln_cfg_dis_2ndorder;
    ret_val->ln_cfg_filter2nd_yz_6_0[0] = mode_args->ln_cfg_filter2nd_yz_6_0;
    ret_val->ln_cfg_ctle_rstn[0] = mode_args->ln_cfg_ctle_rstn;
    ret_val->ln_r_dfe_rstn[0] = mode_args->ln_r_dfe_rstn;
    ret_val->ln_cfg_alos_thr_2_0[0] = preset.ln_cfg_alos_thr_2_0; // was 7
    ret_val->ln_cfg_itx_ipcml_base_1_0[0] = mode_args->ln_cfg_itx_ipcml_base;
    ret_val->ln_cfg_rx_reserve_7_0[0] = 0xbfU;
    ret_val->ln_cfg_rx_reserve_15_8[0] = 0x61U;
    ret_val->ln_cfg_rxterm_2_0[0] = mode_args->ln_rxterm;
    ret_val->cfg_fom_selm[0] = 0U;
    ret_val->ln_cfg_rx_sp_ctle_1_0[0] = 0U;
    ret_val->ln_cfg_isel_ctle_1_0[0] = 0U;
    // ret_val->ln_cfg_vga_ctrl_byp_4_0[0]   =                    4;
    ret_val->ln_cfg_vga_ctrl_byp_4_0[0] = preset.ln_cfg_vga_ctrl_byp_4_0;
    ret_val->ln_cfg_vga_byp[0] = 1U;
    // ret_val->ln_cfg_rx_reserve_7_0[0]   =                    (1<<7);// [7] 1;
    // this is configured in CDR as well
    ret_val->ln_cfg_rx_reserve_15_8[0] = 0x61U;
    ret_val->ln_cfg_agc_adpt_byp[0] = 1U;
    ret_val->ln_cfg_eqr_byp[0] = 1U;
    // ret_val->ln_cfg_eqr_force_3_0[0]   =                       12;
    ret_val->ln_cfg_eqr_force_3_0[0] = preset.ln_cfg_eqR_force_3_0;
    // ret_val->ln_cfg_eqc_force_3_0[0]   =                       0xf;
    ret_val->ln_cfg_eqc_force_3_0[0] = preset.ln_cfg_eqC_force_3_0;
    ret_val->ln_cfg_sum_setcm_en[0] = 1U;
    ret_val->ln_cfg_pi_dfe_en[0] = 1U;
    ret_val->ln_cfg_pi_en[0] = 1U;
    ret_val->ln_cfg_init_pos_iscan_6_0[0] = 6U;
    ret_val->ln_cfg_init_pos_ipi_6_0[0] = 9U;
    ret_val->ln_cfg_dfedig_m_2_0[0] = 6U;
    ret_val->ln_cfg_en_dfedig[0] = mode_args->dfe_enable;
    ret_val->ln_cfg_rstn_dfedig[0] = 0U;
    ret_val->ln_cfg_rstn_dfedig[1] = 1U;
    // cfg control table2.1-3
    ret_val->r_DwidthCtrl_from_hwt[0] = (config.reg_ctrl == 0U) ? 1U : 0U;
    ret_val->r_reg_manual[0] = config.reg_ctrl;
    ret_val->reg_ctrl[0] = config.reg_ctrl;
    ret_val->reg_rst[0] = config.reg_rst;
    ret_val->cfg_jc_byp[0] = 0x1U; // As per CTS: 0: Use INTCML CK/CKB; 1: for external clock
    ret_val->cfg_common_reserve_7_0[0] =
        0x1U;                           // Resistor termination disabled for all 25G Serdes in FA
    ret_val->cfg_pll_lol_set[0] = 0x1U; // loss of lock enable/disable control

    if (config.master_loop == VTSS_SD25G28_LM1) {
        ret_val->ln_cfg_tx2rx_lp_en[0] = 1U;
        ret_val->ln_cfg_txlb_en[0] = 1U;
    } else if (config.master_loop == VTSS_SD25G28_MASTER_LOOP_NONE) {
        ret_val->ln_cfg_tx2rx_lp_en[0] = 0U;
        ret_val->ln_cfg_txlb_en[0] = 0U;
    } else {
        VTSS_D("MISRA Non empty else");
    }

    if (config.slave_loop == VTSS_SD25G28_LS1 &&
        config.master_loop == VTSS_SD25G28_MASTER_LOOP_NONE) {
        ret_val->ln_cfg_rx2tx_lp_en[0] = 1U; // LS1
        ret_val->ln_cfg_rxlb_en[0] = 1U;
        ret_val->ln_cfg_cdrck_en[0] = 0U;
    } else if (config.slave_loop == VTSS_SD25G28_LS2 &&
               config.master_loop == VTSS_SD25G28_MASTER_LOOP_NONE) {
        ret_val->ln_cfg_rx2tx_lp_en[0] = 1U; // LS2
        ret_val->ln_cfg_rxlb_en[0] = 1U;
        ret_val->ln_cfg_cdrck_en[0] = 1U;
    } else if (config.slave_loop == VTSS_SD25G28_SLAVE_LOOP_NONE) {
        ret_val->ln_cfg_rx2tx_lp_en[0] = 0U; // LS1
        ret_val->ln_cfg_rxlb_en[0] = 0U;
        ret_val->ln_cfg_cdrck_en[0] = 1U;
    } else {
        VTSS_D("MISRA Non empty else");
    }
    // TX invert
    if (config.txinvert) {
        ret_val->ln_r_tx_pol_inv[0] = 1U;
    } else {
        ret_val->ln_r_tx_pol_inv[0] = 0U;
    }
    // RX invert
    if (config.rxinvert) {
        ret_val->ln_r_rx_pol_inv[0] = 1U;
    } else {
        ret_val->ln_r_rx_pol_inv[0] = 0U;
    }

    return rslt;
}
/*
vtss_rc vtss_calc_sd25g28_lane_pwr_down (vtss_sd25g28_lane_pwr_down_t *const
ret_val) {

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


vtss_rc vtss_calc_sd25g28_cmu_pwr_down(vtss_sd25g28_cmu_pwr_down_t *const
ret_val) {

    ret_val->cfg_ctrl_logic_pd[0]                   =  1 ;
    ret_val->cfg_vco_pd[0]                          =  1 ;
    ret_val->cfg_en_dummy[0]                        =  0 ;
    ret_val->cfg_ck_tree_pd[0]                      =  1 ;
    ret_val->cfg_rst_tree_pd_man[0]                 =  1 ;
    ret_val->cfg_en_tx_ck_up[0]                     =  0 ;
    ret_val->cfg_en_tx_ck_dn[0]                     =  0 ;
    ret_val->cfg_pd_div64[0]                        =  1 ;
    ret_val->cfg_pd_div66[0]                        =  1 ;
    ret_val->cfg_pma_tx_ck_pd[0]                    =  1 ;
    ret_val->cfg_link_buf_en[0]                     =  0 ;
    ret_val->cfg_refck_ssc_en[0]                    =  0 ;
    ret_val->cfg_refck_term_en[0]                   =  0 ;
    ret_val->cfg_refck_pd[0]                        =  1 ;
    ret_val->cfg_ibias_pd[0]                        =  1 ;
    ret_val->cfg_bias_dn_en[0]                      =  0 ;
    ret_val->cfg_bias_up_en[0]                      =  0 ;


    return VTSS_RC_OK;
}
*/

/* ********************************************************************************
 */
/* ***                        E N D   O F    F I L E *** */
/* ********************************************************************************
 */
