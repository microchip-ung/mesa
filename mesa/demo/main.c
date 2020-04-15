/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/i2c.h>      /* I2C support */
#include <linux/i2c-dev.h>  /* I2C support */
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/syscall.h>

#include "mscc/ethernet/switch/api.h"
#include "mscc/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"
#include "ipc.h"

#define ARRSZ(_x_)  (sizeof(_x_) / sizeof((_x_)[0]))

#define I2C_PORT2DEV(p) (100 + p)

// Local data
static int LOOP_PORT = -1;

static mscc_appl_trace_module_t trace_module = {
    .name = "main"
};

enum {
    TRACE_GROUP_DEFAULT,
    TRACE_GROUP_MEBA,
    TRACE_GROUP_CNT
};

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    // TRACE_GROUP_MEBA
    {
        .name = "meba",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

static mscc_appl_init_t appl_init;
static void init_modules(mscc_appl_init_t *init);

/**
 * Open i2c adapter from user space, return the file descriptor for further i2c read/write.
 * @param[in] adapter_nr zero by default
 * @param[in] i2c_addr i2c slave address
 * @return fileno
 */
static int i2c_adapter_open(int adapter_nr, int i2c_addr)
{
    char filename[20];  /* 20 char should be enough for holding the file name */
    int file;

    snprintf(filename, sizeof(filename), "/dev/i2c-%d", adapter_nr);
    if ((file = open(filename, O_RDWR)) >= 0) {
        T_I("Opened(%s)", filename);
        if (ioctl(file, I2C_SLAVE, i2c_addr) < 0) {
            T_I("cannot specify i2c slave at 0x%02x! [%s]\n", i2c_addr, strerror(errno));
        }
    } else {
        T_I("cannot open /dev/i2c-%d! [%s]\n", adapter_nr, strerror(errno));
    }
    return file;
}

/**
 * \brief Function for doing i2c reads from the switch i2c controller
 *
 * \param port_no [IN] Port number
 * \param i2c_addr [IN] I2C device address
 * \param addr [IN]   Register address
 * \param data [OUT]  Pointer the register(s) data value.
 * \param cnt [IN]    Number of registers to read
 *
 * \return Return code.
 **/
static mesa_rc i2c_read(const mesa_port_no_t port_no,
                        const uint8_t i2c_addr,
                        const uint8_t addr,
                        uint8_t *const data,
                        const uint8_t cnt)
{
    int file;
    mesa_rc rc = MESA_RC_ERROR;
    if ((file = i2c_adapter_open(I2C_PORT2DEV(port_no), i2c_addr)) >= 0) {
        struct i2c_rdwr_ioctl_data packets;
        struct i2c_msg messages[2];

        // Write portion
        messages[0].addr  = i2c_addr;
        messages[0].flags = 0;
        messages[0].len   = 1;
        *data = addr;    // (Re-)Use the read buffer for the address write
        messages[0].buf   = data;

        // Read portion
        messages[1].addr  = i2c_addr;
        messages[1].flags = I2C_M_RD /* | I2C_M_NOSTART*/;
        messages[1].len   = cnt;
        messages[1].buf   = data;

        /* Transfer the i2c packets to the kernel and verify it worked */
        packets.msgs  = messages;
        packets.nmsgs = ARRSZ(messages);
        if(ioctl(file, I2C_RDWR, &packets) < 0) {
            T_I("I2C transfer failed: %s, port_no: %u, i2c_addr: %u, addr: %u, cnt: %u", strerror(errno), port_no, i2c_addr, addr, cnt);
        } else {
            rc = MESA_RC_OK;
        }
        close(file);
    }
    T_D("i2c read port %d, addr 0x%x, %d bytes - RC %d", port_no, i2c_addr, cnt, rc);
    return rc;
}

/**
 * \brief Function for doing i2c reads from the switch i2c controller
 *
 * \param port_no [IN] Port number
 * \param i2c_addr [IN] I2C device address
 * \param data [OUT]  Pointer the register(s) data value.
 * \param cnt [IN]    Number of registers to read
 *
 * \return Return code.
 **/
static mesa_rc i2c_write(const mesa_port_no_t port_no,
                         const uint8_t i2c_addr,
                         uint8_t *const data,
                         const uint8_t cnt)
{
    int file;
    mesa_rc rc = MESA_RC_ERROR;
    if ((file = i2c_adapter_open(I2C_PORT2DEV(port_no), i2c_addr)) >= 0) {
        struct i2c_rdwr_ioctl_data packets;
        struct i2c_msg messages[1];

        // Write portion
        messages[0].addr  = i2c_addr;
        messages[0].flags = 0;
        messages[0].len   = cnt;
        messages[0].buf   = data;

        /* Transfer the i2c packets to the kernel and verify it worked */
        packets.msgs  = messages;
        packets.nmsgs = ARRSZ(messages);
        if(ioctl(file, I2C_RDWR, &packets) < 0) {
            T_I("I2C transfer failed!: %s", strerror(errno));
        } else {
            rc = MESA_RC_OK;
        }
        close(file);
    }
    T_D("i2c write port %d, addr 0x%x, %d bytes - RC %d", port_no, i2c_addr, cnt, rc);
    return rc;
}

static mesa_rc load_board_driver(const char *path, const vtss_board_type_t type)
{
#if !defined(__NR_finit_module)
#error "Modules loading is not supported by the kernel"
#endif

    char board_type[50];
    int res = 0, fd;
    FILE *fp;
    mesa_rc rc = MESA_RC_OK;

    if (access("/sys/bus/platform/drivers/i2c_designware/bind", F_OK) == 0) {
        return MESA_RC_OK; // Using device tree on LS1046
    }

    if ((fp = fopen("/sys/firmware/devicetree/base/model", "r"))) {
        char model[128];
        const char *m = fgets(model, sizeof(model), fp);
        fclose(fp);
        if (m && strstr(model, "BeagleBone")) {
            T_I("Board model: %s", model);
            return MESA_RC_OK; // Using device tree on BeagleBone
        }
    }

    if (access("/proc/modules", F_OK | R_OK) != 0) {
        T_E("Kernel lacks module support, not loading %s", path);
        return MESA_RC_ERROR;
    }

    fd = open(path, O_RDONLY|O_CLOEXEC);
    if (fd < 0) {
        T_E("Unable to open driver %s: %s", path, strerror(errno));
        return MESA_RC_ERROR;
    }

    // finit_module(int fd, const char *uargs, int flags)
    snprintf(board_type, sizeof(board_type), "board_type=%d", type);
    T_D("%s", board_type);
    res = syscall(__NR_finit_module, fd, board_type, 0);
    if (res == -1) {
        if (errno == EEXIST) {
            T_I("Kernel module already loaded: %s", path);
            goto EXIT_CLOSE;
        }
        T_E("Unable to init driver %s: %s", path, strerror(errno));
        rc = MESA_RC_ERROR;
        goto EXIT_CLOSE;
    }
    T_I("Kernel module loaded: %s", path);

EXIT_CLOSE:
    close(fd);
    return rc;
}

static mesa_rc board_conf_get(const char *tag, char *buf, size_t bufsize, size_t *buflen)
{
    uint32_t   port_cnt = mesa_port_cnt(NULL);
    const char *board = NULL;
    uint32_t   target = 0;
    uint32_t   type = 1000;
    uint32_t   port_cfg = 1000;
    size_t     len = 0;
    uint32_t   mux_mode = 0xffffffff;

    /* Board detection is currently done based on MESA capabilities */
    switch (mesa_capability(NULL, MESA_CAP_MISC_CHIP_FAMILY)) {
    case MESA_CHIP_FAMILY_CARACAL:
        if (port_cnt > 10) {
            board = "Luton26";
            target = 0x7429;
        } else {
            board = "Luton10";
            target = 0x7428;
        }
        break;

    case MESA_CHIP_FAMILY_OCELOT:
        // TODO, it currently assumes that we are PCB123
        board = "Ocelot Ref (pcb123)";
        mux_mode = 1;
        break;

    case MESA_CHIP_FAMILY_JAGUAR2:
        if (port_cnt > 48) {
            board = "Jaguar2-cu48";
            target = 0x7449;
            type = 1;
        } else if (port_cnt < 20) {
            board = "Serval2 NID";
            target = 0x7438;
            type = 0;
        } else {
            board = "Jaguar2-cu8sfp16";
            target = 0x7468;
            type = 2;
        }
        break;

    case MESA_CHIP_FAMILY_JAGUAR3:   // JR3 SparX/SparXi Family
        if (mesa_capability(NULL, MESA_CAP_SYNCE)) {  // SparXi Family
            if (port_cnt == 7) {
                board = "SparX-5i-SFP6";  // Board-name for info
                target = 0x47546;         // maps to vtss_target_type_t
                type = 0;                 // maps to board_type_t in MEBA;
                port_cfg = 2;             // maps to port configuration in MEBA;
            } else if (port_cnt == 9) {
                board = "SparX-5i-SFP8";
                target = 0x47558;
                type = 0;
                port_cfg = 2;
            } else if (port_cnt == 10) {
                board = "Sparx-5i-SFP9";
                target = 0x47549;
                type = 0;
                port_cfg = 3;
            } else if (port_cnt == 13) {
                board = "Sparx-5i-SFP12";
                target = 0x47552;
                type = 0;
                port_cfg = 4;
            } else if (port_cnt == 21) {
                board = "Sparx-5i-SFP20";
                target = 0x47558;
                type = 0;
                port_cfg = 0;
            } else if (port_cnt == 57) {
                board = "Sparx-5i-Cu48";
                target = 0x47556;
                type = 1;
            }
        } else {   // SparX Family
            if (port_cnt == 7) {
                board = "SparX-5-SFP6";  // Board-name for info
                target = 0x7546;         // maps to vtss_target_type_t
                type = 0;                // maps to board_type_t in MEBA;
                port_cfg = 2;            // maps to port configuration in MEBA;
            } else if (port_cnt == 9) {
                board = "SparX-5-SFP8";
                target = 0x7558;
                type = 0;
                port_cfg = 2;
            } else if (port_cnt == 10) {
                board = "Sparx-5-SFP9";
                target = 0x7549;
                type = 0;
                port_cfg = 3;
            } else if (port_cnt == 13) {
                board = "Sparx-5-SFP12";
                target = 0x7552;
                type = 0;
                port_cfg = 4;
            } else if (port_cnt == 21) {
                board = "Sparx-5-SFP20";
                target = 0x7558;
                type = 0;
                port_cfg = 0;
            } else if (port_cnt == 57) {
                board = "Sparx-5-Cu48";
                target = 0x7556;
                type = 1;
            }
        }
        break;
    default:
        break;
    }

    if (strcmp(tag, "board") == 0 && board != NULL) {
        len = snprintf(buf, bufsize, "%s", board);
    } else if (strcmp(tag, "target") == 0 && target) {
        len = snprintf(buf, bufsize, "0x%x", target);
    } else if (strcmp(tag, "type") == 0 && type < 1000) {
        len = snprintf(buf, bufsize, "%u", type);
    } else if (mux_mode != 0xffffffff && strcmp(tag, "mux_mode") == 0) {
        len = snprintf(buf, bufsize, "%u", mux_mode);
    } else if (LOOP_PORT >= 0 && strcmp(tag, "mep_loop_port") == 0) {
        len = snprintf(buf, bufsize, "%u", LOOP_PORT); // The loop port is internal port LOOP_PORT
    } else if (strcmp(tag, "port_cfg") == 0 && port_cfg < 1000) {
        len = snprintf(buf, bufsize, "%u", port_cfg);
    }

    if (len) {
        if (buflen) {
            *buflen = len;
        }
        T_D("handling tag: %s, value: %s", tag, buf);
        return MESA_RC_OK;
    }

    T_D("ignoring tag: %s", tag);
    return MESA_RC_ERROR;
}

static void board_debug(meba_trace_level_t level,
                        const char *location,
                        uint32_t line_no,
                        const char *fmt,
                        ...)
{
    mscc_appl_trace_group_t *group = &trace_groups[TRACE_GROUP_MEBA];
    mesa_trace_level_t      lvl;
    va_list                 ap;

    lvl = (level > MEBA_TRACE_LVL_ERROR ? MESA_TRACE_LEVEL_NONE :
           level > MEBA_TRACE_LVL_INFO ? MESA_TRACE_LEVEL_ERROR :
           level > MEBA_TRACE_LVL_DEBUG ? MESA_TRACE_LEVEL_INFO :
           level > MEBA_TRACE_LVL_NOISE ? MESA_TRACE_LEVEL_DEBUG : MESA_TRACE_LEVEL_NOISE);
    if (group->level >= lvl) {
        va_start(ap, fmt);
        // The MEBA 'location' is the function name, and the file name is unknown
        mscc_appl_trace_vprintf(trace_module.name, group->name, lvl, "meba_xxx.c", line_no, location, fmt, ap);
        va_end(ap);
    }
}

/* MESA callouts */
void mesa_callout_lock(const mesa_api_lock_t *const lock)
{
}

void mesa_callout_unlock(const mesa_api_lock_t *const lock)
{
}

static meba_board_interface_t board_info;

/* ================================================================= *
 *  Option parsing
 * ================================================================= */

static mscc_appl_opt_t *main_opt_list;

void mscc_appl_opt_reg(mscc_appl_opt_t *opt)
{
    mscc_appl_opt_t *cur, *prev = NULL;
    int             cmp;

    for (cur = main_opt_list; cur != NULL; prev = cur, cur = cur->next) {
        cmp = strncmp(cur->option, opt->option, 1);
        if (cmp == 0) {
            fprintf(stderr, "duplicate option: %s\n", cur->option);
            return;
        } else if (cmp > 0) {
            // Found greater option
            break;
        }
    }
    if (prev == NULL) {
        // Insert first
        opt->next = main_opt_list;
        main_opt_list = opt;
    } else {
        // Insert after previous entry
        opt->next = prev->next;
        prev->next = opt;
    }
}

static void main_parse_options(int argc, char **argv)
{
    mscc_appl_opt_t *opt;
    char            buf[256], *p = buf;
    int             option;

    // Build option string
    for (opt = main_opt_list; opt != NULL; opt = opt->next) {
        p += sprintf(p, "%s", opt->option);
    }

    while ((option = getopt(argc, argv, buf)) != -1) {
        // Call registered option function
        for (opt = main_opt_list; opt != NULL; opt = opt->next) {
            if (opt->option[0] == option && opt->func(optarg) != MESA_RC_OK) {
                exit(0);
            }
        }
    }
}

static mesa_rc help_option(char *parm)
{
    mscc_appl_opt_t *opt;
    int             i, len, max_len = 0;

    printf("mesa_demo options:\n\n");
    for (i = 0; i < 2; i++) {
        for (opt = main_opt_list; opt != NULL; opt = opt->next) {
            if (i) {
                printf("-%c %-*s : %s\n", opt->option[0], max_len, opt->parm ? opt->parm : "", opt->descr);
            } else if (opt->parm && (len = strlen(opt->parm)) > max_len) {
                max_len = len;
            }
        }
    }
    return MESA_RC_ERROR;
}

static mscc_appl_opt_t main_opt = {
    "h",
    NULL,
    "Show this help text",
    help_option
};

static mesa_bool_t emulation;

static mesa_rc emul_option(char *parm)
{
    emulation = 1;
    return MESA_RC_OK;
}

static mscc_appl_opt_t main_emul = {
    "e",
    NULL,
    "Run application with emulation" ,
    emul_option
};

static int run_in_foreground = 0;
static mesa_rc option_foreground(char *parm)
{
    run_in_foreground = 1;
    return MESA_RC_OK;
}

static mscc_appl_opt_t main_opt_foreground = {
    "f",
    NULL,
    "Run in foreground",
    option_foreground
};

static mesa_bool_t warm_start_enable;

static mesa_rc warm_option(char *parm)
{
    warm_start_enable = 1;
    return MESA_RC_OK;
}

static mscc_appl_opt_t main_opt_warm = {
    "w",
    NULL,
    "Allow warm start",
    warm_option
};

static mesa_rc loop_port_opt(char *parm)
{
    uint32_t uport;
    char     *end;

    uport = strtoul(parm, &end, 0);
    if (*end != '\0' || uport == 0 || uport > mesa_port_cnt(NULL)) {
        fprintf(stderr, "Illegal loop port\n");
        return MESA_RC_ERROR;
    }
    LOOP_PORT = uport2iport(uport);

    T_D("Using loop-port: port %u (iport %u)", uport, LOOP_PORT);

    return MESA_RC_OK;
}

static mscc_appl_opt_t main_opt_loop_port = {
    "l:",
    "<loop-port>",
    "Configure a loop-port",
    loop_port_opt
};

static void cli_cmd_warm_start(cli_req_t *req)
{
    mesa_inst_create_t create;
    mesa_init_conf_t   conf;
    mesa_port_map_t    *port_map = NULL;
    uint32_t           port_cnt = mesa_port_cnt(NULL);

    cli_printf("Warm starting\n");
    if (mesa_init_conf_get(NULL, &conf) != MESA_RC_OK) {
        T_E("mesa_init_conf_get() failed");
    } else if ((port_map = calloc(port_cnt, sizeof(*port_map))) == NULL) {
        T_E("port map calloc() failed");
    } else if (mesa_port_map_get(NULL, port_cnt, port_map) != MESA_RC_OK) {
        T_E("mesa_port_map_get() failed");
    } else {
        conf.warm_start_enable = 1;
        mesa_inst_get(appl_init.board_inst->props.target, &create);
        if (mesa_inst_destroy(NULL) != MESA_RC_OK) {
            T_E("mesa_inst_destroy() failed");
        } else if (mesa_inst_create(&create, NULL) != MESA_RC_OK) {
            T_E("API Failed to Instantiate");
        } else if (mesa_init_conf_set(NULL, &conf) != MESA_RC_OK) {
            T_E("mesa_init_conf_set() failed");
        } else if (mesa_port_map_set(NULL, port_cnt, port_map) != MESA_RC_OK) {
            T_E("mesa_port_map_get() failed");
        } else {
            appl_init.cmd = MSCC_INIT_CMD_INIT_WARM;
            init_modules(&appl_init);
        }
    }

    if (port_map != NULL) {
        free(port_map);
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Warm Start",
        "Restart system using warm start",
        cli_cmd_warm_start
    },
};

static void main_cli_init(void)
{
    int i;

    /* Register commands */
    for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }
}

static int  SPI_REG_IO = 0;
static char SPI_DEVICE[512];
static int  SPI_PAD = 1;
static int  SPI_FREQ = 5000000;
static mesa_rc spidev_opt(char *parm)
{
    char *s_pad, *s_freq;

    s_pad = strchr(parm, '@');

    if (s_pad) {
        *s_pad = 0;
        s_pad++;
        SPI_PAD = atoi(s_pad);

        s_freq = strchr(s_pad, '@');

        if (s_freq) {
            *s_freq = 0;
            s_freq++;
            SPI_FREQ = atoi(s_freq);
        }
    }

    strncpy(SPI_DEVICE, parm, sizeof(SPI_DEVICE));
    SPI_DEVICE[sizeof(SPI_DEVICE) - 1] = 0;
    SPI_REG_IO = 1;

    printf("Using SPI device: %s with %d padding byte%s at %d Hz\n",
           SPI_DEVICE, SPI_PAD, (SPI_PAD == 1) ? "" : "s", SPI_FREQ);

    return MESA_RC_OK;
}

static mscc_appl_opt_t main_opt_spidev = {
    "s:",
    "<spidev[@pad[@freq]]>",
    "SPI device, padding bytes and frequency to use (instead of UIO which is default)",
    spidev_opt
};


static mesa_bool_t vlan_counters_disable;

static mesa_rc vlan_counters_disable_option(char *parm)
{
    vlan_counters_disable = 1;
    return MESA_RC_OK;
}

static mscc_appl_opt_t main_opt_vlan_counters_disable = {
    "v",
    NULL,
    "Disable VLAN counters",
    vlan_counters_disable_option
};

static void main_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        mscc_appl_opt_reg(&main_opt);
        mscc_appl_opt_reg(&main_emul);
        mscc_appl_opt_reg(&main_opt_foreground);
        mscc_appl_opt_reg(&main_opt_warm);
        mscc_appl_opt_reg(&main_opt_loop_port);
        mscc_appl_opt_reg(&main_opt_spidev);
        mscc_appl_opt_reg(&main_opt_vlan_counters_disable);
        break;

    case MSCC_INIT_CMD_INIT:
        main_cli_init();
        break;

    default:
        break;
    }

}

static void init_modules(mscc_appl_init_t *init)
{
    main_init(init);
    mscc_appl_cli_init(init);
    mscc_appl_port_init(init);
    mscc_appl_mac_init(init);
    mscc_appl_vlan_init(init);
    mscc_appl_ip_init(init);
    mscc_appl_json_rpc_init(init);
    mscc_appl_debug_init(init);
    mscc_appl_symreg_init(init);
    mscc_appl_trace_init(init);
    mscc_appl_test_init(init);
}

typedef struct {
    int                fd;
    fd_read_callback_t cb;
} fd_read_reg_t;

#define FD_REG_MAX 8
fd_read_reg_t fd_reg_table[FD_REG_MAX];

void fd_read_register(int fd, fd_read_callback_t cb)
{
    int           i, free = -1;
    fd_read_reg_t *reg;

    if (fd <= 0) {
        T_E("illegal fd: %d", fd);
    }

    for (i = 0; i < FD_REG_MAX; i++) {
        reg = &fd_reg_table[i];
        if (reg->fd == fd) {
            if (cb == NULL) {
                // Deregistration
                reg->fd = 0;
            } else {
                // Re-registration
                reg->cb = cb;
            }
            return;
        } else if (cb != NULL && reg->fd == 0 && free < 0) {
            // First free entry found
            free = i;
        }
    }
    if (free >= 0) {
        // New registration
        reg = &fd_reg_table[free];
        reg->fd = fd;
        reg->cb = cb;
    }
}

int main(int argc, char **argv)
{
    mesa_rc            rc;
    mesa_inst_create_t create;
    mscc_appl_init_t   *init = &appl_init;
    meba_inst_t        meba_inst;
    mesa_init_conf_t   conf;
    uint32_t           port_cnt = mesa_port_cnt(NULL);
    mesa_port_map_t    *port_map;
    meba_port_entry_t  port_entry;
    mesa_port_no_t     port_no;
    mesa_chip_id_t     chip_id;
    struct timeval     tv;
    int                i, fd, fd_max;
    fd_set             rfds;
    fd_read_reg_t      *reg;
    reg_read_t         reg_read;
    reg_write_t        reg_write;

    // Register trace
    init->cmd = MSCC_INIT_CMD_REG;
    init_modules(init);

    // Parse options
    main_parse_options(argc, argv);

    if (!run_in_foreground) {
        if (daemon(0, 1) < 0) {
            T_E("daemon failed");
            return 1;
        }
    }

    // Initialize IO layer
    if (emulation) {
        rc = MESA_RC_OK;
        reg_read = NULL;
        reg_write = NULL;
    } else if (SPI_REG_IO) {
        rc = spi_reg_io_init(SPI_DEVICE, SPI_FREQ, SPI_PAD);
        reg_read = spi_reg_read;
        reg_write = spi_reg_write;
    } else {
        rc = uio_reg_io_init();
        reg_read = uio_reg_read;
        reg_write = uio_reg_write;
    }

    if (rc != MESA_RC_OK) {
        return 1;
    }

    // Initialize SPI slave before doing anything else in the API
    if (SPI_REG_IO) {
        mesa_spi_slave_init_t s;
        s.reg_write = reg_write;
        s.reg_read = reg_read;
        s.endian = MESA_SPI_ENDIAN_BIG;
        s.bit_order = MESA_SPI_BIT_ORDER_MSB_FIRST;
        s.padding = SPI_PAD;
        if (mesa_spi_slave_init(&s) != MESA_RC_OK) {
            return 1;
        }
    }

    // Initialize MEBA
    memset(&board_info, 0, sizeof(board_info));
    board_info.reg_read = reg_read;
    board_info.reg_write = reg_write;
    board_info.i2c_read = i2c_read;
    board_info.i2c_write = i2c_write;
    board_info.conf_get = board_conf_get;
    board_info.debug = board_debug;
    if ((meba_inst = meba_initialize(sizeof(board_info), &board_info)) == NULL) {
        T_E("MEBA failed to Instantiate");
        return 1;
    }
    init->board_inst = meba_inst;
    T_D("MEBA Instantiated");

    // Create API instance
    mesa_inst_get(meba_inst->props.target, &create);
    if (mesa_inst_create(&create, NULL) != MESA_RC_OK) {
        T_E("API Failed to Instantiate");
        return 1;
    }
    T_D("API Instantiated");

    // Initialize API instance
    if (mesa_init_conf_get(NULL, &conf) != MESA_RC_OK) {
        T_E("mesa_init_conf_get() failed");
        return 1;
    }
    conf.reg_read = board_info.reg_read;
    conf.reg_write = board_info.reg_write;
    conf.mux_mode = meba_inst->props.mux_mode;
    conf.using_ufdma = 1;
    conf.warm_start_enable = warm_start_enable;
    conf.vlan_counters_disable = vlan_counters_disable;
    conf.spi_bus = !!SPI_REG_IO;
    if (mesa_init_conf_set(NULL, &conf) != MESA_RC_OK) {
        T_E("mesa_init_conf_set() failed");
        return 1;
    }
    T_D("API initialized");

    // Do a board init before the port map is established in case of any changes
    MEBA_WRAP(meba_reset, init->board_inst, MEBA_BOARD_INITIALIZE);

    // Setup port mapping
    if ((port_map = calloc(port_cnt, sizeof(*port_map))) == NULL) {
        T_E("port map calloc() failed");
        return 1;
    }
    for (port_no = 0; port_no < port_cnt; port_no++) {
        if (meba_inst->api.meba_port_entry_get(meba_inst, port_no, &port_entry) != MESA_RC_OK) {
            memset(&port_entry, 0, sizeof(port_entry));
            port_entry.map.chip_port = -1; // Unused
        }
        port_map[port_no] = port_entry.map;
    }
    rc = mesa_port_map_set(NULL, port_cnt, port_map);
    free(port_map);
    if (rc != MESA_RC_OK) {
        T_E("mesa_port_map_set() failed");
        return 1;
    }
    T_D("Port map initialized");

    // Read chip id (register access check)
    if (mesa_chip_id_get(NULL, &chip_id) != MESA_RC_OK) {
        T_E("mesa_chip_id_get() failed");
        return 1;
    }
    T_D("Chip ID: 0x%04x, revision: %u", chip_id.part_number, chip_id.revision);

    if (!emulation) {
        /* Load any board specific drivers to the kernel */
        load_board_driver("/lib/modules/board/mscc_board.ko", meba_inst->props.board_type);
    }

    // Initialize modules
    init->cmd = MSCC_INIT_CMD_INIT;
    init_modules(init);

    // Poll modules
    while (1) {
        FD_ZERO(&rfds);
        fd_max = 0;
        for (i = 0; i < FD_REG_MAX; i++) {
            fd = fd_reg_table[i].fd;
            if (fd > 0) {
                FD_SET(fd, &rfds);
                if (fd > fd_max) {
                    fd_max = fd;
                }
            }
        }
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        if (select(fd_max + 1, &rfds, NULL, NULL, &tv) < 0) {
            T_E("select() failed");
        } else {
            for (i = 0; i < FD_REG_MAX; i++) {
                reg = &fd_reg_table[i];
                if (reg->fd > 0 && FD_ISSET(reg->fd, &rfds)) {
                    reg->cb(reg->fd);
                }
            }
        }
        T_N("Call init_modules() and mesa_poll_1sec()");
        init->cmd = MSCC_INIT_CMD_POLL;
        init_modules(init);
        if (MESA_RC_OK != mesa_poll_1sec(NULL)) {  // One sec poll of the MESA API
            T_E("mesa_poll_1sec() failed");
        }
    }

    return 0;
}
