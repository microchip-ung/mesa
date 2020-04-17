// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "mscc/ethernet/board/api.h"

#include "meba_aux.h"

mesa_rc meba_tod_phy_ts_clk_info_1g(meba_inst_t inst,
                                    mesa_phy_ts_clockfreq_t *freq,
                                    mesa_phy_ts_clock_src_t *src,
                                    mesa_timeinterval_t *pps_load_delay,
                                    mesa_timeinterval_t *pps_save_delay)
{
    mesa_rc rc = MESA_RC_OK;
    mesa_chip_id_t  chip_id;

    /* Because of a request to be able to run PTP on the Serval1 boards without SyncE, the PHY LTC is connected to CLKOUT2 from Serval that generates 250 Mhz, if serval rev is > A, on Rev a the CLKOUT2 is 156,25 MHz */
    if ((rc = mesa_chip_id_get(NULL, &chip_id)) == MESA_RC_OK) {
        T_I(inst, "Chip ID = %x, rev = %d", chip_id.part_number, chip_id.revision);
    } else {
        T_I(inst, "Could not read Chip ID. Error code: %x", rc);
    }

    if (rc == MESA_RC_OK && chip_id.revision < 1) {
        T_I(inst, "250 MHZ clockout2 not supported on Serval rev A");
        *freq = MESA_PHY_TS_CLOCK_FREQ_15625M;
        *src = MESA_PHY_TS_CLOCK_SRC_EXTERNAL;
        T_I(inst, "Serval1 board 155,25Mhz internal");
    } else {
        *freq = MESA_PHY_TS_CLOCK_FREQ_250M;
        *src = MESA_PHY_TS_CLOCK_SRC_EXTERNAL;
        T_I(inst, "Serval1 board 250Mhz internal");
    }

    /* default 1pps latency for the phy is 2 clock cycles (in the serval environment the delay is split into output latency from Serval and input latency in the PHY) */
    *pps_load_delay = (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 3LL) / clk_mhz[*freq];
    *pps_save_delay = (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 2LL) / clk_mhz[*freq];

    return rc;
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
