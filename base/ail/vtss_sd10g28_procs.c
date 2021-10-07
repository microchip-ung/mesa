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

#include "vtss_sd10g28_procs.h"

static u8 to_u8(const BOOL in) {
    if (in == TRUE) {
        return 1;
    } else {
        return 0;
    }
}

/* function to map from SD10G28 interface width to configuration value */
static u8   sd10g28_get_iw_setting(const u8     interface_width) {
    VTSS_D(" sd10g28_get_iw_setting:  Interface width is %d bits \n", interface_width);
    switch (interface_width) {
        case 10: {
            return 0;
        }
        case 16: {
            return 1;
        }
        case 20: {
            return 2;
        }
        case 32: {
            return 3;
        }
        case 40: {
            return 4;
        }
        case 64: {
            return 7;
        }
        default : {
            VTSS_E("Illegal value %d for interface width\n", interface_width);
            return 0;
        }
    }
}

vtss_rc vtss_sd10g28_get_conf_from_mode(BOOL is_6g, vtss_sd10g28_mode_t        f_mode,
                                           vtss_sd10g28_mode_args_t *const ret_val) {

    switch(f_mode) {
      case VTSS_SD10G28_MODE_10G_QSXGMII : 
      case VTSS_SD10G28_MODE_10G_DSXGMII : {
        //ret_val->datarate = 10.3125e9;
        ret_val->bitwidth = sd10g28_get_iw_setting(32); //usgmii_ext and usxgmii_ext_rx_to_64
        ret_val->cmu_sel  = VTSS_SD10G28_MAIN; //MAIN CMU
        ret_val->rate=0x0; 
        ret_val->dfe_enable=1;
        ret_val->dfe_tap=0x1f;
        ret_val->pi_bw_gen1=0x0;
        ret_val->duty_cycle=0x2;
        VTSS_D ("Mode is Q(D)SXGMII\n");
        break;
        }
      case VTSS_SD10G28_MODE_10G_ETH :
      case VTSS_SD10G28_MODE_10G_LAN :   {
        //ret_val->datarate= 10.3125e9;
        //ret_val->bitwidth 64; //10G Devices
        ret_val->bitwidth = sd10g28_get_iw_setting(64); 
        ret_val->cmu_sel= VTSS_SD10G28_MAIN ;//MAIN CMU
        ret_val->rate= 0x0; 
        ret_val->dfe_enable= 1;
        ret_val->dfe_tap= 0x1f;
        ret_val->pi_bw_gen1= 0x0;
        ret_val->duty_cycle= 0x2 ;
        VTSS_D ("Mode is 10G_LAN/ETH\n");
        break;
      }
      case VTSS_SD10G28_MODE_5G_LAN :  {
        //ret_val->datarate= 5.15625e9;
        if (is_6g) {
          //ret_val->bitwidth 16; // usxgmii_ext_tx_from_64 in 5G Mode 
          ret_val->bitwidth = sd10g28_get_iw_setting(16); 
        } else {
          //ret_val->bitwidth 64; // 10G DEV in 5G Mode 
        ret_val->bitwidth = sd10g28_get_iw_setting(64); 
        }
        ret_val->cmu_sel= VTSS_SD10G28_MAIN;//MAIN CMU
        ret_val->rate= 0x1; 
        ret_val->dfe_enable= 0;
        ret_val->dfe_tap= 0;
        ret_val->pi_bw_gen1= 0x5;
        ret_val->duty_cycle= 0x0 ;
        VTSS_D ("Mode is 5G_LAN/ETH\n");
        break;
      }
      case VTSS_SD10G28_MODE_5G_USXGMII :   {
        //ret_val->datarate= 5.15625e9;
        //ret_val->bitwidth 16; //this has usxgmii_ext_tx_from_64 and rx_to_64 blocks between serdes and usxgmii_ext
                         //which converts 16bit  (serdes)<-> 64bit (Devices)
        ret_val->bitwidth = sd10g28_get_iw_setting(16); //this has usxgmii_ext_tx_from_64 and rx_to_64 blocks between serdes and usxgmii_ext
                                                        //which converts 16bit  (serdes)<-> 64bit (Devices)
        ret_val->cmu_sel= VTSS_SD10G28_MAIN; //MAIN CMU
        ret_val->rate =0x1; 
        ret_val->dfe_enable= 0;
        ret_val->dfe_tap= 0;
        ret_val->pi_bw_gen1= 0x5;
        ret_val->duty_cycle= 0x0 ;
        VTSS_D ("Mode is USXGMII5G\n");
        break;
      }
      case VTSS_SD10G28_MODE_10G_USGMII :   {
        //ret_val->datarate= 10e9;
        ret_val->bitwidth = sd10g28_get_iw_setting(20); 
        ret_val->cmu_sel= VTSS_SD10G28_AUX1;// AUX1 CMU
        ret_val->rate= 0x0; 
        ret_val->dfe_enable= 1;
        ret_val->dfe_tap= 0x1f;
        ret_val->pi_bw_gen1= 0x0;
        ret_val->duty_cycle= 0x2 ;
        VTSS_D ("Mode is 10G_USGMII\n");
        break;
      }
      case VTSS_SD10G28_MODE_QSGMII :   {
        //ret_val->datarate= 5e9;
        ret_val->bitwidth = sd10g28_get_iw_setting(20); 
        ret_val->cmu_sel= VTSS_SD10G28_AUX1; // AUX1 CMU
        ret_val->rate= 0x1; 
        ret_val->dfe_enable= 0;
        ret_val->dfe_tap= 0;
        ret_val->pi_bw_gen1= 0x5;
        ret_val->duty_cycle= 0x0 ;
        VTSS_D ("Mode is QSGMII\n");
        break;
      }
      case VTSS_SD10G28_MODE_SGMII2G5 :   {
        //ret_val->datarate= 3.125e9;
        //ret_val->bitwidth 10; // DEV2G5
        ret_val->bitwidth = sd10g28_get_iw_setting(10); 
        ret_val->cmu_sel= VTSS_SD10G28_AUX2; //AUX2 CMU
        ret_val->rate= 0x2; 
        ret_val->dfe_enable= 0;
        ret_val->dfe_tap= 0;
        ret_val->pi_bw_gen1= 0x7;
        ret_val->duty_cycle= 0x0 ;
        VTSS_D ("Mode is SGMII2G5\n");
        break;
      }
      case VTSS_SD10G28_MODE_FX100 :
      case VTSS_SD10G28_MODE_SGMII : 
      case VTSS_SD10G28_MODE_1G_LAN :   {
        //ret_val->datarate= 1.25e9;
        //ret_val->bitwidth 10;
        ret_val->bitwidth = sd10g28_get_iw_setting(10); 
        ret_val->cmu_sel= VTSS_SD10G28_AUX1; // AUX1 CMU
        ret_val->rate= 0x3; 
        ret_val->dfe_enable= 0;
        ret_val->dfe_tap= 0;
        ret_val->pi_bw_gen1= 0x7; //SBCHG 7->9
        ret_val->duty_cycle= 0x0 ;
        VTSS_D ("Mode is SGMII/1G LAN\n");
        break;
      }
      default :   {
        VTSS_E("vtss_sd10g28_get_conf_from_mode: invalid parameter value for f_mode\n");
        // 10.3125Gbps
        //ret_val->datarate= 10.3125e9;
        //ret_val->bitwidth 64; //10G Devices
        ret_val->bitwidth = sd10g28_get_iw_setting(64); 
        ret_val->cmu_sel= VTSS_SD10G28_MAIN ;//MAIN CMU
        ret_val->rate= 0x0; 
        ret_val->dfe_enable= 1;
        ret_val->dfe_tap= 0x1f;
        ret_val->pi_bw_gen1= 0x0;
        ret_val->duty_cycle= 0x2 ;
        VTSS_D ("Mode is Default: 10G_LAN\n");
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
 ***                   vtss_calc_sd10g28_setup_lane                                  ***
 ********************************************************************************/
vtss_rc vtss_calc_sd10g28_setup_lane (const vtss_sd10g28_setup_args_t config,
                                   vtss_sd10g28_setup_struct_t     *const ret_val) {

    vtss_rc          rslt;
    //vtss_sd10g28_mode_args_t *mode_args = (vtss_sd10g28_mode_args_t*)malloc(sizeof(vtss_sd10g28_mode_args_t));
    vtss_sd10g28_mode_args_t sd10g28_mode;
    vtss_sd10g28_mode_args_t *mode_args = &sd10g28_mode;

    u8 cmu;
    vtss_sd10g28_preset_struct_t preset;

    rslt = VTSS_RC_OK;

    rslt = vtss_sd10g28_get_conf_from_mode(config.is_6g, config.mode, mode_args);

    ret_val->skip_cmu_cfg[0]                   = to_u8(config.skip_cmu_cfg);
    ret_val->is_6g[0]                          = to_u8(config.is_6g);

    if (mode_args->cmu_sel == VTSS_SD10G28_MAIN) {
      ret_val->cmu_sel[0] = 0;
    } else if (mode_args->cmu_sel == VTSS_SD10G28_AUX1) {
      ret_val->cmu_sel[0] = 1;
    } else if (mode_args->cmu_sel == VTSS_SD10G28_AUX2) {
      ret_val->cmu_sel[0] = 3;
    }
    cmu = ret_val->cmu_sel[0];
    ret_val->cfg_lane_reserve_7_0[0]        =   (cmu%2)<<6 ;  // LSB:
    ret_val->cfg_ssc_rtl_clk_sel[0]        =   (cmu/2) ;  // MSB:
    ret_val->cfg_lane_reserve_15_8[0]       =   mode_args->duty_cycle ; //Bit 9 controls Duty cycle; Silicon Dependend this needs to be corrected
      
    //r_DwidthCtrl_from_hwt related signals
    //TX and RX rate selection towards network interface									   
    ret_val->cfg_txrate_1_0[0]              =   mode_args->rate;
    ret_val->cfg_rxrate_1_0[0]              =   mode_args->rate;

    ret_val->fx_100[0]                      =   config.mode == VTSS_SD10G28_MODE_FX100;
      
    //UDL interface configuration bitwidth, tx and rx clock selection, phymode selection 
    ret_val->r_DwidthCtrl_2_0[0]            = mode_args->bitwidth;
    ret_val->cfg_pma_tx_ck_bitwidth_2_0[0]  = mode_args->bitwidth;
    ret_val->cfg_rxdiv_sel_2_0[0]           = mode_args->bitwidth;
    
    ret_val->r_pcs2pma_phymode_4_0[0]       = 0;
      
    ret_val->cfg_lane_id_2_0[0]             = 0;//  Bias Trace Selection
    if ((config.chip_name != VTSS_SD10G28_CHIP_ANT)) {
      if ((config.preset == VTSS_SD10G28_ZR) ||
          (config.preset == VTSS_SD10G28_DAC5M) ||
          (config.preset == VTSS_SD10G28_KR) ) {
        VTSS_E("vtss_calc_sd10g28_setup_lane: Smart Control presets are not supported for the current Device");
      }
    }

    switch(config.preset) {
      case VTSS_SD10G28_SR           : //r_txeq_reg related signals
                                        preset.cfg_en_adv                  = 1;
                                        preset.cfg_en_main                 = 1;
                                        preset.cfg_en_dly                  = 1;
                                        preset.cfg_tap_adv_3_0             = 0;
                                        preset.cfg_tap_main                = 1;
                                        preset.cfg_tap_dly_4_0             = 0xc;
                                        //r_rxeq_reg related signals 
                                        preset.cfg_vga_ctrl_3_0            = 0xa      ;
                                        preset.cfg_vga_cp_2_0              = 0x4      ;
                                        preset.cfg_eq_res_3_0              = 0xa    ;    //CTLE gain control. 
                                        preset.cfg_eqR_byp                 = 1      ;
                                        preset.cfg_eqC_force_3_0           = 0xF    ;
                                        mode_args->dfe_enable              = 0;
                                        preset.cfg_alos_thr_3_0            = 0x3    ;
                                        break;
      case VTSS_SD10G28_DAC3M        : //r_txeq_reg related signals
                                        preset.cfg_en_adv                  = 1;  
                                        preset.cfg_en_main                 = 1;  
                                        preset.cfg_en_dly                  = 1;  
                                        preset.cfg_tap_adv_3_0             = 12;  
                                        preset.cfg_tap_main                = 1;  
                                        preset.cfg_tap_dly_4_0             = 8;  
                                        //r_rxeq_reg related signals 
                                        preset.cfg_vga_ctrl_3_0            = 0xa    ;
                                        preset.cfg_vga_cp_2_0              = 4      ;
                                        preset.cfg_eq_res_3_0              = 0xa    ;    //CTLE gain control. 
                                        preset.cfg_eqR_byp                 = 1      ;
                                        preset.cfg_eqC_force_3_0           = 0xf    ;
                                        preset.cfg_alos_thr_3_0            = 0x0    ;
                                        break;
      case VTSS_SD10G28_DAC1M        : //r_txeq_reg related signals :Not Tested
                                        preset.cfg_en_adv                  = 1;
                                        preset.cfg_en_main                 = 1;
                                        preset.cfg_en_dly                  = 1;
                                        preset.cfg_tap_adv_3_0             = 0;
                                        preset.cfg_tap_main                = 1;
                                        preset.cfg_tap_dly_4_0             = 0xC;
                                        //r_rxeq_reg related signals
                                        preset.cfg_vga_ctrl_3_0            = 0xa      ;
                                        preset.cfg_vga_cp_2_0              = 0x4      ;
                                        preset.cfg_eq_res_3_0              = 0xa    ;    //CTLE gain control. 
                                        preset.cfg_eqR_byp                 = 1      ;
                                        preset.cfg_eqC_force_3_0           = 0xf    ;
                                        preset.cfg_alos_thr_3_0            = 0x0    ;
                                        break;
      case VTSS_SD10G28_DAC2M        : //r_txeq_reg related signals :Not Tested
                                        preset.cfg_en_adv                  = 1;
                                        preset.cfg_en_main                 = 1;
                                        preset.cfg_en_dly                  = 1;
                                        preset.cfg_tap_adv_3_0             = 0;
                                        preset.cfg_tap_main                = 1;
                                        preset.cfg_tap_dly_4_0             = 0xC;
                                        //r_rxeq_reg related signals
                                        preset.cfg_vga_ctrl_3_0            = 0xa      ;
                                        preset.cfg_vga_cp_2_0              = 0x4      ;
                                        preset.cfg_eq_res_3_0              = 0xa    ;    //CTLE gain control. 
                                        preset.cfg_eqR_byp                 = 1      ;
                                        preset.cfg_eqC_force_3_0           = 0xf    ;
                                        preset.cfg_alos_thr_3_0            = 0x0    ;

                                        break;

      case VTSS_SD10G28_DAC5M        : //r_txeq_reg related signals :Not Tested
                                        preset.cfg_en_adv                  = 1;
                                        preset.cfg_en_main                 = 1;
                                        preset.cfg_en_dly                  = 1;
                                        preset.cfg_tap_adv_3_0             = 0;
                                        preset.cfg_tap_main                = 1;
                                        preset.cfg_tap_dly_4_0             = 0xC;
                                        //r_rxeq_reg related signals
                                        preset.cfg_vga_ctrl_3_0            = 0xa      ;
                                        preset.cfg_vga_cp_2_0              = 0x4    ;
                                        preset.cfg_eq_res_3_0              = 0xa    ;    //CTLE gain control. 
                                        preset.cfg_eqR_byp                 = 1      ;
                                        preset.cfg_eqC_force_3_0           = 0xf    ;
                                        preset.cfg_alos_thr_3_0            = 0x0    ;

                                        break;
      case VTSS_SD10G28_DAC3M_PVT     : //r_txeq_reg related signals
                                        preset.cfg_en_adv                  = 1;  
                                        preset.cfg_en_main                 = 1;  
                                        preset.cfg_en_dly                  = 1;  
                                        preset.cfg_tap_adv_3_0             = 12;  
                                        preset.cfg_tap_main                = 1;  
                                        preset.cfg_tap_dly_4_0             = 8;  
                                        //r_rxeq_reg related signals 
                                        preset.cfg_vga_ctrl_3_0            = 0xa    ;
                                        preset.cfg_vga_cp_2_0              = 4      ;
                                        preset.cfg_eq_res_3_0              = 0xa    ;    //CTLE gain control. 
                                        preset.cfg_eqR_byp                 = 1      ;
                                        preset.cfg_eqC_force_3_0           = 0xf    ;
                                        preset.cfg_alos_thr_3_0            = 0x0    ;
                                        break;

      case VTSS_SD10G28_FX100        : //r_txeq_reg related signals
                                        preset.cfg_en_adv                  = 0;
                                        preset.cfg_en_main                 = 1;
                                        preset.cfg_en_dly                  = 0;
                                        preset.cfg_tap_adv_3_0             = 0;
                                        preset.cfg_tap_main                = 1;
                                        preset.cfg_tap_dly_4_0             = 0;
                                        //r_rxeq_reg related signals
                                        preset.cfg_vga_ctrl_3_0            = 0xa      ;
                                        preset.cfg_vga_cp_2_0              = 0      ;
                                        preset.cfg_eq_res_3_0              = 0x2    ;    //CTLE gain control.
                                        preset.cfg_eqR_byp                 = 1      ;
                                        preset.cfg_eqC_force_3_0           = 0x8    ;
                                        preset.cfg_alos_thr_3_0            = 0x3    ;
                                        break;

                                        
      default                        : //r_txeq_reg related signals
                                        preset.cfg_en_adv                  = 0;
                                        preset.cfg_en_main                 = 1;
                                        preset.cfg_en_dly                  = 0;
                                        preset.cfg_tap_adv_3_0             = 0;
                                        preset.cfg_tap_main                = 1;
                                        preset.cfg_tap_dly_4_0             = 0;
                                        //r_rxeq_reg related signals
                                        preset.cfg_vga_ctrl_3_0            = 5      ;
                                        preset.cfg_vga_cp_2_0              = 0      ;
                                        preset.cfg_eq_res_3_0              = 0xa    ;    //CTLE gain control.
                                        preset.cfg_eqR_byp                 = 1      ;
                                        preset.cfg_eqC_force_3_0           = 0x8    ;
                                        preset.cfg_alos_thr_3_0            = 0x3    ;
                                        break;
    }

    //r_reg_manual related signals
    ret_val->cfg_cdrck_en[0]                = 1;
    ret_val->cfg_dfeck_en[0]                = mode_args->dfe_enable;
    ret_val->cfg_dfe_pd[0]                  = (mode_args->dfe_enable==1) ? 0: 1;
    ret_val->cfg_dfetap_en_5_1[0]           = mode_args->dfe_tap;
    ret_val->cfg_erramp_pd[0]               = (mode_args->dfe_enable==1) ? 0: 1;
    ret_val->cfg_pi_DFE_en[0]               = mode_args->dfe_enable;
    ret_val->cfg_pi_en[0]                   = 1;
    ret_val->cfg_pd_ctle[0]                 = 0;
    ret_val->cfg_summer_en[0]               = 1;
    ret_val->cfg_pd_rx_cktree[0]            = 0;
    ret_val->cfg_pd_clk[0]                  = 0;
    ret_val->cfg_pd_cml[0]                  = 0;
    ret_val->cfg_pd_driver[0]               = 0;
    ret_val->cfg_rx_reg_pu[0]               = 1;
    ret_val->cfg_Dcdr_pd[0]                 = 0;
    ret_val->cfg_pd_sq[0]                   = mode_args->dfe_enable;
    ret_val->cfg_rxdet_en[0]                = 0;
    ret_val->cfg_rxdet_str[0]               = 0;
    ret_val->r_multi_lane_mode[0]           = 0;
    
    //r_txeq_reg related signals
    ret_val->cfg_en_adv[0]                  = preset.cfg_en_adv;
    ret_val->cfg_en_main[0]                 = 1;
    ret_val->cfg_en_dly[0]                  = preset.cfg_en_dly;
    ret_val->cfg_tap_adv_3_0[0]             = preset.cfg_tap_adv_3_0;
    ret_val->cfg_tap_main[0]                = preset.cfg_tap_main;
    ret_val->cfg_tap_dly_4_0[0]             = preset.cfg_tap_dly_4_0;
    
    //r_rxeq_reg related signals there are for SR and DFE needs to be enabled for LR/MR
    //DFE is enabled for 10G 
    ret_val->cfg_vga_ctrl_3_0[0]            = preset.cfg_vga_ctrl_3_0;
    ret_val->cfg_vga_cp_2_0[0]              = preset.cfg_vga_cp_2_0;
    ret_val->cfg_eq_res_3_0[0]              = preset.cfg_eq_res_3_0;    //CTLE gain control. 
    ret_val->cfg_eqR_byp[0]                 = preset.cfg_eqR_byp;
    ret_val->cfg_eqC_force_3_0[0]           = preset.cfg_eqC_force_3_0;
    ret_val->cfg_en_dfedig[0]               = mode_args->dfe_enable;
    ret_val->cfg_sum_setcm_en[0]            = 1      ;
      
    //r_misc_reg
    ret_val->cfg_en_preemph[0]              = 0;   //Unused in current IP as per Tony 08/29/2018.
    ret_val->cfg_itx_ippreemp_base_1_0[0]   = 0; //Unused in current IP as per Tony 08/29/2018.
      
    //r_swing_reg;
    ret_val->cfg_itx_ipdriver_base_2_0[0]   =  (config.txswing>>6)       ;
    ret_val->cfg_ibias_tune_reserve_5_0[0]  =  (config.txswing&63)       ;
    ret_val->cfg_txswing_half[0]            =  (config.txmargin)        ;
      
    //r_cdr_from_hwt this is cfg controlled. 
    ret_val->cfg_dis_2ndOrder[0]            = 0x1          ;              //  2nd order CDR disable signal.
    ret_val->cfg_rx_ssc_lh[0]               = 0x0          ;              //  CDR operation rate selection 
    ret_val->cfg_pi_floop_steps_1_0[0]      = 0x0          ;             //  Frequency loop PI step selection
    ret_val->cfg_pi_ext_dac_23_16[0]        = (1<<5)  ;     //  2nd order CDR digital lowpass filter select
                                                     
    ret_val->cfg_pi_ext_dac_15_8[0]         = (0<<6)  ;   //  2nd order CDR digital lowpass filter select
    ret_val->cfg_iscan_ext_dac_7_0[0]       = (1<<7)+9  ;     //CDR clock phase tuning parameter; Silicon Dependend;
    
    //RX CDR  and TX driver register Settings
    ret_val->cfg_cdr_kf_gen1_2_0[0]         = 1;   //CDR 1st order Gain Adjust GEN1
    ret_val->cfg_cdr_kf_gen2_2_0[0]         = 1;   //CDR 1st order Gain Adjust GEN2
    ret_val->cfg_cdr_kf_gen3_2_0[0]         = 1;   //CDR 1st order Gain Adjust GEN3
    ret_val->cfg_cdr_kf_gen4_2_0[0]         = 1;   //CDR 1st order Gain Adjust GEN4
    ret_val->r_cdr_m_gen1_7_0[0]            = 4;   //CDR 1st order LP filter select GEN1
    ret_val->cfg_pi_bw_gen1_3_0[0]          = mode_args->pi_bw_gen1;   //CDR PI BW Adj. GEN1 Silicon Dependend   
    ret_val->cfg_pi_bw_gen2[0]              = mode_args->pi_bw_gen1 ;    //CDR PI BW Adj. GEN2
    ret_val->cfg_pi_bw_gen3[0]              = mode_args->pi_bw_gen1;    //CDR PI BW Adj. GEN3
    ret_val->cfg_pi_bw_gen4[0]              = mode_args->pi_bw_gen1;    //CDR PI BW Adj. GEN4
    //ret_val->cfg_iscan_ext_dac_7_0[0]= 9;   //Already configured
    ret_val->cfg_pi_ext_dac_7_0[0]          = 3;   //DFE clock phase tuning parameter; Silicon Dependend;
    ret_val->cfg_pi_steps[0]                = 0;
    ret_val->cfg_mp_max_3_0[0]              = 1   ;
    ret_val->cfg_rstn_dfedig[0]             = mode_args->dfe_enable;    // DFE Reset; it is reset automatically after assert and release of pclk_gating 
      
    ret_val->cfg_alos_thr_3_0[0]            = preset.cfg_alos_thr_3_0;             //Voltage threshold for squelch detection
      
    ret_val->cfg_predrv_slewrate_1_0[0]     = 3;          // ??
    ret_val->cfg_itx_ipcml_base_1_0[0]      = 0;          // predriver current setting in TX
    ret_val->cfg_ip_pre_base_1_0[0]         = 0;          // SBCHG:changed to 0 as per APP note 12/06/2019?? 
      
    ret_val->r_cdr_m_gen2_7_0[0]            = 2;  //  CDR 1st order LP filter select GEN2
    ret_val->r_cdr_m_gen3_7_0[0]            = 2;  //  CDR 1st order LP filter select GEN3
    ret_val->r_cdr_m_gen4_7_0[0]            = 2;  //  CDR 1st order LP filter select GEN4
    
    ret_val->r_en_auto_cdr_rstn[0]          = 0;           //  Lane CDR auto reset function enable
      
    ret_val->cfg_oscal_afe[0]               = ret_val->fx_100[0] ? 0:1;
    ret_val->cfg_pd_osdac_afe[0]            = ret_val->fx_100[0] ? 1:0;
    ret_val->cfg_resetb_oscal_afe[0]        = 0;
    ret_val->cfg_resetb_oscal_afe[1]        = 1;
    
    // TX SSC 
    ret_val->cfg_center_spreading[0]        = 0;  //  Lane SSC type selection
    ret_val->cfg_McntMaxVal_4_0[0]          = 15; //  Lane SSC spreading range contrl
    ret_val->cfg_ncntMaxVal_7_0[0]          = 32;
    ret_val->cfg_ncntMaxVal_10_8[0]         = 6;
    ret_val->cfg_ssc_en[0]                  = 1;    //  Lane SSC Enable

    if (config.master_loop == VTSS_SD10G28_LM1) {
      ret_val->cfg_tx2rx_lp_en[0]             = 1;     
      ret_val->cfg_txlb_en[0]                 = 1; 
    } else if (config.master_loop == VTSS_SD10G28_MASTER_LOOP_NONE) {
      ret_val->cfg_tx2rx_lp_en[0]             = 0;     
      ret_val->cfg_txlb_en[0]                 = 0; 
    }

    if (config.slave_loop == VTSS_SD10G28_LS1 && config.master_loop== VTSS_SD10G28_MASTER_LOOP_NONE) {
      ret_val->cfg_rx2tx_lp_en[0]             = 1;     //LS1
      ret_val->cfg_rxlb_en[0]                 = 1; 
      ret_val->cfg_cdrck_en[0]                = 0; 
    } else if (config.slave_loop == VTSS_SD10G28_LS2 && config.master_loop == VTSS_SD10G28_MASTER_LOOP_NONE) {
      ret_val->cfg_rx2tx_lp_en[0]             = 1;     //LS2
      ret_val->cfg_rxlb_en[0]                 = 1; 
      ret_val->cfg_cdrck_en[0]                = 1; 
    } else if (config.slave_loop == VTSS_SD10G28_SLAVE_LOOP_NONE) {
      ret_val->cfg_rx2tx_lp_en[0]             = 0;     //
      ret_val->cfg_rxlb_en[0]                 = 0; 
      ret_val->cfg_cdrck_en[0]                = 1; 
    }
    //TX invert
    if (config.txinvert) {
      ret_val->r_tx_pol_inv[0]                =1;
    } else {
      ret_val->r_tx_pol_inv[0]                =0;
    }
    //RX invert
    if (config.rxinvert) {
      ret_val->r_rx_pol_inv[0]                =1;
    } else {
      ret_val->r_rx_pol_inv[0]                =0;
    }

    return rslt;
}

vtss_rc vtss_calc_sd10g28_lane_pwr_down (vtss_sd10g28_lane_pwr_down_t *const ret_val) {

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


vtss_rc vtss_calc_sd10g28_cmu_pwr_down(vtss_sd10g28_cmu_pwr_down_t *const ret_val) {

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

vtss_rc vtss_calc_sd10g28_cmu_type(int cmu_num, vtss_sd10g28_cmu_type_t *const ret_val) {

  if (cmu_num < 14) {

    VTSS_D ("vtss_calc_sd10g28_cmu_type: %d CMU Number\n", cmu_num);
    if (cmu_num==1 || cmu_num==4 || cmu_num ==7 || cmu_num ==10|| cmu_num ==13) {
      ret_val->cmu_type[0] = to_u8(1);/*AUX2 */
    } else {
      ret_val->cmu_type[0] = to_u8(0);/*MAIN and AUX1*/ 
    }

    VTSS_D ("vtss_calc_sd10g28_cmu_type: %d CMU Number and %d Type \n", cmu_num, ret_val->cmu_type[0]);
    return VTSS_RC_OK;
  } else {
    VTSS_D ("vtss_calc_sd10g28_cmu_type: %d CMU Number must be < 14\n", cmu_num);
    return VTSS_RC_ERROR;
  }
}


/* ******************************************************************************** */
/* ***                        E N D   O F    F I L E                            *** */
/* ******************************************************************************** */
