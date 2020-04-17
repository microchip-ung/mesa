// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_APPL_CU_PHY_H_
#define _VTSS_APPL_CU_PHY_H_

int atom12_board_init(int argc, const char **argv, vtss_appl_board_t *board);
int tesla_board_init(int argc, const char **argv, vtss_appl_board_t *board);
int elise_board_init(int argc, const char **argv, vtss_appl_board_t *board);
int nano_board_init(int argc, const char **argv, vtss_appl_board_t *board);
int viper_board_init(int argc, const char **argv, vtss_appl_board_t *board);

void vtss_board_phy_init(vtss_appl_board_t *board);

vtss_rc miim_read(const vtss_inst_t    inst,
                  const vtss_port_no_t port_no,
                  const u8             addr,
                  u16                  *const value);

vtss_rc miim_write(const vtss_inst_t    inst,
                   const vtss_port_no_t port_no,
                   const u8             addr,
                   const u16            value);

#if defined(VTSS_CHIP_10G_PHY)
vtss_rc mmd_read(const vtss_inst_t     inst,
                 const vtss_port_no_t  port_no,
                 const u8              mmd,
                 const u16             addr,
                 u16                   *const value);

vtss_rc mmd_write(const vtss_inst_t     inst,
                  const vtss_port_no_t  port_no,
                  const u8              mmd,
                  const u16             addr,
                  const u16             value);

vtss_rc mmd_read_inc(const vtss_inst_t     inst,
                     const vtss_port_no_t  port_no,
                     const u8              mmd,
                     const u16             addr,
                     u16                   *buf,
                     u8                    count);
#endif /* VTSS_CHIP_10G_PHY */
#endif /* _VTSS_APPL_CU_PHY_H_ */
