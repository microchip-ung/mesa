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

#if defined(BOARD_LUTON10_REF) || defined(BOARD_LUTON26_REF) || defined(BOARD_SERVAL_REF) || defined(BOARD_JAGUAR2_REF) || defined(BOARD_JAGUAR2_CU48_REF) || defined(BOARD_JAGUAR2_AQR_REF) || defined(BOARD_SERVAL2_REF) || defined(BOARD_OCELOT_REF)

#include "vtss_appl.h"
#include "board_probe.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <endian.h>

#include <net/if.h>
#include <sys/ioctl.h>

#include <linux/if_tun.h>
#include <linux/i2c-dev.h>  /* I2C support */

#include <asm/byteorder.h>

#define TUNDEV "/dev/net/tun"

static vtss_port_map_t port_map[VTSS_PORT_ARRAY_SIZE];
const port_custom_entry_t *port_custom_table;

static vtss_board_info_t board_info;    // boards/probe/BSP layer

// Shared with vtss_appl_board_generic_uio.c
BOOL use_tap;
int  tap_fd;
const char *tap_ifname;
vtss_packet_tx_ifh_t tx_ifh;

#if defined (IO_METHOD_UIO)
void board_io_uio_init(vtss_board_info_t *board_info, struct vtss_appl_board_t *board);
#else
void board_io_vrap_init(vtss_board_info_t *board_info, struct vtss_appl_board_t *board);
#endif

static void board_init_post(struct vtss_appl_board_t *board)
{
    (void) port_custom_reset();
    (void) port_custom_led_init();
}

static void board_init_done(struct vtss_appl_board_t *board)
{
#if defined(BOARD_SERVAL_REF)
    // Yuck - why wasn't this wrapped in board layer function!?
    led_tower_update();    // Initial update
#endif
}

static vtss_port_interface_t port_interface(vtss_port_no_t port_no)
{
    if(port_custom_table && port_no < board_info.port_count) {
        return port_custom_table[port_no].mac_if;
    }
    return VTSS_PORT_INTERFACE_NO_CONNECTION;
}

static BOOL port_poll(vtss_port_no_t port_no)
{
#if defined (IO_METHOD_UIO)
    return 1;                   /* Also has NPI port here */
#else
    /* Avoid polling NPI port */
    return (port_no == 10 ? 0 : 1);
#endif
}

static vtss_rc port_update(struct vtss_appl_board_t *board,
                           vtss_port_no_t           port_no, 
                           const vtss_port_conf_t   *pconf)
{
    vtss_port_status_t ps;
    vtss_port_counters_t pc;
    port_custom_conf_t conf;

    memset(&conf, 0, sizeof(conf));

    if (vtss_port_status_get(board->inst, port_no, &ps) == VTSS_RC_OK &&
        vtss_port_counters_get(board->inst, port_no, &pc)  == VTSS_RC_OK) {
        conf.enable = board->port_conf[port_no].enable;
        conf.autoneg = board->port_conf[port_no].autoneg;
        conf.speed = board->port_conf[port_no].speed;
        conf.fdx = board->port_conf[port_no].fdx;
        conf.flow_control = board->port_conf[port_no].flow_control;
        conf.max_length = board->port_conf[port_no].max_length;
        port_custom_conf(port_no, &conf);
        port_custom_led_update(port_no, &ps, &pc, &conf);
    }
    return VTSS_RC_OK;
}

static int maketap (const char *ifname)
{
    struct ifreq ifr;
    int fd, err;

    if( (fd = open(TUNDEV, O_RDWR)) < 0 ) {
        return fd;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
        close(fd);
        return err;
    }

    return fd;
}

/* ================================================================= *
 *  I2C support.
 * ================================================================= */
#if defined VTSS_OPSYS_LINUX
/**
 * \brief Function for doing i2c reads from the switch i2c controller (Using the Linux driver)
 *
 * \param port_no [IN] Port number
 * \param i2c_addr [IN] I2C device address
 * \param addr [IN]   Register address
 * \param data [OUT]  Pointer the register(s) data value.
 * \param cnt [IN]    Number of registers to read
 *
 * \return Return code.
 **/
vtss_rc i2c_read(const vtss_port_no_t port_no, const u8 i2c_addr, const u8 addr, u8 *const data, const u8 cnt)
{
    int file;
    int adapter_nr = 0;        /* probably dynamically determined */
    char filename[20];
    u8 reg_addr = addr;
    int rc_cnt;
    u8 *tmp_data = data;

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) {
        printf("i2c_read: cannot open the file!\n");
        return VTSS_RC_ERROR;
    }

    if (ioctl(file, I2C_SLAVE, i2c_addr) < 0) {
        printf("i2c_read: cannot specify the device!\n");
        return VTSS_RC_ERROR;
    }

    if (write(file, &reg_addr, 1) != 1) {
        printf("i2c_write reg_addr failed! Leads to i2c_read fail!\n");
    }
    
    if ((rc_cnt = read(file, tmp_data, cnt)) != cnt) {
        printf("i2c_read at byte%d: failed! rc_cnt=%d, expect 1\n", cnt, rc_cnt);
        return VTSS_RC_ERROR;
    }    

    return VTSS_RC_OK;
}

/**
 * \brief Function for doing i2c reads from the switch i2c controller (Using the Linux driver)
 *
 * \param port_no [IN] Port number
 * \param i2c_addr [IN] I2C device address
 * \param addr [IN]   Register address
 * \param data [OUT]  Pointer the register(s) data value.
 * \param cnt [IN]    Number of registers to read
 *
 * \return Return code.
 **/
vtss_rc i2c_write(const vtss_port_no_t port_no, const u8 i2c_addr, u8 *const data, const u8 cnt)
{
    int file;
    int adapter_nr = 0;        /* probably dynamically determined */
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) {
        printf("i2c_write: cannot open the file!\n");
        return VTSS_RC_ERROR;
    }

    if (ioctl(file, I2C_SLAVE, i2c_addr) < 0) {
        printf("i2c_write: cannot specify the device!\n");
        return VTSS_RC_ERROR;
    }

    if(write(file, data, cnt) != cnt) {
        printf("i2c_write: failed!\n");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_OPSYS_LINUX */


/* ================================================================= *
 *  Board probe.
 * ================================================================= */

static int board_probe(vtss_appl_board_t *board)
{
    vtss_port_no_t  port_no;
    vtss_rc rc;

    /* Assign I2C support */
    board_info.i2c_read = i2c_read;
    board_info.i2c_write = i2c_write;
    
    /* Detect board type to set */
    rc = vtss_board_probe(&board_info, &port_custom_table);
    //    VTSS_ASSERT(port_custom_table != NULL);

    /* Setup port map for board */
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)
        port_map[port_no] = port_custom_table[port_no].map;
    board->port_map = port_map;

    if (use_tap) {
        vtss_packet_tx_info_t tx_info;
        tap_fd = maketap(tap_ifname);
        if (tap_fd < 0) {
            printf("TAP device %s creation failed, disabling TAP.\n", tap_ifname);
            use_tap = FALSE;
        } else {
            printf("Created '%s' TAP interface, td %d\n", tap_ifname, tap_fd);
        }
        vtss_packet_tx_info_init(NULL, &tx_info);
        tx_info.switch_frm = TRUE;
        vtss_packet_tx_hdr_compile(NULL, &tx_info, &tx_ifh);
    }

    board->descr = vtss_board_name();
    board->port_count =  board_info.port_count;
    printf("Detected '%s' board, %d ports\n", board->descr, board->port_count);

    port_custom_init();

    return rc;
}

/* ================================================================= *
 *  Board init.
 * ================================================================= */

static int board_init(int argc, const char **argv, vtss_appl_board_t *board)
{
    // NB: No I2c support - so no SFP support either
    board->init.init_conf->reg_read = board_info.reg_read;
    board->init.init_conf->reg_write = board_info.reg_write;

#if defined(BOARD_OCELOT_REF)
    board->init.init_conf->mux_mode = VTSS_PORT_MUX_MODE_5;
#endif

    return 0;
}

void vtss_board_generic_init(vtss_appl_board_t *board, int argc, const char **argv)
{
    if(argc > 0) {
        if (strcmp(argv[0],"--tap") == 0) {
            use_tap = TRUE;
            tap_ifname = argc > 1 ? argv[1] : "npi";
        } else {
            printf("Unknown option %s, use:\n"
                   " --tap [<ifname>]: Create TAP inteface with given name.\n", argv[0]);
            exit(1);
        }
    }

    board->descr = "Unprobed Target";
    board->board_init = board_init;
    board->board_probe = board_probe;
    board->board_init_done = board_init_done;
    board->board_init_post = board_init_post;
    board->post_reset = post_port_custom_reset;
    board->port_map = port_map;
    board->port_interface = port_interface;
    board->port_poll = port_poll;
    board->port_update = port_update;

#if defined (IO_METHOD_UIO)
    board_io_uio_init(&board_info, board);
#else
    board_io_vrap_init(&board_info, board);
#endif    // IO_METHOD_UIO

    board_info.port_count = VTSS_PORTS;
    board->target = board_info.target;
}

#endif /* BOARD_xxx */
