// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "cli.h"
#include "kr.h"
#include <sys/time.h>
#include <unistd.h>

typedef uint32_t u32;
typedef uint16_t u16;

extern meba_inst_t meba_global_inst;
kr_appl_conf_t *kr_conf_state;

// For debug
uint32_t deb_dump_irq = 0;
mesa_bool_t kr_debug = 0;
mesa_bool_t BASE_KR_V2 = 0;
mesa_bool_t BASE_KR_V3 = 0;

void kr_printf(const char *fmt, ...)
{
    if (!kr_debug) {
        return;
    }
    va_list ap;
    char local_buf[1024];

    va_start(ap, fmt);
    vsnprintf(local_buf, 1024, fmt, ap);
    va_end(ap);
    printf("%s",local_buf);
}

static char *ber2txt(mesa_ber_stage_t st)
{
    switch (st) {
    case MESA_BER_GO_TO_MIN:        return "GO_TO_MIN";
    case MESA_BER_CALCULATE_BER:    return "CALCULATE_BER";
    case MESA_BER_MOVE_TO_MID_MARK: return "MOVE_TO_MID_MARK";
    case MESA_BER_LOCAL_RX_TRAINED: return "LOCAL_RX_TRAINED";
    default:                        return "ILLEGAL";
    }
}

static char *irq2txt(u32 irq)
{
    switch (irq) {
    case MESA_KR_ACTV:       return  "KR_ACTV";
    case MESA_KR_LPSVALID:   return  "KR_LPS";
    case MESA_KR_LPCVALID:   return  "KR_LPC";
    case MESA_KR_WT_DONE:    return  "WT_DONE";
    case MESA_KR_MW_DONE:    return  "MW_DONE";
    case MESA_KR_BER_BUSY_0: return  "BER_BUSY0";
    case MESA_KR_BER_BUSY_1: return  "BER_BUSY1";
    case MESA_KR_REM_RDY_0:  return  "REM_RDY0";
    case MESA_KR_REM_RDY_1:  return  "REM_RDY1";
    case MESA_KR_FRLOCK_0:   return  "FRLOCK0";
    case MESA_KR_FRLOCK_1:   return  "FRLOCK1";
    case MESA_KR_DME_VIOL_0: return  "DME_VIOL0";
    case MESA_KR_DME_VIOL_1: return  "DME_VIOL1";
    case MESA_KR_AN_XMIT_DISABLE: return  "AN_XM_DIS";
    case MESA_KR_TRAIN:      return  "TRAIN";
    case MESA_KR_RATE_DET:   return  "RATE_DET";
    case MESA_KR_CMPL_ACK:   return  "CMPL_ACK";
    case MESA_KR_AN_GOOD:    return  "AN_GOOD";
    case MESA_KR_LINK_FAIL:  return  "LINK_FAIL";
    case MESA_KR_ABD_FAIL:   return  "ABD_FAIL";
    case MESA_KR_ACK_FAIL:   return  "ACK_FAIL";
    case MESA_KR_NP_FAIL:    return  "NP_FAIL";
    case MESA_KR_NP_RX:      return  "NP_RX";
    case MESA_KR_INCP_LINK:  return  "INCP_LINK";
    case MESA_KR_GEN0_DONE:  return  "GEN0_DONE";
    case MESA_KR_GEN1_DONE:  return  "GEN1_DONE";
    case 0:  return "-";
    default:  return "ILLEGAL";
    }
}

static char *kr_util_action2txt(uint32_t act)
{
    switch (act) {
    case 0:  return "HOLD ";
    case 1:  return "INCR ";
    case 2:  return "DECR ";
    default: return "? ";
    }
}

static void raw_coef2txt(u32 frm_in, char *tap_out, char *action_out)
{
    u32 action = 0;

    if (frm_in == 0xdead) {
        sprintf(tap_out, "-       ");
        sprintf(action_out, "-  ");
        return;
    }

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
        action_out += sprintf(action_out, kr_util_action2txt(action));
    }
    if ((frm_in & 0xc) > 0) {
        tap_out += sprintf(tap_out, "C0 ");
        action = (frm_in >> 2) & 3;
        action_out += sprintf(action_out, kr_util_action2txt(action));
    }
    if ((frm_in & 0x30) > 0 ) {
        tap_out += sprintf(tap_out, "CP1 ");
        action = (frm_in >> 4) & 3;
        action_out += sprintf(action_out, kr_util_action2txt(action));
    }
    if ((frm_in & 0x3f) == 0 ) {
        tap_out += sprintf(tap_out, "ANY ");
        action = 0;
        action_out += sprintf(action_out, kr_util_action2txt(action));
    }
}

static char *kr_util_sts_action2txt(uint32_t act)
{
    switch (act) {
    case 0:  return "NOT_UPD ";
    case 1:  return "UPD ";
    case 2:  return "MIN ";
    case 3:  return "MAX ";
    default: return "? ";
    }
}

static void raw_sts2txt(u32 frm_in, char *tap_out, char *action_out)
{
    u32 action = 0;

    if (frm_in == 0xdead) {
        sprintf(tap_out, "-  ");
        sprintf(action_out, "-  ");
        return;
    }

    if (BT(15) & frm_in) {
        sprintf(tap_out, "RX READY ");
    }
    if ((frm_in & 0x3) > 0) {
        tap_out += sprintf(tap_out, "CM1 ");
        action = frm_in & 0x3;
        action_out += sprintf(action_out, kr_util_sts_action2txt(action));
    }
    if ((frm_in & 0xc) > 0) {
        tap_out += sprintf(tap_out, "C0 ");
        action = (frm_in >> 2) & 3;
        action_out += sprintf(action_out, kr_util_sts_action2txt(action));
    }
    if ((frm_in & 0x30) > 0 ) {
        tap_out += sprintf(tap_out, "CP1 ");
        action = (frm_in >> 4) & 3;
        action_out += sprintf(action_out, kr_util_sts_action2txt(action));
    }
    if ((frm_in & 0x3f) == 0 ) {
        tap_out += sprintf(tap_out, "ANY ");
        action = 0;
        action_out += sprintf(action_out, kr_util_sts_action2txt(action));
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
}

static char *kr_aneg_sm_2_txt(u32 reg)
{
    switch (reg) {
    case 0:  return "AN_ENABLE";
    case 1:  return "XMI_DISABLE";
    case 2:  return "ABILITY_DET";
    case 3:  return "ACK_DET";
    case 4:  return "COMPLETE_ACK";
    case 5:  return "TRAIN";
    case 6:  return "AN_GOOD_CHK";
    case 7:  return "AN_GOOD";
    case 8:  return "RATE_DET";
    case 11: return "LINK_STAT_CHK";
    case 12: return "PARLL_DET_FAULT";
    case 13: return "WAIT_RATE_DONE";
    case 14: return "NXTPG_WAIT";
    default: return "?";
    }
}

static void time_start(struct timeval *store)
{
    (void)gettimeofday(store, NULL);
}

static u32 get_time_us(struct timeval *store)
{
    struct timeval stop;
    (void)gettimeofday(&stop, NULL);
    return ((stop.tv_sec - store->tv_sec) * 1000000 + stop.tv_usec - store->tv_usec);
}

static u32 get_time_ms(struct timeval *store)
{
    struct timeval stop;
    (void)gettimeofday(&stop, NULL);
    return ((stop.tv_sec - store->tv_sec) * 1000000 + stop.tv_usec - store->tv_usec)/1000;
}

static u32 get_time_sec(struct timeval *store)
{
    struct timeval stop;
    (void)gettimeofday(&stop, NULL);
    return ((stop.tv_sec - store->tv_sec) * 1000000 + stop.tv_usec - store->tv_usec)/1000000;
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
    mesa_bool_t no_rem;
    mesa_bool_t no_pd;
    mesa_bool_t no_eq_apply;
    mesa_bool_t printout;
    mesa_bool_t fec;
    mesa_bool_t rsfec;
    mesa_bool_t adv25g;
    mesa_bool_t adv10g;
    mesa_bool_t adv5g;
    mesa_bool_t adv2g5;
    mesa_bool_t adv1g;
    mesa_bool_t np;
    uint32_t    value;
    mesa_bool_t dis;
    mesa_bool_t eq;
    mesa_bool_t ber;
    mesa_bool_t clr;
    mesa_bool_t irq;
    mesa_bool_t ansm;
    mesa_bool_t use_ber;
    mesa_bool_t stop;
    mesa_bool_t test;
    mesa_bool_t ctle;
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
    } else if (!strncasecmp(found, "rfec", 3)) {
        mreq->fec = 1;
    } else if (!strncasecmp(found, "rsfec", 5)) {
        mreq->rsfec = 1;
    } else if (!strncasecmp(found, "train", 5)) {
        mreq->train = 1;
    } else if (!strncasecmp(found, "no-remote", 4)) {
        mreq->no_rem = 1;
    } else if (!strncasecmp(found, "no-pd", 4)) {
        mreq->no_pd = 1;
    } else if (!strncasecmp(found, "no-eq-apply", 4)) {
        mreq->no_eq_apply = 1;
    } else if (!strncasecmp(found, "printout", 4)) {
        mreq->printout = 1;
    } else if (!strncasecmp(found, "all", 3)) {
        mreq->all = 1;
    } else if (!strncasecmp(found, "disable", 3)) {
        mreq->dis = 1;
    } else if (!strncasecmp(found, "eq", 2)) {
        mreq->eq = 1;
    } else if (!strncasecmp(found, "ber", 2)) {
        mreq->ber = 1;
    } else if (!strncasecmp(found, "clr", 3)) {
        mreq->clr = 1;
    } else if (!strncasecmp(found, "irq", 3)) {
        mreq->irq = 1;
    } else if (!strncasecmp(found, "sm", 2)) {
        mreq->ansm = 1;
    } else if (!strncasecmp(found, "use-ber", 4)) {
        mreq->use_ber = 1;
    } else if (!strncasecmp(found, "np", 2)) {
        mreq->np = 1;
    } else if (!strncasecmp(found, "stop", 4)) {
        mreq->stop = 1;
    } else if (!strncasecmp(found, "test", 4)) {
        mreq->test = 1;
    } else if (!strncasecmp(found, "ctl", 3)) {
        mreq->ctle = 1;

    } else
        cli_printf("no match: %s\n", found);

    return 0;
}

static void fa_kr_reset_state(u32 p) {
    kr_appl_train_t *krs = &kr_conf_state[p].tr;
    memset(krs, 0, sizeof(kr_appl_train_t));
}

static void cli_cmd_port_kr_fec(cli_req_t *req)
{
    mesa_port_no_t        uport, iport;
    port_cli_req_t        *mreq = req->module_req;
    mesa_port_kr_fec_t    conf = {0};


    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 || !kr_conf_state[iport].cap_10g) {
            continue;
        }

        conf.r_fec = mreq->fec;
        conf.rs_fec = mreq->rsfec;

        if (conf.rs_fec && !kr_conf_state[iport].cap_25g) {
            printf("RS-FEC only supported on 25G ports\n");
            return;
        }

        if (mesa_port_kr_fec_set(NULL, iport, &conf) != MESA_RC_OK) {
            cli_printf("Failure during port_kr_fec_set\n");
        }

        if (conf.r_fec) {
            printf("Enabled R-FEC\n");
        }
        if (conf.rs_fec) {
            printf("Enabled RS-FEC\n");
        }
        if (!conf.rs_fec && !conf.r_fec) {
            printf("Disabled FEC\n");
        }
    }

}

static void cli_cmd_port_kr_ctle(cli_req_t *req)
{
    mesa_port_no_t        iport, uport;
    kr_appl_train_t       *kr;
    mesa_port_kr_eye_dim_t  eye, eye2;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 || !kr_conf_state[iport].cap_10g) {
            continue;
        }
        (void)mesa_port_kr_eye_get(NULL, iport, &eye);
        kr = &kr_conf_state[iport].tr;
        (void)time_start(&kr_conf_state[iport].tr.time_start_aneg); // Start timer
        if (mesa_port_kr_ctle_adjust(NULL, iport) != MESA_RC_OK) {
            cli_printf("Failure during port_kr_ctle_adjust\n");
        }
        (void)mesa_port_kr_eye_get(NULL, iport, &eye2);
        cli_printf("Port:%d - CTLE done (%d ms). Eye height before:%d after:%d\n",iport, get_time_ms(&kr->time_start_aneg), eye.height, eye2.height);
    }
}


static void cli_cmd_port_kr(cli_req_t *req)
{
    mesa_port_no_t        uport, iport;
    port_cli_req_t        *mreq = req->module_req;

    if (BASE_KR_V3) {
        mesa_port_kr_conf_t conf = {0};


        for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {

            uport = iport2uport(iport);
            if (req->port_list[uport] == 0 || !kr_conf_state[iport].cap_10g) {
                continue;
            }
            if (mesa_port_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK) {
                continue;
            }
            kr_conf_state[iport].link_break = 0;
            (void)fa_kr_reset_state(iport);
            if (req->set) {
                kr_conf_state[iport].compl_ack_done = FALSE;
                kr_conf_state[iport].stop_train = 0;
                kr_conf_state[iport].aneg_enable = 1;
                kr_conf_state[iport].pd = 1;
                mesa_port_kr_fec_t fec = {0};
                (void)mesa_port_kr_fec_set(NULL, iport, &fec);
                conf.aneg.enable = mreq->dis ? 0 : 1;
                conf.train.enable = mreq->train || mreq->all;
                conf.train.no_remote = mreq->no_rem;
                conf.train.no_eq_apply = kr_conf_state[iport].no_eq_apply;
                conf.train.test_mode = mreq->test;
                conf.train.test_repeat = 10;
                conf.train.use_ber_cnt = kr_conf_state[iport].use_ber;
                conf.aneg.adv_1g = mreq->adv1g || mreq->all;
                conf.aneg.adv_2g5 = mreq->adv2g5 || mreq->all;
                conf.aneg.adv_5g = mreq->adv5g || mreq->all;
                conf.aneg.adv_10g = mreq->adv10g || mreq->all;
                conf.aneg.no_pd = mreq->no_pd;

                if (kr_conf_state[iport].cap_25g) {
                    conf.aneg.adv_25g = mreq->adv25g || mreq->all;
                    conf.aneg.rs_fec_req = mreq->rsfec || mreq->all;
                    conf.aneg.r_fec_req = mreq->fec;
                } else {
                    conf.aneg.r_fec_req = mreq->fec || mreq->all;
                }

                if (!kr_conf_state[iport].cap_25g) {
                    if (mreq->adv25g) {
                        printf("adv25g not supported - ignoring\n");
                    }
                    if (mreq->rsfec) {
                        printf("rsfec (25g only) not supported - ignoring\n");
                    }
                }
                if (!mreq->dis) {
                    mesa_port_state_set(NULL, iport, FALSE);
                }

                conf.aneg.next_page = mreq->np;
                if (mesa_port_kr_conf_set(NULL, iport, &conf) != MESA_RC_OK) {
                    cli_printf("KR set failed for port %u\n", uport);
                }

                (void)time_start(&kr_conf_state[iport].tr.time_start_aneg); // Start the aneg timer
            } else {
                cli_printf("Port: %d\n", uport);
                cli_printf("  KR aneg: %s\n", conf.aneg.enable ? "Enabled" : "Disabled");
                cli_printf("  KR training: %s\n", conf.train.enable ? "Enabled" : "Disabled");
            }
        }
    } else if (BASE_KR_V2) {
        mesa_port_kr_conf_t conf = {0};
        for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
            uport = iport2uport(iport);
            if (req->port_list[uport] == 0) {
                continue;
            }
            if (req->set) {
                conf.aneg.enable = mreq->dis ? 0 : 1;
                kr_conf_state[iport].aneg_enable = conf.aneg.enable;
                conf.train.enable = mreq->train || mreq->all;
                conf.aneg.adv_10g = mreq->adv10g || mreq->all;
                conf.aneg.r_fec_req = mreq->fec || mreq->all;
                if (mesa_port_kr_conf_set(NULL, iport, &conf) != MESA_RC_OK) {
                    cli_printf("KR set failed for port %u\n", uport);
                }
                kr_conf_state[iport].mesa_kr_an_good = 0;
            }
        }
    }
}

static void cli_cmd_port_kr_debug(cli_req_t *req)
{
    port_cli_req_t        *mreq = req->module_req;
    mesa_port_no_t        uport, iport;
    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 || !kr_conf_state[iport].cap_10g) {
            continue;
        }
        if (mreq->irq) {
            if (mreq->all) {
                deb_dump_irq = 30;
                printf("all\n");
            } else if (mreq->dis) {
                deb_dump_irq = 0;
            } else {
                deb_dump_irq = 20;
            }
            printf("Port %d: IRQ %s debug %s\n",uport, deb_dump_irq > 16 ? "all" : "aneg", deb_dump_irq > 0 ? "enabled" : "disabled");
        }
        if (mreq->ansm) {
            if (kr_conf_state[iport].aneg_sm_deb) {
                kr_conf_state[iport].aneg_sm_deb = 0;
            } else {
                kr_conf_state[iport].aneg_sm_deb = 1;
            }
            printf("Port %d: Aneg State machine debug %s\n",uport, kr_conf_state[iport].aneg_sm_deb ? "enabled" : "disabled");
        }
        if (mreq->stop) {
            kr_conf_state[iport].global_stop = 1;
            kr_conf_state[iport].stop_train = kr_conf_state[iport].stop_train ? 0 : 1;
            printf("Port %d: Stop aneg (if link failure) %s\n",uport, kr_conf_state[iport].stop_train ? "enabled" : "disabled");
        }
        if (mreq->use_ber) {
            if (kr_conf_state[iport].use_ber) {
                kr_conf_state[iport].use_ber = 0;
            } else {
                kr_conf_state[iport].use_ber = 1;
            }
        }
        if (mreq->ctle) {
            if (kr_conf_state[iport].ctle) {
                kr_conf_state[iport].ctle = 0;
            } else {
                kr_conf_state[iport].ctle = 1;
            }
            printf("Port %d: ctle tuning %s\n",uport, kr_conf_state[iport].ctle ? "enabled" : "disabled");
        }
        if (mreq->no_eq_apply) {
            kr_conf_state[iport].no_eq_apply = !kr_conf_state[iport].no_eq_apply;
            printf("Port %d: no_eq_apply %s\n",uport, kr_conf_state[iport].no_eq_apply ? "enabled" : "disabled");
        }
        if (mreq->printout) {
            kr_debug = !kr_debug;
            printf("Debug dump %s\n",kr_debug ? "enabled" : "disabled");
        }
    }
}

static void cli_cmd_port_kr_poll_debug(cli_req_t *req)
{
    port_cli_req_t        *mreq = req->module_req;
    mesa_port_no_t        uport, iport;
    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 || !kr_conf_state[iport].cap_10g) {
            continue;
        }
        kr_conf_state[iport].conf_pollcnt = mreq->value;
        printf("Fast poll count set to %d\n",kr_conf_state[iport].conf_pollcnt);
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
    mesa_port_kr_status_t status;
    mesa_port_kr_conf_t conf;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }

        if (mesa_port_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK ||
            !conf.aneg.enable) {
            continue;
        }

        if (mesa_port_kr_status_get(NULL, iport, &status) != MESA_RC_OK) {
            cli_printf("Port:%d Could not read status\n",iport);
            continue;
        }

        cli_printf("Port %u\n", uport);
        cli_printf("LP aneg ability                 :%s\n", status.aneg.lp_aneg_able ? "Yes" : "No");
        cli_printf("Aneg active (running)           :%s\n", status.aneg.active ? "Yes" : "No");
        cli_printf("PCS block lock                  :%s\n", status.aneg.block_lock ? "Yes" : "No");
        cli_printf("Aneg complete                   :%s\n", status.aneg.complete ? "Yes" : "No");
        cli_printf("  Speed change req.             :%s\n", status.aneg.speed_req > 0 ? mesa_port_spd2txt(status.aneg.speed_req) : "No");
        cli_printf("  R-FEC (CL-74)                 :%s\n", status.fec.r_fec_enable ? "Yes" : "No");

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

        cli_printf("FEC                             :%s\n", status.fec.r_fec_enable ? "Enabled" : "Disabled");
        if (status.fec.r_fec_enable) {
            cli_printf("  Corrected block count         :%d\n", status.fec.corrected_block_cnt);
            cli_printf("  Un-corrected block count      :%d\n", status.fec.uncorrected_block_cnt);
        }
    }
}

static void kr_dump_tr_eq_history(cli_req_t *req)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    kr_appl_train_t              *krs;
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

        krs = &kr_conf_state[iport].tr;
        if (kr_conf_state[iport].tr.ld_hist_index == 0) {
            continue;
        }
        first = TRUE;
        cli_printf("\nPort %d:\n",uport);
        for (uint16_t indx = 0; indx < kr_conf_state[iport].tr.ld_hist_index; indx++) {
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
                cli_printf("%-4s%-12s%-12s%-12s%-12s%-12s%-15s%-8s\n","","TAP","CMD","CM1","Ampl","CP1","Status","Time (ms)");
                cli_printf("    ----------------------------------------------------------------------\n");
                first = FALSE;
            }
            if (!mreq->all && (krs->ld_hist[indx].res.coef == 0)) {
                continue; // Skip the HOLD cmd
            }
            cli_printf("%-4d%-12s%-12s%-12d%-12d%-12d%-15s%-8d\n", indx, coef_tap, coef_act, cm1, c0, cp1, sts_res, dt);
        }
    }
}

static void kr_dump_tr_ber_history(cli_req_t *req)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    kr_appl_train_t              *krs;
    uint32_t                dt;
    mesa_bool_t             first = TRUE;
    char                    buf[200] = {0}, *b;
    char                    sts_tmp[20] = {0};
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

        krs = &kr_conf_state[iport].tr;
        if (kr_conf_state[iport].tr.lp_hist_index == 0) {
            continue;
        }
        first = TRUE;
        cli_printf("\nPort %d:\n",uport);
        for (uint16_t indx = 0; indx < kr_conf_state[iport].tr.lp_hist_index; indx++) {
            char coef_tap[20] = {0};
            char coef_act[20] = {0};
            (void)raw_coef2txt(krs->lp_hist[indx].ber_coef_frm, coef_tap, coef_act);
            char sts_tap[20] = {0};
            char sts_res[20] = {0};
            (void)raw_sts2txt(krs->lp_hist[indx].ber_status_frm, sts_tap, sts_res);

            if (krs->lp_hist[indx].ber_status_frm == 0 || krs->lp_hist[indx].ber_status_frm == 0xdead) {
            } else
                memcpy(sts_tmp, sts_tap, sizeof(sts_tap));

            dt = krs->lp_hist[indx].time;
            if (first) {
                cli_printf("%-8s%-12s%-12s%-12s%-20s%-8s%-20s\n","","RxTAP","RxLPS","TxLPC","BER state","ms","IRQs");
                cli_printf("  --------------------------------------------------------------------------\n");
                first = FALSE;
            }
            if (!mreq->all && (krs->lp_hist[indx].ber_coef_frm == 0)) {
                continue; // Skip the HOLD cmd
            }
            b = &buf[0];
            for (uint32_t i = 4; i < 31; i++) {
                if ((1 << i) & krs->lp_hist[indx].irq) {
                    b += sprintf(b, "%s ", irq2txt(1 << i));
                }
            }
            if ((krs->irq_hist[indx].irq & 0xf) > 0) {
                sprintf(b, "%s ",fa_kr_aneg_rate(krs->irq_hist[indx].irq & 0xf));
            }

            cli_printf("%-8d%-12s%-12s%-12s%-20s%-8d%-20s\n", indx, sts_tmp, sts_res, coef_act, ber2txt(krs->lp_hist[indx].ber_training_stage), dt, buf);
        }
    }
}

static void kr_dump_irq_history(cli_req_t *req, mesa_bool_t all)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    kr_appl_train_t         *krs;
    uint32_t                dt = 0, delta = 0;
    mesa_bool_t             first = TRUE;
    char                    buf[200] = {0}, *b;
    char                    buf2[200] = {0}, *b2;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0) {
            continue;
        }
        if (mesa_port_kr_conf_get(NULL, iport, &kr) != MESA_RC_OK ||
            !kr.aneg.enable) {
            continue;
        }

        krs = &kr_conf_state[iport].tr;

        if (kr_conf_state[iport].tr.irq_hist_index == 0) {
            continue;
        }
        first = TRUE;

        cli_printf("\nPort %d:\n",uport);
        for (uint16_t indx = 0; indx < kr_conf_state[iport].tr.irq_hist_index; indx++) {
            if (krs->irq_hist[indx].time < dt) {
                delta = krs->irq_hist[indx].time;
            } else {
                delta = krs->irq_hist[indx].time - dt;
            }
            dt = krs->irq_hist[indx].time;
            if (first) {
                cli_printf("%-4s%-10s%-10s%-30s%-22s%-16s%-16s\n","","us","delta","KR IRQs","SM","LP BP ability","LP NP ability");
                cli_printf("    -------------------------------------------------------------------------------------------------------\n");
                first = FALSE;
            }
            memset(buf, 0, sizeof(buf));
            b = &buf[0];
            for (uint32_t i = 4; i < 31; i++) {
                if ((1 << i) & krs->irq_hist[indx].irq) {
                    b += sprintf(b, "%s ", irq2txt(1 << i));
                }
            }
            if ((krs->irq_hist[indx].irq & 0xf) > 0) {
                sprintf(b, "%s ",fa_kr_aneg_rate(krs->irq_hist[indx].irq & 0xf));
            } else if ((krs->irq_hist[indx].irq == 0)) {
                sprintf(b, "-");
            }
            buf2[0] = '\0';
            if (krs->irq_hist[indx].irq & MESA_KR_CMPL_ACK || krs->irq_hist[indx].irq & MESA_KR_NP_RX) {
                b2 = &buf2[0];
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp1 & BT(5) ? "1G/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp2 & BT(0) ? "2G5/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp2 & BT(1) ? "5G/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp1 & BT(7) ? "10G/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp1 & BT(14) ? "25S/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp1 & BT(15) ? "25KR/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp0 & BT(10) ? "FC_ASYM/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp0 & BT(11) ? "FC_SYM/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp0 & BT(13) ? "RF/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp2 & BT(14) ? "FECA/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp2 & BT(15) ? "FECR/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp2 & BT(13) ? "RFEC/" : "");
                b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_bp2 & BT(12) ? "RSFEC" : "");
                b2 += sprintf(b2, "  ");
                if ((krs->irq_hist[indx].lp_np0 & 0x3) == 0x3) { // code for ablilities
                    b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_np1 & BT(5) ? "25KR/" : "");
                    b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_np1 & BT(6) ? "25CR/" : "");
                    b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_np2 & BT(8) ? "F1/" : "");
                    b2 += sprintf(b2, "%s",krs->irq_hist[indx].lp_np2 & BT(9) ? "F2" : "");
                } else {
                    b2 += sprintf(b2, "-");
                }
            }

            if (krs->irq_hist[indx].irq & MESA_KR_AN_GOOD) {
                b2 = &buf2[0];
                mesa_port_kr_status_t sts;
                mesa_port_kr_status_get(NULL, iport, &sts);
                b2 += sprintf(b2, "Aneg results: %s / %s",mesa_port_spd2txt(krs->speed),krs->rfec ? "RFEC" : krs->rsfec ? "RSFEC" : "No FEC");
            }

            cli_printf("%-4d%-10d%-10d%-30s%-22s%-32s\n",
                       indx, dt, delta, buf, kr_aneg_sm_2_txt(krs->irq_hist[indx].sm), buf2);

        }

    }
}

static void cli_cmd_port_kr_status(cli_req_t *req)
{
    mesa_port_no_t          uport, iport;
    mesa_port_kr_conf_t     kr;
    mesa_port_kr_status_t   sts;
    port_cli_req_t          *mreq = req->module_req;
    mesa_port_kr_state_t    kr_state, *krs = &kr_state;
    kr_appl_train_t         *appl;
    mesa_port_kr_eye_dim_t  eye;
    mesa_port_ctle_t        ctle;

    if (BASE_KR_V2) {
        cli_cmd_port_kr_v2_status(req);
        return;
    }

    if (mreq->clr) {
        for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
            uport = iport2uport(iport);
            if (req->port_list[uport] == 0) {
                continue;
            }
            kr_conf_state[iport].tr.irq_glb_hist_index = 0;
            kr_conf_state[iport].tr.lp_hist_index = 0;
            kr_conf_state[iport].tr.ld_hist_index = 0;
            kr_conf_state[iport].tr.irq_hist_index = 0;
        }
        return;
    }

    if (mreq->eq) {
        kr_dump_tr_eq_history(req);
        return;
    }

    if (mreq->ber) {
        kr_dump_tr_ber_history(req);
        return;
    }

    if (mreq->irq) {
        kr_dump_irq_history(req, mreq->all);
        return;
    }

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        uport = iport2uport(iport);
        if (req->port_list[uport] == 0 || !kr_conf_state[iport].cap_10g) {
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
        // Get the internal training state
        if (mesa_port_kr_state_get(NULL, iport, krs) != MESA_RC_OK) {
            cli_printf("Failure during port_kr_state_get\n");
        }

        appl = &kr_conf_state[iport].tr;
        cli_printf("Port %d\n",uport);
        cli_printf("  ANEG completed    : %s\n",sts.aneg.complete ? "Yes" : "No");
        cli_printf("  Speed             : %s\n",mesa_port_spd2txt(sts.aneg.speed_req));
        cli_printf("  R-FEC (CL-74)     : %s\n",sts.fec.r_fec_enable ? "Enabled":"Disabled");
        cli_printf("  RS-FEC (CL-108)   : %s\n",sts.fec.rs_fec_enable ? "Enabled":"Disabled");
        cli_printf("  Time since start  : %d sec\n",get_time_sec(&appl->time_start_aneg));
        if (!kr.train.enable) {
            cli_printf("  Training          : Disabled\n");
        } else {
            cli_printf("\n  Training Results:\n");
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

            cli_printf("\n\n  This port Tx Equalizer settings:\n");
            cli_printf("  LD CM (tap_dly)   : %d\n",sts.train.cm_ob_tap_result);
            cli_printf("  LD C0 (amplitude) : %d\n",sts.train.c0_ob_tap_result);
            cli_printf("  LD CP (tap_adv)   : %d\n",sts.train.cp_ob_tap_result);

            (void)mesa_port_kr_ctle_get(NULL, iport, &ctle);
            cli_printf("\n  This port Rx CTLE settings:\n");
            cli_printf("  LD VGA            : %d\n",ctle.vga);
            cli_printf("  LD EDC            : %d\n",ctle.edc);
            cli_printf("  LD EQR            : %d\n",ctle.eqr);

            cli_printf("\n  FEC Corr./Uncor.  : %d/%d\n", sts.fec.corrected_block_cnt, sts.fec.uncorrected_block_cnt);
            (void)mesa_port_kr_eye_get(NULL, iport, &eye);
            cli_printf("\n  Current eye height: %d\n",eye.height);
            cli_printf("  Training time     : %d ms\n",appl->time_ld);
            cli_printf("  Training status   : %s\n",sts.train.complete ? "OK" : "Failed");
        }
    }
}

static mesa_port_speed_t kr_parallel_spd(mesa_port_no_t iport, mesa_port_kr_conf_t *conf)
{
    if (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_25G) {
        kr_conf_state[iport].next_parallel_spd = MESA_SPEED_10G;
        return MESA_SPEED_25G;
    } else if (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_10G) {
        kr_conf_state[iport].next_parallel_spd = MESA_SPEED_5G;
        return MESA_SPEED_10G;
    } else if (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_5G) {
        kr_conf_state[iport].next_parallel_spd = MESA_SPEED_2500M;
        return MESA_SPEED_5G;
    } else if (kr_conf_state[iport].next_parallel_spd == MESA_SPEED_2500M) {
        kr_conf_state[iport].next_parallel_spd = MESA_SPEED_1G;
        return MESA_SPEED_2500M;
    } else  {
        if (kr_conf_state[iport].cap_25g) {
            kr_conf_state[iport].next_parallel_spd = MESA_SPEED_25G;
        } else {
            kr_conf_state[iport].next_parallel_spd = MESA_SPEED_10G;
        }
        return MESA_SPEED_1G;
    }
}


static void kr_add_to_irq_history(mesa_port_no_t p, uint32_t irq, mesa_port_kr_status_t *status)
{
    kr_appl_train_t *krs = &kr_conf_state[p].tr;


    if (krs->irq_hist_index == KR_HIST_NUM) {
        krs->irq_hist_index = 0;
    }
    if (krs->irq_glb_hist_index == KR_HIST_NUM) {
        krs->irq_glb_hist_index = 0;
    }

    if (krs->irq_hist_index < KR_HIST_NUM) {
        krs->irq_hist[krs->irq_hist_index].time = get_time_us(&krs->time_start_aneg);
        krs->irq_hist[krs->irq_hist_index].irq = irq;
        krs->irq_hist[krs->irq_hist_index].sm = status->aneg.sm;
        krs->irq_hist[krs->irq_hist_index].lp_bp0 = status->aneg.lp_bp0;
        krs->irq_hist[krs->irq_hist_index].lp_bp1 = status->aneg.lp_bp1;
        krs->irq_hist[krs->irq_hist_index].lp_bp2 = status->aneg.lp_bp2;
        krs->irq_hist[krs->irq_hist_index].lp_np0 = status->aneg.lp_np0;
        krs->irq_hist[krs->irq_hist_index].lp_np1 = status->aneg.lp_np1;
        krs->irq_hist[krs->irq_hist_index].lp_np2 = status->aneg.lp_np2;
        krs->irq_hist_index++;
    }
    krs = &kr_conf_state[0].tr;
    if (krs->irq_glb_hist_index < KR_HIST_NUM) {
        krs->irq_glb_hist[krs->irq_glb_hist_index].time = get_time_us(&krs->time_start_aneg);
        krs->irq_glb_hist[krs->irq_glb_hist_index].irq = irq;
        krs->irq_glb_hist[krs->irq_glb_hist_index].sm = status->aneg.sm;
        krs->irq_glb_hist[krs->irq_glb_hist_index].port = p;
        krs->irq_glb_hist_index++;
    }
}

static void kr_add_to_eq_history(mesa_port_no_t p, mesa_kr_status_results_t res)
{
    kr_appl_train_t *krs = &kr_conf_state[p].tr;

    if (krs->ld_hist_index == KR_HIST_NUM) {
        krs->ld_hist_index = 0;
    }

    if (krs->ld_hist_index < KR_HIST_NUM) {
        krs->ld_hist[krs->ld_hist_index].time = get_time_ms(&krs->time_start_train);
        krs->ld_hist[krs->ld_hist_index].res = res;
        krs->ld_hist_index++;
    }
}

static void kr_add_to_ber_history(mesa_port_no_t p, uint32_t irq)
{
    kr_appl_train_t *kr = &kr_conf_state[p].tr;
    mesa_port_kr_state_t *krs = &kr_conf_state[p].tr.state;

    if (kr->lp_hist_index == KR_HIST_NUM) {
        kr->lp_hist_index = 0;
    }

    if (kr->lp_hist_index < KR_HIST_NUM) {
        kr->lp_hist[kr->lp_hist_index].time = get_time_ms(&kr->time_start_train);
        if (irq & MESA_KR_LPSVALID) {
            kr->lp_hist[kr->lp_hist_index].ber_coef_frm = krs->ber_coef_frm;
            kr->lp_hist[kr->lp_hist_index].ber_status_frm = krs->ber_status_frm;
        } else if ((irq & MESA_KR_TRAIN) || (irq & MESA_KR_BER_BUSY_0)) {
            kr->lp_hist[kr->lp_hist_index].ber_coef_frm = krs->ber_coef_frm;
            kr->lp_hist[kr->lp_hist_index].ber_status_frm = 0xdead;
        }
        kr->lp_hist[kr->lp_hist_index].ber_training_stage = krs->ber_training_stage;
        kr->lp_hist[kr->lp_hist_index].irq = irq;
        kr->lp_hist_index++;
    }
}

static mesa_port_speed_t kr_irq2spd(uint32_t irq)
{
    switch (irq) {
    case MESA_KR_ANEG_RATE_25G_S: return MESA_SPEED_25G;
    case MESA_KR_ANEG_RATE_25G: return MESA_SPEED_25G;
    case MESA_KR_ANEG_RATE_10G: return MESA_SPEED_10G;
    case MESA_KR_ANEG_RATE_5G:  return MESA_SPEED_5G;
    case MESA_KR_ANEG_RATE_2G5: return MESA_SPEED_2500M;
    case MESA_KR_ANEG_RATE_1G:  return MESA_SPEED_1G;
    default:
        cli_printf("KR speed not supported\n");
    }
    return MESA_SPEED_10G;
}

static void dump_irq(u32 p, u32 irq, u32 time, u32 irqs)
{
    char buf[200] = {0}, *b=&buf[0];
    mesa_bool_t dump = 0;
    uint32_t irq_indx = deb_dump_irq > irqs ? deb_dump_irq : irqs;

    if (irq_indx) {
        b += sprintf(b, "Port %d (IRQ): ",p);
        for (uint32_t i = 4; i <= irq_indx; i++) {
            if (((1 << i) & irq) > 0) {
                b += sprintf(b, "%s ",irq2txt((1 << i)));
                dump = 1;
            }
        }
        if ((irq & 0xf) > 0) {
            b += sprintf(b, "%s ",fa_kr_aneg_rate(irq & 0xf));
        }
    }
    if (dump) {
        printf("%s (%d ms)\n",buf,time);
    }
}

static void kr_poll_v3(meba_inst_t inst, mesa_port_no_t iport)
{
    mesa_port_no_t        uport;
    mesa_port_kr_conf_t   kr_conf;
    mesa_port_conf_t      pconf;
    mesa_port_kr_state_t  *krs;
    uint32_t              irq;
    kr_appl_train_t       *kr;
    mesa_port_kr_status_t status;
    mesa_port_kr_fec_t fec = {0};

    if (mesa_port_kr_conf_get(NULL, iport, &kr_conf) != MESA_RC_OK || !kr_conf.aneg.enable) {
        return;
    }

    // For debugging..
    if (kr_conf_state[iport].global_stop && kr_conf_state[iport].link_break) {
        return;
    }

    uport = iport2uport(iport);
    kr = &kr_conf_state[iport].tr;
    krs = &kr->state;
    // Poll the IRQs
    if (mesa_port_kr_irq_get(NULL, iport, &irq) != MESA_RC_OK) {
        printf("-->Failure during mesa_port_kr_irq_get\n");
    }

    if (mesa_port_kr_status_get(NULL, iport, &status) != MESA_RC_OK) {
        printf("-->Failure during port_kr_status_get\n");
    }

    if (irq == 0) {
        if (kr_conf_state[iport].aneg_sm_state != status.aneg.sm) {
            kr_add_to_irq_history(iport, irq, &status);
            kr_conf_state[iport].aneg_sm_state = status.aneg.sm;
        }
        return;
    }

    if ((irq & MESA_KR_AN_XMIT_DISABLE) || (irq & MESA_KR_LINK_FAIL)) {
        mesa_port_state_set(NULL, iport, FALSE);
    }

    kr_conf_state[iport].aneg_sm_state = status.aneg.sm;

    // Add IRQs to history
    kr_add_to_irq_history(iport, irq, &status);

    // Start the aneg timer if AN_XMIT_DISABLE IRQ
    if ((irq & MESA_KR_AN_XMIT_DISABLE)) {
        kr_conf_state[iport].compl_ack_done = FALSE;
        kr_conf_state[iport].pollcnt = kr_conf_state[iport].conf_pollcnt;
        (void)time_start(&kr->time_start_aneg);
    }

    if ((irq & MESA_KR_LINK_FAIL || irq & MESA_KR_AN_XMIT_DISABLE) && kr_conf_state[iport].mesa_kr_an_good) {
        kr_conf_state[iport].link_break = 1;
        kr_conf_state[iport].mesa_kr_an_good = 0;
        printf("Port:%d - %s %d ms after TRAIN start\n",uport,
               irq & MESA_KR_LINK_FAIL ? "LINK_FAIL" : "AN_XMIT_DIS", get_time_ms(&kr->time_start_train));
    }

    if (irq & MESA_KR_CMPL_ACK) {
        kr_conf_state[iport].compl_ack_done = TRUE;
    }

    // Dump IRQs if debug is enabled
    dump_irq(uport, irq, get_time_us(&kr->time_start_aneg), 0);

    if (mesa_port_conf_get(NULL, iport, &pconf) != MESA_RC_OK) {
        printf("Failure during port_conf_get\n");
    }

    // KR_AN_RATE (Change to the speed/FEC requested)
    if ((irq & MESA_KR_AN_RATE) > 0) {
        if (mesa_port_kr_status_get(NULL, iport, &status) != MESA_RC_OK) {
            printf("Failure during port_kr_status_get\n");
        }
        if (pconf.speed != kr_irq2spd(irq & 0xf)) {
            pconf.speed = kr_irq2spd(irq & 0xf);
            // Aneg speed change request
            pconf.if_type = pconf.speed > MESA_SPEED_2500M ? MESA_PORT_INTERFACE_SFI : MESA_PORT_INTERFACE_SERDES;
            kr_printf("Port:%d - Aneg speed is %s (%d ms) - Set\n",uport, mesa_port_spd2txt(pconf.speed), get_time_ms(&kr->time_start_aneg));
            (void)mesa_port_conf_set(NULL, iport, &pconf);
        }
        kr_printf("Port:%d - Aneg speed is %s (%d ms) - Done\n",uport, mesa_port_spd2txt(pconf.speed), get_time_ms(&kr->time_start_aneg));
        // Aneg FEC change request
        if (status.aneg.request_fec_change) {
            fec.r_fec = status.aneg.r_fec_enable;
            fec.rs_fec = status.aneg.rs_fec_enable;
            if (mesa_port_kr_fec_set(NULL, iport, &fec) != MESA_RC_OK) {
                cli_printf("Failure during port_kr_fec_set\n");
            }
        }

        if (kr_conf_state[iport].compl_ack_done) {
            kr_printf("Aneg is complete.  Now start training (if enabled).\n");
        } else {
            kr_printf("Now complete Aneg.\n");
        }
    }

    // KR_RATE_DET (Link partner does not have Aneg support)
    if (irq & MESA_KR_RATE_DET) {
        // Parallel detect speed change
        pconf.speed = kr_parallel_spd(iport, &kr_conf);
        pconf.if_type = pconf.speed > MESA_SPEED_2500M ? MESA_PORT_INTERFACE_SFI : MESA_PORT_INTERFACE_SERDES;
        (void)mesa_port_conf_set(NULL, iport, &pconf);
        kr_printf("Port:%d - Parallel detect speed is %s (%d ms) - Done\n",uport, mesa_port_spd2txt(pconf.speed), get_time_ms(&kr->time_start_aneg));
    }

    // Apply the IRQs
    if (mesa_port_kr_irq_apply(NULL, iport, &irq) != MESA_RC_OK) {
        printf("Failure during port_kr_irq_apply\n");
    }

    if ((irq & MESA_KR_TRAIN)) {
        (void)time_start(&kr->time_start_train);
        if (kr_conf_state[iport].ctle) {
            // Adjust CTLE Rx setings (MESA-693) - before training
            if (mesa_port_kr_ctle_adjust(NULL, iport) != MESA_RC_OK) {
                cli_printf("Failure during port_kr_ctle_adjust\n");
            }
        }
    }

    // Get the internal training state for debug purposes
    if (mesa_port_kr_state_get(NULL, iport, krs) != MESA_RC_OK) {
        printf("Failure during port_kr_state_get\n");
    }

    // Dump failure IRQs for debug purposes
    if (irq & MESA_KR_DME_VIOL_1 || irq & MESA_KR_FRLOCK_0) {
        if (kr_debug) {
            dump_irq(uport, irq, get_time_ms(&kr->time_start_aneg), 31);
        }
    }

    // Add training state to history
    if (irq & MESA_KR_LPSVALID || irq & MESA_KR_TRAIN || irq & MESA_KR_BER_BUSY_0) {
        kr_add_to_ber_history(iport, irq);
    }

    // Add equalizer state to history
    if ((irq & MESA_KR_LPCVALID) && krs->training_started) {
        kr_add_to_eq_history(iport, krs->tr_res);
    }

    // Training completed
    if (irq & MESA_KR_WT_DONE && (krs->current_state == MESA_TR_SEND_DATA)) {
        kr->time_ld = get_time_ms(&kr->time_start_train);
        kr_printf("Port:%d - Training completed (%d ms)\n",uport, get_time_ms(&kr->time_start_train));
    }

    // Aneg completed
    if (irq & MESA_KR_AN_GOOD) {
        mesa_port_state_set(NULL, iport, TRUE);
        if (krs->current_state == MESA_TR_SEND_DATA) {
            mesa_port_kr_eye_dim_t  eye;
            (void)mesa_port_kr_eye_get(NULL, iport, &eye);
            printf("Port:%d - Training (eye:%d) and Aneg (%s) completed in %d ms\n",uport, eye.height, mesa_port_spd2txt(pconf.speed), get_time_ms(&kr->time_start_aneg));
            kr_conf_state[iport].mesa_kr_an_good = 1;
            kr->speed = pconf.speed;
            kr->rfec = status.aneg.r_fec_enable;
            kr->rsfec = status.aneg.rs_fec_enable;
        } else {
            printf("Port:%d - Aneg completed (%s) in %d ms\n",uport, mesa_port_spd2txt(pconf.speed), get_time_ms(&kr->time_start_aneg));
        }
        kr_conf_state[iport].next_parallel_spd = MESA_SPEED_2500M;
    }
}

static void kr_poll_v2(meba_inst_t inst, mesa_port_no_t iport)
{
    mesa_port_kr_status_t status;
    mesa_port_kr_conf_t conf;

    if ((mesa_port_kr_conf_get(NULL, iport, &conf) != MESA_RC_OK) ||
        !conf.aneg.enable) {
        return;
    }
    // 10G KR surveilance
    (void)(mesa_port_kr_status_get(NULL, iport, &status));
    if (!kr_conf_state[iport].mesa_kr_an_good && status.aneg.complete) {
        printf("Port:%d - Aneg completed, %s\n",iport2uport(iport), status.train.complete ? "Training completed" : "without training");
    }
    kr_conf_state[iport].mesa_kr_an_good = status.aneg.complete;

}


static void kr_poll(meba_inst_t inst)
{
    mesa_port_no_t iport;
    mesa_port_conf_t pconf;
    uint16_t meba_cnt = inst->api.meba_capability(inst, MEBA_CAP_BOARD_PORT_COUNT);

    if (BASE_KR_V3) {
        for (iport = 0; iport < meba_cnt; iport++) {
            if (!kr_conf_state[iport].aneg_enable) {
                continue;
            }
            if (mesa_port_conf_get(NULL, iport, &pconf) == MESA_RC_OK && pconf.power_down) {
                continue;
            }
            if (kr_conf_state[iport].pollcnt == 0) {
                kr_conf_state[iport].pollcnt = 1;
            }
            while (kr_conf_state[iport].pollcnt > 0) { // When the training starts then the IRQs comes fast
                kr_poll_v3(inst, iport);
                kr_conf_state[iport].pollcnt--;
            }
        }
    } else if (BASE_KR_V2) {
        for (iport = 0; iport < meba_cnt; iport++) {
            if (!kr_conf_state[iport].aneg_enable) {
                continue;
            }
            kr_poll_v2(inst, iport);
        }
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Port KR aneg [<port_list>] [all] [adv-1g] [adv-2g5] [adv-5g] [adv-10g] [adv-25g] [np] [rfec] [rsfec] [train] [no-remote] [no-pd] [test] [disable]",
        "Set or show kr",
        cli_cmd_port_kr
    },
    {
        "Port KR status [<port_list>] [eq] [ber] [irq] [all] [clr]",
        "Show status",
        cli_cmd_port_kr_status
    },
    {
        "Port KR debug [<port_list>] [stop] [irq] [sm] [use-ber] [all] [disable] [ctl] [no-eq-apply] [printout]",
        "Toggle debug",
        cli_cmd_port_kr_debug
    },
    {
        "Port KR fec [<port_list>] [rfec] [rsfec]",
        "Toggle fec",
        cli_cmd_port_kr_fec
    },
    {
        "Port KR ctle [<port_list>]",
        "Adjust ctle",
        cli_cmd_port_kr_ctle
    },

    {
        "Port KR poll [<port_list>] <poll_cnt>",
        "Set the KR poll count",
        cli_cmd_port_kr_poll_debug
    },
};

static int cli_parm_poll_count(cli_req_t *req)
{

    port_cli_req_t *mreq = req->module_req;
    return cli_parm_u32(req, &mreq->value, 0, 0xFFFF);
}

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
        "rfec",
        "rfec: advertise r-fec capability",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "rsfec",
        "rs-fec: advertise rs-fec capability",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "np",
        "np: use next page for advertise",
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
        "no-remote",
        "no-remote: Do not train remote partner",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "no-eq-apply",
        "no-eq-apply: Do not apply EQ settings to local HW",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "printout",
        "printout: Dump live debug msg",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "test",
        "test: train in test mode",
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
        "eq",
        "eq: dump the equalizer history",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "ber",
        "eq: dump the BER history",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },

    {
        "clr",
        "clr: clear history",
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
        "sm",
        "sm: print out AN state machine",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "stop",
        "stop: stop aneg/training",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "use-ber",
        "use-ber: Use BER measurement instead of eye-height",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "ctl",
        "ctle: Toggle CTLE usage as a part of training",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },


    {
        "pr",
        "print out",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "no-pd",
        "Disable parallel detect",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },

    {
        "<poll_cnt>",
        "Value to be written to register (0-0xffff)",
        CLI_PARM_FLAG_SET,
        cli_parm_poll_count
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
    meba_port_entry_t     meba = {0};

    // Free old port table
    if (kr_conf_state != NULL) {
        free(kr_conf_state);
    }
    /* Store the meba inst globally */
    meba_global_inst = inst;

    // Initialize ports
    if ((kr_conf_state = calloc(port_cnt, sizeof(*kr_conf_state))) == NULL) {
        T_E("port_table calloc() failed");
        return;
    }

    for (port_no = 0; port_no < port_cnt; port_no++) {

        kr_conf_state[port_no].conf_pollcnt = 1;

        if (MEBA_WRAP(meba_port_entry_get, inst, port_no, &meba) != MESA_RC_OK) {
            continue;
        }

        kr_conf_state[port_no].cap_25g = (meba.cap & MEBA_PORT_CAP_25G_FDX) > 0 ? 1 : 0;
        kr_conf_state[port_no].cap_10g = (meba.cap & MEBA_PORT_CAP_10G_FDX) > 0 ? 1 : 0;
        kr_conf_state[port_no].next_parallel_spd = MESA_SPEED_2500M;
        kr_conf_state[port_no].ctle = 1;
    }
}

void mscc_appl_kr_init(mscc_appl_init_t *init)
{

    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        if (mesa_capability(NULL, MESA_CAP_PORT_KR_IRQ)) {
            BASE_KR_V3 = 1;
        } else if (mesa_capability(NULL, MESA_CAP_PORT_KR)) {
            BASE_KR_V2 = 1;
        }

        kr_init(init->board_inst);
        kr_cli_init();
        break;

    case MSCC_INIT_CMD_INIT_WARM:
        kr_init(init->board_inst);
        break;

      case MSCC_INIT_CMD_POLL_FAST:
        if (BASE_KR_V2) {
            kr_poll(init->board_inst);
        }
        break;

    case MSCC_INIT_CMD_POLL_FASTEST:
        if (BASE_KR_V3) {
            kr_poll(init->board_inst);
        }
        break;

    default:
        break;
    }
}
