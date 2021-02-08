// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_BOARD_PHY_DRIVER_H_
#define _MICROCHIP_ETHERNET_BOARD_PHY_DRIVER_H_

#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/phy/api/types.h>

#include <microchip/ethernet/hdr_start.h>

/**
 * \brief Reset the PHY
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param rst_conf          [IN] Configuration needed for resetting PHY.
 *
 * \return
**/
mepa_rc meba_phy_reset(meba_inst_t inst, mepa_port_no_t port_no,
                       const mepa_reset_param_t *rst_conf);

/**
 * \brief Get the current status of the PHY.
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param status            [OUT] PHY status.
 *
 * \return
**/
mepa_rc meba_phy_status_poll(meba_inst_t inst, mepa_port_no_t port_no,
                             mepa_driver_status_t *status);

/**
 * \brief Set the configuration to the PHY.
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param conf              [IN] PHY configuration.
 *
 * \return
**/
mepa_rc meba_phy_conf_set(meba_inst_t inst, mepa_port_no_t port_no,
                          mepa_driver_conf_t *conf);
/**
 * \brief Get the PHY interface based on speed.
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param speed             [IN] Speed.
 * \param intf              [OUT] Interface that is needed to be used by the port.
 *
 * \return
**/
mepa_rc meba_phy_if_get(meba_inst_t inst, mepa_port_no_t port_no,
                        mepa_port_speed_t speed, mepa_port_interface_t *intf);

/**
 * \brief Sets the power mode.
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param power             [IN] power mode
 *
 * \return
**/
mepa_rc meba_phy_power_set(meba_inst_t inst, mepa_port_no_t port_no,
                           mepa_power_mode_t power);

/**
 * \brief Starts cable diagnostics.
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param mode              [IN] Mode in which to start.
 *
 * \return
**/
mepa_rc meba_phy_cable_diag_start(meba_inst_t inst, mepa_port_no_t port_no, int mode);

/**
 * \brief Gets result of cable diagnostics.
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param result            [OUT] Result from cable diagnostics.
 *
 * \return
**/
mepa_rc meba_phy_cable_diag_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_cable_diag_result_t *result);

/*
 * \brief Sets the media type in case the port is a dual media port with external phy.
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param phy_media_if      [IN] Media type.
 *
 * \return
**/
mepa_rc meba_phy_media_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_media_interface_t phy_media_if);

/*
 * \brief Gets Copper 1G PHY auto negotiation status.
 *
 * \param inst              [IN] MEBA instance.
 * \param port_no           [IN] port number.
 * \param status            [OUT] PHY auto negotiation status.
 *
 * \return
**/
mepa_rc meba_phy_aneg_status_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_aneg_status_t *status);

#include <microchip/ethernet/hdr_end.h>
#endif //_MICROCHIP_ETHERNET_BOARD_PHY_DRIVER_H
