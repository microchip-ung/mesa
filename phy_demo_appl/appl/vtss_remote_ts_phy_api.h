/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#ifndef _REMOTE_TS_PHY_H_
#define _REMOTE_TS_PHY_H_

/* Error codes (vtss_rc) */
#define VTSS_PHY_TS_REMOTE_PHY_API_STATUS_VTSS_RC_OK         0
#define VTSS_PHY_TS_REMOTE_PHY_API_STATUS_VTSS_RC_ERROR      1
#define VTSS_PHY_TS_REMOTE_PHY_API_STATUS_VTSS_RC_INV_STATE  2
#define VTSS_PHY_TS_REMOTE_PHY_API_STATUS_VTSS_RC_INCOMPLETE 3


/* Message types */
#define REMOTE_TS_PHY_MESSAGE_TYPE_REQUEST             0
#define REMOTE_TS_PHY_MESSAGE_TYPE_REPLY               1
#define REMOTE_TS_PHY_MESSAGE_TYPE_EVENT               2
#define REMOTE_TS_PHY_MESSAGE_TYPE_CNT                 3 /* Number of message types */

/* Instance specific commands */
#define REMOTE_TS_PHY_COMMAND_MODE_SET                 0
#define REMOTE_TS_PHY_COMMAND_MODE_GET                 1
#define REMOTE_TS_PHY_COMMAND_DELAY_METHOD_SET         2
#define REMOTE_TS_PHY_COMMAND_DELAY_METHOD_GET         3
#define REMOTE_TS_PHY_COMMAND_INGRESS_LATENCY_SET      4
#define REMOTE_TS_PHY_COMMAND_INGRESS_LATENCY_GET      5
#define REMOTE_TS_PHY_COMMAND_EGRESS_LATENCY_SET       6
#define REMOTE_TS_PHY_COMMAND_EGRESS_LATENCY_GET       7
#define REMOTE_TS_PHY_COMMAND_DELAY_ASYMMETRY_SET      8
#define REMOTE_TS_PHY_COMMAND_DELAY_ASYMMETRY_GET      9
#define REMOTE_TS_PHY_COMMAND_PATH_DELAY_SET          10
#define REMOTE_TS_PHY_COMMAND_PATH_DELAY_GET          11
#define REMOTE_TS_PHY_COMMAND_SIGNATURE_MASK_SET      12
#define REMOTE_TS_PHY_COMMAND_SIGNATURE_MASK_GET      13
#define REMOTE_TS_PHY_COMMAND_TS_FIFO_EMPTY           14
#define REMOTE_TS_PHY_COMMAND_TX_TIMESTAMP_GET        15
#define REMOTE_TS_PHY_COMMAND_TX_TIMESTAMP_SPI        16
#define REMOTE_TS_PHY_COMMAND_TX_TIMESTAMP_INDICATION 17

/* Global commands (no instance) */
#define REMOTE_TS_PHY_COMMAND_NS_TO_TIMESTAMP_GET     18
#define REMOTE_TS_PHY_COMMAND_PTP_TIME_SET            19
#define REMOTE_TS_PHY_COMMAND_PTP_TIME_SET_DONE       20
#define REMOTE_TS_PHY_COMMAND_PTP_TIME_ARM            21
#define REMOTE_TS_PHY_COMMAND_PTP_TIME_GET            22
#define REMOTE_TS_PHY_COMMAND_CLOCK_ADJUST_SET        23
#define REMOTE_TS_PHY_COMMAND_CLOCK_ADJUST_GET        24
#define REMOTE_TS_PHY_COMMAND_CLOCK_ADJUST_1NS        25

#define REMOTE_TS_PHY_COMMAND_INGR_ENG_INIT           26
#define REMOTE_TS_PHY_COMMAND_INGR_ENG_INIT_CONF_GET  27
#define REMOTE_TS_PHY_COMMAND_INGR_ENG_CLEAR          28

#define REMOTE_TS_PHY_COMMAND_EGR_ENG_INIT            29
#define REMOTE_TS_PHY_COMMAND_EGR_ENG_INIT_CONF_GET   30
#define REMOTE_TS_PHY_COMMAND_EGR_ENG_CLEAR           31

#define REMOTE_TS_PHY_COMMAND_INGR_ENG_CONF_SET       32
#define REMOTE_TS_PHY_COMMAND_INGR_ENG_CONF_GET       33

#define REMOTE_TS_PHY_COMMAND_EGR_ENG_CONF_SET        34
#define REMOTE_TS_PHY_COMMAND_EGR_ENG_CONF_GET        35

#define REMOTE_TS_PHY_COMMAND_INGR_ENG_ACTION_SET     36
#define REMOTE_TS_PHY_COMMAND_INGR_ENG_ACTION_GET     37

#define REMOTE_TS_PHY_COMMAND_EGR_ENG_ACTION_SET      38
#define REMOTE_TS_PHY_COMMAND_EGR_ENG_ACTION_GET      39

#define REMOTE_TS_PHY_COMMAND_EVENT_CONF_SET          40
#define REMOTE_TS_PHY_COMMAND_EVENT_CONF_GET          41
#define REMOTE_TS_PHY_COMMAND_EVENT_POLL              42

#define REMOTE_TS_PHY_COMMAND_STATS_GET               43

#define REMOTE_TS_PHY_COMMAND_CORR_OVERFLOW_GET       44

#define REMOTE_TS_PHY_COMMAND_INIT                    45
#define REMOTE_TS_PHY_COMMAND_PHY_MODE_CHANGE         46

#define REMOTE_TS_PHY_COMMAND_1588_CSR_READ           47
#define REMOTE_TS_PHY_COMMAND_1588_CSR_WRITE          48 

#define REMOTE_TS_PHY_COMMAND_EVENT                   49

#define REMOTE_TS_PHY_COMMAND_CNT                     50 /* Number of commands */

/* Status */
#define REMOTE_TS_PHY_STATUS_SUCCESS                   0
#define REMOTE_TS_PHY_STATUS_FAILURE                   1
#define REMOTE_TS_PHY_STATUS_NOT_READY                 2
#define REMOTE_TS_PHY_STATUS_CNT                       3 /* Number of status's */


/* Remote TS PHY header definition */
typedef struct {
    u8     version;
    u8     message_id;
    u8     command;
    u8     message_type;
    u16    length;
    u8     instance;
    u8     status;
    u16    port_no;
} __attribute__((packed)) remote_ts_msg_header_t;

/* Header Type for engine configuration */
typedef struct engine_init_s
{
    vtss_phy_ts_engine_t            eng_id;
    vtss_phy_ts_encap_t             encap_type;
    u8                              flow_st_index;
    u8                              flow_end_index;
    vtss_phy_ts_engine_flow_match_t flow_match_mode;
} __attribute__((packed)) engine_init_t;

/* Header Type used for event configuration */
typedef struct event_en_s {
    BOOL                enable;
    vtss_phy_ts_event_t ev_mask;
    vtss_phy_ts_event_t status;
} __attribute__((packed)) event_conf_t;

typedef struct ts_mode_s {
    BOOL                enable;
} __attribute__((packed))ts_mode_t;

/* Header Type used for correction overflow configuration */
typedef struct over_flow_s {
    BOOL ingr_overflow;
    BOOL egr_overflow;
} __attribute__((packed)) correction_overflow_t;

/* Header type used for CSR Register configuration */
typedef struct csr_reg_s{
    u32  blk_id;
    u16  csr_address;
    u32  value; 
} __attribute__((packed)) csr_reg_t;


/* Remote TS PHY port map */
typedef struct remote_ts_loc_map_s {
    BOOL   enable;
    vtss_port_no_t remote_port;
}remote_ts_phy_loc_map_t;

typedef enum remote_ts_phy_loc_s {
    REMOTE_TS_PHY_LOCATION_LOCAL,
    REMOTE_TS_PHY_LOCATION_REMOTE,
} remote_ts_phy_loc_t;

#define REMOTE_TS_PHY_REMOTE_LOC_CHANNEL 2

/* Functions for accessing semaphore functions */

#define remote_ts_phy_crit_enter() REMOTE_TS_PHY_crit_enter(__FUNCTION__, __LINE__)
#define remote_ts_phy_crit_exit() REMOTE_TS_PHY_crit_exit(__FUNCTION__, __LINE__)
#define remote_ts_phy_crit_assert_locked() REMOTE_TS_PHY_crit_assert_locked(__FUNCTION__, __LINE__)


void REMOTE_TS_PHY_crit_enter(const char * fn, int line);
void REMOTE_TS_PHY_crit_exit(const char *fn, int line);
void REMOTE_TS_PHY_crit_assert_locked(const char *fn, int line);

/* Function to send the packet */
vtss_rc remote_ts_phy_request_tx(u32 port, u32 instance, u32 command, const u8 *body);
#endif /* _REMOTE_TS_PHY_H_ */
// ***************************************************************************
//
//  End of file.
//
// ***************************************************************************
