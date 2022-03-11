/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_ip/v_reddydev.priv.p31g_ip.vp_model/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/vspec1_def.xml
// Register File Name  : VSPEC1
// Register File Title : Vendor Specific 1 Device for MMD=0x1E
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _VSPEC1_H
#define _VSPEC1_H

//! \defgroup VSPEC1 Register File VSPEC1 - Vendor Specific 1 Device for MMD=0x1E
//! @{

//! Base Address of VSPEC1
#define VSPEC1_MODULE_BASE 0x03C00000u

//! \defgroup VSPEC1_LEDC Register VSPEC1_LEDC - LEDs Complex Group Configuration (Register 30.0)
//! @{

//! Register Offset (relative)
#define VSPEC1_LEDC 0x0
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_LEDC 0x03C00000u

//! Register Reset Value
#define VSPEC1_LEDC_RST 0x37C5u

//! Field NACS - Inverse of SCAN Function
#define VSPEC1_LEDC_NACS_POS 0
//! Field NACS - Inverse of SCAN Function
#define VSPEC1_LEDC_NACS_MASK 0x7u
//! Constant NONE - No Function
#define CONST_VSPEC1_LEDC_NACS_NONE 0x0
//! Constant LINK - Complex function enabled when link is up
#define CONST_VSPEC1_LEDC_NACS_LINK 0x1
//! Constant PDOWN - Complex function enabled when device is powered-down
#define CONST_VSPEC1_LEDC_NACS_PDOWN 0x2
//! Constant EEE - Complex function enabled when device is in EEE mode
#define CONST_VSPEC1_LEDC_NACS_EEE 0x3
//! Constant ANEG - Complex function enabled when auto-negotiation is running
#define CONST_VSPEC1_LEDC_NACS_ANEG 0x4
//! Constant ABIST - Complex function enabled when analog self-test is running
#define CONST_VSPEC1_LEDC_NACS_ABIST 0x5
//! Constant CDIAG - Complex function enabled when cable diagnostics are running
#define CONST_VSPEC1_LEDC_NACS_CDIAG 0x6
//! Constant TEST - Complex function enabled when test mode is running
#define CONST_VSPEC1_LEDC_NACS_TEST 0x7

//! Field SBF - Slow Blink Frequency
#define VSPEC1_LEDC_SBF_POS 4
//! Field SBF - Slow Blink Frequency
#define VSPEC1_LEDC_SBF_MASK 0x30u
//! Constant F02HZ - 2 Hz blinking frequency
#define CONST_VSPEC1_LEDC_SBF_F02HZ 0x0
//! Constant F04HZ - 4 Hz blinking frequency
#define CONST_VSPEC1_LEDC_SBF_F04HZ 0x1
//! Constant F08HZ - 8 Hz blinking frequency
#define CONST_VSPEC1_LEDC_SBF_F08HZ 0x2
//! Constant F16HZ - 16 Hz blinking frequency
#define CONST_VSPEC1_LEDC_SBF_F16HZ 0x3

//! Field FBF - Fast Blink Frequency
#define VSPEC1_LEDC_FBF_POS 6
//! Field FBF - Fast Blink Frequency
#define VSPEC1_LEDC_FBF_MASK 0xC0u
//! Constant F02HZ - 2 Hz blinking frequency
#define CONST_VSPEC1_LEDC_FBF_F02HZ 0x0
//! Constant F04HZ - 4 Hz blinking frequency
#define CONST_VSPEC1_LEDC_FBF_F04HZ 0x1
//! Constant F08HZ - 8 Hz blinking frequency
#define CONST_VSPEC1_LEDC_FBF_F08HZ 0x2
//! Constant F16HZ - 16 Hz blinking frequency
#define CONST_VSPEC1_LEDC_FBF_F16HZ 0x3

//! Field CBLINK - Complex Blinking Configuration
#define VSPEC1_LEDC_CBLINK_POS 8
//! Field CBLINK - Complex Blinking Configuration
#define VSPEC1_LEDC_CBLINK_MASK 0x700u
//! Constant NONE - No Function
#define CONST_VSPEC1_LEDC_CBLINK_NONE 0x0
//! Constant LINK - Complex function enabled when link is up
#define CONST_VSPEC1_LEDC_CBLINK_LINK 0x1
//! Constant PDOWN - Complex function enabled when device is powered-down
#define CONST_VSPEC1_LEDC_CBLINK_PDOWN 0x2
//! Constant EEE - Complex function enabled when device is in EEE mode
#define CONST_VSPEC1_LEDC_CBLINK_EEE 0x3
//! Constant ANEG - Complex function enabled when auto-negotiation is running
#define CONST_VSPEC1_LEDC_CBLINK_ANEG 0x4
//! Constant ABIST - Complex function enabled when analog self-test is running
#define CONST_VSPEC1_LEDC_CBLINK_ABIST 0x5
//! Constant CDIAG - Complex function enabled when cable diagnostics are running
#define CONST_VSPEC1_LEDC_CBLINK_CDIAG 0x6
//! Constant TEST - Complex function enabled when test mode is running
#define CONST_VSPEC1_LEDC_CBLINK_TEST 0x7

//! Field SCAN - Complex SCAN Configuration
#define VSPEC1_LEDC_SCAN_POS 11
//! Field SCAN - Complex SCAN Configuration
#define VSPEC1_LEDC_SCAN_MASK 0x3800u
//! Constant NONE - No Function
#define CONST_VSPEC1_LEDC_SCAN_NONE 0x0
//! Constant LINK - Complex function enabled when link is up
#define CONST_VSPEC1_LEDC_SCAN_LINK 0x1
//! Constant PDOWN - Complex function enabled when device is powered-down
#define CONST_VSPEC1_LEDC_SCAN_PDOWN 0x2
//! Constant EEE - Complex function enabled when device is in EEE mode
#define CONST_VSPEC1_LEDC_SCAN_EEE 0x3
//! Constant ANEG - Complex function enabled when auto-negotiation is running
#define CONST_VSPEC1_LEDC_SCAN_ANEG 0x4
//! Constant ABIST - Complex function enabled when analog self-test is running
#define CONST_VSPEC1_LEDC_SCAN_ABIST 0x5
//! Constant CDIAG - Complex function enabled when cable diagnostics are running
#define CONST_VSPEC1_LEDC_SCAN_CDIAG 0x6
//! Constant TEST - Complex function enabled when test mode is running
#define CONST_VSPEC1_LEDC_SCAN_TEST 0x7

//! @}

//! \defgroup VSPEC1_LED0 Register VSPEC1_LED0 - Configuration for LED Pin 0 (Register 30.1)
//! @{

//! Register Offset (relative)
#define VSPEC1_LED0 0x2
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_LED0 0x03C00002u

//! Register Reset Value
#define VSPEC1_LED0_RST 0x0310u

//! Field BLINKF - Fast Blinking Configuration
#define VSPEC1_LED0_BLINKF_POS 0
//! Field BLINKF - Fast Blinking Configuration
#define VSPEC1_LED0_BLINKF_MASK 0xFu
//! Constant NONE - No Active
#define CONST_VSPEC1_LED0_BLINKF_NONE 0x0
//! Constant LINK10 - Blink when Link is 10 Mbit/s
#define CONST_VSPEC1_LED0_BLINKF_LINK10 0x1
//! Constant LINK100 - Blink when Link is 100 Mbit/s
#define CONST_VSPEC1_LED0_BLINKF_LINK100 0x2
//! Constant LINK1000 - Blink when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED0_BLINKF_LINK1000 0x4
//! Constant LINK2500 - Blink when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED0_BLINKF_LINK2500 0x8

//! Field CON - Constant On Configuration
#define VSPEC1_LED0_CON_POS 4
//! Field CON - Constant On Configuration
#define VSPEC1_LED0_CON_MASK 0xF0u
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED0_CON_NONE 0x0
//! Constant LINK10 - On when Link is 10 Mbit/s
#define CONST_VSPEC1_LED0_CON_LINK10 0x1
//! Constant LINK100 - On when Link is 100 Mbit/s
#define CONST_VSPEC1_LED0_CON_LINK100 0x2
//! Constant LINK1000 - On when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED0_CON_LINK1000 0x4
//! Constant LINK2500 - On when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED0_CON_LINK2500 0x8

//! Field PULSE - Pulsing Configuration
#define VSPEC1_LED0_PULSE_POS 8
//! Field PULSE - Pulsing Configuration
#define VSPEC1_LED0_PULSE_MASK 0xF00u
//! Constant NONE - No pulsing
#define CONST_VSPEC1_LED0_PULSE_NONE 0x0
//! Constant TXACT - Transmit activity
#define CONST_VSPEC1_LED0_PULSE_TXACT 0x1
//! Constant RXACT - Receive activity
#define CONST_VSPEC1_LED0_PULSE_RXACT 0x2
//! Constant COL - Collision
#define CONST_VSPEC1_LED0_PULSE_COL 0x4
//! Constant NO_CON - Constant ON behavior is switched off
#define CONST_VSPEC1_LED0_PULSE_NO_CON 0x8

//! Field BLINKS - Slow Blinking Configuration
#define VSPEC1_LED0_BLINKS_POS 12
//! Field BLINKS - Slow Blinking Configuration
#define VSPEC1_LED0_BLINKS_MASK 0xF000u
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED0_BLINKS_NONE 0x0
//! Constant LINK10 - Blink when Link is 10 Mbit/s
#define CONST_VSPEC1_LED0_BLINKS_LINK10 0x1
//! Constant LINK100 - Blink when Link is 100 Mbit/s
#define CONST_VSPEC1_LED0_BLINKS_LINK100 0x2
//! Constant LINK1000 - Blink when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED0_BLINKS_LINK1000 0x4
//! Constant LINK2500 - Blink when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED0_BLINKS_LINK2500 0x8

//! @}

//! \defgroup VSPEC1_LED1 Register VSPEC1_LED1 - Configuration for LED Pin 1 (Register 30.2)
//! @{

//! Register Offset (relative)
#define VSPEC1_LED1 0x4
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_LED1 0x03C00004u

//! Register Reset Value
#define VSPEC1_LED1_RST 0x0320u

//! Field BLINKF - Fast Blinking Configuration
#define VSPEC1_LED1_BLINKF_POS 0
//! Field BLINKF - Fast Blinking Configuration
#define VSPEC1_LED1_BLINKF_MASK 0xFu
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED1_BLINKF_NONE 0x0
//! Constant LINK10 - Blink when Link is 10 Mbit/s
#define CONST_VSPEC1_LED1_BLINKF_LINK10 0x1
//! Constant LINK100 - Blink when Link is 100 Mbit/s
#define CONST_VSPEC1_LED1_BLINKF_LINK100 0x2
//! Constant LINK1000 - Blink when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED1_BLINKF_LINK1000 0x4
//! Constant LINK2500 - Blink when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED1_BLINKF_LINK2500 0x8

//! Field CON - Constant On Configuration
#define VSPEC1_LED1_CON_POS 4
//! Field CON - Constant On Configuration
#define VSPEC1_LED1_CON_MASK 0xF0u
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED1_CON_NONE 0x0
//! Constant LINK10 - On when Link is 10 Mbit/s
#define CONST_VSPEC1_LED1_CON_LINK10 0x1
//! Constant LINK100 - On when Link is 100 Mbit/s
#define CONST_VSPEC1_LED1_CON_LINK100 0x2
//! Constant LINK1000 - On when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED1_CON_LINK1000 0x4
//! Constant LINK2500 - On when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED1_CON_LINK2500 0x8

//! Field PULSE - Pulsing Configuration
#define VSPEC1_LED1_PULSE_POS 8
//! Field PULSE - Pulsing Configuration
#define VSPEC1_LED1_PULSE_MASK 0xF00u
//! Constant NONE - No pulsing
#define CONST_VSPEC1_LED1_PULSE_NONE 0x0
//! Constant TXACT - Transmit activity
#define CONST_VSPEC1_LED1_PULSE_TXACT 0x1
//! Constant RXACT - Receive activity
#define CONST_VSPEC1_LED1_PULSE_RXACT 0x2
//! Constant COL - Collision
#define CONST_VSPEC1_LED1_PULSE_COL 0x4
//! Constant NO_CON - Constant ON behavior is switched off
#define CONST_VSPEC1_LED1_PULSE_NO_CON 0x8

//! Field BLINKS - Slow Blinking Configuration
#define VSPEC1_LED1_BLINKS_POS 12
//! Field BLINKS - Slow Blinking Configuration
#define VSPEC1_LED1_BLINKS_MASK 0xF000u
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED1_BLINKS_NONE 0x0
//! Constant LINK10 - Blink when Link is 10 Mbit/s
#define CONST_VSPEC1_LED1_BLINKS_LINK10 0x1
//! Constant LINK100 - Blink when Link is 100 Mbit/s
#define CONST_VSPEC1_LED1_BLINKS_LINK100 0x2
//! Constant LINK1000 - Blink when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED1_BLINKS_LINK1000 0x4
//! Constant LINK2500 - Blink when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED1_BLINKS_LINK2500 0x8

//! @}

//! \defgroup VSPEC1_LED2 Register VSPEC1_LED2 - Configuration for LED Pin 2 (Register 30.3)
//! @{

//! Register Offset (relative)
#define VSPEC1_LED2 0x6
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_LED2 0x03C00006u

//! Register Reset Value
#define VSPEC1_LED2_RST 0x0340u

//! Field BLINKF - Fast Blinking Configuration
#define VSPEC1_LED2_BLINKF_POS 0
//! Field BLINKF - Fast Blinking Configuration
#define VSPEC1_LED2_BLINKF_MASK 0xFu
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED2_BLINKF_NONE 0x0
//! Constant LINK10 - Blink when Link is 10 Mbit/s
#define CONST_VSPEC1_LED2_BLINKF_LINK10 0x1
//! Constant LINK100 - Blink when Link is 100 Mbit/s
#define CONST_VSPEC1_LED2_BLINKF_LINK100 0x2
//! Constant LINK1000 - Blink when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED2_BLINKF_LINK1000 0x4
//! Constant LINK2500 - Blink when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED2_BLINKF_LINK2500 0x8

//! Field CON - Constant On Configuration
#define VSPEC1_LED2_CON_POS 4
//! Field CON - Constant On Configuration
#define VSPEC1_LED2_CON_MASK 0xF0u
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED2_CON_NONE 0x0
//! Constant LINK10 - On when Link is 10 Mbit/s
#define CONST_VSPEC1_LED2_CON_LINK10 0x1
//! Constant LINK100 - On when Link is 100 Mbit/s
#define CONST_VSPEC1_LED2_CON_LINK100 0x2
//! Constant LINK1000 - On when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED2_CON_LINK1000 0x4
//! Constant LINK2500 - On when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED2_CON_LINK2500 0x8

//! Field PULSE - Pulsing Configuration
#define VSPEC1_LED2_PULSE_POS 8
//! Field PULSE - Pulsing Configuration
#define VSPEC1_LED2_PULSE_MASK 0xF00u
//! Constant NONE - No pulsing
#define CONST_VSPEC1_LED2_PULSE_NONE 0x0
//! Constant TXACT - Transmit activity
#define CONST_VSPEC1_LED2_PULSE_TXACT 0x1
//! Constant RXACT - Receive activity
#define CONST_VSPEC1_LED2_PULSE_RXACT 0x2
//! Constant COL - Collision
#define CONST_VSPEC1_LED2_PULSE_COL 0x4
//! Constant NO_CON - Constant ON behavior is switched off
#define CONST_VSPEC1_LED2_PULSE_NO_CON 0x8

//! Field BLINKS - Slow Blinking Configuration
#define VSPEC1_LED2_BLINKS_POS 12
//! Field BLINKS - Slow Blinking Configuration
#define VSPEC1_LED2_BLINKS_MASK 0xF000u
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED2_BLINKS_NONE 0x0
//! Constant LINK10 - Blink when Link is 10 Mbit/s
#define CONST_VSPEC1_LED2_BLINKS_LINK10 0x1
//! Constant LINK100 - Blink when Link is 100 Mbit/s
#define CONST_VSPEC1_LED2_BLINKS_LINK100 0x2
//! Constant LINK1000 - Blink when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED2_BLINKS_LINK1000 0x4
//! Constant LINK2500 - Blink when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED2_BLINKS_LINK2500 0x8

//! @}

//! \defgroup VSPEC1_LED3 Register VSPEC1_LED3 - Configuration for LED Pin 3 (Register 30.4)
//! @{

//! Register Offset (relative)
#define VSPEC1_LED3 0x8
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_LED3 0x03C00008u

//! Register Reset Value
#define VSPEC1_LED3_RST 0x0380u

//! Field BLINKF - Fast Blinking Configuration
#define VSPEC1_LED3_BLINKF_POS 0
//! Field BLINKF - Fast Blinking Configuration
#define VSPEC1_LED3_BLINKF_MASK 0xFu
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED3_BLINKF_NONE 0x0
//! Constant LINK10 - Blink when Link is 10 Mbit/s
#define CONST_VSPEC1_LED3_BLINKF_LINK10 0x1
//! Constant LINK100 - Blink when Link is 100 Mbit/s
#define CONST_VSPEC1_LED3_BLINKF_LINK100 0x2
//! Constant LINK1000 - Blink when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED3_BLINKF_LINK1000 0x4
//! Constant LINK2500 - Blink when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED3_BLINKF_LINK2500 0x8

//! Field CON - Constant On Configuration
#define VSPEC1_LED3_CON_POS 4
//! Field CON - Constant On Configuration
#define VSPEC1_LED3_CON_MASK 0xF0u
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED3_CON_NONE 0x0
//! Constant LINK10 - On when Link is 10 Mbit/s
#define CONST_VSPEC1_LED3_CON_LINK10 0x1
//! Constant LINK100 - On when Link is 100 Mbit/s
#define CONST_VSPEC1_LED3_CON_LINK100 0x2
//! Constant LINK1000 - On when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED3_CON_LINK1000 0x4
//! Constant LINK2500 - On when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED3_CON_LINK2500 0x8

//! Field PULSE - Pulsing Configuration
#define VSPEC1_LED3_PULSE_POS 8
//! Field PULSE - Pulsing Configuration
#define VSPEC1_LED3_PULSE_MASK 0xF00u
//! Constant NONE - No pulsing
#define CONST_VSPEC1_LED3_PULSE_NONE 0x0
//! Constant TXACT - Transmit activity
#define CONST_VSPEC1_LED3_PULSE_TXACT 0x1
//! Constant RXACT - Receive activity
#define CONST_VSPEC1_LED3_PULSE_RXACT 0x2
//! Constant COL - Collision
#define CONST_VSPEC1_LED3_PULSE_COL 0x4
//! Constant NO_CON - Constant ON behavior is switched off
#define CONST_VSPEC1_LED3_PULSE_NO_CON 0x8

//! Field BLINKS - Slow Blinking Configuration
#define VSPEC1_LED3_BLINKS_POS 12
//! Field BLINKS - Slow Blinking Configuration
#define VSPEC1_LED3_BLINKS_MASK 0xF000u
//! Constant NONE - Not Active
#define CONST_VSPEC1_LED3_BLINKS_NONE 0x0
//! Constant LINK10 - Blink when Link is 10 Mbit/s
#define CONST_VSPEC1_LED3_BLINKS_LINK10 0x1
//! Constant LINK100 - Blink when Link is 100 Mbit/s
#define CONST_VSPEC1_LED3_BLINKS_LINK100 0x2
//! Constant LINK1000 - Blink when Link is 1000 Mbit/s
#define CONST_VSPEC1_LED3_BLINKS_LINK1000 0x4
//! Constant LINK2500 - Blink when Link is 2500 Mbit/s
#define CONST_VSPEC1_LED3_BLINKS_LINK2500 0x8

//! @}

//! \defgroup VSPEC1_MBOX_DATA Register VSPEC1_MBOX_DATA - Data for Mailbox ( r or w) (Register 30.5)
//! @{

//! Register Offset (relative)
#define VSPEC1_MBOX_DATA 0xA
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_MBOX_DATA 0x03C0000Au

//! Register Reset Value
#define VSPEC1_MBOX_DATA_RST 0x0000u

//! Field DATA - Mailbox Data
#define VSPEC1_MBOX_DATA_DATA_POS 0
//! Field DATA - Mailbox Data
#define VSPEC1_MBOX_DATA_DATA_MASK 0xFFFFu

//! @}

//! \defgroup VSPEC1_MBOX_ADDRLO Register VSPEC1_MBOX_ADDRLO - Lower 16 bits of the 24 bit AHB addresses (Register 30.6)
//! @{

//! Register Offset (relative)
#define VSPEC1_MBOX_ADDRLO 0xC
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_MBOX_ADDRLO 0x03C0000Cu

//! Register Reset Value
#define VSPEC1_MBOX_ADDRLO_RST 0x0000u

//! Field ADDRLO - MBOX Read Address
#define VSPEC1_MBOX_ADDRLO_ADDRLO_POS 0
//! Field ADDRLO - MBOX Read Address
#define VSPEC1_MBOX_ADDRLO_ADDRLO_MASK 0xFFFFu

//! @}

//! \defgroup VSPEC1_MBOX_CMD Register VSPEC1_MBOX_CMD - Mailbox CMD type and upper 8 bits of AHB address (Register 30.7)
//! @{

//! Register Offset (relative)
#define VSPEC1_MBOX_CMD 0xE
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_MBOX_CMD 0x03C0000Eu

//! Register Reset Value
#define VSPEC1_MBOX_CMD_RST 0x0000u

//! Field ADDRHI - AHB High Address or LLAPI ID.
#define VSPEC1_MBOX_CMD_ADDRHI_POS 0
//! Field ADDRHI - AHB High Address or LLAPI ID.
#define VSPEC1_MBOX_CMD_ADDRHI_MASK 0xFFu

//! Field CMD - MBOX Command type
#define VSPEC1_MBOX_CMD_CMD_POS 8
//! Field CMD - MBOX Command type
#define VSPEC1_MBOX_CMD_CMD_MASK 0xF00u
//! Constant READ - Cmd to read a data located at AHB address
#define CONST_VSPEC1_MBOX_CMD_CMD_READ 0x0
//! Constant WRITE - Cmd to write a data located at AHB address
#define CONST_VSPEC1_MBOX_CMD_CMD_WRITE 0x1
//! Constant LLAPI - Request a LLAPI function
#define CONST_VSPEC1_MBOX_CMD_CMD_LLAPI 0x2
//! Constant AFE - Enter AFE Custom Test mode
#define CONST_VSPEC1_MBOX_CMD_CMD_AFE 0x3
//! Constant READ32 - Cmd to read a 32 data located at AHB address
#define CONST_VSPEC1_MBOX_CMD_CMD_READ32 0x4
//! Constant WRITE32 - Cmd to write a 32 data located at AHB address
#define CONST_VSPEC1_MBOX_CMD_CMD_WRITE32 0x5
//! Constant PATCH_REQ - STA sends request to GPY for PATCH Transfer
#define CONST_VSPEC1_MBOX_CMD_CMD_PATCH_REQ 0x6
//! Constant PATCH_CHECK - STA indicates to GPY on completion of PATCH Transfer.
#define CONST_VSPEC1_MBOX_CMD_CMD_PATCH_CHECK 0x7
//! Constant PATCH_REQ_FAST - STA sends request to GPY to enter a FLASH PROGRAM Mode
#define CONST_VSPEC1_MBOX_CMD_CMD_PATCH_REQ_FAST 0x8

//! Field FAIL - PATCH FAIL Indicator
#define VSPEC1_MBOX_CMD_FAIL_POS 14
//! Field FAIL - PATCH FAIL Indicator
#define VSPEC1_MBOX_CMD_FAIL_MASK 0x4000u

//! Field READY - READY indicator
#define VSPEC1_MBOX_CMD_READY_POS 15
//! Field READY - READY indicator
#define VSPEC1_MBOX_CMD_READY_MASK 0x8000u

//! @}

//! \defgroup VSPEC1_SGMII_CTRL Register VSPEC1_SGMII_CTRL - Chip Level SGMII control register (Register 30.8)
//! @{

//! Register Offset (relative)
#define VSPEC1_SGMII_CTRL 0x10
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_SGMII_CTRL 0x03C00010u

//! Register Reset Value
#define VSPEC1_SGMII_CTRL_RST 0x34DAu

//! Field ANMODE - SGMII ANEG Mode
#define VSPEC1_SGMII_CTRL_ANMODE_POS 0
//! Field ANMODE - SGMII ANEG Mode
#define VSPEC1_SGMII_CTRL_ANMODE_MASK 0x3u
//! Constant RES - Reserved
#define CONST_VSPEC1_SGMII_CTRL_ANMODE_RES 0x0
//! Constant AN_1000BX - IEEE 1000Bx SGMII ANEG
#define CONST_VSPEC1_SGMII_CTRL_ANMODE_AN_1000BX 0x1
//! Constant AN_CIS_PHY - CISCO SGMII ANEG mode with GPY acting as a PHY
#define CONST_VSPEC1_SGMII_CTRL_ANMODE_AN_CIS_PHY 0x2
//! Constant AN_CIS_MAC - CISCO SGMII ANEG mode with GPY acting as a MAC
#define CONST_VSPEC1_SGMII_CTRL_ANMODE_AN_CIS_MAC 0x3

//! Field CFGDIR - SGMII Link configuration direction
#define VSPEC1_SGMII_CTRL_CFGDIR_POS 2
//! Field CFGDIR - SGMII Link configuration direction
#define VSPEC1_SGMII_CTRL_CFGDIR_MASK 0x4u
//! Constant TPI - SGMII takes configuration from TPI
#define CONST_VSPEC1_SGMII_CTRL_CFGDIR_TPI 0x0
//! Constant SGMII - SGMII configuration is forced to TPI
#define CONST_VSPEC1_SGMII_CTRL_CFGDIR_SGMII 0x1

//! Field USXGMII_REACH - USXGMII Tx and Rx configuration
#define VSPEC1_SGMII_CTRL_USXGMII_REACH_POS 3
//! Field USXGMII_REACH - USXGMII Tx and Rx configuration
#define VSPEC1_SGMII_CTRL_USXGMII_REACH_MASK 0x18u
//! Constant SHORT - Short Reach Configuration
#define CONST_VSPEC1_SGMII_CTRL_USXGMII_REACH_SHORT 0x0
//! Constant MEDIUM - Medium Reach Configuration
#define CONST_VSPEC1_SGMII_CTRL_USXGMII_REACH_MEDIUM 0x1
//! Constant LONG - Long Reach Configuration
#define CONST_VSPEC1_SGMII_CTRL_USXGMII_REACH_LONG 0x2
//! Constant CUSTOM - Custom Configuration
#define CONST_VSPEC1_SGMII_CTRL_USXGMII_REACH_CUSTOM 0x3

//! Field SGMII_FIXED2G5 - Force control the SGMII interface to remain in 2.5G speed or TPI link speed.
#define VSPEC1_SGMII_CTRL_SGMII_FIXED2G5_POS 5
//! Field SGMII_FIXED2G5 - Force control the SGMII interface to remain in 2.5G speed or TPI link speed.
#define VSPEC1_SGMII_CTRL_SGMII_FIXED2G5_MASK 0x20u
//! Constant NO_FORCE - SGMII speed is reconfigured by GPY based on TPI link speed.
#define CONST_VSPEC1_SGMII_CTRL_SGMII_FIXED2G5_NO_FORCE 0x0
//! Constant FORCE - SGMII speed is forced to 2.5G speed.
#define CONST_VSPEC1_SGMII_CTRL_SGMII_FIXED2G5_FORCE 0x1

//! Field SSM - Force Speed MSB
#define VSPEC1_SGMII_CTRL_SSM_POS 6
//! Field SSM - Force Speed MSB
#define VSPEC1_SGMII_CTRL_SSM_MASK 0x40u

//! Field EEE_CAP - EEE SGMII ANEG
#define VSPEC1_SGMII_CTRL_EEE_CAP_POS 7
//! Field EEE_CAP - EEE SGMII ANEG
#define VSPEC1_SGMII_CTRL_EEE_CAP_MASK 0x80u
//! Constant OFF - EEE is not advertised
#define CONST_VSPEC1_SGMII_CTRL_EEE_CAP_OFF 0x0
//! Constant ON - EEE is advertised
#define CONST_VSPEC1_SGMII_CTRL_EEE_CAP_ON 0x1

//! Field DPLX - Force Duplex
#define VSPEC1_SGMII_CTRL_DPLX_POS 8
//! Field DPLX - Force Duplex
#define VSPEC1_SGMII_CTRL_DPLX_MASK 0x100u
//! Constant OFF - Duplex Mode is OFF
#define CONST_VSPEC1_SGMII_CTRL_DPLX_OFF 0x0
//! Constant ON - Duplex Mode is set
#define CONST_VSPEC1_SGMII_CTRL_DPLX_ON 0x1

//! Field ANRS - Restart SGMII Aneg
#define VSPEC1_SGMII_CTRL_ANRS_POS 9
//! Field ANRS - Restart SGMII Aneg
#define VSPEC1_SGMII_CTRL_ANRS_MASK 0x200u
//! Constant NORMAL - Normal Operation SGMII
#define CONST_VSPEC1_SGMII_CTRL_ANRS_NORMAL 0x0
//! Constant RESTART - Restarts SGMII ANEG
#define CONST_VSPEC1_SGMII_CTRL_ANRS_RESTART 0x1

//! Field RXINV - Inversion of RX0_M and RX0_P
#define VSPEC1_SGMII_CTRL_RXINV_POS 10
//! Field RXINV - Inversion of RX0_M and RX0_P
#define VSPEC1_SGMII_CTRL_RXINV_MASK 0x400u
//! Constant NORMAL - No Inversion
#define CONST_VSPEC1_SGMII_CTRL_RXINV_NORMAL 0x0
//! Constant INVERT - Invert RX SGMII
#define CONST_VSPEC1_SGMII_CTRL_RXINV_INVERT 0x1

//! Field PD - Power Down
#define VSPEC1_SGMII_CTRL_PD_POS 11
//! Field PD - Power Down
#define VSPEC1_SGMII_CTRL_PD_MASK 0x800u
//! Constant OFF - Normal Operation SGMII
#define CONST_VSPEC1_SGMII_CTRL_PD_OFF 0x0
//! Constant ON - SGMII Power Down
#define CONST_VSPEC1_SGMII_CTRL_PD_ON 0x1

//! Field ANEN - ANEG Enable
#define VSPEC1_SGMII_CTRL_ANEN_POS 12
//! Field ANEN - ANEG Enable
#define VSPEC1_SGMII_CTRL_ANEN_MASK 0x1000u
//! Constant OFF - SGMII ANEG Disabled
#define CONST_VSPEC1_SGMII_CTRL_ANEN_OFF 0x0
//! Constant ON - SGMII ANEG Enabled
#define CONST_VSPEC1_SGMII_CTRL_ANEN_ON 0x1

//! Field SSL - Force Speed LSB
#define VSPEC1_SGMII_CTRL_SSL_POS 13
//! Field SSL - Force Speed LSB
#define VSPEC1_SGMII_CTRL_SSL_MASK 0x2000u

//! Field LB - Loopback
#define VSPEC1_SGMII_CTRL_LB_POS 14
//! Field LB - Loopback
#define VSPEC1_SGMII_CTRL_LB_MASK 0x4000u
//! Constant OFF - SGMII Loopback is disabled
#define CONST_VSPEC1_SGMII_CTRL_LB_OFF 0x0
//! Constant ON - SGMII Loopback Enabled
#define CONST_VSPEC1_SGMII_CTRL_LB_ON 0x1

//! Field RST - Reset SGMII
#define VSPEC1_SGMII_CTRL_RST_POS 15
//! Field RST - Reset SGMII
#define VSPEC1_SGMII_CTRL_RST_MASK 0x8000u
//! Constant NORM - Normal Operation SGMII
#define CONST_VSPEC1_SGMII_CTRL_RST_NORM 0x0
//! Constant RST - Reset SGMII
#define CONST_VSPEC1_SGMII_CTRL_RST_RST 0x1

//! @}

//! \defgroup VSPEC1_SGMII_STAT Register VSPEC1_SGMII_STAT - Chip Level SGMII status register (Register 30.9)
//! @{

//! Register Offset (relative)
#define VSPEC1_SGMII_STAT 0x12
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_SGMII_STAT 0x03C00012u

//! Register Reset Value
#define VSPEC1_SGMII_STAT_RST 0x0008u

//! Field DR - SGMII Data Rate
#define VSPEC1_SGMII_STAT_DR_POS 0
//! Field DR - SGMII Data Rate
#define VSPEC1_SGMII_STAT_DR_MASK 0x3u
//! Constant DR_10 - SGMII link rate is 10 Mbit/s
#define CONST_VSPEC1_SGMII_STAT_DR_DR_10 0x0
//! Constant DR_100 - SGMII link rate is 100 Mbit/s
#define CONST_VSPEC1_SGMII_STAT_DR_DR_100 0x1
//! Constant DR_1G - SGMII link rate is 1000 Mbit/s
#define CONST_VSPEC1_SGMII_STAT_DR_DR_1G 0x2
//! Constant DR_2G5 - SGMII link rate is 2500 Mbit/s
#define CONST_VSPEC1_SGMII_STAT_DR_DR_2G5 0x3

//! Field LS - Link Status
#define VSPEC1_SGMII_STAT_LS_POS 2
//! Field LS - Link Status
#define VSPEC1_SGMII_STAT_LS_MASK 0x4u
//! Constant INACTIVE - The link is down. No communication with link partner possible.
#define CONST_VSPEC1_SGMII_STAT_LS_INACTIVE 0x0
//! Constant ACTIVE - The link is up. Data communication with link partner is possible.
#define CONST_VSPEC1_SGMII_STAT_LS_ACTIVE 0x1

//! Field ANAB - Auto-Negotiation Ability
#define VSPEC1_SGMII_STAT_ANAB_POS 3
//! Field ANAB - Auto-Negotiation Ability
#define VSPEC1_SGMII_STAT_ANAB_MASK 0x8u
//! Constant DISABLED - PHY is not able to perform auto-negotiation
#define CONST_VSPEC1_SGMII_STAT_ANAB_DISABLED 0x0
//! Constant ENABLED - PHY is able to perform auto-negotiation
#define CONST_VSPEC1_SGMII_STAT_ANAB_ENABLED 0x1

//! Field RF - Remote Fault
#define VSPEC1_SGMII_STAT_RF_POS 4
//! Field RF - Remote Fault
#define VSPEC1_SGMII_STAT_RF_MASK 0x10u
//! Constant INACTIVE - No remote fault condition detected
#define CONST_VSPEC1_SGMII_STAT_RF_INACTIVE 0x0
//! Constant ACTIVE - Remote fault condition detected
#define CONST_VSPEC1_SGMII_STAT_RF_ACTIVE 0x1

//! Field ANOK - Auto-Negotiation Completed
#define VSPEC1_SGMII_STAT_ANOK_POS 5
//! Field ANOK - Auto-Negotiation Completed
#define VSPEC1_SGMII_STAT_ANOK_MASK 0x20u
//! Constant RUNNING - Auto-negotiation process is in progress or not started
#define CONST_VSPEC1_SGMII_STAT_ANOK_RUNNING 0x0
//! Constant COMPLETED - Auto-negotiation process is completed
#define CONST_VSPEC1_SGMII_STAT_ANOK_COMPLETED 0x1

//! Field MACSEC_CAP - MACSEC Capability in the product
#define VSPEC1_SGMII_STAT_MACSEC_CAP_POS 15
//! Field MACSEC_CAP - MACSEC Capability in the product
#define VSPEC1_SGMII_STAT_MACSEC_CAP_MASK 0x8000u
//! Constant DISABLED - Product is not MACSEC capable
#define CONST_VSPEC1_SGMII_STAT_MACSEC_CAP_DISABLED 0x0
//! Constant ENABLED - Product is MACSEC capable
#define CONST_VSPEC1_SGMII_STAT_MACSEC_CAP_ENABLED 0x1

//! @}

//! \defgroup VSPEC1_NBT_DS_CTRL Register VSPEC1_NBT_DS_CTRL - NBASE-T Downshift Control Register (Register 30.10)
//! @{

//! Register Offset (relative)
#define VSPEC1_NBT_DS_CTRL 0x14
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_NBT_DS_CTRL 0x03C00014u

//! Register Reset Value
#define VSPEC1_NBT_DS_CTRL_RST 0x0400u

//! Field NO_NRG_RST - Advertise all Speeds if No Energy Detected
#define VSPEC1_NBT_DS_CTRL_NO_NRG_RST_POS 0
//! Field NO_NRG_RST - Advertise all Speeds if No Energy Detected
#define VSPEC1_NBT_DS_CTRL_NO_NRG_RST_MASK 0x1u
//! Constant DISABLE - Do not reset speeds adv when no energy detected
#define CONST_VSPEC1_NBT_DS_CTRL_NO_NRG_RST_DISABLE 0x0
//! Constant ENABLE - Reset speed adv when no energy detected
#define CONST_VSPEC1_NBT_DS_CTRL_NO_NRG_RST_ENABLE 0x1

//! Field DOWNSHIFT_EN - NBASE-T Downshift Enable
#define VSPEC1_NBT_DS_CTRL_DOWNSHIFT_EN_POS 1
//! Field DOWNSHIFT_EN - NBASE-T Downshift Enable
#define VSPEC1_NBT_DS_CTRL_DOWNSHIFT_EN_MASK 0x2u
//! Constant DISABLE - Disable NBT downshift
#define CONST_VSPEC1_NBT_DS_CTRL_DOWNSHIFT_EN_DISABLE 0x0
//! Constant ENABLE - Enable NBT downshift
#define CONST_VSPEC1_NBT_DS_CTRL_DOWNSHIFT_EN_ENABLE 0x1

//! Field DOWNSHIFT_THR - NBASE-T Downshift Training Counter Threshold
#define VSPEC1_NBT_DS_CTRL_DOWNSHIFT_THR_POS 2
//! Field DOWNSHIFT_THR - NBASE-T Downshift Training Counter Threshold
#define VSPEC1_NBT_DS_CTRL_DOWNSHIFT_THR_MASK 0x7Cu

//! Field FORCE_RST - Force Reset of Downwshift Process
#define VSPEC1_NBT_DS_CTRL_FORCE_RST_POS 7
//! Field FORCE_RST - Force Reset of Downwshift Process
#define VSPEC1_NBT_DS_CTRL_FORCE_RST_MASK 0x80u

//! Field NRG_RST_CNT - Timer to Reset the Downshift process
#define VSPEC1_NBT_DS_CTRL_NRG_RST_CNT_POS 8
//! Field NRG_RST_CNT - Timer to Reset the Downshift process
#define VSPEC1_NBT_DS_CTRL_NRG_RST_CNT_MASK 0xFF00u

//! @}

//! \defgroup VSPEC1_NBT_DS_STA Register VSPEC1_NBT_DS_STA - NBASE-T Downshift Status Register (Register 30.11)
//! @{

//! Register Offset (relative)
#define VSPEC1_NBT_DS_STA 0x16
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_NBT_DS_STA 0x03C00016u

//! Register Reset Value
#define VSPEC1_NBT_DS_STA_RST 0x0000u

//! Field DOWNSHIFT_CNT - Training attempt counter
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_CNT_POS 0
//! Field DOWNSHIFT_CNT - Training attempt counter
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_CNT_MASK 0x1Fu

//! Field DOWNSHIFT_10G - Downshift 10G to lower speed
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_10G_POS 5
//! Field DOWNSHIFT_10G - Downshift 10G to lower speed
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_10G_MASK 0x20u

//! Field DOWNSHIFT_5G - Downshift 5G to lower speed
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_5G_POS 6
//! Field DOWNSHIFT_5G - Downshift 5G to lower speed
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_5G_MASK 0x40u

//! Field DOWNSHIFT_2G5 - Downshift from 2.5 G to lower speed
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_2G5_POS 7
//! Field DOWNSHIFT_2G5 - Downshift from 2.5 G to lower speed
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_2G5_MASK 0x80u

//! Field DOWNSHIFT_1G - Downshift from 1G to lower speed
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_1G_POS 8
//! Field DOWNSHIFT_1G - Downshift from 1G to lower speed
#define VSPEC1_NBT_DS_STA_DOWNSHIFT_1G_MASK 0x100u

//! @}

//! \defgroup VSPEC1_PM_CTRL Register VSPEC1_PM_CTRL - Packet Manager Control (Register 30.12)
//! @{

//! Register Offset (relative)
#define VSPEC1_PM_CTRL 0x18
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_PM_CTRL 0x03C00018u

//! Register Reset Value
#define VSPEC1_PM_CTRL_RST 0x0083u

//! Field PM_EN - Enable Packet Manager
#define VSPEC1_PM_CTRL_PM_EN_POS 0
//! Field PM_EN - Enable Packet Manager
#define VSPEC1_PM_CTRL_PM_EN_MASK 0x1u
//! Constant DISABLE - Disable
#define CONST_VSPEC1_PM_CTRL_PM_EN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_VSPEC1_PM_CTRL_PM_EN_ENABLE 0x1

//! Field MACSEC_EN - Disable MACsec (Applicable to MACsec capable devices only)
#define VSPEC1_PM_CTRL_MACSEC_EN_POS 1
//! Field MACSEC_EN - Disable MACsec (Applicable to MACsec capable devices only)
#define VSPEC1_PM_CTRL_MACSEC_EN_MASK 0x2u
//! Constant DISABLE - Disable
#define CONST_VSPEC1_PM_CTRL_MACSEC_EN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_VSPEC1_PM_CTRL_MACSEC_EN_ENABLE 0x1

//! Field PTP_1588_EN - Enable Sync 1588 PTP feature
#define VSPEC1_PM_CTRL_PTP_1588_EN_POS 2
//! Field PTP_1588_EN - Enable Sync 1588 PTP feature
#define VSPEC1_PM_CTRL_PTP_1588_EN_MASK 0x4u
//! Constant DISABLE - Disable
#define CONST_VSPEC1_PM_CTRL_PTP_1588_EN_DISABLE 0x0
//! Constant ENABLE - Enable
#define CONST_VSPEC1_PM_CTRL_PTP_1588_EN_ENABLE 0x1

//! Field PTP_1588_STEP - Configure 1588 time stamping mode
#define VSPEC1_PM_CTRL_PTP_1588_STEP_POS 3
//! Field PTP_1588_STEP - Configure 1588 time stamping mode
#define VSPEC1_PM_CTRL_PTP_1588_STEP_MASK 0x8u
//! Constant TWO_STEP - Two steps time stamping
#define CONST_VSPEC1_PM_CTRL_PTP_1588_STEP_TWO_STEP 0x0
//! Constant ONE_STEP - One step time stamping
#define CONST_VSPEC1_PM_CTRL_PTP_1588_STEP_ONE_STEP 0x1

//! Field SYNCE_EN - Enable Sync E feature (Applicable to SyncE capable devices only)
#define VSPEC1_PM_CTRL_SYNCE_EN_POS 4
//! Field SYNCE_EN - Enable Sync E feature (Applicable to SyncE capable devices only)
#define VSPEC1_PM_CTRL_SYNCE_EN_MASK 0x10u
//! Constant DISABLE - Disable Sync E
#define CONST_VSPEC1_PM_CTRL_SYNCE_EN_DISABLE 0x0
//! Constant ENABLE - Enable Sync E
#define CONST_VSPEC1_PM_CTRL_SYNCE_EN_ENABLE 0x1

//! Field SYNCE_CLK - Configure the Sync E clock frequency class.
#define VSPEC1_PM_CTRL_SYNCE_CLK_POS 5
//! Field SYNCE_CLK - Configure the Sync E clock frequency class.
#define VSPEC1_PM_CTRL_SYNCE_CLK_MASK 0x60u
//! Constant PSTN - Sync E clock frequency is PSTN class: 8kHz
#define CONST_VSPEC1_PM_CTRL_SYNCE_CLK_PSTN 0x0
//! Constant EEC1 - Sync E clock frequency is EEC-1 class: 2.048MHz
#define CONST_VSPEC1_PM_CTRL_SYNCE_CLK_EEC1 0x1
//! Constant EEC2 - Sync E clock frequency is EEC-2 class: 1.544MHz
#define CONST_VSPEC1_PM_CTRL_SYNCE_CLK_EEC2 0x2
//! Constant RES - Reserved
#define CONST_VSPEC1_PM_CTRL_SYNCE_CLK_RES 0x3

//! Field MAC_FREQ_TUNE - Control bit to tune the frequency of MACs within GPY in USXGMII Mode.
#define VSPEC1_PM_CTRL_MAC_FREQ_TUNE_POS 7
//! Field MAC_FREQ_TUNE - Control bit to tune the frequency of MACs within GPY in USXGMII Mode.
#define VSPEC1_PM_CTRL_MAC_FREQ_TUNE_MASK 0x180u
//! Constant PPM_0 - Standard USXMII Compliance Test condition
#define CONST_VSPEC1_PM_CTRL_MAC_FREQ_TUNE_PPM_0 0x0
//! Constant PPM_100 - Default working condition
#define CONST_VSPEC1_PM_CTRL_MAC_FREQ_TUNE_PPM_100 0x1
//! Constant PPM_300 - Long Duration 100% Traffic Stress Test condition
#define CONST_VSPEC1_PM_CTRL_MAC_FREQ_TUNE_PPM_300 0x2
//! Constant RES - Defaults to PPM_100
#define CONST_VSPEC1_PM_CTRL_MAC_FREQ_TUNE_RES 0x3

//! @}

//! \defgroup VSPEC1_MBOX_DATA_HIGH Register VSPEC1_MBOX_DATA_HIGH - Data for Mailbox ( r or w) (Register 30.13)
//! @{

//! Register Offset (relative)
#define VSPEC1_MBOX_DATA_HIGH 0x1A
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_MBOX_DATA_HIGH 0x03C0001Au

//! Register Reset Value
#define VSPEC1_MBOX_DATA_HIGH_RST 0x0000u

//! Field DATA - Mailbox Data
#define VSPEC1_MBOX_DATA_HIGH_DATA_POS 0
//! Field DATA - Mailbox Data
#define VSPEC1_MBOX_DATA_HIGH_DATA_MASK 0xFFFFu

//! @}

//! \defgroup VSPEC1_TEMP_STA Register VSPEC1_TEMP_STA - Temperature code (Register 30.14)
//! @{

//! Register Offset (relative)
#define VSPEC1_TEMP_STA 0x1C
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_TEMP_STA 0x03C0001Cu

//! Register Reset Value
#define VSPEC1_TEMP_STA_RST 0x0000u

//! Field TEMP_DATA - Code for Junction Temperature
#define VSPEC1_TEMP_STA_TEMP_DATA_POS 0
//! Field TEMP_DATA - Code for Junction Temperature
#define VSPEC1_TEMP_STA_TEMP_DATA_MASK 0x3FFu

//! @}

//! \defgroup VSPEC1_DCDC1 Register VSPEC1_DCDC1 - Internal DCDC Voltage Settings per state (Register 30.15)
//! @{

//! Register Offset (relative)
#define VSPEC1_DCDC1 0x1E
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_DCDC1 0x03C0001Eu

//! Register Reset Value
#define VSPEC1_DCDC1_RST 0x8E55u

//! Field BASE - BASE Voltage
#define VSPEC1_DCDC1_BASE_POS 0
//! Field BASE - BASE Voltage
#define VSPEC1_DCDC1_BASE_MASK 0x3u
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC1_BASE_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC1_BASE_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC1_BASE_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC1_BASE_V3 0x3

//! Field ANEG - ANEG Voltage
#define VSPEC1_DCDC1_ANEG_POS 2
//! Field ANEG - ANEG Voltage
#define VSPEC1_DCDC1_ANEG_MASK 0xCu
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC1_ANEG_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC1_ANEG_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC1_ANEG_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC1_ANEG_V3 0x3

//! Field TBT - Voltage for 10BASE-T state
#define VSPEC1_DCDC1_TBT_POS 4
//! Field TBT - Voltage for 10BASE-T state
#define VSPEC1_DCDC1_TBT_MASK 0x30u
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC1_TBT_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC1_TBT_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC1_TBT_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC1_TBT_V3 0x3

//! Field HUNDREDBT - Voltage for 100BASE-T state
#define VSPEC1_DCDC1_HUNDREDBT_POS 6
//! Field HUNDREDBT - Voltage for 100BASE-T state
#define VSPEC1_DCDC1_HUNDREDBT_MASK 0xC0u
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC1_HUNDREDBT_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC1_HUNDREDBT_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC1_HUNDREDBT_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC1_HUNDREDBT_V3 0x3

//! Field GIGA - Voltage for 1000BASE-T state
#define VSPEC1_DCDC1_GIGA_POS 8
//! Field GIGA - Voltage for 1000BASE-T state
#define VSPEC1_DCDC1_GIGA_MASK 0x300u
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC1_GIGA_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC1_GIGA_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC1_GIGA_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC1_GIGA_V3 0x3

//! Field GIGA2_5 - Voltage for 2500 BASE-T state
#define VSPEC1_DCDC1_GIGA2_5_POS 10
//! Field GIGA2_5 - Voltage for 2500 BASE-T state
#define VSPEC1_DCDC1_GIGA2_5_MASK 0xC00u
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC1_GIGA2_5_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC1_GIGA2_5_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC1_GIGA2_5_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC1_GIGA2_5_V3 0x3

//! Field RES - Reserved
#define VSPEC1_DCDC1_RES_POS 12
//! Field RES - Reserved
#define VSPEC1_DCDC1_RES_MASK 0x7000u

//! Field DVS_EN - Disable/Enable DVS Feature
#define VSPEC1_DCDC1_DVS_EN_POS 15
//! Field DVS_EN - Disable/Enable DVS Feature
#define VSPEC1_DCDC1_DVS_EN_MASK 0x8000u
//! Constant DIS - Disable DVS Feature
#define CONST_VSPEC1_DCDC1_DVS_EN_DIS 0x0
//! Constant EN - Enable DVS Feature
#define CONST_VSPEC1_DCDC1_DVS_EN_EN 0x1

//! @}

//! \defgroup VSPEC1_DCDC2 Register VSPEC1_DCDC2 - Internal DCDC Voltage Settings per EEE state (Register 30.16)
//! @{

//! Register Offset (relative)
#define VSPEC1_DCDC2 0x20
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_DCDC2 0x03C00020u

//! Register Reset Value
#define VSPEC1_DCDC2_RST 0x00AAu

//! Field QUIET_100 - 100BT EEE Quiet Voltage
#define VSPEC1_DCDC2_QUIET_100_POS 0
//! Field QUIET_100 - 100BT EEE Quiet Voltage
#define VSPEC1_DCDC2_QUIET_100_MASK 0x3u
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC2_QUIET_100_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC2_QUIET_100_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC2_QUIET_100_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC2_QUIET_100_V3 0x3

//! Field QUIET_1G - 1G EEE Quiet Voltage
#define VSPEC1_DCDC2_QUIET_1G_POS 2
//! Field QUIET_1G - 1G EEE Quiet Voltage
#define VSPEC1_DCDC2_QUIET_1G_MASK 0xCu
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC2_QUIET_1G_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC2_QUIET_1G_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC2_QUIET_1G_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC2_QUIET_1G_V3 0x3

//! Field QUIET_2G5 - 2.5G EEE Quiet Voltage
#define VSPEC1_DCDC2_QUIET_2G5_POS 4
//! Field QUIET_2G5 - 2.5G EEE Quiet Voltage
#define VSPEC1_DCDC2_QUIET_2G5_MASK 0x30u
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC2_QUIET_2G5_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC2_QUIET_2G5_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC2_QUIET_2G5_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC2_QUIET_2G5_V3 0x3

//! Field REFRESH_2G5 - 2.5G EEE Refresh Voltage
#define VSPEC1_DCDC2_REFRESH_2G5_POS 6
//! Field REFRESH_2G5 - 2.5G EEE Refresh Voltage
#define VSPEC1_DCDC2_REFRESH_2G5_MASK 0xC0u
//! Constant V0 - V0 voltage level 0.85V
#define CONST_VSPEC1_DCDC2_REFRESH_2G5_V0 0x0
//! Constant V1 - V1 voltage level 0.9V
#define CONST_VSPEC1_DCDC2_REFRESH_2G5_V1 0x1
//! Constant V2 - V2 voltage level 0.95V
#define CONST_VSPEC1_DCDC2_REFRESH_2G5_V2 0x2
//! Constant V3 - V3 voltage level 1.0V
#define CONST_VSPEC1_DCDC2_REFRESH_2G5_V3 0x3

//! @}

//! \defgroup VSPEC1_IMASK Register VSPEC1_IMASK - MACSec Interrupt Mask Register (Register 30.17)
//! @{

//! Register Offset (relative)
#define VSPEC1_IMASK 0x22
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_IMASK 0x03C00022u

//! Register Reset Value
#define VSPEC1_IMASK_RST 0x0000u

//! Field GMACL_TS - Status of Interrupt Request GMACL TS
#define VSPEC1_IMASK_GMACL_TS_POS 0
//! Field GMACL_TS - Status of Interrupt Request GMACL TS
#define VSPEC1_IMASK_GMACL_TS_MASK 0x1u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_VSPEC1_IMASK_GMACL_TS_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_VSPEC1_IMASK_GMACL_TS_ACTIVE 0x1

//! Field PM_LPI - PM LPI Interrupt Request
#define VSPEC1_IMASK_PM_LPI_POS 1
//! Field PM_LPI - PM LPI Interrupt Request
#define VSPEC1_IMASK_PM_LPI_MASK 0x2u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_VSPEC1_IMASK_PM_LPI_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_VSPEC1_IMASK_PM_LPI_ACTIVE 0x1

//! Field MCI - MCI Interrupt Request
#define VSPEC1_IMASK_MCI_POS 2
//! Field MCI - MCI Interrupt Request
#define VSPEC1_IMASK_MCI_MASK 0x4u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_VSPEC1_IMASK_MCI_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_VSPEC1_IMASK_MCI_ACTIVE 0x1

//! Field TS_FIFO - Time Stamp FIFO Interrupt
#define VSPEC1_IMASK_TS_FIFO_POS 3
//! Field TS_FIFO - Time Stamp FIFO Interrupt
#define VSPEC1_IMASK_TS_FIFO_MASK 0x8u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_VSPEC1_IMASK_TS_FIFO_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_VSPEC1_IMASK_TS_FIFO_ACTIVE 0x1

//! Field MACSEC - MACSEC Egress/Ingress Interrupt
#define VSPEC1_IMASK_MACSEC_POS 4
//! Field MACSEC - MACSEC Egress/Ingress Interrupt
#define VSPEC1_IMASK_MACSEC_MASK 0x10u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_VSPEC1_IMASK_MACSEC_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_VSPEC1_IMASK_MACSEC_ACTIVE 0x1

//! @}

//! \defgroup VSPEC1_ISTAT Register VSPEC1_ISTAT - MACSec Interrupt Mask Register (Register 30.18)
//! @{

//! Register Offset (relative)
#define VSPEC1_ISTAT 0x24
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_ISTAT 0x03C00024u

//! Register Reset Value
#define VSPEC1_ISTAT_RST 0x0000u

//! Field GMACL_TS - Status of Interrupt Request GMACL TS
#define VSPEC1_ISTAT_GMACL_TS_POS 0
//! Field GMACL_TS - Status of Interrupt Request GMACL TS
#define VSPEC1_ISTAT_GMACL_TS_MASK 0x1u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_VSPEC1_ISTAT_GMACL_TS_INACTIVE 0x0
//! Constant ACTIVE - GMACL Time Stamp is the source of Interrupt
#define CONST_VSPEC1_ISTAT_GMACL_TS_ACTIVE 0x1

//! Field PM_LPI - PM LPI Interrupt Request
#define VSPEC1_ISTAT_PM_LPI_POS 1
//! Field PM_LPI - PM LPI Interrupt Request
#define VSPEC1_ISTAT_PM_LPI_MASK 0x2u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_VSPEC1_ISTAT_PM_LPI_INACTIVE 0x0
//! Constant ACTIVE - LPI Interrupt Request from PM is the source of Interrupt
#define CONST_VSPEC1_ISTAT_PM_LPI_ACTIVE 0x1

//! Field MCI - MCI Interrupt Request
#define VSPEC1_ISTAT_MCI_POS 2
//! Field MCI - MCI Interrupt Request
#define VSPEC1_ISTAT_MCI_MASK 0x4u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_VSPEC1_ISTAT_MCI_INACTIVE 0x0
//! Constant ACTIVE - MCI Interrupt Request is the source of Interrupt
#define CONST_VSPEC1_ISTAT_MCI_ACTIVE 0x1

//! Field TS_FIFO - Time Stamp FIFO Interrupt
#define VSPEC1_ISTAT_TS_FIFO_POS 3
//! Field TS_FIFO - Time Stamp FIFO Interrupt
#define VSPEC1_ISTAT_TS_FIFO_MASK 0x8u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_VSPEC1_ISTAT_TS_FIFO_INACTIVE 0x0
//! Constant ACTIVE - Time Stamp FIFO Interrupt is the source of Interrupt
#define CONST_VSPEC1_ISTAT_TS_FIFO_ACTIVE 0x1

//! Field MACSEC - MACSEC Egress/Ingress Interrupt
#define VSPEC1_ISTAT_MACSEC_POS 4
//! Field MACSEC - MACSEC Egress/Ingress Interrupt
#define VSPEC1_ISTAT_MACSEC_MASK 0x10u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_VSPEC1_ISTAT_MACSEC_INACTIVE 0x0
//! Constant ACTIVE - MACSEC Egress/Ingress Interrupt is the source of Interrupt
#define CONST_VSPEC1_ISTAT_MACSEC_ACTIVE 0x1

//! @}

//! \defgroup VSPEC1_DCDC3 Register VSPEC1_DCDC3 - Internal DCDC Voltage Settings Storage Reg per EEE state (Register 30.19)
//! @{

//! Register Offset (relative)
#define VSPEC1_DCDC3 0x26
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_DCDC3 0x03C00026u

//! Register Reset Value
#define VSPEC1_DCDC3_RST 0x0154u

//! Field DSM_TARGET - DSM Target Value
#define VSPEC1_DCDC3_DSM_TARGET_POS 0
//! Field DSM_TARGET - DSM Target Value
#define VSPEC1_DCDC3_DSM_TARGET_MASK 0x7FFu

//! Field DSM_DONE - Status of DSM Calibration
#define VSPEC1_DCDC3_DSM_DONE_POS 15
//! Field DSM_DONE - Status of DSM Calibration
#define VSPEC1_DCDC3_DSM_DONE_MASK 0x8000u
//! Constant NOT_DONE - STA writes 0 to retrigger DSM based Voltage Calibration
#define CONST_VSPEC1_DCDC3_DSM_DONE_NOT_DONE 0x0
//! Constant DONE - STA writes to 1 prevents the calibration to happen
#define CONST_VSPEC1_DCDC3_DSM_DONE_DONE 0x1

//! @}

//! \defgroup VSPEC1_LANE_ASP_MAP Register VSPEC1_LANE_ASP_MAP - ASP Mapping to Physical Lanes(Register 30.20)
//! @{

//! Register Offset (relative)
#define VSPEC1_LANE_ASP_MAP 0x28
//! Register Offset (absolute) for 1st Instance VSPEC1
#define VSPEC1_VSPEC1_LANE_ASP_MAP 0x03C00028u

//! Register Reset Value
#define VSPEC1_LANE_ASP_MAP_RST 0x00E4u

//! Field LANE_A - Map Physical Lane-A to the ASP
#define VSPEC1_LANE_ASP_MAP_LANE_A_POS 0
//! Field LANE_A - Map Physical Lane-A to the ASP
#define VSPEC1_LANE_ASP_MAP_LANE_A_MASK 0x3u
//! Constant ASPA - Map Physical Lane-A to the ASP-A
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_A_ASPA 0x0
//! Constant ASPB - Map Physical Lane-A to the ASP-B
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_A_ASPB 0x1
//! Constant ASPC - Map Physical Lane-A to the ASP-C
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_A_ASPC 0x2
//! Constant ASPD - Map Physical Lane-A to the ASP-D
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_A_ASPD 0x3

//! Field LANE_B - Map Physical Lane-B to the ASP
#define VSPEC1_LANE_ASP_MAP_LANE_B_POS 2
//! Field LANE_B - Map Physical Lane-B to the ASP
#define VSPEC1_LANE_ASP_MAP_LANE_B_MASK 0xCu
//! Constant ASPA - Map Physical Lane-B to the ASP-A
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_B_ASPA 0x0
//! Constant ASPB - Map Physical Lane-B to the ASP-B
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_B_ASPB 0x1
//! Constant ASPC - Map Physical Lane-B to the ASP-C
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_B_ASPC 0x2
//! Constant ASPD - Map Physical Lane-B to the ASP-D
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_B_ASPD 0x3

//! Field LANE_C - Map Physical Lane-C to the ASP
#define VSPEC1_LANE_ASP_MAP_LANE_C_POS 4
//! Field LANE_C - Map Physical Lane-C to the ASP
#define VSPEC1_LANE_ASP_MAP_LANE_C_MASK 0x30u
//! Constant ASPA - Map Physical Lane-C to the ASP-A
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_C_ASPA 0x0
//! Constant ASPB - Map Physical Lane-C to the ASP-B
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_C_ASPB 0x1
//! Constant ASPC - Map Physical Lane-C to the ASP-C
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_C_ASPC 0x2
//! Constant ASPD - Map Physical Lane-C to the ASP-D
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_C_ASPD 0x3

//! Field LANE_D - Map Physical Lane-D to the ASP
#define VSPEC1_LANE_ASP_MAP_LANE_D_POS 6
//! Field LANE_D - Map Physical Lane-D to the ASP
#define VSPEC1_LANE_ASP_MAP_LANE_D_MASK 0xC0u
//! Constant ASPA - Map Physical Lane-D to the ASP-A
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_D_ASPA 0x0
//! Constant ASPB - Map Physical Lane-D to the ASP-B
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_D_ASPB 0x1
//! Constant ASPC - Map Physical Lane-D to the ASP-C
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_D_ASPC 0x2
//! Constant ASPD - Map Physical Lane-D to the ASP-D
#define CONST_VSPEC1_LANE_ASP_MAP_LANE_D_ASPD 0x3

//! @}

//! @}

#endif
