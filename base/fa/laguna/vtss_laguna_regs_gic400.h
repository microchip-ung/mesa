// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_GIC400_H_
#define _VTSS_LAGUNA_REGS_GIC400_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a GIC400
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a GIC400:DISTRIBUTOR
 *
 * Memory map for the GIC Distributor block. Contains all registers with the GICD prefix. Note: Some registers are security-banked or banked per-CPU.
 */


/**
 * \brief Distributor Control Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CTLR
 */
#define VTSS_GIC400_GICD_CTLR                VTSS_IOREG(VTSS_TO_GIC400,0x400)

/**
 * \brief
 * Distributor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CTLR . GICD_CTLR
 */
#define  VTSS_F_GIC400_GICD_CTLR_GICD_CTLR(x)  (x)
#define  VTSS_M_GIC400_GICD_CTLR_GICD_CTLR     0xffffffff
#define  VTSS_X_GIC400_GICD_CTLR_GICD_CTLR(x)  (x)


/**
 * \brief Interrupt Controller Type Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_TYPER
 */
#define VTSS_GIC400_GICD_TYPER               VTSS_IOREG(VTSS_TO_GIC400,0x401)

/**
 * \brief
 * Interrupt Controller Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_TYPER . GICD_TYPER
 */
#define  VTSS_F_GIC400_GICD_TYPER_GICD_TYPER(x)  (x)
#define  VTSS_M_GIC400_GICD_TYPER_GICD_TYPER     0xffffffff
#define  VTSS_X_GIC400_GICD_TYPER_GICD_TYPER(x)  (x)


/**
 * \brief Distributor Implementer Identification Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IIDR
 */
#define VTSS_GIC400_GICD_IIDR                VTSS_IOREG(VTSS_TO_GIC400,0x402)

/**
 * \brief
 * Distributor Implementer Identification Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IIDR . GICD_IIDR
 */
#define  VTSS_F_GIC400_GICD_IIDR_GICD_IIDR(x)  (x)
#define  VTSS_M_GIC400_GICD_IIDR_GICD_IIDR     0xffffffff
#define  VTSS_X_GIC400_GICD_IIDR_GICD_IIDR(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR0
 */
#define VTSS_GIC400_GICD_IGROUPR0            VTSS_IOREG(VTSS_TO_GIC400,0x420)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR0 . GICD_IGROUPR0
 */
#define  VTSS_F_GIC400_GICD_IGROUPR0_GICD_IGROUPR0(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR0_GICD_IGROUPR0     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR0_GICD_IGROUPR0(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR1
 */
#define VTSS_GIC400_GICD_IGROUPR1            VTSS_IOREG(VTSS_TO_GIC400,0x421)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR1 . GICD_IGROUPR1
 */
#define  VTSS_F_GIC400_GICD_IGROUPR1_GICD_IGROUPR1(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR1_GICD_IGROUPR1     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR1_GICD_IGROUPR1(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR2
 */
#define VTSS_GIC400_GICD_IGROUPR2            VTSS_IOREG(VTSS_TO_GIC400,0x422)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR2 . GICD_IGROUPR2
 */
#define  VTSS_F_GIC400_GICD_IGROUPR2_GICD_IGROUPR2(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR2_GICD_IGROUPR2     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR2_GICD_IGROUPR2(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR3
 */
#define VTSS_GIC400_GICD_IGROUPR3            VTSS_IOREG(VTSS_TO_GIC400,0x423)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR3 . GICD_IGROUPR3
 */
#define  VTSS_F_GIC400_GICD_IGROUPR3_GICD_IGROUPR3(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR3_GICD_IGROUPR3     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR3_GICD_IGROUPR3(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR4
 */
#define VTSS_GIC400_GICD_IGROUPR4            VTSS_IOREG(VTSS_TO_GIC400,0x424)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR4 . GICD_IGROUPR4
 */
#define  VTSS_F_GIC400_GICD_IGROUPR4_GICD_IGROUPR4(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR4_GICD_IGROUPR4     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR4_GICD_IGROUPR4(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR5
 */
#define VTSS_GIC400_GICD_IGROUPR5            VTSS_IOREG(VTSS_TO_GIC400,0x425)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR5 . GICD_IGROUPR5
 */
#define  VTSS_F_GIC400_GICD_IGROUPR5_GICD_IGROUPR5(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR5_GICD_IGROUPR5     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR5_GICD_IGROUPR5(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR6
 */
#define VTSS_GIC400_GICD_IGROUPR6            VTSS_IOREG(VTSS_TO_GIC400,0x426)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR6 . GICD_IGROUPR6
 */
#define  VTSS_F_GIC400_GICD_IGROUPR6_GICD_IGROUPR6(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR6_GICD_IGROUPR6     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR6_GICD_IGROUPR6(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR7
 */
#define VTSS_GIC400_GICD_IGROUPR7            VTSS_IOREG(VTSS_TO_GIC400,0x427)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR7 . GICD_IGROUPR7
 */
#define  VTSS_F_GIC400_GICD_IGROUPR7_GICD_IGROUPR7(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR7_GICD_IGROUPR7     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR7_GICD_IGROUPR7(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR8
 */
#define VTSS_GIC400_GICD_IGROUPR8            VTSS_IOREG(VTSS_TO_GIC400,0x428)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR8 . GICD_IGROUPR8
 */
#define  VTSS_F_GIC400_GICD_IGROUPR8_GICD_IGROUPR8(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR8_GICD_IGROUPR8     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR8_GICD_IGROUPR8(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR9
 */
#define VTSS_GIC400_GICD_IGROUPR9            VTSS_IOREG(VTSS_TO_GIC400,0x429)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR9 . GICD_IGROUPR9
 */
#define  VTSS_F_GIC400_GICD_IGROUPR9_GICD_IGROUPR9(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR9_GICD_IGROUPR9     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR9_GICD_IGROUPR9(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR10
 */
#define VTSS_GIC400_GICD_IGROUPR10           VTSS_IOREG(VTSS_TO_GIC400,0x42a)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR10 . GICD_IGROUPR10
 */
#define  VTSS_F_GIC400_GICD_IGROUPR10_GICD_IGROUPR10(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR10_GICD_IGROUPR10     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR10_GICD_IGROUPR10(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR11
 */
#define VTSS_GIC400_GICD_IGROUPR11           VTSS_IOREG(VTSS_TO_GIC400,0x42b)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR11 . GICD_IGROUPR11
 */
#define  VTSS_F_GIC400_GICD_IGROUPR11_GICD_IGROUPR11(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR11_GICD_IGROUPR11     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR11_GICD_IGROUPR11(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR12
 */
#define VTSS_GIC400_GICD_IGROUPR12           VTSS_IOREG(VTSS_TO_GIC400,0x42c)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR12 . GICD_IGROUPR12
 */
#define  VTSS_F_GIC400_GICD_IGROUPR12_GICD_IGROUPR12(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR12_GICD_IGROUPR12     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR12_GICD_IGROUPR12(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR13
 */
#define VTSS_GIC400_GICD_IGROUPR13           VTSS_IOREG(VTSS_TO_GIC400,0x42d)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR13 . GICD_IGROUPR13
 */
#define  VTSS_F_GIC400_GICD_IGROUPR13_GICD_IGROUPR13(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR13_GICD_IGROUPR13     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR13_GICD_IGROUPR13(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR14
 */
#define VTSS_GIC400_GICD_IGROUPR14           VTSS_IOREG(VTSS_TO_GIC400,0x42e)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR14 . GICD_IGROUPR14
 */
#define  VTSS_F_GIC400_GICD_IGROUPR14_GICD_IGROUPR14(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR14_GICD_IGROUPR14     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR14_GICD_IGROUPR14(x)  (x)


/**
 * \brief Interrupt Group Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IGROUPR15
 */
#define VTSS_GIC400_GICD_IGROUPR15           VTSS_IOREG(VTSS_TO_GIC400,0x42f)

/**
 * \brief
 * Interrupt Group Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IGROUPR15 . GICD_IGROUPR15
 */
#define  VTSS_F_GIC400_GICD_IGROUPR15_GICD_IGROUPR15(x)  (x)
#define  VTSS_M_GIC400_GICD_IGROUPR15_GICD_IGROUPR15     0xffffffff
#define  VTSS_X_GIC400_GICD_IGROUPR15_GICD_IGROUPR15(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER0
 */
#define VTSS_GIC400_GICD_ISENABLER0          VTSS_IOREG(VTSS_TO_GIC400,0x440)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER0 . GICD_ISENABLER0
 */
#define  VTSS_F_GIC400_GICD_ISENABLER0_GICD_ISENABLER0(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER0_GICD_ISENABLER0     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER0_GICD_ISENABLER0(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER1
 */
#define VTSS_GIC400_GICD_ISENABLER1          VTSS_IOREG(VTSS_TO_GIC400,0x441)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER1 . GICD_ISENABLER1
 */
#define  VTSS_F_GIC400_GICD_ISENABLER1_GICD_ISENABLER1(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER1_GICD_ISENABLER1     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER1_GICD_ISENABLER1(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER2
 */
#define VTSS_GIC400_GICD_ISENABLER2          VTSS_IOREG(VTSS_TO_GIC400,0x442)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER2 . GICD_ISENABLER2
 */
#define  VTSS_F_GIC400_GICD_ISENABLER2_GICD_ISENABLER2(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER2_GICD_ISENABLER2     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER2_GICD_ISENABLER2(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER3
 */
#define VTSS_GIC400_GICD_ISENABLER3          VTSS_IOREG(VTSS_TO_GIC400,0x443)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER3 . GICD_ISENABLER3
 */
#define  VTSS_F_GIC400_GICD_ISENABLER3_GICD_ISENABLER3(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER3_GICD_ISENABLER3     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER3_GICD_ISENABLER3(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER4
 */
#define VTSS_GIC400_GICD_ISENABLER4          VTSS_IOREG(VTSS_TO_GIC400,0x444)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER4 . GICD_ISENABLER4
 */
#define  VTSS_F_GIC400_GICD_ISENABLER4_GICD_ISENABLER4(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER4_GICD_ISENABLER4     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER4_GICD_ISENABLER4(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER5
 */
#define VTSS_GIC400_GICD_ISENABLER5          VTSS_IOREG(VTSS_TO_GIC400,0x445)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER5 . GICD_ISENABLER5
 */
#define  VTSS_F_GIC400_GICD_ISENABLER5_GICD_ISENABLER5(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER5_GICD_ISENABLER5     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER5_GICD_ISENABLER5(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER6
 */
#define VTSS_GIC400_GICD_ISENABLER6          VTSS_IOREG(VTSS_TO_GIC400,0x446)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER6 . GICD_ISENABLER6
 */
#define  VTSS_F_GIC400_GICD_ISENABLER6_GICD_ISENABLER6(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER6_GICD_ISENABLER6     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER6_GICD_ISENABLER6(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER7
 */
#define VTSS_GIC400_GICD_ISENABLER7          VTSS_IOREG(VTSS_TO_GIC400,0x447)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER7 . GICD_ISENABLER7
 */
#define  VTSS_F_GIC400_GICD_ISENABLER7_GICD_ISENABLER7(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER7_GICD_ISENABLER7     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER7_GICD_ISENABLER7(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER8
 */
#define VTSS_GIC400_GICD_ISENABLER8          VTSS_IOREG(VTSS_TO_GIC400,0x448)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER8 . GICD_ISENABLER8
 */
#define  VTSS_F_GIC400_GICD_ISENABLER8_GICD_ISENABLER8(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER8_GICD_ISENABLER8     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER8_GICD_ISENABLER8(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER9
 */
#define VTSS_GIC400_GICD_ISENABLER9          VTSS_IOREG(VTSS_TO_GIC400,0x449)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER9 . GICD_ISENABLER9
 */
#define  VTSS_F_GIC400_GICD_ISENABLER9_GICD_ISENABLER9(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER9_GICD_ISENABLER9     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER9_GICD_ISENABLER9(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER10
 */
#define VTSS_GIC400_GICD_ISENABLER10         VTSS_IOREG(VTSS_TO_GIC400,0x44a)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER10 . GICD_ISENABLER10
 */
#define  VTSS_F_GIC400_GICD_ISENABLER10_GICD_ISENABLER10(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER10_GICD_ISENABLER10     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER10_GICD_ISENABLER10(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER11
 */
#define VTSS_GIC400_GICD_ISENABLER11         VTSS_IOREG(VTSS_TO_GIC400,0x44b)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER11 . GICD_ISENABLER11
 */
#define  VTSS_F_GIC400_GICD_ISENABLER11_GICD_ISENABLER11(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER11_GICD_ISENABLER11     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER11_GICD_ISENABLER11(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER12
 */
#define VTSS_GIC400_GICD_ISENABLER12         VTSS_IOREG(VTSS_TO_GIC400,0x44c)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER12 . GICD_ISENABLER12
 */
#define  VTSS_F_GIC400_GICD_ISENABLER12_GICD_ISENABLER12(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER12_GICD_ISENABLER12     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER12_GICD_ISENABLER12(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER13
 */
#define VTSS_GIC400_GICD_ISENABLER13         VTSS_IOREG(VTSS_TO_GIC400,0x44d)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER13 . GICD_ISENABLER13
 */
#define  VTSS_F_GIC400_GICD_ISENABLER13_GICD_ISENABLER13(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER13_GICD_ISENABLER13     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER13_GICD_ISENABLER13(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER14
 */
#define VTSS_GIC400_GICD_ISENABLER14         VTSS_IOREG(VTSS_TO_GIC400,0x44e)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER14 . GICD_ISENABLER14
 */
#define  VTSS_F_GIC400_GICD_ISENABLER14_GICD_ISENABLER14(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER14_GICD_ISENABLER14     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER14_GICD_ISENABLER14(x)  (x)


/**
 * \brief Interrupt Set-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISENABLER15
 */
#define VTSS_GIC400_GICD_ISENABLER15         VTSS_IOREG(VTSS_TO_GIC400,0x44f)

/**
 * \brief
 * Interrupt Set-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISENABLER15 . GICD_ISENABLER15
 */
#define  VTSS_F_GIC400_GICD_ISENABLER15_GICD_ISENABLER15(x)  (x)
#define  VTSS_M_GIC400_GICD_ISENABLER15_GICD_ISENABLER15     0xffffffff
#define  VTSS_X_GIC400_GICD_ISENABLER15_GICD_ISENABLER15(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER0
 */
#define VTSS_GIC400_GICD_ICENABLER0          VTSS_IOREG(VTSS_TO_GIC400,0x460)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER0 . GICD_ICENABLER0
 */
#define  VTSS_F_GIC400_GICD_ICENABLER0_GICD_ICENABLER0(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER0_GICD_ICENABLER0     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER0_GICD_ICENABLER0(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER1
 */
#define VTSS_GIC400_GICD_ICENABLER1          VTSS_IOREG(VTSS_TO_GIC400,0x461)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER1 . GICD_ICENABLER1
 */
#define  VTSS_F_GIC400_GICD_ICENABLER1_GICD_ICENABLER1(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER1_GICD_ICENABLER1     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER1_GICD_ICENABLER1(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER2
 */
#define VTSS_GIC400_GICD_ICENABLER2          VTSS_IOREG(VTSS_TO_GIC400,0x462)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER2 . GICD_ICENABLER2
 */
#define  VTSS_F_GIC400_GICD_ICENABLER2_GICD_ICENABLER2(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER2_GICD_ICENABLER2     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER2_GICD_ICENABLER2(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER3
 */
#define VTSS_GIC400_GICD_ICENABLER3          VTSS_IOREG(VTSS_TO_GIC400,0x463)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER3 . GICD_ICENABLER3
 */
#define  VTSS_F_GIC400_GICD_ICENABLER3_GICD_ICENABLER3(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER3_GICD_ICENABLER3     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER3_GICD_ICENABLER3(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER4
 */
#define VTSS_GIC400_GICD_ICENABLER4          VTSS_IOREG(VTSS_TO_GIC400,0x464)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER4 . GICD_ICENABLER4
 */
#define  VTSS_F_GIC400_GICD_ICENABLER4_GICD_ICENABLER4(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER4_GICD_ICENABLER4     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER4_GICD_ICENABLER4(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER5
 */
#define VTSS_GIC400_GICD_ICENABLER5          VTSS_IOREG(VTSS_TO_GIC400,0x465)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER5 . GICD_ICENABLER5
 */
#define  VTSS_F_GIC400_GICD_ICENABLER5_GICD_ICENABLER5(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER5_GICD_ICENABLER5     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER5_GICD_ICENABLER5(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER6
 */
#define VTSS_GIC400_GICD_ICENABLER6          VTSS_IOREG(VTSS_TO_GIC400,0x466)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER6 . GICD_ICENABLER6
 */
#define  VTSS_F_GIC400_GICD_ICENABLER6_GICD_ICENABLER6(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER6_GICD_ICENABLER6     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER6_GICD_ICENABLER6(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER7
 */
#define VTSS_GIC400_GICD_ICENABLER7          VTSS_IOREG(VTSS_TO_GIC400,0x467)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER7 . GICD_ICENABLER7
 */
#define  VTSS_F_GIC400_GICD_ICENABLER7_GICD_ICENABLER7(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER7_GICD_ICENABLER7     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER7_GICD_ICENABLER7(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER8
 */
#define VTSS_GIC400_GICD_ICENABLER8          VTSS_IOREG(VTSS_TO_GIC400,0x468)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER8 . GICD_ICENABLER8
 */
#define  VTSS_F_GIC400_GICD_ICENABLER8_GICD_ICENABLER8(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER8_GICD_ICENABLER8     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER8_GICD_ICENABLER8(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER9
 */
#define VTSS_GIC400_GICD_ICENABLER9          VTSS_IOREG(VTSS_TO_GIC400,0x469)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER9 . GICD_ICENABLER9
 */
#define  VTSS_F_GIC400_GICD_ICENABLER9_GICD_ICENABLER9(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER9_GICD_ICENABLER9     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER9_GICD_ICENABLER9(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER10
 */
#define VTSS_GIC400_GICD_ICENABLER10         VTSS_IOREG(VTSS_TO_GIC400,0x46a)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER10 . GICD_ICENABLER10
 */
#define  VTSS_F_GIC400_GICD_ICENABLER10_GICD_ICENABLER10(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER10_GICD_ICENABLER10     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER10_GICD_ICENABLER10(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER11
 */
#define VTSS_GIC400_GICD_ICENABLER11         VTSS_IOREG(VTSS_TO_GIC400,0x46b)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER11 . GICD_ICENABLER11
 */
#define  VTSS_F_GIC400_GICD_ICENABLER11_GICD_ICENABLER11(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER11_GICD_ICENABLER11     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER11_GICD_ICENABLER11(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER12
 */
#define VTSS_GIC400_GICD_ICENABLER12         VTSS_IOREG(VTSS_TO_GIC400,0x46c)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER12 . GICD_ICENABLER12
 */
#define  VTSS_F_GIC400_GICD_ICENABLER12_GICD_ICENABLER12(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER12_GICD_ICENABLER12     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER12_GICD_ICENABLER12(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER13
 */
#define VTSS_GIC400_GICD_ICENABLER13         VTSS_IOREG(VTSS_TO_GIC400,0x46d)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER13 . GICD_ICENABLER13
 */
#define  VTSS_F_GIC400_GICD_ICENABLER13_GICD_ICENABLER13(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER13_GICD_ICENABLER13     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER13_GICD_ICENABLER13(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER14
 */
#define VTSS_GIC400_GICD_ICENABLER14         VTSS_IOREG(VTSS_TO_GIC400,0x46e)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER14 . GICD_ICENABLER14
 */
#define  VTSS_F_GIC400_GICD_ICENABLER14_GICD_ICENABLER14(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER14_GICD_ICENABLER14     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER14_GICD_ICENABLER14(x)  (x)


/**
 * \brief Interrupt Clear-Enable Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICENABLER15
 */
#define VTSS_GIC400_GICD_ICENABLER15         VTSS_IOREG(VTSS_TO_GIC400,0x46f)

/**
 * \brief
 * Interrupt Clear-Enable Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICENABLER15 . GICD_ICENABLER15
 */
#define  VTSS_F_GIC400_GICD_ICENABLER15_GICD_ICENABLER15(x)  (x)
#define  VTSS_M_GIC400_GICD_ICENABLER15_GICD_ICENABLER15     0xffffffff
#define  VTSS_X_GIC400_GICD_ICENABLER15_GICD_ICENABLER15(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR0
 */
#define VTSS_GIC400_GICD_ISPENDR0            VTSS_IOREG(VTSS_TO_GIC400,0x480)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR0 . GICD_ISPENDR0
 */
#define  VTSS_F_GIC400_GICD_ISPENDR0_GICD_ISPENDR0(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR0_GICD_ISPENDR0     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR0_GICD_ISPENDR0(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR1
 */
#define VTSS_GIC400_GICD_ISPENDR1            VTSS_IOREG(VTSS_TO_GIC400,0x481)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR1 . GICD_ISPENDR1
 */
#define  VTSS_F_GIC400_GICD_ISPENDR1_GICD_ISPENDR1(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR1_GICD_ISPENDR1     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR1_GICD_ISPENDR1(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR2
 */
#define VTSS_GIC400_GICD_ISPENDR2            VTSS_IOREG(VTSS_TO_GIC400,0x482)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR2 . GICD_ISPENDR2
 */
#define  VTSS_F_GIC400_GICD_ISPENDR2_GICD_ISPENDR2(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR2_GICD_ISPENDR2     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR2_GICD_ISPENDR2(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR3
 */
#define VTSS_GIC400_GICD_ISPENDR3            VTSS_IOREG(VTSS_TO_GIC400,0x483)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR3 . GICD_ISPENDR3
 */
#define  VTSS_F_GIC400_GICD_ISPENDR3_GICD_ISPENDR3(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR3_GICD_ISPENDR3     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR3_GICD_ISPENDR3(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR4
 */
#define VTSS_GIC400_GICD_ISPENDR4            VTSS_IOREG(VTSS_TO_GIC400,0x484)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR4 . GICD_ISPENDR4
 */
#define  VTSS_F_GIC400_GICD_ISPENDR4_GICD_ISPENDR4(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR4_GICD_ISPENDR4     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR4_GICD_ISPENDR4(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR5
 */
#define VTSS_GIC400_GICD_ISPENDR5            VTSS_IOREG(VTSS_TO_GIC400,0x485)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR5 . GICD_ISPENDR5
 */
#define  VTSS_F_GIC400_GICD_ISPENDR5_GICD_ISPENDR5(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR5_GICD_ISPENDR5     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR5_GICD_ISPENDR5(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR6
 */
#define VTSS_GIC400_GICD_ISPENDR6            VTSS_IOREG(VTSS_TO_GIC400,0x486)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR6 . GICD_ISPENDR6
 */
#define  VTSS_F_GIC400_GICD_ISPENDR6_GICD_ISPENDR6(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR6_GICD_ISPENDR6     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR6_GICD_ISPENDR6(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR7
 */
#define VTSS_GIC400_GICD_ISPENDR7            VTSS_IOREG(VTSS_TO_GIC400,0x487)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR7 . GICD_ISPENDR7
 */
#define  VTSS_F_GIC400_GICD_ISPENDR7_GICD_ISPENDR7(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR7_GICD_ISPENDR7     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR7_GICD_ISPENDR7(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR8
 */
#define VTSS_GIC400_GICD_ISPENDR8            VTSS_IOREG(VTSS_TO_GIC400,0x488)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR8 . GICD_ISPENDR8
 */
#define  VTSS_F_GIC400_GICD_ISPENDR8_GICD_ISPENDR8(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR8_GICD_ISPENDR8     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR8_GICD_ISPENDR8(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR9
 */
#define VTSS_GIC400_GICD_ISPENDR9            VTSS_IOREG(VTSS_TO_GIC400,0x489)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR9 . GICD_ISPENDR9
 */
#define  VTSS_F_GIC400_GICD_ISPENDR9_GICD_ISPENDR9(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR9_GICD_ISPENDR9     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR9_GICD_ISPENDR9(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR10
 */
#define VTSS_GIC400_GICD_ISPENDR10           VTSS_IOREG(VTSS_TO_GIC400,0x48a)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR10 . GICD_ISPENDR10
 */
#define  VTSS_F_GIC400_GICD_ISPENDR10_GICD_ISPENDR10(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR10_GICD_ISPENDR10     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR10_GICD_ISPENDR10(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR11
 */
#define VTSS_GIC400_GICD_ISPENDR11           VTSS_IOREG(VTSS_TO_GIC400,0x48b)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR11 . GICD_ISPENDR11
 */
#define  VTSS_F_GIC400_GICD_ISPENDR11_GICD_ISPENDR11(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR11_GICD_ISPENDR11     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR11_GICD_ISPENDR11(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR12
 */
#define VTSS_GIC400_GICD_ISPENDR12           VTSS_IOREG(VTSS_TO_GIC400,0x48c)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR12 . GICD_ISPENDR12
 */
#define  VTSS_F_GIC400_GICD_ISPENDR12_GICD_ISPENDR12(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR12_GICD_ISPENDR12     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR12_GICD_ISPENDR12(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR13
 */
#define VTSS_GIC400_GICD_ISPENDR13           VTSS_IOREG(VTSS_TO_GIC400,0x48d)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR13 . GICD_ISPENDR13
 */
#define  VTSS_F_GIC400_GICD_ISPENDR13_GICD_ISPENDR13(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR13_GICD_ISPENDR13     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR13_GICD_ISPENDR13(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR14
 */
#define VTSS_GIC400_GICD_ISPENDR14           VTSS_IOREG(VTSS_TO_GIC400,0x48e)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR14 . GICD_ISPENDR14
 */
#define  VTSS_F_GIC400_GICD_ISPENDR14_GICD_ISPENDR14(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR14_GICD_ISPENDR14     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR14_GICD_ISPENDR14(x)  (x)


/**
 * \brief Interrupt Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISPENDR15
 */
#define VTSS_GIC400_GICD_ISPENDR15           VTSS_IOREG(VTSS_TO_GIC400,0x48f)

/**
 * \brief
 * Interrupt Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISPENDR15 . GICD_ISPENDR15
 */
#define  VTSS_F_GIC400_GICD_ISPENDR15_GICD_ISPENDR15(x)  (x)
#define  VTSS_M_GIC400_GICD_ISPENDR15_GICD_ISPENDR15     0xffffffff
#define  VTSS_X_GIC400_GICD_ISPENDR15_GICD_ISPENDR15(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR0
 */
#define VTSS_GIC400_GICD_ICPENDR0            VTSS_IOREG(VTSS_TO_GIC400,0x4a0)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR0 . GICD_ICPENDR0
 */
#define  VTSS_F_GIC400_GICD_ICPENDR0_GICD_ICPENDR0(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR0_GICD_ICPENDR0     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR0_GICD_ICPENDR0(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR1
 */
#define VTSS_GIC400_GICD_ICPENDR1            VTSS_IOREG(VTSS_TO_GIC400,0x4a1)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR1 . GICD_ICPENDR1
 */
#define  VTSS_F_GIC400_GICD_ICPENDR1_GICD_ICPENDR1(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR1_GICD_ICPENDR1     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR1_GICD_ICPENDR1(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR2
 */
#define VTSS_GIC400_GICD_ICPENDR2            VTSS_IOREG(VTSS_TO_GIC400,0x4a2)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR2 . GICD_ICPENDR2
 */
#define  VTSS_F_GIC400_GICD_ICPENDR2_GICD_ICPENDR2(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR2_GICD_ICPENDR2     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR2_GICD_ICPENDR2(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR3
 */
#define VTSS_GIC400_GICD_ICPENDR3            VTSS_IOREG(VTSS_TO_GIC400,0x4a3)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR3 . GICD_ICPENDR3
 */
#define  VTSS_F_GIC400_GICD_ICPENDR3_GICD_ICPENDR3(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR3_GICD_ICPENDR3     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR3_GICD_ICPENDR3(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR4
 */
#define VTSS_GIC400_GICD_ICPENDR4            VTSS_IOREG(VTSS_TO_GIC400,0x4a4)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR4 . GICD_ICPENDR4
 */
#define  VTSS_F_GIC400_GICD_ICPENDR4_GICD_ICPENDR4(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR4_GICD_ICPENDR4     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR4_GICD_ICPENDR4(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR5
 */
#define VTSS_GIC400_GICD_ICPENDR5            VTSS_IOREG(VTSS_TO_GIC400,0x4a5)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR5 . GICD_ICPENDR5
 */
#define  VTSS_F_GIC400_GICD_ICPENDR5_GICD_ICPENDR5(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR5_GICD_ICPENDR5     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR5_GICD_ICPENDR5(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR6
 */
#define VTSS_GIC400_GICD_ICPENDR6            VTSS_IOREG(VTSS_TO_GIC400,0x4a6)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR6 . GICD_ICPENDR6
 */
#define  VTSS_F_GIC400_GICD_ICPENDR6_GICD_ICPENDR6(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR6_GICD_ICPENDR6     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR6_GICD_ICPENDR6(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR7
 */
#define VTSS_GIC400_GICD_ICPENDR7            VTSS_IOREG(VTSS_TO_GIC400,0x4a7)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR7 . GICD_ICPENDR7
 */
#define  VTSS_F_GIC400_GICD_ICPENDR7_GICD_ICPENDR7(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR7_GICD_ICPENDR7     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR7_GICD_ICPENDR7(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR8
 */
#define VTSS_GIC400_GICD_ICPENDR8            VTSS_IOREG(VTSS_TO_GIC400,0x4a8)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR8 . GICD_ICPENDR8
 */
#define  VTSS_F_GIC400_GICD_ICPENDR8_GICD_ICPENDR8(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR8_GICD_ICPENDR8     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR8_GICD_ICPENDR8(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR9
 */
#define VTSS_GIC400_GICD_ICPENDR9            VTSS_IOREG(VTSS_TO_GIC400,0x4a9)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR9 . GICD_ICPENDR9
 */
#define  VTSS_F_GIC400_GICD_ICPENDR9_GICD_ICPENDR9(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR9_GICD_ICPENDR9     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR9_GICD_ICPENDR9(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR10
 */
#define VTSS_GIC400_GICD_ICPENDR10           VTSS_IOREG(VTSS_TO_GIC400,0x4aa)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR10 . GICD_ICPENDR10
 */
#define  VTSS_F_GIC400_GICD_ICPENDR10_GICD_ICPENDR10(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR10_GICD_ICPENDR10     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR10_GICD_ICPENDR10(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR11
 */
#define VTSS_GIC400_GICD_ICPENDR11           VTSS_IOREG(VTSS_TO_GIC400,0x4ab)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR11 . GICD_ICPENDR11
 */
#define  VTSS_F_GIC400_GICD_ICPENDR11_GICD_ICPENDR11(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR11_GICD_ICPENDR11     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR11_GICD_ICPENDR11(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR12
 */
#define VTSS_GIC400_GICD_ICPENDR12           VTSS_IOREG(VTSS_TO_GIC400,0x4ac)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR12 . GICD_ICPENDR12
 */
#define  VTSS_F_GIC400_GICD_ICPENDR12_GICD_ICPENDR12(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR12_GICD_ICPENDR12     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR12_GICD_ICPENDR12(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR13
 */
#define VTSS_GIC400_GICD_ICPENDR13           VTSS_IOREG(VTSS_TO_GIC400,0x4ad)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR13 . GICD_ICPENDR13
 */
#define  VTSS_F_GIC400_GICD_ICPENDR13_GICD_ICPENDR13(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR13_GICD_ICPENDR13     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR13_GICD_ICPENDR13(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR14
 */
#define VTSS_GIC400_GICD_ICPENDR14           VTSS_IOREG(VTSS_TO_GIC400,0x4ae)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR14 . GICD_ICPENDR14
 */
#define  VTSS_F_GIC400_GICD_ICPENDR14_GICD_ICPENDR14(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR14_GICD_ICPENDR14     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR14_GICD_ICPENDR14(x)  (x)


/**
 * \brief Interrupt Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICPENDR15
 */
#define VTSS_GIC400_GICD_ICPENDR15           VTSS_IOREG(VTSS_TO_GIC400,0x4af)

/**
 * \brief
 * Interrupt Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICPENDR15 . GICD_ICPENDR15
 */
#define  VTSS_F_GIC400_GICD_ICPENDR15_GICD_ICPENDR15(x)  (x)
#define  VTSS_M_GIC400_GICD_ICPENDR15_GICD_ICPENDR15     0xffffffff
#define  VTSS_X_GIC400_GICD_ICPENDR15_GICD_ICPENDR15(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER0
 */
#define VTSS_GIC400_GICD_ISACTIVER0          VTSS_IOREG(VTSS_TO_GIC400,0x4c0)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER0 . GICD_ISACTIVER0
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER0_GICD_ISACTIVER0(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER0_GICD_ISACTIVER0     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER0_GICD_ISACTIVER0(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER1
 */
#define VTSS_GIC400_GICD_ISACTIVER1          VTSS_IOREG(VTSS_TO_GIC400,0x4c1)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER1 . GICD_ISACTIVER1
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER1_GICD_ISACTIVER1(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER1_GICD_ISACTIVER1     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER1_GICD_ISACTIVER1(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER2
 */
#define VTSS_GIC400_GICD_ISACTIVER2          VTSS_IOREG(VTSS_TO_GIC400,0x4c2)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER2 . GICD_ISACTIVER2
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER2_GICD_ISACTIVER2(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER2_GICD_ISACTIVER2     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER2_GICD_ISACTIVER2(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER3
 */
#define VTSS_GIC400_GICD_ISACTIVER3          VTSS_IOREG(VTSS_TO_GIC400,0x4c3)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER3 . GICD_ISACTIVER3
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER3_GICD_ISACTIVER3(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER3_GICD_ISACTIVER3     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER3_GICD_ISACTIVER3(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER4
 */
#define VTSS_GIC400_GICD_ISACTIVER4          VTSS_IOREG(VTSS_TO_GIC400,0x4c4)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER4 . GICD_ISACTIVER4
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER4_GICD_ISACTIVER4(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER4_GICD_ISACTIVER4     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER4_GICD_ISACTIVER4(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER5
 */
#define VTSS_GIC400_GICD_ISACTIVER5          VTSS_IOREG(VTSS_TO_GIC400,0x4c5)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER5 . GICD_ISACTIVER5
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER5_GICD_ISACTIVER5(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER5_GICD_ISACTIVER5     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER5_GICD_ISACTIVER5(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER6
 */
#define VTSS_GIC400_GICD_ISACTIVER6          VTSS_IOREG(VTSS_TO_GIC400,0x4c6)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER6 . GICD_ISACTIVER6
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER6_GICD_ISACTIVER6(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER6_GICD_ISACTIVER6     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER6_GICD_ISACTIVER6(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER7
 */
#define VTSS_GIC400_GICD_ISACTIVER7          VTSS_IOREG(VTSS_TO_GIC400,0x4c7)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER7 . GICD_ISACTIVER7
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER7_GICD_ISACTIVER7(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER7_GICD_ISACTIVER7     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER7_GICD_ISACTIVER7(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER8
 */
#define VTSS_GIC400_GICD_ISACTIVER8          VTSS_IOREG(VTSS_TO_GIC400,0x4c8)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER8 . GICD_ISACTIVER8
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER8_GICD_ISACTIVER8(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER8_GICD_ISACTIVER8     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER8_GICD_ISACTIVER8(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER9
 */
#define VTSS_GIC400_GICD_ISACTIVER9          VTSS_IOREG(VTSS_TO_GIC400,0x4c9)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER9 . GICD_ISACTIVER9
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER9_GICD_ISACTIVER9(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER9_GICD_ISACTIVER9     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER9_GICD_ISACTIVER9(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER10
 */
#define VTSS_GIC400_GICD_ISACTIVER10         VTSS_IOREG(VTSS_TO_GIC400,0x4ca)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER10 . GICD_ISACTIVER10
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER10_GICD_ISACTIVER10(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER10_GICD_ISACTIVER10     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER10_GICD_ISACTIVER10(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER11
 */
#define VTSS_GIC400_GICD_ISACTIVER11         VTSS_IOREG(VTSS_TO_GIC400,0x4cb)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER11 . GICD_ISACTIVER11
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER11_GICD_ISACTIVER11(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER11_GICD_ISACTIVER11     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER11_GICD_ISACTIVER11(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER12
 */
#define VTSS_GIC400_GICD_ISACTIVER12         VTSS_IOREG(VTSS_TO_GIC400,0x4cc)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER12 . GICD_ISACTIVER12
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER12_GICD_ISACTIVER12(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER12_GICD_ISACTIVER12     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER12_GICD_ISACTIVER12(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER13
 */
#define VTSS_GIC400_GICD_ISACTIVER13         VTSS_IOREG(VTSS_TO_GIC400,0x4cd)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER13 . GICD_ISACTIVER13
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER13_GICD_ISACTIVER13(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER13_GICD_ISACTIVER13     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER13_GICD_ISACTIVER13(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER14
 */
#define VTSS_GIC400_GICD_ISACTIVER14         VTSS_IOREG(VTSS_TO_GIC400,0x4ce)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER14 . GICD_ISACTIVER14
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER14_GICD_ISACTIVER14(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER14_GICD_ISACTIVER14     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER14_GICD_ISACTIVER14(x)  (x)


/**
 * \brief Interrupt Set-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ISACTIVER15
 */
#define VTSS_GIC400_GICD_ISACTIVER15         VTSS_IOREG(VTSS_TO_GIC400,0x4cf)

/**
 * \brief
 * Interrupt Set-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ISACTIVER15 . GICD_ISACTIVER15
 */
#define  VTSS_F_GIC400_GICD_ISACTIVER15_GICD_ISACTIVER15(x)  (x)
#define  VTSS_M_GIC400_GICD_ISACTIVER15_GICD_ISACTIVER15     0xffffffff
#define  VTSS_X_GIC400_GICD_ISACTIVER15_GICD_ISACTIVER15(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER0
 */
#define VTSS_GIC400_GICD_ICACTIVER0          VTSS_IOREG(VTSS_TO_GIC400,0x4e0)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER0 . GICD_ICACTIVER0
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER0_GICD_ICACTIVER0(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER0_GICD_ICACTIVER0     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER0_GICD_ICACTIVER0(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER1
 */
#define VTSS_GIC400_GICD_ICACTIVER1          VTSS_IOREG(VTSS_TO_GIC400,0x4e1)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER1 . GICD_ICACTIVER1
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER1_GICD_ICACTIVER1(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER1_GICD_ICACTIVER1     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER1_GICD_ICACTIVER1(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER2
 */
#define VTSS_GIC400_GICD_ICACTIVER2          VTSS_IOREG(VTSS_TO_GIC400,0x4e2)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER2 . GICD_ICACTIVER2
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER2_GICD_ICACTIVER2(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER2_GICD_ICACTIVER2     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER2_GICD_ICACTIVER2(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER3
 */
#define VTSS_GIC400_GICD_ICACTIVER3          VTSS_IOREG(VTSS_TO_GIC400,0x4e3)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER3 . GICD_ICACTIVER3
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER3_GICD_ICACTIVER3(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER3_GICD_ICACTIVER3     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER3_GICD_ICACTIVER3(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER4
 */
#define VTSS_GIC400_GICD_ICACTIVER4          VTSS_IOREG(VTSS_TO_GIC400,0x4e4)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER4 . GICD_ICACTIVER4
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER4_GICD_ICACTIVER4(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER4_GICD_ICACTIVER4     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER4_GICD_ICACTIVER4(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER5
 */
#define VTSS_GIC400_GICD_ICACTIVER5          VTSS_IOREG(VTSS_TO_GIC400,0x4e5)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER5 . GICD_ICACTIVER5
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER5_GICD_ICACTIVER5(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER5_GICD_ICACTIVER5     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER5_GICD_ICACTIVER5(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER6
 */
#define VTSS_GIC400_GICD_ICACTIVER6          VTSS_IOREG(VTSS_TO_GIC400,0x4e6)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER6 . GICD_ICACTIVER6
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER6_GICD_ICACTIVER6(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER6_GICD_ICACTIVER6     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER6_GICD_ICACTIVER6(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER7
 */
#define VTSS_GIC400_GICD_ICACTIVER7          VTSS_IOREG(VTSS_TO_GIC400,0x4e7)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER7 . GICD_ICACTIVER7
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER7_GICD_ICACTIVER7(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER7_GICD_ICACTIVER7     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER7_GICD_ICACTIVER7(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER8
 */
#define VTSS_GIC400_GICD_ICACTIVER8          VTSS_IOREG(VTSS_TO_GIC400,0x4e8)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER8 . GICD_ICACTIVER8
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER8_GICD_ICACTIVER8(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER8_GICD_ICACTIVER8     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER8_GICD_ICACTIVER8(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER9
 */
#define VTSS_GIC400_GICD_ICACTIVER9          VTSS_IOREG(VTSS_TO_GIC400,0x4e9)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER9 . GICD_ICACTIVER9
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER9_GICD_ICACTIVER9(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER9_GICD_ICACTIVER9     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER9_GICD_ICACTIVER9(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER10
 */
#define VTSS_GIC400_GICD_ICACTIVER10         VTSS_IOREG(VTSS_TO_GIC400,0x4ea)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER10 . GICD_ICACTIVER10
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER10_GICD_ICACTIVER10(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER10_GICD_ICACTIVER10     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER10_GICD_ICACTIVER10(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER11
 */
#define VTSS_GIC400_GICD_ICACTIVER11         VTSS_IOREG(VTSS_TO_GIC400,0x4eb)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER11 . GICD_ICACTIVER11
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER11_GICD_ICACTIVER11(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER11_GICD_ICACTIVER11     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER11_GICD_ICACTIVER11(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER12
 */
#define VTSS_GIC400_GICD_ICACTIVER12         VTSS_IOREG(VTSS_TO_GIC400,0x4ec)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER12 . GICD_ICACTIVER12
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER12_GICD_ICACTIVER12(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER12_GICD_ICACTIVER12     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER12_GICD_ICACTIVER12(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER13
 */
#define VTSS_GIC400_GICD_ICACTIVER13         VTSS_IOREG(VTSS_TO_GIC400,0x4ed)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER13 . GICD_ICACTIVER13
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER13_GICD_ICACTIVER13(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER13_GICD_ICACTIVER13     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER13_GICD_ICACTIVER13(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER14
 */
#define VTSS_GIC400_GICD_ICACTIVER14         VTSS_IOREG(VTSS_TO_GIC400,0x4ee)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER14 . GICD_ICACTIVER14
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER14_GICD_ICACTIVER14(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER14_GICD_ICACTIVER14     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER14_GICD_ICACTIVER14(x)  (x)


/**
 * \brief Interrupt Clear-Active Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICACTIVER15
 */
#define VTSS_GIC400_GICD_ICACTIVER15         VTSS_IOREG(VTSS_TO_GIC400,0x4ef)

/**
 * \brief
 * Interrupt Clear-Active Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICACTIVER15 . GICD_ICACTIVER15
 */
#define  VTSS_F_GIC400_GICD_ICACTIVER15_GICD_ICACTIVER15(x)  (x)
#define  VTSS_M_GIC400_GICD_ICACTIVER15_GICD_ICACTIVER15     0xffffffff
#define  VTSS_X_GIC400_GICD_ICACTIVER15_GICD_ICACTIVER15(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR0
 */
#define VTSS_GIC400_GICD_IPRIORITYR0         VTSS_IOREG(VTSS_TO_GIC400,0x500)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR0 . GICD_IPRIORITYR0
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR0_GICD_IPRIORITYR0(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR0_GICD_IPRIORITYR0     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR0_GICD_IPRIORITYR0(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR1
 */
#define VTSS_GIC400_GICD_IPRIORITYR1         VTSS_IOREG(VTSS_TO_GIC400,0x501)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR1 . GICD_IPRIORITYR1
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR1_GICD_IPRIORITYR1(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR1_GICD_IPRIORITYR1     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR1_GICD_IPRIORITYR1(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR2
 */
#define VTSS_GIC400_GICD_IPRIORITYR2         VTSS_IOREG(VTSS_TO_GIC400,0x502)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR2 . GICD_IPRIORITYR2
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR2_GICD_IPRIORITYR2(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR2_GICD_IPRIORITYR2     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR2_GICD_IPRIORITYR2(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR3
 */
#define VTSS_GIC400_GICD_IPRIORITYR3         VTSS_IOREG(VTSS_TO_GIC400,0x503)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR3 . GICD_IPRIORITYR3
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR3_GICD_IPRIORITYR3(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR3_GICD_IPRIORITYR3     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR3_GICD_IPRIORITYR3(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR4
 */
#define VTSS_GIC400_GICD_IPRIORITYR4         VTSS_IOREG(VTSS_TO_GIC400,0x504)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR4 . GICD_IPRIORITYR4
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR4_GICD_IPRIORITYR4(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR4_GICD_IPRIORITYR4     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR4_GICD_IPRIORITYR4(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR5
 */
#define VTSS_GIC400_GICD_IPRIORITYR5         VTSS_IOREG(VTSS_TO_GIC400,0x505)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR5 . GICD_IPRIORITYR5
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR5_GICD_IPRIORITYR5(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR5_GICD_IPRIORITYR5     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR5_GICD_IPRIORITYR5(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR6
 */
#define VTSS_GIC400_GICD_IPRIORITYR6         VTSS_IOREG(VTSS_TO_GIC400,0x506)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR6 . GICD_IPRIORITYR6
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR6_GICD_IPRIORITYR6(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR6_GICD_IPRIORITYR6     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR6_GICD_IPRIORITYR6(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR7
 */
#define VTSS_GIC400_GICD_IPRIORITYR7         VTSS_IOREG(VTSS_TO_GIC400,0x507)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR7 . GICD_IPRIORITYR7
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR7_GICD_IPRIORITYR7(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR7_GICD_IPRIORITYR7     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR7_GICD_IPRIORITYR7(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR8
 */
#define VTSS_GIC400_GICD_IPRIORITYR8         VTSS_IOREG(VTSS_TO_GIC400,0x508)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR8 . GICD_IPRIORITYR8
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR8_GICD_IPRIORITYR8(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR8_GICD_IPRIORITYR8     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR8_GICD_IPRIORITYR8(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR9
 */
#define VTSS_GIC400_GICD_IPRIORITYR9         VTSS_IOREG(VTSS_TO_GIC400,0x509)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR9 . GICD_IPRIORITYR9
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR9_GICD_IPRIORITYR9(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR9_GICD_IPRIORITYR9     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR9_GICD_IPRIORITYR9(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR10
 */
#define VTSS_GIC400_GICD_IPRIORITYR10        VTSS_IOREG(VTSS_TO_GIC400,0x50a)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR10 . GICD_IPRIORITYR10
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR10_GICD_IPRIORITYR10(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR10_GICD_IPRIORITYR10     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR10_GICD_IPRIORITYR10(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR11
 */
#define VTSS_GIC400_GICD_IPRIORITYR11        VTSS_IOREG(VTSS_TO_GIC400,0x50b)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR11 . GICD_IPRIORITYR11
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR11_GICD_IPRIORITYR11(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR11_GICD_IPRIORITYR11     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR11_GICD_IPRIORITYR11(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR12
 */
#define VTSS_GIC400_GICD_IPRIORITYR12        VTSS_IOREG(VTSS_TO_GIC400,0x50c)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR12 . GICD_IPRIORITYR12
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR12_GICD_IPRIORITYR12(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR12_GICD_IPRIORITYR12     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR12_GICD_IPRIORITYR12(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR13
 */
#define VTSS_GIC400_GICD_IPRIORITYR13        VTSS_IOREG(VTSS_TO_GIC400,0x50d)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR13 . GICD_IPRIORITYR13
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR13_GICD_IPRIORITYR13(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR13_GICD_IPRIORITYR13     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR13_GICD_IPRIORITYR13(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR14
 */
#define VTSS_GIC400_GICD_IPRIORITYR14        VTSS_IOREG(VTSS_TO_GIC400,0x50e)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR14 . GICD_IPRIORITYR14
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR14_GICD_IPRIORITYR14(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR14_GICD_IPRIORITYR14     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR14_GICD_IPRIORITYR14(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR15
 */
#define VTSS_GIC400_GICD_IPRIORITYR15        VTSS_IOREG(VTSS_TO_GIC400,0x50f)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR15 . GICD_IPRIORITYR15
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR15_GICD_IPRIORITYR15(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR15_GICD_IPRIORITYR15     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR15_GICD_IPRIORITYR15(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR16
 */
#define VTSS_GIC400_GICD_IPRIORITYR16        VTSS_IOREG(VTSS_TO_GIC400,0x510)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR16 . GICD_IPRIORITYR16
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR16_GICD_IPRIORITYR16(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR16_GICD_IPRIORITYR16     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR16_GICD_IPRIORITYR16(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR17
 */
#define VTSS_GIC400_GICD_IPRIORITYR17        VTSS_IOREG(VTSS_TO_GIC400,0x511)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR17 . GICD_IPRIORITYR17
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR17_GICD_IPRIORITYR17(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR17_GICD_IPRIORITYR17     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR17_GICD_IPRIORITYR17(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR18
 */
#define VTSS_GIC400_GICD_IPRIORITYR18        VTSS_IOREG(VTSS_TO_GIC400,0x512)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR18 . GICD_IPRIORITYR18
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR18_GICD_IPRIORITYR18(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR18_GICD_IPRIORITYR18     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR18_GICD_IPRIORITYR18(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR19
 */
#define VTSS_GIC400_GICD_IPRIORITYR19        VTSS_IOREG(VTSS_TO_GIC400,0x513)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR19 . GICD_IPRIORITYR19
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR19_GICD_IPRIORITYR19(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR19_GICD_IPRIORITYR19     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR19_GICD_IPRIORITYR19(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR20
 */
#define VTSS_GIC400_GICD_IPRIORITYR20        VTSS_IOREG(VTSS_TO_GIC400,0x514)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR20 . GICD_IPRIORITYR20
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR20_GICD_IPRIORITYR20(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR20_GICD_IPRIORITYR20     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR20_GICD_IPRIORITYR20(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR21
 */
#define VTSS_GIC400_GICD_IPRIORITYR21        VTSS_IOREG(VTSS_TO_GIC400,0x515)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR21 . GICD_IPRIORITYR21
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR21_GICD_IPRIORITYR21(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR21_GICD_IPRIORITYR21     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR21_GICD_IPRIORITYR21(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR22
 */
#define VTSS_GIC400_GICD_IPRIORITYR22        VTSS_IOREG(VTSS_TO_GIC400,0x516)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR22 . GICD_IPRIORITYR22
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR22_GICD_IPRIORITYR22(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR22_GICD_IPRIORITYR22     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR22_GICD_IPRIORITYR22(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR23
 */
#define VTSS_GIC400_GICD_IPRIORITYR23        VTSS_IOREG(VTSS_TO_GIC400,0x517)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR23 . GICD_IPRIORITYR23
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR23_GICD_IPRIORITYR23(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR23_GICD_IPRIORITYR23     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR23_GICD_IPRIORITYR23(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR24
 */
#define VTSS_GIC400_GICD_IPRIORITYR24        VTSS_IOREG(VTSS_TO_GIC400,0x518)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR24 . GICD_IPRIORITYR24
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR24_GICD_IPRIORITYR24(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR24_GICD_IPRIORITYR24     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR24_GICD_IPRIORITYR24(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR25
 */
#define VTSS_GIC400_GICD_IPRIORITYR25        VTSS_IOREG(VTSS_TO_GIC400,0x519)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR25 . GICD_IPRIORITYR25
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR25_GICD_IPRIORITYR25(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR25_GICD_IPRIORITYR25     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR25_GICD_IPRIORITYR25(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR26
 */
#define VTSS_GIC400_GICD_IPRIORITYR26        VTSS_IOREG(VTSS_TO_GIC400,0x51a)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR26 . GICD_IPRIORITYR26
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR26_GICD_IPRIORITYR26(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR26_GICD_IPRIORITYR26     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR26_GICD_IPRIORITYR26(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR27
 */
#define VTSS_GIC400_GICD_IPRIORITYR27        VTSS_IOREG(VTSS_TO_GIC400,0x51b)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR27 . GICD_IPRIORITYR27
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR27_GICD_IPRIORITYR27(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR27_GICD_IPRIORITYR27     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR27_GICD_IPRIORITYR27(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR28
 */
#define VTSS_GIC400_GICD_IPRIORITYR28        VTSS_IOREG(VTSS_TO_GIC400,0x51c)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR28 . GICD_IPRIORITYR28
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR28_GICD_IPRIORITYR28(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR28_GICD_IPRIORITYR28     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR28_GICD_IPRIORITYR28(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR29
 */
#define VTSS_GIC400_GICD_IPRIORITYR29        VTSS_IOREG(VTSS_TO_GIC400,0x51d)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR29 . GICD_IPRIORITYR29
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR29_GICD_IPRIORITYR29(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR29_GICD_IPRIORITYR29     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR29_GICD_IPRIORITYR29(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR30
 */
#define VTSS_GIC400_GICD_IPRIORITYR30        VTSS_IOREG(VTSS_TO_GIC400,0x51e)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR30 . GICD_IPRIORITYR30
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR30_GICD_IPRIORITYR30(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR30_GICD_IPRIORITYR30     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR30_GICD_IPRIORITYR30(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR31
 */
#define VTSS_GIC400_GICD_IPRIORITYR31        VTSS_IOREG(VTSS_TO_GIC400,0x51f)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR31 . GICD_IPRIORITYR31
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR31_GICD_IPRIORITYR31(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR31_GICD_IPRIORITYR31     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR31_GICD_IPRIORITYR31(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR32
 */
#define VTSS_GIC400_GICD_IPRIORITYR32        VTSS_IOREG(VTSS_TO_GIC400,0x520)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR32 . GICD_IPRIORITYR32
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR32_GICD_IPRIORITYR32(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR32_GICD_IPRIORITYR32     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR32_GICD_IPRIORITYR32(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR33
 */
#define VTSS_GIC400_GICD_IPRIORITYR33        VTSS_IOREG(VTSS_TO_GIC400,0x521)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR33 . GICD_IPRIORITYR33
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR33_GICD_IPRIORITYR33(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR33_GICD_IPRIORITYR33     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR33_GICD_IPRIORITYR33(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR34
 */
#define VTSS_GIC400_GICD_IPRIORITYR34        VTSS_IOREG(VTSS_TO_GIC400,0x522)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR34 . GICD_IPRIORITYR34
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR34_GICD_IPRIORITYR34(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR34_GICD_IPRIORITYR34     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR34_GICD_IPRIORITYR34(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR35
 */
#define VTSS_GIC400_GICD_IPRIORITYR35        VTSS_IOREG(VTSS_TO_GIC400,0x523)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR35 . GICD_IPRIORITYR35
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR35_GICD_IPRIORITYR35(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR35_GICD_IPRIORITYR35     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR35_GICD_IPRIORITYR35(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR36
 */
#define VTSS_GIC400_GICD_IPRIORITYR36        VTSS_IOREG(VTSS_TO_GIC400,0x524)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR36 . GICD_IPRIORITYR36
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR36_GICD_IPRIORITYR36(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR36_GICD_IPRIORITYR36     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR36_GICD_IPRIORITYR36(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR37
 */
#define VTSS_GIC400_GICD_IPRIORITYR37        VTSS_IOREG(VTSS_TO_GIC400,0x525)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR37 . GICD_IPRIORITYR37
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR37_GICD_IPRIORITYR37(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR37_GICD_IPRIORITYR37     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR37_GICD_IPRIORITYR37(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR38
 */
#define VTSS_GIC400_GICD_IPRIORITYR38        VTSS_IOREG(VTSS_TO_GIC400,0x526)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR38 . GICD_IPRIORITYR38
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR38_GICD_IPRIORITYR38(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR38_GICD_IPRIORITYR38     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR38_GICD_IPRIORITYR38(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR39
 */
#define VTSS_GIC400_GICD_IPRIORITYR39        VTSS_IOREG(VTSS_TO_GIC400,0x527)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR39 . GICD_IPRIORITYR39
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR39_GICD_IPRIORITYR39(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR39_GICD_IPRIORITYR39     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR39_GICD_IPRIORITYR39(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR40
 */
#define VTSS_GIC400_GICD_IPRIORITYR40        VTSS_IOREG(VTSS_TO_GIC400,0x528)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR40 . GICD_IPRIORITYR40
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR40_GICD_IPRIORITYR40(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR40_GICD_IPRIORITYR40     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR40_GICD_IPRIORITYR40(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR41
 */
#define VTSS_GIC400_GICD_IPRIORITYR41        VTSS_IOREG(VTSS_TO_GIC400,0x529)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR41 . GICD_IPRIORITYR41
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR41_GICD_IPRIORITYR41(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR41_GICD_IPRIORITYR41     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR41_GICD_IPRIORITYR41(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR42
 */
#define VTSS_GIC400_GICD_IPRIORITYR42        VTSS_IOREG(VTSS_TO_GIC400,0x52a)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR42 . GICD_IPRIORITYR42
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR42_GICD_IPRIORITYR42(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR42_GICD_IPRIORITYR42     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR42_GICD_IPRIORITYR42(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR43
 */
#define VTSS_GIC400_GICD_IPRIORITYR43        VTSS_IOREG(VTSS_TO_GIC400,0x52b)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR43 . GICD_IPRIORITYR43
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR43_GICD_IPRIORITYR43(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR43_GICD_IPRIORITYR43     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR43_GICD_IPRIORITYR43(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR44
 */
#define VTSS_GIC400_GICD_IPRIORITYR44        VTSS_IOREG(VTSS_TO_GIC400,0x52c)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR44 . GICD_IPRIORITYR44
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR44_GICD_IPRIORITYR44(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR44_GICD_IPRIORITYR44     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR44_GICD_IPRIORITYR44(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR45
 */
#define VTSS_GIC400_GICD_IPRIORITYR45        VTSS_IOREG(VTSS_TO_GIC400,0x52d)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR45 . GICD_IPRIORITYR45
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR45_GICD_IPRIORITYR45(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR45_GICD_IPRIORITYR45     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR45_GICD_IPRIORITYR45(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR46
 */
#define VTSS_GIC400_GICD_IPRIORITYR46        VTSS_IOREG(VTSS_TO_GIC400,0x52e)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR46 . GICD_IPRIORITYR46
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR46_GICD_IPRIORITYR46(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR46_GICD_IPRIORITYR46     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR46_GICD_IPRIORITYR46(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR47
 */
#define VTSS_GIC400_GICD_IPRIORITYR47        VTSS_IOREG(VTSS_TO_GIC400,0x52f)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR47 . GICD_IPRIORITYR47
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR47_GICD_IPRIORITYR47(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR47_GICD_IPRIORITYR47     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR47_GICD_IPRIORITYR47(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR48
 */
#define VTSS_GIC400_GICD_IPRIORITYR48        VTSS_IOREG(VTSS_TO_GIC400,0x530)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR48 . GICD_IPRIORITYR48
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR48_GICD_IPRIORITYR48(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR48_GICD_IPRIORITYR48     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR48_GICD_IPRIORITYR48(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR49
 */
#define VTSS_GIC400_GICD_IPRIORITYR49        VTSS_IOREG(VTSS_TO_GIC400,0x531)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR49 . GICD_IPRIORITYR49
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR49_GICD_IPRIORITYR49(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR49_GICD_IPRIORITYR49     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR49_GICD_IPRIORITYR49(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR50
 */
#define VTSS_GIC400_GICD_IPRIORITYR50        VTSS_IOREG(VTSS_TO_GIC400,0x532)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR50 . GICD_IPRIORITYR50
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR50_GICD_IPRIORITYR50(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR50_GICD_IPRIORITYR50     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR50_GICD_IPRIORITYR50(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR51
 */
#define VTSS_GIC400_GICD_IPRIORITYR51        VTSS_IOREG(VTSS_TO_GIC400,0x533)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR51 . GICD_IPRIORITYR51
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR51_GICD_IPRIORITYR51(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR51_GICD_IPRIORITYR51     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR51_GICD_IPRIORITYR51(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR52
 */
#define VTSS_GIC400_GICD_IPRIORITYR52        VTSS_IOREG(VTSS_TO_GIC400,0x534)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR52 . GICD_IPRIORITYR52
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR52_GICD_IPRIORITYR52(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR52_GICD_IPRIORITYR52     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR52_GICD_IPRIORITYR52(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR53
 */
#define VTSS_GIC400_GICD_IPRIORITYR53        VTSS_IOREG(VTSS_TO_GIC400,0x535)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR53 . GICD_IPRIORITYR53
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR53_GICD_IPRIORITYR53(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR53_GICD_IPRIORITYR53     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR53_GICD_IPRIORITYR53(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR54
 */
#define VTSS_GIC400_GICD_IPRIORITYR54        VTSS_IOREG(VTSS_TO_GIC400,0x536)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR54 . GICD_IPRIORITYR54
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR54_GICD_IPRIORITYR54(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR54_GICD_IPRIORITYR54     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR54_GICD_IPRIORITYR54(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR55
 */
#define VTSS_GIC400_GICD_IPRIORITYR55        VTSS_IOREG(VTSS_TO_GIC400,0x537)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR55 . GICD_IPRIORITYR55
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR55_GICD_IPRIORITYR55(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR55_GICD_IPRIORITYR55     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR55_GICD_IPRIORITYR55(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR56
 */
#define VTSS_GIC400_GICD_IPRIORITYR56        VTSS_IOREG(VTSS_TO_GIC400,0x538)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR56 . GICD_IPRIORITYR56
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR56_GICD_IPRIORITYR56(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR56_GICD_IPRIORITYR56     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR56_GICD_IPRIORITYR56(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR57
 */
#define VTSS_GIC400_GICD_IPRIORITYR57        VTSS_IOREG(VTSS_TO_GIC400,0x539)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR57 . GICD_IPRIORITYR57
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR57_GICD_IPRIORITYR57(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR57_GICD_IPRIORITYR57     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR57_GICD_IPRIORITYR57(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR58
 */
#define VTSS_GIC400_GICD_IPRIORITYR58        VTSS_IOREG(VTSS_TO_GIC400,0x53a)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR58 . GICD_IPRIORITYR58
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR58_GICD_IPRIORITYR58(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR58_GICD_IPRIORITYR58     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR58_GICD_IPRIORITYR58(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR59
 */
#define VTSS_GIC400_GICD_IPRIORITYR59        VTSS_IOREG(VTSS_TO_GIC400,0x53b)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR59 . GICD_IPRIORITYR59
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR59_GICD_IPRIORITYR59(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR59_GICD_IPRIORITYR59     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR59_GICD_IPRIORITYR59(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR60
 */
#define VTSS_GIC400_GICD_IPRIORITYR60        VTSS_IOREG(VTSS_TO_GIC400,0x53c)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR60 . GICD_IPRIORITYR60
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR60_GICD_IPRIORITYR60(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR60_GICD_IPRIORITYR60     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR60_GICD_IPRIORITYR60(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR61
 */
#define VTSS_GIC400_GICD_IPRIORITYR61        VTSS_IOREG(VTSS_TO_GIC400,0x53d)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR61 . GICD_IPRIORITYR61
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR61_GICD_IPRIORITYR61(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR61_GICD_IPRIORITYR61     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR61_GICD_IPRIORITYR61(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR62
 */
#define VTSS_GIC400_GICD_IPRIORITYR62        VTSS_IOREG(VTSS_TO_GIC400,0x53e)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR62 . GICD_IPRIORITYR62
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR62_GICD_IPRIORITYR62(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR62_GICD_IPRIORITYR62     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR62_GICD_IPRIORITYR62(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR63
 */
#define VTSS_GIC400_GICD_IPRIORITYR63        VTSS_IOREG(VTSS_TO_GIC400,0x53f)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR63 . GICD_IPRIORITYR63
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR63_GICD_IPRIORITYR63(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR63_GICD_IPRIORITYR63     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR63_GICD_IPRIORITYR63(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR64
 */
#define VTSS_GIC400_GICD_IPRIORITYR64        VTSS_IOREG(VTSS_TO_GIC400,0x540)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR64 . GICD_IPRIORITYR64
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR64_GICD_IPRIORITYR64(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR64_GICD_IPRIORITYR64     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR64_GICD_IPRIORITYR64(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR65
 */
#define VTSS_GIC400_GICD_IPRIORITYR65        VTSS_IOREG(VTSS_TO_GIC400,0x541)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR65 . GICD_IPRIORITYR65
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR65_GICD_IPRIORITYR65(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR65_GICD_IPRIORITYR65     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR65_GICD_IPRIORITYR65(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR66
 */
#define VTSS_GIC400_GICD_IPRIORITYR66        VTSS_IOREG(VTSS_TO_GIC400,0x542)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR66 . GICD_IPRIORITYR66
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR66_GICD_IPRIORITYR66(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR66_GICD_IPRIORITYR66     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR66_GICD_IPRIORITYR66(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR67
 */
#define VTSS_GIC400_GICD_IPRIORITYR67        VTSS_IOREG(VTSS_TO_GIC400,0x543)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR67 . GICD_IPRIORITYR67
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR67_GICD_IPRIORITYR67(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR67_GICD_IPRIORITYR67     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR67_GICD_IPRIORITYR67(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR68
 */
#define VTSS_GIC400_GICD_IPRIORITYR68        VTSS_IOREG(VTSS_TO_GIC400,0x544)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR68 . GICD_IPRIORITYR68
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR68_GICD_IPRIORITYR68(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR68_GICD_IPRIORITYR68     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR68_GICD_IPRIORITYR68(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR69
 */
#define VTSS_GIC400_GICD_IPRIORITYR69        VTSS_IOREG(VTSS_TO_GIC400,0x545)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR69 . GICD_IPRIORITYR69
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR69_GICD_IPRIORITYR69(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR69_GICD_IPRIORITYR69     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR69_GICD_IPRIORITYR69(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR70
 */
#define VTSS_GIC400_GICD_IPRIORITYR70        VTSS_IOREG(VTSS_TO_GIC400,0x546)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR70 . GICD_IPRIORITYR70
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR70_GICD_IPRIORITYR70(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR70_GICD_IPRIORITYR70     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR70_GICD_IPRIORITYR70(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR71
 */
#define VTSS_GIC400_GICD_IPRIORITYR71        VTSS_IOREG(VTSS_TO_GIC400,0x547)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR71 . GICD_IPRIORITYR71
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR71_GICD_IPRIORITYR71(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR71_GICD_IPRIORITYR71     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR71_GICD_IPRIORITYR71(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR72
 */
#define VTSS_GIC400_GICD_IPRIORITYR72        VTSS_IOREG(VTSS_TO_GIC400,0x548)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR72 . GICD_IPRIORITYR72
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR72_GICD_IPRIORITYR72(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR72_GICD_IPRIORITYR72     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR72_GICD_IPRIORITYR72(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR73
 */
#define VTSS_GIC400_GICD_IPRIORITYR73        VTSS_IOREG(VTSS_TO_GIC400,0x549)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR73 . GICD_IPRIORITYR73
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR73_GICD_IPRIORITYR73(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR73_GICD_IPRIORITYR73     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR73_GICD_IPRIORITYR73(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR74
 */
#define VTSS_GIC400_GICD_IPRIORITYR74        VTSS_IOREG(VTSS_TO_GIC400,0x54a)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR74 . GICD_IPRIORITYR74
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR74_GICD_IPRIORITYR74(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR74_GICD_IPRIORITYR74     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR74_GICD_IPRIORITYR74(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR75
 */
#define VTSS_GIC400_GICD_IPRIORITYR75        VTSS_IOREG(VTSS_TO_GIC400,0x54b)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR75 . GICD_IPRIORITYR75
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR75_GICD_IPRIORITYR75(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR75_GICD_IPRIORITYR75     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR75_GICD_IPRIORITYR75(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR76
 */
#define VTSS_GIC400_GICD_IPRIORITYR76        VTSS_IOREG(VTSS_TO_GIC400,0x54c)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR76 . GICD_IPRIORITYR76
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR76_GICD_IPRIORITYR76(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR76_GICD_IPRIORITYR76     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR76_GICD_IPRIORITYR76(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR77
 */
#define VTSS_GIC400_GICD_IPRIORITYR77        VTSS_IOREG(VTSS_TO_GIC400,0x54d)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR77 . GICD_IPRIORITYR77
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR77_GICD_IPRIORITYR77(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR77_GICD_IPRIORITYR77     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR77_GICD_IPRIORITYR77(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR78
 */
#define VTSS_GIC400_GICD_IPRIORITYR78        VTSS_IOREG(VTSS_TO_GIC400,0x54e)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR78 . GICD_IPRIORITYR78
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR78_GICD_IPRIORITYR78(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR78_GICD_IPRIORITYR78     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR78_GICD_IPRIORITYR78(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR79
 */
#define VTSS_GIC400_GICD_IPRIORITYR79        VTSS_IOREG(VTSS_TO_GIC400,0x54f)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR79 . GICD_IPRIORITYR79
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR79_GICD_IPRIORITYR79(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR79_GICD_IPRIORITYR79     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR79_GICD_IPRIORITYR79(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR80
 */
#define VTSS_GIC400_GICD_IPRIORITYR80        VTSS_IOREG(VTSS_TO_GIC400,0x550)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR80 . GICD_IPRIORITYR80
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR80_GICD_IPRIORITYR80(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR80_GICD_IPRIORITYR80     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR80_GICD_IPRIORITYR80(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR81
 */
#define VTSS_GIC400_GICD_IPRIORITYR81        VTSS_IOREG(VTSS_TO_GIC400,0x551)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR81 . GICD_IPRIORITYR81
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR81_GICD_IPRIORITYR81(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR81_GICD_IPRIORITYR81     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR81_GICD_IPRIORITYR81(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR82
 */
#define VTSS_GIC400_GICD_IPRIORITYR82        VTSS_IOREG(VTSS_TO_GIC400,0x552)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR82 . GICD_IPRIORITYR82
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR82_GICD_IPRIORITYR82(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR82_GICD_IPRIORITYR82     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR82_GICD_IPRIORITYR82(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR83
 */
#define VTSS_GIC400_GICD_IPRIORITYR83        VTSS_IOREG(VTSS_TO_GIC400,0x553)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR83 . GICD_IPRIORITYR83
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR83_GICD_IPRIORITYR83(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR83_GICD_IPRIORITYR83     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR83_GICD_IPRIORITYR83(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR84
 */
#define VTSS_GIC400_GICD_IPRIORITYR84        VTSS_IOREG(VTSS_TO_GIC400,0x554)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR84 . GICD_IPRIORITYR84
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR84_GICD_IPRIORITYR84(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR84_GICD_IPRIORITYR84     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR84_GICD_IPRIORITYR84(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR85
 */
#define VTSS_GIC400_GICD_IPRIORITYR85        VTSS_IOREG(VTSS_TO_GIC400,0x555)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR85 . GICD_IPRIORITYR85
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR85_GICD_IPRIORITYR85(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR85_GICD_IPRIORITYR85     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR85_GICD_IPRIORITYR85(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR86
 */
#define VTSS_GIC400_GICD_IPRIORITYR86        VTSS_IOREG(VTSS_TO_GIC400,0x556)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR86 . GICD_IPRIORITYR86
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR86_GICD_IPRIORITYR86(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR86_GICD_IPRIORITYR86     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR86_GICD_IPRIORITYR86(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR87
 */
#define VTSS_GIC400_GICD_IPRIORITYR87        VTSS_IOREG(VTSS_TO_GIC400,0x557)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR87 . GICD_IPRIORITYR87
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR87_GICD_IPRIORITYR87(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR87_GICD_IPRIORITYR87     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR87_GICD_IPRIORITYR87(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR88
 */
#define VTSS_GIC400_GICD_IPRIORITYR88        VTSS_IOREG(VTSS_TO_GIC400,0x558)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR88 . GICD_IPRIORITYR88
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR88_GICD_IPRIORITYR88(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR88_GICD_IPRIORITYR88     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR88_GICD_IPRIORITYR88(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR89
 */
#define VTSS_GIC400_GICD_IPRIORITYR89        VTSS_IOREG(VTSS_TO_GIC400,0x559)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR89 . GICD_IPRIORITYR89
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR89_GICD_IPRIORITYR89(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR89_GICD_IPRIORITYR89     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR89_GICD_IPRIORITYR89(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR90
 */
#define VTSS_GIC400_GICD_IPRIORITYR90        VTSS_IOREG(VTSS_TO_GIC400,0x55a)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR90 . GICD_IPRIORITYR90
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR90_GICD_IPRIORITYR90(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR90_GICD_IPRIORITYR90     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR90_GICD_IPRIORITYR90(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR91
 */
#define VTSS_GIC400_GICD_IPRIORITYR91        VTSS_IOREG(VTSS_TO_GIC400,0x55b)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR91 . GICD_IPRIORITYR91
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR91_GICD_IPRIORITYR91(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR91_GICD_IPRIORITYR91     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR91_GICD_IPRIORITYR91(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR92
 */
#define VTSS_GIC400_GICD_IPRIORITYR92        VTSS_IOREG(VTSS_TO_GIC400,0x55c)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR92 . GICD_IPRIORITYR92
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR92_GICD_IPRIORITYR92(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR92_GICD_IPRIORITYR92     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR92_GICD_IPRIORITYR92(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR93
 */
#define VTSS_GIC400_GICD_IPRIORITYR93        VTSS_IOREG(VTSS_TO_GIC400,0x55d)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR93 . GICD_IPRIORITYR93
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR93_GICD_IPRIORITYR93(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR93_GICD_IPRIORITYR93     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR93_GICD_IPRIORITYR93(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR94
 */
#define VTSS_GIC400_GICD_IPRIORITYR94        VTSS_IOREG(VTSS_TO_GIC400,0x55e)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR94 . GICD_IPRIORITYR94
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR94_GICD_IPRIORITYR94(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR94_GICD_IPRIORITYR94     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR94_GICD_IPRIORITYR94(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR95
 */
#define VTSS_GIC400_GICD_IPRIORITYR95        VTSS_IOREG(VTSS_TO_GIC400,0x55f)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR95 . GICD_IPRIORITYR95
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR95_GICD_IPRIORITYR95(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR95_GICD_IPRIORITYR95     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR95_GICD_IPRIORITYR95(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR96
 */
#define VTSS_GIC400_GICD_IPRIORITYR96        VTSS_IOREG(VTSS_TO_GIC400,0x560)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR96 . GICD_IPRIORITYR96
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR96_GICD_IPRIORITYR96(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR96_GICD_IPRIORITYR96     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR96_GICD_IPRIORITYR96(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR97
 */
#define VTSS_GIC400_GICD_IPRIORITYR97        VTSS_IOREG(VTSS_TO_GIC400,0x561)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR97 . GICD_IPRIORITYR97
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR97_GICD_IPRIORITYR97(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR97_GICD_IPRIORITYR97     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR97_GICD_IPRIORITYR97(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR98
 */
#define VTSS_GIC400_GICD_IPRIORITYR98        VTSS_IOREG(VTSS_TO_GIC400,0x562)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR98 . GICD_IPRIORITYR98
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR98_GICD_IPRIORITYR98(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR98_GICD_IPRIORITYR98     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR98_GICD_IPRIORITYR98(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR99
 */
#define VTSS_GIC400_GICD_IPRIORITYR99        VTSS_IOREG(VTSS_TO_GIC400,0x563)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR99 . GICD_IPRIORITYR99
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR99_GICD_IPRIORITYR99(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR99_GICD_IPRIORITYR99     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR99_GICD_IPRIORITYR99(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR100
 */
#define VTSS_GIC400_GICD_IPRIORITYR100       VTSS_IOREG(VTSS_TO_GIC400,0x564)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR100 . GICD_IPRIORITYR100
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR100_GICD_IPRIORITYR100(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR100_GICD_IPRIORITYR100     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR100_GICD_IPRIORITYR100(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR101
 */
#define VTSS_GIC400_GICD_IPRIORITYR101       VTSS_IOREG(VTSS_TO_GIC400,0x565)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR101 . GICD_IPRIORITYR101
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR101_GICD_IPRIORITYR101(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR101_GICD_IPRIORITYR101     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR101_GICD_IPRIORITYR101(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR102
 */
#define VTSS_GIC400_GICD_IPRIORITYR102       VTSS_IOREG(VTSS_TO_GIC400,0x566)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR102 . GICD_IPRIORITYR102
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR102_GICD_IPRIORITYR102(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR102_GICD_IPRIORITYR102     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR102_GICD_IPRIORITYR102(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR103
 */
#define VTSS_GIC400_GICD_IPRIORITYR103       VTSS_IOREG(VTSS_TO_GIC400,0x567)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR103 . GICD_IPRIORITYR103
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR103_GICD_IPRIORITYR103(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR103_GICD_IPRIORITYR103     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR103_GICD_IPRIORITYR103(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR104
 */
#define VTSS_GIC400_GICD_IPRIORITYR104       VTSS_IOREG(VTSS_TO_GIC400,0x568)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR104 . GICD_IPRIORITYR104
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR104_GICD_IPRIORITYR104(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR104_GICD_IPRIORITYR104     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR104_GICD_IPRIORITYR104(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR105
 */
#define VTSS_GIC400_GICD_IPRIORITYR105       VTSS_IOREG(VTSS_TO_GIC400,0x569)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR105 . GICD_IPRIORITYR105
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR105_GICD_IPRIORITYR105(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR105_GICD_IPRIORITYR105     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR105_GICD_IPRIORITYR105(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR106
 */
#define VTSS_GIC400_GICD_IPRIORITYR106       VTSS_IOREG(VTSS_TO_GIC400,0x56a)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR106 . GICD_IPRIORITYR106
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR106_GICD_IPRIORITYR106(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR106_GICD_IPRIORITYR106     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR106_GICD_IPRIORITYR106(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR107
 */
#define VTSS_GIC400_GICD_IPRIORITYR107       VTSS_IOREG(VTSS_TO_GIC400,0x56b)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR107 . GICD_IPRIORITYR107
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR107_GICD_IPRIORITYR107(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR107_GICD_IPRIORITYR107     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR107_GICD_IPRIORITYR107(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR108
 */
#define VTSS_GIC400_GICD_IPRIORITYR108       VTSS_IOREG(VTSS_TO_GIC400,0x56c)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR108 . GICD_IPRIORITYR108
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR108_GICD_IPRIORITYR108(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR108_GICD_IPRIORITYR108     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR108_GICD_IPRIORITYR108(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR109
 */
#define VTSS_GIC400_GICD_IPRIORITYR109       VTSS_IOREG(VTSS_TO_GIC400,0x56d)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR109 . GICD_IPRIORITYR109
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR109_GICD_IPRIORITYR109(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR109_GICD_IPRIORITYR109     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR109_GICD_IPRIORITYR109(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR110
 */
#define VTSS_GIC400_GICD_IPRIORITYR110       VTSS_IOREG(VTSS_TO_GIC400,0x56e)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR110 . GICD_IPRIORITYR110
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR110_GICD_IPRIORITYR110(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR110_GICD_IPRIORITYR110     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR110_GICD_IPRIORITYR110(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR111
 */
#define VTSS_GIC400_GICD_IPRIORITYR111       VTSS_IOREG(VTSS_TO_GIC400,0x56f)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR111 . GICD_IPRIORITYR111
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR111_GICD_IPRIORITYR111(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR111_GICD_IPRIORITYR111     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR111_GICD_IPRIORITYR111(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR112
 */
#define VTSS_GIC400_GICD_IPRIORITYR112       VTSS_IOREG(VTSS_TO_GIC400,0x570)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR112 . GICD_IPRIORITYR112
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR112_GICD_IPRIORITYR112(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR112_GICD_IPRIORITYR112     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR112_GICD_IPRIORITYR112(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR113
 */
#define VTSS_GIC400_GICD_IPRIORITYR113       VTSS_IOREG(VTSS_TO_GIC400,0x571)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR113 . GICD_IPRIORITYR113
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR113_GICD_IPRIORITYR113(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR113_GICD_IPRIORITYR113     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR113_GICD_IPRIORITYR113(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR114
 */
#define VTSS_GIC400_GICD_IPRIORITYR114       VTSS_IOREG(VTSS_TO_GIC400,0x572)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR114 . GICD_IPRIORITYR114
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR114_GICD_IPRIORITYR114(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR114_GICD_IPRIORITYR114     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR114_GICD_IPRIORITYR114(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR115
 */
#define VTSS_GIC400_GICD_IPRIORITYR115       VTSS_IOREG(VTSS_TO_GIC400,0x573)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR115 . GICD_IPRIORITYR115
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR115_GICD_IPRIORITYR115(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR115_GICD_IPRIORITYR115     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR115_GICD_IPRIORITYR115(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR116
 */
#define VTSS_GIC400_GICD_IPRIORITYR116       VTSS_IOREG(VTSS_TO_GIC400,0x574)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR116 . GICD_IPRIORITYR116
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR116_GICD_IPRIORITYR116(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR116_GICD_IPRIORITYR116     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR116_GICD_IPRIORITYR116(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR117
 */
#define VTSS_GIC400_GICD_IPRIORITYR117       VTSS_IOREG(VTSS_TO_GIC400,0x575)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR117 . GICD_IPRIORITYR117
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR117_GICD_IPRIORITYR117(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR117_GICD_IPRIORITYR117     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR117_GICD_IPRIORITYR117(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR118
 */
#define VTSS_GIC400_GICD_IPRIORITYR118       VTSS_IOREG(VTSS_TO_GIC400,0x576)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR118 . GICD_IPRIORITYR118
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR118_GICD_IPRIORITYR118(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR118_GICD_IPRIORITYR118     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR118_GICD_IPRIORITYR118(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR119
 */
#define VTSS_GIC400_GICD_IPRIORITYR119       VTSS_IOREG(VTSS_TO_GIC400,0x577)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR119 . GICD_IPRIORITYR119
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR119_GICD_IPRIORITYR119(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR119_GICD_IPRIORITYR119     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR119_GICD_IPRIORITYR119(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR120
 */
#define VTSS_GIC400_GICD_IPRIORITYR120       VTSS_IOREG(VTSS_TO_GIC400,0x578)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR120 . GICD_IPRIORITYR120
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR120_GICD_IPRIORITYR120(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR120_GICD_IPRIORITYR120     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR120_GICD_IPRIORITYR120(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR121
 */
#define VTSS_GIC400_GICD_IPRIORITYR121       VTSS_IOREG(VTSS_TO_GIC400,0x579)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR121 . GICD_IPRIORITYR121
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR121_GICD_IPRIORITYR121(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR121_GICD_IPRIORITYR121     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR121_GICD_IPRIORITYR121(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR122
 */
#define VTSS_GIC400_GICD_IPRIORITYR122       VTSS_IOREG(VTSS_TO_GIC400,0x57a)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR122 . GICD_IPRIORITYR122
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR122_GICD_IPRIORITYR122(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR122_GICD_IPRIORITYR122     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR122_GICD_IPRIORITYR122(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR123
 */
#define VTSS_GIC400_GICD_IPRIORITYR123       VTSS_IOREG(VTSS_TO_GIC400,0x57b)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR123 . GICD_IPRIORITYR123
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR123_GICD_IPRIORITYR123(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR123_GICD_IPRIORITYR123     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR123_GICD_IPRIORITYR123(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR124
 */
#define VTSS_GIC400_GICD_IPRIORITYR124       VTSS_IOREG(VTSS_TO_GIC400,0x57c)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR124 . GICD_IPRIORITYR124
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR124_GICD_IPRIORITYR124(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR124_GICD_IPRIORITYR124     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR124_GICD_IPRIORITYR124(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR125
 */
#define VTSS_GIC400_GICD_IPRIORITYR125       VTSS_IOREG(VTSS_TO_GIC400,0x57d)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR125 . GICD_IPRIORITYR125
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR125_GICD_IPRIORITYR125(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR125_GICD_IPRIORITYR125     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR125_GICD_IPRIORITYR125(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR126
 */
#define VTSS_GIC400_GICD_IPRIORITYR126       VTSS_IOREG(VTSS_TO_GIC400,0x57e)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR126 . GICD_IPRIORITYR126
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR126_GICD_IPRIORITYR126(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR126_GICD_IPRIORITYR126     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR126_GICD_IPRIORITYR126(x)  (x)


/**
 * \brief Interrupt Priority Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_IPRIORITYR127
 */
#define VTSS_GIC400_GICD_IPRIORITYR127       VTSS_IOREG(VTSS_TO_GIC400,0x57f)

/**
 * \brief
 * Interrupt Priority Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_IPRIORITYR127 . GICD_IPRIORITYR127
 */
#define  VTSS_F_GIC400_GICD_IPRIORITYR127_GICD_IPRIORITYR127(x)  (x)
#define  VTSS_M_GIC400_GICD_IPRIORITYR127_GICD_IPRIORITYR127     0xffffffff
#define  VTSS_X_GIC400_GICD_IPRIORITYR127_GICD_IPRIORITYR127(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR0
 */
#define VTSS_GIC400_GICD_ITARGETSR0          VTSS_IOREG(VTSS_TO_GIC400,0x600)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR0 . GICD_ITARGETSR0
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR0_GICD_ITARGETSR0(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR0_GICD_ITARGETSR0     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR0_GICD_ITARGETSR0(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR1
 */
#define VTSS_GIC400_GICD_ITARGETSR1          VTSS_IOREG(VTSS_TO_GIC400,0x601)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR1 . GICD_ITARGETSR1
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR1_GICD_ITARGETSR1(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR1_GICD_ITARGETSR1     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR1_GICD_ITARGETSR1(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR2
 */
#define VTSS_GIC400_GICD_ITARGETSR2          VTSS_IOREG(VTSS_TO_GIC400,0x602)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR2 . GICD_ITARGETSR2
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR2_GICD_ITARGETSR2(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR2_GICD_ITARGETSR2     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR2_GICD_ITARGETSR2(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR3
 */
#define VTSS_GIC400_GICD_ITARGETSR3          VTSS_IOREG(VTSS_TO_GIC400,0x603)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR3 . GICD_ITARGETSR3
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR3_GICD_ITARGETSR3(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR3_GICD_ITARGETSR3     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR3_GICD_ITARGETSR3(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR4
 */
#define VTSS_GIC400_GICD_ITARGETSR4          VTSS_IOREG(VTSS_TO_GIC400,0x604)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR4 . GICD_ITARGETSR4
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR4_GICD_ITARGETSR4(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR4_GICD_ITARGETSR4     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR4_GICD_ITARGETSR4(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR5
 */
#define VTSS_GIC400_GICD_ITARGETSR5          VTSS_IOREG(VTSS_TO_GIC400,0x605)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR5 . GICD_ITARGETSR5
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR5_GICD_ITARGETSR5(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR5_GICD_ITARGETSR5     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR5_GICD_ITARGETSR5(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR6
 */
#define VTSS_GIC400_GICD_ITARGETSR6          VTSS_IOREG(VTSS_TO_GIC400,0x606)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR6 . GICD_ITARGETSR6
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR6_GICD_ITARGETSR6(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR6_GICD_ITARGETSR6     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR6_GICD_ITARGETSR6(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR7
 */
#define VTSS_GIC400_GICD_ITARGETSR7          VTSS_IOREG(VTSS_TO_GIC400,0x607)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR7 . GICD_ITARGETSR7
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR7_GICD_ITARGETSR7(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR7_GICD_ITARGETSR7     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR7_GICD_ITARGETSR7(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR8
 */
#define VTSS_GIC400_GICD_ITARGETSR8          VTSS_IOREG(VTSS_TO_GIC400,0x608)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR8 . GICD_ITARGETSR8
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR8_GICD_ITARGETSR8(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR8_GICD_ITARGETSR8     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR8_GICD_ITARGETSR8(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR9
 */
#define VTSS_GIC400_GICD_ITARGETSR9          VTSS_IOREG(VTSS_TO_GIC400,0x609)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR9 . GICD_ITARGETSR9
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR9_GICD_ITARGETSR9(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR9_GICD_ITARGETSR9     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR9_GICD_ITARGETSR9(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR10
 */
#define VTSS_GIC400_GICD_ITARGETSR10         VTSS_IOREG(VTSS_TO_GIC400,0x60a)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR10 . GICD_ITARGETSR10
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR10_GICD_ITARGETSR10(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR10_GICD_ITARGETSR10     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR10_GICD_ITARGETSR10(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR11
 */
#define VTSS_GIC400_GICD_ITARGETSR11         VTSS_IOREG(VTSS_TO_GIC400,0x60b)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR11 . GICD_ITARGETSR11
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR11_GICD_ITARGETSR11(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR11_GICD_ITARGETSR11     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR11_GICD_ITARGETSR11(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR12
 */
#define VTSS_GIC400_GICD_ITARGETSR12         VTSS_IOREG(VTSS_TO_GIC400,0x60c)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR12 . GICD_ITARGETSR12
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR12_GICD_ITARGETSR12(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR12_GICD_ITARGETSR12     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR12_GICD_ITARGETSR12(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR13
 */
#define VTSS_GIC400_GICD_ITARGETSR13         VTSS_IOREG(VTSS_TO_GIC400,0x60d)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR13 . GICD_ITARGETSR13
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR13_GICD_ITARGETSR13(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR13_GICD_ITARGETSR13     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR13_GICD_ITARGETSR13(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR14
 */
#define VTSS_GIC400_GICD_ITARGETSR14         VTSS_IOREG(VTSS_TO_GIC400,0x60e)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR14 . GICD_ITARGETSR14
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR14_GICD_ITARGETSR14(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR14_GICD_ITARGETSR14     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR14_GICD_ITARGETSR14(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR15
 */
#define VTSS_GIC400_GICD_ITARGETSR15         VTSS_IOREG(VTSS_TO_GIC400,0x60f)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR15 . GICD_ITARGETSR15
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR15_GICD_ITARGETSR15(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR15_GICD_ITARGETSR15     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR15_GICD_ITARGETSR15(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR16
 */
#define VTSS_GIC400_GICD_ITARGETSR16         VTSS_IOREG(VTSS_TO_GIC400,0x610)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR16 . GICD_ITARGETSR16
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR16_GICD_ITARGETSR16(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR16_GICD_ITARGETSR16     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR16_GICD_ITARGETSR16(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR17
 */
#define VTSS_GIC400_GICD_ITARGETSR17         VTSS_IOREG(VTSS_TO_GIC400,0x611)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR17 . GICD_ITARGETSR17
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR17_GICD_ITARGETSR17(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR17_GICD_ITARGETSR17     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR17_GICD_ITARGETSR17(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR18
 */
#define VTSS_GIC400_GICD_ITARGETSR18         VTSS_IOREG(VTSS_TO_GIC400,0x612)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR18 . GICD_ITARGETSR18
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR18_GICD_ITARGETSR18(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR18_GICD_ITARGETSR18     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR18_GICD_ITARGETSR18(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR19
 */
#define VTSS_GIC400_GICD_ITARGETSR19         VTSS_IOREG(VTSS_TO_GIC400,0x613)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR19 . GICD_ITARGETSR19
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR19_GICD_ITARGETSR19(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR19_GICD_ITARGETSR19     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR19_GICD_ITARGETSR19(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR20
 */
#define VTSS_GIC400_GICD_ITARGETSR20         VTSS_IOREG(VTSS_TO_GIC400,0x614)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR20 . GICD_ITARGETSR20
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR20_GICD_ITARGETSR20(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR20_GICD_ITARGETSR20     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR20_GICD_ITARGETSR20(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR21
 */
#define VTSS_GIC400_GICD_ITARGETSR21         VTSS_IOREG(VTSS_TO_GIC400,0x615)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR21 . GICD_ITARGETSR21
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR21_GICD_ITARGETSR21(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR21_GICD_ITARGETSR21     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR21_GICD_ITARGETSR21(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR22
 */
#define VTSS_GIC400_GICD_ITARGETSR22         VTSS_IOREG(VTSS_TO_GIC400,0x616)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR22 . GICD_ITARGETSR22
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR22_GICD_ITARGETSR22(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR22_GICD_ITARGETSR22     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR22_GICD_ITARGETSR22(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR23
 */
#define VTSS_GIC400_GICD_ITARGETSR23         VTSS_IOREG(VTSS_TO_GIC400,0x617)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR23 . GICD_ITARGETSR23
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR23_GICD_ITARGETSR23(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR23_GICD_ITARGETSR23     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR23_GICD_ITARGETSR23(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR24
 */
#define VTSS_GIC400_GICD_ITARGETSR24         VTSS_IOREG(VTSS_TO_GIC400,0x618)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR24 . GICD_ITARGETSR24
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR24_GICD_ITARGETSR24(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR24_GICD_ITARGETSR24     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR24_GICD_ITARGETSR24(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR25
 */
#define VTSS_GIC400_GICD_ITARGETSR25         VTSS_IOREG(VTSS_TO_GIC400,0x619)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR25 . GICD_ITARGETSR25
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR25_GICD_ITARGETSR25(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR25_GICD_ITARGETSR25     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR25_GICD_ITARGETSR25(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR26
 */
#define VTSS_GIC400_GICD_ITARGETSR26         VTSS_IOREG(VTSS_TO_GIC400,0x61a)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR26 . GICD_ITARGETSR26
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR26_GICD_ITARGETSR26(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR26_GICD_ITARGETSR26     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR26_GICD_ITARGETSR26(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR27
 */
#define VTSS_GIC400_GICD_ITARGETSR27         VTSS_IOREG(VTSS_TO_GIC400,0x61b)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR27 . GICD_ITARGETSR27
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR27_GICD_ITARGETSR27(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR27_GICD_ITARGETSR27     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR27_GICD_ITARGETSR27(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR28
 */
#define VTSS_GIC400_GICD_ITARGETSR28         VTSS_IOREG(VTSS_TO_GIC400,0x61c)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR28 . GICD_ITARGETSR28
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR28_GICD_ITARGETSR28(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR28_GICD_ITARGETSR28     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR28_GICD_ITARGETSR28(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR29
 */
#define VTSS_GIC400_GICD_ITARGETSR29         VTSS_IOREG(VTSS_TO_GIC400,0x61d)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR29 . GICD_ITARGETSR29
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR29_GICD_ITARGETSR29(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR29_GICD_ITARGETSR29     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR29_GICD_ITARGETSR29(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR30
 */
#define VTSS_GIC400_GICD_ITARGETSR30         VTSS_IOREG(VTSS_TO_GIC400,0x61e)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR30 . GICD_ITARGETSR30
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR30_GICD_ITARGETSR30(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR30_GICD_ITARGETSR30     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR30_GICD_ITARGETSR30(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR31
 */
#define VTSS_GIC400_GICD_ITARGETSR31         VTSS_IOREG(VTSS_TO_GIC400,0x61f)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR31 . GICD_ITARGETSR31
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR31_GICD_ITARGETSR31(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR31_GICD_ITARGETSR31     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR31_GICD_ITARGETSR31(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR32
 */
#define VTSS_GIC400_GICD_ITARGETSR32         VTSS_IOREG(VTSS_TO_GIC400,0x620)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR32 . GICD_ITARGETSR32
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR32_GICD_ITARGETSR32(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR32_GICD_ITARGETSR32     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR32_GICD_ITARGETSR32(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR33
 */
#define VTSS_GIC400_GICD_ITARGETSR33         VTSS_IOREG(VTSS_TO_GIC400,0x621)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR33 . GICD_ITARGETSR33
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR33_GICD_ITARGETSR33(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR33_GICD_ITARGETSR33     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR33_GICD_ITARGETSR33(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR34
 */
#define VTSS_GIC400_GICD_ITARGETSR34         VTSS_IOREG(VTSS_TO_GIC400,0x622)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR34 . GICD_ITARGETSR34
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR34_GICD_ITARGETSR34(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR34_GICD_ITARGETSR34     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR34_GICD_ITARGETSR34(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR35
 */
#define VTSS_GIC400_GICD_ITARGETSR35         VTSS_IOREG(VTSS_TO_GIC400,0x623)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR35 . GICD_ITARGETSR35
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR35_GICD_ITARGETSR35(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR35_GICD_ITARGETSR35     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR35_GICD_ITARGETSR35(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR36
 */
#define VTSS_GIC400_GICD_ITARGETSR36         VTSS_IOREG(VTSS_TO_GIC400,0x624)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR36 . GICD_ITARGETSR36
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR36_GICD_ITARGETSR36(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR36_GICD_ITARGETSR36     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR36_GICD_ITARGETSR36(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR37
 */
#define VTSS_GIC400_GICD_ITARGETSR37         VTSS_IOREG(VTSS_TO_GIC400,0x625)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR37 . GICD_ITARGETSR37
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR37_GICD_ITARGETSR37(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR37_GICD_ITARGETSR37     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR37_GICD_ITARGETSR37(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR38
 */
#define VTSS_GIC400_GICD_ITARGETSR38         VTSS_IOREG(VTSS_TO_GIC400,0x626)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR38 . GICD_ITARGETSR38
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR38_GICD_ITARGETSR38(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR38_GICD_ITARGETSR38     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR38_GICD_ITARGETSR38(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR39
 */
#define VTSS_GIC400_GICD_ITARGETSR39         VTSS_IOREG(VTSS_TO_GIC400,0x627)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR39 . GICD_ITARGETSR39
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR39_GICD_ITARGETSR39(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR39_GICD_ITARGETSR39     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR39_GICD_ITARGETSR39(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR40
 */
#define VTSS_GIC400_GICD_ITARGETSR40         VTSS_IOREG(VTSS_TO_GIC400,0x628)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR40 . GICD_ITARGETSR40
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR40_GICD_ITARGETSR40(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR40_GICD_ITARGETSR40     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR40_GICD_ITARGETSR40(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR41
 */
#define VTSS_GIC400_GICD_ITARGETSR41         VTSS_IOREG(VTSS_TO_GIC400,0x629)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR41 . GICD_ITARGETSR41
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR41_GICD_ITARGETSR41(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR41_GICD_ITARGETSR41     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR41_GICD_ITARGETSR41(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR42
 */
#define VTSS_GIC400_GICD_ITARGETSR42         VTSS_IOREG(VTSS_TO_GIC400,0x62a)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR42 . GICD_ITARGETSR42
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR42_GICD_ITARGETSR42(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR42_GICD_ITARGETSR42     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR42_GICD_ITARGETSR42(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR43
 */
#define VTSS_GIC400_GICD_ITARGETSR43         VTSS_IOREG(VTSS_TO_GIC400,0x62b)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR43 . GICD_ITARGETSR43
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR43_GICD_ITARGETSR43(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR43_GICD_ITARGETSR43     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR43_GICD_ITARGETSR43(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR44
 */
#define VTSS_GIC400_GICD_ITARGETSR44         VTSS_IOREG(VTSS_TO_GIC400,0x62c)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR44 . GICD_ITARGETSR44
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR44_GICD_ITARGETSR44(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR44_GICD_ITARGETSR44     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR44_GICD_ITARGETSR44(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR45
 */
#define VTSS_GIC400_GICD_ITARGETSR45         VTSS_IOREG(VTSS_TO_GIC400,0x62d)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR45 . GICD_ITARGETSR45
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR45_GICD_ITARGETSR45(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR45_GICD_ITARGETSR45     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR45_GICD_ITARGETSR45(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR46
 */
#define VTSS_GIC400_GICD_ITARGETSR46         VTSS_IOREG(VTSS_TO_GIC400,0x62e)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR46 . GICD_ITARGETSR46
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR46_GICD_ITARGETSR46(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR46_GICD_ITARGETSR46     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR46_GICD_ITARGETSR46(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR47
 */
#define VTSS_GIC400_GICD_ITARGETSR47         VTSS_IOREG(VTSS_TO_GIC400,0x62f)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR47 . GICD_ITARGETSR47
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR47_GICD_ITARGETSR47(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR47_GICD_ITARGETSR47     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR47_GICD_ITARGETSR47(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR48
 */
#define VTSS_GIC400_GICD_ITARGETSR48         VTSS_IOREG(VTSS_TO_GIC400,0x630)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR48 . GICD_ITARGETSR48
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR48_GICD_ITARGETSR48(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR48_GICD_ITARGETSR48     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR48_GICD_ITARGETSR48(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR49
 */
#define VTSS_GIC400_GICD_ITARGETSR49         VTSS_IOREG(VTSS_TO_GIC400,0x631)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR49 . GICD_ITARGETSR49
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR49_GICD_ITARGETSR49(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR49_GICD_ITARGETSR49     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR49_GICD_ITARGETSR49(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR50
 */
#define VTSS_GIC400_GICD_ITARGETSR50         VTSS_IOREG(VTSS_TO_GIC400,0x632)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR50 . GICD_ITARGETSR50
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR50_GICD_ITARGETSR50(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR50_GICD_ITARGETSR50     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR50_GICD_ITARGETSR50(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR51
 */
#define VTSS_GIC400_GICD_ITARGETSR51         VTSS_IOREG(VTSS_TO_GIC400,0x633)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR51 . GICD_ITARGETSR51
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR51_GICD_ITARGETSR51(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR51_GICD_ITARGETSR51     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR51_GICD_ITARGETSR51(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR52
 */
#define VTSS_GIC400_GICD_ITARGETSR52         VTSS_IOREG(VTSS_TO_GIC400,0x634)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR52 . GICD_ITARGETSR52
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR52_GICD_ITARGETSR52(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR52_GICD_ITARGETSR52     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR52_GICD_ITARGETSR52(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR53
 */
#define VTSS_GIC400_GICD_ITARGETSR53         VTSS_IOREG(VTSS_TO_GIC400,0x635)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR53 . GICD_ITARGETSR53
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR53_GICD_ITARGETSR53(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR53_GICD_ITARGETSR53     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR53_GICD_ITARGETSR53(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR54
 */
#define VTSS_GIC400_GICD_ITARGETSR54         VTSS_IOREG(VTSS_TO_GIC400,0x636)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR54 . GICD_ITARGETSR54
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR54_GICD_ITARGETSR54(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR54_GICD_ITARGETSR54     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR54_GICD_ITARGETSR54(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR55
 */
#define VTSS_GIC400_GICD_ITARGETSR55         VTSS_IOREG(VTSS_TO_GIC400,0x637)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR55 . GICD_ITARGETSR55
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR55_GICD_ITARGETSR55(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR55_GICD_ITARGETSR55     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR55_GICD_ITARGETSR55(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR56
 */
#define VTSS_GIC400_GICD_ITARGETSR56         VTSS_IOREG(VTSS_TO_GIC400,0x638)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR56 . GICD_ITARGETSR56
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR56_GICD_ITARGETSR56(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR56_GICD_ITARGETSR56     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR56_GICD_ITARGETSR56(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR57
 */
#define VTSS_GIC400_GICD_ITARGETSR57         VTSS_IOREG(VTSS_TO_GIC400,0x639)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR57 . GICD_ITARGETSR57
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR57_GICD_ITARGETSR57(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR57_GICD_ITARGETSR57     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR57_GICD_ITARGETSR57(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR58
 */
#define VTSS_GIC400_GICD_ITARGETSR58         VTSS_IOREG(VTSS_TO_GIC400,0x63a)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR58 . GICD_ITARGETSR58
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR58_GICD_ITARGETSR58(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR58_GICD_ITARGETSR58     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR58_GICD_ITARGETSR58(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR59
 */
#define VTSS_GIC400_GICD_ITARGETSR59         VTSS_IOREG(VTSS_TO_GIC400,0x63b)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR59 . GICD_ITARGETSR59
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR59_GICD_ITARGETSR59(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR59_GICD_ITARGETSR59     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR59_GICD_ITARGETSR59(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR60
 */
#define VTSS_GIC400_GICD_ITARGETSR60         VTSS_IOREG(VTSS_TO_GIC400,0x63c)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR60 . GICD_ITARGETSR60
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR60_GICD_ITARGETSR60(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR60_GICD_ITARGETSR60     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR60_GICD_ITARGETSR60(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR61
 */
#define VTSS_GIC400_GICD_ITARGETSR61         VTSS_IOREG(VTSS_TO_GIC400,0x63d)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR61 . GICD_ITARGETSR61
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR61_GICD_ITARGETSR61(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR61_GICD_ITARGETSR61     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR61_GICD_ITARGETSR61(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR62
 */
#define VTSS_GIC400_GICD_ITARGETSR62         VTSS_IOREG(VTSS_TO_GIC400,0x63e)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR62 . GICD_ITARGETSR62
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR62_GICD_ITARGETSR62(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR62_GICD_ITARGETSR62     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR62_GICD_ITARGETSR62(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR63
 */
#define VTSS_GIC400_GICD_ITARGETSR63         VTSS_IOREG(VTSS_TO_GIC400,0x63f)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR63 . GICD_ITARGETSR63
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR63_GICD_ITARGETSR63(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR63_GICD_ITARGETSR63     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR63_GICD_ITARGETSR63(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR64
 */
#define VTSS_GIC400_GICD_ITARGETSR64         VTSS_IOREG(VTSS_TO_GIC400,0x640)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR64 . GICD_ITARGETSR64
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR64_GICD_ITARGETSR64(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR64_GICD_ITARGETSR64     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR64_GICD_ITARGETSR64(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR65
 */
#define VTSS_GIC400_GICD_ITARGETSR65         VTSS_IOREG(VTSS_TO_GIC400,0x641)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR65 . GICD_ITARGETSR65
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR65_GICD_ITARGETSR65(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR65_GICD_ITARGETSR65     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR65_GICD_ITARGETSR65(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR66
 */
#define VTSS_GIC400_GICD_ITARGETSR66         VTSS_IOREG(VTSS_TO_GIC400,0x642)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR66 . GICD_ITARGETSR66
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR66_GICD_ITARGETSR66(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR66_GICD_ITARGETSR66     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR66_GICD_ITARGETSR66(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR67
 */
#define VTSS_GIC400_GICD_ITARGETSR67         VTSS_IOREG(VTSS_TO_GIC400,0x643)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR67 . GICD_ITARGETSR67
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR67_GICD_ITARGETSR67(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR67_GICD_ITARGETSR67     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR67_GICD_ITARGETSR67(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR68
 */
#define VTSS_GIC400_GICD_ITARGETSR68         VTSS_IOREG(VTSS_TO_GIC400,0x644)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR68 . GICD_ITARGETSR68
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR68_GICD_ITARGETSR68(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR68_GICD_ITARGETSR68     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR68_GICD_ITARGETSR68(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR69
 */
#define VTSS_GIC400_GICD_ITARGETSR69         VTSS_IOREG(VTSS_TO_GIC400,0x645)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR69 . GICD_ITARGETSR69
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR69_GICD_ITARGETSR69(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR69_GICD_ITARGETSR69     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR69_GICD_ITARGETSR69(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR70
 */
#define VTSS_GIC400_GICD_ITARGETSR70         VTSS_IOREG(VTSS_TO_GIC400,0x646)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR70 . GICD_ITARGETSR70
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR70_GICD_ITARGETSR70(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR70_GICD_ITARGETSR70     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR70_GICD_ITARGETSR70(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR71
 */
#define VTSS_GIC400_GICD_ITARGETSR71         VTSS_IOREG(VTSS_TO_GIC400,0x647)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR71 . GICD_ITARGETSR71
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR71_GICD_ITARGETSR71(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR71_GICD_ITARGETSR71     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR71_GICD_ITARGETSR71(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR72
 */
#define VTSS_GIC400_GICD_ITARGETSR72         VTSS_IOREG(VTSS_TO_GIC400,0x648)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR72 . GICD_ITARGETSR72
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR72_GICD_ITARGETSR72(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR72_GICD_ITARGETSR72     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR72_GICD_ITARGETSR72(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR73
 */
#define VTSS_GIC400_GICD_ITARGETSR73         VTSS_IOREG(VTSS_TO_GIC400,0x649)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR73 . GICD_ITARGETSR73
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR73_GICD_ITARGETSR73(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR73_GICD_ITARGETSR73     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR73_GICD_ITARGETSR73(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR74
 */
#define VTSS_GIC400_GICD_ITARGETSR74         VTSS_IOREG(VTSS_TO_GIC400,0x64a)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR74 . GICD_ITARGETSR74
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR74_GICD_ITARGETSR74(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR74_GICD_ITARGETSR74     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR74_GICD_ITARGETSR74(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR75
 */
#define VTSS_GIC400_GICD_ITARGETSR75         VTSS_IOREG(VTSS_TO_GIC400,0x64b)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR75 . GICD_ITARGETSR75
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR75_GICD_ITARGETSR75(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR75_GICD_ITARGETSR75     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR75_GICD_ITARGETSR75(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR76
 */
#define VTSS_GIC400_GICD_ITARGETSR76         VTSS_IOREG(VTSS_TO_GIC400,0x64c)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR76 . GICD_ITARGETSR76
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR76_GICD_ITARGETSR76(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR76_GICD_ITARGETSR76     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR76_GICD_ITARGETSR76(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR77
 */
#define VTSS_GIC400_GICD_ITARGETSR77         VTSS_IOREG(VTSS_TO_GIC400,0x64d)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR77 . GICD_ITARGETSR77
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR77_GICD_ITARGETSR77(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR77_GICD_ITARGETSR77     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR77_GICD_ITARGETSR77(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR78
 */
#define VTSS_GIC400_GICD_ITARGETSR78         VTSS_IOREG(VTSS_TO_GIC400,0x64e)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR78 . GICD_ITARGETSR78
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR78_GICD_ITARGETSR78(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR78_GICD_ITARGETSR78     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR78_GICD_ITARGETSR78(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR79
 */
#define VTSS_GIC400_GICD_ITARGETSR79         VTSS_IOREG(VTSS_TO_GIC400,0x64f)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR79 . GICD_ITARGETSR79
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR79_GICD_ITARGETSR79(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR79_GICD_ITARGETSR79     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR79_GICD_ITARGETSR79(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR80
 */
#define VTSS_GIC400_GICD_ITARGETSR80         VTSS_IOREG(VTSS_TO_GIC400,0x650)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR80 . GICD_ITARGETSR80
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR80_GICD_ITARGETSR80(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR80_GICD_ITARGETSR80     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR80_GICD_ITARGETSR80(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR81
 */
#define VTSS_GIC400_GICD_ITARGETSR81         VTSS_IOREG(VTSS_TO_GIC400,0x651)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR81 . GICD_ITARGETSR81
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR81_GICD_ITARGETSR81(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR81_GICD_ITARGETSR81     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR81_GICD_ITARGETSR81(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR82
 */
#define VTSS_GIC400_GICD_ITARGETSR82         VTSS_IOREG(VTSS_TO_GIC400,0x652)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR82 . GICD_ITARGETSR82
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR82_GICD_ITARGETSR82(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR82_GICD_ITARGETSR82     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR82_GICD_ITARGETSR82(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR83
 */
#define VTSS_GIC400_GICD_ITARGETSR83         VTSS_IOREG(VTSS_TO_GIC400,0x653)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR83 . GICD_ITARGETSR83
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR83_GICD_ITARGETSR83(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR83_GICD_ITARGETSR83     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR83_GICD_ITARGETSR83(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR84
 */
#define VTSS_GIC400_GICD_ITARGETSR84         VTSS_IOREG(VTSS_TO_GIC400,0x654)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR84 . GICD_ITARGETSR84
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR84_GICD_ITARGETSR84(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR84_GICD_ITARGETSR84     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR84_GICD_ITARGETSR84(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR85
 */
#define VTSS_GIC400_GICD_ITARGETSR85         VTSS_IOREG(VTSS_TO_GIC400,0x655)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR85 . GICD_ITARGETSR85
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR85_GICD_ITARGETSR85(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR85_GICD_ITARGETSR85     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR85_GICD_ITARGETSR85(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR86
 */
#define VTSS_GIC400_GICD_ITARGETSR86         VTSS_IOREG(VTSS_TO_GIC400,0x656)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR86 . GICD_ITARGETSR86
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR86_GICD_ITARGETSR86(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR86_GICD_ITARGETSR86     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR86_GICD_ITARGETSR86(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR87
 */
#define VTSS_GIC400_GICD_ITARGETSR87         VTSS_IOREG(VTSS_TO_GIC400,0x657)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR87 . GICD_ITARGETSR87
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR87_GICD_ITARGETSR87(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR87_GICD_ITARGETSR87     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR87_GICD_ITARGETSR87(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR88
 */
#define VTSS_GIC400_GICD_ITARGETSR88         VTSS_IOREG(VTSS_TO_GIC400,0x658)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR88 . GICD_ITARGETSR88
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR88_GICD_ITARGETSR88(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR88_GICD_ITARGETSR88     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR88_GICD_ITARGETSR88(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR89
 */
#define VTSS_GIC400_GICD_ITARGETSR89         VTSS_IOREG(VTSS_TO_GIC400,0x659)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR89 . GICD_ITARGETSR89
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR89_GICD_ITARGETSR89(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR89_GICD_ITARGETSR89     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR89_GICD_ITARGETSR89(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR90
 */
#define VTSS_GIC400_GICD_ITARGETSR90         VTSS_IOREG(VTSS_TO_GIC400,0x65a)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR90 . GICD_ITARGETSR90
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR90_GICD_ITARGETSR90(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR90_GICD_ITARGETSR90     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR90_GICD_ITARGETSR90(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR91
 */
#define VTSS_GIC400_GICD_ITARGETSR91         VTSS_IOREG(VTSS_TO_GIC400,0x65b)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR91 . GICD_ITARGETSR91
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR91_GICD_ITARGETSR91(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR91_GICD_ITARGETSR91     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR91_GICD_ITARGETSR91(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR92
 */
#define VTSS_GIC400_GICD_ITARGETSR92         VTSS_IOREG(VTSS_TO_GIC400,0x65c)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR92 . GICD_ITARGETSR92
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR92_GICD_ITARGETSR92(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR92_GICD_ITARGETSR92     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR92_GICD_ITARGETSR92(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR93
 */
#define VTSS_GIC400_GICD_ITARGETSR93         VTSS_IOREG(VTSS_TO_GIC400,0x65d)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR93 . GICD_ITARGETSR93
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR93_GICD_ITARGETSR93(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR93_GICD_ITARGETSR93     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR93_GICD_ITARGETSR93(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR94
 */
#define VTSS_GIC400_GICD_ITARGETSR94         VTSS_IOREG(VTSS_TO_GIC400,0x65e)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR94 . GICD_ITARGETSR94
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR94_GICD_ITARGETSR94(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR94_GICD_ITARGETSR94     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR94_GICD_ITARGETSR94(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR95
 */
#define VTSS_GIC400_GICD_ITARGETSR95         VTSS_IOREG(VTSS_TO_GIC400,0x65f)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR95 . GICD_ITARGETSR95
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR95_GICD_ITARGETSR95(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR95_GICD_ITARGETSR95     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR95_GICD_ITARGETSR95(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR96
 */
#define VTSS_GIC400_GICD_ITARGETSR96         VTSS_IOREG(VTSS_TO_GIC400,0x660)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR96 . GICD_ITARGETSR96
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR96_GICD_ITARGETSR96(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR96_GICD_ITARGETSR96     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR96_GICD_ITARGETSR96(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR97
 */
#define VTSS_GIC400_GICD_ITARGETSR97         VTSS_IOREG(VTSS_TO_GIC400,0x661)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR97 . GICD_ITARGETSR97
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR97_GICD_ITARGETSR97(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR97_GICD_ITARGETSR97     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR97_GICD_ITARGETSR97(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR98
 */
#define VTSS_GIC400_GICD_ITARGETSR98         VTSS_IOREG(VTSS_TO_GIC400,0x662)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR98 . GICD_ITARGETSR98
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR98_GICD_ITARGETSR98(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR98_GICD_ITARGETSR98     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR98_GICD_ITARGETSR98(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR99
 */
#define VTSS_GIC400_GICD_ITARGETSR99         VTSS_IOREG(VTSS_TO_GIC400,0x663)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR99 . GICD_ITARGETSR99
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR99_GICD_ITARGETSR99(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR99_GICD_ITARGETSR99     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR99_GICD_ITARGETSR99(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR100
 */
#define VTSS_GIC400_GICD_ITARGETSR100        VTSS_IOREG(VTSS_TO_GIC400,0x664)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR100 . GICD_ITARGETSR100
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR100_GICD_ITARGETSR100(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR100_GICD_ITARGETSR100     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR100_GICD_ITARGETSR100(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR101
 */
#define VTSS_GIC400_GICD_ITARGETSR101        VTSS_IOREG(VTSS_TO_GIC400,0x665)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR101 . GICD_ITARGETSR101
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR101_GICD_ITARGETSR101(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR101_GICD_ITARGETSR101     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR101_GICD_ITARGETSR101(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR102
 */
#define VTSS_GIC400_GICD_ITARGETSR102        VTSS_IOREG(VTSS_TO_GIC400,0x666)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR102 . GICD_ITARGETSR102
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR102_GICD_ITARGETSR102(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR102_GICD_ITARGETSR102     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR102_GICD_ITARGETSR102(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR103
 */
#define VTSS_GIC400_GICD_ITARGETSR103        VTSS_IOREG(VTSS_TO_GIC400,0x667)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR103 . GICD_ITARGETSR103
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR103_GICD_ITARGETSR103(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR103_GICD_ITARGETSR103     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR103_GICD_ITARGETSR103(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR104
 */
#define VTSS_GIC400_GICD_ITARGETSR104        VTSS_IOREG(VTSS_TO_GIC400,0x668)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR104 . GICD_ITARGETSR104
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR104_GICD_ITARGETSR104(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR104_GICD_ITARGETSR104     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR104_GICD_ITARGETSR104(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR105
 */
#define VTSS_GIC400_GICD_ITARGETSR105        VTSS_IOREG(VTSS_TO_GIC400,0x669)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR105 . GICD_ITARGETSR105
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR105_GICD_ITARGETSR105(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR105_GICD_ITARGETSR105     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR105_GICD_ITARGETSR105(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR106
 */
#define VTSS_GIC400_GICD_ITARGETSR106        VTSS_IOREG(VTSS_TO_GIC400,0x66a)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR106 . GICD_ITARGETSR106
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR106_GICD_ITARGETSR106(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR106_GICD_ITARGETSR106     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR106_GICD_ITARGETSR106(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR107
 */
#define VTSS_GIC400_GICD_ITARGETSR107        VTSS_IOREG(VTSS_TO_GIC400,0x66b)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR107 . GICD_ITARGETSR107
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR107_GICD_ITARGETSR107(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR107_GICD_ITARGETSR107     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR107_GICD_ITARGETSR107(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR108
 */
#define VTSS_GIC400_GICD_ITARGETSR108        VTSS_IOREG(VTSS_TO_GIC400,0x66c)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR108 . GICD_ITARGETSR108
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR108_GICD_ITARGETSR108(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR108_GICD_ITARGETSR108     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR108_GICD_ITARGETSR108(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR109
 */
#define VTSS_GIC400_GICD_ITARGETSR109        VTSS_IOREG(VTSS_TO_GIC400,0x66d)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR109 . GICD_ITARGETSR109
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR109_GICD_ITARGETSR109(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR109_GICD_ITARGETSR109     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR109_GICD_ITARGETSR109(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR110
 */
#define VTSS_GIC400_GICD_ITARGETSR110        VTSS_IOREG(VTSS_TO_GIC400,0x66e)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR110 . GICD_ITARGETSR110
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR110_GICD_ITARGETSR110(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR110_GICD_ITARGETSR110     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR110_GICD_ITARGETSR110(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR111
 */
#define VTSS_GIC400_GICD_ITARGETSR111        VTSS_IOREG(VTSS_TO_GIC400,0x66f)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR111 . GICD_ITARGETSR111
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR111_GICD_ITARGETSR111(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR111_GICD_ITARGETSR111     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR111_GICD_ITARGETSR111(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR112
 */
#define VTSS_GIC400_GICD_ITARGETSR112        VTSS_IOREG(VTSS_TO_GIC400,0x670)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR112 . GICD_ITARGETSR112
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR112_GICD_ITARGETSR112(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR112_GICD_ITARGETSR112     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR112_GICD_ITARGETSR112(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR113
 */
#define VTSS_GIC400_GICD_ITARGETSR113        VTSS_IOREG(VTSS_TO_GIC400,0x671)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR113 . GICD_ITARGETSR113
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR113_GICD_ITARGETSR113(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR113_GICD_ITARGETSR113     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR113_GICD_ITARGETSR113(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR114
 */
#define VTSS_GIC400_GICD_ITARGETSR114        VTSS_IOREG(VTSS_TO_GIC400,0x672)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR114 . GICD_ITARGETSR114
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR114_GICD_ITARGETSR114(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR114_GICD_ITARGETSR114     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR114_GICD_ITARGETSR114(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR115
 */
#define VTSS_GIC400_GICD_ITARGETSR115        VTSS_IOREG(VTSS_TO_GIC400,0x673)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR115 . GICD_ITARGETSR115
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR115_GICD_ITARGETSR115(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR115_GICD_ITARGETSR115     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR115_GICD_ITARGETSR115(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR116
 */
#define VTSS_GIC400_GICD_ITARGETSR116        VTSS_IOREG(VTSS_TO_GIC400,0x674)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR116 . GICD_ITARGETSR116
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR116_GICD_ITARGETSR116(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR116_GICD_ITARGETSR116     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR116_GICD_ITARGETSR116(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR117
 */
#define VTSS_GIC400_GICD_ITARGETSR117        VTSS_IOREG(VTSS_TO_GIC400,0x675)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR117 . GICD_ITARGETSR117
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR117_GICD_ITARGETSR117(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR117_GICD_ITARGETSR117     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR117_GICD_ITARGETSR117(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR118
 */
#define VTSS_GIC400_GICD_ITARGETSR118        VTSS_IOREG(VTSS_TO_GIC400,0x676)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR118 . GICD_ITARGETSR118
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR118_GICD_ITARGETSR118(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR118_GICD_ITARGETSR118     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR118_GICD_ITARGETSR118(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR119
 */
#define VTSS_GIC400_GICD_ITARGETSR119        VTSS_IOREG(VTSS_TO_GIC400,0x677)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR119 . GICD_ITARGETSR119
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR119_GICD_ITARGETSR119(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR119_GICD_ITARGETSR119     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR119_GICD_ITARGETSR119(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR120
 */
#define VTSS_GIC400_GICD_ITARGETSR120        VTSS_IOREG(VTSS_TO_GIC400,0x678)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR120 . GICD_ITARGETSR120
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR120_GICD_ITARGETSR120(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR120_GICD_ITARGETSR120     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR120_GICD_ITARGETSR120(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR121
 */
#define VTSS_GIC400_GICD_ITARGETSR121        VTSS_IOREG(VTSS_TO_GIC400,0x679)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR121 . GICD_ITARGETSR121
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR121_GICD_ITARGETSR121(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR121_GICD_ITARGETSR121     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR121_GICD_ITARGETSR121(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR122
 */
#define VTSS_GIC400_GICD_ITARGETSR122        VTSS_IOREG(VTSS_TO_GIC400,0x67a)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR122 . GICD_ITARGETSR122
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR122_GICD_ITARGETSR122(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR122_GICD_ITARGETSR122     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR122_GICD_ITARGETSR122(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR123
 */
#define VTSS_GIC400_GICD_ITARGETSR123        VTSS_IOREG(VTSS_TO_GIC400,0x67b)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR123 . GICD_ITARGETSR123
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR123_GICD_ITARGETSR123(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR123_GICD_ITARGETSR123     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR123_GICD_ITARGETSR123(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR124
 */
#define VTSS_GIC400_GICD_ITARGETSR124        VTSS_IOREG(VTSS_TO_GIC400,0x67c)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR124 . GICD_ITARGETSR124
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR124_GICD_ITARGETSR124(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR124_GICD_ITARGETSR124     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR124_GICD_ITARGETSR124(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR125
 */
#define VTSS_GIC400_GICD_ITARGETSR125        VTSS_IOREG(VTSS_TO_GIC400,0x67d)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR125 . GICD_ITARGETSR125
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR125_GICD_ITARGETSR125(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR125_GICD_ITARGETSR125     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR125_GICD_ITARGETSR125(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR126
 */
#define VTSS_GIC400_GICD_ITARGETSR126        VTSS_IOREG(VTSS_TO_GIC400,0x67e)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR126 . GICD_ITARGETSR126
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR126_GICD_ITARGETSR126(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR126_GICD_ITARGETSR126     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR126_GICD_ITARGETSR126(x)  (x)


/**
 * \brief Interrupt Processor Targets Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ITARGETSR127
 */
#define VTSS_GIC400_GICD_ITARGETSR127        VTSS_IOREG(VTSS_TO_GIC400,0x67f)

/**
 * \brief
 * Interrupt Processor Targets Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ITARGETSR127 . GICD_ITARGETSR127
 */
#define  VTSS_F_GIC400_GICD_ITARGETSR127_GICD_ITARGETSR127(x)  (x)
#define  VTSS_M_GIC400_GICD_ITARGETSR127_GICD_ITARGETSR127     0xffffffff
#define  VTSS_X_GIC400_GICD_ITARGETSR127_GICD_ITARGETSR127(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR0
 */
#define VTSS_GIC400_GICD_ICFGR0              VTSS_IOREG(VTSS_TO_GIC400,0x700)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR0 . GICD_ICFGR0
 */
#define  VTSS_F_GIC400_GICD_ICFGR0_GICD_ICFGR0(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR0_GICD_ICFGR0     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR0_GICD_ICFGR0(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR1
 */
#define VTSS_GIC400_GICD_ICFGR1              VTSS_IOREG(VTSS_TO_GIC400,0x701)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR1 . GICD_ICFGR1
 */
#define  VTSS_F_GIC400_GICD_ICFGR1_GICD_ICFGR1(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR1_GICD_ICFGR1     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR1_GICD_ICFGR1(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR2
 */
#define VTSS_GIC400_GICD_ICFGR2              VTSS_IOREG(VTSS_TO_GIC400,0x702)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR2 . GICD_ICFGR2
 */
#define  VTSS_F_GIC400_GICD_ICFGR2_GICD_ICFGR2(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR2_GICD_ICFGR2     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR2_GICD_ICFGR2(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR3
 */
#define VTSS_GIC400_GICD_ICFGR3              VTSS_IOREG(VTSS_TO_GIC400,0x703)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR3 . GICD_ICFGR3
 */
#define  VTSS_F_GIC400_GICD_ICFGR3_GICD_ICFGR3(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR3_GICD_ICFGR3     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR3_GICD_ICFGR3(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR4
 */
#define VTSS_GIC400_GICD_ICFGR4              VTSS_IOREG(VTSS_TO_GIC400,0x704)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR4 . GICD_ICFGR4
 */
#define  VTSS_F_GIC400_GICD_ICFGR4_GICD_ICFGR4(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR4_GICD_ICFGR4     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR4_GICD_ICFGR4(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR5
 */
#define VTSS_GIC400_GICD_ICFGR5              VTSS_IOREG(VTSS_TO_GIC400,0x705)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR5 . GICD_ICFGR5
 */
#define  VTSS_F_GIC400_GICD_ICFGR5_GICD_ICFGR5(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR5_GICD_ICFGR5     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR5_GICD_ICFGR5(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR6
 */
#define VTSS_GIC400_GICD_ICFGR6              VTSS_IOREG(VTSS_TO_GIC400,0x706)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR6 . GICD_ICFGR6
 */
#define  VTSS_F_GIC400_GICD_ICFGR6_GICD_ICFGR6(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR6_GICD_ICFGR6     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR6_GICD_ICFGR6(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR7
 */
#define VTSS_GIC400_GICD_ICFGR7              VTSS_IOREG(VTSS_TO_GIC400,0x707)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR7 . GICD_ICFGR7
 */
#define  VTSS_F_GIC400_GICD_ICFGR7_GICD_ICFGR7(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR7_GICD_ICFGR7     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR7_GICD_ICFGR7(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR8
 */
#define VTSS_GIC400_GICD_ICFGR8              VTSS_IOREG(VTSS_TO_GIC400,0x708)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR8 . GICD_ICFGR8
 */
#define  VTSS_F_GIC400_GICD_ICFGR8_GICD_ICFGR8(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR8_GICD_ICFGR8     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR8_GICD_ICFGR8(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR9
 */
#define VTSS_GIC400_GICD_ICFGR9              VTSS_IOREG(VTSS_TO_GIC400,0x709)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR9 . GICD_ICFGR9
 */
#define  VTSS_F_GIC400_GICD_ICFGR9_GICD_ICFGR9(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR9_GICD_ICFGR9     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR9_GICD_ICFGR9(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR10
 */
#define VTSS_GIC400_GICD_ICFGR10             VTSS_IOREG(VTSS_TO_GIC400,0x70a)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR10 . GICD_ICFGR10
 */
#define  VTSS_F_GIC400_GICD_ICFGR10_GICD_ICFGR10(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR10_GICD_ICFGR10     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR10_GICD_ICFGR10(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR11
 */
#define VTSS_GIC400_GICD_ICFGR11             VTSS_IOREG(VTSS_TO_GIC400,0x70b)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR11 . GICD_ICFGR11
 */
#define  VTSS_F_GIC400_GICD_ICFGR11_GICD_ICFGR11(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR11_GICD_ICFGR11     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR11_GICD_ICFGR11(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR12
 */
#define VTSS_GIC400_GICD_ICFGR12             VTSS_IOREG(VTSS_TO_GIC400,0x70c)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR12 . GICD_ICFGR12
 */
#define  VTSS_F_GIC400_GICD_ICFGR12_GICD_ICFGR12(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR12_GICD_ICFGR12     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR12_GICD_ICFGR12(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR13
 */
#define VTSS_GIC400_GICD_ICFGR13             VTSS_IOREG(VTSS_TO_GIC400,0x70d)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR13 . GICD_ICFGR13
 */
#define  VTSS_F_GIC400_GICD_ICFGR13_GICD_ICFGR13(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR13_GICD_ICFGR13     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR13_GICD_ICFGR13(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR14
 */
#define VTSS_GIC400_GICD_ICFGR14             VTSS_IOREG(VTSS_TO_GIC400,0x70e)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR14 . GICD_ICFGR14
 */
#define  VTSS_F_GIC400_GICD_ICFGR14_GICD_ICFGR14(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR14_GICD_ICFGR14     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR14_GICD_ICFGR14(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR15
 */
#define VTSS_GIC400_GICD_ICFGR15             VTSS_IOREG(VTSS_TO_GIC400,0x70f)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR15 . GICD_ICFGR15
 */
#define  VTSS_F_GIC400_GICD_ICFGR15_GICD_ICFGR15(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR15_GICD_ICFGR15     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR15_GICD_ICFGR15(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR16
 */
#define VTSS_GIC400_GICD_ICFGR16             VTSS_IOREG(VTSS_TO_GIC400,0x710)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR16 . GICD_ICFGR16
 */
#define  VTSS_F_GIC400_GICD_ICFGR16_GICD_ICFGR16(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR16_GICD_ICFGR16     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR16_GICD_ICFGR16(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR17
 */
#define VTSS_GIC400_GICD_ICFGR17             VTSS_IOREG(VTSS_TO_GIC400,0x711)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR17 . GICD_ICFGR17
 */
#define  VTSS_F_GIC400_GICD_ICFGR17_GICD_ICFGR17(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR17_GICD_ICFGR17     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR17_GICD_ICFGR17(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR18
 */
#define VTSS_GIC400_GICD_ICFGR18             VTSS_IOREG(VTSS_TO_GIC400,0x712)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR18 . GICD_ICFGR18
 */
#define  VTSS_F_GIC400_GICD_ICFGR18_GICD_ICFGR18(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR18_GICD_ICFGR18     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR18_GICD_ICFGR18(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR19
 */
#define VTSS_GIC400_GICD_ICFGR19             VTSS_IOREG(VTSS_TO_GIC400,0x713)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR19 . GICD_ICFGR19
 */
#define  VTSS_F_GIC400_GICD_ICFGR19_GICD_ICFGR19(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR19_GICD_ICFGR19     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR19_GICD_ICFGR19(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR20
 */
#define VTSS_GIC400_GICD_ICFGR20             VTSS_IOREG(VTSS_TO_GIC400,0x714)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR20 . GICD_ICFGR20
 */
#define  VTSS_F_GIC400_GICD_ICFGR20_GICD_ICFGR20(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR20_GICD_ICFGR20     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR20_GICD_ICFGR20(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR21
 */
#define VTSS_GIC400_GICD_ICFGR21             VTSS_IOREG(VTSS_TO_GIC400,0x715)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR21 . GICD_ICFGR21
 */
#define  VTSS_F_GIC400_GICD_ICFGR21_GICD_ICFGR21(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR21_GICD_ICFGR21     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR21_GICD_ICFGR21(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR22
 */
#define VTSS_GIC400_GICD_ICFGR22             VTSS_IOREG(VTSS_TO_GIC400,0x716)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR22 . GICD_ICFGR22
 */
#define  VTSS_F_GIC400_GICD_ICFGR22_GICD_ICFGR22(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR22_GICD_ICFGR22     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR22_GICD_ICFGR22(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR23
 */
#define VTSS_GIC400_GICD_ICFGR23             VTSS_IOREG(VTSS_TO_GIC400,0x717)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR23 . GICD_ICFGR23
 */
#define  VTSS_F_GIC400_GICD_ICFGR23_GICD_ICFGR23(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR23_GICD_ICFGR23     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR23_GICD_ICFGR23(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR24
 */
#define VTSS_GIC400_GICD_ICFGR24             VTSS_IOREG(VTSS_TO_GIC400,0x718)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR24 . GICD_ICFGR24
 */
#define  VTSS_F_GIC400_GICD_ICFGR24_GICD_ICFGR24(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR24_GICD_ICFGR24     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR24_GICD_ICFGR24(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR25
 */
#define VTSS_GIC400_GICD_ICFGR25             VTSS_IOREG(VTSS_TO_GIC400,0x719)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR25 . GICD_ICFGR25
 */
#define  VTSS_F_GIC400_GICD_ICFGR25_GICD_ICFGR25(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR25_GICD_ICFGR25     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR25_GICD_ICFGR25(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR26
 */
#define VTSS_GIC400_GICD_ICFGR26             VTSS_IOREG(VTSS_TO_GIC400,0x71a)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR26 . GICD_ICFGR26
 */
#define  VTSS_F_GIC400_GICD_ICFGR26_GICD_ICFGR26(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR26_GICD_ICFGR26     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR26_GICD_ICFGR26(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR27
 */
#define VTSS_GIC400_GICD_ICFGR27             VTSS_IOREG(VTSS_TO_GIC400,0x71b)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR27 . GICD_ICFGR27
 */
#define  VTSS_F_GIC400_GICD_ICFGR27_GICD_ICFGR27(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR27_GICD_ICFGR27     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR27_GICD_ICFGR27(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR28
 */
#define VTSS_GIC400_GICD_ICFGR28             VTSS_IOREG(VTSS_TO_GIC400,0x71c)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR28 . GICD_ICFGR28
 */
#define  VTSS_F_GIC400_GICD_ICFGR28_GICD_ICFGR28(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR28_GICD_ICFGR28     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR28_GICD_ICFGR28(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR29
 */
#define VTSS_GIC400_GICD_ICFGR29             VTSS_IOREG(VTSS_TO_GIC400,0x71d)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR29 . GICD_ICFGR29
 */
#define  VTSS_F_GIC400_GICD_ICFGR29_GICD_ICFGR29(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR29_GICD_ICFGR29     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR29_GICD_ICFGR29(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR30
 */
#define VTSS_GIC400_GICD_ICFGR30             VTSS_IOREG(VTSS_TO_GIC400,0x71e)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR30 . GICD_ICFGR30
 */
#define  VTSS_F_GIC400_GICD_ICFGR30_GICD_ICFGR30(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR30_GICD_ICFGR30     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR30_GICD_ICFGR30(x)  (x)


/**
 * \brief Interrupt Configuration Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_ICFGR31
 */
#define VTSS_GIC400_GICD_ICFGR31             VTSS_IOREG(VTSS_TO_GIC400,0x71f)

/**
 * \brief
 * Interrupt Configuration Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_ICFGR31 . GICD_ICFGR31
 */
#define  VTSS_F_GIC400_GICD_ICFGR31_GICD_ICFGR31(x)  (x)
#define  VTSS_M_GIC400_GICD_ICFGR31_GICD_ICFGR31     0xffffffff
#define  VTSS_X_GIC400_GICD_ICFGR31_GICD_ICFGR31(x)  (x)


/**
 * \brief Private Peripheral Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PPISR
 */
#define VTSS_GIC400_GICD_PPISR               VTSS_IOREG(VTSS_TO_GIC400,0x740)

/**
 * \brief
 * Private Peripheral Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PPISR . GICD_PPISR
 */
#define  VTSS_F_GIC400_GICD_PPISR_GICD_PPISR(x)  (x)
#define  VTSS_M_GIC400_GICD_PPISR_GICD_PPISR     0xffffffff
#define  VTSS_X_GIC400_GICD_PPISR_GICD_PPISR(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR0
 */
#define VTSS_GIC400_GICD_SPISR0              VTSS_IOREG(VTSS_TO_GIC400,0x741)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR0 . GICD_SPISR0
 */
#define  VTSS_F_GIC400_GICD_SPISR0_GICD_SPISR0(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR0_GICD_SPISR0     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR0_GICD_SPISR0(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR1
 */
#define VTSS_GIC400_GICD_SPISR1              VTSS_IOREG(VTSS_TO_GIC400,0x742)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR1 . GICD_SPISR1
 */
#define  VTSS_F_GIC400_GICD_SPISR1_GICD_SPISR1(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR1_GICD_SPISR1     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR1_GICD_SPISR1(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR2
 */
#define VTSS_GIC400_GICD_SPISR2              VTSS_IOREG(VTSS_TO_GIC400,0x743)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR2 . GICD_SPISR2
 */
#define  VTSS_F_GIC400_GICD_SPISR2_GICD_SPISR2(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR2_GICD_SPISR2     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR2_GICD_SPISR2(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR3
 */
#define VTSS_GIC400_GICD_SPISR3              VTSS_IOREG(VTSS_TO_GIC400,0x744)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR3 . GICD_SPISR3
 */
#define  VTSS_F_GIC400_GICD_SPISR3_GICD_SPISR3(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR3_GICD_SPISR3     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR3_GICD_SPISR3(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR4
 */
#define VTSS_GIC400_GICD_SPISR4              VTSS_IOREG(VTSS_TO_GIC400,0x745)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR4 . GICD_SPISR4
 */
#define  VTSS_F_GIC400_GICD_SPISR4_GICD_SPISR4(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR4_GICD_SPISR4     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR4_GICD_SPISR4(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR5
 */
#define VTSS_GIC400_GICD_SPISR5              VTSS_IOREG(VTSS_TO_GIC400,0x746)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR5 . GICD_SPISR5
 */
#define  VTSS_F_GIC400_GICD_SPISR5_GICD_SPISR5(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR5_GICD_SPISR5     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR5_GICD_SPISR5(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR6
 */
#define VTSS_GIC400_GICD_SPISR6              VTSS_IOREG(VTSS_TO_GIC400,0x747)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR6 . GICD_SPISR6
 */
#define  VTSS_F_GIC400_GICD_SPISR6_GICD_SPISR6(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR6_GICD_SPISR6     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR6_GICD_SPISR6(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR7
 */
#define VTSS_GIC400_GICD_SPISR7              VTSS_IOREG(VTSS_TO_GIC400,0x748)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR7 . GICD_SPISR7
 */
#define  VTSS_F_GIC400_GICD_SPISR7_GICD_SPISR7(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR7_GICD_SPISR7     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR7_GICD_SPISR7(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR8
 */
#define VTSS_GIC400_GICD_SPISR8              VTSS_IOREG(VTSS_TO_GIC400,0x749)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR8 . GICD_SPISR8
 */
#define  VTSS_F_GIC400_GICD_SPISR8_GICD_SPISR8(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR8_GICD_SPISR8     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR8_GICD_SPISR8(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR9
 */
#define VTSS_GIC400_GICD_SPISR9              VTSS_IOREG(VTSS_TO_GIC400,0x74a)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR9 . GICD_SPISR9
 */
#define  VTSS_F_GIC400_GICD_SPISR9_GICD_SPISR9(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR9_GICD_SPISR9     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR9_GICD_SPISR9(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR10
 */
#define VTSS_GIC400_GICD_SPISR10             VTSS_IOREG(VTSS_TO_GIC400,0x74b)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR10 . GICD_SPISR10
 */
#define  VTSS_F_GIC400_GICD_SPISR10_GICD_SPISR10(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR10_GICD_SPISR10     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR10_GICD_SPISR10(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR11
 */
#define VTSS_GIC400_GICD_SPISR11             VTSS_IOREG(VTSS_TO_GIC400,0x74c)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR11 . GICD_SPISR11
 */
#define  VTSS_F_GIC400_GICD_SPISR11_GICD_SPISR11(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR11_GICD_SPISR11     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR11_GICD_SPISR11(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR12
 */
#define VTSS_GIC400_GICD_SPISR12             VTSS_IOREG(VTSS_TO_GIC400,0x74d)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR12 . GICD_SPISR12
 */
#define  VTSS_F_GIC400_GICD_SPISR12_GICD_SPISR12(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR12_GICD_SPISR12     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR12_GICD_SPISR12(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR13
 */
#define VTSS_GIC400_GICD_SPISR13             VTSS_IOREG(VTSS_TO_GIC400,0x74e)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR13 . GICD_SPISR13
 */
#define  VTSS_F_GIC400_GICD_SPISR13_GICD_SPISR13(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR13_GICD_SPISR13     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR13_GICD_SPISR13(x)  (x)


/**
 * \brief Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPISR14
 */
#define VTSS_GIC400_GICD_SPISR14             VTSS_IOREG(VTSS_TO_GIC400,0x74f)

/**
 * \brief
 * Shared Peripheral Interrupt Status Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPISR14 . GICD_SPISR14
 */
#define  VTSS_F_GIC400_GICD_SPISR14_GICD_SPISR14(x)  (x)
#define  VTSS_M_GIC400_GICD_SPISR14_GICD_SPISR14     0xffffffff
#define  VTSS_X_GIC400_GICD_SPISR14_GICD_SPISR14(x)  (x)


/**
 * \brief Software Generated Interrupt Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SGIR
 */
#define VTSS_GIC400_GICD_SGIR                VTSS_IOREG(VTSS_TO_GIC400,0x7c0)

/**
 * \brief
 * Software Generated Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SGIR . GICD_SGIR
 */
#define  VTSS_F_GIC400_GICD_SGIR_GICD_SGIR(x)  (x)
#define  VTSS_M_GIC400_GICD_SGIR_GICD_SGIR     0xffffffff
#define  VTSS_X_GIC400_GICD_SGIR_GICD_SGIR(x)  (x)


/**
 * \brief SGI Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CPENDSGIR0
 */
#define VTSS_GIC400_GICD_CPENDSGIR0          VTSS_IOREG(VTSS_TO_GIC400,0x7c4)

/**
 * \brief
 * SGI Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CPENDSGIR0 . GICD_CPENDSGIR0
 */
#define  VTSS_F_GIC400_GICD_CPENDSGIR0_GICD_CPENDSGIR0(x)  (x)
#define  VTSS_M_GIC400_GICD_CPENDSGIR0_GICD_CPENDSGIR0     0xffffffff
#define  VTSS_X_GIC400_GICD_CPENDSGIR0_GICD_CPENDSGIR0(x)  (x)


/**
 * \brief SGI Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CPENDSGIR1
 */
#define VTSS_GIC400_GICD_CPENDSGIR1          VTSS_IOREG(VTSS_TO_GIC400,0x7c5)

/**
 * \brief
 * SGI Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CPENDSGIR1 . GICD_CPENDSGIR1
 */
#define  VTSS_F_GIC400_GICD_CPENDSGIR1_GICD_CPENDSGIR1(x)  (x)
#define  VTSS_M_GIC400_GICD_CPENDSGIR1_GICD_CPENDSGIR1     0xffffffff
#define  VTSS_X_GIC400_GICD_CPENDSGIR1_GICD_CPENDSGIR1(x)  (x)


/**
 * \brief SGI Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CPENDSGIR2
 */
#define VTSS_GIC400_GICD_CPENDSGIR2          VTSS_IOREG(VTSS_TO_GIC400,0x7c6)

/**
 * \brief
 * SGI Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CPENDSGIR2 . GICD_CPENDSGIR2
 */
#define  VTSS_F_GIC400_GICD_CPENDSGIR2_GICD_CPENDSGIR2(x)  (x)
#define  VTSS_M_GIC400_GICD_CPENDSGIR2_GICD_CPENDSGIR2     0xffffffff
#define  VTSS_X_GIC400_GICD_CPENDSGIR2_GICD_CPENDSGIR2(x)  (x)


/**
 * \brief SGI Clear-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CPENDSGIR3
 */
#define VTSS_GIC400_GICD_CPENDSGIR3          VTSS_IOREG(VTSS_TO_GIC400,0x7c7)

/**
 * \brief
 * SGI Clear-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CPENDSGIR3 . GICD_CPENDSGIR3
 */
#define  VTSS_F_GIC400_GICD_CPENDSGIR3_GICD_CPENDSGIR3(x)  (x)
#define  VTSS_M_GIC400_GICD_CPENDSGIR3_GICD_CPENDSGIR3     0xffffffff
#define  VTSS_X_GIC400_GICD_CPENDSGIR3_GICD_CPENDSGIR3(x)  (x)


/**
 * \brief SGI Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPENDSGIR0
 */
#define VTSS_GIC400_GICD_SPENDSGIR0          VTSS_IOREG(VTSS_TO_GIC400,0x7c8)

/**
 * \brief
 * SGI Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPENDSGIR0 . GICD_SPENDSGIR0
 */
#define  VTSS_F_GIC400_GICD_SPENDSGIR0_GICD_SPENDSGIR0(x)  (x)
#define  VTSS_M_GIC400_GICD_SPENDSGIR0_GICD_SPENDSGIR0     0xffffffff
#define  VTSS_X_GIC400_GICD_SPENDSGIR0_GICD_SPENDSGIR0(x)  (x)


/**
 * \brief SGI Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPENDSGIR1
 */
#define VTSS_GIC400_GICD_SPENDSGIR1          VTSS_IOREG(VTSS_TO_GIC400,0x7c9)

/**
 * \brief
 * SGI Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPENDSGIR1 . GICD_SPENDSGIR1
 */
#define  VTSS_F_GIC400_GICD_SPENDSGIR1_GICD_SPENDSGIR1(x)  (x)
#define  VTSS_M_GIC400_GICD_SPENDSGIR1_GICD_SPENDSGIR1     0xffffffff
#define  VTSS_X_GIC400_GICD_SPENDSGIR1_GICD_SPENDSGIR1(x)  (x)


/**
 * \brief SGI Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPENDSGIR2
 */
#define VTSS_GIC400_GICD_SPENDSGIR2          VTSS_IOREG(VTSS_TO_GIC400,0x7ca)

/**
 * \brief
 * SGI Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPENDSGIR2 . GICD_SPENDSGIR2
 */
#define  VTSS_F_GIC400_GICD_SPENDSGIR2_GICD_SPENDSGIR2(x)  (x)
#define  VTSS_M_GIC400_GICD_SPENDSGIR2_GICD_SPENDSGIR2     0xffffffff
#define  VTSS_X_GIC400_GICD_SPENDSGIR2_GICD_SPENDSGIR2(x)  (x)


/**
 * \brief SGI Set-Pending Registers
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_SPENDSGIR3
 */
#define VTSS_GIC400_GICD_SPENDSGIR3          VTSS_IOREG(VTSS_TO_GIC400,0x7cb)

/**
 * \brief
 * SGI Set-Pending Registers
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_SPENDSGIR3 . GICD_SPENDSGIR3
 */
#define  VTSS_F_GIC400_GICD_SPENDSGIR3_GICD_SPENDSGIR3(x)  (x)
#define  VTSS_M_GIC400_GICD_SPENDSGIR3_GICD_SPENDSGIR3     0xffffffff
#define  VTSS_X_GIC400_GICD_SPENDSGIR3_GICD_SPENDSGIR3(x)  (x)


/**
 * \brief Peripheral ID4 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PIDR4
 */
#define VTSS_GIC400_GICD_PIDR4               VTSS_IOREG(VTSS_TO_GIC400,0x7f4)

/**
 * \brief
 * Peripheral ID4 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PIDR4 . GICD_PIDR4
 */
#define  VTSS_F_GIC400_GICD_PIDR4_GICD_PIDR4(x)  (x)
#define  VTSS_M_GIC400_GICD_PIDR4_GICD_PIDR4     0xffffffff
#define  VTSS_X_GIC400_GICD_PIDR4_GICD_PIDR4(x)  (x)


/**
 * \brief Peripheral ID5 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PIDR5
 */
#define VTSS_GIC400_GICD_PIDR5               VTSS_IOREG(VTSS_TO_GIC400,0x7f5)

/**
 * \brief
 * Peripheral ID5 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PIDR5 . GICD_PIDR5
 */
#define  VTSS_F_GIC400_GICD_PIDR5_GICD_PIDR5(x)  (x)
#define  VTSS_M_GIC400_GICD_PIDR5_GICD_PIDR5     0xffffffff
#define  VTSS_X_GIC400_GICD_PIDR5_GICD_PIDR5(x)  (x)


/**
 * \brief Peripheral ID6 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PIDR6
 */
#define VTSS_GIC400_GICD_PIDR6               VTSS_IOREG(VTSS_TO_GIC400,0x7f6)

/**
 * \brief
 * Peripheral ID6 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PIDR6 . GICD_PIDR6
 */
#define  VTSS_F_GIC400_GICD_PIDR6_GICD_PIDR6(x)  (x)
#define  VTSS_M_GIC400_GICD_PIDR6_GICD_PIDR6     0xffffffff
#define  VTSS_X_GIC400_GICD_PIDR6_GICD_PIDR6(x)  (x)


/**
 * \brief Peripheral ID7 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PIDR7
 */
#define VTSS_GIC400_GICD_PIDR7               VTSS_IOREG(VTSS_TO_GIC400,0x7f7)

/**
 * \brief
 * Peripheral ID7 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PIDR7 . GICD_PIDR7
 */
#define  VTSS_F_GIC400_GICD_PIDR7_GICD_PIDR7(x)  (x)
#define  VTSS_M_GIC400_GICD_PIDR7_GICD_PIDR7     0xffffffff
#define  VTSS_X_GIC400_GICD_PIDR7_GICD_PIDR7(x)  (x)


/**
 * \brief Peripheral ID0 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PIDR0
 */
#define VTSS_GIC400_GICD_PIDR0               VTSS_IOREG(VTSS_TO_GIC400,0x7f8)

/**
 * \brief
 * Peripheral ID0 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PIDR0 . GICD_PIDR0
 */
#define  VTSS_F_GIC400_GICD_PIDR0_GICD_PIDR0(x)  (x)
#define  VTSS_M_GIC400_GICD_PIDR0_GICD_PIDR0     0xffffffff
#define  VTSS_X_GIC400_GICD_PIDR0_GICD_PIDR0(x)  (x)


/**
 * \brief Peripheral ID1 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PIDR1
 */
#define VTSS_GIC400_GICD_PIDR1               VTSS_IOREG(VTSS_TO_GIC400,0x7f9)

/**
 * \brief
 * Peripheral ID1 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PIDR1 . GICD_PIDR1
 */
#define  VTSS_F_GIC400_GICD_PIDR1_GICD_PIDR1(x)  (x)
#define  VTSS_M_GIC400_GICD_PIDR1_GICD_PIDR1     0xffffffff
#define  VTSS_X_GIC400_GICD_PIDR1_GICD_PIDR1(x)  (x)


/**
 * \brief Peripheral ID2 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PIDR2
 */
#define VTSS_GIC400_GICD_PIDR2               VTSS_IOREG(VTSS_TO_GIC400,0x7fa)

/**
 * \brief
 * Peripheral ID2 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PIDR2 . GICD_PIDR2
 */
#define  VTSS_F_GIC400_GICD_PIDR2_GICD_PIDR2(x)  (x)
#define  VTSS_M_GIC400_GICD_PIDR2_GICD_PIDR2     0xffffffff
#define  VTSS_X_GIC400_GICD_PIDR2_GICD_PIDR2(x)  (x)


/**
 * \brief Peripheral ID3 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_PIDR3
 */
#define VTSS_GIC400_GICD_PIDR3               VTSS_IOREG(VTSS_TO_GIC400,0x7fb)

/**
 * \brief
 * Peripheral ID3 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_PIDR3 . GICD_PIDR3
 */
#define  VTSS_F_GIC400_GICD_PIDR3_GICD_PIDR3(x)  (x)
#define  VTSS_M_GIC400_GICD_PIDR3_GICD_PIDR3     0xffffffff
#define  VTSS_X_GIC400_GICD_PIDR3_GICD_PIDR3(x)  (x)


/**
 * \brief Component ID0 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CIDR0
 */
#define VTSS_GIC400_GICD_CIDR0               VTSS_IOREG(VTSS_TO_GIC400,0x7fc)

/**
 * \brief
 * Component ID0 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CIDR0 . GICD_CIDR0
 */
#define  VTSS_F_GIC400_GICD_CIDR0_GICD_CIDR0(x)  (x)
#define  VTSS_M_GIC400_GICD_CIDR0_GICD_CIDR0     0xffffffff
#define  VTSS_X_GIC400_GICD_CIDR0_GICD_CIDR0(x)  (x)


/**
 * \brief Component ID1 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CIDR1
 */
#define VTSS_GIC400_GICD_CIDR1               VTSS_IOREG(VTSS_TO_GIC400,0x7fd)

/**
 * \brief
 * Component ID1 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CIDR1 . GICD_CIDR1
 */
#define  VTSS_F_GIC400_GICD_CIDR1_GICD_CIDR1(x)  (x)
#define  VTSS_M_GIC400_GICD_CIDR1_GICD_CIDR1     0xffffffff
#define  VTSS_X_GIC400_GICD_CIDR1_GICD_CIDR1(x)  (x)


/**
 * \brief Component ID2 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CIDR2
 */
#define VTSS_GIC400_GICD_CIDR2               VTSS_IOREG(VTSS_TO_GIC400,0x7fe)

/**
 * \brief
 * Component ID2 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CIDR2 . GICD_CIDR2
 */
#define  VTSS_F_GIC400_GICD_CIDR2_GICD_CIDR2(x)  (x)
#define  VTSS_M_GIC400_GICD_CIDR2_GICD_CIDR2     0xffffffff
#define  VTSS_X_GIC400_GICD_CIDR2_GICD_CIDR2(x)  (x)


/**
 * \brief Component ID3 Register
 *
 * \details
 * Register: \a GIC400:DISTRIBUTOR:GICD_CIDR3
 */
#define VTSS_GIC400_GICD_CIDR3               VTSS_IOREG(VTSS_TO_GIC400,0x7ff)

/**
 * \brief
 * Component ID3 Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICD_CIDR3 . GICD_CIDR3
 */
#define  VTSS_F_GIC400_GICD_CIDR3_GICD_CIDR3(x)  (x)
#define  VTSS_M_GIC400_GICD_CIDR3_GICD_CIDR3     0xffffffff
#define  VTSS_X_GIC400_GICD_CIDR3_GICD_CIDR3(x)  (x)

/**
 * Register Group: \a GIC400:CPUIF
 *
 * Memory map for the GIC CPU interface blocks. Contains all registers with the GICC prefix. Note: The CPU interface block for each CPU is separate.
 */


/**
 * \brief CPU Interface Control Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_CTLR
 */
#define VTSS_GIC400_GICC_CTLR                VTSS_IOREG(VTSS_TO_GIC400,0x800)

/**
 * \brief
 * CPU Interface Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_CTLR . GICC_CTLR
 */
#define  VTSS_F_GIC400_GICC_CTLR_GICC_CTLR(x)  (x)
#define  VTSS_M_GIC400_GICC_CTLR_GICC_CTLR     0xffffffff
#define  VTSS_X_GIC400_GICC_CTLR_GICC_CTLR(x)  (x)


/**
 * \brief Interrupt Priority Mask Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_PMR
 */
#define VTSS_GIC400_GICC_PMR                 VTSS_IOREG(VTSS_TO_GIC400,0x801)

/**
 * \brief
 * Interrupt Priority Mask Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_PMR . GICC_PMR
 */
#define  VTSS_F_GIC400_GICC_PMR_GICC_PMR(x)   (x)
#define  VTSS_M_GIC400_GICC_PMR_GICC_PMR      0xffffffff
#define  VTSS_X_GIC400_GICC_PMR_GICC_PMR(x)   (x)


/**
 * \brief Binary Point Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_BPR
 */
#define VTSS_GIC400_GICC_BPR                 VTSS_IOREG(VTSS_TO_GIC400,0x802)

/**
 * \brief
 * Binary Point Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_BPR . GICC_BPR
 */
#define  VTSS_F_GIC400_GICC_BPR_GICC_BPR(x)   (x)
#define  VTSS_M_GIC400_GICC_BPR_GICC_BPR      0xffffffff
#define  VTSS_X_GIC400_GICC_BPR_GICC_BPR(x)   (x)


/**
 * \brief Interrupt Acknowledge Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_IAR
 */
#define VTSS_GIC400_GICC_IAR                 VTSS_IOREG(VTSS_TO_GIC400,0x803)

/**
 * \brief
 * Interrupt Acknowledge Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_IAR . GICC_IAR
 */
#define  VTSS_F_GIC400_GICC_IAR_GICC_IAR(x)   (x)
#define  VTSS_M_GIC400_GICC_IAR_GICC_IAR      0xffffffff
#define  VTSS_X_GIC400_GICC_IAR_GICC_IAR(x)   (x)


/**
 * \brief End of Interrupt Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_EOIR
 */
#define VTSS_GIC400_GICC_EOIR                VTSS_IOREG(VTSS_TO_GIC400,0x804)

/**
 * \brief
 * End of Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_EOIR . GICC_EOIR
 */
#define  VTSS_F_GIC400_GICC_EOIR_GICC_EOIR(x)  (x)
#define  VTSS_M_GIC400_GICC_EOIR_GICC_EOIR     0xffffffff
#define  VTSS_X_GIC400_GICC_EOIR_GICC_EOIR(x)  (x)


/**
 * \brief Running Priority Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_RPR
 */
#define VTSS_GIC400_GICC_RPR                 VTSS_IOREG(VTSS_TO_GIC400,0x805)

/**
 * \brief
 * Running Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_RPR . GICC_RPR
 */
#define  VTSS_F_GIC400_GICC_RPR_GICC_RPR(x)   (x)
#define  VTSS_M_GIC400_GICC_RPR_GICC_RPR      0xffffffff
#define  VTSS_X_GIC400_GICC_RPR_GICC_RPR(x)   (x)


/**
 * \brief Highest Priority Pending Interrupt Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_HPPIR
 */
#define VTSS_GIC400_GICC_HPPIR               VTSS_IOREG(VTSS_TO_GIC400,0x806)

/**
 * \brief
 * Highest Priority Pending Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_HPPIR . GICC_HPPIR
 */
#define  VTSS_F_GIC400_GICC_HPPIR_GICC_HPPIR(x)  (x)
#define  VTSS_M_GIC400_GICC_HPPIR_GICC_HPPIR     0xffffffff
#define  VTSS_X_GIC400_GICC_HPPIR_GICC_HPPIR(x)  (x)


/**
 * \brief Aliased Binary Point Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_ABPR
 */
#define VTSS_GIC400_GICC_ABPR                VTSS_IOREG(VTSS_TO_GIC400,0x807)

/**
 * \brief
 * Aliased Binary Point Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_ABPR . GICC_ABPR
 */
#define  VTSS_F_GIC400_GICC_ABPR_GICC_ABPR(x)  (x)
#define  VTSS_M_GIC400_GICC_ABPR_GICC_ABPR     0xffffffff
#define  VTSS_X_GIC400_GICC_ABPR_GICC_ABPR(x)  (x)


/**
 * \brief Aliased Interrupt Acknowledge Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_AIAR
 */
#define VTSS_GIC400_GICC_AIAR                VTSS_IOREG(VTSS_TO_GIC400,0x808)

/**
 * \brief
 * Aliased Interrupt Acknowledge Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_AIAR . GICC_AIAR
 */
#define  VTSS_F_GIC400_GICC_AIAR_GICC_AIAR(x)  (x)
#define  VTSS_M_GIC400_GICC_AIAR_GICC_AIAR     0xffffffff
#define  VTSS_X_GIC400_GICC_AIAR_GICC_AIAR(x)  (x)


/**
 * \brief Aliased End of Interrupt Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_AEOIR
 */
#define VTSS_GIC400_GICC_AEOIR               VTSS_IOREG(VTSS_TO_GIC400,0x809)

/**
 * \brief
 * Aliased End of Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_AEOIR . GICC_AEOIR
 */
#define  VTSS_F_GIC400_GICC_AEOIR_GICC_AEOIR(x)  (x)
#define  VTSS_M_GIC400_GICC_AEOIR_GICC_AEOIR     0xffffffff
#define  VTSS_X_GIC400_GICC_AEOIR_GICC_AEOIR(x)  (x)


/**
 * \brief Aliased Highest Priority Pending Interrupt Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_AHPPIR
 */
#define VTSS_GIC400_GICC_AHPPIR              VTSS_IOREG(VTSS_TO_GIC400,0x80a)

/**
 * \brief
 * Aliased Highest Priority Pending Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_AHPPIR . GICC_AHPPIR
 */
#define  VTSS_F_GIC400_GICC_AHPPIR_GICC_AHPPIR(x)  (x)
#define  VTSS_M_GIC400_GICC_AHPPIR_GICC_AHPPIR     0xffffffff
#define  VTSS_X_GIC400_GICC_AHPPIR_GICC_AHPPIR(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_APR0
 */
#define VTSS_GIC400_GICC_APR0                VTSS_IOREG(VTSS_TO_GIC400,0x834)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_APR0 . GICC_APR0
 */
#define  VTSS_F_GIC400_GICC_APR0_GICC_APR0(x)  (x)
#define  VTSS_M_GIC400_GICC_APR0_GICC_APR0     0xffffffff
#define  VTSS_X_GIC400_GICC_APR0_GICC_APR0(x)  (x)


/**
 * \brief Non-Secure Active Priority Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_NSAPR0
 */
#define VTSS_GIC400_GICC_NSAPR0              VTSS_IOREG(VTSS_TO_GIC400,0x838)

/**
 * \brief
 * Non-Secure Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_NSAPR0 . GICC_NSAPR0
 */
#define  VTSS_F_GIC400_GICC_NSAPR0_GICC_NSAPR0(x)  (x)
#define  VTSS_M_GIC400_GICC_NSAPR0_GICC_NSAPR0     0xffffffff
#define  VTSS_X_GIC400_GICC_NSAPR0_GICC_NSAPR0(x)  (x)


/**
 * \brief CPU Interface Identification Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_IIDR
 */
#define VTSS_GIC400_GICC_IIDR                VTSS_IOREG(VTSS_TO_GIC400,0x83f)

/**
 * \brief
 * CPU Interface Identification Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_IIDR . GICC_IIDR
 */
#define  VTSS_F_GIC400_GICC_IIDR_GICC_IIDR(x)  (x)
#define  VTSS_M_GIC400_GICC_IIDR_GICC_IIDR     0xffffffff
#define  VTSS_X_GIC400_GICC_IIDR_GICC_IIDR(x)  (x)


/**
 * \brief Deactivate Interrupt Register
 *
 * \details
 * Register: \a GIC400:CPUIF:GICC_DIR
 */
#define VTSS_GIC400_GICC_DIR                 VTSS_IOREG(VTSS_TO_GIC400,0xc00)

/**
 * \brief
 * Deactivate Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICC_DIR . GICC_DIR
 */
#define  VTSS_F_GIC400_GICC_DIR_GICC_DIR(x)   (x)
#define  VTSS_M_GIC400_GICC_DIR_GICC_DIR      0xffffffff
#define  VTSS_X_GIC400_GICC_DIR_GICC_DIR(x)   (x)

/**
 * Register Group: \a GIC400:VCPUIFHYP
 *
 * Memory map for the GIC virtual CPU interface control registers. Contains all registers with the GICH prefix. Note: This provides access to the control registers for the current CPU. It is expected that this block will only be made accessible to the hypervisor.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_HCR       VTSS_IOREG(VTSS_TO_GIC400,0x1000)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_VTR       VTSS_IOREG(VTSS_TO_GIC400,0x1001)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_VMCR      VTSS_IOREG(VTSS_TO_GIC400,0x1002)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_MISR      VTSS_IOREG(VTSS_TO_GIC400,0x1004)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_EISR0     VTSS_IOREG(VTSS_TO_GIC400,0x1008)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_ELSR0     VTSS_IOREG(VTSS_TO_GIC400,0x100c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_APR0      VTSS_IOREG(VTSS_TO_GIC400,0x103c)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_LR0       VTSS_IOREG(VTSS_TO_GIC400,0x1040)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_LR1       VTSS_IOREG(VTSS_TO_GIC400,0x1041)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_LR2       VTSS_IOREG(VTSS_TO_GIC400,0x1042)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYP:VCPUIFHYP_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYP_GICH_LR3       VTSS_IOREG(VTSS_TO_GIC400,0x1043)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYP_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYP_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYP_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYP_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFHYPALIAS0
 *
 * Memory map allowing access to the GIC virtual CPU interface control registers for CPU0 from any processor. Contains all registers with the GICH prefix. Note: This provides a means for other processors to access the virtual CPU interface control registers for CPU0. It is expected that this block will only be made accessible to hypervisors.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_HCR  VTSS_IOREG(VTSS_TO_GIC400,0x1400)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_VTR  VTSS_IOREG(VTSS_TO_GIC400,0x1401)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_VMCR  VTSS_IOREG(VTSS_TO_GIC400,0x1402)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_MISR  VTSS_IOREG(VTSS_TO_GIC400,0x1404)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_EISR0  VTSS_IOREG(VTSS_TO_GIC400,0x1408)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_ELSR0  VTSS_IOREG(VTSS_TO_GIC400,0x140c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_APR0  VTSS_IOREG(VTSS_TO_GIC400,0x143c)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_LR0  VTSS_IOREG(VTSS_TO_GIC400,0x1440)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_LR1  VTSS_IOREG(VTSS_TO_GIC400,0x1441)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_LR2  VTSS_IOREG(VTSS_TO_GIC400,0x1442)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS0:VCPUIFHYPALIAS0_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYPALIAS0_GICH_LR3  VTSS_IOREG(VTSS_TO_GIC400,0x1443)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS0_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS0_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS0_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS0_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFHYPALIAS1
 *
 * Memory map allowing access to the GIC virtual CPU interface control registers for CPU1 from any processor. Contains all registers with the GICH prefix. Note: This provides a means for other processors to access the virtual CPU interface control registers for CPU1. It is expected that this block will only be made accessible to hypervisors.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_HCR  VTSS_IOREG(VTSS_TO_GIC400,0x1480)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_VTR  VTSS_IOREG(VTSS_TO_GIC400,0x1481)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_VMCR  VTSS_IOREG(VTSS_TO_GIC400,0x1482)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_MISR  VTSS_IOREG(VTSS_TO_GIC400,0x1484)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_EISR0  VTSS_IOREG(VTSS_TO_GIC400,0x1488)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_ELSR0  VTSS_IOREG(VTSS_TO_GIC400,0x148c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_APR0  VTSS_IOREG(VTSS_TO_GIC400,0x14bc)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_LR0  VTSS_IOREG(VTSS_TO_GIC400,0x14c0)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_LR1  VTSS_IOREG(VTSS_TO_GIC400,0x14c1)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_LR2  VTSS_IOREG(VTSS_TO_GIC400,0x14c2)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS1:VCPUIFHYPALIAS1_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYPALIAS1_GICH_LR3  VTSS_IOREG(VTSS_TO_GIC400,0x14c3)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS1_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS1_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS1_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS1_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFHYPALIAS2
 *
 * Memory map allowing access to the GIC virtual CPU interface control registers for CPU2 from any processor. Contains all registers with the GICH prefix. Note: This provides a means for other processors to access the virtual CPU interface control registers for CPU2. It is expected that this block will only be made accessible to hypervisors.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_HCR  VTSS_IOREG(VTSS_TO_GIC400,0x1500)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_VTR  VTSS_IOREG(VTSS_TO_GIC400,0x1501)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_VMCR  VTSS_IOREG(VTSS_TO_GIC400,0x1502)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_MISR  VTSS_IOREG(VTSS_TO_GIC400,0x1504)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_EISR0  VTSS_IOREG(VTSS_TO_GIC400,0x1508)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_ELSR0  VTSS_IOREG(VTSS_TO_GIC400,0x150c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_APR0  VTSS_IOREG(VTSS_TO_GIC400,0x153c)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_LR0  VTSS_IOREG(VTSS_TO_GIC400,0x1540)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_LR1  VTSS_IOREG(VTSS_TO_GIC400,0x1541)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_LR2  VTSS_IOREG(VTSS_TO_GIC400,0x1542)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS2:VCPUIFHYPALIAS2_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYPALIAS2_GICH_LR3  VTSS_IOREG(VTSS_TO_GIC400,0x1543)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS2_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS2_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS2_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS2_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFHYPALIAS3
 *
 * Memory map allowing access to the GIC virtual CPU interface control registers for CPU3 from any processor. Contains all registers with the GICH prefix. Note: This provides a means for other processors to access the virtual CPU interface control registers for CPU3. It is expected that this block will only be made accessible to hypervisors.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_HCR  VTSS_IOREG(VTSS_TO_GIC400,0x1580)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_VTR  VTSS_IOREG(VTSS_TO_GIC400,0x1581)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_VMCR  VTSS_IOREG(VTSS_TO_GIC400,0x1582)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_MISR  VTSS_IOREG(VTSS_TO_GIC400,0x1584)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_EISR0  VTSS_IOREG(VTSS_TO_GIC400,0x1588)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_ELSR0  VTSS_IOREG(VTSS_TO_GIC400,0x158c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_APR0  VTSS_IOREG(VTSS_TO_GIC400,0x15bc)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_LR0  VTSS_IOREG(VTSS_TO_GIC400,0x15c0)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_LR1  VTSS_IOREG(VTSS_TO_GIC400,0x15c1)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_LR2  VTSS_IOREG(VTSS_TO_GIC400,0x15c2)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS3:VCPUIFHYPALIAS3_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYPALIAS3_GICH_LR3  VTSS_IOREG(VTSS_TO_GIC400,0x15c3)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS3_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS3_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS3_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS3_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFHYPALIAS4
 *
 * Memory map allowing access to the GIC virtual CPU interface control registers for CPU4 from any processor. Contains all registers with the GICH prefix. Note: This provides a means for other processors to access the virtual CPU interface control registers for CPU4. It is expected that this block will only be made accessible to hypervisors.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_HCR  VTSS_IOREG(VTSS_TO_GIC400,0x1600)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_VTR  VTSS_IOREG(VTSS_TO_GIC400,0x1601)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_VMCR  VTSS_IOREG(VTSS_TO_GIC400,0x1602)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_MISR  VTSS_IOREG(VTSS_TO_GIC400,0x1604)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_EISR0  VTSS_IOREG(VTSS_TO_GIC400,0x1608)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_ELSR0  VTSS_IOREG(VTSS_TO_GIC400,0x160c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_APR0  VTSS_IOREG(VTSS_TO_GIC400,0x163c)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_LR0  VTSS_IOREG(VTSS_TO_GIC400,0x1640)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_LR1  VTSS_IOREG(VTSS_TO_GIC400,0x1641)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_LR2  VTSS_IOREG(VTSS_TO_GIC400,0x1642)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS4:VCPUIFHYPALIAS4_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYPALIAS4_GICH_LR3  VTSS_IOREG(VTSS_TO_GIC400,0x1643)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS4_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS4_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS4_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS4_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFHYPALIAS5
 *
 * Memory map allowing access to the GIC virtual CPU interface control registers for CPU5 from any processor. Contains all registers with the GICH prefix. Note: This provides a means for other processors to access the virtual CPU interface control registers for CPU5. It is expected that this block will only be made accessible to hypervisors.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_HCR  VTSS_IOREG(VTSS_TO_GIC400,0x1680)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_VTR  VTSS_IOREG(VTSS_TO_GIC400,0x1681)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_VMCR  VTSS_IOREG(VTSS_TO_GIC400,0x1682)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_MISR  VTSS_IOREG(VTSS_TO_GIC400,0x1684)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_EISR0  VTSS_IOREG(VTSS_TO_GIC400,0x1688)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_ELSR0  VTSS_IOREG(VTSS_TO_GIC400,0x168c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_APR0  VTSS_IOREG(VTSS_TO_GIC400,0x16bc)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_LR0  VTSS_IOREG(VTSS_TO_GIC400,0x16c0)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_LR1  VTSS_IOREG(VTSS_TO_GIC400,0x16c1)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_LR2  VTSS_IOREG(VTSS_TO_GIC400,0x16c2)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS5:VCPUIFHYPALIAS5_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYPALIAS5_GICH_LR3  VTSS_IOREG(VTSS_TO_GIC400,0x16c3)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS5_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS5_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS5_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS5_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFHYPALIAS6
 *
 * Memory map allowing access to the GIC virtual CPU interface control registers for CPU6 from any processor. Contains all registers with the GICH prefix. Note: This provides a means for other processors to access the virtual CPU interface control registers for CPU6. It is expected that this block will only be made accessible to hypervisors.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_HCR  VTSS_IOREG(VTSS_TO_GIC400,0x1700)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_VTR  VTSS_IOREG(VTSS_TO_GIC400,0x1701)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_VMCR  VTSS_IOREG(VTSS_TO_GIC400,0x1702)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_MISR  VTSS_IOREG(VTSS_TO_GIC400,0x1704)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_EISR0  VTSS_IOREG(VTSS_TO_GIC400,0x1708)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_ELSR0  VTSS_IOREG(VTSS_TO_GIC400,0x170c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_APR0  VTSS_IOREG(VTSS_TO_GIC400,0x173c)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_LR0  VTSS_IOREG(VTSS_TO_GIC400,0x1740)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_LR1  VTSS_IOREG(VTSS_TO_GIC400,0x1741)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_LR2  VTSS_IOREG(VTSS_TO_GIC400,0x1742)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS6:VCPUIFHYPALIAS6_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYPALIAS6_GICH_LR3  VTSS_IOREG(VTSS_TO_GIC400,0x1743)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS6_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS6_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS6_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS6_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFHYPALIAS7
 *
 * Memory map allowing access to the GIC virtual CPU interface control registers for CPU7 from any processor. Contains all registers with the GICH prefix. Note: This provides a means for other processors to access the virtual CPU interface control registers for CPU7. It is expected that this block will only be made accessible to hypervisors.
 */


/**
 * \brief Hypervisor Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_HCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_HCR  VTSS_IOREG(VTSS_TO_GIC400,0x1780)

/**
 * \brief
 * Hypervisor Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_HCR . GICH_HCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_HCR_GICH_HCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_HCR_GICH_HCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_HCR_GICH_HCR(x)  (x)


/**
 * \brief VGIC Type Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_VTR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_VTR  VTSS_IOREG(VTSS_TO_GIC400,0x1781)

/**
 * \brief
 * VGIC Type Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_VTR . GICH_VTR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_VTR_GICH_VTR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_VTR_GICH_VTR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_VTR_GICH_VTR(x)  (x)


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_VMCR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_VMCR  VTSS_IOREG(VTSS_TO_GIC400,0x1782)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_VMCR . GICH_VMCR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_VMCR_GICH_VMCR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_VMCR_GICH_VMCR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_VMCR_GICH_VMCR(x)  (x)


/**
 * \brief Maintenance Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_MISR
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_MISR  VTSS_IOREG(VTSS_TO_GIC400,0x1784)

/**
 * \brief
 * Maintenance Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_MISR . GICH_MISR
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_MISR_GICH_MISR(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_MISR_GICH_MISR     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_MISR_GICH_MISR(x)  (x)


/**
 * \brief End of Interrupt Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_EISR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_EISR0  VTSS_IOREG(VTSS_TO_GIC400,0x1788)

/**
 * \brief
 * End of Interrupt Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_EISR0 . GICH_EISR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_EISR0_GICH_EISR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_EISR0_GICH_EISR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_EISR0_GICH_EISR0(x)  (x)


/**
 * \brief Empty List register Status Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_ELSR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_ELSR0  VTSS_IOREG(VTSS_TO_GIC400,0x178c)

/**
 * \brief
 * Empty List register Status Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_ELSR0 . GICH_ELSR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_ELSR0_GICH_ELSR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_ELSR0_GICH_ELSR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_ELSR0_GICH_ELSR0(x)  (x)


/**
 * \brief Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_APR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_APR0  VTSS_IOREG(VTSS_TO_GIC400,0x17bc)

/**
 * \brief
 * Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_APR0 . GICH_APR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_APR0_GICH_APR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_APR0_GICH_APR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_APR0_GICH_APR0(x)  (x)


/**
 * \brief List Register 0
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_LR0
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_LR0  VTSS_IOREG(VTSS_TO_GIC400,0x17c0)

/**
 * \brief
 * List Register 0
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_LR0 . GICH_LR0
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_LR0_GICH_LR0(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_LR0_GICH_LR0     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_LR0_GICH_LR0(x)  (x)


/**
 * \brief List Register 1
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_LR1
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_LR1  VTSS_IOREG(VTSS_TO_GIC400,0x17c1)

/**
 * \brief
 * List Register 1
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_LR1 . GICH_LR1
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_LR1_GICH_LR1(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_LR1_GICH_LR1     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_LR1_GICH_LR1(x)  (x)


/**
 * \brief List Register 2
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_LR2
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_LR2  VTSS_IOREG(VTSS_TO_GIC400,0x17c2)

/**
 * \brief
 * List Register 2
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_LR2 . GICH_LR2
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_LR2_GICH_LR2(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_LR2_GICH_LR2     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_LR2_GICH_LR2(x)  (x)


/**
 * \brief List Register 3
 *
 * \details
 * Register: \a GIC400:VCPUIFHYPALIAS7:VCPUIFHYPALIAS7_GICH_LR3
 */
#define VTSS_GIC400_VCPUIFHYPALIAS7_GICH_LR3  VTSS_IOREG(VTSS_TO_GIC400,0x17c3)

/**
 * \brief
 * List Register 3
 *
 * \details
 * Field: ::VTSS_GIC400_VCPUIFHYPALIAS7_GICH_LR3 . GICH_LR3
 */
#define  VTSS_F_GIC400_VCPUIFHYPALIAS7_GICH_LR3_GICH_LR3(x)  (x)
#define  VTSS_M_GIC400_VCPUIFHYPALIAS7_GICH_LR3_GICH_LR3     0xffffffff
#define  VTSS_X_GIC400_VCPUIFHYPALIAS7_GICH_LR3_GICH_LR3(x)  (x)

/**
 * Register Group: \a GIC400:VCPUIFVM
 *
 * Memory map for the GIC virtual CPU interface. Contains all registers with the GICV prefix. Note: This provides access to the virtual CPU interface for the current CPU. It is expected that software will use the translation tables to make this block accessible to the virtual machine in the address space normall used for the (physical) CPU interface.
 */


/**
 * \brief Virtual Machine Control Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_CTLR
 */
#define VTSS_GIC400_GICV_CTLR                VTSS_IOREG(VTSS_TO_GIC400,0x1800)

/**
 * \brief
 * Virtual Machine Control Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_CTLR . GICV_CTLR
 */
#define  VTSS_F_GIC400_GICV_CTLR_GICV_CTLR(x)  (x)
#define  VTSS_M_GIC400_GICV_CTLR_GICV_CTLR     0xffffffff
#define  VTSS_X_GIC400_GICV_CTLR_GICV_CTLR(x)  (x)


/**
 * \brief VM Priority Mask Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_PMR
 */
#define VTSS_GIC400_GICV_PMR                 VTSS_IOREG(VTSS_TO_GIC400,0x1801)

/**
 * \brief
 * VM Priority Mask Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_PMR . GICV_PMR
 */
#define  VTSS_F_GIC400_GICV_PMR_GICV_PMR(x)   (x)
#define  VTSS_M_GIC400_GICV_PMR_GICV_PMR      0xffffffff
#define  VTSS_X_GIC400_GICV_PMR_GICV_PMR(x)   (x)


/**
 * \brief VM Binary Point Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_BPR
 */
#define VTSS_GIC400_GICV_BPR                 VTSS_IOREG(VTSS_TO_GIC400,0x1802)

/**
 * \brief
 * VM Binary Point Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_BPR . GICV_BPR
 */
#define  VTSS_F_GIC400_GICV_BPR_GICV_BPR(x)   (x)
#define  VTSS_M_GIC400_GICV_BPR_GICV_BPR      0xffffffff
#define  VTSS_X_GIC400_GICV_BPR_GICV_BPR(x)   (x)


/**
 * \brief VM Interrupt Acknowledge Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_IAR
 */
#define VTSS_GIC400_GICV_IAR                 VTSS_IOREG(VTSS_TO_GIC400,0x1803)

/**
 * \brief
 * VM Interrupt Acknowledge Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_IAR . GICV_IAR
 */
#define  VTSS_F_GIC400_GICV_IAR_GICV_IAR(x)   (x)
#define  VTSS_M_GIC400_GICV_IAR_GICV_IAR      0xffffffff
#define  VTSS_X_GIC400_GICV_IAR_GICV_IAR(x)   (x)


/**
 * \brief VM End of Interrupt Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_EOIR
 */
#define VTSS_GIC400_GICV_EOIR                VTSS_IOREG(VTSS_TO_GIC400,0x1804)

/**
 * \brief
 * VM End of Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_EOIR . GICV_EOIR
 */
#define  VTSS_F_GIC400_GICV_EOIR_GICV_EOIR(x)  (x)
#define  VTSS_M_GIC400_GICV_EOIR_GICV_EOIR     0xffffffff
#define  VTSS_X_GIC400_GICV_EOIR_GICV_EOIR(x)  (x)


/**
 * \brief VM Running Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_RPR
 */
#define VTSS_GIC400_GICV_RPR                 VTSS_IOREG(VTSS_TO_GIC400,0x1805)

/**
 * \brief
 * VM Running Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_RPR . GICV_RPR
 */
#define  VTSS_F_GIC400_GICV_RPR_GICV_RPR(x)   (x)
#define  VTSS_M_GIC400_GICV_RPR_GICV_RPR      0xffffffff
#define  VTSS_X_GIC400_GICV_RPR_GICV_RPR(x)   (x)


/**
 * \brief VM Highest Priority Pending Interrupt Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_HPPIR
 */
#define VTSS_GIC400_GICV_HPPIR               VTSS_IOREG(VTSS_TO_GIC400,0x1806)

/**
 * \brief
 * VM Highest Priority Pending Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_HPPIR . GICV_HPPIR
 */
#define  VTSS_F_GIC400_GICV_HPPIR_GICV_HPPIR(x)  (x)
#define  VTSS_M_GIC400_GICV_HPPIR_GICV_HPPIR     0xffffffff
#define  VTSS_X_GIC400_GICV_HPPIR_GICV_HPPIR(x)  (x)


/**
 * \brief VM Aliased Binary Point Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_ABPR
 */
#define VTSS_GIC400_GICV_ABPR                VTSS_IOREG(VTSS_TO_GIC400,0x1807)

/**
 * \brief
 * VM Aliased Binary Point Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_ABPR . GICV_ABPR
 */
#define  VTSS_F_GIC400_GICV_ABPR_GICV_ABPR(x)  (x)
#define  VTSS_M_GIC400_GICV_ABPR_GICV_ABPR     0xffffffff
#define  VTSS_X_GIC400_GICV_ABPR_GICV_ABPR(x)  (x)


/**
 * \brief VM Aliased Interrupt Acknowledge Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_AIAR
 */
#define VTSS_GIC400_GICV_AIAR                VTSS_IOREG(VTSS_TO_GIC400,0x1808)

/**
 * \brief
 * VM Aliased Interrupt Acknowledge Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_AIAR . GICV_AIAR
 */
#define  VTSS_F_GIC400_GICV_AIAR_GICV_AIAR(x)  (x)
#define  VTSS_M_GIC400_GICV_AIAR_GICV_AIAR     0xffffffff
#define  VTSS_X_GIC400_GICV_AIAR_GICV_AIAR(x)  (x)


/**
 * \brief VM Aliased End of Interrupt Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_AEOIR
 */
#define VTSS_GIC400_GICV_AEOIR               VTSS_IOREG(VTSS_TO_GIC400,0x1809)

/**
 * \brief
 * VM Aliased End of Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_AEOIR . GICV_AEOIR
 */
#define  VTSS_F_GIC400_GICV_AEOIR_GICV_AEOIR(x)  (x)
#define  VTSS_M_GIC400_GICV_AEOIR_GICV_AEOIR     0xffffffff
#define  VTSS_X_GIC400_GICV_AEOIR_GICV_AEOIR(x)  (x)


/**
 * \brief VM Aliased Highest Priority Pending Interrupt Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_AHPPIR
 */
#define VTSS_GIC400_GICV_AHPPIR              VTSS_IOREG(VTSS_TO_GIC400,0x180a)

/**
 * \brief
 * VM Aliased Highest Priority Pending Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_AHPPIR . GICV_AHPPIR
 */
#define  VTSS_F_GIC400_GICV_AHPPIR_GICV_AHPPIR(x)  (x)
#define  VTSS_M_GIC400_GICV_AHPPIR_GICV_AHPPIR     0xffffffff
#define  VTSS_X_GIC400_GICV_AHPPIR_GICV_AHPPIR(x)  (x)


/**
 * \brief VM Active Priority Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_APR0
 */
#define VTSS_GIC400_GICV_APR0                VTSS_IOREG(VTSS_TO_GIC400,0x1834)

/**
 * \brief
 * VM Active Priority Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_APR0 . GICV_APR0
 */
#define  VTSS_F_GIC400_GICV_APR0_GICV_APR0(x)  (x)
#define  VTSS_M_GIC400_GICV_APR0_GICV_APR0     0xffffffff
#define  VTSS_X_GIC400_GICV_APR0_GICV_APR0(x)  (x)


/**
 * \brief VM CPU Interface Identification Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_IIDR
 */
#define VTSS_GIC400_GICV_IIDR                VTSS_IOREG(VTSS_TO_GIC400,0x183f)

/**
 * \brief
 * VM CPU Interface Identification Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_IIDR . GICV_IIDR
 */
#define  VTSS_F_GIC400_GICV_IIDR_GICV_IIDR(x)  (x)
#define  VTSS_M_GIC400_GICV_IIDR_GICV_IIDR     0xffffffff
#define  VTSS_X_GIC400_GICV_IIDR_GICV_IIDR(x)  (x)


/**
 * \brief VM Deactivate Interrupt Register
 *
 * \details
 * Register: \a GIC400:VCPUIFVM:GICV_DIR
 */
#define VTSS_GIC400_GICV_DIR                 VTSS_IOREG(VTSS_TO_GIC400,0x1c00)

/**
 * \brief
 * VM Deactivate Interrupt Register
 *
 * \details
 * Field: ::VTSS_GIC400_GICV_DIR . GICV_DIR
 */
#define  VTSS_F_GIC400_GICV_DIR_GICV_DIR(x)   (x)
#define  VTSS_M_GIC400_GICV_DIR_GICV_DIR      0xffffffff
#define  VTSS_X_GIC400_GICV_DIR_GICV_DIR(x)   (x)


#endif /* _VTSS_LAGUNA_REGS_GIC400_H_ */
