// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PHY_INIT_SCRIPTS_H_
#define _VTSS_PHY_INIT_SCRIPTS_H_

vtss_rc vtss_phy_post_reset_private(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);



vtss_rc vtss_phy_init_seq_atom(struct vtss_state_s *vtss_state,
                               vtss_phy_port_state_t *ps,
                               vtss_port_no_t        port_no,
                               BOOL                  luton26_mode);

vtss_rc vtss_phy_pre_reset_private(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_phy_wait_for_micro_complete(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);

vtss_rc vtss_phy_is_8051_crc_ok_private (struct vtss_state_s *vtss_state,
                                         vtss_port_no_t port_no,
                                         u16 start_addr,
                                         u16 code_length,
                                         u16 expected_crc,
                                         BOOL first_time);

const char *vtss_phy_family2txt(vtss_phy_family_t family);

vtss_rc vtss_phy_init_seq_blazer(struct vtss_state_s *vtss_state,
                                 vtss_phy_port_state_t *ps,
                                 vtss_port_no_t        port_no);
vtss_rc vtss_phy_pre_init_seq_nano_7435(vtss_state_t *vtss_state,
				        vtss_port_no_t port_no);

// The address at where the first byte of the internal 8051 firmware is placed.
#define FIRMWARE_START_ADDR 0x4000

#endif /* _VTSS_PHY_INIT_SCRIPTS_H_ */

