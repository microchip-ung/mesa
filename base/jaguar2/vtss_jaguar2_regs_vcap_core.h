// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2_REGS_VCAP_CORE_H_
#define _VTSS_JAGUAR2_REGS_VCAP_CORE_H_


#include "vtss_jaguar2_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a VCAP_CORE
 *
 * \see vtss_target_VCAP_CORE_e
 *
 * Vitesse Content Aware Processor
 *
 ***********************************************************************/

/**
 * Register Group: \a VCAP_CORE:VCAP_CORE_CFG
 *
 * VCAP operations
 */


/** 
 * \brief Initiation of read/write/move/initialization operations
 *
 * \details
 * Operations on the VCAP cache is done via this register. The UPDATE_CMD
 * field specifies the operation to perform when UPDATE_SHOT is set. For
 * all of the operations it is possible to disable read/write of entries,
 * actions, and/or counter by setting VCAP_UPDATE_CTRL.UPDATE_ENTRY_DIS,
 * VCAP_UPDATE_CTRL.UPDATE_ACTION_DIS, and/or
 * VCAP_UPDATE_CTRL.UPDATE_CNT_DIS respectively. Writing/moving to
 * unimplemented addresses are ignored. Reading/moving from unimplemented
 * addresses returns never-match for entries, and zeros from
 * actions/counters.
 * Active rules may only be written to empty (initialized) addresses.
 * Software must not overwrite active rules (unless when initializing
 * rules). To initialize a region of addresses use the init operation with
 * CLEAR_CACHE bits set to '1'. Move operations automatically disable rules
 * when moved; so it is OK when source and destination ranges overlap.
 *
 * Register: \a VCAP_CORE:VCAP_CORE_CFG:VCAP_UPDATE_CTRL
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Write and read operations access VCAP memory at address specified by
 * UPDATE_ADDR.
 * Move up opeation moves one or more VCAP addresses from a high address to
 * a lower address, this is equivalent to decreasing priority of a rule.
 * The starting address is specified by UPDATE_ADDR, the number of
 * addresses (the range) that is moved is defined by VCAP_MV_CFG.MV_SIZE,
 * the distance to move is defined by VCAP_MV_CFG. MV_NUM_POS.
 * Move down opeation moves one or more VCAP addresses from a low address
 * to a higer address, this is equivalent to increasing priority of a rule.
 * This operation is equivalent to "Move up" except for the direction that
 * it moves addresses, see "Move up" for more details.
 * Init operation writes the contents of the cache to one or more VCAP
 * addresses. The starting address is specified by UPDATE_ADDR, the number
 * of addresses (the range) that is written is defined by
 * VCAP_MV_CFG.MV_SIZE. Setting CLEAR_CACHE at the same time as starting
 * the operation will clear the cache and cause the init operation to
 * initialize the range of addresses.
 *
 * \details 
 * 000: Write from cache to VCAP
 * 001: Read from VCAP to cache
 * 010: Move entry and/or action up (decreasing addresses)
 * 011: Move entry and/or action down (increasing addresses)
 * 100: Initialize VCAP with the cache-value
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_CMD
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD(x)  VTSS_ENCODE_BITFIELD(x,22,3)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD     VTSS_ENCODE_BITMASK(22,3)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CMD(x)  VTSS_EXTRACT_BITFIELD(x,22,3)

/** 
 * \brief
 * Set to disable update of entries for VCAP operations: For
 * read-operations entry-cache will remain unchanged. For write/move/init
 * operations the VCAP-entry will remain unchanged.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_ENTRY_DIS
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS  VTSS_BIT(21)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Set to disable update of actions for VCAP operations: For
 * read-operations action-cache will remain unchanged. For write/move/init
 * operations the VCAP-action will remain unchanged.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_ACTION_DIS
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS  VTSS_BIT(20)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set to disable update of counter for VCAP operations: For
 * read-operations counter-cache will remain unchanged. For write/init
 * operations the VCAP-counter will remain unchanged. For move operations
 * the destination VCAP-counters will be set to zeros.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_CNT_DIS
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS  VTSS_BIT(19)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * The address to access for VCAP operations.
 *
 * \details 
 * CLM0 defaults at 0x8000-0x8710
 * CLM1 defaults at 0x8720-0x8E30
 * CLM2 defaults at 0x8E40-0x9550
 * IS2 defaults at 0x9560-0x98F0
 * ES0 defaults at 0x1000-0x1034
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_ADDR
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/** 
 * \brief
 * Set to initiate the opeation specified in UPDATE_CMD. This bit is
 * automatically cleared by hardware when the operation is finished.
 * Software must not change write fields in the VCAP target while this
 * field is set (while operation is active.)
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . UPDATE_SHOT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT  VTSS_BIT(2)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_UPDATE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to clear the cache. This field is cleared immediately by hardware
 * (at the same time as clearing the cache). The contents of the cache will
 * be set to disabled/empty.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . CLEAR_CACHE
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_CLEAR_CACHE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_CLEAR_CACHE  VTSS_BIT(1)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_CLEAR_CACHE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * For version 1 VCAPs: Set to ignore interrupting traffic during move
 * operations, this will increase speed of the move operations but
 * counter-events may be lost for the VCAP addresses that are moved. When
 * this field is cleared, then interrupting traffic will cause a restart of
 * the move operation (to ensure consistent counter values) and becasue of
 * this, move operations on a heavily loaded device may take a long time to
 * finish.
 * This field is not used for version 2 VCAPs, moving of counters are safe.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL . MV_TRAFFIC_IGN
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_MV_TRAFFIC_IGN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_MV_TRAFFIC_IGN  VTSS_BIT(0)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_UPDATE_CTRL_MV_TRAFFIC_IGN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration for move/initialization
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CFG:VCAP_MV_CFG
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Specifies the distance during move operations. I.e. if this field is set
 * to 4 for a move-down operation, then source address n is moved to
 * destination address n+5.
 *
 * \details 
 * 0: Distance is one position
 * 1: Distance is two positions
 * n: Distance is n+1 positions
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG . MV_NUM_POS
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_NUM_POS(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Specifies the number of addresses to move/initialize during	move/init
 * operations.
 *
 * \details 
 * 0: Address VCAP_UPDATE_CTRL.UPDATE_ADDR is moved/initialized
 * n: Addresses VCAP_UPDATE_CTRL.UPDATE_ADDR through
 * VCAP_UPDATE_CTRL.UPDATE_ADDR+n are moved/initialized
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG . MV_SIZE
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CFG_VCAP_MV_CFG_MV_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VCAP_CORE:VCAP_CORE_CACHE
 *
 * VCAP cache
 */


/** 
 * \brief Entry data cache
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_ENTRY_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 * @param ri Register: VCAP_ENTRY_DAT (??), 0-63
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT(target,ri)  VTSS_IOREG(target,0x2 + (ri))

/** 
 * \brief
 * The cache register that holds entry data. The register is replicated;
 * index 0 is the 32 LSBs of the entry-data.
 * Together with VCAP_MASK_DAT.MASK_DAT this field defines match parameters
 * for TCAM entries. Version 2 VCAPs allows programming of never-match,
 * this is needed when disabling entries. Version 1 VCAPs converts
 * match-off to match-any when reading/writing entries.
 *
 * \details 
 * Match-0: Entry=0, Mask=0
 * Match-1: Entry=1, Mask=0
 * Match-any (don't care): Entry=0, Mask=1
 * Match-off (never-match): Entry=1, Mask=1
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT . ENTRY_DAT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT_ENTRY_DAT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT_ENTRY_DAT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ENTRY_DAT_ENTRY_DAT(x)  (x)


/** 
 * \brief Entry mask cache
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_MASK_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 * @param ri Register: VCAP_MASK_DAT (??), 0-63
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT(target,ri)  VTSS_IOREG(target,0x42 + (ri))

/** 
 * \brief
 * The cache register that holds entry mask. The register is replicated;
 * index 0 is the 32 LSBs of the entry-mask.
 * See VCAP_MASK_DAT.MASK_DAT for encoding information.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT . MASK_DAT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT_MASK_DAT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT_MASK_DAT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CACHE_VCAP_MASK_DAT_MASK_DAT(x)  (x)


/** 
 * \brief Action cache
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_ACTION_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 * @param ri Register: VCAP_ACTION_DAT (??), 0-63
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT(target,ri)  VTSS_IOREG(target,0x82 + (ri))

/** 
 * \brief
 * The cache register that holds action. The register is replicated; index
 * 0 is the 32 LSBs of the action.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT . ACTION_DAT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT_ACTION_DAT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT_ACTION_DAT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CACHE_VCAP_ACTION_DAT_ACTION_DAT(x)  (x)


/** 
 * \brief Counter cache
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_CNT_DAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 * @param ri Register: VCAP_CNT_DAT (??), 0-31
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT(target,ri)  VTSS_IOREG(target,0xc2 + (ri))

/** 
 * \brief
 * The cache register that holds counter. The register is replicated; index
 * 0 is the 32 LSBs of the counter.
 * When the counter is 1 bit wide the counter operates as a 1 bit
 * saturating counter; it is set by VCAP when a rule is matched by a key.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT . CNT_DAT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT_CNT_DAT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT_CNT_DAT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CACHE_VCAP_CNT_DAT_CNT_DAT(x)  (x)


/** 
 * \brief Cache rule enable
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_CACHE:VCAP_RULE_ENA
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_RULE_ENA(target)  VTSS_IOREG(target,0xe2)

/** 
 * \brief
 * Cache register. Set to enable ES0 rule. Applies only to the ES0 VCAP.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_CACHE_VCAP_RULE_ENA . RULE_ENA
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_CACHE_VCAP_RULE_ENA_RULE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_CACHE_VCAP_RULE_ENA_RULE_ENA  VTSS_BIT(0)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_CACHE_VCAP_RULE_ENA_RULE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VCAP_CORE:VCAP_CORE_MAP
 *
 * Mapping of cores to interfaces
 */


/** 
 * \brief Core index
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_MAP:VCAP_CORE_IDX
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_IDX(target)  VTSS_IOREG(target,0xe3)

/** 
 * \brief
 * Set to index of specific core to access the mapping of that core via
 * VCAP_CORE::VCAP_CORE_MAP.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_IDX . CORE_IDX
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_IDX_CORE_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_IDX_CORE_IDX     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_IDX_CORE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Mapping of core
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_MAP:VCAP_CORE_MAP
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_MAP(target)  VTSS_IOREG(target,0xe4)

/** 
 * \brief
 * Configure ownership of core n (defined by VCAP_CORE::VCAP_CORE_IDX).
 * When a core is mapped to a specific VCAP; lookups for that VCAP will be
 * applied to the core. VCAP priority is still observed, a match in two
 * cores will only cause the most significant rule to be "hit" (highest
 * address.)
 * After reset all cores are in power-save mode.
 *
 * \details 
 * Power-save: 0
 * CLM0: 1
 * CLM1: 2
 * CLM2: 3
 * S2: 4
 * LPM: 5
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_MAP . CORE_MAP
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_MAP_CORE_MAP(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_MAP_CORE_MAP     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_MAP_VCAP_CORE_MAP_CORE_MAP(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a VCAP_CORE:VCAP_CORE_STICKY
 *
 * Sticky bits
 */


/** 
 * \brief Debug information
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CORE_STICKY:VCAP_STICKY
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CORE_STICKY_VCAP_STICKY(target)  VTSS_IOREG(target,0xe5)

/** 
 * \brief
 * A move operation has resulted in deleting of one or more rules.
 * This field applies only to version 1 VCAPs, for version 2 VCAPs it is
 * not implemented and reading it will return zero.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CORE_STICKY_VCAP_STICKY . VCAP_ROW_DELETED_STICKY
 */
#define  VTSS_F_VCAP_CORE_VCAP_CORE_STICKY_VCAP_STICKY_VCAP_ROW_DELETED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_CORE_VCAP_CORE_STICKY_VCAP_STICKY_VCAP_ROW_DELETED_STICKY  VTSS_BIT(0)
#define  VTSS_X_VCAP_CORE_VCAP_CORE_STICKY_VCAP_STICKY_VCAP_ROW_DELETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VCAP_CORE:VCAP_CONST
 *
 * VCAP constants
 */


/** 
 * \brief VCAP version
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:VCAP_VER
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_VCAP_VER(target)  VTSS_IOREG(target,0xe6)

/** 
 * \brief
 * Version of the VCAP control logic.
 *
 * \details 
 * 0: Version 1
 * 1: Version 2
 *
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_VCAP_VER . VCAP_VER
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_VCAP_VER_VCAP_VER(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_VCAP_VER_VCAP_VER     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_VCAP_VER_VCAP_VER(x)  (x)


/** 
 * \brief Entry width
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ENTRY_WIDTH
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH(target)  VTSS_IOREG(target,0xe7)

/** 
 * \brief
 * Width of entry.
 * For version 1 VCAPs this is full word width including bits for the
 * TypeGroup id(s).
 * For version 2 VCAPs this is the width of one entry suboword.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH . ENTRY_WIDTH
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH_ENTRY_WIDTH(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH_ENTRY_WIDTH     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ENTRY_WIDTH_ENTRY_WIDTH(x)  (x)


/** 
 * \brief Number of full-word entries
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ENTRY_CNT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ENTRY_CNT(target)  VTSS_IOREG(target,0xe8)

/** 
 * \brief
 * Number of full-word entries (and actions) per core, see
 * VCAP_CORE::CORE_CNT for number of cores.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ENTRY_CNT . ENTRY_CNT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ENTRY_CNT_ENTRY_CNT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ENTRY_CNT_ENTRY_CNT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ENTRY_CNT_ENTRY_CNT(x)  (x)


/** 
 * \brief Number of subwords per full-word entry
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ENTRY_SWCNT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT(target)  VTSS_IOREG(target,0xe9)

/** 
 * \brief
 * The number of supported subwords per full-word entry.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT . ENTRY_SWCNT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT_ENTRY_SWCNT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT_ENTRY_SWCNT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ENTRY_SWCNT_ENTRY_SWCNT(x)  (x)


/** 
 * \brief Entry type-group width
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ENTRY_TG_WIDTH
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH(target)  VTSS_IOREG(target,0xea)

/** 
 * \brief
 * The width of a single TypeGroup id.
 * For version 2 VCAPs this field return 0, the subword-encoding is
 * configured directly via VCAP_CORE::VCAP_ENTRY_DAT and
 * VCAP_CORE::VCAP_MASK_DAT.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH . ENTRY_TG_WIDTH
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH(x)  (x)


/** 
 * \brief Number of defaults
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ACTION_DEF_CNT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT(target)  VTSS_IOREG(target,0xeb)

/** 
 * \brief
 * The number of default actions. For VCAPs with more than one interface
 * (see VCAP_CORE::IF_CNT); this field returns the total number of defaults
 * for all interfaces.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT . ACTION_DEF_CNT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT_ACTION_DEF_CNT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT_ACTION_DEF_CNT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ACTION_DEF_CNT_ACTION_DEF_CNT(x)  (x)


/** 
 * \brief Action width
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:ACTION_WIDTH
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_ACTION_WIDTH(target)  VTSS_IOREG(target,0xec)

/** 
 * \brief
 * Width of action. For version 1 VCAPs this is full word width. For
 * version 2 VCAPs this is the width of one action suboword.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_ACTION_WIDTH . ACTION_WIDTH
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_ACTION_WIDTH_ACTION_WIDTH(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_ACTION_WIDTH_ACTION_WIDTH     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_ACTION_WIDTH_ACTION_WIDTH(x)  (x)


/** 
 * \brief Counter width
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:CNT_WIDTH
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_CNT_WIDTH(target)  VTSS_IOREG(target,0xed)

/** 
 * \brief
 * The width of the counter memory, this is the complete width of all
 * counter-fields associated with one full-word entry. There is one counter
 * per entry sub-word (see VCAP_CORE::ENTRY_SWCNT for number of subwords.)
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_CNT_WIDTH . CNT_WIDTH
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_CNT_WIDTH_CNT_WIDTH(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_CNT_WIDTH_CNT_WIDTH     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_CNT_WIDTH_CNT_WIDTH(x)  (x)


/** 
 * \brief Number of cores
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:CORE_CNT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_CORE_CNT(target)  VTSS_IOREG(target,0xee)

/** 
 * \brief
 * The number of parallel entry/action cores.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_CORE_CNT . CORE_CNT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_CORE_CNT_CORE_CNT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_CORE_CNT_CORE_CNT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_CORE_CNT_CORE_CNT(x)  (x)


/** 
 * \brief Number of VCAP interfaces
 *
 * \details
 * Register: \a VCAP_CORE:VCAP_CONST:IF_CNT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_VCAP_CONST_IF_CNT(target)  VTSS_IOREG(target,0xef)

/** 
 * \brief
 * The number of VCAP interfaces.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_VCAP_CONST_IF_CNT . IF_CNT
 */
#define  VTSS_F_VCAP_CORE_VCAP_CONST_IF_CNT_IF_CNT(x)  (x)
#define  VTSS_M_VCAP_CORE_VCAP_CONST_IF_CNT_IF_CNT     0xffffffff
#define  VTSS_X_VCAP_CORE_VCAP_CONST_IF_CNT_IF_CNT(x)  (x)

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
#define VTSS_VCAP_CORE_TCAM_BIST_TCAM_CTRL(target)  VTSS_IOREG(target,0xf0)

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
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_CTRL_TCAM_BIST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_CTRL_TCAM_BIST  VTSS_BIT(1)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_CTRL_TCAM_BIST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_CTRL_TCAM_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_CTRL_TCAM_INIT  VTSS_BIT(0)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_CTRL_TCAM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of the TCAM
 *
 * \details
 * Register: \a VCAP_CORE:TCAM_BIST:TCAM_CFG
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_TCAM_BIST_TCAM_CFG(target)  VTSS_IOREG(target,0xf1)

/** 
 * \brief
 * Configures the BIST engine to stop testing if an error is detected. This
 * is a debug feature that leaves the contents of the TCAM at the point of
 * the failure, thusly allowing debug of the failing pattern via normal R/W
 * to the TCAM.
 * Note that because the bist is pipelilned, the contents of the TCAM may
 * have been modified a few times since the actual error.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_CFG . TCAM_BIST_SOE_ENA
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_BIST_SOE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_BIST_SOE_ENA  VTSS_BIT(8)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_BIST_SOE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Disable clock-gating on previous stage hit in the TCAM, clock-gating on
 * previous stage hit is implemented for conserving power when a hit is
 * found in an early pipeline stage.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_CFG . TCAM_HCG_DIS
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_HCG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_HCG_DIS  VTSS_BIT(7)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_HCG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Disable clock-gating in the TCAM, clock-gating is implemented for
 * conserving power while the TCAMs are IDLE.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_CFG . TCAM_CG_DIS
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_CG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_CG_DIS  VTSS_BIT(6)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_CG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Bias setting for the TCAM keeper circuit, configure as described in
 * datasheet.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_CFG . TCAM_BIAS
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_BIAS(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_BIAS     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_CFG_TCAM_BIAS(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Status for the TCAM
 *
 * \details
 * Register: \a VCAP_CORE:TCAM_BIST:TCAM_STAT
 *
 * @param target A \a ::vtss_target_VCAP_CORE_e target
 */
#define VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT(target)  VTSS_IOREG(target,0xf2)

/** 
 * \brief
 * Set if BIST sub-procedure Read-Tree failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_RT_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_RT_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_RT_ERR  VTSS_BIT(15)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_RT_ERR(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set if BIST sub-procedure Priority-Encode failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_PENC_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PENC_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PENC_ERR  VTSS_BIT(14)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PENC_ERR(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set if BIST sub-procedure Compare failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_COMP_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_COMP_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_COMP_ERR  VTSS_BIT(13)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_COMP_ERR(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set if BIST sub-procedure Address Decode failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_ADDR_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_ADDR_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_ADDR_ERR  VTSS_BIT(12)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_ADDR_ERR(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set if BIST sub-procedure Bit-Line-1 (extended) failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_BL1E_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL1E_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL1E_ERR  VTSS_BIT(11)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL1E_ERR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set if BIST sub-procedure Bit-Line-1 failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_BL1_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL1_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL1_ERR  VTSS_BIT(10)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL1_ERR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set if BIST sub-procedure Bit-Line-0 (extended) failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_BL0E_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL0E_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL0E_ERR  VTSS_BIT(9)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL0E_ERR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set if BIST sub-procedure Bit-Line-0 failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_BL0_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL0_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL0_ERR  VTSS_BIT(8)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BL0_ERR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set if BIST sub-procedure Pattern-Horizontal-1 failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_PH1_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PH1_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PH1_ERR  VTSS_BIT(7)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PH1_ERR(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set if BIST sub-procedure Pattern-Horizontal-0 failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_PH0_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PH0_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PH0_ERR  VTSS_BIT(6)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PH0_ERR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set if BIST sub-procedure Pattern-Vertical-1 failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_PV1_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PV1_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PV1_ERR  VTSS_BIT(5)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PV1_ERR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set if BIST sub-procedure Pattern-Vertical-0 failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_PV0_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PV0_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PV0_ERR  VTSS_BIT(4)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_PV0_ERR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set when the BIST has been run. When checking the BIST result this field
 * must be set.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_RUN
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_RUN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_RUN  VTSS_BIT(3)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_RUN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if BIST failed.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_ERR
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_ERR  VTSS_BIT(2)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set while BIST is running. When checking the BIST result this field must
 * be cleared.
 *
 * \details 
 * Field: ::VTSS_VCAP_CORE_TCAM_BIST_TCAM_STAT . BIST_BUSY
 */
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BUSY  VTSS_BIT(1)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_BIST_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_VCAP_CORE_TCAM_BIST_TCAM_STAT_TCAM_RDY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_CORE_TCAM_BIST_TCAM_STAT_TCAM_RDY  VTSS_BIT(0)
#define  VTSS_X_VCAP_CORE_TCAM_BIST_TCAM_STAT_TCAM_RDY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_JAGUAR2_REGS_VCAP_CORE_H_ */
