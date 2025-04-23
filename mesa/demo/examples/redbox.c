// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static struct {
    mesa_rb_id_t id;
} state;

static int redbox_init(int argc, const char *argv[])
{
    mesa_port_no_t port_a = ARGV_INT("port_a", "Port-A");
    mesa_port_no_t port_b = ARGV_INT("port_b", "Port-B");
    uint32_t       cnt;
    mesa_rb_id_t   id;
    mesa_rb_cap_t  cap;
    mesa_rb_conf_t conf;

    EXAMPLE_BARRIER(argc);

    // Look for RedBox with port A and B
    cnt = mesa_capability(NULL, MESA_CAP_L2_REDBOX_CNT);
    for (id = 0; id < cnt; id++) {
        RC(mesa_rb_cap_get(NULL, id, &cap));
        if (mesa_port_list_get(&cap.port_list, port_a) &&
            mesa_port_list_get(&cap.port_list, port_b)) {
            break;
        }
    }
    if (id >= cnt) {
        cli_printf("RedBox not found\n");
        return -1;
    }

    // Store state
    state.id = id;

    // Configure RedBox
    RC(mesa_rb_conf_get(NULL, id, &conf));
    conf.mode = MESA_RB_MODE_HSR_SAN;
    conf.port_a = port_a;
    conf.port_b = port_b;
    RC(mesa_rb_conf_set(NULL, id, &conf));

    return 0;
}

static void redbox_stat(const char *name, uint64_t cnt)
{
    char buf[80];

    sprintf(buf, "%s:", name);
    cli_printf("%-12s%19llu\n", buf, cnt);
}

static void redbox_node(uint8_t *m, mesa_bool_t san)
{
    cli_printf("MAC : %02x-%02x-%02x-%02x-%02x-%02x\n", m[0], m[1], m[2], m[3], m[4], m[5]);
    cli_printf("Type: %s\n", san ? "SAN" : "DAN");
}

static int redbox_run(int argc, const char *argv[])
{
    mesa_rc                  rc;
    mesa_rb_counters_t       cnt;
    mesa_rb_port_counters_t *c;
    mesa_rb_node_t           n = {};
    mesa_rb_proxy_node_t     p = {};
    uint32_t                 i;

    EXAMPLE_BARRIER(argc);

    // Counters
    RC(mesa_rb_counters_get(NULL, state.id, &cnt));
    for (i = 0; i < 3; i++) {
        c = (i == 0 ? &cnt.port_a : i == 1 ? &cnt.port_b : &cnt.port_c);
        cli_printf("Port %s counters:\n", i == 0 ? "A" : i == 1 ? "B" : "C");
        redbox_stat("Rx Untagged", c->rx_untagged);
        redbox_stat("Rx Tagged", c->rx_tagged);
        redbox_stat("Tx Untagged", c->tx_untagged);
        redbox_stat("Tx Tagged", c->tx_tagged);
        cli_printf("\n");
    }

    // Node table
    for (i = 0; i < 3; i++) {
        rc = mesa_rb_node_get_next(NULL, state.id, &n.mac, &n);
        if (rc != MESA_RC_OK) {
            break;
        }
        if (i == 0) {
            cli_printf("Node table:\n\n");
        }
        redbox_node(n.mac.addr, n.type == MESA_RB_NODE_TYPE_SAN);
        cli_printf("Rx A: %llu\n", n.port_a.cnt.rx);
        cli_printf("Rx B: %llu\n", n.port_b.cnt.rx);
        cli_printf("\n");
    }

    // Proxy node table
    for (i = 0; i < 3; i++) {
        rc = mesa_rb_proxy_node_get_next(NULL, state.id, &p.mac, &p);
        if (rc != MESA_RC_OK) {
            break;
        }
        if (i == 0) {
            cli_printf("Proxy node table:\n\n");
        }
        redbox_node(p.mac.addr, p.type == MESA_RB_PROXY_NODE_TYPE_SAN);
        cli_printf("Rx C: %llu\n", p.cnt.rx);
        cli_printf("\n");
    }

    return 0;
}

static int redbox_uninit(void)
{
    mesa_rb_conf_t conf;

    // Restore RedBox configuration
    RC(mesa_rb_conf_get(NULL, state.id, &conf));
    conf.mode = MESA_RB_MODE_DISABLED;
    RC(mesa_rb_conf_set(NULL, state.id, &conf));

    return 0;
}

static const char *redbox_help(void) { return "RedBox example"; }

EXAMPLE(redbox, redbox_init, redbox_run, redbox_uninit, redbox_help);
