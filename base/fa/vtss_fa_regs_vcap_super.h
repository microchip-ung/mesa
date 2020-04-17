// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_VCAP_SUPER_H_
#define _VTSS_FA_REGS_VCAP_SUPER_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a VCAP_SUPER
 *
 * Versatile Content Aware Processor
 *
 ***********************************************************************/

/**
 * Register Group: \a VCAP_SUPER:VCAP_CORE_CFG
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
 * Register: \a VCAP_SUPER:VCAP_CORE_CFG:VCAP_UPDATE_CTRL
 */
#define VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL     VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x0)

/** 
 * \brief
 * Write and read operations access VCAP memory at address specified by
 * UPDATE_ADDR.Move up operation moves one or more VCAP addresses from a
 * high address to a lower address, this is equivalent to decreasing
 * priority of a rule. The starting address is specified by UPDATE_ADDR,
 * the number of addresses (the range) that is moved is defined by
 * VCAP_MV_CFG.MV_SIZE, the distance to move is defined by VCAP_MV_CFG.
 * MV_NUM_POS.Move down operation moves one or more VCAP addresses from a
 * low address to a higher address, this is equivalent to increasing
 * priority of a rule. This operation is equivalent to "Move up" except for
 * the direction that it moves addresses, see "Move up" for more
 * details.Init operation writes the contents of the cache to one or more
 * VCAP addresses. The starting address is specified by UPDATE_ADDR, the
 * number of addresses (the range) that is written is defined by
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
 * 101: Read and clear counter values of a full-word from the VCAP to the
 * chache. Not supported for default actions
 *
 * Field: ::VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL . UPDATE_CMD
 */
#define  VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_CMD(x)  VTSS_ENCODE_BITFIELD(x,22,3)
#define  VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_CMD     VTSS_ENCODE_BITMASK(22,3)
#define  VTSS_X_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_CMD(x)  VTSS_EXTRACT_BITFIELD(x,22,3)

/** 
 * \brief
 * Set to disable update of entries for VCAP operations: For
 * read-operations entry-cache will remain unchanged. For write/move/init
 * operations the VCAP-entry will remain unchanged.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL . UPDATE_ENTRY_DIS
 */
#define  VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS  VTSS_BIT(21)
#define  VTSS_X_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ENTRY_DIS(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Set to disable update of actions for VCAP operations: For
 * read-operations action-cache will remain unchanged. For write/move/init
 * operations the VCAP-action will remain unchanged.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL . UPDATE_ACTION_DIS
 */
#define  VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS  VTSS_BIT(20)
#define  VTSS_X_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ACTION_DIS(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set to disable update of counter for VCAP operations: For
 * read-operations counter-cache will remain unchanged. For write/init
 * operations the VCAP-counter will remain unchanged. For move operations
 * the destination VCAP-counters will be set to zeros.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL . UPDATE_CNT_DIS
 */
#define  VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS  VTSS_BIT(19)
#define  VTSS_X_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_CNT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * The address to access for VCAP operations.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL . UPDATE_ADDR
 */
#define  VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ADDR(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ADDR     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/** 
 * \brief
 * Set to initiate the operation specified in UPDATE_CMD. This bit is
 * automatically cleared by hardware when the operation is
 * finished.Software must not change write fields in the VCAP target while
 * this field is set (while operation is active.)
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL . UPDATE_SHOT
 */
#define  VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_SHOT  VTSS_BIT(2)
#define  VTSS_X_VCAP_SUPER_VCAP_UPDATE_CTRL_UPDATE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to clear the cache. This field is cleared immediately by hardware
 * (at the same time as clearing the cache). The contents of the cache will
 * be set to disabled/empty.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL . CLEAR_CACHE
 */
#define  VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_CLEAR_CACHE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_CLEAR_CACHE  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_VCAP_UPDATE_CTRL_CLEAR_CACHE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * For version 1 VCAPs: Set to ignore interrupting traffic during move
 * operations, this will increase speed of the move operations but
 * counter-events may be lost for the VCAP addresses that are moved. When
 * this field is cleared, then interrupting traffic will cause a restart of
 * the move operation (to ensure consistent counter values) and becasue of
 * this, move operations on a heavily loaded device may take a long time to
 * finish.This field is not used for version 2 VCAPs, moving of counters
 * are safe.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL . MV_TRAFFIC_IGN
 */
#define  VTSS_F_VCAP_SUPER_VCAP_UPDATE_CTRL_MV_TRAFFIC_IGN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_VCAP_UPDATE_CTRL_MV_TRAFFIC_IGN  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_VCAP_UPDATE_CTRL_MV_TRAFFIC_IGN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration for move/initialization
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_CFG:VCAP_MV_CFG
 */
#define VTSS_VCAP_SUPER_VCAP_MV_CFG          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x1)

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
 * Field: ::VTSS_VCAP_SUPER_VCAP_MV_CFG . MV_NUM_POS
 */
#define  VTSS_F_VCAP_SUPER_VCAP_MV_CFG_MV_NUM_POS(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VCAP_SUPER_VCAP_MV_CFG_MV_NUM_POS     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VCAP_SUPER_VCAP_MV_CFG_MV_NUM_POS(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Specifies the number of addresses to move/initialize during	move/init
 * operations.
 *
 * \details 
 * 0: Address VCAP_UPDATE_CTRL.UPDATE_ADDR is moved/initialized
 * n: Addresses VCAP_UPDATE_CTRL.UPDATE_ADDR through
 * VCAP_UPDATE_CTRL.UPDATE_ADDR+n+1 are moved/initialized
 *
 * Field: ::VTSS_VCAP_SUPER_VCAP_MV_CFG . MV_SIZE
 */
#define  VTSS_F_VCAP_SUPER_VCAP_MV_CFG_MV_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VCAP_SUPER_VCAP_MV_CFG_MV_SIZE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VCAP_SUPER_VCAP_MV_CFG_MV_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VCAP_SUPER:VCAP_CORE_CACHE
 *
 * VCAP cache
 */


/** 
 * \brief Entry data cache
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_CACHE:VCAP_ENTRY_DAT
 *
 * @param ri Register: VCAP_ENTRY_DAT (??), 0-63
 */
#define VTSS_VCAP_SUPER_VCAP_ENTRY_DAT(ri)   VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x2 + (ri))

/** 
 * \brief
 * The cache register that holds entry data. The register is replicated;
 * index 0 is the 32 LSBs of the entry-data.Together with
 * VCAP_MASK_DAT.MASK_DAT this field defines match parameters for TCAM
 * entries. Version 2 VCAPs allows programming of never-match, this is
 * needed when disabling entries. Version 1 VCAPs converts match-off to
 * match-any when reading/writing entries.
 *
 * \details 
 * Match-0: Entry=0, Mask=0
 * Match-1: Entry=1, Mask=0
 * Match-any (don't care): Entry=0, Mask=1
 * Match-off (never-match): Entry=1, Mask=1
 *
 * Field: ::VTSS_VCAP_SUPER_VCAP_ENTRY_DAT . ENTRY_DAT
 */
#define  VTSS_F_VCAP_SUPER_VCAP_ENTRY_DAT_ENTRY_DAT(x)  (x)
#define  VTSS_M_VCAP_SUPER_VCAP_ENTRY_DAT_ENTRY_DAT     0xffffffff
#define  VTSS_X_VCAP_SUPER_VCAP_ENTRY_DAT_ENTRY_DAT(x)  (x)


/** 
 * \brief Entry mask cache
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_CACHE:VCAP_MASK_DAT
 *
 * @param ri Register: VCAP_MASK_DAT (??), 0-63
 */
#define VTSS_VCAP_SUPER_VCAP_MASK_DAT(ri)    VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x42 + (ri))

/** 
 * \brief
 * The cache register that holds entry mask. The register is replicated;
 * index 0 is the 32 LSBs of the entry-mask.See VCAP_ENTRY_DAT.ENTRY_DAT
 * for encoding information.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_MASK_DAT . MASK_DAT
 */
#define  VTSS_F_VCAP_SUPER_VCAP_MASK_DAT_MASK_DAT(x)  (x)
#define  VTSS_M_VCAP_SUPER_VCAP_MASK_DAT_MASK_DAT     0xffffffff
#define  VTSS_X_VCAP_SUPER_VCAP_MASK_DAT_MASK_DAT(x)  (x)


/** 
 * \brief Action cache
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_CACHE:VCAP_ACTION_DAT
 *
 * @param ri Register: VCAP_ACTION_DAT (??), 0-63
 */
#define VTSS_VCAP_SUPER_VCAP_ACTION_DAT(ri)  VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x82 + (ri))

/** 
 * \brief
 * The cache register that holds action. The register is replicated; index
 * 0 is the 32 LSBs of the action.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_ACTION_DAT . ACTION_DAT
 */
#define  VTSS_F_VCAP_SUPER_VCAP_ACTION_DAT_ACTION_DAT(x)  (x)
#define  VTSS_M_VCAP_SUPER_VCAP_ACTION_DAT_ACTION_DAT     0xffffffff
#define  VTSS_X_VCAP_SUPER_VCAP_ACTION_DAT_ACTION_DAT(x)  (x)


/** 
 * \brief Counter cache
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_CACHE:VCAP_CNT_DAT
 *
 * @param ri Register: VCAP_CNT_DAT (??), 0-31
 */
#define VTSS_VCAP_SUPER_VCAP_CNT_DAT(ri)     VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xc2 + (ri))

/** 
 * \brief
 * The cache register that holds counter. The register is replicated; index
 * 0 is the 32 LSBs of the counter.When the counter is 1 bit wide the
 * counter operates as a 1 bit saturating counter; it is set by VCAP when a
 * rule is matched by a key.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_CNT_DAT . CNT_DAT
 */
#define  VTSS_F_VCAP_SUPER_VCAP_CNT_DAT_CNT_DAT(x)  (x)
#define  VTSS_M_VCAP_SUPER_VCAP_CNT_DAT_CNT_DAT     0xffffffff
#define  VTSS_X_VCAP_SUPER_VCAP_CNT_DAT_CNT_DAT(x)  (x)


/** 
 * \brief Counter full-word cache
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_CACHE:VCAP_CNT_FW_DAT
 */
#define VTSS_VCAP_SUPER_VCAP_CNT_FW_DAT      VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xe2)

/** 
 * \brief
 * The cache register that holds full-word counter values after completing
 * the update command that reads and clears counter values of a full-word
 * in the VCAP.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_CNT_FW_DAT . CNT_FW_DAT
 */
#define  VTSS_F_VCAP_SUPER_VCAP_CNT_FW_DAT_CNT_FW_DAT(x)  (x)
#define  VTSS_M_VCAP_SUPER_VCAP_CNT_FW_DAT_CNT_FW_DAT     0xffffffff
#define  VTSS_X_VCAP_SUPER_VCAP_CNT_FW_DAT_CNT_FW_DAT(x)  (x)


/** 
 * \brief Entry type-group
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_CACHE:VCAP_TG_DAT
 */
#define VTSS_VCAP_SUPER_VCAP_TG_DAT          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xe3)

/** 
 * \brief
 * This cache register holds the TypeGroup id for each subword in the TCAM.
 * TypeGroup ids are place back to back with subword 0 at the LSBs when
 * VCAP supports multiple subwords.This field applies only to version 1
 * VCAPs, for version 2 VCAPs it is not implemented and reading it will
 * return zeros.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_TG_DAT . TG_DAT
 */
#define  VTSS_F_VCAP_SUPER_VCAP_TG_DAT_TG_DAT(x)  (x)
#define  VTSS_M_VCAP_SUPER_VCAP_TG_DAT_TG_DAT     0xffffffff
#define  VTSS_X_VCAP_SUPER_VCAP_TG_DAT_TG_DAT(x)  (x)

/**
 * Register Group: \a VCAP_SUPER:VCAP_CORE_MAP
 *
 * Mapping of cores to interfaces
 */


/** 
 * \brief Core index
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_MAP:VCAP_CORE_IDX
 */
#define VTSS_VCAP_SUPER_VCAP_CORE_IDX        VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xe4)

/** 
 * \brief
 * Set to index of specific core to access the mapping of that core via
 * VCAP_SUPER:VCAP_CORE_MAP.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_CORE_IDX . CORE_IDX
 */
#define  VTSS_F_VCAP_SUPER_VCAP_CORE_IDX_CORE_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VCAP_SUPER_VCAP_CORE_IDX_CORE_IDX     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VCAP_SUPER_VCAP_CORE_IDX_CORE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Mapping of core
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_MAP:VCAP_CORE_MAP
 */
#define VTSS_VCAP_SUPER_VCAP_CORE_MAP        VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xe5)

/** 
 * \brief
 * Configure ownership of core n (defined by
 * VCAP_SUPER:VCAP_CORE_MAP:VCAP_CORE_IDX).When a core is mapped to a
 * specific VCAP; lookups for that VCAP will be applied to the core. If
 * multiple cores are mapped to the same VCAP, they must cover a
 * consecutive range of cores. VCAP priority is still observed, a match in
 * two cores will only cause the most significant rule to be "hit" (highest
 * address.)After reset all cores are in power-save mode.
 *
 * \details 
 * VCAP_SUPER:
 *   0: Power-save mode - core disabled
 *   1: Core mapped to CLM0
 *   2: Core mapped to CLM1
 *   3: Core mapped to CLM2
 *   4: Core mapped to S2 (first and second lookup)
 *   5: Core mapped to S2 (third and fourth lookup)
 *   6: Core mapped to LPM
 * 
 * VCAP_IP6PFX, VCAP_ES2, VCAP_ES0:
 *   0: Power-save mode - core disabled
 *   1: Core enabled
 *
 * Field: ::VTSS_VCAP_SUPER_VCAP_CORE_MAP . CORE_MAP
 */
#define  VTSS_F_VCAP_SUPER_VCAP_CORE_MAP_CORE_MAP(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VCAP_SUPER_VCAP_CORE_MAP_CORE_MAP     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VCAP_SUPER_VCAP_CORE_MAP_CORE_MAP(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a VCAP_SUPER:VCAP_CORE_STICKY
 *
 * Sticky bits
 */


/** 
 * \brief Debug information
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CORE_STICKY:VCAP_STICKY
 */
#define VTSS_VCAP_SUPER_VCAP_STICKY          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xe6)

/** 
 * \brief
 * A move operation has resulted in deleting of one or more rules.This
 * field applies only to version 1 VCAPs, for version 2 VCAPs it is not
 * implemented and reading it will return zero.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_VCAP_STICKY . VCAP_ROW_DELETED_STICKY
 */
#define  VTSS_F_VCAP_SUPER_VCAP_STICKY_VCAP_ROW_DELETED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_VCAP_STICKY_VCAP_ROW_DELETED_STICKY  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_VCAP_STICKY_VCAP_ROW_DELETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VCAP_SUPER:VCAP_CONST
 *
 * VCAP constants
 */


/** 
 * \brief VCAP version
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:VCAP_VER
 */
#define VTSS_VCAP_SUPER_VCAP_VER             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xe7)

/** 
 * \brief
 * Version of the VCAP control logic.
 *
 * \details 
 * 0: Version 1
 * 1: Version 2
 *
 * Field: ::VTSS_VCAP_SUPER_VCAP_VER . VCAP_VER
 */
#define  VTSS_F_VCAP_SUPER_VCAP_VER_VCAP_VER(x)  (x)
#define  VTSS_M_VCAP_SUPER_VCAP_VER_VCAP_VER     0xffffffff
#define  VTSS_X_VCAP_SUPER_VCAP_VER_VCAP_VER(x)  (x)


/** 
 * \brief Entry width
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:ENTRY_WIDTH
 */
#define VTSS_VCAP_SUPER_ENTRY_WIDTH          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xe8)

/** 
 * \brief
 * Width of entry.For version 1 VCAPs this is full word width including
 * bits for the TypeGroup id(s).For version 2 VCAPs this is the width of
 * one entry suboword.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ENTRY_WIDTH . ENTRY_WIDTH
 */
#define  VTSS_F_VCAP_SUPER_ENTRY_WIDTH_ENTRY_WIDTH(x)  (x)
#define  VTSS_M_VCAP_SUPER_ENTRY_WIDTH_ENTRY_WIDTH     0xffffffff
#define  VTSS_X_VCAP_SUPER_ENTRY_WIDTH_ENTRY_WIDTH(x)  (x)


/** 
 * \brief Number of full-word entries
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:ENTRY_CNT
 */
#define VTSS_VCAP_SUPER_ENTRY_CNT            VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xe9)

/** 
 * \brief
 * Number of full-word entries (and actions) per core, see
 * VCAP_SUPER:VCAP_CONST:CORE_CNT for number of cores.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ENTRY_CNT . ENTRY_CNT
 */
#define  VTSS_F_VCAP_SUPER_ENTRY_CNT_ENTRY_CNT(x)  (x)
#define  VTSS_M_VCAP_SUPER_ENTRY_CNT_ENTRY_CNT     0xffffffff
#define  VTSS_X_VCAP_SUPER_ENTRY_CNT_ENTRY_CNT(x)  (x)


/** 
 * \brief Number of subwords per full-word entry
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:ENTRY_SWCNT
 */
#define VTSS_VCAP_SUPER_ENTRY_SWCNT          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xea)

/** 
 * \brief
 * The number of supported subwords per full-word entry.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ENTRY_SWCNT . ENTRY_SWCNT
 */
#define  VTSS_F_VCAP_SUPER_ENTRY_SWCNT_ENTRY_SWCNT(x)  (x)
#define  VTSS_M_VCAP_SUPER_ENTRY_SWCNT_ENTRY_SWCNT     0xffffffff
#define  VTSS_X_VCAP_SUPER_ENTRY_SWCNT_ENTRY_SWCNT(x)  (x)


/** 
 * \brief Entry type-group width
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:ENTRY_TG_WIDTH
 */
#define VTSS_VCAP_SUPER_ENTRY_TG_WIDTH       VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xeb)

/** 
 * \brief
 * The width of a single TypeGroup id.For version 2 VCAPs this field return
 * 0, the subword-encoding is configured directly via
 * VCAP_SUPER:VCAP_CORE_CACHE:VCAP_ENTRY_DAT and
 * VCAP_SUPER:VCAP_CORE_CACHE:VCAP_MASK_DAT.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ENTRY_TG_WIDTH . ENTRY_TG_WIDTH
 */
#define  VTSS_F_VCAP_SUPER_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH(x)  (x)
#define  VTSS_M_VCAP_SUPER_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH     0xffffffff
#define  VTSS_X_VCAP_SUPER_ENTRY_TG_WIDTH_ENTRY_TG_WIDTH(x)  (x)


/** 
 * \brief Number of defaults
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:ACTION_DEF_CNT
 */
#define VTSS_VCAP_SUPER_ACTION_DEF_CNT       VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xec)

/** 
 * \brief
 * The number of default actions. For VCAPs with more than one interface
 * (see VCAP_SUPER:VCAP_CONST:IF_CNT); this field returns the total number
 * of defaults for all interfaces.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ACTION_DEF_CNT . ACTION_DEF_CNT
 */
#define  VTSS_F_VCAP_SUPER_ACTION_DEF_CNT_ACTION_DEF_CNT(x)  (x)
#define  VTSS_M_VCAP_SUPER_ACTION_DEF_CNT_ACTION_DEF_CNT     0xffffffff
#define  VTSS_X_VCAP_SUPER_ACTION_DEF_CNT_ACTION_DEF_CNT(x)  (x)


/** 
 * \brief Action width
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:ACTION_WIDTH
 */
#define VTSS_VCAP_SUPER_ACTION_WIDTH         VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xed)

/** 
 * \brief
 * Width of action. For version 1 VCAPs this is full word width. For
 * version 2 VCAPs this is the width of one action suboword.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ACTION_WIDTH . ACTION_WIDTH
 */
#define  VTSS_F_VCAP_SUPER_ACTION_WIDTH_ACTION_WIDTH(x)  (x)
#define  VTSS_M_VCAP_SUPER_ACTION_WIDTH_ACTION_WIDTH     0xffffffff
#define  VTSS_X_VCAP_SUPER_ACTION_WIDTH_ACTION_WIDTH(x)  (x)


/** 
 * \brief Counter width
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:CNT_WIDTH
 */
#define VTSS_VCAP_SUPER_CNT_WIDTH            VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xee)

/** 
 * \brief
 * The width of the counter memory, this is the complete width of all
 * counter-fields associated with one full-word entry. There is one counter
 * per entry sub-word (see VCAP_SUPER:VCAP_CONST:ENTRY_SWCNT for number of
 * subwords.)
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_CNT_WIDTH . CNT_WIDTH
 */
#define  VTSS_F_VCAP_SUPER_CNT_WIDTH_CNT_WIDTH(x)  (x)
#define  VTSS_M_VCAP_SUPER_CNT_WIDTH_CNT_WIDTH     0xffffffff
#define  VTSS_X_VCAP_SUPER_CNT_WIDTH_CNT_WIDTH(x)  (x)


/** 
 * \brief Number of cores
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:CORE_CNT
 */
#define VTSS_VCAP_SUPER_CORE_CNT             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xef)

/** 
 * \brief
 * The number of parallel entry/action cores.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_CORE_CNT . CORE_CNT
 */
#define  VTSS_F_VCAP_SUPER_CORE_CNT_CORE_CNT(x)  (x)
#define  VTSS_M_VCAP_SUPER_CORE_CNT_CORE_CNT     0xffffffff
#define  VTSS_X_VCAP_SUPER_CORE_CNT_CORE_CNT(x)  (x)


/** 
 * \brief Number of VCAP interfaces
 *
 * \details
 * Register: \a VCAP_SUPER:VCAP_CONST:IF_CNT
 */
#define VTSS_VCAP_SUPER_IF_CNT               VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xf0)

/** 
 * \brief
 * The number of VCAP interfaces.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_IF_CNT . IF_CNT
 */
#define  VTSS_F_VCAP_SUPER_IF_CNT_IF_CNT(x)   (x)
#define  VTSS_M_VCAP_SUPER_IF_CNT_IF_CNT      0xffffffff
#define  VTSS_X_VCAP_SUPER_IF_CNT_IF_CNT(x)   (x)

/**
 * Register Group: \a VCAP_SUPER:TCAM_BIST
 *
 * Built-in self-test for TCAM
 */


/** 
 * \brief Configuration of the TCAM
 *
 * \details
 * Register: \a VCAP_SUPER:TCAM_BIST:TCAM_CFG
 */
#define VTSS_VCAP_SUPER_TCAM_CFG             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xf1)

/** 
 * \brief
 * Disable clock-gating on previous stage hit in the TCAM, clock-gating on
 * previous stage hit is implemented for conserving power when a hit is
 * found in an early pipeline stage.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_TCAM_CFG . TCAM_HCG_DIS
 */
#define  VTSS_F_VCAP_SUPER_TCAM_CFG_TCAM_HCG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VCAP_SUPER_TCAM_CFG_TCAM_HCG_DIS  VTSS_BIT(3)
#define  VTSS_X_VCAP_SUPER_TCAM_CFG_TCAM_HCG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Disable clock-gating in the TCAM, clock-gating is implemented for
 * conserving power while the TCAMs are IDLE.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_TCAM_CFG . TCAM_CG_DIS
 */
#define  VTSS_F_VCAP_SUPER_TCAM_CFG_TCAM_CG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_SUPER_TCAM_CFG_TCAM_CG_DIS  VTSS_BIT(2)
#define  VTSS_X_VCAP_SUPER_TCAM_CFG_TCAM_CG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Self-timing compare margin for the TCAM compare circuit."00": Faster
 * than recommended performance timing."01": Recommended performance
 * timing."10": Level 1 relaxed timing for lower frequency design."11":
 * Level 2 relaxed timing (slower than level 1).
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_TCAM_CFG . TCAM_STCMP
 */
#define  VTSS_F_VCAP_SUPER_TCAM_CFG_TCAM_STCMP(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VCAP_SUPER_TCAM_CFG_TCAM_STCMP     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VCAP_SUPER_TCAM_CFG_TCAM_STCMP(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Control of TCAM shutdown and reset
 *
 * \details
 * Register: \a VCAP_SUPER:TCAM_BIST:TCAM_CTRL
 */
#define VTSS_VCAP_SUPER_TCAM_CTRL            VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xf2)

/** 
 * \brief
 * This field can be used to force a reset of TCAMs on a per-core basis.If
 * a core is actively performing lookups when being reset, the results are
 * unpredictable.
 *
 * \details 
 * Bit n = '1': TCAMs within core n are reset
 *
 * Field: ::VTSS_VCAP_SUPER_TCAM_CTRL . TCAM_RST_SHOT
 */
#define  VTSS_F_VCAP_SUPER_TCAM_CTRL_TCAM_RST_SHOT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VCAP_SUPER_TCAM_CTRL_TCAM_RST_SHOT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VCAP_SUPER_TCAM_CTRL_TCAM_RST_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * This field can be used to shut down TCAMs on a per-core basis.If TCAMs
 * are powered back up after having been in shutdown mode, they must be
 * reset.
 *
 * \details 
 * Bit n = '0': TCAMs within core n are powered up
 * Bit n = '1': TCAMs within core n are in shutdown mode
 *
 * Field: ::VTSS_VCAP_SUPER_TCAM_CTRL . TCAM_SD
 */
#define  VTSS_F_VCAP_SUPER_TCAM_CTRL_TCAM_SD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VCAP_SUPER_TCAM_CTRL_TCAM_SD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VCAP_SUPER_TCAM_CTRL_TCAM_SD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief TCAM BIST control
 *
 * \details
 * Register: \a VCAP_SUPER:TCAM_BIST:BIST_CTRL
 */
#define VTSS_VCAP_SUPER_BIST_CTRL            VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xf3)

/** 
 * \brief
 * Enables the BIST process. The bit must be '1' while the BIST is running.
 * When the bit is set to '0', the BIST_FAIL and BIST_PASS bits are
 * cleared.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_CTRL . BIST_RUN
 */
#define  VTSS_F_VCAP_SUPER_BIST_CTRL_BIST_RUN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_SUPER_BIST_CTRL_BIST_RUN  VTSS_BIT(2)
#define  VTSS_X_VCAP_SUPER_BIST_CTRL_BIST_RUN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * BIST run-forever mode. When set to '1', the BIST will keep running until
 * it is set to '0'. The BIST will finish the on-going iteration of the
 * BIST algorithm when BIST_RUN_FOREVER is set to '0'. BIST_STAT.BIST_PASS
 * and BIST_STAT.BIST_FAIL status will not be available while BIST is
 * running in in run-forever mode as it will not be available after
 * clearing BIST_RUN_FOREVER.(Status is actually available for 3 system
 * clock cycles at the end of each iteration, but they are not latched in
 * hardware and can therefore not be read reliably).
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_CTRL . BIST_RUN_FOREVER
 */
#define  VTSS_F_VCAP_SUPER_BIST_CTRL_BIST_RUN_FOREVER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_BIST_CTRL_BIST_RUN_FOREVER  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_BIST_CTRL_BIST_RUN_FOREVER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Resume BIST when running in retention mode (BIST_CFG.BIST_RETENT_ENA).
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_CTRL . BIST_RESUME_SHOT
 */
#define  VTSS_F_VCAP_SUPER_BIST_CTRL_BIST_RESUME_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_BIST_CTRL_BIST_RESUME_SHOT  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_BIST_CTRL_BIST_RESUME_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TCAM BIST configuration
 *
 * \details
 * Register: \a VCAP_SUPER:TCAM_BIST:BIST_CFG
 */
#define VTSS_VCAP_SUPER_BIST_CFG             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xf4)

/** 
 * \brief
 * Test TCAMs in stop-on-fail mode or in repair mode.
 *
 * \details 
 * '0': Stop-on-fail mode. The BIST will stop when a failure is detected
 * and no repair will be attempted.
 * '1': Repair mode. If the BIST detects a failure, it will try to repair
 * the defect by controlling the Redundancy Configuration Register (RCR) of
 * the TCAM and retest the TCAM. The RCR values applied by the BIST in
 * repair mode can be read out by using RCR_CTRL.RCR_OPR.
 *
 * Field: ::VTSS_VCAP_SUPER_BIST_CFG . BIST_REPAIR_ENA
 */
#define  VTSS_F_VCAP_SUPER_BIST_CFG_BIST_REPAIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_BIST_CFG_BIST_REPAIR_ENA  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_BIST_CFG_BIST_REPAIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable the BIST retention test mode.In this mode, the BIST will pause at
 * the defined test sequences for retention test. BIST_STAT.BIST_PAUSED
 * will be set to '1'. The BIST will continue execution when
 * BIST_CTRL.BIST_RESUME_SHOT is set to '1'.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_CFG . BIST_RETENT_ENA
 */
#define  VTSS_F_VCAP_SUPER_BIST_CFG_BIST_RETENT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_BIST_CFG_BIST_RETENT_ENA  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_BIST_CFG_BIST_RETENT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TCAM BIST status
 *
 * \details
 * Register: \a VCAP_SUPER:TCAM_BIST:BIST_STAT
 */
#define VTSS_VCAP_SUPER_BIST_STAT            VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xf5)

/** 
 * \brief
 * The overall BIST result from all TCAMs. If all TCAMs passed the BIST,
 * this bit will be set to '1'. The bit is automatically cleared when
 * BIST_RUN is set to '0'.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_STAT . BIST_PASS
 */
#define  VTSS_F_VCAP_SUPER_BIST_STAT_BIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VCAP_SUPER_BIST_STAT_BIST_PASS  VTSS_BIT(3)
#define  VTSS_X_VCAP_SUPER_BIST_STAT_BIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * The overall BIST result from all TCAMs. If any of the TCAMs failed the
 * BIST, this bit will be set to '1'. The bit is automatically cleared when
 * BIST_RUN is set to '0'.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_STAT . BIST_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_STAT_BIST_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_SUPER_BIST_STAT_BIST_FAIL  VTSS_BIT(2)
#define  VTSS_X_VCAP_SUPER_BIST_STAT_BIST_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Indicates that BIST execution is paused for retention test.Retention
 * test is enabled through BIST_CFG.BIST_RETENT_ENA. BIST is resumed by
 * setting BIST_CTRL.BIST_RESUME_SHOT.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_STAT . BIST_PAUSED
 */
#define  VTSS_F_VCAP_SUPER_BIST_STAT_BIST_PAUSED(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_BIST_STAT_BIST_PAUSED  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_BIST_STAT_BIST_PAUSED(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * The BIST has completed for all TCAMs. The bit is automatically cleared
 * when BIST_RUN is set to '0'.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_STAT . BIST_DONE
 */
#define  VTSS_F_VCAP_SUPER_BIST_STAT_BIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_BIST_STAT_BIST_DONE  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_BIST_STAT_BIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TCAM BIST fail status
 *
 * \details
 * The register is replicated; index 0 holds the fail status of all TCAMs
 * within RTL core 0.
 *
 * Register: \a VCAP_SUPER:TCAM_BIST:BIST_FAIL_STAT
 *
 * @param ri Register: BIST_FAIL_STAT (??), 0-15
 */
#define VTSS_VCAP_SUPER_BIST_FAIL_STAT(ri)   VTSS_IOREG(VTSS_TO_VCAP_SUPER,0xf6 + (ri))

/** 
 * \brief
 * The BIST results from the individual TCAMs within the core. For a core
 * with 6 TCAM instances, this field will hold 6 status bits. The status
 * for all TCAMs is available when BIST_STAT.BIST_DONE has been set. The
 * bits are automatically cleared when BIST_RUN is set to '0'.
 *
 * \details 
 * '1' indicates that the TCAM with the same index within the core as the
 * bit position in this field has failed with BIST.
 *
 * Field: ::VTSS_VCAP_SUPER_BIST_FAIL_STAT . BIST_PER_TCAM_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_FAIL_STAT_BIST_PER_TCAM_FAIL(x)  (x)
#define  VTSS_M_VCAP_SUPER_BIST_FAIL_STAT_BIST_PER_TCAM_FAIL     0xffffffff
#define  VTSS_X_VCAP_SUPER_BIST_FAIL_STAT_BIST_PER_TCAM_FAIL(x)  (x)


/** 
 * \brief TCAM BIST diagnostics control
 *
 * \details
 * Register: \a VCAP_SUPER:TCAM_BIST:BIST_DIAG_CTRL
 */
#define VTSS_VCAP_SUPER_BIST_DIAG_CTRL       VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x106)

/** 
 * \brief
 * TCAM index for BIST diagnostics registers.The BIST diagnostics register
 * chain runs through all TCAMs starting from the core with the lowest
 * number in the RTL to the core with the highest number. Within a core,
 * the chain runs from the TCAM holding the least significant sub-words to
 * the TCAM holding the most significant sub-words. Index 0 points to the
 * TCAM holding the least significant sub-words in RTL core 0.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_CTRL . BIST_DIAG_IDX
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_IDX(x)  VTSS_ENCODE_BITFIELD(x,7,6)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_IDX     VTSS_ENCODE_BITMASK(7,6)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_IDX(x)  VTSS_EXTRACT_BITFIELD(x,7,6)

/** 
 * \brief
 * The BIST diagnostics registers related to the TCAM with index
 * BIST_DIAG_IDX are updated. When the update has been completed, this bit
 * is automatically cleared. BIST_CTRL.BIST_RUN must be '1' while accessing
 * the BIST diagnostics register chain.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_CTRL . BIST_DIAG_SHOT
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_SHOT  VTSS_BIT(6)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * The BIST diagnostics registers in all TCAMs are reset, independantly of
 * the value in BIST_DIAG_IDX. When the reset has been completed, this bit
 * is automatically cleared.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_CTRL . BIST_DIAG_RST_SHOT
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_RST_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_RST_SHOT  VTSS_BIT(5)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_RST_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Configures the number of errors to skip when running the BIST. When BIST
 * diagnostics is read, this registers is updated with the value from the
 * TCAM with index BIST_DIAG_IDX.
 *
 * \details 
 * 0: No errors are skipped
 * n: The BIST skips the first n errors detected.
 *
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_CTRL . BIST_DIAG_SKIP_ERR
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_SKIP_ERR(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_SKIP_ERR     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_CTRL_BIST_DIAG_SKIP_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief TCAM BIST diagnostics status
 *
 * \details
 * TCAM BIST diagnostics status registers related to the TCAM with index
 * BIST_DIAG_CTRL.BIST_DIAG_IDX. The fields in this register are updated
 * through BIST_DIAG_CTRL.BIST_DIAG_SHOT.
 *
 * Register: \a VCAP_SUPER:TCAM_BIST:BIST_DIAG_STAT
 */
#define VTSS_VCAP_SUPER_BIST_DIAG_STAT       VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x107)

/** 
 * \brief
 * Fail sequence number. BIST sequence number of the latest error detected
 * in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_FAIL_SEQ
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL_SEQ(x)  VTSS_ENCODE_BITFIELD(x,18,8)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL_SEQ     VTSS_ENCODE_BITMASK(18,8)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL_SEQ(x)  VTSS_EXTRACT_BITFIELD(x,18,8)

/** 
 * \brief
 * Fail address. The address at which the latest error was detected in the
 * TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_FAIL_ADDR
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL_ADDR(x)  VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL_ADDR     VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,10,8)

/** 
 * \brief
 * Flag indicating that a qhita error was detected in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_HITA_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_HITA_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_HITA_FAIL  VTSS_BIT(9)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_HITA_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Flag indicating that a qhitb error was detected in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_HITB_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_HITB_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_HITB_FAIL  VTSS_BIT(8)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_HITB_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Flag indicating that a vbita (valid bit A) error was detected in the
 * TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_VBITA_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_VBITA_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_VBITA_FAIL  VTSS_BIT(7)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_VBITA_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Flag indicating that a vbitb (valid bit B) error was detected in the
 * TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_VBITB_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_VBITB_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_VBITB_FAIL  VTSS_BIT(6)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_VBITB_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Flag indicating that a maska (mask A) error was detected in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_MASKA_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_MASKA_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_MASKA_FAIL  VTSS_BIT(5)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_MASKA_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Flag indicating that a maskb (mask B) error was detected in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_MASKB_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_MASKB_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_MASKB_FAIL  VTSS_BIT(4)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_MASKB_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Flag indicating that a dataa (data A) error was detected in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_DATAA_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_DATAA_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_DATAA_FAIL  VTSS_BIT(3)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_DATAA_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Flag indicating that a datab (data B) error was detected in the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_DATAB_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_DATAB_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_DATAB_FAIL  VTSS_BIT(2)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_DATAB_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Flag indicating that the BIST passed for the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_PASS
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_PASS  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_PASS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Flag indicating that the BIST failed for the TCAM.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_STAT . BIST_DIAG_FAIL
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_STAT_BIST_DIAG_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TCAM BIST diagnostics bitmap A status
 *
 * \details
 * TCAM BIST diagnostics status registers related to the TCAM with index
 * BIST_DIAG_CTRL.BIST_DIAG_IDX. The fields in this register are updated
 * through BIST_DIAG_CTRL.BIST_DIAG_SHOT.
 * The register is replicated; index 0 holds the 32 LSBs of the bitmap;
 * index 1 holds the 20 MSBs of the bitmap.
 *
 * Register: \a VCAP_SUPER:TCAM_BIST:BIST_DIAG_BITMAPA_STAT
 *
 * @param ri Register: BIST_DIAG_BITMAPA_STAT (??), 0-1
 */
#define VTSS_VCAP_SUPER_BIST_DIAG_BITMAPA_STAT(ri)  VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x108 + (ri))

/** 
 * \brief
 * 52-bits bitmap of the comparation result for TCAM array A.
 *
 * \details 
 * '0': The comparision resulted in a match in the bit position.
 * '1': The comparison resulted in a mismatch in the bit position.

 *
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_BITMAPA_STAT . BIST_DIAG_BITMAPA
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_BITMAPA_STAT_BIST_DIAG_BITMAPA(x)  (x)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_BITMAPA_STAT_BIST_DIAG_BITMAPA     0xffffffff
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_BITMAPA_STAT_BIST_DIAG_BITMAPA(x)  (x)


/** 
 * \brief TCAM BIST diagnostics bitmap B status
 *
 * \details
 * TCAM BIST diagnostics status registers related to the TCAM with index
 * BIST_DIAG_CTRL.BIST_DIAG_IDX. The fields in this register are updated
 * through BIST_DIAG_CTRL.BIST_DIAG_SHOT.
 * The register is replicated; index 0 holds the 32 LSBs of the bitmap;
 * index 1 holds the 20 MSBs of the bitmap.
 *
 * Register: \a VCAP_SUPER:TCAM_BIST:BIST_DIAG_BITMAPB_STAT
 *
 * @param ri Register: BIST_DIAG_BITMAPB_STAT (??), 0-1
 */
#define VTSS_VCAP_SUPER_BIST_DIAG_BITMAPB_STAT(ri)  VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x10a + (ri))

/** 
 * \brief
 * 52-bits bitmap of the comparation result for TCAM array B.
 *
 * \details 
 * '0': The comparision resulted in a match in the bit position.
 * '1': The comparison resulted in a mismatch in the bit position.

 *
 * Field: ::VTSS_VCAP_SUPER_BIST_DIAG_BITMAPB_STAT . BIST_DIAG_BITMAPB
 */
#define  VTSS_F_VCAP_SUPER_BIST_DIAG_BITMAPB_STAT_BIST_DIAG_BITMAPB(x)  (x)
#define  VTSS_M_VCAP_SUPER_BIST_DIAG_BITMAPB_STAT_BIST_DIAG_BITMAPB     0xffffffff
#define  VTSS_X_VCAP_SUPER_BIST_DIAG_BITMAPB_STAT_BIST_DIAG_BITMAPB(x)  (x)


/** 
 * \brief TCAM Redundancy Configuration Register (RCR) control
 *
 * \details
 * Register: \a VCAP_SUPER:TCAM_BIST:RCR_CTRL
 */
#define VTSS_VCAP_SUPER_RCR_CTRL             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x10c)

/** 
 * \brief
 * RCR operationThe operation is initiated through RCR_SHOT.
 *
 * \details 
 * "00": Clear. The RCR of all TCAMs are cleared.
 * "01": Write. The RCR_DATA is written to the TCAM pointed out by RCR_IDX.
 * "10": Read. The RCR of the TCAM pointed out by RCR_IDX is read and
 * stored in RCR_DATA.
 *
 * Field: ::VTSS_VCAP_SUPER_RCR_CTRL . RCR_OPR
 */
#define  VTSS_F_VCAP_SUPER_RCR_CTRL_RCR_OPR(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_VCAP_SUPER_RCR_CTRL_RCR_OPR     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_VCAP_SUPER_RCR_CTRL_RCR_OPR(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * TCAM index for RCR read/write operations.The RCR chain runs through all
 * TCAMs starting from the core with the lowest number in the RTL to the
 * core with the highest number. Within a core, the chain runs from the
 * TCAM holding the least significant sub-words to the TCAM holding the
 * most significant sub-words. Index 0 points to the TCAM holding the least
 * significant sub-words in RTL core 0.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_RCR_CTRL . RCR_IDX
 */
#define  VTSS_F_VCAP_SUPER_RCR_CTRL_RCR_IDX(x)  VTSS_ENCODE_BITFIELD(x,15,6)
#define  VTSS_M_VCAP_SUPER_RCR_CTRL_RCR_IDX     VTSS_ENCODE_BITMASK(15,6)
#define  VTSS_X_VCAP_SUPER_RCR_CTRL_RCR_IDX(x)  VTSS_EXTRACT_BITFIELD(x,15,6)

/** 
 * \brief
 * When performing an RCR write operation, the value in RCR_DATA is written
 * to the TCAM with index RCR_IDX.When performing an RCR read operation,
 * the value read from the TCAM with index RCR_IDX is made available in
 * RCR_DATA.
 *
 * \details 
 * Duo TCAM Core B (most significant sub-word):
 * RCR_DATA[13:8]: The number of the normal column, which is disabled
 * RCR_DATA[7]: '0' indicates that none of the normal columns are disabled,
 * '1' indicates that the redundant column is in use and the normal column
 * in RCR_DATA[13:8] is disabled
 * Duo TCAM Core A (least significant sub-word):
 * RCR_DATA[6:1]: The number of the normal column, which is disabled
 * RCR_DATA[0]: '0' indicates that none of the normal columns are disabled,
 * '1' indicates that the redundant column is in use and the normal column
 * in RCR_DATA[6:1] is disabled

 *
 * Field: ::VTSS_VCAP_SUPER_RCR_CTRL . RCR_DATA
 */
#define  VTSS_F_VCAP_SUPER_RCR_CTRL_RCR_DATA(x)  VTSS_ENCODE_BITFIELD(x,1,14)
#define  VTSS_M_VCAP_SUPER_RCR_CTRL_RCR_DATA     VTSS_ENCODE_BITMASK(1,14)
#define  VTSS_X_VCAP_SUPER_RCR_CTRL_RCR_DATA(x)  VTSS_EXTRACT_BITFIELD(x,1,14)

/** 
 * \brief
 * The RCR operation specified in RCR_OPR is triggered. When the operation
 * has been completed, this bit is automatically cleared.
 * BIST_CTRL.BIST_RUN must be set to '0' when performing RCR operations.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_RCR_CTRL . RCR_SHOT
 */
#define  VTSS_F_VCAP_SUPER_RCR_CTRL_RCR_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_RCR_CTRL_RCR_SHOT  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_RCR_CTRL_RCR_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TCAM RCR status
 *
 * \details
 * Register: \a VCAP_SUPER:TCAM_BIST:RCR_STAT
 */
#define VTSS_VCAP_SUPER_RCR_STAT             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x10d)

/** 
 * \brief
 * Set while an RCR operation is running.RCR configuration run
 * automatically after reset and it must be ensure that this bit hs been
 * cleared before using the TCAMs.Before reading RCR_DATA after a read
 * operation, it must be ensured that this bit has been cleared.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_RCR_STAT . RCR_BUSY
 */
#define  VTSS_F_VCAP_SUPER_RCR_STAT_RCR_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_RCR_STAT_RCR_BUSY  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_RCR_STAT_RCR_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VCAP_SUPER:ECC_CHK
 *
 * ECC Checker for TCAM
 */


/** 
 * \brief Control register for ECC checker
 *
 * \details
 * Register: \a VCAP_SUPER:ECC_CHK:ECC_CTRL
 */
#define VTSS_VCAP_SUPER_ECC_CTRL             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x10e)

/** 
 * \brief
 * Set to disable automatic detect of parity invalidate. This is meant for
 * verification of the ECC check function by allowing change of TCAM
 * contents without ECC knowing this.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ECC_CTRL . AUTO_INVALIDATE_DIS
 */
#define  VTSS_F_VCAP_SUPER_ECC_CTRL_AUTO_INVALIDATE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_SUPER_ECC_CTRL_AUTO_INVALIDATE_DIS  VTSS_BIT(2)
#define  VTSS_X_VCAP_SUPER_ECC_CTRL_AUTO_INVALIDATE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to hook ECC checker up to global DEVCPU integrity monitor. By
 * default ECC events (and integrity interrupt) are handled by local
 * integrity monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ECC_CTRL . LOCAL_MEMITGR_DIS
 */
#define  VTSS_F_VCAP_SUPER_ECC_CTRL_LOCAL_MEMITGR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_ECC_CTRL_LOCAL_MEMITGR_DIS  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_ECC_CTRL_LOCAL_MEMITGR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable automatic ECC check function. Once enabled the ECC checker
 * block will automatically monitor the TCAM array for ECC upsets and
 * correct single-bit upsets or report double-bit upsets via the integrity
 * ring. See MEMITGR block in DEVCPU_GCB target for more information about
 * integrity monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ECC_CTRL . ECC_CHK_ENA
 */
#define  VTSS_F_VCAP_SUPER_ECC_CTRL_ECC_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_ECC_CTRL_ECC_CHK_ENA  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_ECC_CTRL_ECC_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Various information from the ECC checker
 *
 * \details
 * Register: \a VCAP_SUPER:ECC_CHK:ECC_STAT
 */
#define VTSS_VCAP_SUPER_ECC_STAT             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x10f)

/** 
 * \brief
 * Set when the block-delay is set too low for blocks to finish before next
 * tick is generated.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ECC_STAT . BLK_DLY_TOO_SMALL
 */
#define  VTSS_F_VCAP_SUPER_ECC_STAT_BLK_DLY_TOO_SMALL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_ECC_STAT_BLK_DLY_TOO_SMALL  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_ECC_STAT_BLK_DLY_TOO_SMALL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set whenever ECC is done processing a block.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ECC_STAT . BLK_DONE
 */
#define  VTSS_F_VCAP_SUPER_ECC_STAT_BLK_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_ECC_STAT_BLK_DONE  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_ECC_STAT_BLK_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Delay between checking ECC blocks
 *
 * \details
 * Register: \a VCAP_SUPER:ECC_CHK:ECC_BLK_DLY
 */
#define VTSS_VCAP_SUPER_ECC_BLK_DLY          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x110)

/** 
 * \brief
 * Set to specific minimum number of clock-cycles between reading blocks of
 * data from the TCAM. The ECC checker works by periodically reading out
 * blocks and checking them against known good parity. The default value
 * will make the ECC checker go throguh the TCAM once every minute.
 *
 * \details 
 * n: Wait at least n clock cylces between subword reads.
 *
 * Field: ::VTSS_VCAP_SUPER_ECC_BLK_DLY . BLK_DLY
 */
#define  VTSS_F_VCAP_SUPER_ECC_BLK_DLY_BLK_DLY(x)  (x)
#define  VTSS_M_VCAP_SUPER_ECC_BLK_DLY_BLK_DLY     0xffffffff
#define  VTSS_X_VCAP_SUPER_ECC_BLK_DLY_BLK_DLY(x)  (x)


/** 
 * \brief Invalidate ECC parity info
 *
 * \details
 * Register: \a VCAP_SUPER:ECC_CHK:ECC_INV
 */
#define VTSS_VCAP_SUPER_ECC_INV              VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x111)

/** 
 * \brief
 * See INV for more information.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ECC_INV . INV_ADDR
 */
#define  VTSS_F_VCAP_SUPER_ECC_INV_INV_ADDR(x)  VTSS_ENCODE_BITFIELD(x,2,16)
#define  VTSS_M_VCAP_SUPER_ECC_INV_INV_ADDR     VTSS_ENCODE_BITMASK(2,16)
#define  VTSS_X_VCAP_SUPER_ECC_INV_INV_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,2,16)

/** 
 * \brief
 * Set to invalidate parity information for a specific TCAM subword, the
 * subword to invalidate is specified via INV_ADDR field. This field is
 * automatically cleared when subword parity has been invalidated.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ECC_INV . INV
 */
#define  VTSS_F_VCAP_SUPER_ECC_INV_INV(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_ECC_INV_INV        VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_ECC_INV_INV(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to invalidate parity information for all TCAM subwords. This field
 * is automatically cleared when all parities has been invalidated.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_ECC_INV . INV_ALL
 */
#define  VTSS_F_VCAP_SUPER_ECC_INV_INV_ALL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_ECC_INV_INV_ALL    VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_ECC_INV_INV_ALL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VCAP_SUPER:MEMITGR
 *
 * Memory integrity monitor
 */


/** 
 * \brief Monitor control
 *
 * \details
 * Register: \a VCAP_SUPER:MEMITGR:MEMITGR_CTRL
 */
#define VTSS_VCAP_SUPER_MEMITGR_CTRL         VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x112)

/** 
 * \brief
 * Setting this field transitions the integrity monitor between operating
 * modes. Transitioning between modes takes time, this field remains set
 * until the new mode is reached. During this time the monitor also reports
 * busy VCAP_SUPER::MEMITGR_STAT.MODE_BUSY is set).From IDLE
 * (VCAP_SUPER::MEMITGR_STAT.MODE_IDLE is set) the monitor can transition
 * into either DETECT or LISTEN mode, the DETECT mode is entered if a
 * memory reports an indication - the LISTEN mode is entered if no
 * indications are reported. The first time after reset the monitor will
 * not detect indications, that is; it will transition directly from IDLE
 * to LISTEN mode.From DETECT (VCAP_SUPER::MEMITGR_STAT.MODE_DETECT is set)
 * the monitor can transition into either DETECT or LISTEN mode, the DETECT
 * mode is entered if more indications are reported - the LISTEN mode is
 * entered if no more indications are reported.From LISTEN
 * (VCAP_SUPER::MEMITGR_STAT.MODE_LISTEN is set) the monitor can transition
 * into IDLE mode.Software shall not set this field when the monitor is
 * BUSY (when VCAP_SUPER::MEMITGR_STAT.MODE_BUSY is set.)
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_CTRL . ACTIVATE
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_CTRL_ACTIVATE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_CTRL_ACTIVATE  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_MEMITGR_CTRL_ACTIVATE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Monitor status
 *
 * \details
 * Register: \a VCAP_SUPER:MEMITGR:MEMITGR_STAT
 */
#define VTSS_VCAP_SUPER_MEMITGR_STAT         VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x113)

/** 
 * \brief
 * This field is set if there is an overflow when recording indications
 * from the memories. If this happens (setting of this field) the value of
 * the VCAP_SUPER::MEMITGR_DIV.MEM_DIV field is set too low!
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_STAT . INDICATION_OVF
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_STAT_INDICATION_OVF(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_STAT_INDICATION_OVF  VTSS_BIT(5)
#define  VTSS_X_VCAP_SUPER_MEMITGR_STAT_INDICATION_OVF(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * If this field is set then there is an indication from one of the
 * memories that needs to be analyzed. An indication is either a parity
 * detection or an error correction.This field is only set when the monitor
 * is in LISTEN mode (VCAP_SUPER::MEMITGR_STAT.MODE_LISTEN is set), in all
 * other states (including BUSY) this field returns 0.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_STAT . INDICATION
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_STAT_INDICATION(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_STAT_INDICATION  VTSS_BIT(4)
#define  VTSS_X_VCAP_SUPER_MEMITGR_STAT_INDICATION(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * This field is set when the monitor is in LISTEN mode, during listen mode
 * the monitor continually check for parity/correction indications from the
 * memories.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_STAT . MODE_LISTEN
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_STAT_MODE_LISTEN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_STAT_MODE_LISTEN  VTSS_BIT(3)
#define  VTSS_X_VCAP_SUPER_MEMITGR_STAT_MODE_LISTEN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * This field is set when the monitor is in DETECT mode, during detect mode
 * the VCAP_SUPER::MEMITGR_INFO and VCAP_SUPER::MEMITGR_IDX registers
 * contains valid information about one indication.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_STAT . MODE_DETECT
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_STAT_MODE_DETECT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_STAT_MODE_DETECT  VTSS_BIT(2)
#define  VTSS_X_VCAP_SUPER_MEMITGR_STAT_MODE_DETECT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This field is set when the monitor is in IDLE mode.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_STAT . MODE_IDLE
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_STAT_MODE_IDLE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_STAT_MODE_IDLE  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_MEMITGR_STAT_MODE_IDLE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * The busy signal is a copy of the VCAP_SUPER::MEMITGR_CTRL.ACTIVATE
 * field, see description of that field for more information about the
 * different states/modes of the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_STAT . MODE_BUSY
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_STAT_MODE_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_STAT_MODE_BUSY  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_MEMITGR_STAT_MODE_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Memory indication
 *
 * \details
 * This field is only valid when the monitor is in the DETECT
 * (VCAP_SUPER::MEMITGR_STAT.MODE_DETECT is set) mode.
 *
 * Register: \a VCAP_SUPER:MEMITGR:MEMITGR_INFO
 */
#define VTSS_VCAP_SUPER_MEMITGR_INFO         VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x114)

/** 
 * \brief
 * This field is set if the monitor has detected a parity indication (or an
 * unrecoverable correction).
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_INFO . MEM_ERR
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_INFO_MEM_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_INFO_MEM_ERR  VTSS_BIT(31)
#define  VTSS_X_VCAP_SUPER_MEMITGR_INFO_MEM_ERR(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * This field is set if the monitor has detected a correction.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_INFO . MEM_COR
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_INFO_MEM_COR(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_INFO_MEM_COR  VTSS_BIT(30)
#define  VTSS_X_VCAP_SUPER_MEMITGR_INFO_MEM_COR(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * This field is set if the monitor has detected a parity indication (or an
 * unrecoverable correction) for which the address has not been recorded.If
 * VCAP_SUPER::MEMITGR_INFO.MEM_ERR is set then there has been more than
 * one indication, then only the address of the newest indication has been
 * kept. If VCAP_SUPER::MEMITGR_INFO.MEM_ERR is cleared then an indication
 * has occurred for which the address could not be stored, this is a very
 * rare situation that can only happen if an indication is detected just as
 * the memory is talking to the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_INFO . MEM_ERR_OVF
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_INFO_MEM_ERR_OVF(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_INFO_MEM_ERR_OVF  VTSS_BIT(29)
#define  VTSS_X_VCAP_SUPER_MEMITGR_INFO_MEM_ERR_OVF(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * This field is set if the monitor has correction indication for which the
 * address has not been recorded.If VCAP_SUPER::MEMITGR_INFO.MEM_ERR is set
 * then there has also been a parity indication (or an unrecoverable
 * correction) which takes priority over correction indications.If
 * VCAP_SUPER::MEMITGR_INFO.MEM_ERR is cleared and
 * VCAP_SUPER::MEMITGR_INFO.MEM_COR is set then there has been more than
 * one correction indication, then only the address of the newest
 * correction indication has been kept.If VCAP_SUPER::MEMITGR_INFO.MEM_ERR
 * and VCAP_SUPER::MEMITGR_INFO.MEM_COR is both cleared then a correction
 * indication has occurred for which the address could not be stored, this
 * is a very rare situation that can only happen if an indication is
 * detected just as the memory is talking to the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_INFO . MEM_COR_OVF
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_INFO_MEM_COR_OVF(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_INFO_MEM_COR_OVF  VTSS_BIT(28)
#define  VTSS_X_VCAP_SUPER_MEMITGR_INFO_MEM_COR_OVF(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * This field is valid only when VCAP_SUPER::MEMITGR_INFO.MEM_ERR or
 * VCAP_SUPER::MEMITGR_INFO.MEM_COR is set.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_INFO . MEM_ADDR
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_INFO_MEM_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_VCAP_SUPER_MEMITGR_INFO_MEM_ADDR     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_VCAP_SUPER_MEMITGR_INFO_MEM_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Memory index
 *
 * \details
 * This field is only valid when the monitor is in the DETECT
 * (VCAP_SUPER::MEMITGR_STAT.MODE_DETECT is set) mode.
 *
 * Register: \a VCAP_SUPER:MEMITGR:MEMITGR_IDX
 */
#define VTSS_VCAP_SUPER_MEMITGR_IDX          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x115)

/** 
 * \brief
 * This field contains a unique index for the memory for which info is
 * currently provided in VCAP_SUPER::MEMITGR_INFO. Indexes are counted from
 * 1 (not 0).
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_IDX . MEM_IDX
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_IDX_MEM_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VCAP_SUPER_MEMITGR_IDX_MEM_IDX     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VCAP_SUPER_MEMITGR_IDX_MEM_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Monitor speed
 *
 * \details
 * Register: \a VCAP_SUPER:MEMITGR:MEMITGR_DIV
 */
#define VTSS_VCAP_SUPER_MEMITGR_DIV          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x116)

/** 
 * \brief
 * Configure divider for generating the sync-pulse to memories (controls
 * the speed at which the monitor talks to the memories). The lower this is
 * set the faster indications can be read out of the memories.
 *
 * \details 
 * See datasheet for appropriate value.
 *
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DIV . MEM_DIV
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DIV_MEM_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DIV_MEM_DIV     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DIV_MEM_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Debug registers
 *
 * \details
 * Register: \a VCAP_SUPER:MEMITGR:MEMITGR_DBG
 */
#define VTSS_VCAP_SUPER_MEMITGR_DBG          VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x117)

/** 
 * \brief
 * This field is used for test purposes.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . MEM_DIV_SENSE
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_MEM_DIV_SENSE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_MEM_DIV_SENSE  VTSS_BIT(9)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_MEM_DIV_SENSE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set to force the intr-field of the intgrity-ring out from the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . FORCE_INTR
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_FORCE_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_FORCE_INTR  VTSS_BIT(8)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_FORCE_INTR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Always shows the (resynced) value of the sync-field of the
 * integrity-ring into the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . SYNC_IN
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_SYNC_IN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_SYNC_IN  VTSS_BIT(7)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_SYNC_IN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Always shows the (resynced) value of the ena-field of the integrity-ring
 * into the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . ENA_IN
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_ENA_IN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_ENA_IN  VTSS_BIT(6)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_ENA_IN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Always shows the (resynced) value of the data-field of the
 * integrity-ring into the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . DATA_IN
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_DATA_IN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_DATA_IN  VTSS_BIT(5)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_DATA_IN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Always shows the (resynced) value of the intr-field of the
 * integrity-ring into the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . INTR_IN
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_INTR_IN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_INTR_IN  VTSS_BIT(4)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_INTR_IN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * When VCAP_SUPER::MEMITGR_DBG.FORCE_ENA is set, this value is driven to
 * sync-field of the intgrity-ring out from the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . SYNC_OUT
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_SYNC_OUT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_SYNC_OUT  VTSS_BIT(3)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_SYNC_OUT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When VCAP_SUPER::MEMITGR_DBG.FORCE_ENA is set, this value is driven to
 * ena-field of the intgrity-ring out from the monitor.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . ENA_OUT
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_ENA_OUT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_ENA_OUT  VTSS_BIT(2)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_ENA_OUT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to overtake ena and sync outputs (bit banging on the integrity ring)
 * and drive these by VCAP_SUPER::MEMITGR_DBG.ENA_OUT and
 * VCAP_SUPER::MEMITGR_DBG.SYNC_OUT respectively.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . FORCE_ENA
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_FORCE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_FORCE_ENA  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_FORCE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to enable detection of parity detections and ecc
 * corrections.The monitor must be initialized before first use (after
 * reset), this is done by making the first transtion from IDLE to LISTEN
 * mode without enabeling detections (this field is cleared) and then
 * setting this field once the monitor reaches the LISTEN mode.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_MEMITGR_DBG . DETECT_ENA
 */
#define  VTSS_F_VCAP_SUPER_MEMITGR_DBG_DETECT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_MEMITGR_DBG_DETECT_ENA  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_MEMITGR_DBG_DETECT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VCAP_SUPER:RAM_CTRL
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
 * Register: \a VCAP_SUPER:RAM_CTRL:RAM_INIT
 */
#define VTSS_VCAP_SUPER_RAM_INIT             VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x118)

/** 
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete (approx. 40 us).
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_VCAP_SUPER_RAM_INIT_RAM_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VCAP_SUPER_RAM_INIT_RAM_INIT  VTSS_BIT(1)
#define  VTSS_X_VCAP_SUPER_RAM_INIT_RAM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When this field is set, all memories HA_RESTART behavior will be
 * inverted. It is a backdoor for potentiel access issues.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_RAM_INIT . RAM_CFG_HOOK
 */
#define  VTSS_F_VCAP_SUPER_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VCAP_SUPER_RAM_INIT_RAM_CFG_HOOK  VTSS_BIT(0)
#define  VTSS_X_VCAP_SUPER_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VCAP_SUPER:COREMEM
 *
 * Access core memory
 */


/** 
 * \brief Address selection
 *
 * \details
 * Register: \a VCAP_SUPER:COREMEM:CM_ADDR
 */
#define VTSS_VCAP_SUPER_CM_ADDR              VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x119)

/** 
 * \brief
 * Address selection for the ram debug address space. 
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_VCAP_SUPER_CM_ADDR_CM_ADDR(x)  (x)
#define  VTSS_M_VCAP_SUPER_CM_ADDR_CM_ADDR     0xffffffff
#define  VTSS_X_VCAP_SUPER_CM_ADDR_CM_ADDR(x)  (x)


/** 
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a VCAP_SUPER:COREMEM:CM_DATA_WR
 */
#define VTSS_VCAP_SUPER_CM_DATA_WR           VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x11a)

/** 
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 bit inspection space. This register provides data to
 * be written when CM_OP is set.
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_CM_DATA_WR . CM_DATA_WR
 */
#define  VTSS_F_VCAP_SUPER_CM_DATA_WR_CM_DATA_WR(x)  (x)
#define  VTSS_M_VCAP_SUPER_CM_DATA_WR_CM_DATA_WR     0xffffffff
#define  VTSS_X_VCAP_SUPER_CM_DATA_WR_CM_DATA_WR(x)  (x)


/** 
 * \brief Core memory data register for read result
 *
 * \details
 * Register: \a VCAP_SUPER:COREMEM:CM_DATA_RD
 */
#define VTSS_VCAP_SUPER_CM_DATA_RD           VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x11b)

/** 
 * \brief
 * Read result
 *
 * \details 
 * Field: ::VTSS_VCAP_SUPER_CM_DATA_RD . CM_DATA_RD
 */
#define  VTSS_F_VCAP_SUPER_CM_DATA_RD_CM_DATA_RD(x)  (x)
#define  VTSS_M_VCAP_SUPER_CM_DATA_RD_CM_DATA_RD     0xffffffff
#define  VTSS_X_VCAP_SUPER_CM_DATA_RD_CM_DATA_RD(x)  (x)


/** 
 * \brief Operation to perform in core memory
 *
 * \details
 * Register: \a VCAP_SUPER:COREMEM:CM_OP
 */
#define VTSS_VCAP_SUPER_CM_OP                VTSS_IOREG(VTSS_TO_VCAP_SUPER,0x11c)

/** 
 * \brief
 * Ask the memory debug system to read or write a specific location. If no
 * response is received from a memory, due to timeout, or selected address
 * out of range, the state machine can be reset by issuing the 11
 * command.Field will return to 00 upon completion.
 *
 * \details 
 * 00: NOP
 * 01: Read from selected address into CM_DATA_RD
 * 10: Write CM_DATA_WR into selected address
 * 11: Reset debug access
 *
 * Field: ::VTSS_VCAP_SUPER_CM_OP . CM_OP
 */
#define  VTSS_F_VCAP_SUPER_CM_OP_CM_OP(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VCAP_SUPER_CM_OP_CM_OP        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VCAP_SUPER_CM_OP_CM_OP(x)     VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_FA_REGS_VCAP_SUPER_H_ */
