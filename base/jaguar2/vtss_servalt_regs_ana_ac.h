#ifndef _VTSS_SERVALT_REGS_ANA_AC_H_
#define _VTSS_SERVALT_REGS_ANA_AC_H_

/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a ANA_AC
 *
 * Controls mask handling etc.
 *
 ***********************************************************************/

/**
 * Register Group: \a ANA_AC:RAM_CTRL
 *
 * Access core memory
 */


/** 
 * \brief Core reset control
 *
 * \details
 * Controls reset and initialization of the switching core. Proper startup
 * sequence is:
 * - Enable memories
 * - Initialize memories
 * - Enable core
 *
 * Register: \a ANA_AC:RAM_CTRL:RAM_INIT
 */
#define VTSS_ANA_AC_RAM_CTRL_RAM_INIT        VTSS_IOREG(VTSS_TO_ANA_AC,0x53f7)

/** 
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete ( approx. 40 us).
 *
 * \details 
 * Field: ::VTSS_ANA_AC_RAM_CTRL_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_ANA_AC_RAM_CTRL_RAM_INIT_RAM_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_RAM_CTRL_RAM_INIT_RAM_INIT  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_RAM_CTRL_RAM_INIT_RAM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Core memory controllers are enabled when this field is set.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_RAM_CTRL_RAM_INIT . RAM_ENA
 */
#define  VTSS_F_ANA_AC_RAM_CTRL_RAM_INIT_RAM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_RAM_CTRL_RAM_INIT_RAM_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_RAM_CTRL_RAM_INIT_RAM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC:COREMEM
 *
 * Access core memory
 */


/** 
 * \brief Address selection
 *
 * \details
 * Register: \a ANA_AC:COREMEM:CM_ADDR
 */
#define VTSS_ANA_AC_COREMEM_CM_ADDR          VTSS_IOREG(VTSS_TO_ANA_AC,0x5516)

/** 
 * \brief
 * Refer to cmid.xls in the AS1000, misc_docs folder.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_COREMEM_CM_ADDR . CM_ID
 */
#define  VTSS_F_ANA_AC_COREMEM_CM_ADDR_CM_ID(x)  VTSS_ENCODE_BITFIELD(x,22,8)
#define  VTSS_M_ANA_AC_COREMEM_CM_ADDR_CM_ID     VTSS_ENCODE_BITMASK(22,8)
#define  VTSS_X_ANA_AC_COREMEM_CM_ADDR_CM_ID(x)  VTSS_EXTRACT_BITFIELD(x,22,8)

/** 
 * \brief
 * Address selection within selected core memory (CMID register). Address
 * is automatically advanced at every data access.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_COREMEM_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_ANA_AC_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_ANA_AC_COREMEM_CM_ADDR_CM_ADDR     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_ANA_AC_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,22)


/** 
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a ANA_AC:COREMEM:CM_DATA
 */
#define VTSS_ANA_AC_COREMEM_CM_DATA          VTSS_IOREG(VTSS_TO_ANA_AC,0x5517)

/** 
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 BIT inspection space.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_COREMEM_CM_DATA . CM_DATA
 */
#define  VTSS_F_ANA_AC_COREMEM_CM_DATA_CM_DATA(x)  (x)
#define  VTSS_M_ANA_AC_COREMEM_CM_DATA_CM_DATA     0xffffffff
#define  VTSS_X_ANA_AC_COREMEM_CM_DATA_CM_DATA(x)  (x)

/**
 * Register Group: \a ANA_AC:PS_COMMON
 *
 * Common configurations for all ports
 */


/** 
 * \brief Miscellaneous control parameters
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:MISC_CTRL
 */
#define VTSS_ANA_AC_PS_COMMON_MISC_CTRL      VTSS_IOREG(VTSS_TO_ANA_AC,0x5700)

/** 
 * \brief
 * Enable use of VID instead of ISDX_BASE_ADDR as index to statistics in
 * ANA_AC:STAT_CNT_CFG_ISDX.
 * 
 * Related parameters:
 * ANA_L2::ISDX_BASE_CFG.ISDX_BASE_ADDR
 * REW:COMMON:CNT_CTRL.STAT_MODE.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_MISC_CTRL . USE_VID_AS_ISDX_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_MISC_CTRL_USE_VID_AS_ISDX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_PS_COMMON_MISC_CTRL_USE_VID_AS_ISDX_ENA  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_PS_COMMON_MISC_CTRL_USE_VID_AS_ISDX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Increase DP level for flooded traffic.
 *
 * \details 
 * 0: Disabled
 * 1: Increase DP by 1 for flooded traffic
 * 2: Increase DP by 2 for flooded traffic
 * 3: Increase DP by 3 for flooded traffic
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_MISC_CTRL . CMAC_FLOOD_DP_INC
 */
#define  VTSS_F_ANA_AC_PS_COMMON_MISC_CTRL_CMAC_FLOOD_DP_INC(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ANA_AC_PS_COMMON_MISC_CTRL_CMAC_FLOOD_DP_INC     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_ANA_AC_PS_COMMON_MISC_CTRL_CMAC_FLOOD_DP_INC(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Avoid CPU sending back to CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_MISC_CTRL . CPU_TO_CPU_KILL_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_MISC_CTRL_CPU_TO_CPU_KILL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_PS_COMMON_MISC_CTRL_CPU_TO_CPU_KILL_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_PS_COMMON_MISC_CTRL_CPU_TO_CPU_KILL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief Various, common configuration parameters
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:PS_COMMON_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_PS_COMMON_CFG  VTSS_IOREG(VTSS_TO_ANA_AC,0x5701)

/** 
 * \brief
 * Enable sFlow Sampler ID in sFlow Stamp.
 * The "sFlow Stamp" replaces the frame's FCS.
 * 
 * With this bit disabled the sFlow Stamp format becomes:
 * Bit 31:8: Frame forwarding count.
 * Bit 7:0: Sample count.
 * 
 * With this bit enabled the sFlow Stamp format becomes:
 * Bit 31:26: Sampler ID
 * Bit 25:8: Frame forwarding count.
 * Bit 7:0: Sample count.

 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_PS_COMMON_CFG . SFLOW_SMPL_ID_IN_STAMP_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_SMPL_ID_IN_STAMP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_SMPL_ID_IN_STAMP_ENA  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_SMPL_ID_IN_STAMP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable sFlow sampling.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_PS_COMMON_CFG . SFLOW_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_PS_COMMON_PS_COMMON_CFG_SFLOW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable lookup of logical source port. 
 * If disabled, the source mask does not affect the egress port mask.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_PS_COMMON_CFG . SRC_LOOKUP_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_PS_COMMON_CFG_SRC_LOOKUP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_PS_COMMON_PS_COMMON_CFG_SRC_LOOKUP_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_PS_COMMON_PS_COMMON_CFG_SRC_LOOKUP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief sFlow configuration
 *
 * \details
 * This register configures the sFlow sampler.
 *
 * Register: \a ANA_AC:PS_COMMON:SFLOW_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_SFLOW_CFG      VTSS_IOREG(VTSS_TO_ANA_AC,0x5702)

/** 
 * \brief
 * CPU queue for frames copied to the CPU by an sFlow Sampler.
 * 
 * Note that sFlow sampling will not cause any bits in IFH.MISC.CPU_MASK to
 * get set. 
 * Instead IFH.DST.SFLOW_MARKING is set (in all CPU copies of the frame).
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_SFLOW_CFG . SFLOW_CPU_QU
 */
#define  VTSS_F_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_ANA_AC_PS_COMMON_SFLOW_CFG_SFLOW_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,12,3)


/** 
 * \brief sFlow counter reset 
 *
 * \details
 * This register configures the sFlow Sampler reset.
 *
 * Register: \a ANA_AC:PS_COMMON:SFLOW_RESET_CTRL
 */
#define VTSS_ANA_AC_PS_COMMON_SFLOW_RESET_CTRL  VTSS_IOREG(VTSS_TO_ANA_AC,0x5703)

/** 
 * \brief
 * When set to 1, the following counters are reset for all sFlow Samplers:
 * ANA_AC:SFLOW:SFLOW_CNT.SFLOW_SAMPLE_CNT
 * ANA_AC:SFLOW:SFLOW_CNT.SFLOW_SAMPLE_FWD_CNT
 * 
 * Upon resetting the counters, the device will set the parameter back to
 * 0.
 *
 * \details 
 * 0: No action
 * 1: Reset counters.
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_SFLOW_RESET_CTRL . SFLOW_FRAME_RESET_SHOT
 */
#define  VTSS_F_ANA_AC_PS_COMMON_SFLOW_RESET_CTRL_SFLOW_FRAME_RESET_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_PS_COMMON_SFLOW_RESET_CTRL_SFLOW_FRAME_RESET_SHOT  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_PS_COMMON_SFLOW_RESET_CTRL_SFLOW_FRAME_RESET_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Enable aggregation using physical source port number
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:PHYS_SRC_AGGR_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_PHYS_SRC_AGGR_CFG  VTSS_IOREG(VTSS_TO_ANA_AC,0x5704)

/** 
 * \brief
 * Enable use of physical source port number for aggregation towards this
 * port.
 * 
 * This is intended to be used when interconnecting two devices using two
 * interconnect ports, which are aggregated in a LLAG, to form a 48 port
 * system.
 *
 * \details 
 * 'xxx0xx': Use normal aggregation code when finding aggregation mask for
 * this port
 * 'xxx1xx': Use only physical source port number in aggregation code when
 * finding aggregation mask for this port.
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_PHYS_SRC_AGGR_CFG . PHYS_SRC_AGGR_MASK
 */
#define  VTSS_F_ANA_AC_PS_COMMON_PHYS_SRC_AGGR_CFG_PHYS_SRC_AGGR_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_PS_COMMON_PHYS_SRC_AGGR_CFG_PHYS_SRC_AGGR_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_PS_COMMON_PHYS_SRC_AGGR_CFG_PHYS_SRC_AGGR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Stack port mask configuration
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:STACK_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_STACK_CFG      VTSS_IOREG(VTSS_TO_ANA_AC,0x5705)

/** 
 * \brief
 * Stack port mask.
 * 
 * For ports used for stacking, the corresponding bit must be set in this
 * port mask.
 *
 * \details 
 * 'XX...XXX': Where X is '0' or '1', representing a destination port.
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_STACK_CFG . STACK_MASK
 */
#define  VTSS_F_ANA_AC_PS_COMMON_STACK_CFG_STACK_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_PS_COMMON_STACK_CFG_STACK_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_PS_COMMON_STACK_CFG_STACK_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Port mask for Stack Port A
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:STACK_A_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_STACK_A_CFG    VTSS_IOREG(VTSS_TO_ANA_AC,0x5706)

/** 
 * \brief
 * Port mask with ports of stack port A.
 * 
 * This mask is only used when forwarding to UPSIDs w.
 * STACK_LINK_EQUAL_COST_CFG.STACK_LINK_EQUAL_ENA=1.
 * 
 * If STACK_LINK_EQUAL_ENA is set, then the stack forwarding mask is
 * calculated as one of the following two, depending on AC:
 *   Even AC:
 *     UPSID.UPSID_PORT_VEC* & STACK_A_CFG.STACK_A_VEC*
 *   Odd AC:
 *     UPSID.UPSID_PORT_VEC* & ~STACK_A_CFG.STACK_A_VEC*
 *
 * \details 
 * 'XX...XXX': Where X is '0' or '1', representing a stacking link A
 * destination port.
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_STACK_A_CFG . STACK_A_MASK
 */
#define  VTSS_F_ANA_AC_PS_COMMON_STACK_A_CFG_STACK_A_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_PS_COMMON_STACK_A_CFG_STACK_A_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_PS_COMMON_STACK_A_CFG_STACK_A_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Common stacking parameters
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:COMMON_VSTAX_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG  VTSS_IOREG(VTSS_TO_ANA_AC,0x5707)

/** 
 * \brief
 * Disable counting of bytes and frames in ANA_AC:STAT_CNT_CFG_ISDX
 * for frames received on a stack port.
 * 
 * Related parameters:
 * REW:COMMON:CNT_CTRL.VSTAX_STAT_ESDX_DIS
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_ISDX_STAT_DIS
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_ISDX_STAT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_ISDX_STAT_DIS  VTSS_BIT(25)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_ISDX_STAT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Allow FWD_LOGICAL entries in MAC table to control internal port number
 * in VStaX header.
 * 
 * If MAC table entry for DMAC specifies vstax.general.fwd_mode=FWD_LOGICAL
 * and a destination port number of type port_type_intpn, then this bit
 * controls the outgoing destination port number in the VStaX header.
 * 
 * If this bit is clear, then the destination port number in VStaX header
 * is set to intpn=15, regardless of the port number specified in the MAC
 * table entry.
 * 
 * If this bit is set, then the destination port number in VStaX header is
 * set to the value of the port number specified in the MAC table entry.

 *
 * \details 
 * 0: Disable (set destination port to intpn=15)
 * 1: Enable (set destination port to value in MAC table)
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_ALLOW_UPSID_CPU_OR_INT_PN_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_ALLOW_UPSID_CPU_OR_INT_PN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_ALLOW_UPSID_CPU_OR_INT_PN_ENA  VTSS_BIT(24)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_ALLOW_UPSID_CPU_OR_INT_PN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Allow routing of VStaX frames received on stack port with
 * vstax.fwd_mode==FWD_LOGICAL with vstax.upsid=COMMON_VSTAX_CFG.OWN_UPSID
 * regardless of vstax.dst.dst_port.
 *
 * \details 
 * 0: Disable (allow only routing of FWD_LOGICAL if dst_port_type ==
 * port_type_intpn and dst_pn == intpn_dlookup or dst_pn == intpn_router)
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_RT_ALL_FWD_LOGICAL_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_ALL_FWD_LOGICAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_ALL_FWD_LOGICAL_ENA  VTSS_BIT(23)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_ALL_FWD_LOGICAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Allow update of vstax.src field for multicast routed frames.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_RT_MC_SRC_UPDATE_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_MC_SRC_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_MC_SRC_UPDATE_ENA  VTSS_BIT(22)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_MC_SRC_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Allow update of vstax.src field for unicast routed frames
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_RT_UC_SRC_UPDATE_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_UC_SRC_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_UC_SRC_UPDATE_ENA  VTSS_BIT(21)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_UC_SRC_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Configures value used for vstax.lrn_mode when forwarding routed IP
 * multicast frames on stack port(s).
 *
 * \details 
 * 0: lrn_mode=lrn_normal
 * 1: lrn_mode=lrn_skip
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_RT_MC_SRC_LRN_SKIP_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_MC_SRC_LRN_SKIP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_MC_SRC_LRN_SKIP_ENA  VTSS_BIT(20)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_MC_SRC_LRN_SKIP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Configures value used for vstax.lrn_mode when forwarding routed IP
 * unicast frames on stack port(s).
 *
 * \details 
 * 0: lrn_mode=lrn_normal
 * 1: lrn_mode=lrn_skip
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_RT_UC_SRC_LRN_SKIP_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_UC_SRC_LRN_SKIP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_UC_SRC_LRN_SKIP_ENA  VTSS_BIT(19)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_RT_UC_SRC_LRN_SKIP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Configures handling of IP multicast routing on stack link.
 * 
 * If IP multicast routing is performed in egress unit, then routed copies
 * shall not be forwarded on the stack ports and this parameter must thus
 * be set to 0.
 * 
 * If IP multicast routing is performed in ingress unit (or centralized),
 * then routed copies shall be forwarded on the stack ports and this
 * parameter must thus be set to 3.

 *
 * \details 
 * 0: Disable multicast on both links
 * 1: Enable multicast routing on stack link A
 * 2: Enable multicast routing on stack link B
 * 3: Enable multicast routing on both links
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_MC_ROUTE_TO_STACK_LINK_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_ROUTE_TO_STACK_LINK_ENA(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_ROUTE_TO_STACK_LINK_ENA     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_ROUTE_TO_STACK_LINK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * Forward unicast frames from front ports as fwd_mode==fwd_llookup
 * (instead of fwd_logical)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_LOGICAL_LLOOKUP_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_LOGICAL_LLOOKUP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_LOGICAL_LLOOKUP_ENA  VTSS_BIT(16)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_LOGICAL_LLOOKUP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * This can be used to enable GLAG in a stack
 * If enabled the upper GLAG*8 number of PGID multicast entries will be
 * used for GLAG
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_GLAG_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_GLAG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_GLAG_ENA  VTSS_BIT(15)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_GLAG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * This feature is to be used in 48 port switches consisting of two units
 * (i.e. chips) and where the CPU is disabled 
 * one of the units. Only the unit with the disabled CPU shall have
 * vstax2_ttl_keep==1
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_TTL_KEEP_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_TTL_KEEP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_TTL_KEEP_ENA  VTSS_BIT(14)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_TTL_KEEP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Forward unicast frames from front ports taking congestion management
 * into account
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_USE_CM_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_USE_CM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_USE_CM_ENA  VTSS_BIT(13)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_USE_CM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Forward multicast frames as fwd_mode==fwd_llookup (instead of fwd_mc).
 * 
 * Note that PTP frames will always be forwarded using fwd_llookup,
 * regardless of the value of VSTAX2_MC_LLOOKUP_ENA.

 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_MC_LLOOKUP_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_LLOOKUP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_LLOOKUP_ENA  VTSS_BIT(12)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_LLOOKUP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Forward non flooded multicast frames w. fwd_mode==fwd_llookup (instead
 * of fwd_mc)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_MC_LLOOKUP_NON_FLOOD_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_LLOOKUP_NON_FLOOD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_LLOOKUP_NON_FLOOD_ENA  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MC_LLOOKUP_NON_FLOOD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * CPU queue for VStaX frames forwarding error.
 *
 * \details 
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_FWD_ERR_QU
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_FWD_ERR_QU(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_FWD_ERR_QU     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_FWD_ERR_QU(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Enable putting DSCP into VStaX header in positions 73-68, provided that
 * VStaX header contains AC (and not ISDX) in misc section, i.e.
 * VSTAX2_MISC_ISDX_ENA=0.
 * 
 * Related parameters:
 * ANA_AC:PS_COMMON:COMMON_VSTAX_CFG.VSTAX2_MISC_ISDX_ENA
 * ANA_CL:PORT:STACKING_CTRL.VSTAX_ISDX_ENA
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_MISC_DSCP_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MISC_DSCP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MISC_DSCP_ENA  VTSS_BIT(6)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MISC_DSCP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable putting ISDX into VStaX header.
 * 
 * Related parameters:
 * ANA_CL:PORT:STACKING_CTRL.VSTAX_ISDX_ENA
 *
 * \details 
 * 0: Disable (VSTAX MISC contains Aggregation code)
 * 1: Enable (VSTAX MISC contains ISDX)
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . VSTAX2_MISC_ISDX_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MISC_ISDX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MISC_ISDX_ENA  VTSS_BIT(5)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_VSTAX2_MISC_ISDX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Specifies own UPSID
 * 
 * This must be configured consistently across the following registers:
 * ANA_CL::UPSID_CFG.UPSID_NUM
 * ANA_AC::COMMON_VSTAX_CFG.OWN_UPSID
 * ANA_L2::VSTAX_CTRL.OWN_UPSID
 * REW::COMMON_CTRL.OWN_UPSID
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG . OWN_UPSID
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_OWN_UPSID(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_OWN_UPSID     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_VSTAX_CFG_OWN_UPSID(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Common stacking parameters
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:COMMON_EQUAL_STACK_LINK_TTL_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG  VTSS_IOREG(VTSS_TO_ANA_AC,0x5708)

/** 
 * \brief
 * Controls flooding in ring topology stacks.
 * 
 * When set, frames to be flooded will be forwarded on only stack port A or
 * only stack port B.
 * TTL will be set to VSTAX2_EQUAL_STACK_LINK_TTL_VAL.
 * 
 * This feature can be used to forward flooded frames in one or the other
 * way around the ring, 
 * 
 * In such case VSTAX2_EQUAL_STACK_LINK_TTL_VAL must be set to the number
 * of units in the ring minus 1.
 * 
 * Frames with even AC will be forwarded on stack port A.
 * Frames with odd AC will be forwarded on stack port B.
 * 
 * Note that this feature is not related to equal cost forwarding. It is
 * applicable to any ring topology stack regardless of whether the number
 * of units is even or odd.
 *
 * \details 
 * 0: Disable (flood on both stack ports using the stack port's TTL)
 * 1: Enable (flood on one stack port using
 * VSTAX2_EQUAL_STACK_LINK_TTL_VAL)
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG . VSTAX2_EQUAL_STACK_LINKS_FLOOD_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG_VSTAX2_EQUAL_STACK_LINKS_FLOOD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG_VSTAX2_EQUAL_STACK_LINKS_FLOOD_ENA  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG_VSTAX2_EQUAL_STACK_LINKS_FLOOD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * TTL value used for equal cost path.
 * 
 * Only applicable for ring topology stacks with an even number of units.
 * Must be set to number of units in the stack divided by two.
 * 
 * Use of equal cost paths is enabled by
 * ANA_AC:UPSID:STACK_LINK_EQUAL_COST_CFG.STACK_LINK_EQUAL_ENA

 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG . VSTAX2_EQUAL_STACK_LINK_TTL_VAL
 */
#define  VTSS_F_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG_VSTAX2_EQUAL_STACK_LINK_TTL_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG_VSTAX2_EQUAL_STACK_LINK_TTL_VAL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ANA_AC_PS_COMMON_COMMON_EQUAL_STACK_LINK_TTL_CFG_VSTAX2_EQUAL_STACK_LINK_TTL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Per port stack configuration
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:VSTAX_CTRL
 *
 * @param ri Replicator: x_ANA_NUM_ETH_PORTS (??), 0-10
 */
#define VTSS_ANA_AC_PS_COMMON_VSTAX_CTRL(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5709 + (ri))

/** 
 * \brief
 * Specify learn and forwarding operation for the port
 *
 * \details 
 * 0: VStaX2/BF mode (Basic Forwarding mode)
 * 1: VStaX2/AF mode (Advanced Forwarding mode)
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_VSTAX_CTRL . VSTAX2_STACK_PORT_MODE
 */
#define  VTSS_F_ANA_AC_PS_COMMON_VSTAX_CTRL_VSTAX2_STACK_PORT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_PS_COMMON_VSTAX_CTRL_VSTAX2_STACK_PORT_MODE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_PS_COMMON_VSTAX_CTRL_VSTAX2_STACK_PORT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief VStaX Gmirror destination configuration
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:VSTAX_GMIRROR_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_VSTAX_GMIRROR_CFG  VTSS_IOREG(VTSS_TO_ANA_AC,0x5714)

/** 
 * \brief
 * The set of port(s) to which frames received on a stack port and with
 * fwd_mode=fwd_gmirror traffic are forwarded.
 * 
 * This is only used in VStaX context.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_VSTAX_GMIRROR_CFG . GMIRROR_PORT_MASK
 */
#define  VTSS_F_ANA_AC_PS_COMMON_VSTAX_GMIRROR_CFG_GMIRROR_PORT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_PS_COMMON_VSTAX_GMIRROR_CFG_GMIRROR_PORT_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_PS_COMMON_VSTAX_GMIRROR_CFG_GMIRROR_PORT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief CPU related parameters
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:CPU_CFG
 */
#define VTSS_ANA_AC_PS_COMMON_CPU_CFG        VTSS_IOREG(VTSS_TO_ANA_AC,0x5715)

/** 
 * \brief
 * Specifies a group of CPU queues which will only receive one frame copy
 * in total.
 * 
 * Note that CPU copies due sFlow sampling will always be generated
 * regardless of the value of ONE_CPU_COPY_ONLY_MASK.
 *
 * \details 
 * '00000000' : A frame copy will be generated for all CPU queues
 * applicable for reception
 * ...
 * 'xxxxxx11' : Only one CPU copy will be generated for CPU queue 1 and 0
 * ...
 * '11111111' : At most one frame copy will be generated for all CPU queues
 * applicable for reception
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_CPU_CFG . ONE_CPU_COPY_ONLY_MASK
 */
#define  VTSS_F_ANA_AC_PS_COMMON_CPU_CFG_ONE_CPU_COPY_ONLY_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_PS_COMMON_CPU_CFG_ONE_CPU_COPY_ONLY_MASK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_PS_COMMON_CPU_CFG_ONE_CPU_COPY_ONLY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CPU debug configuration
 *
 * \details
 * Register: \a ANA_AC:PS_COMMON:PS_DBG_CTRL
 */
#define VTSS_ANA_AC_PS_COMMON_PS_DBG_CTRL    VTSS_IOREG(VTSS_TO_ANA_AC,0x5716)

/** 
 * \brief
 * If ZERO_DST_REDIR_ENA is set and the destination port set calculation
 * for the frame results in an empty port set, then the frame gets
 * redirected to the CPU queue configured by this parameter.
 * 
 * Related parameters:
 * ANA_AC::PS_DBG_CTRL.ZERO_DST_REDIR_ENA

 *
 * \details 
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_AC_PS_COMMON_PS_DBG_CTRL . CPU_QU_ZERO_DST
 */
#define  VTSS_F_ANA_AC_PS_COMMON_PS_DBG_CTRL_CPU_QU_ZERO_DST(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_ANA_AC_PS_COMMON_PS_DBG_CTRL_CPU_QU_ZERO_DST     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_ANA_AC_PS_COMMON_PS_DBG_CTRL_CPU_QU_ZERO_DST(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * See ANA_AC::PS_DBG_CTRL.CPU_QU_ZERO_DST.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_COMMON_PS_DBG_CTRL . ZERO_DST_REDIR_ENA
 */
#define  VTSS_F_ANA_AC_PS_COMMON_PS_DBG_CTRL_ZERO_DST_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_PS_COMMON_PS_DBG_CTRL_ZERO_DST_REDIR_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_PS_COMMON_PS_DBG_CTRL_ZERO_DST_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC:MIRROR_PROBE
 *
 * Mirror probe configuration
 */


/** 
 * \brief Mirror probe configuration
 *
 * \details
 * Register: \a ANA_AC:MIRROR_PROBE:PROBE_CFG
 *
 * @param gi Replicator: x_ANA_AC_NUM_PROBE (??), 0-2
 */
#define VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5717,gi,8,0,0)

/** 
 * \brief
 * Mirror traffic from CPU,  which is set to bypass the analyzer.
 * 
 * Traffic, which is set to bypass the analyzer, is identified by the
 * following criteria:
 * IFH.FWD.DST_MODE == INJECT || IFH.MISC.PIPELINE_PT >= ANA_DONE

 *
 * \details 
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG . MIRROR_CPU_INJECT_ENA
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_MIRROR_CPU_INJECT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_CFG_MIRROR_CPU_INJECT_ENA  VTSS_BIT(31)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_CFG_MIRROR_CPU_INJECT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Controls whether physical or masqueraded port number will be used for
 * lookup in PROBE_PORT_MASK.
 * 
 * CPU injected frames with masqueraded port number are identfied by having
 * IFH.MIWC.PIPELINE_ACT == INJ_MASQ.
 * 
 * Frames, which have been looped back from Up-MEP can only be mirrored if
 * masqueraded port number is used for lookup in PROBE_PORT_MASK.
 * 
 * Related parameters:
 * ANA_AC:MIRROR_PROBE:PROBE_PORT_CFG.PROBE_PORT_MASK.

 *
 * \details 
 * 0: If frame is masqueraded, then use masqueraded port number for lookup
 * in PROBE_PORT_MASK. Otherwise use physical port number for lookup in
 * PROBE_PORT_MASK.
 * 1: Use physical port.number for lookup in PROBE_PORT_MASK.
 *
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG . PROBE_PHYS_RX_PORT
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_PHYS_RX_PORT(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_PHYS_RX_PORT  VTSS_BIT(30)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_PHYS_RX_PORT(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Mirror traffic received from CPU by this mirror probe.
 * 
 * PROBE_RX_CPU_AND_VD works as an extension of the PROBE_PORT_MASK to
 * cover CPU ports and VD0/VD1.
 *
 * \details 
 * "0000": No RX mirror
 * "xxx1": Rx from CPU port 53 is mirrored
 * "xx1x": Rx from CPU port 54 is mirrored
 * "x1xx": Rx from VD0 is mirrored
 * "1xxx": Rx from VD1 is mirrored
 * Only works with RX mirror enabled. See
 * ANA_AC:MIRROR_PROBE:PROBE_CFG.PROBE_DIRECTION.
 *
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG . PROBE_RX_CPU_AND_VD
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_RX_CPU_AND_VD(x)  VTSS_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_RX_CPU_AND_VD     VTSS_ENCODE_BITMASK(26,4)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_RX_CPU_AND_VD(x)  VTSS_EXTRACT_BITFIELD(x,26,4)

/** 
 * \brief
 * The set of CPU extraction ports from where traffic is Tx mirrored by
 * this mirror probe.
 * 
 * Only works when Tx mirroring is  enabled. 
 * 
 * Related parameters:
 * ANA_AC:MIRROR_PROBE:PROBE_CFG.PROBE_DIRECTION
 *
 * \details 
 * 0: CPU extraction port is not Tx mirrored
 * 1: CPU extraction port is Tx mirrored
 *
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG . PROBE_CPU_SET
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_CPU_SET(x)  VTSS_ENCODE_BITFIELD(x,18,8)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_CPU_SET     VTSS_ENCODE_BITMASK(18,8)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_CPU_SET(x)  VTSS_EXTRACT_BITFIELD(x,18,8)

/** 
 * \brief
 * The mirror probe's VLAN ID when PROBE_VLAN_MODE is 10 or 11.
 * 
 * Probing per VLAN can also be enabled in ANA_L3:VLAN, but such
 * configuration will affect all mirror probes.
 * 
 * Related parameters:
 * ANA_AC.MIRROR_PROBE.PROBE_CFG.PROBE_VLAN_MODE
 * ANA_L3:VLAN:VLAN_CFG.VLAN_MIRROR_ENA
 *
 * \details 
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG . PROBE_VID
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_VID(x)  VTSS_ENCODE_BITFIELD(x,6,12)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_VID     VTSS_ENCODE_BITMASK(6,12)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_VID(x)  VTSS_EXTRACT_BITFIELD(x,6,12)

/** 
 * \brief
 * Mirror probe's VLAN filtering mode.
 * 
 * Related parameters:
 * ANA_L3:VLAN:VLAN_CFG.VLAN_MIRROR_ENA
 *
 * \details 
 * 00 : No VLAN filtering
 * 01 : Mirror only traffic in VLANs with
 * ANA_L3:VLAN:VLAN_CFG.VLAN_MIRROR_ENA set
 * 10 : Mirror only traffic with CL-IVID = PROBE_VID.
 * 11 : Reserved.
 *
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG . PROBE_VLAN_MODE
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_VLAN_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_VLAN_MODE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_VLAN_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Mirror probe's MAC address filtering mode, based on the mirror bit in
 * the MAC table.

 *
 * \details 
 * "00" : No MAC filtering
 * "01" : Mirror only traffic with mirror bit set for known DMAC
 * "10" : Mirror only traffic with mirror bit set for known SMAC
 * "11" : Mirror only traffic with mirror bit set for known DMAC and/or
 * known SMAC
 *
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG . PROBE_MAC_MODE
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_MAC_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_MAC_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_MAC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Direction of traffic that is mirrored.

 *
 * \details 
 * "00" : Mirroring is disabled.
 * "01" : TX - Only traffic to destination ports in the probe port set
 * "10" : RX - Only traffic from source ports in the probe port set
 * "11" : RX+TX - Traffic to and from ports in the probe port set (always
 * mirrored as RX)
 *
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_CFG . PROBE_DIRECTION
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_DIRECTION(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_DIRECTION     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_CFG_PROBE_DIRECTION(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Mirror probe port mask configuration
 *
 * \details
 * Register: \a ANA_AC:MIRROR_PROBE:PROBE_PORT_CFG
 *
 * @param gi Replicator: x_ANA_AC_NUM_PROBE (??), 0-2
 */
#define VTSS_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5717,gi,8,0,1)

/** 
 * \brief
 * Specifies the set of ingress port(s) subject to Rx mirroring and the set
 * of egress port(s) subject to Tx mirroring.
 * 
 * PROBE_PHYS_RX_PORT controls whether physical or masqueraded port number
 * is used for lookup in PROBE_PORT_MASK.
 * PROBE_RX_CPU_AND_VD works as an extension of the PROBE_PORT_MASK to
 * cover CPU ports and VD0/VD1.
 * 
 * Ports enabled in PROBE_PORT_MASK are either RX mirrored (ingress
 * mirrored) and/or TX mirrored (egress mirrored) as determined by
 * PROBE_DIRECTION.
 * 
 * Mirror destination port(s) are determined by 
 * QFWD:SYSTEM:FRAME_COPY_CFG
 * 
 * For exact TX mirror, the configuration of this register must be
 * consistent with the configuration of
 * REW:COMMON:MIRROR_PROBE_CFG.MIRROR_TX_PORT.
 * 
 * See also description for register group ANA_AC:MIRROR_PROBE.
 * 
 * Related parameters:
 * ANA_AC:MIRROR_PROBE:PROBE_CFG.PROBE_PHYS_RX_PORT
 * ANA_AC:MIRROR_PROBE:PROBE_CFG.PROBE_RX_CPU_AND_VD
 * ANA_AC:MIRROR_PROBE:PROBE_CFG.PROBE_DIRECTION
 * REW:COMMON:MIRROR_PROBE_CFG.MIRROR_TX_PORT
 * QFWD:SYSTEM:FRAME_COPY_CFG
 *
 * \details 
 * 0: Port is not mirrored
 * 1: Port is mirrored

 *
 * Field: ::VTSS_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG . PROBE_PORT_MASK
 */
#define  VTSS_F_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG_PROBE_PORT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG_PROBE_PORT_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_MIRROR_PROBE_PROBE_PORT_CFG_PROBE_PORT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a ANA_AC:AGGR
 *
 * Aggregation port masks
 */


/** 
 * \brief Aggregation port mask
 *
 * \details
 * See ANA_AC:AGGR.
 *
 * Register: \a ANA_AC:AGGR:AGGR_CFG
 *
 * @param gi Replicator: x_ANA_NUM_AGGR (??), 0-15
 */
#define VTSS_ANA_AC_AGGR_AGGR_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x56f0,gi,1,0,0)

/** 
 * \brief
 * Aggregation port mask.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_AGGR_AGGR_CFG . PORT_MASK
 */
#define  VTSS_F_ANA_AC_AGGR_AGGR_CFG_PORT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_AGGR_AGGR_CFG_PORT_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_AGGR_AGGR_CFG_PORT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a ANA_AC:SRC
 *
 * Source port masks
 */


/** 
 * \brief Source port mask
 *
 * \details
 * Refer to description for ANA_AC:SRC.
 *
 * Register: \a ANA_AC:SRC:SRC_CFG
 *
 * @param gi Replicator: x_ANA_NUM_SRC_ENTRIES (??), 0-22
 */
#define VTSS_ANA_AC_SRC_SRC_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x53e0,gi,1,0,0)

/** 
 * \brief
 * Refer to description for ANA_AC:SRC.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_SRC_SRC_CFG . PORT_MASK
 */
#define  VTSS_F_ANA_AC_SRC_SRC_CFG_PORT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_SRC_SRC_CFG_PORT_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_SRC_SRC_CFG_PORT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a ANA_AC:SFLOW
 *
 * sFlow sampler configuration & status per port
 */


/** 
 * \brief sFlow sampler control 
 *
 * \details
 * This register configures the sFlow sampler.
 *
 * Register: \a ANA_AC:SFLOW:SFLOW_CTRL
 *
 * @param gi Replicator: x_ANA_NUM_ETH_PORTS (??), 0-10
 */
#define VTSS_ANA_AC_SFLOW_SFLOW_CTRL(gi)     VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5520,gi,2,0,0)

/** 
 * \brief
 * The current state of the sampler's PRBS (pseudorandom binary sequence).
 * 
 * SFLOW_PRBS for all samplers can be reset using SFLOW_FRAME_RESET_SHOT.
 * 
 * Related parameters:
 * ANA_AC::SFLOW_RESET_CTRL.SFLOW_FRAME_RESET_SHOT
 *
 * \details 
 * Field: ::VTSS_ANA_AC_SFLOW_SFLOW_CTRL . SFLOW_PRBS
 */
#define  VTSS_F_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_PRBS(x)  VTSS_ENCODE_BITFIELD(x,17,15)
#define  VTSS_M_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_PRBS     VTSS_ENCODE_BITMASK(17,15)
#define  VTSS_X_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_PRBS(x)  VTSS_EXTRACT_BITFIELD(x,17,15)

/** 
 * \brief
 * Configures the sampler as an ingress, egress or dual direction sampler.
 *
 * \details 
 * "00": Disable sampler.
 * "01": RX sampler (samples trafficfrom port)
 * "10": TX sampler (samples traffic to port)
 * "11": RX or TX sampler (samples traffic to and from port)
 *
 * Field: ::VTSS_ANA_AC_SFLOW_SFLOW_CTRL . SFLOW_DIR_SEL
 */
#define  VTSS_F_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_DIR_SEL(x)  VTSS_ENCODE_BITFIELD(x,15,2)
#define  VTSS_M_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_DIR_SEL     VTSS_ENCODE_BITMASK(15,2)
#define  VTSS_X_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_DIR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,15,2)

/** 
 * \brief
 * The probability with which the sampler copies frames to CPU.
 * 
 * The probability can be calculated as:
 * SFLOW_SAMPLE_RATE/32767
 *
 * \details 
 * '0x0': 0 probability, i.e. sFlow sampler is disabled.
 * '0x1': 1/32767
 * '0x7FFF': 100%, i.e. all frames are sampled by the sFlow sampler.
 *
 * Field: ::VTSS_ANA_AC_SFLOW_SFLOW_CTRL . SFLOW_SAMPLE_RATE
 */
#define  VTSS_F_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_SAMPLE_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_SAMPLE_RATE     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_ANA_AC_SFLOW_SFLOW_CTRL_SFLOW_SAMPLE_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,15)


/** 
 * \brief sFlow status counts
 *
 * \details
 * This register configures the sFlow sampler.
 *
 * Register: \a ANA_AC:SFLOW:SFLOW_CNT
 *
 * @param gi Replicator: x_ANA_NUM_ETH_PORTS (??), 0-10
 */
#define VTSS_ANA_AC_SFLOW_SFLOW_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5520,gi,2,0,1)

/** 
 * \brief
 * The number of frames sampled.
 * The counter is free running (wraps around when reaching max value).
 * 
 * The counter can be reset using 
 * ANA_AC::SFLOW_RESET_CTRL.SFLOW_FRAME_RESET_SHOT.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_SFLOW_SFLOW_CNT . SFLOW_SAMPLE_CNT
 */
#define  VTSS_F_ANA_AC_SFLOW_SFLOW_CNT_SFLOW_SAMPLE_CNT(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_ANA_AC_SFLOW_SFLOW_CNT_SFLOW_SAMPLE_CNT     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_ANA_AC_SFLOW_SFLOW_CNT_SFLOW_SAMPLE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * The number of forwarded frames.
 * The counter is free running (wraps around when reaching max value).
 * 
 * This counter can be reset using 
 * ANA_AC::SFLOW_RESET_CTRL.SFLOW_FRAME_RESET_SHOT.
 *
 * \details 
 * 0 : no entries
 *
 * Field: ::VTSS_ANA_AC_SFLOW_SFLOW_CNT . SFLOW_FRAME_FWD_CNT
 */
#define  VTSS_F_ANA_AC_SFLOW_SFLOW_CNT_SFLOW_FRAME_FWD_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_ANA_AC_SFLOW_SFLOW_CNT_SFLOW_FRAME_FWD_CNT     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_ANA_AC_SFLOW_SFLOW_CNT_SFLOW_FRAME_FWD_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a ANA_AC:UPSID
 *
 * UPSID table (one entry per UPS)
 */


/** 
 * \brief Equal cost UPSID destination configuration
 *
 * \details
 * Used for configuring equal distance to UPSID
 *
 * Register: \a ANA_AC:UPSID:STACK_LINK_EQUAL_COST_CFG
 *
 * @param gi Register: UPSID (??), 0-31
 */
#define VTSS_ANA_AC_UPSID_STACK_LINK_EQUAL_COST_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5540,gi,2,0,0)

/** 
 * \brief
 * Enable equal cost forwarding to UPSID. I.e. both stack ports (A and B)
 * are used for forwarding to UPSID.
 * 
 * If STACK_LINK_EQUAL_ENA is set, then the stack forwarding mask is
 * calculated as one of the following two, depending on AC:
 *   Even AC:
 *     UPSID_PORT_MASK &  STACK_A_MASK
 *   Odd AC:
 *     UPSID_PORT_MASK & ~STACK_A_MASK
 * 
 * Furthermore when STACK_LINK_EQUAL_ENA is set, the TTL value is set to
 *   VSTAX2_EQUAL_STACK_LINK_TTL_VAL
 * (instead of REW::VSTAX_PORT_GRP_CFG.VSTAX_TTL).
 * 
 * Related parameters:
 * ANA_AC:UPSID:UPSID_CFG.UPSID_PORT_MASK
 * ANA_AC:PS_COMMON:STACK_A_CFG.STACK_A_MASK
 * ANA_AC:PS_COMMON:COMMON_EQUAL_STACK_LINK_TTL_CFG.VSTAX2_EQUAL_STACK_LINK
 * _TTL_VAL
 * REW:COMMON:VSTAX_PORT_GRP_CFG.VSTAX_TTL
 *
 * \details 
 * Field: ::VTSS_ANA_AC_UPSID_STACK_LINK_EQUAL_COST_CFG . STACK_LINK_EQUAL_ENA
 */
#define  VTSS_F_ANA_AC_UPSID_STACK_LINK_EQUAL_COST_CFG_STACK_LINK_EQUAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_UPSID_STACK_LINK_EQUAL_COST_CFG_STACK_LINK_EQUAL_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_UPSID_STACK_LINK_EQUAL_COST_CFG_STACK_LINK_EQUAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief UPSID destination configuration
 *
 * \details
 * Configures which physical ports to be used for reaching a given UPSID.
 *
 * Register: \a ANA_AC:UPSID:UPSID_CFG
 *
 * @param gi Register: UPSID (??), 0-31
 */
#define VTSS_ANA_AC_UPSID_UPSID_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5540,gi,2,0,1)

/** 
 * \brief
 * UPSID port mask.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_UPSID_UPSID_CFG . UPSID_PORT_MASK
 */
#define  VTSS_F_ANA_AC_UPSID_UPSID_CFG_UPSID_PORT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_UPSID_UPSID_CFG_UPSID_PORT_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_UPSID_UPSID_CFG_UPSID_PORT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a ANA_AC:GLAG
 *
 * Configuration for Global Link Aggregation Groups
 */


/** 
 * \brief GLAG member count configuration
 *
 * \details
 * Register: \a ANA_AC:GLAG:MBR_CNT_CFG
 *
 * @param gi Replicator: x_ANA_NUM_GLAG (??), 0-7
 */
#define VTSS_ANA_AC_GLAG_MBR_CNT_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x53f8,gi,1,0,0)

/** 
 * \brief
 * GLAG member count.
 * 
 * This is used to select the GLAG port mask within the GLAG part of
 * ANA_AC:PGID.
 * 
 * Using GLAG_MBR_CNT a GLAG_MBR_IDX is calculated as follows:
 * GLAG_MBR_IDX = frame.ac % GLAG_MBR_CNT
 * 
 * The frame's GLAGID and GLAG_MBR_IDX are then used for lookup in
 * ANA_AC:PGID.
 *
 * \details 
 * 0: One member
 * 1: Two members
 * ...
 * 7: Eight members
 *
 * Field: ::VTSS_ANA_AC_GLAG_MBR_CNT_CFG . GLAG_MBR_CNT
 */
#define  VTSS_F_ANA_AC_GLAG_MBR_CNT_CFG_GLAG_MBR_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_ANA_AC_GLAG_MBR_CNT_CFG_GLAG_MBR_CNT     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_ANA_AC_GLAG_MBR_CNT_CFG_GLAG_MBR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * Register Group: \a ANA_AC:PGID
 *
 * Port group ID table configurations
 */


/** 
 * \brief PGID port mask / destination configuration
 *
 * \details
 * Register: \a ANA_AC:PGID:PGID_CFG
 *
 * @param gi Replicator: x_ANA_NUM_PGID_TBL_ENTRIES (??), 0-138
 */
#define VTSS_ANA_AC_PGID_PGID_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5400,gi,2,0,0)

/** 
 * \brief
 * PGID port mask or stack forwarding information, depending on
 * STACK_TYPE_ENA.
 * 
 * Related parameters:
 * ANA_AC:PGID:PGID_MISC_CFG.STACK_TYPE_ENA
 *
 * \details 
 * PGID_MISC_CFG.STACK_TYPE_ENA=0:
 * Destination port mask.
 * 
 * PGID_MISC_CFG.STACK_TYPE_ENA=1:
 * Bit 4:0 
 * VStaX destination UPSPN.
 * 
 * Bit 5 
 * VStaX destination port type. 0=Normal UPSPN, 1=Internal port (advanced
 * use).
 * 
 * Bit 10:6  
 * VStaX destination UPSID
 *  
 * Bit 13:11 
 * VStaX forwarding mode.
 * Only used if PGID origins from multicast index in MAC table.
 * In all other cases bit 13:11 must be 0.
 * Encoding:
 * '001': fwd_logical. Forward to logical front port at specific UPS, using
 * (UPSID, UPSPN).
 * '010': fwd_physical. Forward to physical front port at specific UPS,
 * using (UPSID, UPSPN).
 * '101': fwd_gcpu_ups. Forward to GCPU of specific UPS (identified by
 * UPSID).
 * Other: Reserved.
 * 
 * If bit 10:6 is a remote UPSID, then 20:16 must be set to 0.
 * If bit 10:6 is the a UPSID, then 20:16 must be set to same value as bit
 * 4:0.
 *
 * Field: ::VTSS_ANA_AC_PGID_PGID_CFG . PORT_MASK
 */
#define  VTSS_F_ANA_AC_PGID_PGID_CFG_PORT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_PGID_PGID_CFG_PORT_MASK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_PGID_PGID_CFG_PORT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Miscellaneous PGID configuration
 *
 * \details
 * Register: \a ANA_AC:PGID:PGID_MISC_CFG
 *
 * @param gi Replicator: x_ANA_NUM_PGID_TBL_ENTRIES (??), 0-138
 */
#define VTSS_ANA_AC_PGID_PGID_MISC_CFG(gi)   VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5400,gi,2,0,1)

/** 
 * \brief
 * CPU queue for frames copied to CPU due to PGID_CPU_COPY_ENA.
 * 
 * Related parameters:
 * ANA_AC:PGID:PGID_MISC_CFG.PGID_CPU_COPY_ENA
 *
 * \details 
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_AC_PGID_PGID_MISC_CFG . PGID_CPU_QU
 */
#define  VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Encoding of PGID_CFG.PORT_MASK.
 * 
 * Related parameters:
 * ANA_AC:PGID[0-1076]:PGID_CFG.PORT_MASK
 *
 * \details 
 * 0: Port mask encoding
 * 1: Stack forwarding encoding
 *
 * Field: ::VTSS_ANA_AC_PGID_PGID_MISC_CFG . STACK_TYPE_ENA
 */
#define  VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_STACK_TYPE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_PGID_PGID_MISC_CFG_STACK_TYPE_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_STACK_TYPE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Copy frame to CPU.
 * 
 * Related parameters:
 * ANA_AC:PGID:PGID_MISC_CFG.PGID_CPU_QU
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PGID_PGID_MISC_CFG . PGID_CPU_COPY_ENA
 */
#define  VTSS_F_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_PGID_PGID_MISC_CFG_PGID_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC:PS_STICKY
 *
 * Diagnostic information
 */


/** 
 * \brief Diagnostic information
 *
 * \details
 * Diagnostic sticky bits.
 *
 * Register: \a ANA_AC:PS_STICKY:STICKY
 */
#define VTSS_ANA_AC_PS_STICKY_STICKY         VTSS_IOREG(VTSS_TO_ANA_AC,0x5518)

/** 
 * \brief
 * Set if frame is redirected due to VCAP IS2. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * 0: No redir event
 * 1: A frame was redirected.
 *
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . ACL_REDIR_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_ACL_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_ACL_REDIR_STICKY  VTSS_BIT(24)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_ACL_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Set if a mirror probe has been triggered. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * 0: Mirror probe not triggered
 * 1: Mirror probe triggered
 *
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . PROBE_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_PROBE_STICKY(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_PROBE_STICKY     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_PROBE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/** 
 * \brief
 * Set if the egress port mask for a frame was zero and the frame was not
 * sent to the CPU. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . ZERO_DST_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_ZERO_DST_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_ZERO_DST_STICKY  VTSS_BIT(17)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_ZERO_DST_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Set if a frame has been forwarded with a non-zero destination set. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * 0: No frames forwarded
 * 1: Frame forward event
 *
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . FRAME_FWD_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_FRAME_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_FRAME_FWD_STICKY  VTSS_BIT(16)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_FRAME_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Set if a frame, candidate for sFlow sampling, was found.
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . SFLOW_CAND_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_SFLOW_CAND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_SFLOW_CAND_STICKY  VTSS_BIT(15)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_SFLOW_CAND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set if a sFlow destination sample event has taken place. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * 0: No event
 * 1: A sample event has occured
 *
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . SFLOW_DST_SAMPLE_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_SFLOW_DST_SAMPLE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_SFLOW_DST_SAMPLE_STICKY  VTSS_BIT(14)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_SFLOW_DST_SAMPLE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set if a sFlow source sample event has taken place. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * 0: No event
 * 1: A sample event has occured
 *
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . SFLOW_SRC_SAMPLE_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_SFLOW_SRC_SAMPLE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_SFLOW_SRC_SAMPLE_STICKY  VTSS_BIT(13)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_SFLOW_SRC_SAMPLE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set if a sFlow sample event has taken place. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * 0: No event
 * 1: A sample event has occured
 *
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . SFLOW_SAMPLE_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_SFLOW_SAMPLE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_SFLOW_SAMPLE_STICKY  VTSS_BIT(12)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_SFLOW_SAMPLE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set if VLAN mask has been used. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . VLAN_CONTRIB_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_VLAN_CONTRIB_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_VLAN_CONTRIB_STICKY  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_VLAN_CONTRIB_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set if the GLAG source mask has been used. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . GLAG_CONTRIB_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_GLAG_CONTRIB_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_GLAG_CONTRIB_STICKY  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_GLAG_CONTRIB_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set if the source mask has been used. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . SRC_CONTRIB_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_SRC_CONTRIB_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_SRC_CONTRIB_STICKY  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_SRC_CONTRIB_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set if a CPU copy operation from the PGID lookup has been done. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . PGID_CPU_MASK_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_PGID_CPU_MASK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_PGID_CPU_MASK_STICKY  VTSS_BIT(7)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_PGID_CPU_MASK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set if the previous blocks in the Analyzer have signaled that a frame
 * must not be forwarded. This may be done for CPU move or discard
 * operations. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . NO_L2_L3_FWD_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_NO_L2_L3_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_NO_L2_L3_FWD_STICKY  VTSS_BIT(6)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_NO_L2_L3_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set if ip6_mc_ctrl_flood_mask has been used.
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . IP6_MC_CTRL_FLOOD_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_IP6_MC_CTRL_FLOOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_IP6_MC_CTRL_FLOOD_STICKY  VTSS_BIT(5)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_IP6_MC_CTRL_FLOOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set if ip6_mc_data_flood_mask has been used.
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . IP6_MC_DATA_FLOOD_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_IP6_MC_DATA_FLOOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_IP6_MC_DATA_FLOOD_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_IP6_MC_DATA_FLOOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set if ip4_mc_ctrl_flood_mask has been used.
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . IP4_MC_CTRL_FLOOD_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_IP4_MC_CTRL_FLOOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_IP4_MC_CTRL_FLOOD_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_IP4_MC_CTRL_FLOOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if ip4_mc_data_flood_mask has been used.
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . IP4_MC_DATA_FLOOD_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_IP4_MC_DATA_FLOOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_IP4_MC_DATA_FLOOD_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_IP4_MC_DATA_FLOOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set if l2_mc_flood_mask has been used.
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . L2_MC_FLOOD_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_L2_MC_FLOOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_L2_MC_FLOOD_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_L2_MC_FLOOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if the unicast flood mask has been used. 
 * 
 * Write 1 to clear this field.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_STICKY . UC_FLOOD_STICKY
 */
#define  VTSS_F_ANA_AC_PS_STICKY_STICKY_UC_FLOOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_PS_STICKY_STICKY_UC_FLOOD_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_PS_STICKY_STICKY_UC_FLOOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC:PS_STICKY_MASK
 *
 * Counter configuration for diagnostic information
 */


/** 
 * \brief Sticky diagnostic counter masks
 *
 * \details
 * Register: \a ANA_AC:PS_STICKY_MASK:STICKY_MASK
 *
 * @param gi Replicator: x_ANA_NUM_CONCURRENT_CNT (??), 0-3
 */
#define VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x572f,gi,16,0,0)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . PROBE_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_PROBE_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_PROBE_STICKY_MASK     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_PROBE_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . ZERO_DST_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_ZERO_DST_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_ZERO_DST_STICKY_MASK  VTSS_BIT(17)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_ZERO_DST_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . FRAME_FWD_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_FRAME_FWD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_FRAME_FWD_STICKY_MASK  VTSS_BIT(16)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_FRAME_FWD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . SFLOW_CAND_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_CAND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_CAND_STICKY_MASK  VTSS_BIT(15)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_CAND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . SFLOW_DST_SAMPLE_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_DST_SAMPLE_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_DST_SAMPLE_STICKY_MASK  VTSS_BIT(14)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_DST_SAMPLE_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . SFLOW_SRC_SAMPLE_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_SRC_SAMPLE_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_SRC_SAMPLE_STICKY_MASK  VTSS_BIT(13)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_SRC_SAMPLE_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . SFLOW_SAMPLE_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_SAMPLE_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_SAMPLE_STICKY_MASK  VTSS_BIT(12)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SFLOW_SAMPLE_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . VLAN_CONTRIB_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_VLAN_CONTRIB_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_VLAN_CONTRIB_STICKY_MASK  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_VLAN_CONTRIB_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . GLAG_CONTRIB_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_GLAG_CONTRIB_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_GLAG_CONTRIB_STICKY_MASK  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_GLAG_CONTRIB_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . SRC_CONTRIB_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SRC_CONTRIB_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SRC_CONTRIB_STICKY_MASK  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_SRC_CONTRIB_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . PGID_CPU_MASK_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_PGID_CPU_MASK_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_PGID_CPU_MASK_STICKY_MASK  VTSS_BIT(7)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_PGID_CPU_MASK_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . NO_L2_L3_FWD_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_NO_L2_L3_FWD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_NO_L2_L3_FWD_STICKY_MASK  VTSS_BIT(6)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_NO_L2_L3_FWD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . IP6_MC_CTRL_FLOOD_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP6_MC_CTRL_FLOOD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP6_MC_CTRL_FLOOD_STICKY_MASK  VTSS_BIT(5)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP6_MC_CTRL_FLOOD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . IP6_MC_DATA_FLOOD_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP6_MC_DATA_FLOOD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP6_MC_DATA_FLOOD_STICKY_MASK  VTSS_BIT(4)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP6_MC_DATA_FLOOD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . IP4_MC_CTRL_FLOOD_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP4_MC_CTRL_FLOOD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP4_MC_CTRL_FLOOD_STICKY_MASK  VTSS_BIT(3)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP4_MC_CTRL_FLOOD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Mask to enable counting of sticky event.
 *
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . IP4_MC_DATA_FLOOD_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP4_MC_DATA_FLOOD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP4_MC_DATA_FLOOD_STICKY_MASK  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_IP4_MC_DATA_FLOOD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . L2_MC_FLOOD_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_L2_MC_FLOOD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_L2_MC_FLOOD_STICKY_MASK  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_L2_MC_FLOOD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Mask to enable counting of sticky event.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK . UC_FLOOD_STICKY_MASK
 */
#define  VTSS_F_ANA_AC_PS_STICKY_MASK_STICKY_MASK_UC_FLOOD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_UC_FLOOD_STICKY_MASK  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_PS_STICKY_MASK_STICKY_MASK_UC_FLOOD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC:STAT_GLOBAL_CFG_PORT
 *
 * Common counter configuration.
 */


/** 
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_PORT:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-3
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5519 + (ri))

/** 
 * \brief
 * This value stores the event mask which indicates the counter of all
 * flows to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 *  
 *  Which type of frame is counted is defined in: STAT_CFG,
 * CFG_CNT_FRM_TYPE.
 * 
 *  The following events apply to port stat:
 *  bit0: Count events allowed by *_sticky_mask:0
 *  bit1: Count events allowed by *_sticky_mask:1
 *  ...
 *  bit3: Count events allowed by *_sticky_mask:n 
 *  where n is number of counter event masks
 * 
 *  bit4: Count port policer:0 drop events
 *  bit5: Count port policer:1 drop events
 *  bit6: Count port policer:0 pass/active events
 *  bit7: Count port policer:1 pass/active events
 *  where m is number of per port policers
 *  ...
 *  bit8: Count storm policer drop events
 *  bit9: Count outer policer drop events
 *  bit10: Count inner policer drop events
 *  bit11: Count lbk frame. 
 *
 * \details 
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Reset all counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_PORT:STAT_RESET
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET  VTSS_IOREG(VTSS_TO_ANA_AC,0x551d)

/** 
 * \brief
 * Write '1' to this field to reset all counters and configuration for this
 * stat group.
 * 
 * The device will set the bit back to '0' when reset has completed.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET . RESET
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET_RESET  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET_RESET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC:STAT_CNT_CFG_PORT
 *
 * Individual configuration.
 */


/** 
 * \brief Sticky bits for events.
 *
 * \details
 * It is the sticky bits of events. If one event is triggered, the
 * corresponding bit is set to '1' before it is cleared. To write '1' into
 * this bit will clear the sticky bit.
 *
 * Register: \a ANA_AC:STAT_CNT_CFG_PORT:STAT_EVENTS_STICKY
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-14
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_EVENTS_STICKY(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5600,gi,16,0,0)

/** 
 * \brief
 * These are the sticky bits of events. There is a sticky bit for an event
 * for each flow.
 *
 * \details 
 * '1': The corresponding event is triggered since it is cleared last time.
 * '0': No such event is triggered since it is cleared last time.
 *
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_EVENTS_STICKY . STICKY_BITS
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_EVENTS_STICKY_STICKY_BITS(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_PORT_STAT_EVENTS_STICKY_STICKY_BITS     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_PORT_STAT_EVENTS_STICKY_STICKY_BITS(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Event handling configuration.
 *
 * \details
 * This register group defines how to handle the incoming events.
 *
 * Register: \a ANA_AC:STAT_CNT_CFG_PORT:STAT_CFG
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-14
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-3
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5600,gi,16,ri,1)

/** 
 * \brief
 * This field is to configure the counters of a flow to count frames with
 * certain priorities.
 * The field contains one bit per priority.
 * 
 * Note that with the default value of this field, counting is disabled for
 * all priorities.
 *
 * \details 
 * 0: Do not count frames with this priority.
 * 1: Count frames with this priority.
 *
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG . CFG_PRIO_MASK
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_PRIO_MASK(x)  VTSS_ENCODE_BITFIELD(x,4,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_PRIO_MASK     VTSS_ENCODE_BITMASK(4,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_PRIO_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,8)

/** 
 * \brief
 * Selects which frames to count.
 *
 * \details 
 * "000": The frames without any event signal or frame error signal
 * asserted are counted.
 * "001": The frames with unmasked (enabled) events asserted but with no
 * error indications are counted.
 * "010": The frames with both event signal and the error signal asserted
 * are counted.
 * "011": The frames with event signal asserted are counted in spite of the
 * error indications.
 * "100": The frames with the error signal asserted, but with no event
 * signal are counted.
 * "101": The frames with error signal asserted are counted in spite of the
 * accompied event indications.
 * 
 *	| Error | Event
 * -----+-------+------
 *  000 |   N	|   N  
 * -----+-------+------
 *  001 |   N	|   Y  
 * -----+-------+------
 *  010 |   Y	|   Y  
 * -----+-------+------
 *  011 |   -	|   Y  
 * -----+-------+------
 *  100 |   Y	|   N  
 * -----+-------+------
 *  101 |   Y	|   -  
 * -----+-------+------
 *
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG . CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * Configure whether to count frames or bytes.
 *
 * \details 
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG . CFG_CNT_BYTE
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_PORT:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-14
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-3
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_LSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5600,gi,16,ri,5)

/** 
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_PORT_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_PORT_STAT_LSB_CNT_LSB_CNT(x)  (x)


/** 
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_PORT:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-14
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-3
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_MSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5600,gi,16,ri,9)

/** 
 * \brief
 * The counter's most significant 8 bits.
 * 
 * The field stores the value in the counters of a flow from bit 32 to the
 * most significant bit. 
 * 
 * Reading:
 * The MSB part of the counter is latched to a shadow register, when the
 * LSB part is read. 
 * As a result, the LSB part must always be read first, and the MSB part
 * must be read immediately after the LSB part is read. 
 * 
 * Writing:
 * The procedure for writing differs depending on counter group:
 * ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed by
 * MSB part.
 * All other counter groups: MSB part must be written first, followed by
 * LSB part.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_PORT_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_PORT_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ANA_AC:STAT_GLOBAL_CFG_ACL
 *
 * Common counter configuration.
 */


/** 
 * \brief Common frame type configuration
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ACL:GLOBAL_CNT_FRM_TYPE_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ACL_GLOBAL_CNT_FRM_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5536 + (ri))

/** 
 * \brief
 * Configures which frames is counted in relation to FCS error and
 * configured event mask (GLOBAL_EVENT_MASK).
 *
 * \details 
 * 
 * "000": Frames without any event signal or FCS errored frames are
 * counted.
 * "001": Frames with unmasked (enabled) events without FCS error are
 * counted.
 * "010": Frames with unmasked (enabled) events with FCS error are counted.
 * "011": Frames with unmasked (enabled) events independent of FCS error
 * are counted.
 * "100": Frames with FCS error but with no event signal are counted.
 * "101": Frames with FCS error are unconditionally counted.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ACL_GLOBAL_CNT_FRM_TYPE_CFG . GLOBAL_CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ACL_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ACL_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ACL_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Global configuration register
 *
 * \details
 * Global configuration register
 *
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ACL:STAT_GLOBAL_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5538 + (ri))

/** 
 * \brief
 * This field is to configure the counters of all flows to count the byte
 * number or the frame number.
 *
 * \details 
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_CFG . GLOBAL_CFG_CNT_BYTE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ACL:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x553a + (ri))

/** 
 * \brief
 * This value stores the event mask which indicates the counter of all
 * flows to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 * 
 *  The following events apply to ACL stat: 
 *  Bit0: Count CPU traffic applicable for CPU ACL policer but not
 * discarded
 *  Bit1: Count front port traffic applicable for ACL policer but not
 * discarded
 *  Bit2: Count CPU traffic discarded by ACL policer
 *  Bit3: Count front port traffic discarded by ACL policer 
 *
 * \details 
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ACL_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a ANA_AC:STAT_CNT_CFG_ACL
 *
 * Individual configuration.
 */


/** 
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_ACL:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-31
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_ACL_STAT_LSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5580,gi,4,ri,0)

/** 
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_ACL_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_ACL_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_ACL_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_ACL_STAT_LSB_CNT_LSB_CNT(x)  (x)


/** 
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_ACL:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-31
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_ACL_STAT_MSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5580,gi,4,ri,2)

/** 
 * \brief
 * The counter's most significant 8 bits.
 * 
 * The field stores the value in the counters of a flow from bit 32 to the
 * most significant bit. 
 * 
 * Reading:
 * The MSB part of the counter is latched to a shadow register, when the
 * LSB part is read. 
 * As a result, the LSB part must always be read first, and the MSB part
 * must be read immediately after the LSB part is read. 
 * 
 * Writing:
 * The procedure for writing differs depending on counter group:
 * ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed by
 * MSB part.
 * All other counter groups: MSB part must be written first, followed by
 * LSB part.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_ACL_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_ACL_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_ACL_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_ACL_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ANA_AC:STAT_GLOBAL_CFG_QUEUE
 *
 * Common counter configuration.
 */


/** 
 * \brief Common frame type configuration
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_QUEUE:GLOBAL_CNT_FRM_TYPE_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x576f + (ri))

/** 
 * \brief
 * Configures which frames is counted in relation to FCS error and
 * configured event mask (GLOBAL_EVENT_MASK).
 *
 * \details 
 * 
 * "000": Frames without any event signal or FCS errored frames are
 * counted.
 * "001": Frames with unmasked (enabled) events without FCS error are
 * counted.
 * "010": Frames with unmasked (enabled) events with FCS error are counted.
 * "011": Frames with unmasked (enabled) events independent of FCS error
 * are counted.
 * "100": Frames with FCS error but with no event signal are counted.
 * "101": Frames with FCS error are unconditionally counted.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG . GLOBAL_CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Global configuration register
 *
 * \details
 * Global configuration register
 *
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_QUEUE:STAT_GLOBAL_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5771 + (ri))

/** 
 * \brief
 * This field is to configure the counters of all flows to count the byte
 * number or the frame number.
 *
 * \details 
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_CFG . GLOBAL_CFG_CNT_BYTE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_QUEUE:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5773 + (ri))

/** 
 * \brief
 * This value stores the event mask which indicates the counter of all
 * flows to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 * 
 *  The following events apply to queue stat:
 *  Bit0: Count traffic applicable for queue policer but not discarded
 *  Bit1: Count traffic discarded by queue policer
 *
 * \details 
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_QUEUE_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a ANA_AC:STAT_CNT_CFG_QUEUE
 *
 * Individual configuration.
 */


/** 
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_QUEUE:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-119
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_LSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5200,gi,4,ri,0)

/** 
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_LSB_CNT_LSB_CNT(x)  (x)


/** 
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_QUEUE:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-119
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_MSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5200,gi,4,ri,2)

/** 
 * \brief
 * The counter's most significant 8 bits.
 * 
 * The field stores the value in the counters of a flow from bit 32 to the
 * most significant bit. 
 * 
 * Reading:
 * The MSB part of the counter is latched to a shadow register, when the
 * LSB part is read. 
 * As a result, the LSB part must always be read first, and the MSB part
 * must be read immediately after the LSB part is read. 
 * 
 * Writing:
 * The procedure for writing differs depending on counter group:
 * ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed by
 * MSB part.
 * All other counter groups: MSB part must be written first, followed by
 * LSB part.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_QUEUE_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ANA_AC:STAT_GLOBAL_CFG_ISDX
 *
 * Common counter configuration.
 */


/** 
 * \brief Common frame type configuration
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ISDX:GLOBAL_CNT_FRM_TYPE_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_GLOBAL_CNT_FRM_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5775 + (ri))

/** 
 * \brief
 * Configures which frames is counted in relation to FCS error and
 * configured event mask (GLOBAL_EVENT_MASK).
 *
 * \details 
 * 
 * "000": Frames without any event signal or FCS errored frames are
 * counted.
 * "001": Frames with unmasked (enabled) events without FCS error are
 * counted.
 * "010": Frames with unmasked (enabled) events with FCS error are counted.
 * "011": Frames with unmasked (enabled) events independent of FCS error
 * are counted.
 * "100": Frames with FCS error but with no event signal are counted.
 * "101": Frames with FCS error are unconditionally counted.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_GLOBAL_CNT_FRM_TYPE_CFG . GLOBAL_CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ISDX_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ISDX_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Global configuration register
 *
 * \details
 * Global configuration register
 *
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ISDX:STAT_GLOBAL_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x577b + (ri))

/** 
 * \brief
 * This field is to configure the counters of all flows to count the byte
 * number or the frame number.
 *
 * \details 
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG . GLOBAL_CFG_CNT_BYTE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ISDX:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5781 + (ri))

/** 
 * \brief
 * This value stores the event mask which indicates the counter of all
 * flows to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 *  
 *  Which type of frame is counted is defined in: STAT_GLOBAL_CFG.
 *  
 *  The following events apply to ISDX stat:
 *  For CE:
 *  Bit0: Count GREEN traffic
 *  Bit1: Count YELLOW traffic
 *  Bit2: Count RED traffic
 *  
 *  For SME:
 *  Bit3: Count unicast traffic
 *  Bit4: Count multicast traffic
 *  Bit5: Count flooded traffic
 *  Bit6: Count broadcast traffic 
 *
 * \details 
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a ANA_AC:STAT_CNT_CFG_ISDX
 *
 * Individual configuration.
 */


/** 
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_ISDX:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-1023
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x0,gi,16,ri,0)

/** 
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_ISDX_STAT_LSB_CNT_LSB_CNT(x)  (x)


/** 
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_ISDX:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-1023
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-2
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x0,gi,16,ri,6)

/** 
 * \brief
 * The counter's most significant 8 bits.
 * 
 * The field stores the value in the counters of a flow from bit 32 to the
 * most significant bit. 
 * 
 * Reading:
 * The MSB part of the counter is latched to a shadow register, when the
 * LSB part is read. 
 * As a result, the LSB part must always be read first, and the MSB part
 * must be read immediately after the LSB part is read. 
 * 
 * Writing:
 * The procedure for writing differs depending on counter group:
 * ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed by
 * MSB part.
 * All other counter groups: MSB part must be written first, followed by
 * LSB part.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ANA_AC:STAT_GLOBAL_CFG_BDLB
 *
 * Common counter configuration.
 */


/** 
 * \brief Common frame type configuration
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_BDLB:GLOBAL_CNT_FRM_TYPE_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_BDLB_GLOBAL_CNT_FRM_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5787 + (ri))

/** 
 * \brief
 * Configures which frames is counted in relation to FCS error and
 * configured event mask (GLOBAL_EVENT_MASK).
 *
 * \details 
 * 
 * "000": Frames without any event signal or FCS errored frames are
 * counted.
 * "001": Frames with unmasked (enabled) events without FCS error are
 * counted.
 * "010": Frames with unmasked (enabled) events with FCS error are counted.
 * "011": Frames with unmasked (enabled) events independent of FCS error
 * are counted.
 * "100": Frames with FCS error but with no event signal are counted.
 * "101": Frames with FCS error are unconditionally counted.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_BDLB_GLOBAL_CNT_FRM_TYPE_CFG . GLOBAL_CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_BDLB_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_BDLB_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_BDLB_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Global configuration register
 *
 * \details
 * Global configuration register
 *
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_BDLB:STAT_GLOBAL_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5789 + (ri))

/** 
 * \brief
 * This field is to configure the counters of all flows to count the byte
 * number or the frame number.
 *
 * \details 
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_CFG . GLOBAL_CFG_CNT_BYTE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_BDLB:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x578b + (ri))

/** 
 * \brief
 * This value stores the event mask which controls the counter of all
 * bundle stats to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 *  
 *  Which type of frame is counted is defined in: STAT_GLOBAL_CFG.
 *  
 *  The following events apply to Bundle DLB stat:
 *  Bit0: Count GREEN traffic
 *  Bit1: Count YELLOW traffic
 *  Bit2: Count RED traffic
 *
 * \details 
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_BDLB_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a ANA_AC:STAT_CNT_CFG_BDLB
 *
 * Individual configuration.
 */


/** 
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_BDLB:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-127
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_BDLB_STAT_LSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5000,gi,4,ri,0)

/** 
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_BDLB_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_BDLB_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_BDLB_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_BDLB_STAT_LSB_CNT_LSB_CNT(x)  (x)


/** 
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_BDLB:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-127
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-1
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_BDLB_STAT_MSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x5000,gi,4,ri,2)

/** 
 * \brief
 * The counter's most significant 8 bits.
 * 
 * The field stores the value in the counters of a flow from bit 32 to the
 * most significant bit. 
 * 
 * Reading:
 * The MSB part of the counter is latched to a shadow register, when the
 * LSB part is read. 
 * As a result, the LSB part must always be read first, and the MSB part
 * must be read immediately after the LSB part is read. 
 * 
 * Writing:
 * The procedure for writing differs depending on counter group:
 * ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed by
 * MSB part.
 * All other counter groups: MSB part must be written first, followed by
 * LSB part.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_BDLB_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_BDLB_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_BDLB_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_BDLB_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ANA_AC:STAT_GLOBAL_CFG_BUM
 *
 * Common counter configuration.
 */


/** 
 * \brief Common frame type configuration
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_BUM:GLOBAL_CNT_FRM_TYPE_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_BUM_GLOBAL_CNT_FRM_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x578d + (ri))

/** 
 * \brief
 * Configures which frames is counted in relation to FCS error and
 * configured event mask (GLOBAL_EVENT_MASK).
 *
 * \details 
 * 
 * "000": Frames without any event signal or FCS errored frames are
 * counted.
 * "001": Frames with unmasked (enabled) events without FCS error are
 * counted.
 * "010": Frames with unmasked (enabled) events with FCS error are counted.
 * "011": Frames with unmasked (enabled) events independent of FCS error
 * are counted.
 * "100": Frames with FCS error but with no event signal are counted.
 * "101": Frames with FCS error are unconditionally counted.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_BUM_GLOBAL_CNT_FRM_TYPE_CFG . GLOBAL_CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_BUM_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_BUM_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_BUM_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Global configuration register
 *
 * \details
 * Global configuration register
 *
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_BUM:STAT_GLOBAL_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5793 + (ri))

/** 
 * \brief
 * This field is to configure the counters of all flows to count the byte
 * number or the frame number.
 *
 * \details 
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_CFG . GLOBAL_CFG_CNT_BYTE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_BUM:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x5799 + (ri))

/** 
 * \brief
 * This value stores the event mask which controls the counter of all
 * bundle stats to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 *  
 *  Which type of frame is counted is defined in: STAT_GLOBAL_CFG.
 *  
 *  The following events apply to Bundle DLB stat:
 *  Bit0: Count Broadcast traffic discarded by BUM policer
 *  Bit1: Count Multicast traffic discarded by BUM policer
 *  Bit2: Count Unicast traffic discarded by BUM policer
 *  Bit3: Count Broadcast traffic applicable for BUM policer but not
 * discarded
 *  Bit4: Count Multicast traffic applicable for BUM policer but not
 * discarded
 *  Bit5: Count Unicast traffic applicable for BUM policer but not
 * discarded
 *
 * \details 
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_BUM_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a ANA_AC:STAT_CNT_CFG_BUM
 *
 * Individual configuration.
 */


/** 
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_BUM:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-127
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_BUM_STAT_LSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x4000,gi,16,ri,0)

/** 
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_BUM_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_BUM_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_BUM_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_BUM_STAT_LSB_CNT_LSB_CNT(x)  (x)


/** 
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_BUM:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-127
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-5
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_BUM_STAT_MSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x4000,gi,16,ri,6)

/** 
 * \brief
 * The counter's most significant 8 bits.
 * 
 * The field stores the value in the counters of a flow from bit 32 to the
 * most significant bit. 
 * 
 * Reading:
 * The MSB part of the counter is latched to a shadow register, when the
 * LSB part is read. 
 * As a result, the LSB part must always be read first, and the MSB part
 * must be read immediately after the LSB part is read. 
 * 
 * Writing:
 * The procedure for writing differs depending on counter group:
 * ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed by
 * MSB part.
 * All other counter groups: MSB part must be written first, followed by
 * LSB part.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_BUM_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_BUM_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_BUM_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_BUM_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ANA_AC:STAT_GLOBAL_CFG_IRLEG
 *
 * Common counter configuration.
 */


/** 
 * \brief Common frame type configuration
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_IRLEG:GLOBAL_CNT_FRM_TYPE_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_GLOBAL_CNT_FRM_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x579f + (ri))

/** 
 * \brief
 * Configures which frames is counted in relation to FCS error and
 * configured event mask (GLOBAL_EVENT_MASK).
 *
 * \details 
 * 
 * "000": Frames without any event signal or FCS errored frames are
 * counted.
 * "001": Frames with unmasked (enabled) events without FCS error are
 * counted.
 * "010": Frames with unmasked (enabled) events with FCS error are counted.
 * "011": Frames with unmasked (enabled) events independent of FCS error
 * are counted.
 * "100": Frames with FCS error but with no event signal are counted.
 * "101": Frames with FCS error are unconditionally counted.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_GLOBAL_CNT_FRM_TYPE_CFG . GLOBAL_CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_IRLEG_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_IRLEG_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_IRLEG_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Global configuration register
 *
 * \details
 * Global configuration register
 *
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_IRLEG:STAT_GLOBAL_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x57a7 + (ri))

/** 
 * \brief
 * This field is to configure the counters of all flows to count the byte
 * number or the frame number.
 *
 * \details 
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_CFG . GLOBAL_CFG_CNT_BYTE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_IRLEG:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x57af + (ri))

/** 
 * \brief
 * This value stores the event mask which indicates the counter of all
 * flows to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 *  
 *  Which type of frame is counted is defined in: STAT_CFG,
 * CFG_CNT_FRM_TYPE.
 * 
 *  The following events apply to irleg stat:
 *  Bit0: Count acl_discarded traffic 
 *   Bit1: Count received IP UC traffic 
 *   Bit2: Count received IP MC traffic 
 *   Bit3: Count ip_uc_routed traffic 
 *   Bit4: Count ip_mc_routed traffic 
 *   Bit5: Count ip_mc_rpf_discarded traffic 
 *  Bit6: Count ip_ttl_discarded traffic
 *
 * \details 
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_IRLEG_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a ANA_AC:STAT_CNT_CFG_IRLEG
 *
 * Individual configuration.
 */


/** 
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_IRLEG:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-63
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_LSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x4800,gi,16,ri,0)

/** 
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_LSB_CNT_LSB_CNT(x)  (x)


/** 
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_IRLEG:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-63
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_MSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x4800,gi,16,ri,8)

/** 
 * \brief
 * The counter's most significant 8 bits.
 * 
 * The field stores the value in the counters of a flow from bit 32 to the
 * most significant bit. 
 * 
 * Reading:
 * The MSB part of the counter is latched to a shadow register, when the
 * LSB part is read. 
 * As a result, the LSB part must always be read first, and the MSB part
 * must be read immediately after the LSB part is read. 
 * 
 * Writing:
 * The procedure for writing differs depending on counter group:
 * ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed by
 * MSB part.
 * All other counter groups: MSB part must be written first, followed by
 * LSB part.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_IRLEG_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ANA_AC:STAT_GLOBAL_CFG_ERLEG
 *
 * Common counter configuration.
 */


/** 
 * \brief Common frame type configuration
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ERLEG:GLOBAL_CNT_FRM_TYPE_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_GLOBAL_CNT_FRM_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x57b7 + (ri))

/** 
 * \brief
 * Configures which frames is counted in relation to FCS error and
 * configured event mask (GLOBAL_EVENT_MASK).
 *
 * \details 
 * 
 * "000": Frames without any event signal or FCS errored frames are
 * counted.
 * "001": Frames with unmasked (enabled) events without FCS error are
 * counted.
 * "010": Frames with unmasked (enabled) events with FCS error are counted.
 * "011": Frames with unmasked (enabled) events independent of FCS error
 * are counted.
 * "100": Frames with FCS error but with no event signal are counted.
 * "101": Frames with FCS error are unconditionally counted.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_GLOBAL_CNT_FRM_TYPE_CFG . GLOBAL_CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ERLEG_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ERLEG_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ERLEG_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Global configuration register
 *
 * \details
 * Global configuration register
 *
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ERLEG:STAT_GLOBAL_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x57bf + (ri))

/** 
 * \brief
 * This field is to configure the counters of all flows to count the byte
 * number or the frame number.
 *
 * \details 
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_CFG . GLOBAL_CFG_CNT_BYTE
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a ANA_AC:STAT_GLOBAL_CFG_ERLEG:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_ANA_AC,0x57c7 + (ri))

/** 
 * \brief
 * This value stores the event mask which indicates the counter of all
 * flows to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 * 
 *  The following events apply to erleg stat:
 *  Bit0: Count acl_discarded traffic 
 *   Bit1: Count ip_uc_routed traffic 
 *   Bit2: Count ip_mc_routed traffic 
 *   Bit3: Count ip_mc_switched traffic 
 *  Bit4: Count ip_mc_ttl_discarded traffic
 *
 * \details 
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ANA_AC_STAT_GLOBAL_CFG_ERLEG_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a ANA_AC:STAT_CNT_CFG_ERLEG
 *
 * Individual configuration.
 */


/** 
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_ERLEG:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-63
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_LSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x4c00,gi,16,ri,0)

/** 
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_LSB_CNT_LSB_CNT(x)  (x)


/** 
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a ANA_AC:STAT_CNT_CFG_ERLEG:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-63
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-7
 */
#define VTSS_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_MSB_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC,0x4c00,gi,16,ri,8)

/** 
 * \brief
 * The counter's most significant 8 bits.
 * 
 * The field stores the value in the counters of a flow from bit 32 to the
 * most significant bit. 
 * 
 * Reading:
 * The MSB part of the counter is latched to a shadow register, when the
 * LSB part is read. 
 * As a result, the LSB part must always be read first, and the MSB part
 * must be read immediately after the LSB part is read. 
 * 
 * Writing:
 * The procedure for writing differs depending on counter group:
 * ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed by
 * MSB part.
 * All other counter groups: MSB part must be written first, followed by
 * LSB part.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_STAT_CNT_CFG_ERLEG_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_SERVALT_REGS_ANA_AC_H_ */
