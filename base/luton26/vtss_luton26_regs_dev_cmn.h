#ifndef _VTSS_LUTON26_REGS_DEV_CMN_H_
#define _VTSS_LUTON26_REGS_DEV_CMN_H_

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

#include "vtss_luton26_regs_dev_gmii.h"
#include "vtss_luton26_regs_dev.h"

/*
 * Abstraction macros for functionally identical registers 
 * in the DEV and DEV_GMII targets.
 *
 * Caution: These macros may not work a lvalues, depending
 * on compiler and platform.
 *
 */

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_MODE_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_MODE_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_MODE_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_IFG_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_IFG_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_TAGS_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_HDX_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_HDX_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_ENA_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_ENA_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_ENA_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_FC_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_MAXLEN_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_MAXLEN_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_MAXLEN_CFG(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_STICKY(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_STICKY(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY(t) )

#define VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG(t) ( (t) >= VTSS_TO_DEV_10 ? VTSS_DEV_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG(t) : VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG(t) )


#endif /* _VTSS_LUTON26_REGS_DEV_CMN_H_ */
