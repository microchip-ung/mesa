// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "mscc/ethernet/board/api.h"

#include "meba_aux.h"
// Declare all the terminals in the graph

//      NAME                             TYPE                    DEV-ID   INDEX
#define eth_port_0                       MESA_SYNCE_DEV_PORT(         0,      0)
#define eth_port_1                       MESA_SYNCE_DEV_PORT(         1,      0)
#define eth_port_2                       MESA_SYNCE_DEV_PORT(         2,      0)
#define eth_port_3                       MESA_SYNCE_DEV_PORT(         3,      0)
#define eth_port_4                       MESA_SYNCE_DEV_PORT(         4,      0)
#define eth_port_5                       MESA_SYNCE_DEV_PORT(         5,      0)
#define eth_port_6                       MESA_SYNCE_DEV_PORT(         6,      0)
#define eth_port_7                       MESA_SYNCE_DEV_PORT(         7,      0)
#define eth_port_8                       MESA_SYNCE_DEV_PORT(         8,      0)
#define eth_port_9                       MESA_SYNCE_DEV_PORT(         9,      0)
#define eth_port_10                      MESA_SYNCE_DEV_PORT(        10,      0)
#define eth_port_11                      MESA_SYNCE_DEV_PORT(        11,      0)
#define eth_port_12                      MESA_SYNCE_DEV_PORT(        12,      0)
#define eth_port_13                      MESA_SYNCE_DEV_PORT(        13,      0)
#define eth_port_14                      MESA_SYNCE_DEV_PORT(        14,      0)
#define eth_port_15                      MESA_SYNCE_DEV_PORT(        15,      0)
#define eth_port_16                      MESA_SYNCE_DEV_PORT(        16,      0)
#define eth_port_17                      MESA_SYNCE_DEV_PORT(        17,      0)
#define eth_port_18                      MESA_SYNCE_DEV_PORT(        18,      0)
#define eth_port_19                      MESA_SYNCE_DEV_PORT(        19,      0)
#define eth_port_20                      MESA_SYNCE_DEV_PORT(        20,      0)
#define eth_port_21                      MESA_SYNCE_DEV_PORT(        21,      0)
#define eth_port_22                      MESA_SYNCE_DEV_PORT(        22,      0)
#define eth_port_23                      MESA_SYNCE_DEV_PORT(        23,      0)
#define eth_port_24                      MESA_SYNCE_DEV_PORT(        24,      0)
#define eth_port_25                      MESA_SYNCE_DEV_PORT(        25,      0)
#define eth_port_26                      MESA_SYNCE_DEV_PORT(        26,      0)
#define eth_port_27                      MESA_SYNCE_DEV_PORT(        27,      0)
#define eth_port_28                      MESA_SYNCE_DEV_PORT(        28,      0)
#define eth_port_29                      MESA_SYNCE_DEV_PORT(        29,      0)
#define eth_port_30                      MESA_SYNCE_DEV_PORT(        30,      0)
#define eth_port_31                      MESA_SYNCE_DEV_PORT(        31,      0)
#define eth_port_32                      MESA_SYNCE_DEV_PORT(        32,      0)
#define eth_port_33                      MESA_SYNCE_DEV_PORT(        33,      0)
#define eth_port_34                      MESA_SYNCE_DEV_PORT(        34,      0)
#define eth_port_35                      MESA_SYNCE_DEV_PORT(        35,      0)
#define eth_port_36                      MESA_SYNCE_DEV_PORT(        36,      0)
#define eth_port_37                      MESA_SYNCE_DEV_PORT(        37,      0)
#define eth_port_38                      MESA_SYNCE_DEV_PORT(        38,      0)
#define eth_port_39                      MESA_SYNCE_DEV_PORT(        39,      0)
#define eth_port_40                      MESA_SYNCE_DEV_PORT(        40,      0)
#define eth_port_41                      MESA_SYNCE_DEV_PORT(        41,      0)
#define eth_port_42                      MESA_SYNCE_DEV_PORT(        42,      0)
#define eth_port_43                      MESA_SYNCE_DEV_PORT(        43,      0)
#define eth_port_44                      MESA_SYNCE_DEV_PORT(        44,      0)
#define eth_port_45                      MESA_SYNCE_DEV_PORT(        45,      0)
#define eth_port_46                      MESA_SYNCE_DEV_PORT(        46,      0)
#define eth_port_47                      MESA_SYNCE_DEV_PORT(        47,      0)
#define eth_port_48                      MESA_SYNCE_DEV_PORT(        48,      0)
#define eth_port_49                      MESA_SYNCE_DEV_PORT(        49,      0)
#define eth_port_50                      MESA_SYNCE_DEV_PORT(        50,      0)
#define eth_port_51                      MESA_SYNCE_DEV_PORT(        51,      0)
#define eth_port_52                      MESA_SYNCE_DEV_PORT(        52,      0)
#define eth_port_53                      MESA_SYNCE_DEV_PORT(        53,      0)
#define eth_port_54                      MESA_SYNCE_DEV_PORT(        54,      0)
#define eth_port_55                      MESA_SYNCE_DEV_PORT(        55,      0)
#define eth_port_56                      MESA_SYNCE_DEV_PORT(        56,      0)

#define station_clock_fireant_20             MESA_SYNCE_DEV_CLOCK_IN(    21,      0)
#define station_clock_fireant_56             MESA_SYNCE_DEV_CLOCK_IN(    58,      0)

#define switch_mux_port_in_0              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 0)
#define switch_mux_port_in_1              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 1)
#define switch_mux_port_in_2              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 2)
#define switch_mux_port_in_3              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 3)
#define switch_mux_port_in_4              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 4)
#define switch_mux_port_in_5              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 5)
#define switch_mux_port_in_6              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 6)
#define switch_mux_port_in_7              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 7)
#define switch_mux_port_in_8              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 8)
#define switch_mux_port_in_9              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 9)
#define switch_mux_port_in_10             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 10)
#define switch_mux_port_in_11             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 11)
#define switch_mux_port_in_12             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 12)
#define switch_mux_port_in_13             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 13)
#define switch_mux_port_in_14             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 14)
#define switch_mux_port_in_15             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 15)
#define switch_mux_port_in_16             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 16)
#define switch_mux_port_in_17             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 17)
#define switch_mux_port_in_18             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 18)
#define switch_mux_port_in_19             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 19)

#define switch_mux_port_out_0             MESA_SYNCE_DEV_MUX_SWITCH(   600,      0)
#define switch_mux_port_out_1             MESA_SYNCE_DEV_MUX_SWITCH(   600,      1)
#define switch_mux_port_out_2             MESA_SYNCE_DEV_MUX_SWITCH(   600,      2)
#define switch_mux_port_out_3             MESA_SYNCE_DEV_MUX_SWITCH(   600,      3)
#define dpll_port_0                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 0)
#define dpll_port_1                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 1)
#define dpll_port_2                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 2)
#define dpll_port_3                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 3)
#define dpll_port_4                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 4)

static const meba_synce_graph_element_t synce_graph_elements_fireant_24_w_zls30772_board[] = {    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      switch_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      switch_mux_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     switch_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     switch_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                     switch_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                     switch_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_14,                     switch_mux_port_in_14),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_15,                     switch_mux_port_in_15),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_16,                     switch_mux_port_in_16),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_17,                     switch_mux_port_in_17),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_18,                     switch_mux_port_in_18),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_19,                     switch_mux_port_in_19),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_fireant_20,        dpll_port_4),
};

static const meba_synce_terminal_attr_t attr_fireant_24_w_zls30772_board[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,   2),
    MESA_SYNCE_ATTR(dpll_port_4,           MEBA_ATTR_CLOCK_ID,   3),

    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
};
mesa_rc meba_synce_graph_get(meba_inst_t inst, const meba_synce_graph_t **const g)
{
    static meba_synce_graph_t synce_graph;
    meba_synce_clock_hw_id_t dpll_type;

    if (meba_synce_spi_if_get_dpll_type(inst, &dpll_type) != MESA_RC_OK) {
        T_E(inst, "Failure probing DPLL type.");
        return MESA_RC_NOT_IMPLEMENTED;
    } else {
        if (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30771 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772 ||
                dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30773) {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_fireant_24_w_zls30772_board);
            synce_graph.graph = synce_graph_elements_fireant_24_w_zls30772_board;
            synce_graph.attr = attr_fireant_24_w_zls30772_board;
            synce_graph.attr_length = MEBA_ARRSZ(attr_fireant_24_w_zls30772_board);
        }
        *g = &synce_graph;
    }

    return MESA_RC_OK;

}

mesa_rc meba_synce_mux_set(meba_inst_t  inst,
                           uint32_t     dev_id,
                           uint32_t     input,
                           uint32_t     output)
{
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static meba_api_synce_t public_functions = {
#define X(name) . name = name,
    MEBA_LIST_OF_API_SYNCE_CALLS
#undef X
};

meba_api_synce_t *meba_synce_get()
{
    return &public_functions;
}
