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

#include <stdio.h>
#include "mscc/ethernet/switch/api.h"
#include "mscc/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"

static mscc_appl_trace_module_t trace_module = {
    .name = "vlan"
};

enum {
    TRACE_GROUP_DEFAULT,
    TRACE_GROUP_CNT
};

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

typedef struct {
    mesa_vlan_port_type_t port_type;
    mesa_vlan_frame_t     frame_type;
} vlan_cli_req_t;

static void cli_cmd_vlan_add(cli_req_t *req)
{
    mesa_port_no_t   iport;
    mesa_port_list_t member;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        mesa_port_list_set(&member, iport, req->port_list[iport2uport(iport)]);
    }
    (void)mesa_vlan_port_members_set(NULL, req->vid, &member);
}

static void cli_cmd_vlan_del(cli_req_t *req)
{
    mesa_port_list_t member;

    memset(&member, 0, sizeof(member));
    (void)mesa_vlan_port_members_set(NULL, req->vid, &member);
}

typedef enum {
    CLI_CMD_VLAN_TYPE,
    CLI_CMD_VLAN_PVID,
    CLI_CMD_VLAN_UVID,
    CLI_CMD_VLAN_FRAME,
    CLI_CMD_VLAN_FILTER,
} vlan_cli_cmd_t;

static void cli_cmd_vlan_port_conf(cli_req_t *req, vlan_cli_cmd_t cmd)
{
    mesa_port_no_t        iport, uport;
    mesa_vlan_port_conf_t conf;
    mesa_vid_t            vid;
    mesa_port_list_t      member;
    char                  buf[64];
    mesa_bool_t           skip, header = 1;
    vlan_cli_req_t        *mreq = req->module_req;

    /* Set/show port configuration */
    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 || mesa_vlan_port_conf_get(NULL, iport, &conf) != MESA_RC_OK)
            continue;

        if (req->set) {
            if (cmd == CLI_CMD_VLAN_TYPE) {
                conf.port_type = mreq->port_type;
            } else if (cmd == CLI_CMD_VLAN_PVID) {
                conf.pvid = req->vid;
            } else if (cmd == CLI_CMD_VLAN_UVID) {
                conf.untagged_vid = (req->vid == MESA_VID_DEFAULT ? conf.pvid : req->vid);
            } else if (cmd == CLI_CMD_VLAN_FRAME) {
                conf.frame_type = mreq->frame_type;
            } else if (cmd == CLI_CMD_VLAN_FILTER) {
                conf.ingress_filter = req->enable;
            }
            (void)mesa_vlan_port_conf_set(NULL, iport, &conf);
            continue;
        }

        if (header) {
            header = 0;
            cli_table_header("Port  Type      PVID  UVID  Frame     Filter");
        }
        cli_printf("%-6u%-10s%-6u%-6u%-10s%s\n",
                   uport,
                   conf.port_type == MESA_VLAN_PORT_TYPE_UNAWARE ? "Unaware" :
                   conf.port_type == MESA_VLAN_PORT_TYPE_C ? "C-port" :
                   conf.port_type == MESA_VLAN_PORT_TYPE_S ? "S-port" :
                   conf.port_type == MESA_VLAN_PORT_TYPE_S_CUSTOM ? "S-custom" : "?",
                   conf.pvid,
                   conf.untagged_vid,
                   conf.frame_type == MESA_VLAN_FRAME_ALL ? "All" :
                   conf.frame_type == MESA_VLAN_FRAME_TAGGED ? "Tagged" :
                   conf.frame_type == MESA_VLAN_FRAME_UNTAGGED ? "Untagged" : "?",
                   cli_bool_txt(conf.ingress_filter));
    }

    /* Show VLAN table */
    header = 1;
    for (vid = MESA_VID_DEFAULT; !req->set && vid < MESA_VIDS; vid++) {
        if (mesa_vlan_port_members_get(NULL, vid, &member) != MESA_RC_OK)
            continue;

        skip = 1;
        for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
            if (cli_port_list_member(&member, iport)) {
                skip = 0;
                break;
            }
        }
        if (skip)
            continue;

        if (header) {
            header = 0;
            cli_printf("\n");
            cli_table_header("VID   Ports");
        }
        cli_printf("%-6u%s\n", vid, cli_port_list_txt(&member, buf));
    }
}

static void cli_cmd_vlan_port_type(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_TYPE);
}

static void cli_cmd_vlan_port_pvid(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_PVID);
}

static void cli_cmd_vlan_port_uvid(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_UVID);
}

static void cli_cmd_vlan_port_frame(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_FRAME);
}

static void cli_cmd_vlan_port_filter(cli_req_t *req)
{
    cli_cmd_vlan_port_conf(req, CLI_CMD_VLAN_FILTER);
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "VLAN Add <vid> <port_list>",
        "Add VLAN",
        cli_cmd_vlan_add
    },
    {
        "VLAN Delete <vid>",
        "Delete VLAN",
        cli_cmd_vlan_del
    },
    {
        "VLAN Type [<port_list>] [unaware|c-port|s-port]",
        "Set or show VLAN port type",
        cli_cmd_vlan_port_type
    },
    {
        "VLAN PVID [<port_list>] [<vid>]",
        "Set or show port VLAN ID",
        cli_cmd_vlan_port_pvid
    },
    {
        "VLAN UVID [<port_list>] [all|none|pvid]",
        "Set or show Tx untagged VID",
        cli_cmd_vlan_port_uvid
    },
    {
        "VLAN Frame [<port_list>] [all|tagged|untagged]",
        "Set or show accepted frame type",
        cli_cmd_vlan_port_frame
    },
    {
        "VLAN Filter [<port_list>] [enable|disable]",
        "Set or show VLAN ingress filtering",
        cli_cmd_vlan_port_filter
    },
};

static int cli_parm_keyword(cli_req_t *req)
{
    const char     *found;
    vlan_cli_req_t *mreq = req->module_req;
    
    if ((found = cli_parse_find(req->cmd, req->stx)) == NULL)
        return 1;
   
    if (!strncmp(found, "all", 3)) {
        req->vid = MESA_VID_ALL;
        mreq->frame_type = MESA_VLAN_FRAME_ALL;
    } else if (!strncmp(found, "c-port", 6))
        mreq->port_type = MESA_VLAN_PORT_TYPE_C;
    else if (!strncmp(found, "none", 4))
        req->vid = MESA_VID_NULL;
    else if (!strncmp(found, "pvid", 4))
        req->vid = MESA_VID_DEFAULT;
    else if (!strncmp(found, "s-port", 6))
        mreq->port_type = MESA_VLAN_PORT_TYPE_S;
    else if (!strncmp(found, "tagged", 6))
        mreq->frame_type = MESA_VLAN_FRAME_TAGGED;
    else if (!strncmp(found, "untagged", 8))
        mreq->frame_type = MESA_VLAN_FRAME_UNTAGGED;
    else if (!strncmp(found, "unaware", 7))
        mreq->port_type = MESA_VLAN_PORT_TYPE_UNAWARE;
    else
        cli_printf("no match: %s\n", found);
    
    return 0;
}

static cli_parm_t cli_parm_table[] = {
    {
        "unaware|c-port|s-port",
        "VLAN port type, default: Show type",
        CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "all|none|pvid",
        "VLAN egress tagging, default: Show mode",
        CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "all|tagged|untagged",
        "VLAN accepted frames, default: Show mode",
        CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
};

static void vlan_cli_init(void)
{
    int i;

    /* Register commands */
    for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }

    /* Register parameters */
    for (i = 0; i < sizeof(cli_parm_table)/sizeof(cli_parm_t); i++) {
        mscc_appl_cli_parm_reg(&cli_parm_table[i]);
    }
}

void mscc_appl_vlan_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        vlan_cli_init();
        break;

    default:
        break;
    }
}
