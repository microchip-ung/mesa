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
#define station_clock_port_0             MESA_SYNCE_DEV_CLOCK_IN(    11,      0)

#define phy_mux_port_in_0                MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_port_in_1                MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_port_in_2                MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_port_in_3                MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_port_out_0               MESA_SYNCE_DEV_MUX_PHY(    100,      0)
#define phy_mux_port_out_1               MESA_SYNCE_DEV_MUX_PHY(    100,      1)

#define switch_mux_port_in_0             MESA_SYNCE_DEV_MUX_SWITCH( 200,      MESA_SYNCE_DEV_INPUT | 0)
#define switch_mux_port_in_1             MESA_SYNCE_DEV_MUX_SWITCH( 200,      MESA_SYNCE_DEV_INPUT | 1)
#define switch_mux_port_in_2             MESA_SYNCE_DEV_MUX_SWITCH( 200,      MESA_SYNCE_DEV_INPUT | 2)
#define switch_mux_port_in_3             MESA_SYNCE_DEV_MUX_SWITCH( 200,      MESA_SYNCE_DEV_INPUT | 3)
#define switch_mux_port_in_4             MESA_SYNCE_DEV_MUX_SWITCH( 200,      MESA_SYNCE_DEV_INPUT | 4)
#define switch_mux_port_in_5             MESA_SYNCE_DEV_MUX_SWITCH( 200,      MESA_SYNCE_DEV_INPUT | 5)
#define switch_mux_port_out_0            MESA_SYNCE_DEV_MUX_SWITCH( 200,      0)
#define switch_mux_port_out_1            MESA_SYNCE_DEV_MUX_SWITCH( 200,      1)

#define dpll_port_0                      MESA_SYNCE_DEV_DPLL(       300,      MESA_SYNCE_DEV_INPUT | 0)
#define dpll_port_1                      MESA_SYNCE_DEV_DPLL(       300,      MESA_SYNCE_DEV_INPUT | 1)
#define dpll_port_2                      MESA_SYNCE_DEV_DPLL(       300,      MESA_SYNCE_DEV_INPUT | 2)
#define dpll_port_3                      MESA_SYNCE_DEV_DPLL(       300,      MESA_SYNCE_DEV_INPUT | 3)
#define dpll_port_4                      MESA_SYNCE_DEV_DPLL(       300,      MESA_SYNCE_DEV_INPUT | 4)
#define dpll_port_5                      MESA_SYNCE_DEV_DPLL(       300,      MESA_SYNCE_DEV_INPUT | 5)
#define dpll_port_6                      MESA_SYNCE_DEV_DPLL(       300,      MESA_SYNCE_DEV_INPUT | 6)
#define dpll_port_7                      MESA_SYNCE_DEV_DPLL(       300,      MESA_SYNCE_DEV_INPUT | 7)

static const meba_synce_graph_element_t synce_graph_elements_serval_ref_board[] = {
    // type                               source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_0,                      phy_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_1,                      phy_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_2,                      phy_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_3,                      phy_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_4,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_5,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_6,                      switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_7,                      switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_8,                      switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_9,                      switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_0,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_port_out_0,              dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_1,           dpll_port_2),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_port_out_1,              dpll_port_3),
    MESA_SYNCE_GRAPH_CONNECTION(          station_clock_port_0,            dpll_port_7),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  switch_mux_port_in_2,            switch_mux_port_out_0)
};

static const meba_synce_graph_element_t synce_graph_elements_serval_nid_board[] = {
    // type                               source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_0,                      phy_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_1,                      phy_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_2,                      phy_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_3,                      phy_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_4,                      switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_5,                      switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_6,                      switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_7,                      switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_8,                      switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(          eth_port_9,                      switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_0,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(          switch_mux_port_out_1,           dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_port_out_0,              dpll_port_4),
    MESA_SYNCE_GRAPH_CONNECTION(          phy_mux_port_out_1,              dpll_port_5),
    MESA_SYNCE_GRAPH_CONNECTION(          station_clock_port_0,            dpll_port_6),
    MESA_SYNCE_GRAPH_INVALID_CONNECTION(  switch_mux_port_in_2,            switch_mux_port_out_0)
};

static const meba_synce_terminal_attr_t attr_serval_ref_board[] = {
    //              device         attr-type                attr-value
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_2,   MEBA_ATTR_CLOCK_ID,                   2),
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
    MESA_SYNCE_ATTR(eth_port_8,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
    MESA_SYNCE_ATTR(eth_port_9,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,    MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_156_25MHZ),
};

static const meba_synce_terminal_attr_t attr_serval_nid_board[] = {
    //              device         attr-type                attr-value
    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_4,   MEBA_ATTR_CLOCK_ID,                   1),
    MESA_SYNCE_ATTR(dpll_port_5,   MEBA_ATTR_CLOCK_ID,                   2),
    MESA_SYNCE_ATTR(dpll_port_6,   MEBA_ATTR_CLOCK_ID,                   3),

    MESA_SYNCE_ATTR(dpll_port_0,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_1,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_4,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(dpll_port_5,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(dpll_port_6,   MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),

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
};

static const meba_synce_terminal_attr_t attr_serval_ref_board_defaults_dpll[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_2,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_3,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_7,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
};

static const meba_synce_terminal_attr_t attr_serval_ref_board_zls30343_dpll[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_2,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(dpll_port_3,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(dpll_port_7,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
};

static const meba_synce_terminal_attr_t attr_serval_ref_board_zls30363_dpll[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(phy_mux_port_out_0,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(phy_mux_port_out_1,    MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(dpll_port_2,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(dpll_port_2,           MEBA_ATTR_FREQ_2_5G,  MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),

    MESA_SYNCE_ATTR(dpll_port_7,           MEBA_ATTR_FREQ,       MEBA_SYNCE_CLOCK_FREQ_25MHZ),
};

mesa_rc meba_synce_graph_get(meba_inst_t inst, const meba_synce_graph_t **const g)
{
    static meba_synce_graph_t synce_graph;
    static meba_synce_terminal_attr_t attr[MEBA_MAX(MEBA_ARRSZ(attr_serval_ref_board), MEBA_ARRSZ(attr_serval_nid_board))
                                           + MEBA_MAX(MEBA_ARRSZ(attr_serval_ref_board_defaults_dpll),
                                                      MEBA_MAX(MEBA_ARRSZ(attr_serval_ref_board_zls30343_dpll), MEBA_ARRSZ(attr_serval_ref_board_zls30363_dpll)))];
    int board_type = inst->props.board_type;
    meba_synce_clock_hw_id_t dpll_type;

    if (meba_synce_spi_if_get_dpll_type(inst, &dpll_type) != MESA_RC_OK) {
        T_E(inst, "Failure probing DPLL type.");
    }

    if (board_type == VTSS_BOARD_SERVAL_REF) {
        synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_serval_ref_board);
        synce_graph.graph = synce_graph_elements_serval_ref_board;
        memcpy(attr, attr_serval_ref_board, sizeof(attr_serval_ref_board));
        synce_graph.attr_length = MEBA_ARRSZ(attr_serval_ref_board);

        switch (dpll_type) {
        case MEBA_SYNCE_CLOCK_HW_SI_5326:
        case MEBA_SYNCE_CLOCK_HW_SI_5328:
            memcpy(&attr[synce_graph.attr_length], attr_serval_ref_board_defaults_dpll, sizeof(attr_serval_ref_board_defaults_dpll));
            synce_graph.attr_length += MEBA_ARRSZ(attr_serval_ref_board_defaults_dpll);
            break;
        case MEBA_SYNCE_CLOCK_HW_ZL_30343:
            memcpy(&attr[synce_graph.attr_length], attr_serval_ref_board_zls30343_dpll, sizeof(attr_serval_ref_board_zls30343_dpll));
            synce_graph.attr_length += MEBA_ARRSZ(attr_serval_ref_board_zls30343_dpll);
            break;
        case MEBA_SYNCE_CLOCK_HW_ZL_30363:
        case MEBA_SYNCE_CLOCK_HW_ZL_30771:
        case MEBA_SYNCE_CLOCK_HW_ZL_30772:
        case MEBA_SYNCE_CLOCK_HW_ZL_30773:
        default:
            memcpy(&attr[synce_graph.attr_length], attr_serval_ref_board_zls30363_dpll, sizeof(attr_serval_ref_board_zls30363_dpll));
            synce_graph.attr_length += MEBA_ARRSZ(attr_serval_ref_board_zls30363_dpll);
            break;
        }
    } else if (board_type == VTSS_BOARD_SERVAL_PCB106_REF) {
        synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_serval_nid_board);
        synce_graph.graph = synce_graph_elements_serval_nid_board;
        memcpy(attr, attr_serval_nid_board, sizeof(attr_serval_nid_board));
        synce_graph.attr_length = MEBA_ARRSZ(attr_serval_nid_board);
    } else {
        printf("ERROR: Board type not yet implemented.\n");
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
