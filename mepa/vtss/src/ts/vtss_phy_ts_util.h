// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PHY_TS_UTIL_H_
#define _VTSS_PHY_TS_UTIL_H_

#include <vtss_phy_api.h>

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_CHIP_CU_PHY)
BOOL  vtss_phy_ts_algo_execute_check(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no);


extern vtss_rc vtss_phy_ts_read_csr(vtss_state_t *vtss_state,
                                    const vtss_port_no_t port_no,
                                    const vtss_phy_ts_blk_id_t blk_id,
                                    const u16 csr_address,
                                    u32 *const value);

extern vtss_rc vtss_phy_ts_write_csr(vtss_state_t *vtss_state,
                                    const vtss_port_no_t port_no,
                                    const vtss_phy_ts_blk_id_t blk_id,
                                    const u16 csr_address,
                                    const u32 *const value);

extern vtss_rc vtss_phy_id_get_priv(vtss_state_t *vtss_state,
                                    const vtss_port_no_t   port_no,
                                    vtss_phy_type_t *phy_id);

#if defined(VTSS_VIPER_B_FIFO_RESET)
vtss_rc vtss_phy_1588_oos_mitigation_steps_private(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t port_no,
                                                   const vtss_phy_ts_fifo_conf_t   *fifo_conf);


vtss_rc vtss_phy_ts_isolate_phy(vtss_state_t *vtss_state,
                                const vtss_port_no_t port_no);

#endif
#endif /* #if defined(VTSS_CHIP_CU_PHY)*/
#endif /* VTSS_OPT_PHY_TIMESTAMP */
#endif /* _VTSS_PHY_TS_UTIL_H_ */

