/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifdef __KERNEL__
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/clk.h>
#include <asm/uaccess.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/random.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <malloc.h>
//#include <conio.h>
#include <signal.h>
//#include <tchar.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define udelay(x)	usleep(x)

#define BIT(n)		(1 << (n))
#endif
