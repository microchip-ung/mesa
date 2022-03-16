// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_KERNEL_REGS_COMMON_H_
#define _VTSS_FA_KERNEL_REGS_COMMON_H_


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
#ifndef VTSS_IO_ORIGIN2_OFFSET
#define VTSS_IO_ORIGIN2_OFFSET 0x000000000 /*! amba_top region*/
#endif
#ifndef VTSS_IO_ORIGIN2_SIZE
#define VTSS_IO_ORIGIN2_SIZE 0x010000000
#endif
#ifndef VTSS_IO_OFFSET2
#define VTSS_IO_OFFSET2(offset) (VTSS_IO_ORIGIN2_OFFSET + offset)
#endif
#define VTSS_TO_CPU             VTSS_IO_OFFSET2(0x00000000) /*!< Base offset for target CPU */
#define VTSS_TO_UART            VTSS_IO_OFFSET2(0x00100000) /*!< Base offset for target UART */
#define VTSS_TO_UART2           VTSS_IO_OFFSET2(0x00102000) /*!< Base offset for target UART2 */
#define VTSS_TO_TWI             VTSS_IO_OFFSET2(0x00101000) /*!< Base offset for target TWI */
#define VTSS_TO_TWI2            VTSS_IO_OFFSET2(0x00103000) /*!< Base offset for target TWI2 */
#define VTSS_TO_TIMERS          VTSS_IO_OFFSET2(0x00105000) /*!< Base offset for target TIMERS */
#define VTSS_TO_WDT             VTSS_IO_OFFSET2(0x00106000) /*!< Base offset for target WDT */
#define VTSS_TO_SIMC            VTSS_IO_OFFSET2(0x00104000) /*!< Base offset for target SIMC */
#define VTSS_TO_TRNG            VTSS_IO_OFFSET2(0x0010c000) /*!< Base offset for target TRNG */
#define VTSS_TO_MSHC            VTSS_IO_OFFSET2(0x00800000) /*!< Base offset for target MSHC */
#define VTSS_TO_FDMA            VTSS_IO_OFFSET2(0x00080000) /*!< Base offset for target FDMA */
#define VTSS_TO_DDR_UMCTL2      VTSS_IO_OFFSET2(0x00107000) /*!< Base offset for target DDR_UMCTL2 */
#define VTSS_TO_DDR_PHY         VTSS_IO_OFFSET2(0x00108000) /*!< Base offset for target DDR_PHY */
#define VTSS_TO_PCIE_DM_EP      VTSS_IO_OFFSET2(0x00400000) /*!< Base offset for target PCIE_DM_EP */
#define VTSS_TO_PCIE_DM_RC      VTSS_IO_OFFSET2(0x00400000) /*!< Base offset for target PCIE_DM_RC */
#define VTSS_TO_SDPCIE_PHY      VTSS_IO_OFFSET2(0x0010b000) /*!< Base offset for target SDPCIE_PHY */

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
  * \brief Target I2C target offset(s)
  */
enum vtss_target_I2C_e {
    VTSS_TOE_TWI             = VTSS_TO_TWI,
    VTSS_TOE_TWI2            = VTSS_TO_TWI2,
};

/**
  * \brief Target UART target offset(s)
  */
enum vtss_target_UART_e {
    VTSS_TOE_UART            = VTSS_TO_UART,
    VTSS_TOE_UART2           = VTSS_TO_UART2,
};

#endif /* VTSS_FA_WANT_TARGET_ENUMS */


#endif /* _VTSS_FA_KERNEL_REGS_COMMON_H_ */
