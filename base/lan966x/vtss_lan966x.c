// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

/* ================================================================= *
 *  Register access
 * ================================================================= */
void vtss_lan966x_reg_error(const char *file, int line) {
#if VTSS_OPT_TRACE
    vtss_callout_trace_printf(VTSS_TRACE_LAYER, VTSS_TRACE_GROUP_DEFAULT,
                              VTSS_TRACE_LEVEL_ERROR, file, line, file,
                              "Index exceed replication!");
#endif
}

/* Read target register using current CPU interface */
static inline vtss_rc lan966x_rd_direct(vtss_state_t *vtss_state, u32 reg, u32 *value)
{
    return vtss_state->init_conf.reg_read(0, reg, value);
}

/* Write target register using current CPU interface */
static inline vtss_rc lan966x_wr_direct(vtss_state_t *vtss_state, u32 reg, u32 value)
{
    return vtss_state->init_conf.reg_write(0, reg, value);
}

vtss_rc (*vtss_lan966x_wr)(vtss_state_t *vtss_state, u32 addr, u32 value) = lan966x_wr_direct;
vtss_rc (*vtss_lan966x_rd)(vtss_state_t *vtss_state, u32 addr, u32 *value) = lan966x_rd_direct;

/* Read-modify-write target register using current CPU interface */
vtss_rc vtss_lan966x_wrm(vtss_state_t *vtss_state, u32 reg, u32 value, u32 mask)
{
    vtss_rc rc;
    u32     val;

    if ((rc = vtss_lan966x_rd(vtss_state, reg, &val)) == VTSS_RC_OK) {
        val = ((val & ~mask) | (value & mask));
        rc = vtss_lan966x_wr(vtss_state, reg, val);
    }
    return rc;
}

/* ================================================================= *
 *  Utility functions
 * ================================================================= */
u32 vtss_lan966x_clk_period_ps(vtss_state_t *vtss_state)
{
#if defined(VTSS_ARCH_LAN966X_FPGA)
    return 15125;
#else
    return 6038; // 165.625 MHz
#endif
}

u32 vtss_lan966x_port_mask(vtss_state_t *vtss_state, const BOOL member[])
{
    vtss_port_no_t port_no;
    u32            port, mask = 0;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (member[port_no]) {
            port = VTSS_CHIP_PORT(port_no);
            mask |= VTSS_BIT(port);
        }
    }
    return mask;
}

vtss_rc vtss_lan966x_counter_update(vtss_state_t *vtss_state,
                                    u32 *addr, vtss_chip_counter_t *counter, BOOL clear)
{
    u32 value;

    REG_RD(SYS_CNT(*addr), &value);
    *addr = (*addr + 1); /* Next counter address */
    vtss_cmn_counter_32_update(value, counter, clear);
    return VTSS_RC_OK;
}

#if VTSS_OPT_DEBUG_PRINT

/* ================================================================= *
 *  Debug print utility functions
 * ================================================================= */

void vtss_lan966x_debug_print_port_header(vtss_state_t *vtss_state,
                                          const vtss_debug_printf_t pr, const char *txt)
{
    vtss_debug_print_port_header(vtss_state, pr, txt, VTSS_CHIP_PORTS + 1, 1);
}

void vtss_lan966x_debug_print_mask(const vtss_debug_printf_t pr, u32 mask)
{
    u32 port;

    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        pr("%s%s", port == 0 || (port & 7) ? "" : ".", ((1<<port) & mask) ? "1" : "0");
    }
    pr("  0x%08x\n", mask);
}

void vtss_lan966x_debug_reg_header(const vtss_debug_printf_t pr, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%-32s  ", name);
    vtss_debug_print_reg_header(pr, buf);
}

void vtss_lan966x_debug_reg(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr, u32 addr, const char *name)
{
    u32 value;
    char buf[200];

    if (vtss_lan966x_rd(vtss_state, addr, &value) == VTSS_RC_OK) {
        VTSS_SPRINTF(buf, "%-32s  ", name);
        vtss_debug_print_reg(pr, buf, value);
    }
}

void vtss_lan966x_debug_reg_inst(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%s_%u", name, i);
    vtss_lan966x_debug_reg(vtss_state, pr, addr, buf);
}

void vtss_lan966x_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                            vtss_chip_counter_t *c1, vtss_chip_counter_t *c2)
{
    char buf[80];

    if (col1 != NULL) {
        VTSS_SPRINTF(buf, "rx_%s:", col1);
        pr("%-28s%10" PRIu64 "   ", buf, c1->prev);
    } else {
        pr("%-41s", "");
    }
    if (col2 != NULL) {
        VTSS_SPRINTF(buf, "tx_%s:", VTSS_STRLEN(col2) ? col2 : col1);
        pr("%-28s%10" PRIu64, buf, c2 ? c2->prev : (u64) 0);
    }
    pr("\n");
}

/* ================================================================= *
 *  Debug print
 * ================================================================= */
static vtss_rc lan966x_debug_info_print(vtss_state_t *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_lan966x_misc_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_lan966x_port_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_lan966x_l2_debug_print(vtss_state, pr, info));
#if defined(VTSS_FEATURE_VCAP)
    VTSS_RC(vtss_lan966x_vcap_debug_print(vtss_state, pr, info));
#endif
#if defined(VTSS_FEATURE_QOS)
    VTSS_RC(vtss_lan966x_qos_debug_print(vtss_state, pr, info));
#endif
#if defined(VTSS_FEATURE_PACKET)
    VTSS_RC(vtss_lan966x_packet_debug_print(vtss_state, pr, info));
#endif
#if defined(VTSS_AFI_V2)
    VTSS_RC(vtss_lan966x_afi_debug_print(vtss_state, pr, info));
#endif
#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_lan966x_ts_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_TIMESTAMP */
#if defined(VTSS_FEATURE_VOP)
    VTSS_RC(vtss_lan966x_oam_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_VOP */
#if defined(VTSS_FEATURE_MRP)
    VTSS_RC(vtss_lan966x_mrp_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_MRP */
    return VTSS_RC_OK;
}
#endif // VTSS_OPT_DEBUG_PRINT

vtss_rc vtss_lan966x_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    VTSS_RC(vtss_lan966x_port_init(vtss_state, cmd));
    VTSS_RC(vtss_lan966x_misc_init(vtss_state, cmd));
#if defined(VTSS_FEATURE_PACKET)
    VTSS_RC(vtss_lan966x_packet_init(vtss_state, cmd));
#endif
#if defined(VTSS_AFI_V2)
    VTSS_RC(vtss_lan966x_afi_init(vtss_state, cmd));
#endif
    VTSS_RC(vtss_lan966x_l2_init(vtss_state, cmd));
#if defined(VTSS_FEATURE_VCAP)
    VTSS_RC(vtss_lan966x_vcap_init(vtss_state, cmd));
#endif
#if defined(VTSS_FEATURE_QOS)
    VTSS_RC(vtss_lan966x_qos_init(vtss_state, cmd));
#endif
#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_lan966x_ts_init(vtss_state, cmd));
#endif

#if defined(VTSS_FEATURE_VOP)
    VTSS_RC(vtss_lan966x_oam_init(vtss_state, cmd));
#endif
#if defined(VTSS_FEATURE_MRP)
    VTSS_RC(vtss_lan966x_mrp_init(vtss_state, cmd));
#endif

    return VTSS_RC_OK;
}

static vtss_rc lan966x_port_map_set(vtss_state_t *vtss_state)
{
    return vtss_lan966x_init_groups(vtss_state, VTSS_INIT_CMD_PORT_MAP);
}

static vtss_rc lan966x_restart_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mux_mode_set(vtss_state_t *vtss_state)
{
#if !defined(VTSS_OPT_FPGA)
    switch (vtss_state->init_conf.mux_mode) {
    case VTSS_PORT_MUX_MODE_0:
        // 2xQSGMII
        REG_WR(HSIO_HW_CFG, HSIO_HW_CFG_QSGMII_ENA(3));
        break;
    case VTSS_PORT_MUX_MODE_1:
        // 2xCu + 2x2,5G + 1xQSGMII
        REG_WR(HSIO_HW_CFG,
               HSIO_HW_CFG_SD6G_0_CFG(1) |
               HSIO_HW_CFG_SD6G_1_CFG(1) |
               HSIO_HW_CFG_GMII_ENA(3) |
               HSIO_HW_CFG_QSGMII_ENA(2));
        REG_WR(CHIP_TOP_CUPHY_COMMON_CFG,
               CHIP_TOP_CUPHY_COMMON_CFG_XPHYAD0(1) |
               CHIP_TOP_CUPHY_COMMON_CFG_MDC_SEL(1) |
               CHIP_TOP_CUPHY_COMMON_CFG_RESET_N(1));
        break;
    case VTSS_PORT_MUX_MODE_2:
        // 2xCu + 1x2,5G + 2xRGMII(dev2,dev3)
        REG_WR(HSIO_HW_CFG,
               HSIO_HW_CFG_RGMII_ENA(3) |
               HSIO_HW_CFG_GMII_ENA(0xf));

        REG_WR(CHIP_TOP_CUPHY_COMMON_CFG,
               CHIP_TOP_CUPHY_COMMON_CFG_XPHYAD0(1) |
               CHIP_TOP_CUPHY_COMMON_CFG_MDC_SEL(1) |
               CHIP_TOP_CUPHY_COMMON_CFG_RESET_N(1));
        break;
    case VTSS_PORT_MUX_MODE_5:
        // 2xCu + 3x1G
        REG_WR(HSIO_HW_CFG,
               HSIO_HW_CFG_SD6G_0_CFG(1) |
               HSIO_HW_CFG_SD6G_1_CFG(1) |
               HSIO_HW_CFG_GMII_ENA(3) |
               HSIO_HW_CFG_QSGMII_ENA(0));
        REG_WR(CHIP_TOP_CUPHY_COMMON_CFG,
               CHIP_TOP_CUPHY_COMMON_CFG_XPHYAD0(1) |
               CHIP_TOP_CUPHY_COMMON_CFG_MDC_SEL(1) |
               CHIP_TOP_CUPHY_COMMON_CFG_RESET_N(1));
        break;
    default:
        VTSS_E("unknown mux mode");
        return VTSS_RC_ERROR;
    }
#endif
    return VTSS_RC_OK;
}

static vtss_rc lan966x_init_conf_set(vtss_state_t *vtss_state)
{
    u32 val;
#if defined(VTSS_OPT_FPGA)
    u32 diff, err;

    REG_RD(GCB_BUILDID, &val);
    if (val > LAN966X_BUILD_ID) {
        diff = (val - LAN966X_BUILD_ID);
    } else {
        diff = (LAN966X_BUILD_ID - val);
    }
#if (VTSS_OPT_FPGA == 1)
    // Sunrise
    err = (diff > 1000);
#else
    // Adaro
    vtss_state->sys_config.using_pcie = 1; // Indicate external CPU
    err = (diff != 0);
#endif
    if (err) {
        VTSS_E("Unexpected build id. Got: 0x%08x, Expected 0x%08x, diff: %u", val, LAN966X_BUILD_ID, diff);
        return VTSS_RC_ERROR;
    }
#else
    // Reset switch core if using SPI from external CPU
    if (vtss_state->init_conf.spi_bus) {
        REG_WR(GCB_SOFT_RST, GCB_SOFT_RST_SOFT_SWC_RST(1));
        VTSS_MSLEEP(100);
    }
#endif

    VTSS_RC(lan966x_mux_mode_set(vtss_state));

    VTSS_FUNC_RC(misc.chip_id_get, &vtss_state->misc.chip_id);

    /* Initialize RAM */
    REG_WRM(SYS_RESET_CFG, SYS_RESET_CFG_CORE_ENA(0), SYS_RESET_CFG_CORE_ENA_M);
    REG_WRM(SYS_RAM_INIT, SYS_RAM_INIT_RAM_INIT(1) | SYS_RAM_INIT_RAM_CFG_HOOK(0),
            SYS_RAM_INIT_RAM_INIT_M | SYS_RAM_INIT_RAM_CFG_HOOK_M);
    do {
        REG_RD(SYS_RAM_INIT, &val);
    } while (SYS_RAM_INIT_RAM_INIT_X(val) != 0);

    /* Enable switch core */
    REG_WRM(SYS_RESET_CFG, SYS_RESET_CFG_CORE_ENA(1), SYS_RESET_CFG_CORE_ENA_M);

    return vtss_lan966x_init_groups(vtss_state, VTSS_INIT_CMD_INIT);
}

static vtss_rc lan966x_register_access_mode_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_inst_create(vtss_state_t *vtss_state)
{
    /* Initialization */
    vtss_state->cil.init_conf_set = lan966x_init_conf_set;
    vtss_state->cil.register_access_mode_set = lan966x_register_access_mode_set;
    vtss_state->cil.restart_conf_set = lan966x_restart_conf_set;
#if VTSS_OPT_DEBUG_PRINT
    vtss_state->cil.debug_info_print = lan966x_debug_info_print;
#endif
    vtss_state->port.map_set = lan966x_port_map_set;

    /* Create function groups */
    return vtss_lan966x_init_groups(vtss_state, VTSS_INIT_CMD_CREATE);
}
#endif /* VTSS_ARCH_LAN966X */
