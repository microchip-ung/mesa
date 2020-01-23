// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_MAS_CIL_H_
#define _VTSS_MAS_CIL_H_

#include "vtss_api.h"

#if defined(VTSS_ARCH_LAN966X)
#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#include "../ail/vtss_state.h"
#include "../ail/vtss_common.h"
#include "../ail/vtss_util.h"
#include "vtss_lan966x.h"
#include "vtss_lan966x_regs.h"

/* ================================================================= *
 *  Register access
 * ================================================================= */
// TBD
#define IOREG(t,_z2,_z3,_z4,_z5,_z6,_z7,_z8,_z9,_z10,_z11) (_z2 +_z5)

extern vtss_rc (*vtss_lan966x_wr)(vtss_state_t *vtss_state, u32 addr, u32 value);
extern vtss_rc (*vtss_lan966x_rd)(vtss_state_t *vtss_state, u32 addr, u32 *value);
vtss_rc vtss_lan966x_wrm(vtss_state_t *vtss_state, u32 reg, u32 value, u32 mask);

#define REG_RD(p, val)                                                  \
    {                                                                   \
        vtss_rc __rc = vtss_lan966x_rd(vtss_state, IOREG(p), val);      \
        if (__rc != VTSS_RC_OK)                                         \
            return __rc;                                                \
    }

#define REG_WR(p, val)                                                  \
    {                                                                   \
        vtss_rc __rc = vtss_lan966x_wr(vtss_state, IOREG(p), val);      \
        if (__rc != VTSS_RC_OK)                                         \
            return __rc;                                                \
    }

#define REG_WRM(p, val, msk)                                            \
    {                                                                   \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, IOREG(p), val, msk); \
        if (__rc != VTSS_RC_OK)                                         \
            return __rc;                                                \
    }

#define REG_WRM_SET(p, msk)                                             \
    {                                                                   \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, IOREG(p), msk, msk); \
        if (__rc != VTSS_RC_OK)                                         \
            return __rc;                                                \
    }

#define REG_WRM_CLR(p, msk)                                             \
    {                                                                   \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, IOREG(p), 0, msk);  \
        if (__rc != VTSS_RC_OK)                                         \
            return __rc;                                                \
    }

#define REG_WRM_CTL(p, _cond_, msk)                                     \
    {                                                                   \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, IOREG(p), (_cond_) ? (msk) : 0, msk); \
        if (__rc != VTSS_RC_OK)                                         \
            return __rc;                                                \
    }

/* ================================================================= *
 *  Chip ports
 * ================================================================= */
#define VTSS_CHIP_PORTS      8    /* Port 0-7 */
#define VTSS_CHIP_PORT_CPU   VTSS_CHIP_PORTS /* Next port is CPU port */
#define VTSS_CHIP_PORT_CPU_0 (VTSS_CHIP_PORT_CPU + 0) /* Aka. CPU Port 8 */
#define VTSS_CHIP_PORT_CPU_1 (VTSS_CHIP_PORT_CPU + 1) /* Aka. CPU Port 9 */
#define VTSS_CHIP_PORT_MASK  VTSS_BITMASK(VTSS_CHIP_PORTS) /* Chip port mask */

#define LAN966X_ACS          16  /* Number of aggregation masks */

/* Reserved PGIDs */
#define PGID_UC     (VTSS_PGIDS - 4)
#define PGID_MC     (VTSS_PGIDS - 3)
#define PGID_MCIPV4 (VTSS_PGIDS - 2)
#define PGID_MCIPV6 (VTSS_PGIDS - 1)
#define PGID_AGGR   (VTSS_PGIDS)
#define PGID_SRC    (PGID_AGGR + LAN966X_ACS)

/* ================================================================= *
 *  Common functions
 * ================================================================= */
vtss_rc vtss_lan966x_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
u32 vtss_lan966x_port_mask(vtss_state_t *vtss_state, const BOOL member[]);

vtss_rc vtss_lan966x_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_lan966x_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no);

vtss_rc vtss_lan966x_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_afi_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

#endif /* VTSS_ARCH_LAN966X */
#endif /* _VTSS_MAS_CIL_H_ */
