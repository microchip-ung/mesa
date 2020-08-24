/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _TYPES_H_
#define _TYPES_H_

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/time64.h>
#else
#if !defined(NULL)
#define NULL ((void *)0)
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef short s16;
typedef int s32;
typedef long long s64;
typedef s64 time64_t;

struct timespec64 {
	time64_t	tv_sec;			/* seconds */
	long		tv_nsec;		/* nanoseconds */
};
#endif

#endif /* _TYPES_H_ */
