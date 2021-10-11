// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_AESB_ASC_H_
#define _VTSS_LAGUNA_REGS_AESB_ASC_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a AESB_ASC
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a AESB_ASC:AESB_ASC_REGS
 *
 * Not documented
 */


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Base Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RBAR0
 */
#define VTSS_AESB_ASC_TZAESBASC_RBAR0        VTSS_IOREG(VTSS_TO_AESB_ASC,0x0)

/**
 * \brief
 * BASE: Region x Base AddressBase Address bits [MSB_NOT_USED_ADDR:0] are
 * always 0 because a region size granularity is GRANULARITY_SIZEKbytes.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RBAR0 . BASE0
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RBAR0_BASE0(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RBAR0_BASE0     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RBAR0_BASE0(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Top Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RTAR0
 */
#define VTSS_AESB_ASC_TZAESBASC_RTAR0        VTSS_IOREG(VTSS_TO_AESB_ASC,0x1)

/**
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RTAR0 . TOP0
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RTAR0_TOP0(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RTAR0_TOP0     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RTAR0_TOP0(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Base Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RBAR1
 */
#define VTSS_AESB_ASC_TZAESBASC_RBAR1        VTSS_IOREG(VTSS_TO_AESB_ASC,0x2)

/**
 * \brief
 * BASE: Region x Base AddressBase Address bits [MSB_NOT_USED_ADDR:0] are
 * always 0 because a region size granularity is GRANULARITY_SIZEKbytes.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RBAR1 . BASE1
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RBAR1_BASE1(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RBAR1_BASE1     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RBAR1_BASE1(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Top Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RTAR1
 */
#define VTSS_AESB_ASC_TZAESBASC_RTAR1        VTSS_IOREG(VTSS_TO_AESB_ASC,0x3)

/**
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RTAR1 . TOP1
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RTAR1_TOP1(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RTAR1_TOP1     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RTAR1_TOP1(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Base Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RBAR2
 */
#define VTSS_AESB_ASC_TZAESBASC_RBAR2        VTSS_IOREG(VTSS_TO_AESB_ASC,0x4)

/**
 * \brief
 * BASE: Region x Base AddressBase Address bits [MSB_NOT_USED_ADDR:0] are
 * always 0 because a region size granularity is GRANULARITY_SIZEKbytes.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RBAR2 . BASE2
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RBAR2_BASE2(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RBAR2_BASE2     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RBAR2_BASE2(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Top Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RTAR2
 */
#define VTSS_AESB_ASC_TZAESBASC_RTAR2        VTSS_IOREG(VTSS_TO_AESB_ASC,0x5)

/**
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RTAR2 . TOP2
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RTAR2_TOP2(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RTAR2_TOP2     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RTAR2_TOP2(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Base Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RBAR3
 */
#define VTSS_AESB_ASC_TZAESBASC_RBAR3        VTSS_IOREG(VTSS_TO_AESB_ASC,0x6)

/**
 * \brief
 * BASE: Region x Base AddressBase Address bits [MSB_NOT_USED_ADDR:0] are
 * always 0 because a region size granularity is GRANULARITY_SIZEKbytes.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RBAR3 . BASE3
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RBAR3_BASE3(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RBAR3_BASE3     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RBAR3_BASE3(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Top Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RTAR3
 */
#define VTSS_AESB_ASC_TZAESBASC_RTAR3        VTSS_IOREG(VTSS_TO_AESB_ASC,0x7)

/**
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RTAR3 . TOP3
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RTAR3_TOP3(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RTAR3_TOP3     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RTAR3_TOP3(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Base Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RBAR4
 */
#define VTSS_AESB_ASC_TZAESBASC_RBAR4        VTSS_IOREG(VTSS_TO_AESB_ASC,0x8)

/**
 * \brief
 * BASE: Region x Base AddressBase Address bits [MSB_NOT_USED_ADDR:0] are
 * always 0 because a region size granularity is GRANULARITY_SIZEKbytes.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RBAR4 . BASE4
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RBAR4_BASE4(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RBAR4_BASE4     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RBAR4_BASE4(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Top Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RTAR4
 */
#define VTSS_AESB_ASC_TZAESBASC_RTAR4        VTSS_IOREG(VTSS_TO_AESB_ASC,0x9)

/**
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RTAR4 . TOP4
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RTAR4_TOP4(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RTAR4_TOP4     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RTAR4_TOP4(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Base Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RBAR5
 */
#define VTSS_AESB_ASC_TZAESBASC_RBAR5        VTSS_IOREG(VTSS_TO_AESB_ASC,0xa)

/**
 * \brief
 * BASE: Region x Base AddressBase Address bits [MSB_NOT_USED_ADDR:0] are
 * always 0 because a region size granularity is GRANULARITY_SIZEKbytes.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RBAR5 . BASE5
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RBAR5_BASE5(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RBAR5_BASE5     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RBAR5_BASE5(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Top Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RTAR5
 */
#define VTSS_AESB_ASC_TZAESBASC_RTAR5        VTSS_IOREG(VTSS_TO_AESB_ASC,0xb)

/**
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RTAR5 . TOP5
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RTAR5_TOP5(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RTAR5_TOP5     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RTAR5_TOP5(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Base Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RBAR6
 */
#define VTSS_AESB_ASC_TZAESBASC_RBAR6        VTSS_IOREG(VTSS_TO_AESB_ASC,0xc)

/**
 * \brief
 * BASE: Region x Base AddressBase Address bits [MSB_NOT_USED_ADDR:0] are
 * always 0 because a region size granularity is GRANULARITY_SIZEKbytes.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RBAR6 . BASE6
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RBAR6_BASE6(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RBAR6_BASE6     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RBAR6_BASE6(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Top Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RTAR6
 */
#define VTSS_AESB_ASC_TZAESBASC_RTAR6        VTSS_IOREG(VTSS_TO_AESB_ASC,0xd)

/**
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RTAR6 . TOP6
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RTAR6_TOP6(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RTAR6_TOP6     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RTAR6_TOP6(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Base Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RBAR7
 */
#define VTSS_AESB_ASC_TZAESBASC_RBAR7        VTSS_IOREG(VTSS_TO_AESB_ASC,0xe)

/**
 * \brief
 * BASE: Region x Base AddressBase Address bits [MSB_NOT_USED_ADDR:0] are
 * always 0 because a region size granularity is GRANULARITY_SIZEKbytes.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RBAR7 . BASE7
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RBAR7_BASE7(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RBAR7_BASE7     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RBAR7_BASE7(x)  (x)


/**
 * \brief TZAESBASC Region x [x = 0 .. NB_REGION_M1] Top Address Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RTAR7
 */
#define VTSS_AESB_ASC_TZAESBASC_RTAR7        VTSS_IOREG(VTSS_TO_AESB_ASC,0xf)

/**
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RTAR7 . TOP7
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RTAR7_TOP7(x)  (x)
#define  VTSS_M_AESB_ASC_TZAESBASC_RTAR7_TOP7     0xffffffff
#define  VTSS_X_AESB_ASC_TZAESBASC_RTAR7_TOP7(x)  (x)


/**
 * \brief TZAESBASC Region Security Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RSECR
 */
#define VTSS_AESB_ASC_TZAESBASC_RSECR        VTSS_IOREG(VTSS_TO_AESB_ASC,0x20)

/**
 * \brief
 * SECx: Region x Security (x is 0 to 7)0: Region x is secure.1: Region x
 * is non-secure.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RSECR . SECX
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RSECR_SECX(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AESB_ASC_TZAESBASC_RSECR_SECX     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AESB_ASC_TZAESBASC_RSECR_SECX(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TZAESBASC Region Enable Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RER
 */
#define VTSS_AESB_ASC_TZAESBASC_RER          VTSS_IOREG(VTSS_TO_AESB_ASC,0x21)

/**
 * \brief
 * ENx: Region x Enable0: No effect.1: Enables the corresponding region.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RER . ENX
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RER_ENX(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AESB_ASC_TZAESBASC_RER_ENX     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AESB_ASC_TZAESBASC_RER_ENX(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TZAESBASC Region Disable Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RDR
 */
#define VTSS_AESB_ASC_TZAESBASC_RDR          VTSS_IOREG(VTSS_TO_AESB_ASC,0x22)

/**
 * \brief
 * DISx: Region x Disable0: No effect.1: Disables the corresponding region.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RDR . DISX
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RDR_DISX(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AESB_ASC_TZAESBASC_RDR_DISX     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AESB_ASC_TZAESBASC_RDR_DISX(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TZAESBASC Region Status Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RSR
 */
#define VTSS_AESB_ASC_TZAESBASC_RSR          VTSS_IOREG(VTSS_TO_AESB_ASC,0x23)

/**
 * \brief
 * ESx: Region x Enable Status0: The corresponding region is disabled.1:
 * The corresponding region is enabled.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RSR . ESX
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RSR_ESX(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AESB_ASC_TZAESBASC_RSR_ESX     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AESB_ASC_TZAESBASC_RSR_ESX(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TZAESBASC Region Error Status Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RESR
 */
#define VTSS_AESB_ASC_TZAESBASC_RESR         VTSS_IOREG(VTSS_TO_AESB_ASC,0x24)

/**
 * \brief
 * AERx: Region x Address Error0: No region x address error has occurred.1:
 * A region x address error has occurred since the last read of the Region
 * Error Status register.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RESR . AERX
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RESR_AERX(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AESB_ASC_TZAESBASC_RESR_AERX     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AESB_ASC_TZAESBASC_RESR_AERX(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TZAESBASC Region Synchronization Status Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_RSSR
 */
#define VTSS_AESB_ASC_TZAESBASC_RSSR         VTSS_IOREG(VTSS_TO_AESB_ASC,0x25)

/**
 * \brief
 * SYNC: Region Synchronization Status0: Synchronization of the region
 * configuration is done.1: A region configuration is in progress.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_RSSR . SYNC
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_RSSR_SYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AESB_ASC_TZAESBASC_RSSR_SYNC  VTSS_BIT(0)
#define  VTSS_X_AESB_ASC_TZAESBASC_RSSR_SYNC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TZAESBASC Write Protection Mode Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_WPMR
 */
#define VTSS_AESB_ASC_TZAESBASC_WPMR         VTSS_IOREG(VTSS_TO_AESB_ASC,0x39)

/**
 * \brief
 * WPKEY: Write Protection KeyValue Name Description0x415343 PASSWD Writing
 * any other value in this field aborts the write operation of the WPEN
 * bit. Always reads at 0.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_WPMR . WPKEY
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_WPMR_WPKEY(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_AESB_ASC_TZAESBASC_WPMR_WPKEY     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_AESB_ASC_TZAESBASC_WPMR_WPKEY(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * WPEN: Write Protection Enable0: Disables the write protection if WPKEY
 * corresponds to 0x415343 (ASC in ASCII).1: Enables the write protection.
 * All accesses to configuration registers are cancelled and generate an
 * error in theTZAESBASC_WPSR register.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_WPMR . WPEN
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_WPMR_WPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AESB_ASC_TZAESBASC_WPMR_WPEN  VTSS_BIT(0)
#define  VTSS_X_AESB_ASC_TZAESBASC_WPMR_WPEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TZAESBASC Write Protection Status Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_WPSR
 */
#define VTSS_AESB_ASC_TZAESBASC_WPSR         VTSS_IOREG(VTSS_TO_AESB_ASC,0x3a)

/**
 * \brief
 * WPSRC: Write Protection SourceWhen WPVS = 1, WPSRC indicates the
 * register address offset at which a write access has been attempted
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_WPSR . WPSRC
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_WPSR_WPSRC(x)  VTSS_ENCODE_BITFIELD(x,8,16)
#define  VTSS_M_AESB_ASC_TZAESBASC_WPSR_WPSRC     VTSS_ENCODE_BITMASK(8,16)
#define  VTSS_X_AESB_ASC_TZAESBASC_WPSR_WPSRC(x)  VTSS_EXTRACT_BITFIELD(x,8,16)

/**
 * \brief
 * WPVS: Write Protection Violation Status0: No write protection violation
 * has occurred since the last read of TZAESBASC_WPSR.1: A write protection
 * violation has occurred since the last read of TZAESBASC_WPSR. If this
 * violation is an unauthorizedattempt to write a protected register, the
 * associated violation is reported into field WPSRC.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_WPSR . WPVS
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_WPSR_WPVS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AESB_ASC_TZAESBASC_WPSR_WPVS  VTSS_BIT(0)
#define  VTSS_X_AESB_ASC_TZAESBASC_WPSR_WPVS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TZAESBASC Version Register
 *
 * \details
 * Register: \a AESB_ASC:AESB_ASC_REGS:TZAESBASC_VERSION
 */
#define VTSS_AESB_ASC_TZAESBASC_VERSION      VTSS_IOREG(VTSS_TO_AESB_ASC,0x3f)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_VERSION . MFN
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_VERSION_MFN(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_AESB_ASC_TZAESBASC_VERSION_MFN     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_AESB_ASC_TZAESBASC_VERSION_MFN(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the internal version of the
 * macrocell.
 *
 * \details
 * Field: ::VTSS_AESB_ASC_TZAESBASC_VERSION . VERSION
 */
#define  VTSS_F_AESB_ASC_TZAESBASC_VERSION_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_AESB_ASC_TZAESBASC_VERSION_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_AESB_ASC_TZAESBASC_VERSION_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_AESB_ASC_H_ */
