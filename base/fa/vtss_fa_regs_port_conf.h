/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_FA_REGS_PORT_CONF_H_
#define _VTSS_FA_REGS_PORT_CONF_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a PORT_CONF
 *
 * Configuration of top level multiplexer and extender.
 *
 ***********************************************************************/

/**
 * Register Group: \a PORT_CONF:HW_CFG
 *
 * Hardware Configuration
 */


/** 
 * \brief Configure mode of DEV5G devices.
 *
 * \details
 * Configure mode of DEV5G devices.

 *
 * Register: \a PORT_CONF:HW_CFG:DEV5G_MODES
 */
#define VTSS_PORT_CONF_DEV5G_MODES           VTSS_IOREG(VTSS_TO_PORT_CONF,0x0)

/** 
 * \brief
 * Configure mode of DEV5G D0 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D0_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D0_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D0_MODE  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D0_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Configure mode of DEV5G D1 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D1_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D1_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D1_MODE  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D1_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Configure mode of DEV5G D2 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D2_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D2_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D2_MODE  VTSS_BIT(2)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D2_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Configure mode of DEV5G D3 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D3_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D3_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D3_MODE  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D3_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Configure mode of DEV5G D4device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D4_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D4_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D4_MODE  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D4_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Configure mode of DEV5G D5 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D5_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D5_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D5_MODE  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D5_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Configure mode of DEV5G D6 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D6_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D6_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D6_MODE  VTSS_BIT(6)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D6_MODE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Configure mode of DEV5G D7 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D7_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D7_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D7_MODE  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D7_MODE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Configure mode of DEV5G D7 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D8_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D8_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D8_MODE  VTSS_BIT(8)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D8_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Configure mode of DEV5G D9 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D9_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D9_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D9_MODE  VTSS_BIT(9)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D9_MODE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Configure mode of DEV5G D10 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D10_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D10_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D10_MODE  VTSS_BIT(10)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D10_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Configure mode of DEV5G D11 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D11_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D11_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D11_MODE  VTSS_BIT(11)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D11_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Configure mode of DEV5G D64 device.
 *
 * \details 
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D64_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D64_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D64_MODE  VTSS_BIT(12)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D64_MODE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/** 
 * \brief Configure mode of DEV10G devices.
 *
 * \details
 * Configure mode of DEV10G devices.

 *
 * Register: \a PORT_CONF:HW_CFG:DEV10G_MODES
 */
#define VTSS_PORT_CONF_DEV10G_MODES          VTSS_IOREG(VTSS_TO_PORT_CONF,0x1)

/** 
 * \brief
 * Configure mode of DEV10G D12 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D12_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D12_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D12_MODE  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D12_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Configure mode of DEV10G D13 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D13_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D13_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D13_MODE  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D13_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Configure mode of DEV10G D14 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D14_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D14_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D14_MODE  VTSS_BIT(2)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D14_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Configure mode of DEV10G D15 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D15_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D15_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D15_MODE  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D15_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Configure mode of DEV10G D48 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D48_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D48_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D48_MODE  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D48_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Configure mode of DEV10G D49 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D49_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D49_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D49_MODE  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D49_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Configure mode of DEV10G D50 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D50_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D50_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D50_MODE  VTSS_BIT(6)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D50_MODE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Configure mode of DEV10G D51 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D51_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D51_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D51_MODE  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D51_MODE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Configure mode of DEV10G D52 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D52_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D52_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D52_MODE  VTSS_BIT(8)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D52_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Configure mode of DEV10G D53 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D53_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D53_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D53_MODE  VTSS_BIT(9)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D53_MODE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Configure mode of DEV10G D54 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D54_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D54_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D54_MODE  VTSS_BIT(10)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D54_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Configure mode of DEV10G D55 device.
 *
 * \details 
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D55_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D55_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D55_MODE  VTSS_BIT(11)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D55_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)


/** 
 * \brief Configure mode of DEV25G devices.
 *
 * \details
 * Configure mode of DEV25G devices.
 *
 * Register: \a PORT_CONF:HW_CFG:DEV25G_MODES
 */
#define VTSS_PORT_CONF_DEV25G_MODES          VTSS_IOREG(VTSS_TO_PORT_CONF,0x2)

/** 
 * \brief
 * Configure mode of DEV25G D56 device.
 *
 * \details 
 * 0: DEV25G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV25G_MODES . DEV25G_D56_MODE
 */
#define  VTSS_F_PORT_CONF_DEV25G_MODES_DEV25G_D56_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_DEV25G_MODES_DEV25G_D56_MODE  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_DEV25G_MODES_DEV25G_D56_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Configure mode of DEV25G D57 device.
 *
 * \details 
 * 0: DEV25G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV25G_MODES . DEV25G_D57_MODE
 */
#define  VTSS_F_PORT_CONF_DEV25G_MODES_DEV25G_D57_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_DEV25G_MODES_DEV25G_D57_MODE  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_DEV25G_MODES_DEV25G_D57_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Configure mode of DEV25G D58 device.
 *
 * \details 
 * 0: DEV25G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV25G_MODES . DEV25G_D58_MODE
 */
#define  VTSS_F_PORT_CONF_DEV25G_MODES_DEV25G_D58_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PORT_CONF_DEV25G_MODES_DEV25G_D58_MODE  VTSS_BIT(2)
#define  VTSS_X_PORT_CONF_DEV25G_MODES_DEV25G_D58_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Configure mode of DEV25G D59 device.
 *
 * \details 
 * 0: DEV25G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV25G_MODES . DEV25G_D59_MODE
 */
#define  VTSS_F_PORT_CONF_DEV25G_MODES_DEV25G_D59_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_DEV25G_MODES_DEV25G_D59_MODE  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_DEV25G_MODES_DEV25G_D59_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Configure mode of DEV25G D60 device.
 *
 * \details 
 * 0: DEV25G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV25G_MODES . DEV25G_D60_MODE
 */
#define  VTSS_F_PORT_CONF_DEV25G_MODES_DEV25G_D60_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_DEV25G_MODES_DEV25G_D60_MODE  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_DEV25G_MODES_DEV25G_D60_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Configure mode of DEV25G D61 device.
 *
 * \details 
 * 0: DEV25G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV25G_MODES . DEV25G_D61_MODE
 */
#define  VTSS_F_PORT_CONF_DEV25G_MODES_DEV25G_D61_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_DEV25G_MODES_DEV25G_D61_MODE  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_DEV25G_MODES_DEV25G_D61_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Configure mode of DEV25G D62 device.
 *
 * \details 
 * 0: DEV25G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV25G_MODES . DEV25G_D62_MODE
 */
#define  VTSS_F_PORT_CONF_DEV25G_MODES_DEV25G_D62_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PORT_CONF_DEV25G_MODES_DEV25G_D62_MODE  VTSS_BIT(6)
#define  VTSS_X_PORT_CONF_DEV25G_MODES_DEV25G_D62_MODE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Configure mode of DEV25G D63 device.
 *
 * \details 
 * 0: DEV25G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV25G_MODES . DEV25G_D63_MODE
 */
#define  VTSS_F_PORT_CONF_DEV25G_MODES_DEV25G_D63_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_DEV25G_MODES_DEV25G_D63_MODE  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_DEV25G_MODES_DEV25G_D63_MODE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief Enable QSGMII mode for different ports
 *
 * \details
 * Enable QSGMII mode for different ports
 * 
 * Note:  This setting can be overruled from USGMII enable and USXGMII
 * enable configuration as some Dev5G and Dev2G5 devices are used in
 * multiple modes.
 *
 * Register: \a PORT_CONF:HW_CFG:QSGMII_ENA
 */
#define VTSS_PORT_CONF_QSGMII_ENA            VTSS_IOREG(VTSS_TO_PORT_CONF,0x3)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV5G_0, DEV5G_1, DEV5G_2, and
 * DEV5G_3 via SerDes6G_13
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_0
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_0  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV5G_4, DEV5G_5, DEV5G_6, and
 * DEV5G_7 via SerDes6G_14
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_1
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_1  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV5G_8, DEV5G_9, DEV5G_10,
 * and DEV5G_11 via SerDes6G_15
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_2
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_2  VTSS_BIT(2)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV5G_12, DEV5G_13, DEV5G_14,
 * and DEV5G_15 via SerDes6G_16
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_3
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_3(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_3  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_3(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV2G5_16, DEV2G5_17,
 * DEV2G5_18, and DEV2G5_19 via SerDes10G_0
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_4
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_4  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV2G5_20, DEV2G5_21,
 * DEV2G5_22, and DEV2G5_23 via SerDes10G_1
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_5
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_5(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_5  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_5(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV2G5_24, DEV2G5_25,
 * DEV2G5_26, and DEV2G5_27 via SerDes10G_2
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_6
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_6  VTSS_BIT(6)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV2G5_28, DEV2G5_29,
 * DEV2G5_30, and DEV2G5_31 via SerDes10G_3
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_7
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_7(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_7  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_7(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV2G5_32, DEV2G5_33,
 * DEV2G5_34, and DEV2G5_35 via SerDes10G_4
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_8
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_8(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_8  VTSS_BIT(8)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_8(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV2G5_36, DEV2G5_37,
 * DEV2G5_38, and DEV2G5_39 via SerDes10G_5
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_9
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_9(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_9  VTSS_BIT(9)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_9(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV2G5_40, DEV2G5_41,
 * DEV2G5_42, and DEV2G5_43 via SerDes10G_6
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_10
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_10(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_10  VTSS_BIT(10)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_10(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set bit to enable QSGMII mode for devices DEV2G5_44, DEV2G5_45,
 * DEV2G5_46, and DEV2G5_47 via SerDes10G_7
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_ENA . QSGMII_ENA_11
 */
#define  VTSS_F_PORT_CONF_QSGMII_ENA_QSGMII_ENA_11(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PORT_CONF_QSGMII_ENA_QSGMII_ENA_11  VTSS_BIT(11)
#define  VTSS_X_PORT_CONF_QSGMII_ENA_QSGMII_ENA_11(x)  VTSS_EXTRACT_BITFIELD(x,11,1)


/** 
 * \brief Enable USGMII mode for different ports
 *
 * \details
 * Enable USGMII mode for different ports
 * 
 * Note:  This setting can be overruled from USXGMII enable configuration
 * as some Dev5G and Dev2G5 devices are used in multiple modes.
 *
 * Register: \a PORT_CONF:HW_CFG:USGMII_ENA
 */
#define VTSS_PORT_CONF_USGMII_ENA            VTSS_IOREG(VTSS_TO_PORT_CONF,0x4)

/** 
 * \brief
 * Set bit to enable USGMII mode for devices Dev5G_0, Dev5G_1, Dev5G_2,
 * Dev5G_3, Dev5G_4, Dev5G_5, Dev5G_6 and Dev5G_7 via SerDes10G_0
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USGMII_ENA . USGMII_ENA_0
 */
#define  VTSS_F_PORT_CONF_USGMII_ENA_USGMII_ENA_0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_USGMII_ENA_USGMII_ENA_0  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_USGMII_ENA_USGMII_ENA_0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Set bit to enable USGMII mode for devices Dev5G_8, Dev5G_9, Dev5G_10,
 * Dev5G_11, Dev5G_12, Dev5G_13, Dev5G_14 and Dev5G_15 via SerDes10G_1
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USGMII_ENA . USGMII_ENA_1
 */
#define  VTSS_F_PORT_CONF_USGMII_ENA_USGMII_ENA_1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_USGMII_ENA_USGMII_ENA_1  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_USGMII_ENA_USGMII_ENA_1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set bit to enable USGMII mode for devices Dev2G5_16, Dev2G5_17,
 * Dev2G5_18, Dev2G5_19, Dev2G5_20, Dev2G5_21, Dev2G5_22 and Dev2G5_23 via
 * SerDes10G_2 
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USGMII_ENA . USGMII_ENA_2
 */
#define  VTSS_F_PORT_CONF_USGMII_ENA_USGMII_ENA_2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PORT_CONF_USGMII_ENA_USGMII_ENA_2  VTSS_BIT(2)
#define  VTSS_X_PORT_CONF_USGMII_ENA_USGMII_ENA_2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set bit to enable USGMII mode for devices Dev2G5_24, Dev2G5_25,
 * Dev2G5_26, Dev2G5_27, Dev2G5_28, Dev2G5_29, Dev2G5_30 and Dev2G5_31 via
 * SerDes10G_3 
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USGMII_ENA . USGMII_ENA_3
 */
#define  VTSS_F_PORT_CONF_USGMII_ENA_USGMII_ENA_3(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_USGMII_ENA_USGMII_ENA_3  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_USGMII_ENA_USGMII_ENA_3(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set bit to enable USGMII mode for devices Dev2G5_32, Dev2G5_33,
 * Dev2G5_34, Dev2G5_35, Dev2G5_36, Dev2G5_37, Dev2G5_38 and Dev2G5_39 via
 * SerDes10G_4
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USGMII_ENA . USGMII_ENA_4
 */
#define  VTSS_F_PORT_CONF_USGMII_ENA_USGMII_ENA_4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_USGMII_ENA_USGMII_ENA_4  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_USGMII_ENA_USGMII_ENA_4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set bit to enable USGMII mode for devices Dev2G5_40, Dev2G5_41,
 * Dev2G5_42, Dev2G5_43, Dev2G5_44, Dev2G5_45, Dev2G5_46 and Dev2G5_47 via
 * SerDes10G_5 
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USGMII_ENA . USGMII_ENA_5
 */
#define  VTSS_F_PORT_CONF_USGMII_ENA_USGMII_ENA_5(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_USGMII_ENA_USGMII_ENA_5  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_USGMII_ENA_USGMII_ENA_5(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief Enable USXGMII mode for different ports
 *
 * \details
 * Enable USXGMII mode for different ports
 *
 * Register: \a PORT_CONF:HW_CFG:USXGMII_ENA
 */
#define VTSS_PORT_CONF_USXGMII_ENA           VTSS_IOREG(VTSS_TO_PORT_CONF,0x5)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_0 and Dev2G5_32 via
 * SerDes6G_1
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_0
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_0  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_1 and Dev2G5_33 via
 * SerDes6G_2
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_1
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_1  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_2 and Dev2G5_34 via
 * SerDes6G_3
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_2
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_2  VTSS_BIT(2)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_3 and Dev2G5_35 via
 * SerDes6G_4
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_3
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_3(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_3  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_3(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_4 and Dev2G5_36 via
 * SerDes6G_5
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_4
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_4  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_5 and Dev2G5_37 via
 * SerDes6G_6
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_5
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_5(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_5  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_5(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_6 and Dev2G5_38 via
 * SerDes6G_7
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_6
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_6  VTSS_BIT(6)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_7 and Dev2G5_39 via
 * SerDes6G_8
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_7
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_7(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_7  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_7(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_8 and Dev2G5_40 via
 * SerDes6G_9
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_8
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_8(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_8  VTSS_BIT(8)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_8(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_9 and Dev2G5_41 via
 * SerDes6G_10
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_9
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_9(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_9  VTSS_BIT(9)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_9(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_10 and Dev2G5_42 via
 * SerDes6G_11
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_10
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_10(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_10  VTSS_BIT(10)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_10(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_11 and Dev2G5_43 via
 * SerDes6G_12
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_11
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_11(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_11  VTSS_BIT(11)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_11(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_12 and Dev2G5_44 via
 * SerDes6G_13
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_12
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_12(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_12  VTSS_BIT(12)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_12(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_13 and Dev2G5_45 via
 * SerDes6G_14
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_13
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_13(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_13  VTSS_BIT(13)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_13(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_14 and Dev2G5_46 via
 * SerDes6G_15
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_14
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_14(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_14  VTSS_BIT(14)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_14(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev5G_15 and Dev2G5_47 via
 * SerDes6G_16
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_15
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_15(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_15  VTSS_BIT(15)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_15(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_48, Dev5G_0, Dev2G5_16
 * and Dev2G5_32 or subset depending on speed via SerDes10G_0
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_16
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_16(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_16  VTSS_BIT(16)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_16(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_49, Dev5G_1, Dev2G5_17
 * and Dev2G5_33 or subset depending on speed via SerDes10G_1
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_17
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_17(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_17  VTSS_BIT(17)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_17(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_50, Dev5G_2, Dev2G5_18
 * and Dev2G5_34 or subset depending on speed via SerDes10G_2
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_18
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_18(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_18  VTSS_BIT(18)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_18(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_51, Dev5G_3, Dev2G5_19
 * and Dev2G5_35 or subset depending on speed via SerDes10G_3
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_19
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_19(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_19  VTSS_BIT(19)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_19(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_52, Dev5G_4, Dev2G5_20
 * and Dev2G5_36 or subset depending on speed via SerDes10G_4
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_20
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_20(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_20  VTSS_BIT(20)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_20(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_53, Dev5G_5, Dev2G5_21
 * and Dev2G5_37 or subset depending on speed via SerDes10G_5
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_21
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_21(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_21  VTSS_BIT(21)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_21(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_54, Dev5G_6, Dev2G5_22
 * and Dev2G5_38 or subset depending on speed via SerDes10G_6
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_22
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_22(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_22  VTSS_BIT(22)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_22(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_55, Dev5G_7, 
 * Dev2G5_23 and Dev2G5_39 or subset depending on speed via SerDes10G_7
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_23
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_23(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_23  VTSS_BIT(23)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_23(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_56, Dev5G_8, Dev2G5_24
 * and Dev2G5_40 or subset depending on speed via SerDes10G_8
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_24
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_24(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_24  VTSS_BIT(24)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_24(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_57, Dev5G_9, Dev2G5_25
 * and Dev2G5_41 or subset depending on speed via SerDes10G_9
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_25
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_25(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_25  VTSS_BIT(25)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_25(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_58, Dev5G_10,
 * Dev2G5_26 and Dev2G5_42 or subset depending on speed via SerDes10G_10
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_26
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_26(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_26  VTSS_BIT(26)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_26(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_59, Dev5G_11 Dev2G5_27
 * and Dev2G5_43 or subset depending on speed via SerDes10G_0
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_27
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_27(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_27  VTSS_BIT(27)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_27(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_60, Dev5G_12,
 * Dev2G5_28 and Dev2G5_44 or subset depending on speed via SerDes10G_12
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_28
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_28(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_28  VTSS_BIT(28)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_28(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_61, Dev5G_13,
 * Dev2G5_29 and Dev2G5_45 or subset depending on speed via SerDes10G_13
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_29
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_29(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_29  VTSS_BIT(29)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_29(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_62, Dev5G_14,
 * Dev2G5_30 and Dev2G5_46 or subset depending on speed via SerDes10G_14
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_30
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_30(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_30  VTSS_BIT(30)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_30(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Set bit to enable USXGMII mode for devices Dev10G_63, Dev5G_25,
 * Dev2G5_31 and Dev2G5_47 or subset depending on speed via SerDes10G_15
 *
 * \details 
 * 0 : disabled
 * 1 : enabled
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_ENA . USXGMII_ENA_31
 */
#define  VTSS_F_PORT_CONF_USXGMII_ENA_USXGMII_ENA_31(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PORT_CONF_USXGMII_ENA_USXGMII_ENA_31  VTSS_BIT(31)
#define  VTSS_X_PORT_CONF_USXGMII_ENA_USXGMII_ENA_31(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * Register Group: \a PORT_CONF:QSGMII_CFG_STAT
 *
 * QSGMII Configuration
 */


/** 
 * \brief QSGMII Configuration Register
 *
 * \details
 * QSGMII configuration register
 *
 * Register: \a PORT_CONF:QSGMII_CFG_STAT:QSGMII_CFG
 *
 * @param gi Replicator: x_NUM_OF_QSGMII_EXT (??), 0-5
 */
#define VTSS_PORT_CONF_QSGMII_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x6,gi,2,0,0)

/** 
 * \brief
 * Flip or swap lanes (lane 0 with lane 3, lane 1 with lane 2)
 *
 * \details 
 * 0: Disable lane flipping
 * 1: Enable lane flipping
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_CFG . FLIP_LANES
 */
#define  VTSS_F_PORT_CONF_QSGMII_CFG_FLIP_LANES(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_QSGMII_CFG_FLIP_LANES  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_QSGMII_CFG_FLIP_LANES(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Disable hysteresis of synchronization state machine
 *
 * \details 
 * 0: Enable hysteresis
 * 1: Disable hysteresis
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_CFG . SHYST_DIS
 */
#define  VTSS_F_PORT_CONF_QSGMII_CFG_SHYST_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PORT_CONF_QSGMII_CFG_SHYST_DIS  VTSS_BIT(6)
#define  VTSS_X_PORT_CONF_QSGMII_CFG_SHYST_DIS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable 8b10b error propagation (8b10b errors code-groups are replaced by
 * K30.7 error symbols)
 *
 * \details 
 * 0: Disable error propagation
 * 1: Enable error propagation
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_CFG . E_DET_ENA
 */
#define  VTSS_F_PORT_CONF_QSGMII_CFG_E_DET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_QSGMII_CFG_E_DET_ENA  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_QSGMII_CFG_E_DET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Use /I1/ during idle sequencing only
 *
 * \details 
 * 0: Use /I1/ and /I2/
 * 1: Use /I1/ only
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_CFG . USE_I1_ENA
 */
#define  VTSS_F_PORT_CONF_QSGMII_CFG_USE_I1_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_QSGMII_CFG_USE_I1_ENA  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_QSGMII_CFG_USE_I1_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief QSGMII Status Register
 *
 * \details
 * QSGMII Receive Status Register
 *
 * Register: \a PORT_CONF:QSGMII_CFG_STAT:QSGMII_STAT
 *
 * @param gi Replicator: x_NUM_OF_QSGMII_EXT (??), 0-5
 */
#define VTSS_PORT_CONF_QSGMII_STAT(gi)       VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x6,gi,2,0,1)

/** 
 * \brief
 * Variable RX Bit Delay from barrel shifter
 *
 * \details 
 * delay is calculeted as  N x 200ps  with N=[0;39]
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_STAT . DELAY_VAR
 */
#define  VTSS_F_PORT_CONF_QSGMII_STAT_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_PORT_CONF_QSGMII_STAT_DELAY_VAR     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_PORT_CONF_QSGMII_STAT_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Synchronization status of connected ports.Each bit is indicated the
 * status of a port, LSB is port 0 up to MSB for port 3
 *
 * \details 
 * 0 :	out of sync
 * 1 :	in sync
 *
 * Field: ::VTSS_PORT_CONF_QSGMII_STAT . SYNC_STAT_PORTS
 */
#define  VTSS_F_PORT_CONF_QSGMII_STAT_SYNC_STAT_PORTS(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PORT_CONF_QSGMII_STAT_SYNC_STAT_PORTS     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PORT_CONF_QSGMII_STAT_SYNC_STAT_PORTS(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Set when QSGMII channel has successfully synchronized on K28.1
 * code-group, this field is only valid when
 * PORT_CONF:QSGMII_CFG_STAT:QSGMII_CFG.SHYST_DIS is 0.
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_QSGMII_STAT . SYNC_STAT
 */
#define  VTSS_F_PORT_CONF_QSGMII_STAT_SYNC_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PORT_CONF_QSGMII_STAT_SYNC_STAT  VTSS_BIT(16)
#define  VTSS_X_PORT_CONF_QSGMII_STAT_SYNC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * Register Group: \a PORT_CONF:USGMII_CFG_STAT
 *
 * USGMII Configuration and Status Register
 */


/** 
 * \brief USGMII Configuration Register
 *
 * \details
 * USGMII configuration register
 *
 * Register: \a PORT_CONF:USGMII_CFG_STAT:USGMII_CFG
 *
 * @param gi Replicator: x_NUM_OF_USGMII_EXT (??), 0-5
 */
#define VTSS_PORT_CONF_USGMII_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x12,gi,2,0,0)

/** 
 * \brief
 * Bypass TX Scrambler
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USGMII_CFG . BYPASS_SCRAM
 */
#define  VTSS_F_PORT_CONF_USGMII_CFG_BYPASS_SCRAM(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PORT_CONF_USGMII_CFG_BYPASS_SCRAM  VTSS_BIT(9)
#define  VTSS_X_PORT_CONF_USGMII_CFG_BYPASS_SCRAM(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Bypass RX Descrambler
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USGMII_CFG . BYPASS_DESCRAM
 */
#define  VTSS_F_PORT_CONF_USGMII_CFG_BYPASS_DESCRAM(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PORT_CONF_USGMII_CFG_BYPASS_DESCRAM  VTSS_BIT(8)
#define  VTSS_X_PORT_CONF_USGMII_CFG_BYPASS_DESCRAM(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Flip or swap lanes (Quad mode: lane 0 with lane 3, lane 1 with lane 2,
 * Octal mode: lane 0 with lane 7, lane 1 with lane 6, ...)
 *
 * \details 
 * 0: Disable lane flipping
 * 1: Enable lane flipping
 *
 * Field: ::VTSS_PORT_CONF_USGMII_CFG . FLIP_LANES
 */
#define  VTSS_F_PORT_CONF_USGMII_CFG_FLIP_LANES(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_USGMII_CFG_FLIP_LANES  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_USGMII_CFG_FLIP_LANES(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Disable hysteresis of synchronization state machine
 *
 * \details 
 * 0: Enable hysteresis
 * 1: Disable hysteresis
 *
 * Field: ::VTSS_PORT_CONF_USGMII_CFG . SHYST_DIS
 */
#define  VTSS_F_PORT_CONF_USGMII_CFG_SHYST_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PORT_CONF_USGMII_CFG_SHYST_DIS  VTSS_BIT(6)
#define  VTSS_X_PORT_CONF_USGMII_CFG_SHYST_DIS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable 8b10b error propagation (8b10b errors code-groups are replaced by
 * K30.7 error symbols)
 *
 * \details 
 * 0: Disable error propagation
 * 1: Enable error propagation
 *
 * Field: ::VTSS_PORT_CONF_USGMII_CFG . E_DET_ENA
 */
#define  VTSS_F_PORT_CONF_USGMII_CFG_E_DET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_USGMII_CFG_E_DET_ENA  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_USGMII_CFG_E_DET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Use /I1/ during idle sequencing only
 *
 * \details 
 * 0: Use /I1/ and /I2/
 * 1: Use /I1/ only
 *
 * Field: ::VTSS_PORT_CONF_USGMII_CFG . USE_I1_ENA
 */
#define  VTSS_F_PORT_CONF_USGMII_CFG_USE_I1_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_USGMII_CFG_USE_I1_ENA  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_USGMII_CFG_USE_I1_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable quad port mode (QSGMII or Q-USGMII)
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USGMII_CFG . QUAD_MODE
 */
#define  VTSS_F_PORT_CONF_USGMII_CFG_QUAD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_USGMII_CFG_QUAD_MODE  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_USGMII_CFG_QUAD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief USGMII Status Register
 *
 * \details
 * USGMII status register
 *
 * Register: \a PORT_CONF:USGMII_CFG_STAT:USGMII_STAT
 *
 * @param gi Replicator: x_NUM_OF_USGMII_EXT (??), 0-5
 */
#define VTSS_PORT_CONF_USGMII_STAT(gi)       VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x12,gi,2,0,1)

/** 
 * \brief
 * Variable RX Bit Delay from barrel shifter
 *
 * \details 
 * delay is calculeted as  N x 200ps  with N=[0;39]
 *
 * Field: ::VTSS_PORT_CONF_USGMII_STAT . DELAY_VAR
 */
#define  VTSS_F_PORT_CONF_USGMII_STAT_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_PORT_CONF_USGMII_STAT_DELAY_VAR     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_PORT_CONF_USGMII_STAT_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Synchronization status of connected ports.Each bit is indicated the
 * status of a port, LSB is port 0 up to MSB for port 7.In QSGMII mode only
 * bits 0 to 3 are valid.
 *
 * \details 
 * 0 :	out of sync
 * 1 :	in sync
 *
 * Field: ::VTSS_PORT_CONF_USGMII_STAT . SYNC_STAT_PORTS
 */
#define  VTSS_F_PORT_CONF_USGMII_STAT_SYNC_STAT_PORTS(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PORT_CONF_USGMII_STAT_SYNC_STAT_PORTS     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PORT_CONF_USGMII_STAT_SYNC_STAT_PORTS(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Indicates if USGMII has successfully synchronized on K28.1 code-group
 * (shyst_dis must be cleared)
 *
 * \details 
 * 0: USGMII is out of sync
 * 1: USGMII has synchronized
 *
 * Field: ::VTSS_PORT_CONF_USGMII_STAT . SYNC_STAT
 */
#define  VTSS_F_PORT_CONF_USGMII_STAT_SYNC_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PORT_CONF_USGMII_STAT_SYNC_STAT  VTSS_BIT(16)
#define  VTSS_X_PORT_CONF_USGMII_STAT_SYNC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * Register Group: \a PORT_CONF:USXGMII_CFG
 *
 * USXGMII Configuration Register
 */


/** 
 * \brief USXGMII Configuration Register
 *
 * \details
 * USXGMII configuration register
 *
 * Register: \a PORT_CONF:USXGMII_CFG:USXGMII_CFG
 *
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-31
 */
#define VTSS_PORT_CONF_USXGMII_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x1e,gi,3,0,0)

/** 
 * \brief
 * Flip port 0 and 3 on MAC interface (TX and RX)
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . FLIP_PORT_03
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_FLIP_PORT_03(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_FLIP_PORT_03  VTSS_BIT(27)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_FLIP_PORT_03(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Flip port 1 and 2 on MAC interface (TX and RX)
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . FLIP_PORT_12
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_FLIP_PORT_12(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_FLIP_PORT_12  VTSS_BIT(26)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_FLIP_PORT_12(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Flip TX transmit data to SerDes (after gearboxing)
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . TX_FLIP_DATA
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_TX_FLIP_DATA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_TX_FLIP_DATA  VTSS_BIT(25)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_TX_FLIP_DATA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Flip RX receive data from SerDes (before gearboxing)
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . RX_FLIP_DATA
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_RX_FLIP_DATA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_RX_FLIP_DATA  VTSS_BIT(24)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_RX_FLIP_DATA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Number of sync headers required for block lock minus 1
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . SH_CNT_MAX
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_SH_CNT_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_SH_CNT_MAX     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_SH_CNT_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Bypass TX Scrambler
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . BYPASS_SCRAM
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_BYPASS_SCRAM(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_BYPASS_SCRAM  VTSS_BIT(9)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_BYPASS_SCRAM(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Bypass RX Descrambler
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . BYPASS_DESCRAM
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_BYPASS_DESCRAM(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_BYPASS_DESCRAM  VTSS_BIT(8)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_BYPASS_DESCRAM(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Generate IDLE instead of local fault (LF) to RX MAC
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . OOS_IDLE_GEN
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_OOS_IDLE_GEN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_OOS_IDLE_GEN  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_OOS_IDLE_GEN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Enable tranmit path of USXGMII extender
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . TX_ENA
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_TX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_TX_ENA  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_TX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable receive path of USXGMII extender
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . RX_ENA
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_RX_ENA  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Number of active ports (0: single port, 1: dual port, 2: quad port, 3:
 * reserved)
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_CFG . NUM_PORTS
 */
#define  VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PORT_CONF_USXGMII_CFG_NUM_PORTS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief USXGMII Alignment Marker Configuration Register
 *
 * \details
 * USXGMII alignment marker configuration register
 *
 * Register: \a PORT_CONF:USXGMII_CFG:USXGMII_AM_CFG
 *
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-31
 */
#define VTSS_PORT_CONF_USXGMII_AM_CFG(gi)    VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x1e,gi,3,0,1)

/** 
 * \brief
 * DEBUG: select AM marker source per word
 *
 * \details 
 * 0=default
 * 1=alternative
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_AM_CFG . AM_SRC_CFG
 */
#define  VTSS_F_PORT_CONF_USXGMII_AM_CFG_AM_SRC_CFG(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_PORT_CONF_USXGMII_AM_CFG_AM_SRC_CFG     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_PORT_CONF_USXGMII_AM_CFG_AM_SRC_CFG(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * DEBUG: First port number for which data will be sent directl after
 * alignment marker symbol
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_AM_CFG . FIRST_PORT
 */
#define  VTSS_F_PORT_CONF_USXGMII_AM_CFG_FIRST_PORT(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PORT_CONF_USXGMII_AM_CFG_FIRST_PORT     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PORT_CONF_USXGMII_AM_CFG_FIRST_PORT(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Alignment Marker Distance (default is 16400 66B blocks)
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_AM_CFG . AM_DISTANCE
 */
#define  VTSS_F_PORT_CONF_USXGMII_AM_CFG_AM_DISTANCE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PORT_CONF_USXGMII_AM_CFG_AM_DISTANCE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PORT_CONF_USXGMII_AM_CFG_AM_DISTANCE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief USXGMII Local remote Fault Sequence Length Register
 *
 * \details
 * USXGMII local/remote fault sequence length register
 *
 * Register: \a PORT_CONF:USXGMII_CFG:USXGMII_LFRF_SEQ
 *
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-31
 */
#define VTSS_PORT_CONF_USXGMII_LFRF_SEQ(gi)  VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x1e,gi,3,0,2)

/** 
 * \brief
 * Number of blocks transmiter sends out minimal in case ot port number
 * mismatch is detected (CWM port error)
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_LFRF_SEQ . LF_RF_SEQ_LEN
 */
#define  VTSS_F_PORT_CONF_USXGMII_LFRF_SEQ_LF_RF_SEQ_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_PORT_CONF_USXGMII_LFRF_SEQ_LF_RF_SEQ_LEN     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_PORT_CONF_USXGMII_LFRF_SEQ_LF_RF_SEQ_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

/**
 * Register Group: \a PORT_CONF:USXGMII_STAT
 *
 * USXGMII Status
 */


/** 
 * \brief USXGMII Status Register
 *
 * \details
 * USXGMII Receive Status Register
 *
 * Register: \a PORT_CONF:USXGMII_STAT:USXGMII_RX_STATUS
 *
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-31
 */
#define VTSS_PORT_CONF_USXGMII_RX_STATUS(gi)  VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x7e,gi,2,0,0)

/** 
 * \brief
 * Indicates if USXGMII has successfully synchronized on AM marker
 *
 * \details 
 * 0: USXGMII is out of sync
 * 1: USXGMII has synchronized
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_RX_STATUS . SYNC_STAT
 */
#define  VTSS_F_PORT_CONF_USXGMII_RX_STATUS_SYNC_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_USXGMII_RX_STATUS_SYNC_STAT  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_USXGMII_RX_STATUS_SYNC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * indicates if USXGMII extender has reached block lock state, 0: USXGMII
 * not in block lock state, 1: USXGMII in block lock state
 *
 * \details 
 * Field: ::VTSS_PORT_CONF_USXGMII_RX_STATUS . BLOCK_LOCK
 */
#define  VTSS_F_PORT_CONF_USXGMII_RX_STATUS_BLOCK_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_USXGMII_RX_STATUS_BLOCK_LOCK  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_USXGMII_RX_STATUS_BLOCK_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief USXGMII Status Register
 *
 * \details
 * USXGMII Receive Error Status Register
 *
 * Register: \a PORT_CONF:USXGMII_STAT:USXGMII_RX_ERR_STATUS
 *
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-31
 */
#define VTSS_PORT_CONF_USXGMII_RX_ERR_STATUS(gi)  VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x7e,gi,2,0,1)

/** 
 * \brief
 * Port number error detected on during alignment marker reception
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_RX_ERR_STATUS . CWM_PORTNO_ERR_STICKY
 */
#define  VTSS_F_PORT_CONF_USXGMII_RX_ERR_STATUS_CWM_PORTNO_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_USXGMII_RX_ERR_STATUS_CWM_PORTNO_ERR_STICKY  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_USXGMII_RX_ERR_STATUS_CWM_PORTNO_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Indicates that USXGMII has lost snchronization on AM marker,
 *
 * \details 
 * 1: USXGMII lost AM sync
 * 0: USXGMII: No loss of AM synch
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_RX_ERR_STATUS . SYNC_LOST_STICKY
 */
#define  VTSS_F_PORT_CONF_USXGMII_RX_ERR_STATUS_SYNC_LOST_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_USXGMII_RX_ERR_STATUS_SYNC_LOST_STICKY  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_USXGMII_RX_ERR_STATUS_SYNC_LOST_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Indicates that USXGMII has lost block lost,
 *
 * \details 
 * 1: USXGMII lost block lock
 * 0: USXGMII: No loss of block lock
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_PORT_CONF_USXGMII_RX_ERR_STATUS . BLOCK_LOCK_LOST_STICKY
 */
#define  VTSS_F_PORT_CONF_USXGMII_RX_ERR_STATUS_BLOCK_LOCK_LOST_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_USXGMII_RX_ERR_STATUS_BLOCK_LOCK_LOST_STICKY  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_USXGMII_RX_ERR_STATUS_BLOCK_LOCK_LOST_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_FA_REGS_PORT_CONF_H_ */
