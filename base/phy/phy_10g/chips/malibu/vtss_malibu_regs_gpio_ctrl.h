// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_GPIO_CTRL_H_
#define _VTSS_MALIBU_REGS_GPIO_CTRL_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a GPIO_CTRL
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a GPIO_CTRL:GPIO_CFG_STAT
 *
 * Configuration and status of chip level GPIO
 */


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_CFG1
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CFG1  VTSS_IOREG(0x1e, 1, 0xf200)

/** 
 * \brief
 * Output enable mask for GPIO[39:32].	Each bit corresponds to the output
 * enable of that GPIO.  e.g. bit 1 -> GPIO[33]
 *
 * \details 
 * 0 = Output is not enabled (output buffer is tri-stated)
 * 1 = Output is enabled (output is either pull low or is tri-stated
 * depending on what is driving it)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CFG1 . GPIO_OUT1_EN
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CFG1_GPIO_OUT1_EN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CFG1_GPIO_OUT1_EN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CFG1_GPIO_OUT1_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_CFG0
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CFG0  VTSS_IOREG(0x1e, 1, 0xf201)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_INV_CFG1
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_INV_CFG1  VTSS_IOREG(0x1e, 1, 0xf202)

/** 
 * \brief
 * Output invert for GPIO[39:32].  Each bit corresponds to the output
 * invert of that GPIO.  e.g. bit 1 -> GPIO[33]
 *
 * \details 
 * 0 = Output is not inverted (output reflects state of selected source)
 * 1 = Output is inverted
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_INV_CFG1 . GPIO_OUT1_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_INV_CFG1_GPIO_OUT1_INV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_INV_CFG1_GPIO_OUT1_INV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_INV_CFG1_GPIO_OUT1_INV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_INV_CFG0
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_INV_CFG0  VTSS_IOREG(0x1e, 1, 0xf203)


/** 
 * \brief Current status of GPIO inputs
 *
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_STAT1
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_STAT1  VTSS_IOREG(0x1e, 1, 0xf204)

/** 
 * \brief
 * Input state of each GPIO input [39:32]
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_STAT1 . GPIO_IN1_STAT
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_STAT1_GPIO_IN1_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_STAT1_GPIO_IN1_STAT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_STAT1_GPIO_IN1_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Current status of GPIO inputs
 *
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_STAT0
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_STAT0  VTSS_IOREG(0x1e, 1, 0xf205)


/** 
 * \brief Current status of GPIO outputs
 *
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_STAT1
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_STAT1  VTSS_IOREG(0x1e, 1, 0xf206)

/** 
 * \brief
 * Input state of each GPIO output [39:32]
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_STAT1 . GPIO_OUT1_STAT
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_STAT1_GPIO_OUT1_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_STAT1_GPIO_OUT1_STAT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_STAT1_GPIO_OUT1_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Current status of GPIO outputs
 *
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_STAT0
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_STAT0  VTSS_IOREG(0x1e, 1, 0xf207)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_CHANGE1
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CHANGE1  VTSS_IOREG(0x1e, 1, 0xf208)

/** 
 * \brief
 * GPIO input state change detection for each GPIO[39:32]
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CHANGE1 . GPIO_IN1_CHG_STICKY
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CHANGE1_GPIO_IN1_CHG_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CHANGE1_GPIO_IN1_CHG_STICKY     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CHANGE1_GPIO_IN1_CHG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_CHANGE0
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_CHANGE0  VTSS_IOREG(0x1e, 1, 0xf209)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_MASK1
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_MASK1  VTSS_IOREG(0x1e, 1, 0xf20a)

/** 
 * \details 
 * 0 = Corresponding GPIO_IN1_CHG_STICKY will not propogate to INTR
 * 1 = Corresponding GPIO_IN1_CHG_STICKY will propogate to INTR
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_MASK1 . GPIO_IN1_INTR_EN
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_MASK1_GPIO_IN1_INTR_EN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_MASK1_GPIO_IN1_INTR_EN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_MASK1_GPIO_IN1_INTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_MASK0
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_MASK0  VTSS_IOREG(0x1e, 1, 0xf20b)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_0
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_0  VTSS_IOREG(0x1e, 1, 0xf20c)

/** 
 * \brief
 * Selects the source for GPIO_0 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_0 . GPIO_0_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_0_GPIO_0_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_0_GPIO_0_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_0_GPIO_0_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_1
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_1  VTSS_IOREG(0x1e, 1, 0xf20d)

/** 
 * \brief
 * Selects the source for GPIO_1 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_1 . GPIO_1_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_1_GPIO_1_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_1_GPIO_1_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_1_GPIO_1_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_2
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_2  VTSS_IOREG(0x1e, 1, 0xf20e)

/** 
 * \brief
 * Selects the source for GPIO_2 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_2 . GPIO_2_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_2_GPIO_2_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_2_GPIO_2_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_2_GPIO_2_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_3
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_3  VTSS_IOREG(0x1e, 1, 0xf20f)

/** 
 * \brief
 * Selects the source for GPIO_3 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_3 . GPIO_3_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_3_GPIO_3_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_3_GPIO_3_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_3_GPIO_3_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_4
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_4  VTSS_IOREG(0x1e, 1, 0xf210)

/** 
 * \brief
 * Selects the source for GPIO_4 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_4 . GPIO_4_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_4_GPIO_4_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_4_GPIO_4_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_4_GPIO_4_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_5
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_5  VTSS_IOREG(0x1e, 1, 0xf211)

/** 
 * \brief
 * Selects the source for GPIO_5 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_5 . GPIO_5_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_5_GPIO_5_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_5_GPIO_5_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_5_GPIO_5_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_6
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_6  VTSS_IOREG(0x1e, 1, 0xf212)

/** 
 * \brief
 * Selects the source for GPIO_6 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_6 . GPIO_6_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_6_GPIO_6_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_6_GPIO_6_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_6_GPIO_6_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_7
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_7  VTSS_IOREG(0x1e, 1, 0xf213)

/** 
 * \brief
 * Selects the source for GPIO_7 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_7 . GPIO_7_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_7_GPIO_7_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_7_GPIO_7_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_7_GPIO_7_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_8
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_8  VTSS_IOREG(0x1e, 1, 0xf214)

/** 
 * \brief
 * Selects the source for GPIO_8 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_8 . GPIO_8_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_8_GPIO_8_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_8_GPIO_8_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_8_GPIO_8_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_9
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_9  VTSS_IOREG(0x1e, 1, 0xf215)

/** 
 * \brief
 * Selects the source for GPIO_9 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_9 . GPIO_9_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_9_GPIO_9_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_9_GPIO_9_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_9_GPIO_9_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_10
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_10  VTSS_IOREG(0x1e, 1, 0xf216)

/** 
 * \brief
 * Selects the source for GPIO_10 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_10 . GPIO_10_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_10_GPIO_10_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_10_GPIO_10_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_10_GPIO_10_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_11
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_11  VTSS_IOREG(0x1e, 1, 0xf217)

/** 
 * \brief
 * Selects the source for GPIO_11 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_11 . GPIO_11_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_11_GPIO_11_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_11_GPIO_11_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_11_GPIO_11_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_12
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_12  VTSS_IOREG(0x1e, 1, 0xf218)

/** 
 * \brief
 * Selects the source for GPIO_12 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_12 . GPIO_12_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_12_GPIO_12_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_12_GPIO_12_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_12_GPIO_12_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_13
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_13  VTSS_IOREG(0x1e, 1, 0xf219)

/** 
 * \brief
 * Selects the source for GPIO_13 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_13 . GPIO_13_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_13_GPIO_13_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_13_GPIO_13_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_13_GPIO_13_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_14
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_14  VTSS_IOREG(0x1e, 1, 0xf21a)

/** 
 * \brief
 * Selects the source for GPIO_14 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_14 . GPIO_14_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_14_GPIO_14_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_14_GPIO_14_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_14_GPIO_14_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_15
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_15  VTSS_IOREG(0x1e, 1, 0xf21b)

/** 
 * \brief
 * Selects the source for GPIO_15 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_15 . GPIO_15_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_15_GPIO_15_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_15_GPIO_15_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_15_GPIO_15_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_16
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_16  VTSS_IOREG(0x1e, 1, 0xf21c)

/** 
 * \brief
 * Selects the source for GPIO_16 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_16 . GPIO_16_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_16_GPIO_16_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_16_GPIO_16_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_16_GPIO_16_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_17
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_17  VTSS_IOREG(0x1e, 1, 0xf21d)

/** 
 * \brief
 * Selects the source for GPIO_17 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_17 . GPIO_17_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_17_GPIO_17_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_17_GPIO_17_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_17_GPIO_17_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_18
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_18  VTSS_IOREG(0x1e, 1, 0xf21e)

/** 
 * \brief
 * Selects the source for GPIO_18 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_18 . GPIO_18_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_18_GPIO_18_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_18_GPIO_18_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_18_GPIO_18_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_19
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_19  VTSS_IOREG(0x1e, 1, 0xf21f)

/** 
 * \brief
 * Selects the source for GPIO_19 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_19 . GPIO_19_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_19_GPIO_19_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_19_GPIO_19_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_19_GPIO_19_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_20
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_20  VTSS_IOREG(0x1e, 1, 0xf220)

/** 
 * \brief
 * Selects the source for GPIO_20 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_20 . GPIO_20_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_20_GPIO_20_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_20_GPIO_20_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_20_GPIO_20_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_21
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_21  VTSS_IOREG(0x1e, 1, 0xf221)

/** 
 * \brief
 * Selects the source for GPIO_21 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_21 . GPIO_21_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_21_GPIO_21_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_21_GPIO_21_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_21_GPIO_21_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_22
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_22  VTSS_IOREG(0x1e, 1, 0xf222)

/** 
 * \brief
 * Selects the source for GPIO_22 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_22 . GPIO_22_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_22_GPIO_22_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_22_GPIO_22_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_22_GPIO_22_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_23
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_23  VTSS_IOREG(0x1e, 1, 0xf223)

/** 
 * \brief
 * Selects the source for GPIO_23 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_23 . GPIO_23_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_23_GPIO_23_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_23_GPIO_23_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_23_GPIO_23_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_24
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_24  VTSS_IOREG(0x1e, 1, 0xf224)

/** 
 * \brief
 * Selects the source for GPIO_24 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_24 . GPIO_24_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_24_GPIO_24_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_24_GPIO_24_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_24_GPIO_24_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_25
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_25  VTSS_IOREG(0x1e, 1, 0xf225)

/** 
 * \brief
 * Selects the source for GPIO_25 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_25 . GPIO_25_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_25_GPIO_25_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_25_GPIO_25_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_25_GPIO_25_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_26
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_26  VTSS_IOREG(0x1e, 1, 0xf226)

/** 
 * \brief
 * Selects the source for GPIO_26 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_26 . GPIO_26_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_26_GPIO_26_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_26_GPIO_26_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_26_GPIO_26_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_27
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_27  VTSS_IOREG(0x1e, 1, 0xf227)

/** 
 * \brief
 * Selects the source for GPIO_27 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_27 . GPIO_27_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_27_GPIO_27_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_27_GPIO_27_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_27_GPIO_27_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_28
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_28  VTSS_IOREG(0x1e, 1, 0xf228)

/** 
 * \brief
 * Selects the source for GPIO_28 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_28 . GPIO_28_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_28_GPIO_28_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_28_GPIO_28_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_28_GPIO_28_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_29
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_29  VTSS_IOREG(0x1e, 1, 0xf229)

/** 
 * \brief
 * Selects the source for GPIO_29 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_29 . GPIO_29_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_29_GPIO_29_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_29_GPIO_29_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_29_GPIO_29_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_30
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_30  VTSS_IOREG(0x1e, 1, 0xf22a)

/** 
 * \brief
 * Selects the source for GPIO_30 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_30 . GPIO_30_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_30_GPIO_30_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_30_GPIO_30_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_30_GPIO_30_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_31
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_31  VTSS_IOREG(0x1e, 1, 0xf22b)

/** 
 * \brief
 * Selects the source for GPIO_31 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_31 . GPIO_31_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_31_GPIO_31_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_31_GPIO_31_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_31_GPIO_31_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_32
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_32  VTSS_IOREG(0x1e, 1, 0xf22c)

/** 
 * \brief
 * Selects the source for GPIO_32 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_32 . GPIO_32_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_32_GPIO_32_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_32_GPIO_32_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_32_GPIO_32_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_33
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_33  VTSS_IOREG(0x1e, 1, 0xf22d)

/** 
 * \brief
 * Selects the source for GPIO_33 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_33 . GPIO_33_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_33_GPIO_33_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_33_GPIO_33_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_33_GPIO_33_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_34
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_34  VTSS_IOREG(0x1e, 1, 0xf22e)

/** 
 * \brief
 * Selects the source for GPIO_34 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_34 . GPIO_34_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_34_GPIO_34_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_34_GPIO_34_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_34_GPIO_34_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_35
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_35  VTSS_IOREG(0x1e, 1, 0xf22f)

/** 
 * \brief
 * Selects the source for GPIO_35 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_35 . GPIO_35_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_35_GPIO_35_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_35_GPIO_35_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_35_GPIO_35_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_36
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_36  VTSS_IOREG(0x1e, 1, 0xf230)

/** 
 * \brief
 * Selects the source for GPIO_36 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_36 . GPIO_36_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_36_GPIO_36_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_36_GPIO_36_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_36_GPIO_36_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_37
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_37  VTSS_IOREG(0x1e, 1, 0xf231)

/** 
 * \brief
 * Selects the source for GPIO_37 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_37 . GPIO_37_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_37_GPIO_37_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_37_GPIO_37_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_37_GPIO_37_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_38
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_38  VTSS_IOREG(0x1e, 1, 0xf232)

/** 
 * \brief
 * Selects the source for GPIO_38 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_38 . GPIO_38_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_38_GPIO_38_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_38_GPIO_38_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_38_GPIO_38_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_CFG_39
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_39  VTSS_IOREG(0x1e, 1, 0xf233)

/** 
 * \brief
 * Selects the source for GPIO_39 output
 *
 * \details 
 * 
 * 0 = GPIO output 0 from channel 0
 * 1 = GPIO output 1 from channel 0
 * 2 = GPIO output 2 from channel 0
 * 3 = GPIO output 3 from channel 0
 * 4 = GPIO output 4 from channel 0
 * 5 = GPIO output 5 from channel 0
 * 6 = GPIO output 6 from channel 0
 * 7 = GPIO output 7 from channel 0
 * 8 = GPIO output 0 from channel 1
 * 9 = GPIO output 1 from channel 1
 * 10 = GPIO output 2 from channel 1
 * 11 = GPIO output 3 from channel 1
 * 12 = GPIO output 4 from channel 1
 * 13 = GPIO output 5 from channel 1
 * 14 = GPIO output 6 from channel 1
 * 15 = GPIO output 7 from channel 1
 * 16 = GPIO output 0 from channel 2
 * 17 = GPIO output 1 from channel 2
 * 18 = GPIO output 2 from channel 2
 * 19 = GPIO output 3 from channel 2
 * 20 = GPIO output 4 from channel 2
 * 21 = GPIO output 5 from channel 2
 * 22 = GPIO output 6 from channel 2
 * 23 = GPIO output 7 from channel 2
 * 24 = GPIO output 0 from channel 3
 * 25 = GPIO output 1 from channel 3
 * 26 = GPIO output 2 from channel 3
 * 27 = GPIO output 3 from channel 3
 * 28 = GPIO output 4 from channel 3
 * 29 = GPIO output 5 from channel 3
 * 30 = GPIO output 6 from channel 3
 * 31 = GPIO output 7 from channel 3
 * 32 = TX Enable for channel 0
 * 33 = TX Enable for channel 1
 * 34 = TX Enable for channel 2
 * 35 = TX Enable for channel 3
 * 36 = PPS_0 from ip1588
 * 37 = PPS_1 from ip1588
 * 38 = PPS_2 from ip1588
 * 39 = PPS_3 from ip1588
 * 40 = PLL5G Lock status from Line PLL
 * 41 = PLL5G Lock status from Host PLL
 * 42 = RCOMP Busy
 * 43 = N/A
 * 44 = N/A
 * 45 = N/A
 * 46 = N/A
 * 47 = N/A
 * 48 = Channel interrupt 0 from channel 0
 * 49 = Channel interrupt 1 from channel 0
 * 50 = Channel interrupt 0 from channel 1
 * 51 = Channel interrupt 1 from channel 1
 * 52 = Channel interrupt 0 from channel 2
 * 53 = Channel interrupt 1 from channel 2
 * 54 = Channel interrupt 0 from channel 3
 * 55 = Channel interrupt 1 from channel 3
 * 56 = Interrupt from ip1588 channel 0
 * 57 = Interrupt from ip1588 channel 1
 * 58 = Interrupt from ip1588 channel 2
 * 59 = Interrupt from ip1588 channel 3
 * 60 = Timestamp FIFO !empty from ip1588 channel 0
 * 61 = Timestamp FIFO !empty from ip1588 channel 1
 * 62 = Timestamp FIFO !empty from ip1588 channel 2
 * 63 = Timestamp FIFO !empty from ip1588 channel 3
 * 64 = Aggregated interrupt 0
 * 65 = Aggregated interrupt 1
 * 66 = Aggregated interrupt 2
 * 67 = Aggregated interrupt 3
 * 68 = Interrupt from pll 0
 * 69 = Interrupt from pll 1
 * 70 = I2C Slave SDA
 * 71 = Cross connect interrupt
 * 72 = LED Blinker
 * 73-127 = Drive low (or high by also setting output INV bit)
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_39 . GPIO_39_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_39_GPIO_39_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_39_GPIO_39_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_GPIO_OUT_CFG_39_GPIO_39_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH0_LINE_LOPC_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_LINE_LOPC_CFG  VTSS_IOREG(0x1e, 1, 0xf234)

/** 
 * \brief
 * Set high to invert sense of LINE_LOPC
 *
 * \details 
 * 0 = Use GPIO state as is
 * 1 = Invert GPIO input state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_LINE_LOPC_CFG . CH0_LINE_LOPC_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_LINE_LOPC_CFG_CH0_LINE_LOPC_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which CPIO is used for CH0 LINE_LOPC input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_LINE_LOPC_CFG . CH0_LINE_LOPC_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_LINE_LOPC_CFG_CH0_LINE_LOPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH0_LINE_LOPC_CFG_CH0_LINE_LOPC_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH0_LINE_LOPC_CFG_CH0_LINE_LOPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH1_LINE_LOPC_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_LINE_LOPC_CFG  VTSS_IOREG(0x1e, 1, 0xf235)

/** 
 * \brief
 * Set high to invert sense of LINE_LOPC
 *
 * \details 
 * 0 = Use GPIO state as is
 * 1 = Invert GPIO input state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_LINE_LOPC_CFG . CH1_LINE_LOPC_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_LINE_LOPC_CFG_CH1_LINE_LOPC_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which CPIO is used for CH1 LINE_LOPC input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_LINE_LOPC_CFG . CH1_LINE_LOPC_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_LINE_LOPC_CFG_CH1_LINE_LOPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH1_LINE_LOPC_CFG_CH1_LINE_LOPC_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH1_LINE_LOPC_CFG_CH1_LINE_LOPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH2_LINE_LOPC_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_LINE_LOPC_CFG  VTSS_IOREG(0x1e, 1, 0xf236)

/** 
 * \brief
 * Set high to invert sense of LINE_LOPC
 *
 * \details 
 * 0 = Use GPIO state as is
 * 1 = Invert GPIO input state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_LINE_LOPC_CFG . CH2_LINE_LOPC_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_LINE_LOPC_CFG_CH2_LINE_LOPC_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which CPIO is used for CH2 LINE_LOPC input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_LINE_LOPC_CFG . CH2_LINE_LOPC_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_LINE_LOPC_CFG_CH2_LINE_LOPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH2_LINE_LOPC_CFG_CH2_LINE_LOPC_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH2_LINE_LOPC_CFG_CH2_LINE_LOPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH3_LINE_LOPC_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_LINE_LOPC_CFG  VTSS_IOREG(0x1e, 1, 0xf237)

/** 
 * \brief
 * Set high to invert sense of LINE_LOPC
 *
 * \details 
 * 0 = Use GPIO state as is
 * 1 = Invert GPIO input state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_LINE_LOPC_CFG . CH3_LINE_LOPC_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_LINE_LOPC_CFG_CH3_LINE_LOPC_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which CPIO is used for CH3 LINE_LOPC input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_LINE_LOPC_CFG . CH3_LINE_LOPC_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_LINE_LOPC_CFG_CH3_LINE_LOPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH3_LINE_LOPC_CFG_CH3_LINE_LOPC_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH3_LINE_LOPC_CFG_CH3_LINE_LOPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH0_HOST_LOPC_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_HOST_LOPC_CFG  VTSS_IOREG(0x1e, 1, 0xf238)

/** 
 * \brief
 * Set high to invert sense of HOST_LOPC
 *
 * \details 
 * 0 = Use GPIO state as is
 * 1 = Invert GPIO input state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_HOST_LOPC_CFG . CH0_HOST_LOPC_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_HOST_LOPC_CFG_CH0_HOST_LOPC_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which CPIO is used for CH0 HOST_LOPC input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_HOST_LOPC_CFG . CH0_HOST_LOPC_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_HOST_LOPC_CFG_CH0_HOST_LOPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH0_HOST_LOPC_CFG_CH0_HOST_LOPC_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH0_HOST_LOPC_CFG_CH0_HOST_LOPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH1_HOST_LOPC_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_HOST_LOPC_CFG  VTSS_IOREG(0x1e, 1, 0xf239)

/** 
 * \brief
 * Set high to invert sense of HOST_LOPC
 *
 * \details 
 * 0 = Use GPIO state as is
 * 1 = Invert GPIO input state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_HOST_LOPC_CFG . CH1_HOST_LOPC_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_HOST_LOPC_CFG_CH1_HOST_LOPC_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which CPIO is used for CH1 HOST_LOPC input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_HOST_LOPC_CFG . CH1_HOST_LOPC_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_HOST_LOPC_CFG_CH1_HOST_LOPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH1_HOST_LOPC_CFG_CH1_HOST_LOPC_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH1_HOST_LOPC_CFG_CH1_HOST_LOPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH2_HOST_LOPC_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_HOST_LOPC_CFG  VTSS_IOREG(0x1e, 1, 0xf23a)

/** 
 * \brief
 * Set high to invert sense of HOST_LOPC
 *
 * \details 
 * 0 = Use GPIO state as is
 * 1 = Invert GPIO input state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_HOST_LOPC_CFG . CH2_HOST_LOPC_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_HOST_LOPC_CFG_CH2_HOST_LOPC_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which CPIO is used for CH2 HOST_LOPC input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_HOST_LOPC_CFG . CH2_HOST_LOPC_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_HOST_LOPC_CFG_CH2_HOST_LOPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH2_HOST_LOPC_CFG_CH2_HOST_LOPC_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH2_HOST_LOPC_CFG_CH2_HOST_LOPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH3_HOST_LOPC_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_HOST_LOPC_CFG  VTSS_IOREG(0x1e, 1, 0xf23b)

/** 
 * \brief
 * Set high to invert sense of HOST_LOPC
 *
 * \details 
 * 0 = Use GPIO state as is
 * 1 = Invert GPIO input state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_HOST_LOPC_CFG . CH3_HOST_LOPC_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_HOST_LOPC_CFG_CH3_HOST_LOPC_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which CPIO is used for CH3 HOST_LOPC input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_HOST_LOPC_CFG . CH3_HOST_LOPC_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_HOST_LOPC_CFG_CH3_HOST_LOPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH3_HOST_LOPC_CFG_CH3_HOST_LOPC_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH3_HOST_LOPC_CFG_CH3_HOST_LOPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH0_TOSI_SDAT_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_TOSI_SDAT_CFG  VTSS_IOREG(0x1e, 1, 0xf23c)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_TOSI_SDAT_CFG . CH0_TOSI_SDAT_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_TOSI_SDAT_CFG_CH0_TOSI_SDAT_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH0 TOSI SDAT input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_TOSI_SDAT_CFG . CH0_TOSI_SDAT_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_TOSI_SDAT_CFG_CH0_TOSI_SDAT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH0_TOSI_SDAT_CFG_CH0_TOSI_SDAT_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH0_TOSI_SDAT_CFG_CH0_TOSI_SDAT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH1_TOSI_SDAT_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_TOSI_SDAT_CFG  VTSS_IOREG(0x1e, 1, 0xf23d)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_TOSI_SDAT_CFG . CH1_TOSI_SDAT_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_TOSI_SDAT_CFG_CH1_TOSI_SDAT_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH1 TOSI SDAT input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_TOSI_SDAT_CFG . CH1_TOSI_SDAT_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_TOSI_SDAT_CFG_CH1_TOSI_SDAT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH1_TOSI_SDAT_CFG_CH1_TOSI_SDAT_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH1_TOSI_SDAT_CFG_CH1_TOSI_SDAT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH2_TOSI_SDAT_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_TOSI_SDAT_CFG  VTSS_IOREG(0x1e, 1, 0xf23e)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_TOSI_SDAT_CFG . CH2_TOSI_SDAT_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_TOSI_SDAT_CFG_CH2_TOSI_SDAT_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH2 TOSI SDAT input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_TOSI_SDAT_CFG . CH2_TOSI_SDAT_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_TOSI_SDAT_CFG_CH2_TOSI_SDAT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH2_TOSI_SDAT_CFG_CH2_TOSI_SDAT_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH2_TOSI_SDAT_CFG_CH2_TOSI_SDAT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH3_TOSI_SDAT_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_TOSI_SDAT_CFG  VTSS_IOREG(0x1e, 1, 0xf23f)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_TOSI_SDAT_CFG . CH3_TOSI_SDAT_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_TOSI_SDAT_CFG_CH3_TOSI_SDAT_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH3 TOSI SDAT input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_TOSI_SDAT_CFG . CH3_TOSI_SDAT_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_TOSI_SDAT_CFG_CH3_TOSI_SDAT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH3_TOSI_SDAT_CFG_CH3_TOSI_SDAT_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH3_TOSI_SDAT_CFG_CH3_TOSI_SDAT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH0_I2C_MST_DATA_IN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_DATA_IN_CFG  VTSS_IOREG(0x1e, 1, 0xf240)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_DATA_IN_CFG . CH0_I2C_MST_DATA_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_DATA_IN_CFG_CH0_I2C_MST_DATA_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH0 I2C_MST_DATA_IN input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_DATA_IN_CFG . CH0_I2C_MST_DATA_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_DATA_IN_CFG_CH0_I2C_MST_DATA_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_DATA_IN_CFG_CH0_I2C_MST_DATA_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_DATA_IN_CFG_CH0_I2C_MST_DATA_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH1_I2C_MST_DATA_IN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_DATA_IN_CFG  VTSS_IOREG(0x1e, 1, 0xf241)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_DATA_IN_CFG . CH1_I2C_MST_DATA_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_DATA_IN_CFG_CH1_I2C_MST_DATA_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH1 I2C_MST_DATA_IN input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_DATA_IN_CFG . CH1_I2C_MST_DATA_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_DATA_IN_CFG_CH1_I2C_MST_DATA_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_DATA_IN_CFG_CH1_I2C_MST_DATA_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_DATA_IN_CFG_CH1_I2C_MST_DATA_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH2_I2C_MST_DATA_IN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_DATA_IN_CFG  VTSS_IOREG(0x1e, 1, 0xf242)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_DATA_IN_CFG . CH2_I2C_MST_DATA_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_DATA_IN_CFG_CH2_I2C_MST_DATA_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH2 I2C_MST_DATA_IN input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_DATA_IN_CFG . CH2_I2C_MST_DATA_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_DATA_IN_CFG_CH2_I2C_MST_DATA_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_DATA_IN_CFG_CH2_I2C_MST_DATA_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_DATA_IN_CFG_CH2_I2C_MST_DATA_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH3_I2C_MST_DATA_IN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_DATA_IN_CFG  VTSS_IOREG(0x1e, 1, 0xf243)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_DATA_IN_CFG . CH3_I2C_MST_DATA_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_DATA_IN_CFG_CH3_I2C_MST_DATA_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH3 I2C_MST_DATA_IN input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_DATA_IN_CFG . CH3_I2C_MST_DATA_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_DATA_IN_CFG_CH3_I2C_MST_DATA_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_DATA_IN_CFG_CH3_I2C_MST_DATA_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_DATA_IN_CFG_CH3_I2C_MST_DATA_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH0_I2C_MST_CLK_IN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_CLK_IN_CFG  VTSS_IOREG(0x1e, 1, 0xf244)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_CLK_IN_CFG . CH0_I2C_MST_CLK_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_CLK_IN_CFG_CH0_I2C_MST_CLK_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH0 I2C_MST_CLK_IN input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_CLK_IN_CFG . CH0_I2C_MST_CLK_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_CLK_IN_CFG_CH0_I2C_MST_CLK_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_CLK_IN_CFG_CH0_I2C_MST_CLK_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH0_I2C_MST_CLK_IN_CFG_CH0_I2C_MST_CLK_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH1_I2C_MST_CLK_IN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_CLK_IN_CFG  VTSS_IOREG(0x1e, 1, 0xf245)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_CLK_IN_CFG . CH1_I2C_MST_CLK_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_CLK_IN_CFG_CH1_I2C_MST_CLK_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH1 I2C_MST_CLK_IN input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_CLK_IN_CFG . CH1_I2C_MST_CLK_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_CLK_IN_CFG_CH1_I2C_MST_CLK_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_CLK_IN_CFG_CH1_I2C_MST_CLK_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH1_I2C_MST_CLK_IN_CFG_CH1_I2C_MST_CLK_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH2_I2C_MST_CLK_IN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_CLK_IN_CFG  VTSS_IOREG(0x1e, 1, 0xf246)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_CLK_IN_CFG . CH2_I2C_MST_CLK_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_CLK_IN_CFG_CH2_I2C_MST_CLK_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH2 I2C_MST_CLK_IN input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_CLK_IN_CFG . CH2_I2C_MST_CLK_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_CLK_IN_CFG_CH2_I2C_MST_CLK_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_CLK_IN_CFG_CH2_I2C_MST_CLK_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH2_I2C_MST_CLK_IN_CFG_CH2_I2C_MST_CLK_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:CH3_I2C_MST_CLK_IN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_CLK_IN_CFG  VTSS_IOREG(0x1e, 1, 0xf247)

/** 
 * \brief
 * Set high to invert state of selected GPIO
 *
 * \details 
 * 0 = Use GPIO as is
 * 1 = Use inverted GPIO state
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_CLK_IN_CFG . CH3_I2C_MST_CLK_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_CLK_IN_CFG_CH3_I2C_MST_CLK_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input routes to CH3 I2C_MST_CLK_IN input
 *
 * \details 
 * 39:0 -> GPIO[39:0]
 * 63:40 -> 0
 *
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_CLK_IN_CFG . CH3_I2C_MST_CLK_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_CLK_IN_CFG_CH3_I2C_MST_CLK_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_CLK_IN_CFG_CH3_I2C_MST_CLK_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_CH3_I2C_MST_CLK_IN_CFG_CH3_I2C_MST_CLK_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:EXP4_EXT_IN_CFG
 *
 * @param ri Register: EXP4_EXT_IN_CFG, 0-7
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_EXP4_EXT_IN_CFG(ri)  VTSS_IOREG(0x1e, 1, 0xf248 | (ri))

/** 
 * \brief
 * Set high to invert selected GPIO
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_EXP4_EXT_IN_CFG . EXP4_EXT_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_EXP4_EXT_IN_CFG_EXP4_EXT_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input maps to the corresponding cross connect ext_in
 * pin
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_EXP4_EXT_IN_CFG . EXP4_EXT_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_EXP4_EXT_IN_CFG_EXP4_EXT_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_EXP4_EXT_IN_CFG_EXP4_EXT_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_EXP4_EXT_IN_CFG_EXP4_EXT_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:AS_EXT_IN_CFG
 *
 * @param ri Register: AS_EXT_IN_CFG, 0-7
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_AS_EXT_IN_CFG(ri)  VTSS_IOREG(0x1e, 1, 0xf250 | (ri))

/** 
 * \brief
 * Set high to invert selected GPIO
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_AS_EXT_IN_CFG . AS_EXT_IN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_AS_EXT_IN_CFG_AS_EXT_IN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input maps to the corresponding clock auto-squelch
 * ext_in pin
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_AS_EXT_IN_CFG . AS_EXT_IN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_AS_EXT_IN_CFG_AS_EXT_IN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_AS_EXT_IN_CFG_AS_EXT_IN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_AS_EXT_IN_CFG_AS_EXT_IN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:I2C_CLKIN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_I2C_CLKIN_CFG  VTSS_IOREG(0x1e, 1, 0xf258)

/** 
 * \brief
 * Set high to invert selected GPIO
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_I2C_CLKIN_CFG . I2C_CLKIN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_I2C_CLKIN_CFG_I2C_CLKIN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input maps to the I2C_CLKIN input
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_I2C_CLKIN_CFG . I2C_CLKIN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_I2C_CLKIN_CFG_I2C_CLKIN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_I2C_CLKIN_CFG_I2C_CLKIN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_I2C_CLKIN_CFG_I2C_CLKIN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:I2C_DATAIN_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_I2C_DATAIN_CFG  VTSS_IOREG(0x1e, 1, 0xf259)

/** 
 * \brief
 * Set high to invert selected GPIO
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_I2C_DATAIN_CFG . I2C_DATAIN_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_I2C_DATAIN_CFG_I2C_DATAIN_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input maps to the I2C_DATAIN input
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_I2C_DATAIN_CFG . I2C_DATAIN_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_I2C_DATAIN_CFG_I2C_DATAIN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_I2C_DATAIN_CFG_I2C_DATAIN_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_I2C_DATAIN_CFG_I2C_DATAIN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:PMTICK_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_PMTICK_CFG  VTSS_IOREG(0x1e, 1, 0xf25a)

/** 
 * \brief
 * Set high to invert selected GPIO
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_PMTICK_CFG . PMTICK_INV
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_PMTICK_CFG_PMTICK_INV  VTSS_BIT(8)

/** 
 * \brief
 * Selects which GPIO input maps to the PMTICK input
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_PMTICK_CFG . PMTICK_SEL
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_PMTICK_CFG_PMTICK_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_PMTICK_CFG_PMTICK_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_PMTICK_CFG_PMTICK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:BLINK_CFG
 */
#define VTSS_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG  VTSS_IOREG(0x1e, 1, 0xf25b)

/** 
 * \brief
 * Time LED stays high (in 2*ms)
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG . BLINKER_HIGH_TIME
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG_BLINKER_HIGH_TIME(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG_BLINKER_HIGH_TIME     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG_BLINKER_HIGH_TIME(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Time LED is low (in 2*ms).  Disable blink circuit by setting to 0.
 *
 * \details 
 * Field: VTSS_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG . BLINKER_LOW_TIME
 */
#define  VTSS_F_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG_BLINKER_LOW_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG_BLINKER_LOW_TIME     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GPIO_CTRL_GPIO_CFG_STAT_BLINK_CFG_BLINKER_LOW_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a GPIO_CTRL:INTR_CFG_STAT
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a GPIO_CTRL:INTR_CFG_STAT:INTR_SRC_EN
 *
 * @param ri Register: INTR_SRC_EN, 0-3
 */
#define VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN(ri)  VTSS_IOREG(0x1e, 1, 0xf25c | (ri))

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . GPIO_INTR_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_GPIO_INTR_EN  VTSS_BIT(20)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CLK_MUX_INTR_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CLK_MUX_INTR_EN  VTSS_BIT(19)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . EXP4_INTR_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_EXP4_INTR_EN  VTSS_BIT(18)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . LCPLL_1_INTR_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_LCPLL_1_INTR_EN  VTSS_BIT(17)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . LCPLL_0_INTR_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_LCPLL_0_INTR_EN  VTSS_BIT(16)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . IP1588_1_INTR3_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_IP1588_1_INTR3_EN  VTSS_BIT(15)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . IP1588_1_INTR2_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_IP1588_1_INTR2_EN  VTSS_BIT(14)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . IP1588_1_INTR1_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_IP1588_1_INTR1_EN  VTSS_BIT(13)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . IP1588_1_INTR0_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_IP1588_1_INTR0_EN  VTSS_BIT(12)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . IP1588_0_INTR3_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_IP1588_0_INTR3_EN  VTSS_BIT(11)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . IP1588_0_INTR2_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_IP1588_0_INTR2_EN  VTSS_BIT(10)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . IP1588_0_INTR1_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_IP1588_0_INTR1_EN  VTSS_BIT(9)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . IP1588_0_INTR0_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_IP1588_0_INTR0_EN  VTSS_BIT(8)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CH3_INTR1_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CH3_INTR1_EN  VTSS_BIT(7)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CH3_INTR0_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CH3_INTR0_EN  VTSS_BIT(6)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CH2_INTR1_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CH2_INTR1_EN  VTSS_BIT(5)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CH2_INTR0_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CH2_INTR0_EN  VTSS_BIT(4)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CH1_INTR1_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CH1_INTR1_EN  VTSS_BIT(3)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CH1_INTR0_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CH1_INTR0_EN  VTSS_BIT(2)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CH0_INTR1_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CH0_INTR1_EN  VTSS_BIT(1)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN . CH0_INTR0_EN
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN_CH0_INTR0_EN  VTSS_BIT(0)


/** 
 * \details
 * Register: \a GPIO_CTRL:INTR_CFG_STAT:INTR_STAT
 *
 * @param ri Register: INTR_STAT, 0-3
 */
#define VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT(ri)  VTSS_IOREG(0x1e, 1, 0xf260 | (ri))

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . GPIO_INTR_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_GPIO_INTR_STAT  VTSS_BIT(20)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CLK_MUX_INTR_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CLK_MUX_INTR_STAT  VTSS_BIT(19)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . EXP4_INTR_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_EXP4_INTR_STAT  VTSS_BIT(18)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . LCPLL_1_INTR_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_LCPLL_1_INTR_STAT  VTSS_BIT(17)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . LCPLL_0_INTR_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_LCPLL_0_INTR_STAT  VTSS_BIT(16)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . IP1588_1_INTR3_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_IP1588_1_INTR3_STAT  VTSS_BIT(15)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . IP1588_1_INTR2_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_IP1588_1_INTR2_STAT  VTSS_BIT(14)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . IP1588_1_INTR1_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_IP1588_1_INTR1_STAT  VTSS_BIT(13)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . IP1588_1_INTR0_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_IP1588_1_INTR0_STAT  VTSS_BIT(12)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . IP1588_0_INTR3_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_IP1588_0_INTR3_STAT  VTSS_BIT(11)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . IP1588_0_INTR2_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_IP1588_0_INTR2_STAT  VTSS_BIT(10)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . IP1588_0_INTR1_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_IP1588_0_INTR1_STAT  VTSS_BIT(9)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . IP1588_0_INTR0_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_IP1588_0_INTR0_STAT  VTSS_BIT(8)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CH3_INTR1_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CH3_INTR1_STAT  VTSS_BIT(7)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CH3_INTR0_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CH3_INTR0_STAT  VTSS_BIT(6)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CH2_INTR1_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CH2_INTR1_STAT  VTSS_BIT(5)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CH2_INTR0_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CH2_INTR0_STAT  VTSS_BIT(4)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CH1_INTR1_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CH1_INTR1_STAT  VTSS_BIT(3)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CH1_INTR0_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CH1_INTR0_STAT  VTSS_BIT(2)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CH0_INTR1_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CH0_INTR1_STAT  VTSS_BIT(1)

/** 
 * \details 
 * Field: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT . CH0_INTR0_STAT
 */
#define  VTSS_F_GPIO_CTRL_INTR_CFG_STAT_INTR_STAT_CH0_INTR0_STAT  VTSS_BIT(0)


#endif /* _VTSS_MALIBU_REGS_GPIO_CTRL_H_ */
