// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_BOARD_PROBE_H_
#define _VTSS_BOARD_PROBE_H_

#include "port_custom_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /*
     * Identification & Features
     */
    vtss_board_type_t type;
    const char *name;
    u32 features;
    int chipcount;
    const port_custom_entry_t *custom_port_table;

    /*
     * Stacking support
     */
    u32 default_stackport_a, default_stackport_b;

    /* 
     * Board specific functions
     */
    
    /* Initialize board */
    void (*init)(void);

    /* Release ports from reset */
    vtss_rc (*reset)(void);

    /* Post ports reset */
    vtss_rc (*post_reset)(void);

    /* Called when system is reset. */
    void (*pre_reset)(void);

    /* Initialize port LEDs */
    vtss_rc (*led_init)(void);

    /* Update port LED */
    vtss_rc (*led_update)(vtss_port_no_t port_no,
                          vtss_port_status_t *status,
                          vtss_port_counters_t *counters,
                          port_custom_conf_t *port_conf);

    /* Set LED intensity */
    vtss_rc (*led_intensity)(vtss_phy_led_intensity intensity);
    
    /* Function for doing special port configuration that depends upon the platform */
    void (*port_conf)(vtss_port_no_t port, 
                      port_custom_conf_t *port_conf);

    /* Do SFP i2c reads */
    vtss_rc (*sfp_i2c_read)(vtss_port_no_t port_no, 
                            u8 i2c_addr, 
                            u8 addr, 
                            u8 *const data, 
                            u8 cnt,
                            BOOL word_access);

    vtss_rc (*sfp_i2c_write)(vtss_port_no_t port_no, 
                            u8 i2c_addr, 
                            u8 addr, 
                            u8 *const data,
                            BOOL word_access);

   /* Do i2c reads */
    vtss_rc (*i2c_read)(vtss_port_no_t port_no, 
                        u8 i2c_addr, 
                        u8 addr, 
                        u8 *const data, 
                        u8 cnt);

    /* SFP module detect */
    vtss_rc (*sfp_mod_detect)(BOOL *detect_status);

    /* SFP module status */
    vtss_rc (*sfp_status)(port_custom_sfp_status_t *status);

    /* Return capabilities for board and port */
    port_cap_t (*port_cap)(int board_type, vtss_port_no_t port_no);
    
#if defined(VTSS_FEATURE_FAN)
    /* Initialize fan controllers on the board */
    vtss_rc (*board_fan_init)(vtss_fan_conf_t fan_spec);
#endif /* VTSS_FEATURE_FAN */

    /* Initialize temperature sensors on the board */
    vtss_rc (*board_temp_sensors_init)(void);

    /* Get temperature sensors on the board */
    vtss_rc (*board_temp_sensors_get)(vtss_port_no_t iport, i16 *temp);

    /* Get number of temperature sensors on the board */
    u8 (*board_temp_sensors_cnt)(void);

#if defined(VTSS_ARCH_JAGUAR_2)
    /* Mux mode of the chip (if detectable) */
    vtss_port_mux_mode_t mux_mode;
#endif /*  VTSS_ARCH_JAGUAR_2 */
} vtss_board_t;

typedef BOOL (*vtss_board_probe_t)(vtss_board_t *, vtss_board_info_t *);

#if defined(VTSS_ARCH_LUTON26)
extern BOOL vtss_board_probe_lu26(vtss_board_t *board, vtss_board_info_t *board_info);
#endif /* VTSS_ARCH_LUTON26 */

/* Serval architectures */
#if defined(VTSS_ARCH_OCELOT)
extern BOOL vtss_board_probe_ocelot(vtss_board_t *board, vtss_board_info_t *board_info);
extern BOOL vtss_board_probe_ocelot_pcb120(vtss_board_t *board, vtss_board_info_t *board_info);
#elif defined(VTSS_ARCH_SERVAL)
extern BOOL vtss_board_probe_serval(vtss_board_t *board, vtss_board_info_t *board_info);
#endif

#if defined(VTSS_ARCH_JAGUAR_2)
extern BOOL vtss_board_probe_jr2(vtss_board_t *board, vtss_board_info_t *board_info);
#endif /* VTSS_ARCH_JAGUAR_2 */

#ifdef __cplusplus
}
#endif

#endif /* _VTSS_BOARD_PROBE_H_ */

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
