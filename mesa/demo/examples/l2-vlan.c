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
    mesa_port_no_t        uport;
    mesa_port_no_t        aport;
    mesa_port_no_t        tport;
    mesa_port_no_t        hport;
    mesa_port_list_t      port_list;
    mesa_vlan_port_conf_t conf;
} vlan_state;

static int vlan_init(int argc, const char *argv[])
{
    mesa_port_no_t        uport = ARGV_INT("uport", "Unaware port, VID 10");
    mesa_port_no_t        aport = ARGV_INT("aport", "Access port, VID 20");
    mesa_port_no_t        tport = ARGV_INT("tport", "Trunk port, VID 10 and 20");
    mesa_port_no_t        hport = ARGV_INT("hport", "Hybrid port, VID 10 (untagged) and VID 20");
    mesa_vlan_port_conf_t conf;
    mesa_port_list_t      port_list;

    EXAMPLE_BARRIER(argc);

    // Store state
    RC(mesa_vlan_port_conf_get(NULL, uport, &vlan_state.conf));
    vlan_state.uport = uport;
    vlan_state.aport = aport;
    vlan_state.tport = tport;
    vlan_state.hport = hport;
    RC(mesa_vlan_port_members_get(NULL, 1, &vlan_state.port_list));

    // Unaware port, VID 10
    RC(mesa_vlan_port_conf_get(NULL, uport, &conf));
    conf.port_type = MESA_VLAN_PORT_TYPE_UNAWARE;
    conf.pvid = 10;
    conf.untagged_vid = 10;
    conf.frame_type = MESA_VLAN_FRAME_ALL;
    RC(mesa_vlan_port_conf_set(NULL, uport, &conf));

    // Access port, VID 20
    RC(mesa_vlan_port_conf_get(NULL, aport, &conf));
    conf.port_type = MESA_VLAN_PORT_TYPE_C;
    conf.pvid = 20;
    conf.untagged_vid = 20;
    conf.frame_type = MESA_VLAN_FRAME_UNTAGGED;
    RC(mesa_vlan_port_conf_set(NULL, aport, &conf));

    // Trunk port, tag all frames
    RC(mesa_vlan_port_conf_get(NULL, tport, &conf));
    conf.port_type = MESA_VLAN_PORT_TYPE_C;
    conf.pvid = 1;
    conf.untagged_vid = MESA_VID_NULL;
    conf.frame_type = MESA_VLAN_FRAME_TAGGED;
    RC(mesa_vlan_port_conf_set(NULL, tport, &conf));

    // Hybrid port, untag VID 10, tag VID 20
    RC(mesa_vlan_port_conf_get(NULL, hport, &conf));
    conf.port_type = MESA_VLAN_PORT_TYPE_C;
    conf.pvid = 10;
    conf.untagged_vid = 10;
    conf.frame_type = MESA_VLAN_FRAME_ALL;
    RC(mesa_vlan_port_conf_set(NULL, hport, &conf));

    // Remove ports from default VLAN
    mesa_port_list_clear(&port_list);
    RC(mesa_vlan_port_members_set(NULL, 1, &port_list));

    // Add ports to VLAN 10
    RC(mesa_vlan_port_members_get(NULL, 10, &port_list));
    mesa_port_list_set(&port_list, uport, 1);
    mesa_port_list_set(&port_list, tport, 1);
    mesa_port_list_set(&port_list, hport, 1);
    RC(mesa_vlan_port_members_set(NULL, 10, &port_list));

    // Add ports to VLAN 20
    RC(mesa_vlan_port_members_get(NULL, 20, &port_list));
    mesa_port_list_set(&port_list, aport, 1);
    mesa_port_list_set(&port_list, tport, 1);
    mesa_port_list_set(&port_list, hport, 1);
    RC(mesa_vlan_port_members_set(NULL, 20, &port_list));

    return 0;
}

static int vlan_uninit(void)
{
    RC(mesa_vlan_port_conf_set(NULL, vlan_state.uport, &vlan_state.conf));
    RC(mesa_vlan_port_conf_set(NULL, vlan_state.aport, &vlan_state.conf));
    RC(mesa_vlan_port_conf_set(NULL, vlan_state.tport, &vlan_state.conf));
    RC(mesa_vlan_port_conf_set(NULL, vlan_state.hport, &vlan_state.conf));
    RC(mesa_vlan_port_members_set(NULL, 1, &vlan_state.port_list));
    mesa_port_list_clear(&vlan_state.port_list);
    RC(mesa_vlan_port_members_set(NULL, 10, &vlan_state.port_list));
    RC(mesa_vlan_port_members_set(NULL, 20, &vlan_state.port_list));

    return 0;
}

static const char *vlan_help(void)
{
    return "Basic VLAN example";
}

EXAMPLE(vlan, vlan_init, NULL, vlan_uninit, vlan_help);
