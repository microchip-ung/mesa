// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SD25G28_PROCS_H_
#define _VTSS_SD25G28_PROCS_H_


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
    VTSS_SD25G28_CHIP_ANT,
    VTSS_SD25G28_CHIP_LAST
} vtss_sd25g28_chip_name_t;

/** \brief SerDes mode type for differnet configurations*/
typedef enum {
        VTSS_SD25G28_MODE_25G_LAN,
        VTSS_SD25G28_MODE_25G_ETH,
        VTSS_SD25G28_MODE_10G_LAN,
        VTSS_SD25G28_MODE_10G_ETH,
        VTSS_SD25G28_MODE_10G_QSXGMII,//R;only 1G/2G5 devices are used
        VTSS_SD25G28_MODE_10G_DSXGMII,//U;only 5G devices are used
        VTSS_SD25G28_MODE_5G_LAN,
        VTSS_SD25G28_MODE_5G_USXGMII,//F;
        VTSS_SD25G28_MODE_SGMII2G5,
        VTSS_SD25G28_MODE_SGMII,
        VTSS_SD25G28_MODE_1G_LAN,
        VTSS_SD25G28_MODE_FX100,
        VTSS_SD25G28_MODE_NONE
} vtss_sd25g28_mode_t;



/*Master Loopbacks */
typedef enum {
  VTSS_SD25G28_MASTER_LOOP_NONE,
  VTSS_SD25G28_LM1,
} vtss_sd25g28_lm_t;

/*slave Loopbacks */
typedef enum {
  VTSS_SD25G28_SLAVE_LOOP_NONE,
  VTSS_SD25G28_LS1,
  VTSS_SD25G28_LS2,
  VTSS_SD25G28_LS3,
} vtss_sd25g28_ls_t;

/** \brief return values of pwr_down function */
/*
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
} vtss_sd25g28_lane_pwr_down_t;
*/

/**
 * \brief Receiver preset for different cable types
 * \note _SC presets are only available for deviced that have the respective APC HW support
 **/

typedef enum {
    VTSS_SD25G28_ATE,          /**< Setup be used for ATE testing, Not yet added > */
    VTSS_SD25G28_ZR,        /**< ZR with APC software algorithm, Not yet added > */
    VTSS_SD25G28_10GDAC3M,       /**< Variable used for 3M DAC running at 10G speed >**/
    VTSS_SD25G28_10GDAC5M,    /**< Variable used for 5M DAC running at 10G speed >**/
    VTSS_SD25G28_10GDAC1M,    /**<Variable used for 1M DAC running at 10G speed>**/
    VTSS_SD25G28_10GSR,        /**<Variable used for SFP-SR running at 10G speed>**/
    VTSS_SD25G28_KR_HW,        /**< KR Backplane> */
    VTSS_SD25G28_PRESET_NONE,   /**<Variable used for SFP or RJ45 running at speed lesser than 10G>**/
    VTSS_SD25G28_25GSR,         /**<Variable used for 25-SFP-SR running at 25G speed>**/
    VTSS_SD25G28_25GDAC2M,         /**<Variable used for 25G-DAC-2M- running at 25G speed>**/
    VTSS_SD25G28_10GDAC3M_PVT,         /**<Variable used for 10G-DAC-3M- running at 10G speed for PVT setup>**/

} vtss_sd25g28_preset_t;

/** \brief Parameters needed for setup function */
typedef struct {
    vtss_sd25g28_chip_name_t     chip_name;   /**< Name of the vitesse chip >                                                              */
    vtss_sd25g28_mode_t  mode;      /**< Mode parameter.                                             */
    //u32                  datarate;       /**< optional parameter; if this is specified if_width must also be specified >                                                 */
    //u8                   if_width;    /**< UDL interface width 10, 16, 20, 32 or 64 bit >                                           */
    u8                   reg_ctrl;    /*Register/Pin configuration control for r_DwidthCtrl_from_hwt and r_reg_manual >                                           */
    //vtss_sd25g28_cmu_t   cmu_sel;   /* This needs to handled based on the Device/Mode it used*/
    //BOOL                 no_pwrcycle; /**< Omit initial power-cycle >                                                              */
    vtss_sd25g28_ls_t    slave_loop;    /**< Enable input loop LS1/Ls2/LS3 >                                                       */
    vtss_sd25g28_lm_t    master_loop;    /**< Enable pad loop LM1  >                                                               */
    vtss_sd25g28_preset_t    preset;   
    BOOL                 txinvert;      /**< Enable inversion of output data >                                                       */
    BOOL                 rxinvert;      /**< Enable inversion of input data >                                                       */
    BOOL                 txmargin;     /**< Set output level to  half/full                                                  */
    u16                  txswing;     /**< Set output level                                                   */
    BOOL                 mute;        /**< Mute Output Buffer. >                                 */
} vtss_sd25g28_setup_args_t;


typedef struct {
    vtss_sd25g28_mode_t  mode;      /**< Mode parameter.                                             */
    //u32                  datarate;       /**< optional parameter; if this is specified if_width must also be specified >                                                 */
    u8 bitwidth ; 
    u8 tx_pre_div;
    u8 fifo_ck_div;
    u8 pre_divsel;
    u8 vco_div_mode;
    u8 sel_div ;
    u8 ck_bitwidth; 
    u8 subrate; 
    u8 com_txcal_en; 
    u8 com_pll_reserve; 
    u8 com_tx_reserve_msb;
    u8 com_tx_reserve_lsb;
    u8 ln_tx_reserve_lsb ;
    u8 ln_tx_reserve_msb ;
    u8 ln_bw;
    u8 ln_rxterm;
    u8 dfe_enable;
    u8 dfe_tap;      
    u8 tx_tap_dly; 
    u8 tx_tap_adv;// this depends on actual Si
    u8 txmargin;
    u8 ln_cfg_ctle_rstn;
    u8 ln_r_dfe_rstn;
    u8  ln_cfg_pi_bw_3_0;
    u8  ln_cfg_itx_ipcml_base;

} vtss_sd25g28_mode_args_t;

/** \brief return values of setup function */
typedef struct {
    u8	reg_ctrl[1];
    u8	cfg_jc_byp[1];
    u8	cfg_common_reserve_7_0[1];
    u8	r_reg_manual[1];
    u8	r_DwidthCtrl_from_hwt[2];
    u8	r_DwidthCtrl_2_0[1];
    u8	r_txfifo_ck_div_pmad_2_0[1];
    u8	r_rxfifo_ck_div_pmad_2_0[1];
    u8	cfg_pll_lol_set[1];
    u8	cfg_vco_div_mode_1_0[1];
    u8	cfg_pre_divsel_1_0[1];
    u8	cfg_sel_div_3_0[1];
    u8  cfg_vco_start_code_3_0[1];
    u8  ln_cfg_pma_tx_ck_bitwidth_2_0[1];
    u8  ln_cfg_tx_prediv_1_0[1];
    u8  ln_cfg_rxdiv_sel_2_0[1];
    u8  ln_cfg_tx_subrate_2_0[1];
    u8  ln_cfg_rx_subrate_2_0[1];
    u8  r_multi_lane_mode[1];
    u8  ln_cfg_cdrck_en[1];
    u8  ln_cfg_dfeck_en[1];
    u8  ln_cfg_dfe_pd[1];
    u8  ln_cfg_dfedmx_pd[1];
    u8  ln_cfg_dfetap_en_5_1[1];
    u8  ln_cfg_dmux_pd[1];
    u8  ln_cfg_dmux_clk_pd[1];
    u8  ln_cfg_erramp_pd[1];
    u8  ln_cfg_pi_dfe_en[1];
    u8  ln_cfg_pi_en[1];
    u8  ln_cfg_pd_ctle[1];
    u8  ln_cfg_summer_en[1];
    u8  ln_cfg_pmad_ck_pd[1];
    u8  ln_cfg_pd_clk[1];
    u8  ln_cfg_pd_cml[1];
    u8  ln_cfg_pd_driver[1];
    u8  ln_cfg_rx_reg_pu[1];
    u8  ln_cfg_pd_rms_det[1];
    u8  ln_cfg_dcdr_pd[1];
    u8  ln_cfg_ecdr_pd[1];
    u8  ln_cfg_pd_sq[1];
    u8  ln_cfg_itx_ipdriver_base_2_0[1];
    u8  ln_cfg_tap_dly_4_0[1];
    u8  ln_cfg_tap_main[1];
    u8  ln_cfg_en_main[1];
    u8  ln_cfg_tap_adv_3_0[1];
    u8  ln_cfg_en_adv[1];
    u8  ln_cfg_en_dly[1];
    u8  ln_cfg_iscan_en[1];
    u8  l1_pcs_en_fast_iscan[1];
    u8  l0_cfg_bw_1_0[1];
    u8  l0_cfg_txcal_en[1];
    u8  cfg_en_dummy[1];
    u8  cfg_pll_reserve_3_0[1];
    u8  l0_cfg_tx_reserve_15_8[1];
    u8  l0_cfg_tx_reserve_7_0[1];
    u8  ln_cfg_tx_reserve_15_8[1];
    u8  ln_cfg_tx_reserve_7_0[1];
    u8  ln_cfg_bw_1_0[1];
    u8  ln_cfg_txcal_man_en[1];
    u8  ln_cfg_phase_man_4_0[1];
    u8  ln_cfg_quad_man_1_0[1];
    u8  ln_cfg_txcal_shift_code_5_0[1];
    u8  ln_cfg_txcal_valid_sel_3_0[1];
    u8  ln_cfg_txcal_en[1];
    u8  ln_cfg_cdr_kf_2_0[1];
    u8  ln_cfg_cdr_m_7_0[1];
    u8  ln_cfg_pi_bw_3_0[1];
    u8  ln_cfg_pi_steps_1_0[1];
    u8  ln_cfg_dis_2ndorder[1];
    u8  ln_cfg_ctle_rstn[1];
    u8  ln_r_dfe_rstn[1];
    u8  ln_cfg_alos_thr_2_0[1];
    u8  ln_cfg_itx_ipcml_base_1_0[1];
    u8  ln_cfg_rx_reserve_7_0[1];
    u8  ln_cfg_rx_reserve_15_8[1];
    u8  ln_cfg_rxterm_2_0[1];
    u8  cfg_fom_selm[1];
    u8  ln_cfg_rx_sp_ctle_1_0[1];
    u8  ln_cfg_isel_ctle_1_0[1];
    u8  ln_cfg_vga_ctrl_byp_4_0[1];
    u8  ln_cfg_vga_byp[1];
    u8  ln_cfg_agc_adpt_byp[1];
    u8  ln_cfg_eqr_byp[1];
    u8  ln_cfg_eqr_force_3_0[1];
    u8 ln_cfg_eqc_force_3_0[1];
    u8  ln_cfg_sum_setcm_en[1];
    u8  ln_cfg_init_pos_iscan_6_0[1];
    u8  ln_cfg_init_pos_ipi_6_0[1];
    u8  ln_cfg_dfedig_m_2_0[1];
    u8  ln_cfg_en_dfedig  [1];
    u8  ln_cfg_rstn_dfedig[2];
    u8 ln_cfg_pi_DFE_en[1];

    u8 ln_cfg_tx2rx_lp_en[1];
    u8 ln_cfg_txlb_en[1];
    u8 ln_cfg_rx2tx_lp_en[1];
    u8 ln_cfg_rxlb_en[1];
    u8 ln_r_tx_pol_inv[1];
    u8 ln_r_rx_pol_inv[1];
} vtss_sd25g28_setup_struct_t;



/** \brief Receiver preset values based on selected preset mode */
typedef struct {
 u8 ln_cfg_eqC_force_3_0;
 u8 ln_cfg_vga_ctrl_byp_4_0;
 u8 ln_cfg_eqR_force_3_0;
 u8 ln_cfg_en_adv;
 u8 ln_cfg_en_main;
 u8 ln_cfg_en_dly;
 u8 ln_cfg_tap_adv_3_0;
 u8 ln_cfg_tap_main;
 u8 ln_cfg_tap_dly_4_0;
 u8 ln_cfg_alos_thr_2_0;
} vtss_sd25g28_preset_struct_t;

/** \brief Input Buffer loop settings based on loop config */
typedef struct {
} vtss_sd25g28_loop_cfg_t;

/* ================================================================= *
 *  Function prototypes
 * ================================================================= */

vtss_rc vtss_sd25g28_get_conf_from_mode(vtss_sd25g28_mode_t  mode, 
                                        vtss_sd25g28_mode_args_t *const ret_val);


//vtss_rc vtss_sd25g28_setup_tx_args_init(vtss_sd25g28_setup_tx_args_t     *const init_val);
//vtss_rc vtss_sd25g28_setup_rx_args_init(vtss_sd25g28_setup_rx_args_t     *const init_val);

vtss_rc vtss_calc_sd25g28_setup_lane(const vtss_sd25g28_setup_args_t config, 
                                     vtss_sd25g28_setup_struct_t    *const ret_val);

//vtss_rc vtss_calc_sd25g28_lane_pwr_down(vtss_sd25g28_lane_pwr_down_t *const ret_val); 

#endif
