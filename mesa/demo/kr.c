/*
 Copyright (c) 2004-2020 Microsemi Corporation "Microsemi".

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
#include "cli.h"
#include "kr.h"
#include <sys/time.h>
#include <unistd.h>

typedef uint32_t u32;
typedef uint16_t u16;

#define PORTS 60
meba_inst_t meba_global_inst;
kr_train_t kr_tr_state[PORTS] = {0};
kr_conf_t kr_conf_state[PORTS] = {0};

// For debug
#define BUF_SIZE 1000000
#define API_TEST 1
uint32_t deb_dump_irq = 0;
uint32_t deb_my_limit = 2000;
uint32_t deb_my_cnt = 0;
uint32_t deb_coef_now[PORTS][3];
uint32_t deb_coef_max[PORTS][3] = {0};
uint32_t deb_coef_min = 0;
char deb_txt_buffer[BUF_SIZE] = {0};
mesa_bool_t deb_skip_training[PORTS] = {0};
mesa_bool_t deb_log_in_mem = 1;
struct timeval start;
u32 first = 1;
mesa_bool_t BASE_KR_V2 = 0;
mesa_bool_t BASE_KR_V3 = 0;

void kr_printf(const char *fmt, ...)
{
    va_list ap;
    char local_buf[1024];

    if (deb_my_cnt >= deb_my_limit) {
        return;
    }
    deb_my_cnt++;
    va_start(ap, fmt);
    vsnprintf(local_buf, 1024, fmt, ap);
    va_end(ap);
    if (!deb_log_in_mem) {
        printf("%s",local_buf);
    } else {
        if (strlen(deb_txt_buffer) + strlen(local_buf) > BUF_SIZE) {
            sprintf(deb_txt_buffer + strlen(deb_txt_buffer),"Buffer overflow");
            printf("Buffer overflow\n");
        } else {
            sprintf(deb_txt_buffer + strlen(deb_txt_buffer),"%s",local_buf);
        }

        if (deb_my_limit > 0 && (deb_my_cnt == (deb_my_limit-1))) {
            sprintf(deb_txt_buffer + strlen(deb_txt_buffer),"Text output disabled\n");
        }

    }
}

/* static char *bit2txt(uint32_t  bt, char *name) */
/* { */
/*     if (bt > 0) { */
/*         return name; */
/*     } */
/*     return ""; */
/* } */

char *ber2txt(mesa_ber_stage_t st)
{
    switch (st) {
    case MESA_BER_GO_TO_MIN:        return "GO_TO_MIN";
    case MESA_BER_CALCULATE_BER:    return "CALCULATE_BER";
    case MESA_BER_MOVE_TO_MID_MARK: return "MOVE_TO_MID_MARK";
    case MESA_BER_LOCAL_RX_TRAINED: return "LOCAL_RX_TRAINED";
    default:                        return "ILLEGAL";
    }
}

char *state2txt(mesa_train_state_t st)
{
    switch (st) {
    case MESA_TR_INITILIZE:        return "INITILIZE";
    case MESA_TR_SEND_TRAINING:    return "SEND_TRAINING";
    case MESA_TR_TRAIN_LOCAL:      return "TRAIN_LOCAL";
    case MESA_TR_TRAIN_REMOTE:     return "TRAIN_REMOTE";
    case MESA_TR_SEND_DATA:        return "SEND_DATA";
    case MESA_TR_TRAINING_FAILURE: return "TRAINING_FAILURE";
    case MESA_TR_LINK_READY:       return "LINK_READY";
    default:                       return "ILLEGAL";
    }
}

char *tap2txt(mesa_kr_tap_t st)
{
    switch (st) {
    case MESA_TAP_CM1: return "CM1";
    case MESA_TAP_CP1: return "CP1";
    case MESA_TAP_C0:  return "C0";
    default:           return "ILLEGAL";
    }
}

char *irq2txt(u32 irq)
{
    switch (irq) {
    case KR_ACTV:       return  "KR_ACTV";
    case KR_LPSVALID:   return  "KR_LPS";
    case KR_LPCVALID:   return  "KR_LPC";
    case KR_WT_DONE:    return  "WT_DONE";
    case KR_MW_DONE:    return  "MW_DONE";
    case KR_BER_BUSY_0: return  "BER_BUSY0";
    case KR_BER_BUSY_1: return  "BER_BUSY1";
    case KR_REM_RDY_0:  return  "REM_RDY0";
    case KR_REM_RDY_1:  return  "REM_RDY1";
    case KR_FRLOCK_0:   return  "FRLOCK0";
    case KR_FRLOCK_1:   return  "FRLOCK1";
    case KR_DME_VIOL_0: return  "DME_VIOL0";
    case KR_DME_VIOL_1: return  "DME_VIOL1";
    case KR_AN_XMIT_DISABLE: return  "AN_XM_DIS";
    case KR_TRAIN:      return  "TRAIN";
    case KR_RATE_DET:   return  "RATE_DET";
    case KR_CMPL_ACK:   return  "CMPL_ACK";
    case KR_AN_GOOD:    return  "AN_GOOD";
    case KR_LINK_FAIL:  return  "LINK_FAIL";
    case KR_ABD_FAIL:   return  "ABD_FAIL";
    case KR_ACK_FAIL:   return  "ACK_FAIL";
    case KR_NP_FAIL:    return  "NP_FAIL";
    case KR_NP_RX:      return  "NP_RX";
    case KR_INCP_LINK:  return  "INCP_LINK";
    case KR_GEN0_DONE:  return  "GEN0_DONE";
    case KR_GEN1_DONE:  return  "GEN1_DONE";
    case 0:  return "";
    default:  return "ILLEGAL";
    }
}


char *sts2txt(kr_status_report_t vector)
{
    switch (vector & 0xff) {
    case MAXIMUM: return "-->MAXIMUM";
    case MINIMUM: return "-->MINIMUM";
    case UPDATED:  return "UPDATED";
    case NOT_UPDATED:  return "NOT_UPDATED";
    default:  return "ILLEGAL";
    }
}

static void raw_coef2txt(u32 frm_in, char *tap_out, char *action_out)
{
    u32 action = 0;

    if (BT(13) & frm_in) {
        sprintf(tap_out, "PRESET ");
        sprintf(action_out, "PRESET ");
        return;
    }
    if (BT(12) & frm_in) {
        tap_out += sprintf(tap_out, "INIT ");
        action_out += sprintf(action_out, "INIT ");
        return;
    }
    if ((frm_in & 0x3) > 0) {
        tap_out += sprintf(tap_out, "CM1 ");
        action = frm_in & 0x3;
    }
    if ((frm_in & 0xc) > 0) {
        tap_out += sprintf(tap_out, "C0 ");
        action = (frm_in >> 2) & 3;
    }
    if ((frm_in & 0x30) > 0 ) {
        tap_out += sprintf(tap_out, "CP1 ");
        action = (frm_in >> 4) & 3;
    }
    if ((frm_in & 0x3f) == 0 ) {
        tap_out += sprintf(tap_out, "ANY ");
        action = 0;
    }

    if (action == 1) {
        sprintf(action_out, "INCR");
    } else if (action == 2) {
        sprintf(action_out, "DECR");
    } else {
        sprintf(action_out, "HOLD");
    }
}


static void raw_sts2txt(u32 frm_in, char *tap_out, char *action_out)
{
    u32 action = 0;

    if (BT(15) & frm_in) {
        sprintf(tap_out, "RX READY ");
    }
    if ((frm_in & 0x3) > 0) {
        tap_out += sprintf(tap_out, "CM1 ");
        action = frm_in & 0x3;
    }
    if ((frm_in & 0xc) > 0) {
        tap_out += sprintf(tap_out, "C0 ");
        action = (frm_in >> 2) & 3;
    }
    if ((frm_in & 0x30) > 0 ) {
        tap_out += sprintf(tap_out, "CP1 ");
        action = (frm_in >> 4) & 3;
    }
    if ((frm_in & 0x3f) == 0 ) {
        tap_out += sprintf(tap_out, "ANY ");
        action = 0;
    }

    if (action == 0) {
        sprintf(action_out, "NOT_UPDATED");
    } else if (action == 1) {
        sprintf(action_out, "UPDATED");
    } else if (action == 2) {
        sprintf(action_out, "MIN");
    } else if (action == 3) {
        sprintf(action_out, "MAX");
    }
}


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
    mesa_bool_t eye;
    mesa_bool_t fec;
    mesa_bool_t adv25g;
    mesa_bool_t adv10g;
    mesa_bool_t adv5g;
    mesa_bool_t adv2g5;
    mesa_bool_t adv1g;
    uint32_t    value;
    mesa_bool_t dis;
    mesa_bool_t hist;
    mesa_bool_t irq;
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
    } else if (!strncasecmp(found, "adv-25g", 7)) {
        mreq->adv25g = 1;
    } else if (!strncasecmp(found, "fec", 7)) {
        mreq->fec = 1;
    } else if (!strncasecmp(found, "train", 5)) {
        mreq->train = 1;
    } else if (!strncasecmp(found, "eyediag", 5)) {
        mreq->eye = 1;
    } else if (!strncasecmp(found, "all", 3)) {
        mreq->all = 1;
    } else if (!strncasecmp(found, "disable", 3)) {
        mreq->dis = 1;
    } else if (!strncasecmp(found, "hist", 3)) {
        mreq->hist = 1;
    } else if (!strncasecmp(found, "irq", 3)) {
        mreq->irq = 1;
    } else
        cli_printf("no match: %s\n", found);

    return 0;
}

static void fa_kr_reset_state(u32 p) {
    kr_train_t *krs = &kr_tr_state[p];
    memset(krs, 0, sizeof(kr_tr_state[p]));
}

static void cli_cmd_port_kr(cli_req_t *req)
{
    mesa_port_no_t        uport, iport;
    port_cli_req_t        *mreq = req->module_req;

    if (BASE_KR_V3) {
        mesa_port_kr_conf_t conf = {0};
        memset(deb_txt_buffer, 0, BUF_SIZE);
        for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
            uport = iport2uport(iport);
            if (req->port_list[uport] == 0) {
                continue;
            }
            if (mesa_port_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK) {
                continue;
            }
            (void)fa_kr_reset_state(iport);
            if (req->set) {
                conf.aneg.enable = mreq->dis ? 0 : 1;
                conf.train.enable = mreq->train || mreq->all;
                conf.train.eye_diag = mreq->eye;
                conf.aneg.adv_1g = mreq->adv1g || mreq->all;
                conf.aneg.adv_2g5 = mreq->adv2g5 || mreq->all;
                conf.aneg.adv_5g = mreq->adv5g || mreq->all;
                conf.aneg.adv_10g = mreq->adv10g || mreq->all;
                if (kr_conf_state[iport].cap_25g) {
                    conf.aneg.adv_25g = mreq->adv25g || mreq->all;
                }

                conf.aneg.fec_abil = mreq->fec || mreq->all;
                conf.aneg.fec_req = mreq->fec || mreq->all;

                if (mesa_port_kr_conf_set(NULL, iport, &conf) != MESA_RC_OK) {
                    cli_printf("KR set failed for port %u\n", uport);
                }
                deb_my_cnt = 0;
            } else {
                cli_printf("Port: %d\n", uport);
                cli_printf("  KR aneg: %s\n", conf.aneg.enable ? "Enabled" : "Disabled");
                cli_printf("  KR training: %s\n", conf.train.enable ? "Enabled" : "Disabled");
            }
        }
    } else if (BASE_KR_V2) {
        mesa_port_10g_kr_conf_t conf = {0};
        for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
            uport = iport2uport(iport);
            if (req->port_list[uport] == 0) {
                continue;
            }
            if (req->set) {
                conf.aneg.enable = 1;
                conf.train.enable = mreq->train || mreq->all;
                conf.aneg.adv_10g = mreq->adv10g || mreq->all;
                /* conf.aneg.fec_abil = mreq->fec || mreq->all; */
                /* conf.aneg.fec_req = mreq->fec || mreq->all; */

                if (mesa_port_10g_kr_conf_set(NULL, iport, &conf) != MESA_RC_OK) {
                    cli_printf("KR set failed for port %u\n", uport);
                }
            }
        }
    }
}

static void cli_cmd_port_kr_debug(cli_req_t *req)
{
    port_cli_req_t          *mreq = req->module_req;

    if (mreq->irq) {
        deb_dump_irq = !deb_dump_irq;
        printf("IRQ debug %s\n",deb_dump_irq ? "enabled" : "disabled");
        return;
    }

    if (deb_my_limit == 0) {
        printf("Logging enabled\n");
        memset(deb_txt_buffer, 0, BUF_SIZE);
        deb_my_limit = 10000;
        deb_my_cnt = 0;
    } else {
        printf("Loggin disabled\n");
        deb_my_limit = 0;
        deb_my_cnt = 0;
    }
}

static u32 tap_result(u32 value, u32 mask)
{
    if ((value & ~mask) > 0) {
        return ((~value) + 1) & mask;
    } else {
        return value;
    }
}

static void cli_cmd_port_kr_v2_status(cli_req_t *req)

{
    mesa_port_no_t uport, iport;
    mesa_port_10g_kr_status_t status;
    mesa_port_10g_kr_conf_t conf;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }

        if (mesa_port_10g_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK ||
            !conf.aneg.enable) {
            continue;
        }

        if (mesa_port_10g_kr_status_get(NULL, iport, &status) != MESA_RC_OK) {
            cli_printf("Port:%d Could not read status\n",iport);
            continue;
        }

        cli_printf("Port %u\n", iport);
        cli_printf("LP aneg ability                 :%s\n", status.aneg.lp_aneg_able ? "Yes" : "No");
        cli_printf("Aneg active (running)           :%s\n", status.aneg.active ? "Yes" : "No");
        cli_printf("PCS block lock                  :%s\n", status.aneg.block_lock ? "Yes" : "No");
        cli_printf("Aneg complete                   :%s\n", status.aneg.complete ? "Yes" : "No");
        cli_printf("  Enable 10G request            :%s\n", status.aneg.request_10g ? "Yes" : "No");
        cli_printf("  Enable 1G request             :%s\n", status.aneg.request_1g ? "Yes" : "No");
        cli_printf("  FEC change request            :%s\n", status.aneg.request_fec_change ? "Yes" : "No");

        mesa_bool_t cm = (status.train.cm_ob_tap_result >> 6) > 0 ? 1 : 0;
        mesa_bool_t cp = (status.train.cp_ob_tap_result >> 6) > 0 ? 1 : 0;
        mesa_bool_t c0 = (status.train.c0_ob_tap_result >> 6) > 0 ? 1 : 0;
        if (conf.train.enable) {
            cli_printf("Training complete (BER method)  :%s\n", status.train.complete ? "Yes" : "No");
            cli_printf("  CM OB tap (7-bit signed)      :%s%d (%d)\n", cm ? "-" : "+", tap_result(status.train.cm_ob_tap_result, 0x3f), status.train.cm_ob_tap_result);
            cli_printf("  CP OB tap (7-bit signed)      :%s%d (%d)\n", cp ? "-" : "+", tap_result(status.train.cp_ob_tap_result, 0x3f), status.train.cp_ob_tap_result);
            cli_printf("  C0 OB tap (7-bit signed)      :%s%d (%d)\n", c0 ? "-" : "+", tap_result(status.train.c0_ob_tap_result, 0x3f), status.train.c0_ob_tap_result);
        } else {
            cli_printf("Training                        :Disabled\n");
        }

        cli_printf("FEC                             :%s\n", status.fec.enable ? "Enabled" : "Disabled");
        if (status.fec.enable) {
            cli_printf("  Corrected block count         :%d\n", status.fec.corrected_block_cnt);
            cli_printf("  Un-corrected block count      :%d\n", status.fec.uncorrected_block_cnt);
        }
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

static void kr_dump_tr_ld_history(cli_req_t *req)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    kr_train_t              *krs;
    uint16_t                cp1, cm1, c0;
    uint32_t                dt;
    mesa_bool_t             first = TRUE;
    port_cli_req_t          *mreq = req->module_req;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }
        if (mesa_port_kr_conf_get(NULL, iport, &kr) != MESA_RC_OK ||
            !kr.aneg.enable) {
            continue;
        }

        krs = &kr_tr_state[iport];
        if (kr_tr_state[iport].ld_hist_index == 0) {
            continue;
        }
        first = TRUE;
        cli_printf("\nPort %d:\n",iport,kr_tr_state[iport]);
        for (uint16_t indx = 0; indx < kr_tr_state[iport].ld_hist_index; indx++) {
            char coef_tap[20] = {0};
            char coef_act[20] = {0};
            (void)raw_coef2txt(krs->ld_hist[indx].res.coef, coef_tap, coef_act);
            char sts_res[20] = {0};
            char sts_tap[20] = {0};
            (void)raw_sts2txt(krs->ld_hist[indx].res.status, sts_tap, sts_res);
            cp1 = krs->ld_hist[indx].res.cp1;
            cm1 = krs->ld_hist[indx].res.cm1;
            c0 = krs->ld_hist[indx].res.c0;
            dt = krs->ld_hist[indx].time;
            if (first) {
                cli_printf("%-4s%-8s%-8s%-8s%-8s%-8s%-10s%-8s\n","","TAP","CMD","CM1","Ampl","CP1","Status","Time (ms)");
                cli_printf("    ---------------------------------------------------------\n");
                first = FALSE;
            }
            if (!mreq->all && (krs->ld_hist[indx].res.coef == 0)) {
                continue; // Skip the HOLD cmd
            }
            cli_printf("%-4d%-8s%-8s%-8d%-8d%-8d%-10s%-8d\n", indx, coef_tap, coef_act, cm1, c0, cp1, sts_res, dt);
        }
    }
}

static void kr_dump_tr_lp_history(cli_req_t *req)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    kr_train_t              *krs;
    uint32_t                dt;
    mesa_bool_t             first = TRUE;
    port_cli_req_t          *mreq = req->module_req;
    char                    buf[200] = {0}, *b;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }
        if (mesa_port_kr_conf_get(NULL, iport, &kr) != MESA_RC_OK ||
            !kr.aneg.enable) {
            continue;
        }

        krs = &kr_tr_state[iport];
        if (kr_tr_state[iport].lp_hist_index == 0) {
            continue;
        }
        first = TRUE;
        cli_printf("\nPort %d:\n",iport,kr_tr_state[iport]);
        for (uint16_t indx = 0; indx < kr_tr_state[iport].lp_hist_index; indx++) {
            char coef_tap[20] = {0};
            char coef_act[20] = {0};
            (void)raw_coef2txt(krs->lp_hist[indx].ber_coef_frm, coef_tap, coef_act);
            dt = krs->lp_hist[indx].time;
            if (first) {
                cli_printf("%-4s%-8s%-8s%-20s%-8s%-20s\n","","TAP","CMD","BER state","ms","IRQs");
                cli_printf("    ---------------------------------------------------------\n");
                first = FALSE;
            }
            if (!mreq->all && (krs->lp_hist[indx].ber_coef_frm == 0)) {
                continue; // Skip the HOLD cmd
            }
            b = &buf[0];
            for (uint32_t i = 0; i < 31; i++) {
                if ((1 << i) & krs->lp_hist[indx].irq) {
                    b += sprintf(b, "%s ", irq2txt(1 << i));
                }
            }           

            cli_printf("%-4d%-8s%-8s%-20s%-8d%-20s\n", indx, coef_tap, coef_act, ber2txt(krs->lp_hist[indx].ber_training_stage), dt, buf);
        }
    }
}

static void cli_cmd_port_kr_status(cli_req_t *req)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    mesa_port_kr_status_t   sts;
    port_cli_req_t          *mreq = req->module_req;

    if (BASE_KR_V2) {
        cli_cmd_port_kr_v2_status(req);
        return;
    }

    if (mreq->all) {
        printf("Txt buffer:\n%s\n",deb_txt_buffer);
    } 

    if (mreq->hist) {
        printf("hist\n");
        kr_dump_tr_ld_history(req);
        kr_dump_tr_lp_history(req);
        return;
    }


    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }
        if (mesa_port_kr_conf_get(NULL, iport, &kr) != MESA_RC_OK ||
            !kr.aneg.enable) {
            continue;
        }
        if (mesa_port_kr_status_get(NULL, iport, &sts) != MESA_RC_OK) {
            cli_printf("Port:%d Could not read kr status\n",uport);
            continue;
        }
//        krs = &kr_tr_state[iport];
        cli_printf("Port %d\n",uport);
        cli_printf("  ANEG completed    : %s\n",sts.aneg.complete ? "Yes" : "No");
        cli_printf("  Speed             : %s\n",fa_kr_aneg_rate(sts.aneg.sts1 & 0xF));
        /* cli_printf("  This device training details:\n"); */
        /* cli_printf("  BER STAGE         : %s (GO_TO_MIN->CAL_CBER->MOVE_TO_MID->LOCAL_RX_TRAINED)\n",ber2txt(krs->ber_training_stage)); */
        /* cli_printf("  CURRENT TAP       : %s (CM1->C0->CP1)\n",tap2txt(krs->current_tap)); */
        /* cli_printf("  TRAINING_STATE    : %s (INIT->SEND_TRAIN->TRAIN_LOC->TRAIN_REM->LINK_READY->SEND_DATA)\n",state2txt(krs->current_state)); */
        /* cli_printf("  TRAINING_STARTED  : %s\n",krs->training_started ? "TRUE" :"FALSE"); */
        /* cli_printf("  REMOTE_RX_READY   : %s\n",krs->remote_rx_ready ? "TRUE" :"FALSE"); */
        /* cli_printf("  LOCAL_RX_READY    : %s\n",krs->local_rx_ready ? "TRUE" :"FALSE"); */
        /* cli_printf("  DME_VIOL_HANDLED  : %s\n",krs->dme_viol_handled ? "TRUE" :"FALSE"); */
        /* cli_printf("  BER_BUSY          : %s\n",krs->ber_busy ? "TRUE" :"FALSE"); */
        /* cli_printf("  TAP_MAX_REACHED   : %s\n",krs->tap_max_reached ? "TRUE" :"FALSE"); */
        /* cli_printf("  SIGNAL_DEECT      : %s\n",krs->signal_detect ? "TRUE" :"FALSE"); */
        /* cli_printf("  DECR_CNT          : %d\n",krs->decr_cnt); */
        /* cli_printf("  LP CM1 MAX/END    : %d/%d\n",krs->lp_tap_max_cnt[CM1],krs->lp_tap_end_cnt[CM1]); */
        /* cli_printf("  LP C0  MAX/END    : %d/%d\n",krs->lp_tap_max_cnt[C0], krs->lp_tap_end_cnt[C0]); */
        /* cli_printf("  LP CP1 MAX/END    : %d/%d\n",krs->lp_tap_max_cnt[CP1],krs->lp_tap_end_cnt[CP1]); */
        /* cli_printf("  BER_COUNT CM1     : "); */
        /* for (u32 i = 0; i < krs->lp_tap_max_cnt[CM1]; i++) { */
        /*     cli_printf("%d ",krs->ber_cnt[0][i]); */
        /* } */
        /* cli_printf("\n  BER_COUNT C0      : "); */
        /* for (u32 i = 0; i < krs->lp_tap_max_cnt[C0]; i++) { */
        /*     cli_printf("%d ",krs->ber_cnt[1][i]); */
        /* } */
        /* cli_printf("\n  BER_COUNT CP1     : "); */
        /* for (u32 i = 0; i < krs->lp_tap_max_cnt[CP1]; i++) { */
        /*     cli_printf("%d ",krs->ber_cnt[2][i]); */
        /* } */
        /* cli_printf("\n  EYE HEIGHT CM1    : "); */
        /* for (u32 i = 0; i < krs->lp_tap_max_cnt[CM1]; i++) { */
        /*     cli_printf("%d ",krs->eye_height[0][i]); */
        /* } */
        /* cli_printf("\n  EYE HEIGHT C0     : "); */
        /* for (u32 i = 0; i < krs->lp_tap_max_cnt[C0]; i++) { */
        /*     cli_printf("%d ",krs->eye_height[1][i]); */
        /* } */
        /* cli_printf("\n  EYE HEIGHT CP1    : "); */
        /* for (u32 i = 0; i < krs->lp_tap_max_cnt[CP1]; i++) { */
        /*     cli_printf("%d ",krs->eye_height[2][i]); */
        /* } */
        /* cli_printf("  \nTRAINING FRMS SENT: %d\n",krs->frm_sent); */
        /* cli_printf("  TRAINING TIME     : %d ms. (Remote is tuning Tx Serdes).\n",krs->tr_time_ld); */
        /* cli_printf("  TRAINING STATUS   : %s\n",krs->current_state == SEND_DATA ? "OK" : "Failed"); */

        /* cli_printf("  Remote device training details:\n"); */
        /* cli_printf("  LD CM1 MAX/END    : %d/%d\n",krs->ld_tap_max_cnt[CM1],krs->ld_tap_end_cnt[CM1]); */
        /* cli_printf("  LD C0  MAX/END    : %d/%d\n",krs->ld_tap_max_cnt[C0], krs->ld_tap_end_cnt[C0]); */
        /* cli_printf("  LD CP1 MAX/END    : %d/%d\n",krs->ld_tap_max_cnt[CP1],krs->ld_tap_end_cnt[CP1]); */
        /* cli_printf("  LD CM (tap_dly)   : %d (%d)\n",sts.train.cm_ob_tap_result, krs->ld_org_tap_val[CM1]); */
        /* cli_printf("  LD C0 (pc2pma)    : %d (%d)\n",sts.train.c0_ob_tap_result, krs->ld_org_tap_val[C0]); */
        /* cli_printf("  LD CP (tap_adv)   : %d (%d)\n",sts.train.cp_ob_tap_result, krs->ld_org_tap_val[CP1]); */
        /* cli_printf("  TRAINING TIME     : %d ms. (This device is tuning Tx Serdes).\n",krs->tr_time_rd); */

    }
}

/* static char *coef2txt(uint32_t vector) */
/* { */
/*     if (BT(13) & vector) { */
/*         return "PRESET"; */
/*     } */
/*     if (BT(12) & vector) { */
/*         return "INIT"; */
/*     } */

/*     if (vector == HOLD) { */
/*         return "HOLD"; */
/*     } else if (vector == INCR ) { */
/*         return "INCR"; */
/*     } else if (vector == DECR ) { */
/*         return "DECR"; */
/*     } */
/*     return "INVALID"; */
/* } */

static void time_start(struct timeval *store)
{
    (void)gettimeofday(store, NULL);
}

static u32 get_time_ms(struct timeval *store)
{
    struct timeval stop;
    (void)gettimeofday(&stop, NULL);
    return ((stop.tv_sec - store->tv_sec) * 1000000 + stop.tv_usec - store->tv_usec)/1000;
}

/* static mesa_port_speed_t kr_parallel_spd(mesa_port_no_t iport, mesa_port_kr_conf_t *conf) */
/* { */
/*     if (conf->aneg.adv_10g && (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_10G)) { */
/*         kr_conf_state[iport].next_parallel_spd = conf->aneg.adv_5g ? MESA_SPEED_5G : conf->aneg.adv_2g5 ? MESA_SPEED_2500M : MESA_SPEED_1G; */
/*         return MESA_SPEED_10G; */
/*     } else if (conf->aneg.adv_5g && (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_5G)) { */
/*         kr_conf_state[iport].next_parallel_spd = conf->aneg.adv_2g5 ? MESA_SPEED_2500M : MESA_SPEED_1G; */
/*         return MESA_SPEED_5G; */
/*     } else if (conf->aneg.adv_2g5 && (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_2500M)) { */
/*         kr_conf_state[iport].next_parallel_spd = MESA_SPEED_1G; */
/*         return MESA_SPEED_2500M; */
/*     } else  { */
/*         kr_conf_state[iport].next_parallel_spd = MESA_SPEED_10G;; */
/*         return MESA_SPEED_1G; */
/*     } */
/* } */

void kr_add_to_ld_history(mesa_port_no_t p, mesa_kr_status_results_t res)
{
    kr_train_t *krs = &kr_tr_state[p];
    if (krs->ld_hist_index < 200) {
        krs->ld_hist[krs->ld_hist_index].time = get_time_ms(&krs->time_start);
        krs->ld_hist[krs->ld_hist_index].res = res;
        krs->ld_hist_index++;
    }
}

void kr_add_to_lp_history(mesa_port_no_t p, uint32_t irq)
{
    kr_train_t *kr = &kr_tr_state[p];
    mesa_port_kr_state_t *krs = &kr_tr_state[p].state;
    if (kr->lp_hist_index < 200) {
        kr->lp_hist[kr->lp_hist_index].time = get_time_ms(&kr->time_start);
        kr->lp_hist[kr->lp_hist_index].ber_coef_frm = krs->ber_coef_frm;
        kr->lp_hist[kr->lp_hist_index].ber_training_stage = krs->ber_training_stage;
        kr->lp_hist[kr->lp_hist_index].irq = irq;
        kr->lp_hist_index++;
    }
}

#define KR_ANEG_RATE_25G 7
#define KR_ANEG_RATE_10G 9
#define KR_ANEG_RATE_5G 11
#define KR_ANEG_RATE_2G5 12
#define KR_ANEG_RATE_1G 13

/* static mesa_port_speed_t kr_irq2spd(uint32_t irq) */
/* { */
/*     switch (irq) { */
/*     case KR_ANEG_RATE_25G: return MESA_SPEED_25G; */
/*     case KR_ANEG_RATE_10G: return MESA_SPEED_10G; */
/*     case KR_ANEG_RATE_5G:  return MESA_SPEED_5G; */
/*     case KR_ANEG_RATE_2G5: return MESA_SPEED_2500M; */
/*     case KR_ANEG_RATE_1G:  return MESA_SPEED_1G; */
/*     default: */
/*         cli_printf("KR speed not supported\n"); */
/*     } */
/*     return MESA_SPEED_10G; */
/* } */



static void kr_poll(meba_inst_t inst)
{
    mesa_port_no_t        iport;
    mesa_port_kr_status_t kr_sts;
    mesa_port_kr_conf_t kr_conf;
    mesa_port_conf_t        pconf;
    mesa_port_kr_state_t   *krs;
    uint16_t meba_cnt = MEBA_WRAP(meba_capability, inst, MEBA_CAP_BOARD_PORT_COUNT);
    /* mesa_port_kr_fw_req_t req_msg = {0}; */
    kr_train_t *kr;

    for (iport = 0; iport < meba_cnt; iport++) {

        if (mesa_port_kr_conf_get(NULL, iport, &kr_conf) != MESA_RC_OK ||
            !kr_conf.aneg.enable) {
            continue;
        }

        if ((mesa_port_kr_status_get(NULL, iport, &kr_sts) != MESA_RC_OK)
            || (kr_sts.irq.vector == 0)) {
            continue;
        }
        kr = &kr_tr_state[iport];
        kr->status = kr_sts;

        if (kr_sts.irq.vector & KR_TRAIN) {
            (void)time_start(&kr->time_start); // Start the timer
         }

        (void)mesa_port_conf_get(NULL, iport, &pconf);

        mesa_port_kr_irq_apply(NULL, iport, &kr_sts.irq.vector);

        (void)mesa_port_kr_state_get(NULL, iport, &kr->state);
   
        krs = &kr->state;

        if ((kr_sts.irq.vector & KR_LPCVALID) && krs->training_started) {
            kr_add_to_ld_history(iport, krs->tr_res);
        }

        if (krs->training_started) {
            kr_add_to_lp_history(iport, kr_sts.irq.vector);
        }
      

/*         // KR_RATE_DET */
/*         if (kr_sts.irq.vector & KR_RATE_DET) { */
/*             // Parallel detect speed change */
/*             pconf.speed = kr_parallel_spd(iport, &kr); */
/*             pconf.if_type = pconf.speed > MESA_SPEED_2500M ? MESA_PORT_INTERFACE_SFI : MESA_PORT_INTERFACE_SERDES; */
/* //            req_msg.gen0_tmr_start = 1; */
/*             (void)mesa_port_conf_set(NULL, iport, &pconf); */
/*             /\* req_msg.rate_done = 1; *\/ */
/*             /\* (void)mesa_port_kr_fw_req(NULL, iport, &req_msg); *\/ */

/*         } */

/*         // KR_AN_RATE */
/*         if ((kr_sts.irq.vector & KR_AN_RATE) > 0) { */
/*             // Aneg speed change request */
/*             pconf.speed = kr_irq2spd(kr_sts.irq.vector & 0xf); */
/*             pconf.if_type = pconf.speed > MESA_SPEED_2500M ? MESA_PORT_INTERFACE_SFI : MESA_PORT_INTERFACE_SERDES; */
/*             (void)mesa_port_conf_set(NULL, iport, &pconf); */
/*             /\* req_msg.rate_done = 1; *\/ */
/*             /\* (void)mesa_port_kr_fw_req(NULL, iport, &req_msg); *\/ */
/*         } */
    }
}

static void kr_poll_v2(meba_inst_t inst)
{
    mesa_port_no_t iport;
    mesa_port_10g_kr_status_t status;
    mesa_port_10g_kr_conf_t conf;
    uint16_t meba_cnt = MEBA_WRAP(meba_capability, inst, MEBA_CAP_BOARD_PORT_COUNT);

    for (iport = 0; iport < meba_cnt; iport++) {

        if ((mesa_port_10g_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK) ||
            !conf.aneg.enable) {
            continue;
        }

        // 10G KR surveilance
        (void)(mesa_port_10g_kr_status_get(NULL, iport, &status));
    }

}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Port KR aneg [<port_list>] [all] [train] [adv-1g] [adv-2g5] [adv-5g] [adv-10g] [adv-25g] [fec] [disable] [eyediag]",
        "Set or show kr",
        cli_cmd_port_kr
    },
    {
        "Port KR status [<port_list>] [all] [hist]",
        "Show status",
        cli_cmd_port_kr_status
    },
    {
        "Port KR debug [irq]",
        "Toggle debug",
        cli_cmd_port_kr_debug
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
        "adv-25g",
        "adv-25g: advertise 25g",
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
    {
        "disable",
        "disable: disable kr",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "eyediag",
        "eyediag: use eye diagram instead of eye height",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "hist",
        "hist: dump the training history",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "irq",
        "irq: print out interrupts",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "pr",
        "print out",
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
    meba_port_entry_t     meba;

    /* Store the meba inst globally */
    meba_global_inst = inst;

    for (port_no = 0; port_no < port_cnt; port_no++) {
        kr_conf_state[port_no].next_parallel_spd = MESA_SPEED_10G;

        if (MEBA_WRAP(meba_port_entry_get, inst, port_no, &meba) != MESA_RC_OK) {
            continue;
        }

        kr_conf_state[port_no].cap_25g = (meba.cap & MEBA_PORT_CAP_25G_FDX) > 0 ? 1 : 0;
    }
}


void mscc_appl_kr_init(mscc_appl_init_t *init)
{

    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        if (mesa_capability(NULL, MESA_CAP_PORT_10GBASE_KR_V3)) {
            BASE_KR_V3 = 1;
        } else if (mesa_capability(NULL, MESA_CAP_PORT_10GBASE_KR_V2)) {
            BASE_KR_V2 = 1;
        }
        kr_init(init->board_inst);
        kr_cli_init();
        break;

    case MSCC_INIT_CMD_INIT_WARM:
        kr_init(init->board_inst);
        break;

    case MSCC_INIT_CMD_POLL_FAST:
        if (BASE_KR_V3) {
            kr_poll(init->board_inst);
        } else if (BASE_KR_V2) {
            kr_poll_v2(init->board_inst);
        }
        break;

    default:
        break;
    }
}
