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

// #include <cyg/infra/diag.h>
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_fa_cil.h"
#if defined(VTSS_ARCH_FA)


/* - Local functions ------------------------------------------------- */

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


u32 vtss_to_dev2g5(u32 p)
{
    if (p < 3)        { return VTSS_TO_DEV2G5_0 + (p) * (VTSS_TO_DEV2G5_1 - VTSS_TO_DEV2G5_0);}
    else if (p < 6)   { return VTSS_TO_DEV2G5_3 + (p - 3) * (VTSS_TO_DEV2G5_4 - VTSS_TO_DEV2G5_3);}
    else if (p < 13)  { return VTSS_TO_DEV2G5_6 + (p - 6) * (VTSS_TO_DEV2G5_7 - VTSS_TO_DEV2G5_6);}
    else if (p == 13) { return VTSS_TO_DEV2G5_13;}
    else if (p < 16)  { return VTSS_TO_DEV2G5_14 + (p - 14) * (VTSS_TO_DEV2G5_15 - VTSS_TO_DEV2G5_14);}
    else if (p < 24)  { return VTSS_TO_DEV2G5_16 + (p - 16) * (VTSS_TO_DEV2G5_17 - VTSS_TO_DEV2G5_16);}
    else if (p < 32)  { return VTSS_TO_DEV2G5_24 + (p - 24) * (VTSS_TO_DEV2G5_25 - VTSS_TO_DEV2G5_24);}
    else if (p < 48)  { return VTSS_TO_DEV2G5_32 + (p - 32) * (VTSS_TO_DEV2G5_33 - VTSS_TO_DEV2G5_32);}
    else if (p < 57)  { return VTSS_TO_DEV2G5_48 + (p - 48) * (VTSS_TO_DEV2G5_49 - VTSS_TO_DEV2G5_48);}
    else if (p == 57) { return VTSS_TO_DEV2G5_57;}
    else if (p == 58) { return VTSS_TO_DEV2G5_58;}
    else if (p == 59) { return VTSS_TO_DEV2G5_59;}
    else if (p == 60) { return VTSS_TO_DEV2G5_60;}
    else if (p < 64)  { return VTSS_TO_DEV2G5_61 + (p - 61) * (VTSS_TO_DEV2G5_62 - VTSS_TO_DEV2G5_61);}
    else if (p == 64) { return VTSS_TO_DEV2G5_64;}
    else {
        VTSS_E("illegal 2G5 port number %d",p);
        return 0;
    }
}

u32 vtss_to_dev5g(u32 port)
{
    u32 p = VTSS_PORT_DEV_INDX(port);
    switch (p) {
    case 0:  return VTSS_TO_DEV5G_0;
    case 1:  return VTSS_TO_DEV5G_1;
    case 2:  return VTSS_TO_DEV5G_2;
    case 3:  return VTSS_TO_DEV5G_3;
    case 4:  return VTSS_TO_DEV5G_4;
    case 5:  return VTSS_TO_DEV5G_5;
    case 6:  return VTSS_TO_DEV5G_6;
    case 7:  return VTSS_TO_DEV5G_7;
    case 8:  return VTSS_TO_DEV5G_8;
    case 9:  return VTSS_TO_DEV5G_9;
    case 10: return VTSS_TO_DEV5G_10;
    case 11: return VTSS_TO_DEV5G_11;
    case 12: return VTSS_TO_DEV5G_64;
    default:
        VTSS_E("illegal 5G port number %d",port);
        return 0;
    }
}

u32 vtss_to_dev10g(u32 port)
{
    u32 p = VTSS_PORT_DEV_INDX(port);
    switch (p) {
    case 0:  return VTSS_TO_DEV10G_0;
    case 1:  return VTSS_TO_DEV10G_1;
    case 2:  return VTSS_TO_DEV10G_2;
    case 3:  return VTSS_TO_DEV10G_3;
    case 4:  return VTSS_TO_DEV10G_4;
    case 5:  return VTSS_TO_DEV10G_5;
    case 6:  return VTSS_TO_DEV10G_6;
    case 7:  return VTSS_TO_DEV10G_7;
    case 8:  return VTSS_TO_DEV10G_8;
    case 9:  return VTSS_TO_DEV10G_9;
    case 10: return VTSS_TO_DEV10G_10;
    case 11: return VTSS_TO_DEV10G_11;
    default:
        VTSS_E("illegal 10G port number %d",port);
        return 0;
    }
}

u32 vtss_to_dev25g(u32 port)
{
    u32 p = VTSS_PORT_DEV_INDX(port);
    switch (p) {
    case 0: return VTSS_TO_DEV25G_0;
    case 1: return VTSS_TO_DEV25G_1;
    case 2: return VTSS_TO_DEV25G_2;
    case 3: return VTSS_TO_DEV25G_3;
    case 4: return VTSS_TO_DEV25G_4;
    case 5: return VTSS_TO_DEV25G_5;
    case 6: return VTSS_TO_DEV25G_6;
    case 7: return VTSS_TO_DEV25G_7;
    default:
        VTSS_E("illegal 25G port number %d",port);
        return 0;
    }
}

u32 vtss_to_pcs5g(u32 port)
{
    u32 p = VTSS_PORT_DEV_INDX(port);
    switch (p) {
    case 0:  return VTSS_TO_PCS5G_BR_0;
    case 1:  return VTSS_TO_PCS5G_BR_1;
    case 2:  return VTSS_TO_PCS5G_BR_2;
    case 3:  return VTSS_TO_PCS5G_BR_3;
    case 4:  return VTSS_TO_PCS5G_BR_4;
    case 5:  return VTSS_TO_PCS5G_BR_5;
    case 6:  return VTSS_TO_PCS5G_BR_6;
    case 7:  return VTSS_TO_PCS5G_BR_7;
    case 8:  return VTSS_TO_PCS5G_BR_8;
    case 9:  return VTSS_TO_PCS5G_BR_9;
    case 10: return VTSS_TO_PCS5G_BR_10;
    case 11: return VTSS_TO_PCS5G_BR_11;
    case 12: return VTSS_TO_PCS5G_BR_64;
    default:
        VTSS_E("illegal 5G port number %d",p);
        return 0;
    }
}

u32 vtss_to_pcs10g(u32 port)
{
    u32 p = VTSS_PORT_DEV_INDX(port);
    switch (p) {
    case 0:  return VTSS_TO_PCS10G_BR_0;
    case 1:  return VTSS_TO_PCS10G_BR_1;
    case 2:  return VTSS_TO_PCS10G_BR_2;
    case 3:  return VTSS_TO_PCS10G_BR_3;
    case 4:  return VTSS_TO_PCS10G_BR_4;
    case 5:  return VTSS_TO_PCS10G_BR_5;
    case 6:  return VTSS_TO_PCS10G_BR_6;
    case 7:  return VTSS_TO_PCS10G_BR_7;
    case 8:  return VTSS_TO_PCS10G_BR_8;
    case 9:  return VTSS_TO_PCS10G_BR_9;
    case 10: return VTSS_TO_PCS10G_BR_10;
    case 11: return VTSS_TO_PCS10G_BR_11;
    default:
        VTSS_E("illegal 10G port number %d",p);
        return 0;
    }
}

u32 vtss_to_pcs25g(u32 port)
{
    u32 p = VTSS_PORT_DEV_INDX(port);
    switch (p) {
    case 0: return VTSS_TO_PCS25G_BR_0;
    case 1: return VTSS_TO_PCS25G_BR_1;
    case 2: return VTSS_TO_PCS25G_BR_2;
    case 3: return VTSS_TO_PCS25G_BR_3;
    case 4: return VTSS_TO_PCS25G_BR_4;
    case 5: return VTSS_TO_PCS25G_BR_5;
    case 6: return VTSS_TO_PCS25G_BR_6;
    case 7: return VTSS_TO_PCS25G_BR_7;
    default:
        VTSS_E("illegal 25G port number %d",p);
        return 0;
    }
}

u32 vtss_fa_dev_tgt(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 p = VTSS_CHIP_PORT(port_no);
    return (vtss_state->port.conf[port_no].speed <= VTSS_SPEED_2500M) ? VTSS_TO_DEV2G5(p) : VTSS_TO_HIGH_DEV(p);
}

static vtss_rc fa_port_clause_37_control_get(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no,
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

static vtss_rc fa_port_clause_37_control_set(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no)
{
    vtss_port_clause_37_control_t *control = &vtss_state->port.clause_37[port_no];
    u32 value;
    u32 tgt = VTSS_TO_DEV2G5(VTSS_CHIP_PORT(port_no));

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


static vtss_rc fa_port_clause_37_status_get(vtss_state_t *vtss_state,
                                              const vtss_port_no_t         port_no,
                                              vtss_port_clause_37_status_t *const status)

{
    u32 value, port = VTSS_CHIP_PORT(port_no);
    u32 tgt = VTSS_TO_DEV2G5(port);
    vtss_port_sgmii_aneg_t *sgmii_adv = &status->autoneg.partner_adv_sgmii;

    if (vtss_state->port.conf[port_no].power_down) {
        status->link = 0;
        return VTSS_RC_OK;
    }

    /* Get the link state 'down' sticky bit  */
    REG_RD(VTSS_DEV1G_PCS1G_STICKY(tgt), &value);
    status->link = (REG_BF(DEV1G_PCS1G_STICKY_LINK_DOWN_STICKY, value) ? 0 : 1);
    if (status->link == 0) {
        /* The link has been down. Clear the sticky bit and return the 'down' value  */
        REG_WR(VTSS_DEV1G_PCS1G_STICKY(tgt),
                VTSS_M_DEV1G_PCS1G_STICKY_LINK_DOWN_STICKY);
    } else {
       /* PCS1G_LINK_STATUS holds the result of 1) aneg-enable=LINK_OK or 2) aneg-disable=AN_DISABLE_LINK_OK */
        REG_RD(VTSS_DEV1G_PCS1G_LINK_STATUS(tgt), &value);
        status->link = REG_BF(DEV1G_PCS1G_LINK_STATUS_LINK_STATUS, value) &&
                       REG_BF(DEV1G_PCS1G_LINK_STATUS_SYNC_STATUS, value);
    }

    /* Get PCS ANEG status register */
    REG_RD(VTSS_DEV1G_PCS1G_ANEG_STATUS(tgt), &value);

    /* Get 'Aneg complete'   */
    status->autoneg.complete = REG_BF(DEV1G_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);

    /* Return partner advertisement ability */
    value = VTSS_X_DEV1G_PCS1G_ANEG_STATUS_LP_ADV_ABILITY(value);

    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
        VTSS_RC(vtss_cmn_port_sgmii_cisco_aneg_get(value, sgmii_adv));
        /* status->link = PCS link. sgmii_adv->link = Phy link */
        status->link = sgmii_adv->link & status->link;
    } else {
        VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &status->autoneg.partner_advertisement));
    }

    return VTSS_RC_OK;
}

static BOOL fa_change_device(vtss_state_t *vtss_state, vtss_port_no_t port_no) {
    u32 port = VTSS_CHIP_PORT(port_no);

    if (VTSS_PORT_IS_2G5(port)) {
        return FALSE; // This is the primary device
    }

    if ((((vtss_state->port.current_speed[port_no] <= VTSS_SPEED_2500M) && (vtss_state->port.conf[port_no].speed > VTSS_SPEED_2500M))) ||
       ((vtss_state->port.current_speed[port_no] > VTSS_SPEED_2500M) && (vtss_state->port.conf[port_no].speed <= VTSS_SPEED_2500M)) ||
       (vtss_state->port.current_speed[port_no] == VTSS_SPEED_UNDEFINED)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static BOOL fa_is_high_speed_device(vtss_state_t *vtss_state, vtss_port_no_t port_no) {
    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SXGMII ||
        vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_DXGMII_10G) {
       return TRUE;
    }
    return vtss_state->port.conf[port_no].speed > VTSS_SPEED_2500M ? TRUE : FALSE;
}

#define MULTIPLIER_BIT 2048

static u16 wm_enc(u16 value)
{
    if (value >= MULTIPLIER_BIT) {
        return MULTIPLIER_BIT + value / 16;
    }
    return value;
}


/* - CIL functions ------------------------------------------------- */

/* ================================================================= *
 *  Synce
 * ================================================================= */

#if defined(VTSS_FEATURE_SYNCE)
static vtss_rc fa_synce_clock_out_set(vtss_state_t *vtss_state, const vtss_synce_clk_port_t clk_port)
{
    u32 div_mask;

    if (clk_port > 3) {
        VTSS_E("Invalid clock port no: %d\n", clk_port);
        return VTSS_RC_ERROR;
    }
    VTSS_D("clk_port %X  enable %u\n", clk_port, vtss_state->synce.out_conf[clk_port].enable);

    switch (vtss_state->synce.out_conf[clk_port].divider) {
        case VTSS_SYNCE_DIVIDER_2:  div_mask = 0; break;
        case VTSS_SYNCE_DIVIDER_4:  div_mask = 1; break;
        case VTSS_SYNCE_DIVIDER_8:  div_mask = 2; break;
        case VTSS_SYNCE_DIVIDER_16: div_mask = 3; break;
        case VTSS_SYNCE_DIVIDER_5:  div_mask = 4; break;
        case VTSS_SYNCE_DIVIDER_25: div_mask = 5; break;
        default:                    div_mask = 0; break;
    }
    REG_WRM(VTSS_HSIOWRAP_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(div_mask) |
            VTSS_F_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA(vtss_state->synce.out_conf[clk_port].enable),
            VTSS_M_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV |
            VTSS_M_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA);

    return VTSS_RC_OK;
}

static vtss_rc fa_synce_clock_in_set(vtss_state_t *vtss_state, const vtss_synce_clk_port_t clk_port)
{
    vtss_synce_clock_in_t      *conf;
    vtss_synce_clock_in_type_t port_type;
    i32                        chip_port = 0;
    i32                        clk_src;
    BOOL                       ena;

    if (clk_port > 3) {
        VTSS_E("Invalid clock port no: %d\n", clk_port);
        return VTSS_RC_ERROR;
    }
    conf = &vtss_state->synce.in_conf[clk_port];
    if (conf->port_no >= VTSS_PORT_ARRAY_SIZE) {
        VTSS_E("Invalid port no: %d\n", conf->port_no);
        return VTSS_RC_ERROR;
    }
    ena = conf->enable;
    port_type = conf->clk_in;

    if (port_type == VTSS_SYNCE_CLOCK_INTERFACE) {  /* Port type is interface so the clock source is a SerDes */
        /* The SerDes number is the clock source */
        chip_port = vtss_state->port.map[conf->port_no].chip_port;
        if (chip_port <= 15) {
            clk_src = chip_port + 1;
        } else if (chip_port >= 48 && chip_port <= 63) {
            clk_src = chip_port - 31;
        } else {
            VTSS_E("SyncE not supported for port_no %u, chip port %u", conf->port_no, chip_port);
            return VTSS_RC_ERROR;
        }
    } else if (port_type == VTSS_SYNCE_CLOCK_AUX) {  /* Port type is AUX so the clock source is the AUX number */
        if (conf->port_no > 3) {
            VTSS_E("AUX port out of range.  port_no %u", conf->port_no);
            return VTSS_RC_ERROR;
        }
        clk_src = conf->port_no + 33;
    } else {
        VTSS_E("Port type not supported for port_no %u, port_type %u", conf->port_no, port_type);
        return VTSS_RC_ERROR;
    }
    VTSS_D("clk_port %X, port_no %u, chip port %u enable %u, squelsh %u, clk_src %d\n", clk_port, conf->port_no, chip_port, ena, conf->squelsh, clk_src);

    /* Configure the SerDes to select for recovered clock */
    REG_WRM(VTSS_HSIOWRAP_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(clk_src) |
            VTSS_F_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA(ena),
            VTSS_M_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC |
            VTSS_M_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA);

    if (ena) {
        /* Enable input clock configuration - now configuring the new (or maybe the same) input port */
        if (clk_src > 24) { /* SerDes 25 to 32 is 25G that has extra clock divider configuration */
            if (vtss_state->port.conf[conf->port_no].speed == VTSS_SPEED_1G) {
                REG_WRM(VTSS_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG(clk_src),
                        VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(0) |
                        VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(conf->squelsh),
                        VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV |
                        VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA);
            } else {
                REG_WRM(VTSS_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG(clk_src),
                        VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(1) |
                        VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(conf->squelsh),
                        VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV |
                        VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA);
            }
        } else {
            REG_WRM(VTSS_SD_LANE_TARGET_SYNC_ETH_SD_CFG(clk_src),
                    VTSS_F_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(conf->squelsh),
                    VTSS_M_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA);
        }
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_SYNCE */

/* ================================================================= *
 *  Port control
 * ================================================================= */

/* PHY commands */
#define PHY_CMD_ADDRESS  0 /* 10G: Address */
#define PHY_CMD_WRITE    1 /* 1G/10G: Write */
#define PHY_CMD_READ_INC 2 /* 1G: Read, 10G: Read and increment */
#define PHY_CMD_READ     3 /* 10G: Read */

static vtss_rc fa_miim_cmd(vtss_state_t *vtss_state,
                            u32 cmd, u32 sof, vtss_miim_controller_t miim_controller,
                            u8 miim_addr, u8 addr, u16 *data, BOOL report_errors)
{
    u32 i, n;
    u32 value;

    switch (miim_controller) {
    case VTSS_MIIM_CONTROLLER_0:
        i = 0;
        break;
    case VTSS_MIIM_CONTROLLER_1:
        i = 1;
        break;
    case VTSS_MIIM_CONTROLLER_2:
        i = 2;
        break;
    case VTSS_MIIM_CONTROLLER_3:
        i = 3;
        break;
    default:
        VTSS_E("illegal miim_controller: %d", miim_controller);
        return VTSS_RC_ERROR;
    }

    /* Set Start of frame field */
    REG_WR(VTSS_DEVCPU_GCB_MII_CFG(i),
           VTSS_F_DEVCPU_GCB_MII_CFG_MIIM_CFG_PRESCALE(0x32) |
           VTSS_F_DEVCPU_GCB_MII_CFG_MIIM_ST_CFG_FIELD(sof));

    /* Read command is different for Clause 22 */
    if (sof == 1 && cmd == PHY_CMD_READ) {
        cmd = PHY_CMD_READ_INC;
    }

    /* Start command */
    REG_WR(VTSS_DEVCPU_GCB_MII_CMD(i),
           VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_VLD |
           VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_PHYAD(miim_addr) |
           VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_REGAD(addr) |
           VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_WRDATA(*data) |
           VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_OPR_FIELD(cmd));

    /* Wait for access to complete */
    for (n = 0; ; n++) {
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
    if(report_errors) {
        VTSS_E("miim failed, cmd: %s, miim_addr: %u, addr: %u, miim_controller:%u, sof:%u",
               cmd == PHY_CMD_READ ? "PHY_CMD_READ" :
               cmd == PHY_CMD_WRITE ? "PHY_CMD_WRITE" :
               cmd == PHY_CMD_ADDRESS ? "PHY_CMD_ADDRESS" : "PHY_CMD_READ_INC",
               miim_addr, addr, miim_controller, sof);
    }

    return VTSS_RC_ERROR;
}

static vtss_rc fa_miim_read(vtss_state_t *vtss_state,
                              vtss_miim_controller_t miim_controller,
                              u8 miim_addr,
                              u8 addr,
                              u16 *value,
                              BOOL report_errors)
{
    return fa_miim_cmd(vtss_state, PHY_CMD_READ, 1, miim_controller, miim_addr, addr, value, report_errors);
}

static vtss_rc fa_miim_write(vtss_state_t *vtss_state,
                               vtss_miim_controller_t miim_controller,
                               u8 miim_addr,
                               u8 addr,
                               u16 value,
                               BOOL report_errors)
{
    return fa_miim_cmd(vtss_state, PHY_CMD_WRITE, 1, miim_controller, miim_addr, addr, &value, report_errors);
}

static vtss_rc fa_mmd_read(vtss_state_t *vtss_state,
                            vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                            u16 addr, u16 *value, BOOL report_errors)
{

    VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd,
                         &addr, report_errors));
    if (fa_miim_cmd(vtss_state, PHY_CMD_READ, 0, miim_controller, miim_addr, mmd,
                     value, 0) != VTSS_RC_OK) {
        if (report_errors) {
            VTSS_E("fa_mmd_read failed, miim_controller:%d miim_addr:%x, mmd:%x, addr:%x",miim_controller, miim_addr, mmd, addr);
        }
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

/* MMD (MDIO Management Devices (10G)) read-inc */
static vtss_rc fa_mmd_read_inc(vtss_state_t *vtss_state,
                                vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                u16 addr, u16 *buf, u8 count, BOOL report_errors)
{

    VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd,
                         &addr, report_errors));
    while (count > 1) {
        VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_READ_INC, 0, miim_controller, miim_addr, mmd,
                             buf, report_errors));
        buf++;
        count--;
    }
    VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_READ, 0, miim_controller, miim_addr, mmd,
                         buf, report_errors));
    return VTSS_RC_OK;
}


/* MMD (MDIO Management Devices (10G)) write */
static vtss_rc fa_mmd_write(vtss_state_t *vtss_state,
                             vtss_miim_controller_t miim_controller,
                             u8 miim_addr, u8 mmd, u16 addr, u16 data,  BOOL report_errors)
{
    VTSS_RC(fa_miim_cmd(vtss_state, PHY_CMD_ADDRESS, 0, miim_controller, miim_addr, mmd,
                         &addr, report_errors));
    return fa_miim_cmd(vtss_state, PHY_CMD_WRITE, 0, miim_controller, miim_addr, mmd,
                        &data, report_errors);
}


static vtss_rc fa_port_conf_get(vtss_state_t *vtss_state,
                                  const vtss_port_no_t port_no, vtss_port_conf_t *const conf)
{
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_10GBASE_KR_V2)

static vtss_rc fa_port_10g_kr_status(vtss_state_t *vtss_state,
                                      const vtss_port_no_t port_no,
                                      vtss_port_10g_kr_status_t *const status)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_port_10g_kr_conf_set(vtss_state_t *vtss_state,
                                        const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_10G_BASE_KR */

/* Source: ffl_sqs.tcl in verification */
static u32 port_fwd_urg(vtss_state_t *vtss_state, vtss_port_speed_t speed)
{
    u32 clk_period_ps = 2000, urg = 672000;

    switch (vtss_state->init_conf.core_clock.freq) {
    case VTSS_CORE_CLOCK_250MHZ: clk_period_ps = 4000; break;
    case VTSS_CORE_CLOCK_500MHZ: clk_period_ps = 2000; break;
    case VTSS_CORE_CLOCK_625MHZ: clk_period_ps = 1600; break;
    default:{ VTSS_E("Clock freq not supported"); }
    }

    switch (speed) {
    case VTSS_SPEED_10M:
    case VTSS_SPEED_100M:
    case VTSS_SPEED_1G:    urg = 672000; break;
    case VTSS_SPEED_2500M: urg = 270000; break;
    case VTSS_SPEED_5G:    urg = 135000; break;
    case VTSS_SPEED_10G:   urg = 67200;  break;
    case VTSS_SPEED_25G:   urg = 27000;  break;
    default:{ VTSS_E("Speed not supported"); }
    }
    return urg/(clk_period_ps-1);
}

static BOOL fa_vrfy_spd_iface(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_port_interface_t if_type, vtss_port_speed_t speed, BOOL fdx)
{
    u32 port = VTSS_CHIP_PORT(port_no);

    if ((VTSS_PORT_IS_2G5(port) && (speed > VTSS_SPEED_2500M)) ||
        (VTSS_PORT_IS_5G(port)  && (speed > VTSS_SPEED_5G)) ||
        (VTSS_PORT_IS_10G(port) && (speed > VTSS_SPEED_10G))) {
        VTSS_E("Port %d (dev%s) does not support speed '%s'", port, VTSS_PORT_IS_10G(port) ? "10G": \
               VTSS_PORT_IS_5G(port) ? "5G" : "2G5", vtss_port_spd_txt(speed));
        return FALSE;
    }

    switch (if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        return FALSE;

    case VTSS_PORT_INTERFACE_SERDES:
        if ((speed != VTSS_SPEED_1G && speed != VTSS_SPEED_2500M) || VTSS_PORT_IS_2G5(port) || !fdx) {
            VTSS_E("Illegal if, speed or duplex. Serdes port interface supports 1G/2G5/fdx (port:%u speed:%d fdx:%d)",port, speed, fdx);
            return FALSE;
        }
        if (VTSS_PORT_IS_2G5(port)) {
            VTSS_E("port %d does not support interface SERDES",port);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
    case VTSS_PORT_INTERFACE_USGMII: /* USGMII: 8x2G5 devices. Mode 'X'  Use 2G5 device. */
        if (port > 47) {
            VTSS_E("port %d does not support QSGMII",port);
            return FALSE;
        }
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M && speed != VTSS_SPEED_2500M) {
            VTSS_E("QSGMII/USGMII port interface only supports 10/100/1000M/2.5G speeds (port:%u)",port);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M && speed != VTSS_SPEED_2500M) {
            VTSS_E("SGMII port interface only supports 10/100/1000M/2.5G speeds (port:%u)",port);
            return FALSE;
        }
        if (VTSS_PORT_IS_2G5(port)) {
            VTSS_E("port %d does not support interface type SGMII",port);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_100FX:
        if (speed != VTSS_SPEED_100M || VTSS_PORT_IS_2G5(port) || !fdx) {
            VTSS_E("Illegal if, speed or duplex (port:%u speed:%d if:100FX fdx:%d)",port, speed, fdx);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_SFI:
        if ((speed != VTSS_SPEED_5G && speed != VTSS_SPEED_10G && speed != VTSS_SPEED_25G) || !fdx) {
            VTSS_E("SFI port interface only supports 5G/10G/25G/fdx (port:%u speed:%d fdx:%d)",port, speed, fdx);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        if (speed != VTSS_SPEED_2500M || !fdx) {
            VTSS_E("VAUI port interface only supports 2.5G/fdx speed (port:%u speed:%d fdx:%d)",port, speed, fdx);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_SXGMII:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M &&
            speed != VTSS_SPEED_2500M && speed != VTSS_SPEED_5G && speed != VTSS_SPEED_10G) {
            VTSS_E("SXGMII port interface supports speeds 10M-10G (port:%u speed:%d)",port, speed);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_5G:  /* DXGMII_5G: 2x2G5 devices. Mode 'F'. Use 2G5 device. */
        if (port > 64) {
            VTSS_E("port %d does not support DXGMII",port);
            return FALSE;
        }
    case VTSS_PORT_INTERFACE_QXGMII:     /* QXGMII:    4x2G5 devices. Mode 'R'. Use 2G5 device. */
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M &&
            speed != VTSS_SPEED_2500M) {
            VTSS_E("SXGMII/DXGMII_5G port interface supports speeds 10M-2G5 (port:%u speed:%d)",port, speed);
            return FALSE;
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: /* DXGMII_10G: 2x5G devices.  Mode 'U'. Use primary device.*/
        if (port <= 63 && (port <= 15 || port >= 48)) {
            if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_10M &&
                speed != VTSS_SPEED_2500M && speed != VTSS_SPEED_5G) {
                VTSS_E("DXGMII_10G port interface supports speeds 10M-5G (port:%u speed:%d)",port, speed);
                return FALSE;
            }
        } else {
            VTSS_E("port %d does not support DSGMII_10G",port);
            return FALSE;
        }
        break;
    default:
        VTSS_E("Illegal interface type (%d)",if_type);
        return FALSE;
    }
    return TRUE;
}

// Configure port muxing:
// QSGMII:     4x2G5 devices
// USGMII:     8x2G5 devices.
// QXGMII:     4x2G5 devices.
// DXGMII_5G:  2x2G5 devices
// DXGMII_10G: 2x5G  devices.
static vtss_rc fa_port_mux_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 p = VTSS_CHIP_PORT(port_no), Q,X,R,U,F;

    if (vtss_state->port.current_if_type[port_no] == vtss_state->port.conf[port_no].if_type) {
        return VTSS_RC_OK; // Nothing to do
    }

    switch (vtss_state->port.conf[port_no].if_type) {
    case VTSS_PORT_INTERFACE_QSGMII: /* QSGMII: 4x2G5 devices. Mode Q'  */
        Q = (p - p % 4) / 4;
        REG_WRM(VTSS_PORT_CONF_QSGMII_ENA, VTSS_BIT(Q), VTSS_BIT(Q));
        break;
    case VTSS_PORT_INTERFACE_USGMII: /* USGMII: 8x2G5 devices. Mode 'X'  Use 2G5 device. */
        X = (p - p % 8) / 8;
        REG_WRM(VTSS_PORT_CONF_USGMII_ENA, VTSS_BIT(X), VTSS_BIT(X));
        break;
    case VTSS_PORT_INTERFACE_QXGMII:     /* QXGMII:    4x2G5 devices. Mode 'R'. Use 2G5 device. */
        R = (p < 16) ? p : (p < 32) ? p - 16 : (p < 48) ? p - 32 : p - 48;
        REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(R),
                VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(2),
                VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);
        R = R + 16;
        REG_WRM(VTSS_PORT_CONF_USXGMII_ENA, VTSS_BIT(R), VTSS_BIT(R));
        break;
    case VTSS_PORT_INTERFACE_DXGMII_5G:  /* DXGMII_5G: 2x2G5 devices. Mode 'F'. Use 2G5 device. */
        F = (p - p % 8) / 8;
        REG_WRM(VTSS_PORT_CONF_USGMII_ENA, VTSS_BIT(F), VTSS_BIT(F));
        REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(F),
                VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(1),
                VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: /* DXGMII_10G: 2x5G devices.  Mode 'U'. Use primary device.*/
        U = (p < 16) ? p : p - 48;
        REG_WRM(VTSS_PORT_CONF_USXGMII_CFG(U),
                VTSS_F_PORT_CONF_USXGMII_CFG_NUM_PORTS(1),
                VTSS_M_PORT_CONF_USXGMII_CFG_NUM_PORTS);
        U = U + 16;
        REG_WRM(VTSS_PORT_CONF_USGMII_ENA, VTSS_BIT(U), VTSS_BIT(U));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_serdes_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_serdes_mode_t serdes_mode)
{
//    VTSS_RC(vtss_fa_sd_cfg(vtss_state, port_no, serdes_mode)); TBD-BJO
    vtss_state->port.serdes_mode[port_no] = serdes_mode;
    return VTSS_RC_OK;
}

static vtss_rc fa_port_afi_flush(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
#if defined(VTSS_FEATURE_AFI_SWC)
    u32 afi_cnt = 0, afi_val, port = VTSS_CHIP_PORT(port_no);

    // At this point in time, all AFI flows on this port must have been
    // stopped, so that we can flush the port's queues.
    // If it isn't stopped, we might end up corrupting the queue system
    // and send garbage frames out when the port comes back up and the AFI
    // re-enables disabled flows (see BZ#20083, BZ#20189 and BZ#20191 (especially the latter)).

    // "AFI stop" is controlled by the AIL layer.

    // Here, we just make sure that the AFI has no frames outstanding in the queue
    // system by waiting up to 1 second for all AFI flows on this port to get out of the
    // queue system. The 1 second is chosen so that it's very unlikely that the up to
    // AFI::FRM_OUT_MAX frames don't get out of the queue system even when
    // a port shaper is enabled.
    while (afi_cnt < 20) {
        REG_RD(VTSS_AFI_PORT_FRM_OUT(port), &afi_val);
        afi_val = VTSS_X_AFI_PORT_FRM_OUT_FRM_OUT_CNT(afi_val);

        if (afi_val != 0) {
            VTSS_MSLEEP(50);
            if (++afi_cnt == 20) {
                // If this happens, it may be that the port's Tx clock is not running,
                // so that frames are not getting out.
                VTSS_E("AFI's FRM_OUT_CNT is non-zero (%u) on port %u (phys. port %u) even after 1 sec of trying", afi_val, port_no, port);
                // One should probably reboot here, because of the possible frame corruption...
            }
        } else {
            break;
        }
    }

    VTSS_I("Waited %u ms for AFI flows to exit the queue system for port %u (phys. port %u)", afi_cnt * 50, port_no, port);
#endif /* defined(VTSS_FEATURE_AFI_SWC) */
    return VTSS_RC_OK;
}

/* Configure 802.1Qbb Priority Flow Control */
static vtss_rc fa_port_pfc(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u32 q, pfc_mask = 0;
    u32 spd = (conf->speed == VTSS_SPEED_10G) ? 1 :
              (conf->speed == VTSS_SPEED_2500M) ? 2 :
              (conf->speed == VTSS_SPEED_1G) ? 3 :
              (conf->speed == VTSS_SPEED_100M) ? 4 : 5;

    /* ASM / Rx enable */
    for (q = 0; q < VTSS_PRIOS; q++) {
        pfc_mask |= conf->flow_control.pfc[q] ? (1 << q) : 0;
    }
    REG_WRM(VTSS_ASM_PFC_CFG(port),
            VTSS_F_ASM_PFC_CFG_RX_PFC_ENA(pfc_mask) |
            VTSS_F_ASM_PFC_CFG_FC_LINK_SPEED(spd),
            VTSS_M_ASM_PFC_CFG_RX_PFC_ENA |
            VTSS_M_ASM_PFC_CFG_FC_LINK_SPEED);

    /* HQOS Scheduling must be in 'normal' mode otherwise PFC will not work */
    /* Use pfc status for the port on layer 1 */
    REG_WRM(VTSS_HSCH_PFC_CFG(port),
            VTSS_F_HSCH_PFC_CFG_PFC_LAYER(VTSS_BOOL(pfc_mask)),
            VTSS_M_HSCH_PFC_CFG_PFC_LAYER);

    /* Scheduler element = port in normal mode */
    REG_WRM(VTSS_HSCH_PFC_CFG(port),
            VTSS_F_HSCH_PFC_CFG_PFC_SE(port),
            VTSS_M_HSCH_PFC_CFG_PFC_SE);

    /* ASM must not dropASM_CFG PFC frames as the PFC detection is done on the cellbus interface */
    REG_WRM(VTSS_ASM_PAUSE_CFG(port),
            VTSS_F_ASM_PAUSE_CFG_ABORT_CTRL_ENA(!VTSS_BOOL(pfc_mask)),
            VTSS_M_ASM_PAUSE_CFG_ABORT_CTRL_ENA);

    /* DSM / Tx enable */
    REG_WRM(VTSS_QSYS_PFC_CFG(port),
            VTSS_F_QSYS_PFC_CFG_TX_PFC_ENA(pfc_mask),
            VTSS_M_QSYS_PFC_CFG_TX_PFC_ENA);

    REG_WRM(VTSS_DSM_ETH_PFC_CFG(port),
            VTSS_F_DSM_ETH_PFC_CFG_PFC_ENA(VTSS_BOOL(pfc_mask)),
            VTSS_M_DSM_ETH_PFC_CFG_PFC_ENA);

    /* When enabled let the queue system generate Pause frames to avoid HOL */
    REG_WRM(VTSS_DSM_RX_PAUSE_CFG(port),
            VTSS_F_DSM_RX_PAUSE_CFG_FC_OBEY_LOCAL(VTSS_BOOL(pfc_mask)),
            VTSS_M_DSM_RX_PAUSE_CFG_FC_OBEY_LOCAL);

    /* Disable Port memory */
    REG_WR(VTSS_QRES_RES_CFG((4096 + port + 512)), 0);

    /* Disable Shared Prio memory */
    for (q = 0; q < VTSS_PRIOS; q++) {
        REG_WR(VTSS_QRES_RES_CFG((4096 + q + 496)), 0);
    }

    /* Disable Shared DP memory */
    for (q = 0; q < 4; q++) {
        REG_WR(VTSS_QRES_RES_CFG((4096 + q + 508)), 0);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_port_fc_setup(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u8                *smac = &conf->flow_control.smac.addr[0], q;
    BOOL              pfc = 0, fc_gen = conf->flow_control.generate, fc_obey = conf->flow_control.obey;
    vtss_port_no_t    port_no;
    u32               pause_start = 20;   // Number of cells (chip default)
    u32               pause_stop  = 20;   // Number of cells (chip default)
    u32               atop        = 20;   // Number of cells (chip default)
    u32               atop_tot    = 0x7FF;// Number of cells (chip default)

    for (q = 0; q < VTSS_PRIOS; q++) {
        if (conf->flow_control.pfc[q]) {
            pfc = 1;
            if (fc_gen || fc_obey) {
                VTSS_E("802.3x FC and 802.1Qbb PFC cannot both be enabled, chip port %u",port);
                return VTSS_RC_ERROR;
            }
        }
    }

    /* Configure 802.1Qbb PFC */
    VTSS_RC(fa_port_pfc(vtss_state, port, conf));

    /* If FC is enabled then set the FC WMs */
    if (pfc || fc_gen || fc_obey) {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (vtss_state->port.conf[port_no].flow_control.generate || pfc) {
                atop_tot = 0; //  Generate FC early if any port is in FC mode
            }
        }
        if (conf->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
            atop = (20 * VTSS_MAX_FRAME_LENGTH_STANDARD) / FA_BUFFER_CELL_SZ;
        } else {
            atop = 40000 / FA_BUFFER_CELL_SZ;
        }
        /* Apply encoding */
        pause_start = wm_enc(8 * (VTSS_MAX_FRAME_LENGTH_STANDARD / FA_BUFFER_CELL_SZ));
        pause_stop  = wm_enc(4 * (VTSS_MAX_FRAME_LENGTH_STANDARD / FA_BUFFER_CELL_SZ));
        atop        = wm_enc(atop);
        atop_tot    = wm_enc(atop_tot);
    }

    /* Set Pause WM hysteresis */
    REG_WR(VTSS_QSYS_PAUSE_CFG(port),
           VTSS_F_QSYS_PAUSE_CFG_PAUSE_START(pause_start) |
           VTSS_F_QSYS_PAUSE_CFG_PAUSE_STOP(pause_stop) |
           VTSS_F_QSYS_PAUSE_CFG_PAUSE_ENA(0)); // enabled after reset

    /* Port ATOP */
    REG_WR(VTSS_QSYS_ATOP(port),
           VTSS_F_QSYS_ATOP_ATOP(atop));

    /* Total ATOP */
    REG_WR(VTSS_QSYS_ATOP_TOT_CFG,
           VTSS_F_QSYS_ATOP_TOT_CFG_ATOP_TOT(atop_tot));

    /* Set SMAC of Pause frame */
    REG_WR(VTSS_DSM_MAC_ADDR_BASE_HIGH_CFG(port), (smac[0]<<16) | (smac[1]<<8) | smac[2]);
    REG_WR(VTSS_DSM_MAC_ADDR_BASE_LOW_CFG(port),  (smac[3]<<16) | (smac[4]<<8) | smac[5]);

    /* Set HDX flowcontrol */
    REG_WRM(VTSS_DSM_MAC_CFG(port),
            VTSS_F_DSM_MAC_CFG_HDX_BACKPRESSURE(!conf->fdx),
            VTSS_M_DSM_MAC_CFG_HDX_BACKPRESSURE);

    /* Obey flowcontrol  */
    REG_WRM(VTSS_DSM_RX_PAUSE_CFG(port),
            VTSS_F_DSM_RX_PAUSE_CFG_RX_PAUSE_EN(fc_obey),
            VTSS_M_DSM_RX_PAUSE_CFG_RX_PAUSE_EN);

    /* No ingress dropping in flowontrol  */
    REG_WRM(VTSS_QFWD_SWITCH_PORT_MODE(port),
           VTSS_F_QFWD_SWITCH_PORT_MODE_INGRESS_DROP_MODE(!fc_gen),
           VTSS_M_QFWD_SWITCH_PORT_MODE_INGRESS_DROP_MODE);

    return VTSS_RC_OK;
}

/* Port disable and flush procedure */
static vtss_rc fa_port_flush(vtss_state_t *vtss_state, const vtss_port_no_t port_no, BOOL high_speed_dev)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 tgt = high_speed_dev ? VTSS_TO_HIGH_DEV(port) : VTSS_TO_DEV2G5(port);
    u32 delay = 0, value, empty = 0, do_src = 0, src_qu = 0, prio;
    u32 no_of_sources = 0;

    VTSS_D("Flush chip port:%u (%s device)", port, high_speed_dev ? "5/10/25G" : "2G5");

    if (high_speed_dev) {
        /* 1: Reset the PCS Rx clock domain  */
        REG_WRM_SET(VTSS_DEV10G_DEV_RST_CTRL(tgt),
                    VTSS_M_DEV10G_DEV_RST_CTRL_PCS_RX_RST);

        /* 2: Disable MAC frame reception */
        REG_WRM_CLR(VTSS_DEV10G_MAC_ENA_CFG(tgt),
                    VTSS_M_DEV10G_MAC_ENA_CFG_RX_ENA);
    } else {
        /* 1: Reset the PCS Rx clock domain  */
        REG_WRM_SET(VTSS_DEV1G_DEV_RST_CTRL(tgt),
                    VTSS_M_DEV1G_DEV_RST_CTRL_PCS_RX_RST);
        /* 2: Disable MAC frame reception */
        REG_WRM_CLR(VTSS_DEV1G_MAC_ENA_CFG(tgt),
                    VTSS_M_DEV1G_MAC_ENA_CFG_RX_ENA);
    }
    /* 3: Disable traffic being sent to or from switch port */
    REG_WRM_CLR(VTSS_QFWD_SWITCH_PORT_MODE(port),
                 VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA);

    /* 4: Disable dequeuing from the egress queues  */
    REG_WRM_SET(VTSS_HSCH_PORT_MODE(port),
                VTSS_M_HSCH_PORT_MODE_DEQUEUE_DIS);
    /* 5: Disable Flowcontrol */
    REG_WRM_CLR(VTSS_QSYS_PAUSE_CFG(port), VTSS_M_QSYS_PAUSE_CFG_PAUSE_ENA);

    /* 6: Disable PFC */
    /* REG_WRM_CLR(VTSS_QRES_RES_QOS_ADV_PFC_CFG(port), VTSS_M_QRES_RES_QOS_ADV_PFC_CFG_TX_PFC_ENA); */

    /* 7: Wait a worst case time 8ms (jumbo/10Mbit) *\/ */
    VTSS_MSLEEP(8);

    // Whether AFI flush fails or succeeds, continue with the port flush
    (void)fa_port_afi_flush(vtss_state, port_no);

    /* 8: Flush the queues accociated with the port */
    REG_WRM(VTSS_HSCH_FLUSH_CTRL,
            VTSS_F_HSCH_FLUSH_CTRL_FLUSH_PORT(port) |
            VTSS_F_HSCH_FLUSH_CTRL_FLUSH_DST(port) |
            VTSS_F_HSCH_FLUSH_CTRL_FLUSH_SRC(port) |
            VTSS_F_HSCH_FLUSH_CTRL_FLUSH_ENA(1),
            VTSS_M_HSCH_FLUSH_CTRL_FLUSH_PORT |
            VTSS_M_HSCH_FLUSH_CTRL_FLUSH_DST |
            VTSS_M_HSCH_FLUSH_CTRL_FLUSH_SRC |
            VTSS_M_HSCH_FLUSH_CTRL_FLUSH_ENA);

    /* 9: Enable dequeuing from the egress queues */
    REG_WRM_CLR(VTSS_HSCH_PORT_MODE(port),
                VTSS_M_HSCH_PORT_MODE_DEQUEUE_DIS);

#if defined(VTSS_FEATURE_AFI_SWC)
    no_of_sources = 1; // Default = 2
#endif
    /* 10: Wait until flushing is complete */
    do {
        for (prio = 0; prio < 8; prio++) {
            /*  Wait for source (frames to this port) and destination (frames from this port) queues are empty */
            for (do_src = 0; do_src < no_of_sources; do_src++) {
                REG_RD(VTSS_QRES_RES_STAT(2048 * (do_src ? 0 : 1) + 8 * port + prio), &value);
                if (value == 0) {
                    empty++;
                } else {
                    src_qu = do_src;
                    empty = 0;
                }
            }
        }
        VTSS_MSLEEP(1);
        delay++;
        if (delay == 2000) {
            VTSS_E("Flush timeout chip port %u. %s queue not empty",port, src_qu ? "Source)":"Dest");
            break;
        }
    } while (empty < (16 * no_of_sources));


    /* 11: Reset the  MAC clock domain */
    if (high_speed_dev) {
        REG_WRM(VTSS_DEV10G_DEV_RST_CTRL(tgt),
                VTSS_F_DEV10G_DEV_RST_CTRL_PCS_TX_RST(1) |
                VTSS_F_DEV10G_DEV_RST_CTRL_MAC_RX_RST(1) |
                VTSS_F_DEV10G_DEV_RST_CTRL_MAC_TX_RST(1),
                VTSS_M_DEV10G_DEV_RST_CTRL_PCS_TX_RST |
                VTSS_M_DEV10G_DEV_RST_CTRL_MAC_RX_RST |
                VTSS_M_DEV10G_DEV_RST_CTRL_MAC_TX_RST);

    } else {
        REG_WRM(VTSS_DEV1G_DEV_RST_CTRL(tgt),
                VTSS_F_DEV1G_DEV_RST_CTRL_SPEED_SEL(3)    |
                VTSS_F_DEV1G_DEV_RST_CTRL_USX_PCS_TX_RST(1) |
                VTSS_F_DEV1G_DEV_RST_CTRL_USX_PCS_RX_RST(1) |
                VTSS_F_DEV1G_DEV_RST_CTRL_PCS_TX_RST(1) |
                VTSS_F_DEV1G_DEV_RST_CTRL_PCS_RX_RST(1) |
                VTSS_F_DEV1G_DEV_RST_CTRL_MAC_TX_RST(1) |
                VTSS_F_DEV1G_DEV_RST_CTRL_MAC_RX_RST(1),
                VTSS_M_DEV1G_DEV_RST_CTRL_SPEED_SEL |
                VTSS_M_DEV1G_DEV_RST_CTRL_USX_PCS_TX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_USX_PCS_RX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_PCS_TX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_PCS_RX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_MAC_TX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_MAC_RX_RST);
    }
    /* 12: Clear flushing */
    REG_WRM(VTSS_HSCH_FLUSH_CTRL,
            VTSS_F_HSCH_FLUSH_CTRL_FLUSH_PORT(port) |
            VTSS_F_HSCH_FLUSH_CTRL_FLUSH_ENA(0),
            VTSS_M_HSCH_FLUSH_CTRL_FLUSH_PORT |
            VTSS_M_HSCH_FLUSH_CTRL_FLUSH_ENA);

    if (high_speed_dev) {
        /* 13: Disable 10G PCS */
        REG_WRM_CLR(VTSS_PCS_10GBASE_R_PCS_CFG(VTSS_TO_PCS_TGT(port)),
                    VTSS_M_PCS_10GBASE_R_PCS_CFG_PCS_ENA);

        if (VTSS_PORT_IS_25G(port)) {
            /* Disable 25G PCS */
            REG_WRM_CLR(VTSS_DEV10G_PCS25G_CFG(tgt),
                        VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
        }
    }

    /* The port is now flushed and disabled  */

    return VTSS_RC_OK;
}

/* Configuration of the 2G5 device (dev1G architecture) */
static vtss_rc fa_port_conf_2g5_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t       *conf  = &vtss_state->port.conf[port_no];
    u32                    port   = VTSS_CHIP_PORT(port_no);
    u32                    tx_gap, hdx_gap_1 = 0, hdx_gap_2 = 0;
    vtss_port_speed_t      speed = conf->speed;
    u32                    value;
    BOOL                   fdx = conf->fdx, disable = conf->power_down;
    BOOL                   sgmii = FALSE, pcs_100fx = FALSE, pcs_usx = FALSE;
    u32                    tgt = VTSS_TO_DEV2G5(port), clk_spd = 0;
    vtss_serdes_mode_t     serdes_mode = VTSS_SERDES_MODE_SGMII;

    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_SERDES:
        serdes_mode = (speed == VTSS_SPEED_2500M ? VTSS_SERDES_MODE_2G5 : VTSS_SERDES_MODE_1000BaseX);
        break;
    case VTSS_PORT_INTERFACE_SGMII:
        serdes_mode = VTSS_SERDES_MODE_SGMII;
        sgmii = TRUE;
        break;
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        serdes_mode = VTSS_SERDES_MODE_1000BaseX;
        sgmii = TRUE;
        break;
    case VTSS_PORT_INTERFACE_100FX:
        serdes_mode = VTSS_SERDES_MODE_100FX;
        pcs_100fx = TRUE;
        break;
    case VTSS_PORT_INTERFACE_QSGMII:    // Normal QSGMII
        serdes_mode = VTSS_SERDES_MODE_QSGMII;
        break;
    case VTSS_PORT_INTERFACE_USGMII:    // 8x1G, X-mode (ala 2 x QSGMII) 10G Serdes
        serdes_mode = VTSS_SERDES_MODE_USGMII;
        sgmii = TRUE;
        break;
    case VTSS_PORT_INTERFACE_QXGMII:    // 4x2G5 R-mode, 10G Serdes
        serdes_mode = VTSS_SERDES_MODE_USXGMII; // TBD-BJO
        pcs_usx = TRUE;
        break;
    case VTSS_PORT_INTERFACE_DXGMII_5G: // 2x2G5 F-mode, 5G Serdes
        serdes_mode = VTSS_SERDES_MODE_USXGMII; // TBD-BJO
        pcs_usx = TRUE;
        break;
    default: {}
    }

    switch (speed) {
    case VTSS_SPEED_10M:  clk_spd = 0; break;
    case VTSS_SPEED_100M: clk_spd = 1; break;
    case VTSS_SPEED_1G:   clk_spd = 2; break;
    case VTSS_SPEED_2500M:
        clk_spd = conf->if_type == VTSS_PORT_INTERFACE_USGMII ? 6 : 2;
        break;
    default:{ VTSS_E("Speed not supported"); }
    }

    if (disable) {
        /* The port is not powered down in CE builds, as frames still needs to be forwarded to an up-mep */
        /* Instead the PCS is disabled, which forces link down and discards frame forwarding */
        REG_WR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_ANEG_CFG_ANEG_ENA(1) |
               VTSS_F_DEV1G_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1));

         /* Update vtss_state database accordingly */
        fa_port_clause_37_control_get(vtss_state,port_no,&vtss_state->port.clause_37[port_no]);

        REG_WR(VTSS_DEV1G_PCS1G_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_CFG_PCS_ENA(0));

//  TBD  VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, VTSS_SERDES_MODE_IDLE));
        return VTSS_RC_OK;
    }

    /* Enable the Serdes if disabled */
    if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_DISABLE) {
        VTSS_RC(fa_serdes_set(vtss_state, port_no, serdes_mode));
    }

   /* Port disable and flush procedure: */
    VTSS_RC(fa_port_flush(vtss_state, port_no, FALSE));

    /* Configure the Serdes Macro to 'serdes_mode' */
    if (serdes_mode != vtss_state->port.serdes_mode[port_no]) {
        VTSS_RC(fa_serdes_set(vtss_state, port_no, serdes_mode));
    }

    /* Bugzilla 4388: disabling frame aging when in HDX */
    REG_WRM_CTL(VTSS_HSCH_PORT_MODE(port), !fdx, VTSS_M_HSCH_PORT_MODE_AGE_DIS);

    /* GIG/FDX mode */
    REG_WRM(VTSS_DEV1G_MAC_MODE_CFG(tgt),
            VTSS_F_DEV1G_MAC_MODE_CFG_GIGA_MODE_ENA(speed == VTSS_SPEED_1G || speed == VTSS_SPEED_2500M) |
            VTSS_F_DEV1G_MAC_MODE_CFG_FDX_ENA(fdx),
            VTSS_M_DEV1G_MAC_MODE_CFG_GIGA_MODE_ENA |
            VTSS_M_DEV1G_MAC_MODE_CFG_FDX_ENA);

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
        tx_gap = (speed == VTSS_SPEED_1G) ? 4 : fdx ? 6 : 5;
    } else {
        tx_gap = conf->frame_gaps.fdx_gap;
    }

    /* Set MAC IFG Gaps */
    REG_WR(VTSS_DEV1G_MAC_IFG_CFG(tgt),
            VTSS_F_DEV1G_MAC_IFG_CFG_TX_IFG(tx_gap) |
            VTSS_F_DEV1G_MAC_IFG_CFG_RX_IFG1(hdx_gap_1) |
            VTSS_F_DEV1G_MAC_IFG_CFG_RX_IFG2(hdx_gap_2));

    /* Set MAC HDX late collision */
    REG_WRM(VTSS_DEV1G_MAC_HDX_CFG(tgt),
            VTSS_F_DEV1G_MAC_HDX_CFG_LATE_COL_POS(67) |
            VTSS_F_DEV1G_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA(conf->exc_col_cont),
            VTSS_M_DEV1G_MAC_HDX_CFG_LATE_COL_POS |
            VTSS_M_DEV1G_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA);

    /* PCS settings for 100fx/USX/SGMII/SERDES */
    if (pcs_100fx) {
        /* Enable 100FX */
        REG_WRM(VTSS_DEV1G_PCS_FX100_CFG(tgt),
                VTSS_F_DEV1G_PCS_FX100_CFG_PCS_ENA(!disable) |
                VTSS_F_DEV1G_PCS_FX100_CFG_SD_SEL(!conf->sd_internal) |
                VTSS_F_DEV1G_PCS_FX100_CFG_SD_POL(conf->sd_active_high) |
                VTSS_F_DEV1G_PCS_FX100_CFG_SD_ENA(conf->sd_enable),
                VTSS_M_DEV1G_PCS_FX100_CFG_PCS_ENA |
                VTSS_M_DEV1G_PCS_FX100_CFG_SD_SEL |
                VTSS_M_DEV1G_PCS_FX100_CFG_SD_POL |
                VTSS_M_DEV1G_PCS_FX100_CFG_SD_ENA);
    } else if (pcs_usx) {
        /* Disable 100FX */
        REG_WRM_CLR(VTSS_DEV1G_PCS_FX100_CFG(tgt),
                     VTSS_M_DEV1G_PCS_FX100_CFG_PCS_ENA);
        /* Disable SGMII/Serdes PCS */
        REG_WRM_CLR(VTSS_DEV1G_PCS1G_CFG(tgt),
                    VTSS_M_DEV1G_PCS1G_CFG_PCS_ENA);

        /* Signal Detect configuration */
        REG_WRM(VTSS_DEV1G_USXGMII_PCS_SD_CFG(tgt),
               VTSS_F_DEV1G_USXGMII_PCS_SD_CFG_SD_POL(conf->sd_active_high) |
               VTSS_F_DEV1G_USXGMII_PCS_SD_CFG_SD_ENA(conf->sd_enable),
               VTSS_M_DEV1G_USXGMII_PCS_SD_CFG_SD_POL |
               VTSS_M_DEV1G_USXGMII_PCS_SD_CFG_SD_ENA);

        /* Enable USXGMII aneg.  We still use the Aneg results from the Phy though. */
        REG_WRM(VTSS_DEV1G_USXGMII_ANEG_CFG(tgt),
                VTSS_F_DEV1G_USXGMII_ANEG_CFG_ADV_ABILITY(0x0001) |
                VTSS_F_DEV1G_USXGMII_ANEG_CFG_ANEG_ENA(1) |
                VTSS_F_DEV1G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1) |
                VTSS_F_DEV1G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA(1),
                VTSS_M_DEV1G_USXGMII_ANEG_CFG_ADV_ABILITY |
                VTSS_M_DEV1G_USXGMII_ANEG_CFG_ANEG_ENA |
                VTSS_M_DEV1G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT |
                VTSS_M_DEV1G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA);
    } else {
        /* 1000BaseX PCS in SGMII or Serdes mode */

        /* Disable 100FX */
        REG_WRM_CLR(VTSS_DEV1G_PCS_FX100_CFG(tgt),
                     VTSS_M_DEV1G_PCS_FX100_CFG_PCS_ENA);

        /* Choose SGMII or Serdes PCS mode */
        REG_WR(VTSS_DEV1G_PCS1G_MODE_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_MODE_CFG_SGMII_MODE_ENA(sgmii));

        if (sgmii) {
            /* Set whole register */
            REG_WR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt),
                   VTSS_F_DEV1G_PCS1G_ANEG_CFG_SW_RESOLVE_ENA(1));
        } else {
            /* Clear specific bit only */
            REG_WRM_CLR(VTSS_DEV1G_PCS1G_ANEG_CFG(tgt),
                         VTSS_M_DEV1G_PCS1G_ANEG_CFG_SW_RESOLVE_ENA);
        }

        /* Signal Detect configuration */
        REG_WR(VTSS_DEV1G_PCS1G_SD_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_SD_CFG_SD_POL(conf->sd_active_high) |
               VTSS_F_DEV1G_PCS1G_SD_CFG_SD_ENA(conf->sd_enable) |
               VTSS_F_DEV1G_PCS1G_SD_CFG_SD_SEL(!conf->sd_internal));

        /* Enable/disable PCS */
        REG_WR(VTSS_DEV1G_PCS1G_CFG(tgt),
               VTSS_F_DEV1G_PCS1G_CFG_PCS_ENA(!disable));

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
    fa_port_clause_37_control_get(vtss_state,port_no, &vtss_state->port.clause_37[port_no]);

    REG_WRM_CTL(VTSS_DEV1G_PCS1G_LB_CFG(tgt),
                conf->loop == VTSS_PORT_LOOP_PCS_HOST,
                VTSS_M_DEV1G_PCS1G_LB_CFG_TBI_HOST_LB_ENA);

    /* Set Max Length */
    REG_WRM(VTSS_DEV1G_MAC_MAXLEN_CFG(tgt),
            VTSS_F_DEV1G_MAC_MAXLEN_CFG_MAX_LEN(conf->max_frame_length),
            VTSS_M_DEV1G_MAC_MAXLEN_CFG_MAX_LEN);

    /* Configure frame length check (from ethertype / length field) */
    REG_WRM(VTSS_DEV1G_MAC_ADV_CHK_CFG(tgt),
            VTSS_F_DEV1G_MAC_ADV_CHK_CFG_LEN_DROP_ENA(conf->frame_length_chk),
            VTSS_M_DEV1G_MAC_ADV_CHK_CFG_LEN_DROP_ENA);

    /* Must be 1 for 10/100 */
    REG_WRM(VTSS_DSM_DEV_TX_STOP_WM_CFG(port),
            VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM((speed == VTSS_SPEED_10M || speed == VTSS_SPEED_100M) ? 1 : 0),
            VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM);

    if (!disable) {
        /* Configure flow control */
        if (fa_port_fc_setup(vtss_state, port, conf) != VTSS_RC_OK) {
            VTSS_E("Could not configure FC port: %u", port);
        }

        /* Update policer flow control configuration */
        VTSS_RC(vtss_fa_port_policer_fc_set(vtss_state, port_no));

        /* Enable MAC module */
        REG_WR(VTSS_DEV1G_MAC_ENA_CFG(tgt),
               VTSS_M_DEV1G_MAC_ENA_CFG_RX_ENA |
               VTSS_M_DEV1G_MAC_ENA_CFG_TX_ENA);

        /* Take MAC and  PCS (SGMII/Serdes or USX) clock out of reset */
        REG_WRM(VTSS_DEV1G_DEV_RST_CTRL(tgt),
                VTSS_F_DEV1G_DEV_RST_CTRL_SPEED_SEL(clk_spd)    |
                VTSS_F_DEV1G_DEV_RST_CTRL_USX_PCS_TX_RST(!pcs_usx) |
                VTSS_F_DEV1G_DEV_RST_CTRL_USX_PCS_RX_RST(!pcs_usx) |
                VTSS_F_DEV1G_DEV_RST_CTRL_PCS_TX_RST(pcs_usx) |
                VTSS_F_DEV1G_DEV_RST_CTRL_PCS_RX_RST(pcs_usx) |
                VTSS_F_DEV1G_DEV_RST_CTRL_MAC_TX_RST(0) |
                VTSS_F_DEV1G_DEV_RST_CTRL_MAC_RX_RST(0),
                VTSS_M_DEV1G_DEV_RST_CTRL_SPEED_SEL |
                VTSS_M_DEV1G_DEV_RST_CTRL_USX_PCS_TX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_USX_PCS_RX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_PCS_TX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_PCS_RX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_MAC_TX_RST |
                VTSS_M_DEV1G_DEV_RST_CTRL_MAC_RX_RST);

        /* Core: Set the fwd_urgency and and enable port for frame transfer */
        REG_WRM(VTSS_QFWD_SWITCH_PORT_MODE(port),
                VTSS_F_QFWD_SWITCH_PORT_MODE_PORT_ENA(1) |
                VTSS_F_QFWD_SWITCH_PORT_MODE_FWD_URGENCY(port_fwd_urg(vtss_state, conf->speed)),
                VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA |
                VTSS_M_QFWD_SWITCH_PORT_MODE_FWD_URGENCY);

        /* Enable flowcontrol - must be done after the port is enabled */
        if (conf->flow_control.generate) {
            REG_WRM_SET(VTSS_QSYS_PAUSE_CFG(port), VTSS_M_QSYS_PAUSE_CFG_PAUSE_ENA);
        }
    }
    VTSS_D("Chip port: %u (1G) is configured", port);
    return VTSS_RC_OK;
}

/* Configuration of the 5G, 10G and 25G devices (dev10G architecture) */
static vtss_rc fa_port_conf_high_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t       *conf = &vtss_state->port.conf[port_no];
    u32                    port = VTSS_CHIP_PORT(port_no);
    u32                    tgt = VTSS_TO_HIGH_DEV(port);
    u32                    pcs = VTSS_TO_PCS_TGT(port);
    u32                    clk_spd = 0, muxed_ports = 0;
    vtss_serdes_mode_t     serdes_mode = VTSS_SERDES_MODE_SFI;
    BOOL                   pcs_usx = FALSE;

    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_SFI:
        serdes_mode = VTSS_SERDES_MODE_SFI;;
        break;
    case VTSS_PORT_INTERFACE_SXGMII:     // 1x10G device. 10M-10G.
        serdes_mode = VTSS_SERDES_MODE_USXGMII;
        pcs_usx = TRUE;
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: // 2x5G devices. Mode 'U', 10M-5G.
        serdes_mode = VTSS_SERDES_MODE_USXGMII;
        muxed_ports = 1; // Dual
        pcs_usx = TRUE;
        break;
    default: {}
    }

    switch (conf->speed) {
    case VTSS_SPEED_25G:
    case VTSS_SPEED_10G:   clk_spd = 0; break;
    case VTSS_SPEED_5G:    clk_spd = 1; break;
    case VTSS_SPEED_2500M: clk_spd = 2; break;
    case VTSS_SPEED_1G:    clk_spd = 3; break;
    case VTSS_SPEED_100M:  clk_spd = 4; break;
    case VTSS_SPEED_10M:   clk_spd = 5; break;
    default:{}
    }

    if (conf->power_down) {
        /* The port is not powered down in CE builds, as frames still needs to be forwarded to an up-mep */
        /* Instead the Serdes is configured to send out idles which simulates port down state */
// TBD-BJO        VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, VTSS_SERDES_MODE_IDLE));
        return VTSS_RC_OK;
    }


    /* Enable the Serdes if disabled */
    if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_DISABLE) {
        VTSS_RC(fa_serdes_set(vtss_state, port_no, serdes_mode));
    }

    /* Port disable and flush procedure: */
    VTSS_RC(fa_port_flush(vtss_state, port_no, TRUE));

   /* Re-configure Serdes if needed */
    if (serdes_mode != vtss_state->port.serdes_mode[port_no]) {
        VTSS_RC(fa_serdes_set(vtss_state, port_no, serdes_mode));
    }

    if (conf->speed == VTSS_SPEED_25G) {
        /* Disable 10G PCS */
        REG_WRM_CLR(VTSS_PCS_10GBASE_R_PCS_CFG(pcs),
                    VTSS_M_PCS_10GBASE_R_PCS_CFG_PCS_ENA);

        /* Handle Signal Detect in PCS */
        REG_WR(VTSS_DEV10G_PCS25G_SD_CFG(tgt),
               VTSS_F_DEV10G_PCS25G_SD_CFG_SD_SEL(!conf->sd_internal) |
               VTSS_F_DEV10G_PCS25G_SD_CFG_SD_POL(conf->sd_active_high) |
               VTSS_F_DEV10G_PCS25G_SD_CFG_SD_ENA(conf->sd_enable));

        /* Enable 25G PCS */
        REG_WRM_SET(VTSS_DEV10G_PCS25G_CFG(tgt),
                    VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
    } else {
        if (VTSS_PORT_IS_25G(port)) {/* Disable 25G PCS */
            REG_WRM_CLR(VTSS_DEV10G_PCS25G_CFG(tgt),
                        VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA);
        }
        if (pcs_usx) {
            /* Handle SD. */
            REG_WRM(VTSS_DEV10G_USXGMII_PCS_SD_CFG(tgt),
                    VTSS_F_DEV10G_USXGMII_PCS_SD_CFG_SD_POL(conf->sd_active_high) |
                    VTSS_F_DEV10G_USXGMII_PCS_SD_CFG_SD_ENA(conf->sd_enable),
                    VTSS_M_DEV10G_USXGMII_PCS_SD_CFG_SD_POL |
                    VTSS_M_DEV10G_USXGMII_PCS_SD_CFG_SD_ENA);

            /* Enable USXGMII aneg. We still use the Aneg results from the Phy though. */
            REG_WRM(VTSS_DEV10G_USXGMII_ANEG_CFG(tgt),
                    VTSS_F_DEV10G_USXGMII_ANEG_CFG_ADV_ABILITY(0x0001) |
                    VTSS_F_DEV10G_USXGMII_ANEG_CFG_ANEG_ENA(1) |
                    VTSS_F_DEV10G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT(1) |
                    VTSS_F_DEV10G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA(1),
                    VTSS_M_DEV10G_USXGMII_ANEG_CFG_ADV_ABILITY |
                    VTSS_M_DEV10G_USXGMII_ANEG_CFG_ANEG_ENA |
                    VTSS_M_DEV10G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT |
                    VTSS_M_DEV10G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA);
        } else {
            /* Handle Signal Detect in PCS */
            REG_WR(VTSS_PCS_10GBASE_R_PCS_SD_CFG(pcs),
                   VTSS_F_PCS_10GBASE_R_PCS_SD_CFG_SD_POL(conf->sd_active_high) |
                   VTSS_F_PCS_10GBASE_R_PCS_SD_CFG_SD_SEL(!conf->sd_internal) |
                   VTSS_F_PCS_10GBASE_R_PCS_SD_CFG_SD_ENA(conf->sd_enable));

            /* Enable 10G PCS */
            REG_WRM_SET(VTSS_PCS_10GBASE_R_PCS_CFG(pcs),
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

    if (!conf->power_down) {
        /* Configure flow control */
        if (fa_port_fc_setup(vtss_state, port, conf) != VTSS_RC_OK) {
            VTSS_E("Could not configure FC port: %u", port);
        }

        /* Update policer flow control configuration */
        VTSS_RC(vtss_fa_port_policer_fc_set(vtss_state, port_no));

        /* Enable MAC module */
        REG_WR(VTSS_DEV10G_MAC_ENA_CFG(tgt),
               VTSS_M_DEV10G_MAC_ENA_CFG_RX_ENA |
               VTSS_M_DEV10G_MAC_ENA_CFG_TX_ENA);

        /* Take MAC and PCS out of reset */
        REG_WRM(VTSS_DEV10G_DEV_RST_CTRL(tgt),
                VTSS_F_DEV10G_DEV_RST_CTRL_MUXED_USXGMII_NETWORK_PORTS(muxed_ports) |
                VTSS_F_DEV10G_DEV_RST_CTRL_PCS_RX_RST(0) |
                VTSS_F_DEV10G_DEV_RST_CTRL_PCS_TX_RST(0) |
                VTSS_F_DEV10G_DEV_RST_CTRL_MAC_RX_RST(0) |
                VTSS_F_DEV10G_DEV_RST_CTRL_MAC_TX_RST(0) |
                VTSS_F_DEV10G_DEV_RST_CTRL_SPEED_SEL(clk_spd),
                VTSS_M_DEV10G_DEV_RST_CTRL_MUXED_USXGMII_NETWORK_PORTS |
                VTSS_M_DEV10G_DEV_RST_CTRL_PCS_RX_RST |
                VTSS_M_DEV10G_DEV_RST_CTRL_PCS_TX_RST |
                VTSS_M_DEV10G_DEV_RST_CTRL_MAC_RX_RST |
                VTSS_M_DEV10G_DEV_RST_CTRL_MAC_TX_RST |
                VTSS_M_DEV10G_DEV_RST_CTRL_SPEED_SEL);

        REG_WRM(VTSS_QFWD_SWITCH_PORT_MODE(port),
                VTSS_F_QFWD_SWITCH_PORT_MODE_PORT_ENA(1) |
                VTSS_F_QFWD_SWITCH_PORT_MODE_FWD_URGENCY(port_fwd_urg(vtss_state, conf->speed)),
                VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA |
                VTSS_M_QFWD_SWITCH_PORT_MODE_FWD_URGENCY);

        /* Enable flowcontrol - must be done after the port is enabled */
        if (conf->flow_control.generate) {
            REG_WRM_SET(VTSS_QSYS_PAUSE_CFG(port), VTSS_M_QSYS_PAUSE_CFG_PAUSE_ENA);
        }
    } else {
        /* Disable the power hungry serdes */
// TBD-BJO     VTSS_RC(jr2_serdes_cfg(vtss_state, port_no, VTSS_SERDES_MODE_DISABLE));
    }

    VTSS_D("chip port: %u (10G),is configured", port);

    return VTSS_RC_OK;

}

static vtss_rc fa_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    u32              port = VTSS_CHIP_PORT(port_no);
    BOOL             use_primary_dev = fa_is_high_speed_device(vtss_state, port_no);

    if (!fa_vrfy_spd_iface(vtss_state, port_no, conf->if_type, conf->speed, conf->fdx)) {
        return VTSS_RC_ERROR;
    }

    /* All high speed (>2G5) ports have a shadow 2G5 device. */
    /* Only one of them can be active and attached to the switch core at a time. */
    /* Every time the devices changes a port flush (shut down) must be performed on the DEV that is not active. */
    if (fa_change_device(vtss_state, port_no)) {

        VTSS_D("port_no:%d (chip port:%d) shutdown the %s device",port_no, port, use_primary_dev ? "shadow" : "primary");

        /* Shutdown the not-in-use device */
        VTSS_RC(fa_port_flush(vtss_state, port_no, !use_primary_dev));

        /* Enable/disable shadow device */
        u32 bt_indx = VTSS_BIT(VTSS_PORT_DEV_INDX(port));
        if (VTSS_PORT_IS_5G(port)) {
            REG_WRM(VTSS_PORT_CONF_DEV5G_MODES, use_primary_dev ? 0 : bt_indx, bt_indx);
        } else if (VTSS_PORT_IS_10G(port)) {
            REG_WRM(VTSS_PORT_CONF_DEV10G_MODES, use_primary_dev ? 0 : bt_indx, bt_indx);
        } else if (VTSS_PORT_IS_25G(port)) {
            REG_WRM(VTSS_PORT_CONF_DEV25G_MODES, use_primary_dev ? 0 : bt_indx, bt_indx);
        }

        if (use_primary_dev) {
            REG_WRM(VTSS_DSM_DEV_TX_STOP_WM_CFG(port),
                    VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM(0) |
                    VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA(0),
                    VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM |
                    VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA);
        } else {
            REG_WRM(VTSS_DSM_DEV_TX_STOP_WM_CFG(port),
                    VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA(1),
                    VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA);
        }

    }

    VTSS_D("port_no:%d (port:%d, dev%s) if:%s, spd:%s/%s, shutdown:%d",
           port_no, port, VTSS_PORT_IS_25G(port) ? "25G" : VTSS_PORT_IS_10G(port) ? "10G": \
           VTSS_PORT_IS_5G(port) ? "5G" : "2G5", vtss_port_if_txt(conf->if_type),
           vtss_port_spd_txt(conf->speed), conf->fdx ? "FDX" : "HDX", conf->power_down);

    /* Configure USXGMII/USGMII/QSGMII port muxing (if needed) */
    VTSS_RC(fa_port_mux_set(vtss_state, port_no));

    if (use_primary_dev) {
        VTSS_RC(fa_port_conf_high_set(vtss_state, port_no));
    } else {
        VTSS_RC(fa_port_conf_2g5_set(vtss_state, port_no));
    }

    vtss_state->port.current_speed[port_no] = vtss_state->port.conf[port_no].speed;
    vtss_state->port.current_if_type[port_no] = vtss_state->port.conf[port_no].if_type;

    return VTSS_RC_OK;
}



/* Get status of the SFI and 100FX ports. */
/* Note: Status for SERDES is handled through clause_37_status_get. Status for SGMII is retrieved from the Phy */
static vtss_rc fa_port_status_get(vtss_state_t *vtss_state,
                                  const vtss_port_no_t  port_no,
                                  vtss_port_status_t    *const status)
{
    u32              value;
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    u32              tgt = vtss_fa_dev_tgt(vtss_state, port_no);

    if (conf->power_down) {
        /* Disabled port is considered down */
        return VTSS_RC_OK;
    }

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
            REG_WRM_SET(VTSS_DEV1G_PCS1G_STICKY(tgt),
                        VTSS_M_DEV1G_PCS1G_STICKY_LINK_DOWN_STICKY);
        }
        status->speed = VTSS_SPEED_2500M;
        break;
    case VTSS_PORT_INTERFACE_SFI:
        /* MAC10G Tx Monitor Sticky bit Register */
        REG_RD(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), &value);
        status->link_down = REG_BF(DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY, value);
        if (status->link_down) {
            /* The link is or has been down. Clear the sticky bit */
            REG_WR(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), 0xFFFFFFFF);
            REG_RD(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), &value);
        }
        status->link = VTSS_BOOL(value == VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY);
        status->speed = conf->speed;
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        status->link = 0;
        status->link_down = 0;
        break;
    default:
        VTSS_E("Status not supported for port: %u", port_no);
        return VTSS_RC_ERROR;
    }
    status->fdx = conf->fdx;
    return VTSS_RC_OK;
}


#define REG_CNT_1G(name, i, cnt, clr)            \
{                                                \
    u32 value;                                   \
    REG_RD(VTSS_ASM_##name##_CNT(i), &value);    \
    vtss_cmn_counter_32_update(value, cnt, clr); \
}

#define REG_CNT_10G(name, i, cnt, clr)           \
{                                                \
    u32 value;                                   \
    REG_RD(VTSS_DEV10G_##name##_CNT(i), &value); \
    vtss_cmn_counter_32_update(value, cnt, clr); \
}

#define REG_CNT_ANA_AC(name, cnt, clr)               \
{                                                    \
    u32 value;                                       \
    REG_RD(VTSS_ANA_AC_STAT_CNT_CFG_##name, &value); \
    vtss_cmn_counter_32_update(value, cnt, clr);     \
}

static vtss_rc vtss_fa_qsys_counter_update(vtss_state_t *vtss_state,
                                            u32 *addr, vtss_chip_counter_t *counter, BOOL clear)
{
    u32 value;

    REG_RD(VTSS_XQS_CNT(*addr), &value);
    *addr = (*addr + 1); /* Next counter address */
    vtss_cmn_counter_32_update(value, counter, clear);

    return VTSS_RC_OK;
}

/* Index of ANA_AC port counters */
#define REG_CNT_ANA_AC_PORT_FILTER        0
#define REG_CNT_ANA_AC_PORT_POLICER_DROPS 1

/* Index of ANA_AC queue counters */
#define REG_CNT_ANA_AC_QUEUE_PRIO 0

static vtss_rc fa_port_counters_chip(vtss_state_t                  *vtss_state,
                                      vtss_port_no_t               port_no,
                                      vtss_port_fa_counters_t      *c,
                                      vtss_port_counters_t *const  counters,
                                      BOOL                         clr)
{
    u32                                i, addr, port;
    vtss_port_counter_t                rx_errors;
    vtss_port_rmon_counters_t          *rmon;
    vtss_port_if_group_counters_t      *if_group;
    vtss_port_ethernet_like_counters_t *elike;
    vtss_port_proprietary_counters_t   *prop;

    if (port_no >= vtss_state->port_count) {
        /* CPU/virtual port */
        port = (VTSS_CHIP_PORT_CPU + port_no - vtss_state->port_count);
    } else if (!fa_is_high_speed_device(vtss_state, port_no)) {
        /* ASM counters */
        port = VTSS_CHIP_PORT(port_no);
        i = port;
        REG_CNT_1G(RX_IN_BYTES, i, &c->rx_in_bytes, clr);
        REG_CNT_1G(RX_SYMBOL_ERR, i, &c->rx_symbol_err, clr);
        REG_CNT_1G(RX_PAUSE, i, &c->rx_pause, clr);
        REG_CNT_1G(RX_UNSUP_OPCODE, i, &c->rx_unsup_opcode, clr);
        REG_CNT_1G(RX_OK_BYTES, i, &c->rx_ok_bytes, clr);
        REG_CNT_1G(RX_BAD_BYTES, i, &c->rx_bad_bytes, clr);
        REG_CNT_1G(RX_UC, i, &c->rx_unicast, clr);
        REG_CNT_1G(RX_MC, i, &c->rx_multicast, clr);
        REG_CNT_1G(RX_BC, i, &c->rx_broadcast, clr);
        REG_CNT_1G(RX_CRC_ERR, i, &c->rx_crc_err, clr);
        REG_CNT_1G(RX_UNDERSIZE, i, &c->rx_undersize, clr);
        REG_CNT_1G(RX_FRAGMENTS, i, &c->rx_fragments, clr);
        REG_CNT_1G(RX_IN_RANGE_LEN_ERR, i, &c->rx_in_range_len_err, clr);
        REG_CNT_1G(RX_OUT_OF_RANGE_LEN_ERR, i, &c->rx_out_of_range_len_err, clr);
        REG_CNT_1G(RX_OVERSIZE, i, &c->rx_oversize, clr);
        REG_CNT_1G(RX_JABBERS, i, &c->rx_jabbers, clr);
        REG_CNT_1G(RX_SIZE64, i, &c->rx_size64, clr);
        REG_CNT_1G(RX_SIZE65TO127, i, &c->rx_size65_127, clr);
        REG_CNT_1G(RX_SIZE128TO255, i, &c->rx_size128_255, clr);
        REG_CNT_1G(RX_SIZE256TO511, i, &c->rx_size256_511, clr);
        REG_CNT_1G(RX_SIZE512TO1023, i, &c->rx_size512_1023, clr);
        REG_CNT_1G(RX_SIZE1024TO1518, i, &c->rx_size1024_1518, clr);
        REG_CNT_1G(RX_SIZE1519TOMAX, i, &c->rx_size1519_max, clr);

        REG_CNT_1G(TX_OUT_BYTES, i, &c->tx_out_bytes, clr);
        REG_CNT_1G(TX_PAUSE, i, &c->tx_pause, clr);
        REG_CNT_1G(TX_OK_BYTES, i, &c->tx_ok_bytes, clr);
        REG_CNT_1G(TX_UC, i, &c->tx_unicast, clr);
        REG_CNT_1G(TX_MC, i, &c->tx_multicast, clr);
        REG_CNT_1G(TX_BC, i, &c->tx_broadcast, clr);
        REG_CNT_1G(TX_SIZE64, i, &c->tx_size64, clr);
        REG_CNT_1G(TX_SIZE65TO127, i, &c->tx_size65_127, clr);
        REG_CNT_1G(TX_SIZE128TO255, i, &c->tx_size128_255, clr);
        REG_CNT_1G(TX_SIZE256TO511, i, &c->tx_size256_511, clr);
        REG_CNT_1G(TX_SIZE512TO1023, i, &c->tx_size512_1023, clr);
        REG_CNT_1G(TX_SIZE1024TO1518, i, &c->tx_size1024_1518, clr);
        REG_CNT_1G(TX_SIZE1519TOMAX, i, &c->tx_size1519_max, clr);
        REG_CNT_1G(TX_MULTI_COLL, i, &c->tx_multi_coll, clr);
        REG_CNT_1G(TX_LATE_COLL, i, &c->tx_late_coll, clr);
        REG_CNT_1G(TX_XCOLL, i, &c->tx_xcoll, clr);
        REG_CNT_1G(TX_DEFER, i, &c->tx_defer, clr);
        REG_CNT_1G(TX_XDEFER, i, &c->tx_xdefer, clr);
        REG_CNT_1G(TX_BACKOFF1, i, &c->tx_backoff1, clr);
    } else {
        /* DEV5G/DEV10G/DEV25G counters */
        port = VTSS_CHIP_PORT(port_no);
        i = VTSS_TO_HIGH_DEV(port);
        REG_CNT_10G(RX_IN_BYTES, i, &c->rx_in_bytes, clr);
        REG_CNT_10G(RX_SYMBOL_ERR, i, &c->rx_symbol_err, clr);
        REG_CNT_10G(RX_PAUSE, i, &c->rx_pause, clr);
        REG_CNT_10G(RX_UNSUP_OPCODE, i, &c->rx_unsup_opcode, clr);
        REG_CNT_10G(RX_OK_BYTES, i, &c->rx_ok_bytes, clr);
        REG_CNT_10G(RX_BAD_BYTES, i, &c->rx_bad_bytes, clr);
        REG_CNT_10G(RX_UC, i, &c->rx_unicast, clr);
        REG_CNT_10G(RX_MC, i, &c->rx_multicast, clr);
        REG_CNT_10G(RX_BC, i, &c->rx_broadcast, clr);
        REG_CNT_10G(RX_CRC_ERR, i, &c->rx_crc_err, clr);
        REG_CNT_10G(RX_UNDERSIZE, i, &c->rx_undersize, clr);
        REG_CNT_10G(RX_FRAGMENTS, i, &c->rx_fragments, clr);
        REG_CNT_10G(RX_IN_RANGE_LEN_ERR, i, &c->rx_in_range_len_err, clr);
        REG_CNT_10G(RX_OUT_OF_RANGE_LEN_ERR, i, &c->rx_out_of_range_len_err, clr);
        REG_CNT_10G(RX_OVERSIZE, i, &c->rx_oversize, clr);
        REG_CNT_10G(RX_JABBERS, i, &c->rx_jabbers, clr);
        REG_CNT_10G(RX_SIZE64, i, &c->rx_size64, clr);
        REG_CNT_10G(RX_SIZE65TO127, i, &c->rx_size65_127, clr);
        REG_CNT_10G(RX_SIZE128TO255, i, &c->rx_size128_255, clr);
        REG_CNT_10G(RX_SIZE256TO511, i, &c->rx_size256_511, clr);
        REG_CNT_10G(RX_SIZE512TO1023, i, &c->rx_size512_1023, clr);
        REG_CNT_10G(RX_SIZE1024TO1518, i, &c->rx_size1024_1518, clr);
        REG_CNT_10G(RX_SIZE1519TOMAX, i, &c->rx_size1519_max, clr);

        REG_CNT_10G(TX_OUT_BYTES, i, &c->tx_out_bytes, clr);
        REG_CNT_10G(TX_PAUSE, i, &c->tx_pause, clr);
        REG_CNT_10G(TX_OK_BYTES, i, &c->tx_ok_bytes, clr);
        REG_CNT_10G(TX_UC, i, &c->tx_unicast, clr);
        REG_CNT_10G(TX_MC, i, &c->tx_multicast, clr);
        REG_CNT_10G(TX_BC, i, &c->tx_broadcast, clr);
        REG_CNT_10G(TX_SIZE64, i, &c->tx_size64, clr);
        REG_CNT_10G(TX_SIZE65TO127, i, &c->tx_size65_127, clr);
        REG_CNT_10G(TX_SIZE128TO255, i, &c->tx_size128_255, clr);
        REG_CNT_10G(TX_SIZE256TO511, i, &c->tx_size256_511, clr);
        REG_CNT_10G(TX_SIZE512TO1023, i, &c->tx_size512_1023, clr);
        REG_CNT_10G(TX_SIZE1024TO1518, i, &c->tx_size1024_1518, clr);
        REG_CNT_10G(TX_SIZE1519TOMAX, i, &c->tx_size1519_max, clr);
    }

    /* QSYS counters */
    REG_WR(VTSS_XQS_STAT_CFG, VTSS_F_XQS_STAT_CFG_STAT_VIEW(port));
    addr = 16;
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->rx_green_drops[i], clr));
    }
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->rx_yellow_drops[i], clr));
    }
    addr = 256;
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->tx_green_class[i], clr));
    }
    for (i = 0; i < VTSS_PRIOS; i++) {
        VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->tx_yellow_class[i], clr));
    }
    VTSS_RC(vtss_fa_qsys_counter_update(vtss_state, &addr, &c->tx_queue_drops, clr));

    /* ANA_AC counters */
    REG_CNT_ANA_AC(PORT_STAT_LSB_CNT(port, REG_CNT_ANA_AC_PORT_FILTER), &c->rx_local_drops, clr);
    REG_CNT_ANA_AC(PORT_STAT_LSB_CNT(port, REG_CNT_ANA_AC_PORT_POLICER_DROPS), &c->rx_policer_drops, clr);
    for (i = 0; i < VTSS_PRIOS; i++) {
        REG_CNT_ANA_AC(QUEUE_STAT_LSB_CNT(port*8 + i, REG_CNT_ANA_AC_QUEUE_PRIO), &c->rx_class[i], clr);
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
    for (i = 0; i < VTSS_PRIOS; i++) {
        rmon->rx_etherStatsDropEvents += (c->rx_green_drops[i].value + c->rx_yellow_drops[i].value);
    }
    rmon->rx_etherStatsOctets = (c->rx_ok_bytes.value + c->rx_bad_bytes.value);
    rx_errors = (c->rx_crc_err.value +  c->rx_undersize.value + c->rx_oversize.value +
                 c->rx_out_of_range_len_err.value + c->rx_symbol_err.value +
                 c->rx_jabbers.value + c->rx_fragments.value);
    rmon->rx_etherStatsPkts = (c->rx_unicast.value + c->rx_multicast.value +
                               c->rx_broadcast.value + rx_errors);
    rmon->rx_etherStatsBroadcastPkts = c->rx_broadcast.value;
    rmon->rx_etherStatsMulticastPkts = c->rx_multicast.value;
    rmon->rx_etherStatsCRCAlignErrors = c->rx_crc_err.value;
    rmon->rx_etherStatsUndersizePkts = c->rx_undersize.value;
    rmon->rx_etherStatsOversizePkts = c->rx_oversize.value;
    rmon->rx_etherStatsFragments = c->rx_fragments.value;
    rmon->rx_etherStatsJabbers = c->rx_jabbers.value;
    rmon->rx_etherStatsPkts64Octets = c->rx_size64.value;
    rmon->rx_etherStatsPkts65to127Octets = c->rx_size65_127.value;
    rmon->rx_etherStatsPkts128to255Octets = c->rx_size128_255.value;
    rmon->rx_etherStatsPkts256to511Octets = c->rx_size256_511.value;
    rmon->rx_etherStatsPkts512to1023Octets = c->rx_size512_1023.value;
    rmon->rx_etherStatsPkts1024to1518Octets = c->rx_size1024_1518.value;
    rmon->rx_etherStatsPkts1519toMaxOctets = c->rx_size1519_max.value;

    /* RMON Tx counters */
    rmon->tx_etherStatsDropEvents = c->tx_queue_drops.value;
    rmon->tx_etherStatsPkts = (c->tx_unicast.value + c->tx_multicast.value +
                               c->tx_broadcast.value + c->tx_late_coll.value);
    rmon->tx_etherStatsOctets = c->tx_ok_bytes.value;
    rmon->tx_etherStatsBroadcastPkts = c->tx_broadcast.value;
    rmon->tx_etherStatsMulticastPkts = c->tx_multicast.value;
    rmon->tx_etherStatsCollisions = (c->tx_multi_coll.value + c->tx_backoff1.value +
                                     c->tx_late_coll.value + c->tx_xcoll.value);
    rmon->tx_etherStatsPkts64Octets = c->tx_size64.value;
    rmon->tx_etherStatsPkts65to127Octets = c->tx_size65_127.value;
    rmon->tx_etherStatsPkts128to255Octets = c->tx_size128_255.value;
    rmon->tx_etherStatsPkts256to511Octets = c->tx_size256_511.value;
    rmon->tx_etherStatsPkts512to1023Octets = c->tx_size512_1023.value;
    rmon->tx_etherStatsPkts1024to1518Octets = c->tx_size1024_1518.value;
    rmon->tx_etherStatsPkts1519toMaxOctets = c->tx_size1519_max.value;

    /* Interfaces Group Rx counters */
    if_group = &counters->if_group;
    if_group->ifInOctets = rmon->rx_etherStatsOctets;
    if_group->ifInUcastPkts = c->rx_unicast.value;
    if_group->ifInMulticastPkts = c->rx_multicast.value;
    if_group->ifInBroadcastPkts = c->rx_broadcast.value;
    if_group->ifInNUcastPkts = (c->rx_multicast.value + c->rx_broadcast.value);
    if_group->ifInDiscards = rmon->rx_etherStatsDropEvents;
    if_group->ifInErrors = rx_errors;

    /* Interfaces Group Tx counters */
    if_group->ifOutOctets = rmon->tx_etherStatsOctets;
    if_group->ifOutUcastPkts = c->tx_unicast.value;
    if_group->ifOutMulticastPkts = c->tx_multicast.value;
    if_group->ifOutBroadcastPkts = c->tx_broadcast.value;
    if_group->ifOutNUcastPkts = (c->tx_multicast.value + c->tx_broadcast.value);
    if_group->ifOutDiscards = rmon->tx_etherStatsDropEvents;
    if_group->ifOutErrors = (c->tx_late_coll.value + c->tx_csense.value + c->tx_xcoll.value);

#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    /* Ethernet-like Rx counters */
    elike = &counters->ethernet_like;
    elike->dot3StatsAlignmentErrors = 0; /* Not supported */
    elike->dot3StatsFCSErrors = c->rx_crc_err.value;
    elike->dot3StatsFrameTooLongs = c->rx_oversize.value;
    elike->dot3StatsSymbolErrors = c->rx_symbol_err.value;
    elike->dot3ControlInUnknownOpcodes = c->rx_unsup_opcode.value;
    elike->dot3InPauseFrames = c->rx_pause.value;

    /* Ethernet-like Tx counters */
    elike->dot3StatsSingleCollisionFrames = c->tx_backoff1.value;
    elike->dot3StatsMultipleCollisionFrames = c->tx_multi_coll.value;
    elike->dot3StatsDeferredTransmissions = c->tx_defer.value;
    elike->dot3StatsLateCollisions = c->tx_late_coll.value;
    elike->dot3StatsExcessiveCollisions = c->tx_xcoll.value;
    elike->dot3StatsCarrierSenseErrors = c->tx_csense.value;
    elike->dot3OutPauseFrames = c->tx_pause.value;
#endif /* VTSS_FEATURE_PORT_CNT_ETHER_LIKE */

#if defined(VTSS_FEATURE_PORT_CNT_BRIDGE)
    /* Bridge counters, including filtered frames with and without CRC error */
    counters->bridge.dot1dTpPortInDiscards = c->rx_local_drops.value;
#endif /* VTSS_FEATURE_PORT_CNT_BRIDGE */
    return VTSS_RC_OK;
}


static vtss_rc fa_port_counters(vtss_state_t                *vtss_state,
                                 const vtss_port_no_t        port_no,
                                 vtss_port_counters_t *const counters,
                                 BOOL                        clear)
{
    return fa_port_counters_chip(vtss_state,
                                  port_no,
                                  &vtss_state->port.counters[port_no].counter.fa,
                                  counters,
                                  clear);
}

static vtss_rc fa_port_counters_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return fa_port_counters(vtss_state, port_no, NULL, 0);
}

static vtss_rc fa_port_counters_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return fa_port_counters(vtss_state, port_no, NULL, 1);
}

static vtss_rc fa_port_basic_counters_get(vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no,
                                            vtss_basic_counters_t *const counters)
{
    vtss_port_fa_counters_t *c = &vtss_state->port.counters[port_no].counter.fa;
    VTSS_RC(fa_port_counters_update(vtss_state, port_no));
    counters->rx_frames = (c->rx_unicast.value + c->rx_multicast.value + c->rx_broadcast.value);
    counters->tx_frames = (c->tx_unicast.value + c->tx_multicast.value +
                               c->tx_broadcast.value + c->tx_late_coll.value);

    return VTSS_RC_ERROR;
}


static vtss_rc fa_port_counters_get(vtss_state_t *vtss_state,
                                      const vtss_port_no_t port_no,
                                      vtss_port_counters_t *const counters)
{
    memset(counters, 0, sizeof(*counters));
    return fa_port_counters(vtss_state, port_no, counters, 0);
}


static vtss_rc fa_port_forward_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_port_test_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}


 // Configure the defaults of the SQS mode.
vtss_rc vtss_fa_sqs_mode_set(vtss_state_t *vtss_state, fa_sqs_mode_t const *mode)
{
    return VTSS_RC_OK;
}

// Get the configs for a port/class
vtss_rc vtss_fa_sqs_conf_get(vtss_state_t *vtss_state, u32 id, const fa_sqs_conf_t *sqs)
{
    return VTSS_RC_OK;
}

// Set the configs for a port/class
vtss_rc vtss_fa_sqs_conf_set(vtss_state_t *vtss_state, u32 id, fa_sqs_conf_t const *sqs)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_wm_update(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}




/* - Debug print --------------------------------------------------- */

#define FA_DEBUG_MAC(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_MAC_##addr, i, "MAC_"name)
#define FA_DEBUG_PCS(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_PCS1G_##addr, i, "PCS1G_"name)
#define FA_DEBUG_10G_MAC(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV10G_MAC_##addr, i, "MAC_"name)
#define FA_DEBUG_FX100(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_##addr, i, name)

static vtss_rc fa_debug_chip_port(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info,
                                   vtss_port_no_t port_no)
{
    u32  port = VTSS_CHIP_PORT(port_no);
    u32  value, pcs_st, sd_indx, sd_type;
    u32  tgt = vtss_fa_dev_tgt(vtss_state, port_no);
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];

    if (fa_is_high_speed_device(vtss_state, port_no)) {
        u32 pcs = VTSS_TO_PCS_TGT(port); // only for 5G/10G/25G PCS
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_DEV_RST_CTRL(tgt), port, "DEV_RST_CTRL");
        FA_DEBUG_10G_MAC(pr, TX_MONITOR_STICKY(tgt), port, "TX_MONITOR_STICKY");
        FA_DEBUG_10G_MAC(pr, ENA_CFG(tgt), port, "ENA_CFG");
        FA_DEBUG_10G_MAC(pr, MODE_CFG(tgt), port, "MODE_CFG");

        pr("\nLink status (MAC/PCS):\n");
        pr("port          local_fault   remote_fault  idle_state    rx_blk_lock   rx_hi_ber\n");
        REG_RD(VTSS_DEV10G_MAC_TX_MONITOR_STICKY(tgt), &value);
        REG_RD(VTSS_PCS_10GBASE_R_PCS_STATUS(pcs), &pcs_st);
        pr("%-13d %-13d %-13d %-13d %-13d %-13d\n",
           port,
           VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(value),
           VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(value),
           VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(value),
           VTSS_X_PCS_10GBASE_R_PCS_STATUS_RX_BLOCK_LOCK(pcs_st),
           VTSS_X_PCS_10GBASE_R_PCS_STATUS_RX_HI_BER(pcs_st));
        // Clear the stickies
        REG_WR(VTSS_PCS_10GBASE_R_PCS_STATUS(pcs), 0xFFFFFFFF);

    } else {
        vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_DEV_RST_CTRL(tgt), port, "DEV_RST_CTRL");
        FA_DEBUG_MAC(pr, ENA_CFG(tgt), port, "ENA_CFG");
        FA_DEBUG_MAC(pr, MODE_CFG(tgt), port, "MODE_CFG");
        FA_DEBUG_MAC(pr, MAXLEN_CFG(tgt), port, "MAXLEN_CFG");
        FA_DEBUG_MAC(pr, TAGS_CFG(tgt), port, "TAGS_CFG");
        FA_DEBUG_REGX_NAME(pr, DSM, RX_PAUSE_CFG, port, "RX_PAUSE_CFG");
        FA_DEBUG_REGX_NAME(pr, DSM, ETH_FC_CFG, port, "ETH_FC_CFG");
        if (conf->if_type == VTSS_PORT_INTERFACE_100FX) {
            FA_DEBUG_FX100(pr, PCS_FX100_CFG(tgt), port, "PCS_FX100_CFG");
            FA_DEBUG_FX100(pr, PCS_FX100_STATUS(tgt), port, "FX100_STATUS");
        } else {
            FA_DEBUG_PCS(pr, CFG(tgt), port, "CFG");
            FA_DEBUG_PCS(pr, MODE_CFG(tgt), port, "MODE_CFG");
            FA_DEBUG_PCS(pr, SD_CFG(tgt), port, "SD_CFG");
            FA_DEBUG_PCS(pr, ANEG_CFG(tgt), port, "ANEG_CFG");
            FA_DEBUG_PCS(pr, ANEG_STATUS(tgt), port, "ANEG_STATUS");
            FA_DEBUG_PCS(pr, LINK_STATUS(tgt), port, "LINK_STATUS");
        }
    }

    pr("\nSerdes:\n"),
    (void)vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type);
    pr("Port is mapped to serdes %s index %d\n",
       (sd_type == FA_SERDES_TYPE_6G) ? "SD6G" :
       (sd_type == FA_SERDES_TYPE_10G) ? "SD10G" :
       (sd_type == FA_SERDES_TYPE_25G) ? "SD25G" : "N/A", sd_indx);


    pr("\n");
    return VTSS_RC_OK;
}

static vtss_rc fa_debug_port(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)

{
    vtss_port_no_t port_no;
    u32            port;
    char           buf[32];

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0)
            continue;
        port = VTSS_CHIP_PORT(port_no);

        sprintf(buf, "Port %u (%u) Dev%s_%d", port, port_no, VTSS_PORT_IS_25G(port) ? "25G" : \
                VTSS_PORT_IS_10G(port) ? "10G": VTSS_PORT_IS_5G(port) ? "5G" : "2G5", VTSS_PORT_DEV_INDX(port));

        vtss_fa_debug_reg_header(pr, buf);
        VTSS_RC(fa_debug_chip_port(vtss_state, pr, info, port_no));
    } /* Port loop */
    return VTSS_RC_OK;
}


static vtss_rc fa_debug_port_counters(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       const vtss_debug_info_t   *const info, vtss_port_no_t port_no)
{
    u32                      i;
    char                     rx_buf[32], tx_buf[32];
    vtss_port_fa_counters_t cnt;

    memset(&cnt, 0, sizeof(vtss_port_fa_counters_t));
    VTSS_RC(fa_port_counters_chip(vtss_state, port_no, &cnt, NULL, 0));

    if (port_no < vtss_state->port_count) {
        vtss_fa_debug_cnt(pr, "ok_bytes", "out_bytes", &cnt.rx_ok_bytes, &cnt.tx_out_bytes);
        vtss_fa_debug_cnt(pr, "uc", "", &cnt.rx_unicast, &cnt.tx_unicast);
        vtss_fa_debug_cnt(pr, "mc", "", &cnt.rx_multicast, &cnt.tx_multicast);
        vtss_fa_debug_cnt(pr, "bc", "", &cnt.rx_broadcast, &cnt.tx_broadcast);
    }

    if (!info->full) {
        pr("\n");
        return VTSS_RC_OK;
    }

    if (port_no < vtss_state->port_count) {
        vtss_fa_debug_cnt(pr, "pause", "", &cnt.rx_pause, &cnt.tx_pause);
        vtss_fa_debug_cnt(pr, "64", "", &cnt.rx_size64, &cnt.tx_size64);
        vtss_fa_debug_cnt(pr, "65_127", "", &cnt.rx_size65_127, &cnt.tx_size65_127);
        vtss_fa_debug_cnt(pr, "128_255", "", &cnt.rx_size128_255, &cnt.tx_size128_255);
        vtss_fa_debug_cnt(pr, "256_511", "", &cnt.rx_size256_511, &cnt.tx_size256_511);
        vtss_fa_debug_cnt(pr, "512_1023", "", &cnt.rx_size512_1023, &cnt.tx_size512_1023);
        vtss_fa_debug_cnt(pr, "1024_1526", "", &cnt.rx_size1024_1518, &cnt.tx_size1024_1518);
        vtss_fa_debug_cnt(pr, "jumbo", "", &cnt.rx_size1519_max, &cnt.tx_size1519_max);
        vtss_fa_debug_cnt(pr, "crc", NULL, &cnt.rx_crc_err, NULL);
    }
    vtss_fa_debug_cnt(pr, "local_drops", NULL, &cnt.rx_local_drops, NULL);
    vtss_fa_debug_cnt(pr, "policer_drops", "queue_drops", &cnt.rx_policer_drops, &cnt.tx_queue_drops);

    for (i = 0; i < VTSS_PRIOS; i++) {
        sprintf(rx_buf, "class_%u", i);
        vtss_fa_debug_cnt(pr, rx_buf, NULL, &cnt.rx_class[i], NULL);
    }
    for (i = 0; i < VTSS_PRIOS; i++) {
        sprintf(rx_buf, "green_drops_%u", i);
        sprintf(tx_buf, "green_%u", i);
        vtss_fa_debug_cnt(pr, rx_buf, tx_buf, &cnt.rx_green_drops[i], &cnt.tx_green_class[i]);
    }
    for (i = 0; i < VTSS_PRIOS; i++) {
        sprintf(rx_buf, "yellow_drops_%u", i);
        sprintf(tx_buf, "yellow_%u", i);
        vtss_fa_debug_cnt(pr, rx_buf, tx_buf, &cnt.rx_yellow_drops[i], &cnt.tx_yellow_class[i]);
    }
    pr("\n");

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_port_cnt(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455} */ // Due to VTSS_EXIT_ENTER
    vtss_port_no_t port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count + 4; port_no++) {
        if (port_no < vtss_state->port_count) {
            if (info->port_list[port_no] == 0)
                continue;
            pr("Counters for port: %u (chip_port: %u):\n\n", port_no, VTSS_CHIP_PORT(port_no));
        } else {
            if (!info->full)
                continue;
            pr("Counters for chip_port: %u:\n\n", VTSS_CHIP_PORT_CPU + port_no - vtss_state->port_count);
        }
        VTSS_EXIT_ENTER();
        (void)fa_debug_port_counters(vtss_state, pr, info, port_no);
    }
    pr("\n");

    return VTSS_RC_OK;
}


static vtss_rc fa_debug_wm(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t  *const info)

{
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_port_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT, fa_debug_port, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT_CNT, fa_debug_port_cnt, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_WM, fa_debug_wm, vtss_state, pr, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_port_init(vtss_state_t *vtss_state)
{

    // 13 x CMUs
    for (u32 i = 0; i <= 13; i++) {
        VTSS_RC(vtss_fa_cmu_cfg(vtss_state, i));
    }

    // 8 x 25G Macroes
    for (u32 i = 0; i <= 7; i++) {
        VTSS_RC(vtss_fa_sd25g_init(vtss_state, i));
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_port_state_t *state = &vtss_state->port;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->miim_read = fa_miim_read;
        state->miim_write = fa_miim_write;
        state->mmd_read = fa_mmd_read;
        state->mmd_read_inc = fa_mmd_read_inc;
        state->mmd_write = fa_mmd_write;
        state->conf_get = fa_port_conf_get;
        state->conf_set = fa_port_conf_set;
        state->clause_37_status_get = fa_port_clause_37_status_get;
        state->clause_37_control_get = fa_port_clause_37_control_get;
        state->clause_37_control_set = fa_port_clause_37_control_set;
#if defined(VTSS_FEATURE_10GBASE_KR_V2)
        state->kr_conf_set = fa_port_10g_kr_conf_set;
        state->kr_status = fa_port_10g_kr_status;
#endif /* VTSS_FEATURE_10G_BASE_KR */
        state->status_get = fa_port_status_get;
        state->counters_update = fa_port_counters_update;
        state->counters_clear = fa_port_counters_clear;
        state->counters_get = fa_port_counters_get;
        state->basic_counters_get = fa_port_basic_counters_get;
        state->forward_set = fa_port_forward_set;
        state->test_conf_set = fa_port_test_conf_set;

        /* SYNCE features */
#if defined(VTSS_FEATURE_SYNCE)
        vtss_state->synce.clock_out_set = fa_synce_clock_out_set;
        vtss_state->synce.clock_in_set = fa_synce_clock_in_set;
#endif /* VTSS_FEATURE_SYNCE */
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(fa_port_init(vtss_state));
        break;

    case VTSS_INIT_CMD_PORT_MAP:
// FA-FIXME        if (!vtss_state->warm_start_cur) {
// FA-FIXME            if (vtss_state->init_conf.qs_conf.mode == VTSS_QS_MODE_DEFAULT) {
// FA-FIXME                VTSS_RC(fa_port_buf_conf_set(vtss_state));
// FA-FIXME            } else {
// FA-FIXME                VTSS_RC(fa_port_buf_qlim_set(vtss_state));
// FA-FIXME            }
// FA-FIXME        }
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_FA */
