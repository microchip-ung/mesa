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

#include "port_custom_api.h"
#include "board_probe.h"

static vtss_board_probe_t probes[] = {
#if defined(VTSS_ARCH_LUTON26)
    vtss_board_probe_lu26,
#endif /* VTSS_ARCH_LUTON26 */

/* Serval architectures */
#if defined(VTSS_ARCH_OCELOT)
        vtss_board_probe_ocelot,
#elif defined(VTSS_ARCH_SERVAL)
    vtss_board_probe_serval,
#endif

#if defined(VTSS_ARCH_JAGUAR_2)
    vtss_board_probe_jr2,
#endif /* VTSS_ARCH_JAGUAR_2 */
    NULL
};

static vtss_board_t board;

int vtss_board_probe(vtss_board_info_t *board_info, const port_custom_entry_t **port_custom_tbl)
{
    int i;
    /*lint -e{661} */ // Make lint behave for B2 API targets
    for(i = 0; probes[i] != NULL; i++) {
        if(probes[i](&board, board_info)) {
            *port_custom_tbl = board.custom_port_table;
            return board.type;
        }
    }
    return VTSS_BOARD_UNKNOWN;
}

const char *vtss_board_name(void)
{
    return board.name ? board.name : "Unknown";
}

vtss_board_type_t vtss_board_type(void)
{
    return board.type;
}
#if defined(VTSS_ARCH_JAGUAR_2)
vtss_port_mux_mode_t vtss_port_mux_mode(void)
{
    return board.mux_mode;
}
#endif /* VTSS_ARCH_JAGUAR_2 */

u32 vtss_board_features(void)
{
    return board.features;
}

u32 vtss_board_chipcount(void)
{
    return board.chipcount > 1 ? board.chipcount : 1; /* Maps 0 => 1 */
}

#if defined(VTSS_FEATURE_VSTAX)
u32 vtss_board_default_stackport(BOOL port_0)
{
    return ((board.features & VTSS_BOARD_FEATURE_STACKING) ?
            (port_0 ? board.default_stackport_a : board.default_stackport_b) :
            VTSS_PORT_NO_NONE);
}
#endif  /* VTSS_FEATURE_VSTAX */

port_cap_t vtss_board_port_cap(int board_type, vtss_port_no_t port_no)
{
    return (port_no >= VTSS_PORTS ? 0 :
            board.port_cap ? board.port_cap(board_type, port_no) :
            board.custom_port_table[port_no].cap);
}

/* Initialize board */
void port_custom_init(void)
{
    if(board.init)
        board.init();
}


/* Release ports from reset */
vtss_rc port_custom_reset(void)
{
    if(board.reset)
        return board.reset();
    return VTSS_RC_OK;
}


/* Post ports reset */
vtss_rc post_port_custom_reset(void)
{
    if(board.post_reset)
        return board.post_reset();
    return VTSS_RC_OK;
}


/* Initialize port LEDs */
vtss_rc port_custom_led_init(void)
{
    if(board.led_init)
        return board.led_init();
    return VTSS_RC_OK;
}

/* Update port LED */
vtss_rc port_custom_led_update(vtss_port_no_t port_no,
                               vtss_port_status_t *status,
                               vtss_port_counters_t *counters,
                               port_custom_conf_t *port_conf)
{
    if(board.led_update)
        return board.led_update(port_no, status, counters, port_conf);
    return VTSS_RC_INCOMPLETE;
}

/* Set LED intensity */
vtss_rc port_custom_led_intensity_set(vtss_phy_led_intensity intensity)
{
    if(board.led_intensity)
        return board.led_intensity(intensity);
    return VTSS_RC_OK;
}

// Function for doing special port configuration that depends upon the platform
// Forexample do the enzo board requires that if the stack ports uses SFPs, the SFPs must be turn on
// using a special serialised GPIO system.
void port_custom_conf(vtss_port_no_t port,
                      port_custom_conf_t *port_conf)
{
    if(board.port_conf)
        board.port_conf(port, port_conf);
}

/* Called when system is reset. */
void port_custom_pre_reset(void)
{
    if(board.pre_reset)
        board.pre_reset();
}

/* Do PHY i2c read */
vtss_rc board_sfp_i2c_read(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, u8 cnt, BOOL word_access)
{
    if(board.sfp_i2c_read)
        return board.sfp_i2c_read(port_no, i2c_addr, addr, data, cnt, word_access);

    return VTSS_RC_ERROR;
}

/* Do PHY i2c write */
vtss_rc board_sfp_i2c_write(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, BOOL word_access)
{
    if(board.sfp_i2c_write)
        return board.sfp_i2c_write(port_no, i2c_addr, addr, data, word_access);

    return VTSS_RC_ERROR;
}

/* Do a SFP module detect  */
vtss_rc port_custom_sfp_mod_detect(BOOL *detect_status)
{
    if(board.sfp_mod_detect)
        return  board.sfp_mod_detect(detect_status);
    return VTSS_RC_OK;
}

/* Do a SFP module detect  */
vtss_rc port_custom_sfp_status(port_custom_sfp_status_t *status)
{
    if(board.sfp_status)
        return  board.sfp_status(status);
    return VTSS_RC_ERROR;
}

#if defined(VTSS_FEATURE_FAN)
/***************************************************************************
 * Fan
 ***************************************************************************/
vtss_rc port_custom_fan_init(vtss_fan_conf_t fan_spec) {
    if (board.board_fan_init) {
        return  board.board_fan_init(fan_spec);
    }
    return VTSS_RC_ERROR;
}
#endif /* VTSS_FEATURE_FAN */

/***************************************************************************
 * Temperature sensors
 ***************************************************************************/

/* Initialize all temperature sensors on the board */
vtss_rc port_custom_temp_sensors_init(void)
{
    if (board.board_temp_sensors_init) {
        return  board.board_temp_sensors_init();
    }
    return VTSS_RC_ERROR;
}

/* Get temperature sensors values on the board */
vtss_rc port_custom_temp_sensors_get(vtss_port_no_t iport, i16* temp)
{
    if (board.board_temp_sensors_get) {
        return  board.board_temp_sensors_get(iport, temp);
    }
    return VTSS_RC_ERROR;
}


/* Get number of temperature sensors on the board */
u8 port_custom_temp_sensors_cnt(void)
{
    if (board.board_temp_sensors_cnt) {
        return  board.board_temp_sensors_cnt();
    }
    return 0;
}
