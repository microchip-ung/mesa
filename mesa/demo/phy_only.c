// Copyright (c) 2026 Vincent Jardin, Vincent Cruz, Free Mobile
// SPDX-License-Identifier: MIT

// PHY-only mode implementation: see phy_only.h for the rationale.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"
#include "phy_only.h"
#ifdef MEPA_HAS_SPIPROXY
#include <spi_proxy/spiproxy.h>
#endif
#include <linux/gpio.h>
#include <poll.h>
#include "lan80xx_mcu.h"        // gpio_callback_t, lan80xx_MB_INTR_register_callback

// "Dev reset [<port_no>]" CLI handler -- defined below; registered from
// phy_only_init_modules() at the REG phase so no stock file is touched.
static void phy_only_cli_cmd_reset(cli_req_t *req);

// by default, keep legacy mode
mesa_bool_t phy_only_mode = 0;

void phy_only_enter(void)
{
    phy_only_mode = 1;
    printf("No switch UIO device found: PHY-only mode (MEPA slots over SPI only)\n");
}

mesa_rc phy_only_reg_read(const mesa_chip_no_t chip_no,
                          const uint32_t addr,
                          uint32_t *const value)
{
    (void)chip_no;
    (void)addr;
    (void)value;
    return MESA_RC_ERROR; /* no switch on this board */
}

mesa_rc phy_only_reg_write(const mesa_chip_no_t chip_no,
                           const uint32_t addr,
                           const uint32_t value)
{
    (void)chip_no;
    (void)addr;
    (void)value;
    return MESA_RC_ERROR; /* no switch on this board */
}

// Serve the minimal answer the MEBA layer needs and fail
// everything else so callers fall back to their defaults:
// "pcb" = 134 selects the PCB134 board type, whose EDSx path hardcodes
// port_cnt = 9 (PHY slot 1 = ports 0..3) and does not touch switch registers during
// meba_initialize().
mesa_rc phy_only_board_conf_get(const char *tag, char *buf,
                                size_t bufsize, size_t *buflen)
{
    if (strcmp(tag, "pcb") == 0) {
        size_t len = snprintf(buf, bufsize, "134");
        if (buflen) {
            *buflen = len;
        }
        return MESA_RC_OK;
    }
    return MESA_RC_ERROR;
}

// The init_modules() subset that is safe without a MESA switch
// instance: the skipped modules (port, MAC table, VLAN, FDMA packet IO,
// IP, symreg, test, KR, example, UIO IRQs) all drive switch state that
// does not exist here. main_init() and the CLI module have already run
// when this is called.
void phy_only_init_modules(mscc_appl_init_t *init)
{
    if (init->cmd == MSCC_INIT_CMD_INIT) {
        // Register "Dev reset" alongside the stock "Dev Create/Del/conf/
        // Attach": those live in phy_port_config.c and register at the
        // INIT phase too (phy_cli_init() via mscc_appl_phy_init below),
        // because the CLI command list is built at INIT -- a REG-phase
        // registration is dropped. Registering here keeps the stock file
        // untouched. Reuses the global <port_no> parm.
        static cli_cmd_t reset_cmd = {
            "Dev reset [<port_no>]",
            "Hardware-reset the LAN80xx package owning the port via the SPI "
            "proxy (SPIPROXY_RESET); proxy mode only",
            phy_only_cli_cmd_reset,
        };
        mscc_appl_cli_cmd_reg(&reset_cmd);
    }
    if (init->cmd == MSCC_INIT_CMD_INIT) {
        // Normally issued by the (skipped) port module: wires
        // inst->phy_devices to the board state array and installs the
        // MEPA callouts; without it every mepa_dev_create_check() in
        // the demo modules dereferences a NULL phy_devices pointer on
        // the first poll pass.
        MEBA_WRAP(meba_reset, init->board_inst, MEBA_PHY_INITIALIZE);
    }
    mscc_appl_json_rpc_init(init);
    mscc_appl_debug_init(init);
    mscc_appl_trace_init(init);
    mscc_appl_spi_init(init);
    mscc_appl_phy_init(init);
    mscc_appl_kat_demo(init);
    mscc_appl_phy_synce(init);
    mepa_demo_appl_macsec_demo(init);
    mepa_demo_appl_gpio_lp_demo(init);
    mscc_appl_phy_loopback_init(init);
    mscc_appl_phy_xconnect(init);
    mscc_appl_phy_diagnostics_demo(init);
    mscc_appl_phy_restart(init);
    mscc_appl_phy_kr_init(init);
    mepa_demo_appl_ts_demo(init);
    mepa_demo_appl_macsec_rollover_demo(init);
#ifdef MEPA_HAS_LAN80XX
    mscc_appl_m25gdiag_demo(init);
    mscc_appl_mcu_fw_init(init);
#endif
}

//
// Configurable PHY slots (-P option), see phy_only.h.
//
#define PHY_ONLY_SLOT_MAX    8
#define PHY_ONLY_SPI_BYTES   7  /* 3 address + 4 data, as in spi.c */
#define PHY_ONLY_SPI_PAD_MAX 15

#define PHY_ONLY_DEVICE_ID_MMD 0x1E
#define PHY_ONLY_DEVICE_ID_REG 0x0

typedef struct {
    char     dev[sizeof(((struct sockaddr_un *)0)->sun_path)];
    int      pad;
    int      freq;
    uint32_t ports;      /* demo ports covered by this slot */
    uint32_t base;       /* first demo port of this slot */
    int      fd;
    int      proxy;      /* 0 = direct spidev, 1 = via lan80xx-spid */
    uint32_t seq;        /* proxy request sequence */
} phy_only_slot_t;

static phy_only_slot_t phy_only_slot[PHY_ONLY_SLOT_MAX];
static int phy_only_slot_cnt;

// Optional SPI op trace (pre-analysis/debugging)
// set env PHY_ONLY_SPI_TRACE=<file> to log one line per
// logical register access: "<monotonic-us> <port> <R|W> <mmd> <reg>".
// It is Buffered so tracing does not dominate the per-op cost; reads cost
// two SPI transfers on the wire (pipelined dummy read).
static FILE *phy_only_trace_fp = NULL;

static void phy_only_trace_init(void)
{
    const char *path = getenv("PHY_ONLY_SPI_TRACE");

    if (path != NULL && (phy_only_trace_fp = fopen(path, "w")) != NULL) {
        setvbuf(phy_only_trace_fp, NULL, _IOLBF, 0);
        printf("PHY slot SPI trace -> %s\n", path);
    }
}

static void phy_only_trace_op(mepa_port_no_t port_no, mesa_bool_t read,
                              uint8_t mmd, uint16_t reg_num)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    fprintf(phy_only_trace_fp, "%llu %u %c %02x %04x\n",
            (unsigned long long)ts.tv_sec * 1000000ULL + ts.tv_nsec / 1000,
            port_no, read ? 'R' : 'W', mmd, reg_num);
}

int phy_only_slots_configured(void)
{
    return phy_only_slot_cnt;
}

static mesa_rc phy_only_slot_opt(char *parm)
{
    phy_only_slot_t *slot;
    char *s;

    if (phy_only_slot_cnt >= PHY_ONLY_SLOT_MAX) {
        fprintf(stderr, "-P: at most %d PHY slots\n", PHY_ONLY_SLOT_MAX);
        return MESA_RC_ERROR;
    }
    slot = &phy_only_slot[phy_only_slot_cnt];
    slot->pad = 1;
    slot->freq = 15000000;
    slot->ports = 4;

    if (strncmp(parm, "proxy:", 6) == 0) {
#ifndef MEPA_HAS_SPIPROXY
        fprintf(stderr, "-P proxy: not built: install the mepa_spidev_proxy dev "
                "package and rebuild to enable SPI-proxy client mode\n");
        return MESA_RC_ERROR;
#else
        // via lan80xx-spid: proxy:<socket-path>[:ports], pad/freq
        // belong to the daemon. ':ports' = trailing ':' + digits.
        slot->proxy = 1;
        parm += 6;
        if ((s = strrchr(parm, ':')) != NULL && s[1] >= '0' && s[1] <= '9') {
            *s++ = 0;
            slot->ports = atoi(s);
        }
#endif
    } else {
        if ((s = strchr(parm, ':')) != NULL) {
            *s++ = 0;
            slot->ports = atoi(s);
        }
        if ((s = strchr(parm, '@')) != NULL) {
            *s++ = 0;
            slot->pad = atoi(s);
            if (slot->pad > PHY_ONLY_SPI_PAD_MAX) {
                slot->pad = PHY_ONLY_SPI_PAD_MAX;
            }
            if ((s = strchr(s, '@')) != NULL) {
                *s++ = 0;
                slot->freq = atoi(s);
            }
        }
    }
    if (slot->ports < 1 || slot->ports > 4) {
        fprintf(stderr, "-P: ports must be 1..4\n");
        return MESA_RC_ERROR;
    }
    if ((size_t)snprintf(slot->dev, sizeof(slot->dev), "%s", parm) >= sizeof(slot->dev)) {
        fprintf(stderr, "-P: path too long (max %zu chars)\n", sizeof(slot->dev) - 1);
        return MESA_RC_ERROR;
    }
    slot->base = phy_only_slot_cnt ?
                 (phy_only_slot[phy_only_slot_cnt - 1].base +
                  phy_only_slot[phy_only_slot_cnt - 1].ports) : 0;
    phy_only_slot_cnt++;
    if (slot->proxy) {
        printf("PHY slot %d: proxy %s, ports %u..%u\n",
               phy_only_slot_cnt, slot->dev, slot->base,
               slot->base + slot->ports - 1);
    } else {
        printf("PHY slot %d: %s, ports %u..%u, %d padding byte(s) at %d Hz\n",
               phy_only_slot_cnt, slot->dev, slot->base,
               slot->base + slot->ports - 1, slot->pad, slot->freq);
    }
    return MESA_RC_OK;
}

static mscc_appl_opt_t phy_only_opt = {
    "P:",
    "<spidev[@pad[@freq]]|proxy:sock>[:ports]",
    "PHY-only slot: one PHY package serving 'ports' (default 4 =\n"
    "                          quad footprint; repeatable; forces PHY-only mode and replaces\n"
    "                          the built-in slot devices). Direct spidev access, or shared\n"
    "                          access through the SPI proxy socket (proxy:<path>).",
    phy_only_slot_opt
};

void phy_only_opt_reg(void)
{
    mscc_appl_opt_reg(&phy_only_opt);
}

#ifdef MEPA_HAS_SPIPROXY
// Connect (or reconnect after a daemon restart) a proxy-mode slot
static mesa_rc phy_only_proxy_connect(phy_only_slot_t *slot)
{
    struct sockaddr_un sa = { .sun_family = AF_UNIX };
    int fd = socket(AF_UNIX, SOCK_SEQPACKET, 0);

    snprintf(sa.sun_path, sizeof(sa.sun_path), "%s", slot->dev);
    if (fd < 0 || connect(fd, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        fprintf(stderr, "proxy %s: %s\n", slot->dev, strerror(errno));
        if (fd >= 0) {
            close(fd);
        }
        slot->fd = -1;
        return MESA_RC_ERROR;
    }
    slot->fd = fd;
    return MESA_RC_OK;
}
#endif

mesa_rc phy_only_slots_open(void)
{
    int i, fd, mode = 0;

    phy_only_trace_init();
    for (i = 0; i < phy_only_slot_cnt; i++) {
#ifdef MEPA_HAS_SPIPROXY
        if (phy_only_slot[i].proxy) {
            if (phy_only_proxy_connect(&phy_only_slot[i]) != MESA_RC_OK) {
                return MESA_RC_ERROR;
            }
            continue;
        }
#endif
        fd = open(phy_only_slot[i].dev, O_RDWR);
        if (fd < 0) {
            fprintf(stderr, "%s: %s\n", phy_only_slot[i].dev, strerror(errno));
            return MESA_RC_ERROR;
        }
        if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0 ||
            ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0) {
            fprintf(stderr, "%s: cannot set spi mode\n", phy_only_slot[i].dev);
            close(fd);
            return MESA_RC_ERROR;
        }
        phy_only_slot[i].fd = fd;
    }
    return MESA_RC_OK;
}

// One SPI transfer in the spi.c frame format: 23-bit address
// (bit 23 = write) + 32-bit data; reads append the slot's padding bytes.
static mesa_rc phy_only_xfer(phy_only_slot_t *slot, mesa_bool_t read,
                             uint32_t addr, uint32_t *const data)
{
    uint8_t tx[PHY_ONLY_SPI_BYTES + PHY_ONLY_SPI_PAD_MAX];
    uint8_t rx[sizeof(tx)] = { 0 };
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = PHY_ONLY_SPI_BYTES + (read ? slot->pad : 0),
        .speed_hz = slot->freq,
        .bits_per_word = 8,
    };

    memset(tx, 0xff, sizeof(tx));
    tx[0] = (uint8_t)((read ? 0 : 0x80) | ((addr >> 16) & 0x7f));
    tx[1] = (uint8_t)(addr >> 8);
    tx[2] = (uint8_t)(addr >> 0);
    if (!read) {
        tx[3] = (uint8_t)(*data >> 24);
        tx[4] = (uint8_t)(*data >> 16);
        tx[5] = (uint8_t)(*data >> 8);
        tx[6] = (uint8_t)(*data >> 0);
    }
    if (ioctl(slot->fd, SPI_IOC_MESSAGE(1), &tr) < 1) {
        return MESA_RC_ERROR;
    }
    if (read) {
        *data = (rx[3] << 24) | (rx[4] << 16) | (rx[5] << 8) | rx[6];
    }
    return MESA_RC_OK;
}

#ifdef MEPA_HAS_SPIPROXY
// Register access through the SPI proxy:
// one L1 READ/WRITE request/response (the daemon handles the pipelined
// dummy read).
// One transparent reconnect attempt for a daemon restart
static mesa_rc phy_only_proxy_rw(phy_only_slot_t *slot, uint32_t ch_no,
                                 mesa_bool_t read, uint8_t mmd,
                                 uint16_t reg_num, uint32_t *const data)
{
    struct {
        struct spiproxy_hdr h;
        struct spiproxy_op op;
    } msg;
    int retry;
    ssize_t n;

    for (retry = 0; retry < 2; retry++) {
        if (slot->fd < 0 && phy_only_proxy_connect(slot) != MESA_RC_OK) {
            return MESA_RC_ERROR;
        }
        memset(&msg, 0, sizeof(msg));
        msg.h.ver = SPIPROXY_VER;
        msg.h.type = read ? SPIPROXY_READ : SPIPROXY_WRITE;
        msg.h.seq = ++slot->seq;
        msg.h.len = sizeof(msg.op);
        msg.op.slice = (uint8_t)ch_no;
        msg.op.write = !read;
        msg.op.mmd = mmd;
        msg.op.reg = reg_num;
        msg.op.val = read ? 0 : *data;
        if (send(slot->fd, &msg, sizeof(msg), MSG_NOSIGNAL) < 0 ||
            (n = recv(slot->fd, &msg, sizeof(msg), 0)) < (ssize_t)sizeof(msg.h)) {
            close(slot->fd);
            slot->fd = -1;
            continue; /* daemon gone: reconnect once */
        }
        if (msg.h.seq != slot->seq ||
            msg.h.type != ((read ? SPIPROXY_READ : SPIPROXY_WRITE) | SPIPROXY_RESP) ||
            msg.h.flags != SPIPROXY_OK) {
            return MESA_RC_ERROR;
        }
        if (read) {
            *data = msg.op.val;
        }
        return MESA_RC_OK;
    }
    return MESA_RC_ERROR;
}
#endif /* MEPA_HAS_SPIPROXY */

// SPI register access for a demo port through the -P slot table. Same
// register/channel encoding as the built-in slots.
mesa_rc phy_only_spi_rw(mepa_port_no_t port_no, mesa_bool_t read,
                        uint8_t mmd, uint16_t reg_num, uint32_t *const data)
{
    phy_only_slot_t *slot = NULL;
    uint32_t ch_no, addr;
    int i;

    for (i = 0; i < phy_only_slot_cnt; i++) {
        if (port_no >= phy_only_slot[i].base &&
            port_no < phy_only_slot[i].base + phy_only_slot[i].ports) {
            slot = &phy_only_slot[i];
            break;
        }
    }
    if (slot == NULL) {
        return MESA_RC_ERROR;
    }
    if (phy_only_trace_fp != NULL) {
        phy_only_trace_op(port_no, read, mmd, reg_num);
    }
    ch_no = slot->base + slot->ports - 1 - port_no;
#ifdef MEPA_HAS_SPIPROXY
    if (slot->proxy) {
        return phy_only_proxy_rw(slot, ch_no, read, mmd, reg_num, data);
    }
#endif
    if (slot->fd <= 0) {
        return MESA_RC_ERROR;
    }
    addr = ch_no << 21 | mmd << 16 | reg_num;
    if (read) {
        if (phy_only_xfer(slot, 1, addr, data) != MESA_RC_OK) {
            return MESA_RC_ERROR;
        }
        addr = ch_no << 21 | PHY_ONLY_DEVICE_ID_MMD << 16 | PHY_ONLY_DEVICE_ID_REG;
        return phy_only_xfer(slot, 1, addr, data);
    }
    return phy_only_xfer(slot, 0, addr, data);
}

// Hardware-reset the LAN80xx package owning `port_no` by asking the SPI
// proxy to pulse its reset GPIO (SPIPROXY_RESET, daemon defaults for the
// pulse timing). Only possible in proxy mode: a direct-spidev slot has
// no daemon and therefore no reset GPIO. The whole package is reset, so
// the per-port -> channel mapping is irrelevant here.
static mesa_rc phy_only_reset(mepa_port_no_t port_no)
{
#ifndef MEPA_HAS_SPIPROXY
    (void)port_no;
    fprintf(stderr, "Dev reset: not built: install the mepa_spidev_proxy dev "
            "package and rebuild (HW reset uses SPIPROXY_RESET)\n");
    return MESA_RC_ERROR;
#else
    phy_only_slot_t *slot = NULL;
    struct {
        struct spiproxy_hdr   h;
        struct spiproxy_reset r;
    } msg;
    int i, retry;
    ssize_t n;

    for (i = 0; i < phy_only_slot_cnt; i++) {
        if (port_no >= phy_only_slot[i].base &&
            port_no < phy_only_slot[i].base + phy_only_slot[i].ports) {
            slot = &phy_only_slot[i];
            break;
        }
    }
    if (slot == NULL) {
        return MESA_RC_ERROR;
    }
    if (!slot->proxy) {
        fprintf(stderr, "Dev reset: HW reset needs proxy mode "
                "(-P proxy:<sock>); a direct spidev slot has no reset GPIO. "
                "A soft GLOBAL_FAST_RESET over SPI wedges the chip.\n");
        return MESA_RC_ERROR;
    }
    for (retry = 0; retry < 2; retry++) {
        if (slot->fd < 0 && phy_only_proxy_connect(slot) != MESA_RC_OK) {
            return MESA_RC_ERROR;
        }
        memset(&msg, 0, sizeof(msg));
        msg.h.ver = SPIPROXY_VER;
        msg.h.type = SPIPROXY_RESET;
        msg.h.seq = ++slot->seq;
        msg.h.len = sizeof(msg.r);
        /* r.assert_us = r.deassert_us = 0 -> daemon defaults (10/100 ms) */
        if (send(slot->fd, &msg, sizeof(msg), MSG_NOSIGNAL) < 0 ||
            (n = recv(slot->fd, &msg, sizeof(msg), 0)) < (ssize_t)sizeof(msg.h)) {
            close(slot->fd);
            slot->fd = -1;
            continue; /* daemon gone: reconnect once */
        }
        if (msg.h.seq != slot->seq ||
            msg.h.type != (SPIPROXY_RESET | SPIPROXY_RESP)) {
            return MESA_RC_ERROR;
        }
        if (msg.h.flags == SPIPROXY_ENOSYS) {
            fprintf(stderr, "Dev reset: the daemon has no reset GPIO -- start "
                    "lan80xx-spid with -r <line-name> (e.g. -r lan8023-rst)\n");
            return MESA_RC_ERROR;
        }
        return msg.h.flags == SPIPROXY_OK ? MESA_RC_OK : MESA_RC_ERROR;
    }
    return MESA_RC_ERROR;
#endif /* MEPA_HAS_SPIPROXY */
}

static void phy_only_cli_cmd_reset(cli_req_t *req)
{
    if (phy_only_reset(req->port_no) == MESA_RC_OK) {
        cli_printf("Dev reset: port %u package HW-reset via proxy "
                   "(PHY released, run state)\n", req->port_no);
    } else {
        cli_printf("Dev reset: port %u failed\n", req->port_no);
    }
}

// LAN80xx mailbox host-interrupt (MDINT) over a Linux GPIO line.
//
// The LAN80xx asserts its mailbox "response ready" host interrupt on an INTR
// pin. On a switch-less board (no MESA switch) that pin is wired to a host SoC
// GPIO instead of a MESA-switch GPIO, so register a MEPA gpio callback backed
// by that GPIO through the Linux character-device uAPI (v2) with falling-edge
// events: the mailbox then waits on the real interrupt instead of polling the
// flag over SPI.
#define PHY_ONLY_MDINT_ENV  "LAN80XX_MDINT"
#define PHY_ONLY_MDINT_DEF  "lan8023-mdint"   // DT gpio-line-names; probed across all gpiochips

#define PHY_ONLY_MDINT_POLL_MS  8

static int phy_only_mdint_fd = -1;   // line-request fd (edge events + values)

// Find the gpiochip line whose DTS name (gpio-line-names) is name by scanning
// /dev/gpiochip0..63 and matching each line's name. On a match fill chip with
// the owning "/dev/gpiochipN" path and *off with the line offset, return 0;
// return -1 if no chip carries that name. Same probing pattern as the SPI-proxy
// daemon's gpio_open_line_by_name().
static int gpio_find_line_by_name(const char *name, char *chip, size_t chipsz,
                                  unsigned int *off)
{
    int n;

    for (n = 0; n < 64; n++) {
        struct gpiochip_info ci;
        uint32_t o;
        int cfd;

        snprintf(chip, chipsz, "/dev/gpiochip%d", n);
        cfd = open(chip, O_RDONLY | O_CLOEXEC);
        if (cfd < 0) {
            continue;
        }
        memset(&ci, 0, sizeof(ci));
        if (ioctl(cfd, GPIO_GET_CHIPINFO_IOCTL, &ci) == 0) {
            for (o = 0; o < ci.lines; o++) {
                struct gpio_v2_line_info li;

                memset(&li, 0, sizeof(li));
                li.offset = o;
                if (ioctl(cfd, GPIO_V2_GET_LINEINFO_IOCTL, &li) == 0 &&
                    strcmp(li.name, name) == 0) {
                    *off = o;
                    close(cfd);
                    return 0;
                }
            }
        }
        close(cfd);
    }
    return -1;
}

// Open the INTR line and request it: input, falling-edge events. cfg is either
//   - a DT line name from gpio-line-names (e.g. "lan8023-mdint"), probed across
//     every gpiochip (preferred: chip numbers/offsets are not stable, names are);
//   - or an explicit "<chip-path>:<line>" (e.g. "/dev/gpiochip2:0"), recognised
//     by the '/' it contains.
// NULL uses $LAN80XX_MDINT, else the built-in default. Idempotent; 0 on success.
static int phy_only_mdint_open(const char *cfg)
{
    char chip[64];
    unsigned int line = 0;
    const char *s, *colon;
    int cfd;
    struct gpio_v2_line_request req;

    if (phy_only_mdint_fd >= 0) {
        return 0;
    }
    s = (cfg && *cfg) ? cfg : getenv(PHY_ONLY_MDINT_ENV);
    if (!s || !*s) {
        s = PHY_ONLY_MDINT_DEF;
    }
    if (strchr(s, '/')) {
        // explicit "<chip-path>:<line>", e.g. "/dev/gpiochip2:0"
        colon = strrchr(s, ':');
        if (colon) {
            size_t n = (size_t)(colon - s);
            if (n >= sizeof(chip)) {
                n = sizeof(chip) - 1;
            }
            memcpy(chip, s, n);
            chip[n] = '\0';
            line = (unsigned int)strtoul(colon + 1, NULL, 0);
        } else {
            snprintf(chip, sizeof(chip), "%s", s);
        }
    } else {
        // a DT line name (gpio-line-names), e.g. "lan8023-mdint": find which
        // gpiochip/offset currently carries it.
        if (gpio_find_line_by_name(s, chip, sizeof(chip), &line) != 0) {
            fprintf(stderr, "MDINT: GPIO line '%s' not found on any gpiochip\n", s);
            return -1;
        }
    }

    cfd = open(chip, O_RDONLY | O_CLOEXEC);
    if (cfd < 0) {
        fprintf(stderr, "MDINT: open %s: %s\n", chip, strerror(errno));
        return -1;
    }
    // INTR is active-low (its DT line name ends in '#'):
    // asserted = physical low = a falling edge.
    // Do NOT set GPIO_V2_LINE_FLAG_ACTIVE_LOW here: that would
    // turn the logical falling edge into a physical rising edge, which some GPIO
    // irqchips reject (e.g. mpc8xxx: irq_set_type mode 1 fails). Request the
    // physical falling edge and invert the level in software instead (the
    // active-low sense is handled in phy_only_mdint_gpio_cb()).
    memset(&req, 0, sizeof(req));
    req.offsets[0] = line;
    req.num_lines  = 1;
    snprintf(req.consumer, sizeof(req.consumer), "lan80xx-mdint");
    req.config.flags = GPIO_V2_LINE_FLAG_INPUT | GPIO_V2_LINE_FLAG_EDGE_FALLING;
    if (ioctl(cfd, GPIO_V2_GET_LINE_IOCTL, &req) < 0 || req.fd < 0) {
        // Some GPIO controllers can't deliver edge events on this line. Fall
        // back to a level-only request: the callback still reads the real pin
        // (the driver's mailbox loop provides the polling cadence).
        memset(&req, 0, sizeof(req));
        req.offsets[0] = line;
        req.num_lines  = 1;
        snprintf(req.consumer, sizeof(req.consumer), "lan80xx-mdint");
        req.config.flags = GPIO_V2_LINE_FLAG_INPUT;
        if (ioctl(cfd, GPIO_V2_GET_LINE_IOCTL, &req) < 0 || req.fd < 0) {
            fprintf(stderr, "MDINT: request %s line %u: %s\n", chip, line, strerror(errno));
            close(cfd);
            return -1;
        }
        close(cfd);
        phy_only_mdint_fd = req.fd;
        (void)fcntl(phy_only_mdint_fd, F_SETFL, O_NONBLOCK);
        printf("MDINT: %s line %u (level, no edge events) ready, fd=%d\n",
               chip, line, phy_only_mdint_fd);
        return 0;
    }
    close(cfd);                  // req.fd is the live line handle
    phy_only_mdint_fd = req.fd;
    (void)fcntl(phy_only_mdint_fd, F_SETFL, O_NONBLOCK);   // non-blocking event drain
    printf("MDINT: %s line %u (falling-edge events) ready, fd=%d\n",
           chip, line, phy_only_mdint_fd);
    return 0;
}

// MEPA gpio_callback_t
//
// Block in poll() on the line-event fd for up to PHY_ONLY_MDINT_POLL_MS,
// sleeping the calling thread until the INTR edge fires (returns within
// microseconds of the edge) or the window elapses. A falling edge means the
// line went active (INTR asserted), so return 1 and drain the queued events
// (fd is O_NONBLOCK). If no edge arrives in the window, fall back to reading
// the current level: covers a steadily-asserted line and the level-only
// request (no edge events). The INTR is active-low (no ACTIVE_LOW flag on the
// request): asserted == physical 0.
//
// No thread and no central loop is used here on purpose: the mailbox wait is
// synchronous inside a CLI command, so the demo's select() loop
// (fd_read_register/main.c) is blocked meanwhile and cannot service this fd.
// For ASYNC PHY events (link/PTP) that same fd can instead be handed to
// fd_read_register() so the central loop dispatches edges while idle.
static uint8_t phy_only_mdint_gpio_cb(const mepa_device_t *dev)
{
    struct gpio_v2_line_values vals;
    struct pollfd pfd;

    (void)dev;
    if (phy_only_mdint_fd < 0 && phy_only_mdint_open(NULL) != 0) {
        return 0;
    }
    pfd.fd = phy_only_mdint_fd;
    pfd.events = POLLIN;
    if (poll(&pfd, 1, PHY_ONLY_MDINT_POLL_MS) > 0 && (pfd.revents & POLLIN)) {
        struct gpio_v2_line_event ev;
        while (read(phy_only_mdint_fd, &ev, sizeof(ev)) > 0) {
            // drain (O_NONBLOCK): read() returns -1/EAGAIN when empty
        }
        return 1;                // falling edge == host interrupt asserted
    }
    memset(&vals, 0, sizeof(vals));
    vals.mask = 1;               // line index 0 in this request
    if (ioctl(phy_only_mdint_fd, GPIO_V2_LINE_GET_VALUES_IOCTL, &vals) < 0) {
        return 0;
    }
    return (vals.bits & 1) ? 0 : 1;
}

mesa_rc phy_only_mdint_register(const mepa_device_t *dev, const char *gpiochip_line)
{
    if (phy_only_mdint_open(gpiochip_line) != 0) {
        return MESA_RC_ERROR;
    }
    // XXX TODO: for ASYNC PHY events (link change, PTP, MACsec) hand
    // phy_only_mdint_fd to fd_read_register() so the demo's central select()
    // loop (main.c) dispatches INTR edges while idle, then poll the PHY event
    // status in that handler. Not wired yet: there is no async consumer, and
    // the mailbox path above must not share the fd with the central loop while
    // a synchronous CLI command is in flight.
    return lan80xx_MB_INTR_register_callback(dev, phy_only_mdint_gpio_cb);
}
