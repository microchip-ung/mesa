// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_SERVAL_CIL_H_
#define _VTSS_SERVAL_CIL_H_

/* Use relative DWORD addresses for registers - must be first */
#define VTSS_IOADDR(t,o) ((((t) - VTSS_IO_ORIGIN1_OFFSET) >> 2) + (o))
#define VTSS_IOREG(t,o)  (VTSS_IOADDR(t,o))

// Avoid "vtss_serval_cil.h not used in module vtss_serval.c"
/*lint --e{766} */

#include "vtss_api.h"

#if defined(VTSS_ARCH_OCELOT)
#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#include "../ail/vtss_state.h"
#include "../ail/vtss_common.h"
#include "../ail/vtss_util.h"
#include "vtss_ocelot.h"
#include "vtss_ocelot_reg.h"

#include "../ail/vtss_pll5g_procs.h"
#include "vtss_ocelot_pll5g_setup.h"

#define VTSS_CHIP_PORTS      11    /* Port 0-10 */
#define VTSS_CHIP_PORT_CPU   VTSS_CHIP_PORTS /* Next port is CPU port */
#define VTSS_CHIP_PORT_CPU_0 (VTSS_CHIP_PORT_CPU + 0) /* Aka. CPU Port 11 */
#define VTSS_CHIP_PORT_CPU_1 (VTSS_CHIP_PORT_CPU + 1) /* Aka. CPU Port 12 */
#define VTSS_CHIP_PORT_MASK  VTSS_BITMASK(VTSS_CHIP_PORTS) /* Chip port mask */

/* Policers */
#define SRVL_POLICER_PORT    0    /* 0-11    : Port policers (11 unused) */
#define SRVL_POLICER_ACL     12   /* 12-31   : ACL policers (28-31 unused) */
#define SRVL_POLICER_QUEUE   32   /* 32-127  : Queue policers (120-127 unused) */
#define SRVL_POLICER_EVC     129  /* 129-382 : EVC policers (128 unused) */
#define SRVL_POLICER_DISCARD 383  /* 383     : Discard policer */
#define SRVL_POLICER_CNT     384  /* Total number of policers */

/* Ocelot has 4 PTP PIN configurations that can be used for different purposes, the defines below defines the
 * default usage of the 4 pins.
 */
/* PIN configuration for external clock */
#define EXT_CLK_PIN 2           /* external clock 1 pps input */
#define EXT_PPS_PIN 0           /* 1pps pulse output */
#define TOD_ACC_PIN 4           /* pin used for timeofday get/set */

/* PIN configuration for alternative (RS422) clock. Note that 1pps pulse is the same pin as EXT_PPS_PIN, i.e. the application must ensure that only one of the features are enabled at the same time. */
#define ALT_LDST_PIN 3          /* alternative clock 1 pps input (Load/Store) */
#define ALT_PPS_PIN  0          /* alternative clock 1pps pulse */

/* Buffer constants */
#define SRVL_BUFFER_MEMORY     229380
#define SRVL_BUFFER_REFERENCE    1911
#define SRVL_BUFFER_CELL_SZ        60

/* Number of full entries */
#if defined(VTSS_FEATURE_IS0)
#define SRVL_IS0_CNT (VTSS_SRVL_IS0_CNT/2)
#endif /* VTSS_FEATURE_IS0 */
#define SRVL_IS1_CNT (VTSS_SRVL_IS1_CNT/4)
#define SRVL_IS2_CNT (VTSS_SRVL_IS2_CNT/4)
#define SRVL_ES0_CNT VTSS_SRVL_ES0_CNT

#define SRVL_ACS          16  /* Number of aggregation masks */

/* Reserved PGIDs */
#define PGID_UC      (VTSS_PGID_LUTON26 - 4)
#define PGID_MC      (VTSS_PGID_LUTON26 - 3)
#define PGID_MCIPV4  (VTSS_PGID_LUTON26 - 2)
#define PGID_MCIPV6  (VTSS_PGID_LUTON26 - 1)
#define PGID_AGGR    (VTSS_PGID_LUTON26)
#define PGID_SRC     (PGID_AGGR + SRVL_ACS)

#if defined(VTSS_CHIP_SERVAL)
#define SRVL_EVC_CNT 1024
#else
#define SRVL_EVC_CNT 256
#endif /* VTSS_CHIP_SERVAL */

#define SEG_I(idx) vtss_state->mpls.segment_conf[idx]
#define XC_I(idx)  vtss_state->mpls.xc_conf[idx]
#define VP_I(idx)  vtss_state->mpls.vprofile_conf[idx]
#define L2_I(idx)  vtss_state->mpls.l2_conf[idx]

#define SEG_P(idx) SEG_I(idx).pub
#define XC_P(idx)  XC_I(idx).pub
#define VP_P(idx)  VP_I(idx).pub
#define L2_P(idx)  L2_I(idx).pub

/* ================================================================= *
 *  Register access
 * ================================================================= */
extern vtss_rc (*vtss_srvl_wr)(vtss_state_t *vtss_state, u32 addr, u32 value);
extern vtss_rc (*vtss_srvl_rd)(vtss_state_t *vtss_state, u32 addr, u32 *value);
vtss_rc vtss_srvl_wrm(vtss_state_t *vtss_state, u32 reg, u32 value, u32 mask);

#define SRVL_RD(p, value)                 \
    {                                     \
        vtss_rc __rc = vtss_srvl_rd(vtss_state, p, value);    \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    }

#define SRVL_WR(p, value)                 \
    {                                     \
        vtss_rc __rc = vtss_srvl_wr(vtss_state, p, value);    \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    }

#define SRVL_WRM(p, value, mask)                 \
    {                                            \
        vtss_rc __rc = vtss_srvl_wrm(vtss_state, p, value, mask);     \
        if (__rc != VTSS_RC_OK)                  \
            return __rc;                         \
    }

#define SRVL_WRM_SET(p, mask) SRVL_WRM(p, mask, mask)
#define SRVL_WRM_CLR(p, mask) SRVL_WRM(p, 0,    mask)
#define SRVL_WRM_CTL(p, _cond_, mask) SRVL_WRM(p, (_cond_) ? mask : 0, mask)

/* Decode register bit field */
#define SRVL_BF(name, value) ((VTSS_F_##name & value) ? 1 : 0)

/* Common functions */
vtss_rc vtss_srvl_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
u32 vtss_srvl_port_mask(vtss_state_t *vtss_state, const BOOL member[]);
vtss_rc srvl_isdx_table_idle(vtss_state_t *vtss_state);
vtss_rc vtss_srvl_isdx_update_es0(vtss_state_t *vtss_state,
                                  BOOL isdx_ena, u32 isdx, u32 isdx_mask);
vtss_rc vtss_srvl_isdx_update(vtss_state_t *vtss_state,
                              BOOL isdx_ena, u32 isdx, u32 isdx_mask, u32 pol_idx, u32 voe_idx);
void vtss_srvl_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2, 
                         vtss_chip_counter_t *c1, vtss_chip_counter_t *c2);
void vtss_srvl_debug_reg_header(const vtss_debug_printf_t pr, const char *name);
void vtss_srvl_debug_reg(vtss_state_t *vtss_state,
                         const vtss_debug_printf_t pr, u32 addr, const char *name);
void vtss_srvl_debug_reg_inst(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name);
void vtss_srvl_debug_print_port_header(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr, const char *txt);
void vtss_srvl_debug_print_mask(const vtss_debug_printf_t pr, u32 mask);

vtss_rc vtss_srvl_debug_isdx_list(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr, vtss_sdx_entry_t *isdx_list, 
                                  u32 id, BOOL *header, BOOL ece);

/* Port functions */
vtss_rc vtss_srvl_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_srvl_port_debug_print(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info);
vtss_rc vtss_srvl_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_srvl_counter_update(vtss_state_t *vtss_state,
                                 u32 *addr, vtss_chip_counter_t *counter, BOOL clear);

u32 vtss_srvl_wm_high_get(vtss_state_t *vtss_state, u32 queue); /* Returns WRED wm_high in bytes */
vtss_rc vtss_srvl_wm_update(vtss_state_t *vtss_state);

/* Miscellaneous functions */
vtss_rc vtss_srvl_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_srvl_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id);
#if defined(VTSS_GPIOS)
vtss_rc vtss_srvl_gpio_mode(vtss_state_t *vtss_state,
                            const vtss_chip_no_t   chip_no,
                            const vtss_gpio_no_t   gpio_no,
                            const vtss_gpio_mode_t mode);
#endif /* VTSS_GPIOS */
vtss_rc vtss_srvl_misc_debug_print(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info);

/* QoS functions */
vtss_rc vtss_srvl_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_srvl_qos_port_conf_change(vtss_state_t *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const u32 port,
                                       const u32 link_speed);
vtss_rc vtss_srvl_qos_policer_conf_set(vtss_state_t *vtss_state,
                                       u32 policer,
                                       vtss_policer_conf_t *conf);
vtss_rc vtss_srvl_qos_shaper_conf_set(vtss_state_t            *vtss_state,
                                      vtss_shaper_t           *shaper,
                                      u32                      se,
                                      BOOL                     dlb_ena,
                                      u32                      dlb_sense_port,
                                      u32                      dlb_sense_qos,
                                      vtss_shaper_calibrate_t *calibrate);
vtss_rc vtss_srvl_qos_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);

/* L2 functions */
vtss_rc vtss_srvl_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_srvl_l2_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);

/* Packet functions */
vtss_rc vtss_srvl_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_srvl_packet_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info);

#if defined(VTSS_FEATURE_AFI_SWC)
vtss_rc vtss_srvl_afi_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_AFI_SWC */

#if 1
/* ----------------------------------------------------------------- *
 * Raw MPLS encapsulation.
 *
 * WARNING: Special use, not used by other MPLS functionality.
 *
 * WARNING: Serval-specific!
 * ----------------------------------------------------------------- */

#define VTSS_SRVL_MPLS_OUT_ENCAP_RAW_MAX_BYTE_CNT  (272/8)

typedef struct {
    u8  length;                                              // In bytes, [0;SRVL_MPLS_OUT_ENCAP_RAW_MAX_BYTE_CNT]
    u8  data[VTSS_SRVL_MPLS_OUT_ENCAP_RAW_MAX_BYTE_CNT];     // Network order; [0] is first on the wire
} vtss_srvl_mpls_out_encap_raw_t;

vtss_rc vtss_srvl_mpls_out_encap_raw_set(vtss_state_t *vtss_state,
                                         const u32 idx,
                                         const vtss_srvl_mpls_out_encap_raw_t *const entry,
                                         vtss_es0_mpls_encap_len_t *length);

#endif   /* Raw MPLS encapsulation */

#if defined(VTSS_FEATURE_VOP)
/* OAM functions */
vtss_rc vtss_srvl_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_srvl_oam_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_VOP */

/* VCAP functions */
vtss_rc vtss_srvl_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_srvl_vcap_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_srvl_vcap_port_key_addr_set(vtss_state_t         *vtss_state,
                                         const vtss_port_no_t port_no,
                                         u8                   lookup,
                                         vtss_vcap_key_type_t key_new,
                                         vtss_vcap_key_type_t key_old,
                                         BOOL                 dmac_dip_new);
vtss_rc vtss_srvl_vcap_debug_print(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info);
vtss_rc vtss_srvl_debug_is0_all(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);
vtss_rc vtss_srvl_debug_is1_all(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);
vtss_rc vtss_srvl_debug_es0_all(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);
vtss_rc vtss_srvl_debug_range_checkers(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       const vtss_debug_info_t   *const info);
BOOL vtss_srvl_is1_oam_adv(vtss_state_t *vtss_state);

#if defined(VTSS_FEATURE_TIMESTAMP)
/* Timestamp functions */
vtss_rc vtss_srvl_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_srvl_ts_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_TIMESTAMP */

#endif /* VTSS_ARCH_OCELOT */
#endif /* _VTSS_SERVAL_CIL_H_ */
