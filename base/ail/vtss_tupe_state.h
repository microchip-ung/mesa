/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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
