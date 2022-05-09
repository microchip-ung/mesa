// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <ctype.h>
#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"
#include "symreg.h"

extern meba_inst_t meba_global_inst;

static mscc_appl_trace_module_t trace_module = {
    .name = "debug"
};

enum {
    TRACE_GROUP_DEFAULT,
    TRACE_GROUP_CNT
};

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

#define CLI_TGT_MAX  64
#define CLI_ADDR_MAX (1<<8)  /* 8-bit address space */
#define CLI_PHY_MAX 32
#define CLI_PATTERN_MAX 128
#define CLI_VALUES_MAX 10

typedef struct {
    mesa_bool_t tgt_list[CLI_TGT_MAX];
    mesa_bool_t addr_list[CLI_ADDR_MAX];
    mesa_bool_t mmd_list[CLI_ADDR_MAX];
    uint32_t    value_list[CLI_VALUES_MAX];
    uint32_t    value_cnt;
    uint32_t    value;
    uint32_t    page;
    uint16_t    mmd_addr;
    uint32_t    addr;
    uint8_t     miim_addr;
    uint8_t     i2c_addr;
    uint8_t     i2c_reg;
    uint8_t     i2c_value;
    uint8_t     i2c_count;

    mesa_debug_layer_t layer;
    mesa_debug_group_t group;

    mesa_bool_t clear;
    mesa_bool_t full;
    mesa_bool_t has_action;
    mesa_bool_t has_dfe;
    mesa_bool_t has_ctle;
    mesa_bool_t has_txeq;

    char pattern[CLI_PATTERN_MAX + 1];
} debug_cli_req_t;

/* Debug PHY read/write */
static void cli_cmd_debug_phy(cli_req_t *req, mesa_bool_t write)
{
    mesa_port_no_t  port, iport;
    int             i, addr, first = 1;
    uint32_t        reg;
    uint16_t        value;
    debug_cli_req_t *mreq = req->module_req;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        port = iport2uport(iport);
        if (req->port_list[port] == 0)
            continue;

        for (addr = 0; addr < CLI_PHY_MAX; addr++) {
            if (mreq->addr_list[addr] == 0)
                continue;

            reg = ((mreq->page << 5) | addr);
            if (write) {
                /* Write */
                meba_phy_clause22_write(meba_global_inst, iport, reg, mreq->value);
            } else if (meba_phy_clause22_read(meba_global_inst, iport, reg, &value) == MESA_RC_OK) {
                /* Read success */
                if (first) {
                    first = 0;
                    cli_table_header("Port  Addr  15******8*7*******0  Value");
                }

                cli_printf("%-6u0x%02x  ", port, addr);
                for (i = 15; i >= 0; i--)
                    cli_printf("%d%s", value & (1<<i) ? 1 : 0, (i % 4) || i == 0 ? "" : ".");
                cli_printf("  0x%04x\n", value);
            }
        }
    }
}

static void cli_cmd_deb_phy_clause45_rd_wr(cli_req_t *req, mesa_bool_t write)
{
    mesa_port_no_t  port, iport;
    uint32_t        reg;
    uint16_t        value;
    int             i, first = 1;
    debug_cli_req_t *mreq = req->module_req;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        port = iport2uport(iport);
        if (req->port_list[port] == 0)
            continue;

        reg = mreq->page << 16 | mreq->addr;
        if (write) {
            value = (uint16_t)mreq->value;
            meba_phy_clause45_write(meba_global_inst, iport, reg, value);
        } else if (meba_phy_clause45_read(meba_global_inst, iport, reg, &value) == MESA_RC_OK) {
            if (first) {
                first = 0;
                cli_table_header("Port  Page  Address  15******8*7*******0  Value");
            }
            cli_printf("%-6u%-6u0x%04x   ", port, mreq->page, mreq->addr);
            for (i = 15; i >= 0; i--) {
                cli_printf("%d%s", value & (1<<i) ? 1 : 0, (i % 4) || i == 0 ? "" : ".");
            }
            cli_printf("  0x%04x\n", value);
        }
    }
}

static void cli_cmd_debug_phy_read(cli_req_t *req)
{
    cli_cmd_debug_phy(req, 0);
}

static void cli_cmd_debug_phy_write(cli_req_t *req)
{
    cli_cmd_debug_phy(req, 1);
}

static void cli_cmd_debug_phy_clause45_read(cli_req_t *req)
{
    cli_cmd_deb_phy_clause45_rd_wr(req, 0);
}

static void cli_cmd_debug_phy_clause45_write(cli_req_t *req)
{
    cli_cmd_deb_phy_clause45_rd_wr(req, 1);
}

static const char * const cli_api_group_table[MESA_DEBUG_GROUP_COUNT] = {
    [MESA_DEBUG_GROUP_ALL]       = "all",
    [MESA_DEBUG_GROUP_INIT]      = "init",
    [MESA_DEBUG_GROUP_MISC]      = "misc",
    [MESA_DEBUG_GROUP_PORT]      = "port",
    [MESA_DEBUG_GROUP_PORT_CNT]  = "counters",
    [MESA_DEBUG_GROUP_PHY]       = "phy",
    [MESA_DEBUG_GROUP_VLAN]      = "vlan",
    [MESA_DEBUG_GROUP_PVLAN]     = "pvlan",
    [MESA_DEBUG_GROUP_MAC_TABLE] = "mac_table",
    [MESA_DEBUG_GROUP_ACL]       = "acl",
    [MESA_DEBUG_GROUP_QOS]       = "qos",
    [MESA_DEBUG_GROUP_AGGR]      = "aggr",
    [MESA_DEBUG_GROUP_GLAG]      = "glag",
    [MESA_DEBUG_GROUP_STP]       = "stp",
    [MESA_DEBUG_GROUP_MIRROR]    = "mirror",
    [MESA_DEBUG_GROUP_EVC]       = "evc",
    [MESA_DEBUG_GROUP_ERPS]      = "erps",
    [MESA_DEBUG_GROUP_EPS]       = "eps",
    [MESA_DEBUG_GROUP_SR]        = "sr",
    [MESA_DEBUG_GROUP_PACKET]    = "packet",
    [MESA_DEBUG_GROUP_FDMA]      = "fdma",
    [MESA_DEBUG_GROUP_TS]        = "ts",
    [MESA_DEBUG_GROUP_PHY_TS]    = "phy_ts",
    [MESA_DEBUG_GROUP_WM]        = "wm",
    [MESA_DEBUG_GROUP_LRN]       = "lrn",
    [MESA_DEBUG_GROUP_IPMC]      = "ipmc",
    [MESA_DEBUG_GROUP_STACK]     = "stack",
    [MESA_DEBUG_GROUP_CMEF]      = "cmef",
    [MESA_DEBUG_GROUP_HOST]      = "host",
    [MESA_DEBUG_GROUP_MPLS]      = "mpls",
    [MESA_DEBUG_GROUP_HW_PROT]   = "hwprot",
    [MESA_DEBUG_GROUP_HQOS]      = "hqos",
    [MESA_DEBUG_GROUP_VXLAT]     = "vxlat",
    [MESA_DEBUG_GROUP_OAM]       = "oam",
    [MESA_DEBUG_GROUP_MRP]       = "mrp",
    [MESA_DEBUG_GROUP_SER_GPIO]  = "sgpio",
    [MESA_DEBUG_GROUP_L3]        = "l3",
    [MESA_DEBUG_GROUP_AFI]       = "afi",
    [MESA_DEBUG_GROUP_MACSEC]    = "macsec",
    [MESA_DEBUG_GROUP_SERDES]    = "serdes",
    [MESA_DEBUG_GROUP_KR]        = "kr",
    [MESA_DEBUG_GROUP_MUX]       = "mux",
};

static void cli_cmd_debug_api(cli_req_t *req)
{
    mesa_debug_info_t  info;
    mesa_debug_group_t group;
    mesa_port_no_t     iport;
    debug_cli_req_t    *mreq = req->module_req;

    if (mreq->group == MESA_DEBUG_GROUP_COUNT) {
        cli_printf("Legal groups are:\n\n");
        for (group = MESA_DEBUG_GROUP_ALL; group < MESA_DEBUG_GROUP_COUNT; group++) {
            if (cli_api_group_table[group]) {
                cli_printf("%s\n", cli_api_group_table[group]);
            } else {
                cli_printf("%d - unknown\n", group);
            }
        }
    } else if (mesa_debug_info_get(&info) == MESA_RC_OK) {
        info.layer = mreq->layer;
        info.group = mreq->group;
        info.full = mreq->full;
        info.clear = mreq->clear;
        info.has_action = mreq->has_action;
        info.action = mreq->value;
        for (iport = 0; iport < mesa_port_cnt(NULL); iport++)
            mesa_port_list_set(&info.port_list, iport, req->port_list[iport2uport(iport)]);
        mesa_debug_info_print(NULL, cli_printf, &info);
        meba_phy_debug_info_print(req->inst, cli_printf, &info);
    }
}

/* MMD (MDIO Management Devices) read/write */
static void cli_cmd_debug_mmd(cli_req_t *req, mesa_bool_t write)
{
    mesa_port_no_t  iport, port;
    int             i, mmd, first = 1;
    ushort          value;
    debug_cli_req_t *mreq = req->module_req;

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        port = iport2uport(iport);
        if (req->port_list[port] == 0)
            continue;
        for (mmd = 0; mmd < CLI_PHY_MAX; mmd++) {
            if (mreq->mmd_list[mmd] == 0)
                continue;
            if (write) {
                /* Write */
                mesa_port_mmd_write(NULL, iport, mmd, mreq->mmd_addr, mreq->value);
            } else if (mesa_port_mmd_read(NULL, iport, mmd, mreq->mmd_addr, &value) == MESA_RC_OK) {
                /* Read success */
                if (first) {
                    first = 0;
                    cli_printf("Port  MMD   Addr    15******8*7*******0  Value\n");
                }

                cli_printf("%-6u0x%02x  0x%04x  ", port, mmd, mreq->mmd_addr);
                for (i = 15; i >= 0; i--)
                    cli_printf("%d%s",
                           value & (1<<i) ? 1 : 0, (i % 4) || i == 0 ? "" : ".");
                cli_printf("  0x%04x\n", value);
            }
        }
    }
}

static void cli_cmd_debug_mmd_read(cli_req_t *req)
{
    cli_cmd_debug_mmd(req, 0);
}

static void cli_cmd_debug_mmd_write(cli_req_t *req)
{
    cli_cmd_debug_mmd(req, 1);
}

static void cli_cmd_debug_i2c(cli_req_t *req)
{
    mesa_port_no_t  iport, port;
    debug_cli_req_t *mreq = req->module_req;
    uint8_t         i, count, first = 1, buf[256];

    count = mreq->i2c_count;
    if (count == 0) {
        count = 1;
    }
    if (mreq->i2c_reg + count > 255) {
        count = (255 - mreq->i2c_reg);
    }
    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        port = iport2uport(iport);
        if (req->port_list[port] == 0) {
            continue;
        }
        if (req->set) {
            if (req->inst->api.meba_sfp_i2c_xfer(req->inst, iport, 1, mreq->i2c_addr, mreq->i2c_reg, &mreq->i2c_value, 1, 0) != MESA_RC_OK) {
                cli_printf("I2C write failed for port %u\n", port);
            }
        } else if (req->inst->api.meba_sfp_i2c_xfer(req->inst, iport, 0, mreq->i2c_addr, mreq->i2c_reg, buf, count, 0) != MESA_RC_OK) {
            cli_printf("I2C read failed for port %u\n", port);
        } else {
            if (first) {
                first = 0;
                cli_table_header("Port  Addr  Value");
            }
            for (i = 0; i < count; i++) {
                cli_printf("%-6u%-6u0x%02x %c\n", port, mreq->i2c_reg + i, buf[i], isprint(buf[i]) ? buf[i] : '.');
            }
        }
    }
}

static void cli_cmd_debug_serdes(cli_req_t *req)
{
    mesa_port_no_t  iport, port;
    debug_cli_req_t *mreq = req->module_req;
    mesa_port_serdes_debug_t conf = {0};
    char numbuf[100] = {0};

    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        port = iport2uport(iport);
        if (req->port_list[port] == 0)
            continue;

        if (!mreq->has_dfe && !mreq->has_ctle && !mreq->has_txeq) {
            cli_printf("Usage:\n");
            cli_printf("dfe:  For 10G: h1,h2,h3,h4,h5,0. For 25G: h1,h2,h3,h4,h5,dlev\n");
            cli_printf("ctle: For 10G: r,c,vga,0         For 25G: vga_r,vga_c,c,gain\n");
            cli_printf("txeq: tap_dly, tap_adv, amplitude\n");
            cli_printf("Syntax:\n");
            cli_printf("mesa-cmd deb serdes <port> dfe|ctle|txeq <h1,h2,h3,h4,h5,dlev> || <vga_r,vga_c,c,gain> || <tap_dly,tap_adv,amplitude>\n");
            return;
        }

        if (mreq->has_dfe && (mreq->value_cnt != 6)) {
            cli_printf("Error. Expecting 6 values for dfe (<h1,h2,h3,h4,h5,dlev> or <h1,h2,h3,h4,h5,0>\n");
            return;
        } else if (mreq->has_ctle && (mreq->value_cnt != 4)) {
            cli_printf("Error. Expecting 4 values for ctle (<vga_r,vga_c,c,gain> or <r,c,vga,0>)\n");
            return;
        } else if (mreq->has_txeq && (mreq->value_cnt != 3)) {
            cli_printf("Error. Expecting 3 values for txeq (<tap_dly,tap_adv,amplitude>)\n");
            return;
        }

        if (mreq->has_dfe) {
            conf.debug_type = MESA_SERDES_DFE_PRM;
        } else if (mreq->has_ctle) {
            conf.debug_type = MESA_SERDES_CTLE_PRM;
        } else if (mreq->has_txeq) {
            conf.debug_type = MESA_SERDES_TXEQ_PRM;
        }
        for (uint8_t i = 0; i < mreq->value_cnt; i++) {
            conf.serdes_prm[i] = mreq->value_list[i];
            sprintf(numbuf + strlen(numbuf), "%d ",mreq->value_list[i]);
        }
        (void)mesa_port_serdes_debug_set(NULL, iport, &conf);

    }
}

static void cli_cmd_debug_chip_id(cli_req_t *req)
{
    mesa_chip_id_t id;

    if (mesa_chip_id_get(NULL,&id) == MESA_RC_OK) {
        cli_printf("Part Number: 0x%04x\n", id.part_number);
        cli_printf("Revision   : %u\n", id.revision);
    }
}

static void cli_cmd_debug_symreg_read(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;

    symreg_cli_regs_print(READ, mreq->pattern, 0);
}

static void cli_cmd_debug_symreg_write(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;

    symreg_cli_regs_print(WRITE, mreq->pattern, mreq->value);
}

static void cli_cmd_debug_symreg_query(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;

    symreg_cli_regs_print(QUERY, mreq->pattern, 0);
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Debug API [<layer>] [<group>] [<port_list>] [full] [clear] [action] [<act_value>]",
        "Show API debug information",
        cli_cmd_debug_api,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug PHY Read <port_list> <addr_list> [<page>]",
        "Read PHY register",
        cli_cmd_debug_phy_read,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug PHY Write <port_list> <addr_list> <value> [<page>]",
        "Write PHY register",
        cli_cmd_debug_phy_write,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug MMD Read <port_list> <mmd_list> <mmd_addr>",
        "Read MMD register",
        cli_cmd_debug_mmd_read,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug MMD Write <port_list> <mmd_list> <mmd_addr> <value>",
        "Write MMD register",
        cli_cmd_debug_mmd_write,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug I2C Read <port_list> <i2c_addr> <addr> [<count>]",
        "Read I2C register",
        cli_cmd_debug_i2c,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug I2C Write <port_list> <i2c_addr> <addr> <value>",
        "Write I2C register",
        cli_cmd_debug_i2c,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug Chip ID",
        "Read chip ID",
        cli_cmd_debug_chip_id
    },
    {
        "Debug Sym Read <word128>",
        "Read one/many switch register(s)",
        cli_cmd_debug_symreg_read
    },
    {
        "Debug Sym Write <word128> <value32>",
        "Write one/many switch register(s)",
        cli_cmd_debug_symreg_write
    },
    {
        "Debug Sym Query <word128>",
        "Display the matched register(s)",
        cli_cmd_debug_symreg_query
    },
    {
        "Debug serdes <port_list> [dfe] [ctle] [txeq] <value_list>",
        "deb serdes <port> dfe h1,h2,h3,h4,h5,0 (10g) or h1,h2,h3,h4,h5,dlev (25g)\n "
        "deb serdes <port> ctle r,c,vga,0 (10g)  or vga_r,vga_c,c,gain (25g)\n "
        "deb serdes <port> txeq dly,adv,ampl\n ",
        cli_cmd_debug_serdes,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug PHY cls-45 Read <port_list> <page> <addr16>",
        "Read PHY clause-45 register",
        cli_cmd_debug_phy_clause45_read,
        CLI_CMD_FLAG_ALL_PORTS
    },
    {
        "Debug PHY cls-45 Write <port_list> <page> <addr16> <value>",
        "Write PHY clause-45 register",
        cli_cmd_debug_phy_clause45_write,
        CLI_CMD_FLAG_ALL_PORTS
    },

};

static int cli_parm_api_layer(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    const char      *ail_txt = "ail";
    const char      *cil_txt = "cil";

    if (strstr(ail_txt, req->cmd) == ail_txt ||
        strstr(cil_txt, req->cmd) == cil_txt) {
        mreq->layer = (req->cmd[0] == 'a' ? MESA_DEBUG_LAYER_AIL : MESA_DEBUG_LAYER_CIL);
        return 0;
    }
    return 1;
}

static int cli_parm_api_group(cli_req_t *req)
{
    int                error = 1;
    const char         *txt = "show";
    mesa_debug_group_t group;
    debug_cli_req_t    *mreq = req->module_req;

    /* Accept 'show' keyword to display groups */
    if (strstr(txt, req->cmd) == txt) {
        mreq->group = MESA_DEBUG_GROUP_COUNT;
        return 0;
    }

    for (group = MESA_DEBUG_GROUP_ALL; group < MESA_DEBUG_GROUP_COUNT; group++) {
        txt = cli_api_group_table[group];
        if (txt != NULL && strstr(txt, req->cmd) == txt) {
            /* Found matching group */
            error = 0;
            mreq->group = group;
            break;
        }
    }
    return error;
}

static int cli_parm_keyword(cli_req_t *req)
{
    const char      *found;
    debug_cli_req_t *mreq = req->module_req;

    if ((found = cli_parse_find(req->cmd, req->stx)) == NULL)
        return 1;

    if (!strncmp(found, "clear", 5))
        mreq->clear = 1;
    else if (!strncmp(found, "full", 4))
        mreq->full = 1;
    else if (!strncmp(found, "action", 6))
        mreq->has_action = 1;
    else if (!strncmp(found, "dfe", 3))
        mreq->has_dfe = 1;
    else if (!strncmp(found, "ctle", 4))
        mreq->has_ctle = 1;
    else if (!strncmp(found, "txeq", 4))
        mreq->has_txeq = 1;
    else
        cli_printf("no match: %s\n", found);

    return 0;
}

static int cli_parm_addr_list(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parse_list(req->cmd, mreq->addr_list, 0, 31, 0);
}

static int cli_parm_page(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u32(req, &mreq->page, 0, 0xffff);
}

static int cli_parm_phy_value(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u32(req, &mreq->value, 0, 0xffff);
}

static int cli_parm_act_value(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u32(req, &mreq->value, 0, 0xffffffff);
}

static int cli_parm_mmd_list(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parse_list(req->cmd, mreq->mmd_list, 0, 31, 0);
}

static int cli_parm_value_array(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parse_values(req->cmd, mreq->value_list ,&mreq->value_cnt, 0, 0xffffffff, CLI_VALUES_MAX);
}


static int cli_parm_mmd_addr(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u16(req, &mreq->mmd_addr, 0, 0xffff);
}

static int cli_parm_i2c_addr(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u8(req, &mreq->i2c_addr, 0, 0xff);
}

static int cli_parm_i2c_reg(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u8(req, &mreq->i2c_reg, 0, 0xff);
}

static int cli_parm_i2c_value(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u8(req, &mreq->i2c_value, 0, 0xff);
}

static int cli_parm_i2c_count(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u8(req, &mreq->i2c_count, 1, 0xff);
}

static int cli_parm_reg_pattern(cli_req_t *req)
{
    size_t          cnt = 0;
    debug_cli_req_t *mreq = req->module_req;

    cnt = strlen(req->cmd);

    if (cnt + 1 > sizeof(mreq->pattern)) {
        cli_printf("Pattern length must be maximum %d characters!\n", sizeof(mreq->pattern) - 1);
        return 1;
    }

    if (cnt > 0) {
        strncpy(mreq->pattern, req->cmd, CLI_PATTERN_MAX + 1);
        mreq->pattern[cnt] = '\0';
    }

    return 0;
}

static int cli_parm_reg_value(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u32(req, &mreq->value, 0, 0xffffffff);
}

static int cli_parm_addr_16bit(cli_req_t *req)
{
    debug_cli_req_t *mreq = req->module_req;
    return cli_parm_u32(req, &mreq->addr, 0, 0xffff);
}

static cli_parm_t cli_parm_table[] = {
    {
        "<layer>",
        "API Layer, 'ail' or 'cil' (default: All layers)",
        CLI_PARM_FLAG_NONE,
        cli_parm_api_layer
    },
    {
        "<group>",
        "API Function Group or 'show' to list groups (default: All groups)",
        CLI_PARM_FLAG_NONE,
        cli_parm_api_group
    },
    {
        "clear",
        "Clear sticky bits",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "full",
        "Show full information",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "action",
        "Give the action value",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "<value>",
        "Value to be written to register (0-0xffff)",
        CLI_PARM_FLAG_SET,
        cli_parm_phy_value
    },
    {
        "<act_value>",
        "Value of the debug action (0-0xffffffff)",
        CLI_PARM_FLAG_SET,
        cli_parm_act_value
    },
    {
        "<mmd_list>",
        "MMD address list (0-31)",
        CLI_PARM_FLAG_NONE,
        cli_parm_mmd_list,
    },
    {
        "<mmd_addr>",
        "MMD register address (0-0xffff)",
        CLI_PARM_FLAG_NONE,
        cli_parm_mmd_addr
    },
    {
        "<addr_list>",
        "Register address list (0-31)",
        CLI_PARM_FLAG_NONE,
        cli_parm_addr_list
    },
    {
        "<value_list>",
        "u32 list (0-0xffffffff)",
        CLI_PARM_FLAG_NONE,
        cli_parm_value_array,
    },
    {
        "<page>",
        "Register page (0-0xffff), default: page 0",
        CLI_PARM_FLAG_NONE,
        cli_parm_page
    },
    {
        "<i2c_addr>",
        "I2C address (0-255)",
        CLI_PARM_FLAG_NONE,
        cli_parm_i2c_addr
    },
    {
        "<addr>",
        "I2C register (0-255)",
        CLI_PARM_FLAG_NONE,
        cli_parm_i2c_reg
    },
    {
        "<value>",
        "I2C register value (0-255)",
        CLI_PARM_FLAG_SET,
        cli_parm_i2c_value,
        cli_cmd_debug_i2c
    },
    {
        "<count>",
        "Number of I2C registers (1-255)",
        CLI_PARM_FLAG_NONE,
        cli_parm_i2c_count,
    },
    {
        "<word128>",
        "Register pattern on the form 'target[t]:reggrp[g]:reg[r]', where\n\
        'target' is the name of the target (e.g. dev).\n\
        'reggrp' is the name of the register group.\n\
        'reg'    is the name of the register.\n\
        t        is a list of target replications if applicable.\n\
        g        is a list of register group replications if applicable.\n\
        r        is a list of register replications if applicable.\n\
        If a given replication (t, g, r) is omitted, all applicable replications will be accessed.\n\
        Both 'target', 'reggrp' and 'reg' may be omitted, which corresponds to wildcarding that part\n\
        of the name. Matches are exact, but wildcards ('*', '?') are allowed.",
        CLI_PARM_FLAG_NONE,
        cli_parm_reg_pattern
    },
        {
        "<value32>",
        "Value to be written to register (0-0xffffffff)",
        CLI_PARM_FLAG_SET,
        cli_parm_reg_value
    },
    {
        "dfe",
        "Rx equalization: deb serdes <port> dfe h1,h2,h3,h4,h5,0 (10g) or h1,h2,h3,h4,h5,dlev (25g)",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "ctle",
        "Rx equalization: deb serdes <port> ctle r,c,vga,0 (10g) or vga_r,vga_c,c,gain (25g)",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "txeq",
        "Tx equalization: deb serdes <port> txeq dly,adv,ampl",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "<addr16>",
        "16-bit address (0-65535)",
        CLI_PARM_FLAG_NONE,
        cli_parm_addr_16bit
    },

};

static void debug_cli_init(void)
{
    int i;

    /* Register commands */
    for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }

    /* Register parameters */
    for (i = 0; i < sizeof(cli_parm_table)/sizeof(cli_parm_t); i++) {
        mscc_appl_cli_parm_reg(&cli_parm_table[i]);
    }
}

void mscc_appl_debug_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        debug_cli_init();
        break;

    default:
        break;
    }
}
