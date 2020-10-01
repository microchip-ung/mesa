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
#include "vtss_api.h"   // For board initialization
#include "vtss_appl.h"  // For vtss_board_t
#include "vtss_port_api.h"
#include "vtss_macsec_api.h"

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
extern FILE   *fp;
#endif

#ifdef VTSS_FEATURE_MACSEC
#include "vtss_macsec_api.h"
#include <openssl/aes.h>

#include "vtss_appl_macsec_demo.h"

#define EVAL_BOARD_MACSEC_CAPABLE

#define VTSS_RC_TEST(X)           \
{                                 \
    if ((X) != VTSS_RC_OK) {      \
        printf("Failed: "#X"\n"); \
        abort();                  \
    }                             \
}


#endif


// Assuming that if this one is not defined, the others are not defined either
// byte order is handled by the API
#ifndef ETHERTYPE_IEEE_802_1_AE
#define ETHERTYPE_IEEE_IPV4       0x0800
#define ETHERTYPE_IEEE_ARP        0x0806
#define ETHERTYPE_IEEE_WOL        0x0842
#define ETHERTYPE_IEEE_VLAN_TAG   0x8100
#define ETHERTYPE_IEEE_IPV6       0x86DD
#define ETHERTYPE_IEEE_MPLS_UNI   0x8847
#define ETHERTYPE_IEEE_MPLS_MULTI 0x8848
#define ETHERTYPE_IEEE_JUMBO      0x8870
#define ETHERTYPE_IEEE_802_1_AG   0x8902
#define ETHERTYPE_IEEE_802_1_X    0x888E
#define ETHERTYPE_IEEE_802_1_AE   0x88E5
#define ETHERTYPE_IEEE_802_1_AH   0x88E7
#define ETHERTYPE_IEEE_PTP_1588   0x88F7
#define ETHERTYPE_IEEE_802_1_AD   0x88A8
#endif

extern BOOL get_valid_port_no(vtss_port_no_t *  port_no, char port_no_str[]);

#ifdef EVAL_BOARD_MACSEC_CAPABLE

/*
 * Test scenario:
 *
 * This is the simplest possible test scenario where a MACsec port is
 * communicating with a single MACsec peer.
 *
 * This test case covers the configuration of the MACsec port, while we pretend
 * that a MACsec peer is connected to the MACsec port.
 *
 *    +-----------+     +-----------+
 *    |MACsec-Peer|<--->|MACsec-port|
 *    +-----------+     +-----------+
 *
 * - One CA is created comprising the MACsec port, and the MACsec peer
 * - 802.1X frames are associated with the uncontrolled port
 * - All other traffic is treated as MACsec traffic
 * - Traffic which is not recognized as MACsec traffic or 802.1X traffic is
 *   dropped.
 * */

#ifndef KAT_TEST_ENABLE_1G // This function is defined in KAT_TEST also
#if 0
vtss_rc sak_update_hash_key(vtss_macsec_sak_t * sak)
{
    AES_KEY aes_key;
    char null_data[] = {0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0};

    const unsigned char aes_key_128[] = {0xad,0x7a,0x2b,0xd0,0x3e,0xac,0x83,0x5a,0x6f,0x62,0x0f,0xdc,0xb5,0x06,0xb3,0x45}; // 128-bit key
    const unsigned char hash_key_128[] = {0x73,0xa2,0x3d,0x80,0x12,0x1d,0xe2,0xd5,0xa8,0x50,0x25,0x3f,0xcf,0x43,0x12,0x0e}; // Hash is 128-bits
    const unsigned char aes_key_256[] = {0xe3,0xc0,0x8a,0x8f,0x06,0xc6,0xe3,0xad,0x95,0xa7,0x05,0x57,0xb2,0x3f,0x75,0x48,
                                         0x3c,0xe3,0x30,0x21,0xa9,0xc7,0x2b,0x70,0x25,0x66,0x62,0x04,0xc6,0x9c,0x0b,0x72}; // 256-bit key
    const unsigned char hash_key_256[] = {0x28,0x6d,0x73,0x99,0x4e,0xa0,0xba,0x3c,0xfd,0x1f,0x52,0xbf,0x06,0xa8,0xac,0xf2}; // Hash is 128bits

    if (sak->len == 16) {
        memcpy( sak->buf,  aes_key_128,  sak->len);  /* 128 Bit Key */
        AES_set_encrypt_key(sak->buf, (sak->len * 8), &aes_key);
    } else if (sak->len == 32) {
        memcpy(sak->buf,  aes_key_256,  sak->len);  /* 128 Bit Key */
        AES_set_encrypt_key(sak->buf, (sak->len * 8), &aes_key);
    } else {
        return VTSS_RC_ERROR;

    }

    AES_ecb_encrypt((const unsigned char *)null_data,
                    (unsigned char *)sak->h_buf,
                    &aes_key,
                    AES_ENCRYPT);

    return VTSS_RC_OK;
}
#else
vtss_rc sak_update_hash_key(vtss_macsec_sak_t * sak)
{
    // This function is forcing the usage of only 2 Keys.  It is either 128bit or 256bit, but these keys are static.
    // AES_KEY aes_key;
    // char null_data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // key  = 'ad7a2bd03eac835a6f620fdcb506b345'; % 128-bit key
    // hkey = '73a23d80121de2d5a850253fcf43120e';
    // key  = 'e3c08a8f06c6e3ad95a70557b23f75483ce33021a9c72b7025666204c69c0b72'; % 256-bit key
    // hkey = '286d73994ea0ba3cfd1f52bf06a8acf2';
    //rev const unsigned char aes_key_128[] = {0x45,0xb3,0x06,0xb5,0xdc,0x0f,0x62,0x6f,0x5a,0x83,0xac,0x3e,0xd0,0x2b,0x7a,0xad}; // 128-bit key
    //rev const unsigned char hash_key_128[] = {0x0e,0x12,0x43,0xcf,0x3f,0x25,0x50,0xa8,0xd5,0xe2,0x1d,0x12,0x80,0x3d,0xa2,0x73}; // Hash is 128-bits
    //const unsigned char aes_key_128[] = {0xad,0x7a,0x2b,0xd0,0x3e,0xac,0x83,0x5a,0x6f,0x62,0x0f,0xdc,0xb5,0x06,0xb3,0x45}; // 128-bit key
    //const unsigned char hash_key_128[] = {0x73,0xa2,0x3d,0x80,0x12,0x1d,0xe2,0xd5,0xa8,0x50,0x25,0x3f,0xcf,0x43,0x12,0x0e}; // Hash is 128-bits

    const unsigned char aes_key_128[] = {0xad,0x7a,0x2b,0xd0,0x3e,0xac,0x83,0x5a,0x6f,0x62,0x0f,0xdc,0xb5,0x06,0xb3,0x45}; // 128-bit key
    const unsigned char hash_key_128[] = {0x73,0xa2,0x3d,0x80,0x12,0x1d,0xe2,0xd5,0xa8,0x50,0x25,0x3f,0xcf,0x43,0x12,0x0e}; // Hash is 128-bits
    const unsigned char aes_key_256[] = {0xe3,0xc0,0x8a,0x8f,0x06,0xc6,0xe3,0xad,0x95,0xa7,0x05,0x57,0xb2,0x3f,0x75,0x48,
                                         0x3c,0xe3,0x30,0x21,0xa9,0xc7,0x2b,0x70,0x25,0x66,0x62,0x04,0xc6,0x9c,0x0b,0x72}; // 256-bit key
    const unsigned char hash_key_256[] = {0x28,0x6d,0x73,0x99,0x4e,0xa0,0xba,0x3c,0xfd,0x1f,0x52,0xbf,0x06,0xa8,0xac,0xf2}; // Hash is 128bits

    /* 128 Bit Encryption */
    if (sak->len == 16) {
        //AES_set_encrypt_key(sak->buf, 128, &aes_key);
        memcpy( sak->buf,  aes_key_128,  sak->len);  /* 128 Bit Key */
        memcpy( sak->h_buf,  hash_key_128,  sak->len);

    /* 256 Bit Encryption */
    } else if (sak->len == 32) {
        //AES_set_encrypt_key(sak->buf, 256, &aes_key);
        memcpy( sak->buf,  aes_key_256,  sak->len);  /* 128 Bit Key */
        memcpy( sak->h_buf,  hash_key_256,  16);

    } else {
        return VTSS_RC_ERROR;

    }

    // The null_data and encryption key are used to generate the h_buf, but that is already given above
    //AES_ecb_encrypt((const unsigned char *)null_data, (unsigned char *)sak->h_buf, &aes_key, AES_ENCRYPT);

    return VTSS_RC_OK;
}
#endif
#endif   /*   KAT_TEST_ENABLE_1G   */


/*  *************************************************************************************************** */
/*                          Initialize the PHYSCIAL Port of the PHY to process MACSEC Traffic           */
/*  *************************************************************************************************** */
// Warning uses abort as error handling strategy
void vtss_basic_secy(vtss_inst_t          inst,
                     vtss_port_no_t       macsec_physical_port,
                     vtss_macsec_port_t  *in_macsec_port,
                     vtss_mac_t          *in_port_macaddress,
                     vtss_explicit_sci_t *explicit_sci_rx,
                     BOOL                 encrypt_256
)
{
    vtss_rc    rc = 0;
    //const vtss_macsec_vport_id_t   macsec_virtual_port  = 24193;
    const vtss_macsec_vport_id_t   macsec_virtual_port  = 1;           //jbh
    const vtss_macsec_service_id_t macsec_service_id    = 0;
    const vtss_macsec_port_t       macsec_port = {
        .port_no    = macsec_physical_port,
        .service_id = macsec_service_id,
        .port_id    = macsec_virtual_port
    };

    const vtss_mac_t port_macaddress = { .addr = {0, 0, 0, 0, 0, 0xAA}};   /* Local Port MAC Addr */
    const vtss_mac_t peer_macaddress = { .addr = {0, 0, 0, 0, 0, 0xBB}};   /* Peer MAC Addr       */

    // Initialize the MACsec block
    {
        vtss_macsec_init_t init_data = { .enable = TRUE,
                                         .dis_ing_nm_macsec_en = TRUE,
                                         .mac_conf.lmac.dis_length_validate = FALSE,
                                         .mac_conf.hmac.dis_length_validate = FALSE,
                                         .bypass = MACSEC_INIT_BYPASS_NONE }; /* MACSEC_INIT_BYPASS_ENABLE or MACSEC_INIT_BYPASS_DISABLE */

        printf(" Inst: %p, macsec_physical_port: %d, enable: %x\n", inst, macsec_physical_port, init_data.enable);

        if ((rc = vtss_macsec_init_set(inst, macsec_physical_port, &init_data)) != VTSS_RC_OK) {
            printf("vtss_macsec_init_set: rc:%d;  INST: %p; port_no: %d, enable: %x\n", rc, inst, macsec_physical_port, init_data.enable);
            switch(rc) {
            case VTSS_RC_OK:
                break;
            case VTSS_RC_ERROR:
                printf("vtss_macsec_init_set: rc:VTSS_RC_ERROR  \n" );
                break;
            case VTSS_RC_ERR_MACSEC_NOT_ENABLED:
                printf("vtss_macsec_init_set: rc:VTSS_RC_ERR_MACSEC_NOT_ENABLED \n" );
                break;
            default:
                printf("vtss_macsec_init_set: ERROR! rc:%d \n", rc);
            }
        }

        // Use the default rules to drop all non-matched traffic
        // Setup default rules to by-pass traffic classified as control frames
        vtss_macsec_default_action_policy_t default_action_policy = {
            .ingress_non_control_and_non_macsec = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .ingress_control_and_non_macsec     = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .ingress_non_control_and_macsec     = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .ingress_control_and_macsec         = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .egress_control                     = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .egress_non_control                 = VTSS_MACSEC_DEFAULT_ACTION_BYPASS
        };

        rc = vtss_macsec_default_action_set(inst, macsec_physical_port,
                                                    &default_action_policy);

        printf(" Default Action Set to VTSS_MACSEC_DEFAULT_ACTION_BYPASS;  rc = %d\n", rc);
        switch(rc) {
        case VTSS_RC_OK:
            break;
        case VTSS_RC_ERROR:
            printf("vtss_macsec_default_action_set: rc:VTSS_RC_ERROR  \n" );
            break;
        case VTSS_RC_ERR_MACSEC_NOT_ENABLED:
            printf("vtss_macsec_default_action_set: rc:VTSS_RC_ERR_MACSEC_NOT_ENABLED \n" );
            break;
        default:
            printf("vtss_macsec_default_action_set: ERROR! rc:%d \n", rc);
        }
    }


/*  *************************************************************************************************** */
/*                               CREATE a NEW MACSEC SEC_Y                                              */
/*  *************************************************************************************************** */
    {
        vtss_macsec_secy_conf_t macsec_port_conf;
        // Start by adding a SecY
        macsec_port_conf.validate_frames        = VTSS_MACSEC_VALIDATE_FRAMES_STRICT;
        macsec_port_conf.replay_protect         = FALSE;
        macsec_port_conf.replay_window          = 10;
        macsec_port_conf.protect_frames         = TRUE;

        if (explicit_sci_rx->explicit_sci_flag) {
            macsec_port_conf.always_include_sci     = TRUE;       // Must be TRUE for Explicit SCI, adds bytes for Specific SCI

            printf(" MACSEC Sec_Y Explicit SCI = TRUE; always_include_sci = TRUE; 16 Byte SECTAG\n");
        } else {
         // _8BYTE_SECTAG_
            macsec_port_conf.always_include_sci     = FALSE;    // FALSE = Implicit SCI only, no room in pkt provided for Specifying SCI
            printf(" MACSEC Sec_Y Explicit SCI = FALSE; always_include_sci = FALSE; 8 Byte SECTAG\n");

         // _16BYTE_SECTAG_
         //   macsec_port_conf.always_include_sci     = TRUE;       // FALSE = Implicit SCI, adds bytes but SCI not specified
         //   printf(" MACSEC Sec_Y Explicit SCI = FALSE; always_include_sci = TRUE; 16 Byte SECTAG\n");
        }

	if (macsec_port_conf.always_include_sci) {
            printf(" 16 BYTE SECTAG: MACSEC Sec_Y Explicit SCI: %x; always_include_sci to: %x \n", explicit_sci_rx->explicit_sci_flag, macsec_port_conf.always_include_sci);
        } else {
            printf(" 8 BYTE SECTAG: MACSEC Sec_Y Explicit SCI: %x; always_include_sci to: %x \n", explicit_sci_rx->explicit_sci_flag, macsec_port_conf.always_include_sci);
        }

        macsec_port_conf.use_es                 = FALSE;
        macsec_port_conf.use_scb                = FALSE;
        macsec_port_conf.confidentiality_offset = 0;
        macsec_port_conf.mac_addr               = peer_macaddress;

        if (encrypt_256) {
            macsec_port_conf.current_cipher_suite   = VTSS_MACSEC_CIPHER_SUITE_GCM_AES_256;
        } else {
            macsec_port_conf.current_cipher_suite   = VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128;
        }

        rc = vtss_macsec_secy_conf_add(inst, macsec_port, &macsec_port_conf);
        printf(" New MACSEC Sec_Y Created; rc = %d \n", rc);
        switch(rc) {
        case VTSS_RC_OK:
            break;
        case VTSS_RC_ERROR:
            printf("vtss_macsec_default_action_set: rc:VTSS_RC_ERROR  \n" );
            break;
        case VTSS_RC_ERR_MACSEC_NOT_ENABLED:
            printf("vtss_macsec_default_action_set: rc:VTSS_RC_ERR_MACSEC_NOT_ENABLED \n" );
            break;
        default:
            printf("vtss_macsec_default_action_set: ERROR! rc:%d \n", rc);
        }


/*  *************************************************************************************************** */
/*                               CONTROLLED PORT SETUP - EGRESS                                         */
/*  *************************************************************************************************** */
        // No encapsulation is used. Just match everything, but keep the
        // priority lower than the rule matching traffic for the uncontrolled
        // port. In other words, if it is not control traffic, then it should
        // be considered MACsec traffic.
        vtss_macsec_match_pattern_t pattern_ctrl_egr = {
            .priority            = VTSS_MACSEC_MATCH_PRIORITY_LOW,     // 12
            .match               = VTSS_MACSEC_MATCH_ETYPE,            // 0x0004
            .is_control          = FALSE,
            .has_vlan_tag        = FALSE,
            .has_vlan_inner_tag  = FALSE,
            .etype               = ETHERTYPE_IEEE_IPV4,   // 0x0800
            .vid                 = 0,
            .vid_inner           = 0,
            .hdr                 = "",
            .hdr_mask            = 0,
            .src_mac             = port_macaddress,
            .dest_mac            = peer_macaddress
        };


        rc = vtss_macsec_pattern_set(inst, macsec_port, VTSS_MACSEC_DIRECTION_EGRESS,
                                                   VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT, &pattern_ctrl_egr);

        printf(" EGRESS CTRL Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 0800; rc=%d\n", rc);



/*  *************************************************************************************************** */
/*                               CONTROLLED PORT SETUP - INGRESS                                        */
/*  *************************************************************************************************** */
        // No encapsulation is used. Just match everything, but keep the
        // priority lower than the rule matching traffic for the uncontrolled
        // port. In other words, if it is not control traffic, then it should
        // be considered MACsec traffic.
        vtss_macsec_match_pattern_t pattern_ctrl_ingr = {
            .priority            = VTSS_MACSEC_MATCH_PRIORITY_LOW,        // 12
            .match               = VTSS_MACSEC_MATCH_ETYPE,               // 0x0004
            .is_control          = FALSE,
            .has_vlan_tag        = FALSE,
            .has_vlan_inner_tag  = FALSE,
            .etype               = ETHERTYPE_IEEE_802_1_AE,   // 0x88e5
            .vid                 = 0,     // Old 64
            .vid_inner           = 0,
            .hdr                 = "",
            .hdr_mask            = 0,
            .src_mac             = port_macaddress,
            .dest_mac            = peer_macaddress
        };


        // Associate the pattern with the controlled MACsec port
        rc = vtss_macsec_pattern_set(inst, macsec_port, VTSS_MACSEC_DIRECTION_INGRESS,
                                                   VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT, &pattern_ctrl_ingr);

        printf(" INGRESS CTRL Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 88e5 ; rc=%d\n", rc);


/*  *************************************************************************************************** */
/*                               UNCONTROLLED PORT SETUP - INGRESS                                      */
/*  *************************************************************************************************** */
        // All traffic which is not vlan traffic, and have ether-type 0x888E
        // must be associated with the controlled port.
        vtss_macsec_match_pattern_t pattern_unctrl_ingr = {
            .priority            = VTSS_MACSEC_MATCH_PRIORITY_HIGHEST,  // 0
            .match               = VTSS_MACSEC_MATCH_ETYPE,         // 0x0004
            .is_control          = TRUE,
            .has_vlan_tag        = FALSE,
            .has_vlan_inner_tag  = FALSE,
            .etype               = ETHERTYPE_IEEE_802_1_X,    // 0x888e
            .vid                 = 0,
            .vid_inner           = 0,
            .hdr                 = "",
            .hdr_mask            = 0,
            .src_mac             = port_macaddress,
            .dest_mac            = peer_macaddress
        };

        // Associate the pattern with the uncontrolled MACsec port
        rc = vtss_macsec_pattern_set(inst, macsec_port,
                                             VTSS_MACSEC_DIRECTION_INGRESS,
                                             VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT,
                                             &pattern_unctrl_ingr);

        printf(" INGRESS UNCONTROLLED Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 888e; rc=%d \n", rc);

/*  *************************************************************************************************** */
/*                               UNCONTROLLED PORT SETUP - EGRESS                                       */
/*  *************************************************************************************************** */
        vtss_macsec_match_pattern_t pattern_unctrl_egr = {
            .priority            = VTSS_MACSEC_MATCH_PRIORITY_HIGHEST,  // 0
            .match               = VTSS_MACSEC_MATCH_ETYPE,             // 0x0004
            .is_control          = TRUE,
            .has_vlan_tag        = FALSE,
            .has_vlan_inner_tag  = FALSE,
            .etype               = ETHERTYPE_IEEE_802_1_X,    // 0x888e
            .vid                 = 0,
            .vid_inner           = 0,
            .hdr                 = "",
            .hdr_mask            = 0,
            .src_mac             = port_macaddress,
            .dest_mac            = peer_macaddress
        };

        rc = vtss_macsec_pattern_set(inst, macsec_port,
                                     VTSS_MACSEC_DIRECTION_EGRESS, VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT,
                                     &pattern_unctrl_egr);

        printf(" EGRESS UNCONTROLLED Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 888e;  rc=%d \n", rc);

        // Enable the SecY
        rc = vtss_macsec_secy_controlled_set(inst, macsec_port, TRUE);
        printf(" Enable Sec_Y; rc=0x%x \n",rc);
    }

    memcpy(in_macsec_port,     &macsec_port,     sizeof macsec_port);
    memcpy(in_port_macaddress, &port_macaddress, sizeof port_macaddress);
}

// Warning uses abort as error handling strategy
void vtss_single_secy_sample_system_create(vtss_inst_t          inst,
                                           vtss_port_no_t       port_no,
                                           vtss_macsec_port_t  *macsec_port,
                                           vtss_mac_t          *port_macaddress,
                                           vtss_macsec_sci_t   *peer_sci,
                                           vtss_explicit_sci_t *explicit_sci_rx,
                                           BOOL                 encrypt_256,
                                           BOOL                 confidentiality
)
{
    vtss_rc   rc = 0;
    const vtss_mac_t peer_macaddress = { .addr = {0, 0, 0, 0, 0, 0xBB}};
    const vtss_port_no_t macsec_physical_port = port_no;
    vtss_macsec_sci_t sci_rx;

    u16   assoc_no = 0;      // Assn Number  0 - 3
    u32   next_pn = 0x000001;    // Next Pkt Num
    u32   lowest_pn = 0x200000;    // Lowest Pkt Num = 2million

    vtss_basic_secy(inst, macsec_physical_port, macsec_port, port_macaddress, explicit_sci_rx, encrypt_256);

    const vtss_macsec_sci_t implicit_sci_rx = { .mac_addr = peer_macaddress,
                                                .port_id  = macsec_port->port_id};

    if (explicit_sci_rx->explicit_sci_flag) {
        // Explicit SCI - Secure Channel Identifier - Not MAC Addr+Port_id
        // Explicit SCI - '12.15.35.24.c0.89-5e.81'

        // sci_rx = explicit_sci_rx->explicit_sci;

        sci_rx = implicit_sci_rx;

        printf ("Explicit SCI_Rx MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x::0x%04x\n",
                   sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1], sci_rx.mac_addr.addr[2],
                   sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5],
                   sci_rx.port_id );
    } else {
        // Implicit SCI - Secure Channel Identifier - Mac Addr+Port_id
        sci_rx = implicit_sci_rx;

        printf ("Implicit SCI_Rx MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x::0x%04x\n",
                   sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1], sci_rx.mac_addr.addr[2],
                   sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5],
                   sci_rx.port_id );

    }

    printf ("MACsec Phys Port: %d,  Service_id: 0x%x , MACsec Virtual Port (port_id): %d\n",
                   macsec_port->port_no, macsec_port->service_id, macsec_port->port_id );

    printf ("MACsec Port: %d,  Port Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", macsec_physical_port,
                   port_macaddress->addr[0], port_macaddress->addr[1], port_macaddress->addr[2],
                   port_macaddress->addr[3], port_macaddress->addr[4], port_macaddress->addr[5] );

    printf ("Peer MACsec Port_id: %d,  Peer Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", macsec_port->port_id,
                   peer_macaddress.addr[0], peer_macaddress.addr[1], peer_macaddress.addr[2],
                   peer_macaddress.addr[3], peer_macaddress.addr[4], peer_macaddress.addr[5] );

    printf("EGRESS SETUP: Installing Key on HW on Egress Side \n");
    { // Add secure TX channels and a secure association
        vtss_macsec_sak_t sak_tx_sa_0;

        // Add a new TX secure channel
        rc = vtss_macsec_tx_sc_set(inst, *macsec_port);
        printf("vtss_macsec_tx_sc_set:  rc: %d \n", rc);

        if (encrypt_256) {
            // create a zero-key for 256bit cipher suite
            sak_tx_sa_0.len = 32;
        } else {
            // create a zero-key for 128bit cipher suite
            sak_tx_sa_0.len = 16;
        }

        // Update the hash key in the SAK before the key is installed in HW
        rc = sak_update_hash_key(&sak_tx_sa_0);
        printf("sak_update_hash_key  rc: %d \n", rc);

        if ((sak_tx_sa_0.len == 16) || (sak_tx_sa_0.len == 32)) {
            printf ("SAK: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_tx_sa_0.buf[0], sak_tx_sa_0.buf[1], sak_tx_sa_0.buf[2], sak_tx_sa_0.buf[3],
                   sak_tx_sa_0.buf[4], sak_tx_sa_0.buf[5], sak_tx_sa_0.buf[6], sak_tx_sa_0.buf[7],
                   sak_tx_sa_0.buf[8], sak_tx_sa_0.buf[9], sak_tx_sa_0.buf[10], sak_tx_sa_0.buf[11],
                   sak_tx_sa_0.buf[12], sak_tx_sa_0.buf[13], sak_tx_sa_0.buf[14], sak_tx_sa_0.buf[15]);
        }
        if (sak_tx_sa_0.len == 32) {
            printf ("SAK: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_tx_sa_0.buf[16], sak_tx_sa_0.buf[17], sak_tx_sa_0.buf[18], sak_tx_sa_0.buf[19],
                   sak_tx_sa_0.buf[20], sak_tx_sa_0.buf[21], sak_tx_sa_0.buf[22], sak_tx_sa_0.buf[23],
                   sak_tx_sa_0.buf[24], sak_tx_sa_0.buf[25], sak_tx_sa_0.buf[26], sak_tx_sa_0.buf[27],
                   sak_tx_sa_0.buf[28], sak_tx_sa_0.buf[29], sak_tx_sa_0.buf[30], sak_tx_sa_0.buf[31]);
        }

        printf ("SAK: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_tx_sa_0.h_buf[0], sak_tx_sa_0.h_buf[1], sak_tx_sa_0.h_buf[2], sak_tx_sa_0.h_buf[3],
                   sak_tx_sa_0.h_buf[4], sak_tx_sa_0.h_buf[5], sak_tx_sa_0.h_buf[6], sak_tx_sa_0.h_buf[7],
                   sak_tx_sa_0.h_buf[8], sak_tx_sa_0.h_buf[9], sak_tx_sa_0.h_buf[10], sak_tx_sa_0.h_buf[11],
                   sak_tx_sa_0.h_buf[12], sak_tx_sa_0.h_buf[13], sak_tx_sa_0.h_buf[14], sak_tx_sa_0.h_buf[15]);
        // install the key in HW on the egress side

        // install the key in HW on the egress side
        rc = vtss_macsec_tx_sa_set(inst, *macsec_port,
                                           assoc_no,        // associations number
                                           next_pn,         // next_pn,
                                           confidentiality, // confidentiality,
                                           &sak_tx_sa_0);

        // install the key in HW on the egress side
        printf("Activiating Key on HW Egress: rc; %d; Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Next_PN: 0x%x, Service_Id: 0x%x, confid: 0x%x \n",
                   rc, macsec_port->port_no, macsec_port->port_id, assoc_no, next_pn, macsec_port->service_id, confidentiality );

        rc = vtss_macsec_tx_sa_activate(inst, *macsec_port, assoc_no);
    }

    printf("INGRESS SETUP: Installing Key on HW on Ingress Side;  rc=%d \n", rc);

    { // Add a MACsec peer
        vtss_macsec_sak_t sak_rx_sa_0;
        vtss_macsec_sak_t sak_rx_sa_1;

      // Add a new RX secure channel
      //  printf("Adding MACsec Peer\n");
        rc = vtss_macsec_rx_sc_add(inst, *macsec_port, &sci_rx);
        printf("vtss_macsec_rx_sc_add;  rc=%d \n", rc);

        // Add two RX SA's
        if (encrypt_256) {
            sak_rx_sa_0.len = 32;
            sak_rx_sa_1.len = 32;
        } else {
            sak_rx_sa_0.len = 16;
            sak_rx_sa_1.len = 16;
        }


        // Update the hash key in the SAK before the key is installed in HW
        printf("Adding Two Hashes - Secure Association 0 and 1 \n");
        rc = sak_update_hash_key(&sak_rx_sa_0);
        printf("sak_update_hash_key; sak_rx_sa_0;  rc: %d \n", rc);
        rc = sak_update_hash_key(&sak_rx_sa_1);
        printf("sak_update_hash_key; sak_rx_sa_1;  rc: %d \n", rc);

        printf("Setup Key_0: Activating Key on HW on Ingress Side - Assoc: 0\n");
        //printf("SA Set \n");

        if ((sak_rx_sa_0.len == 16) || (sak_rx_sa_0.len == 32)) {
            printf ("SAK_SA0: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_0.buf[0], sak_rx_sa_0.buf[1], sak_rx_sa_0.buf[2], sak_rx_sa_0.buf[3],
                   sak_rx_sa_0.buf[4], sak_rx_sa_0.buf[5], sak_rx_sa_0.buf[6], sak_rx_sa_0.buf[7],
                   sak_rx_sa_0.buf[8], sak_rx_sa_0.buf[9], sak_rx_sa_0.buf[10], sak_rx_sa_0.buf[11],
                   sak_rx_sa_0.buf[12], sak_rx_sa_0.buf[13], sak_rx_sa_0.buf[14], sak_rx_sa_0.buf[15]);
        }
        if (sak_rx_sa_0.len == 32) {
            printf ("SAK_SA0: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_0.buf[16], sak_rx_sa_0.buf[17], sak_rx_sa_0.buf[18], sak_rx_sa_0.buf[19],
                   sak_rx_sa_0.buf[20], sak_rx_sa_0.buf[21], sak_rx_sa_0.buf[22], sak_rx_sa_0.buf[23],
                   sak_rx_sa_0.buf[24], sak_rx_sa_0.buf[25], sak_rx_sa_0.buf[26], sak_rx_sa_0.buf[27],
                   sak_rx_sa_0.buf[28], sak_rx_sa_0.buf[29], sak_rx_sa_0.buf[30], sak_rx_sa_0.buf[31]);
        }

        printf ("SAK_SA0: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_0.h_buf[0], sak_rx_sa_0.h_buf[1], sak_rx_sa_0.h_buf[2], sak_rx_sa_0.h_buf[3],
                   sak_rx_sa_0.h_buf[4], sak_rx_sa_0.h_buf[5], sak_rx_sa_0.h_buf[6], sak_rx_sa_0.h_buf[7],
                   sak_rx_sa_0.h_buf[8], sak_rx_sa_0.h_buf[9], sak_rx_sa_0.h_buf[10], sak_rx_sa_0.h_buf[11],
                   sak_rx_sa_0.h_buf[12], sak_rx_sa_0.h_buf[13], sak_rx_sa_0.h_buf[14], sak_rx_sa_0.h_buf[15]);

        //printf ("SCI_Rx MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x::0x%04x\n",
        //           sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1], sci_rx.mac_addr.addr[2],
        //           sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5],
        //           sci_rx.port_id );

        assoc_no = 0;      // Assn Number
        lowest_pn = 0;     // Lowest Pkt Num
        printf("Setting up RX sa_0 Assoc_No: %d, lowest_pn: %d \n", assoc_no, lowest_pn);
        rc = vtss_macsec_rx_sa_set(inst, *macsec_port,
                                           &sci_rx, // identify which SC the SA belongs to
                                           assoc_no,       // associations number
                                           lowest_pn,       // lowest_pn,
                                           &sak_rx_sa_0);

        printf("vtss_macsec_rx_sa_set  rc: %d \n", rc);

        rc = vtss_macsec_rx_sa_activate(inst, *macsec_port, &sci_rx, assoc_no);
        printf("vtss_macsec_rx_sa_activate   rc: %d \n", rc);

        // install the key in HW on the egress side
        printf("Activiating Key_0 on HW Inress: Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Lowest_PN: 0x%x, SCI: 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x - 0x%x \n",
                   macsec_port->port_no, macsec_port->port_id, assoc_no, lowest_pn, sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1],
                   sci_rx.mac_addr.addr[2], sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5], sci_rx.port_id );

        printf("Setup Key_1: Activating Key on HW on Ingress Side - Assoc: 1\n");

        printf("Setup Key_1: Activating Key on HW on Ingress Side - Assoc: 1\n");

        if ((sak_rx_sa_0.len == 16) || (sak_rx_sa_0.len == 32)) {
            printf ("SAK_SA1: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_1.buf[0], sak_rx_sa_1.buf[1], sak_rx_sa_1.buf[2], sak_rx_sa_1.buf[3],
                   sak_rx_sa_1.buf[4], sak_rx_sa_1.buf[5], sak_rx_sa_1.buf[6], sak_rx_sa_1.buf[7],
                   sak_rx_sa_1.buf[8], sak_rx_sa_1.buf[9], sak_rx_sa_1.buf[10], sak_rx_sa_1.buf[11],
                   sak_rx_sa_1.buf[12], sak_rx_sa_1.buf[13], sak_rx_sa_1.buf[14], sak_rx_sa_1.buf[15]);
        }
        if (sak_rx_sa_0.len == 32) {
            printf ("SAK_SA1: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_1.buf[16], sak_rx_sa_1.buf[17], sak_rx_sa_1.buf[18], sak_rx_sa_1.buf[19],
                   sak_rx_sa_1.buf[20], sak_rx_sa_1.buf[21], sak_rx_sa_1.buf[22], sak_rx_sa_1.buf[23],
                   sak_rx_sa_1.buf[24], sak_rx_sa_1.buf[25], sak_rx_sa_1.buf[26], sak_rx_sa_1.buf[27],
                   sak_rx_sa_1.buf[28], sak_rx_sa_1.buf[29], sak_rx_sa_1.buf[30], sak_rx_sa_1.buf[31]);
        }

        printf ("SAK_SA1: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_1.h_buf[0], sak_rx_sa_1.h_buf[1], sak_rx_sa_1.h_buf[2], sak_rx_sa_1.h_buf[3],
                   sak_rx_sa_1.h_buf[4], sak_rx_sa_1.h_buf[5], sak_rx_sa_1.h_buf[6], sak_rx_sa_1.h_buf[7],
                   sak_rx_sa_1.h_buf[8], sak_rx_sa_1.h_buf[9], sak_rx_sa_1.h_buf[10], sak_rx_sa_1.h_buf[11],
                   sak_rx_sa_1.h_buf[12], sak_rx_sa_1.h_buf[13], sak_rx_sa_1.h_buf[14], sak_rx_sa_1.h_buf[15]);

        assoc_no = 1;         // Assn Number
       lowest_pn = 0x2000000;     // Lowest Pkt Num
        //printf("sa_1 Assoc_No: %d, lowest_pn: %d \n", assoc_no, lowest_pn);
        rc = vtss_macsec_rx_sa_set(inst, *macsec_port,
                                           &sci_rx,      // identify which SC the SA belongs to
                                           assoc_no,     // associations number
                                           lowest_pn,    // lowest_pn,
                                           &sak_rx_sa_1);

        printf("vtss_macsec_rx_sa_set  rc: %d \n", rc);

        rc = vtss_macsec_rx_sa_activate(inst, *macsec_port, &sci_rx, assoc_no);

        printf("vtss_macsec_rx_sa_activate;  rc= %d \n", rc);
        printf("Activiating Key_1 on HW Inress: Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Lowest_PN: 0x%x, SCI: 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x - 0x%x \n",
                   macsec_port->port_no, macsec_port->port_id, assoc_no, lowest_pn, sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1],
                   sci_rx.mac_addr.addr[2], sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5], sci_rx.port_id );
    }

    memcpy(peer_sci, &sci_rx, sizeof sci_rx);
}

void vtss_basic_secy_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port
)
{
    vtss_rc   rc = 0;
    // Delete SecY
    printf(" calling vtss_macsec_secy_conf_del \n");
    rc = vtss_macsec_secy_conf_del(inst, *macsec_port);
    printf(" calling vtss_macsec_secy_conf_del: rc:0x%x \n", rc);

    // Disable the MACsec block
    printf(" calling vtss_macsec_init_set,  Enable=False \n");
    vtss_macsec_init_t deinit_data = { .enable = FALSE };
    rc = vtss_macsec_init_set(inst, macsec_port->port_no, &deinit_data);
    printf(" calling vtss_macsec_init_set: rc:%d \n", rc);
}


void vtss_single_secy_sample_system_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port,
    const vtss_mac_t         *port_macaddress,
    const vtss_macsec_sci_t  *peer_sci
)
{

    // Disable the sa
    //printf ("calling vtss_macsec_rx_sa_disable:  1\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_disable(inst,*macsec_port, peer_sci, 1));
    //printf ("calling vtss_macsec_rx_sa_disable:  0\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_disable(inst,*macsec_port, peer_sci, 0));

    // Delete peer
    //printf ("calling vtss_macsec_rx_sa_del:  1\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_del(inst, *macsec_port, peer_sci, 1));
    printf ("calling vtss_macsec_rx_sa_del:  0\n");
    VTSS_RC_TEST(vtss_macsec_rx_sa_del(inst, *macsec_port, peer_sci, 0));
    printf ("calling vtss_macsec_rx_sc_del\n");
    VTSS_RC_TEST(vtss_macsec_rx_sc_del(inst, *macsec_port, peer_sci));

    // Delete TX SA and SC
    //printf ("calling vtss_macsec_tx_sa_disable:  0\n");
    //VTSS_RC_TEST(vtss_macsec_tx_sa_disable(inst,*macsec_port, 0));
    printf ("calling vtss_macsec_tx_sa_del:  0\n");
    VTSS_RC_TEST(vtss_macsec_tx_sa_del(inst, *macsec_port, 0));
    printf ("calling vtss_macsec_tx_sc_del \n");
    VTSS_RC_TEST(vtss_macsec_tx_sc_del(inst, *macsec_port));

    printf ("calling vtss_basic_secy_destroy  \n");
    vtss_basic_secy_destroy(inst, macsec_port);

}


void vtss_appl_macsec_demo_menu(vtss_inst_t    inst, vtss_port_no_t  port_no)
{
    vtss_rc                 rc;
    u16                     value = 0;
    char                    value_str[255] = {0};
    char                    command[255] = {0};
    char                    port_no_str[255] = {0};
    BOOL enable_macsec[4] = {0};

    vtss_macsec_port_t      macsec_port[4];
    vtss_mac_t              port_macaddress[4];
    vtss_macsec_sci_t       peer_sci[4];

    memset (&macsec_port[0], 0, sizeof(vtss_macsec_port_t) * 4);
    memset (&port_macaddress[0], 0, sizeof(vtss_mac_t) * 4);
    memset (&peer_sci[0], 0, sizeof(vtss_macsec_sci_t) * 4);

          while(1) {
            printf (" \n\n");
            printf (" macsec128Exp   <port_no> - Enable MACSEC Operation: 128-bit Encryption, Explicit SCI with Static Key \n");
            printf (" macsec128Imp   <port_no> - Enable MACSEC Operation: 128-bit Encryption, Implicit SCI with Static Key \n");
            printf (" macsec256Exp   <port_no> - Enable MACSEC Operation: 256-bit Encryption, Explicit SCI with Static Key \n");
            printf (" macsec256Imp   <port_no> - Enable MACSEC Operation: 256-bit Encryption, Implicit SCI with Static Key \n");
            printf (" macsec_off     <port_no> - Disable Port for MACsec Operation \n");
            printf (" macsec_ena     <port_no> - Enable MACSEC on Port and Enable/Disable ByPass for MACsec Operation \n");
            printf (" macsec_en_event   <port_no> - Enable ALL events (Thresh & Rollover) on Port for MACsec Operation \n");
            printf (" macsec_dis_event  <port_no> - Disable ALL events (Thresh & Rollover) on Port for MACsec Operation \n");
            printf (" macsec_poll_event <port_no> - Poll for Event (Thresh or Rollover) on Port for MACsec Operation \n");
            printf (" macsec_get_thresh <port_no> - Get Seq Threshold Setting on Port for MACsec Operation \n");
            printf (" macsec_set_thresh <port_no> - Set Seq Threshold Setting on Port for MACsec Operation \n");
            printf (" macsec_frmcap     <port_no> - Enable INGRESS/EGRESS or Disable MACSEC Frame Capture \n");
            printf (" ctrl_cnt    <port_no> - Get the Sec_Y Control Counters  \n");
            printf (" unctrl_cnt  <port_no> - Get the Sec_Y Uncontrolled Counters  \n");
            printf (" cmn_cnt     <port_no> - Get the Sec_Y Common Counters  \n");
            printf (" hmac_count  <port_no> - Get the MACSEC Host MAC Counters  \n");
            printf (" lmac_count  <port_no> - Get the MACSEC Line MAC Counters  \n");
            printf (" dbg_count   <port_no> - Get the MACSEC Debug Counters  \n");
            printf (" dbg_reg_dump<port_no> - Get the MACSEC Debug Reg Dump  \n");
            printf (" fcb_dump    <port_no> - Get the MACSEC FC Buffer Reg Dump  \n");
            printf (" frm_ctl_dump<port_no> - Get the MACSEC Frame Match Handling CTRL Reg Dump  \n");
#ifdef KAT_TEST_ENABLE_1G
            printf (" kat_test <port_no> - Run KAT Test  \n");
#endif
            printf (" x - exit              - Exit to upper level menu\n");
            printf ("> ");
            rc = scanf("%s", &command[0]);

            if ((strcmp(command, "x") == 0) || (strcmp(command, "X") == 0)) {
                break;

            } else if (strcmp(command, "macsec_ena") == 0) {
                vtss_macsec_init_t    init_data;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                rc = vtss_macsec_init_get(inst, port_no, &init_data);
                printf(" Port_no: %d, Current Settings: MACSEC enable: %x,   MACSEC ByPass (0=None; 1=bypassEN; 2=bypassDIS): 0x%x\n",
                         port_no, init_data.enable, init_data.bypass);

                printf ("\nPort_No: %d, MACSEC Enable/Disable? (0=Disable/1=Enable): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 1) {
                    init_data.enable = TRUE;
                } else {
                    init_data.enable = FALSE;
                }
                init_data.dis_ing_nm_macsec_en = TRUE;

                printf ("\nPort_No: %d, MACSEC ByPass None/Enable/Disable? (0=None/1=ByPass Enable/2=ByPass Disable): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '2') {
                    init_data.bypass = MACSEC_INIT_BYPASS_DISABLE;
                } else if (value_str[0] == '1') {
                    init_data.bypass = MACSEC_INIT_BYPASS_ENABLE;
                } else {
                    init_data.bypass = MACSEC_INIT_BYPASS_NONE;
                }

                rc = vtss_macsec_init_set(inst, port_no, &init_data);
                printf("vtss_macsec_init_set: rc:0x%x;  INST: %p; port_no: %d, enable: %x\n", rc, inst, port_no, init_data.enable);

                continue;

            } else if (strcmp(command, "macsec_frmcap") == 0) {
                vtss_rc  rc;
                vtss_macsec_frame_capture_t  capture;
                u32 frm_len = 0;                                    // Length of the frame captured
                u32 idx = 0;
                u8 frm_buffer[VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX];  // Buffer for storing the frame

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                printf ("\nPort_No: %d, Enter DIRECTION (0=Disable / 1=INGRESS / 2=EGRESS) (0/1/2)): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '2') {
                    printf ("Port_No: %d, EGRESS DIRECTION Selected \n", port_no);
                    capture = VTSS_MACSEC_FRAME_CAPTURE_EGRESS;
                } else if (value_str[0] == '1') {
                    printf ("Port_No: %d, INGRESS DIRECTION Selected \n", port_no);
                    capture = VTSS_MACSEC_FRAME_CAPTURE_INGRESS;
                } else {
                    printf ("Port_No: %d, DISABLE Selected - Also dumping Capture Data \n", port_no);
                    capture = VTSS_MACSEC_FRAME_CAPTURE_DISABLE;
                }

                // Setup capturing of egress frame
                vtss_macsec_frame_capture_set(inst, port_no, capture);

                if (capture == VTSS_MACSEC_FRAME_CAPTURE_DISABLE) {
                    // Get the captured frame
                    vtss_macsec_frame_get(inst, port_no, VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX, &frm_len, &frm_buffer[0]);
                    printf ("Port_No: %d, Capture Disabled - Dumping Capture Data -Frame Len: %d \n", port_no, frm_len);
                    for (idx=0; idx<=frm_len; idx++) {
                        printf ("frame_Buff[%d]:0x%x \n", idx, frm_buffer[idx]);
                    }
                } else {
                    printf ("Port_No: %d, Start Traffic to be Captured - Enable Loopbacks if required \n", port_no);
                }

                continue;

            } else if (strcmp(command, "macsec128Exp") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                vtss_port_no_t           macsec_physical_port = port_no;
                vtss_macsec_vport_id_t   macsec_virtual_port  = 0;
                vtss_macsec_service_id_t macsec_service_id    = 0;
                BOOL                     encrypt_256 = FALSE;
                BOOL                     confidentiality = TRUE;

                vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = TRUE,
                                                        .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                                        .explicit_sci.port_id  = 0x0001 };

                printf ("Port %d Config for Traffic - Explicit SCI: %x;  128bit Encryption\n",
                   port_no, explicit_sci_rx.explicit_sci_flag);

                printf ("\nPort_No: %d, Enter Confidentiality (0=No Encrypt/1=Encrypt): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                confidentiality = atoi(value_str);

                if (confidentiality) {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  128bit Encryption=ON; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                } else {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  128bit Encryption=OFF; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                }


                vtss_single_secy_sample_system_create(inst,
                                                  port_no,
                                                 &macsec_port[port_no],
                                                 &port_macaddress[port_no],
                                                 &peer_sci[port_no],
                                                 &explicit_sci_rx,
                                                  encrypt_256,
                                                  confidentiality );

                if (encrypt_256) {
                    printf ("MACsec PHY Port %d Configured for MACSEC 256-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                } else {
                    printf ("MACsec PHY Port %d Configured for MACSEC 128-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                }
                if (!confidentiality) {
                    printf("Confidentiality=FALSE; Therefore SECTAG and ICV Added, but Packet NOT ENCRYPTED \n");
                }
                printf ("Port %d Ready for Traffic - Encrypt on data Egress;  Decrypt on data Ingress\n", port_no);
                printf ("Unencrypted Data IEEE_IPv4(etherType=0x0800),  Encrypted Data IEEE_802.1AE(etherType=0x88e5)\n");
                enable_macsec[port_no] = TRUE;
    // TODO, inject traffic here, and verify traffic and counters
                continue;

            } else if (strcmp(command, "macsec128Imp") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                vtss_port_no_t           macsec_physical_port = port_no;
                vtss_macsec_vport_id_t   macsec_virtual_port  = 0;
                vtss_macsec_service_id_t macsec_service_id    = 0;
                BOOL                     encrypt_256 = FALSE;
                BOOL                     confidentiality = TRUE;

                vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = FALSE,
                                                        .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                                        .explicit_sci.port_id  = 0x0001 };


                printf ("Port %d Config for Traffic - Explicit SCI: %x;  128bit Encryption\n",
                   port_no, explicit_sci_rx.explicit_sci_flag);

                printf ("\nPort_No: %d, Enter Confidentiality (0=No Encrypt/1=Encrypt): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                confidentiality = atoi(value_str);

                if (confidentiality) {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  128bit Encryption=ON; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                } else {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  128bit Encryption=OFF; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                }

                vtss_single_secy_sample_system_create(inst,
                                                  port_no,
                                                 &macsec_port[port_no],
                                                 &port_macaddress[port_no],
                                                 &peer_sci[port_no],
                                                 &explicit_sci_rx,
                                                  encrypt_256,
                                                  confidentiality );

                if (encrypt_256) {
                    printf ("MACsec PHY Port %d Configured for MACSEC 256-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                } else {
                    printf ("MACsec PHY Port %d Configured for MACSEC 128-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                }
                if (!confidentiality) {
                    printf("Confidentiality=FALSE; Therefore SECTAG and ICV Added, but Packet NOT ENCRYPTED \n");
                }
                printf ("Port %d Ready for Traffic - Encrypt on data Egress;  Decrypt on data Ingress\n", port_no);
                printf ("Unencrypted Data IEEE_IPv4(etherType=0x0800),  Encrypted Data IEEE_802.1AE(etherType=0x88e5)\n");
                enable_macsec[port_no] = TRUE;
    // TODO, inject traffic here, and verify traffic and counters
                continue;

            } else if (strcmp(command, "macsec256Exp") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                vtss_port_no_t           macsec_physical_port = port_no;
                vtss_macsec_vport_id_t   macsec_virtual_port  = 0;
                vtss_macsec_service_id_t macsec_service_id    = 0;
                BOOL                     encrypt_256 = TRUE;
                BOOL                     confidentiality = TRUE;

                vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = TRUE,
                                                        .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                                        .explicit_sci.port_id  = 0x0001 };


                printf ("Port %d Config for Traffic - Explicit SCI: %x;  256bit Encryption\n",
                   port_no, explicit_sci_rx.explicit_sci_flag);

                printf ("\nPort_No: %d, Enter Confidentiality (0=No Encrypt/1=Encrypt): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                confidentiality = atoi(value_str);

                if (confidentiality) {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  256bit Encryption=ON; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                } else {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  256bit Encryption=OFF; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                }

                vtss_single_secy_sample_system_create(inst,
                                                  port_no,
                                                 &macsec_port[port_no],
                                                 &port_macaddress[port_no],
                                                 &peer_sci[port_no],
                                                 &explicit_sci_rx,
                                                  encrypt_256,
                                                  confidentiality );

                if (encrypt_256) {
                    printf ("MACsec PHY Port %d Configured for MACSEC 256-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                } else {
                    printf ("MACsec PHY Port %d Configured for MACSEC 128-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                }

                if (!confidentiality) {
                    printf("Confidentiality=FALSE; Therefore SECTAG and ICV Added, but Packet NOT ENCRYPTED \n");
                }
                printf ("Port %d Ready for Traffic - Encrypt on data Egress;  Decrypt on data Ingress\n", port_no);
                printf ("Unencrypted Data IEEE_IPv4(etherType=0x0800),  Encrypted Data IEEE_802.1AE(etherType=0x88e5)\n");
                enable_macsec[port_no] = TRUE;
    // TODO, inject traffic here, and verify traffic and counters
                continue;

            } else if (strcmp(command, "macsec256Imp") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                vtss_port_no_t           macsec_physical_port = port_no;
                vtss_macsec_vport_id_t   macsec_virtual_port  = 0;
                vtss_macsec_service_id_t macsec_service_id    = 0;
                BOOL                     encrypt_256 = TRUE;
                BOOL                     confidentiality = TRUE;

                vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = FALSE,
                                                        .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                                        .explicit_sci.port_id  = 0x0001 };


                printf ("Port %d Config for Traffic - Explicit SCI: %x;  256bit Encryption\n",
                   port_no, explicit_sci_rx.explicit_sci_flag);

                printf ("\nPort_No: %d, Enter Confidentiality (0=No Encrypt/1=Encrypt): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                confidentiality = atoi(value_str);

                if (confidentiality) {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  256bit Encryption=ON; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                } else {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  256bit Encryption=OFF; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                }

                vtss_single_secy_sample_system_create(inst,
                                                  port_no,
                                                 &macsec_port[port_no],
                                                 &port_macaddress[port_no],
                                                 &peer_sci[port_no],
                                                 &explicit_sci_rx,
                                                  encrypt_256,
                                                  confidentiality );

                if (encrypt_256) {
                    printf ("MACsec PHY Port %d Configured for MACSEC 256-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                } else {
                    printf ("MACsec PHY Port %d Configured for MACSEC 128-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                }

                if (!confidentiality) {
                    printf("Confidentiality=FALSE; Therefore SECTAG and ICV Added, but Packet NOT ENCRYPTED \n");
                }
                printf ("Port %d Ready for Traffic - Encrypt on data Egress;  Decrypt on data Ingress\n", port_no);
                printf ("Unencrypted Data IEEE_IPv4(etherType=0x0800),  Encrypted Data IEEE_802.1AE(etherType=0x88e5)\n");
                enable_macsec[port_no] = TRUE;
    // TODO, inject traffic here, and verify traffic and counters
                continue;


            } else if (strcmp(command, "macsec_off") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                // Tear-Down MACSec setup
                vtss_single_secy_sample_system_destroy(inst,
                                                   &macsec_port[port_no],
                                                   &port_macaddress[port_no],
                                                   &peer_sci[port_no]);

                //printf ("Please Remove Power from Eval Board and Re-Initialize Board\n");
                enable_macsec[port_no] = FALSE;
                continue;

           } else if (strcmp(command, "macsec_en_event") == 0) {
                vtss_rc  rc = 0;
                vtss_macsec_event_t   ev_mask;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }


                rc = vtss_macsec_event_enable_get(inst, port_no, &ev_mask);

                printf ("Getting MACSEC INT Event Mask: %x, rc = %d\n", ev_mask, rc);
                //ev_mask = VTSS_MACSEC_SEQ_NONE;
                //ev_mask = VTSS_MACSEC_SEQ_THRESHOLD_EVENT;
                //ev_mask = VTSS_MACSEC_SEQ_ROLLOVER_EVENT;
                ev_mask = VTSS_MACSEC_SEQ_ALL;

                rc = vtss_macsec_event_enable_set(inst, port_no, ev_mask, TRUE);

                printf ("Setting MACSEC INT Event Mask: %x, rc = %d\n", ev_mask, rc);
                continue;

           } else if (strcmp(command, "macsec_dis_event") == 0) {
                vtss_rc  rc = 0;
                vtss_macsec_event_t   ev_mask;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_event_enable_get(inst, port_no, &ev_mask);
                printf ("Getting MACSEC INT Event Mask: %x, rc = %d\n", ev_mask, rc);
                // Disable specific Event or just disable everything that is enabled?
                //ev_mask = VTSS_MACSEC_SEQ_NONE;
                //ev_mask = VTSS_MACSEC_SEQ_THRESHOLD_EVENT;
                //ev_mask = VTSS_MACSEC_SEQ_ROLLOVER_EVENT;
                //ev_mask = VTSS_MACSEC_SEQ_ALL;

                rc = vtss_macsec_event_enable_set(inst, port_no, ev_mask, FALSE);

                printf ("Clearing MACSEC INT Event Mask: %x, \n", ev_mask);
                continue;

           } else if (strcmp(command, "macsec_poll_event") == 0) {
                vtss_rc  rc = 0;
                vtss_macsec_event_t   ev_mask;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_event_enable_get(inst, port_no, &ev_mask);
                printf ("Getting MACSEC Enabled INT Events: %x, rc = %d\n", ev_mask, rc);

                ev_mask = 0;

                rc = vtss_macsec_event_poll(inst, port_no, &ev_mask);

                printf ("Polling MACSEC INT Event: 0x%x, rc = %d\n", ev_mask, rc);

                if (ev_mask == VTSS_MACSEC_SEQ_NONE) {
                    printf ("MACSEC INT Event: VTSS_MACSEC_SEQ_NONE \n");
                } else if (ev_mask == VTSS_MACSEC_SEQ_THRESHOLD_EVENT) {
                    printf ("MACSEC INT Event: VTSS_MACSEC_SEQ_THRESHOLD_EVENT \n");
                } else if (ev_mask == VTSS_MACSEC_SEQ_ROLLOVER_EVENT) {
                    printf ("MACSEC INT Event: VTSS_MACSEC_SEQ_ROLLOVER_EVENT \n");
                } else if (ev_mask == VTSS_MACSEC_SEQ_ALL) {
                    printf ("MACSEC INT Event: VTSS_MACSEC_SEQ_ALL \n");
                } else {
                    printf ("MACSEC INT Event: Unknown: 0x%x \n", ev_mask);
                }

                continue;

           } else if (strcmp(command, "macsec_get_thresh") == 0) {
                vtss_rc  rc = 0;
                u32      threshold = 0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_event_seq_threshold_get(inst, port_no, &threshold);

                printf ("Current MACSEC Seq Threshold for Port: %d    Thresh: %d;   rc = %d\n", port_no, threshold, rc);

                continue;

          } else if (strcmp(command, "macsec_set_thresh") == 0) {
                vtss_rc  rc = 0;
                u32      threshold = 0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_event_seq_threshold_get(inst, port_no, &threshold);
                printf ("Current MACSEC Seq Threshold for Port: %d    Thresh: %d;   rc = %d\n", port_no, threshold, rc);

                printf ("Please Enter the Desired MACSEC Seq Threshold for Port: %d:  ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                threshold = strtol(value_str, NULL, 10);

                rc = vtss_macsec_event_seq_threshold_set(inst, port_no, threshold);
                printf ("\nSetting MACSEC Seq Threshold for Port: %d    Thresh: %d;   rc = %d\n", port_no, threshold, rc);

                continue;

            } else if (strcmp(command, "ctrl_cnt") == 0) {
                vtss_rc  rc;
                vtss_macsec_secy_port_counters_t     cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_secy_port_counters_t));

                rc = vtss_macsec_controlled_counters_get(inst, macsec_port[port_no], &cntrs);

                printf("\n PORT Sec_Y IN COUNTERS: Port_no: %d\n", port_no);
                printf(" if_in_octets: 0x%llx \n", (long long unsigned int) cntrs.if_in_octets);
                printf(" if_in_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_pkts);
                printf(" if_in_discards: 0x%llx \n", (long long unsigned int)cntrs.if_in_discards);
                printf(" if_in_errors: 0x%llx \n", (long long unsigned int)cntrs.if_in_errors);
                printf("\n PORT Sec_Y OUT COUNTERS: \n");
                printf(" if_out_octets: 0x%llx \n", (long long unsigned int)cntrs.if_out_octets);
                printf(" if_out_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_pkts);
                printf(" if_out_errors: 0x%llx \n", (long long unsigned int)cntrs.if_out_errors);
                printf(" if_out_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_ucast_pkts);
                printf(" if_out_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_multicast_pkts);
                printf(" if_out_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_broadcast_pkts);

                continue;

            } else if (strcmp(command, "unctrl_cnt") == 0) {
                vtss_rc  rc;
                vtss_macsec_uncontrolled_counters_t  cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_secy_port_counters_t));

                rc = vtss_macsec_uncontrolled_counters_get(inst, port_no, &cntrs);

                printf("\n UNCONTROLLED IN-COUNTERS: Port_no: %d\n", port_no);
                printf(" if_in_octets: 0x%llx \n", (long long unsigned int)cntrs.if_in_octets);
                printf(" if_in_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_ucast_pkts);
                printf(" if_in_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_multicast_pkts);
                printf(" if_in_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_broadcast_pkts);
                printf(" if_in_discards: 0x%llx \n", (long long unsigned int)cntrs.if_in_discards);
                printf(" if_in_errors: 0x%llx \n", (long long unsigned int)cntrs.if_in_errors);
                printf("\n UNCONTROLLED OUT-COUNTERS: Port_no: %d\n", port_no);
                printf(" if_out_octets: 0x%llx \n", (long long unsigned int)cntrs.if_out_octets);
                printf(" if_out_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_ucast_pkts);
                printf(" if_out_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_multicast_pkts);
                printf(" if_out_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_broadcast_pkts);
                printf(" if_out_errors: 0x%llx \n", (long long unsigned int)cntrs.if_out_errors);

                continue;

            } else if (strcmp(command, "cmn_cnt") == 0) {
                vtss_rc  rc;
                vtss_macsec_common_counters_t        cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_common_counters_t));

                rc = vtss_macsec_common_counters_get(inst, port_no, &cntrs);

                printf("\n COMMON IN-COUNTERS: Port_no: %d\n", port_no);
                printf(" if_in_octets: 0x%llx \n", (long long unsigned int)cntrs.if_in_octets);
                printf(" if_in_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_ucast_pkts);
                printf(" if_in_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_multicast_pkts);
                printf(" if_in_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_broadcast_pkts);
                printf(" if_in_discards: 0x%llx \n", (long long unsigned int)cntrs.if_in_discards);
                printf(" if_in_errors: 0x%llx \n", (long long unsigned int)cntrs.if_in_errors);
                printf("\n COMMON OUT-COUNTERS: Port_no: %d\n", port_no);
                printf(" if_out_octets: 0x%llx \n", (long long unsigned int)cntrs.if_out_octets);
                printf(" if_out_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_ucast_pkts);
                printf(" if_out_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_multicast_pkts);
                printf(" if_out_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_broadcast_pkts);
                printf(" if_out_errors: 0x%llx \n", (long long unsigned int)cntrs.if_out_errors);

                continue;

            } else if (strcmp(command, "hmac_count") == 0) {
                vtss_rc  rc;
                BOOL                           clear_cntrs = FALSE;
                vtss_macsec_mac_counters_t     cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_mac_counters_t));

                rc = vtss_macsec_hmac_counters_get(inst, port_no, &cntrs, clear_cntrs);

                printf("\n HOST MAC RX COUNTERS: Port_no: %d\n", port_no);
                printf(" if_rx_octets: 0x%llx \n", (long long unsigned int)cntrs.if_rx_octets);
                printf(" if_rx_in_bytes: 0x%llx \n", (long long unsigned int)cntrs.if_rx_in_bytes);
                printf(" if_rx_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_ucast_pkts);
                printf(" if_rx_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_multicast_pkts);
                printf(" if_rx_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_broadcast_pkts);
                printf(" if_rx_discards: 0x%llx \n", (long long unsigned int)cntrs.if_rx_discards);
                printf(" if_rx_CRCAlignErrors: 0x%llx \n", (long long unsigned int)cntrs.if_rx_CRCAlignErrors);
                printf(" if_rx_UndersizePkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_UndersizePkts);
                printf(" if_rx_Fragments: 0x%llx \n", (long long unsigned int)cntrs.if_rx_Fragments);
                printf(" if_rx_Jabbers: 0x%llx \n", (long long unsigned int)cntrs.if_rx_Jabbers);
                printf(" if_rx_errors: 0x%llx \n", (long long unsigned int)cntrs.if_rx_errors);
                printf("\n HOST MAC TX COUNTERS: \n");
                printf(" if_tx_octets: 0x%llx \n", (long long unsigned int)cntrs.if_tx_octets);
                printf(" if_tx_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_ucast_pkts);
                printf(" if_tx_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_multicast_pkts);
                printf(" if_tx_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_broadcast_pkts);
                printf(" if_tx_errors: 0x%llx \n", (long long unsigned int)cntrs.if_tx_errors);

                continue;

            } else if (strcmp(command, "lmac_count") == 0) {
                vtss_rc  rc;
                BOOL                           clear_cntrs = FALSE;
                vtss_macsec_mac_counters_t     cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_mac_counters_t));

                rc = vtss_macsec_lmac_counters_get(inst, port_no, &cntrs, clear_cntrs);

                printf("\n LINE MAC RX COUNTERS: Port_no: %d\n", port_no);
                printf(" if_rx_octets: 0x%llx \n", (long long unsigned int)cntrs.if_rx_octets);
                printf(" if_rx_in_bytes: 0x%llx \n", (long long unsigned int)cntrs.if_rx_in_bytes);
                printf(" if_rx_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_ucast_pkts);
                printf(" if_rx_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_multicast_pkts);
                printf(" if_rx_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_broadcast_pkts);
                printf(" if_rx_discards: 0x%llx \n", (long long unsigned int)cntrs.if_rx_discards);
                printf(" if_rx_CRCAlignErrors: 0x%llx \n", (long long unsigned int)cntrs.if_rx_CRCAlignErrors);
                printf(" if_rx_UndersizePkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_UndersizePkts);
                printf(" if_rx_Fragments: 0x%llx \n", (long long unsigned int)cntrs.if_rx_Fragments);
                printf(" if_rx_Jabbers: 0x%llx \n", (long long unsigned int)cntrs.if_rx_Jabbers);
                printf(" if_rx_errors: 0x%llx \n", (long long unsigned int)cntrs.if_rx_errors);
                printf("\n LINE MAC TX COUNTERS: \n");
                printf(" if_tx_octets: 0x%llx \n", (long long unsigned int)cntrs.if_tx_octets);
                printf(" if_tx_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_ucast_pkts);
                printf(" if_tx_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_multicast_pkts);
                printf(" if_tx_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_broadcast_pkts);
                printf(" if_tx_errors: 0x%llx \n", (long long unsigned int)cntrs.if_tx_errors);

                continue;

            } else if (strcmp(command, "dbg_count") == 0) {
                vtss_rc  rc;
                vtss_macsec_rc_dbg_counters_t  cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_rc_dbg_counters_t));

                rc = vtss_macsec_dbg_counter_get(inst, port_no, &cntrs);

                printf("\n MACSEC DEBUG COUNTERS: Port_no: %d\n", port_no);
                printf(" invalid_sci_macaddr: %d \n", cntrs.invalid_sci_macaddr); /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_INVALID_SCI_MACADDR*/
                printf(" macsec_not_enabled: %d \n", cntrs.macsec_not_enabled);   /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NOT_ENABLED*/
                printf(" secy_already_in_use: %d \n", cntrs.secy_already_in_use); /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_SECY_ALREADY_IN_USE*/
                printf(" no_secy_found: %d \n", cntrs.no_secy_found);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NO_SECY_FOUND*/
                printf(" no_secy_vacancy: %d \n", cntrs.no_secy_vacency);         /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NO_SECY_VACANCY*/
                printf(" invalid_validate_frm: %d \n", cntrs.invalid_validate_frm);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_INVALID_VALIDATE_FRM*/
                printf(" invalid_hdr_bypass_len: %d \n", cntrs.invalid_hdr_bypass_len);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN*/
                printf(" sc_not_found: %d \n", cntrs.sc_not_found);            /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_SC_NOT_FOUND*/
                printf(" could_not_prg_sa_match: %d \n", cntrs.could_not_prg_sa_match);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH*/
                printf(" could_not_prg_sa_flow: %d \n", cntrs.could_not_prg_sa_flow);   /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW*/
                printf(" could_not_ena_sa: %d \n", cntrs.could_not_ena_sa);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA*/
                printf(" could_not_set_sa: %d \n", cntrs.could_not_set_sa);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA*/
                printf(" no_ctrl_frm_match: %d \n", cntrs.no_ctrl_frm_match);       /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH*/
                printf(" could_not_set_pattern: %d \n", cntrs.could_not_set_pattern);   /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN*/
                printf(" timeout_issue: %d \n", cntrs.timeout_issue);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_TIMEOUT_ISSUE*/
                printf(" could_not_empty_egress: %d \n", cntrs.could_not_empty_egress);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS*/
                printf(" an_not_created: %d \n", cntrs.an_not_created);          /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_AN_NOT_CREATED*/
                printf(" counld_not_empty_ingress: %d \n", cntrs.could_not_empty_ingress); /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS*/
                printf(" tx_sc_not_exist: %d \n", cntrs.tx_sc_not_exist);         /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_TX_SC_NOT_EXIST*/
                printf(" could_not_disable_sa: %d \n", cntrs.could_not_disable_sa);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA*/
                printf(" could_not_del_rx_sa: %d \n", cntrs.could_not_del_rx_sa);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA*/
                printf(" could_not_del_tx_sa: %d \n", cntrs.could_not_del_tx_sa);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA*/
                printf(" pattern_not_set: %d \n", cntrs.pattern_not_set);         /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_PATTERN_NOT_SET*/
                printf(" hw_resource_exhausted: %d \n", cntrs.hw_resource_exhusted);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED*/
                printf(" sci_already_exists: %d \n", cntrs.sci_already_exist);       /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_SCI_ALREADY_EXISTS*/
                printf(" sc_resource_not_found: %d \n", cntrs.sc_resource_not_found);   /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND*/
                printf(" rx_an_already_in_use: %d \n", cntrs.rx_an_already_in_use);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE*/
                printf(" empty_record: %d \n", cntrs.empty_record);            /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_EMPTY_RECORD*/
                printf(" could_not_prg_xform: %d \n", cntrs.could_not_prg_xform);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM*/
                printf(" could_not_toggle_sa: %d \n", cntrs.could_not_toggle_sa);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA*/
                printf(" tx_an_already_in_use: %d \n", cntrs.tx_an_already_in_use);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE*/
                printf(" all_avail_sa_in_use: %d \n", cntrs.all_available_sa_in_use); /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE*/
                printf(" match_disable: %d \n", cntrs.match_disable);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_MATCH_DISABLE*/
                printf(" all_cp_rules_in_use: %d \n", cntrs.all_cp_rules_in_use);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE*/
                printf(" pattern_prio_not_valid: %d \n", cntrs.pattern_prio_not_valid);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID*/
                printf(" buffer_too_small: %d \n", cntrs.buffer_too_small);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_BUFFER_TOO_SMALL*/
                printf(" frm_too_long: %d \n", cntrs.frm_too_long);            /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_FRAME_TOO_LONG*/
                printf(" frm_truncated: %d \n", cntrs.frm_truncated);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_FRAME_TRUNCATED*/
                printf(" phy_powered_down: %d \n", cntrs.phy_powered_down);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_PHY_POWERED_DOWN*/
                printf(" phy_not_macsec_capable: %d \n", cntrs.phy_not_macsec_capable);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE*/
                printf(" an_not_exist: %d \n", cntrs.an_not_exist);            /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_AN_NOT_EXIST*/
                printf(" no_pattern_cfg: %d \n", cntrs.no_pattern_cfg);          /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NO_PATTERN_CFG*/
                printf(" unexpected_speed: %d \n", cntrs.unexpected_speed);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_UNEXPECT_SPEED*/
                printf(" max_mtu: %d \n", cntrs.max_mtu);                 /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_MAX_MTU*/
                printf(" unexpected_cp_mode: %d \n", cntrs.unexpected_cp_mode);      /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_UNEXPECT_CP_MODE*/
                printf(" could_not_disable_an: %d \n", cntrs.could_not_disable_an);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN*/
                printf(" rule_out_of_range: %d \n", cntrs.rule_out_of_range);       /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_RULE_OUT_OF_RANGE*/
                printf(" rule_not_exist: %d \n", cntrs.rule_not_exit);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_RULE_NOT_EXIT*/
                printf(" csr_read: %d \n", cntrs.csr_read);                /**< Number of errors happen with error code VTSS_RC_ERR_CSR_READ*/
                printf(" csr_write: %d \n", cntrs.csr_write);               /**< Number of errors happen with error code VTSS_RC_ERR_CSR_WRITE*/
                printf(" unknown_rc_code: %d \n", cntrs.unknown_rc_code);         /**< Number of errors happen with unknown error code*/

                continue;

            } else if (strcmp(command, "dbg_reg_dump") == 0) {
                vtss_rc  rc;
                vtss_macsec_secy_port_counters_t     cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_dbg_reg_dump(inst, port_no, (vtss_debug_printf_t) printf);

                continue;

            } else if (strcmp(command, "fcb_dump") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_dbg_fcb_block_reg_dump(inst, port_no, (vtss_debug_printf_t) printf);

                continue;

            } else if (strcmp(command, "frm_ctl_dump") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_dbg_frm_match_handling_ctrl_reg_dump(inst, port_no, (vtss_debug_printf_t) printf);

                continue;

#ifdef KAT_TEST_ENABLE_1G
            } else if (strcmp(command, "kat_test") == 0) {
                vtss_rc  rc;
                vtss_macsec_frame_capture_t  capture = VTSS_MACSEC_FRAME_CAPTURE_DISABLE;
                BOOL egr_fail = FALSE;
                BOOL ing_fail = FALSE;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_phy_macsec_kat_test(inst, port_no, &egr_fail, &ing_fail);
                printf("Rtn Code for KAT Test: %d  Egress Results: %x,  Ingress_Results: %x\n", rc, egr_fail, ing_fail);
                if (egr_fail) {
                    printf("EGRESS_KAT_Results: FAIL:  %x\n", egr_fail);
                } else {
                    printf("EGRESS_KAT_Results: PASS:  %x\n", egr_fail);
                }
                if (ing_fail) {
                    printf("INGRESS_KAT_Results: FAIL:  %x\n", ing_fail);
                } else {
                    printf("INGRESS_KAT_Results: PASS:  %x\n", ing_fail);
                }
                continue;
#endif
            } else {
                continue;
            }

          }
//          continue;  // Go back to top of Loop


} // end of vtss_appl_macsec_demo_menu

#endif  // End of MACSEC
