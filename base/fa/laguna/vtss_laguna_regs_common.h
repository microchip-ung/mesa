// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_COMMON_H_
#define _VTSS_LAGUNA_REGS_COMMON_H_


#include <stdint.h>
#ifndef VTSS_BITOPS_DEFINED
#ifdef __ASSEMBLER__
#define VTSS_BIT(x)                   (1 << (x))
#define VTSS_BITMASK(x)               ((1 << (x)) - 1)
#else
#define VTSS_BIT(x)                   (1U << (x))
#define VTSS_BITMASK(x)               ((1U << (x)) - 1)
#endif
#define VTSS_EXTRACT_BITFIELD(x,o,w)  (((x) >> (o)) & VTSS_BITMASK(w))
#define VTSS_ENCODE_BITFIELD(x,o,w)   (((x) & VTSS_BITMASK(w)) << (o))
#define VTSS_ENCODE_BITMASK(o,w)      (VTSS_BITMASK(w) << (o))
#define VTSS_BITOPS_DEFINED
#endif /* VTSS_BITOPS_DEFINED */

/* IO indexed register access macro - may be changed for platform */
#if !defined(VTSS_IOREG_IX)
/**
 * @param t  - target base offset
 * @param o  - subtarget offset
 * @param g  - group instance,
 * @param gw - group width
 * @param ro - register offset,
 * @param r  - register (instance) number
 */
#define VTSS_IOREG_IX(t,o,g,gw,r,ro)   VTSS_IOREG(t,(o) + ((g) * (gw)) + (ro) + (r))
#endif


#if 0

/* Main target address offsets */
#ifndef VTSS_IO_ORIGIN1_OFFSET
#define VTSS_IO_ORIGIN1_OFFSET 0x0e2000000 /*! default region*/
#endif
#ifndef VTSS_IO_ORIGIN1_SIZE
#define VTSS_IO_ORIGIN1_SIZE 0x001000000
#endif
#ifndef VTSS_IO_OFFSET1
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)
#endif
#ifndef VTSS_IO_ORIGIN2_OFFSET
#define VTSS_IO_ORIGIN2_OFFSET 0x0e0000000 /*! amba_axi_top region*/
#endif
#ifndef VTSS_IO_ORIGIN2_SIZE
#define VTSS_IO_ORIGIN2_SIZE 0x001000000
#endif
#ifndef VTSS_IO_OFFSET2
#define VTSS_IO_OFFSET2(offset) (VTSS_IO_ORIGIN2_OFFSET + offset)
#endif
#ifndef VTSS_IO_ORIGIN3_OFFSET
#define VTSS_IO_ORIGIN3_OFFSET 0x000000000 /*! amba_axi_top_mem region*/
#endif
#ifndef VTSS_IO_ORIGIN3_SIZE
#define VTSS_IO_ORIGIN3_SIZE 0x001000000
#endif
#ifndef VTSS_IO_OFFSET3
#define VTSS_IO_OFFSET3(offset) (VTSS_IO_ORIGIN3_OFFSET + offset)
#endif
#define VTSS_TO_AES             VTSS_IO_OFFSET2(0x0004c000) /*!< Base offset for target AES */
#define VTSS_TO_AESB_ASC        VTSS_IO_OFFSET2(0x00050000) /*!< Base offset for target AESB_ASC */
#define VTSS_TO_CPU             VTSS_IO_OFFSET2(0x000c0000) /*!< Base offset for target CPU */
#define VTSS_TO_DDR_PHY         VTSS_IO_OFFSET2(0x00084000) /*!< Base offset for target DDR_PHY */
#define VTSS_TO_DDR_UMCTL2      VTSS_IO_OFFSET2(0x00080000) /*!< Base offset for target DDR_UMCTL2 */
#define VTSS_TO_FDMA            VTSS_IO_OFFSET2(0x000c0400) /*!< Base offset for target FDMA */
#define VTSS_TO_FLEXCOM_0       VTSS_IO_OFFSET2(0x00040000) /*!< Base offset for target FLEXCOM_0 */
#define VTSS_TO_FLEXCOM_1       VTSS_IO_OFFSET2(0x00044000) /*!< Base offset for target FLEXCOM_1 */
#define VTSS_TO_FLEXCOM_2       VTSS_IO_OFFSET2(0x00060000) /*!< Base offset for target FLEXCOM_2 */
#define VTSS_TO_FLEXCOM_3       VTSS_IO_OFFSET2(0x00064000) /*!< Base offset for target FLEXCOM_3 */
#define VTSS_TO_CPU_SYSCNT      VTSS_IO_OFFSET2(0x08000000) /*!< Base offset for target CPU_SYSCNT */
#define VTSS_TO_CPU_SYSCNT_RO   VTSS_IO_OFFSET2(0x08000000) /*!< Base offset for target CPU_SYSCNT_RO */
#define VTSS_TO_GIC400          VTSS_IO_OFFSET2(0x08c10000) /*!< Base offset for target GIC400 */
#define VTSS_TO_GPV             VTSS_IO_OFFSET2(0x08b00000) /*!< Base offset for target GPV */
#define VTSS_TO_HICM            VTSS_IO_OFFSET2(0x00810000) /*!< Base offset for target HICM */
#define VTSS_TO_HMATRIX2        VTSS_IO_OFFSET2(0x00800000) /*!< Base offset for target HMATRIX2 */
#define VTSS_TO_MCAN_0          VTSS_IO_OFFSET2(0x0081c000) /*!< Base offset for target MCAN_0 */
#define VTSS_TO_MCAN_1          VTSS_IO_OFFSET2(0x00820000) /*!< Base offset for target MCAN_1 */
#define VTSS_TO_MCAN_TIMER      VTSS_IO_OFFSET2(0x00824000) /*!< Base offset for target MCAN_TIMER */
#define VTSS_TO_UVOV            VTSS_IO_OFFSET2(0x00094000) /*!< Base offset for target UVOV */
#define VTSS_TO_OTP             VTSS_IO_OFFSET2(0x00021000) /*!< Base offset for target OTP */
#define VTSS_TO_PCIE_CFG        VTSS_IO_OFFSET2(0x000d0000) /*!< Base offset for target PCIE_CFG */
#define VTSS_TO_PCIE_DBI        VTSS_IO_OFFSET2(0x00400000) /*!< Base offset for target PCIE_DBI */
#define VTSS_TO_PCIE_PHY_PCS    VTSS_IO_OFFSET2(0x00088000) /*!< Base offset for target PCIE_PHY_PCS */
#define VTSS_TO_PCIE_PHY_PMA    VTSS_IO_OFFSET1(0x00100000) /*!< Base offset for target PCIE_PHY_PMA */
#define VTSS_TO_PCIE_PHY_WRAP   VTSS_IO_OFFSET1(0x000f0000) /*!< Base offset for target PCIE_PHY_WRAP */
#define VTSS_TO_PKE             VTSS_IO_OFFSET3(0x00080000) /*!< Base offset for target PKE */
#define VTSS_TO_QSPI_0          VTSS_IO_OFFSET2(0x00804000) /*!< Base offset for target QSPI_0 */
#define VTSS_TO_QSPI_2          VTSS_IO_OFFSET2(0x00834000) /*!< Base offset for target QSPI_2 */
#define VTSS_TO_SDMMC_0         VTSS_IO_OFFSET2(0x00830000) /*!< Base offset for target SDMMC_0 */
#define VTSS_TO_SDMMC_1         VTSS_IO_OFFSET2(0x00838000) /*!< Base offset for target SDMMC_1 */
#define VTSS_TO_SHA             VTSS_IO_OFFSET2(0x0006c000) /*!< Base offset for target SHA */
#define VTSS_TO_SJTAG           VTSS_IO_OFFSET2(0x00020000) /*!< Base offset for target SJTAG */
#define VTSS_TO_TIMERS          VTSS_IO_OFFSET2(0x0008c000) /*!< Base offset for target TIMERS */
#define VTSS_TO_TRNG            VTSS_IO_OFFSET2(0x00048000) /*!< Base offset for target TRNG */
#define VTSS_TO_TZAESBNS        VTSS_IO_OFFSET2(0x00814000) /*!< Base offset for target TZAESBNS */
#define VTSS_TO_TZAESBS         VTSS_IO_OFFSET2(0x00818000) /*!< Base offset for target TZAESBS */
#define VTSS_TO_TZC_MAIN_HSS    VTSS_IO_OFFSET2(0x00098000) /*!< Base offset for target TZC_MAIN_HSS */
#define VTSS_TO_TZC_CSS         VTSS_IO_OFFSET2(0x00099000) /*!< Base offset for target TZC_CSS */
#define VTSS_TO_TZPM            VTSS_IO_OFFSET2(0x00000000) /*!< Base offset for target TZPM */
#define VTSS_TO_USB3            VTSS_IO_OFFSET3(0x00300000) /*!< Base offset for target USB3 */
#define VTSS_TO_WDT             VTSS_IO_OFFSET2(0x00090000) /*!< Base offset for target WDT */
#define VTSS_TO_XDMAC           VTSS_IO_OFFSET2(0x00068000) /*!< Base offset for target XDMAC */
#define VTSS_TO_AFI             VTSS_IO_OFFSET1(0x00240000) /*!< Base offset for target AFI */
#define VTSS_TO_ANA_AC          VTSS_IO_OFFSET1(0x00900000) /*!< Base offset for target ANA_AC */
#define VTSS_TO_ANA_AC_OAM_MOD  VTSS_IO_OFFSET1(0x00070000) /*!< Base offset for target ANA_AC_OAM_MOD */
#define VTSS_TO_ANA_AC_POL      VTSS_IO_OFFSET1(0x00200000) /*!< Base offset for target ANA_AC_POL */
#define VTSS_TO_ANA_AC_SDLB     VTSS_IO_OFFSET1(0x00500000) /*!< Base offset for target ANA_AC_SDLB */
#define VTSS_TO_ANA_ACL         VTSS_IO_OFFSET1(0x00050000) /*!< Base offset for target ANA_ACL */
#define VTSS_TO_ANA_CL          VTSS_IO_OFFSET1(0x00400000) /*!< Base offset for target ANA_CL */
#define VTSS_TO_ANA_L2          VTSS_IO_OFFSET1(0x00800000) /*!< Base offset for target ANA_L2 */
#define VTSS_TO_ANA_L3          VTSS_IO_OFFSET1(0x00480000) /*!< Base offset for target ANA_L3 */
#define VTSS_TO_ASM             VTSS_IO_OFFSET1(0x01200000) /*!< Base offset for target ASM */
#define VTSS_TO_CHIP_TOP        VTSS_IO_OFFSET1(0x00020000) /*!< Base offset for target CHIP_TOP */
#define VTSS_TO_DEV2G5_1        VTSS_IO_OFFSET1(0x01010000) /*!< Base offset for target DEV2G5_1 */
#define VTSS_TO_DEV2G5_2        VTSS_IO_OFFSET1(0x01014000) /*!< Base offset for target DEV2G5_2 */
#define VTSS_TO_DEV2G5_3        VTSS_IO_OFFSET1(0x01018000) /*!< Base offset for target DEV2G5_3 */
#define VTSS_TO_DEV2G5_5        VTSS_IO_OFFSET1(0x01028000) /*!< Base offset for target DEV2G5_5 */
#define VTSS_TO_DEV2G5_6        VTSS_IO_OFFSET1(0x0102c000) /*!< Base offset for target DEV2G5_6 */
#define VTSS_TO_DEV2G5_7        VTSS_IO_OFFSET1(0x01030000) /*!< Base offset for target DEV2G5_7 */
#define VTSS_TO_DEV2G5_10       VTSS_IO_OFFSET1(0x0104c000) /*!< Base offset for target DEV2G5_10 */
#define VTSS_TO_DEV2G5_11       VTSS_IO_OFFSET1(0x01050000) /*!< Base offset for target DEV2G5_11 */
#define VTSS_TO_DEV2G5_14       VTSS_IO_OFFSET1(0x0106c000) /*!< Base offset for target DEV2G5_14 */
#define VTSS_TO_DEV2G5_15       VTSS_IO_OFFSET1(0x01070000) /*!< Base offset for target DEV2G5_15 */
#define VTSS_TO_DEV2G5_18       VTSS_IO_OFFSET1(0x0108c000) /*!< Base offset for target DEV2G5_18 */
#define VTSS_TO_DEV2G5_19       VTSS_IO_OFFSET1(0x01090000) /*!< Base offset for target DEV2G5_19 */
#define VTSS_TO_DEV2G5_22       VTSS_IO_OFFSET1(0x010ac000) /*!< Base offset for target DEV2G5_22 */
#define VTSS_TO_DEV2G5_23       VTSS_IO_OFFSET1(0x010b0000) /*!< Base offset for target DEV2G5_23 */
#define VTSS_TO_DEVRGMII_0      VTSS_IO_OFFSET1(0x010e4000) /*!< Base offset for target DEVRGMII_0 */
#define VTSS_TO_DEVRGMII_1      VTSS_IO_OFFSET1(0x010e8000) /*!< Base offset for target DEVRGMII_1 */
#define VTSS_TO_DEV2G5_9        VTSS_IO_OFFSET1(0x01040000) /*!< Base offset for target DEV2G5_9 */
#define VTSS_TO_DEV2G5_13       VTSS_IO_OFFSET1(0x01060000) /*!< Base offset for target DEV2G5_13 */
#define VTSS_TO_DEV2G5_17       VTSS_IO_OFFSET1(0x01080000) /*!< Base offset for target DEV2G5_17 */
#define VTSS_TO_DEV2G5_21       VTSS_IO_OFFSET1(0x010a0000) /*!< Base offset for target DEV2G5_21 */
#define VTSS_TO_DEV2G5_0        VTSS_IO_OFFSET1(0x01004000) /*!< Base offset for target DEV2G5_0 */
#define VTSS_TO_DEV2G5_4        VTSS_IO_OFFSET1(0x0101c000) /*!< Base offset for target DEV2G5_4 */
#define VTSS_TO_DEV2G5_8        VTSS_IO_OFFSET1(0x01034000) /*!< Base offset for target DEV2G5_8 */
#define VTSS_TO_DEV2G5_12       VTSS_IO_OFFSET1(0x01054000) /*!< Base offset for target DEV2G5_12 */
#define VTSS_TO_DEV2G5_16       VTSS_IO_OFFSET1(0x01074000) /*!< Base offset for target DEV2G5_16 */
#define VTSS_TO_DEV2G5_20       VTSS_IO_OFFSET1(0x01094000) /*!< Base offset for target DEV2G5_20 */
#define VTSS_TO_DEV2G5_24       VTSS_IO_OFFSET1(0x010b4000) /*!< Base offset for target DEV2G5_24 */
#define VTSS_TO_DEV2G5_25       VTSS_IO_OFFSET1(0x010c0000) /*!< Base offset for target DEV2G5_25 */
#define VTSS_TO_DEV2G5_26       VTSS_IO_OFFSET1(0x010cc000) /*!< Base offset for target DEV2G5_26 */
#define VTSS_TO_DEV2G5_27       VTSS_IO_OFFSET1(0x010d8000) /*!< Base offset for target DEV2G5_27 */
#define VTSS_TO_DEV5G_0         VTSS_IO_OFFSET1(0x01044000) /*!< Base offset for target DEV5G_0 */
#define VTSS_TO_DEV5G_1         VTSS_IO_OFFSET1(0x01064000) /*!< Base offset for target DEV5G_1 */
#define VTSS_TO_DEV5G_2         VTSS_IO_OFFSET1(0x01084000) /*!< Base offset for target DEV5G_2 */
#define VTSS_TO_DEV5G_3         VTSS_IO_OFFSET1(0x010a4000) /*!< Base offset for target DEV5G_3 */
#define VTSS_TO_PCS5G_BR_0      VTSS_IO_OFFSET1(0x01048000) /*!< Base offset for target PCS5G_BR_0 */
#define VTSS_TO_PCS5G_BR_1      VTSS_IO_OFFSET1(0x01068000) /*!< Base offset for target PCS5G_BR_1 */
#define VTSS_TO_PCS5G_BR_2      VTSS_IO_OFFSET1(0x01088000) /*!< Base offset for target PCS5G_BR_2 */
#define VTSS_TO_PCS5G_BR_3      VTSS_IO_OFFSET1(0x010a8000) /*!< Base offset for target PCS5G_BR_3 */
#define VTSS_TO_DEV10G_0        VTSS_IO_OFFSET1(0x01008000) /*!< Base offset for target DEV10G_0 */
#define VTSS_TO_DEV10G_1        VTSS_IO_OFFSET1(0x01020000) /*!< Base offset for target DEV10G_1 */
#define VTSS_TO_DEV10G_2        VTSS_IO_OFFSET1(0x01038000) /*!< Base offset for target DEV10G_2 */
#define VTSS_TO_DEV10G_3        VTSS_IO_OFFSET1(0x01058000) /*!< Base offset for target DEV10G_3 */
#define VTSS_TO_DEV10G_4        VTSS_IO_OFFSET1(0x01078000) /*!< Base offset for target DEV10G_4 */
#define VTSS_TO_DEV10G_5        VTSS_IO_OFFSET1(0x01098000) /*!< Base offset for target DEV10G_5 */
#define VTSS_TO_DEV10G_6        VTSS_IO_OFFSET1(0x010b8000) /*!< Base offset for target DEV10G_6 */
#define VTSS_TO_DEV10G_7        VTSS_IO_OFFSET1(0x010c4000) /*!< Base offset for target DEV10G_7 */
#define VTSS_TO_DEV10G_8        VTSS_IO_OFFSET1(0x010d0000) /*!< Base offset for target DEV10G_8 */
#define VTSS_TO_DEV10G_9        VTSS_IO_OFFSET1(0x010dc000) /*!< Base offset for target DEV10G_9 */
#define VTSS_TO_PCS10G_BR_0     VTSS_IO_OFFSET1(0x0100c000) /*!< Base offset for target PCS10G_BR_0 */
#define VTSS_TO_PCS10G_BR_1     VTSS_IO_OFFSET1(0x01024000) /*!< Base offset for target PCS10G_BR_1 */
#define VTSS_TO_PCS10G_BR_2     VTSS_IO_OFFSET1(0x0103c000) /*!< Base offset for target PCS10G_BR_2 */
#define VTSS_TO_PCS10G_BR_3     VTSS_IO_OFFSET1(0x0105c000) /*!< Base offset for target PCS10G_BR_3 */
#define VTSS_TO_PCS10G_BR_4     VTSS_IO_OFFSET1(0x0107c000) /*!< Base offset for target PCS10G_BR_4 */
#define VTSS_TO_PCS10G_BR_5     VTSS_IO_OFFSET1(0x0109c000) /*!< Base offset for target PCS10G_BR_5 */
#define VTSS_TO_PCS10G_BR_6     VTSS_IO_OFFSET1(0x010bc000) /*!< Base offset for target PCS10G_BR_6 */
#define VTSS_TO_PCS10G_BR_7     VTSS_IO_OFFSET1(0x010c8000) /*!< Base offset for target PCS10G_BR_7 */
#define VTSS_TO_PCS10G_BR_8     VTSS_IO_OFFSET1(0x010d4000) /*!< Base offset for target PCS10G_BR_8 */
#define VTSS_TO_PCS10G_BR_9     VTSS_IO_OFFSET1(0x010e0000) /*!< Base offset for target PCS10G_BR_9 */
#define VTSS_TO_DEVCPU_GCB      VTSS_IO_OFFSET1(0x00010000) /*!< Base offset for target DEVCPU_GCB */
#define VTSS_TO_DEVCPU_ORG0     VTSS_IO_OFFSET1(0x00000000) /*!< Base offset for target DEVCPU_ORG0 */
#define VTSS_TO_DEVCPU_ORG1     VTSS_IO_OFFSET1(0x01000000) /*!< Base offset for target DEVCPU_ORG1 */
#define VTSS_TO_DEVCPU_ORG2     VTSS_IO_OFFSET1(0x01400000) /*!< Base offset for target DEVCPU_ORG2 */
#define VTSS_TO_DEVCPU_PTP      VTSS_IO_OFFSET1(0x00040000) /*!< Base offset for target DEVCPU_PTP */
#define VTSS_TO_DEVCPU_QS       VTSS_IO_OFFSET1(0x00030000) /*!< Base offset for target DEVCPU_QS */
#define VTSS_TO_DSM             VTSS_IO_OFFSET1(0x010ec000) /*!< Base offset for target DSM */
#define VTSS_TO_EACL            VTSS_IO_OFFSET1(0x002c0000) /*!< Base offset for target EACL */
#define VTSS_TO_HSCH            VTSS_IO_OFFSET1(0x00580000) /*!< Base offset for target HSCH */
#define VTSS_TO_HSIO_WRAP       VTSS_IO_OFFSET1(0x01408000) /*!< Base offset for target HSIO_WRAP */
#define VTSS_TO_LRN             VTSS_IO_OFFSET1(0x00060000) /*!< Base offset for target LRN */
#define VTSS_TO_PORT_CONF       VTSS_IO_OFFSET1(0x010f0000) /*!< Base offset for target PORT_CONF */
#define VTSS_TO_QFWD            VTSS_IO_OFFSET1(0x000b0000) /*!< Base offset for target QFWD */
#define VTSS_TO_QRES            VTSS_IO_OFFSET1(0x00280000) /*!< Base offset for target QRES */
#define VTSS_TO_QSYS            VTSS_IO_OFFSET1(0x000a0000) /*!< Base offset for target QSYS */
#define VTSS_TO_REW             VTSS_IO_OFFSET1(0x00600000) /*!< Base offset for target REW */
#define VTSS_TO_RB_0            VTSS_IO_OFFSET1(0x010f4000) /*!< Base offset for target RB_0 */
#define VTSS_TO_RB_1            VTSS_IO_OFFSET1(0x010f8000) /*!< Base offset for target RB_1 */
#define VTSS_TO_RB_2            VTSS_IO_OFFSET1(0x010fc000) /*!< Base offset for target RB_2 */
#define VTSS_TO_RB_3            VTSS_IO_OFFSET1(0x01100000) /*!< Base offset for target RB_3 */
#define VTSS_TO_RB_4            VTSS_IO_OFFSET1(0x01104000) /*!< Base offset for target RB_4 */
#define VTSS_TO_SD_CMU_0        VTSS_IO_OFFSET1(0x01410000) /*!< Base offset for target SD_CMU_0 */
#define VTSS_TO_SD_CMU_CFG_0    VTSS_IO_OFFSET1(0x01440000) /*!< Base offset for target SD_CMU_CFG_0 */
#define VTSS_TO_SD_CMU_1        VTSS_IO_OFFSET1(0x01418000) /*!< Base offset for target SD_CMU_1 */
#define VTSS_TO_SD_CMU_CFG_1    VTSS_IO_OFFSET1(0x01448000) /*!< Base offset for target SD_CMU_CFG_1 */
#define VTSS_TO_SD_CMU_2        VTSS_IO_OFFSET1(0x01420000) /*!< Base offset for target SD_CMU_2 */
#define VTSS_TO_SD_CMU_CFG_2    VTSS_IO_OFFSET1(0x01450000) /*!< Base offset for target SD_CMU_CFG_2 */
#define VTSS_TO_SD_CMU_3        VTSS_IO_OFFSET1(0x01428000) /*!< Base offset for target SD_CMU_3 */
#define VTSS_TO_SD_CMU_CFG_3    VTSS_IO_OFFSET1(0x01458000) /*!< Base offset for target SD_CMU_CFG_3 */
#define VTSS_TO_SD_CMU_4        VTSS_IO_OFFSET1(0x01430000) /*!< Base offset for target SD_CMU_4 */
#define VTSS_TO_SD_CMU_CFG_4    VTSS_IO_OFFSET1(0x01460000) /*!< Base offset for target SD_CMU_CFG_4 */
#define VTSS_TO_SD_CMU_5        VTSS_IO_OFFSET1(0x01438000) /*!< Base offset for target SD_CMU_5 */
#define VTSS_TO_SD_CMU_CFG_5    VTSS_IO_OFFSET1(0x01468000) /*!< Base offset for target SD_CMU_CFG_5 */
#define VTSS_TO_SD10G_LANE_0    VTSS_IO_OFFSET1(0x01470000) /*!< Base offset for target SD10G_LANE_0 */
#define VTSS_TO_SD10G_LANE_1    VTSS_IO_OFFSET1(0x01478000) /*!< Base offset for target SD10G_LANE_1 */
#define VTSS_TO_SD10G_LANE_2    VTSS_IO_OFFSET1(0x01480000) /*!< Base offset for target SD10G_LANE_2 */
#define VTSS_TO_SD10G_LANE_3    VTSS_IO_OFFSET1(0x01488000) /*!< Base offset for target SD10G_LANE_3 */
#define VTSS_TO_SD10G_LANE_4    VTSS_IO_OFFSET1(0x01490000) /*!< Base offset for target SD10G_LANE_4 */
#define VTSS_TO_SD10G_LANE_5    VTSS_IO_OFFSET1(0x01498000) /*!< Base offset for target SD10G_LANE_5 */
#define VTSS_TO_SD10G_LANE_6    VTSS_IO_OFFSET1(0x014a0000) /*!< Base offset for target SD10G_LANE_6 */
#define VTSS_TO_SD10G_LANE_7    VTSS_IO_OFFSET1(0x014a8000) /*!< Base offset for target SD10G_LANE_7 */
#define VTSS_TO_SD10G_LANE_8    VTSS_IO_OFFSET1(0x014b0000) /*!< Base offset for target SD10G_LANE_8 */
#define VTSS_TO_SD10G_LANE_9    VTSS_IO_OFFSET1(0x014b8000) /*!< Base offset for target SD10G_LANE_9 */
#define VTSS_TO_SD10G_KR_0      VTSS_IO_OFFSET1(0x014c0000) /*!< Base offset for target SD10G_KR_0 */
#define VTSS_TO_SD10G_KR_1      VTSS_IO_OFFSET1(0x014c8000) /*!< Base offset for target SD10G_KR_1 */
#define VTSS_TO_SD10G_KR_2      VTSS_IO_OFFSET1(0x014d0000) /*!< Base offset for target SD10G_KR_2 */
#define VTSS_TO_SD10G_KR_3      VTSS_IO_OFFSET1(0x014d8000) /*!< Base offset for target SD10G_KR_3 */
#define VTSS_TO_SD10G_KR_4      VTSS_IO_OFFSET1(0x014e0000) /*!< Base offset for target SD10G_KR_4 */
#define VTSS_TO_SD10G_KR_5      VTSS_IO_OFFSET1(0x014e8000) /*!< Base offset for target SD10G_KR_5 */
#define VTSS_TO_SD10G_KR_6      VTSS_IO_OFFSET1(0x014f0000) /*!< Base offset for target SD10G_KR_6 */
#define VTSS_TO_SD10G_KR_7      VTSS_IO_OFFSET1(0x014f8000) /*!< Base offset for target SD10G_KR_7 */
#define VTSS_TO_SD10G_KR_8      VTSS_IO_OFFSET1(0x01500000) /*!< Base offset for target SD10G_KR_8 */
#define VTSS_TO_SD10G_KR_9      VTSS_IO_OFFSET1(0x01508000) /*!< Base offset for target SD10G_KR_9 */
#define VTSS_TO_SD_LANE_0       VTSS_IO_OFFSET1(0x01510000) /*!< Base offset for target SD_LANE_0 */
#define VTSS_TO_SD_LANE_1       VTSS_IO_OFFSET1(0x01518000) /*!< Base offset for target SD_LANE_1 */
#define VTSS_TO_SD_LANE_2       VTSS_IO_OFFSET1(0x01520000) /*!< Base offset for target SD_LANE_2 */
#define VTSS_TO_SD_LANE_3       VTSS_IO_OFFSET1(0x01528000) /*!< Base offset for target SD_LANE_3 */
#define VTSS_TO_SD_LANE_4       VTSS_IO_OFFSET1(0x01530000) /*!< Base offset for target SD_LANE_4 */
#define VTSS_TO_SD_LANE_5       VTSS_IO_OFFSET1(0x01538000) /*!< Base offset for target SD_LANE_5 */
#define VTSS_TO_SD_LANE_6       VTSS_IO_OFFSET1(0x01540000) /*!< Base offset for target SD_LANE_6 */
#define VTSS_TO_SD_LANE_7       VTSS_IO_OFFSET1(0x01548000) /*!< Base offset for target SD_LANE_7 */
#define VTSS_TO_SD_LANE_8       VTSS_IO_OFFSET1(0x01550000) /*!< Base offset for target SD_LANE_8 */
#define VTSS_TO_SD_LANE_9       VTSS_IO_OFFSET1(0x01558000) /*!< Base offset for target SD_LANE_9 */
#define VTSS_TO_VCAP_ES0        VTSS_IO_OFFSET1(0x000e0000) /*!< Base offset for target VCAP_ES0 */
#define VTSS_TO_VCAP_ES2        VTSS_IO_OFFSET1(0x000d0000) /*!< Base offset for target VCAP_ES2 */
#define VTSS_TO_VCAP_IP6PFX     VTSS_IO_OFFSET1(0x00090000) /*!< Base offset for target VCAP_IP6PFX */
#define VTSS_TO_VCAP_SUPER      VTSS_IO_OFFSET1(0x00080000) /*!< Base offset for target VCAP_SUPER */
#define VTSS_TO_VOP             VTSS_IO_OFFSET1(0x00a00000) /*!< Base offset for target VOP */
#define VTSS_TO_VOP_L3          VTSS_IO_OFFSET1(0x00b00000) /*!< Base offset for target VOP_L3 */
#define VTSS_TO_VOP_MRP         VTSS_IO_OFFSET1(0x00700000) /*!< Base offset for target VOP_MRP */
#define VTSS_TO_VOP_DLR         VTSS_IO_OFFSET1(0x00780000) /*!< Base offset for target VOP_DLR */
#define VTSS_TO_VOP_MPLS        VTSS_IO_OFFSET1(0x00680000) /*!< Base offset for target VOP_MPLS */
#define VTSS_TO_XQS             VTSS_IO_OFFSET1(0x000c0000) /*!< Base offset for target XQS */

/* IO address mapping macro - may be changed for platform */
#if !defined(VTSS_IOADDR)
#define VTSS_IOADDR(t,o)        ((t) + ((o) << 2))
#endif

#if !defined(VTSS_IOADDR_IX)
#define VTSS_IOADDR_IX(t,o,g,gw,r,ro)     ((t) + (((o) + ((g) * (gw)) + (ro) + (r)) << 2))
#endif

/* IO register access macro - may be changed for platform */
#if !defined(VTSS_IOREG)
/**
 * @param t - target base offset
 * @param o - subtarget offset
 */
#define VTSS_IOREG(t,o)      (*((volatile uint32_t*)(VTSS_IOADDR(t,o))))
#endif

#ifdef VTSS_LAGUNA_WANT_TARGET_ENUMS
/*
 * This section is primarily for documentation purposes.
 */

/**
  * \brief Target MCAN target offset(s)
  */
enum vtss_target_MCAN_e {
    VTSS_TOE_MCAN_0          = VTSS_TO_MCAN_0,
    VTSS_TOE_MCAN_1          = VTSS_TO_MCAN_1,
};

/**
  * \brief Target TZAESB target offset(s)
  */
enum vtss_target_TZAESB_e {
    VTSS_TOE_TZAESBNS        = VTSS_TO_TZAESBNS,
    VTSS_TOE_TZAESBS         = VTSS_TO_TZAESBS,
};

/**
  * \brief Target RB target offset(s)
  */
enum vtss_target_RB_e {
    VTSS_TOE_RB_0            = VTSS_TO_RB_0,
    VTSS_TOE_RB_1            = VTSS_TO_RB_1,
    VTSS_TOE_RB_2            = VTSS_TO_RB_2,
    VTSS_TOE_RB_3            = VTSS_TO_RB_3,
    VTSS_TOE_RB_4            = VTSS_TO_RB_4,
};

/**
  * \brief Target QSPI target offset(s)
  */
enum vtss_target_QSPI_e {
    VTSS_TOE_QSPI_0          = VTSS_TO_QSPI_0,
    VTSS_TOE_QSPI_2          = VTSS_TO_QSPI_2,
};

/**
  * \brief Target IP_KRANEG target offset(s)
  */
enum vtss_target_IP_KRANEG_e {
    VTSS_TOE_SD10G_KR_0      = VTSS_TO_SD10G_KR_0,
    VTSS_TOE_SD10G_KR_1      = VTSS_TO_SD10G_KR_1,
    VTSS_TOE_SD10G_KR_2      = VTSS_TO_SD10G_KR_2,
    VTSS_TOE_SD10G_KR_3      = VTSS_TO_SD10G_KR_3,
    VTSS_TOE_SD10G_KR_4      = VTSS_TO_SD10G_KR_4,
    VTSS_TOE_SD10G_KR_5      = VTSS_TO_SD10G_KR_5,
    VTSS_TOE_SD10G_KR_6      = VTSS_TO_SD10G_KR_6,
    VTSS_TOE_SD10G_KR_7      = VTSS_TO_SD10G_KR_7,
    VTSS_TOE_SD10G_KR_8      = VTSS_TO_SD10G_KR_8,
    VTSS_TOE_SD10G_KR_9      = VTSS_TO_SD10G_KR_9,
};

/**
  * \brief Target PCS_10GBASE_R target offset(s)
  */
enum vtss_target_PCS_10GBASE_R_e {
    VTSS_TOE_PCS5G_BR_0      = VTSS_TO_PCS5G_BR_0,
    VTSS_TOE_PCS5G_BR_1      = VTSS_TO_PCS5G_BR_1,
    VTSS_TOE_PCS5G_BR_2      = VTSS_TO_PCS5G_BR_2,
    VTSS_TOE_PCS5G_BR_3      = VTSS_TO_PCS5G_BR_3,
    VTSS_TOE_PCS10G_BR_0     = VTSS_TO_PCS10G_BR_0,
    VTSS_TOE_PCS10G_BR_1     = VTSS_TO_PCS10G_BR_1,
    VTSS_TOE_PCS10G_BR_2     = VTSS_TO_PCS10G_BR_2,
    VTSS_TOE_PCS10G_BR_3     = VTSS_TO_PCS10G_BR_3,
    VTSS_TOE_PCS10G_BR_4     = VTSS_TO_PCS10G_BR_4,
    VTSS_TOE_PCS10G_BR_5     = VTSS_TO_PCS10G_BR_5,
    VTSS_TOE_PCS10G_BR_6     = VTSS_TO_PCS10G_BR_6,
    VTSS_TOE_PCS10G_BR_7     = VTSS_TO_PCS10G_BR_7,
    VTSS_TOE_PCS10G_BR_8     = VTSS_TO_PCS10G_BR_8,
    VTSS_TOE_PCS10G_BR_9     = VTSS_TO_PCS10G_BR_9,
};

/**
  * \brief Target DEV10G target offset(s)
  */
enum vtss_target_DEV10G_e {
    VTSS_TOE_DEV5G_0         = VTSS_TO_DEV5G_0,
    VTSS_TOE_DEV5G_1         = VTSS_TO_DEV5G_1,
    VTSS_TOE_DEV5G_2         = VTSS_TO_DEV5G_2,
    VTSS_TOE_DEV5G_3         = VTSS_TO_DEV5G_3,
    VTSS_TOE_DEV10G_0        = VTSS_TO_DEV10G_0,
    VTSS_TOE_DEV10G_1        = VTSS_TO_DEV10G_1,
    VTSS_TOE_DEV10G_2        = VTSS_TO_DEV10G_2,
    VTSS_TOE_DEV10G_3        = VTSS_TO_DEV10G_3,
    VTSS_TOE_DEV10G_4        = VTSS_TO_DEV10G_4,
    VTSS_TOE_DEV10G_5        = VTSS_TO_DEV10G_5,
    VTSS_TOE_DEV10G_6        = VTSS_TO_DEV10G_6,
    VTSS_TOE_DEV10G_7        = VTSS_TO_DEV10G_7,
    VTSS_TOE_DEV10G_8        = VTSS_TO_DEV10G_8,
    VTSS_TOE_DEV10G_9        = VTSS_TO_DEV10G_9,
};

/**
  * \brief Target FLEXCOM target offset(s)
  */
enum vtss_target_FLEXCOM_e {
    VTSS_TOE_FLEXCOM_0       = VTSS_TO_FLEXCOM_0,
    VTSS_TOE_FLEXCOM_1       = VTSS_TO_FLEXCOM_1,
    VTSS_TOE_FLEXCOM_2       = VTSS_TO_FLEXCOM_2,
    VTSS_TOE_FLEXCOM_3       = VTSS_TO_FLEXCOM_3,
};

/**
  * \brief Target SD_LANE_TARGET target offset(s)
  */
enum vtss_target_SD_LANE_TARGET_e {
    VTSS_TOE_SD_LANE_0       = VTSS_TO_SD_LANE_0,
    VTSS_TOE_SD_LANE_1       = VTSS_TO_SD_LANE_1,
    VTSS_TOE_SD_LANE_2       = VTSS_TO_SD_LANE_2,
    VTSS_TOE_SD_LANE_3       = VTSS_TO_SD_LANE_3,
    VTSS_TOE_SD_LANE_4       = VTSS_TO_SD_LANE_4,
    VTSS_TOE_SD_LANE_5       = VTSS_TO_SD_LANE_5,
    VTSS_TOE_SD_LANE_6       = VTSS_TO_SD_LANE_6,
    VTSS_TOE_SD_LANE_7       = VTSS_TO_SD_LANE_7,
    VTSS_TOE_SD_LANE_8       = VTSS_TO_SD_LANE_8,
    VTSS_TOE_SD_LANE_9       = VTSS_TO_SD_LANE_9,
};

/**
  * \brief Target DEV1G target offset(s)
  */
enum vtss_target_DEV1G_e {
    VTSS_TOE_DEV2G5_1        = VTSS_TO_DEV2G5_1,
    VTSS_TOE_DEV2G5_2        = VTSS_TO_DEV2G5_2,
    VTSS_TOE_DEV2G5_3        = VTSS_TO_DEV2G5_3,
    VTSS_TOE_DEV2G5_5        = VTSS_TO_DEV2G5_5,
    VTSS_TOE_DEV2G5_6        = VTSS_TO_DEV2G5_6,
    VTSS_TOE_DEV2G5_7        = VTSS_TO_DEV2G5_7,
    VTSS_TOE_DEV2G5_10       = VTSS_TO_DEV2G5_10,
    VTSS_TOE_DEV2G5_11       = VTSS_TO_DEV2G5_11,
    VTSS_TOE_DEV2G5_14       = VTSS_TO_DEV2G5_14,
    VTSS_TOE_DEV2G5_15       = VTSS_TO_DEV2G5_15,
    VTSS_TOE_DEV2G5_18       = VTSS_TO_DEV2G5_18,
    VTSS_TOE_DEV2G5_19       = VTSS_TO_DEV2G5_19,
    VTSS_TOE_DEV2G5_22       = VTSS_TO_DEV2G5_22,
    VTSS_TOE_DEV2G5_23       = VTSS_TO_DEV2G5_23,
    VTSS_TOE_DEVRGMII_0      = VTSS_TO_DEVRGMII_0,
    VTSS_TOE_DEVRGMII_1      = VTSS_TO_DEVRGMII_1,
    VTSS_TOE_DEV2G5_9        = VTSS_TO_DEV2G5_9,
    VTSS_TOE_DEV2G5_13       = VTSS_TO_DEV2G5_13,
    VTSS_TOE_DEV2G5_17       = VTSS_TO_DEV2G5_17,
    VTSS_TOE_DEV2G5_21       = VTSS_TO_DEV2G5_21,
    VTSS_TOE_DEV2G5_0        = VTSS_TO_DEV2G5_0,
    VTSS_TOE_DEV2G5_4        = VTSS_TO_DEV2G5_4,
    VTSS_TOE_DEV2G5_8        = VTSS_TO_DEV2G5_8,
    VTSS_TOE_DEV2G5_12       = VTSS_TO_DEV2G5_12,
    VTSS_TOE_DEV2G5_16       = VTSS_TO_DEV2G5_16,
    VTSS_TOE_DEV2G5_20       = VTSS_TO_DEV2G5_20,
    VTSS_TOE_DEV2G5_24       = VTSS_TO_DEV2G5_24,
    VTSS_TOE_DEV2G5_25       = VTSS_TO_DEV2G5_25,
    VTSS_TOE_DEV2G5_26       = VTSS_TO_DEV2G5_26,
    VTSS_TOE_DEV2G5_27       = VTSS_TO_DEV2G5_27,
};

/**
  * \brief Target SD10G_CMU_TARGET target offset(s)
  */
enum vtss_target_SD10G_CMU_TARGET_e {
    VTSS_TOE_SD_CMU_0        = VTSS_TO_SD_CMU_0,
    VTSS_TOE_SD_CMU_1        = VTSS_TO_SD_CMU_1,
    VTSS_TOE_SD_CMU_2        = VTSS_TO_SD_CMU_2,
    VTSS_TOE_SD_CMU_3        = VTSS_TO_SD_CMU_3,
    VTSS_TOE_SD_CMU_4        = VTSS_TO_SD_CMU_4,
    VTSS_TOE_SD_CMU_5        = VTSS_TO_SD_CMU_5,
};

/**
  * \brief Target SDMMC target offset(s)
  */
enum vtss_target_SDMMC_e {
    VTSS_TOE_SDMMC_0         = VTSS_TO_SDMMC_0,
    VTSS_TOE_SDMMC_1         = VTSS_TO_SDMMC_1,
};

/**
  * \brief Target SD_CMU_NONTERM_TARGET target offset(s)
  */
enum vtss_target_SD_CMU_NONTERM_TARGET_e {
    VTSS_TOE_SD_CMU_CFG_1    = VTSS_TO_SD_CMU_CFG_1,
    VTSS_TOE_SD_CMU_CFG_2    = VTSS_TO_SD_CMU_CFG_2,
    VTSS_TOE_SD_CMU_CFG_3    = VTSS_TO_SD_CMU_CFG_3,
    VTSS_TOE_SD_CMU_CFG_4    = VTSS_TO_SD_CMU_CFG_4,
    VTSS_TOE_SD_CMU_CFG_5    = VTSS_TO_SD_CMU_CFG_5,
};

/**
  * \brief Target SD10G_LANE_TARGET target offset(s)
  */
enum vtss_target_SD10G_LANE_TARGET_e {
    VTSS_TOE_SD10G_LANE_0    = VTSS_TO_SD10G_LANE_0,
    VTSS_TOE_SD10G_LANE_1    = VTSS_TO_SD10G_LANE_1,
    VTSS_TOE_SD10G_LANE_2    = VTSS_TO_SD10G_LANE_2,
    VTSS_TOE_SD10G_LANE_3    = VTSS_TO_SD10G_LANE_3,
    VTSS_TOE_SD10G_LANE_4    = VTSS_TO_SD10G_LANE_4,
    VTSS_TOE_SD10G_LANE_5    = VTSS_TO_SD10G_LANE_5,
    VTSS_TOE_SD10G_LANE_6    = VTSS_TO_SD10G_LANE_6,
    VTSS_TOE_SD10G_LANE_7    = VTSS_TO_SD10G_LANE_7,
    VTSS_TOE_SD10G_LANE_8    = VTSS_TO_SD10G_LANE_8,
    VTSS_TOE_SD10G_LANE_9    = VTSS_TO_SD10G_LANE_9,
};

/**
  * \brief Target DEVCPU_ORG target offset(s)
  */
enum vtss_target_DEVCPU_ORG_e {
    VTSS_TOE_DEVCPU_ORG0     = VTSS_TO_DEVCPU_ORG0,
    VTSS_TOE_DEVCPU_ORG1     = VTSS_TO_DEVCPU_ORG1,
    VTSS_TOE_DEVCPU_ORG2     = VTSS_TO_DEVCPU_ORG2,
};

#endif /* VTSS_LAGUNA_WANT_TARGET_ENUMS */

#endif // 0

#endif /* _VTSS_LAGUNA_REGS_COMMON_H_ */
