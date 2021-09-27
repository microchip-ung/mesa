// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "microchip/ethernet/board/api.h"

#include "meba_aux.h"

mesa_rc meba_tod_phy_ts_clk_info_1g(meba_inst_t inst,
                                    mepa_ts_clock_freq_t *freq,
                                    mepa_ts_clock_src_t *src,
                                    mepa_timeinterval_t *pps_load_delay,
                                    mepa_timeinterval_t *pps_save_delay)
{
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
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
