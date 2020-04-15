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
    mesa_port_no_t          iport;
    mesa_port_no_t          tport;
    mesa_port_no_t          rport;
    mesa_port_no_t          eport;
    mesa_port_list_t        port_list[3];
    mesa_qos_fp_port_conf_t conf;
} state;

static int fp_init(int argc, const char *argv[])
{
    mesa_port_no_t          iport = ARGV_INT("iport", "Ingress port");
    mesa_port_no_t          tport = ARGV_INT("tport", "Tx FP port (looped)");
    mesa_port_no_t          rport = ARGV_INT("rport", "Rx FP port (lopped)");
    mesa_port_no_t          eport = ARGV_INT("eport", "Egress port");
    mesa_port_list_t        port_list;
    mesa_qce_t              qce;
    mesa_qos_fp_port_conf_t conf;
    
    EXAMPLE_BARRIER(argc);

    if (mesa_capability(NULL, MESA_CAP_QOS_FRAME_PREEMPTION) == 0) {
        cli_printf("FP not supported\n");
        return -1;
    }

    // Store state
    state.iport = iport;
    state.tport = tport;
    state.rport = rport;
    state.eport = eport;

    // Include loop ports in default VLAN
    RC(mesa_vlan_port_members_get(NULL, 1, &port_list));
    state.port_list[0] = port_list;
    mesa_port_list_set(&port_list, tport, 1);
    mesa_port_list_set(&port_list, rport, 1);
    RC(mesa_vlan_port_members_set(NULL, 1, &port_list));

    // Include ingress port and Tx port in PVLAN 0
    RC(mesa_pvlan_port_members_get(NULL, 0, &state.port_list[1]));
    mesa_port_list_clear(&port_list);
    mesa_port_list_set(&port_list, iport, 1);    
    mesa_port_list_set(&port_list, tport, 1);    
    RC(mesa_pvlan_port_members_set(NULL, 0, &port_list));

    // Include Rx port and egress port PVLAN 1
    RC(mesa_pvlan_port_members_get(NULL, 1, &state.port_list[2]));
    mesa_port_list_clear(&port_list);
    mesa_port_list_set(&port_list, rport, 1);    
    mesa_port_list_set(&port_list, eport, 1);    
    RC(mesa_pvlan_port_members_set(NULL, 1, &port_list));

    // Map broadcasts to priority 7
    RC(mesa_qce_init(NULL, MESA_QCE_TYPE_ANY, &qce));
    qce.id = 1;
    mesa_port_list_set(&qce.key.port_list, iport, 1);
    qce.key.mac.dmac_bc = MESA_VCAP_BIT_1;
    qce.action.prio_enable = 1;
    qce.action.prio = 7;
    RC(mesa_qce_add(NULL, MESA_QCE_ID_LAST, &qce));

    // Enable Frame Preemption for priority 0 on Tx port
    RC(mesa_qos_fp_port_conf_get(NULL, tport, &conf));
    state.conf = conf;
    conf.admin_status[0] = 1;
    conf.enable_tx = 1;
    conf.verify_disable_tx = 0;
    RC(mesa_qos_fp_port_conf_set(NULL, tport, &conf));
    
    return 0;
}

static void fp_stat(const char *col1, const char *col2, uint64_t c1, uint64_t c2)
{
    char buf[80];
    
    sprintf(buf, "Rx %s:", col1);
    cli_printf("%-19s%19llu  ", buf, c1);
    if (col2 != NULL) {
        sprintf(buf, "Tx %s:", strlen(col2) ? col2 : col1);
        cli_printf("%-19s%19llu", buf, c2);
    }
    cli_printf("\n");
}

static void fp_port_stat(mesa_port_no_t port_no)
{
    mesa_port_counters_t c;

    if (mesa_port_counters_get(NULL, port_no, &c) != MESA_RC_OK) {
        return;
    }
    cli_printf("Port %u counters:\n", port_no);
    fp_stat("Packets", "", c.rmon.rx_etherStatsPkts, c.rmon.tx_etherStatsPkts);
    fp_stat("Octets", "", c.rmon.rx_etherStatsOctets, c.rmon.tx_etherStatsOctets);
    fp_stat("Unicast", "", c.if_group.ifInUcastPkts, c.if_group.ifOutUcastPkts);
    fp_stat("Multicast", "", c.rmon.rx_etherStatsMulticastPkts, c.rmon.tx_etherStatsMulticastPkts);
    fp_stat("Broadcast", "", c.rmon.rx_etherStatsBroadcastPkts, c.rmon.tx_etherStatsBroadcastPkts);
    fp_stat("AssError", NULL, c.dot3br.aMACMergeFrameAssErrorCount, 0);
    fp_stat("SmdError", NULL, c.dot3br.aMACMergeFrameSmdErrorCount, 0);
    fp_stat("AssOk", "HoldCount", c.dot3br.aMACMergeFrameAssOkCount, c.dot3br.aMACMergeHoldCount);
    fp_stat("FragCount", "", c.dot3br.aMACMergeFragCountRx, c.dot3br.aMACMergeFragCountTx);
    cli_printf("\n");
}

static int fp_run(int argc, const char *argv[])
{
    EXAMPLE_BARRIER(argc);

    fp_port_stat(state.iport);
    fp_port_stat(state.tport);
    fp_port_stat(state.rport);
    fp_port_stat(state.eport);
    
    return 0;
}

static int fp_uninit(void)
{
    RC(mesa_vlan_port_members_set(NULL, 1, &state.port_list[0]));
    RC(mesa_pvlan_port_members_set(NULL, 0, &state.port_list[1]));
    RC(mesa_pvlan_port_members_set(NULL, 1, &state.port_list[2]));
    RC(mesa_qce_del(NULL, 1));
    RC(mesa_qos_fp_port_conf_set(NULL, state.tport, &state.conf));

    return 0;
}

static const char *fp_help(void)
{
    return "Frame Preemption example";
}

EXAMPLE(fp, fp_init, fp_run, fp_uninit, fp_help);
