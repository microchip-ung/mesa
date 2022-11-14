// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"

#if defined(VTSS_ARCH_LUTON26)
#include "../luton26/vtss_luton26.h"
#endif

#if defined(VTSS_ARCH_OCELOT)
#include "../ocelot/vtss_ocelot.h"
#endif

#if defined(VTSS_ARCH_JAGUAR_2)
#include "../jaguar2/vtss_jaguar2.h"
#endif

#if defined(VTSS_ARCH_SPARX5)
#include "../fa/vtss_fa.h"
#endif

#if defined(VTSS_ARCH_LAN966X)
#include "../lan966x/vtss_lan966x.h"
#endif

/* Default instance */
vtss_inst_t vtss_default_inst = NULL;

/* Trace group table */
vtss_trace_conf_t vtss_trace_conf[VTSS_TRACE_GROUP_COUNT] =
{
    [VTSS_TRACE_GROUP_DEFAULT] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_PORT] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_PHY] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_PACKET] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_QOS] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_L2] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_L3] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_SECURITY] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_EVC] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_FDMA_NORMAL] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_FDMA_IRQ] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_REG_CHECK] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_MPLS] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_HW_PROT] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_HQOS] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_VCAP] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_OAM] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_MRP] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_TS] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
    [VTSS_TRACE_GROUP_CLOCK] = {
        .level = { VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
    },
};

/* ================================================================= *
 *  Initialization
 * ================================================================= */

/* Check and get instance */
vtss_rc vtss_inst_check_get(const vtss_inst_t inst, vtss_state_t **vtss_state)
{
    /* Default instance is used if inst is NULL */
    *vtss_state = (inst == NULL ? vtss_default_inst : inst);

    VTSS_N("enter");

    /* Check cookie */
    if (*vtss_state == NULL || (*vtss_state)->cookie != VTSS_STATE_COOKIE) {
        VTSS_E("illegal inst: %p", inst);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

/* Check instance and save state pointers */
vtss_rc vtss_inst_check(const vtss_inst_t inst, vtss_state_t **vtss_state)
{
    vtss_rc rc;

    if ((rc = vtss_inst_check_get(inst, vtss_state)) == VTSS_RC_OK) {
        /* Select first device by default */
        (*vtss_state)->chip_no = 0;
    }
    return rc;
}

/* Check instance and return the state pointer */
vtss_state_t *vtss_inst_check_no_persist(const vtss_inst_t inst)
{
    /* Default instance is used if inst is NULL */
    vtss_state_t *state = (inst == NULL ? vtss_default_inst : inst);

    VTSS_N("enter");

    /* Check cookie */
    if (state == NULL || state->cookie != VTSS_STATE_COOKIE) {
        VTSS_E("illegal inst: %p", inst);
    }

    return state;
}

vtss_rc vtss_inst_port_no_check(const vtss_inst_t    inst,
                                vtss_state_t         **vtss_state,
                                const vtss_port_no_t port_no)
{
    vtss_rc rc;

    if ((rc = vtss_inst_check(inst, vtss_state)) == VTSS_RC_OK) {
        rc = vtss_port_no_check(*vtss_state, port_no);
    }

    return rc;
}

vtss_rc vtss_inst_port_no_none_check(const vtss_inst_t    inst,
                                     vtss_state_t         **vtss_state,
                                     const vtss_port_no_t port_no)
{
    vtss_rc rc;

    if ((rc = vtss_inst_check(inst, vtss_state)) == VTSS_RC_OK) {
        rc = vtss_port_no_none_check(*vtss_state, port_no);
    }

    return rc;
}

vtss_rc vtss_inst_chip_no_check(const vtss_inst_t    inst,
                                vtss_state_t         **vtss_state,
                                const vtss_chip_no_t chip_no)
{
    vtss_rc rc;

    if ((rc = vtss_inst_check(inst, vtss_state)) == VTSS_RC_OK) {
        if (chip_no >= (*vtss_state)->chip_count) {
            VTSS_E("illegal chip_no: %u", chip_no);
            rc = VTSS_RC_ERROR;
        } else {
            (*vtss_state)->chip_no = chip_no;
        }
    }
    return rc;
}

vtss_rc vtss_inst_get(const vtss_target_type_t target,
                      vtss_inst_create_t       *const create)
{
    VTSS_D("enter");
    create->target = target;
    VTSS_D("exit");

    return VTSS_RC_OK;
}

/* Initialize state to default values */
static vtss_rc vtss_inst_default_set(vtss_state_t *vtss_state)
{
    VTSS_D("enter");

    vtss_state->port_count = VTSS_PORTS;

#if defined(VTSS_FEATURE_SYNCE)
    {
        u32               i;
        for (i=0; i<VTSS_SYNCE_CLK_PORT_ARRAY_SIZE; i++) {
            vtss_state->synce.old_port_no[i] = 0xFFFFFFFF;
        }
    }
#endif /* VTSS_FEATURE_SYNCE*/

    VTSS_D("exit");
    return VTSS_RC_OK;
}

vtss_rc vtss_inst_create(const vtss_inst_create_t *const create,
                         vtss_inst_t              *const inst)
{
    vtss_state_t *vtss_state;
    vtss_arch_t  arch;

    VTSS_D("enter, sizeof(*vtss_state): %zu", sizeof(*vtss_state));

    if ((vtss_state = VTSS_OS_MALLOC(sizeof(*vtss_state), VTSS_MEM_FLAGS_NONE)) == NULL)
        return VTSS_RC_ERROR;

    VTSS_MEMSET(vtss_state, 0, sizeof(*vtss_state));
    vtss_state->cookie = VTSS_STATE_COOKIE;
    vtss_state->create = *create;
    vtss_state->chip_count = 1;

    switch (create->target) {
#if defined(VTSS_ARCH_OCELOT)
    case VTSS_TARGET_7511:
    case VTSS_TARGET_7512:
    case VTSS_TARGET_7513:
    case VTSS_TARGET_7514:
        arch = VTSS_ARCH_SRVL;
        VTSS_RC(vtss_serval_inst_create(vtss_state));
        break;
#endif /* VTSS_ARCH_OCELOT */
#if defined(VTSS_ARCH_LUTON26)
    case VTSS_TARGET_SPARX_III_10_UM:
    case VTSS_TARGET_SPARX_III_17_UM:
    case VTSS_TARGET_SPARX_III_25_UM:
    case VTSS_TARGET_SPARX_III_10:
    case VTSS_TARGET_SPARX_III_18:
    case VTSS_TARGET_SPARX_III_24:
    case VTSS_TARGET_SPARX_III_26:
    case VTSS_TARGET_SPARX_III_10_01:
    case VTSS_TARGET_CARACAL_LITE:
    case VTSS_TARGET_CARACAL_1:
    case VTSS_TARGET_CARACAL_2:
        arch = VTSS_ARCH_L26;
        VTSS_RC(vtss_luton26_inst_create(vtss_state));
        break;
#endif /* VTSS_ARCH_LUTON26 */
#if defined(VTSS_ARCH_JAGUAR_2)
    case VTSS_TARGET_SERVAL_T:
    case VTSS_TARGET_SERVAL_TP:
    case VTSS_TARGET_SERVAL_TE:
    case VTSS_TARGET_SERVAL_TEP:
    case VTSS_TARGET_SERVAL_2_LITE:
    case VTSS_TARGET_SERVAL_TE10:
    case VTSS_TARGET_SPARX_IV_34:
    case VTSS_TARGET_SERVAL_2:
    case VTSS_TARGET_LYNX_2:
    case VTSS_TARGET_JAGUAR_2:
    case VTSS_TARGET_SPARX_IV_44:
    case VTSS_TARGET_SPARX_IV_52:
    case VTSS_TARGET_SPARX_IV_80:
    case VTSS_TARGET_SPARX_IV_90:
        arch = VTSS_ARCH_JR2;
        VTSS_RC(vtss_jaguar2_inst_create(vtss_state));
        break;
#endif /* VTSS_ARCH_JAGUAR_2 */
#if defined(VTSS_ARCH_SPARX5)
    case VTSS_TARGET_7546:
    case VTSS_TARGET_7549:
    case VTSS_TARGET_7552:
    case VTSS_TARGET_7556:
    case VTSS_TARGET_7558:
    case VTSS_TARGET_7546TSN:
    case VTSS_TARGET_7549TSN:
    case VTSS_TARGET_7552TSN:
    case VTSS_TARGET_7556TSN:
    case VTSS_TARGET_7558TSN:
        arch = VTSS_ARCH_ANT;
        VTSS_RC(vtss_fa_inst_create(vtss_state));
        break;
#endif /* VTSS_ARCH_SPARX5 */
#if defined(VTSS_ARCH_LAN966X)
    case VTSS_TARGET_LAN9662:
    case VTSS_TARGET_LAN9668:
        arch = VTSS_ARCH_LAN_966X;
        VTSS_RC(vtss_lan966x_inst_create(vtss_state));
        break;
#endif
    default:
        VTSS_E("unknown target: 0x%05x", create->target);
        return VTSS_RC_ERROR;
    }

    vtss_state->arch = arch;

    /* Set default configuration */
    VTSS_RC(vtss_inst_default_set(vtss_state));

#if defined(VTSS_FEATURE_MISC)
    VTSS_RC(vtss_misc_inst_create(vtss_state));
#endif /* VTSS_FEATURE_MISC */

#if defined(VTSS_FEATURE_PORT_CONTROL)
    VTSS_RC(vtss_port_inst_create(vtss_state));
#endif /* VTSS_FEATURE_PORT_CONTROL */

#if defined(VTSS_FEATURE_PACKET)
    VTSS_RC(vtss_packet_inst_create(vtss_state));
#endif /* VTSS_FEATURE_PACKET */

#if defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_AFI_V2)
     VTSS_RC(vtss_afi_inst_create(vtss_state));
#endif /* VTSS_FEATURE_AFI_SWC && VTSS_AFI_V2 */

#if defined(VTSS_FEATURE_QOS)
    VTSS_RC(vtss_qos_inst_create(vtss_state));
#endif /* VTSS_FEATURE_QOS */

#if defined(VTSS_FEATURE_LAYER2)
    VTSS_RC(vtss_l2_inst_create(vtss_state));
#endif /* VTSS_FEATURE_LAYER2 */

#if defined(VTSS_FEATURE_LAYER3)
    VTSS_RC(vtss_l3_inst_create(vtss_state));
#endif /* VTSS_FEATURE_LAYER2 */

#if defined(VTSS_FEATURE_VCAP)
    VTSS_RC(vtss_vcap_inst_create(vtss_state));
#endif /* VTSS_FEATURE_VCAP */

#if defined(VTSS_FEATURE_VOP)
    VTSS_RC(vtss_oam_inst_create(vtss_state));
#endif /* VTSS_FEATURE_VOP */

#if defined(VTSS_FEATURE_MRP)
    VTSS_RC(vtss_mrp_inst_create(vtss_state));
#endif /* VTSS_FEATURE_MRP */

#if defined(VTSS_FEATURE_TIMESTAMP)
    VTSS_RC(vtss_ts_inst_create(vtss_state));
#endif /* VTSS_FEATURE_TIMESTAMP */

    /* Setup default instance */
    if (vtss_default_inst == NULL)
        vtss_default_inst = vtss_state;

    /* Return instance to application */
    if (inst != NULL)
        *inst = vtss_state;

    VTSS_D("exit");

    return VTSS_RC_OK;
}

vtss_rc vtss_inst_destroy(const vtss_inst_t inst)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state == vtss_default_inst)
            vtss_default_inst = NULL;
        VTSS_OS_FREE(vtss_state, VTSS_MEM_FLAGS_NONE);
    }
    VTSS_D("exit");

    return rc;
}

/* Get initialization configuration */
vtss_rc vtss_init_conf_get(const vtss_inst_t        inst,
                           vtss_init_conf_t * const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        *conf = vtss_state->init_conf;
    VTSS_D("exit");

    return rc;
}

/* Set initialization configuration */
vtss_rc vtss_init_conf_set(const vtss_inst_t              inst,
                           const vtss_init_conf_t * const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("enter");
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->init_conf = *conf;
        rc = VTSS_FUNC_0(cil.init_conf_set);
        vtss_state->warm_start_prev = vtss_state->warm_start_cur;
    } else {
        VTSS_E("Initialization check failed");
    }
    VTSS_D("exit");

    return rc;
}

vtss_rc vtss_register_access_mode_get(const vtss_inst_t inst, BOOL *spi_bus)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if (!spi_bus) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *spi_bus = vtss_state->init_conf.spi_bus;
    }

    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_register_access_mode_set(const vtss_inst_t inst, BOOL spi_bus)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->init_conf.spi_bus = spi_bus;
        if (vtss_state->cil.register_access_mode_set) {
            // Some platforms require a CIL call and some don't
            rc = VTSS_FUNC_0(cil.register_access_mode_set);
        }
    }

    VTSS_EXIT();
    return rc;
}

/* SPI slave initialization configuration */
vtss_rc vtss_spi_slave_init(const vtss_spi_slave_init_t *const conf)
{
#if defined(VTSS_ARCH_LUTON26)
    u32 si = 0, value;
    u32 base_addr = 0x70000>>2;

    VTSS_D("enter endian %u  bit_order %u  padding %u", conf->endian, conf->bit_order, conf->padding);

    if (conf->endian == VTSS_SPI_ENDIAN_BIG) {
        si |= 0x10;
    }

    if (conf->bit_order == VTSS_SPI_BIT_ORDER_LSB_FIRST) {
        si |= 0x20;
    }

    si |= (conf->padding & 0xf);

    VTSS_RC(conf->reg_write(0, base_addr + 1, si));
    VTSS_RC(conf->reg_read(0, base_addr + 1, &value));

    if (si != value) {
        VTSS_E("Read back of SI register failed 0x%08x != 0x%08x", si, value);
        return VTSS_RC_ERROR;
    }
#else // Not VTSS_ARCH_LUTON26
    u32 if_ctrl = 0, if_cfgstat, value;
#ifdef VTSS_ARCH_SPARX5
    u32 base_addr = 0x40406A;
    u32 chip_id;
#else
    u32 base_addr = 0;
#endif

    VTSS_D("enter");

#ifdef VTSS_ARCH_SPARX5
    conf->reg_read(0, 0x404000, &chip_id);
    VTSS_D("chipid: 0x%08x", chip_id);
#endif

    if (conf->endian == VTSS_SPI_ENDIAN_BIG) {
        if_ctrl |= 0x01;
    }

    if (conf->bit_order == VTSS_SPI_BIT_ORDER_LSB_FIRST) {
        if_ctrl |= 0x02;
    }

    if_cfgstat = conf->padding & 0xf;

    VTSS_RC(conf->reg_write(0, base_addr + 0, if_ctrl));
    VTSS_RC(conf->reg_write(0, base_addr + 1, if_cfgstat));

    VTSS_RC(conf->reg_read(0, base_addr + 0, &value));
    if (if_ctrl != value) {
        VTSS_E("Wrong if_ctrl 0x%08x |= 0x%08x", if_ctrl, value);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(conf->reg_read(0, base_addr + 1, &value));
    if (if_cfgstat != (value & 0x0000000f)) {
        VTSS_E("Wrong if_cfgstat 0x%08x |= 0x%08x", if_cfgstat, value);
        return VTSS_RC_ERROR;
    }
#endif
    VTSS_D("exit");
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Miscellaneous
 * ================================================================= */

/* Get trace configuration */
vtss_rc vtss_trace_conf_get(const vtss_trace_group_t group,
                            vtss_trace_conf_t * const conf)
{
    if (group >= VTSS_TRACE_GROUP_COUNT) {
        VTSS_E("illegal group: %d", group);
        return VTSS_RC_ERROR;
    }

    *conf = vtss_trace_conf[group];
    return VTSS_RC_OK;
}

/* Set trace configuration */
vtss_rc vtss_trace_conf_set(const vtss_trace_group_t group,
                            const vtss_trace_conf_t * const conf)
{
    if (group >= VTSS_TRACE_GROUP_COUNT) {
        VTSS_E("illegal group: %d", group);
        return VTSS_RC_ERROR;
    }

    vtss_trace_conf[group] = *conf;
    return VTSS_RC_OK;
}

const char *vtss_port_if_txt(vtss_port_interface_t if_type)
{
    switch (if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION: return "N/C";
    case VTSS_PORT_INTERFACE_LOOPBACK:      return "LOOPBACK";
    case VTSS_PORT_INTERFACE_INTERNAL:      return "INTERNAL";
    case VTSS_PORT_INTERFACE_MII:           return "MII";
    case VTSS_PORT_INTERFACE_GMII:          return "GMII";
    case VTSS_PORT_INTERFACE_RGMII:         return "RGMII";
    case VTSS_PORT_INTERFACE_RGMII_ID:      return "RGMII_ID";
    case VTSS_PORT_INTERFACE_RGMII_RXID:    return "RGMII_RXID";
    case VTSS_PORT_INTERFACE_RGMII_TXID:    return "RGMII_TXID";
    case VTSS_PORT_INTERFACE_TBI:           return "TBI";
    case VTSS_PORT_INTERFACE_RTBI:          return "RTBI";
    case VTSS_PORT_INTERFACE_SGMII:         return "SGMII";
    case VTSS_PORT_INTERFACE_SGMII_2G5:     return "SGMII_2G5";
    case VTSS_PORT_INTERFACE_SERDES:        return "SERDES";
    case VTSS_PORT_INTERFACE_VAUI:          return "VAUI";
    case VTSS_PORT_INTERFACE_100FX:         return "100FX";
    case VTSS_PORT_INTERFACE_XAUI:          return "XAUI";
    case VTSS_PORT_INTERFACE_RXAUI:         return "RXAUI";
    case VTSS_PORT_INTERFACE_XGMII:         return "XGMII";
    case VTSS_PORT_INTERFACE_SPI4:          return "SPI4";
    case VTSS_PORT_INTERFACE_SGMII_CISCO:   return "SGMII_CISCO";
    case VTSS_PORT_INTERFACE_QSGMII:        return "QSGMII";
    case VTSS_PORT_INTERFACE_SFI:           return "SFI";
    case VTSS_PORT_INTERFACE_USGMII:        return "USGMII";
    case VTSS_PORT_INTERFACE_SXGMII:        return "SXGMII";
    case VTSS_PORT_INTERFACE_QXGMII:        return "USX_QXGMII";
    case VTSS_PORT_INTERFACE_DXGMII_10G:    return "DXGMII_10G";
    case VTSS_PORT_INTERFACE_DXGMII_5G:     return "DXGMII_5G";
    case VTSS_PORT_INTERFACE_CPU:           return "CPU";
    }
    return "?   ";
}

const char *vtss_port_spd_txt(vtss_port_speed_t speed)
{
    switch (speed) {
    case VTSS_SPEED_UNDEFINED: return "Undefined";
    case VTSS_SPEED_10M:       return "10M";
    case VTSS_SPEED_100M:      return "100M";
    case VTSS_SPEED_1G:        return "1G";
    case VTSS_SPEED_2500M:     return "2G5";
    case VTSS_SPEED_5G:        return "5G";
    case VTSS_SPEED_10G:       return "10G";
    case VTSS_SPEED_12G:       return "12G";
    case VTSS_SPEED_25G:       return "25G";
    case VTSS_SPEED_AUTO:      return "Auto";
    }
    return "?   ";
}

#if defined(VTSS_FEATURE_PORT_CONTROL)

const char *vtss_serdes_if_txt(vtss_serdes_mode_t serdes)
{
    switch (serdes) {
    case VTSS_SERDES_MODE_DISABLE:   return "Disabled";
    case VTSS_SERDES_MODE_NONE:      return "None";
    case VTSS_SERDES_MODE_XAUI_12G:  return "XAUI_12G";
    case VTSS_SERDES_MODE_XAUI:      return "XAUI";
    case VTSS_SERDES_MODE_RXAUI:     return "RXAUI";
    case VTSS_SERDES_MODE_RXAUI_12G: return "RXAUI_12G";
    case VTSS_SERDES_MODE_2G5:       return "2G5";
    case VTSS_SERDES_MODE_QSGMII:    return "QSGMII";
    case VTSS_SERDES_MODE_SGMII:     return "SGMII";
    case VTSS_SERDES_MODE_100FX:     return "100FX";
    case VTSS_SERDES_MODE_1000BaseX: return "1000BaseX";
    case VTSS_SERDES_MODE_SFI:       return "SFI";
    case VTSS_SERDES_MODE_SFI_SR:    return "SFI_SR";
    case VTSS_SERDES_MODE_SFI_DAC:   return "SFI_DAC";
    case VTSS_SERDES_MODE_SFI_ZR:    return "SFI_ZR";
    case VTSS_SERDES_MODE_SFI_BP:    return "SFI_BP";
    case VTSS_SERDES_MODE_SFI_B2B:   return "SFI_B2B";
    case VTSS_SERDES_MODE_SFI_KR:    return "SFI_KR";
    case VTSS_SERDES_MODE_SFI_PR_NONE:return "SFI_PR_NONE";
    case VTSS_SERDES_MODE_IDLE:      return "IDLE";
    case VTSS_SERDES_MODE_TEST_MODE: return "TEST";
    case VTSS_SERDES_MODE_USXGMII:   return "USXGMII";
    case VTSS_SERDES_MODE_USGMII:    return "USGMII";
    case VTSS_SERDES_MODE_QXGMII:    return "USX_QXGMII";
    case VTSS_SERDES_MODE_DXGMII_10G:return "DXGMII_10G";
    case VTSS_SERDES_MODE_DXGMII_5G: return "DXGMII_5G";
    }
    return "?   ";
}

const char *vtss_media_type_if_txt(vtss_sd10g_media_type_t mt)
{
    switch (mt) {
    case VTSS_SD10G_MEDIA_SR:        return "SR";
    case VTSS_SD10G_MEDIA_ZR:        return "ZR";
    case VTSS_SD10G_MEDIA_DAC:       return "DAC";
    case VTSS_SD10G_MEDIA_DAC_1M:    return "DAC1m";
    case VTSS_SD10G_MEDIA_DAC_2M:    return "DAC2m";
    case VTSS_SD10G_MEDIA_DAC_3M:    return "DAC3m";
    case VTSS_SD10G_MEDIA_DAC_5M:    return "DAC5m";
    case VTSS_SD10G_MEDIA_BP:        return "BP";
    case VTSS_SD10G_MEDIA_B2B:       return "B2B";
    case VTSS_SD10G_MEDIA_10G_KR:    return "KR";
    case VTSS_SD10G_MEDIA_PR_NONE:   return "None";
    }
    return "?   ";
}

#endif

/* - API tod functions -------------------------------------- */

/*
 * If an external ns read function must be called, this variable holds a pointer
 * to the function, otherwise it is NULL.
 */
static tod_get_ns_cnt_cb_t hw_get_ns_callout = 0;

void vtss_tod_set_ns_cnt_cb(tod_get_ns_cnt_cb_t cb)
{
    hw_get_ns_callout = cb;
}

/**
 * \brief Get the current hw nanosec time
 *  Because this function can be called from interrupt and/or with interrupt disabled,
 *  the normal VTSS_ENTER macro is not used, neither is the VTSS_FUNC used, because it copies
 *  an instance pointer to a global variable.
 *  Therefore the CIL layer function is called via the default_inst pointer.
 *
 * \returns actual ns counter
 */
u32 vtss_tod_get_ns_cnt(void)
{
    if (hw_get_ns_callout) {
        return hw_get_ns_callout();
#if defined(VTSS_FEATURE_TIMESTAMP)
    } else if (vtss_default_inst->ts.ns_cnt_get){
        return vtss_default_inst->ts.ns_cnt_get(vtss_default_inst);
#endif
    } else {
        return 0; /* currently no HW support */
    }
}

/* - API SYNCE functions -------------------------------------- */

#if defined(VTSS_FEATURE_SYNCE)
#define clk_port_inx ((clk_port == VTSS_SYNCE_CLK_A) ? 0 : 1)
/* Set the configuration of a selected output clock port - against external clock controller. */
vtss_rc vtss_synce_clock_out_set(const vtss_inst_t              inst,
                                 const vtss_synce_clk_port_t    clk_port,
                                 const vtss_synce_clock_out_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clk_port < VTSS_SYNCE_CLK_MAX) {
            vtss_state->synce.out_conf[clk_port] = *conf;
            rc = VTSS_FUNC_COLD(synce.clock_out_set, clk_port);
        }
        else    rc = VTSS_RC_ERROR;
    }
    VTSS_EXIT();
    return rc;
}

/* Get the configuration of a selected output clock port - against external clock controller. */
vtss_rc vtss_synce_clock_out_get(const vtss_inst_t            inst,
                                 const vtss_synce_clk_port_t  clk_port,
                                 vtss_synce_clock_out_t       *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clk_port < VTSS_SYNCE_CLK_MAX) {
            *conf = vtss_state->synce.out_conf[clk_port];
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

/* Set the configuration of input port for a selected output clock port */
vtss_rc vtss_synce_clock_in_set(const vtss_inst_t              inst,
                                const vtss_synce_clk_port_t    clk_port,
                                const vtss_synce_clock_in_t    *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clk_port < VTSS_SYNCE_CLK_MAX) {
            vtss_state->synce.in_conf[clk_port] = *conf;
            rc = VTSS_FUNC_COLD(synce.clock_in_set, clk_port);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

/* Get the configuration of input port for a selected output clock port */
vtss_rc vtss_synce_clock_in_get(const vtss_inst_t            inst,
                                const vtss_synce_clk_port_t  clk_port,
                                vtss_synce_clock_in_t        *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clk_port < VTSS_SYNCE_CLK_MAX) {
            *conf = vtss_state->synce.in_conf[clk_port];
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

/* Set the configuration of a station clock output */
vtss_rc vtss_synce_synce_station_clk_out_set(const vtss_inst_t              inst,
                                 const vtss_synce_clk_port_t    clk_port,
                                 const vtss_synce_station_clock_out_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clk_port < VTSS_SYNCE_CLK_MAX) {
            vtss_state->synce.station_clk_out_conf[clk_port] = *conf;
            rc = VTSS_FUNC_COLD(synce.station_clk_out_set, clk_port);
        }
        else    rc = VTSS_RC_ERROR;
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_ARCH_SERVAL_T)
/* Get the configuration of a station clock output */
vtss_rc vtss_synce_synce_station_clk_out_get(const vtss_inst_t            inst,
                                 const vtss_synce_clk_port_t  clk_port,
                                 vtss_synce_station_clock_out_t       *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clk_port < VTSS_SYNCE_CLK_MAX) {
            *conf = vtss_state->synce.station_clk_out_conf[clk_port];
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

#endif
#endif /* VTSS_FEATURE_SYNCE */

/* - Warm start functions -------------------------------------- */
#if defined(VTSS_FEATURE_WARM_START)
static vtss_rc vtss_restart_sync(vtss_state_t *vtss_state)
{
#if defined(VTSS_FEATURE_PORT_CONTROL)
    VTSS_RC(vtss_port_restart_sync(vtss_state));
#endif /* VTSS_FEATURE_PORT_CONTROL */

#if defined(VTSS_FEATURE_QOS)
    VTSS_RC(vtss_qos_restart_sync(vtss_state));
#endif /* VTSS_FEATURE_QOS */

#if defined(VTSS_FEATURE_LAYER2)
    VTSS_RC(vtss_l2_restart_sync(vtss_state));
#endif /* VTSS_FEATURE_LAYER2 */

#if defined(VTSS_FEATURE_VCAP)
    VTSS_RC(vtss_vcap_restart_sync(vtss_state));
#endif /* VTSS_FEATURE_VCAP */

    return VTSS_RC_OK;
}

static vtss_rc vtss_restart_cur_set(vtss_state_t *vtss_state, const vtss_restart_t restart)
{
    vtss_rc rc = VTSS_RC_OK;

    vtss_state->restart_cur = restart;
    rc = VTSS_FUNC_0(cil.restart_conf_set);
    return rc;
}

vtss_rc vtss_restart_conf_end(const vtss_inst_t inst)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->warm_start_cur) {
            /* Leave warm start mode */
            vtss_state->warm_start_cur = 0;

            /* Apply configuration */
            VTSS_I("warm start sync start");
            rc = vtss_restart_sync(vtss_state);
            VTSS_I("warm start sync done");
        } else {
            VTSS_I("cold/cool start end");
        }
        /* Next restart is warm */
        if (rc == VTSS_RC_OK) {
            rc = vtss_restart_cur_set(vtss_state, VTSS_RESTART_WARM);
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_restart_status_get(const vtss_inst_t inst,
                                vtss_restart_status_t *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        status->restart = vtss_state->restart_prev;
        status->prev_version = vtss_state->version_prev;
        status->cur_version = vtss_state->version_cur;
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_restart_conf_get(const vtss_inst_t inst,
                              vtss_restart_t *const restart)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *restart = vtss_state->restart_cur;
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_restart_conf_set(const vtss_inst_t inst,
                              const vtss_restart_t restart)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        vtss_state->warm_start_cur == 0) {
        rc = vtss_restart_cur_set(vtss_state, restart);
    }
    VTSS_EXIT();

    return rc;
}
#endif /* VTSS_FEATURE_WARM_START */

#if VTSS_OPT_DEBUG_PRINT

/* - Debug information functions ------------------------------- */

vtss_rc vtss_debug_info_get(vtss_debug_info_t *const info)
{
    vtss_port_no_t port_no;

    VTSS_MEMSET(info, 0, sizeof(*info));
    info->chip_no = VTSS_CHIP_NO_ALL;
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)
        info->port_list[port_no] = 1;
    return VTSS_RC_OK;
}

vtss_rc vtss_debug_info_print(const vtss_inst_t         inst,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = vtss_cmn_debug_info_print(vtss_state, pr, info);
    VTSS_EXIT();

    return rc;
}
#endif // VTSS_OPT_DEBUG_PRINT

vtss_rc vtss_debug_lock(const vtss_inst_t       inst,
                        const vtss_debug_lock_t *const lock)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    /*lint --e{454, 456} */
    VTSS_ENTER();
    /* Lock API and set context to chip number */
    if ((rc = vtss_inst_chip_no_check(inst, &vtss_state, lock->chip_no)) != VTSS_RC_OK) {
        VTSS_EXIT();
    }
    return rc;
}

vtss_rc vtss_debug_unlock(const vtss_inst_t inst,
                          vtss_debug_lock_t *const lock)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    /*lint --e{455} */
    if ((rc = vtss_inst_check_get(inst, &vtss_state)) == VTSS_RC_OK) {
        /* Unlock API and return current chip number */
        lock->chip_no = vtss_state->chip_no;
        VTSS_EXIT();
    }
    return rc;
}
