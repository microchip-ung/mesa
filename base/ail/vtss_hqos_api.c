// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_HQOS
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"

#if defined(VTSS_FEATURE_HQOS)

static BOOL find_hqos_id(vtss_hqos_hier_port_t *hier, vtss_hqos_id_t hqos_id, u32 *l0_index)
{
    for (*l0_index = 0; *l0_index < VTSS_HQOS_PORT_L0_MAX; ++*l0_index) {
        if ((hier->l0_ses[*l0_index].se != VTSS_HQOS_SE_NONE) &&
            (hier->l0_ses[*l0_index].hqos_id == hqos_id)) {
            return TRUE;
        }
    }
    return FALSE;
}

/* - API functions ------------------------------------------------- */

vtss_rc vtss_hqos_port_conf_get(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                vtss_hqos_port_conf_t *const conf)
{
    vtss_rc       rc = VTSS_RC_OK;
    vtss_state_t *vtss_state;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->hqos.port_conf[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_hqos_port_conf_set(const vtss_inst_t                  inst,
                                const vtss_port_no_t               port_no,
                                const vtss_hqos_port_conf_t *const conf)
{
    vtss_rc                rc = VTSS_RC_OK;
    vtss_state_t          *vtss_state;
    vtss_hqos_port_conf_t *port_conf;
#if defined(VTSS_FEATURE_AFI_SWC)
    BOOL afi_link;
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

    VTSS_ENTER();
    VTSS_D("port_no: %u", port_no);

    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) != VTSS_RC_OK) {
        goto do_exit;
    }

    port_conf = &vtss_state->hqos.port_conf[port_no];
    if (port_conf->sch_mode == conf->sch_mode) {
        goto do_exit;
    }
    *port_conf = *conf;

#if defined(VTSS_FEATURE_AFI_SWC)
    // Pause all AFI-generated flows ingressing and egressing this port.
    // This must be done prior to actually reconfiguring the port, so that it
    // can be flushed if necessary.
    afi_link = FALSE;
    VTSS_I("Stopping AFI on port_no %u", port_no);
    (void)vtss_cil_afi_link_state_change(vtss_state, port_no, &afi_link);
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

    rc = vtss_cil_hqos_port_conf_set(vtss_state, port_no);

#if defined(VTSS_FEATURE_AFI_SWC)
    // Before possibly resuming AFI-generated flows on this port, we gotta go
    // through all of them and update the queue numbers, which may have been
    // changed by the above HQOS call.
    VTSS_I("Reconfiguring AFI flows on port_no %u", port_no);
    (void)vtss_cil_afi_qu_ref_update(vtss_state, port_no);

    // Resume AFI-generated flows on this port if it had link prior to calling
    // this function. Link change is only controlled by vtss_port_state_set().
    if (afi_link) {
        VTSS_I("Resuming AFI on port_no %u", port_no);
        (void)vtss_cil_afi_link_state_change(vtss_state, port_no, &afi_link);
    }
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

do_exit:
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_hqos_add(const vtss_inst_t             inst,
                      const vtss_port_no_t          port_no,
                      const vtss_hqos_id_t          hqos_id,
                      const vtss_hqos_conf_t *const conf)
{
    vtss_rc       rc = VTSS_RC_OK;
    vtss_state_t *vtss_state;

    VTSS_D("hqos_id: %u", hqos_id);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (hqos_id >= VTSS_HQOS_ID_MAX) {
            VTSS_E("Illegal hqos_id: %u", hqos_id);
            rc = VTSS_RC_ERROR;
        } else {
            rc = vtss_cil_hqos_add(vtss_state, port_no, hqos_id, conf);
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_hqos_del(const vtss_inst_t    inst,
                      const vtss_port_no_t port_no,
                      const vtss_hqos_id_t hqos_id)
{
    vtss_rc       rc = VTSS_RC_OK;
    vtss_state_t *vtss_state;
    u32           l0_index;

    VTSS_D("hqos_id: %u", hqos_id);
    VTSS_ENTER();
    if (((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) && (hqos_id < VTSS_HQOS_ID_MAX) &&
        (TRUE == find_hqos_id(&vtss_state->hqos.hier_conf[port_no], hqos_id, &l0_index))) {
        rc = vtss_cil_hqos_del(vtss_state, port_no, hqos_id);
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_hqos_get(const vtss_inst_t       inst,
                      const vtss_port_no_t    port_no,
                      const vtss_hqos_id_t    hqos_id,
                      vtss_hqos_conf_t *const conf)
{
    vtss_rc       rc = VTSS_RC_OK;
    vtss_state_t *vtss_state;
    u32           l0_index;

    VTSS_D("hqos_id: %u", hqos_id);
    VTSS_ENTER();
    memset(conf, 0, sizeof(*conf));
    conf->shaper.rate = VTSS_BITRATE_DISABLED;
// For now queue shaper is not implemented due to chip restrictions
#if 0
    for (prio = 0; prio < VTSS_QUEUE_ARRAY_SIZE; ++prio) {
        conf->shaper_queue[prio].rate = VTSS_BITRATE_DISABLED;
    }
#endif

    if (((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) && (hqos_id < VTSS_HQOS_ID_MAX) &&
        (TRUE == find_hqos_id(&vtss_state->hqos.hier_conf[port_no], hqos_id, &l0_index))) {
        (*conf) = vtss_state->hqos.hier_conf[port_no].l0_ses[l0_index].conf;
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_hqos_status_get(const vtss_inst_t         inst,
                             const vtss_port_no_t      port_no,
                             const vtss_hqos_id_t      hqos_id,
                             vtss_hqos_status_t *const status)
{
    vtss_rc       rc = VTSS_RC_OK;
    vtss_state_t *vtss_state;
    u32           l0_index;

    VTSS_D("hqos_id: %u", hqos_id);
    VTSS_ENTER();
    memset(status, 0, sizeof(*status));

    if (((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) && (hqos_id < VTSS_HQOS_ID_MAX) &&
        (TRUE == find_hqos_id(&vtss_state->hqos.hier_conf[port_no], hqos_id, &l0_index))) {
        vtss_cil_hqos_status_get(vtss_state, port_no, hqos_id, status);
    }
    VTSS_EXIT();

    return rc;
}

/* - Warm start synchronization ------------------------------------ */

#if defined(VTSS_FEATURE_WARM_START)
vtss_rc vtss_hqos_restart_sync(vtss_state_t *vtss_state)
{
    //    vtss_port_no_t port_no;
    //
    //    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
    //        vtss_state->hqos.port_conf_old = vtss_state->hqos.port_conf[port_no];
    //        VTSS_FUNC_RC(hqos.port_conf_set, port_no);
    //    }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_WARM_START */

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_hqos_inst_create(vtss_state_t *vtss_state) { return VTSS_RC_OK; }

/* - Debug print --------------------------------------------------- */

void vtss_hqos_debug_print(struct vtss_state_s           *vtss_state,
                           lmu_ss_t                      *ss,
                           const vtss_debug_info_t *const info)
{
}
#endif /* VTSS_FEATURE_HQOS */
