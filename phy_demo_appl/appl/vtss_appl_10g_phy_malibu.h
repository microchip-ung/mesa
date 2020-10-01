/*


 Copyright (c) 2004-2020 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 *****************************************************************************************
* Revision 0.1  2018/06/27 sunilp
* 0.1 is the first version for the Malibu family of products (VSC8254/57/58(-xx))
 *****************************************************************************************

*/

#ifndef _VTSS_APPL_10G_PHY_H_
#define _VTSS_APPL_10G_PHY_H_
//int atom12_board_init(int argc, const char **argv, vtss_appl_board_t *board);
//int tesla_board_init(int argc, const char **argv, vtss_appl_board_t *board);
//int elise_board_init(int argc, const char **argv, vtss_appl_board_t *board);
//int nano_board_init(int argc, const char **argv, vtss_appl_board_t *board);
//int viper_board_init(int argc, const char **argv, vtss_appl_board_t *board);
int malibu_board_init(int argc, const char **argv, vtss_appl_board_t *board);

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
