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
#if defined(VTSS_OPT_FPGA)
#if (VTSS_OPT_FPGA == 1)
#include "vtss_lan966x_regs_sr.h"
#else
#include "vtss_lan966x_regs_ad.h"
#endif
#else
#include "vtss_lan966x_regs.h"
#endif
#include "vtss_lan966x_ifh.h"

/* ================================================================= *
 *  Register access
 * ================================================================= */
extern vtss_rc (*vtss_lan966x_wr)(vtss_state_t *vtss_state, u32 addr, u32 val);
extern vtss_rc (*vtss_lan966x_rd)(vtss_state_t *vtss_state, u32 addr, u32 *val);
vtss_rc vtss_lan966x_wrm(vtss_state_t *vtss_state, u32 reg, u32 val, u32 mask);
void vtss_lan966x_reg_error(const char *file, int line);

static inline u32 vtss_lan966x_target_id_to_addr(int target_id)
{
    switch (target_id) {
    case TARGET_AFI:        return LAN966X_TARGET_AFI_OFFSET;
    case TARGET_ANA:        return LAN966X_TARGET_ANA_OFFSET;
    case (TARGET_DEV + 0):  return LAN966X_TARGET_DEV_0_OFFSET;
    case (TARGET_DEV + 1):  return LAN966X_TARGET_DEV_1_OFFSET;
    case (TARGET_DEV + 2):  return LAN966X_TARGET_DEV_2_OFFSET;
    case (TARGET_DEV + 3):  return LAN966X_TARGET_DEV_3_OFFSET;
    case (TARGET_DEV + 4):  return LAN966X_TARGET_DEV_4_OFFSET;
    case (TARGET_DEV + 5):  return LAN966X_TARGET_DEV_5_OFFSET;
    case (TARGET_DEV + 6):  return LAN966X_TARGET_DEV_6_OFFSET;
    case (TARGET_DEV + 7):  return LAN966X_TARGET_DEV_7_OFFSET;
    case TARGET_GCB:        return LAN966X_TARGET_GCB_OFFSET;
    case TARGET_MEP:        return LAN966X_TARGET_MEP_OFFSET;
    //case TARGET_ORG:        return LAN966X_TARGET_ORG_OFFSET;
    case TARGET_PTP:        return LAN966X_TARGET_PTP_OFFSET;
    case TARGET_QS:         return LAN966X_TARGET_QS_OFFSET;
    case TARGET_QSYS:       return LAN966X_TARGET_QSYS_OFFSET;
    case TARGET_REW:        return LAN966X_TARGET_REW_OFFSET;
    case TARGET_SYS:        return LAN966X_TARGET_SYS_OFFSET;
    case (TARGET_VCAP + 0): return LAN966X_TARGET_VCAP_0_OFFSET;
    case (TARGET_VCAP + 1): return LAN966X_TARGET_VCAP_1_OFFSET;
    case (TARGET_VCAP + 2): return LAN966X_TARGET_VCAP_2_OFFSET;
#if !defined(VTSS_OPT_FPGA)
    case TARGET_CHIP_TOP:   return LAN966X_TARGET_CHIP_TOP_OFFSET;
    case TARGET_HSIO:       return LAN966X_TARGET_HSIO_OFFSET;
#endif
#if defined(LAN966X_TARGET_CPU_OFFSET)
    case TARGET_CPU:        return LAN966X_TARGET_CPU_OFFSET;
#endif
    default: return 0xffffffff;
    }
}
static inline u32 __ioreg(const char *file, int line,
                          int tbaseid, int tinst, int tcnt,
                          int gbase, int ginst, int gcnt, int gwidth,
                          int raddr, int rinst, int rcnt, int rwidth)
{
    u32 addr = vtss_lan966x_target_id_to_addr(tbaseid + tinst);
    if (addr == 0xffffffff || tinst >= tcnt ||
        ginst >= gcnt || rinst >= rcnt) {
        vtss_lan966x_reg_error(file, line);
        return 0xffffffff;
    }

    return (addr +
            gbase + ((ginst) * gwidth) +
            raddr + ((rinst) * rwidth)) / 4;
}

#define IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,                \
              raddr, rinst, rcnt, rwidth)                                      \
        __ioreg(__FILE__, __LINE__, tbaseid, tinst, tcnt, gbase, ginst, gcnt,  \
                gwidth, raddr, rinst, rcnt, rwidth)

#define REG_ADDR(p) IOREG(p)

#define REG_RD(...) REG_RD_(__VA_ARGS__)
#define REG_RD_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,              \
               raddr, rinst, rcnt, rwidth, val)                                \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_rd(vtss_state, o, val);                    \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WR(...) REG_WR_(__VA_ARGS__)
#define REG_WR_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,              \
               raddr, rinst, rcnt, rwidth, val)                                \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wr(vtss_state, o, val);                    \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WRM(...) REG_WRM_(__VA_ARGS__)
#define REG_WRM_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,             \
                raddr, rinst, rcnt, rwidth, val, msk)                          \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, o, val, msk);              \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WRM_SET(...) REG_WRM_SET_(__VA_ARGS__)
#define REG_WRM_SET_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,         \
                    raddr, rinst, rcnt, rwidth, msk)                           \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, o, msk, msk);              \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WRM_CLR(...) REG_WRM_CLR_(__VA_ARGS__)
#define REG_WRM_CLR_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,         \
                    raddr, rinst, rcnt, rwidth, msk)                           \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, o, 0, msk);                \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WRM_CTL(...) REG_WRM_CTL_(__VA_ARGS__)
#define REG_WRM_CTL_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,         \
                    raddr, rinst, rcnt, rwidth, _cond_, msk)                   \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, o,                         \
                                        (_cond_) ? (msk) : 0, msk);            \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

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

#if defined(VTSS_ARCH_LAN966X_FPGA)
#define LAN966X_BUFFER_MEMORY    (32*1024)
#define LAN966X_BUFFER_REFERENCE 255
#else
#define LAN966X_BUFFER_MEMORY    (160*1024)
#define LAN966X_BUFFER_REFERENCE 1280
#endif
#define LAN966X_BUFFER_CELL_SZ   64

// Policers
#define LAN966X_POLICER_PORT  0   // 0-8   : Port policers (9)
#define LAN966X_POLICER_QUEUE 9   // 9-80  : Queue policers (72)
#define LAN966X_POLICER_ACL   81  // 81-96 : ACL policers (16)
#define LAN966X_POLICER_DLB   97  // 97-343: DLB policers (247)
#define LAN966X_POLICER_DISC  344 // 255   : Discard policer
#define LAN966X_POLICER_CNT   345 // Total number of policers

#define LAN966X_PRIOS        8   /* Number of priorities */

/* LAN966X has 4 PTP PIN connected to GPIO that can be used for different purposes, the defines below defines the
 * default usage of the 4 pins.
 */
/* PIN configuration for external clock */
#define EXT_CLK_PIN 3               /* external clock 1 pps output */

/* PIN configuration for alternative clock */
#define ALT_LDST_PIN 2              /* alternative clock 1 pps input (Load/Store) */
#define ALT_PPS_PIN  3              /* alternative clock 1pps pulse */

/* The last PTP pin is not connected to GPIO but can be used for TOD access */
#define TOD_ACC_PIN 7               /* pin used for timeofday get/set */

/* ================================================================= *
 *  Common functions
 * ================================================================= */
vtss_rc vtss_lan966x_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
u32 vtss_lan966x_clk_period_ps(vtss_state_t *vtss_state);
u32 vtss_lan966x_port_mask(vtss_state_t *vtss_state, const BOOL member[]);
vtss_rc vtss_lan966x_counter_update(vtss_state_t *vtss_state,
                                    u32 *addr, vtss_chip_counter_t *counter, BOOL clear);
#if VTSS_OPT_DEBUG_PRINT
void vtss_lan966x_debug_print_port_header(vtss_state_t *vtss_state,
                                          const vtss_debug_printf_t pr, const char *txt);
void vtss_lan966x_debug_print_mask(const vtss_debug_printf_t pr, u32 mask);
void vtss_lan966x_debug_reg_header(const vtss_debug_printf_t pr, const char *name) ;
void vtss_lan966x_debug_reg(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr, u32 addr, const char *name);
void vtss_lan966x_debug_reg_inst(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name);
void vtss_lan966x_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                            vtss_chip_counter_t *c1, vtss_chip_counter_t *c2);
#endif

// Port API
vtss_rc vtss_lan966x_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_port_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info);
#endif
vtss_rc vtss_lan966x_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_lan966x_wm_update(vtss_state_t *vtss_state);
u32 vtss_lan966x_wm_high_get(vtss_state_t *vtss_state, u32 queue);

// Packet API
vtss_rc vtss_lan966x_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_packet_debug_print(vtss_state_t *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const vtss_debug_info_t   *const info);
#endif

// AFI API
vtss_rc vtss_lan966x_afi_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_afi_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info);
#endif

// MISC API
vtss_rc vtss_lan966x_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_misc_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info);
#endif
vtss_rc vtss_lan966x_gpio_mode(vtss_state_t *vtss_state,
                               const vtss_chip_no_t   chip_no,
                               const vtss_gpio_no_t   gpio_no,
                               const vtss_gpio_mode_t mode);

// L2 API
vtss_rc vtss_lan966x_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if defined(VTSS_FEATURE_VCAP)
void vtss_lan966x_is1_action_update(vtss_state_t *vtss_state, vtss_sdx_entry_t *sdx, vtss_is1_action_t *action);
#endif
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_l2_debug_print(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info);
#endif

#if defined(VTSS_FEATURE_QOS)
// QoS API
vtss_rc vtss_lan966x_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_qos_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info);
#endif
vtss_rc vtss_lan966x_qos_tas_port_conf_update(struct vtss_state_s   *vtss_state,
                                              const vtss_port_no_t  port_no);
vtss_rc vtss_lan966x_qos_port_change(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL is_reset);
vtss_rc vtss_lan966x_qos_policer_conf_set(vtss_state_t *vtss_state, u32 policer, vtss_policer_conf_t *conf);
#endif

// TS API
vtss_rc vtss_lan966x_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_ts_debug_print(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info);
#endif

// VCAP API
vtss_rc vtss_lan966x_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_lan966x_vcap_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_lan966x_vcap_port_key_addr_set(vtss_state_t         *vtss_state,
                                            const vtss_port_no_t port_no,
                                            u8                   lookup,
                                            vtss_vcap_key_type_t key_new,
                                            vtss_vcap_key_type_t key_old,
                                            BOOL                 dmac_dip_new);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_vcap_debug_print(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr,
                                      const vtss_debug_info_t   *const info);
vtss_rc vtss_lan966x_debug_range_checkers(vtss_state_t *vtss_state,
                                          const vtss_debug_printf_t pr,
                                          const vtss_debug_info_t   *const info);
vtss_rc vtss_lan966x_debug_is1(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info);
vtss_rc vtss_lan966x_debug_es0(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info);
#endif

// OAM API
vtss_rc vtss_lan966x_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_oam_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info);
#endif

// MRP API
vtss_rc vtss_lan966x_mrp_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_lan966x_mrp_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info);
#endif

#endif /* VTSS_ARCH_LAN966X */
#endif /* _VTSS_MAS_CIL_H_ */
