// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"

static mscc_appl_trace_module_t trace_module = {
    .name = "intr"
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

extern meba_inst_t meba_global_inst;

// From UIO module
extern int uio_fd;
extern char uio_path[];

// Read/write file pointers for 'irqctl' file
static FILE *irq_rd, *irq_wr;

// Mapping from name to IRQ
typedef struct {
    const char *name;
    mesa_irq_t irq;
    uint32_t   cnt;
} irq_map_t;

static irq_map_t irq_map[] = {
    { "ptp_rdy", MESA_IRQ_PTP_RDY },
    { "ptp_sync", MESA_IRQ_PTP_SYNC },
    { "ext_src0", MESA_IRQ_EXT0 },
    { "ext_src1", MESA_IRQ_EXT1 },
    { "oam_vop", MESA_IRQ_OAM },
    { "sgpio", MESA_IRQ_SGPIO },
    { "sgpio0", MESA_IRQ_SGPIO },
    { "sgpio2", MESA_IRQ_SGPIO2 },
    { "dpll", MESA_IRQ_DPLL },
    { "gpio", MESA_IRQ_GPIO },
    { "dev_all", MESA_IRQ_DEV_ALL },
    { "cu_phy0", MESA_IRQ_CU_PHY_0 },
    { "cu_phy1", MESA_IRQ_CU_PHY_1 },
    { "pushbutton", MESA_IRQ_PUSH_BUTTON },
    { "sd10g_kr0", MESA_IRQ_KR_SD10G_0 },
    { "sd10g_kr1", MESA_IRQ_KR_SD10G_1  },
    { "sd10g_kr2", MESA_IRQ_KR_SD10G_2 },
    { "sd10g_kr3", MESA_IRQ_KR_SD10G_3 },
    { "sd10g_kr4", MESA_IRQ_KR_SD10G_4 },
    { "sd10g_kr5", MESA_IRQ_KR_SD10G_5 },
    { "sd10g_kr6", MESA_IRQ_KR_SD10G_6 },
    { "sd10g_kr7", MESA_IRQ_KR_SD10G_7 },
    { "sd10g_kr8", MESA_IRQ_KR_SD10G_8 },
    { "sd10g_kr9", MESA_IRQ_KR_SD10G_9 },
    { "sd10g_kr10", MESA_IRQ_KR_SD10G_10 },
    { "sd10g_kr11", MESA_IRQ_KR_SD10G_11 },
    { "sd10g_kr12", MESA_IRQ_KR_SD10G_12 },
    { "sd10g_kr13", MESA_IRQ_KR_SD10G_13 },
    { "sd10g_kr14", MESA_IRQ_KR_SD10G_14 },
    { "sd10g_kr15", MESA_IRQ_KR_SD10G_15 },
    { "sd10g_kr16", MESA_IRQ_KR_SD10G_16 },
    { "sd10g_kr17", MESA_IRQ_KR_SD10G_17 },
    { "sd10g_kr18", MESA_IRQ_KR_SD10G_18 },
    { "sd10g_kr19", MESA_IRQ_KR_SD10G_19 },

    { "unknown", MESA_IRQ_MAX },
};

// Event counter per port and one extra for exceeding index
#define INTR_EV_IDX_MAX (MESA_PORT_LIST_ARRAY_SIZE * 8 + 1)

typedef struct {
    const char *name;
    uint32_t cnt[INTR_EV_IDX_MAX];
} intr_ev_info_t;

static intr_ev_info_t intr_ev_table[MEBA_EVENT_LAST + 1] = {
    [MEBA_EVENT_LOS] = { "los" },
    [MEBA_EVENT_FLNK] = { "flnk" },
    [MEBA_EVENT_AMS] = { "ams" },
    [MEBA_EVENT_VOE] = { "voe" },
    [MEBA_EVENT_SYNC] = { "sync" },
    [MEBA_EVENT_EXT_SYNC] = { "ext_sync" },
    [MEBA_EVENT_EXT_1_SYNC] = { "ext_1_sync" },
    [MEBA_EVENT_CLK_ADJ] = { "clk_adj" },
    [MEBA_EVENT_CLK_TSTAMP] = { "clk_ts" },
    [MEBA_EVENT_PTP_PIN_0] = { "ptp_pin_0" },
    [MEBA_EVENT_PTP_PIN_1] = { "ptp_pin_1" },
    [MEBA_EVENT_PTP_PIN_2] = { "ptp_pin_2" },
    [MEBA_EVENT_PTP_PIN_3] = { "ptp_pin_3" },
    [MEBA_EVENT_INGR_ENGINE_ERR] = { "igr_engine_err" },
    [MEBA_EVENT_INGR_RW_PREAM_ERR] = { "igr_rw_pream_err" },
    [MEBA_EVENT_INGR_RW_FCS_ERR] = { "igr_rw_fcs_err" },
    [MEBA_EVENT_EGR_ENGINE_ERR] = { "egr_engine_err" },
    [MEBA_EVENT_EGR_RW_FCS_ERR] = { "egr_rw_fcs_err" },
    [MEBA_EVENT_EGR_TIMESTAMP_CAPTURED] = { "egr_ts_captured" },
    [MEBA_EVENT_EGR_FIFO_OVERFLOW] = { "egr_fifo_overflow" },
    [MEBA_EVENT_PUSH_BUTTON] = { "push_button" },
    [MEBA_EVENT_MOD_DET] = { "mod_det" },
    [MEBA_EVENT_KR] = { "kr" },
    [MEBA_EVENT_LAST] = { "unknown" },
};

mesa_rc intr_ev_get(const char *name, uint32_t idx, uint32_t *cnt)
{
    intr_ev_info_t *ev;
    int            i;
    uint32_t       port_cnt = mesa_port_cnt(NULL);

    for (i = 0; i <= MEBA_EVENT_LAST; i++) {
        ev = &intr_ev_table[i];
        if (idx <= port_cnt && strcmp(name, ev->name) == 0) {
            *cnt = ev->cnt[idx];
            return MESA_RC_OK;
        }
    }
    return MESA_RC_ERROR;
}

static void intr_event_enable(meba_event_t ev)
{
    (void)MEBA_WRAP(meba_event_enable, meba_global_inst, ev, 1);
}

static void intr_event(meba_event_t ev, uint32_t idx)
{
    intr_ev_info_t *info;
    uint32_t       port_cnt = mesa_port_cnt(NULL);

    if (ev < MEBA_EVENT_LAST) {
        intr_event_enable(ev);
    } else {
        // Unknown event
        ev = MEBA_EVENT_LAST;
    }
    info = &intr_ev_table[ev];
    T_I("event: %u (%s), idx: %u", ev, info->name, idx);
    if (idx > port_cnt) {
        // Exceeded index
        idx = port_cnt;
    }
    info->cnt[idx]++;
}

static void intr_enable(void)
{
    int enable = 1;

    if (write(uio_fd, &enable, sizeof(enable)) != sizeof(enable)) {
        T_E("write uio_fd failed");
    }
}

static void intr_callback(int fd, void *ref)
{
    int  seq_no, enable, irq_id, i;
    char line[128], irq_name[32];
    irq_map_t *map;

    T_D("callback, fd: %d", fd);
    if (read(fd, &seq_no, sizeof(seq_no)) != sizeof(seq_no)) {
        T_E("read error");
        return;
    }
    T_D("seq_no: %u", seq_no);

    // Enable IRQ file
    intr_enable();

    rewind(irq_rd);
    rewind(irq_wr);
    while (fgets(line, sizeof(line), irq_rd)) {
        if (sscanf(line, "%d|%31s", &irq_id, irq_name) != 2) {
            continue;
        }
        line[strlen(line) - 1] = 0;
        T_D("line: %s", line);
        enable = 0;
        for (i = 0; ; i++) {
            map = &irq_map[i];
            if (map->irq == MESA_IRQ_MAX) {
                T_I("unknown: %s", line);
                map->cnt++;
                break;
            }
            if (strcmp(map->name, irq_name)) {
                continue;
            }
            T_I("map: %s", map->name);
            map->cnt++;
            if (MEBA_WRAP(meba_irq_handler, meba_global_inst, map->irq, intr_event) == MESA_RC_OK) {
                enable = 1;
            }
            break;
        }
        fprintf(irq_wr, "%d\n", enable ? irq_id : -irq_id);
    }
}

static void intr_init(void)
{
    uint32_t        cap = mesa_capability(NULL, MESA_CAP_MISC_CPU_TYPE);
    mesa_irq_t      irq;
    mesa_irq_conf_t conf;
    meba_event_t    ev;

    // For now, no support for external CPU
    if (cap == MESA_CPU_TYPE_EXTERNAL) {
        return;
    }

    if (uio_fd < 1) {
        T_I("invalid uio_fd");
        return;
    }

    // Open 'irqctl' file for read/write
    T_I("uio_fd: %d, uio_path: %s", uio_fd, uio_path);
    if ((irq_rd = fopen(uio_path, "r")) == NULL) {
        T_I("open %s for read failed", uio_path);
        return;
    }
    if ((irq_wr = fopen(uio_path, "w")) == NULL) {
        T_I("open %s for write failed", uio_path);
        fclose(irq_rd);
        return;
    }
    setlinebuf(irq_wr);

    // Register for activity on UIO file descriptor
    fd_read_register(uio_fd, intr_callback, NULL);

    (void)MEBA_WRAP(meba_reset, meba_global_inst, MEBA_INTERRUPT_INITIALIZE);

    // Configure IRQ if requested by MEBA
    conf.external = (cap == MESA_CPU_TYPE_EXTERNAL ? 1 : 0);
    conf.destination = 0;
    for (irq = (mesa_irq_t)0; irq < MESA_IRQ_MAX; irq++) {
        if (MEBA_WRAP(meba_irq_requested, meba_global_inst, irq) == MESA_RC_OK) {
            (void)mesa_irq_conf_set(NULL, irq, &conf);
        }
    }

    // Enable IRQ file
    intr_enable();

    // Enable MEBA events
    for (ev = MEBA_EVENT_FIRST; ev < MEBA_EVENT_LAST; ev++) {
        intr_event_enable(ev);
    }
}

/* - CLI ----------------------------------------------------------- */

typedef struct {
    mesa_bool_t all;
    mesa_bool_t clear;
} intr_cli_req_t;

static void cli_cmd_intr(cli_req_t *req)
{
    irq_map_t      *map;
    intr_ev_info_t *ev;
    int            i, j, header = 1;
    uint32_t       port_cnt = mesa_port_cnt(NULL);
    intr_cli_req_t *mreq = req->module_req;
    char           buf[32];

    if (!mreq->clear) {
        cli_printf("UIO file: %d\n", uio_fd);
        cli_printf("UIO path: %s %s\n", uio_path, irq_rd ? "" : "(not open)");
    }

    for (i = 0; ; i++) {
        map = &irq_map[i];
        if (mreq->clear) {
            map->cnt = 0;
        } else if (map->cnt || mreq->all) {
            if (header) {
                header = 0;
                cli_printf("\n");
                cli_table_header("IRQ         Count");
            }
            cli_printf("%-12s%u\n", map->name, map->cnt);
        }
        if (map->irq == MESA_IRQ_MAX) {
            break;
        }
    }

    for (i = 0, header = 1; i <= MEBA_EVENT_LAST; i++) {
        ev = &intr_ev_table[i];
        for (j = 0; j <= port_cnt; j++) {
            if (mreq->clear) {
                ev->cnt[j] = 0;
            } else if (ev->cnt[j] || mreq->all) {
                if (header) {
                    header = 0;
                    cli_printf("\n");
                    cli_table_header("Event                   Count");
                }
                sprintf(buf, "%s[%u%s]", ev->name, j, j < port_cnt ? "" : "+");
                cli_printf("%-24s%u\n", buf, ev->cnt[j]);
            }
        }
    }
}

static int cli_parm_keyword(cli_req_t *req)
{
    const char     *found;
    intr_cli_req_t *mreq = req->module_req;

    if ((found = cli_parse_find(req->cmd, req->stx)) == NULL)
        return 1;

    if (!strncmp(found, "all", 3))
        mreq->all = 1;
    else if (!strncmp(found, "clear", 5))
        mreq->clear = 1;
    else
        cli_printf("no match: %s\n", found);

    return 0;
}

static cli_parm_t cli_parm_table[] = {
    {
        "all|clear",
        "all     : Show all counters\n"
        "clear   : Clear counters\n"
        "(default: Show non-zero counters)",
        CLI_PARM_FLAG_NO_TXT,
        cli_parm_keyword
    },
};

static cli_cmd_t cli_cmd_table[] = {
    {
        "Intr [all|clear]",
        "Show or clear interrupt/event counters",
        cli_cmd_intr,
    },
};

static void intr_cli_init(void)
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

/* - Initialization ------------------------------------------------ */

void mscc_appl_intr_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        intr_init();
        intr_cli_init();
        break;

    default:
        break;
    }
}
