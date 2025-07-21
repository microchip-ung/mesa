// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef VTSS_STATE_H
#define VTSS_STATE_H

#include <vtss_api.h>

#if defined(VTSS_FEATURE_MPLS)
#include "vtss_mpls_common.h"
#endif
#if defined(VTSS_ARCH_OCELOT)
#include "../ocelot/vtss_ocelot.h"
#endif

/* Bit field macros */
#define VTSS_BF_SIZE(n)   (((n) + 7U) / 8U)
#define VTSS_BF_GET(a, n) (((a[(n) / 8U] & ((u32)1U << ((n) % 8U))) != 0U) ? TRUE : FALSE)

#define VTSS_BF_SET(a, n, v)                                                                       \
    do {                                                                                           \
        if (v) {                                                                                   \
            a[(n) / 8U] |= (1U << ((n) % 8U));                                                     \
        } else {                                                                                   \
            u8 mask = (1U << ((n) % 8U));                                                          \
            a[(n) / 8U] &= ~mask;                                                                  \
        }                                                                                          \
    } while (0 == 1)
#define VTSS_BF_CLR(a, n) (VTSS_MEMSET(a, 0, VTSS_BF_SIZE(n)))

/* Port member bit field macros */
#define VTSS_PORT_BF_SIZE            VTSS_BF_SIZE(VTSS_PORTS)
#define VTSS_PORT_BF_GET(a, port_no) VTSS_BF_GET(a, ((u8)port_no) - VTSS_PORT_NO_START)
#define VTSS_PORT_BF_SET(a, port_no, v)                                                            \
    {                                                                                              \
        u8 port = (u8)(port_no) - VTSS_PORT_NO_START;                                              \
        VTSS_BF_SET(a, port, v);                                                                   \
    }
#define VTSS_PORT_BF_CLR(a) VTSS_BF_CLR(a, VTSS_PORTS)

#if defined(VTSS_FEATURE_MISC)
#include "vtss_misc_state.h"
#endif

#if defined(VTSS_FEATURE_PORT_CONTROL)
#include "vtss_port_state.h"
#endif

#if defined(VTSS_FEATURE_QOS)
#include "vtss_qos_state.h"
#endif

#if defined(VTSS_ARCH_LAIKA)
#include "vtss_lk_packet_state.h"
#endif

#if defined(VTSS_FEATURE_HQOS)
#include "vtss_hqos_state.h"
#endif

#if defined(VTSS_FEATURE_PACKET)
#include "vtss_packet_state.h"
#endif

#if defined(VTSS_FEATURE_AFI_SWC)
#include "vtss_afi_state.h"
#endif

#if defined(VTSS_FEATURE_LAYER2)
#include "vtss_l2_state.h"
#endif

#if defined(VTSS_FEATURE_LAYER3)
#include "vtss_l3_state.h"
#endif

#if defined(VTSS_FEATURE_VCAP)
#include "vtss_vcap_state.h"
#endif

#if defined(VTSS_FEATURE_VOP)
#include "vtss_vop_state.h"
#endif

#if defined(VTSS_FEATURE_MRP)
#include "vtss_mrp_state.h"
#endif

#if defined(VTSS_FEATURE_TIMESTAMP)
#include "vtss_ts_state.h"
#endif

#if defined(VTSS_FEATURE_CLOCK)
#include "vtss_clock_state.h"
#endif

extern const char *vtss_func;

/* Call function in cold start mode only */
#define VTSS_RC_COLD(expr) (vtss_state->warm_start_cur ? VTSS_RC_OK : (expr))

/* Set currently selected device */
#define VTSS_SELECT_CHIP(__chip_no__)                                                              \
    {                                                                                              \
        vtss_state->chip_no = (__chip_no__);                                                       \
    }
#define VTSS_SELECT_CHIP_PORT_NO(port_no) VTSS_SELECT_CHIP(vtss_state->port.map[port_no].chip_no)
/* API enter/exit macros for protection */
#define VTSS_ENTER(...)                                                                            \
    {                                                                                              \
        vtss_api_lock_t _lock;                                                                     \
        _lock.inst = inst;                                                                         \
        _lock.function = __FUNCTION__;                                                             \
        _lock.file = __FILE__;                                                                     \
        _lock.line = __LINE__;                                                                     \
        vtss_callout_lock(&_lock);                                                                 \
        vtss_func = __FUNCTION__;                                                                  \
    }
#define VTSS_EXIT(...)                                                                             \
    {                                                                                              \
        vtss_api_lock_t _lock;                                                                     \
        _lock.inst = inst;                                                                         \
        _lock.function = __FUNCTION__;                                                             \
        _lock.file = __FILE__;                                                                     \
        _lock.line = __LINE__;                                                                     \
        vtss_func = NULL;                                                                          \
        vtss_callout_unlock(&_lock);                                                               \
    }
#define VTSS_EXIT_ENTER(...)                                                                       \
    {                                                                                              \
        vtss_state_t   *old_state = vtss_state;                                                    \
        vtss_chip_no_t  old_chip = vtss_state->chip_no;                                            \
        vtss_api_lock_t _lock;                                                                     \
        _lock.function = __FUNCTION__;                                                             \
        _lock.file = __FILE__;                                                                     \
        _lock.line = __LINE__;                                                                     \
        vtss_callout_unlock(&_lock);                                                               \
        vtss_callout_lock(&_lock);                                                                 \
        vtss_state = old_state;                                                                    \
        vtss_state->chip_no = old_chip;                                                            \
    }

#define VTSS_RC(expr)                                                                              \
    {                                                                                              \
        vtss_rc __rc__ = (expr);                                                                   \
        if (__rc__ < VTSS_RC_OK) {                                                                 \
            return __rc__;                                                                         \
        }                                                                                          \
    }

#define VTSS_FMT(fmt_buf, fmt_str, ...)                                                            \
    do {                                                                                           \
        lmu_fmt_buf_init(&(fmt_buf));                                                              \
        LMU_PP_VA_ARGS_OVERLOAD_ONE_OR_MORE(LMU_SS_FMT, ##__VA_ARGS__)                             \
        (&(fmt_buf).ss, (fmt_str), ##__VA_ARGS__);                                                 \
    } while (0 == 1)

// Debug print
#define pr(fmt_str, ...)                                                                           \
    LMU_PP_VA_ARGS_OVERLOAD_ONE_OR_MORE(LMU_SS_FMT, ##__VA_ARGS__)                                 \
    ((ss), (fmt_str), ##__VA_ARGS__)

#define VTSS_BOOL(expr) (((expr) != 0) ? TRUE : FALSE)

#define VTSS_CHIP_PORT(port_no)                   (uint32_t)vtss_state->port.map[port_no].chip_port
#define VTSS_CHIP_NO(port_no)                     vtss_state->port.map[port_no].chip_no
#define VTSS_CHIP_PORT_FROM_STATE(state, port_no) (uint32_t)(state)->port.map[port_no].chip_port
#define VTSS_CHIP_NO_FROM_STATE(state, port_no)   (state)->port.map[port_no].chip_no
#define VTSS_PORT_CHIP_SELECTED(port_no)                                                           \
    (vtss_state->port.map[port_no].chip_no == vtss_state->chip_no)

/* Get array size */
#define VTSS_ARRSZ(t)          /*lint -e{574} */                                                   \
    (sizeof(t) / sizeof(t[0])) /* Suppress Lint Warning 574: Signed-unsigned                       \
                                  mix with relational */

/* Target architecture */
typedef enum {
    VTSS_ARCH_L26,      /* Luton26 */
    VTSS_ARCH_SRVL,     /* Serval */
    VTSS_ARCH_JR1,      /* Jaguar-1 */
    VTSS_ARCH_JR2,      /* Jaguar-2 */
    VTSS_ARCH_ANT,      /* FA */
    VTSS_ARCH_LAN_966X, /* LAN966X */
} vtss_arch_t;

/* Warm start scratch-pad 32-bit register layout */
#define VTSS_RESTART_VERSION_OFFSET 0U
#define VTSS_RESTART_VERSION_WIDTH  16U
#define VTSS_RESTART_TYPE_OFFSET    16U
#define VTSS_RESTART_TYPE_WIDTH     3U

/* API version used to determine if warm start can be done while
 * downgrading/upgrading */
#define VTSS_API_VERSION 1

/* Ethernet types */
#define VTSS_ETYPE_TAG_C 0x8100U
#define VTSS_ETYPE_TAG_S 0x88a8U

#if defined(VTSS_FEATURE_EEE)
#define VTSS_EEE_TIMER_TABLE_CNT 128

/* CIL function pointers */
vtss_rc vtss_cil_eee_port_conf_set(struct vtss_state_s              *vtss_state,
                                   const vtss_port_no_t              port_no,
                                   const vtss_eee_port_conf_t *const eee_conf);
typedef struct {
    /* Configuration/state */
    BOOL ena[VTSS_PORT_ARRAY_SIZE];     // Signaling current state in the switch api
    BOOL ena_phy[VTSS_PORT_ARRAY_SIZE]; // Signaling current state in the phy api
    u32  timer_table[VTSS_EEE_TIMER_TABLE_CNT];
    BOOL timer_table_initialized;
} vtss_eee_state_t;
#endif /* VTSS_FEATURE_EEE */

#if defined(VTSS_FEATURE_FAN)
/* CIL function pointers */
vtss_rc vtss_cil_fan_controller_init(struct vtss_state_s         *vtss_state,
                                     const vtss_fan_conf_t *const spec);
vtss_rc vtss_cil_fan_cool_lvl_set(struct vtss_state_s *vtss_state, u8 lvl);
vtss_rc vtss_cil_fan_cool_lvl_get(struct vtss_state_s *vtss_state, u8 *lvl);
vtss_rc vtss_cil_fan_rotation_get(struct vtss_state_s *vtss_state,
                                  vtss_fan_conf_t     *fan_spec,
                                  u32                 *rotation_count);
typedef struct {
    /* Configuration/state */
    u16             rotation_count; // Fan rotations count
    vtss_fan_conf_t conf;           // Fan configuration/specifications.
    u8              lvl;            // Fan speed level
} vtss_fan_state_t;
#endif /* VTSS_FEATURE_FAN */

#if defined(VTSS_FEATURE_TEMP_SENSOR)
/* CIL function pointers */
vtss_rc vtss_cil_chip_temp_get(struct vtss_state_s *vtss_state, i16 *chip_temp);
vtss_rc vtss_cil_chip_temp_init(struct vtss_state_s *vtss_state, const BOOL enable);

typedef struct {
    i16 chip_temp; // Chip temperature
} vtss_temp_sensor_state_t;
#endif /* VTSS_FEATURE_TEMP_SENSOR */

#if defined(VTSS_FEATURE_SYNCE)
typedef struct {
    /* Configuration/state */
    u32                            old_port_no[VTSS_SYNCE_CLK_PORT_ARRAY_SIZE];
    vtss_synce_clock_in_t          in_conf[VTSS_SYNCE_CLK_PORT_ARRAY_SIZE];
    vtss_synce_clock_out_t         out_conf[VTSS_SYNCE_CLK_PORT_ARRAY_SIZE];
    vtss_synce_station_clock_out_t station_clk_out_conf[VTSS_SYNCE_CLK_PORT_ARRAY_SIZE];
} vtss_synce_state_t;
#endif /* VTSS_FEATURE_SYNCE */

#if defined(VTSS_ARCH_FA)
typedef enum {
    FEATURE_VLAN_COUNTERS,        // VLAN counters are only supported for SMB devices
    FEATURE_QOS_FRAME_PREEMPTION, // Frame Preemption support (802.1Qbu and
                                  // 802.3br)
    FEATURE_SYNCE,                // SYNCE - L1 syncronization feature
    FEATURE_FRER,                 // IEEE 802.1CB: Frame Replication and Elimination for
                                  // Reliability
    FEATURE_PSFP,                 // IEEE 802.1Qci: Per-Stream Filtering and Policing
    FEATURE_REDBOX,               // PRP/HSR RedBox
    FEATURE_QOS_OT,               // Operational Technology traffic handling
    FEATURE_MRP,                  // IEC 62439-2 MRP
    FEATURE_MRP_V1,               // Version 1 MRP implementation
    FEATURE_MAC_INDEX_TABLE,      // Index-based MAC address table
    FEATURE_TIMESTAMP,            // 1588 timestamp feature for PTP
    FEATURE_LAST
} vtss_feature_t;
#endif

/* Opaque forward declaration */
struct vtss_state_s;

/* ================================================================= *
 *  Chip Interface Layer functions
 * ================================================================= */

vtss_rc vtss_cil_register_access_mode_set(struct vtss_state_s *vtss_state);

/* ================================================================= *
 *  Total API state
 * ================================================================= */

/* State cookie */
#define VTSS_STATE_COOKIE 0x53727910

/* State structure */
typedef struct vtss_state_s {
    /* Initialization */
    u32                cookie;
    vtss_arch_t        arch; /* Architecture */
    vtss_inst_create_t create;
    vtss_init_conf_t   init_conf;
    BOOL               restart_updated; /* Restart has been detected */
    BOOL               warm_start_cur;  /* Current warm start status */
    BOOL               warm_start_prev; /* Previous warm start status */
#if defined(VTSS_FEATURE_WARM_START)
    vtss_restart_t restart_cur;  /* Current restart configuration */
    vtss_restart_t restart_prev; /* Previous restart configuration */
    vtss_version_t version_cur;  /* Current version */
    vtss_version_t version_prev; /* Previous version */
#endif                           /* VTSS_FEATURE_WARM_START */
    BOOL sync_calling_private;   /* Used by PHY APIs */

    u32            chip_count; /* Number of devices */
    vtss_chip_no_t chip_no;    /* Currently selected device */
    u32            port_count;
    BOOL           create_pre; // AIL create preprocessing

#if defined(VTSS_FEATURE_MISC)
    vtss_misc_state_t misc;
#endif /* VTSS_FEATURE_MISC */

#if defined(VTSS_FEATURE_PORT_CONTROL)
    vtss_port_state_t port;
#endif /* VTSS_FEATURE_PORT_CONTROL */

#if defined(VTSS_FEATURE_QOS)
    vtss_qos_state_t qos;
#endif /* VTSS_FEATURE_QOS */

#if defined(VTSS_FEATURE_HQOS)
    vtss_hqos_state_t hqos;
#endif /* VTSS_FEATURE_HQOS */

#if defined(VTSS_FEATURE_PACKET)
    vtss_packet_state_t packet;
#endif /* VTSS_FEATURE_PACKET */

#if defined(VTSS_FEATURE_LAYER2)
    vtss_l2_state_t l2;
#endif /* VTSS_FEATURE_LAYER2 */

#if defined(VTSS_FEATURE_LAYER3)
    vtss_l3_state_t l3;
#endif /* VTSS_FEATURE_LAYER3 */

#if defined(VTSS_FEATURE_VCAP)
    vtss_vcap_state_t vcap;
#endif /* VTSS_FEATURE_VCAP */

#if defined(VTSS_FEATURE_TIMESTAMP)
    vtss_ts_state_t ts;
#endif /* VTSS_FEATURE_TIMESTAMP */

#if defined(VTSS_FEATURE_CLOCK)
    vtss_clock_state_t clock;
#endif /* VTSS_FEATURE_CLOCK */

#if defined(VTSS_FEATURE_VOP)
    vtss_oam_state_t oam;
#endif /* VTSS_FEATURE_VOP */

#if defined(VTSS_FEATURE_MRP)
    vtss_mrp_state_t mrp;
#endif /* VTSS_FEATURE_MRP */

#if defined(VTSS_FEATURE_SYNCE)
    vtss_synce_state_t synce;
#endif /* VTSS_FEATURE_SYNCE */

#if defined(VTSS_FEATURE_FAN)
    vtss_fan_state_t fan;
#endif /* VTSS_FEATURE_FAN */

#if defined(VTSS_FEATURE_TEMP_SENSOR)
    vtss_temp_sensor_state_t temp_sensor;
#endif /* VTSS_FEATURE_TEMP_SENSOR */

#if defined(VTSS_FEATURE_EEE)
    vtss_eee_state_t eee;
#endif /* VTSS_FEATURE_EEE */

#if defined(VTSS_FEATURE_AFI_SWC)
    vtss_afi_state_t afi;
#endif /* VTSS_FEATURE_AFI_SWC */

    struct {
        u8   vcore_cfg;      /* If supported by target */
        BOOL using_vcoreiii; /* If supported by target */
        BOOL using_vrap;     /* If supported by target */
        BOOL using_pcie;     /* If supported by target */
    } sys_config;

    BOOL system_reseting; // Signaling if system is rebooting.

    char  txt_buf[256];  /* General purpose text string buffer */
    int   txt_buf_index; /* Index to text buffer */
    void *app_data;      /**< Application data pointer */

#if defined(VTSS_ARCH_FA)
    BOOL vtss_features[FEATURE_LAST];
    u32 *reg_group_offset;
    u32 *reg_group_sz_offset;
    u32 *reg_target_offset;
    u32 *reg_unstable_addr;
    u32 *reg_unstable_flds;
    u32 *reg_group_cnt;
    u32 *reg_cnt;
    u32 *chip_const;

#if defined(VTSS_FEATURE_REDBOX)
    // This should have been sized by FA_DSM_CAL_MAX_DEVS_PER_TAXI, but that's
    // not available, so using the RedBox count, which is the same.
    u32 taxi_delay[VTSS_REDBOX_CNT];
#endif
#endif
} vtss_state_t;

// For checking state size at compile time
#if 0
char (*_check_vtss_state)[sizeof(vtss_state_t)] = 1;
char (*_check_port_state)[sizeof(vtss_port_state_t)] = 1;
char (*_check_port_counter_state)[(VTSS_PORTS + 1)*sizeof(vtss_port_chip_counters_t)] = 1;
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
char (*_check_port_kr_train_state)[VTSS_PORTS*sizeof(vtss_port_kr_state_t)] = 1;
#endif
char (*_check_l2_state)[sizeof(vtss_l2_state_t)] = 1;
char (*_check_l2_vlan_state)[VTSS_VIDS*sizeof(vtss_vlan_entry_t)] = 1;
char (*_check_l2_mac_state)[VTSS_MAC_ADDRS*sizeof(vtss_mac_entry_t)] = 1;
char (*_check_l2_pgid_state)[VTSS_PGIDS*sizeof(vtss_pgid_entry_t)] = 1;
char (*_check_l2_psfp_state)[sizeof(vtss_psfp_state_t)] = 1;
char (*_check_l2_mstream_state)[VTSS_MSTREAM_CNT*sizeof(vtss_frer_stream_conf_t)] = 1;
char (*_check_l2_cstream_state)[VTSS_CSTREAM_CNT*sizeof(vtss_frer_stream_conf_t)] = 1;
char (*_check_l2_mstream_cnt_state)[VTSS_MSTREAM_CNT*sizeof(vtss_frer_chip_counters_t)] = 1;
char (*_check_l2_cstream_cnt_state)[VTSS_CSTREAM_CNT*sizeof(vtss_frer_chip_counters_t)] = 1;
char (*_check_l2_sdx)[sizeof(vtss_sdx_info_t)] = 1;
char (*_check_l3_state)[sizeof(vtss_l3_state_t)] = 1;
char (*_check_dlb_conf_state)[VTSS_EVC_POL_CNT*sizeof(vtss_dlb_policer_conf_t)] = 1;
char (*_check_qos_state)[sizeof(vtss_qos_state_t)] = 1;
char (*_check_qos_port_state)[VTSS_PORTS*sizeof(vtss_qos_port_conf_t)] = 1;
#if defined(VTSS_FEATURE_QOS_HSCH_LEAK_LISTS)
char (*_check_qos_leak_state)[sizeof(vtss_qos_leak_conf_t)] = 1;
#endif
char (*_check_vcap_state)[sizeof(vtss_vcap_state_t)] = 1;
#if defined(VTSS_FEATURE_IS1)
char (*_check_vcap_is1)[sizeof(vtss_is1_info_t)] = 1;
#endif
char (*_check_vcap_es0)[sizeof(vtss_es0_info_t)] = 1;
char (*_check_misc_state)[sizeof(vtss_misc_state_t)] = 1;
char (*_check_packet_state)[sizeof(vtss_packet_state_t)] = 1;
char (*_check_ts_state)[sizeof(vtss_ts_state_t)] = 1;
#endif

/* Check instance */
vtss_rc       vtss_inst_check(const vtss_inst_t inst, vtss_state_t **vtss_state);
vtss_rc       vtss_inst_check_get(const vtss_inst_t inst, vtss_state_t **vtss_state);
vtss_state_t *vtss_inst_check_no_persist(const vtss_inst_t inst);

/* Check instance and port number */
vtss_rc vtss_inst_port_no_check(const vtss_inst_t    inst,
                                vtss_state_t       **vtss_state,
                                const vtss_port_no_t port_no);

vtss_rc vtss_inst_port_no_none_check(const vtss_inst_t    inst,
                                     vtss_state_t       **vtss_state,
                                     const vtss_port_no_t port_no);

vtss_rc vtss_inst_chip_no_check(const vtss_inst_t    inst,
                                vtss_state_t       **vtss_state,
                                const vtss_chip_no_t chip_no);

extern const char *vtss_port_if_txt(vtss_port_interface_t if_type);
extern const char *vtss_port_spd_txt(vtss_port_speed_t speed);

#if defined(VTSS_FEATURE_PORT_CONTROL)
extern const char *vtss_serdes_if_txt(vtss_serdes_mode_t serdes);
extern const char *vtss_media_type_if_txt(vtss_sd10g_media_type_t mt);
#endif

#if defined(VTSS_FEATURE_PORT_CPU_MASQUERADING)
extern const char *vtss_cpu_masquerade_txt(vtss_cpu_masquerade_t cpu);
#endif

extern vtss_inst_t vtss_default_inst;

typedef enum {
    VTSS_INIT_CMD_CREATE,   /* Called via vtss_inst_create() */
    VTSS_INIT_CMD_INIT,     /* Called via vtss_init_conf_set() */
    VTSS_INIT_CMD_PORT_MAP, /* Called via vtss_port_map_set() */
    VTSS_INIT_CMD_POLL      /* Called via vtss_poll_1sec() */
} vtss_init_cmd_t;

/* ================================================================= *
 *  Trace
 * ================================================================= */

/*lint -esym(459, vtss_trace_conf) */
extern vtss_trace_conf_t vtss_trace_conf[];

/* Default trace layer */
#ifndef VTSS_TRACE_LAYER
#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_AIL
#endif /* VTSS_TRACE_LAYER */

/* Default trace group */
#ifndef VTSS_TRACE_GROUP
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_DEFAULT
#endif /* VTSS_TRACE_GROUP */

#define VTSS_TRACE_TYPES                                                                           \
    VTSS_TRACE_TYPE_X(uint64_t, lmu_fmt_u64, vtss_trace_single_u64, vtss_trace_first_u64,          \
                      vtss_trace_last_u64)                                                         \
    VTSS_TRACE_TYPE_X(uint32_t, lmu_fmt_u32, vtss_trace_single_u32, vtss_trace_first_u32,          \
                      vtss_trace_last_u32)                                                         \
    VTSS_TRACE_TYPE_X(uint16_t, lmu_fmt_u16, vtss_trace_single_u16, vtss_trace_first_u16,          \
                      vtss_trace_last_u16)                                                         \
    VTSS_TRACE_TYPE_X(uint8_t, lmu_fmt_u8, vtss_trace_single_u8, vtss_trace_first_u8,              \
                      vtss_trace_last_u8)                                                          \
    VTSS_TRACE_TYPE_X(int64_t, lmu_fmt_i64, vtss_trace_single_i64, vtss_trace_first_i64,           \
                      vtss_trace_last_i64)                                                         \
    VTSS_TRACE_TYPE_X(int32_t, lmu_fmt_i32, vtss_trace_single_i32, vtss_trace_first_i32,           \
                      vtss_trace_last_i32)                                                         \
    VTSS_TRACE_TYPE_X(int16_t, lmu_fmt_i16, vtss_trace_single_i16, vtss_trace_first_i16,           \
                      vtss_trace_last_i16)                                                         \
    VTSS_TRACE_TYPE_X(int8_t, lmu_fmt_i8, vtss_trace_single_i8, vtss_trace_first_i8,               \
                      vtss_trace_last_i8)                                                          \
    VTSS_TRACE_TYPE_X(char, lmu_fmt_char, vtss_trace_single_char, vtss_trace_first_char,           \
                      vtss_trace_last_char)                                                        \
    VTSS_TRACE_TYPE_X(char *, lmu_fmt_czstr, vtss_trace_single_czstr, vtss_trace_first_czstr,      \
                      vtss_trace_last_czstr)                                                       \
    VTSS_TRACE_TYPE_X(lmu_str_t *, lmu_fmt_str, vtss_trace_single_str, vtss_trace_first_str,       \
                      vtss_trace_last_str)                                                         \
    VTSS_TRACE_TYPE_X(lmu_cstr_t *, lmu_fmt_cstr, vtss_trace_single_cstr, vtss_trace_first_cstr,   \
                      vtss_trace_last_cstr)                                                        \
    VTSS_TRACE_TYPE_X(lm_ipv4_t *, lmu_fmt_ipv4, vtss_trace_single_ipv4, vtss_trace_first_ipv4,    \
                      vtss_trace_last_ipv4)                                                        \
    VTSS_TRACE_TYPE_X(lm_ipv4_prefix_t *, lmu_fmt_ipv4_prefix, vtss_trace_single_ipv4_prefix,      \
                      vtss_trace_first_ipv4_prefix, vtss_trace_last_ipv4_prefix)                   \
    VTSS_TRACE_TYPE_X(lmu_bin4_t *, lmu_fmt_bin4, vtss_trace_single_bin4, vtss_trace_first_bin4,   \
                      vtss_trace_last_bin4)                                                        \
    VTSS_TRACE_TYPE_X(lm_port_list_t *, lmu_fmt_port_list, vtss_trace_single_port_list,            \
                      vtss_trace_first_port_list, vtss_trace_last_port_list)                       \
    VTSS_TRACE_TYPE_X(lm_mac_t *, lmu_fmt_mac, vtss_trace_single_mac, vtss_trace_first_mac,        \
                      vtss_trace_last_mac)

////////////////////////////////////////////////////////////////////////////////
// Declare the the single/first/last prototype for each type.
#define VTSS_TRACE_TYPE_X(TYPE, BASE, SINGLE, FIRST, LAST)                                         \
    void SINGLE(const vtss_trace_layer_t layer, const vtss_trace_group_t group,                    \
                const vtss_trace_level_t level, const char *file, const int line,                  \
                const char *func, const char *fmt, const TYPE val);                                \
    BOOL FIRST(const vtss_trace_layer_t layer, const vtss_trace_group_t group,                     \
               const vtss_trace_level_t level, const char *fmt, lmu_fmt_state_buf128_t *state,     \
               const TYPE val);                                                                    \
    void LAST(const vtss_trace_layer_t layer, const vtss_trace_group_t group,                      \
              const vtss_trace_level_t level, const char *file, const int line, const char *func,  \
              lmu_fmt_state_t *state, const TYPE val);
VTSS_TRACE_TYPES
#undef VTSS_TRACE_TYPE_X

// Special handling of uintptr_t formating
#if defined(__arm__) && !defined(__linux__)
#define VTSS_TRACE_GENERIC_SINGLE_UINTPTR                                                          \
    uintptr_t:                                                                                     \
    vtss_trace_single_i32,
#define VTSS_TRACE_GENERIC_FIRST_UINTPTR                                                           \
    uintptr_t:                                                                                     \
    vtss_trace_first_i32,
#define VTSS_TRACE_GENERIC_LAST_UINTPTR                                                            \
    uintptr_t:                                                                                     \
    vtss_trace_last_i32,
#else
// Need to be empty to avoid clashing with uint32_t/uint64_t
#define VTSS_TRACE_GENERIC_SINGLE_UINTPTR
#define VTSS_TRACE_GENERIC_FIRST_UINTPTR
#define VTSS_TRACE_GENERIC_LAST_UINTPTR
#endif

////////////////////////////////////////////////////////////////////////////////
// Using the _Generic keyword introduce in C11 to choose a fucntion based on the
// type of an expression.
#define VTSS_TRACE_GENERIC_SINGLE(LYR, GRP, LVL, FMT, X)                                           \
    _Generic((X),                                                                                  \
        VTSS_TRACE_GENERIC_SINGLE_UINTPTR uint64_t: vtss_trace_single_u64,                         \
        uint32_t: vtss_trace_single_u32,                                                           \
        uint16_t: vtss_trace_single_u16,                                                           \
        uint8_t: vtss_trace_single_u8,                                                             \
        int64_t: vtss_trace_single_i64,                                                            \
        int32_t: vtss_trace_single_i32,                                                            \
        int16_t: vtss_trace_single_i16,                                                            \
        int8_t: vtss_trace_single_i8,                                                              \
        char: vtss_trace_single_char,                                                              \
        char *: vtss_trace_single_czstr,                                                           \
        const char *: vtss_trace_single_czstr,                                                     \
        lmu_str_t *: vtss_trace_single_str,                                                        \
        lmu_cstr_t *: vtss_trace_single_cstr,                                                      \
        const lmu_cstr_t *: vtss_trace_single_cstr,                                                \
        lm_ipv4_t *: vtss_trace_single_ipv4,                                                       \
        lm_ipv4_prefix_t *: vtss_trace_single_ipv4_prefix,                                         \
        lmu_bin4_t *: vtss_trace_single_bin4,                                                      \
        lm_port_list_t *: vtss_trace_single_port_list,                                             \
        lm_mac_t *: vtss_trace_single_mac)(LYR, GRP, LVL, __FILE__, __LINE__, __FUNCTION__, FMT,   \
                                           X)

#define VTSS_TRACE_GENERIC_FIRST(LYR, GRP, LVL, FMT, X)                                            \
    _Generic((X),                                                                                  \
        VTSS_TRACE_GENERIC_FIRST_UINTPTR uint64_t: vtss_trace_first_u64,                           \
        uint32_t: vtss_trace_first_u32,                                                            \
        uint16_t: vtss_trace_first_u16,                                                            \
        uint8_t: vtss_trace_first_u8,                                                              \
        int64_t: vtss_trace_first_i64,                                                             \
        int32_t: vtss_trace_first_i32,                                                             \
        int16_t: vtss_trace_first_i16,                                                             \
        int8_t: vtss_trace_first_i8,                                                               \
        char: vtss_trace_first_char,                                                               \
        char *: vtss_trace_first_czstr,                                                            \
        const char *: vtss_trace_first_czstr,                                                      \
        lmu_str_t *: vtss_trace_first_str,                                                         \
        lmu_cstr_t *: vtss_trace_first_cstr,                                                       \
        const lmu_cstr_t *: vtss_trace_first_cstr,                                                 \
        lm_ipv4_t *: vtss_trace_first_ipv4,                                                        \
        lm_ipv4_prefix_t *: vtss_trace_first_ipv4_prefix,                                          \
        lmu_bin4_t *: vtss_trace_first_bin4,                                                       \
        lm_port_list_t *: vtss_trace_first_port_list,                                              \
        lm_mac_t *: vtss_trace_first_mac)(LYR, GRP, LVL, FMT, &lmu_fmt_state__, X)

#define VTSS_TRACE_GENERIC_LAST(LYR, GRP, LVL, X)                                                  \
    _Generic((X),                                                                                  \
        VTSS_TRACE_GENERIC_LAST_UINTPTR uint64_t: vtss_trace_last_u64,                             \
        uint32_t: vtss_trace_last_u32,                                                             \
        uint16_t: vtss_trace_last_u16,                                                             \
        uint8_t: vtss_trace_last_u8,                                                               \
        int64_t: vtss_trace_last_i64,                                                              \
        int32_t: vtss_trace_last_i32,                                                              \
        int16_t: vtss_trace_last_i16,                                                              \
        int8_t: vtss_trace_last_i8,                                                                \
        char: vtss_trace_last_char,                                                                \
        char *: vtss_trace_last_czstr,                                                             \
        const char *: vtss_trace_last_czstr,                                                       \
        lmu_str_t *: vtss_trace_last_str,                                                          \
        lmu_cstr_t *: vtss_trace_last_cstr,                                                        \
        const lmu_cstr_t *: vtss_trace_last_cstr,                                                  \
        lm_ipv4_t *: vtss_trace_last_ipv4,                                                         \
        lm_ipv4_prefix_t *: vtss_trace_last_ipv4_prefix,                                           \
        lmu_bin4_t *: vtss_trace_last_bin4,                                                        \
        lm_port_list_t *: vtss_trace_last_port_list,                                               \
        lm_mac_t *: vtss_trace_last_mac)(LYR, GRP, LVL, __FILE__, __LINE__, __FUNCTION__,          \
                                         &lmu_fmt_state__.state, X)

////////////////////////////////////////////////////////////////////////////////
// PRE-PROCESSOR Iterator over arguments. Will "call" LMU_FMT_GENERIC on each
// argument except the last where it "calls" VTSS_TRACE_GENERIC_LAST
#define VTSS_TRACE_FOREACH_0()
#define VTSS_TRACE_FOREACH_1(LYR, GRP, LVL, X) VTSS_TRACE_GENERIC_LAST(LYR, GRP, LVL, X);
#define VTSS_TRACE_FOREACH_2(LYR, GRP, LVL, X, ...)                                                \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_1(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_3(LYR, GRP, LVL, X, ...)                                                \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_2(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_4(LYR, GRP, LVL, X, ...)                                                \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_3(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_5(LYR, GRP, LVL, X, ...)                                                \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_4(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_6(LYR, GRP, LVL, X, ...)                                                \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_5(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_7(LYR, GRP, LVL, X, ...)                                                \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_6(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_8(LYR, GRP, LVL, X, ...)                                                \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_7(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_9(LYR, GRP, LVL, X, ...)                                                \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_8(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_10(LYR, GRP, LVL, X, ...)                                               \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_9(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_11(LYR, GRP, LVL, X, ...)                                               \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_10(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_12(LYR, GRP, LVL, X, ...)                                               \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_11(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_13(LYR, GRP, LVL, X, ...)                                               \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_12(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_14(LYR, GRP, LVL, X, ...)                                               \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_13(LYR, GRP, LVL, __VA_ARGS__)
#define VTSS_TRACE_FOREACH_15(LYR, GRP, LVL, X, ...)                                               \
    LMU_FMT_GENERIC(&lmu_fmt_state__.state, X);                                                    \
    VTSS_TRACE_FOREACH_14(LYR, GRP, LVL, __VA_ARGS__)

// Entry point in the foreach loop to iterate over arguments.
#define VTSS_TRACE_FOREACH(LYR, GRP, LVL, FMT, ...)                                                \
    LMU_PP_VA_ARGS_OVERLOAD(VTSS_TRACE_FOREACH_, ##__VA_ARGS__)                                    \
    (LYR, GRP, LVL, ##__VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////
// PreProcessor overloading to branch out based on the number of arguments.

// Trace called with 0 arguments
#define VTSS_TRACE0(LYR, GRP, LVL, FMT, ...)                                                       \
    if (vtss_trace_conf[GRP].level[LYR] >= LVL) {                                                  \
        vtss_callout_trace_printf(LYR, GRP, LVL, __FILE__, __LINE__, __FUNCTION__, FMT);           \
    }

// Trace called with 1 argument
#define VTSS_TRACE1(LYR, GRP, LVL, FMT, X) VTSS_TRACE_GENERIC_SINGLE(LYR, GRP, LVL, FMT, X);

// Trace called with 2 or more arguments!
#define VTSS_TRACE2(LYR, GRP, LVL, FMT, X, ...)                                                    \
    do {                                                                                           \
        lmu_fmt_state_buf128_t lmu_fmt_state__;                                                    \
        if (VTSS_TRACE_GENERIC_FIRST(LYR, GRP, LVL, FMT, X)) {                                     \
            VTSS_TRACE_FOREACH(LYR, GRP, LVL, FMT, ##__VA_ARGS__)                                  \
        }                                                                                          \
    } while (0)

#define VTSS_TRACE_FMT(LYR, GRP, LVL, FMT, ...)                                                    \
    LMU_PP_VA_ARGS_OVERLOAD_TWO_OR_MORE(VTSS_TRACE, ##__VA_ARGS__)                                 \
    (LYR, GRP, LVL, FMT, ##__VA_ARGS__)

#define VTSS_T(_grp, _lvl, fmt_str, ...)                                                           \
    VTSS_TRACE_FMT(VTSS_TRACE_LAYER, _grp, _lvl, fmt_str, ##__VA_ARGS__)
#define VTSS_HEX(_grp, _lvl, _byte_p, _byte_cnt)                                                   \
    {                                                                                              \
        if (vtss_trace_conf[_grp].level[VTSS_TRACE_LAYER] >= _lvl)                                 \
            vtss_callout_trace_hex_dump(VTSS_TRACE_LAYER, _grp, _lvl, __FILE__, __LINE__,          \
                                        __FUNCTION__, _byte_p, _byte_cnt);                         \
    }

// Error trace
#if VTSS_OPT_TRACE_ERROR
#define VTSS_E(fmt_str, ...)           VTSS_EG(VTSS_TRACE_GROUP, fmt_str, ##__VA_ARGS__)
#define VTSS_E_HEX(_byte_p, _byte_cnt) VTSS_EG_HEX(VTSS_TRACE_GROUP, _byte_p, _byte_cnt)
#define VTSS_EG(_grp, fmt_str, ...)    VTSS_T(_grp, VTSS_TRACE_LEVEL_ERROR, fmt_str, __VA_ARGS__)
#define VTSS_EG_HEX(_grp, _byte_p, _byte_cnt)                                                      \
    VTSS_HEX(_grp, VTSS_TRACE_LEVEL_ERROR, _byte_p, _byte_cnt)
#else
#define VTSS_E(...)
#define VTSS_E_HEX(grp, ...)
#define VTSS_EG(_grp, ...)
#define VTSS_EG_HEX(_grp, _byte_p, _byte_cnt)
#endif

// Info/debug/noise trace
#if VTSS_OPT_TRACE

#define VTSS_I(fmt_str, ...) VTSS_IG(VTSS_TRACE_GROUP, fmt_str, ##__VA_ARGS__)
#define VTSS_D(fmt_str, ...) VTSS_DG(VTSS_TRACE_GROUP, fmt_str, ##__VA_ARGS__)
#define VTSS_N(fmt_str, ...) VTSS_NG(VTSS_TRACE_GROUP, fmt_str, ##__VA_ARGS__)

#define VTSS_I_HEX(_byte_p, _byte_cnt) VTSS_IG_HEX(VTSS_TRACE_GROUP, _byte_p, _byte_cnt)
#define VTSS_D_HEX(_byte_p, _byte_cnt) VTSS_DG_HEX(VTSS_TRACE_GROUP, _byte_p, _byte_cnt)
#define VTSS_N_HEX(_byte_p, _byte_cnt) VTSS_NG_HEX(VTSS_TRACE_GROUP, _byte_p, _byte_cnt)

#define VTSS_IG(_grp, fmt_str, ...) VTSS_T(_grp, VTSS_TRACE_LEVEL_INFO, fmt_str, __VA_ARGS__)
#define VTSS_DG(_grp, fmt_str, ...) VTSS_T(_grp, VTSS_TRACE_LEVEL_DEBUG, fmt_str, __VA_ARGS__)
#define VTSS_NG(_grp, fmt_str, ...) VTSS_T(_grp, VTSS_TRACE_LEVEL_NOISE, fmt_str, __VA_ARGS__)

#define VTSS_IG_HEX(_grp, _byte_p, _byte_cnt)                                                      \
    VTSS_HEX(_grp, VTSS_TRACE_LEVEL_INFO, _byte_p, _byte_cnt)
#define VTSS_DG_HEX(_grp, _byte_p, _byte_cnt)                                                      \
    VTSS_HEX(_grp, VTSS_TRACE_LEVEL_DEBUG, _byte_p, _byte_cnt)
#define VTSS_NG_HEX(_grp, _byte_p, _byte_cnt)                                                      \
    VTSS_HEX(_grp, VTSS_TRACE_LEVEL_NOISE, _byte_p, _byte_cnt)

#else /* VTSS_OPT_TRACE */

/* No trace */
#define VTSS_I(...)
#define VTSS_D(...)
#define VTSS_N(...)

#define VTSS_I_HEX(grp, ...)
#define VTSS_D_HEX(grp, ...)
#define VTSS_N_HEX(grp, ...)

#define VTSS_IG(_grp, ...)
#define VTSS_DG(_grp, ...)
#define VTSS_NG(_grp, ...)

#define VTSS_IG_HEX(_grp, _byte_p, _byte_cnt)
#define VTSS_DG_HEX(_grp, _byte_p, _byte_cnt)
#define VTSS_NG_HEX(_grp, _byte_p, _byte_cnt)

#endif /* VTSS_OPT_TRACE */

#endif /* VTSS_STATE_H */
