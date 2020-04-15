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
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include <linux/if_link.h>
#include <linux/if_addr.h>
#include <linux/if_arp.h>
#include <linux/ip.h>

#include "mscc/ethernet/switch/api.h"
#include "mscc/ethernet/board/api.h"
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
    char buf[1024];
    int chip_port = chip_port_get(ip_port);
    uint8_t mac_addr[] = { 0x02, 0x01, 0xc1, 0x00, 0x00, 0x00 };
    uint seed;
    int  fd, x, if_logical_num, res;
    const char *dev = "/dev/urandom";

    if (chip_port < 0) {
        return MESA_RC_ERROR;
    }

    // Generate random value for the 24 LSB of MAC address
    if ((fd = open(dev, O_RDONLY)) < 0) {
        T_E("open(%s) failed: %s", dev, strerror(errno));
        return MESA_RC_ERROR;
    }
    // Read and set new seed
    res = (read(fd, (void *)&seed, sizeof(seed)) == sizeof(seed));
    close(fd);
    if (res == 0) {
        T_E("read(%s) failed: %s", dev, strerror(errno));
        return MESA_RC_ERROR;
    }
    srand(seed);
    x = rand();
    mac_addr[3] = (x >> 16);
    mac_addr[4] = (x >> 8);
    mac_addr[5] = (x >> 0);

    // Create the interface using chip number as this is used by the mux river
    snprintf(buf, 1024, "ip link add vtss.port.%d address %02x:%02x:%02x:%02x:%02x:%02x type vtss_if_mux",
             chip_port, mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3],
             mac_addr[4], mac_addr[5]);
    if_logical_num = chip_port;
    res = system(buf);
    if (res != 0) {
        fprintf(stderr, "Failed (%d): %s\n", res, buf);
        return MESA_RC_ERROR;
    }

    // Now, rename it, as the user expect to see front ports
    snprintf(buf, 1024, "ip link set vtss.port.%d name vtss.port.%d",
             chip_port, ip_port + 1);
    res = system(buf);
    if (res != 0) {
        goto ERR;
    }
    if_logical_num = ip_port + 1;

    snprintf(buf, 1024, "ip link set vtss.ifh up");
    res = system(buf);
    if (res != 0) {
        goto ERR;
    }

    snprintf(buf, 1024, "ip link set vtss.port.%d up", if_logical_num);
    res = system(buf);
    if (res != 0) {
        goto ERR;
    }

    return MESA_RC_OK;

ERR:
    fprintf(stderr, "Failed (%d): %s\n", res, buf);
    snprintf(buf, 1024, "ip link del vtss.port.%d", if_logical_num);
    res = system(buf);
    if (res != 0) {
        fprintf(stderr, "Failed (%d): %s\n", res, buf);
    }
    return MESA_RC_ERROR;
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
