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

#ifndef _VTSS_PHY_TYPES_H_
#define _VTSS_PHY_TYPES_H_

#include <vtss/api/types.h>

/**
 * \file
 * \brief PHY Public API Header
 * \details This header file describes public PHY data-types
 */

#ifdef __cplusplus
extern "C" {
#endif

#define VTSS_PHY_POWER_ACTIPHY_BIT 0 /**< Defines the bit used to signaling that ActiPhy is enabled */
#define VTSS_PHY_POWER_DYNAMIC_BIT 1 /**< Defines the bit used to signaling that PerfectReach is enabled */

/** \brief PHY power reduction modes */
typedef enum {
    VTSS_PHY_POWER_NOMINAL = 0, /**< Default power settings */
    VTSS_PHY_POWER_ACTIPHY = 1 << VTSS_PHY_POWER_ACTIPHY_BIT, /**< ActiPHY - Link down power savings enabled (Bit 0) */
    VTSS_PHY_POWER_DYNAMIC = 1 << VTSS_PHY_POWER_DYNAMIC_BIT, /**< PerfectReach - Link up power savings enabled (Bit 1) */
    VTSS_PHY_POWER_ENABLED = VTSS_PHY_POWER_ACTIPHY +  VTSS_PHY_POWER_DYNAMIC /**< ActiPHY + PerfectReach enabled */
} vtss_phy_power_mode_t;

/** \brief VeriPHY status */
typedef enum {
    VTSS_VERIPHY_STATUS_OK      = 0,  /**< Correctly terminated pair */
    VTSS_VERIPHY_STATUS_OPEN    = 1,  /**< Open pair */
    VTSS_VERIPHY_STATUS_SHORT   = 2,  /**< Short pair */
    VTSS_VERIPHY_STATUS_ABNORM  = 4,  /**< Abnormal termination */
    VTSS_VERIPHY_STATUS_SHORT_A = 8,  /**< Cross-pair short to pair A */
    VTSS_VERIPHY_STATUS_SHORT_B = 9,  /**< Cross-pair short to pair B */
    VTSS_VERIPHY_STATUS_SHORT_C = 10, /**< Cross-pair short to pair C */
    VTSS_VERIPHY_STATUS_SHORT_D = 11, /**< Cross-pair short to pair D */
    VTSS_VERIPHY_STATUS_COUPL_A = 12, /**< Abnormal cross-pair coupling, pair A */
    VTSS_VERIPHY_STATUS_COUPL_B = 13, /**< Abnormal cross-pair coupling, pair B */
    VTSS_VERIPHY_STATUS_COUPL_C = 14, /**< Abnormal cross-pair coupling, pair C */
    VTSS_VERIPHY_STATUS_COUPL_D = 15, /**< Abnormal cross-pair coupling, pair D */
    VTSS_VERIPHY_STATUS_UNKNOWN = 16, /**< Unknown - VeriPhy never started ? */
    VTSS_VERIPHY_STATUS_RUNNING = 17  /**< VeriPhy is still running - No result yet */
} vtss_phy_veriphy_status_t;




#ifdef __cplusplus
}
#endif

#endif /* #define _VTSS_PHY_TYPES_H_ */
