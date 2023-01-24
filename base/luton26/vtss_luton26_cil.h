// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_LUTON26_CIL_H_
#define _VTSS_LUTON26_CIL_H_

/* Use relative DWORD addresses for registers - must be first */
#define VTSS_IOADDR(t,o) ((((t) - VTSS_TO_DEVCPU_ORG) >> 2) + (o))
#define VTSS_IOREG(t,o)  (VTSS_IOADDR(t,o))

// Avoid "vtss_api.h not used in module vtss_luton26.c"
/*lint --e{766} */

#include "vtss_api.h"

#if defined(VTSS_ARCH_LUTON26)
#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#include "../ail/vtss_state.h"
#include "../ail/vtss_common.h"
#include "../ail/vtss_util.h"
#include "vtss_luton26.h"
#include "vtss_luton26_reg.h"

/* Chip ports - See PD0071 Sect 4.1 */
#define VTSS_CHIP_PORTS           26
/* On the switch core side, the CPU port is one single port */
#define VTSS_CHIP_PORT_CPU        VTSS_CHIP_PORTS
/* On the CPU Port module side, the switch CPU port is split into two "CPU ports" */
#define VTSS_CHIP_PORT_CPU_0      (VTSS_CHIP_PORT_CPU + 0) /* A.k.a. CPU Port 26 */
#define VTSS_CHIP_PORT_CPU_1      (VTSS_CHIP_PORT_CPU + 1) /* A.k.a. CPU Port 27 */
#define VTSS_CHIP_PORT_MASK       ((1U<<VTSS_CHIP_PORTS)-1)

#define CPU_INJ_REG     0 /* CPU Injection GRP - register based */
#define CPU_INJ_DMA     1 /* CPU Injection GRP - DMA based */

#define L26_ACS   16  /* Number of aggregation masks */

/* Buffer constants */
#define L26_BUFFER_MEMORY 512000
#define L26_BUFFER_REFERENCE 5500
#define L26_BUFFER_CELL_SZ 48

/* Reserved PGIDs */
#define PGID_UC      (VTSS_PGID_LUTON26-4)
#define PGID_MC      (VTSS_PGID_LUTON26-3)
#define PGID_MCIPV4  (VTSS_PGID_LUTON26-2)
#define PGID_MCIPV6  (VTSS_PGID_LUTON26-1)
#define PGID_AGGR    (VTSS_PGID_LUTON26)
#define PGID_SRC     (PGID_AGGR + L26_ACS)

/* Policers, last policers used for ACLs */
#define L26_ACL_POLICER_DISC   26 /* Reserved for ACL discarding */
#define L26_ACL_POLICER_OFFSET (VTSS_L26_POLICER_CNT - VTSS_ACL_POLICERS)

/* sFlow H/W-related min/max */
#define LU26_SFLOW_MIN_SAMPLE_RATE    0 /**< Minimum allowable sampling rate for sFlow */
#define LU26_SFLOW_MAX_SAMPLE_RATE 4095 /**< Maximum allowable sampling rate for sFlow */

/* ================================================================= *
 *  Register acces
 * ================================================================= */

#define L26_RD(p, value)                                   \
    {                                                      \
        vtss_rc __rc = vtss_l26_rd(vtss_state, p, value);  \
        if (__rc != VTSS_RC_OK)                            \
            return __rc;                                   \
    }

#define L26_WR(p, value)                                   \
    {                                                      \
        vtss_rc __rc = vtss_l26_wr(vtss_state, p, value);  \
        if (__rc != VTSS_RC_OK)                            \
            return __rc;                                   \
    }

// Read modify write.
//
// p     : Register to modify
// value : New value
// mask  : Bits to be affected.
#define L26_WRM(p, value, mask)                                   \
    {                                                             \
        vtss_rc __rc = vtss_l26_wrm(vtss_state, p, value, mask);  \
        if (__rc != VTSS_RC_OK)                                   \
            return __rc;                                          \
    }

#define L26_WRM_SET(p, mask) L26_WRM(p, mask, mask)
#define L26_WRM_CLR(p, mask) L26_WRM(p, 0,    mask)
#define L26_WRM_CTL(p, _cond_, mask) L26_WRM(p, (_cond_ ? mask : 0), mask)

/* Decode register bit field */
#define L26_BF(name, value) ((VTSS_F_##name & value) ? 1 : 0)

vtss_rc vtss_l26_wr(vtss_state_t *vtss_state, u32 addr, u32 value);
vtss_rc vtss_l26_rd(vtss_state_t *vtss_state, u32 addr, u32 *value);
vtss_rc vtss_l26_wrm(vtss_state_t *vtss_state, u32 reg, u32 value, u32 mask);

/* ----------------------------------------------------------------- */

typedef struct {
    BOOL frame_rate; /* Enable frame rate policing (always single bucket) */
    BOOL dual;       /* Enable dual leaky bucket mode */
    BOOL data_rate;  /* Enable data rate policing */
    u32  cir;        /* CIR in kbps/fps (ignored in single bucket mode) */
    u32  cbs;        /* CBS in bytes/frames (ignored in single bucket mode) */
    u32  eir;        /* EIR (PIR) in kbps/fps */
    u32  ebs;        /* EBS (PBS) in bytes/frames */
    BOOL cf;         /* Coupling flag (ignored in single bucket mode) */
} vtss_l26_policer_conf_t;

/* ----------------------------------------------------------------- */

/* Common functions */
vtss_rc vtss_l26_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
u32 vtss_l26_port_mask(vtss_state_t *vtss_state, const BOOL member[]);
void vtss_l26_debug_reg_header(const vtss_debug_printf_t pr, const char *name);
void vtss_l26_debug_reg(vtss_state_t *vtss_state,
                        const vtss_debug_printf_t pr, u32 addr, const char *name);
void vtss_l26_debug_reg_inst(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name);
void vtss_l26_debug_print_port_header(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr, const char *txt);

/* Port functions */
vtss_rc vtss_l26_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_l26_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_l26_port_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
/* Miscellaneous functions */
vtss_rc vtss_l26_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_l26_gpio_mode(vtss_state_t           *vtss_state,
                           const vtss_chip_no_t   chip_no,
                           const vtss_gpio_no_t   gpio_no,
                           const vtss_gpio_mode_t mode);
vtss_rc vtss_l26_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id);
vtss_rc vtss_l26_misc_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);

/* QoS functions */
vtss_rc vtss_l26_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_l26_port_policer_fc_set(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no, u32 chipport);
vtss_rc vtss_l26_policer_conf_set(vtss_state_t *vtss_state, vtss_policer_user_t user,
                                  u32 policer, BOOL enable, vtss_l26_policer_conf_t *conf);
vtss_rc vtss_l26_policer_free_get(vtss_state_t *vtss_state, u16 *new);
vtss_rc vtss_l26_qos_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
vtss_rc vtss_l26_evc_policer_conf_set(vtss_state_t *vtss_state,
                                      const vtss_evc_policer_id_t policer_id);
#endif /* VTSS_FEATURE_QOS_POLICER_DLB */
vtss_rc vtss_l26_qos_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);

/* L2 functions */
vtss_rc vtss_l26_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_l26_vcl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_l26_l2_debug_print(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);

/* Packet functions */
vtss_rc vtss_l26_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_l26_packet_debug_print(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info);

/* VCAP functions */
vtss_rc vtss_l26_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_l26_acl_policer_move(vtss_state_t *vtss_state, u32 policer);
vtss_rc vtss_l26_acl_evc_policer_move(vtss_state_t *vtss_state,
                                      vtss_policer_user_t user, u32 policer_id,
                                      u16 policer_old, u16 policer_new);
vtss_rc vtss_l26_debug_range_checkers(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info);
vtss_rc vtss_l26_debug_vcap_port(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
vtss_rc vtss_l26_debug_vcap_is1(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);
vtss_rc vtss_l26_debug_vcap_es0(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);
vtss_rc vtss_l26_vcap_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
#if defined(VTSS_FEATURE_TIMESTAMP)
/* Timestamp functions */
vtss_rc vtss_l26_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_l26_ts_debug_print(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_TIMESTAMP */

#endif /* VTSS_ARCH_LUTON26 */
#endif /* _VTSS_LUTON26_CIL_H_ */
