// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef __MSCC_APPL_TRACE_H_
#define __MSCC_APPL_TRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "microchip/ethernet/board/api.h"

// Trace group information
typedef struct mscc_appl_trace_group_t {
    const char         *name;
    mesa_trace_level_t level;

    // Internal fields
    struct mscc_appl_trace_group_t *next;
} mscc_appl_trace_group_t;

// Trace module information
typedef struct mscc_appl_trace_module_t {
    const char *name;

    // Internal fields
    struct mscc_appl_trace_module_t *next;
    mscc_appl_trace_group_t         *group_list;
} mscc_appl_trace_module_t;

// Register trace groups for module
void mscc_appl_trace_register(mscc_appl_trace_module_t *module,
                              mscc_appl_trace_group_t *group,
                              uint32_t count);

void mscc_appl_trace_printf(const char *mname,
                            const char *gname,
                            const mesa_trace_level_t level,
                            const char *file,
                            const int line,
                            const char *function,
                            const char *format,
                            ...);

void mscc_phy_vtrace_printf(mepa_trace_group_t group,
                            mepa_trace_level_t level,
                            const char *location,
                            uint32_t line,
                            const char *format,
                            va_list args);

void mscc_phy_trace_printf(mepa_trace_group_t group,
                           mepa_trace_level_t level,
                           const char *location,
                           uint32_t line,
                           const char *format,
                           ...);

void mscc_appl_trace_vprintf(const char *mname,
                             const char *gname,
                             const mesa_trace_level_t level,
                             const char *file,
                             const int line,
                             const char *function,
                             const char *format,
                             va_list args);

void mscc_appl_trace_hex(const char *mname,
                         const char *gname,
                         const mesa_trace_level_t level,
                         const char *file,
                         const int line,
                         const char *function,
                         const unsigned char *byte_p,
                         const int byte_cnt);

void mscc_mepa_trace_printf(const mepa_trace_data_t *data,
                            va_list                  args);

// Trace macros
#define T(_grp, _lvl, _fmt, ...)       { if (trace_groups[_grp].level >= _lvl) mscc_appl_trace_printf(trace_module.name, trace_groups[_grp].name, _lvl, __FILE__, __LINE__, __FUNCTION__, _fmt, ##__VA_ARGS__);}
#define T_HEX(_grp, _lvl, _byte, _cnt) { if (trace_groups[_grp].level >= _lvl) mscc_appl_trace_hex(trace_module.name, trace_groups[_grp].name, _lvl, __FILE__, __LINE__, __FUNCTION__, _byte, _cnt);}
#define T_EG(_grp, _fmt, ...)          T(_grp, MESA_TRACE_LEVEL_ERROR, _fmt, ##__VA_ARGS__)
#define T_E(_fmt, ...)                 T_EG(0, _fmt, ##__VA_ARGS__)
#define T_EG_HEX(_grp, _byte, _cnt)    T_HEX(_grp, MESA_TRACE_LEVEL_ERROR, _byte, _cnt)
#define T_E_HEX(_byte, _cnt)           T_EG_HEX(0, _byte, _cnt)
#define T_IG(_grp, _fmt, ...)          T(_grp, MESA_TRACE_LEVEL_INFO, _fmt, ##__VA_ARGS__)
#define T_I(_fmt, ...)                 T_IG(0, _fmt, ##__VA_ARGS__)
#define T_IG_HEX(_grp, _byte, _cnt)    T_HEX(_grp, MESA_TRACE_LEVEL_INFO, _byte, _cnt)
#define T_I_HEX(_byte, _cnt)           T_IG_HEX(0, _byte, _cnt)
#define T_DG(_grp, _fmt, ...)          T(_grp, MESA_TRACE_LEVEL_DEBUG, _fmt, ##__VA_ARGS__)
#define T_D(_fmt, ...)                 T_DG(0, _fmt, ##__VA_ARGS__)
#define T_DG_HEX(_grp, _byte, _cnt)    T_HEX(_grp, MESA_TRACE_LEVEL_DEBUG, _byte, _cnt)
#define T_D_HEX(_byte, _cnt)           T_DG_HEX(0, _byte, _cnt)
#define T_NG(_grp, _fmt, ...)          T(_grp, MESA_TRACE_LEVEL_NOISE, _fmt, ##__VA_ARGS__)
#define T_N(_fmt, ...)                 T_NG(0, _fmt, ##__VA_ARGS__)
#define T_NG_HEX(_grp, _byte, _cnt)    T_HEX(_grp, MESA_TRACE_LEVEL_NOISE, _byte, _cnt)
#define T_N_HEX(_byte, _cnt)           T_NG_HEX(0, _byte, _cnt)

#ifdef __cplusplus
}
#endif

#endif /* __MSCC_APPL_TRACE_H_ */
