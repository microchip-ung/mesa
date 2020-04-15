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

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>

#include <linux/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>

#include "mscc/ethernet/switch/api.h"
#include "mscc/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

static mscc_appl_trace_module_t trace_module = {
    .name = "test"
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

#define LOOP_PORT_INVALID  0xFFFFFFFF
static uint32_t loop_port=LOOP_PORT_INVALID;

typedef struct {
    uint32_t test_no;
} test_cli_req_t;

typedef struct {
    const char *descr;
    mesa_rc (* func)(void);
} test_entry_t;

#define MESA_RC(expr) {                                    \
    mesa_rc _rc = (expr);                                  \
    if (_rc != MESA_RC_OK) {                               \
        cli_printf("%d %s failed\n", __LINE__, #expr);     \
        return _rc;                                        \
    }                                                      \
}

// ACL example, discard UDP frames from switch port 2, unless SIP is 1.2.3.4
static mesa_rc test_acl(void)
{
    mesa_port_no_t        port_no = 2;
    mesa_ace_t            ace;
    mesa_ace_frame_ipv4_t *ipv4 = &ace.frame.ipv4;

    // Add ACE 1 allowing all IPv4 frames from switch port 2 with SIP 1.2.3.4
    MESA_RC(mesa_ace_init(NULL, MESA_ACE_TYPE_IPV4, &ace));
    ace.id = 1;
    mesa_port_list_set(&ace.port_list, port_no, 1);
    ipv4->sip.value = 0x01020304;
    ipv4->sip.mask = 0xffffffff;
    MESA_RC(mesa_ace_add(NULL, MESA_ACE_ID_LAST, &ace));

    // Add ACE 2 discarding all UDP frames from switch port 2
    MESA_RC(mesa_ace_init(NULL, MESA_ACE_TYPE_IPV4, &ace));
    ace.id = 2;
    mesa_port_list_set(&ace.port_list, port_no, 1);
    ipv4->proto.value = 17; // UDP protocol
    ipv4->proto.mask = 0xff;
    ace.action.port_action = MESA_ACL_PORT_ACTION_FILTER;
    MESA_RC(mesa_ace_add(NULL, MESA_ACE_ID_LAST, &ace));

    return MESA_RC_OK;
}

//typedef struct {
//    mesa_bool_t switch_frm;
//    uint64_t dst_port_mask;
//    uint32_t frm_len;
//    mesa_vlan_tag_t tag;
//    uint8_t aggr_code;
//    mesa_prio_t cos;
//    mesa_cosid_t cosid;
//    uint16_t vsi;
//    mesa_packet_tx_vstax_t tx_vstax_hdr;
//    mesa_packet_ptp_action_t ptp_action;
//    uint8_t ptp_id;
//    uint64_t ptp_timestamp;
//    uint32_t latch_timestamp;
//    mesa_packet_oam_type_t oam_type;
//    mesa_isdx_t isdx;
//    mesa_bool_t isdx_dont_use;
//    mesa_dp_level_t dp;
//    mesa_port_no_t masquerade_port;
//    uint32_t pdu_offset;
//    mesa_afi_id_t afi_id;
//    mesa_packet_pipeline_pt_t pipeline_pt;
//} mesa_packet_tx_info_t;

#define POStoBYTE(pos) (35-((pos)/8))   /* Converte IFH bit position to a IFH byte position */
#define POStoBIT(pos)  ((pos)%8)        /* Converte IFH bit position to a IFH byte bit position */
#define VSTAX          73               /* The IFH bit position of the first VSTAX bit. This is because the VSTAX bit positions in Data sheet is starting from zero. */
static void print_ifh(uint8_t  *ifh)
{
    uint32_t byte, bit;

    cli_printf("IFH:\n");
    byte = POStoBYTE(232);
    bit = POStoBIT(232);
    cli_printf("TS          Bit %u  byte  %u  width %u  %X %X %X %X %X\n", bit, byte, 40, ifh[byte-4], ifh[byte-3], ifh[byte-2], ifh[byte-1], ifh[byte]); /* 40 bit - 5 bytes*/

    byte = POStoBYTE(153);
    bit = POStoBIT(153);
    cli_printf("DST         Bit %u  byte %u  width %u  %X %X %X %X %X %X %X %X %X %X\n", bit, byte, 79, ifh[byte-9], ifh[byte-8], ifh[byte-7], ifh[byte-6], ifh[byte-5], ifh[byte-4], ifh[byte-3], ifh[byte-2], ifh[byte-1], ifh[byte]); /* 79 bit - 10 bytes*/

    byte = POStoBYTE(VSTAX+79);
    bit = POStoBIT(VSTAX+79);
    cli_printf("VSTAX.MUST  Bit %u  byte %u  width %u   %X\n", bit, byte, 1, ifh[byte]); /* 1 bit - 1 bytes */

    byte = POStoBYTE(VSTAX+64);
    bit = POStoBIT(VSTAX+64);
    cli_printf("VSTAX.MISC  Bit %u  byte %u  width %u  %X %X\n", bit, byte, 15, ifh[byte-1], ifh[byte]); /* 15 bit - 2 bytes */

    byte = POStoBYTE(VSTAX+55);
    bit = POStoBIT(VSTAX+55);
    cli_printf("VSTAX.QOS   Bit %u  byte %u  width %u   %X %X\n", bit, byte, 7, ifh[byte-1], ifh[byte]); /* 7 bit - 1 bytes */

    byte = POStoBYTE(VSTAX+44);
    bit = POStoBIT(VSTAX+44);
    cli_printf("VSTAX.GEN   Bit %u  byte %u  width %u  %X %X\n", bit, byte, 10, ifh[byte-1], ifh[byte]); /* 10 bit - 2 bytes */

    byte = POStoBYTE(VSTAX+32);
    bit = POStoBIT(VSTAX+32);
    cli_printf("VSTAX.DST   Bit %u  byte %u  width %u  %X %X\n", bit, byte, 11, ifh[byte-1], ifh[byte]); /* 11 bit - 2 bytes */

    byte = POStoBYTE(VSTAX+12);
    bit = POStoBIT(VSTAX+12);
    cli_printf("VSTAX.TAG   Bit %u  byte %u  width %u  %X %X %X %X\n", bit, byte, 20, ifh[byte-3], ifh[byte-2], ifh[byte-1], ifh[byte]); /* 20 bit - 3 bytes */

    byte = POStoBYTE(VSTAX+0);
    bit = POStoBIT(VSTAX+0);
    cli_printf("VSTAX.SRC   Bit %u  byte %u  width %u  %X %X\n", bit, byte, 12, ifh[byte-1], ifh[byte]); /* 12 bit - 2 bytes */

    byte = POStoBYTE(64);
    bit = POStoBIT(64);
    cli_printf("FWD.D_MODE  Bit %u  byte %u  width %u   %X %X\n", bit, byte, 9, ifh[byte-1], ifh[byte]); /* 9 bit - 2 bytes */

    byte = POStoBYTE(45);
    bit = POStoBIT(45);
    cli_printf("FWD.DN_REW  Bit %u  byte %u  width %u  %X %X %X\n", bit, byte, 12, ifh[byte-2], ifh[byte-1], ifh[byte]); /* 12 bit - 2 bytes */

    byte = POStoBYTE(29);
    bit = POStoBIT(29);
    cli_printf("MISC        Bit %u  byte %u  width %u  %X %X %X\n", bit, byte, 16, ifh[byte-2], ifh[byte-1], ifh[byte]); /* 16 bit - 2 bytes */

    byte = POStoBYTE(8);
    bit = POStoBIT(8);
    cli_printf("TAGGING     Bit %u  byte %u  width %u  %X %X %X\n", bit, byte, 21, ifh[byte-2], ifh[byte-1], ifh[byte]);  /* 21 bit - 3 bytes */

    byte = POStoBYTE(0);
    bit = POStoBIT(0);
    cli_printf("QOS         Bit %u  byte %u  width %u   %X\n", bit, byte, 8, ifh[byte]);  /* 8 bit - 1 byte */
}

static mesa_rc test_fa_time_stamp(void)
{
    uint32_t                     ctrl_cnt, offset;
    mesa_mac_t                   smac;
    mesa_ts_autoresp_dom_cfg_t   auto_cfg;
    mesa_timestamp_t             ts;
    uint64_t                     tc;
    mesa_synce_clock_out_t       synce_out_cfg;
    mesa_synce_clock_in_t        synce_in_cfg;

    if ((ctrl_cnt = mesa_capability(NULL, MESA_CAP_TS_RESP_CTRL_CNT)) == 0) {
        cli_printf("The test is assuming MESA_CAP_TS_RESP_CTRL_CNT\n");
        return MESA_RC_ERROR;
    }
    if ((ctrl_cnt = mesa_capability(NULL, MESA_CAP_SYNCE)) == 0) {
        cli_printf("The test is assuming MESA_CAP_SYNCE\n");
        return MESA_RC_ERROR;
    }
    if ((ctrl_cnt = mesa_capability(NULL, MESA_CAP_SYNCE_IN_TYPE)) == 0) {
        cli_printf("The test is assuming MESA_CAP_SYNCE\n");
        return MESA_RC_ERROR;
    }

    MESA_RC(mesa_ts_autoresp_dom_cfg_set(0, 1, &auto_cfg));
    MESA_RC(mesa_ts_autoresp_dom_cfg_get(0, 1, &auto_cfg));
    MESA_RC(mesa_ts_smac_set(0, 1, &smac));
    MESA_RC(mesa_ts_smac_get(0, 1, &smac));

    MESA_RC(mesa_ts_timeofday_get(NULL, &ts, &tc));
    MESA_RC(mesa_ts_domain_timeofday_get(NULL, 0, &ts, &tc));
    MESA_RC(mesa_ts_saved_timeofday_get(NULL, 0, &ts, &tc));
    MESA_RC(mesa_ts_timeofday_raw(NULL, &ts, &tc));
    MESA_RC(mesa_ts_output_clock_edge_offset_get(NULL, 0, &offset));

    synce_out_cfg.divider = MESA_SYNCE_DIVIDER_16;
    MESA_RC(mesa_synce_clock_out_set(NULL, 1, &synce_out_cfg));
    synce_in_cfg.clk_in = MESA_SYNCE_CLOCK_AUX;
    synce_in_cfg.port_no = 2;
    MESA_RC(mesa_synce_clock_in_set(NULL, 1, &synce_in_cfg));

    return MESA_RC_OK;
}

static mesa_rc test_fa_policer(mesa_bool_t enable, mesa_bool_t all)
{
    mesa_qos_port_conf_t  conf;

    MESA_RC(mesa_qos_port_conf_get(0, 1, &conf));

//    conf.queue[0].policer.level = 8192;   /*  25 G group highest*/
//    conf.queue[0].policer.rate = (enable || !all) ? 25000000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 3, &conf));     /* QOS 0 Port 3 */
//
//    conf.queue[0].policer.level = 8192;   /*  25 G group highest*/
//    conf.queue[0].policer.rate = enable ? 25000000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 2, &conf));     /* QOS 0 Port 2 */

//    conf.queue[0].policer.level = 8192;   /*  25 G group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 25000000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));     /* QOS 0 Port 1 */
//
//    conf.queue[1].policer.level = 8192;   /*  25 G group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (15000000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 8380416;   /*  25 G group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 20000000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 8192;   /*  15 G group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 15000000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 8192;   /*  15 G group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (10000000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 8380416;   /*  15 G group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 12500000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 8192;   /*  10 G group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 10000000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 8192;   /*  10 G group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (5000000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 8380416;   /*  10 G group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 7500000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 8192;   /*  5 G group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 5000000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 8192;   /*  5 G group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (2500000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 8380416;   /*  5 G group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 3750000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 8192;   /*  2.5 G group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 2500000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 8192;   /*  2.5 G group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (1000000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 8380416;   /*  2.5 G group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 1750000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 4096;   /*  1 G group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 1000000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 4096;   /*  1 G group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (500000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 4190208;   /*  1 G group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 750000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 4096;   /*  500 M group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 500000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 4096;   /*  500 M group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (100000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 4190208;   /*  500 M group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 250000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 4096;   /*  100 M group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 100000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 4096;   /*  100 M group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (50000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 4190208;   /*  100 M group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 75000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 4096;   /*  50 M group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 50000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 4096;   /*  50 M group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? (10000 + 1) : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 4190208;   /*  50 M group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 25000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

//    conf.queue[0].policer.level = 2048;   /*  10 M group highest - min burst size */
//    conf.queue[0].policer.rate = enable ? 10000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[1].policer.level = 2048;   /*  10 M group lowest - min burst size */
//    conf.queue[1].policer.rate = (enable || !all) ? 5 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));
//
//    conf.queue[2].policer.level = 2095104;   /*  10 M group mid - max burst size */
//    conf.queue[2].policer.rate = (enable || !all) ? 5000 : MESA_BITRATE_DISABLED;
//    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));


// idx  min_burst  max_burst  min_rate  max_rate(min)  max_rate(max)  min_token  pup_int  frame_size  lb_count  lb_max
// 0    8192       8380416    3052503   25000000000    25000000000    4915       1638     64          0          408
// 1    8192       8380416    1831501   15000000000    15000000000    5461       2730     64          0          681
// 2    8192       8380416    1221001   10000000000    10000000000    4096       4095     64          0          1022
// 3    8192       8380416    610500    5000000000     5000000000     4096       8190     64          0          2046
// 4    8192       8380416    305250    2500000000     2500000000     3277       16380    64          0          4094
// 5    4096       4190208    244140    1000000000     1999511718     2049       20480    64          0          5119
// 6    4096       4190208    122070    500000000      999755859      820        40960    64          0          10239
// 7    4096       4190208    24414     100000000      199951171      2049       204800   64          0          51199
// 8    4096       4190208    12207     50000000       99975585       820        409600   64          0          102399
// 9    2048       2095104    4882      10000000       39990234       1          1024000  64          0          255999

    conf.queue[0].policer.level = 8190;   /*  10 M group max rate - max rate burst size */
    conf.queue[0].policer.rate = 39990;
    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

    conf.queue[1].policer.level = 8190 - 1;   /*  10 M group max rate - max rate burst size - 1 */
    conf.queue[1].policer.rate = 39990;
    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

    conf.queue[2].policer.level = 2095104 + 1;   /*  10 M group max rate - max burst size + 1 */
    conf.queue[2].policer.rate = 39990;
    MESA_RC(mesa_qos_port_conf_set(0, 1, &conf));

    return MESA_RC_OK;
}
static mesa_rc test_fa_policer_enable(void)
{
    return test_fa_policer(1, 0);
}
static mesa_rc test_fa_policer_disable_first(void)
{
    return test_fa_policer(0, 0);
}
static mesa_rc test_fa_policer_disable_all(void)
{
    return test_fa_policer(0, 1);
}

static mesa_rc test_fa_ts(void)
{
    uint64_t                        ts_cnt;
    uint8_t                         frm[4];
    mesa_timestamp_t                ts;
    mesa_packet_rx_info_t           rx_info;
    mesa_packet_timestamp_props_t   ts_props;
    mesa_bool_t                     timestamp_ok;

    MESA_RC(mesa_packet_phy_cnt_to_ts_cnt(NULL, 5, &ts_cnt));
    cli_printf("mesa_packet_phy_cnt_to_ts_cnt  ts_cnt  %llu  %llX\n", ts_cnt, ts_cnt);

    MESA_RC(mesa_packet_ns_to_ts_cnt(NULL, 1000000000-5, &ts_cnt));
    cli_printf("mesa_packet_ns_to_ts_cnt  ts_cnt  %llu  %llX\n", ts_cnt, ts_cnt);

    memset(frm, 0, sizeof(frm));
    memset(&rx_info, 0, sizeof(rx_info));
    memset(&ts_props, 0, sizeof(ts_props));
    rx_info.hw_tstamp = 0x500;
    MESA_RC(mesa_ptp_get_timestamp(NULL, frm, &rx_info, MESA_PACKET_PTP_MESSAGE_TYPE_SYNC, ts_props, &ts_cnt, &timestamp_ok));
    cli_printf("mesa_ptp_get_timestamp  ts_cnt %llu  timestamp_ok %u\n", ts_cnt, timestamp_ok);

    MESA_RC(mesa_ts_timeofday_get(NULL, &ts, &ts_cnt)); 
    cli_printf("mesa_ts_timeofday_get  ts.sec_msb %u  ts.seconds %u  ts.nanoseconds %u  ts.nanosecondsfrac %u  ts_cnt %llu\n", ts.sec_msb, ts.seconds, ts.nanoseconds, ts.nanosecondsfrac, ts_cnt);

    return MESA_RC_OK;
}

static mesa_rc test_fa_ifh_encode_decode(void)
{
    mesa_packet_tx_info_t tx_info;
    mesa_packet_rx_meta_t meta;
    mesa_packet_rx_info_t rx_info;
    uint64_t timestamp;
    uint8_t *ifh;
    uint32_t  ifh_len;
    uint8_t xtr_hdr[50];

    if (!(ifh_len = mesa_capability(NULL, MESA_CAP_PACKET_TX_IFH_SIZE))) {
        cli_printf("The test is assuming MESA_CAP_PACKET_TX_IFH_SIZE\n");
        return MESA_RC_ERROR;
    }

    ifh = malloc(ifh_len);
    if (ifh == NULL) {
        cli_printf("malloc failed\n");
        return MESA_RC_ERROR;
    }
    memset(ifh, 0, ifh_len);

    memset(&tx_info, 0, sizeof(tx_info));
    tx_info.switch_frm = 0;
    tx_info.dst_port = 2;
    tx_info.pipeline_pt = 5;
    tx_info.cos = 3;
    tx_info.tag.vid = 4096+2;
    tx_info.tag.pcp = 2;
    tx_info.ptp_timestamp = 0x800000000100;

    cli_printf("tx_info:  switch_frm %u  dst_port %u  pipeline_pt %u  cos %u\n", tx_info.switch_frm, tx_info.dst_port, tx_info.pipeline_pt, tx_info.cos);
    cli_printf("          tag.vid %u  tag.pcp %u  ptp_timestamp %llX\n", tx_info.tag.vid, tx_info.tag.pcp, tx_info.ptp_timestamp);
    MESA_RC(mesa_packet_tx_hdr_encode(NULL, &tx_info, ifh_len, (uint8_t *)ifh, &ifh_len));
    print_ifh(ifh);

    memset(&tx_info, 0, sizeof(tx_info));
    tx_info.switch_frm = 1;
    tx_info.masquerade_port = 2;
    tx_info.iflow_id = 7;

    cli_printf("\n");
    cli_printf("tx_info:  switch_frm %u  masquerade_port %u  iflow_id %u\n", tx_info.switch_frm, tx_info.masquerade_port, tx_info.iflow_id);
    MESA_RC(mesa_packet_tx_hdr_encode(NULL, &tx_info, ifh_len, (uint8_t *)ifh, &ifh_len));
    print_ifh(ifh);

    timestamp = 0x8000000001;
    memset(&meta, 0, sizeof(meta));
    memset(xtr_hdr, 0, sizeof(xtr_hdr));
    xtr_hdr[2]  = (timestamp >> 32) & 0xFF;
    xtr_hdr[3]  = (timestamp >> 24) & 0xFF;
    xtr_hdr[4]  = (timestamp >> 16) & 0xFF;
    xtr_hdr[5]  = (timestamp >>  8) & 0xFF;
    xtr_hdr[6]  = (timestamp >>  0) & 0xFF;
    xtr_hdr[16] = 1;    // Bit 152 is the MSB of VSTAX, which must be 1
    MESA_RC(mesa_packet_rx_hdr_decode(NULL, &meta, xtr_hdr, &rx_info));
    cli_printf("\n");
    cli_printf("rx_info:  hw_tstamp %llX\n", rx_info.hw_tstamp);

    return MESA_RC_OK;
}

static mesa_rc test_mac_swap_port_facility_loop(void)
{
    // This test is configuring a Port domain facility MAC swapping loop.
    // All ingress frames on 'port' is redirected to 'port' and transmitted with swapped SMAC/DMAC.
    // All ingress frames on other ports are filtered against 'port'.

    mesa_port_no_t  port_no = 0;
    mesa_ace_t      ace = {};

    if (!mesa_capability(NULL, MESA_CAP_ACL_MAC_SWAP)) {
        cli_printf("The test is assuming HW that implements ACL_MAC_SWAP\n");
        return MESA_RC_ERROR;
    }

    // Create ACL redirecting and MAC swappoing on 'this' port
    MESA_RC(mesa_ace_init(NULL, MESA_ACE_TYPE_ANY, &ace));
    ace.id = 1;
    mesa_port_list_set(&ace.port_list, port_no, 1);
    ace.action.port_action = MESA_ACL_PORT_ACTION_REDIR;
    ace.action.mac_swap = 1;
    mesa_port_list_set(&ace.action.port_list, port_no, 1);
    MESA_RC(mesa_ace_add(NULL, MESA_ACE_ID_LAST, &ace));

    // Create ACL preventing frames to be forwarded to this port
    MESA_RC(mesa_ace_init(NULL, MESA_ACE_TYPE_ANY, &ace));
    ace.id = 2;
    for (uint32_t i = 0; i < mesa_port_cnt(NULL); ++i) {
        if (i == port_no) {
            mesa_port_list_set(&ace.port_list, i, 0);
            mesa_port_list_set(&ace.action.port_list, i, 0);
        } else {
            mesa_port_list_set(&ace.port_list, i, 1);
            mesa_port_list_set(&ace.action.port_list, i, 1);
        }
    }
    ace.action.port_action = MESA_ACL_PORT_ACTION_FILTER;
    MESA_RC(mesa_ace_add(NULL, MESA_ACE_ID_LAST, &ace));

    cli_printf("Port 1 is now configured to loop back all ingress frames with swapped DMAC/SMAC.\n");
    cli_printf("Forwarding to Port 1 from other ports is prevented.\n");
    cli_printf("\n");
    cli_printf("Start injecting untagged frames on port 1 and port 2.\n");
    cli_printf("Observe injected frames on port 1 is transmittec on port 1 with swapped DMAC/SMAC.\n");
    cli_printf("Observe injected frames on port 2 is not forwarded to port 1.\n");

    return MESA_RC_OK;
}

// QoS API test
static mesa_rc test_qos(void)
{
    mesa_port_no_t       port_no = 0;
    mesa_qos_port_conf_t conf = {};

    // Add ACE 1 allowing all IPv4 frames from switch port 2 with SIP 1.2.3.4
    MESA_RC(mesa_qos_port_conf_get(NULL, port_no, &conf));
    cli_printf("Port 0 has basic classification to prio %d.\n", conf.default_prio);
    conf.default_prio = 7;
    MESA_RC(mesa_qos_port_conf_set(NULL, port_no, &conf));

    return MESA_RC_OK;
}

static mesa_rc test_fa_tsn(void)
{
    mesa_vid_t               vid_def = 1;   // Default VLAN
    mesa_vid_t               vid_fwd = 2;   // Forwarding VLAN
    mesa_vid_t               vid_fp = 10;   // Frame preemption VLAN (QCE only)
    mesa_vid_t               vid_psfp = 20; // PSFP VLAN (VCE only)
    mesa_vid_t               vid_frer = 30; // FRER VLAN
    mesa_vid_t               vid_tas = 40;  // TAS VLAN
    mesa_port_no_t           port_no, port_rx = 0, port_tx = 1;
    mesa_port_list_t         port_list, rx_list, tx_list;
    mesa_vlan_port_conf_t    vlan_conf;
    mesa_prio_t              prio;
    mesa_qce_t               qce;
    mesa_qos_fp_port_conf_t  fp_conf;
    mesa_ace_t               ace;
    mesa_ace_ptp_t           *ptp = &ace.frame.etype.ptp;
    mesa_psfp_gce_t          psfp_gcl[2];
    int                      i, q, max_cnt = 2;
    mesa_psfp_gate_id_t      gate_id = 0;
    mesa_psfp_gate_conf_t    gate_conf;
    mesa_psfp_filter_id_t    filter_id = 0;
    mesa_psfp_filter_conf_t  filter_conf;
    mesa_iflow_id_t          iflow_id;
    mesa_iflow_conf_t        iflow_conf;
    mesa_vce_t               vce;
    mesa_tce_t               tce;
    mesa_frer_mstream_id_t   mstream_id;
    mesa_frer_cstream_id_t   cstream_id = 0;
    mesa_frer_stream_conf_t  frer_conf;
    mesa_qos_tas_port_conf_t tas_conf;
    mesa_qos_tas_gce_t       tas_gcl[2];
    uint64_t                 tc;

    /*** VLAN and PVLAN *********************************************************************/

    // Use PVLANs to avoid loops between port Tx ports
    MESA_RC(mesa_pvlan_port_members_get(NULL, 0, &port_list));
    mesa_port_list_set(&port_list, port_tx, 0);
    MESA_RC(mesa_pvlan_port_members_set(NULL, 0, &port_list));
    mesa_port_list_set(&port_list, port_tx, 1);
    mesa_port_list_set(&port_list, port_tx + 1, 0);
    MESA_RC(mesa_pvlan_port_members_set(NULL, 1, &port_list));

    // Exclude port 0-3 from default VLAN
    MESA_RC(mesa_vlan_port_members_get(NULL, vid_def, &port_list));
    for (port_no = 0; port_no < 4; port_no++) {
        mesa_port_list_set(&port_list, port_no, 0);
    }
    MESA_RC(mesa_vlan_port_members_set(NULL, vid_def, &port_list));

    // Include port 0, 1 and 3 in forwarding VLAN
    mesa_port_list_clear(&port_list);
    for (port_no = 0; port_no < 4; port_no++) {
        mesa_port_list_set(&port_list, port_no, port_no == (port_tx + 1) ? 0 : 1);
        MESA_RC(mesa_vlan_port_conf_get(NULL, port_no, &vlan_conf));
        vlan_conf.pvid = 2;
        vlan_conf.untagged_vid = 2;
        MESA_RC(mesa_vlan_port_conf_set(NULL, port_no, &vlan_conf));
    }
    MESA_RC(mesa_vlan_port_members_set(NULL, vid_fwd, &port_list));

    // Include Rx and Tx ports FRER VLAN
    mesa_port_list_clear(&rx_list);
    mesa_port_list_clear(&tx_list);
    mesa_port_list_clear(&port_list);
    for (port_no = 0; port_no < 3; port_no++) {
        mesa_port_list_set(&port_list, port_no, 1);
        mesa_port_list_set(port_no == port_rx ? &rx_list : &tx_list, port_no, 1);
    }
    MESA_RC(mesa_vlan_port_members_set(NULL, vid_frer, &port_list));

    /*** Frame Preemption *******************************************************************/

    // On Rx port, map Frame Preemption VLAN to priority 4
    prio = 4;
    MESA_RC(mesa_qce_init(NULL, MESA_QCE_TYPE_ANY, &qce));
    qce.id = 1;
    qce.key.port_list = rx_list;
    qce.key.tag.tagged = MESA_VCAP_BIT_1;
    qce.key.tag.s_tag = MESA_VCAP_BIT_0;
    qce.key.tag.vid.vr.v.value = vid_fp;
    qce.key.tag.vid.vr.v.mask = 0xfff;
    qce.action.prio_enable = 1;
    qce.action.prio = prio;
    MESA_RC(mesa_qce_add(NULL, MESA_QCE_ID_LAST, &qce));

    // On Tx port, enable frame preemption for priority 4
    MESA_RC(mesa_qos_fp_port_conf_get(NULL, port_tx, &fp_conf));
    fp_conf.admin_status[prio] = 1;
    fp_conf.enable_tx = 1;
    MESA_RC(mesa_qos_fp_port_conf_set(NULL, port_tx, &fp_conf));

    /*** PTP Transparent Clock **************************************************************/

    for (i = 1; i < 5; i++) {
        MESA_RC(mesa_ace_init(NULL, MESA_ACE_TYPE_ETYPE, &ace));
        ace.id = i;
        ace.port_list = port_list;
        ace.frame.etype.etype.value[0] = 0x88;
        ace.frame.etype.etype.value[1] = 0xf7;
        ace.frame.etype.etype.mask[0] = 0xff;
        ace.frame.etype.etype.mask[1] = 0xff;
        ptp->enable = 1;
        ptp->header.mask[1] = 0x0f;
        ptp->header.value[1] = 0x02; /* versionPTP = 2 */
        if (i == 1) {
            ptp->header.mask[0] = 0x0f;
            ptp->header.value[0] = 0x00; /* messageType = 0 */
            ace.action.ptp_action = MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2;
        } else if (i == 2) {
            ptp->header.mask[0] = 0x0f;
            ptp->header.value[0] = 0x03; /* messageType = 3 */
            ace.action.ptp_action = MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1;
        } else if (i == 3) {
            ptp->header.mask[0] = 0x0c;
            ptp->header.value[0] = 0x00; /* messageType = 1/2 */
            ace.action.ptp_action = MESA_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY;
        } else {
            ptp->header.mask[0] = 0x08;
            ptp->header.value[0] = 0x08; /* messageType = 8-15 */
        }
        ace.action.port_action = MESA_ACL_PORT_ACTION_FILTER;
        ace.action.port_list = port_list;
        MESA_RC(mesa_ace_add(NULL, MESA_ACE_ID_LAST, &ace));
    }

    /*** PSFP *******************************************************************************/

    // Setup PSFP gate control list
    MESA_RC(mesa_psfp_gate_conf_get(NULL, gate_id, &gate_conf));
    for (i = 0; i < max_cnt; i++) {
        mesa_psfp_gce_t *gce = &psfp_gcl[i];
        memset(gce, 0, sizeof(*gce));
        /* Open for 1 msec, closed for 9 msec */
        gce->gate_open = (i == 0 ? 1 : 0);
        gce->time_interval = ((i == 0 ? 1 : 9) * 1000000);
        gate_conf.config.cycle_time += gce->time_interval;
    }
    MESA_RC(mesa_psfp_gcl_conf_set(NULL, gate_id, max_cnt, psfp_gcl));
    gate_conf.enable = 1;
    gate_conf.config_change = 1;
    MESA_RC(mesa_psfp_gate_conf_set(NULL, gate_id, &gate_conf));

    // Map filter to gate
    MESA_RC(mesa_psfp_filter_conf_get(NULL, filter_id, &filter_conf));
    filter_conf.gate_enable = 1;
    filter_conf.gate_id = gate_id;
    MESA_RC(mesa_psfp_filter_conf_set(NULL, filter_id, &filter_conf));

    // Allocate iflow for PSFP and map to filter
    MESA_RC(mesa_iflow_alloc(NULL, &iflow_id));
    MESA_RC(mesa_iflow_conf_get(NULL, iflow_id, &iflow_conf));
    iflow_conf.psfp.filter_enable = 1;
    iflow_conf.psfp.filter_id = filter_id;
    iflow_conf.cut_through_disable = 1;
    MESA_RC(mesa_iflow_conf_set(NULL, iflow_id, &iflow_conf));

    // On Rx port, map PSFP VLAN to iflow
    MESA_RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ANY, &vce));
    vce.id = 1;
    vce.key.port_list = rx_list;
    vce.key.tag.tagged = MESA_VCAP_BIT_1;
    vce.key.tag.s_tag = MESA_VCAP_BIT_0;
    vce.key.tag.vid.value = vid_psfp;
    vce.key.tag.vid.mask = 0xfff;
    vce.action.flow_id = iflow_id;
    MESA_RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));

    /*** FRER (sequence generation) *********************************************************/

    // On Rx port, map FRER VLAN to iflow with sequence generation
    MESA_RC(mesa_iflow_alloc(NULL, &iflow_id));
    MESA_RC(mesa_iflow_conf_get(NULL, iflow_id, &iflow_conf));
    iflow_conf.frer.generation = 1;
    iflow_conf.cut_through_disable = 1;
    MESA_RC(mesa_iflow_conf_set(NULL, iflow_id, &iflow_conf));
    vce.id = 2;
    vce.key.tag.vid.value = vid_frer;
    vce.action.vid = vid_frer;
    vce.action.pop_enable = 1;
    vce.action.pop_cnt = 1;
    vce.action.flow_id = iflow_id;
    MESA_RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));

    // On Tx ports, R-tag push enabled for FRER VLAN
    MESA_RC(mesa_tce_init(NULL, &tce));
    tce.id = 1;
    tce.key.port_list = tx_list;
    tce.key.vid = vid_frer;
    tce.action.tag.tpid = MESA_TPID_SEL_C;
    tce.action.tag.vid = vid_frer;
    tce.action.rtag.sel = MESA_RTAG_SEL_INNER;
    MESA_RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce));

    /*** FRER (sequence recovery) ***********************************************************/

    // Enable sequence recovery for compound stream
    MESA_RC(mesa_frer_cstream_conf_get(NULL, cstream_id, &frer_conf));
    frer_conf.recovery = 1;
    frer_conf.alg = MESA_FRER_RECOVERY_ALG_VECTOR;
    frer_conf.hlen = 8;
    frer_conf.reset_time = 1000;
    MESA_RC(mesa_frer_cstream_conf_set(NULL, cstream_id, &frer_conf));

    // Allocate member stream on Rx port and map to compound stream
    MESA_RC(mesa_frer_mstream_alloc(NULL, &rx_list, &mstream_id));
    MESA_RC(mesa_frer_mstream_conf_get(NULL, mstream_id, port_rx, &frer_conf));
    frer_conf.cstream_id = cstream_id;
    MESA_RC(mesa_frer_mstream_conf_set(NULL, mstream_id, port_rx, &frer_conf));

    // On Tx ports, map FRER VLAN to iflow mapping to member stream
    MESA_RC(mesa_iflow_alloc(NULL, &iflow_id));
    MESA_RC(mesa_iflow_conf_get(NULL, iflow_id, &iflow_conf));
    iflow_conf.frer.mstream_enable = 1;
    iflow_conf.frer.mstream_id = mstream_id;
    iflow_conf.cut_through_disable = 1;
    MESA_RC(mesa_iflow_conf_set(NULL, iflow_id, &iflow_conf));
    vce.id = 3;
    vce.key.port_list = tx_list;
    vce.action.flow_id = iflow_id;
    MESA_RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));

    // On Rx port, R-tag pop enabled for FRER VLAN
    tce.id = 2;
    tce.key.port_list = rx_list;
    tce.action.rtag.sel = MESA_RTAG_SEL_NONE;
    tce.action.rtag.pop = 1;
    MESA_RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce));

    /*** TAS ********************************************************************************/

    // On Rx port, map TAS VLAN to priority 5
    prio = 5;
    qce.id++;
    qce.key.tag.vid.vr.v.value = vid_tas;
    qce.action.prio = prio;
    MESA_RC(mesa_qce_add(NULL, MESA_QCE_ID_LAST, &qce));

    // Setup TAS gate control list
    MESA_RC(mesa_qos_tas_port_conf_get(NULL, port_tx, &tas_conf));
    for (i = 0; i < max_cnt; i++) {
        mesa_qos_tas_gce_t *gce = &tas_gcl[i];
        memset(gce, 0, sizeof(*gce));
        for (q = 0; q < MESA_QUEUE_ARRAY_SIZE; q++) {
            /* Open for 1 msec, closed for 9 msec */
            gce->gate_open[q] = (i == 1 && q == prio ? 0 : 1);
        }
        gce->time_interval = ((i == 0 ? 1 : 9) * 1000000);
        tas_conf.cycle_time += gce->time_interval;
    }
    MESA_RC(mesa_qos_tas_port_gcl_conf_set(NULL, port_tx, max_cnt, tas_gcl));
    tas_conf.gate_enabled = 1;
    for (q = 0; q < MESA_QUEUE_ARRAY_SIZE; q++) {
        tas_conf.gate_open[q] = 1;
    }
    tas_conf.config_change = 1;
    MESA_RC(mesa_ts_timeofday_get(NULL, &tas_conf.base_time, &tc));
    tas_conf.base_time.seconds++;
    MESA_RC(mesa_qos_tas_port_conf_set(NULL, port_tx, &tas_conf));

    return MESA_RC_OK;
}

static test_entry_t test_table[] = {
    {
        "ACL test",
        test_acl
    },
    {
        "Serval1 Port facility MAC swapping loop",
        test_mac_swap_port_facility_loop
    },
    {
        "QoS test",
        test_qos
    },
    {
        "Fireant IFH encode test",
        test_fa_ifh_encode_decode
    },
    {
        "Fireant TS test",
        test_fa_time_stamp
    },
    {
        "Fireant Policer enable test",
        test_fa_policer_enable
    },
    {
        "Fireant Policer disable first test",
        test_fa_policer_disable_first
    },
    {
        "Fireant Policer disable all test",
        test_fa_policer_disable_all
    },
    {
        "Fireant TS test",
        test_fa_ts
    },
    {
        "SparX-5i TSN demo",
        test_fa_tsn
    }
};



static void cli_cmd_test(cli_req_t *req)
{
    uint32_t       i, cnt = sizeof(test_table)/sizeof(test_entry_t);
    test_cli_req_t *mreq = req->module_req;

    if (req->set && mreq->test_no < cnt) {
        if (test_table[mreq->test_no].func() != MESA_RC_OK) {
            cli_printf("\nTest failed\n");
        }
        return;
    }

    for (i = 0; i < cnt; i++) {
        if (i == 0) {
            cli_table_header("Number  Description");
        }
        cli_printf("%-8u%s\n", i, test_table[i].descr);
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Test [<test_no>]",
        "Execute test",
        cli_cmd_test
    },
};

static int cli_parm_test_no(cli_req_t *req)
{
    test_cli_req_t *mreq = req->module_req;

    return cli_parm_u32(req, &mreq->test_no, 0, 1000);
}

static cli_parm_t cli_parm_table[] = {
    {
        "<test_no>",
        "Test number, default: Show test descriptions",
        CLI_PARM_FLAG_SET,
        cli_parm_test_no
    },
};

static void test_cli_init(void)
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

void mscc_appl_test_init(mscc_appl_init_t *init)
{
    size_t ret_len;
    char   port_buf[100]={};

    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        test_cli_init();

        if (MESA_RC_OK == init->board_inst->iface.conf_get("mep_loop_port", port_buf, (size_t)sizeof(port_buf), &ret_len)) {
            if (0 != strlen(port_buf)) {
                loop_port = atoi(port_buf);
            }
        }
        break;

    default:
        break;
    }
}


