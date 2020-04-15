/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#ifndef _MSCC_ETHERNET_BOARD_TOD_H_
#define _MSCC_ETHERNET_BOARD_TOD_H_

#include <stdint.h>
#include <mscc/ethernet/switch/api.h>
#include <mscc/ethernet/board/api/types.h>
#include <mscc/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// Function returns board specific info about the PHY ts clock
// freq           [OUT] The input frequency to the timestamp engine in the PHY
// src            [OUT] The clock source used for the timestamp engine
// pps_load_delay [OUT] The delay from PPS going high to time where load
//                      register is loaded into the timestamp engine
// pps_save_delay [OUT] The delay from PPS going high to the time being saved
//                      into the save register
typedef mesa_rc (*meba_tod_phy_ts_clk_info_1g_t)(
        struct meba_inst        *inst,
        mesa_phy_ts_clockfreq_t *freq,
        mesa_phy_ts_clock_src_t *src,
        mesa_timeinterval_t     *pps_load_delay,
        mesa_timeinterval_t     *pps_save_delay);


#define MEBA_LIST_OF_API_TOD_CALLS  \
    X(meba_tod_phy_ts_clk_info_1g)  \

typedef struct {
    meba_tod_phy_ts_clk_info_1g_t meba_tod_phy_ts_clk_info_1g;
} meba_api_tod_t;

#include <mscc/ethernet/board/api/hdr_end.h>
#endif // _MSCC_ETHERNET_BOARD_TOD_H_
