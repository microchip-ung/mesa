// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_BOARD_TOD_H_
#define _MICROCHIP_ETHERNET_BOARD_TOD_H_

#include <stdint.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// Function returns board specific info about the PHY ts clock
// freq           [OUT] The input frequency to the timestamp engine in the PHY
// src            [OUT] The clock source used for the timestamp engine
// pps_load_delay [OUT] The delay from PPS going high to time where load
//                      register is loaded into the timestamp engine
// pps_save_delay [OUT] The delay from PPS going high to the time being saved
//                      into the save register
typedef mesa_rc (*meba_tod_phy_ts_clk_info_t)(
        struct meba_inst        *inst,
        mepa_port_no_t          port,
        mepa_ts_clock_freq_t    *freq,
        mepa_ts_clock_src_t     *src,
        mepa_timeinterval_t     *pps_load_delay,
        mepa_timeinterval_t     *pps_save_delay);


#define MEBA_LIST_OF_API_TOD_CALLS  \
    X(meba_tod_phy_ts_clk_info)     \

typedef struct {
    meba_tod_phy_ts_clk_info_t meba_tod_phy_ts_clk_info;
} meba_api_tod_t;

#include <microchip/ethernet/board/api/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_BOARD_TOD_H_
