// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PHY_TS_H_
#define _VTSS_PHY_TS_H_

#include <vtss_phy_api.h>

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#include "../common/vtss_phy_common.h"
typedef enum {
    VTSS_PHY_TS_ANA_BLK_ID_ING_0, /* Order taken from 1G PHY */
    VTSS_PHY_TS_ANA_BLK_ID_EGR_0,
    VTSS_PHY_TS_ANA_BLK_ID_ING_1,
    VTSS_PHY_TS_ANA_BLK_ID_EGR_1,
    VTSS_PHY_TS_ANA_BLK_ID_ING_2,
    VTSS_PHY_TS_ANA_BLK_ID_EGR_2,
    VTSS_PHY_TS_PROC_BLK_ID_0,
    VTSS_PHY_TS_PROC_BLK_ID_1,
    VTSS_PHY_TS_MAX_BLK_ID
} vtss_phy_ts_blk_id_t;

#define VTSS_PHY_TS_DISP_CSR(c,b,a,v) \
                     if ( vtss_phy_ts_read_csr(vtss_state, c, b, a, v) == VTSS_RC_OK ) { printf("0x%08lx ",(long unsigned int)*v); }

#define VTSS_PHY_TS_READ_CSR(p, b, a, v) vtss_phy_ts_read_csr(vtss_state, p, b, a, v)

#define VTSS_PHY_TS_WRITE_CSR(p, b, a, v) vtss_phy_ts_write_csr(vtss_state, p , b, a, v)
#if !defined(VTSS_PHY_TS_CLR_BITS)
#define  VTSS_PHY_TS_CLR_BITS(value, mask)   ((value) & ~(mask))
#endif

#define VTSS_PHY_TS_ANA_BLK_ID_ING(x) VTSS_PHY_TS_ANA_BLK_ID_ING_##x
#define VTSS_PHY_TS_ANA_BLK_ID_EGR(x) VTSS_PHY_TS_ANA_BLK_ID_EGR_##x
#define VTSS_PHY_TS_PROC_BLK_ID(x)    VTSS_PHY_TS_PROC_BLK_ID_##x

#ifdef VTSS_FEATURE_WARM_START
/**
 * \brief This is used to sync the vtss_state to PHY.
 *
 * \param port_no      [IN]      port number
 *
 * \return Return code.
 **/
extern vtss_rc vtss_phy_ts_sync(vtss_state_t *vtss_state, const vtss_port_no_t port_no);

#endif /* VTSS_FEATURE_WARM_START */

extern void vtss_phy_ts_api_ail_debug_print(vtss_state_t *vtss_state,
                                            const vtss_debug_printf_t pr,
                                            const vtss_debug_info_t   *const info);

extern void vtss_phy_ts_api_cil_debug_print(vtss_state_t *vtss_state,
                                            const vtss_debug_printf_t pr,
                                            const vtss_debug_info_t   *const info);

vtss_rc vtss_phy_ts_macsec_mode_change (vtss_state_t *vtss_state,
                                        const vtss_port_no_t port_no,
                                        const BOOL enable);

vtss_rc vtss_phy_ts_phy_status_change_priv(vtss_state_t *vtss_state,
                                           const vtss_port_no_t       port_no);


vtss_rc vtss_phy_ts_bypass_set(vtss_state_t    *vtss_state,
                               const vtss_port_no_t   port_no, 
                               BOOL enable,
                               BOOL force_bypass);


vtss_rc vtss_phy_ts_version_check(vtss_state_t    *vtss_state,
                                  const vtss_port_no_t port_no,
                                  BOOL *prevent);

#if defined(VTSS_VIPER_B_FIFO_RESET)
typedef struct vtss_phy_ts_overflow_info_s{
    u32 egr_intr_status;
    u32 ingr_intr_status;
}vtss_phy_ts_overflow_info_t;
typedef struct vtss_phy_ts_pop_fifo_s{
    u32 egr_pop_fifo;
    u32 ingr_pop_fifo;
}vtss_phy_ts_pop_fifo_t;

vtss_rc vtss_phy_ts_sw_pop_fifo(vtss_state_t *vtss_state,
                                const vtss_port_no_t port_no,
                                BOOL val);

vtss_rc vtss_phy_intr_status(vtss_state_t *vtss_state,
                             const vtss_port_no_t port_no,
                             vtss_phy_ts_overflow_info_t *overflow_conf);

vtss_rc vtss_phy_sw_pop_fifo_get(vtss_state_t *vtss_state,
                                 const vtss_port_no_t port_no,
                                 vtss_phy_ts_pop_fifo_t *pop_fifo);

vtss_rc vtss_phy_ts_en_pkt_mode(vtss_state_t *vtss_state,
                                const vtss_port_no_t port_no,
                                BOOL enable);

BOOL  vtss_phy_ts_algo_execute_check(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no);

#endif /* VIPER_B_FIFO_RESET */


#endif /* VTSS_OPT_PHY_TIMESTAMP */

#endif /* _VTSS_PHY_TS_H_ */

