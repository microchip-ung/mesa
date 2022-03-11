/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef __GPY211_LOG_H__
#define __GPY211_LOG_H__

#ifdef __KERNEL__
#include <linux/kernel.h>
#define PRINT		printk
#else
#include <stdio.h>
#if LOGM_IN_FILE
extern FILE *mdio_fp;
FILE *get_mdio_fp(void);

#define PRINT(...)						\
	do {FILE *fp;						\
		fp = (FILE *) get_mdio_fp();	\
		fprintf(fp, __VA_ARGS__);		\
	} while (0)
#else
#define PRINT		printf
#endif
#endif

#define LOG_SEVERITY_NO_OUTPUT 0
#define LOG_SEVERITY_CRITICAL 1
#define LOG_SEVERITY_WARNING 1
#define LOG_SEVERITY_INFO 2

#ifndef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX LOG_SEVERITY_CRITICAL
#endif

#if LOG_SEVERITY_MAX >= LOG_SEVERITY_CRITICAL
#define LOG_CRIT_ENABLED
#endif

#if LOG_SEVERITY_MAX >= LOG_SEVERITY_WARNING
#define LOG_WARN_ENABLED
#endif

#if LOG_SEVERITY_MAX >= LOG_SEVERITY_INFO
#define LOG_INFO_ENABLED
#endif

#undef LOG_CRIT
#ifdef LOG_CRIT_ENABLED
#define LOG_CRIT	PRINT
#else
#define LOG_CRIT(...)
#endif

#undef LOG_WARN
#ifdef LOG_WARN_ENABLED
#define LOG_WARN	PRINT
#else
#define LOG_WARN(...)
#endif

#undef LOG_INFO
#ifdef LOG_INFO_ENABLED
#define LOG_INFO	PRINT
#else
#define LOG_INFO(...)
#endif

#endif /* __GPY211_LOG_H__ */
