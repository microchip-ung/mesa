// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_INDY_TS_REGISTERS_H
#define _MEPA_INDY_TS_REGISTERS_H

// EP-4 Chip 1588 Common Registers

//1588 PLL Registers
#define INDY_1588_PLL_RESET                                 INDY_EXT_PAGE_4, 320
#define INDY_1588_PLL_RESET_EN                              INDY_BIT(0)
#define INDY_1588_PLL_BYPASS                                INDY_EXT_PAGE_4, 321
#define INDY_1588_PLL_BYPASS_EN                             INDY_BIT(0)
#define INDY_1588_PLL_STATUS                                INDY_EXT_PAGE_4, 322
#define INDY_1588_PLL_DIVEDER                               INDY_EXT_PAGE_4, 323
#define INDY_1588_PLL_DIVR_F(x)                             INDY_ENCODE_BITFIELD(x, 10, 14)
#define INDY_1588_PLL_DIVR                                  INDY_ENCODE_BITMASK(10, 14)
#define INDY_1588_PLL_DIVF_F(x)                             INDY_ENCODE_BITFIELD(x, 3, 9)
#define INDY_1588_PLL_DIVF                                  INDY_ENCODE_BITMASK(3, 9)
#define INDY_1588_PLL_DIVQ_F(x)                             INDY_ENCODE_BITFIELD(x, 0, 2)
#define INDY_1588_PLL_DIVQ                                  INDY_ENCODE_BITMASK(0, 2)
#define INDY_1588_PLL_FILTER                                INDY_EXT_PAGE_4, 323
#define INDY_1588_PLL_FILTER_RANGE_F(x)                     INDY_ENCODE_BITFIELD(x, 0,3)
#define INDY_1588_PLL_FILTER_RANGE                          INDY_ENCODE_BITMASK(0, 3)

// PTP Common Command and Control Register
#define INDY_PTP_CMD_CTL                                    INDY_EXT_PAGE_4, 512
#define INDY_PTP_CMD_CTL_LTC_DLYD_STEP_SECONDS              INDY_BIT(15)
#define INDY_PTP_CMD_CTL_LTC_DLYD_LOAD                      INDY_BIT(14)
#define INDY_PTP_CMD_CTL_LTC_TARGET_READ                    INDY_BIT(13)
#define INDY_PTP_CMD_CTL_MANUAL_CAPTURE_SEL_F(x)            INDY_ENCODE_BITFIELD(x, 9, 3)
#define INDY_PTP_CMD_CTL_MANUAL_CAPTURE_SEL                 INDY_ENCODE_BITMASK(9, 3)
#define INDY_PTP_CMD_CTL_MANUAL_CAPTURE                     INDY_BIT(8)
#define INDY_PTP_CMD_CTL_LTC_TEMP_RATE                      INDY_BIT(7)
#define INDY_PTP_CMD_CTL_LTC_STEP_NANOSECONDS               INDY_BIT(6)
#define INDY_PTP_CMD_CTL_LTC_STEP_SECONDS                   INDY_BIT(5)
#define INDY_PTP_CMD_CTL_LTC_LOAD                           INDY_BIT(4)
#define INDY_PTP_CMD_CTL_LTC_READ                           INDY_BIT(3)
#define INDY_PTP_CMD_CTL_LTC_TEMP_RATE_SEL                  INDY_BIT(2)
#define INDY_PTP_CMD_CTL_ENABLE                             INDY_BIT(1)
#define INDY_PTP_CMD_CTL_DISABLE                            INDY_BIT(0)

// PTP General Configuration Register
#define INDY_PTP_GENERAL_CONFIG                             INDY_EXT_PAGE_4, 513
#define INDY_PTP_GENERAL_CONFIG_LTC_EVENT_B_F(x)            INDY_ENCODE_BITFIELD(x, 8, 4)
#define INDY_PTP_GENERAL_CONFIG_LTC_EVENT_B                 INDY_ENCODE_BITMASK(8, 4)
#define INDY_PTP_GENERAL_CONFIG_LTC_EVENT_A_F(x)            INDY_ENCODE_BITFIELD(x, 4, 4)
#define INDY_PTP_GENERAL_CONFIG_LTC_EVENT_A                 INDY_ENCODE_BITMASK(4, 4)
#define INDY_PTP_GENERAL_CONFIG_LTC_EVENT_POL_B             INDY_BIT(3)
#define INDY_PTP_GENERAL_CONFIG_RELOAD_ADD_B                INDY_BIT(2)
#define INDY_PTP_GENERAL_CONFIG_LTC_EVENT_POL_A             INDY_BIT(1)
#define INDY_PTP_GENERAL_CONFIG_RELOAD_ADD_A                INDY_BIT(0)


// PTP Reference Clock Configuration Register
#define INDY_PTP_REF_CLK_CFG                                INDY_EXT_PAGE_4, 514
#define INDY_PTP_REF_CLK_CFG_EPPS_ENABLE                    INDY_BIT(13)
#define INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE_F(x)            INDY_ENCODE_BITFIELD(x, 10, 3)
#define INDY_PTP_REF_CLK_CFG_REF_CLK_SOURCE                 INDY_ENCODE_BITMASK(10, 3)
#define INDY_PTP_REF_CLK_CFG_REF_CLK_PERIOD_OVERRIDE        INDY_BIT(9)
#define INDY_PTP_REF_CLK_CFG_REF_CLK_PERIOD_F(x)            INDY_ENCODE_BITFIELD(x, 0, 9)
#define INDY_PTP_REF_CLK_CFG_REF_CLK_PERIOD                 INDY_ENCODE_BITMASK(0, 9)

// PTP Common Interrupt Status Register
#define INDY_PTP_COMMON_INT_STS                             INDY_EXT_PAGE_4, 515

// PTP Common Interrupt Enable Register
#define INDY_PTP_COMMON_INT_EN                              INDY_EXT_PAGE_4,516

// PTP LTC Set Seconds
#define INDY_PTP_LTC_SET_SEC_HI                             INDY_EXT_PAGE_4, 517
#define INDY_PTP_LTC_SET_SEC_MID                            INDY_EXT_PAGE_4, 518
#define INDY_PTP_LTC_SET_SEC_LO                             INDY_EXT_PAGE_4, 519

// PTP LTC Set Nanoseconds
#define INDY_PTP_LTC_SET_NS_HI                              INDY_EXT_PAGE_4, 520
#define INDY_PTP_LTC_SET_NS_LO                              INDY_EXT_PAGE_4, 521

// PTP LTC Set Sub-Nanoseconds
#define INDY_PTP_LTC_SET_SUBNS_HI                           INDY_EXT_PAGE_4, 522
#define INDY_PTP_LTC_SET_SUBNS_LO                           INDY_EXT_PAGE_4, 523

// PTP LTC Rate Adjustment High Register
#define INDY_PTP_LTC_RATE_ADJ_HI                            INDY_EXT_PAGE_4, 524
#define INDY_PTP_LTC_RATE_ADJ_HI_DIR                        INDY_BIT(15)
#define INDY_PTP_LTC_RATE_ADJ_HI_VALUE_F(x)                 INDY_ENCODE_BITFIELD(x, 0, 13)
#define INDY_PTP_LTC_RATE_ADJ_HI_VALUE                      INDY_ENCODE_BITMASK(0, 13)


// PTP LTC Rate Adjustment Low Register
#define INDY_PTP_LTC_RATE_ADJ_LO                            INDY_EXT_PAGE_4, 525

// PTP LTC Temporary Rate Adjustment High Register
#define INDY_PTP_LTC_TEMP_RATE_ADJ_HI                       INDY_EXT_PAGE_4, 526

// PTP LTC Temporary Rate Adjustment Low Register
#define INDY_PTP_LTC_TEMP_RATE_ADJ_LO                       INDY_EXT_PAGE_4, 527

// PTP LTC Temporary Rate Duration High Register
#define INDY_PTP_LTC_TEMP_RATE_DURATION_HI                  INDY_EXT_PAGE_4, 528

// PTP LTC Temporary Rate Duration Low Register
#define INDY_PTP_LTC_TEMP_RATE_DURATION_LO                  INDY_EXT_PAGE_4, 529

// PTP LTC Step Adjustment
#define INDY_PTP_LTC_STEP_ADJ_HI                            INDY_EXT_PAGE_4, 530
#define INDY_PTP_LTC_STEP_ADJ_DIR                           INDY_BIT(15)
#define INDY_PTP_LTC_STEP_ADJ_HI_VALUE_F(x)                 INDY_ENCODE_BITFIELD(x, 0, 13)
#define INDY_PTP_LTC_STEP_ADJ_HI_VALUE                      INDY_ENCODE_BITMASK(0, 13)

#define INDY_PTP_LTC_STEP_ADJ_LO                            INDY_EXT_PAGE_4, 531

// PTP LTC External Adjustment Configuration Register
#define INDY_PTP_LTC_EXT_ADJ_CFG                            INDY_EXT_PAGE_4, 532
#define INDY_PTP_LTC_EXT_ADJ_GPIO_EPPS_SEL                  INDY_BIT(6)
#define INDY_PTP_LTC_EXT_ADJ_SERIAL_TOD_EN                  INDY_BIT(5)
#define INDY_PTP_LTC_EXT_ADJ_MODE                           INDY_BIT(4)
#define INDY_PTP_LTC_EXT_ADJ_TEMP_RATE                      INDY_BIT(3)
#define INDY_PTP_LTC_EXT_ADJ_STEP_NSEC_EN                   INDY_BIT(2)
#define INDY_PTP_LTC_EXT_ADJ_STEP_SEC_EN                    INDY_BIT(1)
#define INDY_PTP_LTC_EXT_ADJ_LOAD_EN                        INDY_BIT(0)

// PTP LTC Target x Seconds High Register
#define INDY_PTP_LTC_TARGET_SEC_HI_A                        INDY_EXT_PAGE_4, 533
#define INDY_PTP_LTC_TARGET_SEC_LO_A                        INDY_EXT_PAGE_4, 534

// PTP LTC Target x Nanoseconds High Register
#define INDY_PTP_LTC_TARGET_NS_HI_A                         INDY_EXT_PAGE_4, 535
#define INDY_PTP_LTC_TARGET_NS_LO_A                         INDY_EXT_PAGE_4, 536

// PTP LTC Target x Reload / Add Seconds High Register
#define INDY_PTP_LTC_TARGET_RELOAD_SEC_HI_A                 INDY_EXT_PAGE_4, 537
#define INDY_PTP_LTC_TARGET_RELOAD_SEC_LO_A                 INDY_EXT_PAGE_4, 538
#define INDY_PTP_LTC_TARGET_RELOAD_NS_HI_A                  INDY_EXT_PAGE_4, 539
#define INDY_PTP_LTC_TARGET_RELOAD_NS_LO_A                  INDY_EXT_PAGE_4, 540

// PTP LTC Target x Actual Nanoseconds High Register
#define INDY_PTP_LTC_TARGET_ACT_NS_HI_A                     INDY_EXT_PAGE_4, 541
#define INDY_PTP_LTC_TARGET_ACT_NS_LO_A                     INDY_EXT_PAGE_4, 542

// PTP LTC Target x Seconds High Register
#define INDY_PTP_LTC_TARGET_SEC_HI_B                        INDY_EXT_PAGE_4, 543

// PTP LTC Target x Seconds Low Register
#define INDY_PTP_LTC_TARGET_SEC_LO_B                        INDY_EXT_PAGE_4, 544

// PTP LTC Target x Nanoseconds High Register
#define INDY_PTP_LTC_TARGET_NS_HI_B                         INDY_EXT_PAGE_4, 545

// PTP LTC Target x Nanoseconds Low Register
#define INDY_PTP_LTC_TARGET_NS_LO_B                         INDY_EXT_PAGE_4, 546

// PTP LTC Target x Reload / Add Seconds High Register
#define INDY_PTP_LTC_TARGET_RELOAD_SEC_HI_B                 INDY_EXT_PAGE_4, 547

// PTP LTC Target x Reload / Add Seconds Low Register
#define INDY_PTP_LTC_TARGET_RELOAD_SEC_LO_B                 INDY_EXT_PAGE_4, 548

// PTP LTC Target x Reload / Add Nanoseconds High Register
#define INDY_PTP_LTC_TARGET_RELOAD_NS_HI_B                  INDY_EXT_PAGE_4, 549

// PTP LTC Target x Reload / Add Nanoseconds Low Register
#define INDY_PTP_LTC_TARGET_RELOAD_NS_LO_B                  INDY_EXT_PAGE_4, 550

// PTP LTC Target x Actual Nanoseconds High Register
#define INDY_PTP_LTC_TARGET_ACT_NS_HI_B                     INDY_EXT_PAGE_4, 551

// PTP LTC Target x Actual Nanoseconds Low Register
#define INDY_PTP_LTC_TARGET_ACT_NS_LO_B                     INDY_EXT_PAGE_4, 552

// PTP LTC READ Registers
#define INDY_PTP_LTC_RD_SEC_HI                              INDY_EXT_PAGE_4, 553
#define INDY_PTP_LTC_RD_SEC_MID                             INDY_EXT_PAGE_4, 554
#define INDY_PTP_LTC_RD_SEC_LO                              INDY_EXT_PAGE_4, 555
#define INDY_PTP_LTC_RD_NS_HI                               INDY_EXT_PAGE_4, 556
#define INDY_PTP_LTC_RD_NS_LO                               INDY_EXT_PAGE_4, 557
#define INDY_PTP_LTC_RD_SUBNS_HI                            INDY_EXT_PAGE_4, 558
#define INDY_PTP_LTC_RD_SUBNS_LO                            INDY_EXT_PAGE_4, 559


// GPIO

//PTP GPIO Select Register
#define INDY_PTP_GPIO_SEL                               INDY_EXT_PAGE_4, 560
#define INDY_PTP_GPIO_SELECT_F(x)                       INDY_ENCODE_BITFIELD(x, 8, 3)
#define INDY_PTP_GPIO_SELECT                            INDY_ENCODE_BITMASK(8, 3)

//PTP GPIO Capture Map High Register
#define INDY_PTP_GPIO_CAP_MAP_HI                        INDY_EXT_PAGE_4, 561
#define INDY_PTP_GPIO_CAP_7_MAP_F(x)                    INDY_ENCODE_BITFIELD(x, 12, 4)
#define INDY_PTP_GPIO_CAP_7_MAP                         INDY_ENCODE_BITMASK(12, 4)
#define INDY_PTP_GPIO_CAP_6_MAP_F(x)                    INDY_ENCODE_BITFIELD(x, 8, 4)
#define INDY_PTP_GPIO_CAP_6_MAP                         INDY_ENCODE_BITMASK(8, 4)
#define INDY_PTP_GPIO_CAP_5_MAP_F(x)                    INDY_ENCODE_BITFIELD(x, 4, 4)
#define INDY_PTP_GPIO_CAP_5_MAP                         INDY_ENCODE_BITMASK(4, 4)
#define INDY_PTP_GPIO_CAP_4_MAP_F(x)                    INDY_ENCODE_BITFIELD(x, 0, 4)
#define INDY_PTP_GPIO_CAP_4_MAP                         INDY_ENCODE_BITMASK(0, 4)
//PTP GPIO Capture Map Low Register
#define INDY_PTP_GPIO_CAP_MAP_LO                        INDY_EXT_PAGE_4, 562
#define INDY_PTP_GPIO_CAP_3_MAP_F(x)                    INDY_ENCODE_BITFIELD(x, 12, 4)
#define INDY_PTP_GPIO_CAP_3_MAP                         INDY_ENCODE_BITMASK(12, 4)
#define INDY_PTP_GPIO_CAP_2_MAP_F(x)                    INDY_ENCODE_BITFIELD(x, 8, 4)
#define INDY_PTP_GPIO_CAP_2_MAP                         INDY_ENCODE_BITMASK(8, 4)
#define INDY_PTP_GPIO_CAP_1_MAP_F(x)                    INDY_ENCODE_BITFIELD(x, 4, 4)
#define INDY_PTP_GPIO_CAP_1_MAP                         INDY_ENCODE_BITMASK(4, 4)
#define INDY_PTP_GPIO_CAP_0_MAP_F(x)                    INDY_ENCODE_BITFIELD(x, 0, 4)
#define INDY_PTP_GPIO_CAP_0_MAP                         INDY_ENCODE_BITMASK(0, 4)

//PTP GPIO Capture Enable Register
#define INDY_PTP_GPIO_CAP_EN                            INDY_EXT_PAGE_4, 563
#define INDY_PTP_GPIO_FE_CAPTURE_EN_F(x)                INDY_ENCODE_BITFIELD(x, 8, 8)
#define INDY_PTP_GPIO_FE_CAPTURE_EN                     INDY_ENCODE_BITMASK(8, 8)
#define INDY_PTP_GPIO_RE_CAPTURE_EN_F(x)                INDY_ENCODE_BITFIELD(x, 0, 8)
#define INDY_PTP_GPIO_RE_CAPTURE_EN                     INDY_ENCODE_BITMASK(0, 8)

//PTP GPIO Capture Lock Register
#define INDY_PTP_GPIO_CAP_LOCK                          INDY_EXT_PAGE_4, 564
#define INDY_PTP_GPIO_LOCK_FE_F(x)                      INDY_ENCODE_BITFIELD(x, 8, 8)
#define INDY_PTP_GPIO_LOCK_FE                           INDY_ENCODE_BITMASK(8, 8)
#define INDY_PTP_GPIO_LOCK_RE_F(x)                      INDY_ENCODE_BITFIELD(x, 0, 8)
#define INDY_PTP_GPIO_LOCK_RE                           INDY_ENCODE_BITMASK(0, 8)

//PTP GPIO x Rising Edge Clock  Capture Registers
#define INDY_PTP_GPIO_RE_CLOCK_SEC_HI                   INDY_EXT_PAGE_4, 565
#define INDY_PTP_GPIO_RE_CLOCK_SEC_LO                   INDY_EXT_PAGE_4, 566
#define INDY_PTP_GPIO_RE_CLOCK_NS_HI                    INDY_EXT_PAGE_4, 567
#define INDY_PTP_GPIO_RE_CLOCK_NS_LO                    INDY_EXT_PAGE_4, 568

//PTP GPIO x Falling Edge Clock Capture Register
#define INDY_PTP_GPIO_FE_CLOCK_SEC_HI                   INDY_EXT_PAGE_4, 569
#define INDY_PTP_GPIO_FE_CLOCK_SEC_LO                   INDY_EXT_PAGE_4, 570
#define INDY_PTP_GPIO_FE_CLOCK_NS_HI                    INDY_EXT_PAGE_4, 571
#define INDY_PTP_GPIO_FE_CLOCK_NS_LO                    INDY_EXT_PAGE_4, 572

//PTP GPIO Capture Status Register
#define INDY_PTP_GPIO_CAP_STS                           INDY_EXT_PAGE_4, 573

//PTP GPIO Interrupt Clear Configuration Register
#define INDY_PTP_GPIO_INT_CLR_CFG                       INDY_EXT_PAGE_4, 574

// PTP LTC Hard Reset Register
#define INDY_PTP_LTC_HARD_RESET                         INDY_EXT_PAGE_4, 575
#define INDY_PTP_LTC_HARD_RESET_CMD                     INDY_BIT(0)

// PTP LTC Soft Reset Register
#define INDY_PTP_LTC_SOFT_RESET                         INDY_EXT_PAGE_4, 576
#define INDY_PTP_LTC_SOFT_RESET_CMD                     INDY_BIT(0)

// PTP Operating Mode Register
#define INDY_PTP_OPERATING_MODE                         INDY_EXT_PAGE_4, 577
#define INDY_PTP_OPERATING_MODE_VAL_F(x)                INDY_ENCODE_BITFIELD(x, 0, 2)
#define INDY_PTP_OPERATING_MODE_VAL                     INDY_ENCODE_BITMASK(0, 2)

// PTP Revision Register
#define INDY_PTP_REVISION                               INDY_EXT_PAGE_4, 578

// PTP PCH SubPortID Register
#define INDY_PTP_PCH_SUBPORT_ID                         INDY_EXT_PAGE_4, 579
#define INDY_PTP_PCH_SUBPORT_ID_PORT3_F(x)              INDY_ENCODE_BITFIELD(x, 12, 4)
#define INDY_PTP_PCH_SUBPORT_ID_PORT3                   INDY_ENCODE_BITMASK(12, 4)
#define INDY_PTP_PCH_SUBPORT_ID_PORT2_F(x)              INDY_ENCODE_BITFIELD(x, 8, 4)
#define INDY_PTP_PCH_SUBPORT_ID_PORT2                   INDY_ENCODE_BITMASK(8, 4)
#define INDY_PTP_PCH_SUBPORT_ID_PORT1_F(x)              INDY_ENCODE_BITFIELD(x, 4, 4)
#define INDY_PTP_PCH_SUBPORT_ID_PORT1                   INDY_ENCODE_BITMASK(4, 4)
#define INDY_PTP_PCH_SUBPORT_ID_PORT0_F(x)              INDY_ENCODE_BITFIELD(x, 0, 4)
#define INDY_PTP_PCH_SUBPORT_ID_PORT0                   INDY_ENCODE_BITMASK(0, 4)


// EP-4 PTP Latency Correction Control Register
#define INDY_PTP_LATENCY_CORRECTION_CTRL                INDY_EXT_PAGE_4, 580

// EP-4 1588 Serial Timestamp Interface Registers

// 1588 STI Configuration Register
#define INDY_PTP_STI_CONFIG                             INDY_EXT_PAGE_4, 768
#define INDY_PTP_STI_Tx_COUNT                           INDY_EXT_PAGE_4, 769
#define INDY_PTP_STI_HARD_RESET                         INDY_EXT_PAGE_4, 770
#define INDY_PTP_STI_SOFT_RESET                         INDY_EXT_PAGE_4, 771



// EP-5 1588 Port-Specific Registers

// PTP TSU Interrupt Enable Register
#define INDY_PTP_TSU_INT_EN                             INDY_EXT_PAGE_5, 512
#define INDY_PTP_TSU_INT_TX_TS_OVRFL_EN                 INDY_BIT(3)
#define INDY_PTP_TSU_INT_TX_TS_EN                       INDY_BIT(2)
#define INDY_PTP_TSU_INT_RX_TS_OVRFL_EN                 INDY_BIT(1)
#define INDY_PTP_TSU_INT_RX_TS_EN                       INDY_BIT(0)


// PTP TSU Interrupt Status Register
#define INDY_PTP_TSU_INT_STS                            INDY_EXT_PAGE_5, 513
#define INDY_PTP_TX_TS_OVRFL_INT                        INDY_BIT(3)
#define INDY_PTP_TX_TS_INT                              INDY_BIT(2)
#define INDY_PTP_RX_TS_OVRFL_INT                        INDY_BIT(1)
#define INDY_PTP_RX_TS_INT                              INDY_BIT(0)

// PTP Modification Error Register
#define INDY_PTP_MOD_ERR                                INDY_EXT_PAGE_5, 514

// PTP User MAC Address
#define INDY_PTP_RX_USER_MAC_HI                         INDY_EXT_PAGE_5, 515
#define INDY_PTP_RX_USER_MAC_MID                        INDY_EXT_PAGE_5, 516
#define INDY_PTP_RX_USER_MAC_LO                         INDY_EXT_PAGE_5, 517

//PTP User IP Address Registers
#define INDY_PTP_RX_USER_IP_ADDR_0                      INDY_EXT_PAGE_5, 518
#define INDY_PTP_RX_USER_IP_ADDR_1                      INDY_EXT_PAGE_5, 519
#define INDY_PTP_RX_USER_IP_ADDR_2                      INDY_EXT_PAGE_5, 520
#define INDY_PTP_RX_USER_IP_ADDR_3                      INDY_EXT_PAGE_5, 521
#define INDY_PTP_RX_USER_IP_ADDR_4                      INDY_EXT_PAGE_5, 522
#define INDY_PTP_RX_USER_IP_ADDR_5                      INDY_EXT_PAGE_5, 523
#define INDY_PTP_RX_USER_IP_ADDR_6                      INDY_EXT_PAGE_5, 524
#define INDY_PTP_RX_USER_IP_ADDR_7                      INDY_EXT_PAGE_5, 525

//PTP User IP Mask Registers
#define INDY_PTP_RX_USER_IP_MASK_0                      INDY_EXT_PAGE_5, 526
#define INDY_PTP_RX_USER_IP_MASK_1                      INDY_EXT_PAGE_5, 527
#define INDY_PTP_RX_USER_IP_MASK_2                      INDY_EXT_PAGE_5, 528
#define INDY_PTP_RX_USER_IP_MASK_3                      INDY_EXT_PAGE_5, 529
#define INDY_PTP_RX_USER_IP_MASK_4                      INDY_EXT_PAGE_5, 530
#define INDY_PTP_RX_USER_IP_MASK_5                      INDY_EXT_PAGE_5, 531
#define INDY_PTP_RX_USER_IP_MASK_6                      INDY_EXT_PAGE_5, 532
#define INDY_PTP_RX_USER_IP_MASK_7                      INDY_EXT_PAGE_5, 533

// VLAN configuration registers common for both ingress and egress
#define INDY_PTP_VLAN_ETH_TYPE_ID                       INDY_EXT_PAGE_5, 534
#define INDY_VLAN1_TYPE_ID                              INDY_EXT_PAGE_5, 535
#define INDY_VLAN1_TYPE_SELECT_F(x)                     INDY_ENCODE_BITFIELD(x, 12, 2)
#define INDY_VLAN1_TYPE_SELECT                          INDY_ENCODE_BITMASK(12, 2)
#define INDY_VLAN1_TYPE_ID_VAL_F(x)                     INDY_ENCODE_BITFIELD(x, 0, 11)
#define INDY_VLAN1_TYPE_ID_VAL                          INDY_ENCODE_BITMASK(0, 11)
#define INDY_VLAN1_ID_MASK                              INDY_EXT_PAGE_5, 536
#define INDY_VLAN1_ID_MASK_VAL_F(x)                     INDY_ENCODE_BITFIELD(x, 0, 11)
#define INDY_VLAN1_ID_MASK_VAL                          INDY_ENCODE_BITMASK(0, 11)
#define INDY_VLAN1_VID_RANGE_UP                         INDY_EXT_PAGE_5, 537
#define INDY_VLAN1_VID_RANGE_EN                         INDY_BIT(12)
#define INDY_VLAN1_VID_RANGE_UP_VAL_F(x)                INDY_ENCODE_BITFIELD(x, 0, 11)
#define INDY_VLAN1_VID_RANGE_UP_VAL                     INDY_ENCODE_BITMASK(0, 11)
#define INDY_VLAN1_VID_RANGE_LO                         INDY_EXT_PAGE_5, 538
#define INDY_VLAN1_VID_RANGE_LO_VAL_F(x)                INDY_ENCODE_BITFIELD(x, 0, 11)
#define INDY_VLAN1_VID_RANGE_LO_VAL                     INDY_ENCODE_BITMASK(0, 11)
#define INDY_VLAN2_TYPE_ID                              INDY_EXT_PAGE_5, 539
#define INDY_VLAN2_TYPE_SELECT_F(x)                     INDY_ENCODE_BITFIELD(x, 12, 2)
#define INDY_VLAN2_TYPE_SELECT                          INDY_ENCODE_BITMASK(12, 2)
#define INDY_VLAN2_TYPE_ID_VAL_F(x)                     INDY_ENCODE_BITFIELD(x, 0, 11)
#define INDY_VLAN2_TYPE_ID_VAL                          INDY_ENCODE_BITMASK(0, 11)
#define INDY_VLAN2_ID_MASK                              INDY_EXT_PAGE_5, 540
#define INDY_VLAN2_ID_MASK_VAL_F(x)                     INDY_ENCODE_BITFIELD(x, 0, 11)
#define INDY_VLAN2_ID_MASK_VAL                          INDY_ENCODE_BITMASK(0, 11)
#define INDY_VLAN2_VID_RANGE_UP                         INDY_EXT_PAGE_5, 541
#define INDY_VLAN2_VID_RANGE_EN                         INDY_BIT(12)
#define INDY_VLAN2_VID_RANGE_UP_VAL_F(x)                INDY_ENCODE_BITFIELD(x, 0, 11)
#define INDY_VLAN2_VID_RANGE_UP_VAL                     INDY_ENCODE_BITMASK(0, 11)
#define INDY_VLAN2_VID_RANGE_LO                         INDY_EXT_PAGE_5, 542
#define INDY_VLAN2_VID_RANGE_LO_VAL_F(x)                INDY_ENCODE_BITFIELD(x, 0, 11)
#define INDY_VLAN2_VID_RANGE_LO_VAL                     INDY_ENCODE_BITMASK(0, 11)
#define INDY_LLC_TYPE_ID                                INDY_EXT_PAGE_5, 543


//PTP RX and TX Latency values for 10Mbps/100Mbps/1000Mbps
#define INDY_PTP_RX_LATENCY_10                          INDY_EXT_PAGE_5, 544
#define INDY_PTP_TX_LATENCY_10                          INDY_EXT_PAGE_5, 545
#define INDY_PTP_RX_LATENCY_100                         INDY_EXT_PAGE_5, 546
#define INDY_PTP_TX_LATENCY_100                         INDY_EXT_PAGE_5, 547
#define INDY_PTP_RX_LATENCY_1000                        INDY_EXT_PAGE_5, 548
#define INDY_PTP_TX_LATENCY_1000                        INDY_EXT_PAGE_5, 549

//PTP Asymmetry Delay
#define INDY_PTP_ASYM_DLY_HI                            INDY_EXT_PAGE_5, 550
#define INDY_PTP_ASYM_DLY_LO                            INDY_EXT_PAGE_5, 551

//PTP Peer Delay
#define INDY_PTP_PEERDLY_HI                             INDY_EXT_PAGE_5, 552
#define INDY_PTP_PEERDLY_LO                             INDY_EXT_PAGE_5, 553

//PTP Capture Information Register
#define INDY_PTP_CAP_INFO                               INDY_EXT_PAGE_5, 554
#define INDY_PTP_CAP_INFO_TX_TS_CNT_THRES_F(x)          INDY_ENCODE_BITFIELD(x, 12, 4)
#define INDY_PTP_CAP_INFO_TX_TS_CNT_THRES               INDY_ENCODE_BITMASK(12,4)
#define INDY_PTP_CAP_INFO_TX_TS_CNT_F(x)                INDY_ENCODE_BITFIELD(x, 8, 4)
#define INDY_PTP_CAP_INFO_TX_TS_CNT                     INDY_ENCODE_BITMASK(8,4)
#define INDY_PTP_CAP_INFO_RX_TS_CNT_THRES_F(x)          INDY_ENCODE_BITFIELD(x, 4, 4)
#define INDY_PTP_CAP_INFO_RX_TS_CNT_THRES               INDY_ENCODE_BITMASK(4,4)
#define INDY_PTP_CAP_INFO_RX_TS_CNT_F(x)                INDY_ENCODE_BITFIELD(x, 0, 4)
#define INDY_PTP_CAP_INFO_RX_TS_CNT                     INDY_ENCODE_BITMASK(0,4)


//PTP TX USER MAC ADDRESS
#define INDY_PTP_TX_USER_MAC_HI                         INDY_EXT_PAGE_5, 555
#define INDY_PTP_TX_USER_MAC_MID                        INDY_EXT_PAGE_5, 556
#define INDY_PTP_TX_USER_MAC_LO                         INDY_EXT_PAGE_5, 557


//PTP TX USER IP ADDRESS REGISTERS
#define INDY_PTP_TX_USER_IP_ADDR_0                      INDY_EXT_PAGE_5, 558
#define INDY_PTP_TX_USER_IP_ADDR_1                      INDY_EXT_PAGE_5, 559
#define INDY_PTP_TX_USER_IP_ADDR_2                      INDY_EXT_PAGE_5, 560
#define INDY_PTP_TX_USER_IP_ADDR_3                      INDY_EXT_PAGE_5, 561
#define INDY_PTP_TX_USER_IP_ADDR_4                      INDY_EXT_PAGE_5, 562
#define INDY_PTP_TX_USER_IP_ADDR_5                      INDY_EXT_PAGE_5, 563
#define INDY_PTP_TX_USER_IP_ADDR_6                      INDY_EXT_PAGE_5, 564
#define INDY_PTP_TX_USER_IP_ADDR_7                      INDY_EXT_PAGE_5, 565

//PTP TX USER IP MASK REGISTERS
#define INDY_PTP_TX_USER_IP_MASK_0                      INDY_EXT_PAGE_5, 566
#define INDY_PTP_TX_USER_IP_MASK_1                      INDY_EXT_PAGE_5, 567
#define INDY_PTP_TX_USER_IP_MASK_2                      INDY_EXT_PAGE_5, 568
#define INDY_PTP_TX_USER_IP_MASK_3                      INDY_EXT_PAGE_5, 569
#define INDY_PTP_TX_USER_IP_MASK_4                      INDY_EXT_PAGE_5, 570
#define INDY_PTP_TX_USER_IP_MASK_5                      INDY_EXT_PAGE_5, 571
#define INDY_PTP_TX_USER_IP_MASK_6                      INDY_EXT_PAGE_5, 572
#define INDY_PTP_TX_USER_IP_MASK_7                      INDY_EXT_PAGE_5, 573

//PTP RX Parsing Configuration Register
#define INDY_PTP_RX_PARSE_CONFIG                        INDY_EXT_PAGE_5, 578
#define INDY_PTP_RX_PARSE_CONFIG_IPv6_FRAG_EN           INDY_BIT(15)
#define INDY_PTP_RX_PARSE_CONFIG_PEER_NONPEER_MIX       INDY_BIT(14)
#define INDY_PTP_RX_PARSE_CONFIG_IP_DA_PEER_NONPEER     INDY_BIT(13)
#define INDY_PTP_RX_PARSE_CONFIG_MAC_DA_PEER_NONPEER    INDY_BIT(12)
#define INDY_PTP_RX_PARSE_CONFIG_MAC_DA_EN              INDY_BIT(11)
#define INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE_F(x)       INDY_ENCODE_BITFIELD(x, 8, 3)
#define INDY_PTP_RX_PARSE_CONFIG_MAC_DA_MODE            INDY_ENCODE_BITMASK(8,3)
#define INDY_PTP_RX_PARSE_CONFIG_IPV4_FRAG_EN           INDY_BIT(7)
#define INDY_PTP_RX_PARSE_CONFIG_UDP_SPORT_EN           INDY_BIT(6)
#define INDY_PTP_RX_PARSE_CONFIG_UDP_DPORT_EN           INDY_BIT(5)
#define INDY_PTP_RX_PARSE_CONFIG_MAC_IP_CONSISTANCY     INDY_BIT(4)
#define INDY_PTP_RX_PARSE_CONFIG_ROUTING_HDR            INDY_BIT(3)
#define INDY_PTP_RX_PARSE_CONFIG_IPV6_EN                INDY_BIT(2)
#define INDY_PTP_RX_PARSE_CONFIG_IPV4_EN                INDY_BIT(1)
#define INDY_PTP_RX_PARSE_CONFIG_LAYER2_EN              INDY_BIT(0)

//PTP RX Parsing VLAN Configuration Register
#define INDY_PTP_RX_PARSE_VLAN_CONFIG                   INDY_EXT_PAGE_5, 579
#define INDY_PTP_RX_PARSE_VLAN_TAG_COUNT_F(x)           INDY_ENCODE_BITFIELD(x,4,3)
#define INDY_PTP_RX_PARSE_VLAN_TAG_COUNT                INDY_ENCODE_BITMASK(4,3)
#define INDY_PTP_RX_PARSE_VLAN_CHECK_EN                 INDY_BIT(2)
#define INDY_PTP_RX_PARSE_VLAN_VLAN2_CHECK_EN           INDY_BIT(1)
#define INDY_PTP_RX_PARSE_VLAN_VLAN1_CHECK_EN           INDY_BIT(0)

//PTP RX Parsing Layer2 Format Address Enable Register
#define INDY_PTP_RX_PARSE_L2_ADDR_EN                    INDY_EXT_PAGE_5, 580
#define INDY_PTP_RX_PARSE_L2_MAC_DA1_EN                 INDY_BIT(3)
#define INDY_PTP_RX_PARSE_L2_MAC_DA2_EN                 INDY_BIT(2)
#define INDY_PTP_RX_PARSE_L2_MAC_EN_F(x)                INDY_ENCODE_BITFIELD(x, 0, 2)
#define INDY_PTP_RX_PARSE_L2_MAC_EN                     INDY_ENCODE_BITMASK(0, 2)

//PTP RX Parsing IP Format Address Enable Register
#define INDY_PTP_RX_PARSE_IP_ADDR_EN                    INDY_EXT_PAGE_5, 581
#define INDY_PTP_RX_PARSE_IP_DA_EN                      INDY_BIT(13)
#define INDY_PTP_RX_PARSE_IP_DA1_EN                     INDY_BIT(12)
#define INDY_PTP_RX_PARSE_IP_DA2_EN                     INDY_BIT(11)
#define INDY_PTP_RX_PARSE_IP_DA3_EN                     INDY_BIT(10)
#define INDY_PTP_RX_PARSE_IP_DA4_EN                     INDY_BIT(9)
#define INDY_PTP_RX_PARSE_IP_DA5_EN                     INDY_BIT(8)
#define INDY_PTP_RX_PARSE_IPv6_UMAC_EN_F(x)             INDY_ENCODE_BITFIELD(x, 6, 2)
#define INDY_PTP_RX_PARSE_IPv6_UMAC_EN                  INDY_ENCODE_BITMASK(6, 2)
#define INDY_PTP_RX_PARSE_IPv6_IP_EN_F(x)               INDY_ENCODE_BITFIELD(x, 4, 2)
#define INDY_PTP_RX_PARSE_IPv6_IP_EN                    INDY_ENCODE_BITMASK(4, 2)
#define INDY_PTP_RX_PARSE_IPv4_UMAC_EN_F(x)             INDY_ENCODE_BITFIELD(x, 2, 2)
#define INDY_PTP_RX_PARSE_IPv4_UMAC_EN                  INDY_ENCODE_BITMASK(2, 2)
#define INDY_PTP_RX_PARSE_IPv4_IP_EN_F(x)               INDY_ENCODE_BITFIELD(x, 0, 2)
#define INDY_PTP_RX_PARSE_IPv4_IP_EN                    INDY_ENCODE_BITMASK(0, 2)

//PTP RX Parsing UDP Source Port Register
#define INDY_PTP_RX_PARSE_UDP_SRC_PORT                  INDY_EXT_PAGE_5, 582

//PTP RX Parsing UDP Destination Port Register
#define INDY_PTP_RX_PARSE_UDP_DEST_PORT                 INDY_EXT_PAGE_5, 583

//PTP RX Version Register
#define INDY_PTP_RX_VERSION                             INDY_EXT_PAGE_5, 584
#define INDY_PTP_RX_VERSION_UP_F(x)                     INDY_ENCODE_BITFIELD(x, 8, 8)
#define INDY_PTP_RX_VERSION_UP                          INDY_ENCODE_BITMASK(8,8)
#define INDY_PTP_RX_VERSION_LOW_F(x)                    INDY_ENCODE_BITFIELD(x, 0, 8)
#define INDY_PTP_RX_VERSION_LOW                         INDY_ENCODE_BITMASK(0,8)

//PTP RX Domain / Domain Range Lower Register
#define INDY_PTP_RX_DOMAIN_DOMAIN_LO                    INDY_EXT_PAGE_5, 585
#define INDY_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_EN           INDY_BIT(15)
#define INDY_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_LO_F(x)      INDY_ENCODE_BITFIELD(x, 0, 8)
#define INDY_PTP_RX_DOMAIN_DOMAIN_LO_RANGE_LO           INDY_ENCODE_BITMASK(0, 8)

//PTP RX Domain Mask / Domain Range Upper Register
#define INDY_PTP_RX_DOMAIN_MASK_DOMAIN_UP               INDY_EXT_PAGE_5, 586

//PTP RX SdoId / SdoId Range Lower Register
#define INDY_PTP_RX_SDOID_SDOID_LO                      INDY_EXT_PAGE_5, 587
#define INDY_PTP_RX_SDOID_SDOID_LO_RANGE_EN             INDY_BIT(15)
#define INDY_PTP_RX_SDOID_SDOID_LO_RANGE_LO_F(x)        INDY_ENCODE_BITFIELD(x, 0, 8)
#define INDY_PTP_RX_SDOID_SDOID_LO_RANGE_LO             INDY_ENCODE_BITMASK(0, 8)

//PTP RX SdoId Mask / SdoId Range Upper Register
#define INDY_PTP_RX_SDOID_MASK_SDOID_UP                 INDY_EXT_PAGE_5, 588

//PTP RX Timestamp Enable Register
#define INDY_PTP_RX_TIMESTAMP_EN                        INDY_EXT_PAGE_5, 589

//PTP RX Timestamp Configuration Register
#define INDY_PTP_RX_TIMESTAMP_CONFIG                    INDY_EXT_PAGE_5, 590
#define INDY_PTP_RX_PTP_UDPV6_ZERO_CHKSUM_EN            INDY_BIT(3)
#define INDY_PTP_RX_PTP_ALT_MASTER_EN                   INDY_BIT(2)
#define INDY_PTP_RX_PTP_UDP_CHKSUM_DIS                  INDY_BIT(1)
#define INDY_PTP_RX_PTP_FCS_DIS                         INDY_BIT(0)

//PTP RX Modification Register
#define INDY_PTP_RX_MOD                                 INDY_EXT_PAGE_5, 591
#define INDY_PTP_RX_MOD_PTP_BAD_IPV6_FORCE_FCS_DIS      INDY_BIT(4)
#define INDY_PTP_RX_MOD_PTP_BAD_IPV4_FORCE_FCS_DIS      INDY_BIT(3)
#define INDY_PTP_RX_MOD_PTP_INSERT_TS_SEC_EN            INDY_BIT(2)
#define INDY_PTP_RX_MOD_PTP_INSERT_TS_32BIT             INDY_BIT(1)
#define INDY_PTP_RX_MOD_PTP_INSERT_TS_EN                INDY_BIT(0)


//PTP RX Reserved Bytes Configuration Register
#define INDY_PTP_RX_RSVD_BYTE_CFG                       INDY_EXT_PAGE_5, 592

//PTP RX Tail Tag Register
#define INDY_PTP_RX_TAIL_TAG                            INDY_EXT_PAGE_5, 593
#define INDY_PTP_RX_TAIL_TAG_ER_FORWARD                 INDY_BIT(8)
#define INDY_PTP_RX_TAIL_TAG_INSERT_IFG_F(x)            INDY_ENCODE_BITFIELD(x, 4, 3)
#define INDY_PTP_RX_TAIL_TAG_INSERT_IFG(x)              INDY_ENCODE_BITMASK(x, 4, 3)
#define INDY_PTP_RX_TAIL_TAG_INSERT                     INDY_BIT(3)
#define INDY_PTP_RX_TAIL_TAG_ALL                        INDY_BIT(2)
#define INDY_PTP_RX_TAIL_TAG_ALL_1588                   INDY_BIT(1)
#define INDY_PTP_RX_TAIL_TAG_EN                         INDY_BIT(0)

//PTP RX Correction Field Modification Enable Register
#define INDY_PTP_RX_CF_MOD_EN                           INDY_EXT_PAGE_5, 594

//PTP RX Correction Field Configuration Register
#define INDY_PTP_RX_CF_CFG                              INDY_EXT_PAGE_5, 595
#define INDY_PTP_RX_PTP_MAX_CF_DIS                      INDY_BIT(1)
#define INDY_PTP_RX_PTP_CF_METHOD                       INDY_BIT(0)

//PTP RX Ingress Timestamp
#define INDY_PTP_RX_TS_NS_HI                            INDY_EXT_PAGE_5, 596
#define INDY_PTP_RX_TS_NS_PTP_TX_TS_VALID               INDY_BIT(15)
#define INDY_PTP_RX_TS_NS_HI_VAL_F(x)                   INDY_ENCODE_BITFIELD(x, 0, 14)
#define INDY_PTP_RX_TS_NS_HI_VAL                        INDY_ENCODE_BITMASK(0,14)
#define INDY_PTP_RX_TS_NS_LO                            INDY_EXT_PAGE_5, 597
#define INDY_PTP_RX_TS_SEC_HI                           INDY_EXT_PAGE_5, 598
#define INDY_PTP_RX_TS_SEC_LO                           INDY_EXT_PAGE_5, 599

//PTP RX Message Header Registers
#define INDY_PTP_RX_MSG_HEADER1                         INDY_EXT_PAGE_5, 600
#define INDY_PTP_RX_MSG_HEADER2                         INDY_EXT_PAGE_5, 601

//PTP RX Pdelay_Req Ingress Timestamp
#define INDY_PTP_RX_PDREQ_SEC_HI                        INDY_EXT_PAGE_5, 602
#define INDY_PTP_RX_PDREQ_SEC_MID                       INDY_EXT_PAGE_5, 603
#define INDY_PTP_RX_PDREQ_SEC_LOW                       INDY_EXT_PAGE_5, 604
#define INDY_PTP_RX_PDREQ_NS_HI                         INDY_EXT_PAGE_5, 605
#define INDY_F_PTP_RX_PDREQ_AUTO_UPDATE                 INDY_BIT(15)
#define INDY_PTP_RX_PDREQ_NS_LO                         INDY_EXT_PAGE_5, 606

//PTP RX Raw Ingress Time Seconds Register
#define INDY_PTP_RX_RAW_TS_SEC                          INDY_EXT_PAGE_5, 607
#define INDY_PTP_RX_RAW_TS_NS_HI                        INDY_EXT_PAGE_5, 608
#define INDY_PTP_RX_RAW_TS_NS_LO                        INDY_EXT_PAGE_5, 609

//PTP RX Checksum Dropped Count
#define INDY_PTP_RX_CHKSUM_DROPPED_CNT_HI               INDY_EXT_PAGE_5, 610
#define INDY_PTP_RX_CHKSUM_DROPPED_CNT_LO               INDY_EXT_PAGE_5, 611

//PTP RX Frames Modified Count
#define INDY_PTP_RX_FRMS_MOD_CNT_HI                     INDY_EXT_PAGE_5, 612
#define INDY_PTP_RX_FRMS_MOD_CNT_LO                     INDY_EXT_PAGE_5, 613

//PTP TX Parsing Configuration Register
#define INDY_PTP_TX_PARSE_CONFIG                        INDY_EXT_PAGE_5, 642
#define INDY_PTP_TX_PARSE_CONFIG_IPv6_FRAG_EN           INDY_BIT(15)
#define INDY_PTP_TX_PARSE_CONFIG_PEER_NONPEER_MIX       INDY_BIT(14)
#define INDY_PTP_TX_PARSE_CONFIG_IP_DA_PEER_NONPEER     INDY_BIT(13)
#define INDY_PTP_TX_PARSE_CONFIG_MAC_DA_PEER_NONPEER    INDY_BIT(12)
#define INDY_PTP_TX_PARSE_CONFIG_MAC_DA_EN              INDY_BIT(11)
#define INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE_F(x)       INDY_ENCODE_BITFIELD(x, 8, 3)
#define INDY_PTP_TX_PARSE_CONFIG_MAC_DA_MODE            INDY_ENCODE_BITMASK(8,3)
#define INDY_PTP_TX_PARSE_CONFIG_IPV4_FRAG_EN           INDY_BIT(7)
#define INDY_PTP_TX_PARSE_CONFIG_UDP_SPORT_EN           INDY_BIT(6)
#define INDY_PTP_TX_PARSE_CONFIG_UDP_DPORT_EN           INDY_BIT(5)
#define INDY_PTP_TX_PARSE_CONFIG_MAC_IP_CONSISTANCY     INDY_BIT(4)
#define INDY_PTP_TX_PARSE_CONFIG_ROUTING_HDR            INDY_BIT(3)
#define INDY_PTP_TX_PARSE_CONFIG_IPV6_EN                INDY_BIT(2)
#define INDY_PTP_TX_PARSE_CONFIG_IPV4_EN                INDY_BIT(1)
#define INDY_PTP_TX_PARSE_CONFIG_LAYER2_EN              INDY_BIT(0)


//PTP TX Parsing VLAN Configuration Register
#define INDY_PTP_TX_PARSE_VLAN_CONFIG                   INDY_EXT_PAGE_5, 643
#define INDY_PTP_TX_PARSE_VLAN_TAG_COUNT_F(x)           INDY_ENCODE_BITFIELD(x,4,3)
#define INDY_PTP_TX_PARSE_VLAN_TAG_COUNT                INDY_ENCODE_BITMASK(4,3)
#define INDY_PTP_TX_PARSE_VLAN_CHECK_EN                 INDY_BIT(2)
#define INDY_PTP_TX_PARSE_VLAN_VLAN2_CHECK_EN           INDY_BIT(1)
#define INDY_PTP_TX_PARSE_VLAN_VLAN1_CHECK_EN           INDY_BIT(0)

//PTP TX Parsing Layer2 Format Address Enable Register
#define INDY_PTP_TX_PARSE_L2_ADDR_EN                    INDY_EXT_PAGE_5, 644
#define INDY_PTP_TX_PARSE_L2_MAC_DA1_EN                 INDY_BIT(3)
#define INDY_PTP_TX_PARSE_L2_MAC_DA2_EN                 INDY_BIT(2)
#define INDY_PTP_TX_PARSE_L2_MAC_EN_F(x)                INDY_ENCODE_BITFIELD(x, 0, 2)
#define INDY_PTP_TX_PARSE_L2_MAC_EN                     INDY_ENCODE_BITMASK(0, 2)

//PTP TX Parsing IP Format Address Enable Register
#define INDY_PTP_TX_PARSE_IP_ADDR_EN                    INDY_EXT_PAGE_5, 645
#define INDY_PTP_TX_PARSE_IP_DA_EN                      INDY_BIT(13)
#define INDY_PTP_TX_PARSE_IP_DA1_EN                     INDY_BIT(12)
#define INDY_PTP_TX_PARSE_IP_DA2_EN                     INDY_BIT(11)
#define INDY_PTP_TX_PARSE_IP_DA3_EN                     INDY_BIT(10)
#define INDY_PTP_TX_PARSE_IP_DA4_EN                     INDY_BIT(9)
#define INDY_PTP_TX_PARSE_IP_DA5_EN                     INDY_BIT(8)
#define INDY_PTP_TX_PARSE_IPv6_UMAC_EN_F(x)             INDY_ENCODE_BITFIELD(x, 6, 2)
#define INDY_PTP_TX_PARSE_IPv6_UMAC_EN                  INDY_ENCODE_BITMASK(6, 2)
#define INDY_PTP_TX_PARSE_IPv6_IP_EN_F(x)               INDY_ENCODE_BITFIELD(x, 4, 2)
#define INDY_PTP_TX_PARSE_IPv6_IP_EN                    INDY_ENCODE_BITMASK(4, 2)
#define INDY_PTP_TX_PARSE_IPv4_UMAC_EN_F(x)             INDY_ENCODE_BITFIELD(x, 2, 2)
#define INDY_PTP_TX_PARSE_IPv4_UMAC_EN                  INDY_ENCODE_BITMASK(2, 2)
#define INDY_PTP_TX_PARSE_IPv4_IP_EN_F(x)               INDY_ENCODE_BITFIELD(x, 0, 2)
#define INDY_PTP_TX_PARSE_IPv4_IP_EN                    INDY_ENCODE_BITMASK(0, 2)
//PTP TX Parsing UDP Source Port Register
#define INDY_PTP_TX_PARSE_UDP_SRC_PORT                  INDY_EXT_PAGE_5, 646

//PTP TX Parsing UDP Destination Port Register
#define INDY_PTP_TX_PARSE_UDP_DEST_PORT                 INDY_EXT_PAGE_5, 647

// PTP TX Version Register
#define INDY_PTP_TX_VERSION                             INDY_EXT_PAGE_5, 648

// PTP TX Domain / Domain Range Lower Register
#define INDY_PTP_TX_DOMAIN_DOMAIN_LO                    INDY_EXT_PAGE_5, 649
#define INDY_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_EN           INDY_BIT(15)
#define INDY_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_LO_F(x)      INDY_ENCODE_BITFIELD(x, 0, 8)
#define INDY_PTP_TX_DOMAIN_DOMAIN_LO_RANGE_LO           INDY_ENCODE_BITMASK(0, 8)

// PTP TX Domain Mask / Domain Range Upper Register
#define INDY_PTP_TX_DOMAIN_MASK_DOMAIN_UP               INDY_EXT_PAGE_5, 650

// PTP TX SdoId / SdoId Range Lower Register
#define INDY_PTP_TX_SDOID_SDOID_LO                      INDY_EXT_PAGE_5, 651
#define INDY_PTP_TX_SDOID_SDOID_LO_RANGE_EN             INDY_BIT(15)
#define INDY_PTP_TX_SDOID_SDOID_LO_RANGE_LO_F(x)        INDY_ENCODE_BITFIELD(x, 0, 8)
#define INDY_PTP_TX_SDOID_SDOID_LO_RANGE_LO             INDY_ENCODE_BITMASK(0, 8)

// PTP TX SdoId Mask / SdoId Range Upper Register
#define INDY_PTP_TX_SDOID_MASK_SDOID_UP                 INDY_EXT_PAGE_5, 652

// PTP TX Timestamp Enable Register
#define INDY_PTP_TX_TIMESTAMP_EN                        INDY_EXT_PAGE_5, 653

// PTP TX Timestamp Configuration Register
#define INDY_PTP_TX_TIMESTAMP_CONFIG                    INDY_EXT_PAGE_5, 654
#define INDY_PTP_TX_PTP_UDPV6_ZERO_CHKSUM_EN            INDY_BIT(3)
#define INDY_PTP_TX_PTP_ALT_MASTER_EN                   INDY_BIT(2)
#define INDY_PTP_TX_PTP_UDP_CHKSUM_DIS                  INDY_BIT(1)
#define INDY_PTP_TX_PTP_FCS_DIS                         INDY_BIT(0)

// PTP TX Modification Register
#define INDY_PTP_TX_MOD                                 INDY_EXT_PAGE_5, 655
#define INDY_PTP_TX_MOD_CLR_1_RSVRD                     INDY_BIT(15)
#define INDY_PTP_TX_MOD_CLR_4_RSVRD                     INDY_BIT(14)
#define INDY_PTP_TX_MOD_PDRESP_TA_INSERT                INDY_BIT(13)
#define INDY_PTP_TX_MOD_SYNC_TS_INSERT                  INDY_BIT(12)
#define INDY_PTP_TX_MOD_FOLLOWUP_TS_INSERT              INDY_BIT(11)
#define INDY_PTP_TX_MOD_PDRESP_TS_INSERT                INDY_BIT(10)
#define INDY_PTP_TX_MOD_PDRESPFOLLOWUP_TS_INSERT        INDY_BIT(9)
#define INDY_PTP_TX_MOD_PTP_BAD_IPV6_FORCE_FCS_DIS      INDY_BIT(4)
#define INDY_PTP_TX_MOD_PTP_BAD_IPV4_FORCE_FCS_DIS      INDY_BIT(3)



// PTP TX Reserved Bytes Configuration Register
#define INDY_PTP_TX_RSVD_BYTE_CFG                       INDY_EXT_PAGE_5, 656

// PTP TX Tail Tag Register
#define INDY_PTP_TX_TAIL_TAG                            INDY_EXT_PAGE_5, 657

// PTP TX Correction Field Modification Enable Register
#define INDY_PTP_TX_CF_MOD_EN                           INDY_EXT_PAGE_5, 658

// PTP TX Correction Field Configuration Register
#define INDY_PTP_TX_CF_CFG                              INDY_EXT_PAGE_5, 659
#define INDY_PTP_TX_PTP_CF_32BIT                        INDY_BIT(2)
#define INDY_PTP_TX_PTP_MAX_CF_DIS                      INDY_BIT(1)
#define INDY_PTP_TX_PTP_CF_METHOD                       INDY_BIT(0)


// PTP TX Egress Timestamp
#define INDY_PTP_TX_TS_NS_HI                            INDY_EXT_PAGE_5, 660
#define INDY_PTP_TX_TS_NS_PTP_TX_TS_VALID               INDY_BIT(15)
#define INDY_PTP_TX_TS_NS_HI_VAL_F(x)                   INDY_ENCODE_BITFIELD(x, 0, 14)
#define INDY_PTP_TX_TS_NS_HI_VAL                        INDY_ENCODE_BITMASK(0,14)

#define INDY_PTP_TX_TS_NS_LO                            INDY_EXT_PAGE_5, 661
#define INDY_PTP_TX_TS_SEC_HI                           INDY_EXT_PAGE_5, 662
#define INDY_PTP_TX_TS_SEC_LO                           INDY_EXT_PAGE_5, 663

// PTP TX Message Header
#define INDY_PTP_TX_MSG_HEADER1                         INDY_EXT_PAGE_5, 664
#define INDY_PTP_TX_MSG_HEADER2                         INDY_EXT_PAGE_5, 665

// PTP TX Sync Egress Timestamp
#define INDY_PTP_TX_SYNC_SEC_HI                         INDY_EXT_PAGE_5, 666
#define INDY_PTP_TX_SYNC_SEC_MID                        INDY_EXT_PAGE_5, 667
#define INDY_PTP_TX_SYNC_SEC_LOW                        INDY_EXT_PAGE_5, 668
#define INDY_PTP_TX_SYNC_NS_HI                          INDY_EXT_PAGE_5, 669
#define INDY_PTP_TX_SYNC_NS_HI_TS_VALID                 INDY_BIT(15)
#define INDY_PTP_TX_SYNC_NS_HI_VAL_F(x)                 INDY_ENCODE_BITFIELD(x, 0, 14)
#define INDY_PTP_TX_SYNC_NS_HI_VAL                      INDY_ENCODE_BITMASK(0,14)
#define INDY_PTP_TX_SYNC_NS_LO                          INDY_EXT_PAGE_5, 670

// PTP TX Pdelay_Resp Egress Timestamp
#define INDY_PTP_TX_PDRESP_SEC_HI                       INDY_EXT_PAGE_5, 671
#define INDY_PTP_TX_PDRESP_SEC_MID                      INDY_EXT_PAGE_5, 672
#define INDY_PTP_TX_PDRESP_SEC_LOW                      INDY_EXT_PAGE_5, 673
#define INDY_PTP_TX_PDRESP_NS_HI                        INDY_EXT_PAGE_5, 674
#define INDY_PTP_TX_PDRESP_NS_HI_TS_VALID               INDY_BIT(15)
#define INDY_PTP_TX_PDRESP_NS_HI_VAL_F(x)               INDY_ENCODE_BITFIELD(x, 0, 14)
#define INDY_PTP_TX_PDRESP_NS_HI_VAL                    INDY_ENCODE_BITMASK(0,14)
#define INDY_PTP_TX_PDRESP_NS_LO                        INDY_EXT_PAGE_5, 675

// PTP TX Raw Egress Time Seconds Register - 16bits
#define INDY_PTP_TX_RAW_TS_SEC                          INDY_EXT_PAGE_5, 676

// PTP TX Raw Egress Time Nanoseconds Register
#define INDY_PTP_TX_RAW_TS_NS_HI                        INDY_EXT_PAGE_5, 677
#define INDY_PTP_TX_RAW_TS_NS_LO                        INDY_EXT_PAGE_5, 678

// PTP TX Checksum Dropped Counter
#define INDY_PTP_TX_CHKSUM_DROPPED_CNT_HI               INDY_EXT_PAGE_5, 679
#define INDY_PTP_TX_CHKSUM_DROPPED_CNT_LO               INDY_EXT_PAGE_5, 680

// PTP TX Frames Modified Counter
#define INDY_PTP_TX_FRMS_MOD_CNT_HI                     INDY_EXT_PAGE_5, 681
#define INDY_PTP_TX_FRMS_MOD_CNT_LO                     INDY_EXT_PAGE_5, 682

// TSU General Configuration Register
#define INDY_PTP_TSU_GEN_CONF                           INDY_EXT_PAGE_5, 704
#define INDY_PTP_TSU_GEN_CONF_TS_CRC_PKT                INDY_BIT(2)
#define INDY_PTP_TSU_GEN_CONF_PREEMPTION_EN             INDY_BIT(1)
#define INDY_PTP_TSU_GEN_CONF_EN                        INDY_BIT(0)

// TSU Hard Reset Register
#define INDY_PTP_TSU_HARD_RESET                         INDY_EXT_PAGE_5, 705
#define INDY_PTP_TSU_HARD_RESET_CMD                     INDY_BIT(0)

// TSU Soft Reset Register
#define INDY_PTP_TSU_SOFT_RESET                         INDY_EXT_PAGE_5, 706
#define INDY_PTP_TSU_SOFT_RESET_CMD                     INDY_BIT(0)

// PTP PCH Format Mismatch Register
#define INDY_PTP_PCH_FORMAT_MISMATCH                    INDY_EXT_PAGE_5, 707
#define INDY_PTP_PCH_FORMAT_MISMATCH_PKT_TYPE           INDY_BIT(3)
#define INDY_PTP_PCH_FORMAT_MISMATCH_EXT_TYPE           INDY_BIT(2)
#define INDY_PTP_PCH_FORMAT_MISMATCH_CRC_ERR            INDY_BIT(1)
#define INDY_PTP_PCH_FORMAT_MISMATCH_SUB_PORT_ID        INDY_BIT(0)


#endif
