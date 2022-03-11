/******************************************************************************

         Copyright 2020 - 2021 MaxLinear Inc.
         Copyright 2016 - 2020 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _GPY211_H_
#define _GPY211_H_

#include <os.h>
#include <types.h>
#include "gpy211_log.h"
#include <registers/p31g/pm_pdi.h>

/** \mainpage GPY APIs
    \section intro_sec Introduction

    The Intel Ethernet Network Connection GPY API device is a
    multi-mode Gigabit Ethernet (GbE) transceiver integrated circuit,
    supporting speeds of 10, 100, 1000 and 2500 Mbps. It supports 10BASE-Te,
    100BASE-TX, 1000BASE-T and 2.5GBASE-T standards and is characterized by
    low power consumption. Power savings at the system level are introduced using
    the Wake-on-LAN feature.

    Ethernet PHYs are controlled over the MDIO interface and the base functionality is
    usually provided by the network stack and the MDIO driver of the operating system.

    The GPY API allows to make use of additional functionality, which is not provided
    by the operating system, to speed up integration of the GPY device and to to ensure
    correct configuration of features. The GPY API is intended to be used in user space,
    but can be used also in kernel space with minor adaptations and based on customer requirements.
*/

/** \defgroup GPY211_API GPY2xx APIs
	\brief This chapter describes the interface for accessing the GPY2xx.
*/

/** @{*/

/** \defgroup GPY211_INIT Init APIs
	\brief Group of functional APIs for initialization and cleanup.
*/

/** \defgroup GPY211_MDIO MDIO Bus APIs
	\brief Group of functional APIs for MDIO Bus access.
*/

/** \defgroup GPY211_LINK_API Link APIs
	\brief Group of functional APIs for auto-negotiation, link status, etc.
*/

/** \defgroup GPY211_LINK_SUPPORTED Supported Link Mode
	\brief Group of macros for supported link mode configuration via \ref gpy211_link in \ref GPY211_LINK_API.
	@cond SUBGROUPING
	@ingroup GPY211_LINK_API
	@endcond*/

/** \defgroup GPY211_LINK_ADVERTISED Advertised Link Mode
	\brief Group of macros for advertised link mode configuration via \ref gpy211_link in \ref GPY211_LINK_API.
	@cond SUBGROUPING
	@ingroup GPY211_LINK_API
	@endcond
*/

/** \defgroup GPY211_LINK_SPEED Link Speed
	\brief Group of macros for link speed configuration via \ref gpy211_link in APIs \ref gpy2xx_setup_forced,
	\ref gpy2xx_config_aneg and \ref gpy2xx_sgmii_config_aneg.
	@cond SUBGROUPING
	@ingroup GPY211_LINK_API
	@endcond
*/

/** \defgroup GPY211_LINK_DUPLEX Duplex
	\brief Group of macros for duplex mode configuration via \ref gpy211_link in APIs \ref gpy2xx_setup_forced,
	\ref gpy2xx_config_aneg and \ref gpy2xx_sgmii_config_aneg.
	@cond SUBGROUPING
	@ingroup GPY211_LINK_API
	@endcond
*/

/** \defgroup GPY211_GPIO_API GPIO APIs
	\brief Group of functional APIs for GPIO configuration. For debugging only, will be removed in future revisions.
*/

/** \defgroup GPY211_GPIO_FLAG GPIO Flags
	\brief Group of macros with GPIO flags for GPIO configuration via \ref gpy211_gpio in \ref GPY211_GPIO_API.
	For debugging only, will be removed in future revisions.
	@cond SUBGROUPING
	@ingroup GPY211_GPIO_API
	@endcond
*/

/** \defgroup GPY211_LED LED Function Config APIs
	\brief Group of functional APIs for LED configuration.
*/

/** \defgroup GPY211_INT External Interrupt APIs
	\brief Group of functional APIs for external interrupt configuration.
*/

/** \defgroup GPY211_DIAG Diagnosis and Test APIs
	\brief Group of functional APIs for diagnosis and test.
*/

/** \defgroup GPY211_SYNCE Synchronous Ethernet (SyncE) Config APIs.
	\brief Group of functional APIs for Synchronous Ethernet (SyncE) configuration.
	Note: Not supported on GPHY flavours (i.e part numbers): GPY212, GPY211.
*/

/** \defgroup GPY211_SGMII SGMII Interface Config APIs
	\brief Group of functional APIs for SGMII interface configuration.
*/

/** \defgroup GPY211_WOL_FLAG Wake-on-LAN Flags
	\brief Group of Wake-on-LAN flags.
*/

/** \defgroup GPY211_MISC Miscellaneous Config APIs
	\brief Group of functional APIs for miscellaneous features.
*/

/** \defgroup GPY211_FW Firmware Download APIs
	\brief Group of functional APIs to download firmware into flash memory.
*/

/** \defgroup GPY211_PTP IEEE 1588 Timestamp Config APIs
	\brief Group of functional APIs for PTP configuration.
*/

/** \defgroup GPY211_PM Packet Manager module APIs
	\brief Group of functional APIs for PM configuration.
*/

/** \defgroup GPY211_BM Buffer Manager APIs
	\brief Group of functional APIs for BM configuration.
*/

/** \defgroup GPY211_GPY24X_USXGMII USXGMII_REACH APIs
	\brief Group of functional APIs for USXGMII Reach configuration only for GPY24X.
	Note: USXGMII is not supported for other models except GPY241.
*/

/**@}*/ /* GPY211_API */

#if !defined(__BIG_ENDIAN) && !defined(__LITTLE_ENDIAN)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __LITTLE_ENDIAN	1
#else
#define __BIG_ENDIAN	1
#endif
#endif

#if defined(P31G_UART) && P31G_UART
extern int pc_uart_dataread(u32 Offset, u32 *value);
extern int pc_uart_datawrite(u32 Offset, u32 value);
#endif

/*
	os_alloc
	OS specific malloc func
*/
static inline void *
os_alloc(unsigned int size)
{
	if (size > 0) {
#ifdef __KERNEL__
		return kzalloc(size, in_atomic() ? GFP_ATOMIC : GFP_KERNEL);

#else
		return malloc(size);
#endif
	} else
		return NULL;
}

/*
	os_free
	OS specific free func
*/
static inline void
os_free(void *p)
{
	if (p != NULL)
#ifdef __KERNEL__
		kfree(p);

#else
		free(p);
#endif
}

/**********************
	Constant
 **********************/

/** \addtogroup GPY211_MDIO */
/**@{*/
/** \brief Flag to enable 21-bit IEEE 802.3ae Clause 45 addressing mode */
#define MII_ADDR_C45            (1<<30)
/**@}*/ /* GPY211_MDIO */

/** @cond INTERNAL */
/** \brief Slave MDIO's Target Base Address Register's Address */
#define SMDIO_BADR              0x1F
/** \brief Slave MDIO's Target Offset Address */
#define SMDIO_TOFF              0x00
/** @endcond */

/** \addtogroup GPY211_LINK_API */
/**@{*/
/** \brief Link mode bit indices */
enum link_mode_bit_indices {
	/** \brief 10M half-duplex twisted-pair */
	LINK_MODE_10baseT_Half_BIT  = 0,
	/** \brief 10M full-duplex twisted-pair */
	LINK_MODE_10baseT_Full_BIT  = 1,
	/** \brief 100M half-duplex twisted-pair */
	LINK_MODE_100baseT_Half_BIT = 2,
	/** \brief 100M full-duplex twisted-pair */
	LINK_MODE_100baseT_Full_BIT = 3,
	/** \brief 1G half-duplex twisted-pair */
	LINK_MODE_1000baseT_Half_BIT    = 4,
	/** \brief 1G full-duplex twisted-pair */
	LINK_MODE_1000baseT_Full_BIT    = 5,
	/** \brief Auto-negotiation */
	LINK_MODE_Autoneg_BIT       = 6,
	/** \brief Twisted-pair */
	LINK_MODE_TP_BIT        = 7,
	/** \brief Attachment unit interface */
	LINK_MODE_AUI_BIT       = 8,
	/** \brief Media-independent interface */
	LINK_MODE_MII_BIT       = 9,
	/** \brief Fiber */
	LINK_MODE_FIBRE_BIT     = 10,
	/** \brief BNC (Bayonet Neill-Concelman) Connector */
	LINK_MODE_BNC_BIT       = 11,
	/** \brief 10G full-duplex twisted-pair */
	LINK_MODE_10000baseT_Full_BIT   = 12,
	/** \brief Pause supported */
	LINK_MODE_Pause_BIT     = 13,
	/** \brief Asymmetric-pause supported */
	LINK_MODE_Asym_Pause_BIT    = 14,
	/** \brief 2.5G full-duplex */
	LINK_MODE_2500baseX_Full_BIT    = 15,
	/** \brief Backplane */
	LINK_MODE_Backplane_BIT     = 16,
	/** \brief 1G full-duplex backplane C48 coding */
	LINK_MODE_1000baseKX_Full_BIT   = 17,
	/** \brief 10G full-duplex 4-lane backplane C48 coding */
	LINK_MODE_10000baseKX4_Full_BIT = 18,
	/** \brief 10G full-duplex 1-lane backplane C49 coding */
	LINK_MODE_10000baseKR_Full_BIT  = 19,
	/** \brief 10G full-duplex C49 coding */
	LINK_MODE_10000baseR_FEC_BIT    = 20,
	/** \brief 20G full-duplex */
	LINK_MODE_20000baseMLD2_Full_BIT = 21,
	/** \brief 20G full-duplex 2-lane backplane C49 coding */
	LINK_MODE_20000baseKR2_Full_BIT = 22,
	/** \brief 40G full-duplex 4-lane backplane C49 coding */
	LINK_MODE_40000baseKR4_Full_BIT = 23,
	/** \brief 40G full-duplex fiber */
	LINK_MODE_40000baseCR4_Full_BIT = 24,
	/** \brief 40G full-duplex fiber */
	LINK_MODE_40000baseSR4_Full_BIT = 25,
	/** \brief 40G full-duplex fiber */
	LINK_MODE_40000baseLR4_Full_BIT = 26,
	/** \brief 56G full-duplex 4-lane backplane C49 coding */
	LINK_MODE_56000baseKR4_Full_BIT = 27,
	/** \brief 56G full-duplex fiber */
	LINK_MODE_56000baseCR4_Full_BIT = 28,
	/** \brief 56G full-duplex fiber */
	LINK_MODE_56000baseSR4_Full_BIT = 29,
	/** \brief 56G full-duplex fiber */
	LINK_MODE_56000baseLR4_Full_BIT = 30,
	/** \brief 25G full-duplex fiber */
	LINK_MODE_25000baseCR_Full_BIT  = 31,
	/** \brief 25G full-duplex backplane C49 coding */
	LINK_MODE_25000baseKR_Full_BIT  = 32,
	/** \brief 25G full-duplex fiber */
	LINK_MODE_25000baseSR_Full_BIT  = 33,
	/** \brief 50G full-duplex fiber */
	LINK_MODE_50000baseCR2_Full_BIT = 34,
	/** \brief 50G full-duplex 2-lane backplane C49 coding */
	LINK_MODE_50000baseKR2_Full_BIT = 35,
	/** \brief 100G full-duplex 4-lane backplane C49 coding */
	LINK_MODE_100000baseKR4_Full_BIT    = 36,
	/** \brief 100G full-duplex fiber */
	LINK_MODE_100000baseSR4_Full_BIT    = 37,
	/** \brief 100G full-duplex fiber */
	LINK_MODE_100000baseCR4_Full_BIT    = 38,
	/** \brief 100G full-duplex fiber */
	LINK_MODE_100000baseLR4_ER4_Full_BIT    = 39,
	/** \brief 50G full-duplex fiber */
	LINK_MODE_50000baseSR2_Full_BIT     = 40,
	/** \brief 1G full-duplex */
	LINK_MODE_1000baseX_Full_BIT    = 41,
	/** \brief 10G full-duplex fiber */
	LINK_MODE_10000baseCR_Full_BIT  = 42,
	/** \brief 10G full-duplex fiber */
	LINK_MODE_10000baseSR_Full_BIT  = 43,
	/** \brief 10G full-duplex fiber */
	LINK_MODE_10000baseLR_Full_BIT  = 44,
	/** \brief 10G full-duplex fiber */
	LINK_MODE_10000baseLRM_Full_BIT = 45,
	/** \brief 10G full-duplex fiber */
	LINK_MODE_10000baseER_Full_BIT  = 46,
	/** \brief 2.5G full-duplex twisted-pair */
	LINK_MODE_2500baseT_Full_BIT	= 47,
	/** \brief 5G full-duplex twisted-pair */
	LINK_MODE_5000baseT_Full_BIT	= 48,
	/** \brief 2.5G Base-T fast retrain */
	LINK_MODE_2500baseT_FR_BIT	= 49,
	/** \brief 5G Base-T fast retrain */
	LINK_MODE_5000baseT_FR_BIT	= 50,

	/** \brief Last Mode */
	LINK_MODE_LAST = LINK_MODE_5000baseT_FR_BIT,
};

/** \brief Wrapper for link mode used by \ref GPY211_LINK_SUPPORTED
	and \ref GPY211_LINK_ADVERTISED macros*/
#define LINK_MODE_MASK(base_name)   \
	(1ULL << (LINK_MODE_ ## base_name ## _BIT))
/**@}*/ /* GPY211_LINK_API */

/** \addtogroup GPY211_LINK_SUPPORTED */
/**@{*/
/** \brief Macros used by \b supported in \ref gpy211_link */
/** \brief 10M half-duplex twisted-pair */
#define	GPY2XX_SUPPORTED_10baseT_Half		LINK_MODE_MASK(10baseT_Half)
/** \brief 10M full-duplex twisted-pair	*/
#define	GPY2XX_SUPPORTED_10baseT_Full		LINK_MODE_MASK(10baseT_Full)
/** \brief 100M	half-duplex twisted-pair */
#define	GPY2XX_SUPPORTED_100baseT_Half		LINK_MODE_MASK(100baseT_Half)
/** \brief 100M	full-duplex twisted-pair */
#define	GPY2XX_SUPPORTED_100baseT_Full		LINK_MODE_MASK(100baseT_Full)
/** \brief 1G half-duplex twisted-pair */
#define	GPY2XX_SUPPORTED_1000baseT_Half	LINK_MODE_MASK(1000baseT_Half)
/** \brief 1G full-duplex twisted-pair */
#define	GPY2XX_SUPPORTED_1000baseT_Full	LINK_MODE_MASK(1000baseT_Full)
/** \brief Auto-negotiation */
#define	GPY2XX_SUPPORTED_Autoneg		LINK_MODE_MASK(Autoneg)
/** \brief Twisted-pair	*/
#define	GPY2XX_SUPPORTED_TP			LINK_MODE_MASK(TP)
/** \brief Media-independent interface */
#define	GPY2XX_SUPPORTED_MII			LINK_MODE_MASK(MII)
/** \brief Pause supported */
#define	GPY2XX_SUPPORTED_Pause			LINK_MODE_MASK(Pause)
/** \brief Asymmetric-pause supported	*/
#define	GPY2XX_SUPPORTED_Asym_Pause		LINK_MODE_MASK(Asym_Pause)
/** \brief 2.5G full-duplex twisted-pair	*/
#define	GPY2XX_SUPPORTED_2500baseT_Full	LINK_MODE_MASK(2500baseT_Full)
/** \brief 5G full-duplex twisted-pair	*/
#define	GPY2XX_SUPPORTED_5000baseT_Full	LINK_MODE_MASK(5000baseT_Full)
/** \brief 2.5G Base-T fast retrain */
#define	GPY2XX_SUPPORTED_2500baseT_FR		LINK_MODE_MASK(2500baseT_FR)
/** \brief 5G Base-T fast retrain */
#define GPY2XX_SUPPORTED_5000baseT_FR		LINK_MODE_MASK(5000baseT_FR)
/**@}*/ /* GPY211_LINK_SUPPORTED */

/** \addtogroup GPY211_LINK_ADVERTISED */
/**@{*/
/** \brief Macros used by \b advertising in \ref gpy211_link */
/** \brief 10M half-duplex twisted-pair */
#define	GPY2XX_ADVERTISED_10baseT_Half		LINK_MODE_MASK(10baseT_Half)
/** \brief 10M full-duplex twisted-pair	*/
#define	GPY2XX_ADVERTISED_10baseT_Full		LINK_MODE_MASK(10baseT_Full)
/** \brief 100M	half-duplex twisted-pair */
#define	GPY2XX_ADVERTISED_100baseT_Half	LINK_MODE_MASK(100baseT_Half)
/** \brief 100M	full-duplex twisted-pair */
#define	GPY2XX_ADVERTISED_100baseT_Full	LINK_MODE_MASK(100baseT_Full)
/** \brief 1G half-duplex twisted-pair */
#define	GPY2XX_ADVERTISED_1000baseT_Half	LINK_MODE_MASK(1000baseT_Half)
/** \brief 1G full-duplex twisted-pair */
#define	GPY2XX_ADVERTISED_1000baseT_Full	LINK_MODE_MASK(1000baseT_Full)
/** \brief Auto-negotiation */
#define	GPY2XX_ADVERTISED_Autoneg		LINK_MODE_MASK(Autoneg)
/** \brief Twisted-pair	*/
#define	GPY2XX_ADVERTISED_TP			LINK_MODE_MASK(TP)
/** \brief Media-independent interface */
#define	GPY2XX_ADVERTISED_MII			LINK_MODE_MASK(MII)
/** \brief Pause supported */
#define	GPY2XX_ADVERTISED_Pause		LINK_MODE_MASK(Pause)
/** \brief Asymmetric-pause supported	*/
#define	GPY2XX_ADVERTISED_Asym_Pause		LINK_MODE_MASK(Asym_Pause)
/** \brief 2.5G full-duplex twisted-pair	*/
#define	GPY2XX_ADVERTISED_2500baseT_Full	LINK_MODE_MASK(2500baseT_Full)
/** \brief 5G full-duplex twisted-pair	*/
#define	GPY2XX_ADVERTISED_5000baseT_Full	LINK_MODE_MASK(5000baseT_Full)
/** \brief 2.5G Base-T fast retrain */
#define	GPY2XX_ADVERTISED_2500baseT_FR		LINK_MODE_MASK(2500baseT_FR)
/** \brief 5G Base-T fast retrain */
#define GPY2XX_ADVERTISED_5000baseT_FR		LINK_MODE_MASK(5000baseT_FR)
/**@}*/ /* GPY211_LINK_ADVERTISED */

/** \addtogroup GPY211_LINK_SPEED */
/**@{*/
/** \brief Macros used by \b speed in \ref gpy211_link */
/** \brief 10 Mbps */
#define	SPEED_10	10
/** \brief 100 Mbps */
#define	SPEED_100	100
/** \brief 1 Gbps */
#define	SPEED_1000	1000
/** \brief 2.5 Gbps */
#define	SPEED_2500	2500
/** \brief 5 Gbps */
#define	SPEED_5000	5000
/** \brief 10 Gbps */
#define	SPEED_10000	10000
/** @cond INTERNAL */
/** \brief Unknown speed */
#define	SPEED_UNKNOWN	-1
/** @endcond */
/**@}*/ /* GPY211_LINK_SPEED */

/** \addtogroup GPY211_LINK_DUPLEX */
/**@{*/
/** \brief Macros used by \b duplex in \ref gpy211_link */
/** \brief Half duplex */
#define DUPLEX_HALF	0x00
/** \brief Full duplex */
#define DUPLEX_FULL	0x01
/** @cond INTERNAL */
/** \brief Unknown duplex */
#define DUPLEX_INVALID	0xFF
/** @endcond */
/**@}*/ /* GPY211_LINK_DUPLEX */

#ifndef __KERNEL__
/** \cond INTERNAL */
#define MDIO_MMD_PMAPMD	0x01
#define MDIO_MMD_PCS	0x03
#define MDIO_MMD_AN     0x07
#define MDIO_MMD_VEND1	0x1E
#define MDIO_MMD_VEND2	0x1F
/** \endcond */
#endif

/** @cond INTERNAL */
/** \brief Max GPIO pins supported */
#define GPIO_PINS_MAX   18
/** @endcond */

/** \addtogroup GPY211_GPIO_FLAG */
/**@{*/
/** \brief Macros used by \b flags in \ref gpy211_gpio */
/** \brief Output pin */
#define GPIOF_DIR_OUT   (0 << 0)
/** \brief Input pin */
#define GPIOF_DIR_IN    (1 << 0)
/** \brief Output pin low */
#define GPIOF_OUTPUT_LOW  (0 << 1)
/** \brief Output pin high */
#define GPIOF_OUTPUT_HIGH (1 << 1)
/** \brief Input pin low */
#define GPIOF_INPUT_LOW   (0 << 2)
/** \brief Input pin high */
#define GPIOF_INPUT_HIGH  (1 << 2)

/** \brief GPIO pin is open-drain */
#define GPIOF_OPEN_DRAIN    (1 << 3)

/** \brief GPIO pin is pull up */
#define GPIOF_PULL_UP       (2 << 8)
/** \brief GPIO pin pull down */
#define GPIOF_PULL_DOWN     (3 << 8)

/** \brief GPIO pin select alternative function "x" (0~3) */
#define GPIOF_FUNC(x)       (((x)&0x03)<<10)

/** \brief GPIO pin pad strength "x": 0 - 2 mA, 1 - 4 mA,
	2 - 8 mA, 3 - 12 mA */
#define GPIOF_PAD_STR(x)    (((x)&0x03)<<12)

/** \brief GPIO pin slow slew */
#define GPIOF_SLOW_SLEW     (0 << 15)
/** \brief GPIO pin fast slew */
#define GPIOF_FAST_SLEW     (1 << 15)
/**@}*/ /* GPY211_GPIO_FLAG */

/** \addtogroup GPY211_LED */
/**@{*/
/** \brief Member used by \b mode in \ref gpy211_led_brlvl_cfg */
/** \brief LED brightness mode */
enum gpy211_led_brlvl_mode {
	/** \brief Constant level at max brightness level of 15 */
	LED_BRLVL_MAX = 0,
	/** \brief Constant level given by lvl_max of \ref gpy211_led_brlvl_cfg */
	LED_BRLVL_CONSTANT = 1,
};
/** \cond INTERNAL */
/** \brief Lowest brightness mode value */
#define LED_BRLEVEL_MIN     LED_BRLVL_MAX
/** \brief Highest brightness mode value */
#define LED_BRLEVEL_MAX     LED_BRLVL_CONSTANT
/** \endcond */

/** \brief Member used by \b sw_edge in \ref gpy211_led_brlvl_cfg */
/** \brief LED switch edge detect mode */
enum gpy211_led_edge_detect {
	/** \brief LED switch edge detection on falling edge */
	LED_EDGE_DETECT_FALLING = 0,
	/** \brief LED switch edge detection on rising edge */
	LED_EDGE_DETECT_RISING = 1,
};
/** \cond INTERNAL */
/** \brief Lowest brightness mode value */
#define LED_EDGE_DET_MIN	LED_EDGE_DETECT_FALLING
/** \brief Highest brightness mode value */
#define LED_EDGE_DET_MAX	LED_EDGE_DETECT_RISING
/** \endcond */

/** \brief Macros used by \b color_mode in \ref gpy211_led_cfg */
/** \brief LED color mode */
enum gpy211_led_colormode {
	/** \brief Ground mode */
	LED_SINGLE = 0,
	/** \brief Power mode */
	LED_DUAL = 1,
};
/** \cond INTERNAL */
/** \brief Lowest CM value */
#define LED_CM_MIN			LED_SINGLE
/** \brief Highest CM value */
#define LED_CM_MAX			LED_DUAL
/** \endcond */

/** \brief Macros used by \b slow_blink_src or \b fast_blink_src or \b const_on in \ref gpy211_led_cfg */
/** \brief Stats trigger PHY blinking */
enum gpy211_led_bsrc {
	/** \brief No blinking */
	LED_BSRC_NONE = 0,
	/** \brief Blink on 10 Mbps link */
	LED_BSRC_LINK10 = 1,
	/** \brief Blink on 100 Mbps link */
	LED_BSRC_LINK100 = 2,
	/** \brief Blink on 1000 Mbps link */
	LED_BSRC_LINK1000 = 4,
	/** \brief Blink on 2500 Mbps link */
	LED_BSRC_LINK2500 = 8,
};
/** \cond INTERNAL */
/** \brief Lowest PHY blinking trigger value */
#define LED_BSRC_MIN	LED_BSRC_NONE
/** \brief Highest PHY blinking trigger value */
#define LED_BSRC_MAX    ((LED_BSRC_LINK2500 << 1) - 1)
/** \endcond */

/** \brief Macros used by \b pulse in \ref gpy211_led_cfg */
/** \brief LED pulse flags */
enum gpy211_led_pulse {
	/** \brief No pulsing */
	LED_PULSE_NONE = 0,
	/** \brief Generate pulse on LED when TX activity is detected */
	LED_PULSE_TX = 1,
	/** \brief Generate pulse on LED when RX activity is detected */
	LED_PULSE_RX = 2,
	/** \brief Generate pulse on LED when Collision is detected */
	LED_PULSE_COL = 4,
	/** \brief Constant ON behavior is switched off */
	LED_PULSE_NO_CON = 8,
};
/** \cond INTERNAL */
/** \brief Lowest pulse value */
#define LED_PULSE_MIN		LED_PULSE_NONE
/** \brief Highest pulse value */
#define LED_PULSE_MAX		((LED_PULSE_NO_CON << 1) - 1)
/** \endcond */

/** \cond INTERNAL */
/** \brief Min discharge slots */
#define LED_DIS_SLOTS_MIN		0
/** \brief Max discharge slots */
#define LED_DIS_SLOTS_MAX		63
/** \endcond */

/** \cond INTERNAL */
/** \brief Min brightness level */
#define LED_BRIGHT_LVL_MIN		0
/** \brief Max brightness level */
#define LED_BRIGHT_LVL_MAX		15
/** \endcond */
/**@}*/ /* GPY211_LED */

/** \addtogroup GPY211_INT */
/**@{*/
#if defined(EN_SUPPORT_TOP_INT) && EN_SUPPORT_TOP_INT
/** \brief External interrupt input characteristics */
enum gpy211_extin_ipc {
	/** \brief Interrupt request generation is disabled */
	EXTIN_IR_DISABLE = 0,
	/** \brief Interrupt on rising edges */
	EXTIN_IR_RISING = 1,
	/** \brief Interrupt on falling edges */
	EXTIN_IR_FALLING = 2,
	/** \brief Interrupt on rising and falling edges */
	EXTIN_IR_BOTH = 3,
	/** \brief Interrupt when high level is detected */
	EXTIN_IR_HIGH = 5,
	/** \brief Interrupt when low level is detected */
	EXTIN_IR_LOW = 6,
};
/** \cond INTERNAL */
/** \brief Min brightness level */
#define EXTIN_IR_IPC_MIN		EXTIN_IR_DISABLE
/** \brief Max brightness level */
#define EXTIN_IR_IPC_MAX		EXTIN_IR_LOW
/** \endcond */

/** \cond INTERNAL */
/** \brief External Interrupt Module-0 Event */
enum gpy211_extin_im0_event {
	/** \brief GPHY IP */
	EXTIN_IM0_GPHY        = (1 << 0),
	/** \brief Packet Manager */
	EXTIN_IM0_PM          = (1 << 1),
	/** \brief Management Interface Subsystem */
	EXTIN_IM0_MGE         = (1 << 2),
	/** \brief External Interrupt 1 */
	EXTIN_IM0_EXTIN1      = (1 << 4),
	/** \brief SGMII */
	EXTIN_IM0_SGMII       = (1 << 5),
	/** \brief PCIE Controller (FXVL IP) */
	EXTIN_IM0_FXVL_IP = (1 << 6),
	/** \brief Temperature Sensor (Overheat) */
	EXTIN_IM0_TEMP        = (1 << 7),
	/** \brief Center Distribution Block (CDB) */
	EXTIN_IM0_CDB         = (1 << 8),
	/** \brief DCDC (Power Module) */
	EXTIN_IM0_DCDC        = (1 << 9),
	/** \brief Wake-up Control */
	EXTIN_IM0_WAKEUP      = (1 << 10),
	/** \brief DCPM (Power Module) */
	EXTIN_IM0_XO_DCPM     = (1 << 11),
	/** \brief Timestamp */
	EXTIN_IM0_TIMESTAMP   = (1 << 12),
};
#define EXTIN_IM0_MIN ((EXTIN_IM0_GPHY << 1) - 1)
#define EXTIN_IM0_MAX ((EXTIN_IM0_TIMESTAMP << 1) - 1)
/** \endcond */

/** \brief External interrupt module-1 event */
enum gpy211_extin_im1_event {
	/** \brief SPD */
	EXTIN_IM1_SPD         = (1 << 0),
	/** \brief SPD B2B */
	EXTIN_IM1_SPD_B2B     = (1 << 1),
	/** \brief Restart ANEG */
	EXTIN_IM1_RESTART_ANEG = (1 << 2),
	/** \brief 2.5G */
	EXTIN_IM1_2P5G        = (1 << 4),
	/** \brief 1G */
	EXTIN_IM1_1G          = (1 << 5),
	/** \brief 100M */
	EXTIN_IM1_100M        = (1 << 6),
	/** \brief Link disconnect */
	EXTIN_IM1_LINK_DISCON = (1 << 7),
	/** \brief MDI flip */
	EXTIN_IM1_MDI_FLIP    = (1 << 8),
	/** \brief 10BT mode */
	EXTIN_IM1_EEE_10BT    = (1 << 9),
	/** \brief 100BT mode */
	EXTIN_IM1_EEE_100BT  = (1 << 10),
	/** \brief 1000BT mode */
	EXTIN_IM1_EEE_1000BT  = (1 << 11),
	/** \brief 2500BT mode */
	EXTIN_IM1_EEE_2500BT  = (1 << 12),
	/** \brief PHY reset */
	EXTIN_IM1_PHY_RESET   = (1 << 12),
	/** \brief PHY power down */
	EXTIN_IM1_PHY_PDOWN   = (1 << 12),
};
/** \cond INTERNAL */
#define EXTIN_IM1_MIN ((EXTIN_IM1_SPD << 1) - 1)
#define EXTIN_IM1_MAX ((EXTIN_IM1_PHY_PDOWN << 1) - 1)
/** \endcond */

/** \brief External interrupt module-2 event */
enum gpy211_extin_im2_event {
	/** \brief MRI TS */
	EXTIN_IM2_MRI_TS      = (1 << 0),
	/** \brief LPI */
	EXTIN_IM2_LPI         = (1 << 1),
	/** \brief MCI */
	EXTIN_IM2_MCI         = (1 << 2),
};
/** \cond INTERNAL */
#define EXTIN_IM2_MIN ((EXTIN_IM2_MRI_TS << 1) - 1)
#define EXTIN_IM2_MAX ((EXTIN_IM2_MCI << 1) - 1)
/** \endcond */
#endif

/** \brief Macros used by \b std_imask or \b std_istat in \ref gpy211_phy_extin */
/** \brief External interrupt event */
enum gpy211_extin_phy_event {
	/** \brief Link state change */
	EXTIN_PHY_LSTC    = (1 << 0),
	/** \brief Link speed change */
	EXTIN_PHY_LSPC    = (1 << 1),
	/** \brief Duplex mode change */
	EXTIN_PHY_DXMC    = (1 << 2),
	/** \brief MDI/MDIX crossover change */
	EXTIN_PHY_MDIXC   = (1 << 3),
	/** \brief MDI polarity change */
	EXTIN_PHY_MDIPC   = (1 << 4),
	/** \brief Link's auto-downspeed change */
	EXTIN_PHY_ADSC    = (1 << 5),
	/** \brief Link's auto-downspeed change */
	EXTIN_PHY_TEMP    = (1 << 6),
	/** \brief Link's auto-downspeed change */
	EXTIN_PHY_ULP     = (1 << 7),
	/** \brief SyncE loss of reference clock */
	EXTIN_PHY_LOR     = (1 << 8),
	/** \cond INTERNAL */
	/** \brief Mailbox transaction complete - (for internal use only)*/
	EXTIN_PHY_MBOX    = (1 << 9),
	/** \endcond */
	/** \brief Auto-negotiation complete */
	EXTIN_PHY_ANC     = (1 << 10),
	/** \brief Auto-negotiation error */
	EXTIN_PHY_ANE     = (1 << 11),
	/** \brief Next page transmitted */
	EXTIN_PHY_NPTX    = (1 << 12),
	/** \brief Next page received */
	EXTIN_PHY_NPRX    = (1 << 13),
	/** \brief Master/slave resolution error */
	EXTIN_PHY_MSRE    = (1 << 14),
	/** \brief Wake-on-LAN event */
	EXTIN_PHY_WOL     = (1 << 15),
};
/** \cond INTERNAL */
#define EXTIN_PHY_EVENT_MIN ((EXTIN_PHY_LSTC << 1) - 1)
#define EXTIN_PHY_EVENT_MAX ((EXTIN_PHY_WOL << 1) - 1)
/** \endcond */

/** \brief Macros used by \b ext_imask or \b ext_istat in \ref gpy211_phy_extin */
/** \brief IM2 interrupt enable */
enum gpy211_extin_im2_mask {
	/** \brief Enable interrupt on LPI event hit */
	EXTIN_IM2_IE_LPI    = (1 << 1),
	/** \brief Enable interrupt on any of Rx/Tx Timestamp FIFO is non-zero */
	EXTIN_IM2_IE_TS_FIFO = (1 << 3),
	/** \brief Enable interrupt on MACsec event hit */
	EXTIN_IM2_IE_MACSEC = (1 << 4),
};
/** \cond INTERNAL */
#define EXTIN_IM2_EVENT_MIN EXTIN_IM2_IE_LPI
#define EXTIN_IM2_EVENT_MAX ((EXTIN_IM2_IE_MACSEC << 1) - 1)
/** \endcond */
/**@}*/ /* GPY211_INT */

/** \addtogroup GPY211_DIAG */
/**@{*/
/** \brief Test modes */
enum gpy211_test_mode {
	/** \brief Normal operation without test */
	TEST_NOP = 0,
	/** \brief Test mode 1 (transmit waveform test)
		Refer to IEEE 802.3-2015 Table 40-7 */
	TEST_MODE1 = 1,
	/** \brief Test mode 1 (transmit waveform test)
		Refer to IEEE 802.3-2015 Table 40-7 */
	TEST_WAV = TEST_MODE1,
	/** \brief Test mode 2 (transmit jitter test in MASTER mode)
		Refer to IEEE 802.3-2015 Table 40-7 */
	TEST_MODE2 = 2,
	/** \brief Test mode 2 (transmit jitter test in MASTER mode)
		Refer to IEEE 802.3-2015 Table 40-7 */
	TEST_JITM = TEST_MODE2,
	/** \brief Test mode 3 (transmit jitter test in SLAVE mode)
		Refer to IEEE 802.3-2015 Table 40-7 */
	TEST_MODE3 = 3,
	/** \brief Test mode 3 (transmit jitter test in SLAVE mode)
		Refer to IEEE 802.3-2015 Table 40-7 */
	TEST_JITS = TEST_MODE3,
	/** \brief Test mode 4 (transmitter distortion test)
		Refer to IEEE 802.3-2015 Table 40-7 */
	TEST_MODE4 = 4,
	/** \brief Test mode 4 (transmitter distortion test)
		Refer to IEEE 802.3-2015 Table 40-7 */
	TEST_DIST = TEST_MODE4,
	/** \brief AFE Test */
	TEST_AFE = 5,
	/** \brief Cable diagnostics */
	TEST_CDIAG = 6,
	/** \brief Analog built-in self-test */
	TEST_ABIST = 7,

	/** \cond INTERNAL */
	TEST_LAST_MODE = TEST_ABIST,
	/** \endcond */
};

/** \brief Macros used by \b state in \ref gpy211_cdiag_sum */
/** \brief Pair state in cable diagnostics */
enum gpy211_cdiag_state {
	/** \brief Indicates non-trivial echo due to mismatch at the reported
		 distance (essentially the level is not ignorable, but not as
		 strong as expected from a full reflection) */
	CDIAG_REFLECTION = 1,
	/** \brief Indicates a clear level of echo due to an open termination */
	CDIAG_OPEN = 2,
	/** \brief Indicates a clear level of echo due to a short termination */
	CDIAG_SHORT = 4,
	/** \brief Indicates no detectable echo impulse (essentially the cable
		is properly matched) */
	CDIAG_MATCHED = 8,
};

/** \brief Macros used by \b test in \ref gpy211_abist_param */
/** \brief Flags in analog built-in self-test (ABIST) */
enum gpy211_abist_test {
	/** \brief Analog test for IP version < 1.5 */
	ABIST_ANALOG_IPV_0 = 0,
	/** \brief Analog test for IP version >= 1.5 */
	//ABIST_ANALOG_IPV_15 = 1, //Commented as not supported in latest spec.

	/** \brief DC test for 10BT mode LD, max +ve differential level */
	ABIST_DC_10BT_MAX_PVE = (1 << 4) | 0,
	/** \brief DC test for 10BT mode LD, 0 differential level */
	ABIST_DC_10BT_0 = (1 << 4) | 1,
	/** \brief DC test for 10BT mode LD, max -ve differential level */
	ABIST_DC_10BT_MAX_NVE = (1 << 4) | 2,

	/** \brief DC test for 100BT mode LD, max +ve differential level */
	ABIST_DC_100BT_MAX_PVE = (1 << 4) | 3,
	/** \brief DC test for 100BT mode LD, 0 differential level */
	ABIST_DC_100BT_0 = (1 << 4) | 4,
	/** \brief DC test for 100BT mode LD, max -ve differential level */
	ABIST_DC_100BT_MAX_NVE = (1 << 4) | 5,

	/** \brief DC test for 1000BT mode LD, max +ve differential level */
	ABIST_DC_1000BT_MAX_PVE = (1 << 4) | 6,
	/** \brief DC test for 1000BT mode LD, 0 differential level */
	ABIST_DC_1000BT_0 = (1 << 4) | 7,
	/** \brief DC test for 10000BT mode LD, max -ve differential level */
	ABIST_DC_1000BT_MAX_NVE = (1 << 4) | 8,

	/** \brief DC test for 2500BT mode LD, max +ve differential level */
	ABIST_DC_2500BT_MAX_PVE = (1 << 4) | 9,
	/** \brief DC test for 2500BT mode LD, 0 differential level */
	ABIST_DC_2500BT_0 = (1 << 4) | 10,
	/** \brief DC test for 2500BT mode LD, max -ve differential level */
	ABIST_DC_2500BT_MAX_NVE = (1 << 4) | 11,

	/** \brief Bit Error Rate (BER) test */
	//ABIST_BER = (2 << 4), //Commented as not supported in latest spec.
};

/** \brief Test loop modes */
enum gpy211_test_loop {
	/** \brief Disable test loop */
	TLOOP_OFF = 0,
	/** \brief GMII (Near End) Test Loop:
		This test loop allows raw (G)MII transmit data to be looped back
		to the (G)MII) receive port. The setting will only take effect
		after a link down/up event takes place. */
	TLOOP_NETl = 1,
	/** \brief Far End Test Loop:
		This PCS far end test loop allows for the receive data at the
		output of the receive PCS to be fed back into the transmit path,
		that is, the input of the transmit PCS. The received data is
		also available at the xMII interface output, however all xMII
		transmit data is ignored in this test mode. The setting will
		only take effect after a link down/up event takes place. */
	TLOOP_FETl = 2,
	/** \brief DEC (Digital Echo Canceler) Test Loop:
		This test loop allows the transmit signal to be looped back via
		the Digital Echo Canceler (DEC). This loopback is similar to
		the functionality of the MDI test loop (\ref TLOOP_RJTl), except
		that it does not require special termination circuitry at the
		MDI connector. The user of this test loop has the option to
		terminate each twisted pair with a 100 Ohm resistor. This test
		loop is only applicable for 1000Base-T/2.5GBase-T. The setting
		will only take effect after a link down/up event takes place. */
	TLOOP_ECHO = 3,
	/** \brief MDI (RJ45 Near End) Test Loop:
		This test loop allows for loopback of the signal at the MDI
		connector, for example RJ45 or SMB. Referring to the four
		available twisted pairs in a CAT5 or equivalent cable type,
		pair A is connected to pair B, and pair C to pair D. This
		shorting of near-end twisted pairs must be enabled using
		specialized termination circuitry. No additional resistors are
		required. The setting will only take effect after a link down/up
		event takes place. */
	TLOOP_RJTl = 4,
	/** \brief Far End Test Loop:
		This is the same as \ref TLOOP_FETl, except that \ref TLOOP_FETl
		is dependent on the availability of TX_CLK and RX_CLK from
		the MII interface, but the IP takes care of generating the necessary
		clocks for the loopback to work in this mode. The setting will
		only take effect after a link down/up event takes place. */
	TLOOP_FELTS = 5,
	/** \brief GMII (Near End) Test Loop:
		This test loop allows raw (G)MII transmit data to be looped back
		to the (G)MII) receive port. The difference compared to
		\ref TLOOP_NETl is that this setting takes effect immediately.
		The Ethernet port indicates a link down and enters test mode,
		in addition to closing the (G)MII-to-PCS buffer loop. */
	TLOOP_NETLI = 8,
};

/** \brief Error events to be counted */
enum gpy211_errcnt_event {
	/** \brief Receive errors are counted */
	ERRCNT_RXERR = 0,
	/** \brief Receive frames are counted */
	ERRCNT_RXACT = 1,
	/** \brief ESD errors are counted */
	ERRCNT_ESDERR = 2,
	/** \brief SSD errors are counted */
	ERRCNT_SSDERR = 3,
	/** \brief Transmit errors are counted */
	ERRCNT_TXERR = 4,
	/** \brief Transmit frames are counted */
	ERRCNT_TXACT = 5,
	/** \brief Collision events are counted */
	ERRCNT_COL = 6,
	/** \brief Link down events are counted */
	ERRCNT_NLD = 8,
	/** \brief Auto-downspeed events are counted */
	ERRCNT_ADS = 9,
	/** \brief CRC error events are counted */
	ERRCNT_CRC = 10,
	/** \brief Time to link events are counted */
	ERRCNT_TTL = 11,
};
/**@}*/ /* GPY211_DIAG */

/** \addtogroup GPY211_SYNCE */
/**@{*/
/** \brief Macros used by \b synce_refclk in \ref gpy211_synce */
/** \brief SyncE reference clock input frequency */
enum gpy211_synce_clk  {
	/** \brief SyncE clock frequency is PSTN class: 8KHz */
	SYNCE_CLK_PSTN = 0,
	/** \brief SyncE clock frequency is EEC-1 class: 2.048MHz */
	SYNCE_CLK_EEC1 = 1,
	/** \brief SyncE clock frequency is EEC-2 class: 1.544MHz */
	SYNCE_CLK_EEC2 = 2,
	/** \brief Reserved */
	SYNCE_CLK_RES = 3,
};
/** \cond INTERNAL */
/** \brief Lowest ref clock's i/p frequency value */
#define SYNCE_REFCLK_MIN	SYNCE_CLK_PSTN
/** \brief Highest ref clock's i/p frequency value */
#define SYNCE_REFCLK_MAX	SYNCE_CLK_EEC2
/** \endcond */

/** \brief GPC-0 mux selected on GPIO pin 10 on GPY2XX */
#define GPIO_PIN10_GPC0_FUN  10
/** \brief GPC-0 mux selected on GPIO pin 10 on GPY24X */
#define GPIO_PIN07_GPC0_FUN  07

/** \brief Macros used by \b master_sel in \ref gpy211_synce */
/** \brief Select synce master, slave mode */
enum gpy211_synce_master_mode {
	/** \brief SLAVE mode */
	SYNCE_SLAVE = 0,
	/** \brief Master mode */
	SYNCE_MASTER = 1,
};

/** \brief Macros used by \b data_rate in \ref gpy211_synce */
/** \brief Data rate */
enum gpy211_data_rate {
	/** \brief SYNCE_1G */
	SYNCE_1G = 0,
	/** \brief SYNCE_2G5 */
	SYNCE_2G5 = 1,
};

/** \brief Macros used by \b gpc_sel in \ref gpy211_synce */
/** \brief Select gpc_sel for GPC and GPIO */
enum gpy211_gpc_sel {
	/** \brief GPC0 */
	SYNCE_GPC0 = 0,
	/** \brief GPC1 */
	SYNCE_GPC1 = 1,
	/** \brief GPC2 */
	SYNCE_GPC2 = 2,
};
/**@}*/ /* GPY211_SYNCE */

/** \addtogroup GPY211_SGMII */
/**@{*/
/** \brief Macros used by \b linkcfg_dir in \ref gpy211_sgmii */
/** \brief SGMII link configuration direction */
enum gpy211_sgmii_linkcfg_dir {
	/** \brief SGMII configuration is taken from twisted pair link status */
	SGMII_LINKCFG_TPI = 0,
	/** \brief SGMII configuration is taken from SGMII registers */
	SGMII_LINKCFG_SGMII = 1,
};

/** \brief Macros used by \b aneg_mode in \ref gpy211_sgmii */
/** \brief SGMII auto-negotiation mode */
enum gpy211_sgmii_aneg_mode {
	/** \brief 1000-Bx ANEG mode */
	SGMII_ANEG_1000BX = 1,
	/** \brief SGMII ANEG mode with GPY2xx acting as a PHY */
	SGMII_ANEG_CISCO_PHY = 2,
	/** \brief SGMII ANEG mode with GPY2xx acting as a MAC */
	SGMII_ANEG_CISCO_MAC = 3,
};

/** \brief SGMII operation mode */
enum gpy211_sgmii_operation {
	/** \brief Normal operation */
	SGMII_OP_NORMAL = 0,
	/** \brief Power down */
	SGMII_OP_DOWN = 1,
	/** \brief Loopback data coming in from analog interface back to itself */
	SGMII_OP_LOOPBACK = 2,
	/** \brief Reset SGMII block */
	SGMII_OP_RESET = 3
};
/**@}*/ /* GPY211_SGMII */

/** \addtogroup GPY211_WOL_FLAG */
/**@{*/
/** \brief Macros used by \b wolopts in \ref gpy2xx_wol_cfg */
/** \brief Wake up when PHY link is up */
#define WAKE_PHY	(1 << 0)
/** \brief Wake up when received Unicast frame */
#define WAKE_UCAST	(1 << 1)
/** \brief Wake up when received Multicast fram */
#define WAKE_MCAST	(1 << 2)
/** \brief Wake up when received Broadcast frame */
#define WAKE_BCAST	(1 << 3)
/** \brief Wake up when received ARP frame */
#define WAKE_ARP	(1 << 4)
/** \brief Wake up when received Magic frame */
#define WAKE_MAGIC	(1 << 5)
/** \brief Secured wake upOnly meaningful if WAKE_MAGIC is use */
#define WAKE_MAGICSECURE	(1 << 6)

/** \cond INTERNAL */
#define GPY211_WOL_FLAG_MIN ((WAKE_PHY << 1) - 1)
#define GPY211_WOL_FLAG_MAX ((WAKE_MAGICSECURE << 1) - 1)
/** \endcond */
/**@}*/ /* GPY211_WOL_FLAG */

/** \addtogroup GPY211_FW */
/**@{*/
/** \brief Default timeout (in milliseconds) for field firmware upgrade APIs */
#define FW_FWR_DEF_TIMEOUT	5000
/**@}*/ /* GPY211_FW */

/** \addtogroup GPY211_GPY24X_USXGMII */
/**@{*/
/** \brief Max number of slices */
#define SLICE_NUM		4
/**@}*/ /* GPY211_GPY24X_USXGMII */

/** @cond INTERNAL */
#define PHYADDR2INDEX(phyaddr)	(phyaddr & (SLICE_NUM - 1))
/** @endcond */

/** \addtogroup GPY211_LINK_API */
/**@{*/
/** \brief Member used by \b link in \ref gpy211_device and \ref gpy211_sgmii */
/** \brief Data structure representing GPHY link configuration and status */
struct gpy211_link {
	/** \brief Link speed (forced) or partner link speed (auto-negotiation)
		defined by \ref GPY211_LINK_SPEED macros */
	int speed;
	/** \brief TPI speed or forced 2.5G */
	int fixed2g5;
	/** \brief Duplex (forced) or partner duplex (auto-negotiation)
	    defined by \ref GPY211_LINK_DUPLEX macros */
	int duplex;
	/** \brief Partner pause (auto-negotiation) */
	int pause;
	/** \brief Partner asym-pause (auto-negotiation) */
	int asym_pause;
	/** \brief The most recently read link state */
	int link;
	/** \brief Union of GPHY supported modes listed in
		\ref GPY211_LINK_SUPPORTED macros. This is updated when \ref gpy2xx_init
		is called and should not be changed by the user application. */
	u64 supported;
	/** \brief Union of GPHY advertising modes listed in
		\ref GPY211_LINK_ADVERTISED macros */
	u64 advertising;
	/** \brief Union of partner advertising modes listed in
		\ref GPY211_LINK_ADVERTISED macros */
	u64 lp_advertising;

	/** \brief Enable auto-negotiation.
		Value 1 to enable auto-negotiation, value 0 to force link */
	int autoneg;
};
/**@}*/ /* GPY211_LINK_API */

/** \addtogroup GPY211_GPIO_API */
/**@{*/
/** \brief Data structure for GPIO pin configuration */
struct gpy211_gpio {
	/** \brief Port ID */
	u16 port;
	/** \brief Pin ID on this port */
	u16 pin;
	/** \brief Flags to configure GPIO pin.
		Valid values are defined in \ref GPY211_GPIO_FLAG macros. Use multiple values with "or".*/
	u32 flags;
};
/**@}*/ /* GPY211_GPIO */

/** \addtogroup GPY211_LED */
/**@{*/
/** \brief (Macros used by \b id in \ref gpy211_led_cfg) */
/** \brief LED ID 0 */
#define LED_ID_0   			0
/** \brief LED ID 1 */
#define LED_ID_1   			1
/** \brief LED ID 2 */
#define LED_ID_2   			2
/** \brief LED ID 3 (Not applicable to gpy24X) */
#define LED_ID_3   			3
/** \cond INTERNAL */
/** \brief Lowest LED value */
#define LED_ID_MIN			LED_ID_0
/** \brief Highest LED value */
#define LED_ID_MAX			LED_ID_3
/** \endcond */

/** \brief Data structure for LED brightness level configuration */
struct gpy211_led_brlvl_cfg {
	/** \brief Brightness Mode:
		Valid values are defined in \ref gpy211_led_brlvl_mode enum */
	enum gpy211_led_brlvl_mode mode;
	/** \brief Maximum brightness level. Applicable only when mode is CONSTANT.
		Level 0 will turn the LED off. */
	int lvl_max;
	/** \brief Minimum brightness level. Not in use. */
	int lvl_min;
	/** \brief Switch edge detect:
		0 - detect on falling edge, 1 - detect on rising edge */
	enum gpy211_led_edge_detect sw_edge;
};

#if defined(EN_LED_TOP_CFG) && EN_LED_TOP_CFG
/** \brief Macros used by \b complex_scan or \b complex_blink or \b inverse_scan in \ref gpy211_led_gcfg */
/** \brief States to activate various LED modes: complex scan,
	complex blinking, and inverse scan */
enum gpy211_led_csrc {
	/** \brief No function */
	LED_CSRC_NONE = 0,
	/** \brief Link up */
	LED_CSRC_LINK = 1,
	/** \brief Power down */
	LED_CSRC_PDOWN = 2,
	/** \brief In EEE mode */
	LED_CSRC_EEE = 3,
	/** \brief Auto-negotiation running */
	LED_CSRC_ANEG = 4,
	/** \brief Analog self-test running */
	LED_CSRC_ABIST = 5,
	/** \brief Cable diagnostics running */
	LED_CSRC_CDIAG = 6,
	/** \brief Test mode running */
	LED_CSRC_TEST = 7,
};
/** \cond INTERNAL */
/** \brief Lowest scan source value */
#define LED_SCAN_SRC_MIN		LED_CSRC_NONE
/** \brief Highest scan source value */
#define LED_SCAN_SRC_MAX		LED_CSRC_TEST
/** \endcond */

/** \brief Macros used by \b fast_blink_freq or \b slow_blink_freq in \ref gpy211_led_gcfg */
/** \brief LED blinking frequency */
enum gpy211_led_blk_freq {
	/** \brief 2 Hz blinking frequency */
	LED_BLK_02Hz = 0,
	/** \brief 4 Hz blinking frequency */
	LED_BLK_04Hz = 1,
	/** \brief 8 Hz blinking frequency */
	LED_BLK_08Hz = 2,
	/** \brief 16 Hz blinking frequency */
	LED_BLK_16Hz = 3,
};
/** \cond INTERNAL */
/** \brief Lowest PHY blinking frequency value */
#define LED_BFRQ_MIN		LED_BLK_02Hz
/** \brief Highest PHY blinking frequency value */
#define LED_BFRQ_MAX		LED_BLK_16Hz
/** \endcond */

/** \brief Data structure for general configuration of all LEDs */
struct gpy211_led_gcfg {
	/** \brief Defines the state in which the "complex scan" should be activated.
		The complex scan performs running LED ON, which turns back and forth
		between the first and last LED. The speed is dependent on
		fast_blink_freq of \ref gpy211_led_gcfg. Valid values are defined in
		\ref gpy211_led_csrc enum. */
	enum gpy211_led_csrc complex_scan;
	/** \brief Defines the state in which the "complex blinking" should be
		activated. The complex blinking performs blinking at
		fast_blink_freq of \ref gpy211_led_gcfg on all LEDs simultaneously.
		This function can be used to indicate a special mode of the PHY
		such as cable-diagnostics or test. Valid values are defined in
		\ref gpy211_led_csrc enum. */
	enum gpy211_led_csrc complex_blink;
	/** \brief Defines in which state the "inverse complex scan" should be
		activated. The inverse complex scan performs running LED OFF, which
		turns back and forth between the first and last LED. The speed
		is dependent on fast_blink_freq of \ref gpy211_led_gcfg. Valid
		values are defined in \ref gpy211_led_csrc enum. */
	enum gpy211_led_csrc inverse_scan;
	/** \brief Fast blink frequency */
	enum gpy211_led_blk_freq fast_blink_freq;
	/** \brief Slow blink frequency */
	enum gpy211_led_blk_freq slow_blink_freq;
};
#endif

/** \brief Data structure for LED configuration */
struct gpy211_led_cfg {
	/** \brief LED ID (0~3) (\ref  GPY211_LED)*/
	int id;
	/** \brief LED color mode.
		Valid values are \ref gpy211_led_colormode.
		NOTE: This is for internal use only */
	enum gpy211_led_colormode color_mode;
	/** \brief Select in which PHY state the LED blinks with slow frequency.
	Valid values are defined in \ref gpy211_led_bsrc enum. */
	enum gpy211_led_bsrc slow_blink_src;
	/** \brief Select in which PHY state the LED blinks with fast frequency.
	Valid values are defined in \ref gpy211_led_bsrc enum. */
	enum gpy211_led_bsrc fast_blink_src;
	/** \brief Select in which PHY status the LED is constantly on.
		Valid values are defined in \ref gpy211_led_bsrc enum. */
	enum gpy211_led_bsrc const_on;
	/** \brief Pulsing configuration.
		Values (\ref gpy211_led_pulse) can be combined with "or". */
	u32 pulse;
};
/**@}*/ /* GPY211_LED */

/** \addtogroup GPY211_INT */
/**@{*/
#if defined(EN_SUPPORT_TOP_INT) && EN_SUPPORT_TOP_INT
/** \brief MDIO interrupt polarity low */
#define MDIO_INT_POL_LOW	0
/** \brief MDIO interrupt polarity high */
#define MDIO_INT_POL_HIGH	1

/** \brief External interrupt ID 0 */
#define EXT_INT_ID_0   		0
/** \brief External interrupt ID 1 */
#define EXT_INT_ID_1   		1

/** \brief Data structure for external interrupt configuration */
struct gpy211_extin {
	/** \brief External Interrupt ID (0~1) */
	int id;
	/** \brief GPIO configuration for external interrupt */
	u32 gpio_flags;
	/** \brief Input pin characteristics when external interrupt is configured
		as input to GPHY. Valid values are defined in \ref gpy211_extin_ipc enum. */
	enum gpy211_extin_ipc ip_char;
	/** \brief Interrupt event if external interrupt is configured
		as input to GPHY. Valid values are defined in \ref gpy211_extin_im0_event enum. */
	enum gpy211_extin_im0_event im0; //for swanville
	/** \brief Interrupt event if external interrupt is configured
		as input to GPHY. Valid values are defined in \ref gpy211_extin_im1_event enum. */
	enum gpy211_extin_im1_event im1;
	/** \brief Interrupt event if external interrupt is configured
		as input to GPHY. Valid values are defined in \ref gpy211_extin_im2_event enum. */
	enum gpy211_extin_im2_event im2;	//for packet manager
};
#endif /* EN_SUPPORT_TOP_INT */

/** \brief Data structure for external interrupt configuration */
struct gpy211_phy_extin {
	/** \brief Standard interrupt mask. Valid values are defined in
		\ref gpy211_extin_phy_event enum */
	enum gpy211_extin_phy_event std_imask;
	/** \brief Standard interrupt status. Valid values are defined in
		\ref gpy211_extin_phy_event enum */
	enum gpy211_extin_phy_event std_istat;
	/** \brief Extended interrupt mask. Valid values are defined in
		\ref gpy211_extin_im2_mask enum */
	enum gpy211_extin_im2_mask ext_imask;
	/** \brief Extended interrupt status. Valid values are defined in
		\ref gpy211_extin_im2_mask enum */
	enum gpy211_extin_im2_mask ext_istat;
};
/**@}*/ /* GPY211_INT */

/** \addtogroup GPY211_DIAG */
/**@{*/
/** \brief Member used by \b results in \ref gpy211_cdiag_pair */
/** \brief Cable diagnostic report of non-trivial echo */
struct gpy211_cdiag_sum {
	/** \brief Distance in meters */
	u8 distance;
	/** \brief Pair state (\ref gpy211_cdiag_state) */
	u8 state;
	/** \brief 16-bit signed short integer of the echo coefficient of the first
		detected peak */
	s16 peak;
};

/** \brief Member used by \b pair in \ref gpy211_cdiag_report */
/** \brief Cable diagnostic report of one pair */
struct gpy211_cdiag_pair {
	/** \brief Number of valid results in results of \ref gpy211_cdiag_pair*/
	u16 num_valid_result;
	/** \brief Up to 5 non-trivial echos are reported */
	struct gpy211_cdiag_sum results[5];
	/** \brief 16-bit signed short integer representing the sum-of-square
		of all XC(0~2) coefficients. This can be used to detect whether
		the cross-talk level is non-trivial. */
	s16 xc_pwr[3];
};

/** \brief Cable diagnostic report */
struct gpy211_cdiag_report {
	/** \brief Report of each pair:
		0 - DSPA, 1 - DSPB, 2 - DSPC, 3 - DSPD */
	struct gpy211_cdiag_pair pair[4];
};

/** \brief Analog built-in self-test parameter */
struct gpy211_abist_param {
	/** \brief Set 1 to restart test */
	u8 restart;
	/** \brief Set 1 to enable detail report on debug UART output */
	u8 uart_report;
	/** \brief Test item defined in \ref gpy211_abist_test enum */
	enum gpy211_abist_test test;
};

/** \brief Member used by \b pair in \ref gpy211_abist_report */
/** \brief Analog built-in self-test report of one pair */
struct gpy211_abist_pair {
	struct {
		/** \brief Max ADC noise injection magnitude */
		u8 mag_max;
		/** \brief Min ADC noise injection magnitude */
		u8 mag_min;
		/** \brief Average ADC noise injection magnitude */
		u8 mag_avg;
		/** \brief DC ADC noise injection magnitude */
		u8 mag_dc;
	}
	/** \brief ADC noise (ICN_GMAX) */
	icn_gmax,
	/** \brief DAC + LD noise (ICN_GMIN) */
	icn_gmin;
	struct {
		/** \brief Measured power at +9/+6/+2/-1/-5/-8 dB gain respectively */
		u8 agc_pwr[6];
		/** \brief Mean of measured power at +9/+6/+2/-1/-5/-8 dB gain */
		u8 agc_mean;
		/** \brief Std measured power at +9/+6/+2/-1/-5/-8 dB gain */
		u8 agc_std;
	}
	/** \brief Measured power when hybrid ON */
	agc_hyb,
	/** \brief Measured power when hybrid OFF */
	agc_nohyb;
	struct {
		/** \brief FFT magnitude at DC */
		u8 dc_mag;
		/** \brief FFT magnitude at nyquist frequency 100 MHz */
		u8 nyq_mag;
		/** \brief FFT magnitude at fundamental frequency */
		u8 k1_mag;
		/** \brief Harmonics K2 */
		u8 k2_mag;
		/** \brief Harmonics K3 */
		u8 k3_mag;
		/** \brief Harmonics K4 */
		u8 k4_mag;
	}
	/** \brief Measured for 10bt mode with hybrid OFF */
	nohyb_10bt,
	/** \brief Measured for 100bt mode with hybrid OFF */
	nohyb_100bt,
	/** \brief Measured for 1000bt mode with hybrid ON */
	hyb_1000bt,
	/** \brief Measured for 1000bt mode with hybrid OFF */
	nohyb_1000bt,
	/** \brief Measured for 2500bt mode with hybrid ON */
	hyb_2500bt,
	/** \brief Measured for 2500bt mode with hybrid OFF */
	nohyb_2500bt;
};

/** \brief Analog built-in self-test report */
struct gpy211_abist_report {
	/** \brief Report of each pair:
		0 - DSPA, 1 - DSPB, 2 - DSPC, 3 - DSPD */
	struct gpy211_abist_pair pair[4];
};

/** \brief PCS status */
struct gpy211_pcs_status {
	/** \brief Bit error rate (BER) */
	u32 ber;
	/** \brief Number of errored blocks */
	u32 errored_block;

	/** \brief 1 indicates high bit error rate (BER) */
	u8 high_ber;
	/** \brief 0 indicates loss of block lock */
	u8 block_lock;
	/** \brief 1 indicates PCS receive link up */
	u8 rcv_link_up;
};
/**@}*/ /* GPY211_DIAG */

/** \addtogroup GPY211_PTP */
/**@{*/
/** \brief Macros used by \b tx_ptp_tpt in \ref gpy211_ptp_ctrl */
/** \brief Transmit PTP transport protocol type.
Indicates the type of transport protocol over which PTP messages are sent */
enum gpy211_ptp_tx_ptoto {
	/** \brief PTP over Ethernet */
	PTP_TRANSPORT_OVER_ETH = 1,
	/** \brief PTP over UDP/IPv4 */
	PTP_TRANSPORT_OVER_IPv4 = 2,
	/** \brief PTP over UDP/IPv6 */
	PTP_TRANSPORT_OVER_IPv6 = 3,
};

/** \cond INTERNAL */
/** \brief TS Control - low */
struct gpy211_tsc_low {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Enable timestamp */
			u16 ts_en: 1;
			/** \brief Fine or coarse timestamp update */
			u16 foc_updt: 1;
			/** \brief Initialize timestamp */
			u16 ts_init: 1;
			/** \brief Update timestamp */
			u16 ts_updt: 1;
			/** \brief Reserved */
			u16 reserved: 1;
			/** \brief Update addend register */
			u16 addend_updt: 1;
			/** \brief Reserved */
			u16 reserved2: 2;
			/** \brief Enable timestamp for all packets */
			u16 en_all_pkts: 1;
			/** \brief Timestamp digital or binary rollover control */
			u16 dob_ro_ctrl: 1;
			/** \brief Enable PTP packet processing for version 2 format */
			u16 ts_ver2_en: 1;
			/** \brief Enable processing of PTP over Ethernet Packets */
			u16 ts_eth_en: 1;
			/** \brief Enable processing of PTP packets sent over IPv6-UDP */
			u16 ts_ipv6_en: 1;
			/** \brief Enable processing of PTP packets sent over IPv4-UDP */
			u16 ts_ipv4_en: 1;
			/** \brief Enable timestamp snapshot for event messages */
			u16 ts_evtmsg_en: 1;
			/** \brief Enable snapshot for messages relevant to master */
			u16 ts_master_en: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief Enable Snapshot for Messages Relevant to Master */
			u16 ts_master_en: 1;
			/** \brief Enable Timestamp Snapshot for Event Messages */
			u16 ts_evtmsg_en: 1;
			/** \brief Enable Processing of PTP Packets Sent over IPv4-UDP */
			u16 ts_ipv4_en: 1;
			/** \brief Enable Processing of PTP Packets Sent over IPv6-UDP */
			u16 ts_ipv6_en: 1;
			/** \brief Enable Processing of PTP over Ethernet Packets */
			u16 ts_eth_en: 1;
			/** \brief Enable PTP Packet Processing for Version 2 Format */
			u16 ts_ver2_en: 1;
			/** \brief Timestamp Digital or Binary Rollover Control */
			u16 dob_ro_ctrl: 1;
			/** \brief Enable Timestamp for All Packets */
			u16 en_all_pkts: 1;
			/** \brief Reserved */
			u16 reserved2: 2;
			/** \brief Update Addend Register */
			u16 addend_updt: 1;
			/** \brief Reserved */
			u16 reserved: 1;
			/** \brief Update Timestamp */
			u16 ts_updt: 1;
			/** \brief Initialize Timestamp */
			u16 ts_init: 1;
			/** \brief Fine or Coarse Timestamp Update */
			u16 foc_updt: 1;
			/** \brief Enable Timestamp */
			u16 ts_en: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Timestamp control low word - raw */
		u16 raw_ts_ctrl_low;
	};
};

/** \brief TS control - high */
struct gpy211_tsc_high {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Select PTP packets for taking snapshots */
			u16 snap_type: 2;
			/** \brief Enable MAC Address for PTP packet filtering */
			u16 ts_mac_en: 1;
			/** \brief Enable checksum correction during One Step Timestamp (OST) for PTP over UDP/IPv4 packets */
			u16 ts_csc_en: 1;
			/** \brief Reserved */
			u16 reserved: 4;
			/** \brief Transmit timestamp status mode: If set, the PHY overwrites the earlier transmit timestamp
			status even if it is not read by the software */
			u16 ts_stat_mode: 1;
			/** \brief Reserved */
			u16 reserved2: 3;
			/** \brief AV 802.1AS mode enable */
			u16 av8021_as_en: 1;
			/** \brief Reserved */
			u16 reserved3: 3;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u16 reserved3: 3;
			/** \brief AV 802.1AS Mode Enable */
			u16 av8021_as_en: 1;
			/** \brief Reserved */
			u16 reserved2: 3;
			/** \brief transmit timestamp status mode: If set the PHY overwrites the earlier transmit timestamp
			status even if it is not read by the software */
			u16 ts_stat_mode: 1;
			/** \brief Reserved */
			u16 reserved: 4;
			/** \brief Enable checksum correction during One Step Timestamp (OST) for PTP over UDP/IPv4 packets */
			u16 ts_csc_en: 1;
			/** \brief Enable MAC Address for PTP Packet Filtering */
			u16 ts_mac_en: 1;
			/** \brief Select PTP packets for Taking Snapshots */
			u16 snap_type: 2;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Timestamp control high word - raw */
		u16 raw_ts_ctrl_high;
	};
};
/** \endcond */

/** \brief Timestamp control */
struct gpy2xx_ts_ctrl {
	/** \brief Enable timestamp snapshot for event messages */
	u16 ts_evtmsg_en: 1;
	/** \brief Enable snapshot for messages relevant to master */
	u16 ts_master_en: 1;
	/** \brief Select PTP packets for taking snapshots */
	u16 snap_type: 2;
	/** \brief GPC pin to be used */
	u32 gpc_sel;
};

/** \cond INTERNAL */
/** \brief PPS control - low */
struct gpy211_pps_low {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief  'Output Frequency' or 'Flexible PPS Output' control */
			u16 ofc_or_cmd: 4;
			/** \brief Flexible PPS output mode enable */
			u16 pps_mode: 1;
			/** \brief Target time register mode for PPS0 output.
			This indicates how the target time registers are programmed, for example, only for generating the interrupt event,
			generating the interrupt event and starting or stopping, only for starting or stopping PPS signal. */
			u16 ttr_mode: 2;
			/** \brief Reserved */
			u16 reserved: 9;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u16 reserved: 9;
			/** \brief Target time register mode for PPS0 output.
			This indicates how the target time registers are programmed, for example, only for generating the interrupt event,
			generating the interrupt event and starting or stopping, only for starting or stopping PPS signal. */
			u16 ttr_mode: 2;
			/** \brief Flexible PPS Output Mode Enable */
			u16 pps_mode: 1;
			/** \brief  'Output Frequency' or 'Felxible PPS Output' Control */
			u16 ofc_or_cmd: 4;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** PPS Control low word - raw */
		u16 raw_pps_ctrl_low;
	};
};
/** \endcond */

/** \brief PPS Control */
struct gpy2xx_pps_ctrl {
	/** PPS control low word - bit field */
	struct gpy211_pps_low ppsctrl_low;
	/** Init target time - nanoseconds */
	u32 nsec_tgttime;
	/** Init target time - seconds */
	u32 sec_tgttime;
	/** PPS0 interval in nanoseconds */
	u32 pps0_interal;
	/** PPS0 width in nanoseconds */
	u32 pps0_width;
};

/** \cond INTERNAL */
/** \brief PTO control - low */
struct gpy211_pto_low {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief PTP offload enable */
			u16 pto_en: 1;
			/** \brief Automatic PTP SYNC message enable */
			u16 auto_sync_en: 1;
			/** \brief Automatic PTP Pdelay_Req message enable */
			u16 auto_pdreq_en: 1;
			/** \brief Reserved */
			u16 reserved: 1;
			/** \brief Automatic PTP SYNC message trigger */
			u16 auto_sync_trig: 1;
			/** \brief Automatic PTP Pdelay_Req message trigger */
			u16 auto_pdreq_trig: 1;
			/** \brief Disable PTO delay request/response generation */
			u16 delay_rrresp_dis: 1;
			/** \brief Disable peer delay response generation */
			u16 peer_delayrr_dis: 1;
			/** \brief Domain number */
			u16 dom_num: 8;
#elif defined(__BIG_ENDIAN)
			/** \brief Domain Number */
			u16 dom_num: 8;
			/** \brief Disable Peer Delay Response generation */
			u16 peer_delayrr_dis: 1;
			/** \brief Disable PTO Delay Request/Response generation */
			u16 delay_rrresp_dis: 1;
			/** \brief Automatic PTP Pdelay_Req message Trigger */
			u16 auto_pdreq_trig: 1;
			/** \brief Automatic PTP SYNC message Trigger */
			u16 auto_sync_trig: 1;
			/** \brief Reserved */
			u16 reserved: 1;
			/** \brief Automatic PTP Pdelay_Req message Enable */
			u16 auto_pdreq_en: 1;
			/** \brief Automatic PTP SYNC message Enable */
			u16 auto_sync_en: 1;
			/** \brief PTP Offload Enable */
			u16 pto_en: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** PTO control low word - raw */
		u16 raw_pto_ctrl_low;
	};
};
/** \endcond */

/** \brief Log message interval */
struct gpy211_logm_level {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Log sync interval. Allowed values are -15 to 15.
			This field indicates the periodicity of the automatically generated SYNC message when
			the PTP node is master.*/
			s16 log_sync_interval: 8;
			/** \brief Delay_Req to SYNC ratio.
			In slave mode, it is used to control the frequency of Delay_Req messages transmitted.*/
			u16 dr_to_sync_ratio: 3;
			/** \brief Reserved */
			u16 reserved: 5;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u16 reserved: 5;
			/** \brief Delay_Req to SYNC ratio.
			In slave mode, it is used to control the frequency of Delay_Req messages transmitted.*/
			u16 dr_to_sync_ratio: 3;
			/** \brief Log sync interval. Allowed values are -15 to 15.
			This field indicates the periodicity of the automatically generated SYNC message when
			the PTP node is master.*/
			s16 log_sync_interval: 8;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Log message interval - low - raw */
		u16 raw_logm_lvl_low;
	};
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Reserved */
			u16 reserved2: 8;
			/** \brief Log Min Pdelay_Req interval. Allowed values are -15 to 15.
			This field indicates logMinPdelayReqInterval of PTP node. This is used to schedule the periodic
			Pdelay request packet transmission.*/
			s16 log_min_pdr_interval: 8;
#elif defined(__BIG_ENDIAN)
			/** \brief Log Min Pdelay_Req interval. Allowed values are -15 to 15.
			This field indicates logMinPdelayReqInterval of PTP node. This is used to schedule the periodic
			Pdelay request packet transmission.*/
			s16 log_min_pdr_interval: 8;
			/** \brief Reserved */
			u16 reserved2: 8;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Log message interval - high - raw */
		u16 raw_logm_lvl_hi;
	};
};

/** \brief PTP offload control */
struct gpy2xx_pto_ctrl {
	/** PTO  Control low word - bit field */
	struct gpy211_pto_low ptoctrl_low;
	/** Source port identity */
	u8 sport_id[10]; //PTP_SPORT_ID_LEN_BYTE
	/** \brief Log message interval */
	struct gpy211_logm_level logmsg_lvl;
};

/** \brief IEEE 1588 PTP control */
struct gpy211_ptp_ctrl {
	/** \brief Enable/disable TX timestamp capture at PHY level */
	u16 tx_ts_phy: 1;
	/** \brief Enable/disable RX timestamp capture at PHY level */
	u16 rx_ts_phy: 1;
	/** \brief Transmit PTP offset */
	u16 tx_ptp_off: 14;
	/** \brief Transmit PTP transport protocol type.
	Valid values are defined in \ref gpy211_ptp_tx_ptoto enum */
	u16  tx_ptp_tpt: 2;
	/** \brief Enable 1-step vs 2-step timestamp method */
	u16 ts_ostc_en: 1;
	/**  Timestamp required for one-step time correction */
	time64_t tx_ost_corr;
	/**  brief auxiliary snapshot trigger port */
	u16 aux_trig_port;
};

/** \cond INTERNAL */
/** \brief IEEE 1588 timestamp logic - bit fields */
struct gpy211_pmts_cfg {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief GMAC-Full PTP reference clock reset */
			u16 ts_refclk_rst: 1;
			/** \brief Transmit one-step time correction enable */
			u16 ts_ostc_en: 1;
			/** \brief GMAC-Lite PTP reference clock reset */
			u16 tsl_refclk_rst: 1;
			/** \brief Reserved */
			u16 reserved: 1;
			/** \brief TX timestamp FIFO enable */
			u16 tx_fifo_en: 1;
			/** \brief RX timestamp FIFO enable */
			u16 rx_fifo_en: 1;
			/** \brief TX timestamp FIFO reset */
			u16 tx_fifo_rst: 1;
			/** \brief RX timestamp FIFO reset */
			u16 rx_fifo_rst: 1;
			/** \brief PHY TX timestamp enable */
			u16 tx_ts_phy: 1;
			/** \brief PHY RX timestamp enable*/
			u16 rx_ts_phy: 1;
			/** \brief Reserved */
			u16 reserved2: 6;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u16 reserved2: 6;
			/** \brief PHY RX Timestamp enable*/
			u16 rx_ts_phy: 1;
			/** \brief PHY TX Timestamp enable*/
			u16 tx_ts_phy: 1;
			/** \brief RX Timestamp FIFO Reset */
			u16 rx_fifo_rst: 1;
			/** \brief TX Timestamp FIFO Reset */
			u16 tx_fifo_rst: 1;
			/** \brief RX Timestamp FIFO Enable */
			u16 rx_fifo_en: 1;
			/** \brief TX Timestamp FIFO Enable */
			u16 tx_fifo_en: 1;
			/** \brief Reserved */
			u16 reserved: 1;
			/** \brief Lite PTP Reference Clock Reset */
			u16 tsl_refclk_rst: 1;
			/** \brief Transmit One-Step Time Correction Enable */
			u16 ts_ostc_en: 1;
			/** \brief Full PTP Reference Clock Reset */
			u16 ts_refclk_rst: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** IEEE 1588 timestamp logic - raw */
		u16 raw_ts_cfg;
	};
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Transmit PTP offset */
			u16 tx_ptp_off: 14;
			/** \brief Transmit PTP transport protocol type.
			Valid values are defined in \ref gpy211_ptp_tx_ptoto enum */
			u16  tx_ptp_tpt: 2;
#elif defined(__BIG_ENDIAN)
			/** \brief Transmit PTP Transport Protocol Type.
				Valid values are defined in \ref gpy211_ptp_tx_ptoto enum */
			u16 tx_ptp_tpt: 2;
			/** \brief Transmit PTP Offset */
			u16 tx_ptp_off: 14;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** PM configuration of PTP - raw */
		u16 raw_ptp_cfg;
	};
};
/** \endcond */

/** \brief Configured PTP information */
struct gpy211_ptp_cfg {
	/** \brief IEEE 1588 PTP control */
	struct gpy211_ptp_ctrl ptp_ctrl;
	/** \brief Timestamp control */
	struct gpy2xx_ts_ctrl ts_ctrl;
	/** \brief PPS control */
	struct gpy2xx_pps_ctrl pps_ctrl;
	/** \brief PTP offload control */
	struct gpy2xx_pto_ctrl pto_ctrl;
};

/** \brief Status of timestamp FIFO */
struct gpy211_ts_fifo_stat {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief TX FIFO fill level */
			u16 tx_fill_lvl: 5;
			/** \brief Reserved */
			u16 reserved: 1;
			/** \brief TX FIFO overflow */
			u16 tx_ovfl: 1;
			/** \brief TX FIFO underflow */
			u16 tx_udfl: 1;
			/** \brief RX FIFO fill level */
			u16 rx_fill_lvl: 5;
			/** \brief Reserved */
			u16 reserved2: 1;
			/** \brief RX FIFO overflow */
			u16 rx_ovfl: 1;
			/** \brief RX FIFO underflow */
			u16 rx_udfl: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief RX FIFO underflow */
			u16	rx_udfl: 1;
			/** \brief RX FIFO overflow */
			u16	rx_ovfl: 1;
			/** \brief Reserved */
			u16	reserved2: 1;
			/** \brief RX FIFO fill level */
			u16	rx_fill_lvl: 5;
			/** \brief TX FIFO underflow */
			u16	tx_udfl: 1;
			/** \brief TX FIFO overflow */
			u16	tx_ovfl: 1;
			/** \brief Reserved */
			u16	reserved: 1;
			/** \brief TX FIFO fill level */
			u16	tx_fill_lvl: 5;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** IEEE 1588 timestamp logic */
		u16 raw_fifo_stat;
	};
};

#if defined(EN_GMAC_DEBUG_ACCESS) && EN_GMAC_DEBUG_ACCESS
/** \brief Member used by \b tss_low in \ref gpy211_ts_stat */
/** \brief Status of Timestamp Status low word */
struct gpy211_ts_stat_low {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Seconds overflow */
			u16 sec_ovfl: 1;
			/** \brief Target time reached for PPS0 */
			u16 tt_rchd_pps0: 1;
			/** \brief Auxiliary trigger snapshot */
			u16 trig_snapshot: 1;
			/** \brief Target time error for PPS0 */
			u16 tt_err_pps0: 1;
			/** \brief Reserved */
			u16 reserved0: 11;
			/** \brief Tx timestamp status interrupt status */
			u16 txts_int_stat: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief Tx timestamp status interrupt status */
			u16 txts_int_stat: 1;
			/** \brief Reserved */
			u16 reserved0: 11;
			/** \brief Target time error for PPS0 */
			u16 tt_err_pps0: 1;
			/** \brief Auxiliary trigger snapshot */
			u16 trig_snapshot: 1;
			/** \brief Target time reached for PPS0 */
			u16 tt_rchd_pps0: 1;
			/** \brief Seconds overflow */
			u16 sec_ovfl: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Status of timestamp status low word - raw */
		u16 raw_ts_stat_low;
	};
};

/** \brief Member used by \b tss_high in \ref gpy211_ts_stat */
/** \brief Status of timestamp status high word */
struct gpy211_ts_stat_high {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Auxiliary timestamp snapshot trigger identifier */
			u16 auxts_st_id: 4;
			/** \brief Reserved */
			u16 reserved: 4;
			/** \brief Auxiliary timestamp snapshot trigger missed */
			u16 auxts_st_mis: 1;
			/** \brief Number of auxiliary timestamp snapshots */
			u16 auxts_nums: 5;
			/** \brief Reserved */
			u16 reserved2: 2;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u16 reserved2: 2;
			/** \brief Number of auxiliary timestamp snapshots */
			u16 auxts_nums: 5;
			/** \brief Auxiliary timestamp snapshot trigger missed */
			u16 auxts_st_mis: 1;
			/** \brief Reserved */
			u16 reserved: 4;
			/** \brief Auxiliary timestamp snapshot trigger identifier */
			u16 auxts_st_id: 4;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Status of timestamp status low word - raw */
		u16 raw_ts_stat_hi;
	};
};

/** \brief Member used by \b txts_stat in \ref gpy211_ts_stat */
/** \brief Status of Tx timestamp TS status */
struct gpy211_tx_ts_stat {
	/** \brief Transmit timestamp status missed */
	u8 txtss_mis;
	/** \brief Transmit timestamp status - nanoseconds */
	u32 txtss_nsec;
	/** \brief Transmit timestamp status - seconds */
	u32 txtss_sec;
};

/** \brief Status of timestamp status */
struct gpy211_ts_stat {
	/** \brief Status of timestamp status low word */
	struct gpy211_ts_stat_low tss_low;
	/** \brief Status of timestamp status high word */
	struct gpy211_ts_stat_high tss_high;
	/** \brief Status of Tx timestamp status */
	struct gpy211_tx_ts_stat txts_stat;
};
#endif

/** \brief Provides the timestamp of the frame transmitted by the MAC */
struct gpy211_tx_ts {
	/** Transmit frame timestamping - in nanoseconds */
	time64_t tx_ts_stat;
	/** Transmit frame CRC used as ID to match */
	u32 tx_crc_stat;
};

/** \brief Provides the timestamp of the frame received by the MAC */
struct gpy211_rx_ts {
	/** Receive frame timestamping - in nanoseconds */
	time64_t rx_ts_stat;
	/** Receive frame CRC used as ID to match */
	u32 rx_crc_stat;
};

/** \brief auxiliary FIFO status */
struct gpy211_aux_fifo_stat {
	/** \brief FIFO overflow */
	u16 ovfl;
	/** \brief FIFO fill level */
	u16 fill_lvl;
};

/** \brief auxiliary configuration */
struct gpy211_aux_cfg {
	/** \brief enable - 1; disable -0 */
	u16 aux_enable;
	/** \brief OUT_TIMER - 0, GPC0 - 1, GPC1 - 2, GPC2 - 3 */
	u16 aux_trigger_port;
};
/**@}*/ /* GPY211_PTP */

/** \addtogroup GPY211_SYNCE */
/**@{*/
/** \brief SyncE configuration */
struct gpy211_synce {
	/** \brief Enable SyncE.
		Value 1 to enable, value 0 to disable */
	char synce_enable; // VSPEC1_PM_CTRL.SYNCE_EN, TGU_PDI_PD_CTL.EN
	/** \brief Select input frequency of reference clock.
		Valid values are defined in \ref gpy211_synce_clk enum */
	enum gpy211_synce_clk synce_refclk;
	/** \brief Master/slave select.
		Value 0 to select slave mode, else to select master mode*/
	enum gpy211_synce_master_mode master_sel;
	/** \brief Data rate (1G or 2.5G) */
	enum gpy211_data_rate data_rate;
	/** \brief GPC select.
		Configure GPC and GPIOs */
	enum gpy211_gpc_sel gpc_sel;
};
/**@}*/ /* GPY211_SYNCE */

/** \addtogroup GPY211_SGMII */
/**@{*/
/** \brief SGMII link configuration/status */
struct gpy211_sgmii {
	/** \brief SGMII configuration direction.
		Valid values are defined in \ref gpy211_sgmii_linkcfg_dir enum */
	enum gpy211_sgmii_linkcfg_dir linkcfg_dir;
	/** \brief SGMII auto-negotiation mode.
		Valid values are defined in \ref gpy211_sgmii_aneg_mode enum */
	enum gpy211_sgmii_aneg_mode aneg_mode;
	/** \brief This struct contains link configuration and status of the SGMII interface */
	struct gpy211_link link;
	/** \brief Enable Efficient Energy Ethernet (EEE) capability advertisement */
	int eee_enable;
};
/**@}*/ /* GPY211_SGMII */

/** \addtogroup GPY211_MISC */
/**@{*/
/** \brief Wake-on-LAN configuration */
struct gpy211_wolinfo {
	/** \brief Flags for enabled Wake-on-LAN modes.
		Values (\ref GPY211_WOL_FLAG) can be combined with "or".
		If this is 0, Wake-on-LAN is disabled */
	u32 wolopts;
	/** \brief Wake-on-LAN designated MAC */
	u8  mac[6];
	/** \brief Wake-on-LAN SecureON password.
		This is only meaningful if \ref WAKE_MAGICSECURE is set
		in wolopts of \ref gpy211_wolinfo */
	u8  sopass[6];
};

/** \brief Macros used by \b no_nrg_rst in \ref gpy211_ads_ctrl */
/** \brief Auto-downspeed configuration  */
enum ads_adv_status {
	/** \brief Disable advertising all speeds when no energy is detected. */
	ADS_NO_ENERGY_ADV_DIS = 0,
	/** \brief Enable advertising all speeds when no energy is detected. */
	ADS_NO_ENERGY_ADV_EN = 1,
};

/** \brief Macros used by \b downshift_en in \ref gpy211_ads_ctrl */
/** \brief Auto-downspeed status */
enum ads_nbt_ds_status {
	/** \brief downshift, disable */
	ADS_NBT_DOWNSHIFT_DIS = 0,
	/** \brief downshift, enable */
	ADS_NBT_DOWNSHIFT_EN = 1,
};

/** \brief Macros used by \b downshift_thr in \ref gpy211_ads_ctrl */
/** \brief ADS_DOWNSHIFT THRESHOLD MIN */
#define ADS_DOWNSHIFT_THR_MIN     0
/** \brief ADS_DOWNSHIFT THRESHOLD MAX */
#define ADS_DOWNSHIFT_THR_MAX     15

/** \brief Macros used by \b nrg_rst_cnt in \ref gpy211_ads_ctrl */
/** \brief ADS_DOWNSHIFT COUNTER MIN */
#define ADS_NRG_RST_CNT_MIN       0
/** \brief ADS_DOWNSHIFT COUNTER MAX */
#define ADS_NRG_RST_CNT_MAX       255

/** \brief Macros used by \b force_rst in \ref gpy211_ads_ctrl */
/** \brief Force reset setting */
enum ads_force_rst_status {
	/** \brief Wait for timeout before reset capability advertisement. */
	ADS_FORCE_RST_DIS = 0,
	/** \brief Reset capability advertisement */
	ADS_FORCE_RST_EN = 1,
};

/** \brief Link Speed Auto-downspeed Control. */
struct gpy211_ads_ctrl {
	/** \brief  Auto-downspeed configuration */
	enum ads_adv_status no_nrg_rst;
	/** \brief Auto-downspeed status */
	enum ads_nbt_ds_status downshift_en;
	/** \brief NBASE-T Downshift Training Counter Threshold, 0 - 15 */
	u16  downshift_thr;
	/** \brief Force Reset of Downshift Process, 0-disable /1-enable */
	enum ads_force_rst_status force_rst;
	/** \brief Timer to Reset the Downshift process, 0 - 255  */
	u8   nrg_rst_cnt;
};

/** \brief Auto-downspeed status & config */
struct gpy211_ads_sta {
	/** \brief Training attempt counter, the number of attempt, when hit downshift_thr, downshift speed */
	u8 downshift_cnt;
	/** \brief Downshift from 2.5 G to lower speed, 0-no downshift / 1-downshift */
	u8 downshift_2G5;
	/** \brief Downshift from 1 G to lower speed, 0-no downshift / 1-downshift */
	u8 downshift_1G;
	/** \brief ads control config */
	struct gpy211_ads_ctrl ads_ctrl;
};

/** \brief Ultra Low Power mode control */
struct gpy211_ulp_ctrl {
	/** \brief ULP is enabled */
	u8 ulp_en;
	/** \brief GPY will enter ULP only after STA aknowledges the ULP interrupt status */
	u8 ulp_sta_block;
};
/**@}*/ /* GPY211_MISC */

/** \addtogroup GPY211_INIT */
/**@{*/
/** \brief Macros used by \b fw_memory in \ref gpy211_id */
/** \brief Indicates the memory target used for firmware execution */
enum gpy211_fwboot_mode {
	/** \brief Firmware is executed from ROM */
	FW_EXECUTED_FROM_ROM = 0,
	/** \brief Firmware is executed from OTP (OneTimeProgram memory) */
	FW_EXECUTED_FROM_OTP = 1,
	/** \brief Firmware is executed from FLASH */
	FW_EXECUTED_FROM_FLASH = 2,
	/** \brief Firmware is executed from SRAM (GPY24x only) */
	FW_EXECUTED_FROM_SRAM = 3,
};

/** \brief Member used by \b id in \ref gpy211_device */
/** \brief GPHY ID information such as manufacturer data, firmware or API version */
struct gpy211_id {
	/** \brief PHY organizationally unique identifier */
	u32 OUI;
	/** \brief PHY manufacturer's model number */
	u8 model_no;
	/** \brief PHY manufacturer's model family */
	u8 family;
	/** \brief PHY revision number */
	u8 revision;

	/** \brief Chip manufacturer ID */
	u16 manufacturer_id;
	/** \brief Chip part number */
	u16 part_no;
	/** \brief Chip version */
	u16 version;

	/** \brief The most recently read firmware major version number */
	u16 fw_major;
	/** \brief The most recently read firmware minor version number */
	u16 fw_minor;
	/** \brief The most recently read firmware release indication:
		0 - test version, 1 - released version */
	u16 fw_release;
	/** \brief The memory target used for firmware execution, valid from FW 8747 onwards only.
		Valid values are defined in \ref gpy211_fwboot_mode enum */
	enum  gpy211_fwboot_mode fw_memory;

	/** \brief API major version number */
	u16 drv_major;
	/** \brief API minor version number */
	u16 drv_minor;
	/** \brief API release indication:
		0 - test version, 1 - general available (GA) release,
		>= 2 - maintenance release (MR) */
	u16 drv_release;
	/** \brief The most recently read firmware patch indication:
		1 - GA/MR release, >= 2 - patch release */
	u16 drv_patch;
};
/**@}*/ /* GPY211_INIT */

/** \addtogroup GPY211_MISC */
/**@{*/
/** \brief GPHY temperature information */
struct gpy211_pvt {
	/** \brief GPHY temperature in degree Celsius scale */
	int temperature;
};
/**@}*/ /* GPY211_MISC */

/** \addtogroup GPY211_PM */
/**@{*/
/** \cond INTERNAL */
/** \brief PM module settings - obsolete */
struct pm_config {
	/** \brief Bypass Smart-AZ subsystem */
	u8 bypass_gmac;
	/** \brief Bypass MACsec Ingress & Egress modules */
	u8 bypass_macsec;
	/** \brief Discard packet if CRC error is raised by MACsec */
	u8 drop_on_crc_err;
	/** \brief Discard packet if packet error is raised by MACsec */
	u8 drop_on_pkt_err;
	/** \brief Discard packet if security fail error is raised by MACsec */
	u8 drop_on_sec_fail;
	/** \brief Discard packet if classification error is raised by MACsec */
	u8 class_drop;
	/** \brief GMAC lite is in custom 3G overclocked mode */
	u8 cust_3g_en;
	/** \brief SGMII loopback mode */
	u8 sgmii_lb_en;
};

/** \brief Macros used by \b crc_pad_ctrl in \ref pm_gmac_cfg */
/** \brief CRC & Padding control options - obsolete */
enum crc_pad_ctrl {
	/** \brief Insert both CRC and paddding */
	PM_INSERT_CRC_AND_PAD = 0,
	/** \brief Insert CRC only but no paddding */
	PM_INSERT_CRC_NO_PAD = 1,
	/** \brief Do not insert CRC or paddding */
	PM_INSERT_NO_CRC_AND_PAD = 2,
	/** \brief Replace CRC but no paddding */
	PM_INSERT_CRC_REPLACE_NO_PAD = 2,
};

/** \brief BM configuration - obsolete */
struct pm_gmac_cfg {
	/** \brief Controls the Smart-AZ insertion of CRC and/or padding.
	Valid values are defined in \ref crc_pad_ctrl enum */
	enum crc_pad_ctrl crc_pad_ctrl;
	/** \brief Indicates to the MAC to corrupt the packet by forcing CRC error (for debugging only) */
	u8 tx_err_input;
	/** \brief Data endianness: 0 - Little endian, 1 - Big endian */
	u8 big_endian;
};

/** \brief Inter-Packet Gap in bytes - obsolete */
enum mac_ipg {
	/** \brief 12 Bytes */
	MAC_IPG_96BITS = 0,
	/** \brief 11 Bytes */
	MAC_IPG_88BITS = 1,
	/** \brief 10 Bytes */
	MAC_IPG_80BITS = 2,
	/** \brief 09 Bytes */
	MAC_IPG_72BITS = 3,
	/** \brief 08 Bytes */
	MAC_IPG_64BITS = 4,
	/** \brief 07 Bytes */
	MAC_IPG_56BITS = 5,
	/** \brief 06 Bytes */
	MAC_IPG_48BITS = 6,
	/** \brief 05 Bytes */
	MAC_IPG_40BITS = 7,
};

/** \brief Smart-AZ Packet Size configuration - obsolete */
struct gmac_pkt_cfg {
	/** \brief Jumbo packet enable (9,018 bytes (9,022 for VLAN tagged)) */
	u8 jumbo_en;
	/** \brief Jabber disable (Allow packet transfer of up to 16,383 bytes).*/
	u8 tx_jabber_dis;
	/** \brief Watchdog disable (Allow pkt reception of up to 16,383 bytes) */
	u8 watchdog_dis;
	/** \brief Automatic Pad or CRC Stripping for ether 'length' packets */
	u8 pad_crc_strip_en;
	/** \brief CRC Stripping for ether 'type' packets */
	u8 crc_strip_en;
	/** \brief IEEE 802.3as support for 2K packets */
	u8 support_2kp;
	/** \brief Inter-Packet Gap in bytes.
	Valid values are defined in \ref mac_ipg enum */
	enum mac_ipg mac_ipg;
};
/** \endcond */

/** \brief Pkt Counters */
struct gmacf_counters {
	/** \brief Tx packet counter that counts both good and bad frames */
	u32 tx_good_bad;
	/** \brief Tx Underflow error packet counter */
	u32 tx_uflow_err;
	/** \brief Tx packet pounter to count only good frames */
	u32 tx_good;
	/** \brief Tx oversized good-only packet counter */
	u32 rx_good_bad;
	/** \brief Rx packet counter that counts both good and bad frames */
	u32 tx_osize_good;
	/** \brief Rx CRC error packet counter */
	u32 rx_crc_err;
	/** \brief Rx undersize good-only packet counter */
	u32 rx_usize_good;
	/** \brief Rx oversized good-only packet counter */
	u32 rx_osize_good;
};

/** \brief MMC counter control */
struct gmacf_counter_ctrl {
	/** \brief Counter reset */
	u8 reset_counters;
	/** \brief Counter stop rollover */
	u8 stop_rollover;
	/** \brief Reset on read */
	u8 clear_on_read;
	/** \brief Counter freeze */
	u8 freeze_counters;
	/** \brief Counters preset */
	u8 preset_counters;
	/** \brief Full-half preset */
	u8 preset_half_full;
	/** \brief Update MMC counters for dropped broadcast packets */
	u8 count_dropped_bc;
};

/** \brief Macsec control */
struct gpy211_macsec {
	/** \brief Discard packet if CRC error is raised by MACsec */
	u8 drop_on_crc_err;
	/** \brief Discard packet if packet error is raised by MACsec */
	u8 drop_on_pkt_err;
	/** \brief Discard packet if security fail error is raised by MACsec */
	u8 drop_on_sec_fail;
	/** \brief Discard packet if classification error is raised by MACsec */
	u8 class_drop;
};
/**@}*/ /* GPY211_PM */

/** \addtogroup GPY211_BM */
/**@{*/
/** \cond INTERNAL */
/** \brief PM shared buffer configuration */
struct bm_cfg {
	/** \brief SB 0 Start location */
	u16 sb0_start;
	/** \brief SB 0 End location */
	u16 sb0_end;
	/** \brief SB 0 Packet threshold to start the dequeue */
	u16 sb0_pkt_thresh;
	/** \brief SB 1 Start location */
	u16 sb1_start;
	/** \brief SB 1 End location */
	u16 sb1_end;
	/** \brief SB 1 Packet threshold to start the dequeue */
	u16 sb1_pkt_thresh;
};

/** \brief Shared buffer status */
struct pm_bm_status {
	/** \brief SB 0 overflow indicator */
	u8 sb0_ov;
	/** \brief SB 0 Tx register overflow indicator */
	u8 sb0_tx_reg_ov;
	/** \brief SB 0 Rx register overflow indicator */
	u8 sb0_rx_reg_ov;
	/** \brief SB 1 overflow indicator */
	u8 sb1_ov;
	/** \brief SB 1 Tx register overflow indicator */
	u8 sb1_tx_reg_ov;
	/** \brief SB 1 Rx register overflow indicator */
	u8 sb1_rx_reg_ov;
	/** \brief SB 0 retry indicator */
	u8 sb0_retry;
	/** \brief SB 0 Sent indicator */
	u8 sb0_sent;
	/** \brief SB 1 retry indicator */
	u8 sb1_retry;
	/** \brief SB 1 sent indicator */
	u8 sb1_sent;
	/** \brief SB 0 complete indicator */
	u8 sb0_complete;
	/** \brief SB 1 complete indicator */
	u8 sb1_complete;
};
/** \endcond */

/** \brief Macros used by \b pause_low_thresh in \ref pause_cfg */
/** \brief Pause low threshold in time slots */
enum pause_low_thresh {
	/** \brief PT-4 slot times */
	PLT_PT_4ST = 0,
	/** \brief PT-28 slot times */
	PLT_PT_28ST = 1,
	/** \brief PT-36 slot times */
	PLT_PT_36ST = 2,
	/** \brief PT-144 slot times */
	PLT_PT_144ST = 3,
	/** \brief PT-256 slot times */
	PLT_PT_256ST = 4,
	/** \brief PT-512 slot times */
	PLT_PT_512ST = 5,
};

/** \brief GMAC-Lite Tx flow control configuration */
struct pause_cfg {
	/** \brief Flow control busy or backpressure activate */
	u8 flow_ctrl_busy;
	/** \brief PM GMAC flow control enable */
	u8 pm_gmacl_fc;
	/** \brief Tx flow control enable */
	u8 tx_flow_ctrl;
	/** \brief Disable zero-quanta pause */
	u8 dis_zquanta_pause;
	/** \brief Pause time */
	u16 pause_time;
	/** \brief Pause frame Src MAC to send with */
	u8 tx_fc_mac[6];
	/** \brief Pause low threshold.
	Valid values are defined in \ref pause_low_thresh enum */
	enum pause_low_thresh pause_low_thresh;
	/** \brief Pause is triggered when available buf size is
			   (wptr - rptr) < PAUSE_THRES */
	u16 pause_assert_thresh;
	/** \brief To create a hysteresis to avoid too frequent PAUSE/UN-PAUSE */
	u16 pause_deassert_thresh;
};

/** \brief Macros used by \b ppm in \ref tune_freq */
/** \brief PHY's dummy MAC freuency to tune */
enum mac_freq_tune {
	/** \brief Standard USXMII Compliance Test condition.
	MACs operate at frequency corresponding to line rate. This is the
	recommended setting when it is accepted to have marginal packet drop at
	maximum data rate testing above 99.9% of maximum rate. */
	FREQ_PPM_000 = 0,
	/** \brief Default working condition.
	MACs operate at frequency+100ppm corresponding to line rate. This is the
	default settings for 100% of maximum rate traffic condition with high
	quality XTALs that generate clocks within +/-50ppm deviation. */
	FREQ_PPM_100 = 1,
	/** \brief Long Duration 100% Traffic Stress Test condition.
	MACs operate at frequency+300ppm corresponding to line rate. This test
	mode is to compensate all the worst case frequency deviations. */
	FREQ_PPM_300 = 2,
};

/** \brief Tune the frequency of MACs within GPY in USXGMII Mode */
struct tune_freq {
	/** \brief Pause low threshold.
	Valid values are defined in \ref pause_low_thresh enum */
	enum mac_freq_tune ppm;
};
/**@}*/ /* GPY211_BM */

/** \addtogroup GPY211_INIT */
/**@{*/

/** \brief Data structure representing the GPHY entity. The user application uses this
	struct to communicate with GPHY APIs.*/
struct gpy211_device {
	/**
		\brief Function called by API when entering an API function.
		The user application should implement this function for resource protection
		in a multi-threaded application, or NULL for a single-threaded application.

		\param lock_data Pointer to user data provided by the user application in
		lock_data of \ref gpy211_device.

		\return No return value.
	*/
	void (*lock)(void *lock_data);

	/**
		\brief Function called by API when leaving an API function.
		The user application should implement this function for resource protection
		in a multi-threaded application, or NULL for a single-threaded application.

		\param lock_data Pointer to user data provided by the user application in
		lock_data of \ref gpy211_device.

		\return No return value.
	*/
	void (*unlock)(void *lock_data);

	/** \brief User data for lock, unlock of \ref gpy211_device. The user application
	    should provide proper value	before calling any GPHY APIs. */
	void *lock_data;

	/**
		\brief Function for MDIO read operation on MDIO bus. The user application
		must implement this function for a GPHY API accessing the MDIO device.
		Both Clause 22 and Clause 45 addressing should be supported. If the MDIO
		master does not support Clause 45 addressing, the user application should
		use MMD indirect access registers at 0x13 and 0x14 for the implementation.

		\param mdiobus_data Pointer to user data provided by the user application
		in mdiobus_data of \ref gpy211_device.

		\param addr This is the PHY address.

		\param regnum In Clause 22, this is 5-bit register number to be written.
		In Clause 45, bits 0~15 are the register number, bits 16~20 are the device address
		(MMD) to be written to, and bit 30 is a flag \ref MII_ADDR_C45 to indicate Clause 45 type.

		\return
		- >=0: register value
		- <0: error code
	*/
	int (*mdiobus_read)(void *mdiobus_data, u16 addr, u32 regnum);

	/**
		\brief Function for MDIO write operation on MDIO bus. The user application
		must implement this function for a GPHY API accessing the MDIO device.
		Both Clause 22 and Clause 45 addressing should be supported. If the MDIO
		master does not support Clause 45 addressing, the user application should
		use MMD indirect access registers at 0x13 and 0x14 for the implementation.

		\param mdiobus_data Pointer to user data provided by user application
		in mdiobus_data of \ref gpy211_device.

		\param addr This is the PHY address.

		\param regnum In Clause 22, this is 5-bit register number to be written.
		In Clause 45, bits 0~15 are the register number, bits 16~20 are the device address
		(MMD) to be written to, and bit 30 is a flag \ref MII_ADDR_C45 to indicate Clause 45 type.

		\param val This is 16-bit value to be written to register.

		\return
		- 0: successful
		- <0: error code
	*/
	int (*mdiobus_write)(void *mdiobus_data, u16 addr, u32 regnum, u16 val);

	/** \brief User data for mdiobus_read and mdiobus_write of
		\ref gpy211_device. The user application must provide proper
		value before calling any GPHY APIs. */
	void *mdiobus_data;

	/** \brief Slave MDIO address for internal register access.
		Default value is 0x1F. The user application must provide proper value
		before calling any GPHY APIs. The value must be the same as
		SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG.ADDR which is pin-strapped. */
	int smdio_addr;

	/** \brief This is the GPHY address for Standard MDIO and MMD register access.
		This address is from PMU_PDI_REGISTERS_GPHY_GPS1.MDIO_PHY_ADDR
		which is pin-strapped. The user application must call \ref gpy2xx_init
		before any other APIs for initialization. */
	int phy_addr;

	/** \brief This is private data for GPHY APIs. The user application must call
		\ref gpy2xx_init before any other APIs for initialization. And call
		\ref gpy2xx_uninit to free the device when cleaning up. */
	void *priv_data;

	/**
		\brief Pointer to data structure.
		For most users, this is NULL. This is a workaround for
		applications that have multiple processes, a separate address for
		each process and share the data section. In this case, the user
		needs to provide the data pointer referring to the shared data. Only fields
		id, link, and wol_supported of \ref gpy211_device in the shared data are used.
	*/
	struct gpy211_device *shared_data;

	/** \brief PHY ID */
	struct gpy211_id id;

	/** \brief Link configuration and status. The user application uses
		APIs defined in \ref GPY211_LINK_API, such as \ref gpy2xx_config_advert,
		\ref gpy2xx_setup_forced, \ref gpy2xx_restart_aneg,
		\ref gpy2xx_config_aneg, \ref gpy2xx_aneg_done, \ref gpy2xx_update_link,
		and \ref gpy2xx_read_status for configuration purposes or to read out information. */
	struct gpy211_link link;

	/** \brief Flags for supported Wake-on-LAN modes.
		Values (\ref GPY211_WOL_FLAG) can be combined with "or" */
	u32 wol_supported;
	/** \brief  MACsec capable (value 1) or not capable (value 0) */
	u8 macsec_supported;
	/** \brief  Max MACSec SAs supported */
	u8 nr_of_sas;
	/** \brief GMAC module information used in GMAC APIs */
	void *gmac_data;
	/** \brief MACsec module information used in MACsec APIs */
	void *macsec_data;
	/** \brief PTP clock (in Hz) */
	u32 ptp_clock;
	/** \brief GMAC-Full base address */
	u32 gmacf_base_addr;
	/** \brief GMAC-Lite base address */
	u32 gmacl_base_addr;
	/** \brief Packet Manager base address */
	u32 pm_base_addr;
	/** \brief  SyncE capable (value 1) or not capable (value 0) */
	u8 synce_supported;
	/** \brief  Allows forcing of master or slave mode manually. Applicaple when
		choosing forced link speed of 2.5G or 1G only */
	u8 mstr_slave;
};
/**@}*/ /* GPY211_INIT */

/** \addtogroup GPY211_GPY24X_USXGMII */
/**@{*/
/** \brief USXMGII EQ configuration (only for GPY24X) */
struct gpy211_usxgmii_reach {
	/** \brief Trace length.
		Value 0x00 - 0x3 */
	u16 trace_len;
	/** \brief Tx EQ min.
		Value 0x00 - 0x3F */
	u16 tx_eq_main;
	/** \brief Tx Pre-Emphasis level.
		Valid 0x00 - 0x3F */
	u16 tx_eq_pre;
	/** \brief Tx Post-Emphasis level.
		Valid 0x00 - 0x3F */
	u16 tx_eq_post;
	/** \brief Tx voltage Boost enable on lane 0.
		Valid 0 - disable / 1 - enable */
	u16 tx_vboost_en;
	/** \brief Tx voltage Boost maximum level.
		Valid 0x00 - 0x07*/
	u16 tx_vboost_lvl;
	/** \brief Tx current boost level on lane 0 .
		Valid 0x00 - 0x07*/
	u16 tx_iboost_lvl;
	/** \brief Rx Equalization Attenuation level for lane 0.
		Valid 0x00 - 0x07*/
	u16 rx_eq_att_lvl;
	/** \brief Rx Equalization VGA1 Gain on lane 0.
		Valid 0x00 - 0x0F*/
	u16 rx_eq_vga1_gain;
	/** \brief Rx Equalization VGA2 Gain on lane 0.
		Valid 0x00 - 0x0F*/
	u16 rx_eq_vga2_gain;
	/** \brief Rx Equalization CTLE Boost value on lane 0.
		Valid 0x00 - 0x1F*/
	u16 rx_eq_ctle_boost;
	/** \brief Rx Equalization CTLE Pole Value on lane 0.
		Valid 0x00 - 0x07*/
	u16 rx_eq_ctle_pole;
	/** \brief Rx Equalization DFE Tap1 Value on lane 0.
		Valid 0x00 - 0xFF*/
	u16 rx_eq_dfe_tap1;
	/** \brief Rx afe_en on lane 0.
		Valid 0 - disable / 1 - enable */
	u16 rx_afe_adapt_en;
	/** \brief Rx dfe_en on lane 0.
		Valid 0 - disable / 1 - enable */
	u16 rx_dfe_adapt_en;
};

/** \brief USXMGII PCS/PMA link status (only for GPY24X) */
struct gpy211_usxgmii_pcs_pma_linksts {
	/** \brief PMA latched link status.
		Valid 0 - link down / 1 - link up */
	int pma_latched_linksts;
	/** \brief PMA link status.
		Valid 0 - link down / 1 - link up */
	int pma_linksts;
	/** \brief PCS latched link status.
		Valid 0 - link down / 1 - link up */
	int pcs_latched_linksts;
	/** \brief PCS link status.
		Valid 0 - link down / 1 - link up */
	int pcs_linksts;
};

/** \brief USXMGII MII link status for each lane/slice (only for GPY24X) */
struct gpy211_usxgmii_mii_linksts {
	/** \brief Latched link status.
		Valid 0 - link down / 1 - link up */
	int latched_linksts;
	/** \brief Link status.
		Valid 0 - link down / 1 - link up */
	int linksts;
};

/** \brief USXMGII auto-negotiation status (only for GPY24X) */
struct gpy211_usxgmii_aneg_status {
	/** \brief The Clause 37 auto-negotiation in the USXGMII mode.
			0 - Configures the xpcs as the MAC side.
			1 - Configures the xpcs as the PHY side. */
	int phy_side;
	/** \brief Force link speed/duplex.
			0 - disabled
			1 - enabled */
	int force_mode;
	/** \brief Enable auto-negotiation.
			0 - disabled
			1 - enabled */
	int aneg_enable;
	/** \brief Auto-negotiation complete. Clear on read. FW may clear this
		   field before API read.
			0 - not complete
			1 - completed */
	int aneg_complete;
	/** \brief Link status from link partner advertisement when
		   phy_side is 0 and aneg_enable is 1.
			0 - link down
			1 - link up */
	int aneg_linksts;
	/** \brief Link speed (Mbps) from ANEG result when phy_side is 0 and
		   aneg_enable is 1. */
	int aneg_speed;
	/** \brief Duplex from ANEG result when phy_side is 0 and
		   aneg_enable is 1.
			0 - Half duplex
			1 - Full duplex */
	int aneg_duplex;
	/** \brief Link status. */
	int mii_linksts;
	/** \brief Link speed (Mbps). This is different from aneg_speed if
		   phy_side is 1 or force_mode is 1. */
	int mii_speed;
	/** \brief Duplex. This is different from aneg_duplex if phy_side is 1
		   or force_mode is 1.
			0 - Half duplex
			1 - Full duplex */
	int mii_duplex;
};

/** \brief Macros used by \b mode in \ref gpy211_usxgmii_tx_bert_config */
/** \brief TX BERT mode (only for GPY24X) */
enum gpy211_tx_bert_mode {
	/** \brief DWC_xpcs transmits the square wave test pattern */
	BERT_SQUAREWAVE_TX = 0,
	/** \brief DWC_xpcs transmits Pseudo-Random  Test Pattern */
	BERT_PSEUDO_RANDOM_TX = 1,
	/** \brief DWC_xpcs transmits PRBS31 Transmit Pattern */
	BERT_PRBS31_TX = 2,
	/** \brief DWC_xpcs transmits PRBS9 Transmit Pattern */
	BERT_PRBS9_TX = 3,
	/** \brief disable TX BERT mode.*/
	BERT_TX_MODE_DISABLE = 4,
};

/** \brief Macros used by \b nval_sel in \ref gpy211_usxgmii_tx_bert_config */
/** \brief SQUAREWAVE PERIOD (only for GPY24X) */
enum gpy211_tx_bert_mode_nval_sel {
	/** \brief 4 bit times for which Ones and Zeros
	should be driven on the serial lines (square wave period) */
	BERT_TX_NVAL_SEL_4 = 0,
	/** \brief 5 bit times for which Ones and Zeros
	should be driven on the serial lines (square wave period) */
	BERT_TX_NVAL_SEL_5 = 1,
	/** \brief 6 bit times for which Ones and Zeros
	should be driven on the serial lines (square wave period) */
	BERT_TX_NVAL_SEL_6 = 2,
	/** \brief 7 bit times for which Ones and Zeros
	should be driven on the serial lines (square wave period) */
	BERT_TX_NVAL_SEL_7 = 3,
	/** \brief 8 bit times for which Ones and Zeros
	should be driven on the serial lines (square wave period) */
	BERT_TX_NVAL_SEL_8 = 4,
	/** \brief 9 bit times for which Ones and Zeros
	should be driven on the serial lines (square wave period) */
	BERT_TX_NVAL_SEL_9 = 5,
	/** \brief 10 bit times for which Ones and Zeros
	should be driven on the serial lines (square wave period) */
	BERT_TX_NVAL_SEL_10 = 6,
	/** \brief 11 bit times for which Ones and Zeros
	should be driven on the serial lines (square wave period) */
	BERT_TX_NVAL_SEL_11 = 7,
	/** \brief unsupported NVAL_SEL */
	BERT_TX_NVAL_SEL_UNSUPPORTED = 8,
};

/** \brief TX BERT config (only for GPY24X) */
struct gpy211_usxgmii_tx_bert_config {

	/** \brief tx bert mode configuration*/
	enum gpy211_tx_bert_mode mode;
	/** \brief Square wave period. When square wave test pattern generation is
	enabled via above \b mode variable, this field indicates the number of bit
	times for which Ones and Zeros should be driven on the serial lines (square
	wave period). */
	enum gpy211_tx_bert_mode_nval_sel nval_sel;

};

/** \brief Macros used by \b mode in \ref gpy211_usxgmii_rx_bert_config */
/** \brief RX BERT mode (only for GPY24X) */
enum gpy211_rx_bert_mode {
	/** \brief DWC_xpcs receive Pseudo-Random  Test Pattern */
	BERT_PSEUDO_RANDOM_RX = 0,
	/** \brief DWC_xpcs receive PRBS31 receive Pattern */
	BERT_PRBS31_RX = 1,
	/** \brief DWC_xpcs receive PRBS9 receive Pattern */
	BERT_PRBS9_RX = 2,
	/** \brief disable RX BERT mode.*/
	BERT_RX_MODE_DISABLE = 3,
};

/** \brief RX BERT config (only for GPY24X) */
struct gpy211_usxgmii_rx_bert_config {
	/** \brief rx bert mode configuration*/
	enum gpy211_rx_bert_mode mode;
};

/** \brief Rx BERT statistics (only for GPY24X) */
struct gpy211_usxgmii_rx_bert_statistics {
	/** \brief Test Pattern Error Counter ,this field indicates
		the test pattern mismatch error count in RX path*/
	int tp_error_count ;
	/** \brief Error Block Counter ,This field indicates invalid 66-bit blocks
		in the receive path*/
	int error_block_count;
	/** \brief Bit Error Rate Counter , This field indicates the
		high bit error count on the receive path. */
	int bit_error_rate_counter;
	/** \brief Latched High Bit Error Rate,High bit error is
		when more than 15 invalid 66-bit blocks are received
		in 125us duration*/
	int latched_high_bit_err_rate;
	/** \brief Latched Block Lock. */
	int latched_block_lock;
};

/** \brief PCS/SERDES loopback mode (only for GPY24X) */
enum gpy211_usxgmii_loopback_mode {
	/** \brief Loopback is disabled. */
	USXGMII_LOOPBACK_DISABLE = 0,
	/** \brief Tx to Rx loopback at serial interface of SERDES is
		   enabled. */
	USXGMII_LOOPBACK_TX2RX,
	/** \brief Rx to Tx loopback at MII interface (parallel interface)
		   is enabled. */
	USXGMII_LOOPBACK_RX2TX,
	/** \brief Number of valid loopback modes. */
	USXGMII_LOOPBACK_MAX,
	/** \brief Invalid configuration of loopback mode. */
	USXGMII_LOOPBACK_INVALID = USXGMII_LOOPBACK_MAX
};

/**@}*/ /* GPY211_GPY24X_USXGMII */

/** @cond INTERNAL */
/** \brief CHIP ID supported */
#define ID_P31G		0x00
#define ID_P34X		0x08
#define ID_P34X_LGS	0x0E
/** @endcond */


/**********************
	APIs
 **********************/

/** @cond INTERNAL */

/** \addtogroup GPY211_MDIO */
/**@{*/
//#if defined(EN_SMDIO_RW) && EN_SMDIO_RW
/**
	\brief API for Slave MDIO read operation.
	\details The user application uses this API	to read the internal registers of the GPHY.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param regaddr 16-bit register number.

	\return
	- >=0: register value
	- <0: error code
*/
static inline int gpy2xx_smdio_read(struct gpy211_device *phy, u32 regaddr)
{
	int ret;

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	ret = phy->mdiobus_write(phy->mdiobus_data, phy->smdio_addr,
				 SMDIO_BADR, regaddr);

	if (ret < 0)
		return ret;

	return phy->mdiobus_read(phy->mdiobus_data, phy->smdio_addr, SMDIO_TOFF);
}

/**
	\brief API for Slave MDIO write operation.
	\details The user application uses this API	to write to the internal registers of the GPHY.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param regaddr 16-bit register number.

	\param data 16-bit value to be written.

	\return
	- =0: successful
	- <0: error code
*/
static inline int gpy2xx_smdio_write(struct gpy211_device *phy, u32 regaddr,
				     u16 data)
{
	int ret;

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	ret = phy->mdiobus_write(phy->mdiobus_data, phy->smdio_addr,
				 SMDIO_BADR, regaddr);

	if (ret < 0)
		return ret;

	return phy->mdiobus_write(phy->mdiobus_data, phy->smdio_addr,
				  SMDIO_TOFF, data);
}
//#endif

/**
	\brief Debug API for reading individual MDIO register of PHY/STD device.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param regaddr 16-bit register number.

	\return
	- >=0: register value
	- <0: error code
*/
static inline int gpy2xx_read(struct gpy211_device *phy, u32 regaddr)
{
	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}
	return phy->mdiobus_read(phy->mdiobus_data, phy->phy_addr, regaddr);
}

/**
	\brief Debug API for writing individual MDIO register of PHY/STD device.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param regaddr 16-bit register number.

	\param data 16-bit value to be written to given 'regaddr' address.

	\return
	- =0: successful
	- <0: error code
*/
static inline int gpy2xx_write(struct gpy211_device *phy, u32 regaddr,
			       u16 data)
{
	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	return phy->mdiobus_write(phy->mdiobus_data, phy->phy_addr,
				  regaddr, data);
}

/**
	\brief Debug API for reading individual register of an MMD device.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param devtype The MMD (MDIO Manageable Device) to read from.

	\param regaddr 16-bit register number on the MMD.

	\return
	- >=0: register value
	- <0: error code
*/
static inline int gpy2xx_read_mmd(struct gpy211_device *phy, int devtype,
				  u32 regaddr)
{
	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	return phy->mdiobus_read(phy->mdiobus_data, phy->phy_addr,
				 (MII_ADDR_C45 | ((devtype & 0x1f) << 16) | (regaddr & 0xffff)));
}

/**
	\brief Debug API for writing individual register of an MMD device.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param devtype The MMD (MDIO Manageable Device) to write to.

	\param regaddr 16-bit register number on the MMD.

	\param data 16-bit value to be written to given 'regaddr' address.

	\return
	- =0: successful
	- <0: error code
*/
static inline int gpy2xx_write_mmd(struct gpy211_device *phy, int devtype,
				   u32 regaddr, u16 data)
{
	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	return phy->mdiobus_write(phy->mdiobus_data, phy->phy_addr,
				  (MII_ADDR_C45 | ((devtype & 0x1f) << 16) | (regaddr & 0xffff)), data);
}

/**@}*/ /* GPY211_MDIO */

/** @endcond */

/** \addtogroup GPY211_INIT */
/**@{*/

/**
	\brief Initialization.
	\details This is the first API called by the user application before any other API.
	This API checks for MDIO access to the given PHY address and verifies the OUI
	(Operationally Unique ID). It reads and stores other information, such as manufacturer data,
	firmware/API version, default supported & advertised link configuration & status. This is
	filled into the \ref gpy211_device structure. The user application must provide
	proper values/function-pointers for mdiobus_read, mdiobus_write, mdiobus_data,
	and smdio_addr in the \ref gpy211_device structure.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_init(struct gpy211_device *phy);

/**
	\brief Cleanup.
	\details This is last API called by the user application for un-initialization purposes.
	The application has to implement/modify this API to unconfigure/release resources,
	disable interrupts etc.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
*/
int gpy2xx_uninit(struct gpy211_device *phy);

/**
	\brief Resets the PHY to its default state.
	\details Triggers a soft reset. Active links are terminated.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_soft_reset(struct gpy211_device *phy);

/**
	\brief Poll PHY reset status
	\details The user application uses \ref gpy2xx_soft_reset to trigger a soft reset.
	Afterwards it uses this API to poll every few milliseconds (e.g. every 50 ms) to determine when the reset has completed,
	 i.e. until a positive value is returned.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- >0: reset complete
	- =0: reset incomplete
	- <0: error code
*/
int gpy2xx_poll_reset(struct gpy211_device *phy);
/**@}*/ /* GPY211_INIT */

/** \addtogroup GPY211_LINK_API */
/**@{*/
/**
	\brief Configures the link advertisement parameters.
	\details It writes MII_ADVERTISE with the appropriate values, after masking the advertising parameter values
	to make sure that only the parameters supported by the firmware are advertised. The user must call \ref gpy2xx_restart_aneg
	to make sure the effective paramaters will be advertised to the link partner.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- >0: advertisement is changed successfully
	- =0: advertisement is not changed
	- <0: error code
*/
int gpy2xx_config_advert(struct gpy211_device *phy);

/**
	\brief Forcefully sets the link speed and duplex mode.
	\details It configures the PHY to forcefully set the link speed and duplex.
	This disables the auto-negotiation at this node and the user application must set
	the link partner's speed and duplex mode forcefully at the other end of the link node.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_setup_forced(struct gpy211_device *phy);

/**
	\brief Enable and restart standard auto-negotiation.
	\details The user application must call this API to restart standard auto-negotiation,
	and also to make sure the effective parameters are set in
	\ref gpy2xx_config_advert. These will be advertised to the link partner when auto-negotiation is restarted.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_restart_aneg(struct gpy211_device *phy);

/**
	\brief Enable & restart auto-negotiation or set link speed & duplex
	forcefully dependending on given autoneg of \ref gpy211_link.
	\details If autoneg is 1, this API calls \ref gpy2xx_config_advert and
	\ref gpy2xx_restart_aneg to advertise and restart auto-negotiation.
	If autoneg is 0, \ref gpy2xx_setup_forced is used to set link speed and duplex
	forcefully. In this case, the auto-negotiation is disabled and it is the responsibility of the user
	application to take care of setting the same speed and duplex for the link partner so that the
	link is UP and running, otherwise the link will be DOWN.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_config_aneg(struct gpy211_device *phy);

/**
	\brief Gets the restarted auto-negotiation status.
	\details The user application must call and check to see if auto-negotiation has completed
	before reading the link status \ref gpy2xx_read_status after auto-negotiation was restarted
	using \ref gpy2xx_restart_aneg.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =1: auto-negotiation is done
	- =0: auto-negotiation is incomplete or there was an error during negotiation
	- <0: error code
*/
int gpy2xx_aneg_done(struct gpy211_device *phy);

/**
	\brief Updates the current link state of UP or DOWN link of \ref gpy211_link
	link state.
	\details The user application can call this API to only update the link state (UP or DOWN)
	in the variable 'link' of \ref gpy211_link.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_update_link(struct gpy211_device *phy);

/**
	\brief Reads and updates the link parameters and status.
	\details The user application can call this API to read and update the link parameters
	of this and the partner node. It also updates the link state of this node.
	If autoneg is 0, speed and duplex of \ref gpy211_link are retrieved from PHY.
	If autoneg is 1, link partner information is updated in lp_advertising,
	speed, duplex, pause, and asym_pause of \ref gpy211_link.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_read_status(struct gpy211_device *phy);

/**
	\brief Reads and updates the PHY FW parameters and boot status.
	\details The user application can call this API to read and update the most recently
	updated FW parameters, like Firmware major & minor version, Firmware release indication
	of test vs engineered and the memory target used for firmware execution.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: Firmware is executed from ROM
	- =1: Firmware is executed from OTP (OneTimeProgram memory)
	- =2: Firmware is executed from FLASH
	- =3: Firmware is executed from SRAM (GPY24x only)
	- <0: error code
*/
int gpy2xx_read_fw_info(struct gpy211_device *phy);
/**@}*/ /* GPY211_LINK */

/** \addtogroup GPY211_GPIO_API */
/**@{*/
/**
	\brief API to configure GPIO pin.
	For debugging only, will be removed in future revisions.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param gpio Pointer to \ref gpy211_gpio. The user application should give
	proper values in this structure.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gpio_cfg(struct gpy211_device *phy, struct gpy211_gpio *gpio);

/**
	\brief API to get GPIO pin configuration.
	For debugging only, will be removed in future revisions.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param gpio Pointer to \ref gpy211_gpio. The user application should give
	port and pin of \ref gpy211_gpio to indicate the pin
	for which the configuration is to be collected.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gpio_get(struct gpy211_device *phy, struct gpy211_gpio *gpio);

/**
	\brief API to set output value on GPIO pin.
	For debugging only, will be removed in future revisions.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param gpio Pointer to \ref gpy211_gpio. The user application should give
	port and pin of \ref gpy211_gpio to indicate the pin for which
	the value is to be set.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gpio_output(struct gpy211_device *phy,
		       struct gpy211_gpio *gpio);

/**
	\brief API to get input value on GPIO pin.
	For debugging only, will be removed in future revisions.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param gpio Pointer to \ref gpy211_gpio. The user application should give
	port and pin of \ref gpy211_gpio to indicate the pin
	for which to get the configuration.

	\return
	- =1: high level
	- =0: low level
	- <0: error code
*/
int gpy2xx_gpio_input(struct gpy211_device *phy,
		      struct gpy211_gpio *gpio);

/**@}*/ /* GPY211_GPIO */

/** \addtogroup GPY211_LED */
/**@{*/
/**
	\brief Controls LED brightness level config.
	\details Use this API to configure LED's switch edge detection of rising vs
	falling edge, brightness mode and max brightness level.

	When mode is selected as \ref LED_BRLVL_MAX, the brightness is configured
	to a max level of 15 and the user input 'lvl_max' is ignored.

	When mode is selected as \ref LED_BRLVL_CONSTANT, the brightness is
	configured to a max level of given user input 'lvl_max' range of 0 - 15.
	Value 0 turns the LED off.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param brightness Pointer to LED brightness config (\ref gpy211_led_brlvl_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_led_br_cfg(struct gpy211_device *phy,
		      struct gpy211_led_brlvl_cfg *brightness);

/**
	\brief Gets LED brightness level config.
	\details Use this API to get LED's brightness config that was using \ref
	gpy2xx_led_br_cfg, like switch edge detection of rising vs falling edge,
	brightness mode and max brightness level.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param brightness Pointer to LED brightness config (\ref gpy211_led_brlvl_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_led_br_get(struct gpy211_device *phy,
		      struct gpy211_led_brlvl_cfg *brightness);

#if defined(EN_LED_TOP_CFG) && EN_LED_TOP_CFG
/**
	\brief Configure general LED function applicable to all LEDs.
	\details Use this generic LED configuration API to configure event based LED function
	to perform complex-scanning, complex-blinking, complex-inverse-scanning,
	fast and slow blinking frequency.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param cfg Pointer to LED general config \ref gpy211_led_gcfg.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_led_top_cfg(struct gpy211_device *phy,
		       struct gpy211_led_gcfg *cfg);

/**
	\brief Gets general LED function applicable to all LEDs.
	\details Use this API to get event based LED function configured using
	\ref gpy2xx_led_top_cfg which performs complex-scanning, complex-blinking,
	complex-inverse-scanning, fast and slow blinking frequency.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param cfg Pointer to LED general config \ref gpy211_led_gcfg.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_led_top_get(struct gpy211_device *phy,
		       struct gpy211_led_gcfg *cfg);
#endif

/**
	\brief Configures the given LED specific function.
	\details Use this API to assign an LED configuration to specific PHY
	activities of given link rates as details below.

	This API configures the behavior of the LED0 depending on pre-defined states
	or events the PHY has entered into or raised. Since more than one event or
	state can be active at the same time, more than one function might apply
	simultaneously. The priority from highest to lowest is given by the order
	pulseFlags, slowBlinkSrc, fastBlinkSrc, constantlyOn. LED pulseFlags for the
	selected activity is displayed only for the link speed selected in
	constantlyOn. If constantlyOn is selected as NONE then pulseFlags is not
	displayed on LED for any activity. To avoid constant ON when LED is
	configured for pulsing alone then set NO_CON bit in pulseFlags field.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param cfg Pointer to given LED config \ref gpy211_led_cfg.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_led_if_cfg(struct gpy211_device *phy,
		      struct gpy211_led_cfg *cfg);

/**
	\brief Gets the given LED specific function.
	\details Use this API to get the given LED configuration that was set for
	specific PHY activities and/or link rates using \ref gpy2xx_led_if_cfg.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param cfg Pointer to given LED config \ref gpy211_led_cfg.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_led_if_get(struct gpy211_device *phy,
		      struct gpy211_led_cfg *cfg);
/**@}*/ /* GPY211_LED */

/** \addtogroup GPY211_INT */
/**@{*/
#if defined(EN_SUPPORT_TOP_INT) && EN_SUPPORT_TOP_INT
/**
	\brief API to configure external interrupt.
	For debugging only, will be removed in future revisions.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param extin Pointer to TOP interrupt \ref gpy211_extin.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_topin_cfg(struct gpy211_device *phy,
		     struct gpy211_extin *extin);

/**
	\brief API to get external interrupt configuration.
	For debugging only, will be removed in future revisions.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param extin Pointer to TOP interrupt \ref gpy211_extin.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_topin_get(struct gpy211_device *phy,
		     struct gpy211_extin *extin);

/**
	\brief API to clear external interrupt event.
	For debugging only, will be removed in future revisions.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param extin Pointer to TOP interrupt (\ref gpy211_extin).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_topin_clr(struct gpy211_device *phy,
		     struct gpy211_extin *extin);
#endif /* EN_SUPPORT_TOP_INT */

/**
	\brief Enable/disable SoC external interrupt event source.
	\details Use this API to config various events to generate MDINT external
	interrupt to SoC, including PHY specific, PTP and MACSec events.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param extin Pointer to EXT interrupt event source (\ref gpy211_phy_extin).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_extin_mask(struct gpy211_device *phy,
		      struct gpy211_phy_extin *extin);

/**
	\brief Gets configured SoC external interrupt source.
	\details Use this API to get various events set by \ref gpy2xx_extin_mask to
	generate MDINT external interrupt to SoC, including PHY specific, PTP and MACSec events.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param extin Pointer to EXT interrupt event source \ref gpy211_phy_extin.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_extin_get(struct gpy211_device *phy,
		     struct gpy211_phy_extin *extin);

#if defined(EN_GMAC_DEBUG_ACCESS) && EN_GMAC_DEBUG_ACCESS
/**
	\brief Clear SoC external interrupt event source.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param extin Pointer to EXT interrupt (\ref gpy211_phy_extin).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_extin_clr(struct gpy211_device *phy,
		     struct gpy211_phy_extin *extin);

#endif
/**@}*/ /* GPY211_INT */

/** \addtogroup GPY211_DIAG */
/**@{*/
/**
	\brief Sets PHY test mode.
	\details Use this API to test modes of PHY, such as transmit waveform,
	transmit jitter in master or slave mode, transmitter distortion and AFE test.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param mode PHY test mode (\ref gpy211_test_mode)

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_test_mode_cfg(struct gpy211_device *phy,
			 enum gpy211_test_mode mode);

/**
	\brief Starts cable diagnostics test.
	\details Use this API to test cable diagnostics, such as cable open/short detection
	and cable length estimation.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_cdiag_start(struct gpy211_device *phy);

/**
	\brief Gets cable diagnostics test report.
	\details The user application needs to call this API once after it starts CDIAG using
	\ref gpy2xx_cdiag_start, to get cable diagnostics such as cable open/short detection
	and cable length estimation.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param report Pointer to cabe diagnostics report (\ref gpy211_cdiag_report).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_cdiag_read(struct gpy211_device *phy,
		      struct gpy211_cdiag_report *report);

/**
	\brief Stops cable diagnostics test.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_cdiag_stop(struct gpy211_device *phy);

/**
	\brief Starts analog built-in self-test (ABIST)
	\details The analog BIST is a feature that enables internal testing & qualification of
	the analog parts of the device, especially the line drivers (LD), analog gain controls (AGC)
	and ADC/DAC, without the need for expensive analog production testing equipment.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param param Pointer to ABIST paramters (\ref gpy211_abist_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_abist_start(struct gpy211_device *phy,
		       struct gpy211_abist_param *param);

/**
	\brief Gets analog built-in self-test (ABIST) report.
	\details The user application needs to call this API once after it starts ABIST using
	\ref gpy2xx_abist_start, in order to get the ABIST report on, for example, the line drivers(LD),
	analog gain controls (AGC) and ADC/DAC.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param report Pointer to ABIST report (\ref gpy211_abist_report).
	(\ref gpy211_abist_report).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_abist_read(struct gpy211_device *phy,
		      struct gpy211_abist_report *report);

/**
	\brief Configures various loopback test modes.
	\details Most loopback mode settings only take effect after a
		link down/up event has taken place.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param tloop PHY Loopback test mode (\ref gpy211_test_loop)

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_loopback_cfg(struct gpy211_device *phy,
			enum gpy211_test_loop tloop);

/**
	\brief Configure errors/events to be counted.
	\details The error/event is counted using an 8-bit counter. The counter
		is cleared every time \ref gpy2xx_errcnt_read is called. This counter
		saturates at the value 255 (0xFF).

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param event Error/event to be counted (\ref gpy211_errcnt_event).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_errcnt_cfg(struct gpy211_device *phy,
		      enum gpy211_errcnt_event event);

/**
	\brief Reads error/event counters.
	\details The source is configured with \ref gpy2xx_errcnt_cfg.
		The error/event is counted using a 8-bit counter. The counter
		is cleared every time this API is called. This counter
		saturates at the value 255 (0xFF).

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- 255: saturated
	- >=0: successful and value is counter
	- <0: error code
*/
int gpy2xx_errcnt_read(struct gpy211_device *phy);

/**
	\brief Gets PCS status.
	\details Read MMD registers 3.32, 3.33, 3.44, 3.45.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param status Point to get status (\ref gpy211_pcs_status).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_pcs_status_read(struct gpy211_device *phy,
			   struct gpy211_pcs_status *status);
/**@}*/ /* GPY211_DIAG */

/** \addtogroup GPY211_PTP */
/**@{*/
/**
	\brief Adjusts the frequency of the hardware clock.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ppb Relative frequency offset from nominal frequency in parts per
	billion.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_adjfreq(struct gpy211_device *phy, s32 ppb);

/**
	\brief Sets the shift time of the hardware clock.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param delta Desired change time in nanoseconds.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_adjtime(struct gpy211_device *phy, s64 delta);

/**
	\brief Sets the system time of the PHY.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ts Desired init time (\b timespec64).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_settime(struct gpy211_device *phy,       struct timespec64 *ts);

/**
	\brief Reads the current system time of the PHY.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ts Holds the current time (\b timespec64).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_gettime(struct gpy211_device *phy,       struct timespec64 *ts);

/**
	\brief Enables and configures the PTP (1588) function.
	\details Enables the PTP (1588) TS configuration and initializes it to default settings.
	It configures the user application given inputs, such as enable/disable Tx/Rx Timestamp capture
	at PHY level, Tx PTP offset of starting byte location of the PTP message, the type of transport
	protocol over which PTP messages are sent. It chooses One Step Timestamp (OST) vs Two Step Timestamp (TST),
	enables/disables OST correction and configures its OST correction time.

	For example, for PTP message sent over UDP/IPv4 via untagged Ethernet packet, the Tx PTP offset
	should be 42 decimal.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ptp_cfg PTP configurations (\ref gpy211_ptp_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_enable(struct gpy211_device *phy,
		      struct gpy211_ptp_ctrl *ptp_cfg);

/**
	\brief Disable PTP (1588) function.
	\details Disables the PTP (1588) TS configuration to default settings and removes
	all other configurations that were set using APIs \ref gpy2xx_ptp_enable,
	\ref gpy2xx_ptp_set_tsctrl, \ref gpy2xx_ptp_set_ppsctrl, or \ref gpy2xx_ptp_set_ptoctrl.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_disable(struct gpy211_device *phy);

/**
	\brief Gets the PTP (1588) TS configuration.
	\details Gets the PTP (1588) TS configuration that was set using APIs \ref gpy2xx_ptp_enable,
	\ref gpy2xx_ptp_set_tsctrl, \ref gpy2xx_ptp_set_ppsctrl, and \ref gpy2xx_ptp_set_ptoctrl.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ptp_cfg PTP configurations (\ref gpy211_ptp_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_getcfg(struct gpy211_device *phy,
		      struct gpy211_ptp_cfg *ptp_cfg);

/**
	\brief Gets timestamp FIFO status.
	\details The FIFO status gives the Rx/Tx FIFO's fill level, overflow and undeflow indication.
	To facilitate the SoC device's retrieval of the captured timestamps, a FIFO of depth 16 entries is
	provided to store the captured timestamp per Rx/Tx direction. Each entry is of width 96 bits:
		- 64 bits of packet timestamp
		- 32 bits of CRC as packet identifier

	The user application must read this API to check the Rx FIFO fill level is not empty before doing a
	read access, otherwise an underflow error flag will be set.

	The hardware pushes values into the FIFO and a software read access to a fixed location pops the oldest content.
	If the FIFO is full and a push is triggered, the data will be dropped and the FIFO content not overwritten,
	an overflow error flag will be set.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param status Holds timestamp FIFO status (\ref gpy211_ts_fifo_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_fifostat(struct gpy211_device *phy,
			struct gpy211_ts_fifo_stat *status);

/**
	\brief Resets the FIFO status.
	\details The user application can use this API to clear the FIFO status \ref gpy211_ts_fifo_stat,
	which shows the Rx/Tx FIFO's fill level, overflow and undeflow indication.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_resetfifo(struct gpy211_device *phy);

#if defined(EN_GMAC_DEBUG_ACCESS) && EN_GMAC_DEBUG_ACCESS
/**
	\brief Gets transmit timestamp details and status.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ts_status Holds timestamp FIFO status (\ref gpy211_ts_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_txtsstat(struct gpy211_device *phy,
			struct gpy211_ts_stat *ts_status);
#endif

/**
	\brief Configures IEEE 1588 Timestamp (TS) control settings.
	\details Use this API to configure TS control to TS functions, such as enable/disable
	TS snapshot for all packets, event messages, messages relevant to master, selected PTP packets,
	program sub-second/sub-nanosecond increment resolution values to the system TS and TS correction
	and default Addend (drift in frequency) value.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ts_cfg PTP configurations (\ref gpy2xx_ts_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_set_tsctrl(struct gpy211_device *phy,
			  struct gpy2xx_ts_ctrl *ts_cfg);

/**
	\brief Configures IEEE 1588 Pulse Per Second (PPS) function settings.
	\details The flexible PPS output option provides features such as programming the start or stop
	time in terms of system time, width between the rising edge and corresponding falling edge,
	the interval between the rising edges of the PPS signal. The width and interval are configured in
	terms of number of units of sub-second increment value.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param pps_ctrl Pointer to PPS config (\ref gpy2xx_pps_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_set_ppsctrl(struct gpy211_device *phy,
			   struct gpy2xx_pps_ctrl *pps_ctrl);
/**
	\brief Configures IEEE 1588 PTP Timestamp Offload function settings.
	\details PTP Timestamp Offload Function is an optional feature that can parse the
	incoming PTP packets on the receiver, and enables the automatic generation of required
	PTP packets periodically or when triggered by the host software.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param pto_ctrl PTO configurations (\ref gpy2xx_pto_ctrl)..

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_set_ptoctrl(struct gpy211_device *phy,
			   struct gpy2xx_pto_ctrl *pto_ctrl);

/**
	\brief Gets Rx packet timestamp snapshot from FIFO.
	\details Gets one entry of the captured IEEE1588 timestamp (TS) of the received packet from FIFO.
	The CRC is used as an identifier for the packet so that the host can correlate the packet with the timestamp.
	The FIFO is capable of storing 16 entries per Tx, Rx direction. The user application must read
	\ref gpy2xx_ptp_fifostat to check that the Rx FIFO fill level is not empty before doing a read access,
	otherwise an underflow error flag will be set.

	Hardware pushes values into the FIFO and a software read access to a fixed location pops the oldest content.
	If the FIFO is full and a push is triggered, the data will be dropped and the FIFO content not overwritten,
	an overflow error flag will be set.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param rx_ts Holds timestamp and CRC (\ref gpy211_rx_ts)..

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_getrxts(struct gpy211_device *phy,
		       struct gpy211_rx_ts *rx_ts);

/**
	\brief Gets Tx packet timestamp snapshot from FIFO.
	\details Gets one entry of the captured IEEE1588 timestamp (TS) of the transmitted packet from FIFO.
	The CRC is used as an identifier for the packet so that the host can correlate the packet with the timestamp.
	The FIFO is capable of storing 16 entries per Tx, Rx direction. The user application must read
	\ref gpy2xx_ptp_fifostat to check that the Tx FIFO fill level is not empty before doing a read access,
	otherwise an underflow error flag will be set.

	Hardware pushes values into the FIFO and a software read access to a fixed location pops the oldest content.
	If the FIFO is full and a push is triggered, the data will be dropped and the FIFO content not overwritten,
	an overflow error flag will be set.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param tx_ts Holds timestamp status and CRC (\ref gpy211_tx_ts).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_gettxts(struct gpy211_device *phy,
		       struct gpy211_tx_ts *tx_ts);

/**
	\brief Configure auxiliary timestamp function.
	\details Configures Auxiiliary timestamp feature Enable/Discable, and the snapshot trigger source/event.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param aux_cfg passes the configuration (\ref gpy211_aux_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_aux_cfg(struct gpy211_device *phy, struct gpy211_aux_cfg *aux_cfg);

/**
	\brief Gets auxiliary timestamp snapshot from FIFO.
	\details Gets one entry of the captured IEEE1588 timestamp (TS) based on an external event from FIFO.
	The timestamp status register will indicate auxiliary event.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ts Holds timestamp.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_getauxts(struct gpy211_device *phy, struct timespec64 *ts);

/**
	\brief Gets filling level and overflow states.
	\details Gets filling level and overflow status of auxiliary timestamp FIFO.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param fifo_status Holds states (\ref gpy211_aux_fifo_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_auxfifostat(struct gpy211_device *phy, struct gpy211_aux_fifo_stat *fifo_status);

/**
	\brief Reset timestamp FIFO.
	\details clear timestamp FIFO.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ptp_resetauxfifo(struct gpy211_device *phy);

/**@}*/ /* GPY211_PTP */

/** \addtogroup GPY211_SYNCE */
/**@{*/
/**
	\brief Configures SyncE function.
	\details Synchronous Ethernet interface to support transportation of a source-referable
	clock from the server to the end-points. Essentially, it consist of a reference clock input
	and a reference clock output. The GPY2xx works as a reference clock master by accepting an input
	reference clock and transporting this clock frequency via the signalling on the twisted pair interface.
	As a reference clock slave, the GPY2xx will recover the clock and derive an output reference clock.
	The GPY2xx provides a means of detecting the loss of reference clock input.
	For the SoC integrators: there are two possible connections for this interface:
	- If the SoC is capable of generating the reference clocks to be transported, then an internal connection
	is all that is required.
	- If the SoC is intended to also accept or provide reference clocks, then pad connectivity to
	REFCLKO/REFCLKI should be provided.

	Note:The GPY2xx provides both REFCLKO and REFCLKI to meet both reference clock master and reference clock slave requirements.
	SoC integrators may choose, depending on their system needs, to provide either one or both at the chip-level pinning.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param cfg SyncE configuration (\ref gpy211_synce).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_synce_cfg(struct gpy211_device *phy, struct gpy211_synce *cfg);

/**
	\brief Gets SyncE configuration.
	\details Gets SyncE configuration that was configured using \ref gpy2xx_synce_cfg.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param cfg Holds SyncE configuration (\ref gpy211_synce).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_synce_get(struct gpy211_device *phy, struct gpy211_synce *cfg);
/**@}*/ /* GPY211_SYNCE */

/** \addtogroup GPY211_SGMII */
/**@{*/
/**
	\brief Restarts SGMII interface auto-negotiation.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_sgmii_restart_aneg(struct gpy211_device *phy);

/**
	\brief Restarts auto-negotiation or sets link speed & duplex forcefully dependending
	on given autoneg of \ref gpy211_link.
	\details Configures the SGMII link configuration direction, auto-negotiation mode,
	EEE capability. Enables & restarts SGMII auto-negotiation to advertise the configuration,
	or sets the SGMII link speed forcefully dependending on the given autoneg of \ref gpy211_link.
	If autoneg is 1, this API sets the SGMII ANEG mode and restarts auto-negotiation.
	If autoneg is 0, this API sets the link speed/duplex and EEE capability forcefully. In this case,
	the auto-negotiation is disabled and it is the responsibility of the user application to take care of setting
	the same speed and EEE capability for the link partner so that the link is UP and running, otherwise the link will be DOWN.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param sgmii Pointer to SGMII configuration (\ref gpy211_sgmii).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_sgmii_config_aneg(struct gpy211_device *phy,
			     struct gpy211_sgmii *sgmii);

/**
	\brief Gets the SGMII restarted auto-negotiation status.
	\details The user application must call and check if auto-negotiation has completed
	before reading the SGMII link status \ref gpy2xx_sgmii_read_status after
	auto-negotiation was restarted using \ref gpy2xx_sgmii_restart_aneg.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =1: auto-negotiation is done
	- =0: auto-negotiation is in progress or not started
	- <0: error code
*/
int gpy2xx_sgmii_aneg_done(struct gpy211_device *phy);

/**
	\brief Reads and updates the SGMII link parameters and status.
	\details The user application can call this API to read and update SGMII link parameters,
	such as link configuration direction, auto-negotiation mode and capability, EEE capability
	link speed and duplex mode, and link state of this node.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param sgmii Pointer to SGMII configuration (\ref gpy211_sgmii).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_sgmii_read_status(struct gpy211_device *phy,
			     struct gpy211_sgmii *sgmii);

/**
	\brief API to configure SGMII operation mode.
	\details The user application can call this API to set SGMII operation mode (Normal, Loopback,
	and Power-Down) or to reset the SGMII interface.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param mode \ref gpy211_sgmii_operation

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_sgmii_opmode(struct gpy211_device *phy,
			enum gpy211_sgmii_operation mode);
/**@}*/ /* GPY211_SGMII */

/** \addtogroup GPY211_MISC */
/**@{*/
/**
	\brief Configures Wake-on-LAN function.
	\details Wake-on-LAN (WoL) is a feature that is capable of monitoring and
	detecting WoL packets. The PHY issues a wake-up indication, via the external interrupt
	sourced by the GPY2xx to the SoC, by activating the MDINT signal to wake a larger SoC from
	its power-down state. The most commonly used WoL packet is a magic packet that contains
	the MAC address of the device that is to be woken up. The wolopts of \ref gpy211_wolinfo
	will be updated to the options that have been successfully configured into the hardware
	after API called.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param wol Pointer to Wake-On-Lan configuration (\ref gpy211_wolinfo).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_wol_cfg(struct gpy211_device *phy, struct gpy211_wolinfo *wol);

/**
	\brief Gets the Wake-on-LAN configuration.
	\details Gets the WoL configuration that was configured using \ref gpy2xx_wol_cfg,
	which contains the WoL flags, magic packet MAC address and SecureON password if enabled.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param wol Pointer to Wake-on-LAN configuration (\ref gpy211_wolinfo).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_wol_get(struct gpy211_device *phy, struct gpy211_wolinfo *wol);

/**
	\brief Configures auto-downspeed (ADS) function.
	\details The ADS feature ensures maximum interoperability in specific situations, such as, information
	available about the cabling during ANEG is insufficient, the integrity of received signals
	is not suitable for link-up due to increased alien noise, or over-length cables.
	The ADS feature avoids continuous link-up failures in such situations, and the next link-up will be
	done at the next advertised speed below 1000 Mbit/s.

	If the link only supports speeds of 1000 Mbit/s or 2500 Mbit/s, the ADS feature is automatically disabled.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ads Holds auto-downspeed configuration (\ref gpy211_ads_sta).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ads_cfg(struct gpy211_device *phy, struct gpy211_ads_ctrl *ads);

/**
	\brief Gets auto-downspeed (ADS) function configuration.
	\details Gets the ADS configuration that was set using \ref gpy2xx_ads_cfg,
	also gets ADS status such as training attempts to select the operating speed,
	downshift events from 2.5 G or 1G to lower speeds.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ads Holds auto-downspeed configuration (\ref gpy211_ads_sta).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ads_get(struct gpy211_device *phy, struct gpy211_ads_sta *ads);

/**
	\brief Gets auto-downspeed (ADS) detected status.
	\details Gets whether the ADS has happened at all due to harsh or inadequate cable
	infrastructure environments. The number of times the GPY2xx decided to downspeed the link
	is counted and available as statistics via the \ref gpy2xx_errcnt_cfg for event = 9.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- >0: successful and auto-downspeed is detected
	- =0: successful but no auto-downspeed is detected
	- <0: error code
*/
int gpy2xx_ads_detected(struct gpy211_device *phy);

/**
	\brief Configures Ultra Low Power configuration.
	\details This enables or disables Ultra Low Power mode and whether the GPY to enter
	ULP only after STA aknowledging the ULP interrupt status by reading PHY_ISTAT or unconditionally
	without acknowledgement from STA.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ulp Holds ULP configuration (\ref gpy211_ulp_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ulp_cfg(struct gpy211_device *phy, struct gpy211_ulp_ctrl *ulp);

/**
	\brief Gets Ultra Low Power configuration.
	\details This gets the Ultra Low Power configuration that was set by API \ref gpy2xx_ulp_cfg.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param ulp Holds ULP configuration (\ref gpy211_ulp_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_ulp_get(struct gpy211_device *phy, struct gpy211_ulp_ctrl *ulp);

/**
	\brief Gets the GPY2xx's sensor temperature in degrees Celsius.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\param pvt Pointer to on-chip sensor temperature (\ref gpy211_pvt).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_pvt_get(struct gpy211_device *phy, struct gpy211_pvt *pvt);
/**@}*/ /* GPY211_MISC */

/** \addtogroup GPY211_FW */
/**@{*/
/**
	\brief API to start the FW downloading procedure.
	\details This function notifies the PHY to start the firmware download.
	The PHY will drop (terminate) the BASE-T link and erase the Flash.
	Erasing a 128kbyte flash takes typically 1s.
	The function behaves differently depending on the value of the timeout parameter.
	When the timeout parameter is larger than zero, the function will poll the PHY
	regularly every 500us, if the Flash erasure has been completed.
	The function will return, when the Flash is erased or, with an error code,
	when the timeout expired. A typical timeout is 5s.
	When the timeout is zero, the function will return immediately and not
	poll the PHY for completion of the Flash erasure operation. In this case,
	the user application has to regularly check the completion of the Flash
	erasure operation by calling gpy2xx_fw_fwr_status.
	Note: Once this API has been called, only \ref gpy2xx_fw_fwr_page, \ref gpy2xx_fw_frw_uninit and
	\ref gpy2xx_fw_fwr_status can be called afterwards. Other commands are blocked.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param timeout Timeout in milliseconds. If it's zero, API is non-blocking
	and return immediately. Please use \ref gpy2xx_fw_fwr_status to poll the
	status. If it's non-zero, API is blocking until either the operation
	completes successfully (and return 0) or error condition reached
	such as timeout (and return error code). A default value is defined as
	\ref FW_FWR_DEF_TIMEOUT (5000 milliseconds).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_fw_frw_init(struct gpy211_device *phy, u32 timeout);

/**
	\brief API to download the firmware into the device via page-wise access to flash memory.
	\details The API \ref gpy2xx_fw_frw_init needs to be called before this API.
	The buffer size is fixed to 256 bytes, corresponding to a typical page of SPI flash memory.
	Please confirm the page	size of flash memory before using the field firmware upgrading APIs.
	Please be aware that the firmware upgrading will not be successful if the flash memory has a
	page size other than 256 bytes. The host software needs to split the firmware binary
	into chunks of 256 bytes and to call this API in sequence. If the last page is less than
	256 bytes, please fill with zeros to pad to 256 bytes in the buffer. It typically takes
	10 ms to download one page of the firmware code into the flash memory. A timeout parameter is used to
	either block operation if the timeout is non-zero, or for host polling if
	the timeout is zero.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param buf Pointer to firmware data in 256-byte chunks.
	\param timeout Timeout in milliseconds. If it is zero, the API is non-blocking
	and returns immediately. Please use \ref gpy2xx_fw_fwr_status to poll the
	status. If it is non-zero, the API is blocking until either the operation
	completes successfully (and returns 0) or an error condition is reached,
	such as timeout (and returns error code). A default value is defined as
	\ref FW_FWR_DEF_TIMEOUT (5000 milliseconds).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_fw_fwr_page(struct gpy211_device *phy, u8 buf[256], u32 timeout);

/**
	\brief Polls completion status of flash init and write page operations during firmware Upgrade.
	\details This API is used by the host software to poll the completion status of
	\ref gpy2xx_fw_frw_init and \ref gpy2xx_fw_fwr_page, if they were used
	with zero timeout (non-blocking mode). The user application must poll with these delays in place
	if the timeout is configured to be zero (non-blocking mode).

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- >0: operation completes successfully
	- =0: operation does not complete
	- <0: error code
*/
int gpy2xx_fw_fwr_status(struct gpy211_device *phy);

/**
	\brief API to finalize firmware download procedure.
	\details This API must be called after all \ref gpy2xx_fw_fwr_page operations
	have finished. It triggers a reset of the GPY2xx device.
	Afterwards, \ref gpy2xx_uninit should be called to close this device entity.
	If the host software does not execute a complete system reboot, it needs to
	wait until the GPY2xx device restarts successfully, which is indicated by an interrupt
	(typically this takes less than 2 seconds) and call \ref gpy2xx_init to initialize
	the device entity and synchronize the status before using other APIs.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_fw_frw_uninit(struct gpy211_device *phy);
/**@}*/ /* GPY211_FW */

/** @cond INTERNAL */
/** \addtogroup GPY211_MDIO */
/**@{*/

/**
	\brief Debug API to read 16-bit wide data from Smart-AZ subsystem registers
	such as Buffer Manager, LED Control and Temperature Sensor.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param regaddr Register (AHB bus) address.
	\param data Pointer to store read data.

	\return
	- =0: successful
	- <0: error code
*/

int gpy2xx_mbox_read16(struct gpy211_device *phy, u32 regaddr, u32 *data);

/**
	\brief Debug API to write 16-bit wide data into Smart-AZ subsystem registers
	such as Buffer Manager, LED Control and Temperature Sensor.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param regaddr Register (AHB bus) address.
	\param data Data to be written to given 'regaddr' address.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_mbox_write16(struct gpy211_device *phy, u32 regaddr, u32 data);

/**
	\brief Debug API to read 32-bit wide data from Smart-AZ subsystem registers
	of MACSec module.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param regaddr Register (AHB bus) address.
	\param data Pointer to store read data.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_mbox_read32(struct gpy211_device *phy, u32 regaddr, u32 *data);

/**
	\brief Debug API to write 32-bit wide data into Smart-AZ subsystem registers
	of MACSec module.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param regaddr Register (AHB bus) address.
	\param data Data to be written to given 'regaddr' address.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_mbox_write32(struct gpy211_device *phy, u32 regaddr, u32 data);
/**@}*/ /* GPY211_MDIO */
/** @endcond */

/** \addtogroup GPY211_PM */
/**@{*/
/**
	\brief Controls the settings to enable MACsec module.
	\details This API sets the basic configuration required to enable MACsec
	like setting option if to discard packet for CRC/Pkt/SecFail/Classification
	failues raised by MACsec.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param msec_cfg Pointer to PM config (\ref gpy211_macsec).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_macsec_enable(struct gpy211_device *phy,
			 const struct gpy211_macsec *msec_cfg);

/**
	\brief Controls the settings to disable MACsec module.
	\details This API reverts the basic configuration that was set using \ref
	gpy2xx_macsec_enable to disable MACsec and other unser input options of to
	discard packet for CRC/Pkt/SecFail/Classification failues raised by MACsec.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_macsec_disable(struct gpy211_device *phy);

/** @cond INTERNAL */
/**
	\brief Controls the settings of the PM module.
	\details This API controls the packet's CRC, Padding and Endianness control
	towards TPI side.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param gmac_ctrl Pointer to PM config (\ref pm_gmac_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacf_pm_cfg(struct gpy211_device *phy,
			const struct pm_gmac_cfg *gmac_ctrl);

/**
	\brief Gets the control settings of the PM module.
	\details This API gets the packet's CRC, Padding and Endianness control
	settings set by \ref gpy2xx_gmacf_pm_cfg.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param gmac_ctrl Pointer to PM config (\ref pm_gmac_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacf_pm_get(struct gpy211_device *phy,
			struct pm_gmac_cfg *gmac_ctrl);

/**
	\brief Controls the settings of the PM module.
	\details This API controls the packet's CRC, Padding and Endianness control
	towards System side.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param gmac_ctrl Pointer to PM config (\ref pm_gmac_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacl_pm_cfg(struct gpy211_device *phy,
			const struct pm_gmac_cfg *gmac_ctrl);

/**
	\brief Gets the control settings of the PM module.
	\details This API gets the packet's CRC, Padding and Endianness control
	settings set by \ref gpy2xx_gmacl_pm_cfg.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param gmac_ctrl Pointer to PM config (\ref pm_gmac_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacl_pm_get(struct gpy211_device *phy,
			struct pm_gmac_cfg *gmac_ctrl);

/**
	\brief Controls the settings of the Smart-AZ bypass and MACSec error handling.
	\details This API controls to bypass or allow packet to go through Smart-AZ and
	control settings for MACSec error handling.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param pm_cfg Pointer to PM config (\ref pm_config).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacx_pm_pdi_cfg(struct gpy211_device *phy,
			    const struct pm_config *pm_cfg);

/**
	\brief Gets the settings of the Smart-AZ bypass and MACSec error handling.
	\details This API gets the control settings that was set by \ref gpy2xx_gmacx_pm_pdi_cfg.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param pm_cfg Pointer to PM config (\ref pm_config).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacx_pm_pdi_get(struct gpy211_device *phy,
			    struct pm_config *pm_cfg);

/**
	\brief Controls the BM's Packet Size related config.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param pcfg Pointer to Packet Size related config (\ref gmac_pkt_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacf_pkt_cfg(struct gpy211_device *phy,
			 const struct gmac_pkt_cfg *pcfg);

/**
	\brief Gets the BM Packet Size related config.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param pcfg Pointer to Packet Size related config (\ref gmac_pkt_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacf_pkt_get(struct gpy211_device *phy,
			 struct gmac_pkt_cfg *pcfg);
/** \endcond */

/**
	\brief This API gets the BM counters.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param counters Pointer to BM counters (\ref gmacf_counters).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacf_count_get(struct gpy211_device *phy,
			   struct gmacf_counters *counters);
/**
	\brief This API controls the BM counter control configuration.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_ctrl Pointer to BM counter control config
			(\ref gmacf_counter_ctrl).

	\return
	- =0: successful
	- <0: error code
*/

int gpy2xx_gmacf_count_ctrl_cfg(struct gpy211_device *phy,
				const struct gmacf_counter_ctrl *cnt_ctrl);

/**
	\brief This API gets the BM counter control config.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_ctrl Pointer to BM Counter Control config
			(\ref gmacf_counter_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacf_count_ctrl_get(struct gpy211_device *phy,
				struct gmacf_counter_ctrl *cnt_ctrl);
/**@}*/ /* GPY211_PM */

/** \addtogroup GPY211_BM */
/**@{*/
/** \cond INTERNAL */
/**
	\brief This API controls the shared buffer configuration.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param bm_cfg Pointer to SB config (\ref bm_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacx_bm_cfg(struct gpy211_device *phy,
			const struct bm_cfg *bm_cfg);

/**
	\brief This API gets the shared buffer configuration.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param bm_cfg Pointer to SB config (\ref bm_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacx_bm_get(struct gpy211_device *phy, struct bm_cfg *bm_cfg);

/**
	\brief This API gets the shared buffer status.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param bm_stat Pointer to SB status (\ref pm_bm_status).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacx_bm_status_get(struct gpy211_device *phy,
			       struct pm_bm_status *bm_stat);
/** \endcond */

/**
	\brief This API controls the flow control (PAUSE) configuration.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cc_cfg Pointer to PAUSE (congestion control) config (\ref pause_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacl_pause_cfg(struct gpy211_device *phy,
			   const struct pause_cfg *cc_cfg);

/**
	\brief This API gets the flow control (PAUSE) configuration.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cc_cfg Pointer to PAUSE config (\ref pause_cfg).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_gmacl_pause_get(struct gpy211_device *phy,
			   struct pause_cfg *cc_cfg);

/**
	\brief This API to tune the frequency of MACs within GPY in USXGMII Mode.
	\details During the stress test of 100% bi-directional traffic for longer
	duration, recommendation is to run the MACs at slightly higher frequency to
	avoid packet drops in USXGMII Mode. Recommended to call API for correct
	programming sequence. In non-USXGMII mode this bit as no effect.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param freq Pointer to fequency tuning config (\ref tune_freq).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_pm_freq_tune(struct gpy211_device *phy,
			struct tune_freq *freq);
/**@}*/ /* GPY211_BM */

/** \addtogroup GPY211_GPY24X_USXGMII */
/**@{*/
/**
	\brief  This API configures the RX/TX settings in the USXGMII module only for GPY24X.

	 \details The Universal Serial 10GE Media Independent Interface (USXGMII) IP core implements an
	 Ethernet Media Access Controller (MAC) with a mechanism to carry a single port of 10M, 100M,
	 1G, 2.5G, 5G or 10GE over an IEEE 802.3 Clause 49 BASE-R physical coding sublayer/physical
	 layer (PCS/PHY).

	 GPY24X provides 2 options for the serdes data interface
	 - a USXGMII single lane interface at 10.3125 GHz bit-clock to connect to a MAC processor with a
	    single Rx / Tx lane
	 - a quad-lane SGMII* interface at up to 3.125 GHz bit-clock or 1.25 GHz bit-clock to connect
	    to legacy switches only supporting SGMII* and not USXGMII.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param reach_cfg Pointer to USXMGII_REACH config (\ref gpy211_usxgmii_reach).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_reach_cfg(struct gpy211_device *phy,
			     const struct gpy211_usxgmii_reach *reach_cfg);

/**
	\brief Get the settings of the USXGMII module.
	\details This API gets the USXGMII REACH settings set by \ref gpy2xx_usxgmii_reach_cfg.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param reach_cfg Pointer to USXMGII_REACH config (\ref gpy211_usxgmii_reach).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_reach_get(struct gpy211_device *phy,
			     struct gpy211_usxgmii_reach *reach_cfg);

/**
	\brief Get the USXMGII PCS/PMA link status.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param psts Pointer to PCS/PMS link status (\ref gpy211_usxgmii_pcs_pma_linksts).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_pcs_pma_linksts(struct gpy211_device *phy,
				   struct gpy211_usxgmii_pcs_pma_linksts *psts);

/**
	\brief Get the USXMGII MII link status for each lane/slice.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param psts Pointer to MII link status (\ref gpy211_usxgmii_mii_linksts).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_mii_linksts(struct gpy211_device *phy,
			       struct gpy211_usxgmii_mii_linksts *psts);

/**
	\brief Get the USXMGII auto-negotiation status.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param psts Pointer to auto negotiation resolution status (\ref gpy211_usxgmii_aneg_status).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_aneg_sts(struct gpy211_device *phy,
			    struct gpy211_usxgmii_aneg_status *psts);

/**
	\brief Restarts USXGMII auto negotiation.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_aneg_rst(struct gpy211_device *phy);

/**
	\brief Vendor-Specific Soft Reset.
	\details When triggered VR reset, the CSR block triggers the software reset
	process in which all internal blocks are reset, except the Management Interface
	block and CSR block. When this VR resets, it also resets the PHY.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_vr_reset(struct gpy211_device *phy);

/**
	\brief Get the VR reset status once issued (\ref gpy2xx_usxgmii_vr_reset).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param psuccess Pointer to VR reset status.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_vr_reset_sts(struct gpy211_device *phy, int *psuccess);

/**
	\brief Set the Alignment Marker interval.
	\details This field controls the Alignment Marker interval when operating in
	multi-port USXGMII Mode. In the transmit data-stream, Alignment Markers are
	inserted periodically at the interval (in terms of 66-bit blocks) defined by
	this field. Similarly, DWC_xpcs checks for Alignment Markers in the receive
	data-stream,at this interval. This field corresponds to the upper 16 bits of
	the alignment count interval. The LSB 4 bits of the alignment count interval
	is always 0. The default value of this field corresponds to the 16'd1025.
	The standard specified AM interval value is 16400. Since this field
	corresponds to the upper 16 bits, the default value of this field is
	16400/16 which is 1025. However, application can modify this value based on
	its choice.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param am Alignment Marker interval.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_alignmentmarker_set(struct gpy211_device *phy, u32 am);

/**
	\brief Get the Alignment Marker interval set using (\ref gpy2xx_usxgmii_alignmentmarker_set).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param pam Pointer to Alignment Marker interval.

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_alignmentmarker_get(struct gpy211_device *phy, u32 *pam);

/**
	\brief Set the Tx Bit Error Rate mode.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cfg Pointer to BERT config (\ref gpy211_usxgmii_tx_bert_config).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_tx_bert_cfg(struct gpy211_device *phy,
			       const struct gpy211_usxgmii_tx_bert_config *cfg);

/**
	\brief Get the Tx Bit Error Rate mode set using (\ref gpy2xx_usxgmii_tx_bert_cfg).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cfg Pointer to BERT config (\ref gpy211_usxgmii_tx_bert_config).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_tx_bert_get(struct gpy211_device *phy,
			       struct gpy211_usxgmii_tx_bert_config *cfg);

/**
	\brief Set the Rx Bit Error Rate mode.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cfg Pointer to BERT config (\ref gpy211_usxgmii_rx_bert_config).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_rx_bert_cfg(struct gpy211_device *phy,
			       const struct gpy211_usxgmii_rx_bert_config *cfg);

/**
	\brief Get the Rx Bit Error Rate mode set using (\ref gpy2xx_usxgmii_rx_bert_cfg).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cfg Pointer to BERT config (\ref gpy211_usxgmii_rx_bert_config).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_rx_bert_get(struct gpy211_device *phy,
			       struct gpy211_usxgmii_rx_bert_config *cfg);

/**
	\brief Get the Bit Error Rate stats.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param stat Pointer to BERT stats (\ref gpy211_usxgmii_rx_bert_statistics).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_rx_bert_stat(struct gpy211_device *phy,
				struct gpy211_usxgmii_rx_bert_statistics *stat);

/**
	\brief Set the USXGMII loopback mode.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param mode Pointer to USXMGII loopback mode (\ref gpy211_usxgmii_loopback_mode).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_loopback_cfg(struct gpy211_device *phy,
				enum gpy211_usxgmii_loopback_mode mode);

/**
	\brief Get the USXGMII loopback mode.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param pmode Pointer to USXMGII loopback mode (\ref gpy211_usxgmii_loopback_mode).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_usxgmii_loopback_get(struct gpy211_device *phy,
				enum gpy211_usxgmii_loopback_mode *pmode);

/**@}*/ /* GPY211_GPY24X_USXGMII */
#endif /* _GPY211_H_ */
