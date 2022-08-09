// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_CIL_H_
#define _VTSS_FA_CIL_H_

/* Register space starts by 'CPU' area followed by 'SWC' area */
#if (VTSS_IO_ORIGIN2_OFFSET > VTSS_IO_ORIGIN1_OFFSET)
#define VTSS_IO_CPU VTSS_IO_ORIGIN1_OFFSET
#define VTSS_IO_SWC VTSS_IO_ORIGIN2_OFFSET
#else
#define VTSS_IO_CPU VTSS_IO_ORIGIN2_OFFSET
#define VTSS_IO_SWC VTSS_IO_ORIGIN1_OFFSET
#endif
#define VTSS_IOADDR(t,o) ((((t) - VTSS_IO_CPU) >> 2) + (o))
#define VTSS_IOREG(t,o)  (VTSS_IOADDR(t,o))

#include "vtss_api.h"

#if defined(VTSS_ARCH_SPARX5)
#define VTSS_ARCH_FA
#endif

#if defined(VTSS_ARCH_FA)

#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#include "../ail/vtss_state.h"
#include "../ail/vtss_common.h"
#include "../ail/vtss_util.h"
#include "../ail/vtss_sd10g28_procs.h"
#include "../ail/vtss_sd25g28_procs.h"

#if defined(VTSS_FEATURE_FDMA) && VTSS_OPT_FDMA
#include "vtss_fa_fdma.h"
#endif

#include "vtss_fa.h"
#include "vtss_fa_reg.h"
#include "vtss_fa_vcap.h"

// Port 0-64 are switch ports and 65-69 are internal ports
#define VTSS_CHIP_PORTS  65
#define VTSS_CHIP_PORT_CPU   VTSS_CHIP_PORTS  /* Next port is CPU port */
#define VTSS_CHIP_PORT_CPU_0 (VTSS_CHIP_PORT_CPU + 0) /* CPU Port 65 */
#define VTSS_CHIP_PORT_CPU_1 (VTSS_CHIP_PORT_CPU + 1) /* CPU Port 66 */
#define VTSS_CHIP_PORT_VD0   (VTSS_CHIP_PORT_CPU + 2) /* VD0/Port 67 used for IPMC */
#define VTSS_CHIP_PORT_VD1   (VTSS_CHIP_PORT_CPU + 3) /* VD1/Port 68 used for AFI/OAM */
#define VTSS_CHIP_PORT_VD2   (VTSS_CHIP_PORT_CPU + 4) /* VD2/Port 69 used for IPinIP*/
#define VTSS_CHIP_PORTS_ALL  (VTSS_CHIP_PORT_CPU + 5) /* Total number of ports */

#define VTSS_SERDES_10G_START 13
#define VTSS_SERDES_25G_START 25


// Fireant port devices:
// D0  - D11      DEV5G  (12)
// D12 - D15      DEV10G  (4)
// D16 - D47      DEV2G5 (32)
// D48 - D55      DEV10G  (8)
// D56 - D63      DEV25G  (8)
// D64            DEV5G   (1)
//                -----------
//                65 port devices + 33 DEV2G5 'shadow' devices

// Macros for primary ports:
#define VTSS_PORT_IS_2G5(port)   (port >= 16 && port <= 47)
#define VTSS_PORT_IS_5G(port)    (port <= 11 || port == 64)
#define VTSS_PORT_IS_10G(port)   ((port >= 12 && port <= 15) || (port >= 48 && port <= 55))
#define VTSS_PORT_IS_25G(port)   (port >= 56 && port <= 63)
#define VTSS_PORT_DEV_INDX(port) (VTSS_PORT_IS_2G5(port) ? port : VTSS_PORT_IS_5G(port) ? (port <= 11 ? port : 12) : \
                                  VTSS_PORT_IS_10G(port) ? ((port >= 12 && port <= 15) ? port - 12 : port - 44) : (port - 56))
// Macros for block address targets:
#define VTSS_TO_DEV2G5(port)   vtss_to_dev2g5(port)
#define VTSS_TO_DEV5G(port)    vtss_to_dev5g(port)
#define VTSS_TO_DEV10G(port)   vtss_to_dev10g(port)
#define VTSS_TO_DEV25G(port)   vtss_to_dev25g(port)
#define VTSS_TO_HIGH_DEV(port) VTSS_PORT_IS_5G(port) ? VTSS_TO_DEV5G(port) :  VTSS_PORT_IS_10G(port) ? VTSS_TO_DEV10G(port) : VTSS_TO_DEV25G(port)
#define VTSS_TO_PCS_TGT(port)  VTSS_PORT_IS_5G(port) ? vtss_to_pcs5g(port) :  VTSS_PORT_IS_10G(port) ? vtss_to_pcs10g(port) : vtss_to_pcs25g(port)
#define VTSS_TO_SD_CMU(indx)  vtss_to_sd_cmu(indx)
#define VTSS_TO_SD_CMU_CFG(indx)  vtss_to_sd_cmu_cfg(indx)
#define VTSS_TO_SD6G_LANE(indx) vtss_to_sd6g_lane(indx)
#define VTSS_TO_SD10G_LANE(indx) vtss_to_sd10g_lane(indx)
#define VTSS_TO_SD25G_LANE(indx) vtss_to_sd25g_lane(indx)
#define VTSS_TO_SD_LANE(indx) vtss_to_sd_lane(indx)


/* Fireant has 4 PTP PIN connected to GPIO that can be used for different purposes, the defines below defines the
 * default usage of the 4 pins.
 */
/* PIN configuration for external clock */
#define EXT_CLK_PIN 1               /* external clock 1 pps output */

/* PIN configuration for alternative clock */
#define ALT_LDST_PIN 2              /* alternative clock 1 pps input (Load/Store) */
#define ALT_PPS_PIN  3              /* alternative clock 1pps pulse */

/* The last PTP pin is not connected to GPIO but can be used for TOD access */
#define TOD_ACC_PIN 4               /* pin used for timeofday get/set */

#define FA_BUFFER_MEMORY    4194280 /* 22795 words * 184 bytes */
#define FA_BUFFER_REFERENCE 22795   /* Frame references */
#define FA_BUFFER_CELL_SZ   184     /* Cell size  */

#define FA_PRIOS 8 /* Number of priorities */

/* ================================================================= *
 *  Register access
 * ================================================================= */
// #define VTSS_OPT_EMUL // Emulation included for now.
extern vtss_rc vtss_fa_emul_rd(u32 addr, u32 *value);
extern vtss_rc vtss_fa_emul_wr(u32 addr, u32 value);
extern vtss_rc vtss_fa_emul_init(vtss_state_t *vtss_state);

extern vtss_rc (*vtss_fa_wr)(vtss_state_t *vtss_state, u32 addr, u32 value);
extern vtss_rc (*vtss_fa_rd)(vtss_state_t *vtss_state, u32 addr, u32 *value);
vtss_rc vtss_fa_wrm(vtss_state_t *vtss_state, u32 addr, u32 value, u32 mask);
vtss_rc vtss_fa_isdx_update(vtss_state_t *vtss_state, vtss_sdx_entry_t *sdx);
vtss_rc vtss_fa_sdx_counters_update(vtss_state_t *vtss_state, vtss_stat_idx_t *stat_idx, vtss_evc_counters_t *const cnt, BOOL clr);
BOOL vtss_fa_port_is_high_speed(vtss_state_t *vtss_state, u32 port);

#define REG_RD(p, value)                 \
    {                                     \
        vtss_rc __rc = vtss_fa_rd(vtss_state, p, value);    \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    }

#define REG_WR(p, value)                 \
    {                                     \
        vtss_rc __rc = vtss_fa_wr(vtss_state, p, value);    \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    }

#define REG_WRM(p, value, mask)                 \
    {                                            \
        vtss_rc __rc = vtss_fa_wrm(vtss_state, p, value, mask);        \
        if (__rc != VTSS_RC_OK)                  \
            return __rc;                         \
    }

#define REG_WRM_SET(p, mask) REG_WRM(p, mask, mask)
#define REG_WRM_CLR(p, mask) REG_WRM(p, 0,    mask)
#define REG_WRM_CTL(p, _cond_, mask) REG_WRM(p, (_cond_) ? mask : 0, mask)

#define DEV_RD(name, port, value)                                      \
    {                                                                  \
        if (vtss_fa_port_is_high_speed(vtss_state, port)) {            \
            REG_RD(VTSS_DEV10G_##name(VTSS_TO_HIGH_DEV(port)), value); \
        } else {                                                       \
            REG_RD(VTSS_DEV1G_##name(VTSS_TO_DEV2G5(port)), value);    \
        }                                                              \
    }

#define DEV_WR(name, port, value)                                      \
    {                                                                  \
        REG_WR(VTSS_DEV1G_##name(VTSS_TO_DEV2G5(port)), value);        \
        if (!VTSS_PORT_IS_2G5(port)) {                                 \
            REG_WR(VTSS_DEV10G_##name(VTSS_TO_HIGH_DEV(port)), value); \
        }                                                              \
    }

#define DEV_WRM(name, port, value, mask)                                      \
    {                                                                         \
        REG_WRM(VTSS_DEV1G_##name(VTSS_TO_DEV2G5(port)), value, mask);        \
        if (!VTSS_PORT_IS_2G5(port)) {                                        \
            REG_WRM(VTSS_DEV10G_##name(VTSS_TO_HIGH_DEV(port)), value, mask); \
        }                                                                     \
    }

/* Decode register bit field */
#define REG_BF(name, value) ((VTSS_M_##name & value) ? 1 : 0)

/* Poll bits in mask until all are zero */
#define REG_POLL_MASK(_p_, _mask_)                                                  \
    {                                                                               \
        u32 _x_, _cnt_ = 0;                                                         \
        do {                                                                        \
            REG_RD(_p_, &_x_);                                                      \
            VTSS_MSLEEP(1);                                                         \
            if (++_cnt_ == 100) {                                                   \
                VTSS_E("timeout, addr: %s, m: 0x%x, v: 0x%x", #_p_, (_mask_), _x_); \
                return VTSS_RC_ERROR;                                               \
            }                                                                       \
        } while (_x_ & (_mask_));                                                   \
    }

/* ================================================================= *
 *  Port masks
 * ================================================================= */

#define REG_WR_PMASK(_t, _m)          { REG_WR(_t, (_m).m[0]);                REG_WR(_t##1, (_m).m[1]);                REG_WR(_t##2, (_m).m[2]);                }
#define REG_WRX_PMASK(_t, x, _m)      { REG_WR(_t(x), (_m).m[0]);             REG_WR(_t##1(x), (_m).m[1]);             REG_WR(_t##2(x), (_m).m[2]);             }
#define REG_WRM_PMASK(_t, _v, _m)     { REG_WRM(_t, (_v).m[0], (_m).m[0]);    REG_WRM(_t##1, (_v).m[1], (_m).m[1]);    REG_WRM(_t##2, (_v).m[2], (_m).m[2]);    }
#define REG_RD_PMASK(_t, _m)          { REG_RD(_t, &(_m)->m[0]);              REG_RD(_t##1, &(_m)->m[1]);              REG_RD(_t##2, &(_m)->m[2]);              }
#define REG_RDX_PMASK(_t, x, _m)      { REG_RD(_t(x), &(_m)->m[0]);           REG_RD(_t##1(x), &(_m)->m[1]);           REG_RD(_t##2(x), &(_m)->m[2]);           }
#define REG_WRXM_PMASK(_t, x, _v, _m) { REG_WRM(_t(x), (_v).m[0], (_m).m[0]); REG_WRM(_t##1(x), (_v).m[1], (_m).m[1]); REG_WRM(_t##2(x), (_v).m[2], (_m).m[2]); }

void vtss_fa_debug_print_port_header(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr, const char *txt);
void vtss_fa_debug_print_pmask(const vtss_debug_printf_t pr, vtss_port_mask_t *pmask);
void vtss_fa_debug_reg_header(const vtss_debug_printf_t pr, const char *name);
void vtss_fa_debug_reg(vtss_state_t *vtss_state,
                       const vtss_debug_printf_t pr, u32 addr, const char *name);
void vtss_fa_debug_reg_inst(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name);
void vtss_fa_debug_sticky(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr, u32 addr, const char *name);
void vtss_fa_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                       vtss_chip_counter_t *c1, vtss_chip_counter_t *c2);

#define FA_DEBUG_REG(pr, tgt, addr)                vtss_fa_debug_reg(vtss_state, pr, VTSS_##tgt##_##addr, #addr)
#define FA_DEBUG_REG_NAME(pr, tgt, addr, name)     vtss_fa_debug_reg(vtss_state, pr, VTSS_##tgt##_##addr, name)
#define FA_DEBUG_REGX_NAME(pr, tgt, addr, x, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_##tgt##_##addr(x), x, name)

/* MC PGIDs */
#define PGID_BASE         65
#define PGID_UC_FLOOD     (PGID_BASE + 0)
#define PGID_MC_FLOOD     (PGID_BASE + 1)
#define PGID_IPV4_MC_DATA (PGID_BASE + 2)
#define PGID_IPV4_MC_CTRL (PGID_BASE + 3)
#define PGID_IPV6_MC_DATA (PGID_BASE + 4)
#define PGID_IPV6_MC_CTRL (PGID_BASE + 5)
#define PGID_DROP         (PGID_BASE + 6)
#define PGID_FLOOD        (PGID_BASE + 7)

/* Mirror probe usage */
#define FA_MIRROR_PROBE_RX   0 /* Ingress mirror probe */
#define FA_MIRROR_PROBE_TX   1 /* Egress mirror probe */
#define FA_MIRROR_PROBE_VLAN 2 /* VLAN mirror probe */

#define QFWD_FRAME_COPY_CFG_CPU_QU(qu)              (qu)
#define QFWD_FRAME_COPY_CFG_LRN_ALL                 8
#define QFWD_FRAME_COPY_CFG_MIRROR_PROBE(probe_idx) (probe_idx + 9)

/* sFlow H/W-related min/max */
#define FA_SFLOW_MIN_SAMPLE_RATE       1 /**< Minimum allowable sampling rate for sFlow */
#define FA_SFLOW_MAX_SAMPLE_RATE   32767 /**< Maximum allowable sampling rate for sFlow */

/* Bits used to control IFH.CL_RSLT from CLM/IS2 */
#define FA_IFH_CL_RSLT_ACL_HIT  0x0001 /* ACL hit flag */
#define FA_IFH_CL_RSLT_ACL_FLAG 0x0002 /* ACL discard flag */

/* IS2 key selection starting at index 70 */
#define FA_VCAP_IS2_KEY_SEL_IRLEG 0
#define FA_VCAP_IS2_KEY_SEL_ERLEG 1
#define FA_VCAP_IS2_KEY_SEL_VD0   2

/* Common functions */
vtss_rc vtss_fa_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

/* Port functions */
vtss_rc vtss_fa_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_port_debug_print(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_port_debug_qres(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, BOOL res_stat_cur);

/* port or index to address target */
u32 vtss_to_dev2g5(u32 port);
u32 vtss_to_dev5g(u32 port);
u32 vtss_to_dev10g(u32 port);
u32 vtss_to_dev25g(u32 port);
u32 vtss_to_sd6g_lane(u32 indx);
u32 vtss_to_sd10g_lane(u32 indx);
u32 vtss_to_sd25g_lane(u32 indx);
u32 vtss_to_sd_cmu(u32 indx);
u32 vtss_to_sd_cmu_cfg(u32 indx);
u32 vtss_to_sd_lane(u32 indx);
u32 vtss_fa_dev_tgt(vtss_state_t *vtss_state, vtss_port_no_t port_no);


/* Serdes functions */
#define FA_SERDES_TYPE_6G  6
#define FA_SERDES_TYPE_10G 10
#define FA_SERDES_TYPE_25G 25
vtss_rc vtss_fa_port2sd(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *sd_indx, u32 *sd_type);
u32 vtss_fa_sd_lane_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_fa_sd_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_serdes_mode_t mode);
vtss_rc vtss_fa_cmu_cfg(vtss_state_t *vtss_state, u32 cmu_id);
vtss_rc vtss_fa_sd25g_init(vtss_state_t *vtss_state, u32 sd_id);
u32 vtss_fa_sd10g28_get_cmu (vtss_state_t *vtss_state, vtss_sd10g28_cmu_t cmu_type, vtss_port_no_t port_no);
u32 vtss_fa_port2sd_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_fa_serdes_init(vtss_state_t *vtss_state);
vtss_rc  vtss_ant_sd10g28_cmu_reg_cfg(vtss_state_t *vtss_state, u32 cmu_num);
vtss_rc fa_debug_chip_serdes(vtss_state_t *vtss_state,  const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info, vtss_port_no_t port_no);
vtss_rc fa_debug_serdes_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                            const vtss_port_serdes_debug_t *const conf);

vtss_rc fa_kr_eye_height(vtss_state_t *vtss_state,  vtss_port_no_t port_no, u32 action, u32 *ret_val);
vtss_rc fa_serdes_ctle_adjust(vtss_state_t *vtss_state, const vtss_debug_printf_t pr,
                              u32 port_no, BOOL ro, u32 *vga, u32 *eqr, u32 *eqc);
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
vtss_rc fa_kr_coef2status(vtss_state_t *vtss_state,
                          const vtss_port_no_t port_no,
                          const u16 coef_in,
                          vtss_kr_status_results_t *const status_out);
vtss_rc fa_port_kr_tap_get(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                           u16 *tap_dly, u16 *tap_adv, u16 *ampl);
vtss_rc fa_port_kr_tap_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                           u16 tap_dly, u16 tap_adv, u16 ampl);

vtss_rc fa_serdes_40b_mode(vtss_state_t *vtss_state, u32 port_no);

vtss_rc fa_port_kr_tap_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                           u16 tap_dly, u16 tap_adv, u16 ampl);
#endif
    

/* Miscellaneous functions */
vtss_rc vtss_fa_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_misc_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id);
vtss_rc vtss_fa_gpio_mode(vtss_state_t *vtss_state,
                          const vtss_chip_no_t   chip_no,
                          const vtss_gpio_no_t   gpio_no,
                          const vtss_gpio_mode_t mode);
u32 vtss_fa_clk_period(vtss_core_clock_freq_t clock);
vtss_rc vtss_fa_dsm_cal_debug(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr);
vtss_rc vtss_fa_cell_cal_debug(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr);
u32 vtss_get_fifo_size(vtss_state_t *vtss_state, vtss_port_no_t port_no);


/* QoS functions */
#if defined(VTSS_FEATURE_QOS)
vtss_rc vtss_fa_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_port_policer_fc_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_fa_policer_conf_set(vtss_state_t *vtss_state, u32 lb_set_idx, vtss_dlb_policer_conf_t *conf);
u32 vtss_fa_imap_key2clm(u16 imap_key, BOOL inner_tag);
vtss_rc vtss_fa_qos_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_qos_port_change(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL is_reset);
vtss_rc vtss_fa_qos_tas_port_conf_update(struct vtss_state_s   *vtss_state,
                                         const vtss_port_no_t  port_no);
#endif /* VTSS_FEATURE_QOS */

/* L2 functions */
vtss_rc vtss_fa_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
u32 vtss_fa_vtss_pgid(const vtss_state_t *const state, u32 pgid);
vtss_rc vtss_fa_vlan_update(vtss_state_t *vtss_state, vtss_vid_t vid);
vtss_rc vtss_fa_l2_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);

/* L3 functions */
vtss_rc vtss_fa_l3_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_l3_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
/* Packet functions */
typedef struct {
    vtss_packet_reg_type_t reg;
    vtss_packet_rx_queue_t queue;
    BOOL                   cosid_enable;
    vtss_cosid_t           cosid;
} vtss_fa_l2cp_conf_t;

vtss_rc vtss_fa_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_packet_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_l2cp_conf_set(vtss_state_t *vtss_state, u32 profile, u32 l2cp, vtss_fa_l2cp_conf_t *conf);

#if defined(VTSS_FEATURE_AFI_SWC)
vtss_rc vtss_fa_afi_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
#if defined(VTSS_AFI_V2)
vtss_rc vtss_fa_afi_init(vtss_state_t *const vtss_state, const vtss_init_cmd_t cmd);
#endif /* VTSS_AFI_V2 */
#endif /* VTSS_FEATURE_AFI_SWC */

#if defined(VTSS_FEATURE_VOP)
/* OAM functions */
u32 vtss_fa_voi_idx_to_mip_idx(vtss_voi_idx_t  voi_idx);
vtss_rc vtss_fa_vop_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_vop_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_VOP */

/* VCAP functions */
#if defined(VTSS_FEATURE_VCAP)
vtss_rc vtss_fa_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_vcap_port_key_set(vtss_state_t *vtss_state, vtss_port_no_t port_no,
                                  u32 lookup, vtss_vcap_key_type_t key_type, BOOL dmac_dip);
vtss_rc vtss_fa_vcap_port_update(vtss_state_t *vtss_state,
                                 vtss_port_no_t port_no);
vtss_rc vtss_fa_vcap_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_clm_a(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_clm_b(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_clm_c(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_es0(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_lpm(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_VCAP */

#if defined(VTSS_FEATURE_TIMESTAMP)
/* Timestamp functions */
vtss_rc vtss_fa_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_ts_debug_print(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);
vtss_rc vtss_timestampSub(vtss_timestamp_t *ts, const vtss_timestamp_t *ts_sub);
vtss_rc vtss_timestampAddNano(vtss_timestamp_t *ts, u64 nano);
vtss_rc vtss_timestampSubNano(vtss_timestamp_t *ts, u64 nano);
BOOL vtss_timestampLarger(const vtss_timestamp_t *ts1, const vtss_timestamp_t *ts2);

#endif /* VTSS_FEATURE_TIMESTAMP */


#endif /* VTSS_ARCH_FA */
#endif /* _VTSS_FA_CIL_H_ */
