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

#define KR_ACTV            (29)
#define KR_LPSVALID        (28)
#define KR_LPCVALID        (27)
#define KR_WT_DONE         (26)
#define KR_MW_DONE         (25)
#define KR_BER_BUSY_0      (24)
#define KR_BER_BUSY_1      (23)
#define KR_REM_RDY_0       (22)
#define KR_REM_RDY_1       (21)
#define KR_FRLOCK_0        (20)
#define KR_FRLOCK_1        (19)
#define KR_DME_VIOL_0      (18)
#define KR_DME_VIOL_1      (17)
#define KR_AN_XMIT_DISABLE (16)
#define KR_TRAIN           (15)
#define KR_RATE_DET        (14)
#define KR_CMPL_ACK        (13)
#define KR_AN_GOOD         (12)
#define KR_LINK_FAIL       (11)
#define KR_ABD_FAIL        (10)
#define KR_ACK_FAIL        (9)
#define KR_NP_FAIL         (8)
#define KR_NP_RX           (7)
#define KR_INCP_LINK       (6)
#define KR_GEN0_DONE       (5)
#define KR_GEN1_DONE       (4)

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


typedef enum {
    INITILIZE,
    SEND_TRAINING,
    TRAIN_LOCAL,
    TRAIN_REMOTE,
    SEND_DATA,
    TAINING_FAILURE
} train_state_t;

typedef enum {
    GO_TO_MIN,
    CALCULATE_BER,
    MOVE_TO_MID_MARK,
    LOCAL_RX_TRAINED
} ber_state_t;

typedef struct {
    train_state_t current_state;
    ber_state_t ber_state;
    mesa_bool_t training;
    mesa_port_speed_t next_parallel_spd;
} kr_train_t;

typedef enum {
    INIT,
    INCR,
    DECR,
    HOLD
} kr_ld_coefficient_t;

typedef enum {
    MAX,
    MIN,
    UPDATED,
} kr_lp_coefficient_t;


kr_train_t kr_tr_state[100];

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
    mesa_bool_t train;
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
    } else if (!strncasecmp(found, "train", 5)) {
        mreq->train = 1;
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
            conf.train.enable = mreq->train;
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

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }
    }
}

static void bit2txt(uint32_t  bt, char *name)
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
#define BT(x) (1 << (x))

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
    bit2txt((BT(KR_ACTV)       & vector),  "KR_ACTV");
    bit2txt((BT(KR_LPSVALID)   & vector),  "LPSVALID");
    bit2txt((BT(KR_LPCVALID)   & vector),  "LPCVALID");
    bit2txt((BT(KR_WT_DONE)    & vector),  "WT_DONE");
    bit2txt((BT(KR_MW_DONE)    & vector),  "MW_DONE");
    bit2txt((BT(KR_BER_BUSY_0) & vector),  "BER_BUSY_0");
    bit2txt((BT(KR_BER_BUSY_1) & vector),  "BER_BUSY_1");
    bit2txt((BT(KR_REM_RDY_0)  & vector),  "REM_RDY_0");
    bit2txt((BT(KR_REM_RDY_1)  & vector),  "REM_RDY_1");
    bit2txt((BT(KR_FRLOCK_0)   & vector),  "FRLOCK_0");
    bit2txt((BT(KR_FRLOCK_1)   & vector),  "FRLOCK_1");
    bit2txt((BT(KR_DME_VIOL_0) & vector),  "DME_VIOL_0");
    bit2txt((BT(KR_DME_VIOL_1) & vector),  "DME_VIOL_1");
    bit2txt((BT(KR_AN_XMIT_DISABLE) & vector),  "AN_XMIT_DISABLE");
    bit2txt((BT(KR_TRAIN)      & vector),  "TRAIN");
    bit2txt((BT(KR_RATE_DET)   & vector),  "RATE_DET");
    bit2txt((BT(KR_CMPL_ACK)   & vector),  "CMPL_ACK");
    bit2txt((BT(KR_AN_GOOD)    & vector),  "AN_GOOD");
    bit2txt((BT(KR_LINK_FAIL)  & vector),  "LINK_FAIL");
    bit2txt((BT(KR_ABD_FAIL)   & vector),  "ABD_FAIL");
    bit2txt((BT(KR_ACK_FAIL)   & vector),  "ACK_FAIL");
    bit2txt((BT(KR_NP_FAIL)    & vector),  "NP_FAIL");
    bit2txt((BT(KR_NP_RX)      & vector),  "NP_RX");
    bit2txt((BT(KR_INCP_LINK)  & vector),  "INCP_LINK");
    bit2txt((BT(KR_GEN0_DONE)  & vector),  "GEN0_DONE");
    bit2txt((BT(KR_GEN1_DONE)  & vector),  "GEN1_DONE");

    if ((0xf & vector) > 0) {
        printf("%s ",fa_kr_aneg_rate((0xf & vector)));
    }
    printf("\n");
}

mesa_port_speed_t kr_parallel_spd(mesa_port_no_t iport, mesa_port_10g_kr_conf_t *conf)
{
    if (conf->aneg.adv_10g && (kr_tr_state[iport].next_parallel_spd == MESA_SPEED_10G)) {
        kr_tr_state[iport].next_parallel_spd = conf->aneg.adv_5g ? MESA_SPEED_5G : conf->aneg.adv_2g5 ? MESA_SPEED_2500M : MESA_SPEED_1G;
        return MESA_SPEED_10G;
    } else if (conf->aneg.adv_5g && (kr_tr_state[iport].next_parallel_spd == MESA_SPEED_5G)) {
        kr_tr_state[iport].next_parallel_spd = conf->aneg.adv_2g5 ? MESA_SPEED_2500M : MESA_SPEED_1G;
        return MESA_SPEED_5G;
    } else if (conf->aneg.adv_2g5 && (kr_tr_state[iport].next_parallel_spd == MESA_SPEED_2500M)) {
        kr_tr_state[iport].next_parallel_spd = MESA_SPEED_1G;
        return MESA_SPEED_2500M;
    } else  {
        kr_tr_state[iport].next_parallel_spd = MESA_SPEED_10G;;
        return MESA_SPEED_1G;
    }
}

uint16_t update_coef(kr_ld_coefficient_t ld)
{
    uint16_t coef = 0;

    switch (ld) {
    case INIT:
        coef = 1 << 12;
        break;
    case DECR:
        coef = 1 << 1;
        break;
    case INCR:
        coef = 1 << 0;
        break;
    case HOLD:
        coef = 0;
        break;
    default:
        printf("Dunno\n");
        break;
    }
    return coef;
}

#define KR_ANEG_RATE_25G 7
#define KR_ANEG_RATE_10G 9
#define KR_ANEG_RATE_5G 11
#define KR_ANEG_RATE_2G5 12
#define KR_ANEG_RATE_1G 13

mesa_port_speed_t kr_irq2spd(uint32_t irq)
{
    switch (irq) {
    case KR_ANEG_RATE_25G: return MESA_SPEED_25G;
    case KR_ANEG_RATE_10G: return MESA_SPEED_10G;
    case KR_ANEG_RATE_5G:  return MESA_SPEED_5G;
    case KR_ANEG_RATE_2G5: return MESA_SPEED_2500M;
    case KR_ANEG_RATE_1G:  return MESA_SPEED_1G;
    default:
        cli_printf("KR speed not supported\n");
    }
    return MESA_SPEED_10G;
}

void perform_lp_training(mesa_port_no_t p, uint32_t irq)
{
    mesa_port_10g_kr_frame_t frm;

    if (irq == KR_TRAIN) {
        frm.type = MESA_COEFFICIENT_UPDATE_FRM;
        frm.data = update_coef(INIT);
        (void)mesa_port_10g_kr_train_frame(NULL, p, &frm);
    }

}

void kr_poll(meba_inst_t inst)
{
    mesa_port_no_t        iport;
    mesa_port_10g_kr_status_t kr_sts;
    mesa_port_10g_kr_conf_t kr;
    mesa_port_conf_t        pconf;
    uint16_t meba_cnt = MEBA_WRAP(meba_capability, inst, MEBA_CAP_BOARD_PORT_COUNT);
    mesa_port_10g_kr_fw_req_t req_msg = {0};

    for (iport = 0; iport < meba_cnt; iport++) {
        if (mesa_port_10g_kr_conf_get(NULL, iport, &kr) != MESA_RC_OK ||
            !kr.aneg.enable) {
            continue;
        }

        if (mesa_port_10g_kr_status_get(NULL, iport, &kr_sts) != MESA_RC_OK || (kr_sts.irq.vector == 0)) {
            return;
        }

        (void)mesa_port_conf_get(NULL, iport, &pconf);

        (void)print_irq_vector(iport, kr_sts.irq.vector);

        if (kr_sts.irq.vector & BT(KR_TRAIN)) {
            kr_tr_state[iport].training = TRUE;
            req_msg.start_training = TRUE;
            (void)mesa_port_10g_kr_fw_req(NULL, iport, &req_msg);
            (void)perform_lp_training(iport, KR_TRAIN);
        }

        if (kr_sts.irq.vector & BT(KR_AN_GOOD)) {
            if (pconf.speed < MESA_SPEED_5G) {
                req_msg.aneg_disable = TRUE;
                (void)mesa_port_10g_kr_fw_req(NULL, iport, &req_msg);
                return;
            }            
        }

        if (kr_sts.irq.vector & BT(KR_RATE_DET)) {
            // Parallel detect speed change
            pconf.speed = kr_parallel_spd(iport, &kr);
            pconf.if_type = pconf.speed > MESA_SPEED_2500M ? MESA_PORT_INTERFACE_SFI : MESA_PORT_INTERFACE_SERDES;
            req_msg.gen0_tmr_start = 1;
            (void)mesa_port_conf_set(NULL, iport, &pconf);
            req_msg.rate_done = 1;
            (void)mesa_port_10g_kr_fw_req(NULL, iport, &req_msg);

        }

        if ((kr_sts.irq.vector & 0xf) > 0) {
            // Aneg speed change request
            pconf.speed = kr_irq2spd(kr_sts.irq.vector & 0xf);
            pconf.if_type = pconf.speed > MESA_SPEED_2500M ? MESA_PORT_INTERFACE_SFI : MESA_PORT_INTERFACE_SERDES;
            (void)mesa_port_conf_set(NULL, iport, &pconf);
            req_msg.rate_done = 1;
            (void)mesa_port_10g_kr_fw_req(NULL, iport, &req_msg);
        }
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Port KR aneg [<port_list>] [all] [train] [adv-1g] [adv-2g5] [adv-5g] [adv-10g] [fec]",
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
        "all: advertise everything",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "adv-1g",
        "adv-1g: advertise 1g",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "adv-2g5",
        "adv-2g5: advertise 2g5",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "adv-5g",
        "adv-5g: advertise 5g",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "adv-10g",
        "adv-10g: advertise 10g",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "fec",
        "fec: advertise fec capability",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "train",
        "train: enable training",
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
        kr_tr_state[port_no].next_parallel_spd = MESA_SPEED_10G;
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
