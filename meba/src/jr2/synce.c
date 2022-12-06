// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "microchip/ethernet/board/api.h"

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

#define station_clock_jr2_24             MESA_SYNCE_DEV_CLOCK_IN(    29,      0)
#define station_clock_jr2_48             MESA_SYNCE_DEV_CLOCK_IN(    51,      0)
#define station_clock_serval2            MESA_SYNCE_DEV_CLOCK_IN(    15,      0)

#define phy_mux_0_port_in_0              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_0_port_in_1              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_0_port_in_2              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_0_port_in_3              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_0_port_in_4              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 4)
#define phy_mux_0_port_in_5              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 5)
#define phy_mux_0_port_in_6              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 6)
#define phy_mux_0_port_in_7              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 7)
#define phy_mux_0_port_in_8              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 8)
#define phy_mux_0_port_in_9              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 9)
#define phy_mux_0_port_in_10             MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 10)
#define phy_mux_0_port_in_11             MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 11)
#define phy_mux_0_port_out_0             MESA_SYNCE_DEV_MUX_PHY(    100,      0)
#define phy_mux_0_port_out_1             MESA_SYNCE_DEV_MUX_PHY(    100,      1)

#define phy_mux_1_port_in_0              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_1_port_in_1              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_1_port_in_2              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_1_port_in_3              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_1_port_in_4              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 4)
#define phy_mux_1_port_in_5              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 5)
#define phy_mux_1_port_in_6              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 6)
#define phy_mux_1_port_in_7              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 7)
#define phy_mux_1_port_in_8              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 8)
#define phy_mux_1_port_in_9              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 9)
#define phy_mux_1_port_in_10             MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 10)
#define phy_mux_1_port_in_11             MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 11)
#define phy_mux_1_port_out_0             MESA_SYNCE_DEV_MUX_PHY(    200,      0)
#define phy_mux_1_port_out_1             MESA_SYNCE_DEV_MUX_PHY(    200,      1)

#define phy_mux_2_port_in_0              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_2_port_in_1              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_2_port_in_2              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_2_port_in_3              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_2_port_in_4              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 4)
#define phy_mux_2_port_in_5              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 5)
#define phy_mux_2_port_in_6              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 6)
#define phy_mux_2_port_in_7              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 7)
#define phy_mux_2_port_in_8              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 8)
#define phy_mux_2_port_in_9              MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 9)
#define phy_mux_2_port_in_10             MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 10)
#define phy_mux_2_port_in_11             MESA_SYNCE_DEV_MUX_PHY(    300,      MESA_SYNCE_DEV_INPUT | 11)
#define phy_mux_2_port_out_0             MESA_SYNCE_DEV_MUX_PHY(    300,      0)
#define phy_mux_2_port_out_1             MESA_SYNCE_DEV_MUX_PHY(    300,      1)

#define phy_mux_3_port_in_0              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_3_port_in_1              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_3_port_in_2              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_3_port_in_3              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_3_port_in_4              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 4)
#define phy_mux_3_port_in_5              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 5)
#define phy_mux_3_port_in_6              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 6)
#define phy_mux_3_port_in_7              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 7)
#define phy_mux_3_port_in_8              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 8)
#define phy_mux_3_port_in_9              MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 9)
#define phy_mux_3_port_in_10             MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 10)
#define phy_mux_3_port_in_11             MESA_SYNCE_DEV_MUX_PHY(     400,      MESA_SYNCE_DEV_INPUT | 11)
#define phy_mux_3_port_out_0             MESA_SYNCE_DEV_MUX_PHY(     400,      0)
#define phy_mux_3_port_out_1             MESA_SYNCE_DEV_MUX_PHY(     400,      1)

#define switch_mux_port_in_0             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 0)
#define switch_mux_port_in_1             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 1)
#define switch_mux_port_in_2             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 2)
#define switch_mux_port_in_3             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 3)
#define switch_mux_port_in_4             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 4)
#define switch_mux_port_in_5             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 5)
#define switch_mux_port_in_6             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 6)
#define switch_mux_port_in_7             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 7)
#define switch_mux_port_in_8             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 8)
#define switch_mux_port_in_9             MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 9)
#define switch_mux_port_in_10            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 10)
#define switch_mux_port_in_11            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 11)
#define switch_mux_port_in_12            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 12)
#define switch_mux_port_in_13            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 13)
#define switch_mux_port_in_14            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 14)
#define switch_mux_port_in_15            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 15)
#define switch_mux_port_in_16            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 16)
#define switch_mux_port_in_17            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 17)
#define switch_mux_port_in_18            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 18)
#define switch_mux_port_in_19            MESA_SYNCE_DEV_MUX_SWITCH(  500,      MESA_SYNCE_DEV_INPUT | 19)
#define switch_mux_port_out_0            MESA_SYNCE_DEV_MUX_SWITCH(  500,      0)
#define switch_mux_port_out_1            MESA_SYNCE_DEV_MUX_SWITCH(  500,      1)
#define switch_mux_port_out_2            MESA_SYNCE_DEV_MUX_SWITCH(  500,      2)
#define switch_mux_port_out_3            MESA_SYNCE_DEV_MUX_SWITCH(  500,      3)

#define board_mux_port_in_2              MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 2)
#define board_mux_port_in_3              MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 3)
#define board_mux_port_in_4              MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 4)
#define board_mux_port_in_5              MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 5)
#define board_mux_port_in_6              MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 6)
#define board_mux_port_in_7              MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 7)
#define board_mux_port_in_8              MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 8)
#define board_mux_port_in_9              MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 9)
#define board_mux_port_in_10             MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 10)
#define board_mux_port_in_11             MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 11)
#define board_mux_port_in_12             MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 12)
#define board_mux_port_in_13             MESA_SYNCE_DEV_MUX_BOARD(   600,      MESA_SYNCE_DEV_INPUT | 13)
#define board_mux_port_out_0             MESA_SYNCE_DEV_MUX_BOARD(   600,      0)
#define board_mux_port_out_1             MESA_SYNCE_DEV_MUX_BOARD(   600,      1)

#define dpll_port_0                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 0)
#define dpll_port_1                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 1)
#define dpll_port_2                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 2)
#define dpll_port_3                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 3)
#define dpll_port_4                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 4)
#define dpll_port_5                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 5)
#define dpll_port_6                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 6)
#define dpll_port_7                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 7)

static const meba_synce_graph_element_t synce_graph_elements_jr2_24_board[] = {          // Note: This graph is only used when DPLL != zls30363. For DPLL == zls30363 see graph further below.
    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      phy_mux_1_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      phy_mux_1_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      phy_mux_1_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      phy_mux_1_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                     switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                     switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_14,                     switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_15,                     switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_16,                     switch_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_17,                     switch_mux_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_18,                     switch_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_19,                     switch_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_20,                     switch_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_21,                     switch_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_22,                     switch_mux_port_in_14),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_23,                     switch_mux_port_in_15),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_24,                     switch_mux_port_in_16),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_25,                     switch_mux_port_in_17),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_26,                     switch_mux_port_in_18),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_27,                     switch_mux_port_in_19),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_0,           board_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_1,           board_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           board_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           board_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_0,            board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_1,            board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_0,            board_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_1,            board_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_0,            dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_1,            dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_jr2_24,            dpll_port_7),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_2,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_4,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_10,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_12,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_3,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_5,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_11,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_13,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_2,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_3,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_4,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_5,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_6,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_7,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_8,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_9,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_10,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_11,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_12,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_13,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_14,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_15,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_16,           switch_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_17,           switch_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_18,           switch_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_19,           switch_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_2,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_3,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_4,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_5,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_6,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_7,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_8,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_9,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_10,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_11,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_12,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_13,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_14,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_15,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_16,           switch_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_17,           switch_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_18,           switch_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_19,           switch_mux_port_out_1)
};

static const meba_synce_graph_element_t synce_graph_elements_jr2_24_w_zls30363_board[] = {          // Note: This graph is only used when DPLL == zls30363. For DPLL != zls30363 see graph above.
    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      phy_mux_1_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      phy_mux_1_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      phy_mux_1_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      phy_mux_1_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                     switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                     switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_14,                     switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_15,                     switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_16,                     switch_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_17,                     switch_mux_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_18,                     switch_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_19,                     switch_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_20,                     switch_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_21,                     switch_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_22,                     switch_mux_port_in_14),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_23,                     switch_mux_port_in_15),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_24,                     switch_mux_port_in_16),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_25,                     switch_mux_port_in_17),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_26,                     switch_mux_port_in_18),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_27,                     switch_mux_port_in_19),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_0,           board_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_1,           board_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           board_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           board_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_0,            board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_1,            board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_0,            board_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_1,            board_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_0,            dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_1,            dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_jr2_24,            dpll_port_7),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_2,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_4,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_10,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_12,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_3,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_5,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_11,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_13,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_2,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_3,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_4,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_5,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_6,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_7,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_8,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_9,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_10,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_11,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_12,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_13,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_14,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_15,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_16,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_17,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_18,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_19,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_2,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_3,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_4,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_5,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_6,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_7,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_8,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_9,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_10,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_11,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_12,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_13,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_14,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_15,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_16,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_17,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_18,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_19,           switch_mux_port_out_3)
};

static const meba_synce_graph_element_t synce_graph_elements_jr2_24_w_zls30772_board[] = {          // Note: This graph is only used when DPLL == zls30772. For DPLL != zls30772 see graphs above.
    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      phy_mux_1_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      phy_mux_1_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      phy_mux_1_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      phy_mux_1_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                     switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                     switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_14,                     switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_15,                     switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_16,                     switch_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_17,                     switch_mux_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_18,                     switch_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_19,                     switch_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_20,                     switch_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_21,                     switch_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_22,                     switch_mux_port_in_14),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_23,                     switch_mux_port_in_15),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_24,                     switch_mux_port_in_16),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_25,                     switch_mux_port_in_17),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_26,                     switch_mux_port_in_18),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_27,                     switch_mux_port_in_19),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_0,           board_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_1,           board_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           board_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           board_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_0,            board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_1,            board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_0,            board_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_1,            board_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_0,            dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_1,            dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_jr2_24,            dpll_port_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_2,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_4,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_10,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_12,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_3,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_5,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_11,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_13,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_2,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_3,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_4,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_5,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_6,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_7,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_8,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_9,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_10,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_11,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_12,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_13,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_14,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_15,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_16,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_17,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_18,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_19,           switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_2,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_3,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_4,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_5,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_6,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_7,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_8,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_9,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_10,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_11,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_12,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_13,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_14,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_15,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_16,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_17,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_18,           switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_19,           switch_mux_port_out_3)
};

static const meba_synce_graph_element_t synce_graph_elements_jr2_48_board[] = {          // Note: This graph is only used when DPLL != zls30363. For DPLL == zls30363 see graph further below.
    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      phy_mux_0_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      phy_mux_0_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      phy_mux_0_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      phy_mux_0_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      phy_mux_0_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      phy_mux_0_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     phy_mux_0_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     phy_mux_0_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                     phy_mux_1_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                     phy_mux_1_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_14,                     phy_mux_1_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_15,                     phy_mux_1_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_16,                     phy_mux_1_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_17,                     phy_mux_1_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_18,                     phy_mux_1_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_19,                     phy_mux_1_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_20,                     phy_mux_1_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_21,                     phy_mux_1_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_22,                     phy_mux_1_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_23,                     phy_mux_1_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_24,                     phy_mux_2_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_25,                     phy_mux_2_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_26,                     phy_mux_2_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_27,                     phy_mux_2_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_28,                     phy_mux_2_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_29,                     phy_mux_2_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_30,                     phy_mux_2_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_31,                     phy_mux_2_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_32,                     phy_mux_2_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_33,                     phy_mux_2_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_34,                     phy_mux_2_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_35,                     phy_mux_2_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_36,                     phy_mux_3_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_37,                     phy_mux_3_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_38,                     phy_mux_3_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_39,                     phy_mux_3_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_40,                     phy_mux_3_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_41,                     phy_mux_3_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_42,                     phy_mux_3_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_43,                     phy_mux_3_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_44,                     phy_mux_3_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_45,                     phy_mux_3_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_46,                     phy_mux_3_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_47,                     phy_mux_3_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_48,                     switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_49,                     switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_0,           board_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_1,           board_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           board_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           board_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_0,            board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_1,            board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_0,            board_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_1,            board_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_2_port_out_0,            board_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_2_port_out_1,            board_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_3_port_out_0,            board_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_3_port_out_1,            board_mux_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_0,            dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_1,            dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_jr2_48,            dpll_port_7),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_2,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_4,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_6,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_8,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_10,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_12,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_3,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_5,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_7,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_9,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_11,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_13,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_1)
};

static const meba_synce_graph_element_t synce_graph_elements_jr2_48_w_zls30363_board[] = {           // Note: This graph is only used when DPLL == zls30363. For DPLL != zls30363 see graph above.
    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      phy_mux_0_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      phy_mux_0_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      phy_mux_0_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      phy_mux_0_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      phy_mux_0_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      phy_mux_0_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     phy_mux_0_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     phy_mux_0_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                     phy_mux_1_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                     phy_mux_1_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_14,                     phy_mux_1_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_15,                     phy_mux_1_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_16,                     phy_mux_1_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_17,                     phy_mux_1_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_18,                     phy_mux_1_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_19,                     phy_mux_1_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_20,                     phy_mux_1_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_21,                     phy_mux_1_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_22,                     phy_mux_1_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_23,                     phy_mux_1_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_24,                     phy_mux_2_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_25,                     phy_mux_2_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_26,                     phy_mux_2_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_27,                     phy_mux_2_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_28,                     phy_mux_2_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_29,                     phy_mux_2_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_30,                     phy_mux_2_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_31,                     phy_mux_2_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_32,                     phy_mux_2_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_33,                     phy_mux_2_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_34,                     phy_mux_2_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_35,                     phy_mux_2_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_36,                     phy_mux_3_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_37,                     phy_mux_3_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_38,                     phy_mux_3_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_39,                     phy_mux_3_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_40,                     phy_mux_3_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_41,                     phy_mux_3_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_42,                     phy_mux_3_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_43,                     phy_mux_3_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_44,                     phy_mux_3_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_45,                     phy_mux_3_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_46,                     phy_mux_3_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_47,                     phy_mux_3_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_48,                     switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_49,                     switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_0,           board_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_1,           board_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           board_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           board_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_0,            board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_1,            board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_0,            board_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_1,            board_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_2_port_out_0,            board_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_2_port_out_1,            board_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_3_port_out_0,            board_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_3_port_out_1,            board_mux_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_0,            dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_1,            dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_jr2_48,            dpll_port_7),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_2,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_4,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_6,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_8,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_10,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_12,            board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_3,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_5,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_7,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_9,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_11,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   board_mux_port_in_13,            board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_3)
};

static const meba_synce_graph_element_t synce_graph_elements_serval2_board[] = {
    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_0,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_1,           dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_0,            dpll_port_4),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_1,            dpll_port_5),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_serval2,           dpll_port_6)
};

static const meba_synce_graph_element_t synce_graph_elements_serval2_rev5_board[] = {
    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                     switch_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                     switch_mux_port_in_9),

    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_0,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_1,           dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           dpll_port_2),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           dpll_port_3),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_0,            dpll_port_4),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_1,            dpll_port_5),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_serval2,           dpll_port_6),

    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_2,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_3,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_4,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_5,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_6,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_7,            switch_mux_port_out_2),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_0,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_1,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_2,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_3,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_4,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_5,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_6,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_7,            switch_mux_port_out_3),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_8,            switch_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_9,            switch_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_8,            switch_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(   switch_mux_port_in_9,            switch_mux_port_out_1)
};

static const meba_synce_terminal_attr_t attr_jr2_24_board[] = {                  // Note: These attributes are only used when DPLL != zls30363. For DPLL == zls30363 see attributes further below.
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_7,           MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(phy_mux_0_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_0_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_0,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_12,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_20,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_21,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_22,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_23,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ)
};

static const meba_synce_terminal_attr_t attr_jr2_24_w_zls30363_board[] = {       // Note: These attributes are only used when DPLL == zls30363. For DPLL != zls30363 see attributes above.
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_7,           MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(phy_mux_0_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_0_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_0,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),

    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),

    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),

    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),

    MESA_SYNCE_ATTR(eth_port_12,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_20,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_21,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_22,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_23,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
};

static const meba_synce_terminal_attr_t attr_jr2_24_w_zls30772_board[] = {       // Note: These attributes are only used when DPLL == zls30772. For DPLL != zls30772 see attributes above.
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,   2),
    MESA_SYNCE_ATTR(dpll_port_2,           MEBA_ATTR_CLOCK_ID,   3),

    MESA_SYNCE_ATTR(phy_mux_0_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_0_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_0,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),

    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),

    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),

    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),

    MESA_SYNCE_ATTR(eth_port_12,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_20,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_21,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_22,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_23,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
};

static const meba_synce_terminal_attr_t attr_jr2_48_board[] = {                  // Note: These attributes are only used when DPLL != zls30363. For DPLL == zls30363 see attributes further below.
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_7,           MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(phy_mux_0_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_0_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_2_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_2_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_3_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_3_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_0,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_12,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_20,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_21,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_22,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_23,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_28,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_29,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_30,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_31,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_32,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_33,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_34,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_35,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_36,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_37,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_38,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_39,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_40,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_41,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_42,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_43,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_44,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_45,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_46,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_47,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_48,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_49,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ)
};

static const meba_synce_terminal_attr_t attr_jr2_48_w_zls30363_board[] = {       // Note: These attributes are only used when DPLL == zls30363. For DPLL != zls30363 see attributes above.
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_7,           MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(phy_mux_0_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_0_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_1_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_2_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_2_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_3_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_3_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_0,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_12,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_20,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_21,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_22,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_23,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_24,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_25,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_26,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_27,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_28,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_29,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_30,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_31,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_32,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_33,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_34,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_35,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_36,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_37,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_38,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_39,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_40,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_41,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_42,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_43,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_44,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_45,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_46,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_47,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_48,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_48,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_48,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
    MESA_SYNCE_ATTR(eth_port_49,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_49,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_49,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ)
};

static const meba_synce_terminal_attr_t attr_serval2_board[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_4,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_5,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_6,           MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(phy_mux_0_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(phy_mux_0_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),

    MESA_SYNCE_ATTR(eth_port_0,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
};

static const meba_synce_terminal_attr_t attr_serval2_rev5_board[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_2,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_3,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_4,           MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_5,           MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_6,           MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(phy_mux_0_port_out_0,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_0_port_out_1,  MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(eth_port_0,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_5,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_6,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_7,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,            MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_12,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_12,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_12,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
    MESA_SYNCE_ATTR(eth_port_13,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_13,           MEBA_ATTR_FREQ_10G,   MEBA_SYNCE_CLOCK_FREQ_161_13MHZ),
};

mesa_rc meba_synce_graph_get(meba_inst_t inst, const meba_synce_graph_t **const g)
{
    static meba_synce_graph_t synce_graph;

    int board_type = inst->props.board_type;
    meba_synce_clock_hw_id_t dpll_type;

    if (meba_synce_spi_if_get_dpll_type(inst, &dpll_type) != MESA_RC_OK) {
        T_E(inst, "Failure probing DPLL type.");
    }

    if (board_type == VTSS_BOARD_JAGUAR2_REF) {
        if (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30363) {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_jr2_24_w_zls30363_board);
            synce_graph.graph = synce_graph_elements_jr2_24_w_zls30363_board;
            synce_graph.attr = attr_jr2_24_w_zls30363_board;
            synce_graph.attr_length = MEBA_ARRSZ(attr_jr2_24_w_zls30363_board);
        } else if (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30771 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772 ||
                   dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30773) {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_jr2_24_w_zls30772_board);
            synce_graph.graph = synce_graph_elements_jr2_24_w_zls30772_board;
            synce_graph.attr = attr_jr2_24_w_zls30772_board;
            synce_graph.attr_length = MEBA_ARRSZ(attr_jr2_24_w_zls30772_board);
        } else {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_jr2_24_board);
            synce_graph.graph = synce_graph_elements_jr2_24_board;
            synce_graph.attr = attr_jr2_24_board;
            synce_graph.attr_length = MEBA_ARRSZ(attr_jr2_24_board);
        }
    } else if (board_type == VTSS_BOARD_JAGUAR2_CU48_REF) {
        if (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30363 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30771 ||
            dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30773) {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_jr2_48_w_zls30363_board);
            synce_graph.graph = synce_graph_elements_jr2_48_w_zls30363_board;
            synce_graph.attr = attr_jr2_48_w_zls30363_board;
            synce_graph.attr_length = MEBA_ARRSZ(attr_jr2_48_w_zls30363_board);
        } else {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_jr2_48_board);
            synce_graph.graph = synce_graph_elements_jr2_48_board;
            synce_graph.attr = attr_jr2_48_board;
            synce_graph.attr_length = MEBA_ARRSZ(attr_jr2_48_board);
        }
    } else if (board_type == VTSS_BOARD_SERVAL2_NID_REF) {
        if (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30363 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30771 ||
            dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30773) {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_serval2_rev5_board);
            synce_graph.graph = synce_graph_elements_serval2_rev5_board;
            synce_graph.attr = attr_serval2_rev5_board;
            synce_graph.attr_length = MEBA_ARRSZ(attr_serval2_rev5_board);
        } else {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_serval2_board);
            synce_graph.graph = synce_graph_elements_serval2_board;
            synce_graph.attr = attr_serval2_board;
            synce_graph.attr_length = MEBA_ARRSZ(attr_serval2_board);
        }
    } else {
        printf("ERROR: Board type not yet implemented.\n");
        synce_graph.graph_length = 0;
        synce_graph.graph = NULL;
        synce_graph.attr = NULL;
        synce_graph.attr_length = 0;
    }

    if ((dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30363 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30771 ||
         dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30773) && (board_type == VTSS_BOARD_SERVAL2_NID_REF)) {
        // If board is a serval2, ref. 4+5 need to be configured as differential.
        const uint8_t tx_data_pg_reg[1] = {0};
        const uint8_t tx_data_cfg_reg[1] = {0x30};
        if (meba_synce_write(inst, 0x7F, 1, tx_data_pg_reg) != MESA_RC_OK ||
            meba_synce_write(inst, 0x7A, 1, tx_data_cfg_reg) != MESA_RC_OK) {
            T_W(inst, "Could not configure ref. 4 and 5 as differential.");
        }
    }

    *g = &synce_graph;

    return MESA_RC_OK;
}

mesa_rc meba_synce_mux_set(meba_inst_t  inst,
                           uint32_t     dev_id,
                           uint32_t     input,
                           uint32_t     output)
{
    return MESA_RC_ERROR;
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
