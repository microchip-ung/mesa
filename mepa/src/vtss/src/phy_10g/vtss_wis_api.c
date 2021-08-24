// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// Avoid "vtss_api.h not used in module vtss_wis_api.c"
/*lint --e{766} */
#include "vtss_phy_api.h"
#if defined(VTSS_FEATURE_WIS)
#include "../common/vtss_phy_common.h"

#define VTSS_PHY_EWIS_ASSERT(x) if(x) { return VTSS_RC_ERROR;}

/* ================================================================= *
 *  Defects/Events
 * ================================================================= */

vtss_rc vtss_ewis_event_enable(const vtss_inst_t         inst,
                               const vtss_port_no_t      port_no,
                               const BOOL                enable,
                               const vtss_ewis_event_t   ev_mask)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_events_conf_set, port_no, enable, ev_mask);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_event_poll(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             vtss_ewis_event_t     *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(status == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_events_poll, port_no, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_event_force(const vtss_inst_t        inst,
                              const vtss_port_no_t     port_no,
                              const BOOL               enable,
                              const vtss_ewis_event_t  ev_force)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if (((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) && (ev_force)) {
        rc = VTSS_FUNC_COLD(cil.ewis_events_force, port_no, enable, ev_force);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_static_conf_get(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  vtss_ewis_static_conf_t *const stat_conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(stat_conf == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *stat_conf = vtss_state->ewis_conf[port_no].static_conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_force_conf_set(const vtss_inst_t inst,
                                 const vtss_port_no_t port_no,
                                 const vtss_ewis_force_mode_t *const force_conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(force_conf == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ewis_conf[port_no].force_mode = *force_conf;
        rc = VTSS_FUNC_COLD(cil.ewis_force_conf_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_force_conf_get(const vtss_inst_t inst,
                                 const vtss_port_no_t port_no,
                                 vtss_ewis_force_mode_t *const force_conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(force_conf == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *force_conf = vtss_state->ewis_conf[port_no].force_mode;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_tx_oh_set(const vtss_inst_t inst,
                            const vtss_port_no_t port_no,
                            const vtss_ewis_tx_oh_t *const tx_oh)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(tx_oh == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ewis_conf[port_no].tx_oh = *tx_oh;
        rc = VTSS_FUNC_COLD(cil.ewis_tx_oh_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_tx_oh_get(const vtss_inst_t inst,
                            const vtss_port_no_t port_no,
                            vtss_ewis_tx_oh_t *const tx_oh)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(tx_oh == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *tx_oh = vtss_state->ewis_conf[port_no].tx_oh;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_tx_oh_passthru_set(const vtss_inst_t inst,
                                     const vtss_port_no_t port_no,
                                     const vtss_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(tx_oh_passthru == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ewis_conf[port_no].tx_oh_passthru = *tx_oh_passthru;
        rc = VTSS_FUNC_COLD(cil.ewis_tx_oh_passthru_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_tx_oh_passthru_get(const vtss_inst_t inst,
                                     const vtss_port_no_t port_no,
                                     vtss_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(tx_oh_passthru == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *tx_oh_passthru = vtss_state->ewis_conf[port_no].tx_oh_passthru;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_exp_sl_set (const vtss_inst_t inst,
                          const vtss_port_no_t port_no,
                          const vtss_ewis_sl_conf_t * const sl)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(sl == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ewis_conf[port_no].exp_sl = *sl;
        rc = VTSS_FUNC_COLD(cil.ewis_exp_sl_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

/* ================================================================= *
 *  Dynamic Config
 * ================================================================= */

vtss_rc vtss_ewis_mode_set(const vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           const vtss_ewis_mode_t *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(mode == NULL);
    VTSS_ENTER();
    if (((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) && (*mode < VTSS_WIS_OPERMODE_MAX)) {
        vtss_state->ewis_conf[port_no].ewis_mode = *mode;
        rc = VTSS_FUNC_COLD(cil.ewis_mode_conf_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_mode_get(const vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           vtss_ewis_mode_t *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(mode == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *mode = vtss_state->ewis_conf[port_no].ewis_mode;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_reset(const vtss_inst_t inst,
                       const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK ) {
        rc = VTSS_FUNC_COLD(cil.ewis_reset, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_cons_act_set(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               const vtss_ewis_cons_act_t *const cons_act)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(cons_act == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ewis_conf[port_no].section_cons_act = *cons_act;
        rc = VTSS_FUNC_COLD(cil.ewis_cons_action_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_cons_act_get(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               vtss_ewis_cons_act_t *const cons_act)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(cons_act == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *cons_act = vtss_state->ewis_conf[port_no].section_cons_act;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_section_txti_set(const vtss_inst_t inst,
                                   const vtss_port_no_t port_no,
                                   const vtss_ewis_tti_t *const txti)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(txti == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK && txti->mode < TTI_MODE_MAX) {
        vtss_state->ewis_conf[port_no].section_txti = *txti;
        rc = VTSS_FUNC_COLD(cil.ewis_section_txti_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_section_txti_get(const vtss_inst_t inst,
                                   const vtss_port_no_t port_no,
                                   vtss_ewis_tti_t *const txti)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(txti == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *txti = vtss_state->ewis_conf[port_no].section_txti;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_path_txti_set(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                const vtss_ewis_tti_t *const txti)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(txti == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK && txti->mode < TTI_MODE_MAX) {
        vtss_state->ewis_conf[port_no].path_txti = *txti;
        rc = VTSS_FUNC_COLD(cil.ewis_path_txti_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_ewis_path_txti_get(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_tti_t *const txti)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(txti == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *txti = vtss_state->ewis_conf[port_no].path_txti;
    }
    VTSS_EXIT();
    return rc;
}


/* ================================================================= *
 *  Test Config/status
 * ================================================================= */

vtss_rc vtss_ewis_test_mode_set(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                const vtss_ewis_test_conf_t *const test_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(test_mode == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ewis_conf[port_no].test_conf = *test_mode;
        rc = VTSS_FUNC_COLD(cil.ewis_test_mode_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_test_mode_get(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_test_conf_t *const test_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(test_mode == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *test_mode = vtss_state->ewis_conf[port_no].test_conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_prbs31_err_inj_set(const vtss_inst_t inst,
                                     const vtss_port_no_t port_no,
                                     const vtss_ewis_prbs31_err_inj_t *const inj)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(inj == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_prbs31_err_inj_set, port_no, inj);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_ewis_test_counter_get(const vtss_inst_t inst,
                                   const vtss_port_no_t port_no,
                                   vtss_ewis_test_status_t *const test_status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(test_status == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_test_status_get, port_no, test_status);
    }
    VTSS_EXIT();
    return rc;
}


/* ================================================================= *
 *  State Reporting
 * ================================================================= */

vtss_rc vtss_ewis_defects_get(const vtss_inst_t inst,
                              const vtss_port_no_t port_no,
                              vtss_ewis_defects_t *const def)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(def == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_defects_get, port_no, def);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_ewis_status_get(const vtss_inst_t inst,
                             const vtss_port_no_t port_no,
                             vtss_ewis_status_t *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(status == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_status_get, port_no, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_section_acti_get(const vtss_inst_t inst,
                                   const vtss_port_no_t port_no,
                                   vtss_ewis_tti_t *const acti)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(acti == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_section_acti_get, port_no, acti);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_path_acti_get(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_tti_t *const acti)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(acti == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_path_acti_get, port_no, acti);
    }
    VTSS_EXIT();
    return rc;
}


/* ================================================================= *
 *  Performance Primitives
 * ================================================================= */

vtss_rc vtss_ewis_perf_get(const vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           vtss_ewis_perf_t *const perf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(perf == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_perf_get, port_no, perf);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_counter_get(const vtss_inst_t      inst,
                              const vtss_port_no_t   port_no,
                              vtss_ewis_counter_t *const counter)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(counter == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(cil.ewis_counter_get, port_no, counter);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_perf_mode_set(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_perf_mode_t const* perf_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(perf_mode == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ewis_conf[port_no].perf_mode = *perf_mode;
        rc = VTSS_FUNC_COLD(cil.ewis_perf_mode_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_perf_mode_get(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_perf_mode_t *const perf_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(perf_mode == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *perf_mode = vtss_state->ewis_conf[port_no].perf_mode;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_counter_threshold_set(const vtss_inst_t inst,
                                        const vtss_port_no_t port_no,
                                        const vtss_ewis_counter_threshold_t *const threshold)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(threshold == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ewis_conf[port_no].ewis_cntr_thresh_conf = *threshold;
        rc = VTSS_FUNC_COLD(cil.ewis_counter_threshold_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ewis_counter_threshold_get(const vtss_inst_t inst,
                                        const vtss_port_no_t port_no,
                                        vtss_ewis_counter_threshold_t *const threshold)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_PHY_EWIS_ASSERT(threshold == NULL);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *threshold = vtss_state->ewis_conf[port_no].ewis_cntr_thresh_conf;
    }
    VTSS_EXIT();
    return rc;
}
#endif /*VTSS_FEATURE_WIS */
