// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "microchip/ethernet/board/api.h"

#include "meba_aux.h"

mesa_rc meba_tod_phy_ts_clk_info(meba_inst_t inst,
                                 mepa_port_no_t       port,
                                 mepa_ts_clock_freq_t *freq,
                                 mepa_ts_clock_src_t *src,
                                 mepa_timeinterval_t *pps_load_delay,
                                 mepa_timeinterval_t *pps_save_delay)
{
    *freq = VTSS_PHY_TS_CLOCK_FREQ_250M;
    *src = VTSS_PHY_TS_CLOCK_SRC_INTERNAL;
    T_I(inst, "Ocelot board 250Mhz internal");

    /* default 1pps latency for the phy is 2 clock cycles (in the serval environment the delay is split into output latency from Serval and input latency in the PHY) */
    *pps_load_delay = (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 3LL) / clk_mhz[*freq];
    *pps_save_delay = (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 2LL) / clk_mhz[*freq];

    return MESA_RC_OK;
}

static meba_api_tod_t public_functions = {
#define X(name) . name = name,
    MEBA_LIST_OF_API_TOD_CALLS
#undef X
};

meba_api_tod_t *meba_tod_get()
{
    return &public_functions;
}
