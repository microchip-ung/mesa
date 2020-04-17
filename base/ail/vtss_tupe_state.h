// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_TUPE_STATE_H_
#define _VTSS_TUPE_STATE_H_

#if defined (VTSS_FEATURE_MPLS)

#if defined(VTSS_ARCH_JAGUAR_2)

/*-------------------------------------------------------------
 * CIL Function Pointers, State Variables
 *-----------------------------------------------------------*/

typedef struct {
    /* Number of bits used for TUPE values (linear protection) and
     * TUPE bitmask values (ring protection) */
    u8 tupe_bits_bits;
    u8 tupe_vals_bits;

    /* Free single bits (for ring protection) */
    u16 tupe_bits_free;

    /* Free TUPE values (for linear protection) */
    u32 tupe_vals_next;
    u32 *tupe_vals_free;

    /* Free AFI TUPE values */
    u32 afi_tupe_vals_next;
    u32 *afi_tupe_vals_free;
} vtss_tupe_state_t;

#endif /* VTSS_ARCH_JAGUAR_2 */

#endif /* VTSS_FEATURE_MPLS */

#endif /* _VTSS_MPLS_STATE_H_ */
