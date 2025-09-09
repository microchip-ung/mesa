// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef PHY_DEFINES_H
#define PHY_DEFINES_H

#define ZERO                (0U)
#define ONE                 ((uint16_t)1U)
#define ONE32               (1UL)

#define BIT(x)                          ((ONE) << (x))
#define BIT32(x)                        ((ONE32) << (x))

#define BIT_MASK(x)             (((ONE) << (x)) - (ONE))
#define BIT32_MASK(x)           (((ONE32) << (x)) - (ONE32))

#define GENMASK(offset, width)      (BIT_MASK(width) << (offset))
#define GENMASK32(offset, width)    (BIT32_MASK(width) << (offset))

#define MCHP_MASK           GENMASK32(15, 0)
#define MCHP_4B_MASK        GENMASK32(31, 0)
#define DEF_MASK            (0xFFFFU)

#define EXTRACT_BITFIELD(value, offset, width)  (((value) >> (offset)) & BIT_MASK(width))
#define EXTRACT_BITS(val, offset, width)    EXTRACT_BITFIELD(val, offset, width)

#define ENCODE_BITFIELD(value, offset, width)   (((value) & BIT_MASK(width)) << (offset))

#define PHY_FALSE           (0U) /**< False boolean value */
#define PHY_TRUE            (1U) /**< True boolean value */
#define PHY_LINKUP          (PHY_TRUE)
#define PHY_LINKDOWN        (PHY_FALSE)

#define ARRAY_SIZE(x)       (sizeof(x) / sizeof((x)[0]))

/* Generate register address from reg_group + reg_offset */
#define MCHP_TEST_BIT(v, x)      ((((v) & BIT32(x)) != 0U) ? 1U : 0U)

#define MCHP_EXTRACT_V(v, h, l) (((v) & GENMASK32((h), (l))) >> (l))

#define MCHP_BSWAP(A) ((((A) & 0xFF00UL) >> 8UL) | (((A) & 0x00FFUL) << 8UL))

#define MCHP_BSWAP32(V) ((((V) & 0x000000FFU) << 24U) | (((V) & 0x0000FF00U) << 8U) | (((V) & 0x00FF0000U) >> 8U) | (((V) & 0xFF000000U) >> 24U))

#define MCHP_GET_U32(v, idx) ((uint32_t)(v)[(idx)] | \
            ((uint32_t)(v)[(idx) + 1U] << 8U) | \
            ((uint32_t)(v)[(idx) + 2U] << 16U) | \
            ((uint32_t)(v)[(idx) + 3U] << 24U))

/* MDIO Manageable Devices (MMDs). */
#define MDIO_MMD_PMAPMD         (1U)        /* Physical Medium Attachment/
                                             * Physical Medium Dependent */
#define MDIO_MMD_PCS            (3U)        /* Physical Coding Sublayer */
#define MDIO_MMD_AN             (7U)        /* Auto-Negotiation */
#define MDIO_MMD_VEND1          (30U)       /* Vendor specific 1 */

/* Generic MII registers. */
#define MII_BMCR                (0x00U)     /* Basic mode control register */

#define BMCR_SPEED1000          (0x0040U)   /* MSB of Speed (1000)         */
#define BMCR_FULLDPLX           (0x0100U)   /* Full duplex                 */
#define BMCR_ANRESTART          (0x0200U)   /* Auto negotiation restart    */
#define BMCR_ISOLATE            (0x0400U)   /* Enable isolate state        */
#define BMCR_PDOWN              (0x0800U)   /* Enable low power state      */
#define BMCR_ANENABLE           (0x1000U)   /* Enable auto negotiation     */
#define BMCR_SPEED100           (0x2000U)   /* Select 100Mbps              */
#define BMCR_LOOPBACK           (0x4000U)   /* TXD loopback bits           */
#define BMCR_RESET              (0x8000U)   /* Reset to default state      */

#define MII_BMSR                (0x01U)     /* Basic mode status register  */
#define BMSR_LSTATUS            (0x0004U)   /* Link status                 */

#define MII_PHYSID1         (0x02U)     /* PHYS ID 1                   */
#define MII_PHYSID2         (0x03U)     /* PHYS ID 2                   */
#define MII_MMD_CTRL            (0x0dU)     /* MMD Access Control Register */
#define MII_MMD_DATA            (0x0eU)     /* MMD Access Data Register */

#define MMDCTRL_ADDRESS                 (0U)
#define MMDCTRL_POST_INC_RW             (0x8000U) // 2 << 14
#define MMDCTRL_POST_INC_W              (0xc000U) // 3 << 14
#define MMDCTRL_NO_POST_INC             (0x4000U) // 1 << 14

/* Generic MDIO registers. */
#define MDIO_CTRL1          MII_BMCR
#define MDIO_STAT1          MII_BMSR

#define MDIO_AN_CTRL1_ENABLE            BMCR_ANENABLE
#define MDIO_AN_CTRL1_RESTART           BMCR_ANRESTART

#define MDIO_AN_T1_CTRL         (512U)     /* BASE-T1 AN control */
#define MDIO_AN_T1_STAT         (513U)     /* BASE-T1 AN status */
#define MDIO_AN_T1_ADV_L        (514U)     /* BASE-T1 AN advertisement register [15:0] */
#define MDIO_AN_T1_ADV_M        (515U)     /* BASE-T1 AN advertisement register [31:16] */
#define MDIO_AN_T1_ADV_H        (516U)     /* BASE-T1 AN advertisement register [47:32] */
#define MDIO_AN_T1_LP_L         (517U)     /* BASE-T1 AN LP Base Page ability register [15:0] */
#define MDIO_AN_T1_LP_M         (518U)     /* BASE-T1 AN LP Base Page ability register [31:16] */
#define MDIO_AN_T1_LP_H         (519U)     /* BASE-T1 AN LP Base Page ability register [47:32] */

#define MDIO_AN_T1_ADV_L_FORCE_MS       (0x1000U)   /* Force Master/slave Configuration */
#define MDIO_AN_T1_LP_L_FORCE_MS        (0x1000U)   /* LP Force Master/slave Configuration */
#define MDIO_AN_T1_ADV_M_MST            (0x0010U)   /* advertise master preference */
#define MDIO_AN_T1_LP_M_MST             (0x0010U)   /* LP master preference */
#define MDIO_AN_STAT1_COMPLETE          (0x0020U)   /* Auto-negotiation complete   */
#define MDIO_AN_T1_ADV_L_PAUSE_CAP      (0x0400U)   /* Try for pause               */
#define MDIO_AN_T1_ADV_L_PAUSE_ASYM     (0x0800U)
#define LPA_100FULL                     (0x0020U)   /* Can do 100mbps full-duplex  */
#define LPA_1000FULL                    (0x0080U)   /* Can do 1000BASE-X full-duplex */
#define MDIO_AN_T1_ADV_M_B1000          (0x0080U)   /* device is compatible with 1000BASE-T1 */
#define MDIO_AN_T1_ADV_M_B100           (0x0020U)   /* device is compatible with 100BASE-T1 */

#define MASTER_SLAVE_STATE_UNSUPPORTED  (0U)
#define MASTER_SLAVE_STATE_UNKNOWN      (1U)
#define MASTER_SLAVE_STATE_MASTER       (2U)
#define MASTER_SLAVE_STATE_SLAVE        (3U)
#define MASTER_SLAVE_STATE_ERR          (4U)

/* Status register 1. */
#define MDIO_STAT1_LSTATUS      BMSR_LSTATUS

/* Media-dependent registers. */
#define MDIO_PMA_PMD_BT1_CTRL           (2100U) /* BASE-T1 PMA/PMD control register */

/* BASE-T1 PMA/PMD control register */
#define MDIO_PMA_PMD_BT1_CTRL_CFG_MST   (0x4000U) /* MASTER-SLAVE config value */

#define T_D(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_DEBUG, __func__, __LINE__, __FILE__, format, ##__VA_ARGS__);

#define T_I(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_INFO, __func__, __LINE__, __FILE__, format, ##__VA_ARGS__);

#define T_W(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_WARNING, __func__, __LINE__, __FILE__, format, ##__VA_ARGS__);

#define T_E(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_ERROR, __func__, __LINE__, __FILE__, format, ##__VA_ARGS__);

#endif //PHY_DEFINES_H
