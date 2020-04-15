#ifndef _VTSS_SERVAL_REGS_VCAP_CORE_H_
#define _VTSS_SERVAL_REGS_VCAP_CORE_H_

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

#include "vtss_serval_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a VCAP_CORE
 *
 * \see vtss_target_VCAP_CORE_e
 *
 * VCAP ES0 Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a VCAP_CORE:VCAP_CORE_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CFG:VCAP_UPDATE_CTRL
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Specifies the operation to be carried out when the vcap_update_shot
 * field is set.
 * 
 * The COPY operations will read or write the content of the
 * VCAP_CORE_CACHE to the TCAM/RAMs at the address specified in
 * UPDATE_ADDR. When writing default actions UPDATE_ENTRY_DIS must be set
 * to avoid overwriting entries at the low addresses in the TCAM.
 * 
 * The MOVE operations will move one or more rows up or down starting from
 * the address in UPDATE_ADDR. The number of rows to move is specified in
 * VCAP_MV_CFG.MV_NUM_POS. Moving a row up will decrease its address by
 * MV_NUM_POS, moving a row down will increase its address by MV_NUM_POS.
 * The number of rows to include in the move is specified in
 * VCAP_MV_CFG.MV_SIZE. If a row is moved to an destination address that is
 * less than zero, i.e. if UPDATE_ADDR - MV_NUM_POS < 0, the row will be
 * invalidated in the TCAM and the action and counter RAM will be set to
 * zero.
 * 
 * The INIT operations will set the range of rows specified by UPDATE_ADDR
 * and VCAP_MV_CFG.MV_SIZE to the value  of cache.
 * 
 * Note: init starts from the address specified in UPDATE_ADDR.
 *
 * \details 
 * 000: Copy entry and/or action from  cache to TCAM/RAM
 * 001: Copy entry and/or action from TCAM/RAM to cache
 * 010: Move entry and/or action up (decreasing addresses)
 * 011: Move entry and/or action down (increasing addresses)
 * 100: Initialize all entries and/or actions with the value in the cache. 

 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_CMD
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD(x)  VTSS_ENCODE_BITFIELD(x,22,3)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD     VTSS_ENCODE_BITMASK(22,3)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD(x)  VTSS_EXTRACT_BITFIELD(x,22,3)

/** 
 * \brief
 * Specifies whether the operation specified in vcap_update_cmd is applied
 * to entries.
 *
 * \details 
 * 0: Entries are copied/moved/init.
 * 1: Entries are not copied/moved/init.

 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_ENTRY_DIS
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS  VTSS_BIT(21)

/** 
 * \brief
 * Specifies whether the operation specified in vcap_update_cmd is applied
 * to actions.
 *
 * \details 
 * 0: Actions are copied/moved/init.
 * 1: Actions are not copied/moved/init.

 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_ACTION_DIS
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS  VTSS_BIT(20)

/** 
 * \brief
 * Specifies whether the operation specified in vcap_update_cmd is applied
 * to cnts.
 *
 * \details 
 * 0: Counters are copied/moved/init.
 * 1: Counters are not copied/moved/init.
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_CNT_DIS
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS  VTSS_BIT(19)

/** 
 * \brief
 * The entry/action address (row-wise) used for copy/move operations.

 *
 * \details 
 * When accessing the default actions the offset specified in
 * VCAP_CONST:ENTRY_CNT should be added to the default action addr, i.e. 
 * Default action 0: set UPDATE_ADDR to VCAP_CONST:ENTRY_CNT + 0.
 * Default action 1: set UPDATE_ADDR to VCAP_CONST:ENTRY_CNT + 1.
 * Default action n: set UPDATE_ADDR to VCAP_CONST:ENTRY_CNT + n.
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_ADDR
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/** 
 * \brief
 * Initiate the operation specified in vcap_update_cmd. The bit is cleared
 * by hw when operation has finished.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_SHOT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT  VTSS_BIT(2)

/** 
 * \brief
 * Reset all registers in VCAP_CORE_CACHE. The register is cleared by hw
 * when the operation has finished.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . CLEAR_CACHE
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_CLEAR_CACHE  VTSS_BIT(1)

/** 
 * \brief
 * Ignore interrupting traffic during move operation. If a lookup is
 * performed during a move operation the move is finished from where it was
 * interrupted. When this field is set counters are not guaranteed to be
 * up-to-date after the move.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . MV_TRAFFIC_IGN
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_MV_TRAFFIC_IGN  VTSS_BIT(0)


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CFG:VCAP_MV_CFG
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Specifies the number of positions the row must be moved up or down
 * during a move operation.

 *
 * \details 
 * 0x0 The row is moved one position up or down.
 * 0x1: The row is moved two positions up or down.
 * 0xn: The row is moved n+1 positions up or down.
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG . MV_NUM_POS
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Specifies the number of rows that must be moved up or down during a move
 * operation. 
 * This field is also used to define the range that is initialized using
 * the init feature.
 *
 * \details 
 * 0x0: The row at address UPDATE_ADDR is moved up or down.
 * 0x1: The row at address UPDATE_ADDR through UPDATE_ADDR+1 are moved up
 * or down.
 * 0x2: The row at address UPDATE_ADDR through UPDATE_ADDR+2 are moved up
 * or down. 
 * 0xn: The row at address UPDATE_ADDR through UPDATE_ADDR+n are moved up
 * or down.
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG . MV_SIZE
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VCAP_CORE:VCAP_CORE_CACHE
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_ENTRY_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 * @param ri Register: VCAP_ENTRY_DAT (??), 0-31
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(target,ri)  VTSS_IOREG(target,0x2 + (ri))


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_MASK_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 * @param ri Register: VCAP_MASK_DAT (??), 0-31
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(target,ri)  VTSS_IOREG(target,0x22 + (ri))


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_ACTION_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 * @param ri Register: VCAP_ACTION_DAT (??), 0-31
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(target,ri)  VTSS_IOREG(target,0x42 + (ri))


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_CNT_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 * @param ri Register: VCAP_CNT_DAT (??), 0-31
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(target,ri)  VTSS_IOREG(target,0x62 + (ri))


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_TG_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_TG_DAT(target)  VTSS_IOREG(target,0x82)

/**
 * Register Group: \a VCAP_CORE:VCAP_CORE_STICKY
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_STICKY:VCAP_STICKY
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_STICKY_VCAP_STICKY(target)  VTSS_IOREG(target,0x83)

/** 
 * \brief
 * A move operation has resulted in one or more rows have been deleted.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_STICKY_VCAP_STICKY . VCAP_ROW_DELETED_STICKY
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_STICKY_VCAP_STICKY_VCAP_ROW_DELETED_STICKY  VTSS_BIT(0)

/**
 * Register Group: \a VCAP_CORE:VCAP_CONST
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ENTRY_WIDTH
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH(target)  VTSS_IOREG(target,0x84)

/** 
 * \brief
 * The width of a TCAM entry including TypeGroup ids. 
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH . ENTRY_WIDTH
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH_ENTRY_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH_ENTRY_WIDTH     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH_ENTRY_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ENTRY_CNT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ENTRY_CNT(target)  VTSS_IOREG(target,0x85)

/** 
 * \brief
 * The number of entries in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ENTRY_CNT . ENTRY_CNT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ENTRY_CNT_ENTRY_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ENTRY_CNT_ENTRY_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ENTRY_CNT_ENTRY_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ENTRY_SWCNT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT(target)  VTSS_IOREG(target,0x86)

/** 
 * \brief
 * The number of supported subwords in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT . ENTRY_SWCNT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT_ENTRY_SWCNT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT_ENTRY_SWCNT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT_ENTRY_SWCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ENTRY_TG_WIDTH
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH(target)  VTSS_IOREG(target,0x87)

/** 
 * \brief
 * The width of a single TypeGroup id.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH . ENTRY_TG_WIDTH
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ACTION_DEF_CNT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT(target)  VTSS_IOREG(target,0x88)

/** 
 * \brief
 * The number of default actions.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT . ACTION_DEF_CNT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT_ACTION_DEF_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT_ACTION_DEF_CNT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT_ACTION_DEF_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ACTION_WIDTH
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ACTION_WIDTH(target)  VTSS_IOREG(target,0x89)

/** 
 * \brief
 * The width of the action RAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ACTION_WIDTH . ACTION_WIDTH
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ACTION_WIDTH_ACTION_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ACTION_WIDTH_ACTION_WIDTH     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ACTION_WIDTH_ACTION_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:CNT_WIDTH
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_CNT_WIDTH(target)  VTSS_IOREG(target,0x8a)

/** 
 * \brief
 * The width of the counter RAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_CNT_WIDTH . CNT_WIDTH
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_CNT_WIDTH_CNT_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_CNT_WIDTH_CNT_WIDTH     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VCAP_CORE_VCAP_CONST_CNT_WIDTH_CNT_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a VCAP_CORE:TCAM_BIST
 *
 * Build in test for TCAM
 */


/** 
 * \brief Control of the TCAM
 *
 * \details
 * Register: \a VCAP_CORE:TCAM_BIST:TCAM_CTRL
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_TCAM_BIST_TCAM_CTRL(target)  VTSS_IOREG(target,0x8b)

/** 
 * \brief
 * Set this field to start manual BIST of the TCAM. This field will be
 * cleared once BIST is complete. The BIST procedure requires that the TCAM
 * is initialized before start, setting TCAM_INIT at the same time as
 * setting this field will first initalize the TCAM and then run BIST.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_CTRL . TCAM_BIST
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_CTRL_TCAM_BIST  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to start manual initialization of the TCAM. This field is
 * cleared once initialization is complete.
 * The TCAM has random contents after reset and must be initialized prior
 * to usage.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_CTRL . TCAM_INIT
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_CTRL_TCAM_INIT  VTSS_BIT(0)


/** 
 * \brief Status for the TCAM
 *
 * \details
 * Register: \a VCAP_CORE:TCAM_BIST:TCAM_STAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT(target)  VTSS_IOREG(target,0x8d)

/** 
 * \brief
 * Set if BIST failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_ERR  VTSS_BIT(2)

/** 
 * \brief
 * Set when the BIST is still running. When checking the BIST result this
 * field must be cleared.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_BUSY
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BUSY  VTSS_BIT(1)

/** 
 * \brief
 * Indicates the current operational state of the TCAM.
 *
 * \details 
 * '0': Busy with initialization.
 * '1': Ready to be used.
 *
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . TCAM_RDY
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_TCAM_RDY  VTSS_BIT(0)


#endif /* _VTSS_SERVAL_REGS_VCAP_CORE_H_ */
