// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

const char *bulk_help_txt = "\
This is a port_conf_bulk test.\n\
\n\
There are two required parameters, 'from' and 'to' port.\n\
The test will apply bulk configuration to those ports.\n\
";

static int port_bulk_init(int argc, const char *argv[])
{
    uint32_t port_from = ARGV_INT("port1", "Apply config from this port");
    uint32_t port_to = ARGV_INT("port2", "Apply config to this port");
    uint32_t port_no;
    mesa_port_conf_t conf, *store;
    uint32_t   port_cnt = mesa_port_cnt(NULL);

    EXAMPLE_BARRIER(argc);

    if ((store = calloc(port_cnt, sizeof(*store))) == NULL) {
        return -1;
    }

    // Force some configuration onto the ports to make them different - which enables re-config.
    for (port_no = port_from; port_no <= port_to; port_no++) {
        RC(mesa_port_conf_get(NULL, port_no, &conf));
        store[port_no] = conf;
        conf.speed = MESA_SPEED_100M;
        conf.if_type = MESA_PORT_INTERFACE_100FX;
        (void)mesa_port_conf_set(NULL, port_no, &conf);
    }

    // Enable bulk config
    if (mesa_capability(NULL, MESA_CAP_PORT_CONF_BULK)) {
        RC(mesa_port_conf_bulk_set(NULL, MESA_PORT_BULK_ENABLED));
    }

    // Apply the original configuration to the API (without applying to HW)
    for (port_no = port_from; port_no <= port_to; port_no++) {
        RC(mesa_port_conf_set(NULL, port_no, &store[port_no]));
    }

    // Apply the stored configuration in 'bulk' manner
    if (mesa_capability(NULL, MESA_CAP_PORT_CONF_BULK)) {
        RC(mesa_port_conf_bulk_set(NULL, MESA_PORT_BULK_APPLY));
    }

    return 0;
}

static int port_bulk_clean()
{
    return 0;
}

static const char* port_bulk_help()
{
    return bulk_help_txt;
}

EXAMPLE(port_conf_bulk, port_bulk_init, NULL, port_bulk_clean, port_bulk_help);
