// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_BOARD_PHY_MACSEC_DRIVER_H_
#define _MICROCHIP_ETHERNET_BOARD_PHY_MACSEC_DRIVER_H_

#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api/phy_macsec.h>
#include <microchip/ethernet/hdr_start.h>

mepa_rc meba_phy_macsec_init_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_init_t *const macsec_init);
mepa_rc meba_phy_macsec_init_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_init_t *const macsec_init);
mepa_rc meba_phy_macsec_secy_conf_add(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_BOARD_PHY_MACSEC_DRIVER_H_
