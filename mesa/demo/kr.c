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
    .name = "kr"
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

meba_inst_t meba_global_inst;
/* ================================================================= *
 *  CLI
 * ================================================================= */
typedef struct {
    mesa_port_speed_t speed;
    mesa_bool_t auto_keyword;

} kr_cli_req_t;

typedef enum {
    CLI_CMD_PORT_KR,
} kr_cli_cmd_t;

typedef struct {
    mesa_bool_t all;
    mesa_bool_t fec;
    mesa_bool_t adv10g;
    mesa_bool_t adv5g;
    mesa_bool_t adv2g5;
    mesa_bool_t adv1g;
} port_cli_req_t;


static int cli_parm_keyword(cli_req_t *req)
{
    const char     *found;
    port_cli_req_t *mreq = req->module_req;

    if ((found = cli_parse_find(req->cmd, req->stx)) == NULL)
        return 1;

    if (!strncasecmp(found, "adv-1g", 6)) {
        mreq->adv1g = 1;
    } else if (!strncasecmp(found, "adv-2g5", 7)) {
        mreq->adv2g5 = 1;
    } else if (!strncasecmp(found, "adv-5g", 6)) {
        mreq->adv5g = 1;
    } else if (!strncasecmp(found, "adv-10g", 7)) {
        mreq->adv10g = 1;
    } else if (!strncasecmp(found, "fec", 7)) {
        mreq->fec = 1;
    } else if (!strncasecmp(found, "all", 3)) {
        mreq->all = 1;
    } else
        cli_printf("no match: %s\n", found);

    return 0;
}

uint32_t my_cnt = 0;

static void cli_cmd_port_kr(cli_req_t *req)
{
    mesa_port_no_t        uport, iport;
    mesa_port_10g_kr_conf_t conf;
    port_cli_req_t        *mreq = req->module_req;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }
        if (mesa_port_10g_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK) {
            continue;
        }

        if (req->set) {
            conf.aneg.enable = 1;
            conf.aneg.adv_1g = mreq->adv1g || mreq->all;
            conf.aneg.adv_2g5 = mreq->adv2g5 || mreq->all;
            conf.aneg.adv_5g = mreq->adv5g || mreq->all;
            conf.aneg.adv_10g = mreq->adv10g || mreq->all;
            conf.aneg.fec_abil = mreq->fec || mreq->all;
            conf.aneg.fec_req = mreq->fec || mreq->all;

            if (mesa_port_10g_kr_conf_set(NULL, iport, &conf) != MESA_RC_OK) {
                cli_printf("KR set failed for port %u\n", uport);
            }
            my_cnt = 0;
        }
    }
}


static void cli_cmd_port_kr_status(cli_req_t *req)
{
    mesa_port_no_t        uport, iport;
    mesa_port_10g_kr_status_t status;
    mesa_port_10g_kr_conf_t conf;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }

        if (mesa_port_10g_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK) {
            continue;
        }

        if (mesa_port_10g_kr_status_get(NULL, iport, &status) != MESA_RC_OK) {
            return;
        }

        if (conf.aneg.enable) {
            cli_printf("LP aneg ability                 :%s\n", status.aneg.lp_aneg_able ? "Yes" : "No");
            cli_printf("Aneg active (running)           :%s\n", status.aneg.active ? "Yes" : "No");
            cli_printf("PCS block lock                  :%s\n", status.aneg.block_lock ? "Yes" : "No");
            cli_printf("Aneg complete                   :%s\n", status.aneg.complete ? "Yes" : "No");
            cli_printf("  Enable 10G request            :%s\n", status.aneg.request_10g ? "Yes" : "No");
            cli_printf("  Enable 1G request             :%s\n", status.aneg.request_1g ? "Yes" : "No");
            cli_printf("  FEC change request            :%s\n", status.aneg.request_fec_change ? "Yes" : "No");
        } else {
            cli_printf("Aneg                            :Disabled\n");
        }
    }
}

static void print_reg_bit(uint32_t  bt, char *name)
{
    if (bt > 0) {
        printf("%s ",name);
    }
}
static char *fa_kr_aneg_rate(uint32_t reg)
{
    switch (reg) {
    case 0:  return "No Change";
    case 7:  return "25G-KR";
    case 8:  return "25G-KR-S";
    case 9:  return "10G-KR";
    case 10: return "10G-KX4";
    case 11: return "5G-KR";
    case 12: return "2.5G-KX";
    case 13: return "1G-KX";
    default: return "other";
    }
    return "other";
}
#define VTSS_BIT(x) (1 << (x))

void print_irq_vector(uint32_t p, uint32_t vector)
{
    if (vector == 0) {
        return;
    }
    if (my_cnt > 100) {
        return;
    }
    my_cnt++;
    printf("Port:%d IRQ: ",p+1);
    print_reg_bit((VTSS_BIT(29) & vector),  "KR_ACTV");
    print_reg_bit((VTSS_BIT(28) & vector),  "LPSVALID");
    print_reg_bit((VTSS_BIT(27) & vector),  "LPCVALID");
    print_reg_bit((VTSS_BIT(26) & vector),  "WT_DONE");
    print_reg_bit((VTSS_BIT(25) & vector),  "MW_DONE");
    print_reg_bit((VTSS_BIT(24) & vector),  "BER_BUSY_0");
    print_reg_bit((VTSS_BIT(23) & vector),  "BER_BUSY_1");
    print_reg_bit((VTSS_BIT(22) & vector),  "REM_RDY_0");
    print_reg_bit((VTSS_BIT(21) & vector),  "REM_RDY_1");
    print_reg_bit((VTSS_BIT(20) & vector),  "FRLOCK_0");
    print_reg_bit((VTSS_BIT(19) & vector),  "FRLOCK_1");
    print_reg_bit((VTSS_BIT(18) & vector),  "DME_VIOL_0");
    print_reg_bit((VTSS_BIT(17) & vector),  "DME_VIOL_1");
    print_reg_bit((VTSS_BIT(16) & vector),  "AN_XMIT_DISABLE");
    print_reg_bit((VTSS_BIT(15) & vector),  "TRAIN");
    print_reg_bit((VTSS_BIT(14) & vector),  "RATE_DET");
    print_reg_bit((VTSS_BIT(13) & vector),  "CMPL_ACK");
    print_reg_bit((VTSS_BIT(12) & vector),  "AN_GOOD");
    print_reg_bit((VTSS_BIT(11) & vector),  "LINK_FAIL");
    print_reg_bit((VTSS_BIT(10) & vector),  "ABD_FAIL");
    print_reg_bit((VTSS_BIT(9)  & vector),  "ACK_FAIL");
    print_reg_bit((VTSS_BIT(8)  & vector),  "NP_FAIL");
    print_reg_bit((VTSS_BIT(7)  & vector),  "NP_RX");
    print_reg_bit((VTSS_BIT(6)  & vector),  "INCP_LINK");
    print_reg_bit((VTSS_BIT(5)  & vector),  "GEN0_DONE");
    print_reg_bit((VTSS_BIT(4)  & vector),  "GEN1_DONE");

    if ((0xf & vector) > 0) {
        printf("%s ",fa_kr_aneg_rate((0xf & vector)));
    }
    printf("\n");
}

void kr_poll(meba_inst_t inst)
{
    mesa_port_no_t        iport;
    mesa_port_10g_kr_status_t status;
    mesa_port_10g_kr_conf_t conf;
    mesa_port_10g_kr_fw_msg_t fw_msg = {0};
    mesa_port_conf_t        pconf;
    uint16_t meba_cnt = MEBA_WRAP(meba_capability, inst, MEBA_CAP_BOARD_PORT_COUNT);

    for (iport = 0; iport < meba_cnt; iport++) {
        if (mesa_port_10g_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK ||
            !conf.aneg.enable) {
            continue;
        }

        if (mesa_port_10g_kr_status_get(NULL, iport, &status) != MESA_RC_OK) {
            return;
        }

        (void)print_irq_vector(iport, status.irq.vector);

        (void) mesa_port_conf_get(NULL, iport, &pconf);

        if (status.aneg.request_10g) {
            pconf.if_type = MESA_PORT_INTERFACE_SFI;
            pconf.speed = MESA_SPEED_10G;
        } else if (status.aneg.request_5g) {
            pconf.if_type = MESA_PORT_INTERFACE_SFI;
            pconf.speed = MESA_SPEED_5G;
        } else if (status.aneg.request_2g5) {
            pconf.if_type = MESA_PORT_INTERFACE_SERDES;
            pconf.speed = MESA_SPEED_2500M;
        } else if (status.aneg.request_1g) {
            pconf.if_type = MESA_PORT_INTERFACE_SERDES;
            pconf.speed = MESA_SPEED_1G;
        } else {
            continue;
        }
        (void)mesa_port_conf_set(NULL, iport, &pconf);
        fw_msg.rate_done = 1;
        if (mesa_port_10g_kr_fw_msg_set(NULL, iport, &fw_msg) != MESA_RC_OK) {
            return;
        }

    }
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Port KR aneg [<port_list>] [all] [adv-1g] [adv-2g5] [adv-5g] [adv-10g] [fec]",
        "Set or show kr",
        cli_cmd_port_kr
    },
    {
        "Port KR status [<port_list>]",
        "Show status",
        cli_cmd_port_kr_status
    },
};


static cli_parm_t cli_parm_table[] = {
    {
        "kr",
        "kr help",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "all",
        "advertise all",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "adv-1g",
        "advertise speed",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "adv-2g5",
        "advertise speed",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "adv-5g",
        "advertise speed",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "adv-10g",
        "advertise speed",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "fec",
        "advertise fec",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "all",
        "advertise all",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },


};

static void kr_cli_init(void)
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





/* ================================================================= *
 *  Initialization
 * ================================================================= */

static void kr_init(meba_inst_t inst)
{
    uint32_t              port_cnt = mesa_capability(NULL, MESA_CAP_PORT_CNT);
    mesa_port_no_t        port_no;

    /* Store the meba inst globally */
    meba_global_inst = inst;

    for (port_no = 0; port_no < port_cnt; port_no++) {
    }

}


void mscc_appl_kr_init(mscc_appl_init_t *init)
{

    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        kr_init(init->board_inst);
        kr_cli_init();
        break;

    case MSCC_INIT_CMD_INIT_WARM:
        kr_init(init->board_inst);
        break;

    case MSCC_INIT_CMD_POLL:
        kr_poll(init->board_inst);

        break;

    default:
        break;
    }
}
