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

meba_inst_t meba_global_inst;
kr_train_t kr_tr_state[100] = {0};
kr_conf_t kr_conf_state[100] = {0};

// For debug
#define BUF_SIZE 1000000
#define API_TEST 1
uint32_t my_limit = 2000;
uint32_t my_cnt = 0;
uint32_t coef_now[100][3];
uint32_t coef_max[100][3] = {0};
uint32_t coef_min = 0;
char txt_buffer[BUF_SIZE] = {0};
mesa_bool_t skip_training[100] = {0};
mesa_bool_t log_in_mem = 1;
struct timeval start;
u32 first = 1;
mesa_bool_t BASE_KR_V2 = 0;
mesa_bool_t BASE_KR_V3 = 0;

mesa_bool_t kr_mw_done = 0;

void kr_printf(const char *fmt, ...)
{
    va_list ap;
    char local_buf[1024];

    if (my_cnt >= my_limit) {
        return;
    }
    my_cnt++;
    va_start(ap, fmt);
    vsnprintf(local_buf, 1024, fmt, ap);
    va_end(ap);
    if (!log_in_mem) {
        printf("%s",local_buf);
    } else {
        if (strlen(txt_buffer) + strlen(local_buf) > BUF_SIZE) {
            sprintf(txt_buffer + strlen(txt_buffer),"Buffer overflow");
            printf("Buffer overflow\n");
        } else {
            sprintf(txt_buffer + strlen(txt_buffer),"%s",local_buf);
        }

        if (my_limit > 0 && (my_cnt == (my_limit-1))) {
            sprintf(txt_buffer + strlen(txt_buffer),"Text output disabled\n");
        }

    }
}

static char *bit2txt(uint32_t  bt, char *name)
{
    if (bt > 0) {
        return name;
    }
    return "";
}

char *ber2txt(ber_stage_t st)
{
    switch (st) {
    case GO_TO_MIN:        return "GO_TO_MIN";
    case CALCULATE_BER:    return "CALCULATE_BER";
    case MOVE_TO_MID_MARK: return "MOVE_TO_MID_MARK";
    case LOCAL_RX_TRAINED: return "LOCAL_RX_TRAINED";
    default:               return "ILLEGAL";
    }
}

char *state2txt(train_state_t st)
{
    switch (st) {
    case INITILIZE:        return "INITILIZE";
    case SEND_TRAINING:    return "SEND_TRAINING";
    case TRAIN_LOCAL:      return "TRAIN_LOCAL";
    case TRAIN_REMOTE:     return "TRAIN_REMOTE";
    case SEND_DATA:        return "SEND_DATA";
    case TRAINING_FAILURE: return "TRAINING_FAILURE";
    case LINK_READY:       return "LINK_READY";
    default:               return "ILLEGAL";
    }
}

char *tap2txt(kr_tap_t st)
{
    switch (st) {
    case CM1: return "CM1";
    case CP1: return "CP1";
    case C0:  return "C0";
    default:  return "ILLEGAL";
    }
}

char *irq2txt(u32 irq)
{
    switch (irq) {
    case KR_ACTV:       return  "KR_ACTV";
    case KR_LPSVALID:   return  "KR_LPSVALID";
    case KR_LPCVALID:   return  "KR_LPCVALID";
    case KR_WT_DONE:    return  "WT_DONE";
    case KR_MW_DONE:    return  "MW_DONE";
    case KR_BER_BUSY_0: return  "BER_BUSY_0";
    case KR_BER_BUSY_1: return  "BER_BUSY_1";
    case KR_REM_RDY_0:  return  "REM_RDY_0";
    case KR_REM_RDY_1:  return  "REM_RDY_1";
    case KR_FRLOCK_0:   return  "FRLOCK_0";
    case KR_FRLOCK_1:   return  "FRLOCK_1";
    case KR_DME_VIOL_0: return  "DME_VIOL_0";
    case KR_DME_VIOL_1: return  "DME_VIOL_1";
    case KR_AN_XMIT_DISABLE: return  "AN_XMIT_DISABLE";
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

    kr_mw_done = 0;

    if (BASE_KR_V3) {
        mesa_port_kr_conf_t conf = {0};
        memset(txt_buffer, 0, BUF_SIZE);
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
                my_cnt = 0;
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

    if (my_limit == 0) {
        printf("Debug enabled\n");
        memset(txt_buffer, 0, BUF_SIZE);
        my_limit = 10000;
        my_cnt = 0;
    } else {
        printf("Debug disabled\n");
        my_limit = 0;
        my_cnt = 0;
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

static void kr_dump_tr_history(cli_req_t *req)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    kr_train_t              *krs;
    uint16_t                cp1, cm1, c0;
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

        krs = &kr_tr_state[uport];

        cli_printf("Port %d: (%d)\n",uport,kr_tr_state[uport].hist_index);
        for (uint16_t indx = 0; indx < kr_tr_state[uport].hist_index; indx++) {
            char coef_tap[20] = {0};
            char coef_act[20] = {0};
            (void)raw_coef2txt(krs->coef_hist[indx].coef, coef_tap, coef_act);
            char sts_res[20] = {0};
            char sts_tap[20] = {0};
            (void)raw_sts2txt(krs->coef_hist[indx].res.status, sts_tap, sts_res);
            cp1 = krs->coef_hist[indx].res.cp1;
            cm1 = krs->coef_hist[indx].res.cm1;
            c0 = krs->coef_hist[indx].res.c0;
            if (first) {
                cli_printf("%-4s%-8s%-8s%-8s%-8s%-8s%-8s\n","","TAP","CMD","CM1","Ampl","CP1","Status");
                first = FALSE;
            }
            if (!mreq->all && (krs->coef_hist[indx].coef == 0)) {
                continue; // Skip the HOLD cmd
            }
            cli_printf("%-4d%-8s%-8s%-8d%-8d%-8d%-8s\n", indx, coef_tap, coef_act, cm1, c0, cp1, sts_res);
        }
    }    
}

static void cli_cmd_port_kr_status(cli_req_t *req)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    mesa_port_kr_status_t   sts;
    kr_train_t              *krs;
    port_cli_req_t          *mreq = req->module_req;

    if (BASE_KR_V2) {
        cli_cmd_port_kr_v2_status(req);
        return;
    }

    if (mreq->all) {
        printf("Txt buffer:\n%s\n",txt_buffer);
    } 

    if (mreq->hist) {
        kr_dump_tr_history(req);
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
        krs = &kr_tr_state[iport];
        cli_printf("Port %d\n",uport);
        cli_printf("  ANEG completed    : %s\n",sts.aneg.complete ? "Yes" : "No");
        cli_printf("  Speed             : %s\n",fa_kr_aneg_rate(sts.aneg.sts1 & 0xF));
        cli_printf("  This device training details:\n");
        cli_printf("  BER STAGE         : %s (GO_TO_MIN->CAL_CBER->MOVE_TO_MID->LOCAL_RX_TRAINED)\n",ber2txt(krs->ber_training_stage));
        cli_printf("  CURRENT TAP       : %s (CM1->C0->CP1)\n",tap2txt(krs->current_tap));
        cli_printf("  TRAINING_STATE    : %s (INIT->SEND_TRAIN->TRAIN_LOC->TRAIN_REM->LINK_READY->SEND_DATA)\n",state2txt(krs->current_state));
        cli_printf("  TRAINING_STARTED  : %s\n",krs->training_started ? "TRUE" :"FALSE");
        cli_printf("  REMOTE_RX_READY   : %s\n",krs->remote_rx_ready ? "TRUE" :"FALSE");
        cli_printf("  LOCAL_RX_READY    : %s\n",krs->local_rx_ready ? "TRUE" :"FALSE");
        cli_printf("  DME_VIOL_HANDLED  : %s\n",krs->dme_viol_handled ? "TRUE" :"FALSE");
        cli_printf("  BER_BUSY          : %s\n",krs->ber_busy ? "TRUE" :"FALSE");
        cli_printf("  TAP_MAX_REACHED   : %s\n",krs->tap_max_reached ? "TRUE" :"FALSE");
        cli_printf("  SIGNAL_DEECT      : %s\n",krs->signal_detect ? "TRUE" :"FALSE");
        cli_printf("  DECR_CNT          : %d\n",krs->decr_cnt);
        cli_printf("  LP CM1 MAX/END    : %d/%d\n",krs->lp_tap_max_cnt[CM1],krs->lp_tap_end_cnt[CM1]);
        cli_printf("  LP C0  MAX/END    : %d/%d\n",krs->lp_tap_max_cnt[C0], krs->lp_tap_end_cnt[C0]);
        cli_printf("  LP CP1 MAX/END    : %d/%d\n",krs->lp_tap_max_cnt[CP1],krs->lp_tap_end_cnt[CP1]);
        cli_printf("  BER_COUNT CM1     : ");
        for (u32 i = 0; i < krs->lp_tap_max_cnt[CM1]; i++) {
            cli_printf("%d ",krs->ber_cnt[0][i]);
        }
        cli_printf("\n  BER_COUNT C0      : ");
        for (u32 i = 0; i < krs->lp_tap_max_cnt[C0]; i++) {
            cli_printf("%d ",krs->ber_cnt[1][i]);
        }
        cli_printf("\n  BER_COUNT CP1     : ");
        for (u32 i = 0; i < krs->lp_tap_max_cnt[CP1]; i++) {
            cli_printf("%d ",krs->ber_cnt[2][i]);
        }
        cli_printf("\n  EYE HEIGHT CM1    : ");
        for (u32 i = 0; i < krs->lp_tap_max_cnt[CM1]; i++) {
            cli_printf("%d ",krs->eye_height[0][i]);
        }
        cli_printf("\n  EYE HEIGHT C0     : ");
        for (u32 i = 0; i < krs->lp_tap_max_cnt[C0]; i++) {
            cli_printf("%d ",krs->eye_height[1][i]);
        }
        cli_printf("\n  EYE HEIGHT CP1    : ");
        for (u32 i = 0; i < krs->lp_tap_max_cnt[CP1]; i++) {
            cli_printf("%d ",krs->eye_height[2][i]);
        }
        cli_printf("\n  FINAL EYE HEIGHT  : %d\n",krs->final_eye_height);
        cli_printf("  TRAINING FRMS SENT: %d\n",krs->frm_sent);
        cli_printf("  TRAINING TIME     : %d ms. (Remote is tuning Tx Serdes).\n",krs->tr_time_ld);
        cli_printf("  TRAINING STATUS   : %s\n",krs->current_state == SEND_DATA ? "OK" : "Failed");

        cli_printf("  Remote device training details:\n");
        cli_printf("  LD CM1 MAX/END    : %d/%d\n",krs->ld_tap_max_cnt[CM1],krs->ld_tap_end_cnt[CM1]);
        cli_printf("  LD C0  MAX/END    : %d/%d\n",krs->ld_tap_max_cnt[C0], krs->ld_tap_end_cnt[C0]);
        cli_printf("  LD CP1 MAX/END    : %d/%d\n",krs->ld_tap_max_cnt[CP1],krs->ld_tap_end_cnt[CP1]);
        cli_printf("  LD CM (tap_dly)   : %d (%d)\n",sts.train.cm_ob_tap_result, krs->ld_org_tap_val[CM1]);
        cli_printf("  LD C0 (pc2pma)    : %d (%d)\n",sts.train.c0_ob_tap_result, krs->ld_org_tap_val[C0]);
        cli_printf("  LD CP (tap_adv)   : %d (%d)\n",sts.train.cp_ob_tap_result, krs->ld_org_tap_val[CP1]);
        cli_printf("  TRAINING TIME     : %d ms. (This device is tuning Tx Serdes).\n",krs->tr_time_rd);

    }
}

static char *coef2txt(uint32_t vector)
{
    if (BT(13) & vector) {
        return "PRESET";
    }
    if (BT(12) & vector) {
        return "INIT";
    }

    if (vector == HOLD) {
        return "HOLD";
    } else if (vector == INCR ) {
        return "INCR";
    } else if (vector == DECR ) {
        return "DECR";
    }
    return "INVALID";
}

static void print_irq_vector(uint32_t p, uint32_t vector, u32 time)
{
    struct timeval tv;
    int            s;
    char buf[200] = {0}, *b;

    kr_train_t *krs = &kr_tr_state[p];

    if (vector == 0) {
        return;
    }
    if (my_cnt > my_limit) {
        return;
    }
    (void)gettimeofday(&tv, NULL);
    s = (tv.tv_sec % 60);

    b = &buf[0];
    b += sprintf(b, "Port:%d (%02u:%03lu) %s (%d ms)\n",p+1,s,tv.tv_usec/1000, (krs->current_state == SEND_DATA) ? "TRAINING COMPLETED":"", time);
    b += sprintf(b, "       IRQ Vector:");
    b += sprintf(b, "%s", bit2txt((KR_ACTV & vector),       "KR_ACTV "));
    b += sprintf(b, "%s", bit2txt((KR_LPSVALID & vector),   "KR_LPSVALID "));
    b += sprintf(b, "%s", bit2txt((KR_LPCVALID & vector),   "KR_LPCVALID "));
    b += sprintf(b, "%s", bit2txt((KR_WT_DONE & vector),    "WT_DONE "));
    b += sprintf(b, "%s", bit2txt((KR_MW_DONE & vector),    "MW_DONE "));
    b += sprintf(b, "%s", bit2txt((KR_BER_BUSY_0 & vector), "BER_BUSY_0 "));
    b += sprintf(b, "%s", bit2txt((KR_BER_BUSY_1 & vector), "BER_BUSY_1 "));
    b += sprintf(b, "%s", bit2txt((KR_REM_RDY_0 & vector),  "REM_RDY_0 "));
    b += sprintf(b, "%s", bit2txt((KR_REM_RDY_1 & vector),  "REM_RDY_1 "));
    b += sprintf(b, "%s", bit2txt((KR_FRLOCK_0 & vector),   "FRLOCK_0 "));
    b += sprintf(b, "%s", bit2txt((KR_FRLOCK_1 & vector),   "FRLOCK_1 "));
    b += sprintf(b, "%s", bit2txt((KR_DME_VIOL_0 & vector), "DME_VIOL_0 "));
    b += sprintf(b, "%s", bit2txt((KR_DME_VIOL_1 & vector), "DME_VIOL_1 "));
    b += sprintf(b, "%s", bit2txt((KR_AN_XMIT_DISABLE & vector),  "AN_XMIT_DISABLE "));
    b += sprintf(b, "%s", bit2txt((KR_TRAIN & vector),      "TRAIN "));
    b += sprintf(b, "%s", bit2txt((KR_RATE_DET & vector),   "RATE_DET "));
    b += sprintf(b, "%s", bit2txt((KR_CMPL_ACK & vector),   "CMPL_ACK "));
    b += sprintf(b, "%s", bit2txt((KR_AN_GOOD & vector),    "AN_GOOD "));
    b += sprintf(b, "%s", bit2txt((KR_LINK_FAIL & vector),  "LINK_FAIL "));
    b += sprintf(b, "%s", bit2txt((KR_ABD_FAIL & vector),   "ABD_FAIL "));
    b += sprintf(b, "%s", bit2txt((KR_ACK_FAIL & vector),   "ACK_FAIL "));
    b += sprintf(b, "%s", bit2txt((KR_NP_FAIL & vector),    "NP_FAIL "));
    b += sprintf(b, "%s", bit2txt((KR_NP_RX & vector),      "ACK_NP_RX "));
    b += sprintf(b, "%s", bit2txt((KR_INCP_LINK & vector),  "INCP_LINK "));
    b += sprintf(b, "%s", bit2txt((KR_GEN0_DONE & vector),  "GEN0_DONE "));
    b += sprintf(b, "%s", bit2txt((KR_GEN1_DONE & vector),  "GEN1_DONE "));

    if ((0xf & vector) > 0) {
//        printf("P:%d Aneg speed:%s\n",p, fa_kr_aneg_rate((0xf & vector)));
        sprintf(b, "%s",fa_kr_aneg_rate((0xf & vector)));
    }

    kr_printf("%s\n",buf);

}

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

static mesa_port_speed_t kr_parallel_spd(mesa_port_no_t iport, mesa_port_kr_conf_t *conf)
{
    if (conf->aneg.adv_10g && (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_10G)) {
        kr_conf_state[iport].next_parallel_spd = conf->aneg.adv_5g ? MESA_SPEED_5G : conf->aneg.adv_2g5 ? MESA_SPEED_2500M : MESA_SPEED_1G;
        return MESA_SPEED_10G;
    } else if (conf->aneg.adv_5g && (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_5G)) {
        kr_conf_state[iport].next_parallel_spd = conf->aneg.adv_2g5 ? MESA_SPEED_2500M : MESA_SPEED_1G;
        return MESA_SPEED_5G;
    } else if (conf->aneg.adv_2g5 && (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_2500M)) {
        kr_conf_state[iport].next_parallel_spd = MESA_SPEED_1G;
        return MESA_SPEED_2500M;
    } else  {
        kr_conf_state[iport].next_parallel_spd = MESA_SPEED_10G;;
        return MESA_SPEED_1G;
    }
}

static u32 get_api_eye_height(mesa_port_no_t p)
{
    mesa_port_kr_eye_dim_t eye;

    if (mesa_port_kr_eye_dim_get(NULL, p, &eye) == MESA_RC_OK) {
        return eye.height;
    } else {
        printf("Eye scan fails to complete\n");
    }
    return 0;
}

static kr_status_report_t coef2status(mesa_port_no_t p, kr_coefficient_t data)
{
    kr_coefficient_t coef = data;
    kr_status_report_t status = 0;
    kr_tap_t tap = 0;
    kr_train_t *krs = &kr_tr_state[p];

    if (((data & INIT)) == 0 && ((data & PRESET) == 0)) {
        if (((data >> 4) & 0x3) > 0) {
            coef = (data >> 4) & 0x3;
            tap = CP1;
        } else if (((data >> 2) & 0x3) > 0) {
            coef = (data >> 2) & 0x3;
            tap = C0;
        } else {
            coef = data & 0x3;
            tap = CM1;
        }
    }

    if (coef == INIT) {
        coef_now[p][CM1] = coef_max[p][CM1] / 2;
        coef_now[p][CP1] = coef_max[p][CP1] / 2;
        coef_now[p][C0]  = coef_max[p][C0] / 2;
        status = UPDATED;
    } else if (coef == PRESET) {
        coef_now[p][CM1] = coef_max[p][CM1] / 2;
        coef_now[p][CP1] = coef_max[p][CP1] / 2;
        coef_now[p][C0]  = coef_max[p][C0] / 2;
        status = UPDATED;
    } else if (coef == HOLD) {
        status = NOT_UPDATED;
    } else if (coef == INCR) {
        if (coef_now[p][tap] < coef_max[p][tap]) {
            coef_now[p][tap]++;
            status = UPDATED;
        } else {
            status = MAXIMUM;
        }
        krs->ld_tap_max_cnt[tap]++;
        if (status == MAXIMUM) {
            krs->ld_tap_end_cnt[tap] = krs->ld_tap_max_cnt[tap];
        }

    } else if (coef == DECR) {
        if (coef_now[p][tap] > coef_min) {
            coef_now[p][tap]--;
            status = UPDATED;
        } else {
            status = MINIMUM;
        }
        if ((krs->ld_tap_end_cnt[tap]) > 0) {
            krs->ld_tap_end_cnt[tap]--;
        }
    } else  {
        printf("Error in coef\n");
    }

    if (krs->ber_training_stage == LOCAL_RX_TRAINED) {
        krs->local_rx_ready = TRUE;
    }

    if (krs->ber_training_stage == LOCAL_RX_TRAINED) {
        status += BT(15);
    }

    if (tap == CP1) {
        status = status << 4;
    } else if (tap == C0) {
        status = status << 2;
    } else if ((coef == PRESET) || coef == PRESET) {
        status = (status << 4) | (status << 2) |  status;
    }

    char coef_tap[20] = {0};
    char coef_act[20] = {0};
    (void)raw_coef2txt(data, coef_tap, coef_act);
    char sts_tap[20] = {0};
    char sts_act[20] = {0};
    (void)raw_sts2txt(status, sts_tap, sts_act);

    kr_printf("       (UPD)TAP:%s Action:%s -> Status:%s/ %s\n", coef_tap, coef_act, sts_tap, sts_act);

    return status;
}


void kr_add_to_history(mesa_port_no_t p, kr_coefficient_t coef, mesa_port_kr_status_results_t res)
{
    kr_train_t *krs = &kr_tr_state[p];
    if (krs->hist_index < 100) {
        krs->coef_hist[krs->hist_index].coef = coef;
        krs->coef_hist[krs->hist_index].res = res;
        krs->hist_index++;
    }
}

static uint16_t coef2status_api(mesa_port_no_t p, uint16_t data)
{
    mesa_port_kr_status_results_t res;
    kr_train_t *krs = &kr_tr_state[p];
    kr_coefficient_t coef = data;
    kr_tap_t tap = 0;
    kr_status_report_t sts = 0;

    mesa_port_kr_coef_set(NULL, p, data, &res);
    kr_add_to_history(p, data, res);

    if (((data & INIT)) == 0 && ((data & PRESET) == 0)) {
        if (((data >> 4) & 0x3) > 0) {
            coef = (data >> 4) & 0x3;
            sts = (res.status >> 4) & 0x3;
            tap = CP1;
        } else if (((data >> 2) & 0x3) > 0) {
            coef = (data >> 2) & 0x3;
            sts = (res.status >> 2) & 0x3;
            tap = C0;
        } else {
            coef = data & 0x3;
            sts = res.status & 0x3;
            tap = CM1;
        }
    }

    if (coef == INCR) {
        krs->ld_tap_max_cnt[tap]++;
        if (sts == MAXIMUM) {
            krs->ld_tap_end_cnt[tap] = krs->ld_tap_max_cnt[tap];
        }
    } else if (coef == DECR) {
        if ((krs->ld_tap_end_cnt[tap]) > 0) {
            krs->ld_tap_end_cnt[tap]--;
        }
    }

    char coef_tap[20] = {0};
    char coef_act[20] = {0};
    (void)raw_coef2txt(data, coef_tap, coef_act);
    char sts_tap[20] = {0};
    char sts_act[20] = {0};
    (void)raw_sts2txt(res.status, sts_tap, sts_act);

    if (krs->ber_training_stage == LOCAL_RX_TRAINED) {
        res.status += BT(15);
    }

    kr_printf("       (UPD)TAP:%s Action:%s -> Status:%s/ %s\n", coef_tap, coef_act, sts_tap, sts_act);

    return res.status;
}

static uint16_t update_coef(kr_coefficient_t ld, kr_tap_t tap)
{
    uint16_t offset;

    if (tap == CP1) {
        offset = 4;
    } else if (tap == C0) {
        offset = 2;
    } else {
        offset = 0;
    }

    switch (ld) {
    case PRESET: return (1 << 13);
    case INIT:   return (1 << 12);
    case DECR:   return (1 << (1 + offset));
    case INCR:   return (1 << (0 + offset));
    case HOLD:   return 0;
    default:
        kr_printf("Illegal prm\n");
        break;
    }
    return 0;
}

static kr_status_report_t kr_status_report(uint16_t data, kr_tap_t tap)
{
    uint16_t sts = 0;

    if (tap == CP1) {
        sts = (data >> 4) & 0x3;
    } else if (tap == C0) {
        sts = (data >> 2) & 0x3;
    } else {
        sts = data & 0x3;
    }

    switch (sts) {
    case 0:  return NOT_UPDATED;
    case 1:  return UPDATED;
    case 2:  return MINIMUM;
    case 3:  return MAXIMUM;
    default:
        kr_printf("Illegal prm\n");
        break;
    }
    return 0;
}


#define KR_ANEG_RATE_25G 7
#define KR_ANEG_RATE_10G 9
#define KR_ANEG_RATE_5G 11
#define KR_ANEG_RATE_2G5 12
#define KR_ANEG_RATE_1G 13

static mesa_port_speed_t kr_irq2spd(uint32_t irq)
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

static void analyze_ber(u32 p, uint16_t *ber, uint16_t *high_mark, uint16_t *low_mark)
{
    kr_train_t *krs = &kr_tr_state[p];
    /* for (uint16_t i = 0; i < 64; i++ ) { */
    /*     if (ber[i] > BER_THRESHOLD) { */
    /*         *low_mark = i; */
    /*         break; */
    /*     } */
    /* } */

    /* for (uint16_t i = 64; i != 0; i-- ) { */
    /*     if (ber[i] > BER_THRESHOLD) { */
    /*         *high_mark = i; */
    /*         break; */
    /*     } */
    /* } */

    *high_mark = krs->tap_idx;
    *low_mark = 0;
}

static u32 get_best_eye(u32 p, kr_tap_t tap)
{
    kr_train_t *krs = &kr_tr_state[p];

    u32 max = krs->eye_height[tap][0];
    u32 indx = 0;
    for (u32 i = 0; i < krs->lp_tap_max_cnt[tap]; i++) {

        if (krs->eye_height[tap][i] >= max ) {
            max = krs->eye_height[tap][i];
            indx = i;
        }
    }
    return indx + 1;
}


static kr_tap_t next_tap(kr_tap_t tap)
{
    switch (tap) {
    case CM1:
        return C0;
    case C0:
        return CP1;
    case CP1:
        return 0;
    }
    return 0;
}

static void send_coef_update(mesa_port_no_t p, kr_coefficient_t coef, kr_tap_t tap, char *txt)
{
    mesa_port_kr_frame_t frm;
//    kr_train_t *krs = &kr_tr_state[p];
    kr_printf("       (LPT)TX COEF FRM: %s (%s)\n", coef2txt(coef), txt);
    frm.data = update_coef(coef, tap);
    frm.type = MESA_COEFFICIENT_UPDATE_FRM;
    (void)mesa_port_kr_train_frm_set(NULL, p, &frm);
}

static void send_sts_report(mesa_port_no_t p, u32 data)
{
    mesa_port_kr_frame_t frm;
    kr_train_t *krs = &kr_tr_state[p];

    if (data & BT(15)) {
        krs->receiver_ready_sent = TRUE;
    }

    frm.data = data;
    frm.type = MESA_STATUS_REPORT_FRM;
    // Send Status report
    (void)mesa_port_kr_train_frm_set(NULL, p, &frm);
}

static void perform_lp_training(mesa_port_no_t p, uint32_t irq)
{
    mesa_port_kr_frame_t frm;
    kr_train_t *krs = &kr_tr_state[p];
    kr_status_report_t lp_status = 0;
    mesa_port_kr_fw_req_t req_msg = {0};

    if (skip_training[p]) {
        krs->ber_training_stage = LOCAL_RX_TRAINED;
        return;
    }

    kr_printf("       (LPT)IRQ:%s TAP:%s BER:%s STATE:%s\n",irq2txt(irq), tap2txt(krs->current_tap),
              ber2txt(krs->ber_training_stage), state2txt(krs->current_state));

    if (irq == KR_TRAIN) {
        send_coef_update(p, INIT, krs->current_tap, "KR_TRAIN");
        krs->ber_training_stage = GO_TO_MIN;
        krs->current_tap = CM1;
        return;
    }

    if (irq == KR_LPSVALID) {
       frm.type = MESA_STATUS_REPORT_FRM;
       (void)mesa_port_kr_train_frm_get(NULL, p, &frm);
       lp_status = kr_status_report(frm.data, krs->current_tap);
       kr_printf("       (LPT)RX STS FRM: %s (%x)\n", sts2txt(lp_status),frm.data);
    }

    switch (krs->ber_training_stage) {
    case GO_TO_MIN:
        if (irq == KR_LPSVALID) {
            if (lp_status == UPDATED || lp_status == MAXIMUM) {
                send_coef_update(p, HOLD, krs->current_tap, "GO_TO_MIN");
                if (krs->dme_viol_handled) {
                    req_msg.ber_enable = TRUE;
                    (void)mesa_port_kr_fw_req(NULL, p, &req_msg);
                    krs->ber_busy_sw = TRUE;
                    krs->ber_training_stage = CALCULATE_BER;
                    krs->tap_idx = 0;
                    krs->dme_viol = 0;
                    krs->dme_viol_handled = FALSE;
                }
            } else if (lp_status == NOT_UPDATED) {
                if (krs->dme_viol) {
                    send_coef_update(p, INCR, krs->current_tap, "GO_TO_MIN");
                    krs->dme_viol_handled = TRUE;
                } else {
                    send_coef_update(p, DECR, krs->current_tap, "GO_TO_MIN");
                }
            } else if (lp_status == MINIMUM) {
                send_coef_update(p, HOLD, krs->current_tap, "GO_TO_MIN/BER_ENABLE");
                req_msg.ber_enable = TRUE;
                (void)mesa_port_kr_fw_req(NULL, p, &req_msg);
                krs->ber_busy_sw = TRUE;
                krs->ber_training_stage = CALCULATE_BER;
                krs->tap_idx = 0;
                krs->tap_max_reached = FALSE;
            } else {
                printf("Error Got lp_status:%d\n",lp_status);
            }

        } else {
            kr_printf("Perform_lp_traing valled with irq:%d when in stage GO_TO_MIN\n",irq);
        }
        return;
    case CALCULATE_BER:
        if (irq == KR_BER_BUSY_1) {
            krs->ber_busy = TRUE;
        } else if ((irq == KR_BER_BUSY_0) && (krs->ber_busy)) {
            krs->ber_busy_sw = FALSE;
            krs->ber_busy = FALSE;
            krs->ber_cnt[krs->current_tap][krs->tap_idx] = krs->status.train.frame_errors;
            kr_printf("       (LPT)GET_EYE 1 (%d ms)\n",get_time_ms(&krs->time_start));
            krs->ignore_fail = TRUE;
            krs->eye_height[krs->current_tap][krs->tap_idx] = get_api_eye_height(p);
            kr_printf("       (LPT)GET_EYE 2 (%d ms)\n",get_time_ms(&krs->time_start));
            if (krs->tap_max_reached) {
                krs->lp_tap_max_cnt[krs->current_tap] = krs->tap_idx;
                u16 high_mark = 0;
                u16 low_mark = 0;
                analyze_ber(p, krs->ber_cnt[krs->current_tap], &high_mark, &low_mark);
                u16 mid_mark = get_best_eye(p, krs->current_tap);
                krs->lp_tap_end_cnt[krs->current_tap] = mid_mark;
                krs->decr_cnt = krs->tap_idx - mid_mark;
                send_coef_update(p, DECR, krs->current_tap, "CALC_BER/BER_BUSY");
                krs->ber_training_stage = MOVE_TO_MID_MARK;
            } else {
                send_coef_update(p, INCR, krs->current_tap, "CALC_BER/BER_BUSY");
            }
        } else if (irq == KR_LPSVALID) {
            if (!krs->ber_busy && !krs->ber_busy_sw) {
                if (lp_status == NOT_UPDATED) {
                    if (krs->dme_viol) {
                        send_coef_update(p, DECR, krs->current_tap, "CALC_BER/LPS_VALID");
                        krs->dme_viol_handled = TRUE;
                    } else {
                        send_coef_update(p, INCR, krs->current_tap, "CALC_BER/LPS_VALID");
                    }
                } else if (lp_status == UPDATED || lp_status == MAXIMUM) {
                    send_coef_update(p, HOLD, krs->current_tap, "CALC_BER/LPS_VALID/BER_ENABLE");
                    req_msg.ber_enable = TRUE;
                    (void)mesa_port_kr_fw_req(NULL, p, &req_msg);
                    krs->ber_busy_sw = TRUE;
                    krs->tap_idx++;
                    if((lp_status == MAXIMUM) || krs->dme_viol_handled) {
                        krs->tap_max_reached = TRUE;
                        if (krs->dme_viol_handled) {
                            krs->tap_idx--;
                            krs->dme_viol = FALSE;
                            krs->dme_viol_handled = FALSE;
                        }
                    } else {
                        krs->tap_max_reached = FALSE;
                    }
                } else if (lp_status != NOT_UPDATED) {
                    kr_printf("Invalid status reveived when BER is busy\n");
                } else {
                    kr_printf("LPSVALID Invalid state 1\n");
                }
            }
        } else if (irq == KR_DME_VIOL_1) {
            krs->dme_viol = TRUE;
        } else {
            kr_printf("LPSVALID Invalid state 2\n");
        }
        break;
    case MOVE_TO_MID_MARK:
        if (irq == KR_LPSVALID) {
            if (lp_status == UPDATED) {
                send_coef_update(p, HOLD, krs->current_tap, "MOVE_TO_MID");
                if (krs->decr_cnt > 0) {
                    krs->decr_cnt--;
                }
                if (krs->decr_cnt == 0) {
                    if (krs->current_tap == CP1) {
                        krs->ber_training_stage = LOCAL_RX_TRAINED;
                        krs->frm_sent = krs->status.train.frame_sent;
                        kr_printf("       (LPT)LOCAL_RX_TRAINED\n");
                        for (u32 i = 0; ((i < 3) && (krs->final_eye_height < 10)); i++) {
                            krs->final_eye_height = get_api_eye_height(p);
                        }
                    } else {
                        krs->current_tap = next_tap(krs->current_tap);
                        kr_printf("       (LPT)Next tap:%s\n",tap2txt(krs->current_tap));
                        krs->ber_training_stage = GO_TO_MIN;
                    }
                } else if (lp_status == NOT_UPDATED) {
                    send_coef_update(p, DECR, krs->current_tap, "MOVE_TO_MID");
                }
            } else if (lp_status == NOT_UPDATED) {
                send_coef_update(p, DECR, krs->current_tap, "MOVE_TO_MID");
            }
        } else {
            kr_printf("perform_lp_training called on invalid irq (%x) in state MOVE_TO_MID_MARK\n",irq);
        }
        break;

    default:
        kr_printf("Reach DEFAULT (irq:%d)\n",irq);
        break;
    }

}

static void kr_poll(meba_inst_t inst)
{
    mesa_port_no_t        iport;
    mesa_port_kr_status_t kr_sts;
    mesa_port_kr_conf_t kr;
    mesa_port_conf_t        pconf;
    uint16_t meba_cnt = MEBA_WRAP(meba_capability, inst, MEBA_CAP_BOARD_PORT_COUNT);
    mesa_port_kr_fw_req_t req_msg = {0};
    kr_train_t *krs;

    for (iport = 0; iport < meba_cnt; iport++) {

        if (mesa_port_kr_conf_get(NULL, iport, &kr) != MESA_RC_OK ||
            !kr.aneg.enable) {
            continue;
        }

        if (first) {

            // For debug purposes

            skip_training[0] = 0;
            /* coef_max[0][CM1] = 3; */
            /* coef_max[0][C0]  = 17; */
            /* coef_max[0][CP1] = 22; */

            /* coef_max[1][CM1] = 3; */
            /* coef_max[1][C0]  = 17; */
            /* coef_max[1][CP1] = 22; */

            for (u32 x = 0; x < 20; x++) {
                coef_max[x][CM1] = 2;
                coef_max[x][C0]  = 2;
                coef_max[x][CP1] = 2;

                coef_max[x][CM1] = 2;
                coef_max[x][C0]  = 2;
                coef_max[x][CP1] = 2;
            }

            (void)gettimeofday(&start, NULL);
            first = 0;
            if (!API_TEST) {
                printf("NOTE: API is disabled\n");
            }
        }

        if ((mesa_port_kr_status_get(NULL, iport, &kr_sts) != MESA_RC_OK)
            || (kr_sts.irq.vector == 0)) {
            continue;
        }
        krs = &kr_tr_state[iport];
        krs->status = kr_sts;

        if (kr_mw_done) {
            continue;
        }

        (void)mesa_port_conf_get(NULL, iport, &pconf);
        (void)print_irq_vector(iport, kr_sts.irq.vector, get_time_ms(&krs->time_start));

        if (kr_sts.irq.vector & KR_DME_VIOL_0 || kr_sts.irq.vector & KR_DME_VIOL_1 ||
            kr_sts.irq.vector & KR_REM_RDY_0 || kr_sts.irq.vector & KR_REM_RDY_0 ||
            kr_sts.irq.vector & KR_FRLOCK_0) {
            if (krs->ignore_fail) { // Needed due to failures during eye height calculation
                kr_printf("       (FAIL)Rx IRQ Errors\n");
                kr_sts.irq.vector &= ~KR_DME_VIOL_0;
                kr_sts.irq.vector &= ~KR_DME_VIOL_1;
                kr_sts.irq.vector &= ~KR_REM_RDY_0;
                kr_sts.irq.vector &= ~KR_FRLOCK_0;
            }
        }

        // KR_AN_XMIT_DISABLE. Aneg is restarted.
        if (kr_sts.irq.vector & KR_AN_XMIT_DISABLE) {
            if (krs->training_started) {
                krs->training_started = FALSE;
                req_msg.stop_training = TRUE;
                (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);
            }
            fa_kr_reset_state(iport);
            krs->ld_org_tap_val[CM1] = kr_sts.train.cm_ob_tap_result;
            krs->ld_org_tap_val[CP1] = kr_sts.train.cp_ob_tap_result;
            krs->ld_org_tap_val[C0] = kr_sts.train.c0_ob_tap_result;
        }
        // KR_TRAIN. Start Training
        if (kr_sts.irq.vector & KR_TRAIN) {
            if (kr.train.enable) {
                (void)time_start(&krs->time_start); // Start the timer
                krs->current_state = SEND_TRAINING;
                krs->training_started = TRUE;
                krs->remote_rx_ready = FALSE;
                krs->local_rx_ready = FALSE;
                req_msg.start_training = TRUE;
                req_msg.mw_start = TRUE;
                (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);
                (void)perform_lp_training(iport, KR_TRAIN);
            } else {
                krs->current_state = SEND_DATA;
                krs->training_started = FALSE;
                req_msg.stop_training = TRUE;
                req_msg.tr_done = TRUE;
                (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);
                krs->signal_detect = TRUE;
            }
        }

        // KR_FRLOCK_1. Training frame lock attained. Change state to TRAIN_LOCAL
        if ((kr_sts.irq.vector & KR_FRLOCK_1) && krs->training_started) {
            if (krs->current_state == SEND_TRAINING) {
                krs->current_state = TRAIN_LOCAL;
            }
        }

        // KR_REM_RDY_1. Remote is ready
        if (kr_sts.irq.vector & KR_REM_RDY_1) {
            if (!krs->remote_rx_ready) {
                krs->tr_time_rd = get_time_ms(&krs->time_start);
            }
            krs->remote_rx_ready = TRUE;
            // Ignore failures after remote is ready
            kr_sts.irq.vector &= ~KR_DME_VIOL_0;
            kr_sts.irq.vector &= ~KR_DME_VIOL_1;
            kr_sts.irq.vector &= ~KR_REM_RDY_0;
            kr_sts.irq.vector &= ~KR_FRLOCK_0;

        }

        // KR_FRLOCK_0. Training frame lock is lost during training
        if ((kr_sts.irq.vector & KR_FRLOCK_0) && krs->training_started && (krs->current_state != LINK_READY)) {
            if ((krs->current_state == TRAIN_LOCAL) || (krs->current_state == TRAIN_REMOTE)) {
                krs->current_state = SEND_TRAINING;
                krs->remote_rx_ready = FALSE;
                krs->local_rx_ready = FALSE;
            }
        }

        // KR_LPCVALID
        if ((kr_sts.irq.vector & KR_LPCVALID) && krs->training_started) {
            mesa_port_kr_frame_t frm;
            frm.type = MESA_COEFFICIENT_UPDATE_FRM;
            (void)mesa_port_kr_train_frm_get(NULL, iport, &frm);
            //  Update Serdes
//            frm.data = coef2status(iport, frm.data);
            if (API_TEST) {
                frm.data = coef2status_api(iport, frm.data);
            } else {
                frm.data = coef2status(iport, frm.data);
            }
            // Send Status report
            frm.type = MESA_STATUS_REPORT_FRM;
            (void)mesa_port_kr_train_frm_set(NULL, iport, &frm);
        }

        // KR_LPSVALID
        if ((kr_sts.irq.vector & KR_LPSVALID) && krs->training_started) {
            if (krs->ignore_fail) {
                krs->ignore_fail = FALSE;
            }
            if (krs->ber_training_stage != LOCAL_RX_TRAINED) {
                perform_lp_training(iport, KR_LPSVALID);
            } else {
                kr_printf("       (KR_LPSVALID)Current state = TRAIN_REMOTE\n");
                if (krs->current_state != TRAIN_REMOTE) {
                    krs->tr_time_ld = get_time_ms(&krs->time_start);
                }
                krs->current_state = TRAIN_REMOTE;
            }

        }

        // KR_WT_DONE
        if (kr_sts.irq.vector & KR_WT_DONE) {
            if (krs->current_state ==  LINK_READY) {
                kr_printf("       (WT_DONE)STOP Training\n");
                krs->current_state = SEND_DATA;
                krs->training_started = FALSE;
                req_msg.stop_training = TRUE;
                req_msg.tr_done = TRUE;
                (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);
                krs->signal_detect = TRUE;
                printf("Port:%d - Training completed (in %d ms)\n",iport+1, get_time_ms(&krs->time_start));
            }
        }

        // KR_BER_BUSY_1
        if (kr_sts.irq.vector & KR_BER_BUSY_1) {
            perform_lp_training(iport, KR_BER_BUSY_1);
        }

        // KR_BER_BUSY_0
        if (kr_sts.irq.vector & KR_BER_BUSY_0) {
            perform_lp_training(iport, KR_BER_BUSY_0);
        }

        // KR_DME_VIOL_1
        if ((kr_sts.irq.vector & KR_DME_VIOL_1) && krs->training_started && (krs->current_state != LINK_READY)) {
            perform_lp_training(iport, KR_DME_VIOL_1);
            printf("p:%d KR_DME_VIOL_1 - stopping\n",iport);
            kr_mw_done = TRUE;
        }

        // KR_DME_VIOL_0
        if (kr_sts.irq.vector & KR_DME_VIOL_0 && krs->training_started && (krs->current_state != LINK_READY)) {
            printf("p:%d KR_DME_VIOL_0 - stopping\n",iport);
            // Do nothing
        }

        // KR_REM_RDY_1
        if (kr_sts.irq.vector & KR_REM_RDY_1) {
            krs->remote_rx_ready = TRUE;
        }

        // KR_REM_RDY_0
        if (kr_sts.irq.vector & KR_REM_RDY_0 && krs->training_started && (krs->current_state != LINK_READY)) {
            krs->remote_rx_ready = FALSE;
            printf("p:%d KR_REM_RDY_0 - stopping\n",iport);
        }

        // KR_MW_DONE
        if ((kr_sts.irq.vector & KR_MW_DONE) && krs->training_started) {
            printf("       (MW_DONE)MAX Wait done - Failure\n");
            req_msg.training_failure = TRUE;
            (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);
            printf("p:%d KR_MW_DONE - stopping\n",iport);
            kr_mw_done = TRUE;
        }

        // WT_START
        if (krs->current_state == TRAIN_REMOTE && krs->remote_rx_ready) {

            kr_printf("       (REMOTE_READY) Send 3 Rx_Ready status reports and WT_START\n");
            send_sts_report(iport, BT(15));
            send_sts_report(iport, BT(15));
            send_sts_report(iport, BT(15));
            send_sts_report(iport, 0); // needed to avoid KR_REM_RDY_1 during next training restart

            req_msg.wt_start = TRUE;
            (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);
            krs->current_state = LINK_READY;
        }

        // KR_AN_GOOD
        if (kr_sts.irq.vector & KR_AN_GOOD) {
            if (pconf.speed < MESA_SPEED_5G) {
                req_msg.aneg_disable = TRUE;
                (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);
                continue;

            }
        }

        // KR_RATE_DET
        if (kr_sts.irq.vector & KR_RATE_DET) {
            // Parallel detect speed change
            pconf.speed = kr_parallel_spd(iport, &kr);
            pconf.if_type = pconf.speed > MESA_SPEED_2500M ? MESA_PORT_INTERFACE_SFI : MESA_PORT_INTERFACE_SERDES;
            req_msg.gen0_tmr_start = 1;
            (void)mesa_port_conf_set(NULL, iport, &pconf);
            req_msg.rate_done = 1;
            (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);

        }

        // KR_AN_RATE
        if ((kr_sts.irq.vector & KR_AN_RATE) > 0) {
            // Aneg speed change request
            pconf.speed = kr_irq2spd(kr_sts.irq.vector & 0xf);
            pconf.if_type = pconf.speed > MESA_SPEED_2500M ? MESA_PORT_INTERFACE_SFI : MESA_PORT_INTERFACE_SERDES;
            (void)mesa_port_conf_set(NULL, iport, &pconf);
            req_msg.rate_done = 1;
            (void)mesa_port_kr_fw_req(NULL, iport, &req_msg);
        }
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
        "Port KR debug",
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
        "hist: dum the training history",
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
