// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "microchip/ethernet/board/api.h"

#include "meba_aux.h"

// Declare all the terminals in the graph

//      NAME                             TYPE                    DEV-ID   INDEX
#define eth_port_0                       MESA_SYNCE_DEV_PORT(         0,      0)  // On Caracal1 boards eth_port_0 to eth_port_9 are used
#define eth_port_1                       MESA_SYNCE_DEV_PORT(         1,      0)  // On Caracal Lite boards eth_port_0 to eth_port_6 are used
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

#define station_clock_port_caracal_lite  MESA_SYNCE_DEV_CLOCK_IN(     7,      0)
#define station_clock_port_caracal_1     MESA_SYNCE_DEV_CLOCK_IN(    10,      0)
#define station_clock_port_caracal_2     MESA_SYNCE_DEV_CLOCK_IN(    26,      0)

#define phy_mux_0_port_in_0              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 0)  // On Caracal1 boards phy_mux_0_port_in_0 to phy_mux_0_port_in_7 are used
#define phy_mux_0_port_in_1              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 1)  // On Caracal Lite boards phy_mux_0_port_in_0 to phy_mux_0_port_in_4 are used
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

#define switch_mux_port_in_0             MESA_SYNCE_DEV_MUX_SWITCH( 200,      MESA_SYNCE_DEV_INPUT | 0)
#define switch_mux_port_in_1             MESA_SYNCE_DEV_MUX_SWITCH( 200,      MESA_SYNCE_DEV_INPUT | 1)
#define switch_mux_port_out_0            MESA_SYNCE_DEV_MUX_SWITCH( 200,      0)
#define switch_mux_port_out_1            MESA_SYNCE_DEV_MUX_SWITCH( 200,      1)

#define board_mux_port_in_0              MESA_SYNCE_DEV_MUX_BOARD(  300,      MESA_SYNCE_DEV_INPUT | MESA_SYNCE_TRI_STATE_FROM_SWITCH | 0)
#define board_mux_port_in_1              MESA_SYNCE_DEV_MUX_BOARD(  300,      MESA_SYNCE_DEV_INPUT | MESA_SYNCE_TRI_STATE_FROM_SWITCH | 1)
#define board_mux_port_in_2              MESA_SYNCE_DEV_MUX_BOARD(  300,      MESA_SYNCE_DEV_INPUT | MESA_SYNCE_TRI_STATE_FROM_PHY | 2)
#define board_mux_port_in_3              MESA_SYNCE_DEV_MUX_BOARD(  300,      MESA_SYNCE_DEV_INPUT | MESA_SYNCE_TRI_STATE_FROM_PHY | 3)
#define board_mux_port_out_0             MESA_SYNCE_DEV_MUX_BOARD(  300,      0)
#define board_mux_port_out_1             MESA_SYNCE_DEV_MUX_BOARD(  300,      1)

#define phy_mux_1_port_in_0              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 0)  // Only used on Luton26 ref boards e.g. Caracal2
#define phy_mux_1_port_in_1              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_1_port_in_2              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_1_port_in_3              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_1_port_in_4              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 4)
#define phy_mux_1_port_in_5              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 5)
#define phy_mux_1_port_in_6              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 6)
#define phy_mux_1_port_in_7              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 7)
#define phy_mux_1_port_in_8              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 8)
#define phy_mux_1_port_in_9              MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 9)
#define phy_mux_1_port_in_10             MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 10)
#define phy_mux_1_port_in_11             MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 11)
#define phy_mux_1_port_out_0             MESA_SYNCE_DEV_MUX_PHY(    400,      0)
#define phy_mux_1_port_out_1             MESA_SYNCE_DEV_MUX_PHY(    400,      1)

#define dpll_port_0                      MESA_SYNCE_DEV_DPLL(       500,      MESA_SYNCE_DEV_INPUT | 0)
#define dpll_port_1                      MESA_SYNCE_DEV_DPLL(       500,      MESA_SYNCE_DEV_INPUT | 1)
#define dpll_port_2                      MESA_SYNCE_DEV_DPLL(       500,      MESA_SYNCE_DEV_INPUT | 2)
#define dpll_port_3                      MESA_SYNCE_DEV_DPLL(       500,      MESA_SYNCE_DEV_INPUT | 3)
#define dpll_port_4                      MESA_SYNCE_DEV_DPLL(       500,      MESA_SYNCE_DEV_INPUT | 4)
#define dpll_port_5                      MESA_SYNCE_DEV_DPLL(       500,      MESA_SYNCE_DEV_INPUT | 5)
#define dpll_port_6                      MESA_SYNCE_DEV_DPLL(       500,      MESA_SYNCE_DEV_INPUT | 6)
#define dpll_port_7                      MESA_SYNCE_DEV_DPLL(       500,      MESA_SYNCE_DEV_INPUT | 7)

static const meba_synce_graph_element_t synce_graph_elements_caracal1_board[] = {
    // type                               source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_4,                      phy_mux_0_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_5,                      phy_mux_0_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_6,                      phy_mux_0_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_7,                      phy_mux_0_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_8,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_9,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_0,           board_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_1,           board_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_0_port_out_0,            board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_0_port_out_1,            board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          board_mux_port_out_0,            dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(          board_mux_port_out_1,            dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(          station_clock_port_caracal_1,    dpll_port_7),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_0,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_1,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_2,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_3,             board_mux_port_out_0)
};

static const meba_synce_graph_element_t synce_graph_elements_caracal_lite_board[] = {
    // type                               source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_4,                      phy_mux_0_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_5,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_6,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_0,           board_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_1,           board_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_0_port_out_0,            board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_0_port_out_1,            board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          board_mux_port_out_0,            dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(          board_mux_port_out_1,            dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(          station_clock_port_caracal_lite, dpll_port_7),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_0,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_1,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_2,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_3,             board_mux_port_out_0)
};

static const meba_synce_graph_element_t synce_graph_elements_caracal2_board[] = {
    // type                               source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_0,                      phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_1,                      phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_2,                      phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_3,                      phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_4,                      phy_mux_0_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_5,                      phy_mux_0_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_6,                      phy_mux_0_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_7,                      phy_mux_0_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_8,                      phy_mux_0_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_9,                      phy_mux_0_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_10,                     phy_mux_0_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_11,                     phy_mux_0_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_12,                     phy_mux_1_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_13,                     phy_mux_1_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_14,                     phy_mux_1_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_15,                     phy_mux_1_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_16,                     phy_mux_1_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_17,                     phy_mux_1_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_18,                     phy_mux_1_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_19,                     phy_mux_1_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_20,                     phy_mux_1_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_21,                     phy_mux_1_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_22,                     phy_mux_1_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_23,                     phy_mux_1_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_24,                     switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_25,                     switch_mux_port_in_1),

    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_0,           board_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_1,           board_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_0_port_out_0,            board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_0_port_out_1,            board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          board_mux_port_out_0,            dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(          board_mux_port_out_1,            dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_1_port_out_0,            dpll_port_2),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_1_port_out_1,            dpll_port_3),
    MESA_SYNCE_GRAPH_CONNECTION(          station_clock_port_caracal_2,    dpll_port_7),

    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_0,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_1,             board_mux_port_out_0),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_2,             board_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  board_mux_port_in_3,             board_mux_port_out_0)
};

static const meba_synce_terminal_attr_t attr_caracal1_board[] = {
    //              device         attr-type                attr-value
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(eth_port_0,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ)
};

static const meba_synce_terminal_attr_t attr_caracal_lite_board[] = {
    //              device         attr-type                attr-value
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(eth_port_0,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ)
};

static const meba_synce_terminal_attr_t attr_caracal2_board[] = {
    //              device         attr-type                attr-value
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_2,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_3,   MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(eth_port_0,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_12,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_20,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_21,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_22,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_23,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_24,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_25,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ)
};

static const meba_synce_terminal_attr_t attr_defaults_dpll[] = {
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ)
};

static const meba_synce_terminal_attr_t attr_zarlink_dpll[] = {
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ)
};

static const meba_synce_terminal_attr_t attr_caracal2_defaults_dpll[] = {
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_2,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_3,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ)
};

static const meba_synce_terminal_attr_t attr_caracal2_zarlink_dpll[] = {
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_2,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(dpll_port_3,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ)
};


mesa_rc meba_synce_graph_get(meba_inst_t inst, const meba_synce_graph_t **const g)
{
    static meba_synce_graph_t synce_graph;
    static meba_synce_terminal_attr_t attr[MEBA_MAX(MEBA_ARRSZ(attr_caracal1_board), MEBA_MAX(MEBA_ARRSZ(attr_caracal_lite_board), MEBA_ARRSZ(attr_caracal2_board)))
                                           + MEBA_MAX(MEBA_MAX(MEBA_ARRSZ(attr_defaults_dpll), MEBA_ARRSZ(attr_zarlink_dpll)),
                                                      MEBA_MAX(MEBA_ARRSZ(attr_caracal2_defaults_dpll), MEBA_ARRSZ(attr_caracal2_zarlink_dpll)))];

    int board_type = inst->props.board_type;
    meba_synce_clock_hw_id_t dpll_type;

    if (meba_synce_spi_if_get_dpll_type(inst, &dpll_type) != MESA_RC_OK) {
        T_E(inst, "Failure probing DPLL type.");
    }

    if (board_type == VTSS_BOARD_LUTON10_REF) {
        if (inst->props.target == MESA_TARGET_CARACAL_LITE) {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_caracal_lite_board);
            synce_graph.graph = synce_graph_elements_caracal_lite_board;
            memcpy(attr, attr_caracal1_board, sizeof(attr_caracal_lite_board));
            synce_graph.attr_length = MEBA_ARRSZ(attr_caracal_lite_board);
        } else if (inst->props.target == MESA_TARGET_CARACAL_1) {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_caracal1_board);
            synce_graph.graph = synce_graph_elements_caracal1_board;
            memcpy(attr, attr_caracal1_board, sizeof(attr_caracal1_board));
            synce_graph.attr_length = MEBA_ARRSZ(attr_caracal1_board);
        } else {
            T_E(inst, "ERROR: Chip type (%d) not yet implemented.\n",
                inst->props.target);
            synce_graph.graph_length = 0;
            synce_graph.graph = NULL;
            synce_graph.attr_length = 0;
        }

        switch (dpll_type) {
        case MEBA_SYNCE_CLOCK_HW_SI_5326:
        case MEBA_SYNCE_CLOCK_HW_SI_5328:
            memcpy(&attr[synce_graph.attr_length], attr_defaults_dpll, sizeof(attr_defaults_dpll));
            synce_graph.attr_length += MEBA_ARRSZ(attr_defaults_dpll);
            break;
        case MEBA_SYNCE_CLOCK_HW_ZL_30343:
        case MEBA_SYNCE_CLOCK_HW_ZL_30363:
        case MEBA_SYNCE_CLOCK_HW_ZL_30771:
        case MEBA_SYNCE_CLOCK_HW_ZL_30772:
        case MEBA_SYNCE_CLOCK_HW_ZL_30773:
        default:
            // Note: In the case that no DPLL is present, we still set up DPLL frequency attributes to avoid a problem
            //       with the PHY output frequencies otherwise being unknown. Alternatively, the PHY output frequencies
            //       could be specified explicitly.
            memcpy(&attr[synce_graph.attr_length], attr_zarlink_dpll, sizeof(attr_zarlink_dpll));
            synce_graph.attr_length += MEBA_ARRSZ(attr_zarlink_dpll);
            break;
        }
    } else if (board_type == VTSS_BOARD_LUTON26_REF) {
        if (inst->props.target == MESA_TARGET_CARACAL_2) {
            synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_caracal2_board);
            synce_graph.graph = synce_graph_elements_caracal2_board;
            memcpy(attr, attr_caracal2_board, sizeof(attr_caracal2_board));
            synce_graph.attr_length = MEBA_ARRSZ(attr_caracal2_board);
        } else {
            T_E(inst, "ERROR: Chip type (%d) not yet implemented.\n",
                inst->props.target);
            synce_graph.graph_length = 0;
            synce_graph.graph = NULL;
            synce_graph.attr_length = 0;
        }

        switch (dpll_type) {
        case MEBA_SYNCE_CLOCK_HW_SI_5326:
        case MEBA_SYNCE_CLOCK_HW_SI_5328:
            memcpy(&attr[synce_graph.attr_length], attr_caracal2_defaults_dpll, sizeof(attr_caracal2_defaults_dpll));
            synce_graph.attr_length += MEBA_ARRSZ(attr_caracal2_defaults_dpll);
            break;
        case MEBA_SYNCE_CLOCK_HW_ZL_30343:
        case MEBA_SYNCE_CLOCK_HW_ZL_30363:
        case MEBA_SYNCE_CLOCK_HW_ZL_30771:
        case MEBA_SYNCE_CLOCK_HW_ZL_30772:
        case MEBA_SYNCE_CLOCK_HW_ZL_30773:
        default:
            // Note: In the case that no DPLL is present, we still set up DPLL frequency attributes to avoid a problem
            //       with the PHY output frequencies otherwise being unknown. Alternatively, the PHY output frequencies
            //       could be specified explicitly.
            memcpy(&attr[synce_graph.attr_length], attr_caracal2_zarlink_dpll, sizeof(attr_caracal2_zarlink_dpll));
            synce_graph.attr_length += MEBA_ARRSZ(attr_caracal2_zarlink_dpll);
            break;
        }
    } else {
        T_E(inst, "ERROR: Board type %d not yet implemented.\n", board_type);
        synce_graph.graph_length = 0;
        synce_graph.graph = NULL;
        synce_graph.attr_length = 0;
    }
    synce_graph.attr = attr;

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
