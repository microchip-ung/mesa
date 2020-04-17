// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LUTON26_REGS_DEVCPU_ORG_H_
#define _VTSS_LUTON26_REGS_DEVCPU_ORG_H_


#include "vtss_luton26_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a DEVCPU_ORG
 *
 * CPU Device Origin
 *
 ***********************************************************************/

/**
 * Register Group: \a DEVCPU_ORG:ORG
 *
 * Origin registers
 */


/** 
 * \brief Target Module ID is Unknown
 *
 * \details
 * Register: \a DEVCPU_ORG:ORG:ERR_ACCESS_DROP
 */
#define VTSS_DEVCPU_ORG_ORG_ERR_ACCESS_DROP  VTSS_IOREG(VTSS_TO_DEVCPU_ORG,0x0)

/** 
 * \brief
 * Sticky bit that - when set - indicates that at least one request was
 * received by a target, but the target did not do anything with it (Eg.
 * access to a non existing register)
 *
 * \details 
 * '0': No errors occurred. 
 * '1': At least one request was received with no action.
 *
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_ACCESS_DROP . NO_ACTION_STICKY
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_ACCESS_DROP_NO_ACTION_STICKY  VTSS_BIT(24)

/** 
 * \brief
 * Target Module ID.
 * When the sticky_no_action bit is set, this field holds the ID of the
 * last target that received a request that didn't resolve in an action.
 *
 * \details 
 * 0x01 : Module id 1 
 * 0xFF : module id 255
 *
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_ACCESS_DROP . TGT_MODULE_NO_ACTION_STICKY
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_ACCESS_DROP_TGT_MODULE_NO_ACTION_STICKY(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DEVCPU_ORG_ORG_ERR_ACCESS_DROP_TGT_MODULE_NO_ACTION_STICKY     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DEVCPU_ORG_ORG_ERR_ACCESS_DROP_TGT_MODULE_NO_ACTION_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Sticky bit that - when set - indicates that at least one request for an
 * unknown target module has been done.
 *
 * \details 
 * '0': No errors occurred. 
 * '1': At least one request to an unknown target has been done.
 *
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_ACCESS_DROP . UTM_STICKY
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_ACCESS_DROP_UTM_STICKY  VTSS_BIT(8)

/** 
 * \brief
 * Target Module ID.
 * When the sticky_utm bit is set, this field holds the ID of the last
 * target that was unknown.
 *
 * \details 
 * 0x01 : Module id 1 
 * 0xFF : module id 255
 *
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_ACCESS_DROP . TGT_MODULE_UTM_STICKY
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_ACCESS_DROP_TGT_MODULE_UTM_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_ORG_ORG_ERR_ACCESS_DROP_TGT_MODULE_UTM_STICKY     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_ORG_ORG_ERR_ACCESS_DROP_TGT_MODULE_UTM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Target Module is Busy
 *
 * \details
 * Write all ones to this register to clear it.
 *
 * Register: \a DEVCPU_ORG:ORG:ERR_TGT
 */
#define VTSS_DEVCPU_ORG_ORG_ERR_TGT          VTSS_IOREG(VTSS_TO_DEVCPU_ORG,0x2)

/** 
 * \brief
 * Sticky bit that - when set - indicates that at least one request was not
 * processed because the target was busy.
 *
 * \details 
 * '0': No error has occurred 
 * '1': A least one request was dropped due to that the target was busy.
 *
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_TGT . BSY_STICKY
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_TGT_BSY_STICKY  VTSS_BIT(8)

/** 
 * \brief
 * Target Module ID.
 * When the sticky_bsy bit is set, this field holds the ID of the last
 * target that was unable to process a request.
 *
 * \details 
 * 0x01 : Module id 1 
 * 0xFF : Module id 255
 *
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_TGT . TGT_MODULE_BSY
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_TGT_TGT_MODULE_BSY(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_ORG_ORG_ERR_TGT_TGT_MODULE_BSY     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_ORG_ORG_ERR_TGT_TGT_MODULE_BSY(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Error Counters
 *
 * \details
 * Register: \a DEVCPU_ORG:ORG:ERR_CNTS
 */
#define VTSS_DEVCPU_ORG_ORG_ERR_CNTS         VTSS_IOREG(VTSS_TO_DEVCPU_ORG,0x3)

/** 
 * \brief
 * No action Counter.
 * Counts the number of requests that were not processed by the Target
 * Module, because the target did not know what to do ( e.g. access to a
 * non-existing register ).
 * This counter saturates at max.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_CNTS . NO_ACTION_CNT
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_CNTS_NO_ACTION_CNT(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DEVCPU_ORG_ORG_ERR_CNTS_NO_ACTION_CNT     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DEVCPU_ORG_ORG_ERR_CNTS_NO_ACTION_CNT(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Unknown Target Counter.
 * Counts the number of requests that were not processed by the Target
 * Module, because the target was no found.
 * This counter saturates at max.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_CNTS . UTM_CNT
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_CNTS_UTM_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DEVCPU_ORG_ORG_ERR_CNTS_UTM_CNT     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DEVCPU_ORG_ORG_ERR_CNTS_UTM_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Busy Counter.
 * Counts the number of requests that were not processed by the Target
 * Module, because it was busy. This may be because the Target Module was
 * waiting for access to/from its host.
 * This counter saturates at max.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ORG_ERR_CNTS . BUSY_CNT
 */
#define  VTSS_F_DEVCPU_ORG_ORG_ERR_CNTS_BUSY_CNT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DEVCPU_ORG_ORG_ERR_CNTS_BUSY_CNT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DEVCPU_ORG_ORG_ERR_CNTS_BUSY_CNT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/** 
 * \brief Configuration and Status Register
 *
 * \details
 * Register: \a DEVCPU_ORG:ORG:CFG_STATUS
 */
#define VTSS_DEVCPU_ORG_ORG_CFG_STATUS       VTSS_IOREG(VTSS_TO_DEVCPU_ORG,0x7)

/** 
 * \brief
 * If a new read access is initialized before the previous read access has
 * completed this sticky bit is set. 
 * Both the 1st and 2nd read access will be handled, but the 2nd access
 * will overwrite data from the 1st access.
 *
 * \details 
 * '0':  A read access that has been initialized before the previous read
 * access had completed has never occurred.
 * '1': At least one time a read access has been initialized before the
 * previous read access had completed.
 *
 * Field: ::VTSS_DEVCPU_ORG_ORG_CFG_STATUS . RD_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_ORG_ORG_CFG_STATUS_RD_ERR_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * When set a access is in progress.
 *
 * \details 
 * '0': No access is in progress. 
 * '1': A access is in progress.
 *
 * Field: ::VTSS_DEVCPU_ORG_ORG_CFG_STATUS . ACCESS_IN_PROGRESS
 */
#define  VTSS_F_DEVCPU_ORG_ORG_CFG_STATUS_ACCESS_IN_PROGRESS  VTSS_BIT(0)


#endif /* _VTSS_LUTON26_REGS_DEVCPU_ORG_H_ */
