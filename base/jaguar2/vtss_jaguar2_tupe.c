// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_HW_PROT
#include "vtss_jaguar2_cil.h"

#if defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_FEATURE_HW_PROT)

#include "vtss_jaguar2_tupe.h"

// #define TUPE_TEST // Include test functions

/* - CIL functions ------------------------------------------------- */

#define TUPE_BITS_MAX     (vtss_state->tupe.tupe_bits_bits)
#define TUPE_VALS_MAX     ((1 << vtss_state->tupe.tupe_vals_bits) & ~1)
#define AFI_TUPE_VALS_MAX (1 << AFI_TUPE_CTRL_MAX)

/* check that 'val' has one and only one bit set */
static BOOL check_bit(vtss_tupe_val_t val, u32 *bit)
{
    u32 i, cnt;

    for (i = 0, cnt = 0; i < 32; ++i) {
        if (val & (1 << i)) {
            cnt++;
            *bit = i;
        }
    }
    return (cnt == 1);
}

/* check TUPE value is valid */
static BOOL check_tupe_value(vtss_state_t *vtss_state,
                             vtss_tupe_val_t val)
{
    u32 i = 0;

    if (val < TUPE_VALS_MAX &&
        !(vtss_state->tupe.tupe_vals_free[val / 32] & (1 << (val % 32)))) {
        return val != 0;
    }
    if (check_bit(val / TUPE_VALS_MAX, &i) &&
        i < TUPE_BITS_MAX &&
        !(vtss_state->tupe.tupe_bits_free & (1 << i))) {
        return TRUE;
    }
    return FALSE;
}

/* Perform a TUPE command */
vtss_rc jr2_tupe_cmd(vtss_state_t *vtss_state,
                     vtss_tupe_cmd_t cmd, vtss_tupe_parms_t *parms)
{
    const u32 max_addr = VTSS_VIDS + VTSS_VSI_CNT;
    u32 v, cnt;
    u64 pmask;
    u8  use_bits, use_comb;
    u16 mask;
    vtss_port_no_t port_no;

    VTSS_D("Enter cmd=%u", cmd);

    if (cmd == VTSS_TUPE_CMD_QUERY) { // Query if TUPE is ready
        JR2_RD(VTSS_ANA_L3_TUPE_TUPE_MISC, &v);
        return VTSS_X_ANA_L3_TUPE_TUPE_MISC_TUPE_START(v) == 0 ? VTSS_RC_OK : VTSS_RC_INCOMPLETE;
    } else if (cmd == VTSS_TUPE_CMD_START_NONBLOCKING || // Start TUPE (nonblocking)
               cmd == VTSS_TUPE_CMD_START_BLOCKING) {    // Start TUPE and wait for completion (blocking)
        if (parms) {
            VTSS_D("parms start_addr=%u end_addr=%u value=0x%08x", parms->start_addr, parms->end_addr, parms->value);
        }
        if (!parms || !check_tupe_value(vtss_state, parms->value) ||
            parms->start_addr > parms->end_addr ||
            parms->start_addr > max_addr ||
            parms->end_addr > max_addr) {
            VTSS_D("Invalid parameters");
            return VTSS_RC_ERR_PARM; // invalid parameters
        }

        // check if ready:
        JR2_RD(VTSS_ANA_L3_TUPE_TUPE_MISC, &v);
        if (VTSS_X_ANA_L3_TUPE_TUPE_MISC_TUPE_START(v) != 0) {
            VTSS_D("TUPE not ready");
            return VTSS_RC_INCOMPLETE; // TUPE not ready
        }

        v = VTSS_F_ANA_L3_TUPE_TUPE_ADDR_TUPE_END_ADDR(parms->end_addr) |
            VTSS_F_ANA_L3_TUPE_TUPE_ADDR_TUPE_START_ADDR(parms->start_addr);
        JR2_WR(VTSS_ANA_L3_TUPE_TUPE_ADDR, v);

        pmask = vtss_jr2_port_mask(vtss_state, parms->set_port_list);
        JR2_WR_PMASK(VTSS_ANA_L3_TUPE_TUPE_CMD_PORT_MASK_SET, pmask);

        pmask = vtss_jr2_port_mask(vtss_state, parms->clr_port_list);
        JR2_WR_PMASK(VTSS_ANA_L3_TUPE_TUPE_CMD_PORT_MASK_CLR, pmask);

        use_bits = (parms->value < TUPE_VALS_MAX) ? 0 : 1;
        use_comb = (vtss_state->tupe.tupe_bits_bits + vtss_state->tupe.tupe_vals_bits) > TUPE_CTRL_MAX ? 1 : 0;
        if (use_bits == 0) {
            JR2_WR(VTSS_ANA_L3_TUPE_TUPE_CTRL_VAL, parms->value);
            JR2_WR(VTSS_ANA_L3_TUPE_TUPE_CTRL_VAL_MASK, TUPE_VALS_MAX - 1);
        } else {
            JR2_WR(VTSS_ANA_L3_TUPE_TUPE_CTRL_BIT_MASK, parms->value);
            if (use_comb) {
                pmask = 0;
                mask = parms->value >> TUPE_CTRL_MAX;
                if (mask) {
                    // must use portmask bit, look through tupe_bits_bits+tupe_vals_bits-TUPE_CTRL_MAX unused ports:
                    cnt = vtss_state->tupe.tupe_bits_bits - (TUPE_CTRL_MAX - vtss_state->tupe.tupe_vals_bits);
                    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS && cnt < vtss_state->tupe.tupe_bits_bits; port_no++) {
                        if (VTSS_CHIP_PORT(port_no) == CHIP_PORT_UNUSED) {
                            if (mask & 1) {
                                pmask |= vtss_jr2_pmask(VTSS_CHIP_PORT(port_no));
                                break;
                            }
                            cnt++;
                            mask >>= 1;
                        }
                    }
                }
                JR2_WR_PMASK(VTSS_ANA_L3_TUPE_TUPE_PORT_MASK_A, pmask);
            }
        }

        v = VTSS_F_ANA_L3_TUPE_TUPE_MISC_TUPE_COMB_MASK_ENA(use_comb)    |
            VTSS_F_ANA_L3_TUPE_TUPE_MISC_TUPE_PORT_MASK_B_ENA(0)         |
            VTSS_F_ANA_L3_TUPE_TUPE_MISC_TUPE_PORT_MASK_A_ENA(use_comb)  |
            VTSS_F_ANA_L3_TUPE_TUPE_MISC_TUPE_CTRL_BIT_ENA(use_bits)     |
            VTSS_F_ANA_L3_TUPE_TUPE_MISC_TUPE_CTRL_VAL_ENA(use_bits ^ 1) |
            VTSS_F_ANA_L3_TUPE_TUPE_MISC_TUPE_START(1); // initiate TUPE
        JR2_WR(VTSS_ANA_L3_TUPE_TUPE_MISC, v);

        if (cmd == VTSS_TUPE_CMD_START_BLOCKING) { // wait for completion
            do {
                JR2_RD(VTSS_ANA_L3_TUPE_TUPE_MISC, &v);
            } while (VTSS_X_ANA_L3_TUPE_TUPE_MISC_TUPE_START(v) != 0);
        }
    } else {
        VTSS_D("Invalid cmd");
        return VTSS_RC_ERR_PARM;
    }
    VTSS_D("Exit ok");
    return VTSS_RC_OK;
}

/* Allocate a TUPE value (bits or value) */
vtss_rc jr2_tupe_alloc(vtss_state_t *vtss_state,
                       vtss_tupe_val_type_t type, vtss_tupe_val_t *val)
{
    u32 i;

    VTSS_D("Enter type=%u", type);

    if (vtss_state->tupe.tupe_vals_next == 0) {
        vtss_state->tupe.tupe_vals_next = 1; // 0 is reserved
    }
    if (type == VTSS_TUPE_TYPE_BITS) {
        for (i = 0; i < TUPE_BITS_MAX; ++i) {
            if (vtss_state->tupe.tupe_bits_free & (1 << i)) {
                vtss_state->tupe.tupe_bits_free &= ~(1 << i);
                *val = (1 << i) * TUPE_VALS_MAX;
                VTSS_D("Exit ok, *val=0x%08x", *val);
                return VTSS_RC_OK;
            }
        }
    } else if (type == VTSS_TUPE_TYPE_VALUE) {
        for (i = 0; i < TUPE_VALS_MAX; ++i) {
            if (vtss_state->tupe.tupe_vals_free[vtss_state->tupe.tupe_vals_next / 32] & (1 << (vtss_state->tupe.tupe_vals_next % 32))) {
                *val = vtss_state->tupe.tupe_vals_next;
                vtss_state->tupe.tupe_vals_free[vtss_state->tupe.tupe_vals_next / 32] &= ~(1 << (vtss_state->tupe.tupe_vals_next % 32));
                VTSS_D("Exit ok, *val=0x%08x", *val);
                return VTSS_RC_OK;
            }
            vtss_state->tupe.tupe_vals_next++;
            if (vtss_state->tupe.tupe_vals_next >= TUPE_VALS_MAX) {
                vtss_state->tupe.tupe_vals_next = 1; // 0 is reserved
            }
        }
    }
    VTSS_D("Failed");
    return VTSS_RC_ERR_NO_RES;
}

/* Free a TUPE value (bits or value) */
vtss_rc jr2_tupe_free(vtss_state_t *vtss_state,
                      vtss_tupe_val_t val)
{
    u32 i = 0;
    vtss_tupe_val_type_t type = (val < TUPE_VALS_MAX) ? VTSS_TUPE_TYPE_VALUE : VTSS_TUPE_TYPE_BITS;

    VTSS_D("Enter type=%u val=0x%08x", type, val);

    if (type == VTSS_TUPE_TYPE_BITS) {
        if (check_bit(val / TUPE_VALS_MAX, &i) &&
            i < TUPE_BITS_MAX &&
            !(vtss_state->tupe.tupe_bits_free & (1 << i))) {
            vtss_state->tupe.tupe_bits_free |= 1 << i;
            VTSS_D("Exit ok");
            return VTSS_RC_OK;
        }
    } else if (type == VTSS_TUPE_TYPE_VALUE) {
        if (val < TUPE_VALS_MAX &&
            !(vtss_state->tupe.tupe_vals_free[val / 32] & (1 << (val % 32)))) {
            vtss_state->tupe.tupe_vals_free[val / 32] |= (1 << (val % 32));
            VTSS_D("Exit ok");
            return VTSS_RC_OK;
        }
    }
    VTSS_D("Failed");
    return VTSS_RC_ERROR;
}

/* Configure VLAN/VSI entry with TUPE value */
vtss_rc jr2_tupe_vlan_set(vtss_state_t *vtss_state,
                          u32 addr, // VLAN/VSI address
                          vtss_tupe_val_type_t type, vtss_tupe_val_t val)
{
    const u32 max_addr = VTSS_VIDS + VTSS_VSI_CNT;
    u8 use_comb;
    u32 mask, cnt, i = 0;
    u64 pmask;
    vtss_port_no_t port_no;

    VTSS_D("Enter addr=0x%08x type=%u val=0x%08x", addr, type, val);

    if (addr > max_addr) {
        VTSS_D("Invalid addr");
        return VTSS_RC_ERR_PARM; // invalid parameter
    }

    if (type == VTSS_TUPE_TYPE_BITS) {
        if (check_bit(val / TUPE_VALS_MAX, &i) &&
            i < TUPE_BITS_MAX &&
            !(vtss_state->tupe.tupe_bits_free & (1 << i))) {
            use_comb = (vtss_state->tupe.tupe_bits_bits + vtss_state->tupe.tupe_vals_bits) > TUPE_CTRL_MAX ? 1 : 0;
            if (use_comb) {
                mask = val >> TUPE_CTRL_MAX;
                if (mask) {
                    // must use portmask bit, look through tupe_bits_bits+tupe_vals_bits-TUPE_CTRL_MAX unused ports:
                    JR2_RDX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, addr, &pmask);
                    cnt = vtss_state->tupe.tupe_bits_bits - (TUPE_CTRL_MAX - vtss_state->tupe.tupe_vals_bits);
                    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS && cnt < vtss_state->tupe.tupe_bits_bits; port_no++) {
                        if (VTSS_CHIP_PORT(port_no) == CHIP_PORT_UNUSED) {
                            if (mask & 1) {
                                pmask |= vtss_jr2_pmask(VTSS_CHIP_PORT(port_no));
                                break;
                            }
                            cnt++;
                            mask >>= 1;
                        }
                    }
                    JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, addr, pmask);
                }
            }
            JR2_WR(VTSS_ANA_L3_VLAN_TUPE_CTRL(addr), VTSS_F_ANA_L3_VLAN_TUPE_CTRL_TUPE_CTRL(val & 0xffff));
            VTSS_D("Exit ok");
            return VTSS_RC_OK;
        }
    } else if (type == VTSS_TUPE_TYPE_VALUE) {
        if (val < TUPE_VALS_MAX &&
            !(vtss_state->tupe.tupe_vals_free[val / 32] & (1 << (val % 32)))) {
            JR2_WR(VTSS_ANA_L3_VLAN_TUPE_CTRL(addr), VTSS_F_ANA_L3_VLAN_TUPE_CTRL_TUPE_CTRL(val & 0xffff));
            VTSS_D("Exit ok");
            return VTSS_RC_OK;
        }
    }
    VTSS_D("Failed");
    return VTSS_RC_ERROR;
}

/* Get VLAN/VSI entry TUPE value */
vtss_rc jr2_tupe_vlan_get(vtss_state_t *vtss_state,
                          u32 addr, // VLAN/VSI address
                          vtss_tupe_val_type_t *type, vtss_tupe_val_t *val)
{
    const u32 max_addr = VTSS_VIDS + VTSS_VSI_CNT;
    u8 use_comb;
    u32 cnt, i = 0, v;
    u64 pmask;
    vtss_port_no_t port_no;

    VTSS_D("Enter addr=0x%08x", addr);

    if (addr > max_addr) {
        VTSS_D("Invalid addr");
        return VTSS_RC_ERR_PARM; // invalid parameter
    }

    JR2_RD(VTSS_ANA_L3_VLAN_TUPE_CTRL(addr), &v);
    if (v < TUPE_VALS_MAX) {
        if (v != 0) {
            *type = VTSS_TUPE_TYPE_VALUE;
            *val  = v;
            VTSS_D("Exit ok");
            return VTSS_RC_OK;
        }
    } else {
        *type = VTSS_TUPE_TYPE_BITS;
        if (v == 0) {
            use_comb = (vtss_state->tupe.tupe_bits_bits + vtss_state->tupe.tupe_vals_bits) > TUPE_CTRL_MAX ? 1 : 0;
            if (use_comb) {
                // using portmask bit, look through tupe_bits_bits+tupe_vals_bits-TUPE_CTRL_MAX unused ports:
                v = 1 << TUPE_CTRL_MAX;
                JR2_RDX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, addr, &pmask);
                cnt = vtss_state->tupe.tupe_bits_bits - (TUPE_CTRL_MAX - vtss_state->tupe.tupe_vals_bits);
                for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS && cnt < vtss_state->tupe.tupe_bits_bits; port_no++) {
                    if (VTSS_CHIP_PORT(port_no) == CHIP_PORT_UNUSED) {
                        if (pmask & vtss_jr2_pmask(VTSS_CHIP_PORT(port_no))) {
                            break;
                        }
                    }
                    v <<= 1;
                    cnt++;
                }
            }
        }
        if (v) {
            if (check_bit(v / TUPE_VALS_MAX, &i) &&
                i < TUPE_BITS_MAX) {
                *val  = v;
                VTSS_D("Exit ok");
                return VTSS_RC_OK;
            }
            VTSS_D("Exit ok");
            return VTSS_RC_OK;
        }
    }
    VTSS_D("Failed");
    return VTSS_RC_ERROR;
}

/* Clear VLAN/VSI entry TUPE value */
vtss_rc jr2_tupe_vlan_clr(vtss_state_t *vtss_state,
                          u32 addr) // VLAN/VSI address
{
    const u32 max_addr = VTSS_VIDS + VTSS_VSI_CNT;
    u8 use_comb;
    u64 pmask;
    vtss_port_no_t port_no;

    VTSS_D("Enter addr=0x%08x", addr);

    if (addr > max_addr) {
        VTSS_D("Invalid addr");
        return VTSS_RC_ERR_PARM; // invalid parameter
    }

    use_comb = (vtss_state->tupe.tupe_bits_bits + vtss_state->tupe.tupe_vals_bits) > TUPE_CTRL_MAX ? 1 : 0;
    if (use_comb) {
        // clear unused ports:
        JR2_RDX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, addr, &pmask);
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
            if (VTSS_CHIP_PORT(port_no) == CHIP_PORT_UNUSED) {
                pmask &= ~vtss_jr2_pmask(VTSS_CHIP_PORT(port_no));
            }
        }
        JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, addr, pmask);
    }
    JR2_WR(VTSS_ANA_L3_VLAN_TUPE_CTRL(addr), 0); // 0 is reserved as 'no match value'
    VTSS_D("Exit ok");
    return VTSS_RC_OK;
}

/* TUPE callback function. Called for each already allocated TUPE value changing due to re-initialization
   where split between linear and ring protection values change */
static jr2_tupe_cb_t jr2_tupe_cb;

/* Register TUPE callback function (only one function may be registered): */
void jr2_tupe_cb_register(jr2_tupe_cb_t cb)
{
    if (cb == NULL) {
        VTSS_D("call back pointer invalid");
        return;
    }
    jr2_tupe_cb = cb;
}

/* realloc existing entries to fit new scheme */
static vtss_rc tupe_realloc(vtss_state_t *vtss_state, u8 tupe_linear_prot_bits)
{
    const u32            max_addr = VTSS_VIDS + VTSS_VSI_CNT;
    u32                  new_tupe_bits_max, new_tupe_vals_max, i, j, k = 0;
    u32                  *from_vals;
    u8                   tmp1, tmp2;
    vtss_tupe_val_type_t tupe_type;
    vtss_tupe_val_t      tupe_val, new_tupe_val;

    from_vals = calloc(TUPE_VALS_MAX + TUPE_BITS_MAX, 4);
    if (!from_vals) {
        return VTSS_RC_ERROR;
    }
    new_tupe_bits_max = TUPE_CTRL_MAX + TUPE_PORTMASK_MAX - tupe_linear_prot_bits;
    new_tupe_vals_max = (1 << tupe_linear_prot_bits) & ~1;
    vtss_state->tupe.tupe_vals_next = 1;
    vtss_state->tupe.tupe_bits_free = 0;
    for (i = 0; i < new_tupe_bits_max; ++i) {
        vtss_state->tupe.tupe_bits_free |= 1 << i;
    }
    if (vtss_state->tupe.tupe_vals_free) {
        free(vtss_state->tupe.tupe_vals_free);
    }
    if (new_tupe_vals_max > 0) {
        vtss_state->tupe.tupe_vals_free = malloc(4 * (31 + new_tupe_vals_max) / 32);
        VTSS_MEMSET(vtss_state->tupe.tupe_vals_free, 0, 4 * (31 + new_tupe_vals_max) / 32);
    }
    for (i = 0; i <= max_addr; ++i) {
        if (jr2_tupe_vlan_get(vtss_state, i, &tupe_type, &tupe_val) != VTSS_RC_OK) {
            continue;
        }
        if (tupe_type == VTSS_TUPE_TYPE_VALUE) {
            for (j = 1; j < vtss_state->tupe.tupe_vals_next; ++j) {
                if (from_vals[j] == tupe_val) {
                    break;
                }
            }
            // update entry:
            if (jr2_tupe_vlan_set(vtss_state, i, tupe_type, j) != VTSS_RC_OK) {
                // should not happen, but exit trying to revert changes so far:
                goto exit_revert;
            }
            if (j >= vtss_state->tupe.tupe_vals_next) {
                if (jr2_tupe_cb) {
                    jr2_tupe_cb(vtss_state, VTSS_TUPE_TYPE_VALUE, tupe_val, j);
                }
                from_vals[j] = tupe_val;
                vtss_state->tupe.tupe_vals_next++;
            }
        } else if (tupe_type == VTSS_TUPE_TYPE_BITS) {
            for (j = 0; j < TUPE_BITS_MAX; ++j) {
                if (from_vals[TUPE_VALS_MAX + j] == tupe_val) {
                    break;
                }
            }
            if (j >= TUPE_BITS_MAX) {
                for (j = 0; j < TUPE_BITS_MAX; ++j) {
                    if (vtss_state->tupe.tupe_bits_free & (1 << j)) {
                        vtss_state->tupe.tupe_bits_free &= ~(1 << j);
                        from_vals[TUPE_VALS_MAX + j] = tupe_val;
                        break;
                    }
                }
                new_tupe_val = (1 << j) * new_tupe_vals_max;
                if (jr2_tupe_cb) {
                    jr2_tupe_cb(vtss_state, VTSS_TUPE_TYPE_BITS, tupe_val, new_tupe_val);
                }
            } else
                new_tupe_val = (1 << j) * new_tupe_vals_max;
            // update entry (using new tupe_bits_bits and tupe_vals_bits values):
            tmp1 = vtss_state->tupe.tupe_bits_bits;
            vtss_state->tupe.tupe_bits_bits = (TUPE_CTRL_MAX + TUPE_PORTMASK_MAX) - tupe_linear_prot_bits;
            tmp2 = vtss_state->tupe.tupe_vals_bits;
            vtss_state->tupe.tupe_vals_bits = tupe_linear_prot_bits;
            if (jr2_tupe_vlan_set(vtss_state, i, tupe_type, new_tupe_val) != VTSS_RC_OK) {
                // should not happen, but exit trying to revert changes so far:
                goto exit_revert;
            }
            vtss_state->tupe.tupe_bits_bits = tmp1;
            vtss_state->tupe.tupe_vals_bits = tmp2;
        }
    }
    free(from_vals);
    vtss_state->tupe.tupe_vals_bits = tupe_linear_prot_bits;
    vtss_state->tupe.tupe_bits_bits = (TUPE_CTRL_MAX + TUPE_PORTMASK_MAX) - tupe_linear_prot_bits;
    for (i = vtss_state->tupe.tupe_vals_next; i < TUPE_VALS_MAX; ++i) {
        vtss_state->tupe.tupe_vals_free[i / 32] |= (1 << (i % 32));
    }
    return VTSS_RC_OK;

    exit_revert:
    for (j = 0; j < i; ++j) {
        if (jr2_tupe_vlan_get(vtss_state, j, &tupe_type, &tupe_val) != VTSS_RC_OK) {
            continue;
        }
        if (tupe_type == VTSS_TUPE_TYPE_VALUE) {
            if (tupe_val < vtss_state->tupe.tupe_vals_next) {
                new_tupe_val = from_vals[tupe_val]; // this is the old value
                (void)jr2_tupe_vlan_set(vtss_state, j, tupe_type, new_tupe_val);
            }
        } else if (tupe_type == VTSS_TUPE_TYPE_BITS) {
            if (check_bit(tupe_val / new_tupe_vals_max, &k) &&
                k < TUPE_BITS_MAX) {
                new_tupe_val = from_vals[TUPE_VALS_MAX + k];
                (void)jr2_tupe_vlan_set(vtss_state, j, tupe_type, new_tupe_val);
            }
        }
    }
    for (j = 0; j < (TUPE_VALS_MAX + TUPE_BITS_MAX); ++j) {
        if (from_vals[j] == 0) {
            continue;
        }
        new_tupe_val = from_vals[j]; // this is the old value
        if (jr2_tupe_cb) {
            jr2_tupe_cb(vtss_state, j < TUPE_VALS_MAX ? VTSS_TUPE_TYPE_VALUE : VTSS_TUPE_TYPE_BITS, tupe_val, new_tupe_val);
        }
    }
    free(from_vals);
    // fix vtss_state->tupe.tupe_bits_free + vtss_state->tupe.tupe_vals_free:
    vtss_state->tupe.tupe_bits_free = 0;
    for (i = 0; i < TUPE_BITS_MAX; ++i) {
        vtss_state->tupe.tupe_bits_free |= 1 << i;
    }
    if (vtss_state->tupe.tupe_vals_free) {
        free(vtss_state->tupe.tupe_vals_free);
    }
    if (vtss_state->tupe.tupe_vals_bits) {
        vtss_state->tupe.tupe_vals_free = malloc(4 * (31 + TUPE_VALS_MAX) / 32);
        VTSS_MEMSET(vtss_state->tupe.tupe_vals_free, 0xff, 4 * (31 + TUPE_VALS_MAX) / 32);
        vtss_state->tupe.tupe_vals_next = 1; // 0 is reserved
    }
    for (i = 0; i <= max_addr; ++i) {
        if (jr2_tupe_vlan_get(vtss_state, i, &tupe_type, &tupe_val) != VTSS_RC_OK) {
            continue;
        }
        if (tupe_type == VTSS_TUPE_TYPE_VALUE) {
            if (tupe_val < TUPE_VALS_MAX && tupe_val != 0) {
                vtss_state->tupe.tupe_vals_free[tupe_val / 32] &= ~(1 << (tupe_val % 32));
            } else {
                (void)jr2_tupe_vlan_clr(vtss_state, i);
                if (jr2_tupe_cb) {
                    jr2_tupe_cb(vtss_state, VTSS_TUPE_TYPE_VALUE, tupe_val, 0);
                }
            }
        } else if (tupe_type == VTSS_TUPE_TYPE_BITS) {
            if (check_bit(tupe_val / TUPE_VALS_MAX, &k) &&
                k < TUPE_BITS_MAX) {
                vtss_state->tupe.tupe_bits_free &= ~(1 << k);
            } else {
                (void)jr2_tupe_vlan_clr(vtss_state, i);
                if (jr2_tupe_cb) {
                    jr2_tupe_cb(vtss_state, VTSS_TUPE_TYPE_BITS, tupe_val, 0);
                }
            }
        }
    }
    return VTSS_RC_ERROR;
}

/* Allocate an AFI TUPE value (use is optional) */
vtss_rc jr2_afi_tupe_alloc(vtss_state_t *vtss_state,
                           vtss_afi_tupe_val_t *val)
{
    u32 i;

    VTSS_D("Enter");

    if (vtss_state->tupe.afi_tupe_vals_next == 0) {
        vtss_state->tupe.afi_tupe_vals_next = 1; // 0 is reserved
    }
    for (i = 0; i < AFI_TUPE_VALS_MAX; ++i) {
        if (vtss_state->tupe.afi_tupe_vals_free[vtss_state->tupe.afi_tupe_vals_next / 32] & (1 << (vtss_state->tupe.afi_tupe_vals_next % 32))) {
            *val = vtss_state->tupe.afi_tupe_vals_next;
            vtss_state->tupe.afi_tupe_vals_free[vtss_state->tupe.afi_tupe_vals_next / 32] &= ~(1 << (vtss_state->tupe.afi_tupe_vals_next % 32));
            VTSS_D("Exit ok, *val=0x%08x", *val);
            return VTSS_RC_OK;
        }
        vtss_state->tupe.afi_tupe_vals_next++;
        if (vtss_state->tupe.afi_tupe_vals_next >= AFI_TUPE_VALS_MAX) {
            vtss_state->tupe.afi_tupe_vals_next = 1; // 0 is reserved
        }
    }
    VTSS_D("Failed");
    return VTSS_RC_ERR_NO_RES;
}

/* Free an AFI TUPE value (use is optional) */
vtss_rc jr2_afi_tupe_free(vtss_state_t *vtss_state,
                          vtss_afi_tupe_val_t val)
{
    VTSS_D("Enter val=0x%08x", val);

    if (val < AFI_TUPE_VALS_MAX &&
        !(vtss_state->tupe.afi_tupe_vals_free[val / 32] & (1 << (val % 32)))) {
        vtss_state->tupe.afi_tupe_vals_free[val / 32] |= (1 << (val % 32));
        VTSS_D("Exit ok");
        return VTSS_RC_OK;
    }
    VTSS_D("Failed");
    return VTSS_RC_ERROR;
}

/* Perform an AFI TUPE command:
 * - QUERY:             Returns VTSS_RC_OK if ready, VTSS_RC_INCOMPLETE if not (parms may be NULL)
 * - START_NONBLOCKING: Returns VTSS_RC_OK if TUPE started, VTSS_RC_ERR_PARM if parms invalid,
 *                      VTSS_RC_INCOMPLETE if not ready.
 *                      Note that while TUPE is running, TTI table must not be changed
 * - START_BLOCKING:    Returns VTSS_RC_OK when TUPE command done, VTSS_RC_ERR_PARM if parms invalid,
 *                      VTSS_RC_INCOMPLETE if not ready.
 * Note that the AFI TUPE values used in parms are used directly, so it is optional to use
 * jr2_afi_tupe_alloc() / jr2_afi_tupe_free(). This is to allow other allocation schemes for the AFI
 * TUPE values.
*/
vtss_rc jr2_afi_tupe_cmd(vtss_state_t *vtss_state,
                         vtss_tupe_cmd_t cmd, vtss_afi_tupe_parms_t *parms)
{
    const u32 max_addr = VTSS_AFI_SLOW_INJ_CNT;
    u32 v;

    VTSS_D("Enter cmd=%u", cmd);

    if (cmd == VTSS_TUPE_CMD_QUERY) { // Query if AFI TUPE is ready
        JR2_RD(VTSS_AFI_TUPE_TUPE_MISC, &v);
        return VTSS_X_AFI_TUPE_TUPE_MISC_TUPE_START(v) == 0 ? VTSS_RC_OK : VTSS_RC_INCOMPLETE;
    } else if (cmd == VTSS_TUPE_CMD_START_NONBLOCKING || // Start AFI TUPE (nonblocking)
               cmd == VTSS_TUPE_CMD_START_BLOCKING) {    // Start AFI TUPE and wait for completion (blocking)
        if (parms) {
            VTSS_D("parms start_addr=%u end_addr=%u match={qu:%u, qu_en:%u, port:%u/%u, port_en:%u, 0x%02x, 0x%02x, 0x%02x} update={qu:%u, qu_en:%u, port:%u/%u, port_en:%u, %u, %u}",
                   parms->start_addr, parms->end_addr, parms->match.qu_num, parms->match.qu_num_en, parms->match.port_no, VTSS_CHIP_PORT(parms->match.port_no),
                   parms->match.port_no_en, parms->match.value[0], parms->match.value[1], parms->match.mask,
                   parms->update.qu_num, parms->update.qu_num_en, parms->update.port_no, VTSS_CHIP_PORT(parms->update.port_no), parms->update.port_no_en,
                   parms->update.timer_ena, parms->update.timer_ena_en);
        }
        if (!parms ||
            parms->start_addr > parms->end_addr ||
            parms->start_addr >= max_addr ||
            parms->end_addr >= max_addr) {
            VTSS_D("Invalid parameters");
            return VTSS_RC_ERR_PARM; // invalid parameters
        }

        // check if ready:
        JR2_RD(VTSS_AFI_TUPE_TUPE_MISC, &v);
        if (VTSS_X_AFI_TUPE_TUPE_MISC_TUPE_START(v) != 0) {
            VTSS_D("TUPE not ready");
            return VTSS_RC_INCOMPLETE; // TUPE not ready
        }

        v = VTSS_F_AFI_TUPE_TUPE_ADDR_TUPE_END_ADDR(parms->end_addr) |
            VTSS_F_AFI_TUPE_TUPE_ADDR_TUPE_START_ADDR(parms->start_addr);
        JR2_WR(VTSS_AFI_TUPE_TUPE_ADDR, v);

        v = VTSS_F_AFI_TUPE_TUPE_CRIT1_CRIT_QU_NUM_VAL(parms->match.qu_num) |
            VTSS_F_AFI_TUPE_TUPE_CRIT1_CRIT_PORT_NUM_VAL(VTSS_CHIP_PORT(parms->match.port_no));
        JR2_WR(VTSS_AFI_TUPE_TUPE_CRIT1, v);

        v = VTSS_F_AFI_TUPE_TUPE_CRIT2_CRIT_TUPE_CTRL_MASK(parms->match.mask);
        JR2_WR(VTSS_AFI_TUPE_TUPE_CRIT2, v);

        v = VTSS_F_AFI_TUPE_TUPE_CRIT3_CRIT_TUPE_CTRL_VAL(parms->match.value[0]);
        JR2_WR(VTSS_AFI_TUPE_TUPE_CRIT3(0), v);
        v = VTSS_F_AFI_TUPE_TUPE_CRIT3_CRIT_TUPE_CTRL_VAL(parms->match.value[1]);
        JR2_WR(VTSS_AFI_TUPE_TUPE_CRIT3(1), v);

        v = VTSS_F_AFI_TUPE_TUPE_CMD1_CMD_QU_NUM_VAL(parms->update.qu_num) |
            VTSS_F_AFI_TUPE_TUPE_CMD1_CMD_PORT_NUM_VAL(VTSS_CHIP_PORT(parms->update.port_no));
        JR2_WR(VTSS_AFI_TUPE_TUPE_CMD1, v);

        v = VTSS_F_AFI_TUPE_TUPE_MISC_CMD_QU_NUM_ENA(parms->update.qu_num_en ? 1 : 0)       |
            VTSS_F_AFI_TUPE_TUPE_MISC_CMD_PORT_NUM_ENA(parms->update.port_no_en ? 1 : 0)    |
            VTSS_F_AFI_TUPE_TUPE_MISC_CMD_TIMER_ENA_VAL(parms->update.timer_ena ? 1 : 0)    |
            VTSS_F_AFI_TUPE_TUPE_MISC_CMD_TIMER_ENA_ENA(parms->update.timer_ena_en ? 1 : 0) |
            VTSS_F_AFI_TUPE_TUPE_MISC_CRIT_QU_NUM_ENA(parms->match.qu_num_en ? 1 : 0)       |
            VTSS_F_AFI_TUPE_TUPE_MISC_CRIT_PORT_NUM_ENA(parms->match.port_no_en ? 1 : 0)    |
            VTSS_F_AFI_TUPE_TUPE_MISC_TUPE_START(1); // initiate TUPE
        JR2_WR(VTSS_AFI_TUPE_TUPE_MISC, v);

        if (cmd == VTSS_TUPE_CMD_START_BLOCKING) { // wait for completion
            do {
                JR2_RD(VTSS_AFI_TUPE_TUPE_MISC, &v);
            } while (VTSS_X_AFI_TUPE_TUPE_MISC_TUPE_START(v) != 0);
        }
    } else {
        VTSS_D("Invalid cmd");
        return VTSS_RC_ERR_PARM;
    }
    VTSS_D("Exit ok");
    return VTSS_RC_OK;
}

vtss_rc jr2_tupe_init(vtss_state_t *vtss_state, u8 tupe_linear_prot_bits)
{
    u32 i, cnt;
    u8 realloc = 0;

    VTSS_D("Enter tupe_linear_prot_bits=%u", tupe_linear_prot_bits);

    if (tupe_linear_prot_bits > TUPE_CTRL_MAX) {
        VTSS_D("Invalid parameters");
        return VTSS_RC_ERR_PARM;
    }
    if (vtss_state->tupe.tupe_bits_bits) {
        // re-init, check if ok
        for (i = 0, cnt = 0; i < TUPE_BITS_MAX; ++i) {
            if (!(vtss_state->tupe.tupe_bits_free & (1 << i))) {
                cnt++;
            }
        }
        realloc = cnt ? 1 : 0;
        if (cnt > ((TUPE_CTRL_MAX + TUPE_PORTMASK_MAX) - tupe_linear_prot_bits)) {
            VTSS_D("Not possible");
            return VTSS_RC_INV_STATE;
        }
    }
    if (vtss_state->tupe.tupe_vals_bits) {
        // re-init, check if ok
        for (i = 1, cnt = 0; i < TUPE_VALS_MAX; ++i) {
            if (!(vtss_state->tupe.tupe_vals_free[i / 32] & (1 << (i % 32)))) {
                cnt++;
            }
        }
        realloc = cnt ? 1 : 0;
        if (cnt > ((1 << tupe_linear_prot_bits) & ~1)) {
            VTSS_D("Not possible");
            return VTSS_RC_INV_STATE;
        }
    }
    if (realloc) {
        if (tupe_realloc(vtss_state, tupe_linear_prot_bits) != VTSS_RC_OK) {
            VTSS_D("realloc failed");
            return VTSS_RC_ERROR;
        }
    } else {
        vtss_state->tupe.tupe_vals_bits = tupe_linear_prot_bits;
        vtss_state->tupe.tupe_bits_bits = (TUPE_CTRL_MAX + TUPE_PORTMASK_MAX) - tupe_linear_prot_bits;
        vtss_state->tupe.tupe_bits_free = 0;
        for (i = 0; i < TUPE_BITS_MAX; ++i) {
            vtss_state->tupe.tupe_bits_free |= 1 << i;
        }
        if (vtss_state->tupe.tupe_vals_free) {
            free(vtss_state->tupe.tupe_vals_free);
            vtss_state->tupe.tupe_vals_free = NULL;
        }
        if (vtss_state->tupe.tupe_vals_bits) {
            vtss_state->tupe.tupe_vals_free = malloc(4 * (31 + TUPE_VALS_MAX) / 32);
            VTSS_MEMSET(vtss_state->tupe.tupe_vals_free, 0xff, 4 * (31 + TUPE_VALS_MAX) / 32);
            vtss_state->tupe.tupe_vals_next = 1; // 0 is reserved
        }
    }
    if (!vtss_state->tupe.afi_tupe_vals_free) {
        vtss_state->tupe.afi_tupe_vals_free = malloc(4 * (31 + AFI_TUPE_VALS_MAX) / 32);
        VTSS_MEMSET(vtss_state->tupe.afi_tupe_vals_free, 0xff, 4 * (31 + AFI_TUPE_VALS_MAX) / 32);
    }
    // Minium number of clock cycles between TUPE accessing TTI Table. Default 10.
    // TUPE access to TTI Table takes precedence over both CSR accesses and normal TTI processing.
    // JR2_WR(VTSS_AFI_TTI_MISC_TTI_CTRL2, VTSS_F_AFI_TTI_MISC_TTI_CTRL2_TTI_TUPE_RSV(10));
    VTSS_D("Exit ok");
    return VTSS_RC_OK;
}

/* - Test functions ------------------------------------------------- */

// test code for debug of this TUPE API
// jr2_tupe_init() must have been called first
// warning: Will mess with the VLAN table!
#ifdef TUPE_TEST
vtss_rc jr2_tupe_test(vtss_state_t *vtss_state)
{
    const u32 max_addr = VTSS_VIDS + VTSS_VSI_CNT + 1;
    u32  vlan_change[1 + max_addr / 32];
    u32  i, j, loop, set_port, clr_port, val, cnt;
    u64  pmask, exp_pmask, org_pmask;
    u8   use_comb;
    BOOL ok = TRUE;
    u16 mask;
    vtss_port_no_t    port_no;
    vtss_tupe_val_t   tupe_vals[TUPE_VALS_MAX], v;
    vtss_tupe_val_t   tupe_bits[TUPE_BITS_MAX];
    vtss_tupe_parms_t parms;

    for (loop = 0; loop < 10 && ok; ++loop) {
        // try to allocate all TUPE entries:
        for (i = 1; i < TUPE_VALS_MAX; ++i) {
            if (jr2_tupe_alloc(vtss_state, VTSS_TUPE_TYPE_VALUE, &tupe_vals[i]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to allocate TUPE_VALUE i=%u\n", i);
                ok = FALSE;
            }
        }
        // should not be able to alloc any more now:
        if (jr2_tupe_alloc(vtss_state, VTSS_TUPE_TYPE_VALUE, &v) == VTSS_RC_OK) {
            printf("*** ERROR: Could allocate extra TUPE_VALUE i=%u\n", i);
            ok = FALSE;
        }
        for (i = 0; i < TUPE_BITS_MAX; ++i) {
            if (jr2_tupe_alloc(vtss_state, VTSS_TUPE_TYPE_BITS, &tupe_bits[i]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to allocate TUPE_BITS i=%u\n", i);
                ok = FALSE;
            }
        }
        // should not be able to alloc any more now:
        if (jr2_tupe_alloc(vtss_state, VTSS_TUPE_TYPE_BITS, &v) == VTSS_RC_OK) {
            printf("*** ERROR: Could allocate extra TUPE_BITS i=%u\n", i);
            ok = FALSE;
        }
        // try to free all TUPE entries (random order):
        for (i = 1; i < TUPE_VALS_MAX; ++i) {
            do {
                j = rand() % TUPE_VALS_MAX;
            } while (j == 0 || tupe_vals[j] == 0xffffffff);
            if (jr2_tupe_free(vtss_state, tupe_vals[j]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to free TUPE_VALUE 0x%08x (j=%u)\n", tupe_vals[j], j);
                ok = FALSE;
            }
            // check double free will fail:
            if (jr2_tupe_free(vtss_state, tupe_vals[j]) == VTSS_RC_OK) {
                printf("*** ERROR: Could double free TUPE_VALUE 0x%08x (j=%u)\n", tupe_vals[j], j);
                ok = FALSE;
            }
            tupe_vals[j] = 0xffffffff;
        }
        for (i = 0; i < TUPE_BITS_MAX; ++i) {
            do {
                j = rand() % TUPE_BITS_MAX;
            } while (tupe_bits[j] == 0xffffffff);
            if (jr2_tupe_free(vtss_state, tupe_bits[j]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to free TUPE_BITS 0x%08x (j=%u)\n", tupe_bits[j], j);
                ok = FALSE;
            }
            // check double free will fail:
            if (jr2_tupe_free(vtss_state, tupe_bits[j]) == VTSS_RC_OK) {
                printf("*** ERROR: Could double free TUPE_BITS 0x%08x (j=%u)\n", tupe_bits[j], j);
                ok = FALSE;
            }
            tupe_bits[j] = 0xffffffff;
        }
        printf("Alloc/free loop %u/10 %s\n", loop + 1, ok ? "ok" : "FAILED!");
    }
    // Query cmd should return ready:
    for (loop = 0; loop < 10 && ok; ++loop) {
        if (jr2_tupe_cmd(vtss_state, VTSS_TUPE_CMD_QUERY, NULL) != VTSS_RC_OK) {
            printf("*** ERROR: QUERY cmd failed\n");
            ok = FALSE;
        }
        printf("QUERY cmd loop %u/10 %s\n", loop + 1, ok ? "ok" : "FAILED!");
    }
    // try to allocate all TUPE entries:
    for (i = 1; i < TUPE_VALS_MAX; ++i) {
        if (jr2_tupe_alloc(vtss_state, VTSS_TUPE_TYPE_VALUE, &tupe_vals[i]) != VTSS_RC_OK) {
            printf("*** ERROR: Failed to allocate TUPE_VALUE i=%u\n", i);
            ok = FALSE;
        }
    }
    for (i = 0; i < TUPE_BITS_MAX; ++i) {
        if (jr2_tupe_alloc(vtss_state, VTSS_TUPE_TYPE_BITS, &tupe_bits[i]) != VTSS_RC_OK) {
            printf("*** ERROR: Failed to allocate TUPE_BITS i=%u\n", i);
            ok = FALSE;
        }
    }
    // Test VTSS_TUPE_CMD_START_BLOCKING:
    use_comb = (vtss_state->tupe.tupe_bits_bits + vtss_state->tupe.tupe_vals_bits) > TUPE_CTRL_MAX ? 1 : 0;
    for (loop = 0; loop < 10 && ok; ++loop) {
        VTSS_MEMSET(&parms, 0, sizeof(parms));
        if ((rand() % 1024) < 512) {
            j = rand() % TUPE_VALS_MAX;
            if (j == 0) {
                j = 1;
            }
            v = tupe_vals[j];
        } else {
            j = rand() % TUPE_BITS_MAX;
            v = tupe_bits[j];
        }
        do {
            parms.start_addr = rand() % max_addr;
            parms.end_addr   = rand() % max_addr;
        } while (parms.end_addr < parms.start_addr);
        parms.value      = v;
        pmask = 0;
        if (use_comb) {
            mask = parms.value >> TUPE_CTRL_MAX;
            if (mask) {
                // must use portmask bit, look through tupe_bits_bits+tupe_vals_bits-TUPE_CTRL_MAX unused ports:
                cnt = vtss_state->tupe.tupe_bits_bits - (TUPE_CTRL_MAX - vtss_state->tupe.tupe_vals_bits);
                for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS && cnt < vtss_state->tupe.tupe_bits_bits; port_no++) {
                    if (VTSS_CHIP_PORT(port_no) == CHIP_PORT_UNUSED) {
                        if (mask & 1) {
                            pmask |= vtss_jr2_pmask(VTSS_CHIP_PORT(port_no));
                            break;
                        }
                        cnt++;
                        mask >>= 1;
                    }
                }
            }
        }
        do {
            set_port = rand() % VTSS_PORTS;
            clr_port = rand() % VTSS_PORTS;
        } while ((pmask & vtss_jr2_pmask(VTSS_CHIP_PORT(set_port))) ||
                 (pmask & vtss_jr2_pmask(VTSS_CHIP_PORT(clr_port))));
        parms.set_port_list[set_port] = TRUE;
        parms.clr_port_list[clr_port] = TRUE;
        if (set_port != clr_port) {
            pmask |= vtss_jr2_port_mask(vtss_state, parms.clr_port_list);
        } else {
            pmask |= (rand() % 1024) < 512 ? 0 : vtss_jr2_port_mask(vtss_state, parms.clr_port_list);
        }
        org_pmask = pmask;
        VTSS_MEMSET(vlan_change, 0, sizeof(vlan_change));
        for (i = 0; i < max_addr; ++i) {
            if ((rand() % 1024) < 700) {
                if (jr2_tupe_vlan_set(vtss_state, i, v < TUPE_VALS_MAX ? VTSS_TUPE_TYPE_VALUE : VTSS_TUPE_TYPE_BITS, v) != VTSS_RC_OK) {
                    printf("*** ERROR: tupe_vlan_set failed, i=%u\n", i);
                    ok = FALSE;
                    break;
                }
                JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, pmask);
                vlan_change[i / 32] |= (1 << (i % 32));
            } else {
                if (jr2_tupe_vlan_clr(vtss_state, i) != VTSS_RC_OK) {
                    printf("*** ERROR: tupe_vlan_clr failed, i=%u\n", i);
                    ok = FALSE;
                }
                JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, (u64)0);
            }
        }
        if (jr2_tupe_cmd(vtss_state, VTSS_TUPE_CMD_START_BLOCKING, &parms) != VTSS_RC_OK) {
            printf("*** ERROR: START_BLOCKING cmd failed\n");
            ok = FALSE;
        }
        // check VLAN table entries:
        for (i = 0; i < max_addr; ++i) {
            if (i < parms.start_addr || i > parms.end_addr ||
                !(vlan_change[i / 32] & (1 << (i % 32)))) {
                // expect no change
                exp_pmask = 0;
                JR2_RD(VTSS_ANA_L3_VLAN_TUPE_CTRL(i), &val);
                if (vlan_change[i / 32] & (1 << (i % 32))) {
                    if (val != (v & 0xffff)) {
                        printf("*** ERROR: VLAN table i=%u read TUPE_CTRL=0x%04x, expected 0x%04x\n", i, val, v & 0xffff);
                        ok = FALSE;
                    }
                    exp_pmask = org_pmask;
                } else if (val != 0) {
                    printf("*** ERROR: VLAN table i=%u read TUPE_CTRL=0x%04x, expected 0x%04x\n", i, val, 0);
                    ok = FALSE;
                }
                JR2_RDX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, &pmask);
                if (pmask != exp_pmask) {
                    printf("*** ERROR: VLAN table i=%u read pmask=0x%08x%08x, expected 0x%08x%08x\n",
                           i, (u32)(pmask >> 32), (u32)(pmask), (u32)(exp_pmask >> 32), (u32)(exp_pmask));
                    ok = FALSE;
                }
            } else {
                // expect change in portmask
                JR2_RD(VTSS_ANA_L3_VLAN_TUPE_CTRL(i), &val);
                if (val != (v & 0xffff)) {
                    printf("*** ERROR: VLAN table i=%u read TUPE_CTRL=0x%04x, expected 0x%04x\n", i, val, v & 0xffff);
                    ok = FALSE;
                }
                if (set_port != clr_port) {
                    exp_pmask = (org_pmask ^ vtss_jr2_port_mask(vtss_state, parms.clr_port_list)) |
                        vtss_jr2_port_mask(vtss_state, parms.set_port_list);
                } else {
                    exp_pmask = org_pmask ^ vtss_jr2_port_mask(vtss_state, parms.set_port_list);
                }
                JR2_RDX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, &pmask);
                if (pmask != exp_pmask) {
                    printf("*** ERROR: VLAN table i=%u read pmask=0x%08x%08x, expected 0x%08x%08x\n",
                           i, (u32)(pmask >> 32), (u32)(pmask), (u32)(exp_pmask >> 32), (u32)(exp_pmask));
                    ok = FALSE;
                }
            }
        }
        // clear VLAN table entries again:
        for (i = 0; i < max_addr; ++i) {
            if (jr2_tupe_vlan_clr(vtss_state, i) != VTSS_RC_OK) {
                printf("*** ERROR: tupe_vlan_clr failed, i=%u\n", i);
                ok = FALSE;
            }
            JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, (u64)0);
        }
        printf("START_BLOCKING cmd loop %u/10 %s\n", loop + 1, ok ? "ok" : "FAILED!");
    }
    // Test VTSS_TUPE_CMD_START_NONBLOCKING:
    for (loop = 0; loop < 10 && ok; ++loop) {
        VTSS_MEMSET(&parms, 0, sizeof(parms));
        if ((rand() % 1024) < 512) {
            j = rand() % TUPE_VALS_MAX;
            if (j == 0) {
                j = 1;
            }
            v = tupe_vals[j];
        } else {
            j = rand() % TUPE_BITS_MAX;
            v = tupe_bits[j];
        }
        do {
            parms.start_addr = rand() % max_addr;
            parms.end_addr   = rand() % max_addr;
        } while (parms.end_addr < parms.start_addr);
        parms.value      = v;
        pmask = 0;
        if (use_comb) {
            mask = parms.value >> TUPE_CTRL_MAX;
            if (mask) {
                // must use portmask bit, look through tupe_bits_bits+tupe_vals_bits-TUPE_CTRL_MAX unused ports:
                cnt = vtss_state->tupe.tupe_bits_bits - (TUPE_CTRL_MAX - vtss_state->tupe.tupe_vals_bits);
                for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS && cnt < vtss_state->tupe.tupe_bits_bits; port_no++) {
                    if (VTSS_CHIP_PORT(port_no) == CHIP_PORT_UNUSED) {
                        if (mask & 1) {
                            pmask |= vtss_jr2_pmask(VTSS_CHIP_PORT(port_no));
                            break;
                        }
                        cnt++;
                        mask >>= 1;
                    }
                }
            }
        }
        do {
            set_port = rand() % VTSS_PORTS;
            clr_port = rand() % VTSS_PORTS;
        } while ((pmask & vtss_jr2_pmask(VTSS_CHIP_PORT(set_port))) ||
                 (pmask & vtss_jr2_pmask(VTSS_CHIP_PORT(clr_port))));
        parms.set_port_list[set_port] = TRUE;
        parms.clr_port_list[clr_port] = TRUE;
        if (set_port != clr_port) {
            pmask |= vtss_jr2_port_mask(vtss_state, parms.clr_port_list);
        } else {
            pmask |= (rand() % 1024) < 512 ? 0 : vtss_jr2_port_mask(vtss_state, parms.clr_port_list);
        }
        org_pmask = pmask;
        VTSS_MEMSET(vlan_change, 0, sizeof(vlan_change));
        for (i = 0; i < max_addr; ++i) {
            if ((rand() % 1024) < 700) {
                if (jr2_tupe_vlan_set(vtss_state, i, v < TUPE_VALS_MAX ? VTSS_TUPE_TYPE_VALUE : VTSS_TUPE_TYPE_BITS, v) != VTSS_RC_OK) {
                    printf("*** ERROR: tupe_vlan_set failed, i=%u\n", i);
                    ok = FALSE;
                    break;
                }
                JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, pmask);
                vlan_change[i / 32] |= (1 << (i % 32));
            } else {
                if (jr2_tupe_vlan_clr(vtss_state, i) != VTSS_RC_OK) {
                    printf("*** ERROR: tupe_vlan_clr failed, i=%u\n", i);
                    ok = FALSE;
                }
                JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, (u64)0);
            }
        }
        if (jr2_tupe_cmd(vtss_state, VTSS_TUPE_CMD_START_NONBLOCKING, &parms) != VTSS_RC_OK) {
            printf("*** ERROR: START_NONBLOCKING cmd failed\n");
            ok = FALSE;
        }
        while (jr2_tupe_cmd(vtss_state, VTSS_TUPE_CMD_QUERY, NULL) != VTSS_RC_OK) {
            printf("Wait for cmd to complete...\n");
        }
        // check VLAN table entries:
        for (i = 0; i < max_addr; ++i) {
            if (i < parms.start_addr || i > parms.end_addr ||
                !(vlan_change[i / 32] & (1 << (i % 32)))) {
                // expect no change
                exp_pmask = 0;
                JR2_RD(VTSS_ANA_L3_VLAN_TUPE_CTRL(i), &val);
                if (vlan_change[i / 32] & (1 << (i % 32))) {
                    if (val != (v & 0xffff)) {
                        printf("*** ERROR: VLAN table i=%u read TUPE_CTRL=0x%04x, expected 0x%04x\n", i, val, v & 0xffff);
                        ok = FALSE;
                    }
                    exp_pmask = org_pmask;
                } else if (val != 0) {
                    printf("*** ERROR: VLAN table i=%u read TUPE_CTRL=0x%04x, expected 0x%04x\n", i, val, 0);
                    ok = FALSE;
                }
                JR2_RDX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, &pmask);
                if (pmask != exp_pmask) {
                    printf("*** ERROR: VLAN table i=%u read pmask=0x%08x%08x, expected 0x%08x%08x\n",
                           i, (u32)(pmask >> 32), (u32)(pmask), (u32)(exp_pmask >> 32), (u32)(exp_pmask));
                    ok = FALSE;
                }
            } else {
                // expect change in portmask
                JR2_RD(VTSS_ANA_L3_VLAN_TUPE_CTRL(i), &val);
                if (val != (v & 0xffff)) {
                    printf("*** ERROR: VLAN table i=%u read TUPE_CTRL=0x%04x, expected 0x%04x\n", i, val, v & 0xffff);
                    ok = FALSE;
                }
                if (set_port != clr_port) {
                    exp_pmask = (org_pmask ^ vtss_jr2_port_mask(vtss_state, parms.clr_port_list)) |
                        vtss_jr2_port_mask(vtss_state, parms.set_port_list);
                } else {
                    exp_pmask = org_pmask ^ vtss_jr2_port_mask(vtss_state, parms.set_port_list);
                }
                JR2_RDX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, &pmask);
                if (pmask != exp_pmask) {
                    printf("*** ERROR: VLAN table i=%u read pmask=0x%08x%08x, expected 0x%08x%08x\n",
                           i, (u32)(pmask >> 32), (u32)(pmask), (u32)(exp_pmask >> 32), (u32)(exp_pmask));
                    ok = FALSE;
                }
            }
        }
        // clear VLAN table entries again:
        for (i = 0; i < max_addr; ++i) {
            if (jr2_tupe_vlan_clr(vtss_state, i) != VTSS_RC_OK) {
                printf("*** ERROR: tupe_vlan_clr failed, i=%u\n", i);
                ok = FALSE;
            }
            JR2_WRX_PMASK(VTSS_ANA_L3_VLAN_VLAN_MASK_CFG, i, (u64)0);
        }
        printf("START_NONBLOCKING cmd loop %u/10 %s\n", loop + 1, ok ? "ok" : "FAILED!");
    }
    // try to free all TUPE entries:
    for (i = 1; i < TUPE_VALS_MAX; ++i) {
        if (jr2_tupe_free(vtss_state, tupe_vals[i]) != VTSS_RC_OK) {
            printf("*** ERROR: Failed to free TUPE_VALUE 0x%08x (i=%u)\n", tupe_vals[i], i);
            ok = FALSE;
        }
    }
    for (i = 0; i < TUPE_BITS_MAX; ++i) {
        if (jr2_tupe_free(vtss_state, tupe_bits[i]) != VTSS_RC_OK) {
            printf("*** ERROR: Failed to free TUPE_BITS 0x%08x (i=%u)\n", tupe_bits[i], i);
            ok = FALSE;
        }
    }
    printf("Test %s\n", ok ? "PASSED" : "FAILED");
    return ok ? VTSS_RC_OK : VTSS_RC_ERROR;
}

vtss_rc jr2_tupe_realloc_test(vtss_state_t *vtss_state)
{
    const u32            max_addr = VTSS_VIDS + VTSS_VSI_CNT + 1;
    u32                  i, j, loop, vals_next, bits_next;
    u32                  new_tupe_bits_max, new_tupe_vals_max;
    u16                  bits_free;
    u8                   tupe_linear_prot_bits;
    BOOL                 ok = TRUE;
    u32                  vlan_vals[max_addr];
    vtss_tupe_val_t      tupe_vals[1 << TUPE_CTRL_MAX];
    vtss_tupe_val_t      from_vals[1 << TUPE_CTRL_MAX];
    vtss_tupe_val_t      tupe_bits[TUPE_CTRL_MAX];
    vtss_tupe_val_t      tupe_val;
    vtss_tupe_val_type_t tupe_type;

    for (loop = 0; loop < 10 && ok; ++loop) {
        printf("loop %u/10 (%u + %u bits)...", loop + 1, vtss_state->tupe.tupe_bits_bits, vtss_state->tupe.tupe_vals_bits);
        // allocate half the TUPE entries (randomize)
        VTSS_MEMSET(tupe_vals, 0, sizeof(tupe_vals));
        VTSS_MEMSET(from_vals, 0, sizeof(tupe_vals));
        VTSS_MEMSET(tupe_bits, 0, sizeof(tupe_bits));
        vals_next = 0;
        bits_next = 0;
        for (i = 0; i < ((TUPE_VALS_MAX / 2) - 1); ++i) {
            vtss_state->tupe.tupe_vals_next = rand() % TUPE_VALS_MAX; // trick to alloc random values
            if (vtss_state->tupe.tupe_vals_next == 0) {
                vtss_state->tupe.tupe_vals_next = 1; // 0 is reserved
            }
            if (jr2_tupe_alloc(vtss_state, VTSS_TUPE_TYPE_VALUE, &tupe_vals[i]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to allocate TUPE_VALUE i=%u\n", i);
                ok = FALSE;
            }
            vals_next++;
        }
        for (i = 0; i < (TUPE_BITS_MAX / 2); ++i) {
            if (jr2_tupe_alloc(vtss_state, VTSS_TUPE_TYPE_BITS, &tupe_bits[i]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to allocate TUPE_BITS i=%u\n", i);
                ok = FALSE;
            }
            bits_next++;
        }
        // configure random VLAN/VSI entries using random TUPE entries from above
        VTSS_MEMSET(vlan_vals, 0, sizeof(vlan_vals));
        for (i = 0; i < max_addr; ++i) {
            if ((rand() % 1024) < 512) {
                tupe_type = VTSS_TUPE_TYPE_VALUE;
                tupe_val  = tupe_vals[rand() % vals_next];
            } else {
                tupe_type = VTSS_TUPE_TYPE_BITS;
                tupe_val  = tupe_bits[rand() % bits_next];
            }
            if ((rand() % 1024) < 700) {
                if (jr2_tupe_vlan_set(vtss_state, i, tupe_type, tupe_val) != VTSS_RC_OK) {
                    printf("*** ERROR: tupe_vlan_set failed, i=%u\n", i);
                    ok = FALSE;
                }
                vlan_vals[i] = tupe_val;
            } else {
                if (jr2_tupe_vlan_clr(vtss_state, i) != VTSS_RC_OK) {
                    printf("*** ERROR: tupe_vlan_clr failed, i=%u\n", i);
                    ok = FALSE;
                }
            }
        }
        // try to re-initialize using different (but possible) TUPE bit split
        // avoid 1-bit (can't get half the entries...)
        if (vtss_state->tupe.tupe_vals_bits == 2) {
            tupe_linear_prot_bits = vtss_state->tupe.tupe_vals_bits + 1;
        } else if (vtss_state->tupe.tupe_vals_bits == 14) {
            tupe_linear_prot_bits = vtss_state->tupe.tupe_vals_bits - 1;
        } else {
            tupe_linear_prot_bits = ((rand() % 1024) < 512) ? vtss_state->tupe.tupe_vals_bits + 1: vtss_state->tupe.tupe_vals_bits - 1;
        }
        new_tupe_vals_max = (1 << tupe_linear_prot_bits) & ~1;
        new_tupe_bits_max = TUPE_CTRL_MAX + TUPE_PORTMASK_MAX - tupe_linear_prot_bits;
        // update vlan_vals:
        vals_next = 1;
        bits_free = 0;
        for (i = 0; i < new_tupe_bits_max; ++i) {
            bits_free |= 1 << i;
        }
        for (i = 0; i < max_addr; ++i) {
            if (vlan_vals[i] == 0) {
                continue;
            }
            if (jr2_tupe_vlan_get(vtss_state, i, &tupe_type, &tupe_val) != VTSS_RC_OK) {
                printf("*** ERROR: vlan_get failed, i=%u\n", i);
                ok = FALSE;
            }
            if (tupe_val != vlan_vals[i]) {
                printf("*** ERROR: tupe_val mismatch 0x%04x != 0x%04x, i=%u\n", tupe_val, vlan_vals[i], i);
                ok = FALSE;
            }
            if (tupe_type == VTSS_TUPE_TYPE_VALUE) {
                for (j = 1; j < vals_next; ++j) {
                    if (from_vals[j] == tupe_val) {
                        break;
                    }
                }
                vlan_vals[i] = j;
                if (j >= vals_next) {
                    from_vals[j] = tupe_val;
                    vals_next++;
                }
            } else if (tupe_type == VTSS_TUPE_TYPE_BITS) {
                for (j = 0; j < TUPE_BITS_MAX; ++j) {
                    if (from_vals[TUPE_VALS_MAX + j] == tupe_val) {
                        break;
                    }
                }
                if (j >= TUPE_BITS_MAX) {
                    for (j = 0; j < TUPE_BITS_MAX; ++j) {
                        if (bits_free & (1 << j)) {
                            bits_free &= ~(1 << j);
                            from_vals[TUPE_VALS_MAX + j] = tupe_val;
                            break;
                        }
                    }
                }
                vlan_vals[i] = (1 << j) * new_tupe_vals_max;
            }
            if ((vals_next - 1) > ((TUPE_VALS_MAX / 2) - 1) ||
                bits_next > (TUPE_BITS_MAX / 2)) {
                printf("*** ERROR: vals_next %u > %u || bits_next %u > %u\n", vals_next, ((TUPE_VALS_MAX / 2) - 1), bits_next, (TUPE_BITS_MAX / 2));
                ok = FALSE;
                break;
            }
        }
        // update tupe_vals and tupe_bits:
        vals_next = 0;
        bits_next = 0;
        VTSS_MEMSET(tupe_vals, 0, sizeof(tupe_vals));
        VTSS_MEMSET(tupe_bits, 0, sizeof(tupe_bits));
        for (i = 0; i < max_addr; ++i) {
            if (vlan_vals[i] == 0) {
                continue;
            }
            if (vlan_vals[i] < new_tupe_vals_max) {
                for (j = 0; j < vals_next; ++j) {
                    if (tupe_vals[j] == vlan_vals[i]) {
                        break; // already updated
                    }
                }
                if (j >= vals_next) {
                    tupe_vals[j] = vlan_vals[i];
                    vals_next++;
                }
            } else {
                for (j = 0; j < bits_next; ++j) {
                    if (tupe_bits[j] == vlan_vals[i]) {
                        break; // already updated
                    }
                }
                if (j >= bits_next) {
                    tupe_bits[j] = vlan_vals[i];
                    bits_next++;
                }
            }
            if (vals_next > ((TUPE_VALS_MAX / 2) - 1) ||
                bits_next > (TUPE_BITS_MAX / 2)) {
                printf("*** ERROR: vals_next %u > %u || bits_next %u > %u\n", vals_next, ((TUPE_VALS_MAX / 2) - 1), bits_next, (TUPE_BITS_MAX / 2));
                ok = FALSE;
                break;
            }
        }
        // perform re-init
        if (jr2_tupe_init(vtss_state, tupe_linear_prot_bits) != VTSS_RC_OK) {
            printf("*** ERROR: jr2_tupe_init(%u -> %u) failed\n", vtss_state->tupe.tupe_vals_bits, tupe_linear_prot_bits);
            ok = FALSE;
            break;
        }
        // check VLAN/VSI table was updated as expected:
        for (i = 0; i < max_addr; ++i) {
            tupe_val = 0;
            if (jr2_tupe_vlan_get(vtss_state, i, &tupe_type, &tupe_val) != VTSS_RC_OK &&
                vlan_vals[i] != 0) {
                printf("*** ERROR: vlan_get failed, vlan_vals[%u]=0x%08x\n", i, vlan_vals[i]);
                ok = FALSE;
            } else if (tupe_val != vlan_vals[i]) {
                printf("*** ERROR: tupe_val mismatch 0x%04x != 0x%04x, i=%u\n", tupe_val, vlan_vals[i], i);
                ok = FALSE;
            }
        }
        // clear VLAN table entries again:
        for (i = 0; i < max_addr; ++i) {
            if (jr2_tupe_vlan_clr(vtss_state, i) != VTSS_RC_OK) {
                printf("*** ERROR: tupe_vlan_clr failed, i=%u\n", i);
                ok = FALSE;
            }
        }
        // free the TUPE entries again
        for (i = 0; i < vals_next; ++i) {
            if (jr2_tupe_free(vtss_state, tupe_vals[i]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to free TUPE_VALUE i=%u\n", i);
                ok = FALSE;
            }
        }
        for (i = 0; i < bits_next; ++i) {
            if (jr2_tupe_free(vtss_state, tupe_bits[i]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to free TUPE_BITS i=%u\n", i);
                ok = FALSE;
            }
        }
        vals_next = 0;
        bits_next = 0;
        printf("%s\n", ok ? "OK" : "FAILED!");
    }
    printf("Test %s\n", ok ? "PASSED" : "FAILED");
    return ok ? VTSS_RC_OK : VTSS_RC_ERROR;
}

vtss_rc jr2_afi_tupe_test(vtss_state_t *vtss_state)
{
    const u32 max_addr = VTSS_AFI_SLOW_INJ_CNT;
    u32 tti_tbl[max_addr][3];
    u32  i, j, loop, v, vv;
    BOOL ok = TRUE;
    vtss_afi_tupe_val_t tupe_vals[AFI_TUPE_VALS_MAX], tupe_val;
    vtss_afi_tupe_parms_t parms;

    for (loop = 0; loop < 10 && ok; ++loop) {
        // try to allocate all AFI TUPE entries:
        for (i = 1; i < AFI_TUPE_VALS_MAX; ++i) {
            if (jr2_afi_tupe_alloc(vtss_state, &tupe_vals[i]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to allocate AFI_TUPE_VALUE i=%u\n", i);
                ok = FALSE;
            }
        }
        // should not be able to alloc any more now:
        if (jr2_afi_tupe_alloc(vtss_state, &tupe_val) == VTSS_RC_OK) {
            printf("*** ERROR: Could allocate extra AFI_TUPE_VALUE i=%u\n", i);
            ok = FALSE;
        }
        // try to free all AFI TUPE entries (random order):
        for (i = 1; i < AFI_TUPE_VALS_MAX; ++i) {
            do {
                j = rand() % AFI_TUPE_VALS_MAX;
            } while (j == 0 || tupe_vals[j] == 0);
            if (jr2_afi_tupe_free(vtss_state, tupe_vals[j]) != VTSS_RC_OK) {
                printf("*** ERROR: Failed to free AFI_TUPE_VALUE 0x%08x (j=%u)\n", tupe_vals[j], j);
                ok = FALSE;
            }
            // check double free will fail:
            if (jr2_afi_tupe_free(vtss_state, tupe_vals[j]) == VTSS_RC_OK) {
                printf("*** ERROR: Could double free AFI_TUPE_VALUE 0x%08x (j=%u)\n", tupe_vals[j], j);
                ok = FALSE;
            }
            tupe_vals[j] = 0;
        }
        printf("Alloc/free loop %u/10 %s\n", loop + 1, ok ? "ok" : "FAILED!");
    }
    // Query cmd should return ready:
    for (loop = 0; loop < 10 && ok; ++loop) {
        if (jr2_afi_tupe_cmd(vtss_state, VTSS_TUPE_CMD_QUERY, NULL) != VTSS_RC_OK) {
            printf("*** ERROR: QUERY cmd failed\n");
            ok = FALSE;
        }
        printf("QUERY cmd loop %u/10 %s\n", loop + 1, ok ? "ok" : "FAILED!");
    }
    // try to allocate all AFI TUPE entries:
    for (i = 1; i < AFI_TUPE_VALS_MAX; ++i) {
        if (jr2_afi_tupe_alloc(vtss_state, &tupe_vals[i]) != VTSS_RC_OK) {
            printf("*** ERROR: Failed to allocate AFI_TUPE_VALUE i=%u\n", i);
            ok = FALSE;
        }
    }
    // Test VTSS_TUPE_CMD_START_BLOCKING:
    for (loop = 0; loop < 10 && ok; ++loop) {
        VTSS_MEMSET(&parms, 0, sizeof(parms));
        do {
            parms.start_addr = rand() % max_addr;
            parms.end_addr   = rand() % max_addr;
        } while (parms.end_addr < parms.start_addr);
        if ((rand() % 1024) < 512) {
            // using AFI TUPE value in match
            j = rand() % AFI_TUPE_VALS_MAX;
            if (j == 0) {
                j = 1;
            }
            if ((rand() % 1024) < 512) {
                parms.match.value[0] = tupe_vals[j];
                parms.match.value[1] = 0;
            } else {
                parms.match.value[0] = 0;
                parms.match.value[1] = tupe_vals[j];
            }
            parms.match.mask     = 0xff;
        } else {
            // not using AFI TUPE value in match
            parms.match.value[0] = tupe_vals[j];
            parms.match.value[1] = tupe_vals[j];
            parms.match.mask     = 0;
        }
        parms.match.qu_num        = rand() % 2048;
        parms.match.qu_num_en     = (rand() % 1024) < 512 ? TRUE : FALSE;
        parms.match.port_no       = rand() % VTSS_PORTS;
        parms.match.port_no_en    = (rand() % 1024) < 512 ? TRUE : FALSE;

        parms.update.qu_num       = rand() % 2048;
        parms.update.qu_num_en    = (rand() % 1024) < 512 ? TRUE : FALSE;
        parms.update.port_no      = rand() % VTSS_PORTS;
        parms.update.port_no_en   = (rand() % 1024) < 512 ? TRUE : FALSE;
        parms.update.timer_ena    = (rand() % 1024) < 512 ? TRUE : FALSE;
        parms.update.timer_ena_en = (rand() % 1024) < 512 ? TRUE : FALSE;

        for (i = 0; i < max_addr; ++i) {
            if ((rand() % 1024) < 512) {
                // make sure this entry does match
                v = VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(parms.match.qu_num_en ? parms.match.qu_num : rand() % 2048) |
                    VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(VTSS_CHIP_PORT(parms.match.port_no_en ? parms.match.port_no : rand() % VTSS_PORTS));
                vv = VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(parms.update.qu_num_en ? parms.update.qu_num : VTSS_X_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(v)) |
                    VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(parms.update.port_no_en ? VTSS_CHIP_PORT(parms.update.port_no) : VTSS_X_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(v));
                if (i < parms.start_addr || i > parms.end_addr || parms.match.mask == 0) {
                    tti_tbl[i][0] = v;  // expect no update
                } else {
                    tti_tbl[i][0] = vv; // expect update
                }
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_PORT_QU(i), v);
                v = VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA((rand() % 1024) < 512 ? 1 : 0);
                vv = VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA(parms.update.timer_ena_en ? parms.update.timer_ena : VTSS_X_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA(v));
                if (i < parms.start_addr || i > parms.end_addr || parms.match.mask == 0) {
                    tti_tbl[i][1] = v;  // expect no update
                } else {
                    tti_tbl[i][1] = vv; // expect update
                }
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_TIMER(i), v);
                v = VTSS_F_AFI_TTI_TBL_TTI_TUPE_CTRL_TUPE_CTRL(parms.match.mask ? parms.match.value[0] : rand() & 0xff);
                tti_tbl[i][2] = v;
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_TUPE_CTRL(i), v);
            } else {
                // make sure this entry does not match
                v = VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(parms.match.qu_num_en ? parms.match.qu_num + 1 : parms.match.qu_num) |
                    VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(parms.match.port_no_en ? 1 + VTSS_CHIP_PORT(parms.match.port_no) : VTSS_CHIP_PORT(parms.match.port_no));
                tti_tbl[i][0] = v;
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_PORT_QU(i), v);
                v = VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA((rand() % 1024) < 512 ? 1 : 0);
                tti_tbl[i][1] = v;
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_TIMER(i), v);
                v = VTSS_F_AFI_TTI_TBL_TTI_TUPE_CTRL_TUPE_CTRL(parms.match.mask ? parms.match.value[0] + 1 : parms.match.value[0]);
                tti_tbl[i][2] = v;
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_TUPE_CTRL(i), v);
            }
        }
        if (jr2_afi_tupe_cmd(vtss_state, VTSS_TUPE_CMD_START_BLOCKING, &parms) != VTSS_RC_OK) {
            printf("*** ERROR: START_BLOCKING cmd failed\n");
            ok = FALSE;
        }
        // check TTI table entries:
        for (i = 0; i < max_addr; ++i) {
            JR2_RD(VTSS_AFI_TTI_TBL_TTI_PORT_QU(i), &v);
            if (v != tti_tbl[i][0]) {
                printf("*** ERROR: i=%u v=0x%08x != tti_tbl[0]=0x%08x\n", i, v, tti_tbl[i][0]);
                ok = FALSE;
            }
            JR2_RD(VTSS_AFI_TTI_TBL_TTI_TIMER(i), &v);
            if (v != tti_tbl[i][1]) {
                printf("*** ERROR: i=%u v=0x%08x != tti_tbl[1]=0x%08x\n", i, v, tti_tbl[i][1]);
                ok = FALSE;
            }
            JR2_RD(VTSS_AFI_TTI_TBL_TTI_TUPE_CTRL(i), &v);
            if (v != tti_tbl[i][2]) {
                printf("*** ERROR: i=%u v=0x%08x != tti_tbl[2]=0x%08x\n", i, v, tti_tbl[i][2]);
                ok = FALSE;
            }
        }
        printf("START_BLOCKING cmd loop %u/10 %s\n", loop + 1, ok ? "ok" : "FAILED!");
    }
    // Test VTSS_TUPE_CMD_START_NONBLOCKING:
    for (loop = 0; loop < 10 && ok; ++loop) {
        VTSS_MEMSET(&parms, 0, sizeof(parms));
        do {
            parms.start_addr = rand() % max_addr;
            parms.end_addr   = rand() % max_addr;
        } while (parms.end_addr < parms.start_addr);
        if ((rand() % 1024) < 512) {
            // using AFI TUPE value in match
            j = rand() % AFI_TUPE_VALS_MAX;
            if (j == 0) {
                j = 1;
            }
            if ((rand() % 1024) < 512) {
                parms.match.value[0] = tupe_vals[j];
                parms.match.value[1] = 0;
            } else {
                parms.match.value[0] = 0;
                parms.match.value[1] = tupe_vals[j];
            }
            parms.match.mask     = 0xff;
        } else {
            // not using AFI TUPE value in match
            parms.match.value[0] = tupe_vals[j];
            parms.match.value[1] = tupe_vals[j];
            parms.match.mask     = 0;
        }
        parms.match.qu_num        = rand() % 2048;
        parms.match.qu_num_en     = (rand() % 1024) < 512 ? TRUE : FALSE;
        parms.match.port_no       = rand() % VTSS_PORTS;
        parms.match.port_no_en    = (rand() % 1024) < 512 ? TRUE : FALSE;

        parms.update.qu_num       = rand() % 2048;
        parms.update.qu_num_en    = (rand() % 1024) < 512 ? TRUE : FALSE;
        parms.update.port_no      = rand() % VTSS_PORTS;
        parms.update.port_no_en   = (rand() % 1024) < 512 ? TRUE : FALSE;
        parms.update.timer_ena    = (rand() % 1024) < 512 ? TRUE : FALSE;
        parms.update.timer_ena_en = (rand() % 1024) < 512 ? TRUE : FALSE;

        for (i = 0; i < max_addr; ++i) {
            if ((rand() % 1024) < 512) {
                // make sure this entry does match
                v = VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(parms.match.qu_num_en ? parms.match.qu_num : rand() % 2048) |
                    VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(VTSS_CHIP_PORT(parms.match.port_no_en ? parms.match.port_no : rand() % VTSS_PORTS));
                vv = VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(parms.update.qu_num_en ? parms.update.qu_num : VTSS_X_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(v)) |
                    VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(parms.update.port_no_en ? VTSS_CHIP_PORT(parms.update.port_no) : VTSS_X_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(v));
                if (i < parms.start_addr || i > parms.end_addr || parms.match.mask == 0) {
                    tti_tbl[i][0] = v;  // expect no update
                } else {
                    tti_tbl[i][0] = vv; // expect update
                }
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_PORT_QU(i), v);
                v = VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA((rand() % 1024) < 512 ? 1 : 0);
                vv = VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA(parms.update.timer_ena_en ? parms.update.timer_ena : VTSS_X_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA(v));
                if (i < parms.start_addr || i > parms.end_addr || parms.match.mask == 0) {
                    tti_tbl[i][1] = v;  // expect no update
                } else {
                    tti_tbl[i][1] = vv; // expect update
                }
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_TIMER(i), v);
                v = VTSS_F_AFI_TTI_TBL_TTI_TUPE_CTRL_TUPE_CTRL(parms.match.mask ? parms.match.value[0] : rand() & 0xff);
                tti_tbl[i][2] = v;
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_TUPE_CTRL(i), v);
            } else {
                // make sure this entry does not match
                v = VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(parms.match.qu_num_en ? parms.match.qu_num + 1 : parms.match.qu_num) |
                    VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(parms.match.port_no_en ? 1 + VTSS_CHIP_PORT(parms.match.port_no) : VTSS_CHIP_PORT(parms.match.port_no));
                tti_tbl[i][0] = v;
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_PORT_QU(i), v);
                v = VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA((rand() % 1024) < 512 ? 1 : 0);
                tti_tbl[i][1] = v;
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_TIMER(i), v);
                v = VTSS_F_AFI_TTI_TBL_TTI_TUPE_CTRL_TUPE_CTRL(parms.match.mask ? parms.match.value[0] + 1 : parms.match.value[0]);
                tti_tbl[i][2] = v;
                JR2_WR(VTSS_AFI_TTI_TBL_TTI_TUPE_CTRL(i), v);
            }
        }
        if (jr2_afi_tupe_cmd(vtss_state, VTSS_TUPE_CMD_START_NONBLOCKING, &parms) != VTSS_RC_OK) {
            printf("*** ERROR: START_NONBLOCKING cmd failed\n");
            ok = FALSE;
        }
        while (jr2_tupe_cmd(vtss_state, VTSS_TUPE_CMD_QUERY, NULL) != VTSS_RC_OK) {
            printf("Wait for cmd to complete...\n");
        }
        // check TTI table entries:
        for (i = 0; i < max_addr; ++i) {
            JR2_RD(VTSS_AFI_TTI_TBL_TTI_PORT_QU(i), &v);
            if (v != tti_tbl[i][0]) {
                printf("*** ERROR: i=%u v=0x%08x != tti_tbl[0]=0x%08x\n", i, v, tti_tbl[i][0]);
                ok = FALSE;
            }
            JR2_RD(VTSS_AFI_TTI_TBL_TTI_TIMER(i), &v);
            if (v != tti_tbl[i][1]) {
                printf("*** ERROR: i=%u v=0x%08x != tti_tbl[1]=0x%08x\n", i, v, tti_tbl[i][1]);
                ok = FALSE;
            }
            JR2_RD(VTSS_AFI_TTI_TBL_TTI_TUPE_CTRL(i), &v);
            if (v != tti_tbl[i][2]) {
                printf("*** ERROR: i=%u v=0x%08x != tti_tbl[2]=0x%08x\n", i, v, tti_tbl[i][2]);
                ok = FALSE;
            }
        }
        printf("START_NONBLOCKING cmd loop %u/10 %s\n", loop + 1, ok ? "ok" : "FAILED!");
    }
    // try to free all AFI TUPE entries:
    for (i = 1; i < AFI_TUPE_VALS_MAX; ++i) {
        if (jr2_afi_tupe_free(vtss_state, tupe_vals[i]) != VTSS_RC_OK) {
            printf("*** ERROR: Failed to free AFI_TUPE_VALUE 0x%08x (i=%u)\n", tupe_vals[i], i);
            ok = FALSE;
        }
    }
    printf("Test %s\n", ok ? "PASSED" : "FAILED");
    return ok ? VTSS_RC_OK : VTSS_RC_ERROR;
}
#endif /* TUPE_TEST */

#endif /* VTSS_FEATURE_HW_PROT */
#endif /* VTSS_ARCH_JAGUAR_2 */

/*****************************************************************************/
//
// End of file
//
//****************************************************************************/
