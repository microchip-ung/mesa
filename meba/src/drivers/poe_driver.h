// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_BOARD_POE_DRIVER_H_
#define _MICROCHIP_ETHERNET_BOARD_POE_DRIVER_H_

#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/switch/api/types.h>

typedef struct {
    const char *i2c_device;
    const uint8_t i2c_address;
} i2c_config_t;

/**
 * \brief Open an I2C device and configure I2C address
 *
 * \param filename       [IN] Filename for the I2C device
 * \param i2c_addr       [IN] i2c address to communicate with
 *
 * \return File descriptor for I2C driver
*/
int meba_pd69200_i2c_adapter_open(const char *filename, uint8_t i2c_addr);

/**
 * \brief Initialize driver
 *
 * \param inst              [IN] MEBA instance.
 * \param driver_name       [IN] Driver name.
 * \param capabilities      [IN] Capabilities.
 * \param port_map          [IN] Port map.
 * \param port_map_length   [IN] Number of elements in port map.
 * \param psu_map           [IN] Psu map.
 * \param psu_map_length    [IN] Number of elements in psu_map.
 * \param read_function     [IN] Read function.
 * \param write_function    [IN] Write function.
 * \param debug             [OUT] Board debug output.
 *
 * \return meba_poe_ctrl_inst
*/
void meba_pd69200_driver_init(
    meba_poe_ctrl_inst_t       *inst,
    char const                 *driver_name, 
    int                         adapter_fd, 
    meba_poe_ctrl_cap_t         capabilities, 
    meba_poe_port_properties_t *port_map,
    uint32_t                    port_map_length,
    meba_poe_psu_input_prob_t   *psu_map,
    uint32_t                    psu_map_length,
    meba_debug_t                debug);

/**
 * \brief Initialize driver
 *
 * \param inst              [IN] MEBA instance.
 * \param driver_name       [IN] Driver name.
 * \param capabilities      [IN] Capabilities.
 * \param port_map          [IN] Port map.
 * \param port_map_length   [IN] Number of elements in port map.
 * \param psu_map           [IN] Psu map.
 * \param psu_map_length    [IN] Number of elements in psu_map.
 * \param read_function     [IN] Read function.
 * \param write_function    [IN] Write function.
 * \param debug             [OUT] Board debug output.
 *
 * \return meba_poe_ctrl_inst
*/
void meba_pd69200bt_driver_init(
    meba_poe_ctrl_inst_t       *inst,
    char const                 *driver_name,
    int                         adapter_fd, 
    meba_poe_ctrl_cap_t         capabilities,
    meba_poe_port_properties_t *port_map,
    uint32_t                    port_map_length,
    meba_poe_psu_input_prob_t   *psu_map,
    uint32_t                    psu_map_length,
    meba_debug_t                debug);

#endif // _MICROCHIP_ETHERNET_BOARD_POE_DRIVER_H_
