// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_VENICE_GLOBAL32_H_
#define _VTSS_VENICE_REGS_VENICE_GLOBAL32_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a VENICE_GLOBAL32
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a VENICE_GLOBAL32:F2DF_DES
 *
 * F2DF DES Configuration and Status Register set
 */


/** 
 * \brief F2DF DES Configuration register 0
 *
 * \details
 * Configuration register 0 for F2DF DES.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_DES:F2DF_DES_CFG0
 */
#define VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0  VTSS_IOREG(0x1e, 1, 0xf000)

/** 
 * \brief
 * Invert output of high auxillary deserializer
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0 . DES_INV_H
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0_DES_INV_H  VTSS_BIT(7)

/** 
 * \brief
 * Invert output of low auxillary deserializer
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0 . DES_INV_L
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0_DES_INV_L  VTSS_BIT(6)

/** 
 * \brief
 * Invert output of main deserializer
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0 . DES_INV_M
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0_DES_INV_M  VTSS_BIT(5)

/** 
 * \brief
 * Interface width
 *
 * \details 
 * 0: 8
 * 1: 10
 * 2: 16 (energy efficient)
 * 3: 20 (energy efficient)
 * 4: 32
 * 5: 40
 * 6: 16 bit (fast)
 * 7: 20 bit (fast)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0 . DES_IF_MODE_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0_DES_IF_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0_DES_IF_MODE_SEL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0_DES_IF_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Auxillary deserializer channels disable.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0 . DES_VSC_DIS
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0_DES_VSC_DIS  VTSS_BIT(1)

/** 
 * \brief
 * Deserializer disable.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0 . DES_DIS
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_DES_CFG0_DES_DIS  VTSS_BIT(0)


/** 
 * \brief F2DF MOEBDIV Configuration register 0
 *
 * \details
 * Configuration register 0 for F2DF MoebiusDivider
 *
 * Register: \a VENICE_GLOBAL32:F2DF_DES:F2DF_MOEBDIV_CFG0
 */
#define VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0  VTSS_IOREG(0x1e, 1, 0xf001)

/** 
 * \brief
 * Bandwidth selection for cp/md of cdr loop when core NOT flags valid data
 * detected
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0 . MOEBDIV_BW_CDR_SEL_A
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * Bandwidth selection for cp/md of cdr loop when core flags valid data
 * detected
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0 . MOEBDIV_BW_CDR_SEL_B
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Bandwidth selection for cp/md signals towards core
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0 . MOEBDIV_BW_CORE_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * CP/MD swapping
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0 . MOEBDIV_CPMD_SWAP
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_CPMD_SWAP  VTSS_BIT(2)

/** 
 * \brief
 * MD divider enable
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0 . MOEBDIV_DIV32_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_DIV32_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Divider disable
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0 . MOEBDIV_DIS
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_DES_F2DF_MOEBDIV_CFG0_MOEBDIV_DIS  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL32:F2DF_PLACEHOLDER
 *
 * F2DF PLACEHOLDER Configuration and Status Register set
 */


/** 
 * \brief F2DF DUMMY register
 *
 * \details
 * Configuration register for F2DF PALCEHOLDER
 *
 * Register: \a VENICE_GLOBAL32:F2DF_PLACEHOLDER:F2DF_PLACEHOLDER_DUMMY
 */
#define VTSS_VENICE_GLOBAL32_F2DF_PLACEHOLDER_F2DF_PLACEHOLDER_DUMMY  VTSS_IOREG(0x1e, 1, 0xf010)

/**
 * Register Group: \a VENICE_GLOBAL32:F2DF_IB
 *
 * F2DF IB Configuration and Status Register set
 */


/** 
 * \brief F2DF IB Configuration register 0
 *
 * \details
 * Configuration register 0 for F2DF IB. Note: Configuration bit-grp
 * IB_CLKDIV_ENA was named IB_VSCOPE_CLK_ENA in an early revision of the
 * input buffer.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG0
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0  VTSS_IOREG(0x1e, 1, 0xf020)

/** 
 * \brief
 * Offset resistance adjustment for CML cells (two-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_RCML_ADJ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_RCML_ADJ(x)  VTSS_ENCODE_BITFIELD(x,27,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_RCML_ADJ     VTSS_ENCODE_BITMASK(27,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_RCML_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,27,4)

/** 
 * \brief
 * Select termination voltage
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_TERM_V_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_TERM_V_SEL(x)  VTSS_ENCODE_BITFIELD(x,23,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_TERM_V_SEL     VTSS_ENCODE_BITMASK(23,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_TERM_V_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,4)

/** 
 * \brief
 * Enable common mode termination
 *
 * \details 
 * 0: no common mode termination (only AC-common mode termination)
 * 1: termination to VDDI
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_TERM_VDD_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_TERM_VDD_ENA  VTSS_BIT(22)

/** 
 * \brief
 * Shifts resistance adjustment value ib_rib_adj by +1
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_RIB_SHIFT
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_RIB_SHIFT  VTSS_BIT(21)

/** 
 * \brief
 * Offset resistance adjustment for termination (two-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_RIB_ADJ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_RIB_ADJ(x)  VTSS_ENCODE_BITFIELD(x,17,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_RIB_ADJ     VTSS_ENCODE_BITMASK(17,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_RIB_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,17,4)

/** 
 * \brief
 * Enable DFE stage (gates IB_ISEL_DFE)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_DFE_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_DFE_ENA  VTSS_BIT(14)

/** 
 * \brief
 * Select input buffer input signal
 *
 * \details 
 * 0: normal operation
 * 1: -6dB input
 * 2: OB->IB data loop or test signal
 * 3: RESERVED
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_SIG_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_SIG_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Controls Bulk Voltage of High Speed Cells
 *
 * \details 
 * 0: High
 * 1: Low (mission mode)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_VBULK_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_VBULK_SEL  VTSS_BIT(11)

/** 
 * \brief
 * Enable for IA including ACJtag
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_IA_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_IA_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Enable for IA signal detect circuit (IB_SDET_SEL = 0 required)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_IA_SDET_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_IA_SDET_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Enable for IA signal detect circuit (IB_SDET_SEL = 1 required)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_IE_SDET_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_IE_SDET_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable for level detect circuit
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_LD_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_LD_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Enable for 1V mode
 *
 * \details 
 * 0: VDDI=1.2V
 * 1: VDDI=1.0V
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_1V_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_1V_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Enable clock dividers in sampling stag
 *
 * \details 
 * 0: Disable (use in double rate mode)
 * 1: Enable (use in full rate mode)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_CLKDIV_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_CLKDIV_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Enable VScope Path of Sampling-Stage
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_VSCOPE_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_VSCOPE_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable SAMpling stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_SAM_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_SAM_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Enable EQualiZation stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0 . IB_EQZ_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG0_IB_EQZ_ENA  VTSS_BIT(1)


/** 
 * \brief F2DF IB Configuration register 1
 *
 * \details
 * Configuration register 1 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG1
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1  VTSS_IOREG(0x1e, 1, 0xf021)

/** 
 * \brief
 * Inductor peaking of 1. stage Input buffer
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3db at 8GHz
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_AMP_L
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AMP_L(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AMP_L     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AMP_L(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer0 (over all 2. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3db at 8GHz
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_EQZ_L0
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L0(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L0     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L0(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer1 (over all 3. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3dB at 8GHz
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_EQZ_L1
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L1(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L1     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L1(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer2 (over all 4. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3dB at 8GHz
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_EQZ_L2
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L2(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L2     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_L2(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer3 (over all 5. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking >3dB at 8GHz
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_AGC_L
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AGC_L(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AGC_L     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AGC_L(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * C-gain peaking for IB-stage
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_ib
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_AMP_C
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AMP_C(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AMP_C     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_AMP_C(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage0
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es0
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_EQZ_C0
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C0(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C0     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C0(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage1
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es1
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_EQZ_C1
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C1(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C1     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C1(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage2
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es2
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1 . IB_EQZ_C2
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C2(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C2     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG1_IB_EQZ_C2(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief F2DF IB Configuration register 2
 *
 * \details
 * Configuration register 2 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG2
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2  VTSS_IOREG(0x1e, 1, 0xf022)

/** 
 * \brief
 * Gain of Input Buffer
 *
 * \details 
 * 0-511 gain adjustment only in first stage > 511 gain in first stage at
 * max.
 * 512-639 gain in 2.stage increased from 1 to 2 > 639 gain = 2
 * 640-767 gain in 3.stage increased from 1 to 2 >767 gain = 2
 * 768-895 gain in 4.stage increased from 1 to 2
 * >895 gain at max.
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2 . IB_EQZ_GAIN
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_GAIN(x)  VTSS_ENCODE_BITFIELD(x,18,10)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_GAIN     VTSS_ENCODE_BITMASK(18,10)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_GAIN(x)  VTSS_EXTRACT_BITFIELD(x,18,10)

/** 
 * \brief
 * Amplification (gain) of AGC in Input Buffer (normal operation)
 *
 * \details 
 * after gain calibration
 * 0: gain = 0.3
 * 255: gain = 1.5
 * if disp/disn is active dac function for dfe gain calibration
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2 . IB_EQZ_AGC
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_AGC(x)  VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_AGC     VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_AGC(x)  VTSS_EXTRACT_BITFIELD(x,10,8)

/** 
 * \brief
 * Offset value for IB-stage of Input Buffer
 *
 * \details 
 * 512: neutral
 * > 512: positive
 * < 512: negative
 * range +/- 600mV (low gain) to +/-30mV (high gain)
 * gain dependent offset sensitivity requiered for Base line wander
 * compensation
 * not supported in test chip
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2 . IB_EQZ_OFFSET
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_OFFSET     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG2_IB_EQZ_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief F2DF IB Configuration register 3
 *
 * \details
 * Configuration register 1 for F2DF IB. Note: the behavior of
 * IB_EQ_LD1_OFFSET changes when APC is disabled. In this case
 * IB_EQ_LD1_OFFSET directly controls the level for Level-Detect circuitry
 * 1. Coding: 0: 20mV, 1: 25mV, ... 63: 340mV.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG3
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3  VTSS_IOREG(0x1e, 1, 0xf023)

/** 
 * \brief
 * Dividing factor for SDET and LD circuits of IE.
 *
 * \details 
 * 0: 128
 * 1: 32
 * 2: 8
 * 3: 4
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_LDSD_DIVSEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_LDSD_DIVSEL(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_LDSD_DIVSEL     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_LDSD_DIVSEL(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/** 
 * \brief
 * Clock dividing factor for Signal Detect circuit of IA
 *
 * \details 
 * 0: 2
 * ...
 * 7: 256
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_SDET_CLK_DIV
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_SDET_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_SDET_CLK_DIV     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_SDET_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Force Signal-Detect output to high level
 *
 * \details 
 * 0: Normal operation
 * 1: Force sigdet high
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_SET_SDET
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_SET_SDET  VTSS_BIT(26)

/** 
 * \brief
 * Selects source of signal detect (ib_X_sdet_ena must be enabled
 * accordingly)
 *
 * \details 
 * 0: IA
 * 1: IE
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_SDET_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_SDET_SEL  VTSS_BIT(24)

/** 
 * \brief
 * Selects source of direct data path to core
 *
 * \details 
 * 0: IE
 * 1: IA
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_DIRECT_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_DIRECT_SEL  VTSS_BIT(23)

/** 
 * \brief
 * With APC enabled level offset (6bit-signed) compared to IB_EQ_LD0_LEVEL
 * for Level-Detect circuitry 1. Saturating between 20mV and 340mV. See
 * also note in register description.
 *
 * \details 
 * 0: no offset
 * 1: +5mV
 * 31: +155mV
 * 63(= -1): -5mV
 * 32(= -32): -160mV.
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_EQ_LD1_OFFSET
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_EQ_LD1_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,17,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_EQ_LD1_OFFSET     VTSS_ENCODE_BITMASK(17,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_EQ_LD1_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,17,6)

/** 
 * \brief
 * Level for Level-Detect circuitry 0.
 *
 * \details 
 * 0: 20mV
 * 1: 25mV
 * ...
 * 40: 220mV
 * ...
 * 63: 340mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_EQ_LD0_LEVEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_EQ_LD0_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,11,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_EQ_LD0_LEVEL     VTSS_ENCODE_BITMASK(11,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_EQ_LD0_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,11,6)

/** 
 * \brief
 * Threshold value for IE Signal-Detect.
 *
 * \details 
 * 0: 20mV
 * 1: 25mV
 * 2: 30mV
 * ...
 * 63: 340mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_IE_SDET_LEVEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_IE_SDET_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_IE_SDET_LEVEL     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_IE_SDET_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * Threshold value for IA Signal-Detect.
 *
 * \details 
 * 0: 0mV
 * ...
 * 8: 80mV
 * ...
 * 31: 310mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3 . IB_IA_SDET_LEVEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_IA_SDET_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_IA_SDET_LEVEL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG3_IB_IA_SDET_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief F2DF IB Configuration register 4
 *
 * \details
 * Configuration register 4 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG4
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4  VTSS_IOREG(0x1e, 1, 0xf024)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 1.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_EQZ_C_ADJ_IB
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_IB(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_IB     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_IB(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 2.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_EQZ_C_ADJ_ES2
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES2(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES2     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES2(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 3.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_EQZ_C_ADJ_ES1
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES1(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES1     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES1(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 4.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_EQZ_C_ADJ_ES0
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES0(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES0     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_ADJ_ES0(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Coder mode: APC L value to IE inductance
 *
 * \details 
 * 0: equ. distributed (double step 3->4)
 * 1: equ. distributed (no change 6+7)
 * 2: 1st buffer max - 2nd buffer max - ...
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_EQZ_L_MODE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_L_MODE(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_L_MODE     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_L_MODE(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/** 
 * \brief
 * Coder mode: APC C value to IE capacitance
 *
 * \details 
 * 0: equ. distributed
 * 2: 1st buffer max - 2nd buffer max - ...
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_EQZ_C_MODE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_MODE(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_MODE     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_EQZ_C_MODE(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/** 
 * \brief
 * Threshold value (offset) for vscope-high sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_VSCOPE_H_THRES
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_VSCOPE_H_THRES(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_VSCOPE_H_THRES     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_VSCOPE_H_THRES(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Threshold value (offset) for vscope-low sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_VSCOPE_L_THRES
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_VSCOPE_L_THRES(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_VSCOPE_L_THRES     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_VSCOPE_L_THRES(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Threshold value (offset) for main sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4 . IB_MAIN_THRES
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_MAIN_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_MAIN_THRES     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG4_IB_MAIN_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief F2DF IB Configuration register 5
 *
 * \details
 * Configuration register 5 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG5
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5  VTSS_IOREG(0x1e, 1, 0xf025)

/** 
 * \brief
 * Test generator amplitude setting
 *
 * \details 
 * 0: 0mV
 * ...
 * 15: 150mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_TSTGEN_AMPL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_TSTGEN_AMPL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_TSTGEN_AMPL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_TSTGEN_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Test generator enable but data path selected with 'ib_sig_sel' (disable
 * input loop if testgenerator is used)
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_TSTGEN_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_TSTGEN_ENA  VTSS_BIT(27)

/** 
 * \brief
 * Test generator data
 *
 * \details 
 * 0: low
 * 1: high
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_TSTGEN_DATA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_TSTGEN_DATA  VTSS_BIT(26)

/** 
 * \brief
 * Test generator data toggle enable
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_TSTGEN_TOGGLE_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_TSTGEN_TOGGLE_ENA  VTSS_BIT(25)

/** 
 * \brief
 * Enable jump to opposite half of h-channel
 *
 * \details 
 * 0: Post main sampler
 * 1: Pre main sampler
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_JUMPH_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_JUMPH_ENA  VTSS_BIT(22)

/** 
 * \brief
 * Enable jump to opposite half of l-channel
 *
 * \details 
 * 0: Post main sampler
 * 1: Pre main sampler
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_JUMPL_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_JUMPL_ENA  VTSS_BIT(21)

/** 
 * \brief
 * DFE output disable required to calibrate IS
 *
 * \details 
 * 0: mission mode
 * 3: Vout = 0V
 * 1: Vout= xx*ampldfe/64
 * 2: Vout=-xx*ampldfe/64
 * 
 * ampldfe=196mV if ena1V = '1' (1V mode)
 * ampldfe=260mV if ena1V = '0' (1.2V mode)
 * 
 * xx= TBD
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_DFE_DIS
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_DFE_DIS(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_DFE_DIS     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_DFE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

/** 
 * \brief
 * AGC output disable required to calibrate DFE-gain
 *
 * \details 
 * 0: mission mode
 * 3: Vout = 0V
 * 1: Vout= xx*ampldfe/64
 * 2: Vout=-xx*ampldfe/64
 * 
 * ampldfe=270mV if ena1V = '1' (1V mode)
 * ampldfe=360mV if ena1V = '0' (1.2V mode)
 * 
 * xx=
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_AGC_DIS
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_AGC_DIS(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_AGC_DIS     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_AGC_DIS(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * Selects EQ Level Detect for calibration
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_EQ_LD_CAL_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_EQ_LD_CAL_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Selects IS threshold circuit for calibration
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_THRES_CAL_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_THRES_CAL_ENA  VTSS_BIT(15)

/** 
 * \brief
 * Selects IS offset circuit for calibration
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_IS_OFFS_CAL_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_IS_OFFS_CAL_ENA  VTSS_BIT(14)

/** 
 * \brief
 * Selects IA offset circuit for calibration
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_IA_OFFS_CAL_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_IA_OFFS_CAL_ENA  VTSS_BIT(13)

/** 
 * \brief
 * Selects IE Signal Detect for calibration
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_IE_SDET_CAL_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_IE_SDET_CAL_ENA  VTSS_BIT(12)

/** 
 * \brief
 * Enable calibration in order to eliminate hysteresis
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_HYS_CAL_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_HYS_CAL_ENA  VTSS_BIT(11)

/** 
 * \brief
 * Enables IS MUX in detblk1
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_CALMUX_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_CALMUX_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Selects calibration target (sample stage threshold, sample stage offset,
 * aux.-stage offset), dependend on calibration group, see encoding.
 *
 * \details 
 * When ib_thres_cal_ena = 1
 * 0: MD0 threshold
 * 1: MD1 threshold
 * 2: CP0 threshold
 * 3: CP1 threshold
 * 4: VH0 threshold
 * 5: VH1 threshold
 * 6: VL0 threshold
 * 7: VL1 threshold
 * When ib_is_offs_cal_ena = 1
 * 0: MD0 offset
 * 1: MD1 offset
 * 2: CP0 offset
 * 3: CP1 offset
 * 4: VH0 offset
 * 5: VH1 offset
 * 6: VL0 offset
 * 7: VL1 offset
 * When ib_ia_offs_cal_ena = 1
 * 0: Observe0 offset
 * 1: Observe1 offset
 * 2: Observe0 threshold
 * 3: Observe1 threshold
 * (MSB not used)
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_OFFS_BLKSEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_OFFS_BLKSEL(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_OFFS_BLKSEL     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_OFFS_BLKSEL(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/** 
 * \brief
 * Calibration value for IA/IS. Values for threshold calibration get
 * inverted for negative threshold voltages (ib_vscope_h_thres,
 * ib_vscope_l_thres or ib_main_thres).
 *
 * \details 
 * For offset calibration
 * 0: -max_offset * 32/32
 * 31: -max_offset * 1/32
 * 32: +max_offset * 1/32
 * 63: +max_offset * 32/32
 * For threshold calibration
 * 0: min_threshold
 * 63: max_threshold
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5 . IB_OFFS_VALUE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_OFFS_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_OFFS_VALUE     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG5_IB_OFFS_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief F2DF IB Configuration register 6
 *
 * \details
 * Configuration register 6 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG6
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6  VTSS_IOREG(0x1e, 1, 0xf026)

/** 
 * \brief
 * 0dB Gain adjustment for EQZ-stages of Input Buffer
 *
 * \details 
 * level at LD0 = LD1 -> 0dB
 * level range 160mV-220mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6 . IB_EQZ_GAIN_ADJ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_EQZ_GAIN_ADJ(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_EQZ_GAIN_ADJ     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_EQZ_GAIN_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Enable automatic AGC adjustment
 *
 * \details 
 * 1: AGC is adjusted automatically (IB_EQZ_AGC_ADJ value is not used)
 * 0: AGC is adjusted with value stored in IB_EQZ_AGC_ADJ
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6 . IB_AUTO_AGC_ADJ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_AUTO_AGC_ADJ  VTSS_BIT(12)

/** 
 * \brief
 * Gain adjustment of AGC-amplifier
 *
 * \details 
 * Bitgroup should be set to 2*IB_DFE_GAIN_ADJ
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6 . IB_EQZ_AGC_ADJ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_EQZ_AGC_ADJ(x)  VTSS_ENCODE_BITFIELD(x,5,7)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_EQZ_AGC_ADJ     VTSS_ENCODE_BITMASK(5,7)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_EQZ_AGC_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,5,7)

/** 
 * \brief
 * Range for offset calibration of all sampling pathes
 *
 * \details 
 * 0: 0mV
 * 32: 80mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6 . IB_SAM_OFFS_ADJ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_SAM_OFFS_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_SAM_OFFS_ADJ     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG6_IB_SAM_OFFS_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief F2DF IB Configuration register 7
 *
 * \details
 * Configuration register 7 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG7
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7  VTSS_IOREG(0x1e, 1, 0xf027)

/** 
 * \brief
 * Initial value for calibration of main sampling path
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7 . IB_MAIN_THRES_CAL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_MAIN_THRES_CAL(x)  VTSS_ENCODE_BITFIELD(x,23,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_MAIN_THRES_CAL     VTSS_ENCODE_BITMASK(23,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_MAIN_THRES_CAL(x)  VTSS_EXTRACT_BITFIELD(x,23,6)

/** 
 * \brief
 * Selects higher or lower DFE offset for IS calibration
 *
 * \details 
 * 0: ib_dfe_offset_l
 * 1: ib_dfe_offset_h
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7 . IB_DFE_OFFSET_H_L
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_OFFSET_H_L  VTSS_BIT(22)

/** 
 * \brief
 * Gain adjustment of DFEamplifier
 *
 * \details 
 * DFE Gain 1 Volt mode = 0dB
 * 1.2 Volt mode 1dB
 * measurement with int. DAC and Vscope Channels
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7 . IB_DFE_GAIN_ADJ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_GAIN_ADJ(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_GAIN_ADJ     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_GAIN_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * Higher threshold offset of DFE buffer for IS calibration
 *
 * \details 
 * 0: 0mv
 * 63: 200mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7 . IB_DFE_OFFSET_H
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_OFFSET_H(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_OFFSET_H     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_OFFSET_H(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Lower sample offset of DFE buffer for IS calibration
 *
 * \details 
 * 0: 0mv
 * 63: 200mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7 . IB_DFE_OFFSET_L
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_OFFSET_L(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_OFFSET_L     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG7_IB_DFE_OFFSET_L(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief F2DF IB Configuration register 8
 *
 * \details
 * Configuration register 8 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG8
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8  VTSS_IOREG(0x1e, 1, 0xf028)

/** 
 * \brief
 * Use separate vscope clock for vscope-channels
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8 . IB_SEL_VCLK
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_SEL_VCLK  VTSS_BIT(20)

/** 
 * \brief
 * Bias regulation mode
 *
 * \details 
 * 0: constant resistor
 * 1: constant current
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8 . IB_BIAS_MODE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_BIAS_MODE  VTSS_BIT(19)

/** 
 * \brief
 * Enables neutral setting of latches
 *
 * \details 
 * 1: Reset to mid values
 * 0: Normal operation
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8 . IB_LAT_NEUTRAL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_LAT_NEUTRAL  VTSS_BIT(18)

/** 
 * \brief
 * Amplitude of cml stages inside IS
 *
 * \details 
 * 0: 200mVppd
 * 7: 240mVppd
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8 . IB_CML_AMPL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_CML_AMPL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_CML_AMPL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_CML_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Gain of cml stages inside IS
 *
 * \details 
 * 0: 3dB
 * 31: 6dB
 * 63: 9dB
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8 . IB_BIAS_ADJ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_BIAS_ADJ(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_BIAS_ADJ     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_BIAS_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Current through CML Cells
 *
 * \details 
 * 0: 150%
 * 5: 100%
 * 15: 50%
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8 . IB_CML_CURR
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_CML_CURR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_CML_CURR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG8_IB_CML_CURR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief F2DF IB Configuration register 9  automatically adapted DFE coefficients
 *
 * \details
 * Configuration register 9 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG9
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9  VTSS_IOREG(0x1e, 1, 0xf029)

/** 
 * \brief
 * Weighting for fourth DFE coefficient
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9 . IB_DFE_COEF4
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF4(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF4     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF4(x)  VTSS_EXTRACT_BITFIELD(x,24,5)

/** 
 * \brief
 * Weighting for third DFE coefficient
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9 . IB_DFE_COEF3
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF3(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF3     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF3(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Weighting for second DFE coefficient
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9 . IB_DFE_COEF2
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF2(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF2     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF2(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Weighting for first DFE coefficient
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9 . IB_DFE_COEF1
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF1(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF1     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG9_IB_DFE_COEF1(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief F2DF IB Configuration register 10 JTAG related setting
 *
 * \details
 * Configuration register 10 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG10
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10  VTSS_IOREG(0x1e, 1, 0xf02a)

/** 
 * \brief
 * Data offset calibration result IA stage
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_IA_DOFFS_CAL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_IA_DOFFS_CAL  VTSS_BIT(31)

/** 
 * \brief
 * Data offset calibration result IS stage
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_IS_DOFFS_CAL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_IS_DOFFS_CAL  VTSS_BIT(30)

/** 
 * \brief
 * Detection of toggling signal at PADP and PADN
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_IE_SDET_PEDGE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_IE_SDET_PEDGE  VTSS_BIT(29)

/** 
 * \brief
 * Detection of toggling signal at PADP and PADN
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_IE_SDET_NEDGE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_IE_SDET_NEDGE  VTSS_BIT(28)

/** 
 * \brief
 * Result signal detect of IE stage
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_IE_SDET
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_IE_SDET  VTSS_BIT(27)

/** 
 * \brief
 * Result signal detect of IA stage
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_IA_SDET
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_IA_SDET  VTSS_BIT(26)

/** 
 * \brief
 * Result of Level-Detect1 (after ES2-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_EQZ_LD1_PEDGE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_EQZ_LD1_PEDGE  VTSS_BIT(25)

/** 
 * \brief
 * Result of Level-Detect1 (after ES2-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_EQZ_LD1_NEDGE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_EQZ_LD1_NEDGE  VTSS_BIT(24)

/** 
 * \brief
 * Result of Level-Detect0 (after IB-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_EQZ_LD0_PEDGE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_EQZ_LD0_PEDGE  VTSS_BIT(23)

/** 
 * \brief
 * Result of Level-Detect0 (after IB-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_EQZ_LD0_NEDGE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_EQZ_LD0_NEDGE  VTSS_BIT(22)

/** 
 * \brief
 * Direct Data output from IE block
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_IE_DIRECT_DATA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_IE_DIRECT_DATA  VTSS_BIT(21)

/** 
 * \brief
 * Direct Data output from IA block
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_IA_DIRECT_DATA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_IA_DIRECT_DATA  VTSS_BIT(20)

/** 
 * \brief
 * Receive enable for BiDi loop (a.k.a. PAD loop o. TX->RX loop). Is or'ed
 * with primary input: ib_pad_loop_ena_i. Disable testgenerator
 * 'ib_tstgen_ena' if input loop is used
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_LOOP_REC
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_LOOP_REC  VTSS_BIT(17)

/** 
 * \brief
 * Drive enable for BiDi loop (a.k.a. Input loop o. RX->TX loop). Is or'ed
 * with primary input: ib_inp_loop_ena_i. Is overruled by PAD loop.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_LOOP_DRV
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_LOOP_DRV  VTSS_BIT(16)

/** 
 * \brief
 * JTAG debug p-output
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_JTAG_OUT_P
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_OUT_P  VTSS_BIT(10)

/** 
 * \brief
 * JTAG debug n-output
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_JTAG_OUT_N
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_OUT_N  VTSS_BIT(9)

/** 
 * \brief
 * JTAG debug threshold
 *
 * \details 
 * 0: 0mV
 * 1: 10mV
 * 31: 310mV
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_JTAG_THRES
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_THRES     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * JTAG debug p-input
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_JTAG_IN_P
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_IN_P  VTSS_BIT(3)

/** 
 * \brief
 * JTAG debug n-input
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_JTAG_IN_N
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_IN_N  VTSS_BIT(2)

/** 
 * \brief
 * JTAG debug clk
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_JTAG_CLK
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_CLK  VTSS_BIT(1)

/** 
 * \brief
 * JTAG debug enable
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10 . IB_JTAG_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG10_IB_JTAG_ENA  VTSS_BIT(0)


/** 
 * \brief F2DF IB Configuration register 11 JTAG related setting
 *
 * \details
 * Configuration register 11 for F2DF IB.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_IB_CFG11
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11  VTSS_IOREG(0x1e, 1, 0xf02b)

/** 
 * \brief
 * DFE Bias current settings (bit-group is gated with IB_DFE_ENA)
 *
 * \details 
 * 0: DFE disabled
 * 1: Minimum current
 * 15: Maximum current
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11 . IB_DFE_ISEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_DFE_ISEL(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_DFE_ISEL     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_DFE_ISEL(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Increase current in first stage (only available in 1.2 Volt mode)
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11 . IB_ENA_400_INP
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_ENA_400_INP  VTSS_BIT(11)

/** 
 * \brief
 * Gain temperature coefficient for DFE stage
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11 . IB_TC_DFE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_TC_DFE(x)  VTSS_ENCODE_BITFIELD(x,6,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_TC_DFE     VTSS_ENCODE_BITMASK(6,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_TC_DFE(x)  VTSS_EXTRACT_BITFIELD(x,6,5)

/** 
 * \brief
 * Gain temperature coefficient for AGC stage
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11 . IB_TC_EQ
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_TC_EQ(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_TC_EQ     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_IB_CFG11_IB_TC_EQ(x)  VTSS_EXTRACT_BITFIELD(x,1,5)


/** 
 * \brief F2DF SBUS RX CFG Service-Bus related setting
 *
 * \details
 * Configuration register for Service-Bus related setting. Note: SBUS
 * configuration applies for RX/TX aggregates only, any configuration
 * applied to SBUS_TX_CFG (output buffer cfg space) will be ignored.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_IB:F2DF_SBUS_RX_CFG
 */
#define VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG  VTSS_IOREG(0x1e, 1, 0xf02c)

/** 
 * \brief
 * Enable BiDi loop driver for F2DF testing
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG . SBUS_LOOPDRV_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_LOOPDRV_ENA  VTSS_BIT(12)

/** 
 * \brief
 * Analog test output
 *
 * \details 
 * 0: l0_ctrlspeed[0]
 * 1: vbulk
 * 2: nref
 * 3: vref820m
 * 4: vddfilt
 * 5: vddfilt
 * 6: ie_aout
 * 7: ib_aout
 * 8: ob_aout2
 * 9: pll_frange
 * 10: pll_srange
 * 11: pll_vreg820m_tx
 * 12: pll_vreg820m_rx
 * 13: ob_aout_n
 * 14: ob_aout_p
 * 15: vddfilt
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG . SBUS_ANAOUT_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_ANAOUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_ANAOUT_SEL     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_ANAOUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Enable analog test output multiplexer
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG . SBUS_ANAOUT_EN
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_ANAOUT_EN  VTSS_BIT(7)

/** 
 * \brief
 * Offset value for BIAS resistor calibration (2-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG . SBUS_RCOMP
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_RCOMP(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_RCOMP     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_RCOMP(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/** 
 * \brief
 * Bias speed selection
 *
 * \details 
 * 0: Below 4Gbps
 * 1: 4Gbps to 6Gbps
 * 2: 6Gbps to 9Gbps
 * 3: Above 9Gbps
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG . SBUS_BIAS_SPEED_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Bias enable
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG . SBUS_BIAS_EN
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_IB_F2DF_SBUS_RX_CFG_SBUS_BIAS_EN  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL32:F2DF_RX_RCPLL
 *
 * F2DF RX RCPLL Configuration and Status Register set
 */


/** 
 * \brief F2DF RX RCPLL Configuration register 0
 *
 * \details
 * Configuration register 0 for F2DF RX RCPLL.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_RCPLL:F2DF_RX_RCPLL_CFG0
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0  VTSS_IOREG(0x1e, 1, 0xf030)

/** 
 * \brief
 * Preload value of the ramp up counter, reduces ramp up time for higher
 * frequencies
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0 . PLLF_START_CNT
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0_PLLF_START_CNT     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Sets the ramp characteristic of the FSM, higher values give faster ramp
 * up but less accuracy,
 *
 * \details 
 * 0: normal (default) ramping
 * 1: faster ramping
 * 2: fastest ramping
 * 3: slow ramping
 * uses all possible values of r_ctrl
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0 . PLLF_RAMP_MODE_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Enable RCPLL FSM
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0 . PLLF_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG0_PLLF_ENA  VTSS_BIT(0)


/** 
 * \brief F2DF RX RCPLL Configuration register 1
 *
 * \details
 * Configuration register 1 for F2DF RX RCPLL.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_RCPLL:F2DF_RX_RCPLL_CFG1
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG1  VTSS_IOREG(0x1e, 1, 0xf031)

/** 
 * \brief
 * Target value: 1/vco_frq * par.bit.width * 512 * ref_clk_frq
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG1 . PLLF_REF_CNT_END
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG1_PLLF_REF_CNT_END     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief F2DF RX RCPLL Configuration register 2
 *
 * \details
 * Configuration register 2 for F2DF RX RCPLL.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_RCPLL:F2DF_RX_RCPLL_CFG2
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2  VTSS_IOREG(0x1e, 1, 0xf032)

/** 
 * \brief
 * Select chargepump current,
 *
 * \details 
 * 0: 50uA
 * 1: 100uA
 * 2: 150uA
 * 3: 200uA
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2 . PLL_LPF_CUR
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2_PLL_LPF_CUR     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Select loop filter resistor value,
 *
 * \details 
 * 0: not allowed
 * 1: 2400
 * 2: 1600
 * 3: 960
 * 4: 1200
 * 5: 800
 * 6: 685
 * 7: 533
 * 8: 800
 * 9: 600
 * 10: 533
 * 11: 436
 * 12: 480
 * 13: 400
 * 14: 369
 * 15: 320
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2 . PLL_LPF_RES
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2_PLL_LPF_RES     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Enable analog RCPLL part
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2 . PLL_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_CFG2_PLL_ENA  VTSS_BIT(0)


/** 
 * \brief F2DF RX RCPLL Status register 0
 *
 * \details
 * Status register 0 for F2DF RX RCPLL.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_RCPLL:F2DF_RX_RCPLL_STAT0
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_STAT0  VTSS_IOREG(0x1e, 1, 0xf033)

/** 
 * \brief
 * PLL lock status,
 *
 * \details 
 * 0: not locked
 * 1: locked
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_STAT0 . PLLF_LOCK_STAT
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_STAT0_PLLF_LOCK_STAT  VTSS_BIT(31)


/** 
 * \brief F2DF RX RCPLL Status register 1
 *
 * \details
 * Status register 1 for F2DF RX RCPLL.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_RCPLL:F2DF_RX_RCPLL_STAT1
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_RCPLL_F2DF_RX_RCPLL_STAT1  VTSS_IOREG(0x1e, 1, 0xf034)

/**
 * Register Group: \a VENICE_GLOBAL32:F2DF_RX_SYNTH
 *
 * F2DF RX SYNTH Configuration and Status Register set
 */


/** 
 * \brief F2DF RX Synthesizer Configuration register 0
 *
 * \details
 * Configuration register 0 for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_CFG0
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0  VTSS_IOREG(0x1e, 1, 0xf040)

/** 
 * \brief
 * selects feedback divider setting.
 *
 * \details 
 * 0: divide by 1
 * 1: divide by 2
 * 2: divide by 4
 * 3: reserved
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_FBDIV_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * selects step width for sync output
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_FB_STEP
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_FB_STEP(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_FB_STEP     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_FB_STEP(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * selects step width for integrator2
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_I2_STEP
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_I2_STEP(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_I2_STEP     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_I2_STEP(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * enable contribution of integral2 part
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_I2_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_I2_ENA  VTSS_BIT(9)

/** 
 * \brief
 * selects step width for integrator1
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_I1_STEP
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_I1_STEP  VTSS_BIT(8)

/** 
 * \brief
 * selects step width for propotional
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_P_STEP
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_P_STEP  VTSS_BIT(6)

/** 
 * \brief
 * Selects circuit speed.
 *
 * \details 
 * 0: for settings with synth_fbdiv_sel = 2
 * 1: for setting with synth_fbdiv_sel less than 2
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_SPEED_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_SPEED_SEL  VTSS_BIT(4)

/** 
 * \brief
 * enables half rate mode
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_HRATE_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_HRATE_ENA  VTSS_BIT(3)

/** 
 * \brief
 * enables CML2CMOS converter (low speed part of synthesizer)
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_CONV_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_CONV_ENA  VTSS_BIT(1)

/** 
 * \brief
 * synthesizer enable
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0 . SYNTH_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG0_SYNTH_ENA  VTSS_BIT(0)


/** 
 * \brief F2DF RX Synthesizer Configuration register 1
 *
 * \details
 * Configuration register 1 for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_CFG1
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1  VTSS_IOREG(0x1e, 1, 0xf041)

/** 
 * \brief
 * frequency multiplier
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1 . SYNTH_FREQ_MULT
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQ_MULT     VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_EXTRACT_BITFIELD(x,8,14)

/** 
 * \brief
 * frequency m setting bits 35:32
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1 . SYNTH_FREQM_1
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQM_1     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * frequency n setting bits 35:32
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1 . SYNTH_FREQN_1
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQN_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief F2DF RX Synthesizer Configuration register 2
 *
 * \details
 * Configuration register 2 for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_CFG2
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2  VTSS_IOREG(0x1e, 1, 0xf042)

/** 
 * \brief
 * Rising edge triggers bit skip forward in serial data stream. Used to
 * align data to parallel interface boundaries.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_SKIP_BIT_FWD
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_FWD  VTSS_BIT(31)

/** 
 * \brief
 * Rising edge triggers bit skip reverse in serial data stream. Used to
 * align data to parallel interface boundaries.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_SKIP_BIT_REV
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_REV  VTSS_BIT(30)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I2 enable function: b0 =
 * 0 => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I2E
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I1 max function: b0 = 0
 * => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I1M
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I1 enable function: b0 =
 * 0 => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I1E
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/** 
 * \brief
 * Controls the data valid behavior for the moebdiv select function: b0 = 0
 * => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_MD
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Cp/md dig select. Coding 0: select Bit 0/5 as cp/md (FX100 mode); 1: use
 * cp/md from core
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_CPMD_DIG_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_SEL  VTSS_BIT(18)

/** 
 * \brief
 * uses cp/md selected via synth_cpmd_dig_sel instead of cp/md from sample
 * stage
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_CPMD_DIG_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_ENA  VTSS_BIT(17)

/** 
 * \brief
 * enables clock for VScope / APC auxillary data chanels
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_AUX_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_AUX_ENA  VTSS_BIT(16)

/** 
 * \brief
 * relationship phase center/edge
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_PHASE_DATA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_PHASE_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_PHASE_DATA     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_PHASE_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * relationship phase center/aux
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2 . SYNTH_PHASE_AUX
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_PHASE_AUX(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_PHASE_AUX     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG2_SYNTH_PHASE_AUX(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief F2DF RX Synthesizer Configuration register 3
 *
 * \details
 * Configuration register 3 for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_CFG3
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG3  VTSS_IOREG(0x1e, 1, 0xf043)


/** 
 * \brief F2DF RX Synthesizer Configuration register 4
 *
 * \details
 * Configuration register 4 for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_CFG4
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CFG4  VTSS_IOREG(0x1e, 1, 0xf044)


/** 
 * \brief F2DF RX Synthesizer Register CDR loopfilter control
 *
 * \details
 * Register for CDR loopfilter control for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_CDRLF
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF  VTSS_IOREG(0x1e, 1, 0xf045)

/** 
 * \brief
 * Enables integrator 3
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF . SYNTH_INTEG3_ENA
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG3_ENA  VTSS_BIT(31)

/** 
 * \brief
 * Select filter damping / gain peaking when integrator 3 is enabled. The
 * control value is interpreted as signed value. Positive values increase
 * the damping, i.e. lowering the gain peacking; negative values decease
 * the damping, i.e. raising the gain peaking. The allowed programming
 * range depends on the SYNTH_INTEG2_FSEL setting: 0 <= (SYNTH_INTEG2_FSEL
 * - SYNTH_INTEG3_DSEL) <= 53. SYNTH_INTEG2_FSEL - SYNTH_INTEG3_DSEL = 0
 * and SYNTH_INTEG2_FSEL - SYNTH_INTEG3_DSEL = 1 gives the same damping.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF . SYNTH_INTEG3_DSEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG3_DSEL(x)  VTSS_ENCODE_BITFIELD(x,26,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG3_DSEL     VTSS_ENCODE_BITMASK(26,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG3_DSEL(x)  VTSS_EXTRACT_BITFIELD(x,26,5)

/** 
 * \brief
 * max value of integrator 1 during normal operation
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF . SYNTH_INTEG1_MAX1
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/** 
 * \brief
 * max value of integrator 1 during init phase
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF . SYNTH_INTEG1_MAX0
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * limit of integrator 1
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF . SYNTH_INTEG1_LIM
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM(x)  VTSS_ENCODE_BITFIELD(x,11,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM     VTSS_ENCODE_BITMASK(11,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM(x)  VTSS_EXTRACT_BITFIELD(x,11,5)

/** 
 * \brief
 * frequency select of integrator 1
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF . SYNTH_INTEG1_FSEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL(x)  VTSS_ENCODE_BITFIELD(x,6,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL     VTSS_ENCODE_BITMASK(6,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL(x)  VTSS_EXTRACT_BITFIELD(x,6,5)

/** 
 * \brief
 * frequency select of integrator 2
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF . SYNTH_INTEG2_FSEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief F2DF RX Synthesizer Register 0 for qualifier access
 *
 * \details
 * Register 0 for qualifier access for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_QUALIFIER0
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0  VTSS_IOREG(0x1e, 1, 0xf046)

/** 
 * \brief
 * Rising edge captures qualifier for readback
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0 . SYNTH_CAPTURE_QUAL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0_SYNTH_CAPTURE_QUAL  VTSS_BIT(20)

/** 
 * \brief
 * MS Bits of captured integrator 2
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0 . SYNTH_QUAL_I2_MSB
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Captured integrator 1 value
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0 . SYNTH_QUAL_I1
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF RX Synthesizer Register 1 for qualifier access
 *
 * \details
 * Register 1 for qualifier access for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_QUALIFIER1
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_QUALIFIER1  VTSS_IOREG(0x1e, 1, 0xf047)


/** 
 * \brief F2DF RX Synthesizer Register for sync control data
 *
 * \details
 * Register 0 for sync control data for F2DF RX SYNTH.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_RX_SYNTH_SYNC_CTRL
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_SYNC_CTRL  VTSS_IOREG(0x1e, 1, 0xf048)

/** 
 * \brief
 * Selects the synchronization period for the I2 value via sync control
 * bus. Must be disabled (0) when sync control test generator is used.
 * Coding in 312.5MHz clock cycles: 0: disabled, 1: 2^6, 2: 2^7, .., 15:
 * 2^20.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_SYNC_CTRL . SYNTH_SC_SYNC_TIMER_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief F2DF Configuration / status register
 *
 * \details
 * Configuration / status register for the F2DF control logic.
 *
 * Register: \a VENICE_GLOBAL32:F2DF_RX_SYNTH:F2DF_CFG_STAT
 */
#define VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT  VTSS_IOREG(0x1e, 1, 0xf049)

/** 
 * \brief
 * Sampling divider: sample every 2^f2df_sample_div parallel data word.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT . F2DF_SAMPLE_DIV
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV(x)  VTSS_ENCODE_BITFIELD(x,25,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV     VTSS_ENCODE_BITMASK(25,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,25,3)

/** 
 * \brief
 * Select bit from input data used for side detection. Debug feature: '31'
 * select constant zero, '30' select constant one.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_BIT_SEL
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,5)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL     VTSS_ENCODE_BITMASK(17,5)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,5)

/** 
 * \brief
 * Sample '1' => increment 8bit filter saturating counter by 2**n. Cnt >=
 * 0xC0 => PropperSide detected.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_ONES_WEIGHT
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT(x)  VTSS_ENCODE_BITFIELD(x,14,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT     VTSS_ENCODE_BITMASK(14,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT(x)  VTSS_EXTRACT_BITFIELD(x,14,3)

/** 
 * \brief
 * Sample '0' => decrement 8bit filter saturating counter by 2**n. Cnt <
 *
 * \details 
 * 0x40 => WrongSide detected.
 *
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_ZEROS_WEIGHT
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Determines the number of samples that have to show at least one toggle.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT . F2DF_TOG_DET_CNT
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Data valid value in "PropperSide" state. '0': data valid flaged only in
 * "Lock" state; '1' data valid also flaged in "PropperSide" state.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT . F2DF_DATA_VALID_PROPPER_SIDE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_DATA_VALID_PROPPER_SIDE  VTSS_BIT(3)

/** 
 * \brief
 * Clear all sticky bits.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT . F2DF_STICKY_CLR
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_STICKY_CLR  VTSS_BIT(2)

/** 
 * \brief
 * F2df enable. Enabling the f2df circuit automatically switches the input
 * of the CDR-loop to the f2df control block (overrules synth_cpmd_dig_sel
 * and synth_cpmd_dig_ena) and replaces the data valid signal from the core
 * logic by the data valid signal generated by the f2df control logic.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT . F2DF_ENABLE
 */
#define  VTSS_F_VENICE_GLOBAL32_F2DF_RX_SYNTH_F2DF_CFG_STAT_F2DF_ENABLE  VTSS_BIT(0)


#endif /* _VTSS_VENICE_REGS_VENICE_GLOBAL32_H_ */
