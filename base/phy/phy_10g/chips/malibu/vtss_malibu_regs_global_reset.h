// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_GLOBAL_RESET_H_
#define _VTSS_MALIBU_REGS_GLOBAL_RESET_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a GLOBAL_RESET
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a GLOBAL_RESET:FAST_ACCESS_RESET
 *
 * FAST RESET REGISTERS ARE NOT ON A CSR RING
 */


/** 
 * \brief FAST RESET REGISTERS ARE NOT ON A CSR RING
 *
 * \details
 * Fast access reset registers are not on a CSR ring
 *
 * Register: \a GLOBAL_RESET:FAST_ACCESS_RESET:GLOBAL_FAST_RESET
 */
#define VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET  VTSS_IOREG(0x1e, 0, 0x8000)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 2

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_5_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_5_FAST_RESET  VTSS_BIT(13)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 2

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_4_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_4_FAST_RESET  VTSS_BIT(12)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 2

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_3_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_3_FAST_RESET  VTSS_BIT(11)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 2

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_2_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_2_FAST_RESET  VTSS_BIT(10)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 1

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_1_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_1_FAST_RESET  VTSS_BIT(9)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset CSR ring 0

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CSR_RING_0_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CSR_RING_0_FAST_RESET  VTSS_BIT(8)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset channel 1 and CSR ring 1

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CHANNEL_3_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CHANNEL_3_FAST_RESET  VTSS_BIT(7)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset channel 1 and CSR ring 1

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CHANNEL_2_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CHANNEL_2_FAST_RESET  VTSS_BIT(6)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset channel 1 and CSR ring 1

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CHANNEL_1_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CHANNEL_1_FAST_RESET  VTSS_BIT(5)

/** 
 * \brief
 * Self-clearing software reset register
 *
 * \details 
 * 0: Normal operation
 * 1: Reset channel 0 and CSR ring 0

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CHANNEL_0_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CHANNEL_0_FAST_RESET  VTSS_BIT(4)

/** 
 * \brief
 * Reset the datapath in both channels and all configuration registers
 * except those used for global configuration.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset

 *
 * Field: VTSS_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET . CHIP_FAST_RESET
 */
#define  VTSS_F_GLOBAL_RESET_FAST_ACCESS_RESET_GLOBAL_FAST_RESET_CHIP_FAST_RESET  VTSS_BIT(0)


#endif /* _VTSS_MALIBU_REGS_GLOBAL_RESET_H_ */
