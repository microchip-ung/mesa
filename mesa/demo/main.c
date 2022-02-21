// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


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

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"
#include "ipc.h"

#define ARRSZ(_x_)  (sizeof(_x_) / sizeof((_x_)[0]))

#define I2C_PORT2DEV(p) (100 + p)

// Local data
static int LOOP_PORT = -1;
static int REF_BOARD_PCB = -1;
static int REF_BOARD_PORT_COUNT = -1;

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

static mesa_bool_t int_from_str(const char *s, int *res)
{
    long int tmp;

    // Get the number only
    while (*s) {
        if(*s >= '0' && *s <= '9') {
            break;
        } else {
            s++;
        }
    }

    if (strlen(s) == 0) {
        return 0;
    }

    tmp = strtol(s, 0, 10);

    if (tmp < 1 || tmp > 9999) {
        return 0;
    }

    *res = tmp;
    return 1;
}

static mesa_bool_t get_uboot_env(const char *env, char *buf, int len)
{
    FILE *fp;
    char cmd[100];

    sprintf(cmd, "/usr/sbin/fw_printenv -n %s 2> /dev/null", env);
    fp = popen(cmd, "r");
    if (fp == NULL) {
        return 0;
    }
    if (fgets(buf, len - 1, fp) == NULL) {
        pclose(fp);
        return 0;
    }
    pclose(fp);
    return 1;
}

void get_mac_addr(uint8_t *mac)
{
    char buf[128];
    uint32_t i, m[6];

    if (get_uboot_env("ethaddr", buf, sizeof(buf)) &&
        sscanf(buf, "%2x:%2x:%2x:%2x:%2x:%2x", &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]) == 6) {
        for (i = 0; i < 6; i++) {
            mac[i] = m[i];
        }
    } else {
        mac[0] = 0x00;
        mac[1] = 0x01;
        mac[2] = 0xc1;
        mac[3] = 0x00;
        mac[4] = 0x00;
        mac[5] = 0x00;
    }
}

// Read the uboot env var and return the results as integer
// FA PCB 134 (12x10G + 8x25G + NPI)
// FA PCB 135 (48x1G + 4x10G + 4x25G + NPI)
// Linux usage e.g.:
// fw_setenv pcb pcb134
// fw_setenv pcb_var 21
static mesa_bool_t get_uboot_env_int(const char *env, int *res)
{
    FILE *fp;
    char cmd[100];
    int ret = 0;
    *res = 0;
    strcpy(cmd, "/usr/sbin/fw_printenv -n ");
    strcat(cmd, env);
    strcat(cmd, " 2> /dev/null");
    fp = popen(cmd, "r");

    if (fp == NULL) {
        pclose(fp);
        return 0;
    }

    if (fgets(cmd, sizeof(cmd) - 1, fp) == NULL) {
        pclose(fp);
        return 0;
    }

    ret = int_from_str(cmd, res);

    pclose(fp);
    return ret;
}

static mesa_bool_t get_env(const char *env, int *res)
{
    const char *e = getenv(env);

    // Try read value from environment first. If success sue the environment.
    // This shall be the first priority as it is ~1000 times faster than the
    // UBoot path.
    if (e && int_from_str(e, res)) {
        return 1;
    }

    // Try UBoot!!!
    return get_uboot_env_int(env, res);
}

// Assign defaults in case if the port count is not given
static uint32_t get_fa_port_cnt_default(uint32_t target, uint32_t pcb)
{
    if (pcb == 125) {
        return 8; // Current support for modular board
    }
    switch (target) {
    case MESA_TARGET_7546TSN:
    case MESA_TARGET_7546:
        return  (pcb == 135) ? 29 : 7;
    case MESA_TARGET_7549TSN:
    case MESA_TARGET_7549:
        return  (pcb == 135) ? 53 : 10;
    case MESA_TARGET_7552TSN:
    case MESA_TARGET_7552:
        return  (pcb == 135) ? 57 : 13;
    case MESA_TARGET_7556TSN:
    case MESA_TARGET_7556:
        if (pcb == 135) {
            T_E("Port config does not exist");
            return 0;
        } else {
            return 17;
        }
        break;
    case MESA_TARGET_7558TSN:
    case MESA_TARGET_7558:
        return  (pcb == 135) ? 57 : 21;
    default:
        T_E("Unknown target '%x'",target);
    }
    return 0;
}

static void get_fa_board_name(uint32_t cnt, mesa_bool_t sparx5i, uint32_t pcb, char *buf)
{
    char str[10];
    if (buf != NULL) {
        strcpy(buf, sparx5i ? "SparX-5i-" : "SparX-5-");
        if (pcb == 125) {
            strcat(buf, "Modular-");
        } else {
            strcat(buf, pcb == 135 ? "CuSFP-" : "SFP-");
        }
        sprintf(str, "%d", cnt);
        strcat(buf, str);
    }
}

static mesa_target_type_t get_fa_target(const mesa_switch_bw_t bw, mesa_bool_t sparxi)
{
    switch (bw) {
    case MESA_SWITCH_BW_64:
        if (sparxi) {
            return MESA_TARGET_7546TSN;
        } else {
            return MESA_TARGET_7546;
        }
        break;
    case MESA_SWITCH_BW_90:
        if (sparxi) {
            return MESA_TARGET_7549TSN;
        } else {
            return MESA_TARGET_7549;
        }
        break;
    case MESA_SWITCH_BW_128:
        if (sparxi) {
            return MESA_TARGET_7552TSN;
        } else {
            return MESA_TARGET_7552;
        }
        break;
    case MESA_SWITCH_BW_160:
        if (sparxi) {
            return MESA_TARGET_7556TSN;
        } else {
            return MESA_TARGET_7556;
        }
        break;
    case MESA_SWITCH_BW_200:
        if (sparxi) {
            return MESA_TARGET_7558TSN;
        } else {
            return MESA_TARGET_7558;
        }
        break;
    default:
        T_E("Illegal Switch BW");
        break;
    }
    return 0;
}

static mesa_rc board_dtree_get(const char *tag, char *buf, size_t bufsize, size_t *buflen)
{
    int    fd;
    char   fname[128];
    size_t n;

    sprintf(fname, "/proc/device-tree/meba/%s", tag);
    if ((fd = open(fname, O_RDONLY)) < 0) {
        T_D("dt tag %s not found", fname);
        return MESA_RC_ERROR;
    }

    if ((n = read(fd, buf, bufsize)) < 0) {
        n = 0;
    }
    buf[n] = 0;
    close(fd);
    if (buflen) {
        *buflen = n;
    }
    T_D("dt tag %s: %s", tag, buf);
    return MESA_RC_OK;
}

#define PCB_TYPE_NONE 10000

static mesa_rc board_conf_get(const char *tag, char *buf, size_t bufsize, size_t *buflen)
{
    uint32_t   port_cnt = mesa_port_cnt(NULL); // Compiled
    const char *board = NULL;
    uint32_t   target = 0;
    uint32_t   type = PCB_TYPE_NONE;
    uint32_t   board_port_cnt = 1000;
    size_t     len = 0;
    uint32_t   mux_mode = 0xffffffff;
    char       name[20];

    // Try device-tree first
    if (board_dtree_get(tag, buf, bufsize, buflen) == MESA_RC_OK) {
        return MESA_RC_OK;
    }

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
        if (REF_BOARD_PCB == -1) {
            if (!get_env("pcb", &REF_BOARD_PCB)) {
                printf("uboot 'pcb' env variable does not exist, use fw_setenv to set (defaulting to pcb111).\n");
                REF_BOARD_PCB = 111;
            }
        }
        if (REF_BOARD_PCB == 111) {
            board = "Jaguar2-cu48";
            target = 0x7449;
            type = 1;
        } else if (REF_BOARD_PCB == 116) {
            board = "Serval2 NID";
            target = 0x7438;
            type = 0;
        } else if (REF_BOARD_PCB == 110) {
            board = "Jaguar2-cu8sfp16";
            target = 0x7468;
            type = 2;
        } else {
            printf("unknown JR2 PCB: %d.\n", REF_BOARD_PCB);
        }
        break;

    case MESA_CHIP_FAMILY_SPARX5:   // SparX-5/SparX-5i Family
        // Read the uboot env variables to find out PCB nr. and port count
        if (REF_BOARD_PCB == -1) {
            if (!get_env("pcb", &REF_BOARD_PCB)) {
                printf("uboot 'pcb' env variable does not exist, use fw_setenv to set (defaulting to pcb125).\n");
                REF_BOARD_PCB = 125;
            }
        }
        if (REF_BOARD_PORT_COUNT == -1) {
            if (!get_env("pcb_var", &REF_BOARD_PORT_COUNT)) {
                T_D("Using default port count\n");
            }
        }
        mesa_bool_t sparxi  = mesa_capability(NULL, MESA_CAP_SYNCE);
        mesa_switch_bw_t bw = mesa_capability(NULL, MESA_CAP_MISC_SWITCH_BW);
        target = get_fa_target(bw, sparxi);
        type = REF_BOARD_PCB;
        if (REF_BOARD_PORT_COUNT <= 0) {
            REF_BOARD_PORT_COUNT = get_fa_port_cnt_default(target, type);
        }
        board_port_cnt = REF_BOARD_PORT_COUNT;
        get_fa_board_name(board_port_cnt, sparxi, type, name);
        board = name;
        break;

    case MESA_CHIP_FAMILY_LAN966X:
        // Device-tree is expected
        break;

    default:
        break;
    }

    if (strcmp(tag, "board") == 0 && board != NULL) {
        len = snprintf(buf, bufsize, "%s", board);
    } else if (strcmp(tag, "target") == 0 && target) {
        len = snprintf(buf, bufsize, "0x%x", target);
    } else if (strcmp(tag, "type") == 0 && type != PCB_TYPE_NONE) {
        len = snprintf(buf, bufsize, "%u", type);
    } else if (mux_mode != 0xffffffff && strcmp(tag, "mux_mode") == 0) {
        len = snprintf(buf, bufsize, "%u", mux_mode);
    } else if (LOOP_PORT >= 0 && strcmp(tag, "mep_loop_port") == 0) {
        len = snprintf(buf, bufsize, "%u", LOOP_PORT); // The loop port is internal port LOOP_PORT
    } else if (strcmp(tag, "pcb") == 0 && type != PCB_TYPE_NONE) {
        len = snprintf(buf, bufsize, "pcb%u", type);
    } else if (strcmp(tag, "pcb_var") == 0 && board_port_cnt < 1000) {
        len = snprintf(buf, bufsize, "%u", board_port_cnt);
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
           level > MEBA_TRACE_LVL_WARNING ? MESA_TRACE_LEVEL_ERROR :
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
    mesa_sgpio_conf_t  sgpio_conf;
    mesa_port_map_t    *port_map = NULL;
    uint32_t           port_cnt = mesa_port_cnt(NULL);

    cli_printf("Warm starting\n");
    if (mesa_init_conf_get(NULL, &conf) != MESA_RC_OK) {
        T_E("mesa_init_conf_get() failed");
    } else if ((port_map = calloc(port_cnt, sizeof(*port_map))) == NULL) {
        T_E("port map calloc() failed");
    } else if (mesa_port_map_get(NULL, port_cnt, port_map) != MESA_RC_OK) {
        T_E("mesa_port_map_get() failed");
    } else if (mesa_sgpio_conf_get(NULL, 0, 0, &sgpio_conf) != MESA_RC_OK) {
        T_E("mesa_sgpio_conf_get() failed");
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
            T_E("mesa_port_map_set() failed");
        } else if (mesa_sgpio_conf_set(NULL, 0, 0, &sgpio_conf) != MESA_RC_OK) {
            T_E("mesa_sgpio_conf_set() failed");
        } else {
            appl_init.cmd = MSCC_INIT_CMD_INIT_WARM;
            init_modules(&appl_init);
        }
    }

    if (port_map != NULL) {
        free(port_map);
    }
}

static void cli_cmd_board_dump(cli_req_t *req)
{
    int16_t  temp_celsius;
    uint16_t meba_cnt = MEBA_WRAP(meba_capability, appl_init.board_inst, MEBA_CAP_BOARD_PORT_COUNT);
    mesa_bool_t cap_sensor = MEBA_WRAP(meba_capability, appl_init.board_inst, MEBA_CAP_TEMP_SENSORS);

    printf("Board name: %s\n",appl_init.board_inst->props.name);
    printf("Ref board PCB: %d\n",appl_init.board_inst->props.board_type);
    printf("API Target: 0x%x\n",appl_init.board_inst->props.target);
    printf("Compiled port count  (mesa): %d\n", mesa_port_cnt(NULL));
    printf("Ref board port count (meba): %d\n", meba_cnt);
    if (cap_sensor && mesa_temp_sensor_get(NULL, &temp_celsius) == MESA_RC_OK) {
        printf("Chip temperature: %d (C)\n",temp_celsius);
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Warm Start",
        "Restart system using warm start",
        cli_cmd_warm_start
    },
    {
        "Debug board dump",
        "Shows boad config",
        cli_cmd_board_dump
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

static int  RESET_FPGA = 0;
static char RESET_DEVICE[512];

static uint32_t assign_core_clock(uint32_t target)
{
    if (target == MESA_TARGET_7552TSN ||
        target == MESA_TARGET_7552) {
        return MESA_CORE_CLOCK_500MHZ; // Typically enough for the target application
    } else if (target == MESA_TARGET_7546TSN) {
        return MESA_CORE_CLOCK_250MHZ; // For testing
    }
    // Defaults to the highest supported frequency
    return MESA_CORE_CLOCK_DEFAULT;
}

static mesa_rc reset_fpga(const char *device)
{
    spi_user_t user = SPI_USER_FPGA;
    uint32_t   val;

    if (spi_io_init(user, RESET_DEVICE, 400000, 1) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }
    if (spi_read(user, 0x200, &val) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }
    printf("FPGA chip ID: 0x%08x\n", val);
    if ((val & 0xffffff00) != 0x01252200 || (val & 0xff) < 2) {
        printf("Invalid FPGA type or revision\n");
        return MESA_RC_ERROR;
    }
    if (spi_write(user, 0x208, 0x2000215) != MESA_RC_OK ||
        spi_write(user, 0x204, 0x0f0) != MESA_RC_OK ||
        spi_write(user, 0x208, 0x2000214) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }
    sleep(1);
    return MESA_RC_OK;
}

static mesa_rc reset_opt(char *parm)
{
    strncpy(RESET_DEVICE, parm, sizeof(RESET_DEVICE));
    RESET_DEVICE[sizeof(RESET_DEVICE) - 1] = 0;
    RESET_FPGA = 1;
    printf("Using SPI device: %s for FPGA reset\n", RESET_DEVICE);
    return MESA_RC_OK;
}

static mscc_appl_opt_t main_opt_reset = {
    "r:",
    "<spidev>",
    "SPI device used for FPGA access",
    reset_opt
};

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
static mesa_bool_t psfp_counters_enable;

static mesa_rc vlan_counters_disable_option(char *parm)
{
    vlan_counters_disable = 1;
    if (parm != NULL && *parm == 'p') {
        psfp_counters_enable = 1;
    }
    return MESA_RC_OK;
}

static mscc_appl_opt_t main_opt_vlan_counters_disable = {
    "v::",
    "[p]",
    "Disable VLAN counters, optionally enable PSFP counters with -vp",
    vlan_counters_disable_option
};

static void main_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        mscc_appl_opt_reg(&main_opt);
        mscc_appl_opt_reg(&main_opt_foreground);
        mscc_appl_opt_reg(&main_opt_warm);
        mscc_appl_opt_reg(&main_opt_loop_port);
        mscc_appl_opt_reg(&main_opt_reset);
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
    mscc_appl_packet_init(init);
    mscc_appl_ip_init(init);
    mscc_appl_json_rpc_init(init);
    mscc_appl_debug_init(init);
    mscc_appl_symreg_init(init);
    mscc_appl_trace_init(init);
    mscc_appl_test_init(init);
    mscc_appl_kr_init(init);
    mscc_appl_example_init(init);
    mscc_appl_uio_init(init);
    mscc_appl_spi_init(init);
    mscc_appl_intr_init(init);
}

typedef struct {
    int                fd;
    fd_read_callback_t cb;
    void               *ref;
} fd_read_reg_t;

#define FD_REG_MAX 32
fd_read_reg_t fd_reg_table[FD_REG_MAX];

int fd_read_register(int fd, fd_read_callback_t cb, void *ref)
{
    int           i, free = -1;
    fd_read_reg_t *reg;

    if (fd <= 0) {
        T_E("illegal fd: %d", fd);
        return -1;
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
                reg->ref = ref;
            }
            return 0;
        } else if (cb != NULL && reg->fd == 0 && free < 0) {
            // First free entry found
            free = i;
        }
    }
    if (free < 0) {
        return -1;
    }
    // New registration
    reg = &fd_reg_table[free];
    reg->fd = fd;
    reg->cb = cb;
    reg->ref = ref;
    return 0;
}

static mesa_rc gpio_func_info_get(const mesa_inst_t inst, mesa_gpio_func_t gpio_func,  mesa_gpio_func_info_t *info)
{
    if (appl_init.board_inst->api.meba_gpio_func_info_get != NULL) {
        return appl_init.board_inst->api.meba_gpio_func_info_get(appl_init.board_inst, gpio_func, info);
    } else {
        return MESA_RC_ERROR;
    }
}

static mesa_rc serdes_tap_get(const mesa_inst_t inst, mesa_port_no_t port_no,
                              mesa_port_speed_t speed, mesa_port_serdes_tap_enum_t tap, uint32_t *const value)
{
    if (appl_init.board_inst->api.meba_serdes_tap_get != NULL) {
        return appl_init.board_inst->api.meba_serdes_tap_get(appl_init.board_inst, port_no, speed, tap, value);
    } else {
        return MESA_RC_NOT_IMPLEMENTED;
    }
}

mesa_bool_t poll_cnt_us(uint32_t sleep_us, uint32_t *poll_cnt, uint32_t wait_usec)
{
    if ((sleep_us * *poll_cnt) % wait_usec == 0) {
        return 1;
    }
    if (*poll_cnt > 10000) {
        *poll_cnt = 0;
    }
    return 0;
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
    uint32_t           sleep_us = 10000, poll_cnt = 0;

    if (mesa_capability(NULL, MESA_CAP_PORT_KR_IRQ)) {
        sleep_us = 200;
    }

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

    if (RESET_FPGA && reset_fpga(RESET_DEVICE) != MESA_RC_OK) {
        return 1;
    }

    // Initialize IO layer
    if (SPI_REG_IO) {
        rc = spi_io_init(SPI_USER_REG, SPI_DEVICE, SPI_FREQ, SPI_PAD);
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
    board_info.trace = mscc_mepa_trace_printf;
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
    conf.psfp_counters_enable = psfp_counters_enable;
    conf.spi_bus = !!SPI_REG_IO;
    conf.gpio_func_info_get = gpio_func_info_get;
    conf.serdes_tap_get = serdes_tap_get;
    if (mesa_capability(NULL, MESA_CAP_INIT_CORE_CLOCK)) {
        conf.core_clock.freq = assign_core_clock(meba_inst->props.target);
    }
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

    // Initialize modules
    init->cmd = MSCC_INIT_CMD_INIT;
    init_modules(init);

    // Initialize fan and chip/board temperature sensors
    if  (MEBA_WRAP(meba_capability, appl_init.board_inst, MEBA_CAP_TEMP_SENSORS)) {
        MEBA_WRAP(meba_reset, init->board_inst, MEBA_SENSOR_INITIALIZE);
    }
    if  (MEBA_WRAP(meba_capability, appl_init.board_inst, MEBA_CAP_FAN_SUPPORT)) {
        MEBA_WRAP(meba_reset, init->board_inst, MEBA_FAN_INITIALIZE);
    }
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
        tv.tv_sec = 0;
        tv.tv_usec = sleep_us; // was 10000
        if (select(fd_max + 1, &rfds, NULL, NULL, &tv) < 0) {
            T_E("select() failed");
        } else {
            for (i = 0; i < FD_REG_MAX; i++) {
                reg = &fd_reg_table[i];
                if (reg->fd > 0 && FD_ISSET(reg->fd, &rfds)) {
                    reg->cb(reg->fd, reg->ref);
                }
            }
        }
        init->cmd = MSCC_INIT_CMD_POLL_FASTEST;
        init_modules(init);
        poll_cnt++;
        if (poll_cnt_us(sleep_us, &poll_cnt, 1000000)) { // 1 sec poll
            T_N("Call init_modules() and mesa_poll_1sec()");
            init->cmd = MSCC_INIT_CMD_POLL;
            init_modules(init);
            if (MESA_RC_OK != mesa_poll_1sec(NULL)) {  // One sec poll
                T_E("mesa_poll_1sec() failed");
            }
        }

        if (poll_cnt_us(sleep_us, &poll_cnt, 10000)) { // 10 ms poll
            T_N("MSCC_INIT_CMD_POLL_FAST");
            init->cmd = MSCC_INIT_CMD_POLL_FAST;
            init_modules(init);
        }
    }

    return 0;
}
