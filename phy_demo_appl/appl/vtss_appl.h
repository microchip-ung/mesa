// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_APPL_H_
#define _VTSS_APPL_H_

/* Application instance number */
typedef int vtss_appl_inst_t;

/* Port status */
typedef struct {
    BOOL              link;       /* Link status, remaining fields only valid if link up */
    vtss_port_speed_t speed;      /* Speed */
    BOOL              fdx;        /* Full duplex */
    
    /* Auto negotiation result */
    struct {
        BOOL obey_pause;     /* This port should obey PAUSE frames */
        BOOL generate_pause; /* Link partner obeys PAUSE frames */
    } aneg;

} vtss_appl_port_status_t;

/* Get port status */
vtss_rc vtss_appl_port_status_get(const vtss_appl_inst_t inst,
                                  const vtss_port_no_t    port_no,
                                  vtss_appl_port_status_t *const status);

/* Port configuration */
typedef struct {
    BOOL              enable;       /* Admin enable/disable */
    BOOL              autoneg;      /* Auto negotiation */
    vtss_port_speed_t speed;        /* Forced port speed */
    BOOL              fdx;          /* Forced duplex mode */
    BOOL              flow_control; /* Flow control */
    u32               max_length;   /* Max frame length */
    BOOL              frame_length_chk; /* True to do 802.3 frame length check for ethertypes below 0x0600*/
} vtss_appl_port_conf_t;

/* Get port configuration */
vtss_rc vtss_appl_port_conf_get(const vtss_appl_inst_t inst, 
                                const vtss_port_no_t  port_no,
                                vtss_appl_port_conf_t *const conf);

/* Set port configuration */
vtss_rc vtss_appl_port_conf_set(const vtss_appl_inst_t inst,
                                const vtss_port_no_t        port_no,
                                const vtss_appl_port_conf_t *const conf);

/* Get port interface type */
vtss_rc vtss_appl_port_if_get(const vtss_appl_inst_t inst,
                              const vtss_port_no_t  port_no,
                              vtss_port_interface_t *const if_type);

#ifdef VTSS_OPT_TRACE

extern vtss_trace_conf_t vtss_appl_trace_conf;

/* Application trace group */
#define VTSS_APPL_TRACE_GROUP VTSS_TRACE_GROUP_COUNT
#define VTSS_APPL_TRACE_LAYER VTSS_TRACE_LAYER_COUNT

/* Application trace macros */
#define T_E(...) { if (vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] >= VTSS_TRACE_LEVEL_ERROR) vtss_callout_trace_printf(VTSS_APPL_TRACE_LAYER, VTSS_APPL_TRACE_GROUP, VTSS_TRACE_LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }
#define T_I(...) { if (vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] >= VTSS_TRACE_LEVEL_INFO) vtss_callout_trace_printf(VTSS_APPL_TRACE_LAYER, VTSS_APPL_TRACE_GROUP, VTSS_TRACE_LEVEL_INFO, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }
#define T_D(...) { if (vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] >= VTSS_TRACE_LEVEL_DEBUG) vtss_callout_trace_printf(VTSS_APPL_TRACE_LAYER, VTSS_APPL_TRACE_GROUP, VTSS_TRACE_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }
#define T_N(...) { if (vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] >= VTSS_TRACE_LEVEL_NOISE) vtss_callout_trace_printf(VTSS_APPL_TRACE_LAYER, VTSS_APPL_TRACE_GROUP, VTSS_TRACE_LEVEL_NOISE, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }
#else

/* No trace */
#define T_E(...)
#define T_I(...)
#define T_D(...)
#define T_N(...)

#endif

typedef struct {
    vtss_init_conf_t *init_conf; /* Init configuration */
} vtss_init_t;

/**< \brief Description: Board structure filled out by vtss_board_init(). */
typedef struct vtss_appl_board_t {
    const char         *descr;     /* Target description */
    vtss_target_type_t target;     /* Target type */
    vtss_inst_t        inst;       /* API instance reference */
    u32                port_count; /* Number of ports */

    vtss_init_t init; /* Init configuration */

    /* Port status */
    vtss_appl_port_status_t port_status[VTSS_PORT_ARRAY_SIZE];

    /* Port configuration */
    vtss_appl_port_conf_t   port_conf[VTSS_PORT_ARRAY_SIZE];

#if defined(VTSS_FEATURE_PORT_CONTROL)
    vtss_port_map_t *port_map;   /* Board port map */
#endif /* VTSS_FEATURE_PORT_CONTROL */

    /* Port MAC interface */
    vtss_port_interface_t (* port_interface)(vtss_port_no_t port_no);

    /* Post ports reset */
    vtss_rc (*post_reset)(void);

    /* Called when system is reset. */
    void (*pre_reset)(void);

    /* Optional, avoid polling for some ports */
    BOOL (* port_poll)(vtss_port_no_t port_no);

    /* Optional, called when API instance created - but before portmap set */
    int  (* board_probe)(struct vtss_appl_board_t *board);

    /* Parse options, initialize I/O, release main chip from reset */
    int  (* board_init)(int argc, const char **argv, struct vtss_appl_board_t *board);

    /* Optional, release PHYs from reset */
    void (* board_init_post)(struct vtss_appl_board_t *board);

    /* Optional, release PHYs from coma */
    void (* board_init_done)(struct vtss_appl_board_t *board);

    /* Optional, periodic board poll */
    void (* board_periodic)(struct vtss_appl_board_t *board);
#if defined(VTSS_FEATURE_PACKET)
    /* Optional, Transmit */
    vtss_rc (* board_transmit)(struct vtss_appl_board_t   *board, 
                               const vtss_packet_tx_ifh_t *const ifh,
                               const u8                   *const frame,
                               const u32                   length);
#endif

#if defined(VTSS_FEATURE_PORT_CONTROL)
    /* Optional, update port LED/config */
    vtss_rc (* port_update)(struct vtss_appl_board_t *board,
                            vtss_port_no_t           port_no, 
                            const vtss_port_conf_t   *conf);
#endif /* VTSS_FEATURE_PORT_CONTROL */
    /* Optional test started with 'debug test' CLI command */
    vtss_rc (* debug_test)(u32 value);
} vtss_appl_board_t;

/* Get API instance */
vtss_appl_board_t *vtss_appl_board_get(vtss_appl_inst_t inst);

void vtss_board_generic_init(vtss_appl_board_t *board, int argc, const char **argv);
extern u16 store_file;

/* ================================================================= *
 *  Conversion between internal and user port numbers.
 *  These functions are intended to be used only in places that
 *  interact with the user, i.e. Web, CLI, SNMP etc..
 * ================================================================= */
typedef vtss_port_no_t vtss_uport_no_t; /* User port is of same type as normal, internal port. */
vtss_uport_no_t iport2uport(vtss_port_no_t iport); // Convert from internal to user port number.
vtss_port_no_t  uport2iport(vtss_uport_no_t uport); // Convert from user to internal port number.

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Options */
typedef struct {
    int  count;
    BOOL quiet;
} vtss_appl_opt;

int vtss_appl_parse_options(int argc, char **argv, vtss_appl_opt *opt);

#endif /* _VTSS_APPL_H_ */
