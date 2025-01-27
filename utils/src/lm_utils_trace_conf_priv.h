// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LM_UTILS_TRACE_CONF_PRIV_H
#define LM_UTILS_TRACE_CONF_PRIV_H

#include <lm_utils_trace_conf.h>

uint32_t lmu_trace_conf_match_name(const uint8_t *begin, const uint8_t *end,
                                   const char *name, lmu_bool_t *match);

#endif
