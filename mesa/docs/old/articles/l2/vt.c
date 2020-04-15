/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#include "mscc/ethernet/switch/api.h"

mesa_rc vt_port_config(const mesa_inst_t inst) {
    mesa_rc rc = MESA_RC_OK;
    // snippet_begin port
    mesa_vlan_trans_port2grp_conf_t port_conf = { 0 };

    // Change the default group assignment for port 3 from
    // translation group 3 to group 1.
    // Note that the port index is zero-based.
    port_conf.group_id = 1;
    port_conf.port_list[2] = 1;
    rc = mesa_vlan_trans_group_to_port_set(NULL, &port_conf);
    // snippet_end

    return rc;
}

mesa_rc vt_translation_config(const mesa_inst_t inst) {
    mesa_rc rc = MESA_RC_OK;

    // snippet_begin translation1
    mesa_vlan_trans_grp2vlan_conf_t group_conf = { 0 };

    // Add a translation entry to group 1 with the following
    // parameters: Bi-directional translation, "external" VID 10
    // and "internal" VID 20.
    group_conf.group_id = 1
    group_conf.dir = MESA_VLAN_TRANS_DIR_BOTH;
    group_conf.vid = 10;
    group_conf.trans_vid = 20;
    rc = mesa_vlan_trans_group_add(NULL, &group_conf);

    // snippet_endbegin translation2
    // Add a second translation entry to group 1 with the following
    // parameters: Egress translation, "external" VID 40
    // and "internal" VID 30.
    group_conf.group_id = 1
    group_conf.dir = MESA_VLAN_TRANS_DIR_EGRESS;
    group_conf.vid = 40;
    group_conf.trans_vid = 30;
    rc = mesa_vlan_trans_group_add(NULL, &group_conf);
    // snippet_end

    return rc;
}

mesa_rc vt_clean_up(const mesa_inst_t inst) {
    // TODO
    return MESA_RC_OK;
}

static seq[] = {
    STEP(vt_translation_config),
    STEP(vt_port_config),
    STEP(vt_clean_up),
};

REGISTER_EXAMPLE("VT-code-example", seq);
