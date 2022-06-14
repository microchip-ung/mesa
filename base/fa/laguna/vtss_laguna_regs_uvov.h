// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_UVOV_H_
#define _VTSS_LAGUNA_REGS_UVOV_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a UVOV
 *
 * UnderVoltatageOverVoltage
 *
 ***********************************************************************/

/**
 * Register Group: \a UVOV:UVOV_REGS
 *
 * UVOV MODULE
 */


/**
 * \brief Under and Over Voltage Control Register
 *
 * \details
 * Under and Over Voltage Control Register
 * Note: This register has no meaning for the UVOV instance that monitors
 * the core domain.
 *
 * Register: \a UVOV:UVOV_REGS:UVOV_CTL
 */
#define VTSS_UVOV_UVOV_CTL                   VTSS_IOREG(VTSS_TO_UVOV,0x0)

/**
 * \brief
 * Master over voltage enable.This bit enables over voltage detection. This
 * bit should be set only after allover voltage registers have been
 * configured.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CTL . MST_OVR_DET_EN
 */
#define  VTSS_F_UVOV_UVOV_CTL_MST_OVR_DET_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_UVOV_UVOV_CTL_MST_OVR_DET_EN  VTSS_BIT(1)
#define  VTSS_X_UVOV_UVOV_CTL_MST_OVR_DET_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Master under voltage enable.This bit enables under voltage detection.
 * This bit should be set only after allunder voltage registers have been
 * configured.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CTL . MST_UVR_DET_EN
 */
#define  VTSS_F_UVOV_UVOV_CTL_MST_UVR_DET_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_CTL_MST_UVR_DET_EN  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_CTL_MST_UVR_DET_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Under and Over Voltage Interrupt Status Register
 *
 * \details
 * Under and Over Voltage Interrupt Status Register
 *
 * Register: \a UVOV:UVOV_REGS:UVOV_INT_STS
 */
#define VTSS_UVOV_UVOV_INT_STS               VTSS_IOREG(VTSS_TO_UVOV,0x1)

/**
 * \brief
 * TRIM_INT_STS
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_STS . TRIM_INT_STS
 */
#define  VTSS_F_UVOV_UVOV_INT_STS_TRIM_INT_STS(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_UVOV_UVOV_INT_STS_TRIM_INT_STS  VTSS_BIT(24)
#define  VTSS_X_UVOV_UVOV_INT_STS_TRIM_INT_STS(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * OVR_INT_STS_V09
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_STS . OVR_INT_STS_V09
 */
#define  VTSS_F_UVOV_UVOV_INT_STS_OVR_INT_STS_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_UVOV_UVOV_INT_STS_OVR_INT_STS_V09  VTSS_BIT(20)
#define  VTSS_X_UVOV_UVOV_INT_STS_OVR_INT_STS_V09(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * UVR_INT_STS_V09
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_STS . UVR_INT_STS_V09
 */
#define  VTSS_F_UVOV_UVOV_INT_STS_UVR_INT_STS_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_UVOV_UVOV_INT_STS_UVR_INT_STS_V09  VTSS_BIT(16)
#define  VTSS_X_UVOV_UVOV_INT_STS_UVR_INT_STS_V09(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * OVR_INT_STS_V12
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_STS . OVR_INT_STS_V12
 */
#define  VTSS_F_UVOV_UVOV_INT_STS_OVR_INT_STS_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_UVOV_UVOV_INT_STS_OVR_INT_STS_V12  VTSS_BIT(12)
#define  VTSS_X_UVOV_UVOV_INT_STS_OVR_INT_STS_V12(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * UVR_INT_STS_V12
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_STS . UVR_INT_STS_V12
 */
#define  VTSS_F_UVOV_UVOV_INT_STS_UVR_INT_STS_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_UVOV_UVOV_INT_STS_UVR_INT_STS_V12  VTSS_BIT(8)
#define  VTSS_X_UVOV_UVOV_INT_STS_UVR_INT_STS_V12(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * OVR_INT_STS_V18
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_STS . OVR_INT_STS_V18
 */
#define  VTSS_F_UVOV_UVOV_INT_STS_OVR_INT_STS_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_UVOV_UVOV_INT_STS_OVR_INT_STS_V18  VTSS_BIT(4)
#define  VTSS_X_UVOV_UVOV_INT_STS_OVR_INT_STS_V18(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * UVR_INT_STS_V18
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_STS . UVR_INT_STS_V18
 */
#define  VTSS_F_UVOV_UVOV_INT_STS_UVR_INT_STS_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_INT_STS_UVR_INT_STS_V18  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_INT_STS_UVR_INT_STS_V18(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Under and Over Voltage Interrupt Enable Register
 *
 * \details
 * Under and Over Voltage Interrupt Enable Register
 *
 * Register: \a UVOV:UVOV_REGS:UVOV_INT_EN
 */
#define VTSS_UVOV_UVOV_INT_EN                VTSS_IOREG(VTSS_TO_UVOV,0x2)

/**
 * \brief
 * TRIM_INT_ENWhen set the respective interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_EN . TRIM_INT_EN
 */
#define  VTSS_F_UVOV_UVOV_INT_EN_TRIM_INT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_UVOV_UVOV_INT_EN_TRIM_INT_EN  VTSS_BIT(24)
#define  VTSS_X_UVOV_UVOV_INT_EN_TRIM_INT_EN(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * OVR_INT_ENWhen set the respective interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_EN . OVR_INT_EN_v09
 */
#define  VTSS_F_UVOV_UVOV_INT_EN_OVR_INT_EN_v09(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_UVOV_UVOV_INT_EN_OVR_INT_EN_v09  VTSS_BIT(20)
#define  VTSS_X_UVOV_UVOV_INT_EN_OVR_INT_EN_v09(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * UVR_INT_ENWhen set the respective interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_EN . UVR_INT_EN_v09
 */
#define  VTSS_F_UVOV_UVOV_INT_EN_UVR_INT_EN_v09(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_UVOV_UVOV_INT_EN_UVR_INT_EN_v09  VTSS_BIT(16)
#define  VTSS_X_UVOV_UVOV_INT_EN_UVR_INT_EN_v09(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * OVR_INT_ENWhen set the respective interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_EN . OVR_INT_EN_v12
 */
#define  VTSS_F_UVOV_UVOV_INT_EN_OVR_INT_EN_v12(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_UVOV_UVOV_INT_EN_OVR_INT_EN_v12  VTSS_BIT(12)
#define  VTSS_X_UVOV_UVOV_INT_EN_OVR_INT_EN_v12(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * UVR_INT_ENWhen set the respective interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_EN . UVR_INT_EN_v12
 */
#define  VTSS_F_UVOV_UVOV_INT_EN_UVR_INT_EN_v12(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_UVOV_UVOV_INT_EN_UVR_INT_EN_v12  VTSS_BIT(8)
#define  VTSS_X_UVOV_UVOV_INT_EN_UVR_INT_EN_v12(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * OVR_INT_ENWhen set the respective interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_EN . OVR_INT_EN_v18
 */
#define  VTSS_F_UVOV_UVOV_INT_EN_OVR_INT_EN_v18(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_UVOV_UVOV_INT_EN_OVR_INT_EN_v18  VTSS_BIT(4)
#define  VTSS_X_UVOV_UVOV_INT_EN_OVR_INT_EN_v18(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * UVR_INT_ENWhen set the respective interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_EN . UVR_INT_EN_v18
 */
#define  VTSS_F_UVOV_UVOV_INT_EN_UVR_INT_EN_v18(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_INT_EN_UVR_INT_EN_v18  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_INT_EN_UVR_INT_EN_v18(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Under and Over Voltage Interrupt Disable Register
 *
 * \details
 * Under and Over Voltage Interrupt Disable Register
 *
 * Register: \a UVOV:UVOV_REGS:UVOV_INT_DIS
 */
#define VTSS_UVOV_UVOV_INT_DIS               VTSS_IOREG(VTSS_TO_UVOV,0x3)

/**
 * \brief
 * TRIM_INT_DISWhen set the respective interrupt is disabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_DIS . TRIM_INT_DIS
 */
#define  VTSS_F_UVOV_UVOV_INT_DIS_TRIM_INT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_UVOV_UVOV_INT_DIS_TRIM_INT_DIS  VTSS_BIT(24)
#define  VTSS_X_UVOV_UVOV_INT_DIS_TRIM_INT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * OVR_INT_DISWhen set the respective interrupt is disabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_DIS . OVR_INT_DIS_V09
 */
#define  VTSS_F_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V09  VTSS_BIT(20)
#define  VTSS_X_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V09(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * UVR_INT_DISWhen set the respective interrupt is disabled
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_DIS . UVR_INT_DIS_V09
 */
#define  VTSS_F_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V09  VTSS_BIT(16)
#define  VTSS_X_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V09(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * OVR_INT_DISWhen set the respective interrupt is disabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_DIS . OVR_INT_DIS_V12
 */
#define  VTSS_F_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V12  VTSS_BIT(12)
#define  VTSS_X_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V12(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * UVR_INT_DISWhen set the respective interrupt is disabled
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_DIS . UVR_INT_DIS_V12
 */
#define  VTSS_F_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V12  VTSS_BIT(8)
#define  VTSS_X_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V12(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * OVR_INT_DISWhen set the respective interrupt is disabled.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_DIS . OVR_INT_DIS_V18
 */
#define  VTSS_F_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V18  VTSS_BIT(4)
#define  VTSS_X_UVOV_UVOV_INT_DIS_OVR_INT_DIS_V18(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * UVR_INT_DISWhen set the respective interrupt is disabled
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_INT_DIS . UVR_INT_DIS_V18
 */
#define  VTSS_F_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V18  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_INT_DIS_UVR_INT_DIS_V18(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a UVOV:UVOV_CFG
 *
 * Contains CFG0 and CFG1
 */


/**
 * \brief Tuning fields of cell
 *
 * \details
 * Tuning fields of 1.8V cell
 *
 * Register: \a UVOV:UVOV_CFG:TUNE
 */
#define VTSS_UVOV_TUNE                       VTSS_IOREG(VTSS_TO_UVOV,0x4)

/**
 * \brief
 * TUNE_CDRTemperature trim tune input.This register must be programmed
 * with the respective trim value in OTP
 *
 * \details
 * Field: ::VTSS_UVOV_TUNE . TUNE_CDR
 */
#define  VTSS_F_UVOV_TUNE_TUNE_CDR(x)         VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_UVOV_TUNE_TUNE_CDR            VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_UVOV_TUNE_TUNE_CDR(x)         VTSS_EXTRACT_BITFIELD(x,24,3)

/**
 * \brief
 * Magnitude trim tune input.This register must be programmed with the
 * respective trim value in OTP.
 *
 * \details
 * Field: ::VTSS_UVOV_TUNE . TUNE_M
 */
#define  VTSS_F_UVOV_TUNE_TUNE_M(x)           VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_UVOV_TUNE_TUNE_M              VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_UVOV_TUNE_TUNE_M(x)           VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * TUNE_MAGThis register is used to report the result of the trim
 * sequence.After the trim process completes the new value is loaded into
 * this register. The TRIM_DONE bit is set and the respective interrupt
 * asserts.Note: The trim process is only ran once at ATE.Note: The value
 * in this field is stored in OTP and must be written into therespective
 * TUNE_M register before using the UVOV function.
 *
 * \details
 * Field: ::VTSS_UVOV_TUNE . TUNE_MAG
 */
#define  VTSS_F_UVOV_TUNE_TUNE_MAG(x)         VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_UVOV_TUNE_TUNE_MAG            VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_UVOV_TUNE_TUNE_MAG(x)         VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * TRIM_ENWhen set this bit enables the trimming function. This bit self
 * clears after thetrim function completes.
 *
 * \details
 * Field: ::VTSS_UVOV_TUNE . TRIM_EN
 */
#define  VTSS_F_UVOV_TUNE_TRIM_EN(x)          VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_UVOV_TUNE_TRIM_EN             VTSS_BIT(6)
#define  VTSS_X_UVOV_TUNE_TRIM_EN(x)          VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief Debug functionality for ATP
 *
 * \details
 * Debug functionality for ATP
 *
 * Register: \a UVOV:UVOV_CFG:ATP_UVOV
 */
#define VTSS_UVOV_ATP_UVOV                   VTSS_IOREG(VTSS_TO_UVOV,0x5)

/**
 * \brief
 * Debug functionality for ATP enabled Chips 2'b00: ATP functionality
 * disabled 2'b01: Internal signal connected to ATP through internal
 * switches.
 *
 * \details
 * Field: ::VTSS_UVOV_ATP_UVOV . ATP_UVOV_SEL
 */
#define  VTSS_F_UVOV_ATP_UVOV_ATP_UVOV_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_UVOV_ATP_UVOV_ATP_UVOV_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_UVOV_ATP_UVOV_ATP_UVOV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Under and Over Voltage Configuration 0 Register
 *
 * \details
 * Under and Over Voltage Configuration 0 Register.
 *
 * Register: \a UVOV:UVOV_CFG:UVOV_CFG0_V09
 */
#define VTSS_UVOV_UVOV_CFG0_V09              VTSS_IOREG(VTSS_TO_UVOV,0x6)

/**
 * \brief
 * OV_DEB_ENWhen set the respective over voltage detection channel is
 * de-bounced.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V09 . OV_DEB_EN_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V09_OV_DEB_EN_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V09_OV_DEB_EN_V09  VTSS_BIT(28)
#define  VTSS_X_UVOV_UVOV_CFG0_V09_OV_DEB_EN_V09(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * UV_DEB_ENWhen set the respective under voltage detection channel is
 * de-bounced.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V09 . UV_DEB_EN_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V09_UV_DEB_EN_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V09_UV_DEB_EN_V09  VTSS_BIT(27)
#define  VTSS_X_UVOV_UVOV_CFG0_V09_UV_DEB_EN_V09(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * OV_RST_ENWhen set the respective over voltage detection channel is
 * capable ofgenerating a system reset.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V09 . OV_RST_EN_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V09_OV_RST_EN_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V09_OV_RST_EN_V09  VTSS_BIT(11)
#define  VTSS_X_UVOV_UVOV_CFG0_V09_OV_RST_EN_V09(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * UV_RST_ENWhen set the respective under voltage detection channel is
 * capable ofgenerating a system reset.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V09 . UV_RST_EN_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V09_UV_RST_EN_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V09_UV_RST_EN_V09  VTSS_BIT(10)
#define  VTSS_X_UVOV_UVOV_CFG0_V09_UV_RST_EN_V09(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * OVR_RNG_SELOver-voltage range select.Where X is VDD.00b:
 * X-X*(2.5/100)01b: X-X*(5/100)10b: X-X*(7.5/100)11b: X-X*(10/100)
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V09 . OVR_RNG_SEL_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V09_OVR_RNG_SEL_V09(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_UVOV_UVOV_CFG0_V09_OVR_RNG_SEL_V09     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_UVOV_UVOV_CFG0_V09_OVR_RNG_SEL_V09(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * UVR_RNG_SELUnder-voltage range select.Where X is VDD.00b:
 * X-X*(2.5/100)01b: X-X*(5/100)10b: X-X*(7.5/100)11b: X-X*(10/100)
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V09 . UVR_RNG_SEL_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V09_UVR_RNG_SEL_V09(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_UVOV_UVOV_CFG0_V09_UVR_RNG_SEL_V09     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_UVOV_UVOV_CFG0_V09_UVR_RNG_SEL_V09(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * OVR_DET_ENThis bit enables over voltage detection for this detector.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V09 . OVR_DET_EN_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V09_OVR_DET_EN_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V09_OVR_DET_EN_V09  VTSS_BIT(1)
#define  VTSS_X_UVOV_UVOV_CFG0_V09_OVR_DET_EN_V09(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * UVR_DET_ENThis bit enables under voltage detection for this detector.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V09 . UVR_DET_EN_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V09_UVR_DET_EN_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V09_UVR_DET_EN_V09  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_CFG0_V09_UVR_DET_EN_V09(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Under and Over Voltage Configuration 1
 *
 * \details
 * Under and Over Voltage Configuration 1
 *
 * Note: This register has no meaning for the UVOV instance that monitors
 * the core domain.
 *
 * Register: \a UVOV:UVOV_CFG:UVOV_CFG1_V09
 */
#define VTSS_UVOV_UVOV_CFG1_V09              VTSS_IOREG(VTSS_TO_UVOV,0x7)

/**
 * \brief
 * UVOV_DEBSpecifies the debounce value used or UV and OV channels that
 * havedebounce enabled.This register has units of a clock cycle (40 ns).A
 * value of 0h disables the debouncer.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V09 . UVOV_DEB_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V09_UVOV_DEB_V09(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_UVOV_UVOV_CFG1_V09_UVOV_DEB_V09     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_UVOV_UVOV_CFG1_V09_UVOV_DEB_V09(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * OV_STSProvides the real time status of the UVOV detector's OV_CR output
 * signal.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V09 . OV_STS_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V09_OV_STS_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_UVOV_UVOV_CFG1_V09_OV_STS_V09  VTSS_BIT(1)
#define  VTSS_X_UVOV_UVOV_CFG1_V09_OV_STS_V09(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * UV_STSProvides the real time status of the UVOV detector's UV_CR output
 * signal.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V09 . UV_STS_V09
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V09_UV_STS_V09(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_CFG1_V09_UV_STS_V09  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_CFG1_V09_UV_STS_V09(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Under and Over Voltage Configuration 0 Register
 *
 * \details
 * Under and Over Voltage Configuration 0 Register.
 *
 * Register: \a UVOV:UVOV_CFG:UVOV_CFG0_V12
 */
#define VTSS_UVOV_UVOV_CFG0_V12              VTSS_IOREG(VTSS_TO_UVOV,0x8)

/**
 * \brief
 * OV_DEB_ENWhen set the respective over voltage detection channel is
 * de-bounced.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V12 . OV_DEB_EN_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V12_OV_DEB_EN_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V12_OV_DEB_EN_V12  VTSS_BIT(28)
#define  VTSS_X_UVOV_UVOV_CFG0_V12_OV_DEB_EN_V12(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * UV_DEB_ENWhen set the respective under voltage detection channel is
 * de-bounced.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V12 . UV_DEB_EN_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V12_UV_DEB_EN_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V12_UV_DEB_EN_V12  VTSS_BIT(27)
#define  VTSS_X_UVOV_UVOV_CFG0_V12_UV_DEB_EN_V12(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * OV_RST_ENWhen set the respective over voltage detection channel is
 * capable ofgenerating a system reset.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V12 . OV_RST_EN_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V12_OV_RST_EN_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V12_OV_RST_EN_V12  VTSS_BIT(11)
#define  VTSS_X_UVOV_UVOV_CFG0_V12_OV_RST_EN_V12(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * UV_RST_ENWhen set the respective under voltage detection channel is
 * capable ofgenerating a system reset.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V12 . UV_RST_EN_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V12_UV_RST_EN_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V12_UV_RST_EN_V12  VTSS_BIT(10)
#define  VTSS_X_UVOV_UVOV_CFG0_V12_UV_RST_EN_V12(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * OVR_RNG_SELOver-voltage range select.Where X is VDD.00b:
 * X-X*(2.5/100)01b: X-X*(5/100)10b: X-X*(7.5/100)11b: X-X*(10/100)
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V12 . OVR_RNG_SEL_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V12_OVR_RNG_SEL_V12(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_UVOV_UVOV_CFG0_V12_OVR_RNG_SEL_V12     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_UVOV_UVOV_CFG0_V12_OVR_RNG_SEL_V12(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * UVR_RNG_SELUnder-voltage range select.Where X is VDD.00b:
 * X-X*(2.5/100)01b: X-X*(5/100)10b: X-X*(7.5/100)11b: X-X*(10/100)
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V12 . UVR_RNG_SEL_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V12_UVR_RNG_SEL_V12(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_UVOV_UVOV_CFG0_V12_UVR_RNG_SEL_V12     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_UVOV_UVOV_CFG0_V12_UVR_RNG_SEL_V12(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * OVR_DET_ENThis bit enables over voltage detection for this detector.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V12 . OVR_DET_EN_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V12_OVR_DET_EN_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V12_OVR_DET_EN_V12  VTSS_BIT(1)
#define  VTSS_X_UVOV_UVOV_CFG0_V12_OVR_DET_EN_V12(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * UVR_DET_ENThis bit enables under voltage detection for this detector.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V12 . UVR_DET_EN_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V12_UVR_DET_EN_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V12_UVR_DET_EN_V12  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_CFG0_V12_UVR_DET_EN_V12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Under and Over Voltage Configuration 1
 *
 * \details
 * Under and Over Voltage Configuration 1
 *
 * Note: This register has no meaning for the UVOV instance that monitors
 * the core domain.
 *
 * Register: \a UVOV:UVOV_CFG:UVOV_CFG1_V12
 */
#define VTSS_UVOV_UVOV_CFG1_V12              VTSS_IOREG(VTSS_TO_UVOV,0x9)

/**
 * \brief
 * UVOV_DEBSpecifies the debounce value used or UV and OV channels that
 * havedebounce enabled.This register has units of a clock cycle (40 ns).A
 * value of 0h disables the debouncer.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V12 . UVOV_DEB_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V12_UVOV_DEB_V12(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_UVOV_UVOV_CFG1_V12_UVOV_DEB_V12     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_UVOV_UVOV_CFG1_V12_UVOV_DEB_V12(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * OV_STSProvides the real time status of the UVOV detector's OV_CR output
 * signal.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V12 . OV_STS_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V12_OV_STS_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_UVOV_UVOV_CFG1_V12_OV_STS_V12  VTSS_BIT(1)
#define  VTSS_X_UVOV_UVOV_CFG1_V12_OV_STS_V12(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * UV_STSProvides the real time status of the UVOV detector's UV_CR output
 * signal.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V12 . UV_STS_V12
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V12_UV_STS_V12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_CFG1_V12_UV_STS_V12  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_CFG1_V12_UV_STS_V12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Under and Over Voltage Configuration 0 Register
 *
 * \details
 * Under and Over Voltage Configuration 0 Register.
 *
 * Register: \a UVOV:UVOV_CFG:UVOV_CFG0_V18
 */
#define VTSS_UVOV_UVOV_CFG0_V18              VTSS_IOREG(VTSS_TO_UVOV,0xa)

/**
 * \brief
 * OV_DEB_ENWhen set the respective over voltage detection channel is
 * de-bounced.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V18 . OV_DEB_EN_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V18_OV_DEB_EN_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V18_OV_DEB_EN_V18  VTSS_BIT(28)
#define  VTSS_X_UVOV_UVOV_CFG0_V18_OV_DEB_EN_V18(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * UV_DEB_ENWhen set the respective under voltage detection channel is
 * de-bounced.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V18 . UV_DEB_EN_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V18_UV_DEB_EN_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V18_UV_DEB_EN_V18  VTSS_BIT(27)
#define  VTSS_X_UVOV_UVOV_CFG0_V18_UV_DEB_EN_V18(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * OV_RST_ENWhen set the respective over voltage detection channel is
 * capable ofgenerating a system reset.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V18 . OV_RST_EN_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V18_OV_RST_EN_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V18_OV_RST_EN_V18  VTSS_BIT(11)
#define  VTSS_X_UVOV_UVOV_CFG0_V18_OV_RST_EN_V18(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * UV_RST_ENWhen set the respective under voltage detection channel is
 * capable ofgenerating a system reset.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V18 . UV_RST_EN_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V18_UV_RST_EN_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V18_UV_RST_EN_V18  VTSS_BIT(10)
#define  VTSS_X_UVOV_UVOV_CFG0_V18_UV_RST_EN_V18(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * OVR_RNG_SELOver-voltage range select.Where X is VDD.00b:
 * X-X*(2.5/100)01b: X-X*(5/100)10b: X-X*(7.5/100)11b: X-X*(10/100)
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V18 . OVR_RNG_SEL_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V18_OVR_RNG_SEL_V18(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_UVOV_UVOV_CFG0_V18_OVR_RNG_SEL_V18     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_UVOV_UVOV_CFG0_V18_OVR_RNG_SEL_V18(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * UVR_RNG_SELUnder-voltage range select.Where X is VDD.00b:
 * X-X*(2.5/100)01b: X-X*(5/100)10b: X-X*(7.5/100)11b: X-X*(10/100)
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V18 . UVR_RNG_SEL_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V18_UVR_RNG_SEL_V18(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_UVOV_UVOV_CFG0_V18_UVR_RNG_SEL_V18     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_UVOV_UVOV_CFG0_V18_UVR_RNG_SEL_V18(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * OVR_DET_ENThis bit enables over voltage detection for this detector.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V18 . OVR_DET_EN_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V18_OVR_DET_EN_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V18_OVR_DET_EN_V18  VTSS_BIT(1)
#define  VTSS_X_UVOV_UVOV_CFG0_V18_OVR_DET_EN_V18(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * UVR_DET_ENThis bit enables under voltage detection for this detector.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG0_V18 . UVR_DET_EN_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG0_V18_UVR_DET_EN_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_CFG0_V18_UVR_DET_EN_V18  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_CFG0_V18_UVR_DET_EN_V18(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Under and Over Voltage Configuration 1
 *
 * \details
 * Under and Over Voltage Configuration 1
 *
 * Note: This register has no meaning for the UVOV instance that monitors
 * the core domain.
 *
 * Register: \a UVOV:UVOV_CFG:UVOV_CFG1_V18
 */
#define VTSS_UVOV_UVOV_CFG1_V18              VTSS_IOREG(VTSS_TO_UVOV,0xb)

/**
 * \brief
 * UVOV_DEBSpecifies the debounce value used or UV and OV channels that
 * havedebounce enabled.This register has units of a clock cycle (40 ns).A
 * value of 0h disables the debouncer.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V18 . UVOV_DEB_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V18_UVOV_DEB_V18(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_UVOV_UVOV_CFG1_V18_UVOV_DEB_V18     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_UVOV_UVOV_CFG1_V18_UVOV_DEB_V18(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * OV_STSProvides the real time status of the UVOV detector's OV_CR output
 * signal.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V18 . OV_STS_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V18_OV_STS_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_UVOV_UVOV_CFG1_V18_OV_STS_V18  VTSS_BIT(1)
#define  VTSS_X_UVOV_UVOV_CFG1_V18_OV_STS_V18(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * UV_STSProvides the real time status of the UVOV detector's UV_CR output
 * signal.
 *
 * \details
 * Field: ::VTSS_UVOV_UVOV_CFG1_V18 . UV_STS_V18
 */
#define  VTSS_F_UVOV_UVOV_CFG1_V18_UV_STS_V18(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_UVOV_UVOV_CFG1_V18_UV_STS_V18  VTSS_BIT(0)
#define  VTSS_X_UVOV_UVOV_CFG1_V18_UV_STS_V18(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_LAGUNA_REGS_UVOV_H_ */
