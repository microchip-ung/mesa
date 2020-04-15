/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_PHY_TS_UTIL_H_
#define _VTSS_PHY_TS_UTIL_H_

#include <vtss/api/types.h>


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

