// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_jaguar2_cil.h"
#include "vtss_jaguar2_sd10g65_setup.h"
#include "vtss_servalt_sd10g65_setup.h"
#include "vtss_jaguar2c_sd10g65_setup.h"
#if defined(VTSS_ARCH_JAGUAR_2)

vtss_rc jr2_sd1g_read_write(vtss_state_t *vtss_state, u32 addr, BOOL write)
{
    u32 data, mask;

    if (write)
        mask =
            VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_WR_ONE_SHOT(
                1);
    else
        mask =
            VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT(
                1);

    JR2_WR(VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG,
           VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR(addr) |
               mask);

    do { /* Wait until operation is completed  */
        JR2_RD(VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG, &data);
    } while (data & mask);

    return VTSS_RC_OK;
}

/* Serdes1G: Read data */
vtss_rc jr2_sd1g_read(vtss_state_t *vtss_state, u32 addr)
{
    return jr2_sd1g_read_write(vtss_state, addr, 0);
}

/* Serdes1G: Write data */
vtss_rc jr2_sd1g_write(vtss_state_t *vtss_state, u32 addr)
{
    return jr2_sd1g_read_write(vtss_state, addr, 1);
}

vtss_rc jr2_sd1g_cfg(vtss_state_t      *vtss_state,
                     vtss_port_no_t     port_no,
                     vtss_serdes_mode_t mode,
                     u32                addr)
{
    vtss_port_lb_t lb = vtss_state->port.test_conf[port_no].loopback;
    BOOL           ena_lane = 1, if_100fx = 0, ena_dc_coupling = 0;
    u32            ob_amp_ctrl = 0, cpmd_sel = 0, mbtr_ctrl = 2, des_bw_ana = 6,
        ob_idle = 0, test_mode = 0, test_pattern = 0;
    u32 cmv_term = 1;
#if defined(VTSS_ARCH_SERVAL_T)
    u32 des_phs_ctrl = 2;
#else
    u32 des_phs_ctrl = 6;
#endif

    VTSS_D("addr: 0x%x, mode: %s", addr, vtss_serdes_mode_txt(mode));

    switch (mode) {
    case VTSS_SERDES_MODE_SGMII: ob_amp_ctrl = 12; break;
    case VTSS_SERDES_MODE_100FX:
        ob_amp_ctrl = 12;
        if_100fx = 1;
        cpmd_sel = 2;
        mbtr_ctrl = 3;
        ena_dc_coupling = 1;
        des_bw_ana = 0;
#if defined(VTSS_ARCH_SERVAL_T)
        des_phs_ctrl = 10;
#else
        des_phs_ctrl = 14;
#endif
        cmv_term = 0;
        break;
    case VTSS_SERDES_MODE_1000BaseX: ob_amp_ctrl = 15; break;
    case VTSS_SERDES_MODE_DISABLE:
        ena_lane = 0;
        ob_amp_ctrl = 0;
        break;
    case VTSS_SERDES_MODE_IDLE: ob_idle = 1; break;
    case VTSS_SERDES_MODE_TEST_MODE:
        test_mode = 2; // Fixed pattern
        test_pattern = 0x5f289;
        break;
    default:
        VTSS_E("Serdes1g mode %s not supported", vtss_serdes_mode_txt(mode));
        return VTSS_RC_ERROR;
    }

    VTSS_RC(jr2_sd1g_read(vtss_state, addr));

    JR2_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG,
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_IDLE(ob_idle) |
                VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI(
                    lb == VTSS_PORT_LB_FACILITY),
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_IDLE |
                VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI);

    if (mode == VTSS_SERDES_MODE_IDLE) {
        /* Apply the idle mode (port down) and return */
        VTSS_RC(jr2_sd1g_write(vtss_state, addr));
        return VTSS_RC_OK;
    }

    // Set test mode and test pattern
    JR2_WR(VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_TP_CFG, test_pattern);
    JR2_WRM(VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0,
            VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_TEST_MODE(test_mode),
            VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_TEST_MODE);

    // OB CFG
    JR2_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG,
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL(ob_amp_ctrl),
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL);

    // IB CFG
    JR2_WRM(
        VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG,
        VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM(cmv_term) |
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA(if_100fx) |
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING(
                ena_dc_coupling) |
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL(13),
        VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM |
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA |
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING |
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL);

    // DES CFG
    JR2_WRM(
        VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG,
        VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL(des_phs_ctrl) |
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL(cpmd_sel) |
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL(
                mbtr_ctrl) |
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA(des_bw_ana),
        VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL |
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL |
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL |
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA);

    // MISC CFG
    JR2_WRM(VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG,
            VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA(
                if_100fx) |
                VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST(1),
            VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA |
                VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST);

    // PLL CFG
    JR2_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG,
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA(1),
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA);

    // COMMON CFG
    JR2_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE(ena_lane) |
                VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP(
                    lb == VTSS_PORT_LB_FACILITY) |
                VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP(
                    lb == VTSS_PORT_LB_EQUIPMENT),
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE |
                VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP |
                VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP);

    // Write SD1G
    VTSS_RC(jr2_sd1g_write(vtss_state, addr));

    JR2_WRM(VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG,
            VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST(1),
            VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST);

    // Write SD1G
    VTSS_RC(jr2_sd1g_write(vtss_state, addr));

    JR2_WRM(VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG,
            VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST(0),
            VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST);

    // Write SD1G
    VTSS_RC(jr2_sd1g_write(vtss_state, addr));

    return VTSS_RC_OK;
}

/* Serdes6G: Read/write data */
vtss_rc jr2_sd6g_read_write(vtss_state_t *vtss_state, u32 addr, BOOL write)
{
    u32 data, mask;

    if (write)
        mask =
            VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT(
                1);
    else
        mask =
            VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT(
                1);

    JR2_WR(VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG,
           VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(addr) |
               mask);

    do { /* Wait until operation is completed  */
        JR2_RD(VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG, &data);
    } while (data & mask);

    return VTSS_RC_OK;
}

/* Serdes6G: Read data */
vtss_rc jr2_sd6g_read(vtss_state_t *vtss_state, u32 addr)
{
    return jr2_sd6g_read_write(vtss_state, addr, 0);
}

/* Serdes6G: Write data */
vtss_rc jr2_sd6g_write(vtss_state_t *vtss_state, u32 addr)
{
    return jr2_sd6g_read_write(vtss_state, addr, 1);
}

/* Serdes6G serdes code is autogenerated (from TCL environment) */
vtss_rc jr2_sd6g_cfg(vtss_state_t      *vtss_state,
                     vtss_port_no_t     port_no,
                     vtss_serdes_mode_t mode,
                     u32                addr)
{
    vtss_port_lb_t lb = vtss_state->port.test_conf[port_no].loopback;
    u32            ob_ena1v_mode = 0;
    u32            ob_post0 = 0;
    u32            ob_prec = 0;
    u32            ob_ena_cas = 0;
    u32            ob_lev = 24;
    u32            ob_idle = 0;
    u32            ob_sr_h = 1;
    u32            des_cpmd_sel = 0;
    u32            des_bw_ana = 3; // as per BZ 17124
    u32            ib_sig_det_clk_sel = 7;
    u32            ser_alisel = 0;
    u32            ser_enali = 0;
    u32            pll_div4 = 0;
    u32            pll_ena_rot = 0;
    u32            pll_fsm_ctrl_data = 120;
    u32            pll_rot_dir = 0;
    u32            pll_rot_frq = 0;
    u32            hrate = 0;
    u32            qrate = 0;
    u32            if_mode = 3;
    u32            des_100fx_cpmd_ena = 0;
    u32            rx_lpi_mode_ena = 0;
    u32            tx_lpi_mode_ena = 0;
    u32            ib_concur = 1;
    u32            ena_lane = 1;
    u32            ib_sig_det_ena = 1;
    u32            ib_sam_ena = 1;
    u32            test_mode = 0;
    u32            test_pattern = 0;
    // 100FX (BZ21878) default values:
    u32 ib_ureg = 4;        // if_cfg2
    u32 ib_eqz_ena = 1;     // if_cfg
    u32 ib_reg_ena = 1;     // if_cfg
    u32 ib_filt_offset = 1; // ib_cfg1
    u32 ib_filt_hp = 1;     // ib_cfg1
    u32 ib_filt_mid = 1;    // ib_cfg1
    u32 ib_filt_lp = 1;     // ib_cfg1
    u32 ib_frc_offset = 0;  // ib_cfg1
    u32 ib_frc_hp = 0;      // ib_cfg1
    u32 ib_frc_mid = 0;     // ib_cfg1
    u32 ib_frc_lp = 0;      // ib_cfg1
    u32 ib_ini_hp = 0;      // ib_cfg3
    u32 ib_ini_mid = 31;    // ib_cfg3
    u32 ib_ini_lp = 1;      // ib_cfg3
    u32 ib_ini_offset = 31; // ib_cfg3

#if defined(VTSS_ARCH_SERVAL_T)
    u32 des_phs_ctrl = 2;
#else
    u32 des_phs_ctrl = 6;
#endif

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
#if defined(VTSS_ARCH_SERVAL_T)
        des_phs_ctrl = 10;
#else
        des_phs_ctrl = 14;
#endif
        ib_ureg = 4;
        ib_eqz_ena = 0;
        ib_reg_ena = 0;

        ib_filt_offset = 0;
        ib_filt_hp = 0;
        ib_filt_mid = 0;
        ib_filt_lp = 0;
        ib_frc_offset = 1;
        ib_frc_hp = 1;
        ib_frc_mid = 1;
        ib_frc_lp = 1;

        ib_ini_hp = 0;
        ib_ini_mid = 31;
        ib_ini_lp = 63;
        ib_ini_offset = 31;
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
        ob_sr_h = 0; // XAUI
        break;
    case VTSS_SERDES_MODE_RXAUI:
        ob_ena1v_mode = 0;
        ob_post0 = 0;
        ob_ena_cas = 0;
        ob_lev = 63;
        ser_alisel = 1;
        ser_enali = 1;
        pll_ena_rot = 1;
        pll_fsm_ctrl_data = 96; // RXAUI
        hrate = 0;              // RXAUI
        if_mode = 3;            // RXAUI
        ob_sr_h = 1;            // RXAUI
        qrate = 0;
        pll_rot_frq = 1;
        des_100fx_cpmd_ena = 0;
        break;
    case VTSS_SERDES_MODE_IDLE: ob_idle = 1; break;
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

    VTSS_RC(jr2_sd6g_read(vtss_state, addr));

    // prepare for initial or new configuration

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_IDLE(ob_idle),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_IDLE);

    if (mode == VTSS_SERDES_MODE_IDLE) {
        /* Apply the idle mode (port down) and return */
        VTSS_RC(jr2_sd6g_write(vtss_state, addr));
        return VTSS_RC_OK;
    }

    // Set test mode and test pattern
    JR2_WR(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0, test_pattern);
    JR2_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0,
            VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TEST_MODE(test_mode),
            VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TEST_MODE);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(0),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(0),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

    JR2_WRM(
        VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
        VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA(
            ib_sig_det_ena) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA(ib_reg_ena) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA(ib_sam_ena) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA(ib_eqz_ena) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR(ib_concur) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA(0),
        VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA);

    JR2_WRM(
        VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
        VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_OFFSET(
            ib_filt_offset) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_HP(ib_filt_hp) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_MID(
                ib_filt_mid) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_LP(ib_filt_lp) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_OFFSET(
                ib_frc_offset) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_HP(ib_frc_hp) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_MID(ib_frc_mid) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_LP(ib_frc_lp),
        VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_OFFSET |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_HP |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_MID |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_LP |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_OFFSET |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_HP |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_MID |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_LP);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UREG(ib_ureg),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UREG);

    JR2_WRM(
        VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3,
        VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_HP(ib_ini_hp) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_MID(ib_ini_mid) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_LP(ib_ini_lp) |
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_OFFSET(
                ib_ini_offset),
        VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_HP |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_MID |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_LP |
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_OFFSET);

    JR2_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
            VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(1),
            VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

    VTSS_RC(jr2_sd6g_write(vtss_state, addr));

    // apply configuration

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE(
                ob_ena1v_mode),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(ob_post0),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(ob_prec),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(ob_ena_cas),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(ob_lev),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H(ob_sr_h),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(
                des_phs_ctrl),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(
                des_cpmd_sel),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(des_bw_ana),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(0),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(16),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(ser_alisel),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI(
                ser_enali || lb == VTSS_PORT_LB_FACILITY),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4(pll_div4),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4);

    JR2_WRM(
        VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
        VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT(pll_ena_rot),
        VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(
                pll_fsm_ctrl_data),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA);

    JR2_WRM(
        VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
        VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR(pll_rot_dir),
        VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR);

    JR2_WRM(
        VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
        VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ(pll_rot_frq),
        VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ);

    JR2_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
            VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(1),
            VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(1),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE(ena_lane),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE(hrate),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE(qrate),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP(
                lb == VTSS_PORT_LB_FACILITY) |
                VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP(
                    lb == VTSS_PORT_LB_EQUIPMENT) |
                VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(if_mode),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP |
                VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP |
                VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE);

    JR2_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
            VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA(
                des_100fx_cpmd_ena),
            VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA);

    JR2_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
            VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA(
                rx_lpi_mode_ena),
            VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA);

    JR2_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
            VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA(
                tx_lpi_mode_ena),
            VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA);

    VTSS_RC(jr2_sd6g_write(vtss_state, addr));
    // Step 2:    Set pll_fsm_ena=1
    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(1),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

    VTSS_RC(jr2_sd6g_write(vtss_state, addr));
    // Step 3: Wait for 20 ms for PLL bringup
    VTSS_MSLEEP(20);
    // Step 4: Start IB calibration by setting ib_cal_ena and clearing lane_rst
    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA(1),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA);

    JR2_WRM(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
            VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(0),
            VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

    VTSS_RC(jr2_sd6g_write(vtss_state, addr));
    // Step 5: Wait for 60 ms for calibration
    VTSS_MSLEEP(60);
    // Step 6:Set ib_tsdet and ib_reg_pat_sel_offset back to correct values
    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(
                ib_sig_det_clk_sel),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL);

    JR2_WRM(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
            VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(3),
            VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET);

    VTSS_RC(jr2_sd6g_write(vtss_state, addr));

    return VTSS_RC_OK;
}

static vtss_chip_name_t get_chip_name(void)
{
#if defined(VTSS_ARCH_SERVAL_T)
    return VTSS_SD10G65_CHIP_SERVALT;
#elif defined(VTSS_ARCH_JAGUAR_2_C)
    return VTSS_SD10G65_CHIP_JAGUAR2C;
#else
    return VTSS_SD10G65_CHIP_JAGUAR2;
#endif
}

static vtss_sd10g65_preset_t serdes2preset(vtss_serdes_mode_t m)
{
    switch (m) {
    case VTSS_SD10G_MEDIA_SR:     return (VTSS_SD10G65_SR_HW);
    case VTSS_SD10G_MEDIA_ZR:     return (VTSS_SD10G65_ZR_HW);
    case VTSS_SD10G_MEDIA_DAC:    return (VTSS_SD10G65_DAC_HW);
    case VTSS_SD10G_MEDIA_DAC_5M: return (VTSS_SD10G65_DAC_HW);
    case VTSS_SD10G_MEDIA_BP:     return (VTSS_SD10G65_BACKPLANE);
    case VTSS_SD10G_MEDIA_B2B:    return (VTSS_SD10G65_B2B);
    case VTSS_SD10G_MEDIA_10G_KR: return (VTSS_SD10G65_KR_HW);
    default:                      return (VTSS_SD10G65_PRESET_NONE);
    }
}

/* Configuration for the 10G Macros.  All functions are autogenerated by UTE/GDC
 */
vtss_rc jr2_sd10g_cfg(vtss_state_t           *vtss_state,
                      vtss_serdes_mode_t      mode,
                      vtss_sd10g_media_type_t media,
                      u32                     port)
{
    vtss_rc                       rc = VTSS_RC_OK;
    vtss_sd10g65_setup_tx_args_t  config_tx = {0};
    vtss_sd10g65_setup_rx_args_t  config_rx = {0};
    vtss_sd10g65_setup_apc_args_t config_apc = {0};
    vtss_sd10g65_f_pll_t          f_pll = {0};
    vtss_sd10g65_preset_t         preset = serdes2preset(media);

    if (mode == VTSS_SERDES_MODE_DISABLE) {
#if defined(VTSS_ARCH_SERVAL_T)
        return vtss_servalt_sd10g_power_down(vtss_state, port);
#elif defined(VTSS_ARCH_JAGUAR_2_C)
        return vtss_jaguar2c_sd10g_power_down(vtss_state, port);
#else /* VTSS_ARCH_JAGUAR_2_B */
        return vtss_jaguar2_sd10g_power_down(vtss_state, port);
#endif
    }

    /* Initialize the configuration with default values */
    VTSS_RC(vtss_sd10g65_setup_tx_args_init(&config_tx));
    VTSS_RC(vtss_sd10g65_setup_rx_args_init(&config_rx));
    VTSS_RC(vtss_sd10g65_setup_apc_args_init(&config_apc));
    config_tx.chip_name = config_rx.chip_name = config_apc.chip_name =
        get_chip_name();

    /* Apply the serdes mode */
    switch (mode) {
    case VTSS_SERDES_MODE_IDLE:
    case VTSS_SERDES_MODE_SFI_DAC:
    case VTSS_SERDES_MODE_SFI_SR:
    case VTSS_SERDES_MODE_SFI_ZR:
    case VTSS_SERDES_MODE_SFI_BP:
    case VTSS_SERDES_MODE_SFI_B2B:
    case VTSS_SERDES_MODE_SFI_PR_NONE:
    case VTSS_SERDES_MODE_SFI_KR:
    case VTSS_SERDES_MODE_SFI:         {
        /* 10G LAN is 10.3125 GHz i.e. 10GHz 66/64 bit encoded */
        f_pll.f_pll_khz = 10000000;
        f_pll.ratio_num = 66;
        f_pll.ratio_den = 64;
        /* setup the config for TX direction */
        config_tx.f_pll = f_pll;
        config_tx.if_width = 32;
        config_tx.mute = (mode == VTSS_SERDES_MODE_IDLE) ? TRUE : FALSE;
        /* setup the config for RX direction */
        config_rx.f_pll = f_pll;
        config_rx.if_width = 32;
        config_rx.preset = preset;
        /* setup the config for APC */
        config_apc.f_pll = f_pll;
        config_apc.if_width = 32;
        config_apc.preset = preset;
        break;
    }

    case VTSS_SERDES_MODE_2G5: {
        f_pll.f_pll_khz = 2500000;
        f_pll.ratio_num = 10;
        f_pll.ratio_den = 8;
        /* setup the config for TX direction */
        config_tx.f_pll = f_pll;
        config_tx.if_width = 10;
        /* setup the config for RX direction */
        config_rx.f_pll = f_pll;
        config_rx.if_width = 10;
        config_rx.preset = preset;
        /* setup the config for APC */
        config_apc.f_pll = f_pll;
        config_apc.if_width = 10;
        config_apc.preset = preset;
        break;
    }

    case VTSS_SERDES_MODE_SGMII:
    case VTSS_SERDES_MODE_1000BaseX: {
        f_pll.f_pll_khz = 1000000;
        f_pll.ratio_num = 10;
        f_pll.ratio_den = 8;
        /* setup the config for TX direction */
        config_tx.f_pll = f_pll;
        config_tx.if_width = 10;
        /* setup the config for RX direction */
        config_rx.f_pll = f_pll;
        config_rx.if_width = 10;
        config_rx.preset = preset;
        /* setup the config for APC */
        config_apc.f_pll = f_pll;
        config_apc.if_width = 10;
        config_apc.preset = preset;
        break;
    }

    case VTSS_SERDES_MODE_100FX: {
        f_pll.f_pll_khz = 1000000;
        f_pll.ratio_num = 10;
        f_pll.ratio_den = 8;
        /* setup the config for TX direction */
        config_tx.f_mode = VTSS_SD10G65_MODE_FX100;
        config_tx.if_width = 10;
        /* setup the config for RX direction */
        config_rx.f_mode = VTSS_SD10G65_MODE_FX100;
        config_rx.if_width = 10;
        config_rx.preset = preset;
        /* setup the config for APC */
        config_apc.f_pll = f_pll;
        config_apc.if_width = 10;
        config_apc.ib_cal_only = TRUE;
        break;
    }

    default: {
        VTSS_E("invalid parameter value for serdes mode:%d\n", mode);
        return VTSS_RC_ERROR;
    }
    }

    /* Apply TX, RX and APC config to the chip*/
#if defined(VTSS_ARCH_SERVAL_T)
    VTSS_RC(vtss_servalt_sd10g_setup_tx(vtss_state, config_tx, port));
    if (mode == VTSS_SERDES_MODE_IDLE) {
        return rc;
    }
    VTSS_RC(vtss_servalt_sd10g_setup_rx(vtss_state, config_rx, port));
    VTSS_RC(vtss_servalt_apc10g_setup(vtss_state, config_apc, port));
#elif defined(VTSS_ARCH_JAGUAR_2_C)
    VTSS_RC(vtss_jaguar2c_sd10g_setup_tx(vtss_state, config_tx, port));
    if (mode == VTSS_SERDES_MODE_IDLE) {
        return rc;
    }
    VTSS_RC(vtss_jaguar2c_sd10g_setup_rx(vtss_state, config_rx, port));
    VTSS_RC(vtss_jaguar2c_apc10g_setup(vtss_state, config_apc, port));
#else /* VTSS_ARCH_JAGUAR_2_B */
    VTSS_RC(vtss_jaguar2_sd10g_setup_tx(vtss_state, config_tx, port));
    if (mode == VTSS_SERDES_MODE_IDLE) {
        return rc;
    }
    VTSS_RC(vtss_jaguar2_sd10g_setup_rx(vtss_state, config_rx, port));
    VTSS_RC(vtss_jaguar2_apc10g_setup(vtss_state, config_apc, port));
#endif
    return rc;
}

#endif /* VTSS_ARCH_JAGUAR_2 */
