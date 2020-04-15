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

static const char *aggr_help_txt = "\
This is a Link aggregation example configuration.\n\
\n\
Two ports are aggregated. Any other port can be used as ingress port.\n\
The aggregation mode is set to selected through parameter.\n\
";

static struct {
    mesa_aggr_mode_t   mode;
    uint32_t           aggr_no;
} state;

static int aggr_init(int argc, const char *argv[])
{
    mesa_port_no_t     port1 = ARGV_INT("port1", "Is the egress port 1 in the aggregation.");
    mesa_port_no_t     port2 = ARGV_INT("port2", "Is the egress port 2 in the aggregation.");
    uint32_t           aggr_mode = ARGV_OPT_INT("aggr-mode", "Is the selected aggregation mode. Default is 0\n   0 is SMAC\n 1 is DMAC\n   2 is SIP/DIP\n   3 is SPORT/DPORT", 0);
    uint32_t           aggr_no = ARGV_OPT_INT("aggr-no", "Is the selected aggregation number. Default is 1", 1);
    mesa_port_list_t   port_list;
    mesa_aggr_mode_t   mode;

    EXAMPLE_BARRIER(argc);

    memset(&state, 0, sizeof(state));
    state.aggr_no = aggr_no;

    // snippet_begin ex-aggr-enable
    mesa_port_list_clear(&port_list);
    mesa_port_list_set(&port_list, port1-1, TRUE);
    mesa_port_list_set(&port_list, port2-1, TRUE);
    RC(mesa_aggr_port_members_set(NULL, aggr_no, &port_list));

    // snippet_endbegin ex-aggr-mode-set
    RC(mesa_aggr_mode_get(NULL, &mode));
    state.mode = mode;
    switch (aggr_mode) {
    case 0: mode.smac_enable = TRUE; break;
    case 1: mode.dmac_enable = TRUE; break;
    case 2: mode.sip_dip_enable = TRUE; break;
    case 3: mode.sport_dport_enable = TRUE; break;
    }
    RC(mesa_aggr_mode_set(NULL, &mode));
    // snippet_end

    return 0;
}

static int aggr_clean()
{
    mesa_port_list_t   port_list;

    // Disable aggregation
    // snippet_begin ex-aggr-disable
    mesa_port_list_clear(&port_list);
    RC(mesa_aggr_port_members_set(NULL, state.aggr_no, &port_list));
    // snippet_end

    RC(mesa_aggr_mode_set(NULL, &state.mode));

    return 0;
}

static const char* aggr_help()
{
    return aggr_help_txt;
}

EXAMPLE(aggr, aggr_init, NULL, aggr_clean, aggr_help);
