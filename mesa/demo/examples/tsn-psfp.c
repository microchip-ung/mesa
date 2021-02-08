// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static struct {
    mesa_iflow_id_t         iflow_id;
    mesa_ingress_cnt_id_t   icnt_id;
    mesa_psfp_filter_id_t   filter_id;
    mesa_psfp_filter_conf_t filter_conf;
    mesa_psfp_gate_id_t     gate_id;
    mesa_psfp_gate_conf_t   gate_conf;
} state;

static int psfp_init(int argc, const char *argv[])
{
    mesa_port_no_t          iport = ARGV_INT("iport", "Ingress port");
    mesa_psfp_gce_t         psfp_gcl[2];
    mesa_psfp_gate_conf_t   gate_conf;
    mesa_psfp_filter_conf_t filter_conf;
    mesa_iflow_conf_t       iflow_conf; 
    mesa_vce_t              vce;
    int                     i, max_cnt = 2;

    EXAMPLE_BARRIER(argc);

    if (mesa_capability(NULL, MESA_CAP_L2_PSFP) == 0) {
        cli_printf("PSFP not supported\n");
        return -1;
    }

    memset(&state, 0, sizeof(state));

    // Setup PSFP gate control list
    RC(mesa_psfp_gate_conf_get(NULL, state.gate_id, &gate_conf));
    state.gate_conf = gate_conf;
    for (i = 0; i < max_cnt; i++) {
        mesa_psfp_gce_t *gce = &psfp_gcl[i];
        memset(gce, 0, sizeof(*gce));
        /* Open for 100 usec, closed for 100 usec */
        gce->gate_open = (i == 0 ? 1 : 0);
        gce->time_interval = 100000;
        gate_conf.config.cycle_time += gce->time_interval;
    }
    RC(mesa_psfp_gcl_conf_set(NULL, state.gate_id, max_cnt, psfp_gcl));
    gate_conf.enable = 1;
    gate_conf.config_change = 1;
    RC(mesa_psfp_gate_conf_set(NULL, state.gate_id, &gate_conf));

    // Map filter to gate
    RC(mesa_psfp_filter_conf_get(NULL, state.filter_id, &filter_conf));
    state.filter_conf = filter_conf;
    filter_conf.gate_enable = 1;
    filter_conf.gate_id = state.gate_id;
    filter_conf.max_sdu = 1300;
    RC(mesa_psfp_filter_conf_set(NULL, state.filter_id, &filter_conf));

    // Allocate ingress counters
    RC(mesa_ingress_cnt_alloc(NULL, 1, &state.icnt_id));

    // Allocate iflow for PSFP and map to counters and filter
    RC(mesa_iflow_alloc(NULL, &state.iflow_id));
    RC(mesa_iflow_conf_get(NULL, state.iflow_id, &iflow_conf));
    iflow_conf.cnt_enable = 1;
    iflow_conf.cnt_id = state.icnt_id;
    iflow_conf.psfp.filter_enable = 1;
    iflow_conf.psfp.filter_id = state.filter_id;
    iflow_conf.cut_through_disable = 1;
    RC(mesa_iflow_conf_set(NULL, state.iflow_id, &iflow_conf));

    // On ingress port map to iflow
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ANY, &vce));
    vce.id = 1;
    mesa_port_list_set(&vce.key.port_list, iport, 1);
    vce.action.flow_id = state.iflow_id;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));

    return 0;
}

static void psfp_stat(const char *name, uint64_t cnt)
{
    char buf[80];

    sprintf(buf, "Rx %s:", name);
    cli_printf("%-19s%19llu\n", buf, cnt);
}

static int psfp_run(int argc, const char *argv[])
{
    mesa_ingress_counters_t c;

    EXAMPLE_BARRIER(argc);

    RC(mesa_ingress_cnt_get(NULL, state.icnt_id, 0, &c));
    cli_printf("Ingress counters:\n");
    psfp_stat("Green", c.rx_green.frames);
    psfp_stat("Yellow", c.rx_yellow.frames);
    psfp_stat("Red", c.rx_red.frames);
    psfp_stat("Match", c.rx_match);
    psfp_stat("Gate Pass", c.rx_gate_pass);
    psfp_stat("Gate Discard", c.rx_gate_discard);
    psfp_stat("SDU Pass", c.rx_sdu_pass);
    psfp_stat("SDU Discard", c.rx_sdu_discard);

    return 0;
}

static int psfp_uninit(void)
{
    RC(mesa_psfp_gate_conf_set(NULL, state.gate_id, &state.gate_conf));
    RC(mesa_psfp_filter_conf_set(NULL, state.filter_id, &state.filter_conf));
    RC(mesa_ingress_cnt_free(NULL, state.icnt_id));
    RC(mesa_iflow_free(NULL, state.iflow_id));
    RC(mesa_vce_del(NULL, 1));
    return 0;
}

static const char *psfp_help(void)
{
    return "PSFP example\n";
}

EXAMPLE(psfp, psfp_init, psfp_run, psfp_uninit, psfp_help);
