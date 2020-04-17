// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVALT_REGS_COMMON_H_
#define _VTSS_SERVALT_REGS_COMMON_H_


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


/*
 * Target offset base(s)
 */
#define VTSS_IO_ORIGIN1_OFFSET 0x70000000
#define VTSS_IO_ORIGIN1_SIZE   0x00200000
#define VTSS_IO_ORIGIN2_OFFSET 0x71000000
#define VTSS_IO_ORIGIN2_SIZE   0x01000000
#ifndef VTSS_IO_OFFSET1
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)
#endif
#ifndef VTSS_IO_OFFSET2
#define VTSS_IO_OFFSET2(offset) (VTSS_IO_ORIGIN2_OFFSET + offset)
#endif

/* Main target address offsets */
#define VTSS_TO_CFG        VTSS_IO_OFFSET1(0x00000000) /*!< Base offset for target CFG */
#define VTSS_TO_UART       VTSS_IO_OFFSET1(0x00100000) /*!< Base offset for target UART */
#define VTSS_TO_TWI        VTSS_IO_OFFSET1(0x00100400) /*!< Base offset for target TWI */
#define VTSS_TO_UART2      VTSS_IO_OFFSET1(0x00100800) /*!< Base offset for target UART2 */
#define VTSS_TO_TWI2       VTSS_IO_OFFSET1(0x00100c00) /*!< Base offset for target TWI2 */
#define VTSS_TO_SIMC       VTSS_IO_OFFSET1(0x00101000) /*!< Base offset for target SIMC */
#define VTSS_TO_SBA        VTSS_IO_OFFSET1(0x00110000) /*!< Base offset for target SBA */
#define VTSS_TO_PCIE_EP    VTSS_IO_OFFSET1(0x00111000) /*!< Base offset for target PCIE_EP */
#define VTSS_TO_DEVCPU_ORG VTSS_IO_OFFSET2(0x00000000) /*!< Base offset for target DEVCPU_ORG */
#define VTSS_TO_DEVCPU_GCB VTSS_IO_OFFSET2(0x00010000) /*!< Base offset for target DEVCPU_GCB */
#define VTSS_TO_DEVCPU_QS  VTSS_IO_OFFSET2(0x00020000) /*!< Base offset for target DEVCPU_QS */
#define VTSS_TO_DEV2G5_0   VTSS_IO_OFFSET2(0x00030000) /*!< Base offset for target DEV2G5_0 */
#define VTSS_TO_DEV2G5_1   VTSS_IO_OFFSET2(0x00040000) /*!< Base offset for target DEV2G5_1 */
#define VTSS_TO_DEV2G5_2   VTSS_IO_OFFSET2(0x00050000) /*!< Base offset for target DEV2G5_2 */
#define VTSS_TO_DEV2G5_3   VTSS_IO_OFFSET2(0x00060000) /*!< Base offset for target DEV2G5_3 */
#define VTSS_TO_DEV2G5_4   VTSS_IO_OFFSET2(0x00070000) /*!< Base offset for target DEV2G5_4 */
#define VTSS_TO_DEV2G5_5   VTSS_IO_OFFSET2(0x00080000) /*!< Base offset for target DEV2G5_5 */
#define VTSS_TO_DEV2G5_6   VTSS_IO_OFFSET2(0x00090000) /*!< Base offset for target DEV2G5_6 */
#define VTSS_TO_DEV2G5_7   VTSS_IO_OFFSET2(0x000a0000) /*!< Base offset for target DEV2G5_7 */
#define VTSS_TO_DEV2G5_8   VTSS_IO_OFFSET2(0x000b0000) /*!< Base offset for target DEV2G5_8 */
#define VTSS_TO_DEV2G5_9   VTSS_IO_OFFSET2(0x000c0000) /*!< Base offset for target DEV2G5_9 */
#define VTSS_TO_DEV2G5_10  VTSS_IO_OFFSET2(0x000d0000) /*!< Base offset for target DEV2G5_10 */
#define VTSS_TO_DEV10G_0   VTSS_IO_OFFSET2(0x000e0000) /*!< Base offset for target DEV10G_0 */
#define VTSS_TO_DEV10G_1   VTSS_IO_OFFSET2(0x000f0000) /*!< Base offset for target DEV10G_1 */
#define VTSS_TO_PCS10G_BR_0 VTSS_IO_OFFSET2(0x00100000) /*!< Base offset for target PCS10G_BR_0 */
#define VTSS_TO_PCS10G_BR_1 VTSS_IO_OFFSET2(0x00110000) /*!< Base offset for target PCS10G_BR_1 */
#define VTSS_TO_ASM        VTSS_IO_OFFSET2(0x00120000) /*!< Base offset for target ASM */
#define VTSS_TO_LRN        VTSS_IO_OFFSET2(0x00130000) /*!< Base offset for target LRN */
#define VTSS_TO_ANA_ACL    VTSS_IO_OFFSET2(0x00140000) /*!< Base offset for target ANA_ACL */
#define VTSS_TO_VCAP_SUPER VTSS_IO_OFFSET2(0x00150000) /*!< Base offset for target VCAP_SUPER */
#define VTSS_TO_DSM        VTSS_IO_OFFSET2(0x00160000) /*!< Base offset for target DSM */
#define VTSS_TO_HSIO       VTSS_IO_OFFSET2(0x00170000) /*!< Base offset for target HSIO */
#define VTSS_TO_VCAP_ES0   VTSS_IO_OFFSET2(0x00180000) /*!< Base offset for target VCAP_ES0 */
#define VTSS_TO_XGANA_0    VTSS_IO_OFFSET2(0x00190000) /*!< Base offset for target XGANA_0 */
#define VTSS_TO_XGANA_1    VTSS_IO_OFFSET2(0x001a0000) /*!< Base offset for target XGANA_1 */
#define VTSS_TO_XGANA_2    VTSS_IO_OFFSET2(0x001b0000) /*!< Base offset for target XGANA_2 */
#define VTSS_TO_XGANA_3    VTSS_IO_OFFSET2(0x001c0000) /*!< Base offset for target XGANA_3 */
#define VTSS_TO_XGDIG_0    VTSS_IO_OFFSET2(0x001d0000) /*!< Base offset for target XGDIG_0 */
#define VTSS_TO_XGDIG_1    VTSS_IO_OFFSET2(0x001e0000) /*!< Base offset for target XGDIG_1 */
#define VTSS_TO_XGDIG_2    VTSS_IO_OFFSET2(0x001f0000) /*!< Base offset for target XGDIG_2 */
#define VTSS_TO_XGDIG_3    VTSS_IO_OFFSET2(0x00200000) /*!< Base offset for target XGDIG_3 */
#define VTSS_TO_XGXFI_0    VTSS_IO_OFFSET2(0x00210000) /*!< Base offset for target XGXFI_0 */
#define VTSS_TO_XGXFI_1    VTSS_IO_OFFSET2(0x00220000) /*!< Base offset for target XGXFI_1 */
#define VTSS_TO_XGXFI_2    VTSS_IO_OFFSET2(0x00230000) /*!< Base offset for target XGXFI_2 */
#define VTSS_TO_XGXFI_3    VTSS_IO_OFFSET2(0x00240000) /*!< Base offset for target XGXFI_3 */
#define VTSS_TO_XGKR0_2    VTSS_IO_OFFSET2(0x00270000) /*!< Base offset for target XGKR0_2 */
#define VTSS_TO_XGKR0_3    VTSS_IO_OFFSET2(0x00280000) /*!< Base offset for target XGKR0_3 */
#define VTSS_TO_XGKR1_2    VTSS_IO_OFFSET2(0x002b0000) /*!< Base offset for target XGKR1_2 */
#define VTSS_TO_XGKR1_3    VTSS_IO_OFFSET2(0x002c0000) /*!< Base offset for target XGKR1_3 */
#define VTSS_TO_OMG        VTSS_IO_OFFSET2(0x002d0000) /*!< Base offset for target OMG */
#define VTSS_TO_QFWD       VTSS_IO_OFFSET2(0x007d0000) /*!< Base offset for target QFWD */
#define VTSS_TO_QSYS       VTSS_IO_OFFSET2(0x007e0000) /*!< Base offset for target QSYS */
#define VTSS_TO_DEVCPU_PTP VTSS_IO_OFFSET2(0x007f0000) /*!< Base offset for target DEVCPU_PTP */
#define VTSS_TO_ANA_L3     VTSS_IO_OFFSET2(0x00800000) /*!< Base offset for target ANA_L3 */
#define VTSS_TO_HSCH       VTSS_IO_OFFSET2(0x00880000) /*!< Base offset for target HSCH */
#define VTSS_TO_QRES       VTSS_IO_OFFSET2(0x00900000) /*!< Base offset for target QRES */
#define VTSS_TO_ANA_AC_POL VTSS_IO_OFFSET2(0x00980000) /*!< Base offset for target ANA_AC_POL */
#define VTSS_TO_VOP_MPLS   VTSS_IO_OFFSET2(0x00a00000) /*!< Base offset for target VOP_MPLS */
#define VTSS_TO_AFI        VTSS_IO_OFFSET2(0x00a80000) /*!< Base offset for target AFI */
#define VTSS_TO_REW        VTSS_IO_OFFSET2(0x00b00000) /*!< Base offset for target REW */
#define VTSS_TO_ANA_AC_OAM_MOD VTSS_IO_OFFSET2(0x00b80000) /*!< Base offset for target ANA_AC_OAM_MOD */
#define VTSS_TO_VOP        VTSS_IO_OFFSET2(0x00c00000) /*!< Base offset for target VOP */
#define VTSS_TO_ANA_CL     VTSS_IO_OFFSET2(0x00d00000) /*!< Base offset for target ANA_CL */
#define VTSS_TO_ANA_L2     VTSS_IO_OFFSET2(0x00e00000) /*!< Base offset for target ANA_L2 */
#define VTSS_TO_ANA_AC     VTSS_IO_OFFSET2(0x00f00000) /*!< Base offset for target ANA_AC */

/* IO address mapping macro - may be changed for platform */
#if !defined(VTSS_IOADDR)
#define VTSS_IOADDR(t,o)        ((t) + ((o) << 2))
#endif

/* IO register access macro - may be changed for platform */
#if !defined(VTSS_IOREG)
/** 
 * @param t - target base offset
 * @param o - subtarget offset
 */
#define VTSS_IOREG(t,o)      (*((volatile unsigned long*)(VTSS_IOADDR(t,o))))
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

#ifdef VTSS_SERVALT_WANT_TARGET_ENUMS
/*
 * This section is primarily for documentation purposes.
 */

/**
  * \brief Target KR_DEV1 target offset(s)
  */
enum vtss_target_KR_DEV1_e {
    VTSS_TOE_XGKR0_2         = VTSS_TO_XGKR0_2,
    VTSS_TOE_XGKR0_3         = VTSS_TO_XGKR0_3,
};

/**
  * \brief Target TWI target offset(s)
  */
enum vtss_target_TWI_e {
    VTSS_TOE_TWI             = VTSS_TO_TWI,
    VTSS_TOE_TWI2            = VTSS_TO_TWI2,
};

/**
  * \brief Target SD10G65 target offset(s)
  */
enum vtss_target_SD10G65_e {
    VTSS_TOE_XGANA_0         = VTSS_TO_XGANA_0,
    VTSS_TOE_XGANA_1         = VTSS_TO_XGANA_1,
    VTSS_TOE_XGANA_2         = VTSS_TO_XGANA_2,
    VTSS_TOE_XGANA_3         = VTSS_TO_XGANA_3,
};

/**
  * \brief Target UART target offset(s)
  */
enum vtss_target_UART_e {
    VTSS_TOE_UART            = VTSS_TO_UART,
    VTSS_TOE_UART2           = VTSS_TO_UART2,
};

/**
  * \brief Target XFI_SHELL target offset(s)
  */
enum vtss_target_XFI_SHELL_e {
    VTSS_TOE_XGXFI_0         = VTSS_TO_XGXFI_0,
    VTSS_TOE_XGXFI_1         = VTSS_TO_XGXFI_1,
    VTSS_TOE_XGXFI_2         = VTSS_TO_XGXFI_2,
    VTSS_TOE_XGXFI_3         = VTSS_TO_XGXFI_3,
};

/**
  * \brief Target KR_DEV7 target offset(s)
  */
enum vtss_target_KR_DEV7_e {
    VTSS_TOE_XGKR1_2         = VTSS_TO_XGKR1_2,
    VTSS_TOE_XGKR1_3         = VTSS_TO_XGKR1_3,
};

/**
  * \brief Target PCS_10GBASE_R target offset(s)
  */
enum vtss_target_PCS_10GBASE_R_e {
    VTSS_TOE_PCS10G_BR_0     = VTSS_TO_PCS10G_BR_0,
    VTSS_TOE_PCS10G_BR_1     = VTSS_TO_PCS10G_BR_1,
};

/**
  * \brief Target VCAP_CORE target offset(s)
  */
enum vtss_target_VCAP_CORE_e {
    VTSS_TOE_VCAP_ES0        = VTSS_TO_VCAP_ES0,
    VTSS_TOE_VCAP_SUPER      = VTSS_TO_VCAP_SUPER,
};

/**
  * \brief Target SD10G65_DIG target offset(s)
  */
enum vtss_target_SD10G65_DIG_e {
    VTSS_TOE_XGDIG_0         = VTSS_TO_XGDIG_0,
    VTSS_TOE_XGDIG_1         = VTSS_TO_XGDIG_1,
    VTSS_TOE_XGDIG_2         = VTSS_TO_XGDIG_2,
    VTSS_TOE_XGDIG_3         = VTSS_TO_XGDIG_3,
};

/**
  * \brief Target DEV10G target offset(s)
  */
enum vtss_target_DEV10G_e {
    VTSS_TOE_DEV10G_0        = VTSS_TO_DEV10G_0,
    VTSS_TOE_DEV10G_1        = VTSS_TO_DEV10G_1,
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
};

#endif /* VTSS_SERVALT_WANT_TARGET_ENUMS */


#endif /* _VTSS_SERVALT_REGS_COMMON_H_ */
