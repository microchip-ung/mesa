// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/* Trace group */
#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

// Avoid "vtss_api.h not used in module vtss_phy_ewis.c"
/*lint --e{766} */

#include "vtss_phy_api.h"
#if defined(VTSS_FEATURE_WIS)
#include "../common/vtss_phy_common.h"
#include "vtss_wis_api.h"


#if defined(VTSS_CHIP_10G_PHY)
#define VTSS_PHY_EWIS_MMD_WRITE_MASK(port_no, mmd, addr, value, mask) VTSS_RC(vtss_phy_ewis_write_mask(vtss_state, port_no, mmd, addr, value, mask))

#define VTSS_PHY_EWIS_BIT_SET(val, pos)   (val | (1 << pos))
#define VTSS_PHY_EWIS_BIT_RESET(val, pos) (val & ~(1 << pos))

/* ================================================================= *
 *  Static Functions
 * ================================================================= */
static vtss_rc vtss_phy_ewis_write(vtss_state_t         *vtss_state,
                                   const vtss_port_no_t port_no,
                                   const u16            mmd,
                                   const u32            addr,
                                   const u16            value)
{
    /* Write */
    if ((vtss_state->init_conf.spi_read_write != NULL ||
         vtss_state->init_conf.spi_32bit_read_write != NULL) &&
        (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_VENICE ||
         vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU)) {
        u32 val = (u32)value;
        if (vtss_state->init_conf.spi_32bit_read_write != NULL) {
            VTSS_RC(vtss_state->init_conf.spi_32bit_read_write(vtss_state, port_no, 0, (u8)mmd, (u16)addr, &val));
        } else {
            VTSS_RC(vtss_phy_10g_spi_read_write(vtss_state, port_no, 0, (u8)mmd, (u16)addr, &val));
        }
    } else {
        vtss_mmd_write_t     mmd_write = vtss_state->init_conf.mmd_write;
        VTSS_RC(mmd_write(vtss_state, port_no, mmd, addr, value));
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_read(vtss_state_t         *vtss_state,
                                  const vtss_port_no_t port_no,
                                  const u16            mmd,
                                  const u32            addr,
                                  u16                  *value)
{
    if ((vtss_state->init_conf.spi_read_write != NULL ||
         vtss_state->init_conf.spi_32bit_read_write != NULL) &&
        (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_VENICE ||
         vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU)) {
        u32 val;
        if (vtss_state->init_conf.spi_32bit_read_write != NULL) {
            VTSS_RC(vtss_state->init_conf.spi_32bit_read_write(vtss_state, port_no, 1, (u8)mmd, (u16)addr, &val));
        } else {
            VTSS_RC(vtss_phy_10g_spi_read_write(vtss_state, port_no, 1, (u8)mmd, (u16)addr, &val));
        }
        *value = (u16)val;
    } else {
        vtss_mmd_read_t     mmd_read = vtss_state->init_conf.mmd_read;
        VTSS_RC(mmd_read(vtss_state, port_no, mmd, addr, value));
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_write_mask(vtss_state_t         *vtss_state,
                                        const vtss_port_no_t port_no,
                                        const u16            mmd,
                                        const u32            addr,
                                        const u16            value,
                                        const u16            mask)
{
    u16              val;

    /* Read-modify-write */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, mmd, addr, &val));
    VTSS_RC(vtss_phy_ewis_write(vtss_state, port_no, mmd, addr, (val & ~mask) | (value & mask)));

    return VTSS_RC_OK;
}

static vtss_rc vtss_mmd_warm_wr_masked(vtss_state_t         *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const u16            mmd,
                                       const u32            addr,
                                       const u16            value,
                                       const u16            mask,
                                       const u16            chk_mask,
                                       const char           *function,
                                       const u16            line)
{
    u16  val;

    if (vtss_state->sync_calling_private) {
        VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, mmd, addr, &val));
        if ((val ^ value) & mask & chk_mask) { /* Change in bit field */
            VTSS_I("Warm start synch. field changed: Port:%u MMD:%d Register:0x%X", port_no, mmd, addr);
            VTSS_I("Mask:0x%X Chip value:0x%X API value:0x%X", mask, val, value);
            VTSS_I("Function:%s, Line:%d (chk_mask:0x%X)", function, line, chk_mask);
            VTSS_PHY_EWIS_MMD_WRITE_MASK(port_no, mmd, addr, value, mask);
        }
    } else {
        VTSS_PHY_EWIS_MMD_WRITE_MASK(port_no, mmd, addr, value, mask);
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_mmd_warm_wr(vtss_state_t         *vtss_state,
                                const vtss_port_no_t port_no,
                                const u16            mmd,
                                const u32            addr,
                                const u16            value,
                                const char           *function,
                                const u16            line)
{
    return vtss_mmd_warm_wr_masked(vtss_state, port_no, mmd, addr, value, 0xFFFF, 0xFFFF, function, line);
}

// Macro for doing warm start register writes. Checks if the register has changed. Also inserts the calling line number when doing register writes. Useful for debugging warm start,
#define VTSS_PHY_WARM_WR_MASKED(port_no, mmd, addr, value, mask) vtss_mmd_warm_wr_masked(vtss_state, port_no, mmd, addr, value, mask, 0xFFFF, __FUNCTION__,  __LINE__)

// See VTSS_PHY_WARM_WR_MASKED. Some registers may not contain the last value written (e.g. self clearing bits), and therefor must be written without doing read check.
// This is possible with this macro which contains a "chk_mask" bit mask for selecting which bit to do read check of. Use this function with care and ONLY with registers there the read value doesn't reflect the last written value.
#define VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, mmd, addr, value, mask, chk_mask) vtss_mmd_warm_wr_masked(vtss_state, port_no, mmd, addr, value, mask, chk_mask, __FUNCTION__, __LINE__)

// Macro that inserts the calling line number when doing register writes. Useful for debugging warm start,
#define VTSS_PHY_WARM_WR(port_no, mmd, addr, value) vtss_mmd_warm_wr(vtss_state, port_no, mmd, addr, value, __FUNCTION__, __LINE__)

static vtss_port_no_t pma_port(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    /* Only one PMA in VSC8487 at channel 0  */
    if (vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8487) {
        return vtss_state->phy_10g_state[port_no].phy_api_base_no;
    }
    return port_no;
}

static vtss_rc vtss_phy_ewis_events_force(vtss_state_t *vtss_state,
                                          vtss_port_no_t port_no,
                                          const BOOL enable,
                                          const vtss_ewis_event_t   ev_force)
{
    u16 mask_rega = 0x00;
    u16 mask_regb = 0x00;

    mask_rega = 0xEC30;
    mask_regb = 0xEC31;

    VTSS_D("EWIS events conf set port - [%d] Channel-Id - [%d] mask_rega - [%x]"
           "mask_regb - [%x] event_mask-[%" PRIx64 "]\n", (unsigned int)port_no,
           vtss_state->phy_10g_state[port_no].channel_id, mask_rega, mask_regb, ev_force);

    if (ev_force & VTSS_EWIS_SEF_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0080 : 0, 0x0080);
    }
    if (ev_force & VTSS_EWIS_FPLM_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0400 : 0, 0x0400);
    }
    if (ev_force & VTSS_EWIS_FAIS_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x1000 : 0, 0x1000);
    }
    if (ev_force & VTSS_EWIS_LOF_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0040 : 0, 0x0040);
    }
    if (ev_force & VTSS_EWIS_LOS_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_rega, (enable) ? 0x0800 : 0, 0x0800);
    }
    if (ev_force & VTSS_EWIS_RDIL_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_rega, (enable) ? 0x0004 : 0, 0x0004);
    }
    if (ev_force & VTSS_EWIS_AISL_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_rega, (enable) ? 0x0008 : 0, 0x0008);
    }
    if (ev_force & VTSS_EWIS_LCDP_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0004 : 0, 0x0004);
    }
    if (ev_force & VTSS_EWIS_PLMP_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x4000 : 0, 0x4000);
    }
    if (ev_force & VTSS_EWIS_AISP_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_rega, (enable) ? 0x0002 : 0, 0x0002);
    }
    if (ev_force & VTSS_EWIS_LOPP_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_rega, (enable) ? 0x0001 : 0, 0x0001);
    }
    if (ev_force & VTSS_EWIS_MODULE_EV) {
        /* Note :: Forcing a module event is not possible */
    }
    if (ev_force & VTSS_EWIS_TXLOL_EV) {
        /* Note :: Forcing a TXLOL lock event is not possible */
    }
    if (ev_force & VTSS_EWIS_RXLOL_EV) {
        /* Note :: Forcing a RXLOL lock event is not possible */
    }
    if (ev_force & VTSS_EWIS_LOPC_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_rega, (enable) ? 0x1000 : 0, 0x1000);
    }
    if (ev_force & VTSS_EWIS_UNEQP_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x8000 : 0, 0x8000);
    }
    if (ev_force & VTSS_EWIS_FEUNEQP_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0800 : 0, 0x0800);
    }
    if (ev_force & VTSS_EWIS_FERDIP_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x2000 : 0, 0x2000);
    }
    if (ev_force & VTSS_EWIS_REIL_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0100 : 0, 0x0100);
    }
    if (ev_force & VTSS_EWIS_REIP_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0200 : 0, 0x0200);
    }
    if (ev_force &  VTSS_EWIS_HIGH_BER_EV) {
        /* Note :: Forcing a HIBER event is not possible */
    }
    if (ev_force & VTSS_EWIS_PCS_RECEIVE_FAULT_PEND) {
        /* Note :: Forcing a PCS receive event is not possible */
    }
    if (ev_force & VTSS_EWIS_B1_NZ_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0020 : 0, 0x0020);
    }
    if (ev_force & VTSS_EWIS_B2_NZ_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0010 : 0, 0x0010);
    }
    if (ev_force & VTSS_EWIS_B3_NZ_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0008 : 0, 0x0008);
    }
    if (ev_force & VTSS_EWIS_REIL_NZ_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0002 : 0, 0x0002);
    }
    if (ev_force & VTSS_EWIS_REIP_NZ_EV) {
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, mask_regb, (enable) ? 0x0001 : 0, 0x0001);
    }
    if (ev_force & VTSS_EWIS_B1_THRESH_EV) {
        /* Note :: Forcing a B1 threshold event is not possible */
    }
    if (ev_force & VTSS_EWIS_B2_THRESH_EV) {
        /* Note :: Forcing a B1 threshold event is not possible */
    }
    if (ev_force & VTSS_EWIS_B3_THRESH_EV) {
        /* Note :: Forcing a B1 threshold event is not possible */
    }
    if (ev_force & VTSS_EWIS_REIL_THRESH_EV) {
        /* Note :: Forcing a B1 threshold event is not possible */
    }
    if (ev_force & VTSS_EWIS_REIP_THRESH_EV) {
        /* Note :: Forcing a B1 threshold event is not possible */
    }

    return VTSS_RC_OK;
}

/* ================================================================= *
 *  VTSS_State initialization
 * ================================================================= */
/**
 * \brief Static Initialization of the configuration data base in the vtss_state.
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 *
 * \return Return code.
 **/


static vtss_rc vtss_phy_ewis_static_conf_set(vtss_state_t *vtss_state,
                                             const vtss_port_no_t port_no)
{
    vtss_ewis_static_conf_t static_conf;
    vtss_ewis_cons_act_t    acti;
    vtss_ewis_force_mode_t  force_mode;
    u16 reg_val = 0;
    BOOL enable = FALSE;
    vtss_ewis_tti_t sec_txti,
                    path_txti;
    u16  sec_reg_val = 0,
         path_reg_val = 0;
    u16 reg_ct = 0;


    static_conf = vtss_state->ewis_conf[port_no].static_conf;

    /* WIS Vendor Specific Tx Control 1 (2xE5FF)*/
    reg_val =  static_conf.ewis_txctrl1;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xE5FF, reg_val);

    /* WIS Vendor Specific Tx Control 2 (2xE600)*/
    reg_val =  static_conf.ewis_txctrl2;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xE600, reg_val);

    /* E-WIS Rx Control 1 (2xEC10)*/
    reg_val =  static_conf.ewis_rx_ctrl1;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEC10, reg_val);

    /* E-WIS Mode Control (2xEC40)*/
    reg_val =  static_conf.ewis_mode_ctrl;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEC40, reg_val);

    /* E-WIS Tx A1/A2 Octets (2xE611)*/
    reg_val =  static_conf.ewis_tx_a1_a2;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xE611, reg_val);

    /* E-WIS Tx C2/H1 Octets (2xE615)*/
    reg_val =  static_conf.ewis_tx_c2_h1;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xE615, reg_val);

    /* E-WIS Tx H2/H3 Octets (2xE616)*/
    reg_val =  static_conf.ewis_tx_h2_h3;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xE616, reg_val);

    /* E-WIS Rx Framer Control 1 (2xEC00)*/
    reg_val =  static_conf.ewis_rx_frm_ctrl1;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEC00, reg_val);

    /* E-WIS Rx Framer Control 2 (2xEC01)*/
    reg_val =  static_conf.ewis_rx_frm_ctrl2;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEC01, reg_val);

    /* E-WIS Loss of Frame Control 1 (2xEC02)*/
    reg_val =  static_conf.ewis_lof_ctrl1;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEC02, reg_val);

    /* E-WIS Loss of Frame Control 2 (2xEC03)*/
    reg_val =  static_conf.ewis_lof_ctrl2;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEC03, reg_val);

    /* E-WIS Rx Error Force Control 1 (2xEC30)*/
    reg_val =  static_conf.ewis_rx_err_frc1;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEC30, reg_val);

    /* E-WIS Performance Monitor Control (2xEC60) */
    reg_val =  static_conf.ewis_pmtick_ctrl;
    VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, MMD_WIS, 0xEC60, reg_val, 0xFFFE, 0x1);

    /* E-WIS Counter Configuration (2xEC61)*/
    reg_val =  static_conf.ewis_cnt_cfg;
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEC61, reg_val);

    /* Set the Consequent Actions to Default */
    acti = vtss_state->ewis_conf[port_no].section_cons_act;
    reg_val = 0x00;
    (acti.fault.fault_on_feplmp == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 10)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 10));
    (acti.fault.fault_on_feaisp == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 9)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 9));
    (acti.fault.fault_on_rdil   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 8)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 8));
    (acti.fault.fault_on_sef    == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 7)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 7));
    (acti.fault.fault_on_lof    == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 6)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 6));
    (acti.fault.fault_on_los    == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 5)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 5));
    (acti.fault.fault_on_aisl   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 4)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 4));
    (acti.fault.fault_on_lcdp   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 3)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 3));
    (acti.fault.fault_on_plmp   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 2)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 2));
    (acti.fault.fault_on_aisp   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 1)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 1));
    (acti.fault.fault_on_lopp   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 0)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 0));
    /* Write to WIS_FAULT_MASK (2xEE07) */
    VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, MMD_WIS, 0xEE07, reg_val, 0x07FF, 0x07FF);

    reg_val = 0x00;
    /* Read from EWIS Rx to Tx control */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xEDFF, &reg_val));
    (acti.aisl.ais_on_los == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 5)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 5));
    (acti.aisl.ais_on_lof == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 4)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 4));

    (acti.rdil.rdil_on_los   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 2)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 2));
    (acti.rdil.rdil_on_lof   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 1)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 1));
    (acti.rdil.rdil_on_lopc  == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 3)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 3));
    (acti.rdil.rdil_on_ais_l == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 0)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 0));
    /* Write to EWIS Rx to Tx control */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEDFF, reg_val);

    /* Configure the Force configuration */
    force_mode = vtss_state->ewis_conf[port_no].force_mode;

    enable = force_mode.line_rx_force.force_ais;
    /* E-WIS Rx Error Force Control 1 (2xEC30) ::3 FRC_RX_AISL */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC30, (enable) ? 0x0008 : 0, 0x0008);

    enable = force_mode.line_rx_force.force_rdi;
    /* E-WIS Rx Error Force Control 1 (2xEC30) ::2 FRC_RX_RDIL*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC30, (enable) ? 0x0004 : 0, 0x0004);

    enable = force_mode.line_tx_force.force_ais;
    /* WIS Vendor Specific Tx Control 2 (2xE600)  ::1 FRC_TX_AISL */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE600, (enable) ? 0x0002 : 0, 0x0002);

    enable = force_mode.line_tx_force.force_rdi;
    /* WIS Vendor Specific Tx Control 2 (2xE600)  ::2 FRC_TX_RDI*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE600, (enable) ? 0x0004 : 0, 0x0004);

    enable = force_mode.path_force.force_uneq;
    /* E-WIS Rx Error Force Control 2 (2xEC31)  ::15 FRC_RX_UNEQP*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC31, (enable) ? 0x8000 : 0, 0x8000);

    enable = force_mode.path_force.force_rdi;
    /* E-WIS Rx Error Force Control 2 (2xEC31)  ::13 FRC_RX_RDIP */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC31, (enable) ? 0x2000 : 0, 0x2000);

    sec_txti = vtss_state->ewis_conf[port_no].section_txti;
    /* Section TXTI (J0) Mode Length is configured in 2xE700::3:2
     * Mask = 0x000c
     */
    switch (sec_txti.mode) {
    case TTI_MODE_1:
        sec_reg_val = 0x000C;
        break;
    case TTI_MODE_16:
        sec_reg_val = 0x0000;
        break;
    case TTI_MODE_64:
        sec_reg_val = 0x0004;
        break;
    default :
        break;
    }
    /* Configure the J0, Section Transmit Trace Identifier Length */
    /* Configure J0_TX_LEN E-WIS Tx Trace Message Length Control (2xE700)*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE700, sec_reg_val, 0x000C);
    /* Configure J0_RX_LEN E-WIS Rx Trace Message Length Control (2xEC20)  */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC20, sec_reg_val, 0x000C);

    path_txti = vtss_state->ewis_conf[port_no].path_txti;
    /* Path TXTI (J1) Mode Length is configured in 2xE700::1:0
     * Mask = 0x0003
     */
    switch (path_txti.mode) {
    case TTI_MODE_1:
        path_reg_val = 0x0003;
        break;
    case TTI_MODE_16:
        path_reg_val = 0x0000;
        break;
    case TTI_MODE_64:
        path_reg_val = 0x0001;
        break;
    default :
        break;
    }
    /* Configure the J1, Path Transmit Trace Identifier Length */
    /* Configure J1_TX_LEN E-WIS Tx Trace Message Length Control (2xE700)*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE700, path_reg_val, 0x0003);
    /* Configure J1_RX_LEN E-WIS Rx Trace Message Length Control (2xEC20)  */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC20, path_reg_val, 0x0003);

    /* Note :: Irrespective of the Length of the configured Section/Path Transmit
     * Trace Identifier length, all the 64 bytes in the txti variable is configured
     * in the registers
     */
    for (reg_ct = 0; reg_ct < 32; reg_ct++) {
        sec_reg_val = sec_txti.tti[(reg_ct * 2) + 1] << 8 | sec_txti.tti[(reg_ct * 2)];
        path_reg_val = path_txti.tti[(reg_ct * 2) + 1] << 8 | path_txti.tti[(reg_ct * 2)];
        if (reg_ct < 8) {
            /* Section TTI 0-15 Bytes should be written in registers 0x0040 - 0x0047 */
            VTSS_PHY_WARM_WR(port_no, MMD_WIS, (0x0040 + reg_ct), sec_reg_val);
            /* Path TTI 0-15 Bytes should be written in registers 0x0027 - 0x002E */
            VTSS_PHY_WARM_WR(port_no, MMD_WIS, (0x0027 + reg_ct), path_reg_val);
        } else {
            /* Section TTI 16-63 Bytes should be written in registers 0xE800 - 0xE817 */
            VTSS_PHY_WARM_WR(port_no, MMD_WIS, (0xE800 + (reg_ct - 8)), sec_reg_val);
            /* Path TTI 16-63 Bytes should be written in registers 0xEA00 - 0xEA17 */
            VTSS_PHY_WARM_WR(port_no, MMD_WIS, (0xEA00 + (reg_ct - 8)), path_reg_val);

        }
    }

    /* Clear all the interrupts
     *    Mask-A             Mask-B
     *    0xEE01-0x0EFF      0xEE02 - 0x0EFF
     *    0xEE05-0xFFFF      0xEE06 - 0xFFFF
     *    0xEE09-0x001F      0xEE0A - 0x001F
     *
     */
    //reg_val = 0;
    //VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEE01, reg_val, 0x0EFF);
    //VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEE02, reg_val, 0x0EFF);
    //VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEE05, reg_val, 0xFFFF);
    //VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEE06, reg_val, 0xFFFF);
    //VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEE09, reg_val, 0x001F);
    //VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEE0A, reg_val, 0x001F);

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_force_conf_set(vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no)
{
    vtss_ewis_force_mode_t  force_mode;
    BOOL enable = FALSE;

    force_mode = vtss_state->ewis_conf[port_no].force_mode;

    enable = force_mode.line_rx_force.force_ais;
    /* E-WIS Rx Error Force Control 1 (2xEC30) ::3 FRC_RX_AISL */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC30, (enable) ? 0x0008 : 0, 0x0008);

    enable = force_mode.line_rx_force.force_rdi;
    /* E-WIS Rx Error Force Control 1 (2xEC30) ::2 FRC_RX_RDIL*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC30, (enable) ? 0x0004 : 0, 0x0004);

    enable = force_mode.line_tx_force.force_ais;
    /* WIS Vendor Specific Tx Control 2 (2xE600)  ::1 FRC_TX_AISL */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE600, (enable) ? 0x0002 : 0, 0x0002);

    enable = force_mode.line_tx_force.force_rdi;
    /* WIS Vendor Specific Tx Control 2 (2xE600)  ::2 FRC_TX_RDI*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE600, (enable) ? 0x0004 : 0, 0x0004);

    enable = force_mode.path_force.force_uneq;
    /* E-WIS Rx Error Force Control 2 (2xEC31)  ::15 FRC_RX_UNEQP*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC31, (enable) ? 0x8000 : 0, 0x8000);

    enable = force_mode.path_force.force_rdi;
    /* E-WIS Rx Error Force Control 2 (2xEC31)  ::13 FRC_RX_RDIP */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC31, (enable) ? 0x2000 : 0, 0x2000);

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_tx_oh_set(vtss_state_t *vtss_state,
                                       const vtss_port_no_t port_no)
{
    vtss_ewis_tx_oh_t tx_oh;
    u16 reg_val = 0;

    tx_oh = vtss_state->ewis_conf[port_no].tx_oh;

    /* Section Overhead configuration */
    /* D1 :: EWIS_TX_F1_D1: E-WIS Tx F1/D1 Octets (2xE613) */
    reg_val = (tx_oh.tx_f1 << 8) | tx_oh.tx_dcc_s[0];
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE613, reg_val, 0xffff);

    /* D2 & D3 :: EWIS_TX_D2_D3: E-WIS Tx D2/D3 Octets (2xE614) */
    reg_val = (tx_oh.tx_dcc_s[1] << 8) | tx_oh.tx_dcc_s[2];
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE614, reg_val, 0xffff);

    /* E1 :: EWIS_TX_Z0_E1: E-WIS Tx Z0/E1 Octets (2xE612) */
    reg_val = tx_oh.tx_e1;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE612, reg_val, 0x00ff);

    /* Line Overhead configuration */
    /* D4 & D5 :: EWIS_TX_D4_D5: E-WIS Tx D4/D5 Octets (2xE619) */
    reg_val = (tx_oh.tx_dcc_l[0] << 8) | tx_oh.tx_dcc_l[1];
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE619, reg_val, 0xffff);

    /* D6 :: EWIS_TX_D6_H4: E-WIS Tx D6/H4 Octets (2xE61A) */
    reg_val = (tx_oh.tx_dcc_l[2] << 8);
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61A, reg_val, 0xff00);

    /* D7 & D8 ::E-WIS Tx D7/D8 Octets (2xE61B) */
    reg_val = (tx_oh.tx_dcc_l[3] << 8) | tx_oh.tx_dcc_l[4];
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61B, reg_val, 0xffff);

    /* D9 :: EWIS_TX_D9_Z3: E-WIS Tx D9/Z3 Octets (2xE61C) */
    reg_val = (tx_oh.tx_dcc_l[5] << 8);
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61C, reg_val, 0xff00);

    /* D10 & D11 :: E-WIS Tx D10/D11 Octets (2xE61D) */
    reg_val = (tx_oh.tx_dcc_l[6] << 8) | tx_oh.tx_dcc_l[7];
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61D, reg_val, 0xffff);

    /* D12 :: E-WIS Tx D12/Z4 Octets (2xE61E) */
    reg_val = (tx_oh.tx_dcc_l[8] << 8);
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61E, reg_val, 0xff00);

    /* E2 :: E-WIS Tx Z2/E2 Octets (2xE620)*/
    reg_val = tx_oh.tx_e2;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE620, reg_val, 0x00ff);

    /* K1 :: E-WIS Tx G1/K1 Octets (2xE617) */
    reg_val = (tx_oh.tx_k1_k2 & 0xff00) >> 8;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE617, reg_val, 0x00ff);

    /* K2 :: E-WIS Tx K2/F2 Octets (2xE618) */
    reg_val = (tx_oh.tx_k1_k2 & 0x00ff) << 8;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE618, reg_val, 0xff00);

    /* S1 :: E-WIS Tx S1/Z1 Octets (2xE61F) */
    reg_val = (tx_oh.tx_s1 << 8);
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61F, reg_val, 0xff00);

    /* Z1 :: E-WIS Tx S1/Z1 Octets (2xE61F) */
    reg_val = (tx_oh.tx_z1_z2 & 0xff00) >> 8;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61F, reg_val, 0x00ff);

    /* Z2 :: E-WIS Tx Z2/E2 Octets (2xE620) */
    reg_val = (tx_oh.tx_z1_z2 & 0x00ff) << 8;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE620, reg_val, 0xff00);

    /* Path Overhead configuration */
    /* C2 :: E-WIS Tx C2/H1 Octets (2xE615) */
    reg_val = (tx_oh.tx_c2 << 8);
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE615, reg_val, 0xff00);

    /* F2 :: E-WIS Tx K2/F2 Octets (2xE618)*/
    reg_val = tx_oh.tx_f2;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE618, reg_val, 0x00ff);

    /* N1 :: E-WIS Tx N1 Octet (2xE621)*/
    reg_val = (tx_oh.tx_n1 << 8);
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE621, reg_val, 0xff00);

    /* Z3 :: E-WIS Tx D9/Z3 Octets (2xE61C)*/
    reg_val = (tx_oh.tx_z3_z4 & 0xff00) >> 8;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61C, reg_val, 0x00ff);

    /* Z4 :: E-WIS Tx D12/Z4 Octets (2xE61E)*/
    reg_val = tx_oh.tx_z3_z4 & 0x00ff;
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE61E, reg_val, 0x00ff);

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_mode_conf_set(vtss_state_t *vtss_state,
                                           vtss_port_no_t port_no)
{
    vtss_ewis_mode_t mode;
    u16 reg_val = 0x00;

    mode = vtss_state->ewis_conf[port_no].ewis_mode;
    VTSS_D("enter port_no %d, mode %d ", port_no, mode);
    if (mode == VTSS_WIS_OPERMODE_WIS_MODE) {
        /* Configure for the WIS mode */
        VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0x0007, 1);         /* WIS Control, Enable WAN MODE */
        /* Configure the TX_C2 and C2_EXP bytes for configuring the STS Path Signal Label */
        /* TX_C2 */
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE615, 0x1A00, 0xff00);
        /* C2_EXP */
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC40, 0x001A, 0x00ff);
    } else if (mode == VTSS_WIS_OPERMODE_STS192) {
    } else if (mode == VTSS_WIS_OPERMODE_STM64) {
    } else if (mode == VTSS_WIS_OPERMODE_DISABLE) {
        /* Disable the WIS mode & configure the Reference clocks to operate in LAN mode */
        /* Regular LAN mode with a single Ref clock: XREFCLK @ 156.25Mhz */
        VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0x0007, 0);         /* WIS Control, Disable WAN MODE */
    }

    /* Read and check the status */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_PMA, 0xA101, &reg_val));

    if ((mode != VTSS_WIS_OPERMODE_DISABLE) && (!(reg_val & (1 << 3)))) {
        VTSS_E("WAN API mode does not match the actual chip mode :: Value - [%x]", reg_val);
    }
    if (vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8487 ||
        vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8488) {
        /* Reset the PMA Tx & Rx */
        VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, MMD_PMA, 0xAE00, 0x0006, 0x0006, 0x0);

        /* Reset the CRU PLL,Force CRU to lock to reference PMA Rx EDC Control (1x8003)*/
        /* Reset */
        VTSS_PHY_WARM_WR_MASKED_CHK_MASK(pma_port(vtss_state, port_no), MMD_PMA, 0x8003, 0x0001, 0x0001, 0x0);
        /* Clear */
        VTSS_PHY_WARM_WR_MASKED_CHK_MASK(pma_port(vtss_state, port_no), MMD_PMA, 0x8003, 0x0000, 0x0001, 0x0);
    } else if (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_VENICE ||
               vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU) {
        VTSS_D("No need to PMA reset");
    } else {
        VTSS_E("WIS not supported for current PHY port %d", port_no);
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_reset(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_D("EWIS reset on port - [%d] \n", (unsigned int)port_no);
    /* 8487,8488 family:
     * Set the reset for the following fields
     * Reset Tx WIS
     * Reset TX WIS FIFO
     * Reset Tx WIS FIFO Pointer
     * Reset WIS Interrupt Tree
     * Reset Rx WIS
     * 0x1E8
     *
     * Venice family:
     * Set the reset for the following fields
     * Reset WIS Interrupt Tree
     * Reset INGRESS WIS
     * Reset EGR WIS
     * Reset FIFO_EGR and LINE_MAC_EGR
     * 0xAE00 = 0x0202, 0xAE01 = 0x0002, 0xAE01 = 0x0050
     */
    if (vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8487 ||
        vtss_state->phy_10g_state[port_no].type == VTSS_PHY_TYPE_8488) {
        VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, MMD_PMA, 0xAE00, 0x1E8, 0x1E8, 0x0);
    } else if (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_VENICE || vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU)  {
        VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, MMD_PMA, 0xAE00, 0x0202, 0x0202, 0x0);
        VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, MMD_PMA, 0xAE01, 0x0002, 0x0002, 0x0);
        VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, MMD_PMA, 0xAE01, 0x0050, 0x0050, 0x0);
        VTSS_D("WIS reset");
    } else {
        VTSS_E("WIS not supported for current PHY port %d", port_no);
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_action_set(vtss_state_t *vtss_state,
                                        vtss_port_no_t port_no)
{
    vtss_ewis_cons_act_t acti;
    u16 reg_val = 0x00;

    acti = vtss_state->ewis_conf[port_no].section_cons_act;
    reg_val = 0x00;
    (acti.fault.fault_on_feplmp == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 10)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 10));
    (acti.fault.fault_on_feaisp == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 9)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 9));
    (acti.fault.fault_on_rdil   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 8)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 8));
    (acti.fault.fault_on_sef    == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 7)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 7));
    (acti.fault.fault_on_lof    == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 6)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 6));
    (acti.fault.fault_on_los    == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 5)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 5));
    (acti.fault.fault_on_aisl   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 4)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 4));
    (acti.fault.fault_on_lcdp   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 3)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 3));
    (acti.fault.fault_on_plmp   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 2)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 2));
    (acti.fault.fault_on_aisp   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 1)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 1));
    (acti.fault.fault_on_lopp   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 0)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 0));
    /* Write to WIS_FAULT_MASK (2xEE07) */
    VTSS_PHY_WARM_WR_MASKED_CHK_MASK(port_no, MMD_WIS, 0xEE07, reg_val, 0x07FF, 0x07FF);

    reg_val = 0x00;
    /* Read from EWIS Rx to Tx control */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xEDFF, &reg_val));
    (acti.aisl.ais_on_los == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 5)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 5));
    (acti.aisl.ais_on_lof == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 4)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 4));

    (acti.rdil.rdil_on_los   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 2)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 2));
    (acti.rdil.rdil_on_lof   == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 1)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 1));
    (acti.rdil.rdil_on_lopc  == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 3)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 3));
    (acti.rdil.rdil_on_ais_l == TRUE) ? (reg_val = VTSS_PHY_EWIS_BIT_SET(reg_val, 0)) : (reg_val = VTSS_PHY_EWIS_BIT_RESET(reg_val, 0));
    /* Write to EWIS Rx to Tx control */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEDFF, reg_val);

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_section_txti_set(vtss_state_t *vtss_state,
                                              vtss_port_no_t port_no)
{
    vtss_ewis_tti_t txti;
    u16 reg_val = 0;
    u16 reg_ct = 0;

    txti = vtss_state->ewis_conf[port_no].section_txti;
    /* Section TXTI (J0) Mode Length is configured in 2xE700::3:2
     * Mask = 0x000c
     */
    switch (txti.mode) {
    case TTI_MODE_1:
        reg_val = 0x000C;
        break;
    case TTI_MODE_16:
        reg_val = 0x0000;
        break;
    case TTI_MODE_64:
        reg_val = 0x0004;
        break;
    default :
        break;
    }
    /* Configure the J0, Section Transmit Trace Identifier Length */
    /* Configure J0_TX_LEN E-WIS Tx Trace Message Length Control (2xE700)*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE700, reg_val, 0x000C);
    /* Configure J0_RX_LEN E-WIS Rx Trace Message Length Control (2xEC20)  */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC20, reg_val, 0x000C);
    /* Note :: Irrespective of the Length of the configured Section Transmit
     * Trace Identifier length, all the 64 bytes in the txti variable is configured
     * in the registers
     */
    for (reg_ct = 0; reg_ct < 32; reg_ct++) {
        reg_val = txti.tti[(reg_ct * 2) + 1] << 8 | txti.tti[(reg_ct * 2)];
        if (reg_ct < 8) {
            /* Section TTI 0-15 Bytes should be written in registers 0x0040 - 0x0047 */
            VTSS_PHY_WARM_WR(port_no, MMD_WIS, (0x0040 + reg_ct), reg_val);
        } else {
            /* Section TTI 16-63 Bytes should be written in registers 0xE800 - 0xE817 */
            VTSS_PHY_WARM_WR(port_no, MMD_WIS, (0xE800 + (reg_ct - 8)), reg_val);
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_path_txti_set(vtss_state_t *vtss_state,
                                           vtss_port_no_t port_no)
{
    vtss_ewis_tti_t txti;
    u16 reg_val = 0;
    u16 reg_ct = 0;

    txti = vtss_state->ewis_conf[port_no].path_txti;
    /* Section TXTI (J1) Mode Length is configured in 2xE700::1:0
     * Mask = 0x0003
     */
    switch (txti.mode) {
    case TTI_MODE_1:
        reg_val = 0x0003;
        break;
    case TTI_MODE_16:
        reg_val = 0x0000;
        break;
    case TTI_MODE_64:
        reg_val = 0x0001;
        break;
    default :
        break;
    }
    /* Configure the J1, Section Transmit Trace Identifier Length */
    /* Configure J1_TX_LEN E-WIS Tx Trace Message Length Control (2xE700)*/
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xE700, reg_val, 0x0003);
    /* Configure J1_RX_LEN E-WIS Rx Trace Message Length Control (2xEC20)  */
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC20, reg_val, 0x0003);

    /* Note :: Irrespective of the Length of the configured Path Transmit
     * Trace Identifier length, all the 64 bytes in the txti variable is configured
     * in the registers
     */
    for (reg_ct = 0; reg_ct < 32; reg_ct++) {
        reg_val = txti.tti[(reg_ct * 2) + 1] << 8 | txti.tti[(reg_ct * 2)];
        if (reg_ct < 8) {
            /* Path TTI 0-15 Bytes should be written in registers 0x0027 - 0x002E */
            VTSS_PHY_WARM_WR(port_no, MMD_WIS, (0x0027 + reg_ct), reg_val);
        } else {
            /* Path TTI 16-63 Bytes should be written in registers 0xEA00 - 0xEA17 */
            VTSS_PHY_WARM_WR(port_no, MMD_WIS, (0xEA00 + (reg_ct - 8)), reg_val);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_test_mode_set(vtss_state_t *vtss_state,
                                           vtss_port_no_t port_no)
{
    vtss_ewis_test_conf_t test_conf;
    u16 reg_val = 0x00;

    memset(&test_conf , 0, sizeof(test_conf));
    test_conf = vtss_state->ewis_conf[port_no].test_conf;

    /*  Loopbacks: 2x0000.14 Enables WIS system loopback (loopback.J) */
    (test_conf.loopback == TRUE) ? (reg_val = 0x4000) : (reg_val = 0x0000);
    VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0x0000, reg_val, 0x4000);

    /* Read the 2x0007 register to read the current settings */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0007, &reg_val));
    switch (test_conf.test_pattern_gen) {
    case VTSS_WIS_TEST_MODE_DISABLE :
        reg_val &= ~0x001a;
        break;
    case VTSS_WIS_TEST_MODE_SQUARE_WAVE :
        /* Clear the other tests */
        reg_val &= ~0x001a;
        /* Configure for Square WAVE tests */
        reg_val |= 0x000a;
        break;
    case VTSS_WIS_TEST_MODE_PRBS31 :
        /* Clear the other tests */
        reg_val &= ~0x001a;
        /* Configure for PRBS31 test pattern generation */
        reg_val |= 0x0010;
        break;
    case VTSS_WIS_TEST_MODE_MIXED_FREQUENCY:
        /* Clear the other tests */
        reg_val &= ~0x001a;
        /* Configure for PRBS31 test pattern generation */
        reg_val |= 0x0002;
        break;
    default :
        return VTSS_RC_ERROR;
    }
    switch (test_conf.test_pattern_ana) {
    case VTSS_WIS_TEST_MODE_DISABLE :
        reg_val &= ~0x0024;
        break;
    case VTSS_WIS_TEST_MODE_SQUARE_WAVE :
        /* This test is not valid for pattern analyzer */
        return VTSS_RC_ERROR;
    case VTSS_WIS_TEST_MODE_PRBS31 :
        /* Clear the other tests */
        reg_val &= ~0x0024;
        /* Configure for PRBS31 test pattern analyzer */
        reg_val |= 0x0020;
        break;
    case VTSS_WIS_TEST_MODE_MIXED_FREQUENCY:
        /* Clear the other tests */
        reg_val &= ~0x0024;
        /* Configure for PRBS31 test pattern analyzer */
        reg_val |= 0x0004;
        break;
    default :
        return VTSS_RC_ERROR;
    }
    /* Write the 2x0007 register to update the test pattern settings */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0x0007, reg_val);

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_prbs31_err_inj_set(vtss_state_t *vtss_state,
                                                vtss_port_no_t port_no, const vtss_ewis_prbs31_err_inj_t *const inj)
{

    /* EWIS_PRBS31_ANA_CTRL: E-WIS PRBS31 Analyzer Control (2xEC50) */
    switch (*inj) {
    case EWIS_PRBS31_SINGLE_ERR:
        /* Write the 2xEC50::1 register for enabling PRBS31_FRC_ERR */
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC50, 0x0002, 0x0003);
        break;
    case EWIS_PRBS31_SAT_ERR:
        /* Write the 2xEC50::0 register for enabling PRBS31_FRC_SAT */
        VTSS_PHY_WARM_WR_MASKED(port_no, MMD_WIS, 0xEC50, 0x0001, 0x0003);
        break;
    default :
        /* PRBS31_SINGLE_ERR & PRBS31_SAT_ERR are self clearing bits */
        break;
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_test_status_get(vtss_state_t *vtss_state,
                                             vtss_port_no_t port_no, vtss_ewis_test_status_t *const test_status)
{
    u16 reg_val = 0x00;

    /* Read the register 2x0009 to read the test pattern error count */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0009, &reg_val));
    test_status->tstpat_cnt = reg_val;
    /* Read the register 2xEC51::0 E-WIS PRBS31 Analyzer Status (2xEC51)*/
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xEC51, &reg_val));
    test_status->ana_sync = (reg_val & 0x0001);

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_defects_get(vtss_state_t *vtss_state,
                                         vtss_port_no_t port_no, vtss_ewis_defects_t *const def)
{
    u16 reg_val = 0x00;
    u16 reg_val1 = 0x00;

    /* Read the register 2x0021 to read the current status of the defects */
    /* Read the Register twice to get the current status of the defects */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0021, &reg_val));
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0021, &reg_val));
    /* Loss of Signal */
    (reg_val & 0x0040) ? (def->dlos_s = TRUE) : (def->dlos_s = FALSE);
    /* Loss of Frame */
    (reg_val & 0x0080) ? (def->dlof_s = TRUE) : (def->dlof_s = FALSE);
    /* Line alarm indication signal */
    (reg_val & 0x0010) ? (def->dais_l = TRUE) : (def->dais_l = FALSE);
    /* Line remote defect indication */
    (reg_val & 0x0020) ? (def->drdi_l = TRUE) : (def->drdi_l = FALSE);
    /* Path alarm indication signal */
    (reg_val & 0x0002) ? (def->dais_p = TRUE) : (def->dais_p = FALSE);
    /* Loss of pointer Path */
    (reg_val & 0x0001) ? (def->dlop_p = TRUE) : (def->dlop_p = FALSE);
    def->duneq_p = FALSE;
    def->drdi_p = FALSE;
    /* loss of code-group delineation path */
    (reg_val & 0x0008) ? (def->dlcd_p = TRUE) : (def->dlcd_p = FALSE);
    /* Path Label mismatch */
    (reg_val & 0x0004) ? (def->dplm_p = TRUE) : (def->dplm_p = FALSE);

    /* Far End Path defects */
    /* far-end AIS-P/LOP-P */
    (reg_val & 0x0200) ? (def->dfais_p = TRUE) : (def->dfais_p = FALSE);

    /* far-end PLM-P/LCD-P defects */
    (reg_val & 0x0400) ? (def->dfplm_p = TRUE) : (def->dfplm_p = FALSE);

    /* Read the register 0xEE03 for Unequiped Path */
    if ((vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU) ||
        (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_VENICE)) {
        VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xee03, &reg_val1));
        (reg_val1 & 0x0400) ? (def->duneq_p = TRUE) : (def->duneq_p = FALSE);
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_status_get(vtss_state_t *vtss_state,
                                        vtss_port_no_t port_no, vtss_ewis_status_t *const status)
{
    u16 reg_val = 0x00;

    /* WIS Status 1 (2x0001) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0001, &reg_val));
    /* 2x0001::7:RO/LH = FAULT */
    if ( reg_val & 0x80) {
        status->fault = TRUE;
    } else {
        status->fault = FALSE;
    }
    /* 2x0001::2:RO/LL = LINK_STAT */
    if ( reg_val & 0x04) {
        status->link_stat = TRUE;
    } else {
        status->link_stat = FALSE;
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_section_acti_get(vtss_state_t *vtss_state,
                                              vtss_port_no_t port_no, vtss_ewis_tti_t *const acti)
{
    vtss_ewis_tti_t txti;
    u16 reg_val = 0;
    i16 reg_ct = 0, reg_len = 0;
    i16 idx_ct = 0, arr_idx = 0;

    memset(&txti, 0, sizeof(vtss_ewis_tti_t));
    memset(acti, 0, sizeof(vtss_ewis_tti_t));
    txti = vtss_state->ewis_conf[port_no].section_txti;
    switch (txti.mode) {
    case TTI_MODE_1:
        reg_len = 1;
        break;
    case TTI_MODE_16:
        reg_len = 8;
        break;
    case TTI_MODE_64:
        reg_len = 32;
        break;
    default :
        break;
    }
    /* Extract the Accepted Bytes from the registers */
    for (reg_ct = 0; reg_ct < reg_len; reg_ct++) {
        if (reg_ct < 8) {
            /* Section TTI 0-15 Accepted Bytes are read from registers 0x0048 - 0x004F */
            VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, (0x0048 + reg_ct), &reg_val));
        } else {
            /* Section TTI 16-63 Accepted Bytes are read from registers 0xE900 - 0xE917 */
            VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, (0xE900 + (reg_ct - 8)), &reg_val));
        }
        txti.tti[(reg_ct * 2) + 1] = (u8)((reg_val & 0xff00) >> 8);
        txti.tti[(reg_ct * 2)] = (u8)(reg_val & 0x00ff);
    }
    /* Update the acti based on the TTI_MODE */
    /* Update the acti based on the TTI_MODE */
    acti->mode = txti.mode;
    acti->valid = FALSE;
    txti.valid = FALSE;
    switch (txti.mode) {
    case TTI_MODE_1:
        /* Update Only 1 Byte */
        acti->tti[0] = txti.tti[0];
        acti->valid = TRUE;
        break;
    case TTI_MODE_16:
        for (reg_ct = 0; reg_ct < (reg_len * 2); reg_ct++) {
            if (txti.tti[reg_ct] & 0x80) {
                txti.tti[reg_ct] = '\0';
                acti->valid = TRUE;
                break;
            }
        }
        if (acti->valid == FALSE) {
            break;
        }

        for (idx_ct = reg_ct; idx_ct >= 0; idx_ct--) {
            if (txti.tti[idx_ct] & 0x80) {
                acti->valid = FALSE;
                break;
            }
            acti->tti[15 - (reg_ct - idx_ct)] = txti.tti[idx_ct];
        }
        for (idx_ct = 15; idx_ct > reg_ct; idx_ct-- ) {
            if (txti.tti[idx_ct] & 0x80) {
                acti->valid = FALSE;
                break;
            }
            acti->tti[idx_ct - (reg_ct + 1)] = txti.tti[idx_ct];
        }
        break;
    case TTI_MODE_64:
        for (reg_ct = 0; reg_ct < (reg_len * 2); reg_ct++) {
            if ((txti.tti[reg_ct] == 13) && (txti.tti[reg_ct + 1] == 10)) {
                txti.valid = TRUE;
                break;
            }
        }
        if (txti.valid == FALSE) {
            break;
        }
        reg_ct++;
        /* Since the TTi contains \n\r increase 2 bytes */
        for (idx_ct = (reg_ct + 1), arr_idx = 63; idx_ct <= 63; idx_ct++, arr_idx--) {
            if (txti.tti[idx_ct] & 0x80) {
                acti->valid = FALSE;
                break;
            }
            acti->tti[arr_idx] = txti.tti[idx_ct];
        }

        for (idx_ct = 0, arr_idx = reg_ct; idx_ct <= reg_ct; idx_ct++, arr_idx-- ) {
            if (txti.tti[idx_ct] & 0x80) {
                acti->valid = FALSE;
                break;
            }
            acti->tti[arr_idx] = txti.tti[idx_ct];
        }

        /* Reverse the Bytes */
        for (idx_ct = 0; idx_ct < 64; idx_ct++) {
            txti.tti[(63 - idx_ct)] = acti->tti[idx_ct];
        }
        *acti = txti;
        break;
    default :
        break;
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_path_acti_get(vtss_state_t *vtss_state,
                                           vtss_port_no_t port_no, vtss_ewis_tti_t *const acti)
{
    vtss_ewis_tti_t txti;
    u16 reg_val = 0;
    i16 reg_ct = 0, reg_len = 0;
    i16 idx_ct = 0, arr_idx = 0;

    memset(&txti, 0, sizeof(vtss_ewis_tti_t));
    memset(acti, 0, sizeof(vtss_ewis_tti_t));
    txti = vtss_state->ewis_conf[port_no].path_txti;
    switch (txti.mode) {
    case TTI_MODE_1:
        reg_len = 1;
        break;
    case TTI_MODE_16:
        reg_len = 8;
        break;
    case TTI_MODE_64:
        reg_len = 32;
        break;
    default :
        break;
    }
    /* Extract the Accepted Bytes from the registers */
    for (reg_ct = 0; reg_ct < reg_len; reg_ct++) {
        if (reg_ct < 8) {
            /* Path TTI 0-15 Accepted Bytes are read from registers 0x002F - 0x0036 */
            VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, (0x002F + reg_ct), &reg_val));
        } else {
            /* Path TTI 16-63 Accepted Bytes are read from registers 0xEB00 - 0xEB17 */
            VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, (0xEB00 + (reg_ct - 8)), &reg_val));
        }
        txti.tti[(reg_ct * 2) + 1] = (u8)((reg_val & 0xff00) >> 8);
        txti.tti[(reg_ct * 2)] = (u8)(reg_val & 0x00ff);
    }
    /* Update the acti based on the TTI_MODE */
    acti->mode = txti.mode;
    acti->valid = FALSE;
    txti.valid = FALSE;
    switch (txti.mode) {
    case TTI_MODE_1:
        /* Update Only 1 Byte */
        acti->tti[0] = txti.tti[0];
        acti->valid = TRUE;
        break;
    case TTI_MODE_16:
        for (reg_ct = 0; reg_ct < (reg_len * 2); reg_ct++) {
            if (txti.tti[reg_ct] & 0x80) {
                txti.tti[reg_ct] = '\0';
                acti->valid = TRUE;
                break;
            }
        }
        if (acti->valid == FALSE) {
            break;
        }
        for (idx_ct = reg_ct; idx_ct >= 0; idx_ct--) {
            if (txti.tti[idx_ct] & 0x80) {
                acti->valid = FALSE;
                break;
            }
            acti->tti[15 - (reg_ct - idx_ct)] = txti.tti[idx_ct];
        }
        for (idx_ct = 15; idx_ct > reg_ct; idx_ct-- ) {
            if (txti.tti[idx_ct] & 0x80) {
                acti->valid = FALSE;
                break;
            }
            acti->tti[idx_ct - (reg_ct + 1)] = txti.tti[idx_ct];
        }
        break;
    case TTI_MODE_64:
        for (reg_ct = 0; reg_ct < (reg_len * 2); reg_ct++) {
            if ((txti.tti[reg_ct] == 13) && (txti.tti[reg_ct + 1] == 10)) {
                txti.valid = TRUE;
                break;
            }
        }
        if (txti.valid == FALSE) {
            break;
        }
        reg_ct++;
        /* Since the TTi contains \n\r increase 2 bytes */
        for (idx_ct = (reg_ct + 1), arr_idx = 63; idx_ct <= 63; idx_ct++, arr_idx--) {
            if (txti.tti[idx_ct] & 0x80) {
                acti->valid = FALSE;
                break;
            }
            acti->tti[arr_idx] = txti.tti[idx_ct];
        }

        for (idx_ct = 0, arr_idx = reg_ct; idx_ct <= reg_ct; idx_ct++, arr_idx-- ) {
            if (txti.tti[idx_ct] & 0x80) {
                acti->valid = FALSE;
                break;
            }
            acti->tti[arr_idx] = txti.tti[idx_ct];
        }
        /* Reverse the Bytes */
        for (idx_ct = 0; idx_ct < 64; idx_ct++) {
            txti.tti[(63 - idx_ct)] = acti->tti[idx_ct];
        }
        *acti = txti;

        break;
    default :
        break;
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_perf_get(vtss_state_t *vtss_state,
                                      vtss_port_no_t port_no, vtss_ewis_perf_t *const perf)
{
    u16 lsw = 0x0000, msw = 0x0000;


    /* E-WIS S-BIP Error Counter 1 (MSW) (2xECB0) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xECB0, &msw));
    /* E-WIS S-BIP Error Counter 0 (LSW) (2xECB1) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xECB1, &lsw));
    perf->pn_ebc_s = ((msw << 16) | lsw);

    /* E-WIS L-BIP Error Counter 1 (MSW) (2xECB2) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xECB2, &msw));
    /* E-WIS L-BIP Error Counter 0 (LSW) (2xECB3) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xECB3, &lsw));
    perf->pn_ebc_l = ((msw << 16) | lsw);

    /* E-WIS L-REI Counter 1 (MSW) (2xEC90) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xEC90, &msw));
    /* E-WIS L-REI Counter 0 (LSW) (2xEC91)  */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xECB5, &lsw));
    perf->pf_ebc_l = ((msw << 16) | lsw);

    /* E-WIS P-BIP Error Counter 1 (MSW) (2xECB4) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xECB4, &msw));
    /* E-WIS P-BIP Error Counter 0 (LSW) (2xECB5) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xECB5, &lsw));
    perf->pn_ebc_p = ((msw << 16) | lsw);

    /* E-WIS P-REI Counter 1 (MSW) (2xEC80) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xEC80, &msw));
    /* E-WIS P-REI Counter 0 (LSW) (2xEC81) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0xEC81, &lsw));
    perf->pf_ebc_p = ((msw << 16) | lsw);

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_ewis_counter_get(vtss_state_t *vtss_state,
                                         vtss_port_no_t port_no, vtss_ewis_counter_t *const counter)
{
    u16 reg_val = 0x00;

    /*   WIS S-BIP Error Count 2x003c */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x003c, &reg_val));
    counter->pn_ebc_s = reg_val;

    /* Read Near End BIP Error Count, first read MSW and then read LSW */
    reg_val = 0;
    /*   WIS L-BIP Error Count 1 MSW (2x0039) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0039, &reg_val));
    counter->pn_ebc_l = (reg_val & 0xffff) << 15;
    reg_val = 0;
    /*   WIS L-BIP Error Count 0 LSW (2x003A) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x003A, &reg_val));
    counter->pn_ebc_l |= reg_val;

    /* Read Far End BIP Error Count, first read MSW and then read LSW */
    reg_val = 0;
    /*   WIS Far-End Line BIP Errors 1 MSW (2x0037)  */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0037, &reg_val));
    counter->pf_ebc_l = (reg_val & 0xffff) << 15;
    reg_val = 0;
    /*   WIS Far-End Line BIP Errors 0 LSW (2x0038) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0038, &reg_val));
    counter->pf_ebc_l |= reg_val;

    reg_val = 0;
    /* Read Path Block Error count, WIS P-BIP Block Error Count (2x003B) */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x003B, &reg_val));
    counter->pn_ebc_p = reg_val;

    reg_val = 0;
    /* Read Far End Path Block Error count, WIS Far-End Path Block Error Count (2x0025)  */
    VTSS_RC(vtss_phy_ewis_read(vtss_state, port_no, MMD_WIS, 0x0025, &reg_val));
    counter->pf_ebc_p = reg_val;

    return VTSS_RC_OK;
}


static vtss_rc vtss_phy_ewis_counter_threshold_set(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t port_no)
{
    vtss_ewis_counter_threshold_t threshold;
    u16 reg_val = 0x0000;

    threshold = vtss_state->ewis_conf[port_no].ewis_cntr_thresh_conf;

    /* WIS B1 Threshold Level 1 MSW :: (2xEE14) Level 2  LSW :: (2xEE15) */
    reg_val = (threshold.n_ebc_thr_s & 0xffff0000) >> 16; /* MSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE14, reg_val);
    reg_val = (threshold.n_ebc_thr_s & 0x0000ffff); /* LSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE15, reg_val);

    /* WIS B2 Threshold Level 1 MSW :: (2xEE16) Level 2 LSW :: (2xEE17) */
    reg_val = (threshold.n_ebc_thr_l & 0xffff0000) >> 16; /* MSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE16, reg_val);
    reg_val = (threshold.n_ebc_thr_l & 0x0000ffff); /* LSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE17, reg_val);

    /* WIS REI-L Threshold Level 1 MSW :: (2xEE12) Level 2 LSW :: (2xEE13) */
    reg_val = (threshold.f_ebc_thr_l & 0xffff0000) >> 16; /* MSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE12, reg_val);
    reg_val = (threshold.f_ebc_thr_l & 0x0000ffff); /* LSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE13, reg_val);

    /* WIS B3 Threshold Level 1 MSW :: (2xEE18) Level 2  LSW :: (2xEE19) */
    reg_val = (threshold.n_ebc_thr_p & 0xffff0000) >> 16; /* MSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE18, reg_val);
    reg_val = (threshold.n_ebc_thr_p & 0x0000ffff); /* LSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE19, reg_val);

    /* WIS REI-P Threshold Level 1 MSW :: (2xEE10) Level 2 LSW :: (2xEE11) */
    reg_val = (threshold.f_ebc_thr_p & 0xffff0000) >> 16; /* MSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE10, reg_val);
    reg_val = (threshold.f_ebc_thr_p & 0x0000ffff); /* LSW */
    VTSS_PHY_WARM_WR(port_no, MMD_WIS, 0xEE11, reg_val);

    return VTSS_RC_OK;
}

static const vtss_ewis_cons_act_t act_default = {
    .aisl = {
        .ais_on_los       = FALSE,
        .ais_on_lof       = FALSE,
    },
    .rdil = {
        .rdil_on_los      = FALSE,
        .rdil_on_lof      = FALSE,
        .rdil_on_lopc     = FALSE,
        .rdil_on_ais_l    = FALSE,
    },
    .fault = {
        .fault_on_feplmp = FALSE,
        .fault_on_feaisp = FALSE,
        .fault_on_rdil   = FALSE,
        .fault_on_sef    = FALSE,
        .fault_on_lof    = FALSE,
        .fault_on_los    = FALSE,
        .fault_on_aisl   = FALSE,
        .fault_on_lcdp   = FALSE,
        .fault_on_plmp   = FALSE,
        .fault_on_aisp   = FALSE,
        .fault_on_lopp   = FALSE,
    },
};

static const vtss_ewis_tti_t txti_default = {
    .mode = TTI_MODE_16,
    .tti = {
        [15] = 0x89,
    },

};

static const vtss_ewis_line_force_mode_t line_force_default = {
    .force_ais = FALSE,
    .force_rdi = FALSE,
};

static const vtss_ewis_line_tx_force_mode_t  line_tx_force_default = {
    .force_ais = FALSE,
    .force_rdi = FALSE,
};

static const vtss_ewis_path_force_mode_t path_force_default = {
    .force_uneq = FALSE,
    .force_rdi  = FALSE,
};

static const vtss_ewis_test_conf_t test_conf_default = {
    .loopback         = FALSE,
    .test_pattern_gen = VTSS_WIS_TEST_MODE_DISABLE,
    .test_pattern_ana = VTSS_WIS_TEST_MODE_DISABLE,
};

static const vtss_ewis_counter_threshold_t counter_threshold_default = {
    .n_ebc_thr_s      = 0xFFFFFFFF,
    .n_ebc_thr_l      = 0xFFFFFFFF,
    .f_ebc_thr_l      = 0xFFFFFFFF,
    .n_ebc_thr_p      = 0xFFFFFFFF,
    .f_ebc_thr_p      = 0xFFFFFFFF
};

/* ================================================================= *
*  Static Config Default values
*  All the values defined here are chip default values, except:
*    PMTICK_CTRL::PMTICK_ENA, which is enabled.
* ================================================================= */
static const vtss_ewis_static_conf_t static_default = {
    .ewis_txctrl1      = 0x0000,     /**< WIS Vendor Specific Tx Control 1 */
    .ewis_txctrl2      = 0x1640,     /**< WIS Vendor Specific Tx Control 2 */
    .ewis_rx_ctrl1     = 0x0003,     /**< E-WIS Rx Control 1 */
    .ewis_mode_ctrl    = 0x011A,     /**< E-WIS Mode Control (incl expected C2 Path label) */
    .ewis_tx_a1_a2     = 0xF628,     /**< E-WIS Tx A1/A2 Octets (frame alignment)*/
    .ewis_tx_c2_h1     = 0x1A62,     /**< E-WIS Tx C2/H1 Octets */
    .ewis_tx_h2_h3     = 0x0A00,     /**< E-WIS Tx H2/H3 Octets */
    .ewis_tx_z0_e1     = 0xCC00,     /**< E-WIS Tx Z0/E1 Octets */
    .ewis_rx_frm_ctrl1 = 0x1210,     /**< E-WIS Rx Framer Control 1 */
    .ewis_rx_frm_ctrl2 = 0x0244,     /**< E-WIS Rx Framer Control 2 */
    .ewis_lof_ctrl1    = 0x0618,     /**< E-WIS Loss of Frame Control 1 */
    .ewis_lof_ctrl2    = 0x0030,     /**< E-WIS Loss of Frame Control 2 */
    .ewis_rx_err_frc1  = 0x0050,     /**< E-WIS Rx Error Force Control 1 (RXLOF_ON_LOPC=0, APS_THRES=5)*/
    .ewis_pmtick_ctrl  = 0xFA06,     /**< E-WIS Performance Monitor Control (PMTICK enabled,internally 1 tick pr sec)*/
    .ewis_cnt_cfg      = 0x0000,     /**< E-WIS Counter Configuration (all counters in bit mode)*/
};

/**
 * \brief Create instance (set up function pointers), this function
 * should be called while creating the instance.
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_inst_ewis_create(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    vtss_cil_func_t *func = &vtss_state->cil;

    /* 10G PHY eWIS functions */
    func->ewis_events_conf_set        = NULL;
    func->ewis_events_poll            = NULL;
    func->ewis_events_force           = vtss_phy_ewis_events_force;
    func->ewis_static_conf_set        = vtss_phy_ewis_static_conf_set;
    func->ewis_force_conf_set         = vtss_phy_ewis_force_conf_set;
    func->ewis_tx_oh_set              = vtss_phy_ewis_tx_oh_set;
    func->ewis_tx_oh_passthru_set     = NULL;
    func->ewis_exp_sl_set             = NULL;
    func->ewis_mode_conf_set          = vtss_phy_ewis_mode_conf_set;
    func->ewis_reset                  = vtss_phy_ewis_reset;
    func->ewis_cons_action_set        = vtss_phy_ewis_action_set;
    func->ewis_section_txti_set       = vtss_phy_ewis_section_txti_set;
    func->ewis_path_txti_set          = vtss_phy_ewis_path_txti_set;
    func->ewis_test_mode_set          = vtss_phy_ewis_test_mode_set;
    func->ewis_prbs31_err_inj_set     = vtss_phy_ewis_prbs31_err_inj_set;
    func->ewis_test_status_get        = vtss_phy_ewis_test_status_get;
    func->ewis_defects_get            = vtss_phy_ewis_defects_get;
    func->ewis_status_get             = vtss_phy_ewis_status_get;
    func->ewis_section_acti_get       = vtss_phy_ewis_section_acti_get;
    func->ewis_path_acti_get          = vtss_phy_ewis_path_acti_get;
    func->ewis_perf_get               = vtss_phy_ewis_perf_get;
    func->ewis_counter_get            = vtss_phy_ewis_counter_get;
    func->ewis_counter_threshold_set  = vtss_phy_ewis_counter_threshold_set;

    for (port_no = 0 ; port_no < VTSS_PORT_ARRAY_SIZE; port_no++) {
        vtss_state->ewis_conf[port_no].static_conf = static_default;
        vtss_state->ewis_conf[port_no].section_cons_act   = act_default;
        vtss_state->ewis_conf[port_no].section_txti       = txti_default;
        vtss_state->ewis_conf[port_no].path_txti          = txti_default;
        vtss_state->ewis_conf[port_no].force_mode.line_rx_force  = line_force_default;
        vtss_state->ewis_conf[port_no].force_mode.line_tx_force  = line_tx_force_default;
        vtss_state->ewis_conf[port_no].force_mode.path_force     = path_force_default;
        vtss_state->ewis_conf[port_no].test_conf          = test_conf_default;
        vtss_state->ewis_conf[port_no].ewis_cntr_thresh_conf  = counter_threshold_default;
    }
    return VTSS_RC_OK;
}

/* - Warm start synchronization ------------------------------------ */
#define VTSS_SYNC_RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) {vtss_state->sync_calling_private = FALSE; return __rc__; }}

vtss_rc vtss_phy_ewis_sync(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_10g_port_state_t *ps = &vtss_state->phy_10g_state[port_no];

    if ((ps->type != VTSS_PHY_TYPE_8487) &&
        (ps->type != VTSS_PHY_TYPE_8488)) {
        VTSS_D("port_no %u WIS mode not supported ", port_no);
        return VTSS_RC_OK;
    }

    if (vtss_state->ewis_conf[port_no].ewis_mode == VTSS_WIS_OPERMODE_DISABLE) {
        return VTSS_RC_OK;
    }

    vtss_state->sync_calling_private = TRUE;

    VTSS_SYNC_RC(vtss_phy_ewis_static_conf_set(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_ewis_mode_conf_set(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_ewis_force_conf_set(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_ewis_action_set(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_ewis_section_txti_set(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_ewis_path_txti_set(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_ewis_test_mode_set(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_ewis_counter_threshold_set(vtss_state, port_no));

    vtss_state->sync_calling_private = FALSE;

    return VTSS_RC_OK;
}
#endif /* VTSS_CHIP_10G_PHY */
#endif /* VTSS_FEATURE_WIS */
