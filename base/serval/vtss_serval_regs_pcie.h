// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVAL_REGS_PCIE_H_
#define _VTSS_SERVAL_REGS_PCIE_H_


#include "vtss_serval_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a PCIE
 *
 * PCIe endpoint configuration space
 *
 ***********************************************************************/

/**
 * Register Group: \a PCIE:PCIE
 *
 * PCIe endpoint configuration space
 */


/** 
 * \brief PCI configruation space
 *
 * \details
 * This is not the complete configuration + extended configuration space,
 * only op to byte address 6FF.
 *
 * Register: \a PCIE:PCIE:CONF_SPACE
 *
 * @param ri Register: CONF_SPACE (??), 0-447
 */
#define VTSS_PCIE_PCIE_CONF_SPACE(ri)        VTSS_IOREG(VTSS_TO_PCIE_EP,0x0 + (ri))


/** 
 * \brief Address translation region
 *
 * \details
 * The address translation unit supports 2 outbound regions. The registers
 * PCIE::ATU_CFG1, PCIE::ATU_CFG2, PCIE::ATU_BASE_ADDR_LOW,
 * PICE::ATU_BASE_ADDR_HIGH, PCIE::ATU_LIMIT_ADDR, PCIE::ATU_TGT_ADDR_LOW,
 * and PCIE::ATU_TGT_ADDR_HIGH all maps to the currently configured region
 * (as configured in this register).
 *
 * Register: \a PCIE:PCIE:ATU_REGION
 */
#define VTSS_PCIE_PCIE_ATU_REGION            VTSS_IOREG(VTSS_TO_PCIE_EP,0x240)

/** 
 * \brief
 * Selects region index, set to 0 or 1.

 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_REGION . ATU_IDX
 */
#define  VTSS_F_PCIE_PCIE_ATU_REGION_ATU_IDX  VTSS_BIT(0)


/** 
 * \brief Address translation configuration register 1
 *
 * \details
 * Register: \a PCIE:PCIE:ATU_CFG1
 */
#define VTSS_PCIE_PCIE_ATU_CFG1              VTSS_IOREG(VTSS_TO_PCIE_EP,0x241)

/** 
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * ATTR field of the TLP is changed to the value in this register.
 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_CFG1 . ATU_ATTR
 */
#define  VTSS_F_PCIE_PCIE_ATU_CFG1_ATU_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_PCIE_ATU_CFG1_ATU_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_PCIE_ATU_CFG1_ATU_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/** 
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TD field of the TLP is changed to the value in this register.
 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_CFG1 . ATU_TD
 */
#define  VTSS_F_PCIE_PCIE_ATU_CFG1_ATU_TD     VTSS_BIT(8)

/** 
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TC field of the TLP is changed to the value in this register.
 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_CFG1 . ATU_TC
 */
#define  VTSS_F_PCIE_PCIE_ATU_CFG1_ATU_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_PCIE_ATU_CFG1_ATU_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_PCIE_ATU_CFG1_ATU_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TYPE field of the TLP is changed to the value in this register.
 *
 * \details 
 * 0: MRd/MWr
 * 1: MRdLk
 * 2: IORd/IOWr
 * 4: CfgRd0/CfgWr0
 * 5: CfgRd1/CfgWr1
 * 16-23: Msg/MsgD
 *
 * Field: ::VTSS_PCIE_PCIE_ATU_CFG1 . ATU_TYPE
 */
#define  VTSS_F_PCIE_PCIE_ATU_CFG1_ATU_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_PCIE_ATU_CFG1_ATU_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_PCIE_ATU_CFG1_ATU_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Address translation configuration register 2
 *
 * \details
 * Register: \a PCIE:PCIE:ATU_CFG2
 */
#define VTSS_PCIE_PCIE_ATU_CFG2              VTSS_IOREG(VTSS_TO_PCIE_EP,0x242)

/** 
 * \brief
 * This bit must be set for address translation to take place.
 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_CFG2 . ATU_REGION_ENA
 */
#define  VTSS_F_PCIE_PCIE_ATU_CFG2_ATU_REGION_ENA  VTSS_BIT(31)

/** 
 * \brief
 * When the address of an outbound TLP is matched to this region, and the
 * translated TLP TYPE field is Msg or MsgD; then the Message field of the
 * TLP is changed to the value in this register.
 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_CFG2 . ATU_MSG_CODE
 */
#define  VTSS_F_PCIE_PCIE_ATU_CFG2_ATU_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_PCIE_ATU_CFG2_ATU_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_PCIE_ATU_CFG2_ATU_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Address translation lower base address
 *
 * \details
 * Register: \a PCIE:PCIE:ATU_BASE_ADDR_LOW
 */
#define VTSS_PCIE_PCIE_ATU_BASE_ADDR_LOW     VTSS_IOREG(VTSS_TO_PCIE_EP,0x243)

/** 
 * \brief
 * Bits 31:16 of the starting address of the address region to be
 * translated.
 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_BASE_ADDR_LOW . ATU_BASE_ADDR_LOW
 */
#define  VTSS_F_PCIE_PCIE_ATU_BASE_ADDR_LOW_ATU_BASE_ADDR_LOW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_PCIE_ATU_BASE_ADDR_LOW_ATU_BASE_ADDR_LOW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_PCIE_ATU_BASE_ADDR_LOW_ATU_BASE_ADDR_LOW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Address translation upper base address
 *
 * \details
 * Register: \a PCIE:PCIE:ATU_BASE_ADDR_HIGH
 */
#define VTSS_PCIE_PCIE_ATU_BASE_ADDR_HIGH    VTSS_IOREG(VTSS_TO_PCIE_EP,0x244)


/** 
 * \brief Address translation limit address
 *
 * \details
 * This register configures the window which is translated.
 * For example: If PCIE::ATU_BASE_ADDR_LOW is set to 0x00010000,
 * PCIE::ATU_LIMIT_ADDR is set to 0x0005FFFF, PCIE::ATU_TGT_ADDR_LOW is set
 * to 0x20000000, and PCIE::ATU_TGT_ADDR_HIGH is set to 0x00007000. Then
 * outbound TLPs with PCIe addresses in the range 0x00010000 though
 * 0x0005FFFF is mapped to 64bit address 0x0000700020000000 though
 * 0x000070002004FFFF. Header fields of the mapped TLPs are configured via
 * PCIE::ATU_CFG1 and PCIE::ATU_CFG2.
 *
 * Register: \a PCIE:PCIE:ATU_LIMIT_ADDR
 */
#define VTSS_PCIE_PCIE_ATU_LIMIT_ADDR        VTSS_IOREG(VTSS_TO_PCIE_EP,0x245)

/** 
 * \brief
 * Bits 31:16 of the ending address of the address region to be translated.
 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_LIMIT_ADDR . ATU_LIMIT_ADDR
 */
#define  VTSS_F_PCIE_PCIE_ATU_LIMIT_ADDR_ATU_LIMIT_ADDR(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_PCIE_ATU_LIMIT_ADDR_ATU_LIMIT_ADDR     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_PCIE_ATU_LIMIT_ADDR_ATU_LIMIT_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Address translation lower target address
 *
 * \details
 * Register: \a PCIE:PCIE:ATU_TGT_ADDR_LOW
 */
#define VTSS_PCIE_PCIE_ATU_TGT_ADDR_LOW      VTSS_IOREG(VTSS_TO_PCIE_EP,0x246)

/** 
 * \brief
 * Bits 31:16 of the new address of the translated region.
 *
 * \details 
 * Field: ::VTSS_PCIE_PCIE_ATU_TGT_ADDR_LOW . ATU_TGT_ADDR_LOW
 */
#define  VTSS_F_PCIE_PCIE_ATU_TGT_ADDR_LOW_ATU_TGT_ADDR_LOW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_PCIE_ATU_TGT_ADDR_LOW_ATU_TGT_ADDR_LOW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_PCIE_ATU_TGT_ADDR_LOW_ATU_TGT_ADDR_LOW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Address translation upper target address
 *
 * \details
 * Register: \a PCIE:PCIE:ATU_TGT_ADDR_HIGH
 */
#define VTSS_PCIE_PCIE_ATU_TGT_ADDR_HIGH     VTSS_IOREG(VTSS_TO_PCIE_EP,0x247)


#endif /* _VTSS_SERVAL_REGS_PCIE_H_ */
