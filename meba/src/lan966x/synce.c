// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "microchip/ethernet/board/api.h"

#include "meba_aux.h"

// Declare all the terminals in the graph

//      NAME                    TYPE                         DEV-ID   INDEX
#define eth_port_0              MESA_SYNCE_DEV_PORT(              0,      0)
#define eth_port_1              MESA_SYNCE_DEV_PORT(              1,      0)
#define eth_port_2              MESA_SYNCE_DEV_PORT(              2,      0)
#define eth_port_3              MESA_SYNCE_DEV_PORT(              3,      0)
#define eth_port_4              MESA_SYNCE_DEV_PORT(              4,      0)
#define eth_port_5              MESA_SYNCE_DEV_PORT(              5,      0)
#define eth_port_6              MESA_SYNCE_DEV_PORT(              6,      0)
#define eth_port_7              MESA_SYNCE_DEV_PORT(              7,      0)
#define station_clock_port_0    MESA_SYNCE_DEV_CLOCK_IN(          8,      0)

#define phy_mux_0_port_in_0              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_0_port_in_1              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_0_port_in_2              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_0_port_in_3              MESA_SYNCE_DEV_MUX_PHY(    100,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_0_port_out_0             MESA_SYNCE_DEV_MUX_PHY(    100,      0)
#define phy_mux_0_port_out_1             MESA_SYNCE_DEV_MUX_PHY(    100,      1)

#define phy_mux_1_port_in_0              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_1_port_in_1              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_1_port_in_2              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_1_port_in_3              MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_1_reco_clk_in_0          MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 4)
#define phy_mux_1_reco_clk_in_1          MESA_SYNCE_DEV_MUX_PHY(    200,      MESA_SYNCE_DEV_INPUT | 5)
#define phy_mux_1_port_out_0             MESA_SYNCE_DEV_MUX_PHY(    200,      0)
#define phy_mux_1_port_out_1             MESA_SYNCE_DEV_MUX_PHY(    200,      1)

#define dpll_port_0             MESA_SYNCE_DEV_DPLL(            500,      MESA_SYNCE_DEV_INPUT | 0)
#define dpll_port_1             MESA_SYNCE_DEV_DPLL(            500,      MESA_SYNCE_DEV_INPUT | 1)
#define dpll_port_4             MESA_SYNCE_DEV_DPLL(            500,      MESA_SYNCE_DEV_INPUT | 4)

/* When a port on phy device 100 is used for clk1, we want the signal to be routed to clk1_out on
   device 100 and from clk1_in to clk1_out on device 200. That restriction is not reflected in the above
   graph. It also allows the signal to be routed to clk2_out on device 100 and then from clk2_in to
   clk1_out on device 200. The mux setup is therefore not using the following graph, but is being
   hard coded in the application */

static const meba_synce_graph_element_t synce_graph_elements_8290_board[] = {
    // type                             source                    destination
    MESA_SYNCE_GRAPH_CONNECTION(        eth_port_0,               phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(        eth_port_1,               phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(        eth_port_2,               phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(        eth_port_3,               phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(        eth_port_4,               phy_mux_1_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(        eth_port_5,               phy_mux_1_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(        eth_port_6,               phy_mux_1_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(        eth_port_7,               phy_mux_1_port_in_3),

    MESA_SYNCE_GRAPH_CONNECTION(        phy_mux_0_port_out_0,     phy_mux_1_reco_clk_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(        phy_mux_0_port_out_1,     phy_mux_1_reco_clk_in_1),

    MESA_SYNCE_GRAPH_CONNECTION(        phy_mux_1_port_out_0,     dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(        phy_mux_1_port_out_1,     dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(        station_clock_port_0,     dpll_port_4),
};

static const meba_synce_terminal_attr_t attr_8290_board[] = {
    //              device                   attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,             MEBA_ATTR_CLOCK_ID,   1),
    MESA_SYNCE_ATTR(dpll_port_1,             MEBA_ATTR_CLOCK_ID,   2),
    MESA_SYNCE_ATTR(dpll_port_4,             MEBA_ATTR_CLOCK_ID,   3),

    MESA_SYNCE_ATTR(eth_port_0,              MEBA_ATTR_FREQ_1G,    MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,              MEBA_ATTR_FREQ_1G,    MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,              MEBA_ATTR_FREQ_1G,    MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,              MEBA_ATTR_FREQ_1G,    MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,              MEBA_ATTR_FREQ_1G,    MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,              MEBA_ATTR_FREQ_1G,    MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,              MEBA_ATTR_FREQ_1G,    MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,              MEBA_ATTR_FREQ_1G,    MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_0,              MEBA_ATTR_FREQ_100M,  MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(eth_port_1,              MEBA_ATTR_FREQ_100M,  MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(eth_port_2,              MEBA_ATTR_FREQ_100M,  MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(eth_port_3,              MEBA_ATTR_FREQ_100M,  MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(eth_port_4,              MEBA_ATTR_FREQ_100M,  MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(eth_port_5,              MEBA_ATTR_FREQ_100M,  MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(eth_port_6,              MEBA_ATTR_FREQ_100M,  MEBA_SYNCE_CLOCK_FREQ_25MHZ),
    MESA_SYNCE_ATTR(eth_port_7,              MEBA_ATTR_FREQ_100M,  MEBA_SYNCE_CLOCK_FREQ_25MHZ),
};

static mesa_rc meba_synce_graph_get(meba_inst_t inst, const meba_synce_graph_t **const g)
{
    static meba_synce_graph_t synce_graph;

    int board_type = inst->props.board_type;
    meba_synce_clock_hw_id_t dpll_type;

    if (meba_synce_spi_if_get_dpll_type(inst, &dpll_type) != MESA_RC_OK) {
        T_E(inst, "Failure probing DPLL type.");
    }

    if (board_type == VTSS_BOARD_LAN9668_8PORT_REF) {
        synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_8290_board);
        synce_graph.graph = synce_graph_elements_8290_board;
        synce_graph.attr = attr_8290_board;
        synce_graph.attr_length = MEBA_ARRSZ(attr_8290_board);
    } else {
        T_E(inst, "Board type not yet implemented.");
        synce_graph.graph_length = 0;
        synce_graph.graph = NULL;
        synce_graph.attr_length = 0;
        synce_graph.attr = NULL;
    }

    *g = &synce_graph;

    return MESA_RC_OK;
}

static mesa_rc meba_synce_mux_set(meba_inst_t  inst,
                                  uint32_t     dev_id,
                                  uint32_t     input,
                                  uint32_t     output)
{
    int board_type = inst->props.board_type;
    mepa_device_t *phy_dev;
    mepa_synce_clock_conf_t conf;
    T_D(inst, "Enter");

    if (board_type != VTSS_BOARD_LAN9668_8PORT_REF) {
        T_E(inst, "Board type not yet implemented.");
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if ((dev_id != 100) && (dev_id != 200)) {
        T_E(inst, "Invalid device.");
        return MESA_RC_ERROR;
    }

    if ((dev_id == 100) && ((input < (MESA_SYNCE_DEV_INPUT | 0)) || (input > (MESA_SYNCE_DEV_INPUT | 3)))) {
        // MESA_SYNCE_DEV_INPUT | (0-3) - Front port 1-4
        T_E(inst, "Invalid input.");
        return MESA_RC_ERROR;
    }
    if ((dev_id == 200) && input != 0
                        && input != 1
                        && ((input < (MESA_SYNCE_DEV_INPUT | 4)) || (input > (MESA_SYNCE_DEV_INPUT | 7)))) {
        // 0 - clk1_in
        // 1 - clk2_in
        // MESA_SYNCE_DEV_INPUT | (4-7) - Front port 5-8
        T_E(inst, "Invalid input.");
        return MESA_RC_ERROR;
    }
    if (output > 1) {
        T_E(inst, "Invalid output.");
        return MESA_RC_ERROR;
    }

    if ((dev_id == 200) && input != 0 && input != 1) {
        // Device 200 is configured to route a phy to the clk-out port. Thus disable
        // the clk-out on device 100
        phy_dev = inst->phy_devices[0];
        conf.src = MEPA_SYNCE_CLOCK_SRC_DISABLED;
        conf.dst = (output == 0) ? MEPA_SYNCE_CLOCK_DST_1 : MEPA_SYNCE_CLOCK_DST_2;
        if (MESA_RC_OK != mepa_synce_clock_conf_set(phy_dev, &conf)) {
            T_E(inst, "Failed disabling device 100 for clock %d", conf.dst);
        }
    }

    if (input & MESA_SYNCE_DEV_INPUT) {
        // A normal port
        uint32_t phy_port = input & ~MESA_SYNCE_DEV_INPUT;
        /* Get the PHY device */
        phy_dev = inst->phy_devices[phy_port];
        conf.src = MEPA_SYNCE_CLOCK_SRC_COPPER_MEDIA;
    } else {
        // A clk input (0 or 1)
        phy_dev = (dev_id == 100) ? inst->phy_devices[0] : inst->phy_devices[4];
        conf.src = MEPA_SYNCE_CLOCK_SRC_CLOCK_IN_1 + input;
    }

    conf.dst = (output == 0) ? MEPA_SYNCE_CLOCK_DST_1 : MEPA_SYNCE_CLOCK_DST_2;
    conf.freq = MEPA_FREQ_125M;
    return mepa_synce_clock_conf_set(phy_dev, &conf);
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
