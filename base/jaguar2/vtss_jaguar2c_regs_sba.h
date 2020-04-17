// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2C_REGS_SBA_H_
#define _VTSS_JAGUAR2C_REGS_SBA_H_


#include "vtss_jaguar2c_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a SBA
 *
 * Shared Bus Arbiter
 *
 ***********************************************************************/

/**
 * Register Group: \a SBA:SBA
 *
 * Shared bus arbiter registers
 */


/** 
 * \brief Master 1 arbitration priority
 *
 * \details
 * Register: \a SBA:SBA:PL_CPU
 */
#define VTSS_SBA_SBA_PL_CPU                  VTSS_IOREG(VTSS_TO_SBA,0x0)

/** 
 * \brief
 * Arbitration priority for the master. When multiple masters request the
 * bus at the same time, the one with the highest priority is ganted bus
 * access.
 *
 * \details 
 * Values 0x1 through 0xF, higher values are prioritized over lower values.
 *
 * Field: ::VTSS_SBA_SBA_PL_CPU . PL1
 */
#define  VTSS_F_SBA_SBA_PL_CPU_PL1(x)         VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SBA_SBA_PL_CPU_PL1            VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SBA_SBA_PL_CPU_PL1(x)         VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Master 2 arbitration priority
 *
 * \details
 * Register: \a SBA:SBA:PL_PCIE
 */
#define VTSS_SBA_SBA_PL_PCIE                 VTSS_IOREG(VTSS_TO_SBA,0x1)

/** 
 * \brief
 * See SBA::PL1 for description.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_PL_PCIE . PL2
 */
#define  VTSS_F_SBA_SBA_PL_PCIE_PL2(x)        VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SBA_SBA_PL_PCIE_PL2           VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SBA_SBA_PL_PCIE_PL2(x)        VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Master 3 arbitration priority
 *
 * \details
 * Register: \a SBA:SBA:PL_CSR
 */
#define VTSS_SBA_SBA_PL_CSR                  VTSS_IOREG(VTSS_TO_SBA,0x2)

/** 
 * \brief
 * See SBA::PL1 for description.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_PL_CSR . PL3
 */
#define  VTSS_F_SBA_SBA_PL_CSR_PL3(x)         VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SBA_SBA_PL_CSR_PL3            VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SBA_SBA_PL_CSR_PL3(x)         VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a SBA:SBA:RESERVED1
 *
 * @param ri Register: RESERVED1 (??), 0-11
 */
#define VTSS_SBA_SBA_RESERVED1(ri)           VTSS_IOREG(VTSS_TO_SBA,0x3 + (ri))

/** 
 * \details 
 * Field: ::VTSS_SBA_SBA_RESERVED1 . RESERVED1
 */
#define  VTSS_F_SBA_SBA_RESERVED1_RESERVED1(x)  (x)
#define  VTSS_M_SBA_SBA_RESERVED1_RESERVED1     0xffffffff
#define  VTSS_X_SBA_SBA_RESERVED1_RESERVED1(x)  (x)


/** 
 * \brief Early burst termination count
 *
 * \details
 * Register: \a SBA:SBA:EBT_COUNT
 */
#define VTSS_SBA_SBA_EBT_COUNT               VTSS_IOREG(VTSS_TO_SBA,0xf)

/** 
 * \brief
 * Maximum number of cycles a transfer can take before being subject to an
 * early burst termination.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_EBT_COUNT . EBT_COUNT
 */
#define  VTSS_F_SBA_SBA_EBT_COUNT_EBT_COUNT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SBA_SBA_EBT_COUNT_EBT_COUNT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SBA_SBA_EBT_COUNT_EBT_COUNT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Early burst termination enable
 *
 * \details
 * Register: \a SBA:SBA:EBT_EN
 */
#define VTSS_SBA_SBA_EBT_EN                  VTSS_IOREG(VTSS_TO_SBA,0x10)

/** 
 * \brief
 * Use this field to enable early burst termination.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_SBA_SBA_EBT_EN . EBT_EN
 */
#define  VTSS_F_SBA_SBA_EBT_EN_EBT_EN(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SBA_SBA_EBT_EN_EBT_EN         VTSS_BIT(0)
#define  VTSS_X_SBA_SBA_EBT_EN_EBT_EN(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Early burst termination
 *
 * \details
 * Register: \a SBA:SBA:EBT
 */
#define VTSS_SBA_SBA_EBT                     VTSS_IOREG(VTSS_TO_SBA,0x11)

/** 
 * \brief
 * Set when an Early Burst Termination takes place. The register is cleared
 * when read.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_EBT . EBT
 */
#define  VTSS_F_SBA_SBA_EBT_EBT(x)            VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SBA_SBA_EBT_EBT               VTSS_BIT(0)
#define  VTSS_X_SBA_SBA_EBT_EBT(x)            VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Default master
 *
 * \details
 * The default master is selected by the bus when no master has requested
 * ownership. The default master is able to start bus accesses slightly
 * faster than other masters.
 *
 * Register: \a SBA:SBA:DFT_MST
 */
#define VTSS_SBA_SBA_DFT_MST                 VTSS_IOREG(VTSS_TO_SBA,0x12)

/** 
 * \brief
 * Use this field to configure default master.
 *
 * \details 
 * 0: No default master
 * 1: Master 1
 * 2: Master 2
 * 3: Master 3
 *
 * Field: ::VTSS_SBA_SBA_DFT_MST . DFT_MST
 */
#define  VTSS_F_SBA_SBA_DFT_MST_DFT_MST(x)    VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SBA_SBA_DFT_MST_DFT_MST       VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SBA_SBA_DFT_MST_DFT_MST(x)    VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Weighted-token arbitration scheme enable
 *
 * \details
 * When weighted token arbitration is enabled, each master on the shared
 * bus is granted a configurable number of tokens at the start of each
 * refresh period. The length of each refresh period is configurable. In
 * each clock-cycle that a master uses the bus, the token counter for that
 * master decreases. Once all tokens are spent, the master is forced to a
 * low priority. A master with tokens remaining, always takes priority over
 * masters with no tokens remaining.
 *
 * Register: \a SBA:SBA:WT_EN
 */
#define VTSS_SBA_SBA_WT_EN                   VTSS_IOREG(VTSS_TO_SBA,0x13)

/** 
 * \brief
 * Set this field to enable weighted-token arbitration scheme.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_WT_EN . WT_EN
 */
#define  VTSS_F_SBA_SBA_WT_EN_WT_EN(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SBA_SBA_WT_EN_WT_EN           VTSS_BIT(0)
#define  VTSS_X_SBA_SBA_WT_EN_WT_EN(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clock tokens refresh period
 *
 * \details
 * Register: \a SBA:SBA:WT_TCL
 */
#define VTSS_SBA_SBA_WT_TCL                  VTSS_IOREG(VTSS_TO_SBA,0x14)

/** 
 * \brief
 * Refresh period length for the weighted-token arbitration scheme.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_WT_TCL . WT_TCL
 */
#define  VTSS_F_SBA_SBA_WT_TCL_WT_TCL(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SBA_SBA_WT_TCL_WT_TCL         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SBA_SBA_WT_TCL_WT_TCL(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Master 1 clock tokens
 *
 * \details
 * Register: \a SBA:SBA:WT_CPU
 */
#define VTSS_SBA_SBA_WT_CPU                  VTSS_IOREG(VTSS_TO_SBA,0x15)

/** 
 * \brief
 * Number of tokens to grant the master at the start of each refresh period
 * for weighted-token arbitration scheme. If configured with a value of
 * zero, the master is considered to have infinite tokens.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_WT_CPU . WT_CL1
 */
#define  VTSS_F_SBA_SBA_WT_CPU_WT_CL1(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SBA_SBA_WT_CPU_WT_CL1         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SBA_SBA_WT_CPU_WT_CL1(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Master 2 clock tokens
 *
 * \details
 * Register: \a SBA:SBA:WT_PCIE
 */
#define VTSS_SBA_SBA_WT_PCIE                 VTSS_IOREG(VTSS_TO_SBA,0x16)

/** 
 * \brief
 * See SBA::WT_CL1 for description.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_WT_PCIE . WT_CL2
 */
#define  VTSS_F_SBA_SBA_WT_PCIE_WT_CL2(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SBA_SBA_WT_PCIE_WT_CL2        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SBA_SBA_WT_PCIE_WT_CL2(x)     VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Master 3 clock tokens
 *
 * \details
 * Register: \a SBA:SBA:WT_CSR
 */
#define VTSS_SBA_SBA_WT_CSR                  VTSS_IOREG(VTSS_TO_SBA,0x17)

/** 
 * \brief
 * See SBA::WT_CL1 for description.
 *
 * \details 
 * Field: ::VTSS_SBA_SBA_WT_CSR . WT_CL3
 */
#define  VTSS_F_SBA_SBA_WT_CSR_WT_CL3(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SBA_SBA_WT_CSR_WT_CL3         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SBA_SBA_WT_CSR_WT_CL3(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_JAGUAR2C_REGS_SBA_H_ */
