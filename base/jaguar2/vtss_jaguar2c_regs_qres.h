#ifndef _VTSS_JAGUAR2C_REGS_QRES_H_
#define _VTSS_JAGUAR2C_REGS_QRES_H_

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

#include "vtss_jaguar2c_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a QRES
 *
 * Queue System Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a QRES:RES_WRED
 *
 * Not documented
 */


/** 
 * \brief Random Early Discard (WRED) configuration
 *
 * \details
 * Configuration of Random Early Discard (RED) profile per RedGroup/QoS
 * class/DP level. The profile index is calulated as Group*24+(DP-1)*8+QOS.
 * There are no profiled for DP=0..
 *
 * Register: \a QRES:RES_WRED:WRED_PROFILE
 *
 * @param gi Register: RES_WRED (??), 0-71
 */
#define VTSS_QRES_RES_WRED_WRED_PROFILE(gi)  VTSS_IOREG_IX(VTSS_TO_QRES,0x5000,gi,1,0,0)

/** 
 * \brief
 * When enqueuing a frame, RED is active if the egress memory consumption
 * for the applicaple profile is above WM_RED_LEVEL. The probability of
 * random early discarding is calculated as: (Memory consumption -
 * WM_RED_LOW)/(WM_RED_HIGH - WM_RED_LOW).
 * Unit is 2816 bytes.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_WRED_WRED_PROFILE . WM_RED_LOW
 */
#define  VTSS_F_QRES_RES_WRED_WRED_PROFILE_WM_RED_LOW(x)  VTSS_ENCODE_BITFIELD(x,11,11)
#define  VTSS_M_QRES_RES_WRED_WRED_PROFILE_WM_RED_LOW     VTSS_ENCODE_BITMASK(11,11)
#define  VTSS_X_QRES_RES_WRED_WRED_PROFILE_WM_RED_LOW(x)  VTSS_EXTRACT_BITFIELD(x,11,11)

/** 
 * \brief
 * See WM_RED_LOW. Unit is 2816 bytes.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_WRED_WRED_PROFILE . WM_RED_HIGH
 */
#define  VTSS_F_QRES_RES_WRED_WRED_PROFILE_WM_RED_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_QRES_RES_WRED_WRED_PROFILE_WM_RED_HIGH     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_QRES_RES_WRED_WRED_PROFILE_WM_RED_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a QRES:RES_QOS_ADV
 *
 * Not documented
 */


/** 
 * \brief Random Early Discard (WRED) configuration
 *
 * \details
 * Configured the WRED group per port.
 *
 * Register: \a QRES:RES_QOS_ADV:WRED_GROUP
 *
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QRES_RES_QOS_ADV_WRED_GROUP(ri)  VTSS_IOREG(VTSS_TO_QRES,0x5048 + (ri))

/** 
 * \brief
 * Frames towards a port is WRED discarded by the profiles for the group
 * configured.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_QOS_ADV_WRED_GROUP . WRED_GROUP
 */
#define  VTSS_F_QRES_RES_QOS_ADV_WRED_GROUP_WRED_GROUP(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QRES_RES_QOS_ADV_WRED_GROUP_WRED_GROUP     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QRES_RES_QOS_ADV_WRED_GROUP_WRED_GROUP(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Shared QOS resource mode
 *
 * \details
 * Register: \a QRES:RES_QOS_ADV:RES_QOS_MODE
 */
#define VTSS_QRES_RES_QOS_ADV_RES_QOS_MODE   VTSS_IOREG(VTSS_TO_QRES,0x5081)

/** 
 * \brief
 * When a qos class is enabled in this mask, the class will have guaranteed
 * shared space. The watermarks found in RES_CFG are used for setting the
 * amount of space set aside.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_QOS_ADV_RES_QOS_MODE . RES_QOS_RSRVD
 */
#define  VTSS_F_QRES_RES_QOS_ADV_RES_QOS_MODE_RES_QOS_RSRVD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QRES_RES_QOS_ADV_RES_QOS_MODE_RES_QOS_RSRVD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QRES_RES_QOS_ADV_RES_QOS_MODE_RES_QOS_RSRVD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Various switch port mode settings
 *
 * \details
 * Register: \a QRES:RES_QOS_ADV:PFC_CFG
 *
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QRES_RES_QOS_ADV_PFC_CFG(ri)    VTSS_IOREG(VTSS_TO_QRES,0x5082 + (ri))

/** 
 * \brief
 * When set the MAC sends PRIO pause control frames in the Tx direction
 * when congested.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_QOS_ADV_PFC_CFG . TX_PFC_ENA
 */
#define  VTSS_F_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * When set, a congested priority request pause of all lower priorities as
 * well.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_QOS_ADV_PFC_CFG . TX_PFC_MODE
 */
#define  VTSS_F_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_MODE  VTSS_BIT(0)
#define  VTSS_X_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DLB shaping offset
 *
 * \details
 * Register: \a QRES:RES_QOS_ADV:RES_DLB_OFFSET
 */
#define VTSS_QRES_RES_QOS_ADV_RES_DLB_OFFSET  VTSS_IOREG(VTSS_TO_QRES,0x50bb)

/** 
 * \brief
 * The watermarks for enabling DLB rate will be offset this value compared
 * to the sensed resource. Ie. if shared priority 0 watermark is set to
 * 40000 cells, the default value will allow higher rate shaping when 39950
 * cells has been used.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_QOS_ADV_RES_DLB_OFFSET . RES_DLB_OFFS_VAL
 */
#define  VTSS_F_QRES_RES_QOS_ADV_RES_DLB_OFFSET_RES_DLB_OFFS_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_QRES_RES_QOS_ADV_RES_DLB_OFFSET_RES_DLB_OFFS_VAL     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_QRES_RES_QOS_ADV_RES_DLB_OFFSET_RES_DLB_OFFS_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a QRES:RES_CTRL
 *
 * Watermarks and status for egress queue system
 */


/** 
 * \brief Watermark configuration
 *
 * \details
 * The queue system tracks four resource consumptions:
 * Resource 0: Memory tracked per source
 * Resource 1: Frame references tracked per source
 * Resource 2: Memory tracked per destination
 * Resource 3: Frame references tracked per destination
 * 
 * Before a frame is added to the queue system, some conditions must be
 * met:
 * - Reserved memory for the specific (SRC, PRIO) or for the specific SRC
 * is available
 * OR
 * - Reserved memory for the specific (DST,PRIO) or for the specific DST is
 * available
 * OR
 * - Shared memory is available
 * 
 * The frame reference resources are checked for availability like the
 * memory resources. Enqueuing of a frame is allowed if both the memory
 * resource check and the frame reference resource check succeed.
 * 
 * The extra resources consumed when enqueuing a frame are first taken from
 * the reserved (SRC,PRIO), next from the reserved SRC, and last from the
 * shared memory area. The same is done for DST. Both memory consumptions
 * and frame reference consumptions are updated.
 * 
 * The register is layed out the following way for source memory (resource
 * 0):
 * Index 0-xxx: Reserved amount for (SRC,PRIO) at index 8*SRC+PRIO
 * Index 496-503: Maximum allowed use of the shared buffer for PRIO at
 * index PRIO+496
 * Index 512-568: Reserved amount for SRC at index SRC+512.
 * Index 510: Maximum allowed use of the shared buffer for frames with
 * DP=1.
 * Index 511: Maximum allowed use of the shared buffer for source.
 * 
 * The layout is similar for resources 1, 2, and 3. Resource 1 uses indices
 * 1024-2047, resource 2 uses indices 2048-3071, and resource 3 uses
 * indices 3072-4095.
 * 
 * The allocation size for memory tracking is 176 bytes. All frames are
 * prepended with a 16-byte header.
 *
 * Register: \a QRES:RES_CTRL:RES_CFG
 *
 * @param gi Register: RES_CTRL (??), 0-5119
 */
#define VTSS_QRES_RES_CTRL_RES_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_QRES,0x0,gi,4,0,0)

/** 
 * \brief
 * Watermark for resource.
 * Note, the default value depends on the index. Refer to the congestion
 * scheme documentation for details.
 *
 * \details 
 * Bit 10:   Unit; 0:1, 1:16
 * Bits 9-0: Value to be multiplied with unit

 *
 * Field: ::VTSS_QRES_RES_CTRL_RES_CFG . WM_HIGH
 */
#define  VTSS_F_QRES_RES_CTRL_RES_CFG_WM_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QRES_RES_CTRL_RES_CFG_WM_HIGH     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QRES_RES_CTRL_RES_CFG_WM_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Resource status
 *
 * \details
 * Register: \a QRES:RES_CTRL:RES_STAT
 *
 * @param gi Register: RES_CTRL (??), 0-5119
 */
#define VTSS_QRES_RES_CTRL_RES_STAT(gi)      VTSS_IOREG_IX(VTSS_TO_QRES,0x0,gi,4,0,1)

/** 
 * \brief
 * Maximum consumption since last read for corresponding watermark in
 * RES_CFG.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_CTRL_RES_STAT . MAXUSE
 */
#define  VTSS_F_QRES_RES_CTRL_RES_STAT_MAXUSE(x)  VTSS_ENCODE_BITFIELD(x,0,21)
#define  VTSS_M_QRES_RES_CTRL_RES_STAT_MAXUSE     VTSS_ENCODE_BITMASK(0,21)
#define  VTSS_X_QRES_RES_CTRL_RES_STAT_MAXUSE(x)  VTSS_EXTRACT_BITFIELD(x,0,21)


/** 
 * \brief Resource status
 *
 * \details
 * Register: \a QRES:RES_CTRL:RES_STAT_CUR
 *
 * @param gi Register: RES_CTRL (??), 0-5119
 */
#define VTSS_QRES_RES_CTRL_RES_STAT_CUR(gi)  VTSS_IOREG_IX(VTSS_TO_QRES,0x0,gi,4,0,2)

/** 
 * \brief
 * Current consumption for corresponding watermark in RES_CFG.
 *
 * \details 
 * Field: ::VTSS_QRES_RES_CTRL_RES_STAT_CUR . INUSE
 */
#define  VTSS_F_QRES_RES_CTRL_RES_STAT_CUR_INUSE(x)  VTSS_ENCODE_BITFIELD(x,0,21)
#define  VTSS_M_QRES_RES_CTRL_RES_STAT_CUR_INUSE     VTSS_ENCODE_BITMASK(0,21)
#define  VTSS_X_QRES_RES_CTRL_RES_STAT_CUR_INUSE(x)  VTSS_EXTRACT_BITFIELD(x,0,21)


#endif /* _VTSS_JAGUAR2C_REGS_QRES_H_ */
