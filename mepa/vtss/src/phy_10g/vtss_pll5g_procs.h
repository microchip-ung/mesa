// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/*---------------------------------------------------------------------------
 * $HeadURL: svn://svn-de.vitesse.com/svn-de/vtslibs/vts_ute_tcllib/tags/UTE_release_vts_ute_tcllib_20180312_trunk_bjo/api_c/vtss_pll5g_procs.h $
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

#ifndef _VTSS_PLL5G_PROCS_H_
#define _VTSS_PLL5G_PROCS_H_

#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#endif

/* ================================================================= *
 *  Data structures / types
 * ================================================================= */
/** \brief Vitesse chip development name */
typedef enum {
    VTSS_PLL5G_CHIP_ES65XX,
    VTSS_PLL5G_CHIP_ES6512,
    VTSS_PLL5G_CHIP_ES6514,
    VTSS_PLL5G_CHIP_JAGUAR2,
    VTSS_PLL5G_CHIP_JAGUAR2C,
    VTSS_PLL5G_CHIP_VENICE,
    VTSS_PLL5G_CHIP_VENICE_C,
    VTSS_PLL5G_CHIP_MALIBU,
    VTSS_PLL5G_CHIP_MALIBU_B,
    VTSS_PLL5G_CHIP_SERVALT,
    VTSS_PLL5G_CHIP_ROLEX,
    VTSS_PLL5G_CHIP_FERRET,
    VTSS_PLL5G_CHIP_OCELOT,
    VTSS_PLL5G_CHIP_LAST
} vtss_pll5g_chip_name_t;

typedef enum {
    VTSS_HOST,    // Venice and Malibu
    VTSS_CLIENT,
    VTSS_LINE,    // Venice and Malibu
    VTSS_LTC,
} vtss_pll5g_side;

typedef struct {
    vtss_pll5g_chip_name_t chip_name;   // Name of the vitesse chip
    u8                     selbgv820;   // Set the bandgap voltage value
    vtss_pll5g_side        side;
    u32                    f_ref_kHz;   // Set reference clock frequency (in kHz) to adjust loop bandwidth resistor
    BOOL                   unlock;      // Unlock PLL from reference clock (no other cfg steps are applied)
    BOOL                   lock;        // Lock PLL to reference clock after unlock (no other cfg steps are applied)
} vtss_pll5g_setup_args_t;


/** \brief return values of calc_pll5g_setup function */
typedef struct {
    u8  unlock[1];
    u8  lock[1];
    u8  pll5g_cfg2__ena_gain_test[1];
    u8  pll5g_cfg2__gain_test[1];
    u8  pll5g_cfg2__disable_fsm[2];
    u16 pll5g_cfg4__ib_ctrl[1];
    u8  pll5g_cfg0__ena_vco_contrh[1];
    u8  pll5g_cfg0__loop_bw_res[1];
    u8  pll5g_cfg0__selbgv820[1];
    u8  pll5g_cfg6__refclk_sel[1];
 } vtss_pll5g_setup_struct_t;


/* ================================================================= *
 *  Function prototypes
 * ================================================================= */
vtss_rc vtss_pll5g_setup_args_init (vtss_pll5g_setup_args_t *const init_val);

vtss_rc vtss_calc_pll5g_setup(const vtss_pll5g_setup_args_t config,
                              vtss_pll5g_setup_struct_t *const ret_val);

#endif
