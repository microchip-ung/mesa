// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_QRES_H_
#define _VTSS_LAGUNA_REGS_QRES_H_

#include "vtss_laguna_regs_common.h"

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
#define VTSS_QRES_WRED_PROFILE(gi)           VTSS_IOREG_IX(VTSS_TO_QRES,0x5000,gi,1,0,0)

/**
 * \brief
 * When enqueuing a frame, RED is active if the egress memory consumption
 * for the applicaple profile is above WM_RED_LEVEL. The probability of
 * random early discarding is calculated as: (Memory consumption -
 * WM_RED_LOW)/(WM_RED_HIGH - WM_RED_LOW).Unit is 2944 bytes.
 *
 * \details
 * Field: ::VTSS_QRES_WRED_PROFILE . WM_RED_LOW
 */
#define  VTSS_F_QRES_WRED_PROFILE_WM_RED_LOW(x)  VTSS_ENCODE_BITFIELD(x,11,6)
#define  VTSS_M_QRES_WRED_PROFILE_WM_RED_LOW     VTSS_ENCODE_BITMASK(11,6)
#define  VTSS_X_QRES_WRED_PROFILE_WM_RED_LOW(x)  VTSS_EXTRACT_BITFIELD(x,11,6)

/**
 * \brief
 * See WM_RED_LOW. Unit is 2944 bytes.
 *
 * \details
 * Field: ::VTSS_QRES_WRED_PROFILE . WM_RED_HIGH
 */
#define  VTSS_F_QRES_WRED_PROFILE_WM_RED_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_QRES_WRED_PROFILE_WM_RED_HIGH     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_QRES_WRED_PROFILE_WM_RED_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

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
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_QRES_WRED_GROUP(ri)             VTSS_IOREG(VTSS_TO_QRES,0x5048 + (ri))

/**
 * \brief
 * Frames towards a port is WRED discarded by the profiles for the group
 * configured.
 *
 * \details
 * Field: ::VTSS_QRES_WRED_GROUP . WRED_GROUP
 */
#define  VTSS_F_QRES_WRED_GROUP_WRED_GROUP(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QRES_WRED_GROUP_WRED_GROUP     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QRES_WRED_GROUP_WRED_GROUP(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Shared QOS resource mode
 *
 * \details
 * Register: \a QRES:RES_QOS_ADV:RES_QOS_MODE
 */
#define VTSS_QRES_RES_QOS_MODE               VTSS_IOREG(VTSS_TO_QRES,0x508e)

/**
 * \brief
 * When a QoS class is enabled in this mask, the class will have guaranteed
 * shared space. The watermarks found in RES_CFG are used for setting the
 * amount of space set aside.
 *
 * \details
 * Field: ::VTSS_QRES_RES_QOS_MODE . RES_QOS_RSRVD
 */
#define  VTSS_F_QRES_RES_QOS_MODE_RES_QOS_RSRVD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QRES_RES_QOS_MODE_RES_QOS_RSRVD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QRES_RES_QOS_MODE_RES_QOS_RSRVD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief DLB shaping offset
 *
 * \details
 * Register: \a QRES:RES_QOS_ADV:RES_DLB_OFFSET
 */
#define VTSS_QRES_RES_DLB_OFFSET             VTSS_IOREG(VTSS_TO_QRES,0x508f)

/**
 * \brief
 * The watermarks for enabling DLB rate will be offset this value compared
 * to the sensed resource. Ie. if shared priority 0 watermark is set to
 * 40000 cells, the default value will allow higher rate shaping when 39950
 * cells has been used.
 *
 * \details
 * Field: ::VTSS_QRES_RES_DLB_OFFSET . RES_DLB_OFFS_VAL
 */
#define  VTSS_F_QRES_RES_DLB_OFFSET_RES_DLB_OFFS_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_QRES_RES_DLB_OFFSET_RES_DLB_OFFS_VAL     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_QRES_RES_DLB_OFFSET_RES_DLB_OFFS_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

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
 * Index 0-  : Reserved amount for (PORT,PRIO) at index 8*PORT+PRIO
 * Index 280 - : Maximum allowed use of the shared buffer for ports,
 * starting with port 0.
 * Index 315 - : Maximum allowed use of the shared buffer for priorities,
 * starting with prio 0.
 * Index 323 - : Maximum allowed use of the shared buffer for colors,
 * starting with dp level 0.
 *
 * The layout is similar for resources 1, 2, and 3. Resource 1 uses indices
 * 1024-2047, resource 2 uses indices 2048-3071, and resource 3 uses
 * indices 3072-4095.
 *
 * The allocation size for memory tracking is 184 bytes. All frames are
 * prepended with an IFH.
 *
 * Register: \a QRES:RES_CTRL:RES_CFG
 *
 * @param gi Register: RES_CTRL (??), 0-5119
 */
#define VTSS_QRES_RES_CFG(gi)                VTSS_IOREG_IX(VTSS_TO_QRES,0x0,gi,4,0,0)

/**
 * \brief
 * Watermark for resource.Note, the default value depends on the index.
 * Refer to the congestion scheme documentation for details.
 *
 * \details
 * Bit 10:   Unit; 0:1, 1:16
 * Bits 9-0: Value to be multiplied with unit

 *
 * Field: ::VTSS_QRES_RES_CFG . WM_HIGH
 */
#define  VTSS_F_QRES_RES_CFG_WM_HIGH(x)       VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_QRES_RES_CFG_WM_HIGH          VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_QRES_RES_CFG_WM_HIGH(x)       VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Resource status
 *
 * \details
 * Register: \a QRES:RES_CTRL:RES_STAT
 *
 * @param gi Register: RES_CTRL (??), 0-5119
 */
#define VTSS_QRES_RES_STAT(gi)               VTSS_IOREG_IX(VTSS_TO_QRES,0x0,gi,4,0,1)

/**
 * \brief
 * Maximum consumption since last read for corresponding watermark in
 * RES_CFG.
 *
 * \details
 * Field: ::VTSS_QRES_RES_STAT . MAXUSE
 */
#define  VTSS_F_QRES_RES_STAT_MAXUSE(x)       VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_QRES_RES_STAT_MAXUSE          VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_QRES_RES_STAT_MAXUSE(x)       VTSS_EXTRACT_BITFIELD(x,0,15)


/**
 * \brief Resource status
 *
 * \details
 * Register: \a QRES:RES_CTRL:RES_STAT_CUR
 *
 * @param gi Register: RES_CTRL (??), 0-5119
 */
#define VTSS_QRES_RES_STAT_CUR(gi)           VTSS_IOREG_IX(VTSS_TO_QRES,0x0,gi,4,0,2)

/**
 * \brief
 * Current consumption for corresponding watermark in RES_CFG.
 *
 * \details
 * Field: ::VTSS_QRES_RES_STAT_CUR . INUSE
 */
#define  VTSS_F_QRES_RES_STAT_CUR_INUSE(x)    VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_QRES_RES_STAT_CUR_INUSE       VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_QRES_RES_STAT_CUR_INUSE(x)    VTSS_EXTRACT_BITFIELD(x,0,15)


#endif /* _VTSS_LAGUNA_REGS_QRES_H_ */
