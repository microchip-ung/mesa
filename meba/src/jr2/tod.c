/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "mscc/ethernet/board/api.h"

#include "meba_aux.h"

mesa_rc meba_tod_phy_ts_clk_info_1g(meba_inst_t inst,
                                    mesa_phy_ts_clockfreq_t *freq,
                                    mesa_phy_ts_clock_src_t *src,
                                    mesa_timeinterval_t *pps_load_delay,
                                    mesa_timeinterval_t *pps_save_delay)
{
    *src = MESA_PHY_TS_CLOCK_SRC_EXTERNAL;
    *freq = MESA_PHY_TS_CLOCK_FREQ_250M;

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
