// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/*---------------------------------------------------------------------------
 * $HeadURL: svn://svn-de.vitesse.com/svn-de/vtslibs/vts_ute_tcllib/tags/UTE_release_vts_ute_tcllib_20180312_trunk_bjo/api_c/vtss_pll5g_procs.c $
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

#include <stdio.h>

#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#else
#include <vtss_phy_api.h>
#include "../common/vtss_phy_common.h"
#endif

#include "vtss_pll5g_procs.h"

vtss_rc vtss_pll5g_setup_args_init (vtss_pll5g_setup_args_t *const init_val) {

    init_val->chip_name = VTSS_PLL5G_CHIP_ES65XX;
    init_val->selbgv820 = 4; /* must be 2 for  init_val->chip_name == VTSS_PLL5G_CHIP_VENICE && init_val->side == VTSS_LINE */
    init_val->side      = VTSS_LINE;
    init_val->f_ref_kHz = 125000;
    init_val->unlock    = FALSE;
    init_val->lock      = FALSE;

    return VTSS_RC_OK;
}

/********************************************************************************
 ********************************************************************************
 ***     M A I N   F U N C T I O N S                                          ***
 ********************************************************************************
 ********************************************************************************/
vtss_rc vtss_calc_pll5g_setup(const vtss_pll5g_setup_args_t config,
                         vtss_pll5g_setup_struct_t *const ret_val) {
    vtss_rc rslt;
    u8 loop_bw_res;
    u8 ena_vco_contrh;
    u8 refclk_sel;

    rslt = VTSS_RC_OK;
    if(config.f_ref_kHz == 25000) {
        loop_bw_res = 10;
        refclk_sel  = 4;
    } else if (config.f_ref_kHz == 125000) {
        loop_bw_res = 14;
        refclk_sel  = 0;
    } else if (config.f_ref_kHz == 156250) {
        loop_bw_res = 17;
        refclk_sel  = 1;
    } else if (config.f_ref_kHz == 250000) {
        loop_bw_res = 21;
        refclk_sel  = 2;
    // 312.5e6 is possible but not characterized => use 250e6 value which is best apporximation for now
    } else if (config.f_ref_kHz == 312500) {
        loop_bw_res = 21;
        refclk_sel  = 3;
    } else {
        VTSS_E("vtss_pll5g_setup: Reference clock frequence not supported. Using f_ref_kHz=125000kHz instead");
        loop_bw_res = 14;
        refclk_sel  = 0;
    }

    ret_val->unlock[0] = config.unlock;
    ret_val->lock[0]   = config.lock;
    // ----------------------------------------------------------------------
    if(config.chip_name == VTSS_PLL5G_CHIP_ES6514   ||
       config.chip_name == VTSS_PLL5G_CHIP_FERRET   ||
       config.chip_name == VTSS_PLL5G_CHIP_OCELOT   ||
       config.chip_name == VTSS_PLL5G_CHIP_JAGUAR2  ||
       config.chip_name == VTSS_PLL5G_CHIP_JAGUAR2C ||
       config.chip_name == VTSS_PLL5G_CHIP_SERVALT) {
        if(config.unlock) {
            ret_val->pll5g_cfg2__ena_gain_test[0] = 1; // unlock PLL
            ret_val->pll5g_cfg2__gain_test[0]     = 0; // force to low freq
        } else if (config.lock) {
            ret_val->pll5g_cfg2__ena_gain_test[0]  = 0; // lock PLL
        } else {
            ret_val->pll5g_cfg6__refclk_sel[0]     = refclk_sel;
            ret_val->pll5g_cfg4__ib_ctrl[0]        = 0x7600; // enable IB

            ret_val->pll5g_cfg0__ena_vco_contrh[0] = 0;
            ret_val->pll5g_cfg0__loop_bw_res[0]    = loop_bw_res;
            ret_val->pll5g_cfg0__selbgv820[0]      = config.selbgv820;

            ret_val->pll5g_cfg2__disable_fsm[0]    = 1; // toggle once
            ret_val->pll5g_cfg2__disable_fsm[1]    = 0;
        }
    } else if(config.chip_name == VTSS_PLL5G_CHIP_VENICE || config.chip_name == VTSS_PLL5G_CHIP_VENICE_C ||
              config.chip_name == VTSS_PLL5G_CHIP_MALIBU || config.chip_name == VTSS_PLL5G_CHIP_MALIBU_B) {
        if(config.chip_name == VTSS_PLL5G_CHIP_VENICE || config.chip_name == VTSS_PLL5G_CHIP_VENICE_C) {
            ena_vco_contrh = 1;
        } else {
            ena_vco_contrh = 0;
        }
        if(config.unlock) {
            ret_val->pll5g_cfg2__ena_gain_test[0] = 1; // unlock PLL
            ret_val->pll5g_cfg2__gain_test[0]     = 0; // force to low freq
        } else if (config.lock) {
            ret_val->pll5g_cfg2__ena_gain_test[0] = 0; // lock PLL
        } else {
            if(config.side == VTSS_HOST) {
                ret_val->pll5g_cfg4__ib_ctrl[0] = 0x7200; // enable IB
            } else {
                ret_val->pll5g_cfg4__ib_ctrl[0] = 0x7600; // enable IB
            }

            ret_val->pll5g_cfg0__ena_vco_contrh[0] = ena_vco_contrh;
            ret_val->pll5g_cfg0__loop_bw_res[0]    = loop_bw_res;
            ret_val->pll5g_cfg0__selbgv820[0]      = config.selbgv820;

            ret_val->pll5g_cfg2__disable_fsm[0]    = 1; // toggle once
            ret_val->pll5g_cfg2__disable_fsm[1]    = 0;
        }
    }

    // vts_wait 5 ;# wait until LCPLL has stabilized
    return rslt;
}

/* ******************************************************************************** */
/* ***                        E N D   O F    F I L E                            *** */
/* ******************************************************************************** */
