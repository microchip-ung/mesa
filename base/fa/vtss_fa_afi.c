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

#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_AFI
#include "vtss_fa_cil.h"
#include <unistd.h>
#include <sys/syscall.h>

#if defined(VTSS_ARCH_FA) && defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_AFI_V2)

/******************************************************************************/
//
// Internal CIL: Misc. functions
//
/******************************************************************************/

/******************************************************************************/
//
// Internal CIL: TTI functions
//
/******************************************************************************/

/******************************************************************************/
//
// External CIL: DTI functions
//
/******************************************************************************/

/*
 * fa_afi_dti_start()
 *
 * do_frm_delay_config: (Re)configure frame-delay sequence before (re)starting
 * do_dti_config:       (Re)configure DTI before (re)starting
 */
static vtss_rc fa_afi_dti_start(vtss_state_t *const vtss_state, u32 dti_idx, BOOL do_frm_delay_config, BOOL do_dti_config, BOOL start_flow)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_dti_stop()
 */
static vtss_rc fa_afi_dti_stop(vtss_state_t *const vtss_state, u32 dti_idx)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_dti_frm_hijack()
 */
static vtss_rc fa_afi_dti_frm_hijack(vtss_state_t *const vtss_state, u32 dti_idx, u32 frm_size)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_dti_frm_rm_inj()
 *
 * TOETBD: What if port has been stopped? (and not ServalT)
 */
static vtss_rc fa_afi_dti_frm_rm_inj(vtss_state_t *const vtss_state, u32 dti_idx)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_dti_cnt_get()
 */
static vtss_rc fa_afi_dti_cnt_get(vtss_state_t *const vtss_state, u32 dti_idx, u32 *const cnt)
{
    return VTSS_RC_OK;
}

/******************************************************************************/
//
// External CIL: TTI functions
//
/******************************************************************************/

/*
 * fa_afi_ttis_enable()
 */
static vtss_rc fa_afi_ttis_enable(vtss_state_t *const vtss_state)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_tti_start()
 *
 * do_config: (Re)configure TTI before (re)starting
 */
static vtss_rc fa_afi_tti_start(vtss_state_t *const vtss_state,  u32 tti_idx, BOOL do_config)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_tti_stop()
 */
static vtss_rc fa_afi_tti_stop(vtss_state_t *const vtss_state, u32 tti_idx)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_tti_frm_hijack()
 */
static vtss_rc fa_afi_tti_frm_hijack(vtss_state_t *const vtss_state, u32 tti_idx)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_tti_frm_rm_inj()
 *
 * TOETBD: What if port has been stopped (and not ServalT)?
 */
static vtss_rc fa_afi_tti_frm_rm_inj(vtss_state_t *const vtss_state, u32 tti_idx)
{
    return VTSS_RC_OK;
}

/******************************************************************************/
//
// External CIL: Other functions
//
/******************************************************************************/

/*
 * fa_afi_link_state_change()
 */
static vtss_rc fa_afi_link_state_change(vtss_state_t *const vtss_state, vtss_port_no_t port_no, BOOL *link_up)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_enable()
 */
static vtss_rc fa_afi_enable(vtss_state_t *const vtss_state)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_port_admin_start()
 *
 * Administrative port start
 * Upon init, the ports are in started state.
 */
static vtss_rc fa_afi_port_admin_start(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

/*
 * fa_afi_port_admin_stop()
 *
 * Administrative port stop
 * Upon init, the ports are in started state.
 */
static vtss_rc fa_afi_port_admin_stop(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

/*
 * vtss_fa_afi_debug_print()
 */
vtss_rc vtss_fa_afi_debug_print(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    return VTSS_RC_OK;
}

/*
 * vtss_fa_afi_init()
 */
vtss_rc vtss_fa_afi_init(vtss_state_t *const vtss_state, const vtss_init_cmd_t cmd)
{
    vtss_afi_state_t    *state = &vtss_state->afi;
    vtss_port_no_t      port_no;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        // Assign CIL function pointers
        state->afi_enable        = fa_afi_enable;
        state->ttis_enable       = fa_afi_ttis_enable;

        state->tti_start         = fa_afi_tti_start;
        state->tti_stop          = fa_afi_tti_stop;
        state->tti_frm_hijack    = fa_afi_tti_frm_hijack;
        state->tti_frm_rm_inj    = fa_afi_tti_frm_rm_inj;

        state->dti_start         = fa_afi_dti_start;
        state->dti_stop          = fa_afi_dti_stop;
        state->dti_frm_hijack    = fa_afi_dti_frm_hijack;
        state->dti_frm_rm_inj    = fa_afi_dti_frm_rm_inj;
        state->dti_cnt_get       = fa_afi_dti_cnt_get;

        state->port_admin_start  = fa_afi_port_admin_start;
        state->port_admin_stop   = fa_afi_port_admin_stop;
        state->link_state_change = fa_afi_link_state_change;


        // Initialize ports to started = 1. This corresponds to
        // calling jr2_afi_port_admin_start() during boot.
        for (port_no = 0; port_no < VTSS_ARRSZ(vtss_state->afi.port_tbl); port_no++) {
            vtss_state->afi.port_tbl[port_no].started = 1;
        }
        break;

    case VTSS_INIT_CMD_INIT:
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        break;

    case VTSS_INIT_CMD_POLL:
        break;

    default:
        break;
    }

    return VTSS_RC_OK;
}

#endif /* defined(VTSS_AFI_V2) && defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_ARCH_FA) */

