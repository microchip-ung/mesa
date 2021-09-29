// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_GLOBAL_FAST_RESET_H_
#define _VTSS_VENICE_REGS_GLOBAL_FAST_RESET_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a GLOBAL_FAST_RESET
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a GLOBAL_FAST_RESET:FAST_ACCESS_RESET
 *
 * FAST RESET REGISTERS NOT ON CSR RING
 */


/** 
 * \brief FAST RESET REGISTERS NOT ON CSR RING
 *
 * \details
 * Fast access reset registers not on CSR ring
 *
 * Register: \a GLOBAL_FAST_RESET:FAST_ACCESS_RESET:GLOBAL_FAST_RESET
 */
#define VTSS_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET  VTSS_IOREG(0x1e, 0, 0x8000)

/** 
 * \brief
 * Self-clearance fast access reset
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 2

 *
 * Field: VTSS_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_2_FAST_RESET
 */
#define  VTSS_F_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_2_FAST_RESET  VTSS_BIT(5)

/** 
 * \brief
 * Self-clearance fast access reset
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 1

 *
 * Field: VTSS_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_1_FAST_RESET
 */
#define  VTSS_F_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_1_FAST_RESET  VTSS_BIT(4)

/** 
 * \brief
 * Self-clearance fast access reset
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 0

 *
 * Field: VTSS_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_0_FAST_RESET
 */
#define  VTSS_F_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_0_FAST_RESET  VTSS_BIT(3)

/** 
 * \brief
 * Self-clearance fast access reset
 *
 * \details 
 * 0: Normal operation
 * 1: Reset channel 1 and CSR ring 1

 *
 * Field: VTSS_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CHANNEL_1_FAST_RESET
 */
#define  VTSS_F_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CHANNEL_1_FAST_RESET  VTSS_BIT(2)

/** 
 * \brief
 * Self-clearance fast access reset
 *
 * \details 
 * 0: Normal operation
 * 1: Reset channel 0 and CSR ring 0

 *
 * Field: VTSS_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CHANNEL_0_FAST_RESET
 */
#define  VTSS_F_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CHANNEL_0_FAST_RESET  VTSS_BIT(1)

/** 
 * \brief
 * Reset the datapath in both channels and all configuration registers
 * except those used for global configuration.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset

 *
 * Field: VTSS_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CHIP_FAST_RESET
 */
#define  VTSS_F_GLOBAL_FAST_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CHIP_FAST_RESET  VTSS_BIT(0)


#endif /* _VTSS_VENICE_REGS_GLOBAL_FAST_RESET_H_ */
