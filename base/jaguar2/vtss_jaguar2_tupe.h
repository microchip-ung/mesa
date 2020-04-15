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
#ifndef _VTSS_JAGUAR2_TUPE_H_
#define _VTSS_JAGUAR2_TUPE_H_

#if defined(VTSS_FEATURE_HW_PROT)

/****************************************************************************
 * TUPE (Table UPdate Engine) for linear/ring protection
 * Used to update VLAN/VSI table
 ****************************************************************************/

/* The TUPE supports using 16 bits for control. This is split in
 * use for linear protection and ring protection.
 * Linear protection will use N number of bits, e.g. 8, which gives 256 TUPE values.
 * Ring protection will then use remaining 16-N (tupe_bits_bits) number of bits,
 * e.g. 8, which gives 8 TUPE bitmask values.
 */

#define TUPE_CTRL_MAX     16     // TUPE control field is 16 bits

#if 0
/* This is currently disabled due to a software defect. */

/* The TUPE also suppports using unused portmask bits for matching.
 * This is supported by the API code, but not recommended.
*/
#if defined(VTSS_CHIP_SERVAL_2) || defined(VTSS_CHIP_LYNX_2)
#define TUPE_PORTMASK_MAX  8     // Max unused portmask bits to use
#elif defined(VTSS_CHIP_JAGUAR_2)
#define TUPE_PORTMASK_MAX  2     // Max unused portmask bits to use
#else
#define TUPE_PORTMASK_MAX  0     // Max unused portmask bits to use
#endif
#else
#define TUPE_PORTMASK_MAX  0     // Max unused portmask bits to use
#endif /* if 0 */

/* TUPE value */
typedef u32 vtss_tupe_val_t;

/* TUPE value type */
typedef enum {
    VTSS_TUPE_TYPE_BITS,  // TUPE value is bitmask (ring protection group)
    VTSS_TUPE_TYPE_VALUE, // TUPE value is value (linear protection group)
} vtss_tupe_val_type_t;

/* TUPE command */
typedef enum {
    VTSS_TUPE_CMD_QUERY,                               // Query if TUPE is ready
    VTSS_TUPE_CMD_START_NONBLOCKING,                   // Start TUPE (nonblocking)
    VTSS_TUPE_CMD_START_BLOCKING,                      // Start TUPE and wait for completion (blocking)
} vtss_tupe_cmd_t;

/* TUPE parameters */
typedef struct {
    u32             start_addr;                          // Start address (VLAN/VSI)
    u32             end_addr;                            // End address (VLAN/VSI)
    vtss_tupe_val_t value;                               // TUPE value
    BOOL            set_port_list[VTSS_PORT_ARRAY_SIZE]; // Ports to set in VLAN/VSI port list
    BOOL            clr_port_list[VTSS_PORT_ARRAY_SIZE]; // Ports to clear in VLAN/VSI port list
} vtss_tupe_parms_t;

/* Allocate a TUPE value (bits or value) */
vtss_rc jr2_tupe_alloc(vtss_state_t *vtss_state,
                       vtss_tupe_val_type_t type, vtss_tupe_val_t *val);

/* Free a TUPE value (bits or value)
   Note that VLAN/VSI entries should be updated first
*/
vtss_rc jr2_tupe_free(vtss_state_t *vtss_state,
                      vtss_tupe_val_t val);

/* Configure VLAN/VSI entry with TUPE value */
vtss_rc jr2_tupe_vlan_set(vtss_state_t *vtss_state,
                          u32 addr, // VLAN/VSI address
                          vtss_tupe_val_type_t type, vtss_tupe_val_t val);

/* Get VLAN/VSI entry TUPE value */
vtss_rc jr2_tupe_vlan_get(vtss_state_t *vtss_state,
                          u32 addr, // VLAN/VSI address
                          vtss_tupe_val_type_t *type, vtss_tupe_val_t *val);

/* Clear VLAN/VSI entry TUPE value */
vtss_rc jr2_tupe_vlan_clr(vtss_state_t *vtss_state,
                          u32 addr); // VLAN/VSI address

/* Perform a TUPE command:
 * - QUERY:             Returns VTSS_RC_OK if ready, VTSS_RC_INCOMPLETE if not (parms may be NULL)
 * - START_NONBLOCKING: Returns VTSS_RC_OK if TUPE started, VTSS_RC_ERR_PARM if parms invalid,
 *                      VTSS_RC_INCOMPLETE if not ready.
 *                      Note that while TUPE is running, VLAN table must not be changed
 * - START_BLOCKING:    Returns VTSS_RC_OK when TUPE command done, VTSS_RC_ERR_PARM if parms invalid,
 *                      VTSS_RC_INCOMPLETE if not ready.
*/
vtss_rc jr2_tupe_cmd(vtss_state_t *vtss_state,
                     vtss_tupe_cmd_t cmd, vtss_tupe_parms_t *parms);

/* TUPE callback function. Called for each already allocated TUPE value changing due to re-initialization
   where split between linear and ring protection values change */
typedef void (*jr2_tupe_cb_t)(vtss_state_t *vtss_state,
                              vtss_tupe_val_type_t type,
                              vtss_tupe_val_t old_val, vtss_tupe_val_t new_val);

/* Register TUPE callback function (only one function may be registered): */
void jr2_tupe_cb_register(jr2_tupe_cb_t cb);


/****************************************************************************
 * TUPE (Table UPdate Engine) for AFI (Automatic Frame Injector)
 * Used to update the AFI TTI (Timer Triggered Injection) table
 ****************************************************************************/

/* The AFI TUPE supports using 8 bits for control value: */
#define AFI_TUPE_CTRL_MAX  8     // AFI TUPE control field is 8 bits

/* AFI TUPE value */
typedef u8 vtss_afi_tupe_val_t;

/* AFI TUPE parameters */
typedef struct {
    u32                     start_addr;      // Start address (TTI table)
    u32                     end_addr;        // End address (TTI table)

    // match criterias (TTI table):
    struct {
        u32                 qu_num;          // [0; 3357] on ServalT and [0; 272xx] on Jaguar_2_C
        BOOL                qu_num_en;       // Enable use of qu_num in match
        vtss_port_no_t      port_no;         // Port number for match
        BOOL                port_no_en;      // Enable use of port_no in match
        vtss_afi_tupe_val_t value[2];        // AFI TUPE values for match
        vtss_afi_tupe_val_t mask;            // AFI TUPE value mask
    } match;

    // update values (TTI table for match cases):
    struct {
        u32                 qu_num;          // [0; 3357] on ServalT and [0; 272xx] on Jaguar_2_C
        BOOL                qu_num_en;       // Enable update of TTI table qu_num
        vtss_port_no_t      port_no;         // New port number
        BOOL                port_no_en;      // Enable use of TTI table port_no
        BOOL                timer_ena;       // New timer_ena value
        BOOL                timer_ena_en;    // Enable update of TTI table timer_ena
    } update;
} vtss_afi_tupe_parms_t;

/* Allocate an AFI TUPE value (use is optional) */
vtss_rc jr2_afi_tupe_alloc(vtss_state_t *vtss_state,
                           vtss_afi_tupe_val_t *val);

/* Free an AFI TUPE value (use is optional) */
vtss_rc jr2_afi_tupe_free(vtss_state_t *vtss_state,
                          vtss_afi_tupe_val_t val);

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
                         vtss_tupe_cmd_t cmd, vtss_afi_tupe_parms_t *parms);

/* Init TUPE using tupe_linear_prot_bits bits for linear protection groups and
   the rest of the bits for ring protection groups. This function may be called
   multiple times to reconfigure the split between linear and ring protection.
   If TUPE values have been allocated and are in use, they will be reallocated
   to fit in the new configuration (if possible)
*/
vtss_rc jr2_tupe_init(vtss_state_t *vtss_state, u8 tupe_linear_prot_bits);

#endif /* VTSS_FEATURE_HW_PROT */

#endif /* _VTSS_JAGUAR2_TUPE_H_ */

/*****************************************************************************/
//
// End of file
//
//****************************************************************************/
