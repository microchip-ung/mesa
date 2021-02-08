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
#define station_clock_port_0             MESA_SYNCE_DEV_CLOCK_IN(    11,      0)

#define divider_switch_mux_port_0_in     MESA_SYNCE_DEV_DIVIDER(    100,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_0_out    MESA_SYNCE_DEV_DIVIDER(    100,      0)

#define divider_switch_mux_port_1_in     MESA_SYNCE_DEV_DIVIDER(    101,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_1_out    MESA_SYNCE_DEV_DIVIDER(    101,      0)

#define divider_switch_mux_port_2_in     MESA_SYNCE_DEV_DIVIDER(    102,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_2_out    MESA_SYNCE_DEV_DIVIDER(    102,      0)

#define divider_switch_mux_port_3_in     MESA_SYNCE_DEV_DIVIDER(    103,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_3_out    MESA_SYNCE_DEV_DIVIDER(    103,      0)

#define divider_switch_mux_port_4_in     MESA_SYNCE_DEV_DIVIDER(    104,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_4_out    MESA_SYNCE_DEV_DIVIDER(    104,      0)

#define divider_switch_mux_port_5_in     MESA_SYNCE_DEV_DIVIDER(    105,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_5_out    MESA_SYNCE_DEV_DIVIDER(    105,      0)

#define divider_switch_mux_port_6_in     MESA_SYNCE_DEV_DIVIDER(    106,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_6_out    MESA_SYNCE_DEV_DIVIDER(    106,      0)

#define divider_switch_mux_port_7_in     MESA_SYNCE_DEV_DIVIDER(    107,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_7_out    MESA_SYNCE_DEV_DIVIDER(    107,      0)

#define phy_mux_port_in_0                MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_port_in_1                MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_port_in_2                MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_port_in_3                MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_port_out_0               MESA_SYNCE_DEV_MUX_PHY(    200,      0)
#define phy_mux_port_out_1               MESA_SYNCE_DEV_MUX_PHY(    200,      1)

#define switch_mux_port_in_0             MESA_SYNCE_DEV_MUX_SWITCH( 300,      MESA_SYNCE_DEV_INPUT | 0)
#define switch_mux_port_in_1             MESA_SYNCE_DEV_MUX_SWITCH( 300,      MESA_SYNCE_DEV_INPUT | 1)
#define switch_mux_port_in_2             MESA_SYNCE_DEV_MUX_SWITCH( 300,      MESA_SYNCE_DEV_INPUT | 2)
#define switch_mux_port_in_3             MESA_SYNCE_DEV_MUX_SWITCH( 300,      MESA_SYNCE_DEV_INPUT | 3)
#define switch_mux_port_in_4             MESA_SYNCE_DEV_MUX_SWITCH( 300,      MESA_SYNCE_DEV_INPUT | 4)
#define switch_mux_port_in_5             MESA_SYNCE_DEV_MUX_SWITCH( 300,      MESA_SYNCE_DEV_INPUT | 5)
#define switch_mux_port_in_6             MESA_SYNCE_DEV_MUX_SWITCH( 300,      MESA_SYNCE_DEV_INPUT | 6)
#define switch_mux_port_in_7             MESA_SYNCE_DEV_MUX_SWITCH( 300,      MESA_SYNCE_DEV_INPUT | 7)
#define switch_mux_port_out_0            MESA_SYNCE_DEV_MUX_SWITCH( 300,      0)
#define switch_mux_port_out_1            MESA_SYNCE_DEV_MUX_SWITCH( 300,      1)

#define dpll_port_0                      MESA_SYNCE_DEV_DPLL(       400,      MESA_SYNCE_DEV_INPUT | 0)
#define dpll_port_1                      MESA_SYNCE_DEV_DPLL(       400,      MESA_SYNCE_DEV_INPUT | 1)
#define dpll_port_4                      MESA_SYNCE_DEV_DPLL(       400,      MESA_SYNCE_DEV_INPUT | 4)
#define dpll_port_7                      MESA_SYNCE_DEV_DPLL(       400,      MESA_SYNCE_DEV_INPUT | 7)

static const meba_synce_graph_element_t synce_graph_elements_ocelot10_ref_board[] = {
    // type                               source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_0,                      phy_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_1,                      phy_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_2,                      phy_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_3,                      phy_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_port_out_0,              divider_switch_mux_port_0_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_0_out,   switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_port_out_1,              divider_switch_mux_port_1_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_1_out,   switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_4,                      divider_switch_mux_port_2_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_2_out,   switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_5,                      divider_switch_mux_port_3_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_3_out,   switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_6,                      divider_switch_mux_port_4_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_4_out,   switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_7,                      divider_switch_mux_port_5_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_5_out,   switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_8,                      divider_switch_mux_port_6_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_6_out,   switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_9,                      divider_switch_mux_port_7_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_7_out,   switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_0,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_1,           dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(          station_clock_port_0,            dpll_port_7),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  switch_mux_port_in_0,            switch_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  switch_mux_port_in_1,            switch_mux_port_out_0)
};

static const meba_synce_terminal_attr_t attr_ocelot10_ref_board[] = {
    //              device         attr-type                attr-value
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(phy_mux_port_out_0,      MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_port_out_1,      MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(switch_mux_port_in_0,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_1,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_2,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_3,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_4,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_5,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_5,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_6,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_6,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_7,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_7,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),

    MESA_SYNCE_ATTR(eth_port_0,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_8,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_9,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
};

static const meba_synce_graph_element_t synce_graph_elements_ocelot10_w_zls30772_board[] = {

    // Note: This graph is only used when DPLL == zls30772. For DPLL != zls30772 see graphs above.
    // type                               source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_0,                      phy_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_1,                      phy_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_2,                      phy_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_3,                      phy_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_port_out_0,              divider_switch_mux_port_0_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_0_out,   switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_port_out_1,              divider_switch_mux_port_1_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_1_out,   switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_4,                      divider_switch_mux_port_2_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_2_out,   switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_5,                      divider_switch_mux_port_3_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_3_out,   switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_6,                      divider_switch_mux_port_4_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_4_out,   switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_7,                      divider_switch_mux_port_5_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_5_out,   switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_8,                      divider_switch_mux_port_6_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_6_out,   switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_9,                      divider_switch_mux_port_7_in),
    MESA_SYNCE_GRAPH_CONNECTION(          divider_switch_mux_port_7_out,   switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_0,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_1,           dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(          station_clock_port_0,            dpll_port_4),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  switch_mux_port_in_0,            switch_mux_port_out_1),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  switch_mux_port_in_1,            switch_mux_port_out_0)
};

static const meba_synce_terminal_attr_t attr_ocelot10_w_zls30772_board[] = {
    // Note: These attributes are only used when DPLL == zls30772. For DPLL != zls30772 see attributes above.
    //              device         attr-type                attr-value
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_4,   MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(phy_mux_port_out_0,      MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_port_out_1,      MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),

    MESA_SYNCE_ATTR(switch_mux_port_in_0,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_1,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_2,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_3,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_4,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_5,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_5,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_6,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_6,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_7,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_7,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),

    MESA_SYNCE_ATTR(eth_port_0,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_8,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_9,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(dpll_port_4,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
};
static const meba_synce_terminal_attr_t attr_ocelot10_ref_board_defaults_dpll[] = {
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
};

static const meba_synce_terminal_attr_t attr_ocelot10_ref_board_zarlink_dpll[] = {
    MESA_SYNCE_ATTR(dpll_port_7,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
};

mesa_rc meba_synce_graph_get(meba_inst_t inst, const meba_synce_graph_t **const g)
{
    static meba_synce_graph_t synce_graph;
    static meba_synce_terminal_attr_t attr[MEBA_ARRSZ(attr_ocelot10_ref_board)
                                           + MEBA_MAX(MEBA_ARRSZ(attr_ocelot10_ref_board_defaults_dpll), MEBA_ARRSZ(attr_ocelot10_ref_board_zarlink_dpll))];

    int board_type = inst->props.board_type;

    if (board_type == VTSS_BOARD_OCELOT_PCB123_REF) {  // PCB123
        meba_synce_clock_hw_id_t dpll_type;


        if (meba_synce_spi_if_get_dpll_type(inst, &dpll_type) != MESA_RC_OK) {
            T_E(inst, "Failure probing DPLL type.");
        }

        switch (dpll_type) {
            case MEBA_SYNCE_CLOCK_HW_SI_5326:
            case MEBA_SYNCE_CLOCK_HW_SI_5328:
                synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_ocelot10_ref_board);
                synce_graph.graph = synce_graph_elements_ocelot10_ref_board;
                memcpy(attr, attr_ocelot10_ref_board, sizeof(attr_ocelot10_ref_board));
                synce_graph.attr_length = MEBA_ARRSZ(attr_ocelot10_ref_board);
                memcpy(&attr[synce_graph.attr_length], attr_ocelot10_ref_board_defaults_dpll, sizeof(attr_ocelot10_ref_board_defaults_dpll));
                synce_graph.attr_length += MEBA_ARRSZ(attr_ocelot10_ref_board_defaults_dpll);
                break;
            case MEBA_SYNCE_CLOCK_HW_ZL_30771:
            case MEBA_SYNCE_CLOCK_HW_ZL_30772:
            case MEBA_SYNCE_CLOCK_HW_ZL_30773:
                synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_ocelot10_w_zls30772_board);
                synce_graph.graph = synce_graph_elements_ocelot10_w_zls30772_board;
                memcpy(attr, attr_ocelot10_w_zls30772_board, sizeof(attr_ocelot10_w_zls30772_board));
                synce_graph.attr_length = MEBA_ARRSZ(attr_ocelot10_w_zls30772_board);
                break;
            case MEBA_SYNCE_CLOCK_HW_ZL_30343:
            case MEBA_SYNCE_CLOCK_HW_ZL_30363:
            default:
                // Note: In the case that no DPLL is present, we still set up DPLL frequency attributes to avoid a problem
                //       with the PHY output frequencies otherwise being unknown. Alternatively, the PHY output frequencies
                //       could be specified explicitly.
                synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_ocelot10_ref_board);
                synce_graph.graph = synce_graph_elements_ocelot10_ref_board;
                memcpy(attr, attr_ocelot10_ref_board, sizeof(attr_ocelot10_ref_board));
                synce_graph.attr_length = MEBA_ARRSZ(attr_ocelot10_ref_board);
                memcpy(&attr[synce_graph.attr_length], attr_ocelot10_ref_board_zarlink_dpll, sizeof(attr_ocelot10_ref_board_zarlink_dpll));
                synce_graph.attr_length += MEBA_ARRSZ(attr_ocelot10_ref_board_zarlink_dpll);
                break;
        }
    } else {  // Other Ocelot boards not featuring a SyncE DPLL e.g. PCB123
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
