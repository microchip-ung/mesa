// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define MEPA_RC(expr) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) return __rc__; }
// Trace macros
#define T_D(data, grp, format, ...) if (data->trace_func) data->trace_func(grp, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(data, grp, format, ...) if (data->trace_func) data->trace_func(grp, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(data, grp, format, ...) if (data->trace_func) data->trace_func(grp, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(data, grp, format, ...) if (data->trace_func) data->trace_func(grp, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);

#define true 1
#define false 0

#define TS_ENGINES_PER_PORT 3
#define TS_FLOWS_PER_ENG 8
#define MAX_PORTS_PER_PHY 4
#define TS_ACTIONS_PER_ENGINE 2

typedef enum {
    PHY_CAP_1G,
    PHY_CAP_10G
} phy_cap_t;

// Common configuration from 'mepa_ts_classifier_eth_t' && 'mepa_ts_classifier_ip_t' which is shared by all flows of engine.
typedef struct {
    // ETH
    mepa_bool_t pbb_en;
    uint16_t tpid;
    uint16_t etype;
    // IP
    uint8_t ip_mode;
    uint16_t sport_val;
    uint16_t sport_mask;
    uint16_t dport_val;
    uint16_t dport_mask;
} phy_ts_eng_comm_t;
// flow configuration from 'mepa_ts_classifier_eth_t' && 'mepa_ts_classifier_ip_t' which is unique to each flow of engine.
typedef struct {
    // ETH
    mepa_ts_mac_match_mode_t    mac_match_mode;
    mepa_ts_mac_match_select_t  mac_match_select;
    uint8_t                     mac_addr[6];
    mepa_bool_t                 vlan_check;
    uint8_t                     num_tag;
    mepa_ts_match_uint16_t      outer_tag;
    mepa_ts_match_uint16_t      inner_tag;

    // IP
    mepa_ts_ip_match_select_t   ip_match_mode;
    mepa_ts_ip_network_t        ip_addr;

    // Enabling info for flow
    mepa_bool_t                 flow_en;
    mepa_bool_t                 alt_port_en; // flow enabled for alternate or not.
} phy_ts_eng_flow_t;

typedef struct {
    mepa_ts_pkt_encap_t      pkt_encap_type;
    uint8_t                  clock_id;
    mepa_bool_t              eng_enable; // engine enable
    phy_ts_eng_comm_t        comm;
    phy_ts_eng_flow_t        flow[TS_FLOWS_PER_ENG];
    mepa_ts_ptp_clock_conf_t clk[TS_ACTIONS_PER_ENGINE];
} phy_ts_engine_t;

typedef struct {
    mepa_bool_t          dly_req_recv_10byte_ts;
} phy_ts_data_t;

typedef struct {
    mepa_port_no_t port_no;
    mepa_port_interface_t mac_if;
    phy_cap_t cap;
    phy_ts_data_t ts;
    mepa_trace_func_t trace_func;
    mepa_bool_t   ts_base_detected;
    mepa_device_t *base_dev;
    mepa_device_t *other_dev[MAX_PORTS_PER_PHY]; // utmost 3 other ports would exist on phy.
    mepa_port_no_t all_phy_ports[MAX_PORTS_PER_PHY];
    mepa_device_t *ts_base_dev;
    mepa_device_t *ts_alt_dev;
} phy_data_t;
