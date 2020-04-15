#ifndef _VTSS_JAGUAR2_REGS_XFI_SHELL_H_
#define _VTSS_JAGUAR2_REGS_XFI_SHELL_H_

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

#include "vtss_jaguar2_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a XFI_SHELL
 *
 * \see vtss_target_XFI_SHELL_e
 *
 * XFI shell
 *
 ***********************************************************************/

/**
 * Register Group: \a XFI_SHELL:XFI_CONTROL
 *
 * XFI controls
 */


/** 
 * \brief KR mode control
 *
 * \details
 * Control operating modes initiated by KR
 *
 * Register: \a XFI_SHELL:XFI_CONTROL:KR_CONTROL
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * ANEG link partner rate negotiation result (link-HCD)
 *
 * \details 
 * 0: 10G
 * 1: 1G
 * 2: 3G
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_RATE
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_RATE(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_RATE     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * KR-ANEG FEC negotiation result
 *
 * \details 
 * 0: KR_FEC shall be disabled
 * 1: KR_FEC shall be enabled
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_FEC_ENABLE
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_FEC_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_FEC_ENABLE  VTSS_BIT(16)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_FEC_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Global Masking of KR interrupt
 *
 * \details 
 * 0: Inhibit KR interrupt propagation
 * 1: Enable KR interrupt
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_INT_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_INT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_INT_MASK  VTSS_BIT(15)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_INT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Polarity of KR interrupt
 *
 * \details 
 * 0: High-active (0 is inactive level)
 * 1: Low-active (1 is inactive level)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_INT_POL
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_INT_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_INT_POL  VTSS_BIT(14)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_INT_POL(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Masking of KR RATE interrupt
 *
 * \details 
 * 0: Inhibit KR_RATE select interrupt propagation
 * 1: Enable KR_RATE select interrupt
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_RATE_INT_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_RATE_INT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_RATE_INT_MASK  VTSS_BIT(13)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_RATE_INT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Masking of KR FEC interrupt
 *
 * \details 
 * 0: Inhibit KR_FEC interrupt propagation
 * 1: Enable KR_FEC interrupt
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_FEC_INT_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_FEC_INT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_FEC_INT_MASK  VTSS_BIT(12)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_FEC_INT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Masking of KR MODE interrupt
 *
 * \details 
 * 0: Inhibit KR_MODE interrupt propagation
 * 1: Enable KR_MODE interrupt
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_MODE_INT_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_MODE_INT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_MODE_INT_MASK  VTSS_BIT(11)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_MODE_INT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * ANEG requires KR rate selection be changed (required state see
 * KR_FEC_ENABLE)
 *
 * \details 
 * 0: No action required
 * 1: KR rate must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_RATE_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RATE_STICKY  VTSS_BIT(10)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * ANEG requires KR_FEC state be changed (required state see KR_FEC_ENABLE)
 *
 * \details 
 * 0: No action required
 * 1: KR_FEC must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_FEC_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_FEC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_FEC_STICKY  VTSS_BIT(9)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_FEC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * ANEG requires SD10G65-macro (RX+TX) be setup to 10.3125G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_10G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_10G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_10G_STICKY  VTSS_BIT(8)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_10G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * ANEG requires SD10G65_TX-macro be setup to 10.3125G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_TX10G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX10G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX10G_STICKY  VTSS_BIT(7)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX10G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * ANEG requires SD10G65_RX-macro be setup to 10.3125G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_RX10G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX10G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX10G_STICKY  VTSS_BIT(6)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX10G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * ANEG requires SD10G65_-macro (RX+TX) be setup to 3.125G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_3G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_3G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_3G_STICKY  VTSS_BIT(5)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_3G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * ANEG requires SD10G65_TX-macro be setup to 3.125G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_TX3G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX3G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX3G_STICKY  VTSS_BIT(4)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX3G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * ANEG requires SD10G65_RX-macro be setup to 3.125G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_RX3G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX3G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX3G_STICKY  VTSS_BIT(3)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX3G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * ANEG requires SD10G65-macro (RX+TX) be setup to 1.25G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_1G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_1G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_1G_STICKY  VTSS_BIT(2)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_1G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * ANEG requires SD10G65_TX-macro be setup to 1.25G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_TX1G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX1G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX1G_STICKY  VTSS_BIT(1)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_TX1G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * ANEG requires SD10G65_RX-macro be setup to 1.25G mode
 *
 * \details 
 * 0: No action required
 * 1: Macro must be reconfigured, SW has to clear this bit after
 * reconfiguration (by writing a 1 to this bit-group)!
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_KR_CONTROL . KR_ANEG_RX1G_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX1G_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX1G_STICKY  VTSS_BIT(0)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_KR_CONTROL_KR_ANEG_RX1G_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief XFI modes
 *
 * \details
 * Control and operating modes of the XFI.
 *
 * Register: \a XFI_SHELL:XFI_CONTROL:XFI_MODE
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Phase selection of DES in 100fx mode
 *
 * \details 
 * 0: CDR locked at bit 9
 * 1: CDR locked at bit 4

 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . DES_100FX_PHASE_SEL
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_DES_100FX_PHASE_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_DES_100FX_PHASE_SEL  VTSS_BIT(31)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_DES_100FX_PHASE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Select external macro for sync_ctrl information.
 *
 * \details 
 * 0: Select macro 0
 * 1: Select macro 1
 * 2: Select macro 2
 * 3: Select macro 3
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . EXT_SYNC_CTRL_SEL
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_EXT_SYNC_CTRL_SEL(x)  VTSS_ENCODE_BITFIELD(x,27,4)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_EXT_SYNC_CTRL_SEL     VTSS_ENCODE_BITMASK(27,4)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_EXT_SYNC_CTRL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,27,4)

/** 
 * \brief
 * Enable 100Base-FX mode. Enables specific deserializer cp/md handling 
 * (requires enabling external cp/md sourceing in the SerDes macro. 
 * PORT_SEL must be set to 1 (40-bit mode) for 100Base-FX mode.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . FX100_ENA
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_ENA  VTSS_BIT(26)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_ENA(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Select 100Base-FX operation mode.
 *
 * \details 
 * 0: Normal mode (optimal bit is copied to all bits)
 * 1: Simple mode (received data not modified)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . FX100_MODE
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_MODE  VTSS_BIT(25)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_MODE(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Enable kick-out-of-180-degree functionality.
 *
 * \details 
 * 0: Enable PCS controlled kicking (kicking allowed in case of no sync)
 * 1: Disable kicking
 * 2: Enable kicking at any time
 * 3: Reserved
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . FX100_KICK_MODE
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_KICK_MODE(x)  VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_KICK_MODE     VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_KICK_MODE(x)  VTSS_EXTRACT_BITFIELD(x,23,2)

/** 
 * \brief
 * Swap cp/md signals in 100Base-FX mode.
 *
 * \details 
 * 0: No swapping of cp and md
 * 1: Swap cp and md
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . FX100_SWAP_CP_MD
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_SWAP_CP_MD(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_SWAP_CP_MD  VTSS_BIT(22)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_FX100_SWAP_CP_MD(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Active port selection. Only one port can be active at a time.
 *
 * \details 
 * 0: 64-bit port is active.
 * 1: 40-bit port is active.
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . PORT_SEL
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_PORT_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_PORT_SEL  VTSS_BIT(21)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_PORT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * The 64-bit port can be equipped with a FIFO to ease 64/66-bit originated
 * clock variations.
 *
 * \details 
 * 0: TX-FIFO is bypassed.
 * 1: TX-FIFO is enabled.
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . TX_USE_FIFO
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_USE_FIFO(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_USE_FIFO  VTSS_BIT(20)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_USE_FIFO(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Clock divider for SPI Master
 *
 * \details 
 * f(spi_clk) = f(system_clk)/(SPI_CLK_DIV+2)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . SPI_CLK_DIV
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_SPI_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_SPI_CLK_DIV     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_SPI_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Invert data received from the HSS Rx data port
 *
 * \details 
 * 0: Non-inverted data from the Rx data port
 * 1: Inverted data from the Rx data port
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . RX_INVERT
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_RX_INVERT(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_RX_INVERT  VTSS_BIT(9)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_RX_INVERT(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Invert data driven into the HSS Tx data port (txad)
 *
 * \details 
 * 0: Non-inverted data to the Tx data port
 * 1: Inverted data to the Tx data port
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . TX_INVERT
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_INVERT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_INVERT  VTSS_BIT(8)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_INVERT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Select the line Rx data loopback path instead of the core Tx data as the
 * source of the internal Tx data path.
 *
 * \details 
 * 0: Core Tx data selected (default)
 * 1: Line Rx data (loopback) selected
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . SEL_LINELB
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_SEL_LINELB(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_SEL_LINELB  VTSS_BIT(6)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_SEL_LINELB(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * TX_FIFO error mode control
 * When deasserted (default), if single Tx-data word is read outside the
 * 'safe' zone (where a full-cycle of setup and hold are guaranteed), the
 * TX_LOS status will be asserted.
 * Due to synchronization uncertainties it is possible to be 'on-edge' and
 * still make timing, having a whole cycle plus something less than a cycle
 * for setup and hold timing. When this field is asserted, two concecutive
 * read cycles outside the 'safe' zone must occur to generate the TX_LOS
 * status. This allows a known (slew-rate limited) drift rate to dither
 * 'on-edge' out of the 'safe' zone for a cycle and not generate the TX_LOS
 * if read timing returns to the 'safe' zone on the following cycle.
 *
 * \details 
 * 0: A single read outside the 'safe' zone generates a TX_LOS condition
 * (default)
 * 1: Monitor for two concecutive out of 'safe' zone cycles to generate
 * TX_LOS
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . TXF_ERR_MODE
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_TXF_ERR_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_TXF_ERR_MODE  VTSS_BIT(5)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_TXF_ERR_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set the data-type/endian mode of the core to HSS interface
 *
 * \details 
 * 0: Core 64/66 data: bit 63 first, followed by the remaining bits leading
 * to bit 0 (default)
 * 1: Core 64/66 data: bit 0 first, followed by the remaining bits leading
 * to bit 63
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . ENDIAN
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_ENDIAN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_ENDIAN  VTSS_BIT(4)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_ENDIAN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Automatically assert a hardware TX_RESYNC when TX_FIFO_LOS is detected
 *
 * \details 
 * 0: TX_FIFO will not resync when an LOS event is detected
 * 1: TX_FIFO will resync when an LOS event is detected
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . TX_AUTORESYNC
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_AUTORESYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_AUTORESYNC  VTSS_BIT(3)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_AUTORESYNC(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Resynchronize the core/XFI data phase crossing logic
 * Must always be asserted after SW_RST or SW_ENA
 *
 * \details 
 * 0: No action
 * 1: Set TX_RESYNC, HW will clear this bit when sync has completed
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . TX_RESYNC_SHOT
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_RESYNC_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_RESYNC_SHOT  VTSS_BIT(2)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_TX_RESYNC_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * SW_ENA input to XFI clk_rst_sync modules (internal Tx-clock, core Tx
 * clock-input, internal Rx-clock)
 *
 * \details 
 * 0: SW_ENA deasserted (default)
 * 1: SW_ENA asserted
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . SW_ENA
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_ENA  VTSS_BIT(1)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * SW_RST input to XFI clk_rst_sync modules (internal Tx-clock, core Tx
 * clock-input, internal Rx-clock)
 *
 * \details 
 * 0: SW_RST deasserted
 * 1: SW_RST asserted (default)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_MODE . SW_RST
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_RST  VTSS_BIT(0)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_MODE_SW_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief XFI interrupt status
 *
 * \details
 * The XFI_INT, its sources, and the XFI_SSF are visible from this
 * register.
 *
 * Register: \a XFI_SHELL:XFI_CONTROL:XFI_STATUS
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_XFI_STATUS(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Status from macro: Receiver detected.
 *
 * \details 
 * 0: XFI has no receiver detected
 * 1: XFI has a receiver detected
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_STATUS . RECEIVER_DETECT_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_STATUS_RECEIVER_DETECT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_STATUS_RECEIVER_DETECT_STATUS  VTSS_BIT(24)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_STATUS_RECEIVER_DETECT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Status of the XFI_SSF output port
 *
 * \details 
 * 0: XFI_SSF deasserted
 * 1: XFI_SSF asserted
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_STATUS . SSF_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_STATUS_SSF_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_STATUS_SSF_STATUS  VTSS_BIT(20)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_STATUS_SSF_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Unmasked status of the ANEG_KR_INT status output
 * When the ANEG_KR_INT_MASK is set, this status is a source of the
 * XFI_INT.
 *
 * \details 
 * 0: The ANEG_KR_INT status is deasserted (low)
 * 1: The ANEG_KR_INT status is asserted (high)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_STATUS . ANEG_KR_INT_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_STATUS_ANEG_KR_INT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_STATUS_ANEG_KR_INT_STATUS  VTSS_BIT(18)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_STATUS_ANEG_KR_INT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Unmasked status of the ANEG_ACTIVE status output
 * When the ANEG_ACTIVE_MASK is set, this status is a source of the
 * XFI_INT.
 *
 * \details 
 * 0: The ANEG_ACTIVE status is deasserted (low)
 * 1: The ANEG_ACTIVE status is asserted (high)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_STATUS . ANEG_ACTIVE_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_STATUS_ANEG_ACTIVE_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_STATUS_ANEG_ACTIVE_STATUS  VTSS_BIT(16)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_STATUS_ANEG_ACTIVE_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Status of XFI_INT output port
 * XFI_INT = XFI_MASK & (RXINT_STATUS | TXINT_STATUS)
 *
 * \details 
 * 0: XFI_INT deasserted
 * 1: XFI_INT asserted
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_XFI_STATUS . XFIINT_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_XFI_STATUS_XFIINT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_XFI_STATUS_XFIINT_STATUS  VTSS_BIT(0)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_XFI_STATUS_XFIINT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SSF INT control/masks and global XFI INT mask
 *
 * \details
 * Control and mask of the asynchronous XFI_SFF output. The global XFI_INT
 * mask located here supersede the individual masks.
 * Note: SSF status is also captured in the HSS_STICKY and HSS_STATUS
 * registers.
 *
 * Register: \a XFI_SHELL:XFI_CONTROL:INT_CTRL
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Invert polarity of tx_pll_lock_i prior to summing it with rxsigdet_i and
 * rx_los_i to generate xfi_ssf_o.
 * See SSF_MASK Encoding field.
 * Note: The "good" case for TX_PLL_LOCK is when the SERDES delivers a '1'.
 * Therefor the signal is per default inverted.
 *
 * \details 
 * 0: Do not invert the TX_PLL_LOCK before summing it to generate the
 * XFI_SSF output (default)
 * 1: Invert the TX_PLL_LOCK before summing it to generate the XFI_SSF
 * output
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . TX_PLL_LOCK_INV
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_TX_PLL_LOCK_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_TX_PLL_LOCK_INV  VTSS_BIT(31)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_TX_PLL_LOCK_INV(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Enable tx_pll_lock_i prior to summing it with rxsigdet_i and rx_los_i to
 * generate xfi_ssf_o.
 * See SSF_MASK Encoding field.
 *
 * \details 
 * 0: Inhibit the TX_PLL_LOCK (either polarity) from the XFI_SSF output
 * 1: Enable the TX_PLL_LOCK (either polarity) to the XFI_SSF output
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . TX_PLL_LOCK_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_TX_PLL_LOCK_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_TX_PLL_LOCK_MASK  VTSS_BIT(30)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_TX_PLL_LOCK_MASK(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Invert polarity of rx_pll_lock_i prior to summing it with rxsigdet_i and
 * rx_los_i to generate xfi_ssf_o.
 * See SSF_MASK Encoding field.
 * Note: The "good" case for RX_PLL_LOCK is when the SERDES delivers a '1'.
 * Therefor the signal is per default inverted.
 *
 * \details 
 * 0: Do not invert the RX_PLL_LOCK before summing it to generate the
 * XFI_SSF output (default)
 * 1: Invert the RX_PLL_LOCK before summing it to generate the XFI_SSF
 * output
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . RX_PLL_LOCK_INV
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_PLL_LOCK_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_PLL_LOCK_INV  VTSS_BIT(29)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_PLL_LOCK_INV(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Enable rx_pll_lock_i prior to summing it with rxsigdet_i and rx_los_i to
 * generate xfi_ssf_o.
 * See SSF_MASK Encoding field.
 *
 * \details 
 * 0: Inhibit the RX_PLL_LOCK (either polarity) from the XFI_SSF output
 * 1: Enable the RX_PLL_LOCK (either polarity) to the XFI_SSF output
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . RX_PLL_LOCK_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_PLL_LOCK_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_PLL_LOCK_MASK  VTSS_BIT(28)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_PLL_LOCK_MASK(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Invert polarity of rx_sigdet_i prior to summing it with rx_los_i to
 * generate xfi_ssf_o.
 * See SSF_MASK Encoding field.
 * Note: The "good" case for RX_SIGDET is when the SERDES delivers a '1'.
 * Therefor the signal is per default inverted.
 *
 * \details 
 * 0: Do not invert the RX_SIGDET before summing it to generate the XFI_SSF
 * output (default)
 * 1: Invert the RX_SIGDET before summing it to generate the XFI_SSF output
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . RXSIGDET_INV
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_RXSIGDET_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_RXSIGDET_INV  VTSS_BIT(27)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_RXSIGDET_INV(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Enable rx_sigdet_i prior to summing it with rx_los_i to generate
 * xfi_ssf_o.
 * See SSF_MASK Encoding field.
 *
 * \details 
 * 0: Inhibit the RX_SIGDET (either polarity) from the XFI_SSF output
 * 1: Enable the RX_SIGDET (either polarity) to the XFI_SSF output
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . RXSIGDET_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_RXSIGDET_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_RXSIGDET_MASK  VTSS_BIT(26)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_RXSIGDET_MASK(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Invert polarity of rx_los_i prior to summing it with rx_sigdet_i to
 * generate xfi_ssf_o.
 * See SSF_MASK Encoding field.
 *
 * \details 
 * 0: Do not invert the RX_LOS before summing it to generate the XFI_SSF
 * output (default)
 * 1: Invert the RX_LOS before summing it to generate the XFI_SSF output
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . RX_LOS_INV
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_LOS_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_LOS_INV  VTSS_BIT(25)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_LOS_INV(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Enable rx_los_i prior to summing it with rx_sigdet_i to generate
 * xfi_ssf_o.
 * See SSF_MASK Encoding field.
 *
 * \details 
 * 0: Inhibit the RX_LOS (either polarity) from the XFI_SSF output
 * 1: Enable the RX_LOS (either polarity) to the XFI_SSF output
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . RX_LOS_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_LOS_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_LOS_MASK  VTSS_BIT(24)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_RX_LOS_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Global mask (enable) the XFI_SSF output.
 * xfi_ssf_o =	SSF_MASK &
 *   ( rx_los_mask & (rx_los_inv ^ rx_los_i)
 *   | rx_sigdet_mask & (rx_sigdet_inv ^ rx_sigdet_i)
 *   | rx_pll_lock_mask & rx_pll_lock_ssf_r
 *   | tx_pll_lock_mask  & tx_pll_lock_ssf_r
 *
 * \details 
 * 0: Inhibit XFI_SSF from being asserted
 * 1: Enable the XFI_SSF to use the RX_LOS and the RX_SIGDET states,
 * polarities, and masks
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . SSF_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_SSF_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_SSF_MASK  VTSS_BIT(20)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_SSF_MASK(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Global mask (enable) the ANEG_INT status as a source of the XFI_INT.
 *
 * \details 
 * 0: Disable ANEG_KR_INT status from setting XFI_INT (default)
 * 1: Enable ANEG_KR_INT status to set XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . ANEG_KR_INT_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_ANEG_KR_INT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_ANEG_KR_INT_MASK  VTSS_BIT(18)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_ANEG_KR_INT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Global mask (enable) the ANEG_ACTIVE status as a source of the XFI_INT.
 *
 * \details 
 * 0: Disable ANEG_ACTIVE status from setting XFI_INT (default)
 * 1: Enable ANEG_ACTIVE status to set XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . ANEG_ACTIVE_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_ANEG_ACTIVE_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_ANEG_ACTIVE_MASK  VTSS_BIT(16)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_ANEG_ACTIVE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Global mask (enable) the XFI_INT output.
 *
 * \details 
 * 0: Disable XFI_INT output, regardless of the STICKY and corresponding
 * MASK states
 * 1: Enable XFI_INT, using STICKY and corresponding MASK states
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_INT_CTRL . XFI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_INT_CTRL_XFI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_INT_CTRL_XFI_MASK  VTSS_BIT(0)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_INT_CTRL_XFI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SSF set / reset hysteresis enable register.
 *
 * \details
 * SSF set / reset hysteresis enable register. Enables the timing of
 * asserting or deasserting SSF
 *
 * Register: \a XFI_SHELL:XFI_CONTROL:SSF_HYST_ENA_CTRL
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_SSF_HYST_ENA_CTRL(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * Enable timing and hysteresis as defined in SSF_HYST_TIMING_CTRL.
 *
 * \details 
 * 0: SSF is immediately asserted to the core.
 * 1: SSF signal to core is timed as defined by SSF_HYST_TIMING_CTRL.
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_SSF_HYST_ENA_CTRL . SSF_HYST_ENA
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_SSF_HYST_ENA_CTRL_SSF_HYST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_SSF_HYST_ENA_CTRL_SSF_HYST_ENA  VTSS_BIT(0)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_SSF_HYST_ENA_CTRL_SSF_HYST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SSF set / reset hysteresis control register.
 *
 * \details
 * SSF set / reset hysteresis control register. Controls the timing of
 * asserting or deasserting SSF
 *
 * Register: \a XFI_SHELL:XFI_CONTROL:SSF_HYST_TIMING_CTRL
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Time a SSF must be inactive before it is forwarded to the core.
 * Resolution: One tick is 102.4 ns.
 *
 * \details 
 * Number of ticks SSF must be constantly inactive before it is reported to
 * the core.
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL . SSF_DEASSERT_TIMING
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL_SSF_DEASSERT_TIMING(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL_SSF_DEASSERT_TIMING     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL_SSF_DEASSERT_TIMING(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/** 
 * \brief
 * Time a SSF must be active before it is forwarded to the core.
 * Resolution: One tick is 102.4 ns.
 *
 * \details 
 * Number of ticks SSF must be constantly active before it is reported to
 * the core.
 * E.g. a value of 23 would result in a wait time of 2.3552 us.
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL . SSF_ASSERT_TIMING
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL_SSF_ASSERT_TIMING(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL_SSF_ASSERT_TIMING     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_SSF_HYST_TIMING_CTRL_SSF_ASSERT_TIMING(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief XFI HSS macro status sticky bits
 *
 * \details
 * Register: \a XFI_SHELL:XFI_CONTROL:HSS_STICKY
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * The DFT_NO_SYNC signal was detected asserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: DFT_NO_SYNC was not detected asserted (since this bit was last
 * cleared)
 * 1: DFT_NO_SYNC was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_NO_SYNC_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_NO_SYNC_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_NO_SYNC_HI_STICKY  VTSS_BIT(31)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_NO_SYNC_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * The DFT_NO_SYNC signal was detected deasserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: DFT_NO_SYNC was not detected deasserted (since this bit was last
 * cleared)
 * 1: DFT_NO_SYNC was detected deasserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_NO_SYNC_LO_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_NO_SYNC_LO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_NO_SYNC_LO_STICKY  VTSS_BIT(30)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_NO_SYNC_LO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * The DFT_INSTABLE signal was detected asserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: DFT_INSTABLE was not detected asserted (since this bit was last
 * cleared)
 * 1: DFT_INSTABLE was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_INSTABLE_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INSTABLE_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INSTABLE_HI_STICKY  VTSS_BIT(29)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INSTABLE_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * The DFT_INSTABLE signal was detected deasserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: DFT_INSTABLE was not detected deasserted (since this bit was last
 * cleared)
 * 1: DFT_INSTABLE was detected deasserted (since this bit was last
 * cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_INSTABLE_LO_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INSTABLE_LO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INSTABLE_LO_STICKY  VTSS_BIT(28)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INSTABLE_LO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * The DFT_INCOMPLETE signal was detected asserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: DFT_INCOMPLETE was not detected asserted (since this bit was last
 * cleared)
 * 1: DFT_INCOMPLETE was detected asserted (since this bit was last
 * cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_INCOMPLETE_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INCOMPLETE_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INCOMPLETE_HI_STICKY  VTSS_BIT(27)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INCOMPLETE_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * The DFT_INCOMPLETE signal was detected deasserted (since this bit was
 * last cleared)
 *
 * \details 
 * 0: DFT_INCOMPLETE was not detected deasserted (since this bit was last
 * cleared)
 * 1: DFT_INCOMPLETE was detected deasserted (since this bit was last
 * cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_INCOMPLETE_LO_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INCOMPLETE_LO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INCOMPLETE_LO_STICKY  VTSS_BIT(26)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_INCOMPLETE_LO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * The DFT_ACTIVE signal was detected asserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: DFT_ACTIVE was not detected asserted (since this bit was last
 * cleared)
 * 1: DFT_ACTIVE was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_ACTIVE_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_ACTIVE_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_ACTIVE_HI_STICKY  VTSS_BIT(25)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_ACTIVE_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * The DFT_ACTIVE signal was detected deasserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: DFT_ACTIVE was not detected deasserted (since this bit was last
 * cleared)
 * 1: DFT_ACTIVE was detected deasserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_ACTIVE_LO_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_ACTIVE_LO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_ACTIVE_LO_STICKY  VTSS_BIT(24)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_ACTIVE_LO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * The DFT_STUCK_AT signal was detected asserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: DFT_STUCK_AT was not detected asserted (since this bit was last
 * cleared)
 * 1: DFT_STUCK_AT was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . DFT_STUCK_AT_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_STUCK_AT_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_STUCK_AT_HI_STICKY  VTSS_BIT(22)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_DFT_STUCK_AT_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * The TX_FIFO was detected asserted (since this bit was last cleared)
 *
 * \details 
 * 0: TX_FIFO_LOS was not detected asserted (since this bit was last
 * cleared)
 * 1: TX_FIFO_LOS was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . TX_FIFO_LOS_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_FIFO_LOS_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_FIFO_LOS_HI_STICKY  VTSS_BIT(21)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_FIFO_LOS_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * TX_PLL_LOCK input pin was detected asserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: TX_PLL_LOCK was not detected asserted (since this bit was last
 * cleared)
 * 1: TX_PLL_LOCK was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . TX_PLL_LOCK_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_PLL_LOCK_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_PLL_LOCK_HI_STICKY  VTSS_BIT(19)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_PLL_LOCK_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * TX_PLL_LOCK input pin was detected deasserted (since this bit was last
 * cleared).
 *
 * \details 
 * 0: TX_PLL_LOCK was not detected deasserted (since this bit was last
 * cleared)
 * 1: TX_PLL_LOCK was detected deasserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . TX_PLL_LOCK_LO_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_PLL_LOCK_LO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_PLL_LOCK_LO_STICKY  VTSS_BIT(18)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_TX_PLL_LOCK_LO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * RX_PLL_LOCK input pin was detected asserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: RX_PLL_LOCK was not detected asserted (since this bit was last
 * cleared)
 * 1: RX_PLL_LOCK was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . RX_PLL_LOCK_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_PLL_LOCK_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_PLL_LOCK_HI_STICKY  VTSS_BIT(17)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_PLL_LOCK_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * RX_PLL_LOCK input pin was detected deasserted (since this bit was last
 * cleared).
 *
 * \details 
 * 0: RX_PLL_LOCK was not detected deasserted (since this bit was last
 * cleared)
 * 1: RX_PLL_LOCK was detected deasserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . RX_PLL_LOCK_LO_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_PLL_LOCK_LO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_PLL_LOCK_LO_STICKY  VTSS_BIT(16)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_PLL_LOCK_LO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * XFI RX_LOS input pin was detected asserted (since this bit was last
 * cleared).
 *
 * \details 
 * 0: RX_LOS was not detected asserted (since this bit was last cleared)
 * 1: RX_LOS was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . RX_LOS_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_LOS_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_LOS_HI_STICKY  VTSS_BIT(15)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_LOS_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * XFI RX_LOS input pin was detected deasserted (since this bit was last
 * cleared)
 *
 * \details 
 * 0: RX_LOS was not detected deasserted (since this bit was last cleared)
 * 1: RX_LOS was detected deasserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . RX_LOS_LO_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_LOS_LO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_LOS_LO_STICKY  VTSS_BIT(14)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RX_LOS_LO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * HSS11G macro RXSIGDET output port was detected asserted (since this bit
 * was last cleared)
 *
 * \details 
 * 0: RXSIGDET was not detected asserted (since this bit was last cleared)
 * 1: RXSIGDET was detected asserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . RXSIGDET_HI_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RXSIGDET_HI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RXSIGDET_HI_STICKY  VTSS_BIT(13)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RXSIGDET_HI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * HSS11G macro RXSIGDET output port was detected deasserted (since this
 * bit was last cleared)
 *
 * \details 
 * 0: RXSIGDET was not detected deasserted (since this bit was last
 * cleared)
 * 1: RXSIGDET was detected deasserted (since this bit was last cleared)
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STICKY . RXSIGDET_LO_STICKY
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RXSIGDET_LO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RXSIGDET_LO_STICKY  VTSS_BIT(12)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STICKY_RXSIGDET_LO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/** 
 * \brief XFI HSS macro sticky interrupt masks (enables) 
 *
 * \details
 * Register: \a XFI_SHELL:XFI_CONTROL:HSS_MASK
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Mask (enable) a XFI_INT if dft_no_sync is asserted
 *
 * \details 
 * 0: Inhibit dft_no_sync from generating a XFI_INT
 * 1: Enable dft_no_sync to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_NO_SYNC_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_NO_SYNC_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_NO_SYNC_HI_MASK  VTSS_BIT(31)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_NO_SYNC_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if dft_no_sync is not asserted
 *
 * \details 
 * 0: Inhibit dft_no_sync from generating a XFI_INT
 * 1: Enable dft_no_sync to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_NO_SYNC_LO_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_NO_SYNC_LO_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_NO_SYNC_LO_MASK  VTSS_BIT(30)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_NO_SYNC_LO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if dft_instable is asserted
 *
 * \details 
 * 0: Inhibit dft_instable from generating a XFI_INT
 * 1: Enable dft_instable to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_INSTABLE_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INSTABLE_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INSTABLE_HI_MASK  VTSS_BIT(29)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INSTABLE_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if dft_instable is not asserted
 *
 * \details 
 * 0: Inhibit dft_instable from generating a XFI_INT
 * 1: Enable dft_instable to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_INSTABLE_LO_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INSTABLE_LO_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INSTABLE_LO_MASK  VTSS_BIT(28)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INSTABLE_LO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if dft_incomplete is asserted
 *
 * \details 
 * 0: Inhibit dft_incomplete from generating a XFI_INT
 * 1: Enable dft_incomplete to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_INCOMPLETE_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INCOMPLETE_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INCOMPLETE_HI_MASK  VTSS_BIT(27)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INCOMPLETE_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if dft_incomplete is not asserted
 *
 * \details 
 * 0: Inhibit dft_incomplete from generating a XFI_INT
 * 1: Enable dft_incomplete to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_INCOMPLETE_LO_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INCOMPLETE_LO_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INCOMPLETE_LO_MASK  VTSS_BIT(26)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_INCOMPLETE_LO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if DFT_ACTIVE is asserted
 *
 * \details 
 * 0: Inhibit dft_active from generating a XFI_INT
 * 1: Enable dft_active to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_ACTIVE_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_ACTIVE_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_ACTIVE_HI_MASK  VTSS_BIT(25)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_ACTIVE_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if DFT_ACTIVE is not asserted
 *
 * \details 
 * 0: Inhibit dft_active from generating a XFI_INT
 * 1: Enable dft_active to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_ACTIVE_LO_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_ACTIVE_LO_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_ACTIVE_LO_MASK  VTSS_BIT(24)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_ACTIVE_LO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if dft_stuck_at is asserted
 *
 * \details 
 * 0: Inhibit dft_stuck_at from generating a XFI_INT
 * 1: Enable dft_stuck_at to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . DFT_STUCK_AT_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_STUCK_AT_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_STUCK_AT_HI_MASK  VTSS_BIT(22)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_DFT_STUCK_AT_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if IF_PLL_LOCK_HI_STICKY is asserted
 *
 * \details 
 * 0: Inhibit TX_FIFO_LOS_HI_STICKY from generating a XFI_INT
 * 1: Enable TX_FIFO_LOSss_HI_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . TX_FIFO_LOS_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_FIFO_LOS_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_FIFO_LOS_HI_MASK  VTSS_BIT(21)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_FIFO_LOS_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if TX_PLL_LOCK_HI_STICKY is asserted
 *
 * \details 
 * 0: Inhibit TX_PLL_LOCK_HI_STICKY from generating a XFI_INT
 * 1: Enable TX_PLL_LOCK_HI_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . TX_PLL_LOCK_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_PLL_LOCK_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_PLL_LOCK_HI_MASK  VTSS_BIT(19)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_PLL_LOCK_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if TX_PLL_LOCK_LO_STICKY is asserted
 *
 * \details 
 * 0: Inhibit TX_PLL_LOCK_LO_STICKY from generating a XFI_INT
 * 1: Enable TX_PLL_LOCK_LO_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . TX_PLL_LOCK_LO_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_PLL_LOCK_LO_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_PLL_LOCK_LO_MASK  VTSS_BIT(18)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_TX_PLL_LOCK_LO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if RX_PLL_LOCK_HI_STICKY is asserted
 *
 * \details 
 * 0: Inhibit RX_PLL_LOCK_HI_STICKY from generating a XFI_INT
 * 1: Enable RX_PLL_LOCK_HI_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . RX_PLL_LOCK_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_PLL_LOCK_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_PLL_LOCK_HI_MASK  VTSS_BIT(17)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_PLL_LOCK_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if RX_PLL_LOCK_LO_STICKY is asserted
 *
 * \details 
 * 0: Inhibit RX_PLL_LOCK_LO_STICKY from generating a XFI_INT
 * 1: Enable RX_PLL_LOCK_LO_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . RX_PLL_LOCK_LO_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_PLL_LOCK_LO_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_PLL_LOCK_LO_MASK  VTSS_BIT(16)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_PLL_LOCK_LO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if RX_LOS_HI_STICKY is asserted
 *
 * \details 
 * 0: Inhibit RX_LOS_HI_STICKY from generating a XFI_INT
 * 1: Enable RX_LOS_HI_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . RX_LOS_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_LOS_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_LOS_HI_MASK  VTSS_BIT(15)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_LOS_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if RX_LOS_LO_STICKY is asserted
 *
 * \details 
 * 0: Inhibit RX_LOS_LO_STICKY from generating a XFI_INT
 * 1: Enable RX_LOS_LO_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . RX_LOS_LO_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_LOS_LO_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_LOS_LO_MASK  VTSS_BIT(14)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_RX_LOS_LO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if RXSIGDET_HI_STICKY is asserted
 *
 * \details 
 * 0: Inhibit RXSIGDET_HI_STICKY from generating a XFI_INT
 * 1: Enable the RXSIGDET_HI_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . RXSIGDET_HI_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_RXSIGDET_HI_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_RXSIGDET_HI_MASK  VTSS_BIT(13)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_RXSIGDET_HI_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Mask (enable) a XFI_INT if RXSIGDET_LO_STICKY is asserted
 *
 * \details 
 * 0: Inhibit RXSIGDET_LO_STICKY from generating a XFI_INT
 * 1: Enable RXSIGDET_LO_STICKY to generate a XFI_INT
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_MASK . RXSIGDET_LO_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_MASK_RXSIGDET_LO_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_MASK_RXSIGDET_LO_MASK  VTSS_BIT(12)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_MASK_RXSIGDET_LO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/** 
 * \brief XFI HSS macro current status
 *
 * \details
 * Register: \a XFI_SHELL:XFI_CONTROL:HSS_STATUS
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_HSS_STATUS(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * TX_FIFO loss of sync 
 * This can occur if the core clock sourcing the Tx port of the XFI is out
 * of phase with the XFI Tx clock, or if the core clock glitches.
 *
 * \details 
 * 0: TX_FIFO is not out of sync
 * 1: TX_FIFO is out of sync
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STATUS . TX_FIFO_LOS_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STATUS_TX_FIFO_LOS_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STATUS_TX_FIFO_LOS_STATUS  VTSS_BIT(20)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STATUS_TX_FIFO_LOS_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * RC-PLL lock status of Serializer
 *
 * \details 
 * 0: RC-PLL is not locked
 * 1: RC-PLL is locked
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STATUS . TX_PLL_LOCK_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STATUS_TX_PLL_LOCK_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STATUS_TX_PLL_LOCK_STATUS  VTSS_BIT(18)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STATUS_TX_PLL_LOCK_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * RC-PLL lock status of Deserializer
 *
 * \details 
 * 0: RC-PLL is not locked
 * 1: RC-PLL is locked
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STATUS . RX_PLL_LOCK_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RX_PLL_LOCK_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RX_PLL_LOCK_STATUS  VTSS_BIT(16)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RX_PLL_LOCK_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Current value of XFI LOS pin driven by HSS XFP/SFP+
 *
 * \details 
 * 0: Pin is driven low
 * 1: Pin is driven high
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STATUS . RX_LOS_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RX_LOS_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RX_LOS_STATUS  VTSS_BIT(14)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RX_LOS_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Signal detect indicator
 *
 * \details 
 * 0: No signal
 * 1: Active signal detected on the serial input
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_HSS_STATUS . RXSIGDET_STATUS
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RXSIGDET_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RXSIGDET_STATUS  VTSS_BIT(12)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_HSS_STATUS_RXSIGDET_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/** 
 * \brief Data valid detect control register.
 *
 * \details
 * Data valid detect control register. Selects the sources for valid data
 * detection.
 * Controls various functions in the deserializer macro which are swiched
 * when the digital logic has detected a valid signal.
 * Note: The three possible sources are first masked and than ORed
 * together.
 *
 * Register: \a XFI_SHELL:XFI_CONTROL:DATA_VALID_DETECT_CTRL
 *
 * @param target A \a ::vtss_target_XFI_SHELL_e target
 */
#define VTSS_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL(target)  VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Enable OTN LOF to control signal detect.
 *
 * \details 
 * 0: Inhibit OTN LOF to control signal detect.
 * 1: Enable OTN LOF to control signal detect.
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL . OTN_DETECT_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_OTN_DETECT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_OTN_DETECT_MASK  VTSS_BIT(2)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_OTN_DETECT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable eWIS LOF to control signal detect.
 *
 * \details 
 * 0: Inhibit eWIS LOF to control signal detect.
 * 1: Enable eWIS LOF to control signal detect.
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL . EWIS_DETECT_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_EWIS_DETECT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_EWIS_DETECT_MASK  VTSS_BIT(1)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_EWIS_DETECT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable PCS lock to control signal detect.
 *
 * \details 
 * 0: Inhibit PCS lock to control signal detect.
 * 1: Enable PCS lock to control signal detect.
 *
 * Field: ::VTSS_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL . PCS_DETECT_MASK
 */
#define  VTSS_F_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_PCS_DETECT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_PCS_DETECT_MASK  VTSS_BIT(0)
#define  VTSS_X_XFI_SHELL_XFI_CONTROL_DATA_VALID_DETECT_CTRL_PCS_DETECT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_JAGUAR2_REGS_XFI_SHELL_H_ */
