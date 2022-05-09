// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_ocelot_cil.h"

#if defined(VTSS_ARCH_OCELOT)

/* - CIL functions ------------------------------------------------- */



static BOOL srvl_port_is_internal_phy(u32 chip_port);

static vtss_rc srvl_port_clause_37_control_get(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no,
                                               vtss_port_clause_37_control_t *const control)
{
    u32 value, port = VTSS_CHIP_PORT(port_no);

    SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(VTSS_TO_DEV(port)), &value);
    control->enable = VTSS_BOOL(value & VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA);
    value = VTSS_X_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(control->enable ? value : 0);
    VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &control->advertisement));

    return VTSS_RC_OK;
}

static vtss_rc srvl_port_clause_37_control_set(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no)
{
    vtss_port_clause_37_control_t *control = &vtss_state->port.clause_37[port_no];
    u32                           value, port = VTSS_CHIP_PORT(port_no);

    /* Aneg capabilities for this port */
    VTSS_RC(vtss_cmn_port_clause_37_adv_set(&value, &control->advertisement, control->enable));

    /* Set aneg capabilities */
    SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(VTSS_TO_DEV(port)),
           VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(value) |
           VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT |
           (control->enable ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA : 0));

    return VTSS_RC_OK;
}

static vtss_rc srvl_port_clause_37_status_get(vtss_state_t *vtss_state,
                                              const vtss_port_no_t         port_no,
                                              vtss_port_clause_37_status_t *const status)
{
    u32                    value, tgt = VTSS_TO_DEV(vtss_state->port.map[port_no].chip_port);
    vtss_port_sgmii_aneg_t *sgmii_adv = &status->autoneg.partner.sgmii;
    BOOL                   synced_status;
    vtss_port_clause_37_control_t *aneg = &vtss_state->port.clause_37[port_no];

    if (vtss_state->port.conf[port_no].power_down) {
        status->link = 0;
        return VTSS_RC_OK;
    }

    /* Get the link state 'down' sticky bit  */
    SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);
    status->link = (SRVL_BF(DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY, value) ? 0 : 1);
    SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(tgt), &value);
    if (status->link == 0) {
        /* The link has been down. Clear the sticky bit and return the 'down' value  */
        SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt),
                VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY);
    } else {
        status->link = SRVL_BF(DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS, value) &&
                       SRVL_BF(DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS, value);
    }

    synced_status = SRVL_BF(DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_SYNC_STATUS, value);

    /* Get PCS ANEG status register */
    SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS(tgt), &value);

    /* Get 'Aneg complete'   */
    status->autoneg.complete = SRVL_BF(DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);

   /* Workaround for a Serdes issue, when aneg completes with FDX capability=0 */
   /* There is another situation which needs to restart aneg: aneg un-complete but the synced status is up, added by SGZ */

    if (aneg->enable && vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SERDES) {
        if ((status->autoneg.complete && ((value >> 21) & 0x1) == 0) ||
            (synced_status && !status->autoneg.complete)) {
            SRVL_WRM_CLR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
            SRVL_WRM_SET(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
            (void)srvl_port_clause_37_control_set(vtss_state, port_no); /* Restart Aneg */
            VTSS_MSLEEP(50);
            SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS(tgt), &value);
            status->autoneg.complete = SRVL_BF(DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_ANEG_COMPLETE, value);
        }
    }

    /* Return partner advertisement ability */
    value = VTSS_X_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_STATUS_LP_ADV_ABILITY(value);

    VTSS_N("port:%d, if_type:0x%X", port_no, vtss_state->port.conf[port_no].if_type);
    if (vtss_state->port.conf[port_no].if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
        sgmii_adv->link = ((value >> 15) == 1) ? 1 : 0;
        sgmii_adv->fdx = (((value >> 12) & 0x1) == 1) ? 1 : 0;
        value = ((value >> 10) & 3);
        sgmii_adv->speed_10M = (value == 0 ? 1 : 0);
        sgmii_adv->speed_100M = (value == 1 ? 1 : 0);
        sgmii_adv->speed_1G = (value == 2 ? 1 : 0);
        sgmii_adv->hdx = (status->autoneg.partner.cl37.fdx ? 0 : 1);

        if (status->link) {
            /* If the SFP module does not have a link then the port does not have link */
            status->link = sgmii_adv->link;
        }

        VTSS_N("port:%d, value:0x%X, sgmii_adv->link:%d, status->link:%d", port_no, value, sgmii_adv->link, status->link);
    } else {
        VTSS_RC(vtss_cmn_port_clause_37_adv_get(value, &status->autoneg.partner.cl37));
    }
    return VTSS_RC_OK;
}

/* =================================================================
 *  Serdes configuration
 * =================================================================*/

#if VTSS_OPT_TRACE
static const char *srvl_serdes_mode_txt(vtss_serdes_mode_t mode)
{
    return (mode == VTSS_SERDES_MODE_DISABLE ? "DISABLE" : 
            mode == VTSS_SERDES_MODE_2G5 ? "2G5" : 
            mode == VTSS_SERDES_MODE_SGMII ? "SGMII" :
            mode == VTSS_SERDES_MODE_100FX ? "100FX" :
            mode == VTSS_SERDES_MODE_1000BaseX ? "1000BX" : "?");
}
#endif

/* Serdes1G: Read/write data */
static vtss_rc srvl_sd1g_read_write(vtss_state_t *vtss_state, u32 addr, BOOL write)
{
    u32 data, mask;
    
    if (write)
        mask = VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_WR_ONE_SHOT;
    else
        mask = VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT;

    SRVL_WR(VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG,
           VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR(addr) | mask);
    
    do { /* Wait until operation is completed  */
        SRVL_RD(VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG, &data);
    } while (data & mask);

    return VTSS_RC_OK;
}

/* Serdes1G: Read data */
static vtss_rc srvl_sd1g_read(vtss_state_t *vtss_state, u32 addr) 
{
    return srvl_sd1g_read_write(vtss_state, addr, 0);
}

/* Serdes1G: Write data */
static vtss_rc srvl_sd1g_write(vtss_state_t *vtss_state, u32 addr)
{
    return srvl_sd1g_read_write(vtss_state, addr, 1);
}

/* Wait 100 usec after some SerDes operations */
static vtss_rc srvl_sd1g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 addr)
{
    vtss_serdes_mode_t mode = vtss_state->port.serdes_mode[port_no];
    vtss_port_lb_t     lb = vtss_state->port.test_conf[port_no].loopback;
    BOOL ena_lane = 1, if_100fx = 0, ena_dc_coupling = 0, idle = 0;
    u32  ob_amp_ctrl = 0, cpmd_sel=0, mbtr_ctrl=2, des_bw_ana=6, test_mode = 0, test_pattern = 0;
    u32  des_phs_ctrl = 6, cmv_term = 1;

    VTSS_D("addr: 0x%x, mode: %s", addr, srvl_serdes_mode_txt(mode));
    
    switch (mode) {
    case VTSS_SERDES_MODE_SGMII:
        ob_amp_ctrl = 12;
        break;
    case VTSS_SERDES_MODE_100FX:
        ob_amp_ctrl = 12;
        if_100fx = 1;
        cpmd_sel = 2;
        mbtr_ctrl = 3;
        ena_dc_coupling = 1;
        des_bw_ana = 0;
        des_phs_ctrl = 14; // BZ21121
        cmv_term = 0;
        break;
    case VTSS_SERDES_MODE_1000BaseX:
        ob_amp_ctrl = 15;
        break;
    case VTSS_SERDES_MODE_DISABLE:
        ena_lane = 0;
        ob_amp_ctrl = 0;
        break;
    case VTSS_SERDES_MODE_IDLE:
        idle = 1;
        break;
    case VTSS_SERDES_MODE_TEST_MODE:
        test_mode = 2; // Fixed pattern
        test_pattern = 0x5f289;
        break;
    default:
        VTSS_E("Serdes1g mode %s not supported", srvl_serdes_mode_txt(mode));
        return VTSS_RC_ERROR;
    }

    VTSS_RC(srvl_sd1g_read(vtss_state, addr));
  
    /* 1. Configure macro, apply reset */
    /* IB_CFG */
    SRVL_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG,
             (idle ? VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_IDLE : 0) |
             (lb == VTSS_PORT_LB_FACILITY ? VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI : 0),
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_IDLE |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI);

    if (idle) {
        /* Apply the idle mode (port down) and return */
        VTSS_RC(srvl_sd1g_write(vtss_state, addr));
        return VTSS_RC_OK;
    }

    SRVL_WR(VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_TP_CFG, test_pattern);
    SRVL_WRM(VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0,
            VTSS_ENCODE_BITFIELD(test_mode,16,3),
            VTSS_ENCODE_BITMASK(16,3));

    SRVL_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG,
             (if_100fx ? VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA : 0) |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DETLEV |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV(3) |
             (ena_dc_coupling ? VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING : 0) |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN(2) |
             (cmv_term ? VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM : 0),
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DETLEV |
             VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING |
             VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM);

    /* DES_CFG */
    SRVL_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG,
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL(cpmd_sel) |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL(mbtr_ctrl) |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA(des_bw_ana) |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL(des_phs_ctrl),
             VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL |
             VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL |
             VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA |
             VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL);


    /* OB_CFG */
    SRVL_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG,
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL(ob_amp_ctrl),
             VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL);
    
    /* COMMON_CFG */
    SRVL_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
             (ena_lane ? VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE : 0) |
             (lb == VTSS_PORT_LB_FACILITY ? VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP : 0) |
             (lb == VTSS_PORT_LB_EQUIPMENT ? VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP : 0),
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP);

    SRVL_WRM_CLR(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
                 VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_PWD_RX);
    SRVL_WRM_CLR(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
                 VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_PWD_TX);

    /* PLL_CFG */
    SRVL_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG,
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA |
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA(200),
             VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA |
             VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA);   
    
    /* MISC_CFG */
    SRVL_WRM(VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG,
             (if_100fx ? VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA : 0) |
             VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST,
             VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA |
             VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST);
    
    VTSS_RC(srvl_sd1g_write(vtss_state, addr));
    
    /* 2. Release PLL reset */
    SRVL_WRM_SET(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
                 VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST);
    VTSS_RC(srvl_sd1g_write(vtss_state, addr));
    
    /* 3. Release digital reset */
    SRVL_WRM(VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG, 0,
             VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST);
    VTSS_RC(srvl_sd1g_write(vtss_state, addr));
    
    return VTSS_RC_OK;
}

static vtss_rc srvl_sd6g_lock(vtss_state_t *vtss_state)
{
    u32 value;

    do {
        SRVL_RD(VTSS_DEVCPU_ORG_ORG_SEMA0, &value);
    } while (value == 0);
    return VTSS_RC_OK;
}

static vtss_rc srvl_sd6g_unlock(vtss_state_t *vtss_state)
{
    SRVL_WR(VTSS_DEVCPU_ORG_ORG_SEMA0, 1);
    return VTSS_RC_OK;
}

/* Serdes6G: Read/write data */
static vtss_rc srvl_sd6g_read_write(vtss_state_t *vtss_state, u32 addr, BOOL write)
{
    u32 data, mask;

    if (write)
        mask = VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT;
    else
        mask = VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT;

    SRVL_WR(VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG,
            VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(addr) | mask);
    
    do { /* Wait until operation is completed  */
        SRVL_RD(VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG, &data);
    } while (data & mask);

    return VTSS_RC_OK;
}

/* Serdes6G: Read data */
static vtss_rc srvl_sd6g_read(vtss_state_t *vtss_state, u32 addr) 
{
    return srvl_sd6g_read_write(vtss_state, addr, 0);
}

/* Serdes6G: Write data */
static vtss_rc srvl_sd6g_write(vtss_state_t *vtss_state, u32 addr)
{
    return srvl_sd6g_read_write(vtss_state, addr, 1);
}

/* Serdes6G setup (Disable/2G5/QSGMII/SGMII) */
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
static vtss_rc srvl_sd6g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 addr)
{
    vtss_serdes_mode_t mode = vtss_state->port.serdes_mode[port_no];
    vtss_port_lb_t     lb = vtss_state->port.test_conf[port_no].loopback;
    /* The following code is based on the Jaguar-2/Serval-T implementation */
    /* Therefore it is open to Ocelot specific tweaks */
    u32 ob_ena1v_mode = 0;
    u32 ob_post0 = 0;
    u32 ob_prec = 0;
    u32 ob_ena_cas = 0;
    u32 ob_lev = 24;
    u32 idle = 0;
    u32 des_cpmd_sel = 0;
    u32 des_bw_ana = 3; // as per BZ 17124
    u32 ib_sig_det_clk_sel = 7;
    u32 ser_alisel = 0;
    u32 ser_enali = 0;
    u32 pll_div4 = 0;
    u32 pll_ena_rot = 0;
    u32 pll_fsm_ctrl_data = 120;
    u32 pll_rot_dir = 0;
    u32 pll_rot_frq = 0;
    u32 hrate = 0;
    u32 qrate = 0;
    u32 if_mode = 3;
    u32 des_100fx_cpmd_ena = 0;
    u32 rx_lpi_mode_ena = 0;
    u32 tx_lpi_mode_ena = 0;
    u32 ib_concur = 1;
    u32 ena_lane = 1;
    u32 ib_sig_det_ena = 1;
    u32 ib_sam_ena = 1;
    u32 test_mode = 0;
    u32 test_pattern = 0;
    // 100FX (BZ21878) default values:
    u32 ib_ureg        = 4;  // if_cfg2
    u32 ib_eqz_ena     = 1;  // if_cfg
    u32 ib_reg_ena     = 1;  // if_cfg
    u32 ib_filt_offset = 1;  // ib_cfg1
    u32 ib_filt_hp     = 1;  // ib_cfg1
    u32 ib_filt_mid    = 1;  // ib_cfg1
    u32 ib_filt_lp     = 1;  // ib_cfg1
    u32 ib_frc_offset  = 0;  // ib_cfg1
    u32 ib_frc_hp      = 0;  // ib_cfg1
    u32 ib_frc_mid     = 0;  // ib_cfg1
    u32 ib_frc_lp      = 0;  // ib_cfg1
    u32 ib_ini_hp      = 0;  // ib_cfg3
    u32 ib_ini_mid     = 31; // ib_cfg3
    u32 ib_ini_lp      = 1;  // ib_cfg3
    u32 ib_ini_offset  = 31; // ib_cfg3
    // Ferret
    u32 des_phs_ctrl = 2;


    switch (mode) {
    case VTSS_SERDES_MODE_2G5:
        ob_ena1v_mode = 0;
        ob_post0 = 0;
        ob_ena_cas = 0;
        ob_lev = 63;
        ser_alisel = 0;
        ser_enali = 0;
        pll_ena_rot = 1;
        pll_fsm_ctrl_data = 48;
        pll_rot_frq = 1;
        hrate = 1;
        qrate = 0;
        if_mode = 1;
        des_100fx_cpmd_ena = 0;
        des_bw_ana = 4; // as per BZ 17124
        break;
    case VTSS_SERDES_MODE_QSGMII:
        ob_ena1v_mode = 0;
        ob_post0 = 0;
        ob_ena_cas = 0;
        ob_lev = 24;
        ser_alisel = 0;
        ser_enali = 0;
        pll_ena_rot = 0;
        pll_fsm_ctrl_data = 120;
        pll_rot_frq = 0;
        hrate = 0;
        qrate = 0;
        if_mode = 3;
        des_100fx_cpmd_ena = 0;
        des_bw_ana = 5; // as per BZ 17124
        break;
    case VTSS_SERDES_MODE_SGMII:
        ob_ena1v_mode = 1;
        ob_post0 = 0;
        ob_ena_cas = 2;
        ob_lev = 48;
        ser_alisel = 0;
        ser_enali = 0;
        pll_ena_rot = 0;
        pll_fsm_ctrl_data = 60;
        pll_rot_frq = 0;
        hrate = 0;
        qrate = 1;
        if_mode = 1;
        des_100fx_cpmd_ena = 0;
        break;
    case VTSS_SERDES_MODE_100FX:
        ob_ena1v_mode = 1;
        ob_post0 = 1;
        ob_ena_cas = 0;
        ob_lev = 48;
        ser_alisel = 0;
        ser_enali = 0;
        pll_ena_rot = 0;
        pll_fsm_ctrl_data = 60;
        pll_rot_frq = 0;
        hrate = 0;
        qrate = 1;
        if_mode = 1;
        des_100fx_cpmd_ena = 1;
        des_cpmd_sel = 2;

        // 100FX (BZ21878):
        des_phs_ctrl   = 10;
        ib_ureg        = 4;
        ib_eqz_ena     = 0;
        ib_reg_ena     = 0;

        ib_filt_offset = 0;
        ib_filt_hp     = 0;
        ib_filt_mid    = 0;
        ib_filt_lp     = 0;
        ib_frc_offset  = 1;
        ib_frc_hp      = 1;
        ib_frc_mid     = 1;
        ib_frc_lp      = 1;

        ib_ini_hp      = 0;
        ib_ini_mid     = 31;
        ib_ini_lp      = 63;
        ib_ini_offset  = 31;
        break;
    case VTSS_SERDES_MODE_1000BaseX:
        ob_ena1v_mode = 0;
        ob_post0 = 1;
        ob_ena_cas = 2;
        ob_lev = 48;
        ser_alisel = 0;
        ser_enali = 0;
        pll_ena_rot = 0;
        pll_fsm_ctrl_data = 60;
        pll_rot_frq = 0;
        qrate = 1;
        if_mode = 1;
        des_100fx_cpmd_ena = 0;
        break;
    case VTSS_SERDES_MODE_XAUI:
        ob_ena1v_mode = 0;
        ob_post0 = 0;
        ob_ena_cas = 0;
        ob_lev = 63;
        ser_alisel = 1;
        ser_enali = 1;
        pll_ena_rot = 1;
        pll_fsm_ctrl_data = 48;
        pll_rot_frq = 1;
        hrate = 1;
        qrate = 0;
        if_mode = 1;
        des_100fx_cpmd_ena = 0;
        break;
    case VTSS_SERDES_MODE_IDLE:
        idle = 1;
        break;
    case VTSS_SERDES_MODE_TEST_MODE:
        test_mode = 2; // Fixed pattern
        test_pattern = 0x5f289;
        break;
    case VTSS_SERDES_MODE_DISABLE:
        ib_concur = 0;
        ena_lane = 0;
        ib_sig_det_ena = 0;
        ib_reg_ena = 0;
        ib_sam_ena = 0;
        ib_eqz_ena = 0;
        break;
    default:
        VTSS_E("Serdes6g mode %s not supported", vtss_serdes_mode_txt(mode));
        return VTSS_RC_ERROR;
    }

    VTSS_RC(srvl_sd6g_lock(vtss_state));
    VTSS_RC(srvl_sd6g_read(vtss_state, addr));

    if (idle) {
        /* Apply the idle mode (port down) and return */
        SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG, idle,
                     VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_IDLE);
        VTSS_RC(srvl_sd6g_write(vtss_state, addr));
        VTSS_RC(srvl_sd6g_unlock(vtss_state));
        return VTSS_RC_OK;
    }

    // prepare for initial or new configuration

    // Set test mode and test pattern
    SRVL_WR(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0, test_pattern);
    SRVL_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0,
             VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TEST_MODE(test_mode),
             VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TEST_MODE);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                 0,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
                 0,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
             (ib_sig_det_ena ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA : 0) |
             (ib_reg_ena ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA : 0) |
             (ib_sam_ena ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA : 0) |
             (ib_eqz_ena ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA : 0) |
             (ib_concur ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR : 0),
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
             (ib_filt_offset ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_OFFSET : 0) |
             (ib_filt_hp ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_HP : 0) |
             (ib_filt_mid ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_MID : 0) |
             (ib_filt_lp ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_LP : 0) |
             (ib_frc_offset ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_OFFSET : 0) |
             (ib_frc_hp ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_HP : 0) |
             (ib_frc_mid ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_MID : 0) |
             (ib_frc_lp ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_LP : 0),
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_OFFSET |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_HP |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_MID |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_LP |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_OFFSET |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_HP |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_MID |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_LP);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UREG(ib_ureg),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UREG);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_HP(ib_ini_hp) |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_MID(ib_ini_mid) |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_LP(ib_ini_lp) |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_OFFSET(ib_ini_offset),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_HP |
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_MID |
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_LP |
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_OFFSET);

    SRVL_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
             VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST,
             VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

    VTSS_RC(srvl_sd6g_write(vtss_state, addr));

    // apply configuration

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
                 idle,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_IDLE);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
                 ob_ena1v_mode,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(ob_post0),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(ob_prec),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(ob_ena_cas),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(ob_lev),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(des_phs_ctrl),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(des_cpmd_sel),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(des_bw_ana),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(0),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(16),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(ser_alisel),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG,
                 ser_enali || lb == VTSS_PORT_LB_FACILITY,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
                 pll_div4,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
                 pll_ena_rot,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(pll_fsm_ctrl_data),
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
                 pll_rot_dir,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
                 pll_rot_frq,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
                 1,
                 VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                 1,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                 ena_lane,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                 0,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                 0,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                 hrate,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
                 qrate,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE);

    SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
             (lb == VTSS_PORT_LB_FACILITY ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP : 0) |
             (lb == VTSS_PORT_LB_EQUIPMENT ? VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP : 0) |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(if_mode),
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP |
             VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP |
             VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
                 des_100fx_cpmd_ena,
                 VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
                 rx_lpi_mode_ena,
                 VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
                 tx_lpi_mode_ena,
                 VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA);

    VTSS_RC(srvl_sd6g_write(vtss_state, addr));

    // Step 2: Set pll_fsm_ena=1
    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
                 1,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

    VTSS_RC(srvl_sd6g_write(vtss_state, addr));

    // Step 3: Wait for 20 ms for PLL bringup
    VTSS_MSLEEP(20);

    // Step 4: Start IB calibration by setting ib_cal_ena and clearing lane_rst
    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
                 1,
                 VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA);

    SRVL_WRM_CTL(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
                 0,
                 VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

      VTSS_RC(srvl_sd6g_write(vtss_state, addr));

      // Step 5: Wait for 60 ms for calibration
      VTSS_MSLEEP(60);

      // Step 6:Set ib_tsdet and ib_reg_pat_sel_offset back to correct values
      SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
               VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0),
               VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET);

      SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
               VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(ib_sig_det_clk_sel),
               VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL);

      SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
               VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(3),
               VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET);

      VTSS_RC(srvl_sd6g_write(vtss_state, addr));
      VTSS_RC(srvl_sd6g_unlock(vtss_state));
    return VTSS_RC_OK;
}
#endif

/* Configure the Serdes1G/Serdes6G blocks based on mux mode and target */
static vtss_rc ocelot_serdes_macro_config(vtss_state_t *vtss_state)
{
    vtss_port_mux_mode_t mux_mode = vtss_state->init_conf.mux_mode;

    /* Configure the HW device mux */
    if (vtss_state->create.target == VTSS_TARGET_7511 ||
        vtss_state->create.target == VTSS_TARGET_7513) {
        switch (mux_mode) {
        case VTSS_PORT_MUX_MODE_0:
            // Default API settings, no over-ride needed.
            break;
        case VTSS_PORT_MUX_MODE_1:
            // Enable PCIe mode for SerDes6G_2.
            SRVL_WR(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_PCIE_ENA);
            break;
        case VTSS_PORT_MUX_MODE_2:
            // Enable QSGMII mode for devices DEV1G_4, DEV1G_5,
            // DEV1G_6, and DEV1G_7 via SerDes6G_0.
            SRVL_WR(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_QSGMII_ENA);
            break;
        case VTSS_PORT_MUX_MODE_3:
            // 1) Enable QSGMII mode for devices DEV1G_4, DEV1G_5,
            //    DEV1G_6, and DEV1G_7 via SerDes6G_0.
            // 2) Enable PCIe mode for SerDes6G_2.
            SRVL_WR(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_QSGMII_ENA |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_PCIE_ENA);
            break;
        default:
            VTSS_E("port mux mode not supported");
        }
    } else if (vtss_state->create.target == VTSS_TARGET_7512 ||
               vtss_state->create.target == VTSS_TARGET_7514) {
        switch (mux_mode) {
        case VTSS_PORT_MUX_MODE_0:
            // Default API settings, no over-ride needed.
            break;
        case VTSS_PORT_MUX_MODE_1:
            // Enable PCIe mode for SerDes6G_2.
            SRVL_WR(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_PCIE_ENA);
            break;
        case VTSS_PORT_MUX_MODE_2:
            // 1) Enable QSGMII mode for devices DEV1G_4, DEV1G_5,
            //    DEV1G_6, and DEV1G_7 via SerDes6G_0.
            // 2) Connect DEV1G_9 to SerDes1G_4.
            SRVL_WR(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_QSGMII_ENA |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV1G_9_MODE);
            break;
        case VTSS_PORT_MUX_MODE_3:
            // 1) Enable QSGMII mode for devices DEV1G_4, DEV1G_5,
            //    DEV1G_6, and DEV1G_7 via SerDes6G_0.
            // 2) Enable PCIe mode for SerDes6G_2.
            // 3) Connect DEV2G5_10 to SerDes1G_5.
            //    Setting PCIE_ENA prevents that DEV2G5_10 can be connected to SerDes6G_2.
            // 4) Connect DEV1G_9 to SerDes1G_4.
            SRVL_WR(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_QSGMII_ENA |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_PCIE_ENA |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV2G5_10_MODE |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV1G_9_MODE);
            break;
        case VTSS_PORT_MUX_MODE_4:
            // 1) Connect DEV1G_9 to SerDes1G_4.
            // 2) Connect DEV1G_4 to SerDes1G_2.
            //    SerDes1G_4 is used by DEV1G_9.
            // 3) Connect DEV1G_6 to SerDes1G_3.
            SRVL_WR(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV1G_4_MODE |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV1G_6_MODE |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV1G_9_MODE);
            break;
        case VTSS_PORT_MUX_MODE_5:
            // 1) Enable PCIe mode for SerDes6G_2.
            // 2) Connect DEV1G_9 to SerDes1G_4.
            // 3) Connect DEV1G_4 to SerDes1G_2.
            //    SerDes1G_4 is used by DEV1G_9.
            // 4) Connect DEV1G_6 to SerDes1G_3.
            SRVL_WR(VTSS_HSIO_HW_CFGSTAT_HW_CFG,
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_PCIE_ENA |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV1G_4_MODE |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV1G_6_MODE |
                    VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV1G_9_MODE);
            break;
        default:
            VTSS_E("port mux mode not supported");
            return VTSS_RC_ERROR;
        }
    } else {
        VTSS_E("Chip target not supported");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

/* ================================================================= *
 *  SYNCE (Level 1 syncronization)
 * ================================================================= */

#define SRVL_SERDES_INST_NONE 255

static vtss_rc srvl_serdes_inst_get(vtss_state_t *vtss_state,
                                    u32 port, u32 *inst, BOOL *serdes6g)
{
    if (port >= VTSS_CHIP_PORTS) {
        VTSS_E("illegal port: %u", port);
        return VTSS_RC_ERROR;
    }

    u8 mode0_serd6[] =   {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1};
    u8 mode0_inst_no[] = {0, 1, 2, 3, 4, 5, SRVL_SERDES_INST_NONE, 0, 1, SRVL_SERDES_INST_NONE, 2};

    u8 mode1_serd6[] =   {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0};
    u8 mode1_inst_no[] = {0, 1, 2, 3, 4, 5, SRVL_SERDES_INST_NONE, 0, 1, SRVL_SERDES_INST_NONE, SRVL_SERDES_INST_NONE};

    u8 mode2_serd6[] =   {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1};
    u8 mode2_inst_no[] = {0, 1, 2, 3, 0, 0, 0, 0, 1, 4, 2};

    u8 mode3_serd6[] =   {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0};
    u8 mode3_inst_no[] = {0, 1, 2, 3, 0, 0, 0, 0, 1, 4, 5};

    u8 mode4_serd6[] =   {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1};
    u8 mode4_inst_no[] = {0, 1, SRVL_SERDES_INST_NONE, SRVL_SERDES_INST_NONE, 2, 5, 3, 0, 1, 4, 2};

    u8 mode5_serd6[] =   {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0};
    u8 mode5_inst_no[] = {0, 1, SRVL_SERDES_INST_NONE, SRVL_SERDES_INST_NONE, 2, 5, 3, 0, 1, 4, SRVL_SERDES_INST_NONE};

    vtss_port_mux_mode_t mux_mode = vtss_state->init_conf.mux_mode;

    switch (mux_mode) {
    case VTSS_PORT_MUX_MODE_0:
        *serdes6g = mode0_serd6[port];
        *inst = mode0_inst_no[port];
        break;
    case VTSS_PORT_MUX_MODE_1:
        *serdes6g = mode1_serd6[port];
        *inst = mode1_inst_no[port];
        break;
    case VTSS_PORT_MUX_MODE_2:
        *serdes6g = mode2_serd6[port];
        *inst = mode2_inst_no[port];
        // Difference in the port map for VSC7511/VSC7513
        if (port == 9 && (vtss_state->create.target == VTSS_TARGET_7511 ||
                          vtss_state->create.target == VTSS_TARGET_7513)) {
            *inst = SRVL_SERDES_INST_NONE;
        }
        break;
    case VTSS_PORT_MUX_MODE_3:
        *serdes6g = mode3_serd6[port];
        *inst = mode3_inst_no[port];
        // Difference in the port map for VSC7513
        if ((port == 9 || port == 10) && (vtss_state->create.target == VTSS_TARGET_7511 ||
                                          vtss_state->create.target == VTSS_TARGET_7513)) {
            *inst = SRVL_SERDES_INST_NONE;
        }
        break;
    case VTSS_PORT_MUX_MODE_4:
        *serdes6g = mode4_serd6[port];
        *inst = mode4_inst_no[port];
        break;
    case VTSS_PORT_MUX_MODE_5:
        *serdes6g = mode5_serd6[port];
        *inst = mode5_inst_no[port];
        break;
    default:
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

// Serval:
// Clock A output maps to Serval RCVRD_CLK0
// Use register RECO_CLK_SEL0 to select any port as source
// All individual Clock divider registers are set to 'divider'
// Clock B output maps to Serval RCVRD_CLK1.9 (configured by a separate function)
// Use common clockbus to select any port as source
// Clock divider register is the common bus divider
// clk_port = 0 => CLK_A, clk_port = 1 => CLK_B
// Ocelot:
// Clock A output maps to Serval RCVRD_CLK0, Clock B output maps to Serval RCVRD_CLK1
#define RCVRD_CLK_GPIO_NO 20      // on ocelot the 2 recovered clock outputs are GPIO 20-21

static vtss_rc srvl_synce_clock_out_set(vtss_state_t *vtss_state, const u32 clk_port)
{
    vtss_synce_clock_out_t *conf = &vtss_state->synce.out_conf[clk_port];
    u32 div_mask;

    switch (conf->divider) {
        case VTSS_SYNCE_DIVIDER_1: div_mask = 6; break;
        case VTSS_SYNCE_DIVIDER_4: div_mask = 1; break;
        case VTSS_SYNCE_DIVIDER_5: div_mask = 4; break;
        case VTSS_SYNCE_DIVIDER_2: div_mask = 0; break;
        case VTSS_SYNCE_DIVIDER_8: div_mask = 2; break;
        case VTSS_SYNCE_DIVIDER_16: div_mask = 3; break;
        case VTSS_SYNCE_DIVIDER_25: div_mask = 5; break;
        default: div_mask = 6; break;
    }

    VTSS_D("divider %d, div_mask %d, clk_port %d\n", vtss_state->synce.out_conf[clk_port].divider, div_mask, clk_port);
    SRVL_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(clk_port),
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_DIV(div_mask) |
            (vtss_state->synce.out_conf[clk_port].enable ? VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA : 0),
            VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_DIV |
            VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA);
    // Recovered clocks use GPIO20 and 21
    if (VTSS_RC_OK != vtss_srvl_gpio_mode(vtss_state, 0, RCVRD_CLK_GPIO_NO + clk_port, VTSS_GPIO_ALT_0)) {
        VTSS_E("Failed to set GPIO mode for recovered clock[%d]\n", clk_port);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

#define rcvrd_clk_b_output_pin 1        // clock selector uses pin 1

// Serval:
// Clock A output maps to Serval RCVRD_CLK0
// Use register RECO_CLK_ENA to enable the output (individual for all ports)
// Clock B output maps to Serval RCVRD_CLK1..9 (configured by a separate function)
// Use common clockbus to select any port as source (output B is activated for the selected port
// If Clock B outout is disabled, all CLK1..9 outputs are set to individual.
// clk_port = 0 => CLK_A, clk_port = 1 => CLK_B
// Ocelot:
// Clock A output maps to Serval RCVRD_CLK0, Clock B output maps to Serval RCVRD_CLK1
// The recovered clock src is selected from the Serdes type (1G or 6G) and the instance number.
// The function srvl_serdes_inst_get returns correct serdes type and instance depending on the actual port muxing.
static vtss_rc srvl_synce_clock_in_set(vtss_state_t *vtss_state, const u32 clk_port)
{
    vtss_synce_clock_in_t *conf = &vtss_state->synce.in_conf[clk_port];
    vtss_serdes_mode_t    serdes_mode = vtss_state->port.serdes_mode[conf->port_no];
    BOOL                  serdes6g;
    u32                   serdes_instance, common_cfg = 0, common_mask, mask, sq_mask;
    i32                   new_chip_port = VTSS_CHIP_PORT(conf->port_no);
    i32                   clk_src = clk_port;

    VTSS_I("port_no %d, serdes mode %d", conf->port_no, serdes_mode);
    if (conf->enable) {
        /* Enable input clock configuration - now configuring the new (or maybe the same) input port */
        VTSS_I("mux_mode %d", vtss_state->init_conf.mux_mode);
        if (VTSS_RC_OK == srvl_serdes_inst_get(vtss_state, new_chip_port, &serdes_instance, &serdes6g)) {
            mask = (1<<serdes_instance);
            if (serdes6g) {
                sq_mask = VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_ENA;
                common_mask = (sq_mask);
                common_cfg = ((conf->squelsh ? sq_mask : 0));
                if (serdes_instance < SRVL_SERDES_INST_NONE) {
                    clk_src = 8 + serdes_instance;
                } else {
                    clk_src = clk_port;
                }
                VTSS_RC(srvl_sd6g_lock(vtss_state));
                VTSS_RC(srvl_sd6g_read(vtss_state, mask)); /* Readback the 6G common config register */
                VTSS_I("enable 6G   instance %u  common_cfg %X", serdes_instance, common_cfg);
                SRVL_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, common_cfg, common_mask);
                VTSS_RC(srvl_sd6g_write(vtss_state, mask)); /* transfer 6G common config register */
                VTSS_RC(srvl_sd6g_unlock(vtss_state));
            } else {
                sq_mask = VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_ENA;
                common_mask = sq_mask;
                common_cfg = conf->squelsh ? sq_mask : 0;
                if (srvl_port_is_internal_phy(new_chip_port) && serdes_mode == VTSS_SERDES_MODE_SGMII) {
                    // if internal phy operating in SGMII mode, use PHY recovered clock, otherwise use serdes recovered clock
                    clk_src = clk_port;
                } else {
                    if (serdes_instance < SRVL_SERDES_INST_NONE) {
                        clk_src = 2 + serdes_instance;
                    } else {
                        clk_src = clk_port;
                    }
                }
                VTSS_RC(srvl_sd1g_read(vtss_state, mask)); /* Readback the 1G common config register */
                VTSS_I("enable 1G   instance %u  common_cfg %X", serdes_instance, common_cfg);
                SRVL_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, common_cfg, common_mask);
                VTSS_RC(srvl_sd1g_write(vtss_state, mask));     /* transfer 1G common config register */
            }
            vtss_state->synce.old_port_no[clk_port] = new_chip_port;
        } else {
            VTSS_E("could not get serdes instance for port %d", new_chip_port);
        }
    }
    VTSS_I("clk_port %d new_chip_port %u clk_src %d  enable %d squelch %d",
           clk_port, new_chip_port, clk_src, conf->enable, conf->squelsh);
    SRVL_WRM(VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(clk_port),
             VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_SRC(clk_src) |
                (conf->enable ? VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA : 0),
             VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RCVRD_CLK_SRC |
                VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RCVRD_CLK_ENA);
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Port control
 * ================================================================= */

vtss_rc vtss_srvl_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_max_tags_t  max_tags = vtss_state->port.conf[port_no].max_tags;
    vtss_vlan_port_type_t vlan_type = vtss_state->l2.vlan_port_conf[port_no].port_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    u32                   tgt = VTSS_TO_DEV(port);
    u32                   etype, double_ena, single_ena;

    /* S-ports and VLAN unaware ports both suport 0x88a8 (in addition to 0x8100) */
    etype = (vlan_type == VTSS_VLAN_PORT_TYPE_S_CUSTOM ? vtss_state->l2.vlan_conf.s_etype :
             vlan_type == VTSS_VLAN_PORT_TYPE_C ? VTSS_ETYPE_TAG_C : VTSS_ETYPE_TAG_S);
    single_ena = (max_tags == VTSS_PORT_MAX_TAGS_NONE ? 0 : 1);
    double_ena = (max_tags == VTSS_PORT_MAX_TAGS_TWO ? 1 : 0);
    
    SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG(tgt), 
            VTSS_F_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(etype) |
            (double_ena ? VTSS_F_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_DBL_AWR_ENA : 0) |
            (single_ena ? VTSS_F_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_AWR_ENA : 0) |
            VTSS_F_DEV_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA);
    return VTSS_RC_OK;
}

static vtss_rc srvl_miim_read_write(vtss_state_t *vtss_state,
                                    BOOL read, 
                                    u32 miim_controller, 
                                    u8 miim_addr, 
                                    u8 addr, 
                                    u16 *value, 
                                    BOOL report_errors)
{
    u32 data, reg_cmd, reg_status, reg_data;

    reg_cmd = VTSS_DEVCPU_GCB_MIIM_MII_CMD(miim_controller);
    reg_status = VTSS_DEVCPU_GCB_MIIM_MII_STATUS(miim_controller);
    reg_data = VTSS_DEVCPU_GCB_MIIM_MII_DATA(miim_controller);

    /* Enqueue MIIM operation to be executed */
    SRVL_WR(reg_cmd,
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(miim_addr) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(addr) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(*value) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(read ? 2 : 1));
    
    /* Wait for MIIM operation to finish */
    do {
        SRVL_RD(reg_status, &data);
    } while (data & VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_BUSY);
    
    if (read) {
        SRVL_RD(reg_data, &data);
        if (data & VTSS_F_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS(3))
            return VTSS_RC_ERROR;
        *value = VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(data);
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_miim_read(vtss_state_t *vtss_state,
                              vtss_miim_controller_t miim_controller, 
                              u8 miim_addr, 
                              u8 addr, 
                              u16 *value, 
                              BOOL report_errors)
{
    return srvl_miim_read_write(vtss_state, TRUE, miim_controller, miim_addr, addr, value, report_errors);
}

static vtss_rc srvl_miim_write(vtss_state_t *vtss_state,
                               vtss_miim_controller_t miim_controller, 
                               u8 miim_addr, 
                               u8 addr, 
                               u16 value, 
                               BOOL report_errors)
{
    return srvl_miim_read_write(vtss_state, FALSE, miim_controller, miim_addr, addr, &value, report_errors);
}

#define PHY_CMD_WRITE    1 /* 10G: Write */
#define PHY_CMD_READ_INC 2 /* 10G: Read and increment */
#define PHY_CMD_READ     3 /* 10G: Read */

static vtss_rc srvl_mmd_cmd(vtss_state_t *vtss_state,
                            u32 cmd,
                            u32 miim_controller,
                            u8 miim_addr,
                            u8 mmd,
                            u16 addr,
                            u16 *value,
                            BOOL report_errors)
{
    u32 data, reg_cmd, reg_status, reg_data, reg_cfg;
    vtss_rc rc = VTSS_RC_OK;

    reg_cmd = VTSS_DEVCPU_GCB_MIIM_MII_CMD(miim_controller);
    reg_status = VTSS_DEVCPU_GCB_MIIM_MII_STATUS(miim_controller);
    reg_data = VTSS_DEVCPU_GCB_MIIM_MII_DATA(miim_controller);
    reg_cfg = VTSS_DEVCPU_GCB_MIIM_MII_CFG(miim_controller);

    /* Switch to clause 45 */
    SRVL_WRM(reg_cfg,
             VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(0),
             VTSS_M_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD);

    /* Enqueue address set operation */
    SRVL_WR(reg_cmd,
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(miim_addr) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(mmd) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(addr) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(0));

    /* Wait for MIIM operation to finish */
    do {
        SRVL_RD(reg_status, &data);
    } while (data & VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_BUSY);

    /* Enqueue read or write operation */
    SRVL_WR(reg_cmd,
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(miim_addr) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(mmd) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(*value) |
            VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(cmd));

    /* Wait for MIIM operation to finish */
    do {
        SRVL_RD(reg_status, &data);
    } while (data & VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_BUSY);

    if (cmd == PHY_CMD_READ || cmd == PHY_CMD_READ_INC) {
        SRVL_RD(reg_data, &data);
        if (data & VTSS_F_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS(3)) {
            rc = VTSS_RC_ERROR;
        }
        else {
            *value = VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(data);
        }
    }

    /* Switch back to clause 22 */
    SRVL_WRM(reg_cfg,
             VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(1),
             VTSS_M_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD);

    return rc;
}



static vtss_rc srvl_mmd_read(vtss_state_t *vtss_state,
                             vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                             u16 addr, u16 *value, BOOL report_errors)
{
    return srvl_mmd_cmd(vtss_state, PHY_CMD_READ, miim_controller, miim_addr, mmd, addr, value, report_errors);
}

static vtss_rc srvl_mmd_write(vtss_state_t *vtss_state,
                              vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                              u16 addr, u16 value, BOOL report_errors)
{
    return srvl_mmd_cmd(vtss_state, PHY_CMD_WRITE, miim_controller, miim_addr, mmd, addr, &value, report_errors);
}

static vtss_rc srvl_mmd_read_inc(vtss_state_t *vtss_state,
                                 vtss_miim_controller_t miim_controller, u8 miim_addr, u8 mmd,
                                 u16 addr, u16 *buf, u8 count, BOOL report_errors)
{
    while (count > 1) {
        VTSS_RC(srvl_mmd_cmd(vtss_state, PHY_CMD_READ_INC, miim_controller, miim_addr, mmd, addr, buf, report_errors));
        buf++;
        count--;
    }
    return VTSS_RC_OK;
}


/*
 * Watermark encode/decode for QSYS:RES_CTRL:RES_CFG.WM_HIGH
 * Bit 8:   Unit; 0:1, 1:16
 * Bit 7-0: Value to be multiplied with unit
 */
#define MULTIPLIER_BIT 256
static u16 wm_enc(u16 value)
{
    if (value >= MULTIPLIER_BIT) {
        return MULTIPLIER_BIT + value / 16;
    }
    return value;
}

static u32 wm_dec(u32 value)
{
    if (value > MULTIPLIER_BIT) { 
        return (value - MULTIPLIER_BIT) * 16;
    }        
    return value;
}

u32 vtss_srvl_wm_high_get(vtss_state_t *vtss_state, u32 queue)
{
    u32 wm_high;
    SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((queue + 216)), &wm_high); /* Shared ingress high watermark for queue - common for all dpls */
    return wm_dec(wm_high) * SRVL_BUFFER_CELL_SZ; /* Convert from 60 byte chunks to bytes */
}

static vtss_rc srvl_port_pfc(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u32 q, pfc_mask = 0;
    u32 spd = (conf->speed == VTSS_SPEED_10M ? 3 :
               conf->speed == VTSS_SPEED_100M ? 2 :
               conf->speed == VTSS_SPEED_1G ? 1 : 0);

    for (q = 0; q < VTSS_PRIOS; q++) {
        pfc_mask |= conf->flow_control.pfc[q] ? (1 << q) : 0;
    }
       
    /* Rx enable/disable */
    SRVL_WRM(VTSS_ANA_PFC_PFC_CFG(port), 
             VTSS_F_ANA_PFC_PFC_CFG_RX_PFC_ENA(pfc_mask) |
             VTSS_F_ANA_PFC_PFC_CFG_FC_LINK_SPEED(spd),
             VTSS_M_ANA_PFC_PFC_CFG_RX_PFC_ENA |
             VTSS_M_ANA_PFC_PFC_CFG_FC_LINK_SPEED);
    
    /* Forward 802.1Qbb pause frames to analyzer */
    SRVL_WRM(VTSS_DEV_PORT_MODE_PORT_MISC(VTSS_TO_DEV(port)), 
             VTSS_BOOL(pfc_mask) ? VTSS_F_DEV_PORT_MODE_PORT_MISC_FWD_CTRL_ENA : 0,
             VTSS_F_DEV_PORT_MODE_PORT_MISC_FWD_CTRL_ENA);
 
    /*  PFC Tx enable is done after the core is enabled */

    return VTSS_RC_OK;
}

static vtss_rc srvl_port_fc_setup(vtss_state_t *vtss_state, u32 port, vtss_port_conf_t *conf)
{
    u8                *mac, q;
    BOOL              pfc = 0, fc_gen = conf->flow_control.generate, fc_obey = conf->flow_control.obey;
    vtss_port_speed_t speed = conf->speed;
    vtss_port_no_t    port_no;
    u32               rsrv_raw, rsrv_total = 0, atop_wm, tgt = VTSS_TO_DEV(port);
    u32               pause_start = 0x7ff, sum_port, sum_cpu, val;
    u32               pause_stop  = 0xfff;
    u32               rsrv_raw_fc_jumbo = 40000;
    u32               rsrv_raw_no_fc_jumbo = 12000;
    u32               rsrv_raw_fc_no_jumbo = 13662; /* 9 x 1518 */
    u32               link_speed = (speed == VTSS_SPEED_10M ? 3 :
                                    speed == VTSS_SPEED_100M ? 2 :
                                    speed == VTSS_SPEED_1G ? 1 : 0);

    for (q = 0; q < VTSS_PRIOS; q++) {
        if (conf->flow_control.pfc[q]) {
            pfc = 1;
            if (fc_gen || fc_obey) {
                VTSS_E("802.3X FC and 802.1Qbb PFC cannot both be enabled, chip port %u",port);
                return VTSS_RC_ERROR;
            }
        }
    }
    /* Configure 802.1Qbb PFC */
    VTSS_RC(srvl_port_pfc(vtss_state, port, conf));

    if (pfc) {
        // Each port can use this as max before tail dropping starts
        rsrv_raw = rsrv_raw_fc_no_jumbo;
    } else {
        /* Standard Flowcontrol */

        // pause_start must be greater than reserved memory for
        //    IGR_WM(PORT) + IGR_WM(PORT, PRIO)
        // and
        //    EGR_WM(CPUPORT_0) + EGR_WM(CPUPORT_0, PRIO)
        // The latter is required in order not to transmit pause frames when the
        // CPU is congested.

        // Per port:
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG(  0 /* ingress */ + 224 /* per port */ + port),                 &sum_port);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG(512 /* egress  */ + 224 /* per port */ + VTSS_CHIP_PORT_CPU_0), &sum_cpu);

        // Per prio:
        for (q = 0; q < VTSS_PRIOS; q++) {
            SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG(  0 /* ingress */ + port *                 VTSS_PRIOS /* per prio */ + q), &val);
            sum_port += val;

            SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG(512 /* egress  */ + VTSS_CHIP_PORT_CPU_0 * VTSS_PRIOS /* per prio */+ q), &val);
            sum_cpu += val;
        }

        pause_start = MAX(sum_port, sum_cpu);

        // Allow for a standard frame.
        pause_start += VTSS_MAX_FRAME_LENGTH_STANDARD / SRVL_BUFFER_CELL_SZ;

        if (conf->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
            if (fc_gen) { /* FC and jumbo enabled*/
                pause_stop  = 177;     /* 7 x 1518 / 60 */
                rsrv_raw    = rsrv_raw_fc_jumbo;
            } else {      /* FC disabled, jumbo enabled */
                rsrv_raw = rsrv_raw_no_fc_jumbo;
            }
        } else {
            if (fc_gen) { /* FC enabled, jumbo disabled */
                pause_stop  = 101;    /* 4 x 1518 / 60 */
                rsrv_raw    = rsrv_raw_fc_no_jumbo;
            } else {
                rsrv_raw    = 0;
            }
        }
    }

    /* Set Pause WM hysteresis*/
    SRVL_WR(VTSS_SYS_PAUSE_CFG_PAUSE_CFG(port),
            VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(wm_enc(pause_start)) |
            VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(pause_stop) |
            (fc_gen ? VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA : 0));
    
    /* Set SMAC of Pause frame */
    mac = &conf->flow_control.smac.addr[0];
    SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG(tgt), (mac[0]<<16) | (mac[1]<<8) | mac[2]);
    SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG(tgt), (mac[3]<<16) | (mac[4]<<8) | mac[5]);

    /* Enable/disable FC incl. pause value and zero pause */
    SRVL_WR(VTSS_SYS_PAUSE_CFG_MAC_FC_CFG(port),
            VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_FC_LINK_SPEED(link_speed) |
            VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_FC_LATENCY_CFG(7) |
            VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_ZERO_PAUSE_ENA |
            (fc_obey ? VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_RX_FC_ENA : 0) |
            VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_PAUSE_VAL_CFG(pfc ? 0xff : 0xffff));
    SRVL_WRM(VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE(port),
             fc_gen ? 0 : VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE,
             VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE);

    /* Calculate the total reserved space for all ports */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        conf = &vtss_state->port.conf[port_no];
        fc_gen = conf->flow_control.generate;
        if (conf->max_frame_length > VTSS_MAX_FRAME_LENGTH_STANDARD) {
            if (fc_gen) {
                rsrv_total += rsrv_raw_fc_jumbo;
            } else {
                rsrv_total += rsrv_raw_no_fc_jumbo;
            }
        } else if (fc_gen) {
            rsrv_total += rsrv_raw_fc_no_jumbo;
        }
    }
    atop_wm = (SRVL_BUFFER_MEMORY - rsrv_total)/SRVL_BUFFER_CELL_SZ;

    /*  When 'port ATOP' and 'common ATOP_TOT' are exceeded, tail dropping is activated on port */
    SRVL_WR(VTSS_SYS_PAUSE_CFG_ATOP_TOT_CFG, wm_enc(atop_wm));
    SRVL_WR(VTSS_SYS_PAUSE_CFG_ATOP(port), wm_enc(rsrv_raw / SRVL_BUFFER_CELL_SZ));

    return VTSS_RC_OK;
}

static vtss_rc srvl_port_conf_get(vtss_state_t *vtss_state,
                                  const vtss_port_no_t port_no, vtss_port_conf_t *const conf)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u32 tgt = VTSS_TO_DEV(port);
    u32 value, link_speed;

    /* Speed */
    SRVL_RD(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt), &value);
    link_speed = VTSS_X_DEV_PORT_MODE_CLOCK_CFG_LINK_SPEED(value);
    conf->speed = (link_speed == 3 ? VTSS_SPEED_10M :
                   link_speed == 2 ? VTSS_SPEED_100M :
                   vtss_state->port.conf[port_no].speed);

    /* Duplex */
    SRVL_RD(VTSS_DEV_MAC_CFG_STATUS_MAC_MODE_CFG(tgt), &value);
    conf->fdx = VTSS_BOOL(value & VTSS_F_DEV_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA);

    /* Power down */
    SRVL_RD(VTSS_DEV_MAC_CFG_STATUS_MAC_ENA_CFG(tgt), &value);
    conf->power_down = (value & VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA ? 0 : 1);

    /* Flow control */
    SRVL_RD(VTSS_SYS_PAUSE_CFG_PAUSE_CFG(port), &value);
    conf->flow_control.generate = VTSS_BOOL(value & VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA);
    SRVL_RD(VTSS_SYS_PAUSE_CFG_MAC_FC_CFG(port), &value);
    conf->flow_control.obey = VTSS_BOOL(value & VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_RX_FC_ENA);

    return VTSS_RC_OK;
}

static BOOL srvl_port_is_internal_phy(u32 chip_port)
{
    return (chip_port < 4); // cport 0-3 is internal phy ports
}

static vtss_rc srvl_serdes_cfg(vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_serdes_mode_t mode)
{
    u32  inst, addr, port = VTSS_CHIP_PORT(port_no);
    BOOL serdes6g;
    vtss_state->port.serdes_mode[port_no] = mode;
    VTSS_RC(srvl_serdes_inst_get(vtss_state, port, &inst, &serdes6g));
    addr = (1 << inst);
    if (inst == SRVL_SERDES_INST_NONE) {
        /* No SerDes setup */
    } else if (serdes6g) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        VTSS_RC(srvl_sd6g_cfg(vtss_state, port_no, addr));
#endif
    } else {
        VTSS_RC(srvl_sd1g_cfg(vtss_state, port_no, addr));
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_conf_t       *conf = &vtss_state->port.conf[port_no];
    u32                    port = VTSS_CHIP_PORT(port_no);
    u32                    link_speed, value, tgt = VTSS_TO_DEV(port), delay = 0;
    u32                    q, pfc_mask = 0;
    vtss_port_frame_gaps_t gaps;
    vtss_port_speed_t      speed = conf->speed;
    BOOL                   fdx = conf->fdx, disable = conf->power_down;
    BOOL                   sgmii = 0, if_100fx = 0;
    vtss_serdes_mode_t     mode = VTSS_SERDES_MODE_SGMII;   
    u32                    cnt[2];

    // Enable/disable the internal PHY
    if (srvl_port_is_internal_phy(port)) {
        SRVL_WRM_CTL(VTSS_DEVCPU_GCB_PHY_PHY_CFG,
                     conf->if_type == VTSS_PORT_INTERFACE_SGMII,
                     VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_ENA(VTSS_BIT(port)));
    }

    /* Verify speed and interface type */
    switch (speed) {
    case VTSS_SPEED_10M:
        link_speed = 3;
        break;
    case VTSS_SPEED_100M:
        link_speed = 2;
        break;
    case VTSS_SPEED_1G:
    case VTSS_SPEED_2500M:
        link_speed = 1;
        break;
    default:
        VTSS_E("illegal speed:%d, port %u", speed, port);
        return VTSS_RC_ERROR;
    }

    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        disable = 1;
        break;
    case VTSS_PORT_INTERFACE_INTERNAL:
    case VTSS_PORT_INTERFACE_RGMII:
    case VTSS_PORT_INTERFACE_SGMII:
        sgmii = 1;
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        mode = VTSS_SERDES_MODE_QSGMII;
        if ((port % 4) == 0) {
            // BZ23738
            BOOL p3_in_map = FALSE;
            SRVL_WRM_CLR(VTSS_DEV_PORT_MODE_CLOCK_CFG(VTSS_TO_DEV((port + 1))), VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_TX_RST);
            SRVL_WRM_CLR(VTSS_DEV_PORT_MODE_CLOCK_CFG(VTSS_TO_DEV((port + 2))), VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_TX_RST);
            for (u32 p = VTSS_PORT_NO_START; p < vtss_state->port_count; p++) {
                if (vtss_state->port.map[p].chip_port == port + 3)
                    p3_in_map = TRUE;
            }
            if (!p3_in_map) {
                SRVL_WR(VTSS_DEV_PORT_MODE_CLOCK_CFG(VTSS_TO_DEV((port + 3))), 0x1);
            } else {
                SRVL_WRM_CLR(VTSS_DEV_PORT_MODE_CLOCK_CFG(VTSS_TO_DEV((port + 3))), VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_TX_RST);
            }
        }
        break;
    case VTSS_PORT_INTERFACE_SERDES:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_2500M) {
            VTSS_E("illegal speed, port %u", port);
            return VTSS_RC_ERROR;
        }
        mode = (speed == VTSS_SPEED_2500M ? VTSS_SERDES_MODE_2G5 : VTSS_SERDES_MODE_1000BaseX);
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
        mode = VTSS_SERDES_MODE_1000BaseX;
        sgmii = 1;        
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        if (speed != VTSS_SPEED_1G && speed != VTSS_SPEED_2500M) {
            VTSS_E("illegal speed, port %u", port);
            return VTSS_RC_ERROR;
        }
        mode = (speed == VTSS_SPEED_2500M ? VTSS_SERDES_MODE_2G5 : VTSS_SERDES_MODE_1000BaseX);
        break;
    default:
        VTSS_E("illegal interface, port %u", port);
        return VTSS_RC_ERROR;
    }
    if (conf->loop == VTSS_PORT_LOOP_PCS_HOST) {
        mode = VTSS_SERDES_MODE_TEST_MODE;
    }

    if (disable) {
        /* The port is not powered down as frames still needs to be forwarded to an up-mep */
        /* Instead the Serdes Macro is configured to Idle mode  */

        // Loopback is still supported during power down
        SRVL_WRM_CTL(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LB_CFG(tgt), 
                     conf->loop == VTSS_PORT_LOOP_PCS_HOST, 
                     VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA);

        // Notify link partner
        srvl_port_clause_37_control_set(vtss_state, port_no);

        if (conf->if_type != VTSS_PORT_INTERFACE_QSGMII) {
            VTSS_RC(srvl_serdes_cfg(vtss_state, port_no, VTSS_SERDES_MODE_IDLE));
        }
        return VTSS_RC_OK; // Nothing else needs to be disabled
    }

    /* Enable the Serdes if disabled */
    if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_DISABLE) {
        VTSS_RC(srvl_serdes_cfg(vtss_state, port_no, mode));
    }

    /* Store counters (Workaround for BZ17386) */
    SRVL_WR(VTSS_SYS_SYSTEM_STAT_CFG, VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_VIEW(port));
    SRVL_RD(VTSS_SYS_STAT_CNT(0x40), &cnt[0]); // tx_bytes
    SRVL_RD(VTSS_SYS_STAT_CNT(0x41), &cnt[1]); // tx_unicast

    /* ********************************* */
    /* Port disable and flush procedure: */
    /* ********************************* */
    /* 1: Reset the PCS Rx clock domain  */
    SRVL_WRM_SET(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt),
                 VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PCS_RX_RST);

    /* 2: Disable MAC frame reception */
    SRVL_WRM_CLR(VTSS_DEV_MAC_CFG_STATUS_MAC_ENA_CFG(tgt),
                 VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA);

    /* 3: Disable traffic being sent to or from switch port */
    SRVL_WRM_CLR(VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE(port),
                 VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);

    /* 4: Disable dequeuing from the egress queues  */
    SRVL_WRM_SET(VTSS_QSYS_SYSTEM_PORT_MODE(port),
                VTSS_F_QSYS_SYSTEM_PORT_MODE_DEQUEUE_DIS);

    /* 5: Disable Flowcontrol */
    SRVL_WRM_CLR(VTSS_SYS_PAUSE_CFG_PAUSE_CFG(port),  VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA);

    /* 5.1: Disable PFC */
    SRVL_WRM(VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE(port),
             VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_TX_PFC_ENA(0),
             VTSS_M_QSYS_SYSTEM_SWITCH_PORT_MODE_TX_PFC_ENA)

    /* 6: Wait a worst case time 8ms (jumbo/10Mbit) */
    VTSS_MSLEEP(8);

    /* 7: Disable HDX backpressure (Bugzilla 3203) */
    SRVL_WRM_CLR(VTSS_SYS_SYSTEM_FRONT_PORT_MODE(port), 
                 VTSS_F_SYS_SYSTEM_FRONT_PORT_MODE_HDX_MODE);
   
    /* 8: Flush the queues accociated with the port */
    SRVL_WRM_SET(VTSS_REW_PORT_PORT_CFG(port), 
                 VTSS_F_REW_PORT_PORT_CFG_FLUSH_ENA);

    /* 9: Enable dequeuing from the egress queues */
    SRVL_WRM_CLR(VTSS_QSYS_SYSTEM_PORT_MODE(port),
                VTSS_F_QSYS_SYSTEM_PORT_MODE_DEQUEUE_DIS);

    /* 10: Wait until flushing is complete */
    do { 
        SRVL_RD(VTSS_QSYS_SYSTEM_SW_STATUS(port), &value);
        VTSS_MSLEEP(1);            
        delay++;
        if (delay == 2000) {
            VTSS_E("Rev 3. Flush timeout chip port %u",port);
            break;
        }
    } while (value & VTSS_M_QSYS_SYSTEM_SW_STATUS_EQ_AVAIL);

    /* 11: Reset the Port and MAC clock domains */
    SRVL_WRM_CLR(VTSS_DEV_MAC_CFG_STATUS_MAC_ENA_CFG(tgt),
            VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA); /* Bugzilla#19076 */
    SRVL_WRM_SET(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt),
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PORT_RST);
    VTSS_MSLEEP(1);
    SRVL_WRM_SET(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt),
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_MAC_TX_RST |
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_MAC_RX_RST |
            VTSS_F_DEV_PORT_MODE_CLOCK_CFG_PORT_RST);

    /* 12: Clear flushing */
    SRVL_WRM_CLR(VTSS_REW_PORT_PORT_CFG(port), VTSS_F_REW_PORT_PORT_CFG_FLUSH_ENA);

    /* The port is disabled and flushed, now set up the port in the new operating mode */

    /* Re-Configure the Serdes macros */
    if (mode != vtss_state->port.serdes_mode[port_no]) {
        VTSS_RC(srvl_serdes_cfg(vtss_state, port_no, mode));
    }

    /*  Restore counters (Workaround for BZ17386) */
    SRVL_WR(VTSS_SYS_STAT_CNT(0x40), cnt[0]);
    SRVL_WR(VTSS_SYS_STAT_CNT(0x41), cnt[1]);

    /* Bugzilla 4388: disabling frame aging when in HDX */
    SRVL_WRM_CTL(VTSS_REW_PORT_PORT_CFG(port), !fdx, VTSS_F_REW_PORT_PORT_CFG_AGE_DIS);

    /* GIG/FDX mode */
    if (fdx) {
        value = VTSS_F_DEV_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA;
        if (speed == VTSS_SPEED_1G || speed == VTSS_SPEED_2500M) {
            value |= VTSS_F_DEV_MAC_CFG_STATUS_MAC_MODE_CFG_GIGA_MODE_ENA;
        }
    } else {        
        SRVL_WRM_SET(VTSS_SYS_SYSTEM_FRONT_PORT_MODE(port), 
                     VTSS_F_SYS_SYSTEM_FRONT_PORT_MODE_HDX_MODE);
        value = conf->flow_control.obey ? 0x100 : 0; /* FC_WORD_SYNC_ENA=1 for HDX/FC for Rev B chip */
    }
   
    VTSS_N("conf->frame_length_chk:%d", conf->frame_length_chk);

    /* Configure framelength check (from ethertype / length field) */
    SRVL_WRM(VTSS_DEV_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(tgt), 
             conf->frame_length_chk ? VTSS_F_DEV_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA : 0,
             VTSS_F_DEV_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA);

    SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_MODE_CFG(tgt), value);
    
    /* Default gaps */
    gaps.fdx_gap = 15; // Serval SGMII IF 
    if (speed == VTSS_SPEED_1G || speed == VTSS_SPEED_2500M) {
        gaps.fdx_gap = 5;
    } else if (srvl_port_is_internal_phy(port) &&
               (speed == VTSS_SPEED_100M || speed == VTSS_SPEED_10M) &&
               (conf->if_type != VTSS_PORT_INTERFACE_SGMII_CISCO)     /* cport 0-3 can be the Cu SFP in combo mode */) {
        // BZ#21738 - MINI PHY ports receive more broadcast traffic rate when speed is 10MHDX/100MHDX
        // BZ#22645 - Ocelot: Ferret Ports (5-8) receive more broadcast traffic rate than speed of the port with 64 frames
        gaps.fdx_gap = 16;
    }

    gaps.hdx_gap_1 = 0;
    gaps.hdx_gap_2 = 0;    
    if (!fdx) {
        gaps.hdx_gap_1 = 5;
        gaps.hdx_gap_2 = 5;
    }

    /* Non default gaps */
    if (conf->frame_gaps.hdx_gap_1 != VTSS_FRAME_GAP_DEFAULT) 
        gaps.hdx_gap_1 = conf->frame_gaps.hdx_gap_1;
    if (conf->frame_gaps.hdx_gap_2 != VTSS_FRAME_GAP_DEFAULT)
        gaps.hdx_gap_2 = conf->frame_gaps.hdx_gap_2;
    if (conf->frame_gaps.fdx_gap != VTSS_FRAME_GAP_DEFAULT)
        gaps.fdx_gap = conf->frame_gaps.fdx_gap;
    
    /* Set MAC IFG Gaps */
    SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_IFG_CFG(tgt), 
            VTSS_F_DEV_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG(gaps.fdx_gap) |
            VTSS_F_DEV_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1(gaps.hdx_gap_1) |
            VTSS_F_DEV_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2(gaps.hdx_gap_2));
    
    /* Load seed and set MAC HDX late collision */
    value = ((conf->exc_col_cont ? 
              VTSS_F_DEV_MAC_CFG_STATUS_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA : 0) | 
             VTSS_F_DEV_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS(67));
    SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_HDX_CFG(tgt), 
            value | VTSS_F_DEV_MAC_CFG_STATUS_MAC_HDX_CFG_SEED_LOAD);
    VTSS_NSLEEP(1000);
    SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_HDX_CFG(tgt), value);

    /* Disable HDX fast control */
    SRVL_WRM_SET(VTSS_DEV_PORT_MODE_PORT_MISC(tgt), VTSS_F_DEV_PORT_MODE_PORT_MISC_HDX_FAST_DIS);

    /* PCS settings for 100fx/SGMII/SERDES */
    if (if_100fx) {
        /* 100FX PCS */                    
        SRVL_WRM(VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                 (disable ? 0 : VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA) |
                 (conf->sd_internal ? 0 : VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL) |
                 (conf->sd_active_high ? VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_POL : 0) |
                 (conf->sd_enable ? VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA : 0),
                 VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA | 
                 VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_SEL |
                 VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_POL |
                 VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA);
    } else {
        /* Disable 100FX */
        SRVL_WRM_CLR(VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                     VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_PCS_ENA);

        /* Choose SGMII or Serdes PCS mode */
        SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_MODE_CFG(tgt), 
                (sgmii ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_MODE_CFG_SGMII_MODE_ENA : 0));
        
        if (sgmii) {
            /* Set whole register */
            SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                    VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA);
        } else {
            /* Clear specific bit only */
            SRVL_WRM_CLR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                         VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA);
        }
        
        SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
                (conf->sd_active_high ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_POL : 0) |
                (conf->sd_enable ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA : 0) |
                (conf->sd_internal ? 0 : VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_SEL));
        
        /* Enable/disable PCS */
        SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_CFG(tgt), 
                disable ? 0 : VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_CFG_PCS_ENA);
        
        if (conf->if_type == VTSS_PORT_INTERFACE_SGMII) {
            SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt), 0);
        } else if (conf->if_type == VTSS_PORT_INTERFACE_SGMII_CISCO) {
            /* Complete SGMII aneg */
            SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG(tgt),
                    VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ADV_ABILITY(0x0001) |
                    VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_SW_RESOLVE_ENA |
                    VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_ENA |
                    VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT);
            /* Clear the sticky bits */
            SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);
            SRVL_WR(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), value);
        }
        //Update vtss_state database accordingly
        srvl_port_clause_37_control_get(vtss_state,port_no,&(vtss_state->port.clause_37[port_no]));
    }

    SRVL_WRM_CTL(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LB_CFG(tgt), 
                 conf->loop == VTSS_PORT_LOOP_PCS_HOST, 
                 VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_LB_CFG_TBI_HOST_LB_ENA);

    /* Set Max Length and maximum tags allowed */
    SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_MAXLEN_CFG(tgt), conf->max_frame_length);
    VTSS_RC(vtss_srvl_port_max_tags_set(vtss_state, port_no));

    if (!disable) {
        /* Enable MAC module */
        SRVL_WR(VTSS_DEV_MAC_CFG_STATUS_MAC_ENA_CFG(tgt), 
                VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA |
                VTSS_F_DEV_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA);
        
        /* Take MAC, Port, Phy (intern) and PCS (SGMII/Serdes) clock out of reset */
        SRVL_WR(VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt), 
                VTSS_F_DEV_PORT_MODE_CLOCK_CFG_LINK_SPEED(link_speed));

        /* Configure flow control */
        if (srvl_port_fc_setup(vtss_state, port, conf) != VTSS_RC_OK)
            return VTSS_RC_ERROR;
       
        /* Core: Enable port for frame transfer */
        SRVL_WRM_SET(VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE(port),
                     VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);

        /* Enable flowcontrol - must be done after flushing */
        if (conf->flow_control.generate) {   
            SRVL_WRM_SET(VTSS_SYS_PAUSE_CFG_MAC_FC_CFG(port), VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_TX_FC_ENA);
        }

        for (q = 0; q < VTSS_PRIOS; q++) {
            pfc_mask |= conf->flow_control.pfc[q] ? (1 << q) : 0;
        }

        if (pfc_mask > 0) {
            /*  Enable PFC Tx enable */
            SRVL_WRM(VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE(port),
                     VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_TX_PFC_ENA(pfc_mask),
                     VTSS_M_QSYS_SYSTEM_SWITCH_PORT_MODE_TX_PFC_ENA);
        }

        /* Notify QoS module about port configuration change */
        VTSS_RC(vtss_srvl_qos_port_conf_change(vtss_state, port_no, port, link_speed));
    }

    return VTSS_RC_OK;
}


static vtss_rc srvl_port_ifh_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32 port               = VTSS_CHIP_PORT(port_no);
    vtss_port_ifh_t *ifh = &vtss_state->port.ifh_conf[port_no];

     /* Enable/Disable IFH parsing upon injection - expecting to see No Prefix */
    SRVL_WRM(VTSS_SYS_SYSTEM_PORT_MODE(port), 
             VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR(ifh->ena_inj_header ? 1 : 0),
             VTSS_M_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR);
     /* Enable/Disable IFH parsing upon extraction - add long prefix */
    SRVL_WRM(VTSS_SYS_SYSTEM_PORT_MODE(port), 
             VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR(ifh->ena_xtr_header ? 3 : 0),
             VTSS_M_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR);
 
    return VTSS_RC_OK;
}

static vtss_rc srvl_port_status_get(vtss_state_t *vtss_state,
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

    switch (conf->if_type) {
    case VTSS_PORT_INTERFACE_100FX:
        /* Get the PCS status  */
        SRVL_RD(VTSS_DEV_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), &value);
        
        /* Link has been down if the are any error stickies */
        status->link_down = SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY, value) ||
                            SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY, value) ||
                            SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY, value) ||
                            SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_STATUS, value);

        /* The 'SSD_ERROR_STICKY' check has removed in changeset:88db8234280e86f69cde36b0089fc1c640677b04
         * Log message: Bugzilla#21121 - Corrected the value of Serdes1G cmv_term
         * And the 'SSD_ERROR_STICKY' check is ignored too on JR2 due to BZ#22236.
         * See the brief below.
         *
         * BZ#22236 - One of 10G port link with 100FX SFP goes down in J2-24 and J2-48 after traffic is started
         * When polling for link status several
         * sticky bits are checked.  If they are set then the link is considered down and
         * the port is removed from the forwarding mask. The SSD_ERROR_STICKY (Stream
         * Start Delimiter Error from FX100-PCS) was getting asserted on a 100FX/10G port,
         * but no frames are lost.
         * The logic owner (Alexander Kock) have looked at this but cannot explain this,
         * the frames should be dropped if the sticky is asserted.  As a workaround we
         * decided to remove this bit from the checking.
         * changeset: 23d0a0aefa70bf5a99f2cc071d6a6a25efb1bb85
         *
         * And then we found the workaround bring the new issue.
         * BZ#23095: Ports are blinking continuously when SFPs are inserted, without any cable connected
         * BZ#23096: 1Gig SFP ports are UP even after removing the SFPs
         */
         status->link_down |= SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY, value) ? 1 : 0;

        if (status->link_down) {
            SRVL_WR(VTSS_DEV_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), 0xFFFF);
            VTSS_MSLEEP(1); // BZ18779
            SRVL_RD(VTSS_DEV_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt), &value);
        }
        /* Link=1 if sync status=1 and no error stickies after a clear */
        status->link = SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_STATUS, value)      && 
                       SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SIGNAL_DETECT, value)    &&
                      !SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_LOST_STICKY, value) &&
                      !SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_FOUND_STICKY, value) &&
                      !SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_PCS_ERROR_STICKY, value) &&
                      !SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_FEF_STATUS, value);

        //BZ#23095/23096
        status->link &= (SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SYNC_STATUS, value) &&
                         !SRVL_BF(DEV_PCS_FX100_STATUS_PCS_FX100_STATUS_SSD_ERROR_STICKY, value)) ? 1 : 0;

        status->speed = VTSS_SPEED_100M; 
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        /* Get the PCS status */
        SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(tgt), &value);
        status->link = SRVL_BF(DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_LINK_STATUS, value);
        SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt), &value);
        VTSS_I("status->link:%d, status->link_down:%d", status->link, status->link_down);
        status->link_down = SRVL_BF(DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY, value);
        if (status->link_down) {
            /* The link has been down. Clear the sticky bit */
            SRVL_WRM_SET(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY(tgt),
                         VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_STICKY_LINK_DOWN_STICKY);
        }
        status->speed = VTSS_SPEED_2500M; 
        if (vtss_state->port.serdes_mode[port_no] != VTSS_SERDES_MODE_2G5) {
            status->speed = VTSS_SPEED_1G;
        }
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        status->link = 0;
        status->link_down = 0;
        break;
    default:
        return VTSS_RC_ERROR;
    }        
    status->fdx = 1;    
    return VTSS_RC_OK;
}

static vtss_rc srvl_port_counters_read(vtss_state_t                 *vtss_state,
                                       vtss_port_no_t               port_no,
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
    BOOL                               tx_aging_clear = clear;

    /* Setup counter view */
    SRVL_WR(VTSS_SYS_SYSTEM_STAT_CFG, VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_VIEW(port));

    base = 0x00;
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_octets, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_unicast, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_multicast, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_broadcast, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_shorts, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_fragments, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_jabbers, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_crc_align_errors, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_symbol_errors, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_64, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_65_127, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_128_255, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_256_511, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_512_1023, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_1024_1526, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_1527_max, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_pause, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_control, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_longs, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_classified_drops, clear));
    for (i = 0; i < VTSS_PRIOS; i++) 
        VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_red_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_green_class[i], clear));
    
    base = 0x40;
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_octets, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_unicast, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_multicast, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_broadcast, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_collision, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_drops, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_pause, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_64, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_65_127, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_128_255, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_256_511, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_512_1023, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_1024_1526, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_1527_max, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_green_class[i], clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_aging, tx_aging_clear));

    /* 32-bit Drop chip counters */
    base = 0x80;
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->dr_local, clear));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->dr_tail, clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->dr_yellow_class[i], clear));
    for (i = 0; i < VTSS_PRIOS; i++)
        VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->dr_green_class[i], clear));
   
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
        prop->rx_prio[i] = (c->rx_red_class[i].value + c->rx_yellow_class[i].value + c->rx_green_class[i].value);
        prop->tx_prio[i] = (c->tx_yellow_class[i].value + c->tx_green_class[i].value);
    }

    /* RMON Rx counters */
    rmon->rx_etherStatsDropEvents = c->dr_tail.value;

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
    for (i = 0; i < VTSS_PRIOS; i++) {
        rmon->tx_etherStatsDropEvents += (c->dr_yellow_class[i].value + c->dr_green_class[i].value);
    }
    rmon->tx_etherStatsOctets = c->tx_octets.value;
    rmon->tx_etherStatsPkts = 
        (c->tx_64.value + c->tx_65_127.value + c->tx_128_255.value + c->tx_256_511.value + 
         c->tx_512_1023.value + c->tx_1024_1526.value + c->tx_1527_max.value);
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
    if_group->ifInErrors = 
        (c->rx_crc_align_errors.value + c->rx_shorts.value + c->rx_fragments.value +
         c->rx_jabbers.value + c->rx_longs.value);
  
    /* Interfaces Group Tx counters */
    if_group->ifOutOctets = c->tx_octets.value;
    if_group->ifOutUcastPkts = c->tx_unicast.value;
    if_group->ifOutMulticastPkts = c->tx_multicast.value;
    if_group->ifOutBroadcastPkts = c->tx_broadcast.value;
    if_group->ifOutNUcastPkts = (c->tx_multicast.value + c->tx_broadcast.value);
    if_group->ifOutDiscards = rmon->tx_etherStatsDropEvents;
    if_group->ifOutErrors = (c->tx_drops.value + c->tx_aging.value);

    /* Ethernet-like counters */
    elike->dot3InPauseFrames = c->rx_pause.value + c->rx_control.value;
    elike->dot3OutPauseFrames = c->tx_pause.value;     

    /* Bridge counters */
    counters->bridge.dot1dTpPortInDiscards = (c->rx_classified_drops.value + c->dr_local.value);
    for (i = 0; i < VTSS_PRIOS; i++) {
        counters->bridge.dot1dTpPortInDiscards += c->rx_red_class[i].value;
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_port_basic_counters_get(vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no,
                                            vtss_basic_counters_t *const counters)
{
    u32                          base, *p = &base, port = VTSS_CHIP_PORT(port_no);
    vtss_port_luton26_counters_t *c = &vtss_state->port.counters[port_no].counter.luton26;

    /* Setup counter view */
    SRVL_WR(VTSS_SYS_SYSTEM_STAT_CFG, VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_VIEW(port));
    
    /* Rx Counters */
    base = 0x09; /* rx_64 */
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_64, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_65_127, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_128_255, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_256_511, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_512_1023, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_1024_1526, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->rx_1527_max, 0));

    /* Tx Counters */
    base = 0x47; /* tx_64 */
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_64, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_65_127, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_128_255, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_256_511, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_512_1023, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_1024_1526, 0));
    VTSS_RC(vtss_srvl_counter_update(vtss_state, p, &c->tx_1527_max, 0));

    /* Rx frames */
    counters->rx_frames = 
        (c->rx_64.value + c->rx_65_127.value + c->rx_128_255.value + c->rx_256_511.value + 
         c->rx_512_1023.value + c->rx_1024_1526.value + c->rx_1527_max.value);
    
    /* Tx frames */
    counters->tx_frames = 
        (c->tx_64.value + c->tx_65_127.value + c->tx_128_255.value + c->tx_256_511.value + 
         c->tx_512_1023.value + c->tx_1024_1526.value + c->tx_1527_max.value);

    return VTSS_RC_OK;
}

static vtss_rc srvl_port_counters_cmd(vtss_state_t                *vtss_state,
                                      const vtss_port_no_t        port_no, 
                                      vtss_port_counters_t *const counters, 
                                      BOOL                        clear)
{
    return srvl_port_counters_read(vtss_state,
                                   port_no,
                                   VTSS_CHIP_PORT(port_no),
                                   &vtss_state->port.counters[port_no].counter.luton26,
                                   counters,
                                   clear);
}

static vtss_rc srvl_port_counters_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return srvl_port_counters_cmd(vtss_state, port_no, NULL, 0);
}

static vtss_rc srvl_port_counters_clear(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return srvl_port_counters_cmd(vtss_state, port_no, NULL, 1);
}

static vtss_rc srvl_port_counters_get(vtss_state_t *vtss_state,
                                      const vtss_port_no_t port_no,
                                      vtss_port_counters_t *const counters)
{
    VTSS_MEMSET(counters, 0, sizeof(*counters));
    return srvl_port_counters_cmd(vtss_state, port_no, counters, 0);
}

static vtss_rc srvl_port_forward_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc srvl_port_test_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    u32                   inst, addr, port = VTSS_CHIP_PORT(port_no);
    BOOL                  serdes6g;
    vtss_port_lb_t        lb = vtss_state->port.test_conf[port_no].loopback;
    vtss_port_conf_t      *conf = &vtss_state->port.conf[port_no];
    u32                   tgt = VTSS_TO_DEV(port);

    if (srvl_serdes_inst_get(vtss_state, port, &inst, &serdes6g) != VTSS_RC_OK || inst == SRVL_SERDES_INST_NONE) {
        return VTSS_RC_OK;
    }

    addr = (1 << inst);
    if (serdes6g) {
        VTSS_RC(srvl_sd6g_cfg(vtss_state, port_no, addr));
    } else {
        VTSS_RC(srvl_sd1g_cfg(vtss_state, port_no, addr));
    }

        // Disable signal detect during loopback
    if (lb == VTSS_PORT_LB_DISABLED) {
        SRVL_WRM(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
                 0,
                 VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA);
        SRVL_WRM(VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                 0,
                 VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA);

    } else {
        SRVL_WRM(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG(tgt),
                 (conf->sd_enable ? VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA : 0),
                 VTSS_F_DEV_PCS1G_CFG_STATUS_PCS1G_SD_CFG_SD_ENA);
        SRVL_WRM(VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                 (conf->sd_enable ? VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA : 0),
                 VTSS_F_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG_SD_ENA);
    }
#endif
    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_wm_update(vtss_state_t *vtss_state)
{
    u32 q;

    /* Update BUF_PRIO_SHR_E sharing watermarks according to AN1121 Section 7 WRED Operation */
    for (q = 0; q < VTSS_PRIOS; q++) {
        if (vtss_state->qos.conf.red_v2[q][0].enable || vtss_state->qos.conf.red_v2[q][1].enable) {
            SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 512)), 0); /* WRED is enabled for DP0 or DP1 - set watermark to zero */
        } else {
            SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 512)), vtss_state->port.buf_prio_shr[q]); /* Restore initial value */
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_port_buf_conf_set(vtss_state_t *vtss_state)
{
    int q;
    u32 port, value;
#if defined(VTSS_ARCH_SERVAL_ORG)
    /* Setup watermarks for Serval-1 */
    u32 port_no, dp;
    u32 buf_q_rsrv_i, buf_q_rsrv_e, ref_q_rsrv_i, ref_q_rsrv_e, buf_prio_shr_i[8], buf_prio_shr_e[8], ref_prio_shr_i[8], ref_prio_shr_e[8];
    u32 buf_p_rsrv_i, buf_p_rsrv_e, ref_p_rsrv_i, ref_p_rsrv_e, buf_col_shr_i, buf_col_shr_e, ref_col_shr_i, ref_col_shr_e;
    u32 buf_prio_rsrv, ref_prio_rsrv, guaranteed, q_rsrv_mask, prio_mem, prio_ref, oversubscription_factor;
    BOOL prio_strict;

    /* This mode to be configurable by user somehow */
    /* Mode 0: Strict priorities. Higher priorities have right to use all shared before lower */
    /* Mode 1: Classes with equal memory rights */
    u32 shr_mode = 0;

    /***********************/
    /* Settings for mode 0 */
    /***********************/
    /* SYS::RES_CFG : 1024 watermarks for 1024000 byte shared buffer, unit is 60 byte */
    /* Is divided into 4 resource consumptions, ingress and egress memory (BUF) and ingress and egress frame reference (REF) blocks */   
    /* Queue reserved (q_rsrv) : starts at offset 0 within in each BUF and REF   */
    /* Prio shared (prio_shr)  : starts at offset 216 within in each BUF and REF */
    /* Port reserved (p_rsrv)  : starts at offset 224 within in each BUF and REF */
    /* Colour shared (col_shr) : starts at offset 254 within in each BUF and REF */

    /* Buffer values are in BYTES */ 
    buf_q_rsrv_i = 512;    /* Guarantees at least 1 MTU  */
    buf_p_rsrv_i = 0;      /* No additional ingress guarantees   */
    buf_q_rsrv_e = 3000;   /* Guarantees all QoS classes some space */
    buf_p_rsrv_e = 40960;  /* Guarantees a space to the egress ports */
    buf_col_shr_i = SRVL_BUFFER_MEMORY; /* Green color - disabled for now */
    buf_col_shr_e = SRVL_BUFFER_MEMORY; /* Green color - disabled for now */
    buf_prio_rsrv = 12288;  /* In the shared area, each priority is cut off 12kB before the others. Yellow colour is cut of 12kb before lowest */
    prio_strict   = TRUE;   /* The priorities are treated strict in the shared memory */

    /* Reference values in NUMBER of FRAMES */
    ref_q_rsrv_e = 10;     /* Number of frames that can be pending at each egress queue   */
    ref_q_rsrv_i = 10;     /* Number of frames that can be pending at each ingress queue  */
    ref_p_rsrv_e = 100;    /* Number of frames that can be pending shared between the QoS classes at egress */
    ref_p_rsrv_i = 20;     /* Number of frames that can be pending shared between the QoS classes at ingress */
    ref_col_shr_i = SRVL_BUFFER_REFERENCE; /* Green color - disabled for now */
    ref_col_shr_e = SRVL_BUFFER_REFERENCE; /* Green color - disabled for now */
    ref_prio_rsrv = 50;   /* Number of frames that can be pending for each class */

    /* The memory is oversubsrcribed by this factor (factor 1 = 100) */
    /* Oversubscription is possible (in some degree) because it's rare that all ports use their reserved space at the same time */
    oversubscription_factor = 100; /* No oversubscription */

    /****** User configured mode changes *************/

    /************/
    /* Mode 1   */
    /************/
    if (shr_mode == 1) {
        prio_strict     = FALSE; /* Each priority has its own share */
        buf_prio_rsrv   = 30000; /* 30kB set aside to each active priority */
        buf_p_rsrv_i    = 0;     /* No port reservation allowed in this mode */
        buf_p_rsrv_e    = 0;
        ref_prio_rsrv   = 200;  /* 200 frames set aside to each active priority */
        ref_p_rsrv_i    = 0;    /* No port reservation allowed in this mode */
        ref_p_rsrv_e    = 0;  
        oversubscription_factor = 200; /* Assume only half of the reserved memory is in use at any time */
    }
    /*************************************************/


    /* Note, the shared reserved space (buf_prio_shr_i, ref_prio_shr_i, buf_prio_shr_e, ref_prio_shr_e) is calulated based on above */

    /* The number of supported queues is given through the state structure                           */
    /* The supported queues (lowest to higest) are givin reserved buffer space as specified above.   */
    /* Frames in remaining queues (if any) are not getting any reserved space - but are allowed in the system.*/
    q_rsrv_mask = 0xff >> (8 - vtss_state->qos.conf.prios); 


    /* **************************************************  */
    /* BELOW, everything is calculated based on the above. */
    /* **************************************************  */

    /* Find the amount of guaranteeed space per port */
    guaranteed = buf_p_rsrv_i+buf_p_rsrv_e;
    for (q=0; q<VTSS_PRIOS; q++) {
        if (q_rsrv_mask & (1<<q)) 
            guaranteed+=(buf_q_rsrv_i+buf_q_rsrv_e);
    }

    prio_mem = SRVL_BUFFER_MEMORY - (vtss_state->port_count+1)*guaranteed*100/oversubscription_factor;

    /* Find the amount of guaranteeed frame references */
    guaranteed = ref_p_rsrv_i+ref_p_rsrv_e;
    for (q = 0; q < VTSS_PRIOS; q++) {
        if (q_rsrv_mask & (1 << q)) {
            guaranteed += (ref_q_rsrv_i + ref_q_rsrv_e);
        }
    }
    prio_ref = SRVL_BUFFER_REFERENCE - (vtss_state->port_count + 1) * guaranteed * 100 / oversubscription_factor;

    /* Configuring the prio watermarks */
    if (prio_strict) {
        for (q = vtss_state->qos.conf.prios - 1; q >= 0; q--) {
            buf_prio_shr_i[q] = prio_mem;
            ref_prio_shr_i[q] = prio_ref;
            buf_prio_shr_e[q] = prio_mem;
            ref_prio_shr_e[q] = prio_ref;

            prio_mem -= buf_prio_rsrv;
            prio_ref -= ref_prio_rsrv;
        }
        buf_col_shr_i = prio_mem - buf_prio_rsrv;
        buf_col_shr_e = prio_mem - buf_prio_rsrv;
        ref_col_shr_i = prio_ref - ref_prio_rsrv;
        ref_col_shr_e = prio_ref - ref_prio_rsrv;
    } else {
        /* Shared area per prio */
        for (q = 0; q < vtss_state->qos.conf.prios; q++) {
            buf_prio_shr_i[q] = buf_prio_rsrv;
            ref_prio_shr_i[q] = ref_prio_rsrv;
            buf_prio_shr_e[q] = buf_prio_rsrv;
            ref_prio_shr_e[q] = ref_prio_rsrv;
            prio_mem -= buf_prio_rsrv;
            prio_ref -= ref_prio_rsrv;
        }
        buf_col_shr_i = prio_mem;
        buf_col_shr_e = prio_mem;
        ref_col_shr_i = prio_ref;
        ref_col_shr_e = prio_ref;
        /* Use per priority shared areas */
        SRVL_WR(VTSS_QSYS_RES_QOS_ADV_RES_QOS_MODE, 0xff);
    }


    /* Configure reserved space for all QoS classes per port */
    for (port_no = 0; port_no <= vtss_state->port_count; port_no++) {
        if (port_no == vtss_state->port_count) {
            port = VTSS_CHIP_PORT_CPU;
        } else {
            port = VTSS_CHIP_PORT(port_no);
        }
        for (q = 0; q < VTSS_PRIOS; q++) {
            if (q_rsrv_mask&(1<<q)) {
                SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 0),   wm_enc(buf_q_rsrv_i / SRVL_BUFFER_CELL_SZ));
                SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 256), wm_enc(ref_q_rsrv_i));
                SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 512), wm_enc(buf_q_rsrv_e / SRVL_BUFFER_CELL_SZ));
                SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(port * VTSS_PRIOS + q + 768), wm_enc(ref_q_rsrv_e));
            }
        }
    }

    /* Configure shared space for all QoS classes */
    for (q = 0; q < VTSS_PRIOS; q++) {
        /* Save initial encoded value of shared area for later use by WRED */
        vtss_state->port.buf_prio_shr[q] = wm_enc(buf_prio_shr_e[q] / SRVL_BUFFER_CELL_SZ);

        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 0)),   wm_enc(buf_prio_shr_i[q] / SRVL_BUFFER_CELL_SZ));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 256)), wm_enc(ref_prio_shr_i[q]));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 512)), wm_enc(buf_prio_shr_e[q] / SRVL_BUFFER_CELL_SZ));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 768)), wm_enc(ref_prio_shr_e[q]));
    }

    /* Configure reserved space for all ports */
    for (port_no = 0; port_no <= vtss_state->port_count; port_no++) {
        if (port_no == vtss_state->port_count) {
            port = VTSS_CHIP_PORT_CPU;
#if defined(VTSS_FEATURE_AFI_SWC)
            // We must guarantee the CPU port at least the following amount of
            // buffer memory for use by the AFI:
            //   16 flows of each Max MTU (10240) bytes with an IFH of 16 bytes
            //   + 4 internally generated bytes for timestamp =
            //   16 * (10240 + 16 + 4) = 164,160 bytes.
            buf_p_rsrv_i = 164160;

            if (ref_p_rsrv_i < 16) {
               ref_p_rsrv_i = 16;
            }
#endif /* defined(VTSS_FEATURE_AFI_SWC) */
        } else {
            port = VTSS_CHIP_PORT(port_no);
        }
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(port + 224 +   0), wm_enc(buf_p_rsrv_i / SRVL_BUFFER_CELL_SZ));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(port + 224 + 256), wm_enc(ref_p_rsrv_i));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(port + 224 + 512), wm_enc(buf_p_rsrv_e / SRVL_BUFFER_CELL_SZ));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(port + 224 + 768), wm_enc(ref_p_rsrv_e));
    }

    /* Configure shared space for both DP levels         */
    /* In this context dp:0 is yellow and dp:1 is green */
    for (dp = 0; dp < 2; dp++) {
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(dp + 254 +   0), wm_enc(buf_col_shr_i / SRVL_BUFFER_CELL_SZ));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(dp + 254 + 256), wm_enc(ref_col_shr_i));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(dp + 254 + 512), wm_enc(buf_col_shr_e / SRVL_BUFFER_CELL_SZ));
        SRVL_WR(VTSS_QSYS_RES_CTRL_RES_CFG(dp + 254 + 768), wm_enc(ref_col_shr_e));
        // Green watermark should match the highest priority watermark. Otherwise the will be no
        // strict shared space per qos level
        buf_col_shr_i=buf_col_shr_e=buf_prio_shr_i[7];
        ref_col_shr_i=ref_col_shr_e=ref_prio_shr_i[7];
    }
#else
    /* Use default watermarks for all other devices */
    for (q = 0; q < VTSS_PRIOS; q++) {
        /* Save initial encoded value of shared area for later use by WRED */
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 512)), &vtss_state->port.buf_prio_shr[q]);
    }

#endif /* defined(VTSS_ARCH_SERVAL_ORG) */

    // The CPU will only use its reserved buffer in the shared queue system and
    // none of the shared buffer space, therefore we disable resource sharing in
    // egress direction. We must not disable resource sharing in the ingress
    // direction, because some traffic test scenarios require loads of buffer
    // memory for frames initiated by the CPU.
    port = VTSS_CHIP_PORT_CPU;

    // Egress
    SRVL_RD(VTSS_QSYS_SYSTEM_EGR_NO_SHARING, &value);
    value = VTSS_X_QSYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING(value);
    value |= VTSS_BIT(port);
    SRVL_WRM(VTSS_QSYS_SYSTEM_EGR_NO_SHARING,
             VTSS_F_QSYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING(value),
             VTSS_M_QSYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING);

    // The CPU should also discard frames forwarded to it if it has run
    // out of the reserved buffer space. Otherwise they will be held back
    // in the ingress queues with potential head-of-line blocking effects.
    SRVL_RD(VTSS_QSYS_DROP_CFG_EGR_DROP_MODE, &value);
    value = VTSS_X_QSYS_DROP_CFG_EGR_DROP_MODE_EGRESS_DROP_MODE(value);
    value |= VTSS_BIT(port);
    SRVL_WRM(VTSS_QSYS_DROP_CFG_EGR_DROP_MODE,
             VTSS_F_QSYS_DROP_CFG_EGR_DROP_MODE_EGRESS_DROP_MODE(value),
             VTSS_M_QSYS_DROP_CFG_EGR_DROP_MODE_EGRESS_DROP_MODE);

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static void srvl_debug_fld_nl(const vtss_debug_printf_t pr, const char *name, u32 value)
{
    pr("%-20s: %u\n", name, value);
}

#define SRVL_GET_FLD(tgt, addr, fld, value)  VTSS_X_##tgt##_##addr##_##fld(value)
#define SRVL_GET_BIT(tgt, addr, fld, value)  (VTSS_F_##tgt##_##addr##_##fld & (value) ? 1 : 0)

#define SRVL_DEBUG_HSIO(pr, addr, name) vtss_srvl_debug_reg(vtss_state, pr, VTSS_HSIO_##addr, name)
#define SRVL_DEBUG_MAC(pr, addr, i, name) vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_DEV_MAC_CFG_STATUS_MAC_##addr, i, "MAC_"name)
#define SRVL_DEBUG_PCS(pr, addr, i, name) vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_##addr, i, "PCS_"name)

#define SRVL_DEBUG_HSIO_BIT(pr, addr, fld, value) srvl_debug_fld_nl(pr, #fld, SRVL_GET_BIT(HSIO, addr, fld, x))
#define SRVL_DEBUG_HSIO_FLD(pr, addr, fld, value) srvl_debug_fld_nl(pr, #fld, SRVL_GET_FLD(HSIO, addr, fld, x))
#define SRVL_DEBUG_RAW(pr, offset, length, value, name) srvl_debug_fld_nl(pr, name, VTSS_EXTRACT_BITFIELD(value, offset, length))

static vtss_rc srvl_debug_serdes6g(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   u32 inst,
                                   const char *buf)
{
    u32            x;

    vtss_srvl_debug_reg_header(pr, buf);
    VTSS_RC(srvl_sd6g_lock(vtss_state));
    VTSS_RC(srvl_sd6g_read(vtss_state, 1 << inst));
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_DES_CFG, "DES_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_IB_CFG, "IB_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_IB_CFG1, "IB_CFG1");
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, "OB_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG1, "OB_CFG1");
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_SER_CFG, "SER_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, "COMMON_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, "PLL_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, "PLL_STATUS");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_DIG_CFG, "DIG_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0, "DFT_CFG0");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1, "DFT_CFG1");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2, "DFT_CFG2");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_TP_CFG0, "TP_CFG0");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_TP_CFG1, "TP_CFG1");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_MISC_CFG, "MISC_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG, "OB_ANEG_CFG");
    SRVL_DEBUG_HSIO(pr, SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS, "DFT_STATUS");

    pr("\n%s:OB_CFG:\n", buf);
    SRVL_RD(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG, &x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, OB_ENA1V_MODE, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, OB_POL, x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, OB_POST0, x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, OB_PREC, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, OB_SR_H, x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG, OB_SR, x);

    pr("\n%s:OB_CFG1:\n", buf);
    SRVL_RD(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1, &x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG1, OB_ENA_CAS, x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_OB_CFG1, OB_LEV, x);

    pr("\n%s:DES_CFG:\n", buf);
    SRVL_RD(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG, &x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_DES_CFG, DES_MBTR_CTRL, x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_DES_CFG, DES_CPMD_SEL, x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_DES_CFG, DES_BW_ANA, x);

    pr("\n%s:IB_CFG:\n", buf);
    SRVL_RD(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG, &x);

    pr("\n%s:SER_CFG:\n", buf);
    SRVL_RD(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG, &x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_SER_CFG, SER_ENALI, x);

    pr("\n%s:PLL_CFG:\n", buf);
    SRVL_RD(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, &x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, PLL_DIV4, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, PLL_ENA_ROT, x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, PLL_FSM_CTRL_DATA, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, PLL_FSM_ENA, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, PLL_ROT_DIR, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_PLL_CFG, PLL_ROT_FRQ, x);

    pr("\n%s:COMMON_CFG:\n", buf);
    SRVL_RD(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, &x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, ENA_LANE, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, HRATE, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, QRATE, x);
    SRVL_DEBUG_HSIO_FLD(pr, SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, IF_MODE, x);
    SRVL_DEBUG_HSIO_BIT(pr, SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG, SE_AUTO_SQUELCH_ENA, x);
    VTSS_RC(srvl_sd6g_unlock(vtss_state));

    return VTSS_RC_OK;
}

static vtss_rc srvl_debug_port(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    u32            port, tgt;
    vtss_port_no_t port_no;
    char           buf[32];
    u32            inst, x;
    BOOL           serdes6g;
    
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        if ((port_no = vtss_cmn_port2port_no(vtss_state, info, port)) == VTSS_PORT_NO_NONE)
            continue;

        VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
        vtss_srvl_debug_reg_header(pr, buf);
        tgt = VTSS_TO_DEV(port);
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_DEV_PORT_MODE_CLOCK_CFG(tgt), port, "CLOCK_CFG");
        SRVL_DEBUG_MAC(pr, ENA_CFG(tgt), port, "ENA_CFG");
        SRVL_DEBUG_MAC(pr, MODE_CFG(tgt), port, "MODE_CFG");
        SRVL_DEBUG_MAC(pr, MAXLEN_CFG(tgt), port, "MAXLEN_CFG");
        SRVL_DEBUG_MAC(pr, TAGS_CFG(tgt), port, "TAGS_CFG");
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_SYS_PAUSE_CFG_MAC_FC_CFG(port), port, "FC_CFG");
        SRVL_DEBUG_PCS(pr, CFG(tgt), port, "CFG");
        SRVL_DEBUG_PCS(pr, MODE_CFG(tgt), port, "MODE_CFG");
        SRVL_DEBUG_PCS(pr, SD_CFG(tgt), port, "SD_CFG");
        SRVL_DEBUG_PCS(pr, ANEG_CFG(tgt), port, "ANEG_CFG");
        SRVL_DEBUG_PCS(pr, ANEG_STATUS(tgt), port, "ANEG_STATUS");
        SRVL_DEBUG_PCS(pr, LINK_STATUS(tgt), port, "LINK_STATUS");
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_DEV_PCS_FX100_CONFIGURATION_PCS_FX100_CFG(tgt),
                            port, "PCS_FX100_CFG");
        vtss_srvl_debug_reg_inst(vtss_state, pr, VTSS_DEV_PCS_FX100_STATUS_PCS_FX100_STATUS(tgt),
                            port, "FX100_STATUS");
        pr("\n");

        if (!info->full || srvl_serdes_inst_get(vtss_state, port, &inst, &serdes6g) != VTSS_RC_OK) {
            continue;
        }
        // Skip ports not connected to a SerDes.
        if (inst == SRVL_SERDES_INST_NONE) {
            continue;
        }
        
        if (serdes6g) {
            VTSS_SPRINTF(buf, "SerDes6G_%u", inst);
            (void)srvl_debug_serdes6g(vtss_state, pr, inst, buf);
        } else {
            VTSS_SPRINTF(buf, "SerDes1G_%u", inst);
            vtss_srvl_debug_reg_header(pr, buf);
            VTSS_RC(srvl_sd1g_read(vtss_state, 1 << inst));
            SRVL_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_DES_CFG, "DES_CFG");
            SRVL_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_IB_CFG, "IB_CFG");
            SRVL_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_OB_CFG, "OB_CFG");
            SRVL_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_SER_CFG, "SER_CFG");
            SRVL_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, "COMMON_CFG");
            SRVL_DEBUG_HSIO(pr, SERDES1G_ANA_CFG_SERDES1G_PLL_CFG, "PLL_CFG");
            SRVL_DEBUG_HSIO(pr, SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS, "PLL_STATUS");
            SRVL_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0, "DFT_CFG0");
            SRVL_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1, "DFT_CFG1");
            SRVL_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2, "DFT_CFG2");
            SRVL_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_TP_CFG, "TP_CFG");
            SRVL_DEBUG_HSIO(pr, SERDES1G_DIG_CFG_SERDES1G_MISC_CFG, "MISC_CFG");
            SRVL_DEBUG_HSIO(pr, SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS, "DFT_STATUS");


            pr("\n%s:IB_CFG:\n", buf);
            SRVL_RD(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG, &x);
            SRVL_DEBUG_HSIO_FLD(pr, SERDES1G_ANA_CFG_SERDES1G_IB_CFG, IB_DET_LEV, x);
            SRVL_DEBUG_HSIO_BIT(pr, SERDES1G_ANA_CFG_SERDES1G_IB_CFG, IB_ENA_DC_COUPLING, x);
            SRVL_DEBUG_HSIO_BIT(pr, SERDES1G_ANA_CFG_SERDES1G_IB_CFG, IB_ENA_DETLEV, x);

            pr("\n%s:DES_CFG:\n", buf);
            SRVL_RD(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG, &x);
            SRVL_DEBUG_HSIO_FLD(pr, SERDES1G_ANA_CFG_SERDES1G_DES_CFG, DES_MBTR_CTRL, x);
            SRVL_DEBUG_HSIO_FLD(pr, SERDES1G_ANA_CFG_SERDES1G_DES_CFG, DES_CPMD_SEL, x);
            SRVL_DEBUG_HSIO_FLD(pr, SERDES1G_ANA_CFG_SERDES1G_DES_CFG, DES_BW_ANA, x);

            pr("\n%s:OB_CFG:\n", buf);
            SRVL_RD(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG, &x);
            SRVL_DEBUG_HSIO_FLD(pr, SERDES1G_ANA_CFG_SERDES1G_OB_CFG, OB_AMP_CTRL, x);

            pr("\n%s:COMMON_CFG:\n", buf);
            SRVL_RD(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, &x);
            SRVL_DEBUG_RAW(pr, 7, 1, x, "HRATE");
            SRVL_DEBUG_HSIO_BIT(pr, SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, ENA_LANE, x);
            SRVL_DEBUG_HSIO_BIT(pr, SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG, SE_AUTO_SQUELCH_ENA, x);

            pr("\n%s:PLL_CFG:\n", buf);
            SRVL_RD(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG, &x);
            SRVL_DEBUG_RAW(pr, 21, 1, x, "PLL_FSM_RC_DIV2");
            SRVL_DEBUG_HSIO_FLD(pr, SERDES1G_ANA_CFG_SERDES1G_PLL_CFG, PLL_FSM_CTRL_DATA, x);
        }
        pr("\n");
    }
    pr("\n");

    if (vtss_state->sys_config.using_pcie) {
        inst = 2; /* Serdes2 == PCIe */
        VTSS_SPRINTF(buf, "SerDes6G_%u (PCIe)", inst);
        (void)srvl_debug_serdes6g(vtss_state, pr, inst, buf);
    }

    return VTSS_RC_OK;
}

static void srvl_debug_cnt_inst(const vtss_debug_printf_t pr, u32 i,
                                const char *col1, const char *col2, 
                                vtss_chip_counter_t *c1, vtss_chip_counter_t *c2)
{
    char buf1[80], buf2[80];
    
    VTSS_SPRINTF(buf1, "%s_%u", col1 && strlen(col1) ? col1 : col2, i);
    VTSS_SPRINTF(buf2, "%s_%u", col2 && strlen(col2) ? col2 : col1, i);
    vtss_srvl_debug_cnt(pr, col1 ? buf1 : col1, col2 ? buf2 : col2, c1, c2);
}

static vtss_rc srvl_debug_port_cnt(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    /*lint --e{454, 455} */ // Due to VTSS_EXIT_ENTER
    vtss_port_no_t               port_no = 0;
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
        VTSS_RC(srvl_port_counters_read(vtss_state, port_no, port, cnt, NULL, 0));
        VTSS_EXIT_ENTER();

        if (info->clear) {
            SRVL_WR(VTSS_SYS_SYSTEM_STAT_CFG, VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_SHOT(0x7) | VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_VIEW(port));
        }

        /* Basic counters */
        if (cpu_port) {
            pr("Counters CPU port: %u\n\n", port);
        } else {
            pr("Counters for port: %u (chip_port %u):\n\n", port_no, port);
            if (info->full || info->action != 3) {
                vtss_srvl_debug_cnt(pr, "oct", "", &cnt->rx_octets, &cnt->tx_octets);
                vtss_srvl_debug_cnt(pr, "uc", "", &cnt->rx_unicast, &cnt->tx_unicast);
                vtss_srvl_debug_cnt(pr, "mc", "", &cnt->rx_multicast, &cnt->tx_multicast);
                vtss_srvl_debug_cnt(pr, "bc", "", &cnt->rx_broadcast, &cnt->tx_broadcast);
            }

            /* Detailed MAC Ccounters */
            if (info->full || info->action == 2) {
                vtss_srvl_debug_cnt(pr, "pause", "", &cnt->rx_pause, &cnt->tx_pause);
                vtss_srvl_debug_cnt(pr, "64", "", &cnt->rx_64, &cnt->tx_64);
                vtss_srvl_debug_cnt(pr, "65_127", "", &cnt->rx_65_127, &cnt->tx_65_127);
                vtss_srvl_debug_cnt(pr, "128_255", "", &cnt->rx_128_255, &cnt->tx_128_255);
                vtss_srvl_debug_cnt(pr, "256_511", "", &cnt->rx_256_511, &cnt->tx_256_511);
                vtss_srvl_debug_cnt(pr, "512_1023", "", &cnt->rx_512_1023, &cnt->tx_512_1023);
                vtss_srvl_debug_cnt(pr, "1024_1526", "", &cnt->rx_1024_1526, &cnt->tx_1024_1526);
                vtss_srvl_debug_cnt(pr, "jumbo", "", &cnt->rx_1527_max, &cnt->tx_1527_max);
                vtss_srvl_debug_cnt(pr, "crc", NULL, &cnt->rx_crc_align_errors, NULL);
                vtss_srvl_debug_cnt(pr, "symbol", NULL, &cnt->rx_symbol_errors, NULL);
                vtss_srvl_debug_cnt(pr, "short", NULL, &cnt->rx_shorts, NULL);
                vtss_srvl_debug_cnt(pr, "long", NULL, &cnt->rx_longs, NULL);
                vtss_srvl_debug_cnt(pr, "frag", NULL, &cnt->rx_fragments, NULL);
                vtss_srvl_debug_cnt(pr, "jabber", NULL, &cnt->rx_jabbers, NULL);
                vtss_srvl_debug_cnt(pr, "control", NULL, &cnt->rx_control, NULL);
            }
        }

        if (info->full || info->action == 1 || info->action == 3) {
            /* Queue system counters */
            vtss_srvl_debug_cnt(pr, "cat_drop", cpu_port ? NULL : "drops",
                                &cnt->rx_classified_drops, &cnt->tx_drops);
            vtss_srvl_debug_cnt(pr, "dr_local", cpu_port ? NULL : "aged",
                                &cnt->dr_local, &cnt->tx_aging);
            vtss_srvl_debug_cnt(pr, "dr_tail", NULL, &cnt->dr_tail, NULL);
            for (i = 0; i < VTSS_PRIOS; i++)
                srvl_debug_cnt_inst(pr, i, "green", "", 
                                    &cnt->rx_green_class[i], &cnt->tx_green_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                srvl_debug_cnt_inst(pr, i, "yellow", "", 
                                    &cnt->rx_yellow_class[i], &cnt->tx_yellow_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++) 
                srvl_debug_cnt_inst(pr, i, "red", "dr_green", &cnt->rx_red_class[i], &cnt->dr_green_class[i]);
            for (i = 0; i < VTSS_PRIOS; i++)
                srvl_debug_cnt_inst(pr, i, NULL, "dr_yellow", NULL, &cnt->dr_yellow_class[i]);
        }
        pr("\n");
    }
    return VTSS_RC_OK;
}

static void srvl_debug_wm_dump(const vtss_debug_printf_t pr, const char *reg_name, u32 *value, u32 i, u32 multiplier)
{
    u32 q;
    pr("%-26s", reg_name);
    for (q = 0; q < i; q++) {
        pr("%6u ", wm_dec(value[q]) * multiplier);
    }
    pr("\n");
}

static vtss_rc srvl_debug_wm(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)

{
    u32 port_no, value, q, dp, cpu_port, port;
    u32 id[8] = {0}, val1[8] = {0}, val2[8] = {0}, val3[8] = {0}, val4[8] = {0}, val5[8] = {0};

    pr("Global configuration:\n");
    pr("---------------------\n");
    pr("Total buffer memory     : %d bytes\n", SRVL_BUFFER_MEMORY);
    pr("Total frame references  : %d frames\n", SRVL_BUFFER_REFERENCE);
    pr("\n");
    SRVL_RD(VTSS_SYS_PAUSE_CFG_PAUSE_TOT_CFG, &value);
    pr("FC Pause TOT_START WM   : %d bytes\n", (wm_dec(VTSS_X_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(value)) * SRVL_BUFFER_CELL_SZ));
    pr("FC Pause TOT_STOP WM    : %d bytes\n", (wm_dec(VTSS_X_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(value)) * SRVL_BUFFER_CELL_SZ));
    SRVL_RD(VTSS_SYS_PAUSE_CFG_ATOP_TOT_CFG, &value);
    pr("FC TailDrop ATOP_TOT WM : %d bytes\n", (wm_dec(VTSS_X_SYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(value)) * SRVL_BUFFER_CELL_SZ));
    pr("\n");

    for (port_no = VTSS_PORT_NO_START; port_no <= vtss_state->port_count; port_no++) {
        cpu_port = (port_no == vtss_state->port_count);
        if (cpu_port) {
            /* CPU port */
            if (!info->full) {
                continue;
            }
            port = VTSS_CHIP_PORT_CPU;
        } else {
            if (!info->port_list[port_no]) {
                continue;
            }
            port = VTSS_CHIP_PORT(port_no);
        }
        if (cpu_port) {
            pr("CPU Port : %2u\n", port_no);
            pr("-------------\n");
        } else {
            pr("Port : %2u\n", port_no);
            pr("---------\n");
        }
        if (!cpu_port) {
            if ((port_no = vtss_cmn_port2port_no(vtss_state, info, port)) == VTSS_PORT_NO_NONE) {
                continue;
            }

            SRVL_RD(VTSS_SYS_PAUSE_CFG_MAC_FC_CFG(port), &value);
            pr("FC Pause Tx ena     : %d\n", (value & VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_TX_FC_ENA) ? 1 : 0);
            pr("FC Pause Rx ena     : %d\n", (value & VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_RX_FC_ENA) ? 1 : 0);
            pr("FC Pause Time Value : 0x%x\n", VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_PAUSE_VAL_CFG(value));
            pr("FC Zero pause       : %d\n", (value & VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_ZERO_PAUSE_ENA) ? 1 : 0);          
            SRVL_RD(VTSS_SYS_PAUSE_CFG_PAUSE_CFG(port), &value);
            pr("FC Pause Ena        : %d\n", (value & VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA) ? 1 : 0);
            pr("FC Pause Start WM   : %d bytes\n", (wm_dec(VTSS_X_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(value)) * SRVL_BUFFER_CELL_SZ));
            pr("FC Pause Stop WM    : %d bytes\n", (wm_dec(VTSS_X_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(value)) * SRVL_BUFFER_CELL_SZ));
            pr("\n");
        }

        SRVL_RD(VTSS_SYS_PAUSE_CFG_ATOP(port), &value);
        pr("FC TailDrop ATOP WM : %d bytes\n", (wm_dec(VTSS_X_SYS_PAUSE_CFG_ATOP_ATOP(value)) * SRVL_BUFFER_CELL_SZ));
        SRVL_RD(VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE(port), &value);
        pr("Ingress Drop Mode   : %d\n", (value & VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE) ? 1 : 0);
        SRVL_RD(VTSS_QSYS_DROP_CFG_EGR_DROP_MODE, &value);
        pr("Egress Drop Mode    : %d\n", (VTSS_X_QSYS_DROP_CFG_EGR_DROP_MODE_EGRESS_DROP_MODE(value) & VTSS_BIT(port)) ? 1 : 0);
        SRVL_RD(VTSS_QSYS_SYSTEM_IGR_NO_SHARING, &value);
        pr("Ingress No Sharing  : %d\n", (VTSS_X_QSYS_SYSTEM_IGR_NO_SHARING_IGR_NO_SHARING(value) & VTSS_BIT(port)) ? 1 : 0);
        SRVL_RD(VTSS_QSYS_SYSTEM_EGR_NO_SHARING, &value);
        pr("Ingress No Sharing  : %d\n", (VTSS_X_QSYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING(value) & VTSS_BIT(port)) ? 1 : 0);
        SRVL_RD(VTSS_QSYS_SYSTEM_PORT_MODE(port), &value);
        pr("Dequeuing disabled  : %d\n", (value & VTSS_F_QSYS_SYSTEM_PORT_MODE_DEQUEUE_DIS) ? 1 : 0);
        pr("\n");

        for (q = 0; q < VTSS_PRIOS; q++) {
            id[q] = q;
            SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 0)),   &val1[q]);
            SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 256)), &val2[q]);
            SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 512)), &val3[q]);
            SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((port * VTSS_PRIOS + q + 768)), &val4[q]);
        }

        srvl_debug_wm_dump(pr, "Queue level rsrv WMs:", id, 8, 1);
        srvl_debug_wm_dump(pr, "Qu Ingr Buf Rsrv (Bytes) :", val1, 8, SRVL_BUFFER_CELL_SZ);
        srvl_debug_wm_dump(pr, "Qu Ingr Ref Rsrv (Frames):", val2, 8, 1);
        srvl_debug_wm_dump(pr, "Qu Egr Buf Rsrv  (Bytes) :", val3, 8, SRVL_BUFFER_CELL_SZ);
        srvl_debug_wm_dump(pr, "Qu Egr Ref Rsrv  (Frames):", val4, 8, 1);
        pr("\n");

        /* Configure reserved space for port */
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((port + 224 +   0)), &val1[0]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((port + 224 + 256)), &val2[0]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((port + 224 + 512)), &val3[0]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((port + 224 + 768)), &val4[0]);
        pr("Port level rsrv WMs:\n");
        pr("Port Ingress Buf Rsrv: %u Bytes\n",  wm_dec(val1[0]) * SRVL_BUFFER_CELL_SZ);
        pr("Port Ingress Ref Rsrv: %u Frames\n", wm_dec(val2[0]));
        pr("Port Egress  Buf Rsrv: %u Bytes\n",  wm_dec(val3[0]) * SRVL_BUFFER_CELL_SZ);
        pr("Port Egress  Ref Rsrv: %u Frames\n", wm_dec(val4[0]));
        pr("\n");
    }

    pr("Shared :\n");
    pr("--------\n");
    /* Shared space for all QoS classes */
    SRVL_RD(VTSS_QSYS_RES_QOS_ADV_RES_QOS_MODE, &value);
    value = VTSS_X_QSYS_RES_QOS_ADV_RES_QOS_MODE_RES_QOS_RSRVD(value);
    for (q = 0; q < VTSS_PRIOS; q++) {
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 0)),   &val1[q]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 256)), &val2[q]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 512)), &val3[q]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216 + 768)), &val4[q]);
        val5[q] = (value & VTSS_BIT(q)) ? 1 : 0;
    }
    srvl_debug_wm_dump(pr, "QoS level:", id, 8, 1);
    srvl_debug_wm_dump(pr, "QoS Ingr Buf (Bytes) :", val1, 8, SRVL_BUFFER_CELL_SZ);
    srvl_debug_wm_dump(pr, "QoS Ingr Ref (Frames):", val2, 8, 1);
    srvl_debug_wm_dump(pr, "QoS Egr Buf  (Bytes) :", val3, 8, SRVL_BUFFER_CELL_SZ);
    srvl_debug_wm_dump(pr, "QoS Egr Ref  (Frames):", val4, 8, 1);
    srvl_debug_wm_dump(pr, "QoS Reservation Mode :", val5, 8, 1);
    pr("\n");
        
    pr("Color level:\n");
    /* Configure shared space for both DP levels         */
    /* In this context dp:0 is yellow and dp:1 is green */
    for (dp = 0; dp < 2; dp++) {
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((dp + 254 +   0)), &val1[0]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((dp + 254 + 256)), &val2[0]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((dp + 254 + 512)), &val3[0]);
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((dp + 254 + 768)), &val4[0]);
        pr("Port DP:%6s Ingress Buf : %u Bytes\n", dp ? "Green" : "Yellow", wm_dec(val1[0]) * SRVL_BUFFER_CELL_SZ);
        pr("Port DP:%6s Ingress Ref : %u Frames\n",dp ? "Green" : "Yellow", wm_dec(val2[0]));
        pr("Port DP:%6s Egress  Buf : %u Bytes\n", dp ? "Green" : "Yellow", wm_dec(val3[0]) * SRVL_BUFFER_CELL_SZ);
        pr("Port DP:%6s Egress  Ref : %u Frames\n",dp ? "Green" : "Yellow", wm_dec(val4[0]));
    }
    pr("\n");

    pr("WRED config:\n");
    pr("Queue Dpl WM_HIGH  bytes RED_LOW  bytes RED_HIGH  bytes\n");
    //  xxxxx xxx 0xxxxx xxxxxxx 0xxxxx xxxxxxx 0xxxxx  xxxxxxx
    for (q = VTSS_QUEUE_START; q < VTSS_QUEUE_END; q++) {
        u32 wm_high, red_profile, wm_red_low, wm_red_high;
        SRVL_RD(VTSS_QSYS_RES_CTRL_RES_CFG((q + 216)), &wm_high); /* Shared ingress high watermark for queue */
        for (dp = 0; dp < 2; dp++) {
            SRVL_RD(VTSS_QSYS_RES_QOS_ADV_RED_PROFILE((q + (8 * dp))), &red_profile); /* Red profile for queue, dpl */
            wm_red_low  = VTSS_X_QSYS_RES_QOS_ADV_RED_PROFILE_WM_RED_LOW(red_profile);
            wm_red_high = VTSS_X_QSYS_RES_QOS_ADV_RED_PROFILE_WM_RED_HIGH(red_profile);
            pr("%5u %3u  0x%04x %6u  0x%04x %6u   0x%04x %6u\n",
               q,
               dp,
               wm_high,
               wm_dec(wm_high) * SRVL_BUFFER_CELL_SZ,
               wm_red_low,
               wm_red_low * 960,
               wm_red_high,
               wm_red_high * 960);
        }
    }
    pr("\n");

    for (port_no = VTSS_PORT_NO_START; port_no <= vtss_state->port_count; port_no++) {
        for (q = 0; q < VTSS_PRIOS; q++) {
            port = (port_no == vtss_state->port_count) ? VTSS_CHIP_PORT_CPU : VTSS_CHIP_PORT(port_no);
            SRVL_RD(VTSS_QSYS_RES_CTRL_RES_STAT(port * VTSS_PRIOS + q + 0), &val1[q]);
            if (val1[q] > 0) {
                pr("API port %u (%u), ingress qu %u: Inuse:%u bytes, Maxuse:%u bytes\n",
                   port_no, port, q, VTSS_X_QSYS_RES_CTRL_RES_STAT_INUSE(val1[q]) * SRVL_BUFFER_CELL_SZ,
                   VTSS_X_QSYS_RES_CTRL_RES_STAT_MAXUSE(val1[q]) * SRVL_BUFFER_CELL_SZ);
            }
        }
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_port_debug_print(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT, srvl_debug_port, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_PORT_CNT, srvl_debug_port_cnt, vtss_state, pr, info));
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_WM, srvl_debug_wm, vtss_state, pr, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

vtss_rc vtss_srvl_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_port_state_t *state = &vtss_state->port;
    u32               port;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->miim_read = srvl_miim_read;
        state->miim_write = srvl_miim_write;
        state->mmd_read = srvl_mmd_read;
        state->mmd_read_inc = srvl_mmd_read_inc;
        state->mmd_write = srvl_mmd_write;
        state->conf_get = srvl_port_conf_get;
        state->conf_set = srvl_port_conf_set;
        state->clause_37_status_get = srvl_port_clause_37_status_get;
        state->clause_37_control_get = srvl_port_clause_37_control_get;
        state->clause_37_control_set = srvl_port_clause_37_control_set;
        state->status_get = srvl_port_status_get;
        state->counters_update = srvl_port_counters_update;
        state->counters_clear = srvl_port_counters_clear;
        state->counters_get = srvl_port_counters_get;
        state->basic_counters_get = srvl_port_basic_counters_get;
        state->ifh_set = srvl_port_ifh_set;
        state->forward_set = srvl_port_forward_set;
        state->test_conf_set = srvl_port_test_conf_set;
#if defined(VTSS_FEATURE_SYNCE)
        /* SYNCE features */
        vtss_state->synce.clock_out_set = srvl_synce_clock_out_set;
        vtss_state->synce.clock_in_set = srvl_synce_clock_in_set;
#endif /* VTSS_FEATURE_SYNCE */
        break;
    case VTSS_INIT_CMD_INIT:
    /* Set up the Serdes1g/Serdes6g macro muxing based on the selected mux mode.
       This will setup all the needed serdes connectivity for a given port configuration,
       including QSGMII and PCIe connections. */
    VTSS_RC(ocelot_serdes_macro_config(vtss_state));

        if (!vtss_state->warm_start_cur) {
            /* Initialize the internal PHYs */
            SRVL_WR(VTSS_DEVCPU_GCB_PHY_PHY_CFG, 0);
            SRVL_WRM(VTSS_DEVCPU_GCB_PHY_PHY_CFG,
                     VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_RESET(0xF) |
                     VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_ENA(0xF) |
                     VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_COMMON_RESET,
                     VTSS_M_DEVCPU_GCB_PHY_PHY_CFG_PHY_RESET |
                     VTSS_M_DEVCPU_GCB_PHY_PHY_CFG_PHY_ENA |
                     VTSS_F_DEVCPU_GCB_PHY_PHY_CFG_PHY_COMMON_RESET);
            VTSS_MSLEEP(200);

            /* Clear port counters */
            for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
                SRVL_WR(VTSS_SYS_SYSTEM_STAT_CFG,
                        VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_SHOT(0x7) |
                        VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_VIEW(port));
            }
        }

        // Count QS drops at egress port
        SRVL_WRM_SET(VTSS_QSYS_SYSTEM_STAT_CNT_CFG, VTSS_F_QSYS_SYSTEM_STAT_CNT_CFG_DROP_COUNT_EGRESS);
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(srvl_port_buf_conf_set(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_OCELOT */
