/*
Copyright (c) 2004-2018 Microsemi Corporation "Microsemi"

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

/*---------------------------------------------------------------------------
 * $HeadURL: svn://svn-de.vitesse.com/svn-de/vtslibs/vts_ute_tcllib/tags/UTE_release_vts_ute_tcllib_20180312_trunk_bjo/api_c/vtss_sd10g65_jaguar2_apc_procs.h $
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


#ifndef _VTSS_SD10G65_JAGUAR2_APC_PROCS_H_
#define _VTSS_SD10G65_JAGUAR2_APC_PROCS_H_

#include <vtss/api/options.h>  // To get the ARCH define
#if defined(VTSS_ARCH_JAGUAR_2_B)

#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#else
#include <vtss/api/types.h>
#endif

/** \brief sd10g65 lc_softctrl algoritm parameters   */
typedef struct vtss_sd10g65_jaguar2_lc_softctrl_cfg_t {
    u8   mode;           /**<  Set LC-softctrl algorithm (mode 1 or 2) */
    u16  iterations;     /**<  Set number of iterations  */
    u8   iter_delay;     /**<  Set delay between iterations */
    u8   dfe1_target;    /**<  Set target value for DFE1 */
    u8   dfe2_target;    /**<  Set target value for DFE2 */
    u8   eqz_l_div;      /**<  Set eqz_l divider value for mode 1 */
    u16  agc_threshold;  /**<  Set agc_threshold for mode 2 */
    u8   dfe1_threshold; /**<  Set dfe1_threshold for mode 2 */
    u8   dfe2_threshold; /**<  Set dfe2_threshold for mode 2 */ 
    BOOL observe;        /**<  Print intermediate parameter values per step */
} vtss_sd10g65_jaguar2_lc_softctrl_args_t;

/* ================================================================= *
 *  Function prototypes
 * ================================================================= */
vtss_rc vtss_sd10g65_jaguar2_lc_softctrl_args_init(vtss_sd10g65_jaguar2_lc_softctrl_args_t  *const init_val);
vtss_rc vtss_sd10g65_jaguar2_lc_softctrl(vtss_state_t                                  *vtss_state,
                                         const vtss_sd10g65_jaguar2_lc_softctrl_args_t config,
                                         const vtss_port_no_t                          port_no);


#endif
#endif

/* ******************************************************************************** */
/* ***                        E N D   O F    F I L E                            *** */
/* ******************************************************************************** */
