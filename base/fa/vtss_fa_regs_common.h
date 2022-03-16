// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_COMMON_H_
#define _VTSS_FA_REGS_COMMON_H_


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

/* Main target address offsets */
#ifndef VTSS_IO_ORIGIN1_OFFSET
#define VTSS_IO_ORIGIN1_OFFSET 0x010000000 /*! default region*/
#endif
#ifndef VTSS_IO_ORIGIN1_SIZE
#define VTSS_IO_ORIGIN1_SIZE 0x010000000
#endif
#ifndef VTSS_IO_OFFSET1
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)
#endif
#define VTSS_TO_AFI             VTSS_IO_OFFSET1(0x01240000) /*!< Base offset for target AFI */
#define VTSS_TO_ANA_AC          VTSS_IO_OFFSET1(0x01900000) /*!< Base offset for target ANA_AC */
#define VTSS_TO_ANA_AC_OAM_MOD  VTSS_IO_OFFSET1(0x01070000) /*!< Base offset for target ANA_AC_OAM_MOD */
#define VTSS_TO_ANA_AC_POL      VTSS_IO_OFFSET1(0x01200000) /*!< Base offset for target ANA_AC_POL */
#define VTSS_TO_ANA_AC_SDLB     VTSS_IO_OFFSET1(0x01500000) /*!< Base offset for target ANA_AC_SDLB */
#define VTSS_TO_ANA_ACL         VTSS_IO_OFFSET1(0x01050000) /*!< Base offset for target ANA_ACL */
#define VTSS_TO_ANA_CL          VTSS_IO_OFFSET1(0x01400000) /*!< Base offset for target ANA_CL */
#define VTSS_TO_ANA_L2          VTSS_IO_OFFSET1(0x01800000) /*!< Base offset for target ANA_L2 */
#define VTSS_TO_ANA_L3          VTSS_IO_OFFSET1(0x01480000) /*!< Base offset for target ANA_L3 */
#define VTSS_TO_ASM             VTSS_IO_OFFSET1(0x00600000) /*!< Base offset for target ASM */
#define VTSS_TO_CHIP_TOP        VTSS_IO_OFFSET1(0x01020000) /*!< Base offset for target CHIP_TOP */
#define VTSS_TO_CLKGEN          VTSS_IO_OFFSET1(0x01100000) /*!< Base offset for target CLKGEN */
#define VTSS_TO_DEV10G_0        VTSS_IO_OFFSET1(0x00074000) /*!< Base offset for target DEV10G_0 */
#define VTSS_TO_DEV10G_1        VTSS_IO_OFFSET1(0x0042c000) /*!< Base offset for target DEV10G_1 */
#define VTSS_TO_DEV10G_2        VTSS_IO_OFFSET1(0x00080000) /*!< Base offset for target DEV10G_2 */
#define VTSS_TO_DEV10G_3        VTSS_IO_OFFSET1(0x0008c000) /*!< Base offset for target DEV10G_3 */
#define VTSS_TO_DEV10G_4        VTSS_IO_OFFSET1(0x00458000) /*!< Base offset for target DEV10G_4 */
#define VTSS_TO_DEV10G_5        VTSS_IO_OFFSET1(0x00464000) /*!< Base offset for target DEV10G_5 */
#define VTSS_TO_DEV10G_6        VTSS_IO_OFFSET1(0x00470000) /*!< Base offset for target DEV10G_6 */
#define VTSS_TO_DEV10G_7        VTSS_IO_OFFSET1(0x0047c000) /*!< Base offset for target DEV10G_7 */
#define VTSS_TO_DEV10G_8        VTSS_IO_OFFSET1(0x00488000) /*!< Base offset for target DEV10G_8 */
#define VTSS_TO_DEV10G_9        VTSS_IO_OFFSET1(0x00494000) /*!< Base offset for target DEV10G_9 */
#define VTSS_TO_DEV10G_10       VTSS_IO_OFFSET1(0x004a0000) /*!< Base offset for target DEV10G_10 */
#define VTSS_TO_DEV10G_11       VTSS_IO_OFFSET1(0x004ac000) /*!< Base offset for target DEV10G_11 */
#define VTSS_TO_DEV25G_0        VTSS_IO_OFFSET1(0x004b8000) /*!< Base offset for target DEV25G_0 */
#define VTSS_TO_DEV25G_1        VTSS_IO_OFFSET1(0x000f8000) /*!< Base offset for target DEV25G_1 */
#define VTSS_TO_DEV25G_2        VTSS_IO_OFFSET1(0x004c8000) /*!< Base offset for target DEV25G_2 */
#define VTSS_TO_DEV25G_3        VTSS_IO_OFFSET1(0x00108000) /*!< Base offset for target DEV25G_3 */
#define VTSS_TO_DEV25G_4        VTSS_IO_OFFSET1(0x00118000) /*!< Base offset for target DEV25G_4 */
#define VTSS_TO_DEV25G_5        VTSS_IO_OFFSET1(0x004d8000) /*!< Base offset for target DEV25G_5 */
#define VTSS_TO_DEV25G_6        VTSS_IO_OFFSET1(0x004e8000) /*!< Base offset for target DEV25G_6 */
#define VTSS_TO_DEV25G_7        VTSS_IO_OFFSET1(0x004f8000) /*!< Base offset for target DEV25G_7 */
#define VTSS_TO_DEV2G5_0        VTSS_IO_OFFSET1(0x00004000) /*!< Base offset for target DEV2G5_0 */
#define VTSS_TO_DEV2G5_1        VTSS_IO_OFFSET1(0x00010000) /*!< Base offset for target DEV2G5_1 */
#define VTSS_TO_DEV2G5_2        VTSS_IO_OFFSET1(0x0001c000) /*!< Base offset for target DEV2G5_2 */
#define VTSS_TO_DEV2G5_3        VTSS_IO_OFFSET1(0x00404000) /*!< Base offset for target DEV2G5_3 */
#define VTSS_TO_DEV2G5_4        VTSS_IO_OFFSET1(0x00410000) /*!< Base offset for target DEV2G5_4 */
#define VTSS_TO_DEV2G5_5        VTSS_IO_OFFSET1(0x0041c000) /*!< Base offset for target DEV2G5_5 */
#define VTSS_TO_DEV2G5_6        VTSS_IO_OFFSET1(0x00028000) /*!< Base offset for target DEV2G5_6 */
#define VTSS_TO_DEV2G5_7        VTSS_IO_OFFSET1(0x00034000) /*!< Base offset for target DEV2G5_7 */
#define VTSS_TO_DEV2G5_8        VTSS_IO_OFFSET1(0x00040000) /*!< Base offset for target DEV2G5_8 */
#define VTSS_TO_DEV2G5_9        VTSS_IO_OFFSET1(0x0004c000) /*!< Base offset for target DEV2G5_9 */
#define VTSS_TO_DEV2G5_10       VTSS_IO_OFFSET1(0x00058000) /*!< Base offset for target DEV2G5_10 */
#define VTSS_TO_DEV2G5_11       VTSS_IO_OFFSET1(0x00064000) /*!< Base offset for target DEV2G5_11 */
#define VTSS_TO_DEV2G5_12       VTSS_IO_OFFSET1(0x00070000) /*!< Base offset for target DEV2G5_12 */
#define VTSS_TO_DEV2G5_13       VTSS_IO_OFFSET1(0x00428000) /*!< Base offset for target DEV2G5_13 */
#define VTSS_TO_DEV2G5_14       VTSS_IO_OFFSET1(0x0007c000) /*!< Base offset for target DEV2G5_14 */
#define VTSS_TO_DEV2G5_15       VTSS_IO_OFFSET1(0x00088000) /*!< Base offset for target DEV2G5_15 */
#define VTSS_TO_DEV2G5_16       VTSS_IO_OFFSET1(0x00094000) /*!< Base offset for target DEV2G5_16 */
#define VTSS_TO_DEV2G5_17       VTSS_IO_OFFSET1(0x00098000) /*!< Base offset for target DEV2G5_17 */
#define VTSS_TO_DEV2G5_18       VTSS_IO_OFFSET1(0x0009c000) /*!< Base offset for target DEV2G5_18 */
#define VTSS_TO_DEV2G5_19       VTSS_IO_OFFSET1(0x000a0000) /*!< Base offset for target DEV2G5_19 */
#define VTSS_TO_DEV2G5_20       VTSS_IO_OFFSET1(0x000a4000) /*!< Base offset for target DEV2G5_20 */
#define VTSS_TO_DEV2G5_21       VTSS_IO_OFFSET1(0x000a8000) /*!< Base offset for target DEV2G5_21 */
#define VTSS_TO_DEV2G5_22       VTSS_IO_OFFSET1(0x000ac000) /*!< Base offset for target DEV2G5_22 */
#define VTSS_TO_DEV2G5_23       VTSS_IO_OFFSET1(0x000b0000) /*!< Base offset for target DEV2G5_23 */
#define VTSS_TO_DEV2G5_24       VTSS_IO_OFFSET1(0x00434000) /*!< Base offset for target DEV2G5_24 */
#define VTSS_TO_DEV2G5_25       VTSS_IO_OFFSET1(0x00438000) /*!< Base offset for target DEV2G5_25 */
#define VTSS_TO_DEV2G5_26       VTSS_IO_OFFSET1(0x0043c000) /*!< Base offset for target DEV2G5_26 */
#define VTSS_TO_DEV2G5_27       VTSS_IO_OFFSET1(0x00440000) /*!< Base offset for target DEV2G5_27 */
#define VTSS_TO_DEV2G5_28       VTSS_IO_OFFSET1(0x00444000) /*!< Base offset for target DEV2G5_28 */
#define VTSS_TO_DEV2G5_29       VTSS_IO_OFFSET1(0x00448000) /*!< Base offset for target DEV2G5_29 */
#define VTSS_TO_DEV2G5_30       VTSS_IO_OFFSET1(0x0044c000) /*!< Base offset for target DEV2G5_30 */
#define VTSS_TO_DEV2G5_31       VTSS_IO_OFFSET1(0x00450000) /*!< Base offset for target DEV2G5_31 */
#define VTSS_TO_DEV2G5_32       VTSS_IO_OFFSET1(0x000b4000) /*!< Base offset for target DEV2G5_32 */
#define VTSS_TO_DEV2G5_33       VTSS_IO_OFFSET1(0x000b8000) /*!< Base offset for target DEV2G5_33 */
#define VTSS_TO_DEV2G5_34       VTSS_IO_OFFSET1(0x000bc000) /*!< Base offset for target DEV2G5_34 */
#define VTSS_TO_DEV2G5_35       VTSS_IO_OFFSET1(0x000c0000) /*!< Base offset for target DEV2G5_35 */
#define VTSS_TO_DEV2G5_36       VTSS_IO_OFFSET1(0x000c4000) /*!< Base offset for target DEV2G5_36 */
#define VTSS_TO_DEV2G5_37       VTSS_IO_OFFSET1(0x000c8000) /*!< Base offset for target DEV2G5_37 */
#define VTSS_TO_DEV2G5_38       VTSS_IO_OFFSET1(0x000cc000) /*!< Base offset for target DEV2G5_38 */
#define VTSS_TO_DEV2G5_39       VTSS_IO_OFFSET1(0x000d0000) /*!< Base offset for target DEV2G5_39 */
#define VTSS_TO_DEV2G5_40       VTSS_IO_OFFSET1(0x000d4000) /*!< Base offset for target DEV2G5_40 */
#define VTSS_TO_DEV2G5_41       VTSS_IO_OFFSET1(0x000d8000) /*!< Base offset for target DEV2G5_41 */
#define VTSS_TO_DEV2G5_42       VTSS_IO_OFFSET1(0x000dc000) /*!< Base offset for target DEV2G5_42 */
#define VTSS_TO_DEV2G5_43       VTSS_IO_OFFSET1(0x000e0000) /*!< Base offset for target DEV2G5_43 */
#define VTSS_TO_DEV2G5_44       VTSS_IO_OFFSET1(0x000e4000) /*!< Base offset for target DEV2G5_44 */
#define VTSS_TO_DEV2G5_45       VTSS_IO_OFFSET1(0x000e8000) /*!< Base offset for target DEV2G5_45 */
#define VTSS_TO_DEV2G5_46       VTSS_IO_OFFSET1(0x000ec000) /*!< Base offset for target DEV2G5_46 */
#define VTSS_TO_DEV2G5_47       VTSS_IO_OFFSET1(0x000f0000) /*!< Base offset for target DEV2G5_47 */
#define VTSS_TO_DEV2G5_48       VTSS_IO_OFFSET1(0x00454000) /*!< Base offset for target DEV2G5_48 */
#define VTSS_TO_DEV2G5_49       VTSS_IO_OFFSET1(0x00460000) /*!< Base offset for target DEV2G5_49 */
#define VTSS_TO_DEV2G5_50       VTSS_IO_OFFSET1(0x0046c000) /*!< Base offset for target DEV2G5_50 */
#define VTSS_TO_DEV2G5_51       VTSS_IO_OFFSET1(0x00478000) /*!< Base offset for target DEV2G5_51 */
#define VTSS_TO_DEV2G5_52       VTSS_IO_OFFSET1(0x00484000) /*!< Base offset for target DEV2G5_52 */
#define VTSS_TO_DEV2G5_53       VTSS_IO_OFFSET1(0x00490000) /*!< Base offset for target DEV2G5_53 */
#define VTSS_TO_DEV2G5_54       VTSS_IO_OFFSET1(0x0049c000) /*!< Base offset for target DEV2G5_54 */
#define VTSS_TO_DEV2G5_55       VTSS_IO_OFFSET1(0x004a8000) /*!< Base offset for target DEV2G5_55 */
#define VTSS_TO_DEV2G5_56       VTSS_IO_OFFSET1(0x004b4000) /*!< Base offset for target DEV2G5_56 */
#define VTSS_TO_DEV2G5_57       VTSS_IO_OFFSET1(0x000f4000) /*!< Base offset for target DEV2G5_57 */
#define VTSS_TO_DEV2G5_58       VTSS_IO_OFFSET1(0x004c4000) /*!< Base offset for target DEV2G5_58 */
#define VTSS_TO_DEV2G5_59       VTSS_IO_OFFSET1(0x00104000) /*!< Base offset for target DEV2G5_59 */
#define VTSS_TO_DEV2G5_60       VTSS_IO_OFFSET1(0x00114000) /*!< Base offset for target DEV2G5_60 */
#define VTSS_TO_DEV2G5_61       VTSS_IO_OFFSET1(0x004d4000) /*!< Base offset for target DEV2G5_61 */
#define VTSS_TO_DEV2G5_62       VTSS_IO_OFFSET1(0x004e4000) /*!< Base offset for target DEV2G5_62 */
#define VTSS_TO_DEV2G5_63       VTSS_IO_OFFSET1(0x004f4000) /*!< Base offset for target DEV2G5_63 */
#define VTSS_TO_DEV2G5_64       VTSS_IO_OFFSET1(0x00124000) /*!< Base offset for target DEV2G5_64 */
#define VTSS_TO_DEV5G_0         VTSS_IO_OFFSET1(0x00008000) /*!< Base offset for target DEV5G_0 */
#define VTSS_TO_DEV5G_1         VTSS_IO_OFFSET1(0x00014000) /*!< Base offset for target DEV5G_1 */
#define VTSS_TO_DEV5G_2         VTSS_IO_OFFSET1(0x00020000) /*!< Base offset for target DEV5G_2 */
#define VTSS_TO_DEV5G_3         VTSS_IO_OFFSET1(0x00408000) /*!< Base offset for target DEV5G_3 */
#define VTSS_TO_DEV5G_4         VTSS_IO_OFFSET1(0x00414000) /*!< Base offset for target DEV5G_4 */
#define VTSS_TO_DEV5G_5         VTSS_IO_OFFSET1(0x00420000) /*!< Base offset for target DEV5G_5 */
#define VTSS_TO_DEV5G_6         VTSS_IO_OFFSET1(0x0002c000) /*!< Base offset for target DEV5G_6 */
#define VTSS_TO_DEV5G_7         VTSS_IO_OFFSET1(0x00038000) /*!< Base offset for target DEV5G_7 */
#define VTSS_TO_DEV5G_8         VTSS_IO_OFFSET1(0x00044000) /*!< Base offset for target DEV5G_8 */
#define VTSS_TO_DEV5G_9         VTSS_IO_OFFSET1(0x00050000) /*!< Base offset for target DEV5G_9 */
#define VTSS_TO_DEV5G_10        VTSS_IO_OFFSET1(0x0005c000) /*!< Base offset for target DEV5G_10 */
#define VTSS_TO_DEV5G_11        VTSS_IO_OFFSET1(0x00068000) /*!< Base offset for target DEV5G_11 */
#define VTSS_TO_DEV5G_64        VTSS_IO_OFFSET1(0x00128000) /*!< Base offset for target DEV5G_64 */
#define VTSS_TO_DEVCPU_GCB      VTSS_IO_OFFSET1(0x01010000) /*!< Base offset for target DEVCPU_GCB */
#define VTSS_TO_DEVCPU_ORG0     VTSS_IO_OFFSET1(0x00000000) /*!< Base offset for target DEVCPU_ORG0 */
#define VTSS_TO_DEVCPU_ORG1     VTSS_IO_OFFSET1(0x00400000) /*!< Base offset for target DEVCPU_ORG1 */
#define VTSS_TO_DEVCPU_ORG2     VTSS_IO_OFFSET1(0x00800000) /*!< Base offset for target DEVCPU_ORG2 */
#define VTSS_TO_DEVCPU_ORG3     VTSS_IO_OFFSET1(0x00c00000) /*!< Base offset for target DEVCPU_ORG3 */
#define VTSS_TO_DEVCPU_ORG4     VTSS_IO_OFFSET1(0x01000000) /*!< Base offset for target DEVCPU_ORG4 */
#define VTSS_TO_DEVCPU_PTP      VTSS_IO_OFFSET1(0x01040000) /*!< Base offset for target DEVCPU_PTP */
#define VTSS_TO_DEVCPU_QS       VTSS_IO_OFFSET1(0x01030000) /*!< Base offset for target DEVCPU_QS */
#define VTSS_TO_DSM             VTSS_IO_OFFSET1(0x00504000) /*!< Base offset for target DSM */
#define VTSS_TO_EACL            VTSS_IO_OFFSET1(0x012c0000) /*!< Base offset for target EACL */
#define VTSS_TO_HSCH            VTSS_IO_OFFSET1(0x01580000) /*!< Base offset for target HSCH */
#define VTSS_TO_HSIO_WRAP       VTSS_IO_OFFSET1(0x00508000) /*!< Base offset for target HSIO_WRAP */
#define VTSS_TO_LCPLL28_1       VTSS_IO_OFFSET1(0x010f0000) /*!< Base offset for target LCPLL28_1 */
#define VTSS_TO_LRN             VTSS_IO_OFFSET1(0x01060000) /*!< Base offset for target LRN */
#define VTSS_TO_PCIE_PHY_WRAP   VTSS_IO_OFFSET1(0x00dd8000) /*!< Base offset for target PCIE_PHY_WRAP */
#define VTSS_TO_PCS10G_BR_0     VTSS_IO_OFFSET1(0x00078000) /*!< Base offset for target PCS10G_BR_0 */
#define VTSS_TO_PCS10G_BR_1     VTSS_IO_OFFSET1(0x00430000) /*!< Base offset for target PCS10G_BR_1 */
#define VTSS_TO_PCS10G_BR_2     VTSS_IO_OFFSET1(0x00084000) /*!< Base offset for target PCS10G_BR_2 */
#define VTSS_TO_PCS10G_BR_3     VTSS_IO_OFFSET1(0x00090000) /*!< Base offset for target PCS10G_BR_3 */
#define VTSS_TO_PCS10G_BR_4     VTSS_IO_OFFSET1(0x0045c000) /*!< Base offset for target PCS10G_BR_4 */
#define VTSS_TO_PCS10G_BR_5     VTSS_IO_OFFSET1(0x00468000) /*!< Base offset for target PCS10G_BR_5 */
#define VTSS_TO_PCS10G_BR_6     VTSS_IO_OFFSET1(0x00474000) /*!< Base offset for target PCS10G_BR_6 */
#define VTSS_TO_PCS10G_BR_7     VTSS_IO_OFFSET1(0x00480000) /*!< Base offset for target PCS10G_BR_7 */
#define VTSS_TO_PCS10G_BR_8     VTSS_IO_OFFSET1(0x0048c000) /*!< Base offset for target PCS10G_BR_8 */
#define VTSS_TO_PCS10G_BR_9     VTSS_IO_OFFSET1(0x00498000) /*!< Base offset for target PCS10G_BR_9 */
#define VTSS_TO_PCS10G_BR_10    VTSS_IO_OFFSET1(0x004a4000) /*!< Base offset for target PCS10G_BR_10 */
#define VTSS_TO_PCS10G_BR_11    VTSS_IO_OFFSET1(0x004b0000) /*!< Base offset for target PCS10G_BR_11 */
#define VTSS_TO_PCS25G_BR_0     VTSS_IO_OFFSET1(0x004bc000) /*!< Base offset for target PCS25G_BR_0 */
#define VTSS_TO_PCS25G_BR_1     VTSS_IO_OFFSET1(0x000fc000) /*!< Base offset for target PCS25G_BR_1 */
#define VTSS_TO_PCS25G_BR_2     VTSS_IO_OFFSET1(0x004cc000) /*!< Base offset for target PCS25G_BR_2 */
#define VTSS_TO_PCS25G_BR_3     VTSS_IO_OFFSET1(0x0010c000) /*!< Base offset for target PCS25G_BR_3 */
#define VTSS_TO_PCS25G_BR_4     VTSS_IO_OFFSET1(0x0011c000) /*!< Base offset for target PCS25G_BR_4 */
#define VTSS_TO_PCS25G_BR_5     VTSS_IO_OFFSET1(0x004dc000) /*!< Base offset for target PCS25G_BR_5 */
#define VTSS_TO_PCS25G_BR_6     VTSS_IO_OFFSET1(0x004ec000) /*!< Base offset for target PCS25G_BR_6 */
#define VTSS_TO_PCS25G_BR_7     VTSS_IO_OFFSET1(0x004fc000) /*!< Base offset for target PCS25G_BR_7 */
#define VTSS_TO_PCS25G_RSFEC_0  VTSS_IO_OFFSET1(0x004c0000) /*!< Base offset for target PCS25G_RSFEC_0 */
#define VTSS_TO_PCS25G_RSFEC_1  VTSS_IO_OFFSET1(0x00100000) /*!< Base offset for target PCS25G_RSFEC_1 */
#define VTSS_TO_PCS25G_RSFEC_2  VTSS_IO_OFFSET1(0x004d0000) /*!< Base offset for target PCS25G_RSFEC_2 */
#define VTSS_TO_PCS25G_RSFEC_3  VTSS_IO_OFFSET1(0x00110000) /*!< Base offset for target PCS25G_RSFEC_3 */
#define VTSS_TO_PCS25G_RSFEC_4  VTSS_IO_OFFSET1(0x00120000) /*!< Base offset for target PCS25G_RSFEC_4 */
#define VTSS_TO_PCS25G_RSFEC_5  VTSS_IO_OFFSET1(0x004e0000) /*!< Base offset for target PCS25G_RSFEC_5 */
#define VTSS_TO_PCS25G_RSFEC_6  VTSS_IO_OFFSET1(0x004f0000) /*!< Base offset for target PCS25G_RSFEC_6 */
#define VTSS_TO_PCS25G_RSFEC_7  VTSS_IO_OFFSET1(0x00500000) /*!< Base offset for target PCS25G_RSFEC_7 */
#define VTSS_TO_PCS5G_BR_0      VTSS_IO_OFFSET1(0x0000c000) /*!< Base offset for target PCS5G_BR_0 */
#define VTSS_TO_PCS5G_BR_1      VTSS_IO_OFFSET1(0x00018000) /*!< Base offset for target PCS5G_BR_1 */
#define VTSS_TO_PCS5G_BR_2      VTSS_IO_OFFSET1(0x00024000) /*!< Base offset for target PCS5G_BR_2 */
#define VTSS_TO_PCS5G_BR_3      VTSS_IO_OFFSET1(0x0040c000) /*!< Base offset for target PCS5G_BR_3 */
#define VTSS_TO_PCS5G_BR_4      VTSS_IO_OFFSET1(0x00418000) /*!< Base offset for target PCS5G_BR_4 */
#define VTSS_TO_PCS5G_BR_5      VTSS_IO_OFFSET1(0x00424000) /*!< Base offset for target PCS5G_BR_5 */
#define VTSS_TO_PCS5G_BR_6      VTSS_IO_OFFSET1(0x00030000) /*!< Base offset for target PCS5G_BR_6 */
#define VTSS_TO_PCS5G_BR_7      VTSS_IO_OFFSET1(0x0003c000) /*!< Base offset for target PCS5G_BR_7 */
#define VTSS_TO_PCS5G_BR_8      VTSS_IO_OFFSET1(0x00048000) /*!< Base offset for target PCS5G_BR_8 */
#define VTSS_TO_PCS5G_BR_9      VTSS_IO_OFFSET1(0x00054000) /*!< Base offset for target PCS5G_BR_9 */
#define VTSS_TO_PCS5G_BR_10     VTSS_IO_OFFSET1(0x00060000) /*!< Base offset for target PCS5G_BR_10 */
#define VTSS_TO_PCS5G_BR_11     VTSS_IO_OFFSET1(0x0006c000) /*!< Base offset for target PCS5G_BR_11 */
#define VTSS_TO_PCS5G_BR_64     VTSS_IO_OFFSET1(0x0012c000) /*!< Base offset for target PCS5G_BR_64 */
#define VTSS_TO_PORT_CONF       VTSS_IO_OFFSET1(0x00130000) /*!< Base offset for target PORT_CONF */
#define VTSS_TO_QFWD            VTSS_IO_OFFSET1(0x010b0000) /*!< Base offset for target QFWD */
#define VTSS_TO_QRES            VTSS_IO_OFFSET1(0x01280000) /*!< Base offset for target QRES */
#define VTSS_TO_QSYS            VTSS_IO_OFFSET1(0x010a0000) /*!< Base offset for target QSYS */
#define VTSS_TO_REW             VTSS_IO_OFFSET1(0x01600000) /*!< Base offset for target REW */
#define VTSS_TO_SD_CMU_0        VTSS_IO_OFFSET1(0x00808000) /*!< Base offset for target SD_CMU_0 */
#define VTSS_TO_SD_CMU_CFG_0    VTSS_IO_OFFSET1(0x00850000) /*!< Base offset for target SD_CMU_CFG_0 */
#define VTSS_TO_SD_CMU_1        VTSS_IO_OFFSET1(0x00810000) /*!< Base offset for target SD_CMU_1 */
#define VTSS_TO_SD_CMU_CFG_1    VTSS_IO_OFFSET1(0x00858000) /*!< Base offset for target SD_CMU_CFG_1 */
#define VTSS_TO_SD_CMU_2        VTSS_IO_OFFSET1(0x00818000) /*!< Base offset for target SD_CMU_2 */
#define VTSS_TO_SD_CMU_CFG_2    VTSS_IO_OFFSET1(0x00860000) /*!< Base offset for target SD_CMU_CFG_2 */
#define VTSS_TO_SD_CMU_3        VTSS_IO_OFFSET1(0x00820000) /*!< Base offset for target SD_CMU_3 */
#define VTSS_TO_SD_CMU_CFG_3    VTSS_IO_OFFSET1(0x00868000) /*!< Base offset for target SD_CMU_CFG_3 */
#define VTSS_TO_SD_CMU_4        VTSS_IO_OFFSET1(0x00828000) /*!< Base offset for target SD_CMU_4 */
#define VTSS_TO_SD_CMU_CFG_4    VTSS_IO_OFFSET1(0x00870000) /*!< Base offset for target SD_CMU_CFG_4 */
#define VTSS_TO_SD_CMU_5        VTSS_IO_OFFSET1(0x00830000) /*!< Base offset for target SD_CMU_5 */
#define VTSS_TO_SD_CMU_CFG_5    VTSS_IO_OFFSET1(0x00878000) /*!< Base offset for target SD_CMU_CFG_5 */
#define VTSS_TO_SD_CMU_6        VTSS_IO_OFFSET1(0x00838000) /*!< Base offset for target SD_CMU_6 */
#define VTSS_TO_SD_CMU_CFG_6    VTSS_IO_OFFSET1(0x00880000) /*!< Base offset for target SD_CMU_CFG_6 */
#define VTSS_TO_SD_CMU_7        VTSS_IO_OFFSET1(0x00840000) /*!< Base offset for target SD_CMU_7 */
#define VTSS_TO_SD_CMU_CFG_7    VTSS_IO_OFFSET1(0x00888000) /*!< Base offset for target SD_CMU_CFG_7 */
#define VTSS_TO_SD_CMU_8        VTSS_IO_OFFSET1(0x00848000) /*!< Base offset for target SD_CMU_8 */
#define VTSS_TO_SD_CMU_CFG_8    VTSS_IO_OFFSET1(0x00890000) /*!< Base offset for target SD_CMU_CFG_8 */
#define VTSS_TO_SD_CMU_9        VTSS_IO_OFFSET1(0x00c08000) /*!< Base offset for target SD_CMU_9 */
#define VTSS_TO_SD_CMU_CFG_9    VTSS_IO_OFFSET1(0x00c30000) /*!< Base offset for target SD_CMU_CFG_9 */
#define VTSS_TO_SD_CMU_10       VTSS_IO_OFFSET1(0x00c10000) /*!< Base offset for target SD_CMU_10 */
#define VTSS_TO_SD_CMU_CFG_10   VTSS_IO_OFFSET1(0x00c38000) /*!< Base offset for target SD_CMU_CFG_10 */
#define VTSS_TO_SD_CMU_11       VTSS_IO_OFFSET1(0x00c18000) /*!< Base offset for target SD_CMU_11 */
#define VTSS_TO_SD_CMU_CFG_11   VTSS_IO_OFFSET1(0x00c40000) /*!< Base offset for target SD_CMU_CFG_11 */
#define VTSS_TO_SD_CMU_12       VTSS_IO_OFFSET1(0x00c20000) /*!< Base offset for target SD_CMU_12 */
#define VTSS_TO_SD_CMU_CFG_12   VTSS_IO_OFFSET1(0x00c48000) /*!< Base offset for target SD_CMU_CFG_12 */
#define VTSS_TO_SD_CMU_13       VTSS_IO_OFFSET1(0x00c28000) /*!< Base offset for target SD_CMU_13 */
#define VTSS_TO_SD_CMU_CFG_13   VTSS_IO_OFFSET1(0x00c50000) /*!< Base offset for target SD_CMU_CFG_13 */
#define VTSS_TO_SD6G_LANE_0     VTSS_IO_OFFSET1(0x00898000) /*!< Base offset for target SD6G_LANE_0 */
#define VTSS_TO_SD6G_LANE_1     VTSS_IO_OFFSET1(0x008a0000) /*!< Base offset for target SD6G_LANE_1 */
#define VTSS_TO_SD6G_LANE_2     VTSS_IO_OFFSET1(0x008a8000) /*!< Base offset for target SD6G_LANE_2 */
#define VTSS_TO_SD6G_LANE_3     VTSS_IO_OFFSET1(0x008b0000) /*!< Base offset for target SD6G_LANE_3 */
#define VTSS_TO_SD6G_LANE_4     VTSS_IO_OFFSET1(0x008b8000) /*!< Base offset for target SD6G_LANE_4 */
#define VTSS_TO_SD6G_LANE_5     VTSS_IO_OFFSET1(0x008c0000) /*!< Base offset for target SD6G_LANE_5 */
#define VTSS_TO_SD6G_LANE_6     VTSS_IO_OFFSET1(0x008c8000) /*!< Base offset for target SD6G_LANE_6 */
#define VTSS_TO_SD6G_LANE_7     VTSS_IO_OFFSET1(0x008d0000) /*!< Base offset for target SD6G_LANE_7 */
#define VTSS_TO_SD6G_LANE_8     VTSS_IO_OFFSET1(0x008d8000) /*!< Base offset for target SD6G_LANE_8 */
#define VTSS_TO_SD6G_LANE_9     VTSS_IO_OFFSET1(0x008e0000) /*!< Base offset for target SD6G_LANE_9 */
#define VTSS_TO_SD6G_LANE_10    VTSS_IO_OFFSET1(0x008e8000) /*!< Base offset for target SD6G_LANE_10 */
#define VTSS_TO_SD6G_LANE_11    VTSS_IO_OFFSET1(0x008f0000) /*!< Base offset for target SD6G_LANE_11 */
#define VTSS_TO_SD6G_LANE_12    VTSS_IO_OFFSET1(0x008f8000) /*!< Base offset for target SD6G_LANE_12 */
#define VTSS_TO_SD10G_LANE_0    VTSS_IO_OFFSET1(0x00900000) /*!< Base offset for target SD10G_LANE_0 */
#define VTSS_TO_SD10G_LANE_1    VTSS_IO_OFFSET1(0x00908000) /*!< Base offset for target SD10G_LANE_1 */
#define VTSS_TO_SD10G_LANE_2    VTSS_IO_OFFSET1(0x00910000) /*!< Base offset for target SD10G_LANE_2 */
#define VTSS_TO_SD10G_LANE_3    VTSS_IO_OFFSET1(0x00918000) /*!< Base offset for target SD10G_LANE_3 */
#define VTSS_TO_SD6G_KR_0       VTSS_IO_OFFSET1(0x00920000) /*!< Base offset for target SD6G_KR_0 */
#define VTSS_TO_SD6G_KR_1       VTSS_IO_OFFSET1(0x00928000) /*!< Base offset for target SD6G_KR_1 */
#define VTSS_TO_SD6G_KR_2       VTSS_IO_OFFSET1(0x00930000) /*!< Base offset for target SD6G_KR_2 */
#define VTSS_TO_SD6G_KR_3       VTSS_IO_OFFSET1(0x00938000) /*!< Base offset for target SD6G_KR_3 */
#define VTSS_TO_SD6G_KR_4       VTSS_IO_OFFSET1(0x00940000) /*!< Base offset for target SD6G_KR_4 */
#define VTSS_TO_SD6G_KR_5       VTSS_IO_OFFSET1(0x00948000) /*!< Base offset for target SD6G_KR_5 */
#define VTSS_TO_SD6G_KR_6       VTSS_IO_OFFSET1(0x00950000) /*!< Base offset for target SD6G_KR_6 */
#define VTSS_TO_SD6G_KR_7       VTSS_IO_OFFSET1(0x00958000) /*!< Base offset for target SD6G_KR_7 */
#define VTSS_TO_SD6G_KR_8       VTSS_IO_OFFSET1(0x00960000) /*!< Base offset for target SD6G_KR_8 */
#define VTSS_TO_SD6G_KR_9       VTSS_IO_OFFSET1(0x00968000) /*!< Base offset for target SD6G_KR_9 */
#define VTSS_TO_SD6G_KR_10      VTSS_IO_OFFSET1(0x00970000) /*!< Base offset for target SD6G_KR_10 */
#define VTSS_TO_SD6G_KR_11      VTSS_IO_OFFSET1(0x00978000) /*!< Base offset for target SD6G_KR_11 */
#define VTSS_TO_SD6G_KR_12      VTSS_IO_OFFSET1(0x00980000) /*!< Base offset for target SD6G_KR_12 */
#define VTSS_TO_SD10G_KR_0      VTSS_IO_OFFSET1(0x00988000) /*!< Base offset for target SD10G_KR_0 */
#define VTSS_TO_SD10G_KR_1      VTSS_IO_OFFSET1(0x00990000) /*!< Base offset for target SD10G_KR_1 */
#define VTSS_TO_SD10G_KR_2      VTSS_IO_OFFSET1(0x00998000) /*!< Base offset for target SD10G_KR_2 */
#define VTSS_TO_SD10G_KR_3      VTSS_IO_OFFSET1(0x009a0000) /*!< Base offset for target SD10G_KR_3 */
#define VTSS_TO_SD_LANE_0       VTSS_IO_OFFSET1(0x009a8000) /*!< Base offset for target SD_LANE_0 */
#define VTSS_TO_SD_LANE_1       VTSS_IO_OFFSET1(0x009b0000) /*!< Base offset for target SD_LANE_1 */
#define VTSS_TO_SD_LANE_2       VTSS_IO_OFFSET1(0x009b8000) /*!< Base offset for target SD_LANE_2 */
#define VTSS_TO_SD_LANE_3       VTSS_IO_OFFSET1(0x009c0000) /*!< Base offset for target SD_LANE_3 */
#define VTSS_TO_SD_LANE_4       VTSS_IO_OFFSET1(0x009c8000) /*!< Base offset for target SD_LANE_4 */
#define VTSS_TO_SD_LANE_5       VTSS_IO_OFFSET1(0x009d0000) /*!< Base offset for target SD_LANE_5 */
#define VTSS_TO_SD_LANE_6       VTSS_IO_OFFSET1(0x009d8000) /*!< Base offset for target SD_LANE_6 */
#define VTSS_TO_SD_LANE_7       VTSS_IO_OFFSET1(0x009e0000) /*!< Base offset for target SD_LANE_7 */
#define VTSS_TO_SD_LANE_8       VTSS_IO_OFFSET1(0x009e8000) /*!< Base offset for target SD_LANE_8 */
#define VTSS_TO_SD_LANE_9       VTSS_IO_OFFSET1(0x009f0000) /*!< Base offset for target SD_LANE_9 */
#define VTSS_TO_SD_LANE_10      VTSS_IO_OFFSET1(0x009f8000) /*!< Base offset for target SD_LANE_10 */
#define VTSS_TO_SD_LANE_11      VTSS_IO_OFFSET1(0x00a00000) /*!< Base offset for target SD_LANE_11 */
#define VTSS_TO_SD_LANE_12      VTSS_IO_OFFSET1(0x00a08000) /*!< Base offset for target SD_LANE_12 */
#define VTSS_TO_SD_LANE_13      VTSS_IO_OFFSET1(0x00a10000) /*!< Base offset for target SD_LANE_13 */
#define VTSS_TO_SD_LANE_14      VTSS_IO_OFFSET1(0x00a18000) /*!< Base offset for target SD_LANE_14 */
#define VTSS_TO_SD_LANE_15      VTSS_IO_OFFSET1(0x00a20000) /*!< Base offset for target SD_LANE_15 */
#define VTSS_TO_SD_LANE_16      VTSS_IO_OFFSET1(0x00a28000) /*!< Base offset for target SD_LANE_16 */
#define VTSS_TO_SD10G_LANE_4    VTSS_IO_OFFSET1(0x00c58000) /*!< Base offset for target SD10G_LANE_4 */
#define VTSS_TO_SD10G_LANE_5    VTSS_IO_OFFSET1(0x00c60000) /*!< Base offset for target SD10G_LANE_5 */
#define VTSS_TO_SD10G_LANE_6    VTSS_IO_OFFSET1(0x00c68000) /*!< Base offset for target SD10G_LANE_6 */
#define VTSS_TO_SD10G_LANE_7    VTSS_IO_OFFSET1(0x00c70000) /*!< Base offset for target SD10G_LANE_7 */
#define VTSS_TO_SD10G_LANE_8    VTSS_IO_OFFSET1(0x00c78000) /*!< Base offset for target SD10G_LANE_8 */
#define VTSS_TO_SD10G_LANE_9    VTSS_IO_OFFSET1(0x00c80000) /*!< Base offset for target SD10G_LANE_9 */
#define VTSS_TO_SD10G_LANE_10   VTSS_IO_OFFSET1(0x00c88000) /*!< Base offset for target SD10G_LANE_10 */
#define VTSS_TO_SD10G_LANE_11   VTSS_IO_OFFSET1(0x00c90000) /*!< Base offset for target SD10G_LANE_11 */
#define VTSS_TO_SD10G_KR_4      VTSS_IO_OFFSET1(0x00cd8000) /*!< Base offset for target SD10G_KR_4 */
#define VTSS_TO_SD10G_KR_5      VTSS_IO_OFFSET1(0x00ce0000) /*!< Base offset for target SD10G_KR_5 */
#define VTSS_TO_SD10G_KR_6      VTSS_IO_OFFSET1(0x00ce8000) /*!< Base offset for target SD10G_KR_6 */
#define VTSS_TO_SD10G_KR_7      VTSS_IO_OFFSET1(0x00cf0000) /*!< Base offset for target SD10G_KR_7 */
#define VTSS_TO_SD10G_KR_8      VTSS_IO_OFFSET1(0x00cf8000) /*!< Base offset for target SD10G_KR_8 */
#define VTSS_TO_SD10G_KR_9      VTSS_IO_OFFSET1(0x00d00000) /*!< Base offset for target SD10G_KR_9 */
#define VTSS_TO_SD10G_KR_10     VTSS_IO_OFFSET1(0x00d08000) /*!< Base offset for target SD10G_KR_10 */
#define VTSS_TO_SD10G_KR_11     VTSS_IO_OFFSET1(0x00d10000) /*!< Base offset for target SD10G_KR_11 */
#define VTSS_TO_SD_LANE_17      VTSS_IO_OFFSET1(0x00d58000) /*!< Base offset for target SD_LANE_17 */
#define VTSS_TO_SD_LANE_18      VTSS_IO_OFFSET1(0x00d60000) /*!< Base offset for target SD_LANE_18 */
#define VTSS_TO_SD_LANE_19      VTSS_IO_OFFSET1(0x00d68000) /*!< Base offset for target SD_LANE_19 */
#define VTSS_TO_SD_LANE_20      VTSS_IO_OFFSET1(0x00d70000) /*!< Base offset for target SD_LANE_20 */
#define VTSS_TO_SD_LANE_21      VTSS_IO_OFFSET1(0x00d78000) /*!< Base offset for target SD_LANE_21 */
#define VTSS_TO_SD_LANE_22      VTSS_IO_OFFSET1(0x00d80000) /*!< Base offset for target SD_LANE_22 */
#define VTSS_TO_SD_LANE_23      VTSS_IO_OFFSET1(0x00d88000) /*!< Base offset for target SD_LANE_23 */
#define VTSS_TO_SD_LANE_24      VTSS_IO_OFFSET1(0x00d90000) /*!< Base offset for target SD_LANE_24 */
#define VTSS_TO_SD25G_LANE_0    VTSS_IO_OFFSET1(0x00c98000) /*!< Base offset for target SD25G_LANE_0 */
#define VTSS_TO_SD25G_LANE_1    VTSS_IO_OFFSET1(0x00ca0000) /*!< Base offset for target SD25G_LANE_1 */
#define VTSS_TO_SD25G_LANE_2    VTSS_IO_OFFSET1(0x00ca8000) /*!< Base offset for target SD25G_LANE_2 */
#define VTSS_TO_SD25G_LANE_3    VTSS_IO_OFFSET1(0x00cb0000) /*!< Base offset for target SD25G_LANE_3 */
#define VTSS_TO_SD25G_LANE_4    VTSS_IO_OFFSET1(0x00cb8000) /*!< Base offset for target SD25G_LANE_4 */
#define VTSS_TO_SD25G_LANE_5    VTSS_IO_OFFSET1(0x00cc0000) /*!< Base offset for target SD25G_LANE_5 */
#define VTSS_TO_SD25G_LANE_6    VTSS_IO_OFFSET1(0x00cc8000) /*!< Base offset for target SD25G_LANE_6 */
#define VTSS_TO_SD25G_LANE_7    VTSS_IO_OFFSET1(0x00cd0000) /*!< Base offset for target SD25G_LANE_7 */
#define VTSS_TO_SD10G_KR_12     VTSS_IO_OFFSET1(0x00d18000) /*!< Base offset for target SD10G_KR_12 */
#define VTSS_TO_SD10G_KR_13     VTSS_IO_OFFSET1(0x00d20000) /*!< Base offset for target SD10G_KR_13 */
#define VTSS_TO_SD10G_KR_14     VTSS_IO_OFFSET1(0x00d28000) /*!< Base offset for target SD10G_KR_14 */
#define VTSS_TO_SD10G_KR_15     VTSS_IO_OFFSET1(0x00d30000) /*!< Base offset for target SD10G_KR_15 */
#define VTSS_TO_SD10G_KR_16     VTSS_IO_OFFSET1(0x00d38000) /*!< Base offset for target SD10G_KR_16 */
#define VTSS_TO_SD10G_KR_17     VTSS_IO_OFFSET1(0x00d40000) /*!< Base offset for target SD10G_KR_17 */
#define VTSS_TO_SD10G_KR_18     VTSS_IO_OFFSET1(0x00d48000) /*!< Base offset for target SD10G_KR_18 */
#define VTSS_TO_SD10G_KR_19     VTSS_IO_OFFSET1(0x00d50000) /*!< Base offset for target SD10G_KR_19 */
#define VTSS_TO_SD_LANE_25      VTSS_IO_OFFSET1(0x00d98000) /*!< Base offset for target SD_LANE_25 */
#define VTSS_TO_SD_LANE_26      VTSS_IO_OFFSET1(0x00da0000) /*!< Base offset for target SD_LANE_26 */
#define VTSS_TO_SD_LANE_27      VTSS_IO_OFFSET1(0x00da8000) /*!< Base offset for target SD_LANE_27 */
#define VTSS_TO_SD_LANE_28      VTSS_IO_OFFSET1(0x00db0000) /*!< Base offset for target SD_LANE_28 */
#define VTSS_TO_SD_LANE_29      VTSS_IO_OFFSET1(0x00db8000) /*!< Base offset for target SD_LANE_29 */
#define VTSS_TO_SD_LANE_30      VTSS_IO_OFFSET1(0x00dc0000) /*!< Base offset for target SD_LANE_30 */
#define VTSS_TO_SD_LANE_31      VTSS_IO_OFFSET1(0x00dc8000) /*!< Base offset for target SD_LANE_31 */
#define VTSS_TO_SD_LANE_32      VTSS_IO_OFFSET1(0x00dd0000) /*!< Base offset for target SD_LANE_32 */
#define VTSS_TO_SDPCIE_PMA      VTSS_IO_OFFSET1(0x00de0000) /*!< Base offset for target SDPCIE_PMA */
#define VTSS_TO_VCAP_ES0        VTSS_IO_OFFSET1(0x010e0000) /*!< Base offset for target VCAP_ES0 */
#define VTSS_TO_VCAP_ES2        VTSS_IO_OFFSET1(0x010d0000) /*!< Base offset for target VCAP_ES2 */
#define VTSS_TO_VCAP_IP6PFX     VTSS_IO_OFFSET1(0x01090000) /*!< Base offset for target VCAP_IP6PFX */
#define VTSS_TO_VCAP_SUPER      VTSS_IO_OFFSET1(0x01080000) /*!< Base offset for target VCAP_SUPER */
#define VTSS_TO_VOP             VTSS_IO_OFFSET1(0x01a00000) /*!< Base offset for target VOP */
#define VTSS_TO_VOP_L3          VTSS_IO_OFFSET1(0x01b00000) /*!< Base offset for target VOP_L3 */
#define VTSS_TO_VOP_MPLS        VTSS_IO_OFFSET1(0x01680000) /*!< Base offset for target VOP_MPLS */
#define VTSS_TO_XQS             VTSS_IO_OFFSET1(0x010c0000) /*!< Base offset for target XQS */

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
#define VTSS_IOREG(t,o)      (*((volatile u32*)(VTSS_IOADDR(t,o))))
#endif

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

#ifdef VTSS_FA_WANT_TARGET_ENUMS
/*
 * This section is primarily for documentation purposes.
 */

/**
  * \brief Target IP_KRANEG_NOTR target offset(s)
  */
enum vtss_target_IP_KRANEG_NOTR_e {
    VTSS_TOE_SD6G_KR_0       = VTSS_TO_SD6G_KR_0,
    VTSS_TOE_SD6G_KR_1       = VTSS_TO_SD6G_KR_1,
    VTSS_TOE_SD6G_KR_2       = VTSS_TO_SD6G_KR_2,
    VTSS_TOE_SD6G_KR_3       = VTSS_TO_SD6G_KR_3,
    VTSS_TOE_SD6G_KR_4       = VTSS_TO_SD6G_KR_4,
    VTSS_TOE_SD6G_KR_5       = VTSS_TO_SD6G_KR_5,
    VTSS_TOE_SD6G_KR_6       = VTSS_TO_SD6G_KR_6,
    VTSS_TOE_SD6G_KR_7       = VTSS_TO_SD6G_KR_7,
    VTSS_TOE_SD6G_KR_8       = VTSS_TO_SD6G_KR_8,
    VTSS_TOE_SD6G_KR_9       = VTSS_TO_SD6G_KR_9,
    VTSS_TOE_SD6G_KR_10      = VTSS_TO_SD6G_KR_10,
    VTSS_TOE_SD6G_KR_11      = VTSS_TO_SD6G_KR_11,
    VTSS_TOE_SD6G_KR_12      = VTSS_TO_SD6G_KR_12,
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
    VTSS_TOE_SD_CMU_6        = VTSS_TO_SD_CMU_6,
    VTSS_TOE_SD_CMU_7        = VTSS_TO_SD_CMU_7,
    VTSS_TOE_SD_CMU_8        = VTSS_TO_SD_CMU_8,
    VTSS_TOE_SD_CMU_9        = VTSS_TO_SD_CMU_9,
    VTSS_TOE_SD_CMU_10       = VTSS_TO_SD_CMU_10,
    VTSS_TOE_SD_CMU_11       = VTSS_TO_SD_CMU_11,
    VTSS_TOE_SD_CMU_12       = VTSS_TO_SD_CMU_12,
    VTSS_TOE_SD_CMU_13       = VTSS_TO_SD_CMU_13,
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
    VTSS_TOE_SD10G_KR_10     = VTSS_TO_SD10G_KR_10,
    VTSS_TOE_SD10G_KR_11     = VTSS_TO_SD10G_KR_11,
    VTSS_TOE_SD10G_KR_12     = VTSS_TO_SD10G_KR_12,
    VTSS_TOE_SD10G_KR_13     = VTSS_TO_SD10G_KR_13,
    VTSS_TOE_SD10G_KR_14     = VTSS_TO_SD10G_KR_14,
    VTSS_TOE_SD10G_KR_15     = VTSS_TO_SD10G_KR_15,
    VTSS_TOE_SD10G_KR_16     = VTSS_TO_SD10G_KR_16,
    VTSS_TOE_SD10G_KR_17     = VTSS_TO_SD10G_KR_17,
    VTSS_TOE_SD10G_KR_18     = VTSS_TO_SD10G_KR_18,
    VTSS_TOE_SD10G_KR_19     = VTSS_TO_SD10G_KR_19,
};

/**
  * \brief Target PCS_10GBASE_R target offset(s)
  */
enum vtss_target_PCS_10GBASE_R_e {
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
    VTSS_TOE_PCS10G_BR_10    = VTSS_TO_PCS10G_BR_10,
    VTSS_TOE_PCS10G_BR_11    = VTSS_TO_PCS10G_BR_11,
    VTSS_TOE_PCS25G_BR_0     = VTSS_TO_PCS25G_BR_0,
    VTSS_TOE_PCS25G_BR_1     = VTSS_TO_PCS25G_BR_1,
    VTSS_TOE_PCS25G_BR_2     = VTSS_TO_PCS25G_BR_2,
    VTSS_TOE_PCS25G_BR_3     = VTSS_TO_PCS25G_BR_3,
    VTSS_TOE_PCS25G_BR_4     = VTSS_TO_PCS25G_BR_4,
    VTSS_TOE_PCS25G_BR_5     = VTSS_TO_PCS25G_BR_5,
    VTSS_TOE_PCS25G_BR_6     = VTSS_TO_PCS25G_BR_6,
    VTSS_TOE_PCS25G_BR_7     = VTSS_TO_PCS25G_BR_7,
    VTSS_TOE_PCS5G_BR_0      = VTSS_TO_PCS5G_BR_0,
    VTSS_TOE_PCS5G_BR_1      = VTSS_TO_PCS5G_BR_1,
    VTSS_TOE_PCS5G_BR_2      = VTSS_TO_PCS5G_BR_2,
    VTSS_TOE_PCS5G_BR_3      = VTSS_TO_PCS5G_BR_3,
    VTSS_TOE_PCS5G_BR_4      = VTSS_TO_PCS5G_BR_4,
    VTSS_TOE_PCS5G_BR_5      = VTSS_TO_PCS5G_BR_5,
    VTSS_TOE_PCS5G_BR_6      = VTSS_TO_PCS5G_BR_6,
    VTSS_TOE_PCS5G_BR_7      = VTSS_TO_PCS5G_BR_7,
    VTSS_TOE_PCS5G_BR_8      = VTSS_TO_PCS5G_BR_8,
    VTSS_TOE_PCS5G_BR_9      = VTSS_TO_PCS5G_BR_9,
    VTSS_TOE_PCS5G_BR_10     = VTSS_TO_PCS5G_BR_10,
    VTSS_TOE_PCS5G_BR_11     = VTSS_TO_PCS5G_BR_11,
    VTSS_TOE_PCS5G_BR_64     = VTSS_TO_PCS5G_BR_64,
};

/**
  * \brief Target SD_CMU_NONTERM_TARGET target offset(s)
  */
enum vtss_target_SD_CMU_NONTERM_TARGET_e {
    VTSS_TOE_SD_CMU_CFG_0    = VTSS_TO_SD_CMU_CFG_0,
    VTSS_TOE_SD_CMU_CFG_1    = VTSS_TO_SD_CMU_CFG_1,
    VTSS_TOE_SD_CMU_CFG_2    = VTSS_TO_SD_CMU_CFG_2,
    VTSS_TOE_SD_CMU_CFG_3    = VTSS_TO_SD_CMU_CFG_3,
    VTSS_TOE_SD_CMU_CFG_4    = VTSS_TO_SD_CMU_CFG_4,
    VTSS_TOE_SD_CMU_CFG_5    = VTSS_TO_SD_CMU_CFG_5,
    VTSS_TOE_SD_CMU_CFG_6    = VTSS_TO_SD_CMU_CFG_6,
    VTSS_TOE_SD_CMU_CFG_7    = VTSS_TO_SD_CMU_CFG_7,
    VTSS_TOE_SD_CMU_CFG_10   = VTSS_TO_SD_CMU_CFG_10,
    VTSS_TOE_SD_CMU_CFG_11   = VTSS_TO_SD_CMU_CFG_11,
    VTSS_TOE_SD_CMU_CFG_12   = VTSS_TO_SD_CMU_CFG_12,
    VTSS_TOE_SD_CMU_CFG_13   = VTSS_TO_SD_CMU_CFG_13,
};

/**
  * \brief Target SD_CMU_TERM_TARGET target offset(s)
  */
enum vtss_target_SD_CMU_TERM_TARGET_e {
    VTSS_TOE_SD_CMU_CFG_8    = VTSS_TO_SD_CMU_CFG_8,
    VTSS_TOE_SD_CMU_CFG_9    = VTSS_TO_SD_CMU_CFG_9,
};

/**
  * \brief Target SD25G_TARGET target offset(s)
  */
enum vtss_target_SD25G_TARGET_e {
    VTSS_TOE_SD25G_LANE_0    = VTSS_TO_SD25G_LANE_0,
    VTSS_TOE_SD25G_LANE_1    = VTSS_TO_SD25G_LANE_1,
    VTSS_TOE_SD25G_LANE_2    = VTSS_TO_SD25G_LANE_2,
    VTSS_TOE_SD25G_LANE_3    = VTSS_TO_SD25G_LANE_3,
    VTSS_TOE_SD25G_LANE_4    = VTSS_TO_SD25G_LANE_4,
    VTSS_TOE_SD25G_LANE_5    = VTSS_TO_SD25G_LANE_5,
    VTSS_TOE_SD25G_LANE_6    = VTSS_TO_SD25G_LANE_6,
    VTSS_TOE_SD25G_LANE_7    = VTSS_TO_SD25G_LANE_7,
};

/**
  * \brief Target DEV10G target offset(s)
  */
enum vtss_target_DEV10G_e {
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
    VTSS_TOE_DEV10G_10       = VTSS_TO_DEV10G_10,
    VTSS_TOE_DEV10G_11       = VTSS_TO_DEV10G_11,
    VTSS_TOE_DEV25G_0        = VTSS_TO_DEV25G_0,
    VTSS_TOE_DEV25G_1        = VTSS_TO_DEV25G_1,
    VTSS_TOE_DEV25G_2        = VTSS_TO_DEV25G_2,
    VTSS_TOE_DEV25G_3        = VTSS_TO_DEV25G_3,
    VTSS_TOE_DEV25G_4        = VTSS_TO_DEV25G_4,
    VTSS_TOE_DEV25G_5        = VTSS_TO_DEV25G_5,
    VTSS_TOE_DEV25G_6        = VTSS_TO_DEV25G_6,
    VTSS_TOE_DEV25G_7        = VTSS_TO_DEV25G_7,
    VTSS_TOE_DEV5G_0         = VTSS_TO_DEV5G_0,
    VTSS_TOE_DEV5G_1         = VTSS_TO_DEV5G_1,
    VTSS_TOE_DEV5G_2         = VTSS_TO_DEV5G_2,
    VTSS_TOE_DEV5G_3         = VTSS_TO_DEV5G_3,
    VTSS_TOE_DEV5G_4         = VTSS_TO_DEV5G_4,
    VTSS_TOE_DEV5G_5         = VTSS_TO_DEV5G_5,
    VTSS_TOE_DEV5G_6         = VTSS_TO_DEV5G_6,
    VTSS_TOE_DEV5G_7         = VTSS_TO_DEV5G_7,
    VTSS_TOE_DEV5G_8         = VTSS_TO_DEV5G_8,
    VTSS_TOE_DEV5G_9         = VTSS_TO_DEV5G_9,
    VTSS_TOE_DEV5G_10        = VTSS_TO_DEV5G_10,
    VTSS_TOE_DEV5G_11        = VTSS_TO_DEV5G_11,
    VTSS_TOE_DEV5G_64        = VTSS_TO_DEV5G_64,
};

/**
  * \brief Target SD10G_LANE_TARGET target offset(s)
  */
enum vtss_target_SD10G_LANE_TARGET_e {
    VTSS_TOE_SD6G_LANE_0     = VTSS_TO_SD6G_LANE_0,
    VTSS_TOE_SD6G_LANE_1     = VTSS_TO_SD6G_LANE_1,
    VTSS_TOE_SD6G_LANE_2     = VTSS_TO_SD6G_LANE_2,
    VTSS_TOE_SD6G_LANE_3     = VTSS_TO_SD6G_LANE_3,
    VTSS_TOE_SD6G_LANE_4     = VTSS_TO_SD6G_LANE_4,
    VTSS_TOE_SD6G_LANE_5     = VTSS_TO_SD6G_LANE_5,
    VTSS_TOE_SD6G_LANE_6     = VTSS_TO_SD6G_LANE_6,
    VTSS_TOE_SD6G_LANE_7     = VTSS_TO_SD6G_LANE_7,
    VTSS_TOE_SD6G_LANE_8     = VTSS_TO_SD6G_LANE_8,
    VTSS_TOE_SD6G_LANE_9     = VTSS_TO_SD6G_LANE_9,
    VTSS_TOE_SD6G_LANE_10    = VTSS_TO_SD6G_LANE_10,
    VTSS_TOE_SD6G_LANE_11    = VTSS_TO_SD6G_LANE_11,
    VTSS_TOE_SD6G_LANE_12    = VTSS_TO_SD6G_LANE_12,
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
    VTSS_TOE_SD10G_LANE_10   = VTSS_TO_SD10G_LANE_10,
    VTSS_TOE_SD10G_LANE_11   = VTSS_TO_SD10G_LANE_11,
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
    VTSS_TOE_SD_LANE_10      = VTSS_TO_SD_LANE_10,
    VTSS_TOE_SD_LANE_11      = VTSS_TO_SD_LANE_11,
    VTSS_TOE_SD_LANE_12      = VTSS_TO_SD_LANE_12,
    VTSS_TOE_SD_LANE_13      = VTSS_TO_SD_LANE_13,
    VTSS_TOE_SD_LANE_14      = VTSS_TO_SD_LANE_14,
    VTSS_TOE_SD_LANE_15      = VTSS_TO_SD_LANE_15,
    VTSS_TOE_SD_LANE_16      = VTSS_TO_SD_LANE_16,
    VTSS_TOE_SD_LANE_17      = VTSS_TO_SD_LANE_17,
    VTSS_TOE_SD_LANE_18      = VTSS_TO_SD_LANE_18,
    VTSS_TOE_SD_LANE_19      = VTSS_TO_SD_LANE_19,
    VTSS_TOE_SD_LANE_20      = VTSS_TO_SD_LANE_20,
    VTSS_TOE_SD_LANE_21      = VTSS_TO_SD_LANE_21,
    VTSS_TOE_SD_LANE_22      = VTSS_TO_SD_LANE_22,
    VTSS_TOE_SD_LANE_23      = VTSS_TO_SD_LANE_23,
    VTSS_TOE_SD_LANE_24      = VTSS_TO_SD_LANE_24,
};

/**
  * \brief Target DEVCPU_ORG target offset(s)
  */
enum vtss_target_DEVCPU_ORG_e {
    VTSS_TOE_DEVCPU_ORG0     = VTSS_TO_DEVCPU_ORG0,
    VTSS_TOE_DEVCPU_ORG1     = VTSS_TO_DEVCPU_ORG1,
    VTSS_TOE_DEVCPU_ORG2     = VTSS_TO_DEVCPU_ORG2,
    VTSS_TOE_DEVCPU_ORG3     = VTSS_TO_DEVCPU_ORG3,
    VTSS_TOE_DEVCPU_ORG4     = VTSS_TO_DEVCPU_ORG4,
};

/**
  * \brief Target DEV1G target offset(s)
  */
enum vtss_target_DEV1G_e {
    VTSS_TOE_DEV2G5_0        = VTSS_TO_DEV2G5_0,
    VTSS_TOE_DEV2G5_1        = VTSS_TO_DEV2G5_1,
    VTSS_TOE_DEV2G5_2        = VTSS_TO_DEV2G5_2,
    VTSS_TOE_DEV2G5_3        = VTSS_TO_DEV2G5_3,
    VTSS_TOE_DEV2G5_4        = VTSS_TO_DEV2G5_4,
    VTSS_TOE_DEV2G5_5        = VTSS_TO_DEV2G5_5,
    VTSS_TOE_DEV2G5_6        = VTSS_TO_DEV2G5_6,
    VTSS_TOE_DEV2G5_7        = VTSS_TO_DEV2G5_7,
    VTSS_TOE_DEV2G5_8        = VTSS_TO_DEV2G5_8,
    VTSS_TOE_DEV2G5_9        = VTSS_TO_DEV2G5_9,
    VTSS_TOE_DEV2G5_10       = VTSS_TO_DEV2G5_10,
    VTSS_TOE_DEV2G5_11       = VTSS_TO_DEV2G5_11,
    VTSS_TOE_DEV2G5_12       = VTSS_TO_DEV2G5_12,
    VTSS_TOE_DEV2G5_13       = VTSS_TO_DEV2G5_13,
    VTSS_TOE_DEV2G5_14       = VTSS_TO_DEV2G5_14,
    VTSS_TOE_DEV2G5_15       = VTSS_TO_DEV2G5_15,
    VTSS_TOE_DEV2G5_16       = VTSS_TO_DEV2G5_16,
    VTSS_TOE_DEV2G5_17       = VTSS_TO_DEV2G5_17,
    VTSS_TOE_DEV2G5_18       = VTSS_TO_DEV2G5_18,
    VTSS_TOE_DEV2G5_19       = VTSS_TO_DEV2G5_19,
    VTSS_TOE_DEV2G5_20       = VTSS_TO_DEV2G5_20,
    VTSS_TOE_DEV2G5_21       = VTSS_TO_DEV2G5_21,
    VTSS_TOE_DEV2G5_22       = VTSS_TO_DEV2G5_22,
    VTSS_TOE_DEV2G5_23       = VTSS_TO_DEV2G5_23,
    VTSS_TOE_DEV2G5_24       = VTSS_TO_DEV2G5_24,
    VTSS_TOE_DEV2G5_25       = VTSS_TO_DEV2G5_25,
    VTSS_TOE_DEV2G5_26       = VTSS_TO_DEV2G5_26,
    VTSS_TOE_DEV2G5_27       = VTSS_TO_DEV2G5_27,
    VTSS_TOE_DEV2G5_28       = VTSS_TO_DEV2G5_28,
    VTSS_TOE_DEV2G5_29       = VTSS_TO_DEV2G5_29,
    VTSS_TOE_DEV2G5_30       = VTSS_TO_DEV2G5_30,
    VTSS_TOE_DEV2G5_31       = VTSS_TO_DEV2G5_31,
    VTSS_TOE_DEV2G5_32       = VTSS_TO_DEV2G5_32,
    VTSS_TOE_DEV2G5_33       = VTSS_TO_DEV2G5_33,
    VTSS_TOE_DEV2G5_34       = VTSS_TO_DEV2G5_34,
    VTSS_TOE_DEV2G5_35       = VTSS_TO_DEV2G5_35,
    VTSS_TOE_DEV2G5_36       = VTSS_TO_DEV2G5_36,
    VTSS_TOE_DEV2G5_37       = VTSS_TO_DEV2G5_37,
    VTSS_TOE_DEV2G5_38       = VTSS_TO_DEV2G5_38,
    VTSS_TOE_DEV2G5_39       = VTSS_TO_DEV2G5_39,
    VTSS_TOE_DEV2G5_40       = VTSS_TO_DEV2G5_40,
    VTSS_TOE_DEV2G5_41       = VTSS_TO_DEV2G5_41,
    VTSS_TOE_DEV2G5_42       = VTSS_TO_DEV2G5_42,
    VTSS_TOE_DEV2G5_43       = VTSS_TO_DEV2G5_43,
    VTSS_TOE_DEV2G5_44       = VTSS_TO_DEV2G5_44,
    VTSS_TOE_DEV2G5_45       = VTSS_TO_DEV2G5_45,
    VTSS_TOE_DEV2G5_46       = VTSS_TO_DEV2G5_46,
    VTSS_TOE_DEV2G5_47       = VTSS_TO_DEV2G5_47,
    VTSS_TOE_DEV2G5_48       = VTSS_TO_DEV2G5_48,
    VTSS_TOE_DEV2G5_49       = VTSS_TO_DEV2G5_49,
    VTSS_TOE_DEV2G5_50       = VTSS_TO_DEV2G5_50,
    VTSS_TOE_DEV2G5_51       = VTSS_TO_DEV2G5_51,
    VTSS_TOE_DEV2G5_52       = VTSS_TO_DEV2G5_52,
    VTSS_TOE_DEV2G5_53       = VTSS_TO_DEV2G5_53,
    VTSS_TOE_DEV2G5_54       = VTSS_TO_DEV2G5_54,
    VTSS_TOE_DEV2G5_55       = VTSS_TO_DEV2G5_55,
    VTSS_TOE_DEV2G5_56       = VTSS_TO_DEV2G5_56,
    VTSS_TOE_DEV2G5_57       = VTSS_TO_DEV2G5_57,
    VTSS_TOE_DEV2G5_58       = VTSS_TO_DEV2G5_58,
    VTSS_TOE_DEV2G5_59       = VTSS_TO_DEV2G5_59,
    VTSS_TOE_DEV2G5_60       = VTSS_TO_DEV2G5_60,
    VTSS_TOE_DEV2G5_61       = VTSS_TO_DEV2G5_61,
    VTSS_TOE_DEV2G5_62       = VTSS_TO_DEV2G5_62,
    VTSS_TOE_DEV2G5_63       = VTSS_TO_DEV2G5_63,
    VTSS_TOE_DEV2G5_64       = VTSS_TO_DEV2G5_64,
};

/**
  * \brief Target PCS25G_RSFEC target offset(s)
  */
enum vtss_target_PCS25G_RSFEC_e {
    VTSS_TOE_PCS25G_RSFEC_0  = VTSS_TO_PCS25G_RSFEC_0,
    VTSS_TOE_PCS25G_RSFEC_1  = VTSS_TO_PCS25G_RSFEC_1,
    VTSS_TOE_PCS25G_RSFEC_2  = VTSS_TO_PCS25G_RSFEC_2,
    VTSS_TOE_PCS25G_RSFEC_3  = VTSS_TO_PCS25G_RSFEC_3,
    VTSS_TOE_PCS25G_RSFEC_4  = VTSS_TO_PCS25G_RSFEC_4,
    VTSS_TOE_PCS25G_RSFEC_5  = VTSS_TO_PCS25G_RSFEC_5,
    VTSS_TOE_PCS25G_RSFEC_6  = VTSS_TO_PCS25G_RSFEC_6,
    VTSS_TOE_PCS25G_RSFEC_7  = VTSS_TO_PCS25G_RSFEC_7,
};

/**
  * \brief Target SD25G_CFG_TARGET target offset(s)
  */
enum vtss_target_SD25G_CFG_TARGET_e {
    VTSS_TOE_SD_LANE_25      = VTSS_TO_SD_LANE_25,
    VTSS_TOE_SD_LANE_26      = VTSS_TO_SD_LANE_26,
    VTSS_TOE_SD_LANE_27      = VTSS_TO_SD_LANE_27,
    VTSS_TOE_SD_LANE_28      = VTSS_TO_SD_LANE_28,
    VTSS_TOE_SD_LANE_29      = VTSS_TO_SD_LANE_29,
    VTSS_TOE_SD_LANE_30      = VTSS_TO_SD_LANE_30,
    VTSS_TOE_SD_LANE_31      = VTSS_TO_SD_LANE_31,
    VTSS_TOE_SD_LANE_32      = VTSS_TO_SD_LANE_32,
};

#endif /* VTSS_FA_WANT_TARGET_ENUMS */


#endif /* _VTSS_FA_REGS_COMMON_H_ */
