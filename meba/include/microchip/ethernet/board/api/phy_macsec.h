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
mepa_rc meba_phy_macsec_secy_conf_update(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf);
mepa_rc meba_phy_macsec_secy_conf_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf);
mepa_rc meba_phy_macsec_secy_conf_del(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_secy_controlled_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_bool_t *const enable);
mepa_rc meba_phy_macsec_secy_controlled_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, const mepa_bool_t enable);
mepa_rc meba_phy_macsec_secy_port_status_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_macsec_secy_port_status_t *const status);
mepa_rc meba_phy_macsec_port_get_next(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t *const search_macsec_port, mepa_macsec_port_t *const found_macsec_port);
mepa_rc meba_phy_macsec_rx_sc_add(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci);
mepa_rc meba_phy_macsec_rx_sc_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const mepa_macsec_rx_sc_conf_t *const conf);
mepa_rc meba_phy_macsec_rx_sc_get_conf(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_conf_t *const conf);
mepa_rc meba_phy_macsec_rx_sc_get_next(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const search_sci, mepa_macsec_sci_t *const found_sci);
mepa_rc meba_phy_macsec_rx_sc_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci);
mepa_rc meba_phy_macsec_rx_sc_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_status_t *const status);
mepa_rc meba_phy_macsec_tx_sc_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_tx_sc_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_tx_sc_conf_t *const conf);
mepa_rc meba_phy_macsec_tx_sc_get_conf(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_conf_t *const conf);
mepa_rc meba_phy_macsec_tx_sc_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_tx_sc_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_status_t *const status);
mepa_rc meba_phy_macsec_rx_sa_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn, const mepa_macsec_sak_t *const sak);
mepa_rc meba_phy_macsec_rx_sa_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, uint32_t *const lowest_pn, mepa_macsec_sak_t *const sak, mepa_bool_t *const active);
mepa_rc meba_phy_macsec_rx_sa_activate(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an);
mepa_rc meba_phy_macsec_rx_sa_disable(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an);
mepa_rc meba_phy_macsec_rx_sa_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an);
mepa_rc meba_phy_macsec_rx_sa_lowest_pn_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn);
mepa_rc meba_phy_macsec_rx_sa_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_rx_sa_status_t *const status);
mepa_rc meba_phy_macsec_rx_seca_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const mepa_macsec_pkt_num_t lowest_pn, const mepa_macsec_sak_t *const sak, const mepa_macsec_ssci_t *const ssci);
mepa_rc meba_phy_macsec_rx_seca_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_pkt_num_t *const lowest_pn, mepa_macsec_sak_t *const sak, mepa_bool_t *const active, mepa_macsec_ssci_t *const ssci);
mepa_rc meba_phy_macsec_rx_seca_lowest_pn_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const mepa_macsec_pkt_num_t lowest_pn);
mepa_rc meba_phy_macsec_tx_sa_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, const uint32_t next_pn, const mepa_bool_t confidentiality, const mepa_macsec_sak_t *const sak);
mepa_rc meba_phy_macsec_tx_sa_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, uint32_t *const next_pn, mepa_bool_t *const confidentiality, mepa_macsec_sak_t *const sak, mepa_bool_t *const active);
mepa_rc meba_phy_macsec_tx_sa_activate(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an);
mepa_rc meba_phy_macsec_tx_sa_disable(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an);
mepa_rc meba_phy_macsec_tx_sa_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an);
mepa_rc meba_phy_macsec_tx_sa_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_tx_sa_status_t *const status);
mepa_rc meba_phy_macsec_tx_seca_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, const mepa_macsec_pkt_num_t next_pn, const mepa_bool_t confidentiality, const mepa_macsec_sak_t *const sak, const mepa_macsec_ssci_t *const ssci);
mepa_rc meba_phy_macsec_tx_seca_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_pkt_num_t *const next_pn, mepa_bool_t *const confidentiality, mepa_macsec_sak_t *const sak, mepa_bool_t *const active, mepa_macsec_ssci_t *const ssci);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_BOARD_PHY_MACSEC_DRIVER_H_
