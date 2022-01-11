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

/* Main target address offsets */
#ifndef VTSS_IO_ORIGIN1_OFFSET
#define VTSS_IO_ORIGIN1_OFFSET 0x0e2000000 /*! default region*/
#endif
#ifndef VTSS_IO_ORIGIN1_SIZE
#define VTSS_IO_ORIGIN1_SIZE 0x010000000
#endif
#ifndef VTSS_IO_OFFSET1
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)
#endif
#ifndef VTSS_IO_ORIGIN2_OFFSET
#define VTSS_IO_ORIGIN2_OFFSET 0x0e0000000 /*! amba_axi_top region*/
#endif
#ifndef VTSS_IO_ORIGIN2_SIZE
#define VTSS_IO_ORIGIN2_SIZE 0x010000000
#endif
#ifndef VTSS_IO_OFFSET2
#define VTSS_IO_OFFSET2(offset) (VTSS_IO_ORIGIN2_OFFSET + offset)
#endif
#define VTSS_TO_CPU             VTSS_IO_OFFSET1(0x00130000) /*!< Base offset for target CPU */
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
#define VTSS_TO_SUNRISE_TOP     VTSS_IO_OFFSET1(0x01470000) /*!< Base offset for target SUNRISE_TOP */
#define VTSS_TO_DEV2G5_1        VTSS_IO_OFFSET1(0x01010000) /*!< Base offset for target DEV2G5_1 */
#define VTSS_TO_DEV2G5_2        VTSS_IO_OFFSET1(0x01014000) /*!< Base offset for target DEV2G5_2 */
#define VTSS_TO_DEV2G5_3        VTSS_IO_OFFSET1(0x01018000) /*!< Base offset for target DEV2G5_3 */
#define VTSS_TO_DEV2G5_0        VTSS_IO_OFFSET1(0x01004000) /*!< Base offset for target DEV2G5_0 */
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

#ifdef VTSS_LAGUNA_WANT_TARGET_ENUMS
/*
 * This section is primarily for documentation purposes.
 */

/**
  * \brief Target DEVCPU_ORG target offset(s)
  */
enum vtss_target_DEVCPU_ORG_e {
    VTSS_TOE_DEVCPU_ORG0     = VTSS_TO_DEVCPU_ORG0,
    VTSS_TOE_DEVCPU_ORG1     = VTSS_TO_DEVCPU_ORG1,
    VTSS_TOE_DEVCPU_ORG2     = VTSS_TO_DEVCPU_ORG2,
};

/**
  * \brief Target DEV1G target offset(s)
  */
enum vtss_target_DEV1G_e {
    VTSS_TOE_DEV2G5_1        = VTSS_TO_DEV2G5_1,
    VTSS_TOE_DEV2G5_2        = VTSS_TO_DEV2G5_2,
    VTSS_TOE_DEV2G5_3        = VTSS_TO_DEV2G5_3,
    VTSS_TOE_DEV2G5_0        = VTSS_TO_DEV2G5_0,
};

#endif /* VTSS_LAGUNA_WANT_TARGET_ENUMS */


#endif /* _VTSS_LAGUNA_REGS_COMMON_H_ */
