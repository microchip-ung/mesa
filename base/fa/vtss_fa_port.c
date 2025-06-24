// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_fa_cil.h"
#if defined(VTSS_ARCH_FA)

#define FA_MULTIPLIER_BIT ((VTSS_M_QRES_RES_CFG_WM_HIGH + 1) / 2) // FA=LA

/* - Local functions ------------------------------------------------- */

static vtss_rc fa_port_counters(vtss_state_t               *vtss_state,
                                const vtss_port_no_t        port_no,
                                vtss_port_counters_t *const counters,
                                vtss_counter_cmd_t          cmd);

// Devices:
// D0  - D11      DEV5G  (12)
// D12 - D15      DEV10G  (4)
// D16 - D47      DEV2G5 (32)
// D48 - D55      DEV10G  (8)
// D56 - D63      DEV25G  (8)
// D64            DEV5G   (1)
//                -----------
//                65 port devices + 33 DEV2G5 'shadow' devices

// Serdeses:
// SD0  - SD12    SD5G   (13)
// SD13 - SD24    SD10G  (12)
// SD25 - SD32    SD25G   (8)
//                -----------
//                33 Serdes instances

u32 fla_port_is_2G5(vtss_state_t *vtss_state, u32 port)
{
    if (FA_TGT) {
        return (port >= 16 && port <= 47);
    } else if (LA_TGT) {
        return ((port >= 1 && port <= 3) || (port >= 5 && port <= 7) || (port == 10) ||
                (port == 11) || (port >= 14 && port <= 15) || (port == 18) || (port == 19) ||
                (port == 22) || (port == 23) || (port == 28) || (port == 29));
    } else if (LK_TGT) {
        return (port >= 1 && port <= 31) && ((port % 2) == 1);
    }
    // No return here, rely on -Wreturn-type.
}

u32 fla_port_is_5G(vtss_state_t *vtss_state, u32 port)
{
    if (FA_TGT) {
        return (port <= 11 || port == 64);
    } else if (LA_TGT) {
        return ((port == 9) || (port == 13) || (port == 17) || (port == 21));
    } else if (LK_TGT) {
        return (0);
    }
    // No return here, rely on -Wreturn-type.
}

u32 fla_port_is_10G(vtss_state_t *vtss_state, u32 port)
{
    if (FA_TGT) {
        return ((port >= 12 && port <= 15) || (port >= 48 && port <= 55));
    } else if (LA_TGT) {
        return ((port == 0) || (port == 4) || (port == 8) || (port == 12) || (port == 16) ||
                (port == 20) || (port >= 24 && port <= 27));
    } else if (LK_TGT) {
        return (port >= 0 && port <= 30) && ((port % 2) == 0);
    }
    // No return here, rely on -Wreturn-type.
}

u32 fla_port_is_25G(vtss_state_t *vtss_state, u32 port)
{
    if (FA_TGT) {
        return (port >= 56 && port <= 63);
    } else {
        return (0);
    }
}

// Port nr (0-65) to DEV id e.g. DEV2G5_<id>, DEV10G_<id>
static u32 fla_port_dev_index(vtss_state_t *vtss_state, u32 port, BOOL modes)
{
    if (FA_TGT) {
        if (VTSS_PORT_IS_2G5(port)) {
            return port;
        } else if (VTSS_PORT_IS_5G(port)) {
            if (port <= 11) {
                return port;
            } else {
                return 12;
            }
        } else if (VTSS_PORT_IS_10G(port)) {
            if (port >= 12 && port <= 15) {
                return port - 12;
            } else {
                return port - 44;
            }
        } else if (VTSS_PORT_IS_25G(port)) {
            return port - 56;
        } else {
            VTSS_E("illegal  port number %d", port);
        }
    } else if (LA_TGT) {
        if (VTSS_PORT_IS_2G5(port)) {
            return port;
        } else if (VTSS_PORT_IS_5G(port)) {
            if (modes) {
                // DEV5G_MODES mapping
                return port;
            }
            switch (port) {
            case 9:  return 0;
            case 13: return 1;
            case 17: return 2;
            case 21: return 3;
            }
        } else if (VTSS_PORT_IS_10G(port)) {
            if (modes) {
                // DEV10G_MODES mapping
                return (port == 0 ? 12 : port == 4 ? 13 : port == 8 ? 14 : port == 12 ? 0 : port);
            }
            switch (port) {
            case 0:  return 0;
            case 4:  return 1;
            case 8:  return 2;
            case 12: return 3;
            case 16: return 4;
            case 20: return 5;
            case 24: return 6;
            case 25: return 7;
            case 26: return 8;
            case 27: return 9;
            }
        } else {
            VTSS_E("illegal  port number %d", port);
        }
    } else if (LK_TGT) {
        if (VTSS_PORT_IS_2G5(port) || VTSS_PORT_IS_10G(port)) {
            return port / 2;
        } else {
            VTSS_E("illegal  port number %d", port);
        }
    }
    return 0;
}

u32 vtss_port_dev_index(vtss_state_t *vtss_state, u32 port)
{
    return fla_port_dev_index(vtss_state, port, FALSE);
}

u32 vtss_to_dev2g5(vtss_state_t *vtss_state, u32 port)
{
    switch (port) {
    case 0:  return VTSS_TO_DEV2G5_0;
    case 1:  return VTSS_TO_DEV2G5_1;
    case 2:  return VTSS_TO_DEV2G5_2;
    case 3:  return VTSS_TO_DEV2G5_3;
    case 4:  return VTSS_TO_DEV2G5_4;
    case 5:  return VTSS_TO_DEV2G5_5;
    case 6:  return VTSS_TO_DEV2G5_6;
    case 7:  return VTSS_TO_DEV2G5_7;
    case 8:  return VTSS_TO_DEV2G5_8;
    case 9:  return VTSS_TO_DEV2G5_9;
    case 10: return VTSS_TO_DEV2G5_10;
    case 11: return VTSS_TO_DEV2G5_11;
    case 12: return VTSS_TO_DEV2G5_12;
    case 13: return VTSS_TO_DEV2G5_13;
    case 14: return VTSS_TO_DEV2G5_14;
    case 15: return VTSS_TO_DEV2G5_15;
    case 16: return VTSS_TO_DEV2G5_16;
    case 17: return VTSS_TO_DEV2G5_17;
    case 18: return VTSS_TO_DEV2G5_18;
    case 19: return VTSS_TO_DEV2G5_19;
    case 20: return VTSS_TO_DEV2G5_20;
    case 21: return VTSS_TO_DEV2G5_21;
    case 22: return VTSS_TO_DEV2G5_22;
    case 23: return VTSS_TO_DEV2G5_23;
    case 24: return VTSS_TO_DEV2G5_24;
    case 25: return VTSS_TO_DEV2G5_25;
    case 26: return VTSS_TO_DEV2G5_26;
    case 27: return VTSS_TO_DEV2G5_27;
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAIKA)
    case 28: return VTSS_TO_DEV2G5_28;
    case 29: return VTSS_TO_DEV2G5_29;
    case 30: return VTSS_TO_DEV2G5_30;
    case 31: return VTSS_TO_DEV2G5_31;
#endif
#if defined(VTSS_ARCH_SPARX5)
    case 32: return VTSS_TO_DEV2G5_32;
    case 33: return VTSS_TO_DEV2G5_33;
    case 34: return VTSS_TO_DEV2G5_34;
    case 35: return VTSS_TO_DEV2G5_35;
    case 36: return VTSS_TO_DEV2G5_36;
    case 37: return VTSS_TO_DEV2G5_37;
    case 38: return VTSS_TO_DEV2G5_38;
    case 39: return VTSS_TO_DEV2G5_39;
    case 40: return VTSS_TO_DEV2G5_40;
    case 41: return VTSS_TO_DEV2G5_41;
    case 42: return VTSS_TO_DEV2G5_42;
    case 43: return VTSS_TO_DEV2G5_43;
    case 44: return VTSS_TO_DEV2G5_44;
    case 45: return VTSS_TO_DEV2G5_45;
    case 46: return VTSS_TO_DEV2G5_46;
    case 47: return VTSS_TO_DEV2G5_47;
    case 48: return VTSS_TO_DEV2G5_48;
    case 49: return VTSS_TO_DEV2G5_49;
    case 50: return VTSS_TO_DEV2G5_50;
    case 51: return VTSS_TO_DEV2G5_51;
    case 52: return VTSS_TO_DEV2G5_52;
    case 53: return VTSS_TO_DEV2G5_53;
    case 54: return VTSS_TO_DEV2G5_54;
    case 55: return VTSS_TO_DEV2G5_55;
    case 56: return VTSS_TO_DEV2G5_56;
    case 57: return VTSS_TO_DEV2G5_57;
    case 58: return VTSS_TO_DEV2G5_58;
    case 59: return VTSS_TO_DEV2G5_59;
    case 60: return VTSS_TO_DEV2G5_60;
    case 61: return VTSS_TO_DEV2G5_61;
    case 62: return VTSS_TO_DEV2G5_62;
    case 63: return VTSS_TO_DEV2G5_63;
    case 64: return VTSS_TO_DEV2G5_64;
#endif
#if defined(VTSS_ARCH_LAN969X)
    case 28: return VTSS_TO_DEVRGMII_0;
    case 29: return VTSS_TO_DEVRGMII_1;
#endif
    default: VTSS_E("illegal 2G5 port number %d", port); return 0;
    }
}

u32 vtss_to_dev5g(vtss_state_t *vtss_state, u32 port)
{
    u32 p = vtss_port_dev_index(vtss_state, port);
    switch (p) {
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
    case 0: return VTSS_TO_DEV5G_0;
    case 1: return VTSS_TO_DEV5G_1;
    case 2: return VTSS_TO_DEV5G_2;
    case 3: return VTSS_TO_DEV5G_3;
#endif
#if defined(VTSS_ARCH_SPARX5)
    case 4:  return VTSS_TO_DEV5G_4;
    case 5:  return VTSS_TO_DEV5G_5;
    case 6:  return VTSS_TO_DEV5G_6;
    case 7:  return VTSS_TO_DEV5G_7;
    case 8:  return VTSS_TO_DEV5G_8;
    case 9:  return VTSS_TO_DEV5G_9;
    case 10: return VTSS_TO_DEV5G_10;
    case 11: return VTSS_TO_DEV5G_11;
    case 12: return VTSS_TO_DEV5G_64;
#endif
    default: VTSS_E("illegal 5G port number %d", port); return 0;
    }
}

u32 vtss_to_dev10g(vtss_state_t *vtss_state, u32 port)
{
    u32 p = vtss_port_dev_index(vtss_state, port);
    switch (p) {
    case 0: return VTSS_TO_DEV10G_0;
    case 1: return VTSS_TO_DEV10G_1;
    case 2: return VTSS_TO_DEV10G_2;
    case 3: return VTSS_TO_DEV10G_3;
    case 4: return VTSS_TO_DEV10G_4;
    case 5: return VTSS_TO_DEV10G_5;
    case 6: return VTSS_TO_DEV10G_6;
    case 7: return VTSS_TO_DEV10G_7;
    case 8: return VTSS_TO_DEV10G_8;
    case 9: return VTSS_TO_DEV10G_9;
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAIKA)
    case 10: return VTSS_TO_DEV10G_10;
    case 11: return VTSS_TO_DEV10G_11;
#endif
#if defined(VTSS_ARCH_LAIKA)
    case 12: return VTSS_TO_DEV10G_12;
    case 13: return VTSS_TO_DEV10G_13;
    case 14: return VTSS_TO_DEV10G_14;
    case 15: return VTSS_TO_DEV10G_15;
#endif
    default: VTSS_E("illegal 10G port number %d", port); return 0;
    }
}

u32 vtss_to_dev25g(vtss_state_t *vtss_state, u32 port)
{
    u32 p = vtss_port_dev_index(vtss_state, port);
    switch (p) {
#if defined(VTSS_ARCH_SPARX5)
    case 0: return VTSS_TO_DEV25G_0;
    case 1: return VTSS_TO_DEV25G_1;
    case 2: return VTSS_TO_DEV25G_2;
    case 3: return VTSS_TO_DEV25G_3;
    case 4: return VTSS_TO_DEV25G_4;
    case 5: return VTSS_TO_DEV25G_5;
    case 6: return VTSS_TO_DEV25G_6;
    case 7: return VTSS_TO_DEV25G_7;
#endif
    default: VTSS_E("illegal 25G port number %d", port); return 0;
    }
}

u32 vtss_to_pcs5g(vtss_state_t *vtss_state, u32 port)
{
    u32 p = vtss_port_dev_index(vtss_state, port);
    switch (p) {
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
    case 0: return VTSS_TO_PCS5G_BR_0;
    case 1: return VTSS_TO_PCS5G_BR_1;
    case 2: return VTSS_TO_PCS5G_BR_2;
    case 3: return VTSS_TO_PCS5G_BR_3;
#endif
#if defined(VTSS_ARCH_SPARX5)
    case 4:  return VTSS_TO_PCS5G_BR_4;
    case 5:  return VTSS_TO_PCS5G_BR_5;
    case 6:  return VTSS_TO_PCS5G_BR_6;
    case 7:  return VTSS_TO_PCS5G_BR_7;
    case 8:  return VTSS_TO_PCS5G_BR_8;
    case 9:  return VTSS_TO_PCS5G_BR_9;
    case 10: return VTSS_TO_PCS5G_BR_10;
    case 11: return VTSS_TO_PCS5G_BR_11;
    case 12: return VTSS_TO_PCS5G_BR_64;
#endif
    default: VTSS_E("illegal 5G port number %d", p); return 0;
    }
}

u32 vtss_to_pcs10g(vtss_state_t *vtss_state, u32 port)
{
    u32 p = vtss_port_dev_index(vtss_state, port);
    switch (p) {
    case 0: return VTSS_TO_PCS10G_BR_0;
    case 1: return VTSS_TO_PCS10G_BR_1;
    case 2: return VTSS_TO_PCS10G_BR_2;
    case 3: return VTSS_TO_PCS10G_BR_3;
    case 4: return VTSS_TO_PCS10G_BR_4;
    case 5: return VTSS_TO_PCS10G_BR_5;
    case 6: return VTSS_TO_PCS10G_BR_6;
    case 7: return VTSS_TO_PCS10G_BR_7;
    case 8: return VTSS_TO_PCS10G_BR_8;
    case 9: return VTSS_TO_PCS10G_BR_9;
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAIKA)
    case 10: return VTSS_TO_PCS10G_BR_10;
    case 11: return VTSS_TO_PCS10G_BR_11;
#endif
#if defined(VTSS_ARCH_LAIKA)
    case 12: return VTSS_TO_PCS10G_BR_12;
    case 13: return VTSS_TO_PCS10G_BR_13;
    case 14: return VTSS_TO_PCS10G_BR_14;
    case 15: return VTSS_TO_PCS10G_BR_15;
#endif
    default: VTSS_E("illegal 10G port number %d", p); return 0;
    }
}

u32 vtss_to_pcs25g(vtss_state_t *vtss_state, u32 port)
{
    u32 p = vtss_port_dev_index(vtss_state, port);
    switch (p) {
#if defined(VTSS_ARCH_SPARX5)
    case 0: return VTSS_TO_PCS25G_BR_0;
    case 1: return VTSS_TO_PCS25G_BR_1;
    case 2: return VTSS_TO_PCS25G_BR_2;
    case 3: return VTSS_TO_PCS25G_BR_3;
    case 4: return VTSS_TO_PCS25G_BR_4;
    case 5: return VTSS_TO_PCS25G_BR_5;
    case 6: return VTSS_TO_PCS25G_BR_6;
    case 7: return VTSS_TO_PCS25G_BR_7;
#endif
    default: VTSS_E("illegal 25G port number %d", p); return 0;
    }
}

u32 vtss_to_sd10g_kr(vtss_state_t *vtss_state, u32 port)
{
    u32 p = vtss_port_dev_index(vtss_state, port);
    if (VTSS_PORT_IS_25G(port)) {
        p += 12; // _TGT(VTSS_TO_SD10G_KR covers 10G and 25G, where 25G starts
                 // index 12.
    }
    switch (p) {
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
    case 0: return VTSS_TO_SD10G_KR_0;
    case 1: return VTSS_TO_SD10G_KR_1;
    case 2: return VTSS_TO_SD10G_KR_2;
    case 3: return VTSS_TO_SD10G_KR_3;
    case 4: return VTSS_TO_SD10G_KR_4;
    case 5: return VTSS_TO_SD10G_KR_5;
    case 6: return VTSS_TO_SD10G_KR_6;
    case 7: return VTSS_TO_SD10G_KR_7;
    case 8: return VTSS_TO_SD10G_KR_8;
    case 9: return VTSS_TO_SD10G_KR_9;
#endif
#if defined(VTSS_ARCH_SPARX5)
    case 10: return VTSS_TO_SD10G_KR_10;
    case 11: return VTSS_TO_SD10G_KR_11;
    case 12: return VTSS_TO_SD10G_KR_12;
    case 13: return VTSS_TO_SD10G_KR_13;
    case 14: return VTSS_TO_SD10G_KR_14;
    case 15: return VTSS_TO_SD10G_KR_15;
    case 16: return VTSS_TO_SD10G_KR_16;
    case 17: return VTSS_TO_SD10G_KR_17;
    case 18: return VTSS_TO_SD10G_KR_18;
    case 19: return VTSS_TO_SD10G_KR_19;
#endif
    default: VTSS_E("illegal 10G port number %d", p); return 0;
    }
}

#if defined(VTSS_FEATURE_SD_25G)
static u32 vtss_to_rsfec(vtss_state_t *vtss_state, u32 port)
{
    u32 p = vtss_port_dev_index(vtss_state, port);
    switch (p) {
    case 0:  return VTSS_TO_PCS25G_RSFEC_0;
    case 1:  return VTSS_TO_PCS25G_RSFEC_1;
    case 2:  return VTSS_TO_PCS25G_RSFEC_2;
    case 3:  return VTSS_TO_PCS25G_RSFEC_3;
    case 4:  return VTSS_TO_PCS25G_RSFEC_4;
    case 5:  return VTSS_TO_PCS25G_RSFEC_5;
    case 6:  return VTSS_TO_PCS25G_RSFEC_6;
    case 7:  return VTSS_TO_PCS25G_RSFEC_7;
    default: VTSS_E("illegal 25G port number %d", p); return 0;
    }
}
#endif

u32 vtss_fa_dev_tgt(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 p = VTSS_CHIP_PORT(port_no);
    return (vtss_state->port.conf[port_no].speed <= VTSS_SPEED_2500M) ? VTSS_TO_DEV2G5(p)
                                                                      : VTSS_TO_HIGH_DEV(p);
}

static BOOL port_is_rgmii(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    if ((vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_RGMII) ||
        (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_RGMII_ID) ||
        (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_RGMII_RXID) ||
        (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_RGMII_TXID)) {
        return TRUE;
    }
    return FALSE;
}

vtss_rc vtss_cil_port_clause_37_control_get(vtss_state_t                        *vtss_state,
                                            const vtss_port_no_t                 port_no,
                                            vtss_port_clause_37_control_t *const control)
{
    u32 value;
    u32 tgt = VTSS_TO_DEV2G5(VTSS_CHIP_PORT(port_no));

    REG_RD(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt), &value);
    control->enable = VTSS_BOOL(VTSS_X_DEV1G_PCS1G_ANEG_CFG_ANEG_ENA(value));
    value = VTSS_X_DEV1G_PCS1G_ANEG_CFG_ADV_ABILITY(control->enable ? value : 0);
    VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &control->advertisement));

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_clause_37_control_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{

    vtss_port_clause_37_control_t *control = &vtss_state->port.clause_37[port_no];
    u32                            value;
    u32                            tgt = VTSS_TO_DEV2G5(VTSS_CHIP_PORT(port_no));

    /* Aneg capabilities for this port */
    VTSS_RC(vtss_cmn_port_clause_37_adv_set(&value, &control->advertisement, control->enable));

    /* Set aneg capabilities, enable neg and restart */
    REG_WR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt),
           VTSS_F_DEV1G_PCS1G_ANEG_CFG_ADV_ABILITY(value) |
               VTSS_F_DEV1G_PCS1G_ANEG_CFG_ANEG_ENA(1) |
               VTSS_F_DEV1G_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1));

    if (!control->enable) {
        /* Disable Aneg */
        REG_WR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_ANEG_CFG_ADV_ABILITY(0) |
                   VTSS_F_DEV1G_PCS1G_ANEG_CFG_ANEG_ENA(0) |
                   VTSS_F_DEV1G_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1));
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_port_usxgmii_status_get(vtss_state_t                       *vtss_state,
                                          const vtss_port_no_t                port_no,
                                          vtss_port_clause_37_status_t *const status)
{
    u32                       tgt, adv, aneg = 0, port = VTSS_CHIP_PORT(port_no);
    vtss_port_interface_t     if_type = vtss_state->port.conf[port_no].if_type;
    vtss_port_usxgmii_aneg_t *usxgmii = &status->autoneg.partner.usxgmii;

    if (if_type == VTSS_PORT_INTERFACE_QXGMII || if_type == VTSS_PORT_INTERFACE_DXGMII_5G) {
        tgt = VTSS_TO_DEV2G5(port);
#if !defined(VTSS_ARCH_LAIKA)
        REG_RD(VTSS_DEV1G_USXGMII_ANEG_STATUS(tgt), &aneg);
        REG_WR(VTSS_DEV1G_USXGMII_ANEG_STATUS(tgt), aneg); /* Clear PAGE_RX_STICKY */
#endif
    } else {
        tgt = VTSS_TO_HIGH_DEV(port);
        REG_RD(VTSS_DEV10G_USXGMII_ANEG_STATUS(tgt), &aneg);
        REG_WR(VTSS_DEV10G_USXGMII_ANEG_STATUS(tgt), aneg); /* Clear PAGE_RX_STICKY */
    }

    status->autoneg.complete = REG_BF(DEV10G_USXGMII_ANEG_STATUS_ANEG_COMPLETE, aneg);
    adv = VTSS_X_DEV10G_USXGMII_ANEG_STATUS_LP_ADV_ABILITY(aneg);
    VTSS_RC(vtss_cmn_port_usxgmii_aneg_get(adv, usxgmii));
    status->link = !VTSS_X_DEV10G_USXGMII_ANEG_STATUS_PAGE_RX_STICKY(aneg) &&
                   !VTSS_X_DEV10G_USXGMII_ANEG_STATUS_LINK_DOWN_STATUS(aneg);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_clause_37_status_get(vtss_state_t                       *vtss_state,
                                           const vtss_port_no_t                port_no,
                                           vtss_port_clause_37_status_t *const status)

{
    u32                     value, port = VTSS_CHIP_PORT(port_no);
    u32                     tgt = VTSS_TO_DEV2G5(port);
    vtss_port_sgmii_aneg_t *sgmii_adv = &status->autoneg.partner.sgmii;
    vtss_port_interface_t   if_type = vtss_state->port.conf[port_no].if_type;
    BOOL                    in_sync = 0;

    if (vtss_state->port.conf[port_no].power_down) {
        status->link = 0;
        return VTSS_RC_OK;
    }

    if (if_type == VTSS_PORT_INTERFACE_USGMII) {
        VTSS_E("USGMII mode not supported\n");
        return VTSS_RC_ERROR;
    }

    /* USXGMII modes  */
    if (if_type == VTSS_PORT_INTERFACE_QXGMII || if_type == VTSS_PORT_INTERFACE_USXGMII ||
        if_type == VTSS_PORT_INTERFACE_DXGMII_10G || if_type == VTSS_PORT_INTERFACE_DXGMII_5G) {
        return fa_port_usxgmii_status_get(vtss_state, port_no, status);
    }

    /* Get the link state 'down' sticky bit  */
    REG_RD(VTSS_DEV1G_PCS1G_STICKY(tgt), &value);
    status->link = (REG_BF(DEV1G_PCS1G_STICKY_LINK_DOWN_STICKY, value) ? 0 : 1);
    if (status->link == 0) {
        /* The link has been down. Clear the sticky bit and return the 'down'
         * value  */
        REG_WR(VTSS_DEV1G_PCS1G_STICKY(tgt), VTSS_M_DEV1G_PCS1G_STICKY_LINK_DOWN_STICKY);
    } else {
        /* PCS1G_LINK_STATUS holds the result of 1) aneg-enable=LINK_OK or
                                                 2)
           aneg-disable=AN_DISABLE_LINK_OK */
        REG_RD(VTSS_DEV1G_PCS1G_LINK_STATUS(tgt), &value);
        status->link = REG_BF(DEV1G_PCS1G_LINK_STATUS_LINK_STATUS, value) &&
                       REG_BF(DEV1G_PCS1G_LINK_STATUS_SYNC_STATUS, value);
        in_sync = REG_BF(DEV1G_PCS1G_LINK_STATUS_SYNC_STATUS, value);
    }

    /* Get PCS ANEG status register */
    REG_RD(VTSS_DEV1G_PCS1G_ANEG_STATUS(tgt), &value);

    /* Get 'Aneg complete'   */
    status->autoneg.complete = REG_BF(DEV1G_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);

    /* Workaround for a Clause 37 Aneg issue (TN1395)
       1) When aneg completes with FDX capability=0
       2) PCS in in sync and ACK is received but we cannot complete aneg. */
    if (in_sync && vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SERDES) {
        if ((status->autoneg.complete &&
             (((value >> 21) & 0x1) == 0)) || /* aneg-complete && !FDX */
            (!status->autoneg.complete &&
             (((value >> 30) & 0x1) == 1))) { /* !aneg-complete && ACK */
            /* Reset PCS and restart Aneg */
            REG_WRM_CLR(VTSS_DEV1G_PCS1G_CFG(tgt), VTSS_M_DEV1G_PCS1G_CFG_PCS_ENA);
            REG_WRM_SET(VTSS_DEV1G_PCS1G_CFG(tgt), VTSS_M_DEV1G_PCS1G_CFG_PCS_ENA);
            (void)vtss_cil_port_clause_37_control_set(vtss_state, port_no);
            VTSS_MSLEEP(50);
            REG_RD(VTSS_DEV1G_PCS1G_ANEG_STATUS(tgt), &value);
            status->autoneg.complete = REG_BF(DEV1G_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);
        }
    }

    /* Return partner advertisement ability */
    value = VTSS_X_DEV1G_PCS1G_ANEG_STATUS_LP_ADV_ABILITY(value);

    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
        VTSS_RC(vtss_cmn_port_sgmii_cisco_aneg_get(value, sgmii_adv));
        /* status->link = PCS link. sgmii_adv->link = Phy link */
        status->link = sgmii_adv->link & status->link;
    } else {
        VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &status->autoneg.partner.cl37));
    }
    return VTSS_RC_OK;
}

static BOOL fa_change_device(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no);

    if (VTSS_PORT_IS_2G5(port)) {
        return FALSE; // This is the primary device
    }

    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_USXGMII) {
        return FALSE; // Can run all speeds
    }

    if ((((vtss_state->port.current_speed[port_no] <= VTSS_SPEED_2500M) &&
          (vtss_state->port.conf[port_no].speed > VTSS_SPEED_2500M))) ||
        ((vtss_state->port.current_speed[port_no] > VTSS_SPEED_2500M) &&
         (vtss_state->port.conf[port_no].speed <= VTSS_SPEED_2500M)) ||
        (vtss_state->port.current_speed[port_no] == VTSS_SPEED_UNDEFINED)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

BOOL fa_is_high_speed_device(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_USXGMII ||
        vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_DXGMII_10G) {
        return TRUE;
    }
    return vtss_state->port.conf[port_no].speed > VTSS_SPEED_2500M ? TRUE : FALSE;
}

BOOL vtss_fa_port_is_high_speed(vtss_state_t *vtss_state, u32 port)
{
    u32 value = 0, mask = 0;

    if (VTSS_PORT_IS_2G5(port)) {
        return FALSE;
    }

    if (VTSS_PORT_IS_5G(port)) {
#if !defined(VTSS_ARCH_LAIKA)
        REG_RD(VTSS_PORT_CONF_DEV5G_MODES, &value);
#endif
    } else if (VTSS_PORT_IS_10G(port)) {
        REG_RD(VTSS_PORT_CONF_DEV10G_MODES, &value);
    } else if (VTSS_PORT_IS_25G(port)) {
#if defined(VTSS_FEATURE_SD_25G)
        REG_RD(VTSS_PORT_CONF_DEV25G_MODES, &value);
#endif
    }
    mask = VTSS_BIT(fla_port_dev_index(vtss_state, port, TRUE));
    return (value & mask ? FALSE : TRUE);
}

static u16 wm_enc(u16 value)
{
    if (value >= FA_MULTIPLIER_BIT) {
        return FA_MULTIPLIER_BIT + value / 16;
    }
    return value;
}

#if VTSS_OPT_DEBUG_PRINT
static u32 wm_dec(u32 value)
{
    if (value >= FA_MULTIPLIER_BIT) {
        return (value - FA_MULTIPLIER_BIT) * 16;
    }
    return value;
}
#endif

/* - CIL functions ------------------------------------------------- */

/* ================================================================= *
 *  Synce
 * ================================================================= */

#if defined(VTSS_FEATURE_SYNCE)
#define RCVRD_CLK_GPIO_NO 60 // on Fireant the 4 recovered clock outputs are GPIO 60-63
vtss_rc vtss_cil_synce_clock_out_set(vtss_state_t *vtss_state, const vtss_synce_clk_port_t clk_port)
{
    u32                     div_mask;
    vtss_synce_clock_out_t *conf;

    if (!vtss_state->vtss_features[FEATURE_SYNCE]) {
        return VTSS_RC_ERROR;
    }

    if (clk_port > 3) {
        VTSS_E("Invalid clock port no: %d\n", clk_port);
        return VTSS_RC_ERROR;
    }

    conf = &vtss_state->synce.out_conf[clk_port];

    VTSS_D("clk_port %X  enable %u\n", clk_port, conf->enable);

    switch (conf->divider) {
    case VTSS_SYNCE_DIVIDER_1:  div_mask = 6; break;
    case VTSS_SYNCE_DIVIDER_2:  div_mask = 0; break;
    case VTSS_SYNCE_DIVIDER_4:  div_mask = 1; break;
    case VTSS_SYNCE_DIVIDER_5:  div_mask = 4; break;
    case VTSS_SYNCE_DIVIDER_8:  div_mask = 2; break;
    case VTSS_SYNCE_DIVIDER_16: div_mask = 3; break;
    case VTSS_SYNCE_DIVIDER_25: div_mask = 5; break;
    default:                    div_mask = 0; break;
    }
    REG_WRM(VTSS_HSIOWRAP_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(div_mask) |
                VTSS_F_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA(conf->enable),
            VTSS_M_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV |
                VTSS_M_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA);

    if (VTSS_RC_OK != vtss_fa_gpio_mode(vtss_state, 0, RCVRD_CLK_GPIO_NO + clk_port,
                                        conf->enable ? VTSS_GPIO_ALT_0 : VTSS_GPIO_IN)) {
        VTSS_E("Failed to set GPIO mode for recovered clock[%d]\n", clk_port);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_synce_clock_in_set(vtss_state_t *vtss_state, const vtss_synce_clk_port_t clk_port)
{
    vtss_synce_clock_in_t     *conf;
    vtss_synce_clock_in_type_t port_type;
    vtss_port_conf_t          *port_conf;
#if VTSS_OPT_TRACE
    i32 chip_port = 0;
#endif
    i32  clk_src;
    BOOL ena;
    u32  sd_indx, sd_type, clk_div, sd_ena, sd_lane_tgt = 0;

    VTSS_D("Enter");

    if (!vtss_state->vtss_features[FEATURE_SYNCE]) {
        return VTSS_RC_ERROR;
    }

    if (clk_port > 3) {
        VTSS_E("Invalid clock port no: %d\n", clk_port);
        return VTSS_RC_ERROR;
    }
    conf = &vtss_state->synce.in_conf[clk_port];
    if (conf->port_no >= VTSS_PORTS) {
        VTSS_E("Invalid port no: %d\n", conf->port_no);
        return VTSS_RC_ERROR;
    }
    ena = conf->enable;
    port_type = conf->clk_in;
    port_conf = &vtss_state->port.conf[conf->port_no];

    if (port_type == VTSS_SYNCE_CLOCK_INTERFACE) { /* Port type is interface so the clock
                                                      source is a SerDes */
        /* The SerDes number is the clock source */
        if (VTSS_RC_OK != vtss_fa_port2sd(vtss_state, conf->port_no, &sd_indx, &sd_type)) {
            return VTSS_RC_ERROR;
        }
        if (sd_type == FA_SERDES_TYPE_10G) {
            sd_indx = sd_indx + RT_SERDES_10G_START;
        } else if (sd_type == FA_SERDES_TYPE_25G) {
            sd_indx = sd_indx + RT_SERDES_25G_START;
        } else if (sd_type == FA_SERDES_TYPE_6G) {
            sd_indx = sd_indx;
        } else {
            VTSS_E("Unknown SERDES type %u", sd_type);
            return VTSS_RC_ERROR;
        }
        sd_lane_tgt = VTSS_TO_SD_LANE(sd_indx);
        clk_src = sd_indx;
    } else if (port_type == VTSS_SYNCE_CLOCK_AUX) { /* Port type is AUX so the clock source
                                                       is the AUX number */
        if (conf->port_no > 3) {
            VTSS_E("AUX port out of range.  port_no %u", conf->port_no);
            return VTSS_RC_ERROR;
        }
        clk_src = conf->port_no + 33;
    } else {
        VTSS_E("Port type not supported for port_no %u, port_type %u", conf->port_no, port_type);
        return VTSS_RC_ERROR;
    }
    VTSS_D("clk_port %X, port_no %u, chip port %u enable %u, squelsh %u, clk_src %d\n", clk_port,
           conf->port_no, chip_port, ena, conf->squelsh, clk_src);

    /* Configure the SerDes to select for recovered clock */
    REG_WRM(VTSS_HSIOWRAP_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(clk_src) |
                VTSS_F_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA(ena),
            VTSS_M_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC |
                VTSS_M_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA);

    if (ena) {
        /* Enable input clock configuration - now configuring the new (or maybe
         * the same) input port */
        if (port_type == VTSS_SYNCE_CLOCK_INTERFACE) { /* Port type is interface so the clock
                                                          source is a SerDes */
            /* In the following the SERDES recovered clock divider (LANE divider
             * in DS1241) is calculated. */
            /* Values are chosen that gives frequency closest to 100 MHz or the
             * frequency closest to a whole number - less decimals */
            clk_div = 0; /* Divide by 1 is default */
            if ((port_conf->speed == VTSS_SPEED_25G) || (port_conf->speed == VTSS_SPEED_10G) ||
                (port_conf->speed == VTSS_SPEED_5G)) {
                clk_div = 1; /* Divide by 2 */
            }

            if (port_conf->serdes.media_type == VTSS_SD10G_MEDIA_SR ||
                port_conf->serdes.media_type ==
                    VTSS_SD10G_MEDIA_ZR) { /* Optical SFP with LOS signal
                                              connected to serial GPIO */
                sd_ena = 1;
            } else { /* No LOS signal connected to serial GPIO */
                sd_ena = 0;
            }

            if (sd_type == FA_SERDES_TYPE_25G) {
#if defined(VTSS_FEATURE_SD_25G)
                REG_WRM(
                    VTSS_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG(sd_lane_tgt),
                    VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(clk_div) |
                        VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(conf->squelsh),
                    VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV |
                        VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA);

                REG_WR(VTSS_SD25G_CFG_TARGET_SD_CFG(sd_lane_tgt),
                       VTSS_F_SD25G_CFG_TARGET_SD_CFG_SD_SEL(1) |
                           VTSS_F_SD25G_CFG_TARGET_SD_CFG_SD_POL(0) |
                           VTSS_F_SD25G_CFG_TARGET_SD_CFG_SD_ENA(sd_ena));
#endif
            } else {
                REG_WRM(VTSS_SD_LANE_TARGET_SYNC_ETH_SD_CFG(sd_lane_tgt),
                        VTSS_F_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(clk_div) |
                            VTSS_F_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(conf->squelsh),
                        VTSS_M_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV |
                            VTSS_M_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA);
                if (FA_TGT) {
                    REG_WR(VTSS_SD_LANE_TARGET_SD_CFG(sd_lane_tgt),
                           VTSS_F_SD_LANE_TARGET_SD_CFG_SD_SEL(1) |
                               VTSS_F_SD_LANE_TARGET_SD_CFG_SD_POL(0) |
                               VTSS_F_SD_LANE_TARGET_SD_CFG_SD_ENA(sd_ena));
                }
            }
        } else if (port_type == VTSS_SYNCE_CLOCK_AUX) { /* Port type is AUX so the clock
                                                           source is the AUX number */
            /* TBD */
            VTSS_E("VTSS_SYNCE_CLOCK_AUX not supported yet");
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_synce_station_clk_out_set(vtss_state_t               *vtss_state,
                                           const vtss_synce_clk_port_t clk_port_par)
{
    if (!vtss_state->vtss_features[FEATURE_SYNCE]) {
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_SYNCE */

/* ================================================================= *
 *  MIIM control
 * ================================================================= */
#if !defined(VTSS_ARCH_LAIKA)

/* PHY commands */
#define PHY_CMD_ADDRESS  0 /* 10G: Address */
#define PHY_CMD_WRITE    1 /* 1G/10G: Write */
#define PHY_CMD_READ_INC 2 /* 1G: Read, 10G: Read and increment */
#define PHY_CMD_READ     3 /* 10G: Read */

static vtss_rc fa_miim_cmd(vtss_state_t          *vtss_state,
                           u32                    cmd,
                           u32                    sof,
                           vtss_miim_controller_t miim_controller,
                           u8                     miim_addr,
                           u8                     addr,
                           u16                   *data,
                           BOOL                   report_errors)
{
    u32 i, n;
    u32 value;

    switch (miim_controller) {
    case VTSS_MIIM_CONTROLLER_0: i = 0; break;
    case VTSS_MIIM_CONTROLLER_1: i = 1; break;
#if defined(VTSS_ARCH_SPARX5)
    case VTSS_MIIM_CONTROLLER_2: i = 2; break;
    case VTSS_MIIM_CONTROLLER_3: i = 3; break;
#endif
    default: VTSS_E("illegal miim_controller: %d", miim_controller); return VTSS_RC_ERROR;
    }

    /* Set Start of frame field */
    REG_WRM(VTSS_DEVCPU_GCB_MII_CFG(i), VTSS_F_DEVCPU_GCB_MII_CFG_MIIM_ST_CFG_FIELD(sof),
            VTSS_M_DEVCPU_GCB_MII_CFG_MIIM_ST_CFG_FIELD);

    /* Read command is different for Clause 22 */
    if (sof == 1 && cmd == PHY_CMD_READ) {
        cmd = PHY_CMD_READ_INC;
    }

    /* Start command */
    REG_WR(VTSS_DEVCPU_GCB_MII_CMD(i), VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_VLD |
                                           VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_PHYAD(miim_addr) |
                                           VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_REGAD(addr) |
                                           VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_WRDATA(*data) |
                                           VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_OPR_FIELD(cmd));

    /* Wait for access to complete */
    for (n = 0;; n++) {
        REG_RD(VTSS_DEVCPU_GCB_MII_STATUS(i), &value);
        if ((value & (VTSS_M_DEVCPU_GCB_MII_STATUS_MIIM_STAT_PENDING_RD |
                      VTSS_M_DEVCPU_GCB_MII_STATUS_MIIM_STAT_PENDING_WR)) == 0) {
            break;
        }
        if (n == 1000) {
            goto mmd_error;
        }
    }

    /* Read data */
    if (cmd == PHY_CMD_READ || cmd == PHY_CMD_READ_INC) {
        REG_RD(VTSS_DEVCPU_GCB_MII_DATA(i), &value);
        if (value & VTSS_M_DEVCPU_GCB_MII_DATA_MIIM_DATA_SUCCESS) {
            goto mmd_error;
        }
        *data = VTSS_X_DEVCPU_GCB_MII_DATA_MIIM_DATA_RDDATA(value);
    }

    return VTSS_RC_OK;
mmd_error:
    if (report_errors) {
        VTSS_E("miim failed, cmd: %s, miim_addr: %u, addr: %u, miim_controller:%u, sof:%u",
               cmd == PHY_CMD_READ      ? "PHY_CMD_READ"
               : cmd == PHY_CMD_WRITE   ? "PHY_CMD_WRITE"
               : cmd == PHY_CMD_ADDRESS ? "PHY_CMD_ADDRESS"
                                        : "PHY_CMD_READ_INC",
               miim_addr, addr, miim_controller, sof);
    }

    return VTSS_RC_ERROR;
}

vtss_rc vtss_cil_miim_read(vtss_state_t          *vtss_state,
                           vtss_miim_controller_t miim_controller,
                           u8                     miim_addr,
                           u8                     addr,
                           u16                   *value,
                           BOOL                   report_errors)
{
    return fa_miim_cmd(vtss_state, PHY_CMD_READ, 1, miim_controller, miim_addr, addr, value,
                       report_errors);
}

vtss_rc vtss_cil_miim_write(vtss_state_t          *vtss_state,
                            vtss_miim_controller_t miim_controller,
                            u8                     miim_addr,
                            u8                     addr,
                            u16                    value,
                            BOOL                   report_errors)
{
    return fa_miim_cmd(vtss_state, PHY_CMD_WRITE, 1, miim_controller, miim_addr, addr, &value,
                       report_errors);
}

vtss_rc vtss_cil_mmd_read(vtss_state_t          *vtss_state,
                          vtss_miim_controller_t miim_controller,
                          u8                     miim_addr,
                          u8                     mmd,
                          u16                    addr,
                          u16                   *value,
                          BOOL                   report_errors)
{

    VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd, &addr,
                        report_errors));
    if (fa_miim_cmd(vtss_state, PHY_CMD_READ, 0, miim_controller, miim_addr, mmd, value, 0) !=
        VTSS_RC_OK) {
        if (report_errors) {
            VTSS_E("fa_mmd_read failed, miim_controller:%d miim_addr:%x, mmd:%x, addr:%x",
                   miim_controller, miim_addr, mmd, addr);
        }
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

/* MMD (MDIO Management Devices (10G)) read-inc */
vtss_rc vtss_cil_mmd_read_inc(vtss_state_t          *vtss_state,
                              vtss_miim_controller_t miim_controller,
                              u8                     miim_addr,
                              u8                     mmd,
                              u16                    addr,
                              u16                   *buf,
                              u8                     count,
                              BOOL                   report_errors)
{

    VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd, &addr,
                        report_errors));
    while (count > 1) {
        VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_READ_INC, 0, miim_controller, miim_addr, mmd, buf,
                            report_errors));
        buf++;
        count--;
    }
    VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_READ, 0, miim_controller, miim_addr, mmd, buf,
                        report_errors));
    return VTSS_RC_OK;
}

/* MMD (MDIO Management Devices (10G)) write */
vtss_rc vtss_cil_mmd_write(vtss_state_t          *vtss_state,
                           vtss_miim_controller_t miim_controller,
                           u8                     miim_addr,
                           u8                     mmd,
                           u16                    addr,
                           u16                    data,
                           BOOL                   report_errors)
{
    VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd, &addr,
                        report_errors));
    return fa_miim_cmd(vtss_state, PHY_CMD_WRITE, 0, miim_controller, miim_addr, mmd, &data,
                       report_errors);
}

#endif /* !VTSS_ARCH_LAIKA */

/* ================================================================= *
 *  KR related functions
 * ================================================================= */

vtss_rc vtss_cil_port_kr_ctle_adjust(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return fa_serdes_ctle_adjust(vtss_state,
#if VTSS_OPT_DEBUG_PRINT
                                 NULL,
#endif
                                 port_no, FALSE, NULL, NULL, NULL);
}

vtss_rc vtss_cil_port_kr_ctle_get(vtss_state_t           *vtss_state,
                                  const vtss_port_no_t    port_no,
                                  vtss_port_ctle_t *const ctle)
{
    return fa_serdes_ctle_adjust(vtss_state,
#if VTSS_OPT_DEBUG_PRINT
                                 NULL,
#endif
                                 port_no, TRUE, &ctle->vga, &ctle->eqr, &ctle->edc);
}

#define PORT_IS_KR_CAP(p)                                                                          \
    (VTSS_PORT_IS_2G5(VTSS_CHIP_PORT(p)) || VTSS_PORT_IS_5G(VTSS_CHIP_PORT(p))) ? FALSE : TRUE

#if defined(VTSS_FEATURE_PORT_KR_IRQ)

#define NP_NULL         (VTSS_BIT(0) | VTSS_BIT(13) | VTSS_BIT(14))
#define NP_TOGGLE       (VTSS_BIT(11))
#define NP_ACK2         (VTSS_BIT(12))
#define NP_MP           (VTSS_BIT(13))
#define NP_ACK          (VTSS_BIT(14))
#define NP_NP           (VTSS_BIT(15))
#define NP_RSFEC        (VTSS_BIT(8))
#define NP_RFEC         (VTSS_BIT(9))
#define AN_RATE         (0xF)
#define AN_XMIT_DISABLE (1 << 16)
#define CMPL_ACK        (1 << 13)
#define ANEG_KR_AN_GOOD (1 << 12)
#define ANEG_RATE_25G   7
#define ANEG_RATE_10G   9
static vtss_rc fa_serdes_set(vtss_state_t        *vtss_state,
                             const vtss_port_no_t port_no,
                             vtss_serdes_mode_t   serdes_mode);

u32 vtss_to_sd_kr(vtss_state_t *vtss_state, u32 p)
{
    if (p < 12 || p == 64) {
        VTSS_E("Not supported\n");
        return VTSS_RC_ERROR;
    } else {
        return vtss_to_sd10g_kr(vtss_state, p);
    }
}

static vtss_rc fa_port_kr_speed_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)

{
    u32 tgt, sts, spd = 0;

    if (!vtss_state->port.kr_conf[port_no].aneg.enable) {
        return VTSS_RC_OK;
    }
    tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));

    if (vtss_state->port.conf[port_no].speed == VTSS_SPEED_10G) {
        spd = KR_ANEG_RATE_10G;
    } else if (vtss_state->port.conf[port_no].speed == VTSS_SPEED_25G) {
        REG_RD(VTSS_IP_KRANEG_AN_STS1(tgt), &sts);
        if (VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(sts) == KR_ANEG_RATE_25G_S) {
            spd = KR_ANEG_RATE_25G_S;
        } else {
            spd = KR_ANEG_RATE_25G;
        }
    } else if (vtss_state->port.conf[port_no].speed == VTSS_SPEED_5G) {
        spd = KR_ANEG_RATE_5G;
    } else if (vtss_state->port.conf[port_no].speed == VTSS_SPEED_2500M) {
        spd = KR_ANEG_RATE_2G5;
    } else if (vtss_state->port.conf[port_no].speed == VTSS_SPEED_1G) {
        spd = KR_ANEG_RATE_1G;
    } else {
        VTSS_E("Could not set KR speed %d\n", vtss_state->port.conf[port_no].speed);
        return VTSS_RC_ERROR;
    }

    if (vtss_state->port.conf[port_no].speed == VTSS_SPEED_25G) {
        // 25G PRBS values are defined in clause 92 (25G/100G)
        REG_WRM(VTSS_IP_KRANEG_TR_CFG0(tgt),
                VTSS_F_IP_KRANEG_TR_CFG0_PRBS_SEL(0) | VTSS_F_IP_KRANEG_TR_CFG0_PRBS_SEED(0x57e),
                VTSS_M_IP_KRANEG_TR_CFG0_PRBS_SEL | VTSS_M_IP_KRANEG_TR_CFG0_PRBS_SEED);
    } else if (vtss_state->port.conf[port_no].speed == VTSS_SPEED_10G) {
        // 10G PRBS values are defined in clause 72 (10G)
        int seed = VTSS_OS_RAND() % 1024; // 1024 = 2^10;
        REG_WRM(VTSS_IP_KRANEG_TR_CFG0(tgt),
                VTSS_F_IP_KRANEG_TR_CFG0_PRBS_SEL(4) | VTSS_F_IP_KRANEG_TR_CFG0_PRBS_SEED(seed),
                VTSS_M_IP_KRANEG_TR_CFG0_PRBS_SEL | VTSS_M_IP_KRANEG_TR_CFG0_PRBS_SEED);
    }

    REG_WRM(VTSS_IP_KRANEG_AN_CFG1(tgt), VTSS_F_IP_KRANEG_AN_CFG1_RATE(spd),
            VTSS_M_IP_KRANEG_AN_CFG1_RATE);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_coef_set(vtss_state_t                   *vtss_state,
                                  const vtss_port_no_t            port_no,
                                  const u16                       coef_in,
                                  vtss_kr_status_results_t *const sts_out)
{
    u16                      s = 0;
    vtss_kr_status_results_t r = {};

    if (vtss_state->port.current_speed[port_no] != VTSS_SPEED_10G &&
        vtss_state->port.current_speed[port_no] != VTSS_SPEED_25G) {
        VTSS_E("Speed not supported for KR\n");
        return VTSS_RC_ERROR;
    }

    if (coef_in & 0xf000) { /* INIT/PRESET */
        VTSS_RC(fa_kr_coef2status(vtss_state, port_no, (coef_in & 0xf000), &r));
        s = r.status;
    } else {
        if (coef_in & 0x3) { /* CM coefficient */
            VTSS_RC(fa_kr_coef2status(vtss_state, port_no, (coef_in & 0x3), &r));
            s |= r.status;
        }
        if (coef_in & 0xc) { /* C0 coefficient */
            VTSS_RC(fa_kr_coef2status(vtss_state, port_no, (coef_in & 0xc), &r));
            s |= r.status;
        }
        if (coef_in & 0x30) { /* CP coefficient */
            VTSS_RC(fa_kr_coef2status(vtss_state, port_no, (coef_in & 0x30), &r));
            s |= r.status;
        }
    }
    r.status = s;
    *sts_out = r;
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_frame_set(vtss_state_t                     *vtss_state,
                                   const vtss_port_no_t              port_no,
                                   const vtss_port_kr_frame_t *const frm)
{
    u32 tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));

    if (frm->type == VTSS_COEFFICIENT_UPDATE_FRM) {
        REG_WR(VTSS_IP_KRANEG_LD_COEF_UPD(tgt), frm->data);
        REG_WRM(VTSS_IP_KRANEG_FW_MSG(tgt), VTSS_F_IP_KRANEG_FW_MSG_LDCOEF_VLD(1),
                VTSS_M_IP_KRANEG_FW_MSG_LDCOEF_VLD);
    } else {
        REG_WR(VTSS_IP_KRANEG_LD_STS_RPT(tgt), frm->data);
        REG_WRM(VTSS_IP_KRANEG_FW_MSG(tgt), VTSS_F_IP_KRANEG_FW_MSG_LDSTAT_VLD(1),
                VTSS_M_IP_KRANEG_FW_MSG_LDSTAT_VLD);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_frame_get(vtss_state_t               *vtss_state,
                                   const vtss_port_no_t        port_no,
                                   vtss_port_kr_frame_t *const frm)
{
    u32 tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no)), val;

    if (frm->type == VTSS_COEFFICIENT_UPDATE_FRM) {
        REG_RD(VTSS_IP_KRANEG_LP_COEF_UPD(tgt), &val);
    } else {
        REG_RD(VTSS_IP_KRANEG_LP_STS_RPT(tgt), &val);
    }

    frm->data = (u16)val;

    return VTSS_RC_OK;
}

static vtss_rc fa_np_set(vtss_state_t        *vtss_state,
                         const vtss_port_no_t port_no,
                         u32                  np0,
                         u32                  np1,
                         u32                  np2)
{
    u32 val;
    u32 tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));
    REG_RD(VTSS_IP_KRANEG_LD_NP0(tgt), &val);

    if ((val & NP_TOGGLE) == 0) {
        np0 = np0 | NP_TOGGLE;
    } else {
        np0 &= ~NP_TOGGLE;
    }
    REG_WR(VTSS_IP_KRANEG_LD_NP0(tgt), np0);
    REG_WR(VTSS_IP_KRANEG_LD_NP1(tgt), np1);
    REG_WR(VTSS_IP_KRANEG_LD_NP2(tgt), np2);

    REG_WRM(VTSS_IP_KRANEG_FW_MSG(tgt), VTSS_F_IP_KRANEG_FW_MSG_NP_LOADED(1),
            VTSS_M_IP_KRANEG_FW_MSG_NP_LOADED);
    return VTSS_RC_OK;
}

static vtss_rc fa_np_rx(vtss_state_t        *vtss_state,
                        const vtss_port_no_t port_no,
                        u32                 *np0,
                        u32                 *np1,
                        u32                 *np2)
{
    u32 tgt = vtss_to_sd_kr(vtss_state, VTSS_CHIP_PORT(port_no));

    REG_RD(VTSS_IP_KRANEG_LD_NP0(tgt), np0);
    REG_RD(VTSS_IP_KRANEG_LD_NP1(tgt), np1);
    REG_RD(VTSS_IP_KRANEG_LD_NP2(tgt), np2);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_eye_dim(vtss_state_t                 *vtss_state,
                                 const vtss_port_no_t          port_no,
                                 vtss_port_kr_eye_dim_t *const eye)
{

    eye->height = fa_eye_height_num(vtss_state, port_no, 3);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_ber_cnt(vtss_state_t        *vtss_state,
                                 const vtss_port_no_t port_no,
                                 u16 *const           ber)
{
    u32 tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));
    u32 val;
    REG_RD(VTSS_IP_KRANEG_TR_ERRCNT(tgt), &val);
    *ber = (u16)val;
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SD_25G)
static vtss_rc fa_port_kr_rsfec_radapt_set(vtss_state_t        *vtss_state,
                                           const vtss_port_no_t port_no,
                                           bool                 ena)
{
    u32 val, tgt = VTSS_TO_HIGH_DEV(VTSS_CHIP_PORT(port_no));

    REG_WR(VTSS_DEV10G_MAC_ENA_CFG(tgt), 0);

    REG_WRM(VTSS_DEV10G_PCS25G_RSFEC_CFG(tgt), VTSS_F_DEV10G_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA(ena),
            VTSS_M_DEV10G_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA);

    REG_RD(VTSS_DEV10G_DEV_STICKY(tgt), &val);
    if (VTSS_X_DEV10G_DEV_STICKY_TX_RADAPT_FIFO_UFLOW_STICKY(val) ||
        VTSS_X_DEV10G_DEV_STICKY_TX_RADAPT_FIFO_OFLOW_STICKY(val)) {
        REG_WRM(VTSS_DEV10G_USXGMII_TX_RADAPT_CFG(tgt),
                VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_FIFO_FLUSH(1),
                VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_FIFO_FLUSH);
    }

    REG_WR(VTSS_DEV10G_MAC_ENA_CFG(tgt),
           VTSS_M_DEV10G_MAC_ENA_CFG_RX_ENA | VTSS_M_DEV10G_MAC_ENA_CFG_TX_ENA);

    return VTSS_RC_OK;
}
#endif

vtss_rc vtss_cil_port_kr_fec_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    if (!PORT_IS_KR_CAP(port_no)) {
        VTSS_E("Not KR capable")
        return VTSS_RC_ERROR;
    }

    u32                 port = VTSS_CHIP_PORT(port_no);
    vtss_port_kr_fec_t *kr = &vtss_state->port.kr_fec[port_no];
    u32                 pcs = VTSS_TO_PCS_TGT(port);

    if (kr->r_fec && kr->rs_fec) {
        VTSS_E("Illegal FEC config");
        return VTSS_RC_ERROR;
    }

    // R-FEC: 10G/25G in 10G-mode
    REG_WRM(VTSS_PCS_10GBASE_R_KR_FEC_CFG(pcs),
            VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_FEC_ENA(kr->r_fec) |
                VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_TX_DATA_FLIP(kr->r_fec) |
                VTSS_F_PCS_10GBASE_R_KR_FEC_CFG_RX_DATA_FLIP(kr->r_fec),
            VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_TX_DATA_FLIP |
                VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_RX_DATA_FLIP |
                VTSS_M_PCS_10GBASE_R_KR_FEC_CFG_FEC_ENA);

    if (VTSS_PORT_IS_25G(port)) {
#if defined(VTSS_FEATURE_SD_25G)
        BOOL                 pcs_ena;
        u32                  rs_fec = vtss_to_rsfec(vtss_state, port);
        u32                  tgt = VTSS_TO_HIGH_DEV(port), val;
        vtss_port_kr_conf_t *kr_conf = &vtss_state->port.kr_conf[port_no];

        // 25G PCS must be disabled when enabling FEC
        REG_RD(VTSS_DEV10G_PCS25G_CFG(tgt), &val);
        pcs_ena = VTSS_X_DEV10G_PCS25G_CFG_PCS25G_ENA(val);

        if (pcs_ena) {
            REG_WRM_CLR(VTSS_DEV10G_PCS25G_CFG(tgt), VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
        }

        // R-FEC: 25G in 25G mode
        REG_WRM(VTSS_DEV10G_PCS25G_FEC74_CFG(tgt),
                VTSS_F_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_RX(kr->r_fec) |
                    VTSS_F_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_TX(kr->r_fec),
                VTSS_M_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_RX |
                    VTSS_M_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_TX);

        // RS-FEC: 25G in 25G mode
        REG_WRM(VTSS_PCS25G_RSFEC_VENDOR_PCS_MODE(rs_fec),
                VTSS_F_PCS25G_RSFEC_VENDOR_PCS_MODE_HI_BER25(kr->rs_fec),
                VTSS_M_PCS25G_RSFEC_VENDOR_PCS_MODE_HI_BER25);

        REG_WRM(VTSS_DEV10G_PCS25G_RSFEC_CFG(tgt),
                VTSS_F_DEV10G_PCS25G_RSFEC_CFG_FEC91_ENA(kr->rs_fec),
                VTSS_M_DEV10G_PCS25G_RSFEC_CFG_FEC91_ENA);

        REG_WRM(VTSS_DEV10G_USXGMII_TX_RADAPT_CFG(tgt),
                VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL(2) |
                    VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL(10) |
                    VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG(1) |
                    VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS(1),
                VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL |
                    VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL |
                    VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG |
                    VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS);

        // RS-FEC/RADAPT: If train, disable for now, enable later (MESA-723)
        fa_port_kr_rsfec_radapt_set(vtss_state, port_no, kr_conf->train.enable ? FALSE : TRUE);

        vtss_state->port.kr_store[port_no].rs_fec_cc = 0;
        vtss_state->port.kr_store[port_no].rs_fec_uc = 0;

        if (pcs_ena) {
            REG_WRM_SET(VTSS_DEV10G_PCS25G_CFG(tgt), VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
        }
#endif
    }

    return VTSS_RC_OK;
}

/* Restart aneg if SM is stuck (UNG_FIREANT-91) */
static vtss_rc fa_kr_state_chk(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no)), val;

    REG_RD(VTSS_IP_KRANEG_AN_SM(tgt), &val);
    if (VTSS_X_IP_KRANEG_AN_SM_AN_SM(val) == 1) {
        if (vtss_state->port.kr_store[port_no].sm_dis) {
            REG_WRM(VTSS_IP_KRANEG_AN_CFG0(tgt), VTSS_F_IP_KRANEG_AN_CFG0_AN_RESTART(1),
                    VTSS_M_IP_KRANEG_AN_CFG0_AN_RESTART);
            vtss_state->port.kr_store[port_no].sm_dis = FALSE;
        } else {
            vtss_state->port.kr_store[port_no].sm_dis = TRUE;
        }
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_irq_get(vtss_state_t        *vtss_state,
                                 const vtss_port_no_t port_no,
                                 u32 *const           irq)
{
    if (!PORT_IS_KR_CAP(port_no)) {
        VTSS_E("Not KR capable")
        return VTSS_RC_ERROR;
    }
    u32                  tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));
    vtss_port_kr_conf_t *kr = &vtss_state->port.kr_conf[port_no];
    u32                  val;
    REG_RD(VTSS_IP_KRANEG_IRQ_VEC(tgt), &val);
    if (val > 0) {

        if (val & CMPL_ACK) {
            if (kr->aneg.next_page && vtss_state->port.kr_store[port_no].base_page) {
                REG_WRM(VTSS_IP_KRANEG_LD_ADV0(tgt), VTSS_BIT(15), VTSS_BIT(15));
                // Send first next page
                fa_np_set(vtss_state, port_no, 0xe805, 0x0040, 0xc100);
            }
            vtss_state->port.kr_store[port_no].base_page = FALSE;
            vtss_state->port.kr_store[port_no].compl_ack = TRUE;
        }

        if ((val & AN_RATE) > 0) {
            // Freeze link_break timer while speed config
            REG_WRM(VTSS_IP_KRANEG_TMR_HOLD(tgt), 0x100, 0x100);
        }

        if (val & AN_XMIT_DISABLE) {
            vtss_state->port.kr_store[port_no].compl_ack = FALSE;
            vtss_state->port.kr_store[port_no].base_page = TRUE;
        }

        // Clear the IRQs
        REG_WR(VTSS_IP_KRANEG_IRQ_VEC(tgt), val);
    }
    *irq = val;

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_irq_activity(vtss_state_t *vtss_state, u32 *const irq_mask)
{
#if defined(VTSS_ARCH_SPARX5)
    REG_RD(VTSS_CPU_KR10G_INTR_RAW, irq_mask);
#else
    for (u32 p = VTSS_PORT_NO_START; p < vtss_state->port_count; p++) {
        if (!PORT_IS_KR_CAP(p)) {
            continue;
        }
        vtss_port_kr_conf_t *kr = &vtss_state->port.kr_conf[p];
        u32                  val, tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(p));
        if (!kr->aneg.enable) {
            continue;
        }
        REG_RD(VTSS_IP_KRANEG_IRQ_VEC(tgt), &val);
        if (val > 0) {
            *irq_mask |= (u32)(1 << VTSS_CHIP_PORT(p));
        }
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_event_enable(vtss_state_t        *vtss_state,
                                      const vtss_port_no_t port_no,
                                      BOOL                 enable)
{
    if (!PORT_IS_KR_CAP(port_no)) {
        VTSS_E("Not KR capable")
        return VTSS_RC_ERROR;
    }
    u32 mask = enable ? 0xFFFFFFFF : 0;
    u32 tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));
    REG_WR(VTSS_IP_KRANEG_IRQ_MASK(tgt), mask);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_status(vtss_state_t                *vtss_state,
                                const vtss_port_no_t         port_no,
                                vtss_port_kr_status_t *const status)
{
    u32                   sts0, sts1, tr;
    u16                   val1, val2, val3;
    u32                   tgt, pcs;
    BOOL                  spd10g = vtss_state->port.conf[port_no].speed == VTSS_SPEED_10G;
    vtss_port_kr_state_t *krs = &vtss_state->port.train_state[port_no];
    vtss_port_kr_conf_t  *kr = &vtss_state->port.kr_conf[port_no];
    BOOL                  spd25g = vtss_state->port.conf[port_no].speed == VTSS_SPEED_25G;
    u32                   port = VTSS_CHIP_PORT(port_no), reg;

    if (!PORT_IS_KR_CAP(port_no)) {
        VTSS_E("Not KR capable")
        return VTSS_RC_ERROR;
    }

    pcs = VTSS_TO_PCS_TGT(VTSS_CHIP_PORT(port_no));
    tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));

    REG_RD(VTSS_IP_KRANEG_AN_STS0(tgt), &sts0);
    REG_RD(VTSS_IP_KRANEG_AN_STS1(tgt), &sts1);
    status->aneg.complete = VTSS_X_IP_KRANEG_AN_STS0_AN_COMPLETE(sts0);

    if (VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(sts1) > 0) {
        if (VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(sts1) == KR_ANEG_RATE_25G ||
            VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(sts1) == KR_ANEG_RATE_25G_S) {
            status->aneg.speed_req = VTSS_SPEED_25G;
        } else if (VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(sts1) == KR_ANEG_RATE_10G) {
            status->aneg.speed_req = VTSS_SPEED_10G;
        } else if (VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(sts1) == KR_ANEG_RATE_5G) {
            status->aneg.speed_req = VTSS_SPEED_5G;
        } else if (VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(sts1) == KR_ANEG_RATE_2G5) {
            status->aneg.speed_req = VTSS_SPEED_2500M;
        } else if (VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(sts1) == KR_ANEG_RATE_1G) {
            status->aneg.speed_req = VTSS_SPEED_1G;
        } else {
            status->aneg.speed_req = VTSS_SPEED_UNDEFINED;
        }
    }

    VTSS_RC(fa_port_kr_tap_get(vtss_state, port_no, &val1, &val2, &val3));
    status->train.cp_ob_tap_result = (u8)val1;
    status->train.cm_ob_tap_result = (u8)val2;
    status->train.c0_ob_tap_result = (u8)val3;
    status->train.complete = krs->current_state == VTSS_TR_SEND_DATA;

    REG_RD(VTSS_IP_KRANEG_TR_FRSENT(tgt), &tr);
    status->train.frame_sent = tr;

    // LP base and NP pages (for debug)
    REG_RD(VTSS_IP_KRANEG_AN_SM(tgt), &tr);
    status->aneg.sm = VTSS_X_IP_KRANEG_AN_SM_AN_SM(tr);
    REG_RD(VTSS_IP_KRANEG_LP_BP0(tgt), &tr);
    status->aneg.lp_bp0 = tr;
    REG_RD(VTSS_IP_KRANEG_LP_BP1(tgt), &tr);
    status->aneg.lp_bp1 = tr;
    REG_RD(VTSS_IP_KRANEG_LP_BP2(tgt), &tr);
    status->aneg.lp_bp2 = tr;
    REG_RD(VTSS_IP_KRANEG_LP_NP0(tgt), &tr);
    status->aneg.lp_np0 = tr;
    REG_RD(VTSS_IP_KRANEG_LP_NP1(tgt), &tr);
    status->aneg.lp_np1 = tr;
    REG_RD(VTSS_IP_KRANEG_LP_NP2(tgt), &tr);
    status->aneg.lp_np2 = tr;

    // Base page FEC
    REG_RD(VTSS_IP_KRANEG_BP_ETH_STS(tgt), &tr);
    status->aneg.r_fec_enable = VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_R_FEC(tr);
    status->aneg.rs_fec_enable = VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_RS_FEC(tr);

    // Next Page FEC
    if (status->aneg.speed_req == VTSS_SPEED_25G) {
        if ((status->aneg.lp_np2 & NP_RSFEC && (kr->aneg.rs_fec_req))) {
            status->aneg.rs_fec_enable = TRUE;
            status->aneg.r_fec_enable = FALSE;
        } else if ((status->aneg.lp_np2 & NP_RFEC && (kr->aneg.r_fec_req))) {
            status->aneg.r_fec_enable = TRUE;
            status->aneg.rs_fec_enable = FALSE;
        }
    }

    // Change the FEC ?
    if ((vtss_state->port.kr_fec[port_no].r_fec != status->aneg.r_fec_enable) ||
        (vtss_state->port.kr_fec[port_no].rs_fec != status->aneg.rs_fec_enable)) {
        status->aneg.request_fec_change = TRUE;
    } else {
        status->aneg.request_fec_change = FALSE;
    }

    // Copy actual FEC config into current FEC status
    status->fec.r_fec_enable = vtss_state->port.kr_fec[port_no].r_fec;
    status->fec.rs_fec_enable = vtss_state->port.kr_fec[port_no].rs_fec;

    if (spd10g) {
        REG_RD(VTSS_PCS_10GBASE_R_KR_FEC_CORRECTED(pcs), &tr);
        status->fec.corrected_block_cnt = tr;
        REG_RD(VTSS_PCS_10GBASE_R_KR_FEC_UNCORRECTED(pcs), &tr);
        status->fec.uncorrected_block_cnt = tr;
    }

    if (spd25g) {
#if defined(VTSS_FEATURE_SD_25G)
        u32 *rs_fec_cc = &vtss_state->port.kr_store[port_no].rs_fec_cc;
        u32 *rs_fec_uc = &vtss_state->port.kr_store[port_no].rs_fec_uc;

        if (status->fec.r_fec_enable) {
            u32 dev_tgt = VTSS_TO_HIGH_DEV(port);
            REG_RD(VTSS_DEV10G_PCS25G_FEC74_CERR_CNT(dev_tgt), &reg);
            status->fec.corrected_block_cnt = reg;
            REG_RD(VTSS_DEV10G_PCS25G_FEC74_NCERR_CNT(dev_tgt), &reg);
            status->fec.uncorrected_block_cnt = reg;
        } else {
            u32 reg2, rs_fec = vtss_to_rsfec(vtss_state, port);
            REG_RD(VTSS_PCS25G_RSFEC_RS_FEC_CCW_LO(rs_fec), &reg);
            REG_RD(VTSS_PCS25G_RSFEC_RS_FEC_CCW_HI(rs_fec),
                   &reg2); // Clear on read
            *rs_fec_cc += (reg2 << 16) | reg;
            status->fec.corrected_block_cnt = *rs_fec_cc;
            REG_RD(VTSS_PCS25G_RSFEC_RS_FEC_NCCW_LO(rs_fec), &reg);
            REG_RD(VTSS_PCS25G_RSFEC_RS_FEC_NCCW_HI(rs_fec),
                   &reg2); // Clear on read
            *rs_fec_uc += (reg2 << 16) | reg;
            status->fec.uncorrected_block_cnt = *rs_fec_uc;
        }
#endif
    }

    // Debug
    REG_RD(VTSS_IP_KRANEG_AN_SM(tgt), &tr);
    status->aneg.sm = VTSS_X_IP_KRANEG_AN_SM_AN_SM(tr);
    REG_RD(VTSS_IP_KRANEG_LP_BP0(tgt), &tr);
    status->aneg.lp_bp0 = tr;
    REG_RD(VTSS_IP_KRANEG_LP_BP1(tgt), &tr);
    status->aneg.lp_bp1 = tr;
    REG_RD(VTSS_IP_KRANEG_LP_BP2(tgt), &tr);
    status->aneg.lp_bp2 = tr;

    REG_RD(VTSS_IP_KRANEG_AN_HIST(tgt), &tr);
    status->aneg.hist = VTSS_X_IP_KRANEG_AN_HIST_AN_SM_HIST(tr);
    // Clear aneg history
    if (status->aneg.sm == 1) {
        REG_WRM(VTSS_IP_KRANEG_AN_CFG1(tgt), VTSS_F_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR(1),
                VTSS_M_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR);

        REG_WRM(VTSS_IP_KRANEG_AN_CFG1(tgt), VTSS_F_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR(0),
                VTSS_M_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR);
    }

    if (spd25g) {
        u32 tgt = vtss_fa_dev_tgt(vtss_state, port_no);
        REG_RD(VTSS_DEV10G_PCS25G_STATUS(tgt), &reg);
        if (status->fec.rs_fec_enable) {
            status->aneg.block_lock = VTSS_X_DEV10G_PCS25G_STATUS_ALIGN_DONE(reg);
        } else {
            status->aneg.block_lock = VTSS_X_DEV10G_PCS25G_STATUS_BLOCK_LOCK(reg);
        }
    } else {
        REG_RD(VTSS_PCS_10GBASE_R_PCS_STATUS(VTSS_TO_PCS_TGT(port)), &reg);
        status->aneg.block_lock = reg == 8 ? 1 : 0;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    if (!PORT_IS_KR_CAP(port_no)) {
        VTSS_E("Not KR capable")
        return VTSS_RC_ERROR;
    }
    vtss_port_kr_conf_t *kr = &vtss_state->port.kr_conf[port_no];
    u32                  abil = 0;
    u32                  tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));
    u32                  indx = vtss_fa_sd_lane_indx(vtss_state, port_no);

    // Reset the serdes
    VTSS_RC(fa_serdes_set(vtss_state, port_no, vtss_state->port.sd28_mode[indx]));

    // Reset aneg, training and IRQs
    REG_WRM(VTSS_IP_KRANEG_AN_CFG0(tgt), VTSS_F_IP_KRANEG_AN_CFG0_AN_ENABLE(0),
            VTSS_M_IP_KRANEG_AN_CFG0_AN_ENABLE);

    REG_WR(VTSS_IP_KRANEG_IRQ_MASK(tgt), kr->aneg.enable ? 0xFFFFFFFF : 0);
    REG_WR(VTSS_IP_KRANEG_IRQ_VEC(tgt), 0xFFFFFFFF);

    REG_WRM(VTSS_IP_KRANEG_KR_PMD_STS(tgt), VTSS_F_IP_KRANEG_KR_PMD_STS_STPROT(0),
            VTSS_M_IP_KRANEG_KR_PMD_STS_STPROT);

    REG_WRM(VTSS_IP_KRANEG_KR_PMD_CTRL(tgt), VTSS_F_IP_KRANEG_KR_PMD_CTRL_TR_ENABLE(0),
            VTSS_M_IP_KRANEG_KR_PMD_CTRL_TR_ENABLE);

    /* AN Selector */
    REG_WR(VTSS_IP_KRANEG_LD_ADV0(tgt), VTSS_F_IP_KRANEG_LD_ADV0_ADV0(kr->aneg.enable));

    if (kr->aneg.enable) {
        /* Reg LD_ADV1.
           AN Technology aneg field bit
           LD_ADV1 bit 5  = 1000Base-KX,
           LD_ADV1 bit 7  = 10GBase-KR
           LD_ADV1 bit 14 = 25GBase-KR-S
           LD_ADV1 bit 15 = 25GBase-KR */
        abil = kr->aneg.adv_1g ? VTSS_BIT(5) : 0;
        abil |= kr->aneg.adv_10g ? VTSS_BIT(7) : 0;
        abil |= kr->aneg.adv_25g ? VTSS_BIT(14) : 0;
        abil |= kr->aneg.adv_25g ? VTSS_BIT(15) : 0;
        REG_WRM(VTSS_IP_KRANEG_LD_ADV1(tgt), abil,
                VTSS_BIT(5) | VTSS_BIT(7) | VTSS_BIT(14) | VTSS_BIT(15));

        /* AN Technology aneg field bit
           LD_ADV2 bit 0 = 2.5G-KX,
           LD_ADV2 bit 1 = 5G-KR */
        abil = kr->aneg.adv_2g5 ? VTSS_BIT(0) : 0;
        abil |= kr->aneg.adv_5g ? VTSS_BIT(1) : 0;
        REG_WRM(VTSS_IP_KRANEG_LD_ADV2(tgt), abil, VTSS_BIT(0) | VTSS_BIT(1));

        /* AN FEC aneg field
           LD_ADV2 bit 14/F0 = fec ability
           LD_ADV2 bit 15/F1 = R-FEC requested */
        abil = VTSS_BIT(14); // FEC support
        if (VTSS_PORT_IS_25G(VTSS_CHIP_PORT(port_no)) &&
            (kr->aneg.r_fec_req || kr->aneg.rs_fec_req)) {
            /* LD_ADV2 bit 12/F2 = RS-FEC requested      */
            /* LD_ADV2 bit 13/F3 = Base-R FEC requested, */
            abil |= kr->aneg.rs_fec_req ? VTSS_BIT(12) : 0; // F2
            abil |= kr->aneg.r_fec_req ? VTSS_BIT(13) : 0;  // F3
            abil |= VTSS_BIT(15);                           // FEC requested
        } else if (kr->aneg.r_fec_req) {
            abil |= VTSS_BIT(13); // F3
            abil |= VTSS_BIT(15); // FEC requested
        }
        REG_WRM(VTSS_IP_KRANEG_LD_ADV2(tgt), abil,
                VTSS_BIT(12) | VTSS_BIT(13) | VTSS_BIT(14) | VTSS_BIT(15));
    }

    // Enable/disable training
    REG_WRM(VTSS_IP_KRANEG_AN_CFG1(tgt), VTSS_F_IP_KRANEG_AN_CFG1_TR_DISABLE(!kr->train.enable),
            VTSS_M_IP_KRANEG_AN_CFG1_TR_DISABLE);

    // Clear aneg history
    REG_WRM(VTSS_IP_KRANEG_AN_CFG1(tgt), VTSS_F_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR(1),
            VTSS_M_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR);

    REG_WRM(VTSS_IP_KRANEG_AN_CFG1(tgt), VTSS_F_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR(0),
            VTSS_M_IP_KRANEG_AN_CFG1_AN_SM_HIST_CLR);

    // Disable Auto-neg
    REG_WRM(VTSS_IP_KRANEG_AN_CFG0(tgt), VTSS_F_IP_KRANEG_AN_CFG0_AN_ENABLE(0),
            VTSS_M_IP_KRANEG_AN_CFG0_AN_ENABLE);

    if (kr->aneg.enable) {
        REG_WRM(VTSS_IP_KRANEG_AN_CFG0(tgt), VTSS_F_IP_KRANEG_AN_CFG0_AN_ENABLE(1),
                VTSS_M_IP_KRANEG_AN_CFG0_AN_ENABLE);
        // Restart Auto-neg
        REG_WRM(VTSS_IP_KRANEG_AN_CFG0(tgt), VTSS_F_IP_KRANEG_AN_CFG0_AN_RESTART(1),
                VTSS_M_IP_KRANEG_AN_CFG0_AN_RESTART);
    }
    // Number of frames for BER calculation
    REG_WRM(VTSS_IP_KRANEG_FRCNT_BER(tgt), VTSS_F_IP_KRANEG_FRCNT_BER_FRCNT_BER(100),
            VTSS_M_IP_KRANEG_FRCNT_BER_FRCNT_BER);

    // Disable / Enable training
    REG_WRM(VTSS_IP_KRANEG_KR_PMD_CTRL(tgt),
            VTSS_F_IP_KRANEG_KR_PMD_CTRL_TR_ENABLE(kr->train.enable),
            VTSS_M_IP_KRANEG_KR_PMD_CTRL_TR_ENABLE);

    REG_WRM(VTSS_IP_KRANEG_KR_PMD_STS(tgt), VTSS_F_IP_KRANEG_KR_PMD_STS_TR_FAIL(0),
            VTSS_M_IP_KRANEG_KR_PMD_STS_TR_FAIL);

    // Freeze page detect timer
    REG_WRM(VTSS_IP_KRANEG_TMR_HOLD(tgt), kr->aneg.no_pd ? 0x10 : 0, 0x10);

    // Generic timer 0
    REG_WR(VTSS_IP_KRANEG_GEN0_TMR(tgt), 0x04a817c8); // 500 ms

    if (kr->train.enable) {
        // Link PASS inihibit timer (LP_TMR) in AN_GOOD_CHECK: 10ms
        // Link FAIL inihibit timer (LF_TMR) in AN_GOOD_CHECK: 50ms (default)
        REG_WR(VTSS_IP_KRANEG_LP_TMR(tgt), 1562500); // 10 ms
    } else {
        // Link pass inihibit timer (in AN_GOOD_CHECK)
        REG_WR(VTSS_IP_KRANEG_LP_TMR(tgt), 1562500 * 3); // 3 * 10ms
#if defined(VTSS_ARCH_LAN969X)
        // FA: LFLONG_TMR (default 50ms) is enough)
        // Link fail inihibit timer (in AN_GOOD_CHECK)
        REG_WR(VTSS_IP_KRANEG_LF_TMR(tgt), 4101049 * 3); // 3 * 50ms
#endif
    }

    // Store the cuurnet TxEq values
    vtss_port_kr_temp_storage_t *st = &vtss_state->port.kr_store[port_no];
    VTSS_RC(fa_port_kr_tap_get(vtss_state, port_no, &st->tap_dly, &st->tap_adv, &st->amplitude));

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_kr_fw_req(vtss_state_t                *vtss_state,
                                const vtss_port_no_t         port_no,
                                vtss_port_kr_fw_req_t *const fw_req)

{
    u32                  tgt = vtss_to_sd10g_kr(vtss_state, VTSS_CHIP_PORT(port_no));
    vtss_port_kr_conf_t *kr = &vtss_state->port.kr_conf[port_no];

    if (fw_req->transmit_disable && (fw_req->stop_training || fw_req->start_training)) {
        u32 indx = vtss_fa_sd_lane_indx(vtss_state, port_no);
        /* Training is interruptet, restart serdes and kr blocks */
        vtss_state->port.kr_conf[port_no].aneg.enable = FALSE;
        vtss_state->port.kr_conf[port_no].train.enable = FALSE;
        vtss_cil_port_kr_conf_set(vtss_state, port_no);
        VTSS_RC(fa_serdes_set(vtss_state, port_no, vtss_state->port.sd28_mode[indx]));
        vtss_state->port.kr_conf[port_no].aneg.enable = TRUE;
        vtss_state->port.kr_conf[port_no].train.enable = TRUE;
        vtss_cil_port_kr_conf_set(vtss_state, port_no);
        return VTSS_RC_OK;
    }

    if (fw_req->wt_start) {
        if (vtss_state->port.current_speed[port_no] == VTSS_SPEED_25G) {
            REG_WR(VTSS_IP_KRANEG_WT_TMR(tgt), 5312); /* 200 frames @ 25G */
        } else {
            REG_WR(VTSS_IP_KRANEG_WT_TMR(tgt), 13280); /* 200 frames @ 10G */
        }
    }

    if (fw_req->ber_enable || fw_req->mw_start || fw_req->wt_start || fw_req->gen0_tmr_start ||
        fw_req->gen1_tmr_start) {
        REG_WRM(VTSS_IP_KRANEG_FW_REQ(tgt),
                VTSS_F_IP_KRANEG_FW_REQ_BER_EN(fw_req->ber_enable) |
                    VTSS_F_IP_KRANEG_FW_REQ_MW_START(fw_req->mw_start) |
                    VTSS_F_IP_KRANEG_FW_REQ_WT_START(fw_req->wt_start) |
                    VTSS_F_IP_KRANEG_FW_REQ_GEN0_TMR_START(fw_req->gen0_tmr_start) |
                    VTSS_F_IP_KRANEG_FW_REQ_GEN1_TMR_START(fw_req->gen1_tmr_start),
                VTSS_M_IP_KRANEG_FW_REQ_BER_EN | VTSS_M_IP_KRANEG_FW_REQ_MW_START |
                    VTSS_M_IP_KRANEG_FW_REQ_WT_START | VTSS_M_IP_KRANEG_FW_REQ_GEN0_TMR_START |
                    VTSS_M_IP_KRANEG_FW_REQ_GEN1_TMR_START);
    }

    if (fw_req->rate_done || fw_req->tr_done) {
        REG_WRM(VTSS_IP_KRANEG_FW_MSG(tgt),
                VTSS_F_IP_KRANEG_FW_MSG_RATE_DONE(fw_req->rate_done) |
                    VTSS_F_IP_KRANEG_FW_MSG_TR_DONE(fw_req->tr_done),
                VTSS_M_IP_KRANEG_FW_MSG_RATE_DONE | VTSS_M_IP_KRANEG_FW_MSG_TR_DONE);

        if (fw_req->rate_done) {
            // Release link_break timer after speed config
            REG_WRM(VTSS_IP_KRANEG_TMR_HOLD(tgt), 0, 0x100);
        }
    }

    if (fw_req->start_training) {
        // Change to 64 bit KR mode while training is done by the application
        // through Rate Sel IRQ
        REG_WRM(VTSS_IP_KRANEG_KR_PMD_STS(tgt), VTSS_F_IP_KRANEG_KR_PMD_STS_STPROT(1),
                VTSS_M_IP_KRANEG_KR_PMD_STS_STPROT);
    }

    if (fw_req->stop_training) {
        u32 pcs = vtss_fa_dev_tgt(vtss_state, port_no);

        if (vtss_state->port.current_speed[port_no] == VTSS_SPEED_25G) {
            // Make sure that link is down when AN_GOOD_CHECK is entered by
            // disabling the PCS. This will force LP to obey 73.10.2
            // link_fail_inhibit_timer which gives us time to change to 40bit mode
            REG_WRM_CLR(VTSS_DEV10G_PCS25G_CFG(pcs), VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
            if (kr->train.pcs_flap) {
                VTSS_MSLEEP(5);
            }
        }

        REG_WRM(VTSS_IP_KRANEG_KR_PMD_STS(tgt), VTSS_F_IP_KRANEG_KR_PMD_STS_STPROT(0),
                VTSS_M_IP_KRANEG_KR_PMD_STS_STPROT);

        if (vtss_state->port.current_speed[port_no] == VTSS_SPEED_25G) {
#if defined(VTSS_FEATURE_SD_25G)
            // Change back to 25G 40bit data mode
            VTSS_RC(fa_serdes_40b_mode(vtss_state, port_no));

            VTSS_RC(fa_port_kr_rsfec_radapt_set(vtss_state, port_no,
                                                vtss_state->port.kr_fec[port_no].rs_fec));

            REG_WRM_SET(VTSS_DEV10G_PCS25G_CFG(pcs), VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
#endif
        }
    }

    if (fw_req->training_failure) {
        REG_WRM(VTSS_IP_KRANEG_KR_PMD_STS(tgt),
                VTSS_F_IP_KRANEG_KR_PMD_STS_STPROT(0) | VTSS_F_IP_KRANEG_KR_PMD_STS_TR_FAIL(1),
                VTSS_M_IP_KRANEG_KR_PMD_STS_STPROT | VTSS_M_IP_KRANEG_KR_PMD_STS_TR_FAIL);
    }

    if (fw_req->aneg_disable) {
        REG_WRM(VTSS_IP_KRANEG_AN_CFG0(tgt), VTSS_F_IP_KRANEG_AN_CFG0_AN_ENABLE(0),
                VTSS_M_IP_KRANEG_AN_CFG0_AN_ENABLE);
    }

    if (fw_req->next_page) {
        u32                  np0, np1, np2, fec;
        vtss_port_kr_conf_t *kr = &vtss_state->port.kr_conf[port_no];

        // 1. Send NP with message code 5 (OUI of the 25G/50G Ethernet
        // Consortium)
        // 2. Send NP with message code 3 (Capabilities)
        fa_np_rx(vtss_state, port_no, &np0, &np1, &np2);
        if ((np0 & 0xf) == 0 && (np0 & 0xf) != 5) {
            fa_np_set(vtss_state, port_no, 0xe805, 0x0353, 0x04df); /* msg code #5 + OUI (DS1217) */
        } else {
            if (kr->aneg.rs_fec_req) {
                fec = VTSS_BIT(8) | VTSS_BIT(9); /* RFEC | RSFEC */
            } else if (kr->aneg.r_fec_req) {
                fec = VTSS_BIT(8); /* RFEC */
            } else {
                fec = 0; /* No FECx */
            }
            fa_np_set(vtss_state, port_no, 0x4203, 0x0030, fec); /* 25G-KR/25G-CR/FEC cap. */
        }
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_PORT_KR_IRQ */

/* ================================================================= *
 *  Switch port functions
 * ================================================================= */

vtss_rc vtss_cil_port_conf_get(vtss_state_t           *vtss_state,
                               const vtss_port_no_t    port_no,
                               vtss_port_conf_t *const conf)
{
    return VTSS_RC_OK;
}

/* #define QLIM_WM(fraction) \ */
/*     ((RT_BUFFER_MEMORY/FA_BUFFER_CELL_SZ-100) * fraction / 100) */

static vtss_rc fa_port_buf_qlim_set(vtss_state_t *vtss_state)
{
    u32 res, dp, prio;

    // QLIM WM setup from MOT 15/8/2019:
    // Set legacy share levels to max for src_mem and src_ref
    for (res = 0; res < 2; res++) {
        for (prio = 0; prio < 8; prio++) {
            REG_WR(VTSS_QRES_RES_CFG(prio + RT_RES_CFG_MAX_PRIO_IDX + res * 1024),
                   VTSS_M_QRES_RES_CFG_WM_HIGH);
        }
        for (dp = 0; dp < 4; dp++) {
            REG_WR(VTSS_QRES_RES_CFG(dp + RT_RES_CFG_MAX_COLOUR_IDX + res * 1024),
                   VTSS_M_QRES_RES_CFG_WM_HIGH);
        }
    }

#if defined(VTSS_FEATURE_QOS_OT)
    if (!vtss_state->vtss_features[FEATURE_QOS_OT])
#endif
    {
        // Apply 100% to share 0
        if (fa_share_config(vtss_state, 0, 100) != VTSS_RC_OK) {
            VTSS_E("Could not setup WMs");
        }
    }

    return VTSS_RC_OK;
}

#if VTSS_OPT_DEBUG_PRINT
static vtss_rc fa_debug_wm_qlim(vtss_state_t                  *vtss_state,
                                lmu_ss_t                      *ss,
                                const vtss_debug_info_t *const info)
{
    u32 value, val1, val2, q, shr_id, qinf, srcport, dstport, prio, port_no, ports[100] = {0},
                                                                             killed, qsz;
    // FA_CORE_QUEUE_CNT = 40460; // 70 ports * 8 prio * 72 scheduling elements
    // + 2 * 70 (superprio)

    pr("\nQueue limitation check/status\n");
    pr("----------------------------\n");

    for (shr_id = 0; shr_id < 1; shr_id++) {
        pr("\nCurrent consumption tracked (share %d):\n", shr_id);
        REG_RD(VTSS_XQS_QLIMIT_SHR_FILL_STAT(shr_id), &value);
        pr("Current fill level...................: %5u (%d bytes)\n", value,
           value * FA_BUFFER_CELL_SZ);
        REG_RD(VTSS_XQS_QLIMIT_CONG_CNT_STAT(shr_id), &value);
        pr("Current congested SE count...........: %5u\n\n", value);
        pr("\nMaximum consumption tracked (share %d):\n", shr_id);
        REG_RD(VTSS_XQS_QLIMIT_SHR_FILL_MAX_STAT(shr_id), &value);
        pr("Highest fill level...................: %5u (%d bytes)\n", value,
           value * FA_BUFFER_CELL_SZ);
        REG_RD(VTSS_XQS_QLIMIT_CONG_CNT_MAX_STAT(shr_id), &value);
        pr("Highest congested SE count...........: %5u\n\n", value);

        REG_WR(VTSS_XQS_QLIMIT_SHR_FILL_MAX_STAT(shr_id), 0);
        REG_WR(VTSS_XQS_QLIMIT_CONG_CNT_MAX_STAT(shr_id), 0);
    }

    pr("                    %5u        %5u\n", 0, 1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_TOP_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_TOP_CFG(1), &val2);
    pr("QLIMIT_SHR_TOP      %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SHR_ATOP_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_ATOP_CFG(1), &val2);
    pr("QLIMIT_SHR_ATOP     %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SHR_CTOP_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_CTOP_CFG(1), &val2);
    pr("QLIMIT_SHR_CTOP     %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SHR_QLIM_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_QLIM_CFG(1), &val2);
    pr("QLIMIT_SHR_QLIM     %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SHR_QDIV_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_QDIV_CFG(1), &val2);
    pr("QLIMIT_SHR_QDIV     %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_QUE_CONG_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_QUE_CONG_CFG(1), &val2);
    pr("QLIMIT_QUE_CONG     %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SE_CONG_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SE_CONG_CFG(1), &val2);
    pr("QLIMIT_SE_CONG      %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SHR_QDIVMAX_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_QDIVMAX_CFG(1), &val2);
    pr("QLIMIT_SHR_QDIVMAX  %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SE_EIR_CFG(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SE_EIR_CFG(1), &val2);
    pr("QLIMIT_SE_EIR       %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_CONG_CNT_STAT(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_CONG_CNT_STAT(1), &val2);
    pr("QLIMIT_CONG_CNT     %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SHR_FILL_STAT(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_FILL_STAT(1), &val2);
    pr("QLIMIT_SHR_FILL     %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SHR_WM_STAT(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_WM_STAT(1), &val2);
    pr("QLIMIT_SHR_WM       %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_CONG_CNT_MAX_STAT(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_CONG_CNT_MAX_STAT(1), &val2);
    pr("QLIMIT_CONG_CNT_MAX %5u        %5u\n", val1, val2);
    REG_RD(VTSS_XQS_QLIMIT_SHR_FILL_MAX_STAT(0), &val1);
    REG_RD(VTSS_XQS_QLIMIT_SHR_FILL_MAX_STAT(1), &val2);
    pr("QLIMIT_SHR_FILL_MAX %5u        %5u\n", val1, val2);

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        ports[VTSS_CHIP_PORT(port_no)] = 1;
    }
    for (port_no = RT_CHIP_PORT_CPU; port_no < RT_CHIP_PORTS_ALL; port_no++) {
        ports[port_no] = 1;
    }

    pr("\nQueues hit by queue limitation:\n");
    for (q = 0; q < RT_CORE_QUEUE_CNT; q++) {
        if (FA_TGT) {
            if (q < 0x8c00) { // 70 * 512
                // Src < 64
                srcport = q & 0x3F;
                prio = (q >> 6) & 0x7;
                dstport = q >> 9;
            } else {
                // Src > 63
                srcport = (q & 0x7) + 64;
                prio = (q >> 3) & 0x7;
                dstport = (q - 0x8c00) >> 6;
            }
        } else {
            srcport = q % 32;
            prio = (q / 32) % 8;
            dstport = (q / 256);
        }
        if (!ports[srcport] || !ports[dstport]) {
            continue;
        }
        REG_WR(VTSS_XQS_MAP_CFG_CFG, q);
        REG_RD(VTSS_XQS_QUEUE_SIZE(0), &qinf);
        killed = VTSS_X_XQS_QUEUE_SIZE_QUEUE_KILLED(qinf);
        qsz = VTSS_X_XQS_QUEUE_SIZE_QUEUE_SIZE(qinf);

        if (killed || qsz) {
            pr("Qu indx:%5d Src-chip-port:%2d Dst-chip-port:%2d prio:%d. Killed:%1u CurSize:%5u (%d bytes)\n",
               q, srcport, dstport, prio, killed, qsz, qsz * FA_BUFFER_CELL_SZ);
            REG_WR(VTSS_XQS_QUEUE_SIZE(0), 0);
        }
    }

    return VTSS_RC_OK;
}
#endif

/* Source: ffl_sqs.tcl in verification */
static u32 port_fwd_urg(vtss_state_t *vtss_state, vtss_port_speed_t speed)
{
    u32 clk_period_ps = vtss_fa_clk_period(vtss_state->init_conf.core_clock.freq);
    u32 urg = 672000;

    switch (speed) {
    case VTSS_SPEED_10M:
    case VTSS_SPEED_100M:
    case VTSS_SPEED_1G:    urg = 672000; break;
    case VTSS_SPEED_2500M: urg = 270000; break;
    case VTSS_SPEED_5G:    urg = 135000; break;
    case VTSS_SPEED_10G:   urg = 67200; break;
    case VTSS_SPEED_25G:   urg = 27000; break;
    default:               {
        VTSS_E("Speed not supported");
    }
    }
    return urg / clk_period_ps - 1;
}

static BOOL fa_vrfy_spd_iface(vtss_state_t         *vtss_state,
                              vtss_port_no_t        port_no,
                              vtss_port_interface_t if_type,
                              vtss_port_speed_t     speed,
                              BOOL                  fdx)
{
    u32 port = VTSS_CHIP_PORT(port_no);

    if ((VTSS_PORT_IS_2G5(port) && (speed > VTSS_SPEED_2500M)) ||
        (VTSS_PORT_IS_5G(port) && (speed > VTSS_SPEED_5G)) ||
        (VTSS_PORT_IS_10G(port) && (speed > VTSS_SPEED_10G))) {
        VTSS_E("Port %d (dev%s) does not support speed '%s'", port,
               VTSS_PORT_IS_10G(port)  ? "10G"
               : VTSS_PORT_IS_5G(port) ? "5G"
                                       : "2G5",
               vtss_port_spd_txt(speed));
        return FALSE;
    }

    switch (if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION: return FALSE;

    case VTSS_PORT_INTERFACE_SERDES:
        if ((speed != VTSS_SPEED_1G && speed != VTSS_SPEED_2500M) || !fdx) {
            VTSS_E(
                "Illegal if, speed or duplex. Serdes port interface supports 1G/2G5/fdx (port:%u speed:%d fdx:%d)",
                port, speed, fdx);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_USGMII: /* USGMII: 8x2G5 devices. Mode 'X'  Use 2G5
                                        device. */
        VTSS_E("port %d USGMII not supported yet", port);
        return FALSE;
    case VTSS_PORT_INTERFACE_QSGMII:
        if (port > 47) {
            VTSS_E("port %d does not support QSGMII", port);
            return FALSE;
        }
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M &&
            speed != VTSS_SPEED_2500M) {
            VTSS_E("QSGMII/USGMII port interface only supports 10/100/1000M/2.5G speeds (port:%u)",
                   port);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_RGMII:
    case VTSS_PORT_INTERFACE_RGMII_ID:
    case VTSS_PORT_INTERFACE_RGMII_RXID:
    case VTSS_PORT_INTERFACE_RGMII_TXID:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M &&
            speed != VTSS_SPEED_2500M) {
            VTSS_E("SGMII port interface only supports 10/100/1000M/2.5G speeds (port:%u)", port);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_100FX:
        if (speed != VTSS_SPEED_100M || VTSS_PORT_IS_2G5(port) || !fdx) {
            VTSS_E("Illegal if, speed or duplex (port:%u speed:%d if:100FX fdx:%d)", port, speed,
                   fdx);
            return FALSE;
        }
        u32 sd_indx, sd_type;
        (void)vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type);
        if (sd_type == FA_SERDES_TYPE_25G) {
            VTSS_E("Port:%d is connected to a 25G Serdes which does not support 100fx", port);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_SFI:
        if ((speed != VTSS_SPEED_5G && speed != VTSS_SPEED_10G && speed != VTSS_SPEED_25G) ||
            !fdx) {
            VTSS_E("SFI port interface only supports 5G/10G/25G/fdx (port:%u speed:%d fdx:%d)",
                   port, speed, fdx);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        if (speed != VTSS_SPEED_2500M || !fdx) {
            VTSS_E("VAUI port interface only supports 2.5G/fdx speed (port:%u speed:%d fdx:%d)",
                   port, speed, fdx);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_USXGMII:
        if (FA_TGT) {
            VTSS_E("port %d USXGMII not supported", port);
            return FALSE;
        } else {
            return TRUE;
        }
    case VTSS_PORT_INTERFACE_DXGMII_5G: /* DXGMII_5G: 2x2G5 devices. Mode 'F'.
                                           Use 2G5 device. */
        VTSS_E("port %d not DXGMII_5G supported yet", port);
        return FALSE;
    case VTSS_PORT_INTERFACE_QXGMII: /* QXGMII:    4x2G5 devices. Mode 'R'. Use
                                        2G5 device. */
        if (port > 64 || LK_TGT) {
            VTSS_E("port %d does not support QXGMII", port);
            return FALSE;
        }
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M &&
            speed != VTSS_SPEED_2500M) {
            VTSS_E("SXGMII/DXGMII_5G port interface supports speeds 10M-2G5 (port:%u speed:%d)",
                   port, speed);
            return FALSE;
        }
        if (!fdx) {
            VTSS_E("QXGMII port only supports full duplex (port:%u speed:%d)", port, speed);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: /* DXGMII_10G: 2x5G devices.  Mode 'U'.
                                            Use primary device.*/
        VTSS_E("port %d DXGMII_10G not supported yet", port);
        return FALSE;
        if (port <= 63 && (port <= 15 || port >= 48)) {
            if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M &&
                speed != VTSS_SPEED_2500M && speed != VTSS_SPEED_5G) {
                VTSS_E("DXGMII_10G port interface supports speeds 10M-5G (port:%u speed:%d)", port,
                       speed);
                return FALSE;
            }
            if (!fdx) {
                VTSS_E("SXGMII/DXGMII_5G port only supports full duplex (port:%u speed:%d)", port,
                       speed);
                return FALSE;
            }
        } else {
            VTSS_E("port %d does not support DSGMII_10G", port);
            return FALSE;
        }
        break;
    default: VTSS_E("Illegal interface type (%d)", if_type); return FALSE;
    }
    return TRUE;
}

static vtss_rc fa_enable_usx_extender(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    if (vtss_state->port.conf[port_no].if_type != VTSS_PORT_INTERFACE_QXGMII ||
        vtss_state->port.current_if_type[port_no] == VTSS_PORT_INTERFACE_QXGMII) {
        return VTSS_RC_OK; // Already configured
    }
    u32 p = VTSS_CHIP_PORT(port_no), R, port, tgt, cnt;

    /* Enable the USXGMII extender after the last port is configured */
    if (p > 47 && p < 64) {
        R = (p < 16) ? p : (p < 32) ? p - 16 : (p < 48) ? p - 32 : p - 48;
        R = R + 16;
        REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(R),
                VTSS_F_PORT_CONF_USXGMII_CFG_TX_ENA(1) | VTSS_F_PORT_CONF_USXGMII_CFG_RX_ENA(1) |
                    VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(2),
                VTSS_M_PORT_CONF_USXGMII_CFG_TX_ENA | VTSS_M_PORT_CONF_USXGMII_CFG_RX_ENA |
                    VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);

        REG_WRM(VTSS_PORT_CONF_USXGMII_ENA, VTSS_BIT(R), VTSS_BIT(R));
        VTSS_MSLEEP(3);

        /* The usx channel is ready, restart aneg for all 4 ports in the group */
        for (cnt = 0; cnt < 4; cnt++) {
            port = p - (16 * cnt);
            tgt = VTSS_TO_DEV2G5(port);

#if !defined(VTSS_ARCH_LAIKA)
            REG_WRM(VTSS_DEV1G_USXGMII_ANEG_CFG(tgt),
                    VTSS_F_DEV1G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1),
                    VTSS_M_DEV1G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT);
#else
            (void)tgt;
#endif
        }
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_ARCH_SPARX5)
// Configure port muxing:
// QSGMII:     4x2G5 devices
// USGMII:     8x2G5 devices.
// QXGMII:     4x2G5 devices.
// DXGMII_5G:  2x2G5 devices
// DXGMII_10G: 2x5G  devices.
// USXGMII:    1x10G devices
static vtss_rc fa_port_mux_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 p = VTSS_CHIP_PORT(port_no), Q, X, U, F, S, mask;

    if (vtss_state->port.current_if_type[port_no] == vtss_state->port.conf[port_no].if_type) {
        return VTSS_RC_OK; // Nothing to do
    }

    switch (vtss_state->port.conf[port_no].if_type) {
    case VTSS_PORT_INTERFACE_QSGMII: /* QSGMII: 4x2G5 devices. Mode Q'  */
        Q = (p - p % 4) / 4;
        REG_WRM(VTSS_PORT_CONF_QSGMII_ENA, VTSS_BIT(Q), VTSS_BIT(Q));

        if ((p / 4 % 2) == 0) {
            /* Affects d0-d3,d8-d11..d40-d43 */
            REG_WRM(VTSS_PORT_CONF_USGMII_CFG((p / 8)),
                    VTSS_F_PORT_CONF_USGMII_CFG_BYPASS_SCRAM(1) |
                        VTSS_F_PORT_CONF_USGMII_CFG_BYPASS_DESCRAM(1) |
                        VTSS_F_PORT_CONF_USGMII_CFG_QUAD_MODE(1),
                    VTSS_M_PORT_CONF_USGMII_CFG_BYPASS_SCRAM |
                        VTSS_M_PORT_CONF_USGMII_CFG_BYPASS_DESCRAM |
                        VTSS_M_PORT_CONF_USGMII_CFG_QUAD_MODE);
        }
        break;
    case VTSS_PORT_INTERFACE_USGMII: /* USGMII: 8x2G5 devices. Mode 'X'  Use 2G5
                                        device. */
        X = (p - p % 8) / 8;
        REG_WRM(VTSS_PORT_CONF_USGMII_ENA, VTSS_BIT(X), VTSS_BIT(X));
        break;
    case VTSS_PORT_INTERFACE_QXGMII: /* QXGMII:    4x2G5 devices. Mode 'R'. Use
                                        2G5 device. */
        if (VTSS_PORT_IS_5G(p)) {
            mask = VTSS_BIT(fla_port_dev_index(vtss_state, p, TRUE));
            REG_WRM(VTSS_PORT_CONF_DEV5G_MODES, mask, mask);
        } else if (VTSS_PORT_IS_10G(p)) {
            mask = VTSS_BIT(fla_port_dev_index(vtss_state, p, TRUE));
            REG_WRM(VTSS_PORT_CONF_DEV10G_MODES, mask, mask);
        } else if (VTSS_PORT_IS_25G(p)) {
            mask = VTSS_BIT(fla_port_dev_index(vtss_state, p, TRUE));
            REG_WRM(VTSS_PORT_CONF_DEV25G_MODES, mask, mask);
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_5G: /* DXGMII_5G: 2x2G5 devices. Mode 'F'.
                                           Use 2G5 device. */
        F = (p - p % 8) / 8;
        REG_WRM(VTSS_PORT_CONF_USGMII_ENA, VTSS_BIT(F), VTSS_BIT(F));
        REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(F), VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(1),
                VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: /* DXGMII_10G: 2x5G devices.  Mode 'U'.
                                            Use primary device.*/
        U = (p < 16) ? p : p - 48;
        REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(U), VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(1),
                VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);
        U = U + 16;
        REG_WRM(VTSS_PORT_CONF_USGMII_ENA, VTSS_BIT(U), VTSS_BIT(U));
        break;
    case VTSS_PORT_INTERFACE_USXGMII: /* USXGMII: 1x10G */
        if (p >= 48 && p < 64) {
            S = p - 32;
            REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(S),
                    VTSS_F_PORT_CONF_USXGMII_CFG_TX_ENA(1) |
                        VTSS_F_PORT_CONF_USXGMII_CFG_RX_ENA(1) |
                        VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(0),
                    VTSS_M_PORT_CONF_USXGMII_CFG_TX_ENA | VTSS_M_PORT_CONF_USXGMII_CFG_RX_ENA |
                        VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);
            REG_WRM(VTSS_PORT_CONF_USXGMII_ENA, VTSS_BIT(S), VTSS_BIT(S));
        } else {
            VTSS_E("chip port %d does not support SXGMII mode", p);
            return VTSS_RC_ERROR;
        }
        break;
    default: break;
    }

    return VTSS_RC_OK;
}
#else
static vtss_rc la_port_mux_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 p = VTSS_CHIP_PORT(port_no), Q;
    u32 R, H;

    if (vtss_state->port.current_if_type[port_no] == vtss_state->port.conf[port_no].if_type) {
        return VTSS_RC_OK; // Nothing to do
    }

    switch (vtss_state->port.conf[port_no].if_type) {
    case VTSS_PORT_INTERFACE_QSGMII: /* QSGMII: 4x2G5 devices. Mode Q'  */
        Q = (p - p % 4) / 4;
        REG_WRM(VTSS_PORT_CONF_QSGMII_ENA, VTSS_BIT(Q), VTSS_BIT(Q));
        break;
    case VTSS_PORT_INTERFACE_QXGMII: /* QXGMII: 4x2G5 devices. Mode 'R'. Use 2G5
                                        device. */
        if (LA_TGT && p >= 8 && p < 23) {
            R = p / 4; /* equals index 2-5 */
            REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(R),
                    VTSS_F_PORT_CONF_USXGMII_CFG_TX_ENA(1) |
                        VTSS_F_PORT_CONF_USXGMII_CFG_RX_ENA(1) |
                        VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(2),
                    VTSS_M_PORT_CONF_USXGMII_CFG_TX_ENA | VTSS_M_PORT_CONF_USXGMII_CFG_RX_ENA |
                        VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);
            REG_WRM(VTSS_PORT_CONF_USXGMII_ENA, VTSS_BIT(R), VTSS_BIT(R));
        } else {
            VTSS_E("chip port %d does not support QXGMII mode", p);
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_PORT_INTERFACE_USXGMII: /* USXGMII: 1x10G USXGMII. Mode 'H' */
        if (VTSS_PORT_IS_10G(p)) {
            H = vtss_port_dev_index(vtss_state, p);
            REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(H),
                    VTSS_F_PORT_CONF_USXGMII_CFG_TX_ENA(1) |
                        VTSS_F_PORT_CONF_USXGMII_CFG_RX_ENA(1) |
                        VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(0),
                    VTSS_M_PORT_CONF_USXGMII_CFG_TX_ENA | VTSS_M_PORT_CONF_USXGMII_CFG_RX_ENA |
                        VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);
            REG_WRM(VTSS_PORT_CONF_USXGMII_ENA, VTSS_BIT(H), VTSS_BIT(H));
        } else {
            VTSS_E("chip port %d does not support SXGMII mode", p);
            return VTSS_RC_ERROR;
        }
        break;
    default: break;
    }
    return VTSS_RC_OK;
}
#endif

static vtss_rc port_mux_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
#if defined(VTSS_ARCH_SPARX5)
    return fa_port_mux_set(vtss_state, port_no);
#elif defined(VTSS_ARCH_LAN969X) || defined(VTSS_ARCH_LAIKA)
    return la_port_mux_set(vtss_state, port_no);
#endif
}

static vtss_rc fa_serdes_set(vtss_state_t        *vtss_state,
                             const vtss_port_no_t port_no,
                             vtss_serdes_mode_t   serdes_mode)
{

    u32 indx = vtss_fa_sd_lane_indx(vtss_state, port_no);

    if (vtss_state->port.bulk_state != VTSS_PORT_BULK_DISABLED) {
        vtss_state->port.sd28_mode[indx] = serdes_mode;
        vtss_state->port.serdes_mode[port_no] = serdes_mode;
        return VTSS_RC_OK;
    }
    vtss_state->port.bulk_port_mask |= VTSS_BIT64(port_no);
    VTSS_RC(vtss_fa_sd_cfg(vtss_state, port_no, serdes_mode));
    vtss_state->port.sd28_mode[indx] = serdes_mode;
    vtss_state->port.bulk_port_mask &= ~VTSS_BIT64(port_no);

    /* Also update the port.serdes_mode[port_no] - for backward compatability */
    if (serdes_mode == VTSS_SERDES_MODE_QSGMII) {
        u32 p = (VTSS_CHIP_PORT(port_no) / 4) * 4;
        for (u32 cnt = 0; cnt < 4; cnt++) {
            for (u32 port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                if (p + cnt == VTSS_CHIP_PORT(port_no)) {
                    vtss_state->port.serdes_mode[port_no] = VTSS_SERDES_MODE_QSGMII;
                }
            }
        }
    } else if (serdes_mode == VTSS_SERDES_MODE_QXGMII) {
        u32 port = VTSS_CHIP_PORT(port_no) % 16;
        for (u32 cnt = 0; cnt < 4; cnt++) {
            for (u32 port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                if (port + (cnt * 16) == VTSS_CHIP_PORT(port_no)) {
                    vtss_state->port.serdes_mode[port_no] = VTSS_SERDES_MODE_QXGMII;
                }
            }
        }
    } else {
        vtss_state->port.serdes_mode[port_no] = serdes_mode;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_max_tags_t  max_tags = vtss_state->port.conf[port_no].max_tags;
    vtss_vlan_port_type_t vlan_type = vtss_state->l2.vlan_port_conf[port_no].port_type;
    u32                   etype, port = VTSS_CHIP_PORT(port_no);

    /* S-ports and VLAN unaware ports both support 0x88a8 (in addition to
     * 0x8100) */
    etype = (vlan_type == VTSS_VLAN_PORT_TYPE_S_CUSTOM ? vtss_state->l2.vlan_conf.s_etype
             : vlan_type == VTSS_VLAN_PORT_TYPE_C      ? VTSS_ETYPE_TAG_C
                                                       : VTSS_ETYPE_TAG_S);

    if (VTSS_PORT_IS_10G(port)) {
        /* As 10G and 1G devices come in pairs, we must update both devices with
         * max tags */
        /* Currently only supporting one user defined TAG (besides 0x8100 and
         * 0x88A8) */
        REG_WRM(VTSS_DEV10G_MAC_TAGS_CFG(VTSS_TO_HIGH_DEV(port), 0),
                VTSS_F_DEV10G_MAC_TAGS_CFG_TAG_ID(etype) |
                    VTSS_F_DEV10G_MAC_TAGS_CFG_TAG_ENA(max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1),
                VTSS_M_DEV10G_MAC_TAGS_CFG_TAG_ID | VTSS_M_DEV10G_MAC_TAGS_CFG_TAG_ENA);

        REG_WRM(VTSS_DEV10G_MAC_NUM_TAGS_CFG(VTSS_TO_HIGH_DEV(port)), // Triple tags not currently
                                                                      // supported
                VTSS_F_DEV10G_MAC_NUM_TAGS_CFG_NUM_TAGS(max_tags == VTSS_PORT_MAX_TAGS_ONE   ? 1
                                                        : max_tags == VTSS_PORT_MAX_TAGS_TWO ? 2
                                                                                             : 0),
                VTSS_M_DEV10G_MAC_NUM_TAGS_CFG_NUM_TAGS);

        REG_WRM(VTSS_DEV10G_MAC_MAXLEN_CFG(VTSS_TO_HIGH_DEV(port)),
                VTSS_F_DEV10G_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(max_tags == VTSS_PORT_MAX_TAGS_NONE
                                                                 ? 0
                                                                 : 1),
                VTSS_M_DEV10G_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK);
    }
    REG_WR(VTSS_DEV1G_MAC_TAGS_CFG(VTSS_TO_DEV2G5(port)),
           VTSS_F_DEV1G_MAC_TAGS_CFG_TAG_ID(etype) |
               VTSS_F_DEV1G_MAC_TAGS_CFG_PB_ENA(max_tags == VTSS_PORT_MAX_TAGS_TWO
                                                    ? 1
                                                    : 0) | // Triple tags not currently supported
               VTSS_F_DEV1G_MAC_TAGS_CFG_VLAN_AWR_ENA(max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1) |
               VTSS_F_DEV1G_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA(max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0
                                                                                              : 1));

    return VTSS_RC_OK;
}

static vtss_rc fa_dsm_wm_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no), stop_wm;
    /* MESA-641 - Setting the tx_stop_wm manually to avoid preemtion issues */
    stop_wm = vtss_get_fifo_size(vtss_state, port_no);
    REG_WRM(VTSS_DSM_DEV_TX_STOP_WM_CFG(port),
            VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM(stop_wm),
            VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM);

    return VTSS_RC_OK;
}

/* Configure 802.1Qbb Priority Flow Control */
static vtss_rc fa_port_pfc(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u32 q, pfc_mask = 0;
    u32 spd = (conf->speed == VTSS_SPEED_25G)     ? 0
              : (conf->speed == VTSS_SPEED_10G)   ? 1
              : (conf->speed == VTSS_SPEED_2500M) ? 2
              : (conf->speed == VTSS_SPEED_1G)    ? 3
              : (conf->speed == VTSS_SPEED_100M)  ? 4
              : (conf->speed == VTSS_SPEED_10M)   ? 5
                                                  : 6;

    for (q = 0; q < VTSS_PRIOS; q++) {
        pfc_mask |= conf->flow_control.pfc[q] ? (1 << q) : 0;
    }

    /* QSYS / Tx enable */
    REG_WRM(VTSS_QSYS_PFC_CFG(port), VTSS_F_QSYS_PFC_CFG_TX_PFC_ENA(pfc_mask),
            VTSS_M_QSYS_PFC_CFG_TX_PFC_ENA);

    /* DSM / Tx enable */
    REG_WRM(VTSS_DSM_ETH_PFC_CFG(port),
            VTSS_F_DSM_ETH_PFC_CFG_PFC_XOFF_MIN_UPDATE_ENA(1) |
                VTSS_F_DSM_ETH_PFC_CFG_PFC_ENA(VTSS_BOOL(pfc_mask)),
            VTSS_M_DSM_ETH_PFC_CFG_PFC_XOFF_MIN_UPDATE_ENA | VTSS_M_DSM_ETH_PFC_CFG_PFC_ENA);

    /* Asm / Rx enable */
    REG_WR(VTSS_ASM_PFC_CFG(port),
           VTSS_F_ASM_PFC_CFG_RX_PFC_ENA(pfc_mask) | VTSS_F_ASM_PFC_CFG_FC_LINK_SPEED(spd));

    /* ASM must not drop PFC frames as the PFC detection is done on the cellbus
     * interface */
    REG_WRM(VTSS_ASM_PAUSE_CFG(port), VTSS_F_ASM_PAUSE_CFG_ABORT_CTRL_ENA(!VTSS_BOOL(pfc_mask)),
            VTSS_M_ASM_PAUSE_CFG_ABORT_CTRL_ENA);

    /* Enable PFC Rx in Scheduler, layer 2 */
    REG_WRM(VTSS_HSCH_PFC_CFG(port), VTSS_F_HSCH_PFC_CFG_PFC_LAYER(VTSS_BOOL(pfc_mask) ? 2 : 0),
            VTSS_M_HSCH_PFC_CFG_PFC_LAYER);

    /* Scheduler element = port in normal mode */
    REG_WRM(VTSS_HSCH_PFC_CFG(port), VTSS_F_HSCH_PFC_CFG_PFC_SE(port), VTSS_M_HSCH_PFC_CFG_PFC_SE);

    return VTSS_RC_OK;
}

static vtss_rc fa_port_fc_setup(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u8  *smac = &conf->flow_control.smac.addr[0], q;
    BOOL pfc = 0, fc_gen = conf->flow_control.generate, fc_obey = conf->flow_control.obey;
    u32  pause_start = 20;       // Number of cells (chip default)
    u32  pause_stop = 0xFFF - 1; // Max number of cells - Disables FC (default) (JIRA APPL-2649)
    u32  atop = VTSS_M_QSYS_ATOP_ATOP; // Default disabled
    u32  fc_start = 6;                 // start when fc is enabled (frames)
    u32  fc_stop = 4;                  // stop when fc is enabled (frames)
    u32  atop_tot = VTSS_M_QSYS_ATOP_TOT_CFG_ATOP_TOT;

    for (q = 0; q < VTSS_PRIOS; q++) {
        if (conf->flow_control.pfc[q]) {
            pfc = 1;
            if (fc_gen || fc_obey) {
                VTSS_E("802.3x FC and 802.1Qbb PFC cannot both be enabled, chip port %u", port);
                return VTSS_RC_ERROR;
            }
        }
    }
    /* Configure 802.1Qbb PFC */
    VTSS_RC(fa_port_pfc(vtss_state, port, conf));

    /* If FC is enabled then set the FC WMs */
    if (pfc || fc_gen || fc_obey) {
        atop = wm_enc(20 * (VTSS_MAX_FRAME_LENGTH_STANDARD / FA_BUFFER_CELL_SZ));
        pause_start = wm_enc(fc_start * (VTSS_MAX_FRAME_LENGTH_STANDARD / FA_BUFFER_CELL_SZ));
        pause_stop = wm_enc(fc_stop * (VTSS_MAX_FRAME_LENGTH_STANDARD / FA_BUFFER_CELL_SZ));
        atop_tot = 0; /* = VTSS_QSYS_ATOP controls tail drop alone */
    }

    /* No ingress drops in FC */
    REG_WRM(VTSS_QFWD_SWITCH_PORT_MODE(port),
            VTSS_F_QFWD_SWITCH_PORT_MODE_INGRESS_DROP_MODE(!fc_obey),
            VTSS_M_QFWD_SWITCH_PORT_MODE_INGRESS_DROP_MODE);

    /* Set Pause WM hysteresis */
    REG_WRM(VTSS_QSYS_PAUSE_CFG(port),
            VTSS_F_QSYS_PAUSE_CFG_PAUSE_START(pause_start) |
                VTSS_F_QSYS_PAUSE_CFG_PAUSE_STOP(pause_stop) | VTSS_F_QSYS_PAUSE_CFG_PAUSE_ENA(0),
            VTSS_M_QSYS_PAUSE_CFG_PAUSE_START | VTSS_M_QSYS_PAUSE_CFG_PAUSE_STOP |
                VTSS_M_QSYS_PAUSE_CFG_PAUSE_ENA); // enabled after reset

    /* Port ATOP. Frames are tail dropped when this WM is hit */
    REG_WRM(VTSS_QSYS_ATOP(port), VTSS_F_QSYS_ATOP_ATOP(atop), VTSS_M_QSYS_ATOP_ATOP);

    /*  When 'port ATOP' and 'common ATOP_TOT' are exceeded, tail dropping is
     * activated on port */
    REG_WRM(VTSS_QSYS_ATOP_TOT_CFG, VTSS_F_QSYS_ATOP_TOT_CFG_ATOP_TOT(atop_tot),
            VTSS_M_QSYS_ATOP_TOT_CFG_ATOP_TOT);

    /* Set SMAC of Pause frame */
    REG_WR(VTSS_DSM_MAC_ADDR_BASE_HIGH_CFG(port), (smac[0] << 16) | (smac[1] << 8) | smac[2]);
    REG_WR(VTSS_DSM_MAC_ADDR_BASE_LOW_CFG(port), (smac[3] << 16) | (smac[4] << 8) | smac[5]);

    /* Set HDX flowcontrol */
    REG_WRM(VTSS_DSM_MAC_CFG(port), VTSS_F_DSM_MAC_CFG_HDX_BACKPREASSURE(!conf->fdx),
            VTSS_M_DSM_MAC_CFG_HDX_BACKPREASSURE);

    /* Obey flowcontrol  */
    REG_WRM(VTSS_DSM_RX_PAUSE_CFG(port), VTSS_F_DSM_RX_PAUSE_CFG_RX_PAUSE_EN(fc_obey),
            VTSS_M_DSM_RX_PAUSE_CFG_RX_PAUSE_EN);

    /* Disable forward pressure when in fc (JIRA-UNG_FIREANT-17) */
    REG_WRM(VTSS_QSYS_FWD_PRESSURE(port), VTSS_F_QSYS_FWD_PRESSURE_FWD_PRESSURE_DIS(fc_obey),
            VTSS_M_QSYS_FWD_PRESSURE_FWD_PRESSURE_DIS);

    /* Discard pause frame 01-80-C2-00-00-01 */
    REG_WRM(VTSS_ANA_CL_CAPTURE_BPDU_CFG(port),
            VTSS_F_ANA_CL_CAPTURE_BPDU_CFG_CPU_BPDU_REDIR_SEL(0xC),
            VTSS_M_ANA_CL_CAPTURE_BPDU_CFG_CPU_BPDU_REDIR_SEL);

    return VTSS_RC_OK;
}

/* Poll port until all memory is freed */
static vtss_rc fa_port_flush_poll(vtss_state_t *vtss_state, vtss_phys_port_no_t port)
{
    u32 value, resource, prio, delay_cnt = 0;
#if VTSS_OPT_TRACE_ERROR
    char *failing_mem = "";
#endif
    BOOL poll_src;

#if defined(VTSS_FEATURE_AFI_SWC)
    // Only do DST-MEM resource.
    // The reason not to do SRC-MEM poll is that if the AFI is having at least
    // one up-flow (with CL_DP == 0) on the port we are trying to flush, SRC-MEM
    // will never go to zero even though the flow has actually been stopped
    // (which it is by now).
    poll_src = FALSE;
#else
    // Do both DST-MEM and SRC-MEM poll.
    poll_src = TRUE;
#endif

    // Resource == 0: Memory tracked per source (SRC-MEM)
    // Resource == 1: Frame references tracked per source (SRC-REF)
    // Resource == 2: Memory tracked per destination (DST-MEM)
    // Resource == 3: Frame references tracked per destination. (DST-REF)

    while (1) {
        BOOL empty = TRUE;

        for (resource = 0; resource < (poll_src ? 2 : 1); resource++) {
            // Start with DST-MEM (base == 2048) and if enabled, also check
            // SRC-MEM (base == 0).
            u32 base = (resource == 0 ? 2048 : 0) + VTSS_PRIOS * port;

            for (prio = 0; prio < VTSS_PRIOS; prio++) {
                REG_RD(VTSS_QRES_RES_STAT(base + prio), &value);
                if (value) {
#if VTSS_OPT_TRACE_ERROR
                    failing_mem = resource == 0 ? "DST-MEM" : "SRC-MEM";
#endif
                    empty = FALSE;

                    // Here, it could be tempting to exit the loop, but because
                    // the registers are clear-on-read, we gotta continue, or it
                    // will take at least 8 or 16 VTSS_MSLEEP() calls to get out
                    // of this.
                }
            }
        }

        if (empty) {
            break;
        }

        if (delay_cnt++ == 2000) {
            u32           base, idx;
            lmu_fmt_buf_t buf;

            VTSS_FMT(buf, "QRES:RES_CTRL[chip-port = %u]:RES_STAT\n", port);
            for (resource = 0; resource < 4; resource++) {
                base = resource * 1024 + port * VTSS_PRIOS;
                for (prio = 0; prio < VTSS_PRIOS; prio++) {
                    idx = base + prio;
                    REG_RD(VTSS_QRES_RES_STAT(idx), &value);
                    if (value) {
                        LMU_SS_FMT(&buf.ss, "res = %u, prio = %u => idx = %u val = %u\n", resource,
                                   prio, idx, value);
                    }
                }
            }

            VTSS_E("Flush timeout chip port %u. %s queue not empty\n%s", port, failing_mem, buf.s);
            break;
        }

        VTSS_MSLEEP(1);
    }

    return VTSS_RC_OK;
}

static inline vtss_rc fa_dev1g_rst_ctrl(vtss_state_t *vtss_state,
                                        u32           tgt,
                                        u32           clk_spd,
                                        BOOL          usx_pcs_rst,
                                        BOOL          pcs_rst,
                                        BOOL          mac_rst)
{
    u32 mask = VTSS_M_DEV1G_DEV_RST_CTRL_SPEED_SEL | VTSS_M_DEV1G_DEV_RST_CTRL_PCS_TX_RST |
               VTSS_M_DEV1G_DEV_RST_CTRL_PCS_RX_RST | VTSS_M_DEV1G_DEV_RST_CTRL_MAC_TX_RST |
               VTSS_M_DEV1G_DEV_RST_CTRL_MAC_RX_RST;
    u32 val = VTSS_F_DEV1G_DEV_RST_CTRL_SPEED_SEL(clk_spd) |
              VTSS_F_DEV1G_DEV_RST_CTRL_PCS_TX_RST(pcs_rst) |
              VTSS_F_DEV1G_DEV_RST_CTRL_PCS_RX_RST(pcs_rst) |
              VTSS_F_DEV1G_DEV_RST_CTRL_MAC_TX_RST(mac_rst) |
              VTSS_F_DEV1G_DEV_RST_CTRL_MAC_RX_RST(mac_rst);
#if !defined(VTSS_ARCH_LAIKA)
    mask |= VTSS_M_DEV1G_DEV_RST_CTRL_USX_PCS_TX_RST | VTSS_M_DEV1G_DEV_RST_CTRL_USX_PCS_RX_RST;
    val |= VTSS_F_DEV1G_DEV_RST_CTRL_USX_PCS_TX_RST(usx_pcs_rst) |
           VTSS_F_DEV1G_DEV_RST_CTRL_USX_PCS_RX_RST(usx_pcs_rst);
#endif
    REG_WRM(VTSS_DEV1G_DEV_RST_CTRL(tgt), val, mask);
    return VTSS_RC_OK;
}

/* Port disable and flush procedure */
static vtss_rc fa_port_flush(vtss_state_t        *vtss_state,
                             const vtss_port_no_t port_no,
                             BOOL                 high_speed_dev)
{
    u32               port = VTSS_CHIP_PORT(port_no);
    u32               tgt = high_speed_dev ? VTSS_TO_HIGH_DEV(port) : VTSS_TO_DEV2G5(port);
    vtss_port_speed_t spd = vtss_state->port.current_speed[port_no];
    u32               spd_prm = spd == VTSS_SPEED_10M ? 1000 : spd == VTSS_SPEED_100M ? 100 : 10;
    BOOL              rgmii = port_is_rgmii(vtss_state, port_no);

    VTSS_I("Flush chip port: %u (%s device)", port, high_speed_dev ? "5/10/25G" : "2G5");

    if (high_speed_dev) {
        /* 1: Reset the PCS Rx clock domain  */
        REG_WRM_SET(VTSS_DEV10G_DEV_RST_CTRL(tgt), VTSS_M_DEV10G_DEV_RST_CTRL_PCS_RX_RST);

        /* 2: Disable MAC frame reception */
        REG_WRM_CLR(VTSS_DEV10G_MAC_ENA_CFG(tgt), VTSS_M_DEV10G_MAC_ENA_CFG_RX_ENA);
    } else {
        if (rgmii) {
#if defined(VTSS_ARCH_LAN969X)
            REG_WRM_CLR(VTSS_DEVRGMII_MAC_ENA_CFG(tgt), VTSS_M_DEVRGMII_MAC_ENA_CFG_RX_ENA);
#endif
        } else {
            /* 1: Reset the PCS Rx clock domain  */
            REG_WRM_SET(VTSS_DEV1G_DEV_RST_CTRL(tgt), VTSS_M_DEV1G_DEV_RST_CTRL_PCS_RX_RST);
            /* 2: Disable MAC frame reception */
            REG_WRM_CLR(VTSS_DEV1G_MAC_ENA_CFG(tgt), VTSS_M_DEV1G_MAC_ENA_CFG_RX_ENA);
        }
    }
    /* 3: Disable traffic being sent to or from switch port */
    REG_WRM_CLR(VTSS_QFWD_SWITCH_PORT_MODE(port), VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA);

    /* 4: Disable dequeuing from the egress queues  */
    REG_WRM_SET(VTSS_HSCH_PORT_MODE(port), VTSS_M_HSCH_PORT_MODE_DEQUEUE_DIS);

    /* 5: Disable Flowcontrol */
    REG_WRM(VTSS_QSYS_PAUSE_CFG(port), VTSS_F_QSYS_PAUSE_CFG_PAUSE_STOP(0xFFF - 1),
            VTSS_M_QSYS_PAUSE_CFG_PAUSE_STOP);

    /* 5.1: Disable PFC */
    /* REG_WRM_CLR(VTSS_QRES_RES_QOS_ADV_PFC_CFG(port),
     * VTSS_M_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA); */

    /* 6: Wait a worst case time 8ms (jumbo/10Mbit) *\/ */
    VTSS_NSLEEP(8000 * spd_prm);

    /* 7: Flush the queues accociated with the port */
    REG_WRM(VTSS_HSCH_FLUSH_CTRL,
            VTSS_F_HSCH_FLUSH_CTRL_FLUSH_PORT(port) | VTSS_F_HSCH_FLUSH_CTRL_FLUSH_DST(1) |
                VTSS_F_HSCH_FLUSH_CTRL_FLUSH_SRC(1) | VTSS_F_HSCH_FLUSH_CTRL_FLUSH_ENA(1),
            VTSS_M_HSCH_FLUSH_CTRL_FLUSH_PORT | VTSS_M_HSCH_FLUSH_CTRL_FLUSH_DST |
                VTSS_M_HSCH_FLUSH_CTRL_FLUSH_SRC | VTSS_M_HSCH_FLUSH_CTRL_FLUSH_ENA);

    /* 8: Enable dequeuing from the egress queues */
    REG_WRM_CLR(VTSS_HSCH_PORT_MODE(port), VTSS_M_HSCH_PORT_MODE_DEQUEUE_DIS);

    /* 9: Wait until flushing is complete */
    VTSS_RC(fa_port_flush_poll(vtss_state, port))

    /* 10: Reset the  MAC clock domain */
    if (high_speed_dev) {
        REG_WRM(VTSS_DEV10G_DEV_RST_CTRL(tgt),
                VTSS_F_DEV10G_DEV_RST_CTRL_PCS_TX_RST(1) |
                    VTSS_F_DEV10G_DEV_RST_CTRL_MAC_RX_RST(1) |
                    VTSS_F_DEV10G_DEV_RST_CTRL_MAC_TX_RST(1),
                VTSS_M_DEV10G_DEV_RST_CTRL_PCS_TX_RST | VTSS_M_DEV10G_DEV_RST_CTRL_MAC_RX_RST |
                    VTSS_M_DEV10G_DEV_RST_CTRL_MAC_TX_RST);
    } else {
        if (!rgmii) {
            fa_dev1g_rst_ctrl(vtss_state, tgt, 3, TRUE, TRUE, TRUE);
        }
    }

    /* 11: Clear flushing */
    REG_WRM(VTSS_HSCH_FLUSH_CTRL,
            VTSS_F_HSCH_FLUSH_CTRL_FLUSH_PORT(port) | VTSS_F_HSCH_FLUSH_CTRL_FLUSH_ENA(0),
            VTSS_M_HSCH_FLUSH_CTRL_FLUSH_PORT | VTSS_M_HSCH_FLUSH_CTRL_FLUSH_ENA);

    if (high_speed_dev) {
        /* 12: Disable 10G PCS */
        REG_WRM_CLR(VTSS_PCS_10GBASE_R_PCS_CFG(VTSS_TO_PCS_TGT(port)),
                    VTSS_M_PCS_10GBASE_R_PCS_CFG_PCS_ENA);

        if (VTSS_PORT_IS_25G(port)) {
            /* Disable 25G PCS */
            REG_WRM_CLR(VTSS_DEV10G_PCS25G_CFG(tgt), VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
        }
    }

    if (!rgmii) {
        REG_WRM_CLR(VTSS_DEV1G_PCS1G_CFG(tgt), VTSS_M_DEV1G_PCS1G_CFG_PCS_ENA);
        REG_WRM_CLR(VTSS_DEV1G_PCS_FX100_CFG(tgt), VTSS_M_DEV1G_PCS_FX100_CFG_PCS_ENA);
    }

    /* The port is now flushed and disabled  */

    return VTSS_RC_OK;
}

// Power down serdes TX driver and set RX PCS in reset
static vtss_rc fa_sd_power_save(vtss_state_t        *vtss_state,
                                const vtss_port_no_t port_no,
                                BOOL                 power_down)
{
    u32  indx, type, sd_tgt, port = VTSS_CHIP_PORT(port_no);
    BOOL pd_serdes = 1;

    if (port_is_rgmii(vtss_state, port_no) ||
        (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_USGMII) ||
        (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_QXGMII) ||
        (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_DXGMII_5G)) {
        pd_serdes = 0; // Do not power down multi-port serdes
    }

    // Only power down QSGMII serdes when all port instanaces are powered down
    if (power_down && vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_QSGMII) {
        u32 base = (port / 4) * 4;
        for (u32 cnt = 0; cnt < 4; cnt++) {
            pd_serdes = 1;
            for (u32 api_port = VTSS_PORT_NO_START; api_port < vtss_state->port_count; api_port++) {
                if (api_port == port_no) {
                    continue;
                }
                if (base + cnt == VTSS_CHIP_PORT(api_port)) {
                    if (!vtss_state->port.conf[api_port].power_down) {
                        pd_serdes = 0;
                        break;
                    }
                }
            }
            if (!pd_serdes) {
                break;
            }
        }
    }

    if (pd_serdes) {
        VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
        if (type == FA_SERDES_TYPE_25G) {
#if defined(VTSS_FEATURE_SD_25G)
            sd_tgt = VTSS_TO_SD25G_LANE(indx);
            DEV_WRM(DEV_RST_CTRL, VTSS_CHIP_PORT(port_no),
                    VTSS_F_DEV10G_DEV_RST_CTRL_PCS_TX_RST(power_down),
                    VTSS_M_DEV10G_DEV_RST_CTRL_PCS_TX_RST);
            VTSS_MSLEEP(1);
            REG_WRM(VTSS_SD25G_TARGET_LANE_04(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_PD_DRIVER(power_down),
                    VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_PD_DRIVER);
#endif
        } else {
            // 6G and 10G
            if (type == FA_SERDES_TYPE_6G) {
                sd_tgt = VTSS_TO_SD6G_LANE(indx);
            } else {
                sd_tgt = VTSS_TO_SD10G_LANE(indx);
            }
#if !defined(VTSS_ARCH_LAIKA)
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_06(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_06_CFG_PD_DRIVER(power_down),
                    VTSS_M_SD10G_LANE_TARGET_LANE_06_CFG_PD_DRIVER);
#else
            (void)sd_tgt;
#endif
        }
    }

    if (power_down) { // Covers shadow and primary ports
        DEV_WRM(DEV_RST_CTRL, VTSS_CHIP_PORT(port_no), VTSS_F_DEV10G_DEV_RST_CTRL_PCS_RX_RST(1),
                VTSS_M_DEV10G_DEV_RST_CTRL_PCS_RX_RST);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_usxgmii_enable(vtss_state_t        *vtss_state,
                                 const vtss_port_no_t port_no,
                                 BOOL                 dev_high)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 tgt = dev_high ? VTSS_TO_HIGH_DEV(port) : VTSS_TO_DEV2G5(port);

    if (vtss_state->port.current_if_type[port_no] == VTSS_PORT_INTERFACE_QXGMII) {
        return VTSS_RC_OK; // Already done
    }

    if (!dev_high) {
#if !defined(VTSS_ARCH_LAIKA)
        REG_WRM(VTSS_DEV1G_USXGMII_RX_RADAPT_CFG(tgt),
                VTSS_F_DEV1G_USXGMII_RX_RADAPT_CFG_RX_RADAPT_ADD_LVL(3) |
                    VTSS_F_DEV1G_USXGMII_RX_RADAPT_CFG_RX_RADAPT_DROP_LVL(7) |
                    VTSS_F_DEV1G_USXGMII_RX_RADAPT_CFG_RX_RADAPT_MIN_IFG(1),
                VTSS_M_DEV1G_USXGMII_RX_RADAPT_CFG_RX_RADAPT_ADD_LVL |
                    VTSS_M_DEV1G_USXGMII_RX_RADAPT_CFG_RX_RADAPT_DROP_LVL |
                    VTSS_M_DEV1G_USXGMII_RX_RADAPT_CFG_RX_RADAPT_MIN_IFG);

        REG_WRM(VTSS_DEV1G_USXGMII_TX_RADAPT_CFG(tgt),
                VTSS_F_DEV1G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS(0) |
                    VTSS_F_DEV1G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL(2) |
                    VTSS_F_DEV1G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL(6) |
                    VTSS_F_DEV1G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG(1),
                VTSS_M_DEV1G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS |
                    VTSS_M_DEV1G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL |
                    VTSS_M_DEV1G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL |
                    VTSS_M_DEV1G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG);

        REG_WRM(VTSS_DEV1G_USXGMII_ANEG_CFG(tgt),
                VTSS_F_DEV1G_USXGMII_ANEG_CFG_ADV_ABILITY(0xd801) |
                    VTSS_F_DEV1G_USXGMII_ANEG_CFG_LINK_TIMER(1) |
                    VTSS_F_DEV1G_USXGMII_ANEG_CFG_ANEG_ENA(1) |
                    VTSS_F_DEV1G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA(1),
                VTSS_M_DEV1G_USXGMII_ANEG_CFG_ADV_ABILITY |
                    VTSS_M_DEV1G_USXGMII_ANEG_CFG_LINK_TIMER |
                    VTSS_M_DEV1G_USXGMII_ANEG_CFG_ANEG_ENA |
                    VTSS_M_DEV1G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA);

        REG_WRM(VTSS_DEV1G_USXGMII_GMII_XGMII_MAP_CFG(tgt),
                VTSS_F_DEV1G_USXGMII_GMII_XGMII_MAP_CFG_LFS_MODE_ENA(0) | // Need to disable LFS to
                                                                          // work against ML
                    VTSS_F_DEV1G_USXGMII_GMII_XGMII_MAP_CFG_LFS_MAX_NON_FAULT_SEQ(127) |
                    VTSS_F_DEV1G_USXGMII_GMII_XGMII_MAP_CFG_LFS_MAX_FAULT_SEQ(3),
                VTSS_M_DEV1G_USXGMII_GMII_XGMII_MAP_CFG_LFS_MODE_ENA |
                    VTSS_M_DEV1G_USXGMII_GMII_XGMII_MAP_CFG_LFS_MAX_NON_FAULT_SEQ |
                    VTSS_M_DEV1G_USXGMII_GMII_XGMII_MAP_CFG_LFS_MAX_FAULT_SEQ);

#endif
    } else {
        REG_WRM(VTSS_DEV10G_USXGMII_TX_RADAPT_CFG(tgt),
                VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL(4) |
                    VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL(8) |
                    VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG(1) |
                    VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_FIFO_FLUSH(0) |
                    VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS(1),
                VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL |
                    VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL |
                    VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG |
                    VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_FIFO_FLUSH |
                    VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS);

        REG_WRM(VTSS_DEV10G_USXGMII_ANEG_CFG(tgt),
                VTSS_F_DEV10G_USXGMII_ANEG_CFG_ADV_ABILITY(0xd801) |
                    VTSS_F_DEV10G_USXGMII_ANEG_CFG_ANEG_ENA(1) |
                    VTSS_F_DEV10G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1) |
                    VTSS_F_DEV10G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA(1),
                VTSS_M_DEV10G_USXGMII_ANEG_CFG_ADV_ABILITY |
                    VTSS_M_DEV10G_USXGMII_ANEG_CFG_ANEG_ENA |
                    VTSS_M_DEV10G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT |
                    VTSS_M_DEV10G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA);
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_ARCH_LAN969X)
static vtss_rc fa_rgmii_setup(vtss_state_t         *vtss_state,
                              vtss_port_no_t        port_no,
                              vtss_port_interface_t mode,
                              int                   speed)
{
    bool tx_delay = FALSE;
    bool rx_delay = FALSE;
    int  inst, spd;
    u32  port = VTSS_CHIP_PORT(port_no);

    if (port == 28) {
        inst = 0;
    } else if (port == 29) {
        inst = 1;
    } else {
        VTSS_E("illegal rgmii port %d", port);
        return VTSS_RC_ERROR;
    }

    spd = (speed == VTSS_SPEED_10M ? 3 : speed == VTSS_SPEED_100M ? 2 : 1);

    REG_WRM(VTSS_HSIOWRAP_RGMII_CFG(inst),
            VTSS_F_HSIOWRAP_RGMII_CFG_TX_CLK_CFG(spd) | VTSS_F_HSIOWRAP_RGMII_CFG_RGMII_TX_RST(0) |
                VTSS_F_HSIOWRAP_RGMII_CFG_RGMII_RX_RST(0),
            VTSS_M_HSIOWRAP_RGMII_CFG_TX_CLK_CFG | VTSS_M_HSIOWRAP_RGMII_CFG_RGMII_TX_RST |
                VTSS_M_HSIOWRAP_RGMII_CFG_RGMII_RX_RST);

    if (mode == VTSS_PORT_INTERFACE_RGMII || mode == VTSS_PORT_INTERFACE_RGMII_ID ||
        mode == VTSS_PORT_INTERFACE_RGMII_TXID) {
        tx_delay = TRUE;
    }

    if (mode == VTSS_PORT_INTERFACE_RGMII_ID || mode == VTSS_PORT_INTERFACE_RGMII_RXID) {
        rx_delay = TRUE;
    }
    // RX:
    REG_WRM(VTSS_HSIOWRAP_DLL_CFG(inst, 0),
            VTSS_F_HSIOWRAP_DLL_CFG_DLL_CLK_SEL(3) | VTSS_F_HSIOWRAP_DLL_CFG_DLL_ENA(1) |
                VTSS_F_HSIOWRAP_DLL_CFG_DLL_RST(0) | VTSS_F_HSIOWRAP_DLL_CFG_DLL_CLK_ENA(rx_delay),
            VTSS_M_HSIOWRAP_DLL_CFG_DLL_CLK_SEL | VTSS_M_HSIOWRAP_DLL_CFG_DLL_ENA |
                VTSS_M_HSIOWRAP_DLL_CFG_DLL_RST | VTSS_M_HSIOWRAP_DLL_CFG_DLL_CLK_ENA);

    // TX:
    REG_WRM(VTSS_HSIOWRAP_DLL_CFG(inst, 1),
            VTSS_F_HSIOWRAP_DLL_CFG_DLL_CLK_SEL(3) | VTSS_F_HSIOWRAP_DLL_CFG_DLL_ENA(1) |
                VTSS_F_HSIOWRAP_DLL_CFG_DLL_RST(0) | VTSS_F_HSIOWRAP_DLL_CFG_DLL_CLK_ENA(tx_delay),
            VTSS_M_HSIOWRAP_DLL_CFG_DLL_CLK_SEL | VTSS_M_HSIOWRAP_DLL_CFG_DLL_ENA |
                VTSS_M_HSIOWRAP_DLL_CFG_DLL_RST | VTSS_M_HSIOWRAP_DLL_CFG_DLL_CLK_ENA);

    REG_WRM(VTSS_HSIOWRAP_XMII_CFG(!inst), // XMII_CFG index is swapped
            VTSS_F_HSIOWRAP_XMII_CFG_GPIO_XMII_CFG(1), VTSS_M_HSIOWRAP_XMII_CFG_GPIO_XMII_CFG);

    return VTSS_RC_OK;
}
#endif

/* Configuration of the 2G5 device (dev1G architecture) */
static vtss_rc fa_port_conf_2g5_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t  *conf = &vtss_state->port.conf[port_no];
    u32                port = VTSS_CHIP_PORT(port_no);
    u32                tx_gap, hdx_gap_1 = 0, hdx_gap_2 = 0;
    vtss_port_speed_t  speed = conf->speed;
    u32                value;
    BOOL               fdx = conf->fdx;
    BOOL               sgmii = FALSE, pcs_100fx = FALSE, pcs_usx = FALSE, rgmii = FALSE;
    u32                tgt = VTSS_TO_DEV2G5(port), clk_spd = 0;
    vtss_serdes_mode_t serdes_mode = VTSS_SERDES_MODE_SGMII;
    u32                sd_indx = vtss_fa_sd_lane_indx(vtss_state, port_no);

    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
        serdes_mode = (speed == VTSS_SPEED_2500M ? VTSS_SERDES_MODE_2G5 : VTSS_SERDES_MODE_SGMII);
        break;
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        serdes_mode = (speed == VTSS_SPEED_2500M ? VTSS_SERDES_MODE_2G5 : VTSS_SERDES_MODE_SGMII);
        sgmii = TRUE;
        break;
    case VTSS_PORT_INTERFACE_RGMII:
    case VTSS_PORT_INTERFACE_RGMII_RXID:
    case VTSS_PORT_INTERFACE_RGMII_TXID:
    case VTSS_PORT_INTERFACE_RGMII_ID:
        if (port != 28 && port != 29) {
            VTSS_E("Port %u does not support RGMII", port);
            return VTSS_RC_ERROR;
        }
        rgmii = TRUE;
        break;
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_QSGMII) {
            serdes_mode = VTSS_SERDES_MODE_QSGMII; // Do not change the Serdes mode
        } else {
            serdes_mode = VTSS_SERDES_MODE_SGMII;
        }
        sgmii = TRUE;
        break;
    case VTSS_PORT_INTERFACE_100FX:
        serdes_mode = VTSS_SERDES_MODE_100FX;
        pcs_100fx = TRUE;
        break;
    case VTSS_PORT_INTERFACE_QSGMII: // Normal QSGMII
        serdes_mode = VTSS_SERDES_MODE_QSGMII;
        sgmii = TRUE;
        break;
    case VTSS_PORT_INTERFACE_USGMII: // 8x1G, X-mode (ala 2 x QSGMII) 10G Serdes
        serdes_mode = VTSS_SERDES_MODE_USGMII;
        sgmii = TRUE;
        break;
    case VTSS_PORT_INTERFACE_QXGMII: // 4x2G5 R-mode, 10G Serdes
        serdes_mode = VTSS_SERDES_MODE_QXGMII;
        pcs_usx = TRUE;
        break;
    case VTSS_PORT_INTERFACE_DXGMII_5G: // 2x2G5 F-mode, 5G Serdes
        serdes_mode = VTSS_SERDES_MODE_DXGMII_5G;
        pcs_usx = TRUE;
        break;
    default: {
        VTSS_E("Interface type not supported");
    }
    }
    switch (speed) {
    case VTSS_SPEED_10M:   clk_spd = 0; break;
    case VTSS_SPEED_100M:  clk_spd = 1; break;
    case VTSS_SPEED_1G:    clk_spd = 2; break;
    case VTSS_SPEED_2500M: clk_spd = pcs_usx ? 6 : 2; break;
    default:               {
        VTSS_E("Speed not supported");
    }
    }

    /* Enable the Serdes if disabled */
    if (!rgmii && (vtss_state->port.sd28_mode[sd_indx] == VTSS_SERDES_MODE_DISABLE)) {
        VTSS_RC(fa_serdes_set(vtss_state, port_no, serdes_mode));
    }

    /* Port disable and flush procedure: */
    VTSS_RC(fa_port_flush(vtss_state, port_no, FALSE));

    /* Configure the Serdes Macro to 'serdes_mode' */
    if (!rgmii && (serdes_mode != vtss_state->port.sd28_mode[sd_indx])) {
        VTSS_RC(fa_serdes_set(vtss_state, port_no, serdes_mode));
    }

    /* Enable ASM/DSM 1G/2Gg5 counters */
    REG_WRM(VTSS_ASM_PORT_CFG(port), VTSS_F_ASM_PORT_CFG_CSC_STAT_DIS(0),
            VTSS_M_ASM_PORT_CFG_CSC_STAT_DIS);

    REG_WRM(VTSS_DSM_BUF_CFG(port), VTSS_F_DSM_BUF_CFG_CSC_STAT_DIS(0),
            VTSS_M_DSM_BUF_CFG_CSC_STAT_DIS);

    /* Bugzilla 4388: disabling frame aging when in HDX */
    REG_WRM_CTL(VTSS_HSCH_PORT_MODE(port), !fdx, VTSS_M_HSCH_PORT_MODE_AGE_DIS);

    /* GIG/FDX mode */
    if (rgmii) {
#if defined(VTSS_ARCH_LAN969X)
        REG_WRM(VTSS_DEVRGMII_MAC_MODE_CFG(tgt),
                VTSS_F_DEVRGMII_MAC_MODE_CFG_GIGA_MODE_ENA(1) |
                    VTSS_F_DEVRGMII_MAC_MODE_CFG_FDX_ENA(fdx),
                VTSS_M_DEVRGMII_MAC_MODE_CFG_GIGA_MODE_ENA | VTSS_M_DEVRGMII_MAC_MODE_CFG_FDX_ENA);
#endif
    } else {
        REG_WRM(VTSS_DEV1G_MAC_MODE_CFG(tgt),
                VTSS_F_DEV1G_MAC_MODE_CFG_GIGA_MODE_ENA(1) | VTSS_F_DEV1G_MAC_MODE_CFG_FDX_ENA(fdx),
                VTSS_M_DEV1G_MAC_MODE_CFG_GIGA_MODE_ENA | VTSS_M_DEV1G_MAC_MODE_CFG_FDX_ENA);
    }

    /* HDX gap 1 */
    if (conf->frame_gaps.hdx_gap_1 == VTSS_FRAME_GAP_DEFAULT) {
        hdx_gap_1 = speed == VTSS_SPEED_100M ? 1 : speed == VTSS_SPEED_10M ? 2 : 0;
    } else {
        hdx_gap_1 = conf->frame_gaps.hdx_gap_1;
    }
    /* HDX gap 2 */
    if (conf->frame_gaps.hdx_gap_2 == VTSS_FRAME_GAP_DEFAULT) {
        hdx_gap_2 = VTSS_SPEED_100M ? 4 : speed == VTSS_SPEED_10M ? 1 : 0;
    } else {
        hdx_gap_2 = conf->frame_gaps.hdx_gap_2;
    }
    /* TX interframe gap */
    if (conf->frame_gaps.fdx_gap == VTSS_FRAME_GAP_DEFAULT) {
        if (FA_TGT) {
            /* UNG_LAGUNA-590 */
            tx_gap = (speed == VTSS_SPEED_1G) ? 4 : fdx ? 6 : 5;
        } else {
            tx_gap = (speed == VTSS_SPEED_1G) ? 4 : fdx ? 5 : 4;
        }
    } else {
        tx_gap = conf->frame_gaps.fdx_gap;
    }

    if (LA_TGT) {
        // MESA-931
        conf->exc_col_cont = TRUE;
    }

    if (rgmii) {
#if defined(VTSS_ARCH_LAN969X)
        /* Set MAC IFG Gaps */
        REG_WR(VTSS_DEVRGMII_MAC_IFG_CFG(tgt), VTSS_F_DEVRGMII_MAC_IFG_CFG_TX_IFG(tx_gap) |
                                                   VTSS_F_DEVRGMII_MAC_IFG_CFG_RX_IFG1(hdx_gap_1) |
                                                   VTSS_F_DEVRGMII_MAC_IFG_CFG_RX_IFG2(hdx_gap_2));

        /* Set MAC HDX late collision */
        REG_WRM(VTSS_DEVRGMII_MAC_HDX_CFG(tgt),
                VTSS_F_DEVRGMII_MAC_HDX_CFG_LATE_COL_POS(67) |
                    VTSS_F_DEVRGMII_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA(conf->exc_col_cont),
                VTSS_M_DEVRGMII_MAC_HDX_CFG_LATE_COL_POS |
                    VTSS_M_DEVRGMII_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA);
#endif
    } else {
        /* Set MAC IFG Gaps */
        REG_WR(VTSS_DEV1G_MAC_IFG_CFG(tgt), VTSS_F_DEV1G_MAC_IFG_CFG_TX_IFG(tx_gap) |
                                                VTSS_F_DEV1G_MAC_IFG_CFG_RX_IFG1(hdx_gap_1) |
                                                VTSS_F_DEV1G_MAC_IFG_CFG_RX_IFG2(hdx_gap_2));

        /* Set MAC HDX late collision */
        REG_WRM(VTSS_DEV1G_MAC_HDX_CFG(tgt),
                VTSS_F_DEV1G_MAC_HDX_CFG_LATE_COL_POS(67) |
                    VTSS_F_DEV1G_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA(conf->exc_col_cont),
                VTSS_M_DEV1G_MAC_HDX_CFG_LATE_COL_POS |
                    VTSS_M_DEV1G_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA);
    }

    /* PCS settings for 100fx/USX/SGMII/SERDES */
    if (pcs_100fx) {
        /* Enable 100FX */
        REG_WRM(VTSS_DEV1G_PCS_FX100_CFG(tgt),
                VTSS_F_DEV1G_PCS_FX100_CFG_PCS_ENA(1) |
                    VTSS_F_DEV1G_PCS_FX100_CFG_SD_SEL(!conf->sd_internal) |
                    VTSS_F_DEV1G_PCS_FX100_CFG_SD_POL(conf->sd_active_high) |
                    VTSS_F_DEV1G_PCS_FX100_CFG_SD_ENA(conf->sd_enable) |
                    VTSS_F_DEV1G_PCS_FX100_CFG_RXBITSEL(0),
                VTSS_M_DEV1G_PCS_FX100_CFG_PCS_ENA | VTSS_M_DEV1G_PCS_FX100_CFG_SD_SEL |
                    VTSS_M_DEV1G_PCS_FX100_CFG_SD_POL | VTSS_M_DEV1G_PCS_FX100_CFG_SD_ENA |
                    VTSS_M_DEV1G_PCS_FX100_CFG_RXBITSEL);

    } else if (pcs_usx) {
        /* USX PCS enable comes later */
    } else if (rgmii) {
        /* do nothing */
    } else {
        /* 1000BaseX PCS in SGMII or Serdes mode */

        /* Disable 100FX */
        REG_WRM_CLR(VTSS_DEV1G_PCS_FX100_CFG(tgt), VTSS_M_DEV1G_PCS_FX100_CFG_PCS_ENA);

        /* Choose SGMII or Serdes PCS mode */
        REG_WRM(VTSS_DEV1G_PCS1G_MODE_CFG(tgt), VTSS_F_DEV1G_PCS1G_MODE_CFG_SGMII_MODE_ENA(sgmii),
                VTSS_M_DEV1G_PCS1G_MODE_CFG_SGMII_MODE_ENA);

        if (sgmii) {
            /* Set whole register */
            REG_WR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt), VTSS_F_DEV1G_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(1));
        } else {
            /* Clear specific bit only */
            REG_WRM_CLR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt), VTSS_M_DEV1G_PCS1G_ANEG_CFG_SW_RESOLVE_ENA);
        }

        /* Signal Detect configuration */
        REG_WR(VTSS_DEV1G_PCS1G_SD_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_SD_CFG_SD_POL(conf->sd_active_high) |
                   VTSS_F_DEV1G_PCS1G_SD_CFG_SD_ENA(conf->sd_enable) |
                   VTSS_F_DEV1G_PCS1G_SD_CFG_SD_SEL(!conf->sd_internal));

        /* Enable PCS */
        REG_WR(VTSS_DEV1G_PCS1G_CFG(tgt), VTSS_F_DEV1G_PCS1G_CFG_PCS_ENA(1));

        if (sgmii && conf->if_type != VTSS_PORT_INTERFACE_SGMII_CISCO) {
            /* Disable SGMII aneg */
            REG_WR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt), 0);
        } else if (conf->if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
            /* Complete SGMII aneg */
            REG_WR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt),
                   VTSS_F_DEV1G_PCS1G_ANEG_CFG_ADV_ABILITY(0x0001) |
                       VTSS_F_DEV1G_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(1) |
                       VTSS_F_DEV1G_PCS1G_ANEG_CFG_ANEG_ENA(1) |
                       VTSS_F_DEV1G_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1));

            /* Clear the sticky bits */
            REG_RD(VTSS_DEV1G_PCS1G_STICKY(tgt), &value);
            REG_WR(VTSS_DEV1G_PCS1G_STICKY(tgt), value);
        }
    }

    /* Update vtss_state database accordingly */
    vtss_cil_port_clause_37_control_get(vtss_state, port_no, &vtss_state->port.clause_37[port_no]);
    if (!rgmii) {
        REG_WRM_CTL(VTSS_DEV1G_PCS1G_LB_CFG(tgt), conf->loop == VTSS_PORT_LOOP_PCS_HOST,
                    VTSS_M_DEV1G_PCS1G_LB_CFG_TBI_HOST_LB_ENA);
    }
    /* Always update FCS, needed for Frame Preemption */
    value = 1;
    if (FA_TGT) {
        if (vtss_state->misc.chip_id.revision == 0) {
            value = 0;
        }
    }

    if (rgmii) {
#if defined(VTSS_ARCH_LAN969X)
        /* Set Max Length */
        REG_WRM(VTSS_DEVRGMII_MAC_MAXLEN_CFG(tgt),
                VTSS_F_DEVRGMII_MAC_MAXLEN_CFG_MAX_LEN(conf->max_frame_length),
                VTSS_M_DEVRGMII_MAC_MAXLEN_CFG_MAX_LEN);

        /* Configure frame length check (from ethertype / length field) */
        REG_WRM(VTSS_DEVRGMII_MAC_ADV_CHK_CFG(tgt),
                VTSS_F_DEVRGMII_MAC_ADV_CHK_CFG_LEN_DROP_ENA(conf->frame_length_chk),
                VTSS_M_DEVRGMII_MAC_ADV_CHK_CFG_LEN_DROP_ENA);

        REG_WRM(VTSS_DEVRGMII_DEV_DBG_CFG(tgt), VTSS_F_DEVRGMII_DEV_DBG_CFG_FCS_UPDATE_CFG(value),
                VTSS_M_DEVRGMII_DEV_DBG_CFG_FCS_UPDATE_CFG);

#endif
    } else {
        /* Set Max Length */
        REG_WRM(VTSS_DEV1G_MAC_MAXLEN_CFG(tgt),
                VTSS_F_DEV1G_MAC_MAXLEN_CFG_MAX_LEN(conf->max_frame_length),
                VTSS_M_DEV1G_MAC_MAXLEN_CFG_MAX_LEN);

        /* Configure frame length check (from ethertype / length field) */
        REG_WRM(VTSS_DEV1G_MAC_ADV_CHK_CFG(tgt),
                VTSS_F_DEV1G_MAC_ADV_CHK_CFG_LEN_DROP_ENA(conf->frame_length_chk),
                VTSS_M_DEV1G_MAC_ADV_CHK_CFG_LEN_DROP_ENA);

        REG_WRM(VTSS_DEV1G_DEV_DBG_CFG(tgt), VTSS_F_DEV1G_DEV_DBG_CFG_FCS_UPDATE_CFG(value),
                VTSS_M_DEV1G_DEV_DBG_CFG_FCS_UPDATE_CFG);
    }

    /* Set DSM Watermark */
    VTSS_RC(fa_dsm_wm_set(vtss_state, port_no));

    /* Setup QoS - in reset */
    VTSS_RC(vtss_fa_qos_port_change(vtss_state, port_no, TRUE));

    /* Configure flow control */
    if (fa_port_fc_setup(vtss_state, port, conf) != VTSS_RC_OK) {
        VTSS_E("Could not configure FC port: %u", port);
    }

    /* Update policer flow control configuration */
    VTSS_RC(vtss_fa_port_policer_fc_set(vtss_state, port_no));

    if (rgmii) {
#if defined(VTSS_ARCH_LAN969X)
        /* Enable RGMII mode */
        VTSS_RC(fa_rgmii_setup(vtss_state, port_no, conf->if_type, speed));
        /* Enable MAC module */
        REG_WR(VTSS_DEVRGMII_MAC_ENA_CFG(tgt),
               VTSS_M_DEVRGMII_MAC_ENA_CFG_RX_ENA | VTSS_M_DEVRGMII_MAC_ENA_CFG_TX_ENA);

        /* Take MAC and  PCS (SGMII/Serdes or USX) clock out of reset */
        REG_WRM(VTSS_DEVRGMII_DEV_RST_CTRL(tgt),
                VTSS_F_DEVRGMII_DEV_RST_CTRL_SPEED_SEL(clk_spd) |
                    VTSS_F_DEVRGMII_DEV_RST_CTRL_MAC_TX_RST(0) |
                    VTSS_F_DEVRGMII_DEV_RST_CTRL_MAC_RX_RST(0),
                VTSS_M_DEVRGMII_DEV_RST_CTRL_SPEED_SEL | VTSS_M_DEVRGMII_DEV_RST_CTRL_MAC_TX_RST |
                    VTSS_M_DEVRGMII_DEV_RST_CTRL_MAC_RX_RST);
#endif
    } else {
        /* Enable MAC module */
        REG_WR(VTSS_DEV1G_MAC_ENA_CFG(tgt),
               VTSS_M_DEV1G_MAC_ENA_CFG_RX_ENA | VTSS_M_DEV1G_MAC_ENA_CFG_TX_ENA);

        /* Take MAC and  PCS (SGMII/Serdes or USX) clock out of reset */
        fa_dev1g_rst_ctrl(vtss_state, tgt, clk_spd, !pcs_usx, pcs_usx || rgmii, FALSE);
    }

    /* Must take the PCS out of reset for all 4 QSGMII instances */
    if (conf->if_type == VTSS_PORT_INTERFACE_QSGMII) {
        u32 p = (port / 4) * 4;
        for (u32 cnt = 0; cnt < 4; cnt++) {
            if (p + cnt == port) {
                continue;
            }
            REG_WRM(VTSS_DEV1G_DEV_RST_CTRL(VTSS_TO_DEV2G5(p + cnt)),
                    VTSS_F_DEV1G_DEV_RST_CTRL_PCS_TX_RST(0), VTSS_M_DEV1G_DEV_RST_CTRL_PCS_TX_RST);
        }
    }

    /* Core: Set the fwd_urgency and and enable port for frame transfer */
    REG_WRM(VTSS_QFWD_SWITCH_PORT_MODE(port),
            VTSS_F_QFWD_SWITCH_PORT_MODE_PORT_ENA(1) |
                VTSS_F_QFWD_SWITCH_PORT_MODE_FWD_URGENCY(port_fwd_urg(vtss_state, conf->speed)),
            VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA | VTSS_M_QFWD_SWITCH_PORT_MODE_FWD_URGENCY);

    /* Enable flowcontrol - must be done after the port is enabled */
    if (conf->flow_control.generate) {
        REG_WRM_SET(VTSS_QSYS_PAUSE_CFG(port), VTSS_M_QSYS_PAUSE_CFG_PAUSE_ENA);
    }

    if (pcs_usx) {
        /* Enable in-band-aneg, etc (config only needed once) */
        VTSS_RC(fa_usxgmii_enable(vtss_state, port_no, FALSE));

        /* Enable the usx extender (only for the last port in the QXGMII group
         * and only once) */
        VTSS_RC(fa_enable_usx_extender(vtss_state, port_no));
    }

    /* Setup QoS - out of reset */
    VTSS_RC(vtss_fa_qos_port_change(vtss_state, port_no, FALSE));

    VTSS_D("Chip port: %u (1G) is configured", port);
    return VTSS_RC_OK;
}

/* Configuration of the 5G, 10G and 25G devices (dev10G architecture) */
static vtss_rc fa_port_conf_high_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t  *conf = &vtss_state->port.conf[port_no];
    u32                port = VTSS_CHIP_PORT(port_no);
    u32                tgt = VTSS_TO_HIGH_DEV(port);
    u32                pcs = VTSS_TO_PCS_TGT(port);
    u32                clk_spd = 0, muxed_ports = 0, value, q;
    vtss_serdes_mode_t serdes_mode = VTSS_SERDES_MODE_SFI;
    BOOL               pcs_usx = FALSE;
    u32                sd_indx = vtss_fa_sd_lane_indx(vtss_state, port_no);

    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_SFI: serdes_mode = VTSS_SERDES_MODE_SFI; break;
    case VTSS_PORT_INTERFACE_USXGMII: // 1x10G device. 10M-10G.
        serdes_mode = VTSS_SERDES_MODE_USXGMII;
        pcs_usx = TRUE;
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: // 2x5G devices. Mode 'U', 10M-5G.
        serdes_mode = VTSS_SERDES_MODE_DXGMII_10G;
        muxed_ports = 1; // Dual
        pcs_usx = TRUE;
        break;
    default: {
    }
    }

    switch (conf->speed) {
    case VTSS_SPEED_25G:
    case VTSS_SPEED_10G:   clk_spd = 0; break;
    case VTSS_SPEED_5G:    clk_spd = 1; break;
    case VTSS_SPEED_2500M: clk_spd = 2; break;
    case VTSS_SPEED_1G:    clk_spd = 3; break;
    case VTSS_SPEED_100M:  clk_spd = 4; break;
    case VTSS_SPEED_10M:   clk_spd = 5; break;
    default:               {
    }
    }

    if (vtss_state->port.sd28_mode[sd_indx] == VTSS_SERDES_MODE_DISABLE) {
        /* Enable the Serdes if disabled (to get clock) */
        VTSS_RC(fa_serdes_set(vtss_state, port_no, serdes_mode));
        /* Port disable and flush procedure: */
        VTSS_RC(fa_port_flush(vtss_state, port_no, TRUE));
    } else {
        /* Port disable and flush procedure: */
        VTSS_RC(fa_port_flush(vtss_state, port_no, TRUE));
        /* Re-configure Serdes if needed */
        if (serdes_mode != vtss_state->port.sd28_mode[sd_indx] ||
            ((vtss_state->port.current_speed[port_no] != conf->speed) &&
             (vtss_state->port.sd28_mode[sd_indx] != VTSS_SERDES_MODE_USXGMII)) ||
            vtss_state->port.current_mt[port_no] != conf->serdes.media_type) {
            VTSS_RC(fa_serdes_set(vtss_state, port_no, serdes_mode));
        }
    }

    /* Disable ASM/DSM 1G/2Gg5 counters */
    REG_WRM(VTSS_ASM_PORT_CFG(port), VTSS_F_ASM_PORT_CFG_CSC_STAT_DIS(1),
            VTSS_M_ASM_PORT_CFG_CSC_STAT_DIS);

    REG_WRM(VTSS_DSM_BUF_CFG(port), VTSS_F_DSM_BUF_CFG_CSC_STAT_DIS(1),
            VTSS_M_DSM_BUF_CFG_CSC_STAT_DIS);

    if (conf->speed == VTSS_SPEED_25G) {
        /* Disable 10G PCS */
        REG_WRM_CLR(VTSS_PCS_10GBASE_R_PCS_CFG(pcs), VTSS_M_PCS_10GBASE_R_PCS_CFG_PCS_ENA);

        /* Handle Signal Detect in PCS */
        REG_WR(VTSS_DEV10G_PCS25G_SD_CFG(tgt),
               VTSS_F_DEV10G_PCS25G_SD_CFG_SD_SEL(!conf->sd_internal) |
                   VTSS_F_DEV10G_PCS25G_SD_CFG_SD_POL(conf->sd_active_high) |
                   VTSS_F_DEV10G_PCS25G_SD_CFG_SD_ENA(conf->sd_enable));

        /* Enable 25G PCS */
        REG_WRM(VTSS_DEV10G_PCS25G_CFG(tgt), VTSS_F_DEV10G_PCS25G_CFG_PCS25G_ENA(1),
                VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
    } else {
        if (pcs_usx) {
            /* Setup USXGMII mode (once) */
            VTSS_RC(fa_usxgmii_enable(vtss_state, port_no, TRUE));
        } else {
            /* The PCS_BR block below handles 5G/10G speeds for all primary
             * devices */

            /* Handle Signal Detect in PCS */
            REG_WR(VTSS_PCS_10GBASE_R_PCS_SD_CFG(pcs),
                   VTSS_F_PCS_10GBASE_R_PCS_SD_CFG_SD_POL(conf->sd_active_high) |
                       VTSS_F_PCS_10GBASE_R_PCS_SD_CFG_SD_SEL(!conf->sd_internal) |
                       VTSS_F_PCS_10GBASE_R_PCS_SD_CFG_SD_ENA(conf->sd_enable));

            /* Enable 10G PCS  */
            REG_WRM(VTSS_PCS_10GBASE_R_PCS_CFG(pcs), VTSS_F_PCS_10GBASE_R_PCS_CFG_PCS_ENA(1),
                    VTSS_M_PCS_10GBASE_R_PCS_CFG_PCS_ENA);
        }
    }

    /* MAC Host loopback */
    REG_WRM(VTSS_DEV10G_MAC_LB_CFG(tgt),
            VTSS_F_DEV10G_MAC_LB_CFG_XGMII_HOST_LB_ENA(conf->loop == VTSS_PORT_LOOP_PCS_HOST),
            VTSS_M_DEV10G_MAC_LB_CFG_XGMII_HOST_LB_ENA);

    /* Set Max Length and maximum tags allowed */
    REG_WRM(VTSS_DEV10G_MAC_MAXLEN_CFG(tgt),
            VTSS_F_DEV10G_MAC_MAXLEN_CFG_MAX_LEN(conf->max_frame_length),
            VTSS_M_DEV10G_MAC_MAXLEN_CFG_MAX_LEN);

    /* Configure framelength check (from ethertype / length field) */
    REG_WRM(VTSS_DEV10G_MAC_ADV_CHK_CFG(tgt),
            VTSS_F_DEV10G_MAC_ADV_CHK_CFG_INR_ERR_ENA(conf->frame_length_chk),
            VTSS_M_DEV10G_MAC_ADV_CHK_CFG_INR_ERR_ENA);

    /* Set DSM Watermark */
    VTSS_RC(fa_dsm_wm_set(vtss_state, port_no));

    /* Always update FCS, needed for Frame Preemption */
    value = 2;
    if (FA_TGT) {
        if (vtss_state->misc.chip_id.revision == 0) {
            value = 0;
        }
    }
    REG_WRM(VTSS_DEV10G_DEV_MISC_CFG(tgt), VTSS_F_DEV10G_DEV_MISC_CFG_TX_FCS_UPDATE_SEL(value),
            VTSS_M_DEV10G_DEV_MISC_CFG_TX_FCS_UPDATE_SEL);

    /* Setup QoS - in reset */
    VTSS_RC(vtss_fa_qos_port_change(vtss_state, port_no, TRUE));

    /* Configure flow control */
    if (fa_port_fc_setup(vtss_state, port, conf) != VTSS_RC_OK) {
        VTSS_E("Could not configure FC port: %u", port);
    }

    // PFC counter mode
    value = 0;
    for (q = 0; q < VTSS_PRIOS; q++) {
        if (conf->flow_control.pfc[q]) {
            value = 1;
            break;
        }
    }
    REG_WR(VTSS_DEV10G_PFC_PAUSE_MODE_CTRL(tgt),
           VTSS_F_DEV10G_PFC_PAUSE_MODE_CTRL_PFC_PAUSE_MODE_SELECT(value));

    /* Update policer flow control configuration */
    VTSS_RC(vtss_fa_port_policer_fc_set(vtss_state, port_no));

    /* Enable MAC module */
    REG_WR(VTSS_DEV10G_MAC_ENA_CFG(tgt),
           VTSS_M_DEV10G_MAC_ENA_CFG_RX_ENA | VTSS_M_DEV10G_MAC_ENA_CFG_TX_ENA);

    /* Take MAC and PCS out of reset */
    REG_WRM(VTSS_DEV10G_DEV_RST_CTRL(tgt),
            VTSS_F_DEV10G_DEV_RST_CTRL_MUXED_USXGMII_NETWORK_PORTS(muxed_ports) |
                VTSS_F_DEV10G_DEV_RST_CTRL_PCS_RX_RST(0) |
                VTSS_F_DEV10G_DEV_RST_CTRL_PCS_TX_RST(0) |
                VTSS_F_DEV10G_DEV_RST_CTRL_MAC_RX_RST(0) |
                VTSS_F_DEV10G_DEV_RST_CTRL_MAC_TX_RST(0) |
                VTSS_F_DEV10G_DEV_RST_CTRL_SPEED_SEL(clk_spd),
            VTSS_M_DEV10G_DEV_RST_CTRL_MUXED_USXGMII_NETWORK_PORTS |
                VTSS_M_DEV10G_DEV_RST_CTRL_PCS_RX_RST | VTSS_M_DEV10G_DEV_RST_CTRL_PCS_TX_RST |
                VTSS_M_DEV10G_DEV_RST_CTRL_MAC_RX_RST | VTSS_M_DEV10G_DEV_RST_CTRL_MAC_TX_RST |
                VTSS_M_DEV10G_DEV_RST_CTRL_SPEED_SEL);

    REG_WRM(VTSS_QFWD_SWITCH_PORT_MODE(port),
            VTSS_F_QFWD_SWITCH_PORT_MODE_PORT_ENA(1) | VTSS_F_QFWD_SWITCH_PORT_MODE_YEL_RSRVD(0xf) |
                VTSS_F_QFWD_SWITCH_PORT_MODE_FWD_URGENCY(port_fwd_urg(vtss_state, conf->speed)),
            VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA |
                VTSS_M_QFWD_SWITCH_PORT_MODE_YEL_RSRVD | // An AFI bug makes this
                                                         // required. See bz.24445
                VTSS_M_QFWD_SWITCH_PORT_MODE_FWD_URGENCY);

    /* Enable flowcontrol - must be done after the port is enabled */
    if (conf->flow_control.generate) {
        REG_WRM_SET(VTSS_QSYS_PAUSE_CFG(port), VTSS_M_QSYS_PAUSE_CFG_PAUSE_ENA);
    }

    /* Setup QoS - out of reset */
    VTSS_RC(vtss_fa_qos_port_change(vtss_state, port_no, FALSE));

    VTSS_D("chip port: %u (10G),is configured", port);

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_PORT_DYNAMIC)
static int fa_multi_serdes_chk(vtss_serdes_mode_t new_sd, vtss_serdes_mode_t old_sd)
{
    vtss_serdes_mode_t a, b;

    if (new_sd == old_sd || old_sd == VTSS_SERDES_MODE_DISABLE) {
        return 0;
    }

    for (int i = 0; i < 2; i++) {
        a = i == 0 ? old_sd : new_sd;
        b = i == 0 ? new_sd : old_sd;

        if ((a == VTSS_SERDES_MODE_QXGMII || a == VTSS_SERDES_MODE_USGMII ||
             a == VTSS_SERDES_MODE_QSGMII) &&
            (b != VTSS_SERDES_MODE_QXGMII && b != VTSS_SERDES_MODE_USGMII &&
             b != VTSS_SERDES_MODE_QSGMII)) {
            return 1;
        }
    }

    return 0;
}

static vtss_rc fa_calendar_check(vtss_state_t        *vtss_state,
                                 const vtss_port_no_t port_no,
                                 vtss_serdes_mode_t   old_sd)
{
    vtss_port_interface_t new_if_type = vtss_state->port.conf[port_no].if_type;
    u32                   sd, new_sd_idx = vtss_fa_sd_lane_indx(vtss_state, port_no);
    vtss_serdes_mode_t    new_sd = vtss_state->port.sd28_mode[new_sd_idx];
    vtss_port_interface_t cur_if;
    u32                   st;

    if (!fa_multi_serdes_chk(new_sd, old_sd)) {
        // Calender check only needed for single to multi port serdes change
        return VTSS_RC_OK;
    }

    /* Run through all ports for this serdes and reset BW to zero */
    for (u32 p = VTSS_PORT_NO_START; p < vtss_state->port_count; p++) {
        cur_if = vtss_state->port.conf[p].if_type;
        vtss_state->port.conf[p].if_type = VTSS_PORT_INTERFACE_QSGMII;
        if (vtss_fa_port2sd(vtss_state, p, &sd, &st) != VTSS_RC_OK) {
            vtss_state->port.conf[p].if_type = cur_if;
            continue;
        }
        sd += (st == FA_SERDES_TYPE_10G) ? RT_SERDES_10G_START : RT_SERDES_25G_START;
        if (sd == new_sd_idx) {
            if (p != port_no) {
                vtss_state->port.conf[p].if_type = VTSS_PORT_INTERFACE_NO_CONNECTION;
            } else {
                vtss_state->port.conf[p].if_type = cur_if;
            }
            vtss_state->port.map[p].max_bw = VTSS_BW_NONE;
        } else {
            vtss_state->port.conf[p].if_type = cur_if;
        }
    }
    /* Apply the reduced BW to cell calendar */
    VTSS_RC(fa_cell_calendar_auto(vtss_state));

    /* Set the new BW requirements for the ports that belong to this serdes */
    for (u32 p = VTSS_PORT_NO_START; p < vtss_state->port_count; p++) {
        cur_if = vtss_state->port.conf[p].if_type;
        vtss_state->port.conf[p].if_type = new_if_type;
        if (vtss_fa_port2sd(vtss_state, p, &sd, &st) != VTSS_RC_OK) {
            vtss_state->port.conf[p].if_type = cur_if;
            continue;
        }
        sd += (st == FA_SERDES_TYPE_10G) ? RT_SERDES_10G_START : RT_SERDES_25G_START;

        if (sd == new_sd_idx) {
            switch (new_if_type) {
            case VTSS_PORT_INTERFACE_QSGMII:     vtss_state->port.map[p].max_bw = VTSS_BW_1G; break;
            case VTSS_PORT_INTERFACE_QXGMII:     vtss_state->port.map[p].max_bw = VTSS_BW_2G5; break;
            case VTSS_PORT_INTERFACE_DXGMII_10G: vtss_state->port.map[p].max_bw = VTSS_BW_5G; break;
            case VTSS_PORT_INTERFACE_SFI:
                if (vtss_state->port.conf[p].speed == VTSS_SPEED_5G) {
                    vtss_state->port.map[p].max_bw = VTSS_BW_5G;
                } else {
                    vtss_state->port.map[p].max_bw = VTSS_BW_10G;
                }
                break;
            default: VTSS_E("Should not occur\n");
            }
        }
        vtss_state->port.conf[p].if_type = cur_if;
    }
    /* Apply the new BW to cell and taxi calendar */
    VTSS_RC(fa_cell_calendar_auto(vtss_state));
    return fa_dsm_calc_and_apply_calendar(
        vtss_state, TRUE /* force a new calendar because the port map has changed */);
}
#endif /* defined(VTSS_FEATURE_PORT_DYNAMIC) */

vtss_rc vtss_cil_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    u32               port = VTSS_CHIP_PORT(port_no), mask;
    BOOL              use_primary_dev = fa_is_high_speed_device(vtss_state, port_no);
#if defined(VTSS_FEATURE_PORT_DYNAMIC)
    u32                sd_indx = vtss_fa_sd_lane_indx(vtss_state, port_no);
    vtss_serdes_mode_t old_sd = vtss_state->port.sd28_mode[sd_indx];
#endif

    /* If bulk config is enabled then chip config is skipped */
    if (vtss_state->port.bulk_state == VTSS_PORT_BULK_ENABLED) {
        vtss_state->port.bulk_port_mask |= VTSS_BIT64(port_no);
        return VTSS_RC_OK;
    }

    VTSS_I("port_no:%d (port:%d, dev%s) if:%s, spd:%s/%s, shutdown:%d, media_type:%d", port_no,
           port,
           VTSS_PORT_IS_25G(port)   ? "25G"
           : VTSS_PORT_IS_10G(port) ? "10G"
           : VTSS_PORT_IS_5G(port)  ? "5G"
                                    : "2G5",
           vtss_port_if_txt(conf->if_type), vtss_port_spd_txt(conf->speed),
           conf->fdx ? "FDX" : "HDX", conf->power_down, conf->serdes.media_type);

    if (!fa_vrfy_spd_iface(vtss_state, port_no, conf->if_type, conf->speed, conf->fdx)) {
        return VTSS_RC_ERROR;
    }

    /* All high speed (>2G5) ports have a shadow 2G5 device. */
    /* Only one of them can be active and attached to the switch core at a time.
     */
    /* Every time the device changes, a port flush (shut down) must be performed
     * on the DEV that is not active. */
    if (fa_change_device(vtss_state, port_no)) {
        VTSS_I("port_no:%d (chip port:%d) shutdown the %s device", port_no, port,
               use_primary_dev ? "shadow" : "primary");
        /* Shutdown the not-in-use device */
        VTSS_RC(fa_port_flush(vtss_state, port_no, !use_primary_dev));

        if (LA_TGT) {
            // On Laguna, we might need to change DSM Taxi calendar when
            // enabling or disabling a shadow device.
            VTSS_RC(fa_dsm_calc_and_apply_calendar(vtss_state,
                                                   FALSE /* don't force a new calendar */));
        }

        /* Enable/disable shadow device */
        if (VTSS_PORT_IS_5G(port)) {
#if !defined(VTSS_ARCH_LAIKA)
            mask = VTSS_BIT(fla_port_dev_index(vtss_state, port, TRUE));
            REG_WRM(VTSS_PORT_CONF_DEV5G_MODES, use_primary_dev ? 0 : mask, mask);
#endif
        } else if (VTSS_PORT_IS_10G(port)) {
            mask = VTSS_BIT(fla_port_dev_index(vtss_state, port, TRUE));
            REG_WRM(VTSS_PORT_CONF_DEV10G_MODES, use_primary_dev ? 0 : mask, mask);
        } else if (VTSS_PORT_IS_25G(port)) {
#if defined(VTSS_FEATURE_SD_25G)
            mask = VTSS_BIT(fla_port_dev_index(vtss_state, port, TRUE));
            REG_WRM(VTSS_PORT_CONF_DEV25G_MODES, use_primary_dev ? 0 : mask, mask);
#endif
        }
        REG_WRM(VTSS_DSM_DEV_TX_STOP_WM_CFG(port),
                VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA(!use_primary_dev),
                VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA);

        /* Read port counters ignoring updates */
        VTSS_RC(fa_port_counters(vtss_state, port_no, NULL, VTSS_COUNTER_CMD_REBASE));
    }
    /* Configure USXGMII/USGMII/QSGMII port muxing (if needed) */
    VTSS_RC(port_mux_set(vtss_state, port_no));
    /* Configure MAC vlan awareness */
    VTSS_RC(vtss_fa_port_max_tags_set(vtss_state, port_no));
    /* Enable/disable serdes power saving mode  */
    VTSS_RC(fa_sd_power_save(vtss_state, port_no, conf->power_down));
    if (conf->power_down) {
        // No more config needed when in power_down
        return VTSS_RC_OK;
    }

    if (use_primary_dev) {
        VTSS_RC(fa_port_conf_high_set(vtss_state, port_no));
    } else {
        VTSS_RC(fa_port_conf_2g5_set(vtss_state, port_no));
    }

#if defined(VTSS_FEATURE_SYNCE)
    if (vtss_state->vtss_features[FEATURE_SYNCE]) {
        vtss_synce_clk_port_t clk_port;
        /* Some changes in port configuration require that the Synce input
         * configuration must be updated */
        for (clk_port = 0; clk_port < VTSS_SYNCE_CLK_PORT_ARRAY_SIZE; clk_port++) {
            if ((vtss_state->synce.in_conf[clk_port].port_no == port_no) &&
                ((vtss_state->port.current_speed[port_no] |= conf->speed) ||
                 (vtss_state->port.current_mt[port_no] = conf->serdes.media_type))) {
                (void)vtss_cil_synce_clock_in_set(vtss_state, clk_port);
            }
        }
    }
#endif
    vtss_state->port.current_speed[port_no] = vtss_state->port.conf[port_no].speed;
    vtss_state->port.current_if_type[port_no] = vtss_state->port.conf[port_no].if_type;
    vtss_state->port.current_mt[port_no] = vtss_state->port.conf[port_no].serdes.media_type;
#if defined(VTSS_FEATURE_QOS_TAS)
    /* Time Aware Scheduling setup depends on link speed */
    VTSS_RC(vtss_fa_qos_tas_port_conf_update(vtss_state, port_no));
#endif

#if defined(VTSS_FEATURE_PORT_KR_IRQ)
    VTSS_RC(fa_port_kr_speed_set(vtss_state, port_no));
#endif
#if defined(VTSS_FEATURE_PORT_DYNAMIC)
    VTSS_RC(fa_calendar_check(vtss_state, port_no, old_sd));
#endif

    return VTSS_RC_OK;
}

/* Get status of the SFI and 100FX ports. */
/* Note: Status for SERDES is handled through clause_37_status_get. Status for
 * SGMII is retrieved from the Phy */
vtss_rc vtss_cil_port_status_get(vtss_state_t             *vtss_state,
                                 const vtss_port_no_t      port_no,
                                 vtss_port_status_t *const status)
{
    u32               value, val2, rx_link;
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    u32               tgt = vtss_fa_dev_tgt(vtss_state, port_no);
    u32               sd_indx = 0, sd_type, sd_tgt;
    BOOL              analog_sd = TRUE, kr_aneg_ena = FALSE;

    if (conf->power_down) {
        /* Disabled port is considered down */
        return VTSS_RC_OK;
    }
    (void)val2;
    switch (vtss_state->port.conf[port_no].if_type) {

    case VTSS_PORT_INTERFACE_100FX:
        /* Get the PCS status  */
        REG_RD(VTSS_DEV1G_PCS_FX100_STATUS(tgt), &value);

        /* Link has been down if the are any error stickies */
        status->link_down = VTSS_X_DEV1G_PCS_FX100_STATUS_SYNC_LOST_STICKY(value) ||
                            VTSS_X_DEV1G_PCS_FX100_STATUS_FEF_FOUND_STICKY(value) ||
                            VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_ERROR_STICKY(value) ||
                            VTSS_X_DEV1G_PCS_FX100_STATUS_SSD_ERROR_STICKY(value) ||
                            VTSS_X_DEV1G_PCS_FX100_STATUS_FEF_STATUS(value);

        if (status->link_down) {
            /* Reset the serdes for re-calibration */
#if !defined(VTSS_ARCH_LAIKA)
            u32 indx = vtss_fa_sd_lane_indx(vtss_state, port_no);
            u32 sd_lane_tgt = VTSS_TO_SD_LANE(indx);
            REG_WRM(VTSS_SD_LANE_TARGET_SD_LANE_CFG(sd_lane_tgt),
                    VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_LANE_RX_RST(1),
                    VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_LANE_RX_RST);
            VTSS_MSLEEP(3);
            REG_WRM(VTSS_SD_LANE_TARGET_SD_LANE_CFG(sd_lane_tgt),
                    VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_LANE_RX_RST(0),
                    VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_LANE_RX_RST);
            VTSS_MSLEEP(1);

#endif
            /* Clear the stickies and re-read */
            REG_WR(VTSS_DEV1G_PCS_FX100_STATUS(tgt), value);
            VTSS_MSLEEP(1);
            REG_RD(VTSS_DEV1G_PCS_FX100_STATUS(tgt), &value);
        }
        /* Link=1 if sync status=1 and no error stickies after a clear */
        status->link = VTSS_X_DEV1G_PCS_FX100_STATUS_SYNC_STATUS(value) &&
                       !VTSS_X_DEV1G_PCS_FX100_STATUS_SYNC_LOST_STICKY(value) &&
                       !VTSS_X_DEV1G_PCS_FX100_STATUS_FEF_FOUND_STICKY(value) &&
                       !VTSS_X_DEV1G_PCS_FX100_STATUS_PCS_ERROR_STICKY(value) &&
                       !VTSS_X_DEV1G_PCS_FX100_STATUS_SSD_ERROR_STICKY(value) &&
                       !VTSS_X_DEV1G_PCS_FX100_STATUS_FEF_STATUS(value);

        status->speed = VTSS_SPEED_100M;
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        /* Get the PCS status */
        REG_RD(VTSS_DEV1G_PCS1G_LINK_STATUS(tgt), &value);
        status->link = REG_BF(DEV1G_PCS1G_LINK_STATUS_LINK_STATUS, value) &&
                       REG_BF(DEV1G_PCS1G_LINK_STATUS_SYNC_STATUS, value);
        REG_RD(VTSS_DEV1G_PCS1G_STICKY(tgt), &value);
        status->link_down = REG_BF(DEV1G_PCS1G_STICKY_LINK_DOWN_STICKY, value);
        if (status->link_down) {
            /* The link has been down. Clear the sticky bit */
            REG_WRM_SET(VTSS_DEV1G_PCS1G_STICKY(tgt), VTSS_M_DEV1G_PCS1G_STICKY_LINK_DOWN_STICKY);
        }
        status->speed = VTSS_SPEED_2500M;
        break;
    case VTSS_PORT_INTERFACE_SFI:
        (void)sd_tgt;
        VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type));
        if (sd_type == FA_SERDES_TYPE_25G) {
#if defined(VTSS_FEATURE_SD_25G)
            sd_tgt = VTSS_TO_SD25G_LANE(sd_indx);
            /* Check the analog loss of signal detect of the 25G-Serdes */
            REG_RD(VTSS_SD25G_TARGET_LANE_DE(sd_tgt), &val2);
            analog_sd = !VTSS_X_SD25G_TARGET_LANE_DE_LN_PMA_RXEI(val2); // 0 = link
#endif
        } else {
            if (sd_type == FA_SERDES_TYPE_6G) {
                sd_tgt = VTSS_TO_SD6G_LANE(sd_indx);
            } else {
                sd_tgt = VTSS_TO_SD10G_LANE(sd_indx);
            }
#if !defined(VTSS_ARCH_LAIKA)
            /* Check the analog loss of signal detect of the 10G-Serdes */
            REG_RD(VTSS_SD10G_LANE_TARGET_LANE_DF(sd_tgt), &val2);
            analog_sd = !VTSS_X_SD10G_LANE_TARGET_LANE_DF_PMA2PCS_RXEI_FILTERED(val2); // 0 = link
#endif
        }

        /* MAC10G Tx Monitor Sticky bit Register */
        REG_RD(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), &value);
        rx_link = value & ~VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY;
        if (value != VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY) {
            /* The link is or has been down. Clear the sticky bit */
            status->link_down = 1;
            REG_WR(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), 0xFFFFFFFF);
            REG_RD(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), &value);
        }

        if ((sd_type == FA_SERDES_TYPE_25G) && (conf->speed == VTSS_SPEED_25G)) {
            /* PCS and Analog Macro SD must agree on link status */
            if (VTSS_BOOL(value == VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY) &&
                analog_sd) {
                status->link = TRUE;
                vtss_state->port.link[port_no] = TRUE;
            } else if (VTSS_BOOL(value != VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY) &&
                       !analog_sd) {
                status->link = FALSE;
                vtss_state->port.link[port_no] = FALSE;
            } else {
                status->link = vtss_state->port.link[port_no];
            }
        } else {
            /* Combine status from PCS and Analog Macro */
            status->link =
                VTSS_BOOL(value == VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY) &&
                analog_sd;
        }

#if defined(VTSS_FEATURE_PORT_KR_IRQ)
        if (vtss_state->port.kr_conf[port_no].aneg.enable) {
            kr_aneg_ena = TRUE;
        }
#endif
        /* Perform CTLE training at link-up for 10G/25G when KR-Aneg is not
         * enabled */
        if (!kr_aneg_ena && (conf->speed == VTSS_SPEED_10G || conf->speed == VTSS_SPEED_25G)) {
            if (rx_link != VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY) {
                vtss_state->port.ctle_done[port_no] = FALSE;
            }
            if (status->link && !vtss_state->port.ctle_done[port_no]) {
                if (vtss_cil_port_kr_ctle_adjust(vtss_state, port_no) == VTSS_RC_OK) {
                    VTSS_NSLEEP(300000); /* wait 300us while the link stabilize */
                    REG_WR(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), 0xFFFFFFFF);
                    vtss_state->port.ctle_done[port_no] = TRUE;
                }
            }
        }
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
        if (kr_aneg_ena) {
            /* UNG_FIREANT-91 workaround */
            (void)fa_kr_state_chk(vtss_state, port_no);
        }
#endif
        status->speed = conf->speed;
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        status->link = 0;
        status->link_down = 0;
        break;
    default: VTSS_E("Status not supported for port: %u", port_no); return VTSS_RC_ERROR;
    }
    status->fdx = conf->fdx;
    return VTSS_RC_OK;
}

#define REG_CNT_1G_ONE(name, i, cnt, cmd)                                                          \
    {                                                                                              \
        u32 value;                                                                                 \
        REG_RD(VTSS_ASM_##name##_CNT(i), &value);                                                  \
        vtss_cmn_counter_32_cmd(value, cnt, cmd);                                                  \
    }

#define REG_CNT_10G_ONE(name, i, cnt, cmd)                                                         \
    {                                                                                              \
        u32 value;                                                                                 \
        REG_RD(VTSS_DEV10G_##name##_CNT(i), &value);                                               \
        vtss_cmn_counter_32_cmd(value, cnt, cmd);                                                  \
    }

#define REG_CNT_10G(name, i, cnt, cmd)                                                             \
    {                                                                                              \
        u32 emac, pmac;                                                                            \
        REG_RD(VTSS_DEV10G_##name##_CNT(i), &emac);                                                \
        REG_RD(VTSS_DEV10G_PMAC_##name##_CNT(i), &pmac);                                           \
        vtss_cmn_counter_dual_cmd(emac, pmac, cnt, cmd);                                           \
    }

#define REG_CNT_ANA_AC(name, cnt, cmd)                                                             \
    {                                                                                              \
        u32 value;                                                                                 \
        REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_##name, &value);                                           \
        vtss_cmn_counter_32_cmd(value, cnt, cmd);                                                  \
    }

#define REG_CNT_1G(name, i, cnt, cmd)                                                              \
    {                                                                                              \
        u32 emac, pmac;                                                                            \
        REG_RD(VTSS_ASM_##name##_CNT(i), &emac);                                                   \
        REG_RD(VTSS_ASM_PMAC_##name##_CNT(i), &pmac);                                              \
        vtss_cmn_counter_dual_cmd(emac, pmac, cnt, cmd);                                           \
    }

#define CNT_SUM(cnt) (cnt.value)

static vtss_rc vtss_fa_qsys_counter_update(vtss_state_t        *vtss_state,
                                           u32                 *addr,
                                           vtss_chip_counter_t *counter,
                                           vtss_counter_cmd_t   cmd)
{
    u32 value;

    REG_RD(VTSS_XQS_CNT(*addr), &value);
    *addr = (*addr + 1); /* Next counter address */
    vtss_cmn_counter_32_cmd(value, counter, cmd);

    return VTSS_RC_OK;
}

/* Index of ANA_AC port counters */
#define REG_CNT_ANA_AC_PORT_FILTER        0
#define REG_CNT_ANA_AC_PORT_POLICER_DROPS 1

/* Index of ANA_AC queue counters */
#define REG_CNT_ANA_AC_QUEUE_PRIO 0

static vtss_rc fa_port_counters_chip(vtss_state_t               *vtss_state,
                                     vtss_port_no_t              port_no,
                                     vtss_port_fa_counters_t    *c,
                                     vtss_port_counters_t *const counters,
                                     vtss_counter_cmd_t          cmd)
{
    u32                            i, addr, port, val;
    vtss_port_counter_t            rx_errors;
    vtss_port_rmon_counters_t     *rmon;
    vtss_port_if_group_counters_t *if_group;
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    vtss_port_ethernet_like_counters_t *elike;
#endif
    vtss_port_proprietary_counters_t *prop;

    if (port_no >= vtss_state->port_count) {
        /* CPU/virtual port */
        port = (RT_CHIP_PORT_CPU + port_no - vtss_state->port_count);
    } else if (!fa_is_high_speed_device(vtss_state, port_no)) {
        /* ASM counters */
        port = VTSS_CHIP_PORT(port_no);
        i = port;
        REG_CNT_1G_ONE(RX_IN_BYTES, i, &c->rx_in_bytes, cmd);
        REG_CNT_1G(RX_SYMBOL_ERR, i, &c->rx_symbol_err, cmd);
        REG_CNT_1G(RX_PAUSE, i, &c->rx_pause, cmd);
        REG_CNT_1G(RX_UNSUP_OPCODE, i, &c->rx_unsup_opcode, cmd);
        REG_CNT_1G(RX_OK_BYTES, i, &c->rx_ok_bytes, cmd);
        REG_CNT_1G(RX_BAD_BYTES, i, &c->rx_bad_bytes, cmd);
        REG_CNT_1G(RX_UC, i, &c->rx_unicast, cmd);
        REG_CNT_1G(RX_MC, i, &c->rx_multicast, cmd);
        REG_CNT_1G(RX_BC, i, &c->rx_broadcast, cmd);
        REG_CNT_1G(RX_CRC_ERR, i, &c->rx_crc_err, cmd);
        REG_CNT_1G(RX_UNDERSIZE, i, &c->rx_undersize, cmd);
        REG_CNT_1G(RX_FRAGMENTS, i, &c->rx_fragments, cmd);
        REG_CNT_1G(RX_IN_RANGE_LEN_ERR, i, &c->rx_in_range_len_err, cmd);
        REG_CNT_1G(RX_OUT_OF_RANGE_LEN_ERR, i, &c->rx_out_of_range_len_err, cmd);
        REG_RD(VTSS_ASM_RX_OVERSIZE_CNT(i), &val);
        vtss_cmn_counter_dual_cmd(val, 0, &c->rx_oversize, cmd);
        REG_CNT_1G(RX_JABBERS, i, &c->rx_jabbers, cmd);
        REG_CNT_1G(RX_SIZE64, i, &c->rx_size64, cmd);
        REG_CNT_1G(RX_SIZE65TO127, i, &c->rx_size65_127, cmd);
        REG_CNT_1G(RX_SIZE128TO255, i, &c->rx_size128_255, cmd);
        REG_CNT_1G(RX_SIZE256TO511, i, &c->rx_size256_511, cmd);
        REG_CNT_1G(RX_SIZE512TO1023, i, &c->rx_size512_1023, cmd);
        REG_CNT_1G(RX_SIZE1024TO1518, i, &c->rx_size1024_1518, cmd);
        REG_CNT_1G(RX_SIZE1519TOMAX, i, &c->rx_size1519_max, cmd);

        REG_CNT_1G_ONE(TX_OUT_BYTES, i, &c->tx_out_bytes, cmd);
        REG_CNT_1G(TX_PAUSE, i, &c->tx_pause, cmd);
        REG_CNT_1G(TX_OK_BYTES, i, &c->tx_ok_bytes, cmd);
        REG_CNT_1G(TX_UC, i, &c->tx_unicast, cmd);
        REG_CNT_1G(TX_MC, i, &c->tx_multicast, cmd);
        REG_CNT_1G(TX_BC, i, &c->tx_broadcast, cmd);
        REG_CNT_1G(TX_SIZE64, i, &c->tx_size64, cmd);
        REG_CNT_1G(TX_SIZE65TO127, i, &c->tx_size65_127, cmd);
        REG_CNT_1G(TX_SIZE128TO255, i, &c->tx_size128_255, cmd);
        REG_CNT_1G(TX_SIZE256TO511, i, &c->tx_size256_511, cmd);
        REG_CNT_1G(TX_SIZE512TO1023, i, &c->tx_size512_1023, cmd);
        REG_CNT_1G(TX_SIZE1024TO1518, i, &c->tx_size1024_1518, cmd);
        REG_CNT_1G(TX_SIZE1519TOMAX, i, &c->tx_size1519_max, cmd);
        REG_CNT_1G_ONE(TX_MULTI_COLL, i, &c->tx_multi_coll, cmd);
        REG_CNT_1G_ONE(TX_LATE_COLL, i, &c->tx_late_coll, cmd);
        REG_CNT_1G_ONE(TX_XCOLL, i, &c->tx_xcoll, cmd);
        REG_CNT_1G_ONE(TX_DEFER, i, &c->tx_defer, cmd);
        REG_CNT_1G_ONE(TX_XDEFER, i, &c->tx_xdefer, cmd);
        REG_CNT_1G_ONE(TX_BACKOFF1, i, &c->tx_backoff1, cmd);
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        if (vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION]) {
            REG_CNT_1G_ONE(MM_RX_ASSEMBLY_ERR, i, &c->rx_mm_assembly_errors, cmd);
            REG_CNT_1G_ONE(MM_RX_SMD_ERR, i, &c->rx_mm_smd_errors, cmd);
            REG_CNT_1G_ONE(MM_RX_ASSEMBLY_OK, i, &c->rx_mm_assembly_ok, cmd);
            REG_CNT_1G_ONE(MM_RX_MERGE_FRAG, i, &c->rx_mm_fragments, cmd);
            REG_CNT_1G_ONE(MM_TX_PFRAGMENT, i, &c->tx_mm_fragments, cmd);
        }
#endif
    } else {
        /* DEV5G/DEV10G/DEV25G counters */
        port = VTSS_CHIP_PORT(port_no);
        i = VTSS_TO_HIGH_DEV(port);
        REG_CNT_10G_ONE(RX_IN_BYTES, i, &c->rx_in_bytes, cmd);
        REG_CNT_10G(RX_SYMBOL_ERR, i, &c->rx_symbol_err, cmd);
        REG_CNT_10G(RX_PAUSE, i, &c->rx_pause, cmd);
        REG_CNT_10G(RX_UNSUP_OPCODE, i, &c->rx_unsup_opcode, cmd);
        REG_CNT_10G(RX_OK_BYTES, i, &c->rx_ok_bytes, cmd);
        REG_CNT_10G(RX_BAD_BYTES, i, &c->rx_bad_bytes, cmd);
        REG_CNT_10G(RX_UC, i, &c->rx_unicast, cmd);
        REG_CNT_10G(RX_MC, i, &c->rx_multicast, cmd);
        REG_CNT_10G(RX_BC, i, &c->rx_broadcast, cmd);
        REG_CNT_10G(RX_CRC_ERR, i, &c->rx_crc_err, cmd);
        REG_CNT_10G(RX_UNDERSIZE, i, &c->rx_undersize, cmd);
        REG_CNT_10G(RX_FRAGMENTS, i, &c->rx_fragments, cmd);
        REG_CNT_10G(RX_IN_RANGE_LEN_ERR, i, &c->rx_in_range_len_err, cmd);
        REG_CNT_10G(RX_OUT_OF_RANGE_LEN_ERR, i, &c->rx_out_of_range_len_err, cmd);
        REG_CNT_10G(RX_OVERSIZE, i, &c->rx_oversize, cmd);
        REG_CNT_10G(RX_JABBERS, i, &c->rx_jabbers, cmd);
        REG_CNT_10G(RX_SIZE64, i, &c->rx_size64, cmd);
        REG_CNT_10G(RX_SIZE65TO127, i, &c->rx_size65_127, cmd);
        REG_CNT_10G(RX_SIZE128TO255, i, &c->rx_size128_255, cmd);
        REG_CNT_10G(RX_SIZE256TO511, i, &c->rx_size256_511, cmd);
        REG_CNT_10G(RX_SIZE512TO1023, i, &c->rx_size512_1023, cmd);
        REG_CNT_10G(RX_SIZE1024TO1518, i, &c->rx_size1024_1518, cmd);
        REG_CNT_10G(RX_SIZE1519TOMAX, i, &c->rx_size1519_max, cmd);

        REG_CNT_10G_ONE(TX_OUT_BYTES, i, &c->tx_out_bytes, cmd);
        REG_CNT_10G(TX_PAUSE, i, &c->tx_pause, cmd);
        REG_CNT_10G(TX_OK_BYTES, i, &c->tx_ok_bytes, cmd);
        REG_CNT_10G(TX_UC, i, &c->tx_unicast, cmd);
        REG_CNT_10G(TX_MC, i, &c->tx_multicast, cmd);
        REG_CNT_10G(TX_BC, i, &c->tx_broadcast, cmd);
        REG_CNT_10G(TX_SIZE64, i, &c->tx_size64, cmd);
        REG_CNT_10G(TX_SIZE65TO127, i, &c->tx_size65_127, cmd);
        REG_CNT_10G(TX_SIZE128TO255, i, &c->tx_size128_255, cmd);
        REG_CNT_10G(TX_SIZE256TO511, i, &c->tx_size256_511, cmd);
        REG_CNT_10G(TX_SIZE512TO1023, i, &c->tx_size512_1023, cmd);
        REG_CNT_10G(TX_SIZE1024TO1518, i, &c->tx_size1024_1518, cmd);
        REG_CNT_10G(TX_SIZE1519TOMAX, i, &c->tx_size1519_max, cmd);
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        if (vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION]) {
            REG_CNT_10G_ONE(MM_RX_ASSEMBLY_ERR, i, &c->rx_mm_assembly_errors, cmd);
            REG_CNT_10G_ONE(MM_RX_SMD_ERR, i, &c->rx_mm_smd_errors, cmd);
            REG_CNT_10G_ONE(MM_RX_ASSEMBLY_OK, i, &c->rx_mm_assembly_ok, cmd);
            REG_CNT_10G_ONE(MM_RX_MERGE_FRAG, i, &c->rx_mm_fragments, cmd);
            REG_CNT_10G_ONE(MM_TX_PFRAGMENT, i, &c->tx_mm_fragments, cmd);
        }
#endif
    }

    /* QSYS counters */
    REG_WR(VTSS_XQS_STAT_CFG, VTSS_F_XQS_STAT_CFG_STAT_VIEW(port));
    addr = 16;
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->tx_green_drops[i], cmd));
    }
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->tx_yellow_drops[i], cmd));
    }
    addr = 256;
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->tx_green_class[i], cmd));
    }
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->tx_yellow_class[i], cmd));
    }
    VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->tx_queue_drops, cmd));

    /* ANA_AC counters */
    REG_CNT_ANA_AC(PORT_STAT_LSB_CNT(port, REG_CNT_ANA_AC_PORT_FILTER), &c->rx_local_drops, cmd);
    REG_CNT_ANA_AC(PORT_STAT_LSB_CNT(port, REG_CNT_ANA_AC_PORT_POLICER_DROPS), &c->rx_policer_drops,
                   cmd);
    for (i = 0; i < VTSS_PRIOS; i++) {
        REG_CNT_ANA_AC(QUEUE_STAT_LSB_CNT(port * 8 + i, REG_CNT_ANA_AC_QUEUE_PRIO), &c->rx_class[i],
                       cmd);
    }

    if (counters == NULL) {
        return VTSS_RC_OK;
    }

    /* Proprietary counters */
    prop = &counters->prop;
    for (i = 0; i < VTSS_PRIOS; i++) {
        prop->rx_prio[i] = c->rx_class[i].value;
        prop->tx_prio[i] = (c->tx_yellow_class[i].value + c->tx_green_class[i].value);
    }

    /* RMON Rx counters */
    rmon = &counters->rmon;
    rmon->rx_etherStatsDropEvents = c->rx_policer_drops.value;
    rmon->rx_etherStatsOctets = (CNT_SUM(c->rx_ok_bytes) + CNT_SUM(c->rx_bad_bytes));
    rx_errors = (CNT_SUM(c->rx_crc_err) + CNT_SUM(c->rx_undersize) + CNT_SUM(c->rx_oversize) +
                 CNT_SUM(c->rx_symbol_err) + CNT_SUM(c->rx_jabbers) + CNT_SUM(c->rx_fragments));
    if (vtss_state->port.conf[port_no].frame_length_chk) {
        rx_errors += (CNT_SUM(c->rx_in_range_len_err) + CNT_SUM(c->rx_out_of_range_len_err));
    }
    rmon->rx_etherStatsPkts =
        (CNT_SUM(c->rx_unicast) + CNT_SUM(c->rx_multicast) + CNT_SUM(c->rx_broadcast) + rx_errors);
    rmon->rx_etherStatsBroadcastPkts = CNT_SUM(c->rx_broadcast);
    rmon->rx_etherStatsMulticastPkts = CNT_SUM(c->rx_multicast);
    rmon->rx_etherStatsCRCAlignErrors = CNT_SUM(c->rx_crc_err);
    rmon->rx_etherStatsUndersizePkts = CNT_SUM(c->rx_undersize);
    rmon->rx_etherStatsOversizePkts = CNT_SUM(c->rx_oversize);
    rmon->rx_etherStatsFragments = CNT_SUM(c->rx_fragments);
    rmon->rx_etherStatsJabbers = CNT_SUM(c->rx_jabbers);
    rmon->rx_etherStatsPkts64Octets = CNT_SUM(c->rx_size64);
    rmon->rx_etherStatsPkts65to127Octets = CNT_SUM(c->rx_size65_127);
    rmon->rx_etherStatsPkts128to255Octets = CNT_SUM(c->rx_size128_255);
    rmon->rx_etherStatsPkts256to511Octets = CNT_SUM(c->rx_size256_511);
    rmon->rx_etherStatsPkts512to1023Octets = CNT_SUM(c->rx_size512_1023);
    rmon->rx_etherStatsPkts1024to1518Octets = CNT_SUM(c->rx_size1024_1518);
    rmon->rx_etherStatsPkts1519toMaxOctets = CNT_SUM(c->rx_size1519_max);

    /* RMON Tx counters */
    rmon->tx_etherStatsDropEvents = c->tx_queue_drops.value;
    for (i = 0; i < VTSS_PRIOS; i++) {
        rmon->tx_etherStatsDropEvents += (c->tx_green_drops[i].value + c->tx_yellow_drops[i].value);
    }
    rmon->tx_etherStatsPkts = (CNT_SUM(c->tx_unicast) + CNT_SUM(c->tx_multicast) +
                               CNT_SUM(c->tx_broadcast) + c->tx_late_coll.value);
    rmon->tx_etherStatsOctets = CNT_SUM(c->tx_ok_bytes);
    rmon->tx_etherStatsBroadcastPkts = CNT_SUM(c->tx_broadcast);
    rmon->tx_etherStatsMulticastPkts = CNT_SUM(c->tx_multicast);
    rmon->tx_etherStatsCollisions =
        (c->tx_multi_coll.value + c->tx_backoff1.value + c->tx_late_coll.value + c->tx_xcoll.value);
    rmon->tx_etherStatsPkts64Octets = CNT_SUM(c->tx_size64);
    rmon->tx_etherStatsPkts65to127Octets = CNT_SUM(c->tx_size65_127);
    rmon->tx_etherStatsPkts128to255Octets = CNT_SUM(c->tx_size128_255);
    rmon->tx_etherStatsPkts256to511Octets = CNT_SUM(c->tx_size256_511);
    rmon->tx_etherStatsPkts512to1023Octets = CNT_SUM(c->tx_size512_1023);
    rmon->tx_etherStatsPkts1024to1518Octets = CNT_SUM(c->tx_size1024_1518);
    rmon->tx_etherStatsPkts1519toMaxOctets = CNT_SUM(c->tx_size1519_max);

    /* Interfaces Group Rx counters */
    if_group = &counters->if_group;
    if_group->ifInOctets = rmon->rx_etherStatsOctets;
    if_group->ifInUcastPkts = CNT_SUM(c->rx_unicast);
    if_group->ifInMulticastPkts = CNT_SUM(c->rx_multicast);
    if_group->ifInBroadcastPkts = CNT_SUM(c->rx_broadcast);
    if_group->ifInNUcastPkts = (CNT_SUM(c->rx_multicast) + CNT_SUM(c->rx_broadcast));
    if_group->ifInDiscards = rmon->rx_etherStatsDropEvents;
    if_group->ifInErrors = rx_errors;

    /* Interfaces Group Tx counters */
    if_group->ifOutOctets = rmon->tx_etherStatsOctets;
    if_group->ifOutUcastPkts = CNT_SUM(c->tx_unicast);
    if_group->ifOutMulticastPkts = CNT_SUM(c->tx_multicast);
    if_group->ifOutBroadcastPkts = CNT_SUM(c->tx_broadcast);
    if_group->ifOutNUcastPkts = (CNT_SUM(c->tx_multicast) + CNT_SUM(c->tx_broadcast));
    if_group->ifOutDiscards = rmon->tx_etherStatsDropEvents;
    if_group->ifOutErrors = (c->tx_late_coll.value + c->tx_csense.value + c->tx_xcoll.value);

#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    /* Ethernet-like Rx counters */
    elike = &counters->ethernet_like;
    elike->dot3StatsAlignmentErrors = 0; /* Not supported */
    elike->dot3StatsFCSErrors = CNT_SUM(c->rx_crc_err);
    elike->dot3StatsFrameTooLongs = CNT_SUM(c->rx_oversize);
    elike->dot3StatsSymbolErrors = CNT_SUM(c->rx_symbol_err);
    elike->dot3ControlInUnknownOpcodes = CNT_SUM(c->rx_unsup_opcode);
    elike->dot3InPauseFrames = CNT_SUM(c->rx_pause) + CNT_SUM(c->rx_unsup_opcode);

    /* Ethernet-like Tx counters */
    elike->dot3StatsSingleCollisionFrames = c->tx_backoff1.value;
    elike->dot3StatsMultipleCollisionFrames = c->tx_multi_coll.value;
    elike->dot3StatsDeferredTransmissions = c->tx_defer.value;
    elike->dot3StatsLateCollisions = c->tx_late_coll.value;
    elike->dot3StatsExcessiveCollisions = c->tx_xcoll.value;
    elike->dot3StatsCarrierSenseErrors = c->tx_csense.value;
    elike->dot3OutPauseFrames = CNT_SUM(c->tx_pause);
#endif /* VTSS_FEATURE_PORT_CNT_ETHER_LIKE */

#if defined(VTSS_FEATURE_PORT_CNT_BRIDGE)
    /* Bridge counters, including filtered frames with and without CRC error */
    counters->bridge.dot1dTpPortInDiscards = c->rx_local_drops.value;
#endif /* VTSS_FEATURE_PORT_CNT_BRIDGE */
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    if (vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION]) {
        {
            vtss_port_dot3br_counters_t *dot3br = &counters->dot3br;

            /* 802.3br counters */
            dot3br->aMACMergeFrameAssErrorCount = c->rx_mm_assembly_errors.value;
            dot3br->aMACMergeFrameSmdErrorCount = c->rx_mm_smd_errors.value;
            dot3br->aMACMergeFrameAssOkCount = c->rx_mm_assembly_ok.value;
            dot3br->aMACMergeFragCountRx = c->rx_mm_fragments.value;
            dot3br->aMACMergeFragCountTx = c->tx_mm_fragments.value;
            dot3br->aMACMergeHoldCount = 0;
        }
    }
#endif /* VTSS_FEATURE_QOS_FRAME_PREEMPTION */
    return VTSS_RC_OK;
}

static vtss_rc fa_port_counters(vtss_state_t               *vtss_state,
                                const vtss_port_no_t        port_no,
                                vtss_port_counters_t *const counters,
                                vtss_counter_cmd_t          cmd)
{
    return fa_port_counters_chip(vtss_state, port_no,
                                 &vtss_state->port.counters[port_no].counter.fa, counters, cmd);
}

vtss_rc vtss_cil_port_counters_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return fa_port_counters(vtss_state, port_no, NULL, VTSS_COUNTER_CMD_UPDATE);
}

vtss_rc vtss_cil_port_counters_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return fa_port_counters(vtss_state, port_no, NULL, VTSS_COUNTER_CMD_CLEAR);
}

vtss_rc vtss_cil_port_basic_counters_get(vtss_state_t                *vtss_state,
                                         const vtss_port_no_t         port_no,
                                         vtss_basic_counters_t *const counters)
{
    vtss_port_fa_counters_t *c = &vtss_state->port.counters[port_no].counter.fa;
    VTSS_RC(vtss_cil_port_counters_update(vtss_state, port_no));
    counters->rx_frames =
        (CNT_SUM(c->rx_unicast) + CNT_SUM(c->rx_multicast) + CNT_SUM(c->rx_broadcast));
    counters->tx_frames = (CNT_SUM(c->tx_unicast) + CNT_SUM(c->tx_multicast) +
                           CNT_SUM(c->tx_broadcast) + c->tx_late_coll.value);

    return VTSS_RC_ERROR;
}

vtss_rc vtss_cil_port_counters_get(vtss_state_t               *vtss_state,
                                   const vtss_port_no_t        port_no,
                                   vtss_port_counters_t *const counters)
{
    VTSS_MEMSET(counters, 0, sizeof(*counters));
    return fa_port_counters(vtss_state, port_no, counters, VTSS_COUNTER_CMD_UPDATE);
}

vtss_rc vtss_cil_port_forward_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_test_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_port_serdes_debug(vtss_state_t                         *vtss_state,
                                   const vtss_port_no_t                  port_no,
                                   const vtss_port_serdes_debug_t *const conf)
{
    VTSS_RC(fa_debug_serdes_set(vtss_state, port_no, conf));
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_PORT_CONF_BULK)
/* Apply the port configuration to hardware */
/* Configuration is applied in parallel where possible */
vtss_rc vtss_cil_port_conf_set_bulk(vtss_state_t *vtss_state)
{
    vtss_port_conf_t       *conf;
    BOOL                    found_next_if;
    u32                     sdi, this_type, sd_type_org;
    vtss_port_no_t          port_no, start_port = 0;
    vtss_sd10g_media_type_t md_type_org = VTSS_SD10G_MEDIA_PR_NONE;
    vtss_serdes_mode_t      this_mode, sd_mode_org = VTSS_SERDES_MODE_DISABLE;
    vtss_port_speed_t       speed_org = VTSS_SPEED_UNDEFINED;
    u64                     bulk_port_mask = vtss_state->port.bulk_port_mask;

    /* Apply the stored port config in normal manner - serdes'es are skipped */
    for (u32 port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (bulk_port_mask & VTSS_BIT64(port_no)) {
            if (vtss_cil_port_conf_set(vtss_state, port_no) != VTSS_RC_OK) {
                VTSS_E("Could not apply port conf to port %d", port_no);
            }
        }
    }

    /* Now configure the serdes'es in parallel */
    while (1) {
        found_next_if = FALSE;
        vtss_state->port.bulk_port_mask = 0;

        /* Find serdes'es with identical configuration: serdes-mode, arch-type,
         * media-type and speed  */
        for (port_no = start_port; port_no < vtss_state->port_count; port_no++) {
            if (!(bulk_port_mask & VTSS_BIT64(port_no))) {
                continue;
            }
            conf = &vtss_state->port.conf[port_no];
            if (!found_next_if) {
                found_next_if = TRUE;
                /* serdes properties to be applied to all common ones */
                start_port = port_no;
                if (vtss_fa_port2sd(vtss_state, port_no, &sdi, &sd_type_org) != VTSS_RC_OK) {
                    continue;
                }
                md_type_org = conf->serdes.media_type;
                sd_mode_org = vtss_state->port.sd28_mode[vtss_fa_sd_lane_indx(vtss_state, port_no)];
                speed_org = conf->speed;
            } else {
                /* if next interface is different then break and apply */
                if (vtss_fa_port2sd(vtss_state, port_no, &sdi, &this_type) != VTSS_RC_OK) {
                    continue;
                }
                this_mode = vtss_state->port.sd28_mode[vtss_fa_sd_lane_indx(vtss_state, port_no)];
                if ((sd_mode_org != this_mode) || (sd_type_org != this_type) ||
                    (md_type_org != conf->serdes.media_type) || (speed_org != conf->speed)) {
                    break;
                }
            }
            if (!(sd_mode_org == VTSS_SERDES_MODE_QSGMII && ((VTSS_CHIP_PORT(port_no) % 4) != 0))) {
                vtss_state->port.bulk_port_mask |= VTSS_BIT64(port_no);
            }
        }

        /* Apply the config to serdes'es defined in
         * 'vtss_state->port.bulk_port_mask' */
        if (vtss_state->port.bulk_port_mask > 0) {
            if (vtss_fa_sd_cfg(vtss_state, start_port, sd_mode_org) != VTSS_RC_OK) {
                VTSS_E("Could not set common serdes");
            }
        }

        if (port_no == vtss_state->port_count) {
            break;
        }

        start_port = port_no;
    }

    vtss_state->port.bulk_state = VTSS_PORT_BULK_DISABLED;
    vtss_state->port.bulk_port_mask = 0;
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_PORT_CONF_BULK */

vtss_rc vtss_cil_port_ifh_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */
#if VTSS_OPT_DEBUG_PRINT

#define FA_DEBUG_MAC(ss, addr, i, name)                                                            \
    vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_DEV1G_MAC_##addr), i, "MAC_" name)
#define FA_DEBUG_PCS(ss, addr, i, name)                                                            \
    vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_DEV1G_PCS1G_##addr), i, "PCS1G_" name)
#define FA_DEBUG_10G_MAC(ss, addr, i, name)                                                        \
    vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_DEV10G_MAC_##addr), i, "MAC_" name)
#define FA_DEBUG_FX100(ss, addr, i, name)                                                          \
    vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_DEV1G_##addr), i, name)
#define FA_DEBUG_ALL(ss, addr, i, name)                                                            \
    vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_##addr), i, name)

static vtss_rc fa_debug_chip_port(vtss_state_t                  *vtss_state,
                                  lmu_ss_t                      *ss,
                                  const vtss_debug_info_t *const info,
                                  vtss_port_no_t                 port_no)
{
    u32               port = VTSS_CHIP_PORT(port_no);
    u32               sd_indx, sd_type, sd;
    u32               tgt = vtss_fa_dev_tgt(vtss_state, port_no);
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    BOOL              rs_fec = 0, r_fec = 0;

    if (fa_is_high_speed_device(vtss_state, port_no)) {
        tgt = VTSS_TO_HIGH_DEV(port);
        u32 value, val2, usx, pcs_st,
            pcs = VTSS_TO_PCS_TGT(port); // only for 5G/10G/25G PCS
        BOOL lock, hi_ber, spd25g = vtss_state->port.current_speed[port_no] == VTSS_SPEED_25G;
        FA_DEBUG_ALL(ss, DEV10G_DEV_RST_CTRL(tgt), port, "DEV10G_DEV_RST_CTRL");
        FA_DEBUG_10G_MAC(ss, TX_MONITOR_STICKY(tgt), port, "TX_MONITOR_STICKY");
        FA_DEBUG_10G_MAC(ss, ENA_CFG(tgt), port, "ENA_CFG");
        FA_DEBUG_10G_MAC(ss, MODE_CFG(tgt), port, "MODE_CFG");
        if (conf->if_type == VTSS_PORT_INTERFACE_USXGMII) {
            //            REG_RD(VTSS_DEV10G_USXGMII_ANEG_STATUS(tgt), &usx);
            FA_DEBUG_ALL(ss, DEV10G_USXGMII_ANEG_STATUS(tgt), port, "USXGMII_ANEG_STATUS");
            FA_DEBUG_ALL(ss, DEV10G_USXGMII_ANEG_CFG(tgt), port, "USXGMII_ANEG_CFG");
        }
        pr("\nLink status (MAC/PCS):\n");
        pr("port          local_fault   remote_fault  idle_state    rx_blk_lock   rx_hi_ber   rsfec/rfec\n");
        REG_RD(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), &value);
        REG_RD(VTSS_DEV10G_PCS25G_STATUS(tgt), &val2);
        REG_RD(VTSS_PCS_10GBASE_R_PCS_STATUS(pcs), &pcs_st);
        REG_RD(VTSS_DEV10G_USXGMII_PCS_STATUS(tgt), &usx);
        if (spd25g) {
            lock = VTSS_X_DEV10G_PCS25G_STATUS_BLOCK_LOCK(val2);
            hi_ber = VTSS_X_DEV10G_PCS25G_STATUS_HI_BER(val2);
        } else {
            if (conf->if_type == VTSS_PORT_INTERFACE_USXGMII) {
                lock = VTSS_X_DEV10G_USXGMII_PCS_STATUS_USXGMII_BLOCK_LOCK(usx);
            } else {
                lock = VTSS_X_PCS_10GBASE_R_PCS_STATUS_RX_BLOCK_LOCK(pcs_st);
            }
            hi_ber = VTSS_X_PCS_10GBASE_R_PCS_STATUS_RX_HI_BER(pcs_st);
        }
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
        rs_fec = vtss_state->port.kr_fec[port_no].rs_fec;
        r_fec = vtss_state->port.kr_fec[port_no].r_fec;
#endif
        pr("%-13d %-13d %-13d %-13d %-13d %-13d %d/%-13d\n", port,
           VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(value),
           VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(value),
           VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(value), lock, hi_ber, rs_fec,
           r_fec);
        // Clear the stickies
        REG_WR(VTSS_PCS_10GBASE_R_PCS_STATUS(pcs), 0xFFFFFFFF);
    } else {
        vtss_fa_debug_reg_inst(vtss_state, ss, REG_ADDR(VTSS_DEV1G_DEV_RST_CTRL(tgt)), port,
                               "DEV_RST_CTRL");
        FA_DEBUG_MAC(ss, ENA_CFG(tgt), port, "ENA_CFG");
        FA_DEBUG_MAC(ss, MODE_CFG(tgt), port, "MODE_CFG");
        FA_DEBUG_MAC(ss, MAXLEN_CFG(tgt), port, "MAXLEN_CFG");
        FA_DEBUG_MAC(ss, TAGS_CFG(tgt), port, "TAGS_CFG");
        FA_DEBUG_REGX_NAME(ss, DSM, RX_PAUSE_CFG, port, "RX_PAUSE_CFG");
        FA_DEBUG_REGX_NAME(ss, DSM, ETH_FC_CFG, port, "ETH_FC_CFG");
        if (conf->if_type == VTSS_PORT_INTERFACE_100FX) {
            FA_DEBUG_FX100(ss, PCS_FX100_CFG(tgt), port, "PCS_FX100_CFG");
            FA_DEBUG_FX100(ss, PCS_FX100_STATUS(tgt), port, "FX100_STATUS");
        } else {
            FA_DEBUG_PCS(ss, CFG(tgt), port, "CFG");
            FA_DEBUG_PCS(ss, MODE_CFG(tgt), port, "MODE_CFG");
            FA_DEBUG_PCS(ss, SD_CFG(tgt), port, "SD_CFG");
            FA_DEBUG_PCS(ss, ANEG_CFG(tgt), port, "ANEG_CFG");
            FA_DEBUG_PCS(ss, ANEG_STATUS(tgt), port, "ANEG_STATUS");
            FA_DEBUG_PCS(ss, LINK_STATUS(tgt), port, "LINK_STATUS");
        }
    }

    pr("\nSerdes:\n");
    if (vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type) == VTSS_RC_OK) {
        if (sd_type == FA_SERDES_TYPE_10G) {
            sd = sd_indx + RT_SERDES_10G_START;
        } else if (sd_type == FA_SERDES_TYPE_25G) {
            sd = sd_indx + RT_SERDES_25G_START;
        } else {
            sd = sd_indx;
        }
    } else {
        sd_type = FA_SERDES_TYPE_UNKNOWN;
        sd_indx = 0;
        sd = 0;
    }
    pr("Port is mapped to serdes %s index %d (S%d)\n",
       (sd_type == FA_SERDES_TYPE_6G)    ? "SD6G"
       : (sd_type == FA_SERDES_TYPE_10G) ? "SD10G"
       : (sd_type == FA_SERDES_TYPE_25G) ? "SD25G"
                                         : "N/A",
       sd_indx, sd);
    pr("\n");

    if (info->full) {
        pr("DSM Taxi calendar mappings:\n");
        (void)vtss_fa_dsm_cal_debug(vtss_state, ss);
        pr("\n");
        pr("Cell bus auto calendar mappings:\n");
        (void)vtss_fa_cell_cal_debug(vtss_state, ss);
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_PORT_KR_IRQ)
static void print_reg_bit(lmu_ss_t *ss, BOOL bt, char *name)
{
    if (bt) {
        pr("%s ", name);
    }
}
static char *fa_kr_aneg_sm(u32 reg)
{
    switch (reg) {
    case 0:  return "AN_ENABLE(0)";
    case 1:  return "XMI_DISABLE(1)";
    case 2:  return "ABILITY_DET(2)";
    case 3:  return "ACK_DET(3)";
    case 4:  return "COMPLETE_ACK(4)";
    case 5:  return "TRAIN(5)";
    case 6:  return "AN_GOOD_CHK(6)";
    case 7:  return "AN_GOOD(7)";
    case 8:  return "RATE_DET(8)";
    case 11: return "LINK_STAT_CHK(11)";
    case 12: return "PARLL_DET_FAULT(12)";
    case 13: return "WAIT_RATE_DONE(13)";
    case 14: return "NXTPG_WAIT(14)";
    default: return "?";
    }
}

static char *fa_kr_aneg_rate(u32 reg)
{
    switch (reg) {
    case 0:  return "No Change";
    case 7:  return "25G-KR";
    case 8:  return "25G-KR-S";
    case 9:  return "10G-KR";
    case 10: return "10G-KX4";
    case 11: return "5G-KR";
    case 12: return "2.5G-KX";
    case 13: return "1G-KX";
    default: return "other";
    }
}

static vtss_rc fa_debug_chip_kr(vtss_state_t                  *vtss_state,
                                lmu_ss_t                      *ss,
                                const vtss_debug_info_t *const info,
                                vtss_port_no_t                 port_no)
{
    u32 val;
    u32 tgt;
    u32 p = VTSS_CHIP_PORT(port_no);

    if (!PORT_IS_KR_CAP(port_no)) {
        return VTSS_RC_OK;
    }
    tgt = vtss_to_sd10g_kr(vtss_state, p);

    pr("Port %d:", p);
    REG_RD(VTSS_IP_KRANEG_IRQ_VEC(tgt), &val);
    REG_WR(VTSS_IP_KRANEG_IRQ_VEC(tgt), val);
    if (val > 0) {
        pr("\n  IRQ:       ");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_KR_ACTV(val), "KR_ACTV");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_LPSVALID(val), "LPSVALID");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_WT_DONE(val), "LPSVALID");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_MW_DONE(val), "MW_DONE");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_BER_BUSY_0(val), "BER_BUSY_0");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_BER_BUSY_1(val), "BER_BUSY_1");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_REM_RDY_0(val), "REM_RDY_0");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_REM_RDY_1(val), "REM_RDY_1");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_FRLOCK_0(val), "FRLOCK_0");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_FRLOCK_1(val), "FRLOCK_1");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_DME_VIOL_0(val), "DME_VIOL_0");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_DME_VIOL_1(val), "DME_VIOL_1");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_AN_XMIT_DISABLE(val), "AN_XMIT_DISABLE");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_AN_TRAIN(val), "AN_TRAIN");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_AN_RATE_DET(val), "AN_RATE_DET");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_CMPL_ACK(val), "CMPL_ACK");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_AN_GOOD(val), "AN_GOOD");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_LINK_FAIL(val), "LINK_FAIL");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_ABD_FAIL(val), "ABD_FAIL");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_ACK_FAIL(val), "ACK_FAIL");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_NP_FAIL(val), "NP_FAIL");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_NP_RX(val), "NP_RX");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_INCP_LINK(val), "INCP_LINK");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_GEN0_DONE(val), "GEN0_DONE");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_IRQ_VEC_GEN1_DONE(val), "GEN1_DONE");
        if (VTSS_X_IP_KRANEG_IRQ_VEC_AN_RATE(val) > 0) {
            pr("AN_RATE:%s ", fa_kr_aneg_rate(VTSS_X_IP_KRANEG_IRQ_VEC_AN_RATE(val)));
        }
    }

    REG_RD(VTSS_IP_KRANEG_FW_MSG(tgt), &val);
    if (val > 0) {
        pr("\n  FW_MSG:    ");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_MSG_TR_DONE(val), "TR_DONE");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_MSG_LDCOEF_VLD(val), "LDCOEF_VLD");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_MSG_LDSTAT_VLD(val), "LDSTAT_VLD");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_MSG_NP_LOADED(val), "NP_LOADED");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_MSG_RATE_DONE(val), "RATE_DONE");
    }
    REG_RD(VTSS_IP_KRANEG_FW_REQ(tgt), &val);
    if (val > 0) {
        pr("\n  FW_REQ:    ");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_REQ_BER_EN(val), "BER_EN");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_REQ_GEN0_TMR_START(val), "GEN0_TMR_START");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_REQ_GEN1_TMR_START(val), "GEN1_TMR_START");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_REQ_WT_START(val), "WT_START");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_FW_REQ_MW_START(val), "MW_START");
    }
    REG_RD(VTSS_IP_KRANEG_AN_SM(tgt), &val);
    REG_WR(VTSS_IP_KRANEG_AN_SM(tgt), val);
    if (val > 0) {
        pr("\n  AN_SM:     ");
        pr("%s ", fa_kr_aneg_sm(VTSS_X_IP_KRANEG_AN_SM_AN_SM(val)));
        pr("ABDET_CNT:%d ", VTSS_X_IP_KRANEG_AN_SM_ABDET_CNT(val));
    }
    REG_RD(VTSS_IP_KRANEG_AN_HIST(tgt), &val);
    REG_WR(VTSS_IP_KRANEG_AN_HIST(tgt), val);
    if (val > 0) {
        pr("\n  AN_HIST:   ");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 0, 1), "AN_ENA(0)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 1, 1), "XMI_DIS(1)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 2, 1), "ABI_DET(2)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 3, 1), "ACK_DET(3)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 4, 1), "COM_ACK(4)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 5, 1), "TRAIN(5)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 6, 1), "AN_GOOD_CHK(6)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 7, 1), "AN_GOOD(7)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 8, 1), "RATE_CHK(8)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 11, 1), "LNK_ST_CHK(11)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 12, 1), "PARL_DET_FAUL(12)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 13, 1), "WAIT_RT_DONE(13)");
        print_reg_bit(ss, VTSS_EXTRACT_BITFIELD(val, 14, 1), "NXT_PG_WAIT(14)");
    }
    REG_RD(VTSS_IP_KRANEG_AN_STS0(tgt), &val);
    REG_WR(VTSS_IP_KRANEG_AN_STS0(tgt), val);
    if (val > 0) {
        pr("\n  AN_STAT_0: ");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS0_PARDETFLT(val), "PARDETFLT");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS0_NPSTAT(val), "NPSTAT");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS0_PG_RCVD(val), "PG_RCVD");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS0_AN_COMPLETE(val), "AN_COMPLETE");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS0_REM_FLT(val), "REM_FLT");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS0_AN_ABLE(val), "AN_ABLE");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS0_LINKSTAT(val), "LINKSTAT");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS0_AN_LP_ABLE(val), "AN_LP_ABLE");
    }

    REG_RD(VTSS_IP_KRANEG_AN_STS1(tgt), &val);
    REG_WR(VTSS_IP_KRANEG_AN_STS1(tgt), val);
    if (val > 0) {
        pr("\n  AN_STAT_1: ");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS1_KR_ACTV(val), "KR_ACTV");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS1_SYNC8B10B(val), "SYNC8B10B");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS1_SYNC10G(val), "SYNC10G");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS1_NONCE_MATCH(val), "NONCE");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_AN_STS1_INCP_LINK(val), "INCP_LINK");
        if (VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(val) > 0) {
            pr("LINK_HCD:%s ", fa_kr_aneg_rate(VTSS_X_IP_KRANEG_AN_STS1_LINK_HCD(val)));
        }
    }

    REG_RD(VTSS_IP_KRANEG_BP_ETH_STS(tgt), &val);
    if (val > 0) {
        pr("\n  BP_ETH_ST: ");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_5G_KR(val), "AN_NEG_5G_KR");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_2P5G_KX(val), "AN_NEG_2P5G_KX");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_25G_KR(val), "AN_NEG_25G_KR");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_25G_KR_S(val), "AN_NEG_25G_KR_S");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_RS_FEC(val), "AN_NEG_RS_FEC");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_R_FEC(val), "AN_NEG_R_FEC");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_10G_KR(val), "AN_NEG_10G_KR");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_NEG_1G_KX(val), "AN_NEG_1G_KX");
        print_reg_bit(ss, VTSS_X_IP_KRANEG_BP_ETH_STS_AN_BP_ABLE(val), "AN_BP_ABLE");
    }
    pr("\n");

    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_PORT_KR_IRQ

static vtss_rc fa_debug_serdes(vtss_state_t                  *vtss_state,
                               lmu_ss_t                      *ss,
                               const vtss_debug_info_t *const info)

{
    vtss_port_no_t port_no;

    if (info->has_action && info->action == 0) {
        pr("Serdes actions:\n");
        pr("0: Show actions\n");
        pr("1: Dump Serdes registers\n");
        pr("2: Show normal eye diagram\n");
        pr("3: Read fast eye height\n");
        pr("4: Read eye area (25G)\n");
        pr("5: Read DFE settings\n");
        pr("6: Read CTLE settings\n");
        pr("7: Enable Oscal (25G)\n");
        pr("8: Disable DFE\n");
        pr("9: Enable  DFE (auto mode)\n");
        pr("10: Read TxEQ settings\n");
        pr("11: Enable Tx square wave\n");
        pr("12: Disable Tx square wave\n");
        pr("13: Auto adjust VGA gain\n");
        pr("14: Auto adjust EQR gain\n");
        pr("15: Auto adjust EQC gain\n");
        pr("16: Perform CTLE adjustment (13,14,15,13) \n");
        pr("20: INIT\n");
        pr("21: CM1 DECR\n");
        pr("22: CM1 INCR\n");
        pr("23: CP1 DECR\n");
        pr("24: CP1 INCR\n");
        pr("25: CM0 DECR\n");
        pr("26: CM0 INCR\n");
        return VTSS_RC_OK;
    }
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0) {
            continue;
        }

        VTSS_RC(fa_debug_chip_serdes(vtss_state, ss, info, port_no));
    } /* Port loop */

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_PORT_KR_IRQ)
static vtss_rc fa_debug_kr(vtss_state_t                  *vtss_state,
                           lmu_ss_t                      *ss,
                           const vtss_debug_info_t *const info)

{
    vtss_port_no_t port_no;

    if (info->has_action && info->action == 0) {
        pr("Serdes actions:\n");
        pr("0: Show actions\n");
        pr("1: Dump kr\n");
        return VTSS_RC_OK;
    }
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0) {
            continue;
        }
        VTSS_RC(fa_debug_chip_kr(vtss_state, ss, info, port_no));
    } /* Port loop */

    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_PORT_KR_IRQ

#if defined(VTSS_ARCH_SPARX5)
static vtss_rc fa_debug_mux(vtss_state_t                  *vtss_state,
                            lmu_ss_t                      *ss,
                            const vtss_debug_info_t *const info)

{
    u32 val, val2;

    REG_RD(VTSS_PORT_CONF_USXGMII_ENA, &val2);
    for (u32 a = 0; a < 32; a++) {
        if ((val2 & VTSS_BIT(a)) == 0) {
            continue;
        }
        REG_RD(VTSS_PORT_CONF_USXGMII_CFG(a), &val);
        if (VTSS_X_PORT_CONF_USXGMII_CFG_NUM_PORTS(val) == 0) {
            pr("port mode 0 not supported\n");
            if (a > 15) {
                pr("USX extender:%d is in SXGMII mode with chip port %d --> SD%d\n", a, a + 32,
                   a + 1);
            }
        } else if (VTSS_X_PORT_CONF_USXGMII_CFG_NUM_PORTS(val) == 1) {
            pr("port mode 1 not supported\n");
        } else {
            pr("USX extender:%d is in QXGMII mode with chip ports: [", a);
            for (u32 i = 0; i < 4; i++) {
                pr("  %d", a - 16 + i * 16);
            }
            pr(" ]  --> SD%d\n", a + 1);
        }
    }
    REG_RD(VTSS_PORT_CONF_QSGMII_ENA, &val2);
    for (u32 a = 0; a < 12; a++) {
        if ((val2 & VTSS_BIT(a)) == 0) {
            continue;
        }
        pr("MUX:%d is in QSGMII mode with chip ports: [", a);
        for (u32 i = 0; i < 4; i++) {
            pr("  %d", a * 4 + i);
        }
        pr(" ]  --> SD%d\n", a + 13);
    }

    return VTSS_RC_OK;
}
#else // Laguna
static vtss_rc fa_debug_mux(vtss_state_t                  *vtss_state,
                            lmu_ss_t                      *ss,
                            const vtss_debug_info_t *const info)
{
    u32 val, val2, cp;

    REG_RD(VTSS_PORT_CONF_USXGMII_ENA, &val2);
    for (u32 a = 0; a < 10; a++) {
        if ((val2 & VTSS_BIT(a)) == 0) {
            continue;
        }
        REG_RD(VTSS_PORT_CONF_USXGMII_CFG(a), &val);
        if (VTSS_X_PORT_CONF_USXGMII_CFG_NUM_PORTS(val) == 0) {
            if (a > 1 && a < 6) {
                pr("%d not supported as USXGMII\n", a);
                continue;
            }
            if (a == 0) {
                cp = 0;
            } else if (a == 1) {
                cp = 4;
            } else if (a == 6) {
                cp = 24;
            } else if (a == 7) {
                cp = 25;
            } else if (a == 8) {
                cp = 26;
            } else {
                cp = 27;
            }
            pr("USX extender:%d is in USXGMII mode with chip port %d --> SD%d\n", a, cp, a);
        } else if (VTSS_X_PORT_CONF_USXGMII_CFG_NUM_PORTS(val) == 1) {
            pr("port mode 1 not supported\n");
        } else {
            if (a < 2 || a > 5) {
                pr("%d not supported as QXGMII\n", a);
                continue;
            }
            pr("USX extender:%d is in QXGMII mode with chip ports: [", a);
            for (u32 i = 0; i < 4; i++) {
                pr("  %d", 8 + (a - 2) * 4 + i);
            }
            pr(" ]  --> SD%d\n", a);
        }
    }
    REG_RD(VTSS_PORT_CONF_QSGMII_ENA, &val2);
    for (u32 a = 0; a < 6; a++) {
        if ((val2 & VTSS_BIT(a)) == 0) {
            continue;
        }
        pr("MUX:%d is in QSGMII mode with chip ports: [", a);
        for (u32 i = 0; i < 4; i++) {
            pr("  %d", a * 4 + i);
        }
        pr(" ]  --> SD%d\n", a);
    }

    return VTSS_RC_OK;
}
#endif

static vtss_rc fa_debug_port(vtss_state_t                  *vtss_state,
                             lmu_ss_t                      *ss,
                             const vtss_debug_info_t *const info)

{
    vtss_port_no_t port_no;
    u32            port;
    lmu_fmt_buf_t  buf;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {

        if (info->port_list[port_no] == 0) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);

        if (fa_is_high_speed_device(vtss_state, port_no)) {
            VTSS_FMT(buf, "Chip port %u (%u) Dev%s_%d", port, port_no,
                     VTSS_PORT_IS_25G(port)   ? "25G"
                     : VTSS_PORT_IS_10G(port) ? "10G"
                     : VTSS_PORT_IS_5G(port)  ? "5G"
                                              : "2G5",
                     vtss_port_dev_index(vtss_state, port));
        } else {
            VTSS_FMT(buf, "Chip port %u (%u) Dev%s_%d", port, port_no, "2G5", port);
        }

        vtss_fa_debug_reg_header(ss, buf.s);

        VTSS_RC(fa_debug_chip_port(vtss_state, ss, info, port_no));
    } /* Port loop */

    return VTSS_RC_OK;
}

static void fa_debug_dual_cnt(lmu_ss_t            *ss,
                              const char          *col1,
                              const char          *col2,
                              vtss_dual_counter_t *c1,
                              vtss_dual_counter_t *c2,
                              BOOL                 mixed)
{
    u32                 i;
    lmu_fmt_buf_t       buf1, buf2;
    const char         *name;
    vtss_chip_counter_t ca, cb;

    for (i = 0; i < 2; i++) {
        if (i) {
            name = "pmac";
            ca.value = c1->pmac;
        } else {
            name = "emac";
            ca.value = c1->emac;
        }
        VTSS_FMT(buf1, "%s_%s", name, col1);
        if (col2 == NULL) {
            vtss_fa_debug_cnt(ss, buf1.s, NULL, &ca, NULL);
        } else {
            if (mixed) {
                VTSS_FMT(buf2, "%s", col2);
                col2 = NULL;
            } else if (VTSS_STRLEN(col2) != 0) {
                VTSS_FMT(buf2, "%s_%s", name, col2);
            } else {
                VTSS_FMT(buf2, "");
            }
            cb.value = (i ? c2->pmac : c2->emac);
            vtss_fa_debug_cnt(ss, buf1.s, buf2.s, &ca, &cb);
        }
    }
}

static void fa_debug_cnt(lmu_ss_t            *ss,
                         const char          *col1,
                         const char          *col2,
                         vtss_dual_counter_t *c1,
                         vtss_dual_counter_t *c2)
{
    fa_debug_dual_cnt(ss, col1, col2, c1, c2, FALSE);
}

static void fa_debug_mix_cnt(lmu_ss_t            *ss,
                             const char          *col1,
                             const char          *col2,
                             vtss_dual_counter_t *c1,
                             vtss_chip_counter_t *c2)
{
    vtss_dual_counter_t c = {};

    c.emac = c2->value;
    fa_debug_dual_cnt(ss, col1, col2, c1, &c, TRUE);
}

static vtss_rc fa_debug_port_counters(vtss_state_t                  *vtss_state,
                                      lmu_ss_t                      *ss,
                                      const vtss_debug_info_t *const info,
                                      vtss_port_no_t                 port_no)
{
    u32                     i;
    lmu_fmt_buf_t           rx_buf, tx_buf;
    vtss_port_fa_counters_t cnt;

    VTSS_MEMSET(&cnt, 0, sizeof(vtss_port_fa_counters_t));
    VTSS_RC(fa_port_counters_chip(vtss_state, port_no, &cnt, NULL, 0));

    if (port_no < vtss_state->port_count && (info->full || info->action != 3)) {
        fa_debug_mix_cnt(ss, "ok_bytes", "out_bytes", &cnt.rx_ok_bytes, &cnt.tx_out_bytes);
        fa_debug_cnt(ss, "uc", "", &cnt.rx_unicast, &cnt.tx_unicast);
        fa_debug_cnt(ss, "mc", "", &cnt.rx_multicast, &cnt.tx_multicast);
        fa_debug_cnt(ss, "bc", "", &cnt.rx_broadcast, &cnt.tx_broadcast);
    }

    if (port_no < vtss_state->port_count && (info->full || info->action == 2)) {
        fa_debug_cnt(ss, "pause", "", &cnt.rx_pause, &cnt.tx_pause);
        fa_debug_cnt(ss, "unsup_opcode", NULL, &cnt.rx_unsup_opcode, NULL);
        fa_debug_cnt(ss, "64", "", &cnt.rx_size64, &cnt.tx_size64);
        fa_debug_cnt(ss, "65_127", "", &cnt.rx_size65_127, &cnt.tx_size65_127);
        fa_debug_cnt(ss, "128_255", "", &cnt.rx_size128_255, &cnt.tx_size128_255);
        fa_debug_cnt(ss, "256_511", "", &cnt.rx_size256_511, &cnt.tx_size256_511);
        fa_debug_cnt(ss, "512_1023", "", &cnt.rx_size512_1023, &cnt.tx_size512_1023);
        fa_debug_cnt(ss, "1024_1526", "", &cnt.rx_size1024_1518, &cnt.tx_size1024_1518);
        fa_debug_cnt(ss, "jumbo", "", &cnt.rx_size1519_max, &cnt.tx_size1519_max);
        fa_debug_cnt(ss, "crc", NULL, &cnt.rx_crc_err, NULL);
        fa_debug_mix_cnt(ss, "undersize", "multi_coll", &cnt.rx_undersize, &cnt.tx_multi_coll);
        fa_debug_mix_cnt(ss, "fragments", "late_coll", &cnt.rx_fragments, &cnt.tx_late_coll);
        fa_debug_mix_cnt(ss, "inr_len_err", "xcoll", &cnt.rx_in_range_len_err, &cnt.tx_xcoll);
        fa_debug_mix_cnt(ss, "oor_len_err", "defer", &cnt.rx_out_of_range_len_err, &cnt.tx_defer);
        fa_debug_mix_cnt(ss, "oversize", "xdefer", &cnt.rx_oversize, &cnt.tx_xdefer);
        fa_debug_mix_cnt(ss, "jabbers", "backoff1", &cnt.rx_jabbers, &cnt.tx_backoff1);
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        if (vtss_state->vtss_features[FEATURE_QOS_FRAME_PREEMPTION]) {
            /* 802.3br counters */
            vtss_fa_debug_cnt(ss, "mm_ass_err", NULL, &cnt.rx_mm_assembly_errors, NULL);
            vtss_fa_debug_cnt(ss, "mm_smd_err", NULL, &cnt.rx_mm_smd_errors, NULL);
            vtss_fa_debug_cnt(ss, "mm_ass_ok", NULL, &cnt.rx_mm_assembly_ok, NULL);
            vtss_fa_debug_cnt(ss, "mm_frag", "", &cnt.rx_mm_fragments, &cnt.tx_mm_fragments);
        }
#endif
    }

    if (info->full || info->action == 1 || info->action == 3) {
        vtss_fa_debug_cnt(ss, "local_drops", NULL, &cnt.rx_local_drops, NULL);
        vtss_fa_debug_cnt(ss, "policer_drops", "queue_drops", &cnt.rx_policer_drops,
                          &cnt.tx_queue_drops);

        for (i = 0; i < VTSS_PRIOS; i++) {
            VTSS_FMT(rx_buf, "class_%u", i);
            VTSS_FMT(tx_buf, "green_%u", i);
            vtss_fa_debug_cnt(ss, rx_buf.s, tx_buf.s, &cnt.rx_class[i], &cnt.tx_green_class[i]);
        }
        for (i = 0; i < VTSS_PRIOS; i++) {
            VTSS_FMT(tx_buf, "yellow_%u", i);
            vtss_fa_debug_cnt(ss, NULL, tx_buf.s, NULL, &cnt.tx_yellow_class[i]);
        }
        for (i = 0; i < VTSS_PRIOS; i++) {
            VTSS_FMT(tx_buf, "green_drops_%u", i);
            vtss_fa_debug_cnt(ss, NULL, tx_buf.s, NULL, &cnt.tx_green_drops[i]);
        }
        for (i = 0; i < VTSS_PRIOS; i++) {
            VTSS_FMT(tx_buf, "yellow_drops_%u", i);
            vtss_fa_debug_cnt(ss, NULL, tx_buf.s, NULL, &cnt.tx_yellow_drops[i]);
        }
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_port_cnt(vtss_state_t                  *vtss_state,
                                 lmu_ss_t                      *ss,
                                 const vtss_debug_info_t *const info)
{
    /*lint --e{454, 455} */ // Due to VTSS_EXIT_ENTER
    vtss_port_no_t port_no;
    BOOL           cpu_port = (info->action == 1);

    if (info->has_action && info->action == 0) {
        pr("Port counter actions:\n");
        pr("0: Show actions\n");
        pr("1: Show CPU and VD counters\n");
        pr("2: Show MAC counters only\n");
        pr("3: Show QS counters only\n");
        return VTSS_RC_OK;
    }

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count + 4; port_no++) {
        if (port_no < vtss_state->port_count) {
            if (info->port_list[port_no] == 0 || cpu_port) {
                continue;
            }
            pr("Counters for port: %u (chip_port: %u):\n\n", port_no, VTSS_CHIP_PORT(port_no));
        } else {
            if (!cpu_port) {
                continue;
            }
            pr("Counters for chip_port: %u:\n\n",
               RT_CHIP_PORT_CPU + port_no - vtss_state->port_count);
        }
        VTSS_EXIT_ENTER();
        (void)fa_debug_port_counters(vtss_state, ss, info, port_no);
    }
    return VTSS_RC_OK;
}

static char *fa_chip_port_to_str(vtss_state_t *vtss_state, vtss_phys_port_no_t chip_port, char *str)
{
    vtss_port_no_t port_no;
    lmu_fmt_buf_t  buf;

    if (chip_port == -1) {
        // Special case just to get the print function print something special
        VTSS_FMT(buf, "SHARED");
    } else if (chip_port == RT_CHIP_PORT_CPU_0) {
        VTSS_FMT(buf, "CPU0");
    } else if (chip_port == RT_CHIP_PORT_CPU_1) {
        VTSS_FMT(buf, "CPU1");
    } else if (chip_port == RT_CHIP_PORT_VD0) {
        VTSS_FMT(buf, "VD0");
    } else if (chip_port == RT_CHIP_PORT_VD1) {
        VTSS_FMT(buf, "VD1");
    } else if (chip_port == RT_CHIP_PORT_VD2) {
        VTSS_FMT(buf, "VD2");
    } else {
        port_no = vtss_cmn_chip_to_logical_port(vtss_state, vtss_state->chip_no, chip_port);
        if (port_no != VTSS_PORT_NO_NONE) {
            VTSS_FMT(buf, "%u", port_no);
        } else {
            // Port is not in port map. Odd.
            VTSS_E("chip_port = %u not in port map", chip_port);
            VTSS_FMT(buf, "N/A");
        }
    }
    lmu_czstrcpy(str, buf.s);
    return str;
}

static const char *fa_qsys_resource_to_str(u32 resource)
{
    switch (resource) {
    case 0: return "SRC-MEM";

    case 1: return "SRC-REF";

    case 2: return "DST-MEM";

    case 3: return "DST-REF";

    default: VTSS_E("Invalid resource (%u)", resource); break;
    }

    return "INVALID";
}

static void fa_debug_qres_print(vtss_state_t       *vtss_state,
                                lmu_ss_t           *ss,
                                u32                 idx,
                                vtss_phys_port_no_t chip_port,
                                u32                 resource,
                                u32                 prio,
                                u32                 val)
{
    char buf[20];

    pr("%-4u %-8s %7s %9d %4u %10u\n", idx, fa_qsys_resource_to_str(resource),
       fa_chip_port_to_str(vtss_state, chip_port, buf), chip_port, prio, val);
}

vtss_rc vtss_fa_port_debug_qres(vtss_state_t *vtss_state, lmu_ss_t *ss, BOOL res_stat_cur)
{
    vtss_phys_port_no_t chip_port;
    u32                 resource, resource_base, port_base, idx, prio, val, addr;

    pr("\nQSYS Resource table (QRES:RES_CTRL[idx]:RES_STAT%s)\n", res_stat_cur ? "_CUR" : "");
    pr("Idx  Resource Port No Chip Port Prio Value\n");
    pr("---- -------- ------- --------- ---- ----------\n");

    // Print shared SRC-MEM, because up-flows with CL_DP == 1 are counted here
    // and not in the masquerade port counters.

    // The index of the shared SRC-MEM is given by 9 * total-number-of-ports + 8
    // which amounts to 638 on SparX5 and 323 on LAN969x.
    idx = 9 * RT_CHIP_PORTS_ALL + 8;
    addr = res_stat_cur ? REG_ADDR(VTSS_QRES_RES_STAT_CUR(idx)) : REG_ADDR(VTSS_QRES_RES_STAT(idx));
    vtss_fa_rd(vtss_state, addr, &val);
    fa_debug_qres_print(vtss_state, ss, idx, -1, 0, 7, val);

    for (resource = 0; resource < 4; resource++) {
        resource_base = resource * 1024;
        for (chip_port = 0; chip_port < RT_CHIP_PORTS_ALL; chip_port++) {
            port_base = resource_base + chip_port * VTSS_PRIOS;
            for (prio = 0; prio < VTSS_PRIOS; prio++) {
                idx = port_base + prio;
                addr = res_stat_cur ? REG_ADDR(VTSS_QRES_RES_STAT_CUR(idx))
                                    : REG_ADDR(VTSS_QRES_RES_STAT(idx));
                vtss_fa_rd(vtss_state, addr, &val);
                if (val) {
                    // Only print non-zero values or we will be flooded.
                    fa_debug_qres_print(vtss_state, ss, idx, chip_port, resource, prio, val);
                }
            }
        }
    }

    pr("\n");

    if (res_stat_cur) {
        // Also print current number of (about-to-be) free words
        REG_RD(VTSS_HSCH_MMGT, &val);
        pr("MMGT.RELCNT  = %u\n", VTSS_X_HSCH_MMGT_RELCNT(val));
        pr("MMGT.FREECNT = %u\n\n", VTSS_X_HSCH_MMGT_FREECNT(val));
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_wm(vtss_state_t                  *vtss_state,
                           lmu_ss_t                      *ss,
                           const vtss_debug_info_t *const info)
{
    u32 val, port;

    pr("General info:\n");
    pr("-------------\n");
    pr("Total Buffer           : %d bytes\n", RT_BUFFER_MEMORY);
    pr("Total Frame References : %d\n", RT_BUFFER_REFERENCE);
    pr("Cell size              : %d bytes\n", FA_BUFFER_CELL_SZ);
    pr("Num of external ports (vtss_state->port_count)  : %d\n", vtss_state->port_count);
    pr("Num of internal ports  : %d\n", RT_CHIP_PORTS_ALL - RT_CHIP_PORT_CPU);

    pr("\n");
    for (u32 port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no]) {
            continue;
        }
        port = VTSS_CHIP_PORT(port_no);
        pr("Flow Control:\n");
        pr("------------\n");
        REG_RD(VTSS_QSYS_PFC_CFG(port), &val);
        pr("PFC ena (mask)      : 0x%x\n", VTSS_X_QSYS_PFC_CFG_TX_PFC_ENA(val));
        REG_RD(VTSS_DSM_RX_PAUSE_CFG(port), &val);
        pr("FC Rx ena (standard): %d\n", VTSS_X_QSYS_PAUSE_CFG_PAUSE_ENA(val));
        REG_RD(VTSS_QSYS_PAUSE_CFG(port), &val);
        pr("FC Tx ena (standard): %d\n", VTSS_X_QSYS_PAUSE_CFG_PAUSE_ENA(val));
        pr("FC Start            : %d  (%d bytes)\n", VTSS_X_QSYS_PAUSE_CFG_PAUSE_START(val),
           wm_dec(VTSS_X_QSYS_PAUSE_CFG_PAUSE_START(val)) * FA_BUFFER_CELL_SZ);
        pr("FC Stop             : %d  (%d bytes)\n", VTSS_X_QSYS_PAUSE_CFG_PAUSE_STOP(val),
           wm_dec(VTSS_X_QSYS_PAUSE_CFG_PAUSE_STOP(val)) * FA_BUFFER_CELL_SZ);
        REG_RD(VTSS_QSYS_ATOP(port), &val);
        pr("FC Atop             : %d  (%d bytes)\n", VTSS_X_QSYS_ATOP_ATOP(val),
           wm_dec(VTSS_X_QSYS_ATOP_ATOP(val)) * FA_BUFFER_CELL_SZ);
        REG_RD(VTSS_QSYS_ATOP_TOT_CFG, &val);
        pr("FC tot atop         : %d  (%d bytes)\n", VTSS_X_QSYS_ATOP_TOT_CFG_ATOP_TOT(val),
           wm_dec(VTSS_X_QSYS_ATOP_TOT_CFG_ATOP_TOT(val)) * FA_BUFFER_CELL_SZ);
        pr("\n");
    }

    VTSS_RC(fa_debug_wm_qlim(vtss_state, ss, info));

    VTSS_RC(vtss_fa_port_debug_qres(vtss_state, ss, FALSE));
    VTSS_RC(vtss_fa_port_debug_qres(vtss_state, ss, TRUE));

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_port_debug_print(vtss_state_t                  *vtss_state,
                                 lmu_ss_t                      *ss,
                                 const vtss_debug_info_t *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT, fa_debug_port, vtss_state, ss, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT_CNT, fa_debug_port_cnt, vtss_state, ss,
                                   info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_WM, fa_debug_wm, vtss_state, ss, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_SERDES, fa_debug_serdes, vtss_state, ss, info));
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_KR, fa_debug_kr, vtss_state, ss, info));
#endif
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_MUX, fa_debug_mux, vtss_state, ss, info));
    return VTSS_RC_OK;
}
#endif

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_port_init(vtss_state_t *vtss_state)
{
    u32 port;
    VTSS_RC(vtss_fa_serdes_init(vtss_state));

    /* Setup ANA_AC to count local drops and policer drops per port */
    REG_WR(VTSS_ANA_AC_PS_STICKY_MASK_STICKY_MASK(0),
           VTSS_M_ANA_AC_PS_STICKY_MASK_STICKY_MASK_ZERO_DST_STICKY_MASK);
    REG_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK(REG_CNT_ANA_AC_PORT_FILTER),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(1 << 0));
    REG_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK(REG_CNT_ANA_AC_PORT_POLICER_DROPS),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_PORT_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(
               0xf0f0)); /* count policer drops*/
    for (port = 0; port < RT_CHIP_PORTS_ALL; port++) {
        REG_WR(VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG(port, REG_CNT_ANA_AC_PORT_FILTER),
               VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_PRIO_MASK(0xff) |
                   VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_FRM_TYPE(1));
        REG_WR(VTSS_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG(port, REG_CNT_ANA_AC_PORT_POLICER_DROPS),
               VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_PRIO_MASK(0xff) |
                   VTSS_F_ANA_AC_STAT_CNT_CFG_PORT_STAT_CFG_CFG_CNT_FRM_TYPE(1));
    }

    /* Setup ANA_AC to count non-FCS errors per queue */
    REG_WR(VTSS_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG(REG_CNT_ANA_AC_QUEUE_PRIO),
           VTSS_F_ANA_AC_STAT_GLOBAL_CFG_QUEUE_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(0));

    // Count QS drops at egress port
    REG_WR(VTSS_XQS_STAT_CNT_CFG, VTSS_F_XQS_STAT_CNT_CFG_DROP_COUNT_EGRESS(1));

    /* Reset the Port Mux (not done through chip-soft-reset) */
#if !defined(VTSS_ARCH_LAIKA)
    REG_WR(VTSS_PORT_CONF_DEV5G_MODES, 0);
#endif
    REG_WR(VTSS_PORT_CONF_DEV10G_MODES, 0);
    REG_WR(VTSS_PORT_CONF_QSGMII_ENA, 0);
    REG_WR(VTSS_PORT_CONF_USXGMII_ENA, 0);
#if defined(VTSS_ARCH_SPARX5)
    REG_WR(VTSS_PORT_CONF_DEV25G_MODES, 0);
    REG_WR(VTSS_PORT_CONF_USGMII_ENA, 0);
#endif

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    switch (cmd) {
    case VTSS_INIT_CMD_CREATE: break;

    case VTSS_INIT_CMD_INIT:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_INIT, 10);
        VTSS_RC(fa_port_init(vtss_state));
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_INIT, 10);
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_PMAP, 10);
        if (!vtss_state->warm_start_cur) {
            VTSS_RC(fa_port_buf_qlim_set(vtss_state));
        }
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_PMAP, 10);
        break;

    default: break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_FA */
