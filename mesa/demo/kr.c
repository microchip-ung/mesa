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
#include <sys/time.h>

typedef uint32_t u32;
typedef uint16_t u16;

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


#define BER_THRESHOLD      (10)

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
} ber_stage_t;


typedef enum {
    CM1,
    C0,
    CP1,
} kr_tap_t;

typedef struct {
    train_state_t current_state;
    ber_stage_t ber_training_stage;
    mesa_bool_t training_started;
    mesa_bool_t remote_rx_ready;
    mesa_bool_t local_rx_ready;
    mesa_bool_t dme_viol_handled;
    mesa_bool_t dme_viol;
    mesa_bool_t ber_busy;
    mesa_bool_t tap_max_reached;
    mesa_port_speed_t next_parallel_spd;
    kr_tap_t current_tap;
    uint32_t  tap_idx;
    mesa_port_10g_kr_status_t status;
    uint16_t  ber_cnt[64];
    uint16_t  decr_cnt;
} kr_train_t;

typedef enum {
    HOLD = 0,
    INCR = 1,
    DECR = 2,
    INIT = 0x1000,
    PRESET = 0x2000
} kr_coefficient_t;

typedef enum {
    NOT_UPDATED = 0,
    UPDATED = 1,
    MINIMUM = 2,
    MAXIMUM = 3,
} kr_status_report_t;

kr_train_t kr_tr_state[100] = {0};

uint32_t my_cnt = 0;
uint32_t my_limit = 1000;
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
            conf.train.enable = mreq->train || mreq->all;
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


void kr_printf(const char *fmt, ...)
{

    va_list ap;
    char local_buf[1024];

    if (my_cnt > my_limit) {
        return;
    }
    my_cnt++;

    va_start(ap, fmt);
    vsnprintf(local_buf, 1024, fmt, ap);
    va_end(ap);

    printf("%s",local_buf);
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
#define VTSS_BITMASK(x)               ((1 << (x)) - 1)
#define BITFIELD(x,o,w)  (((x) >> (o)) & VTSS_BITMASK(w))

//VTSS_EXTRACT_BITFIELD(x,5,1)


char *coef2txt(uint32_t vector)
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
    case INITILIZE:     return "INITILIZE";
    case SEND_TRAINING: return "SEND_TRAINING";
    case TRAIN_LOCAL:   return "TRAIN_LOCAL";
    case SEND_DATA:     return "SEND_DATA";
    default:            return "ILLEGAL";
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

char *sts2txt(kr_status_report_t vector)
{
    switch (vector) {
    case MAXIMUM: return "MAXIMUM";
    case MINIMUM: return "MINIMUM";
    case UPDATED:  return "UPDATED";
    case NOT_UPDATED:  return "NOT_UPDATED";
    default:  return "ILLEGAL";
    }
}

void print_irq_vector(uint32_t p, uint32_t vector)
{
    struct timeval tv;
    int            s;

    if (vector == 0) {
        return;
    }
    if (my_cnt > my_limit) {
        return;
    }
    (void)gettimeofday(&tv, NULL);
    s = (tv.tv_sec % 60);

    printf("Port:%d (%02u:%03lu)\n",p+1,s,tv.tv_usec/1000);
    printf("       IRQ:");
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

u32 coef_now[3];
u32 coef_max = 10;
u32 coef_min = 0;

kr_status_report_t coef2status(mesa_port_no_t p, kr_coefficient_t data)
{
    kr_coefficient_t coef = data;
    kr_status_report_t status = 0;
    kr_tap_t tap = 0;

    if ((data & INIT) == 0) {
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
    kr_printf("       RX COEF FRM: %s\n",coef2txt(coef));

    if (coef == INIT) {
        coef_now[CM1] = coef_max / 2;
        coef_now[CP1] = coef_max / 2;
        coef_now[C0]  = coef_max / 2;
        status = UPDATED;
    } else if (coef == HOLD) {
        status = NOT_UPDATED;
    } else if (coef == INCR) {
        if (coef_now[tap] < coef_max) {
            coef_now[tap]++;
            status = UPDATED;
        } else {
            status = MAXIMUM;
        }
    } else if (coef == DECR) {
        if (coef_now[tap] > coef_min) {
            coef_now[tap]--;
            status = UPDATED;
        } else {
            status = MINIMUM;
        }
    } else  {
        kr_printf("Error in coef\n");
    }

    kr_printf("       TX STS FRM: %s\n",sts2txt(status));

    if (tap == CP1) {
        status = status << 4;
    } else if (tap == C0) {
        status = status << 2;
    }

    return status;
}

uint16_t update_coef(kr_coefficient_t ld, kr_tap_t tap)
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
        printf("Illegal prm\n");
        break;
    }
    return 0;
}

kr_status_report_t kr_status_report(uint16_t data, kr_tap_t tap)
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
        printf("Illegal prm\n");
        break;
    }
    return 0;
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

void analyze_ber(uint16_t *ber, uint16_t *high_mark, uint16_t *low_mark)
{
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

    *high_mark = coef_max;
    *low_mark = coef_min;
}

kr_tap_t next_tap(kr_tap_t tap)
{
    switch (tap) {
    case CM1: return C0;
    case C0:  return CP1;
    case CP1: return 0;
    }
    return 0;
}

void send_coef_update(mesa_port_no_t p, kr_coefficient_t coef, kr_tap_t tap)
{
    mesa_port_10g_kr_frame_t frm;
    kr_printf("       TX COEF FRM: %s\n",coef2txt(coef));
    frm.data = update_coef(coef, tap);
    frm.type = MESA_COEFFICIENT_UPDATE_FRM;
    (void)mesa_port_10g_kr_train_frm_set(NULL, p, &frm);
}

/* void send_status_report(mesa_port_no_t p, kr_status_report_t rep, kr_tap_t tap) */
/* { */
/*     mesa_port_10g_kr_frame_t frm; */
/*     frm.data = update_report(rep, tap); */
/*     frm.type = MESA_STATUS_REPORT_FRM; */
/*     (void)mesa_port_10g_kr_train_frm_set(NULL, p, &frm);     */
/* } */

void perform_lp_training(mesa_port_no_t p, uint32_t irq)
{
    mesa_port_10g_kr_frame_t frm;
    kr_train_t *krs = &kr_tr_state[p];
    kr_status_report_t lp_status = 0;
    mesa_port_10g_kr_fw_req_t req_msg = {0};

    kr_printf("       TAP:%s BER:%s STATE:%s\n",tap2txt(krs->current_tap),
              ber2txt(krs->ber_training_stage), state2txt(krs->current_state));

    if (irq == KR_TRAIN) {
        send_coef_update(p, INIT, krs->current_tap);
        krs->ber_training_stage = GO_TO_MIN;
        krs->current_tap = CM1;
        return;
    }

    if (irq == KR_LPSVALID) {
       frm.type = MESA_STATUS_REPORT_FRM;
       (void)mesa_port_10g_kr_train_frm_get(NULL, p, &frm);
       lp_status = kr_status_report(frm.data, krs->current_tap);
       kr_printf("       RX STS FRM: %s\n", sts2txt(lp_status));
    }

    switch (krs->ber_training_stage) {
    case GO_TO_MIN:
        if (irq == KR_LPSVALID) {
            if (lp_status == UPDATED) {
                send_coef_update(p, HOLD, krs->current_tap);
                if (krs->dme_viol_handled) {
                    req_msg.ber_enable = TRUE;
                    (void)mesa_port_10g_kr_fw_req(NULL, p, &req_msg);
                    krs->ber_training_stage = CALCULATE_BER;
                    krs->tap_idx = 0;
                    krs->dme_viol = 0;
                    krs->dme_viol_handled = FALSE;
                }
            } else if (lp_status == NOT_UPDATED) {
                if (krs->dme_viol) {
                    send_coef_update(p, INCR, krs->current_tap);
                    krs->dme_viol_handled = TRUE;
                } else {
                    send_coef_update(p, DECR, krs->current_tap);
                }
            } else if (lp_status == MINIMUM) {
                send_coef_update(p, HOLD, krs->current_tap);
                req_msg.ber_enable = TRUE;
                (void)mesa_port_10g_kr_fw_req(NULL, p, &req_msg);
                krs->ber_training_stage = CALCULATE_BER;
                krs->tap_idx = 0;
                krs->tap_max_reached = FALSE;
            } else {
                kr_printf("Error Got lp_status:%d\n",lp_status);
            }

        } else {
            kr_printf("Perform_lp_traing valled with irq:%d when in stage GO_TO_MIN\n",irq);
        }
        return;
    case CALCULATE_BER:
        if (irq == KR_BER_BUSY_1) {
            krs->ber_busy = TRUE;
        } else if ((irq == KR_BER_BUSY_0) && (krs->ber_busy)) {
            krs->ber_busy = FALSE;
            krs->ber_cnt[krs->tap_idx] = krs->status.train.frame_errors;
            if (krs->tap_max_reached) {
                u16 high_mark = 0;
                u16 low_mark = 0;
                analyze_ber(krs->ber_cnt, &high_mark, &low_mark);
                u16 mid_mark = high_mark - ((high_mark - low_mark) / 2);
                krs->decr_cnt = krs->tap_idx - mid_mark;
                send_coef_update(p, DECR, krs->current_tap);
                krs->ber_training_stage = MOVE_TO_MID_MARK;
            } else {
                send_coef_update(p, INCR, krs->current_tap);
            }
        } else if (irq == KR_LPSVALID) {
            if (!krs->ber_busy) {
                if (lp_status == NOT_UPDATED) {
                    if (krs->dme_viol) {
                        send_coef_update(p, DECR, krs->current_tap);
                        krs->dme_viol_handled = TRUE;
                    } else {
                        send_coef_update(p, INCR, krs->current_tap);
                    }
                } else if (lp_status == UPDATED || lp_status == MAXIMUM) {
                    send_coef_update(p, HOLD, krs->current_tap);
                    req_msg.ber_enable = TRUE;
                    (void)mesa_port_10g_kr_fw_req(NULL, p, &req_msg);

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
                send_coef_update(p, HOLD, krs->current_tap);
                krs->decr_cnt--;
                if (krs->decr_cnt == 0) {
                    if (krs->current_tap == CP1) {
                        krs->ber_training_stage = LOCAL_RX_TRAINED;
                    } else {
                        krs->current_tap = next_tap(krs->current_tap);
                        krs->ber_training_stage = GO_TO_MIN;
                    }
                } else if (lp_status == NOT_UPDATED) {
                    send_coef_update(p, DECR, krs->current_tap);
                }
            } else if (lp_status == NOT_UPDATED) {
                send_coef_update(p, DECR, krs->current_tap);
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


void kr_poll(meba_inst_t inst)
{
    mesa_port_no_t        iport;
    mesa_port_10g_kr_status_t kr_sts;
    mesa_port_10g_kr_conf_t kr;
    mesa_port_conf_t        pconf;
    uint16_t meba_cnt = MEBA_WRAP(meba_capability, inst, MEBA_CAP_BOARD_PORT_COUNT);
    mesa_port_10g_kr_fw_req_t req_msg = {0};
    kr_train_t *krs;



    for (iport = 0; iport < meba_cnt; iport++) {
        if (mesa_port_10g_kr_conf_get(NULL, iport, &kr) != MESA_RC_OK ||
            !kr.aneg.enable) {
            continue;
        }

        if ((mesa_port_10g_kr_status_get(NULL, iport, &kr_sts) != MESA_RC_OK)
            || (kr_sts.irq.vector == 0)) {
            return;
        }
        krs = &kr_tr_state[iport];
        krs->status = kr_sts;
        (void)mesa_port_conf_get(NULL, iport, &pconf);

        (void)print_irq_vector(iport, kr_sts.irq.vector);

        // #2 TX Send Coef INIT
        if (kr_sts.irq.vector & BT(KR_TRAIN)) {
            krs->current_state = SEND_TRAINING;
            krs->training_started = TRUE;
            krs->remote_rx_ready = FALSE;
            krs->local_rx_ready = FALSE;
            req_msg.start_training = TRUE;
            (void)mesa_port_10g_kr_fw_req(NULL, iport, &req_msg);
            kr_printf("       perform_lp_training(KR_TRAIN)\n");
            (void)perform_lp_training(iport, KR_TRAIN);
        }

        // Training frame lock attained. Change state to TRAIN_LOCAL
        if ((kr_sts.irq.vector & BT(KR_FRLOCK_1)) && krs->training_started) {
            if (krs->current_state == SEND_TRAINING) {
                krs->current_state = TRAIN_LOCAL;
            }
        }

        // Training frame lock is lost during training
        if ((kr_sts.irq.vector & BT(KR_FRLOCK_0)) && krs->training_started) {
            if ((krs->current_state == TRAIN_LOCAL) || (krs->current_state == TRAIN_REMOTE)) {
                krs->current_state = SEND_TRAINING;
                krs->remote_rx_ready = FALSE;
                krs->local_rx_ready = FALSE;
            }
        }

        // KR_LPCVALID
        if ((kr_sts.irq.vector & BT(KR_LPCVALID)) && krs->training_started) {
            if (iport != 0) {
                mesa_port_10g_kr_frame_t frm;
                frm.type = MESA_COEFFICIENT_UPDATE_FRM;
                (void)mesa_port_10g_kr_train_frm_get(NULL, iport, &frm);

                //  Update Serdes
                frm.data = coef2status(iport, frm.data);

                // Send Status report
                frm.type = MESA_STATUS_REPORT_FRM;
                (void)mesa_port_10g_kr_train_frm_set(NULL, iport, &frm);
            }

        }

        // KR_LPSVALID
        if ((kr_sts.irq.vector & BT(KR_LPSVALID)) && krs->training_started) {
            if (krs->ber_training_stage != LOCAL_RX_TRAINED) {
                kr_printf("       perform_lp_training(KR_LPSVALID)\n");
                perform_lp_training(iport, KR_LPSVALID);
            } else {
                printf("current_state=TRAIN_REMOTE\n");
                krs->current_state = TRAIN_REMOTE;
            }
        }

        // KR_BER_BUSY_1
        if (kr_sts.irq.vector & BT(KR_BER_BUSY_1)) {
            kr_printf("       perform_lp_training(KR_BER_BUSY_1)\n");
            perform_lp_training(iport, KR_BER_BUSY_1);
        }

        // KR_BER_BUSY_0
        if (kr_sts.irq.vector & BT(KR_BER_BUSY_0)) {
            kr_printf("       perform_lp_training(KR_BER_BUSY_0)\n");
            perform_lp_training(iport, KR_BER_BUSY_0);
        }

        // KR_DME_VIOL_1
        if (kr_sts.irq.vector & BT(KR_DME_VIOL_1)) {
            kr_printf("       perform_lp_training(KR_DME_VIOL_1)\n");
            perform_lp_training(iport, KR_DME_VIOL_1);

        }

        // KR_DME_VIOL_0
        if (kr_sts.irq.vector & BT(KR_DME_VIOL_0)) {
            // Do nothing
        }

        // KR_REM_RDY_1
        if (kr_sts.irq.vector & BT(KR_REM_RDY_1)) {
            krs->remote_rx_ready = TRUE;
        }

        // KR_REM_RDY_0
        if (kr_sts.irq.vector & BT(KR_REM_RDY_0)) {
            krs->remote_rx_ready = FALSE;
        }

        // KR_WT_DONE
        if (kr_sts.irq.vector & BT(KR_WT_DONE)) {
            // TBD
        }

        // KR_MW_DONE
        if (kr_sts.irq.vector & BT(KR_MW_DONE)) {
            req_msg.training_failure = TRUE;
            (void)mesa_port_10g_kr_fw_req(NULL, iport, &req_msg);
        }

        // WT_START
        if (krs->current_state == TRAIN_REMOTE && krs->remote_rx_ready) {
            req_msg.wt_start = TRUE;
            (void)mesa_port_10g_kr_fw_req(NULL, iport, &req_msg);
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
