// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN867X_H
#define LAN867X_H

#ifndef BIT
#define BIT(x)  ((uint16_t)0x1U << (x))
#endif

/* SMI Basic Constrol and Status Registers */
#define LAN867X_BASIC_CONTROL_REG           (uint16_t)0x00U
#define LAN867X_BASIC_CONTROL_POWER_DOWN    (uint16_t)0x0800U
#define LAN867X_BASIC_STATUS_REG            (uint16_t)0x01U
#define LAN867X_PHY_ID0_REG                 (uint16_t)0x02U
#define LAN867X_PHY_ID1_REG                 (uint16_t)0x03U
#define LAN867X_MMDCTRL_REG                 (uint16_t)0x0DU
#define LAN867X_MMDAD_REG                   (uint16_t)0x0EU
#define LAN867X_STRAP_CTRL0_REG             (uint16_t)0x12U

#define LAN867X_REV(x)                  ((x) & 0xFU)
#define LAN867X_MODEL(x)                (((x) & 0x03F0U) >> 4U)
#define LAN867X_OUI(x, y)               (((x) << 2U) & 0x0003FFFCU) | (((y) & 0x0000FC00U) << 18U)
#define LAN867X_REVB                    (0x02U)

#define MMDCTRL_ADDRESS                 ((uint16_t)0x0U << 14U)
#define MMDCTRL_NO_POST_INC             ((uint16_t)0x1U << 14U)
#define MMDCTRL_POST_INC_RW             ((uint16_t)0x2U << 14U)
#define MMDCTRL_POST_INC_W              ((uint16_t)0x3U << 14U)

#define STRAP_MEDIA_TYPE_M              (uint16_t)0x3U
#define STRAP_MEDIA_TYPE_S              (uint16_t)7U
#define MEDIA_SIMPLIFIED_MII            (uint16_t)3U
#define MEDIA_MII                       (uint16_t)2U
#define MEDIA_RMII                      (uint16_t)1U
#define STRAP_PACKAGE_TYPE_M            (uint16_t)0x3U
#define STRAP_PACKAGE_TYPE_S            (uint16_t)5U
#define PACKAGE_LAN8672                 (uint16_t)3U
#define PACKAGE_LAN8671                 (uint16_t)2U
#define PACKAGE_LAN8670                 (uint16_t)1U
#define STRAP_PHY_ADDRESS_M             (uint16_t)0x1FU
/* b3 = RMII, 8672, 0x13, 172 = MII, 8670, 0x12 */

#define MMD_PMA_PMD                     (uint16_t)0x01U

#define PMA_EXT_ABILITY                 (uint16_t)0x0012U
#define T1_PMA_CTRL                     (uint16_t)0x0834U
#define T1S_PMA_CTRL                    (uint16_t)0x08F9U
#define T1S_PMA_STATUS                  (uint16_t)0x08FAU
#define T1S_TEST_CTRL                   (uint16_t)0x08FBU

#define MMD_PCS                         (uint16_t)0x03U

#define T1S_PCS_CTRL                    (uint16_t)0x08F3U
#define T1S_PCS_STATUS                  (uint16_t)0x08F4U
#define T1S_PCS_DIAG_1                  (uint16_t)0x08F5U
#define T1S_PCS_DIAG_2                  (uint16_t)0x08F6U

#define MMD_MISC                        (uint8_t)0x1FU

#define MISC_CTRL_1                     (uint16_t)0x0010U

#define INACTIVITY_WATCHDOG_ENABLE      BIT(3U)
#define DIGITAL_LOOPBACK_ENABLE         BIT(1U)

#define MISC_PIN_CTRL                   (uint16_t)0x0011U

#define GPIO0_SIGNAL_SEL_M              (uint16_t)0x03U
#define GPIO0_SIGNAL_SEL_S              (uint16_t)14U
#define GPIO0_SIGNAL_ACMA_INPUT         (uint16_t)3U
#define GPIO0_SIGNAL_PMCH               (uint16_t)2U
#define GPIO0_SIGNAL_PMCH_TX            (uint16_t)1U
#define GPIO0_SIGNAL_PMCH_RX            (uint16_t)0U
#define PMCH_RX_POLARITY_S              (uint16_t)6U
#define PMCH_TX_POLARITY_S              (uint16_t)4U
#define WAKE_OUT_POLARITY_S             (uint16_t)2U
#define POLARITY_M                      (uint16_t)0x3U

#define POLARITY_NEG_PULSE              (uint16_t)1U
#define POLARITY_POS_PULSE              (uint16_t)0U

#define ACMA_POLARITY_S                 (uint16_t)0U
#define POLARITY_FALLING_EDGE           (uint16_t)1U
#define POLARITY_RISING_EDGE            (uint16_t)0U

#define MISC_STAT_1                     (uint16_t)0x0018
/* 0184; 0080, 0180 */

#define TX_COLLISION_INTR               BIT(10U)
#define TX_JABBER_INTR                  BIT(9U)
#define PATTERN_MATCH                   BIT(8U)
#define PLCA_EMPTY_CYCLE_INTR           BIT(7U)
#define RX_IN_TX_OP_INTR                BIT(6U)
#define UNEXPECTED_BEACON_INTR          BIT(5U)
#define BEACON_RX_BEFORE_TX_OP_INTR     BIT(4U)
#define BEACON_SYMBOLS_DETECTED_INTR    BIT(2U)
#define ESD_ERR_INTR                    BIT(1U)
#define DECODE_ERR_INTR                 BIT(0U)

#define MISC_STAT_2                     (uint16_t)0x0019U
/* 0810; 0800, 0000 */

#define RESET_COMPLETE_INTR             BIT(11U)
#define MDI_WAKEUP_INTR                 BIT(10U)
#define WAKE_IN_WAKEUP_INTR             BIT(9U)
#define OVER_TEMP_INTR                  BIT(6U)
#define WATCHDOG_INTR                   BIT(5U)

#define MISC_STAT_3                     (uint16_t)0x001AU
/* 0004; 0003, 0006 */

#define MISC_INTR_MASK_1                (uint16_t)0x001CU
#define MISC_INTR_MASK_2                (uint16_t)0x001DU

#define MISC_COUNTER_ENABLE             (uint16_t)0x0020U

#define TX_OP_CNT_ENABLE                BIT(1U)
#define BEACON_CNT_ENABLE               BIT(0U)

#define MISC_TX_OP_CNT_H                (uint16_t)0x0024U
#define MISC_TX_OP_CNT_L                (uint16_t)0x0025U
#define MISC_BEACON_CNT_H               (uint16_t)0x0026U
#define MISC_BEACON_CNT_L               (uint16_t)0x0027U

#define MISC_MULTI_ID_0                 (uint16_t)0x0030U
#define MISC_MULTI_ID_1                 (uint16_t)0x0031U
#define MISC_MULTI_ID_2                 (uint16_t)0x0032U
#define MISC_MULTI_ID_3                 (uint16_t)0x0033U

#define MISC_PLCA_STAT                  (uint16_t)0x0036U

#define PLCA_MAX_ID_S                   (uint16_t)8U

#define MISC_PORT_MANAGE_2              (uint16_t)0x003DU

#define MII_RX_WATCHDOG_ENABLE          BIT(13U)
#define SMI_WATCHDOG_ENABLE             BIT(12U)
#define MII_TX_WATCHDOG_ENABLE          BIT(11U)

/* 200 ns unit.  0x00989680 = 2 seconds. */
#define MISC_WATCHDOG_TIMEOUT_H         (uint16_t)0x003EU
#define MISC_WATCHDOG_TIMEOUT_L         (uint16_t)0x003FU

#define MISC_TX_MATCH_CTRL              (uint16_t)0x0040U

#define TX_MATCH_DETECTED               BIT(7U)
#define TX_MAC_TS_ENABLE                BIT(2U)
#define TX_MATCH_ENABLE                 BIT(1U)

#define MISC_TX_MATCH_PATTERN_H         (uint16_t)0x0041U
#define MISC_TX_MATCH_PATTERN_L         (uint16_t)0x0042U
#define MISC_TX_MATCH_MASK_H            (uint16_t)0x0043U
#define MISC_TX_MATCH_MASK_L            (uint16_t)0x0044U
#define MISC_TX_MATCH_LOCATION          (uint16_t)0x0045U

#define MATCH_H_M                       (uint16_t)0xFFU
#define MATCH_LOCATION_M                (uint16_t)0x7U

#define MISC_RX_MATCH_CTRL              (uint16_t)0x0050U

#define RX_MATCH_DETECTED               BIT(6U)
#define RX_MATCH_ENABLE                 BIT(1U)

#define MISC_RX_MATCH_PATTERN_H         (uint16_t)0x0051U
#define MISC_RX_MATCH_PATTERN_L         (uint16_t)0x0052U
#define MISC_RX_MATCH_MASK_H            (uint16_t)0x0053U
#define MISC_RX_MATCH_MASK_L            (uint16_t)0x0054U
#define MISC_RX_MATCH_LOCATION          (uint16_t)0x0055U

#define MISC_CBS_STOP_THRES_H           (uint16_t)0x0060U
#define MISC_CBS_STOP_THRES_L           (uint16_t)0x0061U

#define MISC_CBS_THRES_H                (uint16_t)0x0062U
#define MISC_CBS_THRES_L                (uint16_t)0x0063U

#define MISC_CBS_SLOPE_CTRL             (uint16_t)0x0064U

#define MISC_CBS_TOP_LIMIT_H            (uint16_t)0x0065U
#define MISC_CBS_TOP_LIMIT_L            (uint16_t)0x0066U

#define MISC_CBS_BOT_LIMIT_H            (uint16_t)0x0067U
#define MISC_CBS_BOT_LIMIT_L            (uint16_t)0x0068U

#define MISC_CBS_CNT_H                  (uint16_t)0x0069U
#define MISC_CBS_CNT_L                  (uint16_t)0x006AU

#define MISC_CBS_CTRL                   (uint16_t)0x006BU

#define CBS_EMPTY_SLOPE_M               (uint16_t)0xFU
#define CBS_EMPTY_SLOPE_S               (uint16_t)1U
#define CBS_ENABLE                      BIT(0U)

#define MISC_PLCA_SKIP_CTRL             (uint16_t)0x0070U

#define PLCA_SKIP_ENABLE                (uint16_t)BIT(1U)

#define MISC_PLCA_TO_SKIP               (uint16_t)0x0071U

#define PLCA_TO_SKIP_M                  (uint16_t)0xFFU

#define MISC_ACMA                       (uint16_t)0x0074U

#define ACMA_COLLISION_ENABLE           BIT(2U)
#define ACMA_COLLISION_DETECTED         BIT(1U)
#define ACMA_ENABLE                     BIT(0U)

#define MISC_SLEEP_CTRL_0               (uint16_t)0x0080U
#define MISC_SLEEP_CTRL_1               (uint16_t)0x0081U

#define MISC_SQI_CTRL                   (uint16_t)0x00A0U

#define SQI_RESET                       BIT(15U)
#define SQI_ENABLE                      BIT(14U)

#define MISC_SQI_STAT_0                 (uint16_t)0x00A1U

#define SQI_ERR                         BIT(7U)
#define SQI_VALID                       BIT(6U)
#define SQD_VAL_M                       (uint16_t)0x7U
#define SQI_VAL_S                       (uint16_t)3U
#define SQI_ERR_CODE_M                  (uint16_t)0x7U
#define SQI_LO_THRES_MORE_HI_THRES      (uint16_t)5U
#define SQI_HI_THRES_LESS_MAX_LIMIT     (uint16_t)4U
#define SQI_LO_THRES_LESS_MAX_LIMIT     (uint16_t)3U
#define SQI_HI_THRES_MORE_MAX_LIMIT     (uint16_t)2U
#define SQI_LO_THRES_MORE_MAX_LIMIT     (uint16_t)1U
#define SQI_NO_ERR                      (uint16_t)0U

#define MISC_SQI_CFG_0                  (uint16_t)0x00AAU

#define SQI_PLCA_TO_ID_S                4U

#define MISC_PAD_CTRL_3                 (uint16_t)0x00CBU

#define DIGITAL_OUT_DRIVE_STRENGH_M     (uint16_t)0x3U
#define DIGITAL_OUT_DRIVE_STRENGH_S     (uint16_t)2U
#define DRIVE_STRENGH_7_MA              (uint16_t)3U
#define DRIVE_STRENGH_5_MA              (uint16_t)2U
#define DRIVE_STRENGH_3_MA              (uint16_t)1U
#define DRIVE_STRENGH_1_MA              (uint16_t)0U

#define MAP_ID_VERSION                  (uint16_t)0xCA00U

#define PLCA_CTRL_0                     (uint16_t)0xCA01U

#define PLCA_ENABLE                     BIT(15U)
#define PLCA_RESET                      BIT(14U)

#define PLCA_CTRL_1                     (uint16_t)0xCA02U

#define PLCA_NODE_CNT_M                 (uint16_t)0xFFU
#define PLCA_NODE_CNT_S                 (uint16_t)8U
#define PLCA_LOCAL_NODE_ID_M            (uint16_t)0xFFU

#define PLCA_STATUS                     (uint16_t)0xCA03U

#define BEACON_ACTIVE                   BIT(15U)

#define PLCA_TO_TIMER                   (uint16_t)0xCA04U

#define PLCA_TO_TIMER_M                 (uint16_t)0xFFU

#define PLCA_BURST                      (uint16_t)0xCA05U

#define PLCA_MAX_BURST_CNT_M            (uint16_t)0xFFU
#define PLCA_MAX_BURST_CNT_S            (uint16_t)8U
#define PLCA_BURST_TIMER_M              (uint16_t)0xFFU

#endif // LAN867X_H
