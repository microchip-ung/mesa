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

#ifndef _VTSS_FA_REGS_HSIOWRAP_H_
#define _VTSS_FA_REGS_HSIOWRAP_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a HSIOWRAP
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a HSIOWRAP:SYNC_ETH_CFG
 *
 * SYNC_ETH Configuration Registers
 */


/** 
 * \brief Recovered Clock Configuration
 *
 * \details
 * This register is replicated once per recovered clock destination.
 * Replications 0-3 are GPIO mapped recovered clocks 0 though 3.
 * Replications 4-7 are SD10G mapped recovered clocks.
 *
 * Register: \a HSIOWRAP:SYNC_ETH_CFG:SYNC_ETH_CFG
 *
 * @param ri Register: SYNC_ETH_CFG (??), 0-3
 */
#define VTSS_HSIOWRAP_SYNC_ETH_CFG(ri)       VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x0 + (ri))

/** 
 * \brief
 * Select recovered clock source.
 *
 * \details 
 * 0-16: Select SD6G 0 through 16 recovered RX data clock
 * 17-32: Select SD10G 0 through 15 recovered RX data lock
 * 33: Select AUX1 clock from LCPLL1 reference
 * 34: Select AUX2 clock from LCPLL1 reference
 * 35: Select AUX3 clock from LCPLL1 reference
 * 36: Select AUX4 clock from LCPLL1 reference
 * Other values are reserved.
 *
 * Field: ::VTSS_HSIOWRAP_SYNC_ETH_CFG . SEL_RECO_CLK_SRC
 */
#define  VTSS_F_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Select recovered clock divider.
 *
 * \details 
 * 0: Divide clock by 2
 * 1: Divide clock by 4
 * 2: Divide clock by 8
 * 3: Divide clock by 16
 * 4: Divide clock by 5
 * 5: Divide clock by 25
 * 6: No clock dividing
 * 7: Reserved
 *
 * Field: ::VTSS_HSIOWRAP_SYNC_ETH_CFG . SEL_RECO_CLK_DIV
 */
#define  VTSS_F_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Set to enable recovered clock generation. Bit is also used to enable
 * corresponding GPIO pad. 
 *
 * \details 
 * 0: Disable (high-impedance)
 * 1: Enable (output recovered clock)
 *
 * Field: ::VTSS_HSIOWRAP_SYNC_ETH_CFG . RECO_CLK_ENA
 */
#define  VTSS_F_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA  VTSS_BIT(12)
#define  VTSS_X_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * Register Group: \a HSIOWRAP:GPIO_CFG
 *
 * Registers for accessing the GPIO pad cell configuration
 */


/** 
 * \brief GPIO pad cell configuration
 *
 * \details
 * Register: \a HSIOWRAP:GPIO_CFG:GPIO_CFG
 *
 * @param ri Replicator: x_FFL_DEVCPU_GPIO_CNT (??), 0-63
 */
#define VTSS_HSIOWRAP_GPIO_CFG(ri)           VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x4 + (ri))

/** 
 * \brief
 * Controls the drive strength of GPIO outputs
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . G_DS
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_G_DS(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_G_DS        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_G_DS(x)     VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Enable schmitt trigger function on GPIO inputs
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . G_ST
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_G_ST(x)     VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_G_ST        VTSS_BIT(2)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_G_ST(x)     VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable pull up resistor on GPIO inputs. Should not be set to '1' when
 * G_PD is '1'
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . G_PU
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_G_PU(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_G_PU        VTSS_BIT(3)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_G_PU(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable pull down resistor on GPIO inputs. Should not be set to '1' when
 * G_PU is '1'
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . G_PD
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_G_PD(x)     VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_G_PD        VTSS_BIT(4)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_G_PD(x)     VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * Register Group: \a HSIOWRAP:TEMP_SENSOR
 *
 * Temperature sensor control
 */


/** 
 * \brief Temperature Sensor Control
 *
 * \details
 * Register: \a HSIOWRAP:TEMP_SENSOR:TEMP_SENSOR_CTRL
 */
#define VTSS_HSIOWRAP_TEMP_SENSOR_CTRL       VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x44)

/** 
 * \brief
 * Set to force reading of temperature. This field only works when
 * SAMPLE_ENA is cleared. The read will either instantaneously or
 * synchronized to the RDY output of the temperature sensor if the sensor
 * is enabled.	The temperature sensor can be configured to run
 * continuously by using these settings:FORCE_POWER_UP = 1Wait 50
 * usFORCE_CLK = 1Wait 5 usFORCE_NO_RST = 1Wait 5 usFORCE_RUN =
 * 1FORCE_TEMP_RD= 1This will cause the temperature sensor to sample
 * continuously and provide the result in TEMP_SENSOR_STAT.TEMP.  The
 * status TEMP_SENSOR_STAT.TEMP_VALID will be 1 after the first sample.
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CTRL . FORCE_TEMP_RD
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_TEMP_RD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_TEMP_RD  VTSS_BIT(4)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_TEMP_RD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set to force RUN signal towards temperature sensor. This field only
 * works when SAMPLE_ENA is cleared.
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CTRL . FORCE_RUN
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_RUN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_RUN  VTSS_BIT(3)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_RUN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set to force the RSTN signal towards temperature sensor (release of
 * reset). This field only works when SAMPLE_ENA is cleared.
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CTRL . FORCE_NO_RST
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_NO_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_NO_RST  VTSS_BIT(2)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_NO_RST(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to force the PD signal towards temperature sensor. This field only
 * works when SAMPLE_ENA is cleared.
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CTRL . FORCE_POWER_UP
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_POWER_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_POWER_UP  VTSS_BIT(1)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_POWER_UP(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to force a clock signal towards the temperature sensor. The clock
 * frequency will be controlled by the TEMP_SENSOR_CFG.CLK_CYCLES_1US
 * setting. This field only works when SAMPLE_ENA is cleared.
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CTRL . FORCE_CLK
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_CLK  VTSS_BIT(0)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CTRL_FORCE_CLK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Temperature Sensor Configuration
 *
 * \details
 * Register: \a HSIOWRAP:TEMP_SENSOR:TEMP_SENSOR_CFG
 */
#define VTSS_HSIOWRAP_TEMP_SENSOR_CFG        VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x45)

/** 
 * \brief
 * The number of system clock cycles in one 1us. This is used to generated
 * the temperature sensor clock signal (CLK.)  The frequency of CLK must be
 * higher than 0.75Mhz and lower than 2Mhz.
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CFG . CLK_CYCLES_1US
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CFG_CLK_CYCLES_1US(x)  VTSS_ENCODE_BITFIELD(x,15,10)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_CLK_CYCLES_1US     VTSS_ENCODE_BITMASK(15,10)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CFG_CLK_CYCLES_1US(x)  VTSS_EXTRACT_BITFIELD(x,15,10)

/** 
 * \brief
 * Trim value. This value should only be modified as a result of a sensor
 * calibration
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CFG . TRIM_VAL
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CFG_TRIM_VAL(x)  VTSS_ENCODE_BITFIELD(x,11,4)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_TRIM_VAL     VTSS_ENCODE_BITMASK(11,4)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CFG_TRIM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,11,4)

/** 
 * \brief
 * Set this field to enable calibration of the sensor. A 0.7V signal must
 * be applied to the calibration input.The calibration procedure is as
 * follows:Set SAMPLE_ENA to 0Apply 0.7V +/- 10% to the calibration input
 * pinMeasure actual voltage on calibration input with highest possible
 * precisionSet CAL_ENA to 1Set SAMPLE_ENA to 1Read TEMP_SENSOR_STAT.TEMP
 * and use this value and the calibration voltage to calculate the
 * calibration temperature.Find TRIM_VAL:Set SAMPLE_ENA to 0Set CAL_ENA to
 * 0Set SAMPLE_ENA to 1Change TRIM_VAL until TEMP_SENSOR_STAT.TEMP results
 * in a temperature as close as possible to the calibration
 * temperatureNormal mode:Set SAMPLE_ENA to 1Use TRIM_VAL obtained from
 * calibration
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CFG . CAL_ENA
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CFG_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_CAL_ENA  VTSS_BIT(10)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CFG_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Power up delay. The unit is number of sensor CLK cycles. See:
 * CLK_CYCLES_1USDefault value corresponds to a 50us delay, which is the
 * minimum required value.
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CFG . PWR_UP_DELAY
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CFG_PWR_UP_DELAY(x)  VTSS_ENCODE_BITFIELD(x,3,7)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_PWR_UP_DELAY     VTSS_ENCODE_BITMASK(3,7)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CFG_PWR_UP_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,3,7)

/** 
 * \brief
 * Set this bit to start a temperature sample cycle. This is only used if
 * continuous sampling is disabled.Procedure:Set START_CAPTURE to 1Wait
 * until hardware clears START_CAPTURE Read temperature from
 * TEMP_SENSOR_STAT.TEMP
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CFG . START_CAPTURE
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CFG_START_CAPTURE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_START_CAPTURE  VTSS_BIT(2)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CFG_START_CAPTURE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set this field to enable continuous sampling of temperature. The latest
 * sample value will be available in TEMP_SENSOR_STAT.TEMP
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CFG . CONTINUOUS_MODE
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CFG_CONTINUOUS_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_CONTINUOUS_MODE  VTSS_BIT(1)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CFG_CONTINUOUS_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to enable sampling of temperature. The sensor will be
 * taken out of power down mode and the temperature sampling is stared when
 * SAMPLE_ENA is set to 1
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_CFG . SAMPLE_ENA
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_CFG_SAMPLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_CFG_SAMPLE_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_CFG_SAMPLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Temperature Sensor Status
 *
 * \details
 * Register: \a HSIOWRAP:TEMP_SENSOR:TEMP_SENSOR_STAT
 */
#define VTSS_HSIOWRAP_TEMP_SENSOR_STAT       VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x46)

/** 
 * \brief
 * This field is set when valid temperature data is available in
 * TEMP_SENSOR_STAT.TEMP
 *
 * \details 
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_STAT . TEMP_VALID
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_STAT_TEMP_VALID(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_STAT_TEMP_VALID  VTSS_BIT(12)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_STAT_TEMP_VALID(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Temperature data readout This field is valid when
 * TEMP_SENSOR_STAT.TEMP_VALID is set. This field is continually updated
 * while the temperature sensor is enabled. See TEMP_SENSOR_CFG.SAMPLE_ENA
 * for more information.
 *
 * \details 
 * Temp(C) = TEMP_SENSOR_STAT.TEMP / 4096 * 352.2 - 109.4
 *
 * Field: ::VTSS_HSIOWRAP_TEMP_SENSOR_STAT . TEMP
 */
#define  VTSS_F_HSIOWRAP_TEMP_SENSOR_STAT_TEMP(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSIOWRAP_TEMP_SENSOR_STAT_TEMP     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSIOWRAP_TEMP_SENSOR_STAT_TEMP(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_FA_REGS_HSIOWRAP_H_ */
