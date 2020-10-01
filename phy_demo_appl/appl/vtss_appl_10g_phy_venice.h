// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/*
 *****************************************************************************************
* Revision 0.1  2018/07/27 sunilp
* 0.1 is the first version for the Venice family of products (VSC8489/90/91(-xx))
 *****************************************************************************************

*/

#ifndef _VTSS_APPL_10G_PHY_H_
#define _VTSS_APPL_10G_PHY_H_
//int atom12_board_init(int argc, const char **argv, vtss_appl_board_t *board);
//int tesla_board_init(int argc, const char **argv, vtss_appl_board_t *board);
//int elise_board_init(int argc, const char **argv, vtss_appl_board_t *board);
//int nano_board_init(int argc, const char **argv, vtss_appl_board_t *board);
//int viper_board_init(int argc, const char **argv, vtss_appl_board_t *board);
int venice_board_init(int argc, const char **argv, vtss_appl_board_t *board);

void vtss_board_phy_init(vtss_appl_board_t *board);

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
#endif /* _VTSS_APPL_10G_PHY_H_ */
