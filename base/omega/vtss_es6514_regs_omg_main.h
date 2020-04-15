#ifndef _VTSS_ES6514_REGS_OMG_MAIN_H_
#define _VTSS_ES6514_REGS_OMG_MAIN_H_

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

#include "vtss_es6514_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a OMG_MAIN
 *
 * Configuration register set for Omega IP.
 *
 ***********************************************************************/

/**
 * Register Group: \a OMG_MAIN:OMG_MAIN
 *
 * Common Omega configuration registers
 */


/** 
 * \brief Main configuration register.
 *
 * \details
 * Register: \a OMG_MAIN:OMG_MAIN:OMG_MAIN_CFG
 */
#define VTSS_OMG_MAIN_OMG_MAIN_OMG_MAIN_CFG  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x0)

/** 
 * \brief
 * Software Enable.
 *
 * \details 
 * 0: Clock for all registers other than configuration and status registers
 * is disabled.
 * 1: Clock is enabled.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_MAIN_OMG_MAIN_CFG . SW_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_MAIN_OMG_MAIN_CFG_SW_ENA  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Software Reset.
 *
 * \details 
 * 0: Logic operates normally.
 * 1: Logic other than configuration and status interface registers is kept
 * in reset.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_MAIN_OMG_MAIN_CFG . SW_RST
 */
#define  VTSS_F_OMG_MAIN_OMG_MAIN_OMG_MAIN_CFG_SW_RST  VTSS_ES6514_BIT(0)


/** 
 * \brief SVN revision number.
 *
 * \details
 * Register: \a OMG_MAIN:OMG_MAIN:OMG_SVN_ID
 */
#define VTSS_OMG_MAIN_OMG_MAIN_OMG_SVN_ID    VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x1)


/** 
 * \brief Main status register.
 *
 * \details
 * Status bits of the sync-ctrl merger (SCR) and others
 *
 * Register: \a OMG_MAIN:OMG_MAIN:OMG_MAIN_STAT
 *
 * @param ri Replicator: x_NUM_OUTPUT_LANES (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_MAIN_OMG_MAIN_STAT(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x2 + (ri))

/** 
 * \brief
 * Sync. control merger protocol error. Occurs if a command (CMD) occurs on
 * both sync-ctrl inputs at the same time, i.e. if both inputs receive CMD
 * related data for at least one clock cycle simultaniously
 *
 * \details 
 * 0: No protocol error occured
 * 1: At least one protocol error occured.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_MAIN_OMG_MAIN_STAT . SCR_PROT_ERR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_MAIN_OMG_MAIN_STAT_SCR_PROT_ERR_STICKY  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Sync. control merger stack overflow/underflow. Occurs if consecutive
 * increment (overflow) or decrement (underflow) commands on the sync-ctrl
 * inputs of the merger lead to a stack overflow/underflow, i.e. increments
 * or decrements are discarded
 *
 * \details 
 * 0: No stack overflow/underflow occured
 * 1: At least one stack overflow/underflow occured.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_MAIN_OMG_MAIN_STAT . SCR_STACK_OVFL_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_MAIN_OMG_MAIN_STAT_SCR_STACK_OVFL_STICKY  VTSS_ES6514_BIT(0)

/**
 * Register Group: \a OMG_MAIN:OMG_IRQ
 *
 * Interrupt configuration and status registers
 */


/** 
 * \brief Qualifier alarm interrupt enable register 
 *
 * \details
 * Register: \a OMG_MAIN:OMG_IRQ:OMG_IRQ_ALARM_ENA_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x6 + (ri))

/** 
 * \brief
 * Interrupt enable for LOL_ALARM_CLR_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when LOL_ALARM_CLR_STICKY is active.
 * 1: Interrupt is asserted when LOL_ALARM_CLR_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_LOL_ALARM_CLR_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_LOL_ALARM_CLR_INT_ENA  VTSS_ES6514_BIT(11)

/** 
 * \brief
 * Interrupt enable for LOL_ALARM_ACT_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when LOL_ALARM_ACT_STICKY is active.
 * 1: Interrupt is asserted when LOL_ALARM_ACT_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_LOL_ALARM_ACT_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_LOL_ALARM_ACT_INT_ENA  VTSS_ES6514_BIT(10)

/** 
 * \brief
 * Interrupt enable for GST_ALARM_CLR_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when GST_ALARM_CLR_STICKY is active.
 * 1: Interrupt is asserted when GST_ALARM_CLR_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_GST_ALARM_CLR_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_GST_ALARM_CLR_INT_ENA  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * Interrupt enable for GST_ALARM_ACT_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when GST_ALARM_ACT_STICKY is active.
 * 1: Interrupt is asserted when GST_ALARM_ACT_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_GST_ALARM_ACT_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_GST_ALARM_ACT_INT_ENA  VTSS_ES6514_BIT(8)

/** 
 * \brief
 * Interrupt enable for SCM_ALARM_CLR_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when SCM_ALARM_CLR_STICKY is active.
 * 1: Interrupt is asserted when SCM_ALARM_CLR_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_SCM_ALARM_CLR_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_SCM_ALARM_CLR_INT_ENA  VTSS_ES6514_BIT(7)

/** 
 * \brief
 * Interrupt enable for SCM_ALARM_ACT_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when SCM_ALARM_ACT_STICKY is active.
 * 1: Interrupt is asserted when SCM_ALARM_ACT_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_SCM_ALARM_ACT_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_SCM_ALARM_ACT_INT_ENA  VTSS_ES6514_BIT(6)

/** 
 * \brief
 * Interrupt enable for CFM_ALARM_CLR_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when CFM_ALARM_CLR_STICKY is active.
 * 1: Interrupt is asserted when CFM_ALARM_CLR_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_CFM_ALARM_CLR_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_CFM_ALARM_CLR_INT_ENA  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * Interrupt enable for CFM_ALARM_ACT_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when CFM_ALARM_ACT_STICKY is active.
 * 1: Interrupt is asserted when CFM_ALARM_ACT_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_CFM_ALARM_ACT_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_CFM_ALARM_ACT_INT_ENA  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Interrupt enable for PFM_ALARM_CLR_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when PFM_ALARM_CLR_STICKY is active.
 * 1: Interrupt is asserted when PFM_ALARM_CLR_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_PFM_ALARM_CLR_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_PFM_ALARM_CLR_INT_ENA  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * Interrupt enable for PFM_ALARM_ACT_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when PFM_ALARM_ACT_STICKY is active.
 * 1: Interrupt is asserted when PFM_ALARM_ACT_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_PFM_ALARM_ACT_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_PFM_ALARM_ACT_INT_ENA  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * Interrupt enable for EXT_LOS_CLR_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when EXT_LOS_CLR_STICKY is active.
 * 1: Interrupt is asserted when EXT_LOS_CLR_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_EXT_LOS_CLR_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_EXT_LOS_CLR_INT_ENA  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Interrupt enable for EXT_LOS_ACT_STICKY.
 *
 * \details 
 * 0: Interrupt is not asserted when EXT_LOS_ACT_STICKY is active.
 * 1: Interrupt is asserted when EXT_LOS_ACT_STICKY is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG . IRQ_EXT_LOS_ACT_INT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_ENA_CFG_IRQ_EXT_LOS_ACT_INT_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief Qualifier alarm interrupt status register
 *
 * \details
 * Register: \a OMG_MAIN:OMG_IRQ:OMG_IRQ_ALARM_STATUS
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0xa + (ri))

/** 
 * \brief
 * Loss of lock status.
 *
 * \details 
 * 0: Loss of lock is not active.
 * 1: Loss of lock is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS . IRQ_LOL_ALARM_STATUS
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS_IRQ_LOL_ALARM_STATUS  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * Guard soak timer alarm status.
 *
 * \details 
 * 0: Guard soak timer alarm is not active.
 * 1: Guard soak timer alarm is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS . IRQ_GST_ALARM_STATUS
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS_IRQ_GST_ALARM_STATUS  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Single cycle monitor alarm status.
 *
 * \details 
 * 0: Single cycle monitor alarm is not active.
 * 1: Single cycle monitor alarm is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS . IRQ_SCM_ALARM_STATUS
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS_IRQ_SCM_ALARM_STATUS  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * Coarse frequency monitor alarm status.
 *
 * \details 
 * 0: Coarse frequency monitor alarm is not active.
 * 1: Coarse frequency monitor alarm is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS . IRQ_CFM_ALARM_STATUS
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS_IRQ_CFM_ALARM_STATUS  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * Precise frequency monitor alarm status.
 *
 * \details 
 * 0: Precise frequency monitor alarm is not active.
 * 1: Precise frequency monitor alarm is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS . IRQ_PFM_ALARM_STATUS
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS_IRQ_PFM_ALARM_STATUS  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * External loss of signal status.
 *
 * \details 
 * 0: External loss of signal is not active.
 * 1: External loss of signal is active.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS . IRQ_EXT_LOS_STATUS
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_STATUS_IRQ_EXT_LOS_STATUS  VTSS_ES6514_BIT(0)


/** 
 * \brief Qualifier alarm interrupt event register
 *
 * \details
 * Register: \a OMG_MAIN:OMG_IRQ:OMG_IRQ_ALARM_EVENT
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0xe + (ri))

/** 
 * \brief
 * Loss of lock inactive detected.
 *
 * \details 
 * 0: Loss of lock did not become inactive.
 * 1: Loss of lock became inactive.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_LOL_ALARM_CLR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_LOL_ALARM_CLR_STICKY  VTSS_ES6514_BIT(11)

/** 
 * \brief
 * Loss of lock active detected.
 *
 * \details 
 * 0: Loss of lock did not become active.
 * 1: Loss of lock became active.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_LOL_ALARM_ACT_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_LOL_ALARM_ACT_STICKY  VTSS_ES6514_BIT(10)

/** 
 * \brief
 * Guard soak timer alarm cleared detected.
 *
 * \details 
 * 0: Guard soak timer alarm has not been cleared.
 * 1: Guard soak timer alarm has been cleared.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_GST_ALARM_CLR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_GST_ALARM_CLR_STICKY  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * Guard soak timer alarm detected.
 *
 * \details 
 * 0: Guard soak timer alarm has not been seen.
 * 1: Guard soak timer alarm has been seen.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_GST_ALARM_ACT_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_GST_ALARM_ACT_STICKY  VTSS_ES6514_BIT(8)

/** 
 * \brief
 * Single cycle monitor alarm cleared detected.
 *
 * \details 
 * 0: Single cycle monitor alarm has not been cleared.
 * 1: Single cycle monitor alarm has been cleared.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_SCM_ALARM_CLR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_SCM_ALARM_CLR_STICKY  VTSS_ES6514_BIT(7)

/** 
 * \brief
 * Single cycle monitor alarm detected.
 *
 * \details 
 * 0: Single cycle monitor alarm has not been seen.
 * 1: Single cycle monitor alarm has been seen.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_SCM_ALARM_ACT_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_SCM_ALARM_ACT_STICKY  VTSS_ES6514_BIT(6)

/** 
 * \brief
 * Coarse frequency monitor alarm cleared detected.
 *
 * \details 
 * 0: Coarse frequency monitor alarm has not been cleared.
 * 1: Coarse frequency monitor alarm has been cleared.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_CFM_ALARM_CLR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_CFM_ALARM_CLR_STICKY  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * Coarse frequency monitor alarm detected.
 *
 * \details 
 * 0: Coarse frequency monitor alarm has not been seen.
 * 1: Coarse frequency monitor alarm has been seen.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_CFM_ALARM_ACT_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_CFM_ALARM_ACT_STICKY  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Precise frequency monitor alarm cleared detected.
 *
 * \details 
 * 0: Precise frequency monitor alarm has not been cleared.
 * 1: Precise frequency monitor alarm has been cleared.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_PFM_ALARM_CLR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_PFM_ALARM_CLR_STICKY  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * Precise frequency monitor alarm detected.
 *
 * \details 
 * 0: Precise frequency monitor alarm has not been seen.
 * 1: Precise frequency monitor alarm has been seen.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_PFM_ALARM_ACT_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_PFM_ALARM_ACT_STICKY  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * External loss of signal inactive detected.
 *
 * \details 
 * 0: External loss of signal has not been inactive.
 * 1: External loss of signal changed from active to inactive.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_EXT_LOS_CLR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_EXT_LOS_CLR_STICKY  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * External loss of signal active detected.
 *
 * \details 
 * 0: External loss of signal has not been active.
 * 1: External loss of signal changed from inactive to active.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT . IRQ_EXT_LOS_ACT_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_IRQ_OMG_IRQ_ALARM_EVENT_IRQ_EXT_LOS_ACT_STICKY  VTSS_ES6514_BIT(0)

/**
 * Register Group: \a OMG_MAIN:OMG_QUAL
 *
 * Qualifier configuration and status register set
 */


/** 
 * \brief Common qualifier configuration register
 *
 * \details
 * Configuration register for common settings in the qualifier block
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_COMMON_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_COMMON_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x12 + (ri))

/** 
 * \brief
 * Invert polarity of external loss-of-signal (LOS) input
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_COMMON_CFG . QUAL_EXT_LOS_INV
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_COMMON_CFG_QUAL_EXT_LOS_INV  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * Software reset of qualifier (QUAL_ENA and OMG_MAIN_CFG.SW_ENA must be 1
 * to be effective)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_COMMON_CFG . QUAL_SW_RST
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_COMMON_CFG_QUAL_SW_RST  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Enable qualifier logic
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_COMMON_CFG . QUAL_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_COMMON_CFG_QUAL_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief SCM configuration register
 *
 * \details
 * Configuration register for the Single Cycle Monitor (SCM). Note: When
 * the external frequency or interface width has changed, the clock
 * recovery process has to be restarted. This can be accomplished by either
 * toggling the QUAL_SCM_AUTOMODE_ENA bit or asserting/deasserting
 * OMG_QUAL_COMMON_CFG.QUAL_SW_RST while OMG_MAIN_CFG.SW_ENA and
 * OMG_QUAL_COMMON_CFG.QUAL_ENA are both kept at 1.
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_SCM_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x16 + (ri))

/** 
 * \brief
 * Spike-filter (filtering out single bit spikes) disable
 *
 * \details 
 * 0: Enable spike filter
 * 1: Disable spike filter
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG . QUAL_SCM_SPKFLT_DIS
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_SPKFLT_DIS  VTSS_ES6514_BIT(29)

/** 
 * \brief
 * Check against recovered clock periods
 *
 * \details 
 * 0: Check against values given in QUAL_SCM_OBJC_CLK_PERIOD
 * 1: Check against recovered clock periods
 * A 0 to 1 transition restarts clock period recovery process
 * Note: The clock recovery process must be manually restarted
 * when the clock frequency and/or the interface width has changed.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG . QUAL_SCM_AUTOMODE_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_AUTOMODE_ENA  VTSS_ES6514_BIT(28)

/** 
 * \brief
 * Select measured period/phase to stored in QUAL_SCM_MEAS_CLK_PERIOD
 *
 * \details 
 * 0: Average period
 * 1: Average length of high phase
 * 2: Average length of low phase
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG . QUAL_SCM_MEAS_CLK_PER_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_MEAS_CLK_PER_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_MEAS_CLK_PER_SEL     VTSS_ES6514_ENCODE_BITMASK(26,2)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_MEAS_CLK_PER_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Objective clock period (in bits), measured clock periods differing from
 * this value will cause an SCM alarm
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG . QUAL_SCM_OBJC_CLK_PERIOD
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_OBJC_CLK_PERIOD(x)  VTSS_ES6514_ENCODE_BITFIELD(x,12,14)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_OBJC_CLK_PERIOD     VTSS_ES6514_ENCODE_BITMASK(12,14)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_OBJC_CLK_PERIOD(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,12,14)

/** 
 * \brief
 * Maximum tolerated missing clock edges
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG . QUAL_SCM_MAX_MIS_CLK_EDGE
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_MAX_MIS_CLK_EDGE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_MAX_MIS_CLK_EDGE     VTSS_ES6514_ENCODE_BITMASK(10,2)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_MAX_MIS_CLK_EDGE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Tolerated phase length uncertainty (in 1/16 steps)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG . QUAL_SCM_PHASE_UNCERT
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_PHASE_UNCERT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_PHASE_UNCERT     VTSS_ES6514_ENCODE_BITMASK(6,4)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_PHASE_UNCERT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,6,4)

/** 
 * \brief
 * Number N of learn periods before SCM becomes active
 *
 * \details 
 * N=2^(5+QUAL_SCM_NUM_LRN_PERIODS)
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG . QUAL_SCM_NUM_LRN_PERIODS
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_NUM_LRN_PERIODS(x)  VTSS_ES6514_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_NUM_LRN_PERIODS     VTSS_ES6514_ENCODE_BITMASK(3,3)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_NUM_LRN_PERIODS(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Interface width of parallel rx date i/f
 *
 * \details 
 * 0: 8-bit
 * 1: 10-bit
 * 2: 16-bit
 * 3: 20-bit
 * 4: 32-bit
 * 5: 40-bit
 * 6-7: Reserved
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG . QUAL_SCM_IFW
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_IFW(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_IFW     VTSS_ES6514_ENCODE_BITMASK(0,3)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_CFG_QUAL_SCM_IFW(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief PFM check configuration register
 *
 * \details
 * Configuration register for the Precise Frequency monitor (PFM) checker.
 * PFM alarm becomes active when the following relation is violated:
 * QUAL_CPFM_PF_MAX - QUAL_CPFM_PF_HYST < PFM < QUAL_CPFM_PF_MAX +
 * QUAL_CPFM_PF_HYST where PFM is the filtered resulting delta-f value.
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_PFM_CHECK_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x1a + (ri))

/** 
 * \brief
 * Maximum tolerated PFM deviation
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG . QUAL_CPFM_PF_MAX
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG_QUAL_CPFM_PF_MAX(x)  VTSS_ES6514_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG_QUAL_CPFM_PF_MAX     VTSS_ES6514_ENCODE_BITMASK(12,20)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG_QUAL_CPFM_PF_MAX(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,12,20)

/** 
 * \brief
 * Hysteresis for PFM deviation.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG . QUAL_CPFM_PF_HYST
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG_QUAL_CPFM_PF_HYST(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG_QUAL_CPFM_PF_HYST     VTSS_ES6514_ENCODE_BITMASK(0,12)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_PFM_CHECK_CFG_QUAL_CPFM_PF_HYST(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief CFM check configuration register
 *
 * \details
 * Configuration register for the Coarse Frequency monitor (CFM) checker.
 * CFM alarm becomes active when the following relation is violated:
 * QUAL_CPFM_CF_MAX - QUAL_CPFM_CF_HYST < CFM < QUAL_CPFM_CF_MAX +
 * QUAL_CPFM_CF_HYST where CFM is the resulting delta-f value.
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_CFM_CHECK_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x1e + (ri))

/** 
 * \brief
 * Maximum tolerated CFM deviation
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG . QUAL_CPFM_CF_MAX
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG_QUAL_CPFM_CF_MAX(x)  VTSS_ES6514_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG_QUAL_CPFM_CF_MAX     VTSS_ES6514_ENCODE_BITMASK(12,20)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG_QUAL_CPFM_CF_MAX(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,12,20)

/** 
 * \brief
 * Hysteresis for CFM deviation.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG . QUAL_CPFM_CF_HYST
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG_QUAL_CPFM_CF_HYST(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG_QUAL_CPFM_CF_HYST     VTSS_ES6514_ENCODE_BITMASK(0,12)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CFM_CHECK_CFG_QUAL_CPFM_CF_HYST(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief CPFM filter configuration register
 *
 * \details
 * Configuration register for the filter blocks of the Coarse and Precise
 * Frequency monitor (CFM and PFM). The cut-off frequency for the
 * integrator 1 and delta-F low-pass filters (i1_lpf and df_lpf) calculates
 * to f_c = 3.11 MHz * LPF_FILTCOEF / 2**LPF_FILTSHFT. The recovered
 * integrator 1 (I1) value can be scaled with a programmable factor c_i1 =
 * I1_SCALECOEF / 2**(4+I1_SCALESHFT).
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_CPFM_FILTER_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x22 + (ri))

/** 
 * \brief
 * Programmable multiplicator for I1
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG . QUAL_CPFM_I1_SCALECOEF
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_SCALECOEF(x)  VTSS_ES6514_ENCODE_BITFIELD(x,22,10)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_SCALECOEF     VTSS_ES6514_ENCODE_BITMASK(22,10)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_SCALECOEF(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,22,10)

/** 
 * \brief
 * Programmable shift number for I1 (max: 7)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG . QUAL_CPFM_I1_SCALESHFT
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_SCALESHFT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_SCALESHFT     VTSS_ES6514_ENCODE_BITMASK(19,3)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_SCALESHFT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * Programmable multiplicator for I1-LPF
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG . QUAL_CPFM_I1_LPF_FILTCOEF
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_LPF_FILTCOEF(x)  VTSS_ES6514_ENCODE_BITFIELD(x,15,4)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_LPF_FILTCOEF     VTSS_ES6514_ENCODE_BITMASK(15,4)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_LPF_FILTCOEF(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,15,4)

/** 
 * \brief
 * Programmable shift number for I1-LPF (max: 16)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG . QUAL_CPFM_I1_LPF_FILTSHFT
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_LPF_FILTSHFT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_LPF_FILTSHFT     VTSS_ES6514_ENCODE_BITMASK(10,5)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_I1_LPF_FILTSHFT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,5)

/** 
 * \brief
 * Programmable multiplicator for delta-f-LPF
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG . QUAL_CPFM_DF_LPF_FILTCOEF
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_DF_LPF_FILTCOEF(x)  VTSS_ES6514_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_DF_LPF_FILTCOEF     VTSS_ES6514_ENCODE_BITMASK(5,4)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_DF_LPF_FILTCOEF(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Programmable shift number for delta-f-LPF (max: 20)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG . QUAL_CPFM_DF_LPF_FILTSHFT
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_DF_LPF_FILTSHFT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_DF_LPF_FILTSHFT     VTSS_ES6514_ENCODE_BITMASK(0,5)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_FILTER_CFG_QUAL_CPFM_DF_LPF_FILTSHFT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CPFM I2 replica configuration register
 *
 * \details
 * Configuration register for I2 replica in the Coarse and Precise
 * Frequency monitor (CFM and PFM)
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_CPFM_I2_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x26 + (ri))

/** 
 * \brief
 * Clear wrap detection status bit
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG . QUAL_CPFM_WRAP_CLR
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG_QUAL_CPFM_WRAP_CLR  VTSS_ES6514_BIT(7)

/** 
 * \brief
 * Inhibit wrapping of I2
 *
 * \details 
 * 0: I2 wrapping mode
 * 1: I2 saturation mode
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG . QUAL_CPFM_WRAP_INHIBIT
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG_QUAL_CPFM_WRAP_INHIBIT  VTSS_ES6514_BIT(6)

/** 
 * \brief
 * Manual setting of fsel (last fsel change wins)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG . QUAL_CPFM_SET_FSEL
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG_QUAL_CPFM_SET_FSEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG_QUAL_CPFM_SET_FSEL     VTSS_ES6514_ENCODE_BITMASK(0,6)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_CFG_QUAL_CPFM_SET_FSEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief GST timing configuration register 0
 *
 * \details
 * Guard Soak Timer (GST) timing configuration register 0.
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_GST_TIM_CFG0
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x2a + (ri))

/** 
 * \brief
 * GST decrement. Qualification time is T = 3.2ns * QUAL_GST_QUAL_PREDIV *
 * QUAL_GST_QUAL_THRESHOLD / QUAL_GST_QUAL_DECR
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0 . QUAL_GST_QUAL_DECR
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_DECR(x)  VTSS_ES6514_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_DECR     VTSS_ES6514_ENCODE_BITMASK(24,8)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_DECR(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * GST increment. Disqualification time is T = 3.2ns * QUAL_GST_QUAL_PREDIV
 * * QUAL_GST_QUAL_THRESHOLD / QUAL_GST_QUAL_INCR
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0 . QUAL_GST_QUAL_INCR
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_INCR(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_INCR     VTSS_ES6514_ENCODE_BITMASK(16,8)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_INCR(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * GST predivider, divides 312.5MHz operating clock
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0 . QUAL_GST_QUAL_PREDIV
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_PREDIV(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_PREDIV     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG0_QUAL_GST_QUAL_PREDIV(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief GST timing configuration register 1
 *
 * \details
 * Guard Soak Timer (GST) timing configuration register 1. It has to be
 * made sure that QUAL_GST_QUAL_DECR and QUAL_GST_QUAL_INCR is lower than
 * QUAL_GST_QUAL_THRESHOLD.
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_GST_TIM_CFG1
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG1(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x2e + (ri))

/** 
 * \brief
 * GST qualification threshold (weighting qualification and
 * disqualification times)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG1 . QUAL_GST_QUAL_THRESHOLD
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG1_QUAL_GST_QUAL_THRESHOLD(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,25)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG1_QUAL_GST_QUAL_THRESHOLD     VTSS_ES6514_ENCODE_BITMASK(0,25)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_TIM_CFG1_QUAL_GST_QUAL_THRESHOLD(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,25)


/** 
 * \brief GST alarm configuration register
 *
 * \details
 * Guard Soak Timer (GST) alarm configuration register. This register
 * defines alarms be processed in the guard soak process.
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_GST_ALARM_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x32 + (ri))

/** 
 * \brief
 * Loss of lock alarm enable for GST processing
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG . QUAL_GST_LOL_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG_QUAL_GST_LOL_ALARM_ENA  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * SCM alarm enable for GST processing
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG . QUAL_GST_SCM_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG_QUAL_GST_SCM_ALARM_ENA  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * CFM alarm enable for GST processing
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG . QUAL_GST_CFM_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG_QUAL_GST_CFM_ALARM_ENA  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * PFM alarm enable for GST processing
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG . QUAL_GST_PFM_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG_QUAL_GST_PFM_ALARM_ENA  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * External LOS alarm enable for GST processing
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG . QUAL_GST_LOS_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_GST_ALARM_CFG_QUAL_GST_LOS_ALARM_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief Alarm configuration register
 *
 * \details
 * Alarm configuration register. This register defines the alarms visible
 * at an external port (GPIO) and visible at the attached controller block.
 * The attached controller will only react on alarms enabled here.
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_ALARM_CFG
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x36 + (ri))

/** 
 * \brief
 * Loss of lock alarm enable for GPIO port
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_LOL_GPIO_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_LOL_GPIO_ALARM_ENA  VTSS_ES6514_BIT(15)

/** 
 * \brief
 * GST alarm enable for GPIO port
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_GST_GPIO_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_GST_GPIO_ALARM_ENA  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * SCM alarm enable for GPIO port
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_SCM_GPIO_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_SCM_GPIO_ALARM_ENA  VTSS_ES6514_BIT(13)

/** 
 * \brief
 * CFM alarm enable for GPIO port
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_CFM_GPIO_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_CFM_GPIO_ALARM_ENA  VTSS_ES6514_BIT(12)

/** 
 * \brief
 * PFM alarm enable for GPIO port
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_PFM_GPIO_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_PFM_GPIO_ALARM_ENA  VTSS_ES6514_BIT(11)

/** 
 * \brief
 * External LOS alarm enable for GPIO port
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_LOS_GPIO_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_LOS_GPIO_ALARM_ENA  VTSS_ES6514_BIT(10)

/** 
 * \brief
 * Loss of lock alarm enable for control logic (EEC)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_LOL_CTRL_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_LOL_CTRL_ALARM_ENA  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * GST alarm enable for control logic (EEC)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_GST_CTRL_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_GST_CTRL_ALARM_ENA  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * SCM alarm enable for control logic (EEC)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_SCM_CTRL_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_SCM_CTRL_ALARM_ENA  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * CFM alarm enable for control logic (EEC)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_CFM_CTRL_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_CFM_CTRL_ALARM_ENA  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * PFM alarm enable for control logic (EEC)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_PFM_CTRL_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_PFM_CTRL_ALARM_ENA  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * External LOS alarm enable for control logic (EEC)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG . QUAL_LOS_CTRL_ALARM_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_ALARM_CFG_QUAL_LOS_CTRL_ALARM_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief SCM status register
 *
 * \details
 * Status register for the Single Cycle Monitor (SCM)
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_SCM_STAT
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x3a + (ri))

/** 
 * \brief
 * Noise error detected (too many edges within one rx_data word)
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT . QUAL_SCM_NOISE_ERR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT_QUAL_SCM_NOISE_ERR_STICKY  VTSS_ES6514_BIT(18)

/** 
 * \brief
 * Missing clock edge error detected
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT . QUAL_SCM_MIS_CLK_ERR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT_QUAL_SCM_MIS_CLK_ERR_STICKY  VTSS_ES6514_BIT(17)

/** 
 * \brief
 * Duty cycle error discovered
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT . QUAL_SCM_DUTY_CYCLE_ERR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT_QUAL_SCM_DUTY_CYCLE_ERR_STICKY  VTSS_ES6514_BIT(16)

/** 
 * \brief
 * Measured clock period matches objective clock period
 *
 * \details 
 * 0: No match
 * 1 Match
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT . QUAL_SCM_MEAS_CLK_MATCH
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT_QUAL_SCM_MEAS_CLK_MATCH  VTSS_ES6514_BIT(15)

/** 
 * \brief
 * Clock period successfully recovered
 *
 * \details 
 * 0: Not recovered
 * 1: Recovered
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT . QUAL_SCM_MEAS_LOCK
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT_QUAL_SCM_MEAS_LOCK  VTSS_ES6514_BIT(14)

/** 
 * \brief
 * Measured clock period (in bits)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT . QUAL_SCM_MEAS_CLK_PERIOD
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT_QUAL_SCM_MEAS_CLK_PERIOD(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT_QUAL_SCM_MEAS_CLK_PERIOD     VTSS_ES6514_ENCODE_BITMASK(0,14)
#define  VTSS_X_OMG_MAIN_OMG_QUAL_OMG_QUAL_SCM_STAT_QUAL_SCM_MEAS_CLK_PERIOD(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,14)


/** 
 * \brief CPFM I2 replica status register
 *
 * \details
 * Status register of the I2 replica of Coarse and Precise Frequency
 * Monitor (CFM and PFM)
 *
 * Register: \a OMG_MAIN:OMG_QUAL:OMG_QUAL_CPFM_I2_STAT
 *
 * @param ri Replicator: x_NUM_OF_QUAL_BLOCKS (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_STAT(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x3e + (ri))

/** 
 * \brief
 * I2 (sync ctrl bus) protocol error detected
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_STAT . QUAL_CPFM_PROTOCOL_ERR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_STAT_QUAL_CPFM_PROTOCOL_ERR_STICKY  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * I2 wrapping event detected
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_STAT . QUAL_CPFM_WRAP_DET_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_QUAL_OMG_QUAL_CPFM_I2_STAT_QUAL_CPFM_WRAP_DET_STICKY  VTSS_ES6514_BIT(0)

/**
 * Register Group: \a OMG_MAIN:OMG_CTRL
 *
 * Controller configuration and status registers
 */


/** 
 * \brief Main controller configuration register
 *
 * \details
 * Main controller configuration register
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_MAIN_CFG
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x42 + (ri))

/** 
 * \brief
 * Define periods of OMG-Ctrl timer.
 *
 * \details 
 * 0: 1us/1ms/1s (mission mode)
 * 1: 100ns/10us/1ms
 * 2: 100ns/3.2us/100us
 * 3: 100ns/1us/10us
 *
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG . CTRL_TIMER_TEST
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_TIMER_TEST(x)  VTSS_ES6514_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_TIMER_TEST     VTSS_ES6514_ENCODE_BITMASK(6,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_TIMER_TEST(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Automatic switch back to higher prioritized valid reference input.
 *
 * \details 
 * 0: Disable automatic switch-back
 * 1: Enable automatic switch-back
 *
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG . CTRL_AUTO_SWITCH_BACK
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_AUTO_SWITCH_BACK  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Controller operation mode.
 *
 * \details 
 * 0: DISABLED (stop operation)
 * 1: FRC_FREE_RUN (force controller into free-run mode)
 * 2: FRC_HO_MODE (force controller into hold-over mode)
 * 3: AUTO (controller in automatic mode)
 *
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG . CTRL_OP_MODE
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_OP_MODE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_OP_MODE     VTSS_ES6514_ENCODE_BITMASK(2,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_OP_MODE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Software reset of controller (CTRL_ENA must be 1 to be effective).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG . CTRL_SW_RST
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_SW_RST  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Enable controller logic.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG . CTRL_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_MAIN_CFG_CTRL_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief Reference clock selection register
 *
 * \details
 * Reference clock input selection register. The available clock sources
 * must always be programmed from highest to lowest priority.
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_REFSEL
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x44 + (ri))

/** 
 * \brief
 * Reference input port with lowest priority.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL . CTRL_REFSEL_PRIO3_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO3_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO3_SEL     VTSS_ES6514_ENCODE_BITMASK(10,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO3_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Enable reference input port with lowest priority.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL . CTRL_REFSEL_PRIO3_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO3_ENA  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * Reference input port with mid-low priority.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL . CTRL_REFSEL_PRIO2_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO2_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO2_SEL     VTSS_ES6514_ENCODE_BITMASK(7,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO2_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,7,2)

/** 
 * \brief
 * Enable reference input port with mid-low priority.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL . CTRL_REFSEL_PRIO2_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO2_ENA  VTSS_ES6514_BIT(6)

/** 
 * \brief
 * Reference input port with mid-high priority.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL . CTRL_REFSEL_PRIO1_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO1_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO1_SEL     VTSS_ES6514_ENCODE_BITMASK(4,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO1_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Enable reference input port with mid-high priority.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL . CTRL_REFSEL_PRIO1_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO1_ENA  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * Reference input port with highest priority. This is the master reference
 * input.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL . CTRL_REFSEL_PRIO0_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO0_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO0_SEL     VTSS_ES6514_ENCODE_BITMASK(1,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO0_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Enable reference input port with highest priority. Must be set for
 * proper function.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL . CTRL_REFSEL_PRIO0_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_REFSEL_CTRL_REFSEL_PRIO0_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief Controller timing cfg register 0
 *
 * \details
 * Controller timing configuration register 0
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_TIMING_CFG0
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x46 + (ri))

/** 
 * \brief
 * Initial qualification time (in sec, typically 0-720s, max 1023s).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0 . CTRL_INI_QUAL_TIME
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0_CTRL_INI_QUAL_TIME(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0_CTRL_INI_QUAL_TIME     VTSS_ES6514_ENCODE_BITMASK(16,10)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0_CTRL_INI_QUAL_TIME(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Hold-off time (in ms, typically 50ms-10s, max 65.535s).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0 . CTRL_HOLD_OFF_TIME
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0_CTRL_HOLD_OFF_TIME(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0_CTRL_HOLD_OFF_TIME     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG0_CTRL_HOLD_OFF_TIME(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Controller timing cfg register 1
 *
 * \details
 * Controller timing configuration register 1
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_TIMING_CFG1
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x48 + (ri))

/** 
 * \brief
 * Wait-to-restore time (in sec, typically 0-720s, max 1023s).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1 . CTRL_WAIT_TO_RESTORE_TIME
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1_CTRL_WAIT_TO_RESTORE_TIME(x)  VTSS_ES6514_ENCODE_BITFIELD(x,17,10)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1_CTRL_WAIT_TO_RESTORE_TIME     VTSS_ES6514_ENCODE_BITMASK(17,10)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1_CTRL_WAIT_TO_RESTORE_TIME(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,17,10)

/** 
 * \brief
 * Hold-over time (in ms, typically 0-84.6s, max 131.071s).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1 . CTRL_HOLD_OVER_TIME
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1_CTRL_HOLD_OVER_TIME(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,17)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1_CTRL_HOLD_OVER_TIME     VTSS_ES6514_ENCODE_BITMASK(0,17)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_TIMING_CFG1_CTRL_HOLD_OVER_TIME(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,17)


/** 
 * \brief Holdover stack cfg register
 *
 * \details
 * Hold-over stack configuration register (ho = hold-over). The cut-off
 * frequency of the hold-over low-pass-filter with decimation is f_cut =
 * 3.11MHz * CTRL_HO_LPF_FILTCOEF /
 * 2**(5+CTRL_HO_LPF_FILTSHFT+CTRL_HO_LPF_DECIMPWR). F(N) = F(N-1) * (1 -
 * CTRL_HO_FILT_CFG/4) + F(N) * CTRL_HO_FILT_CFG/4
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_HO_STACK_CFG
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x4a + (ri))

/** 
 * \brief
 * HO-stack read address, HO-Stack content is read from this address (max
 * address is 11).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_RD_ADDR
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_RD_ADDR(x)  VTSS_ES6514_ENCODE_BITFIELD(x,23,4)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_RD_ADDR     VTSS_ES6514_ENCODE_BITMASK(23,4)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_RD_ADDR(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,23,4)

/** 
 * \brief
 * HO-stack read strobe, HO-Stack content is read on a rising edge of this
 * bit-group.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_RD_STRB_ONE_SHOT
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_RD_STRB_ONE_SHOT  VTSS_ES6514_BIT(22)

/** 
 * \brief
 * Enable averaging of hold-over values before storing in next level of
 * HO-stack
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_AVG_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_AVG_CFG  VTSS_ES6514_BIT(21)

/** 
 * \brief
 * Define filtering of hold-over values before storing in next level of
 * HO-stack. From stage N-1 to stage N the value be stored as calculated
 * per HO(N) = HO(N-1) * (1 - CTRL_HO_FILT_CFG/4) + HO(N) *
 * CTRL_HO_FILT_CFG/4
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_FILT_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_FILT_CFG(x)  VTSS_ES6514_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_FILT_CFG     VTSS_ES6514_ENCODE_BITMASK(19,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_FILT_CFG(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,19,2)

/** 
 * \brief
 * HO-low-pass filter decimation 2**(5+CTRL_HO_LPF_DECIMPWR).
 *
 * \details 
 * 0: 32
 * 1: 64
 * 2: 128
 * 3: 256
 * ...
 * 7: 4096
 *
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_LPF_DECIMPWR
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_DECIMPWR(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_DECIMPWR     VTSS_ES6514_ENCODE_BITMASK(16,3)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_DECIMPWR(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * HO-low-pass filter multiply value.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_LPF_FILTCOEF
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_FILTCOEF(x)  VTSS_ES6514_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_FILTCOEF     VTSS_ES6514_ENCODE_BITMASK(12,4)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_FILTCOEF(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * HO-low-pass filter shift value.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_LPF_FILTSHFT
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_FILTSHFT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_FILTSHFT     VTSS_ES6514_ENCODE_BITMASK(8,4)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_LPF_FILTSHFT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Minimum fill level before ho-stack considered full. First when minimum
 * fill level is reached, hold-over state may be entered.
 * (CTRL_HO_MIN_FILL_LVL must be identical to CTRL_HO_SEL in mission mode,
 * except when CTRL_HO_SEL=15).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_MIN_FILL_LVL
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_MIN_FILL_LVL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_MIN_FILL_LVL     VTSS_ES6514_ENCODE_BITMASK(4,4)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_MIN_FILL_LVL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Select ho-value to take in hold-over state.
 *
 * \details 
 * 0-11: Select ho-stack entry 0-11
 * 12-14: Reserved
 * 15: Select value stored in OMG_CTRL_DF_HOM0/1
 *
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG . CTRL_HO_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_SEL     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_CFG_CTRL_HO_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Delta_f cfg register 0 for free run mode
 *
 * \details
 * Configuration register 0 for frequency offset (delta-f) in free-run
 * mode. Coding of 36-bit DF_FRM value: F_offset = DF_FRM / (7 * 2**32) *
 * 1e6/1024 ppm. The max. value for DF_FRM is 7 * 2**32.
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_DF_FRM0
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_FRM0(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x4c + (ri))


/** 
 * \brief Delta_f cfg register 1 for free run mode
 *
 * \details
 * Configuration register 1 for frequency offset (delta-f) in free-run
 * mode.
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_DF_FRM1
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_FRM1(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x4e + (ri))

/** 
 * \brief
 * Make new delta-f value valid (operational).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_FRM1 . DF_FRM_UPDATE_ONE_SHOT
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_FRM1_DF_FRM_UPDATE_ONE_SHOT  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Delta-f output in free-run mode (upper 4 bits).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_FRM1 . DF_FRM_HIGH
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_FRM1_DF_FRM_HIGH(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_FRM1_DF_FRM_HIGH     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_FRM1_DF_FRM_HIGH(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Delta_f cfg register 0 for holdover mode
 *
 * \details
 * Configuration register 0 for frequency offset (delta-f) in hold-over
 * mode. The value in this register is used as an alternative to the
 * content in the hold-over stack. Requires CTRL_HO_SEL = 0xF be set.
 * Coding of 36-bit DF_HOF value: F_offset = DF_HOF / (7 * 2**32) *
 * 1e6/1024 ppm. The max. value for DF_HOF is 7 * 2**32.
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_DF_HOM0
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_HOM0(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x50 + (ri))


/** 
 * \brief Delta_f cfg register 1 for holdover mode
 *
 * \details
 * Configuration register 1 for frequency offset (delta-f) in hold-over
 * mode. The value in this register is used as an alternative to the
 * content in the hold-over stack. Requires CTRL_HO_SEL = 0xF be set.
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_DF_HOM1
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_HOM1(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x52 + (ri))

/** 
 * \brief
 * Make new delta-f value valid (operational).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_HOM1 . DF_HOM_UPDATE_ONE_SHOT
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_HOM1_DF_HOM_UPDATE_ONE_SHOT  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Alternative delta-f output in hold-over mode (upper 4 bits; CTRL_HO_SEL
 * = 0xF required).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_HOM1 . DF_HOM_HIGH
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_HOM1_DF_HOM_HIGH(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_HOM1_DF_HOM_HIGH     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_DF_HOM1_DF_HOM_HIGH(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Hold-over stack read register 0
 *
 * \details
 * Hold-over stack read result (lower 32 bits). Data are internally read on
 * a rising edge of CTRL_HO_RD_STRB.
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_HO_STACK_STAT0
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_STAT0(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x54 + (ri))


/** 
 * \brief Hold-over stack read register 1
 *
 * \details
 * Hold-over stack read result (upper 4 bits). Data are internally read on
 * a rising edge of CTRL_HO_RD_STRB.
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_HO_STACK_STAT1
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_STAT1(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x56 + (ri))

/** 
 * \brief
 * HO-stack read data, result of HO-stack read operation (upper 4 bits).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_STAT1 . CTRL_HO_RD_DATA_HIGH
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_STAT1_CTRL_HO_RD_DATA_HIGH(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_STAT1_CTRL_HO_RD_DATA_HIGH     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_HO_STACK_STAT1_CTRL_HO_RD_DATA_HIGH(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Common controller status register
 *
 * \details
 * Common controller status and observe register
 *
 * Register: \a OMG_MAIN:OMG_CTRL:OMG_CTRL_STAT
 *
 * @param ri Replicator: x_NUM_OF_CTRL_BLOCKS (??), 0-1
 */
#define VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x58 + (ri))

/** 
 * \brief
 * Hold-over stack write toggle, toggles whenever the HO-stack has been
 * updated (useful for consistent HO-stack read-outs).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT . CTRL_HO_WR_TOGGLE
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_HO_WR_TOGGLE  VTSS_ES6514_BIT(8)

/** 
 * \brief
 * Current state of central control FSM.
 *
 * \details 
 * 0: Forced free-run mode
 * 1: Select reference in free-run mode (fall-through state)
 * 2: Free-run mode
 * 3: Locked mode - acquiring hold-over values
 * 4: Locked mode - hold-over value available
 * 5: Hold-over mode
 * 6: Select new reference in hold-over mode (fall-through state)
 * 7: Forced hold-over mode
 *
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT . CTRL_EEC_STATE
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_EEC_STATE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_EEC_STATE     VTSS_ES6514_ENCODE_BITMASK(5,3)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_EEC_STATE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Hold-over stack filled indication. Bit becomes active when HO-stack is
 * filled up to CTRL_HO_MIN_FILL_LVL level.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT . CTRL_HO_FILLED
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_HO_FILLED  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Input source selection.
 *
 * \details 
 * 0: Delta-f taken from port 0
 * ...
 * 3: Delta-f taken from port 3
 *
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT . CTRL_INP_SRC_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_INP_SRC_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_INP_SRC_SEL     VTSS_ES6514_ENCODE_BITMASK(2,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_INP_SRC_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Output source selection.
 *
 * \details 
 * 0: Delta-f taken from CTRL_DELTA_F_FRM (in free-run mode)
 * 1: Delta-f taken from selected reference input
 * 2: Delta-f taken from Hold-over stack
 *
 * Field: ::VTSS_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT . CTRL_EEC_SRC_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_EEC_SRC_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_EEC_SRC_SEL     VTSS_ES6514_ENCODE_BITMASK(0,2)
#define  VTSS_X_OMG_MAIN_OMG_CTRL_OMG_CTRL_STAT_CTRL_EEC_SRC_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a OMG_MAIN:OMG_PSG
 *
 * Phase Shift Generator Configuration Register set
 */


/** 
 * \brief Main Phase Shift Generator Configuration Register
 *
 * \details
 * Register: \a OMG_MAIN:OMG_PSG:OMG_PS_GEN_MAIN_CFG
 */
#define VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x5a)

/** 
 * \brief
 * Configured (unsigned) frequency offset or number of
 * increments/decrements for the sync control mechanism
 *
 * \details 
 * Mode A:
 *   +/-2^N is applied to the filter stage (per enabled lane) where +/- is
 * chosen with bit 'freq_offs_sign_cfg' and N = psg_freq_offs_val_cfg;
 * N(max) = 34
 * Mode B:
 *   2^N increments/decrements are applied to the integrator2 input
 * directly, where N = freq_offs_val_cfg and N(max) = 19
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG . PSG_FREQ_OFFS_VAL_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_FREQ_OFFS_VAL_CFG(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_FREQ_OFFS_VAL_CFG     VTSS_ES6514_ENCODE_BITMASK(10,6)
#define  VTSS_X_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_FREQ_OFFS_VAL_CFG(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Sign bit of the configured frequency offset or direction bit for the
 * sync control mechanism
 *
 * \details 
 * Mode A:
 *   0: The frequency offset is applied as positive value
 *   1: The frequency offset is applied as negative value
 * Mode B:
 *   0: The sync control ramp starts with increments, i.e. the phase shift
 * is increasing
 *   1: The sync control ramp starts with decrements, i.e. the phase shift
 * is decreasing
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG . PSG_FREQ_OFFS_SIGN_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_FREQ_OFFS_SIGN_CFG  VTSS_ES6514_BIT(9)

/** 
 * \brief
 * Lane selection; none to all lanes can be chosen in parallel
 *
 * \details 
 * Each bit enables one lane if set to 1, where bit 0 (LSB) enables lane 0,
 * etc.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG . PSG_LANE_ENA_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_LANE_ENA_CFG(x)  VTSS_ES6514_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_LANE_ENA_CFG     VTSS_ES6514_ENCODE_BITMASK(5,4)
#define  VTSS_X_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_LANE_ENA_CFG(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Phase shift generator mode
 *
 * \details 
 * 0: Mode A; The phase shift generator enables the frequency offset
 * output, i.e. the input to the filter stage
 * 1: Mode B; The phase shift generator activates the sync-control output,
 * i.e. the input to the integrator2 directly
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG . PSG_MODE_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_MODE_CFG  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Phase shift generator single shot mode
 *
 * \details 
 * 0: Off
 * 1: single shot; a transition to 1 enables the phase shift generator for
 * 1 time
 * Hardware resets this bit after finishing the phase shift manupulation
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG . PSG_ONE_SHOT
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_ONE_SHOT  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * Phase shift generator toggle mode
 *
 * \details 
 * 0: Off
 * 1: toggling; the phase shift generator toggles between being active and
 * inactive
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG . PSG_TOGGLE_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_TOGGLE_CFG  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * Software reset of phase shift generator (PSG_ENA must be 1 to be
 * effective)
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG . PSG_SW_RST
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_SW_RST  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Enable phase shift generator logic
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG . PSG_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_CFG_PSG_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief Phase Shift Generator Timer Configuration Register
 *
 * \details
 * Timer configurations must always be done prior to activating a phase
 * shift generator mode and must not be changed before the mode is
 * deactivated again.
 *
 * Register: \a OMG_MAIN:OMG_PSG:OMG_PS_GEN_TIMER_CFG
 */
#define VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x5b)

/** 
 * \brief
 * Timer value for the delay (number of clock cycles 'S') between 2
 * consecutive increments or decrements (Mode B)
 *
 * \details 
 * 'S' = 2^(N+1) where N = psg_i2_ramp_slope_cfg
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG . PSG_I2_RAMP_SLOPE_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_I2_RAMP_SLOPE_CFG(x)  VTSS_ES6514_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_I2_RAMP_SLOPE_CFG     VTSS_ES6514_ENCODE_BITMASK(21,3)
#define  VTSS_X_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_I2_RAMP_SLOPE_CFG(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,21,3)

/** 
 * \brief
 * Selects 1 of 21 enable bits which are used to enable the phase shift
 * timer. Each bit is set active for one of 2^N clock cycles. Note that
 * this selection also influences the time T between 'indicating a
 * sync-control access' and 'starting the sync-control events', when in
 * mode B, so that other modules' synchronization attempt is suppressed.
 * For values < 7 time T = 64 ( plus the uncertainty between the SW access
 * and the heart-beat signal period); for values > 6 time T = 1 heart-beat
 * cycle ( plus the uncertainty between the SW access and the heart-beat
 * signal period)
 *
 * \details 
 * enable is active every (2^N)'th clock cycle with N =
 * psg_heart_beat_sel_cfg and N(max) = 20
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG . PSG_HEART_BEAT_SEL_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_HEART_BEAT_SEL_CFG(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_HEART_BEAT_SEL_CFG     VTSS_ES6514_ENCODE_BITMASK(16,5)
#define  VTSS_X_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_HEART_BEAT_SEL_CFG(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Timer value for the number of 'heart beats' to hold the alternative
 * value enabled. For mode A the frequency offset is enabled for that time.
 * For mode B the number of increments or decrements is hold in I2 for that
 * time before the invers function brings I2 to its previous value again
 *
 * \details 
 * N * H = number of clock cycles to hold the alternative value; where N =
 * psg_timer_cfg and H = 2^psg_heart_beat_sel_cfg
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG . PSG_TIMER_CFG
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_TIMER_CFG(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_TIMER_CFG     VTSS_ES6514_ENCODE_BITMASK(0,16)
#define  VTSS_X_OMG_MAIN_OMG_PSG_OMG_PS_GEN_TIMER_CFG_PSG_TIMER_CFG(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Phase Shift Generator Main Status Register
 *
 * \details
 * Register: \a OMG_MAIN:OMG_PSG:OMG_PS_GEN_MAIN_STATUS
 */
#define VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_STATUS  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x5c)

/** 
 * \brief
 * Applying of alternative value has been finished
 *
 * \details 
 * 0: Application is pending
 * 1: Application has finished
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_STATUS . PSG_TOGGLE_ITR_DONE_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_PSG_OMG_PS_GEN_MAIN_STATUS_PSG_TOGGLE_ITR_DONE_STICKY  VTSS_ES6514_BIT(0)

/**
 * Register Group: \a OMG_MAIN:OMG_FILT
 *
 * Filter Configuration and Status Register set
 */


/** 
 * \brief Omega output filter main configuration register
 *
 * \details
 * Main configuration register for the Omega output filter.
 *
 * Register: \a OMG_MAIN:OMG_FILT:OMG_FILTER_MAIN
 *
 * @param ri Replicator: x_NUM_OUTPUT_LANES (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x5d + (ri))

/** 
 * \brief
 * Select data source for output filter.
 *
 * \details 
 * 0: Ref. clock input 0 (bypassing control block)
 * 1: Ref. clock input 1 (bypassing control block)
 * 2: Ref. clock input 2 (bypassing control block)
 * 3: Ref. clock input 3 (bypassing control block)
 * 4: Control block 0
 * 5: Control block 1
 * 6: Pure DCO mode
 * 7: Reserved
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN . FILT_SRC_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_SRC_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_SRC_SEL     VTSS_ES6514_ENCODE_BITMASK(16,3)
#define  VTSS_X_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_SRC_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Select filter damping / gain peaking. The default gain peaking of the
 * output filter is 0.034dB. The control value is interpreted as signed
 * value. Positive values increase the damping, i.e. lowering the gain
 * peacking; negative values decease the damping, i.e. raising the gain
 * peaking. The allowed programming range depends on the FILT_F_SEL
 * setting: 0 <= (FILT_F_SEL - FILT_D_SEL) <= 53. Values below -12 will
 * result in ringing. FILT_F_SEL - FILT_D_SEL = 0 and FILT_F_SEL -
 * FILT_D_SEL = 1 gives the same damping.
 *
 * \details 
 * Gain peaking = 0.0022 * e ** ((12 - FILT_D_SEL) / 3.84)
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN . FILT_D_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_D_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_D_SEL     VTSS_ES6514_ENCODE_BITMASK(10,6)
#define  VTSS_X_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_D_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Select filter cut off frequency. Permited value range 0 to 53.
 *
 * \details 
 * F_cut_off = 0.35 mHz * (FILT_F_SEL % 2) ? (1 << ((1 << (FILT_F_SEL >>
 * 1)) + ((1 << (FILT_F_SEL >> 1)) >> 1)) : (FILT_F_SEL >> 1))
 * F_cut_off ~= 0.35 mHz * int(2**(FILT_F_SEL/2))
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN . FILT_F_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_F_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_F_SEL     VTSS_ES6514_ENCODE_BITMASK(4,6)
#define  VTSS_X_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_F_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Synchronize output to input, i.e. the filter is preloaded in a way, that
 * the output frequency is immediately set to the input frequency and the
 * phase error integrator is cleared. This means, that the output is phase
 * locked to the current input phase.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN . FILT_SYNC_ONE_SHOT
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_SYNC_ONE_SHOT  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * Select whether FILT_SYNC_ONE_SHOT updates the output value and clears
 * the error integrator or clears the error integrator only.
 *
 * \details 
 * 0: Update output value and clear error integrator
 * 1: Clear the error integrator only
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN . FILT_SYNC_MODE
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_SYNC_MODE  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * Clear the filter circuit (integrators). FILT_ENA must be 1 to be
 * effective.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN . FILT_CLR
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_CLR  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Main enable for filter circuit.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN . FILT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_MAIN_FILT_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief Omega output filter phase slope limit configuration register
 *
 * \details
 * Phase slope limit configuration register for the Omega output filter.
 *
 * Register: \a OMG_MAIN:OMG_FILT:OMG_FILTER_PSL
 *
 * @param ri Replicator: x_NUM_OUTPUT_LANES (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x61 + (ri))

/** 
 * \brief
 * Select the phase slope limit. The output frequency is clamped in the
 * range of +/- the selected limit. The maximum value is 7 * 2 ** 32 and
 * corresponds to 1e6/1024 ppm.
 *
 * \details 
 * Bit 9-5 unsigned mantissa; bit 4-0 unsigned exponent. I.e. limit =
 * psl_limit[9:5] * 2 ** psl_limit[4:0]
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL . PSL_LIMIT
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL_PSL_LIMIT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL_PSL_LIMIT     VTSS_ES6514_ENCODE_BITMASK(4,10)
#define  VTSS_X_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL_PSL_LIMIT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Phase slope limiting mode selects, whether the phase slope limiting
 * happens before or after the output filter. Pre filter allows a larger
 * amount (> 1 us) of phase to be stored and compensated when not in phase
 * build out mode. Post filter is more precise, since the gain peaking of
 * the filter is also covered.
 *
 * \details 
 * 0: Pre filter limiting
 * 1: Post filter limiting
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL . PSL_MODE
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL_PSL_MODE  VTSS_ES6514_BIT(3)

/** 
 * \brief
 * Select whether the accumulated phase information, that is suppressed due
 * to phase slope limiting, is applied to the output clock when the
 * frequency offset returns back into the valid range.
 *
 * \details 
 * 0: Limited phase information is accumulated and applied
 * 1: Limited phase information is dismissed (phase build out)
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL . PSL_PHS_BUILD_OUT_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL_PSL_PHS_BUILD_OUT_ENA  VTSS_ES6514_BIT(2)

/** 
 * \brief
 * Select whether phase slope limiting is local reference based or holdover
 * based. If phase slope limiting is configured to be holdover based and no
 * valid holdover is present, the phase slope limiting is automatically
 * based on the local reference.
 *
 * \details 
 * 0: Local reference based
 * 1: Holdover based
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL . PSL_HO_BASED
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL_PSL_HO_BASED  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Enable phase slope limiting.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL . PSL_ENA
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_PSL_PSL_ENA  VTSS_ES6514_BIT(0)


/** 
 * \brief Omega output filter DCO low configuration register
 *
 * \details
 * DCO (digital controled oscilator) low configuration register for the
 * Omega output filter. Coding of signed 36-bit DCO value: F_offset [ppm] =
 * DCO / (7 * 2**32) * 1e6/1024 ppm. The max. value for DCO is +/- 7 *
 * 2**32.
 *
 * Register: \a OMG_MAIN:OMG_FILT:OMG_FILTER_DCO_LOW
 *
 * @param ri Replicator: x_NUM_OUTPUT_LANES (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_DCO_LOW(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x65 + (ri))


/** 
 * \brief Omega output filter DCO high configuration register
 *
 * \details
 * DCO (digital controled oscilator) high configuration register for the
 * Omega output filter. Coding of signed 36-bit DCO value: F_offset [ppm] =
 * DCO / (7 * 2**32) * 1e6/1024 ppm. The max. value for DCO is +/- 7 *
 * 2**32.
 *
 * Register: \a OMG_MAIN:OMG_FILT:OMG_FILTER_DCO_HIGH
 *
 * @param ri Replicator: x_NUM_OUTPUT_LANES (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_DCO_HIGH(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x69 + (ri))

/** 
 * \brief
 * One shot update bit to capture the DCO_high and DCO_low signal and use
 * them as new DCO value.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_DCO_HIGH . DCO_UPDATE_ONE_SHOT
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_DCO_HIGH_DCO_UPDATE_ONE_SHOT  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * MSB's [35:32] of the DCO value.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_DCO_HIGH . DCO_HIGH
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_DCO_HIGH_DCO_HIGH(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OMG_MAIN_OMG_FILT_OMG_FILTER_DCO_HIGH_DCO_HIGH     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_OMG_MAIN_OMG_FILT_OMG_FILTER_DCO_HIGH_DCO_HIGH(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Omega output filter sync control configuration register
 *
 * \details
 * Sync control configuration register for the Omega output filter.
 *
 * Register: \a OMG_MAIN:OMG_FILT:OMG_FILTER_SC
 *
 * @param ri Replicator: x_NUM_OUTPUT_LANES (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_SC(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x6d + (ri))

/** 
 * \brief
 * Select sync control test generator mode:
 *
 * \details 
 * 0: INC
 * 1: DEC
 * 2: WOBBLE
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_SC . FILT_SC_TEST_MODE
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_TEST_MODE(x)  VTSS_ES6514_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_TEST_MODE     VTSS_ES6514_ENCODE_BITMASK(16,2)
#define  VTSS_X_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_TEST_MODE(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Select sync control test generator period, i.e. number of INC resp. DEC
 * steps.
 *
 * \details 
 * Effective test generator period = FILT_SC_TEST_COUNT + 1
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_SC . FILT_SC_TEST_COUNT
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_TEST_COUNT(x)  VTSS_ES6514_ENCODE_BITFIELD(x,6,10)
#define  VTSS_M_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_TEST_COUNT     VTSS_ES6514_ENCODE_BITMASK(6,10)
#define  VTSS_X_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_TEST_COUNT(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,6,10)

/** 
 * \brief
 * Trigger sync control test generator. In INC resp. DEC mode both edges
 * act as trigger event. In WOBBLE mode a 1 enables wobbling. Disabling in
 * WOBBEL mode lets current wobble cycle finish before stopping. I.e. the
 * I2 values reaches its value prior to wobbling again.
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_SC . FILT_SC_TEST_TRIGGER
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_TEST_TRIGGER  VTSS_ES6514_BIT(5)

/** 
 * \brief
 * Enable for sync control test generator. Before enabling the test
 * generator the sync timer must be disabled (SC_SYNC_TIMER_SEL = 0) and
 * the filter has to be cleared (FILTER_CLEAR = 1).
 *
 * \details 
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_SC . FILT_SC_TEST_ENABLE
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_TEST_ENABLE  VTSS_ES6514_BIT(4)

/** 
 * \brief
 * Select the synchronization period for the I2 value via sync control bus.
 * Must be disabled (0) when sync control test generator is used.
 *
 * \details 
 * Number of 312.5MHz clock cycles:
 * 0: disabled
 * 1: 2**6
 * 2: 2**7
 * ..
 * 15: 2**20
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_SC . FILT_SC_SYNC_TIMER_SEL
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_SYNC_TIMER_SEL(x)  VTSS_ES6514_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_SYNC_TIMER_SEL     VTSS_ES6514_ENCODE_BITMASK(0,4)
#define  VTSS_X_OMG_MAIN_OMG_FILT_OMG_FILTER_SC_FILT_SC_SYNC_TIMER_SEL(x)  VTSS_ES6514_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Omega output filter status register
 *
 * \details
 * Status register for the Omega output filter.
 *
 * Register: \a OMG_MAIN:OMG_FILT:OMG_FILTER_STAT
 *
 * @param ri Replicator: x_NUM_OUTPUT_LANES (??), 0-3
 */
#define VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_STAT(ri)  VTSS_ES6514_IOREG(VTSS_TO_OMG_IP,0x71 + (ri))

/** 
 * \brief
 * Sync control receiver detected a protocol error.
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_STAT . FILT_SC_PROTOCOL_ERR_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_STAT_FILT_SC_PROTOCOL_ERR_STICKY  VTSS_ES6514_BIT(16)

/** 
 * \brief
 * The accumlator for phase correction after phase slope limiting
 * saturated. If psl_mode = 1 this is equivalent with a saturation of the
 * first filter integrator.
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_STAT . PSL_ACCU_SAT_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_STAT_PSL_ACCU_SAT_STICKY  VTSS_ES6514_BIT(1)

/** 
 * \brief
 * Phase slope limiting occured. If psl_mode = 1 this is equivalent with a
 * saturation of the second filter integrator.
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OMG_MAIN_OMG_FILT_OMG_FILTER_STAT . PSL_STAT_STICKY
 */
#define  VTSS_F_OMG_MAIN_OMG_FILT_OMG_FILTER_STAT_PSL_STAT_STICKY  VTSS_ES6514_BIT(0)


#endif /* _VTSS_ES6514_REGS_OMG_MAIN_H_ */
