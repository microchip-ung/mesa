// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#include "vtss_fa_cil.h"

// Avoid "vtss_api.h not used in module vtss_fa_fdma.c"
/*lint --e{766} */
#if defined(VTSS_OPT_VCORE_IV) && VTSS_OPT_FDMA && defined(VTSS_ARCH_FA)
#include "../ail/vtss_fdma.h"
#include "../ail/vtss_fdma_common.h"

// We don't operate with assertions in the API, so we print an error and
// gracefully return. Note: This macro is sometimes used with code that MUST be
// executed - even on non-debug builds -, so if you don't like to have VTSS_EG()
// calls, then rewrite the macro to avoid that call.
#define FDMA_ASSERT(grp, expr, code)                                           \
    do {                                                                       \
        if (!(expr)) {                                                         \
            VTSS_EG((VTSS_TRACE_GROUP_FDMA_##grp), "Assert failed: " #expr);   \
            code                                                               \
        }                                                                      \
    } while (0);

#define FDMA_INLINE inline

/*****************************************************************************/
//
// PRIVATE FUNCTIONS
//
//****************************************************************************/

/*****************************************************************************/
// fa_fdma_xtr_dcb_init()
/*****************************************************************************/
static vtss_rc fa_fdma_xtr_dcb_init(vtss_state_t *const vstate,
                                    vtss_fdma_ch_t      xtr_ch,
                                    fdma_sw_dcb_t      *list,
                                    u32                 cfg_alloc_len)
{
    return VTSS_RC_OK;
}

/*****************************************************************************/
// fa_fdma_xtr_connect()
// This function must be called with interrupts disabled, so that no context
// switches can occur, since it manipulates list pointers that are used in
// IRQ (DSR) context.
/*****************************************************************************/
static void fa_fdma_xtr_connect(vtss_state_t *const vstate,
                                fdma_hw_dcb_t      *tail,
                                fdma_hw_dcb_t      *more)
{
}

/*****************************************************************************/
// fa_fdma_xtr_restart_ch()
// We need to feed the channel with a new list of DCBs (if any).
// This function must be called with interrupts disabled.
/*****************************************************************************/
static BOOL fa_fdma_xtr_restart_ch(vtss_state_t *const vstate,
                                   vtss_fdma_ch_t      xtr_ch)
{
    return TRUE;
}

/*****************************************************************************/
// fa_fdma_start_ch()
/*****************************************************************************/
static void fa_fdma_start_ch(vtss_state_t *const  vstate,
                             const vtss_fdma_ch_t ch)
{
}

/*****************************************************************************/
// xtr_qu_suspend_set()
/*****************************************************************************/
static void fa_fdma_xtr_qu_suspend_set(vtss_state_t *const    vstate,
                                       vtss_packet_rx_queue_t xtr_qu,
                                       BOOL                   do_suspend)
{
}

/*****************************************************************************/
// fa_fdma_inj_restart_ch()
/*****************************************************************************/
static vtss_rc fa_fdma_inj_restart_ch(vtss_state_t *const vstate,
                                      vtss_fdma_ch_t      inj_ch,
                                      fdma_sw_dcb_t      *head,
                                      BOOL                do_start,
                                      BOOL                thread_safe)
{
    return VTSS_RC_OK;
}

/*****************************************************************************/
//
// PUBLIC FUNCTIONS
//
//****************************************************************************/

/*****************************************************************************/
// fa_fdma_init_conf_set()
/*****************************************************************************/
static vtss_rc fa_fdma_init_conf_set(vtss_state_t *const vstate)
{
    return VTSS_RC_OK;
}

/*****************************************************************************/
// fa_fdma_uninit()
/*****************************************************************************/
static vtss_rc fa_fdma_uninit(vtss_state_t *const vstate) { return VTSS_RC_OK; }

/*****************************************************************************/
// fa_fdma_tx()
/*****************************************************************************/
static vtss_rc fa_fdma_tx(vtss_state_t *const          vstate,
                          fdma_sw_dcb_t               *sw_dcb,
                          vtss_fdma_tx_info_t *const   fdma_info,
                          vtss_packet_tx_info_t *const tx_info,
                          BOOL                         afi_cancel)
{
    return VTSS_RC_OK;
}

/*****************************************************************************/
// fa_fdma_stats_clr()
/*****************************************************************************/
static vtss_rc fa_fdma_stats_clr(vtss_state_t *const vstate)
{
    return VTSS_RC_OK;
}

/*****************************************************************************/
// fa_debug_print()
/*****************************************************************************/
static vtss_rc fa_debug_print(vtss_state_t *const            vstate,
                              const vtss_debug_printf_t      pr,
                              const vtss_debug_info_t *const info)
{
    return VTSS_RC_OK;
}

/*****************************************************************************/
// fa_fdma_irq_handler()
/*****************************************************************************/
static vtss_rc fa_fdma_irq_handler(vtss_state_t *const vstate,
                                   void *const         cntxt)
{
    return VTSS_RC_OK;
}

/*****************************************************************************/
// fa_fdma_func_init()
// Initialize current global state's function pointers.
// This is the only real public function.
/*****************************************************************************/
void fa_fdma_func_init(vtss_state_t *vtss_state)
{
    fdma_func_t *func = &vtss_state->fdma_state.fdma_func;

    // Internal functions
    func->fdma_init_conf_set = fa_fdma_init_conf_set;
    func->fdma_xtr_qu_suspend_set = fa_fdma_xtr_qu_suspend_set;
    func->fdma_xtr_dcb_init = fa_fdma_xtr_dcb_init;
    func->fdma_xtr_connect = fa_fdma_xtr_connect;
    func->fdma_xtr_restart_ch = fa_fdma_xtr_restart_ch;
    func->fdma_inj_restart_ch = fa_fdma_inj_restart_ch;
    func->fdma_start_ch = fa_fdma_start_ch;

    // External functions
    func->fdma_uninit = fa_fdma_uninit;
    func->fdma_stats_clr = fa_fdma_stats_clr;
    func->fdma_debug_print = fa_debug_print;
    func->fdma_irq_handler = fa_fdma_irq_handler;
    func->fdma_tx = fa_fdma_tx;
}

#endif /* defined(VTSS_OPT_VCORE_IV) && VTSS_OPT_FDMA && defined(VTSS_ARCH_FA) \
        */

/*****************************************************************************/
//
// End of file
//
//****************************************************************************/
