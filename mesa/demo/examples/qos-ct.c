/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "mscc/ethernet/switch/api.h"

static struct {
    mesa_port_no_t       iport;
    mesa_port_no_t       eport;
    mesa_qos_port_conf_t conf;
} state;

static int ct_init(int argc, const char *argv[])
{
    mesa_port_no_t       iport = ARGV_INT("iport", "Ingress port");
    mesa_port_no_t       eport = ARGV_INT("eport", "Egress port");
    mesa_qos_port_conf_t conf;

    EXAMPLE_BARRIER(argc);

    if (mesa_capability(NULL, MESA_CAP_QOS_EGRESS_QUEUE_CUT_THROUGH) == 0) {
        cli_printf("Cut-through not supported\n");
        return -1;
    }

    // Store state
    state.iport = iport;
    state.eport = eport;

    // Ingress port has tag classification is enabled
    RC(mesa_qos_port_conf_get(NULL, iport, &conf));
    state.conf = conf;
    conf.tag.class_enable = 1;
    RC(mesa_qos_port_conf_set(NULL, iport, &conf));

    // Egress port has cut-through enabled for priority 7
    RC(mesa_qos_port_conf_get(NULL, eport, &conf));
    conf.queue[7].cut_through_enable = 1;
    RC(mesa_qos_port_conf_set(NULL, eport, &conf));

    return 0;
}

static int ct_uninit(void)
{
    RC(mesa_qos_port_conf_set(NULL, state.iport, &state.conf));
    RC(mesa_qos_port_conf_set(NULL, state.eport, &state.conf));
    return 0;
}

static const char *ct_help(void)
{
    return "Cut-through example";
}

EXAMPLE(ct, ct_init, NULL, ct_uninit, ct_help);
