// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <arpa/inet.h>

#include <linux/if_link.h>
#include <linux/if_addr.h>
#include <linux/if_arp.h>
#include <linux/ip.h>

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"

static mscc_appl_trace_module_t trace_module = {
    .name = "ip"
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

mesa_port_no_t ip_port = MESA_PORT_NO_NONE;

#define SYS_CMD(cmd) { if (system(cmd) != 0) return MESA_RC_ERROR; }

static mesa_rc ip_interface_setup(char *create_name, char *name, int add)
{
    char buf[1024];
    uint8_t mac[6];

    if (add) {
        // Get system MAC address
        get_mac_addr(mac);

        // Create interface
        snprintf(buf, sizeof(buf), "ip link add %s address %02x:%02x:%02x:%02x:%02x:%02x type vtss_if_mux",
                 create_name, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        SYS_CMD(buf);

        // Rename interface and set it up
        snprintf(buf, sizeof(buf), "ip link set %s name %s up", create_name, name);
        SYS_CMD(buf);

        // Set carrier up
        snprintf(buf, sizeof(buf), "echo 1 > /sys/class/net/%s/carrier", create_name);
        SYS_CMD(buf);

        // Set IFH interface up
        SYS_CMD("ip link set vtss.ifh up");
    } else {
        snprintf(buf, sizeof(buf), "ip link del %s", name);
        SYS_CMD(buf);
    }
    return MESA_RC_OK;
}

static mesa_bool_t ip_vid_enabled[MESA_VIDS];

void ip_mac_setup(mesa_vid_t vid, mesa_bool_t add)
{
    uint8_t                i, mac[6];
    mesa_mac_table_entry_t uc, bc;
    mesa_port_no_t         iport;

    // Setup unicast/broadcast MAC address entries
    get_mac_addr(mac);
    memset(&uc, 0, sizeof(uc));
    uc.locked = 1;
    uc.copy_to_cpu = 1;
    uc.vid_mac.vid = vid;
    bc = uc;
    for (i = 0; i < 6; i++) {
        uc.vid_mac.mac.addr[i] = mac[i];
        bc.vid_mac.mac.addr[i] = 0xff;
    }
    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        mesa_port_list_set(&bc.destination, iport, 1);
    }

    if (add) {
        if (mesa_mac_table_add(NULL, &uc) != MESA_RC_OK ||
            mesa_mac_table_add(NULL, &bc) != MESA_RC_OK) {
            cli_printf("MAC address add failed\n");
        }
    } else {
        if (mesa_mac_table_del(NULL, &uc.vid_mac) != MESA_RC_OK ||
            mesa_mac_table_del(NULL, &bc.vid_mac) != MESA_RC_OK) {
            cli_printf("MAC address delete failed\n");
        }
    }
}

static void cli_cmd_ip_setup(cli_req_t *req, mesa_bool_t add)
{
    char                   name[16];

    if (ip_vid_enabled[req->vid] == add) {
        cli_printf("IP is already %s on VID %u\n", add ? "enabled" : "disabled", req->vid);
        return;
    }

    // Setup IP interface
    sprintf(name, "vtss.vlan.%u", req->vid);
    if (ip_interface_setup(name, name, add) != MESA_RC_OK) {
        return;
    }
    ip_vid_enabled[req->vid] = add;

    ip_mac_setup(req->vid, add);
}

static void cli_cmd_ip_add(cli_req_t *req)
{
    cli_cmd_ip_setup(req, 1);
}

static void cli_cmd_ip_del(cli_req_t *req)
{
    cli_cmd_ip_setup(req, 0);
}

static void cli_cmd_ip_status(cli_req_t *req)
{
    cli_printf("IP port: ");
    if (ip_port == MESA_PORT_NO_NONE) {
        cli_printf("Disabled");
    } else {
        cli_printf("%u", iport2uport(ip_port));
    }
    cli_printf("\n");
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Interface IP Add <vid>",
        "Add IP interface",
        cli_cmd_ip_add
    },
    {
        "Interface IP Delete <vid>",
        "Delete IP interface",
        cli_cmd_ip_del
    },
    {
        "IP Status",
        "Show IP management status",
        cli_cmd_ip_status
    },
};

static void ip_cli_init(void)
{
    int i;

    /* Register commands */
    for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }
}

static mesa_rc ip_option(char *parm)
{
    uint32_t uport;
    char     *end;

    uport = strtoul(parm, &end, 0);
    if (*end != '\0' || uport == 0 || uport > mesa_port_cnt(NULL)) {
        fprintf(stderr, "Illegal management port\n");
        return MESA_RC_ERROR;
    }
    ip_port = uport2iport(uport);

    T_D("using IP management port %u (iport %u)", uport, ip_port);

    return MESA_RC_OK;
}

static mscc_appl_opt_t ip_opt = {
    "p:",
    "<port>",
    "Enable IP management port" ,
    ip_option
};

static int32_t chip_port_get(int32_t user_port) {
    mesa_port_map_t *port_map;
    int32_t port_cnt = mesa_port_cnt(NULL);
    int32_t res = -1;
    mesa_rc rc;

    port_map = calloc(port_cnt, sizeof(*port_map));
    if (!port_map) {
        return -1;
    }

    rc = mesa_port_map_get(NULL, port_cnt, port_map);
    if (rc != MESA_RC_OK) {
        goto OUT;
    }

    res = port_map[ip_port].chip_port;

OUT:
    free(port_map);
    return res;
}

static mesa_rc ip_create_interface(void)
{
    char create_name[32], name[32];
    int chip_port = chip_port_get(ip_port);

    if (chip_port < 0) {
        return MESA_RC_ERROR;
    }

    // Port interface is created using chip port number as this is used by the mux driver
    sprintf(create_name, "vtss.port.%d", chip_port);

    // Port interface is then renamed based on CLI port number
    sprintf(name, "vtss.port.%d", ip_port + 1);

    return ip_interface_setup(create_name, name, 1);
}

#define MESA_RC(expr) { mesa_rc _rc = (expr); if (_rc != MESA_RC_OK) { fprintf(stderr, "%s failed\n", #expr); return _rc; } }

static mesa_rc ip_init(mesa_bool_t warm)
{
    mesa_vid_t           vid;
    mesa_port_list_t     port_list;
    mesa_acl_port_conf_t conf;
    mesa_learn_mode_t    mode;

    if (ip_port == MESA_PORT_NO_NONE) {
        return MESA_RC_OK;
    }
    
    // Exclude management port from default VLAN
    vid = MESA_VID_DEFAULT;
    MESA_RC(mesa_vlan_port_members_get(NULL, vid, &port_list));
    mesa_port_list_set(&port_list, ip_port, 0);
    MESA_RC(mesa_vlan_port_members_set(NULL, vid, &port_list));

    // Redirect all frames from management port to the CPU using ACL default action
    MESA_RC(mesa_acl_port_conf_get(NULL, ip_port, &conf));
    conf.action.cpu = 1;
    conf.action.port_action = MESA_ACL_PORT_ACTION_FILTER;
    MESA_RC(mesa_acl_port_conf_set(NULL, ip_port, &conf));

    // Disable learning on management port
    MESA_RC(mesa_learn_port_mode_get(NULL, ip_port, &mode));
    mode.automatic = 0;
    MESA_RC(mesa_learn_port_mode_set(NULL, ip_port, &mode));

    return (warm ? MESA_RC_OK : ip_create_interface());
}

void mscc_appl_ip_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        mscc_appl_opt_reg(&ip_opt);
        break;

    case MSCC_INIT_CMD_INIT:
        if (ip_init(0) == MESA_RC_OK) {
            ip_cli_init();
        }
        break;

    case MSCC_INIT_CMD_INIT_WARM:
        ip_init(1);
        break;

    default:
        break;
    }
}
