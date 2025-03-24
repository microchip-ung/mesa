// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "microchip/ethernet/board/api.h"

#include "meba_aux.h"
#include "meba_common.h"

mesa_rc meba_tod_phy_ts_clk_info(meba_inst_t           inst,
                                 mepa_port_no_t        port,
                                 mepa_ts_clock_freq_t *freq,
                                 mepa_ts_clock_src_t  *src,
                                 mepa_timeinterval_t  *pps_load_delay,
                                 mepa_timeinterval_t  *pps_save_delay)
{
    meba_board_state_t *board;
    board = INST2BOARD(inst);

    switch (board->type) {
    case BOARD_TYPE_LAGUNA_PCB8398:
        T_I(inst, "PCB8398 board with Indy phy");
        *freq = MEPA_TS_CLOCK_FREQ_25M;
        *src = MEPA_TS_CLOCK_SRC_EXT_1588_REF_CLOCK;
        break;
    case BOARD_TYPE_SPARX5_PCB135:
        T_I(inst, "PCB135 board with Indy phy");
        *freq = MEPA_TS_CLOCK_FREQ_250M;
        *src = MEPA_TS_CLOCK_SRC_EXT_1588_REF_CLOCK;
        break;
    default: T_I(inst, "Board type not supported: %d", board->type);
    }

    /* default 1pps latency for the phy is 2 clock cycles (updated from ocelot) */
    *pps_load_delay =
        (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 3LL) / clk_mhz[*freq];
    *pps_save_delay =
        (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 2LL) / clk_mhz[*freq];

    return MESA_RC_OK;
}

static meba_api_tod_t public_functions = {
#define X(name) .name = name,
    MEBA_LIST_OF_API_TOD_CALLS
#undef X
};

meba_api_tod_t *meba_tod_get() { return &public_functions; }
