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

#ifndef _MSCC_APPL_PORT_H_
#define _MSCC_APPL_PORT_H_

#include "mscc/ethernet/switch/api.h"
#include "trace.h"

#define BER_THRESHOLD      (10)
#define KR_AN_RATE         (0xF)



#define KR_ACTV            (1 << 29)
#define KR_LPSVALID        (1 << 28)
#define KR_LPCVALID        (1 << 27)
#define KR_WT_DONE         (1 << 26)
#define KR_MW_DONE         (1 << 25)
#define KR_BER_BUSY_0      (1 << 24)
#define KR_BER_BUSY_1      (1 << 23)
#define KR_REM_RDY_0       (1 << 22)
#define KR_REM_RDY_1       (1 << 21)
#define KR_FRLOCK_0        (1 << 20)
#define KR_FRLOCK_1        (1 << 19)
#define KR_DME_VIOL_0      (1 << 18)
#define KR_DME_VIOL_1      (1 << 17)
#define KR_AN_XMIT_DISABLE (1 << 16)
#define KR_TRAIN           (1 << 15)
#define KR_RATE_DET        (1 << 14)
#define KR_CMPL_ACK        (1 << 13)
#define KR_AN_GOOD         (1 << 12)
#define KR_LINK_FAIL       (1 << 11)
#define KR_ABD_FAIL        (1 << 10)
#define KR_ACK_FAIL        (1 << 9)
#define KR_NP_FAIL         (1 << 8)
#define KR_NP_RX           (1 << 7)
#define KR_INCP_LINK       (1 << 6)
#define KR_GEN0_DONE       (1 << 5)
#define KR_GEN1_DONE       (1 << 4)

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define BT(x) (1 << (x))
#define VTSS_BITMASK(x)               ((1 << (x)) - 1)
#define BITFIELD(x,o,w)  (((x) >> (o)) & VTSS_BITMASK(w))

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


typedef enum {
    INITILIZE,
    SEND_TRAINING,
    TRAIN_LOCAL,
    TRAIN_REMOTE,
    SEND_DATA,
    TRAINING_FAILURE,
    LINK_READY
} train_state_t;

typedef enum {
    GO_TO_MIN,
    CALCULATE_BER,
    MOVE_TO_MID_MARK,
    LOCAL_RX_TRAINED
} ber_stage_t;

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

typedef enum {
    CM1,
    C0,
    CP1,
} kr_tap_t;

typedef struct {
    mesa_port_kr_status_results_t res;
    kr_coefficient_t coef;
    uint32_t time;
} kr_coef_t;

typedef struct {
    train_state_t current_state;
    ber_stage_t ber_training_stage;
    mesa_bool_t signal_detect;
    mesa_bool_t training_started;
    mesa_bool_t remote_rx_ready;
    mesa_bool_t local_rx_ready;
    mesa_bool_t dme_viol_handled;
    mesa_bool_t dme_viol;
    mesa_bool_t ber_busy;
    mesa_bool_t ber_busy_sw;
    mesa_bool_t tap_max_reached;
    mesa_bool_t receiver_ready_sent;
    mesa_bool_t kr_mw_done;
    mesa_bool_t ignore_fail;
    mesa_port_speed_t next_parallel_spd;
    kr_tap_t current_tap;
    uint32_t  tap_idx;
    uint16_t  ber_cnt[3][64];
    uint32_t  frm_sent;
    uint16_t  eye_height[3][64];
    uint16_t  decr_cnt;
    uint16_t  lp_tap_max_cnt[3];
    uint16_t  lp_tap_end_cnt[3];
    uint16_t  ld_tap_max_cnt[3];
    uint16_t  ld_tap_end_cnt[3];
    uint16_t  ld_org_tap_val[3];
    uint32_t  tr_time_ld;
    uint32_t  tr_time_rd;
    struct timeval time_start;
    mesa_port_kr_status_t status;
    kr_coef_t coef_hist[200];
    uint16_t hist_index;
} kr_train_t;

typedef struct {
    mesa_port_speed_t next_parallel_spd;
    mesa_bool_t cap_25g;
    mesa_bool_t show_irq;
} kr_conf_t;


typedef struct {
    
} kr_aneg_t;


#endif /* _MSCC_APPL_PORT_H_ */
