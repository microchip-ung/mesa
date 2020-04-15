/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_FA_REGS_CHIP_TOP_H_
#define _VTSS_FA_REGS_CHIP_TOP_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a CHIP_TOP
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a CHIP_TOP:OTP_MEM
 *
 * OTP memory
 */


/** 
 * \brief Configuration of OTP memory
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_CFG
 */
#define VTSS_CHIP_TOP_OTP_CFG                VTSS_IOREG(VTSS_TO_CHIP_TOP,0x0)

/** 
 * \brief
 * The core frequency divided by OTP_DIV must be 125MHz
 *
 * \details 
 * Field: ::VTSS_CHIP_TOP_OTP_CFG . OTP_DIV
 */
#define  VTSS_F_CHIP_TOP_OTP_CFG_OTP_DIV(x)   VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_CHIP_TOP_OTP_CFG_OTP_DIV      VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_CHIP_TOP_OTP_CFG_OTP_DIV(x)   VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief TCAM recovery information
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_RCR
 *
 * @param ri Register: OTP_RCR (??), 0-2
 */
#define VTSS_CHIP_TOP_OTP_RCR(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x1 + (ri))

/** 
 * \details 
 * 
 *	     TCAM repair information is divided in groups of 16-bits (2
 * groups per 32-bit register)
 *		 0..5: column
 *		    6: 0:core_a 1:core_b
 *		7..12: tcam index
 *	       13..14: 0:super 1:es0 2:es2 3:ip6pfx
 *		   15: 0:invalid group 1:valid group

 *
 * Field: ::VTSS_CHIP_TOP_OTP_RCR . OTP_RCR
 */
#define  VTSS_F_CHIP_TOP_OTP_RCR_OTP_RCR(x)   (x)
#define  VTSS_M_CHIP_TOP_OTP_RCR_OTP_RCR      0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_RCR_OTP_RCR(x)   (x)


/** 
 * \brief miscellaneous memory
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_MSC
 *
 * @param ri Register: OTP_MSC (??), 0-3
 */
#define VTSS_CHIP_TOP_OTP_MSC(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x4 + (ri))

/** 
 * \details 
 * Field: ::VTSS_CHIP_TOP_OTP_MSC . OTP_MSC
 */
#define  VTSS_F_CHIP_TOP_OTP_MSC_OTP_MSC(x)   (x)
#define  VTSS_M_CHIP_TOP_OTP_MSC_OTP_MSC      0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_MSC_OTP_MSC(x)   (x)


/** 
 * \brief Chip Identification
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_ID
 */
#define VTSS_CHIP_TOP_OTP_ID                 VTSS_IOREG(VTSS_TO_CHIP_TOP,0x8)

/** 
 * \details 
 * Field: ::VTSS_CHIP_TOP_OTP_ID . OTP_ID
 */
#define  VTSS_F_CHIP_TOP_OTP_ID_OTP_ID(x)     (x)
#define  VTSS_M_CHIP_TOP_OTP_ID_OTP_ID        0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_ID_OTP_ID(x)     (x)


/** 
 * \brief OTP random key
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_RND
 *
 * @param ri Register: OTP_RND (??), 0-7
 */
#define VTSS_CHIP_TOP_OTP_RND(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x9 + (ri))

/** 
 * \details 
 * Field: ::VTSS_CHIP_TOP_OTP_RND . OTP_RND
 */
#define  VTSS_F_CHIP_TOP_OTP_RND_OTP_RND(x)   (x)
#define  VTSS_M_CHIP_TOP_OTP_RND_OTP_RND      0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_RND_OTP_RND(x)   (x)


/** 
 * \brief OTP product information
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_PRD
 *
 * @param ri Register: OTP_PRD (??), 0-7
 */
#define VTSS_CHIP_TOP_OTP_PRD(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x11 + (ri))

/** 
 * \details 
 * Field: ::VTSS_CHIP_TOP_OTP_PRD . OTP_PRD
 */
#define  VTSS_F_CHIP_TOP_OTP_PRD_OTP_PRD(x)   (x)
#define  VTSS_M_CHIP_TOP_OTP_PRD_OTP_PRD      0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_PRD_OTP_PRD(x)   (x)


#endif /* _VTSS_FA_REGS_CHIP_TOP_H_ */
