// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LK_PACKET_STATE_H_
#define _VTSS_LK_PACKET_STATE_H_

#if defined(VTSS_FEATURE_PACKET)

#if defined(VTSS_ARCH_LAIKA)

// 255 descriptors could be not enough.
// 64K descriptors is a lot.
typedef uint16_t vtss_circ_ring_idx_t;

typedef struct {
    vtss_circ_ring_idx_t crc_size;
    vtss_circ_ring_idx_t crc_wr_next;
    vtss_circ_ring_idx_t crc_rd_next;
} vtss_circ_ring_ctl_t;

typedef struct lk_pie_rx_desc_t lk_pie_rx_desc_t;
typedef struct lk_pie_tx_desc_t lk_pie_tx_desc_t;

typedef struct {
    u32                  pc_buff_sz;
    vtss_circ_ring_ctl_t pc_rx_ring_ctl;
    vtss_circ_ring_ctl_t pc_tx_ring_ctl;
    // Buffer descriptors
    lk_pie_rx_desc_t *pc_rx_ring_mem;
    u64               pc_rx_ring_mem_dma;
    lk_pie_tx_desc_t *pc_tx_ring_mem;
    u64               pc_tx_ring_mem_dma;
    // Ring MSB's
    u32 pc_rx_ring_msb;
    u32 pc_tx_ring_msb;
    // Packet memory
    u8 *pc_rx_bmem;
    u64 pc_rx_bmem_dma;
    u8 *pc_tx_bmem;
    u64 pc_tx_bmem_dma;
} vtss_lk_pie_chnl_t;

typedef struct {
    vtss_lk_pie_chnl_t chnls[2];
} vtss_lk_packet_state_t;

#endif /* VTSS_ARCH_LAIKA */

#endif /* VTSS_FEATURE_PACKET */

#endif /*_VTSS_LK_PACKET_STATE_H_*/