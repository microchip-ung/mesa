// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SD10G28_PROCS_H_
#define _VTSS_SD10G28_PROCS_H_


#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#else
#include <vtss/api/types.h>
#endif

/* ================================================================= *
 *  Data structures / types
 * ================================================================= */


/** \brief Vitesse chip development name */
typedef enum {
    VTSS_SD10G28_CHIP_ANT,
    VTSS_SD10G28_CHIP_LAST
} vtss_sd10g28_chip_name_t;

/** \brief SerDes mode type for differnet configurations*/
typedef enum {
        VTSS_SD10G28_MODE_10G_LAN,//D;
        VTSS_SD10G28_MODE_10G_ETH,
        VTSS_SD10G28_MODE_10G_QSXGMII,//R;only 1G/2G5 devices are used
        VTSS_SD10G28_MODE_10G_DSXGMII,//U;only 5G devices are used
        VTSS_SD10G28_MODE_10G_USGMII,//X;1G/2G5 devices are used
        VTSS_SD10G28_MODE_QSGMII,//Q;
        VTSS_SD10G28_MODE_5G_LAN,
        VTSS_SD10G28_MODE_5G_USXGMII,//F;
        VTSS_SD10G28_MODE_SGMII2G5,
        VTSS_SD10G28_MODE_SGMII,
        VTSS_SD10G28_MODE_1G_LAN,
        VTSS_SD10G28_MODE_FX100,
        VTSS_SD10G28_MODE_NONE
} vtss_sd10g28_mode_t;

/*CMU selection*/
typedef enum {
  VTSS_SD10G28_MAIN,
  VTSS_SD10G28_AUX1,
  VTSS_SD10G28_AUX2,
  VTSS_SD10G28_CMU_NONE,
} vtss_sd10g28_cmu_t;

/*Rate selection*/
typedef enum {
  VTSS_SD10G28_RATE_1,
  VTSS_SD10G28_RATE_0P5,
  VTSS_SD10G28_RATE_0P25,
  VTSS_SD10G28_RATE_0P125,
} vtss_sd10g28_rate_t;

/*Master Loopbacks */
typedef enum {
  VTSS_SD10G28_MASTER_LOOP_NONE,
  VTSS_SD10G28_LM1,
} vtss_sd10g28_lm_t;

/*slave Loopbacks */
typedef enum {
  VTSS_SD10G28_SLAVE_LOOP_NONE,
  VTSS_SD10G28_LS1,
  VTSS_SD10G28_LS2,
  VTSS_SD10G28_LS3,
} vtss_sd10g28_ls_t;


/**
 * \brief Receiver preset for different cable types
 **/

typedef enum {
    VTSS_SD10G28_ATE,          /**< Setup be used for ATE testing,Not yet configured > */
    VTSS_SD10G28_ZR,           /**< ZR,Not yet configured  > */
    VTSS_SD10G28_DAC3M,       /**< Variable used for running DAC 3m at 10G speed > */
    VTSS_SD10G28_DAC5M,       /**< Variable used for running DAC 5m at 10G speed > */
    VTSS_SD10G28_DAC2M,       /**< Variable used for running DAC 2m at 10G speed > */
    VTSS_SD10G28_DAC1M,       /**< Variable used for running DAC 1m at 10G speed > */
    VTSS_SD10G28_SR,          /**< Variable used for running SFP_SR at 10G speed > */
    VTSS_SD10G28_DAC3M_PVT,    /**<Variable used for running PVT using DAC3M at 10G speed>*/
    VTSS_SD10G28_KR,          /**< KR Backplane, not yet configured> */
    VTSS_SD10G28_FX100,       /**< 100FX settings> */
    VTSS_SD10G28_PRESET_NONE   /**< Variable used for running using SFp, RJ45 at speed lesser than 10G> */ 
} vtss_sd10g28_preset_t;


/** \brief return values of pwr_down function */
typedef struct {
    u8 r_iscan_reg[1]               ; 
    u8 r_txeq_reg[1]                ;
    u8 r_misc_reg[1]                ;
    u8 r_swing_reg[1]               ;
    u8 r_reg_manual[1]              ; 
    u8 r_dwidthctrl_from_hwt[1]     ;          
    u8 r_auxcksel_from_hwt[1]       ;        
    u8 r_lane_id_from_hwt[1]        ;       
    u8 r_rx_pcie_gen12_from_hwt[1]  ;             
    u8 r_ssc_from_hwt[1]            ;   
    u8 r_cdr_from_hwt[1]            ;   
    u8 r_pclk_gating_from_hwt[1]    ;           
    u8 cfg_lane_id_2_0[1]           ;    
    u8 cfg_dfetap_en_5_1[1]         ;      
    u8 cfg_dfeck_en[1]              ; 
    u8 cfg_dfe_pd[1]                ;
    u8 cfg_erramp_pd[1]             ;  
    u8 cfg_pi_dfe_en[1]             ;  
    u8 cfg_pi_en[1]                 ;
    u8 cfg_pd_ctle[1]               ;
    u8 cfg_summer_en[1]             ;  
    u8 cfg_pd_rx_cktree[1]          ;     
    u8 cfg_pd_clk[1]                ;
    u8 cfg_pd_cml[1]                ;
    u8 cfg_pd_driver[1]             ;  
    u8 cfg_rx_reg_pu[1]             ;  
    u8 cfg_cdrck_en[1]              ; 
    u8 cfg_dcdr_pd[1]               ;
    u8 cfg_pd_sq[1]                 ;
    u8 cfg_en_main[1]               ;
    u8 cfg_en_adv[1]                ;
    u8 cfg_en_dly[1]                ;
    u8 cfg_tap_main[1]              ; 
    u8 cfg_r50_en[1]                ;
    u8 cfg_rxdet_en[1]              ; 
    u8 cfg_rxdet_str[1]             ;  
    u8 cfg_eid_lp[1]                ;
    u8 r_txei[1]                    ;
} vtss_sd10g28_lane_pwr_down_t;


typedef struct {
    u8 cfg_ctrl_logic_pd[1]  ; 
    u8 cfg_vco_pd[1]         ;
    u8 cfg_en_dummy[1]       ;
    u8 cfg_ck_tree_pd[1]     ;
    u8 cfg_rst_tree_pd_man[1]; 
    u8 cfg_en_tx_ck_up[1]    ;          
    u8 cfg_en_tx_ck_dn[1]    ;        
    u8 cfg_pd_div64[1]       ;       
    u8 cfg_pd_div66[1]       ;             
    u8 cfg_pma_tx_ck_pd[1]   ;   
    u8 cfg_link_buf_en[1]    ;   
    u8 cfg_refck_ssc_en[1]   ;           
    u8 cfg_refck_term_en[1]  ;    
    u8 cfg_refck_pd[1]       ;      
    u8 cfg_ibias_pd[1]       ; 
    u8 cfg_bias_dn_en[1]     ;
    u8 cfg_bias_up_en[1]     ;  
} vtss_sd10g28_cmu_pwr_down_t;

/** \brief Parameters needed for setup function */
typedef struct {
    vtss_sd10g28_chip_name_t     chip_name;   /**< Name of the chip >                                                              */
    vtss_sd10g28_mode_t  mode;      /**< Mode parameter.                                             */
    //u32                  datarate;       /**< optional parameter; if this is specified if_width must also be specified >                                                 */
    u8                   if_width;    /**< UDL interface width 10, 16, 20, 32 or 64 bit >                                           */
    BOOL                 skip_cmu_cfg;   /* Enable/disable CMU configuration for this serdes*/
    vtss_sd10g28_cmu_t   cmu_sel;   /* This needs to be handled based on the Device/Mode serdes uses*/
    BOOL                 no_pwrcycle; /**< Omit initial power-cycle >                                                              */
    vtss_sd10g28_ls_t    slave_loop;    /**< Enable input loop LS1/Ls2/LS3 >                                                       */
    vtss_sd10g28_lm_t    master_loop;    /**< Enable pad loop LM1  >                                                               */
    vtss_sd10g28_preset_t    preset;    /**< Preset Media Type  >                                                               */
    BOOL                 txinvert;      /**< Enable inversion of output data >                                                       */
    BOOL                 rxinvert;      /**< Enable inversion of input data >                                                       */
    BOOL                 txmargin;     /**< Set output level to  half/full                                                  */
    u16                  txswing;     /**< Set output level                                                   */
    u8                   dfe_enable;
    BOOL                 mute;        /**< Mute Output Buffer. >                                 */
    BOOL                 is_6g;
} vtss_sd10g28_setup_args_t;
//
typedef struct {
    vtss_sd10g28_mode_t  mode;      /**< Mode parameter.                                             */
    //u32                  datarate;       /**< optional parameter; if this is specified if_width must also be specified >                                                 */
    u8                   bitwidth;    /**< UDL interface width 10, 16, 20, 32 or 64 bit >                                           */
    vtss_sd10g28_cmu_t   cmu_sel;   /* This needs to handled based on the Device/Mode it used*/
    BOOL                 skip_cmu_cfg;   /* Enable/disable CMU configuration for this serdes*/
    u8                   rate;    /**< Rate of network interface >                                                       */
    u8                   dfe_tap;      /**< Enable inversion of output data >                                                       */
    u8                   pi_bw_gen1;      /**< Enable inversion of input data >                                                       */
    u8                   duty_cycle;     /**< Set output level to  half/full                                                  */
    BOOL                 dfe_enable;
} vtss_sd10g28_mode_args_t;


/** \brief return values of setup function */
typedef struct {
    u8 cmu_sel[1];
    u8 is_6g[1];
    u8 skip_cmu_cfg[1];
    u8 cfg_lane_reserve_7_0[1]     ;  // LSB:
    u8 cfg_ssc_rtl_clk_sel[1]     ;  // MSB:
    u8 cfg_lane_reserve_15_8[1]    ; //Bit 9 controls Duty cycle; Silicon Dependend this needs to be corrected
      
    //r_DwidthCtrl_from_hwt related signals
    //TX and RX rate selection towards network interface									   
    u8 cfg_txrate_1_0[1];
    u8 cfg_rxrate_1_0[1];
      
    //UDL interface configuration bitwidth, tx and rx clock selection, phymode selection 
    u8 r_DwidthCtrl_2_0[1];
    u8 cfg_pma_tx_ck_bitwidth_2_0[1];
    u8 cfg_rxdiv_sel_2_0[1]         ;
    
    u8 r_pcs2pma_phymode_4_0[1];
      
    u8 cfg_lane_id_2_0[1];//  Bias Trace Selection
    
    //r_reg_manual related signals
    u8 cfg_cdrck_en[1]         ;
    u8 cfg_dfeck_en[1]         ;
    u8 cfg_dfe_pd[1]           ;
    u8 cfg_dfetap_en_5_1[1]    ;
    u8 cfg_erramp_pd[1]        ;
    u8 cfg_pi_DFE_en[1]       ;
    u8 cfg_pi_en[1]           ;
    u8 cfg_pd_ctle[1]         ;
    u8 cfg_summer_en[1]        ;
    u8 cfg_pd_rx_cktree[1]     ;
    u8 cfg_pd_clk[1]           ;
    u8 cfg_pd_cml[1]           ;
    u8 cfg_pd_driver[1]        ;
    u8 cfg_rx_reg_pu[1]        ;
    u8 cfg_Dcdr_pd[1]          ;
    u8 cfg_pd_sq[1]            ;
    u8 cfg_rxdet_en[1]         ;
    u8 cfg_rxdet_str[1]        ;
    u8 r_multi_lane_mode[1]    ;
    
    //r_txeq_reg related signals
    u8 cfg_en_adv[1]     ;
    u8 cfg_en_main[1]    ;
    u8 cfg_en_dly[1]     ;
    u8 cfg_tap_adv_3_0[1];
    u8 cfg_tap_main[1]   ;
    u8 cfg_tap_dly_4_0[1];
    
    //r_rxeq_reg related signals there are for SR and DFE needs to be enabled for LR/MR
    //DFE is enabled for 10G 
    u8 cfg_vga_ctrl_3_0[1]   ;
    u8 cfg_vga_cp_2_0[1]   ;
    u8 cfg_eq_res_3_0[1];    //CTLE gain control. 
    u8 cfg_eqR_byp[1]        ;
    u8 cfg_eqC_force_3_0[1]  ;
    u8 cfg_en_dfedig[1]      ;
    u8 cfg_sum_setcm_en[1]   ;
      
    //r_misc_reg
    u8 cfg_en_preemph[1];   //Unused in current IP as per Tony 08/29/2018.
    u8 cfg_itx_ippreemp_base_1_0[1]; //Unused in current IP as per Tony 08/29/2018.
      
    //r_swing_reg;
    u8 cfg_itx_ipdriver_base_2_0[1]           ;
    u8 cfg_ibias_tune_reserve_5_0[1]          ;
    u8 cfg_txswing_half[1]                    ;
      
    //r_cdr_from_hwt this is cfg controlled. 
    u8 cfg_dis_2ndOrder[1]      ;              //  2nd order CDR disable signal.
    u8 cfg_rx_ssc_lh[1]         ;              //  CDR operation rate selection 
    u8 cfg_pi_floop_steps_1_0[1] ;             //  Frequency loop PI step selection
    u8 cfg_pi_ext_dac_23_16[1]  ;     //  2nd order CDR digital lowpass filter select
    u8 cfg_pi_ext_dac_15_8[1]     ;   //  2nd order CDR digital lowpass filter select
    u8 cfg_iscan_ext_dac_7_0[1]  ;     //CDR clock phase tuning parameter; Silicon Dependend;
    
    //RX CDR  and TX driver register Settings
    u8 cfg_cdr_kf_gen1_2_0[1]  ;   //CDR 1st order Gain Adjust GEN1
    u8 cfg_cdr_kf_gen2_2_0[1]  ;   //CDR 1st order Gain Adjust GEN2
    u8 cfg_cdr_kf_gen3_2_0[1]  ;   //CDR 1st order Gain Adjust GEN3
    u8 cfg_cdr_kf_gen4_2_0[1]  ;   //CDR 1st order Gain Adjust GEN4
    u8 r_cdr_m_gen1_7_0[1]     ;   //CDR 1st order LP filter select GEN1
    u8 cfg_pi_bw_gen1_3_0[1]   ;   //CDR PI BW Adj. GEN1 Silicon Dependend   
    u8 cfg_pi_bw_gen2[1]      ;    //CDR PI BW Adj. GEN2
    u8 cfg_pi_bw_gen3[1]      ;    //CDR PI BW Adj. GEN3
    u8 cfg_pi_bw_gen4[1]      ;    //CDR PI BW Adj. GEN4
    //u8 cfg_iscan_ext_dac_7_0[1];   //Already configured
    u8 cfg_pi_ext_dac_7_0[1]   ;   //DFE clock phase tuning parameter; Silicon Dependend;
    u8 cfg_pi_steps[1]            ;
    u8 cfg_mp_max_3_0[1]          ;
    u8 cfg_rstn_dfedig[1]     ;    // DFE Reset; it is reset automatically after assert and release of pclk_gating 
      
    u8 cfg_alos_thr_3_0[1]     ;             //Voltage threshold for squelch detection
      
    u8 cfg_predrv_slewrate_1_0[1] ;          // ??
    u8 cfg_itx_ipcml_base_1_0[1]  ;          // predriver current setting in TX
    u8 cfg_ip_pre_base_1_0[1]     ;          // ?? 
      
    u8 r_cdr_m_gen2_7_0[1]        ;  //  CDR 1st order LP filter select GEN2
    u8 r_cdr_m_gen3_7_0[1]        ;  //  CDR 1st order LP filter select GEN3
    u8 r_cdr_m_gen4_7_0[1]        ;  //  CDR 1st order LP filter select GEN4
    
    u8 r_en_auto_cdr_rstn[1]     ;           //  Lane CDR auto reset function enable
      
    u8 cfg_oscal_afe[1]          ;
    u8 cfg_pd_osdac_afe[1]       ;
    u8 cfg_resetb_oscal_afe[2]   ;
    
    // TX SSC 
    u8 cfg_center_spreading[1] ;  //  Lane SSC type selection
    u8 cfg_McntMaxVal_4_0[1]    ; //  Lane SSC spreading range contrl
    u8 cfg_ncntMaxVal_7_0[1]   ;
    u8 cfg_ncntMaxVal_10_8[1]   ;
    u8 cfg_ssc_en[1]          ;    //  Lane SSC Enable

    u8 cfg_tx2rx_lp_en[1];    //LM1 
    u8 cfg_txlb_en[1]    ; 


    u8 cfg_rx2tx_lp_en[1];     //LSx
    u8 cfg_rxlb_en[1]    ; 
    u8 r_tx_pol_inv[1];
    u8 r_rx_pol_inv[1];
    u8 fx_100[1];
} vtss_sd10g28_setup_struct_t;

//Definition to handle cmu num
typedef struct {
  u8 cmu_type[1];
} vtss_sd10g28_cmu_type_t;



/** \brief Receiver preset values based on selected preset mode */
typedef struct {
    u8 cfg_en_adv;
    u8 cfg_en_main;
    u8 cfg_en_dly;
    u8 cfg_tap_adv_3_0;
    u8 cfg_tap_main;
    u8 cfg_tap_dly_4_0;
    //r_rxeq_reg related signals there are for SR and DFE needs to be enabled for LR/MR
    u8 cfg_vga_ctrl_3_0;//vga R
    u8 cfg_vga_cp_2_0;//vga C
    u8 cfg_eq_res_3_0;//CTLE gain control. 
    u8 cfg_eqR_byp;
    u8 cfg_eqC_force_3_0;
    u8 cfg_alos_thr_3_0;
} vtss_sd10g28_preset_struct_t;

/** \brief Input Buffer loop settings based on loop config */
typedef struct {
} vtss_sd10g28_loop_cfg_t;

/** \brief Parameters needed for setup_rx function */
//TODO need to see if this is required
//typedef struct {
//    vtss_sd10g28_chip_name_t      chip_name;   /**< Name of the vitesse chip >                                 */
//    vtss_sd10g28_rate_t   datarate;       /**< targeted sample frequency / data rate >                    */
//    vtss_sd10g28_mode_t   mode;      /**< Optional mode for setting up the frequency.                */
//                                       /**<   Overwrites f_pll if !=  VTSS_SD10G28_MODE_NONE,          */
//                                       /**<   Mandatory for FX100 mode                                 */
//    u8                    if_width;    /**< interface width 8, 10, 16, 20, 32 or 40 bit >              */
//    vtss_sd10g28_preset_t preset;      /**< Setup macro with link specific presets >                   */
//} vtss_sd10g28_setup_rx_args_t;

/** \brief return values of setup_rx function */
//TODO need to see if this is required
//typedef struct {
//
//} vtss_sd10g28_setup_rx_struct_t;


/* ================================================================= *
 *  Function prototypes
 * ================================================================= */

vtss_rc vtss_sd10g28_get_conf_from_mode(BOOL is_6g, vtss_sd10g28_mode_t  mode, 
                                        vtss_sd10g28_mode_args_t *const ret_val);


//vtss_rc vtss_sd10g28_setup_tx_args_init(vtss_sd10g28_setup_tx_args_t     *const init_val);
//vtss_rc vtss_sd10g28_setup_rx_args_init(vtss_sd10g28_setup_rx_args_t     *const init_val);

vtss_rc vtss_calc_sd10g28_setup_lane(const vtss_sd10g28_setup_args_t config, 
                                     vtss_sd10g28_setup_struct_t    *const ret_val);

vtss_rc vtss_calc_sd10g28_cmu_type(int cmu_num, vtss_sd10g28_cmu_type_t *const ret_val); 
vtss_rc vtss_calc_sd10g28_lane_pwr_down(vtss_sd10g28_lane_pwr_down_t *const ret_val); 
vtss_rc vtss_calc_sd10g28_cmu_pwr_down(vtss_sd10g28_cmu_pwr_down_t *const ret_val); 

#endif
