// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef MESA_INTERNAL_HXX
#define MESA_INTERNAL_HXX

// Make sure assert() really asserts
// BEGIN
#if defined(NDEBUG)
#define NDEBUG_WAS_DEFINED
#undef NDEBUG
#endif

#include <assert.h>
#define MESA_ASSERT(expr) assert(expr)

#if defined(NDEBUG_WAS_DEFINED)
#define NDEBUG
#undef NDEBUG_WAS_DEFINED
#endif
// END

#endif /* MESA_INTERNAL_HXX */
