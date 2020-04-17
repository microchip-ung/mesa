// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_api.h"   // For board initialization
#include "vtss_appl.h"  // For vtsss_board_t
#include "vtss_port_api.h"
#include "vtss_appl_cu_phy.h" // For board init

#include "vtss_macsec_api.h"
#include <openssl/aes.h>

#if defined(VTSS_FEATURE_MACSEC)

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_MACSEC // Must come before #include "vtss_state.h"

#if(1)

/* Application trace macros */
#define T_E(...) { if (vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] >= VTSS_TRACE_LEVEL_ERROR) vtss_callout_trace_printf(VTSS_APPL_TRACE_LAYER, VTSS_APPL_TRACE_GROUP, VTSS_TRACE_LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }
#define T_I(...) { if (vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] >= VTSS_TRACE_LEVEL_INFO) vtss_callout_trace_printf(VTSS_APPL_TRACE_LAYER, VTSS_APPL_TRACE_GROUP, VTSS_TRACE_LEVEL_INFO, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }
#define T_D(...) { if (vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] >= VTSS_TRACE_LEVEL_DEBUG) vtss_callout_trace_printf(VTSS_APPL_TRACE_LAYER, VTSS_APPL_TRACE_GROUP, VTSS_TRACE_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }
#define T_N(...) { if (vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] >= VTSS_TRACE_LEVEL_NOISE) vtss_callout_trace_printf(VTSS_APPL_TRACE_LAYER, VTSS_APPL_TRACE_GROUP, VTSS_TRACE_LEVEL_NOISE, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); }

#else

/* No trace */
#define T_E(...)
#define T_I(...)
#define T_D(...)
#define T_N(...)

#endif


/* **************************************************************** */
/*            Start of KNOWN ANSWER TEST - KAT  - Change section    */
/* **************************************************************** */
#if defined(VTSS_CHIP_CU_PHY) && defined(KAT_TEST_ENABLE_1G)



typedef struct explicit_sci_struct {
    BOOL                 explicit_sci_flag;
    vtss_macsec_sci_t    explicit_sci;
} vtss_explicit_sci_t;


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


vtss_rc vtss_phy_macsec_kat_config_basic_secy(vtss_inst_t          inst,
                                           vtss_port_no_t       macsec_physical_port,
                                           vtss_macsec_port_t  *in_macsec_port,
                                           vtss_mac_t          *in_port_macaddress,
                                           vtss_explicit_sci_t *explicit_sci_rx,
                                           BOOL                 encrypt_256)
{

    vtss_rc    rc = VTSS_RC_OK;
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

        if ((rc = vtss_macsec_init_set(inst, macsec_physical_port, &init_data)) != VTSS_RC_OK) {
            T_I ("vtss_macsec_init_set: rc:%d;  INST: %p; port_no: %d, enable: %x", rc, inst, macsec_physical_port, init_data.enable);
            switch(rc) {
            case VTSS_RC_OK:
                break;
            case VTSS_RC_ERROR:
                T_E("vtss_macsec_init_set: rc:VTSS_RC_ERROR  port_no: %d", macsec_physical_port);
                break;
            case VTSS_RC_ERR_MACSEC_NOT_ENABLED:
                T_I("vtss_macsec_init_set: rc:VTSS_RC_ERR_MACSEC_NOT_ENABLED, port_no: %d \n", macsec_physical_port);
                break;
            default:
                T_E("vtss_macsec_init_set: port_no: %d, ERROR! rc:%d \n", macsec_physical_port, rc);
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

        rc = vtss_macsec_default_action_set(inst, macsec_physical_port, &default_action_policy);

        T_I(" Default Action Set to VTSS_MACSEC_DEFAULT_ACTION_BYPASS;  rc = %d\n", rc);
        switch(rc) {
        case VTSS_RC_OK:
            break;
        case VTSS_RC_ERROR:
            T_E("vtss_macsec_default_action_set: rc:VTSS_RC_ERROR  \n" );
            break;
        case VTSS_RC_ERR_MACSEC_NOT_ENABLED:
            T_I("vtss_macsec_default_action_set: rc:VTSS_RC_ERR_MACSEC_NOT_ENABLED \n" );
            break;
        default:
            T_E("vtss_macsec_default_action_set: ERROR! rc:%d \n", rc);
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

            T_I(" MACSEC Sec_Y Explicit SCI = TRUE; always_include_sci = TRUE; 16 Byte SECTAG\n");
        } else {
         // _8BYTE_SECTAG_
            macsec_port_conf.always_include_sci     = FALSE;    // FALSE = Implicit SCI only, no room in pkt provided for Specifying SCI
            T_I(" MACSEC Sec_Y Explicit SCI = FALSE; always_include_sci = FALSE; 8 Byte SECTAG\n");

         // _16BYTE_SECTAG_
         //   macsec_port_conf.always_include_sci     = TRUE;       // FALSE = Implicit SCI, adds bytes but SCI not specified
         //   printf(" MACSEC Sec_Y Explicit SCI = FALSE; always_include_sci = TRUE; 16 Byte SECTAG\n");
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
        T_I(" New MACSEC Sec_Y Created; rc = %d \n", rc);
        switch(rc) {
        case VTSS_RC_OK:
            break;
        case VTSS_RC_ERROR:
            T_E("vtss_macsec_default_action_set: rc:VTSS_RC_ERROR  \n" );
            break;
        case VTSS_RC_ERR_MACSEC_NOT_ENABLED:
            T_I("vtss_macsec_default_action_set: rc:VTSS_RC_ERR_MACSEC_NOT_ENABLED \n" );
            break;
        default:
            T_E("vtss_macsec_default_action_set: ERROR! rc:%d \n", rc);
        }

/*  *************************************************************************************************** */
/*                               CONTROLLED PORT SETUP - EGRESS                                         */
/*  *************************************************************************************************** */
        // No encapsulation is used. Just match everything, but keep the
        // priority lower than the rule matching traffic for the uncontrolled
        // port. In other words, if it is not control traffic, then it should
        // be considered MACsec traffic.
        vtss_macsec_match_pattern_t pattern_ctrl_egr;
        memset (&pattern_ctrl_egr, 0, sizeof(vtss_macsec_match_pattern_t));
        pattern_ctrl_egr.priority            = VTSS_MACSEC_MATCH_PRIORITY_LOW;     // 12
        pattern_ctrl_egr.match               = VTSS_MACSEC_MATCH_ETYPE;            // 0x0004
        pattern_ctrl_egr.is_control          = FALSE;
        pattern_ctrl_egr.has_vlan_tag        = FALSE;
        pattern_ctrl_egr.has_vlan_inner_tag  = FALSE;
        pattern_ctrl_egr.etype               = 0x0800;                             // ETHERTYPE_IEEE_IPV4 0x0800
        pattern_ctrl_egr.vid                 = 0;
        pattern_ctrl_egr.vid_inner           = 0;
        int i = 0;
        for (i=0; i<8; i++) {
            pattern_ctrl_egr.hdr[i]          = 0;
            pattern_ctrl_egr.hdr_mask[i]     = 0;
        }
        pattern_ctrl_egr.src_mac             = port_macaddress;
        pattern_ctrl_egr.dest_mac            = peer_macaddress;

        rc = vtss_macsec_pattern_set(inst, macsec_port, VTSS_MACSEC_DIRECTION_EGRESS,
                                                   VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT, &pattern_ctrl_egr);

        T_I(" EGRESS CTRL Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 0800; rc=%d\n", rc);


/*  *************************************************************************************************** */
/*                               CONTROLLED PORT SETUP - INGRESS                                        */
/*  *************************************************************************************************** */
        // No encapsulation is used. Just match everything, but keep the
        // priority lower than the rule matching traffic for the uncontrolled
        // port. In other words, if it is not control traffic, then it should
        // be considered MACsec traffic.
        vtss_macsec_match_pattern_t pattern_ctrl_ingr;
        memset (&pattern_ctrl_ingr, 0, sizeof(vtss_macsec_match_pattern_t));

        pattern_ctrl_ingr.priority            = VTSS_MACSEC_MATCH_PRIORITY_LOW;        // 12
        pattern_ctrl_ingr.match               = VTSS_MACSEC_MATCH_ETYPE;               // 0x0004
        pattern_ctrl_ingr.is_control          = FALSE;
        pattern_ctrl_ingr.has_vlan_tag        = FALSE;
        pattern_ctrl_ingr.has_vlan_inner_tag  = FALSE;
        pattern_ctrl_ingr.etype               = 0x88e5;    // ETHERTYPE_IEEE_802_1_AE,   // 0x88e5
        pattern_ctrl_ingr.vid                 = 0;     // Old 64
        pattern_ctrl_ingr.vid_inner           = 0;
        for (i=0; i<8; i++) {
            pattern_ctrl_ingr.hdr[i]          = 0;
            pattern_ctrl_ingr.hdr_mask[i]     = 0;
        }
        pattern_ctrl_ingr.src_mac             = port_macaddress;
        pattern_ctrl_ingr.dest_mac            = peer_macaddress;

        // Associate the pattern with the controlled MACsec port
        rc = vtss_macsec_pattern_set(inst, macsec_port, VTSS_MACSEC_DIRECTION_INGRESS,
                                                   VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT, &pattern_ctrl_ingr);

        T_I(" INGRESS CTRL Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 88e5 ; rc=%d\n", rc);
/*  *************************************************************************************************** */
/*                               UNCONTROLLED PORT SETUP - INGRESS                                      */
/*  *************************************************************************************************** */
        // All traffic which is not vlan traffic, and have ether-type 0x888E
        // must be associated with the controlled port.
        vtss_macsec_match_pattern_t pattern_unctrl_ingr;
        memset (&pattern_unctrl_ingr, 0, sizeof(vtss_macsec_match_pattern_t));

        pattern_unctrl_ingr.priority            = VTSS_MACSEC_MATCH_PRIORITY_HIGHEST;  // 0
        pattern_unctrl_ingr.match               = VTSS_MACSEC_MATCH_ETYPE;         // 0x0004
        pattern_unctrl_ingr.is_control          = TRUE;
        pattern_unctrl_ingr.has_vlan_tag        = FALSE;
        pattern_unctrl_ingr.has_vlan_inner_tag  = FALSE;
        pattern_unctrl_ingr.etype               = 0x888e;    // ETHERTYPE_IEEE_802_1_X,    // 0x888e
        pattern_unctrl_ingr.vid                 = 0;
        pattern_unctrl_ingr.vid_inner           = 0;
        for (i=0; i<8; i++) {
            pattern_unctrl_ingr.hdr[i]          = 0;
            pattern_unctrl_ingr.hdr_mask[i]     = 0;
        }
        pattern_unctrl_ingr.src_mac             = port_macaddress;
        pattern_unctrl_ingr.dest_mac            = peer_macaddress;
 
        // Associate the pattern with the uncontrolled MACsec port
        rc = vtss_macsec_pattern_set(inst, macsec_port,
                                             VTSS_MACSEC_DIRECTION_INGRESS,
                                             VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT,
                                             &pattern_unctrl_ingr);

        T_I(" INGRESS UNCONTROLLED Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 888e; rc=%d \n", rc);

/*  *************************************************************************************************** */
/*                               UNCONTROLLED PORT SETUP - EGRESS                                       */
/*  *************************************************************************************************** */
        vtss_macsec_match_pattern_t pattern_unctrl_egr;
        memset (&pattern_unctrl_egr, 0, sizeof(vtss_macsec_match_pattern_t));

        pattern_unctrl_egr.priority            = VTSS_MACSEC_MATCH_PRIORITY_HIGHEST;  // 0
        pattern_unctrl_egr.match               = VTSS_MACSEC_MATCH_ETYPE;             // 0x0004
        pattern_unctrl_egr.is_control          = TRUE;
        pattern_unctrl_egr.has_vlan_tag        = FALSE;
        pattern_unctrl_egr.has_vlan_inner_tag  = FALSE;
        pattern_unctrl_egr.etype               = 0x888e;     // ETHERTYPE_IEEE_802_1_X,    // 0x888e
        pattern_unctrl_egr.vid                 = 0;
        pattern_unctrl_egr.vid_inner           = 0;
        for (i=0; i<8; i++) {
            pattern_unctrl_egr.hdr[i]          = 0;
            pattern_unctrl_egr.hdr_mask[i]     = 0;
        }
        pattern_unctrl_egr.src_mac             = port_macaddress;
        pattern_unctrl_egr.dest_mac            = peer_macaddress;

        rc = vtss_macsec_pattern_set(inst, macsec_port,
                                     VTSS_MACSEC_DIRECTION_EGRESS, VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT,
                                     &pattern_unctrl_egr);

        T_I(" EGRESS UNCONTROLLED Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 888e;  rc=%d \n", rc);

        // Enable the SecY
        rc = vtss_macsec_secy_controlled_set(inst, macsec_port, TRUE);
        T_I(" Enable Sec_Y; rc=0x%x \n",rc);
    }
    memcpy(in_macsec_port,     &macsec_port,     sizeof macsec_port);
    memcpy(in_port_macaddress, &port_macaddress, sizeof port_macaddress);

    return(rc);
}

vtss_rc vtss_phy_macsec_kat_config_system_create(vtss_inst_t          inst,
                                              vtss_port_no_t       port_no,
                                              vtss_macsec_port_t  *macsec_port,
                                              vtss_mac_t          *port_macaddress,
                                              vtss_macsec_sci_t   *peer_sci,
                                              vtss_explicit_sci_t *explicit_sci_rx,
                                              BOOL                 encrypt_256,
                                              BOOL                 confidentiality
)
{
    vtss_rc   rc = VTSS_RC_OK;
    const vtss_mac_t peer_macaddress = { .addr = {0, 0, 0, 0, 0, 0xBB}};
    const vtss_port_no_t macsec_physical_port = port_no;
    vtss_macsec_sci_t sci_rx;

    u16   assoc_no = 0;      // Assn Number  0 - 3
    u32   next_pn = 0x000001;    // Next Pkt Num
    u32   lowest_pn = 0x200000;    // Lowest Pkt Num = 2million

    //vtss_phy_macsec_kat_config_basic_secy(inst, macsec_physical_port, macsec_port, port_macaddress, explicit_sci_rx, encrypt_256);

    const vtss_macsec_sci_t implicit_sci_rx = { .mac_addr = peer_macaddress,
                                                .port_id  = macsec_port->port_id};
    if (explicit_sci_rx->explicit_sci_flag) {
        // Explicit SCI - Secure Channel Identifier - Not MAC Addr+Port_id
        // Explicit SCI - '12.15.35.24.c0.89-5e.81'

        sci_rx = explicit_sci_rx->explicit_sci;

        T_I ("Explicit SCI_Rx MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x::0x%04x\n",
                   sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1], sci_rx.mac_addr.addr[2],
                   sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5],
                   sci_rx.port_id );
    } else {
        // Implicit SCI - Secure Channel Identifier - Mac Addr+Port_id
        sci_rx = implicit_sci_rx;

        T_I ("Implicit SCI_Rx MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x::0x%04x\n",
                   sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1], sci_rx.mac_addr.addr[2],
                   sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5],
                   sci_rx.port_id );

    }

    T_D ("MACsec Phys Port: %d,  Service_id: 0x%x , MACsec Virtual Port (port_id): %d\n",
                   macsec_port->port_no, macsec_port->service_id, macsec_port->port_id );

    T_D ("MACsec Port: %d,  Port Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", macsec_physical_port,
                   port_macaddress->addr[0], port_macaddress->addr[1], port_macaddress->addr[2],
                   port_macaddress->addr[3], port_macaddress->addr[4], port_macaddress->addr[5] );
    T_D("Peer MACsec Port_id: %d,  Peer Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", macsec_port->port_id,
                   peer_macaddress.addr[0], peer_macaddress.addr[1], peer_macaddress.addr[2],
                   peer_macaddress.addr[3], peer_macaddress.addr[4], peer_macaddress.addr[5] );

    T_I("EGRESS SETUP: Installing Key on HW on Egress Side \n");
    { // Add secure TX channels and a secure association
        vtss_macsec_sak_t sak_tx_sa_0;

        // Add a new TX secure channel
        rc = vtss_macsec_tx_sc_set(inst, *macsec_port);
        T_D("vtss_macsec_tx_sc_set:  rc: %d \n", rc);

        if (encrypt_256) {
            // create a zero-key for 256bit cipher suite
            sak_tx_sa_0.len = 32;
        } else {
            // create a zero-key for 128bit cipher suite
            sak_tx_sa_0.len = 16;
        }

        // Update the hash key in the SAK before the key is installed in HW
        rc = sak_update_hash_key(&sak_tx_sa_0);
        T_D("sak_update_hash_key  rc: %d \n", rc);

        if ((sak_tx_sa_0.len == 16) || (sak_tx_sa_0.len == 32)) {
            T_D ("SAK: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_tx_sa_0.buf[0], sak_tx_sa_0.buf[1], sak_tx_sa_0.buf[2], sak_tx_sa_0.buf[3],
                   sak_tx_sa_0.buf[4], sak_tx_sa_0.buf[5], sak_tx_sa_0.buf[6], sak_tx_sa_0.buf[7],
                   sak_tx_sa_0.buf[8], sak_tx_sa_0.buf[9], sak_tx_sa_0.buf[10], sak_tx_sa_0.buf[11],
                   sak_tx_sa_0.buf[12], sak_tx_sa_0.buf[13], sak_tx_sa_0.buf[14], sak_tx_sa_0.buf[15]);
        }
        if (sak_tx_sa_0.len == 32) {
            T_D ("SAK: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_tx_sa_0.buf[16], sak_tx_sa_0.buf[17], sak_tx_sa_0.buf[18], sak_tx_sa_0.buf[19],
                   sak_tx_sa_0.buf[20], sak_tx_sa_0.buf[21], sak_tx_sa_0.buf[22], sak_tx_sa_0.buf[23],
                   sak_tx_sa_0.buf[24], sak_tx_sa_0.buf[25], sak_tx_sa_0.buf[26], sak_tx_sa_0.buf[27],
                   sak_tx_sa_0.buf[28], sak_tx_sa_0.buf[29], sak_tx_sa_0.buf[30], sak_tx_sa_0.buf[31]);
        }

        T_D ("SAK: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
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
        T_I("Activiating Key on HW Egress: rc; %d; Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Next_PN: 0x%x, Service_Id: 0x%x, confid: 0x%x \n",
                   rc, macsec_port->port_no, macsec_port->port_id, assoc_no, next_pn, macsec_port->service_id, confidentiality );

        rc = vtss_macsec_tx_sa_activate(inst, *macsec_port, assoc_no);
    }

    T_I("INGRESS SETUP: Installing Key on HW on Ingress Side;  rc=%d \n", rc);

    { // Add a MACsec peer
        vtss_macsec_sak_t sak_rx_sa_0;
        vtss_macsec_sak_t sak_rx_sa_1;

      // Add a new RX secure channel
      //  printf("Adding MACsec Peer\n");
        rc = vtss_macsec_rx_sc_add(inst, *macsec_port, &sci_rx);
        T_D("vtss_macsec_rx_sc_add;  rc=%d \n", rc);

        // Add two RX SA's
        if (encrypt_256) {
            sak_rx_sa_0.len = 32;
            sak_rx_sa_1.len = 32;
        } else {
            sak_rx_sa_0.len = 16;
            sak_rx_sa_1.len = 16;
        }


        // Update the hash key in the SAK before the key is installed in HW
        T_D("Adding Two Hashes - Secure Association 0 and 1 \n");
        rc = sak_update_hash_key(&sak_rx_sa_0);
        T_D("sak_update_hash_key; sak_rx_sa_0;  rc: %d \n", rc);
        rc = sak_update_hash_key(&sak_rx_sa_1);
        T_D("sak_update_hash_key; sak_rx_sa_1;  rc: %d \n", rc);

        T_D("Setup Key_0: Activating Key on HW on Ingress Side - Assoc: 0\n");
        //printf("SA Set \n");

        if ((sak_rx_sa_0.len == 16) || (sak_rx_sa_0.len == 32)) {
            T_D ("SAK_SA0: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_0.buf[0], sak_rx_sa_0.buf[1], sak_rx_sa_0.buf[2], sak_rx_sa_0.buf[3],
                   sak_rx_sa_0.buf[4], sak_rx_sa_0.buf[5], sak_rx_sa_0.buf[6], sak_rx_sa_0.buf[7],
                   sak_rx_sa_0.buf[8], sak_rx_sa_0.buf[9], sak_rx_sa_0.buf[10], sak_rx_sa_0.buf[11],
                   sak_rx_sa_0.buf[12], sak_rx_sa_0.buf[13], sak_rx_sa_0.buf[14], sak_rx_sa_0.buf[15]);
        }
        if (sak_rx_sa_0.len == 32) {
            T_D ("SAK_SA0: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_0.buf[16], sak_rx_sa_0.buf[17], sak_rx_sa_0.buf[18], sak_rx_sa_0.buf[19],
                   sak_rx_sa_0.buf[20], sak_rx_sa_0.buf[21], sak_rx_sa_0.buf[22], sak_rx_sa_0.buf[23],
                   sak_rx_sa_0.buf[24], sak_rx_sa_0.buf[25], sak_rx_sa_0.buf[26], sak_rx_sa_0.buf[27],
                   sak_rx_sa_0.buf[28], sak_rx_sa_0.buf[29], sak_rx_sa_0.buf[30], sak_rx_sa_0.buf[31]);
        }

        T_D ("SAK_SA0: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
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
        T_I("Setting up RX sa_0 Assoc_No: %d, lowest_pn: %d \n", assoc_no, lowest_pn);
        rc = vtss_macsec_rx_sa_set(inst, *macsec_port,
                                           &sci_rx, // identify which SC the SA belongs to
                                           assoc_no,       // associations number
                                           lowest_pn,       // lowest_pn,
                                           &sak_rx_sa_0);

        T_D("vtss_macsec_rx_sa_set  rc: %d \n", rc);

        rc = vtss_macsec_rx_sa_activate(inst, *macsec_port, &sci_rx, assoc_no);
        T_D("vtss_macsec_rx_sa_activate   rc: %d \n", rc);

        // install the key in HW on the egress side
        T_I("Activiating Key_0 on HW Inress: Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Lowest_PN: 0x%x, SCI: 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x - 0x%x \n",
                   macsec_port->port_no, macsec_port->port_id, assoc_no, lowest_pn, sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1],
                   sci_rx.mac_addr.addr[2], sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5], sci_rx.port_id );

        T_I("Setup Key_1: Activating Key on HW on Ingress Side - Assoc: 1\n");

        if ((sak_rx_sa_0.len == 16) || (sak_rx_sa_0.len == 32)) {
            T_D ("SAK_SA1: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_1.buf[0], sak_rx_sa_1.buf[1], sak_rx_sa_1.buf[2], sak_rx_sa_1.buf[3],
                   sak_rx_sa_1.buf[4], sak_rx_sa_1.buf[5], sak_rx_sa_1.buf[6], sak_rx_sa_1.buf[7],
                   sak_rx_sa_1.buf[8], sak_rx_sa_1.buf[9], sak_rx_sa_1.buf[10], sak_rx_sa_1.buf[11],
                   sak_rx_sa_1.buf[12], sak_rx_sa_1.buf[13], sak_rx_sa_1.buf[14], sak_rx_sa_1.buf[15]);
        }
        if (sak_rx_sa_0.len == 32) {
            T_D ("SAK_SA1: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_1.buf[16], sak_rx_sa_1.buf[17], sak_rx_sa_1.buf[18], sak_rx_sa_1.buf[19],
                   sak_rx_sa_1.buf[20], sak_rx_sa_1.buf[21], sak_rx_sa_1.buf[22], sak_rx_sa_1.buf[23],
                   sak_rx_sa_1.buf[24], sak_rx_sa_1.buf[25], sak_rx_sa_1.buf[26], sak_rx_sa_1.buf[27],
                   sak_rx_sa_1.buf[28], sak_rx_sa_1.buf[29], sak_rx_sa_1.buf[30], sak_rx_sa_1.buf[31]);
        }

        T_D ("SAK_SA1: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
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

        T_D("vtss_macsec_rx_sa_set  rc: %d \n", rc);

        rc = vtss_macsec_rx_sa_activate(inst, *macsec_port, &sci_rx, assoc_no);

        T_D("vtss_macsec_rx_sa_activate;  rc= %d \n", rc);
        T_I("Activiating Key_1 on HW Inress: Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Lowest_PN: 0x%x, SCI: 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x - 0x%x \n",
                   macsec_port->port_no, macsec_port->port_id, assoc_no, lowest_pn, sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1],
                   sci_rx.mac_addr.addr[2], sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5], sci_rx.port_id );
    }

    memcpy(peer_sci, &sci_rx, sizeof sci_rx);

    return(rc);
}

vtss_rc vtss_phy_macsec_kat_basic_secy_destroy(vtss_inst_t inst, const vtss_macsec_port_t *macsec_port)
{
    vtss_rc   rc = VTSS_RC_OK;
    // Delete SecY
    if ((rc = vtss_macsec_secy_conf_del(inst, *macsec_port)) != VTSS_RC_OK) {
        T_E("ERROR: Unable to delete SEC-Y Config\n");
        return rc;
    }

    // Disable the MACsec block
    printf("vtss_macsec_init_set,  Enable=False \n");
    vtss_macsec_init_t deinit_data = { .enable = FALSE };
    if ((rc = vtss_macsec_init_set(inst, macsec_port->port_no, &deinit_data)) != VTSS_RC_OK) {
        T_E("ERROR: Unable to perform macsec_init_set\n");
        return rc;
    }
    //printf("vtss_macsec_init_set: rc:%d \n", rc);

    return rc;
}

vtss_rc vtss_phy_macsec_kat_secy_system_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port,
    const vtss_mac_t         *port_macaddress,
    const vtss_macsec_sci_t  *peer_sci
)
{
    vtss_rc   rc = VTSS_RC_OK;

    // Disable the sa
    //printf ("calling vtss_macsec_rx_sa_disable:  1\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_disable(inst,*macsec_port, peer_sci, 1));
    //printf ("calling vtss_macsec_rx_sa_disable:  0\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_disable(inst,*macsec_port, peer_sci, 0));

    // Delete peer
    //printf ("calling vtss_macsec_rx_sa_del:  1\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_del(inst, *macsec_port, peer_sci, 1));
    //printf ("calling vtss_macsec_rx_sa_del:  0\n");
    if ((rc = vtss_macsec_rx_sa_del(inst, *macsec_port, peer_sci, 0)) != VTSS_RC_OK) {
        T_E("ERROR: Unable to Delete RX - SA\n");
        return rc;
    }
    printf ("vtss_macsec_rx_sc_del: rc=0x%x\n", rc);
    if ((rc = vtss_macsec_rx_sc_del(inst, *macsec_port, peer_sci)) != VTSS_RC_OK) {
        T_E("ERROR: Unable to Delete RX - SC\n");
        return rc;
    }

    // Delete TX SA and SC
    //printf ("calling vtss_macsec_tx_sa_disable:  0\n");
    //VTSS_RC_TEST(vtss_macsec_tx_sa_disable(inst,*macsec_port, 0));
    //printf ("calling vtss_macsec_tx_sa_del:  0\n");
    if ((rc = vtss_macsec_tx_sa_del(inst, *macsec_port, 0)) != VTSS_RC_OK) {
        T_E("ERROR: Unable to Delete TX - SA\n");
        return rc;
    }
    printf ("vtss_macsec_tx_sc_del: rc = 0x%x \n", rc);
    if ((rc = vtss_macsec_tx_sc_del(inst, *macsec_port)) != VTSS_RC_OK) {
        T_E("ERROR: Unable to Delete TX - SC\n");
        return rc;
    }

    //printf ("calling vtss_basic_secy_destroy  \n");
    if ((rc = vtss_phy_macsec_kat_basic_secy_destroy(inst, macsec_port)) != VTSS_RC_OK) {
        T_E("ERROR: Unable to Delete Known Answer Test: SEC-Y\n");
        return rc;
    }
    printf ("vtss_basic_secy_destroy: rc: 0x%x  \n", rc);

    return rc;
}


vtss_rc vtss_phy_macsec_kat_config_media_if(vtss_inst_t                        inst,
                                            const vtss_port_no_t               port_no,
                                            vtss_phy_conf_t                   *saved_phyCfg,
                                            vtss_phy_reset_conf_t             *saved_resetCfg)
{
    vtss_rc                  rc = VTSS_RC_OK;
    vtss_phy_type_t          phy_id = {0};
    vtss_phy_reset_conf_t    phy_resetCfg = {0};
    vtss_phy_conf_t          phyCfg = {0};
    u16                      value = 0;
    u16                      media_operating_mode = 0;

    if ((rc = vtss_phy_id_get(inst, port_no, &phy_id)) != VTSS_RC_OK) {
        T_E("ERROR:: Unable to get PHY_ID!  port_no: %d", port_no);
        return VTSS_RC_ERROR;
    }

    T_I("PHY Identified:PortID:%d PHY: %d Rev:%d Channel:%d  Channel count:%d Baseport:%d\n",
           port_no, phy_id.part_number, phy_id.revision, phy_id.channel_id, phy_id.port_cnt, phy_id.base_port_no);

    if (!((phy_id.part_number == VTSS_PHY_TYPE_8584) || (phy_id.part_number == VTSS_PHY_TYPE_8582))) {
        //Return silently as we don't want to throw the error for other PHYs
        T_I("Not a VIPER PHY! - VIPER-KAT Test Not Supported - Returning... ");
        return VTSS_RC_OK;
    }   

    /* Viper_RevA = 0; Viper_RevB = 1 */
    if (phy_id.revision < 0x1) {
        //Return silently as we don't want to throw the error for other PHYs
        T_I("Not a VIPER Rev_B PHY! - VIPER-KAT Test Not Supported - Returning... ");
        return VTSS_RC_OK;
    }

       /* *********************************************************************************** */
       /* The following code checks the MEDIA I/f Config / Media Operating Mode in SW and HW  */
       /* *********************************************************************************** */
    if ((rc = vtss_phy_reset_get(inst, port_no, saved_resetCfg)) != VTSS_RC_OK) {
        T_E("ERROR:: Unable to get PHY_RESET_CFG!  port_no: %d", port_no);
    }

    if ((rc = vtss_phy_conf_get(inst, port_no, saved_phyCfg)) != VTSS_RC_OK) {
        T_E("ERROR:: Unable to get PHY_CFG!  port_no: %d", port_no);
    }

    value = 0;
    if ((rc = vtss_phy_read_page(inst, port_no, VTSS_PHY_PAGE_STANDARD, 23, &value)) != VTSS_RC_OK) {
        T_E("ERROR:: Unable to READ Reg23!  port_no: %d", port_no);
    }

    media_operating_mode = (value & 0x0700) >> 8;
    T_I("Media i/f Config SW PHY_Inst:0x%x::HW_Reg23:0x%04x Media_OpMode: 0x%x port-no: %d \n", 
             saved_resetCfg->media_if, value, media_operating_mode, port_no);

    phy_resetCfg = *saved_resetCfg;
    phyCfg = *saved_phyCfg;

    if (phy_resetCfg.media_if != VTSS_PHY_MEDIA_IF_FI_1000BX || (media_operating_mode != 2)) {
        phy_resetCfg.media_if = VTSS_PHY_MEDIA_IF_FI_1000BX;
        phy_resetCfg.force = VTSS_PHY_FORCE_RESET;
        phyCfg.mode = VTSS_PHY_MODE_FORCED;
        phyCfg.forced.speed = VTSS_SPEED_1G;
        //phyCfg.sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_HIGH;

        vtss_phy_conf_set(inst, port_no, &phyCfg);
        vtss_phy_reset(inst, port_no, &phy_resetCfg);
    }
    return(rc);
}

//#define KAT_TEST_DEBUG

vtss_rc vtss_phy_macsec_kat_config_secy(vtss_inst_t                        inst,
                                        const vtss_port_no_t               port_no,
                                        vtss_phy_conf_t                   *saved_phyCfg,
                                        vtss_phy_reset_conf_t             *saved_resetCfg,
                                        vtss_macsec_port_t                *macsec_port,
                                        vtss_mac_t                        *port_macaddress,
                                        vtss_macsec_sci_t                 *peer_sci,
                                        BOOL                               encrypt_256)
{
    vtss_rc                  rc = VTSS_RC_OK;
    BOOL                     confidentiality = TRUE;

    vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = FALSE,
                                            .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                            .explicit_sci.port_id  = 0x0001 };

    if ((rc = vtss_phy_macsec_kat_config_media_if(inst, port_no, saved_phyCfg, saved_resetCfg)) != VTSS_RC_OK) {
        T_E("Failed to change Media i/f to 1000BaseX, port-no: %d\n", port_no);
        return VTSS_RC_ERROR;
    }

    if (encrypt_256) {
        printf("KAT Test - GCM-AES-256 - KAT_BASIC_Secy port_no: %d\n", port_no);
    } else {
        printf("KAT Test - GCM-AES-128 - KAT_BASIC_Secy port_no: %d\n", port_no);
    }
    /* This config sets up the basic SEC-Y with Defaults */
    if ((rc = vtss_phy_macsec_kat_config_basic_secy(inst, port_no, macsec_port, port_macaddress, 
                                                    &explicit_sci_rx, encrypt_256)) != VTSS_RC_OK) {
        T_E("Unable to Successfully configure Basic SEC-Y in MACSEC Block - port_no: %d\n", port_no);
        return rc;
    }

    if (encrypt_256) {
        printf("KAT Test - GCM-AES-256 - KAT_SYSTEM_CREATE port_no: %d\n", port_no);
    } else {
        printf("KAT Test - GCM-AES-128 - KAT_SYSTEM_CREATE port_no: %d\n", port_no);
    }
    if ((rc = vtss_phy_macsec_kat_config_system_create(inst, port_no, macsec_port, port_macaddress, peer_sci,
                                                  &explicit_sci_rx, encrypt_256, confidentiality )) != VTSS_RC_OK) {
        T_E("Unable to Successfully configure System Create in MACSEC Block - port_no: %d\n", port_no);
        return rc;
    }

    return(rc);
}

static vtss_rc vtss_phy_macsec_kat_test_private(vtss_inst_t                        inst,
                                                const vtss_port_no_t               port_no,
                                                vtss_phy_conf_t                   *saved_phyCfg,
                                                vtss_phy_reset_conf_t             *saved_reset_cfg,
                                                BOOL                               encrypt_256,
                                                u8                                *egr_fail,
                                                u8                                *ing_fail)
{
    vtss_rc                      rc = VTSS_RC_OK;
    u32                          buf_length = VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX;
    u32                          frm_length = 0;
    int                          i;
    u8                           frame[VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX];
    vtss_phy_loopback_t          loopback = {0};
    vtss_macsec_frame_capture_t  capture = VTSS_MACSEC_FRAME_CAPTURE_EGRESS;
    vtss_port_status_t           status;
    u8                           expect_fail_result = FALSE;
    

    u8   exp_frame_encr_128[]  = {0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xf2,0x88,0xe5,0x0c,0x00,
                                  0x00,0x00,0x00,0x01,0xc7,0x20,0xc7,0x45,0x1d,0x50,0x7a,0x2a,0x9d,0xa2,0x93,0x0c,
                                  0xe8,0x79,0xa7,0x8a,0xc1,0x3b,0x57,0x3a,0x66,0x09,0x01,0xff,0x85,0xc3,0x93,0xf0,
                                  0x8b,0xc3,0x1b,0x4c,0x6d,0x1f,0x81,0x97,0x7d,0x2c,0x1c,0x34,0x13,0xc7,0x37,0x0f,
                                  0x18,0x6b,0x6b,0x8e,0x02,0xe1,0xaa,0x6c,0x73,0x96,0x88,0x46,0xc1,0xb5,0x9a,0xa1,
                                  0x01,0xb1,0x13,0x3a,0xc3,0x37,0x6b,0x48,0x36,0xbb,0xd5,0x55,0x92,0xd5,0xb2,0x37,
                                  0x24,0x47,0x56,0x6d,0x5d,0x4d,0x23,0x7e,0xbc,0xaf,0xb3,0x7b,0x5f,0x2e,0xd7,0x82,
                                  0x6c,0x12,0xc6,0xe9,0x43,0x03,0x93,0x62,0xfa,0x14,0x19,0x52,0xf0,0xdc,0x6e,0xe8,
                                  0x50,0x65,0x02,0x2c,0x15,0xf3,0xcd,0xcb,0xaf,0x31,0x4a,0xca,0x73,0xc3,0xec,0x11,
                                  0xfa,0x65,0x02,0x2c,0x00,0xbb,0x00,0x00};

    u8   exp_frame_encr_256[]  = {0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xf2,0x88,0xe5,0x0c,0x00,
                                  0x00,0x00,0x00,0x01,0x72,0xe4,0x6d,0x64,0x64,0xe4,0x1a,0xd8,0xd6,0x5b,0x9d,0x0c,
                                  0x4e,0x30,0xdb,0x1a,0xe4,0x50,0x3c,0x5d,0xc2,0x35,0x7a,0xc5,0x2f,0xf6,0x9a,0x18,
                                  0x56,0xe4,0xd9,0x69,0xc0,0x9f,0xff,0x01,0x00,0x74,0x8e,0x54,0xe2,0x27,0x1c,0x97,
                                  0x49,0xd7,0x94,0xd9,0xde,0x41,0xd4,0x64,0xce,0x1e,0xd3,0xdb,0xb4,0xcf,0x4f,0xb4,
                                  0xe4,0x96,0x22,0xc5,0xfd,0xf9,0x66,0x1d,0xbc,0xf1,0x80,0x8e,0xfd,0x86,0x92,0xdf,
                                  0x00,0x41,0x2d,0x7e,0xb0,0x32,0x4a,0xec,0xe9,0x8d,0xac,0xa6,0x62,0xbc,0x81,0xfd,
                                  0x6d,0x75,0x79,0xf1,0xe2,0x62,0xcc,0x7a,0x98,0x42,0x84,0x00,0x80,0xf0,0xd8,0xb0,
                                  0xdb,0x12,0x7c,0x17,0xc7,0x1f,0xef,0x9a,0x86,0x99,0x07,0xcb,0x49,0x69,0x87,0xf8,
                                  0x02,0x12,0x7c,0x17,0x00,0x00,0x00,0x00};

    u8  exp_frame[] =            {0xff,0xff,0xff,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xf2,0x08,0x00,0x45,0x00,
                                  0x00,0x6b,0x00,0x00,0x00,0x00,0xff,0x11,0x4e,0x2f,0xc0,0xa8,0x76,0x00,0xc0,0xa8,
                                  0x76,0x01,0x00,0x00,0x01,0x3f,0x00,0x57,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    printf("KAT_TEST:Ensure ALL Loopbacks are Disabled\n");
    /* ******************* Clear ALL Loopbacks ************** */
    if ((rc = vtss_phy_loopback_get( inst, port_no, &loopback)) != VTSS_RC_OK) {
        T_E("ERROR during Get ALL Loopbacks");
    }
    loopback.far_end_enable = FALSE;
    loopback.near_end_enable = FALSE;
    loopback.connector_enable = FALSE;
    loopback.mac_serdes_input_enable = FALSE;
    loopback.mac_serdes_facility_enable = FALSE;
    loopback.mac_serdes_equipment_enable = FALSE;
    loopback.media_serdes_input_enable = FALSE;
    loopback.media_serdes_facility_enable = FALSE;
    loopback.media_serdes_equipment_enable = FALSE;

    if ((rc = vtss_phy_loopback_set( inst, port_no, loopback)) != VTSS_RC_OK) {
        T_E("ERROR during Disable ALL Loopbacks");
    }
    T_I("Ensure ALL Loopbacks are Disabled");

    /* ******************* ENGAGE SerDes Media Equipment Loopback ************** */
    loopback.far_end_enable = FALSE;
    loopback.near_end_enable = FALSE;
    loopback.connector_enable = FALSE;
    loopback.mac_serdes_input_enable = FALSE;
    loopback.mac_serdes_facility_enable = FALSE;
    loopback.mac_serdes_equipment_enable = FALSE;
    loopback.media_serdes_input_enable = FALSE;
    loopback.media_serdes_facility_enable = FALSE;
    loopback.media_serdes_equipment_enable = TRUE;
    if ((rc = vtss_phy_loopback_set( inst, port_no, loopback)) != VTSS_RC_OK) {
        T_E("ERROR Setting MEDIA SerDes Equip Loopbacks");
    }
    T_I("Setting Media SerDes Equip Loopback ");
    printf("KAT TEST: MEDIA SerDes EQUIP Loopback Set \n");

    /* Make sure the Media Link is UP */
    for (i = 0; i < 100; i++) {
        vtss_phy_status_get(inst, port_no, &status);
        if (status.link) {
            break;
        }
        VTSS_MSLEEP(100);
    }
    T_I("vtss_phy_macsec_kat_test: Link Status: 0x%x,  Count: %d ", status.link, i);
    printf("vtss_phy_macsec_kat_test: Link Status: 0x%x,  Count: %d \n", status.link, i);

    /* ******************* EGRESS SIDE - GOOD Frame Test ************** */
    /* Note, the Expected Packet Number=0, but changes on each packet, therefore, this will PASS on first run */
    T_I("vtss_phy_macsec_kat_test: VTSS_MACSEC_FRAME_CAPTURE_EGRESS");
    printf("Known Answer Test (KAT)#1: VTSS_MACSEC_FRAME_CAPTURE_EGRESS - POSITIVE TEST\n");
    T_I("TESTING EGRESS: ETH-IP-UDP Ecryption Only");
    printf("TESTING EGRESS: ETH-IP-UDP Ecryption Only\n");

    expect_fail_result = FALSE;
    capture = VTSS_MACSEC_FRAME_CAPTURE_EGRESS;
    if ((rc = vtss_macsec_frame_capture_set(inst, port_no, capture)) != VTSS_RC_OK) {
        T_E("Configuring EGRESS FRAME_CAPTURE: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }
    if ((rc = vtss_phy_epg_gen_kat_frame(inst, port_no, TRUE)) != VTSS_RC_OK) {
        T_E("Configuring EPG to generate Matching Frame: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }
    if ((rc = vtss_macsec_frame_get(inst, port_no, buf_length, &frm_length, &frame[0])) != VTSS_RC_OK) {
        T_E("Getting Captured frame from EGRESS FRAME_CAPTURE: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }

    /* Compare the Captured Frame, Captured on EGRESS, frame will be Encrypted */
    if (rc == VTSS_RC_OK) {
        if (frm_length > 0) {
            if (encrypt_256) {
                if (frm_length > sizeof(exp_frame_encr_256)) {
                    frm_length = sizeof(exp_frame_encr_256);
                }
            } else {
                if (frm_length > sizeof(exp_frame_encr_128)) {
                    frm_length = sizeof(exp_frame_encr_128);
                }
            }
            T_I("EGRESS Frame (Encrypted) - port_no: %d, frame_length: %d", port_no, frm_length);
            printf("EGRESS Frame (Encrypted) - port_no: %d, frame_length: %d\n", port_no, frm_length);
#ifdef KAT_TEST_DEBUG
            for (i = 0; i < frm_length; i+=16) {
                T_I("buf[%d]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x ", i,
                frame[i+0], frame[i+1], frame[i+2], frame[i+3], frame[i+4], frame[i+5], frame[i+6], frame[i+7],
                frame[i+8], frame[i+9], frame[i+10], frame[i+11], frame[i+12], frame[i+13], frame[i+14], frame[i+15]);
                printf("buf[%d]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x \n", i,
                frame[i+0], frame[i+1], frame[i+2], frame[i+3], frame[i+4], frame[i+5], frame[i+6], frame[i+7],
                frame[i+8], frame[i+9], frame[i+10], frame[i+11], frame[i+12], frame[i+13], frame[i+14], frame[i+15]);
            }
#endif

            if (encrypt_256) {
                for (i = 0; i < frm_length; i++) {
                    if (frame[i] != exp_frame_encr_256[i]) {
#ifdef KAT_TEST_DEBUG
                        T_E("ERROR: EGR Encrypted Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x",
                           port_no, i, exp_frame_encr_256[i], frame[i]);
                        printf("ERROR: EGR Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x\n",
                           port_no, i, exp_frame_encr_256[i], frame[i]);
#endif
                        *egr_fail = TRUE;
                    }
                } 
            } else {
                for (i = 0; i < frm_length; i++) {
                    if (frame[i] != exp_frame_encr_128[i]) {
#ifdef KAT_TEST_DEBUG
                        T_E("ERROR: EGR Encrypted Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x",
                           port_no, i, exp_frame_encr_128[i], frame[i]);
                        printf("ERROR: EGR Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x\n",
                           port_no, i, exp_frame_encr_128[i], frame[i]);
#endif
                        *egr_fail = TRUE;
                    }
                }        
            }
        } else {
            T_E("ERROR: EGRESS Frame Zero Length (Encrypted) - port_no: %d, frame_length: %d", port_no, frm_length);
            printf("ERROR: EGRESS Frame Zero Length (Encrypted) - port_no: %d, frame_length: %d\n", port_no, frm_length);
            *egr_fail = TRUE;
            return(VTSS_RC_ERROR);
        }
    } else {
        T_E("ERROR: EGRESS Frame Capture Failure - port_no: %d ", port_no);
        //printf("ERROR: EGRESS Frame Capture Failure - port_no: %d \n", port_no);
        *egr_fail = TRUE;
        return(VTSS_RC_ERROR);
    }

    if (*egr_fail == expect_fail_result) {
        printf("TEST PASSED: TESTING ENCRYPTED EGRESS: EXPECT MATCH : RESULTS = MATCH - port_no: %d \n", port_no);
        T_I("TEST PASSED: TESTING ENCRYPTED EGRESS: EXPECT MATCH : RESULTS = MATCH - port_no: %d ", port_no);
        *egr_fail = FALSE;
    } else {
        printf("TEST FAILED: TESTING ENCRYPTED EGRESS: EXPECT MATCH : RESULTS = NO-MATCH - port_no: %d \n", port_no);
        T_I("TEST FAILED: TESTING ENCRYPTED EGRESS: EXPECT MATCH : RESULTS = NO-MATCH - port_no: %d ", port_no);
    }

    /* ******************* EGRESS SIDE - BAD Frame Test ************** */
    /* Note, the Packet Number changes on each packet, therefore, this will fail */
    T_I("Known Answer Test (KAT)#2: VTSS_MACSEC_FRAME_CAPTURE_EGRESS - NEGATIVE TEST - Expected Result=FAIL");
    printf("\nKnown Answer Test (KAT)#2: VTSS_MACSEC_FRAME_CAPTURE_EGRESS - NEGATIVE TEST - Expected Result=FAIL\n");
    T_I("TESTING EGRESS: ETH-IP-UDP Ecryption Only");
    printf("TESTING EGRESS: ETH-IP-UDP Ecryption Only\n");

    expect_fail_result = TRUE;
    capture = VTSS_MACSEC_FRAME_CAPTURE_EGRESS;
    if ((rc = vtss_macsec_frame_capture_set(inst, port_no, capture)) != VTSS_RC_OK) {
        T_E("Configuring EGRESS FRAME_CAPTURE: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }
    if ((rc = vtss_phy_epg_gen_kat_frame(inst, port_no, FALSE)) != VTSS_RC_OK) {
        T_E("Configuring EPG to generate Non-Matching Frame: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }
    if ((rc = vtss_macsec_frame_get(inst, port_no, buf_length, &frm_length, &frame[0])) != VTSS_RC_OK) {
        T_E("Getting Captured frame from EGRESS FRAME_CAPTURE: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }

    /* Compare the Captured Frame, Captured on EGRESS, frame will be Encrypted */
    if (rc == VTSS_RC_OK) {
        if (frm_length > 0) {
            T_I("EGRESS Frame (Encrypted) - port_no: %d, frame_length: %d", port_no, frm_length);
            printf("EGRESS Frame (Encrypted) - port_no: %d, frame_length: %d\n", port_no, frm_length);
            if (encrypt_256) {
                if (frm_length > sizeof(exp_frame_encr_256)) {
                    frm_length = sizeof(exp_frame_encr_256);
                }
            } else {
                if (frm_length > sizeof(exp_frame_encr_128)) {
                    frm_length = sizeof(exp_frame_encr_128);
                }
            }

#ifdef KAT_TEST_DEBUG
            for (i = 0; i < frm_length; i+=16) {
                T_I("buf[%d]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x ", i,
                frame[i+0], frame[i+1], frame[i+2], frame[i+3], frame[i+4], frame[i+5], frame[i+6], frame[i+7],
                frame[i+8], frame[i+9], frame[i+10], frame[i+11], frame[i+12], frame[i+13], frame[i+14], frame[i+15]);
                printf("buf[%d]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x \n", i,
                frame[i+0], frame[i+1], frame[i+2], frame[i+3], frame[i+4], frame[i+5], frame[i+6], frame[i+7],
                frame[i+8], frame[i+9], frame[i+10], frame[i+11], frame[i+12], frame[i+13], frame[i+14], frame[i+15]);
            }
#endif
            if (encrypt_256) {
                for (i = 0; i < frm_length; i++) {
                    if (frame[i] != exp_frame_encr_256[i]) {
#ifdef KAT_TEST_DEBUG
                        T_E("ERROR: EGR Encrypted Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x",
                           port_no, i, exp_frame_encr_256[i], frame[i]);
                        printf("ERROR: EGR Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x\n",
                           port_no, i, exp_frame_encr_256[i], frame[i]);
#endif
                        *egr_fail = TRUE;
                    }
                } 
            } else {
                for (i = 0; i < frm_length; i++) {
                    if (frame[i] != exp_frame_encr_128[i]) {
#ifdef KAT_TEST_DEBUG
                        T_E("ERROR: EGR Encrypted Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x",
                           port_no, i, exp_frame_encr_128[i], frame[i]);
                        printf("ERROR: EGR Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x\n",
                           port_no, i, exp_frame_encr_128[i], frame[i]);
#endif
                        *egr_fail = TRUE;
                    }
                }
            }
        } else {
            T_E("ERROR: EGRESS Frame Zero Length (Encrypted) - port_no: %d, frame_length: %d", port_no, frm_length);
            printf("ERROR: EGRESS Frame Zero Length (Encrypted) - port_no: %d, frame_length: %d\n", port_no, frm_length);
            *egr_fail = TRUE;
            return(VTSS_RC_ERROR);
        }
    } else {
        T_E("ERROR: EGRESS Frame Capture Failure - port_no: %d ", port_no);
        //printf("ERROR: EGRESS Frame Capture Failure - port_no: %d \n", port_no);
        *egr_fail = TRUE;
        return(VTSS_RC_ERROR);
    }

    if (*egr_fail == expect_fail_result) {
        printf("TEST PASSED: TESTING ENCRYPTED EGRESS: EXPECT NO-MATCH : RESULTS = NO-MATCH - port_no: %d \n", port_no);
        T_I("TEST PASSED: TESTING ENCRYPTED EGRESS: EXPECT NO-MATCH : RESULTS = NO-MATCH - port_no: %d ", port_no);
        *egr_fail = FALSE;
    } else {
        printf("TEST FAILED: TESTING ENCRYPTED EGRESS: EXPECT NO-MATCH : RESULTS = MATCH - port_no: %d \n", port_no);
        T_I("TEST FAILED: TESTING ENCRYPTED EGRESS: EXPECT NO-MATCH : RESULTS = MATCH - port_no: %d ", port_no);
    }

    /* ******************* INGRESS SIDE ************** */
    T_I("Known Answer Test (KAT)#3: VTSS_MACSEC_FRAME_CAPTURE_INGRESS - POSITIVE TEST");
    printf("Known Answer Test (KAT)#3: VTSS_MACSEC_FRAME_CAPTURE_INGRESS - POSITIVE TEST\n");
    T_I("TESTING INGRESS: ETH-IP-UDP Ecryption/Loopback/Decryption Only");
    printf("TESTING INGRESS: ETH-IP-UDP Ecryption/Loopback/Decryption Only\n");

    expect_fail_result = FALSE;
    capture = VTSS_MACSEC_FRAME_CAPTURE_INGRESS;
    if ((rc = vtss_macsec_frame_capture_set(inst, port_no, capture)) != VTSS_RC_OK) {
        T_E("Configuring INRESS FRAME_CAPTURE: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }
    if ((rc = vtss_phy_epg_gen_kat_frame(inst, port_no, TRUE)) != VTSS_RC_OK) {
        T_E("Configuring EPG to generate Matching Frame: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }
    if ((rc = vtss_macsec_frame_get(inst, port_no, buf_length, &frm_length, &frame[0])) != VTSS_RC_OK) {
        T_E("Getting Captured frame from INRESS FRAME_CAPTURE: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }

    if (rc == VTSS_RC_OK) {
        if (frm_length > 0) {
            T_I("INGRESS Frame (Decrypted) - port_no: %d, frame_length: %d", port_no, frm_length);
            printf("INGRESS Frame (Decrypted) - port_no: %d, frame_length: %d \n", port_no, frm_length);
            if (frm_length > sizeof(exp_frame)) {
                frm_length = sizeof(exp_frame);
            }

            //printf("INGRESS Encrytped Frame Values - port_no: %d \n", port_no);
#ifdef KAT_TEST_DEBUG
            for (i = 0; i < frm_length; i+=16) {
                T_I("buf[%d]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x ", i,
                frame[i+0], frame[i+1], frame[i+2], frame[i+3], frame[i+4], frame[i+5], frame[i+6], frame[i+7],
                frame[i+8], frame[i+9], frame[i+10], frame[i+11], frame[i+12], frame[i+13], frame[i+14], frame[i+15]);
                printf("buf[%d]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x \n", i,
                frame[i+0], frame[i+1], frame[i+2], frame[i+3], frame[i+4], frame[i+5], frame[i+6], frame[i+7],
                frame[i+8], frame[i+9], frame[i+10], frame[i+11], frame[i+12], frame[i+13], frame[i+14], frame[i+15]);
            }
#endif
            for (i = 0; i < frm_length; i++) {
                if (frame[i] == exp_frame[i]) {
                /* Match, Do Nothing */
                } else {
#ifdef KAT_TEST_DEBUG
                    T_E("ERROR: INGR Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x",
                        port_no, i, exp_frame[i], frame[i]);
                      printf("ERROR: INGR Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x\n",
                          port_no, i, exp_frame[i], frame[i]);
#endif
                    *ing_fail = TRUE;
                }
            }
        } else {
            T_E("ERROR: INGRESS Frame Zero Length (Encrypted) - port_no: %d, frame_length: %d", port_no, frm_length);
            printf("ERROR: INGRESS Frame Zero Length (Encrypted) - port_no: %d, frame_length: %d\n", port_no, frm_length);
            *ing_fail = TRUE;
            return(VTSS_RC_ERROR);
        }
    } else {
        T_E("ERROR: INGRESS Frame Capture Failure - port_no: %d ", port_no);
        //printf("ERROR: INGRESS Frame Capture Failure - port_no: %d \n", port_no);
        *ing_fail = TRUE;
        return(VTSS_RC_ERROR);
    }

    if (*ing_fail == expect_fail_result) {
        printf("TEST PASSED: TESTING DECRYPT INGRESS: EXPECT MATCH : RESULTS = MATCH - port_no: %d \n", port_no);
        T_I("TEST PASSED: TESTING DECRYPT INGRESS: EXPECT MATCH : RESULTS = MATCH - port_no: %d ", port_no);
        *ing_fail = FALSE;
    } else {
        printf("TEST FAILED: TESTING DECRYPT INGRESS: EXPECT MATCH : RESULTS = NO-MATCH - port_no: %d \n", port_no);
        T_I("TEST FAILED: TESTING DECRYPT INGRESS: EXPECT MATCH : RESULTS = NO-MATCH - port_no: %d ", port_no);
    }

    T_I("Known Answer Test (KAT)#4: VTSS_MACSEC_FRAME_CAPTURE_INGRESS - NEGATIVE TEST - Expected Result=FAIL");
    printf("Known Answer Test (KAT)#4: VTSS_MACSEC_FRAME_CAPTURE_INGRESS - NEGATIVE TEST - Expected Result=FAIL\n");
    T_I("TESTING INGRESS: ETH-IP-UDP Ecryption/Loopback/Decryption ");
    printf("TESTING INGRESS: ETH-IP-UDP Ecryption/Loopback/Decryption \n");

    expect_fail_result = TRUE;
    capture = VTSS_MACSEC_FRAME_CAPTURE_INGRESS;
    if ((rc = vtss_macsec_frame_capture_set(inst, port_no, capture)) != VTSS_RC_OK) {
        T_E("Configuring INRESS FRAME_CAPTURE: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }
    if ((rc = vtss_phy_epg_gen_kat_frame(inst, port_no, FALSE)) != VTSS_RC_OK) {
        T_E("Configuring EPG to generate Non-Matching Frame: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }
    if ((rc = vtss_macsec_frame_get(inst, port_no, buf_length, &frm_length, &frame[0])) != VTSS_RC_OK) {
        T_E("Getting Captured frame from INRESS FRAME_CAPTURE: FAILED!, port_no: %d, rc: 0x%x", port_no, rc);
    }

    if (rc == VTSS_RC_OK) {
        if (frm_length > 0) {
            T_I("INGRESS Frame (Decrypted) - port_no: %d, frame_length: %d", port_no, frm_length);
            printf("INGRESS Frame (Decrypted) - port_no: %d, frame_length: %d\n", port_no, frm_length);
            if (frm_length > sizeof(exp_frame)) {
                frm_length = sizeof(exp_frame);
            }

            //printf("INGRESS Encrytped Frame Values - port_no: %d \n", port_no);
#ifdef KAT_TEST_DEBUG
            for (i = 0; i < frm_length; i+=16) {
                T_I("buf[%d]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x ", i,
                frame[i+0], frame[i+1], frame[i+2], frame[i+3], frame[i+4], frame[i+5], frame[i+6], frame[i+7],
                frame[i+8], frame[i+9], frame[i+10], frame[i+11], frame[i+12], frame[i+13], frame[i+14], frame[i+15]);
                printf("buf[%d]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x \n", i,
                frame[i+0], frame[i+1], frame[i+2], frame[i+3], frame[i+4], frame[i+5], frame[i+6], frame[i+7],
                frame[i+8], frame[i+9], frame[i+10], frame[i+11], frame[i+12], frame[i+13], frame[i+14], frame[i+15]);
            }
#endif
            for (i = 0; i < frm_length; i++) {
                if (frame[i] == exp_frame[i]) {
                /* Match, Do Nothing */
                } else {
#ifdef KAT_TEST_DEBUG
                    T_E("ERROR: INGR Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x",
                        port_no, i, exp_frame[i], frame[i]);
                    printf("ERROR: INGR Frame does not Match Expected - port_no: %d,  Byte: %d:: exp_val:0x%02x  val:0x%02x\n",
                        port_no, i, exp_frame[i], frame[i]);
#endif
                    *ing_fail = TRUE;
                }
            }
        } else {
            T_E("ERROR: INGRESS Frame Zero Length (Encrypted) - port_no: %d, frame_length: %d", port_no, frm_length);
            printf("ERROR: INGRESS Frame Zero Length (Encrypted) - port_no: %d, frame_length: %d\n", port_no, frm_length);
            *ing_fail = TRUE;
            return(VTSS_RC_ERROR);
        }
    } else {
        T_E("ERROR: INGRESS Frame Capture Failure - port_no: %d ", port_no);
        //printf("ERROR: INGRESS Frame Capture Failure - port_no: %d \n", port_no);
        *ing_fail = TRUE;
    }

    if (*ing_fail == expect_fail_result) {
        printf("TEST PASSED: TESTING DECRYPT INGRESS: EXPECT NO-MATCH : RESULTS = NO-MATCH - port_no: %d \n", port_no);
        T_I("TEST PASSED: TESTING DECRYPT INGRESS: EXPECT NO-MATCH : RESULTS = NO-MATCH - port_no: %d ", port_no);
        *ing_fail = FALSE;
    } else {
        printf("TEST FAILED: TESTING DECRYPT INGRESS: EXPECT NO-MATCH : RESULTS = MATCH - port_no: %d \n", port_no);
        T_I("TEST FAILED: TESTING DECRYPT INGRESS: EXPECT NO-MATCH : RESULTS = MATCH - port_no: %d ", port_no);
    }

   /* ******************* Clear ALL Loopbacks ************** */
    loopback.far_end_enable = FALSE;
    loopback.near_end_enable = FALSE;
    loopback.connector_enable = FALSE;
    loopback.mac_serdes_input_enable = FALSE;
    loopback.mac_serdes_facility_enable = FALSE;
    loopback.mac_serdes_equipment_enable = FALSE;
    loopback.media_serdes_input_enable = FALSE;
    loopback.media_serdes_facility_enable = FALSE;
    loopback.media_serdes_equipment_enable = FALSE;

    if ((rc = vtss_phy_loopback_set( inst, port_no, loopback)) != VTSS_RC_OK) {
        T_E("ERROR during Disable ALL Loopbacks");
    }
    T_I("Disabling ALL Loopbacks ");

    T_I("Restoring PHY config  ");
    if ((rc = vtss_phy_conf_set(inst, port_no, saved_phyCfg)) != VTSS_RC_OK) {
        T_E("Error Restoring PHY config ");
    }
    if ((rc = vtss_phy_reset(inst, port_no, saved_reset_cfg)) != VTSS_RC_OK) {
        T_E("Error Restoring PHY Reset config ");
    }

    T_I("KAT Complete! ");

    return (rc);
}

vtss_rc vtss_phy_macsec_kat_test(vtss_inst_t                        inst,
                                 const vtss_port_no_t               port_no,
                                 u8                                *egr_fail,
                                 u8                                *ing_fail)
{
    vtss_rc                      rc = VTSS_RC_OK;
    vtss_macsec_port_t           macsec_port;
    vtss_mac_t                   port_macaddress;
    vtss_macsec_sci_t            peer_sci;
    vtss_phy_conf_t              saved_phyCfg = {0};
    vtss_phy_reset_conf_t        saved_resetCfg = {0};
//    BOOL                         encrypt_256 = FALSE; // 128bit Encryption
    BOOL                         encrypt_256 = TRUE;  // 256bit Encryption

    /**************************************** */

   if ((rc = vtss_phy_reset_get(inst, port_no, &saved_resetCfg)) != VTSS_RC_OK) {
        T_E("Unable to Successfully retrieve PHY_RESET_CFG for macsec_kat_test - port_no: %d\n", port_no);
        return rc;
    }

    if ((rc = vtss_phy_macsec_kat_config_secy(inst, port_no, &saved_phyCfg, &saved_resetCfg, &macsec_port, 
                                                             &port_macaddress, &peer_sci, encrypt_256)) != VTSS_RC_OK) {
        T_E("Unable to Successfully configure MACSEC Block for macsec_kat_test - port_no: %d\n", port_no);
        return rc;
    }
    
    if ((rc = vtss_phy_macsec_kat_test_private(inst, port_no, &saved_phyCfg, &saved_resetCfg, 
                                                              encrypt_256, egr_fail, ing_fail)) != VTSS_RC_OK) {
        T_E("vtss_phy_macsec_kat_test: ERROR encountered when Running Known Answer Test (KAT) : rc= 0x%x \n", rc);
    }

    /**************************************** */
    /* Must be outside T_ENTER / VTSS_EXIT */
    printf("Known Answer Test (KAT): Removing SEC-Y \n");
    T_I("vtss_phy_macsec_kat_test: Removing SEC-Y  \n");
    if ((rc = vtss_phy_macsec_kat_secy_system_destroy(inst, &macsec_port, &port_macaddress, &peer_sci)) != VTSS_RC_OK) {
        T_E("vtss_phy_macsec_kat_test: ERROR encountered when Removing SEC-Y  \n");
    }

    if (*egr_fail) {
        printf("TESTING ENCRYPTED EGRESS:  FAIL - port_no: %d \n", port_no);
        T_E("TESTING ENCRYPTED EGRESS:  FAIL - port_no: %d ", port_no);
    } else {
        printf("TESTING ENCRYPTED EGRESS:  PASS - port_no: %d \n", port_no);
        T_I("TESTING ENCRYPTED EGRESS:  PASS - port_no: %d ", port_no);
    }

    if (*ing_fail) {
        printf("TESTING ENCRYPTED INGRESS:  FAIL - port_no: %d \n", port_no);
        T_E("TESTING ENCRYPTED INGRESS:  FAIL - port_no: %d ", port_no);
    } else {
        printf("TESTING ENCRYPTED INGRESS:  PASS - port_no: %d \n", port_no);
        T_I("TESTING ENCRYPTED INGRESS:  PASS - port_no: %d ", port_no);
    }

    T_I("KAT Complete! ");

    return (rc);
}
/* **************************************************************** */
/*            END of KNOWN ANSWER TEST - KAT                        */
/* **************************************************************** */


#endif   // (VTSS_CHIP_CU_PHY) && (KAT_TEST_ENABLE_1G)

#endif /*VTSS_FEATURE_MACSEC */


