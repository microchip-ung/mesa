// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_EMUL
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA) && defined(VTSS_OPT_EMUL)

/* 4-byte register per target (11 bits) and address (12 bits) */
#define VTSS_FA_REG_SPACE (1 << 23)
static u32 *vtss_reg_mem;

/* - Static exceptions --------------------------------------------- */

typedef struct {
    u32 addr;
    u32 value;
} vtss_reg_exc_t;

static vtss_reg_exc_t vtss_reg_exc_table[] = {
    /* Chip ID must return a valid number */
    { VTSS_DEVCPU_GCB_CHIP_ID, VTSS_F_DEVCPU_GCB_CHIP_ID_PART_ID(0x7568) },

    /* MAC address table must return IDLE and read invalid entries */
    { VTSS_LRN_COMMON_ACCESS_CTRL, 0 },
    { VTSS_LRN_MAC_ACCESS_CFG_2, 0},

    /* VCAPs must return IDLE */
    { VTSS_VCAP_SUPER_VCAP_UPDATE_CTRL, 0},
    { VTSS_VCAP_ES0_VCAP_UPDATE_CTRL, 0},
    { VTSS_VCAP_ES2_VCAP_UPDATE_CTRL, 0},
    { VTSS_VCAP_IP6PFX_VCAP_UPDATE_CTRL, 0},

    /* Switchcore and RAM reset */
    { VTSS_DEVCPU_GCB_SOFT_RST, 4},
    { VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_RESET, 2},
    { VTSS_ASM_STAT_CFG, 2},
    { VTSS_QSYS_RAM_INIT, 1},
    { VTSS_REW_RAM_INIT, 1},
    { VTSS_VOP_RAM_INIT, 1},
    { VTSS_ANA_AC_RAM_CTRL_RAM_INIT, 1},
    { VTSS_ASM_RAM_INIT, 1},
    { VTSS_EACL_RAM_INIT, 1},
    { VTSS_VCAP_SUPER_RAM_INIT, 1},
    { VTSS_VOP_RAM_INIT, 1},
    { VTSS_DSM_RAM_INIT, 1},

    /* System clock speed needs to be set in HSCH */
    { VTSS_HSCH_SYS_CLK_PER, 16},

    /* Policer init bits need to "self-clear" */
    { VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG, 0},

    /* End of list */
    {0, 0}
};

static BOOL vtss_reg_exc_static(u32 addr, u32 *value, BOOL write)
{
    vtss_reg_exc_t *e;

    if (write) {
        return FALSE;
    }

    for (e = vtss_reg_exc_table; e->addr; e++) {
        if (e->addr == addr) {
            *value = e->value;
            return TRUE;
        }
    }
    return FALSE;
}

/* - Exception function table -------------------------------------- */

typedef BOOL (* vtss_reg_exc_func_t)(u32 addr, u32 *value, BOOL write);

static vtss_reg_exc_func_t vtss_reg_exc_func_table[] = {
    vtss_reg_exc_static,
    NULL
};

static vtss_rc vtss_fa_emul_rd_wr(u32 addr, u32 *value, BOOL write)
{
    vtss_reg_exc_func_t *func;
    BOOL                exc = FALSE;
    u32                 baddr, base = VTSS_IOREG(VTSS_IO_SWC, 0); /* First switch core address */

    if (addr < base) {
        /* CPU register space */
        *value = 0;
    } else {
        /* Switch core register space */
        baddr = (addr - base);
        if (baddr >= VTSS_FA_REG_SPACE) {
            VTSS_E("illegal address: 0x%08x", addr);
            return VTSS_RC_ERROR;
        }

        /* By default, read/write allocated register memory */
        if (write) {
            vtss_reg_mem[baddr] = *value;
        } else {
            *value = vtss_reg_mem[baddr];
        }
    }

    /* Check for exceptions */
    for (func = vtss_reg_exc_func_table; *func != NULL; func++) {
        if ((*func)(addr, value, write)) {
            exc = TRUE;
            break;
        }
    }
    VTSS_N("%s%s addr: 0x%08x, value: 0x%08x", write ? "WR" : "RD", exc ? "X" : " ", addr, *value);
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_emul_rd(u32 addr, u32 *value)
{
    return vtss_fa_emul_rd_wr(addr, value, FALSE);
}

vtss_rc vtss_fa_emul_wr(u32 addr, u32 value)
{
    return vtss_fa_emul_rd_wr(addr, &value, TRUE);
}

vtss_rc vtss_fa_emul_init(vtss_state_t *vtss_state)
{
    /* Each register has 4 bytes */
    size_t size = (4 * VTSS_FA_REG_SPACE);

    VTSS_N("enter");

    if ((vtss_reg_mem = VTSS_OS_MALLOC(size, 0)) == NULL) {
        VTSS_E("malloc register memory failed");
        return VTSS_RC_ERROR;
    }
    VTSS_MEMSET(vtss_reg_mem, 0, size);
    return VTSS_RC_OK;
}
#endif
