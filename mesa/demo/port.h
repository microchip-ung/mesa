// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MSCC_APPL_PORT_H_
#define _MSCC_APPL_PORT_H_

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "microchip/ethernet/phy/api.h"
// #include "sfp.h"

char *mesa_port_spd2txt(mesa_port_speed_t speed);

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef enum {
    MSCC_PORT_TYPE_NONE,  /** None */
    MSCC_PORT_TYPE_CU,    /** Copper port */
    MSCC_PORT_TYPE_DUAL,  /** Dual media port */
    MSCC_PORT_TYPE_SFP    /** SFP port */
} mscc_port_type_t;

// Port configuration
typedef struct {
    mesa_port_admin_state_t admin;       /* Admin enable/disable */
    mesa_bool_t             autoneg;      /* Auto negotiation */
    mesa_port_speed_t       speed;        /* Forced port speed */
    mesa_bool_t             fdx;          /* Forced duplex mode */
    mesa_bool_t             flow_control; /* Flow control */
    uint32_t                max_length;   /* Max frame length */
    uint32_t                adv_dis;      /* Advertisement disable flags */
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
    mesa_bool_t           in_bound_status; /* TRUE:  get status from switch.
                                              FALSE: get status from phy */
} port_entry_t;

mesa_rc mscc_appl_port_status_get(const mesa_port_no_t  port_no,
                                  mesa_port_status_t    *const status);
#endif /* _MSCC_APPL_PORT_H_ */
