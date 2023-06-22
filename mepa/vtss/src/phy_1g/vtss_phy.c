// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// Avoid "options.h not used in module vtss_phy.c"
/*lint --e{766} */

#include <vtss_phy_api.h>
#ifdef VTSS_CHIP_CU_PHY

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#include "../ts/vtss_phy_ts.h"
#endif

#if defined(VTSS_VIPER_B_FIFO_RESET)
#include "../ts/vtss_phy_ts_util.h"
#endif

#include "../common/vtss_phy_common.h"
#include "vtss_phy_init_scripts.h"

#define DEBUG_TOKEN_RING_REGDUMP_EN 0

#if DEBUG_TOKEN_RING_REGDUMP_EN
/* Keep this function for debug, if any issue find */
static vtss_rc vtss_phy_debug_tr_regdump_print(vtss_state_t              *vtss_state,
                                               const vtss_debug_printf_t pr,
                                               const vtss_port_no_t      port_no,
                                               const BOOL                print_hdr);
#endif

/* SPI callout function for 1G Phys */
#if defined(VTSS_OPT_PHY_TIMESTAMP) || defined(VTSS_FEATURE_MACSEC)
extern vtss_rc vtss_phy_1g_spi_read_write(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 rng_sel, BOOL read, u8 target_id, u16 offset, u32 *const data);
extern vtss_rc get_base_adr(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 dev, u32 addr, u32 *phy10g_base, u32 *target_id, u32 *offset, BOOL *use_base_port);
#endif

// Because the PHYs operates with paged registers, we have sometimes expired that the registers are accessed to wrong pages due to code bugs.
// These bugs can be hard to find therefore definitions of registers are including the page they belong to. By setting the do_page_chk variable the page register is checked whenever a register is accessed, and giving an error message if there is an unexpected page access.
// For this to work the register definitions must be used, and therefor all new updates to the phy api should use these register definition and the corresponding rd_page and wr_page functions and macros.
#ifdef VTSS_SW_OPTION_DEBUG
static BOOL do_page_chk = TRUE;
#else
static BOOL do_page_chk = FALSE;
#endif

#if defined(VTSS_FEATURE_MACSEC)
extern vtss_rc vtss_macsec_drop_all_traffic_priv(vtss_state_t *vtss_state,
                                                 const vtss_port_no_t port_no);

extern vtss_rc vtss_inst_macsec_port_no_check(vtss_inst_t inst,  vtss_state_t **vtss_state, vtss_port_no_t port_no);

extern vtss_rc vtss_macsec_store_sa(vtss_state_t *vtss_state,
                                    const vtss_port_no_t port_no, BOOL store);
#endif

/* ================================================================= *
 *  Pre-declare functions
 * ================================================================= */
static vtss_rc vtss_phy_cl37_lp_abil_get_private(vtss_state_t *vtss_state,
                                                 const vtss_port_no_t port_no,
                                                 vtss_port_status_t   *const status);
static vtss_rc vtss_phy_conf_set_private(vtss_state_t *vtss_state,
                                         const vtss_port_no_t port_no);

static vtss_rc vtss_phy_conf_1g_set_private(vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no);

static vtss_rc vtss_phy_debug_reg_dump_private(vtss_state_t *vtss_state, const vtss_debug_printf_t pr,
                                               BOOL clear, const vtss_port_no_t port_no);

static vtss_rc vtss_phy_detect_base_ports_private(vtss_state_t *vtss_state);

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
static BOOL vtss_phy_chk_serdes_init_mac_mode_private(vtss_state_t                      *vtss_state,
                                                      vtss_port_no_t                     port_no,
                                                      const vtss_phy_reset_conf_t *const conf);

u8 vtss_phy_cfg_buf_size(vtss_state_t *vtss_state, const vtss_port_no_t    port_no);

#endif

static vtss_rc vtss_phy_serdes_sgmii_loopback_private (vtss_state_t *vtss_state, const vtss_port_no_t port_no, const u16 mode);
static vtss_rc vtss_phy_serdes_fmedia_loopback_private (vtss_state_t *vtss_state, const vtss_port_no_t port_no, const u16 mode);
static vtss_rc vtss_phy_reset_lcpll_private(vtss_state_t *vtss_state, vtss_port_no_t port_no);
short vtss_phy_tmon_adjust_private ( const u8 adc_val, const u8 offset_adj, const u8  slope_adj);
vtss_rc vtss_phy_ext_connector_loopback_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no, BOOL lpback);
BOOL vtss_phy_port_wol_capable(vtss_state_t  *vtss_state, const vtss_port_no_t  port_no);

short vtss_phy_tmon_adjust_private ( const u8 adc_val, const u8 offset_adj, const u8  slope_adj);
vtss_rc vtss_phy_ext_connector_loopback_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no, BOOL lpback);
BOOL vtss_phy_port_wol_capable(vtss_state_t  *vtss_state, const vtss_port_no_t  port_no);
u8 vtss_phy_status_buf_size(vtss_state_t *vtss_state, const vtss_port_no_t    port_no);
/* ================================================================= *
 *  Private functions
 * ================================================================= */

//Aquantia fucntion wrapper

// Function that is called any time the micro reset is being asserted
// This function specifically avoids bugzilla #5731
// IN : port_no - Any port within the chip.
vtss_rc vtss_phy_micro_assert_reset(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{

    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];


    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
        // Bugzilla#5731 - The following code-sequence is needed for Luton26 Rev. A and B where
        // a consumptive patch disables interrupts inside a micro-command patch.

        // Set to micro/GPIO-page
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

        //----------------------------------------------------------------------
        // Pass the NOP cmd to Micro to insure that any consumptive patch exits
        // There is no issue with doing this on any revision since it is just a NOP on any Vitesse PHY.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x800f));

        // Poll on 18G.15 to clear
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        //----------------------------------------------------------------------

        // Set to micro/GPIO-page (Has been set to std page by vtss_phy_wait_for_micro_complete
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

        // force micro into a loop, preventing any SMI accesses
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0000, 0x0800)); // Disable patch vector 3 (just in case)
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_9, 0x005b));     // Setup patch vector 3 to trap MicroWake interrupt
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_10, 0x005b));     // Loop forever on MicroWake interrupts
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0800, 0x0800)); // Enable patch vector 3
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x800f));     // Trigger MicroWake interrupt to make safe to reset

        // Assert reset after micro is trapped in a loop (averts micro-SMI access deadlock at reset)
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x0000, 0x8000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x0000));     // Make sure no MicroWake persists after reset
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0000, 0x0800)); // Disable patch vector 3

        break;
    default:
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0, 0x8000));
        break;
    }
    return vtss_phy_page_std(vtss_state, port_no);
}


//
// Conversion from vtss_phy_media_interface_t to printable text.
//
// In : media_if_type : The interface type
//
// Return :  Printable text
static const char *vtss_phy_media_if2txt(vtss_phy_media_interface_t media_if_type)
{
    switch (media_if_type) {
    case VTSS_PHY_MEDIA_IF_CU:
        return "VTSS_PHY_MEDIA_IF_CU";
    case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
        return "VTSS_PHY_MEDIA_IF_SFP_PASSTHRU";
    case VTSS_PHY_MEDIA_IF_FI_1000BX:
        return "VTSS_PHY_MEDIA_IF_FI_1000BX";
    case VTSS_PHY_MEDIA_IF_FI_100FX:
        return "VTSS_PHY_MEDIA_IF_FI_100FX";
    case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
        return "VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU";
    case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
        return "VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU";
    case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
        return "VTSS_PHY_MEDIA_IF_AMS_CU_1000BX";
    case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
        return "VTSS_PHY_MEDIA_IF_AMS_FI_1000BX";
    case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
        return "VTSS_PHY_MEDIA_IF_AMS_CU_100FX";
    case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
        return "VTSS_PHY_MEDIA_IF_AMS_FI_100FX";
    }
    return "Media Interface not defined";
}


//
// Conversion from vtss_phy_mac_interface_t to printable text.
//
// In : media_if_type : The interface type
//
// Return :  Printable text
static const char *vtss_phy_mac_if2txt(vtss_port_interface_t mac_if_type)
{
    switch (mac_if_type) {
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        return "No connection";
    case VTSS_PORT_INTERFACE_LOOPBACK:
        return "Internal loopback in MAC ";
    case VTSS_PORT_INTERFACE_INTERNAL:
        return "Internal interface ";
    case VTSS_PORT_INTERFACE_MII:
        return "MII (RMII does not exist) ";
    case VTSS_PORT_INTERFACE_GMII:
        return "GMII ";
    case VTSS_PORT_INTERFACE_RGMII:
        return "RGMII ";
    case VTSS_PORT_INTERFACE_TBI:
        return "TBI ";
    case VTSS_PORT_INTERFACE_RTBI:
        return "RTBI ";
    case VTSS_PORT_INTERFACE_SGMII:
        return "SGMII ";
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        return "SGMII_2G5 ";
    case VTSS_PORT_INTERFACE_SERDES:
        return "SERDES ";
    case VTSS_PORT_INTERFACE_VAUI:
        return "VAUI ";
    case VTSS_PORT_INTERFACE_100FX:
        return "100FX ";
    case VTSS_PORT_INTERFACE_XAUI:
        return "XAUI ";
    case VTSS_PORT_INTERFACE_RXAUI:
        return "RXAUI ";
    case VTSS_PORT_INTERFACE_XGMII:
        return "XGMII ";
    case VTSS_PORT_INTERFACE_SPI4:
        return "SPI4 ";
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        return "SGMII_CISCO ";
    case VTSS_PORT_INTERFACE_QSGMII:
        return "QSGMII ";
    case VTSS_PORT_INTERFACE_SFI:
        return "SFI ";
    default:
        return "Mac Interface not defined";
    }
}

// Function that returns TRUE if the port is any AMS mode, else FALSE
//
// In : port_mode : Port in question
//
// Return : TRUE if the port is any AMS mode, else FALSE
static BOOL is_phy_in_ams_mode(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg_val;
    u16 media_operating_mode;

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, &reg_val));
    media_operating_mode = (reg_val >> 8) & 0x7;
    return  media_operating_mode > 0x3; // See datasheet register 23, non AMS modes are 0x0, 0x1, 0x2, 0x3.
}

static vtss_rc vtss_phy_i2c_wait_for_ready(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 timeout = 500;
    u16 reg_value;

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_2, &reg_value));
    while ((reg_value & 0x8000) == 0 && timeout > 0) {
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_2, &reg_value));
        timeout--; // Make sure that we don't run forever
        MEPA_MSLEEP(1);
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    if (timeout == 0) {
        VTSS_E("vtss_phy_i2c_wait_for_ready timeoout, port_no %u", port_no);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

// Function for Setting the I2C clock select
// In: port_no - The PHY port number from 0, clock value - 0,1,2,3 for selecting the Clock frequency ranging 100 Khz to 4 Mhz
static vtss_rc vtss_phy_i2c_clock_sel_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, const mepa_i2c_clk_select_t *clk_value)
{
    u16 reg_value;
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_1, &reg_value));

    reg_value = ((reg_value & 0xffcf) | *clk_value<<4);

    /* Fix for Jira MEPA-231 I2C clock is selectable based on register 20G */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_1, reg_value));

    return VTSS_RC_OK;
}

// Function for doing phy i2c reads
// In: port_no - The PHY port number starting from 0.
static vtss_rc vtss_phy_i2c_wr_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 i2c_mux, u8 i2c_reg_start_addr, u8 i2c_device_addr, BOOL word_access, u8 cnt, const u8 *value)
{
    u16 i, count = (cnt == 0 ? 256 : cnt);
    u32 reg_val = 0;
    u16 reg_value = 0;

    VTSS_I("i2c_mux = %d, i2c_reg_start_addr = 0x%X, i2c_device_addr =0x%X", i2c_mux, i2c_reg_start_addr, i2c_device_addr);

    VTSS_RC(vtss_phy_i2c_wait_for_ready(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_1, &reg_value));

    reg_val = VTSS_F_PHY_I2C_MUX_CONTROL_1_DEV_ADDR(i2c_device_addr) |
              VTSS_F_PHY_I2C_MUX_CONTROL_1_SCL_CLK_FREQ((0x30 &(reg_value))>>4) |
              (i2c_mux == 3 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_3_ENABLE : 0) |
              (i2c_mux == 2 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_2_ENABLE : 0) |
              (i2c_mux == 1 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_1_ENABLE : 0) |
              (i2c_mux == 0 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_0_ENABLE : 0);

    VTSS_D("REg_val = 0x%X, 0x%X", reg_val, VTSS_F_PHY_I2C_MUX_CONTROL_1_DEV_ADDR(i2c_device_addr));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_1,
                        VTSS_F_PHY_I2C_MUX_CONTROL_1_DEV_ADDR(i2c_device_addr) |
                        VTSS_F_PHY_I2C_MUX_CONTROL_1_SCL_CLK_FREQ((0x30 &(reg_value))>>4) |
                        (i2c_mux == 3 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_3_ENABLE : 0) |
                        (i2c_mux == 2 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_2_ENABLE : 0) |
                        (i2c_mux == 1 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_1_ENABLE : 0) |
                        (i2c_mux == 0 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_0_ENABLE : 0)));



    for (i = 0; i < count; i++) {
        u8 i2c_reg_addr;
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        i2c_reg_addr = word_access ? (i2c_reg_start_addr + (i / 2) ) : (i2c_reg_start_addr + i);


        // setup data to be written
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_DATA_READ_WRITE, value[i]));

        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_DATA_READ_WRITE, &reg_value));

        // Execute the write
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_2,
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_MUX_READY |
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_PHY_PORT_ADDR(i2c_mux) |
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_ENA_I2C_MUX_ACCESS |
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_ADDR(i2c_reg_addr)));

        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_2, &reg_value));
        VTSS_D("i2c_reg_start_addr:%d, i2c_reg_addr:%d", i2c_reg_start_addr, i2c_reg_addr);
        VTSS_RC(vtss_phy_i2c_wait_for_ready(vtss_state, port_no));
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

// Function for doing phy i2c writes
// In: port_no - The PHY port number starting from 0.
static vtss_rc vtss_phy_i2c_rd_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 i2c_mux, u8 i2c_reg_start_addr, u8 i2c_device_addr, BOOL word_access, u8 cnt, u8 *value)
{

    u32 reg_val32 = 0;
    u16 reg_val16 = 0;
    u16 reg_value = 0;
    u16 i, count = (cnt == 0 ? 256 : cnt);

    VTSS_N("i2c_mux = %d, i2c_reg_start_addr = 0x%X, i2c_device_addr =0x%X", i2c_mux, i2c_reg_start_addr, i2c_device_addr);

    VTSS_RC(vtss_phy_i2c_wait_for_ready(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_1, &reg_value));

    reg_val32 = VTSS_F_PHY_I2C_MUX_CONTROL_1_DEV_ADDR(i2c_device_addr) |
                VTSS_F_PHY_I2C_MUX_CONTROL_1_SCL_CLK_FREQ((0x30 &(reg_value))>>4) |
                (i2c_mux == 3 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_3_ENABLE : 0) |
                (i2c_mux == 2 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_2_ENABLE : 0) |
                (i2c_mux == 1 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_1_ENABLE : 0) |
                (i2c_mux == 0 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_0_ENABLE : 0);

    VTSS_N("Reg_val = 0x%X, 0x%X", reg_val32, VTSS_F_PHY_I2C_MUX_CONTROL_1_DEV_ADDR(i2c_device_addr));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_1,
                        VTSS_F_PHY_I2C_MUX_CONTROL_1_DEV_ADDR(i2c_device_addr) |
                        VTSS_F_PHY_I2C_MUX_CONTROL_1_SCL_CLK_FREQ((0x30 &(reg_value))>>4) |
                        (i2c_mux == 3 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_3_ENABLE : 0) |
                        (i2c_mux == 2 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_2_ENABLE : 0) |
                        (i2c_mux == 1 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_1_ENABLE : 0) |
                        (i2c_mux == 0 ? VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_0_ENABLE : 0)));



    for (i = 0; i < count; i++) {
        u16 i2c_reg_addr = word_access ? (i2c_reg_start_addr + (i / 2) ) : (i2c_reg_start_addr + i);
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_CONTROL_2,
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_MUX_READY |
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_PHY_PORT_ADDR(i2c_mux) |
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_ENA_I2C_MUX_ACCESS |
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_RD |
                            VTSS_F_PHY_I2C_MUX_CONTROL_2_ADDR(i2c_reg_addr)));


        VTSS_RC(vtss_phy_i2c_wait_for_ready(vtss_state, port_no));


        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_I2C_MUX_DATA_READ_WRITE, &reg_val16));

        value[i] = (reg_val16 & VTSS_M_PHY_I2C_MUX_DATA_READ_WRITE_READ_DATA) >> 8;
        VTSS_N("i2c_reg_start_addr:%d, value[%d]:0x%X, i2c_reg_addr:%d", i2c_reg_start_addr + i, i, value[i], i2c_reg_addr);
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}


static vtss_rc vtss_phy_rd_wr_masked(vtss_state_t         *vtss_state,
                                     BOOL                 read,
                                     const vtss_port_no_t port_no,
                                     const u32            addr,
                                     u16                  *const value,
                                     const u16            mask)
{
    vtss_rc           rc = VTSS_RC_OK;
    vtss_miim_read_t  read_func;
    vtss_miim_write_t write_func;
    u16               reg, page, val;

    /* Setup read/write function pointers */
    read_func = vtss_state->init_conf.miim_read;
    write_func = vtss_state->init_conf.miim_write;

    /* Page is encoded in address */
    page = (addr >> 5);
    reg = (addr & 0x1f);

    /* Change page */
    if (page) {
        rc = write_func(vtss_state, port_no, 31, page);
    }
    if (rc == VTSS_RC_OK) {
        if (read) {
            /* Read */
            rc = read_func(vtss_state, port_no, reg, value);
            VTSS_N("Read - port:%d, reg:0x%X, value:0x%X", port_no, reg, *value);
        } else if (mask != 0xffff) {
            /* Read-modify-write */
            if ((rc = read_func(vtss_state, port_no, reg, &val)) == VTSS_RC_OK) {
                rc = write_func(vtss_state, port_no, reg, (val & ~mask) | (*value & mask));
            }
            VTSS_N("Read-modify-write - port:%d, reg:0x%X, rd_val:0x%X, value:0x%X, mask:0x%X  wr_val:0x%x",
                   port_no, reg, val, *value, mask, ((val & ~mask) | (*value & mask)));
            //VTSS_N("Read- port:%d, reg:0x%X, val:0x%X", port_no, reg, val);

        } else {
            /* Write */
            rc = write_func(vtss_state, port_no, reg, *value);
            VTSS_N("Write - port:%d, reg:0x%X, value:0x%X", port_no, reg, *value);
        }
    }

    /* Restore standard page */
    if (page && rc == VTSS_RC_OK) {
        rc = write_func(vtss_state, port_no, 31, VTSS_PHY_PAGE_STANDARD);
    }

    return rc;
}

/* Read PHY register - used for legacy code where the programmer keep track of the page.*/
vtss_rc vtss_phy_rd(vtss_state_t         *vtss_state,
                    const vtss_port_no_t port_no,
                    const u32            addr,
                    u16                  *const value)
{
    return vtss_phy_rd_wr_masked(vtss_state, 1, port_no, addr, value, 0);
}



// For debugging - See comment at the do_page_chk
static void vtss_phy_do_page_chk_set_private(BOOL enable)
{
    do_page_chk = enable;
}

// For debugging - See comment at the do_page_chk
static void vtss_phy_do_page_chk_get_private(BOOL *enable)
{
    *enable = do_page_chk;
}




// See comment at the do_page_chk
static vtss_rc  vtss_phy_do_page_chk(vtss_state_t         *vtss_state,
                                     const vtss_port_no_t port_no,
                                     const u16            page,
                                     const u16            line)
{
    u16 current_page;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];


    switch (ps->family) {
    case VTSS_PHY_FAMILY_MUSTANG:
    case VTSS_PHY_FAMILY_QUATTRO:
    case VTSS_PHY_FAMILY_COBRA:
    case VTSS_PHY_FAMILY_ENZO:
    case VTSS_PHY_FAMILY_LUTON:
    case VTSS_PHY_FAMILY_SPYDER:
    case VTSS_PHY_FAMILY_NONE:
        // These chip will return 0x0 from the page register, so they can't be checked.
        // Mustang(8201), Quattro(8224,8234,8244), Cobra(8211,8221), and Luton (1st gen in TSMC)
        return VTSS_RC_OK;
    default:
        // Do the page check
        VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &current_page));
        if (current_page != page) {
            VTSS_E("Unexpected page - Current_Page:0x%X, expected page:0x%X, line:%d, port:%d, family:%d", current_page, page, line, port_no, ps->family);

        } else {
            VTSS_N("Correct page: Current_Page:0x%X, expected page:0x%X, line:%d", current_page, page, line);
        }
    }
    return VTSS_RC_OK;
}



// See comment at the do_page_chk
/* Read PHY register (include page) - Use this function in combination with the register defines for new code. */
vtss_rc vtss_phy_rd_page(vtss_state_t         *vtss_state,
                         const vtss_port_no_t port_no,
                         const u16            page,
                         const u32            addr,
                         u16                  *const value,
                         const u16            line)
{
    if (do_page_chk) {
        VTSS_RC(vtss_phy_do_page_chk(vtss_state, port_no, page, line));
    }
    return vtss_phy_rd_wr_masked(vtss_state, 1, port_no, addr, value, 0);
}



// See comment at the do_page_chk
/* Write PHY register, masked (including the page) */
vtss_rc vtss_phy_wr_masked_page(vtss_state_t         *vtss_state,
                                const vtss_port_no_t port_no,
                                const u16            page,
                                const u32            addr,
                                const u16            value,
                                const u16            mask,
                                const u16            line)
{
    u16 val = value;
    if (do_page_chk) {
        VTSS_RC(vtss_phy_do_page_chk(vtss_state, port_no, page, line));
    }
    return vtss_phy_rd_wr_masked(vtss_state, 0, port_no, addr, &val, mask);
}


/* Write PHY register, masked - used for legacy code where the programmer keep track of the page.*/
vtss_rc vtss_phy_wr_masked(vtss_state_t         *vtss_state,
                           const vtss_port_no_t port_no,
                           const u32            addr,
                           const u16            value,
                           const u16            mask)
{
    u16 val = value;
    return vtss_phy_rd_wr_masked(vtss_state, 0, port_no, addr, &val, mask);
}

// Macro for doing warm start register writes. Checks if the register has changed. Also inserts the calling line number when doing register writes. Useful for debugging warm start,
#define VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, page_addr, value, mask) vtss_phy_warm_wr_masked(vtss_state, port_no, page_addr, value, mask, 0xFFFF, __FUNCTION__,  __LINE__)

// See VTSS_PHY_WARM_WR_MASKED. Some registers may not contain the last value written to they (e.g. self clearing bits), and therefor must be written without doing read check.
// This is possible with this macro which contains a "chk_mask" bit mask for selecting which bit to do read check of. Use this function with care and ONLY with registers there the read value doesn't reflect the last written value.
#define VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, page_addr, value, mask, chk_mask) vtss_phy_warm_wr_masked(vtss_state, port_no, page_addr, value, mask, chk_mask, __FUNCTION__, __LINE__)

// Function for doing phy register writes for functions that supports warm start.
// This function only writes to the register if the value is different from what is currently in the register in order not to affect traffic
// In : port_no - Phy port number
//      addr    - The register address in the phy.
//      value   - The data to be written.
//      mask     - Bit mask for bit to be written.
//      chk_mask - Bit mask for bit to be checked.
//      function - Pointer to string containing the name of the calling function.
//      line     - Line number calling the function.
static vtss_rc vtss_phy_warm_wr_masked(vtss_state_t         *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const u16            page,
                                       const u32            addr,
                                       const u16            value,
                                       const u16            mask,
                                       const u16            chk_mask,
                                       const char           *function,
                                       const u16            line)

{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16     val;

    // If in warm start phase then only update the register if the value is different from the current register value.
    if (vtss_state->sync_calling_private) {
        VTSS_RC(vtss_phy_rd_page(vtss_state, port_no, page, addr, &val, line));
        if ((val ^ value) & mask & chk_mask) { /* Change in bit field */
            VTSS_I("Warm start synch. field changed: Port:%u MMD:%d Register:0x%X", port_no, page, addr);
            VTSS_I("Mask:0x%X Chip value:0x%X API value:0x%X", mask, val, value);
            VTSS_I("Function:%s, Line:%d (chk_mask:0x%X)", function, line, chk_mask);
            VTSS_I("warm_start_reg_changed:%d, chk_mask:%d", ps->warm_start_reg_changed, chk_mask);

            ps->warm_start_reg_changed = TRUE; // Signaling the a register for this port port has changed.

            VTSS_RC(vtss_phy_wr_masked_page(vtss_state, port_no, page, addr, value, mask, line));
        }
    } else {
        VTSS_RC(vtss_phy_wr_masked_page(vtss_state, port_no, page, addr, value, mask, line));
    }
    return VTSS_RC_OK;
}

// Function returning VTSS_RC_ERROR if any registers were unexpected needed to be changed during warm start
static vtss_rc vtss_phy_warm_start_failed_get_private(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    VTSS_I("warm_start_reg_changed:%d", ps->warm_start_reg_changed);
    return ps->warm_start_reg_changed ? VTSS_RC_ERROR : VTSS_RC_OK;
}

/* Write PHY register */
vtss_rc vtss_phy_wr(vtss_state_t         *vtss_state,
                    const vtss_port_no_t port_no,
                    const u32            addr,
                    const u16            value)
{
    u16 val = value;
    return vtss_phy_rd_wr_masked(vtss_state, 0, port_no, addr, &val, 0xffff);
}


/* Write PHY register */
// See comment at the do_page_chk
vtss_rc vtss_phy_wr_page(vtss_state_t         *vtss_state,
                         const vtss_port_no_t port_no,
                         const u16            page,
                         const u32            addr,
                         const u16            value,
                         const u16            line)
{
    u16 val = value;
    if (do_page_chk) {
        VTSS_RC(vtss_phy_do_page_chk(vtss_state, port_no, page, line));
    }
    return vtss_phy_rd_wr_masked(vtss_state, 0, port_no, addr, &val, 0xFFFF);
}

// Macro that inserts the calling line number when doing register writes. Useful for debugging warm start,
#define VTSS_PHY_WARM_WR(vtss_state, port_no, page_addr, value) vtss_phy_warm_wr(vtss_state, port_no, page_addr, value, __FUNCTION__, __LINE__)

// Function for doing phy register writes for functions that supports warm start.
// This function only writes to the register if the value is different from what is currently in the register in order not to affect traffic
// In : port_no - Phy port number
//      addr    - The register address in the phy.
//      value   - The data to be written.
//      function - Pointer to string containing the name of the calling function.
//      line     - Line number calling the function.
static vtss_rc vtss_phy_warm_wr(vtss_state_t         *vtss_state,
                                const vtss_port_no_t port_no,
                                const u16            page,
                                const u32            addr,
                                const u16            value,
                                const char           *function,
                                const u16            line)
{
    return vtss_phy_warm_wr_masked(vtss_state, port_no, page, addr, value, 0xFFFF, 0xFFFF, function, line);
}


// Clause 45 register access setup. Setups the MMD register access with the address.
//
static vtss_rc vtss_phy_mmd_reg_setup(vtss_state_t         *vtss_state,
                                      const vtss_port_no_t port_no,
                                      const u8  devad,
                                      const u16 addr)
{
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MMD_EEE_ACCESS, devad)); // Setup cmd=address + devad address
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MMD_ADDR_OR_DATA, addr));  // Setup address
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MMD_EEE_ACCESS, (1 << 14) + devad)); // Setup cmd=data + devad address
    return VTSS_RC_OK;
}


// Clause 45 writes
static vtss_rc vtss_phy_mmd_wr(vtss_state_t *vtss_state,
                               const vtss_port_no_t port_no,
                               const u8  devad,
                               const u16 addr,
                               const u16 data_val)
{
    VTSS_RC(vtss_phy_mmd_reg_setup(vtss_state, port_no, devad, addr));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MMD_ADDR_OR_DATA, data_val));  // Write data

    return VTSS_RC_OK;
}


// Clause 45 reads
static vtss_rc vtss_phy_mmd_rd(vtss_state_t *vtss_state,
                               const vtss_port_no_t port_no,
                               const u8 devad,
                               const u16 addr,
                               u16   *value)
{
    VTSS_RC(vtss_phy_mmd_reg_setup(vtss_state, port_no, devad, addr));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MMD_ADDR_OR_DATA, value));  // read data

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_EEE)
// Clause 45 read-modify mask writes
static vtss_rc vtss_phy_mmd_reg_wr_masked(vtss_state_t *vtss_state,
                                          const vtss_port_no_t port_no,
                                          const u16 devad,
                                          const u16 addr,
                                          const u16 data_val,
                                          const u16 mask)
{
    u16 current_reg_val;
    VTSS_RC(vtss_phy_mmd_rd(vtss_state, port_no, devad, addr, &current_reg_val)); // Read current value of the register
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MMD_ADDR_OR_DATA, (current_reg_val & ~mask) | (data_val & mask) ));  // Modify current value and write.

    return VTSS_RC_OK;
}
#endif

static u16 rgmii_clock_skew(u16 ps)
{
    return (ps == 0 ? 0 : ps < 1600 ? 1 : ps < 2050 ? 2 : 3);
}

vtss_rc vtss_phy_page_std(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_STANDARD);
}

vtss_rc vtss_phy_page_0x2daf(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_0x2DAF);
}

vtss_rc vtss_phy_page_ext(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_EXTENDED);
}

vtss_rc vtss_phy_page_ext2(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_EXTENDED_2);
}

vtss_rc vtss_phy_page_ext3(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_N("Port:%d - Page 3", port_no)
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_EXTENDED_3);
}
vtss_rc vtss_phy_page_ext4(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_N("Port:%d - Page 4", port_no)
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_EXTENDED_4);
}
vtss_rc vtss_phy_page_gpio(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_GPIO);
}

// Selecting 1588/ptp page registers
vtss_rc vtss_phy_page_1588(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_1588);
}

// Selecting MACSEC page registers
vtss_rc vtss_phy_page_macsec(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_MACSEC);
}

vtss_rc vtss_phy_page_test(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_TEST);
}

vtss_rc vtss_phy_page_tr(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return vtss_phy_wr(vtss_state, port_no, 31, VTSS_PHY_PAGE_TR);
}

// Function for mapping the port_no giving to a function to the  physical port number.
static vtss_port_no_t vtss_phy_chip_port(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg_val;
    u16 current_page;
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &current_page));
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg_val));
    VTSS_D("reg_val:0x%X, chip_no:%d, port_no:%u", reg_val,  (reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS) >> 11, port_no);
    VTSS_RC(vtss_phy_wr(vtss_state, port_no, 31, current_page));
    return (reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS) >> 11;
}

/* Bz#23788 Work-Around for 100BT Link break Issue, after restoring link it does not come up for a long time. */
/* The Condition required is that the Links should be DOWN */
static vtss_rc vtss_phy_100BaseT_long_linkup_workaround(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL force)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *conf = &ps->reset;
    u16                   tp_reg5 = 0;
    u16                   tr_reg17 = 0;
    u16                   tr_reg18 = 0;
    u16                   reg0val = 0;
    u16                   reg4val = 0;
    u16                   reg9val = 0;
    u16                   retryCnt100 = 0;
    u16                   speed_sel = 0;
    BOOL                  aneg_ena = FALSE;
    BOOL                  par_det100_ena = FALSE;

    /* If the current link is down NOW, then execute */
    /* Bz#23788 Work-Around for 100BT Link break Issue, after restoring link it does not come up for a long time. */
    /* TP5.11 is ONLY set for the later versions of 65nm PHY's, all others have TP5.11=0 */
    /* Tesla Rev. E, Viper A&B, ELISE, NANO, MINI. */
    /* Therefore there is no reason to special case this work-around per PHY Family */
    /* SPECIAL NOTE: */
    /* The only device which has the HW FIX for this issue is MINI Rev. C, which does not need this work-around */

    /* Read PHY with TP5 */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_5, &tp_reg5)); /* Read TP_Reg5.11 */
    /* Switch back to STD Page */
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    /* Only apply the workaround for PHY with TP5.11 is set */
    if (conf->media_if == VTSS_PHY_MEDIA_IF_CU) {
        if (tp_reg5 & (0x1 << 11)) {
            /*  Read the ANEG ENABLE and Forced Speed Selection  */
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, &reg0val));
            aneg_ena = (reg0val & (0x1 << 12)) ? TRUE:FALSE;
            speed_sel = (reg0val & (0x1 << 13) ? 0x1:0x0) | (reg0val & (0x1 << 6) ? 0x2:0x0);
            /* The problem only occurs if the pre-emphasis feature (TP5.11) is enabled   */
            /* Typically: media_if == VTSS_PHY_MEDIA_IF_CU && mode == VTSS_PHY_MODE_FORCED && forced.speed == VTSS_SPEED_100M */
                /* Only if 100M Forced Speed Copper */
                VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xaff4)); /* Read in Data */
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &tr_reg18)); /* Read bit 7, PreEmphEnabled status  */
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &tr_reg17)); /* Read 5:0, RetryCnt100 */
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                retryCnt100 = tr_reg17 & 0x003f;
                VTSS_I("Reading TR_16 addr:0x0ff4 PreEmphEnabled status for port_no: %u, TR18: 0x%04x,  TR17: 0x%04x, retryCnt100: %d",
                        port_no, tr_reg18, tr_reg17, retryCnt100);

                /* Toggling ANEG causes the retryCnt100 to increment */
                /* If the is Media i/f setup or if this is Link transition from Link Up to down, then Force this work-around */
                /* If the is Link is down and has been down, only execute the work-around if retryCnt100 has incremented more than 3 */
                /* Note: vtss_phy_status_get() is called by the Applicaiton, so the rate could be 1/sec or 10/sec or 5/sec  */
                /*       The retryCnt100 is trying to limit the number of times this is activated giving reasonable time for link-up */
           VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT, &reg4val));
            if (!aneg_ena) {  /* Forced Mode Operation */
                if (speed_sel == 0x1) {  /* 00=10M; 01=100M; 10=1000M; 11=Resvd;  Forced Speed */
                    VTSS_I("Forced Mode - Cu Media Interface, Speed=100M, Executing 100BT_Long_LinkDn_Work_Around");
                    if ((tr_reg18 & 0x0080) &&  /* Currently Have NO Link and PreEmphEnabledStatus set */
                        (retryCnt100 >= VTSS_FORCED_LONG_LINKUP_COUNTER_WINDOW)) {
                            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, &reg9val));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT, 0x1));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, 0x0));
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0x1000, 0x1000));
                            VTSS_I("Toggle ANEG 100BT_Long_LinkDn_Work_Around Executed - ADVERTISEMENTS Clear\n");
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0x0000, 0x1000));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT, reg4val));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, reg9val));
                        } else {
                            VTSS_I("Forced Mode - Cu Media Interface, Skipping 100BT_Long_LinkDn_Work_Around\n");
                        }
                } else {
                    VTSS_D("Forced Mode - Cu Media Interface, Speed not 100M, Skipping 100BT_Long_LinkDn_Work_Around");
                }
            } else { /* ANEG ENABLED */
                par_det100_ena = reg4val & (0x1 << 7) ? TRUE:FALSE; // 100 HDX is Advertised, therefore PD Enabled for 100M
                if (par_det100_ena) {
                    if (retryCnt100 >= VTSS_FORCED_LONG_LINKUP_COUNTER_WINDOW) {
                        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                   VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG,
                                   VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG)); // Restart ANEG
                    }
                }
            } /* End of ANEG */
        }
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    }
    return (VTSS_RC_OK);
}


// Function for soft resetting a single phy port
// In: port_no : The phy port number to be soft reset
static vtss_rc vtss_phy_soft_reset_port(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    mepa_mtimer_t         timer;
    u16                   reg;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc               rc = VTSS_RC_ERROR;

    if (!vtss_state->sync_calling_private) { // Don't reset during warm start
        VTSS_D("Soft resetting port:%d", port_no);
        /* See bugzilla 9450 and 17849 : Correct the implementation of bug9450 and Bugzero_48512 */
        switch (ps->family) {
        case VTSS_PHY_FAMILY_TESLA:
            reg = VTSS_F_PHY_MODE_CONTROL_SW_RESET | VTSS_F_PHY_MODE_CONTROL_LOOP | (1 << 6);
            VTSS_D("Soft resetting Tesla port:%d, Writing RegValue = 0x%x", port_no, reg);
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, reg));  // Tesla PHY Only - Writing 0xc040, See Bug_9450
            break;

        case VTSS_PHY_FAMILY_ATOM:
        case VTSS_PHY_FAMILY_LUTON26:
        case VTSS_PHY_FAMILY_VIPER:
        case VTSS_PHY_FAMILY_ELISE:
        case VTSS_PHY_FAMILY_NANO:
        default:
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                       VTSS_F_PHY_MODE_CONTROL_SW_RESET,
                                       VTSS_F_PHY_MODE_CONTROL_SW_RESET)); // Reset phy port
            break;
        }

        MEPA_MSLEEP(1);/* pause after reset */
        MEPA_MTIMER_START(&timer, 5000); /* Wait up to 5 seconds */
        while (1) {
            if (PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, &reg) == VTSS_RC_OK && (reg & VTSS_F_PHY_MODE_CONTROL_SW_RESET) == 0) {
                break;
            }
            MEPA_MSLEEP(1);
            if (MEPA_MTIMER_TIMEOUT(&timer)) {
                VTSS_E("port_no %u, reset timeout, reg = 0x%X", port_no, reg);
                return VTSS_RC_ERROR;
            }
        }
        MEPA_MTIMER_CANCEL(&timer);
        // After reset of a port, we need to re-configure it
        VTSS_RC(vtss_phy_conf_1g_set_private(vtss_state, port_no));

#if defined(VTSS_OPT_PHY_TIMESTAMP)
        rc = VTSS_RC_COLD(vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, FALSE));
        if (rc == VTSS_RC_OK) {
#endif
            rc = vtss_phy_conf_set_private(vtss_state, port_no);
#if defined(VTSS_OPT_PHY_TIMESTAMP)
            rc = VTSS_RC_COLD(vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, FALSE));
        }
#endif

        if (rc != VTSS_RC_OK) {
            VTSS_E("vtss_phy_conf_set_private Failed port_no %u", port_no);
            return rc;
        }

    } else {
        VTSS_D("Warm-Start Detected: Soft reset of port:%d   Skipped!", port_no);
    }

    return VTSS_RC_OK;
}

// Function for resetting a phy port
// In: port_no : The phy port number to be reset
static vtss_rc port_reset(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, TRUE)); // Suspend the micro patch while resetting

    VTSS_RC(vtss_phy_soft_reset_port(vtss_state, port_no));

    VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, FALSE)); // Restart micro patch
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_optimize_receiver_init(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg17;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    VTSS_N("vtss_phy_optimize_receiver_init enter port = %d", port_no);

    /* BZ 1776/1860/2095/2107, part 1/3 and 2/3 */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO:
        break;
    default:
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_12, 0x0200, 0x0300)); // Not needed for the above
    }

    if (ps->power.vtss_phy_power_dynamic) {
        /* Restore changed dsp setting used by dynamic power saving algorithm */
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_TEST_PAGE_12, 0x0000, 0xfc00));

        switch (ps->family) {
        case VTSS_PHY_FAMILY_ATOM:
        case VTSS_PHY_FAMILY_LUTON26:
        case VTSS_PHY_FAMILY_TESLA:
            // Read-modify-write word containing half_comp_en
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xafe4));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));
            reg17 = (reg17 & 0xffef); //Clear half_adc as desired
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe4));
            break;
        default:
            /* Restore 1000-BT LD-Q Current Control */
            // For now don't restore at warm start
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x2000, 0x2000, 0x0));
        }

        if (ps->power.vtss_phy_actiphy_on) {
            ps->power.pwrusage = VTSS_PHY_ACTIPHY_PWR;
        } else {
            ps->power.pwrusage = VTSS_PHY_LINK_DOWN_PWR;
        }
    }
    return vtss_phy_page_std(vtss_state, port_no);
}

static vtss_rc vtss_phy_optimize_dsp(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    /* BZ 2226/2227/2228/2229/2230/2231/2232/2294 */
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xaf8a));               /*- Read PMA internal Register 5 */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000, 0x0000)); /*- Configure PMA */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0008, 0x000c)); /*- Register 5 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f8a));               /*- Write PMA internal Register 5 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xaf86));               /*- Read PMA internal Register 3 */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008, 0x000c)); /*- Configure PMA */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000, 0x0000)); /*- Register 3 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f86));               /*- Write PMA internal Register 3 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xaf82));               /*- Read PMA internal Register 1 */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000, 0x0000)); /*- Configure PMA */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0100, 0x0180)); /*- Register 1 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));               /*- Write PMA internal Register 1 */

    return VTSS_RC_OK;
}

/* Dynamic Transmit Side Power Optimizations */
#define WORST_SUBCHAN_MSE 120
#define WORST_AVERAGE_MSE 100


/*- EC length power-down optimzations */
/*- 1:Full-length(0), 2:64 taps(5), 3:48 taps(9), 4:32 taps(12), 5:16 taps(14) */
static const u16 ecpdset[] = { 0, 5, 9, 12, 14 };
#define NUM_ECPD_SETTINGS (sizeof(ecpdset)/sizeof(ecpdset[0]))

/* Computes optimal power setting level reductions based on */
/* calculated noise values from the specific cable being used */
static vtss_rc vtss_phy_power_opt(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u16 reg17, reg18, ecpd_idx, ncpd, half_adc;
    u32 maxMse, meanMse, tempMse, c, r, popt_idx, set[5][3];
    i16 done;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    VTSS_D("vtss_phy_power_opt enter, port = %d", port_no);

    reg17 = reg18 = ecpd_idx = maxMse = meanMse = done = half_adc = 0;
    ncpd = 1;


    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO:
        half_adc = 1;
        break;
    default:
        ncpd = 1;
        break;
    }

    /*- Prepare TR node for MSE Averaging - Normkmse_m7 = 3 (default 0) */
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa3aa));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0003));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83aa));

    for (c = 0; c < 3; c++) {
        for (r = 0; r < 5; r++) {
            set[r][c] = (5 * c) + (r + 1);
        }
    }

    while (done < 2) {
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_TEST_PAGE_12, ((ecpdset[ecpd_idx] << 12) | (ncpd << 10)), 0xfc00));

        switch (ps->family) {
        case VTSS_PHY_FAMILY_ATOM:
        case VTSS_PHY_FAMILY_LUTON26:
        case VTSS_PHY_FAMILY_TESLA:
        case VTSS_PHY_FAMILY_VIPER:
        case VTSS_PHY_FAMILY_ELISE:
        case VTSS_PHY_FAMILY_NANO:
            // Read-modify-write word containing half_comp_en
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xafe4));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));
            reg17 = (reg17 & 0xffef) | ((half_adc & 1) << 4); //Seat or clear half_adc as desired
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe4));
            break;
        default:
            break;
        }


        if (done != 0) {
            if (done < 0) {
                MEPA_MSLEEP(50);
            }
            ++done;
        } else {
            /*- Read MSE A and B */
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa3c0));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18));

            maxMse = (reg17 & 0x0fff);
            tempMse = (reg17 >> 12) | (reg18 << 4);
            meanMse = maxMse + tempMse;
            if (tempMse > maxMse) {
                maxMse = tempMse;
            }

            /*- Read MSE C and D */
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa3c2));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18));

            meanMse += (reg17 & 0x0fff);
            if ((reg17 & 0x0fff) > maxMse) {
                maxMse = (reg17 & 0x0fff);
            }
            tempMse = (reg17 >> 12) | (reg18 << 4);
            meanMse += tempMse;
            if (tempMse > maxMse) {
                maxMse = tempMse;
            }
            meanMse /= 4;

            if ((maxMse >= WORST_SUBCHAN_MSE) || (meanMse >= WORST_AVERAGE_MSE)) {
                if (ncpd == 0) {    /*- ADC Optimization went too far */
                    half_adc--;
                    ncpd = 1;
                } else if (ecpd_idx == 0) {    /*- NC Optimization went too far */
                    ncpd--;
                    done = -1;
                    ecpd_idx = 1;
                } else {                /*- EC Optimization went too far */
                    ecpd_idx--;
                    done = 1;
                }
            } else if ((ecpd_idx == 0) && (ncpd < 2)) {
                ncpd++;
            } else if (++ecpd_idx >= NUM_ECPD_SETTINGS) {
                done = 2;
            }
        }
    }

    if (ecpd_idx >= 1) {
        popt_idx = set[ecpd_idx - 1][ncpd];
    } else {
        popt_idx = set[0][ncpd];
    }


    vtss_state->phy_state[port_no].power.pwrusage = ((ncpd > 0 || ecpd_idx > 0) ?
                                                     popt_idx : VTSS_PHY_LINK_UP_FULL_PWR);

    /*- Restore Normkmse_m7 = 0 */
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa3aa));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83aa));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    VTSS_D("ncpd 0x%X, ecpd_idx = %d", ncpd, ecpd_idx);

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_optimize_receiver_reconfig(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16                   vga_state_a;
    i16                   max_vga_state_to_optimize;


    VTSS_N("vtss_phy_optimize_receiver_reconfig enter port_no = %u", port_no);

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO:
        //65nm PHY adjusted VGA window to more effectively use dynamic range
        //as a result, VGA gains for a given cable length are higher here.
        max_vga_state_to_optimize = -9;
        break;
    default:
        max_vga_state_to_optimize = -12;
        break;
    }

    /* BZ 1776/1860/2095/2107 part 3/3 */
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xaff0));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &vga_state_a));

    vga_state_a = ((vga_state_a >> 4) & 0x01f);
    /* vga_state_a is a 2's complement signed number ranging from -13 to +8 */
    /* Test for vga_state_a < 16 is really a check for positive vga_state_a */
    if ((vga_state_a < 16) || (vga_state_a > (max_vga_state_to_optimize & 0x1f))) {
        VTSS_N("vga_state_a = %u", vga_state_a);
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_TEST_PAGE_12, 0x0000, 0x0300));
        ps->power.pwrusage = VTSS_PHY_LINK_UP_FULL_PWR;
    } else {    /*- Short loop */
        VTSS_D("ps->power.vtss_phy_power_dynamic = %d", ps->power.vtss_phy_power_dynamic)
        if (ps->power.vtss_phy_power_dynamic) {
            VTSS_RC(vtss_phy_page_test(vtss_state, port_no));

            switch (ps->family) {
            case VTSS_PHY_FAMILY_ATOM:
            case VTSS_PHY_FAMILY_LUTON26:
            case VTSS_PHY_FAMILY_TESLA:
            case VTSS_PHY_FAMILY_VIPER:
            case VTSS_PHY_FAMILY_ELISE:
            case VTSS_PHY_FAMILY_NANO:
                break;
            default:
                /*- Transmit side power reduction - 1000-BT LD-Q Current Control */
                VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0000, 0x2000));
                break;
            }

            /*- Dynamic Power Reduction */
            VTSS_RC(vtss_phy_power_opt(vtss_state, port_no));
        } else {
            ps->power.pwrusage = VTSS_PHY_LINK_UP_FULL_PWR;
        }
    }
    return vtss_phy_page_std(vtss_state, port_no);
}

static vtss_rc vtss_phy_optimize_jumbo(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    /* BZ 1799/1801 */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0E35));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9786));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
    return vtss_phy_page_std(vtss_state, port_no);
}

static vtss_rc vtss_phy_optimize_rgmii_strength(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    /* BZ 2094 */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_3, 0xf082));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_3, 0xf082));
    return vtss_phy_page_std(vtss_state, port_no);
}


// Function for setting mdi control register when in force mdi mode.
static vtss_rc vtss_phy_mdi_control_reg(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_status_t   status;

    memset(&status, 0, sizeof(status));
    VTSS_RC(vtss_phy_status_get_private(vtss_state, port_no, &status));


    if (status.speed == VTSS_SPEED_1G) {
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0000,
                                        VTSS_F_PHY_BYPASS_CONTROL_HP_AUTO_MDIX_AT_FORCE));
        VTSS_N("speed:%d", status.speed);
    } else {
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, VTSS_F_PHY_BYPASS_CONTROL_HP_AUTO_MDIX_AT_FORCE,
                                        VTSS_F_PHY_BYPASS_CONTROL_HP_AUTO_MDIX_AT_FORCE));
    }

    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL,
                                    0,
                                    VTSS_F_PHY_BYPASS_CONTROL_DISABLE_PARI_SWAP_CORRECTION));

    return VTSS_RC_OK;
}

// Function for configuring MDI for a given port, with the MDI selected in the vtss_state.
static vtss_rc vtss_phy_mdi_setup(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_conf_t       *conf = &ps->setup;

    switch (conf->mdi) {
    case VTSS_PHY_MDIX_AUTO:
        VTSS_N("VTSS_PHY_MDIX_AUTO, port:%d", port_no);
        // Enable  HP AUto-MDIX, and en pair swap correction.
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0000,
                                        VTSS_F_PHY_BYPASS_CONTROL_HP_AUTO_MDIX_AT_FORCE | VTSS_F_PHY_BYPASS_CONTROL_DISABLE_PARI_SWAP_CORRECTION));

        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL,
                                        0x0, // Cu media forced normal HP-AUTO-MDIX operation, See datasheet
                                        VTSS_M_PHY_EXTENDED_MODE_CONTROL_FORCE_MDI_CROSSOVER));

        break;

    case VTSS_PHY_MDIX:
        VTSS_N("VTSS_PHY_MDIX, port:%d", port_no);

        VTSS_RC(vtss_phy_mdi_control_reg(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL,
                                        0x000C, // Cu media forced MDI-X, See datasheet
                                        VTSS_M_PHY_EXTENDED_MODE_CONTROL_FORCE_MDI_CROSSOVER));
        break;

    case VTSS_PHY_MDI:
        VTSS_N("VTSS_PHY_MDI, port:%d", port_no);

        VTSS_RC(vtss_phy_mdi_control_reg(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL,
                                        0x0008, // Cu media forced MDI, See datasheet
                                        VTSS_M_PHY_EXTENDED_MODE_CONTROL_FORCE_MDI_CROSSOVER));


        break;
    default:
        VTSS_E("Unknown mdi mode:%d, port:%d", conf->mdi, port_no);

    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_detect(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_rc               rc = VTSS_RC_OK;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16                   reg2, reg3, model = 0, sku;
    u16                   reg30 = 0;
    u32                   oui = 0;

    /* Only detect PHY once (avoid overwriting base_port_no) */
    /* Note: ps->type.channel_id is ONLY valid for the base_port_no of the PHY because of the following return */
    if (ps->family != VTSS_PHY_FAMILY_NONE) {
        VTSS_I("vtss_phy_detect: port_no: %d, Returning, ps->family != VTSS_PHY_FAMILY_NONE ", port_no);
        return VTSS_RC_OK;
    }

    ps->features = 0;
    ps->type.port_cnt = 1; //Default to 1, just to make sure that it is always set.
    ps->type.phy_api_base_no = 0;
    ps->type.channel_id = 0;
    ps->family = VTSS_PHY_FAMILY_NONE; // Default no phy detected


        /* Detect VTSS PHY type and family -- */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_IDENTIFIER_1, &reg2));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_IDENTIFIER_2, &reg3));

        oui = ((reg2 << 6) | ((reg3 >> 10) & 0x3F));
        model = ((reg3 >> 4) & 0x3F);
        ps->type.revision = (reg3 & 0xF);
        ps->conf_none = (oui == 0x005043 && model == 2 && ps->type.revision == 4 ? 1 : 0);
        /* Lookup PHY Family and Type */
        if (oui == 0x0001C1) {
            /* Vitesse OUI */
            switch (model) {
            case 0x02:
                ps->type.part_number = VTSS_PHY_TYPE_8601;
                ps->family = VTSS_PHY_FAMILY_COOPER;
                ps->type.port_cnt = 1;
                break;
            case 0x03:
                ps->type.part_number = VTSS_PHY_TYPE_8641;
                ps->family = VTSS_PHY_FAMILY_COOPER;
                ps->type.port_cnt = 1;
                break;
            case 0x05:
                ps->type.part_number = VTSS_PHY_TYPE_7385;
                ps->family = VTSS_PHY_FAMILY_LUTON;
                ps->type.port_cnt = 5;
                break;
            case 0x08:
                if (ps->reset.mac_if == VTSS_PORT_INTERFACE_INTERNAL) {
                    ps->type.part_number = VTSS_PHY_TYPE_7388;
                    ps->family = VTSS_PHY_FAMILY_LUTON;
                    ps->type.port_cnt = 8;
                } else {
                    /* VSC8538 revision A1 */
                    ps->type.part_number = VTSS_PHY_TYPE_8538;
                    ps->family = VTSS_PHY_FAMILY_SPYDER;
                    ps->type.port_cnt = 8;
                }
                break;
            case 0x09: /* VSC7389 SparX-G16 */


            case 0x0a: // VSC8574 Tesla
                ps->type.part_number = VTSS_PHY_TYPE_8574;
                ps->family = VTSS_PHY_FAMILY_TESLA;
                ps->type.port_cnt = 4;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
    
                VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));      // Switch to micro/GPIO register-page
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_REVISION, &reg30));
                if (reg30 & VTSS_F_PHY_EXTENDED_REVISION_TESLA_E) {
                    ps->type.revision = VTSS_PHY_TESLA_REV_E;
                }
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));       // Switch back to STD register-page

                break;

            case 0x0C : // VSC8504 Tesla
                ps->type.part_number = VTSS_PHY_TYPE_8504;
                ps->family = VTSS_PHY_FAMILY_TESLA;
                ps->type.port_cnt = 4;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);

                VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));      // Switch to micro/GPIO register-page
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_REVISION, &reg30));
                if (reg30 & VTSS_F_PHY_EXTENDED_REVISION_TESLA_E) {
                    ps->type.revision = VTSS_PHY_TESLA_REV_E;
                }
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));       // Switch back to STD register-page

                break;

            case 0x0D : // VSC8572 Tesla
                ps->type.part_number = VTSS_PHY_TYPE_8572;
                ps->family = VTSS_PHY_FAMILY_TESLA;
                ps->type.port_cnt = 2;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);

                VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));      // Switch to micro/GPIO register-page
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_REVISION, &reg30));
                if (reg30 & VTSS_F_PHY_EXTENDED_REVISION_TESLA_E) {
                    ps->type.revision = VTSS_PHY_TESLA_REV_E;
                }
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));       // Switch back to STD register-page

                break;

            case 0x0E : // VSC8552 Tesla
                ps->type.part_number = VTSS_PHY_TYPE_8552;
                ps->family = VTSS_PHY_FAMILY_TESLA;
                ps->type.port_cnt = 2;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);

                VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));      // Switch to micro/GPIO register-page
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_REVISION, &reg30));
                if (reg30 & VTSS_F_PHY_EXTENDED_REVISION_TESLA_E) {
                    ps->type.revision = VTSS_PHY_TESLA_REV_E;
                }
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));       // Switch back to STD register-page

                break;

            case 0x10:
                ps->type.part_number = VTSS_PHY_TYPE_7390;
                ps->family = VTSS_PHY_FAMILY_LUTON24;
                ps->type.port_cnt = 12;
                break;

            case 0x11: /* VSC7391 SparX-G16R */
                ps->type.part_number = VTSS_PHY_TYPE_7389;
                ps->family = VTSS_PHY_FAMILY_LUTON24;
                ps->type.port_cnt = 8;
                break;

            case 0x15:
                ps->type.part_number = VTSS_PHY_TYPE_7395;
                ps->family = VTSS_PHY_FAMILY_LUTON_E;
                ps->type.port_cnt = 5;
                break;

            case 0x18:
                if (ps->reset.mac_if == VTSS_PORT_INTERFACE_INTERNAL) {
                    ps->type.part_number = VTSS_PHY_TYPE_7398;
                    ps->family = VTSS_PHY_FAMILY_LUTON_E;
                    ps->type.port_cnt = 8;
                } else {
                    /* VSC8558 revision A1 */
                    ps->type.part_number = VTSS_PHY_TYPE_8558;
                    ps->family = VTSS_PHY_FAMILY_SPYDER;
                    ps->type.port_cnt = 8;
                }
                break;
            case 0x24:
                ps->type.part_number = VTSS_PHY_TYPE_8634;
                ps->family = VTSS_PHY_FAMILY_ENZO;
                ps->type.port_cnt = 4;
                ps->type.channel_id = port_no % 4; // PHY address bit 4:2 are set by CMODE pins. The channel id is bits 0-1. See PHY Datasheet page 31.
                break;
            case 0x26:
                ps->type.part_number = VTSS_PHY_TYPE_8664;
                ps->family = VTSS_PHY_FAMILY_ENZO;
                ps->type.port_cnt = 4;
                ps->type.channel_id = port_no % 4;// PHY address bit 4:2 are set by CMODE pins. The channel id is bits 0-1. See PHY Datasheet page 31.
                break;
            case 0x28:
                ps->type.part_number = VTSS_PHY_TYPE_8538;
                ps->family = VTSS_PHY_FAMILY_SPYDER;
                ps->type.port_cnt = 8;
                break;
            case 0x2D:
                ps->type.part_number = VTSS_PHY_TYPE_7420;
                ps->family = VTSS_PHY_FAMILY_LUTON26;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                ps->type.port_cnt = 10;
                break;
            case 0x2E:
                ps->type.part_number = VTSS_PHY_TYPE_8512;
                ps->family = VTSS_PHY_FAMILY_ATOM;
                ps->type.port_cnt = 12;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                break;
            case 0x2F:
                ps->type.part_number = VTSS_PHY_TYPE_8522;
                ps->family = VTSS_PHY_FAMILY_ATOM;
                ps->type.port_cnt = 12;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                break;
            case 0x38:
                ps->type.part_number = VTSS_PHY_TYPE_8558;
                ps->family = VTSS_PHY_FAMILY_SPYDER;
                ps->type.port_cnt = 8;
                break;
            case 0x35:
                ps->type.part_number = VTSS_PHY_TYPE_8658;
                ps->family = VTSS_PHY_FAMILY_SPYDER;
                ps->type.port_cnt = 8;
                break;

            //
            // Viper family
            //
            case 0x3B: // VSC8582 (dual full-featured)
                ps->type.part_number = VTSS_PHY_TYPE_8582;
                ps->family = VTSS_PHY_FAMILY_VIPER;
                ps->type.port_cnt = 2;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                ps->features |= VTSS_CAP_MACSEC;
                break;
            case 0x3C: // VSC8584 (quad full-featured)
                ps->type.part_number = VTSS_PHY_TYPE_8584;
                ps->family = VTSS_PHY_FAMILY_VIPER;
                ps->type.port_cnt = 4;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                ps->features |= VTSS_CAP_MACSEC;
                break;
            case 0x3D: // VSC8575 (quad w/o MACsec)
                ps->type.part_number = VTSS_PHY_TYPE_8575;
                ps->family = VTSS_PHY_FAMILY_VIPER;
                ps->type.port_cnt = 4;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                break;
            case 0x3E: //VSC8564 (quad w/o 1588*)
                VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_EXTENDED_CHIP_ID, &sku));
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                if ( !(sku & 0x4000) )  {
                    ps->type.part_number = VTSS_PHY_TYPE_8562;
                    ps->family = VTSS_PHY_FAMILY_VIPER;
                    ps->type.port_cnt = 2;
                    ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                    ps->features |= VTSS_CAP_MACSEC;
                } else {
                    ps->type.part_number = VTSS_PHY_TYPE_8564;
                    ps->family = VTSS_PHY_FAMILY_VIPER;
                    ps->type.port_cnt = 4;
                    ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                    ps->features |= VTSS_CAP_MACSEC;
                }
                break;
            case 0x3F: //VSC8586 - (reserved SKU)
                VTSS_E("Please implement CHIP information for VSC8586");
                break;

            //
            // ELISE family - Cost optimized VIPER (Without SGMII, FIBER media, 1588, MacSec and Legacy MAC EEE supprt)
            //
            case 0x27: //
                ps->type.part_number = VTSS_PHY_TYPE_8514;
                ps->family = VTSS_PHY_FAMILY_ELISE;
                ps->type.port_cnt = 4;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                break;

            //
            // Nano family
            //
            case 0x13 : // VSC8501 Nano
                ps->type.part_number = VTSS_PHY_TYPE_8501;
                ps->family = VTSS_PHY_FAMILY_NANO;
                ps->type.port_cnt = 1;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                ps->features |= VTSS_CAP_WOL;    /* Can Wake ON LAN */
                break;

            case 0x14 : // Ocelot internal PHY (Nano)
                ps->type.part_number = VTSS_PHY_TYPE_7435;
                ps->family = VTSS_PHY_FAMILY_NANO;
                ps->type.port_cnt = 1; // One integrated PHY
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                ps->features |= VTSS_CAP_WOL;    /* Can Wake ON LAN */
                break;

            case 0x23 : // VSC8502 Nano
                ps->type.part_number = VTSS_PHY_TYPE_8502;
                ps->family = VTSS_PHY_FAMILY_NANO;
                ps->type.port_cnt = 2;
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                ps->features |= VTSS_CAP_WOL;    /* Can Wake ON LAN */
                break;

            case 0x34 : // ServalT internal PHY (Nano)
                ps->type.part_number = VTSS_PHY_TYPE_7435;
                ps->family = VTSS_PHY_FAMILY_NANO;
                ps->type.port_cnt = 1; // One integrated PHY
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                ps->features |= VTSS_CAP_WOL;    /* Can Wake ON LAN */
                break;


            case 0x37 : // VSC8541 "Mini" PHY
                ps->type.part_number = VTSS_PHY_TYPE_8541;
                ps->family = VTSS_PHY_FAMILY_NANO;
                ps->type.port_cnt = 1; // One integrated PHY
                ps->type.channel_id = vtss_phy_chip_port(vtss_state, port_no);
                ps->features |= VTSS_CAP_SOF_TS;
                break;

            //
            // Default
            //
            default:
                ps->type.part_number = VTSS_PHY_TYPE_NONE;
                ps->family = VTSS_PHY_FAMILY_NONE;
                rc = VTSS_RC_ERROR;
                ps->type.port_cnt = 1;
                break;
            }
        } else if (oui == 0x0003F1) {
            /* Cicada OUI */
            switch (model) {
            case 0x01:
                ps->type.part_number = VTSS_PHY_TYPE_8201;
                ps->family = VTSS_PHY_FAMILY_MUSTANG;
                ps->type.port_cnt = 1;
                break;
            case 0x04:
                ps->type.part_number = VTSS_PHY_TYPE_8204;
                ps->family = VTSS_PHY_FAMILY_BLAZER;
                ps->type.port_cnt = 4;
                break;
            case 0x0B:
                ps->type.part_number = VTSS_PHY_TYPE_8211;
                ps->family = VTSS_PHY_FAMILY_COBRA;
                ps->type.port_cnt = 1;
                break;
            case 0x15:
                ps->type.part_number = VTSS_PHY_TYPE_8221;
                ps->family = VTSS_PHY_FAMILY_COBRA;
                ps->type.port_cnt = 1;
                break;
            case 0x18:
                ps->type.part_number = VTSS_PHY_TYPE_8224;
                ps->family = VTSS_PHY_FAMILY_QUATTRO;
                ps->type.port_cnt = 4;
                break;
            case 0x22:
                ps->type.part_number = VTSS_PHY_TYPE_8234;
                ps->family = VTSS_PHY_FAMILY_QUATTRO;
                ps->type.port_cnt = 4;
                break;
            case 0x2C:
                ps->type.part_number = VTSS_PHY_TYPE_8244;
                ps->family = VTSS_PHY_FAMILY_QUATTRO;
                ps->type.port_cnt = 4;
                break;
            default:
                ps->type.part_number = VTSS_PHY_TYPE_NONE;
                ps->family = VTSS_PHY_FAMILY_NONE;
                ps->type.port_cnt = 1;
                rc = VTSS_RC_ERROR;
                break;
            }
        } else {
            ps->type.part_number = VTSS_PHY_TYPE_NONE;
            ps->family = VTSS_PHY_FAMILY_NONE;
            rc = VTSS_RC_ERROR;
            ps->type.port_cnt = 1;
        }

        /* Capabilities */
        if (ps->family == VTSS_PHY_FAMILY_ATOM    ||
            ps->family == VTSS_PHY_FAMILY_LUTON26 ||
            ps->family == VTSS_PHY_FAMILY_VIPER   ||
            ps->family == VTSS_PHY_FAMILY_ELISE   ||
            ps->family == VTSS_PHY_FAMILY_NANO    ||
            ps->family == VTSS_PHY_FAMILY_TESLA) {
            ps->features |= VTSS_CAP_EEE;    /* Can EEE */
        }
        if (ps->family == VTSS_PHY_FAMILY_ATOM    ||
            ps->family == VTSS_PHY_FAMILY_LUTON26 ||
            ps->family == VTSS_PHY_FAMILY_TESLA   ||
            ps->family == VTSS_PHY_FAMILY_VIPER   ||
            ps->family == VTSS_PHY_FAMILY_ELISE   ||
            ps->family == VTSS_PHY_FAMILY_NANO    ||
            ps->family == VTSS_PHY_FAMILY_COBRA   ||
            ps->family == VTSS_PHY_FAMILY_ENZO) {
            ps->features |= VTSS_CAP_INT;    /* Can interrupts */
        }
        if (ps->family == VTSS_PHY_FAMILY_VIPER   ||
            ps->family == VTSS_PHY_FAMILY_ELISE   ||
            ps->family == VTSS_PHY_FAMILY_NANO) {
            ps->features |= VTSS_CAP_INT_EXT;   /* Extended Interrupts registers supported */
        }
        // Get the channel number (the phy number )
        if (ps->type.part_number == VTSS_PHY_TYPE_NONE) {
            ps->type.channel_id = 0;
            ps->type.base_port_no = 0;
        } else {
            if (port_no < ps->type.channel_id) {
                ps->type.base_port_no = 0; // hardcode it to zero to avoid negative base_port_no
            } else {
                ps->type.base_port_no = port_no - ps->type.channel_id; // Find the first port number for the PHY.
            }
        }

    VTSS_D("port_no:%u, Detect oui:0x%X, model:0x%X, revision:%d, detected:%s PHY:%d_%d (model:0x%02x, features:0x%02x, family:%s)",
           port_no,
           oui, model, ps->type.revision,
           ps->type.part_number != VTSS_PHY_TYPE_NONE ? "Vitesse" : "Unknown",
           ps->type.part_number, ps->type.revision, model, ps->features, vtss_phy_family2txt(ps->family));

    return rc;
}

// Function that returns the chip type/id for a given port.
// In     : port_no  - Internal port (starting from 0)
// In/Out : phy_id - Pointer to phy_id to be returned.
static vtss_rc vtss_phy_id_get_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_phy_type_t *phy_id)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    *phy_id = ps->type;
    VTSS_D("channel_id:%d, port_no:%d, phy_api_base_no:%d", phy_id->channel_id, port_no, phy_id->phy_api_base_no);
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
//=============================================================================
// 6G Macro setup - Code comes from James M.
//=============================================================================
static vtss_rc vtss_phy_sd6g_ob_cfg_wr_private(vtss_state_t        *vtss_state,
                                               const vtss_port_no_t port_no,
                                               const u8             ob_ena1v_mode,    /*- bit 30     */
                                               const u8             ob_pol,           /*- bit 29     */
                                               const u8             ob_post0,         /*- bits 28:23 */
                                               const u8             ob_post1,         /*- bits 18:22 */
                                               const u8             ob_sr_h,          /*- bit 8      */
                                               const u8             ob_resistor_ctr,  /*- bits 7:4   */
                                               const u8             ob_sr)            /*- bits 3:0   */
{
    u32 reg_val = 0;

    // configurable terms
    reg_val |= (u32)(ob_ena1v_mode) << 30 | (u32)(ob_pol) << 29 | (u32)(ob_post0) << 23 | (u32)(ob_post1) << 18 |
               (u32)(ob_sr_h) << 8 | (u32)(ob_resistor_ctr) << 4 | (u32)(ob_sr) << 0;

    // Modify the Values for ob_post0 and ob_post1
    return (vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x28, reg_val)); // ob_cfg
}

static vtss_rc vtss_phy_sd6g_ob_cfg1_wr_private(vtss_state_t        *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             ob_ena_cas,    /*- bits 8:6  */
                                                const u8             ob_lev)        /*- bits 5:0  */
{
    u32 reg_val = 0;

    // configurable terms - Modify the Values for ob_ena_cas and ob_lev
    reg_val |= (u32)(ob_ena_cas) << 6 | (u32)(ob_lev) << 0;
    return (vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x29, reg_val)); // ob_cfg1

}

static vtss_rc vtss_phy_sd6g_des_cfg_rd_private(vtss_state_t        *vtss_state,
                                                const vtss_port_no_t port_no,
                                                u8                  *des_phy_ctrl,
                                                u8                  *des_mbtr_ctrl,
                                                u8                  *des_bw_hyst,
                                                u8                  *des_bw_ana)
{
    u32 reg_val;

    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, 0x21, &reg_val)); // des_cfg
    *des_phy_ctrl =  (u8) ((reg_val & 0x0001e000) >> 13);     // bits 16:13
    *des_mbtr_ctrl = (u8) ((reg_val & 0x00001c00) >> 10);     // bits 12:10
    *des_bw_hyst =   (u8) ((reg_val & 0x000000e0) >> 5);      // bits  7:5
    *des_bw_ana =    (u8) ((reg_val & 0x0000000e) >> 1);      // bit   3:1

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_sd6g_des_cfg_wr_private(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             des_phy_ctrl,
                                                const u8             des_mbtr_ctrl,
                                                const u8             des_bw_hyst,
                                                const u8             des_bw_ana,
                                                const u8             des_cpmd_sel)
{
    u32 reg_val;

    // configurable terms
    reg_val = ((u32)(des_phy_ctrl) << 13) | ((u32)(des_mbtr_ctrl) << 10) | ((u32)(des_cpmd_sel) << 8) | ((u32)(des_bw_hyst) << 5) | ((u32)(des_bw_ana) << 1);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x21, reg_val); // des_cfg
}

static vtss_rc vtss_phy_sd6g_ib_cfg0_rd_private(vtss_state_t        *vtss_state,
                                                const vtss_port_no_t port_no,
                                                u8                  *ib_rtrm_adj,
                                                u8                  *ib_sig_det_clk_sel,
                                                u8                  *ib_reg_pat_sel_offset,
                                                u8                  *ib_cal_ena)
{
    u32 reg_val;

    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, 0x22, &reg_val)); // ib_cfg0
    *ib_rtrm_adj =           (u8) ((reg_val & 0x1E000000) >> 25);  // bits 28:25
    *ib_sig_det_clk_sel =    (u8) ((reg_val & 0x00070000) >> 16);  // bits 18:16
    *ib_reg_pat_sel_offset = (u8) ((reg_val & 0x00000300) >> 8);   // bits 9:8
    *ib_cal_ena =            (u8) ((reg_val & 0x00000008) >> 3);   // bit 3

    return VTSS_RC_OK;
}


static vtss_rc vtss_phy_sd6g_ib_cfg0_wr_private(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             ib_rtrm_adj,
                                                const u8             ib_sig_det_clk_sel,
                                                const u8             ib_reg_pat_sel_offset,
                                                const u8             ib_cal_ena)
{
    u32 base_val;
    u32 reg_val;

    // constant terms
    base_val = (1 << 30) | (1 << 29) | (5 << 21) | (1 << 19) | (1 << 14) | (1 << 12) | (2 << 10) | (1 << 5) | (1 << 4) | 7;
    // configurable terms
    reg_val = base_val | ((u32)(ib_rtrm_adj) << 25) | ((u32)(ib_sig_det_clk_sel) << 16) | ((u32)(ib_reg_pat_sel_offset) << 8) | ((u32)(ib_cal_ena) << 3);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x22, reg_val); // ib_cfg0
}


#if 0  // Uncomment this function when and if needed
static vtss_rc vtss_phy_sd6g_ib_cfg1_rd_private(vtss_state_t        *vtss_state,
                                                const vtss_port_no_t port_no,
                                                u8                  *ib_tjtag,
                                                u8                  *ib_tsdet,
                                                u8                  *ib_scaly,
                                                u8                  *ib_frc_offset)
{
    u32 reg_val;

    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, 0x23, &reg_val)); // ib_cfg1
    *ib_tjtag =  (u8) ((reg_val & 0x003e0000) >> 17);      // bits 21:17
    *ib_tsdet =  (u8) ((reg_val & 0x0001f000) >> 12);      // bits 16:12
    *ib_scaly =  (u8) ((reg_val & 0x00000f00) >> 8);       // bits 11:8
    *ib_frc_offset = (u8) ((reg_val & 0x00000001) >> 0);   // bit  0

    return VTSS_RC_OK;
}
#endif

static vtss_rc vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             ib_tjtag,
                                                const u8             ib_tsdet,
                                                const u8             ib_scaly,
                                                const u8             ib_frc_offset,
                                                const u8             ib_filt_offset)
{
    u32 ib_filt_val;
    u32 ib_frc_val;
    u32 reg_val = 0;

    // constant terms
    ib_filt_val = (1 << 7) + (1 << 6) + (1 << 5);
    ib_frc_val = (0 << 3) + (0 << 2) + (0 << 1);
    // configurable terms
    reg_val  = ((u32)ib_tjtag << 17) + ((u32)ib_tsdet << 12) + ((u32)ib_scaly << 8) + ib_filt_val + ((u32)ib_filt_offset << 4) + ib_frc_val + ((u32)ib_frc_offset << 0);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x23, reg_val); // ib_cfg1
}

static vtss_rc vtss_phy_sd6g_ib_cfg2_rd_private(vtss_state_t        *vtss_state,
                                                const vtss_port_no_t port_no,
                                                u8                  *ib_tinfv,
                                                u8                  *ib_tcalv,
                                                u8                  *ib_ureg)
{
    u32 reg_val;

    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, 0x24, &reg_val)); // ib_cfg2
    *ib_tinfv =  (u8) ((reg_val & 0x70000000) >> 28);  // bits 30:28
    *ib_tcalv =  (u8) ((reg_val & 0x000003e0) >> 5);   // bits  9:5
    *ib_ureg =   (u8) ((reg_val & 0x00000007) >> 0);   // bits  2:0

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_sd6g_ib_cfg2_wr_private(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             ib_tinfv,
                                                const u8             ib_tcalv,
                                                const u8             ib_ureg)
{
    u32 base_val;
    u32 ib_cfg2_val;

    // constant terms
    base_val = 0x0f878010; // in theory, we should read the register and mask off bits 30:28, etc., and/or pass in other arguments
    ib_cfg2_val = base_val | ((u32)(ib_tinfv) << 28) | ((u32)(ib_tcalv) << 5) | ((u32)(ib_ureg) << 0);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x24, ib_cfg2_val); // ib_cfg2
}

static vtss_rc vtss_phy_sd6g_ib_cfg3_wr_private(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             ib_ini_hp,
                                                const u8             ib_ini_mid,
                                                const u8             ib_ini_lp,
                                                const u8             ib_ini_offset)
{
    u32 reg_val;

    reg_val  = ((u32)ib_ini_hp << 24) + ((u32)ib_ini_mid << 16) + ((u32)ib_ini_lp << 8) + ((u32)ib_ini_offset << 0);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x25, reg_val); // ib_cfg3
}

static vtss_rc vtss_phy_sd6g_ib_cfg4_wr_private(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             ib_max_hp,
                                                const u8             ib_max_mid,
                                                const u8             ib_max_lp,
                                                const u8             ib_max_offset)
{
    u32 reg_val;

    reg_val  = ((u32)ib_max_hp << 24) + ((u32)ib_max_mid << 16) + ((u32)ib_max_lp << 8) + ((u32)ib_max_offset << 0);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x26, reg_val); // ib_cfg4
}

static vtss_rc vtss_phy_sd6g_pll_cfg_wr_private(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             pll_ena_offs,
                                                const u8             pll_fsm_ctrl_data,
                                                const u8             pll_fsm_ena)
{
    u32 reg_val;

    reg_val  = ((u32)pll_ena_offs << 21) + ((u32)pll_fsm_ctrl_data << 8) + ((u32)pll_fsm_ena << 7);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x2b, reg_val); // pll_cfg
}

static vtss_rc vtss_phy_sd6g_common_cfg_wr_private(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t port_no,
                                                   const u8             sys_rst,
                                                   const u8             ena_lane,
                                                   const u8             ena_loop,
                                                   const u8             qrate,
                                                   const u8             if_mode,
                                                   const u8             pwd_tx)
{
//  ena_loop = 8 for eloop
//           = 4 for floop
//           = 2 for iloop
//           = 1 for ploop
//  qrate    = 1 for SGMII, 0 for QSGMII
//  if_mode  = 1 for SGMII, 3 for QSGMII

    u32 reg_val;

    reg_val  = ((u32)sys_rst << 31) + ((u32)ena_lane << 18) + ((u32)pwd_tx << 16) + ((u32)ena_loop << 8) + ((u32)qrate << 6) + ((u32)if_mode << 4);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x2c, reg_val); // common_cfg
}

static vtss_rc vtss_phy_sd6g_gp_cfg_wr_private(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no,
                                               const u32            gp_cfg_val)
{
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x2e, gp_cfg_val); // gp_cfg
}

static vtss_rc vtss_phy_sd6g_misc_cfg_wr_private(vtss_state_t *vtss_state,
                                                 const vtss_port_no_t port_no,
                                                 const u8             lane_rst)
{
    // all other bits are 0 for now
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x3b, (u32)lane_rst); // misc_cfg
}

// Access LCPLL Cfg_0
static vtss_rc vtss_phy_pll5g_cfg0_wr_private(vtss_state_t *vtss_state,
                                              const vtss_port_no_t port_no,
                                              const u8             selbgv820)
{
    u32 base_val;
    u32 reg_val;

    // constant terms
    base_val = 0x7036f145; // in theory, we should read the register and mask off bits 26:23, or pass in other arguments
    // configurable terms
    reg_val = base_val | ((u32)(selbgv820) << 23);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x06, reg_val); // pll5g_cfg0
}
#endif /* VTSS_FEATURE_SERDES_MACRO_SETTINGS */

// Access LCPLL Cfg_2
static vtss_rc vtss_phy_pll5g_cfg2_wr_private(vtss_state_t        *vtss_state,
                                              const vtss_port_no_t port_no,
                                              const u8             disable_fsm,
                                              const u8             ena_clk_bypass)
{
    u32 rd_dat;

    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, 0x08, &rd_dat)); // pll5g_cfg2
    rd_dat &= 0xff7ffffd; // Mask Off bit 1:disable fsm and bit 23:ena_clk_bypass
    rd_dat |= ((u32)disable_fsm << 1) | ((u32)ena_clk_bypass << 23);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x08, rd_dat); // pll5g_cfg2
}

// Macro for making sure that we don't run forever
//#define SD6G_TIMEOUT(timeout_var) if (timeout_var-- == 0) {goto macro_6g_err;} else {MEPA_MSLEEP(1);}
#define SD6G_TIMEOUT(timeout_var) if (timeout_var-- == 0) {VTSS_E("TIMEOUT_ERROR: SD6G MACRO NOT CONFIGURED CORRECTLY! for port:%d", port_no); return VTSS_RC_ERR_PHY_6G_MACRO_SETUP;} else {MEPA_MSLEEP(1);}

// trigger a write to the spcified MCB
static vtss_rc vtss_phy_mcb_wr_trig_private(vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no,
                                            const u32            mcb_reg_addr,
                                            const u8             mcb_slave_num)
{
    u8 timeout;
    u32 rd_dat;

    VTSS_RC(vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, mcb_reg_addr, (0x80000000 | (1L << mcb_slave_num)))); // write back MCB
    timeout = 200;
    do {
        VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, mcb_reg_addr, &rd_dat)); // wait for MCB write to complete
        SD6G_TIMEOUT(timeout);
    } while (rd_dat & 0x80000000);   // Wait for Bit 31 to clear
    return VTSS_RC_OK;
}

// trigger a read to the spcified MCB
static vtss_rc vtss_phy_mcb_rd_trig_private(vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no,
                                            const u32            mcb_reg_addr,
                                            const u8             mcb_slave_num)
{
    u8 timeout;
    u32 rd_dat;

    VTSS_RC(vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, mcb_reg_addr, (0x40000000 | (1L << mcb_slave_num)))); // read MCB
    timeout = 200;
    do {
        VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, mcb_reg_addr, &rd_dat)); // wait for MCB read to complete
        VTSS_N("port:%d,timeout:%d", port_no, timeout);
        SD6G_TIMEOUT(timeout);
    } while (rd_dat & 0x40000000);   // Wait for Bit 30 to clear
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_sd6g_dft_cfg2_wr_private(vtss_state_t *vtss_state,
                                                 const vtss_port_no_t port_no,
                                                 const u8             rx_ji_ampl,
                                                 const u8             rx_step_freq,
                                                 const u8             rx_ji_ena,
                                                 const u8             rx_waveform_sel,
                                                 const u8             rx_freqoff_dir,
                                                 const u8             rx_freqoff_ena)
{
    u32 reg_val;

    // configurable terms
    reg_val = ((u32)(rx_ji_ampl) << 8) | ((u32)(rx_step_freq) << 4) | ((u32)(rx_ji_ena) << 3) | ((u32)(rx_waveform_sel) << 2) | ((u32)(rx_freqoff_dir) << 1) | (u32)(rx_freqoff_ena);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x37, reg_val);
}

static vtss_rc vtss_phy_sd6g_dft_cfg0_wr_private(vtss_state_t *vtss_state,
                                                 const vtss_port_no_t port_no,
                                                 const u8             prbs_sel,
                                                 const u8             test_mode,
                                                 const u8             rx_dft_ena)
{
    u32 reg_val;

    // configurable terms
    reg_val = ((u32)(prbs_sel) << 20) | ((u32)(test_mode) << 16) | ((u32)(rx_dft_ena) << 2);
    return vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x35, reg_val);
}

static vtss_rc detune_pll5g(vtss_state_t *vtss_state,
                            const vtss_port_no_t port_no)
{
    u32 rd_dat;
    u32 gain_test = 0;
    u32 ena_gain_test = 1;
    vtss_phy_type_t phy_id;

    VTSS_I("DeTune_PLL5G");
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x08, &rd_dat)); // pll5g_cfg2
    rd_dat &= 0xfffffc1e; // Mask Off bit 0: ena_gain_test & bit [9:5] = gain_test
    rd_dat |= ((u32)ena_gain_test << 0) | ((u32)gain_test << 5);
    return vtss_phy_macsec_csr_wr_private(vtss_state, phy_id.base_port_no, 7, 0x08, rd_dat); // pll5g_cfg2
}

static vtss_rc tune_pll5g(vtss_state_t *vtss_state,
                          const vtss_port_no_t port_no)
{
    u32 rd_dat;
    u32 ena_gain_test = 0;
    vtss_phy_type_t phy_id;

    VTSS_I("Tune_PLL5G");
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x08, &rd_dat)); // pll5g_cfg2
    rd_dat &= 0xfffffffe; // Mask Off bit 0: ena_gain_test
    rd_dat |= (u32)ena_gain_test << 0;
    return vtss_phy_macsec_csr_wr_private(vtss_state, phy_id.base_port_no, 7, 0x08, rd_dat); // pll5g_cfg2
}

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
/*- TESLA FAMILY ONLY -- VSC8574 */
static vtss_rc vtss_phy_cfg_ob_lev_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 val)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t        phy_id;
    u16                    reg18g = 0;
    vtss_rc                rc = VTSS_RC_OK;
    u8                     tmp = 0;

    if (vtss_state->sync_calling_private) {
        return VTSS_RC_OK; // Skipping warm start register check because the same registers are writing multiple times with different values.
    }

    switch (ps->family) {
    case VTSS_PHY_FAMILY_TESLA:
        break;

    default:
        return VTSS_RC_OK;
    }

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    VTSS_N("TESLA: Port: %d,  base_port_no: %d,  Executing vtss_phy_cfg_ob_lev_private", port_no, phy_id.base_port_no );

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, 0x8013));  // Read MCB for 6G macro 0 into PRAM
    (void)  vtss_phy_wait_for_micro_complete(vtss_state, phy_id.base_port_no);

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, 0xd7cc));  // set mem_addr to cfg_buf[5] (0x47cc)
    (void)(vtss_phy_wait_for_micro_complete(vtss_state, phy_id.base_port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, 0x8007));  // read the value of cfg_buf[5] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, phy_id.base_port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch back to micro/GPIO register-page
    // get bits 11:4 from return value and mask off upper 3 bits
    VTSS_RC(PHY_RD_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
    tmp = (u8)((reg18g >> 4) & 0x1f);
    // OR in lower 3 bits of val shifted aprropriately
    tmp |= ((val & 7) << 5);

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch back to micro/GPIO register-page
    // write the value back to cfg_buf[5] w/ post-incr.
    VTSS_RC(PHY_WR_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, 0x9006 | ((u16)tmp << 4)));
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, phy_id.base_port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, 0x8007));  // read the value of cfg_buf[6] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, phy_id.base_port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch back to micro/GPIO register-page
    // get bits 11:4 from return value and mask off lower 3 bits
    VTSS_RC(PHY_RD_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
    tmp = (u8)((reg18g >> 4) & 0xf8);
    // OR in upper 3 bits of val shifted aprropriately
    tmp |= ((val >> 3) & 7);

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch back to micro/GPIO register-page
    // write the value back to cfg_buf[6] w/o post-incr.
    VTSS_RC(PHY_WR_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | ((u16)tmp << 4)));
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, phy_id.base_port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, phy_id.base_port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_MICRO_PAGE, 0x9c40));  // Write MCB for 6G macro 0 from PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, phy_id.base_port_no));

    return rc;
}


/*- VIPER and ELISE FAMILY ONLY -- VSC8584 & VSC8514 */
static vtss_rc vtss_phy_sd6g_ob_post_wr_private(vtss_state_t       *vtss_state,
                                                const vtss_port_no_t port_no,
                                                const u8             ob_post0,
                                                const u8             ob_post1)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t phy_id;
    u16 reg_val;
    u8 mac_if;

    u8 ob_ena1v_mode = 1;
    u8 ob_pol = 1;
    u8 ob_resistor_ctr = 1;
    u8 ob_sr_h = 0;
    u8 ob_sr = 0;

    if (vtss_state->sync_calling_private) {
        return VTSS_RC_OK; // Skipping warm start register check because the same registers are writing multiple times with different values.
    }

    /*- This applies to Viper and Elise PHY's only */
    switch (ps->family) {
    // These chips support the 6G macro setup
    case VTSS_PHY_FAMILY_VIPER:
    /*-   viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A);    -- Uncomment for Viper RevA if needed */
        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ELISE:
        break;
    default:
        return VTSS_RC_OK;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    mac_if = (reg_val >> 14) & 0x3;

    // See TN1052 6G SerDes Table for Elise and Viper_RevA
    if (mac_if ==  0x1) {  // QSGMII, See data sheet register 19G
        ob_sr_h = 0;
        ob_sr = 0;
    } else if (mac_if ==  0x0) { // SGMII, See data sheet register 19G
        ob_sr_h = 1;
        ob_sr = 7;
    } else {
        return VTSS_RC_OK;
    }

    // Get the PHY_ID struct so we can determine Port 0 of the PHY
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    // Read SerDes info in so we can manipulate it
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // read 6G MCB into CSRs
    // Modify the Values for ob_post0 and ob_post1
    VTSS_RC(vtss_phy_sd6g_ob_cfg_wr_private(vtss_state, phy_id.base_port_no,
                                            ob_ena1v_mode, ob_pol, ob_post0, ob_post1,
                                            ob_sr_h, ob_resistor_ctr, ob_sr));
    // Write SerDes changes back out
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // Write 6G MCB into CSRs

    return VTSS_RC_OK;
}

/*- VIPER, ELISE, and TESLA FAMILY ONLY -- VSC8584, VSC8574 & VSC8514 */
static vtss_rc vtss_phy_sd6g_ob_lev_wr_private(vtss_state_t        *vtss_state,
                                               const vtss_port_no_t port_no,
                                               const u8             ob_lev)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t phy_id;

    u16 reg_val = 0;
    u8  mac_if;
    u8  ob_ena_cas = 0;    //  (0 << 8) + (0 << 7) + (0 << 6);

    /*- BOOL viper_rev_a = FALSE;  -- Uncomment to check for Viper RevA if Viper RevB is different */

    if (vtss_state->sync_calling_private) {
        return VTSS_RC_OK; // Skipping warm start register check because the same registers are writing multiple times with different values.
    }

    switch (ps->family) {
    case VTSS_PHY_FAMILY_TESLA:
        return (vtss_phy_cfg_ob_lev_private(vtss_state, port_no, ob_lev));

    // These chips support the 6G macro setup
    case VTSS_PHY_FAMILY_VIPER:
    /*-   viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A);    -- Uncomment for Viper RevA if needed */
        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ELISE:
        break;

    default:
        return VTSS_RC_OK;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    mac_if = (reg_val >> 14) & 0x3;

    // See TN1052 6G SerDes Table for Elise and Viper_RevA
    if (mac_if ==  0x1) {  // QSGMII, See data sheet register 19G
        ob_ena_cas = 0;
    } else if (mac_if ==  0x0) { // SGMII, See data sheet register 19G
        ob_ena_cas = 2;
    } else {
        return VTSS_RC_OK;
    }

    // Get the PHY_ID struct so we can determine Port 0 of the PHY
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    VTSS_N("VIPER/ELISE: Port: %d,  base_port_no: %d,  Executing vtss_phy_sd6g_ob_lev_wr_private", port_no, phy_id.base_port_no );

    // Read SerDes info in so we can manipulate it
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // read 6G MCB into CSRs
    // Modify the Values for ob_level
    VTSS_RC(vtss_phy_sd6g_ob_cfg1_wr_private(vtss_state, phy_id.base_port_no, ob_ena_cas, ob_lev));
    // Write SerDes changes back out
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // Write 6G MCB into CSRs

    return VTSS_RC_OK; // ob_cfg1
}

//=============================================================================
// 6G Macro debug
//=============================================================================
static vtss_rc vtss_phy_sd6g_csr_reg_rd_private(vtss_state_t              *vtss_state,
                                                const vtss_port_no_t       port_no,
                                                const u16                  tgt,
                                                const u32                  reg,
                                                u32                       *reg_val)
{
    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, tgt, (u32)reg, reg_val));
    return VTSS_RC_OK;
}

#if defined VTSS_PHY_SERDES_DEBUG_ENABLE
static vtss_rc vtss_phy_sd6g_csr_reg_wr_private(vtss_state_t *vtss_state,
                                                const vtss_port_no_t       port_no,
                                                const u16                  tgt,
                                                const u32                  reg,
                                                const u32                  reg_val)
{
    return (vtss_phy_macsec_csr_wr_private(vtss_state, port_no, tgt, reg, reg_val));
}
#endif

/*- VIPER & ELISE FAMILY ONLY -- VSC8584 & VSC8514 */
static vtss_rc vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state_t        *vtss_state,
                                                    const vtss_port_no_t      port_no,
                                                    const u32                 csr_reg,
                                                    u32                      *csr_reg_val)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t phy_id;

    u16 reg_val = 0;
    u16 csr_tgt = 7;
    u8  mac_if;
//    u8  ob_ena_cas = 0;    //  (0 << 8) + (0 << 7) + (0 << 6);
    u8  mcb_slave_num = 0;
    u32 mcb_addr = 0;

    if (csr_reg > VTSS_PHY_SERDES_6G_CSR_REG_MAX) {
        return VTSS_RC_ERROR;
    }

    switch (ps->type.channel_id) {
    case 0:
        mcb_slave_num = 0;
        mcb_addr = 0x3f;
        break;
    case 1:
        mcb_slave_num = 1;
        mcb_addr = 0x20;
        break;
    case 2:
        mcb_slave_num = 3;
        mcb_addr = 0x20;
        break;
    case 3:
        mcb_slave_num = 5;
        mcb_addr = 0x20;
        break;
    default:
        return VTSS_RC_ERROR;
        break;
    }

    switch (ps->family) {
    // These chips support the 6G macro setup
    case VTSS_PHY_FAMILY_VIPER:
    /*-   viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A);    -- Uncomment for Viper RevA if needed */
        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ELISE:
        break;

    default:
        return VTSS_RC_OK;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    mac_if = (reg_val >> 14) & 0x3;

    // See TN1052 6G SerDes Table for Elise and Viper_RevA
    if (mac_if ==  0x1) {  // QSGMII, See data sheet register 19G
//        ob_ena_cas = 0;
    } else if (mac_if ==  0x0) { // SGMII, See data sheet register 19G
//        ob_ena_cas = 2;
    } else {
        return VTSS_RC_OK;
    }

    // Get the PHY_ID struct so we can determine Port 0 of the PHY
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    // Read SerDes info in so we can manipulate it
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, mcb_addr, mcb_slave_num)); // read 1G or 6G MCB into CSRs
    // Modify the Values for ob_level
    VTSS_RC(vtss_phy_sd6g_csr_reg_rd_private(vtss_state, phy_id.base_port_no, csr_tgt, csr_reg, csr_reg_val));
    VTSS_D("VIPER/ELISE: Port: %d, base_port_no: %d,  MCB_Slave: %d, Reading Reg: 0x%x, Value: 0x%x", port_no, phy_id.base_port_no, mcb_slave_num, csr_reg, *csr_reg_val);

    return VTSS_RC_OK;
}

#if defined VTSS_PHY_SERDES_DEBUG_ENABLE
static vtss_rc vtss_phy_sd6g_csr_reg_wr_dbg_private(vtss_state_t        *vtss_state,
                                                    const vtss_port_no_t      port_no,
                                                    const u32                 csr_reg,
                                                    u32                       csr_reg_val)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t phy_id;

    u16 reg_val = 0;
    u16 csr_tgt = 7;
    u8  mac_if;
    u8  ob_ena_cas = 0;    //  (0 << 8) + (0 << 7) + (0 << 6);
    u8  mcb_slave_num = 0;
    u32 mcb_addr = 0;

    if (csr_reg > VTSS_PHY_SERDES_6G_CSR_REG_MAX) {
        return VTSS_RC_ERROR;
    }

    switch (ps->type.channel_id) {
    case 0:
        mcb_slave_num = 0;
        mcb_addr = 0x3f;
        break;
    case 1:
        mcb_slave_num = 1;
        mcb_addr = 0x20;
        break;
    case 2:
        mcb_slave_num = 3;
        mcb_addr = 0x20;
        break;
    case 3:
        mcb_slave_num = 5;
        mcb_addr = 0x20;
        break;
    default:
        return VTSS_RC_ERROR;
        break;
    }

    switch (ps->family) {
    // These chips support the 6G macro setup
    case VTSS_PHY_FAMILY_VIPER:
    /*-   viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A);    -- Uncomment for Viper RevA if needed */
        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ELISE:
        break;

    default:
        return VTSS_RC_OK;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    mac_if = (reg_val >> 14) & 0x3;

    // See TN1052 6G SerDes Table for Elise and Viper_RevA
    if (mac_if ==  0x1) {  // QSGMII, See data sheet register 19G
        ob_ena_cas = 0;
    } else if (mac_if ==  0x0) { // SGMII, See data sheet register 19G
        ob_ena_cas = 2;
    } else {
        return VTSS_RC_OK;
    }

    // Get the PHY_ID struct so we can determine Port 0 of the PHY
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    // Read SerDes info in so we can manipulate it
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, mcb_addr, mcb_slave_num)); // read 1G or 6G MCB into CSRs
    // Modify the Values for ob_level
    VTSS_RC(vtss_phy_sd6g_csr_reg_wr_private(vtss_state, phy_id.base_port_no, csr_tgt, csr_reg, csr_reg_val));
    VTSS_D("VIPER/ELISE: Port: %d, base_port_no: %d,  MCB_Slave: %d, Writing Reg: 0x%x, Value: 0x%x", port_no, phy_id.base_port_no, mcb_slave_num, csr_reg, csr_reg_val);
    //printf("VIPER/ELISE: Port: %d, base_port_no: %d,  MCB_Slave: %d, Writing Reg: 0x%x, Value: 0x%x \n", port_no, phy_id.base_port_no, mcb_slave_num, csr_reg, csr_reg_val);
    // Write SerDes changes back out
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, mcb_addr, mcb_slave_num)); // Write 1G or 6G MCB into CSRs

    return VTSS_RC_OK;
}
#endif

//=============================================================================
// End of 6G Macro debug
//=============================================================================

//=============================================================================
// 1G Macro setup
//=============================================================================

static vtss_rc vtss_phy_sd1g_des_cfg_wr_private(vtss_state_t         *vtss_state,
                                                const vtss_port_no_t  port_no,
                                                const u8              des_phs_ctrl,
                                                const u8              des_mbtr_ctrl)
{
    u32 reg_val;

    // read old val
    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, 0x12, &reg_val)); // des_cfg
    // mask off old des_phs_ctrl (16:13) and des_mbtr_ctrl (10:8) values
    reg_val &= ~(0xf << 13); // des_phs_ctrl (16:13)
    reg_val &= ~(0x7 << 8);  // des_mbtr_ctrl (10:8)
    // OR in new values for des_phs_ctrl (16:13) and des_mbtr_ctrl (10:8)
    reg_val = reg_val | ((u32)(des_phs_ctrl) << 13) | ((u32)(des_mbtr_ctrl) << 8);
    // write back with updated values
    return (vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x12, reg_val)); // des_cfg
}
static vtss_rc vtss_phy_sd1g_ib_cfg_wr_private(vtss_state_t         *vtss_state,
                                               const vtss_port_no_t  port_no,
                                               const u8              ib_ena_cmv_term)
{
    u32 reg_val;

    // read old val
    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, 0x13, &reg_val)); // ib_cfg
    // mask off old ib_ena_cmv_term (13) value
    reg_val &= ~(1 << 13); // ib_ena_cmv_term (13)
    // OR in new value for ib_ena_cmv_term (13)
    reg_val = reg_val | ((u32)(ib_ena_cmv_term) << 13);
    // write back with updated values
    return (vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x13, reg_val)); // ib_cfg
}

static vtss_rc vtss_phy_sd1g_misc_cfg_wr_private(vtss_state_t         *vtss_state,
                                                 const vtss_port_no_t  port_no,
                                                 const u8              des_100fx_cpmd_mode)
{
    u32 reg_val;

    // read old val
    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, 7, 0x1e, &reg_val)); // ib_cfg
    // mask off old des_100fx_cpmd_mode (9) value
    reg_val &= ~(1 << 9); // des_100fx_cpmd_mode (9)
    // OR in new value for des_100fx_cpmd_mode (9)
    reg_val = reg_val | ((u32)(des_100fx_cpmd_mode) << 9);
    // write back with updated values
    return (vtss_phy_macsec_csr_wr_private(vtss_state, port_no, 7, 0x1e, reg_val)); // ib_cfg
}

static vtss_rc vtss_phy_sd1g_patch_private(vtss_state_t                *vtss_state,
                                           const vtss_port_no_t        port_no,
                                           const BOOL                  is_100fx)
{
    vtss_phy_type_t phy_id;
    u8 slave_addr = port_no * 2;

    VTSS_D("Setting 1G SerDes for port_no: %d   is_100fx: %x ", port_no, is_100fx);
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    if ((VTSS_PHY_BASE_PORTS_FOUND) != VTSS_RC_OK) { // Make sure that base ports are found for the PHY Instance
        VTSS_E("Early-Exit from 1G SerDes Patch Config - Base_Port not found!!  base_port: %u", phy_id.base_port_no);
        return VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND;
    }

    if ((phy_id.base_port_no) >= 0xffff) { // Make sure that base ports are found for this port, Default = -1
        VTSS_E("Early-Exit from 1G SerDes Patch Config - Base_Port INVALID!!  base_port: %u", phy_id.base_port_no);
        return VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND;
    }


    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x20, slave_addr)); // read 1G MCB into CSRs

    if (is_100fx) {
        VTSS_RC(vtss_phy_sd1g_ib_cfg_wr_private(vtss_state, phy_id.base_port_no, 0));      // ib_cfg
        VTSS_RC(vtss_phy_sd1g_misc_cfg_wr_private(vtss_state, phy_id.base_port_no, 1));    // misc_cfg
        VTSS_RC(vtss_phy_sd1g_des_cfg_wr_private(vtss_state, phy_id.base_port_no, 14, 3)); // des_cfg
    } else {
        VTSS_RC(vtss_phy_sd1g_ib_cfg_wr_private(vtss_state, phy_id.base_port_no, 1));      // ib_cfg
        VTSS_RC(vtss_phy_sd1g_misc_cfg_wr_private(vtss_state, phy_id.base_port_no, 0));    // misc_cfg
        VTSS_RC(vtss_phy_sd1g_des_cfg_wr_private(vtss_state, phy_id.base_port_no,  6, 2)); // des_cfg
    }

    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x20, slave_addr)); // write back 1G MCB

    VTSS_D("vtss_phy_sd1g_patch_private: Port: %d  is_100fx: %x;  sd1g patch Complete", port_no, is_100fx);

    return VTSS_RC_OK;
}

//=============================================================================
// End of 1G Macro
//=============================================================================

//=============================================================================
// Updated version of vtss_phy_sd6g_patch_private that differentiate Viper A vs Viper B & Elise
// vtss_phy_sd6g_patch_private requires a de-tuning of the LCPLL and tuning it back after completion
// Therefore, must call detune_pll5g(vtss_state, port_no) prior to vtss_phy_sd6g_patch_private()
// and call tune_pll5g(vtss_state, port_no) after
static vtss_rc vtss_phy_sd6g_patch_private(vtss_state_t                *vtss_state,
                                           const vtss_port_no_t        port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    BOOL viper_rev_a = FALSE;
    vtss_phy_type_t phy_id;
    u32  rd_dat = 0;
    u16  reg_val = 0;
    u16  timeout = 0;
    u8   rcomp;
    u8   ib_rtrm_adj;
    u8   iter;
    u8   gp_iter;

    u8   pll_fsm_ctrl_data;
    u8   qrate;
    u8   if_mode;
    u8   des_bw_ana_val;
    u8   ib_sig_det_clk_sel_cal = 0; // 0 for during IBCAL for all
    u8   ib_sig_det_clk_sel_mm  = 7;
    u8   ib_tsdet_cal = 16;
    u8   ib_tsdet_mm  = 5;
    u8   mac_if;

    VTSS_D("Entering: vtss_phy_sd6g_patch_private: Port: %d", port_no);

    switch (ps->family) {
    // These chips support the 6G macro setup
    // Note: Viper Rev. A is different from Viper Rev B and Elise SerDes, which are the same design
    case VTSS_PHY_FAMILY_VIPER:
        viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A);
        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ELISE:
        break;
    default:
        return VTSS_RC_OK;
    }

    // Configure for SGMII only for IB_CAL
    pll_fsm_ctrl_data = 60;
    qrate   = 1;
    if_mode = 1;
    des_bw_ana_val = 3;

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    // Get the Base Port
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    // Detune/Unlock LCPLL
    VTSS_RC(detune_pll5g(vtss_state, port_no));

    //0. Reset RCPLL
    VTSS_RC(vtss_phy_sd6g_pll_cfg_wr_private(vtss_state, phy_id.base_port_no, 3, pll_fsm_ctrl_data, 0)); // pll_fsm_ena=0, reset rcpll
    VTSS_RC(vtss_phy_sd6g_common_cfg_wr_private(vtss_state, phy_id.base_port_no, 0, 0, 0, qrate, if_mode, 0)); // sys_rst=0, assert sys_rst
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
    //1. Configure sd6g for SGMII prior to sd6g_IB_CAL
    if (viper_rev_a) {
        // modify RComp value for Viper Rev. A
        VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x0f, &rd_dat)); // rcomp_status
        rcomp = rd_dat & 0xf; //~10;
        ib_rtrm_adj = rcomp - 3;
    } else {
        // use trim offset for Viper Rev. B+ and Elise
        ib_rtrm_adj = 16 - 3;
    }

    // update des_bw_ana for bug 14948
    VTSS_RC(vtss_phy_sd6g_des_cfg_wr_private(vtss_state, phy_id.base_port_no, 6, 2, 5, des_bw_ana_val, 0)); // des_cfg
    VTSS_RC(vtss_phy_sd6g_ib_cfg0_wr_private(vtss_state, phy_id.base_port_no, ib_rtrm_adj, ib_sig_det_clk_sel_mm, 0, 0)); // ib_cfg0
    VTSS_RC(vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state, phy_id.base_port_no, 8, ib_tsdet_mm, 15, 0, 1)); // ib_cfg1

    // update ib_tcalv & ib_ureg for bug 14626
    VTSS_RC(vtss_phy_sd6g_ib_cfg2_wr_private(vtss_state, phy_id.base_port_no, 3, 13, 5)); // ib_cfg2
    VTSS_RC(vtss_phy_sd6g_ib_cfg3_wr_private(vtss_state, phy_id.base_port_no,  0, 31, 1, 31)); // ib_cfg3
    VTSS_RC(vtss_phy_sd6g_ib_cfg4_wr_private(vtss_state, phy_id.base_port_no, 63, 63, 2, 63)); // ib_cfg4

    VTSS_RC(vtss_phy_sd6g_common_cfg_wr_private(vtss_state, phy_id.base_port_no, 1, 1, 0, qrate, if_mode, 0)); // sys_rst, ena_lane
    VTSS_RC(vtss_phy_sd6g_misc_cfg_wr_private(vtss_state, phy_id.base_port_no, 1)); // assert lane reset
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    //2. Start rcpll_fsm
    VTSS_D("Calibrating RCPLL...");
    VTSS_RC(vtss_phy_sd6g_pll_cfg_wr_private(vtss_state, phy_id.base_port_no, 3, pll_fsm_ctrl_data, 1)); // pll_fsm_ena
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    // 3. Wait for PLL cal to complete
    timeout = 300;
    do {
        VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // read 6G MCB into CSRs
        VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x31, &rd_dat)); // pll_status
        SD6G_TIMEOUT(timeout);
    } while (rd_dat & 0x0001000); // wait for bit 12 to clear

    // 4. Release digital reset and disable transmitter
    VTSS_RC(vtss_phy_sd6g_misc_cfg_wr_private(vtss_state, phy_id.base_port_no, 0)); // release lane reset
    VTSS_RC(vtss_phy_sd6g_common_cfg_wr_private(vtss_state, phy_id.base_port_no, 1, 1, 0, qrate, if_mode, 1)); // sys_rst, ena_lane, pwd_tx
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    // 5. Apply a frequency offset on RX-side (using internal FoJi logic)
    // Make sure that equipment loop is not active. Already done above
    VTSS_RC(vtss_phy_sd6g_gp_cfg_wr_private(vtss_state, phy_id.base_port_no, 768)); // gp_cfg
    VTSS_RC(vtss_phy_sd6g_dft_cfg2_wr_private(vtss_state, phy_id.base_port_no, 0, 2, 0, 0, 0, 1)); // rx_step_freq=2, rx_ji_ena=0, rx_freqoff_dir=0, rx_freqoff_ena=1
    VTSS_RC(vtss_phy_sd6g_dft_cfg0_wr_private(vtss_state, phy_id.base_port_no, 0, 0, 1)); // rd_dft_ena
    VTSS_RC(vtss_phy_sd6g_des_cfg_wr_private(vtss_state, phy_id.base_port_no, 6, 2, 5, des_bw_ana_val, 2)); // set des_cmpd_sel = 2
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    // 6. Prepare required settings for IBCAL
    if (viper_rev_a) {
        gp_iter = 11;
        VTSS_RC(vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state, phy_id.base_port_no, 8, ib_tsdet_cal, 0, 1, 1)); // ib_cfg1
    } else {
        gp_iter = 5;
        VTSS_RC(vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state, phy_id.base_port_no, 8, ib_tsdet_cal, 15, 1, 0)); // ib_cfg1
    }
    VTSS_RC(vtss_phy_sd6g_ib_cfg0_wr_private(vtss_state, phy_id.base_port_no, ib_rtrm_adj, ib_sig_det_clk_sel_cal, 0, 0)); // ib_cfg0
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    // 7. Start IB_CAL
    VTSS_D("Calibrating SD6G IB...");
    VTSS_RC(vtss_phy_sd6g_ib_cfg0_wr_private(vtss_state, phy_id.base_port_no, ib_rtrm_adj, ib_sig_det_clk_sel_cal, 0, 1)); // ib_cal_ena
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
    // 11 cycles (for ViperA) or 5 cycles (for ViperB & Elise) w/ SW clock
    for (iter = 0; iter < gp_iter; iter++) {
        VTSS_RC(vtss_phy_sd6g_gp_cfg_wr_private(vtss_state, phy_id.base_port_no, 769)); // set gp(0)
        VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
        VTSS_RC(vtss_phy_sd6g_gp_cfg_wr_private(vtss_state, phy_id.base_port_no, 768)); // clear gp(0)
        VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
    }
    // switch to auto. cal
    if (viper_rev_a) {
        VTSS_RC(vtss_phy_sd6g_ib_cfg0_wr_private(vtss_state, phy_id.base_port_no, ib_rtrm_adj, ib_sig_det_clk_sel_cal, 0, 0)); // ib_cal_ena
        // update value write sequence for bug 14320
        // first ib_cal_ena=0
        VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
        // then ib_frc_offset=0 and ib_scaly=15
        VTSS_RC(vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state, phy_id.base_port_no, 8, ib_tsdet_cal, 15, 0, 1)); // ib_cfg1
        VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
        // then ib_cal_ena=1
        VTSS_RC(vtss_phy_sd6g_ib_cfg0_wr_private(vtss_state, phy_id.base_port_no, ib_rtrm_adj, ib_sig_det_clk_sel_cal, 0, 1)); // ib_cal_ena
        VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
    } else {
        //ib_filt_offset=1
        VTSS_RC(vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state, phy_id.base_port_no, 8, ib_tsdet_cal, 15, 1, 1)); // ib_cfg1
        VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
        // then ib_frc_offset=0
        VTSS_RC(vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state, phy_id.base_port_no, 8, ib_tsdet_cal, 15, 0, 1)); // ib_cfg1
        VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB
    }
    // 8. Wait for IB cal to complete
    timeout = 200;
    do {
        VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // read 6G MCB into CSRs
        VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x2f, &rd_dat)); // ib_status0
        SD6G_TIMEOUT(timeout);
    } while (~rd_dat & 0x0000100); // wait for bit 8 to set

    // 9. Restore cfg values for mission mode
    VTSS_RC(vtss_phy_sd6g_ib_cfg0_wr_private(vtss_state, phy_id.base_port_no, ib_rtrm_adj, ib_sig_det_clk_sel_mm, 0, 1)); // ib_sig_det_clk_sel, ib_reg_pat_sel_offset
    VTSS_RC(vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state, phy_id.base_port_no, 8, ib_tsdet_mm, 15, 0, 1)); // ib_tsdet
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    // 10. Re-enable transmitter
    VTSS_RC(vtss_phy_sd6g_common_cfg_wr_private(vtss_state, phy_id.base_port_no, 1, 1, 0, qrate, if_mode, 0)); // pwd_tx=0
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    // 11. Disable frequency offset generation (using internal FoJi logic)
    VTSS_RC(vtss_phy_sd6g_dft_cfg2_wr_private(vtss_state, phy_id.base_port_no, 0, 0, 0, 0, 0, 0)); // rx_step_freq=0, rx_ji_ena=0, rx_freqoff_dir=0, rx_freqoff_ena=0
    VTSS_RC(vtss_phy_sd6g_dft_cfg0_wr_private(vtss_state, phy_id.base_port_no, 0, 0, 0)); // rd_dft_ena
    VTSS_RC(vtss_phy_sd6g_des_cfg_wr_private(vtss_state, phy_id.base_port_no, 6, 2, 5, des_bw_ana_val, 0)); // set des_cmpd_sel = 2
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    // Tune/Re-lock LCPLL
    VTSS_RC(tune_pll5g(vtss_state, port_no));

    // 12. Configure for Final Configuration and Settings
    VTSS_D("Configure for final settings...");
    //a. Reset RCPLL
    VTSS_RC(vtss_phy_sd6g_pll_cfg_wr_private(vtss_state, phy_id.base_port_no, 3, pll_fsm_ctrl_data, 0)); // pll_fsm_ena=0, reset rcpll
    VTSS_RC(vtss_phy_sd6g_common_cfg_wr_private(vtss_state, phy_id.base_port_no, 0, 1, 0, qrate, if_mode, 0)); // sys_rst=0, assert sys_rst
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    //b. Configure sd6g for desired operating mode
    VTSS_D("Setting 6G into final operating mode");
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    mac_if = (reg_val >> 14) & 0x3;

    if (mac_if ==  0x1) { // QSGMII
        pll_fsm_ctrl_data = 120;
        qrate   = 0;
        if_mode = 3;
        des_bw_ana_val = 5;
        VTSS_D("port_no %u, Config: VTSS_PORT_INTERFACE_QSGMII after sd6g_ib_cal", port_no);
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80E0, 0xFFFF, 0x0));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    } else if (mac_if ==  0x0) { // SGMII
        pll_fsm_ctrl_data = 60;
        qrate   = 1;
        if_mode = 1;
        des_bw_ana_val = 3;
        VTSS_D("port_no %u, Config: VTSS_PORT_INTERFACE_SGMII after sd6g_ib_cal", port_no);
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80F0, 0xFFFF, 0));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    } else {
        VTSS_D("VTSS_PORT_INTERFACE_RGMII or VTSS_PORT_INTERFACE_NO_CONNECTION:: port_no %u", port_no);
    }

    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x11, 0)); // read LCPLL MCB into CSRs
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // read 6G MCB into CSRs

    // update LCPLL bandgap voltage setting (bug 13887)
    VTSS_RC(vtss_phy_pll5g_cfg0_wr_private(vtss_state, phy_id.base_port_no, 4)); // pll5g_cfg0
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x11, 0)); // write back LCPLL MCB

    // update des_bw_ana for bug 14948
    VTSS_RC(vtss_phy_sd6g_des_cfg_wr_private(vtss_state, phy_id.base_port_no, 6, 2, 5, des_bw_ana_val, 0)); // des_cfg
    VTSS_RC(vtss_phy_sd6g_ib_cfg0_wr_private(vtss_state, phy_id.base_port_no, ib_rtrm_adj, ib_sig_det_clk_sel_mm, 0, 1)); // ib_cfg0
    VTSS_RC(vtss_phy_sd6g_ib_cfg1_wr_private(vtss_state, phy_id.base_port_no, 8, ib_tsdet_mm, 15, 0, 1)); // ib_cfg1
    VTSS_RC(vtss_phy_sd6g_common_cfg_wr_private(vtss_state, phy_id.base_port_no, 1, 1, 0, qrate, if_mode, 0)); // sys_rst=1

    // update ib_tcalv & ib_ureg for bug 14626
    VTSS_RC(vtss_phy_sd6g_ib_cfg2_wr_private(vtss_state, phy_id.base_port_no, 3, 13, 5)); // ib_cfg2
    VTSS_RC(vtss_phy_sd6g_ib_cfg3_wr_private(vtss_state, phy_id.base_port_no,  0, 31, 1, 31)); // ib_cfg3
    VTSS_RC(vtss_phy_sd6g_ib_cfg4_wr_private(vtss_state, phy_id.base_port_no, 63, 63, 2, 63)); // ib_cfg4

    VTSS_RC(vtss_phy_sd6g_misc_cfg_wr_private(vtss_state, phy_id.base_port_no, 1)); // assert lane reset
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    //2. Start rcpll_fsm
    VTSS_D("Final RCPLL Calibration ...");
    VTSS_RC(vtss_phy_sd6g_pll_cfg_wr_private(vtss_state, phy_id.base_port_no, 3, pll_fsm_ctrl_data, 1)); // pll_fsm_ena
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    //3. Wait for PLL cal to complete
    timeout = 200;
    do {
        VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // read 6G MCB into CSRs
        VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x31, &rd_dat)); // pll_status
        SD6G_TIMEOUT(timeout);
    } while (rd_dat & 0x0001000); // wait for bit 12 to clear

    VTSS_RC(vtss_phy_sd6g_misc_cfg_wr_private(vtss_state, phy_id.base_port_no, 0)); // release lane reset
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // write back 6G MCB

    VTSS_D("vtss_phy_sd6g_patch_private: Port: %d  sd6g patch Complete", port_no);

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_SERDES_MACRO_SETTINGS */

//=============================================================================
//=============================================================================
//
// Phy Smart premphasis
//
static vtss_rc vtss_phy_enab_smrt_premphasis (vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200)); //Ensure RClk125 enabled even in powerdown

    switch (ps->family) {
    case VTSS_PHY_FAMILY_COBRA:  /* COBRA has different TR Reg Access */
        /* BZ 2675 */
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xa7fa));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000, 0x0000));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0008, 0x0008));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x87fa));
        break;

    case VTSS_PHY_FAMILY_QUATTRO:
    case VTSS_PHY_FAMILY_SPYDER:
    case VTSS_PHY_FAMILY_COOPER:
    case VTSS_PHY_FAMILY_LUTON:
    case VTSS_PHY_FAMILY_LUTON_E:
    case VTSS_PHY_FAMILY_LUTON24:
    default:
        /* BZ 2675 */
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa7fa));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000, 0x0000));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0008, 0x0008));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));
        break;
    }

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200)); //Restore RClk125 gating
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return VTSS_RC_OK;
}

void vga_adc_debug(const vtss_inst_t inst, u8 vga_adc_pwr, vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;

    // vga_adc_pwr: allows VGA and/or ADC to power down for EEE
    // 00: power down neither
    // 01: power down ADCs only
    // 10: power down VGAs only
    // 11: power down both

    if (vtss_inst_check(inst, &vtss_state) != VTSS_RC_OK) {
        return;
    }

    // turn off micro VGA patch temporarily to allow token-ring access
    (void) vtss_phy_page_gpio(vtss_state, port_no); // switch to micro page (glabal to all 12 PHYs)
    (void) PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9024);

    (void) vtss_phy_page_tr(vtss_state, port_no);   // Switch to token-ring register page
    (void) PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0001);
    (void) PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x40b9 | (vga_adc_pwr << 1));
    (void) PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fda);   // for 100
    (void) PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000);
    (void) PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0159 | (vga_adc_pwr << 1));
    (void) PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fd6);   // for 1000

    // turn micro VGA patch back on to allow correct PHY start-up
    (void) vtss_phy_page_gpio(vtss_state, port_no); // switch to micro page (glabal to all 12 PHYs)
    (void) PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9004);
    (void) vtss_phy_page_std(vtss_state, port_no);
}

// Function for testing phy features
BOOL vtss_phy_can(vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_phy_feature_t feature)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    VTSS_N("port_no:%d ps->features:0x%X 0x%X", port_no, ps->features, feature);
    return !!(ps->features & feature);
}

#if defined(VTSS_FEATURE_EEE)
// Function for setting EEE (Energy Efficient Ethernet)
//
// In: port_no      - The PHY port number starting from 0.
//     enable_conf  - 0=Update EEE state to disabled, 1=Update EEE state to enabled, 2=Update EEE register with current state.
//
// Return: VTSS_RC_OK if configuration went well - else error code
static vtss_rc vtss_phy_eee_ena_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc rc = VTSS_RC_OK;
    BOOL reconfigure = FALSE; // Default don't update registers.

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
        if (ps->type.revision == VTSS_PHY_ATOM_REV_B) {
            if (vtss_state->phy_state[port_no].eee_conf.eee_mode == EEE_ENABLE) {
                VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, FALSE)); // Make sure that 8051 patch is running
            } else if (vtss_state->phy_state[port_no].eee_conf.eee_mode == EEE_DISABLE) {
                VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, TRUE)); // Suspend 8051 Patch.
            }
        }
        /* fall-through */
    // Pass through
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO:
        // Called
        if (vtss_state->phy_state[port_no].eee_conf.eee_mode == EEE_REG_UPDATE) {
            // Called with re-configure registers but don't change state
            if (!vtss_state->sync_calling_private) {
                reconfigure = TRUE;
            }
            ps->eee_conf.eee_mode = ps->eee_conf.eee_ena_phy ? EEE_ENABLE : EEE_DISABLE;
        } else if (ps->eee_conf.eee_ena_phy && vtss_state->phy_state[port_no].eee_conf.eee_mode == EEE_DISABLE) {
            //current state is Enabled, New state is disable. Re-configure registers and change state.
            ps->eee_conf.eee_ena_phy = FALSE;
            reconfigure = TRUE;
        } else if (!ps->eee_conf.eee_ena_phy && vtss_state->phy_state[port_no].eee_conf.eee_mode == EEE_ENABLE) {
            //Current state is Disable, New state is Enable. Re-configure registers and change state.
            ps->eee_conf.eee_ena_phy = TRUE;
            reconfigure = TRUE;
        }


        // re-configure registers
        if (reconfigure) {
            VTSS_D("New EEE Enable = %d, port = %d", vtss_state->phy_state[port_no].eee_conf.eee_mode, port_no);
            // Enable/Disable all EEE
            if (ps->eee_conf.eee_ena_phy) {
                VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EEE_CONTROL,
                                                VTSS_F_PHY_EEE_CONTROL_ENABLE_10BASE_TE,
                                                VTSS_F_PHY_EEE_CONTROL_ENABLE_10BASE_TE)); // Enable EEE (EEE control, Adress 17E2, bit 15)
#ifdef VTSS_PHY_OPT_CAP_FE_ONLY // Fast Ethernet - Advertise EEE Capable for 100BaseT Only
                VTSS_D("EEE Enabled: 100BaseT Advertisements only for Port = %d", port_no);
                VTSS_RC(vtss_phy_mmd_reg_wr_masked(vtss_state, port_no, 7, 60, 2, 0x0006)); // Enable 100BaseT advertisement Only
#elif defined VTSS_PHY_OPT_CAP_GE_ONLY // GigaBit Ethernet - Advertise EEE Capable for 1000BaseT Only
                VTSS_D("EEE Enabled: 1000BaseT Advertisements only for Port = %d", port_no);
                VTSS_RC(vtss_phy_mmd_reg_wr_masked(vtss_state, port_no, 7, 60, 4, 0x0006)); // Enable 1000BaseT advertisement Only
#else  // Default Config - ANEG the Speed, 100/1G Ethernet - Advertise EEE Capable for both 100/1000 BaseT
                VTSS_D("EEE Enabled: 100/1000BaseT Advertisements for Port = %d", port_no);
                VTSS_RC(vtss_phy_mmd_reg_wr_masked(vtss_state, port_no, 7, 60, 6, 0x0006)); // Enable 100BaseT and 1000BaseT advertisement
#endif

                VTSS_RC(vtss_phy_page_test(vtss_state, port_no));                      // Switch to test-register page
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_TEST_PAGE_25, 0, 1));                 // Clear EEE bit (bit 0)
            } else {
                VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EEE_CONTROL, 0x0, VTSS_F_PHY_EEE_CONTROL_ENABLE_10BASE_TE));  // Disable EEE (EEE control, Adress 17E2, bit 15)
                VTSS_RC(vtss_phy_mmd_reg_wr_masked(vtss_state, port_no, 7, 60, 0, 0x0006));    // Disable advertisement
            }

            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));   // Go back to standard page.
            VTSS_N("restart auto neg - Needed for disable/enable EEE advertisement, port = %d", port_no);

            // Only re-start auto-neg if in auto neg mode (Primary due to Bugzilla#7343,
            // which is also the reason to setting the AUTO_NED_ENA bit)
            if (ps->setup.mode == VTSS_PHY_MODE_ANEG) {
                if (!vtss_state->sync_calling_private) {// Don't Reset under warm start, even if something has changed.
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                                    VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG,
                                                    VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG)); // Restart Auto-negotiation
                } else {
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                                    VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA,
                                                    VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA)); // During warm start only enable Auto-negotiation

                }
                VTSS_D("Autoneg, port:%d", port_no);
            }
        }
        break;

    default:
        VTSS_D("EEE not support for family:%s, port = %d",
               vtss_phy_family2txt(ps->family), port_no);
        rc = VTSS_RC_OK;
    }

    return rc;
}

// Function for returning link partners EEE advertisement.
// In: port_no - The PHY port number starting from 0.
// Out: Advertisement bit mask.
//      Bit 0 = Link partner advertises 100BASE-T capability.
//      Bit 1 = Link partner advertises 1000BASE-T capability.
static vtss_rc vtss_phy_eee_link_partner_advertisements_get_private(
    vtss_state_t *vtss_state,
    const vtss_port_no_t        port_no,
    u8  *advertisements)
{

    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc rc = VTSS_RC_OK;
    u16 reg_val;

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO:
        VTSS_RC(vtss_phy_mmd_rd(vtss_state, port_no, 7, 61, &reg_val)); // Get the link partner advertisement.
        *advertisements = reg_val >> 1; // Bit 0 is reserved. See data sheet.
        break;

    default:
        *advertisements = 0;
        VTSS_D("EEE not support for family:%s",
               vtss_phy_family2txt(ps->family));
        rc = VTSS_RC_OK;
    }
    return rc;

}

// Function for returning if phy is currently powered save mode due to EEE
// In: port_no - The PHY port number starting from 0.
// Out: rx_in_power_save_state - TRUE if rx part of the PHY is in power save mode
//      tx_in_power_save_state - TRUE if tx part of the PHY is in power save mode
static vtss_rc vtss_phy_eee_power_save_state_get_private(
    vtss_state_t *vtss_state,
    const vtss_port_no_t        port_no,
    BOOL  *rx_in_power_save_state,
    BOOL  *tx_in_power_save_state)
{

    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc rc = VTSS_RC_OK;
    u16 reg_val;

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO:
        VTSS_RC(vtss_phy_mmd_rd(vtss_state, port_no, 3, 1, &reg_val)); // Get PCS status

        // Bit 8 is RX LPI. See data sheet.
        if (reg_val & 0x0100) {
            *rx_in_power_save_state = TRUE;
        } else {
            *rx_in_power_save_state = FALSE;
        }

        // Bit 9 is TX LPI. See data sheet.
        if (reg_val & 0x0200) {
            *tx_in_power_save_state = TRUE;
        } else {
            *tx_in_power_save_state = FALSE;
        }

        VTSS_N("PCS Status:0x%X, port:%d, rx_in_power_save_state:%d, tx_in_power_save_state:%d",
               reg_val, port_no, *rx_in_power_save_state, *tx_in_power_save_state);
        break;

    default:
        *rx_in_power_save_state = FALSE;
        *tx_in_power_save_state = FALSE;
        VTSS_D("EEE not support for family:%s",
               vtss_phy_family2txt(ps->family));
        rc = VTSS_RC_OK;
    }
    return rc;
}

#endif // end defined(VTSS_FEATURE_EEE)



/************************************************************************/
/* COBRA family functions                                               */
/************************************************************************/

// Setup MAC and Media interface
//
// In : port_no - port starting from 0.
//      conf    - Configuration for the port
static vtss_rc vtss_phy_mac_media_if_cobra_setup(vtss_state_t *vtss_state,
                                                 const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    u16 reg = 0;
    u16 mac_media_mode_sel_15_12 = 0x0; // Mac/Media interface mode selct bits 15:12 - Datasheet table 36
    u16 mac_media_mode_sel_2_1 = 0x0;   // Mac/Media interface mode selct bits 2:1 - Datasheet table 36


    switch (conf->mac_if) {

    case VTSS_PORT_INTERFACE_SGMII:
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            mac_media_mode_sel_15_12 = 0xB;
            mac_media_mode_sel_2_1   = 0x0;
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
        case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
            mac_media_mode_sel_15_12 = 0x9;
            mac_media_mode_sel_2_1   = 0x1;
            break;
        default:
            goto conf_error;
        }
        break;


    case VTSS_PORT_INTERFACE_RGMII:
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            mac_media_mode_sel_15_12 = 0x1;
            mac_media_mode_sel_2_1   = 0x2;
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
        case VTSS_PHY_MEDIA_IF_FI_100FX:
            mac_media_mode_sel_15_12 = 0x1;
            mac_media_mode_sel_2_1   = 0x1;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
        case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
            mac_media_mode_sel_15_12 = 0x0;
            mac_media_mode_sel_2_1   = 0x2;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
        case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
            mac_media_mode_sel_15_12 = 0x0;
            mac_media_mode_sel_2_1   = 0x1;
            break;
        default:
            goto conf_error;
        }
        break;

    case VTSS_PORT_INTERFACE_RTBI:
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            mac_media_mode_sel_15_12 = 0x4;
            mac_media_mode_sel_2_1   = 0x0;
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
        case VTSS_PHY_MEDIA_IF_FI_100FX:
            mac_media_mode_sel_15_12 = 0x5;
            mac_media_mode_sel_2_1   = 0x1;
            break;
        default:
            goto conf_error;
        }
        break;


    case VTSS_PORT_INTERFACE_TBI:
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            mac_media_mode_sel_15_12 = 0x6;
            mac_media_mode_sel_2_1   = 0x0;
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
        case VTSS_PHY_MEDIA_IF_FI_100FX:
            mac_media_mode_sel_15_12 = 0x7;
            mac_media_mode_sel_2_1   = 0x1;
            break;
        default:
            goto conf_error;
        }
        break;



    case VTSS_PORT_INTERFACE_GMII:
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            mac_media_mode_sel_15_12 = 0x3;
            mac_media_mode_sel_2_1   = 0x2;
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
        case VTSS_PHY_MEDIA_IF_FI_100FX:
            mac_media_mode_sel_15_12 = 0x3;
            mac_media_mode_sel_2_1   = 0x1;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
        case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
            mac_media_mode_sel_15_12 = 0x2;
            mac_media_mode_sel_2_1   = 0x2;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
        case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
            mac_media_mode_sel_15_12 = 0x2;
            mac_media_mode_sel_2_1   = 0x1;
            break;
        default:
            goto conf_error;
        }
        break;

    case VTSS_PORT_INTERFACE_SERDES:
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            mac_media_mode_sel_15_12 = 0xF;
            mac_media_mode_sel_2_1   = 0x0;
            break;
        case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
        case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
            mac_media_mode_sel_15_12 = 0x9;
            mac_media_mode_sel_2_1   = 0x1;
            break;
        default:
            goto conf_error;
        }
        break;
    default:
        goto conf_error;
    }


    // Do the register (address 0x23)  write
    reg = 0x0a20; // Setup skew and RX idle clock, datasheet table 36.
    reg |= mac_media_mode_sel_15_12 << 12;
    reg |= mac_media_mode_sel_2_1 << 1;

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, reg));
    return VTSS_RC_OK;


// Configuration error.
conf_error:
    VTSS_E("Cobra family, Port %u, Media interface:%s not supported for mac if:%s",
           port_no, vtss_phy_media_if2txt(conf->media_if),
           vtss_port_if_txt(conf->mac_if));
    return VTSS_RC_ERROR;
}

/* Init Scripts for VSC8211/VSC8221 aka Cobra */
static vtss_rc vtss_phy_init_seq_cobra(vtss_state_t *vtss_state,
                                       vtss_phy_port_state_t *ps,
                                       vtss_port_no_t        port_no)
{
    /* Enable token-ring register access for entire init script */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));

    /* BZ 1769 */
    /* Performance robustness improvement on 50m loops */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xafa4));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000, 0x0000));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x4000, 0xf000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8fa4));

    /* BZ 2337 */
    /* Inter-operability with Intel 82547E1 L322SQ96 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xafae));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000, 0x0000));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0600, 0x7f80));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8fae));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0040, 0x0040));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));

    /* BZ 1800 */
    /* 100BT Jumbo packet mode script */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xb786));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000, 0x0000));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0e20, 0x1fe0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x9786));

    /* BZ 2331 */
    /* Insufficient RGMII drive strength on long traces */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_3, 0x2000, 0x2000));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_3, 0x1080, 0x1ff8));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));

    /* BZ 2232 */
    /* DSP Optimization script */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xaf8a));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000, 0x0000));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0008, 0x000c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8f8a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xaf86));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0008, 0x000c));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0000, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8f86));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xaf82));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000, 0x0000));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0100, 0x0180));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8f82));

    /* New bugzilla 11377 */
    /* Forced-10BASE-T PHY falsely linking up with forced-100BASE-TX link partner */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xa7f4));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000, 0x0000));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0002, 0x0006));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x87f4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0xa7f8));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000, 0x0000));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0800, 0x0800));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x87f8));

    /* Restore normal clock gating and return to main page after init script */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    /* Enable Smart Pre-emphasis */
    VTSS_RC(vtss_phy_enab_smrt_premphasis(vtss_state, port_no));

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
/************************************************************************/
/* Atom family functions                                                */
/************************************************************************/
// Function that returns if the conf id configured as fiber port
// Return - TRUE - conf is configured as fiber port else return FALSE
static BOOL is_fiber_port(const vtss_phy_reset_conf_t *const conf)
{
    switch (conf->media_if) {
    case VTSS_PHY_MEDIA_IF_FI_100FX:
    case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
    case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
    case VTSS_PHY_MEDIA_IF_FI_1000BX:
    case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
    case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
    case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
        return TRUE;
    default:
        return FALSE;
    }
    return FALSE;
}


// function cfg_ib(port_no, ib_cterm_ena, ib_eq_mode);
//   set the ib_cterm_ena and ib_eq_mode bits to the input values (0 or 1)
//   ib_cterm_ena => cfg_vec[91] => cfg_buf[11].3
//   ib_eq_mode    => cfg_vec[90] => cfg_buf[11].2
//
//   ib_rst       => cfg_vec[86] => cfg_buf[10].6
//
static vtss_rc vtss_phy_atom12_cfg_ib_cterm_ena_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 ib_cterm_ena, u8 ib_eq_mode)
{
    u8 tmp, tmp1;
    u16 reg18g = 0;
    vtss_rc rc = VTSS_RC_OK;

    VTSS_I("ib_eq_mode:%d, ib_cterm_ena:%d", ib_eq_mode, ib_cterm_ena);

    // fetch MCB data
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8113));     // Read MCB for 6G macro 1 into PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Assert ib_rst
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d9));     // set mem_addr to cfg_buf[10] (0x47d9)
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));     // read the value of cfg_buf[10] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    // get bits 11:4 from return value and OR in ib_rst (bit 6)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
    tmp1 = (u8)(((reg18g >> 4) & 0xff) | 0x40);

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9006 | (tmp1 << 4)));    // write the value back to cfg_buf[10] w/ post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // update ib_cterm_ena and ib_eq_mode
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));     // read the value of cfg_buf[11] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    // get bits 11:4 from return value and mask off bits 2 & 3
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
    tmp = (u8)((reg18g >> 4) & 0xf3);
    // OR in ib_cterm_ena shifted by 3 bits
    tmp |= ((ib_cterm_ena & 1) << 3);
    // OR in ib_eq_mode shifted by 2 bits
    tmp |= ((ib_eq_mode & 1) << 2);

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | (tmp << 4)));    // write the value back to cfg_buf[11] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Update MCB w/ ib_rst asserted
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7ce));     // set mem_addr to 0x47ce (addr_vec)
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80e6));     // set addr_vec for macros 1-3
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9cc0));     // Write MCB for 6G macros 1-3 from PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Clear ib_rst
    // mask off ib_rst (bit 6)
    tmp1 &= 0xbf;

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d9));     // set mem_addr to cfg_buf[10] (0x47d9)
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | (tmp1 << 4)));    // write the value back to cfg_buf[10] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Update MCB w/ ib_rst cleared
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9cc0));     // Write MCB for 6G macros 1-3 from PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    return rc;
}

// function cfg_ib(port_no, ib_cterm_ena, ib_eq_mode);
//   set the ib_cterm_ena and ib_eq_mode bits to the input values (0 or 1)
//   ib_cterm_ena => cfg_vec[91] => cfg_buf[11].3
//   ib_eq_mode    => cfg_vec[90] => cfg_buf[11].2
//
//   ib_rst       => cfg_vec[86] => cfg_buf[10].6
//
static vtss_rc vtss_phy_tesla_cfg_ib_cterm_ena_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 ib_cterm_ena, u8 ib_eq_mode)
{
    u8 tmp, tmp1;
    u16 reg18g = 0;
    vtss_rc rc = VTSS_RC_OK;

    VTSS_I("ib_eq_mode:%d, ib_cterm_ena:%d", ib_eq_mode, ib_cterm_ena);

    // fetch MCB data
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8013));     // Read MCB for 6G macro 0 into PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Assert ib_rst
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d1));     // set mem_addr to cfg_buf[10] (0x47d1)
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));     // read the value of cfg_buf[10] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    // get bits 11:4 from return value and OR in ib_rst (bit 6)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
    tmp1 = (u8)(((reg18g >> 4) & 0xff) | 0x40);

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9006 | (tmp1 << 4)));    // write the value back to cfg_buf[10] w/ post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // update ib_cterm_ena and ib_eq_mode
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));     // read the value of cfg_buf[11] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    // get bits 11:4 from return value and mask off bits 2 & 3
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
    tmp = (u8)((reg18g >> 4) & 0xf3);
    // OR in ib_cterm_ena shifted by 3 bits
    tmp |= ((ib_cterm_ena & 1) << 3);
    // OR in ib_eq_mode shifted by 2 bits
    tmp |= ((ib_eq_mode & 1) << 2);

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | (tmp << 4)));    // write the value back to cfg_buf[11] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Update MCB w/ ib_rst asserted
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9c40));     // Write MCB for 6G macro 0 from PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Clear ib_rst
    // mask off ib_rst (bit 6)
    tmp1 &= 0xbf;

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d1));     // set mem_addr to cfg_buf[10] (0x47d1)
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | (tmp1 << 4)));    // write the value back to cfg_buf[10] w/o post-incr.
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Update MCB w/ ib_rst cleared
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9c40));     // Write MCB for 6G macro 0 from PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    return rc;
}

// Function call the ib_cterm configuration for the current chipset
static vtss_rc vtss_phy_cfg_ib_cterm_ena_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 ib_cterm_ena, u8 ib_eq_mode)
{
    switch (vtss_state->phy_state[port_no].family) {
    case VTSS_PHY_FAMILY_ATOM:
        VTSS_RC(vtss_phy_atom12_cfg_ib_cterm_ena_private(vtss_state, port_no, ib_cterm_ena, ib_eq_mode));
        break;

    case VTSS_PHY_FAMILY_TESLA:
        VTSS_RC(vtss_phy_tesla_cfg_ib_cterm_ena_private(vtss_state, port_no, ib_cterm_ena, ib_eq_mode));
        break;

    default :
        VTSS_I("No cterm configuration for %s family", vtss_phy_family2txt(vtss_state->phy_state[port_no].family));
    }
    return VTSS_RC_OK;
}

/**
 * \brief Debug function for getting the size of the micro patch CFG buffer size.
 *
 * \param vtss_state [IN] The current instance state.
 * \param port_no    [IN] Internal port number.
 *
 * \return Return size of cfg buffer;
 **/

// See vtss_phy_api.h
u8 vtss_phy_cfg_buf_size(vtss_state_t *vtss_state,
                         const vtss_port_no_t    port_no)
{

    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    // MAX_CFG_BUF_SIZE is 36 for Atom12 and 38 for Tesla, so array sized for larger of the two
    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM :
        return (MAX_CFG_BUF_SIZE - 2);
    case VTSS_PHY_FAMILY_TESLA:
        return (MAX_CFG_BUF_SIZE);
    default:
        return 0;
    }
}

/**
 * \brief Debug function for getting the size of the micro patch STATUS buffer size.
 *
 * \param vtss_state [IN] The current instance state.
 * \param port_no    [IN] Internal port number.
 *
 * \return Return size of cfg buffer;
 **/
// See vtss_phy_api.h
u8 vtss_phy_status_buf_size(vtss_state_t *vtss_state,
                            const vtss_port_no_t    port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    // MAX_STAT_BUF_SIZE is 8 for Atom12 and 6 for Tesla, so array sized for larger of the two
    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM :
        return (MAX_STAT_BUF_SIZE);
    case VTSS_PHY_FAMILY_TESLA:
        return (MAX_STAT_BUF_SIZE - 2);
    default:
        return 0;
    }
}

// Function for getting the PHY settings set by the micro patch.
// In - port_no - Phy port number.
// Out - cfg_buf  - Array containing the configuration setting
//       stat_buf - Array containing the status
static vtss_rc vtss_phy_atom12_patch_setttings_get_private(vtss_state_t *vtss_state,
                                                           vtss_port_no_t port_no, u8 *mcb_bus, u8 *cfg_buf, u8 *stat_buf)
{
    u16 idx;
    u16 reg18g;
    u8 slave_num = 0;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *conf = &ps->reset;

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
        // set mem_addr to cfg_buf (0xd7cf for Atom12)
        //mem_addr = 0xd7cf;

        // assume MCB bus is passed in as mcb_bus
        //    it is passed to 8051 in bits 7:4
        //    0: SerDes 1G
        //    1: SerDes 6G
        //    2: LCPLL/RComp

        //    it is passed to 8051 in bits 12:8
        //    for 1G the range is 0-7 (see port to MCB mappings in TN1085)
        //    for GG the range is 0-3 (see port to MCB mappings in TN1085)
        //    for LCPLL/RComp (only one) the value is always 0
        if (*mcb_bus == 2) {
            slave_num = 0;
        } else if (is_fiber_port(conf)) {
            // for fiber media port mappings:
            *mcb_bus = 0;  // only 1G macros used for fiber media

            // 6G macro 0 not used in QSGMII mode
            switch (port_no % ps->type.port_cnt) {
            case 8  :    // 1G macro 7
                slave_num = 7;
                break;
            case 9  :    // 1G macro 6
                slave_num = 6;
                break;
            case 10 :    // 1G macro 5
                slave_num = 5;
                break;
            case 11 :    // 1G macro 4
                slave_num = 4;
                break;
            default :
                VTSS_E("Invalid port number:%d", port_no);
            }
        } else if (conf->mac_if ==  VTSS_PORT_INTERFACE_QSGMII) {  // QSGMII mapping (these are one macro per quad)
            *mcb_bus = 1;  // only 6G macros used for QSGMII MACs
            switch (port_no % ps->type.port_cnt) {
            // 6G macro 0 not used in QSGMII mode
            case 0 :    // 6G macro 1
            case 1 :
            case 2 :
            case 3 :
                slave_num = 1;
                break;
            case 4 :    // 6G macro 2
            case 5 :
            case 6 :
            case 7 :
                slave_num = 2;
                break;
            case 8  :    // 6G macro 3
            case 9  :
            case 10 :
            case 11 :
                slave_num = 3;
                break;
            default :
                VTSS_E("Invalid port:%d", port_no);;
            }
        } else { // SGMII
            switch (port_no % ps->type.port_cnt) {
            // all 6G and 1G macros used for MACs in this mode
            case 0 :    // 6G macro 0
                *mcb_bus = 1;
                slave_num = 0;
                break;
            case 1 :    // 1G macro 0
                *mcb_bus = 0;
                slave_num = 0;
                break;
            case 2 :    // 1G macro 1
                *mcb_bus = 0;
                slave_num = 1;
                break;
            case 3 :    // 6G macro 1
                *mcb_bus = 1;
                slave_num = 1;
                break;
            case 4 :    // 1G macro 2
                *mcb_bus = 0;
                slave_num = 2;
                break;
            case 5 :    // 1G macro 3
                *mcb_bus = 0;
                slave_num = 3;
                break;
            case 6 :    // 6G macro 2
                *mcb_bus = 1;
                slave_num = 2;
                break;
            case 7 :    // 1G macro 4
                *mcb_bus = 0;
                slave_num = 4;
                break;
            case 8  :    // 1G macro 5
                *mcb_bus = 0;
                slave_num = 5;
                break;
            case 9  :    // 6G macro 3
                *mcb_bus = 1;
                slave_num = 3;
                break;
            case 10 :    // 1G macro 6
                *mcb_bus = 0;
                slave_num = 6;
                break;
            case 11 :    // 1G macro 7
                *mcb_bus = 0;
                slave_num = 7;
                break;
            default :
                VTSS_E("Invalid port:%d", port_no);  // some sort of error handling should go here
            }
        }
        break;

    default:
        VTSS_E("atom12_patch_setttings_get not supported for family:%s", vtss_phy_family2txt(ps->family));
        return VTSS_RC_ERROR;
    }


    // fetch MCB data
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8003 | (slave_num << 8) | (*mcb_bus << 4)));     // Read MCB macro into PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7cf));     // set mem_addr to cfg_buf (0x47cf)
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // read out cfg_buf
    for (idx = 0; idx < vtss_phy_cfg_buf_size(vtss_state, port_no); idx++) {  // MAX_CFG_BUF_SIZE is 36 for Atom12 and 38 for Tesla
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));                     // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9007));     // read the value of cfg_buf[idx] w/ post-incr.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
        // get bits 11:4 from return value
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        cfg_buf[idx] = (u8)((reg18g >> 4) & 0xff);
    }

    // read out stat_buf (starts where cfg_buf leaves off)
    for (idx = 0; idx < vtss_phy_status_buf_size(vtss_state, port_no); idx++) {  // MAX_CFG_STATUS_SIZE is 8 for Atom12 and 6 for Tesla
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));                        // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9007));     // read the value of stat_buf[idx] w/ post-incr.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
        // get bits 11:4 from return value
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        stat_buf[idx] = (u8)((reg18g >> 4) & 0xff);
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

// Function for getting the PHY settings set by the micro patch.
// In - port_no - Phy port number.
// Out - cfg_buf  - Array containing the configuration setting
//       stat_buf - Array containing the status
static vtss_rc vtss_phy_tesla_patch_setttings_get_private(vtss_state_t *vtss_state,
                                                          vtss_port_no_t port_no, u8 *mcb_bus, u8 *cfg_buf, u8 *stat_buf)
{
    u16 idx;
    u16 reg18g;
    u8 slave_num = 0;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *conf = &ps->reset;
    vtss_port_no_t         chip_port_no;

    if (ps->family != VTSS_PHY_FAMILY_TESLA) {
        VTSS_I("Port_no: %d;   Not a Tesla PHY - Returning", port_no);
        return (VTSS_RC_OK);
    }

    chip_port_no = vtss_phy_chip_port(vtss_state, port_no);

    switch (ps->family) {

    case VTSS_PHY_FAMILY_TESLA :
        // set mem_addr to cfg_buf (0xd7c7 for Tesla)
        //mem_addr = 0xD7c7;

        // assume MCB bus is passed in as mcb_bus
        //    it is passed to 8051 in bits 7:4
        //    0: SerDes 1G
        //    1: SerDes 6G
        //    2: LCPLL/RComp

        //    it is passed to 8051 in bits 12:8
        //    for 1G the range is 0-7 (see port to MCB mappings in TN1121)
        //    for GG the range is 0-3 (see port to MCB mappings in TN1121)
        //    for LCPLL/RComp (only one) the value is always 0
        if (*mcb_bus == 2) {
            slave_num = 0;
        } else if (is_fiber_port(conf)) {
            // for fiber media port mappings:
            *mcb_bus = 0;  // only 1G macros used for fiber media

            // 6G macro 0 not used in QSGMII mode
            switch (chip_port_no) {
            case 0  :    // 1G macro 0
                slave_num = 0;
                *mcb_bus = 1;
                break;
            case 1  :    // 1G macro 2
                slave_num = 2;
                break;
            case 2 :     // 1G macro 4
                slave_num = 4;
                break;
            case 3 :     // 1G macro 6
                slave_num = 6;
                break;
            default :
                VTSS_E("Invalid port number:%d", port_no);
            }
        } else if (conf->mac_if ==  VTSS_PORT_INTERFACE_QSGMII) {  // QSGMII mapping (these are one macro per quad)
            *mcb_bus = 1;  // only 6G macros used for QSGMII MACs
            switch (chip_port_no) {
            // 6G macro 0 not used in QSGMII mode
            case 0 :    // 6G macro 0
            case 1 :
            case 2 :
            case 3 :
                slave_num = 0;
                break;
            default :
                VTSS_E("Invalid port:%d", port_no);;
            }
        } else { // SGMII
            switch (chip_port_no) {
            // all 6G and 1G macros used for MACs in this mode
            case 0 :    // 6G macro 0
                *mcb_bus = 1;
                slave_num = 0;
                break;
            case 1 :    // 1G macro 1
                *mcb_bus = 0;
                slave_num = 1;
                break;
            case 2 :    // 1G macro 3
                *mcb_bus = 0;
                slave_num = 3;
                break;
            case 3 :    // 1G macro 5
                *mcb_bus = 0;
                slave_num = 5;
                break;
            default :
                VTSS_E("Invalid port:%d", port_no);  // some sort of error handling should go here
            }
        }
        break;
    default:
        VTSS_I("Patch setting get not supported for family:%s", vtss_phy_family2txt(ps->family));
        return VTSS_RC_ERR_PHY_PATCH_SETTING_NOT_SUPPORTED;
    }

    VTSS_I("tesla_patch_setttings_get:%s;  port_no: %d; chip_port: %d, mcb_bus: 0x%x,  slave_num: 0x%x \n", vtss_phy_family2txt(ps->family), port_no, chip_port_no, *mcb_bus, slave_num);


    // fetch MCB data
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8003 | (slave_num << 8) | (*mcb_bus << 4)));     // Read MCB macro into PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7c7));
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // read out cfg_buf
    for (idx = 0; idx < vtss_phy_cfg_buf_size(vtss_state, port_no); idx++) {  // MAX_CFG_BUF_SIZE is 36 for Atom12 and 38 for Tesla
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9007));     // read the value of cfg_buf[idx] w/ post-incr.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
        // get bits 11:4 from return value
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        cfg_buf[idx] = (u8)((reg18g >> 4) & 0xff);
    }

    // read out stat_buf (starts where cfg_buf leaves off)
    for (idx = 0; idx < vtss_phy_status_buf_size(vtss_state, port_no); idx++) {  // MAX_CFG_STATUS_SIZE is 8 for Atom12 and 6 for Tesla
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9007));     // read the value of stat_buf[idx] w/ post-incr.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
        // get bits 11:4 from return value
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        stat_buf[idx] = (u8)((reg18g >> 4) & 0xff);
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

// Function call the patch setting get configuration for the current chipset
static vtss_rc vtss_phy_patch_setttings_get_private(vtss_state_t *vtss_state,
                                                    vtss_port_no_t port_no, u8 *mcb_bus, u8 *cfg_buf, u8 *stat_buf)
{

    switch (vtss_state->phy_state[port_no].family) {
    case VTSS_PHY_FAMILY_ATOM:
        VTSS_RC(vtss_phy_atom12_patch_setttings_get_private(vtss_state, port_no, mcb_bus, cfg_buf, stat_buf));
        break;

    case VTSS_PHY_FAMILY_TESLA:
        VTSS_RC(vtss_phy_tesla_patch_setttings_get_private(vtss_state, port_no, mcb_bus, cfg_buf, stat_buf));
        break;

    default :
        VTSS_D("No cterm configuration for %s family", vtss_phy_family2txt(vtss_state->phy_state[port_no].family));
    }
    return VTSS_RC_OK;
}


// Function for finding a specific bit(s) in the phy patch configuration/status array.
// IN : msb    - MSB bit in array.
//      lsb    - LSB bit in array - If only one bit the LSB shall be set to -1
//      vec    - Pointer the setting/status patch array
static u8 patch_array_value_decode(i16 msb, i16 lsb, u8 *vec)
{
    u16 bit_idx;
    u8 value = 0;

    VTSS_D("Patch_Array_Decode msb:%d;   lsb: %d", msb, lsb);

    if (lsb > 0) {
        for (bit_idx = lsb; bit_idx <= msb; bit_idx++) {
            value += VTSS_BF_GET(vec, bit_idx) << (bit_idx - lsb);
            VTSS_D("Patch_Array_Decode bit_idx:%d;   value = 0x%x", bit_idx, value);
        }
    } else {
        value += VTSS_BF_GET(vec, msb);
        VTSS_D("Patch_Array_Decode msb:%d;   value = 0x%x", msb, value);
    }
    return value;
}

/*- **************************************************************************************** */
/*- vtss_phy_chk_serdes_init_mac_mode_private()                                              */
/*- Description: Determine if the 6G Macros have already been Initialized                    */
/*-              This determines if the 0x80E0 for QSGMII or                                 */
/*-              or 0x80F0 for SGMII have been written to VTSS_PHY_MICRO_PAGE                */
/*-              This DOES NOT indicate if the 6G micro-patch has been applied               */
/*-                                                                                          */
/*- For the 6G and 1G macros, the following bits will be strong indicators that the          */
/*- macro has been configured by the software:                                               */
/*- sys_rst      1                                                                           */
/*- ena_lane     1                                                                           */
/*- pll_fsm_ena  1                                                                           */
/*-                                                                                          */
/*- To tell if the 6G macro has been configured for QSGMII or SGMII operation                */
/*- (should correspond with 19G.14):                                                         */
/*-                                                                                          */
/*-          QSGMII  SGMII                                                                   */
/*-          ------  -----                                                                   */
/*-   hrate     0      0                                                                     */
/*-   qrate     0      1                                                                     */
/*-   if_mode   3      1                                                                     */
/*-                                                                                          */
/*- To tell if the 1G fiber-media macros have been configured for 100BASE-FX or 1000BASE-X:  */
/*-                                                                                          */
/*-                      100  1000                                                           */
/*-                      ---  ----                                                           */
/*-   ib_fx100_ena        1     0                                                            */
/*-   des_cpmd_sel        2     0                                                            */
/*-   des_100fx_cpmd_ena  1     0                                                            */
/*-                                                                                          */
/*-   RETURNS:  TRUE     If the HW has been initialized                                      */
/*-             FALSE    If the HW has not been initialized but Needs Initialization         */
/*- **************************************************************************************** */
// The 6G Macro can't be setup before all base ports are found
// The 6G Macro should only be run ONCE and on the base port of the PHY.
static BOOL vtss_phy_chk_serdes_init_mac_mode_private(vtss_state_t                      *vtss_state,
                                                      vtss_port_no_t                     port_no,
                                                      const vtss_phy_reset_conf_t *const conf)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_port_interface_t        micro_patch_mac_mode = VTSS_PORT_INTERFACE_NO_CONNECTION;
    vtss_phy_type_t              phy_id;
    u32  rd_dat = 0;
    u32  rd_dat1 = 0;
    u16  reg19G_val = 0;
    u8   mcb_bus = 0;
    u8   cfg_buf[MAX_CFG_BUF_SIZE];
    u8   stat_buf[MAX_STAT_BUF_SIZE];
    u8   pll_fsm_ena = 0;
    u8   sys_rst = 0;
    u8   ena_lane = 0;
    u8   hrate = 0;
    u8   qrate = 0;
    u8   if_mode = 0;
    u8   mac_if_19G = 0;

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg19G_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    mac_if_19G = (reg19G_val >> 14) & 0x3;
    VTSS_D("Checking SerDes Init MAC Mode, mac_if_19G: 0x%x", mac_if_19G);

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:
        VTSS_RC(vtss_phy_patch_setttings_get_private(vtss_state, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]));
        // Port 0 comes from 6G SerDes
        if (phy_id.base_port_no == port_no) {
            VTSS_D("Checking 6G SerDes Init MAC Mode");
            pll_fsm_ena = patch_array_value_decode(5, -1, &cfg_buf[0]);
            if_mode = patch_array_value_decode(17, 16, &cfg_buf[0]);
            qrate = patch_array_value_decode(18, -1, &cfg_buf[0]);
            hrate = patch_array_value_decode(19, -1, &cfg_buf[0]);
            ena_lane = patch_array_value_decode(30, -1, &cfg_buf[0]);
            sys_rst = patch_array_value_decode(35, -1, &cfg_buf[0]);
        } else {   // Non-Port 0 comes from 1G SerDes and the Offsets are Different in cfg_buf array
            VTSS_D("Checking 1G SerDes Init MAC Mode");
            pll_fsm_ena = patch_array_value_decode(3, -1, &cfg_buf[0]);
            if_mode = patch_array_value_decode(14, -1, &cfg_buf[0]);
            hrate = patch_array_value_decode(15, -1, &cfg_buf[0]);
            ena_lane = patch_array_value_decode(26, -1, &cfg_buf[0]);
            sys_rst = patch_array_value_decode(31, -1, &cfg_buf[0]);
            qrate = 0;
        }

        VTSS_D("ATOM/TESLA: HW Settings for port: %d, base_port: %d, hrate:%d, qrate: %d, if_mode:%d, pll_fsm_ena:%d, ena_lane:%d, sys_rst:%d ",
               port_no, phy_id.base_port_no, hrate, qrate, if_mode, pll_fsm_ena, ena_lane, sys_rst);
        //printf("ATOM/TESLA: HW Settings for port: %d, base_port: %d, hrate:%d, qrate: %d, if_mode:%d, pll_fsm_ena:%d, ena_lane:%d, sys_rst:%d \n", port_no, phy_id.base_port_no, hrate, qrate, if_mode, pll_fsm_ena, ena_lane, sys_rst);
#if 0
        printf("ATOM/TESLA: HW Settings for port: %d, base_port: %d, hrate:%d, qrate: %d, if_mode:%d, pll_fsm_ena:%d, ena_lane:%d, sys_rst:%d \n",
               port_no, phy_id.base_port_no, hrate, qrate, if_mode, pll_fsm_ena, ena_lane, sys_rst);
        u8   i = 0;
        for (i = 0; i < MAX_CFG_BUF_SIZE; i++) {
            printf("ATOM/TESLA: HW Patch_Array[%d] = 0x%x\n", i, cfg_buf[i]);
        }
#endif

        // From James : To tell if the 6G macro has been configured for QSGMII or SGMII operation (should correspond with 19G.15:14):
        //         QSGMII   SGMII   RGMII
        //        ------    -----  ------
        // hrate     0      0
        // qrate     0      1
        // if_mode   3      1
        // Reg19G    1      0         2
        if (phy_id.base_port_no == port_no) {         // Port 0 comes from 6G SerDes
            if ((mac_if_19G == 0x0) && (if_mode == 0x1) && (qrate == 0x1) && (hrate == 0)) {
                micro_patch_mac_mode = VTSS_PORT_INTERFACE_SGMII;
            } else if ((mac_if_19G == 0x1) && (if_mode == 0x3) && (qrate == 0) && (hrate == 0)) {
                micro_patch_mac_mode = VTSS_PORT_INTERFACE_QSGMII;
            } else if (mac_if_19G == 0x2) {
                micro_patch_mac_mode = VTSS_PORT_INTERFACE_RGMII;
            }
        } else {                                       // Non-Port 0 comes from 1G SerDes, have to check diff values
            if ((mac_if_19G == 0x0) && (if_mode == 0x1) && (hrate == 0)) {
                micro_patch_mac_mode = VTSS_PORT_INTERFACE_SGMII;
            } else if ((mac_if_19G == 0x1) && (if_mode == 0x0) && (hrate == 0)) {  // This should not be read for QSGMII
                micro_patch_mac_mode = VTSS_PORT_INTERFACE_QSGMII;
            } else if (mac_if_19G == 0x2) {
                micro_patch_mac_mode = VTSS_PORT_INTERFACE_RGMII;
            }
        }

        VTSS_D("ATOM/TESLA: port: %d, base_port: %d, mac_if_19G: %d, hrate:%d, qrate: %d, if_mode:%d micro_patch_mac_mode: %d, conf_mac_mode: %d",
               port_no, phy_id.base_port_no, mac_if_19G, hrate, qrate, if_mode, micro_patch_mac_mode, conf->mac_if);
        //printf("ATOM/TESLA: port: %d, base_port: %d, mac_if_19G: %d, hrate:%d, qrate: %d, if_mode:%d micro_patch_mac_mode: %d, conf_mac_mode: %d \n", port_no, phy_id.base_port_no, mac_if_19G, hrate, qrate, if_mode, micro_patch_mac_mode, conf->mac_if);

        if ((micro_patch_mac_mode != VTSS_PORT_INTERFACE_NO_CONNECTION) &&
            (conf->mac_if == micro_patch_mac_mode)) {
            if (micro_patch_mac_mode == VTSS_PORT_INTERFACE_QSGMII) {
                VTSS_I("API Config (%d) IN-SYNC with MAC SerDes HW (%d) == QSGMII", conf->mac_if, micro_patch_mac_mode);
                //printf("API Config (%d) IN-SYNC with MAC SerDes HW (%d) == QSGMII\n", conf->mac_if, micro_patch_mac_mode);
            } else if (micro_patch_mac_mode == VTSS_PORT_INTERFACE_SGMII) {
                VTSS_I("API Config (%d) IN-SYNC with MAC SerDes HW (%d) == SGMII", conf->mac_if, micro_patch_mac_mode);
                //printf("API Config (%d) IN-SYNC with MAC SerDes HW (%d) == SGMII\n", conf->mac_if, micro_patch_mac_mode);
            } else if (micro_patch_mac_mode == VTSS_PORT_INTERFACE_RGMII) {
                VTSS_I("API Config (%d) IN-SYNC with MAC HW (%d) == RGMII", conf->mac_if, micro_patch_mac_mode);
                //printf("API Config (%d) IN-SYNC with MAC HW (%d) == RGMII\n", conf->mac_if, micro_patch_mac_mode);
            }
            return TRUE;
        } else {
            VTSS_I("API Config (%d) NOT-IN-SYNC with MAC SerDes HW (%d); ", conf->mac_if, micro_patch_mac_mode);
            //printf("API Config (%d) NOT-IN-SYNC with MAC SerDes HW (%d); \n", conf->mac_if, micro_patch_mac_mode);
        }
        break;

    // These chips support the 6G macro setup
    case VTSS_PHY_FAMILY_VIPER:
    // viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A);
        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ELISE:
        // See TN1052 6G SerDes Table for Elise and Viper_RevA
        // Check the SW Config and the HW Config, if they don't match, STOP here!!
        // Reg19G has the HW MAC Setting, Compare to SW Config.
        // If the HW and SW do not match, The HW must be reconfigured!
        if (mac_if_19G ==  0x1) { // QSGMII, See data sheet register 19G
            if (conf->mac_if != VTSS_PORT_INTERFACE_QSGMII) {
                break;
            }
        } else if (mac_if_19G ==  0x0) {   // Viper Config ONLY, ie. This is an error for Elise
            if (conf->mac_if != VTSS_PORT_INTERFACE_SGMII) {
                break;
            }
        } else {
            // If we get to here, 6G SerDes settings only applies to QSGMII and SGMII.
            break;
        }

        /* Read in MCB's:  For Base Port: 0x3f; For Ports 1,2,3: 0x20 */
        /* Port 0 has both SGMII and QSGMII SerDes capabilities */
        if (port_no == phy_id.base_port_no) {
            /* Reading 6G MACRO - Offset 0x3f */
            VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0));    // read 6G MCB into CSRs
            VTSS_RC(vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, 0x2b, &rd_dat));  // PLL_CFG
            VTSS_RC(vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, 0x2c, &rd_dat1)); // COMMON_CFG
            VTSS_D("VIPER/ELISE: HW Settings for port: %d, base_port: %d, MACRO_CTRL::SERDES6G_PLL_CFG: 0x%08x;  SERDES6G_COMMON_CFG: 0x%08x",
                   port_no, phy_id.base_port_no, rd_dat, rd_dat1);
            pll_fsm_ena = (u8) ((rd_dat & 0x00000080) >> 7);
            sys_rst = (u8)((rd_dat1 & 0x80000000) >> 31);
            ena_lane = (u8)((rd_dat1 & 0x00040000) >> 18);
            hrate = (u8)((rd_dat1 & 0x00000080) >> 7);
            qrate = (u8)((rd_dat1 & 0x00000040) >> 6);
            if_mode = (u8)((rd_dat1 & 0x00000030) >> 4);

            // To tell if the 6G macro has been configured for QSGMII or SGMII operation (should correspond with 19G.14):
            //             QSGMII   SGMII
            //             ------    -----
            //      hrate     0      0
            //      qrate     0      1
            //      if_mode   3      1
            //      Reg19G    1      0
            //
            // Check to see if it's enabled
            if ((sys_rst == 0x1) && (ena_lane == 0x1) && (pll_fsm_ena == 0x1)) {
                if ((if_mode == 0x3) && (qrate == 0) && (hrate == 0)) {
                    micro_patch_mac_mode = VTSS_PORT_INTERFACE_QSGMII;
                } else if ((if_mode == 0x1) && (qrate == 1) && (hrate == 0)) {
                    micro_patch_mac_mode = VTSS_PORT_INTERFACE_SGMII;
                }
            }
        } else if (conf->mac_if == VTSS_PORT_INTERFACE_SGMII) {
            /* Reading 1G MACRO - Offset 0x20 */
            VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x20, 0));     // read 1G MCB into CSRs
            VTSS_RC(vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, 0x17, &rd_dat));   // PLL_CFG
            VTSS_RC(vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, 0x16, &rd_dat1));  // COMMON_CFG
            VTSS_D("VIPER/ELISE: HW Settings for port: %d, base_port: %d, MACRO_CTRL::SERDES1G_PLL_CFG: 0x%08x;  SERDES1G_COMMON_CFG: 0x%08x", port_no, phy_id.base_port_no, rd_dat, rd_dat1);
            pll_fsm_ena = (u8) ((rd_dat & 0x00000080) >> 7);
            sys_rst = (u8)((rd_dat1 & 0x80000000) >> 31);
            ena_lane = (u8)((rd_dat1 & 0x00040000) >> 18);
            hrate = (u8)((rd_dat1 & 0x00000080) >> 7);
            qrate = 1;  /* No Qrate for SGMII - Hard code just to be different than QSGMII */
            if_mode = (u8)((rd_dat1 & 0x00000001));

            // To tell if the 6G macro has been configured for QSGMII or SGMII operation (should correspond with 19G.14):
            //         QSGMII   SGMII
            //        ------    -----
            // hrate     0      0
            // qrate     0      1
            // if_mode   3      1
            // Reg19G    1      0
            // Check to see if it's enabled
            if ((sys_rst == 0x1) && (ena_lane == 0x1) && (pll_fsm_ena == 0x1)) {
                if ((if_mode == 0x3) && (qrate == 0) && (hrate == 0)) {
                    micro_patch_mac_mode = VTSS_PORT_INTERFACE_QSGMII;
                } else if ((if_mode == 0x1) && (qrate == 1) && (hrate == 0)) {
                    micro_patch_mac_mode = VTSS_PORT_INTERFACE_SGMII;
                }
            }
          /* QSGMII for ports NOT Base Port */
        } else if (conf->mac_if == VTSS_PORT_INTERFACE_QSGMII) {
            /* Reading 6G MACRO - Offset 0x3f */
            VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0));    // read 6G MCB into CSRs
            VTSS_RC(vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, 0x2b, &rd_dat));  // PLL_CFG
            VTSS_RC(vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, 0x2c, &rd_dat1)); // COMMON_CFG
            VTSS_D("VIPER/ELISE: HW Settings for port: %d, base_port: %d, MACRO_CTRL::SERDES6G_PLL_CFG: 0x%08x;  SERDES6G_COMMON_CFG: 0x%08x", port_no, phy_id.base_port_no, rd_dat, rd_dat1);
            pll_fsm_ena = (u8) ((rd_dat & 0x00000080) >> 7);
            sys_rst = (u8)((rd_dat1 & 0x80000000) >> 31);
            ena_lane = (u8)((rd_dat1 & 0x00040000) >> 18);
            hrate = (u8)((rd_dat1 & 0x00000080) >> 7);
            qrate = (u8)((rd_dat1 & 0x00000040) >> 6);
            if_mode = (u8)((rd_dat1 & 0x00000030) >> 4);
            // To tell if the 6G macro has been configured for QSGMII or SGMII operation (should correspond with 19G.14):
            //         QSGMII   SGMII
            //        ------    -----
            // hrate     0      0
            // qrate     0      1
            // if_mode   3      1
            // Reg19G    1      0
            // Check to see if it's enabled
            if ((sys_rst == 0x1) && (ena_lane == 0x1) && (pll_fsm_ena == 0x1)) {
                if ((qrate == 0) && (hrate == 0)) {
                    micro_patch_mac_mode = VTSS_PORT_INTERFACE_QSGMII;
                } else if ((if_mode == 0x1) && (qrate == 1) && (hrate == 0)) {
                    micro_patch_mac_mode = VTSS_PORT_INTERFACE_SGMII;
                }
            }
        }

        VTSS_D("VIPER/ELISE: HW Settings for port: %d, base_port: %d, mac_if_19G: 0x%x, hrate:%d, qrate: %d, if_mode:%d, pll_fsm_ena:%d, ena_lane:%d, sys_rst:%d ",
               port_no, phy_id.base_port_no, mac_if_19G, hrate, qrate, if_mode, pll_fsm_ena, ena_lane, sys_rst);

        if ((micro_patch_mac_mode != VTSS_PORT_INTERFACE_NO_CONNECTION) &&
            (conf->mac_if == micro_patch_mac_mode)) {
            if (micro_patch_mac_mode == VTSS_PORT_INTERFACE_QSGMII) {
                VTSS_D("API Config (%d) IN-SYNC with MAC SerDes HW (%d) == QSGMII", conf->mac_if, micro_patch_mac_mode);
            } else if (micro_patch_mac_mode == VTSS_PORT_INTERFACE_SGMII) {
                VTSS_D("API Config (%d) IN-SYNC with MAC SerDes HW (%d) == SGMII", conf->mac_if, micro_patch_mac_mode);
            }
            return TRUE;
        } else {
            VTSS_D("API Config (%d) NOT-IN-SYNC with MAC SerDes HW (%d); QSGMII != SGMII", conf->mac_if, micro_patch_mac_mode);
        }
        break;

    default:
        VTSS_D("Unhandled PHY Family: API Config (%d) NOT-IN-SYNC with MAC SerDes HW (%d)", conf->mac_if, micro_patch_mac_mode);
        break;
    }  // End of switch (ps->family)

    VTSS_D("Returning....API Config (%d) NOT-IN-SYNC with MAC SerDes HW (%d); QSGMII != SGMII", conf->mac_if, micro_patch_mac_mode);
    return FALSE;

}

/*- **************************************************************************************** */
/*- vtss_phy_chk_serdes_patch_init_private()                                                 */
/*- Description: Determine if the patch to the 6G Macros have already been applied           */
/*-              The micro-patch for the 6G Macros should be applied after SerDes init       */
/*-                                                                                          */
/*-              The SerDes Init and Micro-Patch should only be performed ONCE               */
/*-                                                                                          */
/*- For the 6G and 1G macros, the following bits will be strong indicators that the          */
/*- 6G macro has been configured by the software:  ie. if 0x80E0 for QSGMII or               */
/*-    0x80F0 for SGMII have been written to VTSS_PHY_MICRO_PAGE                             */
/*-                                                                                          */
/*-    ib Cfg bits                                                                           */
/*-    ----------------------------------------------------                                  */
/*-    ib_reg_pat_sel_offset  HW default = 1   New Value: 0                                  */
/*-                                                                                          */
/*-    ib Cfg2 bits                                                                          */
/*-    ----------------------------------------------------                                  */
/*-    ib_tcalv               HW default = 12  New Value: 13                                 */
/*-    ib_ureg                HW default = 4   New Value: 5                                  */
/*-                                                                                          */
/*-    Des Cfg bits                                          SGMII     QSGMII                */
/*-    --------------------------------------------------    -----     ------                */
/*-    des_bw_ana         HW default =          New Value:     3          5                  */
/*-                                                                                          */
/*-   RETURNS:  TRUE     If the HW has been initialized                                      */
/*-             FALSE    If the HW has not been initialized but Needs Initialization         */
/*- **************************************************************************************** */
// The 6G Macro can't be setup before all base ports are found
// The 6G Macro should only be run ONCE and on the base port of the PHY.
static BOOL vtss_phy_chk_serdes_patch_init_private(vtss_state_t                      *vtss_state,
                                                   vtss_port_no_t                     port_no,
                                                   const vtss_phy_reset_conf_t *const conf)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t              phy_id;
    u8                           ib_rtrm_adj = 0;
    u8                           ib_sig_det_clk_sel = 0;
    u8                           ib_reg_pat_sel_offset = 0;
    u8                           ib_cal_ena = 0;
    u8                           des_phy_ctrl = 0;
    u8                           des_mbtr_ctrl = 0;
    u8                           des_bw_hyst = 0;
    u8                           des_bw_ana = 0;
    u8                           ib_tinfv = 0;
    u8                           ib_tcalv = 0;
    u8                           ib_ureg = 0;

    VTSS_D("Checking 6G micro-patch MAC mode");

/*  The process of finding the Base Port of the PHY requires writing to EPG Registers */
/*  The Clock to enable writing to this registers is gated off of basic SerDes Init, ie. 0x80E0 or 0x80F0 (for Viper family) */
/*  Therefore, If the clock has not been enabled yet, it is safe to assume that the SerDes have not been configured */
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    if ((VTSS_PHY_BASE_PORTS_FOUND) != VTSS_RC_OK) { // Make sure that base ports are found, otherwise base port = -1
        VTSS_I("VTSS_PHY_BASE_PORTS_FOUND: SerDes micro-patch NOT Enabled on port: %d, base_port: %u", port_no, phy_id.base_port_no);
        return FALSE;
    }

    if ((phy_id.base_port_no) >= 0xffff) { // Make sure that base ports are found for this port, Default = -1
        VTSS_I("Early-Exit: SerDes micro-patch NOT Enabled on port: %d, base_port: %u", port_no, phy_id.base_port_no);
        return VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND;
    }

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:
        return TRUE;

    // These chips support the 6G macro setup
    case VTSS_PHY_FAMILY_VIPER:
    // viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A);
        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ELISE:
        VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0)); // read 6G MCB into CSRs
        VTSS_RC(vtss_phy_sd6g_ib_cfg0_rd_private(vtss_state, phy_id.base_port_no, &ib_rtrm_adj, &ib_sig_det_clk_sel, &ib_reg_pat_sel_offset, &ib_cal_ena));
        VTSS_RC(vtss_phy_sd6g_ib_cfg2_rd_private(vtss_state, phy_id.base_port_no, &ib_tinfv, &ib_tcalv, &ib_ureg));
        VTSS_RC(vtss_phy_sd6g_des_cfg_rd_private(vtss_state, phy_id.base_port_no, &des_phy_ctrl, &des_mbtr_ctrl, &des_bw_hyst, &des_bw_ana));

        VTSS_D("SerDes micro-patch for port: %d, ib_reg_pat_sel_offset: %d, ib_tcalv: %d, ib_ureg: %d, des_bw_ana: %d",
               port_no, ib_reg_pat_sel_offset, ib_tcalv, ib_ureg, des_bw_ana);

        if ((ib_reg_pat_sel_offset == 0) &&   // HW default = 1
            (ib_tcalv == 13) &&               // HW default = 12
            (ib_ureg  == 5) &&                // HW default = 4
            (((conf->mac_if == VTSS_PORT_INTERFACE_SGMII) && (des_bw_ana == 3)) ||    // SGMII
             ((conf->mac_if == VTSS_PORT_INTERFACE_QSGMII) && (des_bw_ana == 5)))) {   // QSGMII
            VTSS_D("SerDes micro-patch Enabled: %d", port_no);
            return TRUE;
        }
        break;

    default:
        VTSS_D("Unhandled PHY Family: Checking SerDes micro-patch for port:%d", port_no);
        break;
    }  // End of switch (ps->family)

    VTSS_D("SerDes micro-patch NOT Enabled: %d", port_no);
    return FALSE;
}

// The 6G Macro can't be setup before all base ports are found
// The 6G Macro should only be run ONCE and on the base port of the PHY.
static vtss_rc vtss_phy_warmstart_chk_micro_patch_mac_mode(vtss_state_t *vtss_state, vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    BOOL                   mac_if_ok;

    if (vtss_state->sync_calling_private) {
        mac_if_ok = vtss_phy_chk_serdes_init_mac_mode_private(vtss_state, port_no, conf);
        if (!mac_if_ok) {
            ps->warm_start_reg_changed = TRUE; // Signaling the a register for this port port has changed.
            VTSS_E("Warmstart micropatch mode NOT-IN-SYNC, Setting Warm Start Reg Change FLag, change detected in API 'vtss_phy_chk_serdes_init_mac_mode_private'");
        }
    }
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)

// Function for manipulating specific bit(s) in the phy patch configuration array for TESLA.
// NOTICE: Very Important!!  It is assumed that the MCB Data has already been fetched !!!!
//                           This function will configure the MCB, but the caller must write it back out!
// Limitations: This function only allow bit fields up to 8 bits.
//      This function handles: Single bit, Multi-bit in same byte, Multi-bit spanning 2 bytes, but Max of 8 bits.
// IN : port_no - PHY Port being operated upon
//      msb    - MSB bit in array.
//      lsb    - LSB bit in array - If only one bit the LSB shall be set to -1
//      val    - Value to be set
static vtss_rc patch_array_set_value(vtss_state_t *vtss_state, vtss_port_no_t port_no, i16 msb, i16 lsb, u8 val)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t        phy_id;
    u16                    arr_bit_lsb;
    u16                    arr_idx_lsb;
    u16                    arr_bit_msb;
    u16                    arr_idx_msb;
    u16                    reg18g = 0;
    u16                    addr = 0;
    u8                     pos = 0;
    u8                     tmp = 0;
    u8                     m = 0;
    u8                     sz = 0;

    if (ps->family != VTSS_PHY_FAMILY_TESLA) {
        VTSS_I ("port_no: %d,  Not TESLA Family!: 1G SerDes Config - INVALID FAMILY - ", port_no);
        return (VTSS_RC_INV_STATE);
    }

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    // We have the bit(s) we want to modify, i.e. VTSS_TESLA_SERDES1G_ANA_CFG_IB_ENA_DC_COUPLING_1G, so we need to find
    // the Address of the Byte that contains the bit(s).  A shift 3, bit >> 3, is a divide by 8, 8bits per byte
    if (lsb > 0) {
        arr_bit_lsb = lsb;
        arr_idx_lsb = arr_bit_lsb >> 3;
        arr_bit_msb = msb;
        arr_idx_msb = arr_bit_msb >> 3;
    } else {
        arr_bit_lsb = msb;
        arr_idx_lsb = arr_bit_lsb >> 3;
        arr_bit_msb = msb;
        arr_idx_msb = arr_bit_msb >> 3;
    }

    sz = (arr_bit_msb - arr_bit_lsb) + 1;
    if (sz > 8) {
        return (-101);
    }

    // Compute bit field starting position in local byte; arr_idx_lsb << 3 is arr_idx_lsb * 8;
    pos = arr_bit_lsb - (arr_idx_lsb << 3);
    addr = VTSS_TESLA_MCB_CFG_BUF_START_ADDR + arr_idx_lsb;

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, addr));  // set mem_addr to cfg_buf[arr_idx_lsb]
    (void)(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
    // read the value of cfg_buf[arr_idx_lsb] w/o post-incr.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
    // Now pointing at cfg_buf[arr_idx_lsb].
    // Read Reg18g, contains 16bits, starting at the address selected
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
    // This is setup for the lower 8bits first, then upper 8 bits; Manipulate the 16bits as required

    tmp = (u8)((reg18g >> 4) & 0xff);

    /* There are 3 cases to handle:   */
    /* 1. Single Bit field - Simplest */
    /* 2. Multiple bits in single byte   */
    /* 3. Multiple bits spanning 2 bytes   */
    m = 0;
    if (arr_idx_msb == arr_idx_lsb) {          // The bit fields are all in the same byte
        if (sz > 1) {          // Multiple bits
            u8 i;
            for (i = 0; i < sz; i++) {
                m |= 1 << (i % 8);
            }
            val = val & m;       // Mask the value to fit in this field
            m = m << pos;        // Shift the mask into the proper position
            tmp &= ~m;           // Clear any existing data in the fields
            tmp |= (val << pos); // Or in the data into the appropropriate fields
        } else {       // Multi-bit field
            m = 1 << ((pos) % 8);
            if (val) {
                tmp |= m;
            } else {
                tmp &= ~m;
            }
        }

        VTSS_D ("(1): port_no: %d, Addr: 0x%x; cfg_buf[%d]; lsb: %d; loc_pos: %d; m= 0x%x, sz: %d, Reg18g:0x%x; val:0x%x, Tmp:0x%x ",
                port_no, addr, arr_idx_lsb, arr_bit_lsb, pos, m, sz, (reg18g >> 4), val, tmp);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // write the value back to cfg_buf[arr_idx_lsb] w/ post-incr.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | ((u16)tmp << 4)));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        // Now pointing at cfg_buf[arr_idx_lsb+1].
    } else {                                   // The bit fields span 2 bytes
        u8   m1 = 0;
        u8   m2 = 0;
        u8   i;
        for (i = 0; i < sz; i++) {
            m |= 1 << (i % 8);
        }
        val = val & m;                 // Mask the value to fit in this field
        m1 = (m << pos) & 0xff;        // Shift the mask into the proper position for the lower byte
        m2 = (m >> (8 - pos)) & 0xff;      // Shift the mask into the proper position for the upper byte
        tmp &= ~m1;                    // Clear any existing data in the fields
        tmp |= ((val << pos) & m1);    // Or in the data into the appropropriate fields

        VTSS_D ("(2-Split): port_no: %d, Addr: 0x%x; cfg_buf[%d]; lsb: %d; loc_pos: %d; m=0x%x, m1= 0x%x, sz: %d, Reg18g:0x%x; val:0x%x, Tmp:0x%x ",
                port_no, addr, arr_idx_lsb, arr_bit_lsb, pos, m, m1, sz, (reg18g >> 4), val, tmp);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // write the value back to cfg_buf[arr_idx_lsb] w/post-incr.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9006 | ((u16)tmp << 4)));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // read the value of cfg_buf[arr_idx_lsb+1] w/o post-incr.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // because of post-incr, Now pointing at cfg_buf[arr_idx_lsb+1].
        // Read Reg18g, contains 16bits, starting at the address selected
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        // This is setup for the lower 8bits first, then upper 8 bits; Manipulate the 16bits as required

        tmp = (u8)((reg18g >> 4) & 0xff);    // Since this is a continuation, the position is going to be 0
        tmp &= ~m2;                          // Clear any existing data in the fields
        tmp |= (val >> (8 - pos)) & m2;      // Shift the data to match to location in this byte
        arr_bit_lsb = arr_idx_msb << 3;      // Starting bit location for 2nd part of value in patch stream

        VTSS_D("(3-Split) port_no: %d, Addr: 0x%x; cfg_buf[%d]; lsb: %d; loc_pos: %d; m2= 0x%x, sz: %d, Reg18g:0x%x; val:0x%x, Tmp:0x%x",
               port_no, addr + 1, arr_idx_lsb + 1, arr_bit_lsb, pos, m2, sz, (reg18g >> 4), val, tmp);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // write the value back to cfg_buf[arr_idx_lsb+1] w/post-incr.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | ((u16)tmp << 4)));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        // Now pointing at cfg_buf[arr_idx_lsb+2].

    }

    return VTSS_RC_OK;
}


// Function for configuring/updating the MAC (SGMII)/MEDIA (Fiber) 1G-SerDes PHY settings for PRBS enablement
// In - port_no - Phy port number.
//    - mcb_bus - MCB Bus to be configured
//                0: SerDes 1G
//                1: SerDes 6G
//                2: LCPLL/RComp
//    - slave_num - Slave to be Configured (1G Macro for MAC=SGMII/MEDIA=Fiber)
//                MAC i/f
//                mcb_bus=1, slave = 0 for QSGMII (6G Macro)
//                mcb_bus=1, slave = 0 for QSGMII (6G Macro) for Port 0
//                mcb_bus=0, slave = 1 for SGMII  (1G Macro) for Port 1
//                mcb_bus=0, slave = 3 for SGMII  (1G Macro) for Port 2
//                mcb_bus=0, slave = 5 for SGMII  (1G Macro) for Port 3
//                MEDIA i/f
//                mcb_bus=0, slave = 0 for Fiber (1G Macro) for Port 0
//                mcb_bus=0, slave = 2 for Fiber (1G Macro) for Port 1
//                mcb_bus=0, slave = 4 for Fiber (1G Macro) for Port 2
//                mcb_bus=0, slave = 6 for Fiber (1G Macro) for Port 3
//
static vtss_rc vtss_phy_tesla_serdes_sd6g_1g_prbs_conf_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 mcb_bus, u8 slave_num, BOOL is_fiber, BOOL prbs_ena)
{
    vtss_phy_type_t        phy_id;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16   micro_cmd = 0;
    u8    portAddr = 0;

    if (ps->family != VTSS_PHY_FAMILY_TESLA) {
        VTSS_I ("port_no: %d,  Not TESLA Family!: 1G SerDes Config - INVALID FAMILY,  mcb_bus: %d, slave_num: %d", port_no, mcb_bus, slave_num);
        return (VTSS_RC_INV_STATE);
    }

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    portAddr = vtss_phy_chip_port(vtss_state, port_no);

    if ((mcb_bus == 0) || (mcb_bus == 1)) {
        VTSS_I ("port_no: %d,  1G SerDes Config - Chip_Port: 0x%x, mcb_bus: %d, slave_num: %d", port_no, portAddr, mcb_bus, slave_num);
    } else {
        VTSS_I ("port_no: %d,  1G SerDes Config - INVALID MCB!,  Chip_Port: 0x%x, mcb_bus: %d, slave_num: %d", port_no, portAddr, mcb_bus, slave_num);
        return (VTSS_RC_INV_STATE);
    }

    // Note: The function patch_array_set_value() will reset the cfg_buf ptr to the correct offset based upon the bits manipulated each time it is called
    // The Function for manipulating specific bit(s) in the phy patch configuration array for TESLA.
    // NOTICE: Very Important!!  This function assumes that the MCB Data has already been fetched !!!!
    //                           This function will configure the MCB, but the caller must write it back out!
    //
    // Step 1: fetch MCB data
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, (0x8003 | (slave_num << 8) | (mcb_bus << 4))));     // Read MCB macro into PRAM
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    // Step 2: Modify the MCB Array
               mcb_bus = 1;
                slave_num = 0;

    if (mcb_bus == 1 && slave_num == 0) {   // VTSS_PORT_INTERFACE_QSGMII MACRO - one macro per quad)
        micro_cmd = 0x9c40;

        // Modify bits 288-287  PRBS_SEL=PRBS7
        VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES6G_DIG_CFG_PRBS_SEL_6G + 1, VTSS_TESLA_SERDES6G_DIG_CFG_PRBS_SEL_6G, VTSS_TESLA_SERDES_PRBS_7));

        if (prbs_ena) {
            // Modify bits 286-284  TEST_MODE=BIST
            VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES6G_DIG_CFG_TEST_MODE_6G + 2, VTSS_TESLA_SERDES6G_DIG_CFG_TEST_MODE_6G, VTSS_TESLA_SERDES_TEST_MODE_BIST));
        } else {
            // Modify bits 286-284  TEST_MODE=OFF
            VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES6G_DIG_CFG_TEST_MODE_6G + 2, VTSS_TESLA_SERDES6G_DIG_CFG_TEST_MODE_6G, VTSS_TESLA_SERDES_TEST_MODE_OFF));
        }
    } else if (mcb_bus == 0 && slave_num > 0) {  // VTSS_PORT_INTERFACE_SGMII MACRO
        // Modify bits 193-192  PRBS_SEL=PRBS7
        VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES1G_DIG_CFG_PRBS_SEL_1G + 1, VTSS_TESLA_SERDES1G_DIG_CFG_PRBS_SEL_1G, VTSS_TESLA_SERDES_PRBS_7));

        if (prbs_ena) {
            // Modify bits 191-189  TEST_MODE=BIST
            VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES1G_DIG_CFG_TEST_MODE_1G + 2, VTSS_TESLA_SERDES1G_DIG_CFG_TEST_MODE_1G, VTSS_TESLA_SERDES_TEST_MODE_BIST));
        } else {
            // Modify bits 191-189  TEST_MODE=OFF
            VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES1G_DIG_CFG_TEST_MODE_1G + 2, VTSS_TESLA_SERDES1G_DIG_CFG_TEST_MODE_1G, VTSS_TESLA_SERDES_TEST_MODE_OFF));
        }

        // 1000BASE-X/SGMII
        if (is_fiber) {
            // Setup MicroCmd for Write out the MCB - 1G Macro
            micro_cmd = 0x8040 | ((1 << portAddr) << 8);
            VTSS_I("port_no: %d, Media = FIBER (1000BX): Setting 1G MEDIA SerDes,  mcb_bus: %d, slave: %d, Cmd: 0x%x", port_no, mcb_bus, slave_num, micro_cmd);
        } else {
            // Setup MicroCmd for Write out the MCB - 1G Macro
            if (portAddr == 0) {
                micro_cmd = 0x9c40;
            } else {
                micro_cmd = 0x9040 | (portAddr << 8);
            }
            VTSS_I("port_no: %d, MAC = SGMII: Setting 1G MAC SerDes, mcb_bus: %d, slave: %d,  Cmd: 0x%x", port_no, mcb_bus, slave_num, micro_cmd);
        }
    }

    // Step 3: Write the MCB Array back out to take effect
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, micro_cmd)); // Write MCB for 1G macros X from PRAM
    (void) vtss_phy_wait_for_micro_complete(vtss_state, port_no);

    return VTSS_RC_OK;
}

// Function for configuring/updating the MAC SerDes PRBS PHY settings.
// In - port_no - Phy port number.
// In - prbs_ena - PRBS Enable  (TRUE=Enable/FALSE=Disable)
static vtss_rc vtss_phy_tesla_serdes_prbs_conf_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL prbs_ena)
{
    vtss_port_no_t         chip_port_no;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *conf = &ps->reset;
    u8 slave_num = 0;
    u8 mcb_bus = 0;
    BOOL  is_fiber = FALSE;

    if (ps->family != VTSS_PHY_FAMILY_TESLA) {
        return (VTSS_RC_OK);
    }

    chip_port_no = vtss_phy_chip_port(vtss_state, port_no);

    if (vtss_state->sync_calling_private) {
        return VTSS_RC_OK;
    }

    switch (ps->family) {
    case VTSS_PHY_FAMILY_TESLA :
        // set mem_addr to cfg_buf (0xd7c7 for Tesla)
        //mem_addr = 0xD7c7;

        // assume MCB bus is passed in as mcb_bus
        //    it is passed to 8051 in bits 7:4
        //    0: SerDes 1G
        //    1: SerDes 6G
        //    2: LCPLL/RComp

        //    it is passed to 8051 in bits 12:8
        //    for 1G the range is 0-7 (see port to MCB mappings in TN1121)
        //    for GG the range is 0-3 (see port to MCB mappings in TN1121)
        //    for LCPLL/RComp (only one) the value is always 0
        if (conf->mac_if ==  VTSS_PORT_INTERFACE_QSGMII) {  // QSGMII mapping (these are one macro per quad)
            mcb_bus = 1;  // only 6G macros used for QSGMII MACs
            switch (chip_port_no) {
            // 6G macro 0 not used in QSGMII mode
            case 0 :    // 6G macro 0
            case 1 :
            case 2 :
            case 3 :
                slave_num = 0;
                break;
            default :
                VTSS_E("Invalid port:%d", port_no);;
            }
        } else { // SGMII
            switch (chip_port_no) {
            // all 6G and 1G macros used for MACs in this mode
            case 0 :    // 6G macro 0
                mcb_bus = 1;
                slave_num = 0;
                break;
            case 1 :    // 1G macro 1
                mcb_bus = 0;
                slave_num = 1;
                break;
            case 2 :    // 1G macro 3
                mcb_bus = 0;
                slave_num = 3;
                break;
            case 3 :    // 1G macro 5
                mcb_bus = 0;
                slave_num = 5;
                break;
            default :
                VTSS_E("Invalid port:%d", port_no);  // some sort of error handling should go here
            }
        }
        break;
    default:
        VTSS_I("Patch setting get not supported for family:%s", vtss_phy_family2txt(ps->family));
        return (VTSS_RC_ERROR);
    }

    // MAC ports
    VTSS_RC(vtss_phy_tesla_serdes_sd6g_1g_prbs_conf_private(vtss_state, port_no, mcb_bus, slave_num, is_fiber, prbs_ena));

    return VTSS_RC_OK;
}
#endif


#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
// Function to set the ob_post0 parameter after configuring the 6G macro for QSGMII for ATOM12
// In : port_no - Port to configure
//      val     - Value to configure
static vtss_rc vtss_phy_cfg_ob_post0_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 val)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *conf = &ps->reset;
    vtss_rc rc = VTSS_RC_OK;
    u16 reg18g = 0;
    u8 tmp;

    if (conf->mac_if !=  VTSS_PORT_INTERFACE_QSGMII) {
        VTSS_I("vtss_phy_cfg_ob_post0 not supported on Non-QSGMII MAC i/f at port %u, Chip family:%s", port_no + 1, vtss_phy_family2txt(vtss_state->phy_state[port_no].family));
        return VTSS_RC_ERROR;
    }

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8113));  // Read MCB for 6G macro 1 into PRAM
        (void)  vtss_phy_wait_for_micro_complete(vtss_state, port_no);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d8));  // set mem_addr to cfg_buf[9] (0x47d8)
        (void)(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));  // read the value of cfg_buf[9] w/o post-incr.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // get bits 11:4 from return value and mask off upper 3 bits
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        tmp = (u8)((reg18g >> 4) & 0x1f);
        // OR in lower 3 bits of val shifted aprropriately
        tmp |= ((val & 7) << 5);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // write the value back to cfg_buf[9] w/ post-incr.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9006 | ((u16)tmp << 4)));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));  // read the value of cfg_buf[10] w/o post-incr.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // get bits 11:4 from return value and mask off lower 3 bits
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        tmp = (u8)((reg18g >> 4) & 0xf8);
        // OR in upper 3 bits of val shifted aprropriately
        tmp |= ((val >> 3) & 7);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // write the value back to cfg_buf[10] w/o post-incr.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | ((u16)tmp << 4)));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7ce));  // set mem_addr to 0x47ce (addr_vec)
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80e6));  // set addr_vec for macros 1-3
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9cc0));  // Write MCB for 6G macros 1-3 from PRAM
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        break;
    case VTSS_PHY_FAMILY_TESLA:
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8013));  // Read MCB for 6G macro 0 into PRAM
        (void)  vtss_phy_wait_for_micro_complete(vtss_state, port_no);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d0));  // set mem_addr to cfg_buf[9] (0x47d0)
        (void)(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));  // read the value of cfg_buf[9] w/o post-incr.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // get bits 11:4 from return value and mask off upper 3 bits
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        tmp = (u8)((reg18g >> 4) & 0x1f);
        // OR in lower 3 bits of val shifted aprropriately
        tmp |= ((val & 7) << 5);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // write the value back to cfg_buf[9] w/ post-incr.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9006 | ((u16)tmp << 4)));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));  // read the value of cfg_buf[10] w/o post-incr.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // get bits 11:4 from return value and mask off lower 3 bits
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        tmp = (u8)((reg18g >> 4) & 0xf8);
        // OR in upper 3 bits of val shifted aprropriately
        tmp |= ((val >> 3) & 7);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        // write the value back to cfg_buf[10] w/o post-incr.
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8006 | ((u16)tmp << 4)));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9c40));  // Write MCB for 6G macro 0 from PRAM
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        break;
    default:
        rc = VTSS_RC_ERROR;
        VTSS_I("vtss_phy_cfg_ob_post0 not supported at port %u, Chip family:%s", port_no + 1, vtss_phy_family2txt(vtss_state->phy_state[port_no].family));
    }

    return rc;
}
#endif

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)

// Function to set the ob_post0, ob_post1, ob_prec parameter after configuring the 6G macro for QSGMII for TESLA
// In : port_no - Port to configure
//      ob_post0     - Value to configure for ob_post0, 6 bits, Range 0-63
//      ob_post1     - Value to configure for ob_post1, 5 bits, Range 0-31
//      ob_prec      - Value to configure for ob_prec,  5 bits, Range 0-31
//
static vtss_rc vtss_phy_cfg_ob_cntrl_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 mcb_bus, u8 slave_num, u8 ob_post0, u8 ob_post1, u8 ob_prec)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc rc = VTSS_RC_OK;

    if (mcb_bus == 1 && slave_num == 0) {   // VTSS_PORT_INTERFACE_QSGMII MACRO - one macro per quad)
        switch (ps->family) {
        case VTSS_PHY_FAMILY_TESLA:
            // fetch MCB data
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch to micro/GPIO register-page
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, (0x8003 | (slave_num << 8) | (mcb_bus << 4))));     // Read MCB macro into PRAM
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));     // Switch back to micro/GPIO register-page
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, VTSS_TESLA_MCB_CFG_BUF_START_ADDR));    // 0xd7c7
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

            // ob_post0 = cfg_vec[ 82: 77], 6 bits
            // ob_post1 = cfg_vec[ 76: 72], 5 bits
            // ob_prec =  cfg_vec[ 71: 67], 5 bits
            VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES6G_ANA_CFG_OB_POST0_6G + 5 , VTSS_TESLA_SERDES6G_ANA_CFG_OB_POST0_6G, ob_post0));
            VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES6G_ANA_CFG_OB_POST1_6G + 4 , VTSS_TESLA_SERDES6G_ANA_CFG_OB_POST1_6G, ob_post1));
            VTSS_RC(patch_array_set_value(vtss_state, port_no, VTSS_TESLA_SERDES6G_ANA_CFG_OB_PREC_6G + 4 , VTSS_TESLA_SERDES6G_ANA_CFG_OB_PREC_6G, ob_prec));

            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9c40));  // Write MCB for 6G macro 0 from PRAM
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
            break;
        default:
            rc = VTSS_RC_ERROR;
            VTSS_I("vtss_phy_cfg_ob_cntrl_private not supported at port %u, Chip family:%s", port_no + 1, vtss_phy_family2txt(vtss_state->phy_state[port_no].family));
        }
    } else {
        VTSS_I("vtss_phy_cfg_ob_cntrl_private Only QSGMII supported at port %u, Chip family:%s", port_no + 1, vtss_phy_family2txt(vtss_state->phy_state[port_no].family));
        rc = VTSS_RC_ERROR;
    }
    return rc;
}

// Function for configuring/updating the MAC SerDes PRBS PHY settings.
// In - port_no - Phy port number.
// In - mode - INIT of MAC or MEDIA i/f values
// In - ob_post0 - ob_post0 value (6 bits: range 0-63)
// In - ob_post1 - ob_post0 value (5 bits: range 0-31)
// In - ob_prec  - ob_prec  value (5 bits: range 0-31)
static vtss_rc vtss_phy_tesla_serdes_ob_cntrl_conf_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_phy_serdes_init_t mode, u8 ob_post0, u8 ob_post1, u8 ob_prec)
{
    vtss_port_no_t         chip_port_no;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *conf = &ps->reset;
    u8 slave_num = 0;
    u8 mcb_bus = 0;

    if (ps->family != VTSS_PHY_FAMILY_TESLA) {
        return (VTSS_RC_OK);
    }

    chip_port_no = vtss_phy_chip_port(vtss_state, port_no);

    if (vtss_state->sync_calling_private) {
        return VTSS_RC_OK;
    }

    switch (ps->family) {
    case VTSS_PHY_FAMILY_TESLA :
        // set mem_addr to cfg_buf (0xd7c7 for Tesla)
        //mem_addr = 0xD7c7;

        // assume MCB bus is passed in as mcb_bus
        //    it is passed to 8051 in bits 7:4
        //    0: SerDes 1G
        //    1: SerDes 6G
        //    2: LCPLL/RComp

        //    it is passed to 8051 in bits 12:8
        //    for 1G the range is 0-7 (see port to MCB mappings in TN1121)
        //    for GG the range is 0-3 (see port to MCB mappings in TN1121)
        //    for LCPLL/RComp (only one) the value is always 0
        if (conf->mac_if ==  VTSS_PORT_INTERFACE_QSGMII) {  // QSGMII mapping (these are one macro per quad)
            mcb_bus = 1;  // only 6G macros used for QSGMII MACs
            switch (chip_port_no) {
            // 6G macro 0 not used in QSGMII mode
            case 0 :    // 6G macro 0
            case 1 :
            case 2 :
            case 3 :
                slave_num = 0;
                break;
            default :
                VTSS_E("Invalid port:%d", port_no);;
            }
        } else { // SGMII
            switch (chip_port_no) {
            // all 6G and 1G macros used for MACs in this mode
            case 0 :    // 6G macro 0
                mcb_bus = 1;
                slave_num = 0;
                break;
            case 1 :    // 1G macro 1
                mcb_bus = 0;
                slave_num = 1;
                break;
            case 2 :    // 1G macro 3
                mcb_bus = 0;
                slave_num = 3;
                break;
            case 3 :    // 1G macro 5
                mcb_bus = 0;
                slave_num = 5;
                break;
            default :
                VTSS_E("Invalid port:%d", port_no);  // some sort of error handling should go here
            }
        }
        break;
    default:
        VTSS_I("OB CNTRL not supported for family:%s", vtss_phy_family2txt(ps->family));
        return (VTSS_RC_ERROR);
    }

    /* Configure the MAC SerDes OB_CNTRL   */
    if (mode == VTSS_PHY_SERDES_INIT_MAC) {
        // MAC ports
        VTSS_I("Setting SERDES OB_CNTRL (MAC) for family:%s,  port_no:%d, ob_post0:0x%x, ob_post1:0x%x, ob_prec:0x%x",
                       vtss_phy_family2txt(ps->family), port_no, ob_post0, ob_post1, ob_prec);

        VTSS_RC(vtss_phy_cfg_ob_cntrl_private(vtss_state, port_no, mcb_bus, slave_num, ob_post0, ob_post1, ob_prec));

    } else {
        VTSS_I("vtss_phy_tesla_serdes_ob_cntrl_conf_private: OB_CNTRL Only Supported for QSGMII MAC port: %u, Chip family:%s", port_no + 1, vtss_phy_family2txt(vtss_state->phy_state[port_no].family));
        return (VTSS_RC_ERROR);
    }

    return VTSS_RC_OK;
}


#endif


// Function that check if mac interface for a specific port  has changed since the last time this function was called.
// Needed for Bugzero#48512, Changing speed at one port gives CRC errors at other ports.
// IN : port_no - The port in question.
//      current_mac_if - The current mac interface.

// OK - That multiple function call access this function at the same time, since the mac interface is not changed once it is configured for a specific port.
static BOOL mac_if_changed(vtss_state_t *vtss_state,
                           vtss_port_no_t port_no,
                           const vtss_phy_reset_conf_t *const conf)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_port_interface_t current_mac_if = conf->mac_if;
    BOOL                  mac_if_chged = FALSE;

    // Find out if interface has changed.
    if (ps->mac_if_old == current_mac_if) {
        mac_if_chged = FALSE;
    } else {
        // We think that the MAC i/f has changed.
        // We need to keep in mind that mac i/f can be RGMII, SGMII, QSGMII, others
        // This could be a Warm-Start where the HW is already configured but the vtss_state has not yet been set correctly
        mac_if_chged = TRUE;
    }

    VTSS_N("port:%u, mac_if_changed:%d, mac_if_old:%d, current_mac_if:%d",
           port_no, mac_if_chged, ps->mac_if_old, current_mac_if);

    ps->mac_if_old = current_mac_if; // Remember the last mac interface configured for this port.

    return mac_if_chged;
}

static vtss_rc vtss_phy_mac_media_if_atom_setup(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    //vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16 reg23 = 0;
    u16 reg19g = 0;
    BOOL fi_1000_mode = FALSE;  // Use to signal if 1000base-x mode is selected
    BOOL fi_100_mode = FALSE;   // Use to signal if 100base-fx mode is selected

    switch (conf->mac_if) {
    case VTSS_PORT_INTERFACE_SGMII:
        reg19g = 1 << 14; // SGMII to  CAT5 mode
        reg23  = 0 << 12; /* SGMII   */
        break;
    case VTSS_PORT_INTERFACE_SERDES:
        reg19g = 1 << 14; // SGMII to  CAT5 mode
        reg23  = 1 << 12; //  1000 BASE-X
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_FI_100FX:
        case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
        case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
        case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
        case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
        case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
            vtss_state->phy_inst_state.at_least_one_fiber_port = TRUE;
            break;
        default:
            // Copper port, but don't touch at_least_one_fiber_port.
            break;
        }

        //If some ports are copper only, you would not put these ports in an AMS or Fiber mode.  If you always set 19G.14:15 to 10, then you will enable the HSIO to power up the fiber media ports, so if we don't see any fiber ports at all, we keep the HSIO powered down in order to reduce the power consumption.
        if (vtss_state->phy_inst_state.at_least_one_fiber_port) {
            reg19g = 2 << 14; // QSGMII to CAT5 & Fiber mode
        } else {
            reg19g = 0 << 14; // QSGMII to CAT5 mode
        }
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        reg23 |= 0; //  Shouldn't matter since there is no "interface" for this port
        break;

    default:
        VTSS_E("port_no %u, Mac interface %d not supported", port_no, conf->mac_if);
        return VTSS_RC_ERROR;
    }

    switch (conf->media_if) {
    case VTSS_PHY_MEDIA_IF_CU:
        reg23 |= 0 << 8;
        break;
    case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
        reg23 |= 1 << 8;
        break;
    case VTSS_PHY_MEDIA_IF_FI_1000BX:
        fi_1000_mode = TRUE;
        reg23 |= 2 << 8;
        break;
    case VTSS_PHY_MEDIA_IF_FI_100FX:
        fi_100_mode = TRUE;
        reg23 |= 3 << 8;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
        reg23 |= VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE;
        reg23 |=  (4 << 8);
        break;
    case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
        fi_1000_mode = TRUE;
        reg23 |=  (5 << 8);
        reg23 &= ~VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
        reg23 |= VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE;
        fi_1000_mode = TRUE;
        reg23 |=  (6 << 8);
        break;
    case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
        fi_1000_mode = TRUE;
        reg23 |=  (6 << 8);
        reg23 &= ~VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
        reg23 |= VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE;
        fi_100_mode = TRUE;
        reg23 |= (7 << 8);
        break;
    case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
        fi_100_mode = TRUE;
        reg23 &= ~VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE;
        reg23 |= (7 << 8);
        break;
    default:
        VTSS_E("port_no %u, Media interface %d not supported", port_no, conf->media_if);
        return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
    }

    // Do the register accesses
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, reg19g, 0xC000));

    // Could be a Luton26 which is also using this function, but shouldn't set the MAC interface
    if (vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_ATOM ||  vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_TESLA) {
        VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, TRUE)); // Suspend 8051 Patch.
        if (mac_if_changed(vtss_state, port_no, conf)) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
            VTSS_RC(vtss_phy_warmstart_chk_micro_patch_mac_mode(vtss_state, port_no, conf));
#endif
            if (!vtss_state->sync_calling_private) {
                if (conf->mac_if ==  VTSS_PORT_INTERFACE_QSGMII) {
                    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

                    //  Bugzero#48512, Changing speed at one port gives CRC errors at other ports.
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80A0)); // See TN1085

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)

                    // ib_cterm and ob_post0 patches is only designed to run on Atom12 devices where the 8051 controls the MCB (otherwise the dreaded timeout will occur).
                    // ib_cterm called to override the ROM default.
                    VTSS_RC(vtss_phy_cfg_ib_cterm_ena_private(vtss_state, port_no, vtss_state->init_conf.serdes.ib_cterm_ena, 1));

                    // ob post called to override the ROM default of 2.
                    VTSS_RC(vtss_phy_cfg_ob_post0_private(vtss_state, port_no, vtss_state->init_conf.serdes.qsgmii.ob_post0));
#endif
                } else {
                    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
                    //  Bugzero#48512, Changing speed at one port gives CRC errors at other ports.
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80B0));// Seee TN1085
                }
            }
            // Wait for micro to complete MCB command to configure for QSGMII
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        }

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        if (fi_100_mode) {
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE , 0x8091 | 0x0100 << (vtss_phy_chip_port(vtss_state, port_no) % 4)));
            VTSS_D("MCB : Setting 100Fx mode, 0x%X", 0x8091 | 0x0100 << (vtss_phy_chip_port(vtss_state, port_no) % 4));
        }

        if (fi_1000_mode) {
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8081 | 0x0100 << (vtss_phy_chip_port(vtss_state, port_no) % 4)));
            VTSS_D("MCB : Setting 1000x mode, 0x%X", 0x8081 | 0x0100 << (vtss_phy_chip_port(vtss_state, port_no) % 4));
        }

        // Wait for micro to complete MCB command
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, FALSE)); // Resume 8051 Patch.
    }


    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_D("reg23:0x%X, media_if:%s, mac if:%d, port_no:%u, chip_no:%u",
           reg23, vtss_phy_media_if2txt(conf->media_if), conf->mac_if, port_no, vtss_phy_chip_port(vtss_state, port_no) % 12);
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, reg23));


    // Port must be reset in order to update the media setting for register 23
    VTSS_RC(vtss_phy_soft_reset_port(vtss_state, port_no));
    MEPA_MSLEEP(10);

    // Bugzilla#8714 - LabQual failures in QSGMII operation on FFFF parts
    // The sequence of PHY writes setting register 20E3.2 must be after the soft-reset.
    // This is because comma-bypass is envisioned as a debug bit that
    // should be reset when soft-reset is asserted; however, in this case, when the
    // QSGMII MAC interface is selected, it is desired to always bypass the
    // comma-detection logic to avoid issues on corner silicon.
    if (conf->mac_if == VTSS_PORT_INTERFACE_QSGMII) {
        VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MAC_SERDES_STATUS, 0x0004, 0x0004));
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

// Function for keeping track of if any port is running VeriPhy.
// In - port_no - Phy port number.
//      set     - True if the running state shall be updated for the port_no
//      running - Set to TRUE if VeriPhy is running for port_no.
BOOL vtss_phy_veriphy_running(vtss_state_t *vtss_state,
                              vtss_port_no_t port_no, BOOL set, u8 running)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_port_no_t        port_idx;

    // Remember if veriphy is running for this port.
    if (set) {
        ps->veriphy_running = (running ? TRUE : FALSE);
    }
    VTSS_N("set =%d, running = %d, veriphy_running[%d] = %u",
           set, running, port_no, ps->veriphy_running);


    // Return TRUE is any port has veriphy running
    for (port_idx = 0; port_idx < VTSS_PORTS; port_idx++) {
        if (vtss_state->phy_state[port_idx].veriphy_running) {
            return TRUE;
        }
    }

    return FALSE;
}

//Function for suspending / resuming the 8051 patch.
//
// In : port_no - Any port within the chip where to supend 8051 patch
//      suspend - True if 8051 patch shall be suspended, else patch is resumed.
// Return : VTSS_RC_OK if patch was suspended else error code.
vtss_rc vtss_atom_patch_suspend(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL suspend)
{
    u16 word;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    switch (vtss_state->phy_state[port_no].family) {
    case VTSS_PHY_FAMILY_TESLA:
        if (ps->type.revision == VTSS_PHY_TESLA_REV_A) {
            // No patch suspending for Rev. A.
            return VTSS_RC_OK;
        }
    // Fall through
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO :
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Change to GPIO page

        VTSS_N("vtss_atom_patch_suspend = %d, port = %d", suspend, port_no);




        // We must disable the EEE patch when VeriPHY is running,  When VeriPHY  is running, the patch  needs to be suspended by
        // writing 0x800f to register 18 on the Micro/GPIO page (0x10).  0x800f is chosen as this is an unimplemented micro-command
        // and issuing any micro command when the patch is running, causes the patch to stop.
        // The micro patch must not be enabled until all pending VeriPHY requests have been completed on all ports in the relevant Luton26 or Atom12 chip.
        // When all have been completed, the micro patch should re-enable.  Note that this is necessary only because the patch for EEE consumes
        //the micro continually to service all 12 PHYs in a timely manner and workaround one of the weaknesses in gigabit EEE in Luton26/Atom12.
        if (vtss_phy_veriphy_running(vtss_state, port_no, FALSE, FALSE)) {
            VTSS_N("vtss_atom_patch_suspend, port = %d", port_no);
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x800F)); // Suspend the micro patch
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no)); // Back to standard page
            return VTSS_RC_OK;
        }

        if (suspend) {
            // Suspending 8051 patch
            if ((vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_ATOM ||
                 vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_LUTON26) && (ps->type.revision == VTSS_PHY_ATOM_REV_A)) {
                // From JimB
                // You are suspending the micro patch momentarily by writing
                // 0x9014 to GPIO-page register 18 and resuming by writing 0x9004 to
                // GPIO-page register 18..
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9014)); // Suspend vga patch
                VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
            }  else {
                // See comment below.
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &word));
                if (!(word & 0x4000)) {
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x800F)); // Suspend 8051 EEE patch
                }
                VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
            }
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        } else {
            // Resuming 8051 patch
            if ((vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_ATOM ||
                 vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_LUTON26) && (ps->type.revision == VTSS_PHY_ATOM_REV_A)) {
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9004));
                VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

            }  else {
                // On page 0x10 (Reg31 = 0x10), write register 18 with 0x8009 to turn on the EEE patch.
                // Once this is done all code that might attempt to access page 0x52b5 will fail and likely cause issues.
                // If you need to access page 0x52b5 or run another page 0x10, register 18 function, you must first disable
                // the patch by writing 0x8009 again to register 18.  In response, the error bit (bit 14) will be set,
                // but the micro is now freed from running the EEE patch and you may issue your other micro requests.
                // When the other requests are complete, you will want to rerun the EEE patch by writing 0x8009 to register 18 on page 0x10.
                // The events that are handled by the micro patch occur occasionally, say one event across 12 ports every 30 seconds.
                // As a result, suspending the EEE patch for short durations Is unlikely to result in link drops, but it is possible.
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &word));
                if (word & 0x4000) {
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8009));
                }
                VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
            }
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        }

        break;
    default:
        VTSS_D("No micro patch for this PHY");
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no)); // Change to standard page

    return VTSS_RC_OK;
}

//  Function for pulling the coma mode pin high or low (The coma mode pin MUST be pulled high by an external pull up resistor)
//
// In : port  : Phy port (Any port within the PHY chip to pull down coma mode pin).
//      Low   : True to pull coma mode pin low (disable coma mode - ports are powered up)
// Return :  VTSS_RC_OK is setup was preformed correct else VTSS_RC_ERROR

static vtss_rc vtss_phy_coma_mode_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no, BOOL low)
{
// COMA mode is a new concept for Luton26/Atom12 for the PHYs and when the COMA_MODE pin is asserted, the PHY will
// remain powered down which is the ideal state to configure the PHY and SerDes MAC interfaces.  C
// COMA_MODE is designed to also synchronize LED clocks upon deassertion of COMA_MODE.  T
// The board designer should tie all COMA_MODE pins together. When the pin floats, an internal pull-up asserts the COMA_MDOE pin.
// After all internal Luton26 and external Atom12 PHYs have been configured, the initialization scripts should configure one of the devices to
// drive COMA_MODE pin low by changing COMA_MODE from an input to an output and setting the output to 0.  This will be sensed simultaneously
// at all PHYs and synchronize LED clocks between these PHYs.  Note that the LED blink on reset will occur, if configured, at the time that COMA_MODE goes low.


// The COMA_MODE pin may be configured using micro/GPIO register 14G.[13:12].
// Bit 13 is an active-low output enable which defaults on reset to 1 (e.g. output disabled).
// Bit 12 is the bit to drive the COMA_MODE pin to when the output is enabled.
    VTSS_RC(vtss_phy_page_gpio(vtss_state, (port_no)));
    if (low) {
        VTSS_N("Setting coma pin low");
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_GPIO_CONTROL_2, 0x0000,
                                        VTSS_F_PHY_GPIO_CONTROL_2_COMA_MODE_OUTPUT_ENABLE | VTSS_F_PHY_GPIO_CONTROL_2_COMA_MODE_OUTPUT_DATA));
    } else {
        VTSS_I("Setting coma pin high");
        // The coma mode pin MUST pulled high by an external pull up resistor, so only the output enable is changed)
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_GPIO_CONTROL_2, VTSS_F_PHY_GPIO_CONTROL_2_COMA_MODE_OUTPUT_ENABLE,
                                        VTSS_F_PHY_GPIO_CONTROL_2_COMA_MODE_OUTPUT_ENABLE));
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}


static vtss_rc vtss_phy_set_private_atom(vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_phy_mode_t mode)
{
    VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, TRUE));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000)); //Ensure RClk125 enabled even in powerdown
    // Clear Cl40AutoCrossover in forced-speed mode, but set it in non-forced modes
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa7fa));  // issue token-ring read request
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, (mode == VTSS_PHY_MODE_FORCED)
                               ? 0x0000 : 0x1000, 0x1000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));  // issue token-ring write request

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xaf82));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2, 0xf));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000)); //Restore RClk125 gating
    VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, FALSE));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));


    // Enable HP Auto-MDIX in forced-mode (by clearing disable bit)
    if (!vtss_state->sync_calling_private) {
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0000, VTSS_F_PHY_BYPASS_CONTROL_HP_AUTO_MDIX_AT_FORCE));
    }
    return VTSS_RC_OK;
}


static vtss_rc vtss_phy_get_media_if_config(const vtss_phy_reset_conf_t *const conf, u16 *micro_cmd_100fx, u8 *media_operating_mode, BOOL *cu_prefered)
{
    // Setup media interface
    switch (conf->media_if) {
    case VTSS_PHY_MEDIA_IF_CU:
        *media_operating_mode = 0;
        *cu_prefered = TRUE;
        break;
    case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
        *media_operating_mode = 1;
        *cu_prefered = TRUE;
        break;
    case VTSS_PHY_MEDIA_IF_FI_1000BX:
        *media_operating_mode = 2;
        *cu_prefered = FALSE;
        break;
    case VTSS_PHY_MEDIA_IF_FI_100FX:
        *media_operating_mode = 3;
        *cu_prefered = FALSE;
        *micro_cmd_100fx = 1 << 4;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
        *media_operating_mode = 5;
        *cu_prefered = TRUE;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
        *media_operating_mode = 5;
        *cu_prefered = FALSE;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
        *media_operating_mode = 6;
        *cu_prefered = TRUE;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
        *media_operating_mode = 6;
        *cu_prefered = FALSE;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
        *media_operating_mode = 7;
        *cu_prefered = TRUE;
        *micro_cmd_100fx = 1 << 4;
        break;
    case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
        *media_operating_mode = 7;
        *cu_prefered = FALSE;
        *micro_cmd_100fx = 1 << 4;
        break;
    default:
        return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
    }

    return (VTSS_RC_OK);
}

static vtss_rc vtss_phy_rgmii_tesla_mac_if_skew_setup(vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    u16   reg_val = 0;
    u8    rx_clk_skew = 0;
    u8    tx_clk_skew = 0;

    switch (conf->rgmii.tx_clk_skew_ps) {
    case rgmii_skew_delay_200_psec:
        tx_clk_skew = 0;
        break;
    case rgmii_skew_delay_800_psec:
        tx_clk_skew = 1;
        break;
    case rgmii_skew_delay_1100_psec:
        tx_clk_skew = 2;
        break;
    case rgmii_skew_delay_1700_psec:
        tx_clk_skew = 3;
        break;
    case rgmii_skew_delay_2000_psec:
        tx_clk_skew = 4;
        break;
    case rgmii_skew_delay_2300_psec:
        tx_clk_skew = 5;
        break;
    case rgmii_skew_delay_2600_psec:
        tx_clk_skew = 6;
        break;
    case rgmii_skew_delay_3400_psec:
        tx_clk_skew = 7;
        break;
    default:
        tx_clk_skew = 0;
        break;
    }

    switch (conf->rgmii.rx_clk_skew_ps) {
    case rgmii_skew_delay_200_psec:
        rx_clk_skew = 0;
        break;
    case rgmii_skew_delay_800_psec:
        rx_clk_skew = 1;
        break;
    case rgmii_skew_delay_1100_psec:
        rx_clk_skew = 2;
        break;
    case rgmii_skew_delay_1700_psec:
        rx_clk_skew = 3;
        break;
    case rgmii_skew_delay_2000_psec:
        rx_clk_skew = 4;
        break;
    case rgmii_skew_delay_2300_psec:
        rx_clk_skew = 5;
        break;
    case rgmii_skew_delay_2600_psec:
        rx_clk_skew = 6;
        break;
    case rgmii_skew_delay_3400_psec:
        rx_clk_skew = 7;
        break;
    default:
        rx_clk_skew = 0;
        break;
    }


    reg_val = VTSS_F_PHY_RGMII_CONTROL_TESLA_RGMII_SKEW_TX(tx_clk_skew) | VTSS_F_PHY_RGMII_CONTROL_TESLA_RGMII_SKEW_RX(rx_clk_skew);
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TESLA_RGMII_CONTROL, reg_val,
                               (VTSS_M_PHY_RGMII_CONTROL_TESLA_RGMII_SKEW_TX | VTSS_M_PHY_RGMII_CONTROL_TESLA_RGMII_SKEW_RX)));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return (VTSS_RC_OK);
}

/************************************************************************/
/* Tesla family functions                                               */
/************************************************************************/
/* See bugzilla 9450 for initial issue and 17849:Corrected the implementation of bug9450 and Bugzero_48512 */
/* Removed the code to put the PHY into Near-End loopback for all PHY's, this was a Tesla ONLY 1588 Clock issue */
static vtss_rc vtss_phy_mac_media_if_tesla_setup(vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf, BOOL *force_reset)
{
    u16                    micro_cmd_100fx = 0; // Use to signal to micro program if the fiber is 100FX (Bit 4). Default is 1000BASE-x
    u16                    reg_val;
    u16                    reg_mask;
    u16                    regConf = 0;
    u8                     media_operating_mode = 0;
    BOOL                   cu_prefered = FALSE;
    vtss_rc                rc = 0;
    BOOL                   mac_if_serdes_init = FALSE;
    BOOL                   mac_if_match = FALSE;
    BOOL                   media_if_match = FALSE;
    BOOL                   mac_if_has_chged_in_sw = FALSE;
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    BOOL                   mac_if_serdes_patch_init = FALSE;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
#endif
#ifdef _ENABLE_PHY_SERDES_DEBUG_
    u32                    csr_reg = 0;
    u32                    csr_reg_val = 0;
#endif


    mac_if_has_chged_in_sw = mac_if_changed(vtss_state, port_no, conf);
    /* This Compares the existing MAC/Media settings in Chip to those in the incoming Config */
    /* If MAC and MEDIA i/f is already configured and the setting is to Not Force a Reset, then rtn */
    /* The following 3 Scenario's are considered. All are because vtss_state has been cleared */
    /*  1) Power-On Reset - HW cleared, SW Appl Reset, prev_mac_if=0, ie. it was not initialized yet */
    /*  2) Warm-Start - HW configured, SW Appl Planned Reset, prev_mac_if = 0, but we have Warm-Start indicator flag */
    /*  3) Hot-Restart - HW Configured, SW Appl UnPlanned Reset, prev_mac_if = 0, but w/No Warm-Start Indication */
    if (conf->force == VTSS_PHY_NOFORCE_RESET) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        // Use the passed in Config and compare to Reg19G to get the MAC i/f of the HW and do config comparison
        switch (conf->mac_if) {
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_QSGMII:
        case VTSS_PORT_INTERFACE_RGMII:
            if ((rc = VTSS_PHY_BASE_PORTS_FOUND) == VTSS_RC_OK) { // Make sure that base ports are found
                mac_if_serdes_init = vtss_phy_chk_serdes_init_mac_mode_private(vtss_state, port_no, conf);
            } else {
                mac_if_serdes_init = FALSE;
            }
            VTSS_D("VTSS_PHY_NOFORCE_RESET:: port_no %u, mac_if_serdes_init = 0x%x, base_port_found:%x", port_no, mac_if_serdes_init, rc);
            //printf("VTSS_PHY_NOFORCE_RESET:: port_no %u, mac_if_serdes_init = 0x%x \n", port_no, mac_if_serdes_init);
            /* The MAC SerDes uses the base_port_no of the PHY.  This value is not known until Post-Reset of PHY is executed */
            if (vtss_state->sync_calling_private) {
                mac_if_serdes_init = TRUE;
            } else {                                     // Not Warm-Start, So if Appl Restarted, MAC i/f will not be initialized yet, ie. mac_if=0.
                if ((mac_if_serdes_init) && // If detect the MAC i/f appears to be setup correctly, but it could be Pwr-On default
                    (mac_if_has_chged_in_sw) &&  // The vtss_state indicates a diff since last mac_if update, possible hot-restart
                    (ps->type.base_port_no == port_no)) { // We are checking the base port
                    mac_if_serdes_init = FALSE;          // Over-ride the MAC i/f SerDes init and force a re-init
                    VTSS_D("VTSS_PHY_NOFORCE_RESET:Hot-Restart OVER-RIDE: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
                }
            }
            break;
        case VTSS_PORT_INTERFACE_NO_CONNECTION:
            mac_if_serdes_init = FALSE;
            VTSS_D("VTSS_PHY_NOFORCE_RESET:: NO_CONNECT: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
            break;
        default:
            mac_if_serdes_init = FALSE;
            VTSS_D("VTSS_PHY_NOFORCE_RESET:: DEFAULT: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
            break;
        }

#endif
        /* Now we can check the Media Side only if the MAC i/f appears to be Ok. */
        if (mac_if_serdes_init) {
            // Get the Media i/f that is in the configuration
            rc = vtss_phy_get_media_if_config(conf, &micro_cmd_100fx, &media_operating_mode, &cu_prefered);

            if (rc == VTSS_RC_OK) {
                regConf = VTSS_F_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE(media_operating_mode) |
                          (cu_prefered ? VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE : 0);

                // QSGMII, See Datasheet for 19G, if mac_if_serdes_init=TRUE, then SW Config==HW Config
                if (conf->mac_if == VTSS_PORT_INTERFACE_QSGMII) {           // SW Configured for QSGMII
                    mac_if_match = TRUE;
                } else if (conf->mac_if == VTSS_PORT_INTERFACE_SGMII) {     // HW and SW Config for SGMII
                    // If it is SGMII, we now need to determine if it is 1000BX or SGMII to check media operating modes later
                    // If SGMII and not 1000BX Operation, then VTSS_F_PHY_EXTENDED_PHY_CONTROL_MAC_INTERFACE_MODE must be clear
                    mac_if_match = TRUE;
                } else if (conf->mac_if == VTSS_PORT_INTERFACE_RGMII) {     // HW and SW Config for RGMII
                    mac_if_match = TRUE;
                } else {
                    mac_if_match = FALSE;
                }
            } else {
                mac_if_match = FALSE;
            }
            VTSS_D("port_no %u, mac_if_match = 0x%x ", port_no, mac_if_match);

            if (mac_if_match) {  /* If the MAC i/f is the same, Now check the Media side */
                /* Read Reg23 to check MAC, AMS Preference and Media operating modes */
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, &reg_val));
                if ((reg_val & 0x3f00) == regConf) {  // Compare bits 13:8 and if they match, no need to reset PHY
                    media_if_match = TRUE;
                    *force_reset = FALSE;
                    /* For 1000BaseX MAC, API does not really support it, but check for it in case someone went around the API to set it  */
                    /* Compare bits 11:8 to match media only, and if they match, then check the MAC I/F mode for a match  */
                } else if (((reg_val & 0x0f00) == regConf) &&                                   // Media Operating Modes match
                           (conf->mac_if == VTSS_PORT_INTERFACE_SGMII) &&                      // SW Config for SGMII
                           (reg_val & VTSS_F_PHY_EXTENDED_PHY_CONTROL_MAC_INTERFACE_MODE) &&   // 1000BaseX MAC is current HW Setting, This had to be set outside of API
                           (media_operating_mode == 2)) {                                      // 1000BaseX Fiber Media Only
                    media_if_match = TRUE;
                    *force_reset = FALSE;
                } else {
                    media_if_match = FALSE;
                    *force_reset = TRUE;
                }
            } else {
                *force_reset = TRUE;  /* MAC i/f changed, so force PHY RESET */
            }
        } else {
            *force_reset = TRUE;  /* MAC i/f changed, so force PHY RESET */
            VTSS_D("FORCE_RESET: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
        }

        VTSS_D("port_no %u, mac_if_match = 0x%x FORCE_RESET: 0x%x\n", port_no, mac_if_match, *force_reset );

        if (mac_if_match && media_if_match) {
            VTSS_I("VTSS_PHY_NOFORCE_RESET:: port_no %u, mac_if_match = TRUE, media_if_match = TRUE ", port_no);
            return VTSS_RC_OK;
        }
    }

    // Setup MAC Configuration
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    switch (conf->mac_if) {
    case VTSS_PORT_INTERFACE_SGMII:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK,
                                        0, VTSS_M_MAC_MODE_AND_FAST_LINK_MAC_IF_MODE_SELECT));
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK,
                                        0x4000, VTSS_M_MAC_MODE_AND_FAST_LINK_MAC_IF_MODE_SELECT));
        break;
    case VTSS_PORT_INTERFACE_RGMII:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK,
                                        0x8000, VTSS_M_MAC_MODE_AND_FAST_LINK_MAC_IF_MODE_SELECT));
        // Set the RGMII Skews, passed in from reset_config
        VTSS_RC(vtss_phy_rgmii_tesla_mac_if_skew_setup(vtss_state, port_no, conf));
        break;

    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        break;
    default:
        VTSS_E("port_no %u, Mac interface %d not supported", port_no, conf->mac_if);
        return VTSS_RC_ERROR;
    }

    // Setup media interface
    if ((rc = vtss_phy_get_media_if_config(conf, &micro_cmd_100fx, &media_operating_mode, &cu_prefered)) != VTSS_RC_OK) {
        VTSS_E("port_no %u, Media interface %d not supported", port_no, conf->media_if);
        return (rc);
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    if (mac_if_has_chged_in_sw) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        // Use the passed in Config and compare to Reg19G to get the MAC i/f of the HW and do config comparison
        switch (conf->mac_if) {
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_QSGMII:
        case VTSS_PORT_INTERFACE_RGMII:
            // On Warm-Start the MAC i/f in the vtss_state would be 0, because it has not been initialized yet.
            if (vtss_state->sync_calling_private) {
                VTSS_RC(vtss_phy_warmstart_chk_micro_patch_mac_mode(vtss_state, port_no, conf));
                if (ps->warm_start_reg_changed) {     // Signaling the a register for this port port has changed, ie. MAC i/f has changed; Therefore need to init.
                    mac_if_serdes_init = FALSE;
                    VTSS_I("MAC_IF_CHG:WARMSTART: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
                } else {
                    mac_if_serdes_init = TRUE;    // No HW Change, SW matches too
                    VTSS_I("MAC_IF_CHG:WARMSTART: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
                }
            } else {
                // NOT in warm-start - But, MAC_if Changed was indicated,
                // The Power-On Default is SGMII.  Therefore, if this PHY has not had the MAC i/f Initialized before,
                // We still need to run init.
                // This may cause an issue with running Hot Restart where System reboots without indicating warm-start
                if (ps->type.base_port_no == port_no) {
                    mac_if_serdes_init = FALSE;
                    VTSS_I("MAC_IF_CHG:: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
                } else {
                    mac_if_serdes_init = vtss_phy_chk_serdes_init_mac_mode_private(vtss_state, port_no, conf);
                    VTSS_I("MAC_IF_CHG:: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
                }
            }
            break;
        case VTSS_PORT_INTERFACE_NO_CONNECTION:
            mac_if_serdes_init = FALSE;
            VTSS_D("MAC_IF_CHG:: NO_CONNECT: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
            break;
        default:
            mac_if_serdes_init = FALSE;
            VTSS_D("MAC_IF_CHG:: DEFAULT: port_no %u, mac_if_serdes_init = 0x%x ", port_no, mac_if_serdes_init);
            break;
        }

#endif
        // Note: Setting to GPIO MUST occur before writing to PHY_MICRO_PAGE
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        if (conf->mac_if ==  VTSS_PORT_INTERFACE_QSGMII) {
            // Configure SerDes macros for QSGMII MAC interface (See TN1080)
            // Bug:16492:
            // However, Don't reconfig unless necessary because Reconfiguring SerDes means you also must reconfigure SerDes Patch
            // If the MAC i/f gets changed, we gotta do a PHY Reset for settings to take effect
            VTSS_D("port_no %u, Config: VTSS_PORT_INTERFACE_QSGMII", port_no);
            if (!mac_if_serdes_init) {   // Port 0 of the PHY
                VTSS_I("port_no %u, Configuring SerDes for VTSS_PORT_INTERFACE_QSGMII - 0x80E0 - force_reset = TRUE", port_no);
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80E0, 0xFFFF, 0x0));
                *force_reset = TRUE;
            }
        } else if (conf->mac_if ==  VTSS_PORT_INTERFACE_SGMII) {
            // Configure SerDes macros for 4xSGMII MAC interface (See TN1080)
            // Bug:16492:
            // All Ports need to get initialzed
            // However, Don't reconfig unless necessary because Reconfiguring SerDes means you also must reconfigure SerDes Patch
            // If the MAC i/f gets changed, we gotta do a PHY Reset for settings to take effect
            VTSS_D("port_no %u, Config: VTSS_PORT_INTERFACE_SGMII", port_no);
            if (!mac_if_serdes_init) {
                VTSS_I("port_no %u, Configuring SerDes for VTSS_PORT_INTERFACE_SGMII - 0x80F0 - force_reset = TRUE", port_no);
                VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80F0, 0xFFFF, 0));
                *force_reset = TRUE;
            }
        } else {
            VTSS_D("VTSS_PORT_INTERFACE_RGMII or VTSS_PORT_INTERFACE_NO_CONNECTION:: port_no %u", port_no);
        }
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        /*- Note: the SerDes Init will not occur until the sd6g patch is applied */
        /*- Cannot apply the Patch until the basic MAC i/f init has been done, ie. 0x80E0 or 0x80F0 */
        /*- The Basic MAC i/f init was done in code just above */
        /*- The SerDes patch config happens here */

        /* The Finding of base ports require writing to EPG register 30E1 */
        /* This requires a clock for the Writes to EPG Registers to take effect */
        /* The clock on Viper and Elise is not enabled until basic SerDes init, ie. 0x80E0 or 0x80F0 applied  */
        /* Also, the Base Port will be -1 if not found, the Macro: VTSS_PHY_BASE_PORTS_FOUND is for the PHY Instance  */
        /* If this is a multi-PHY Instance, then this information is misleading because there is a base port on each PHY */
        rc = vtss_phy_detect_base_ports_private(vtss_state);
        VTSS_I("Port:%d Results of vtss_phy_detect_base_ports_private: rc = 0x%x ", port_no, rc);

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        /*- Note: For Viper (VSC8584/etc) and Elise(VSC8514) PHY's, The SerDes init is a 2 stage process */
        /*- For Tesla, SerDes config is performed inside the micro-patch  */
        /*- This is the 2nd step, SerDes patch init, for Viper */
        if (ps->family == VTSS_PHY_FAMILY_VIPER) {
            /*- Note: the SerDes Init will not occur until the sd6g patch is applied */
            if ((rc = VTSS_PHY_BASE_PORTS_FOUND) == VTSS_RC_OK) { // Make sure that base ports are found
                switch (conf->mac_if) {
                case VTSS_PORT_INTERFACE_SGMII:
                case VTSS_PORT_INTERFACE_QSGMII:
#ifdef _ENABLE_PHY_SERDES_DEBUG_
                    for (csr_reg = 0x12; csr_reg < 0x34; csr_reg++) {
                        vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, csr_reg, &csr_reg_val);
                        VTSS_D("SD6G dump before sd6g_patch: port_no %u, sd6G SerDes Reg: 0x%x;  RegValue: 0x%08x  ", port_no, csr_reg, csr_reg_val);
                        VTSS_D("In First _ENABLE_PHY_SERDES_DEBUG_");
                    }
#endif
                    /* Check to ensure that 0x80E0 or 0x80F0 have been applied */
                    mac_if_serdes_init = vtss_phy_chk_serdes_init_mac_mode_private(vtss_state, port_no, conf);
                    if (!mac_if_serdes_init) {
                        VTSS_E("port_no %u, ERROR!  MAC i/f NOT CONFIGURED!   VTSS_PHY_BASE_PORTS_FOUND", port_no);
                    }

                    mac_if_serdes_patch_init = vtss_phy_chk_serdes_patch_init_private(vtss_state, port_no, conf);
                    if (!mac_if_serdes_patch_init) {
                        VTSS_D("VTSS_PHY_BASE_PORTS_FOUND:: port_no %u, base_ports_found rc: %d, Calling vtss_phy_sd6g_patch_private", port_no, rc);
                        VTSS_RC(vtss_phy_sd6g_patch_private(vtss_state, port_no));
                        *force_reset = TRUE;
                    }
#ifdef _ENABLE_PHY_SERDES_DEBUG_
                    for (csr_reg = 0x12; csr_reg < 0x34; csr_reg++) {
                        vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, csr_reg, &csr_reg_val);
                        VTSS_D("SD6G dump before sd6g_patch: port_no %u, sd6G SerDes Reg: 0x%x;  RegValue: 0x%08x  ", port_no, csr_reg, csr_reg_val);
                        VTSS_D("In First _ENABLE_PHY_SERDES_DEBUG_");
                    }
#endif
                    break;

                case VTSS_PORT_INTERFACE_RGMII:
                case VTSS_PORT_INTERFACE_NO_CONNECTION:
                default:
                    VTSS_D("MAC_IF: VTSS_PORT_INTERFACE_RGMII or VTSS_PORT_INTERFACE_NO_CONNECTION:: port_no %u, base_ports_found rc: %d", port_no, rc);
                    break;
                }
            }
        } else {
            VTSS_D("BASE_PORTS_NOT_FOUND: sd6g_patch init to occur in vtss_phy_post_reset: port_no %u, base_ports_found rc: %d", port_no, rc);
        }
#endif
    }
    MEPA_MSLEEP(10);

    if (!vtss_state->sync_calling_private) {
        if (conf->media_if == VTSS_PHY_MEDIA_IF_CU) {
            // Setup media in micro program.
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            // Turn off SerDes for 100Base-FX.
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80f1 | (0x0100 << (vtss_phy_chip_port(vtss_state, port_no) % 4))));
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
            // Turn off SerDes for 1000Base-X.
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80e1 | (0x0100 << (vtss_phy_chip_port(vtss_state, port_no) % 4))));
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
            MEPA_MSLEEP(10);
        } else {
            // Setup media in micro program. Bit 8-11 is bit for the corresponding port (See TN1080)
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            // Should be warmstart checked, but not possible at the moment (Bugzilla#11826)
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80C1 | (0x0100 << (vtss_phy_chip_port(vtss_state, port_no) % 4)) | micro_cmd_100fx));
            VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
            MEPA_MSLEEP(10);
        }
    }
    // Setup Media interface
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    reg_val  = VTSS_F_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE(media_operating_mode) |
               (cu_prefered ? VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE : 0);

    reg_mask  = VTSS_M_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE | VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE;

    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, reg_val, reg_mask));
    VTSS_D("media_operating_mode:%d, media_if:%d", media_operating_mode, conf->media_if);

    //Set packet mode
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    switch (conf->pkt_mode) {
    case VTSS_PHY_PKT_MODE_JUMBO_9_KB:
    case VTSS_PHY_PKT_MODE_JUMBO_12_KB:
    case VTSS_PHY_PKT_MODE_IEEE_1_5_KB:
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, conf->pkt_mode << 4, 0x30));
        break;
    default:
        break;
    }
    /* PHY Reset is performed by vtss_phy_reset_private(), Step 3.  */
    return VTSS_RC_OK;
}

/************************************************************************/
/* NANO family functions                                               */
/************************************************************************/

static vtss_rc vtss_phy_rgmii_nano_mac_if_skew_setup(vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    u16   reg_val = 0;
    u8    rx_clk_skew = 0;
    u8    tx_clk_skew = 0;

    switch (conf->rgmii.tx_clk_skew_ps) {
    case rgmii_skew_delay_200_psec:
        tx_clk_skew = 0;
        break;
    case rgmii_skew_delay_800_psec:
        tx_clk_skew = 1;
        break;
    case rgmii_skew_delay_1100_psec:
        tx_clk_skew = 2;
        break;
    case rgmii_skew_delay_1700_psec:
        tx_clk_skew = 3;
        break;
    case rgmii_skew_delay_2000_psec:
        tx_clk_skew = 4;
        break;
    case rgmii_skew_delay_2300_psec:
        tx_clk_skew = 5;
        break;
    case rgmii_skew_delay_2600_psec:
        tx_clk_skew = 6;
        break;
    case rgmii_skew_delay_3400_psec:
        tx_clk_skew = 7;
        break;
    default:
        tx_clk_skew = 0;
        break;
    }

    switch (conf->rgmii.rx_clk_skew_ps) {
    case rgmii_skew_delay_200_psec:
        rx_clk_skew = 0;
        break;
    case rgmii_skew_delay_800_psec:
        rx_clk_skew = 1;
        break;
    case rgmii_skew_delay_1100_psec:
        rx_clk_skew = 2;
        break;
    case rgmii_skew_delay_1700_psec:
        rx_clk_skew = 3;
        break;
    case rgmii_skew_delay_2000_psec:
        rx_clk_skew = 4;
        break;
    case rgmii_skew_delay_2300_psec:
        rx_clk_skew = 5;
        break;
    case rgmii_skew_delay_2600_psec:
        rx_clk_skew = 6;
        break;
    case rgmii_skew_delay_3400_psec:
        rx_clk_skew = 7;
        break;
    default:
        rx_clk_skew = 0;
        break;
    }

    reg_val = VTSS_F_PHY_RGMII_CONTROL_NANO_RGMII_SKEW_TX(tx_clk_skew) | VTSS_F_PHY_RGMII_CONTROL_NANO_RGMII_SKEW_RX(rx_clk_skew);
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_RGMII_CONTROL, reg_val,
                               (VTSS_M_PHY_RGMII_CONTROL_NANO_RGMII_SKEW_TX | VTSS_M_PHY_RGMII_CONTROL_NANO_RGMII_SKEW_RX)));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return (VTSS_RC_OK);
}


static vtss_rc vtss_phy_mac_media_if_nano_setup(vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    if (vtss_state->phy_state[port_no].type.part_number == VTSS_PHY_TYPE_7435) {
        // The integrated PHY in Serval does not supports this. In fact it is not a "real" dual media (See Serval data sheet).
        return VTSS_RC_OK;
    }

    // For Nano the only MAC modes are (G)MII and RGMII.

    // Setup MAC Configuration
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    switch (conf->mac_if) {
    case VTSS_PORT_INTERFACE_MII:
    case VTSS_PORT_INTERFACE_GMII:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, 0x0,
                                        (VTSS_F_PHY_EXTENDED_PHY_CONTROL_MAC_INTERFACE_MODE | VTSS_F_PHY_EXTENDED_PHY_CONTROL_RXCLK_BUG_15388)));

        VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_RGMII_CONTROL, VTSS_F_PHY_RGMII_CONTROL_RX_CLK_OUT_DISABLE,
                                        VTSS_F_PHY_RGMII_CONTROL_RX_CLK_OUT_DISABLE));
        break;

    case VTSS_PORT_INTERFACE_RGMII:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL,
                                        (VTSS_F_PHY_EXTENDED_PHY_CONTROL_MAC_INTERFACE_MODE | VTSS_F_PHY_EXTENDED_PHY_CONTROL_RXCLK_BUG_15388),
                                        (VTSS_F_PHY_EXTENDED_PHY_CONTROL_MAC_INTERFACE_MODE | VTSS_F_PHY_EXTENDED_PHY_CONTROL_RXCLK_BUG_15388)));

        VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_RGMII_CONTROL, 0x0,
                                        VTSS_F_PHY_RGMII_CONTROL_RX_CLK_OUT_DISABLE));

        /* Enable SOF signal if PHY has this capability */
        if (vtss_state->phy_state[port_no].features & VTSS_CAP_SOF_TS) {
            VTSS_D("Enabling SOF signal on PHY");
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_RGMII_CONTROL, VTSS_M_PHY_RGMII_CONTROL_NANO_SOF_ENABLE, VTSS_M_PHY_RGMII_CONTROL_NANO_SOF_ENABLE));
        }

        VTSS_RC(vtss_phy_rgmii_nano_mac_if_skew_setup(vtss_state, port_no, conf));
        break;

    case VTSS_PORT_INTERFACE_NO_CONNECTION:
    case VTSS_PORT_INTERFACE_QSGMII:
    default:
        VTSS_E("port_no %u, Mac interface %d not supported", port_no, conf->mac_if);
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    /* PHY Reset is performed by vtss_phy_reset_private(), Step 3.  */
    return VTSS_RC_OK;
}


/************************************************************************/
/* ELISE family functions                                               */
/************************************************************************/

static vtss_rc vtss_phy_mac_media_if_elise_setup(vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16 reg_val;
    u16 reg_mask;
    BOOL                   mac_if_serdes_init = FALSE;
    vtss_rc                rc = 0;
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    BOOL                   mac_if_serdes_patch_init = FALSE;
#endif

    if (vtss_phy_chip_port(vtss_state, port_no) != 0) {
        return VTSS_RC_OK;
    }

    // Setup MAC Configuration
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

    switch (conf->mac_if) {
    case VTSS_PORT_INTERFACE_QSGMII:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK,
                                        0x4000, VTSS_M_MAC_MODE_AND_FAST_LINK_MAC_IF_MODE_SELECT));
        break;

    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
    default:
        VTSS_E("port_no %u, Mac interface %d not supported", port_no, conf->mac_if);
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        return VTSS_RC_ERROR;
    }

    // Setup media interface
    switch (conf->media_if) {
    case VTSS_PHY_MEDIA_IF_CU:
        break;
    case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
    case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
    case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
    case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
        if (ps->type.part_number != VTSS_PHY_TYPE_7435) { // Only the integrated PHY in Serval supports these. In fact it is not a "real" dual media (See Serval data sheet).
            VTSS_E("port_no %u, Media interface %d not supported", port_no, conf->media_if);
            return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
        }
        break;
    default:
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_E("port_no %u, Media interface %d not supported", port_no, conf->media_if);
        return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    mac_if_serdes_init = vtss_phy_chk_serdes_init_mac_mode_private(vtss_state, port_no, conf);
    VTSS_RC(vtss_phy_warmstart_chk_micro_patch_mac_mode(vtss_state, port_no, conf));
#endif
    // Note: Setting to GPIO MUST occur before writing to PHY_MICRO_PAGE
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    // Configure SerDes macros for QSGMII MAC interface (See TN1080)
    // Bug:16492:
    // However, Don't reconfig unless necessary because Reconfiguring SerDes means you also must reconfigure SerDes Patch
    // If the MAC i/f gets changed, we gotta do a PHY Reset for settings to take effect
    VTSS_D("port_no %u, Config: VTSS_PORT_INTERFACE_QSGMII", port_no);
    if (!mac_if_serdes_init) {   // Port 0 of the PHY
        VTSS_D("port_no %u, Configuring SerDes for VTSS_PORT_INTERFACE_QSGMII ", port_no);
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80E0, 0xFFFF, 0x0));
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
    }

    /*- Note: the SerDes Init will not occur until the sd6g patch is applied */
    /* The Finding of base ports require writing to EPG register 30E1 */
    /* This requires a clock for the Writes to EPG Registers to take effect */
    /* The clock on Viper and Elise is not enabled until basic SerDes init, ie. 0x80E0 or 0x80F0 applied  */
    /* Also, the Base Port will be -1 if not found, the Macro: VTSS_PHY_BASE_PORTS_FOUND is for the PHY Instance  */
    /* If this is a multi-PHY Instance, then this information is misleading because there is a base port on each PHY */
    rc = vtss_phy_detect_base_ports_private(vtss_state);
    VTSS_I("Port:%d Results of vtss_phy_detect_base_ports_private: rc = 0x%x ", port_no, rc);

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    if ((rc = VTSS_PHY_BASE_PORTS_FOUND) == VTSS_RC_OK) { // Make sure that base ports are found
        /* Check to ensure that 0x80E0 or 0x80F0 have been applied */
        mac_if_serdes_init = vtss_phy_chk_serdes_init_mac_mode_private(vtss_state, port_no, conf);
        if (!mac_if_serdes_init) {
            VTSS_E("port_no %u, ERROR!  MAC i/f NOT CONFIGURED!   VTSS_PHY_BASE_PORTS_FOUND", port_no);
        }

        mac_if_serdes_patch_init = vtss_phy_chk_serdes_patch_init_private(vtss_state, port_no, conf);
        if (!mac_if_serdes_patch_init) {
            VTSS_D("VTSS_PHY_BASE_PORTS_FOUND:: port_no %u, base_ports_found rc: %d, Calling vtss_phy_sd6g_patch_private", port_no, rc);
            VTSS_RC(vtss_phy_sd6g_patch_private(vtss_state, port_no));
        }
    }
#endif
    // Setup Media interface
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    reg_val  = VTSS_F_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE(0);
    reg_mask = VTSS_M_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE;
    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, reg_val, reg_mask));

    /* PHY Reset is performed by vtss_phy_reset_private(), Step 3.  */

    return VTSS_RC_OK;
}


/************************************************************************/
/* Quattro family functions                                               */
/************************************************************************/

static vtss_rc vtss_phy_mac_media_if_quattro_setup (vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    u16 reg = 0;
    switch (conf->mac_if) {
    case VTSS_PORT_INTERFACE_SGMII:
        /* VSC8234 */
        reg = ((0xB << 12) | (0 << 1)); /* 4-pin SGMII, auto negotiation disabled */
        break;
    case VTSS_PORT_INTERFACE_RGMII:
        /* VSC8224/44 */
        reg = (((conf->media_if == VTSS_PHY_MEDIA_IF_AMS_CU_1000BX ||
                 conf->media_if == VTSS_PHY_MEDIA_IF_AMS_FI_1000BX ? 0 : 1) << 12) |
               (rgmii_clock_skew(conf->rgmii.tx_clk_skew_ps) << 10) |
               (rgmii_clock_skew(conf->rgmii.rx_clk_skew_ps) << 8) |
               ((conf->media_if == VTSS_PHY_MEDIA_IF_CU ||
                 conf->media_if == VTSS_PHY_MEDIA_IF_AMS_CU_1000BX ? 2 : 1) << 1));
        break;
    case VTSS_PORT_INTERFACE_RTBI:
        /* VSC8224/44 */
        reg = (((conf->tbi.aneg_enable ? 4 : 5) << 12) |
               ((conf->tbi.aneg_enable ? 1 : 0) << 1));
        break;
    default:
        VTSS_E("port_no %u, MAC interface %s not supported for Quattro",
               port_no, vtss_port_if_txt(conf->mac_if));
        return VTSS_RC_ERROR;
    }
    reg |= (1 << 5); /* Rx Idle Clock Enable, must be 1 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, reg));
    return VTSS_RC_OK;
}

/* Init Scripts for VSC8224/VSC8234/VSC8244 aka Quattro */
static vtss_rc vtss_phy_init_seq_quattro(vtss_state_t *vtss_state,
                                         vtss_phy_port_state_t *ps,
                                         vtss_port_no_t        port_no)
{
    u16 reg = 0;

    /* BZ 1380 - PLL Error Detect Bit Enable */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_2, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    if (ps->type.revision < 3) {
        /* BZ 1671 */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0671));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fae));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0040, 0x0040));

        /* BZ 1746 */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000f));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x492a));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fa4));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

        /* BZ 1799 */
        VTSS_RC(vtss_phy_optimize_jumbo(vtss_state, port_no));

        /* BZ 2094 */
        if (ps->reset.mac_if == VTSS_PORT_INTERFACE_RGMII) {
            VTSS_RC(vtss_phy_optimize_rgmii_strength(vtss_state, port_no));
        }
    }

    /* BZ 1776 */
    VTSS_RC(vtss_phy_optimize_receiver_init(vtss_state, port_no));

    /* BZ 2229 */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
    VTSS_RC(vtss_phy_optimize_dsp(vtss_state, port_no));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    /* BZ 2080 */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xaf82));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
    reg = (reg & 0xffef) | 0;           /*- Enable DFE in 100BT */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));

    /* Enable signal detect input (active low) if not copper media */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL,
                        ps->reset.media_if == VTSS_PHY_MEDIA_IF_CU ?
                        0x0002 : 0x0001));

    /* Disable down shifting */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, 0x0000, 0x0010));

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    /* Enable Smart Pre-emphasis */
    VTSS_RC(vtss_phy_enab_smrt_premphasis(vtss_state, port_no));

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_mac_media_if_spyder_gto_setup (vtss_state_t *vtss_state, const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf, \
                                                       const vtss_phy_type_t phy_type)
{
    u16 reg = 0;

    if (phy_type.part_number == VTSS_PHY_TYPE_8538) {
        switch (conf->mac_if) {
        case VTSS_PORT_INTERFACE_SGMII:
            reg = ((0 << 13) | (0 << 12));  /* SGMII, Auto negotiation disabled */
            break;
        case VTSS_PORT_INTERFACE_SERDES:
            reg = ((0 << 13) | (1 << 12));      /* SerDes 1000-BaseX, Auto negotiation disabled */
            break;

        case VTSS_PORT_INTERFACE_NO_CONNECTION:
            reg |= (0 << 11) | (8 << 12); // Setting to Reserved. Shouldn't matter since there is no "interface" for this port
            break;

        default:
            VTSS_E("port_no %u, MAC interface %s not supported for Spyder",
                   port_no, vtss_port_if_txt(conf->mac_if));
            return VTSS_RC_ERROR;
        }
    }         /* phy_type = VTSS_PHY_TYPE_8538 */
    else if (phy_type.part_number == VTSS_PHY_TYPE_8558) {
        switch (conf->mac_if) {
        case VTSS_PORT_INTERFACE_SGMII:
            reg = ((0 << 13) | (0 << 12));                                                    /* SGMII MAC; MAC Auto Negotiation disabled */
            break;
        case VTSS_PORT_INTERFACE_SERDES:                              /* SerDes MAC; MAC Auto Negotiation disabled */
            reg = ((0 << 13)) | ((1 << 12));
            break;
        case VTSS_PORT_INTERFACE_NO_CONNECTION:
            reg |= (0 << 11) | (8 << 12); // Setting to Reserved. Shouldn't matter since there is no "interface" for this port
            break;

        default:
            VTSS_E("port_no %u, MAC interface %s not supported for Spyder",
                   port_no, vtss_port_if_txt(conf->mac_if));
            return VTSS_RC_ERROR;
        }

        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            reg |= (0 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
            reg |= (1 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
            reg |= (2 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
            reg |= (1 << 11) | (5 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
            reg |= (0 << 11) | (5 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
            reg |= (1 << 11) | (6 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
            reg |= (0 << 11) | (6 << 8);
            break;
        default:
            VTSS_E("port_no %u, Media interface not supported for Spyder", port_no);
            return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
        }
    }              /* phy_type == VTSS_PHY_TYPE_8558 */
    else if (phy_type.part_number == VTSS_PHY_TYPE_8658) {
        switch (conf->mac_if) {
        case VTSS_PORT_INTERFACE_SGMII:
            reg = ((0 << 13) | (0 << 12));                                                    /* SGMII MAC; MAC Auto Negotiation disabled */
            switch (conf->media_if) {
            case VTSS_PHY_MEDIA_IF_CU:
                reg |= (0 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
                reg |= (1 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_FI_1000BX:
                reg |= (2 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_FI_100FX:
                reg |= (3 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
                reg |= (1 << 11)  |  (5 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
                reg |= (0 << 11) | (5 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
                reg |= (1 << 11) | (6 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
                reg |= (0 << 11) | (6 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
                reg |= (1 << 11) | (7 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
                reg |= (0 << 11) | (7 << 8);
                break;
            default:
                VTSS_E("port_no %u, Media interface not supported for Spyder", port_no);
                return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
            }
            break;
        case VTSS_PORT_INTERFACE_SERDES:
            reg = ((0 << 13)) | ((1 << 12));                                                   /* SerDes MAC; MAC Auto Negotiation disabled */
            switch (conf->media_if) {
            case VTSS_PHY_MEDIA_IF_CU:
                reg |= (0 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
                reg |= (1 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_FI_1000BX:
                reg |= (2 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
                reg |= (1 << 11)  |  (5 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
                reg |= (0 << 11) | (5 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
                reg |= (1 << 11) | (6 << 8);
                break;
            case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
                reg |= (0 << 11) | (6 << 8);
                break;
            default:
                VTSS_E("port_no %u, Media interface not supported for Spyder", port_no);
                return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
            }
            break;

        case VTSS_PORT_INTERFACE_NO_CONNECTION:
            reg |= (0 << 11) | (8 << 8); // Setting to Reserved. Shouldn't matter since there is no "interface" for this port
            break;


        default:
            VTSS_E("port_no %u, MAC interface %s not supported for Spyder",
                   port_no, vtss_port_if_txt(conf->mac_if));
            return VTSS_RC_ERROR;
        }
    }             /* phy_type == VTSS_PHY_TYPE_8658 */

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, reg));
    return VTSS_RC_OK;
}

/* Init scripts for VSC8538/VSC8558/VSC8658 aka Spyder/GTO */
static vtss_rc vtss_phy_init_seq_spyder(vtss_state_t *vtss_state,
                                        vtss_phy_port_state_t *ps,
                                        vtss_port_no_t        port_no)
{
    u16 reg = 0;

    /* Init scripts common to all Octal PHY devices */
    /* BZ 2486/2487 */
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    /* BZ 2112 */
    /* Turn off Carrier Extensions */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    if (ps->type.part_number == VTSS_PHY_TYPE_8538 || ps->type.part_number == VTSS_PHY_TYPE_8558) {
        if (ps->type.revision == 0) { /* VSC8538/58 Rev A */
            /* BZ 2020 */
            VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_27, 0x8000, 0x8000));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_19, 0x0300, 0x0f00));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

            /* BZ 2063 */
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa60c));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa60c));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
            if ((reg & (1 << 3)) == 0) {
                /* !RxTrLock */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0010));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8604));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x00df));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8600));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x00ff));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8600));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8604));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa60c));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa60c));
            }
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

            /* BZ 2069/2086 */
            VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_REG_17E, 0x0000, 0x0001));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg)); /* PHY address at bit 11-15 */
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

            /* BZ 2084 */
            if ((reg & (0x7 << 11)) == 0) {
                VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_GPIO_0, 0x7009)); /*- Hold 8051 in SW Reset,Enable auto incr address and patch clock,Disable the 8051 clock */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5000)); /*- Dummy write to start off */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_11, 0xffff)); /*- Dummy write to start off */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5002)); /*- Dummy write to addr 16384= 02 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5040)); /*- Dummy write to addr 16385= 40 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x500C)); /*- Dummy write to addr 16386= 0C */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5002)); /*- Dummy write to addr 16387= 02 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5040)); /*- Dummy write to addr 16388= 40 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5021)); /*- Dummy write to addr 16389= 21 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5002)); /*- Dummy write to addr 16390= 02 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5040)); /*- Dummy write to addr 16391= 40 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5022)); /*- Dummy write to addr 16392= 22 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5002)); /*- Dummy write to addr 16393= 02 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5040)); /*- Dummy write to addr 16391= 40 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5023)); /*- Dummy write to addr 16392= 23 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50C2)); /*- Dummy write to addr 16396= C2 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50AD)); /*- Dummy write to addr 16397= AD */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50C2)); /*- Dummy write to addr 16396= C2 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50CA)); /*- Dummy write to addr 16399= CA */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5075)); /*- Dummy write to addr 16400= 75 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50CB)); /*- Dummy write to addr 16401= CB */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x509A)); /*- Dummy write to addr 16402= 9A */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5075)); /*- Dummy write to addr 16400= 75 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50CA)); /*- Dummy write to addr 16399= CA */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5046)); /*- Dummy write to addr 16405= 46 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5085)); /*- Dummy write to addr 16406= 85 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50CB)); /*- Dummy write to addr 16401= CB */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50CD)); /*- Dummy write to addr 16408= CD */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5085)); /*- Dummy write to addr 16406= 85 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50CA)); /*- Dummy write to addr 16399= CA */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50CC)); /*- Dummy write to addr 16411= CC */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50D2)); /*- Dummy write to addr 164VTSS_PHY_GPIO_12= D2 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50CA)); /*- Dummy write to addr 16399= CA */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50D2)); /*- Dummy write to addr 16414= D2 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x50AD)); /*- Dummy write to addr 16415= AD */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5022)); /*- Dummy write to addr 16416= 22 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5022)); /*- Dummy write to addr 16416= 22 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5022)); /*- Dummy write to addr 16416= 22 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5022)); /*- Dummy write to addr 16416= 22 */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0000)); /*- Clear internal memory access */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4099)); /*- Allow 8051 to run again, with patch enabled */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc099)); /*- Allow 8051 to run again, with patch enabled */
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            }

            /* BZ 2087 */
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            if (ps->type.part_number == VTSS_PHY_TYPE_8558) {
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa606));    /*- Request read, Media SerDes Control */
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
                reg = (reg & 0xfff8) | 5;                        /*- Optimize sample delay setting */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));    /*- Is this OK? */
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8606));    /* Write Media SerDes Control Word */
            }
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xae06));       /*- Request read, MAC SerDes control */
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
            reg = (reg & 0xfff8) | 5;                           /*- Optimize sample delay setting */
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));       /*- Is this OK? */
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8e06));        /* Write MAC SerDes Control Word */
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        }

        /* BZ 2411 - PLL Error Detector Bit Enable */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_2, 0x8000, 0x8000));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

        /* BZ 2230 - DSP Optimization, BZ 2230 */
        VTSS_RC(vtss_phy_optimize_dsp(vtss_state, port_no));

        /* BZ 1971 */
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0040, 0x0040));

        /* BZ 1860 */
        VTSS_RC(vtss_phy_optimize_receiver_init(vtss_state, port_no));

        /* BZ 2114 */
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xaf82));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
        reg = (reg & 0xffef) | 0;           /*- Enable DFE in 100BT */
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

        /* BZ 2221*/
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, 0x1800, 0x1800));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

        /* BZ 2012 */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x6000, 0x6000));  /* MDI Impedance setting = +2 */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0xa002, 0xe00e));  /* 100-BT Amplitude/Slew Rate Control */
    }   /* (ps->type.part_number == VTSS_PHY_TYPE_8538 || ps->type.part_number == VTSS_PHY_TYPE_8558) */
    else if (ps->type.part_number == VTSS_PHY_TYPE_8658) {
        if (ps->type.revision == 0) {
            /* BZ 2545 */
            /* 100-Base FX Clock Data Recovery Improvement */
            {
                u16 reg17, reg18;

                VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xae0e));
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18));
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, reg18));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, (reg17 & 0xffef)));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8e0e));
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            }
        } /* ps->type.revision == 0 */
    }   /* (ps->type.part_number == VTSS_PHY_TYPE_8658) */

    // Improve 100BASE-TX link startup robustness to address interop issue
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0060));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    if ((!ps->reset.i_cpu_en) && (port_no % 8 == 0)) {
        /* disable iCPU */
        VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
    }


    /* Enable Smart Pre-emphasis */
    VTSS_RC(vtss_phy_enab_smrt_premphasis(vtss_state, port_no));

    return VTSS_RC_OK;
}

/* Init scripts for VSC8601/VSC8641 aka Cooper */
static vtss_rc vtss_phy_init_seq_cooper(vtss_state_t *vtss_state,
                                        vtss_phy_port_state_t *ps,
                                        vtss_port_no_t        port_no)
{
    u16 reg = 0;

    /* BZ 2474 */
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    if (ps->type.revision == 0) {    /*- Rev A */
        /* BZ 2231 */
        VTSS_RC(vtss_phy_optimize_dsp(vtss_state, port_no));

        /* BZ 2253 */
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_REG_17E, 0x0010, 0x0010)); /*- Enab Enh mode for Reg17E chg */
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_REG_17E, 0x0007, 0x0007)); /*- sets the LEDs combine/separate */
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_REG_17E, 0x0000, 0x0010)); /*- sets back to simple mode */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

        /* BZ 2234 */
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, 0x0000, 0x0400));    /*- Port Type #2234 */
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_STD_27, 0x0004, 0x0004));   /*- nVidia Req */
    }

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200)); //Ensure RClk125 enabled even in powerdown

    /* BZ 2644 - Improvement for marginal 10-Base T settings */
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x9e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xdd39));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87aa));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa7b4));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, reg));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
    reg = (reg & ~0x003f) | 0x003c;
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87b4));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa794));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, reg));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
    reg = (reg & ~0x003f) | 0x003e;
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8794));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0xf7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xbe36));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x879e));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa7a0));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, reg));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
    reg = (reg & ~0x003f) | 0x0034;
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x3c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf3cf));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x3c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf3cf));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a4));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x3c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd287));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a6));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa7a8));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, reg));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
    reg = (reg & ~0x0fff) | 0x0125;
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a8));

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200)); //Restore RClk125 gating
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    /* Enable Smart Pre-emphasis */
    VTSS_RC(vtss_phy_enab_smrt_premphasis(vtss_state, port_no));

    return VTSS_RC_OK;
}

/* Init scripts for VSC7385/VSC7388/VSC7395/VSC7398/VSC7389/VSC7390/VSC7391 aka "Luton" family */
static vtss_rc vtss_phy_init_seq_luton(vtss_state_t *vtss_state,
                                       vtss_phy_port_state_t *ps,
                                       vtss_port_no_t        port_no)
{
    /* BZ 1801, 1973 */
    /* 100 Base-TX jumbo frame support */
    VTSS_RC(vtss_phy_optimize_jumbo(vtss_state, port_no));

    /* BZ 2094 */
    /* Insufficient RGMII drive-strength seen especially on long traces */
    if (ps->family != VTSS_PHY_FAMILY_LUTON24) {
        if (ps->reset.mac_if == VTSS_PORT_INTERFACE_RGMII) {
            VTSS_RC(vtss_phy_optimize_rgmii_strength(vtss_state, port_no));
        }
    }

    /* BZ 1682, BZ 2345 */
    /* Enable PLL Error Detector Bit */
    /* Applicable to VSC 7385/7385 Rev A, VSC 7389/90 */
    if ((ps->family == VTSS_PHY_FAMILY_LUTON24) ||
        (ps->family == VTSS_PHY_FAMILY_LUTON && ps->type.revision == 0)) {
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_2, 0x8000, 0x8000));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    }

    /* Applicable to VSC 7385/7388 Rev A*/
    if (ps->family == VTSS_PHY_FAMILY_LUTON && ps->type.revision == 0) {
        /* BZ 1954 */
        /* Tweak 100 Base-TX DSP setting for VGA */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0689));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f92));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));

        /* BZ 1933 */
        /* Kick start Tx line-driver common-mode voltage */
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_23, 0xFF80));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_23, 0x0000));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    }

    /* BZ 2226/2227/2228 - DSP Optimization */
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
    VTSS_RC(vtss_phy_optimize_dsp(vtss_state, port_no));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));

    /* BZ 2095/2107 - DSP short cable optimization */
    VTSS_RC(vtss_phy_optimize_receiver_init(vtss_state, port_no));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));                       /*- Additional Init for parts that */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));  /*- lack Viterbi decoder */
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));                         /*- to prevent DSP drift from */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xb68a));               /*- leading to bit errors */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0003, 0xff07));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x00a2, 0x00ff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968a));

    // Improve 100BASE-TX link startup robustness to address interop issue
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0060));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    /* BZ 1742/1971/2000/2034 */
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0040, 0x0040));

    /* Amplitude/ Z-Cal Adjustments at startup */
    /* These values are start-up values and will get readjusted based on link-up speed */
    if (ps->family == VTSS_PHY_FAMILY_LUTON24) {
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0xa002, 0xe00e));
    } else if (ps->family == VTSS_PHY_FAMILY_LUTON && ps->type.revision == 0) {
        /* BZ 2012 - Applies to VSC 7385/7388 Rev A */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x4000, 0x6000)); /* Trim MDI Termination Impedance */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0xa00e, 0xe00e)); /* Trim 100/1000 Tx amplitude & edge rate */
    } else {
        /* BZ 2043 - Applies to VSC 7385/7388 Rev B and later, VSC 7395/7398 all revs */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_22, 0x0240, 0x0fc0)); /* Trim reference currents */
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x4000, 0x6000)); /* Trim termination impedance */
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0030, 0x0038)); /* 1000-BT Edge Rate Ctrl */
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, 0x2000, 0xe000)); /* Trim 1000 Base-T amplitude */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x8002, 0xe00e)); /* 100-BT Edge Rate Ctrl */
    }

    /* Enable Smart Pre-emphasis */
    VTSS_RC(vtss_phy_enab_smrt_premphasis(vtss_state, port_no));

    return VTSS_RC_OK;
}

/************************************************************************/
/* GPIO control                                                         */
/************************************************************************/
#define comma ,
#define GPIO_NOT_SUPPORTED -1
#define GPIOS_SUPPORT_CNT 14

static vtss_rc vtss_phy_is_gpio_supported(vtss_state_t               *vtss_state,
                                          const vtss_port_no_t       port_no,
                                          const u8                   gpio_no,
                                          gpio_table_t               *gpio_ctrl_table)
{
    vtss_rc   rc;

    static gpio_table_t gpio_ctrl_table_viper[GPIOS_SUPPORT_CNT] = {{13, 0}, {13, 2}, {13, 4}, {13, 6}, {13, 8}, {13, 10}, {13, 12}, {13, 14}, {14, 0}, {14, 2}, {14, 4}, {14, 6}, {14, 14}, {14, 14}}; // See Viper datasheet table 55.
    static gpio_table_t gpio_ctrl_table_viper_2_ports[GPIOS_SUPPORT_CNT] = {{13, 0}, {13, 2}, {GPIO_NOT_SUPPORTED, GPIO_NOT_SUPPORTED},
        {GPIO_NOT_SUPPORTED, GPIO_NOT_SUPPORTED}, {13, 8}, {13, 10}, {GPIO_NOT_SUPPORTED, GPIO_NOT_SUPPORTED}, {GPIO_NOT_SUPPORTED, GPIO_NOT_SUPPORTED}, {14, 0},
        {14, 2}, {14, 4}, {14, 6}, {14, 14}, {14, 14}
    };
    static gpio_table_t gpio_ctrl_table_tesla_8572[GPIOS_SUPPORT_CNT] = {{13, 0}, {13, 2}, {GPIO_NOT_SUPPORTED, GPIO_NOT_SUPPORTED}, {GPIO_NOT_SUPPORTED, GPIO_NOT_SUPPORTED}, {13, 8}, {13, 10}, {GPIO_NOT_SUPPORTED, GPIO_NOT_SUPPORTED}, {GPIO_NOT_SUPPORTED, GPIO_NOT_SUPPORTED}, {14, 0}, {14, 2}, {14, 4}, {14, 6}, {14, 14}, {14, 14}}; // See Tesla 7472 datasheet, table 33.

    static gpio_table_t gpio_ctrl_table_tesla_8574[GPIOS_SUPPORT_CNT] = {{13, 0}, {13, 2}, {13, 4}, {13, 6}, {13, 8}, {13, 10}, {13, 12}, {13, 14}, {14, 0}, {14, 2}, {14, 4}, {14, 6}, {14, 14}, {14, 14}};  // See Tesla 7474 datasheet, table 29.

    if (gpio_no > GPIOS_SUPPORT_CNT) {
        return VTSS_RC_ERR_PHY_GPIO_PIN_NOT_SUPPORTED;
    }

    switch (vtss_state->phy_state[port_no].family) {
    case VTSS_PHY_FAMILY_TESLA:
        VTSS_D("Pointer to gpio_ctrl_table_tesla");
        if ((vtss_state->phy_state[port_no].type.part_number == VTSS_PHY_TYPE_8572) ||
            (vtss_state->phy_state[port_no].type.part_number == VTSS_PHY_TYPE_8552)) {
            memcpy(gpio_ctrl_table, &gpio_ctrl_table_tesla_8572[0], sizeof(gpio_ctrl_table_tesla_8572));
        } else {
            memcpy(gpio_ctrl_table, &gpio_ctrl_table_tesla_8574[0], sizeof(gpio_ctrl_table_tesla_8574));
        }
        break;
    case VTSS_PHY_FAMILY_VIPER:
        VTSS_N("Pointer to gpio_ctrl_table_viper");
        if ((vtss_state->phy_state[port_no].type.part_number == VTSS_PHY_TYPE_8562) ||
            (vtss_state->phy_state[port_no].type.part_number == VTSS_PHY_TYPE_8582)) {
            memcpy(gpio_ctrl_table, &gpio_ctrl_table_viper_2_ports[0], sizeof(gpio_ctrl_table_viper_2_ports));
        } else {
            memcpy(gpio_ctrl_table, &gpio_ctrl_table_viper[0], sizeof(gpio_ctrl_table_viper));
        }
        break;
    default:
        return VTSS_RC_ERR_PHY_GPIO_PIN_NOT_SUPPORTED;
    }

    if (gpio_ctrl_table[gpio_no].reg == GPIO_NOT_SUPPORTED) {
        VTSS_D("GPIO NOT Supported");
        return VTSS_RC_ERR_PHY_GPIO_PIN_NOT_SUPPORTED;
    }

    if ((rc = VTSS_PHY_BASE_PORTS_FOUND) != VTSS_RC_OK) {
        VTSS_I("Base port not found, rc: %d", rc);
        return VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND;
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_gpio_mode_private(vtss_state_t               *vtss_state,
                                          const vtss_port_no_t       port_no,
                                          const u8                   gpio_no,
                                          const vtss_phy_gpio_mode_t mode)
{

    gpio_table_t gpio_ctrl_table[GPIOS_SUPPORT_CNT];
    u8            mode_val = 0x3;

    VTSS_RC(vtss_phy_is_gpio_supported(vtss_state, port_no, gpio_no, &gpio_ctrl_table[0]));

    VTSS_N("GPIO:%d supported, mode:%d", gpio_no, mode);

    switch (mode) {
    case VTSS_PHY_GPIO_OUT:
    case VTSS_PHY_GPIO_IN:
        mode_val = 0x3; // So far all GPIO is set to in/out with the value 0x3 (See datasheet)
        break;
    case VTSS_PHY_GPIO_ALT_0:
        mode_val = 0;
        break;
    case VTSS_PHY_GPIO_ALT_1:
        mode_val = 1;
        break;
    case VTSS_PHY_GPIO_ALT_2:
        mode_val = 2;
        break;
    }

    if (mode == VTSS_PHY_GPIO_ALT_1 || mode == VTSS_PHY_GPIO_ALT_2) {
        // Currently we don't support this
        VTSS_I("MODE-NOT-SUPPORTED: port_no:%d, gpio_no:%d, base port:%d, reg:%d, bit:%d, mode_val:%d, mode:%d", port_no, gpio_no, vtss_state->phy_state[port_no].type.base_port_no, gpio_ctrl_table[gpio_no].reg, gpio_ctrl_table[gpio_no].bit, mode_val, mode);
        return VTSS_RC_ERR_PHY_GPIO_ALT_MODE_NOT_SUPPORTED;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, vtss_state->phy_state[port_no].type.base_port_no));
    VTSS_N("port_no:%d, gpio_no:%d, base port:%d, reg:%d, bit:%d, mode_val:%d, mode:%d", port_no, gpio_no, vtss_state->phy_state[port_no].type.base_port_no, gpio_ctrl_table[gpio_no].reg, gpio_ctrl_table[gpio_no].bit, mode_val, mode);


    // Setup mode
    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, vtss_state->phy_state[port_no].type.base_port_no, VTSS_PHY_PAGE_GPIO comma  gpio_ctrl_table[gpio_no].reg, mode_val << gpio_ctrl_table[gpio_no].bit, 0x3 << gpio_ctrl_table[gpio_no].bit));


    // Setup in or output
    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, vtss_state->phy_state[port_no].type.base_port_no, VTSS_PHY_GPIO_IN_OUT_CONF,
                                    mode == VTSS_PHY_GPIO_OUT ? (1 << gpio_no) : 0, (1 << gpio_no)));

    VTSS_RC(vtss_phy_page_std(vtss_state, vtss_state->phy_state[port_no].type.base_port_no));

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_gpio_get_private(vtss_state_t         *vtss_state,
                                         const vtss_port_no_t port_no,
                                         const u8             gpio_no,
                                         BOOL                 *value)
{
    u16          reg;
    gpio_table_t gpio_ctrl_table[GPIOS_SUPPORT_CNT]; // Dummy, in fact not needed here
    VTSS_RC(vtss_phy_is_gpio_supported(vtss_state, port_no, gpio_no, gpio_ctrl_table));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_INPUT, &reg));
    *value = (((reg >> gpio_no) & 0x1) == 0x1) ? TRUE : FALSE;
    VTSS_N("gpio_no:%d, reg:0x%X, %d, val:%d", gpio_no, reg, ((reg >> gpio_no) & 0x1), *value);
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_gpio_set_private(vtss_state_t         *vtss_state,
                                         const vtss_port_no_t port_no,
                                         const u8             gpio_no,
                                         const BOOL           value)
{

    gpio_table_t gpio_ctrl_table[GPIOS_SUPPORT_CNT]; // Dummy, in fact not needed here
    VTSS_RC(vtss_phy_is_gpio_supported(vtss_state, port_no, gpio_no, gpio_ctrl_table));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    // Setup in or output
    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, vtss_state->phy_state[port_no].type.base_port_no, VTSS_PHY_GPIO_OUTPUT,
                                    value << gpio_no, 1 << gpio_no));

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_iso_set_private(vtss_state_t         *vtss_state,
                                         const vtss_port_no_t port_no,
                                         const BOOL           iso_en)
{

    if(iso_en) {
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                   VTSS_F_PHY_MODE_CONTROL_ISOLATE,
                                   VTSS_F_PHY_MODE_CONTROL_ISOLATE)); // Isolate Mode Enable
    } else {
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                   0,
                                   VTSS_F_PHY_MODE_CONTROL_ISOLATE)); // Isolate Mode Disable
    }

    return VTSS_RC_OK;
}


/************************************************************************/
/* Interrupt functions                                               */
/************************************************************************/

// Function for setting interrupt mask events and includes
//          setting PHY Extended Interrupt mask events (Reg 28E2)
// In - port_no - PHY port number.
static vtss_rc vtss_phy_event_enable_private(vtss_state_t *vtss_state,
                                             const vtss_port_no_t  port_no)
{
    u16     mask = 0;
    u16     mask_cur = 0;
    u16     ext_mask = 0;
    vtss_rc rc = VTSS_RC_OK;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_event_t       ev_mask = ps->ev_mask;
    vtss_phy_conf_t       *conf = &ps->setup;
    u16                    reg = 0;
    vtss_phy_reset_conf_t *reset_conf = &ps->reset;

    //Bugzilla#4467 - Board/interrupt: Rev-B support of Fast Link Fail from internal PHY
    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
        if (ps->type.revision == VTSS_PHY_ATOM_REV_B) {
            if (vtss_state->phy_state[port_no].eee_conf.eee_mode == EEE_ENABLE) {
                ev_mask = 0;     // Disable all interrupts when EEE is enabled due to Bugzilla#4467
                VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_INTERRUPT_MASK, 0));
            }
        }
        break;
    case VTSS_PHY_FAMILY_COBRA:
        VTSS_N("Port:%d  Bugzilla#7489 - Interrupt must be disable when powered down.", port_no);
        if (conf->mode ==  VTSS_PHY_MODE_POWER_DOWN) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_INTERRUPT_MASK, 0x0, 0xFFFF));
            return VTSS_RC_OK;
        }
        break;
    default:
        break;
    }


    VTSS_N("vtss_phy_event_enable_private - ev_mask:0x%X", ev_mask);
    // Exit if this PHY doesn't support interrupts
    if (!vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT)) {
        return (VTSS_RC_ERROR);
    }

    if (ev_mask & VTSS_PHY_LINK_LOS_EV) {
        mask |= VTSS_F_PHY_INTERRUPT_MASK_LINK_MASK;
    }

#ifdef VTSS_SW_OPTION_EEE
    u16     reg_val;
    // Bug in chip. Mask out fast link failure when EEE is included due to bugzilla#2965 & #2966
    VTSS_RC(vtss_phy_mmd_rd(vtss_state, port_no, 7, 60, &reg_val)); // Read current value of the register
    if (ev_mask && (reg_val & 0x0006) && (ps->family == VTSS_PHY_FAMILY_ATOM || ps->family != VTSS_PHY_FAMILY_LUTON26)) { // Do not allow enable if EEE is enabled - Check if advertisement is enabled
    } else
#endif
    {
        if (ev_mask & VTSS_PHY_LINK_FFAIL_EV) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_FAST_LINK_MASK;
            // Work around of Bugzilla#8881, False interrupts when no 100FX SFP module plugged in (Disable fast link interrupt if link is down)
            if (reset_conf->media_if == VTSS_PHY_MEDIA_IF_FI_100FX || reset_conf->media_if == VTSS_PHY_MEDIA_IF_AMS_FI_100FX) {
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_STATUS, &reg));

                // Disable dat link interrupt if link is down.
                if (!(reg & VTSS_F_PHY_STATUS_LINK_STATUS)) {
                    mask &= ~VTSS_F_PHY_INTERRUPT_MASK_FAST_LINK_MASK; // Clear the mask again.

                    // Disable the fast link interrupt
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_INTERRUPT_MASK, 0, VTSS_F_PHY_INTERRUPT_MASK_FAST_LINK_MASK));
                }
                VTSS_D("reg:0x%X, mask:0x%X, port_no:%d", reg, mask, port_no);
            }
        }


        if (ev_mask & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV) {
            if (ps->family == VTSS_PHY_FAMILY_COBRA) {
                VTSS_E("PHY Family %s doesn't support \"Speed state change\" interrupt", vtss_phy_family2txt(ps->family));
            } else {
                mask |= VTSS_F_PHY_INTERRUPT_MASK_SPEED_STATE_CHANGE_MASK;
            }
        }

        if (ev_mask & VTSS_PHY_LINK_FDX_STATE_CHANGE_EV) {
            if (ps->family == VTSS_PHY_FAMILY_COBRA) {
                VTSS_I("PHY Family %s doesn't support \"FDX state change\" interrupt", vtss_phy_family2txt(ps->family));
            } else {
                mask |= VTSS_F_PHY_INTERRUPT_MASK_FDX_STATE_CHANGE_MASK;
            }
        }

        if (ev_mask & VTSS_PHY_LINK_AUTO_NEG_ERROR_EV) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_AUTO_NEG_ERROR_MASK;
        }

        if (ev_mask & VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_AUTO_NEG_COMPLETE_MASK;
        }

        if (ev_mask & VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_INLINE_POW_DEV_DETECT_MASK;
        }

        if (ev_mask & VTSS_PHY_LINK_SYMBOL_ERR_INT_EV) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_SYMBOL_ERR_INT_MASK;
        }

        // This is for compatability with Older 130nm Parts.
        // The 65nm parts do not support these FIFO conditions
        // This is bit masks for bits 5 & 6 which get re-assigned in some 65nm products
        // Note: These two Interrupts, if supported, are in Extended INT Reg
        if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT_FIFO)) {
            if (ev_mask & VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV) {
                mask |= VTSS_F_PHY_INTERRUPT_MASK_TX_FIFO_OVERFLOW_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV) {
                mask |= VTSS_F_PHY_INTERRUPT_MASK_RX_FIFO_OVERFLOW_INT_MASK;
            }
        }

        //   The 65nm parts re-use masks, bit 5 and bit 6
        //   re-use mask bit 6, for WOL
        if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_WOL)) {
            if (ev_mask & VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV) {
                mask |= VTSS_F_PHY_INTERRUPT_MASK_WAKE_ON_LAN_MASK;
            }
        }

        //   The 65nm parts re-use masks, bit 5 and bit 6
        //   There were more than 16 Interrupts, therefore there are other INT Registers to read
        //   This indicates that the Extended Registers need to be read to clear INT
        if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT_EXT)) {
            if (ev_mask & VTSS_PHY_LINK_EXTENDED_REG_INT_EV) {
                mask |= VTSS_F_PHY_INTERRUPT_MASK_EXTENDED_INT_MASK;
            }
        }

        if (ev_mask & VTSS_PHY_LINK_FALSE_CARRIER_INT_EV) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_FALSE_CARRIER_INT_MASK;
        }

        if (ev_mask & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV ) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_LINK_SPEED_DS_DETECT_MASK;
        }

        if (ev_mask & VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_MASTER_SLAVE_RES_ERR_MASK;
        }

        if (ev_mask & VTSS_PHY_LINK_RX_ER_INT_EV) {
            mask |= VTSS_F_PHY_INTERRUPT_MASK_RX_ER_INT_MASK;
        }

        // Extended Int Mask Settings
        if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT_EXT)) {

            if (ev_mask & VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_EEE_WAKE_ERR_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_EEE_RX_TS_TIMER_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_EEE_RX_TQ_TIMER_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_EEE_LINK_FAIL_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_RR_SW_OVER_COMPL_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_MACSEC_HOST_MAC_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_MACSEC_LINE_MAC_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_MACSEC_FLOW_CTL_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_MACSEC_INGRESS_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_MACSEC_EGRESS_INT_MASK;
            }

            if (ev_mask & VTSS_PHY_LINK_EXT_MEM_INT_RING_EV) {
                ext_mask |= VTSS_F_PHY_EXT_INT_MASK_MEM_INTEGRITY_RING_CTL_INT_MASK;
            }
        }
    }

    if (ev_mask & VTSS_PHY_LINK_AMS_EV) {
        if (ps->family == VTSS_PHY_FAMILY_COBRA || ps->family == VTSS_PHY_FAMILY_ENZO) {
            VTSS_D("PHY Family %s doesn't support \"AMS state change\" interrupt or is not in AMS mode", vtss_phy_family2txt(ps->family));
        } else {
            if (!is_phy_in_ams_mode(vtss_state, port_no)) {
                VTSS_I("Note PHY is not in AMS mode, the signal detect pins must not be floating when setting enabling AMS interrupts");
            }
            mask |= VTSS_F_PHY_INTERRUPT_MASK_AMS_MEDIA_CHANGE_MASK;
        }
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    if (ext_mask) {
        mask |= VTSS_F_PHY_INTERRUPT_MASK_EXTENDED_INT_MASK;
    }

    if ((mask) || (ext_mask)) {
        mask |= VTSS_F_PHY_INTERRUPT_MASK_INT_MASK;         /* Add Interrupt Status */
    }

    /* ********************************************************************************************************** */
    //           Viper Rev. B Self-Clearing Interrupt Stuck ON Work-Around
    // Viper Rev_B has a Bug and EXT INT and AMS will not Clear properly (MDINT stays asserted),
    //             resulting in MDINT Stuck ON if these INT's are ever set
    // Therefore, for Viper Rev_B DO NOT Set the EXT INT and AMS Masks, Ensure that they are always Clear!
    // See Bugzilla: 19643: BugZero#73794:Extended interrupt status is always high, not self clearing after read
    // Work-Around: Ext INT Mask Reg28E2 is still set properly by API.
    //     However, Ext INT Status Reg29E2 will have to be polled by the Customer Application
    /* ********************************************************************************************************** */
    if ((ps->family == VTSS_PHY_FAMILY_VIPER) && (ps->type.revision == VTSS_PHY_VIPER_REV_B)) {
        // Keep Reg25.5 and Reg25.4 clear for Viper Rev. B
        ps->ev_mask &= ~(VTSS_PHY_LINK_EXTENDED_REG_INT_EV | VTSS_PHY_LINK_AMS_EV);
        mask &= ~(VTSS_F_PHY_INTERRUPT_MASK_EXTENDED_INT_MASK | VTSS_F_PHY_INTERRUPT_MASK_AMS_MEDIA_CHANGE_MASK);
        if ((mask & ~(VTSS_F_PHY_INTERRUPT_MASK_INT_MASK)) == 0) {  // If the only thing left ON in Reg25 is MDINT, turn MDINT OFF for Rev.B
            mask &= ~(VTSS_F_PHY_INTERRUPT_MASK_INT_MASK);
        }
        VTSS_I("VIPER_Rev_B_WorkAround_Enabled: Masking OFF EXT INT and AMS INT Events in Reg25: ev_mask:0x%X", mask);
    }

    /* Read the Current mask.  We want to Clear existing bits, As well as set bits that are being passed in */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_INTERRUPT_MASK, &mask_cur));
    mask_cur |= mask;
    VTSS_N("Setting Int_Mask: port_no:%d, ev_mask:0x%X, mask:0x%X, mask_cur: 0x%X", port_no, ev_mask, mask, mask_cur);
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_INTERRUPT_MASK, mask, mask_cur));
    ps->int_mask_reg = mask;

    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_INTERRUPT_MASK, &mask_cur));
    mask_cur |= ext_mask;
    VTSS_N("Setting Ext_Int_Mask: port_no:%d, ev_mask:0x%X, mask:0x%X, ext_mask: 0x%X;  ext_mask_cur: 0x%X", port_no, ev_mask, mask, ext_mask, mask_cur);
    if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT_EXT)) {
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_INTERRUPT_MASK, ext_mask, mask_cur));
    }
    ps->ext_int_mask_reg = ext_mask;

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return rc;
}

// Function for getting the interrupt events status and includes
//          getting PHY Extended Interrupt events (Reg 29E2)

static vtss_rc vtss_phy_event_poll_private(vtss_state_t *vtss_state,
                                           const vtss_port_no_t  port_no,
                                           vtss_phy_event_t      *const events)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16     pending, mask;
    vtss_rc rc = VTSS_RC_OK;

    *events = 0;

    if (!vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT)) {
        return VTSS_RC_ERROR;
    }
        rc = vtss_phy_page_std(vtss_state, port_no);
        rc = PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_INTERRUPT_STATUS, &pending); /* Pending is cleared by read */
        //rc = PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_INTERRUPT_MASK, &mask);
        mask = vtss_state->phy_state[port_no].int_mask_reg;

        VTSS_N("port_no:%d, pending:0x%X, mask:0x%X", port_no, pending, mask);

        pending &= ~VTSS_F_PHY_INTERRUPT_MASK_INT_MASK; /* pending on 'Interrupt Status' is not included */
        pending &= mask; /* Only include enabled interrupts */

        if (pending) {
            if (pending & VTSS_F_PHY_INTERRUPT_MASK_LINK_MASK) {
                *events |= VTSS_PHY_LINK_LOS_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_FAST_LINK_MASK) {
                *events |= VTSS_PHY_LINK_FFAIL_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_AMS_MEDIA_CHANGE_MASK) {
                *events |= VTSS_PHY_LINK_AMS_EV;
                /*-  Start of TESLA_AMS_WORK_AROUND_100FX_RJ45 */
                if (ps->family == VTSS_PHY_FAMILY_TESLA) {
                    u16  reg = 0;
                    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, &reg));
                    if (reg & VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_ENABLED) {  /* Is AMS Set for this port, bit 10: 0x0400 ? */
                        u16   regVal = 0x1000; /* Default for 100FX - AMS */
                        if (!(reg & VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE)) {  /* AMS Set for Fibre Preference */
                            reg = (reg & VTSS_M_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE) >> 8;
                            if (reg == 7) {  /* Only for AMS - 100FX */
                                VTSS_D("port_no:%d AMS Mode, Force 100FX", port_no);
                                VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, regVal, regVal));
                            }
                        }
                    }
                } /*-  End of TESLA_AMS_WORK_AROUND_100FX_RJ45 */
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_SPEED_STATE_CHANGE_MASK) {
                *events |= VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_FDX_STATE_CHANGE_MASK) {
                *events |= VTSS_PHY_LINK_FDX_STATE_CHANGE_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_AUTO_NEG_ERROR_MASK) {
                *events |= VTSS_PHY_LINK_AUTO_NEG_ERROR_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_AUTO_NEG_COMPLETE_MASK) {
                *events |= VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_INLINE_POW_DEV_DETECT_MASK) {
                *events |= VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_SYMBOL_ERR_INT_MASK) {
                *events |= VTSS_PHY_LINK_SYMBOL_ERR_INT_EV;
            }

            // This is for compatability with Older 130nm Parts.
            // The 65nm parts do not support these FIFO conditions
            // This is bit masks for bits 5 & 6 which get re-assigned in some 65nm
            if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT_FIFO)) {
                if (pending & VTSS_F_PHY_INTERRUPT_MASK_TX_FIFO_OVERFLOW_INT_MASK) {
                    *events |= VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV;
                }

                if (pending & VTSS_F_PHY_INTERRUPT_MASK_RX_FIFO_OVERFLOW_INT_MASK) {
                    *events |= VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV;
                }
            }

            //   The 65nm parts re-use these masks, bit 6
            if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_WOL)) {
                if (pending & VTSS_F_PHY_INTERRUPT_MASK_WAKE_ON_LAN_MASK) {
                    *events |= VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV;
                }
            }

            //   The 65nm parts re-use these masks, bit 5
            //   There were more than 16 Interrupts, therefore there are other INT Registers to read
            //   This indicates that the Extended Registers need to be read to clear INT
            if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT_EXT)) {
                if (pending & VTSS_F_PHY_INTERRUPT_MASK_EXTENDED_INT_MASK) {
                    *events |= VTSS_PHY_LINK_EXTENDED_REG_INT_EV;
                }
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_FALSE_CARRIER_INT_MASK) {
                *events |= VTSS_PHY_LINK_FALSE_CARRIER_INT_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_LINK_SPEED_DS_DETECT_MASK) {
                *events |= VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_MASTER_SLAVE_RES_ERR_MASK) {
                *events |= VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV;
            }

            if (pending & VTSS_F_PHY_INTERRUPT_MASK_RX_ER_INT_MASK) {
                *events |= VTSS_PHY_LINK_RX_ER_INT_EV;
            }
        }

        /* ********************************************************************************************************** */
        //           Viper Rev. B Self-Clearing Interrupt Stuck ON Work-Around
        // Viper Rev_B has a Bug and EXT INT and AMS will not Clear properly (MDINT stays asserted),
        //             resulting in MDINT Stuck ON if these INT's are ever set
        // Therefore, for Viper Rev_B DO NOT Set the EXT INT and AMS Masks, Ensure that they are always Clear!
        //
        // See Bugzilla: 19643: BugZero#73794:Extended interrupt status is always high, not self clearing after read
        // NOTE: Since the Ext INT Mask is NOT set for Viper Rev B in vtss_phy_event_enable_private(), There is no work-around here.
        //
        // Work-Around: Ext INT Mask Reg28E2 is still set properly by API.
        //     However, Ext INT Status Reg29E2 will have to be polled by the Customer Application
        //     An API has been created to directly poll Reg29E2 which will be called by Customer Application
        /* ********************************************************************************************************** */

        // Check for Extended Interrupts
        if ((*events & VTSS_PHY_LINK_EXTENDED_REG_INT_EV) || (ps->type.revision == VTSS_PHY_VIPER_REV_B)) {
            pending = 0;
            VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
            rc = PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_INTERRUPT_STATUS, &pending); /* Pending is cleared by read */
            mask = vtss_state->phy_state[port_no].ext_int_mask_reg;

            VTSS_N("port_no:%d, EXT_INT pending:0x%X, mask:0x%X", port_no, pending, mask);

            pending &= mask; /* Only include enabled interrupts */

            if (pending & VTSS_F_PHY_EXT_INT_MASK_EEE_WAKE_ERR_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_EEE_RX_TS_TIMER_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_EEE_RX_TQ_TIMER_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_EEE_LINK_FAIL_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_RR_SW_OVER_COMPL_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_HOST_MAC_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_LINE_MAC_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_FLOW_CTL_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_INGRESS_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_EGRESS_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV;
            }

            if (pending & VTSS_F_PHY_EXT_INT_MASK_MEM_INTEGRITY_RING_CTL_INT_MASK) {
                *events |= VTSS_PHY_LINK_EXT_MEM_INT_RING_EV;
            }
        }

        VTSS_N("port_no:%d, ev_mask:0x%X", port_no, *events);

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return rc;
}


/* ********************************************************************************************************** */
//           Viper Rev. B Self-Clearing Interrupt Stuck ON Work-Around
// Viper Rev_B has a Bug and EXT INT and AMS will not Clear properly (MDINT stays asserted),
//             resulting in MDINT Stuck ON if these INT's are ever set
// Therefore, for Viper Rev_B DO NOT Set the EXT INT and AMS Masks, Ensure that they are always Clear!
//
// See Bugzilla: 19643: BugZero#73794:Extended interrupt status is always high, not self clearing after read
// NOTE: Since the Ext INT Mask is NOT set for Viper Rev B in vtss_phy_event_enable_private(), There is no work-around here.
//
// Work-Around: Ext INT Mask Reg28E2 is still set properly by API.
//     However, Ext INT Status Reg29E2 will have to be polled by the Customer Application
//     An API (vtss_phy_ext_event_poll) has been created to directly poll Reg29E2 which will be called by Customer Application
/* ********************************************************************************************************** */

// Function for getting the Extended interrupt events status(Reg 29E2)
static vtss_rc vtss_phy_ext_event_poll_private(vtss_state_t *vtss_state,
                                               const vtss_port_no_t  port_no,
                                               vtss_phy_event_t      *const events)
{
    u16     pending, mask;
    vtss_rc rc = VTSS_RC_OK;

    *events = 0;

    if (!vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT)) {
        return VTSS_RC_ERROR;
    }

    pending = 0;
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    rc = PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_INTERRUPT_STATUS, &pending); /* Pending is cleared by read */
    mask = vtss_state->phy_state[port_no].ext_int_mask_reg;

    VTSS_N("port_no:%d, EXT_INT pending:0x%X, mask:0x%X", port_no, pending, mask);

    pending &= mask; /* Only include enabled interrupts */

    if (pending == 0) {
        return VTSS_RC_OK;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_EEE_WAKE_ERR_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_EEE_RX_TS_TIMER_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_EEE_RX_TQ_TIMER_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_EEE_LINK_FAIL_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_RR_SW_OVER_COMPL_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_HOST_MAC_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_LINE_MAC_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_FLOW_CTL_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_INGRESS_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_MACSEC_EGRESS_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV;
    }

    if (pending & VTSS_F_PHY_EXT_INT_MASK_MEM_INTEGRITY_RING_CTL_INT_MASK) {
        *events |= VTSS_PHY_LINK_EXT_MEM_INT_RING_EV;
    }

    VTSS_N("port_no:%d, ev_mask:0x%X", port_no, *events);
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return rc;
}



/************************************************************************/
/* Reset functions                                               */
/************************************************************************/

// Function for setting phy in pass through mode according to "Application Note : Protocol transfer mode guide"
static vtss_rc vtss_phy_pass_through_speed_mode(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_conf_t       *setup_conf = &ps->setup;

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
        // From Protocol Transfer mode Guide (Written by James McIntosh and Jim Barnette)
        VTSS_I("Port:%d: Pass through mode setting mode:%d, speed:%d", port_no, setup_conf->mode, setup_conf->forced.speed);

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        //Protocol Transfer mode Guide : Section 4.1.1 - Aneg must be enabled
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA, VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA));

        VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));

        // Default clear "force advertise ability" bit as well
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MAC_SERDES_PCS_CONTROL,
                                        VTSS_F_MAC_SERDES_PCS_CONTROL_ANEG_ENA,
                                        VTSS_F_MAC_SERDES_PCS_CONTROL_ANEG_ENA | VTSS_F_MAC_SERDES_PCS_CONTROL_FORCE_ADV_ABILITY));

        // Protocol Transfer mode Guide : Section 4.1.3
        if (setup_conf->mode == VTSS_PHY_MODE_FORCED) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MAC_SERDES_PCS_CONTROL, VTSS_F_MAC_SERDES_PCS_CONTROL_FORCE_ADV_ABILITY, VTSS_F_MAC_SERDES_PCS_CONTROL_FORCE_ADV_ABILITY));

            switch (setup_conf->forced.speed) {
            case VTSS_SPEED_100M:
                VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_MAC_SERDES_CLAUSE_37_ADVERTISED_ABILITY, 0x8401));
                break;

            case VTSS_SPEED_10M:
                VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_MAC_SERDES_CLAUSE_37_ADVERTISED_ABILITY, 0x8001));
                break;

            case VTSS_SPEED_1G:
                VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_MAC_SERDES_CLAUSE_37_ADVERTISED_ABILITY, 0x8801));
                break;

            default:
                VTSS_E("Unexpected port speed:%d defaulting to 1G", setup_conf->forced.speed);
                VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_MAC_SERDES_CLAUSE_37_ADVERTISED_ABILITY, 0x8801));
                break;
            }
        }

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        /* Restart ANEG to ensure that the Cu SFP sends Idle and config code words to the MAC */
        /* But, We ONLY want to restart ANEG if this is the FIRST Time configuring CuSFP      */
        /* Otherwise, Link will drop temporarily if we restart ANEG                           */
        if (vtss_state->sync_calling_private) {  // Warm-Start
            ps->cu_sfp_config_complete = TRUE;
        } else {
            // This is for the VSC PHY, NOT the PHY in the CuSFP Module!
            // Restart Auto-negotiation - However, We only want to restart ANEG the very first time we switch into Pass-Thru Mode
            // If we are already in Pass-Thru mode and there is a Speed Change or if the user just re-applies curr config, do not Force ANEG
            if (!ps->cu_sfp_config_complete && ps->setup.mode == VTSS_PHY_MODE_ANEG) {
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                                VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG,
                                                VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG));

                ps->cu_sfp_config_complete = TRUE;
                VTSS_D("Port:%d: SFP Pass-Through Mode, Force ANEG Restart; PHY_MODE_CONTROL_RESTART_AUTO_NEG ", port_no);
            }
        }
        break;

    default:
        VTSS_D("Port:%d: All other PHYs don't need this or are not supporting SFP pass through mode.", port_no);
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_gp_reg_rd(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 *value)
{
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 30, value));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_gp_reg_wr(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 value)
{
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(vtss_phy_wr(vtss_state, port_no, 30, value));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_detect_base_ports_private(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_x, port_y = 0, base_port_no, base_port_1588inst0, base_port_1588inst1;
    BOOL           port_skip[VTSS_PORTS], port_phy[VTSS_PORTS];
    u16            gp_reg[VTSS_PORTS], gp_x, gp_y, addr, addr_min;
    u8             port_addr[VTSS_PORTS];

    /* Read and clear GP register for all ports */
    for (port_x = 0; port_x < vtss_state->port_count; port_x++) {
        gp_reg[port_x] = 0; /* Just to please Lint */
        port_skip[port_x] = 1;
        switch (vtss_state->phy_state[port_x].family) {
        case VTSS_PHY_FAMILY_TESLA:
        case VTSS_PHY_FAMILY_ATOM:
        case VTSS_PHY_FAMILY_ENZO:
        case VTSS_PHY_FAMILY_LUTON26:
        case VTSS_PHY_FAMILY_VIPER:
        case VTSS_PHY_FAMILY_ELISE:
        case VTSS_PHY_FAMILY_NANO :
            if (vtss_phy_gp_reg_rd(vtss_state, port_x, &gp_reg[port_x]) == VTSS_RC_OK &&
                vtss_phy_gp_reg_wr(vtss_state, port_x, 0) == VTSS_RC_OK) {
                port_skip[port_x] = 0;
            }
        default:
            break;
        }
    }

    /* Write unique value to GP register using broadcast write (register 22) */
    for (port_x = 0; port_x < vtss_state->port_count; port_x++) {
        if (port_skip[port_x]) {
            continue;
        }
        VTSS_RC(vtss_phy_wr_masked(vtss_state, port_x, 22, 0x0001, 0x0001));  /* Broadcast Write */
        VTSS_RC(vtss_phy_gp_reg_wr(vtss_state, port_x, 0x0100 + port_x));
        VTSS_N("vtss_phy_detect_base_ports_private: port_x: %d Broadcast Write to 30E1: %x ", port_x, 0x0100 + port_x);
        VTSS_RC(vtss_phy_wr_masked(vtss_state, port_x, 22, 0x0000, 0x0001));
    }

    /* Find base port for each PHY */
    for (port_x = 0; port_x < vtss_state->port_count; port_x++) {
        if (port_skip[port_x] || vtss_phy_gp_reg_rd(vtss_state, port_x, &gp_x) != VTSS_RC_OK) {
            VTSS_N("vtss_phy_detect_base_ports_private: SKIPPING Port: port_skip[%d] = %x", port_x, port_skip[port_x]);
            continue;
        }

        base_port_no = VTSS_PORT_NO_NONE;
        base_port_1588inst0 = VTSS_PORT_NO_NONE;
        base_port_1588inst1 = VTSS_PORT_NO_NONE;
        addr_min = 0xffff;
        for (port_y = port_x; port_y < vtss_state->port_count; port_y++) {
            port_phy[port_y] = 0;
            port_addr[port_y] = 0xff;
            if (!port_skip[port_y] &&
                vtss_phy_gp_reg_rd(vtss_state, port_y, &gp_y) == VTSS_RC_OK &&
                gp_x == gp_y) {
                /* Found port_x and port_y on same PHY */
                port_phy[port_y] = 1;
                if (vtss_phy_page_ext(vtss_state, port_y) == VTSS_RC_OK &&
                    vtss_phy_rd(vtss_state, port_y, 23, &addr) == VTSS_RC_OK &&
                    vtss_phy_page_std(vtss_state, port_y) == VTSS_RC_OK) {
                    /* Base port has smallest PHY address (register 23E1) */
                    if (addr <= addr_min) {
                        addr_min = addr;
                        base_port_no = port_y;
                    }
                    if (((vtss_state->phy_state[port_y].family) == VTSS_PHY_FAMILY_TESLA) ||
                        ((vtss_state->phy_state[port_y].family) == VTSS_PHY_FAMILY_VIPER)) {
                        port_addr[port_y] = (addr & 0x1800) >> 11;
                        if (port_addr[port_y] == 0) {
                            base_port_1588inst0 = port_y;
                            VTSS_N("vtss_phy_detect_base_ports_private: 1588Inst0: Port: %d ", port_y);
                        }
                        if (port_addr[port_y] == 1) {
                            base_port_1588inst1 = port_y;
                            VTSS_N("vtss_phy_detect_base_ports_private: 1588Inst1: Port: %d ", port_y);
                        }
                    }
                }
            }
        }
        /* Save 1588 base port for all ports on PHY */
        for (port_y = port_x; port_y < vtss_state->port_count; port_y++) {
            if (((vtss_state->phy_state[port_y].family) == VTSS_PHY_FAMILY_TESLA) ||
                ((vtss_state->phy_state[port_y].family) == VTSS_PHY_FAMILY_VIPER)) {
                if (port_phy[port_y]) {
                    /* Base port was found */
                    if ((port_addr[port_y] == 0) || (port_addr[port_y] == 2)) {
                        vtss_state->phy_state[port_y].type.phy_api_base_no = base_port_1588inst0;
                        VTSS_D("port: %u, 1588 base: %u", port_y, base_port_1588inst0);
                    } else if ((port_addr[port_y] == 1) || (port_addr[port_y] == 3)) {
                        vtss_state->phy_state[port_y].type.phy_api_base_no = base_port_1588inst1;
                        VTSS_D("port: %u, 1588 base: %u", port_y, base_port_1588inst1);
                    }
                }
            }
        }

        /* Save base port for all ports on PHY */
        for (port_y = port_x; port_y < vtss_state->port_count; port_y++) {
            if (port_phy[port_y]) {
                /* Base port was found */
                VTSS_D("port: %u, base: %u", port_y, base_port_no);
                vtss_state->phy_state[port_y].type.base_port_no = base_port_no;
                port_skip[port_y] = 1;
            }
        }

        /* Restore GP register */
        VTSS_RC(vtss_phy_gp_reg_wr(vtss_state, port_x, gp_reg[port_x]));
    }
    vtss_state->phy_inst_state.base_ports_found = TRUE; // Signaling that base port found (mainly for the 6g macro configuration setup)
    VTSS_D("port: %u, base_ports_found: %x    base_port_no: 0x%x\n", port_x, vtss_state->phy_inst_state.base_ports_found,
             vtss_state->phy_state[port_y].type.base_port_no);

    return VTSS_RC_OK;
}


// Function that is called at boot, after port reset.
// The function is calling the post initialization script (setting coma).
// IN : port_no - Any port within the chip.
vtss_rc vtss_phy_post_reset_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO :
        /* COMA mode should only be changed during COLD Start - not during phy_sync of WARMSTART */
        if (vtss_state->sync_calling_private == FALSE) {
            vtss_phy_conf_t       *conf = &ps->setup;
            /* COMA Mode API are not affected: vtss_phy_coma_mode_disable and vtss_phy_coma_mode_enable */
            /* FPGA or other device can override the Default behavior and SKIP Automatic config here */
            if (conf->skip_coma) {
                VTSS_I("Skipping config of COMA_MODE in POST_RESET, port = %d", port_no);
            } else {
                VTSS_I("Applying COMA_MODE Default (Disable) in POST_RESET, port = %d", port_no);
                VTSS_RC(vtss_phy_coma_mode_private(vtss_state, port_no, TRUE));
            }
        }
        break;
    default:
        VTSS_D("No post-initialising needed for family:%s, port = %d",
               vtss_phy_family2txt(ps->family), port_no);
    }
    return VTSS_RC_OK;
}


static vtss_rc vtss_phy_mac_media_if_enzo_setup(vtss_state_t *vtss_state,
                                                const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    u16 reg = 0;

    switch (conf->mac_if) {
    case VTSS_PORT_INTERFACE_SGMII:
        reg = ((0 << 13) | (0 << 12)); /* SGMII, auto negotiation disabled */
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            reg |= (0 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
            reg |= (1 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
            reg |= (2 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_FI_100FX:
            reg |= (3 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
            reg |= (1 << 11)  |  (5 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
            reg |= (0 << 11) | (5 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
            reg |= (1 << 11) | (6 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
            reg |= (0 << 11) | (6 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
            reg |= (1 << 11) | (7 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
            reg |= (0 << 11) | (7 << 8);
            break;
        default:
            VTSS_E("port_no %u, Media interface %d not supported", port_no, conf->media_if);
            return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
        }
        break;

    case VTSS_PORT_INTERFACE_SERDES:
        reg = ((0 << 13) | (1 << 12));
        switch (conf->media_if) {
        case VTSS_PHY_MEDIA_IF_CU:
            reg |= (0 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
            reg |= (1 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
            reg |= (2 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
            reg |= (1 << 11) | (5 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
            reg |= (0 << 11) | (5 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
            reg |= (1 << 11) | (6 << 8);
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
            reg |= (0 << 11) | (6 << 8);
            break;
        default:
            VTSS_E("port_no %u, Media interface %d not supported", port_no, conf->media_if);
            return VTSS_RC_ERR_PHY_MEDIA_IF_NOT_SUPPORTED;
        }
        break;

    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        reg |= (0 << 11) | (8 << 8); // Setting to Reserved. Shouldn't matter since there is no "interface" for this port
        break;


    default:
        VTSS_E("port_no %u, MAC interface %s not supported",
               port_no, vtss_port_if_txt(conf->mac_if));
        return VTSS_RC_ERROR;
    }

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, reg));
    return VTSS_RC_OK;
}


/* Init scripts for VSC8634-VSC8664 aka "Enzo" family */
static vtss_rc vtss_phy_init_seq_enzo(vtss_state_t *vtss_state,
                                      vtss_phy_port_state_t *ps,
                                      vtss_port_no_t        port_no)
{
    u16 reg = 0;

    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg)); /* PHY address at bit 11-15 */
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    /* BZ 2633 */
    /* Enable LED blinking after reset */
    /* BZ 15809 */
    /* Move the BZ 2633 fix outside the Broadcast, this effects SigDet polarity */
    /* if ports after 0 have different config for SigDet polarity, broadcasting Port 0 config wipes it out */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL, 0x0800, 0x0800));

    /* Script runs only for the first port of each device in system */
    if ((reg & (0x3 << 11)) == 0) {
        /* Enable Broad-cast writes for this device */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001));

        if (ps->type.revision == 0) {    /*- Rev A */
            /* BZ 2637 */
            /* 100/1000 Base-T amplitude compenstation */
            VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0003, 0x0007)); // ->(val & ~mask) | (*value & mask) i.e (value at 24 & 0xfff8) | (0x0003 & 0x0007)
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x0004, 0x000e)); // ->(val & ~mask) | (*value & mask) i.e(value at 24 & 0xfff1) | (0x0004 & 0x000e)

            /* BZ 2639 / BZ 2642 */
            /* Improve robustness of 10Base-T performance */
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3f));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8794));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0xf7));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xadb4));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x879e));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x32));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a0));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x41));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x410));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a2));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x41));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x410));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a4));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x41));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x284));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a6));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x92));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xbcb8));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87a8));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x3));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xcfbf));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87aa));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x49));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2451));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87ac));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x1));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1410));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87c0));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x10));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb498));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87e8));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x71));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xe7dd));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87ea));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x69));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x6512));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87ec));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x49));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2451));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87ee));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x45));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x410));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87f0));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x41));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x410));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87f2));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x10));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87f4));

            VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_9, 0x0040, 0x0040));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_22, 0x0010, 0x0010));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

            /* BZ 2643 */
            /* Performance optimization - 100Base-TX/1000Base-T slave */
            VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_0, 0x0060, 0x00e0));
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x12));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x480a));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x422));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f86));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x3c));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3800));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f8a));

            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x8));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xe33f));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83ae));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        }   /*- Rev A */

        /* BZ 2112 */
        /* Turn off Carrier Extensions */
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, 0x8000, 0x8000));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

        /* Turn-off broad-cast writes for this device */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001));
    }   /* ps->map.addr % 4) == 0 */

    if ((!ps->reset.i_cpu_en) && (port_no % 4 == 0)) {
        /* disable iCPU */
        VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_phy_1g_init_conf_set(vtss_state_t *vtss_state)
{
    vtss_init_conf_t *conf = &vtss_state->init_conf;
    vtss_port_no_t   port_no = conf->restart_info_port;
    u16              reg;
    u32              value;
    VTSS_D("vtss_phy_init_conf_set, port_no:%d", port_no);

    if (conf->restart_info_src == VTSS_RESTART_INFO_SRC_CU_PHY &&
        vtss_phy_detect(vtss_state, port_no) == VTSS_RC_OK &&
        vtss_state->phy_state[port_no].family != VTSS_PHY_FAMILY_NONE) {
            /* Get restart information from Vitesse 1G PHY */
            VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg)); /* 16 MSB at register 29E1 */
            value = reg;
            value = (value << 16);
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, &reg)); /* 16 LSB at register 30E1 */
            value += reg;
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            VTSS_RC(vtss_cmn_restart_update(vtss_state, value));
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_mac_media_inhibit_odd_start_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no, BOOL mac_inhibit_oddst, BOOL media_inhibit_oddst)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16                    regVal = 0;
    BOOL                   viper_rev_a = FALSE;
    /* -- Step 2: Pre-reset setup of MAC and Media interface -- */
    switch (ps->family) {

    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
        viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A); // Viper and Elise have the same Rev for Rev A.

        if (viper_rev_a) {
            //BugZilla 16631 - Interop Issue with Freescale MAC; Work-Around API Resolution: Reg23E3.4=0
            VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
            // Reg16E3.2 = 0 -- Clear Inhibit MAC Odd Start Delay

            regVal = (mac_inhibit_oddst ? VTSS_F_MAC_SERDES_PCS_CONTROL_INHIBIT_MAC_ODD_START_DELAY : 0);
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MAC_SERDES_PCS_CONTROL, regVal,
                                       VTSS_F_MAC_SERDES_PCS_CONTROL_INHIBIT_MAC_ODD_START_DELAY));

            ps->setup.mac_if_pcs.inhibit_odd_start = mac_inhibit_oddst;
            // Reg23E3.4 = 0 -- Clear Inhibit MEDIA Odd Start Delay
            regVal = (media_inhibit_oddst ? VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_INHIBIT_ODD_START_DELAY : 0);
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_CONTROL, regVal,
                                       VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_INHIBIT_ODD_START_DELAY));

            ps->setup.media_if_pcs.inhibit_odd_start = media_inhibit_oddst;

            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        }
        break;

    default:
        break;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_phy_restart_conf_set(vtss_state_t *vtss_state)
{
    vtss_init_conf_t *conf = &vtss_state->init_conf;
    vtss_port_no_t   port_no = conf->restart_info_port;
    u16              reg;
    u32              value;

    if (conf->restart_info_src == VTSS_RESTART_INFO_SRC_CU_PHY &&
        vtss_state->phy_state[port_no].family != VTSS_PHY_FAMILY_NONE) {
        /* Set restart information in Vitesse 1G PHY */
        value = vtss_cmn_restart_value_get(vtss_state);
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        reg = ((value >> 16) & 0x7fff); /* Bit 15 must be zero to disable EPG */
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, reg)); /* 16 MSB at register 29E1 */
        reg = (value & 0xffff);
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, reg)); /* 16 LSB at register 30E1 */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_phy_reset_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *conf = &ps->reset;
    u16                    reg;
    BOOL                   force_reset = TRUE;


#if defined(VTSS_FEATURE_MACSEC)
    if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC)) {
        if (vtss_state->macsec_conf[port_no].glb.init.enable) {
            VTSS_I("Stopping MACsec and MAC traffic port_no %u\n", port_no);
            VTSS_RC(vtss_macsec_drop_all_traffic_priv(vtss_state, port_no));
            VTSS_RC(phy_10g_mac_conf(vtss_state, port_no, 0, 1));
        }
    }
#endif

    // Don't signal link down if doing warm start
    if (!vtss_state->sync_calling_private) {

        // If the link is up we have to remember that link has been down due to port reset.
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_STATUS, &reg));

        if (reg & VTSS_F_PHY_STATUS_LINK_STATUS) {
            ps->link_down_due_to_port_reset = TRUE;
            VTSS_D("link_down_due_to_port_reset = TRUE, port_no = %d", port_no);
        } else {
            VTSS_D("link_down_due_to_port_reset = FALSE, port_no = %d", port_no);
            ps->link_down_due_to_port_reset = FALSE;
        }
    }

    /* -- Step 2: Pre-reset setup of MAC and Media interface -- */
    switch (ps->family) {
    case VTSS_PHY_FAMILY_MUSTANG:
        /* TBD */
        break;
    case VTSS_PHY_FAMILY_BLAZER:
        /* Interface is setup after reset */
        if (ps->type.revision < 4 || ps->type.revision > 6) {
            VTSS_E("port_no %u, unsupported Blazer revision: %u", port_no, ps->type.revision);
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_PHY_FAMILY_COBRA:
        VTSS_RC(vtss_phy_mac_media_if_cobra_setup(vtss_state, port_no, conf));
        break;
    case VTSS_PHY_FAMILY_QUATTRO:
        VTSS_RC(vtss_phy_mac_media_if_quattro_setup(vtss_state, port_no, conf));
        break;
    case VTSS_PHY_FAMILY_SPYDER:
        if (ps->type.revision == 0) {
            /* BZ 2027 */
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4c19));
            VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        }
        VTSS_RC(vtss_phy_mac_media_if_spyder_gto_setup(vtss_state, port_no, conf, ps->type));
        break;
    case VTSS_PHY_FAMILY_ENZO:
        VTSS_RC(vtss_phy_mac_media_if_enzo_setup(vtss_state, port_no, conf));
        break;
    case VTSS_PHY_FAMILY_COOPER: {
        u16 tx_clk_skew, rx_clk_skew;
        reg = 0;
        switch (conf->rgmii.tx_clk_skew_ps) {
        // Setting 0 - disabled RGMII skew compensation (0 ps of skew)
        case 0 :
            rx_clk_skew = 0;
            tx_clk_skew = 0;
            break;
        // Setting 1 - enabled RGMII skew compensation at low delay of approximately 1400 ps of skew (original target was 1.5 ns)
        case 1400 :
            rx_clk_skew = 1;
            tx_clk_skew = 1;
            break;
        case 1700:
            // Setting 2 - enabled RGMII skew compensation at medium delay of approximately 1700 ps of skew (original target was 2.0 ns)
            rx_clk_skew = 2;
            tx_clk_skew = 2;
            break;
        default :
            // Setting 3 - enabled RGMII skew compensation at high delay of approximately 2000 ps of skew (original target was 2.5 ns)
            rx_clk_skew = 3;
            tx_clk_skew = 3;
            break;
        }

        reg = tx_clk_skew << 14 | rx_clk_skew << 12;
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg, 0xf000));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        break;
    }
    case VTSS_PHY_FAMILY_LUTON:
    case VTSS_PHY_FAMILY_LUTON24:
    case VTSS_PHY_FAMILY_LUTON_E:
        switch (conf->mac_if) {
        case VTSS_PORT_INTERFACE_INTERNAL:
            /* Register 23 is setup correctly by default */
            break;
        default:
            VTSS_E("port_no %u, MAC interface %s not supported for SparX",
                   port_no, vtss_port_if_txt(conf->mac_if));
            return VTSS_RC_ERROR;
        }
        break;

    case VTSS_PHY_FAMILY_LUTON26:
        //  There is logic that was attempting to keep the SMI from interfering with the micro access to token-ring registers.
        // We need to disable this logic as it appears to be causing problems. To disable this token-ring access blocking mechanism,
        // set bit 3 of register 28TP (page 0x2a30).
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_28, 0x8 , 0x8));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ATOM:
        VTSS_RC(vtss_phy_mac_media_if_atom_setup(vtss_state, port_no, conf));
        break;

    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
        VTSS_RC(vtss_phy_mac_media_if_tesla_setup(vtss_state, port_no, conf, &force_reset));
        break;

    case VTSS_PHY_FAMILY_ELISE:
        VTSS_RC(vtss_phy_mac_media_if_elise_setup(vtss_state, port_no, conf));
        break;

    case VTSS_PHY_FAMILY_NANO:
        if (ps->type.part_number != VTSS_PHY_TYPE_7435) {
            VTSS_RC(vtss_phy_mac_media_if_nano_setup(vtss_state, port_no, conf));
        }
        break;

    case VTSS_PHY_FAMILY_NONE:
    default:
        if (ps->conf_none) {
            switch (conf->mac_if) {
            case VTSS_PORT_INTERFACE_RGMII:
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_STD_27, 0x848B));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS_20, 0x0CE2));
                break;
            case VTSS_PORT_INTERFACE_RTBI:
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_STD_27, 0x8489));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS_20, 0x0CE2));
                break;
            default:
                break;
            }
            break;
        }
        break;
    }
    //Set 1588 Bypass before performing reset.
#if defined(VTSS_OPT_PHY_TIMESTAMP)
    VTSS_RC(vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, FALSE));
#endif
    /* -- Step 3: Reset PHY -- */
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    if (force_reset) {
        VTSS_I("port_no %u, Calling Port Reset - Resetting PHY Port ", port_no);
        //printf("port_no %u, Calling Port Reset - Resetting PHY Port \n", port_no);
        ps->cu_sfp_config_complete = FALSE; // Clear this flag if we are resetting the PHY Mac/Media i/f
        VTSS_RC(port_reset(vtss_state, port_no));
#if defined(VTSS_FEATURE_EEE)
        vtss_state->phy_state[port_no].eee_conf.eee_mode = EEE_REG_UPDATE;
#endif
    } else {
        ps->link_down_due_to_port_reset = FALSE;
        VTSS_I("port_no %u, No Config Change detected, NOT Resetting PHY Port ", port_no);
        //printf("port_no %u, No Config Change detected, NOT Resetting PHY Port \n", port_no);
    }

    /* -- Step 4: Run startup scripts -- */
    switch (ps->family) {

    case VTSS_PHY_FAMILY_MUSTANG:
        /* TBD */
        break;

    case VTSS_PHY_FAMILY_BLAZER:
        VTSS_RC(vtss_phy_init_seq_blazer(vtss_state, ps, port_no));

        /* Setup MAC interface */
        switch (conf->mac_if) {
        case VTSS_PORT_INTERFACE_MII:
        case VTSS_PORT_INTERFACE_GMII:
            reg = (0 << 12);
            break;
        case VTSS_PORT_INTERFACE_RGMII:
            reg = (1 << 12);
            break;
        case VTSS_PORT_INTERFACE_TBI:
            reg = (2 << 12);
            break;
        case VTSS_PORT_INTERFACE_RTBI:
            reg = (3 << 12);
            break;
        default:
            VTSS_E("port_no %u, MAC interface %s not supported for Blazer",
                   port_no, vtss_port_if_txt(conf->mac_if));
            return VTSS_RC_ERROR;
        }
        reg |= (((ps->type.revision == 6 ? 1 : 0) << 9) | /* 2.5V */
                ((conf->rgmii.rx_clk_skew_ps || conf->rgmii.tx_clk_skew_ps ? 1 : 0) << 8) |
                (0x14 << 0)); /* Reserved */
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, reg));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x3000));
        break;

    case VTSS_PHY_FAMILY_COBRA:
        VTSS_RC(vtss_phy_init_seq_cobra(vtss_state, ps, port_no));
        break;

    case VTSS_PHY_FAMILY_QUATTRO:
        VTSS_RC(vtss_phy_init_seq_quattro(vtss_state, ps, port_no));
        break;

    case VTSS_PHY_FAMILY_SPYDER:
        VTSS_RC(vtss_phy_init_seq_spyder(vtss_state, ps, port_no));
        break;

    case VTSS_PHY_FAMILY_COOPER:
        VTSS_RC(vtss_phy_init_seq_cooper(vtss_state, ps, port_no));
        break;

    case VTSS_PHY_FAMILY_LUTON:
    case VTSS_PHY_FAMILY_LUTON_E:
    case VTSS_PHY_FAMILY_LUTON24:
        VTSS_RC(vtss_phy_init_seq_luton(vtss_state, ps, port_no));
        break;

    case VTSS_PHY_FAMILY_LUTON26:
        VTSS_RC(vtss_phy_init_seq_atom(vtss_state, ps, port_no, TRUE));

#if defined(VTSS_FEATURE_EEE)
        VTSS_RC(vtss_phy_eee_ena_private(vtss_state, port_no));
#endif
        break;
    case VTSS_PHY_FAMILY_ATOM:
        VTSS_RC(vtss_phy_init_seq_atom(vtss_state, ps, port_no, FALSE));

#if defined(VTSS_FEATURE_EEE)
        VTSS_RC(vtss_phy_eee_ena_private(vtss_state, port_no));
#endif
        break;

    case VTSS_PHY_FAMILY_VIPER: {
        u16 reg_val = 0, new_val = 0;
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        BOOL is_100fx = FALSE;

        /* Bug# 19146  */
        /* Adjust the 1G SerDes SigDet Input Threshold and Signal Sensitivity for 100FX */
        /* For Luton and Tesla, This is done in the Micro-Patch */
        if ((conf->media_if == VTSS_PHY_MEDIA_IF_FI_100FX) ||
            (conf->media_if == VTSS_PHY_MEDIA_IF_AMS_CU_100FX) ||     // In AMS, Both Cu and Fiber are possible
            (conf->media_if == VTSS_PHY_MEDIA_IF_AMS_FI_100FX)) {
            is_100fx = TRUE;
        } else {
            is_100fx = FALSE;
        }
        VTSS_RC(vtss_phy_sd1g_patch_private(vtss_state, port_no, is_100fx));
#endif

        /* Fix for bz# 21484 ,TR.LinkDetectCtrl = 3*/
        if (!vtss_state->sync_calling_private) {
            new_val = 3;
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa7f8));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg_val));
            reg_val &= 0xffe7;
            reg_val |= ((new_val & 3) << 3);
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg_val));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87f8));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            /* Fix for bz# 21485 ,VgaThresh100=25*/
            new_val = 25;
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xafa4));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg_val));
            reg_val &= 0xff80;
            reg_val |= (new_val & 0x7F);
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, reg_val));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fa4));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        }

        /* Bz#23788 Work-Around for 100BT Link break Issue, after restoring link it does not come up for a long time. */
        /* This only currently applies to Families VIPER and NANO */
        VTSS_RC(vtss_phy_100BaseT_long_linkup_workaround(vtss_state, port_no, TRUE));

    }
        /* fall-through */
    // Intentionally Fall thru to Elise.... because Elise is Cu only

    case VTSS_PHY_FAMILY_ELISE:
        // Force Clear Default Settings for Inhibit Odd Start on MAC and MEDIA I/F Reg16E3.2=0 and Reg23E3.4=0
        VTSS_RC(vtss_phy_mac_media_inhibit_odd_start_private(vtss_state, port_no, FALSE, FALSE));
        /* fall-through */
    // Intentionally Fall thru to EEE

    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_NANO:
#if defined(VTSS_FEATURE_EEE)
        VTSS_RC(vtss_phy_eee_ena_private(vtss_state, port_no));
#endif
        /* Bz#23788 Work-Around for 100BT Link break Issue, after restoring link it does not come up for a long time. */
        /* This only currently applies to Families VIPER and NANO */
        VTSS_RC(vtss_phy_100BaseT_long_linkup_workaround(vtss_state, port_no, TRUE));

        // No init seq defined yet.
        break;
    case VTSS_PHY_FAMILY_ENZO:
        VTSS_RC(vtss_phy_init_seq_enzo(vtss_state, ps, port_no));
        break;

    case VTSS_PHY_FAMILY_NONE:
    default:
        break;
    }
    return VTSS_RC_OK;
}

static BOOL is_media_if_passthru(const vtss_phy_media_interface_t media_if)
{
    return media_if == VTSS_PHY_MEDIA_IF_SFP_PASSTHRU ||
           media_if == VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU ||
           media_if == VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU;
}

static vtss_rc vtss_phy_conf_set_private(vtss_state_t *vtss_state,
                                         const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps         = &vtss_state->phy_state[port_no];
    vtss_phy_conf_t       *conf       = &ps->setup;
    vtss_phy_reset_conf_t *reset_conf = &ps->reset;
    u16                   current_reg_value, new_reg_value, revision;
    u16                   prev_mdi_value;
    vtss_phy_family_t     family;
    u16                   advertise_reg_bit_mask = 0;
    BOOL                  restart_aneg = FALSE;

#if defined(VTSS_VIPER_B_FIFO_RESET)
    u16 is_power_down = 0;  //for OOS API shutdown case.
#endif

    /* Save setup */
    VTSS_D("enter, port_no: %u", port_no);
    family = ps->family;
    revision = ps->type.revision;

        /*- This is for a Luton26 Switch */
        /*- By defining VTSS_PHY_OPT_CAP_FE_ONLY, Downgrade PHY Advertised Capability, Over-ride Config */
        /*- This is forcing 1_GigE capable PHY to be configured with no more capability than a 100M_FE PHY */
        /*- For VTSS_PHY_OPT_CAP_FE_ONLY, the static configuration is as follows: */
        /*- Ports 0 -7: CuPHY     */
        /*- Ports 8 -22: Not Used */
        /*- Ports 23: SerDes1G, 0 */
        /*- Ports 24: SerDes6G, 1 */
        /*- Ports 25: SerDes6G, 0 */
        /*- Ports 26: CPU Port    */
#ifdef VTSS_PHY_OPT_CAP_FE_ONLY
        if (port_no < 8) {
            conf->aneg.speed_1g_fdx = FALSE;
            conf->aneg.speed_1g_hdx = FALSE;
            if (conf->forced.speed >= VTSS_SPEED_1G) {
                conf->forced.speed = VTSS_SPEED_100M;
            }

            // Setup Access to Test Page Registers
            VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
            // Clear Bit 4 - When this bit is set high sub-channels C and D are powered down.
            //  1: disable pair CD power down
            //  0: enable pair CD power down
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0010));
        } else {
            return VTSS_RC_ERR_PHY_PORT_OUT_RANGE;
        }
#endif

        // Read the current MDI Settings before changing any config
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL, &prev_mdi_value));
        prev_mdi_value &= 0x000C;

        // Ensure that we are on the Std Page Registers before we start programming
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        // If in forced mdi mode and ANEG, we have to make sure to set MDI mode before ANEG restart
        VTSS_RC(vtss_phy_mdi_setup(vtss_state, port_no));
        VTSS_I("mode:%d", conf->mode);
        switch (conf->mode) {
        case VTSS_PHY_MODE_ANEG:
            /* Setup register 4 */
            new_reg_value = (((conf->aneg.tx_remote_fault ? 1 : 0) << 13) |
                             ((conf->aneg.asymmetric_pause ? 1 : 0) << 11) |
                             ((conf->aneg.symmetric_pause ? 1 : 0) << 10) |
                             ((conf->aneg.speed_100m_fdx ? 1 : 0) << 8) |
                             ((conf->aneg.speed_100m_hdx ? 1 : 0) << 7) |
                             ((conf->aneg.speed_10m_fdx ? 1 : 0) << 6) |
                             ((conf->aneg.speed_10m_hdx ? 1 : 0) << 5) |
                             (1 << 0));

            if (is_media_if_passthru(reset_conf->media_if)) {
                advertise_reg_bit_mask = 0xac1f; // In Pass though mode the advertisement is done in the cu SFP.
            } else {
                advertise_reg_bit_mask = 0xbfff;// Bit 14 is reserved.
            }

            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT, &current_reg_value));

            if (current_reg_value != new_reg_value) {
                restart_aneg = TRUE;
            }

            /* Normally, we are in MDIX_AUTO. */
            /* However, If we are in Forced MDI or MDIX mode, In order to assure that we are in the correct mode, restart ANEG */
            /* In some situations in 1G mode, the chip tries to maintain the link-up regardless of forced MDI settings */
            /* See Bugzilla 18532: MDI config is not taking effect immediately */
            switch (conf->mdi) {
            case VTSS_PHY_MDIX_AUTO:
                if (prev_mdi_value != 0x0) {
                    restart_aneg = TRUE;
                }
                break;
            case VTSS_PHY_MDIX:
                if (prev_mdi_value != 0xC) {
                    restart_aneg = TRUE;
                }
                /* fall-through */
            case VTSS_PHY_MDI:
                if (prev_mdi_value != 0x8) {
                    restart_aneg = TRUE;
                }
                break;
            default:
                break;
            }

            VTSS_D("VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT, port:%d,  mdi: 0x%x, Curr RegVal: 0x%x, New RegVal: 0x%x,  Mask: 0x%x ",
                   port_no, conf->mdi, current_reg_value, new_reg_value, advertise_reg_bit_mask);

            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT, new_reg_value, advertise_reg_bit_mask));

            /* Setup register 9 for 1G advertisement */
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, &current_reg_value));
            new_reg_value = 0;
            if (conf->aneg.speed_1g_fdx) {
                new_reg_value |= VTSS_PHY_1000BASE_T_CONTROL_1000BASE_T_FDX_CAPABILITY;
            }
            /* bug 17917: */
            /* For 1000BaseT-HDX, although allowed per 802.3, is not supported in industry */
            /* We are unaware of anyone making a Gigabit Ethernet hub, so testing 1000BT hdx with any vendors L2 device may be problematic. */
            if (conf->aneg.speed_1g_hdx) {
                new_reg_value |= VTSS_PHY_1000BASE_T_CONTROL_1000BASE_T_HDX_CAPABILITY;
            }

            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, new_reg_value,
                                            (VTSS_PHY_1000BASE_T_CONTROL_1000BASE_T_FDX_CAPABILITY |
                                             VTSS_PHY_1000BASE_T_CONTROL_1000BASE_T_HDX_CAPABILITY)));

            if ((current_reg_value & (VTSS_PHY_1000BASE_T_CONTROL_1000BASE_T_FDX_CAPABILITY |
                                      VTSS_PHY_1000BASE_T_CONTROL_1000BASE_T_HDX_CAPABILITY)) != new_reg_value) {
                restart_aneg = TRUE;
            }

            /* advertise ring resiliency capbality only in 1000BT mode */
            if ((family == VTSS_PHY_FAMILY_VIPER) && (conf->aneg.speed_1g_fdx)) {
                VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no,
                                                VTSS_PHY_EXTENDED_RING_RESILIENCY_CTRL,
                                                VTSS_F_PHY_EXT_RING_RSLNT_STARTUP_EN |
                                                VTSS_F_PHY_EXT_RING_RSLNT_ADVERTISE_RING_RESILIENCY,
                                                VTSS_F_PHY_EXT_RING_RSLNT_STARTUP_EN |
                                                VTSS_F_PHY_EXT_RING_RSLNT_ADVERTISE_RING_RESILIENCY));
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            }
            switch (family) {
            case VTSS_PHY_FAMILY_COOPER:
                /* BZ 2528 - Part 2/2
                 * Solution for Interop (slow link-up) issue with Marvell PHYs */
                VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200)); //Ensure RClk125 enabled even in powerdown
                VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xA7F8));
                VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000, 0x0018));
                VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0, 0));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87F8));
                VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200)); //Restore RClk125 gating
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                break;

            case VTSS_PHY_FAMILY_ATOM:
            case VTSS_PHY_FAMILY_LUTON26:
            case VTSS_PHY_FAMILY_TESLA:
            case VTSS_PHY_FAMILY_VIPER:
            case VTSS_PHY_FAMILY_ELISE:
            case VTSS_PHY_FAMILY_NANO :
                VTSS_RC(vtss_phy_set_private_atom(vtss_state, port_no, conf->mode));
                break;

            default:
                break;
            }

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_VIPER_B_FIFO_RESET)
#if defined(VTSS_FEATURE_MACSEC)
            if (!vtss_state->macsec_conf[port_no].glb.init.enable) {
#endif
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no,VTSS_PHY_MODE_CONTROL, &is_power_down));
                if(is_power_down & VTSS_F_PHY_MODE_CONTROL_POWER_DOWN){
                    VTSS_RC(vtss_phy_ts_isolate_phy(vtss_state, port_no));
                }
#if defined(VTSS_FEATURE_MACSEC)
            }
#endif
#endif
#endif

            /* Use register 0 to restart auto negotiation */
            // Don't restart auton-neg at warm start if something has changed
            if (!conf->aneg.no_restart_aneg) {
                if (!vtss_state->sync_calling_private && restart_aneg) {
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                                    VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG,
                                                    VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG | VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));
                    VTSS_D("VTSS_PHY_MODE_FORCED, port:%d", port_no);

                } else {
                    // If warm start then don't restart auto-negotiation.
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                                    VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA,
                                                    VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA | VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));
                }
            }
#if defined(VTSS_VIPER_B_FIFO_RESET) && defined(VTSS_VIPER_B_FIFO_RESET_API_CALL)
                if(is_power_down & VTSS_F_PHY_MODE_CONTROL_POWER_DOWN){
                    vtss_phy_ts_fifo_conf_t fifo_conf_viper;
                    memset(&fifo_conf_viper, 0, sizeof(vtss_phy_ts_fifo_conf_t));
                    //Private API takes care of MACsec case(Algorithm is not executed in Macsec Case)
                    VTSS_RC(vtss_phy_1588_oos_mitigation_steps_private(vtss_state, port_no, &fifo_conf_viper));
                }

#endif
            VTSS_D("VTSS_PHY_MODE_ANEG, port:%d, reg:0x%X", port_no, new_reg_value);
            break;

        case VTSS_PHY_MODE_FORCED:
            if (is_media_if_passthru(reset_conf->media_if)) {
                VTSS_D("port: %d; VTSS_PHY_MODE_FORCED: media_if = VTSS_PHY_MEDIA_IF_SFP_PASSTHRU", port_no);
            } else {
#if defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_VIPER_B_FIFO_RESET)
#if defined(VTSS_FEATURE_MACSEC)
                if (!vtss_state->macsec_conf[port_no].glb.init.enable) {
#endif
                    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no,VTSS_PHY_MODE_CONTROL, &is_power_down));
                    if(is_power_down & VTSS_F_PHY_MODE_CONTROL_POWER_DOWN){
                        VTSS_RC(vtss_phy_ts_isolate_phy(vtss_state, port_no));
                    }
#if defined(VTSS_FEATURE_MACSEC)
                }
#endif
#endif
#endif

                new_reg_value = (((ps->loopback.near_end_enable ? 1 : 0 ) << 14) |
                                 ((conf->forced.speed == VTSS_SPEED_100M ? 1 : 0) << 13) | (0 << 12) |
                                 ((conf->forced.fdx ? 1 : 0) << 8) |
                                 ((conf->forced.speed == VTSS_SPEED_1G ? 1 : 0) << 6) |
                                 ((conf->unidir == VTSS_PHY_UNIDIRECTIONAL_ENABLE ? 1 : 0) << 5));

                VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, new_reg_value));
                VTSS_D("VTSS_PHY_MODE_FORCED, port:%d, mode_control regVal:0x%X ", port_no, new_reg_value);

                if ((reset_conf->media_if == VTSS_PHY_MEDIA_IF_CU) && (conf->forced.speed == VTSS_SPEED_1G)) {
                    /* Work-around for Bug#9805/9806/1282 *** also *** Not in Warm-Start mode */
                    if (!vtss_state->sync_calling_private) {
                        switch (family) {
                        case VTSS_PHY_FAMILY_ATOM:
                        case VTSS_PHY_FAMILY_LUTON26:
                        case VTSS_PHY_FAMILY_TESLA:
                            // Setting AUTO NEG advertisement to 0 in order to make sure that ANEG is restarted when return to aneg mode.
                            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT, 0x0,
                                                            (VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT_100BASETX_FDX |
                                                             VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT_100BASETX_HDX |
                                                             VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT_10BASET_FDX |
                                                             VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT_10BASET_HDX)));
                            break;

                        case VTSS_PHY_FAMILY_VIPER:
                        case VTSS_PHY_FAMILY_ELISE:
                        case VTSS_PHY_FAMILY_NANO :
                            break;

                        default:
                            break;
                        }
                    }
                } else {
                    /* Enable Auto MDI/MDI-X in forced 10/100 mode */
                    switch (family) {
                    case VTSS_PHY_FAMILY_QUATTRO:
                        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
                        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2803));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));
                        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
                        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                        break;
                    case VTSS_PHY_FAMILY_LUTON:
                        if (revision == 0) {
                            VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
                            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2803));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));
                            VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
                            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                        } else {
                            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0000, 0x0080));
                        }
                        break;
                    case VTSS_PHY_FAMILY_SPYDER:
                    case VTSS_PHY_FAMILY_LUTON_E:
                        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0000, 0x0080));
                        break;
                    case VTSS_PHY_FAMILY_LUTON24:
                        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
                        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0092));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2803));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87FA));
                        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
                        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                        break;
                    case VTSS_PHY_FAMILY_COOPER:
                        /* BZ 2528 - Part 1/2
                         * Solution for Interop (slow link-up) issue with Marvell PHYs */
                        if (conf->forced.speed == VTSS_SPEED_100M) {
                            //Note: no need to ungate/gate RClk125 here since known to be in forced-100
                            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xA7F8));
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0018, 0x0018));
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0, 0));
                            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87F8));
                            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                        }
                        break;

                    case VTSS_PHY_FAMILY_COBRA:
                        // Work around bugzilla8953 - Port is not coming UP without auto negotiation
                        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0200, 0x0200));
                        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0012));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x2803));
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x87fa));
                        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x0200));
                        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                        break;
                    case VTSS_PHY_FAMILY_ENZO:
                        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0000, 0x0080));
                        break;

                    case VTSS_PHY_FAMILY_ATOM:
                    case VTSS_PHY_FAMILY_LUTON26:
                    case VTSS_PHY_FAMILY_TESLA:
                    case VTSS_PHY_FAMILY_VIPER:
                    case VTSS_PHY_FAMILY_ELISE:
                    case VTSS_PHY_FAMILY_NANO :
                        VTSS_RC(vtss_phy_set_private_atom(vtss_state, port_no, conf->mode));
                        break;

                    default:
                        break;
                    }  // End of switch on Family
                }   // End of forced.speed != VTSS_SPEED_1G
            } // End of !VTSS_PHY_MEDIA_IF_SFP_PASSTHRU
#if defined(VTSS_VIPER_B_FIFO_RESET) && defined(VTSS_VIPER_B_FIFO_RESET_API_CALL)
            if(is_power_down & VTSS_F_PHY_MODE_CONTROL_POWER_DOWN){
                vtss_phy_ts_fifo_conf_t fifo_conf_viper;
                memset(&fifo_conf_viper, 0, sizeof(vtss_phy_ts_fifo_conf_t));
                //Private API takes care of MACsec case(Algorithm is not executed in Macsec Case)
                VTSS_RC(vtss_phy_1588_oos_mitigation_steps_private(vtss_state, port_no, &fifo_conf_viper));
            }
#endif

            break;

        case VTSS_PHY_MODE_POWER_DOWN:
            /* - Perform SPI PAUSE to prevent possibility of dual CSR Accesses by SPI and Micro which may cause Micro-Hang during PwrDn */
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0)
            if (vtss_state->phy_ts_port_conf[port_no].new_spi_conf.phy_type == VTSS_PHY_TYPE_8574 ||
                vtss_state->phy_ts_port_conf[port_no].new_spi_conf.phy_type == VTSS_PHY_TYPE_8572) {
                if ((vtss_phy_ts_spi_pause_priv(vtss_state, port_no)) != VTSS_RC_OK) {
                    VTSS_E("POWER_DOWN: SPI pause fail!, port %u", port_no);
                }
            }
#endif
            new_reg_value = 0;
            /* If VeriPHY is active, we must do a SW Reset to clear the VeriPHY before PowerDN to cancel it */
            /* Read register 24E1, Check for VeriPHY being active */
            VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_VERIPHY_CTRL_REG1, &new_reg_value));
            // Ensure that we are on the Std Page Registers before we start programming
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

            if (new_reg_value & VTSS_F_PHY_VERIPHY_CTRL_REG1_TRIGGER) {
                VTSS_I("VERIPHY Running on Port: %d, Initiating SW Reset before PowerDn Port, Reg24E1 Status: 0x%04x\n", port_no, new_reg_value);
                // signal to API the veriphy isn't running for this port
                VTSS_RC(vtss_phy_soft_reset_port(vtss_state, port_no));
            }

            /* Read register 24E1, Check for VeriPHY being active, It should be cleared after SW Reset */
            VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_VERIPHY_CTRL_REG1, &new_reg_value));
            // Ensure that we are on the Std Page Registers before we start programming
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            if (new_reg_value & VTSS_F_PHY_VERIPHY_CTRL_REG1_TRIGGER) {
                VTSS_E("VERIPHY Still Running on Port: %d after SW Reset, PowerDn Port, Reg24E1 Status: 0x%04x", port_no, new_reg_value);
            } else {
                VTSS_RC(vtss_phy_veriphy_running(vtss_state, port_no, TRUE, FALSE));
            }
#if defined(VTSS_OPT_PHY_TIMESTAMP)
            VTSS_RC(vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, FALSE));
#endif
            /* Setup register 0 */
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, VTSS_F_PHY_MODE_CONTROL_POWER_DOWN, VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));

            // Work-around for bugzilla#12650 - Link status shows link up even when PHY is powered down
            if (family == VTSS_PHY_FAMILY_QUATTRO || family == VTSS_PHY_FAMILY_COBRA) {
                /* Briefly power up-down to make sure the link status bit clears */
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, !VTSS_F_PHY_MODE_CONTROL_POWER_DOWN, VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, VTSS_F_PHY_MODE_CONTROL_POWER_DOWN, VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));
            }
            /* POWER_DOWN- Perform SPI UNPAUSE to release */
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0)
            if (vtss_state->phy_ts_port_conf[port_no].new_spi_conf.phy_type == VTSS_PHY_TYPE_8574 ||
                vtss_state->phy_ts_port_conf[port_no].new_spi_conf.phy_type == VTSS_PHY_TYPE_8572) {
                if ((vtss_phy_ts_spi_unpause_priv(vtss_state, port_no)) != VTSS_RC_OK) {
                    VTSS_E("POWER_DOWN: SPI unpause fail!, port %u", port_no);
                }
            }
#endif

            break;
        default:
            VTSS_E("port_no %u, unknown mode %d", port_no, conf->mode);
            return VTSS_RC_ERROR;
        }

        if (conf->mode == VTSS_PHY_MODE_POWER_DOWN) {
            VTSS_I("Powering down, no need to do mdi setup , port_no: %u", port_no);
        } else {
            // If in Not in ANEG mode, need to set mdi after vtss_phy_set_private_atom()
            VTSS_RC(vtss_phy_mdi_setup(vtss_state, port_no));
        }

        if (family == VTSS_PHY_FAMILY_COBRA) {
            VTSS_N("Port:%d  Bugzilla#7489 - Interrupt must be disable when powered down.", port_no);
            VTSS_RC(vtss_phy_event_enable_private(vtss_state, port_no));
        }

        if (is_media_if_passthru(reset_conf->media_if))  {
            VTSS_D("port: %d; media_if = VTSS_PHY_MEDIA_IF_SFP_PASSTHRU, Configuring SFP", port_no);
            VTSS_RC(vtss_phy_pass_through_speed_mode(vtss_state, port_no));
        } else {
            switch (ps->family) {
            case VTSS_PHY_FAMILY_ATOM:
            case VTSS_PHY_FAMILY_LUTON26:
            case VTSS_PHY_FAMILY_TESLA:
            case VTSS_PHY_FAMILY_VIPER:
            case VTSS_PHY_FAMILY_ELISE:
                VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
                // Setup Reg16E3
                new_reg_value = 0;
                new_reg_value = (((conf->mac_if_pcs.disable ? 1 : 0) << 15) |
                                 ((conf->mac_if_pcs.restart ? 1 : 0) << 14) |
                                 ((conf->mac_if_pcs.pd_enable ? 1 : 0) << 13) |
                                 ((conf->mac_if_pcs.aneg_restart ? 1 : 0) << 12) |
                                 ((conf->mac_if_pcs.force_adv_ability ? 1 : 0) << 11) |
                                 (conf->mac_if_pcs.sgmii_in_pre << 9) |
                                 ((conf->mac_if_pcs.sgmii_out_pre ? 1 : 0) << 8) |
                                 ((conf->mac_if_pcs.serdes_aneg_ena ? 1 : 0) << 7) |
                                 ((conf->mac_if_pcs.serdes_pol_inv_in ? 1 : 0) << 6) |
                                 ((conf->mac_if_pcs.serdes_pol_inv_out ? 1 : 0) << 5) |
                                 ((conf->mac_if_pcs.fast_link_stat_ena ? 1 : 0) << 4) |
                                 ((conf->mac_if_pcs.inhibit_odd_start ? 1 : 0) << 2));

                // Recommended by chip designers - Setting VTSS_F_MAC_SERDES_PCS_CONTROL_MAC_IF_PD_ENA,
                // This should allow link-up if the MAC is not doing auto-neg.
                // Enable "MAC interface autonegotiation parallel detect",
                //    else data flow is stopped for the CU ports if PHY has MAC ANEG enabled and the switch is connected to isn't
                new_reg_value |= VTSS_F_MAC_SERDES_PCS_CONTROL_MAC_IF_PD_ENA;
                /* If the bits are ON by Default, leave them ON - We don't want to break default behavior */
                /* If clearing bit is desired, Clear the bit in the Register either before or after this Write */
                if (!vtss_state->sync_calling_private) {
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MAC_SERDES_PCS_CONTROL, 0xFFFF, new_reg_value));
                }
                // Setup Reg23E3
                new_reg_value = 0;
                new_reg_value = ((conf->media_if_pcs.remote_fault << 14) |
                                 ((conf->media_if_pcs.aneg_pd_detect ? 1 : 0) << 13) |
                                 ((conf->media_if_pcs.force_adv_ability ? 1 : 0) << 11) |
                                 ((conf->media_if_pcs.serdes_pol_inv_in ? 1 : 0) << 6) |
                                 ((conf->media_if_pcs.serdes_pol_inv_out ? 1 : 0) << 5) |
                                 ((conf->media_if_pcs.inhibit_odd_start ? 1 : 0) << 4) |
                                 ((conf->media_if_pcs.force_hls ? 1 : 0) << 2) |
                                 ((conf->media_if_pcs.force_fefi ? 1 : 0) << 1) |
                                 ((conf->media_if_pcs.force_fefi_value ? 1 : 0)));

                /* If the bits are ON by Default, leave them ON - We don't want to break default behavior */
                /* If clearing bit is desired, Clear the bit in the Register either before or after this Write */
                if (!vtss_state->sync_calling_private) {
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_CONTROL, 0xFFFF, new_reg_value));
                }

                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                break;

            default :
                break;
            }

            /* Force AMS Override: Reg23.7:6 - 0:Normal; 1:SerDes; 2:Copper */
            switch (ps->family) {
                case VTSS_PHY_FAMILY_TESLA:
                case VTSS_PHY_FAMILY_VIPER:
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL,
                                                    VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_OVERRIDE(conf->force_ams_sel),
                                                    VTSS_M_PHY_EXTENDED_PHY_CONTROL_AMS_OVERRIDE));
                    break;
                default:
                    break;
            }
        }
        /* Set Sigdet pin polarity active high/low. Reg19E1.0 */
        switch (conf->sigdet) {
        case VTSS_PHY_SIGDET_POLARITY_ACT_LOW:
            VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL,
                                            1 << VTSS_S_PHY_EXTENDED_MODE_CONTROL_SIGDET_POLARITY,
                                            1 << 0));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            break;
        case VTSS_PHY_SIGDET_POLARITY_ACT_HIGH:
            VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL,
                                            0 << VTSS_S_PHY_EXTENDED_MODE_CONTROL_SIGDET_POLARITY,
                                            1 << 0));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            break;
        default:
            /* Default is to keep the sigdet polarity active high */
            break;
        }

        /* Enable/disable fast link failure. Reg19E1.4 */
        switch (conf->flf) {
        case VTSS_PHY_FAST_LINK_FAIL_DISABLE:
            /* This manipulates GPIO9 output, therefore it can only be done from PHY Port 0 */
            if (vtss_phy_chip_port(vtss_state, port_no) == 0) {
                VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL,
                                                0x0, VTSS_F_PHY_EXTENDED_MODE_CONTROL_FAST_LINK_FAILURE));
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            }
            break;
        case VTSS_PHY_FAST_LINK_FAIL_ENABLE:
            /* This manipulates GPIO9 output, therefore it can only be done from PHY Port 0 */
            if (vtss_phy_chip_port(vtss_state, port_no) == 0) {
                VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL,
                                                VTSS_F_PHY_EXTENDED_MODE_CONTROL_FAST_LINK_FAILURE,
                                                VTSS_F_PHY_EXTENDED_MODE_CONTROL_FAST_LINK_FAILURE));
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            }
            break;
        default:
            /* Default is to keep the fast link failure pin disabled */
            break;
        }

    return VTSS_RC_OK;
}
static vtss_rc vtss_phy_ring_resiliency_conf_set_private(vtss_state_t *vtss_state,
                                                         const vtss_port_no_t port_no)
{

    u16    val;
    vtss_phy_port_state_t *ps   = &vtss_state->phy_state[port_no];
    vtss_rc   rc                = VTSS_RC_OK;

    VTSS_D("enter, port_no: %u", port_no);
    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
        if (ps->rslnt_conf.enable_rrslnt) {
            VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_RING_RESILIENCY_CTRL, &val));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            if (VTSS_F_PHY_EXT_RING_RSLNT_LP_RING_RESILIENCY_ADVERTISE & val) {
                /* start switchover */
                VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
                VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no,
                                                VTSS_PHY_EXTENDED_RING_RESILIENCY_CTRL,
                                                VTSS_F_PHY_EXT_RING_RSLNT_START_SWITCHOVER,
                                                VTSS_F_PHY_EXT_RING_RSLNT_START_SWITCHOVER));
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
            } else {
                vtss_state->phy_state[port_no].rslnt_conf.ring_res_status = TIMING_LP_NOT_RESILIENT_CAP;
                VTSS_I("Link Partener is not ring resilient capable port: %u", port_no);
                return rc;
            }
        } else {
            VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_RING_RESILIENCY_CTRL,
                                            0,
                                            VTSS_F_PHY_EXT_RING_RSLNT_START_SWITCHOVER));
            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        }
        break;
    default:
        VTSS_I("ring resiliency not supported family: %s port_no:%u", vtss_phy_family2txt(ps->family), port_no);
        return (VTSS_RC_OK);
    }
    return rc;
}

static vtss_rc vtss_phy_ring_resiliency_conf_get_private(vtss_state_t *vtss_state,
                                                         const vtss_port_no_t port_no,
                                                         vtss_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    u16 status, val;
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_RING_RESILIENCY_CTRL, &val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    if (VTSS_F_PHY_EXT_RING_RSLNT_LP_RING_RESILIENCY_ADVERTISE & val) {
        status = VTSS_PHY_EXTRACT_BITFIELD(val, 4, 2);
        switch (status) {
        case 0:
            vtss_state->phy_state[port_no].rslnt_conf.ring_res_status = TIMING_DEFAULT_SLAVE;
            break;
        case 1:
            vtss_state->phy_state[port_no].rslnt_conf.ring_res_status = TIMING_MASTER_AS_SLAVE;
            break;
        case 2:
            vtss_state->phy_state[port_no].rslnt_conf.ring_res_status = TIMING_SLAVE_AS_MASTER;
            break;
        case 3:
            vtss_state->phy_state[port_no].rslnt_conf.ring_res_status = TIMING_DEFAULT_MASTER;
            break;
        default:
            break;
        }
    } else {
        vtss_state->phy_state[port_no].rslnt_conf.ring_res_status = TIMING_LP_NOT_RESILIENT_CAP;
    }
    return VTSS_RC_OK;
}
// Function for enabling/disabling squelch work around.
// In : port_no - Any phy port with the chip
//    : enable  - TRUE = enable squelch workaround, FALSE = Disable squelch workaround
// Return - VTSS_RC_OK - Workaround was enabled/disable. VTSS_RC_ERROR - Squelch workaround patch not loaded
static vtss_rc squelch_workaround_private(vtss_state_t *vtss_state,
                                          vtss_port_no_t port_no, BOOL enable)
{
    u16 reg_value;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    switch (ps->family) {
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
        if (ps->family == VTSS_PHY_FAMILY_VIPER) {
            if (ps->type.revision != VTSS_PHY_VIPER_REV_A) {
                break;
            }
        }

        //Enable workaround by writing command to 18G
        //Command 18G instruction
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));   // switch to micro page (glabal to all 12 PHYs)
        if (enable) {
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x801d));
        } else {
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x800d));
        }
        //After writing to register 18G wait for bit 15 to equal 0.
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        // Check bit register 18G bit 14, if equal 1 there was an error.
        // If there was an error then most likely the squelch patch is not loaded.
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));   // switch to micro page (glabal to all 12 PHYs)
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg_value));
        if (reg_value & (1 << 14)) {
            VTSS_E("squelch workaround not loaded");
            return VTSS_RC_ERROR;
        }
        VTSS_I("squelch_workaround setup reg_value = 0x%X, enable:%d", reg_value, enable);
        break;
    default:
        break;
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

#if defined(VTSS_OPT_PHY_TIMESTAMP)
// Function for checking if 1588 registers are ready for new accesses. NOTE: **** Page register is left at 0x1588, and not return to standard page  ****
// In - port_no : Any phy port with the chip
static vtss_rc vtss_phy_wait_for_1588_command_busy(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t      port_no)
{
    u16 val;
    u8 timeout = 255; // For making sure that we don't get stucked

    // Wait for bit 15 to be set (or timeout)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_1588_16, &val));
    while (!(val & VTSS_PHY_F_PAGE_1588_16_CMD_BIT) && timeout)  {
        timeout--;
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_1588_16, &val));
    }

    if (timeout == 0) {
        VTSS_E("Unexpected timeout");
        return VTSS_RC_ERROR;
    } else {
        return VTSS_RC_OK;
    }
}
#endif

// Function for checking if MACSEC registers are ready for new accesses. NOTE: **** Page register is left at 0xMACSEC, and not return to standard page  ****
// In - port_no : Any phy port with the chip
static vtss_rc vtss_phy_wait_for_macsec_command_busy(vtss_state_t *vtss_state, const vtss_port_no_t  port_no, u32 page)
{
    u16 val;
    u8 timeout = 255; // For making sure that we don't get stucked

    // Wait for bit 15 to be set (or timeout)
    if (page == 19) {
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_19, &val));
        while (!(val & VTSS_PHY_F_PAGE_MACSEC_19_CMD_BIT) && timeout)  {
            timeout--;
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_19, &val));
        }
    } else if (page == 20) {
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_20, &val));
        while (!(VTSS_PHY_F_PAGE_MACSEC_20_READY(val) == 0) && timeout)  {
            timeout--;
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_20, &val));
        }
    }

    if (timeout == 0) {
        VTSS_E("Unexpected timeout when accesing port:%d page:%d", port_no, page);
        return VTSS_RC_ERROR;
    } else {
        return VTSS_RC_OK;
    }
}


// See vtss_phy_csr_wr
vtss_rc vtss_phy_1588_csr_wr_private(vtss_state_t         *vtss_state,
                                     const vtss_port_no_t port_no,
                                     const u16            target,
                                     const u32            csr_reg_addr,
                                     const u32            value)
{
#if defined(VTSS_OPT_PHY_TIMESTAMP)
    u32               value32;
    u16               reg_value = 0;
    u16               actual_tgt_id = 0;
    vtss_port_no_t    base_port_no = 0;
    vtss_port_no_t    cfg_port = port_no;
    BOOL              spi_access = FALSE;

    value32 = value;

    if (vtss_state->phy_ts_port_conf[port_no].is_gen2 == TRUE) {
        spi_access = vtss_state->init_conf.spi_32bit_read_write || vtss_state->init_conf.spi_read_write;
    }

    actual_tgt_id = target;
    if (vtss_state->phy_ts_port_conf[port_no].port_ts_init_done != FALSE) {
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0)
        BOOL              new_spi_mode = FALSE;
        new_spi_mode = vtss_state->phy_ts_port_conf[port_no].new_spi_conf.enable;
        if (new_spi_mode) {
            VTSS_E("Port:%d, NEW_SPI_MODE_ENABLED - This API does not support NEW_SPI_MODE!! ", port_no);
            return VTSS_RC_ERROR;
        }
#endif
        /* Function Access */
        /* Input Port (cfg_port) = 25, 26
         * Block Id = Ingress Engine0, Egress Engine0
         *            Ingress Engine1, Egress Engine1
         *            Ingress Engine2, Egress Engine2
         *            Processor0
         */
        base_port_no = vtss_state->phy_ts_port_conf[cfg_port].base_port;
        if (base_port_no != cfg_port) {
            cfg_port = base_port_no;
            if (target == 6) {         // PROC_BLOCK_ID_0 = 6
                actual_tgt_id = 7;     // PROC_BLOCK_ID_1 = 7
            }
        }
        /* Prevent access to TimeStamp FIFO Registers */
        if ((actual_tgt_id == 6) || (actual_tgt_id == 7)) {
            if ((csr_reg_addr >= 0x5c) && (csr_reg_addr <= 0x63)) {
                VTSS_D("Port:%d, Attempting to Access TimeStamp FIFO Registers - Access Denied - Returning OK", port_no);
                return VTSS_RC_OK;
            }
        }
    } else {
        return VTSS_RC_ERROR;
    }

    if (spi_access == TRUE) {
#if defined(VTSS_CHIP_CU_PHY)
        if (vtss_state->init_conf.spi_32bit_read_write != NULL) {
            VTSS_RC(vtss_state->init_conf.spi_32bit_read_write(vtss_state, cfg_port, 0, (actual_tgt_id + 8), (u16)csr_reg_addr, &value32));
        } else if (vtss_state->init_conf.spi_read_write != NULL) {
            VTSS_RC(vtss_phy_1g_spi_read_write(vtss_state, cfg_port, 0, 0, (actual_tgt_id + 8), (u16)csr_reg_addr, &value32));
        }
#endif
    } else {
        /* Divide the 32 bit value to [15..0] Bits & [31..16] Bits */
        u16 reg_value_lower = (value32 & 0xffff);
        u16 reg_value_upper = (value32 >> 16);
        u16 base_reg_value = 0;
        BOOL base_reg_update = FALSE;
        // Wait for any previous Cmd to complete
        //VTSS_RC(vtss_phy_wait_for_1588_command_busy(vtss_state, port_no)); // Wait for 1588 register access
        // The Sequence to Write to CSR's is as Follows:
        // Most Significant Word (MSW) (18)
        // Least Significant Word (LSW) (17)
        // Trigger CSR Action - Write (16) and wait for complete

        /* Read basepage Reg-18 */
        VTSS_RC(PHY_RD_PAGE(vtss_state, cfg_port, VTSS_PHY_PAGE_1588_CSR_DATA_MSB, &base_reg_value));

        /* 1588 - Page Selection */
        VTSS_RC(vtss_phy_page_1588(vtss_state, port_no));

        /* Write the upper word data (upper 16 bits) to register 18 */
        if ((target == 6 || target == 7) && (csr_reg_addr == 0x10 ||
                                             csr_reg_addr == 0x2e || csr_reg_addr == 0x4e ||
                                             csr_reg_addr == 0x2d || csr_reg_addr == 0x4d)) {
            if (!reg_value_upper) {
                VTSS_D("Ignore upper value for blk_id %d, csr_address %x", target, csr_reg_addr);
            } else {
                // Most Significant Word (MSW) (18)
                base_reg_update = TRUE;
                VTSS_RC(PHY_WR_PAGE(vtss_state, cfg_port, VTSS_PHY_PAGE_1588_CSR_DATA_MSB, reg_value_upper));
            }
        } else {
            // Most Significant Word (MSW) (18)
            VTSS_RC(PHY_WR_PAGE(vtss_state, cfg_port, VTSS_PHY_PAGE_1588_CSR_DATA_MSB, reg_value_upper));
        }
        // Least Significant Word (LSW) (17)
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_1588_CSR_DATA_LSB, reg_value_lower));

        reg_value = VTSS_PHY_F_PAGE_1588_16_CMD_BIT  |                   // Cmd Bit
                    0x0 |                                                // Write Cmd
                    VTSS_PHY_F_PAGE_1588_16_TARGET(actual_tgt_id) |      // Actual Tgt_ID or Actual Blk_ID on this Engine
                    VTSS_PHY_F_PAGE_1588_16_CSR_REG_ADDR(csr_reg_addr);

        // Trigger CSR Action - Write (16) - Write the Data out
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_1588_16, reg_value));

        // Wait for CSR Access to complete
        VTSS_RC(vtss_phy_wait_for_1588_command_busy(vtss_state, port_no)); // Wait for 1588 register access

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        if (base_reg_update != FALSE) {
            VTSS_RC(PHY_WR_PAGE(vtss_state, cfg_port, VTSS_PHY_PAGE_1588_CSR_DATA_MSB, base_reg_value));
        }
    }
#endif
    return VTSS_RC_OK;
}

// See vtss_phy_csr_rd
vtss_rc vtss_phy_1588_csr_rd_private(vtss_state_t         *vtss_state,
                                     const vtss_port_no_t port_no,
                                     const u16            target,
                                     const u32            csr_reg_addr,
                                     u32                  *value)
{
#if defined(VTSS_OPT_PHY_TIMESTAMP)

    u32               value32;
    u16               reg_value = 0;
    u16               actual_tgt_id = 0;
    vtss_port_no_t    base_port_no = 0;
    vtss_port_no_t    cfg_port = port_no;
    BOOL              spi_access = FALSE;

    value32 = 0;
    *value = 0;

    if (vtss_state->phy_ts_port_conf[port_no].is_gen2 == TRUE) {
        spi_access = vtss_state->init_conf.spi_32bit_read_write || vtss_state->init_conf.spi_read_write;
    }

    actual_tgt_id = target;
    if (vtss_state->phy_ts_port_conf[port_no].port_ts_init_done != FALSE) {
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0)
        BOOL              new_spi_mode = FALSE;
        new_spi_mode = vtss_state->phy_ts_port_conf[port_no].new_spi_conf.enable;
        if (new_spi_mode) {
            VTSS_E("Port:%d, NEW_SPI_MODE_ENABLED - This API does not support NEW_SPI_MODE!! ", port_no);
            return VTSS_RC_ERROR;
        }
#endif
        /* Function Access */
        /* Function Access */
        /* Input Port (cfg_port) = 25, 26
         * Block Id = Ingress Engine0, Egress Engine0
         *            Ingress Engine1, Egress Engine1
         *            Ingress Engine2, Egress Engine2
         *            Processor0
         */
        base_port_no = vtss_state->phy_ts_port_conf[cfg_port].base_port;
        if (base_port_no != cfg_port) {
            cfg_port = base_port_no;
            if (target == 6) {         // PROC_BLOCK_ID_0 = 6
                actual_tgt_id = 7;     // PROC_BLOCK_ID_1 = 7
            }
        }
        /* Prevent access to TimeStamp FIFO Registers */
        if ((actual_tgt_id == 6) || (actual_tgt_id == 7)) {
            if ((csr_reg_addr >= 0x5c) && (csr_reg_addr <= 0x63)) {
                VTSS_D("Port:%d, Attempting to Access TimeStamp FIFO Registers - Access Denied - Returning OK", port_no);
                return VTSS_RC_OK;
            }
        }
    } else {
        return VTSS_RC_ERROR;
    }

    if (spi_access == TRUE) {
#if defined(VTSS_CHIP_CU_PHY)
        if (vtss_state->init_conf.spi_32bit_read_write != NULL) {
            VTSS_RC(vtss_state->init_conf.spi_32bit_read_write(vtss_state, cfg_port, 1, (actual_tgt_id + 8), (u16)csr_reg_addr, &value32));
        } else if (vtss_state->init_conf.spi_read_write != NULL) {
            VTSS_RC(vtss_phy_1g_spi_read_write(vtss_state, cfg_port, 0, 1, (actual_tgt_id + 8), (u16)csr_reg_addr, &value32));
        }
#endif
        *value = value32;
    } else {
        u16 reg_value_lower = 0;
        u16 reg_value_upper = 0;

        // Wait for any previous Cmd to complete
        //VTSS_RC(vtss_phy_wait_for_1588_command_busy(vtss_state, port_no)); // Wait for 1588 register access
        // The Sequence to Write to CSR's is as Follows:
        // Most Significant Word (MSW) (18)
        // Least Significant Word (LSW) (17)
        // Trigger CSR Action - Write (16) and wait for complete

        /* 1588 - Page Selection */
        VTSS_RC(vtss_phy_page_1588(vtss_state, port_no));
        // Wait for any previous Cmd to complete
        //VTSS_RC(vtss_phy_wait_for_1588_command_busy(vtss_state, port_no)); // Wait for 1588 register access

        reg_value = VTSS_PHY_F_PAGE_1588_16_CMD_BIT  |                   // Cmd Bit
                    VTSS_PHY_F_PAGE_1588_16_READ |                       // Read Cmd, Set bit 14
                    VTSS_PHY_F_PAGE_1588_16_TARGET(actual_tgt_id) |      // Actual Tgt_ID or Actual Blk_ID on this Engine
                    VTSS_PHY_F_PAGE_1588_16_CSR_REG_ADDR(csr_reg_addr);

        // Trigger CSR Action - Read (16) into the CSR's and wait for complete
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_1588_16, reg_value));

        // Wait for CSR Access to complete
        VTSS_RC(vtss_phy_wait_for_1588_command_busy(vtss_state, port_no)); // Wait for 1588 register access

        // Read the Least Significant Word (LSW) (17)
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_1588_CSR_DATA_LSB, &reg_value_lower));
        // Read the Most Significant Word (MSW) (18)
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_1588_CSR_DATA_MSB, &reg_value_upper));

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

        *value = (reg_value_upper << 16) | reg_value_lower;
    }
#endif
    return VTSS_RC_OK;
}


// See vtss_phy_csr_wr
vtss_rc vtss_phy_macsec_csr_wr_private(vtss_state_t         *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const u16            target,
                                       const u32            csr_reg_addr,
                                       const u32            value)
{

    /* Divide the 32 bit value to [15..0] Bits & [31..16] Bits */
    u16 reg_value_lower = (value & 0xffff);
    u16 reg_value_upper = (value >> 16);
    u32 target_tmp = 0;
    //    u16 val;

    // The only ones not accessible in non-MACsec devices are the MACsec ingress and egress blocks at 0x38 and 0x3C (for each port).
    // Everything else is accessible using the so-called macsec_csr_wr/rd functions using registers 17-20 in extended page 4 (as described in PS1046).
    if (!vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC) && (target == 0x38 || target == 0x3C)) {
        VTSS_E("Port:%d, MACSEC to phy without MACSEC support", port_no);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_phy_page_macsec(vtss_state, port_no));

    // Wait for any previous Cmd to complete
    VTSS_RC(vtss_phy_wait_for_macsec_command_busy(vtss_state, port_no, 19)); // Wait for MACSEC register access

    // The Sequence to Write to CSR's is as Follows:
    // Setup the Target Id
    // Write the Least Significant Word (LSW) (17)
    // Write the Most Significant Word (MSW) (18)
    // Trigger CSR Action - Write(16) into the CSR's and wait for complete

    // Setup the Target Id
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_20, VTSS_PHY_F_PAGE_MACSEC_20_TARGET((target >> 2))));

    //    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_20, &val));
    //    printf("reg20:%x\n",val);

    if (target >> 2 == 1 || target >> 2 == 3) {
        target_tmp = target; // non-macsec access
    }
    // Write the Least Significant Word (LSW) (17)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_CSR_DATA_LSB, reg_value_lower));
    // Write the Most Significant Word (MSW) (18)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_CSR_DATA_MSB, reg_value_upper));
    // Trigger CSR Action - Write into the CSR's and wait for complete
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_19,  VTSS_PHY_F_PAGE_MACSEC_19_CMD_BIT |
                        VTSS_PHY_F_PAGE_MACSEC_19_TARGET(target_tmp) | VTSS_PHY_F_PAGE_MACSEC_19_CSR_REG_ADDR(csr_reg_addr)));

    // Wait for the Write to complete
    VTSS_RC(vtss_phy_wait_for_macsec_command_busy(vtss_state, port_no, 19)); // Wait for MACSEC register access

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

// See vtss_phy_csr_rd
vtss_rc vtss_phy_macsec_csr_rd_private(vtss_state_t         *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const u16            target,
                                       const u32            csr_reg_addr,
                                       u32                  *value)
{
    u16 reg_value_lower;
    u16 reg_value_upper;
    u32 target_tmp = 0;

    if (!vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC) && (target == 0x38 || target == 0x3C)) {
        VTSS_E("Port:%d, MACSEC to phy without MACSEC support, target:0x%X", port_no, target);
        return VTSS_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE;
    }

    VTSS_RC(vtss_phy_page_macsec(vtss_state, port_no));

    // Wait for any previous Cmd to complete
    VTSS_RC(vtss_phy_wait_for_macsec_command_busy(vtss_state, port_no, 19)); // Wait for MACSEC register access

    // The Sequence to Read from the CSR's is as Follows:
    // Setup the Target Id
    // Trigger CSR Action - Read(16) into the CSR's and wait for complete
    // Read the Least Significant Word (LSW) (17)
    // Read the Most Significant Word (MSW) (18)

    // Setup the Target Id
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_20, VTSS_PHY_F_PAGE_MACSEC_20_TARGET((target >> 2))));

    if (target >> 2 == 1) {
        target_tmp = target & 3; // non-macsec access
    }

    // Trigger CSR Action - Read(16) into the CSR's and wait for complete
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_19,
                        VTSS_PHY_F_PAGE_MACSEC_19_CMD_BIT | VTSS_PHY_F_PAGE_MACSEC_19_TARGET(target_tmp) |
                        VTSS_PHY_F_PAGE_MACSEC_19_READ    | VTSS_PHY_F_PAGE_MACSEC_19_CSR_REG_ADDR(csr_reg_addr)));

    VTSS_RC(vtss_phy_wait_for_macsec_command_busy(vtss_state, port_no, 19)); // Wait for MACSEC register access

    // Read the Least Significant Word (LSW) (17)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_CSR_DATA_LSB, &reg_value_lower));
    // Read the Most Significant Word (MSW) (18)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_CSR_DATA_MSB, &reg_value_upper));

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    *value = (reg_value_upper << 16) | reg_value_lower;
    return VTSS_RC_OK;
}


vtss_rc vtss_phy_macsec_csr_rd_64_private(vtss_state_t         *vtss_state,
                                          const vtss_port_no_t port_no,
                                          const u16            target,
                                          const u32            csr_reg_addr,
                                          u64                  *value)
{
    u16 reg_value_lower;
    u16 reg_value_upper;
    u16 reg_value_lower_1;
    u16 reg_value_upper_1;
    u32 target_tmp = 0;
    u64 value_64 = 0;

    *value = 0;
    if (!vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC) && (target == 0x38 || target == 0x3C)) {
        VTSS_E("Port:%d, MACSEC to phy without MACSEC support, target:0x%X", port_no, target);
        return VTSS_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE;
    }

    VTSS_RC(vtss_phy_page_macsec(vtss_state, port_no));

    // Wait for any previous Cmd to complete
    VTSS_RC(vtss_phy_wait_for_macsec_command_busy(vtss_state, port_no, 19)); // Wait for MACSEC register access

    // 64bit Access requires 4 x 16bit register accesses
    // The Sequence to Read from the CSR's is as Follows:
    // Setup the Target Id
    // Trigger CSR Action - Read into the CSR's and wait for complete
    // Read the Least Significant Word (LSW) (17)
    // Read the Most Significant Word (MSW) (18)

    // Setup the Target Id
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_20, VTSS_PHY_F_PAGE_MACSEC_20_TARGET((target >> 2))));

    if (target >> 2 == 1) {
        target_tmp = target & 3; // non-macsec access
    }
    // Trigger CSR Action - Read into the CSR's and wait for complete
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_19,
                        VTSS_PHY_F_PAGE_MACSEC_19_CMD_BIT | VTSS_PHY_F_PAGE_MACSEC_19_TARGET(target_tmp) |
                        VTSS_PHY_F_PAGE_MACSEC_19_READ    | VTSS_PHY_F_PAGE_MACSEC_19_CSR_REG_ADDR(csr_reg_addr)));

    VTSS_RC(vtss_phy_wait_for_macsec_command_busy(vtss_state, port_no, 19)); // Wait for MACSEC register access

    // Read the Least Significant Word (LSW) (17)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_CSR_DATA_LSB, &reg_value_lower));
    // Read the Most Significant Word (MSW) (18)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_CSR_DATA_MSB, &reg_value_upper));

    // Trigger CSR Action - Read into the CSR's and wait for complete
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_19,
                        VTSS_PHY_F_PAGE_MACSEC_19_CMD_BIT | VTSS_PHY_F_PAGE_MACSEC_19_TARGET(target_tmp) |
                        VTSS_PHY_F_PAGE_MACSEC_19_READ    | VTSS_PHY_F_PAGE_MACSEC_19_CSR_REG_ADDR(csr_reg_addr + 1)));

    VTSS_RC(vtss_phy_wait_for_macsec_command_busy(vtss_state, port_no, 19)); // Wait for MACSEC register access

    // Read the Least Significant Word (LSW) (17)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_CSR_DATA_LSB, &reg_value_lower_1));
    // Read the Most Significant Word (MSW) (18)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_MACSEC_CSR_DATA_MSB, &reg_value_upper_1));

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    VTSS_D("Port:%d, Read Value: 0x%04X %04X %04X %04X", port_no, reg_value_upper_1, reg_value_lower_1, reg_value_upper, reg_value_lower);
    value_64 = (0x000000000000FFFF & ((u64)reg_value_lower));
    value_64 |= (0x00000000FFFF0000 & ((u64)(reg_value_upper << 16)));
    value_64 |= (0x0000FFFF00000000 & ((u64)reg_value_lower_1 << 32));
    value_64 |= (0xFFFF000000000000 & (((u64)reg_value_upper_1 << 48)));
    *value = value_64;
    VTSS_D("Port:%d, Read Value: 0x%" PRIx64 "(%" PRIu64 ")", port_no, *value, *value);

    return VTSS_RC_OK;
}


// Function for determining the type of flow control
// In: port_no - The port in question.
//     lp_auto_neg_advertisment_reg - The value from the register containing the Link partners auto negotiation advertisement (Standard page 5)
//     phy_setup - The PHY configuration
// In/out:   Status  - Pointer to where to put the result
static void vtss_phy_flowcontrol_decode_status_private(vtss_port_no_t port_no, u16 lp_auto_neg_advertisment_reg, const vtss_phy_conf_t phy_setup, vtss_port_status_t *const status)
{
    BOOL                  sym_pause, asym_pause, lp_sym_pause, lp_asym_pause;
    sym_pause = phy_setup.aneg.symmetric_pause;
    asym_pause = phy_setup.aneg.asymmetric_pause;
    lp_sym_pause = (lp_auto_neg_advertisment_reg & (1 << 10) ? 1 : 0);
    lp_asym_pause = (lp_auto_neg_advertisment_reg & (1 << 11) ? 1 : 0);
    status->aneg.obey_pause =
        (sym_pause && (lp_sym_pause || (asym_pause && lp_asym_pause)) ? 1 : 0);
    status->aneg.generate_pause =
        (lp_sym_pause && (sym_pause || (asym_pause && lp_asym_pause)) ? 1 : 0);
    VTSS_N("port:%u, status->aneg.generate_pause:%d, status->aneg.generate_pause:%d, lp_asym_pause:%d, lp_sym_pause:%d, sym_pause:%d, asym_pause:%d",
           port_no, status->aneg.generate_pause, status->aneg.generate_pause, lp_asym_pause, lp_sym_pause, sym_pause, asym_pause);

}


// Function for determining the link speed
// In: port_no - The port in question.
//     lp_1000base_t_status_reg - The value from the register containing the Link partners 1000BASE-T Status (Standard page 10)
//     mii_status_reg - The value from the register containing mii status (Standard page 1)
//     phy_setup - The PHY configuration
// In/out:   Status  - Pointer to where to put the result
static void vtss_phy_link_speeed_decode_status(vtss_port_no_t port_no, u16 lp_1000base_t_status_reg, u16 mii_status_reg, const vtss_phy_conf_t phy_setup, vtss_port_status_t *const status)
{
    if (phy_setup.aneg.speed_1g_fdx &&  /* 1G fdx advertised */
        (lp_1000base_t_status_reg & (1 << 15)) == 0 &&     /* No master/slave fault */
        (lp_1000base_t_status_reg & (1 << 11))) {          /* 1G fdx advertised by LP */
        status->speed = VTSS_SPEED_1G;
        status->fdx = 1;
    } else if (phy_setup.aneg.speed_100m_fdx && /* 100M fdx advertised */
               (mii_status_reg & (1 << 8))) {              /* 100M fdx advertised by LP */
        status->speed = VTSS_SPEED_100M;
        status->fdx = 1;
    } else if (phy_setup.aneg.speed_100m_hdx && /* 100M hdx advertised */
               (mii_status_reg & (1 << 7))) {              /* 100M hdx advertised by LP */
        status->speed = VTSS_SPEED_100M;
        status->fdx = 0;
    } else if (phy_setup.aneg.speed_10m_fdx &&  /* 10M fdx advertised */
               (mii_status_reg & (1 << 6))) {              /* 10M fdx advertised by LP */
        status->speed = VTSS_SPEED_10M;
        status->fdx = 1;
    } else if (phy_setup.aneg.speed_10m_hdx &&  /* 10M hdx advertised */
               (mii_status_reg & (1 << 5))) {              /* 10M hdx advertised by LP */
        status->speed = VTSS_SPEED_10M;
        status->fdx = 0;
    } else {
        status->speed = VTSS_SPEED_UNDEFINED;
        status->fdx = 0;
    }
    VTSS_N("port:%d, lp_1000base_t_status_reg:0x%X, mii_status_reg:0x%X, speed:%d",
           port_no, lp_1000base_t_status_reg, mii_status_reg, status->speed);
}


static void vtss_phy_decode_status_reg(vtss_port_no_t port_no, u16 mii_status_reg, vtss_port_status_t *const status)
{
    // Link up/down
    status->link                   = (mii_status_reg & (1 << 2) ? TRUE : FALSE);
    status->link_down              = (mii_status_reg & (1 << 2) ? FALSE : TRUE);
    status->aneg_complete          = (mii_status_reg & (1 << 5) ? TRUE : FALSE);
    status->remote_fault           = (mii_status_reg & (1 << 4) ? TRUE : FALSE);
    status->unidirectional_ability = ((mii_status_reg & VTSS_F_PHY_UNIDIRECTIONAL_ABILITY) ? TRUE : FALSE);
}

// Function for determining status from PHY registers
// In: port_no - The port in question.
//     lp_1000base_t_status_reg - The value from the register containing the Link partners 1000BASE-T Status (Standard page 10)
//     mii_status_reg - The value from the register containing mii status (Standard page 1)
//     lp_auto_neg_advertisment_reg - The value from the register containing the Link partners auto negotiation advertisement (Standard page 5)
// In/out:   Status  - Pointer to where to put the result
void vtss_phy_reg_decode_status(vtss_port_no_t port_no, u16 lp_auto_neg_advertisment_reg, u16 lp_1000base_t_status_reg,
                                u16 mii_status_reg, const vtss_phy_conf_t phy_setup, vtss_port_status_t *const status)
{
    vtss_phy_flowcontrol_decode_status_private(port_no, lp_auto_neg_advertisment_reg, phy_setup, status); // Flow control
    vtss_phy_link_speeed_decode_status(port_no, lp_1000base_t_status_reg, mii_status_reg, phy_setup, status); // Speed + Duplex

    // Link up/down
    vtss_phy_decode_status_reg(port_no, mii_status_reg, status);
}
vtss_rc vtss_phy_status_get_private(vtss_state_t *vtss_state,
                                    const vtss_port_no_t port_no,
                                    vtss_port_status_t   *const status)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16                   reg, reg10;
    u16                   revision;
    vtss_phy_reset_conf_t *conf = &ps->reset;
    revision = ps->type.revision;

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_N("vtss_phy_status_get_private, port_no: %u", port_no);

        /* Read link status from register 1 */
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_STATUS, &reg));
        /* Set Link Down Indication based on latched in link_status in Reg01 */
        status->link_down = (reg & (1 << 2) ? 0 : 1);

        //VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, &reg10));
        /* Populates the Local PHY Status from Reg01 and Reg09 */
        vtss_phy_decode_status_reg(port_no, reg, status);

        if (status->link_down) {
            /* Read status again if link down (latch low field) */
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_STATUS, &reg));
            status->link = (reg & (1 << 2) ? 1 : 0);
            VTSS_N("status->link = %d, port = %d, reg = 0x%X", status->link, port_no, reg);
        } else {
            status->link = 1;
        }

        // Check if link has been down due to port has been reset
        // If the link has been down, we need to pass that indication up to Application
        if (ps->link_down_due_to_port_reset) {
            status->link_down = TRUE; // Link due the port reset
            status->link = FALSE;     // Force Status to Link Down so Application is notified of the event
            VTSS_D("Setting link_down_due_to_port_reset, port_no = %d", port_no);
            ps->link_down_due_to_port_reset = FALSE; // OK - Link down is now detected by the Application.
        }

        if (ps->status.link != status->link) {
            VTSS_I("Link change ps->status.link=%d, status->link=%d, port_no = %d, status->link_down =%d, ps->setup.mode =%d, vtss_state->warm_start_cur:%d", ps->status.link, status->link, port_no, status->link_down, ps->setup.mode, vtss_state->warm_start_cur);
        }

        if (status->link) {
            /* Cobra's near-end loopback operates as force mode no matter ANEG is set or not, the behavior is the same as SMB6000. */
            vtss_phy_mode_t setup_mode = (ps->family == VTSS_PHY_FAMILY_COBRA && ps->loopback.near_end_enable &&
                                          ps->setup.mode != VTSS_PHY_MODE_POWER_DOWN) ? VTSS_PHY_MODE_FORCED : ps->setup.mode;
            switch (setup_mode) {
            case VTSS_PHY_MODE_ANEG:
                if ((reg & (1 << 5)) == 0) {
                    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, &reg));
                    status->mdi_cross = ((reg & VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_HP_AUTO_MDIX_CROSSOVER_INDICATION) ? TRUE : FALSE);
                    // Link up can not be trusted if auto-neg has not completed.
                    if ((reg & 0x1b) != 0xa) {
                        /* Auto negotiation not complete, link considered down */
                        status->link = 0;
                    } else {
                        if (ps->family == VTSS_PHY_FAMILY_ENZO) {
                            /* Workaround to have SW aware 100FX link up state for VSC8664*/
                            status->speed = VTSS_SPEED_100M;
                            status->fdx = 1;
                        }
                    }
                }

                /* Use register 5 to determine flow control result */
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_AUTONEGOTIATION_LINK_PARTNER_ABILITY, &reg));
                vtss_phy_flowcontrol_decode_status_private(port_no, reg, ps->setup, status); // Decode type of flow control

                if (ps->family == VTSS_PHY_FAMILY_NONE) {
                    /* Standard PHY, use register 10 and 5 to determine speed/duplex */
                    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_STATUS, &reg10));
                    vtss_phy_link_speeed_decode_status(port_no, reg10, reg, ps->setup, status);
                } else {
                    /* Vitesse PHY, use register 28 to determine speed/duplex */
                    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, &reg));
                    status->mdi_cross = ((reg & VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_HP_AUTO_MDIX_CROSSOVER_INDICATION) ? TRUE : FALSE);

                    switch ((reg >> 3) & 0x3) {
                    case 0:
                        status->speed = VTSS_SPEED_10M;
                        break;
                    case 1:
                        status->speed = VTSS_SPEED_100M;
                        break;
                    case 2:
                        status->speed = VTSS_SPEED_1G;
                        break;
                    case 3:
                        status->speed = VTSS_SPEED_UNDEFINED;
                        break;
                    }
                    status->fdx = (reg & (1 << 5) ? 1 : 0);
                }
                break;
            case VTSS_PHY_MODE_FORCED:
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, &reg));
                status->mdi_cross = ((reg & VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_HP_AUTO_MDIX_CROSSOVER_INDICATION) ? TRUE : FALSE);

                if (ps->family == VTSS_PHY_FAMILY_NONE) {
                    status->speed = ps->setup.forced.speed;
                    status->fdx = ps->setup.forced.fdx;
                } else if (ps->family == VTSS_PHY_FAMILY_COBRA && ps->loopback.near_end_enable) {
                    /* Cobra's near-end loopback operates as force mode no matter ANGE is set or not,
                     * speed refer to MII register 0 and always set to FDX */
                    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, &reg));
                    switch (((reg >> 6) << 1 & (reg >> 13)) & 0x3) {
                    case 0:
                        status->speed = VTSS_SPEED_10M;
                        break;
                    case 1:
                        status->speed = VTSS_SPEED_100M;
                        break;
                    case 2:
                        status->speed = VTSS_SPEED_1G;
                        break;
                    case 3:
                        status->speed = VTSS_SPEED_UNDEFINED;
                        break;
                    }
                    /* set FDX for loopback */
                    status->fdx = 1;
                } else {
                    switch ((reg >> 3) & 0x3) {
                    case 0:
                        status->speed = VTSS_SPEED_10M;
                        break;
                    case 1:
                        status->speed = VTSS_SPEED_100M;
                        break;
                    case 2:
                        status->speed = VTSS_SPEED_1G;
                        break;
                    case 3:
                        status->speed = VTSS_SPEED_UNDEFINED;
                        break;
                    }
                    status->fdx = (reg & (1 << 5) ? 1 : 0);
                }
                break;
            case VTSS_PHY_MODE_POWER_DOWN:
                break;
            default:
                VTSS_E("port_no %u, unknown mode %d", port_no, setup_mode);
                return VTSS_RC_ERROR;
            }
        }

        VTSS_N("status0-port:%d, speed:%d, fdx:%d, mode:%d, link:%d", port_no, status->speed, status->fdx, ps->setup.mode, status->link);
        /* Fetch link, duplex and speed for PASSTHRU media mode */

        // Determine if it is a fiber or CU port
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, &reg));
        status->fiber = (((reg >> 6) & 0x3) == 2 ? TRUE : FALSE);
        status->copper = (((reg >> 6) & 0x3) == 1 ? TRUE : FALSE);
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_N("port_no:%d, status->fiber:%d", port_no, status->fiber);

        if (status->fiber) {
            vtss_phy_cl37_lp_abil_get_private(vtss_state, port_no, status);
        }
        VTSS_N("status1-port:%d, speed:%d, fdx:%d, mode:%d, link:%d", port_no, status->speed, status->fdx, ps->setup.mode, status->link);

        /* Handle link down event */
        /* If the prev status was link up and there has been a link down event since last status update */
        if ((!status->link || status->link_down) && ps->status.link) {
            VTSS_I("link down event on port_no %u, status->link = %d, status->link_down = %d, ps->status.link =%d",
                   port_no, status->link, status->link_down, ps->status.link);

            switch (ps->family) {
            case VTSS_PHY_FAMILY_QUATTRO:
            case VTSS_PHY_FAMILY_COBRA:
                /* BZ ? */
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, &reg));
                if ((reg & (1 << 11)) == 0) {
                    /* Briefly power down PHY to avoid problem sometimes seen when
                       changing speed on SmartBit */
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, reg | (1 << 11)));
                    status->link = 0;
                    MEPA_MSLEEP(100);
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, reg));
                }
                /* fall-through */
                /*lint -e(616) */ /* Fall through OK. */
            case VTSS_PHY_FAMILY_SPYDER:
            case VTSS_PHY_FAMILY_LUTON:
            case VTSS_PHY_FAMILY_LUTON_E:
            case VTSS_PHY_FAMILY_LUTON24:
                VTSS_RC(vtss_phy_optimize_receiver_init(vtss_state, port_no));

                if (ps->family != VTSS_PHY_FAMILY_QUATTRO) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear MDI Impedance Force Bit - Safety  */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                }

                if (ps->family == VTSS_PHY_FAMILY_LUTON_E) {
                    /*- Raise the 10-Base T squelch control to eliminate */
                    /*- link-up deadlocks. Observed in 7395 parts so far */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0800, 0x0c00));
                }
                break;

            case VTSS_PHY_FAMILY_ATOM:
            case VTSS_PHY_FAMILY_LUTON26:
                // Work-around for bugzilla#5050/#5568 - Problem with going from 10/100 mode to 1000 auto-neg
                if (revision == VTSS_PHY_ATOM_REV_B || revision == VTSS_PHY_ATOM_REV_A) {
                    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, &reg));
                    if (!(reg & VTSS_F_PHY_MODE_CONTROL_POWER_DOWN)) {
                        // pt. This doesn't work for SFP ports
                        if (conf->media_if == VTSS_PHY_MEDIA_IF_CU && ps->setup.mode == VTSS_PHY_MODE_ANEG) {
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                                       VTSS_F_PHY_MODE_CONTROL_POWER_DOWN,
                                                       VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));
                            VTSS_D("Work-around for bugzilla#5050/#5568, conf->media_if = %d, port_no =%d", conf->media_if, port_no);
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0, VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));
                        }
                    }
                }

                // Work-around for bugzilla#8381 - Link not coming up if disconnected while transmitting (only in 10 Mbit forced mode).
                //We agree that the issue is still present and recommend the following workaround for bugzilla 8381:
                //When the link drops in any copper PHY speed, read MII register 1 and if the link status is still down, do the following:
                //If in forced 10BASE-T mode, momentarily force 10BASE-T link status (after you are sure the MAC is no longer transmitting to the PHY) and then unforce 10BASE-T link status using MII register 22, bit 15 toggling 1/0.
                //    Else momentarily force power-down using MII register 0, bit 11 toggling 1/0.
                // Note that if link status comes back up, the workaround wasnt required.  The only remaining danger is if link status just came up after reading link status and before power-down.  This is unlikely and unlikely to repeat.
                VTSS_D("Mode:%d, speed:%d", ps->setup.mode, ps->setup.forced.speed);
                if (ps->setup.mode == VTSS_PHY_MODE_FORCED) {
                    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_STATUS, &reg));
                    VTSS_N("reg:0x%X", reg);
                    if (reg & VTSS_F_PHY_STATUS_LINK_STATUS) {
                        VTSS_I("Link is up, port:%d", port_no);
                    } else {
                        if (ps->setup.forced.speed == VTSS_SPEED_10M) {
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS,
                                                       VTSS_PHY_EXTENDED_CONTROL_AND_STATUS_FORCE_10BASE_T_HIGH,
                                                       VTSS_PHY_EXTENDED_CONTROL_AND_STATUS_FORCE_10BASE_T_HIGH));

                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS,
                                                       0,
                                                       VTSS_PHY_EXTENDED_CONTROL_AND_STATUS_FORCE_10BASE_T_HIGH));
                            MEPA_MSLEEP(20); // Make sure that status register is updated before we clear it (20 ms chosen due to link pulse interval timer).
                            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_STATUS, &reg)); // Clear the status register, to get rid of the false link up, due to that we have just forced the link up/down.
                            VTSS_D("Bugzilla#8381 work-around 10 MBit force high - port_no:%d reg:0x%X", port_no, reg);
                        } else {
                            VTSS_D("port_no:%d power down/up", port_no);
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                                       VTSS_F_PHY_MODE_CONTROL_POWER_DOWN,
                                                       VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0, VTSS_F_PHY_MODE_CONTROL_POWER_DOWN));
                        }
                    }
                }



                // Set optimize
                VTSS_RC(vtss_phy_optimize_receiver_init(vtss_state, port_no));
                break;

            case VTSS_PHY_FAMILY_TESLA:
                /*-  Start of TESLA_AMS_WORK_AROUND_100FX_RJ45 */
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, &reg));
                if (reg & VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_ENABLED) {  /* Is AMS Set for this port, bit 10: 0x0400 ? */
                    u16   regVal = 0x1000; /* Default for 100FX - AMS */
                    if (!(reg & VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE)) {  /* AMS Set for Fibre Preference */
                        reg = (reg & VTSS_M_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE) >> 8;
                        if (reg == 7) {  /* Only for AMS - 100FX */
                            VTSS_D("port_no:%d AMS Mode, Force 100FX", port_no);
                            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, regVal, regVal));
                        }
                    }
                } /*-  End of TESLA_AMS_WORK_AROUND_100FX_RJ45 */
                break;

            case VTSS_PHY_FAMILY_VIPER:
#if defined(VTSS_VIPER_B_FIFO_RESET) && defined(VTSS_VIPER_B_FIFO_RESET_API_CALL)
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                //Step 0: check if the link down is caused by shutdown
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, &reg));
                VTSS_I("Value of VTSS_PHY_MODE_CONTROL Register port_no %u is 0x%x\n", port_no, reg);
                if (!(reg & VTSS_F_PHY_MODE_CONTROL_POWER_DOWN)) {
                    vtss_phy_ts_fifo_conf_t fifo_conf_viper;
                    memset(&fifo_conf_viper, 0, sizeof(vtss_phy_ts_fifo_conf_t));
                    VTSS_RC(vtss_phy_1588_oos_mitigation_steps_private(vtss_state, port_no, &fifo_conf_viper));
                }
#endif
                //In Link Down event we stop traffic in MACSEC block and disable MAC's
#if defined(VTSS_FEATURE_MACSEC)
                VTSS_I("Stopping MACsec and MAC traffic port_no %u\n", port_no);
                if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC)) {
                    if (vtss_state->macsec_conf[port_no].glb.init.enable) {
                        VTSS_RC(vtss_macsec_store_sa(vtss_state, port_no, 1));
                        VTSS_RC(vtss_macsec_drop_all_traffic_priv(vtss_state, port_no));
                        VTSS_RC(phy_10g_mac_conf(vtss_state, port_no, 0, 1));
                    }
                }
#endif

            case VTSS_PHY_FAMILY_ELISE:
            case VTSS_PHY_FAMILY_NANO :
            case VTSS_PHY_FAMILY_MUSTANG:
            case VTSS_PHY_FAMILY_BLAZER:
            case VTSS_PHY_FAMILY_NONE:
            default:
                break;
            }

            /* Bz#23788 Work-Around for 100BT Link break Issue, after restoring link it does not come up for a long time. */
            /* This only currently applies to Families VIPER and NANO */
            switch (ps->family) {
                case VTSS_PHY_FAMILY_TESLA:
                    if (ps->type.revision >= VTSS_PHY_TESLA_REV_E) {
                        VTSS_RC(vtss_phy_100BaseT_long_linkup_workaround(vtss_state, port_no, TRUE));
                    }
                    break;

                case VTSS_PHY_FAMILY_VIPER:
                case VTSS_PHY_FAMILY_NANO :
                    VTSS_RC(vtss_phy_100BaseT_long_linkup_workaround(vtss_state, port_no, TRUE));
                    break;
                default:
                    break;
            }
        }

        /* Handle link up event */
        if (status->link && (!ps->status.link || status->link_down) && !vtss_state->warm_start_cur) {// Don't do optimize if the status get is done during warmstart.
            VTSS_D("link up event on port_no %u", port_no);
            /* To avoid bz#21483  */
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, &reg10));
            switch (ps->family) {

            case VTSS_PHY_FAMILY_QUATTRO:
                if (status->speed == VTSS_SPEED_1G) {
                    VTSS_RC(vtss_phy_optimize_receiver_reconfig(vtss_state, port_no));
                }
                break;

            case VTSS_PHY_FAMILY_SPYDER:
                if (status->speed == VTSS_SPEED_1G) {
                    VTSS_RC(vtss_phy_optimize_receiver_reconfig(vtss_state, port_no));
                } else if (status->speed == VTSS_SPEED_100M) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x2000, 0x6000));  /*- MDI Impedance offset -1 */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0xa004, 0xe00e));   /*- 10/100 Edge Rate/Amplitude Control */
                } else if (status->speed == VTSS_SPEED_10M) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x6000, 0x6000));  /*- MDI Impedance Offset = +1 */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                }
                break;

            case VTSS_PHY_FAMILY_LUTON:
                if (status->speed == VTSS_SPEED_1G) {
                    VTSS_RC(vtss_phy_optimize_receiver_reconfig(vtss_state, port_no));
                } else if (status->speed == VTSS_SPEED_100M) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x6000));  /*- MDI Impedance offset default */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                    /*- MII 24 can be 0xa000(0xe000), if customer has 100-BT rise time issues */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x8002, 0xe00e));   /*- 10/100 Edge Rate/Amplitude Control */
                } else if (status->speed == VTSS_SPEED_10M) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x2000, 0x6000));  /*- MDI Impedance Offset = -1 */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                }
                break;

            case VTSS_PHY_FAMILY_LUTON_E:
                if (status->speed == VTSS_SPEED_1G) {
                    VTSS_RC(vtss_phy_optimize_receiver_reconfig(vtss_state, port_no));
                    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, 0x2000, 0xe000));  /*- 1000-BT DAC Amplitude control = +2% */
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0030, 0x0038));  /*- 1000-BT Edge Rate Control */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x4000, 0x6000));  /*- MDI Impedance Offset = +2 */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                } else if (status->speed == VTSS_SPEED_100M) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x2000, 0x6000));  /*- MDI Impedance Offset = -1 */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                    /*- MII 24 can be 0xa000(0xe000), if customer has 100-BT rise time issues */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x8002, 0xe00e));   /*- 10/100 Edge Rate/Amplitude Control */
                } else if (status->speed == VTSS_SPEED_10M) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x2000, 0x6000));   /*- MDI Impedance Offset = -1 */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                    /*- Restore the 10-Base T squelch control when link comes up in 10M*/
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0c00));
                }
                break;

            case VTSS_PHY_FAMILY_LUTON24:
                if (status->speed == VTSS_SPEED_1G) {
                    VTSS_RC(vtss_phy_optimize_receiver_reconfig(vtss_state, port_no));
                } else if (status->speed == VTSS_SPEED_100M) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x6000));   /*- MDI Impedance offset default */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0xa002, 0xe00e));    /*- 10/100 Edge Rate/Amplitude Control */
                } else if (status->speed == VTSS_SPEED_10M) {
                    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x1000));  /*- Clear Force Bit */
                    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x2000, 0x6000));   /*- MDI Impedance Offset = -1 */
                    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                }
                break;
            case VTSS_PHY_FAMILY_VIPER:
            case VTSS_PHY_FAMILY_TESLA:
                // Determine if it is a fiber or CU port
                VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, &reg));
                status->fiber = (((reg >> 6) & 0x3) == 2 ? TRUE : FALSE);
                status->copper = (((reg >> 6) & 0x3) == 1 ? TRUE : FALSE);
                VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
                VTSS_N("port_no:%d, status->fiber:%d", port_no, status->fiber)

                ps->status = *status;

#if defined(VTSS_OPT_PHY_TIMESTAMP)
                /* On link up ,modifying latency values according to speed */
                VTSS_RC(vtss_phy_ts_phy_status_change_priv(vtss_state, port_no));
#endif
            /* fall-through */
            /* Falling thru - Intentional */

            case VTSS_PHY_FAMILY_COOPER:
            case VTSS_PHY_FAMILY_ENZO:
            case VTSS_PHY_FAMILY_ATOM:
            case VTSS_PHY_FAMILY_LUTON26:
            case VTSS_PHY_FAMILY_ELISE:
            case VTSS_PHY_FAMILY_NANO :
                if (status->speed == VTSS_SPEED_1G) {
                    VTSS_RC(vtss_phy_optimize_receiver_reconfig(vtss_state, port_no));
                }
                break;

            case VTSS_PHY_FAMILY_MUSTANG:
            case VTSS_PHY_FAMILY_BLAZER:
            case VTSS_PHY_FAMILY_COBRA:
            case VTSS_PHY_FAMILY_INTRIGUE:
            case VTSS_PHY_FAMILY_NONE:
                // Removing the Default Specifically to cause compilation warning if another PHY Family is added without adding to this feature set.
                //default:
                break;
            }

#if defined(VTSS_FEATURE_MACSEC)
            if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC)) {
                ps->status = *status; // When booting "vtss_state phy status" is not updated yet, so we need to make sure that status is updated before calling vtss_macsec_speed_conf_priv (We do it all the time, even though it in fact was only needed the first time we come through here).
                if (vtss_state->macsec_conf[port_no].glb.init.enable) {
                    VTSS_RC(vtss_macsec_drop_all_traffic_priv(vtss_state, port_no));
                    VTSS_RC(phy_10g_mac_conf(vtss_state, port_no, 0, 1));
                    VTSS_RC(vtss_macsec_speed_conf_priv(vtss_state, port_no, 1, 1));
                    VTSS_RC(phy_10g_mac_conf(vtss_state, port_no, 1, 1));
                }
            }
#endif

        }

        /* If the prev status was link down and current status is link down, then see if Long Link Work-Around applies  */
        if (((!status->link || status->link_down) && !ps->status.link) &&
              (conf->media_if == VTSS_PHY_MEDIA_IF_CU) &&
              (ps->setup.mode == VTSS_PHY_MODE_FORCED) &&
              (ps->setup.forced.speed == VTSS_SPEED_100M)) {

            VTSS_D("link down, Copper, Forced Mode-100M on port_no %u, status->link = %d, status->link_down = %d, ps->status.link =%d",
                    port_no, status->link, status->link_down, ps->status.link);

            /* Bz#23788 Work-Around for 100BT Link break Issue, after restoring link it does not come up for a long time. */
            /* This only currently applies to Families VIPER and NANO and TESLA Rev. E Only */
            switch (ps->family) {
                case VTSS_PHY_FAMILY_TESLA:
                    if (ps->type.revision >= VTSS_PHY_TESLA_REV_E) {
                        VTSS_RC(vtss_phy_100BaseT_long_linkup_workaround(vtss_state, port_no, FALSE));
                    }
                    break;

                    /* This only currently applies to Families VIPER and NANO, All revisions */
                case VTSS_PHY_FAMILY_VIPER:
                case VTSS_PHY_FAMILY_NANO :
                    VTSS_RC(vtss_phy_100BaseT_long_linkup_workaround(vtss_state, port_no, FALSE));
                    break;
                default:
                    break;
            }
        }

        // Determine if it is a fiber or CU port
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, &reg));
        status->fiber = (((reg >> 6) & 0x3) == 2 ? TRUE : FALSE);
        status->copper = (((reg >> 6) & 0x3) == 1 ? TRUE : FALSE);
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_N("port_no:%d, status->fiber:%d", port_no, status->fiber)


    /* Save status */
    ps->status = *status;
    return VTSS_RC_OK;
}



static vtss_rc vtss_phy_power_conf_set_private(vtss_state_t *vtss_state,
                                               const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_power_conf_t *conf = &ps->conf_power;

    /* Check to see if operation supported on this PHY */
    switch (ps->family) {
    case VTSS_PHY_FAMILY_QUATTRO:
    case VTSS_PHY_FAMILY_LUTON_E:
    case VTSS_PHY_FAMILY_LUTON24:
    case VTSS_PHY_FAMILY_SPYDER:
    case VTSS_PHY_FAMILY_ENZO:
    case VTSS_PHY_FAMILY_COBRA:
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO :
    case VTSS_PHY_FAMILY_COOPER:
        break;
    default:
        VTSS_E("Power control not supported, PHY family %d", ps->family);
        return VTSS_RC_ERROR;
    }

    switch (conf->mode) {
    case VTSS_PHY_POWER_ACTIPHY:
        /* Restore original power level settings */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_TEST_PAGE_12, 0x0000, 0xfc00));
        // For now don't restore at warm start if nothing has changed
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x2000, 0x2000, 0x0));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        /* Enable Link down Power savings - aka / "Enhanced ActiPHY" */
        if (ps->family == VTSS_PHY_FAMILY_COOPER) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, COOPER_VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, 0x0020, 0x0020));
        } else {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS,
                                            VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ACTIPHY_MODE_ENABLE,
                                            VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ACTIPHY_MODE_ENABLE));
        }
        ps->power.vtss_phy_actiphy_on = 1;
        ps->power.vtss_phy_power_dynamic = 0;
        ps->power.pwrusage = VTSS_PHY_ACTIPHY_PWR;
        break;
    case VTSS_PHY_POWER_DYNAMIC:
        /* Enabled Link-up power savings - algorithm runs at link-up time */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        if (ps->family == VTSS_PHY_FAMILY_COOPER) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, COOPER_VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, 0x0000, 0x0020));
        } else {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, 0x0000,
                                            VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ACTIPHY_MODE_ENABLE));
        }
        ps->power.vtss_phy_actiphy_on = 0;
        ps->power.vtss_phy_power_dynamic = 1;
        break;
    case VTSS_PHY_POWER_ENABLED:
        /* Enable ActiPHY and link-up power savings */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        if (ps->family == VTSS_PHY_FAMILY_COOPER) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, COOPER_VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, 0x0020, 0x0020));
        } else {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS,
                                            VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ACTIPHY_MODE_ENABLE,
                                            VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ACTIPHY_MODE_ENABLE));
        }
        ps->power.vtss_phy_actiphy_on = 1;
        ps->power.vtss_phy_power_dynamic = 1;
        ps->power.pwrusage = VTSS_PHY_ACTIPHY_PWR;
        break;
    case VTSS_PHY_POWER_NOMINAL:
        /* Restore original power level settings */
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_TEST_PAGE_12, 0x0000, 0xfc00));
        // For now don't restore at warm start if nothing has changed
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x2000, 0x2000, 0x0));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        if (ps->family == VTSS_PHY_FAMILY_COOPER) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, COOPER_VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, 0x0000, 0x0020));
        } else {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, 0x0000,
                                            VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ACTIPHY_MODE_ENABLE));
        }
        ps->power.vtss_phy_actiphy_on = 0;
        ps->power.vtss_phy_power_dynamic = 0;
        ps->power.pwrusage = VTSS_PHY_LINK_DOWN_PWR ;
        break;
    default:
        break;
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_conf_1g_set_private(vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no)
{
    vtss_phy_conf_1g_t *conf = &vtss_state->phy_state[port_no].conf_1g;
    u16                reg, reg_cont = 0, reg_status = 0;


        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, &reg_cont));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_STATUS, &reg_status));

        reg  = ((conf->master.cfg ? 1 : 0) << 12) | ((conf->master.val ? 1 : 0) << 11);

        /* Commit 1000-BT Control values */
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, reg, 0x1800));

        /* Re-start Auto-Neg if Master/Slave Manual Config/Value changed */
        if ((reg_cont ^ reg) & 0x1800) {
            if ((reg & 0x1000) || (reg_status & 0x8000)) { /* Only start Auto-neg if Manuel is selected or master/slave resolution failed */
                if (!vtss_state->sync_calling_private) {
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0x0200, 0x0200));
                }
            }
        }
    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_status_1g_get_private(vtss_state_t *vtss_state,
                                              const vtss_port_no_t  port_no,
                                              vtss_phy_status_1g_t  *const status)
{
    u16 reg = 0;

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_STATUS, &reg));

        status->master_cfg_fault = (reg >> 15) & 1;
        status->master = (reg >> 14) & 1;
    return VTSS_RC_OK;
}

/* Function to set the current micro peek/poke address */
static vtss_rc vtss_phy_set_micro_set_addr_private(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t  port_no,
                                                   const u16             addr)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_type_t       phy_id;
    u16                   reg18g;
    vtss_rc               rc;

    if ((rc = vtss_phy_id_get_private(vtss_state, port_no, &phy_id)) != VTSS_RC_OK) {
        return rc;
    }

    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
        VTSS_RC(VTSS_PHY_BASE_PORTS_FOUND); // Make sure that base ports are found
        VTSS_RC(vtss_phy_page_ext(vtss_state, phy_id.base_port_no));        // Switch to extended register-page 1
        VTSS_RC(PHY_WR_PAGE(vtss_state, phy_id.base_port_no, VTSS_PHY_VERIPHY_CTRL_REG2, addr));
        VTSS_RC(vtss_phy_page_std(vtss_state, phy_id.base_port_no));        // Switch to standard register-page
        reg18g = 0xc000;
        break;

    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
        if (ps->type.revision > VTSS_PHY_ATOM_REV_A) {
            if (addr & 0x4000) {
                reg18g = 0xd000 | (addr & 0xfff);
            } else {
                reg18g = 0xc000 | (addr & 0xfff);
            }
            break;
        }
        /* fall-through */
    // Let Luton26, Atom12, and Tesla rev. A fall through to error
    default:
        VTSS_E("Micro peek/poke not supported, PHY family %d, revision %u", ps->family, ps->type.revision);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, reg18g));  // set micro peek/poke address
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    return VTSS_RC_OK;
}

/* Function to peek a byte from the current micro address */
static vtss_rc vtss_phy_micro_peek_private(vtss_state_t *vtss_state,
                                           const vtss_port_no_t  port_no,
                                           const BOOL            post_increment,
                                           u8                   *peek_byte_ptr)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16                   reg18g;

    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
        break;

    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
        if (ps->type.revision > VTSS_PHY_ATOM_REV_A) {
            break;
        }
        /* fall-through */
    // Let Luton26, Atom12, and Tesla rev. A fall through to error
    default:
        VTSS_E("Micro peek/poke not supported, PHY family %d, revision %u", ps->family, ps->type.revision);
        return VTSS_RC_ERROR;
    }

    // Setup peek command with or without post-increment
    reg18g = (post_increment) ? 0x9007 : 0x8007;

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, reg18g));  // Peek micro memory
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));  // read to get peek'ed byte
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));        // Switch to standard register-page

    if (reg18g & 0x4000) {
        return VTSS_RC_ERROR;
    }

    *peek_byte_ptr = (reg18g >> 4) & 0xff;
    return VTSS_RC_OK;
}

/* Function to poke a byte to the current micro address */
static vtss_rc vtss_phy_micro_poke_private(vtss_state_t *vtss_state,
                                           const vtss_port_no_t  port_no,
                                           const BOOL            post_increment,
                                           const u8              poke_byte)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    u16                   reg18g;

    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
        break;

    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
        if (ps->type.revision > VTSS_PHY_ATOM_REV_A) {
            break;
        }
        /* fall-through */
    // Let Luton26, Atom12, and Tesla rev. A fall through to error
    default:
        VTSS_E("Micro peek/poke not supported, PHY family %d, revision %u", ps->family, ps->type.revision);
        return VTSS_RC_ERROR;
    }

    // Setup peek command with or without post-increment
    reg18g = ((post_increment) ? 0x9006 : 0x8006) | (((u16)poke_byte) << 4);

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, reg18g));  // Poke byte into micro memory
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    return VTSS_RC_OK;
}

/* Configure 23G/24G (Recovered Clock1/Recovered Clock2) */
static vtss_rc vtss_phy_clock_conf_set_private(vtss_state_t *vtss_state,
                                               const vtss_port_no_t         port_no,
                                               const vtss_phy_recov_clk_t   clock_port)
{
    u16  reg_val = 0;
    vtss_phy_type_t phy_id;
    vtss_phy_clock_conf_t conf;
    vtss_port_no_t        source;
    BOOL                  use_squelch_workaround;
    u16                   save_squelch_ctrl_addr;
    u8                    other_port_save_squelch_ctrl = 0;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    VTSS_RC(VTSS_PHY_BASE_PORTS_FOUND); // Make sure that base ports are found
    conf = vtss_state->phy_state[phy_id.base_port_no].clock_conf[clock_port].conf;
    source = vtss_state->phy_state[phy_id.base_port_no].clock_conf[clock_port].source;

    switch (vtss_state->phy_state[port_no].family) {
    // These families support clock recovery, but need a squelch work-around
    case VTSS_PHY_FAMILY_VIPER:
        if (ps->type.revision == VTSS_PHY_VIPER_REV_A) {
            use_squelch_workaround = TRUE;
        } else {
            use_squelch_workaround = FALSE;
        }
        break;

    case VTSS_PHY_FAMILY_TESLA:
        use_squelch_workaround = TRUE;
        break;

    // These families support clock recovery
    case VTSS_PHY_FAMILY_ENZO:
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
        use_squelch_workaround = FALSE;
        break;

    case VTSS_PHY_FAMILY_ELISE:
        // Only Certain chip Dash Numbers support clock configuration. The chip detection is determined by register 18E2
        VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_REVERED_18, &reg_val));
        reg_val &= 0x3f;
        if ((reg_val == 0x10) || (reg_val == 0x13)) {  // VSC8514-10 and VSC8514-13 do not support Recovered Clock
            return VTSS_RC_ERR_PHY_CLK_CONF_NOT_SUPPORTED;
        }
        use_squelch_workaround = FALSE;
        break;

    case VTSS_PHY_FAMILY_NANO:
        // Only Certain chip Dash Numbers support clock configuration. The chip detection is determined by register 18E2
        VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_REVERED_18, &reg_val));
        reg_val &= 0x3f;
        if (reg_val == 0x13) {  // VSC8502-13 do not support Recovered Clock
            return VTSS_RC_ERR_PHY_CLK_CONF_NOT_SUPPORTED;
        }
        use_squelch_workaround = FALSE;
        break;

    default:
        // All other families don't support clock recovery
        if (!vtss_state->sync_calling_private) {
            VTSS_E("clock recovery setup not supported on port %u, Chip family:%s", port_no + 1, vtss_phy_family2txt(vtss_state->phy_state[port_no].family));
            return VTSS_RC_ERR_PHY_CLK_CONF_NOT_SUPPORTED;
        }
        return VTSS_RC_OK;
    }
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    if (clock_port == VTSS_PHY_RECOV_CLK1) {
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_RECOVERED_CLOCK_0_CONTROL, &reg_val));
    } else {
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_RECOVERED_CLOCK_1_CONTROL, &reg_val));
    }

    /* return if already disabled and new source is disable (due to the 'weired' disable) */
    if (!(reg_val & 0x8000) && (conf.src == VTSS_PHY_CLK_DISABLED)) {
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        return VTSS_RC_OK;
    }

    //Compare the channel_id with sync source inside the register for the given port
    // Applicable only for WARM sync
    if ((vtss_state->sync_calling_private) &&
        (((reg_val >> 11) & 0xF) != ps->type.channel_id)) {
        VTSS_D("\n%s: WARM synch : Ignore if sync source %d does not match "
               "this port %d", __FUNCTION__, source, port_no);
        return VTSS_RC_OK;
    }

    switch (conf.src) {
    case VTSS_PHY_SERDES_MEDIA:
        reg_val = 0x8000;
        break;
    case VTSS_PHY_COPPER_MEDIA:
        reg_val = 0x8001;
        break;
    case VTSS_PHY_TCLK_OUT:
        reg_val = 0x8002;
        break;
    case VTSS_PHY_LOCAL_XTAL:
        reg_val = 0x8003;
        break;
    case VTSS_PHY_CLK_DISABLED:
        reg_val = (reg_val + 1) & 0x0001;
        break; /* Know this is weird - have to set media wrong to get clock out disabled */
    default:
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        return VTSS_RC_OK;
    }

    if (vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_ENZO) {
        reg_val |= (((source & 3) << 12) | (conf.freq << 8) | (conf.squelch << 4));
    }


    switch (vtss_state->phy_state[port_no].family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
        reg_val |= ((((vtss_phy_chip_port(vtss_state, source) % 12) & 0xF) << 11) | (conf.freq << 8) | (conf.squelch << 4));
        break;
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO :
        reg_val |= ((((vtss_phy_chip_port(vtss_state, source) % 4) & 0xF) << 11) | (conf.freq << 8) | (conf.squelch << 4));
        break;
    default:
        break;
    }

    if (use_squelch_workaround) {
        VTSS_RC(squelch_workaround_private(vtss_state, port_no, FALSE));

        // Set address to save squelch control for the other recovered-clock port
        if ((vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_TESLA) &&
            (ps->type.revision == VTSS_PHY_TESLA_REV_A)) {
            save_squelch_ctrl_addr = (clock_port == VTSS_PHY_RECOV_CLK1) ? 0x00BE : 0x00BD;
        } else {
            switch (vtss_state->phy_state[phy_id.base_port_no].micro_patch_crc) {
            case 0xB7C2:  /* ALL Tesla API 4.04 -> 4.32 */
                save_squelch_ctrl_addr = (clock_port == VTSS_PHY_RECOV_CLK1) ? 0x0025 : 0x0026;
                VTSS_D("\n%s: port %d  Squelch Addr: 0x0025 / 0x0026 ", __FUNCTION__, port_no);
                break;
            case 0x9995:  /* ALL Viper Rev. A      */
                save_squelch_ctrl_addr = (clock_port == VTSS_PHY_RECOV_CLK1) ? 0x0016 : 0x0017;
                VTSS_D("\n%s: port %d  Squelch Addr: 0x0016 / 0x0017 ", __FUNCTION__, port_no);
                break;
            case 0x2BB0:  /* ALL Tesla API 4.39 -> 4.66 */
            case 0x29E8:  /* ALL Tesla API 4.67, 4.67.01, 4.67.02 w/o OOS enabled */
                save_squelch_ctrl_addr = (clock_port == VTSS_PHY_RECOV_CLK1) ? 0x002a : 0x002b;
                VTSS_D("\n%s: port %d  Squelch Addr: 0x002a / 0x002b ", __FUNCTION__, port_no);
                break;
            default:
                save_squelch_ctrl_addr = (clock_port == VTSS_PHY_RECOV_CLK1) ? 0x002a : 0x002b;
                VTSS_E("\n%s: port %d  ERROR, CRC Case not handled: Squelch Addr: 0x002a / 0x002b ", __FUNCTION__, port_no);
            }
        }
        VTSS_RC(vtss_phy_set_micro_set_addr_private(vtss_state, port_no, save_squelch_ctrl_addr));

        // Peek saved squelch control for the other recovered-clock port
        VTSS_RC(vtss_phy_micro_peek_private(vtss_state, port_no, 0, &other_port_save_squelch_ctrl));
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

    /* Tesla and VIPER are only ones to set use_squelch_workaround=TRUE */
    if (use_squelch_workaround) {
        reg_val &= ~(0x8000);
        VTSS_I("\n%s: port %d  Clearing bit 23G.15 or 24G.15; Reg_val: 0x%04x", __FUNCTION__, port_no, reg_val);
    }

    if (clock_port == VTSS_PHY_RECOV_CLK1) {
        if (vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_ENZO) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_RECOVERED_CLOCK_0_CONTROL, reg_val, 0xFFFF, 0x7FFF));     /* On Enzo it is not possible to set bit 15 - do not check */
        } else {
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_RECOVERED_CLOCK_0_CONTROL, reg_val));
            VTSS_I("\n%s: port %d  VTSS_PHY_RECOV_CLK1: Reg_val: 0x%04x", __FUNCTION__, port_no, reg_val);
        }
    } else {
        if (vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_ENZO) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED_CHK_MASK(vtss_state, port_no, VTSS_PHY_RECOVERED_CLOCK_1_CONTROL, reg_val, 0xFFFF, 0x7FFF));     /* On Enzo it is not possible to set bit 15 - do not check */
        } else {
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_RECOVERED_CLOCK_1_CONTROL, reg_val));
            VTSS_I("\n%s: port %d  VTSS_PHY_RECOV_CLK2: Reg_val: 0x%04x", __FUNCTION__, port_no, reg_val);
        }
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    if (use_squelch_workaround) {
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(squelch_workaround_private(vtss_state, port_no, TRUE));
        // Poke back saved squelch control for the other recovered-clock port
        VTSS_RC(vtss_phy_micro_poke_private(vtss_state, port_no, 0, other_port_save_squelch_ctrl));
        // Switch back to GPIO page
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        /* Tesla and VIPER are only ones to set use_squelch_workaround=TRUE */
        if (conf.src != VTSS_PHY_CLK_DISABLED) {
            reg_val |= (0x8000);
            if (clock_port == VTSS_PHY_RECOV_CLK1) {
                VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_RECOVERED_CLOCK_0_CONTROL, reg_val));
                VTSS_I("\n%s: port %d  VTSS_PHY_RECOV_CLK1: Reg_val: 0x%04x", __FUNCTION__, port_no, reg_val);
            } else {
                VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_RECOVERED_CLOCK_1_CONTROL, reg_val));
                VTSS_I("\n%s: port %d  VTSS_PHY_RECOV_CLK2: Reg_val: 0x%04x", __FUNCTION__, port_no, reg_val);
            }
        }

    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}


// Setting LED mode (blink mode)
//
// In : port : Phy port
//      led : LED mode to run the LEDs in
//      led_number : Which LED to configure
//
// Return :  VTSS_RC_OK is setup was preformed correct else VTSS_RC_ERROR
static vtss_rc vtss_phy_luton26_led_mode_set_private(vtss_state_t *vtss_state,
                                                     const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps  = &vtss_state->phy_state[port_no];
    u16 reg19e_mode = 0;
    u16 reg29_mode = 0;

    switch (vtss_state->led_mode_select.mode) {
    case VTSS_PHY_LED_MODE_LINK_ACTIVITY:
        reg29_mode = 0;
        break;
    case VTSS_PHY_LED_MODE_LINK1000_ACTIVITY:
        reg29_mode = 1;
        break;
    case VTSS_PHY_LED_MODE_LINK100_ACTIVITY:
        reg29_mode = 2;
        break;
    case VTSS_PHY_LED_MODE_LINK10_ACTIVITY:
        reg29_mode = 3;
        break;
    case VTSS_PHY_LED_MODE_LINK100_1000_ACTIVITY:
        reg29_mode = 4;
        break;
    case VTSS_PHY_LED_MODE_LINK10_1000_ACTIVITY:
        reg29_mode = 5;
        break;
    case VTSS_PHY_LED_MODE_LINK10_100_ACTIVITY:
        reg29_mode = 6;
        break;
    case VTSS_PHY_LED_MODE_LINK100BASE_FX_1000BASE_X_ACTIVITY:
        reg29_mode = 7;
        break;
    case VTSS_PHY_LED_MODE_DUPLEX_COLLISION:
        reg29_mode = 8;
        break;
    case VTSS_PHY_LED_MODE_COLLISION:
        reg29_mode = 9;
        break;
    case VTSS_PHY_LED_MODE_ACTIVITY:
        reg29_mode = 10;
        break;
    case VTSS_PHY_LED_MODE_BASE100_FX_1000BASE_X_FIBER_ACTIVITY:
        reg29_mode = 11;
        break;
    case VTSS_PHY_LED_MODE_AUTONEGOTIATION_FAULT:
        reg29_mode = 12;
        break;
    case VTSS_PHY_LED_MODE_FORCE_LED_OFF:
        reg29_mode = 14;
        break;
    case VTSS_PHY_LED_MODE_FORCE_LED_ON:
        reg29_mode = 15;
        break;
    case VTSS_PHY_LED_MODE_LINK1000BASE_X_ACTIVITY:
        reg29_mode = 0;
        reg19e_mode = 1;
        break;
    case VTSS_PHY_LED_MODE_LINK100BASE_FX_ACTIVITY:
        reg29_mode = 1;
        reg19e_mode = 1;
        break;
    case VTSS_PHY_LED_MODE_BASE1000_ACTIVITY:
        reg29_mode = 2;
        reg19e_mode = 1;
        break;
    case VTSS_PHY_LED_MODE_BASE100_FX_ACTIVITY:
        reg29_mode = 3;
        reg19e_mode = 1;
        break;
    case VTSS_PHY_LED_MODE_FAST_LINK_FAIL:
        reg29_mode = 6;
        reg19e_mode = 1;
        break;
    default:
        VTSS_E("Invalid mode. Not supported for family: %s, port = %d", vtss_phy_family2txt(ps->family), port_no);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    switch (vtss_state->led_mode_select.number) {
    case LED3:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_LED_MODE_SELECT, reg29_mode << 12, 0xF000));
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL, reg19e_mode << 15, 0x8000));
        break;
    case LED2:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_LED_MODE_SELECT, reg29_mode << 8, 0x0F00));
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL, reg19e_mode << 14, 0x4000));
        break;
    case LED1:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_LED_MODE_SELECT, reg29_mode << 4, 0x00F0));
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL, reg19e_mode << 13, 0x2000));
        break;
    case LED0:
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_LED_MODE_SELECT, reg29_mode, 0x000F));
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_MODE_CONTROL, reg19e_mode << 12, 0x1000));
        break;
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

// Cobra PHY LED mode Setting (blink mode)
//
// In : port_no : Phy port number
//
// Return :  VTSS_RC_OK is setup was preformed correct else VTSS_RC_ERROR
static vtss_rc vtss_phy_cobra_led_mode_set_private(vtss_state_t         *vtss_state,
                                                   const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps  = &vtss_state->phy_state[port_no];
    vtss_phy_led_mode_t   mode = vtss_state->led_mode_select.mode;
    vtss_phy_led_number_t led  = vtss_state->led_mode_select.number;
    u8 val;

    /* Enable Force LED ON/OFF 20E Bit:13 */
    if ((mode == VTSS_PHY_LED_MODE_FORCE_LED_ON) || (mode == VTSS_PHY_LED_MODE_FORCE_LED_OFF)) {
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        if (mode == VTSS_PHY_LED_MODE_FORCE_LED_ON) {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, 1 << 13, 0x2000));
        } else {
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, 0 << 13, 0x2000));
        }
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        return VTSS_RC_OK;
    }

    if (led > LED2) {
        VTSS_E("Invalid LED number. Not supported for family: %s, port = %d", vtss_phy_family2txt(ps->family), port_no);
        return VTSS_RC_ERROR;
    }

    if (led == LED2) {
        /* LED[2] Bit 11:10 */
        val = 2;
        switch (mode) {
	case VTSS_PHY_LED_MODE_LINK10_ACTIVITY:
            val = 0;
            break;
        case VTSS_PHY_LED_MODE_DUPLEX_COLLISION:
            val = 1;
            break;
	case VTSS_PHY_LED_MODE_LINK_ACTIVITY:
            val = 2;
            break;
	case VTSS_PHY_LED_MODE_LINK_TX:
            val = 3;
            break;
        default:
            VTSS_E("Invalid Mode selection on LED[2]. Not supported for family: %s, port = %d", vtss_phy_family2txt(ps->family), port_no);
            return VTSS_RC_ERROR;
        }
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_COBRA_LED_MODE_SELECT, val << 10, 0x0C00));
    } else if (led == LED1) {
        /* LED[1] Bit 9:8 */
        val = 2;
        switch (mode) {
        case VTSS_PHY_LED_MODE_LINK100_ACTIVITY:
            val = 0;
            break;
        case VTSS_PHY_LED_MODE_LINK10_100_ACTIVITY:
            val = 1;
            break;
        case VTSS_PHY_LED_MODE_LINK_ACTIVITY:
            val = 2;
            break;
        case VTSS_PHY_LED_MODE_LINK100_1000_ACTIVITY:
            val = 3;
            break;
        default:
            VTSS_E("Invalid Mode selection on LED[1]. Not supported for family: %s, port = %d", vtss_phy_family2txt(ps->family), port_no);
            return VTSS_RC_ERROR;
        }
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_COBRA_LED_MODE_SELECT, val << 8, 0x0300));
    } else {
        /* LED[0] Bit 7:6 */
        val = 2;
        switch (mode) {
        case VTSS_PHY_LED_MODE_LINK1000_ACTIVITY:
            val = 0;
            break;
        case VTSS_PHY_LED_MODE_LINK_ACTIVITY:
            val = 1;
            break;
        case VTSS_PHY_LED_MODE_LINK_FAULT:
            val = 2;
            break;
        case VTSS_PHY_LED_MODE_LINK_RX:
            val = 3;
            break;
        default:
            VTSS_E("Invalid Mode selection on LED[0]. Not supported for family: %s, port = %d", vtss_phy_family2txt(ps->family), port_no);
            return VTSS_RC_ERROR;
        }
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_COBRA_LED_MODE_SELECT, val << 6, 0x00C0));
    }

    return VTSS_RC_OK;
}

// Setting LED mode (blink mode)
//
// In : port : Phy port
//
// Return :  VTSS_RC_OK is setup was preformed correct else VTSS_RC_ERROR
static vtss_rc vtss_phy_led_mode_set_private(vtss_state_t *vtss_state,
                                             const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    switch (ps->family) {
    case VTSS_PHY_FAMILY_COBRA:
        return vtss_phy_cobra_led_mode_set_private(vtss_state, port_no);
        break;
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_TESLA:
        return vtss_phy_luton26_led_mode_set_private(vtss_state, port_no);
        break;
    default:
        VTSS_E("Not supported for family: %s, port = %d", vtss_phy_family2txt(ps->family), port_no);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_LED_POW_REDUC)
// Setting LED intensity.
//
// In : port : Phy port
//
// Return :  VTSS_RC_OK is setup was preformed correct else VTSS_RC_ERROR
static vtss_rc vtss_phy_led_intensity_set_private(vtss_state_t *vtss_state,
                                                  const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps;
    vtss_phy_family_t     family;

    if (port_no >= VTSS_PORTS) {
        return VTSS_RC_ERR_PHY_PORT_OUT_RANGE;
    }

    ps = &vtss_state->phy_state[port_no];

    /* Save setup */
    family = ps->family;

    VTSS_N("Family: %s, port_no = %u, vtss_state->led_intensity = %d",
           vtss_phy_family2txt(family), port_no, vtss_state->led_intensity);


    switch (family) {
    case VTSS_PHY_FAMILY_ENZO:
    case VTSS_PHY_FAMILY_SPYDER:
        // We only operate with on/off for these PHYs
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        if (vtss_state->led_intensity == 0) {
            // Turn LED off
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_LED_MODE_SELECT, 0xEEEE, 0xFFFF));
        } else {
            // Turn LED on
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_LED_MODE_SELECT, 0xEE64, 0xFFFF));
        }

        break;
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO :
        // Datasheet section 4.6.15, register 25G
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        // Set intensity. Multiply with 2 in order to convert from percent to register values (See datasheet 25G)
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_ENHANCED_LED_CONTROL, (vtss_state->led_intensity * 2) << 8, 0xFF00));
        break;

    default:
        VTSS_E("LED intensity not supported for family: %s, port = %d", vtss_phy_family2txt(family), port_no);
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}



// Setting the enhanced LED control initial state (Should only be set once at startup).
//
// In : port  : Phy port
//      conf  : Enhanced LED control configuration
//
// Return :  VTSS_RC_OK is setup was preformed correct else VTSS_RC_ERROR
static vtss_rc vtss_phy_enhanced_led_control_init_private(vtss_state_t *vtss_state,
                                                          const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_family_t     family;

    /* Save setup */
    VTSS_D("enter, port_no: %u", port_no);
    family = ps->family;

    vtss_state->phy_led_control_warm_start_port_list[port_no] = TRUE; // Signaling that this port is used for LED control (for warm start)

    switch (family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO :
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_ENHANCED_LED_CONTROL, vtss_state->enhanced_led_control.ser_led_output_2 << 7, 0x80)); // Datasheet section 4.6.15, register 25G
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_ENHANCED_LED_CONTROL, vtss_state->enhanced_led_control.ser_led_output_1 << 6, 0x40)); // Datasheet section 4.6.15, register 25G
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_ENHANCED_LED_CONTROL, vtss_state->enhanced_led_control.ser_led_frame_rate << 3, 0x38)); // Datasheet section 4.6.15, register 25G
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_ENHANCED_LED_CONTROL, vtss_state->enhanced_led_control.ser_led_select << 1, 0x06)); // Datasheet section 4.6.15, register 25G


        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        if (!vtss_state->enhanced_led_control.ser_led_output_2 && !vtss_state->enhanced_led_control.ser_led_output_1) {
            VTSS_N("ser_led_output_2:%d, ser_led_output_1:%d", vtss_state->enhanced_led_control.ser_led_output_2, vtss_state->enhanced_led_control.ser_led_output_1);
            // If non serial LED mode, we enable LED pulsing
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_LED_BEHAVIOR, VTSS_F_PHY_LED_BEHAVIOR_LED_PULSING_ENABLE, VTSS_F_PHY_LED_BEHAVIOR_LED_PULSING_ENABLE));
        }  else {
            VTSS_N("ser_led_output_2:%d, ser_led_output_1:%d", vtss_state->enhanced_led_control.ser_led_output_2, vtss_state->enhanced_led_control.ser_led_output_1);
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_LED_BEHAVIOR, 0, VTSS_F_PHY_LED_BEHAVIOR_LED_PULSING_ENABLE));
        }
        break;

    default:
        VTSS_E("Enhanced LED control not supported for family: %s", vtss_phy_family2txt(family));
        return VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}

#endif


/* ================================================================= */
// Private Function that is called for adjusting the slope and offset
// for the Temp calculation function
/**
 * \brief Function for Adjusting Temp Calculations
 * \param adc_val                      [IN]    ADC Value read from PHY Reg VTSS_PHY_TEMP_VAL
 * \param offset_adj                   [IN]    The offset adjustment for PHY device from Reg VTSS_PHY_GPIO_11
 * \param slope_adj                    [IN]    The slope adjustment for PHY device from Reg VTSS_PHY_GPIO_12
 * \return Return Value - Temp Value in counts
 */
// Have to scale up by 1000 so we do not use Floating Points
#define TMON_BASE_SLOPE   (-714)    //  (-0.714) * 1000
#define TMON_BASE_OFFSET   (135300) //  (135.3) * 1000
short vtss_phy_tmon_adjust_private ( const u8 adc_val, const u8 offset_adj, const u8  slope_adj)
{
    int    slope, offset, val;
    short  rval = 0;

    slope = (int)slope_adj * 1000;
    slope = TMON_BASE_SLOPE + (slope / 512);     //range +/-0.25
    offset = (int)offset_adj * 1000;
    offset = TMON_BASE_OFFSET + offset;          // range +/-128
    val = adc_val;
    val = val * slope + offset;

    // Round to nearest int,
    // Done by adding 0.5 (scaled up by 1000) and then truncating the result
    rval = (val + 500) / 1000;
    VTSS_N("adc_val = %d, slope = %d,  offset = %d,  val = %d, rval = %d ", adc_val, slope, offset, val, rval);
    return (rval);
}


/* - Chip temperature  ----------------------------------- */
/* ================================================================= */
// Private Function that is called for calculating the Chip Temperature
/**
 * \brief Function for Calculating Chip Temperature
 * \param vtss_state                   [IN]    Port Structure
 * \param port_no                      [IN]    The Port No.
 * \param temp_reading                 [OUT]   The unscaled Temp Reading
 * \Return: VTSS_RC_OK if we got the temperature - else error code
 */
static vtss_rc vtss_phy_read_temp_reg (vtss_state_t *vtss_state,
                                       vtss_port_no_t port_no, u8 *temp_reading)
{
    mepa_mtimer_t         timer;
    u8                    timeout = 255; // Used to make sure that we don't run forever in while loop.
    u16                   reg = 0;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Change to GPIO page

        // Workaround because background temperature monitoring doesn't work
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_CONF, 0x0, 0x0040));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_CONF, 0x0040, 0x0040));

        // Read current register value (Temperature Registers 26G,27G and 28G)
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_VAL, &reg));
        *temp_reading = reg & 0xFF; // See data sheet for Registers 26G,27G and 28G

        // Revision A special
        if ((ps->family == VTSS_PHY_FAMILY_ATOM ||
             ps->family == VTSS_PHY_FAMILY_LUTON26) &&
            (ps->type.revision == VTSS_PHY_ATOM_REV_A)) {
            // From Jim B - You need to suspend the 8051 patch prior to triggering the TMON.
            //  I put code in the patch to automatically trigger a temperature reading at the end of the 5ms polling loop,
            // but here is no guarantee that you're not reading in the middle of the patch where we are using the aux-ADC to read out VGA power-up status.
            VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, TRUE));


            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Change to GPIO page

            // Workaround because background temperature monitoring doesn't work
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_CONF, 0x0, 0x0040));
            VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_CONF, 0x0040, 0x0040));

            // Due to a bug in Atom12 rev A (which is going to fixed in next chip revision) we sometimes get wrong
            // temperature reading. This is a work around that makes sure that these wrong temperatures doesn't make dramatics
            // changes.
            while (*temp_reading != ps->last_temp_reading && timeout != 0) {


                // Read current register value (Temperature Registers 26G,27G and 28G)
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_VAL, &reg));
                *temp_reading = reg & 0xFF; // See data sheet for Registers 26G,27G and 28G

                if (*temp_reading == 0xFF || *temp_reading == 0x00) {
                    // Do nothing
                } else if (*temp_reading > ps->last_temp_reading) {
                    ps->last_temp_reading += 1;
                } else {
                    ps->last_temp_reading -= 1;
                }
                timeout--;

                VTSS_N("temp_reading = %d, last_temp_reading = %d",
                       *temp_reading, ps->last_temp_reading);
            }

            VTSS_RC(vtss_atom_patch_suspend(vtss_state, port_no, FALSE)); // Resume patch
        }
        break;

    case VTSS_PHY_FAMILY_NANO:
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Change to GPIO page
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_VAL, &reg));

        // Workaround because background temperature monitoring doesn't work
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_CONF, 0x0, 0x0040));
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_CONF, 0x0040, 0x0040));

        MEPA_MTIMER_START(&timer, 200); /* Wait up to 200 msecs */
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Change to GPIO page
        // Wait for Done, Use Reg28 Bit 8
        while (1) {
            if (PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_VAL, &reg) == VTSS_RC_OK && (reg & 0x0100) == 0) {
                break;
            }

            MEPA_MSLEEP(2); // 2msec sleep
            if (MEPA_MTIMER_TIMEOUT(&timer)) {
                VTSS_E("port_no %u, reset timeout, reg = 0x%X", port_no, reg);
                return VTSS_RC_ERROR;
            }
        }
        MEPA_MTIMER_CANCEL(&timer);

        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_VAL, &reg));
        *temp_reading = reg & 0xFF; // adc_val - Only bottom 8
        break;

    default:
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no)); // Back to standard page.
    return VTSS_RC_OK;
}


// Public API Function for getting chip temperature
/* Note: Function to Initialize chip temperature sensor must be called at least once prior
 * \brief Function for getting Chip Temperature
 * \param vtss_state                   [IN]    Port Structure
 * \param port_no                      [IN]    The PHY Port No.
 * \param temp                         [OUT]   The chip temperature (from -46 to 135 degC)
 * \Return: VTSS_RC_OK if we got the temperature - else error code
 */
vtss_rc vtss_phy_chip_temp_get_private (vtss_state_t   *vtss_state,
                                        const vtss_port_no_t  port_no,
                                        i16            *const temp)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc                rc = VTSS_RC_OK;
    u8                     temp_reading = 0;
    u8                     tmon_adj_lo  = 0;
    u8                     tmon_adj_hi  = 0;
    u16                    reg = 0;
    i16                    temperature;

    /* Check to see if operation supported on this PHY */
    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
        // Read the temperature.
        VTSS_RC(vtss_phy_read_temp_reg(vtss_state, port_no, &temp_reading));

        //135.3degC - 0.71degC*ADCOUT
        temperature = (13530 - 71 * temp_reading) / 100;
        *temp = temperature; // Temperature bits - See PHY Data sheet section 4.6.18
        VTSS_N("Temperature = %d, temp_reading = 0x%X", *temp, temp_reading);
        break;

    case VTSS_PHY_FAMILY_NANO:
        // Read the temperature.
        VTSS_RC(vtss_phy_read_temp_reg(vtss_state, port_no, &temp_reading));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

        // reg_value=1;  mask=0x0040;   26G.6=1
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x03, 0x000f));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_11, &reg)) // Read Lower TMON Bits (55:48)
        tmon_adj_lo = reg & 0xff; // Mask off to only get Lower TMON Bits (55:48)
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, &reg)) // Read Upper TMON Bits (63:56)
        reg = reg >> 8; // Shift over to get 1 byte
        tmon_adj_hi = reg & 0xff; // Mask off to only get Upper TMON Bits (63:56)

        //135.3degC - 0.714degC*ADCOUT
        temperature = vtss_phy_tmon_adjust_private ( temp_reading, tmon_adj_lo, tmon_adj_hi);
        *temp = temperature; // Temperature bits - See PHY Data sheet section 4.6.18
        VTSS_N("Temperature = %d, temp_reading = 0x%X, tmon_hi: 0x%X, tmon_lo: 0x%X ",
               *temp, temp_reading, tmon_adj_lo, tmon_adj_hi);
        break;
    default:
        VTSS_E("Temperature reading not supported for family: %s, port_no:%d", vtss_phy_family2txt(ps->family), port_no);
        rc = VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return rc;
}


// Function for Initializing Chip Temperature sensor
/* Note: This Function to Initialize chip temperature sensor must be called at least once prior to reading Temp
 * \brief Function for Initializing Chip Temperature Sensor
 * \param vtss_state                   [IN]    Port Structure
 * \param port_no                      [IN]    The PHY Port No.
 * \Return: VTSS_RC_OK if we got the temperature - else error code
 */
vtss_rc vtss_phy_chip_temp_init_private(vtss_state_t *vtss_state, const vtss_port_no_t  port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc rc = VTSS_RC_OK;

    VTSS_D("Init chip for port:%u", port_no);

    /* Check to see if operation supported on this PHY */
    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_LUTON26:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO:
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        // mask=0xf000;   28G.15:12=0
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_VAL, 0x0, 0xf000));
        // Read current register value (Temperature Registers 26G,27G and 28G)

        // Read current register value (Temperature Registers 26G,27G and 28G)
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_CONF, 0x0080, 0x0080)); // Deassert TMON0, Reset and enable background monitoring
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEMP_CONF, 0x00C0, 0x00C0)); // Disable TMON1
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        break;
    default:
        VTSS_E("Temperature reading not supported for family: %s, port_no:%d", vtss_phy_family2txt(ps->family), port_no);
        rc = VTSS_RC_ERROR;
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return rc;
}


/* - Debug functions  ----------------------------------- */
/* Enable/disable a loopback  */
static vtss_rc vtss_phy_loopback_set_private(vtss_state_t *vtss_state,
                                             const vtss_port_no_t       port_no)

{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *conf = &ps->reset;
    vtss_rc rc = VTSS_RC_OK;
    u16  mode = 0;
    u16  reg_val = 0;
    u16  reg_mask = 0;
    u8   phy_port_addr;
    u8   tmp_phy_port_addr;
    BOOL fiber = FALSE;
        // Get the PHY Physical Port
        phy_port_addr = vtss_phy_chip_port(vtss_state, port_no);

        // Workaround for viper-B far-end loopback functionality, bug#24139
        // Clear bit 22E3.13 before enabling far-end loopback for viper B.
        if((ps->loopback.far_end_enable == TRUE) && (ps->type.revision == VTSS_PHY_VIPER_REV_B)){
            VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, 0, VTSS_F_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_TX_PREAMBLE_FIX));
        }
        // FAR-End Loopback
        // Enable Far End Loopback, Set Reg23.3=1
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL,
                                        (vtss_state->phy_state[port_no].loopback.far_end_enable ? VTSS_F_PHY_EXTENDED_PHY_CONTROL_FAR_END_LOOPBACK_MODE : 0),
                                         VTSS_F_PHY_EXTENDED_PHY_CONTROL_FAR_END_LOOPBACK_MODE)); // Far end Loopback
        // Reset bit 22E3.13, if far-end loopback is disabled for viper B.
        if((ps->loopback.far_end_enable == FALSE) && (ps->type.revision == VTSS_PHY_VIPER_REV_B)){
            VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, VTSS_F_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_TX_PREAMBLE_FIX,
                                            VTSS_F_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_TX_PREAMBLE_FIX));
        }
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        // NEAR-End Loopback
        // Enable Near End Loopback, Set Reg0.14=1
        // Need to check for Media Interface type, For Fiber 1000BX, need to turn off ANEG
        if ((conf->media_if == VTSS_PHY_MEDIA_IF_FI_1000BX) || (conf->media_if == VTSS_PHY_MEDIA_IF_AMS_FI_1000BX)) {
            // Determine if it is a fiber or CU port
            VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_3, &reg_val));
            fiber = (((reg_val >> 6) & 0x3) == 2 ? TRUE : FALSE);

            /* If the ena_forced_1000_mode_prev is ever set, we do not want to clear it without resetting 17E2.5 */
            if (!ps->ena_forced_1000_mode_prev) {
                ps->ena_forced_1000_mode_prev = ps->ena_forced_1000_mode_curr;
            }
            VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EEE_CONTROL, &reg_val));
            ps->ena_forced_1000_mode_curr = ((reg_val & VTSS_F_PHY_EEE_CONTROL_ENABLE_1000BASE_T_FORCE_MODE) ==
                                             VTSS_F_PHY_EEE_CONTROL_ENABLE_1000BASE_T_FORCE_MODE) ? 1 : 0;

            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

            // For Near-End Loopback to work in 1000BX mode, Must put into FORCED mode, ie. clear ANEG
            if (vtss_state->phy_state[port_no].loopback.near_end_enable) {
                reg_val = vtss_state->phy_state[port_no].loopback.near_end_enable ? VTSS_F_PHY_MODE_CONTROL_LOOP : 0;
                reg_mask = VTSS_F_PHY_MODE_CONTROL_LOOP;
                // Clear ANEG and Turn On Near end Loopback
                if (fiber) {
                    reg_mask |= VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA;
                }
                if (ps->ena_forced_1000_mode_curr) {
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EEE_CONTROL, 0x0,
                                                    VTSS_F_PHY_EEE_CONTROL_ENABLE_1000BASE_T_FORCE_MODE)); // Clear 17E2.5 if Setting Near-End loopback
                }

            } else {
                reg_val = vtss_state->phy_state[port_no].loopback.near_end_enable ? VTSS_F_PHY_MODE_CONTROL_LOOP : 0;
                reg_mask = VTSS_F_PHY_MODE_CONTROL_LOOP;
                // Near-End Loopback OFF, Chk to see if we Need to turn ANEG back ON
                if (ps->setup.mode == VTSS_PHY_MODE_ANEG) {
                    reg_val |= VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA;
                    reg_mask |= VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA;
                }
                if (ps->ena_forced_1000_mode_prev) {
                    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EEE_CONTROL,
                                                    VTSS_F_PHY_EEE_CONTROL_ENABLE_1000BASE_T_FORCE_MODE,
                                                    VTSS_F_PHY_EEE_CONTROL_ENABLE_1000BASE_T_FORCE_MODE)); // If Prev Set, Set 17E2.5 if Clearing Near-End loopback
                }
                ps->ena_forced_1000_mode_curr = 0;
                ps->ena_forced_1000_mode_prev = 0;
            }
            // NEAR-End Loopback
            // Enable Near End Loopback, Set Reg0.14=1
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, reg_val, reg_mask)); // Set Near-End loopback

        } else {
            // NEAR-End Loopback - Copper, Non 1000BX Fiber
            // Enable Near End Loopback, Set Reg0.14=1
            VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                                            (vtss_state->phy_state[port_no].loopback.near_end_enable ? VTSS_F_PHY_MODE_CONTROL_LOOP : 0),
                                            VTSS_F_PHY_MODE_CONTROL_LOOP)); // Near end Loopback
        }


        // CONNECTOR Loopback
        // Enable 1000BaseT connector Loopback, Set Reg24.0=1
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2,
                                        (vtss_state->phy_state[port_no].loopback.connector_enable ? VTSS_F_PHY_EXTENDED_PHY_CONTROL_2_CONNECTOR_LOOPBACK_MODE : 0),
                                        VTSS_F_PHY_EXTENDED_PHY_CONTROL_2_CONNECTOR_LOOPBACK_MODE)); // Connector Loopback
        // Disable Pair Swap Correction, Set Reg18.5=1
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL,
                                        (vtss_state->phy_state[port_no].loopback.connector_enable ? VTSS_F_PHY_BYPASS_CONTROL_DISABLE_PARI_SWAP_CORRECTION : 0),
                                        VTSS_F_PHY_BYPASS_CONTROL_DISABLE_PARI_SWAP_CORRECTION)); // Connector Loopback

        // If a Warmstart in progress, we do not want to change any of the MAC or Media Register settings
        // The MAC/MEDIA SerDes loopbacks will write to registers, Changing register settings to either turn loopback ON or OFF
        // Therefore, we need to return here and skip any register writing for SerDes loopbacks.
        if (vtss_state->sync_calling_private) {
            return rc;
        }

        // Start of MAC SerDes Loopbacks
        // MAC Ports are 0,1,2,3 for SGMII MAC
        // MAC Ports are "c" for QSGMII MAC
        tmp_phy_port_addr = phy_port_addr;
        if (ps->reset.mac_if == VTSS_PORT_INTERFACE_QSGMII) {
            switch (ps->family) {
            case VTSS_PHY_FAMILY_ATOM:
                if (phy_port_addr < 4) {
                    tmp_phy_port_addr = 0xc;
                } else if ((phy_port_addr > 3) && (phy_port_addr < 8)) {
                    tmp_phy_port_addr = 0xd;
                } else if ((phy_port_addr > 7) && (phy_port_addr < 12)) {
                    tmp_phy_port_addr = 0xe;
                }
                break;

            case VTSS_PHY_FAMILY_TESLA:
            case VTSS_PHY_FAMILY_VIPER:
            case VTSS_PHY_FAMILY_ELISE:
                tmp_phy_port_addr = 0xc;
                break;
            default:
                break;
            }
        }

        // MAC SerDes Loopbacks
        if ((vtss_state->phy_state[port_no].loopback.mac_serdes_input_enable) ||
            (vtss_state->phy_state[port_no].loopback.mac_serdes_facility_enable) ||
            (vtss_state->phy_state[port_no].loopback.mac_serdes_equipment_enable)) {

            mode = 0x9002;
            // MAC Ports are 0,1,2,3
            mode |= (tmp_phy_port_addr << 8);
            // MAC SerDes INPUT Loopback
            if (vtss_state->phy_state[port_no].loopback.mac_serdes_input_enable) {
                // Only allow one MAC SerDes loopback to be set at a time
                vtss_state->phy_state[port_no].loopback.mac_serdes_facility_enable = FALSE;
                vtss_state->phy_state[port_no].loopback.mac_serdes_equipment_enable = FALSE;
                mode |= (VTSS_SERDES_LB_INPUT << 4);
                rc = vtss_phy_serdes_sgmii_loopback_private (vtss_state, port_no, mode);
                if (rc == VTSS_RC_OK) {
                    vtss_state->phy_state[port_no].prev_mac_serdes_lpback = VTSS_SERDES_LB_INPUT;
                }
            }
            // MAC SerDes FACILITY Loopback
            if (vtss_state->phy_state[port_no].loopback.mac_serdes_facility_enable) {
                // Only allow one MAC SerDes loopback to be set at a time
                vtss_state->phy_state[port_no].loopback.mac_serdes_input_enable = FALSE;
                vtss_state->phy_state[port_no].loopback.mac_serdes_equipment_enable = FALSE;
                mode |= (VTSS_SERDES_LB_FACILITY << 4);
                rc = vtss_phy_serdes_sgmii_loopback_private (vtss_state, port_no, mode);
                if (rc == VTSS_RC_OK) {
                    vtss_state->phy_state[port_no].prev_mac_serdes_lpback = VTSS_SERDES_LB_FACILITY;
                }
            }
            // MAC SerDes EQUIPMENT Loopback
            if (vtss_state->phy_state[port_no].loopback.mac_serdes_equipment_enable) {
                // Only allow one MAC SerDes loopback to be set at a time
                vtss_state->phy_state[port_no].loopback.mac_serdes_facility_enable = FALSE;
                vtss_state->phy_state[port_no].loopback.mac_serdes_input_enable = FALSE;
                mode |= (VTSS_SERDES_LB_EQUIPMENT << 4);
                rc = vtss_phy_serdes_sgmii_loopback_private (vtss_state, port_no, mode);
                if (rc == VTSS_RC_OK) {
                    vtss_state->phy_state[port_no].prev_mac_serdes_lpback = VTSS_SERDES_LB_EQUIPMENT;
                }
            }
        } else {
            if (vtss_state->phy_state[port_no].prev_mac_serdes_lpback == VTSS_SERDES_LB_NONE) {
                // If it is NONE, Nothing to do
            } else {
                mode = 0x9002;
                mode |= (tmp_phy_port_addr << 8);
                mode |= (VTSS_SERDES_LB_NONE << 4);
                rc = vtss_phy_serdes_sgmii_loopback_private (vtss_state, port_no, mode);
                if (rc == VTSS_RC_OK) {
                    vtss_state->phy_state[port_no].prev_mac_serdes_lpback = VTSS_SERDES_LB_NONE;
                }
            }
        }

        // Start of MEDIA SerDes Loopbacks
        tmp_phy_port_addr = phy_port_addr;
        if (ps->family == VTSS_PHY_FAMILY_ATOM) {
            if (phy_port_addr > 7) {
                // Fibre Ports are by bit position, ie: Fibre8=1, Fibre9=2, Fibre10=4, Fibre11=8
                tmp_phy_port_addr = (1 << (phy_port_addr - 8)); /* Port_no's are 1, 2, 4, 8 */
            } else {
                return VTSS_RC_OK;
            }
        } else {
            // Fibre Ports are by bit position, ie: Fibre0=1, Fibre1=2, Fibre2=4, Fibre3=8
            tmp_phy_port_addr = (1 << phy_port_addr); /* Port_no's are 1, 2, 4, 8 */
        }

        // MEDIA SerDes Loopbacks
        if ((vtss_state->phy_state[port_no].loopback.media_serdes_input_enable) ||
            (vtss_state->phy_state[port_no].loopback.media_serdes_facility_enable) ||
            (vtss_state->phy_state[port_no].loopback.media_serdes_equipment_enable)) {
            mode = 0x8002;
            mode |= (tmp_phy_port_addr << 8);

            // MEDIA SerDes INPUT Loopback
            if (vtss_state->phy_state[port_no].loopback.media_serdes_input_enable) {
                // Only allow one MEDIA SerDes loopback to be set at a time
                vtss_state->phy_state[port_no].loopback.media_serdes_facility_enable = FALSE;
                vtss_state->phy_state[port_no].loopback.media_serdes_equipment_enable = FALSE;
                mode |= (VTSS_SERDES_LB_INPUT << 4);
                rc = vtss_phy_serdes_fmedia_loopback_private (vtss_state, port_no, mode);
                if (rc == VTSS_RC_OK) {
                    vtss_state->phy_state[port_no].prev_media_serdes_lpback = VTSS_SERDES_LB_INPUT;
                }
            }
            // MEDIA SerDes FACILITY Loopback
            if (vtss_state->phy_state[port_no].loopback.media_serdes_facility_enable) {
                // Only allow one MEDIA SerDes loopback to be set at a time
                vtss_state->phy_state[port_no].loopback.media_serdes_input_enable = FALSE;
                vtss_state->phy_state[port_no].loopback.media_serdes_equipment_enable = FALSE;
                mode |= (VTSS_SERDES_LB_FACILITY << 4);
                rc = vtss_phy_serdes_fmedia_loopback_private (vtss_state, port_no, mode);
                if (rc == VTSS_RC_OK) {
                    vtss_state->phy_state[port_no].prev_media_serdes_lpback = VTSS_SERDES_LB_FACILITY;
                }
            }
            // MEDIA SerDes EQUIPMENT Loopback
            if (vtss_state->phy_state[port_no].loopback.media_serdes_equipment_enable) {
                // Only allow one MEDIA SerDes loopback to be set at a time
                vtss_state->phy_state[port_no].loopback.media_serdes_input_enable = FALSE;
                vtss_state->phy_state[port_no].loopback.media_serdes_facility_enable = FALSE;
                mode |= (VTSS_SERDES_LB_EQUIPMENT << 4);
                rc = vtss_phy_serdes_fmedia_loopback_private (vtss_state, port_no, mode);
                if (rc == VTSS_RC_OK) {
                    vtss_state->phy_state[port_no].prev_media_serdes_lpback = VTSS_SERDES_LB_EQUIPMENT;
                }
            }
        } else {
            if (vtss_state->phy_state[port_no].prev_media_serdes_lpback == VTSS_SERDES_LB_NONE) {
                // If it is NONE, Nothing to do
            } else {
                mode = 0x8002;
                mode |= (tmp_phy_port_addr << 8);
                mode |= (VTSS_SERDES_LB_NONE << 4);
                rc = vtss_phy_serdes_fmedia_loopback_private (vtss_state, port_no, mode);
                if (rc == VTSS_RC_OK) {
                    vtss_state->phy_state[port_no].prev_media_serdes_lpback = VTSS_SERDES_LB_NONE;
                }
            }
        }
    return rc;
}


// Getting phy statistic
static vtss_rc vtss_phy_statistic_get_private(vtss_state_t *vtss_state,
                                              const vtss_port_no_t port_no, vtss_phy_statistic_t *statistic)
{
    u16 reg_val;


    // Update CRC good count
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_CU_MEDIA_CRC_GOOD_COUNTER, &reg_val));
    VTSS_D("reg_val:0x%X", reg_val);
    if (reg_val & VTSS_F_PHY_CU_MEDIA_CRC_GOOD_COUNTER_PACKET_SINCE_LAST_READ) {
        statistic->cu_good = reg_val & VTSS_M_PHY_CU_MEDIA_CRC_GOOD_COUNTER_CONTENTS;
    } else {
        statistic->cu_good = 0;
    }


    // Update CRC bad count
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg_val));
    statistic->cu_bad = reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_CU_MEDIA_CRC_ERROR_COUNTER;


    // Update serdes good count
    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER, &reg_val));
    if (reg_val & VTSS_F_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER_ACTIVE) {
        statistic->serdes_tx_good = reg_val & VTSS_M_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER_CNT;
    } else {
        statistic->serdes_tx_good = 0;
    }

    // Update serdes bad count
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, &reg_val));
    statistic->serdes_tx_bad = reg_val & VTSS_M_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_CNT;


    // Update 100/1000BASE-TX media/mac serdes CRC error counter
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER, &reg_val));
    statistic->media_mac_serdes_crc = reg_val & VTSS_M_PHY_MEDIA_MAC_SERDES_RX_CRC_ERR_COUNTER_CNT;

    // Update 100/1000BASE-TX media/mac serdes counter
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER, &reg_val));
    statistic->media_mac_serdes_good = reg_val & VTSS_M_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER_CNT;

    // Update 100/1000BASE-TX receive error counter
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_ERROR_COUNTER_1, &reg_val));
    statistic->rx_err_cnt_base_tx = reg_val & VTSS_M_PHY_ERROR_COUNTER_1_100_1000BASETX_RX_ERR_CNT;



    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
/* Tesla and Atom12 use same API */
static vtss_rc vtss_serdes6g_tesla_rcpll_status_get_private(vtss_state_t         *vtss_state,
                                                            const vtss_port_no_t port_no,
                                                            vtss_rcpll_status_t  *status)
{
    vtss_rc rc = VTSS_RC_OK;
    u8 mcb_bus;
    u8 cfg_buf[MAX_CFG_BUF_SIZE];
    u8 stat_buf[MAX_STAT_BUF_SIZE];
    u16 mac_if, reg_val;
    vtss_phy_type_t phy_id;

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    if (phy_id.base_port_no != port_no) {
        VTSS_I("Tesla/Atom12 6G serdes status only on Base port:%d", phy_id.base_port_no);
        return VTSS_RC_ERR_PHY_6G_RCPLL_ON_BASE_PORT_ONLY;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    mac_if = (reg_val >> 14) & 0x3;
    if (mac_if ==  0) {  // SGMII
        VTSS_I("Tesla/Atom12 1G serdes SGMII configured for port:%d", port_no);
        return VTSS_RC_ERR_PHY_RCPLL_NOT_SUPPORTED;
    } else if (mac_if !=  0x1) {
        VTSS_E("Tesla/Atom12 MAC I/F invalid configuration for port:%d", port_no);
        return VTSS_RC_ERROR;
    }

    mcb_bus = 1; // 1: SerDes 6G
    VTSS_RC(vtss_phy_patch_setttings_get_private(vtss_state, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]));

    status->out_of_range = patch_array_value_decode(10, -1, &stat_buf[0]);  // bit:10
    status->cal_error = patch_array_value_decode(11, -1, &stat_buf[0]);     // bit:11
    status->cal_not_done = patch_array_value_decode(12, -1, &stat_buf[0]);  // bit:12

    if (status->out_of_range) {
        VTSS_I("Tesla Serdes/Atom12 6G RC-PLL Out of range error for port:%d", port_no);
    }
    if (status->cal_error) {
        VTSS_I("Tesla Serdes/Atom12 6G RC-PLL Calibration error for port:%d", port_no);
    }
    if (!status->cal_not_done) {
        VTSS_I("Tesla/Atom12 Serdes 6G RC-PLL Calibration not started/ongoing for port:%d", port_no);
    }

    return (rc);
}

/* Tesla and Atom12 use same API */
static vtss_rc vtss_serdes1g_tesla_rcpll_status_get_private(vtss_state_t         *vtss_state,
                                                            const vtss_port_no_t port_no,
                                                            vtss_rcpll_status_t  *status)
{
    vtss_rc rc = VTSS_RC_OK;
    u8 mcb_bus;
    u8 cfg_buf[MAX_CFG_BUF_SIZE];
    u8 stat_buf[MAX_STAT_BUF_SIZE];
    u16 mac_if, reg_val;

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    mac_if = (reg_val >> 14) & 0x3;
    if (mac_if ==  0x1) {  // QSGMII
        VTSS_I("Tesla/Atom12 6G serdes QSGMII configured for port:%d", port_no);
        return VTSS_RC_ERR_PHY_RCPLL_NOT_SUPPORTED;
    } else if (mac_if !=  0x0) {
        VTSS_E("Tesla/Atom12 MAC I/F invalid configuration for port:%d", port_no);
        return VTSS_RC_ERROR;
    }

    mcb_bus = 0; // 0: SerDes 1G
    VTSS_RC(vtss_phy_patch_setttings_get_private(vtss_state, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]));

    status->out_of_range = patch_array_value_decode(10, -1, &stat_buf[0]);  // bit:10
    status->cal_error = patch_array_value_decode(11, -1, &stat_buf[0]);     // bit:11
    status->cal_not_done = patch_array_value_decode(12, -1, &stat_buf[0]);  // bit:12

    if (status->out_of_range) {
        VTSS_I("Tesla/Atom12 Serdes 1G RC-PLL Out of range error for port:%d", port_no);
    }
    if (status->cal_error) {
        VTSS_I("Tesla/Atom12 Serdes 1G RC-PLL Calibration error for port:%d", port_no);
    }
    if (!status->cal_not_done) {
        VTSS_I("Tesla/Atom12 Serdes 1G RC-PLL Calibration not started/ongoing for port:%d", port_no);
    }

    return (rc);
}

/* Tesla and Atom12 use same API */
static vtss_rc vtss_lcpll_tesla_status_get_private(vtss_state_t         *vtss_state,
                                                   const vtss_port_no_t port_no,
                                                   vtss_lcpll_status_t  *status)
{
    vtss_rc rc = VTSS_RC_OK;
    u8 mcb_bus;
    u8 cfg_buf[MAX_CFG_BUF_SIZE];
    u8 stat_buf[MAX_STAT_BUF_SIZE];

    mcb_bus = 2; // 2: LCPLL/RComp
    VTSS_RC(vtss_phy_patch_setttings_get_private(vtss_state, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]));

    /* PLL5G_STATUS:PLL5G_STATUS0 */
    status->lock_status = patch_array_value_decode(45, -1, &stat_buf[0]);   // bit:45 of stat_buf[]
    status->cal_done = patch_array_value_decode(36, -1, &stat_buf[0]);      // bit:36
    status->cal_error = patch_array_value_decode(35, -1, &stat_buf[0]);     // bit:35

    /* PLL5G_STATUS:PLL5G_STATUS1 */
    status->fsm_lock = patch_array_value_decode(32, -1, &stat_buf[0]);      // bit:32
    status->fsm_stat = patch_array_value_decode(31, 29, &stat_buf[0]);      // bit:31-29
    status->gain_stat = patch_array_value_decode(18, 14, &stat_buf[0]);     // bit:18-14

    if (!status->lock_status) {
        VTSS_I("Tesla/Atom12 LC-PLL not locked for port:%d", port_no);
    }
    if (!status->fsm_lock) {
        VTSS_I("Tesla/Atom12 LC-PLL FSM not locked for port:%d", port_no);
    }
    if (status->fsm_stat != 6) {
        VTSS_I("Tesla/Atom12 LC-PLL FSM Status must be 6 for port:%d", port_no);
    }
    if (status->gain_stat < 2 || status->gain_stat > 10) {
        VTSS_I("Tesla/Atom12 LC-PLL Gain Stat should be between 2 and 10 for port:%d", port_no);
    }

    return (rc);
}

static vtss_rc vtss_serdes6g_rcpll_viper_status_get_private(vtss_state_t         *vtss_state,
                                                            const vtss_port_no_t port_no,
                                                            vtss_rcpll_status_t  *status)
{
    vtss_rc rc = VTSS_RC_OK;
    vtss_phy_type_t phy_id;
    u32 rd_dat;
    u16 mac_if, reg_val;

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    if (phy_id.base_port_no != port_no) {
        VTSS_I("Viper 6G serdes status only on Base port:%d", phy_id.base_port_no);
        return VTSS_RC_ERR_PHY_6G_RCPLL_ON_BASE_PORT_ONLY;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    mac_if = (reg_val >> 14) & 0x3;
    if (mac_if ==  0x0) {  // SGMII, See data sheet register 19G
        VTSS_I("Viper 1G serdes SGMII configured for port:%d", port_no);
        return VTSS_RC_ERR_PHY_RCPLL_NOT_SUPPORTED;
    } else if (mac_if !=  0x1) {
        VTSS_E("Viper MAC I/F invalid configuration for port:%d", port_no);
        return VTSS_RC_ERROR;
    }

    /* Read 6G MCB into CSRs */
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x3f, 0));

    /* SERDES6G_ANA_STATUS:SERDES6G_PLL_STATUS Base Address: 0x2F*/
    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x31, &rd_dat));
    status->out_of_range = (u8)((rd_dat & 0x400) >> 10);          // bit:10
    status->cal_error = (u8)((rd_dat & 0x800) >> 11);             // bit:11
    status->cal_not_done = (u8)((rd_dat & 0x1000) >> 12);         // bit:12

    if (status->out_of_range) {
        VTSS_I("Viper Serdes 6G RC-PLL Out of range error for port:%d", port_no);
    }
    if (status->cal_error) {
        VTSS_I("Viper Serdes 6G RC-PLL Calibration error for port:%d", port_no);
    }
    if (!status->cal_not_done) {
        VTSS_I("Viper Serdes 6G RC-PLL Calibration not started/ongoing for port:%d", port_no);
    }

    return (rc);
}

static vtss_rc vtss_phy_serdes6g_rcpll_status_get_private(vtss_state_t         *vtss_state,
                                                          const vtss_port_no_t port_no,
                                                          vtss_rcpll_status_t  *status)
{
    vtss_rc         rc = VTSS_RC_ERROR;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];


    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
        rc = vtss_serdes6g_rcpll_viper_status_get_private(vtss_state, port_no, status);
        break;

    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:
        rc = vtss_serdes6g_tesla_rcpll_status_get_private(vtss_state, port_no, status);
        break;

    case VTSS_PHY_FAMILY_NANO:
    default:
        VTSS_I("vtss_phy_rcpll_status_get_private: Skipping RCPLL Status_Get, Not Valid for PHY FAMILY Port: %d", port_no);
        rc = VTSS_RC_ERR_PHY_RCPLL_NOT_SUPPORTED;
        break;
    }

    return (rc);
}

static vtss_rc vtss_serdes1g_rcpll_viper_status_get_private(vtss_state_t         *vtss_state,
                                                            const vtss_port_no_t port_no,
                                                            vtss_rcpll_status_t  *status)
{
    vtss_rc rc = VTSS_RC_OK;
    vtss_phy_type_t phy_id;
    u32 rd_dat;
    u16 mac_if, reg_val;

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_MODE_AND_FAST_LINK, &reg_val));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    mac_if = (reg_val >> 14) & 0x3;
    if (mac_if ==  0x1) {  // QSGMII, See data sheet register 19G
        VTSS_I("Viper 6G serdes QSGMII configured for port:%d", port_no);
        return VTSS_RC_ERR_PHY_RCPLL_NOT_SUPPORTED;
    } else if (mac_if !=  0x0) {
        VTSS_E("Viper MAC I/F 1G serdes invalid configuration for port:%d", port_no);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    /* Read 1G MCB into CSRs */
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x20, 0));

    /* SERDES1G_ANA_STATUS Base Address: 0x18*/
    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x18, &rd_dat));
    status->out_of_range = (u8)((rd_dat & 0x400) >> 10);          // bit:10
    status->cal_error = (u8)((rd_dat & 0x800) >> 11);             // bit:11
    status->cal_not_done = (u8)((rd_dat & 0x1000) >> 12);         // bit:12
    if (status->out_of_range) {
        VTSS_I("Viper Serdes 1G RC-PLL Out of range error for port:%d", port_no);
    }
    if (status->cal_error) {
        VTSS_I("Viper Serdes 1G RC-PLL Calibration error for port:%d", port_no);
    }
    if (!status->cal_not_done) {
        VTSS_I("Viper Serdes 1G RC-PLL Calibration not started/ongoing for port:%d", port_no);
    }

    return (rc);
}

static vtss_rc vtss_phy_serdes1g_rcpll_status_get_private(vtss_state_t         *vtss_state,
                                                          const vtss_port_no_t port_no,
                                                          vtss_rcpll_status_t  *status)
{
    vtss_rc         rc = VTSS_RC_ERROR;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];


    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
        rc = vtss_serdes1g_rcpll_viper_status_get_private(vtss_state, port_no, status);
        break;

    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:
        rc = vtss_serdes1g_tesla_rcpll_status_get_private(vtss_state, port_no, status);
        break;

    case VTSS_PHY_FAMILY_NANO:
    default:
        VTSS_I("vtss_phy_rcpll_status_get_private: Skipping LCPLL Status_Get, Not Valid for PHY FAMILY Port: %d", port_no);
        rc = VTSS_RC_ERR_PHY_RCPLL_NOT_SUPPORTED;
        break;
    }

    return (rc);
}

static vtss_rc vtss_lcpll_viper_status_get_private(vtss_state_t         *vtss_state,
                                                   const vtss_port_no_t port_no,
                                                   vtss_lcpll_status_t  *status)
{
    vtss_rc rc = VTSS_RC_OK;
    vtss_phy_type_t phy_id;
    u32 status0;
    u32 status1;

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    /* Read LCPLL MCB into CSRs */
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, phy_id.base_port_no, 0x11, 0));

    /* Read PLL5G_STATUS:PLL5G_STATUS0 - Reg:0xC */
    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x0C, &status0));
    /* Read PLL5G_STATUS:PLL5G_STATUS1 - Reg:0xD */
    VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, phy_id.base_port_no, 7, 0x0D, &status1));

    status->lock_status = (u8)status0 & 0x1;                // Status0 - bit:0
    status->cal_done = (u8)((status0 & 0x200) >> 9);        // Status0 - bit:9
    status->cal_error = (u8)((status0 & 0x400) >> 10);      // Status0 - bit:10
    status->fsm_lock = (u8) status1 & 0x1;                  // Status1 - bit 0
    status->fsm_stat = (u8) ((status1 & 0xe) >> 1);         // Status1 - bits 3:1
    status->gain_stat = (u8) ((status1 & 0x7c000) >> 14);   // Status1 - bits 18:14

    if (!status->lock_status)
        VTSS_I("Viper LC-PLL not locked for port:%d", port_no)
        if (!status->fsm_lock) {
            VTSS_I("Viper LC-PLL FSM not locked for port:%d", port_no);
        }
    if (status->fsm_stat != 6) {
        VTSS_I("Viper LC-PLL FSM Status must be 6 for port:%d", port_no);
    }
    if (status->gain_stat < 2 || status->gain_stat > 10) {
        VTSS_I("Viper LC-PLL Gain Stat should be between 2 and 10 for port:%d", port_no);
    }

    return (rc);
}


static vtss_rc vtss_phy_lcpll_status_get_private(vtss_state_t         *vtss_state,
                                                 const vtss_port_no_t port_no,
                                                 vtss_lcpll_status_t  *status)
{
    vtss_rc         rc = VTSS_RC_ERROR;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    // Get the chip physical port number, if it is 0, then it is the base port.

    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
        rc = vtss_lcpll_viper_status_get_private(vtss_state, port_no, status);
        break;

    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:
        rc = vtss_lcpll_tesla_status_get_private(vtss_state, port_no, status);
        break;

    case VTSS_PHY_FAMILY_NANO:
    default:
        VTSS_I("vtss_phy_lcpll_status_get_private: Skipping LCPLL Status_Get, Not Valid for PHY FAMILY Port: %d", port_no);
        rc = VTSS_RC_ERR_PHY_LCPLL_NOT_SUPPORTED;
        break;
    }

    return (rc);
}

vtss_rc vtss_phy_sd6g_mac_serdes_conf(const vtss_inst_t    inst,
                                      const vtss_port_no_t port_no)
{
    vtss_rc      rc = VTSS_RC_OK;
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    vtss_state_t *vtss_state;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_sd6g_patch_private(vtss_state, port_no);
        if (rc != VTSS_RC_OK) {
            VTSS_E("port_no %u, SD6G_PATCH Failure, rc = %d", port_no, rc);
        }
    }
    VTSS_EXIT();
#endif
    return rc;
}

#ifdef _ENABLE_PHY_SERDES_DEBUG_
/*- VIPER & ELISE FAMILY ONLY -- VSC8584/82 & VSC8514 */
vtss_rc vtss_phy_sd6g_csr_reg_rd_dbg(const vtss_inst_t         inst,
                                     const vtss_port_no_t      port_no,
                                     const u32                 csr_reg,
                                     u32                      *csr_reg_val)
{
    vtss_rc      rc = VTSS_RC_OK;
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    vtss_state_t *vtss_state;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_sd6g_mac_serdes_set port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* Valid Register Range is: csr_reg = 0x20; csr_reg <= 0x34 */
        if (csr_reg >= 0x12 && csr_reg <= 0x34) {
            vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, csr_reg, csr_reg_val);
            VTSS_D("port_no %u, sd6G SerDes Reg: 0x%x;  RegValue: 0x%08x  ", port_no, csr_reg, *csr_reg_val);
        } else {
            *csr_reg_val = 0;
            VTSS_D("port_no %u, sd6G SerDes Reg: 0x%x: OUT-OF-RANGE:  RegValue: 0x%08x  ", port_no, csr_reg, *csr_reg_val);
        }
    }
    VTSS_EXIT();
#endif
    return rc;
}
#endif

#endif



/* ================================================================= *
 *  Public functions
 * ================================================================= */

/* - Reset --------------------------------------------------------- */

vtss_rc vtss_phy_pre_reset(const vtss_inst_t           inst,
                           const vtss_port_no_t        port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_pre_reset port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);

        /* -- Step 2: Reset the PHY LCPLL if it is applicable -- Base Port only! */
        if (rc == VTSS_RC_OK) {
            rc = VTSS_RC_COLD(vtss_phy_reset_lcpll_private(vtss_state, port_no));
        }

        if (rc == VTSS_RC_OK) {
            rc = VTSS_RC_COLD(vtss_phy_pre_reset_private(vtss_state, port_no));
        }
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_phy_firmware_update(const vtss_inst_t    inst,
                                 const vtss_port_no_t port_no,
                                 u8 *const fw,
                                 u32 *const len)
{
    vtss_rc      rc = VTSS_RC_ERROR;
    return rc;
}

vtss_rc vtss_phy_post_reset(const vtss_inst_t           inst,
                            const vtss_port_no_t        port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_post_reset port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);

        if (rc == VTSS_RC_OK) {
            rc = VTSS_RC_COLD(vtss_phy_post_reset_private(vtss_state, port_no));
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_pre_system_reset(const vtss_inst_t           inst,
                                  const vtss_port_no_t        port_no)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_phy_reset(const vtss_inst_t           inst,
                       const vtss_port_no_t        port_no,
                       const vtss_phy_reset_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("vtss_phy_reset, Port:%d", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->phy_state[port_no].reset = *conf;

        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);
        if (rc == VTSS_RC_OK) {
            rc = vtss_phy_detect_base_ports_private(vtss_state);
        }

        if (rc == VTSS_RC_OK) {
            if (vtss_state->phy_state[port_no].type.part_number == VTSS_PHY_TYPE_7435) {
		/* Keep this function to debug, if any issue find */
#if DEBUG_TOKEN_RING_REGDUMP_EN
                VTSS_I("Dumping TR_REG Before vtss_phy_reset Update TR_Regs port_no:%d", port_no);
                vtss_phy_debug_tr_regdump_print(vtss_state, printf, port_no, TRUE);
#endif
                VTSS_I("Update TR_Regs for NANO_PHY_7435 port_no:%d", port_no);
                rc = vtss_phy_pre_init_seq_nano_7435(vtss_state, port_no);
		/* Keep this function to debug, if any issue find */
#if DEBUG_TOKEN_RING_REGDUMP_EN
                if (rc == VTSS_RC_OK) {
                    VTSS_I("Dumping TR_REG After vtss_phy_reset Update TR_Regs port_no:%d", port_no);
                    rc = vtss_phy_debug_tr_regdump_print(vtss_state, printf, port_no, TRUE);
                }
#endif
            }
        }

        if (rc == VTSS_RC_OK) {
            rc = VTSS_RC_COLD(vtss_phy_reset_private(vtss_state, port_no));
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_reset_get(const vtss_inst_t           inst,
                           const vtss_port_no_t        port_no,
                           vtss_phy_reset_conf_t *conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->phy_state[port_no].reset;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_detect_base_ports(const vtss_inst_t inst)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc =  vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (rc == VTSS_RC_OK) {
            rc = (vtss_phy_detect_base_ports_private(vtss_state));
        }
    }
    VTSS_EXIT();
    return rc;
}


// Returns if a port is EEE capable
vtss_rc vtss_phy_port_eee_capable(const vtss_inst_t           inst,
                                  const vtss_port_no_t        port_no,
                                  BOOL                        *eee_capable)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *eee_capable = vtss_phy_can(vtss_state, port_no, VTSS_CAP_EEE);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_EEE)
// Enable disable EEE (energy Efficient Ethernet)
vtss_rc vtss_phy_eee_ena(const vtss_inst_t           inst,
                         const vtss_port_no_t        port_no,
                         const BOOL                  enable)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (enable) {
            vtss_state->phy_state[port_no].eee_conf.eee_mode = EEE_ENABLE;
        } else {
            vtss_state->phy_state[port_no].eee_conf.eee_mode = EEE_DISABLE;
        }
        rc = VTSS_RC_COLD(vtss_phy_eee_ena_private(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_phy_eee_conf_get(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              vtss_phy_eee_conf_t         *conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->phy_state[port_no].eee_conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_eee_conf_set(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              const vtss_phy_eee_conf_t   conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->phy_state[port_no].eee_conf = conf;
        rc = VTSS_RC_COLD(vtss_phy_eee_ena_private(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}

// EEE link partners advertisements
vtss_rc vtss_phy_eee_link_partner_advertisements_get(const vtss_inst_t           inst,
                                                     const vtss_port_no_t        port_no,
                                                     u8  *advertisements)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_RC_COLD(vtss_phy_eee_link_partner_advertisements_get_private(vtss_state, port_no, advertisements));
    }
    VTSS_EXIT();
    return rc;
}

// EEE current phy power save mode state
vtss_rc vtss_phy_eee_power_save_state_get(const vtss_inst_t           inst,
                                          const vtss_port_no_t        port_no,
                                          BOOL  *rx_in_power_save_state,
                                          BOOL  *tx_in_power_save_state)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_RC_COLD(vtss_phy_eee_power_save_state_get_private(vtss_state, port_no, rx_in_power_save_state, tx_in_power_save_state));
    }
    VTSS_EXIT();
    return rc;
}

#endif // end VTSS_FEATURE_EEE
/* - Main configuration and status --------------------------------- */

// See header file
vtss_rc vtss_phy_id_get(const vtss_inst_t   inst,
                        const vtss_port_no_t  port_no,
                        vtss_phy_type_t *phy_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_id_get_private(vtss_state, port_no, phy_id);
    }

    VTSS_EXIT();
    return rc;
}


// See vtss_phy_api.h
vtss_rc vtss_phy_chip_temp_init(const vtss_inst_t     inst,
                                const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_chip_temp_init_private(vtss_state, port_no);
    }

    VTSS_EXIT();
    return rc;
}



// See vtss_phy_api.h
vtss_rc vtss_phy_chip_temp_get(const vtss_inst_t     inst,
                               const vtss_port_no_t port_no,
                               i16                    *const temp)
{
    vtss_state_t *vtss_state;
    i16 chip_temp;
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_chip_temp_get_private(vtss_state, port_no, &chip_temp);
        *temp = chip_temp;
    }

    VTSS_EXIT();
    return rc;
}



// See vtss_phy_api.h
vtss_rc vtss_phy_conf_get(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          vtss_phy_conf_t      *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->phy_state[port_no].setup;
    }
    VTSS_EXIT();
    return rc;
}

// See vtss_phy_api.h
vtss_rc vtss_phy_conf_set(const vtss_inst_t     inst,
                          const vtss_port_no_t  port_no,
                          const vtss_phy_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_MACSEC)
        if (vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC)) {
            if (vtss_state->macsec_conf[port_no].glb.init.enable) {
                VTSS_I("Stopping MACsec and MAC traffic port_no %u\n", port_no);
                rc = vtss_macsec_drop_all_traffic_priv(vtss_state, port_no);
                rc = phy_10g_mac_conf(vtss_state, port_no, 0, 1);
            }
        }
#endif

        vtss_state->phy_state[port_no].setup = *conf;

#if defined(VTSS_OPT_PHY_TIMESTAMP)
        rc = VTSS_RC_COLD(vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, FALSE));
        if (rc == VTSS_RC_OK) {
#endif

            rc = VTSS_RC_COLD(vtss_phy_conf_set_private(vtss_state, port_no));

#if defined(VTSS_OPT_PHY_TIMESTAMP)
            rc = VTSS_RC_COLD(vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, FALSE));
        }
#endif
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_status_get(const vtss_inst_t    inst,
                            const vtss_port_no_t port_no,
                            vtss_port_status_t   *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_status_get_private(vtss_state, port_no, status);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_status_inst_poll(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  vtss_port_status_t   *const status)
{
    vtss_state_t *vtss_state;
    vtss_phy_port_state_t *ps;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        ps = &vtss_state->phy_state[port_no];
        *status = ps->status;
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_phy_ring_resiliency_conf_set(const vtss_inst_t    inst,
                                          const vtss_port_no_t port_no,
                                          const vtss_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->phy_state[port_no].rslnt_conf = *ring_rslnt_conf;
        rc = VTSS_RC_COLD(vtss_phy_ring_resiliency_conf_set_private(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}
vtss_rc vtss_phy_ring_resiliency_conf_get(const vtss_inst_t    inst,
                                          const vtss_port_no_t port_no,
                                          vtss_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_ring_resiliency_conf_get_private(vtss_state, port_no, ring_rslnt_conf);
        *ring_rslnt_conf = vtss_state->phy_state[port_no].rslnt_conf;
    }
    VTSS_EXIT();
    return rc;
}
vtss_rc vtss_phy_cl37_lp_abil_get_private(vtss_state_t *vtss_state,
                                          const vtss_port_no_t port_no,
                                          vtss_port_status_t   *const status)
{
    u16                   reg;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_phy_reset_conf_t *reset_conf = &ps->reset;

    //VTSS_D("vtss_phy_cl37_lp_abil_get_private, port_no: %u", port_no);

    if (is_media_if_passthru(reset_conf->media_if)) {
        VTSS_N("Reading link partner's ability in PASSTHRU MODE\n");
        switch (ps->setup.mode) {
        case VTSS_PHY_MODE_ANEG:
            /* Vitesse PHY, use register 0 to determine if ANEG is Enabled */
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, &reg));
            if (reg & VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA) {
                /* Vitesse PHY, use register 28 to determine if ANEG has completed */
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS, &reg));
                if (reg & VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ANEG_COMPLETE) {
                    VTSS_N("PASSTHRU MODE: ANEG Enabled and ANEG Complete on port: %d", port_no);
                } else {
                    VTSS_N("PASSTHRU MODE: ANEG NOT Complete - Cl37 Data not valid on port: %d", port_no);
                    return VTSS_RC_OK;
                }
            } else {
                VTSS_N("PASSTHRU MODE: ANEG NOT Enabled - Cl37 Data not Valid on port_no: %d", port_no);
                return VTSS_RC_OK;
            }

            /* Read link status from register 26E3 - This is Link Partner Status! */
            /* By "ANDING" these values, this is what is happening:  */
            /* 1. the Link Status passed in from Reg01 must be OK - Indicates MAC & MEDIA Status  */
            /* 2. the MEDIA Link Status from the Link Partner (Remote PHY) must also be OK  */
            VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no,
                                VTSS_PHY_MEDIA_SERDES_CLAUSE_37_LP_ABILITY, &reg));
            if (reg & (1 << 0)) {   /* Make sure we are dealing with SGMII Extensions */
                status->link &= (reg & (1 << 15) ? 1 : 0);
                status->fdx =  (reg & (1 << 12) ? 1 : 0);
                switch ((reg >> 10) & 0x3) {
                case 0:
                    status->speed = VTSS_SPEED_10M;
                    break;
                case 1:
                    status->speed = VTSS_SPEED_100M;
                    break;
                case 2:
                    status->speed = VTSS_SPEED_1G;
                    break;
                case 3:
                    status->speed = VTSS_SPEED_UNDEFINED;
                    break;
                }
                VTSS_N("Autoneg PASSTHRU mode: speed:%d fdx:%d link:%d\n",
                   status->speed, status->fdx, status->link);
            }
            break;

        case VTSS_PHY_MODE_FORCED:
            /* In Forced Mode, Reg24E3 provides the status between the VSC PHY and the SFP */
            /* For CuSPF, which has another PHY in it, it is the Media i/f with the PHY inside the SFP */
            /* Therefore, Really Need ANEG enabled for CuSFP to get Cl37 Media info for link w/LP */
            /* For Fiber SPF, There is no PHY so it is the actual Media i/f coming out of the SFP */
            /* Vitesse PHY, use register 24E3 to determine Media i/f Status */
            /* Reg 24E3 Media PCS Status:  */
            /* Reg 24E3.12 = SerDes Protocol Transfer 10Mb Speed */
            /* Reg 24E3.13 = SerDes Proto Transfer 100M Speed */
            /* Reg 24E3.13:12=00 (both bits clear) SerDes Protocol Transfer 1Gb. */
            VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_STATUS, &reg));
            status->link &= ((reg & VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_MEDIA_LINK_STATUS) ? 1 : 0);

            /* Read link status from register 24E3 - Cl37 Advertisements of what we can do */
            status->fdx =  1;

            /* Reg 24E3 Media PCS Status - 24E3.13:12=00 SerDes Protocol Transfer 1Gb. */
            if ((reg & (VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_10MB_LINK_STATUS |
                        VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_100BASEFX_PROTO_XFER_LINK_STATUS)) == 0) {
                status->speed = VTSS_SPEED_1G;
            } else if (reg & VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_100BASEFX_PROTO_XFER_LINK_STATUS) { /* 24E3.13=SerDes ProtoXfer 100M */
                status->speed = VTSS_SPEED_100M;
            } else if (reg & VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_10MB_LINK_STATUS) { /* 24E3.12=SerDes Protocol Transfer 10Mb */
                status->speed = VTSS_SPEED_10M;
            } else { /* Reg 24E3 Media PCS Status, 24E3.13:12=11 - This should never happen as bits 12/13 are checked above */
                status->speed = VTSS_SPEED_UNDEFINED;
            }

            VTSS_N("Forced PASSTHRU mode: speed:%d fdx:%d link:%d\n",
                   status->speed, status->fdx, status->link);
            break;

        default:
            break;
        }

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    } else {
        VTSS_N("Not PASSTHRU media_if:%d\n", reset_conf->media_if);
    }
    return VTSS_RC_OK;
}


/* - 1G configuration and status ----------------------------------- */

vtss_rc vtss_phy_conf_1g_get(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             vtss_phy_conf_1g_t    *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->phy_state[port_no].conf_1g;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_conf_1g_set(const vtss_inst_t         inst,
                             const vtss_port_no_t      port_no,
                             const vtss_phy_conf_1g_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->phy_state[port_no].conf_1g = *conf;
        rc = VTSS_RC_COLD(vtss_phy_conf_1g_set_private(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_status_1g_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_phy_status_1g_t  *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_status_1g_get_private(vtss_state, port_no, status);
    }
    VTSS_EXIT();
    return rc;
}

/* - Power configuration and status -------------------------------- */

vtss_rc vtss_phy_power_conf_get(const vtss_inst_t      inst,
                                const vtss_port_no_t   port_no,
                                vtss_phy_power_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->phy_state[port_no].conf_power;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_power_conf_set(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_phy_power_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->phy_state[port_no].conf_power = *conf;
        rc = VTSS_RC_COLD(vtss_phy_power_conf_set_private(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_power_status_get(const vtss_inst_t        inst,
                                  const vtss_port_no_t     port_no,
                                  vtss_phy_power_status_t  *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        status->level = vtss_state->phy_state[port_no].power.pwrusage;
    }
    VTSS_EXIT();
    return rc;
}

/* - Clock configuration ---------- -------------------------------- */
vtss_rc vtss_phy_clock_conf_set(const vtss_inst_t           inst,
                                const vtss_port_no_t        port_no,
                                const vtss_phy_recov_clk_t  clock_port,
                                const vtss_phy_clock_conf_t *const conf)
{
    vtss_state_t    *vtss_state;
    vtss_rc         rc;
    vtss_phy_type_t phy_id;


    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (clock_port < VTSS_PHY_RECOV_CLK_NUM) { /* Valid clock port */
            if ((rc = vtss_phy_id_get_private(vtss_state, port_no, &phy_id)) == VTSS_RC_OK) {
                if ((rc = VTSS_PHY_BASE_PORTS_FOUND) == VTSS_RC_OK) { // Make sure that base ports are found
                    vtss_state->phy_state[phy_id.base_port_no].clock_conf[clock_port].conf = *conf;      /* Configuration is always saved in the base port phy_state */
                    vtss_state->phy_state[phy_id.base_port_no].clock_conf[clock_port].source = port_no;  /* Also save the clock source port number */
                    rc = VTSS_RC_COLD(vtss_phy_clock_conf_set_private(vtss_state, port_no, clock_port));
                }
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

/* get function for above set */
vtss_rc vtss_phy_clock_conf_get(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_phy_recov_clk_t   clock_port,
                                vtss_phy_clock_conf_t        *const conf,
                                vtss_port_no_t               *const clock_source)
{
    vtss_state_t    *vtss_state;
    vtss_rc         rc;
    vtss_phy_type_t phy_id;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (clock_port < VTSS_PHY_RECOV_CLK_NUM) { /* Valid clock port */
            if ((rc = vtss_phy_id_get_private(vtss_state, port_no, &phy_id)) == VTSS_RC_OK) {
                if ((rc = VTSS_PHY_BASE_PORTS_FOUND) == VTSS_RC_OK) { // Make sure that base ports are found
                    *conf = vtss_state->phy_state[phy_id.base_port_no].clock_conf[clock_port].conf;      /* Configuration is always saved in the base port phy_state */
                    *clock_source = vtss_state->phy_state[phy_id.base_port_no].clock_conf[clock_port].source;    /* Also return the clock source port number */
                }
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

/* - Warm start synchronization ------------------------------------ */

#define VTSS_SYNC_RC(function) if ((rc = function) != VTSS_RC_OK) {vtss_state->sync_calling_private = FALSE; return rc;}
vtss_rc vtss_phy_sync(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_rc rc;
    vtss_port_no_t i;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    VTSS_I("OK - Warm start : port:%d", port_no);
    // Make sure that this port in fact has a 1G PHY

    if (ps->family == VTSS_PHY_FAMILY_NONE) {
        VTSS_N("port_no %u not connected to 1G PHY", port_no);
        return VTSS_RC_OK;
    }

    VTSS_D("vtss_phy_sync, port_no:%d", port_no);
    vtss_state->sync_calling_private = TRUE;

    // Starting with no registers changed.
    vtss_state->phy_state[port_no].warm_start_reg_changed = FALSE;

    if (vtss_state->phy_state[port_no].type.base_port_no == port_no) {
        VTSS_SYNC_RC(vtss_phy_pre_reset_private(vtss_state, port_no));
        VTSS_SYNC_RC(vtss_phy_post_reset_private(vtss_state, port_no));
    }


    // Call the private function for updating H/W registers
    VTSS_SYNC_RC(vtss_phy_conf_set_private(vtss_state, port_no));
#if defined(VTSS_FEATURE_LED_POW_REDUC)
    if (vtss_state->phy_led_control_warm_start_port_list[port_no]) { // Only warm-start the ports that was initialized
        VTSS_SYNC_RC(vtss_phy_led_intensity_set_private(vtss_state, port_no));
        VTSS_SYNC_RC(vtss_phy_enhanced_led_control_init_private(vtss_state, port_no));
    }
#endif
    VTSS_SYNC_RC(vtss_phy_power_conf_set_private(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_conf_1g_set_private(vtss_state, port_no));

#if defined(VTSS_FEATURE_EEE)
    VTSS_SYNC_RC(vtss_phy_eee_ena_private(vtss_state, port_no));
#endif

    VTSS_SYNC_RC(vtss_phy_reset_private(vtss_state, port_no));
    VTSS_SYNC_RC(vtss_phy_loopback_set_private(vtss_state, port_no));
    VTSS_N("Calling vtss_phy_event_enable_private(%d)", port_no);
    VTSS_SYNC_RC(vtss_phy_event_enable_private(vtss_state, port_no));

    for (i = 0; i < VTSS_PHY_RECOV_CLK_NUM; ++i) {
        VTSS_SYNC_RC(vtss_phy_clock_conf_set_private(vtss_state, port_no, i));
    }

    VTSS_I("OK - Warm start done");
    vtss_state->sync_calling_private = FALSE;

    return VTSS_RC_OK;

    // These functions shall not be called during warm start (The list below is just to show that we have thought about these functiona)
    // vtss_phy_coma_mode_private(port_no, TRUE)
    // vtss_phy_pre_system_reset_private(port_no)
    // vtss_phy_post_reset_private(port_no)
    // vtss_phy_pre_reset_private(port_no)

}

// Function returning VTSS_RC_ERROR if any registers were unexpected needed to be changed during warm start, else return VTSS_RC_OK - Note: In a working system VTSS_RC_ERROR should never be seen.
vtss_rc vtss_phy_warm_start_failed_get(const vtss_inst_t    inst,
                                       const vtss_port_no_t port_no)
{
    vtss_rc rc;
    vtss_state_t *vtss_state;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_warm_start_failed_get_private(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}

/* - LED Control ------------------------------------------------------- */

vtss_rc vtss_phy_led_mode_set(const vtss_inst_t            inst,
                              const vtss_port_no_t         port_no,
                              const vtss_phy_led_mode_select_t led_mode_select)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_N("enter, port_no: %u", port_no);
        vtss_state->led_mode_select = led_mode_select;
        rc = VTSS_RC_COLD(vtss_phy_led_mode_set_private(vtss_state, port_no));
    }

    VTSS_EXIT();
    return rc;
}




#if defined(VTSS_FEATURE_LED_POW_REDUC)


vtss_rc vtss_phy_led_intensity_set(const vtss_inst_t            inst,
                                   const vtss_port_no_t         port_no,
                                   const vtss_phy_led_intensity intensity)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->led_intensity  = intensity;
        rc = VTSS_RC_COLD(vtss_phy_led_intensity_set_private(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_led_intensity_get(const vtss_inst_t            inst,
                                   const vtss_port_no_t         port_no,
                                   vtss_phy_led_intensity       *intensity)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *intensity = vtss_state->led_intensity;
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_phy_enhanced_led_control_init(const vtss_inst_t            inst,
                                           const vtss_port_no_t         port_no,
                                           const vtss_phy_enhanced_led_control_t conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_N("enter, port_no: %u", port_no);
        vtss_state->enhanced_led_control  = conf;
        rc = VTSS_RC_COLD(vtss_phy_enhanced_led_control_init_private(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_enhanced_led_control_init_get(const vtss_inst_t            inst,
                                               const vtss_port_no_t         port_no,
                                               vtss_phy_enhanced_led_control_t *conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->enhanced_led_control;
    }
    VTSS_EXIT();
    return rc;
}

#endif

/* - Coma mode  ---------------------------------------------------- */


vtss_rc vtss_phy_coma_mode_disable(const vtss_inst_t            inst,
                                   const vtss_port_no_t         port_no)

{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_I("enter, port_no: %u", port_no);
        rc = VTSS_RC_COLD(vtss_phy_coma_mode_private(vtss_state, port_no, TRUE));
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_phy_coma_mode_enable(const vtss_inst_t            inst,
                                  const vtss_port_no_t         port_no)

{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_I("enter, port_no: %u", port_no);
        rc = VTSS_RC_COLD(vtss_phy_coma_mode_private(vtss_state, port_no, FALSE));
    }
    VTSS_EXIT();
    return rc;
}


/* - I2C ---------------------------------------------------- */

/* Read PHY i2c register */
vtss_rc vtss_phy_i2c_read(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          const u8             i2c_mux,
                          const u8             i2c_reg_start_addr,
                          const u8             i2c_device_addr,
                          BOOL                 word_access,
                          u8                   cnt,
                          u8                   *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_i2c_rd_private(vtss_state, port_no, i2c_mux, i2c_reg_start_addr, i2c_device_addr, word_access, cnt, value);
    }
    VTSS_EXIT();
    return rc;
}


/* Read PHY i2c register */
vtss_rc vtss_phy_i2c_write(const vtss_inst_t    inst,
                           const vtss_port_no_t port_no,
                           const u8             i2c_mux,
                           const u8             i2c_reg_start_addr,
                           const u8             i2c_device_addr,
                           BOOL                 word_access,
                           u8                   cnt,
                           const u8            *value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_i2c_wr_private(vtss_state, port_no, i2c_mux, i2c_reg_start_addr, i2c_device_addr, word_access, cnt, value);
    }
    VTSS_EXIT();
    return rc;
}


/* I2C Clock frequency select */
vtss_rc vtss_phy_i2c_clock_select(const vtss_inst_t    inst,
                                 const vtss_port_no_t port_no,
                                 const mepa_i2c_clk_select_t  *clk_value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_i2c_clock_sel_private(vtss_state, port_no, clk_value);
    }
    VTSS_EXIT();
    return rc;
}


/* - Read/write ---------------------------------------------------- */


/* Read PHY mmd register */
vtss_rc vtss_phy_mmd_read(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          const u16            devad,
                          const u32            addr,
                          u16                  *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_mmd_rd(vtss_state, port_no, devad, addr, value);
    }
    VTSS_EXIT();
    return rc;
}


/* Write PHY mmd register */
vtss_rc vtss_phy_mmd_write(const vtss_inst_t    inst,
                           const vtss_port_no_t port_no,
                           const u16            devad,
                           const u32            addr,
                           u16                  value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_mmd_wr(vtss_state, port_no, devad, addr, value);
    }
    VTSS_EXIT();
    return rc;
}


/* Get PHY statistic  */
vtss_rc vtss_phy_statistic_get(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               vtss_phy_statistic_t *statistic)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_statistic_get_private(vtss_state, port_no, statistic);
    }
    VTSS_EXIT();
    return rc;
}


/* Read PHY register at a specific page  */
vtss_rc vtss_phy_read_page(const vtss_inst_t    inst,
                           const vtss_port_no_t port_no,
                           const u32            page,
                           const u32            addr,
                           u16                  *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc |= vtss_phy_wr(vtss_state, port_no, 31, page);
        rc |= vtss_phy_rd(vtss_state, port_no, addr, value);
        rc |= vtss_phy_page_std(vtss_state, port_no);
    }
    VTSS_EXIT();
    return rc;
}


/* Read PHY register */vtss_rc vtss_phy_read(const vtss_inst_t    inst,
                                             const vtss_port_no_t port_no,
                                             const u32            addr,
                                             u16                  *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_rd(vtss_state, port_no, addr, value);
    }
    VTSS_EXIT();
    return rc;
}

/* Write PHY register */
vtss_rc vtss_phy_write(const vtss_inst_t    inst,
                       const vtss_port_no_t port_no,
                       const u32            addr,
                       const u16            value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_wr(vtss_state, port_no, addr, value);
    }
    VTSS_EXIT();
    return rc;
}

/* Write PHY register, masked */
vtss_rc vtss_phy_write_masked(const vtss_inst_t    inst,
                              const vtss_port_no_t port_no,
                              const u32            addr,
                              const u16            value,
                              const u16            mask)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_wr_masked(vtss_state, port_no, addr, value, mask);
    }
    VTSS_EXIT();
    return rc;
}



/* Write PHY register, masked (including page setup) */
vtss_rc vtss_phy_write_masked_page(const vtss_inst_t    inst,
                                   const vtss_port_no_t port_no,
                                   const u16            page,
                                   const u16            addr,
                                   const u16            value,
                                   const u16            mask)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        (void) vtss_phy_wr(vtss_state, port_no, 31, page);
        rc = vtss_phy_wr_masked(vtss_state, port_no, addr, value, mask);
        (void) vtss_phy_wr(vtss_state, port_no, 31, 0);
    }
    VTSS_EXIT();
    return rc;
}



/* - VeriPHY ------------------------------------------------------- */
#if VTSS_PHY_OPT_VERIPHY

static vtss_rc vtss_phy_veriphy_get_private(vtss_state_t *vtss_state,
                                            const vtss_port_no_t      port_no,
                                            vtss_phy_veriphy_result_t *const result)
{
    vtss_veriphy_task_t c51_idata *tsk;
    vtss_rc                       rc;
    u32                           i;

    tsk = &vtss_state->phy_state[port_no].veriphy;
    rc = vtss_phy_veriphy(vtss_state, tsk);
    if (rc == VTSS_RC_OK && !(tsk->flags & (1 << 1))) {
        /* Invalid result */
        rc = VTSS_RC_ERROR;
    }

    result->link = (rc == VTSS_RC_OK && (tsk->flags & (1 << 0)) ? 1 : 0);
    for (i = 0; i < 4; i++) {
        result->status[i] = (rc == VTSS_RC_OK ? (tsk->stat[i] & 0x0f) :
                             VTSS_VERIPHY_STATUS_OPEN);
        result->length[i] = (rc == VTSS_RC_OK ? tsk->loc[i] : 0);
    }
    return rc;
}

vtss_rc vtss_phy_veriphy_start(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               const u8              mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_veriphy_task_start(vtss_state, port_no, mode);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_phy_veriphy_get(const vtss_inst_t          inst,
                             const vtss_port_no_t       port_no,
                             vtss_phy_veriphy_result_t  *const result)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_veriphy_get_private(vtss_state, port_no, result);
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_PHY_OPT_VERIPHY */



/* - Events --------------------------------------------------- */
/* - Includes Extended Events --------------------------------- */


vtss_rc vtss_phy_event_enable_set(const vtss_inst_t         inst,
                                  const vtss_port_no_t      port_no,
                                  const vtss_phy_event_t    ev_mask,
                                  const BOOL                enable)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (enable) {
            vtss_state->phy_state[port_no].ev_mask |= ev_mask;
        } else {
            vtss_state->phy_state[port_no].ev_mask &= ~ev_mask;
        }

        VTSS_N("vtss_phy_event_enable_set - updated phy_ev_mask: 0x%X;  ev_mask:0x%X, enable:%d", vtss_state->phy_state[port_no].ev_mask, ev_mask, enable);
        rc = VTSS_RC_COLD(vtss_phy_event_enable_private(vtss_state, port_no));
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_event_enable_get(const vtss_inst_t         inst,
                                  const vtss_port_no_t      port_no,
                                  vtss_phy_event_t          *ev_mask)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *ev_mask = vtss_state->phy_state[port_no].ev_mask;
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_phy_event_poll(const vtss_inst_t     inst,
                            const vtss_port_no_t  port_no,
                            vtss_phy_event_t      *const events)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_event_poll_private(vtss_state, port_no, events);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_ext_event_poll(const vtss_inst_t     inst,
                                const vtss_port_no_t  port_no,
                                vtss_phy_event_t      *const events)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_ext_event_poll_private(vtss_state, port_no, events);
    }
    VTSS_EXIT();
    return rc;
}

/* - Misc.  --------------------------------------------------- */

// Function for enabling/disabling squelch work around.
// In : port_no - Any phy port with the chip
//    : enable  - TRUE = enable squelch workaround, FALSE = Disable squelch workaround
// Return - VTSS_RC_OK - Workaround was enabled/disable. VTSS_RC_ERROR - Squelch workaround patch not loaded
vtss_rc vtss_squelch_workaround(const vtss_inst_t         inst,
                                const vtss_port_no_t      port_no,
                                const BOOL enable)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = squelch_workaround_private(vtss_state, port_no, enable);
    }
    VTSS_EXIT();
    return rc;
}

// See vtss_phy_api.h
vtss_rc vtss_phy_csr_wr(const vtss_inst_t    inst,
                        const u16            page,
                        const vtss_port_no_t port_no,
                        const u16            target,
                        const u32            csr_reg_addr,
                        const u32            value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        switch (page) {
        case VTSS_PHY_PAGE_1588:
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_OPT_PHY_TIMESTAMP)
            rc = vtss_phy_1588_csr_wr_private(vtss_state, port_no, target, csr_reg_addr, value);
#endif
            break;

        case VTSS_PHY_PAGE_MACSEC:
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_FEATURE_MACSEC)
        {
            u32          addr = 0;
            u32          offset = 0;
            u32          target_id = 0;
            u32          base_addr = 0;
            BOOL         use_base_port = TRUE;
            BOOL         valid_addr = FALSE;

            if (target == 0x38) {          // Ingress
                addr = csr_reg_addr + 0x0000;
                valid_addr = TRUE;
            } else if (target == 0x3c) {   // Egress
                addr = csr_reg_addr + 0x8000;
                valid_addr = TRUE;
            } else {
                VTSS_E("port: %d: Invalid Target ID", port_no);
            }

            if (valid_addr) {
                if ((rc = get_base_adr(inst, port_no, 0x1f, addr, &base_addr, &target_id, &offset, &use_base_port)) == VTSS_RC_OK) {
                    rc = vtss_phy_macsec_csr_wr_private(vtss_state, port_no, target_id, offset, value);
                }
            }
        }
#endif
        break;
        default:
            VTSS_E("Unknown page:0x%X for CSR access", page);
        }

    }
    VTSS_EXIT();

    return rc;
}

// See vtss_phy_api.h
vtss_rc vtss_phy_csr_rd(const vtss_inst_t    inst,
                        const u16            page,
                        const vtss_port_no_t port_no,
                        const u16            target,
                        const u32            csr_reg_addr,
                        u32                  *value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        switch (page) {
        case VTSS_PHY_PAGE_1588:
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_OPT_PHY_TIMESTAMP)
            rc = vtss_phy_1588_csr_rd_private(vtss_state, port_no, target, csr_reg_addr, value);
#endif
            break;

        case VTSS_PHY_PAGE_MACSEC:
#if defined(VTSS_CHIP_CU_PHY) && defined(VTSS_FEATURE_MACSEC)
        {
            u32          addr = 0;
            u32          offset = 0;
            u32          target_id = 0;
            u32          base_addr = 0;
            BOOL         use_base_port = TRUE;
            BOOL         valid_addr = FALSE;

            if (target == 0x38) {          // Ingress
                addr = csr_reg_addr + 0x0000;
                valid_addr = TRUE;
            } else if (target == 0x3c) {   // Egress
                addr = csr_reg_addr + 0x8000;
                valid_addr = TRUE;
            } else {
                VTSS_E("port: %d: Invalid Target ID", port_no);
            }

            if (valid_addr) {
                if ((rc = get_base_adr(inst, port_no, 0x1f, addr, &base_addr, &target_id, &offset, &use_base_port)) == VTSS_RC_OK) {
                    rc = vtss_phy_macsec_csr_rd_private(vtss_state, port_no, target_id, offset, value);
                }
            }
        }
#endif
        break;
        default:
            VTSS_E("Unknown page:0x%X for CSR access", page);
        }
    }
    VTSS_EXIT();

    return rc;
}


/* - Debug  --------------------------------------------------- */
// Function printing PHY statistics
static void vtss_phy_debug_stat_print_private(vtss_state_t *vtss_state,
                                              const vtss_debug_printf_t pr,
                                              const vtss_port_no_t      port_no,
                                              const BOOL                print_hdr)
{
    vtss_phy_statistic_t statistics;

    memset(&statistics, 0, sizeof(vtss_phy_statistic_t));

        if (vtss_phy_statistic_get_private(vtss_state, port_no, &statistics) == VTSS_RC_OK) {
            VTSS_D("got phy statistics - ok");
        } else {
            pr("Could not get PHY statistics for port:%d \n", port_no);
            return;
        }

    if (print_hdr) {
        pr("%-5s %-10s %-13s %-9s %-14s %-17s %-14s %-13s\n", "Port", "CU Rx Good", "CU Rx CRC err", "CU Rx Err", "SerDes Tx Good", "SerDes Tx CRC Err", "SerDes Rx Good", "SerDes Rx CRC");
        pr("%-5s %-10s %-13s %-9s %-14s %-17s %-14s %-13s\n", "----", "----------", "-------------", "---------", "--------------", "-----------------", "--------------", "-------------");
    }

    pr("%-5u %-10d %-13d %-9d %-14d %-17d %-14d %-13d\n",
       port_no,
       statistics.cu_good,                  /* 18E1: VTSS_PHY_CU_MEDIA_CRC_GOOD_COUNTER - Cu Media CRC Good Cnt */
       statistics.cu_bad,                   /* 23E1: VTSS_PHY_EXTENDED_PHY_CONTROL_4 - Cu Media CRC Error Cnt */
       statistics.rx_err_cnt_base_tx,       /* 19:   VTSS_PHY_ERROR_COUNTER_1  */
       statistics.serdes_tx_good,           /* 21E3: VTSS_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER - SerDes Tx Good Pkt Cnt */
       statistics.serdes_tx_bad,            /* 22E3: VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER - SerDes Tx CRC Pkt Cnt - Bits 15:14 selects Fibre Media or MAC SerDes */
       statistics.media_mac_serdes_good,    /* 28E3: VTSS_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER - Media/MAC SerDes Rx CRC Good Counter */
       statistics.media_mac_serdes_crc);    /* 29E3: VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER - SerDes Rx CRC Pkt Cnt - Bits 15:14 selects Fibre Media or MAC SerDes*/
}

/* Get statistics */
vtss_rc vtss_phy_debug_stat_print(const vtss_inst_t         inst,
                                  const vtss_debug_printf_t pr,
                                  const vtss_port_no_t      port_no,
                                  const BOOL                print_hdr)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_phy_debug_stat_print_private(vtss_state, pr, port_no, print_hdr);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_1g_debug_info_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info,
                                     const BOOL                ail,
                                     const BOOL                ignore_group_enabled,
                                     const BOOL                print_hdr)
{
    vtss_port_no_t        port_no;
    vtss_phy_port_state_t *ps;
    vtss_phy_event_t      events;
    vtss_phy_type_t       phy_id;


    if (!ignore_group_enabled) {
        if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_PHY)) {
            return VTSS_RC_OK;
        }
    }

    if (ail) {
        /* Application Interface Layer */
        if (print_hdr) {
            pr("Port  Family    Type  Rev  MediaIf                         MacIf         IntrEvent EEE INT MAC WOL Chan Port   1588   uPatch Chip\n");
            pr("                                                                         Poll              SEC     ID   BaseNo BaseNo CRC    Port\n");
            pr("----- --------- ----- ---- ------------------------------- ------------- --------- --- --- --- --- ---- ------ ------ ------ ----\n");
        }
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            vtss_port_no_t base_port = vtss_state->phy_state[port_no].type.base_port_no;
            if (!info->port_list[port_no] || vtss_state->phy_state[port_no].type.part_number == VTSS_PHY_TYPE_NONE) {
                continue;
            }

            VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
            (void)vtss_phy_event_poll_private(vtss_state, port_no, &events);
            ps = &vtss_state->phy_state[port_no];
            VTSS_I("ps->features:0x%X, %p", ps->features, &vtss_state);
            pr("%-4u  %-8s  %-4u  %-4u %-31s %-13s 0x%-7X %-3s %-3s %-3s %-3s %-4d %-6u %-6u 0x%-4X %-4d\n",
               port_no, vtss_phy_family2txt(ps->family),
               ps->type.part_number,
               ps->type.revision,
               vtss_phy_media_if2txt(ps->reset.media_if),
               vtss_phy_mac_if2txt(ps->reset.mac_if),
               events,
               vtss_phy_can(vtss_state, port_no, VTSS_CAP_EEE) ? "Yes" : "No",
               vtss_phy_can(vtss_state, port_no, VTSS_CAP_INT) ? "Yes" : "No",
               vtss_phy_can(vtss_state, port_no, VTSS_CAP_MACSEC) ? "Yes" : "No",
               vtss_phy_can(vtss_state, port_no, VTSS_CAP_WOL)    ? "Yes" : "No",
               phy_id.channel_id,
               phy_id.base_port_no,
               phy_id.phy_api_base_no,
               vtss_state->phy_state[base_port].micro_patch_crc,
               vtss_phy_chip_port(vtss_state, port_no)
              );
        }
    } else {
        /* Chip Interface Layer */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (!info->port_list[port_no] || vtss_state->phy_state[port_no].type.part_number == VTSS_PHY_TYPE_NONE) {
                continue;
            }

            vtss_phy_debug_reg_dump_private(vtss_state, pr, FALSE, port_no);
        }
    }
    return VTSS_RC_OK;
}

// Print internal PHY state
vtss_rc vtss_phy_debug_phyinfo_print(const vtss_inst_t         inst,
                                     const vtss_debug_printf_t pr,
                                     const vtss_port_no_t      port_no,
                                     const BOOL                print_hdr)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_OK;
    vtss_debug_info_t info;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        memset(&info, 0, sizeof(info));
        info.port_list[port_no] = TRUE;
        rc = vtss_phy_1g_debug_info_print(vtss_state, pr, &info, TRUE, TRUE, print_hdr);
    }
    VTSS_EXIT();
    return rc;
}

static void vtss_phy_debug_reg_header(const vtss_debug_printf_t pr, const char *name)
{
    pr("%-45s   DEV_ID REG_ADDR   VALUE\n", "REG_NAME");
}

static void vtss_phy_deb_pr_reg (vtss_state_t *vtss_state, const vtss_debug_printf_t pr,
                                 vtss_port_no_t port_no,
                                 u16 page, u16 addr, const char *name, u16 *value)
{

    vtss_miim_read_t miim_read_fn = vtss_state->init_conf.miim_read;
    vtss_miim_write_t miim_write_fn = vtss_state->init_conf.miim_write;

    /* Change page */
    if (page) {
        miim_write_fn(vtss_state, port_no, 31, page);
    }
    miim_read_fn(vtss_state, port_no, addr, value);
    pr("%-45s:  0x%02x   0x%04x     0x%08x\n", name, page, addr, *value);

}
static vtss_rc vtss_phy_debug_reg_dump_private(vtss_state_t *vtss_state,
                                               const vtss_debug_printf_t pr,
                                               BOOL clear,
                                               const vtss_port_no_t port_no)
{
    vtss_rc rc = VTSS_RC_OK;
    char buf[32];
    u16 value;

    if (clear) {
        pr("Nothing to Clear, exiting\n");
    } else {
        sprintf(buf, "PORT %d", port_no);
        vtss_phy_debug_reg_header(pr, buf);
        pr("Main Page Registers\n");
        rc = vtss_phy_page_std(vtss_state, port_no);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 0,  "MODE_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 1,  "MODE_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 2,  "PHY_ID1", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 3,  "PHY_ID2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 4,  "ANEG_ADVERTISEMENT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 5,  "ANEG_LP_ABILITY", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 6,  "ANEG_EXPANSION", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 7,  "ANEG_NEXT_PAGE_TRANSMIT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 8,  "ANEG_LP_NEXT_PAGE_RECV", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 9,  "1000BASE-T_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 10, "1000BASE-T_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 11, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 12, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 13, "CLASUE45_ACCESS1", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 14, "CLASUE45_ACCESS2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 15, "1000BASE-T_STATUS_EXTENSION_1", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 16, "1000BASE-TX_STATUS_EXTENSION", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 17, "1000BASE-T_STATUS_EXTENSION_2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 18, "BYPASS_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 19, "ERROR_COUNTER_1", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 20, "ERROR_COUNTER_2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 21, "ERROR_COUNTER_3", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 22, "EXTENDED_CONTROL_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 23, "EXTENDED_PHY_CONTROL_1", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 24, "EXTENDED_PHY_CONTROL_2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 25, "INTERRUPT_MASK", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 26, "INTERRUPT_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 27, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 28, "AUXILIARY_CONTROL_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 29, "LED_MODE_SELECT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 30, "LED_BEHAVIOUR", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x0, 31, "EXTENDED_REG_PAGE_ACCESS", &value);

        pr("\n\nExtended Page1 Registers\n");
        rc = vtss_phy_page_ext(vtss_state, port_no);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 16, "SERDES_MEDIA_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 17, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 18, "CU_MEDIA_CRC_GOOD_COUNTER", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 19, "EXTENDED_MODE_SIGDET_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 20, "EXTENDED_PHY_CONTROL_3", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 21, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 22, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 23, "EXTENDED_PHY_CONTROL_4", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 24, "VERIPHY_1", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 25, "VERIPHY_2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 26, "VERIPHY_3", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 27, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 28, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 29, "EPG1", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 30, "EPG2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x1, 31, "EXTENDED_REG_PAGE_ACCESS", &value);

        pr("\n\nExtended Page2 Registers\n");
        rc = vtss_phy_page_ext2(vtss_state, port_no);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 16, "CU_PMD_TRANSMIT_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 17, "EEE_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 18, "EXTENDED_CHIP_ID", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 19, "ENTROPY_DATA", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 20, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 21, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 22, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 23, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 24, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 25, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 26, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 27, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 28, "EXTENDED_INTERRUPT_MASK", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 29, "EXTENDED_INTERRUPT_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 30, "RING_RESILIENCY_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x2, 31, "EXTENDED_REG_PAGE_ACCESS", &value);

        pr("\n\nExtended Page3 Registers\n");
        rc = vtss_phy_page_ext3(vtss_state, port_no);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 16, "MAC_SERDES_PCS_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 17, "MAC_SERDES_PCS_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 18, "MAC_SERDES_CL37_ADV_ABILITY", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 19, "MAC_SERDES_CL37_LP_ABILITY", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 20, "MAC_SERDES_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 21, "MAC_MEDIA_SERDES_TX_GOOD_PKT_COUNT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 22, "MAC_MEDIA_SERDES_TX_CRC_ERROR_COUNT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 23, "MEDIA_SERDES_PCS_CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 24, "MEDIA_SERDES_PCS_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 25, "MEDIA_SERDES_CL37_ADV_ABILITY", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 26, "MEDIA_SERDES_CL37_LP_ABILITY", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 27, "MAC_MEDIA_SERDES_RECEIVE_STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 28, "MAC_MEDIA_SERDES_RX_GOOD_PKT_COUNT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 29, "MAC_MEDIA_SERDES_RX_CRC_ERROR_COUNT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 30, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x3, 31, "EXTENDED_REG_PAGE_ACCESS", &value);

        pr("\n\nGPIO Registers\n");
        rc = vtss_phy_page_gpio(vtss_state, port_no);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 13, "LED/SIGDET/GPIO CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 14, "GPIO CONTROL_2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 15, "GPIO INPUT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 16, "GPIO OUTPUT", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 17, "GPIO OUTPUT ENABLE", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 18, "MICRO CMD", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 19, "MAC MODE AND FAST LINK CONFIG", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 20, "TWO-WIRE SERIAL MUX CONTROL_1", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 21, "TWO-WIRE SERIAL MUX CONTROL_2", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 22, "TWO-WIRE SERIAL MUX DATA R/W", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 23, "RECOVERED CLK_1 CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 24, "RECOVERED CLK_2 CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 25, "ENHANCED LED CONTROL", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 26, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 27, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 28, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 29, "GLOBAL INTERRUPT STATUS", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 30, "RESERVED", &value);
        vtss_phy_deb_pr_reg(vtss_state, pr, port_no, 0x10, 31, "EXTENDED_REG_PAGE_ACCESS", &value);
        pr("\n\n");

        rc = vtss_phy_page_std(vtss_state, port_no);
    }
    return rc;
}

vtss_rc vtss_phy_debug_register_dump (const vtss_inst_t inst,
                                      const vtss_debug_printf_t pr,
                                      BOOL clear, const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_RC_COLD(vtss_phy_debug_reg_dump_private(vtss_state, pr, clear, port_no));
    }
    VTSS_EXIT();
    return rc;
}


// Setup Internal Loopback in the PHY
vtss_rc vtss_phy_loopback_set(const vtss_inst_t    inst,
                              const vtss_port_no_t port_no,
                              vtss_phy_loopback_t  loopback)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->phy_state[port_no].loopback.far_end_enable = loopback.far_end_enable;
        vtss_state->phy_state[port_no].loopback.near_end_enable = loopback.near_end_enable;
        vtss_state->phy_state[port_no].loopback.connector_enable = loopback.connector_enable;
        vtss_state->phy_state[port_no].loopback.mac_serdes_input_enable = loopback.mac_serdes_input_enable;
        vtss_state->phy_state[port_no].loopback.mac_serdes_facility_enable = loopback.mac_serdes_facility_enable;
        vtss_state->phy_state[port_no].loopback.mac_serdes_equipment_enable = loopback.mac_serdes_equipment_enable;
        vtss_state->phy_state[port_no].loopback.media_serdes_input_enable = loopback.media_serdes_input_enable;
        vtss_state->phy_state[port_no].loopback.media_serdes_facility_enable = loopback.media_serdes_facility_enable;
        vtss_state->phy_state[port_no].loopback.media_serdes_equipment_enable = loopback.media_serdes_equipment_enable;

#if defined(VTSS_OPT_PHY_TIMESTAMP)
        rc = VTSS_RC_COLD(vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, FALSE));
        if (rc == VTSS_RC_OK) {
#endif

            rc = VTSS_RC_COLD(vtss_phy_loopback_set_private(vtss_state, port_no));

#if defined(VTSS_OPT_PHY_TIMESTAMP)
            rc = VTSS_RC_COLD(vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, FALSE));
        }
#endif

    }
    VTSS_EXIT();
    return rc;
}


/* Set do_page_chk */
vtss_rc vtss_phy_do_page_chk_set(const vtss_inst_t          inst,
                                 const BOOL                     enable)
{
    vtss_rc rc = VTSS_RC_OK;
    VTSS_ENTER();
    vtss_phy_do_page_chk_set_private(enable);
    VTSS_EXIT();
    return rc;
}

/* Set do_page_chk */
vtss_rc vtss_phy_do_page_chk_get(const vtss_inst_t          inst,
                                 BOOL                       *enable)
{
    vtss_rc rc = VTSS_RC_OK;
    VTSS_ENTER();
    vtss_phy_do_page_chk_get_private(enable);
    VTSS_EXIT();
    return rc;
}

/* Get the current loopback */
vtss_rc vtss_phy_loopback_get(const vtss_inst_t         inst,
                              const vtss_port_no_t      port_no,
                              vtss_phy_loopback_t   *loopback)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *loopback = vtss_state->phy_state[port_no].loopback;
    }
    VTSS_EXIT();
    return rc;
}

// Function for checking if firmware is downloaded correctly
vtss_rc vtss_phy_is_8051_crc_ok(const vtss_inst_t       inst,
                                const vtss_port_no_t    port_no,
                                u16                     code_length,
                                u16                     expected_crc)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    BOOL         first_time = FALSE; // This is set to TRUE in cases where Failing CRC Check is NOT an Error

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_is_8051_crc_ok_private(vtss_state, port_no, FIRMWARE_START_ADDR, code_length, expected_crc, first_time);
    }
    VTSS_EXIT();
    return rc;
}

// Function for setting ob_post0 patch
vtss_rc vtss_phy_cfg_ob_post0(const vtss_inst_t       inst,
                              const vtss_port_no_t    port_no,
                              const u16               value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        rc = vtss_phy_cfg_ob_post0_private(vtss_state, port_no, value);
#endif
    }
    VTSS_EXIT();
    return rc;
}

// Function for setting ib_cterm patch
vtss_rc vtss_phy_cfg_ib_cterm(const vtss_inst_t       inst,
                              const vtss_port_no_t    port_no,
                              const u8                ib_cterm_ena,
                              const                   u8 ib_eq_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        rc = vtss_phy_cfg_ib_cterm_ena_private(vtss_state, port_no, ib_cterm_ena, ib_eq_mode);
#endif
    }
    VTSS_EXIT();
    return rc;
}

// Function for getting patch settings
vtss_rc vtss_phy_patch_settings_get(const vtss_inst_t       inst,
                                    const vtss_port_no_t    port_no,
                                    u8                      *mcb_bus,
                                    u8                      *cfg_buf,
                                    u8                      *stat_buf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        rc = vtss_phy_patch_setttings_get_private(vtss_state, port_no, mcb_bus, cfg_buf, stat_buf);
#endif
    }
    VTSS_EXIT();
    return rc;
}

// Function for finding flow status in auto neg mode
vtss_rc vtss_phy_flowcontrol_decode_status(const vtss_inst_t       inst,
                                           const vtss_port_no_t port_no,
                                           u16 lp_auto_neg_advertisment_reg,
                                           const vtss_phy_conf_t phy_setup,
                                           vtss_port_status_t *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_phy_flowcontrol_decode_status_private(port_no, lp_auto_neg_advertisment_reg, phy_setup, status);
    }
    VTSS_EXIT();
    return rc;
}


// See vtss_phy_api.h
vtss_rc vtss_phy_gpio_mode(const vtss_inst_t          inst,
                           const vtss_port_no_t       port_no,
                           const u8                   gpio_no,
                           const vtss_phy_gpio_mode_t mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_gpio_mode_private(vtss_state, port_no, gpio_no, mode);
    }
    VTSS_EXIT();
    return rc;
}

// See vtss_phy_api.h
vtss_rc vtss_phy_gpio_get(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          const u8             gpio_no,
                          BOOL                 *value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_gpio_get_private(vtss_state, port_no, gpio_no, value);
    }
    VTSS_EXIT();
    return rc;
}

// See vtss_phy_api.h
vtss_rc vtss_phy_gpio_set(const vtss_inst_t          inst,
                          const vtss_port_no_t      port_no,
                          const u8                  gpio_no,
                          const BOOL                value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_gpio_set_private(vtss_state, port_no, gpio_no, value);
    }
    VTSS_EXIT();
    return rc;
}

// Enable/Disable Isolate mode
vtss_rc vtss_phy_isolate_mode_conf(const vtss_inst_t          inst,
                          const vtss_port_no_t      port_no,
                          const BOOL                iso_en)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_iso_set_private(vtss_state, port_no,   iso_en);
    }
    VTSS_EXIT();
    return rc;
}


// ****************************************************************************

/* ================================================================= */
// Private Function that is called for External Connector Loopback
/**
 * \brief Function for configuring External Connector Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param lpback                       [IN]    TRUE=Loopback ON, FALSE=Loopback OFF
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/

vtss_rc vtss_phy_ext_connector_loopback_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no, BOOL lpback)
{
    vtss_rc rc = VTSS_RC_OK;
    vtss_state->phy_state[port_no].loopback.connector_enable = lpback;
    // Enable 1000BaseT connector Loopback, Set Reg24.0=1
    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2,
                                    (vtss_state->phy_state[port_no].loopback.connector_enable ? VTSS_F_PHY_EXTENDED_PHY_CONTROL_2_CONNECTOR_LOOPBACK_MODE : 0),
                                    VTSS_F_PHY_EXTENDED_PHY_CONTROL_2_CONNECTOR_LOOPBACK_MODE)); // Connector Loopback
    // Disable Pair Swap Correction, Set Reg18.5=1
    VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL,
                                    (vtss_state->phy_state[port_no].loopback.connector_enable ? VTSS_F_PHY_BYPASS_CONTROL_DISABLE_PARI_SWAP_CORRECTION : 0),
                                    VTSS_F_PHY_BYPASS_CONTROL_DISABLE_PARI_SWAP_CORRECTION)); // Connector Loopback

    return rc;
}

/* ================================================================= */
// Public Function that is called for External Connector Loopback
/**
 * \brief Function for configuring External Connector Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param lpback                       [IN]    TRUE=Loopback ON, FALSE=Loopback OFF
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_ext_connector_loopback(const vtss_inst_t  inst, const vtss_port_no_t port_no, BOOL lpback)
{

    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_ext_connector_loopback_private( vtss_state, port_no, lpback);
    }
    VTSS_EXIT();
    return rc;
}

/* ================================================================= */
// Function that is called for MAC SerDes Loopback on sgmii or qsgmii - Facility loop
// Call with lpback=1 to start and call again with lpback=0 to stop
// This function specifically avoids bugzilla #5731
/**
 * \brief Private Function for configuring MAC-SerDes(SGMII) Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param mode                         [IN]    serdes mode and port
 *        mode: bits 15:12: 0x8= Fibre Media or 0x9=SGMII/QSGMII MAC
 *        mode: bits 11:8: Port Address (0-3)
 *        mode: bits 7:4: Loopback Type: 0=No,1=Pad,2=Input,4=Facility,8=Equipment
 *        mode: bits 3:0: 0x2
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
static vtss_rc vtss_phy_serdes_sgmii_loopback_private (vtss_state_t *vtss_state, const vtss_port_no_t port_no, const u16 mode)
{
    u16 reg_value = 0;
    u16 macroVal  = 0;
    u16 sgmiiVal  = 0;
    u16 loopback_type = 0;
    u16 portAddr = 0;
    u16 tmp = 0;

    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    loopback_type = (mode & 0x00f0) >> 4;
    VTSS_D("mode: 0x%X, Loopback_type: 0x%X", mode, loopback_type);

    // Bugzilla#5731 - The following code-sequence is needed for Luton26 Rev. A and B where
    // a consumptive patch disables interrupts inside a micro-command patch.

    // Set to micro/GPIO-page
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

    //----------------------------------------------------------------------
    // Pass the NOP cmd to Micro to insure that any consumptive patch exits
    // There is no issue with doing this on any revision since it is just a NOP on any Vitesse PHY.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x800f));

    // Poll on 18G.15 to clear
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
    //----------------------------------------------------------------------
    // Set to micro/GPIO-page (Has been set to std page by vtss_phy_wait_for_micro_complete
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    // This sets the loopback and works for MAC I/F as well as MEDIA I/F
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, mode));

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:

        if ((loopback_type == VTSS_SERDES_LB_FACILITY) ||    // Facility Loopback
            (loopback_type == VTSS_SERDES_LB_NONE)) {        // Turning OFF Facility Loopback
            // microval = 0x8n03; n=0 for SGMII0; n=1 for SGMII1; n=3 for SGMII2; n=5 for SGMII3; Written to 18G
            macroVal  = 0x8003;
            portAddr = (mode & 0x0f00) >> 8;
            if (portAddr == 0) {    // VTSS_PORT_INTERFACE_QSGMII, Only Port 0
                macroVal = 0x8003;   // SerDes 0
            } else if (portAddr == 1) { // VTSS_PORT_INTERFACE_SGMII, Port 1
                macroVal = 0x8103;   // SerDes 1
            } else if (portAddr == 2) { // VTSS_PORT_INTERFACE_SGMII, Port 2
                macroVal = 0x8303;   // SerDes 3
            } else if (portAddr == 3) { // VTSS_PORT_INTERFACE_SGMII, Port 3
                macroVal = 0x8503;   // SerDes 5
            }

            // sgmiiVal = 0x9m03; m=0 for PHY 0; m=1 for PHY1; m=2 for PHY2; m=3 for PHY3; Written to 18G
            sgmiiVal  = 0x9040 | (portAddr << 8);

            if ((ps->reset.mac_if == VTSS_PORT_INTERFACE_SGMII) && (portAddr != 0)) {
                VTSS_D("mode: 0x%X, Writing SerDes macroVal: 0x%X, sgmiiVal: 0x%X", mode, macroVal, sgmiiVal );
                // 1G Macro programming
                // Set to micro/GPIO-page (Has been set to std page by vtss_phy_wait_for_micro_complete
                VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
                // Use physical address of Serdes macro
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, macroVal ));

                // Tesla is a Quad Port device and Atom12 is a 12 Port Device
                if (ps->family == VTSS_PHY_FAMILY_TESLA) {
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7cb));
                } else {  // Atom12
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d3));
                }

                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg_value));

                reg_value = reg_value & 0x0ff0;

                if (loopback_type == VTSS_SERDES_LB_FACILITY) {        // Facility Loopback
                    tmp = reg_value | 0x0010;
                } else {                                               // Turning OFF Facility Loopback
                    tmp = reg_value & 0x0fe0;
                }

                tmp = tmp | 0x8006;
                VTSS_D("sgmiiVal: 0x%X, Read reg_val: 0x%X,  Writing tmp: 0x%X", sgmiiVal, reg_value, tmp);
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, tmp));
                // Use logical address for port
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, sgmiiVal ));
            }

            // 6G Macro programming
            if ((ps->reset.mac_if == VTSS_PORT_INTERFACE_QSGMII) ||
                ((ps->reset.mac_if == VTSS_PORT_INTERFACE_SGMII) && (portAddr == 0))) {
                // Set to micro/GPIO-page (Has been set to std page by vtss_phy_wait_for_micro_complete
                reg_value = 0;
                VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8013));

                if (ps->family == VTSS_PHY_FAMILY_TESLA) {
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7cb)); // Tesla Vector
                } else {
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d3)); // Atom12 Vector
                }

                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));
                VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg_value));

                reg_value = reg_value & 0x0ff0;

                if (loopback_type == VTSS_SERDES_LB_FACILITY) {       // Facility Loopback
                    tmp = reg_value | 0x0100;
                } else {                                              // Turning OFF Facility Loopback
                    tmp = reg_value & 0x0ef0;
                }

                tmp = tmp | 0x8006;
                VTSS_D("Read reg_val: 0x%X,  Writing tmp: 0x%X", reg_value, tmp);
                VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, tmp));

                // Tesla is a Quad Port device and Atom12 is a 12 Port Device, so diff Vector per Quad
                if (ps->family == VTSS_PHY_FAMILY_TESLA) {
                    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9c40));
                } else {   // Atom12
                    if (portAddr < 4) {
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9c40));  // Atom12 Ports 0 - 3
                    } else if ((portAddr > 3) && (portAddr < 8)) {
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9d40));  // Atom12 Ports 4 - 7
                    } else if ((portAddr > 7) && (portAddr < 12)) {
                        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x9e40));  // Atom12 Ports 8 - 11
                    }
                }
            }
        }

        if ((loopback_type == VTSS_SERDES_LB_EQUIPMENT) ||  // Equipment LoopBack
            (loopback_type == VTSS_SERDES_LB_NONE)) {       // Turning OFF Equipment Loopback
            u16 reg17 = 0;
            // Read-modify-write word in Token Ring containing SigDet
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa68c));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));

            if (loopback_type == VTSS_SERDES_LB_EQUIPMENT) {  //  Setting Equipment LoopBack
                reg17 |= 0x0010;         //Set SigDet as desired, Set bit 4
            } else {
                reg17 &= 0xffef;         //Clear SigDet as desired, Clear bit 4
            }
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x868c));
        }

        break;

    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:

        if ((loopback_type == VTSS_SERDES_LB_EQUIPMENT) ||  // Equipment LoopBack
            (loopback_type == VTSS_SERDES_LB_NONE)) {       // Turning OFF Equipment Loopback
            u16 reg17 = 0;
            // Read-modify-write word in Token Ring containing SigDet
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa68c));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));

            if (loopback_type == VTSS_SERDES_LB_EQUIPMENT) {  //  Setting Equipment LoopBack
                reg17 |= 0x0010;         //Set SigDet as desired, Set bit 4
            } else {
                reg17 &= 0xffef;         //Clear SigDet as desired, Clear bit 4
            }
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x868c));
        }

        break;

    default:
        VTSS_D(" MAC LOOPBACK on sgmii/qsgmii I/F Not Supported on Family: x%x", ps->family );
        break;
    }
    return vtss_phy_page_std(vtss_state, port_no);
}

/* ================================================================= */
// Private Function that is called for SerDes Fibre Media Side Loopback
// Call with lpback=1 to start and call again with lpback=0 to stop
// This function specifically avoids bugzilla #5731
/**
 * \brief Function for configuring Fibre-Media SerDes Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param mode                         [IN]    serdes mode and port
 *        mode: bits 15:12: 0x8= Fibre Media or 0x9=SGMII/QSGMII MAC
 *        mode: bits 11:8: Port Address (0-3)
 *        mode: bits 7:4: Loopback Type: 0=No,1=Pad,2=Input,4=Facility,8=Equipment
 *        mode: bits 3:0: 0x2
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
static vtss_rc vtss_phy_serdes_fmedia_loopback_private (vtss_state_t *vtss_state, const vtss_port_no_t port_no, const u16 mode)
{
    u16 reg_value = 0;
    u16 macroVal  = 0;
    u16 fiberVal  = 0;
    u16 loopback_type = 0;
    u16 portAddr = 0;
    u16 tmp = 0;

    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    loopback_type = (mode & 0x00f0) >> 4;
    VTSS_D("mode: 0x%X, Loopback_type: 0x%X", mode, loopback_type);

    // Bugzilla#5731 - The following code-sequence is needed for Luton26 Rev. A and B where
    // a consumptive patch disables interrupts inside a micro-command patch.

    // Set to micro/GPIO-page
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

    //----------------------------------------------------------------------
    // Pass the NOP cmd to Micro to insure that any consumptive patch exits
    // There is no issue with doing this on any revision since it is just a NOP on any Vitesse PHY.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x800f));

    // Poll on 18G.15 to clear
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
    //----------------------------------------------------------------------

    // Set to micro/GPIO-page (Has been set to std page by vtss_phy_wait_for_micro_complete
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    // This works for MAC I/F as well as MEDIA I/F
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, mode));
    VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:
        if ((loopback_type == VTSS_SERDES_LB_FACILITY) ||  // Facility Loop Back
            (loopback_type == VTSS_SERDES_LB_NONE)) {      // Turning OFF Facility Loopback
            // Media Interface Only
            // Fibre Ports are by bit position, ie: Fibre0=1, Fibre1=2, Fibre2=4, Fibre3=8
            // Port_no's are 1, 2, 4, 8
            // microval = 0x8n03; n=0 for PHY 0; n=2 for PHY1; n=4 for PHY2; n=6 for PHY3;
            macroVal  = 0x8003;
            portAddr = (mode & 0x0f00) >> 8;
            if (portAddr == 1) {
                macroVal = 0x8003;  // SerDes0
                fiberVal = 0;
            } else if (portAddr == 2) {
                macroVal = 0x8203;  // SerDes 2
                fiberVal = 1;
            } else if (portAddr == 4) {
                macroVal = 0x8403;  // SerDes 4
                fiberVal = 2;
            } else if (portAddr == 8) {
                macroVal = 0x8603;  // SerDes 6
                fiberVal = 3;
            }

            // fiberVal = 0x8m40; m=1 for PHY 0; m=2 for PHY1; m=4 for PHY2; m=8 for PHY3; Written to 18G
            fiberVal  = 0x8040 | ((1 << fiberVal) << 8);

            VTSS_D("mode: 0x%X, macroVal: 0x%X, fiberVal:0x%X", mode, macroVal, fiberVal);

            // physical address of Serdes macro
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            // microval = 0x8n03; n=0 for PHY 0; n=2 for PHY1; n=4 for PHY2; n=6 for PHY3; Written to 18G
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, macroVal));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7cb));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8007));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg_value));

            reg_value = reg_value & 0x0ff0;

            if (loopback_type == VTSS_SERDES_LB_FACILITY) {    // Facility Loopback
                tmp = reg_value | 0x0010;
            } else {                                           // Turning OFF Facility Loopback
                tmp = reg_value & 0x0fe0;
            }

            tmp = tmp | 0x8006;
            VTSS_D("fiberVal: 0x%X, reg_val: 0x%X,  tmp: 0x%X", fiberVal, reg_value, tmp);
            // logical addr fiber media i/f
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, tmp));
            // fiberVal = 0x8m40; m=1 for PHY 0; m=2 for PHY1; m=4 for PHY2; m=8 for PHY3; Written to 18G
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, fiberVal));
        }

        if ((loopback_type == VTSS_SERDES_LB_EQUIPMENT) ||  // Equipment LoopBack
            (loopback_type == VTSS_SERDES_LB_NONE)) {       // Turning OFF Equipment Loopback
            u16 reg17 = 0;
            // Read-modify-write word in Token Ring containing SigDet
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa68a));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));

            if (loopback_type == VTSS_SERDES_LB_EQUIPMENT) {  //  Setting Equipment LoopBack
                reg17 |= 0x0030;         //Set SigDet as desired, Set bits 5:4
            } else {
                reg17 &= 0xffcf;         //Clear SigDet as desired, Clear bits 5:4
            }
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x868a));
        }

        break;

    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:

        if ((loopback_type == VTSS_SERDES_LB_EQUIPMENT) ||  // Equipment LoopBack
            (loopback_type == VTSS_SERDES_LB_NONE)) {       // Turning OFF Equipment Loopback
            u16 reg17 = 0;
            // Read-modify-write word in Token Ring containing SigDet
            VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xa68a));
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));

            if (loopback_type == VTSS_SERDES_LB_EQUIPMENT) {  //  Setting Equipment LoopBack
                reg17 |= 0x0030;         //Set SigDet as desired, Set bits 5:4
            } else {
                reg17 &= 0xffcf;         //Clear SigDet as desired, Clear bits 5:4
            }
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
            VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x868a));
        }

        break;

    default:
        VTSS_D(" MEDIA LOOPBACK on Media I/F Not Supported on Family: x%x", ps->family );
        break;
    }
    return vtss_phy_page_std(vtss_state, port_no);
}


/* ================================================================= */
// Public Function that is called for MAC (SGMII/QSGMII) SerDes Loopback
// Call with lpback=1 to start and call again with lpback=0 to stop
// This function specifically avoids bugzilla #5731
/**
 * \brief Private Function for configuring MAC-SerDes(SGMII) Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param mode                         [IN]    serdes mode and port
 *        mode: bits 15:12: 0x8= Fibre Media or 0x9=SGMII/QSGMII MAC
 *        mode: bits 11:8: Port Address (0-3)
 *        mode: bits 7:4: Loopback Type: 0=No,1=Pad,2=Input,4=Facility,8=Equipment
 *        mode: bits 3:0: 0x2
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_serdes_sgmii_loopback(const vtss_inst_t  inst, const vtss_port_no_t port_no, const u16 mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_serdes_sgmii_loopback_private (vtss_state, port_no, mode);
    }
    VTSS_EXIT();
    return rc;
}

/* ================================================================= */
// Public Function that is called for SerDes Fibre Media Side Loopback
// Call with lpback=1 to start and call again with lpback=0 to stop
// This function specifically avoids bugzilla #5731
/**
 * \brief Function for configuring Fibre-Media SerDes Loopback.
 * \param inst                         [IN]    Target instance reference.
 * \param port_no                      [IN]    The port in question.
 * \param mode                         [IN]    serdes mode and port
 *        mode: bits 15:12: 0x8= Fibre Media or 0x9=SGMII/QSGMII MAC
 *        mode: bits 11:8: Port Address (0-3)
 *        mode: bits 7:4: Loopback Type: 0=No,1=Pad,2=Input,4=Facility,8=Equipment
 *        mode: bits 3:0: 0x2
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_serdes_fmedia_loopback(const vtss_inst_t  inst, const vtss_port_no_t port_no, const u16 mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_serdes_fmedia_loopback_private (vtss_state, port_no, mode);
    }
    VTSS_EXIT();
    return rc;
}


/**
 * \brief Private debug function to get PHY Register dump
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
static vtss_rc vtss_phy_get_regdump_private(vtss_state_t              *vtss_state,
                                            const vtss_port_no_t       port_no,
                                            const u32                  phy_page_no,
                                            vtss_phy_page_reg_dump_t *p_info)
{
    u32                   idx;
    u16                   reg_value = 0;

    p_info->phy_port = port_no;
    p_info->page = phy_page_no;

    for (idx = 0; idx < 4; idx++) {
        p_info->page_code[idx] = '\0';
    }

    /* Chip Interface Layer */
    switch (p_info->page) {
    case VTSS_PHY_PAGE_STANDARD:
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        p_info->page_code[0] = 'S';
        p_info->page_code[1] = 't';
        p_info->page_code[2] = 'd';
        break;
    case VTSS_PHY_PAGE_EXTENDED:
        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        p_info->page_code[0] = 'E';
        p_info->page_code[1] = '1';
        break;
    case VTSS_PHY_PAGE_EXTENDED_2:
        VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
        p_info->page_code[0] = 'E';
        p_info->page_code[1] = '2';
        break;
    case VTSS_PHY_PAGE_EXTENDED_3:
        VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
        p_info->page_code[0] = 'E';
        p_info->page_code[1] = '3';
        break;
    case VTSS_PHY_PAGE_GPIO:
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        p_info->page_code[0] = 'G';
        break;
    case VTSS_PHY_PAGE_1588:
        VTSS_RC(vtss_phy_page_1588(vtss_state, port_no));
        p_info->page_code[0] = '1';
        p_info->page_code[1] = '5';
        p_info->page_code[2] = '8';
        p_info->page_code[3] = '8';
        break;
    case VTSS_PHY_PAGE_MACSEC:
        VTSS_RC(vtss_phy_page_macsec(vtss_state, port_no));
        p_info->page_code[0] = 'M';
        p_info->page_code[1] = 'S';
        break;
    case VTSS_PHY_PAGE_TEST:
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        p_info->page_code[0] = 'T';
        p_info->page_code[1] = 'E';
        p_info->page_code[2] = 'S';
        p_info->page_code[3] = 'T';
        break;
    case VTSS_PHY_PAGE_TR:
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        p_info->page_code[0] = 'T';
        p_info->page_code[1] = 'R';
        break;
    case VTSS_PHY_PAGE_0x2DAF:
        VTSS_RC(vtss_phy_page_0x2daf(vtss_state, port_no));
        p_info->page_code[0] = '2';
        p_info->page_code[1] = 'D';
        p_info->page_code[2] = 'A';
        p_info->page_code[3] = 'F';
        break;
    default:
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        break;
    }

    for (idx = 0; idx < MAX_REGISTERS_PER_PAGE; idx++) {
        // VTSS_RC(vtss_phy_read_page(vtss_state, port_no, phy_page_no, idx, &reg_value));
        VTSS_RC(vtss_phy_rd(vtss_state, port_no, idx, &reg_value));
        p_info->reg[idx] = idx;
        p_info->reg_value[idx] = reg_value;
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return VTSS_RC_OK;
}

/**
 * \brief debug function for printing some of the internal PHY Registers
 * \param inst      [IN] Target instance reference.
 * \param pr        [IN] Function pointer to print function e.g. CPRINTF
 * \param port_no   [IN] Port in question
 * \param page_no   [IN] Page No in question, 0, 1, 2, 3, 1588, MACSEC, TEST, TR
 * \param print_hdr [IN] Set to TRUE to print header and phy state info. Set FALSE to only print state info. Normally this is set to TRUE for the first port called, and FALSE for the rest in order to only get one (common) header
 * \return Return code. VTSS_RC_OK if not errors were seen during warm-start else VTSS_RC_ERROR.*/
vtss_rc vtss_phy_debug_regdump_print(const vtss_inst_t         inst,
                                     const vtss_debug_printf_t pr,
                                     const vtss_port_no_t      port_no,
                                     const u32                 page_no,
                                     const BOOL                print_hdr)
{
    u32           idx = 0;
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_OK;
    vtss_phy_page_reg_dump_t  info;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        memset(&info, 0, sizeof(info));
        rc = vtss_phy_get_regdump_private(vtss_state, port_no, page_no, &info);

        if (print_hdr) {
            pr("%-5s %-5s %-14s %-10s \n", "Port", "Page", "Reg-Page Code", "HEX Value");
            pr("%-5s %-5s %-14s %-10s \n", "----", "----", "-------------", "---------");
            VTSS_D("%-5s %-5s %-14s %-10s ", "Port", "Page", "Reg-Page Code", "HEX Value");
            VTSS_D("%-5s %-5s %-14s %-10s ", "----", "----", "-------------", "---------");
        }

        for (idx = 0; idx < MAX_REGISTERS_PER_PAGE; idx++) {
            pr("%4d 0x%04x  %4d-%-4s      0x%04x \n", info.phy_port, info.page, info.reg[idx], info.page_code, info.reg_value[idx]);
            VTSS_D("%4d 0x%04x  %4d-%-4s      0x%04x ", info.phy_port, info.page, info.reg[idx], info.page_code, info.reg_value[idx]);
        }

    }
    VTSS_EXIT();
    return rc;
}


static vtss_rc vtss_phy_wol_conf_get_private(vtss_state_t         *vtss_state,
                                             const vtss_port_no_t  port_no,
                                             vtss_phy_wol_conf_t  *wol_conf)
{
    vtss_rc     rc = VTSS_RC_OK;
    u16         regVal = 0;

    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    // WOL MAC Addr
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_WOL_LOWER_MAC_ADDR, &regVal));
    wol_conf->wol_mac.addr[0] = regVal & 0x00ff;
    wol_conf->wol_mac.addr[1] = (regVal & 0xff00) >> 8;

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_WOL_MID_MAC_ADDR, &regVal));
    wol_conf->wol_mac.addr[2] = regVal & 0x00ff;
    wol_conf->wol_mac.addr[3] = (regVal & 0xff00) >> 8;

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_WOL_UPPER_MAC_ADDR, &regVal));
    wol_conf->wol_mac.addr[4] = regVal & 0x00ff;
    wol_conf->wol_mac.addr[5] = (regVal & 0xff00) >> 8;


    // WOL Secure-ON Password
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_WOL_LOWER_PASSWD, &regVal));
    wol_conf->wol_pass.passwd[0] = regVal & 0x00ff;
    wol_conf->wol_pass.passwd[1] = (regVal & 0xff00) >> 8;

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_WOL_MID_PASSWD, &regVal));
    wol_conf->wol_pass.passwd[2] = regVal & 0x00ff;
    wol_conf->wol_pass.passwd[3] = (regVal & 0xff00) >> 8;

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_WOL_UPPER_PASSWD, &regVal));
    wol_conf->wol_pass.passwd[4] = regVal & 0x00ff;
    wol_conf->wol_pass.passwd[5] = (regVal & 0xff00) >> 8;

    regVal = 0;
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_WOL_CONTROL, &regVal));
    // Default = 0 or Disabled
    wol_conf->secure_on_enable = 0;
    if (regVal & VTSS_PHY_WOL_CONTROL_SECURE_ON_ENABLE) {
        wol_conf->secure_on_enable = 1;
    }

    // Default = 0 or 6 bytes
    wol_conf->wol_passwd_len = VTSS_WOL_PASSWD_LEN_6;
    if (regVal & VTSS_PHY_WOL_CONTROL_SECURE_ON_PASSWD_LEN_4) {
        wol_conf->wol_passwd_len = VTSS_WOL_PASSWD_LEN_4;
    }

    // Magic Pkt Count Ranges from 1 to 16
    wol_conf->magic_pkt_cnt = ((regVal & 0x0f00) >> 8) + 1;

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return (rc);
}

static vtss_rc vtss_phy_wol_conf_set_private(vtss_state_t   *vtss_state, const vtss_port_no_t port_no)
{
    vtss_phy_wol_conf_t    *wol_conf = &vtss_state->phy_state[port_no].wol_conf;
    vtss_rc                 rc = VTSS_RC_OK;
    u16 regVal;

    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));

    // WOL MAC Addr; Setup Reg 21E2, 22E2, and 23E2
    regVal = wol_conf->wol_mac.addr[1] << 8;
    regVal |= wol_conf->wol_mac.addr[0];
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_LOWER_MAC_ADDR, regVal));

    regVal = wol_conf->wol_mac.addr[3] << 8;
    regVal |= wol_conf->wol_mac.addr[2];
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_MID_MAC_ADDR, regVal));

    regVal = wol_conf->wol_mac.addr[5] << 8;
    regVal |= wol_conf->wol_mac.addr[4];
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_UPPER_MAC_ADDR, regVal));

    // Default = 0 or Disabled; Setup Reg 24E2, 25E2, and 26E2
    if (wol_conf->secure_on_enable) {
        // WOL Secure-ON Password
        regVal = wol_conf->wol_pass.passwd[1] << 8;
        regVal |= wol_conf->wol_pass.passwd[0];
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_LOWER_PASSWD, regVal));

        regVal = wol_conf->wol_pass.passwd[3] << 8;
        regVal |= wol_conf->wol_pass.passwd[2];
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_MID_PASSWD, regVal));

        if (wol_conf->wol_passwd_len == VTSS_WOL_PASSWD_LEN_4) {
            regVal = 0;
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_UPPER_PASSWD, regVal));
        } else {
            regVal = wol_conf->wol_pass.passwd[5] << 8;
            regVal |= wol_conf->wol_pass.passwd[4];
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_UPPER_PASSWD, regVal));
        }
    } else {
        regVal = 0;
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_LOWER_PASSWD, regVal));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_MID_PASSWD, regVal));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_UPPER_PASSWD, regVal));
    }

    // Default = 0 or Disabled; Setup Reg 27E2
    regVal = 0;
    if (wol_conf->secure_on_enable) {
        regVal |= VTSS_PHY_WOL_CONTROL_SECURE_ON_ENABLE;
    }

    // Default = 0 or 6 bytes
    if (wol_conf->wol_passwd_len == VTSS_WOL_PASSWD_LEN_4) {
        regVal |= VTSS_PHY_WOL_CONTROL_SECURE_ON_PASSWD_LEN_4;
    }

    // Magic Pkt Count Ranges from 1 to 16
    if (wol_conf->magic_pkt_cnt > 16) {
        wol_conf->magic_pkt_cnt = 16;
    }

    // Default Value is 16, So if it is left blank or 0,
    // Assume the default value of 16; Valid Range is: 1-16
    if (wol_conf->magic_pkt_cnt == 0) {
        wol_conf->magic_pkt_cnt = 16;
    }

    regVal |= (wol_conf->magic_pkt_cnt - 1) << 8;

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_WOL_CONTROL, regVal));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return (rc);
}

// Returns if a port is WoL capable
BOOL vtss_phy_port_wol_capable(vtss_state_t  *vtss_state, const vtss_port_no_t  port_no)
{
    BOOL         wol_capable;

    wol_capable = vtss_phy_can(vtss_state, port_no, VTSS_CAP_WOL);
    //printf("WoL Capable: 0x%x, port_no:%d \n", wol_capable, port_no);

    return (wol_capable);
}

// Enable-disable WOL by enabling or disabling the interrupt
vtss_rc vtss_phy_wol_enable(const vtss_inst_t           inst,
                            const vtss_port_no_t        port_no,
                            const BOOL                  enable)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;
    u16          mask = 0;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_phy_port_wol_capable(vtss_state, port_no)) {
            if (enable) {
                vtss_state->phy_state[port_no].int_mask_reg |= VTSS_F_PHY_INTERRUPT_MASK_WAKE_ON_LAN_MASK;
            } else {
                vtss_state->phy_state[port_no].int_mask_reg &= ~VTSS_F_PHY_INTERRUPT_MASK_WAKE_ON_LAN_MASK;
            }
            mask = vtss_state->phy_state[port_no].int_mask_reg;
            rc = VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_INTERRUPT_MASK, mask, mask);
        } else {
            VTSS_N("Not WoL Capable: port_no:%d ps->features:0x%X WoL=0x%x", port_no, vtss_state->phy_state[port_no].features, VTSS_CAP_WOL);
        }
    }
    VTSS_EXIT();
    return rc;
}


// Get the WOL config
vtss_rc vtss_phy_wol_conf_get(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              vtss_phy_wol_conf_t   *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    if (conf == NULL) {
        return rc;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_phy_port_wol_capable(vtss_state, port_no)) {
            rc = vtss_phy_wol_conf_get_private(vtss_state, port_no, conf);
            //*conf = vtss_state->phy_state[port_no].wol_conf;
        }
    }
    VTSS_EXIT();
    return rc;
}

// Set the WOL config
vtss_rc vtss_phy_wol_conf_set(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              const vtss_phy_wol_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    if (conf == NULL) {
        return rc;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_phy_port_wol_capable(vtss_state, port_no)) {
            vtss_state->phy_state[port_no].wol_conf = *conf;
            rc = vtss_phy_wol_conf_set_private(vtss_state, port_no);
        }
    }
    VTSS_EXIT();
    return rc;
}

// Sequence to Reset LCPLL for the VIPER and ELISE PHY
// Note: This would occur PRIOR to calling PHY pre-reset(), reset(), and post-reset() functions
// Therefore, the phy_id base_port_no will not be valid.
// The Calling application must know the PHY Base Port number.
static vtss_rc vtss_phy_pll5g_reset(vtss_state_t                *vtss_state,
                                    const vtss_port_no_t         port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
//    BOOL viper_rev_a = FALSE;
    u8 dis_fsm;
    u8 ena_clk_bypass;

    if (vtss_state->sync_calling_private) {
        VTSS_I("vtss_phy_pll5g_reset: Skipping LCPLL Reset, Not Valid during warmstart Port: %d", port_no);
        return VTSS_RC_OK; // Skipping warm start register check because the same registers are writing multiple times with different values.
    }

    VTSS_D("Entering: vtss_phy_pll5g_reset: Port: %d", port_no);

    switch (ps->family) {
    // These chips support the LCPLL macro setup
    case VTSS_PHY_FAMILY_VIPER:
//        viper_rev_a = (ps->type.revision == VTSS_PHY_VIPER_REV_A);

        /* fall-through */
    // Fall through on purpose
    case VTSS_PHY_FAMILY_ELISE:
        break;

    default:
        return VTSS_RC_OK;
    }

    VTSS_D("ReSetting LCPLL");
    // Note: This will be called PRIOR to Phy_Pre_Reset, therefore, we the phy_id base_port_no
    // will not be valid.
    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, port_no, 0x11, 0)); // read LCPLL MCB into CSRs
    dis_fsm = 1;
    ena_clk_bypass = 0;
    // Reset LCPLL
    VTSS_RC(vtss_phy_pll5g_cfg2_wr_private(vtss_state, port_no, dis_fsm, ena_clk_bypass)); // pll5g_cfg2
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, port_no, 0x11, 0)); // write back LCPLL MCB

    // Delay
    MEPA_MSLEEP(10); // 10msec sleep while LCPLL is held in reset

    VTSS_RC(vtss_phy_mcb_rd_trig_private(vtss_state, port_no, 0x11, 0)); // read LCPLL MCB into CSRs
    dis_fsm = 0;
    ena_clk_bypass = 0;
    // Release the Reset of LCPLL
    VTSS_RC(vtss_phy_pll5g_cfg2_wr_private(vtss_state, port_no, dis_fsm, ena_clk_bypass)); // pll5g_cfg2
    VTSS_RC(vtss_phy_mcb_wr_trig_private(vtss_state, port_no, 0x11, 0)); // write back LCPLL MCB

    VTSS_D("vtss_phy_pll5g_reset: Port: %d  LCPLL Reset Complete", port_no);

    return VTSS_RC_OK;
}

// Sequence to Reset LCPLL for the PHY
// Note: This would occur PRIOR to calling PHY pre-reset(), reset(), and post-reset() functions
// The Calling application must know the PHY Base Port number.
static vtss_rc vtss_phy_reset_lcpll_private(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16             reg_val = 0;
    vtss_rc         rc = VTSS_RC_OK;
    vtss_port_no_t  chip_port_no = 0;
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    // Get the chip physical port number, if it is 0, then it is the base port.
    chip_port_no = vtss_phy_chip_port(vtss_state, port_no);
    if (chip_port_no != 0) {
        return (VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND);
    }

    if (vtss_state->sync_calling_private) {
        VTSS_I("vtss_phy_reset_lcpll_private: Skipping LCPLL Reset, Not Valid during warmstart Port: %d", port_no);
        return VTSS_RC_OK;
    }

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
        VTSS_I("vtss_phy_reset_lcpll_private: Skipping LCPLL Reset, Not Valid for ATOM FAMILY Port: %d", port_no);
        return (rc);
        break;

    case VTSS_PHY_FAMILY_TESLA:
        VTSS_I("vtss_phy_reset_lcpll_private: TESLA LCPLL Reset, Port: %d \n", port_no);
        rc = VTSS_RC_OK;
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8023));  // Read LCPLL Config Vector into PRAM
        (void)  vtss_phy_wait_for_micro_complete(vtss_state, port_no);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0xd7d5));  // Set Address to Poke
        (void)  vtss_phy_wait_for_micro_complete(vtss_state, port_no);

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8d06));  // Poke to Reset PLL Startup State Machine, set disable_fsm:bit 119
        (void)(vtss_phy_wait_for_micro_complete(vtss_state, port_no));


        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80c0));  // Rewrite PLL Config Vector
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        MEPA_MSLEEP(10); // 10msec sleep

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8506));  // Poke to De-Assert Reset of PLL State Machine, clear disable_fsm:bit 119
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));       // Switch back to micro/GPIO register-page
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x80c0));  // Rewrite PLL Config Vector
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));

        MEPA_MSLEEP(10); // 10msec sleep

        VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_SERDES_STATUS, &reg_val));

        VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MAC_SERDES_STATUS, &reg_val));
        break;

    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
        VTSS_I("vtss_phy_reset_lcpll_private: VIPER LCPLL Reset, Port: %d \n", port_no);
        VTSS_RC(vtss_phy_pll5g_reset(vtss_state, port_no));
        break;

    case VTSS_PHY_FAMILY_NANO:
    default:
        VTSS_I("vtss_phy_reset_lcpll_private: Skipping LCPLL Reset, Not Valid for PHY FAMILY Port: %d", port_no);
        return (rc);
        break;
    }

    MEPA_MSLEEP(110); // 110msec sleep to allow re-calibration of LCPLL

    return (rc);
}

// Reset LCPLL for the PHY
// Note: This would occur PRIOR to calling PHY pre-reset(), reset(), and post-reset() functions
// To get the PHY Type and Family, we must call phy_detect first.i
// The PHY base port_no is not known until the phy_post_reset() function is called so the calling
// Application needs to know the base_port of the PHY. The chip_port_no is checked to see if it is the base_port_no.
vtss_rc vtss_phy_reset_lcpll(const vtss_inst_t           inst,
                             const vtss_port_no_t        port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_reset_lcpll port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);

        if (rc == VTSS_RC_OK) {
            rc = VTSS_RC_COLD(vtss_phy_reset_lcpll_private(vtss_state, port_no));
        }
    }
    VTSS_EXIT();


    return rc;
}

vtss_rc vtss_phy_sd6g_ob_post_rd(vtss_inst_t          inst,
                                 const vtss_port_no_t port_no,
                                 u8                  *ob_post0,
                                 u8                  *ob_post1)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        u32  csr_reg = 0x28;    // ob_cfg;
        u32  csr_reg_val = 0;
        *ob_post0 = 0;
        *ob_post1 = 0;

        rc = vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, csr_reg, &csr_reg_val);
        if (rc == VTSS_RC_OK) {
            *ob_post0 = (csr_reg_val & 0x1f800000) >> 23;   /* bits 28:23 */
            *ob_post1 = (csr_reg_val & 0x007c0000) >> 18;   /* bits 18:22 */
        }
#endif
    }
    VTSS_EXIT();

    return rc;
}


vtss_rc vtss_phy_sd6g_ob_post_wr(vtss_inst_t          inst,
                                 const vtss_port_no_t port_no,
                                 const u8             ob_post0,
                                 const u8             ob_post1)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        rc = vtss_phy_sd6g_ob_post_wr_private(vtss_state, port_no, ob_post0, ob_post1);
#endif
    }
    VTSS_EXIT();

    return rc;
}


vtss_rc vtss_phy_sd6g_ob_lev_rd(vtss_inst_t          inst,
                                const vtss_port_no_t port_no,
                                u8                  *ob_level)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        u32  csr_reg = 0x29;    // ob_cfg1;
        u32  csr_reg_val = 0;
        *ob_level = 0;

        rc = vtss_phy_sd6g_csr_reg_rd_dbg_private(vtss_state, port_no, csr_reg, &csr_reg_val);
        if (rc == VTSS_RC_OK) {
            *ob_level = csr_reg_val & 0x0000003f;   /* bits 5:0 */
        }
#endif
    }
    VTSS_EXIT();

    return rc;
}


vtss_rc vtss_phy_sd6g_ob_lev_wr(vtss_inst_t          inst,
                                const vtss_port_no_t port_no,
                                const u8             ob_level)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        rc = vtss_phy_sd6g_ob_lev_wr_private(vtss_state, port_no, ob_level);
#endif
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_phy_mac_media_inhibit_odd_start(vtss_inst_t          inst,
                                             const vtss_port_no_t port_no,
                                             const BOOL           mac_inhibit,
                                             const BOOL           media_inhibit)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_mac_media_inhibit_odd_start_private(vtss_state, port_no, mac_inhibit, media_inhibit);
    }
    VTSS_EXIT();

    return rc;
}

static vtss_rc vtss_phy_fefi_get_private(vtss_state_t             *vtss_state,
                                         const vtss_port_no_t      port_no,
                                         vtss_fefi_mode_t         *fefi_conf)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc                rc = VTSS_RC_OK;
    u16                    regVal = 0;

    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
        break;
    default:
        *fefi_conf = 0;
        return (VTSS_RC_OK);
    }


    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
    // WOL MAC Addr
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_CONTROL, &regVal));

    /* Read Reg23E3 and Decode bits 0 and 1. */
    if (regVal & VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_FEFI) {
        if (regVal & VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FEFI_FORCE_VALUE) {
            *fefi_conf = VTSS_100FX_FEFI_FORCE_ENABLE;     /**< Force FEFI, Reg23E3.1 = 1; Reg23E3.0 = 1  */
        } else {
            *fefi_conf = VTSS_100FX_FEFI_FORCE_SUPPRESS;   /**< Force FEFI, Reg23E3.1 = 1; Reg23E3.0 = 0  */
        }
    } else {
        *fefi_conf = VTSS_100FX_FEFI_NORMAL;  /**< Normal FEFI Operation, Reg23E3.1 = 0 */
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return (rc);
}

static vtss_rc vtss_phy_fefi_set_private(vtss_state_t             *vtss_state,
                                         const vtss_port_no_t      port_no,
                                         const vtss_fefi_mode_t    fefi_conf)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc                rc = VTSS_RC_OK;
    u16 regVal;


    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
        break;
    default:
        return (VTSS_RC_OK);
    }

    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
    // WOL MAC Addr
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_CONTROL, &regVal));

    switch (fefi_conf) {
    case VTSS_100FX_FEFI_NORMAL:             /**< Normal FEFI Operation, Reg23E3.1 = 0, Reg23E3.0 = 0 */
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_CONTROL, 0,
                                        (VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_FEFI |
                                         VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FEFI_FORCE_VALUE) ));

        ps->setup.media_if_pcs.force_fefi = 0;
        ps->setup.media_if_pcs.force_fefi_value = 0;
        break;

    case VTSS_100FX_FEFI_FORCE_SUPPRESS:     /**< Force FEFI Operation, Reg23E3.1 = 1, Reg23E3.0 = 0 */
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_CONTROL,
                                        VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_FEFI,
                                        (VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_FEFI |
                                         VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FEFI_FORCE_VALUE) ));

        ps->setup.media_if_pcs.force_fefi = 1;
        ps->setup.media_if_pcs.force_fefi_value = 0;
        break;

    case VTSS_100FX_FEFI_FORCE_ENABLE:       /**< Force FEFI Operation, Reg23E3.1 = 1, Reg23E3.0 = 1 */
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_CONTROL,
                                        (VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_FEFI |
                                         VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FEFI_FORCE_VALUE),
                                        (VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_FEFI |
                                         VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FEFI_FORCE_VALUE) ));

        ps->setup.media_if_pcs.force_fefi = 1;
        ps->setup.media_if_pcs.force_fefi_value = 1;
        break;

    default:    /* Default it to Normal Mode, ie. AUTO - No Force */
        VTSS_RC(VTSS_PHY_WARM_WR_MASKED(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_CONTROL, 0,
                                        (VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_FEFI |
                                         VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FEFI_FORCE_VALUE) ));

        ps->setup.media_if_pcs.force_fefi = 0;
        ps->setup.media_if_pcs.force_fefi_value = 0;
        break;
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return (rc);
}

static vtss_rc vtss_phy_fefi_detect_private(vtss_state_t             *vtss_state,
                                            const vtss_port_no_t      port_no,
                                            BOOL                     *fefi_detect)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc                rc = VTSS_RC_OK;
    u16 regVal;

    switch (ps->family) {
    case VTSS_PHY_FAMILY_VIPER:
        break;
    default:
        *fefi_detect = FALSE;
        return (VTSS_RC_OK);
    }

    // EXT PAGE 3
    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
    // Read Reg27E3 to get FEFI Status
    *fefi_detect = FALSE;
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_STATUS, &regVal));
    if (regVal & VTSS_F_PHY_MEDIA_SERDES_STATUS_100FX_FEFI_DETECT) {
        *fefi_detect = TRUE;
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return (rc);
}

vtss_rc vtss_phy_fefi_get(vtss_inst_t             inst,
                          const vtss_port_no_t    port_no,
                          vtss_fefi_mode_t       *fefi)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_fefi_get_private(vtss_state, port_no, fefi);
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_phy_fefi_set(vtss_inst_t               inst,
                          const vtss_port_no_t      port_no,
                          vtss_fefi_mode_t          fefi)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_fefi_set_private(vtss_state, port_no, fefi);
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_phy_fefi_detect(vtss_inst_t              inst,
                             const vtss_port_no_t     port_no,
                             BOOL                    *fefi_detect)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_fefi_detect_private(vtss_state, port_no, fefi_detect);
    }
    VTSS_EXIT();

    return rc;
}

/* compute the Mean Squared Error for a given Channel */
/* Need Floating Point or Double Precision and API does not have float MathLib  */
/* *chan_Mse = *chan_Mse / (1024 * 2048);     2^21 = 1024 * 2048 */
/* *chan_Mse = 20 * log10(*chan_Mse);         Convert to dB      */
static vtss_rc vtss_phy_chan_mse_get_private(vtss_state_t             *vtss_state,
                                             const vtss_port_no_t      port_no,
                                             vtss_phy_channel_t        chan,
                                             u32                      *chan_Mse)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    vtss_rc                rc = VTSS_RC_OK;
    u16 regVal16;
    u16 reg17;
    u16 reg18;

    /* 65nm PHY Families */
    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
    case VTSS_PHY_FAMILY_TESLA:
    case VTSS_PHY_FAMILY_VIPER:
    case VTSS_PHY_FAMILY_ELISE:
    case VTSS_PHY_FAMILY_NANO :
        break;
    default:
        return (VTSS_RC_OK);
    }

    /* Map Chan to Addr */
    switch (chan) {
    case VTSS_PHY_CHAN_A:
        regVal16 = 0xa3d0;
        break;
    case VTSS_PHY_CHAN_B:
        regVal16 = 0xa3d2;
        break;
    case VTSS_PHY_CHAN_C:
        regVal16 = 0xa3d4;
        break;
    case VTSS_PHY_CHAN_D:
        regVal16 = 0xa3d6;
        break;
    default:
        return VTSS_RC_ERROR;
        break;
    }

    // TR PAGE 0x52b5
    /*- Read MSE for given Channel A, B, C, D */
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, regVal16));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    *chan_Mse = (reg18 & 0x007f);
    *chan_Mse = *chan_Mse << 16;
    *chan_Mse |= (reg17 & 0xffff);

    return (rc);
}

/* API Function to retrieve the Mean Squared Error for a ChannelA (100m) */
/* Need Floating Point or Double Precision and API does not have float MathLib  */
/* *chan_Mse = *chan_Mse / (1024 * 2048);     2^21 = 1024 * 2048  */
/* *chan_Mse = 20 * log10(*chan_Mse);         Convert to dB       */
/*      Nominal Result Values are in the Range of -22dB to -31dB  */
vtss_rc vtss_phy_mse_100m_get(vtss_inst_t              inst,
                              const vtss_port_no_t     port_no,
                              u32                     *chanA_mse)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_chan_mse_get_private(vtss_state, port_no, VTSS_PHY_CHAN_A, chanA_mse);
    }
    VTSS_EXIT();

    return rc;
}

/* API Function to retrieve the Mean Squared Error for a Channels A;B;C;D  (1000m) */
/* Need Floating Point or Double Precision and API does not have float MathLib  */
/* *chan_Mse = *chan_Mse / (1024 * 2048);     2^21 = 1024 * 2048  */
/* *chan_Mse = 20 * log10(*chan_Mse);         Convert to dB       */
/*      Nominal Result Values are in the Range of -22dB to -31dB  */
vtss_rc vtss_phy_mse_1000m_get(vtss_inst_t              inst,
                               const vtss_port_no_t     port_no,
                               u32                     *chanA_mse,
                               u32                     *chanB_mse,
                               u32                     *chanC_mse,
                               u32                     *chanD_mse)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if ((rc = vtss_phy_chan_mse_get_private(vtss_state, port_no, VTSS_PHY_CHAN_A, chanA_mse)) == VTSS_RC_OK) {
            if ((rc = vtss_phy_chan_mse_get_private(vtss_state, port_no, VTSS_PHY_CHAN_B, chanB_mse)) == VTSS_RC_OK) {
                if ((rc = vtss_phy_chan_mse_get_private(vtss_state, port_no, VTSS_PHY_CHAN_C, chanC_mse)) == VTSS_RC_OK) {
                    rc = vtss_phy_chan_mse_get_private(vtss_state, port_no, VTSS_PHY_CHAN_D, chanD_mse);
                }
            }
        }
    }
    VTSS_EXIT();

    return rc;
}


static vtss_rc vtss_phy_read_tr_addr_private(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 reg16, u16 *reg17, u16 *reg18)
{
    vtss_rc  rc = VTSS_RC_OK;

    reg16 |= 0x2000;
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, reg18));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, reg17));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return rc;
}

/* API Debug Function to retrieve the values from Token Ring  */
vtss_rc vtss_phy_read_tr_addr(vtss_inst_t              inst,
                              const vtss_port_no_t     port_no,
                              u16                      tr_addr,
                              u16                     *tr_lower,
                              u16                     *tr_upper)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_read_tr_addr_private(vtss_state, port_no, tr_addr, tr_lower, tr_upper);
    }
    VTSS_EXIT();

    return rc;
}

/*
 * API to get clause37 link partner's ability
 */
vtss_rc vtss_phy_cl37_lp_abil_get(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  vtss_port_status_t   *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_cl37_lp_abil_get_private(vtss_state, port_no, status);
    }
    VTSS_EXIT();
    return rc;
}


vtss_rc vtss_phy_is_viper_revB(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               BOOL                  *is_viper_revB)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;
    *is_viper_revB = FALSE;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if ((vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_VIPER) &&
            (vtss_state->phy_state[port_no].type.revision == VTSS_PHY_VIPER_REV_B)) {
            *is_viper_revB = TRUE;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_phy_serdes6g_rcpll_status_get(const vtss_inst_t    inst,
                                           const vtss_port_no_t port_no,
                                           vtss_rcpll_status_t  *status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_serdes6g_rcpll_status_get port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);

        if (rc == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
            rc = VTSS_RC_COLD(vtss_phy_serdes6g_rcpll_status_get_private(vtss_state, port_no, status));
#else
        VTSS_E("vtss_phy_serdes6g_rcpll_status_get NOT  compiled into build!  port_no:%d", port_no);
#endif
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_phy_serdes1g_rcpll_status_get(const vtss_inst_t    inst,
                                           const vtss_port_no_t port_no,
                                           vtss_rcpll_status_t  *status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_serdes1g_rcpll_status_get port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);

        if (rc == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
            rc = VTSS_RC_COLD(vtss_phy_serdes1g_rcpll_status_get_private(vtss_state, port_no, status));
#else
            VTSS_E("vtss_phy_serdes1g_rcpll_status_get NOT  compiled into build!  port_no:%d", port_no);
#endif
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_phy_lcpll_status_get(const vtss_inst_t    inst,
                                  const vtss_port_no_t port_no,
                                  vtss_lcpll_status_t  *status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_lcpll_status_get port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);

        if (rc == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
            rc = VTSS_RC_COLD(vtss_phy_lcpll_status_get_private(vtss_state, port_no, status));
#else
            VTSS_E("vtss_phy_lcpll_status_get  NOT  compiled into build!  port_no:%d", port_no);
#endif
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_phy_macsec_csr_sd6g_rd(vtss_inst_t          inst,
                                    const vtss_port_no_t port_no,
                                    const u16            target,
                                    const u32            csr_reg_addr,
                                    u32                  *value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_RC(vtss_phy_macsec_csr_rd_private(vtss_state, port_no, target, csr_reg_addr, value));
    }

    return (rc);
}

vtss_rc vtss_phy_macsec_csr_sd6g_wr(vtss_inst_t          inst,
                                    const vtss_port_no_t port_no,
                                    const u16            target,
                                    const u32            csr_reg_addr,
                                    u32                  value)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_OK;
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        VTSS_RC(vtss_phy_macsec_csr_wr_private(vtss_state, port_no, target, csr_reg_addr, value));
    }

    return (rc);
}

/* Keep this function for debug, if any issue find */
vtss_rc vtss_phy_debug_tr_reg_read_print_priv(vtss_state_t             *vtss_state,
                                              const vtss_port_no_t      port_no,
                                              const u16                 tr_addr,
                                              u16                      *tr_reg17,
                                              u16                      *tr_reg18)
{
    u16          reg16 = 0;

    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));

    reg16 = tr_addr | 0xa000; /* Setup the Tr Read */
    VTSS_RC(VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, tr_reg18));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, tr_reg17));
    printf("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, *tr_reg18, *tr_reg17);

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return VTSS_RC_OK;
}


#if DEBUG_TOKEN_RING_REGDUMP_EN
/* Keep this function for debug, if any issue find */
vtss_rc vtss_phy_debug_tr_regdump_print(vtss_state_t *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const vtss_port_no_t      port_no,
                                        const BOOL                print_hdr)
{
    vtss_rc rc = VTSS_RC_OK;
    u16          addr = 0;
    u16          reg16 = 0;
    u16          reg17 = 0;
    u16          reg18 = 0;


    if (print_hdr) {
        pr("%-5s %-5s %-14s %-10s \n", "Port", "Addr", "      Reg18    ", "     Reg17  ");
        pr("%-5s %-5s %-14s %-10s \n", "----", "----------", "-----------", "---------");
    }

    rc = vtss_phy_page_tr(vtss_state, port_no);

    addr = 0x0486;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x0488;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x048a;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x07f8;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x07fa;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x07fe;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x0796;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x03a4;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x1688;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x0fc0;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x0f90;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);
    addr = 0x0fe4;
    reg16 = addr | 0xa000;
    VTSS_PHY_WARM_WR(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, reg16);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg18);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg17);
    pr("%4d Addr:0x%04x  Reg18:0x%04x   Reg17:0x%04x \n", port_no, reg16, reg18, reg17);

    rc = vtss_phy_page_test(vtss_state, port_no);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_5, &reg17);
    PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, &reg18);
    pr("%4d Page:TEST    Reg05:0x%04x   Reg24:0x%04x \n", port_no, reg17, reg18);

    rc = vtss_phy_page_std(vtss_state, port_no);
    return rc;
}
#endif /* End of DEBUG_TOKEN_RING_REGDUMP_EN */

#if defined(VTSS_FEATURE_MACSEC) && defined(KAT_TEST_ENABLE_1G)

/* **************************************************************** */
/*            Configuring EPG for MACSEC Known Answer Test (KAT)    */
/* **************************************************************** */
// Configure EPG to send KAT Frames - Ttl = 300Pkts;
// (64 or 125 byte) Pkts (ETH-IPv4-UDP) - Pattern = 0x0000
static vtss_rc vtss_phy_epg_gen_kat_frame_private(vtss_state_t *vtss_state, const vtss_port_no_t  port_no, const BOOL match)
{
    vtss_rc            rc = VTSS_RC_OK;
    u16                pkt_sz = 125;
    u16                value = 0;
    u16                value1 = 0;
    u16                reg28e = 0;
    u16                reg29e = 0;
    u16                reg30e = 0;
    u16                index = 0;
    u8                 loop_cnt = 2;
    vtss_phy_type_t    phy_id;
    BOOL               enable_mac_counter = FALSE;
    u16                tr_reg17 = 0;
    u16                tr_reg18 = 0;

    /* Clear Counters */
    VTSS_I("Configure EPG to send 300 Packets  \n");
    phy_id = vtss_state->phy_state[port_no].type;

   /* Clear Counters 21E3 Tx Good Pkt Counters and 22E3 Tx CRC Counters by reading them */
    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, &value1));   /* Read 22E3 to clear Counter  */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER, &value)); /* Read 21E3 to clear Counter  */
    if (value1 & (1 << 14)) {
        VTSS_I("MAC SerDes Tx CRC Counters Reg_22E3: 0x%x  \n", value1);
        VTSS_I("MAC SerDes Tx Good Counters Reg_21E3: 0x%x  \n", value);
    } else {
        VTSS_I("Media SerDes Tx CRC Counters Reg_22E3: 0x%x  \n", value1);
        VTSS_I("Media SerDes Tx Good Counters Reg_21E3: 0x%x  \n", value);
    }
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER, &value1));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER, &value));
    if (value1 & (1 << 14)) {
        VTSS_I("MAC SerDes Rx CRC Counters Reg_29E3: 0x%x  \n", value1);
        VTSS_I("MAC SerDes Rx Good Counters Reg_28E3: 0x%x  \n", value);
    } else {
        VTSS_I("Media SerDes Rx CRC Counters Reg_29E3: 0x%x  \n", value1);
        VTSS_I("Media SerDes Rx Good Counters Reg_28E3: 0x%x  \n", value);
    }

    /* Select Fiber Media or MAC SerDes */
   value &= 0x3fff;  /*  Clear Selects Fiber Media SerDes Tx Counters */
    if (enable_mac_counter) {
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, &value));   /* Read 22E3 to clear Counter  */
        /* Reg22E3.15:14 :: 0 = Fiber Media; 01 = Selects MAC SerDes Tx Counters */
        value |= VTSS_F_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_TX_SELECT(1);
        /* Read Reg22E3 Tx Media SerDes CRC Error Counter to clear Counter  */
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, value));
        VTSS_D("Updating to Select MAC SerDes Tx CRC Counters Reg_22E3: 0x%x  \n", value);
        //printf("Updating to Select MAC SerDes Tx CRC Counters Reg_22E3: 0x%x  \n", value);
        /* Read Reg29E3, the SerDes Rx CRC Error Counters to clear them */
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER, &value1));
        /* Reg29E3.15:14 :: 0 = Fiber Media; 01 = Selects MAC SerDes Tx Counters */
        value1 |= VTSS_F_PHY_MEDIA_MAC_SERDES_RX_CRC_ERR_COUNTER_RX_SELECT(1);
        /* Write 29E3 to Setup MAC SerDes Counter  */
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER, value1));
        VTSS_D("Updating to Select MAC SerDes Rx CRC Counters Reg_29E3: 0x%x  \n", value1);
        //printf("Updating to Select MAC SerDes Rx CRC Counters Reg_29E3: 0x%x  \n", value1);

        /* Read Reg22E the Tx SerDes Tx Counters to clear them */
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, &value1));
        VTSS_D("22E3: VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, 0x%x  \n", value1);
        //printf("22E3: VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, 0x%x  \n", value1);
        /* Read 21E3 to clear Counter  */
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER, &value));
        VTSS_D("21E3: VTSS_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER: 0x%x  \n", value);
        //printf("21E3: VTSS_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER: 0x%x  \n", value);
        /* Read Reg29E3, the SerDes Rx CRC Error Counters to clear them */
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER, &value1));
        VTSS_D("29E3: VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER: 0x%x  \n", value1);
        //printf("29E3: VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER: 0x%x  \n", value1);
        /* Read Reg28E3, the SerDes Rx Good Counters to clear them */
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER, &value));
        VTSS_D("28E3: VTSS_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER: 0x%x  \n", value1);
        //printf("28E3: VTSS_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER: 0x%x  \n", value1);
    }
    /* Setup TR EPG Registers for IPv4-UDP Protocol */
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, VTSS_PHY_TR_EPG_ADDR_RD)); /* Read in Data */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &tr_reg18)); /* Read upper 16 */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &tr_reg17)); /* Read lower 16 */
    tr_reg18 &= 0xfffc;     /* Reg18.15:8; Clear */
    tr_reg18 |= 0x3;        /* Reg18.1:0   Set EPG_IP_ENABLE=1 and EPG_TESTMODE=1 (Test Mode means Tx only 300pkts) */
    tr_reg17 &= 0x00ff;     /* Reg17.15:8; Clear EPG_IP_Protocol */
    tr_reg17 |= 0x11 << 8;  /* Reg17.15:8; Set EPG_IP_Protocol = 0x11 (17) for UDP Protocol */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, tr_reg18)); /* Write upper 16 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, tr_reg17)); /* Write lower 16 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, VTSS_PHY_TR_EPG_ADDR_WR)); /* Write Data Out */
    VTSS_I("Config TR::EPG - IP_ENABLE=1; TESTMODE=1; IP_PROTCOL=UDP for PTP TR_Reg16: 0x%04x,  TR_Reg17:0x%04x, TR_Reg18: 0x%04x\n",
            VTSS_PHY_TR_EPG_ADDR_WR, tr_reg17, tr_reg18);
    //printf("Config TR::EPG - IP_ENABLE=1; TESTMODE=1; IP_PROTCOL=UDP for PTP TR_Reg16: 0x%04x,  TR_Reg17:0x%04x, TR_Reg18: 0x%04x\n", VTSS_PHY_TR_EPG_ADDR_WR, tr_reg17, tr_reg18);

    /* Reg28E1.3:0 = 0=EPG Payload Data; 1=EtherType/UDP Dest Port; 2=Signature Counter; 3=IPG Override value; 4=EPG Pkt Len Override */
    /* Reg28E1.3:0 = 1=EtherType/UDP Dest Port */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, &reg28e));   /* Read 28E1 to Select Index  */
    reg28e |= VTSS_F_PHY_EXT_28_ETYPE_UDPDEST_OV_ENA;  /* 28E1.4: 1=EtherType/UDP Dest Port;  */

    index = 1;
    reg28e &= ~VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX;  /* Clear the Index Field */
    reg28e |= VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(index);   /* Write 28E1 to Select bits_3:0=Index = 0;  bit4:1=EtherType/UDP Dest Port;  */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg28e));    /* Write 28E1 to Select UDP Dport */

    if (match) {
        reg30e = 319;   /* 0x013F */
    } else {
        reg30e = 320;   /* 0x0140 */
    }
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, reg30e));     /* Write 30E1 to Select UDP Dport=319  */
    VTSS_D("Configure EPG to send PTP Packets (UDP)-Pattern:0x0000  \n");
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, &reg28e));   /* Read 28E1 to Select Index  */
    index = 0;
    reg28e &= ~VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX; /* Clear the Index Field */
    reg28e |= VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(index);   /* Write 28E1 to Select bits_3:0=Index = 0;  bit4:1=EtherType/UDP Dest Port;  */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg28e));    /* Write 28E1 to Select UDP Dport */
    reg30e = 0x0;   /* 0x0 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, reg30e));     /* Write 30E1 to Select UDP Pattern=0  */
    VTSS_I("Config of EPG done  \n");
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    index = 0;
    reg28e &= ~VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX;  /* Clear the Index Field */
    reg28e |= VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(index);   /* Write 28E1 to Select bits_3:0=Index = 0;  bit4:1=EtherType/UDP Dest Port;  */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg28e));    /* Write 28E1 to Select UDP Dport */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, &reg30e));   /* Read 30E1  */
    VTSS_I("Reading EPG Config: port_no: %d,  Index: 0x%x,  Reg28E1_Value: 0x%04x  Reg30E1_Value: 0x%04x\n", port_no, index, reg28e, reg30e);

    index = 1;
    reg28e &= ~VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX;   /* Clear the Index Field */
    reg28e |= VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(index);   /* Write 28E1 to Select bits_3:0=Index = 0;  bit4:1=EtherType/UDP Dest Port;  */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg28e));    /* Write 28E1 to Select UDP Dport */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, &reg30e));   /* Read 30E1  */
    VTSS_I("Reading EPG Config: port_no: %d,  Index: 0x%x,  Reg28E1_Value: 0x%04x  Reg30E1_Value: 0x%04x\n", port_no, index, reg28e, reg30e);

    index = 2;
    reg28e &= ~VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX;   /* Clear the Index Field */
    reg28e |= VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(index);   /* Write 28E1 to Select bits_3:0=Index = 0;  bit4:1=EtherType/UDP Dest Port;  */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg28e));    /* Write 28E1 to Select UDP Dport */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, &reg30e));   /* Read 30E1  */
    VTSS_I("Reading EPG Config: port_no: %d,  Index: 0x%x,  Reg28E1_Value: 0x%04x  Reg30E1_Value: 0x%04x\n", port_no, index, reg28e, reg30e);

    index = 3;
    reg28e &= ~VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX;   /* Clear the Index Field */
    reg28e |= VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(index);   /* Write 28E1 to Select bits_3:0=Index = 0;  bit4:1=EtherType/UDP Dest Port;  */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg28e));    /* Write 28E1 to Select UDP Dport */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, &reg30e));   /* Read 30E1  */
    VTSS_I("Reading EPG Config: port_no: %d,  Index: 0x%x,  Reg28E1_Value: 0x%04x  Reg30E1_Value: 0x%04x\n", port_no, index, reg28e, reg30e);

    index = 4;
    reg28e &= ~VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX;   /* Clear the Index Field */
    reg28e |= VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(index);   /* Write 28E1 to Select bits_3:0=Index = 0;  bit4:1=EtherType/UDP Dest Port;  */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg28e));    /* Write 28E1 to Select UDP Dport */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_2, &reg30e));   /* Read 30E1  */
    VTSS_I("Reading EPG Config: port_no: %d,  Index: 0x%x,  Reg28E1_Value: 0x%04x  Reg30E1_Value: 0x%04x\n", port_no, index, reg28e, reg30e);

    /* Return to Index = 0 for Default */
    index = 0;
    reg28e &= ~VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX;  /* Clear the Index Field */
    reg28e |= VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(index);   /* Write 28E1 to Select bits_3:0=Index = 0;  bit4:1=EtherType/UDP Dest Port;  */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXT_28, reg28e));    /* Write 28E1 to Select UDP Dport */

    /*  When using 8051 toggling, 8051 is setting bit 14, the RUN bit.  This is done for Jumbo Frames */
    /*  0x9C40 = EPG Enable, Stop, 10,000 Byte Frames, IPG=8192nsec, Dst=0001, Src=0000, Fixed Payload Pattern, Good FCS */
    /*  0x9840 = EPG Enable, Stop, 10,000 Byte Frames, IPG=96nsec, Dst=0001, Src=0000, Fixed Payload Pattern, Good FCS */
    /*  0xC040 = EPG Enable, Run, 125 Byte Frames, IPG=96nsec, Dst=0001, Src=0000, Fixed Payload Pattern, Good FCS */
    /*  0x8040 = EPG Enable, Stop, 125 Byte Frames, IPG=96nsec, Dst=0001, Src=0000, Fixed Payload Pattern, Good FCS */
    /*  0xE840 = EPG Enable, Run, 64 Byte Frames, IPG=96nsec, Dst=0001, Src=0000, Fixed Payload Pattern, Good FCS */
   if (pkt_sz == 64) {
        VTSS_I("Configure EPG to send 300 x 64-byte packets, IPG=96ns (UDP) - Pattern = 0x013F - Not Using 8051 \n");
        reg29e = 0x8840;  // Configure, but don't Run 64 byte
    } else if (pkt_sz == 125) {
        VTSS_I("Configure EPG to send 125-byte packets, IPG=96ns (UDP) - Pattern = 0x013F  \n");
        reg29e = 0x8040;  // Configure, but don't Run 125 byte
    } else if (pkt_sz == 1518) {
        VTSS_I("Configure EPG to send 300 x 1518-byte packets, IPG=96ns (UDP) - Pattern = 0x013F - Not Using 8051 \n");
        reg29e = 0x9040;  // Configure, but don't Run 125 byte
    } else if (pkt_sz == 10000) {
        VTSS_I("Configure EPG to send 300 x 10000-byte packets, IPG=96ns (UDP) - Pattern = 0x013F - Not Using 8051 \n");
        reg29e = 0x9840;  // Configure, but don't Run 125 byte
    } else {   // Default to 125 byte packets
        VTSS_I("Configure EPG to send 300 x 125-byte packets, IPG=96ns (UDP) - Pattern = 0x013F - Not Using 8051 \n");
        reg29e = 0x8040;  // Configure, but don't Run 125 byte
    }

    /*  Set the DA and SA based upon the Match Mode for the EPG */
    reg29e |= (VTSS_PHY_EPG_DST_ADDR << 6) | (VTSS_PHY_EPG_SRC_ADDR << 2);

    VTSS_I("Configure DA and SA - Value: 0x%04x  \n", reg29e);
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, reg29e));     /* Write 30E1 to Select UDP Dport=319  */

    VTSS_I("ETH-IP-UDP 125 Byte Pkt Created port_no: %d ", port_no);
    VTSS_I("ETH Dest: 0xff 0xff 0xff 0xff 0xff 0xf1   ETH Src: 0xff 0xff 0xff 0xff 0xff 0xf2 ");
    VTSS_I("ETH Type: 0x0800   IP Hdr: 0x4500  Len:0x006b   IP Protocol: 0x11 ");
    VTSS_I("Chksum: 0x4e2f   Src IP: 0xc0 0xa8 0x76 0x0   Dest IP: 0xc0 0xa8 0x76 0x1 ");
    VTSS_I("UDP Sport: 0x0   UDP Dport: 0x013f    Len: 0x0057   Chksum: 0x0000 ");
    VTSS_I("ff ff ff ff ff f1 ff ff ff ff ff f2 08 00 45 00 "); // Octets: 0-15
    VTSS_I("00 6b 00 00 00 00 ff 11 4e 2f c0 a8 76 00 c0 a8 "); // Octets: 16-31
    if (match) {
        VTSS_I("76 01 00 00 01 3f 00 57 00 00 00 00 00 00 00 00 "); // Octets: 32-47
    } else {
        VTSS_I("76 01 00 00 01 40 00 57 00 00 00 00 00 00 00 00 "); // Octets: 32-47
    }

    printf("ETH-IP-UDP 125 Byte Pkt Created port_no: %d \n", port_no);
    printf("ff ff ff ff ff f1 ff ff ff ff ff f2 08 00 45 00 \n"); // Octets: 0-15
    printf("00 6b 00 00 00 00 ff 11 4e 2f c0 a8 76 00 c0 a8 \n"); // Octets: 16-31
    if (match) {
        printf("76 01 00 00 01 3f 00 57 00 00 00 00 00 00 00 00 \n\n"); // Octets: 32-47
    } else {
        printf("76 01 00 00 01 40 00 57 00 00 00 00 00 00 00 00 \n\n"); // Octets: 32-47
    }

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg29e));     /* Write 30E1 to Select UDP Dport=319  */
    reg29e |= VTSS_F_EPG_CTRL_REG_1_EPG_RUN_STOP;  // Run!!  Bit 14: 1=Run, 0=Stop
    VTSS_I("Running EPG (Setting bit 14): Reg29E1: 0x%x\n", reg29e);
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, reg29e));     /* Write 30E1 to Select UDP Dport=319  */
    /* STOPPING EPG is Not necessary - It stops on it's own after 300 packets and changes the Run/Stop bit to Stop */
    /* However, we need to verify the Run bit is cleared */
    do {
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg29e));     /* Write 30E1 to Select UDP Dport=319  */
        VTSS_I("port_no: %d, Checking EPG for Completion, Reg29E1:0x%04X \n", port_no, reg29e);
        if (!(reg29e & VTSS_F_EPG_CTRL_REG_1_EPG_RUN_STOP)) {   // Bit 14: 1=Run, 0=Stop
            break;
        }
        MEPA_MSLEEP(1);
        loop_cnt--;
    } while (loop_cnt > 0);
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg29e));     /* Write 30E1 to Select UDP Dport=319  */
    reg29e &= ~(VTSS_F_EPG_CTRL_REG_1_EPG_RUN_STOP);   // STOP!!  It should already be Stopped, but just in case, Force Stop!
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, reg29e));     /* Write 30E1 to Select UDP Dport=319  */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg29e));     /* Write 30E1 to Select UDP Dport=319  */
    VTSS_I("Ensuring EPG Stopped (Clearing bit 14): Reg29E1: 0x%x\n", reg29e);

    /* Read Counters 21E3 Tx Good Pkt Counters and 22E3 Tx CRC Counters by reading them */
    VTSS_I("Media SerDes Tx CRC Counters Reg_22E3: 0x%x  \n", value);
    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, &value1));   /* Read 22E3 to clear Counter  */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER, &value)); /* Read 21E3 to clear Counter  */
    if (value1 & (1 << 14)) {
        VTSS_I("MAC SerDes Tx CRC Counters Reg_22E3: 0x%x  \n", value1);
        VTSS_I("MAC SerDes Tx Good Counters Reg_21E3: 0x%x  \n", value);
    } else {
        VTSS_I("Media SerDes Tx CRC Counters Reg_22E3: 0x%x  \n", value1);
        VTSS_I("Media SerDes Tx Good Counters Reg_21E3: 0x%x  \n", value);
    }
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER, &value1));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER, &value));
    if (value1 & (1 << 14)) {
        VTSS_I("MAC SerDes Rx CRC Counters Reg_29E3: 0x%x  \n", value1);
        VTSS_I("MAC SerDes Rx Good Counters Reg_28E3: 0x%x  \n", value);
    } else {
        VTSS_I("Media SerDes Rx CRC Counters Reg_29E3: 0x%x  \n", value1);
        VTSS_I("Media SerDes Rx Good Counters Reg_28E3: 0x%x  \n", value);
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return (rc);
}

vtss_rc vtss_phy_epg_gen_kat_frame( const vtss_inst_t        inst,
                                    const vtss_port_no_t     port_no,
                                    BOOL                     match)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if ((rc = vtss_phy_epg_gen_kat_frame_private (vtss_state, port_no, match)) != VTSS_RC_OK) {
            /* Ensure we return to the Std Page if Error */
            vtss_phy_page_std(vtss_state, port_no);
        }
    }
    VTSS_EXIT();
    return rc;
}

#endif /* VTSS_FEATURE_MACSEC && KAT_TEST_ENABLE_1G */

// Function for configuring/updating the MAC SerDes OB_CNTRL PHY settings.
// In - port_no - Phy port number.
// Out - ob_post0 - ob_post0 value (6 bits: range 0-63)
// Out - ob_post1 - ob_post0 value (5 bits: range 0-31)
// Out - ob_prec  - ob_prec  value (5 bits: range 0-31)
vtss_rc vtss_phy_mac_serdes_ob_cntrl_get(const vtss_inst_t    inst,
                                           const vtss_port_no_t port_no,
                                           u8                  *ob_post0,
                                           u8                  *ob_post1,
                                           u8                  *ob_prec)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;
    u8           mcb_bus = 0;
    u8           cfg_buf[MAX_CFG_BUF_SIZE] = {0};
    u8           stat_buf[MAX_STAT_BUF_SIZE] = {0};

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_mac_serdes_ob_cntrl_get port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        rc = vtss_phy_patch_setttings_get_private(vtss_state, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]);

        if (rc == VTSS_RC_OK) {
            *ob_prec = (cfg_buf[8] & 0xf8) >> 3;
            *ob_post1 = cfg_buf[9] & 0x1f;
            *ob_post0 = ((cfg_buf[10] & 0x07) << 3) | ((cfg_buf[9] & 0xe0) >> 5);
             VTSS_D("Port: %x: MAC SerDes cfg_buf[8]:0x%x, cfg_buf[9]: 0x%x, cfg_buf[10]: 0x%x \n", port_no, cfg_buf[8], cfg_buf[9], cfg_buf[10]);
             VTSS_I("Port: %x: MAC SerDes ob_prec: 0x%x, ob_post1: 0x%x, ob_post0: 0x%x \n", port_no, *ob_prec, *ob_post1, *ob_post0);
        }
#endif
    }
    VTSS_EXIT();

    return rc;
}

// Function for configuring/updating the MAC SerDes OB_CNTRL PHY settings.
// In - port_no - Phy port number.
// In - ob_post0 - ob_post0 value (6 bits: range 0-63)
// In - ob_post1 - ob_post0 value (5 bits: range 0-31)
// In - ob_prec  - ob_prec  value (5 bits: range 0-31)
vtss_rc vtss_phy_mac_serdes_ob_cntrl_set(const vtss_inst_t    inst,
                                           const vtss_port_no_t port_no,
                                           const u8   ob_post0,
                                           const u8   ob_post1,
                                           const u8   ob_prec)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_mac_serdes_ob_cntrl_set port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);

        if (rc == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
            if (vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_TESLA) {
                rc = VTSS_RC_COLD(vtss_phy_tesla_serdes_ob_cntrl_conf_private(vtss_state, port_no, VTSS_PHY_SERDES_INIT_MAC, ob_post0, ob_post1, ob_prec));
            } else {
                VTSS_I("vtss_phy_mac_serdes_ob_cntrl_set NOT SUPPORTED!  port_no:%d", port_no);
            }
#else
            VTSS_E("vtss_phy_mac_serdes_ob_cntrl_set NOT  compiled into build!  port_no:%d", port_no);
#endif
        }
    }
    VTSS_EXIT();

    return rc;
}

// Function for Retrieving the MAC SerDes PRBS PHY settings.
// In - port_no - Phy port number.
// Out - ob_post0 - ob_post0 value (6 bits: range 0-63)
// Out - ob_post1 - ob_post0 value (5 bits: range 0-31)
// Out - ob_prec  - ob_prec  value (5 bits: range 0-31)
//
vtss_rc vtss_phy_serdes_prbs_conf_get (const vtss_inst_t    inst,
                                       const vtss_port_no_t port_no,
                                       u8                  *test_sel,
                                       u8                  *prbs)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;
    u8           mcb_bus = 0;
    u8           cfg_buf[MAX_CFG_BUF_SIZE] = {0};
    u8           stat_buf[MAX_STAT_BUF_SIZE] = {0};

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_serdes_prbs_conf_get port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
        vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
        vtss_phy_reset_conf_t *conf = &ps->reset;

        rc = vtss_phy_patch_setttings_get_private(vtss_state, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]);

        if (rc == VTSS_RC_OK) {
            if (conf->mac_if ==  VTSS_PORT_INTERFACE_QSGMII) {  // QSGMII mapping (these are one macro per quad)
                // bits 286-284  TEST_MODE=BIST
                // bits 288-287  PRBS_SEL=PRBS7
                *prbs = (cfg_buf[36] & 0x1) << 1 | (cfg_buf[35] & 0x80) >> 7 ;
                *test_sel = cfg_buf[35] & 0x70 >> 4;
            } else if (conf->mac_if ==  VTSS_PORT_INTERFACE_SGMII) {  // SGMII mapping (these are four macro per quad)
                // bits 193-192  PRBS_SEL=PRBS7
                // bits 191-189  TEST_MODE=BIST
                *prbs = cfg_buf[24] & 0x3;
                *test_sel = cfg_buf[23] & 0xe0 >> 5;
            }

             VTSS_D("Port: %x: MAC SerDes PRBS: 1G-cfg_buf[24]:0x%x, 6G-cfg_buf[35]: 0x%x cfg_buf[36]: 0x%x \n", port_no, cfg_buf[24], cfg_buf[35], cfg_buf[36]);
             VTSS_D("Port: %x: MAC SerDes Test Mode: 0x%x,   PRBS: 0x%x\n", port_no, *test_sel, *prbs);
        }
#endif
    }
    VTSS_EXIT();

    return rc;
}

// Function to Enable/Disable the SerDes PRBS within the PHY.
// In - port_no - Phy port number.
// In - prbs_ena - PRBS7 Enable  (TRUE=Enable/FALSE=Disable)
vtss_rc vtss_phy_serdes_prbs_conf_set(const vtss_inst_t    inst,
                                      const vtss_port_no_t port_no,
                                      const BOOL           prbs_ena)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc = VTSS_RC_ERROR;

    VTSS_ENTER();
    VTSS_D("Enter vtss_phy_media_serdes_ob_cntrl_set port_no:%d", port_no);
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        /* -- Step 1: Detect PHY type and family -- */
        rc = vtss_phy_detect(vtss_state, port_no);

        // For QSGMII MAC
        // Modify bits 286-284  TEST_MODE=BIST
        // Modify bits 288-287  PRBS_SEL=PRBS7
        // For SGMII MAC
        // Modify bits 193-192  PRBS_SEL=PRBS7
        // Modify bits 191-189  TEST_MODE=BIST

        if (rc == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
            if (vtss_state->phy_state[port_no].family == VTSS_PHY_FAMILY_TESLA) {
                rc = VTSS_RC_COLD(vtss_phy_tesla_serdes_prbs_conf_private(vtss_state, port_no, prbs_ena));
            } else {
                VTSS_I("vtss_phy_serdes_prbs_conf NOT SUPPORTED!  port_no:%d", port_no);
            }
#else
            VTSS_E("vtss_phy_serdes_prbs_conf NOT compiled into build!  port_no:%d", port_no);
#endif
        }
    }
    VTSS_EXIT();

    return rc;
}

#endif // VTSS_CHIP_CU_PHY
