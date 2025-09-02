// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_GLOBAL_H_
#define LAN80XX_MALIBU25G_REGS_GLOBAL_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a GLOBAL
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a GLOBAL:STRAP_INFO
 *
 * Device Info
 */


/**
 * \brief Strap read register
 *
 * \details
 * Strap read register
 *
 * Register: \a GLOBAL:STRAP_INFO:STRAP_READ_REG
 */
#define LAN80XX_GLOBAL_STRAP_READ_REG                                                               (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x200))

/**
 * \brief
 * The value of this register is the value of strap pins latched on the
 * deassertion of RESET_N pin
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_STRAP_READ_REG . STRAP_READ
 */
#define  LAN80XX_F_GLOBAL_STRAP_READ_REG_STRAP_READ(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_GLOBAL_STRAP_READ_REG_STRAP_READ                                                 (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_GLOBAL_STRAP_READ_REG_STRAP_READ(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief Strap override register
 *
 * \details
 * Strap override register
 *
 * Register: \a GLOBAL:STRAP_INFO:STRAP_OVERRIDE_REG
 */
#define LAN80XX_GLOBAL_STRAP_OVERRIDE_REG                                                           (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x201))

/**
 * \brief
 * Host S/W use this register to override the STRAP_READ_REG;STRAP_READ
 *
 * \details
 * the default of bit[7:0] is the value of STRAP_READ_REG;STRAP_READ
 * the default of bit[15:8] is 0
 *
 * Field: ::LAN80XX_GLOBAL_STRAP_OVERRIDE_REG . STRAP_OVERRIDE
 */
#define  LAN80XX_F_GLOBAL_STRAP_OVERRIDE_REG_STRAP_OVERRIDE(x)                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_STRAP_OVERRIDE_REG_STRAP_OVERRIDE                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_STRAP_OVERRIDE_REG_STRAP_OVERRIDE(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a GLOBAL:BLOCK_LEVEL_SOFTWARE_RESET
 *
 * Block level software reset registers
 */


/**
 * \brief Block Level Software Reset register 1
 *
 * \details
 * Register: \a GLOBAL:BLOCK_LEVEL_SOFTWARE_RESET:BLOCK_LEVEL_SOFTWARE_RESET1
 */
#define LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1                                                  (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x202))

/**
 * \brief
 * Reset the logic and configuration registers in 1588 clock generator,
 * self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_1588_CLKGEN
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_CLKGEN(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_CLKGEN                          (LAN80XX_BIT(15))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_CLKGEN(x)                       (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * Reset the logic and configuration registers in 1588 STI. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_1588_STI
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_STI(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),14,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_STI                             (LAN80XX_BIT(14))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_STI(x)                          (LAN80XX_EXTRACT_BITFIELD(x,14,1))

/**
 * \brief
 * Reset the logic and configuration registers in 1588 LTC. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_1588_LTC
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_LTC(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),13,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_LTC                             (LAN80XX_BIT(13))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_LTC(x)                          (LAN80XX_EXTRACT_BITFIELD(x,13,1))

/**
 * \brief
 * Reset the logic and configuration registers in Cross-connect.
 * self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_XC
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_XC(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_XC                                   (LAN80XX_BIT(12))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_XC(x)                                (LAN80XX_EXTRACT_BITFIELD(x,12,1))

/**
 * \brief
 * Reset the datapath, configuration registers and csr rings in slice 3
 * host. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_HOST_SLICE_3
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_3(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),11,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_3                         (LAN80XX_BIT(11))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_3(x)                      (LAN80XX_EXTRACT_BITFIELD(x,11,1))

/**
 * \brief
 * Reset the datapath, configuration registers and csr rings in slice 3
 * line. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_LINE_SLICE_3
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_3(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_3                         (LAN80XX_BIT(10))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_3(x)                      (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * Reset the datapath, configuration registers and csr rings in slice 2
 * host. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_HOST_SLICE_2
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_2(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_2                         (LAN80XX_BIT(9))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_2(x)                      (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * Reset the datapath, configuration registers and csr rings in slice 2
 * line. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_LINE_SLICE_2
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_2(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_2                         (LAN80XX_BIT(8))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_2(x)                      (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Reset the datapath, configuration registers and csr rings in slice 1
 * host. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_HOST_SLICE_1
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_1(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_1                         (LAN80XX_BIT(7))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_1(x)                      (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * Reset the datapath, configuration registers and csr rings in slice 1
 * line. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_LINE_SLICE_1
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_1(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_1                         (LAN80XX_BIT(6))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_1(x)                      (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Reset the datapath, configuration registers and csr rings in slice 0
 * host. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_HOST_SLICE_0
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_0(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_0                         (LAN80XX_BIT(5))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_HOST_SLICE_0(x)                      (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Reset the datapath, configuration registers and csr rings in slice 0
 * line. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_LINE_SLICE_0
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_0(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_0                         (LAN80XX_BIT(4))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_LINE_SLICE_0(x)                      (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Reset the MDIO chip management interface. self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_MDIO
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_MDIO(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_MDIO                                 (LAN80XX_BIT(3))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_MDIO(x)                              (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Reset the SPI chip management interface.  This is not the PTP STI
 * interface.self-clearing
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_SPI
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_SPI(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_SPI                                  (LAN80XX_BIT(2))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_SPI(x)                               (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Reset the datapath in all slices, all csr rings and all configuration
 * registers except the GPIO configuration registers (1ExF200-1ExF2FF) and
 * global configuration registers (1Ex0200-1Ex05FF).  GPIO functions are
 * not modified when using this software reset since the GPIO configuration
 * registers are not reset to default settings. STRAP inputs are not
 * reloaded. MCU subsystem is reset. self-clearing.
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1 . SW_RESET_CHIP
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_CHIP(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_CHIP                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_CHIP(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Block Level Software Reset register 2
 *
 * \details
 * Register: \a GLOBAL:BLOCK_LEVEL_SOFTWARE_RESET:BLOCK_LEVEL_SOFTWARE_RESET2
 */
#define LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2                                                  (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x203))

/**
 * \brief
 * Reset the MCU
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2 . SW_RESET_MCU
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2_SW_RESET_MCU(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2_SW_RESET_MCU                                  (LAN80XX_BIT(1))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2_SW_RESET_MCU(x)                               (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Reset the temp sensor controller
 *
 * \details
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: ::LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2 . SW_RESET_TEMP_SENSOR
 */
#define  LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2_SW_RESET_TEMP_SENSOR(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2_SW_RESET_TEMP_SENSOR                          (LAN80XX_BIT(0))
#define  LAN80XX_X_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET2_SW_RESET_TEMP_SENSOR(x)                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a GLOBAL:TEMP_SENSOR
 *
 * Temperature sensor control
 */


/**
 * \brief Temperature Sensor Control
 *
 * \details
 * Register: \a GLOBAL:TEMP_SENSOR:TEMP_SENSOR_CTRL
 */
#define LAN80XX_GLOBAL_TEMP_SENSOR_CTRL                                                             (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0 ,0x204))

/**
 * \brief
 * Set to force reading of temperature. This field only works when
 * SAMPLE_ENA is cleared. The read will either instantaneously or
 * synchronized to the RDY output of the temperature sensor if the sensor
 * is enabled.  The temperature sensor can be configured to run
 * continuously by using these settings:FORCE_POWER_UP = 1Wait 50
 * usFORCE_CLK = 1Wait 5 usFORCE_NO_RST = 1Wait 5 usFORCE_RUN =
 * 1FORCE_TEMP_RD= 1This will cause the temperature sensor to sample
 * continuously and provide the result in TEMP_SENSOR_STAT.TEMP.  The
 * status TEMP_SENSOR_STAT.TEMP_VALID will be 1 after the first sample.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CTRL . FORCE_TEMP_RD
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CTRL_FORCE_TEMP_RD(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CTRL_FORCE_TEMP_RD                                            (LAN80XX_BIT(4))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CTRL_FORCE_TEMP_RD(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Set to force RUN signal towards temperature sensor. This field only
 * works when SAMPLE_ENA is cleared.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CTRL . FORCE_RUN
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CTRL_FORCE_RUN(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CTRL_FORCE_RUN                                                (LAN80XX_BIT(3))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CTRL_FORCE_RUN(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Set to force the RSTN signal towards temperature sensor (release of
 * reset). This field only works when SAMPLE_ENA is cleared.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CTRL . FORCE_NO_RST
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CTRL_FORCE_NO_RST(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CTRL_FORCE_NO_RST                                             (LAN80XX_BIT(2))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CTRL_FORCE_NO_RST(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Set to force the PD signal towards temperature sensor. This field only
 * works when SAMPLE_ENA is cleared.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CTRL . FORCE_POWER_UP
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CTRL_FORCE_POWER_UP(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CTRL_FORCE_POWER_UP                                           (LAN80XX_BIT(1))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CTRL_FORCE_POWER_UP(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Set to force a clock signal towards the temperature sensor. The clock
 * frequency will be controlled by the TEMP_SENSOR_CFG.CLK_CYCLES_1US
 * setting. This field only works when SAMPLE_ENA is cleared.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CTRL . FORCE_CLK
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CTRL_FORCE_CLK(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CTRL_FORCE_CLK                                                (LAN80XX_BIT(0))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CTRL_FORCE_CLK(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Temperature Sensor Configuration 0
 *
 * \details
 * Register: \a GLOBAL:TEMP_SENSOR:TEMP_SENSOR_CFG_0
 */
#define LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0                                                            (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0 ,0x205))

/**
 * \brief
 * Trim value. This value should only be modified as a result of a sensor
 * calibration
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0 . TRIM_VAL
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CFG_0_TRIM_VAL(x)                                             (LAN80XX_ENCODE_BITFIELD(x,11,4))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_TRIM_VAL                                                (LAN80XX_ENCODE_BITMASK(11,4))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CFG_0_TRIM_VAL(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,11,4))

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
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0 . CAL_ENA
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CFG_0_CAL_ENA(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_CAL_ENA                                                 (LAN80XX_BIT(10))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CFG_0_CAL_ENA(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief
 * Power up delay. The unit is number of sensor CLK cycles. See:
 * CLK_CYCLES_1USDefault value corresponds to a 50us delay, which is the
 * minimum required value.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0 . PWR_UP_DELAY
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CFG_0_PWR_UP_DELAY(x)                                         (LAN80XX_ENCODE_BITFIELD(x,3,7))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_PWR_UP_DELAY                                            (LAN80XX_ENCODE_BITMASK(3,7))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CFG_0_PWR_UP_DELAY(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,3,7))

/**
 * \brief
 * Set this bit to start a temperature sample cycle. This is only used if
 * continuous sampling is disabled.Procedure:Set START_CAPTURE to 1Wait
 * until hardware clears START_CAPTURE Read temperature from
 * TEMP_SENSOR_STAT.TEMP
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0 . START_CAPTURE
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CFG_0_START_CAPTURE(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_START_CAPTURE                                           (LAN80XX_BIT(2))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CFG_0_START_CAPTURE(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Set this field to enable continuous sampling of temperature. The latest
 * sample value will be available in TEMP_SENSOR_STAT.TEMP
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0 . CONTINUOUS_MODE
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CFG_0_CONTINUOUS_MODE(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_CONTINUOUS_MODE                                         (LAN80XX_BIT(1))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CFG_0_CONTINUOUS_MODE(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Set this field to enable sampling of temperature. The sensor will be
 * taken out of power down mode and the temperature sampling is started
 * when SAMPLE_ENA is set to 1
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0 . SAMPLE_ENA
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CFG_0_SAMPLE_ENA(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_SAMPLE_ENA                                              (LAN80XX_BIT(0))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CFG_0_SAMPLE_ENA(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Temperature Sensor Configuration 1
 *
 * \details
 * Register: \a GLOBAL:TEMP_SENSOR:TEMP_SENSOR_CFG_1
 */
#define LAN80XX_GLOBAL_TEMP_SENSOR_CFG_1                                                            (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0 ,0x206))

/**
 * \brief
 * The number of system clock cycles in one 1us. This is used to generated
 * the temperature sensor clock signal (CLK.)  The frequency of CLK must be
 * higher than 0.75Mhz and lower than 2Mhz.0x12C = 300 for 300.00Mhz System
 * Clock
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_CFG_1 . CLK_CYCLES_1US
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_CFG_1_CLK_CYCLES_1US(x)                                       (LAN80XX_ENCODE_BITFIELD(x,0,10))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_1_CLK_CYCLES_1US                                          (LAN80XX_ENCODE_BITMASK(0,10))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_CFG_1_CLK_CYCLES_1US(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,10))


/**
 * \brief Temperature Sensor Status
 *
 * \details
 * Register: \a GLOBAL:TEMP_SENSOR:TEMP_SENSOR_STAT
 */
#define LAN80XX_GLOBAL_TEMP_SENSOR_STAT                                                             (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0 ,0x207))

/**
 * \brief
 * This field is set when valid temperature data is available in
 * TEMP_SENSOR_STAT.TEMP
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_STAT . TEMP_VALID
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_STAT_TEMP_VALID(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),12,1))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_STAT_TEMP_VALID                                               (LAN80XX_BIT(12))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_STAT_TEMP_VALID(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,12,1))

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
 * Field: ::LAN80XX_GLOBAL_TEMP_SENSOR_STAT . TEMP
 */
#define  LAN80XX_F_GLOBAL_TEMP_SENSOR_STAT_TEMP(x)                                                  (LAN80XX_ENCODE_BITFIELD(x,0,12))
#define  LAN80XX_M_GLOBAL_TEMP_SENSOR_STAT_TEMP                                                     (LAN80XX_ENCODE_BITMASK(0,12))
#define  LAN80XX_X_GLOBAL_TEMP_SENSOR_STAT_TEMP(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,0,12))

/**
 * Register Group: \a GLOBAL:WARM_RESTART_REGS
 *
 * Warm Restart registers
 */


/**
 * \brief Warm Restart registers
 *
 * \details
 * Register: \a GLOBAL:WARM_RESTART_REGS:WARM_RESTART_REG
 *
 * @param ri Register: WARM_RESTART_REG (??), 0-3
 */
#define LAN80XX_GLOBAL_WARM_RESTART_REG(ri)                                                         (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x208 + (ri)))

/**
 * \brief
 * The 16 bit read/write Warm Restart registers have no effect on silicon
 * operation. They are intendedto be used by the programmer to hold data
 * needed by software to perform a Warm Restart.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_WARM_RESTART_REG . WARM_RESTART
 */
#define  LAN80XX_F_GLOBAL_WARM_RESTART_REG_WARM_RESTART(x)                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_WARM_RESTART_REG_WARM_RESTART                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_WARM_RESTART_REG_WARM_RESTART(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a GLOBAL:SPI_CTRL
 *
 * SPI mode control register
 */


/**
 * \brief SPI mode control register
 *
 * \details
 * SPI mode control register
 *
 * Register: \a GLOBAL:SPI_CTRL:SPI_CTRL
 */
#define LAN80XX_GLOBAL_SPI_CTRL                                                                     (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x20d))

/**
 * \brief
 * Set the SPI management interface mode
 *
 * \details
 * 0: Normal mode
 * 1: Fast mode
 *
 * Field: ::LAN80XX_GLOBAL_SPI_CTRL . FAST_MODE
 */
#define  LAN80XX_F_GLOBAL_SPI_CTRL_FAST_MODE(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_GLOBAL_SPI_CTRL_FAST_MODE                                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_GLOBAL_SPI_CTRL_FAST_MODE(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a GLOBAL:ROSC
 *
 * Ring oscillator control
 */


/**
 * \brief Enable and configure ring oscillators
 *
 * \details
 * Register: \a GLOBAL:ROSC:ROSC_CFG
 *
 * @param ri Register: ROSC_CFG (??), 0-5
 */
#define LAN80XX_GLOBAL_ROSC_CFG(ri)                                                                 (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x240 + (ri)))

/**
 * \brief
 * Select transistors used by the ring oscillators. The replication number
 * is used to select.See: ROSC_CFG.ROSC_ENAMode bit encoding:0: HVT1: SVT2:
 * LVT3: Reserved
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_ROSC_CFG . ROSC_MODE
 */
#define  LAN80XX_F_GLOBAL_ROSC_CFG_ROSC_MODE(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,1,2))
#define  LAN80XX_M_GLOBAL_ROSC_CFG_ROSC_MODE                                                        (LAN80XX_ENCODE_BITMASK(1,2))
#define  LAN80XX_X_GLOBAL_ROSC_CFG_ROSC_MODE(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,1,2))

/**
 * \brief
 * Enable any of the six ring oscillators. The replication number is used
 * to select:replication 0: NW cornerreplication 1: NE cornerreplication 2:
 * SE cornerreplication 3: SW cornerreplication 4: Centerreplication 5:
 * Temp Diode
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_ROSC_CFG . ROSC_ENA
 */
#define  LAN80XX_F_GLOBAL_ROSC_CFG_ROSC_ENA(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_GLOBAL_ROSC_CFG_ROSC_ENA                                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_GLOBAL_ROSC_CFG_ROSC_ENA(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Configuration register 0 for ring oscillator measurements
 *
 * \details
 * Register: \a GLOBAL:ROSC:ROSC_MEASURE_CFG_0
 */
#define LAN80XX_GLOBAL_ROSC_MEASURE_CFG_0                                                           (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x248))

/**
 * \brief
 * Number of clock cycles per capture time unit. The default value of 6262
 * corresponds to a 10us base time unit.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_ROSC_MEASURE_CFG_0 . TIME_BASE
 */
#define  LAN80XX_F_GLOBAL_ROSC_MEASURE_CFG_0_TIME_BASE(x)                                           (LAN80XX_ENCODE_BITFIELD(x,0,13))
#define  LAN80XX_M_GLOBAL_ROSC_MEASURE_CFG_0_TIME_BASE                                              (LAN80XX_ENCODE_BITMASK(0,13))
#define  LAN80XX_X_GLOBAL_ROSC_MEASURE_CFG_0_TIME_BASE(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,13))


/**
 * \brief Configuration register 1 for ring oscillator measurements
 *
 * \details
 * Register: \a GLOBAL:ROSC:ROSC_MEASURE_CFG_1
 */
#define LAN80XX_GLOBAL_ROSC_MEASURE_CFG_1                                                           (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x249))

/**
 * \brief
 * Configure the ring oscillator measuring time in base time units. The
 * default values corresponds to a measuring time of 1msSee:
 * ROSC_MEASURE_CFG.TIME_BASETime = MEASURE_TIME * TIME_BASE
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_ROSC_MEASURE_CFG_1 . MEASURE_TIME
 */
#define  LAN80XX_F_GLOBAL_ROSC_MEASURE_CFG_1_MEASURE_TIME(x)                                        (LAN80XX_ENCODE_BITFIELD(x,5,8))
#define  LAN80XX_M_GLOBAL_ROSC_MEASURE_CFG_1_MEASURE_TIME                                           (LAN80XX_ENCODE_BITMASK(5,8))
#define  LAN80XX_X_GLOBAL_ROSC_MEASURE_CFG_1_MEASURE_TIME(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,5,8))

/**
 * \brief
 * Start sampling of the selected ring oscillator output. The HW will clear
 * this bit when the measuring time has passed.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_ROSC_MEASURE_CFG_1 . START
 */
#define  LAN80XX_F_GLOBAL_ROSC_MEASURE_CFG_1_START(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_GLOBAL_ROSC_MEASURE_CFG_1_START                                                  (LAN80XX_BIT(4))
#define  LAN80XX_X_GLOBAL_ROSC_MEASURE_CFG_1_START(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Select one of the six ring oscillators to sample:0: NW corner1: NE
 * corner2: SE corner3: SW corner4: Center5: Temp Diode6-7: Reserved
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_ROSC_MEASURE_CFG_1 . ROSC_SEL
 */
#define  LAN80XX_F_GLOBAL_ROSC_MEASURE_CFG_1_ROSC_SEL(x)                                            (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_GLOBAL_ROSC_MEASURE_CFG_1_ROSC_SEL                                               (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_GLOBAL_ROSC_MEASURE_CFG_1_ROSC_SEL(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,3))


/**
 * \brief ROSC frequency
 *
 * \details
 * Register: \a GLOBAL:ROSC:ROSC_FREQ_CNT
 */
#define LAN80XX_GLOBAL_ROSC_FREQ_CNT                                                                (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x24a))

/**
 * \brief
 * The frequency of the configured ring oscillator. This is expressed as
 * the number of counts that has occurred during the measuring
 * time:freq_osc = FREQ_CNT / (TIME_BASE(s) * MEASURE_TIME)When the default
 * configuration is used a FREQ_CNT value of 1000 corresponds to a ring
 * oscillator frequency of 1 MHz.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_ROSC_FREQ_CNT . FREQ_CNT
 */
#define  LAN80XX_F_GLOBAL_ROSC_FREQ_CNT_FREQ_CNT(x)                                                 (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_ROSC_FREQ_CNT_FREQ_CNT                                                    (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_ROSC_FREQ_CNT_FREQ_CNT(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a GLOBAL:PAD
 *
 * PAD control registers
 */


/**
 * \brief IO Pad Control registers
 *
 * \details
 * Register: \a GLOBAL:PAD:IO_PAD_CTRL
 *
 * @param ri Register: IO_PAD_CTRL (??), 0-79
 */
#define LAN80XX_GLOBAL_IO_PAD_CTRL(ri)                                                              (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x280 + (ri)))

/**
 * \details
 * 0 = Mode pad controlled
 * 1 = Override
 *
 * Field: ::LAN80XX_GLOBAL_IO_PAD_CTRL . VOLTAGE_OVR
 */
#define  LAN80XX_F_GLOBAL_IO_PAD_CTRL_VOLTAGE_OVR(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_GLOBAL_IO_PAD_CTRL_VOLTAGE_OVR                                                   (LAN80XX_BIT(8))
#define  LAN80XX_X_GLOBAL_IO_PAD_CTRL_VOLTAGE_OVR(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Only valid when VOLTAGE_OVR is 1
 *
 * \details
 * 0 = 1.8V
 * 1 = 3.3V
 *
 * Field: ::LAN80XX_GLOBAL_IO_PAD_CTRL . VOLTAGE_MODE
 */
#define  LAN80XX_F_GLOBAL_IO_PAD_CTRL_VOLTAGE_MODE(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_GLOBAL_IO_PAD_CTRL_VOLTAGE_MODE                                                  (LAN80XX_BIT(7))
#define  LAN80XX_X_GLOBAL_IO_PAD_CTRL_VOLTAGE_MODE(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \details
 * 00 = 4ma
 * 01 = 8ma
 * 10 = 16ma
 * 11 = 20ma
 *
 * Field: ::LAN80XX_GLOBAL_IO_PAD_CTRL . DRIVE_STRENGTH
 */
#define  LAN80XX_F_GLOBAL_IO_PAD_CTRL_DRIVE_STRENGTH(x)                                             (LAN80XX_ENCODE_BITFIELD(x,5,2))
#define  LAN80XX_M_GLOBAL_IO_PAD_CTRL_DRIVE_STRENGTH                                                (LAN80XX_ENCODE_BITMASK(5,2))
#define  LAN80XX_X_GLOBAL_IO_PAD_CTRL_DRIVE_STRENGTH(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,5,2))

/**
 * \details
 * 1 = schmitt input enabled
 * 0 = schmitt input disabled
 *
 * Field: ::LAN80XX_GLOBAL_IO_PAD_CTRL . SCHMITT_IN_EN
 */
#define  LAN80XX_F_GLOBAL_IO_PAD_CTRL_SCHMITT_IN_EN(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_GLOBAL_IO_PAD_CTRL_SCHMITT_IN_EN                                                 (LAN80XX_BIT(4))
#define  LAN80XX_X_GLOBAL_IO_PAD_CTRL_SCHMITT_IN_EN(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \details
 * 1 = 40K ohms, weak
 * 0 = 10K ohms, medium
 *
 * Field: ::LAN80XX_GLOBAL_IO_PAD_CTRL . PUPD_STRENGTH
 */
#define  LAN80XX_F_GLOBAL_IO_PAD_CTRL_PUPD_STRENGTH(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_GLOBAL_IO_PAD_CTRL_PUPD_STRENGTH                                                 (LAN80XX_BIT(3))
#define  LAN80XX_X_GLOBAL_IO_PAD_CTRL_PUPD_STRENGTH(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \details
 * 0 = Function controlled
 * 1 = Override
 *
 * Field: ::LAN80XX_GLOBAL_IO_PAD_CTRL . PUPD_OVR
 */
#define  LAN80XX_F_GLOBAL_IO_PAD_CTRL_PUPD_OVR(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_GLOBAL_IO_PAD_CTRL_PUPD_OVR                                                      (LAN80XX_BIT(2))
#define  LAN80XX_X_GLOBAL_IO_PAD_CTRL_PUPD_OVR(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Only valid when PUPD_OVR is 1
 *
 * \details
 * 00 = no pull
 * 01 = pull up
 * 10 = pull down
 * 11 = illegal configuration
 *
 * Field: ::LAN80XX_GLOBAL_IO_PAD_CTRL . PUPD_EN
 */
#define  LAN80XX_F_GLOBAL_IO_PAD_CTRL_PUPD_EN(x)                                                    (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_GLOBAL_IO_PAD_CTRL_PUPD_EN                                                       (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_GLOBAL_IO_PAD_CTRL_PUPD_EN(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief LVDS Pad Control registers
 *
 * \details
 * Register: \a GLOBAL:PAD:LVDS_PAD_CTRL
 */
#define LAN80XX_GLOBAL_LVDS_PAD_CTRL                                                                (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x2d0))

/**
 * \brief
 * Input Hysteresis Enable
 *
 * \details
 * 1 = enabled
 * 0 = disabled
 *
 * Field: ::LAN80XX_GLOBAL_LVDS_PAD_CTRL . INPUT_HYS_ENABLE
 */
#define  LAN80XX_F_GLOBAL_LVDS_PAD_CTRL_INPUT_HYS_ENABLE(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_GLOBAL_LVDS_PAD_CTRL_INPUT_HYS_ENABLE                                            (LAN80XX_BIT(6))
#define  LAN80XX_X_GLOBAL_LVDS_PAD_CTRL_INPUT_HYS_ENABLE(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Receiver enable
 *
 * \details
 * 1 = disabled
 * 0 = enabled
 *
 * Field: ::LAN80XX_GLOBAL_LVDS_PAD_CTRL . RECEIVER_ENABLE
 */
#define  LAN80XX_F_GLOBAL_LVDS_PAD_CTRL_RECEIVER_ENABLE(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_GLOBAL_LVDS_PAD_CTRL_RECEIVER_ENABLE                                             (LAN80XX_BIT(5))
#define  LAN80XX_X_GLOBAL_LVDS_PAD_CTRL_RECEIVER_ENABLE(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * control the bias current of individual receiver stages
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_LVDS_PAD_CTRL . RECEIVE_BIAS
 */
#define  LAN80XX_F_GLOBAL_LVDS_PAD_CTRL_RECEIVE_BIAS(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_GLOBAL_LVDS_PAD_CTRL_RECEIVE_BIAS                                                (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_GLOBAL_LVDS_PAD_CTRL_RECEIVE_BIAS(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * Register Group: \a GLOBAL:TEST_STRAP_INFO
 *
 * Test Mode Straps
 */


/**
 * \brief Test Mode Strap register
 *
 * \details
 * Register: \a GLOBAL:TEST_STRAP_INFO:TEST_STRAP_READ
 */
#define LAN80XX_GLOBAL_TEST_STRAP_READ                                                              (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x380))

/**
 * \brief
 * This is not really a strap but rather the live pin value of TEST pin.
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEST_STRAP_READ . TEST_STRAP_TEST
 */
#define  LAN80XX_F_GLOBAL_TEST_STRAP_READ_TEST_STRAP_TEST(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_GLOBAL_TEST_STRAP_READ_TEST_STRAP_TEST                                           (LAN80XX_BIT(7))
#define  LAN80XX_X_GLOBAL_TEST_STRAP_READ_TEST_STRAP_TEST(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * The value of this register is the value of RCKOUTB pin latched on the
 * deassertion of RESET_N pin
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEST_STRAP_READ . TEST_STRAP_3
 */
#define  LAN80XX_F_GLOBAL_TEST_STRAP_READ_TEST_STRAP_3(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_GLOBAL_TEST_STRAP_READ_TEST_STRAP_3                                              (LAN80XX_BIT(3))
#define  LAN80XX_X_GLOBAL_TEST_STRAP_READ_TEST_STRAP_3(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * The value of this register is the value of RCKOUTA pin latched on the
 * deassertion of RESET_N pin
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEST_STRAP_READ . TEST_STRAP_2
 */
#define  LAN80XX_F_GLOBAL_TEST_STRAP_READ_TEST_STRAP_2(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_GLOBAL_TEST_STRAP_READ_TEST_STRAP_2                                              (LAN80XX_BIT(2))
#define  LAN80XX_X_GLOBAL_TEST_STRAP_READ_TEST_STRAP_2(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * The value of this register is the value of GPIO_33 pin latched on the
 * deassertion of RESET_N pin
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEST_STRAP_READ . TEST_STRAP_1
 */
#define  LAN80XX_F_GLOBAL_TEST_STRAP_READ_TEST_STRAP_1(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_GLOBAL_TEST_STRAP_READ_TEST_STRAP_1                                              (LAN80XX_BIT(1))
#define  LAN80XX_X_GLOBAL_TEST_STRAP_READ_TEST_STRAP_1(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * The value of this register is the value of GPIO_32 pin latched on the
 * deassertion of RESET_N pin
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TEST_STRAP_READ . TEST_STRAP_0
 */
#define  LAN80XX_F_GLOBAL_TEST_STRAP_READ_TEST_STRAP_0(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_GLOBAL_TEST_STRAP_READ_TEST_STRAP_0                                              (LAN80XX_BIT(0))
#define  LAN80XX_X_GLOBAL_TEST_STRAP_READ_TEST_STRAP_0(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a GLOBAL:GLB_SPARE_REG
 *
 * Global spare registers
 */


/**
 * \brief Spare Read Write registers
 *
 * \details
 * Register: \a GLOBAL:GLB_SPARE_REG:GLB_SPARE_RW_REG
 *
 * @param ri Register: GLB_SPARE_RW_REG (??), 0-3
 */
#define LAN80XX_GLOBAL_GLB_SPARE_RW_REG(ri)                                                         (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x3f0 + (ri)))

/**
 * \brief
 * Global spare read/write registers
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_GLB_SPARE_RW_REG . GLB_SPARE_RW_REG
 */
#define  LAN80XX_F_GLOBAL_GLB_SPARE_RW_REG_GLB_SPARE_RW_REG(x)                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_GLB_SPARE_RW_REG_GLB_SPARE_RW_REG                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_GLB_SPARE_RW_REG_GLB_SPARE_RW_REG(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Spare Status registers
 *
 * \details
 * Register: \a GLOBAL:GLB_SPARE_REG:GLB_SPARE_STS_REG
 *
 * @param ri Register: GLB_SPARE_STS_REG (??), 0-1
 */
#define LAN80XX_GLOBAL_GLB_SPARE_STS_REG(ri)                                                        (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x3f4 + (ri)))

/**
 * \brief
 * Global spare read-only registers
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_GLB_SPARE_STS_REG . GLB_SPARE_STS_REG
 */
#define  LAN80XX_F_GLOBAL_GLB_SPARE_STS_REG_GLB_SPARE_STS_REG(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_GLB_SPARE_STS_REG_GLB_SPARE_STS_REG                                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_GLB_SPARE_STS_REG_GLB_SPARE_STS_REG(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a GLOBAL:FPGA_REVISION
 *
 * FPGA Revision
 */


/**
 * \brief Type A FPGA Revision Register
 *
 * \details
 * Type A FPGA Revision Register
 *
 * Register: \a GLOBAL:FPGA_REVISION:TYPE_A_FPGA_REV_H_REG
 */
#define LAN80XX_GLOBAL_TYPE_A_FPGA_REV_H_REG                                                        (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x3f8))

/**
 * \brief
 * Type A FPGA revision id[31:16]
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TYPE_A_FPGA_REV_H_REG . TYPE_A_FPGA_REV_H
 */
#define  LAN80XX_F_GLOBAL_TYPE_A_FPGA_REV_H_REG_TYPE_A_FPGA_REV_H(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_TYPE_A_FPGA_REV_H_REG_TYPE_A_FPGA_REV_H                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_TYPE_A_FPGA_REV_H_REG_TYPE_A_FPGA_REV_H(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Type A FPGA Revision Register
 *
 * \details
 * Type A FPGA Revision Register
 *
 * Register: \a GLOBAL:FPGA_REVISION:TYPE_A_FPGA_REV_L_REG
 */
#define LAN80XX_GLOBAL_TYPE_A_FPGA_REV_L_REG                                                        (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x3f9))

/**
 * \brief
 * Type A FPGA revision id[15:0]
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TYPE_A_FPGA_REV_L_REG . TYPE_A_FPGA_REV_L
 */
#define  LAN80XX_F_GLOBAL_TYPE_A_FPGA_REV_L_REG_TYPE_A_FPGA_REV_L(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_TYPE_A_FPGA_REV_L_REG_TYPE_A_FPGA_REV_L                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_TYPE_A_FPGA_REV_L_REG_TYPE_A_FPGA_REV_L(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Type B FPGA Revision Register
 *
 * \details
 * Type B FPGA Revision Register
 *
 * Register: \a GLOBAL:FPGA_REVISION:TYPE_B_FPGA_REV_H_REG
 */
#define LAN80XX_GLOBAL_TYPE_B_FPGA_REV_H_REG                                                        (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x3fa))

/**
 * \brief
 * Type B FPGA revision id[31:16]
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TYPE_B_FPGA_REV_H_REG . TYPE_B_FPGA_REV_H
 */
#define  LAN80XX_F_GLOBAL_TYPE_B_FPGA_REV_H_REG_TYPE_B_FPGA_REV_H(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_TYPE_B_FPGA_REV_H_REG_TYPE_B_FPGA_REV_H                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_TYPE_B_FPGA_REV_H_REG_TYPE_B_FPGA_REV_H(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Type B FPGA Revision Register
 *
 * \details
 * Type B FPGA Revision Register
 *
 * Register: \a GLOBAL:FPGA_REVISION:TYPE_B_FPGA_REV_L_REG
 */
#define LAN80XX_GLOBAL_TYPE_B_FPGA_REV_L_REG                                                        (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x3fb))

/**
 * \brief
 * Type B FPGA revision id[15:0]
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TYPE_B_FPGA_REV_L_REG . TYPE_B_FPGA_REV_L
 */
#define  LAN80XX_F_GLOBAL_TYPE_B_FPGA_REV_L_REG_TYPE_B_FPGA_REV_L(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_TYPE_B_FPGA_REV_L_REG_TYPE_B_FPGA_REV_L                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_TYPE_B_FPGA_REV_L_REG_TYPE_B_FPGA_REV_L(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Type C FPGA Revision Register
 *
 * \details
 * Type C FPGA Revision Register
 *
 * Register: \a GLOBAL:FPGA_REVISION:TYPE_C_FPGA_REV_H_REG
 */
#define LAN80XX_GLOBAL_TYPE_C_FPGA_REV_H_REG                                                        (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x3fc))

/**
 * \brief
 * Type C FPGA revision id[31:16]
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TYPE_C_FPGA_REV_H_REG . TYPE_C_FPGA_REV_H
 */
#define  LAN80XX_F_GLOBAL_TYPE_C_FPGA_REV_H_REG_TYPE_C_FPGA_REV_H(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_TYPE_C_FPGA_REV_H_REG_TYPE_C_FPGA_REV_H                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_TYPE_C_FPGA_REV_H_REG_TYPE_C_FPGA_REV_H(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Type C FPGA Revision Register
 *
 * \details
 * Type C FPGA Revision Register
 *
 * Register: \a GLOBAL:FPGA_REVISION:TYPE_C_FPGA_REV_L_REG
 */
#define LAN80XX_GLOBAL_TYPE_C_FPGA_REV_L_REG                                                        (LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 0, 0x3fd))

/**
 * \brief
 * Type C FPGA revision id[15:0]
 *
 * \details
 * Field: ::LAN80XX_GLOBAL_TYPE_C_FPGA_REV_L_REG . TYPE_C_FPGA_REV_L
 */
#define  LAN80XX_F_GLOBAL_TYPE_C_FPGA_REV_L_REG_TYPE_C_FPGA_REV_L(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_GLOBAL_TYPE_C_FPGA_REV_L_REG_TYPE_C_FPGA_REV_L                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_GLOBAL_TYPE_C_FPGA_REV_L_REG_TYPE_C_FPGA_REV_L(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


#endif /* _LAN80XX_MALIBU25G_REGS_GLOBAL_H_ */
