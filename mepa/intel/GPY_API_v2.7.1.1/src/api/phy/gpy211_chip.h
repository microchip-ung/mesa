/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _GPY211_CHIP_H_
#define _GPY211_CHIP_H_

#include "gpy211_regs.h"

/* PTP defines */
#define SEC_TO_NANOSEC(sec) ((sec) * 1000000000ULL)
#define MHZ_TO_HZ(freq) ((freq) * 1000000ULL)
#define NEG_SEC_TO_NANOSEC(sec) -((sec) * 1000000000)
/* Max Nano-Seconds in one Day */
#define MAX_NANOSEC_IN_DAY 86399999999999ULL
/* Max Nano-seconds in one Sec  //999,999,999  */
#define MAX_NSEC_IN_SEC	0x3B9AC9FF
/* Max Nano-seconds in Digital rollover mode  //999,999,999  */
#define DIG_ROLLOVER_NSEC_MAX 0x3B9AC9FF
/* Max Nano-seconds in Binarty rollover mode  //999999999 / 0.465 */
#define BIN_ROLLOVER_NSEC_MAX 0x7FFFFFFF
/* Source Port Identity len in bytes */
#define PTP_SPORT_ID_LEN_BYTE 10
/* Source Port Identity len in bytes */
#define PTP_SPORT_ID_LEN_HWORD (PTP_SPORT_ID_LEN_BYTE / 2)
/* Log Sync Interval min value */
#define PTP_LOG_SYNC_INTVL_MIN -15
/* Log Sync Interval max value */
#define PTP_LOG_SYNC_INTVL_MAX 15
/* Log Sync Interval max value */
#define PTP_DR_TO_SYNC_RATIO_MAX 5
/* Log Min Pdelay_Req Interval min value */
#define PTP_LOG_MIN_PDR_INTVL_MIN -15
/* Log Min Pdelay_Req Interval max value */
#define PTP_LOG_MIN_PDR_INTVL_MAX 15

static struct {
	u32 output;
	u32 input;
	u32 dir;
	u32 alt0;
	u32 alt1;
	u32 od;
	u32 pull_up;
	u32 pull_en;
	u32 strength0;
	u32 strength1;
	u32 fast_slew;
	u32 voltage_ctrl;
} gpio_reg[] = {
	{
output:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_OUT,
input:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_IN,
dir:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_DIR,
alt0:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_ALTSEL0,
alt1:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_ALTSEL1,
od:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_OD,
pull_up:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_PUDSEL,
pull_en:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_PUDEN,
strength0:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_DRIVE0_CFG,
strength1:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_DRIVE1_CFG,
fast_slew:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_SLEW_CFG,
voltage_ctrl:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_VOL_CFG,
	},
	{
output:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_OUT,
input:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_IN,
dir:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_DIR,
alt0:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_ALTSEL0,
alt1:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_ALTSEL1,
od:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_OD,
pull_up:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_PUDSEL,
pull_en:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_PUDEN,
strength0:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_DRIVE0_CFG,
strength1:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_DRIVE1_CFG,
fast_slew:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO2_SLEW_CFG,
voltage_ctrl:
		GPIO_PDI_REGISTERS_GPIO_PDI_REGISTERS_GPIO_VOL_CFG,
	}
};

#endif /* _GPY211_CHIP_H_ */
