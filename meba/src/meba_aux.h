// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <microchip/ethernet/board/api.h>

#include "meba_generic.h"

static const int64_t clk_mhz[VTSS_PHY_TS_CLOCK_FREQ_MAX] = {125000000LL, 156250000LL, 200000000LL, 250000000LL, 500000000LL};

static inline mesa_rc meba_conf_get_hex(meba_inst_t inst,
                                        const char *tag,
                                        int *value)
{
    char buf[64];
    if (inst->iface.conf_get(tag, buf, sizeof(buf), NULL) == MESA_RC_OK &&
        sscanf(buf, "%x", value) == 1) {
        return MESA_RC_OK;
    }

    return MESA_RC_ERROR;
}

static inline mesa_rc meba_conf_get_u32(meba_inst_t inst,
                                        const char *tag,
                                        uint32_t *value)
{
    char buf[64];
    if (inst->iface.conf_get(tag, buf, sizeof(buf), NULL) == MESA_RC_OK &&
        sscanf(buf, "%u", value) == 1) {
        return MESA_RC_OK;
    }

    return MESA_RC_ERROR;
}

/**
 * \brief Allocate and initialize instance data
 *
 * \param iface       [IN] The board interface functions
 * \param private_len [IN] Size of the (private) board state
 *
 * \return The board instance - or NULL
 **/
static inline meba_inst_t meba_state_alloc(const meba_board_interface_t *iface,
                                           const char *default_board_name,
                                           mesa_target_type_t default_target,
                                           size_t private_len)
{
    meba_inst_t inst;
    int i;
    if ((inst = (meba_inst_t) malloc(sizeof(*inst))) != NULL) {
        memset(inst, 0, sizeof(*inst));
        inst->api_version = MEBA_API_VERSION;
        inst->instance_size = sizeof(*inst);
        inst->iface = *iface;
        inst->synce_spi_if_fd = -1;

        // Initialize board props
        if (inst->iface.conf_get("board", inst->props.name, sizeof(inst->props.name) - 1, NULL) != MESA_RC_OK) {
            strncpy(inst->props.name, default_board_name, sizeof(inst->props.name) - 1);
        }
        if (meba_conf_get_hex(inst, "target", &i) == MESA_RC_OK) {
            inst->props.target = (mesa_target_type_t) i;
        } else {
            inst->props.target = default_target;
        }
        // Allocate private state
        if (private_len) {
            if ((inst->private_data = malloc(private_len)) == NULL) {
                T_E(inst, "Error allocating %zd bytes private data", private_len);
                free(inst);
                return NULL;
            }
            memset(inst->private_data, 0, private_len);
        }
    } else {
        iface->debug(MEBA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__,
                     "Unable to allocate %zd bytes instance data", sizeof(*inst));
    }
    return inst;
}

typedef struct meba_aux_rawmiim {
    uint8_t status, cmd, data, cfg;
} meba_aux_rawmiim_t;

typedef struct meba_aux_rawgpio {
    uint8_t alt_0;
    uint8_t alt1_0;
} meba_aux_rawgpio_t;

typedef struct meba_aux_rawio {
    uint32_t base;
    uint8_t gcb;
    meba_aux_rawmiim_t miim;
    meba_aux_rawgpio_t gpio;
} meba_aux_rawio_t;

/* Read from primary device */
static inline mesa_rc mebaux_rd(meba_inst_t inst, uint32_t base, uint32_t tgt, uint32_t addr, uint32_t *value)
{
    mesa_rc rc;
    *value = 0xdeadbeef;
    addr += base + (0x01 << 22) + (tgt << 14);
    rc = inst->iface.reg_read(0, addr, value);
    T_R(inst, "tgt: 0x%x, addr: 0x%x, value: 0x%08x", tgt, addr, *value);
    return rc;
}

/* Write to primary device */
static inline mesa_rc mebaux_wr(meba_inst_t inst, uint32_t base, uint32_t tgt, uint32_t addr, uint32_t value)
{
    addr += base + (0x01 << 22) + (tgt << 14);
    T_R(inst, "tgt: 0x%x, addr: 0x%x, value: 0x%08x", tgt, addr, value);
    return inst->iface.reg_write(0, addr, value);
}

static inline void mebaux_gpio_mode_set(meba_inst_t inst, const meba_aux_rawio_t *raw,
                                        int gpio, int alt)
{
    uint32_t mask, i, bit, regoff;
    alt = 1 + alt - MESA_GPIO_ALT_0;  // 1-based
    if (gpio < 32) {
        regoff = raw->gpio.alt_0;     // Lo regset
    } else {
        regoff = raw->gpio.alt1_0;    // Hi regset
        gpio -= 32;
    }
    bit = (1 << gpio);
    for (i = 0; i < 2; i++) {
        (void) mebaux_rd(inst, raw->base, raw->gcb, regoff + i, &mask);
        if (alt & (1 << i)) {
            mask |= bit;
        } else {
            mask &= ~bit;
        }
        mebaux_wr(inst, raw->base, raw->gcb, regoff + i, mask);
    }
}

#define MEBAUX_PHY_CMD_ADDRESS  0 /* 10G: Address */
#define MEBAUX_PHY_CMD_WRITE    1 /* 1G/10G: Write */
#define MEBAUX_PHY_CMD_READ_INC 2 /* 1G: Read, 10G: Read and increment */
#define MEBAUX_PHY_CMD_READ     3 /* 10G: Read */

/* MIIM bus command function for primary device */
static inline mesa_rc mebaux_miim_cmd(meba_inst_t inst, const meba_aux_rawio_t *raw,
                                      uint8_t cmd, uint8_t sof, uint8_t ctrl, uint8_t miim_addr, uint8_t reg_addr, uint16_t *data)
{
    mesa_rc rc;
    uint32_t value, offs = (ctrl * 9);
    int i;

    T_N(inst, "cmd: %u, sof: %u, ctrl: %u, miim_addr: %u, reg_addr: %u",  cmd, sof, ctrl, miim_addr, reg_addr);

    if ((rc = mebaux_wr(inst, raw->base, raw->gcb, raw->miim.cfg + offs, (sof << 9) | (0x32 << 0))) != MESA_RC_OK) {
        return rc;
    }

    rc = mebaux_wr(inst, raw->base, raw->gcb, raw->miim.cmd + offs,
                   (1UL << 31) | (uint32_t)(miim_addr << 25) | (reg_addr << 20) |  ((*data) << 4) | (cmd << 1));
    if (rc != MESA_RC_OK) {
        return rc;
    }

    for (i = 0; i < 100; i++) {
        if ((rc = mebaux_rd(inst, raw->base, raw->gcb, raw->miim.status + offs, &value)) != MESA_RC_OK) {
            return rc;
        }
        T_N(inst, "RD: status(%d) value: 0x%08x", offs, value);
        if (value != 0) {
            continue;
        }

        if (cmd == MEBAUX_PHY_CMD_READ_INC || cmd == MEBAUX_PHY_CMD_READ) {
            rc = mebaux_rd(inst, raw->base, raw->gcb, raw->miim.data + offs, &value);
            if (rc != MESA_RC_OK) {
                return rc;
            }
            T_N(inst, "RD: data(%d) value: 0x%08x", offs, value);
            if (value & 0x30000) {
                break;
            }
            *data = (value & 0xffff);
        }
        return MESA_RC_OK;
    }
    return MESA_RC_ERROR;
}

/* Read PHY register on primary device */
static inline mesa_rc mebaux_miim_rd(meba_inst_t inst, const meba_aux_rawio_t *raw,
                                     uint8_t ctrl, uint8_t miim_addr, uint8_t reg_addr, uint16_t *data)
{
    return mebaux_miim_cmd(inst, raw, MEBAUX_PHY_CMD_READ_INC, 1, ctrl, miim_addr, reg_addr, data);
}

/* Write PHY register on primary device */
static inline mesa_rc mebaux_miim_wr(meba_inst_t inst, const meba_aux_rawio_t *raw,
                                     uint8_t ctrl, uint8_t miim_addr, uint8_t reg_addr, uint16_t data)
{
    uint16_t dptr = data;
    return mebaux_miim_cmd(inst, raw, MEBAUX_PHY_CMD_WRITE, 1, ctrl, miim_addr, reg_addr, &dptr);
}

/* Detect Vitesse 10G PHY module on MIIM controller 0 */
static inline mesa_miim_controller_t mebaux_phy_detect(meba_inst_t inst, const meba_aux_rawio_t *raw,
                                                       uint8_t miim_addr)
{
    uint16_t tmp = 0;
    for (mesa_miim_controller_t ctrl = MESA_MIIM_CONTROLLER_0; ctrl < MESA_MIIM_CONTROLLERS; ctrl++) {
        if (mebaux_miim_rd(inst, raw, ctrl, miim_addr, 0, &tmp) == MESA_RC_OK) {
            T_I(inst, "Found NPI PHY on ctrl%d", ctrl);
            return ctrl;
        }
    }
    T_W(inst, "Did not find an NPI PHY");
    return MESA_MIIM_CONTROLLER_NONE; // Nothing found
}

/* Read MMD register on primary device */
static inline mesa_rc mebaux_mmd_rd(meba_inst_t inst, const meba_aux_rawio_t *raw,
                                    uint8_t ctrl, uint8_t miim_addr, uint8_t mmd, uint16_t addr, uint16_t *value)
{
    mesa_rc rc;

    rc = mebaux_miim_cmd(inst, raw, MEBAUX_PHY_CMD_ADDRESS, 0, ctrl, miim_addr, mmd, &addr);
    if (rc == MESA_RC_OK) {
        rc = mebaux_miim_cmd(inst, raw, MEBAUX_PHY_CMD_READ, 0, ctrl, miim_addr, mmd, value);
    }
    return rc;
}

static inline void meba_deinitialize(meba_inst_t inst)
{
    free(inst);
}

mesa_rc meba_synce_spi_if_spi_transfer(meba_inst_t inst, uint32_t buflen, const uint8_t *tx_data, uint8_t *rx_data);
mesa_rc meba_synce_write(struct meba_inst *inst, uint8_t addr, uint32_t buflen, const uint8_t *tx_data);
mesa_rc meba_synce_read(struct meba_inst *inst, uint8_t addr, uint32_t buflen, uint8_t *rx_data);
mesa_rc meba_synce_spi_if_get_dpll_type(meba_inst_t inst, meba_synce_clock_hw_id_t *dpll_type);
mesa_rc meba_synce_spi_if_dpll_fw_ver_get(meba_inst_t inst, meba_synce_clock_fw_ver_t *dpll_ver);
mesa_rc meba_synce_spi_if_find_spidev(meba_inst_t inst, const char *id, char *spi_file, size_t max_size);

meba_api_synce_t *meba_synce_get();
meba_api_tod_t *meba_tod_get();
meba_api_poe_t *meba_poe_get();
