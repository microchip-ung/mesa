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
    tx_info.isdx = 7;

    cli_printf("\n");
    cli_printf("tx_info:  switch_frm %u  masquerade_port %u  isdx %u\n", tx_info.switch_frm, tx_info.masquerade_port, tx_info.isdx);
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





static mesa_vid_t       cl_vid = 100;
static mesa_port_no_t   network_port_0 = 0;
static mesa_port_no_t   network_port_1 = 0;
static mesa_port_no_t   network_port_2 = 0;
static mesa_mac_t       unicast_addr = {{0x01,0x02,0x03,0x04,0x05,0x6}};

static uint32_t         meg_level = 3;
static uint16_t         mep_id = 10;
static uint16_t         peer_mep_id = 20;
static uint8_t          meg_id[10] = {'A','B','C','D','E','F','G','H','I','J'};
static uint8_t          priority = 3;


static mesa_iflow_id_t     port_voe_iflow_id;
static mesa_iflow_id_t     voe_iflow_id;
static mesa_eflow_id_t     voe_eflow_id;
static mesa_iflow_id_t     down_voi_iflow_id;
static mesa_iflow_id_t     up_voi_iflow_id;
static mesa_eflow_id_t     up_voi_eflow_id;
static mesa_voe_idx_t      vlan_voe_idx;
static mesa_voe_idx_t      port_voe_idx;
static mesa_voi_idx_t      down_voi_idx;
static mesa_voi_idx_t      up_voi_idx;
static uint32_t            longest_ccm_period = 0;
static mesa_bool_t         dUNM, dLOC;

void initialize_voe()
{
    mesa_vop_conf_t  vop;
    mesa_mac_t       multicast_addr = {{0x01,0x80,0xC2,0x00,0x00,0x30}};

    memset(&vop, 0, sizeof(vop));
    memcpy(vop.multicast_dmac.addr, multicast_addr.addr, sizeof(vop.multicast_dmac.addr));
    vop.auto_copy_period[0] = 3*1000*1000;  /* Slow - Normal - 3s */
    vop.auto_copy_period[1] = 1*1000*1000;  /* Fast - 1s */
    vop.voe_queue_ccm = 3;
    vop.voe_queue_lt = 3;
    vop.voe_queue_lbr = 3;
    vop.voi_queue = 3;
    (void)mesa_vop_conf_set(NULL, &vop);
}

void standard_vlan_configuration()
{
    mesa_vlan_conf_t        vlan_conf;
    mesa_vlan_port_conf_t   vlan_port_conf;
    mesa_port_list_t        port_list;

    vlan_conf.s_etype = 0x8902;
    (void)mesa_vlan_conf_set(NULL, &vlan_conf);

    vlan_port_conf.port_type = MESA_VLAN_PORT_TYPE_S;
    vlan_port_conf.pvid = 1;
    vlan_port_conf.untagged_vid = MESA_VID_NULL;
    vlan_port_conf.frame_type = MESA_VLAN_FRAME_TAGGED;
    vlan_port_conf.ingress_filter = FALSE;

    (void)mesa_vlan_port_conf_set(NULL, network_port_0, &vlan_port_conf);
    (void)mesa_vlan_port_conf_set(NULL, network_port_1, &vlan_port_conf);
    (void)mesa_vlan_port_conf_set(NULL, network_port_2, &vlan_port_conf);

    mesa_port_list_set(&port_list, network_port_0, 1);
    mesa_port_list_set(&port_list, network_port_1, 1);
    mesa_port_list_set(&port_list, network_port_2, 1);

    (void)mesa_vlan_port_members_set(NULL, cl_vid, &port_list);
}

void port_down_mep_configuration()
{
    uint32_t               i;
    mesa_vce_t             vce;
    mesa_iflow_conf_t      iflow;
    mesa_voe_conf_t        voe_cfg;
    mesa_voe_allocation_t  alloc_data;

    /* Allocate the Port VOE */
    alloc_data.type = MESA_VOE_TYPE_PORT;
    alloc_data.port = network_port_0;
    alloc_data.direction = MESA_OAM_DIRECTION_DOWN;
    (void)mesa_voe_alloc(NULL, &alloc_data, &port_voe_idx);

    /* Allocate and configure the ingress flow ID */
    (void)mesa_iflow_alloc(NULL, &port_voe_iflow_id);
    (void)mesa_iflow_conf_get(NULL, port_voe_iflow_id, &iflow);
    iflow.voe_idx = port_voe_idx;
    (void)mesa_iflow_conf_set(NULL, port_voe_iflow_id, &iflow);

    /* Initialize and add an OAM ingress VOE pointing VCE rule */
    (void)mesa_vce_init(NULL, MESA_VCE_TYPE_ETYPE, &vce);
    mesa_port_list_set(&vce.key.port_list, network_port_0, 1);  /* Match on ingress port as the Down MEP residence network port */
    vce.key.type = MESA_VCE_TYPE_ETYPE;                         /* Match on Ether type frames */
    vce.key.frame.etype.etype.value[0] = 0x89;                  /* Match on Ethernet OAM frames - 0x8902 */
    vce.key.frame.etype.etype.value[1] = 0x02;                  /* Match on Ethernet OAM frames - 0x8902 */
    vce.key.frame.etype.etype.mask[0] = 0xFF;
    vce.key.frame.etype.etype.mask[1] = 0xFF;
    vce.key.frame.etype.mel.value = 0;                          /* Matching MEG level mask is calculated. This will cover all levels <= 7 */
    vce.key.frame.etype.mel.mask = ~((0x01 << 7) - 1);
    vce.action.oam_detect = MESA_OAM_DETECT_UNTAGGED;           /* Mark frames as OAM */
    vce.action.flow_id = port_voe_iflow_id;                     /* Generate the ingress flow */
    (void)mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce);

    /* Configure the down Port VOE */
    memset(&voe_cfg, 0, sizeof(voe_cfg));
    voe_cfg.enable = TRUE;
    voe_cfg.unicast_mac = unicast_addr;
    voe_cfg.meg_level = meg_level;
    voe_cfg.dmac_check_type = MESA_VOE_DMAC_CHECK_BOTH;
    voe_cfg.loop_iflow_id = MESA_IFLOW_ID_NONE;
    voe_cfg.block_mel_high = TRUE;
    (void)mesa_voe_conf_set(NULL, port_voe_idx, &voe_cfg);

    /* Add an OAM ingress VOE marking VCE rule on VLAN ports "behind" the Port Down VOE. This will enable the Port down VOE to do MEG level filtering on egress */
    /* We inherits most VCE configuration from previous VCE add */
    vce.key.frame.etype.mel.mask = 0;            /* Match on all MEG levels */
    vce.action.flow_id = MESA_IFLOW_ID_NONE;     /* Do not generate ingress flow */
    for (i = network_port_1; i <= network_port_2; ++i)
    {
        mesa_port_list_clear(&vce.key.port_list);
        mesa_port_list_set(&vce.key.port_list, i, 1);
        (void)mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce);
    }
}

void vlan_down_mep_configuration()
{
    uint32_t               i;
    mesa_vce_t             vce;
    mesa_tce_t             tce;
    mesa_iflow_conf_t      iflow;
    mesa_eflow_conf_t      eflow;
    mesa_voe_conf_t        voe_cfg;
    mesa_voe_allocation_t  alloc_data;

    /* Allocate the Service VOE */
    alloc_data.type = MESA_VOE_TYPE_SERVICE;
    alloc_data.port = network_port_0;
    alloc_data.direction = MESA_OAM_DIRECTION_DOWN;
    (void)mesa_voe_alloc(NULL, &alloc_data, &port_voe_idx);

    /* Allocate and configure the ingress flow ID */
    (void)mesa_iflow_alloc(NULL, &voe_iflow_id);
    (void)mesa_iflow_conf_get(NULL, voe_iflow_id, &iflow);
    iflow.voe_idx = vlan_voe_idx;
    (void)mesa_iflow_conf_set(NULL, voe_iflow_id, &iflow);

    /* Allocate and configure the egress flow ID */
    (void)mesa_eflow_alloc(NULL, &voe_eflow_id);
    (void)mesa_eflow_conf_get(NULL, voe_eflow_id, &eflow);
    eflow.voe_idx = vlan_voe_idx;
    (void)mesa_eflow_conf_set(NULL, voe_eflow_id, &eflow);

    /* Initialize and add an OAM ingress VOE pointing VCE rule */
    (void)mesa_vce_init(NULL, MESA_VCE_TYPE_ETYPE, &vce);
    mesa_port_list_set(&vce.key.port_list, network_port_0, 1);  /* Match on ingress port as the Down MEP residence network port */
    vce.key.tag.vid.value = cl_vid;                             /* Match on the VID for this VLAN */
    vce.key.tag.vid.mask = 0xFFFF;                              
    vce.key.tag.tagged = MESA_VCAP_BIT_1;                       /* Match on tagged frames */
    vce.key.tag.s_tag = MESA_VCAP_BIT_0;                        /* Match on C-tagged frames */
    vce.key.type = MESA_VCE_TYPE_ETYPE;                         /* Match on Ether type frames */
    vce.key.frame.etype.etype.value[0] = 0x89;                  /* Match on Ethernet OAM frames - 0x8902 */
    vce.key.frame.etype.etype.value[1] = 0x02;
    vce.key.frame.etype.etype.mask[0] = 0xFF;
    vce.key.frame.etype.etype.mask[1] = 0xFF;
    vce.key.frame.etype.mel.value = 0;                          /* Matching MEG level mask is calculated. This will cover all levels <= 'meg_level' */
    vce.key.frame.etype.mel.mask = ~((0x01 << meg_level) - 1);  
    vce.action.oam_detect = MESA_OAM_DETECT_SINGLE_TAGGED;      /* Mark frames as OAM */
    vce.action.flow_id = voe_iflow_id;                          /* Generate the ingress flow */
    (void)mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce);

    /* Configure the VLAN down Service VOE */
    memset(&voe_cfg, 0, sizeof(voe_cfg));
    voe_cfg.enable = TRUE;
    voe_cfg.unicast_mac = unicast_addr;
    voe_cfg.meg_level = meg_level;
    voe_cfg.dmac_check_type = MESA_VOE_DMAC_CHECK_BOTH;
    voe_cfg.loop_iflow_id = MESA_IFLOW_ID_NONE;
    voe_cfg.block_mel_high = FALSE;
    (void)mesa_voe_conf_set(NULL, vlan_voe_idx, &voe_cfg);

    /* Add an OAM ingress VOE marking VCE rule on VLAN ports "behind" the VLAN Down VOE. This will enable the VLAN down VOE to do MEG level filtering on egress */
    /* We inherits most VCE configuration from previous VCE add */
    vce.key.frame.etype.mel.mask = 0;            /* Match on all MEG levels */
    vce.action.flow_id = MESA_IFLOW_ID_NONE;     /* Do not generate ingress flow */
    for (i = network_port_1; i <= network_port_2; ++i)
    {
        mesa_port_list_clear(&vce.key.port_list);
        mesa_port_list_set(&vce.key.port_list, i, 1);
        (void)mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce);
    }

    /* Initialize and add an classified VID egress VOE pointing TCE rule. */
    /* This will point any OAM coming from the switch to VOE for MEG level filtering. Also hit by injection */
    (void)mesa_tce_init(NULL, &tce);
    mesa_port_list_set(&tce.key.port_list, network_port_0, 1);   /* Match on egress port as the Down MEP residence network port */
    tce.key.vid = cl_vid;                                        /* Match on egress flow id */
    tce.action.flow_id = voe_eflow_id;
    (void)mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce);
}

void vlan_voi_configuration()
{
    uint32_t              i;
    mesa_vce_t            vce;
    mesa_tce_t            tce;
    mesa_iflow_conf_t     iflow;
    mesa_eflow_conf_t     eflow;
    mesa_voi_conf_t       voi_cfg;

    down_voi_idx = 0;   /* Using the first Down-VOI */
    up_voi_idx = 0;     /* Using the first Up-VOI */

    /* Allocate and configure the Down VOI ingress flow ID */
    (void)mesa_iflow_alloc(NULL, &down_voi_iflow_id);
    (void)mesa_iflow_conf_get(NULL, down_voi_iflow_id, &iflow);
    iflow.voi_idx = down_voi_idx;
    (void)mesa_iflow_conf_set(NULL, down_voi_iflow_id, &iflow);

    /* Allocate the Up VOI ingress flow ID */
    (void)mesa_iflow_alloc(NULL, &up_voi_iflow_id);

    /* Allocate and configure the Up VOI egress flow ID */
    (void)mesa_eflow_alloc(NULL, &up_voi_eflow_id);
    (void)mesa_eflow_conf_get(NULL, up_voi_eflow_id, &eflow);
    eflow.voi_idx = up_voi_idx;
    (void)mesa_eflow_conf_set(NULL, up_voi_eflow_id, &eflow);

    /* Initialize and add an OAM ingress Down VOI pointing VCE rule */
    (void)mesa_vce_init(NULL, MESA_VCE_TYPE_ETYPE, &vce);
    mesa_port_list_set(&vce.key.port_list, network_port_0, 1);  /* Match on ingress port as the Down MEP residence network port */
    vce.key.tag.vid.value = cl_vid;                             /* Match on the VID for this VLAN */
    vce.key.tag.vid.mask = 0xFFFF;
    vce.key.tag.tagged = MESA_VCAP_BIT_1;                       /* Match on tagged frames */
    vce.key.tag.s_tag = MESA_VCAP_BIT_0;                        /* Match on C-tagged frames */
    vce.key.type = MESA_VCE_TYPE_ETYPE;                         /* Match on Ether type frames */
    vce.key.frame.etype.etype.value[0] = 0x89;                  /* Match on Ethernet OAM frames - 0x8902 */
    vce.key.frame.etype.etype.value[1] = 0x02;                  /* Match on Ethernet OAM frames - 0x8902 */
    vce.key.frame.etype.etype.mask[0] = 0xFF;
    vce.key.frame.etype.etype.mask[1] = 0xFF;
    vce.key.frame.etype.mel.value = (0x01 << meg_level) - 1;    /* Matching MEG level mask is calculated. This will match on level == 'meg_level' */
    vce.key.frame.etype.mel.mask = (0x01 << meg_level) - 1;
    vce.action.oam_detect = MESA_OAM_DETECT_SINGLE_TAGGED;      /* Mark frames as OAM */
    vce.action.flow_id = down_voi_iflow_id;                     /* Generate the Down VOI ingress flow */
    (void)mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce);

    /* Add an OAM ingress Up VOI OAM marking VCE rule on VLAN ports "in front of" the VLAN Up VOI. */
    /* We inherits most VCE configuration from previous VCE add */
    vce.key.frame.etype.mel.mask = 0;         /* Match on all MEG levels */
    vce.action.flow_id = up_voi_iflow_id;     /* Generate the Down VOI ingress flow */
    for (i = network_port_1; i <= network_port_2; ++i)
    {
        mesa_port_list_clear(&vce.key.port_list);
        mesa_port_list_set(&vce.key.port_list, i, 1);
        (void)mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce);
    }

    /* Initialize and add an OAM egress VOI pointing TCE rule */
    (void)mesa_tce_init(NULL, &tce);
    mesa_port_list_set(&tce.key.port_list, network_port_0, 1);             /* Match on egress port as the Down VOI residence network port */
    tce.key.vid = cl_vid;                              /* Match on classified VID */
    tce.action.flow_id = up_voi_eflow_id;                 /* Generate egress flow id */
    (void)mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce);

    /* Configure the VLAN Down and Up VOI */
    memset(&voi_cfg, 0, sizeof(voi_cfg));
    voi_cfg.enable = TRUE;
    voi_cfg.unicast_mac = unicast_addr;
    voi_cfg.meg_level = meg_level;
    voi_cfg.lbm_cpu_redir = TRUE;
    voi_cfg.ltm_cpu_redir = TRUE;
    voi_cfg.raps_handling = MESA_OAM_RAPS_HANDLING_NONE;
    (void)mesa_voi_conf_set(NULL, down_voi_idx, &voi_cfg);
    (void)mesa_voi_conf_set(NULL, up_voi_idx, &voi_cfg);
}

void vlan_mep_ccm_config(mesa_bool_t enable)
{
    mesa_voe_cc_conf_t voe_cc_cfg;

    /* Configure the VOE CC feature */
    memset(&voe_cc_cfg, 0, sizeof(voe_cc_cfg));
    voe_cc_cfg.enable   = TRUE;
    voe_cc_cfg.cpu_copy = MESA_OAM_CPU_COPY_AUTO;
    voe_cc_cfg.seq_no_update = TRUE;
    voe_cc_cfg.expected_period = MESA_VOE_CCM_PERIOD_1_SEC;
    voe_cc_cfg.expected_priority = priority;
    memcpy(voe_cc_cfg.expected_megid, meg_id, sizeof(voe_cc_cfg.expected_megid));
    voe_cc_cfg.expected_peer_mepid = peer_mep_id;

    (void)mesa_voe_cc_conf_set(NULL, vlan_voe_idx, &voe_cc_cfg);

    /* Enable CCM events */
    (void)mesa_voe_event_mask_set(NULL, vlan_voe_idx, MESA_VOE_EVENT_MASK_CCM_LOC |
                                                      MESA_VOE_EVENT_MASK_CCM_MEG_ID |
                                                      MESA_VOE_EVENT_MASK_CCM_MEP_ID |
                                                      MESA_VOE_EVENT_MASK_CCM_PERIOD |
                                                      MESA_VOE_EVENT_MASK_CCM_PRIORITY |
                                                      MESA_VOE_EVENT_MASK_CCM_RX_RDI |
                                                      MESA_VOE_EVENT_MASK_CCM_ZERO_PERIOD |
                                                      MESA_VOE_EVENT_MASK_CCM_MEG_LEVEL, TRUE);
}

void vlan_mep_ccm_transmit(mesa_bool_t single)
{
    uint8_t                        mc_mac[6] = {0x01,0x80,0xC2,0x00,0x00,0x30};
    uint8_t                        frame[6+6+2+80];    // Room for max size PDU (CCM)
    mesa_packet_tx_info_t          tx_info;
    mesa_packet_tx_ifh_t           ifh;
    mesa_afi_slow_inj_alloc_cfg_t  afi_cfg;
    mesa_afi_slowid_t              afi_id;
    mesa_afi_slow_inj_start_cfg_t  afi_start_cfg;

    // Create CCM frame
    memset(frame, 0, sizeof(frame));
    memcpy(&frame[0], mc_mac, 6);
    memcpy(&frame[6], unicast_addr.addr, 6);
    frame[12] = 0x89;
    frame[13] = 0x02;
    frame[14] = meg_level << 5;
    frame[15] = 1;           // CCM opcode
    frame[16] = 4;           // flags = one frame per sec
    frame[17] = 70;
    frame[22] = mep_id >> 8;  // MEP-ID
    frame[23] = mep_id;
    memcpy(&frame[24], meg_id, sizeof(meg_id));

    /* initialize 'tx_info' */
    tx_info.tag.vid         = cl_vid;
    tx_info.tag.pcp         = priority;
    tx_info.tag.dei         = 0;
    tx_info.cos             = priority;
    tx_info.cosid           = priority;
    tx_info.dp              = 0;
    tx_info.pdu_offset      = 14;
    tx_info.oam_type        = MESA_PACKET_OAM_TYPE_CCM;
    tx_info.iflow_id        = MESA_IFLOW_ID_NONE;
    tx_info.pipeline_pt     = MESA_PACKET_PIPELINE_PT_REW_IN_VOE;
    tx_info.dst_port_mask   = (1ULL << network_port_0);
    tx_info.switch_frm      = FALSE;
    tx_info.masquerade_port = MESA_PORT_NO_NONE;

    if (single) {   // Transmit the frame as a single - not AFI
        (void)mesa_packet_tx_hdr_compile(NULL, &tx_info, &ifh);        // Compile the IFH
        (void)mesa_packet_tx_frame(NULL, &ifh, frame, (6+6+2+75));     // Transmit the frame as a single - not AFI
    } else {        // Transmit the frame using AFI
        // Allocate the AFI
        memset(&afi_cfg, 0, sizeof(afi_cfg));
        afi_cfg.port_no            = network_port_0;
        afi_cfg.masquerade_port_no = MESA_PORT_NO_NONE;
        afi_cfg.prio               = tx_info.cos;
        (void)mesa_afi_slow_inj_alloc(NULL, &afi_cfg, &afi_id);

        // Send the packet to the AFI
        tx_info.afi_id = afi_id;    // Indicate that this frame is going to AFI
        (void)mesa_packet_tx_hdr_compile(NULL, &tx_info, &ifh);        // Compile the IFH
        (void)mesa_packet_tx_frame(NULL, &ifh, frame, (6+6+2+75));     // Transmit the frame to AFI

        // Assure that the frame is reaching the AFI
        if (mesa_afi_slow_inj_frm_hijack(NULL, afi_id) == MESA_RC_OK) {
            // Start the AFI
            memset(&afi_start_cfg, 0, sizeof(afi_start_cfg));
            afi_start_cfg.fph                = 1 * 60 * 60;     // One CCM frame per second in frames per hour
            afi_start_cfg.jitter_mode        = 0;               // No injection jitter required
            afi_start_cfg.first_frame_urgent = FALSE;           // First frame is not urgent
            (void)mesa_afi_slow_inj_start(NULL, afi_id, &afi_start_cfg);
        }
    }
}

void vlan_voi_lbr_transmit(uint8_t *lbm,  uint32_t length,  uint8_t rx_prio,  mesa_voi_idx_t rx_voi_idx)
{
    uint8_t                        frame[6+6+2+80];    // Room for max size PDU (CCM)
    mesa_packet_tx_info_t          tx_info;
    mesa_packet_tx_ifh_t           ifh;
    mesa_bool_t                    down;

    down = (rx_voi_idx == down_voi_idx) ? TRUE : FALSE;

    // Convert LBM into LBR frame
    memcpy(&frame[0], &frame[6], 6);    /* DMAC = SMAC */
    memcpy(&frame[6], unicast_addr.addr, 6);  /* SMAC = Unicast MAC of this instance */
    frame[15] = 2;           // LBR opcode

    /* initialize 'tx_info' */
    tx_info.tag.vid         = cl_vid;
    tx_info.tag.pcp         = rx_prio;
    tx_info.tag.dei         = 0;
    tx_info.cos             = rx_prio;
    tx_info.cosid           = rx_prio;
    tx_info.dp              = 0;
    tx_info.pdu_offset      = 14;
    tx_info.oam_type        = MESA_PACKET_OAM_TYPE_LBR;
    tx_info.pipeline_pt     = down ? MESA_PACKET_PIPELINE_PT_REW_IN_VOI : MESA_PACKET_PIPELINE_PT_ANA_IN_VOI;
    tx_info.dst_port_mask   = down ? (1ULL << network_port_0) : 0;
    tx_info.switch_frm      = down ? FALSE : TRUE;
    tx_info.masquerade_port = down ? MESA_PORT_NO_NONE : network_port_0;

    (void)mesa_packet_tx_hdr_compile(NULL, &tx_info, &ifh);        // Compile the IFH
    (void)mesa_packet_tx_frame(NULL, &ifh, frame, (6+6+2+75));     // Transmit the frame as a single - not AFI
}

void vlan_mep_ccm_receive(uint8_t *packet,  uint32_t length)
{
    mesa_packet_rx_meta_t meta;
    mesa_packet_rx_info_t rx_info;
    uint8_t               *ifh, *frame, *fcs, *etype, *pdu;
    uint32_t              ifh_offset, frame_offset, fcs_length, period;

    fcs_length = 4;    // FSC length. Assuming the packet is received with FSC
    ifh_offset = 0;    // IFH offset. Assuming there is no prefix before IFH in packet. IFH starting position depends on internal or external CPU and NPI port configuration
    frame_offset = ifh_offset + MESA_CAP(MESA_CAP_PACKET_RX_IFH_SIZE);  // Frame offset

    ifh = &packet[ifh_offset];          // Pointer to IFH
    frame = &packet[frame_offset];      // Pointer to frame
    fcs = &packet[length - fcs_length]; // Pointer to FSC
    etype = &frame[16];                 // Pointer to ETYPE
    pdu = &frame[6+6+2];                // Pointer to PDU

    // Build 'meta' structure.
    memset(&meta, 0, sizeof(meta));
    meta.length = length - frame_offset - fcs_length;   // Calculate the length of the actual frame
    meta.fcs = (fcs[0] << 24) | (fcs[1] << 16) | (fcs[2] << 8) | (fcs[3] << 0);
    meta.etype = (etype[0] << 8) | (etype[1] << 0);

    (void)mesa_packet_rx_hdr_decode(NULL, &meta, ifh, &rx_info);  // Decode the rx_info

    if ((rx_info.iflow_id == voe_iflow_id) && (pdu[1] == 1)) {  // This is a CCM frame for this VLAN Down MEP instance
        period = pdu[2] & 0x07;
        if (longest_ccm_period < period) {   // Calculate to longest received CCM period
            longest_ccm_period = period;
        }
    }
}

void vlan_voi_lbm_receive(uint8_t *packet,  uint32_t length)
{
    mesa_packet_rx_meta_t meta;
    mesa_packet_rx_info_t rx_info;
    uint8_t               *ifh, *frame, *fcs, *etype, *pdu;
    uint32_t              ifh_offset, frame_offset, fcs_length;
    mesa_voi_idx_t        rx_voi_idx = MESA_VOI_IDX_NONE;

    fcs_length = 4;    // FSC length. Assuming the packet is received with FSC
    ifh_offset = 0;    // IFH offset. Assuming there is no prefix before IFH in packet. IFH starting position depends on internal or external CPU and NPI port configuration
    frame_offset = ifh_offset + MESA_CAP(MESA_CAP_PACKET_RX_IFH_SIZE);  // Frame offset

    ifh = &packet[ifh_offset];          // Pointer to IFH
    frame = &packet[frame_offset];      // Pointer to frame
    fcs = &packet[length - fcs_length]; // Pointer to FSC
    etype = &frame[16];                 // Pointer to ETYPE
    pdu = &frame[6+6+2];                // Pointer to PDU

    // Build 'meta' structure.
    memset(&meta, 0, sizeof(meta));
    meta.length = length - frame_offset - fcs_length;   // Calculate the length of the actual frame
    meta.fcs = (fcs[0] << 24) | (fcs[1] << 16) | (fcs[2] << 8) | (fcs[3] << 0);
    meta.etype = (etype[0] << 8) | (etype[1] << 0);

    (void)mesa_packet_rx_hdr_decode(NULL, &meta, ifh, &rx_info);              // Decode the rx_info

    if ((rx_info.port_no == network_port_0) && (rx_info.iflow_id == down_voi_iflow_id)) { // Frame received on Down VOI port and ingress flow id
        rx_voi_idx = down_voi_idx;
    } else if ((rx_info.port_no == network_port_0) && (rx_info.iflow_id == up_voi_iflow_id)) {  // Frame received on Up VOI port and vid and no ingress flow id
        rx_voi_idx = up_voi_idx;
    }

    if ((rx_voi_idx != MESA_IFLOW_ID_NONE) && (pdu[1] == 3)) {  // This is a LBM frame for 'rx_voi_idx' instance
        vlan_voi_lbr_transmit(frame, meta.length, rx_info.tag.pcp, rx_voi_idx);
    }
}

void expired_unm_timer()
{
    dUNM = FALSE;     // Clear the UNM defect as no Unexpected MEP-ID is received
}

void start_unm_timer(uint32_t period)
{
    // Start the UNM defect timer with 3,5 period
}

void stop_unm_timer()
{
    // Stop the UNM defect timer
}

void vlan_mep_event_handle()
{
    uint32_t               voe_cnt = MESA_CAP(MESA_CAP_VOP_VOE_CNT), voe_event_array_size, *voe_active;
    uint32_t               event_mask;
    mesa_voe_idx_t         voe_idx;
    mesa_voe_cc_status_t   cc_status;

    // Allocate 'voe_active' array
    voe_event_array_size = MESA_CAP(MESA_CAP_VOP_EVENT_ARRAY_SIZE);
    voe_active = (uint32_t *)malloc(voe_event_array_size);
    if (voe_active == NULL) {
        return;
    }

    (void)mesa_voe_event_active_get(NULL, voe_event_array_size, voe_active);

    for (voe_idx = 0; voe_idx < voe_cnt; ) {
        if (!(voe_active[voe_idx / 32])) {    // Check for new event for this 32 MEP instances
            voe_idx += 32;
            continue;
        }
        if (!(voe_active[voe_idx / 32] & (1 << (voe_idx % 32)))) {  // Check for new event on this MEP instance
            voe_idx++;
            continue;
        }
        (void)mesa_voe_event_get(NULL, voe_idx, &event_mask);
        (void)mesa_voe_cc_status_get(NULL, voe_idx, &cc_status);

        dLOC = cc_status.loc;    // 'loc' is dLOC according to G.8021. Take as is.
        if (MESA_CAP(MESA_CAP_VOP_CCM_DEFECT)) {                  // Check if this platform supports CCM defects according to G.8021.
            dUNM = cc_status.mep_id_unexp;   // 'mep_id_unexp' is dUNM according to G.8021. Take as is.
        } else {
            if (event_mask & MESA_VOE_EVENT_MASK_CCM_MEP_ID) {     // Check for 'mep_id_unexp' event. This is not dUNM according to G.8021. Must be calculated.
                dUNM = TRUE;                              // dUNM must be unconditionally active now as event indicate status raising or falling edge. 
                if (!cc_status.mep_id_unexp) {
                    start_unm_timer(longest_ccm_period);  // Expected MEP-ID is received - so start the defect clear timer
                } else {
                    stop_unm_timer();                     // Unexpected MEP-ID is received - so stop the defect clear timer
                }
            }
        }
    }

    free(voe_active);
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


