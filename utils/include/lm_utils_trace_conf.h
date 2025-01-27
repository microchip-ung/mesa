// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LM_UTILS_TRACE_CONF_H
#define LM_UTILS_TRACE_CONF_H

#include <lm_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// Purpose of lmu_trace_conf_* is to store a collection of named trace channels
// and the configured max level which is considered active.
//
// As the lmu_trace_conf_active function is called many times, it is important
// that the performance of that is optimial.
//
// The implementation uses a lmu_bin_t to store all the data. The format is:
// <trace-level><tracename><seperator>
//
// Here: <trace-level> is a single char in the range of 0-31 (both included)
// <trace-name> is a sequence of chars in the range of 32-127 (both included)
// <seperator> is 0x255
//
// The end is mated by an additional 0x255
//
// When adding/setting trace levels, the entries shall be moved such that they
// are sorted by trace level starting with the highes. This allows
// 'lmu_trace_conf_active' to return LMU_FALSE, if there is no match, and the
// configured level of an entry is lover than the actual level.
//
// Example: '3', 'f', 'o', 'o', 0xff, '2', 'b', 'a', 'r', 0xff, '1', 'b', 'a',
// 'z', 0xff, 0xff
//
// When traces are disabled, then lmu_trace_conf_active will return LMU_FALSE
// after checking just 1 byte!

// NOTE: If the name contains a '/', then the '/' and everything comming after
// it is skipped. This done to allow using the name to identify both the trace
// channel and where the trace origins.

void lmu_trace_conf_init(lmu_bin_t *ds);

lm_rc_t lmu_trace_conf_set(lmu_bin_t *ds, const char *name, uint8_t level);

lmu_bool_t lmu_trace_conf_active(lmu_bin_t *ds, const char *name,
                                 uint8_t level);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
