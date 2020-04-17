// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_ASM_H_
#define _VTSS_FA_REGS_ASM_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a ASM
 *
 * Assembler
 *
 ***********************************************************************/

/**
 * Register Group: \a ASM:DEV_STATISTICS
 *
 * Not documented
 */


/** 
 * \brief Rx Byte Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_IN_BYTES_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_IN_BYTES_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,0)

/** 
 * \brief
 * The number of bytes received (good, bad, and framing).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_IN_BYTES_CNT . RX_IN_BYTES_CNT
 */
#define  VTSS_F_ASM_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT(x)  (x)
#define  VTSS_M_ASM_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT     0xffffffff
#define  VTSS_X_ASM_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Symbol Carrier Error Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SYMBOL_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SYMBOL_ERR_CNT(gi)       VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,1)

/** 
 * \brief
 * The number of frames received with one or more symbol errors.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SYMBOL_ERR_CNT . RX_SYMBOL_ERR_CNT
 */
#define  VTSS_F_ASM_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT(x)  (x)


/** 
 * \brief Rx Pause Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_PAUSE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_PAUSE_CNT(gi)            VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,2)

/** 
 * \brief
 * Number of pause control frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_PAUSE_CNT . RX_PAUSE_CNT
 */
#define  VTSS_F_ASM_RX_PAUSE_CNT_RX_PAUSE_CNT(x)  (x)
#define  VTSS_M_ASM_RX_PAUSE_CNT_RX_PAUSE_CNT     0xffffffff
#define  VTSS_X_ASM_RX_PAUSE_CNT_RX_PAUSE_CNT(x)  (x)


/** 
 * \brief Rx Control Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_UNSUP_OPCODE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_UNSUP_OPCODE_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,3)

/** 
 * \brief
 * Number of control frames with unsupported opcode received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_UNSUP_OPCODE_CNT . RX_UNSUP_OPCODE_CNT
 */
#define  VTSS_F_ASM_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT(x)  (x)
#define  VTSS_M_ASM_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT     0xffffffff
#define  VTSS_X_ASM_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT(x)  (x)


/** 
 * \brief Rx OK Byte Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_OK_BYTES_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_OK_BYTES_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,4)

/** 
 * \brief
 * The number of received bytes in good frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_OK_BYTES_CNT . RX_OK_BYTES_CNT
 */
#define  VTSS_F_ASM_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_ASM_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_ASM_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Bad Byte Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_BAD_BYTES_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_BAD_BYTES_CNT(gi)        VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,5)

/** 
 * \brief
 * The number of received bytes in bad frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_BAD_BYTES_CNT . RX_BAD_BYTES_CNT
 */
#define  VTSS_F_ASM_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT(x)  (x)
#define  VTSS_M_ASM_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT     0xffffffff
#define  VTSS_X_ASM_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Unicast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_UC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_UC_CNT(gi)               VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,6)

/** 
 * \brief
 * The number of good unicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_UC_CNT . RX_UC_CNT
 */
#define  VTSS_F_ASM_RX_UC_CNT_RX_UC_CNT(x)    (x)
#define  VTSS_M_ASM_RX_UC_CNT_RX_UC_CNT       0xffffffff
#define  VTSS_X_ASM_RX_UC_CNT_RX_UC_CNT(x)    (x)


/** 
 * \brief Rx Multicast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_MC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_MC_CNT(gi)               VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,7)

/** 
 * \brief
 * The number of good multicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_MC_CNT . RX_MC_CNT
 */
#define  VTSS_F_ASM_RX_MC_CNT_RX_MC_CNT(x)    (x)
#define  VTSS_M_ASM_RX_MC_CNT_RX_MC_CNT       0xffffffff
#define  VTSS_X_ASM_RX_MC_CNT_RX_MC_CNT(x)    (x)


/** 
 * \brief Rx Broadcast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_BC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_BC_CNT(gi)               VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,8)

/** 
 * \brief
 * The number of good broadcast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_BC_CNT . RX_BC_CNT
 */
#define  VTSS_F_ASM_RX_BC_CNT_RX_BC_CNT(x)    (x)
#define  VTSS_M_ASM_RX_BC_CNT_RX_BC_CNT       0xffffffff
#define  VTSS_X_ASM_RX_BC_CNT_RX_BC_CNT(x)    (x)


/** 
 * \brief Rx CRC Error Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_CRC_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_CRC_ERR_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,9)

/** 
 * \brief
 * The number of frames received with CRC error only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_CRC_ERR_CNT . RX_CRC_ERR_CNT
 */
#define  VTSS_F_ASM_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (valid frame format)
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_UNDERSIZE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_UNDERSIZE_CNT(gi)        VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,10)

/** 
 * \brief
 * The number of undersize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_UNDERSIZE_CNT . RX_UNDERSIZE_CNT
 */
#define  VTSS_F_ASM_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT(x)  (x)
#define  VTSS_M_ASM_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT     0xffffffff
#define  VTSS_X_ASM_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (CRC error)
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_FRAGMENTS_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_FRAGMENTS_CNT(gi)        VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,11)

/** 
 * \brief
 * The number of undersize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_FRAGMENTS_CNT . RX_FRAGMENTS_CNT
 */
#define  VTSS_F_ASM_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT(x)  (x)
#define  VTSS_M_ASM_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT     0xffffffff
#define  VTSS_X_ASM_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT(x)  (x)


/** 
 * \brief Rx In-range Length Error Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_IN_RANGE_LEN_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_IN_RANGE_LEN_ERR_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,12)

/** 
 * \brief
 * The number of frames with legal length field that does not match length
 * of MAC client data.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_IN_RANGE_LEN_ERR_CNT . RX_IN_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_ASM_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Out-Of-Range Length Error Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_OUT_OF_RANGE_LEN_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_OUT_OF_RANGE_LEN_ERR_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,13)

/** 
 * \brief
 * The number of frames with illegal length field (frames using type field
 * are not counted here).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_OUT_OF_RANGE_LEN_ERR_CNT . RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_ASM_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Oversize Counter (valid frame format)
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_OVERSIZE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_OVERSIZE_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,14)

/** 
 * \brief
 * The number of oversize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_OVERSIZE_CNT . RX_OVERSIZE_CNT
 */
#define  VTSS_F_ASM_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT(x)  (x)
#define  VTSS_M_ASM_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT     0xffffffff
#define  VTSS_X_ASM_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Jabbers Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_JABBERS_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_JABBERS_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,15)

/** 
 * \brief
 * The number of oversize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_JABBERS_CNT . RX_JABBERS_CNT
 */
#define  VTSS_F_ASM_RX_JABBERS_CNT_RX_JABBERS_CNT(x)  (x)
#define  VTSS_M_ASM_RX_JABBERS_CNT_RX_JABBERS_CNT     0xffffffff
#define  VTSS_X_ASM_RX_JABBERS_CNT_RX_JABBERS_CNT(x)  (x)


/** 
 * \brief Rx 64 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SIZE64_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SIZE64_CNT(gi)           VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,16)

/** 
 * \brief
 * The number of 64 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SIZE64_CNT . RX_SIZE64_CNT
 */
#define  VTSS_F_ASM_RX_SIZE64_CNT_RX_SIZE64_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SIZE64_CNT_RX_SIZE64_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SIZE64_CNT_RX_SIZE64_CNT(x)  (x)


/** 
 * \brief Rx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SIZE65TO127_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SIZE65TO127_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,17)

/** 
 * \brief
 * The number of 65 to 127 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SIZE65TO127_CNT . RX_SIZE65TO127_CNT
 */
#define  VTSS_F_ASM_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Rx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SIZE128TO255_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SIZE128TO255_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,18)

/** 
 * \brief
 * The number of 128 to 255 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SIZE128TO255_CNT . RX_SIZE128TO255_CNT
 */
#define  VTSS_F_ASM_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Rx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SIZE256TO511_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SIZE256TO511_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,19)

/** 
 * \brief
 * The number of 256 to 511 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SIZE256TO511_CNT . RX_SIZE256TO511_CNT
 */
#define  VTSS_F_ASM_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Rx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SIZE512TO1023_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SIZE512TO1023_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,20)

/** 
 * \brief
 * The number of 512 to 1023 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SIZE512TO1023_CNT . RX_SIZE512TO1023_CNT
 */
#define  VTSS_F_ASM_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Rx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SIZE1024TO1518_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SIZE1024TO1518_CNT(gi)   VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,21)

/** 
 * \brief
 * The number of 1024 to 1518 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SIZE1024TO1518_CNT . RX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_ASM_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Rx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SIZE1519TOMAX_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SIZE1519TOMAX_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,22)

/** 
 * \brief
 * The number of frames received longer than 1518 bytes and not longer than
 * Maximum Length Register (Maximum Length Register + 4 if the frame is
 * VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SIZE1519TOMAX_CNT . RX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_ASM_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Rx Inter Packet Gap Shrink Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_IPG_SHRINK_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_IPG_SHRINK_CNT(gi)       VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,23)

/** 
 * \brief
 * Number of inter packet gap shrinks detected (IPG < 12 bytes).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_IPG_SHRINK_CNT . RX_IPG_SHRINK_CNT
 */
#define  VTSS_F_ASM_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT(x)  (x)
#define  VTSS_M_ASM_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT     0xffffffff
#define  VTSS_X_ASM_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT(x)  (x)


/** 
 * \brief Tx Byte Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_OUT_BYTES_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_OUT_BYTES_CNT(gi)        VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,24)

/** 
 * \brief
 * The number of bytes transmitted (good, bad and framing).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_OUT_BYTES_CNT . TX_OUT_BYTES_CNT
 */
#define  VTSS_F_ASM_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT(x)  (x)
#define  VTSS_M_ASM_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT     0xffffffff
#define  VTSS_X_ASM_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT(x)  (x)


/** 
 * \brief Tx Pause Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_PAUSE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_PAUSE_CNT(gi)            VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,25)

/** 
 * \brief
 * The number of pause control frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_PAUSE_CNT . TX_PAUSE_CNT
 */
#define  VTSS_F_ASM_TX_PAUSE_CNT_TX_PAUSE_CNT(x)  (x)
#define  VTSS_M_ASM_TX_PAUSE_CNT_TX_PAUSE_CNT     0xffffffff
#define  VTSS_X_ASM_TX_PAUSE_CNT_TX_PAUSE_CNT(x)  (x)


/** 
 * \brief Tx OK Byte Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_OK_BYTES_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_OK_BYTES_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,26)

/** 
 * \brief
 * The number of bytes transmitted successfully.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_OK_BYTES_CNT . TX_OK_BYTES_CNT
 */
#define  VTSS_F_ASM_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_ASM_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_ASM_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT(x)  (x)


/** 
 * \brief Tx Unicast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_UC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_UC_CNT(gi)               VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,27)

/** 
 * \brief
 * The number of unicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_UC_CNT . TX_UC_CNT
 */
#define  VTSS_F_ASM_TX_UC_CNT_TX_UC_CNT(x)    (x)
#define  VTSS_M_ASM_TX_UC_CNT_TX_UC_CNT       0xffffffff
#define  VTSS_X_ASM_TX_UC_CNT_TX_UC_CNT(x)    (x)


/** 
 * \brief Tx Multicast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_MC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_MC_CNT(gi)               VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,28)

/** 
 * \brief
 * The number of multicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_MC_CNT . TX_MC_CNT
 */
#define  VTSS_F_ASM_TX_MC_CNT_TX_MC_CNT(x)    (x)
#define  VTSS_M_ASM_TX_MC_CNT_TX_MC_CNT       0xffffffff
#define  VTSS_X_ASM_TX_MC_CNT_TX_MC_CNT(x)    (x)


/** 
 * \brief Tx Broadcast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_BC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_BC_CNT(gi)               VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,29)

/** 
 * \brief
 * The number of broadcast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_BC_CNT . TX_BC_CNT
 */
#define  VTSS_F_ASM_TX_BC_CNT_TX_BC_CNT(x)    (x)
#define  VTSS_M_ASM_TX_BC_CNT_TX_BC_CNT       0xffffffff
#define  VTSS_X_ASM_TX_BC_CNT_TX_BC_CNT(x)    (x)


/** 
 * \brief Tx 64 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_SIZE64_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_SIZE64_CNT(gi)           VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,30)

/** 
 * \brief
 * The number of 64 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_SIZE64_CNT . TX_SIZE64_CNT
 */
#define  VTSS_F_ASM_TX_SIZE64_CNT_TX_SIZE64_CNT(x)  (x)
#define  VTSS_M_ASM_TX_SIZE64_CNT_TX_SIZE64_CNT     0xffffffff
#define  VTSS_X_ASM_TX_SIZE64_CNT_TX_SIZE64_CNT(x)  (x)


/** 
 * \brief Tx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_SIZE65TO127_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_SIZE65TO127_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,31)

/** 
 * \brief
 * The number of 65 to 127 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_SIZE65TO127_CNT . TX_SIZE65TO127_CNT
 */
#define  VTSS_F_ASM_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_ASM_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_ASM_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Tx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_SIZE128TO255_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_SIZE128TO255_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,32)

/** 
 * \brief
 * The number of 128 to 255 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_SIZE128TO255_CNT . TX_SIZE128TO255_CNT
 */
#define  VTSS_F_ASM_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_ASM_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_ASM_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Tx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_SIZE256TO511_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_SIZE256TO511_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,33)

/** 
 * \brief
 * The number of 256 to 511 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_SIZE256TO511_CNT . TX_SIZE256TO511_CNT
 */
#define  VTSS_F_ASM_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_ASM_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_ASM_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Tx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_SIZE512TO1023_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_SIZE512TO1023_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,34)

/** 
 * \brief
 * The number of 512 to 1023 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_SIZE512TO1023_CNT . TX_SIZE512TO1023_CNT
 */
#define  VTSS_F_ASM_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_ASM_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_ASM_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Tx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_SIZE1024TO1518_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_SIZE1024TO1518_CNT(gi)   VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,35)

/** 
 * \brief
 * The number of 1024 to 1518 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_SIZE1024TO1518_CNT . TX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_ASM_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_ASM_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_ASM_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Tx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_SIZE1519TOMAX_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_SIZE1519TOMAX_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,36)

/** 
 * \brief
 * The number of frames transmitted longer than 1518 bytes and not longer
 * than Maximum Length Register (Maximum Length Register + 4 if the frame
 * is VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_SIZE1519TOMAX_CNT . TX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_ASM_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_ASM_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_ASM_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Counter to track the dribble-nibble (extra nibble) errors in frames.
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_ALIGNMENT_LOST_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_ALIGNMENT_LOST_CNT(gi)   VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,37)

/** 
 * \brief
 * The number of frames received with Alignment (dribble-nibble) error.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_ALIGNMENT_LOST_CNT . RX_ALIGNMENT_LOST_CNT
 */
#define  VTSS_F_ASM_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT(x)  (x)
#define  VTSS_M_ASM_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT     0xffffffff
#define  VTSS_X_ASM_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT(x)  (x)


/** 
 * \brief Counts frames that are tagged (C-Tagged or S-Tagged).
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_TAGGED_FRMS_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_TAGGED_FRMS_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,38)

/** 
 * \brief
 * The number of frames received with C-Tag or S-Tag information
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_TAGGED_FRMS_CNT . RX_TAGGED_FRMS_CNT
 */
#define  VTSS_F_ASM_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_ASM_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_ASM_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are Not tagged  (neither C-Tagged nor S-Tagged).
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_UNTAGGED_FRMS_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_UNTAGGED_FRMS_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,39)

/** 
 * \brief
 * The number of frames received without C-Tag and S-Tag information.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_UNTAGGED_FRMS_CNT . RX_UNTAGGED_FRMS_CNT
 */
#define  VTSS_F_ASM_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_ASM_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_ASM_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are tagged (C-Tagged or S-Tagged).
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_TAGGED_FRMS_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_TAGGED_FRMS_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,40)

/** 
 * \brief
 * The number of frames transmitted with C-Tag or S-Tag information
 *
 * \details 
 * Field: ::VTSS_ASM_TX_TAGGED_FRMS_CNT . TX_TAGGED_FRMS_CNT
 */
#define  VTSS_F_ASM_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_ASM_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_ASM_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are Not tagged  (neither C-Tagged nor S-Tagged).
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:TX_UNTAGGED_FRMS_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_UNTAGGED_FRMS_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,41)

/** 
 * \brief
 * The number of frames transmitted without C-Tag and S-Tag information.
 *
 * \details 
 * Field: ::VTSS_ASM_TX_UNTAGGED_FRMS_CNT . TX_UNTAGGED_FRMS_CNT
 */
#define  VTSS_F_ASM_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_ASM_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_ASM_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Rx Symbol Carrier Error Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_SYMBOL_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_SYMBOL_ERR_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,42)

/** 
 * \brief
 * PMAC - The number of frames received with one or more symbol errors.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_SYMBOL_ERR_CNT . PMAC_RX_SYMBOL_ERR_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT(x)  (x)


/** 
 * \brief Rx Pause Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_PAUSE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_PAUSE_CNT(gi)       VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,43)

/** 
 * \brief
 * PMAC - Number of pause control frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_PAUSE_CNT . PMAC_RX_PAUSE_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT(x)  (x)


/** 
 * \brief Rx Control Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_UNSUP_OPCODE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_UNSUP_OPCODE_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,44)

/** 
 * \brief
 * PMAC - Number of control frames with unsupported opcode received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_UNSUP_OPCODE_CNT . PMAC_RX_UNSUP_OPCODE_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT(x)  (x)


/** 
 * \brief Rx OK Byte Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_OK_BYTES_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_OK_BYTES_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,45)

/** 
 * \brief
 * PMAC - The number of received bytes in good frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_OK_BYTES_CNT . PMAC_RX_OK_BYTES_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Bad Byte Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_BAD_BYTES_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_BAD_BYTES_CNT(gi)   VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,46)

/** 
 * \brief
 * PMAC - The number of received bytes in bad frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_BAD_BYTES_CNT . PMAC_RX_BAD_BYTES_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Unicast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_UC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_UC_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,47)

/** 
 * \brief
 * PMAC - The number of good unicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_UC_CNT . PMAC_RX_UC_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT(x)  (x)


/** 
 * \brief Rx Multicast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_MC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_MC_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,48)

/** 
 * \brief
 * PMAC - The number of good multicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_MC_CNT . PMAC_RX_MC_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT(x)  (x)


/** 
 * \brief Rx Broadcast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_BC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_BC_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,49)

/** 
 * \brief
 * PMAC - The number of good broadcast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_BC_CNT . PMAC_RX_BC_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT(x)  (x)


/** 
 * \brief Rx CRC Error Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_CRC_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_CRC_ERR_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,50)

/** 
 * \brief
 * PMAC - The number of frames received with CRC error only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_CRC_ERR_CNT . PMAC_RX_CRC_ERR_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (valid frame format)
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_UNDERSIZE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_UNDERSIZE_CNT(gi)   VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,51)

/** 
 * \brief
 * PMAC - The number of undersize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_UNDERSIZE_CNT . PMAC_RX_UNDERSIZE_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (CRC error)
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_FRAGMENTS_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_FRAGMENTS_CNT(gi)   VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,52)

/** 
 * \brief
 * PMAC - The number of undersize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_FRAGMENTS_CNT . PMAC_RX_FRAGMENTS_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT(x)  (x)


/** 
 * \brief Rx In-range Length Error Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_IN_RANGE_LEN_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_IN_RANGE_LEN_ERR_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,53)

/** 
 * \brief
 * PMAC - The number of frames with legal length field that does not match
 * length of MAC client data.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_IN_RANGE_LEN_ERR_CNT . PMAC_RX_IN_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Out-Of-Range Length Error Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,54)

/** 
 * \brief
 * PMAC - The number of frames with illegal length field (frames using type
 * field are not counted here).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT . PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Oversize Counter (valid frame format)
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_OVERSIZE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_OVERSIZE_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,55)

/** 
 * \brief
 * PMAC - The number of oversize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_OVERSIZE_CNT . PMAC_RX_OVERSIZE_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Jabbers Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_JABBERS_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_JABBERS_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,56)

/** 
 * \brief
 * PMAC - The number of oversize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_JABBERS_CNT . PMAC_RX_JABBERS_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT(x)  (x)


/** 
 * \brief Rx 64 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_SIZE64_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_SIZE64_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,57)

/** 
 * \brief
 * PMAC - The number of 64 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_SIZE64_CNT . PMAC_RX_SIZE64_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT(x)  (x)


/** 
 * \brief Rx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_SIZE65TO127_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_SIZE65TO127_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,58)

/** 
 * \brief
 * PMAC - The number of 65 to 127 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_SIZE65TO127_CNT . PMAC_RX_SIZE65TO127_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Rx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_SIZE128TO255_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_SIZE128TO255_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,59)

/** 
 * \brief
 * PMAC - The number of 128 to 255 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_SIZE128TO255_CNT . PMAC_RX_SIZE128TO255_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Rx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_SIZE256TO511_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_SIZE256TO511_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,60)

/** 
 * \brief
 * PMAC - The number of 256 to 511 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_SIZE256TO511_CNT . PMAC_RX_SIZE256TO511_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Rx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_SIZE512TO1023_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_SIZE512TO1023_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,61)

/** 
 * \brief
 * PMAC - The number of 512 to 1023 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_SIZE512TO1023_CNT . PMAC_RX_SIZE512TO1023_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Rx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_SIZE1024TO1518_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_SIZE1024TO1518_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,62)

/** 
 * \brief
 * PMAC - The number of 1024 to 1518 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_SIZE1024TO1518_CNT . PMAC_RX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Rx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_SIZE1519TOMAX_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_SIZE1519TOMAX_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,63)

/** 
 * \brief
 * PMAC - The number of frames received longer than 1518 bytes and not
 * longer than Maximum Length Register (Maximum Length Register + 4 if the
 * frame is VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_SIZE1519TOMAX_CNT . PMAC_RX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Tx Pause Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_PAUSE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_PAUSE_CNT(gi)       VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,64)

/** 
 * \brief
 * PMAC - The number of pause control frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_PAUSE_CNT . PMAC_TX_PAUSE_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT(x)  (x)


/** 
 * \brief Tx OK Byte Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_OK_BYTES_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_OK_BYTES_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,65)

/** 
 * \brief
 * PMAC - The number of bytes transmitted successfully.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_OK_BYTES_CNT . PMAC_TX_OK_BYTES_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT(x)  (x)


/** 
 * \brief Tx Unicast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_UC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_UC_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,66)

/** 
 * \brief
 * PMAC - The number of unicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_UC_CNT . PMAC_TX_UC_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT(x)  (x)


/** 
 * \brief Tx Multicast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_MC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_MC_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,67)

/** 
 * \brief
 * PMAC - The number of multicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_MC_CNT . PMAC_TX_MC_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT(x)  (x)


/** 
 * \brief Tx Broadcast Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_BC_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_BC_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,68)

/** 
 * \brief
 * PMAC - The number of broadcast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_BC_CNT . PMAC_TX_BC_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT(x)  (x)


/** 
 * \brief Tx 64 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_SIZE64_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_SIZE64_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,69)

/** 
 * \brief
 * PMAC - The number of 64 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_SIZE64_CNT . PMAC_TX_SIZE64_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT(x)  (x)


/** 
 * \brief Tx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_SIZE65TO127_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_SIZE65TO127_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,70)

/** 
 * \brief
 * PMAC - The number of 65 to 127 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_SIZE65TO127_CNT . PMAC_TX_SIZE65TO127_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Tx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_SIZE128TO255_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_SIZE128TO255_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,71)

/** 
 * \brief
 * PMAC - The number of 128 to 255 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_SIZE128TO255_CNT . PMAC_TX_SIZE128TO255_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Tx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_SIZE256TO511_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_SIZE256TO511_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,72)

/** 
 * \brief
 * PMAC - The number of 256 to 511 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_SIZE256TO511_CNT . PMAC_TX_SIZE256TO511_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Tx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_SIZE512TO1023_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_SIZE512TO1023_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,73)

/** 
 * \brief
 * PMAC - The number of 512 to 1023 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_SIZE512TO1023_CNT . PMAC_TX_SIZE512TO1023_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Tx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_SIZE1024TO1518_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_SIZE1024TO1518_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,74)

/** 
 * \brief
 * PMAC - The number of 1024 to 1518 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_SIZE1024TO1518_CNT . PMAC_TX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Tx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_SIZE1519TOMAX_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_SIZE1519TOMAX_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,75)

/** 
 * \brief
 * PMAC - The number of frames transmitted longer than 1518 bytes and not
 * longer than Maximum Length Register (Maximum Length Register + 4 if the
 * frame is VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_SIZE1519TOMAX_CNT . PMAC_TX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Counter to track the dribble-nibble (extra nibble) errors in frames.
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_ALIGNMENT_LOST_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_ALIGNMENT_LOST_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,76)

/** 
 * \brief
 * PMAC - The number of frames received with Alignment (dribble-nibble)
 * error.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_ALIGNMENT_LOST_CNT . PMAC_RX_ALIGNMENT_LOST_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT(x)  (x)
#define  VTSS_M_ASM_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT     0xffffffff
#define  VTSS_X_ASM_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT(x)  (x)


/** 
 * \brief Counts Pframes that are with assembly error .
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:MM_RX_ASSEMBLY_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_MM_RX_ASSEMBLY_ERR_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,77)

/** 
 * \brief
 * MAC MERGE - The number of Pframes received with aseembly error.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_MM_RX_ASSEMBLY_ERR_CNT . MM_RX_ASSEMBLY_ERR_CNT
 */
#define  VTSS_F_ASM_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT(x)  (x)


/** 
 * \brief Counts Pframes that are with SMD error .
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:MM_RX_SMD_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_MM_RX_SMD_ERR_CNT(gi)       VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,78)

/** 
 * \brief
 * MAC MERGE - The number of Pframe fragaments rejected die to unknown SMD
 * values or arrving with SMD-C when no pframe in progress  .
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_MM_RX_SMD_ERR_CNT . MM_RX_SMD_ERR_CNT
 */
#define  VTSS_F_ASM_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT(x)  (x)


/** 
 * \brief Counts Pframes that are successfully  re-assembled and sent to PMAC .
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:MM_RX_ASSEMBLY_OK_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_MM_RX_ASSEMBLY_OK_CNT(gi)   VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,79)

/** 
 * \brief
 * MAC MERGE - The number of Pframes received whitch are successfully
 * reassembled .
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_MM_RX_ASSEMBLY_OK_CNT . MM_RX_ASSEMBLY_OK_CNT
 */
#define  VTSS_F_ASM_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT(x)  (x)
#define  VTSS_M_ASM_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT     0xffffffff
#define  VTSS_X_ASM_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT(x)  (x)


/** 
 * \brief Counts Pframes which are mPackets (fragments) due to preemption.
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:MM_RX_MERGE_FRAG_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_MM_RX_MERGE_FRAG_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,80)

/** 
 * \brief
 * MAC MERGE - The number of Pframes received whitch are mPackets
 * (Fragments) due to preemption .
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_MM_RX_MERGE_FRAG_CNT . MM_RX_MERGE_FRAG_CNT
 */
#define  VTSS_F_ASM_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT(x)  (x)
#define  VTSS_M_ASM_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT     0xffffffff
#define  VTSS_X_ASM_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT(x)  (x)


/** 
 * \brief Counts pframe fragment sent when preemption enabled .
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:MM_TX_PFRAGMENT_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_MM_TX_PFRAGMENT_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,81)

/** 
 * \brief
 * MAC MERGE - The number of Pframe fragments sent when preemption enabled
 * .
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_MM_TX_PFRAGMENT_CNT . MM_TX_PFRAGMENT_CNT
 */
#define  VTSS_F_ASM_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT(x)  (x)
#define  VTSS_M_ASM_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT     0xffffffff
#define  VTSS_X_ASM_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT(x)  (x)


/** 
 * \brief Tx Multi Collision Counter
 *
 * \details
 * Counter collecting the number of frames transmitted without errors after
 * multiple collisions.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_MULTI_COLL_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_MULTI_COLL_CNT(gi)       VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,82)

/** 
 * \brief
 * The number of frames transmitted without errors after multiple
 * collisions.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_MULTI_COLL_CNT . TX_MULTI_COLL_CNT
 */
#define  VTSS_F_ASM_TX_MULTI_COLL_CNT_TX_MULTI_COLL_CNT(x)  (x)
#define  VTSS_M_ASM_TX_MULTI_COLL_CNT_TX_MULTI_COLL_CNT     0xffffffff
#define  VTSS_X_ASM_TX_MULTI_COLL_CNT_TX_MULTI_COLL_CNT(x)  (x)


/** 
 * \brief Tx Late Collision Counter
 *
 * \details
 * Counter collecting the number of late collisions.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_LATE_COLL_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_LATE_COLL_CNT(gi)        VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,83)

/** 
 * \brief
 * The number of late collisions detected.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_LATE_COLL_CNT . TX_LATE_COLL_CNT
 */
#define  VTSS_F_ASM_TX_LATE_COLL_CNT_TX_LATE_COLL_CNT(x)  (x)
#define  VTSS_M_ASM_TX_LATE_COLL_CNT_TX_LATE_COLL_CNT     0xffffffff
#define  VTSS_X_ASM_TX_LATE_COLL_CNT_TX_LATE_COLL_CNT(x)  (x)


/** 
 * \brief Tx Excessive Collision Counter
 *
 * \details
 * Counter collecting the number of frames due to excessive collisions.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_XCOLL_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_XCOLL_CNT(gi)            VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,84)

/** 
 * \brief
 * The number of frames lost due to excessive collisions.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_XCOLL_CNT . TX_XCOLL_CNT
 */
#define  VTSS_F_ASM_TX_XCOLL_CNT_TX_XCOLL_CNT(x)  (x)
#define  VTSS_M_ASM_TX_XCOLL_CNT_TX_XCOLL_CNT     0xffffffff
#define  VTSS_X_ASM_TX_XCOLL_CNT_TX_XCOLL_CNT(x)  (x)


/** 
 * \brief Tx First Defer Counter
 *
 * \details
 * Counter collecting the number of frames being deferred on first
 * transmission attempt.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_DEFER_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_DEFER_CNT(gi)            VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,85)

/** 
 * \brief
 * The number of frames being deferred on first transmission attempt. Note:
 * This counter always counts when a defer event is present, even when it
 * is an excessive defer (TX_XDEFER_CNT).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_DEFER_CNT . TX_DEFER_CNT
 */
#define  VTSS_F_ASM_TX_DEFER_CNT_TX_DEFER_CNT(x)  (x)
#define  VTSS_M_ASM_TX_DEFER_CNT_TX_DEFER_CNT     0xffffffff
#define  VTSS_X_ASM_TX_DEFER_CNT_TX_DEFER_CNT(x)  (x)


/** 
 * \brief Tx Excessive Defer Counter
 *
 * \details
 * Counter collecting the number of frames sent with excessive deferral.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_XDEFER_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_XDEFER_CNT(gi)           VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,86)

/** 
 * \brief
 * The number of frames sent with excessive deferral.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_XDEFER_CNT . TX_XDEFER_CNT
 */
#define  VTSS_F_ASM_TX_XDEFER_CNT_TX_XDEFER_CNT(x)  (x)
#define  VTSS_M_ASM_TX_XDEFER_CNT_TX_XDEFER_CNT     0xffffffff
#define  VTSS_X_ASM_TX_XDEFER_CNT_TX_XDEFER_CNT(x)  (x)


/** 
 * \brief Tx 1 Backoff Counter
 *
 * \details
 * Counter collecting the number of frames sent successfully after 1
 * backoff/collision.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_BACKOFF1_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_BACKOFF1_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,87)

/** 
 * \brief
 * Number of frames sent successfully after 1 backoff/collision.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_BACKOFF1_CNT . TX_BACKOFF1_CNT
 */
#define  VTSS_F_ASM_TX_BACKOFF1_CNT_TX_BACKOFF1_CNT(x)  (x)
#define  VTSS_M_ASM_TX_BACKOFF1_CNT_TX_BACKOFF1_CNT     0xffffffff
#define  VTSS_X_ASM_TX_BACKOFF1_CNT_TX_BACKOFF1_CNT(x)  (x)


/** 
 * \brief Tx Carrier Sense Error Counter
 *
 * \details
 * Counter collecting the number of times CarrierSenseError is true at the
 * end of a frame transmission.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_CSENSE_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_CSENSE_CNT(gi)           VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,88)

/** 
 * \brief
 * The number of times CarrierSenseError is true at the end of a frame
 * transmission.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_CSENSE_CNT . TX_CSENSE_CNT
 */
#define  VTSS_F_ASM_TX_CSENSE_CNT_TX_CSENSE_CNT(x)  (x)
#define  VTSS_M_ASM_TX_CSENSE_CNT_TX_CSENSE_CNT     0xffffffff
#define  VTSS_X_ASM_TX_CSENSE_CNT_TX_CSENSE_CNT(x)  (x)


/** 
 * \brief MSB of RX in byte Counter
 *
 * \details
 * Register allowing to access the upper 4 bits of RX_IN_BYTE counter.
 * Note: When writing to RX_IN_BYTES counter RX_IN_BYTES_MSB_CNT has to be
 * written before RX_IN_BYTES_CNT is written. When reading RX_IN_BYTES
 * counter RX_IN_BYTES_CNT has to be read before RX_IN_BYTES_MSB_CNT is
 * read. Accessing both counters must not be interfered by other register
 * accesses.
 *
 * Register: \a ASM:DEV_STATISTICS:RX_IN_BYTES_MSB_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_IN_BYTES_MSB_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,89)

/** 
 * \brief
 * Upper 4 bits of RX_IN_BYTES_CNT.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_IN_BYTES_MSB_CNT . RX_IN_BYTES_MSB_CNT
 */
#define  VTSS_F_ASM_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ASM_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ASM_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief MSB of RX ok byte Counter
 *
 * \details
 * Register allowing to access the upper 4 bits of RX_IN_BYTE counter.
 * Note: When writing to RX_OK_BYTES counter RX_OK_BYTES_MSB_CNT has to be
 * written before RX_OK_BYTES_CNT is written. When reading RX_OK_BYTES
 * counter RX_OK_BYTES_CNT has to be read before RX_OK_BYTES_MSB_CNT is
 * read. Accessing both counters must not be interfered by other register
 * accesses.
 *
 * Register: \a ASM:DEV_STATISTICS:RX_OK_BYTES_MSB_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_OK_BYTES_MSB_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,90)

/** 
 * \brief
 * Upper 4 bits of RX_OK_BYTES_CNT.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_OK_BYTES_MSB_CNT . RX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_ASM_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ASM_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ASM_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief MSB of PMAC RX ok byte Counter
 *
 * \details
 * Register allowing to access the upper 4 bits of RX_IN_BYTE counter.
 * Note: When writing to RX_OK_BYTES counter RX_OK_BYTES_MSB_CNT has to be
 * written before RX_OK_BYTES_CNT is written. When reading RX_OK_BYTES
 * counter RX_OK_BYTES_CNT has to be read before RX_OK_BYTES_MSB_CNT is
 * read. Accessing both counters must not be interfered by other register
 * accesses.
 *
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_OK_BYTES_MSB_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_OK_BYTES_MSB_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,91)

/** 
 * \brief
 * Upper 4 bits of RX_OK_BYTES_CNT.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_OK_BYTES_MSB_CNT . PMAC_RX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ASM_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ASM_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief MSB of RX bad byte Counter
 *
 * \details
 * Register allowing to access the upper 4 bits of RX_IN_BYTE counter.
 * Note: When writing to RX_BAD_BYTES counter RX_BAD_BYTES_MSB_CNT has to
 * be written before RX_BAD_BYTES_CNT is written. When reading RX_BAD_BYTES
 * counter RX_BAD_BYTES_CNT has to be read before RX_BAD_BYTES_MSB_CNT is
 * read. Accessing both counters must not be interfered by other register
 * accesses.
 *
 * Register: \a ASM:DEV_STATISTICS:RX_BAD_BYTES_MSB_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_BAD_BYTES_MSB_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,92)

/** 
 * \brief
 * Upper 4 bits of RX_BAD_BYTES_CNT.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_BAD_BYTES_MSB_CNT . RX_BAD_BYTES_MSB_CNT
 */
#define  VTSS_F_ASM_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ASM_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ASM_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief MSB of PMAC RX bad byte Counter
 *
 * \details
 * Register allowing to access the upper 4 bits of PMAC RX_IN_BYTE counter.
 * Note: When writing to RX_BAD_BYTES counter RX_BAD_BYTES_MSB_CNT has to
 * be written before RX_BAD_BYTES_CNT is written. When reading RX_BAD_BYTES
 * counter RX_BAD_BYTES_CNT has to be read before RX_BAD_BYTES_MSB_CNT is
 * read. Accessing both counters must not be interfered by other register
 * accesses.
 *
 * Register: \a ASM:DEV_STATISTICS:PMAC_RX_BAD_BYTES_MSB_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_RX_BAD_BYTES_MSB_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,93)

/** 
 * \brief
 * Upper 4 bits of RX_BAD_BYTES_CNT.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_RX_BAD_BYTES_MSB_CNT . PMAC_RX_BAD_BYTES_MSB_CNT
 */
#define  VTSS_F_ASM_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ASM_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ASM_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief MSB of TX out byte Counter
 *
 * \details
 * Register allowing to access the upper 4 bits of RX_IN_BYTE counter.
 * Note: When writing to TX_OUT_BYTES counter TX_OUT_BYTES_MSB_CNT has to
 * be written before TX_OUT_BYTES_CNT is written. When reading TX_OUT_BYTES
 * counter TX_OUT_BYTES_CNT has to be read before TX_OUT_BYTES_MSB_CNT is
 * read. Accessing both counters must not be interfered by other register
 * accesses.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_OUT_BYTES_MSB_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_OUT_BYTES_MSB_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,94)

/** 
 * \brief
 * Upper 4 bits of TX_OUT_BYTES_CNT.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_OUT_BYTES_MSB_CNT . TX_OUT_BYTES_MSB_CNT
 */
#define  VTSS_F_ASM_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ASM_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ASM_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief MSB of TX ok byte Counter
 *
 * \details
 * Register allowing to access the upper 4 bits of TX_OK_BYTES counter.
 * Note: When writing to TX_OK_BYTES counter TX_OK_BYTES_MSB_CNT has to be
 * written before TX_OK_BYTES_CNT is written. When reading TX_OK_BYTES
 * counter TX_OK_BYTES_CNT has to be read before TX_OK_BYTES_MSB_CNT is
 * read. Accessing both counters must not be interfered by other register
 * accesses.
 *
 * Register: \a ASM:DEV_STATISTICS:TX_OK_BYTES_MSB_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_TX_OK_BYTES_MSB_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,95)

/** 
 * \brief
 * Upper 4 bits of TX_OK_BYTES_CNT.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_TX_OK_BYTES_MSB_CNT . TX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_ASM_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ASM_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ASM_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief MSB of PMAC TX ok byte Counter
 *
 * \details
 * Register allowing to access the upper 4 bits of TX_OK_BYTES counter.
 * Note: When writing to TX_OK_BYTES counter TX_OK_BYTES_MSB_CNT has to be
 * written before TX_OK_BYTES_CNT is written. When reading TX_OK_BYTES
 * counter TX_OK_BYTES_CNT has to be read before TX_OK_BYTES_MSB_CNT is
 * read. Accessing both counters must not be interfered by other register
 * accesses.
 *
 * Register: \a ASM:DEV_STATISTICS:PMAC_TX_OK_BYTES_MSB_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_PMAC_TX_OK_BYTES_MSB_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,96)

/** 
 * \brief
 * Upper 4 bits of PMAC TX_OK_BYTES_CNT.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_PMAC_TX_OK_BYTES_MSB_CNT . PMAC_TX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_ASM_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ASM_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ASM_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Counter to track the PCS's Sync-lost error
 *
 * \details
 * Register: \a ASM:DEV_STATISTICS:RX_SYNC_LOST_ERR_CNT
 *
 * @param gi Replicator: x_NUM_DEVS_PER_STATS_BLOCK (??), 0-64
 */
#define VTSS_ASM_RX_SYNC_LOST_ERR_CNT(gi)    VTSS_IOREG_IX(VTSS_TO_ASM,0x0,gi,128,0,97)

/** 
 * \brief
 * Counter to track the PCS's Sync-lost error
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_ASM_RX_SYNC_LOST_ERR_CNT . RX_SYNC_LOST_ERR_CNT
 */
#define  VTSS_F_ASM_RX_SYNC_LOST_ERR_CNT_RX_SYNC_LOST_ERR_CNT(x)  (x)
#define  VTSS_M_ASM_RX_SYNC_LOST_ERR_CNT_RX_SYNC_LOST_ERR_CNT     0xffffffff
#define  VTSS_X_ASM_RX_SYNC_LOST_ERR_CNT_RX_SYNC_LOST_ERR_CNT(x)  (x)

/**
 * Register Group: \a ASM:CFG
 *
 * Assembler Configuration Registers
 */


/** 
 * \brief Statistics counter configuration
 *
 * \details
 * Register that contains the bitgroups to configure/control the statistics
 * counters.
 *
 * Register: \a ASM:CFG:STAT_CFG
 */
#define VTSS_ASM_STAT_CFG                    VTSS_IOREG(VTSS_TO_ASM,0x2080)

/** 
 * \brief
 * Setting of this bit initiates the clearing of all statistics counter.
 *
 * \details 
 * '0': No action
 * '1': Stat cnt clr (Bit is automatically cleared)
 *
 * Field: ::VTSS_ASM_STAT_CFG . STAT_CNT_CLR_SHOT
 */
#define  VTSS_F_ASM_STAT_CFG_STAT_CNT_CLR_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_STAT_CFG_STAT_CNT_CLR_SHOT  VTSS_BIT(0)
#define  VTSS_X_ASM_STAT_CFG_STAT_CNT_CLR_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief MAC Address Configuration Register (MSB)
 *
 * \details
 * Register: \a ASM:CFG:MAC_ADDR_HIGH_CFG
 *
 * @param ri Replicator: x_NUM_ASM_PORTS (??), 0-66
 */
#define VTSS_ASM_MAC_ADDR_HIGH_CFG(ri)       VTSS_IOREG(VTSS_TO_ASM,0x2081 + (ri))

/** 
 * \brief
 * Upper 24 bits of MAC address.The MAC address is used when filtering
 * incoming Pause Control Frames - i.e. when the ASM determines whether or
 * not a pause value must be passed to the DSM.
 *
 * \details 
 * The resulting MAC address of a device is determined as:
 * MAC_ADDR_HIGH  & MAC_ADDR_LOW.
 *
 * Field: ::VTSS_ASM_MAC_ADDR_HIGH_CFG . MAC_ADDR_HIGH
 */
#define  VTSS_F_ASM_MAC_ADDR_HIGH_CFG_MAC_ADDR_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_ASM_MAC_ADDR_HIGH_CFG_MAC_ADDR_HIGH     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_ASM_MAC_ADDR_HIGH_CFG_MAC_ADDR_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief MAC Address Configuration Register (LSB)
 *
 * \details
 * Register: \a ASM:CFG:MAC_ADDR_LOW_CFG
 *
 * @param ri Replicator: x_NUM_ASM_PORTS (??), 0-66
 */
#define VTSS_ASM_MAC_ADDR_LOW_CFG(ri)        VTSS_IOREG(VTSS_TO_ASM,0x20c4 + (ri))

/** 
 * \brief
 * Lower 24 bits of MAC address.The MAC address is used when filtering
 * incoming Pause Control Frames - i.e. when the ASM determines whether or
 * not a pause value must be passed to the DSM.
 *
 * \details 
 * The resulting MAC address of a device is determined as:
 * MAC_ADDR_HIGH  & MAC_ADDR_LOW.

 *
 * Field: ::VTSS_ASM_MAC_ADDR_LOW_CFG . MAC_ADDR_LOW
 */
#define  VTSS_F_ASM_MAC_ADDR_LOW_CFG_MAC_ADDR_LOW(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_ASM_MAC_ADDR_LOW_CFG_MAC_ADDR_LOW     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_ASM_MAC_ADDR_LOW_CFG_MAC_ADDR_LOW(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief Port configuration
 *
 * \details
 * This register holds port configuration bit groups
 *
 * Register: \a ASM:CFG:PORT_CFG
 *
 * @param ri Replicator: x_NUM_ASM_PORTS (??), 0-66
 */
#define VTSS_ASM_PORT_CFG(ri)                VTSS_IOREG(VTSS_TO_ASM,0x2107 + (ri))

/** 
 * \brief
 * Disables updates of the ASM related counters for the common statistics
 * counter system that is used for DEV1G/DEV2G5 devices
 * (ASM:DEV_STATISTICS:RX_PAUSE_CNT and
 * ASM:DEV_STATISTICS:RX_UNSUP_OPCODE_CNT).Set this when the port utilizes
 * a DEV10G device as it handles the statistics locally in the device
 * (Statistics counters in DEV10G:DEV_STATISTICS_*:*).
 *
 * \details 
 * Field: ::VTSS_ASM_PORT_CFG . CSC_STAT_DIS
 */
#define  VTSS_F_ASM_PORT_CFG_CSC_STAT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ASM_PORT_CFG_CSC_STAT_DIS     VTSS_BIT(12)
#define  VTSS_X_ASM_PORT_CFG_CSC_STAT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * If this field is set the ASM removes the first 4 bytes of the payload
 * and inserts it into the HIH field of the IFH.
 *
 * \details 
 * Field: ::VTSS_ASM_PORT_CFG . HIH_AFTER_PREAMBLE_ENA
 */
#define  VTSS_F_ASM_PORT_CFG_HIH_AFTER_PREAMBLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ASM_PORT_CFG_HIH_AFTER_PREAMBLE_ENA  VTSS_BIT(11)
#define  VTSS_X_ASM_PORT_CFG_HIH_AFTER_PREAMBLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * If this field is set the ASM will ignore any abort indications received
 * on the TAXI interface for the port.
 *
 * \details 
 * Field: ::VTSS_ASM_PORT_CFG . IGN_TAXI_ABORT_ENA
 */
#define  VTSS_F_ASM_PORT_CFG_IGN_TAXI_ABORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ASM_PORT_CFG_IGN_TAXI_ABORT_ENA  VTSS_BIT(10)
#define  VTSS_X_ASM_PORT_CFG_IGN_TAXI_ABORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * If this field is set the ASM does not expect the incoming frame data to
 * have a preamble prepended.
 *
 * \details 
 * Field: ::VTSS_ASM_PORT_CFG . NO_PREAMBLE_ENA
 */
#define  VTSS_F_ASM_PORT_CFG_NO_PREAMBLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ASM_PORT_CFG_NO_PREAMBLE_ENA  VTSS_BIT(9)
#define  VTSS_X_ASM_PORT_CFG_NO_PREAMBLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * If this field is set the ASM will not store the first 8 bytes from the
 * packet. This must be enabled when injecting with IFH without prefix from
 * an external CPU (INJ_FORMAT_CFG=1).
 *
 * \details 
 * Field: ::VTSS_ASM_PORT_CFG . SKIP_PREAMBLE_ENA
 */
#define  VTSS_F_ASM_PORT_CFG_SKIP_PREAMBLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ASM_PORT_CFG_SKIP_PREAMBLE_ENA  VTSS_BIT(8)
#define  VTSS_X_ASM_PORT_CFG_SKIP_PREAMBLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * This field determines if the ASM must abort mark frames that become
 * older than 16-24 ms before an EOF is received.
 *
 * \details 
 * '0': Aging enabled.
 * '1': Aging disabled.
 *
 * Field: ::VTSS_ASM_PORT_CFG . FRM_AGING_DIS
 */
#define  VTSS_F_ASM_PORT_CFG_FRM_AGING_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ASM_PORT_CFG_FRM_AGING_DIS    VTSS_BIT(7)
#define  VTSS_X_ASM_PORT_CFG_FRM_AGING_DIS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This field determines if the ASM must zero-pad Ethernet frames that are
 * less than 64 bytes.
 *
 * \details 
 * '0': Padding is disabled. Frames that are less than 64 bytes and have
 * not been abort marked are passed to the ANA block 'as is'. Frames that
 * are less than 64 bytes and have been abort marked are normally discarded
 * silently by the ASM.
 * '1': Padding is enabled. If the resulting frame size will be less than
 * 64 bytes, the frame is zero-padded, so that the resulting frame size is
 * 64 bytes.
 *
 * Field: ::VTSS_ASM_PORT_CFG . PAD_ENA
 */
#define  VTSS_F_ASM_PORT_CFG_PAD_ENA(x)       VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ASM_PORT_CFG_PAD_ENA          VTSS_BIT(6)
#define  VTSS_X_ASM_PORT_CFG_PAD_ENA(x)       VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Configure discard behavior depending on matching result of the selected
 * injection format in ASM:CFG:PORT_CFG.INJ_FORMAT_CFG. If a non-matching
 * frame is not discarded it will be forwarded as a normal frame.This
 * setting is only valid for injection formats with short or long prefix.
 *
 * \details 
 * 0: Discard none
 * 1: Discard frames with wrong injection format
 * 2: Discard frames with correct injection format
 *
 * Field: ::VTSS_ASM_PORT_CFG . INJ_DISCARD_CFG
 */
#define  VTSS_F_ASM_PORT_CFG_INJ_DISCARD_CFG(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ASM_PORT_CFG_INJ_DISCARD_CFG     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_ASM_PORT_CFG_INJ_DISCARD_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Set the mode for the format of incoming frames. Four different modes can
 * be selected: - Normal mode (No IFH) - IFH without prefix - IFH with
 * short prefix - IFH with long prefixIf one of the IFH modes are selected
 * incoming frames are expected to contain the selected prefix followed by
 * an IFH as the first part of the frame. Frames are forwarded based on the
 * contents in the IFH instead of normal forwarding. The prefix will be
 * stripped from the frame before it is forwarded.Three different prefix
 * modes are supported:- No prefix.- IFH short prefix:. any DMAC, any SMAC,
 * EtherType=0x8880, payload=0x000B- IFH long prefix: any DMAC, any SMAC,
 * VLAN Tag, EtherType=0x8880, payload=0x000B.The VLAN tag to compare
 * against is set in ASM:CFG:INJ_VLAN_CFG. Only the VID and TPID fields of
 * the VLAN Tag will be compared.If one of the IFH short or long prefix
 * modes are selected and a frame with non-matching prefix is received the
 * frame can either be forwarded as a normal frame or discarded depending
 * on the setting of ASM:CFG:PORT_CFG.INJ_DISCARD_CFG.In the IFH short/long
 * prefix modes, if the incoming frame's format does not comply with the
 * prefix, then ASM:PORT_STATUS:PORT_STICKY.IFH_PREFIX_ERR_STICKY is set.
 *
 * \details 
 * 0: Normal mode (No IFH)
 * 1: IFH without prefix
 * 2: IFH with short prefix
 * 3: IFH with long prefix
 *
 * Field: ::VTSS_ASM_PORT_CFG . INJ_FORMAT_CFG
 */
#define  VTSS_F_ASM_PORT_CFG_INJ_FORMAT_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ASM_PORT_CFG_INJ_FORMAT_CFG     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ASM_PORT_CFG_INJ_FORMAT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * This bit defines if the ASM must be VStaX2 aware or not. If VStaX2
 * awareness is enabled and a frame holds a VStaX2 header following the
 * SMAC address, this VStaX2 header is removed from the frame and placed in
 * the IFH and the vstax_avail and update_fcs fields in the IFH will be
 * set, so that the frame FCS is recalculated in the egress direction.If
 * VStaX2 awareness is disabled or a frame does not hold a VStaX2 header,
 * no bytes will be removed from the frame and the vstax_hdr, vstax_avail
 * and fcs_update fields in the IFH will be cleared.When VStaX2 awareness
 * is enabled INJ_FORMAT_CFG must be set to 0
 *
 * \details 
 * 0: VStaX2 awareness is disabled. 
 * 1: VStaX2 awareness is enabled.
 *
 * Field: ::VTSS_ASM_PORT_CFG . VSTAX2_AWR_ENA
 */
#define  VTSS_F_ASM_PORT_CFG_VSTAX2_AWR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ASM_PORT_CFG_VSTAX2_AWR_ENA   VTSS_BIT(1)
#define  VTSS_X_ASM_PORT_CFG_VSTAX2_AWR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Flush P-frames from this port.
 *
 * \details 
 * Field: ::VTSS_ASM_PORT_CFG . PFRM_FLUSH
 */
#define  VTSS_F_ASM_PORT_CFG_PFRM_FLUSH(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_PORT_CFG_PFRM_FLUSH       VTSS_BIT(0)
#define  VTSS_X_ASM_PORT_CFG_PFRM_FLUSH(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Holds DEVCPU specific Flow Control configuration signals
 *
 * \details
 * Register: \a ASM:CFG:CPU_FC_CFG
 */
#define VTSS_ASM_CPU_FC_CFG                  VTSS_IOREG(VTSS_TO_ASM,0x214a)

/** 
 * \brief
 * This field determines the ASM FIFO fill level required for the ASM to
 * activate FC. The fill level is given by the number of complete cells in
 * the FIFO that are ready to be passed to the ANA block.
 *
 * \details 
 * 0: Flow control is activated if the ASM FIFO of the DEVCPU holds 1 or
 * more complete cells.
 * 1: Flow control is activated if the ASM FIFO of the DEVCPU holds 2 or
 * more complete cells.
 * ---
 * X: Flow control is activated if the ASM FIFO of the DEVCPU holds X+1 or
 * more complete cells.
 *
 * Field: ::VTSS_ASM_CPU_FC_CFG . CPU_FC_WM
 */
#define  VTSS_F_ASM_CPU_FC_CFG_CPU_FC_WM(x)   VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_ASM_CPU_FC_CFG_CPU_FC_WM      VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_ASM_CPU_FC_CFG_CPU_FC_WM(x)   VTSS_EXTRACT_BITFIELD(x,1,2)


/** 
 * \brief Holds configuration related to Pause frame detection.
 *
 * \details
 * This register control whether pause and control frames should be
 * forwarded or terminated at ingress.
 *
 * Register: \a ASM:CFG:PAUSE_CFG
 *
 * @param ri Replicator: x_NUM_ASM_PORTS (??), 0-66
 */
#define VTSS_ASM_PAUSE_CFG(ri)               VTSS_IOREG(VTSS_TO_ASM,0x214b + (ri))

/** 
 * \brief
 * This field indicates whether or not the ASM must discard a valid Pause
 * frame to the IQS by asserting the abort signal.One configuration bit is
 * defined for each port.
 *
 * \details 
 * '0': The ASM must not discard valid Pause frames.
 * '1': The ASM must discard valid Pause frames to the IQS by asserting the
 * abort signal, but the Pause value must still be used to stall the egress
 * data flow.
 *
 * Field: ::VTSS_ASM_PAUSE_CFG . ABORT_PAUSE_ENA
 */
#define  VTSS_F_ASM_PAUSE_CFG_ABORT_PAUSE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_PAUSE_CFG_ABORT_PAUSE_ENA  VTSS_BIT(0)
#define  VTSS_X_ASM_PAUSE_CFG_ABORT_PAUSE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * This field indicates whether or not the ASM must discard Control frames
 * with type 0x8808 not being Pause frames, to the IQS by asserting the
 * abort signal.One configuration bit is defined for each port.
 *
 * \details 
 * '0': The ASM must not discard Control frames.
 * '1': The ASM must discard Control frames to the IQS by asserting the
 * abort signal.
 *
 * Field: ::VTSS_ASM_PAUSE_CFG . ABORT_CTRL_ENA
 */
#define  VTSS_F_ASM_PAUSE_CFG_ABORT_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ASM_PAUSE_CFG_ABORT_CTRL_ENA  VTSS_BIT(1)
#define  VTSS_X_ASM_PAUSE_CFG_ABORT_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief Configure custom VLAN tag for injection
 *
 * \details
 * Register: \a ASM:CFG:INJ_VLAN_CFG
 */
#define VTSS_ASM_INJ_VLAN_CFG                VTSS_IOREG(VTSS_TO_ASM,0x218e)

/** 
 * \brief
 * The VID used for VLAN tag matching when injection with long IFH prefix
 * is selected in ASM:CFG:PORT_CFG.INJ_FORMAT_CFG.
 *
 * \details 
 * Field: ::VTSS_ASM_INJ_VLAN_CFG . INJ_VID_CFG
 */
#define  VTSS_F_ASM_INJ_VLAN_CFG_INJ_VID_CFG(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_ASM_INJ_VLAN_CFG_INJ_VID_CFG     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_ASM_INJ_VLAN_CFG_INJ_VID_CFG(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/** 
 * \brief
 * The TPID used for VLAN tag matching when injection with long IFH prefix
 * is selected in ASM:CFG:PORT_CFG.INJ_FORMAT_CFG.
 *
 * \details 
 * Field: ::VTSS_ASM_INJ_VLAN_CFG . INJ_TPID_CFG
 */
#define  VTSS_F_ASM_INJ_VLAN_CFG_INJ_TPID_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ASM_INJ_VLAN_CFG_INJ_TPID_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ASM_INJ_VLAN_CFG_INJ_TPID_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Time tick configuration
 *
 * \details
 * Register: \a ASM:CFG:TIME_TICK_CFG
 */
#define VTSS_ASM_TIME_TICK_CFG               VTSS_IOREG(VTSS_TO_ASM,0x218f)

/** 
 * \brief
 * Counter value used to generate a tick every 16777216 ns used for ASM
 * aging logic.
 *
 * \details 
 * Set to the number of system clock cycles in 16777216 ns (flooring) - 1.
 * For example if the system clock period is 6.4 ns set TIME_TICK_VAL to
 * 16777216/6.4 - 1.
 *
 * Field: ::VTSS_ASM_TIME_TICK_CFG . TIME_TICK_VAL
 */
#define  VTSS_F_ASM_TIME_TICK_CFG_TIME_TICK_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,23)
#define  VTSS_M_ASM_TIME_TICK_CFG_TIME_TICK_VAL     VTSS_ENCODE_BITMASK(0,23)
#define  VTSS_X_ASM_TIME_TICK_CFG_TIME_TICK_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,23)

/**
 * Register Group: \a ASM:DBG
 *
 * Assembler Debug Registers
 */


/** 
 * \brief Miscellaneous debug configuration
 *
 * \details
 * This register holds miscellaneous configuration bit groups used for
 * debug
 *
 * Register: \a ASM:DBG:DBG_CFG
 */
#define VTSS_ASM_DBG_CFG                     VTSS_IOREG(VTSS_TO_ASM,0x2190)

/** 
 * \brief
 * If this fields is set to 1, cell cycles allocated for front ports, but
 * with no data available, will be given to the virtual device. Otherwise
 * the VD is only given the cycles set by the cell bus calendar.
 *
 * \details 
 * Field: ::VTSS_ASM_DBG_CFG . IDLE_TO_VD
 */
#define  VTSS_F_ASM_DBG_CFG_IDLE_TO_VD(x)     VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ASM_DBG_CFG_IDLE_TO_VD        VTSS_BIT(2)
#define  VTSS_X_ASM_DBG_CFG_IDLE_TO_VD(x)     VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This field indicates if a given ASM FIFO must be reset or not. Resetting
 * a FIFO does not affect the device status interface to the DSM.
 *
 * \details 
 * '0': The FIFO is NOT reset.
 * '1': The FIFO is reset and it will remain reset until FIFO_RST is
 * deasserted.
 *
 * Field: ::VTSS_ASM_DBG_CFG . FIFO_RST
 */
#define  VTSS_F_ASM_DBG_CFG_FIFO_RST(x)       VTSS_ENCODE_BITFIELD(x,3,9)
#define  VTSS_M_ASM_DBG_CFG_FIFO_RST          VTSS_ENCODE_BITMASK(3,9)
#define  VTSS_X_ASM_DBG_CFG_FIFO_RST(x)       VTSS_EXTRACT_BITFIELD(x,3,9)

/** 
 * \brief
 * This field can be used to disable the cell bus output of the ASM - i.e.
 * to configure the ASM to replace any data cells with IDLE cells. Data is
 * flushed from the ASM FIFO when the output is disabled.
 *
 * \details 
 * '0': Any data cells read from the ASM FIFO are passed to the ANA block.
 * '1': No data cells are passed to the ANA block. Only IDLE and REFRESH
 * cells will be transmitted. Data is still read from the ASM FIFO, even
 * though the cell bus interface has been disabled.
 *
 * Field: ::VTSS_ASM_DBG_CFG . CELL_BUS_DIS
 */
#define  VTSS_F_ASM_DBG_CFG_CELL_BUS_DIS(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ASM_DBG_CFG_CELL_BUS_DIS      VTSS_BIT(1)
#define  VTSS_X_ASM_DBG_CFG_CELL_BUS_DIS(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This field can be used to configure the ASM not to silently discard
 * frames that are aborted by a device within the first cell of a
 * frame.Note that enabling this feature may cause overflow in the ASM when
 * small fragments are received at the Taxi interface.
 *
 * \details 
 * '0': Frames are silently discarded by the ASM if it is aborted within
 * the first cell of the frame.
 * '1': No frames are silently discarded by the ASM
 *
 * Field: ::VTSS_ASM_DBG_CFG . ABORT_DIS
 */
#define  VTSS_F_ASM_DBG_CFG_ABORT_DIS(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_DBG_CFG_ABORT_DIS         VTSS_BIT(0)
#define  VTSS_X_ASM_DBG_CFG_ABORT_DIS(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Holds a number of sticky bits that are set if internal errors are detected.
 *
 * \details
 * Writing a '1' to a bit group clears that bit.
 *
 * Register: \a ASM:DBG:ERR_STICKY
 *
 * @param ri Replicator: x_NUM_OF_TAXI (??), 0-8
 */
#define VTSS_ASM_ERR_STICKY(ri)              VTSS_IOREG(VTSS_TO_ASM,0x2191 + (ri))

/** 
 * \brief
 * Cell words must not be granted a given Taxi more often than every 2nd
 * cell cycle. If the cell bus calendar causes 2 consequtive cell slots to
 * be allocated to the same Taxi bus, the last cell slot is ignored and a
 * sticky bit is asserted.
 *
 * \details 
 * '0': No cell slot calendar error detected.
 * '1': One or more cell slots have been ignored by ASM.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . CALENDAR_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_CALENDAR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ASM_ERR_STICKY_CALENDAR_STICKY  VTSS_BIT(7)
#define  VTSS_X_ASM_ERR_STICKY_CALENDAR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This sticky bit is set if a partial Taxi word (unused_bytes <> 0) is
 * received while EOF = 0.
 *
 * \details 
 * '0': No error detected in UNUSED_BYTES field ofTaxi word.
 * '1': One or more Taxi words have been received where the UNUSED_BYTES
 * field was different from 0 and EOP = 0.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . UNUSED_BYTES_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_UNUSED_BYTES_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ASM_ERR_STICKY_UNUSED_BYTES_STICKY  VTSS_BIT(6)
#define  VTSS_X_ASM_ERR_STICKY_UNUSED_BYTES_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * This sticky bit is set if the ASM passes a frame to the cell bus, which
 * is less than 64 bytes (before any padding is done, if enabled) - and has
 * not been aborted or abortion has been disabled.The padding configuration
 * does not affect this sticky bit.
 *
 * \details 
 * '0': No error detected.
 * '1': One or more frames have been passed to the cell bus, where the
 * frame size was less than 64 bytes.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . FRAGMENT_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_FRAGMENT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ASM_ERR_STICKY_FRAGMENT_STICKY  VTSS_BIT(5)
#define  VTSS_X_ASM_ERR_STICKY_FRAGMENT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This sticky bit is set if the ASM receives a Taxi word where SOF is
 * asserted and the previous valid Taxi word from that port did not hold an
 * EOF.
 *
 * \details 
 * '0': No missing EOF detected
 * '1': Missing EOF detected
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . MISSING_EOF_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_MISSING_EOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ASM_ERR_STICKY_MISSING_EOF_STICKY  VTSS_BIT(4)
#define  VTSS_X_ASM_ERR_STICKY_MISSING_EOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * This sticky bit is set if the ASM receives a Taxi word where ABORT is
 * asserted but EOF is not asserted.
 *
 * \details 
 * '0': No misaligned ABORT/EOF indications detected.
 * '1': Misaligned ABORT/EOF indications detected.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . INVLD_ABORT_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_INVLD_ABORT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ASM_ERR_STICKY_INVLD_ABORT_STICKY  VTSS_BIT(3)
#define  VTSS_X_ASM_ERR_STICKY_INVLD_ABORT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * This sticky bit is set if the ASM receives a Taxi word with SOF=0 and
 * the previous valid Taxi word from that port hold an EOF.
 *
 * \details 
 * '0': No missing EOF detected
 * '1': Missing EOF detected
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . MISSING_SOF_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_MISSING_SOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ASM_ERR_STICKY_MISSING_SOF_STICKY  VTSS_BIT(2)
#define  VTSS_X_ASM_ERR_STICKY_MISSING_SOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The ASM must assert a sticky bit if an overflow occurs in the main
 * statemachine.
 *
 * \details 
 * '0': No overflow has been detected in the main statemachine.
 * '1': An overflow has been detected in the main statemachine.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . MAIN_SM_INTRN_ERR_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_MAIN_SM_INTRN_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ASM_ERR_STICKY_MAIN_SM_INTRN_ERR_STICKY  VTSS_BIT(1)
#define  VTSS_X_ASM_ERR_STICKY_MAIN_SM_INTRN_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * The ASM must assert a sticky bit if an overflow occurs in the main
 * statemachine.
 *
 * \details 
 * '0': No overflow has been detected in the main statemachine.
 * '1': An overflow has been detected in the main statemachine.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . MAIN_SM_OFLW_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_MAIN_SM_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_ERR_STICKY_MAIN_SM_OFLW_STICKY  VTSS_BIT(0)
#define  VTSS_X_ASM_ERR_STICKY_MAIN_SM_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * The ASM must assert a sticky bit if an underflow occurs in the main
 * statemachine.
 *
 * \details 
 * '0': No underflow has been detected in the main statemachine.
 * '1': An underflow has been detected in the main statemachine.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_ERR_STICKY . MAIN_SM_UFLW_STICKY
 */
#define  VTSS_F_ASM_ERR_STICKY_MAIN_SM_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ASM_ERR_STICKY_MAIN_SM_UFLW_STICKY  VTSS_BIT(8)
#define  VTSS_X_ASM_ERR_STICKY_MAIN_SM_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/** 
 * \brief Register containing sticky bits for pre counter overflow
 *
 * \details
 * Register containing sticky bits for pre counter overflow
 *
 * Register: \a ASM:DBG:PRE_CNT_OFLW_STICKY
 */
#define VTSS_ASM_PRE_CNT_OFLW_STICKY         VTSS_IOREG(VTSS_TO_ASM,0x219a)

/** 
 * \brief
 * Will be set if one of the statistics pre counters for unsupported
 * control frames has an overflow.
 *
 * \details 
 * '0': An overflow in pre-counter has not occurred
 * '1': An overflow in pre-counter has occurred
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_PRE_CNT_OFLW_STICKY . UNSUP_OPCODE_PRE_CNT_OFLW_STICKY
 */
#define  VTSS_F_ASM_PRE_CNT_OFLW_STICKY_UNSUP_OPCODE_PRE_CNT_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ASM_PRE_CNT_OFLW_STICKY_UNSUP_OPCODE_PRE_CNT_OFLW_STICKY  VTSS_BIT(1)
#define  VTSS_X_ASM_PRE_CNT_OFLW_STICKY_UNSUP_OPCODE_PRE_CNT_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Will be set if one of the statistics pause frame pre counters has an
 * overflow.
 *
 * \details 
 * '0': An overflow in pre-counter has not occurred
 * '1': An overflow in pre-counter has occurred
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_PRE_CNT_OFLW_STICKY . PAUSE_FRM_PRE_CNT_OFLW_STICKY
 */
#define  VTSS_F_ASM_PRE_CNT_OFLW_STICKY_PAUSE_FRM_PRE_CNT_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_PRE_CNT_OFLW_STICKY_PAUSE_FRM_PRE_CNT_OFLW_STICKY  VTSS_BIT(0)
#define  VTSS_X_ASM_PRE_CNT_OFLW_STICKY_PAUSE_FRM_PRE_CNT_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Number of used cells in taxi buffer
 *
 * \details
 * Taxi buffer is shared between all devices on the same ring
 *
 * Register: \a ASM:DBG:CELLBUF_STAT
 *
 * @param ri Replicator: x_NUM_OF_TAXI (??), 0-8
 */
#define VTSS_ASM_CELLBUF_STAT(ri)            VTSS_IOREG(VTSS_TO_ASM,0x219b + (ri))

/** 
 * \brief
 * Field return number of currently used cell buffers for the taxi ring
 *
 * \details 
 * Field: ::VTSS_ASM_CELLBUF_STAT . CELLBUF_CNT
 */
#define  VTSS_F_ASM_CELLBUF_STAT_CELLBUF_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ASM_CELLBUF_STAT_CELLBUF_CNT     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ASM_CELLBUF_STAT_CELLBUF_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a ASM:PORT_STATUS
 *
 * Status for ASM ingress ports
 */


/** 
 * \brief ASM port sticky bits
 *
 * \details
 * This register holds all the sticky bits that exists for each port.
 *
 * Register: \a ASM:PORT_STATUS:PORT_STICKY
 *
 * @param ri Replicator: x_NUM_ASM_PORTS (??), 0-66
 */
#define VTSS_ASM_PORT_STICKY(ri)             VTSS_IOREG(VTSS_TO_ASM,0x21a4 + (ri))

/** 
 * \brief
 *  This field is set if the PORT_CFG.INJ_FORMAT_CFG field is set to one of
 * the IFH modes and the incoming frame's format does not comply with the
 * configured prefix.
 *
 * \details 
 * Field: ::VTSS_ASM_PORT_STICKY . IFH_PREFIX_ERR_STICKY
 */
#define  VTSS_F_ASM_PORT_STICKY_IFH_PREFIX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ASM_PORT_STICKY_IFH_PREFIX_ERR_STICKY  VTSS_BIT(1)
#define  VTSS_X_ASM_PORT_STICKY_IFH_PREFIX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This field indicates if one or more Ethernet frames have been discarded
 * due to aging.
 *
 * \details 
 * '0': No Ethernet frames have been discarded due to aging.
 * '1': One or more Ethernet frames have been discarded due to aging.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_ASM_PORT_STICKY . FRM_AGING_STICKY
 */
#define  VTSS_F_ASM_PORT_STICKY_FRM_AGING_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_PORT_STICKY_FRM_AGING_STICKY  VTSS_BIT(0)
#define  VTSS_X_ASM_PORT_STICKY_FRM_AGING_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ASM:PFC
 *
 * Priority-based flow control configuration
 */


/** 
 * \brief Priority-based flow control configuration
 *
 * \details
 * Register: \a ASM:PFC:PFC_CFG
 *
 * @param gi Replicator: x_NUM_ASM_PORTS (??), 0-66
 */
#define VTSS_ASM_PFC_CFG(gi)                 VTSS_IOREG_IX(VTSS_TO_ASM,0x2800,gi,16,0,0)

/** 
 * \brief
 * Enable PFC per priority. Bit n enables PFC on priority n.
 *
 * \details 
 * Field: ::VTSS_ASM_PFC_CFG . RX_PFC_ENA
 */
#define  VTSS_F_ASM_PFC_CFG_RX_PFC_ENA(x)     VTSS_ENCODE_BITFIELD(x,3,8)
#define  VTSS_M_ASM_PFC_CFG_RX_PFC_ENA        VTSS_ENCODE_BITMASK(3,8)
#define  VTSS_X_ASM_PFC_CFG_RX_PFC_ENA(x)     VTSS_EXTRACT_BITFIELD(x,3,8)

/** 
 * \brief
 * Configures the link speed. This is used to evaluate the time
 * specifications in incoming pause frames. 
 *
 * \details 
 * 0: 12000 Mbps
 * 1: 10000 Mbps
 * 2: 2500 Mbps
 * 3: 1000 Mbps
 * 4: 100 Mbps
 * 5: 10 Mbps
 * 6: 5000 Mbps
 * 7: Reserved
 *
 * Field: ::VTSS_ASM_PFC_CFG . FC_LINK_SPEED
 */
#define  VTSS_F_ASM_PFC_CFG_FC_LINK_SPEED(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ASM_PFC_CFG_FC_LINK_SPEED     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ASM_PFC_CFG_FC_LINK_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Current timer per priority
 *
 * \details
 * Register: \a ASM:PFC:PFC_TIMER
 *
 * @param gi Replicator: x_NUM_ASM_PORTS (??), 0-66
 * @param ri Replicator: x_PRIO_CNT (??), 0-7
 */
#define VTSS_ASM_PFC_TIMER(gi,ri)            VTSS_IOREG_IX(VTSS_TO_ASM,0x2800,gi,16,ri,1)

/** 
 * \brief
 * The current timer value per priority. Value >0 indicates that the
 * priority is paused.
 *
 * \details 
 * Unit is 1024 bit times.
 *
 * Field: ::VTSS_ASM_PFC_TIMER . PFC_TIMER_VAL
 */
#define  VTSS_F_ASM_PFC_TIMER_PFC_TIMER_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ASM_PFC_TIMER_PFC_TIMER_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ASM_PFC_TIMER_PFC_TIMER_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a ASM:PFC_TIMER_CFG
 *
 * Not documented
 */


/** 
 * \brief PFC timer max count per port speed
 *
 * \details
 * Register: \a ASM:PFC_TIMER_CFG:PFC_TIMER_MAX
 *
 * @param ri Register: PFC_TIMER_MAX (??), 0-6
 */
#define VTSS_ASM_PFC_TIMER_MAX(ri)           VTSS_IOREG(VTSS_TO_ASM,0x21e7 + (ri))

/** 
 * \brief
 * The PFC pause timer max value per port speed.Index 0: 25GIndex 1:
 * 10GIndex 2: 2G5Index 3: 1GIndex 4: 100MIndex 5: 10MIndex 6: 5G
 *
 * \details 
 * Set to the number of systen clock cycles in 512 bit times.
 * If set to 0 default values matching a system clock frequency of 625 MHz
 * will be used.
 *
 * Field: ::VTSS_ASM_PFC_TIMER_MAX . PFC_TIMER_MAX
 */
#define  VTSS_F_ASM_PFC_TIMER_MAX_PFC_TIMER_MAX(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_ASM_PFC_TIMER_MAX_PFC_TIMER_MAX     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_ASM_PFC_TIMER_MAX_PFC_TIMER_MAX(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/**
 * Register Group: \a ASM:LBK_WM_CFG
 *
 * Loopback Watermark Configuration
 */


/** 
 * \brief Loopback watermark configuration for flow control on virtual devices
 *
 * \details
 * Register: \a ASM:LBK_WM_CFG:VD_FC_WM
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_VD_PORTS (??), 0-2
 */
#define VTSS_ASM_VD_FC_WM(ri)                VTSS_IOREG(VTSS_TO_ASM,0x21ee + (ri))

/** 
 * \brief
 * Flow control to QS is set when the FIFO fill level reaches this
 * watermark.
 *
 * \details 
 * Field: ::VTSS_ASM_VD_FC_WM . VD_FC_WM
 */
#define  VTSS_F_ASM_VD_FC_WM_VD_FC_WM(x)      VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ASM_VD_FC_WM_VD_FC_WM         VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ASM_VD_FC_WM_VD_FC_WM(x)      VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a ASM:LBK_MISC_CFG
 *
 * Not documented
 */


/** 
 * \brief Disable aging 
 *
 * \details
 * Register: \a ASM:LBK_MISC_CFG:LBK_AGING_DIS
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_CELLBUS_OUTB_DIV_32 (??), 0-4
 */
#define VTSS_ASM_LBK_AGING_DIS(ri)           VTSS_IOREG(VTSS_TO_ASM,0x21f1 + (ri))

/** 
 * \brief
 * Disable aging in loopback path.Frame aging related
 * parameters:QSYS:SYSTEM:FRM_AGING.MAX_AGEASM:LBK_MISC_CFG:LBK_AGING_DIS.L
 * BK_AGING_DISHSCH:SYSTEM:PORT_MODE.AGE_DISDSM:CFG:BUF_CFG.AGING_ENA
 *
 * \details 
 * portmask
 *
 * Field: ::VTSS_ASM_LBK_AGING_DIS . LBK_AGING_DIS
 */
#define  VTSS_F_ASM_LBK_AGING_DIS_LBK_AGING_DIS(x)  (x)
#define  VTSS_M_ASM_LBK_AGING_DIS_LBK_AGING_DIS     0xffffffff
#define  VTSS_X_ASM_LBK_AGING_DIS_LBK_AGING_DIS(x)  (x)


/** 
 * \brief Configuration of LBK FIFOs
 *
 * \details
 * Register: \a ASM:LBK_MISC_CFG:LBK_FIFO_CFG
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_VDS_PLUS_ONE (??), 0-3
 */
#define VTSS_ASM_LBK_FIFO_CFG(ri)            VTSS_IOREG(VTSS_TO_ASM,0x21f6 + (ri))

/** 
 * \brief
 * Flush all data in the FIFO
 *
 * \details 
 * Field: ::VTSS_ASM_LBK_FIFO_CFG . FIFO_FLUSH
 */
#define  VTSS_F_ASM_LBK_FIFO_CFG_FIFO_FLUSH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_LBK_FIFO_CFG_FIFO_FLUSH   VTSS_BIT(0)
#define  VTSS_X_ASM_LBK_FIFO_CFG_FIFO_FLUSH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ASM:LBK_STAT
 *
 * Loopback Block Status registers
 */


/** 
 * \brief Overflow sticky bits
 *
 * \details
 * Register: \a ASM:LBK_STAT:LBK_OVFLW_STICKY
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_CELLBUS_OUTB_DIV_32 (??), 0-4
 */
#define VTSS_ASM_LBK_OVFLW_STICKY(ri)        VTSS_IOREG(VTSS_TO_ASM,0x21fa + (ri))

/** 
 * \brief
 * Frames are dropped due to FIFO overflow.
 *
 * \details 
 * bitmask per port.
 *
 * Field: ::VTSS_ASM_LBK_OVFLW_STICKY . LBK_OVFLW_STICKY
 */
#define  VTSS_F_ASM_LBK_OVFLW_STICKY_LBK_OVFLW_STICKY(x)  (x)
#define  VTSS_M_ASM_LBK_OVFLW_STICKY_LBK_OVFLW_STICKY     0xffffffff
#define  VTSS_X_ASM_LBK_OVFLW_STICKY_LBK_OVFLW_STICKY(x)  (x)


/** 
 * \brief Aging sticky bits
 *
 * \details
 * Register: \a ASM:LBK_STAT:LBK_AGING_STICKY
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_CELLBUS_OUTB_DIV_32 (??), 0-4
 */
#define VTSS_ASM_LBK_AGING_STICKY(ri)        VTSS_IOREG(VTSS_TO_ASM,0x21ff + (ri))

/** 
 * \brief
 * Frames are dropped due to aging in loopback FIFO.
 *
 * \details 
 * bitmask per port.
 *
 * Field: ::VTSS_ASM_LBK_AGING_STICKY . LBK_AGING_STICKY
 */
#define  VTSS_F_ASM_LBK_AGING_STICKY_LBK_AGING_STICKY(x)  (x)
#define  VTSS_M_ASM_LBK_AGING_STICKY_LBK_AGING_STICKY     0xffffffff
#define  VTSS_X_ASM_LBK_AGING_STICKY_LBK_AGING_STICKY(x)  (x)

/**
 * Register Group: \a ASM:RAM_CTRL
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
 * Register: \a ASM:RAM_CTRL:RAM_INIT
 */
#define VTSS_ASM_RAM_INIT                    VTSS_IOREG(VTSS_TO_ASM,0x2204)

/** 
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete (approx. 40 us).
 *
 * \details 
 * Field: ::VTSS_ASM_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_ASM_RAM_INIT_RAM_INIT(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ASM_RAM_INIT_RAM_INIT         VTSS_BIT(1)
#define  VTSS_X_ASM_RAM_INIT_RAM_INIT(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When this field is set, all memories HA_RESTART behavior will be
 * inverted. It is a backdoor for potentiel access issues.
 *
 * \details 
 * Field: ::VTSS_ASM_RAM_INIT . RAM_CFG_HOOK
 */
#define  VTSS_F_ASM_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ASM_RAM_INIT_RAM_CFG_HOOK     VTSS_BIT(0)
#define  VTSS_X_ASM_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ASM:COREMEM
 *
 * Access core memory
 */


/** 
 * \brief Address selection
 *
 * \details
 * Register: \a ASM:COREMEM:CM_ADDR
 */
#define VTSS_ASM_CM_ADDR                     VTSS_IOREG(VTSS_TO_ASM,0x2205)

/** 
 * \brief
 * Address selection for the ram debug address space. 
 *
 * \details 
 * Field: ::VTSS_ASM_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_ASM_CM_ADDR_CM_ADDR(x)        (x)
#define  VTSS_M_ASM_CM_ADDR_CM_ADDR           0xffffffff
#define  VTSS_X_ASM_CM_ADDR_CM_ADDR(x)        (x)


/** 
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a ASM:COREMEM:CM_DATA_WR
 */
#define VTSS_ASM_CM_DATA_WR                  VTSS_IOREG(VTSS_TO_ASM,0x2206)

/** 
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 bit inspection space. This register provides data to
 * be written when CM_OP is set.
 *
 * \details 
 * Field: ::VTSS_ASM_CM_DATA_WR . CM_DATA_WR
 */
#define  VTSS_F_ASM_CM_DATA_WR_CM_DATA_WR(x)  (x)
#define  VTSS_M_ASM_CM_DATA_WR_CM_DATA_WR     0xffffffff
#define  VTSS_X_ASM_CM_DATA_WR_CM_DATA_WR(x)  (x)


/** 
 * \brief Core memory data register for read result
 *
 * \details
 * Register: \a ASM:COREMEM:CM_DATA_RD
 */
#define VTSS_ASM_CM_DATA_RD                  VTSS_IOREG(VTSS_TO_ASM,0x2207)

/** 
 * \brief
 * Read result
 *
 * \details 
 * Field: ::VTSS_ASM_CM_DATA_RD . CM_DATA_RD
 */
#define  VTSS_F_ASM_CM_DATA_RD_CM_DATA_RD(x)  (x)
#define  VTSS_M_ASM_CM_DATA_RD_CM_DATA_RD     0xffffffff
#define  VTSS_X_ASM_CM_DATA_RD_CM_DATA_RD(x)  (x)


/** 
 * \brief Operation to perform in core memory
 *
 * \details
 * Register: \a ASM:COREMEM:CM_OP
 */
#define VTSS_ASM_CM_OP                       VTSS_IOREG(VTSS_TO_ASM,0x2208)

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
 * Field: ::VTSS_ASM_CM_OP . CM_OP
 */
#define  VTSS_F_ASM_CM_OP_CM_OP(x)            VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ASM_CM_OP_CM_OP               VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ASM_CM_OP_CM_OP(x)            VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_FA_REGS_ASM_H_ */
