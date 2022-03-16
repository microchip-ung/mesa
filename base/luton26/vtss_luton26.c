// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_luton26_cil.h"

#if defined(VTSS_ARCH_LUTON26)

/* ================================================================= *
 *  Function declarations
 * ================================================================= */
static inline BOOL l26_reg_directly_accessible(vtss_state_t *vtss_state, u32 addr)
{
    /* Using SPI, VCoreIII registers require indirect access.
     * Otherwise, all registers are directly accessible.
     */
    return vtss_state->init_conf.spi_bus ?
            (addr < ((VTSS_IO_ORIGIN2_OFFSET - VTSS_IO_ORIGIN1_OFFSET) >> 2)) :
            TRUE;
}

/* Read or write register indirectly */
static vtss_rc l26_reg_indirect_access(vtss_state_t *vtss_state,
                                       u32 addr, u32 *value, BOOL is_write)
{
    /* The following access must be executed atomically, and since this function may be called
     * without the API lock taken, we have to disable the scheduler
     */
    /*lint --e{529} */ // Avoid "Symbol 'flags' not subsequently referenced" Lint warning
    VTSS_OS_SCHEDULER_FLAGS flags = 0;
    u32 ctrl;
    vtss_rc result;

    /* The @addr is an address suitable for the read or write callout function installed by
     * the application, i.e. it's a 32-bit address suitable for presentation on a PI
     * address bus, i.e. it's not suitable for presentation on the VCore-III shared bus.
     * In order to make it suitable for presentation on the VCore-III shared bus, it must
     * be made an 8-bit address, so we multiply by 4, and it must be offset by the base
     * address of the switch core registers, so we add VTSS_IO_ORIGIN1_OFFSET.
     */
    addr <<= 2;
    addr += VTSS_IO_ORIGIN1_OFFSET;

    VTSS_OS_SCHEDULER_LOCK(flags);

    if ((result = vtss_l26_wr(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_ADDR, addr)) != VTSS_RC_OK) {
        goto do_exit;
    }
    if (is_write) {
        if ((result = vtss_l26_wr(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA, *value)) != VTSS_RC_OK) {
            goto do_exit;
        }
        // Wait for operation to complete
        do {
            if ((result = vtss_l26_rd(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL, &ctrl)) != VTSS_RC_OK) {
                goto do_exit;
            }
        } while (ctrl & VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_BUSY);
    } else {
        // Dummy read to initiate access
        if ((result = vtss_l26_rd(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA, value)) != VTSS_RC_OK) {
            goto do_exit;
        }
        // Wait for operation to complete
        do {
            if ((result = vtss_l26_rd(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL, &ctrl)) != VTSS_RC_OK) {
                goto do_exit;
            }
        } while (ctrl & VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_BUSY);
        if ((result = vtss_l26_rd(vtss_state, VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA, value)) != VTSS_RC_OK) {
            goto do_exit;
        }
    }

do_exit:
    VTSS_OS_SCHEDULER_UNLOCK(flags);
    return result;
}

/* Read target register using current CPU interface */
vtss_rc vtss_l26_rd(vtss_state_t *vtss_state, u32 reg, u32 *value)
{
    if (l26_reg_directly_accessible(vtss_state, reg)) {
        return vtss_state->init_conf.reg_read(0, reg, value);
    } else {
        return l26_reg_indirect_access(vtss_state, reg, value, FALSE);
    }
}

/* Write target register using current CPU interface */
vtss_rc vtss_l26_wr(vtss_state_t *vtss_state, u32 reg, u32 value)
{
    if (l26_reg_directly_accessible(vtss_state, reg)) {
        return vtss_state->init_conf.reg_write(0, reg, value);
    } else {
        return l26_reg_indirect_access(vtss_state, reg, &value, TRUE);
    }
}

/* Read-modify-write target register using current CPU interface */
vtss_rc vtss_l26_wrm(vtss_state_t *vtss_state, u32 reg, u32 value, u32 mask)
{
    vtss_rc rc;
    u32     val;

    if ((rc = vtss_l26_rd(vtss_state, reg, &val)) == VTSS_RC_OK) {
        val = ((val & ~mask) | (value & mask));
        rc = vtss_l26_wr(vtss_state, reg, val);
    }
    return rc;
}

/* ================================================================= *
 *  Utility functions
 * ================================================================= */

u32 vtss_l26_port_mask(vtss_state_t *vtss_state, const BOOL member[])
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

/* ================================================================= *
 *  Initialization 
 * ================================================================= */

static vtss_rc l26_setup_cpu_if(vtss_state_t *vtss_state, const vtss_init_conf_t * const conf)
{
    const vtss_pi_conf_t *pi;
    u8                   b;
    u32                  value, wait;
    
    VTSS_D("enter");
    
    /* Setup PI width */
    pi = &conf->pi;
    switch (pi->width) {
    case VTSS_PI_WIDTH_8:  
        b = 0;
        break;
    case VTSS_PI_WIDTH_16: 
        b = VTSS_F_DEVCPU_PI_PI_PI_MODE_DATA_BUS_WID;
        break;
    default:
        VTSS_E("unknown pi->width");
        return VTSS_RC_ERROR;
    }

    /* Endianess */
    value = 0x01020304; /* Endianness test value used in next line */
    if (*((u8 *)&value) == 0x01)
        b |= VTSS_F_DEVCPU_PI_PI_PI_MODE_ENDIAN; /* Big endian */

    /* Mirror settings for all bytes */
    value = ((b<<24) | (b<<16) | (b<<8) | b);
    L26_WR(VTSS_DEVCPU_PI_PI_PI_MODE, value);
    
    /* PI bus cycle configuration */
    wait = pi->cs_wait_ns / 8; /* Wait unit is 8 nsec */
    if (wait > 15)
        wait = 15;
    value = VTSS_F_DEVCPU_PI_PI_PI_CFG_PI_WAIT(wait);
    if(pi->use_extended_bus_cycle)
        value |= VTSS_F_DEVCPU_PI_PI_PI_CFG_BUSY_FEEDBACK_ENA;
    L26_WR(VTSS_DEVCPU_PI_PI_PI_CFG, value);
    
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Debug print
 * ================================================================= */

void vtss_l26_debug_reg_header(const vtss_debug_printf_t pr, const char *name)
{
    char buf[64];
    
    VTSS_SPRINTF(buf, "%-18s  Tgt   Addr", name);
    vtss_debug_print_reg_header(pr, buf);
}

void vtss_l26_debug_reg(vtss_state_t *vtss_state,
                        const vtss_debug_printf_t pr, u32 addr, const char *name)
{
    u32 value;
    char buf[100];

    if (vtss_l26_rd(vtss_state, addr, &value) == VTSS_RC_OK) {
        VTSS_SPRINTF(buf, "%-18s  0x%02x  0x%04x", name, (addr >> 14) & 0x3f, addr & 0x3fff);
        vtss_debug_print_reg(pr, buf, value);
    }
}

void vtss_l26_debug_reg_inst(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name)
{
    char buf[64];

    VTSS_SPRINTF(buf, "%s_%u", name, i);
    vtss_l26_debug_reg(vtss_state, pr, addr, buf);
}

void vtss_l26_debug_print_port_header(vtss_state_t *vtss_state,
                                      const vtss_debug_printf_t pr, const char *txt)
{
    vtss_debug_print_port_header(vtss_state, pr, txt, VTSS_CHIP_PORTS + 1, 1);
}

static vtss_rc l26_debug_info_print(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_l26_misc_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_l26_port_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_l26_packet_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_l26_l2_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_l26_vcap_debug_print(vtss_state, pr, info));
    VTSS_RC(vtss_l26_qos_debug_print(vtss_state, pr, info));
#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_l26_ts_debug_print(vtss_state, pr, info));
#endif /* VTSS_FEATURE_TIMESTAMP */
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Initialization
 * ================================================================= */
vtss_rc vtss_l26_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    /* Initialize ports */
    VTSS_RC(vtss_l26_port_init(vtss_state, cmd));

    /* Initialize miscellaneous */
    VTSS_RC(vtss_l26_misc_init(vtss_state, cmd));

    /* Initialize packet */
    VTSS_RC(vtss_l26_packet_init(vtss_state, cmd));

    /* Initialize L2 */
    VTSS_RC(vtss_l26_l2_init(vtss_state, cmd));

    /* Initialize VCAP */
    VTSS_RC(vtss_l26_vcap_init(vtss_state, cmd));

    /* Initialize QoS */
    VTSS_RC(vtss_l26_qos_init(vtss_state, cmd));

#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_l26_ts_init(vtss_state, cmd));
#endif /* VTSS_FEATURE_TIMESTAMP */

    return VTSS_RC_OK;
}

static vtss_rc l26_port_map_set(vtss_state_t *vtss_state)
{
    /* Initialize function groups */
    return vtss_l26_init_groups(vtss_state, VTSS_INIT_CMD_PORT_MAP);
}   

static vtss_rc l26_restart_conf_set(vtss_state_t *vtss_state)
{
    L26_WR(VTSS_DEVCPU_GCB_CHIP_REGS_GENERAL_PURPOSE, vtss_cmn_restart_value_get(vtss_state));

    return VTSS_RC_OK;
}

static vtss_rc l26_init_conf_set(vtss_state_t *vtss_state)
{
    vtss_init_conf_t *conf = &vtss_state->init_conf;
    u32              value, i;

    VTSS_D("enter");

    VTSS_RC(l26_setup_cpu_if(vtss_state, conf));

    /* Unfortunately a switch-core-only reset also affects the VCore-III
       bus and MIPS frequency, and thereby also the DDR SDRAM controller,
       so until we have a work-around, we skip resetting the switch core. */
#if 0
    {
        u32 gpio_alt[2], i
        /* Before we reset the switch core below, save the current
           GPIO alternate function settings, so that we can restore
           them after the reset. These two registers are reset to their
           defaults with a switch core reset, and are used to select
           a.o. UART operation on two GPIOs. */
        for (i = 0; i < 2; i++) {
            L26_RD(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(i), &gpio_alt[i]);
        }

        /* Top-level switch core reset */
        /* Prevent VCore-III from being reset with a chip soft reset */
        L26_WRM_SET(VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET, VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_PROTECT);
        /* Then reset switch core + internal PHYs. */
        L26_WR(VTSS_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST,
               VTSS_F_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST_SOFT_PHY_RST |
               VTSS_F_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST_SOFT_CHIP_RST);
        /* Unprevent VCore-III from being reset with a chip soft reset */
        L26_WRM_CLR(VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET, VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_PROTECT);

        /* Time to restore GPIO alternate function control */
        for (i = 0; i < 2; i++) {
            L26_WR(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(i), gpio_alt[i]);
        }

        /* After the reset, re-setup the CPU I/F */
        VTSS_RC(l26_setup_cpu_if(conf));
    }
#endif
    // Flush extraction queues
    L26_WR(VTSS_DEVCPU_QS_XTR_XTR_QU_FLUSH, VTSS_F_DEVCPU_QS_XTR_XTR_QU_FLUSH_FLUSH(3));
    VTSS_MSLEEP(1);
    L26_WR(VTSS_DEVCPU_QS_XTR_XTR_QU_FLUSH, VTSS_F_DEVCPU_QS_XTR_XTR_QU_FLUSH_FLUSH(0));

    /* Read chip ID to check CPU interface */
    VTSS_RC(vtss_l26_chip_id_get(vtss_state, &vtss_state->misc.chip_id));
    VTSS_I("chip_id: 0x%04x, revision: 0x%04x", 
           vtss_state->misc.chip_id.part_number, vtss_state->misc.chip_id.revision);

    /* Read restart type */
    L26_RD(VTSS_DEVCPU_GCB_CHIP_REGS_GENERAL_PURPOSE, &value);
    VTSS_RC(vtss_cmn_restart_update(vtss_state, value));
    if (vtss_state->warm_start_cur)
        return VTSS_RC_OK;

    /* BZ17883 - Restart the LC-PLL */
    L26_WRM(VTSS_MACRO_CTRL_PLL5G_CFG_PLL5G_CFG2, VTSS_BIT(1), VTSS_BIT(1));
    L26_WRM(VTSS_MACRO_CTRL_PLL5G_CFG_PLL5G_CFG2, 0,           VTSS_BIT(1));

    /* Initialize memories */
    L26_WR(VTSS_SYS_SYSTEM_RESET_CFG,
           VTSS_F_SYS_SYSTEM_RESET_CFG_MEM_ENA|VTSS_F_SYS_SYSTEM_RESET_CFG_MEM_INIT);
    i = 0;
    do {
        VTSS_MSLEEP(1); /* MEM_INIT should clear after appx. 22us */
        L26_RD(VTSS_SYS_SYSTEM_RESET_CFG, &value);
    } while(i++ < 10 && (value & VTSS_F_SYS_SYSTEM_RESET_CFG_MEM_INIT));
    if(value & VTSS_F_SYS_SYSTEM_RESET_CFG_MEM_INIT) {
        VTSS_E("Memory initialization error, SYS::RESET_CFG: 0x%08x", value);
        return VTSS_RC_ERROR;
    }

    /* Enable switch core */
    L26_WRM_SET(VTSS_SYS_SYSTEM_RESET_CFG, VTSS_F_SYS_SYSTEM_RESET_CFG_CORE_ENA);

    /* Initialize function groups */
    return vtss_l26_init_groups(vtss_state, VTSS_INIT_CMD_INIT);
}

vtss_rc vtss_luton26_inst_create(vtss_state_t *vtss_state)
{
    vtss_cil_func_t *func = &vtss_state->cil;

    /* Initialization */
    func->init_conf_set = l26_init_conf_set;
    func->restart_conf_set = l26_restart_conf_set;
    func->debug_info_print = l26_debug_info_print;
    vtss_state->port.map_set = l26_port_map_set;

    /* Create function groups */
    return vtss_l26_init_groups(vtss_state, VTSS_INIT_CMD_CREATE);
}

#endif /* VTSS_ARCH_LUTON26 */
