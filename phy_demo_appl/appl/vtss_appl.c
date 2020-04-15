/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#include "vtss_api.h"

#if defined(VTSS_FEATURE_LAYER2)

#include "vtss_appl.h"
#include "vtss_appl_cli.h"
#include "vtss_version.h"
#include "port_custom_api.h"

/* Board specifics */
static vtss_appl_board_t board_table;

/* ================================================================= *
 *  Main
 * ================================================================= */

/* Determine if port is connected to 1G PHY */
static BOOL board_port_phy(vtss_appl_board_t *board, vtss_port_no_t port_no)
{
    switch (board->port_interface(port_no)) {
        case VTSS_PORT_INTERFACE_100FX:
        case VTSS_PORT_INTERFACE_RGMII:
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_SGMII_2G5:
        case VTSS_PORT_INTERFACE_QSGMII:
            return 1;
        default:
            return 0;
    }
}

/* Setup port based on configuration and auto negotiation result */
static void port_setup(vtss_appl_board_t *board, vtss_port_no_t port_no, BOOL aneg)
{
    vtss_phy_conf_t         phy;
    vtss_appl_port_conf_t   *pc = &board->port_conf[port_no];
    vtss_appl_port_status_t *ps;
    vtss_port_conf_t        conf;
    
    vtss_port_conf_get(board->inst, port_no, &conf);
    conf.if_type = board->port_interface(port_no);
    conf.power_down = (pc->enable ? 0 : 1);
    conf.flow_control.smac.addr[5] = port_no;
    conf.max_frame_length = pc->max_length;
    
    if (aneg) {
        /* Setup port based on auto negotiation status */
        ps = &board->port_status[port_no];
        conf.speed = ps->speed;
        conf.fdx = ps->fdx;
        conf.flow_control.obey = ps->aneg.obey_pause;
        conf.flow_control.generate = ps->aneg.generate_pause;
    } else {
        /* Setup port based on configuration */
        if (board_port_phy(board, port_no)) {
            /* Setup PHY */
            memset(&phy, 0, sizeof(phy));
            phy.mode = (pc->enable ? 
                        (pc->autoneg || pc->speed == VTSS_SPEED_1G ? 
                         VTSS_PHY_MODE_ANEG : VTSS_PHY_MODE_FORCED) : 
                        VTSS_PHY_MODE_POWER_DOWN);
            phy.aneg.speed_10m_hdx = 1;
            phy.aneg.speed_10m_fdx = 1;
            phy.aneg.speed_100m_hdx = 1;
            phy.aneg.speed_100m_fdx = 1;
            phy.aneg.speed_1g_fdx = 1;
            phy.aneg.symmetric_pause = pc->flow_control;
            phy.aneg.asymmetric_pause = pc->flow_control;
            phy.forced.speed = pc->speed;
            phy.forced.fdx = pc->fdx;
            phy.mdi = VTSS_PHY_MDIX_AUTO; // always enable auto detection of crossed/non-crossed cables
            vtss_phy_conf_set(board->inst, port_no, &phy);
        } else if (conf.if_type == VTSS_PORT_INTERFACE_SERDES) {
            /* IEEE 802.3 clause 37 auto-negotiation */
            vtss_port_clause_37_control_t control;
            vtss_port_clause_37_adv_t     *adv;

            control.enable = pc->autoneg;
            adv = &control.advertisement;
            adv->fdx = 1;
            adv->hdx = 0;
            adv->symmetric_pause = pc->flow_control;
            adv->asymmetric_pause = pc->flow_control;
            adv->remote_fault = (pc->enable ? VTSS_PORT_CLAUSE_37_RF_LINK_OK : 
                                 VTSS_PORT_CLAUSE_37_RF_OFFLINE);
            adv->acknowledge = 0;
            adv->next_page = 0;
            vtss_port_clause_37_control_set(board->inst, port_no, &control);
        }
        /* Use configured values */
        conf.speed = (pc->autoneg ? VTSS_SPEED_1G : pc->speed);
        conf.fdx = pc->fdx;
        conf.flow_control.obey = pc->flow_control;
        conf.flow_control.generate = pc->flow_control;
    }
    vtss_port_conf_set(board->inst, port_no, &conf);
    if (board->port_update)
        board->port_update(board, port_no, &conf);
}

#if defined(VTSS_FEATURE_PACKET)
#if !defined(VTSS_FEATURE_IRQ_CONTROL)
static void packet_poll(vtss_appl_board_t *board)
{
    vtss_packet_rx_queue_t  queue;
    vtss_packet_rx_header_t header;
    u8                      frame[2000];
    u32                     i;
    char                    buf[100], *p;
    
    for (queue = VTSS_PACKET_RX_QUEUE_START; queue < VTSS_PACKET_RX_QUEUE_END; queue++) {
        if (vtss_packet_rx_frame_get(board->inst, queue, &header, frame, 2000) != VTSS_RC_OK)
            continue;

        T_I("received frame on port_no: %u, queue_mask: 0x%08x, length: %u",
            header.port_no, header.queue_mask, header.length);

        /* Dump frame */
        for (i = 0, p = &buf[0]; i < header.length; i++) {
            if ((i % 16) == 0) {
                p = &buf[0];
                p += sprintf(p, "%04x: ", i);
            }
            p += sprintf(p,"%02x%c", frame[i], ((i+9)%16)==0 ? '-' : ' ');
            if (((i+1) % 16) == 0 || (i+1) == header.length) {
                T_D("%s", buf);
            }
        }
    }
}
#endif /* !VTSS_FEATURE_IRQ_CONTROL */

static void setup_rx_reg(void)
{
    vtss_packet_rx_conf_t conf;
    int i;

    // Get Rx packet configuration */
    if (vtss_packet_rx_conf_get(0, &conf) != VTSS_RC_OK) {
        T_E("vtss_packet_rx_conf_get failed");
        return;
    }

    // Setup CPU rx registration
    conf.map.bpdu_queue = (VTSS_PACKET_RX_QUEUE_CNT - 1);

    /* Queue setup */
    for (i = VTSS_PACKET_RX_QUEUE_START; i < VTSS_PACKET_RX_QUEUE_END; i++) {
        conf.queue[i].size = 8 * 1024;
    }

    // Set Rx packet configuration */
    if (vtss_packet_rx_conf_set(0, &conf) != VTSS_RC_OK) {
        T_E("vtss_packet_rx_conf_set failed");
    }
}
#endif /* VTSS_FEATURE_PACKET */

int main(int argc, char **argv)
{
    vtss_appl_board_t       *board = &board_table;
    vtss_inst_create_t      create;
    vtss_init_conf_t        init_conf;
    vtss_port_no_t          port_no;
    vtss_appl_port_conf_t   *pc;
    vtss_appl_port_status_t *ps;
    vtss_port_status_t      status;
    BOOL                    link_old;
    vtss_phy_reset_conf_t   phy_reset;
    BOOL                    port_poll[VTSS_PORT_ARRAY_SIZE];
    BOOL                    init_done = 0;
    vtss_appl_opt           opt;

    /* Parse options */
    memset(&opt, 0, sizeof(opt));
    if (vtss_appl_parse_options(argc, argv, &opt))
        return 1;

    T_D("enter");

    /* Initialize board */
#if defined(BOARD_LUTON10_REF) || defined(BOARD_LUTON26_REF) || defined(BOARD_SERVAL_REF) || defined(BOARD_JAGUAR2_REF) || defined(BOARD_JAGUAR2_CU48_REF) || defined(BOARD_JAGUAR2_AQR_REF) || defined(BOARD_SERVAL2_REF) || defined(BOARD_OCELOT_REF)
    vtss_board_generic_init(board, (argc - opt.count), (const char **)(argv + opt.count));
#endif /* BOARD_xxx */

    /* Initialize board instance */
    T_D("---------- init inst ---------");

    vtss_inst_get(board->target, &create);
    vtss_inst_create(&create, &board->inst);
    
    vtss_init_conf_get(board->inst, &init_conf);
    board->init.init_conf = &init_conf;

    if (board->board_init(argc - opt.count, (const char **)(argv + opt.count), board))
        return 1;
    
    if (vtss_init_conf_set(board->inst, &init_conf) == VTSS_RC_ERROR) {
        T_E("Could not initialize");
        return 1;
    };
    
    if (board->board_probe) {
        board->board_probe(board);
    }

    vtss_port_map_set(board->inst, board->port_map);
    
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        /* Default port status */
        board->port_status[port_no].link = 0;
        
        /* Default port configuration */
        pc = &board->port_conf[port_no];
        memset(pc, 0, sizeof(*pc));
        switch (board->port_interface(port_no)) {
        case VTSS_PORT_INTERFACE_100FX:
            pc->speed = VTSS_SPEED_100M;
            break;
        case VTSS_PORT_INTERFACE_XAUI:  
        case VTSS_PORT_INTERFACE_SFI: 
            pc->speed = VTSS_SPEED_10G;
            break;
        case VTSS_PORT_INTERFACE_VAUI:
            pc->speed = VTSS_SPEED_2500M;
            break;
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_SGMII_2G5:
        case VTSS_PORT_INTERFACE_RGMII:
        case VTSS_PORT_INTERFACE_QSGMII:
            pc->speed = VTSS_SPEED_1G;
            pc->autoneg = 1;
            pc->flow_control = 1;
            break;
        case VTSS_PORT_INTERFACE_SERDES:
            pc->speed = VTSS_SPEED_1G;
            break;
        default:
            T_E("unknown if_type on port %u", port_no);
        }
        pc->enable = 1;
        pc->fdx = 1;
        port_poll[port_no] = (board->port_poll == NULL || 
                              board->port_poll(port_no) ? 1 : 0);
        pc->max_length = VTSS_MAX_FRAME_LENGTH_STANDARD;
        if (board->port_map != NULL && board->port_map[port_no].chip_port < 0) {
            port_poll[port_no] = 0;
        } 
    }
    
    if (board->board_init_post)
        board->board_init_post(board);
    
#if defined(VTSS_FEATURE_PACKET)
    /* Packet RX */
    setup_rx_reg();
#endif
    
    if (board->pre_reset)
        board->pre_reset(); // Mainly PHY pre-reset 
    
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        if (port_poll[port_no] == 0)
            continue;
        
        if (board_port_phy(board, port_no)) {
            phy_reset.mac_if = board->port_interface(port_no);
            phy_reset.media_if = VTSS_PHY_MEDIA_IF_CU;
            vtss_phy_reset(board->inst, port_no, &phy_reset);
        }
        port_setup(board, port_no, 0);
    }
    
    if (board->post_reset)
        board->post_reset(); // Mainly PHY post reset 

    if (board->board_init_done)
        board->board_init_done(board);
    
    if (!opt.quiet) {
        vtss_appl_cli_init();
    }

    for (;;) {
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
#if defined(VTSS_FEATURE_PACKET) && !defined(VTSS_FEATURE_IRQ_CONTROL)
            packet_poll(board);
#endif /* VTSS_FEATURE_PACKET */            
            if (!port_poll[port_no])
                continue;

            if (vtss_port_status_get(board->inst, port_no, &status) != VTSS_RC_OK)
                continue;
            
            ps = &board->port_status[port_no];
            link_old = ps->link;
            ps->link = status.link;
            ps->speed = status.speed;
            ps->fdx = status.fdx;
            ps->aneg.obey_pause = status.aneg.obey_pause;
            ps->aneg.generate_pause = status.aneg.generate_pause;
            /* Detect link down and disable port */
            if ((!status.link || status.link_down) && link_old) {
                port_custom_conf_t   conf;
                vtss_port_counters_t counters;
                
                T_D("link down event on port_no: %u", port_no);
                link_old = 0;
                vtss_port_state_set(board->inst, port_no, 0);
                vtss_mac_table_port_flush(board->inst, port_no);

                memset(&conf, 0, sizeof(port_custom_conf_t));
                conf.enable = board->port_conf[port_no].enable;
                conf.autoneg = board->port_conf[port_no].autoneg;
                conf.speed = board->port_conf[port_no].speed;
                conf.fdx = board->port_conf[port_no].fdx;
                conf.flow_control = board->port_conf[port_no].flow_control;
                conf.max_length = board->port_conf[port_no].max_length;
                
                /* Update led, to turn off it */
                memset(&counters, 0, sizeof(counters));
                port_custom_led_update(port_no, &status, &counters, &conf);
            }
         
            /* Detect link up and setup port */
            if (status.link && !link_old) { 
                T_D("link up event on port_no: %u", port_no);
                vtss_port_state_set(board->inst, port_no, 1);

                if (board->port_conf[port_no].autoneg)
                    port_setup(board, port_no, 1);
            }

            if (!opt.quiet) {
                vtss_appl_cli_task();
            }
        } /* Port loop */

        if (!opt.quiet) {
            vtss_appl_cli_task();
        }
        if (!init_done) {
            init_done = 1;
#if defined(VTSS_FEATURE_WARM_START)
        /* Configuration done */
            vtss_restart_conf_end(board->inst);
#endif /* VTSS_FEATURE_WARM_START */
        }

        if (board->board_periodic)
            board->board_periodic(board);
    } /* for (;;) loop */

    return 0;
}

/* ================================================================= *
 *  API functions
 * ================================================================= */

vtss_appl_board_t *vtss_appl_board_get(vtss_appl_inst_t inst)
{
    return &board_table;
}

static BOOL port_invalid(vtss_appl_board_t *board, const vtss_port_no_t port_no)
{
    return (port_no >= board->port_count || 
            (board->port_poll != NULL && board->port_poll(port_no) == 0));
}

vtss_rc vtss_appl_port_status_get(const vtss_appl_inst_t inst,
                                  const vtss_port_no_t    port_no,
                                  vtss_appl_port_status_t *const status)
{
    vtss_appl_board_t *board = &board_table;
    
    if (port_invalid(board, port_no))
        return VTSS_RC_ERROR;

    *status = board->port_status[port_no];
    return VTSS_RC_OK;
}

/* Get port configuration */
vtss_rc vtss_appl_port_conf_get(const vtss_appl_inst_t inst,
                                const vtss_port_no_t          port_no,
                                vtss_appl_port_conf_t * const conf)
{
    vtss_appl_board_t *board = &board_table;
    
    if (port_invalid(board, port_no))
        return VTSS_RC_ERROR;

    *conf = board->port_conf[port_no];
    return VTSS_RC_OK;
}

/* Set port configuration */
vtss_rc vtss_appl_port_conf_set(const vtss_appl_inst_t inst,
                                const vtss_port_no_t                port_no,
                                const vtss_appl_port_conf_t * const conf)
{
    BOOL                  error = 0, fdx_only;
    vtss_appl_board_t     *board = &board_table;
    port_cap_t            cap;

    if (port_invalid(board, port_no))
        return VTSS_RC_ERROR;

    /* PHY ports must run auto negotiation or 1G/100M/10M */
    if (board_port_phy(board, port_no) && conf->autoneg == 0 && 
        (conf->speed < VTSS_SPEED_10M || conf->speed > VTSS_SPEED_1G))
        error = 1;
    
    /* Speed capability check */
    if (conf->autoneg) {
        cap = PORT_CAP_AUTONEG;
    } else {
        fdx_only = 1;
        switch (conf->speed) {
        case VTSS_SPEED_10M:
            cap = (conf->fdx ? PORT_CAP_10M_FDX : PORT_CAP_10M_HDX);
            fdx_only = 0;
            break;
        case VTSS_SPEED_100M:
            cap = (conf->fdx ? PORT_CAP_100M_FDX : PORT_CAP_100M_HDX);
            fdx_only = 0;
            break;
        case VTSS_SPEED_1G:
            cap = PORT_CAP_1G_FDX;
            break;
        case VTSS_SPEED_2500M:
            cap = PORT_CAP_2_5G_FDX;
            break;
        case VTSS_SPEED_10G:
            cap = PORT_CAP_10G_FDX;
            break;
        default:
            cap = 0;
            break;
        }
        if (fdx_only && conf->fdx == 0) {
            error = 1;
        }
    }
    if ((vtss_board_port_cap(0, port_no) & cap) == 0) {
        error = 1;
    }
    
    if (error) {
        T_D("illegal port or mode, port_no: %u", port_no);
        return VTSS_RC_ERROR;
    }
    
    board->port_conf[port_no] = *conf;
    port_setup(board, port_no, 0);
    return VTSS_RC_OK;
}

vtss_rc vtss_appl_port_if_get(const vtss_appl_inst_t inst,
                              const vtss_port_no_t  port_no,
                              vtss_port_interface_t *const if_type)
{
    vtss_appl_board_t *board = &board_table;
    
    if (port_invalid(board, port_no)) {
        T_D("illegal port : %u", port_no);
        return VTSS_RC_ERROR;
    }
    *if_type = board->port_interface(port_no);
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_LAYER2 */
