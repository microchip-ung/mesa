/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#ifndef __MSCC_APPL_TRACE_H_
#define __MSCC_APPL_TRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

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

void mscc_appl_trace_vprintf(const char *mname,
                             const char *gname,
                             const mesa_trace_level_t level,
                             const char *file,
                             const int line,
                             const char *function,
                             const char *format,
                             va_list args);

// Trace macros
#define T(_grp, _lvl, _fmt, ...) { if (trace_groups[_grp].level >= _lvl) mscc_appl_trace_printf(trace_module.name, trace_groups[_grp].name, _lvl, __FILE__, __LINE__, __FUNCTION__, _fmt, ##__VA_ARGS__);}
#define T_EG(_grp, _fmt, ...)    T(_grp, MESA_TRACE_LEVEL_ERROR, _fmt, ##__VA_ARGS__)
#define T_E(_fmt, ...)           T_EG(0, _fmt, ##__VA_ARGS__)
#define T_IG(_grp, _fmt, ...)    T(_grp, MESA_TRACE_LEVEL_INFO, _fmt, ##__VA_ARGS__)
#define T_I(_fmt, ...)           T_IG(0, _fmt, ##__VA_ARGS__)
#define T_DG(_grp, _fmt, ...)    T(_grp, MESA_TRACE_LEVEL_DEBUG, _fmt, ##__VA_ARGS__)
#define T_D(_fmt, ...)           T_DG(0, _fmt, ##__VA_ARGS__)
#define T_NG(_grp, _fmt, ...)    T(_grp, MESA_TRACE_LEVEL_NOISE, _fmt, ##__VA_ARGS__)
#define T_N(_fmt, ...)           T_NG(0, _fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* __MSCC_APPL_TRACE_H_ */
