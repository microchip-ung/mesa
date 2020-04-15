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

#ifndef _MSCC_APPL_PORT_H_
#define _MSCC_APPL_PORT_H_

#include "mscc/ethernet/switch/api.h"
// #include "sfp.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef enum {
    MSCC_PORT_TYPE_CU,    /** Copper port */
    MSCC_PORT_TYPE_DUAL,  /** Dual media port */
    MSCC_PORT_TYPE_SFP    /** SFP port */
} mscc_port_type_t;

// Port configuration
typedef struct {
    meba_port_admin_state_t admin;       /* Admin enable/disable */
    mesa_bool_t             autoneg;      /* Auto negotiation */
    mesa_port_speed_t       speed;        /* Forced port speed */
    mesa_bool_t             fdx;          /* Forced duplex mode */
    mesa_bool_t             flow_control; /* Flow control */
    uint32_t                max_length;   /* Max frame length */
} mscc_appl_port_conf_t;

// Port entry
typedef struct {
    mesa_bool_t           valid;
    mscc_port_type_t      media_type;
    mscc_appl_port_conf_t conf;
    mesa_port_status_t    status;
    meba_port_entry_t     meba;
    meba_sfp_status_t     sfp_status;
    meba_sfp_transreceiver_t sfp_type;
    meba_sfp_device_t     *sfp_device;
    meba_sfp_driver_t     sfp_driver;
} port_entry_t;

#endif /* _MSCC_APPL_PORT_H_ */
