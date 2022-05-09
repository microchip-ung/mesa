// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_STATE_H_
#define _VTSS_STATE_H_

#include <vtss_api.h>

#if defined(VTSS_FEATURE_MPLS)
#include "vtss_mpls_common.h"
#endif
#if defined(VTSS_ARCH_OCELOT)
#include "../ocelot/vtss_ocelot.h"
#endif

/* Bit field macros */
#define VTSS_BF_SIZE(n)      ((n+7)/8)
#define VTSS_BF_GET(a, n)    ((a[(n)/8] & (1<<((n)%8))) ? 1 : 0)
#define VTSS_BF_SET(a, n, v) do { if (v) { a[(n)/8] |= (1U<<((n)%8)); } else { a[(n)/8] &= ~(1U<<((n)%8)); }} while (0)
#define VTSS_BF_CLR(a, n)    (VTSS_MEMSET(a, 0, VTSS_BF_SIZE(n)))

/* Port member bit field macros */
#define VTSS_PORT_BF_SIZE                VTSS_BF_SIZE(VTSS_PORTS)
#define VTSS_PORT_BF_GET(a, port_no)     VTSS_BF_GET(a, (port_no) - VTSS_PORT_NO_START)
#define VTSS_PORT_BF_SET(a, port_no, v)  VTSS_BF_SET(a, (port_no) - VTSS_PORT_NO_START, v)
#define VTSS_PORT_BF_CLR(a)              VTSS_BF_CLR(a, VTSS_PORTS)

#if defined(VTSS_FEATURE_MISC)
#include "vtss_misc_state.h"
#endif

#if defined(VTSS_FEATURE_PORT_CONTROL)
#include "vtss_port_state.h"
#endif

#if defined(VTSS_FEATURE_QOS)
#include "vtss_qos_state.h"
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

/* Call Chip Interface Layer function if it exists */
#define VTSS_FUNC(func, ...) (vtss_state->func == NULL ? VTSS_RC_ERROR : vtss_state->func(vtss_state, ##__VA_ARGS__))

/* Call Chip Interface Layer function if it exists, given the state as an argument. This is useful for functions that don't require vtss_state to be set-up. */
#define VTSS_FUNC_FROM_STATE(state, func, ...) ((state == NULL || state->func == NULL) ? VTSS_RC_ERROR : state->func(state, __VA_ARGS__))

/* Call Chip Interface Layer function if it exists, return error code, if error */
#define VTSS_FUNC_RC(func, ...) { vtss_rc __rc__ = (vtss_state->func == NULL ? VTSS_RC_ERROR : vtss_state->func(vtss_state, ## __VA_ARGS__)); if (__rc__ < VTSS_RC_OK) return __rc__; }
/* Call Chip Interface Layer function if it exists and we are in cold start mode */
#define VTSS_FUNC_COLD(func, ...) (vtss_state->func == NULL ? VTSS_RC_ERROR : vtss_state->warm_start_cur ? VTSS_RC_OK : vtss_state->func(vtss_state, ## __VA_ARGS__))

/* The following macros are needed when only the 'vtss_state' is passed to the CIL function,
   to avoid warnings on certain compilers */
#define VTSS_FUNC_0(func, ...) (vtss_state->func == NULL ? VTSS_RC_ERROR : vtss_state->func(vtss_state))
#define VTSS_FUNC_COLD_0(func, ...) (vtss_state->func == NULL ? VTSS_RC_ERROR : vtss_state->warm_start_cur ? VTSS_RC_OK : vtss_state->func(vtss_state))
#define VTSS_FUNC_RC_0(func, ...) { vtss_rc __rc__ = (vtss_state->func == NULL ? VTSS_RC_ERROR : vtss_state->func(vtss_state)); if (__rc__ < VTSS_RC_OK) return __rc__; }

/* Call function in cold start mode only */
#define VTSS_RC_COLD(expr) (vtss_state->warm_start_cur ? VTSS_RC_OK : (expr))

/* Set currently selected device */
#define VTSS_SELECT_CHIP(__chip_no__) { vtss_state->chip_no = (__chip_no__); }
#define VTSS_SELECT_CHIP_PORT_NO(port_no) VTSS_SELECT_CHIP(vtss_state->port.map[port_no].chip_no)
/* API enter/exit macros for protection */
#define VTSS_ENTER(...) { vtss_api_lock_t _lock; _lock.inst = inst; _lock.function = __FUNCTION__; _lock.file = __FILE__; _lock.line = __LINE__; vtss_callout_lock(&_lock); vtss_func = __FUNCTION__; }
#define VTSS_EXIT(...) { vtss_api_lock_t _lock; _lock.inst = inst; _lock.function = __FUNCTION__; _lock.file = __FILE__; _lock.line = __LINE__; vtss_func = NULL; vtss_callout_unlock(&_lock); }
#define VTSS_EXIT_ENTER(...) { vtss_state_t *old_state = vtss_state; vtss_chip_no_t old_chip = vtss_state->chip_no; vtss_api_lock_t _lock; _lock.function = __FUNCTION__; _lock.file = __FILE__; _lock.line = __LINE__; vtss_callout_unlock(&_lock); vtss_callout_lock(&_lock); vtss_state = old_state; vtss_state->chip_no = old_chip; }

#define VTSS_RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }

#define VTSS_BOOL(expr) ((expr) ? 1 : 0)

#define VTSS_CHIP_PORT(port_no)                   vtss_state->port.map[port_no].chip_port
#define VTSS_CHIP_NO(port_no)                     vtss_state->port.map[port_no].chip_no
#define VTSS_CHIP_PORT_FROM_STATE(state, port_no) (state)->port.map[port_no].chip_port
#define VTSS_CHIP_NO_FROM_STATE(state, port_no)   (state)->port.map[port_no].chip_no
#define VTSS_PORT_CHIP_SELECTED(port_no)          (vtss_state->port.map[port_no].chip_no == vtss_state->chip_no)

/* Get array size */
#define VTSS_ARRSZ(t) /*lint -e{574} */ (sizeof(t)/sizeof(t[0])) /* Suppress Lint Warning 574: Signed-unsigned mix with relational */

/* Target architecture */
typedef enum {
    VTSS_ARCH_CU_PHY,  /* Cu PHYs */
    VTSS_ARCH_10G_PHY, /* 10G PHYs */
    VTSS_ARCH_L26,     /* Luton26 */
    VTSS_ARCH_SRVL,    /* Serval */
    VTSS_ARCH_JR1,     /* Jaguar-1 */
    VTSS_ARCH_JR2,     /* Jaguar-2 */
    VTSS_ARCH_ANT,      /* FA */
    VTSS_ARCH_LAN_966X,/* LAN966X */
} vtss_arch_t;

/* Warm start scratch-pad 32-bit register layout */
#define VTSS_RESTART_VERSION_OFFSET 0
#define VTSS_RESTART_VERSION_WIDTH  16
#define VTSS_RESTART_TYPE_OFFSET    16
#define VTSS_RESTART_TYPE_WIDTH     3

/* API version used to determine if warm start can be done while downgrading/upgrading */
#define VTSS_API_VERSION 1

/* Ethernet types */
#define VTSS_ETYPE_TAG_C 0x8100
#define VTSS_ETYPE_TAG_S 0x88a8

#if defined(VTSS_FEATURE_EEE)
#define VTSS_EEE_TIMER_TABLE_CNT 128

typedef struct {
    /* CIL function pointers */
    vtss_rc (* port_conf_set)(struct vtss_state_s *vtss_state,
                              const vtss_port_no_t port_no,
                              const vtss_eee_port_conf_t    *const eee_conf);
    /* Configuration/state */
    BOOL ena[VTSS_PORT_ARRAY_SIZE]; // Signaling current state in the switch api
    BOOL ena_phy[VTSS_PORT_ARRAY_SIZE]; // Signaling current state in the phy api
    u32  timer_table[VTSS_EEE_TIMER_TABLE_CNT];
    BOOL timer_table_initialized;
} vtss_eee_state_t;
#endif /* VTSS_FEATURE_EEE */

#if defined(VTSS_FEATURE_FAN)
typedef struct {
    /* CIL function pointers */
    vtss_rc (* controller_init)(struct vtss_state_s *vtss_state,
                                const vtss_fan_conf_t *const spec);
    vtss_rc (* cool_lvl_set)(struct vtss_state_s *vtss_state, u8 lvl);
    vtss_rc (* cool_lvl_get)(struct vtss_state_s *vtss_state, u8 *lvl);
    vtss_rc (* rotation_get)(struct vtss_state_s *vtss_state,
                             vtss_fan_conf_t *fan_spec, u32 *rotation_count);
    /* Configuration/state */
    u16             rotation_count; // Fan rotations count
    vtss_fan_conf_t conf;           // Fan configuration/specifications.
    u8              lvl;            // Fan speed level
} vtss_fan_state_t;
#endif /* VTSS_FEATURE_FAN */

#if defined(VTSS_FEATURE_TEMP_SENSOR)
typedef struct {
    /* CIL function pointers */
    vtss_rc (* chip_temp_get)(struct vtss_state_s *vtss_state, i16 *chip_temp);
    vtss_rc (* chip_temp_init)(struct vtss_state_s *vtss_state, const BOOL enable);

    i16             chip_temp;      // Chip temperature
} vtss_temp_sensor_state_t;
#endif /* VTSS_FEATURE_TEMP_SENSOR */

#if defined(VTSS_FEATURE_SYNCE)
typedef struct {
    /* CIL function pointers */
    vtss_rc (* clock_out_set)(struct vtss_state_s *vtss_state, const vtss_synce_clk_port_t clk_port);
    vtss_rc (* clock_in_set)(struct vtss_state_s *vtss_state, const vtss_synce_clk_port_t clk_port);
    vtss_rc (* station_clk_out_set)(struct vtss_state_s *vtss_state, const vtss_synce_clk_port_t clk_port);

    /* Configuration/state */
    u32                    old_port_no[VTSS_SYNCE_CLK_PORT_ARRAY_SIZE];
    vtss_synce_clock_in_t  in_conf[VTSS_SYNCE_CLK_PORT_ARRAY_SIZE];
    vtss_synce_clock_out_t out_conf[VTSS_SYNCE_CLK_PORT_ARRAY_SIZE];
    vtss_synce_station_clock_out_t station_clk_out_conf[VTSS_SYNCE_CLK_PORT_ARRAY_SIZE];
} vtss_synce_state_t;
#endif /* VTSS_FEATURE_SYNCE */

/* Opaque forward declaration */
struct vtss_state_s;

/* ================================================================= *
 *  Chip Interface Layer functions
 * ================================================================= */
typedef struct {
    vtss_rc (* init_conf_set)(struct vtss_state_s *vtss_state);

    vtss_rc (* register_access_mode_set)(struct vtss_state_s *vtss_state);

    vtss_rc (* qs_conf_set)(struct vtss_state_s *vtss_state);

#if defined(VTSS_FEATURE_WARM_START)
    vtss_rc (* restart_conf_set)(struct vtss_state_s *vtss_state);
#endif /* VTSS_FEATURE_WARM_START */

#if VTSS_OPT_DEBUG_PRINT
    vtss_rc (* debug_info_print)(struct vtss_state_s *vtss_state,
                                 const vtss_debug_printf_t prntf,
                                 const vtss_debug_info_t   *const info);
#endif
} vtss_cil_func_t;

/* ================================================================= *
 *  Total API state
 * ================================================================= */

/* State cookie */
#define VTSS_STATE_COOKIE 0x53727910

/* State structure */
typedef struct vtss_state_s {
    /* Initialization */
    u32                           cookie;
    vtss_arch_t                   arch;            /* Architecture */
    vtss_inst_create_t            create;
    vtss_init_conf_t              init_conf;
    BOOL                          restart_updated; /* Restart has been detected */
    BOOL                          warm_start_cur;  /* Current warm start status */
    BOOL                          warm_start_prev; /* Previous warm start status */
#if defined(VTSS_FEATURE_WARM_START)
    vtss_restart_t                restart_cur;     /* Current restart configuration */
    vtss_restart_t                restart_prev;    /* Previous restart configuration */
    vtss_version_t                version_cur;     /* Current version */
    vtss_version_t                version_prev;    /* Previous version */
#endif /* VTSS_FEATURE_WARM_START */
    BOOL                          sync_calling_private; /* Used by PHY APIs */

    u32                           chip_count;      /* Number of devices */
    vtss_chip_no_t                chip_no;         /* Currently selected device */
    u32                           port_count;

    /* CIL function pointers not part of a specific group */
    vtss_cil_func_t cil;

#if defined(VTSS_FEATURE_MISC)
    vtss_misc_state_t misc;
#endif /* VTSS_FEATURE_MISC */

#if defined(VTSS_FEATURE_PORT_CONTROL)
    vtss_port_state_t port;
#endif /* VTSS_FEATURE_PORT_CONTROL */

#if defined(VTSS_FEATURE_QOS)
    vtss_qos_state_t qos;
#endif /* VTSS_FEATURE_QOS */

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
#endif  /* VTSS_FEATURE_SYNCE */

#if defined(VTSS_FEATURE_FAN)
    vtss_fan_state_t fan;
#endif  /* VTSS_FEATURE_FAN */

#if defined(VTSS_FEATURE_TEMP_SENSOR)
    vtss_temp_sensor_state_t temp_sensor;
#endif  /* VTSS_FEATURE_TEMP_SENSOR */

#if defined(VTSS_FEATURE_EEE)
    vtss_eee_state_t eee;
#endif  /* VTSS_FEATURE_EEE */

#if defined(VTSS_FEATURE_AFI_SWC)
    vtss_afi_state_t              afi;
#endif /* VTSS_FEATURE_AFI_SWC */

    struct {
        u8   vcore_cfg;         /* If supported by target */
        BOOL using_vcoreiii;    /* If supported by target */
        BOOL using_vrap;        /* If supported by target */
        BOOL using_pcie;        /* If supported by target */
    } sys_config;

    BOOL                   system_reseting; // Signaling if system is rebooting.

    char txt_buf[256];  /* General purpose text string buffer */
    int  txt_buf_index; /* Index to text buffer */
    void *app_data;    /**< Application data pointer */
} vtss_state_t;

/* Check instance */
vtss_rc vtss_inst_check(const vtss_inst_t inst, vtss_state_t **vtss_state);
vtss_rc vtss_inst_check_get(const vtss_inst_t inst, vtss_state_t **vtss_state);
vtss_state_t *vtss_inst_check_no_persist(const vtss_inst_t inst);

/* Check instance and port number */
vtss_rc vtss_inst_port_no_check(const vtss_inst_t    inst,
                                vtss_state_t         **vtss_state,
                                const vtss_port_no_t port_no);

vtss_rc vtss_inst_port_no_none_check(const vtss_inst_t    inst,
                                     vtss_state_t         **vtss_state,
                                     const vtss_port_no_t port_no);

vtss_rc vtss_inst_chip_no_check(const vtss_inst_t    inst,
                                vtss_state_t         **vtss_state,
                                const vtss_chip_no_t chip_no);

extern const char *vtss_port_if_txt(vtss_port_interface_t if_type);
extern const char *vtss_port_spd_txt(vtss_port_speed_t speed);

#if defined(VTSS_FEATURE_PORT_CONTROL)
extern const char *vtss_serdes_if_txt(vtss_serdes_mode_t serdes);
extern const char *vtss_media_type_if_txt(vtss_sd10g_media_type_t mt);
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

#if VTSS_OPT_TRACE

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

#define VTSS_E(...) VTSS_EG(VTSS_TRACE_GROUP, ##__VA_ARGS__)
#define VTSS_I(...) VTSS_IG(VTSS_TRACE_GROUP, ##__VA_ARGS__)
#define VTSS_D(...) VTSS_DG(VTSS_TRACE_GROUP, ##__VA_ARGS__)
#define VTSS_N(...) VTSS_NG(VTSS_TRACE_GROUP, ##__VA_ARGS__)

#define VTSS_E_HEX(_byte_p, _byte_cnt) VTSS_EG_HEX(VTSS_TRACE_GROUP, _byte_p, _byte_cnt)
#define VTSS_I_HEX(_byte_p, _byte_cnt) VTSS_IG_HEX(VTSS_TRACE_GROUP, _byte_p, _byte_cnt)
#define VTSS_D_HEX(_byte_p, _byte_cnt) VTSS_DG_HEX(VTSS_TRACE_GROUP, _byte_p, _byte_cnt)
#define VTSS_N_HEX(_byte_p, _byte_cnt) VTSS_NG_HEX(VTSS_TRACE_GROUP, _byte_p, _byte_cnt)

/* For files with multiple trace groups: */
#define VTSS_T(_grp, _lvl, ...) { if (vtss_trace_conf[_grp].level[VTSS_TRACE_LAYER] >= _lvl) vtss_callout_trace_printf(VTSS_TRACE_LAYER, _grp, _lvl, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }
#define VTSS_EG(_grp, ...) VTSS_T(_grp, VTSS_TRACE_LEVEL_ERROR, __VA_ARGS__)
#define VTSS_IG(_grp, ...) VTSS_T(_grp, VTSS_TRACE_LEVEL_INFO,  __VA_ARGS__)
#define VTSS_DG(_grp, ...) VTSS_T(_grp, VTSS_TRACE_LEVEL_DEBUG, __VA_ARGS__)
#define VTSS_NG(_grp, ...) VTSS_T(_grp, VTSS_TRACE_LEVEL_NOISE, __VA_ARGS__)

#define VTSS_HEX(_grp, _lvl, _byte_p, _byte_cnt) { if (vtss_trace_conf[_grp].level[VTSS_TRACE_LAYER] >= _lvl) vtss_callout_trace_hex_dump(VTSS_TRACE_LAYER, _grp, _lvl, __FILE__, __LINE__, __FUNCTION__, _byte_p, _byte_cnt); }
#define VTSS_EG_HEX(_grp, _byte_p, _byte_cnt) VTSS_HEX(_grp, VTSS_TRACE_LEVEL_ERROR, _byte_p, _byte_cnt)
#define VTSS_IG_HEX(_grp, _byte_p, _byte_cnt) VTSS_HEX(_grp, VTSS_TRACE_LEVEL_INFO,  _byte_p, _byte_cnt)
#define VTSS_DG_HEX(_grp, _byte_p, _byte_cnt) VTSS_HEX(_grp, VTSS_TRACE_LEVEL_DEBUG, _byte_p, _byte_cnt)
#define VTSS_NG_HEX(_grp, _byte_p, _byte_cnt) VTSS_HEX(_grp, VTSS_TRACE_LEVEL_NOISE, _byte_p, _byte_cnt)

#else /* VTSS_OPT_TRACE */

/* No trace */
#define VTSS_E(...)
#define VTSS_I(...)
#define VTSS_D(...)
#define VTSS_N(...)

#define VTSS_E_HEX(grp, ...)
#define VTSS_I_HEX(grp, ...)
#define VTSS_D_HEX(grp, ...)
#define VTSS_N_HEX(grp, ...)

#define VTSS_EG(_grp, ...)
#define VTSS_IG(_grp, ...)
#define VTSS_DG(_grp, ...)
#define VTSS_NG(_grp, ...)

#define VTSS_EG_HEX(_grp, _byte_p, _byte_cnt)
#define VTSS_IG_HEX(_grp, _byte_p, _byte_cnt)
#define VTSS_DG_HEX(_grp, _byte_p, _byte_cnt)
#define VTSS_NG_HEX(_grp, _byte_p, _byte_cnt)

#endif /* VTSS_OPT_TRACE */


#endif /* _VTSS_STATE_H_ */
