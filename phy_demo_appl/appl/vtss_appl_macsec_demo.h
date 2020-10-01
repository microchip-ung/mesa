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


*/

#ifndef _VTSS_APPL_MACSEC_DEMO_H_
#define _VTSS_APPL_MACSEC_DEMO_H_

#ifdef VTSS_FEATURE_MACSEC

typedef struct explicit_sci_struct {
    BOOL                 explicit_sci_flag;
    vtss_macsec_sci_t    explicit_sci;
} vtss_explicit_sci_t;

void vtss_basic_secy(vtss_inst_t          inst,
                     vtss_port_no_t       macsec_physical_port,
                     vtss_macsec_port_t  *_macsec_port,
                     vtss_mac_t          *_port_macaddress,
                     vtss_explicit_sci_t *explicit_sci_rx,
                     BOOL                 encrypt_256);

void vtss_basic_secy_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port);


void vtss_single_secy_sample_system_create(
    vtss_inst_t          inst,
    vtss_port_no_t       port_no,
    vtss_macsec_port_t  *_macsec_port,
    vtss_mac_t          *_port_macaddress,
    vtss_macsec_sci_t   *_peer_sci,
    vtss_explicit_sci_t *explicit_sci_rx,
    BOOL                 encrypt_256,
    BOOL                 confidentiality);


void vtss_single_secy_sample_system_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port,
    const vtss_mac_t         *port_macaddress,
    const vtss_macsec_sci_t  *peer_sci);

vtss_rc sak_update_hash_key(vtss_macsec_sak_t * sak);


void vtss_appl_macsec_demo_menu(vtss_inst_t    inst, vtss_port_no_t  port_no);

#ifdef KAT_TEST_ENABLE_1G
vtss_rc vtss_phy_macsec_kat_test(vtss_inst_t             inst,
                                 const vtss_port_no_t    port_no,
                                 u8                     *egr_fail,
                                 u8                     *ing_fail);
#endif


#endif /* VTSS_FEATURE_MACSEC  */

#endif /* _VTSS_APPL_MACSEC_DEMO_H_ */
