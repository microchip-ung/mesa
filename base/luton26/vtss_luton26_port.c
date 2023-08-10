// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_luton26_cil.h"

#if defined(VTSS_ARCH_LUTON26)

/* - CIL functions ------------------------------------------------- */

static vtss_rc l26_port_clause_37_control_get(vtss_state_t *vtss_state,
                                              const vtss_port_no_t port_no,
                                              vtss_port_clause_37_control_t *const control)
{
    u32 value, port = VTSS_CHIP_PORT(port_no);
    if (port < 12) {
        VTSS_I("The PCS block is only available in port modules 12 through 25. - Datasheet Section 3.1.3. Port:%d", port);
        return VTSS_RC_ERR_PCS_BLOCK_NOT_SUPPORTED;
    }

    L26_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(VTSS_TO_DEV(port)), &value);
    control->enable = VTSS_BOOL(value & VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA);
    value = VTSS_X_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(control->enable ? value : 0);
    VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &control->advertisement));

    return VTSS_RC_OK;
}

/* Set 1000Base-X Fiber Auto-negotiation (Clause 37) */
static vtss_rc l26_port_clause_37_control_set(vtss_state_t *vtss_state,
                                              const vtss_port_no_t port_no)
{
    vtss_port_clause_37_control_t *control = &vtss_state->port.clause_37[port_no];
    u32 value, tgt = VTSS_TO_DEV(vtss_state->port.map[port_no].chip_port);
    u32 port       = VTSS_CHIP_PORT(port_no);

    if (port < 12) {
        VTSS_I("The PCS block is only available in port modules 12 through 25. - Datasheet Section 3.1.3. Port:%d", port);
        return VTSS_RC_ERR_PCS_BLOCK_NOT_SUPPORTED;
    }

    /* Aneg capabilities for this port */
    VTSS_RC(vtss_cmn_port_clause_37_adv_set(&value, &control->advertisement, control->enable));

    /* Set aneg capabilities and restart */
    L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
           VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(value) |
           VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT |
           VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA);

    if (!control->enable) {
        /* Disable Aneg */
        L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
               VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(0) |
               VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT);

    }
    return VTSS_RC_OK;
}

/* Get 1000Base-X Fiber Auto-negotiation status (Clause 37) */
static vtss_rc l26_port_clause_37_status_get(vtss_state_t *vtss_state,
                                             const vtss_port_no_t         port_no,
                                             vtss_port_clause_37_status_t *const status)

{
    u32 value, tgt = VTSS_TO_DEV(vtss_state->port.map[port_no].chip_port);
    u32 port       = VTSS_CHIP_PORT(port_no);

    if (vtss_state->port.conf[port_no].power_down) {
        status->link = 0;
        return VTSS_RC_OK;
    }

    if (port < 12) {
        VTSS_I("The PCS block is only available in port modules 12 through 25. - Datasheet Section 3.1.3. Port:%d", port);
        return VTSS_RC_ERR_PCS_BLOCK_NOT_SUPPORTED;
    }

    /* Get the link state 'down' sticky bit  */
    L26_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);
    status->link = L26_BF(DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY, value) ? 0 : 1;
    if (status->link == 0) {
        /* The link has been down. Clear the sticky bit and return the 'down' value  */
        L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt),
               VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY |
               VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_OUT_OF_SYNC_STICKY);
    } else {
        L26_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(tgt), &value);
        status->link = L26_BF(DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS, value) &&
                       L26_BF(DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS, value);
    }

    /* Get PCS ANEG status register */
    L26_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS(tgt), &value);

    /* Get 'Aneg complete'   */
    status->autoneg.complete = L26_BF(DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);

    /* Workaround for a Serdes issue, when aneg completes with FDX capability=0 */
    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SERDES) {
        if (status->autoneg.complete) {
            if (((value >> 21) & 0x1) == 0) {
                L26_WRM_CLR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
                L26_WRM_SET(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
                (void)l26_port_clause_37_control_set(vtss_state, port_no); /* Restart Aneg */
                VTSS_MSLEEP(50);
                L26_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS(tgt), &value);
                status->autoneg.complete = L26_BF(DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);
            }
        }
    }

    /* Return partner advertisement ability */
    value = VTSS_X_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_LP_ADV_ABILITY(value);

    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
        status->autoneg.partner.sgmii.link = ((value >> 15) == 1) ? 1 : 0;
        status->autoneg.partner.sgmii.speed_10M = (((value >> 10) & 3) == 0) ? 1 : 0;
        status->autoneg.partner.sgmii.speed_100M =(((value >> 10) & 3) == 1) ? 1 : 0;
        status->autoneg.partner.sgmii.speed_1G =  (((value >> 10) & 3) == 2) ? 1 : 0;
        status->autoneg.partner.sgmii.fdx = (((value >> 12) & 0x1) == 1) ? 1 : 0;
        if (status->link) {
            /* If the SFP module does not have a link then the port does not have link */
            status->link = status->autoneg.partner.sgmii.link;
        }
    } else {
        VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &status->autoneg.partner.cl37));
    }

    return VTSS_RC_OK;
}

/* =================================================================
 *  Serdes configuration
 * =================================================================*/

#if VTSS_OPT_TRACE
static const char *l26_serdes_mode_txt(vtss_serdes_mode_t mode)
{
    return (mode == VTSS_SERDES_MODE_DISABLE ? "DISABLE" :
            mode == VTSS_SERDES_MODE_2G5 ? "2G5" :
            mode == VTSS_SERDES_MODE_QSGMII ? "QSGMII" :
            mode == VTSS_SERDES_MODE_SGMII ? "SGMII" : "?");
}
#endif

/* Serdes1G: Read/write data */
static vtss_rc l26_sd1g_read_write(vtss_state_t *vtss_state, u32 addr, BOOL write, u32 nsec)
{
    u32 data, mask;

    if (write)
        mask = VTSS_F_MACRO_CTRL_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_WR_ONE_SHOT;
    else
        mask = VTSS_F_MACRO_CTRL_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT;

    L26_WR(VTSS_MACRO_CTRL_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG,
           VTSS_F_MACRO_CTRL_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR(addr) | mask);

    do { /* Wait until operation is completed  */
        L26_RD(VTSS_MACRO_CTRL_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG, &data);
    } while (data & mask);

    if (nsec)
        VTSS_NSLEEP(nsec);

    return VTSS_RC_OK;
}

/* Serdes1G: Read data */
static vtss_rc l26_sd1g_read(vtss_state_t *vtss_state, u32 addr)
{
    return l26_sd1g_read_write(vtss_state, addr, 0, 0);
}

/* Serdes1G: Write data */
static vtss_rc l26_sd1g_write(vtss_state_t *vtss_state, u32 addr, u32 nsec)
{
    return l26_sd1g_read_write(vtss_state, addr, 1, nsec);
}

/* Wait 100 usec after some SerDes operations */
#define L26_SERDES_WAIT 100000
#define RCOMP_CFG0 VTSS_IOREG(VTSS_TO_MACRO_CTRL,0x8)
static vtss_rc l26_sd1g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_serdes_mode_t mode, u32 addr)
{
    vtss_port_lb_t lb = vtss_state->port.test_conf[port_no].loopback;
    BOOL ena_lane, if_100fx, ib_ena_dc_coupling=0;
    u32  ob_amp_ctrl, rcomp_val, resist_val, value, rev, des_phs_ctrl = 6, cmv_term = 1;

    VTSS_D("addr: 0x%x, mode: %s", addr, l26_serdes_mode_txt(mode));

    switch (mode) {
    case VTSS_SERDES_MODE_SGMII:
        ena_lane = 1;
        ob_amp_ctrl = 12;
        if_100fx = 0;
        break;
    case VTSS_SERDES_MODE_100FX:
        ena_lane = 1;
        ob_amp_ctrl = 12;
        if_100fx = 1;
        ib_ena_dc_coupling = 1;
        des_phs_ctrl = 14; // BZ21121
        cmv_term = 0;
        break;
    case VTSS_SERDES_MODE_1000BaseX:
        ena_lane = 1;
        ob_amp_ctrl = 15;
        if_100fx = 0;
        break;
    case VTSS_SERDES_MODE_DISABLE:
        if_100fx = 0;
        ena_lane = 0;
        ob_amp_ctrl = 0;
        break;
    default:
        VTSS_E("Serdes1g mode %s not supported", l26_serdes_mode_txt(mode));
        return VTSS_RC_ERROR;
    }

    L26_RD(VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID, &value);
    rev = VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID(value);

    /* RCOMP_CFG0.MODE_SEL = 2 */
    L26_WR(RCOMP_CFG0, 0x3<<8);

    /* RCOMP_CFG0.RUN_CAL = 1 */
    L26_WR(RCOMP_CFG0, 0x3<<8|1<<12);

    do { /* Wait for calibration to finish */
        L26_RD(VTSS_MACRO_CTRL_RCOMP_STATUS_RCOMP_STATUS, &rcomp_val);
    } while(rcomp_val & VTSS_F_MACRO_CTRL_RCOMP_STATUS_RCOMP_STATUS_BUSY);

    L26_RD(VTSS_MACRO_CTRL_RCOMP_STATUS_RCOMP_STATUS, &rcomp_val);
    rcomp_val = VTSS_X_MACRO_CTRL_RCOMP_STATUS_RCOMP_STATUS_RCOMP(rcomp_val);

    /* 1. Configure macro, apply reset */
    L26_WRM(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG,
            (if_100fx ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA : 0) |
            (ib_ena_dc_coupling ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING : 0) |
            (cmv_term ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM : 0) |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DETLEV |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV(3) |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_OFFSET_COMP |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL(rcomp_val-3) |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN(3),
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DETLEV |
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_OFFSET_COMP |
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL |
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN);

    L26_WRM(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG,
            (if_100fx ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL(2) : 0) |
            (if_100fx ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL(3) : 0) |
            (if_100fx ? 0 : VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA(6)) |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL(des_phs_ctrl),
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL |
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL |
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA |
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL);

    resist_val = (vtss_state->init_conf.serdes.serdes1g_vdd == VTSS_VDD_1V0) ? rcomp_val+1 : rcomp_val-4;
    L26_WRM(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_OB_CFG,
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_RESISTOR_CTRL(resist_val) |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL(ob_amp_ctrl),
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_RESISTOR_CTRL |
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL);

    L26_WRM_CTL(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_SER_CFG,
                lb == VTSS_PORT_LB_FACILITY,
                VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI);

    /* Write masked to avoid changing RECO_SEL_* fields used by SyncE */
    L26_WRM(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
            (ena_lane ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE : 0) |
            (lb == VTSS_PORT_LB_FACILITY ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP : 0) |
            (lb == VTSS_PORT_LB_EQUIPMENT ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP : 0) |
            VTSS_BIT(0),
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP |
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP |
           (rev == 0 ? VTSS_BIT(7) : 0) | /* Rev 0 -> HRATE = 0.  Rev 1 -> HRATE = 1 (default) */
            VTSS_BIT(0)); /* IFMODE = 1 */

    L26_WRM(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG,
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA |
            (rev == 0 ? VTSS_BIT(21) : 0) | /* Rev 0 -> RC_DIV2 = 1. Rev 1 -> RC_DIV2 = 0 (default) */
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA(200),
            VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA |
            VTSS_BIT(21) |
            VTSS_M_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA);

    L26_WRM(VTSS_MACRO_CTRL_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG,
            (if_100fx ? VTSS_F_MACRO_CTRL_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA : 0) |
            VTSS_F_MACRO_CTRL_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST,
            VTSS_F_MACRO_CTRL_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA |
            VTSS_F_MACRO_CTRL_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST);

    VTSS_RC(l26_sd1g_write(vtss_state, addr, L26_SERDES_WAIT));

    /* 2. Release PLL reset */
    L26_WRM_SET(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
                VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST);
    VTSS_RC(l26_sd1g_write(vtss_state, addr, L26_SERDES_WAIT));

    /* 3. Release digital reset */
    L26_WRM(VTSS_MACRO_CTRL_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG, 0,
            VTSS_F_MACRO_CTRL_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST);
    VTSS_RC(l26_sd1g_write(vtss_state, addr, 0));

    return VTSS_RC_OK;
}


/* Serdes6G: Read/write data */
static vtss_rc l26_sd6g_read_write(vtss_state_t *vtss_state, u32 addr, BOOL write, u32 nsec)
{
    u32 data, mask;

    if (write)
        mask = VTSS_F_MACRO_CTRL_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT;
    else
        mask = VTSS_F_MACRO_CTRL_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT;

    L26_WR(VTSS_MACRO_CTRL_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG,
           VTSS_F_MACRO_CTRL_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(addr) | mask);

    do { /* Wait until operation is completed  */
        L26_RD(VTSS_MACRO_CTRL_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG, &data);
    } while (data & mask);

    if (nsec)
        VTSS_NSLEEP(nsec);

    return VTSS_RC_OK;
}

/* Serdes6G: Read data */
static vtss_rc l26_sd6g_read(vtss_state_t *vtss_state, u32 addr)
{
    return l26_sd6g_read_write(vtss_state, addr, 0, 0);
}

/* Serdes6G: Write data */
static vtss_rc l26_sd6g_write(vtss_state_t *vtss_state, u32 addr, u32 nsec)
{
    return l26_sd6g_read_write(vtss_state, addr, 1, nsec);
}

/* Serdes6G setup (Disable/2G5/QSGMII/SGMII) */
static vtss_rc l26_sd6g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_serdes_mode_t mode, u32 addr)
{
    vtss_port_lb_t lb = vtss_state->port.test_conf[port_no].loopback;
    u32 ib_rf, ctrl_data, if_mode=1, ob_ena_cas, ob_lev, ib_vbac=5, ib_vbcom=4, rcomp_val, ob_post_0=0, ib_ic_ac=0, ib_c=15, ib_chf=0;
    u32 ob_sr = 7, des_phs_ctrl = 6;
    BOOL ena_lane=1, ena_rot=0, qrate, hrate, ob_ena1v, if_100fx=0, ib_cterm_ena;


    VTSS_D("addr: 0x%x, mode: %s", addr, l26_serdes_mode_txt(mode));
    ob_ena1v = (vtss_state->init_conf.serdes.serdes6g_vdd == VTSS_VDD_1V0) ? 1 : 0;
    ib_cterm_ena = (vtss_state->init_conf.serdes.ib_cterm_ena);

    switch (mode) {
    case VTSS_SERDES_MODE_2G5:
        /* Seredes6g_ob_cfg  */
        ob_post_0 = 2;
        /* Seredes6g_ob_cfg1 */
        ob_ena_cas = 1;
        ob_lev = ob_ena1v ? 48 : 63;
        /* Seredes6g_des_cfg --> see code */
        /* Seredes6g_ib_cfg */
        ib_ic_ac = ob_ena1v ? 2 : 0;
        ib_vbac  = ob_ena1v ? 4 : 5;
        ib_rf    = ob_ena1v ? 2 : 10;
        ib_vbcom = ob_ena1v ? 4 : 5;
        /* Seredes6g_ib_cfg1 */
        ib_c = ob_ena1v ? 6 : 10;
        ib_chf = ob_ena1v ? 1 : 0;
        /* Seredes6g_pll_cfg */
        ena_rot = 1;
        ctrl_data = 48;
        /* Seredes6g_common_cfg */
        qrate = 0;
        hrate = 1;
        break;
    case VTSS_SERDES_MODE_QSGMII:
        /* Seredes6g_ob_cfg  */
        ob_sr = vtss_state->init_conf.serdes.qsgmii.ob_sr;
        ob_post_0 = vtss_state->init_conf.serdes.qsgmii.ob_post0;
        /* Seredes6g_ob_cfg1 */
        ob_ena_cas = 1;
        ob_lev = 24;
        /* Seredes6g_ib_cfg */
        ib_rf = 4;
        /* Seredes6g_ib_cfg1 */
        ib_c = 4;
        /* Seredes6g_pll_cfg */
        /* Seredes6g_pll_cfg */
        ctrl_data = 120;
        if_mode = 3;
        qrate = 0;
        hrate = 0;
        break;
    case VTSS_SERDES_MODE_SGMII:
        ob_lev = 48;
        ob_ena_cas = 2;
        ib_rf = 15;
        ctrl_data = 60;
        qrate = 1;
        hrate = 0;
        break;
    case VTSS_SERDES_MODE_100FX:
        ob_lev = 48;
        ob_ena_cas = 1;
        ib_rf = 15;
        ctrl_data = 60;
        qrate = 1;
        hrate = 0;
        if_100fx = 1;
        des_phs_ctrl = 14; // BZ21121
        break;
    case VTSS_SERDES_MODE_1000BaseX:
        ob_lev = 48;
        ob_ena_cas = 2;
        ib_rf = 15;
        ctrl_data = 60;
        qrate = 1;
        hrate = 0;
        break;
    case VTSS_SERDES_MODE_DISABLE:
        ob_lev = 0;
        ob_ena_cas = 0;
        ib_rf = 0;
        ib_vbcom = 0;
        ena_rot = 0;
        ctrl_data = 0;
        qrate = 0;
        hrate = 0;
        break;
    default:
        VTSS_E("Serdes6g mode %s not supported", l26_serdes_mode_txt(mode));
        return VTSS_RC_ERROR;
    }
    /* RCOMP_CFG0.MODE_SEL = 2 */
    L26_WR(RCOMP_CFG0, 0x3<<8);

    /* RCOMP_CFG0.RUN_CAL = 1 */
    L26_WR(RCOMP_CFG0, 0x3<<8|1<<12);

    do { /* Wait for calibration to finish */
        L26_RD(VTSS_MACRO_CTRL_RCOMP_STATUS_RCOMP_STATUS, &rcomp_val);
    } while(rcomp_val & VTSS_F_MACRO_CTRL_RCOMP_STATUS_RCOMP_STATUS_BUSY);

    L26_RD(VTSS_MACRO_CTRL_RCOMP_STATUS_RCOMP_STATUS, &rcomp_val);
    rcomp_val = VTSS_X_MACRO_CTRL_RCOMP_STATUS_RCOMP_STATUS_RCOMP(rcomp_val);

    /* 1. Configure macro, apply reset */
    /* OB_CFG  */
    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POL |
            VTSS_ENCODE_BITFIELD(rcomp_val+1,4,4) | /* RCOMP: bit 4-7 */
            VTSS_ENCODE_BITFIELD(ob_sr,0,4) |       /* SR:    bit 0-3 */
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(ob_post_0) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H |
            (ob_ena1v ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE : 0),
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POL |
            VTSS_ENCODE_BITMASK(4,4) | /* RCOMP: bit 4-7 */
            VTSS_ENCODE_BITMASK(0,4) | /* SR:    bit 0-3 */
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0 |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE);

    /* OB_CFG1 */
    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1,
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(ob_ena_cas) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(ob_lev),
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV);

     /* IB_CFG */
    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_AC(ib_ic_ac) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RT(15) |
            VTSS_ENCODE_BITFIELD(ib_vbac,7,3) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RESISTOR_CTRL(rcomp_val+2) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBCOM(ib_vbcom) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RF(ib_rf),
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_IC_AC |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RT |
            VTSS_ENCODE_BITMASK(7,3) |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RESISTOR_CTRL |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBCOM |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RF);

    /* IB_CFG1 */
    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
            (ib_cterm_ena ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_CTERM_ENA : 0) |
            (ib_chf ? VTSS_BIT(7) : 0 ) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_C(ib_c) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_DIS_EQ |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_ENA_OFFSAC |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_ENA_OFFSDC |
            (if_100fx ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FX100_ENA : 0) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_RST,
            VTSS_BIT(7) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_CTERM_ENA |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_C |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_DIS_EQ |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_ENA_OFFSAC |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_ENA_OFFSDC |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FX100_ENA |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_RST);

    /* DES_CFG */
    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(des_phs_ctrl) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_MBTR_CTRL(2) |
           (if_100fx ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(2) : 0) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_HYST(5) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(5),
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_MBTR_CTRL |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_HYST |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA);

    /* PLL_CFG */
    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(ctrl_data) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA |
            (ena_rot ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT : 0),
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT);

    L26_WRM_CTL(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_SER_CFG,
                lb == VTSS_PORT_LB_FACILITY,
                VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI);

    /* Write masked to avoid changing RECO_SEL_* fields used by SyncE */
    /* COMMON_CFG */
    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
            (ena_lane ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE : 0) |
            (lb == VTSS_PORT_LB_FACILITY ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP : 0) |
            (lb == VTSS_PORT_LB_EQUIPMENT ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP : 0) |
            (hrate ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE : 0) |
            (qrate ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE : 0) |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(if_mode),
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE |
            VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE |
            VTSS_M_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE);


    /* MISC_CFG */
    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
            (if_100fx ? VTSS_F_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA : 0),
            VTSS_F_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA);

    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
            (if_100fx ? VTSS_F_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA : 0) |
            VTSS_F_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST,
            VTSS_F_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA |
            VTSS_F_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

    VTSS_RC(l26_sd6g_write(vtss_state, addr, L26_SERDES_WAIT));

    /* 2. Release PLL reset */
    L26_WRM_SET(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);
    VTSS_RC(l26_sd6g_write(vtss_state, addr, L26_SERDES_WAIT));

    /* 3. Release digital reset */
    L26_WRM_CLR(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
                VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_RST);

    L26_WRM(VTSS_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG, 0,
            VTSS_F_MACRO_CTRL_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);
    VTSS_RC(l26_sd6g_write(vtss_state, addr, 0));

    return VTSS_RC_OK;
}


/* Configures the Serdes1G/Serdes6G blocks based on mux mode and Target */
static vtss_rc l26_serdes_macro_config(vtss_state_t *vtss_state)
{
    vtss_port_mux_mode_t mux_mode = vtss_state->init_conf.mux_mode;
    u32                  sw_mode;

    /* Setup mux mode */
    switch (mux_mode) {
    case VTSS_PORT_MUX_MODE_0:
        sw_mode = 0;
        break;
    case VTSS_PORT_MUX_MODE_1:
        sw_mode = 1;
        break;
    case VTSS_PORT_MUX_MODE_2:
        sw_mode = 2;

        /* In mode 2, ports 10 and 11 are connected to Serdes1G Macro */
        L26_WR(VTSS_DEV_DEV_CFG_STATUS_DEV_IF_CFG(VTSS_TO_DEV(10)), 1);
        L26_WR(VTSS_DEV_DEV_CFG_STATUS_DEV_IF_CFG(VTSS_TO_DEV(11)), 1);
        break;
    default:
        VTSS_E("port mux mode not supported");
        return VTSS_RC_ERROR;
    }

    L26_WRM(VTSS_DEVCPU_GCB_MISC_MISC_CFG,
            VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_SW_MODE(sw_mode),
            VTSS_M_DEVCPU_GCB_MISC_MISC_CFG_SW_MODE);

    /* Setup macros */
    switch (vtss_state->create.target) {
    case VTSS_TARGET_SPARX_III_10:
    case VTSS_TARGET_SPARX_III_10_01:
        if (mux_mode != VTSS_PORT_MUX_MODE_2) {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }

        VTSS_RC(l26_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x3)); /* SGMII mode, Serdes1g (1-0) */
        break;
    case VTSS_TARGET_SPARX_III_18:
        if (mux_mode == VTSS_PORT_MUX_MODE_0) {
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_QSGMII, 0x2));  /* QSGMII mode, Serdes6g (1) */
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x1));   /* SGMII mode, Serdes6g (0) */
            VTSS_RC(l26_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x1));   /* SGMII mode, Serdes1g (0) */
        } else if (mux_mode == VTSS_PORT_MUX_MODE_2) {
            VTSS_RC(l26_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x3F));  /* Enable SGMII, Serdes1g (5-0)   */
        } else {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_TARGET_SPARX_III_24:
        if (mux_mode != VTSS_PORT_MUX_MODE_0) {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }
        VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_QSGMII, 0xE));     /* Enable QSGMII, Serdes6g (3-1) */
        break;
    case VTSS_TARGET_SPARX_III_26:
        if (mux_mode != VTSS_PORT_MUX_MODE_0) {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }
        VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_QSGMII, 0xE));     /* Enable QSGMII, Serdes6g (3-1) */
        VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x1));      /* Enable SGMII, Serdes6g (0) */
        VTSS_RC(l26_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x1));      /* Enable SGMII, Serdes1g (0) */
        break;
    case VTSS_TARGET_CARACAL_LITE:
    case VTSS_TARGET_CARACAL_1:
        if (mux_mode != VTSS_PORT_MUX_MODE_1) {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }
        VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_2G5, 0x3));        /* Enable 2.5G, Serdes6g (1-0) */
        VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x4));      /* Enable SGMII, Serdes6g (2) */
        VTSS_RC(l26_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0xFF));     /* Enable SGMII, Serdes1g (7-0) */
        break;
    case VTSS_TARGET_CARACAL_2:
        if (mux_mode == VTSS_PORT_MUX_MODE_0) {
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_2G5, 0x1));    /* Enable 2.5G, Serdes6g (0) */
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_QSGMII, 0xE)); /* Enable QSGMII, Serdes6g (3-1) */
            VTSS_RC(l26_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 1));    /* Enable SGMII, Serdes1g (0) */
        } else if (mux_mode == VTSS_PORT_MUX_MODE_1) {
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_2G5, 0x3));    /* Enable 2.5G, Serdes6g (1-0) */
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0xC));  /* Enable SGMII, Serdes6g (3-2) */
            VTSS_RC(l26_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0xFF)); /* Enable SGMII, Serdes1g (7-0) */
        } else if (mux_mode == VTSS_PORT_MUX_MODE_2) {
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_QSGMII, 0xC)); /* Enable QSGMII, Serdes6g (3-2) */
            VTSS_RC(l26_sd1g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0xFF)); /* Enable SGMII, Serdes1g (7-0) */
        } else {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_TARGET_SPARX_III_10_UM:
        if (mux_mode == VTSS_PORT_MUX_MODE_1) {
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x3));  /* Enable SGMII, Serdes6g (1-0) */
        } else {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_TARGET_SPARX_III_17_UM:
        if (mux_mode == VTSS_PORT_MUX_MODE_0) {
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x1));  /* Enable SGMII, Serdes6g (0) */
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_QSGMII, 0x8)); /* Enable QSGMII, Serdes6g (3) */
        } else if (mux_mode == VTSS_PORT_MUX_MODE_1) {
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0xF));  /* Enable SGMII, Serdes6g (3-0) */
        } else {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_TARGET_SPARX_III_25_UM:
        if (mux_mode == VTSS_PORT_MUX_MODE_0) {
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_QSGMII, 0xE)); /* Enable QSGMII, Serdes6g (3-1) */
            VTSS_RC(l26_sd6g_cfg(vtss_state, VTSS_PORT_NO_START, VTSS_SERDES_MODE_SGMII, 0x1));  /* Enable SGMII, Serdes6g (0) */
        } else {
            VTSS_E("Mux mode not supported for this Target");
            return VTSS_RC_ERROR;
        }
        break;
    default:
        VTSS_E("Unknown Target");
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}


static vtss_rc l26_miim_read_write(vtss_state_t *vtss_state,
                                   BOOL read,
                                   u32 miim_controller,
                                   u8 miim_addr,
                                   u8 addr,
                                   u16 *value,
                                   BOOL report_errors)
{
    u32 data;

    /* Command part */
    data = (read ? VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(2) : /* Read op */
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(1) | /* Write op */
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(*value)); /* value */

    /* Addressing part */
    data |=
        VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD | /* Valid command */
        VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(addr) | /* Register address */
        VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(miim_addr); /* Phy/port address */

    /* Enqueue MIIM operation to be executed */
    L26_WR(VTSS_DEVCPU_GCB_MIIM_MII_CMD(miim_controller), data);

    /* Wait for MIIM operation to finish */
    do {
        L26_RD(VTSS_DEVCPU_GCB_MIIM_MII_STATUS(miim_controller), &data);
    } while(data & VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_BUSY);

    if (read) {
        L26_RD(VTSS_DEVCPU_GCB_MIIM_MII_DATA(miim_controller), &data);
        if (data & VTSS_F_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS(3))
            return VTSS_RC_ERROR;
        *value = VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(data);
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_miim_read(vtss_state_t *vtss_state,
                             vtss_miim_controller_t miim_controller,
                             u8 miim_addr,
                             u8 addr,
                             u16 *value,
                             BOOL report_errors)
{
    return l26_miim_read_write(vtss_state, TRUE, miim_controller, miim_addr, addr,
                               value, report_errors);
}

static vtss_rc l26_miim_write(vtss_state_t *vtss_state,
                              vtss_miim_controller_t miim_controller,
                              u8 miim_addr,
                              u8 addr,
                              u16 value,
                              BOOL report_errors)
{
    return l26_miim_read_write(vtss_state, FALSE, miim_controller, miim_addr, addr,
                               &value, report_errors);
}

#define PHY_CMD_WRITE    1 /* 10G: Write */
#define PHY_CMD_READ_INC 2 /* 10G: Read and increment */
#define PHY_CMD_READ     3 /* 10G: Read */

static vtss_rc l26_mmd_cmd(vtss_state_t *vtss_state,
                           u32 cmd,
                           u32 miim_controller,
                           u8 miim_addr,
                           u8 mmd,
                           u8 addr,
                           u16 *value,
                           BOOL report_errors)
{
    u32 data;
    vtss_rc rc = VTSS_RC_OK;

    /* Switch to clause 45 */
    L26_WRM(VTSS_DEVCPU_GCB_MIIM_MII_CFG(miim_controller),
            VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(0),
            VTSS_M_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD);

    /* Enqueue address set operation */
    L26_WR(VTSS_DEVCPU_GCB_MIIM_MII_CMD(miim_controller),
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(miim_addr) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(mmd) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(addr) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(0));

    /* Wait for MIIM operation to finish */
    do {
        L26_RD(VTSS_DEVCPU_GCB_MIIM_MII_STATUS(miim_controller), &data);
    } while(data & VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_BUSY);

    /* Enqueue read or write operation */
    L26_WR(VTSS_DEVCPU_GCB_MIIM_MII_CMD(miim_controller),
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(miim_addr) |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(mmd) |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(*value) |
           VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(cmd));

    /* Wait for MIIM operation to finish */
    do {
        L26_RD(VTSS_DEVCPU_GCB_MIIM_MII_STATUS(miim_controller), &data);
    } while(data & VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_BUSY);

    if (cmd == PHY_CMD_READ || cmd == PHY_CMD_READ_INC) {
        L26_RD(VTSS_DEVCPU_GCB_MIIM_MII_DATA(miim_controller), &data);
        if (data & VTSS_F_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS(3))
            rc = VTSS_RC_ERROR;
        *value = VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(data);
    }

    /* Switch back to clause 22 */
    L26_WRM(VTSS_DEVCPU_GCB_MIIM_MII_CFG(miim_controller),
            VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(1),
            VTSS_M_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD);

    return rc;
}

static vtss_rc l26_mmd_read(vtss_state_t *vtss_state,
                            vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                            u16 addr, u16 *value, BOOL report_errors)
{
    return l26_mmd_cmd(vtss_state, PHY_CMD_READ, miim_controller, miim_addr, mmd, addr, value, report_errors);
}

static vtss_rc l26_mmd_write(vtss_state_t *vtss_state,
                             vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                             u16 addr, u16 value, BOOL report_errors)
{
    return l26_mmd_cmd(vtss_state, PHY_CMD_WRITE, miim_controller, miim_addr, mmd, addr, &value, report_errors);
}

static vtss_rc l26_mmd_read_inc(vtss_state_t *vtss_state,
                                vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                u16 addr, u16 *buf, u8 count, BOOL report_errors)
{
    while (count > 1) {
        VTSS_RC(l26_mmd_cmd(vtss_state, PHY_CMD_READ_INC, miim_controller, miim_addr, mmd, addr, buf, report_errors));
        buf++;
        count--;
    }
    return VTSS_RC_OK;
}

// Watermark values encoded at little odd for values larger than 1024
/*
 * Watermark encode/decode for SYS:RES_CTRL:RES_CFG.WM_HIGH
 * Bit 10:  Unit; 0:1, 1:16
 * Bit 9-0: Value to be multiplied with unit
 */
static int wm_enc(int value) {
    if (value >= 1024) {
        return 1024 + value / 16;
    }
    return value;
}

static u32 wm_dec(u32 value)
{
    if (value > 1024) {
        return (value - 1024) * 16;
    }
    return value;
}

/* Setup water marks, drop levels, etc for port */
static vtss_rc l26_port_fc_setup(vtss_state_t *vtss_state, u32 port,
                                 const vtss_port_conf_t *const conf)
{
    const u8 *mac;
    u32 pause_start, pause_stop, rsrv_raw, rsrv_total=0, atop_wm, q, sum_port, sum_cpu, val;
    vtss_port_conf_t *conf_tmp;
    vtss_port_no_t port_no;


    pause_stop  = 0x7ff;
    pause_start = 0x7ff;
    rsrv_raw = 0;

    if (conf->flow_control.generate) {
        // pause_start must be greater than reserved memory for
        //    IGR_WM(PORT) + IGR_WM(PORT, PRIO)
        // and
        //    EGR_WM(CPUPORT_0) + EGR_WM(CPUPORT_0, PRIO)
        // The latter is required in order not to transmit pause frames when the
        // CPU is congested.

        // Per port:
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG(  0 /* ingress */ + 224 /* per port */ + port),                 &sum_port);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG(512 /* egress  */ + 224 /* per port */ + VTSS_CHIP_PORT_CPU_0), &sum_cpu);

        // Per prio:
        for (q = 0; q < VTSS_PRIOS; q++) {
            L26_RD(VTSS_SYS_RES_CTRL_RES_CFG(  0 /* ingress */ + port *                 VTSS_PRIOS /* per prio */ + q), &val);
            sum_port += val;

            L26_RD(VTSS_SYS_RES_CTRL_RES_CFG(512 /* egress  */ + VTSS_CHIP_PORT_CPU_0 * VTSS_PRIOS /* per prio */+ q), &val);
            sum_cpu += val;
        }

        pause_start = MAX(sum_port, sum_cpu);

        // Allow for a standard frame.
        pause_start += VTSS_MAX_FRAME_LENGTH_STANDARD / L26_BUFFER_CELL_SZ;
    }

    if (conf->flow_control.generate && conf->max_frame_length <= VTSS_MAX_FRAME_LENGTH_STANDARD) {
        /* FC enabled and no jumbo */
        pause_stop  = 127;    /* 4 x 1518 / 48 */
        rsrv_raw  =  253;     /* 8 x 1518 / 48 */
    } else if (conf->flow_control.generate && conf->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
        /* FC enabled and jumbo */
        pause_stop = 158;     /* 5 x 1518 / 48 */
        rsrv_raw =  284;      /* 9 x 1518 / 48 */
    } else if (!conf->flow_control.generate && conf->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
        /* FC disabled and jumbo */
        rsrv_raw  = 250;      /* 12000 / 48 */
    }

    /* Calculate the total reserved space for all ports*/
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        conf_tmp = &vtss_state->port.conf[port_no];
        if (conf_tmp->flow_control.generate && conf_tmp->max_frame_length <= VTSS_MAX_FRAME_LENGTH_STANDARD) {
            rsrv_total +=  12144; /* 8*1518 */
        } else if (conf_tmp->flow_control.generate && conf_tmp->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
            rsrv_total +=  13662; /* 9*1518 */
        } else if (!conf_tmp->flow_control.generate && conf_tmp->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
            rsrv_total  += 12000;
        }
    }

    /* Set Pause WM hysteresis*/
    L26_WR(VTSS_SYS_PAUSE_CFG_PAUSE_CFG(port),
           VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(wm_enc(pause_start)) |
           VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(pause_stop) |
           (conf->flow_control.generate ? VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA : 0));

    atop_wm = (L26_BUFFER_MEMORY - rsrv_total)/L26_BUFFER_CELL_SZ;
    if (atop_wm >= 1024) {
        atop_wm = 1024 + atop_wm/16;
    }

    /*  When 'port ATOP' and 'common ATOP_TOT' are exceeded, tail dropping is activated on a port */
    L26_WR(VTSS_SYS_PAUSE_CFG_ATOP_TOT_CFG, atop_wm);
    L26_WR(VTSS_SYS_PAUSE_CFG_ATOP(port), rsrv_raw);

    /* Set SMAC of Pause frame */
    mac = &conf->flow_control.smac.addr[0];
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG(VTSS_TO_DEV(port)),(mac[0]<<16) | (mac[1]<<8) | mac[2]);
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG(VTSS_TO_DEV(port)), (mac[3]<<16) | (mac[4]<<8) | mac[5]);

    /* Enable/disable FC incl. pause value and zero pause */
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_CFG(VTSS_TO_DEV(port)),
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_ZERO_PAUSE_ENA |
           (conf->flow_control.obey ? VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_RX_FC_ENA  : 0) |
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_PAUSE_VAL_CFG(0xff) |
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_FC_LATENCY_CFG(63));  /* changed from 7 to 63 (recommended by MOT) */

    return VTSS_RC_OK;
}

/* Returns the serdes instance and if it is a serdes6g or serdes1g */
static vtss_rc serdes_instance_get(vtss_state_t *vtss_state,
                                   u32 port, u32 *instance, BOOL *serdes6g)
{
    vtss_port_mux_mode_t mode = vtss_state->init_conf.mux_mode;

    int mode_0_serd6[] =  {-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,0,1};
    int mode_0_inst[] =   {-1,-1,3,3,3,3,2,2,2,2,1,1,1,1,0,0};

    int mode_1_serd6[] =  {-1,-1,-1,-1,0,0,1,0,0,1,0,0,0,0,1,1};
    int mode_1_inst[] =   {-1,-1,-1,-1,7,6,3,5,4,2,3,2,1,0,1,0};

    int mode_2_serd6[] =  {0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0};
    int mode_2_inst[] =   {7,6,3,3,3,3,2,2,2,2,5,4,3,2,0,1};

    if (port < 10) {
        return VTSS_RC_ERROR;
    }

    if (mode == 0) {
        if (mode_0_inst[port-10] == -1) {
            return VTSS_RC_ERROR;
        }
        *instance = mode_0_inst[port-10];
        *serdes6g = mode_0_serd6[port-10];
    } else if (mode == 1) {
        if (mode_1_inst[port-10] == -1) {
            return VTSS_RC_ERROR;
        }
        *instance = mode_1_inst[port-10];
        *serdes6g = mode_1_serd6[port-10];
    } else {
        *instance = mode_2_inst[port-10];
        *serdes6g = mode_2_serd6[port-10];
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_l26_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_max_tags_t  max_tags = vtss_state->port.conf[port_no].max_tags;
    vtss_vlan_port_type_t vlan_type = vtss_state->l2.vlan_port_conf[port_no].port_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    u32                   tgt = VTSS_TO_DEV(port);
    u32                   etype, double_ena, single_ena;

    /* S-ports and VLAN unaware ports both support 0x88a8 (in addition to 0x8100) */
    etype = (vlan_type == VTSS_VLAN_PORT_TYPE_S_CUSTOM ? vtss_state->l2.vlan_conf.s_etype :
             vlan_type == VTSS_VLAN_PORT_TYPE_C ? VTSS_ETYPE_TAG_C : VTSS_ETYPE_TAG_S);
    single_ena = (max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1);
    double_ena = (max_tags == VTSS_PORT_MAX_TAGS_TWO ? 1 : 0);

    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_TAGS_CFG(tgt),
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(etype) |
           (double_ena ? VTSS_F_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_DBL_AWR_ENA : 0) |
           (single_ena ? VTSS_F_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_AWR_ENA : 0) |
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA);
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_PORT_PCS_CONF)
// ECOS-148 / BZ9251
static vtss_rc l26_port_oos_fix(vtss_state_t *vtss_state, u32 port, vtss_port_pcs_conf_t pcs)
{
    u32 tgt = VTSS_TO_DEV(port);
    if (port < 10) {
        VTSS_E("Chip port:%d does not support PCS operations\n", port);
        return VTSS_RC_ERROR;
    } else if (port < 12 && (vtss_state->init_conf.mux_mode != VTSS_PORT_MUX_MODE_2)) {
        return VTSS_RC_OK; // PCS not used
    }
    if (pcs == VTSS_PORT_PCS_ENABLE) {
        VTSS_I("Port:%d Enable PCS and return", port);
        L26_WRM(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt),
                VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA,
                VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
    } else {
        VTSS_I("Port:%d Disable PCS and return", port);
        L26_WRM(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt),
                0,
                VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
    }
    VTSS_MSLEEP(10);
    L26_WRM(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt),
            pcs == VTSS_PORT_PCS_ENABLE ? 0 : VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_RX_RST,
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_RX_RST);

    return VTSS_RC_OK;
}
#endif


/* HDX gap_1 is also used to detect speed in warm start synchronization */
typedef enum {
    L26_HDX_GAP_1_10M = 11,
    L26_HDX_GAP_1_100M = 9,
    L26_HDX_GAP_1_1G = 0,
    L26_HDX_GAP_1_2500M = 1
} l26_hdx_gap_1_t;

static vtss_rc l26_port_conf_get(vtss_state_t *vtss_state,
                                 const vtss_port_no_t port_no, vtss_port_conf_t *const conf)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 tgt = VTSS_TO_DEV(port);
    u32 value;

    /* Speed, detected using HDX gap_1 */
    L26_RD(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_IFG_CFG(tgt), &value);
    switch (VTSS_X_DEV_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1(value)) {
    case L26_HDX_GAP_1_10M:
        conf->speed = VTSS_SPEED_10M;
        break;
    case L26_HDX_GAP_1_100M:
        conf->speed = VTSS_SPEED_100M;
        break;
    case L26_HDX_GAP_1_2500M:
        conf->speed = VTSS_SPEED_2500M;
        break;
    default:
        conf->speed = VTSS_SPEED_1G;
        break;
    }

    /* Duplex */
    L26_RD(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_MODE_CFG(tgt), &value)
    conf->fdx = VTSS_BOOL(value & VTSS_F_DEV_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA);

    /* Power down */
    L26_RD(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_ENA_CFG(tgt), &value);
    conf->power_down = (value & VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA ? 0 : 1);

    /* Flow control */
    L26_RD(VTSS_SYS_PAUSE_CFG_PAUSE_CFG(port), &value);
    conf->flow_control.generate = VTSS_BOOL(value & VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA);
    L26_RD(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_CFG(tgt), &value);
    conf->flow_control.obey = VTSS_BOOL(value & VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_RX_FC_ENA);

    return VTSS_RC_OK;
}

/* MAC config for internal(0-11), SGMII, Serdes, 100fx and VAUI ports.        */
/* Ports 10 and 11 can connect to internal Phys (GMII) or to a Serdes1g macro */
static vtss_rc l26_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t       *conf = &vtss_state->port.conf[port_no];
    u32                    port = VTSS_CHIP_PORT(port_no);
    u32                    link_speed, value, tgt = VTSS_TO_DEV(port), instance;
    vtss_port_interface_t  if_type = conf->if_type;
    vtss_port_frame_gaps_t gaps;
    vtss_port_speed_t      speed = conf->speed;
    BOOL                   fdx=conf->fdx, disable=conf->power_down;
    BOOL                   sgmii=0, if_100fx=0, serdes6g;
    vtss_serdes_mode_t     mode = VTSS_SERDES_MODE_SGMII;
    u16                    delay=0;
    BOOL                   oos_fix = FALSE;

#if defined(VTSS_FEATURE_PORT_PCS_CONF)
    if (if_type == VTSS_PORT_INTERFACE_SGMII || if_type == VTSS_PORT_INTERFACE_QSGMII) {
        if ((conf->pcs == VTSS_PORT_PCS_ENABLE) || (conf->pcs == VTSS_PORT_PCS_DISABLE)) {
            return l26_port_oos_fix(vtss_state, port, conf->pcs);
        }
        if (conf->pcs == VTSS_PORT_PCS_IGNORE) {
            oos_fix = TRUE;
        }
    } else {
        conf->pcs = VTSS_PORT_PCS_NORMAL;
    }
#endif
    VTSS_I("port_no:%d (port:%d) if:%s, spd:%d/%s, shutdown:%d",
           port_no, port, vtss_port_if_txt(conf->if_type),
           conf->speed, conf->fdx ? "FDX" : "HDX", conf->power_down);

    /* Default frame gaps */
    gaps.hdx_gap_2 = 9;
    gaps.fdx_gap = 0;

    /* Verify speed and interface type */
    switch (speed) {
    case VTSS_SPEED_10M:
        link_speed = 3;
        gaps.hdx_gap_1 = L26_HDX_GAP_1_10M;
        break;
    case VTSS_SPEED_100M:
        link_speed = 2;
        gaps.hdx_gap_1 = L26_HDX_GAP_1_100M;
        break;
    case VTSS_SPEED_1G:
        link_speed = 1;
        gaps.hdx_gap_1 = L26_HDX_GAP_1_1G;
        gaps.fdx_gap = 5;
        break;
    case VTSS_SPEED_2500M:
        link_speed = 1;
        gaps.hdx_gap_1 = L26_HDX_GAP_1_2500M;
        gaps.fdx_gap = 5;
        break;
    default:
        VTSS_E("illegal speed, port %u", port);
        return VTSS_RC_ERROR;
    }

    /* FDX gap */
    if (gaps.fdx_gap == 0) {
        if (port < 10) {
            gaps.fdx_gap = 16;
        } else if (port < 12 && vtss_state->init_conf.mux_mode != VTSS_PORT_MUX_MODE_2)  {
            gaps.fdx_gap = (fdx ? 16 : 14);
        } else {
            gaps.fdx_gap = 15;
        }
    }

    switch (if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        disable = 1;
        break;
    case VTSS_PORT_INTERFACE_INTERNAL:
    case VTSS_PORT_INTERFACE_SGMII:
        sgmii = 1;
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        sgmii = 1;
        if ((port % 4) == 0) {
            // BZ23738
            for (u32 p = port + 1; p <= port + 3; ++p)
                L26_WRM_CLR(VTSS_DEV_PORT_MODE_CLOCK_CFG(VTSS_TO_DEV(p)), VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_TX_RST);
        }
        vtss_state->port.serdes_mode[port_no] = VTSS_SERDES_MODE_QSGMII; // The serdes mode is already configured
        break;
    case VTSS_PORT_INTERFACE_100FX:
        if (speed != VTSS_SPEED_100M) {
            VTSS_E("illegal speed, port %u", port);
            return VTSS_RC_ERROR;
        }
        mode = VTSS_SERDES_MODE_100FX;
        if_100fx = 1;
        break;
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        if (speed != VTSS_SPEED_10M && speed != VTSS_SPEED_100M && speed != VTSS_SPEED_1G) {
            VTSS_E("SFP_CU, illegal speed, port %u", port);
            return VTSS_RC_ERROR;
        }
        if (vtss_state->port.serdes_mode[port_no] != VTSS_SERDES_MODE_QSGMII) {
            mode = VTSS_SERDES_MODE_1000BaseX;
        }
        sgmii = 1;
        break;
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_SERDES:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_2500M) {
            VTSS_E("illegal speed, port %u", port);
            return VTSS_RC_ERROR;
        }
        mode = (speed == VTSS_SPEED_2500M ? VTSS_SERDES_MODE_2G5 : VTSS_SERDES_MODE_1000BaseX);
        break;
    case VTSS_PORT_INTERFACE_LOOPBACK:
        if (port < 12) {
            sgmii = 1;
        } else {
            mode = VTSS_SERDES_MODE_1000BaseX;
        }
        break;
    default:
        VTSS_E("illegal interface, port %u", port);
        return VTSS_RC_ERROR;
    }
    /* (re-)configure the Serdes macros to 100FX / 1000BaseX / 2500 */
    if (mode != vtss_state->port.serdes_mode[port_no] && mode != VTSS_SERDES_MODE_SGMII) {

        VTSS_RC(serdes_instance_get(vtss_state, port, &instance, &serdes6g));
        if (mode == VTSS_SERDES_MODE_2G5 && !serdes6g) {
            VTSS_E("illegal serdes settings, port %u", port);
            return VTSS_RC_ERROR;
        }
        if (serdes6g) {
            VTSS_RC(l26_sd6g_read(vtss_state, 1<<instance));
            VTSS_MSLEEP(10);
            VTSS_RC(l26_sd6g_cfg(vtss_state, port_no, mode, 1<<instance));
            VTSS_RC(l26_sd6g_write(vtss_state, 1<<instance, L26_SERDES_WAIT));
        } else {
            VTSS_RC(l26_sd1g_read(vtss_state, 1<<instance));
            VTSS_MSLEEP(10);
            VTSS_RC(l26_sd1g_cfg(vtss_state, port_no, mode, 1<<instance));
            VTSS_RC(l26_sd1g_write(vtss_state, 1<<instance, L26_SERDES_WAIT));
        }
        VTSS_MSLEEP(1);
        vtss_state->port.serdes_mode[port_no] = mode;
    }
    /* Port disable and flush procedure: */
    /* 0.1: Reset the PCS */
    if (port > 9) {
        L26_WRM_SET(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt),
                    VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_RX_RST);
    }
    /* 1: Disable MAC frame reception */
    L26_WRM_CLR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_ENA_CFG(tgt),
                VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA);

    /* 2: Disable traffic being sent to or from switch port */
    L26_WRM_CLR(VTSS_SYS_SYSTEM_SWITCH_PORT_MODE(port),
                VTSS_F_SYS_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);

    /* 3: Disable dequeuing from the egress queues *\/ */
    L26_WRM_SET(VTSS_SYS_SYSTEM_PORT_MODE(port),
                VTSS_F_SYS_SYSTEM_PORT_MODE_DEQUEUE_DIS);

    /* 4: Wait a worst case time 8ms (jumbo/10Mbit) *\/ */
    VTSS_MSLEEP(8);

    /* 5: Disable HDX backpressure (Bugzilla 3203) */
    L26_WRM_CLR(VTSS_SYS_SYSTEM_FRONT_PORT_MODE(port),
                VTSS_F_SYS_SYSTEM_FRONT_PORT_MODE_HDX_MODE);

    /* 6: Flush the queues accociated with the port */
    L26_WRM_SET(VTSS_REW_PORT_PORT_CFG(port),
                VTSS_F_REW_PORT_PORT_CFG_FLUSH_ENA);

    /* 7: Enable dequeuing from the egress queues */
    L26_WRM_CLR(VTSS_SYS_SYSTEM_PORT_MODE(port),
                VTSS_F_SYS_SYSTEM_PORT_MODE_DEQUEUE_DIS);

    /* 9: Reset the clock */
    if (port > 9) {
        value =
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_RX_RST |
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_MAC_TX_RST |
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_MAC_RX_RST |
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PORT_RST;
        L26_WR(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt), value);
    } else {
        value =
            VTSS_F_DEV_GMII_PORT_MODE_CLOCK_CFG_MAC_TX_RST |
            VTSS_F_DEV_GMII_PORT_MODE_CLOCK_CFG_MAC_RX_RST |
            VTSS_F_DEV_GMII_PORT_MODE_CLOCK_CFG_PORT_RST;
        L26_WR(VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG(tgt), value);
    }


    do { /* 8: Wait until flushing is complete */
        L26_RD(VTSS_SYS_SYSTEM_SW_STATUS(port), &value);
        VTSS_MSLEEP(1);
        delay++;
        if (delay == 2000) {
            VTSS_E("Flush timeout port %u, delay:%d\n",port, delay);
            break;
        }
    } while(value & VTSS_M_SYS_SYSTEM_SW_STATUS_EQ_AVAIL);
    VTSS_I("port:%d, Flush delay:%d", port, delay);


    /* 10: Clear flushing */
    L26_WRM_CLR(VTSS_REW_PORT_PORT_CFG(port), VTSS_F_REW_PORT_PORT_CFG_FLUSH_ENA);

    /* The port is disabled and flushed, now set up the port in the new operating mode */

    /* Bugzilla 4388: disabling frame aging when in HDX */
    L26_WRM(VTSS_REW_PORT_PORT_CFG(port), (fdx ? 0 : VTSS_F_REW_PORT_PORT_CFG_AGE_DIS), VTSS_F_REW_PORT_PORT_CFG_AGE_DIS);

    /* GIG/FDX mode */
    if (fdx && ((speed == VTSS_SPEED_1G) || speed == VTSS_SPEED_2500M)) {
        value = VTSS_F_DEV_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA | VTSS_F_DEV_MAC_CFG_STATUS_MAC_MODE_CFG_GIGA_MODE_ENA;
    } else if (fdx) {
        value = VTSS_F_DEV_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA;
    } else {
        L26_WRM(VTSS_SYS_SYSTEM_FRONT_PORT_MODE(port), 1, VTSS_F_SYS_SYSTEM_FRONT_PORT_MODE_HDX_MODE);
        value = 0;
    }
    /* Set GIG/FDX mode */
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_MODE_CFG(tgt), value);

    /* Configure frame length check (from ethertype / length field) */
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(tgt),
           conf->frame_length_chk ? VTSS_F_DEV_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA : 0);

    /* Set MAC IFG Gaps */
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_IFG_CFG(tgt),
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG(gaps.fdx_gap) |
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1(gaps.hdx_gap_1) |
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2(gaps.hdx_gap_2));

    /* Set MAC HDX Late collision and assert seed load. Seed load must be de-asserted after min 1us */
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_HDX_CFG(tgt),
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS(60) | // The number 60 comes from mot/yl who have done testing with this
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_HDX_CFG_SEED_LOAD);
    VTSS_NSLEEP(1000);
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_HDX_CFG(tgt),
           (conf->exc_col_cont ? VTSS_F_DEV_MAC_CFG_STATUS_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA : 0) |
           VTSS_F_DEV_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS(60)); // The number 60 comes from mot/yl who have done testing with this

    /* PSC settings for 100fx/SGMII/SERDES */
    if (port > 9) {
        if (if_100fx) {
            /* VTSS_MSLEEP(1);            */
            value = (disable ? 0 : VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA) |
                (conf->sd_internal    ? 0 : VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL) |
                (conf->sd_active_high ? 1<<25 : 0)  |  /* VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_SD_POL [DBG] */
                (conf->sd_enable      ? VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA : 0);

            /* 100FX PCS */
            L26_WRM(VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),value,
                    VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA |
                    VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL |
                    (1<<25) | /* VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_POL [DBG] */
                    VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA)
        } else {
            /* Disable 100FX */
            L26_WRM(VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),0,
                    VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA)

            /* Choose SGMII or Serdes PCS mode */
            L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_MODE_CFG(tgt),
                   (sgmii ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_SGMII_MODE_ENA : 0));

            if (sgmii) {
                L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                       VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA); /* Set whole register */
            } else {
                L26_WRM_CLR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                            VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA); /* Clear specific bit only */
            }

            L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
                  (conf->sd_active_high ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_POL : 0) |
                   (conf->sd_enable ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA : 0) |
                   (conf->sd_internal ? 0 : VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_SEL));

            /* Enable/disable PCS */
            if (port > 11) {
                if (disable && !oos_fix) {
                    L26_WRM_CLR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
                }
            }

            if (conf->if_type == VTSS_PORT_INTERFACE_SGMII) {
                L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt), 0);
            } else if (conf->if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
                /* Complete SGMII aneg */
                value = 0x0001;

                L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                       VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(value)    |
                       VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA        |
                       VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA              |
                       VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT);

                /* Clear the sticky bits */
                L26_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);
                L26_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), value);
            }
            //Update vtss_state database accordingly
            l26_port_clause_37_control_get(vtss_state,port_no,&(vtss_state->port.clause_37[port_no]));
        }
    }

    /* Disable loopback */
    if (port < 10) {
        L26_WRM_CLR(VTSS_DEV_GMII_PORT_MODE_PORT_MISC(tgt), VTSS_F_DEV_GMII_PORT_MODE_PORT_MISC_GMII_LOOP_ENA);
    } else if (port > 9 && port < 12) {
        L26_WRM_CLR(VTSS_DEV_PORT_MODE_PORT_MISC(tgt), VTSS_F_DEV_PORT_MODE_PORT_MISC_DEV_LOOP_ENA);
    } else {
        L26_WRM_CLR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LB_CFG(tgt), VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA);
    }
    /* Enable loopback if requested */
    if (conf->if_type == VTSS_PORT_INTERFACE_LOOPBACK || conf->loop == VTSS_PORT_LOOP_PCS_HOST) {
        if (conf->loop == VTSS_PORT_LOOP_PCS_HOST && port < 12) {
            VTSS_E("PCS loopback not supported for port:%u\n",port_no);
            return VTSS_RC_ERROR;
        }
        if (port < 10) {
            L26_WRM_SET(VTSS_DEV_GMII_PORT_MODE_PORT_MISC(tgt), VTSS_F_DEV_GMII_PORT_MODE_PORT_MISC_GMII_LOOP_ENA);
        } else if (port > 9 && port < 12) {
            L26_WRM_SET(VTSS_DEV_PORT_MODE_PORT_MISC(tgt), VTSS_F_DEV_PORT_MODE_PORT_MISC_DEV_LOOP_ENA);
        } else {
            L26_WRM_SET(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LB_CFG(tgt), VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA);
        }
    }

    /* Set Max Length and maximum tags allowed */
    L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_MAXLEN_CFG(tgt), conf->max_frame_length);
    VTSS_RC(vtss_l26_port_max_tags_set(vtss_state, port_no));

    if (!disable) {
        /* Configure flow control */
        if (l26_port_fc_setup(vtss_state, port, conf) != VTSS_RC_OK) {
            VTSS_E("Flow control setup issue, port:%u\n", port_no);
            return VTSS_RC_ERROR;
        }

        /* Update policer flow control configuration */
        VTSS_RC(vtss_l26_port_policer_fc_set(vtss_state, port_no, port));

        /* Enable MAC module */
        L26_WR(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_ENA_CFG(tgt),
               VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA |
               VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA);

        /* Take MAC, Port, Phy (intern) and PCS (SGMII/Serdes) clock out of reset */
        if (port > 9) {
            if (oos_fix) {
                L26_WR(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt),
                       VTSS_F_DEV_PORT_MODE_CLOCK_CFG_LINK_SPEED(link_speed) |
                       VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_RX_RST);
            } else {
                L26_WR(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt), VTSS_F_DEV_PORT_MODE_CLOCK_CFG_LINK_SPEED(link_speed));
            }
        } else {
            L26_WR(VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG(tgt), 0);
        }

        VTSS_I("Port:%d", port_no);

        /* Core: Enable port for frame transfer */
        L26_WRM_SET(VTSS_SYS_SYSTEM_SWITCH_PORT_MODE(port),
                    VTSS_F_SYS_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);

        /* Enable flowcontrol - must be done after flushing */
        if (conf->flow_control.generate) {
            L26_WRM_SET(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_CFG(VTSS_TO_DEV(port)), VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_TX_FC_ENA);
        }

        /* Enable PCS */
        if (port > 11 || (port > 9 && (vtss_state->init_conf.mux_mode == VTSS_PORT_MUX_MODE_2))) {
            if (conf->pcs != VTSS_PORT_PCS_IGNORE) {
                L26_WRM_SET(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
            }
        }
    }
    return VTSS_RC_OK;
}


/* Get status of the VAUI or 100FX ports.  Internal/SGMII/Serdes ports are covered elsewhere */
static vtss_rc l26_port_status_get(vtss_state_t *vtss_state,
                                   const vtss_port_no_t  port_no,
                                   vtss_port_status_t    *const status)
{
    vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
    u32              tgt = VTSS_TO_DEV(vtss_state->port.map[port_no].chip_port);
    u32              value;

    if (conf->power_down) {
        VTSS_MEMSET(status, 0, sizeof(*status));
        return VTSS_RC_OK;
    }

    if (conf->if_type == VTSS_PORT_INTERFACE_100FX) {
        /* Get the PCS status  */
        L26_RD(VTSS_DEV_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), &value);

        /* Link has been down if the are any error stickies */
        status->link_down = L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY, value) ||
                            L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY, value) ||
                            L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY, value) ||
                            L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY, value);

        if (status->link_down) {
            L26_WR(VTSS_DEV_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), 0xFFFF);
            VTSS_MSLEEP(1);
            L26_RD(VTSS_DEV_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), &value);
        }
        /* Link=1 if sync status=1 and no error stickies after a clear */
        status->link = L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_STATUS, value) &&
                     (!L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY, value) &&
                      !L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY, value) &&
                      !L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY, value) &&
                      !L26_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY, value));

        status->speed = VTSS_SPEED_100M;

        // 100FX SFP can be auto detected and then the aneg status must be updated to the current flow control .
        status->aneg.obey_pause = conf->flow_control.obey;
        status->aneg.generate_pause = conf->flow_control.generate;

    }  else if (conf->if_type == VTSS_PORT_INTERFACE_VAUI) {
        /* Get the PCS status */
        L26_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(tgt), &value);
        status->link = L26_BF(DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS, value) &&
                       L26_BF(DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS, value);

        L26_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);

        status->link_down = L26_BF(DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY, value);

        if (status->link_down) {
            /* The link has been down. Clear the sticky bit */
            L26_WRM_SET(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt),
                        VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY |
                        VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_OUT_OF_SYNC_STICKY);
        }
        status->speed = VTSS_SPEED_2500M;
    }  else if (conf->if_type == VTSS_PORT_INTERFACE_NO_CONNECTION) {
        status->link = 0;
        status->link_down = 0;
    } else {
        // VTSS_E("Status not supported for port: %u",port_no);
        return VTSS_RC_ERROR;
    }
    status->fdx = 1;
    return VTSS_RC_OK;
}

/* Read a counter and return the value */
static vtss_rc l26_port_counter(vtss_state_t *vtss_state,
                                u32 *cnt_addr, u32 port, vtss_chip_counter_t *counter, BOOL clear)
{
    u32 value, addr;

    addr = *cnt_addr;
    *cnt_addr = (addr + 1); /* Next counter */
    if (addr >= 0xC00) {
        addr += 18*port; /* Drop cnt */
    } else if (addr >= 0x800) {
        addr += 31*port; /* Tx cnt */
    } else {
        addr += 43*port; /* Rx cnt */
    }

    L26_RD(VTSS_SYS_STAT_CNT(addr), &value);
    if (clear) {
        /* Clear counter */
        counter->value = 0;
    } else {
        /* Accumulate counter */
        if (value >= counter->prev) {
            /* Not wrapped */
            counter->value += (value - counter->prev);
        } else {
            /* Wrapped */
            counter->value += (0xffffffff - counter->prev);
            counter->value += (value + 1);
        }
    }
    counter->prev = value;
    return VTSS_RC_OK;
}

/* Read the chip counters and store them in a different counter groups */
static vtss_rc l26_port_counters_read(vtss_state_t *vtss_state,
                                      u32                          port,
                                      vtss_port_luton26_counters_t *c,
                                      vtss_port_counters_t *const  counters,
                                      BOOL                         clear)
{
    u32                                i, base, *p = &base;
    vtss_port_rmon_counters_t          *rmon;
    vtss_port_if_group_counters_t      *if_group;
    vtss_port_ethernet_like_counters_t *elike;
    vtss_port_proprietary_counters_t   *prop;

    /* 32-bit Rx chip counters */
    base = 0x000;
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_octets, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_unicast, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_multicast, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_broadcast, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_shorts, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_fragments, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_jabbers, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_crc_align_errors, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_64, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_65_127, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_128_255, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_256_511, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_512_1023, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_1024_1526, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_1527_max, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_pause, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_control, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_longs, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_classified_drops, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_red_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_green_class[i], clear));

    /* 32-bit Drop chip counters */
    base = 0xC00;
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->dr_local, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->dr_tail, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(l26_port_counter(vtss_state, p, port, &c->dr_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(l26_port_counter(vtss_state, p, port, &c->dr_green_class[i], clear));

    /* 32-bit Tx chip counters */
    base = 0x800;
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_octets, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_unicast, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_multicast, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_broadcast, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_collision, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_drops, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_pause, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_64, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_65_127, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_128_255, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_256_511, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_512_1023, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_1024_1526, clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_1527_max, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_green_class[i], clear));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_aging, clear));

    if (counters == NULL) {
        return VTSS_RC_OK;
    }

    /* Calculate API counters based on chip counters */
    rmon = &counters->rmon;
    if_group = &counters->if_group;
    elike = &counters->ethernet_like;
    prop = &counters->prop;

    /* Proprietary counters */
    for (i = 0; i < VTSS_PRIOS; i++) {
        prop->rx_prio[i] = c->rx_red_class[i].value + c->rx_yellow_class[i].value + c->rx_green_class[i].value;
        prop->tx_prio[i] = c->tx_yellow_class[i].value + c->tx_green_class[i].value;
    }

    /* RMON Rx counters */
    rmon->rx_etherStatsDropEvents = c->rx_classified_drops.value + c->dr_tail.value;
    for (i = 0; i < VTSS_PRIOS; i++) {
        rmon->rx_etherStatsDropEvents += (c->dr_yellow_class[i].value + c->dr_green_class[i].value);
    }

    rmon->rx_etherStatsOctets = c->rx_octets.value;
    rmon->rx_etherStatsPkts =
        (c->rx_shorts.value + c->rx_fragments.value + c->rx_jabbers.value + c->rx_longs.value +
         c->rx_64.value + c->rx_65_127.value + c->rx_128_255.value + c->rx_256_511.value +
         c->rx_512_1023.value + c->rx_1024_1526.value + c->rx_1527_max.value);
    rmon->rx_etherStatsBroadcastPkts = c->rx_broadcast.value;
    rmon->rx_etherStatsMulticastPkts = c->rx_multicast.value;
    rmon->rx_etherStatsCRCAlignErrors = c->rx_crc_align_errors.value;
    rmon->rx_etherStatsUndersizePkts = c->rx_shorts.value;
    rmon->rx_etherStatsOversizePkts = c->rx_longs.value;
    rmon->rx_etherStatsFragments = c->rx_fragments.value;
    rmon->rx_etherStatsJabbers = c->rx_jabbers.value;
    rmon->rx_etherStatsPkts64Octets = c->rx_64.value;
    rmon->rx_etherStatsPkts65to127Octets = c->rx_65_127.value;
    rmon->rx_etherStatsPkts128to255Octets = c->rx_128_255.value;
    rmon->rx_etherStatsPkts256to511Octets = c->rx_256_511.value;
    rmon->rx_etherStatsPkts512to1023Octets = c->rx_512_1023.value;
    rmon->rx_etherStatsPkts1024to1518Octets = c->rx_1024_1526.value;
    rmon->rx_etherStatsPkts1519toMaxOctets = c->rx_1527_max.value;

    /* RMON Tx counters */
    rmon->tx_etherStatsDropEvents = (c->tx_drops.value + c->tx_aging.value);
    rmon->tx_etherStatsOctets = c->tx_octets.value;
    rmon->tx_etherStatsPkts = c->tx_64.value + c->tx_65_127.value + c->tx_128_255.value + c->tx_256_511.value +
                              c->tx_512_1023.value + c->tx_1024_1526.value + c->tx_1527_max.value;
    rmon->tx_etherStatsBroadcastPkts = c->tx_broadcast.value;
    rmon->tx_etherStatsMulticastPkts = c->tx_multicast.value;
    rmon->tx_etherStatsCollisions = c->tx_collision.value;
    rmon->tx_etherStatsPkts64Octets = c->tx_64.value;
    rmon->tx_etherStatsPkts65to127Octets = c->tx_65_127.value;
    rmon->tx_etherStatsPkts128to255Octets = c->tx_128_255.value;
    rmon->tx_etherStatsPkts256to511Octets = c->tx_256_511.value;
    rmon->tx_etherStatsPkts512to1023Octets = c->tx_512_1023.value;
    rmon->tx_etherStatsPkts1024to1518Octets = c->tx_1024_1526.value;
    rmon->tx_etherStatsPkts1519toMaxOctets = c->tx_1527_max.value;

    /* Interfaces Group Rx counters */
    if_group->ifInOctets = c->rx_octets.value;
    if_group->ifInUcastPkts = c->rx_unicast.value;
    if_group->ifInMulticastPkts = c->rx_multicast.value;
    if_group->ifInBroadcastPkts = c->rx_broadcast.value;
    if_group->ifInNUcastPkts = c->rx_multicast.value + c->rx_broadcast.value;
    if_group->ifInDiscards = rmon->rx_etherStatsDropEvents;
    if_group->ifInErrors = c->rx_crc_align_errors.value + c->rx_shorts.value + c->rx_fragments.value +
                           c->rx_jabbers.value + c->rx_longs.value;

    /* Interfaces Group Tx counters */
    if_group->ifOutOctets = c->tx_octets.value;
    if_group->ifOutUcastPkts = c->tx_unicast.value;
    if_group->ifOutMulticastPkts = c->tx_multicast.value;
    if_group->ifOutBroadcastPkts = c->tx_broadcast.value;
    if_group->ifOutNUcastPkts = c->tx_multicast.value + c->tx_broadcast.value;
    if_group->ifOutDiscards = rmon->tx_etherStatsDropEvents;
    if_group->ifOutErrors = c->tx_drops.value + c->tx_aging.value;

    /* Ethernet-like counters */
    elike->dot3InPauseFrames = c->rx_pause.value + c->rx_control.value;
    elike->dot3OutPauseFrames = c->tx_pause.value;

    /* Bridge counters */
    counters->bridge.dot1dTpPortInDiscards = c->dr_local.value;
    for (i = 0; i < VTSS_PRIOS; i++) {
        counters->bridge.dot1dTpPortInDiscards += c->rx_red_class[i].value;
    }

#if defined(VTSS_ARCH_CARACAL)
    /* EVC counters */
    {
        vtss_port_evc_counters_t *evc = &counters->evc;

        for (i = 0; i < VTSS_PRIOS; i++) {
            evc->rx_green[i] = c->rx_green_class[i].value;
            evc->rx_yellow[i] = c->rx_yellow_class[i].value;
            evc->rx_red[i] = c->rx_red_class[i].value;
            evc->rx_green_discard[i] = c->dr_green_class[i].value;
            evc->rx_yellow_discard[i] = c->dr_yellow_class[i].value;
            evc->tx_green[i] = c->tx_green_class[i].value;
            evc->tx_yellow[i] = c->tx_yellow_class[i].value;
        }
    }
#endif /* VTSS_ARCH_CARACAL */

    return VTSS_RC_OK;
}

/* Get Rx and Tx packets */
static vtss_rc l26_port_basic_counters_get(vtss_state_t *vtss_state,
                                           const vtss_port_no_t port_no,
                                           vtss_basic_counters_t *const counters)
{
    u32                          base, *p = &base, port = VTSS_CHIP_PORT(port_no);
    vtss_port_luton26_counters_t *c = &vtss_state->port.counters[port_no].counter.luton26;

    /* Rx Counters */
    base = 0x008; /* rx_64 */
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_64, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_65_127, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_128_255, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_256_511, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_512_1023, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_1024_1526, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->rx_1527_max, 0));

    /* Tx Counters */
    base = 0x807; /* tx_64 */
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_64, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_65_127, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_128_255, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_256_511, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_512_1023, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_1024_1526, 0));
    VTSS_RC(l26_port_counter(vtss_state, p, port, &c->tx_1527_max, 0));

    /* Rx frames */
    counters->rx_frames = (c->rx_64.value + c->rx_65_127.value + c->rx_128_255.value + c->rx_256_511.value +
                           c->rx_512_1023.value + c->rx_1024_1526.value + c->rx_1527_max.value);

    /* Tx frames */
    counters->tx_frames = (c->tx_64.value + c->tx_65_127.value + c->tx_128_255.value + c->tx_256_511.value +
                           c->tx_512_1023.value + c->tx_1024_1526.value + c->tx_1527_max.value);
    return VTSS_RC_OK;
}


static vtss_rc l26_port_counters_cmd(vtss_state_t *vtss_state,
                                     const vtss_port_no_t        port_no,
                                     vtss_port_counters_t *const counters,
                                     BOOL                        clear)
{
    return l26_port_counters_read(vtss_state,
                                  VTSS_CHIP_PORT(port_no),
                                  &vtss_state->port.counters[port_no].counter.luton26,
                                  counters,
                                  clear);
}

static vtss_rc l26_port_counters_update(vtss_state_t *vtss_state,
                                        const vtss_port_no_t port_no)
{
    return l26_port_counters_cmd(vtss_state, port_no, NULL, 0);
}

static vtss_rc l26_port_counters_clear(vtss_state_t *vtss_state,
                                       const vtss_port_no_t port_no)
{
    return l26_port_counters_cmd(vtss_state, port_no, NULL, 1);
}

static vtss_rc l26_port_counters_get(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no,
                                     vtss_port_counters_t *const counters)
{
    VTSS_MEMSET(counters, 0, sizeof(*counters));
    return l26_port_counters_cmd(vtss_state, port_no, counters, 0);
}

/* Set forwarding state (already done by vtss_update_masks) */
static vtss_rc l26_port_forward_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc l26_port_test_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_serdes_mode_t mode = vtss_state->port.serdes_mode[port_no];
    u32                addr, instance, port = VTSS_CHIP_PORT(port_no);
    BOOL               serdes6g;
    vtss_port_lb_t     lb = vtss_state->port.test_conf[port_no].loopback;
    vtss_port_conf_t   *conf = &vtss_state->port.conf[port_no];
    u32                tgt = VTSS_TO_DEV(port);


    VTSS_RC(serdes_instance_get(vtss_state, port, &instance, &serdes6g));
    addr = (1 << instance);
    if (serdes6g) {
        VTSS_RC(l26_sd6g_read(vtss_state, addr));
        VTSS_MSLEEP(10);
        VTSS_RC(l26_sd6g_cfg(vtss_state, port_no, mode, addr));
        VTSS_RC(l26_sd6g_write(vtss_state, addr, L26_SERDES_WAIT));
    } else {
        VTSS_RC(l26_sd1g_read(vtss_state, addr));
        VTSS_MSLEEP(10);
        VTSS_RC(l26_sd1g_cfg(vtss_state, port_no, mode, addr));
        VTSS_RC(l26_sd1g_write(vtss_state, addr, L26_SERDES_WAIT));
    }
    // Disable signal detect during loopback
    if (lb == VTSS_PORT_LB_DISABLED) {
        L26_WRM(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
                (conf->sd_enable ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA : 0),
                (VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA));
        L26_WRM(VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
               (conf->sd_enable ? VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA : 0),
                VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA);
    } else {
        L26_WRM(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
                0,
                (VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA));
        L26_WRM(VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                0,
                VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA);
    }

    return VTSS_RC_OK;
}

static vtss_rc l26_buf_conf_set(vtss_state_t *vtss_state)
{
    u32 port_no, port, q, dp, i = 0;
    u32 buf_q_rsrv_i, buf_q_rsrv_e, ref_q_rsrv_i, ref_q_rsrv_e, buf_prio_shr_i[8], buf_prio_shr_e[8], ref_prio_shr_i[8], ref_prio_shr_e[8];
    u32 buf_p_rsrv_i, buf_p_rsrv_e, ref_p_rsrv_i, ref_p_rsrv_e, buf_col_shr_i, buf_col_shr_e, ref_col_shr_i, ref_col_shr_e;
    u32 prio_mem_rsrv, prio_ref_rsrv, guaranteed, q_rsrv_mask, prio_mem, prio_ref, oversubscription_factor;

    /*  SYS::RES_CFG : 1024 watermarks for 512 kB shared buffer, unit is 48 byte */
    /*  Is divided into 4 resource consumptions, ingress and egress memory (BUF) and ingress and egress frame reference (REF) blocks */

    /* BUF_xxx_Ingress starts @ offset 0   */
    /* REF_xxx_Ingress starts @ offset 256 */
    /* BUF_xxx_Egress  starts @ offset 512 */
    /* REF_xxx_Egress  starts @ offset 768 */
    /* xxx = q_rsrv, prio_shr, p_rsrv, col_shr */

    /* Queue reserved (q_rsrv) : starts @ offset 0 within in each BUF and REF */
    /* Prio shared (prio_shr)  : starts @ offset 216 within in each BUF and REF */
    /* Port reserved (p_rsrv)  : starts @ offset 224 within in each BUF and REF */
    /* Colour shared (col_shr) : starts @ offset 254 within in each BUF and REF */

    /* Buffer values are in BYTES */
    buf_q_rsrv_i = 0;     /* Space per queue is not  guaranteed                  */
    buf_q_rsrv_e = 1519;  /* Guarantees all priorities to non-congested traffic stream */
    buf_p_rsrv_i = 512;   /* Guarantees reception of 1 MTUs per ingress port      */
    buf_p_rsrv_e = 4000;  /* Memory shared between priorities per egress port       */
    buf_col_shr_i = L26_BUFFER_MEMORY;    /* Coloring - disabled  */
    buf_col_shr_e = L26_BUFFER_MEMORY;    /* Coloring - disabled  */

    /* Reference values in NUMBER of FRAMES */
    ref_q_rsrv_i = 10;    /* Pending frames per ingress queue              */
    ref_q_rsrv_e = 4;     /* Frames can be pending to each egress queue    */
    ref_p_rsrv_i = 10;    /* Pending frames per ingress port               */
    ref_p_rsrv_e = 10;    /* Frames can be pending for each egress port    */
    ref_col_shr_i = L26_BUFFER_REFERENCE; /* Coloring - disabled           */
    ref_col_shr_e = L26_BUFFER_REFERENCE; /* Coloring - disabled           */

    prio_mem_rsrv = 2000;  /* In the shared area, each priority is cut off 2kB before the others */
    prio_ref_rsrv = 50;    /* And 50 references ... */

    /* The number of supported queues is given through the state structure                           */
    /* The supported queues (lowest to higest) are givin reserved buffer space as specified above.   */
    /* Frames in remaining queues (if any) are not getting any reserved space - but are allowed in the system.*/
    q_rsrv_mask = 0xff >> (8 - vtss_state->qos.conf.prios);

    /* The memory is oversubsrcribed by this factor (factor 1 = 100) */
    if (vtss_state->port_count > 12) {
        oversubscription_factor = 130;
    } else {
        oversubscription_factor = 100;
    }

    /* **************************************************  */
    /* BELOW, everything is calculated based on the above. */
    /* **************************************************  */

    /* Find the amount of guaranteeed space per port */
    guaranteed = buf_p_rsrv_i+buf_p_rsrv_e;
    for (q=0; q<VTSS_PRIOS; q++) {
        if (q_rsrv_mask & (1<<q))
            guaranteed+=(buf_q_rsrv_i+buf_q_rsrv_e);
    }
    prio_mem = (oversubscription_factor * L26_BUFFER_MEMORY)/100 - vtss_state->port_count*guaranteed;
    /* Find the amount of guaranteeed frame references */
    guaranteed = ref_p_rsrv_i+ref_p_rsrv_e;
    for (q=0; q<VTSS_PRIOS; q++) {
        if (q_rsrv_mask & (1<<q)) {
            guaranteed+=(ref_q_rsrv_i+ref_q_rsrv_e);
        }
    }
    prio_ref = L26_BUFFER_REFERENCE - vtss_state->port_count*guaranteed;

    for (q = VTSS_PRIOS-1; ; q--) {
        buf_prio_shr_i[q] = prio_mem;
        ref_prio_shr_i[q] = prio_ref;
        buf_prio_shr_e[q] = prio_mem;
        ref_prio_shr_e[q] = prio_ref;

        if (q_rsrv_mask & (1<<q)) {
            prio_mem -= prio_mem_rsrv;
            prio_ref -= prio_ref_rsrv;
        }
        if (q==0) break;
    }

    do { /* Reset default WM */
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(i), 0);
        i++;
    } while (i<1024);

    /* Configure reserved space for all QoS classes per port */
    for (port_no = 0; port_no <= vtss_state->port_count; port_no++) {
        if (port_no == vtss_state->port_count) {
            port = VTSS_CHIP_PORT_CPU;
        } else {
            port = VTSS_CHIP_PORT(port_no);
        }
        for (q = 0; q < VTSS_PRIOS; q++) {
            if (q_rsrv_mask&(1<<q)) {
                L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 0),   wm_enc(buf_q_rsrv_i / L26_BUFFER_CELL_SZ));
                L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 256), wm_enc(ref_q_rsrv_i));
                L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 512), wm_enc(buf_q_rsrv_e / L26_BUFFER_CELL_SZ));
                L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 768), wm_enc(ref_q_rsrv_e));
            }
        }
    }

    /* Configure shared space for all QoS classes */
    for (q = 0; q < VTSS_PRIOS; q++) {
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG((q + 216 + 0)),   wm_enc(buf_prio_shr_i[q] / L26_BUFFER_CELL_SZ));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG((q + 216 + 256)), wm_enc(ref_prio_shr_i[q]));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG((q + 216 + 512)), wm_enc(buf_prio_shr_e[q] / L26_BUFFER_CELL_SZ));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG((q + 216 + 768)), wm_enc(ref_prio_shr_e[q]));
    }

    /* Configure reserved space for all ports */
    for (port_no = 0; port_no <= vtss_state->port_count; port_no++) {
        if (port_no == vtss_state->port_count) {
            port = VTSS_CHIP_PORT_CPU;
        } else {
            port = VTSS_CHIP_PORT(port_no);
        }
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(port + 224 +   0), wm_enc(buf_p_rsrv_i / L26_BUFFER_CELL_SZ));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(port + 224 + 256), wm_enc(ref_p_rsrv_i));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(port + 224 + 512), wm_enc(buf_p_rsrv_e / L26_BUFFER_CELL_SZ));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(port + 224 + 768), wm_enc(ref_p_rsrv_e));
    }

    /* Configure shared space for both DP levels         */
    /* In this context dp:0 is yellow and dp:1 is green */
    for (dp = 0; dp < 2; dp++) {
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(dp + 254 +   0), wm_enc(buf_col_shr_i / L26_BUFFER_CELL_SZ));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(dp + 254 + 256), wm_enc(ref_col_shr_i));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(dp + 254 + 512), wm_enc(buf_col_shr_e / L26_BUFFER_CELL_SZ));
        L26_WR(VTSS_SYS_RES_CTRL_RES_CFG(dp + 254 + 768), wm_enc(ref_col_shr_e));
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SYNCE)
/* ================================================================= *
 *  SYNCE (Level 1 syncronization)
 * ================================================================= */

typedef enum
{
    SERDES_1G,
    SERDES_6G,
} serdes_t;

static vtss_rc synce_chip_port_to_serdes(vtss_target_type_t target,   vtss_port_mux_mode_t mux_mode,   i32 chip_port,   serdes_t *type,   u32 *instance)
{ /* This function is able to calculate the SERDES type and instance of all chip ports that can possible be a synce source */
    switch (target) {
        case VTSS_TARGET_SPARX_III_10:     /* VSC7424 */
        case VTSS_TARGET_SPARX_III_10_01:  /* VSC7424-01 */
            if (mux_mode != VTSS_PORT_MUX_MODE_2)   return VTSS_RC_ERROR;

            *type = SERDES_1G;
            if (chip_port == 24)     *instance = 0;
            else
            if (chip_port == 25)     *instance = 1;
            else                     return VTSS_RC_ERROR;
            break;
        case VTSS_TARGET_SPARX_III_18:  /* VSC7425 */
            if (mux_mode == VTSS_PORT_MUX_MODE_0) {
                *instance = 0;
                if (chip_port == 24)  *type = SERDES_1G;
                else
                if (chip_port == 25)  *type = SERDES_6G;
                else                  return VTSS_RC_ERROR;
            } else
            if (mux_mode == VTSS_PORT_MUX_MODE_2) {
                *type = SERDES_1G;
                switch (chip_port) {
                    case 20: case 21: case 22: case 23: *instance = 5 - (chip_port-20); break;
                    case 24: case 25: *instance = chip_port-24; break;
                    default:    return VTSS_RC_ERROR;
                }
            }
            else   return VTSS_RC_ERROR;
            break;
        case VTSS_TARGET_SPARX_III_24:  /* VSC7426 */
            return VTSS_RC_ERROR;
        case VTSS_TARGET_SPARX_III_26:  /* VSC7427 */
            if (mux_mode != VTSS_PORT_MUX_MODE_0)      return VTSS_RC_ERROR;
            *instance = 0;
            if (chip_port == 24)  *type = SERDES_1G;
            else
            if (chip_port == 25)  *type = SERDES_6G;
            else                  return VTSS_RC_ERROR;
            break;
        case VTSS_TARGET_CARACAL_LITE:  /* VSC7423 */
        case VTSS_TARGET_CARACAL_1:     /* VSC7428 */
            if (mux_mode != VTSS_PORT_MUX_MODE_1)      return VTSS_RC_ERROR;
            switch (chip_port) {
                case 14: case 15: *type = SERDES_1G; *instance = 7 - (chip_port-14); break;
                case 17: case 18: *type = SERDES_1G; *instance = 5 - (chip_port-17); break;
                case 19: *type = SERDES_6G; *instance = 2; break;
                case 20: case 21: case 22: case 23: *type = SERDES_1G; *instance = 3 - (chip_port-20); break;
                case 24: case 25: *type = SERDES_6G; *instance = 1 - (chip_port-24); break;
                default:    return VTSS_RC_ERROR;
            }
            break;
        case VTSS_TARGET_CARACAL_2:  /* VSC7429 */
            if (mux_mode == VTSS_PORT_MUX_MODE_0) {
                *instance = 0;
                if (chip_port == 24)  *type = SERDES_1G;
                else
                if (chip_port == 25)  *type = SERDES_6G;
                else                  return VTSS_RC_ERROR;
            } else
            if (mux_mode == VTSS_PORT_MUX_MODE_1) {
                switch (chip_port) {
                    case 14: case 15: *type = SERDES_1G; *instance = 7 - (chip_port-14); break;
                    case 16: *type = SERDES_6G; *instance = 3; break;
                    case 17: case 18: *type = SERDES_1G; *instance = 5 - (chip_port-17); break;
                    case 19: *type = SERDES_6G; *instance = 2; break;
                    case 20: case 21: case 22: case 23: *type = SERDES_1G; *instance = 3 - (chip_port-20); break;
                    case 24: case 25: *type = SERDES_6G; *instance = 1 - (chip_port-24); break;
                    default:    return VTSS_RC_ERROR;
                }
            } else
            if (mux_mode == VTSS_PORT_MUX_MODE_2) {
                *type = SERDES_1G;
                switch (chip_port) {
                    case 10: case 11: *instance = 7 - (chip_port-10); break;
                    case 20: case 21: case 22: case 23: *instance = 5 - (chip_port-20); break;
                    case 24: case 25: *instance = chip_port-24; break;
                    default:    return VTSS_RC_ERROR;
                }
            } else   return VTSS_RC_ERROR;
            break;
        default:
            return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_synce_supported(vtss_state_t *vtss_state)
{
    vtss_rc rc;

    switch (vtss_state->create.target) {
    case VTSS_TARGET_CARACAL_LITE:
    case VTSS_TARGET_CARACAL_1:
    case VTSS_TARGET_CARACAL_2:
    case VTSS_TARGET_SPARX_III_26:
        rc = VTSS_RC_OK;
        break;
    default:
        rc = VTSS_RC_ERROR;
        break;
    }
    return rc;
}

static vtss_rc l26_synce_clock_out_set(vtss_state_t *vtss_state, const u32 clk_port)
{
    u32 eth_cfg, div_mask, en_mask;

    VTSS_RC(l26_synce_supported(vtss_state));

    div_mask = (clk_port ? VTSS_M_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_B : VTSS_M_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_A);
    en_mask = (clk_port ? VTSS_F_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_B_ENA : VTSS_F_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_A_ENA);

    L26_RD(VTSS_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG, &eth_cfg);
    eth_cfg &= ~(div_mask | en_mask);      /* clear the related bits for this configuration */
    switch (vtss_state->synce.out_conf[clk_port].divider) {
        case VTSS_SYNCE_DIVIDER_1: div_mask = (clk_port ? VTSS_F_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_B(0) : VTSS_F_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_A(0)); break;
        case VTSS_SYNCE_DIVIDER_4: div_mask = (clk_port ? VTSS_F_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_B(2) : VTSS_F_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_A(2)); break;
        case VTSS_SYNCE_DIVIDER_5: div_mask = (clk_port ? VTSS_F_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_B(1) : VTSS_F_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_A(1)); break;
    }
    eth_cfg = eth_cfg | div_mask | (vtss_state->synce.out_conf[clk_port].enable ? en_mask : 0);
//printf("l26_synce_clock_out_set  eth_cfg %X\n", eth_cfg);
    L26_WR(VTSS_MACRO_CTRL_SYNC_ETH_CFG_SYNC_ETH_CFG,  eth_cfg);  /* Set the related bits defending on configuration */

    return VTSS_RC_OK;
}

static vtss_rc l26_synce_clock_in_set(vtss_state_t *vtss_state, const u32 clk_port)
{
    vtss_synce_clock_in_t *conf = &vtss_state->synce.in_conf[clk_port];
    serdes_t    serdes_type;
    u32         serdes_instance, common_cfg, sq_mask, en_mask, mask;
    i32         new_chip_port = VTSS_CHIP_PORT(conf->port_no);
    i32         old_chip_port = vtss_state->synce.old_port_no[clk_port];

    VTSS_RC(l26_synce_supported(vtss_state));

    if (!conf->enable || (new_chip_port != old_chip_port)) {
    /* Disable of this clock port or input port has changed for this clock output port - disable old input */
        if (VTSS_RC_OK == synce_chip_port_to_serdes(vtss_state->create.target,   vtss_state->init_conf.mux_mode,   old_chip_port,   &serdes_type,   &serdes_instance)) {
            mask = (1<<serdes_instance);
            if (serdes_type == SERDES_1G) {
                VTSS_RC(l26_sd1g_read(vtss_state, mask)); /* Readback the 1G common config register */
                L26_RD(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, &common_cfg);
                common_cfg &= ~(clk_port ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_RECO_SEL_B :
                                VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_RECO_SEL_A);
//printf("l26_synce_clock_in_set disable 1G   instance %u  common_cfg %X\n", serdes_instance, common_cfg);
                L26_WR(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, common_cfg);   /* Clear the recovered clock enable */
                VTSS_RC(l26_sd1g_write(vtss_state, mask, 0));
            }
            if (serdes_type == SERDES_6G) {
                VTSS_RC(l26_sd6g_read(vtss_state, mask));
                L26_RD(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, &common_cfg);
                common_cfg &= ~(clk_port ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_RECO_SEL_B :
                                VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_RECO_SEL_A);
//printf("l26_synce_clock_in_set disable 6G   instance %u  common_cfg %X\n", serdes_instance, common_cfg);
                L26_WR(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, common_cfg);   /* Clear the recovered clock enable */
                VTSS_RC(l26_sd6g_write(vtss_state, mask, 0));
            }
        }
    }

    if (conf->enable) {
    /* Enable input clock configuration - now configuring the new (or maybe the same) input port */
        if (VTSS_RC_OK == synce_chip_port_to_serdes(vtss_state->create.target,   vtss_state->init_conf.mux_mode,   new_chip_port,   &serdes_type,   &serdes_instance)) {
            mask = (1<<serdes_instance);
            if (serdes_type == SERDES_1G) {
                sq_mask = (clk_port ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_B_ENA :
                           VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_A_ENA);
                en_mask = (clk_port ? VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_RECO_SEL_B :
                           VTSS_F_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_RECO_SEL_A);
                VTSS_RC(l26_sd1g_read(vtss_state, mask)); /* Readback the 1G common config register */
                L26_RD(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, &common_cfg);
                common_cfg &= ~(sq_mask | en_mask);      /* clear the related bits for this configuration */
                common_cfg |= (conf->squelsh ? sq_mask : 0) | en_mask;
//printf("l26_synce_clock_in_set enable 1G   instance %u  common_cfg %X\n", serdes_instance, common_cfg);
                L26_WR(VTSS_MACRO_CTRL_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, common_cfg);   /* Set the related bits depending on configuration */
                VTSS_RC(l26_sd1g_write(vtss_state, mask, 0)); /* transfer 1G common config register */
            }
            if (serdes_type == SERDES_6G) {
                sq_mask = (clk_port ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_B_ENA :
                           VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_A_ENA);
                en_mask = (clk_port ? VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_RECO_SEL_B :
                           VTSS_F_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_RECO_SEL_A);
                VTSS_RC(l26_sd6g_read(vtss_state, mask)); /* Readback the 1G common config register */
                L26_RD(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, &common_cfg);
                common_cfg &= ~(sq_mask | en_mask);      /* clear the related bits for this configuration */
                common_cfg |= (conf->squelsh ? sq_mask : 0) | en_mask;
//printf("l26_synce_clock_in_set enable 6G   instance %u  common_cfg %X\n", serdes_instance, common_cfg);
                L26_WR(VTSS_MACRO_CTRL_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, common_cfg);   /* Set the related bits depending on configuration */
                VTSS_RC(l26_sd6g_write(vtss_state, mask, 0));     /* transfer 1G common config register */
            }
            vtss_state->synce.old_port_no[clk_port] = new_chip_port;
        }
    }

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_SYNCE */

/* - Debug print --------------------------------------------------- */

#define L26_DEBUG_HSIO(pr, addr, name) vtss_l26_debug_reg(vtss_state, pr, VTSS_MACRO_CTRL_##addr, name)
#define L26_DEBUG_MAC(pr, addr, i, name) vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_##addr, i, "MAC_"name)
#define L26_DEBUG_PCS(pr, addr, i, name) vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_##addr, i, "PCS_"name)

static vtss_rc l26_debug_port(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32                          i, value, port, tgt;
    vtss_port_no_t               port_no;
    char                         buf[32];

    L26_RD(VTSS_DEVCPU_GCB_MISC_MISC_CFG, &value);
    pr("Target  : 0x%04x/0x%04x\n", vtss_state->create.target, vtss_state->misc.chip_id.part_number);
    pr("Mux Mode: %u/%u\n\n",
       vtss_state->init_conf.mux_mode, VTSS_X_DEVCPU_GCB_MISC_MISC_CFG_SW_MODE(value));

    for (i = 0; info->full && i < 8; i++) {
        VTSS_SPRINTF(buf, "SerDes1G_%u", i);
        vtss_l26_debug_reg_header(pr, buf);
        VTSS_RC(l26_sd1g_read(vtss_state, 1 << i));
        L26_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_DES_CFG, "DES_CFG");
        L26_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_IB_CFG, "IB_CFG");
        L26_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_OB_CFG, "OB_CFG");
        L26_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_SER_CFG, "SER_CFG");
        L26_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, "COMMON_CFG");
        L26_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_PLL_CFG, "PLL_CFG");
        L26_DEBUG_HSIO(pr, SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS, "PLL_STATUS");
        L26_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0, "DFT_CFG0");
        L26_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1, "DFT_CFG1");
        L26_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2, "DFT_CFG2");
        L26_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_TP_CFG, "TP_CFG");
        L26_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_MISC_CFG, "MISC_CFG");
        L26_DEBUG_HSIO(pr, SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS, "DFT_STATUS");
        pr("\n");
    }

    for (i = 0; info->full && i < 4; i++) {
        VTSS_SPRINTF(buf, "SerDes6G_%u", i);
        vtss_l26_debug_reg_header(pr, buf);
        VTSS_RC(l26_sd6g_read(vtss_state, 1 << i));
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_DES_CFG, "DES_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_IB_CFG, "IB_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_IB_CFG1, "IB_CFG1");
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, "OB_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG1, "OB_CFG1");
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_SER_CFG, "SER_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, "COMMON_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, "PLL_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, "PLL_STATUS");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_DIG_CFG, "DIG_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0, "DFT_CFG0");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1, "DFT_CFG1");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2, "DFT_CFG2");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_TP_CFG0, "TP_CFG0");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_TP_CFG1, "TP_CFG1");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_MISC_CFG, "MISC_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG, "OB_ANEG_CFG");
        L26_DEBUG_HSIO(pr, SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS, "DFT_STATUS");
        pr("\n");
    }
    pr("\n");

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (info->port_list[port_no] == 0)
            continue;
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "Port %u", port);
        vtss_l26_debug_reg_header(pr, buf);
        tgt = VTSS_TO_DEV(port);
        vtss_l26_debug_reg_inst(vtss_state, pr,
                                port > 9 ? VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt) :
                                VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG(tgt),
                                port, "CLOCK_CFG");
        L26_DEBUG_MAC(pr, ENA_CFG(tgt), port, "ENA_CFG");
        L26_DEBUG_MAC(pr, MODE_CFG(tgt), port, "MODE_CFG");
        L26_DEBUG_MAC(pr, MAXLEN_CFG(tgt), port, "MAXLEN_CFG");
        L26_DEBUG_MAC(pr, TAGS_CFG(tgt), port, "TAGS_CFG");
        L26_DEBUG_MAC(pr, FC_CFG(tgt), port, "FC_CFG");
        L26_DEBUG_PCS(pr, CFG(tgt), port, "CFG");
        L26_DEBUG_PCS(pr, MODE_CFG(tgt), port, "MODE_CFG");
        L26_DEBUG_PCS(pr, SD_CFG(tgt), port, "SD_CFG");
        L26_DEBUG_PCS(pr, ANEG_CFG(tgt), port, "ANEG_CFG");
        L26_DEBUG_PCS(pr, ANEG_STATUS(tgt), port, "ANEG_STATUS");
        L26_DEBUG_PCS(pr, LINK_STATUS(tgt), port, "LINK_STATUS");
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt), port,
                                "PCS_FX100_CFG");
        vtss_l26_debug_reg_inst(vtss_state, pr, VTSS_DEV_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), port,
                                "FX100_STATUS");
        pr("\n");
    }
    pr("\n");

    return VTSS_RC_OK;
}

static void l26_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                          vtss_chip_counter_t *c1, vtss_chip_counter_t *c2)
{
    char buf[400];

    VTSS_SPRINTF(buf, "rx_%s:", col1);
    pr("%-19s%19" PRIu64, buf, c1->prev);
    if (col2 != NULL) {
        VTSS_SPRINTF(buf, "tx_%s:", VTSS_STRLEN(col2) ? col2 : col1);
        pr("   %-19s%19" PRIu64, buf, c2->prev);
    }
    pr("\n");
}

static void l26_debug_cnt_inst(const vtss_debug_printf_t pr, u32 i,
                               const char *col1, const char *col2,
                               vtss_chip_counter_t *c1, vtss_chip_counter_t *c2)
{
    char buf[200];

    VTSS_SPRINTF(buf, "%s_%u", col1, i);
    l26_debug_cnt(pr, buf, col2, c1, c2);
}

static vtss_rc l26_debug_port_cnt(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455) */ // Due to VTSS_EXIT_ENTER
    vtss_port_no_t               port_no;
    u32                          i, port;
    vtss_port_luton26_counters_t *cnt;
    BOOL                         cpu_port;

    if (info->has_action && info->action == 0) {
        pr("Port counter actions:\n");
        pr("0: Show actions\n");
        pr("1: Show CPU and VD counters\n");
        pr("2: Show MAC counters only\n");
        pr("3: Show QS counters only\n");
        return VTSS_RC_OK;
    }

    for (port_no = VTSS_PORT_NO_START; port_no <= vtss_state->port_count; port_no++) {
        cpu_port = (port_no == vtss_state->port_count);
        if (cpu_port) {
            /* CPU port */
            if (info->action != 1)
                continue;
            port = VTSS_CHIP_PORT_CPU;
            cnt = &vtss_state->port.cpu_counters.counter.luton26;
        } else {
            /* Normal port */
            if (info->action == 1 || info->port_list[port_no] == 0)
                continue;
            port = VTSS_CHIP_PORT(port_no);
            cnt = &vtss_state->port.counters[port_no].counter.luton26;
        }
        VTSS_RC(l26_port_counters_read(vtss_state, port, cnt, NULL, 0));
        VTSS_EXIT_ENTER();

        /* Basic counters */
        if (cpu_port) {
            pr("Counters CPU port: %u\n\n", port);
        } else {
            pr("Counters for port: %u (port_no %u):\n\n", port, port_no);
            if (info->full || info->action != 3) {
                l26_debug_cnt(pr, "oct", "", &cnt->rx_octets, &cnt->tx_octets);
                l26_debug_cnt(pr, "uc", "", &cnt->rx_unicast, &cnt->tx_unicast);
                l26_debug_cnt(pr, "mc", "", &cnt->rx_multicast, &cnt->tx_multicast);
                l26_debug_cnt(pr, "bc", "", &cnt->rx_broadcast, &cnt->tx_broadcast);
            }

            /* Detailed MAC counters */
            if (info->full || info->action == 2) {
                l26_debug_cnt(pr, "pause", "", &cnt->rx_pause, &cnt->tx_pause);
                l26_debug_cnt(pr, "64", "", &cnt->rx_64, &cnt->tx_64);
                l26_debug_cnt(pr, "65_127", "", &cnt->rx_65_127, &cnt->tx_65_127);
                l26_debug_cnt(pr, "128_255", "", &cnt->rx_128_255, &cnt->tx_128_255);
                l26_debug_cnt(pr, "256_511", "", &cnt->rx_256_511, &cnt->tx_256_511);
                l26_debug_cnt(pr, "512_1023", "", &cnt->rx_512_1023, &cnt->tx_512_1023);
                l26_debug_cnt(pr, "1024_1526", "", &cnt->rx_1024_1526, &cnt->tx_1024_1526);
                l26_debug_cnt(pr, "jumbo", "", &cnt->rx_1527_max, &cnt->tx_1527_max);
            }
            if (!cpu_port) {
                l26_debug_cnt(pr, "crc", NULL, &cnt->rx_crc_align_errors, NULL);
                l26_debug_cnt(pr, "short", NULL, &cnt->rx_shorts, NULL);
                l26_debug_cnt(pr, "long", NULL, &cnt->rx_longs, NULL);
                l26_debug_cnt(pr, "frag", NULL, &cnt->rx_fragments, NULL);
                l26_debug_cnt(pr, "jabber", NULL, &cnt->rx_jabbers, NULL);
                l26_debug_cnt(pr, "control", NULL, &cnt->rx_control, NULL);
            }
        }

        if (info->full || info->action == 1 || info->action == 3) {
            /* Queue system counters */
            l26_debug_cnt(pr, "cat_drop", cpu_port ? NULL : "drops",
                          &cnt->rx_classified_drops, &cnt->tx_drops);
            l26_debug_cnt(pr, "dr_local", cpu_port ? NULL : "aged",
                          &cnt->dr_local, &cnt->tx_aging);
            l26_debug_cnt(pr, "dr_tail", NULL, &cnt->dr_tail, NULL);
            for (i = 0; i < VTSS_PRIOS; i++)
                l26_debug_cnt_inst(pr, i, "green", "",
                                   &cnt->rx_green_class[i], &cnt->tx_green_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                l26_debug_cnt_inst(pr, i, "yellow", "",
                                   &cnt->rx_yellow_class[i], &cnt->tx_yellow_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                l26_debug_cnt_inst(pr, i, "red", NULL, &cnt->rx_red_class[i], NULL);
            for (i = 0; i < VTSS_PRIOS; i++)
                l26_debug_cnt_inst(pr, i, "dr_green", NULL, &cnt->dr_green_class[i], NULL);
            for (i = 0; i < VTSS_PRIOS; i++)
                l26_debug_cnt_inst(pr, i, "dr_yellow", NULL, &cnt->dr_yellow_class[i], NULL);
        }
        pr("\n");
    }
    return VTSS_RC_OK;
}

static void l26_debug_wm_dump (const vtss_debug_printf_t pr, const char *reg_name, u32 *value, u32 i, u32 multiplier) {
    u32 q;
    pr("%-25s",reg_name);
    for (q = 0; q < i; q++) {
        pr("%6u ", wm_dec(value[q]) * multiplier);
    }
    pr("\n");
}

static vtss_rc l26_debug_wm(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info)

{
    u32 port_no, value, q, dp, cpu_port, port;
    u32 id[8] = {0}, val1[8] = {0}, val2[8] = {0}, val3[8] = {0}, val4[8] = {0};


    for (port_no = VTSS_PORT_NO_START; port_no <= vtss_state->port_count; port_no++) {
        cpu_port = (port_no == vtss_state->port_count);
        if (cpu_port) {
            /* CPU port */
            if (!info->full)
                continue;
            port = VTSS_CHIP_PORT_CPU;
        } else {
            if (!info->port_list[port_no]) {
                continue;
            }
            port = VTSS_CHIP_PORT(port_no);
        }
        if (cpu_port)
            pr("CPU_Port          : %u\n\n",port_no);
        else
            pr("Port          : %u\n\n",port_no);
        if (!cpu_port) {
            L26_RD(VTSS_DEV_CMN_MAC_CFG_STATUS_MAC_FC_CFG(VTSS_TO_DEV(VTSS_CHIP_PORT(port_no))), &value);
            pr("FC Tx ena     : %d\n", (value & VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_TX_FC_ENA) ? 1 : 0);
            pr("FC Rx ena     : %d\n", (value & VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_RX_FC_ENA) ? 1 : 0);
            pr("FC Value      : 0x%x\n", VTSS_X_DEV_MAC_CFG_STATUS_MAC_FC_CFG_PAUSE_VAL_CFG(value));
            pr("FC Latency    : %u\n", VTSS_X_DEV_MAC_CFG_STATUS_MAC_FC_CFG_FC_LATENCY_CFG(value));
            pr("FC Zero pause : %d\n", (value & VTSS_F_DEV_MAC_CFG_STATUS_MAC_FC_CFG_ZERO_PAUSE_ENA) ? 1 : 0);

            L26_RD(VTSS_SYS_PAUSE_CFG_PAUSE_CFG(VTSS_CHIP_PORT(port_no)), &value);
            pr("FC Start      : 0x%x\n",  VTSS_X_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(value));
            pr("FC Stop       : 0x%x\n", VTSS_X_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(value));
            pr("FC Ena        : %d\n", (value & VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA) ? 1 : 0);
            L26_RD(VTSS_SYS_PAUSE_CFG_ATOP(VTSS_CHIP_PORT(port_no)), &value);
            pr("FC Atop       : 0x%x\n", VTSS_F_SYS_PAUSE_CFG_ATOP_ATOP(value));

            L26_RD(VTSS_SYS_PAUSE_CFG_PAUSE_TOT_CFG, &value);
            pr("FC TOT_START  : 0x%x\n", VTSS_X_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(value));
            pr("FC TOT_STOP   : 0x%x\n", VTSS_X_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(value));
            L26_RD(VTSS_SYS_PAUSE_CFG_ATOP_TOT_CFG, &value);
            pr("FC ATOP_TOT   : 0x%x\n", VTSS_F_SYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(value));
            pr("\n");
        }

        for (q = 0; q < VTSS_PRIOS; q++) {
            id[q] = q;
            L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 0)),   &val1[q]);
            L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 256)), &val2[q]);
            L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 512)), &val3[q]);
            L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 768)), &val4[q]);
        }

        l26_debug_wm_dump(pr, "Queue level:", id, 8, 1);
        l26_debug_wm_dump(pr, "Qu Ingr Buf Rsrv (Bytes) :", val1, 8, L26_BUFFER_CELL_SZ);
        l26_debug_wm_dump(pr, "Qu Ingr Ref Rsrv (Frames):", val2, 8, 1);
        l26_debug_wm_dump(pr, "Qu Egr Buf Rsrv  (Bytes) :", val3, 8, L26_BUFFER_CELL_SZ);
        l26_debug_wm_dump(pr, "Qu Egr Ref Rsrv  (Frames):", val4, 8, 1);
        pr("\n");

        /* Configure reserved space for port */
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((port + 224 +   0)), &val1[0]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((port + 224 + 256)), &val2[0]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((port + 224 + 512)), &val3[0]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((port + 224 + 768)), &val4[0]);
        pr("Port level:\n");
        pr("Port Ingress Buf Rsrv: %u Bytes\n",  wm_dec(val1[0]) * L26_BUFFER_CELL_SZ);
        pr("Port Ingress Ref Rsrv: %u Frames\n", wm_dec(val2[0]));
        pr("Port Egress  Buf Rsrv: %u Bytes\n",  wm_dec(val3[0]) * L26_BUFFER_CELL_SZ);
        pr("Port Egress  Ref Rsrv: %u Frames\n", wm_dec(val4[0]));
        pr("\n");
    }

    /* Shared space for all QoS classes */
    for (q = 0; q < VTSS_PRIOS; q++) {
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((q + 216 + 0)),   &val1[q]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((q + 216 + 256)), &val2[q]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((q + 216 + 512)), &val3[q]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((q + 216 + 768)), &val4[q]);
    }
    l26_debug_wm_dump(pr, "QoS level:", id, 8, 1);
    l26_debug_wm_dump(pr, "QoS Ingr Buf Rsrv (Bytes) :", val1, 8, L26_BUFFER_CELL_SZ);
    l26_debug_wm_dump(pr, "QoS Ingr Ref Rsrv (Frames):", val2, 8, 1);
    l26_debug_wm_dump(pr, "QoS Egr Buf Rsrv  (Bytes) :", val3, 8, L26_BUFFER_CELL_SZ);
    l26_debug_wm_dump(pr, "QoS Egr Ref Rsrv  (Frames):", val4, 8, 1);
    pr("\n");

    pr("Color level:\n");
    /* Configure shared space for both DP levels         */
    /* In this context dp:0 is yellow and dp:1 is green */
    for (dp = 0; dp < 2; dp++) {
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((dp + 254 +   0)), &val1[0]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((dp + 254 + 256)), &val2[0]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((dp + 254 + 512)), &val3[0]);
        L26_RD(VTSS_SYS_RES_CTRL_RES_CFG((dp + 254 + 768)), &val4[0]);
        pr("Port DP:%6s Ingress Buf Rsrv: 0x%x\n",dp?"Green":"Yellow", wm_dec(val1[0]));
        pr("Port DP:%6s Ingress Ref Rsrv: 0x%x\n",dp?"Green":"Yellow", wm_dec(val2[0]));
        pr("Port DP:%6s Egress  Buf Rsrv: 0x%x\n",dp?"Green":"Yellow", wm_dec(val3[0]));
        pr("Port DP:%6s Egress  Ref Rsrv: 0x%x\n",dp?"Green":"Yellow", wm_dec(val4[0]));
    }
    pr("\n");
    return VTSS_RC_OK;
}

vtss_rc vtss_l26_port_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT, l26_debug_port, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT_CNT, l26_debug_port_cnt, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_WM, l26_debug_wm, vtss_state, pr, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc l26_port_init(vtss_state_t *vtss_state)
{
    u32 port;

    /* Set up the Serdes1g/Serdes6g macros incl. switch_mode. */
    VTSS_RC(l26_serdes_macro_config(vtss_state));

    /* Release reset of internal Phys */
    L26_WRM_CLR(VTSS_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST,
                VTSS_F_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST_SOFT_PHY_RST);

    for (port = 0; port < 12; port++) { /* VTSS_CHIP_PORTS */
        if (port > 9) {
            L26_WRM_CLR(VTSS_DEV_PORT_MODE_CLOCK_CFG(VTSS_TO_DEV(port)),
                        VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PHY_RST);
        } else {
            L26_WRM_CLR(VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG(VTSS_TO_DEV(port)),
                        VTSS_F_DEV_GMII_PORT_MODE_CLOCK_CFG_PHY_RST);
        }
    }

    /* Clear counters */
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        L26_WRM(VTSS_SYS_SYSTEM_STAT_CFG,
                VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_PORT(port) |
                VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_SHOT,
                VTSS_M_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_PORT);
    }

    /* Only count drops once */
    L26_WRM_SET(VTSS_SYS_SYSTEM_STAT_CFG, VTSS_BIT(6));

    /* Wait for internal PHYs to be ready */
    VTSS_MSLEEP(500);

    // Power down all PHY ports as default in order to save power
    for (port = 0; port < 12; port++) { /* VTSS_CHIP_PORTS */
        (void)l26_miim_write(vtss_state, VTSS_MIIM_CONTROLLER_0, port, 0, 1<<11, FALSE);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_port_state_t *state = &vtss_state->port;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->miim_read = l26_miim_read;
        state->miim_write = l26_miim_write;
        state->mmd_read = l26_mmd_read;
        state->mmd_read_inc = l26_mmd_read_inc;
        state->mmd_write = l26_mmd_write;
        state->conf_get = l26_port_conf_get;
        state->conf_set = l26_port_conf_set;
        state->clause_37_status_get = l26_port_clause_37_status_get;
        state->clause_37_control_get = l26_port_clause_37_control_get;
        state->clause_37_control_set = l26_port_clause_37_control_set;
        state->status_get = l26_port_status_get;
        state->counters_update = l26_port_counters_update;
        state->counters_clear = l26_port_counters_clear;
        state->counters_get = l26_port_counters_get;
        state->basic_counters_get = l26_port_basic_counters_get;
        state->forward_set = l26_port_forward_set;
        state->test_conf_set = l26_port_test_conf_set;
#if defined(VTSS_FEATURE_SYNCE)
        vtss_state->synce.clock_out_set = l26_synce_clock_out_set;
        vtss_state->synce.clock_in_set = l26_synce_clock_in_set;
#endif /* VTSS_FEATURE_SYNCE */
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(l26_port_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        if (!vtss_state->warm_start_cur) {
            /* Setup WM (depends on the port map)  */
            VTSS_RC(l26_buf_conf_set(vtss_state));
        }
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LUTON26 */
