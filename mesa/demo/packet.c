// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"

static mscc_appl_trace_module_t trace_module = {
    .name = "packet"
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
    uint8_t     queue_valid;
    mesa_bool_t queue_list[MESA_PACKET_RX_QUEUE_CNT];
    uint32_t    len;
    uint32_t    cnt;
} packet_cli_req_t;

typedef struct {
    mesa_bool_t    poll;
    mesa_port_no_t iport[MESA_PACKET_RX_QUEUE_CNT];
} packet_conf_t;

static packet_conf_t packet_conf;

static void cli_cmd_packet_forward(cli_req_t *req)
{
    packet_cli_req_t *mreq = req->module_req;
    uint8_t          queue;
    mesa_port_no_t   *iport, uport;
    
    if (!req->set) {
        cli_printf("Queue  Port\n");
    }
    packet_conf.poll = 0;
    for (queue = 0; queue < MESA_PACKET_RX_QUEUE_CNT; queue++) {
        iport = &packet_conf.iport[queue];
        if (mreq->queue_valid && mreq->queue_list[queue] == 0) {
        } else if (req->set) {
            *iport = req->port_no;
        } else {
            uport = (*iport == MESA_PORT_NO_NONE ? 0 : iport2uport(*iport));
            cli_printf("%-7u%u%s\n", queue, uport, uport ? "" : " (Disabled)");
        }
        if (*iport != MESA_PORT_NO_NONE) {
            packet_conf.poll = 1;
        }
    }
}

static void cli_cmd_packet_tx(cli_req_t *req)
{
    mesa_port_no_t        uport, iport;
    mesa_bool_t           state;
    packet_cli_req_t      *mreq = req->module_req;
    uint32_t              len = (mreq->len ? mreq->len : 64);
    uint32_t              cnt = (mreq->cnt ? mreq->cnt : 1), i;
    uint8_t               frame[1600];
    mesa_packet_tx_info_t tx_info;

    memset(frame, 0xaa, sizeof(frame));
    memset(frame, 0xff, 6);
    memset(&frame[6], 0x00, 6);

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 ||
            mesa_port_state_get(NULL, iport, &state) != MESA_RC_OK ||
            state == 0 ||
            mesa_packet_tx_info_init(NULL, &tx_info) != MESA_RC_OK) {
            continue;
        }

        cli_printf("Sending %u frames of %u bytes on port %u\n", cnt, len, uport);
        tx_info.dst_port_mask = 1;
        tx_info.dst_port_mask <<= iport;
        tx_info.dst_port = iport;
        frame[11] = uport;
        for (i = 0; i < cnt; i++) {
            if (mesa_packet_tx_frame(NULL, &tx_info, frame, len - 4) != MESA_RC_OK) {
                cli_printf("tx_frame[%u] failed\n", i);
                break;
            }
        }
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Packet Forward [<queue_list>] [<port_no>]",
        "Set or show packet forwarding",
        cli_cmd_packet_forward
    },
    {
        "Packet Tx [<port_list>] [<length>] [<count>]",
        "Send broadcast frame to ports",
        cli_cmd_packet_tx
    },
};

static int cli_parm_queue_list(cli_req_t *req)
{
    packet_cli_req_t *mreq = req->module_req;
    int              error;

    error = cli_parse_list(req->cmd, mreq->queue_list, 0, MESA_PACKET_RX_QUEUE_CNT - 1, 1);
    if (!error) {
        mreq->queue_valid = 1;
    }
    return error;
}

static int cli_parm_length(cli_req_t *req)
{
    packet_cli_req_t *mreq = req->module_req;

    return cli_parm_u32(req, &mreq->len, 64, 1518);
}

static int cli_parm_count(cli_req_t *req)
{
    packet_cli_req_t *mreq = req->module_req;

    return cli_parm_u32(req, &mreq->cnt, 1, 1000);
}

static cli_parm_t cli_parm_table[] = {
    {
        "<queue_list>",
        "Queue list, default: All queues (0-7)",
        CLI_PARM_FLAG_NONE,
        cli_parm_queue_list
    },
    {
        "<length>",
        "Frame length including FCS (64 - 1518), default: 64 bytes",
        CLI_PARM_FLAG_NONE | CLI_PARM_FLAG_SET,
        cli_parm_length
    },
    {
        "<count>",
        "Frame count (1 - 1000), default: 1",
        CLI_PARM_FLAG_NONE,
        cli_parm_count
    },
};

static void packet_cli_init(void)
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

    for (i = 0; i < MESA_PACKET_RX_QUEUE_CNT; i++) {
        packet_conf.iport[i] = MESA_PORT_NO_NONE;
    }    
}

static void packet_poll(void)
{
    uint8_t               frame[1600];
    uint32_t              queue;
    mesa_packet_rx_info_t rx_info;
    mesa_packet_tx_info_t tx_info;
    mesa_port_no_t        iport = MESA_PORT_NO_NONE;

    if (!packet_conf.poll) {
        return;
    }

    /* Extract frame */
    if (mesa_packet_rx_frame(NULL, frame, sizeof(frame), &rx_info) != MESA_RC_OK) {
        return;
    }
    T_I("Rx frame on port %u, length: %u, vid: %u, qmask: 0x%02x",
        rx_info.port_no, rx_info.length, rx_info.tag.vid, rx_info.xtr_qu_mask);
    T_D_HEX(frame, rx_info.length);
    
    /* Check if forwarding is enabled for Rx queue */
    for (queue = 0; queue < MESA_PACKET_RX_QUEUE_CNT; queue++) {
        if (rx_info.xtr_qu_mask & (1 << queue)) {
            iport = packet_conf.iport[queue];
            break;
        }
    }
    if (iport == MESA_PORT_NO_NONE || mesa_packet_tx_info_init(NULL, &tx_info) != MESA_RC_OK) {
        return;
    }

    /* Inject frame to egress port */
    T_I("forward to port %u", iport);
    tx_info.dst_port_mask = 1;
    tx_info.dst_port_mask <<= iport;
    tx_info.dst_port = iport;
    if (mesa_packet_tx_frame(NULL, &tx_info, frame, rx_info.length) != MESA_RC_OK) {
    }
}

void mscc_appl_packet_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        packet_cli_init();
        break;

    case MSCC_INIT_CMD_POLL_FAST:
        packet_poll();
        break;

    default:
        break;
    }
}
