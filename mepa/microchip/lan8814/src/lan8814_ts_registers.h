// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_LAN8814_TS_REGISTERS_H
#define _MEPA_LAN8814_TS_REGISTERS_H

// EP-4 Chip 1588 Common Registers

//1588 PLL Registers
#define LAN8814_1588_PLL_RESET                                 LAN8814_EXT_PAGE_4, 320
#define LAN8814_1588_PLL_RESET_EN                              LAN8814_BIT(0)
#define LAN8814_1588_PLL_BYPASS                                LAN8814_EXT_PAGE_4, 321
#define LAN8814_1588_PLL_BYPASS_EN                             LAN8814_BIT(0)
#define LAN8814_1588_PLL_STATUS                                LAN8814_EXT_PAGE_4, 322
#define LAN8814_1588_PLL_DIVEDER                               LAN8814_EXT_PAGE_4, 323
#define LAN8814_1588_PLL_DIVR_F(x)                             LAN8814_ENCODE_BITFIELD(x, 10, 14)
#define LAN8814_1588_PLL_DIVR                                  LAN8814_ENCODE_BITMASK(10, 14)
#define LAN8814_1588_PLL_DIVF_F(x)                             LAN8814_ENCODE_BITFIELD(x, 3, 9)
#define LAN8814_1588_PLL_DIVF                                  LAN8814_ENCODE_BITMASK(3, 9)
#define LAN8814_1588_PLL_DIVQ_F(x)                             LAN8814_ENCODE_BITFIELD(x, 0, 2)
#define LAN8814_1588_PLL_DIVQ                                  LAN8814_ENCODE_BITMASK(0, 2)
#define LAN8814_1588_PLL_FILTER                                LAN8814_EXT_PAGE_4, 323
#define LAN8814_1588_PLL_FILTER_RANGE_F(x)                     LAN8814_ENCODE_BITFIELD(x, 0,3)
#define LAN8814_1588_PLL_FILTER_RANGE                          LAN8814_ENCODE_BITMASK(0, 3)

// PTP Common Command and Control Register
#define LAN8814_PTP_CMD_CTL                                    LAN8814_EXT_PAGE_4, 512
#define LAN8814_PTP_CMD_CTL_LTC_DLYD_STEP_SECONDS              LAN8814_BIT(15)
#define LAN8814_PTP_CMD_CTL_LTC_DLYD_LOAD                      LAN8814_BIT(14)
#define LAN8814_PTP_CMD_CTL_LTC_TARGET_READ                    LAN8814_BIT(13)
#define LAN8814_PTP_CMD_CTL_MANUAL_CAPTURE_SEL_F(x)            LAN8814_ENCODE_BITFIELD(x, 9, 3)
#define LAN8814_PTP_CMD_CTL_MANUAL_CAPTURE_SEL                 LAN8814_ENCODE_BITMASK(9, 3)
#define LAN8814_PTP_CMD_CTL_MANUAL_CAPTURE                     LAN8814_BIT(8)
#define LAN8814_PTP_CMD_CTL_LTC_TEMP_RATE                      LAN8814_BIT(7)
#define LAN8814_PTP_CMD_CTL_LTC_STEP_NANOSECONDS               LAN8814_BIT(6)
#define LAN8814_PTP_CMD_CTL_LTC_STEP_SECONDS                   LAN8814_BIT(5)
#define LAN8814_PTP_CMD_CTL_LTC_LOAD                           LAN8814_BIT(4)
#define LAN8814_PTP_CMD_CTL_LTC_READ                           LAN8814_BIT(3)
#define LAN8814_PTP_CMD_CTL_LTC_TEMP_RATE_SEL                  LAN8814_BIT(2)
#define LAN8814_PTP_CMD_CTL_ENABLE                             LAN8814_BIT(1)
#define LAN8814_PTP_CMD_CTL_DISABLE                            LAN8814_BIT(0)

// PTP General Configuration Register
#define LAN8814_PTP_GENERAL_CONFIG                             LAN8814_EXT_PAGE_4, 513
#define LAN8814_PTP_GENERAL_CONFIG_LTC_EVENT_B_F(x)            LAN8814_ENCODE_BITFIELD(x, 8, 4)
#define LAN8814_PTP_GENERAL_CONFIG_LTC_EVENT_B                 LAN8814_ENCODE_BITMASK(8, 4)
#define LAN8814_PTP_GENERAL_CONFIG_LTC_EVENT_A_F(x)            LAN8814_ENCODE_BITFIELD(x, 4, 4)
#define LAN8814_PTP_GENERAL_CONFIG_LTC_EVENT_A                 LAN8814_ENCODE_BITMASK(4, 4)
#define LAN8814_PTP_GENERAL_CONFIG_LTC_EVENT_POL_B             LAN8814_BIT(3)
#define LAN8814_PTP_GENERAL_CONFIG_RELOAD_ADD_B                LAN8814_BIT(2)
#define LAN8814_PTP_GENERAL_CONFIG_LTC_EVENT_POL_A             LAN8814_BIT(1)
#define LAN8814_PTP_GENERAL_CONFIG_RELOAD_ADD_A                LAN8814_BIT(0)


// PTP Reference Clock Configuration Register
#define LAN8814_PTP_REF_CLK_CFG                                LAN8814_EXT_PAGE_4, 514
#define LAN8814_PTP_REF_CLK_CFG_EPPS_ENABLE                    LAN8814_BIT(13)
#define LAN8814_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(x)            LAN8814_ENCODE_BITFIELD(x, 10, 3)
#define LAN8814_PTP_REF_CLK_CFG_REF_CLK_SOURCE                 LAN8814_ENCODE_BITMASK(10, 3)
#define LAN8814_PTP_REF_CLK_CFG_REF_CLK_PERIOD_OVERRIDE        LAN8814_BIT(9)
#define LAN8814_PTP_REF_CLK_CFG_REF_CLK_PERIOD_F(x)            LAN8814_ENCODE_BITFIELD(x, 0, 9)
#define LAN8814_PTP_REF_CLK_CFG_REF_CLK_PERIOD                 LAN8814_ENCODE_BITMASK(0, 9)

// PTP Common Interrupt Status Register
#define LAN8814_PTP_COMMON_INT_STS                             LAN8814_EXT_PAGE_4, 515

// PTP Common Interrupt Enable Register
#define LAN8814_PTP_COMMON_INT_EN                              LAN8814_EXT_PAGE_4,516

// PTP LTC Set Seconds
#define LAN8814_PTP_LTC_SET_SEC_HI                             LAN8814_EXT_PAGE_4, 517
#define LAN8814_PTP_LTC_SET_SEC_MID                            LAN8814_EXT_PAGE_4, 518
#define LAN8814_PTP_LTC_SET_SEC_LO                             LAN8814_EXT_PAGE_4, 519

// PTP LTC Set Nanoseconds
#define LAN8814_PTP_LTC_SET_NS_HI                              LAN8814_EXT_PAGE_4, 520
#define LAN8814_PTP_LTC_SET_NS_LO                              LAN8814_EXT_PAGE_4, 521

// PTP LTC Set Sub-Nanoseconds
#define LAN8814_PTP_LTC_SET_SUBNS_HI                           LAN8814_EXT_PAGE_4, 522
#define LAN8814_PTP_LTC_SET_SUBNS_LO                           LAN8814_EXT_PAGE_4, 523

// PTP LTC Rate Adjustment High Register
#define LAN8814_PTP_LTC_RATE_ADJ_HI                            LAN8814_EXT_PAGE_4, 524
#define LAN8814_PTP_LTC_RATE_ADJ_HI_DIR                        LAN8814_BIT(15)
#define LAN8814_PTP_LTC_RATE_ADJ_HI_VALUE_F(x)                 LAN8814_ENCODE_BITFIELD(x, 0, 13)
#define LAN8814_PTP_LTC_RATE_ADJ_HI_VALUE                      LAN8814_ENCODE_BITMASK(0, 13)


// PTP LTC Rate Adjustment Low Register
#define LAN8814_PTP_LTC_RATE_ADJ_LO                            LAN8814_EXT_PAGE_4, 525

// PTP LTC Temporary Rate Adjustment High Register
#define LAN8814_PTP_LTC_TEMP_RATE_ADJ_HI                       LAN8814_EXT_PAGE_4, 526

// PTP LTC Temporary Rate Adjustment Low Register
#define LAN8814_PTP_LTC_TEMP_RATE_ADJ_LO                       LAN8814_EXT_PAGE_4, 527

// PTP LTC Temporary Rate Duration High Register
#define LAN8814_PTP_LTC_TEMP_RATE_DURATION_HI                  LAN8814_EXT_PAGE_4, 528

// PTP LTC Temporary Rate Duration Low Register
#define LAN8814_PTP_LTC_TEMP_RATE_DURATION_LO                  LAN8814_EXT_PAGE_4, 529

// PTP LTC Step Adjustment
#define LAN8814_PTP_LTC_STEP_ADJ_HI                            LAN8814_EXT_PAGE_4, 530
#define LAN8814_PTP_LTC_STEP_ADJ_DIR                           LAN8814_BIT(15)
#define LAN8814_PTP_LTC_STEP_ADJ_HI_VALUE_F(x)                 LAN8814_ENCODE_BITFIELD(x, 0, 13)
#define LAN8814_PTP_LTC_STEP_ADJ_HI_VALUE                      LAN8814_ENCODE_BITMASK(0, 13)

#define LAN8814_PTP_LTC_STEP_ADJ_LO                            LAN8814_EXT_PAGE_4, 531

// PTP LTC External Adjustment Configuration Register
#define LAN8814_PTP_LTC_EXT_ADJ_CFG                            LAN8814_EXT_PAGE_4, 532
#define LAN8814_PTP_LTC_EXT_ADJ_GPIO_EPPS_SEL                  LAN8814_BIT(6)
#define LAN8814_PTP_LTC_EXT_ADJ_SERIAL_TOD_EN                  LAN8814_BIT(5)
#define LAN8814_PTP_LTC_EXT_ADJ_MODE                           LAN8814_BIT(4)
#define LAN8814_PTP_LTC_EXT_ADJ_TEMP_RATE                      LAN8814_BIT(3)
#define LAN8814_PTP_LTC_EXT_ADJ_STEP_NSEC_EN                   LAN8814_BIT(2)
#define LAN8814_PTP_LTC_EXT_ADJ_STEP_SEC_EN                    LAN8814_BIT(1)
#define LAN8814_PTP_LTC_EXT_ADJ_LOAD_EN                        LAN8814_BIT(0)

// PTP LTC Target x Seconds High Register
#define LAN8814_PTP_LTC_TARGET_SEC_HI_A                        LAN8814_EXT_PAGE_4, 533
#define LAN8814_PTP_LTC_TARGET_SEC_LO_A                        LAN8814_EXT_PAGE_4, 534

// PTP LTC Target x Nanoseconds High Register
#define LAN8814_PTP_LTC_TARGET_NS_HI_A                         LAN8814_EXT_PAGE_4, 535
#define LAN8814_PTP_LTC_TARGET_NS_LO_A                         LAN8814_EXT_PAGE_4, 536

// PTP LTC Target x Reload / Add Seconds High Register
#define LAN8814_PTP_LTC_TARGET_RELOAD_SEC_HI_A                 LAN8814_EXT_PAGE_4, 537
#define LAN8814_PTP_LTC_TARGET_RELOAD_SEC_LO_A                 LAN8814_EXT_PAGE_4, 538
#define LAN8814_PTP_LTC_TARGET_RELOAD_NS_HI_A                  LAN8814_EXT_PAGE_4, 539
#define LAN8814_PTP_LTC_TARGET_RELOAD_NS_LO_A                  LAN8814_EXT_PAGE_4, 540

// PTP LTC Target x Actual Nanoseconds High Register
#define LAN8814_PTP_LTC_TARGET_ACT_NS_HI_A                     LAN8814_EXT_PAGE_4, 541
#define LAN8814_PTP_LTC_TARGET_ACT_NS_LO_A                     LAN8814_EXT_PAGE_4, 542

// PTP LTC Target x Seconds High Register
#define LAN8814_PTP_LTC_TARGET_SEC_HI_B                        LAN8814_EXT_PAGE_4, 543

// PTP LTC Target x Seconds Low Register
#define LAN8814_PTP_LTC_TARGET_SEC_LO_B                        LAN8814_EXT_PAGE_4, 544

// PTP LTC Target x Nanoseconds High Register
#define LAN8814_PTP_LTC_TARGET_NS_HI_B                         LAN8814_EXT_PAGE_4, 545

// PTP LTC Target x Nanoseconds Low Register
#define LAN8814_PTP_LTC_TARGET_NS_LO_B                         LAN8814_EXT_PAGE_4, 546

// PTP LTC Target x Reload / Add Seconds High Register
#define LAN8814_PTP_LTC_TARGET_RELOAD_SEC_HI_B                 LAN8814_EXT_PAGE_4, 547

// PTP LTC Target x Reload / Add Seconds Low Register
#define LAN8814_PTP_LTC_TARGET_RELOAD_SEC_LO_B                 LAN8814_EXT_PAGE_4, 548

// PTP LTC Target x Reload / Add Nanoseconds High Register
#define LAN8814_PTP_LTC_TARGET_RELOAD_NS_HI_B                  LAN8814_EXT_PAGE_4, 549

// PTP LTC Target x Reload / Add Nanoseconds Low Register
#define LAN8814_PTP_LTC_TARGET_RELOAD_NS_LO_B                  LAN8814_EXT_PAGE_4, 550

// PTP LTC Target x Actual Nanoseconds High Register
#define LAN8814_PTP_LTC_TARGET_ACT_NS_HI_B                     LAN8814_EXT_PAGE_4, 551

// PTP LTC Target x Actual Nanoseconds Low Register
#define LAN8814_PTP_LTC_TARGET_ACT_NS_LO_B                     LAN8814_EXT_PAGE_4, 552

// PTP LTC READ Registers
#define LAN8814_PTP_LTC_RD_SEC_HI                              LAN8814_EXT_PAGE_4, 553
#define LAN8814_PTP_LTC_RD_SEC_MID                             LAN8814_EXT_PAGE_4, 554
#define LAN8814_PTP_LTC_RD_SEC_LO                              LAN8814_EXT_PAGE_4, 555
#define LAN8814_PTP_LTC_RD_NS_HI                               LAN8814_EXT_PAGE_4, 556
#define LAN8814_PTP_LTC_RD_NS_LO                               LAN8814_EXT_PAGE_4, 557
#define LAN8814_PTP_LTC_RD_SUBNS_HI                            LAN8814_EXT_PAGE_4, 558
#define LAN8814_PTP_LTC_RD_SUBNS_LO                            LAN8814_EXT_PAGE_4, 559


// GPIO

//PTP GPIO Select Register
#define LAN8814_PTP_GPIO_SEL                               LAN8814_EXT_PAGE_4, 560
#define LAN8814_PTP_GPIO_SELECT_F(x)                       LAN8814_ENCODE_BITFIELD(x, 8, 3)
#define LAN8814_PTP_GPIO_SELECT                            LAN8814_ENCODE_BITMASK(8, 3)

//PTP GPIO Capture Map High Register
#define LAN8814_PTP_GPIO_CAP_MAP_HI                        LAN8814_EXT_PAGE_4, 561
#define LAN8814_PTP_GPIO_CAP_7_MAP_F(x)                    LAN8814_ENCODE_BITFIELD(x, 12, 4)
#define LAN8814_PTP_GPIO_CAP_7_MAP                         LAN8814_ENCODE_BITMASK(12, 4)
#define LAN8814_PTP_GPIO_CAP_6_MAP_F(x)                    LAN8814_ENCODE_BITFIELD(x, 8, 4)
#define LAN8814_PTP_GPIO_CAP_6_MAP                         LAN8814_ENCODE_BITMASK(8, 4)
#define LAN8814_PTP_GPIO_CAP_5_MAP_F(x)                    LAN8814_ENCODE_BITFIELD(x, 4, 4)
#define LAN8814_PTP_GPIO_CAP_5_MAP                         LAN8814_ENCODE_BITMASK(4, 4)
#define LAN8814_PTP_GPIO_CAP_4_MAP_F(x)                    LAN8814_ENCODE_BITFIELD(x, 0, 4)
#define LAN8814_PTP_GPIO_CAP_4_MAP                         LAN8814_ENCODE_BITMASK(0, 4)
//PTP GPIO Capture Map Low Register
#define LAN8814_PTP_GPIO_CAP_MAP_LO                        LAN8814_EXT_PAGE_4, 562
#define LAN8814_PTP_GPIO_CAP_3_MAP_F(x)                    LAN8814_ENCODE_BITFIELD(x, 12, 4)
#define LAN8814_PTP_GPIO_CAP_3_MAP                         LAN8814_ENCODE_BITMASK(12, 4)
#define LAN8814_PTP_GPIO_CAP_2_MAP_F(x)                    LAN8814_ENCODE_BITFIELD(x, 8, 4)
#define LAN8814_PTP_GPIO_CAP_2_MAP                         LAN8814_ENCODE_BITMASK(8, 4)
#define LAN8814_PTP_GPIO_CAP_1_MAP_F(x)                    LAN8814_ENCODE_BITFIELD(x, 4, 4)
#define LAN8814_PTP_GPIO_CAP_1_MAP                         LAN8814_ENCODE_BITMASK(4, 4)
#define LAN8814_PTP_GPIO_CAP_0_MAP_F(x)                    LAN8814_ENCODE_BITFIELD(x, 0, 4)
#define LAN8814_PTP_GPIO_CAP_0_MAP                         LAN8814_ENCODE_BITMASK(0, 4)

//PTP GPIO Capture Enable Register
#define LAN8814_PTP_GPIO_CAP_EN                            LAN8814_EXT_PAGE_4, 563
#define LAN8814_PTP_GPIO_FE_CAPTURE_EN_F(x)                LAN8814_ENCODE_BITFIELD(x, 8, 8)
#define LAN8814_PTP_GPIO_FE_CAPTURE_EN                     LAN8814_ENCODE_BITMASK(8, 8)
#define LAN8814_PTP_GPIO_RE_CAPTURE_EN_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 8)
#define LAN8814_PTP_GPIO_RE_CAPTURE_EN                     LAN8814_ENCODE_BITMASK(0, 8)

//PTP GPIO Capture Lock Register
#define LAN8814_PTP_GPIO_CAP_LOCK                          LAN8814_EXT_PAGE_4, 564
#define LAN8814_PTP_GPIO_LOCK_FE_F(x)                      LAN8814_ENCODE_BITFIELD(x, 8, 8)
#define LAN8814_PTP_GPIO_LOCK_FE                           LAN8814_ENCODE_BITMASK(8, 8)
#define LAN8814_PTP_GPIO_LOCK_RE_F(x)                      LAN8814_ENCODE_BITFIELD(x, 0, 8)
#define LAN8814_PTP_GPIO_LOCK_RE                           LAN8814_ENCODE_BITMASK(0, 8)

//PTP GPIO x Rising Edge Clock  Capture Registers
#define LAN8814_PTP_GPIO_RE_CLOCK_SEC_HI                   LAN8814_EXT_PAGE_4, 565
#define LAN8814_PTP_GPIO_RE_CLOCK_SEC_LO                   LAN8814_EXT_PAGE_4, 566
#define LAN8814_PTP_GPIO_RE_CLOCK_NS_HI                    LAN8814_EXT_PAGE_4, 567
#define LAN8814_PTP_GPIO_RE_CLOCK_NS_LO                    LAN8814_EXT_PAGE_4, 568

//PTP GPIO x Falling Edge Clock Capture Register
#define LAN8814_PTP_GPIO_FE_CLOCK_SEC_HI                   LAN8814_EXT_PAGE_4, 569
#define LAN8814_PTP_GPIO_FE_CLOCK_SEC_LO                   LAN8814_EXT_PAGE_4, 570
#define LAN8814_PTP_GPIO_FE_CLOCK_NS_HI                    LAN8814_EXT_PAGE_4, 571
#define LAN8814_PTP_GPIO_FE_CLOCK_NS_LO                    LAN8814_EXT_PAGE_4, 572

//PTP GPIO Capture Status Register
#define LAN8814_PTP_GPIO_CAP_STS                           LAN8814_EXT_PAGE_4, 573

//PTP GPIO Interrupt Clear Configuration Register
#define LAN8814_PTP_GPIO_INT_CLR_CFG                       LAN8814_EXT_PAGE_4, 574

// PTP LTC Hard Reset Register
#define LAN8814_PTP_LTC_HARD_RESET                         LAN8814_EXT_PAGE_4, 575
#define LAN8814_PTP_LTC_HARD_RESET_CMD                     LAN8814_BIT(0)

// PTP LTC Soft Reset Register
#define LAN8814_PTP_LTC_SOFT_RESET                         LAN8814_EXT_PAGE_4, 576
#define LAN8814_PTP_LTC_SOFT_RESET_CMD                     LAN8814_BIT(0)

// PTP Operating Mode Register
#define LAN8814_PTP_OPERATING_MODE                         LAN8814_EXT_PAGE_4, 577
#define LAN8814_PTP_OPERATING_MODE_VAL_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 2)
#define LAN8814_PTP_OPERATING_MODE_VAL                     LAN8814_ENCODE_BITMASK(0, 2)

// PTP Revision Register
#define LAN8814_PTP_REVISION                               LAN8814_EXT_PAGE_4, 578

// PTP PCH SubPortID Register
#define LAN8814_PTP_PCH_SUBPORT_ID                         LAN8814_EXT_PAGE_4, 579
#define LAN8814_PTP_PCH_SUBPORT_ID_PORT3_F(x)              LAN8814_ENCODE_BITFIELD(x, 12, 4)
#define LAN8814_PTP_PCH_SUBPORT_ID_PORT3                   LAN8814_ENCODE_BITMASK(12, 4)
#define LAN8814_PTP_PCH_SUBPORT_ID_PORT2_F(x)              LAN8814_ENCODE_BITFIELD(x, 8, 4)
#define LAN8814_PTP_PCH_SUBPORT_ID_PORT2                   LAN8814_ENCODE_BITMASK(8, 4)
#define LAN8814_PTP_PCH_SUBPORT_ID_PORT1_F(x)              LAN8814_ENCODE_BITFIELD(x, 4, 4)
#define LAN8814_PTP_PCH_SUBPORT_ID_PORT1                   LAN8814_ENCODE_BITMASK(4, 4)
#define LAN8814_PTP_PCH_SUBPORT_ID_PORT0_F(x)              LAN8814_ENCODE_BITFIELD(x, 0, 4)
#define LAN8814_PTP_PCH_SUBPORT_ID_PORT0                   LAN8814_ENCODE_BITMASK(0, 4)


// EP-4 PTP Latency Correction Control Register
#define LAN8814_PTP_LATENCY_CORRECTION_CTRL                LAN8814_EXT_PAGE_4, 580

// EP-4 1588 Serial Timestamp Interface Registers

// 1588 STI Configuration Register
#define LAN8814_PTP_STI_CONFIG                             LAN8814_EXT_PAGE_4, 768
#define LAN8814_PTP_STI_Tx_COUNT                           LAN8814_EXT_PAGE_4, 769
#define LAN8814_PTP_STI_HARD_RESET                         LAN8814_EXT_PAGE_4, 770
#define LAN8814_PTP_STI_SOFT_RESET                         LAN8814_EXT_PAGE_4, 771



// EP-5 1588 Port-Specific Registers

// PTP TSU Interrupt Enable Register
#define LAN8814_PTP_TSU_INT_EN                             LAN8814_EXT_PAGE_5, 512
#define LAN8814_PTP_TSU_INT_TX_TS_OVRFL_EN                 LAN8814_BIT(3)
#define LAN8814_PTP_TSU_INT_TX_TS_EN                       LAN8814_BIT(2)
#define LAN8814_PTP_TSU_INT_RX_TS_OVRFL_EN                 LAN8814_BIT(1)
#define LAN8814_PTP_TSU_INT_RX_TS_EN                       LAN8814_BIT(0)


// PTP TSU Interrupt Status Register
#define LAN8814_PTP_TSU_INT_STS                            LAN8814_EXT_PAGE_5, 513
#define LAN8814_PTP_TX_TS_OVRFL_INT                        LAN8814_BIT(3)
#define LAN8814_PTP_TX_TS_INT                              LAN8814_BIT(2)
#define LAN8814_PTP_RX_TS_OVRFL_INT                        LAN8814_BIT(1)
#define LAN8814_PTP_RX_TS_INT                              LAN8814_BIT(0)

// PTP Modification Error Register
#define LAN8814_PTP_MOD_ERR                                LAN8814_EXT_PAGE_5, 514

// PTP User MAC Address
#define LAN8814_PTP_RX_USER_MAC_HI                         LAN8814_EXT_PAGE_5, 515
#define LAN8814_PTP_RX_USER_MAC_MID                        LAN8814_EXT_PAGE_5, 516
#define LAN8814_PTP_RX_USER_MAC_LO                         LAN8814_EXT_PAGE_5, 517

//PTP User IP Address Registers
#define LAN8814_PTP_RX_USER_IP_ADDR_0                      LAN8814_EXT_PAGE_5, 518
#define LAN8814_PTP_RX_USER_IP_ADDR_1                      LAN8814_EXT_PAGE_5, 519
#define LAN8814_PTP_RX_USER_IP_ADDR_2                      LAN8814_EXT_PAGE_5, 520
#define LAN8814_PTP_RX_USER_IP_ADDR_3                      LAN8814_EXT_PAGE_5, 521
#define LAN8814_PTP_RX_USER_IP_ADDR_4                      LAN8814_EXT_PAGE_5, 522
#define LAN8814_PTP_RX_USER_IP_ADDR_5                      LAN8814_EXT_PAGE_5, 523
#define LAN8814_PTP_RX_USER_IP_ADDR_6                      LAN8814_EXT_PAGE_5, 524
#define LAN8814_PTP_RX_USER_IP_ADDR_7                      LAN8814_EXT_PAGE_5, 525

//PTP User IP Mask Registers
#define LAN8814_PTP_RX_USER_IP_MASK_0                      LAN8814_EXT_PAGE_5, 526
#define LAN8814_PTP_RX_USER_IP_MASK_1                      LAN8814_EXT_PAGE_5, 527
#define LAN8814_PTP_RX_USER_IP_MASK_2                      LAN8814_EXT_PAGE_5, 528
#define LAN8814_PTP_RX_USER_IP_MASK_3                      LAN8814_EXT_PAGE_5, 529
#define LAN8814_PTP_RX_USER_IP_MASK_4                      LAN8814_EXT_PAGE_5, 530
#define LAN8814_PTP_RX_USER_IP_MASK_5                      LAN8814_EXT_PAGE_5, 531
#define LAN8814_PTP_RX_USER_IP_MASK_6                      LAN8814_EXT_PAGE_5, 532
#define LAN8814_PTP_RX_USER_IP_MASK_7                      LAN8814_EXT_PAGE_5, 533

// VLAN configuration registers common for both ingress and egress
#define LAN8814_PTP_VLAN_ETH_TYPE_ID                       LAN8814_EXT_PAGE_5, 534
#define LAN8814_VLAN1_TYPE_ID                              LAN8814_EXT_PAGE_5, 535
#define LAN8814_VLAN1_TYPE_SELECT_F(x)                     LAN8814_ENCODE_BITFIELD(x, 12, 2)
#define LAN8814_VLAN1_TYPE_SELECT                          LAN8814_ENCODE_BITMASK(12, 2)
#define LAN8814_VLAN1_TYPE_ID_VAL_F(x)                     LAN8814_ENCODE_BITFIELD(x, 0, 11)
#define LAN8814_VLAN1_TYPE_ID_VAL                          LAN8814_ENCODE_BITMASK(0, 11)
#define LAN8814_VLAN1_ID_MASK                              LAN8814_EXT_PAGE_5, 536
#define LAN8814_VLAN1_ID_MASK_VAL_F(x)                     LAN8814_ENCODE_BITFIELD(x, 0, 11)
#define LAN8814_VLAN1_ID_MASK_VAL                          LAN8814_ENCODE_BITMASK(0, 11)
#define LAN8814_VLAN1_VID_RANGE_UP                         LAN8814_EXT_PAGE_5, 537
#define LAN8814_VLAN1_VID_RANGE_EN                         LAN8814_BIT(12)
#define LAN8814_VLAN1_VID_RANGE_UP_VAL_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 11)
#define LAN8814_VLAN1_VID_RANGE_UP_VAL                     LAN8814_ENCODE_BITMASK(0, 11)
#define LAN8814_VLAN1_VID_RANGE_LO                         LAN8814_EXT_PAGE_5, 538
#define LAN8814_VLAN1_VID_RANGE_LO_VAL_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 11)
#define LAN8814_VLAN1_VID_RANGE_LO_VAL                     LAN8814_ENCODE_BITMASK(0, 11)
#define LAN8814_VLAN2_TYPE_ID                              LAN8814_EXT_PAGE_5, 539
#define LAN8814_VLAN2_TYPE_SELECT_F(x)                     LAN8814_ENCODE_BITFIELD(x, 12, 2)
#define LAN8814_VLAN2_TYPE_SELECT                          LAN8814_ENCODE_BITMASK(12, 2)
#define LAN8814_VLAN2_TYPE_ID_VAL_F(x)                     LAN8814_ENCODE_BITFIELD(x, 0, 11)
#define LAN8814_VLAN2_TYPE_ID_VAL                          LAN8814_ENCODE_BITMASK(0, 11)
#define LAN8814_VLAN2_ID_MASK                              LAN8814_EXT_PAGE_5, 540
#define LAN8814_VLAN2_ID_MASK_VAL_F(x)                     LAN8814_ENCODE_BITFIELD(x, 0, 11)
#define LAN8814_VLAN2_ID_MASK_VAL                          LAN8814_ENCODE_BITMASK(0, 11)
#define LAN8814_VLAN2_VID_RANGE_UP                         LAN8814_EXT_PAGE_5, 541
#define LAN8814_VLAN2_VID_RANGE_EN                         LAN8814_BIT(12)
#define LAN8814_VLAN2_VID_RANGE_UP_VAL_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 11)
#define LAN8814_VLAN2_VID_RANGE_UP_VAL                     LAN8814_ENCODE_BITMASK(0, 11)
#define LAN8814_VLAN2_VID_RANGE_LO                         LAN8814_EXT_PAGE_5, 542
#define LAN8814_VLAN2_VID_RANGE_LO_VAL_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 11)
#define LAN8814_VLAN2_VID_RANGE_LO_VAL                     LAN8814_ENCODE_BITMASK(0, 11)
#define LAN8814_LLC_TYPE_ID                                LAN8814_EXT_PAGE_5, 543


//PTP RX and TX Latency values for 10Mbps/100Mbps/1000Mbps
#define LAN8814_PTP_RX_LATENCY_10                          LAN8814_EXT_PAGE_5, 544
#define LAN8814_PTP_TX_LATENCY_10                          LAN8814_EXT_PAGE_5, 545
#define LAN8814_PTP_RX_LATENCY_100                         LAN8814_EXT_PAGE_5, 546
#define LAN8814_PTP_TX_LATENCY_100                         LAN8814_EXT_PAGE_5, 547
#define LAN8814_PTP_RX_LATENCY_1000                        LAN8814_EXT_PAGE_5, 548
#define LAN8814_PTP_TX_LATENCY_1000                        LAN8814_EXT_PAGE_5, 549

//PTP Asymmetry Delay
#define LAN8814_PTP_ASYM_DLY_HI                            LAN8814_EXT_PAGE_5, 550
#define LAN8814_PTP_ASYM_DLY_LO                            LAN8814_EXT_PAGE_5, 551

//PTP Peer Delay
#define LAN8814_PTP_PEERDLY_HI                             LAN8814_EXT_PAGE_5, 552
#define LAN8814_PTP_PEERDLY_LO                             LAN8814_EXT_PAGE_5, 553

//PTP Capture Information Register
#define LAN8814_PTP_CAP_INFO                               LAN8814_EXT_PAGE_5, 554
#define LAN8814_PTP_CAP_INFO_TX_TS_CNT_THRES_F(x)          LAN8814_ENCODE_BITFIELD(x, 12, 4)
#define LAN8814_PTP_CAP_INFO_TX_TS_CNT_THRES               LAN8814_ENCODE_BITMASK(12,4)
#define LAN8814_PTP_CAP_INFO_TX_TS_CNT_F(x)                LAN8814_ENCODE_BITFIELD(x, 8, 4)
#define LAN8814_PTP_CAP_INFO_TX_TS_CNT                     LAN8814_ENCODE_BITMASK(8,4)
#define LAN8814_PTP_CAP_INFO_RX_TS_CNT_THRES_F(x)          LAN8814_ENCODE_BITFIELD(x, 4, 4)
#define LAN8814_PTP_CAP_INFO_RX_TS_CNT_THRES               LAN8814_ENCODE_BITMASK(4,4)
#define LAN8814_PTP_CAP_INFO_RX_TS_CNT_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 4)
#define LAN8814_PTP_CAP_INFO_RX_TS_CNT                     LAN8814_ENCODE_BITMASK(0,4)


//PTP TX USER MAC ADDRESS
#define LAN8814_PTP_TX_USER_MAC_HI                         LAN8814_EXT_PAGE_5, 555
#define LAN8814_PTP_TX_USER_MAC_MID                        LAN8814_EXT_PAGE_5, 556
#define LAN8814_PTP_TX_USER_MAC_LO                         LAN8814_EXT_PAGE_5, 557


//PTP TX USER IP ADDRESS REGISTERS
#define LAN8814_PTP_TX_USER_IP_ADDR_0                      LAN8814_EXT_PAGE_5, 558
#define LAN8814_PTP_TX_USER_IP_ADDR_1                      LAN8814_EXT_PAGE_5, 559
#define LAN8814_PTP_TX_USER_IP_ADDR_2                      LAN8814_EXT_PAGE_5, 560
#define LAN8814_PTP_TX_USER_IP_ADDR_3                      LAN8814_EXT_PAGE_5, 561
#define LAN8814_PTP_TX_USER_IP_ADDR_4                      LAN8814_EXT_PAGE_5, 562
#define LAN8814_PTP_TX_USER_IP_ADDR_5                      LAN8814_EXT_PAGE_5, 563
#define LAN8814_PTP_TX_USER_IP_ADDR_6                      LAN8814_EXT_PAGE_5, 564
#define LAN8814_PTP_TX_USER_IP_ADDR_7                      LAN8814_EXT_PAGE_5, 565

//PTP TX USER IP MASK REGISTERS
#define LAN8814_PTP_TX_USER_IP_MASK_0                      LAN8814_EXT_PAGE_5, 566
#define LAN8814_PTP_TX_USER_IP_MASK_1                      LAN8814_EXT_PAGE_5, 567
#define LAN8814_PTP_TX_USER_IP_MASK_2                      LAN8814_EXT_PAGE_5, 568
#define LAN8814_PTP_TX_USER_IP_MASK_3                      LAN8814_EXT_PAGE_5, 569
#define LAN8814_PTP_TX_USER_IP_MASK_4                      LAN8814_EXT_PAGE_5, 570
#define LAN8814_PTP_TX_USER_IP_MASK_5                      LAN8814_EXT_PAGE_5, 571
#define LAN8814_PTP_TX_USER_IP_MASK_6                      LAN8814_EXT_PAGE_5, 572
#define LAN8814_PTP_TX_USER_IP_MASK_7                      LAN8814_EXT_PAGE_5, 573

//PTP RX Parsing Configuration Register
#define LAN8814_PTP_RX_PARSE_CONFIG                        LAN8814_EXT_PAGE_5, 578
#define LAN8814_PTP_RX_PARSE_CONFIG_IPv6_FRAG_EN           LAN8814_BIT(15)
#define LAN8814_PTP_RX_PARSE_CONFIG_PEER_NONPEER_MIX       LAN8814_BIT(14)
#define LAN8814_PTP_RX_PARSE_CONFIG_IP_DA_PEER_NONPEER     LAN8814_BIT(13)
#define LAN8814_PTP_RX_PARSE_CONFIG_MAC_DA_PEER_NONPEER    LAN8814_BIT(12)
#define LAN8814_PTP_RX_PARSE_CONFIG_MAC_DA_EN              LAN8814_BIT(11)
#define LAN8814_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(x)       LAN8814_ENCODE_BITFIELD(x, 8, 3)
#define LAN8814_PTP_RX_PARSE_CONFIG_MAC_DA_MODE            LAN8814_ENCODE_BITMASK(8,3)
#define LAN8814_PTP_RX_PARSE_CONFIG_IPV4_FRAG_EN           LAN8814_BIT(7)
#define LAN8814_PTP_RX_PARSE_CONFIG_UDP_SPORT_EN           LAN8814_BIT(6)
#define LAN8814_PTP_RX_PARSE_CONFIG_UDP_DPORT_EN           LAN8814_BIT(5)
#define LAN8814_PTP_RX_PARSE_CONFIG_MAC_IP_CONSISTANCY     LAN8814_BIT(4)
#define LAN8814_PTP_RX_PARSE_CONFIG_ROUTING_HDR            LAN8814_BIT(3)
#define LAN8814_PTP_RX_PARSE_CONFIG_IPV6_EN                LAN8814_BIT(2)
#define LAN8814_PTP_RX_PARSE_CONFIG_IPV4_EN                LAN8814_BIT(1)
#define LAN8814_PTP_RX_PARSE_CONFIG_LAYER2_EN              LAN8814_BIT(0)

//PTP RX Parsing VLAN Configuration Register
#define LAN8814_PTP_RX_PARSE_VLAN_CONFIG                   LAN8814_EXT_PAGE_5, 579
#define LAN8814_PTP_RX_PARSE_VLAN_TAG_COUNT_F(x)           LAN8814_ENCODE_BITFIELD(x,4,3)
#define LAN8814_PTP_RX_PARSE_VLAN_TAG_COUNT                LAN8814_ENCODE_BITMASK(4,3)
#define LAN8814_PTP_RX_PARSE_VLAN_CHECK_EN                 LAN8814_BIT(2)
#define LAN8814_PTP_RX_PARSE_VLAN_VLAN2_CHECK_EN           LAN8814_BIT(1)
#define LAN8814_PTP_RX_PARSE_VLAN_VLAN1_CHECK_EN           LAN8814_BIT(0)

//PTP RX Parsing Layer2 Format Address Enable Register
#define LAN8814_PTP_RX_PARSE_L2_ADDR_EN                    LAN8814_EXT_PAGE_5, 580
#define LAN8814_PTP_RX_PARSE_L2_MAC_DA1_EN                 LAN8814_BIT(3)
#define LAN8814_PTP_RX_PARSE_L2_MAC_DA2_EN                 LAN8814_BIT(2)
#define LAN8814_PTP_RX_PARSE_L2_MAC_EN_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 2)
#define LAN8814_PTP_RX_PARSE_L2_MAC_EN                     LAN8814_ENCODE_BITMASK(0, 2)

//PTP RX Parsing IP Format Address Enable Register
#define LAN8814_PTP_RX_PARSE_IP_ADDR_EN                    LAN8814_EXT_PAGE_5, 581
#define LAN8814_PTP_RX_PARSE_IP_DA_EN                      LAN8814_BIT(13)
#define LAN8814_PTP_RX_PARSE_IP_DA1_EN                     LAN8814_BIT(12)
#define LAN8814_PTP_RX_PARSE_IP_DA2_EN                     LAN8814_BIT(11)
#define LAN8814_PTP_RX_PARSE_IP_DA3_EN                     LAN8814_BIT(10)
#define LAN8814_PTP_RX_PARSE_IP_DA4_EN                     LAN8814_BIT(9)
#define LAN8814_PTP_RX_PARSE_IP_DA5_EN                     LAN8814_BIT(8)
#define LAN8814_PTP_RX_PARSE_IPv6_UMAC_EN_F(x)             LAN8814_ENCODE_BITFIELD(x, 6, 2)
#define LAN8814_PTP_RX_PARSE_IPv6_UMAC_EN                  LAN8814_ENCODE_BITMASK(6, 2)
#define LAN8814_PTP_RX_PARSE_IPv6_IP_EN_F(x)               LAN8814_ENCODE_BITFIELD(x, 4, 2)
#define LAN8814_PTP_RX_PARSE_IPv6_IP_EN                    LAN8814_ENCODE_BITMASK(4, 2)
#define LAN8814_PTP_RX_PARSE_IPv4_UMAC_EN_F(x)             LAN8814_ENCODE_BITFIELD(x, 2, 2)
#define LAN8814_PTP_RX_PARSE_IPv4_UMAC_EN                  LAN8814_ENCODE_BITMASK(2, 2)
#define LAN8814_PTP_RX_PARSE_IPv4_IP_EN_F(x)               LAN8814_ENCODE_BITFIELD(x, 0, 2)
#define LAN8814_PTP_RX_PARSE_IPv4_IP_EN                    LAN8814_ENCODE_BITMASK(0, 2)

//PTP RX Parsing UDP Source Port Register
#define LAN8814_PTP_RX_PARSE_UDP_SRC_PORT                  LAN8814_EXT_PAGE_5, 582

//PTP RX Parsing UDP Destination Port Register
#define LAN8814_PTP_RX_PARSE_UDP_DEST_PORT                 LAN8814_EXT_PAGE_5, 583

//PTP RX Version Register
#define LAN8814_PTP_RX_VERSION                             LAN8814_EXT_PAGE_5, 584
#define LAN8814_PTP_RX_VERSION_UP_F(x)                     LAN8814_ENCODE_BITFIELD(x, 8, 8)
#define LAN8814_PTP_RX_VERSION_UP                          LAN8814_ENCODE_BITMASK(8,8)
#define LAN8814_PTP_RX_VERSION_LOW_F(x)                    LAN8814_ENCODE_BITFIELD(x, 0, 8)
#define LAN8814_PTP_RX_VERSION_LOW                         LAN8814_ENCODE_BITMASK(0,8)

//PTP RX Domain / Domain Range Lower Register
#define LAN8814_PTP_RX_DOMAIN_DOMAIN_LO                    LAN8814_EXT_PAGE_5, 585
#define LAN8814_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_EN           LAN8814_BIT(15)
#define LAN8814_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_LO_F(x)      LAN8814_ENCODE_BITFIELD(x, 0, 8)
#define LAN8814_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_LO           LAN8814_ENCODE_BITMASK(0, 8)

//PTP RX Domain Mask / Domain Range Upper Register
#define LAN8814_PTP_RX_DOMAIN_MASK_DOMAIN_UP               LAN8814_EXT_PAGE_5, 586

//PTP RX SdoId / SdoId Range Lower Register
#define LAN8814_PTP_RX_SDOID_SDOID_LO                      LAN8814_EXT_PAGE_5, 587
#define LAN8814_PTP_RX_SDOID_SDOID_LO_RANGE_EN             LAN8814_BIT(15)
#define LAN8814_PTP_RX_SDOID_SDOID_LO_RANGE_LO_F(x)        LAN8814_ENCODE_BITFIELD(x, 0, 8)
#define LAN8814_PTP_RX_SDOID_SDOID_LO_RANGE_LO             LAN8814_ENCODE_BITMASK(0, 8)

//PTP RX SdoId Mask / SdoId Range Upper Register
#define LAN8814_PTP_RX_SDOID_MASK_SDOID_UP                 LAN8814_EXT_PAGE_5, 588

//PTP RX Timestamp Enable Register
#define LAN8814_PTP_RX_TIMESTAMP_EN                        LAN8814_EXT_PAGE_5, 589

//PTP RX Timestamp Configuration Register
#define LAN8814_PTP_RX_TIMESTAMP_CONFIG                    LAN8814_EXT_PAGE_5, 590
#define LAN8814_PTP_RX_PTP_UDPV6_ZERO_CHKSUM_EN            LAN8814_BIT(3)
#define LAN8814_PTP_RX_PTP_ALT_MASTER_EN                   LAN8814_BIT(2)
#define LAN8814_PTP_RX_PTP_UDP_CHKSUM_DIS                  LAN8814_BIT(1)
#define LAN8814_PTP_RX_PTP_FCS_DIS                         LAN8814_BIT(0)

//PTP RX Modification Register
#define LAN8814_PTP_RX_MOD                                 LAN8814_EXT_PAGE_5, 591
#define LAN8814_PTP_RX_MOD_PTP_BAD_IPV6_FORCE_FCS_DIS      LAN8814_BIT(4)
#define LAN8814_PTP_RX_MOD_PTP_BAD_IPV4_FORCE_FCS_DIS      LAN8814_BIT(3)
#define LAN8814_PTP_RX_MOD_PTP_INSERT_TS_SEC_EN            LAN8814_BIT(2)
#define LAN8814_PTP_RX_MOD_PTP_INSERT_TS_32BIT             LAN8814_BIT(1)
#define LAN8814_PTP_RX_MOD_PTP_INSERT_TS_EN                LAN8814_BIT(0)


//PTP RX Reserved Bytes Configuration Register
#define LAN8814_PTP_RX_RSVD_BYTE_CFG                       LAN8814_EXT_PAGE_5, 592

//PTP RX Tail Tag Register
#define LAN8814_PTP_RX_TAIL_TAG                            LAN8814_EXT_PAGE_5, 593
#define LAN8814_PTP_RX_TAIL_TAG_ER_FORWARD                 LAN8814_BIT(8)
#define LAN8814_PTP_RX_TAIL_TAG_INSERT_IFG_F(x)            LAN8814_ENCODE_BITFIELD(x, 4, 3)
#define LAN8814_PTP_RX_TAIL_TAG_INSERT_IFG(x)              LAN8814_ENCODE_BITMASK(x, 4, 3)
#define LAN8814_PTP_RX_TAIL_TAG_INSERT                     LAN8814_BIT(3)
#define LAN8814_PTP_RX_TAIL_TAG_ALL                        LAN8814_BIT(2)
#define LAN8814_PTP_RX_TAIL_TAG_ALL_1588                   LAN8814_BIT(1)
#define LAN8814_PTP_RX_TAIL_TAG_EN                         LAN8814_BIT(0)

//PTP RX Correction Field Modification Enable Register
#define LAN8814_PTP_RX_CF_MOD_EN                           LAN8814_EXT_PAGE_5, 594

//PTP RX Correction Field Configuration Register
#define LAN8814_PTP_RX_CF_CFG                              LAN8814_EXT_PAGE_5, 595
#define LAN8814_PTP_RX_PTP_MAX_CF_DIS                      LAN8814_BIT(1)
#define LAN8814_PTP_RX_PTP_CF_METHOD                       LAN8814_BIT(0)

//PTP RX Ingress Timestamp
#define LAN8814_PTP_RX_TS_NS_HI                            LAN8814_EXT_PAGE_5, 596
#define LAN8814_PTP_RX_TS_NS_PTP_TX_TS_VALID               LAN8814_BIT(15)
#define LAN8814_PTP_RX_TS_NS_HI_VAL_F(x)                   LAN8814_ENCODE_BITFIELD(x, 0, 14)
#define LAN8814_PTP_RX_TS_NS_HI_VAL                        LAN8814_ENCODE_BITMASK(0,14)
#define LAN8814_PTP_RX_TS_NS_LO                            LAN8814_EXT_PAGE_5, 597
#define LAN8814_PTP_RX_TS_SEC_HI                           LAN8814_EXT_PAGE_5, 598
#define LAN8814_PTP_RX_TS_SEC_LO                           LAN8814_EXT_PAGE_5, 599

//PTP RX Message Header Registers
#define LAN8814_PTP_RX_MSG_HEADER1                         LAN8814_EXT_PAGE_5, 600
#define LAN8814_PTP_RX_MSG_HEADER2                         LAN8814_EXT_PAGE_5, 601

//PTP RX Pdelay_Req Ingress Timestamp
#define LAN8814_PTP_RX_PDREQ_SEC_HI                        LAN8814_EXT_PAGE_5, 602
#define LAN8814_PTP_RX_PDREQ_SEC_MID                       LAN8814_EXT_PAGE_5, 603
#define LAN8814_PTP_RX_PDREQ_SEC_LOW                       LAN8814_EXT_PAGE_5, 604
#define LAN8814_PTP_RX_PDREQ_NS_HI                         LAN8814_EXT_PAGE_5, 605
#define LAN8814_F_PTP_RX_PDREQ_AUTO_UPDATE                 LAN8814_BIT(15)
#define LAN8814_PTP_RX_PDREQ_NS_LO                         LAN8814_EXT_PAGE_5, 606

//PTP RX Raw Ingress Time Seconds Register
#define LAN8814_PTP_RX_RAW_TS_SEC                          LAN8814_EXT_PAGE_5, 607
#define LAN8814_PTP_RX_RAW_TS_NS_HI                        LAN8814_EXT_PAGE_5, 608
#define LAN8814_PTP_RX_RAW_TS_NS_LO                        LAN8814_EXT_PAGE_5, 609

//PTP RX Checksum Dropped Count
#define LAN8814_PTP_RX_CHKSUM_DROPPED_CNT_HI               LAN8814_EXT_PAGE_5, 610
#define LAN8814_PTP_RX_CHKSUM_DROPPED_CNT_LO               LAN8814_EXT_PAGE_5, 611

//PTP RX Frames Modified Count
#define LAN8814_PTP_RX_FRMS_MOD_CNT_HI                     LAN8814_EXT_PAGE_5, 612
#define LAN8814_PTP_RX_FRMS_MOD_CNT_LO                     LAN8814_EXT_PAGE_5, 613

//PTP TX Parsing Configuration Register
#define LAN8814_PTP_TX_PARSE_CONFIG                        LAN8814_EXT_PAGE_5, 642
#define LAN8814_PTP_TX_PARSE_CONFIG_IPv6_FRAG_EN           LAN8814_BIT(15)
#define LAN8814_PTP_TX_PARSE_CONFIG_PEER_NONPEER_MIX       LAN8814_BIT(14)
#define LAN8814_PTP_TX_PARSE_CONFIG_IP_DA_PEER_NONPEER     LAN8814_BIT(13)
#define LAN8814_PTP_TX_PARSE_CONFIG_MAC_DA_PEER_NONPEER    LAN8814_BIT(12)
#define LAN8814_PTP_TX_PARSE_CONFIG_MAC_DA_EN              LAN8814_BIT(11)
#define LAN8814_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(x)       LAN8814_ENCODE_BITFIELD(x, 8, 3)
#define LAN8814_PTP_TX_PARSE_CONFIG_MAC_DA_MODE            LAN8814_ENCODE_BITMASK(8,3)
#define LAN8814_PTP_TX_PARSE_CONFIG_IPV4_FRAG_EN           LAN8814_BIT(7)
#define LAN8814_PTP_TX_PARSE_CONFIG_UDP_SPORT_EN           LAN8814_BIT(6)
#define LAN8814_PTP_TX_PARSE_CONFIG_UDP_DPORT_EN           LAN8814_BIT(5)
#define LAN8814_PTP_TX_PARSE_CONFIG_MAC_IP_CONSISTANCY     LAN8814_BIT(4)
#define LAN8814_PTP_TX_PARSE_CONFIG_ROUTING_HDR            LAN8814_BIT(3)
#define LAN8814_PTP_TX_PARSE_CONFIG_IPV6_EN                LAN8814_BIT(2)
#define LAN8814_PTP_TX_PARSE_CONFIG_IPV4_EN                LAN8814_BIT(1)
#define LAN8814_PTP_TX_PARSE_CONFIG_LAYER2_EN              LAN8814_BIT(0)


//PTP TX Parsing VLAN Configuration Register
#define LAN8814_PTP_TX_PARSE_VLAN_CONFIG                   LAN8814_EXT_PAGE_5, 643
#define LAN8814_PTP_TX_PARSE_VLAN_TAG_COUNT_F(x)           LAN8814_ENCODE_BITFIELD(x,4,3)
#define LAN8814_PTP_TX_PARSE_VLAN_TAG_COUNT                LAN8814_ENCODE_BITMASK(4,3)
#define LAN8814_PTP_TX_PARSE_VLAN_CHECK_EN                 LAN8814_BIT(2)
#define LAN8814_PTP_TX_PARSE_VLAN_VLAN2_CHECK_EN           LAN8814_BIT(1)
#define LAN8814_PTP_TX_PARSE_VLAN_VLAN1_CHECK_EN           LAN8814_BIT(0)

//PTP TX Parsing Layer2 Format Address Enable Register
#define LAN8814_PTP_TX_PARSE_L2_ADDR_EN                    LAN8814_EXT_PAGE_5, 644
#define LAN8814_PTP_TX_PARSE_L2_MAC_DA1_EN                 LAN8814_BIT(3)
#define LAN8814_PTP_TX_PARSE_L2_MAC_DA2_EN                 LAN8814_BIT(2)
#define LAN8814_PTP_TX_PARSE_L2_MAC_EN_F(x)                LAN8814_ENCODE_BITFIELD(x, 0, 2)
#define LAN8814_PTP_TX_PARSE_L2_MAC_EN                     LAN8814_ENCODE_BITMASK(0, 2)

//PTP TX Parsing IP Format Address Enable Register
#define LAN8814_PTP_TX_PARSE_IP_ADDR_EN                    LAN8814_EXT_PAGE_5, 645
#define LAN8814_PTP_TX_PARSE_IP_DA_EN                      LAN8814_BIT(13)
#define LAN8814_PTP_TX_PARSE_IP_DA1_EN                     LAN8814_BIT(12)
#define LAN8814_PTP_TX_PARSE_IP_DA2_EN                     LAN8814_BIT(11)
#define LAN8814_PTP_TX_PARSE_IP_DA3_EN                     LAN8814_BIT(10)
#define LAN8814_PTP_TX_PARSE_IP_DA4_EN                     LAN8814_BIT(9)
#define LAN8814_PTP_TX_PARSE_IP_DA5_EN                     LAN8814_BIT(8)
#define LAN8814_PTP_TX_PARSE_IPv6_UMAC_EN_F(x)             LAN8814_ENCODE_BITFIELD(x, 6, 2)
#define LAN8814_PTP_TX_PARSE_IPv6_UMAC_EN                  LAN8814_ENCODE_BITMASK(6, 2)
#define LAN8814_PTP_TX_PARSE_IPv6_IP_EN_F(x)               LAN8814_ENCODE_BITFIELD(x, 4, 2)
#define LAN8814_PTP_TX_PARSE_IPv6_IP_EN                    LAN8814_ENCODE_BITMASK(4, 2)
#define LAN8814_PTP_TX_PARSE_IPv4_UMAC_EN_F(x)             LAN8814_ENCODE_BITFIELD(x, 2, 2)
#define LAN8814_PTP_TX_PARSE_IPv4_UMAC_EN                  LAN8814_ENCODE_BITMASK(2, 2)
#define LAN8814_PTP_TX_PARSE_IPv4_IP_EN_F(x)               LAN8814_ENCODE_BITFIELD(x, 0, 2)
#define LAN8814_PTP_TX_PARSE_IPv4_IP_EN                    LAN8814_ENCODE_BITMASK(0, 2)
//PTP TX Parsing UDP Source Port Register
#define LAN8814_PTP_TX_PARSE_UDP_SRC_PORT                  LAN8814_EXT_PAGE_5, 646

//PTP TX Parsing UDP Destination Port Register
#define LAN8814_PTP_TX_PARSE_UDP_DEST_PORT                 LAN8814_EXT_PAGE_5, 647

// PTP TX Version Register
#define LAN8814_PTP_TX_VERSION                             LAN8814_EXT_PAGE_5, 648

// PTP TX Domain / Domain Range Lower Register
#define LAN8814_PTP_TX_DOMAIN_DOMAIN_LO                    LAN8814_EXT_PAGE_5, 649
#define LAN8814_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_EN           LAN8814_BIT(15)
#define LAN8814_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_LO_F(x)      LAN8814_ENCODE_BITFIELD(x, 0, 8)
#define LAN8814_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_LO           LAN8814_ENCODE_BITMASK(0, 8)

// PTP TX Domain Mask / Domain Range Upper Register
#define LAN8814_PTP_TX_DOMAIN_MASK_DOMAIN_UP               LAN8814_EXT_PAGE_5, 650

// PTP TX SdoId / SdoId Range Lower Register
#define LAN8814_PTP_TX_SDOID_SDOID_LO                      LAN8814_EXT_PAGE_5, 651
#define LAN8814_PTP_TX_SDOID_SDOID_LO_RANGE_EN             LAN8814_BIT(15)
#define LAN8814_PTP_TX_SDOID_SDOID_LO_RANGE_LO_F(x)        LAN8814_ENCODE_BITFIELD(x, 0, 8)
#define LAN8814_PTP_TX_SDOID_SDOID_LO_RANGE_LO             LAN8814_ENCODE_BITMASK(0, 8)

// PTP TX SdoId Mask / SdoId Range Upper Register
#define LAN8814_PTP_TX_SDOID_MASK_SDOID_UP                 LAN8814_EXT_PAGE_5, 652

// PTP TX Timestamp Enable Register
#define LAN8814_PTP_TX_TIMESTAMP_EN                        LAN8814_EXT_PAGE_5, 653

// PTP TX Timestamp Configuration Register
#define LAN8814_PTP_TX_TIMESTAMP_CONFIG                    LAN8814_EXT_PAGE_5, 654
#define LAN8814_PTP_TX_PTP_UDPV6_ZERO_CHKSUM_EN            LAN8814_BIT(3)
#define LAN8814_PTP_TX_PTP_ALT_MASTER_EN                   LAN8814_BIT(2)
#define LAN8814_PTP_TX_PTP_UDP_CHKSUM_DIS                  LAN8814_BIT(1)
#define LAN8814_PTP_TX_PTP_FCS_DIS                         LAN8814_BIT(0)

// PTP TX Modification Register
#define LAN8814_PTP_TX_MOD                                 LAN8814_EXT_PAGE_5, 655
#define LAN8814_PTP_TX_MOD_CLR_1_RSVRD                     LAN8814_BIT(15)
#define LAN8814_PTP_TX_MOD_CLR_4_RSVRD                     LAN8814_BIT(14)
#define LAN8814_PTP_TX_MOD_PDRESP_TA_INSERT                LAN8814_BIT(13)
#define LAN8814_PTP_TX_MOD_SYNC_TS_INSERT                  LAN8814_BIT(12)
#define LAN8814_PTP_TX_MOD_FOLLOWUP_TS_INSERT              LAN8814_BIT(11)
#define LAN8814_PTP_TX_MOD_PDRESP_TS_INSERT                LAN8814_BIT(10)
#define LAN8814_PTP_TX_MOD_PDRESPFOLLOWUP_TS_INSERT        LAN8814_BIT(9)
#define LAN8814_PTP_TX_MOD_PTP_BAD_IPV6_FORCE_FCS_DIS      LAN8814_BIT(4)
#define LAN8814_PTP_TX_MOD_PTP_BAD_IPV4_FORCE_FCS_DIS      LAN8814_BIT(3)



// PTP TX Reserved Bytes Configuration Register
#define LAN8814_PTP_TX_RSVD_BYTE_CFG                       LAN8814_EXT_PAGE_5, 656

// PTP TX Tail Tag Register
#define LAN8814_PTP_TX_TAIL_TAG                            LAN8814_EXT_PAGE_5, 657

// PTP TX Correction Field Modification Enable Register
#define LAN8814_PTP_TX_CF_MOD_EN                           LAN8814_EXT_PAGE_5, 658

// PTP TX Correction Field Configuration Register
#define LAN8814_PTP_TX_CF_CFG                              LAN8814_EXT_PAGE_5, 659
#define LAN8814_PTP_TX_PTP_CF_32BIT                        LAN8814_BIT(2)
#define LAN8814_PTP_TX_PTP_MAX_CF_DIS                      LAN8814_BIT(1)
#define LAN8814_PTP_TX_PTP_CF_METHOD                       LAN8814_BIT(0)


// PTP TX Egress Timestamp
#define LAN8814_PTP_TX_TS_NS_HI                            LAN8814_EXT_PAGE_5, 660
#define LAN8814_PTP_TX_TS_NS_PTP_TX_TS_VALID               LAN8814_BIT(15)
#define LAN8814_PTP_TX_TS_NS_HI_VAL_F(x)                   LAN8814_ENCODE_BITFIELD(x, 0, 14)
#define LAN8814_PTP_TX_TS_NS_HI_VAL                        LAN8814_ENCODE_BITMASK(0,14)

#define LAN8814_PTP_TX_TS_NS_LO                            LAN8814_EXT_PAGE_5, 661
#define LAN8814_PTP_TX_TS_SEC_HI                           LAN8814_EXT_PAGE_5, 662
#define LAN8814_PTP_TX_TS_SEC_LO                           LAN8814_EXT_PAGE_5, 663

// PTP TX Message Header
#define LAN8814_PTP_TX_MSG_HEADER1                         LAN8814_EXT_PAGE_5, 664
#define LAN8814_PTP_TX_MSG_HEADER2                         LAN8814_EXT_PAGE_5, 665

// PTP TX Sync Egress Timestamp
#define LAN8814_PTP_TX_SYNC_SEC_HI                         LAN8814_EXT_PAGE_5, 666
#define LAN8814_PTP_TX_SYNC_SEC_MID                        LAN8814_EXT_PAGE_5, 667
#define LAN8814_PTP_TX_SYNC_SEC_LOW                        LAN8814_EXT_PAGE_5, 668
#define LAN8814_PTP_TX_SYNC_NS_HI                          LAN8814_EXT_PAGE_5, 669
#define LAN8814_PTP_TX_SYNC_NS_HI_TS_VALID                 LAN8814_BIT(15)
#define LAN8814_PTP_TX_SYNC_NS_HI_VAL_F(x)                 LAN8814_ENCODE_BITFIELD(x, 0, 14)
#define LAN8814_PTP_TX_SYNC_NS_HI_VAL                      LAN8814_ENCODE_BITMASK(0,14)
#define LAN8814_PTP_TX_SYNC_NS_LO                          LAN8814_EXT_PAGE_5, 670

// PTP TX Pdelay_Resp Egress Timestamp
#define LAN8814_PTP_TX_PDRESP_SEC_HI                       LAN8814_EXT_PAGE_5, 671
#define LAN8814_PTP_TX_PDRESP_SEC_MID                      LAN8814_EXT_PAGE_5, 672
#define LAN8814_PTP_TX_PDRESP_SEC_LOW                      LAN8814_EXT_PAGE_5, 673
#define LAN8814_PTP_TX_PDRESP_NS_HI                        LAN8814_EXT_PAGE_5, 674
#define LAN8814_PTP_TX_PDRESP_NS_HI_TS_VALID               LAN8814_BIT(15)
#define LAN8814_PTP_TX_PDRESP_NS_HI_VAL_F(x)               LAN8814_ENCODE_BITFIELD(x, 0, 14)
#define LAN8814_PTP_TX_PDRESP_NS_HI_VAL                    LAN8814_ENCODE_BITMASK(0,14)
#define LAN8814_PTP_TX_PDRESP_NS_LO                        LAN8814_EXT_PAGE_5, 675

// PTP TX Raw Egress Time Seconds Register - 16bits
#define LAN8814_PTP_TX_RAW_TS_SEC                          LAN8814_EXT_PAGE_5, 676

// PTP TX Raw Egress Time Nanoseconds Register
#define LAN8814_PTP_TX_RAW_TS_NS_HI                        LAN8814_EXT_PAGE_5, 677
#define LAN8814_PTP_TX_RAW_TS_NS_LO                        LAN8814_EXT_PAGE_5, 678

// PTP TX Checksum Dropped Counter
#define LAN8814_PTP_TX_CHKSUM_DROPPED_CNT_HI               LAN8814_EXT_PAGE_5, 679
#define LAN8814_PTP_TX_CHKSUM_DROPPED_CNT_LO               LAN8814_EXT_PAGE_5, 680

// PTP TX Frames Modified Counter
#define LAN8814_PTP_TX_FRMS_MOD_CNT_HI                     LAN8814_EXT_PAGE_5, 681
#define LAN8814_PTP_TX_FRMS_MOD_CNT_LO                     LAN8814_EXT_PAGE_5, 682

// TSU General Configuration Register
#define LAN8814_PTP_TSU_GEN_CONF                           LAN8814_EXT_PAGE_5, 704
#define LAN8814_PTP_TSU_GEN_CONF_TS_CRC_PKT                LAN8814_BIT(2)
#define LAN8814_PTP_TSU_GEN_CONF_PREEMPTION_EN             LAN8814_BIT(1)
#define LAN8814_PTP_TSU_GEN_CONF_EN                        LAN8814_BIT(0)

// TSU Hard Reset Register
#define LAN8814_PTP_TSU_HARD_RESET                         LAN8814_EXT_PAGE_5, 705
#define LAN8814_PTP_TSU_HARD_RESET_CMD                     LAN8814_BIT(0)

// TSU Soft Reset Register
#define LAN8814_PTP_TSU_SOFT_RESET                         LAN8814_EXT_PAGE_5, 706
#define LAN8814_PTP_TSU_SOFT_RESET_CMD                     LAN8814_BIT(0)

// PTP PCH Format Mismatch Register
#define LAN8814_PTP_PCH_FORMAT_MISMATCH                    LAN8814_EXT_PAGE_5, 707
#define LAN8814_PTP_PCH_FORMAT_MISMATCH_PKT_TYPE           LAN8814_BIT(3)
#define LAN8814_PTP_PCH_FORMAT_MISMATCH_EXT_TYPE           LAN8814_BIT(2)
#define LAN8814_PTP_PCH_FORMAT_MISMATCH_CRC_ERR            LAN8814_BIT(1)
#define LAN8814_PTP_PCH_FORMAT_MISMATCH_SUB_PORT_ID        LAN8814_BIT(0)


#endif
