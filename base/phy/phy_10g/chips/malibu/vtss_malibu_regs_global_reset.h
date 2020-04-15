#ifndef _VTSS_MALIBU_REGS_GLOBAL_RESET_H_
#define _VTSS_MALIBU_REGS_GLOBAL_RESET_H_

/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

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
