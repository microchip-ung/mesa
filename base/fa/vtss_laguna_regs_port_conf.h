// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_PORT_CONF_H_
#define _VTSS_LAGUNA_REGS_PORT_CONF_H_

#include "vtss_laguna_regs_common.h"

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
 * Configure mode of DEV5G D4 device.
 *
 * \details
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D4_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D4_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D4_MODE  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D4_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D9_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D9_MODE  VTSS_BIT(2)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D9_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Configure mode of DEV5G D13 device.
 *
 * \details
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D13_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D13_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D13_MODE  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D13_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Configure mode of DEV5G D17 device.
 *
 * \details
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D17_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D17_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D17_MODE  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D17_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Configure mode of DEV5G D21 device.
 *
 * \details
 * 0: DEV5G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV5G_MODES . DEV5G_D21_MODE
 */
#define  VTSS_F_PORT_CONF_DEV5G_MODES_DEV5G_D21_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_DEV5G_MODES_DEV5G_D21_MODE  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_DEV5G_MODES_DEV5G_D21_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


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
 * Configure mode of DEV10G D8 device.
 *
 * \details
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D8_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D8_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D8_MODE  VTSS_BIT(0)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D8_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D12_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D12_MODE  VTSS_BIT(1)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D12_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Configure mode of DEV10G D16 device.
 *
 * \details
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D16_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D16_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D16_MODE  VTSS_BIT(2)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D16_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Configure mode of DEV10G D20 device.
 *
 * \details
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D20_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D20_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D20_MODE  VTSS_BIT(3)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D20_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Configure mode of DEV10G D24 device.
 *
 * \details
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D24_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D24_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D24_MODE  VTSS_BIT(4)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D24_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Configure mode of DEV10G D25 device.
 *
 * \details
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D25_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D25_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D25_MODE  VTSS_BIT(5)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D25_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Configure mode of DEV10G D26 device.
 *
 * \details
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D26_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D26_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D26_MODE  VTSS_BIT(6)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D26_MODE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Configure mode of DEV10G D27 device.
 *
 * \details
 * 0: DEV10G  XFI - USXGMII mode (device speed > 2.5G)
 * 1: DEV2G5  SGMII - USXGMII mode (device speed <= 2.5G)
 *
 * Field: ::VTSS_PORT_CONF_DEV10G_MODES . DEV10G_D27_MODE
 */
#define  VTSS_F_PORT_CONF_DEV10G_MODES_DEV10G_D27_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PORT_CONF_DEV10G_MODES_DEV10G_D27_MODE  VTSS_BIT(7)
#define  VTSS_X_PORT_CONF_DEV10G_MODES_DEV10G_D27_MODE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


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
#define VTSS_PORT_CONF_QSGMII_ENA            VTSS_IOREG(VTSS_TO_PORT_CONF,0x2)

/**
 * \brief
 * Set bit to enable QSGMII mode for devices DEV5G_0, DEV2G5_1, DEV2G5_2,
 * and DEV2G5_3 via SerDes10G_0
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
 * Set bit to enable QSGMII mode for devices DEV5G_4, DEV2G5_5, DEV2G5_6,
 * and DEV2G5_7 via SerDes10G_1
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
 * Set bit to enable QSGMII mode for devices DEV10G_8, DEV5G_9, DEV2G5_10,
 * and DEV2G5_11 via SerDes10G_2
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
 * Set bit to enable QSGMII mode for devices DEV10G_12, DEV5G_13,
 * DEV2G5_14, and DEV2G5_15 via SerDes10G_3
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
 * Set bit to enable QSGMII mode for devices DEV10G_16, DEV5G_17,
 * DEV2G5_18, and DEV2G5_19 via SerDes10G_4
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
 * Set bit to enable QSGMII mode for devices DEV10G_20, DEV5G_21,
 * DEV2G5_22, and DEV2G5_23 via SerDes10G_5
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
 * \brief Enable USXGMII mode for different ports
 *
 * \details
 * Enable USXGMII mode for different ports
 *
 * Register: \a PORT_CONF:HW_CFG:USXGMII_ENA
 */
#define VTSS_PORT_CONF_USXGMII_ENA           VTSS_IOREG(VTSS_TO_PORT_CONF,0x3)

/**
 * \brief
 * Set bit to enable single port USXGMII mode for device Dev5G_0
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
 * Set bit to enable single port USXGMII mode for device Dev5G_4
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
 * Set bit to enable USXGMII mode for devices Dev10G_8, Dev5G_9, Dev2G5_10
 * and Dev2G5_11 or subset depending on speed via SerDes10G_2
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
 * Set bit to enable USXGMII mode for devices Dev10G_12, Dev5G_13,
 * Dev2G5_14 and Dev2G5_15 or subset depending on speed via SerDes10G_3
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
 * Set bit to enable USXGMII mode for devices Dev10G_16, Dev5G_17,
 * Dev2G5_18 and Dev2G5_19 or subset depending on speed via SerDes10G_4
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
 * Set bit to enable USXGMII mode for devices Dev10G_20, Dev5G_21,
 * Dev2G5_22 and Dev2G5_23 or subset depending on speed via SerDes10G_5
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
 * Set bit to enable single port USXGMII mode for device Dev10G_24
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
 * Set bit to enable single port USXGMII mode for device Dev10G_25
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
 * Set bit to enable single port USXGMII mode for device Dev10G_26
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
 * Set bit to enable single port USXGMII mode for device Dev10G_27
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
#define VTSS_PORT_CONF_QSGMII_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x4,gi,2,0,0)

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
#define VTSS_PORT_CONF_QSGMII_STAT(gi)       VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x4,gi,2,0,1)

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
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-9
 */
#define VTSS_PORT_CONF_USXGMII_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x10,gi,3,0,0)

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
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-9
 */
#define VTSS_PORT_CONF_USXGMII_AM_CFG(gi)    VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x10,gi,3,0,1)

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
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-9
 */
#define VTSS_PORT_CONF_USXGMII_LFRF_SEQ(gi)  VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x10,gi,3,0,2)

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
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-9
 */
#define VTSS_PORT_CONF_USXGMII_RX_STATUS(gi)  VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x2e,gi,2,0,0)

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
 * @param gi Replicator: x_NUM_OF_USXGMII_EXT (??), 0-9
 */
#define VTSS_PORT_CONF_USXGMII_RX_ERR_STATUS(gi)  VTSS_IOREG_IX(VTSS_TO_PORT_CONF,0x2e,gi,2,0,1)

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


#endif /* _VTSS_LAGUNA_REGS_PORT_CONF_H_ */
