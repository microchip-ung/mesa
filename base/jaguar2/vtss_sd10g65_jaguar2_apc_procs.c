// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/*---------------------------------------------------------------------------
 * $HeadURL: svn://svn-de.vitesse.com/svn-de/vtslibs/vts_ute_tcllib/tags/UTE_release_vts_ute_tcllib_20180312_trunk_bjo/api_c/vtss_sd10g65_jaguar2_apc_procs.c $
 *---------------------------------------------------------------------------*/

/* ================================================================= *
 *               Note: This code is provided as part of the
 *                     Universal Tcl Environment (UTE) to provide 
 *                     consistent setup functions for 
 *       ^             - Verification
 *      / \            - Validation
 *     /   \           - Test Pattern Generation and
 *    /  |  \          - Software
 *   /   !   \         It should not be modified without further inquiry
 *  /_________\        by the respective team.
 *                     Please contact
 *                       Patrick Urban <patrick.urban@microsemi.com> or
 *                       Alexander Koch <alexander.koch@microsemi.com> or
 *                       Mark Venneboerger <mark.venneboerger@microsemi.com>
 *                     Please use Bugzilla for reporting issues or requesting enhancements: 
 *                     Bugzilla: Tools->Victoria
 *                     http://projissuetracker/bugzilla/enter_bug.cgi?product=Victoria
 * ================================================================= */


#include <vtss/api/options.h>  // To get the ARCH define
#if defined(VTSS_ARCH_JAGUAR_2_B)

#include "vtss_jaguar2_inc.h"
#include "vtss_sd10g65_jaguar2_apc_procs.h"


/* ================================================================= *
 *  Helper functions
 * ================================================================= */
static vtss_rc vtss_sd10g65_jaguar2_apc_print_results(vtss_state_t *vtss_state,
                                                      const vtss_port_no_t port_no,
                                                      const BOOL           header)
{
    u32 tgt_dig;
    u32 rd_val;
    u8  freeze_apc;
    
    u32 eqz_gain;    
    u32 eqz_gain_adj;
    u32 ld_lev;
    u32 eqz_offs;
    u32 eqz_agc;
    u32 eqz_c;
    u32 eqz_l;
    u32 dfe1;
    u32 dfe2;
    u32 dfe3;
    u32 dfe4;

    i32 d_dfe1;
    i32 d_dfe2;
    i32 d_dfe3;
    i32 d_dfe4;
    i32 d_dfe;


    tgt_dig = VTSS_TO_10G_APC_TGT(port_no);

    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0(tgt_dig), &rd_val);
    freeze_apc = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC(rd_val);
    JR2_WRM(VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0(tgt_dig), 
            VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC(1),
            VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC);

    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS(tgt_dig), &rd_val);
    eqz_gain     = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ACTVAL(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS(tgt_dig), &rd_val);
    eqz_gain_adj = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_EQZ_GAIN_ADJ_ACTVAL(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS(tgt_dig), &rd_val);
    ld_lev       = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_CTRL_STATUS_LD_LEV_ACTVAL(rd_val);  
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL(tgt_dig),   &rd_val);
    eqz_offs     = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_OFFS_CTRL_EQZ_OFFS_ACTVAL(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL(tgt_dig),    &rd_val);
    eqz_agc      = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL(rd_val);  
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL(tgt_dig),      &rd_val);
    eqz_c        = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL(tgt_dig),      &rd_val);
    eqz_l        = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL(tgt_dig),       &rd_val);
    dfe1         = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL(tgt_dig),       &rd_val);
    dfe2         = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL(tgt_dig),       &rd_val);
    dfe3         = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE3_CTRL_DFE3_ACTVAL(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL(tgt_dig),       &rd_val);
    dfe4         = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE4_CTRL_DFE4_ACTVAL(rd_val);

    /* Resume APC operation */
    JR2_WRM(VTSS_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0(tgt_dig), 
            VTSS_F_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC(freeze_apc),
            VTSS_M_SD10G65_DIG_SD10G65_APC_APC_COMMON_CFG0_FREEZE_APC);

    d_dfe1 = (dfe1 >= 64) ? (dfe1 - 64) : (dfe1 - 63);
    d_dfe2 = (dfe2 >= 32) ? (dfe2 - 32) : (dfe2 - 31);
    d_dfe3 = (dfe3 >= 16) ? (dfe3 - 16) : (dfe3 - 15);
    d_dfe4 = (dfe4 >= 16) ? (dfe4 - 16) : (dfe4 - 15);
    d_dfe  = d_dfe1 + d_dfe2 + d_dfe3 + d_dfe4;

    if (header == TRUE) {
        VTSS_I("---------------------   Printing LC-softcontrol results for SerDes #%d (Port #%d) ----------------------", port_no, port_no +1);
        VTSS_I("# %4s  %8s  %7s  %6s  %5s  %5s  %5s  %5s  %5s  %5s  %5s  %5s", "gain", "gain_adj", "lev_det", "offs", "agc", "l", "c", "dfe1", "dfe2", "dfe3", "dfe4", "D/dfe");
    }
    VTSS_I("# %4d  %8d  %7d  %6d  %5d  %5d  %5d  %5d  %5d  %5d  %5d  %5d", eqz_gain,  eqz_gain_adj,  ld_lev,  eqz_offs,  eqz_agc, eqz_l,  eqz_c,  dfe1,  dfe2,  dfe3,  dfe4, d_dfe);
    return VTSS_RC_OK;
}




vtss_rc vtss_sd10g65_jaguar2_lc_softctrl_args_init(vtss_sd10g65_jaguar2_lc_softctrl_args_t  *const init_val){

    init_val->mode           =   1;
    init_val->iterations     =  30;    
    init_val->iter_delay     =   1;    
    init_val->dfe1_target    =  63;   
    init_val->dfe2_target    =  32;   
    init_val->eqz_l_div      =   8;     
    init_val->agc_threshold  = 253; 
    init_val->dfe1_threshold =   8;
    init_val->dfe2_threshold =   4;
    init_val->observe        =   0;       

    return VTSS_RC_OK;
}

vtss_rc vtss_sd10g65_jaguar2_lc_softctrl(vtss_state_t                                  *vtss_state,
                                         const vtss_sd10g65_jaguar2_lc_softctrl_args_t config,
                                         const vtss_port_no_t                          port_no)
{
    u32 tgt_dig;
    u32 rd_val;
    u32 eqz_l_max;
    u32 eqz_l_min;
    u32 eqz_c_max;
    u32 eqz_c_min;
    u32 eqz_l;
    u32 eqz_c;
    u32 eqz_agc;
    u32 dfe1;
    u32 dfe2;
    u8  iter;

    tgt_dig = VTSS_TO_10G_APC_TGT(port_no);

    if ((config.mode < 1) || (config.mode > 2)) {
        VTSS_E("vtss_sd10g65_jaguar2_lc_softctrl: illegal mode selected %u", config.mode);
        return VTSS_RC_ERROR;
    }

    if( config.observe == TRUE) {
        VTSS_I("LC-soft-control port %u\n", port_no + 1);
    }

    /* get min/max values for L and C */
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG(tgt_dig), &rd_val);
    eqz_l_max = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MAX(rd_val);
    eqz_l_min = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_MIN(rd_val);
    JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG(tgt_dig), &rd_val);
    eqz_c_max = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MAX(rd_val);
    eqz_c_min = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_MIN(rd_val);

    for (iter=0; iter < config.iterations; iter++) {
        JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL(tgt_dig), &rd_val);
        eqz_l = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_ACTVAL(rd_val);

        JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL(tgt_dig), &rd_val);
        eqz_c = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_ACTVAL(rd_val);

        JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL(tgt_dig),  &rd_val);
        dfe1 = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE1_CTRL_DFE1_ACTVAL(rd_val);

        JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL(tgt_dig),  &rd_val);
        dfe2 = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_DFE2_CTRL_DFE2_ACTVAL(rd_val);

        if (config.mode == 1) {
            /******************************************************* */
            /* eqz_l_control */
            if ((dfe1 < (config.dfe1_target - (eqz_l/config.eqz_l_div))) && (eqz_l < eqz_l_max)) {
                eqz_l++;
            } else if ((dfe1 > (config.dfe1_target - (eqz_l/config.eqz_l_div))) && (eqz_l > eqz_l_min)) {
                eqz_l--;
            }
            /******************************************************* */
            /* eqz_c_control */
            if ((dfe2 < (config.dfe2_target + (eqz_l/config.eqz_l_div))) && (eqz_c < eqz_c_max)) {
                eqz_c++;
            } else if ((dfe2 > (config.dfe2_target + (eqz_l/config.eqz_l_div))) && (eqz_c > eqz_c_min)) {
                eqz_c--;
            }
        } else {  /*config.mode == 2*/
            JR2_RD(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL(tgt_dig), &rd_val);
            eqz_agc = VTSS_X_SD10G65_DIG_SD10G65_APC_APC_EQZ_AGC_CTRL_EQZ_AGC_ACTVAL(rd_val);

            /******************************************************* */
            /* eqz_l_control */
            if ((eqz_agc >= config.agc_threshold) && (eqz_l < eqz_l_max)) {
                eqz_l++;
            } else if ((dfe1 <= config.dfe1_target - config.dfe1_threshold) && (eqz_l < eqz_l_max)) {
                eqz_l++;
            } else if ((dfe1 > config.dfe1_target + config.dfe1_threshold) && (eqz_l > eqz_l_min)) {
                eqz_l--;
            }
            /******************************************************* */
            /* eqz_c_control */
            if ((eqz_agc >= config.agc_threshold) && (eqz_c < eqz_c_max)) {
                eqz_c++;
            } else if ((dfe2 <= config.dfe2_target - config.dfe2_threshold) && (eqz_c < eqz_c_max)) {
                eqz_c++;
            } else if ((dfe2 > config.dfe2_target + config.dfe2_threshold) && (eqz_c > eqz_c_min)) {
                eqz_c--;
            }
        }
        /******************************/
        /*   update parameters   */
        JR2_WRM(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG(tgt_dig),
                VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_INI(eqz_l),
                VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_INI);

        JR2_WRM(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG(tgt_dig),
                VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_INI(eqz_c),
                VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_INI);

        if (iter == 0) {
            /* stop automatic control of L and C via pattern matching */
            /* (needs to be done only after the 1st iterations) */
            JR2_WRM(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG(tgt_dig), 
                    VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_CHG_MODE(1),
                    VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_PAR_CFG_EQZ_L_CHG_MODE); /* use fix values */
            JR2_WRM(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG(tgt_dig),
                    VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_CHG_MODE(1),
                    VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_PAR_CFG_EQZ_C_CHG_MODE); /* use fix values */
            JR2_WRM(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL(tgt_dig),
                    VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_SYNC_MODE(0),
                    VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_L_CTRL_EQZ_L_SYNC_MODE); /* no auto-ctrl */
            JR2_WRM(VTSS_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL(tgt_dig),
                    VTSS_F_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_SYNC_MODE(0),
                    VTSS_M_SD10G65_DIG_SD10G65_APC_APC_EQZ_C_CTRL_EQZ_C_SYNC_MODE); /* no auto-ctrl */

            if (config.observe == TRUE) {
                vtss_sd10g65_jaguar2_apc_print_results(vtss_state, port_no, TRUE);
            }
        } else {
            if (config.observe == TRUE) {
                vtss_sd10g65_jaguar2_apc_print_results(vtss_state, port_no, FALSE);
            }
        }
        /* wait n ms */
        VTSS_MSLEEP(config.iter_delay);
    } /* for (iter=.... */

    return VTSS_RC_OK;
}

#endif


/* ******************************************************************************** */
/* ***                        E N D   O F    F I L E                            *** */
/* ******************************************************************************** */

