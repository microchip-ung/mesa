// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef __VTSS_LK_PACKET_H__
#define __VTSS_LK_PACKET_H__

#if defined(VTSS_ARCH_LAIKA)

vtss_rc lk_init(vtss_state_t *vtss_state);
vtss_rc lk_pie_chnl_rx(vtss_state_t *vtss_state, void *data, const u32 buflen, u8 *ifh, u32 *pktlen);
vtss_rc lk_pie_chnl_tx(vtss_state_t                     *vtss_state,
                       const void *const                 frame,
                       u16                               flen,
                       const vtss_packet_tx_ifh_t *const ifh);

#endif /* VTSS_ARCH_LAIKA */

#endif /* __VTSS_LK_PACKET_H__ */
