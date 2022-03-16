// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_PHY_TRACE_GROUP_TS

// Avoid "vtss_api.h not used in module vtss_phy_ts_api.c"
/*lint --e{766} */

#include "vtss_phy_api.h"
#ifndef VIPER_B_FIFO_RESET
#define VIPER_B_FIFO_RESET
#endif

#if defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_CHIP_CU_PHY)
#include "../common/vtss_phy_common.h"
#include "vtss_phy_ts_api.h"
#include "vtss_phy_ts.h"


# if defined(VTSS_FIFO_SYNC_DEBUG)
#include <sys/time.h>
#endif

#if defined(VTSS_FEATURE_MACSEC)
#include "vtss_macsec_api.h"
#endif /* VTSS_FEATURE_MACSEC */

#if defined(VTSS_IOADDR)
#undef VTSS_IOADDR
#endif

#if defined(VTSS_IOREG)
#undef VTSS_IOREG
#endif

#if defined(VTSS_IOREG_IX)
#undef VTSS_IOREG_IX
#endif

#include "vtss_phy_ts_regs_common.h"
#include "vtss_phy_ts_regs.h"
#include "vtss_phy_ts_util.h"
/*lint -sem( vtss_callout_lock, thread_lock ) */
/*lint -sem( vtss_callout_unlock, thread_unlock ) */

static vtss_rc vtss_phy_id_get_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no, vtss_phy_type_t *phy_id)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];
    *phy_id = ps->type;
    VTSS_N("channel_id:%d, port_no:%d, phy_api_base_no:%d", phy_id->channel_id, port_no, phy_id->phy_api_base_no);
    return VTSS_RC_OK;
}

#if defined(VTSS_VIPER_B_FIFO_RESET)
#define VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO VTSS_IOREG(0xC0)
#define VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO VTSS_IOREG(0x9f)
#define VTSS_F_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO_AUTO_CLR VTSS_BIT(1)
#define VTSS_F_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO_AUTO_CLR VTSS_BIT(1)

#define VTSS_F_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO_INGR_SW_POP_FIFO VTSS_BIT(0)
#define VTSS_F_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO_EGR_SW_POP_FIFO VTSS_BIT(0)
#define VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_INTR_STATUS VTSS_IOREG(0x4D)
#define VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_INTR_STATUS VTSS_IOREG(0x2D)

BOOL vtss_phy_ts_bypass_get(vtss_state_t  *vtss_state,
                            const vtss_port_no_t   port_no)
{
    u32 value = 0;

    VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                 VTSS_PTP_IP_1588_TOP_CFG_STAT_INTERFACE_CTL, &value));

    if ( value & VTSS_F_PTP_IP_1588_TOP_CFG_STAT_INTERFACE_CTL_EGR_BYPASS) {
        return TRUE;
    }

    return FALSE;
}

vtss_rc vtss_phy_ts_sw_pop_fifo(vtss_state_t *vtss_state,
                                const vtss_port_no_t port_no,
                                BOOL val)
{
    u32 value = 0;
    //set ingress sw_pop_fifo
    if (val) {
        VTSS_I("2.1 set ingress sw_pop_fifo on port %u\n", port_no);
        VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                     VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO,
                                     &value));

        value = VTSS_PHY_TS_CLR_BITS(value, VTSS_F_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO_INGR_SW_POP_FIFO);

        VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                      VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO,
                                      &value));
        //    MEPA_MSLEEP(1);

        value = 0;
        VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                     VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO, &value));

        VTSS_I("INGR_SW_POP_FIFO port_no %u value 0x%x\n", port_no, value);

        //set egress sw_pop_fifo
        VTSS_I("2.1 set egress sw_pop_fifo on port %u\n", port_no);
        VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                     VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO,
                                     &value));

        value = VTSS_PHY_TS_CLR_BITS(value, VTSS_F_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO_EGR_SW_POP_FIFO);

        VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                      VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO,
                                      &value));
        //   MEPA_MSLEEP(1);

        value = 0;

        VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                     VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO, &value));
        VTSS_I("EGR_SW_POP_FIFO port_no %u value 0x%x\n", port_no, value);

    } else {
        VTSS_I("2.1 set ingress sw_pop_fifo on port %u\n", port_no);
        VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                     VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO,
                                     &value));
        value |= VTSS_F_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO_INGR_SW_POP_FIFO;
        VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                      VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO,
                                      &value));
        //    MEPA_MSLEEP(1);

        value = 0;
        VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                     VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO, &value));

        VTSS_I("INGR_SW_POP_FIFO port_no %u value 0x%x\n", port_no, value);

        //set egress sw_pop_fifo
        VTSS_I("2.1 set egress sw_pop_fifo on port %u\n", port_no);
        VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                     VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO,
                                     &value));
        value |= VTSS_F_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO_EGR_SW_POP_FIFO;
        VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                      VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO,
                                      &value));
        //   MEPA_MSLEEP(1);

        value = 0;
        VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                     VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO, &value));
        VTSS_I("EGR_SW_POP_FIFO port_no %u value 0x%x\n", port_no, value);
    }
    return VTSS_RC_OK;

}

vtss_rc vtss_phy_ts_en_pkt_mode(vtss_state_t *vtss_state,
                                const vtss_port_no_t port_no,
                                BOOL enable)
{
    u32 value = 0;
    if (enable) {
        value = 0x4;
        VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                      VTSS_PTP_IP_1588_TOP_CFG_STAT_MODE_CTL,
                                      &value));
    } else {
        /*disable packet mode */
        value = 0x0;
        VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                      VTSS_PTP_IP_1588_TOP_CFG_STAT_MODE_CTL,
                                      &value));
    }
    VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                 VTSS_PTP_IP_1588_TOP_CFG_STAT_MODE_CTL, &value));

    VTSS_I("CFG_STAT_MODE_CTL  port_no %u value 0x%x\n", port_no, value);

    return VTSS_RC_OK;
}

vtss_rc vtss_phy_intr_status(vtss_state_t *vtss_state,
                             const vtss_port_no_t port_no,
                             vtss_phy_ts_overflow_info_t *overflow_conf)
{

    u32 value = 0;

    VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                 VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_INTR_STATUS, &value));

    overflow_conf->egr_intr_status = value;

    VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                 VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_INTR_STATUS, &value));

    overflow_conf->ingr_intr_status = value;

    //write the interrupt status back.
    value = overflow_conf->egr_intr_status;
    VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                  VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_INTR_STATUS,
                                  &value));

    value = overflow_conf->ingr_intr_status;
    VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                  VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_INTR_STATUS,
                                  &value));

    return VTSS_RC_OK;
}

vtss_rc vtss_phy_sw_pop_fifo_get(vtss_state_t *vtss_state,
                                 const vtss_port_no_t port_no,
                                 vtss_phy_ts_pop_fifo_t *pop_fifo)
{
    u32 value = 0;

    VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                 VTSS_PTP_EGR_IP_1588_DEBUG_REGISTERS_EGR_SW_POP_FIFO, &value));

    pop_fifo->egr_pop_fifo = value;

    VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                 VTSS_PTP_INGR_IP_1588_DEBUG_REGISTERS_INGR_SW_POP_FIFO , &value));

    pop_fifo->ingr_pop_fifo = value;

    return VTSS_RC_OK;
}

BOOL  vtss_phy_ts_algo_execute_check(vtss_state_t *vtss_state,
                                     const vtss_port_no_t port_no)
{
    u32 value = 0;
    u32 ingr_eng, egr_eng;
    if (vtss_state->phy_ts_port_conf[port_no].port_ts_init_done == FALSE) {
        VTSS_I("Port ts not initialized! port: %d", port_no);
        return FALSE;
    }
    /* Check if 1588 clock is enabled or not */
    value = 0;
    VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                 VTSS_PTP_IP_1588_TOP_CFG_STAT_INTERFACE_CTL, &value));

    if (value & VTSS_F_PTP_IP_1588_TOP_CFG_STAT_INTERFACE_CTL_CLK_ENA) {
        VTSS_I("1588 Clk is enabled - OOS Check Supported ");
    } else {
        VTSS_I("1588 Clk is Disabled - OOS Check NOT Supported - Returning!");
        //        VTSS_PHY_TS_SPI_UNPAUSE_PRIV(port_no);
        return FALSE;
    }
    value = 0;
    VTSS_RC(VTSS_PHY_TS_READ_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID_0,
                                 VTSS_PTP_IP_1588_TOP_CFG_STAT_ANALYZER_MODE, &value));

    ingr_eng = value & 0x7;
    egr_eng = value & ( 0x7 << 4);

    VTSS_I("ingr_eng %u egr_eng %u\n", ingr_eng, egr_eng);
    if (!(ingr_eng | egr_eng)) {
        return FALSE;
    }


    return TRUE;
}


vtss_rc vtss_phy_1588_oos_mitigation_steps_private(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t port_no,
                                                   const vtss_phy_ts_fifo_conf_t *fifo_conf);


static vtss_rc vtss_phy_1588_oos_mitigation_steps_execute(vtss_state_t *vtss_state,
                                                          const vtss_port_no_t port_no,
                                                          BOOL copper,
                                                          BOOL ams_mode,
                                                          BOOL cu_sfp);

//proc core_patch {port proc_id} {

static vtss_rc vtss_phy_10g_oos_core_patch( vtss_state_t *vtss_state,
                                            const vtss_port_no_t port_no)
{
    u16 reg;
#if defined(VTSS_FEATURE_MACSEC)
    BOOL macsec_enable = FALSE;
    macsec_enable = vtss_state->macsec_conf[port_no].glb.init.enable;
#endif

    VTSS_I("Executing core patch in pkt mode to clear fifo reset bit ox69\n");

    //TeslaCsrWrite $port $proc_id 0x02 0x4;  #Mode ctrl, enable pkt mode
#if defined(VTSS_FEATURE_MACSEC)
    if(!macsec_enable)
#endif
    {
        VTSS_RC(vtss_phy_ts_en_pkt_mode(vtss_state, port_no, TRUE));
    }

    //TeslaCsrWrite $port $proc_id 0x00 0x46;#Enable 1588 Bypass
    vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, TRUE);

    //Ext4MiiWriteBits 0 21 15 15 1;#1588 reset

    VTSS_RC(vtss_phy_page_ext4(vtss_state, port_no));
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_1588_PPS_0_MUX_CTRL , VTSS_F_PHY_1588_PPS_0_MUX_CTRL_1588_SOFT_RESET,
                                    VTSS_F_PHY_1588_PPS_0_MUX_CTRL_1588_SOFT_RESET));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1588_PPS_0_MUX_CTRL , &reg));

    VTSS_I("VTSS_PHY_1588_PPS_0_MUX_CTRL Port_no %u Value 0x%x\n", port_no, reg);

    //after 1
    MEPA_MSLEEP(1);

    //TeslaCsrWrite $port $proc_id 0x00 0x42;#Disable 1588 bypass
    vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, TRUE);

    //TeslaCsrWrite $port $proc_id 0x9F 0x69;#SW_POP_FIFO
    //TeslaCsrWrite $port $proc_id 0xC0 0x69
    VTSS_RC(vtss_phy_ts_sw_pop_fifo(vtss_state, port_no, FALSE));

    //after 1
    MEPA_MSLEEP(1);

    //ExtMiiWrite $port 29 0x8042;#Enable EPG
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));        // Switch to extended register-page 1
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, 0x8042));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg));
    VTSS_I("EPG_CTRL_REG_1 Port_no %u Value 0x%x\n", port_no, reg);

    //ExtMiiWriteBits $port 29 14 14 1;#Trigger 300 EPG frames
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg));
    reg = reg | 0x4000;
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, reg));

    //after 10
    MEPA_MSLEEP(10);

    //TeslaCsrWrite $port $proc_id 0x00 0x46;#Enable 1588 Bypass
    vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, TRUE);

    //Ext4MiiWriteBits 0 21 15 15 1;#1588 reset
    VTSS_RC(vtss_phy_page_ext4(vtss_state, port_no));
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_1588_PPS_0_MUX_CTRL , VTSS_F_PHY_1588_PPS_0_MUX_CTRL_1588_SOFT_RESET,
                                    VTSS_F_PHY_1588_PPS_0_MUX_CTRL_1588_SOFT_RESET));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1588_PPS_0_MUX_CTRL , &reg));

    VTSS_I("VTSS_PHY_1588_PPS_0_MUX_CTRL Port_no %u Value 0x%x\n", port_no, reg);

    //after 1
    MEPA_MSLEEP(1);

    //TeslaCsrWrite $port $proc_id 0x00 0x42;#Disable 1588 bypass
    vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, TRUE);

    //TeslaCsrWrite $port $proc_id 0x9F 0x69;
    //TeslaCsrWrite $port $proc_id 0xC0 0x69
    VTSS_RC(vtss_phy_ts_sw_pop_fifo(vtss_state, port_no, FALSE));

    //TeslaCsrWrite $port $proc_id 0x02 0x0;  #Mode ctrl pkt mode disable
#if defined(VTSS_FEATURE_MACSEC)
    if(!macsec_enable)
#endif
    {
        VTSS_RC(vtss_phy_ts_en_pkt_mode(vtss_state, port_no, FALSE));
    }

    return VTSS_RC_OK;

}
vtss_rc vtss_phy_ts_viper_fifo_reset(const vtss_inst_t               inst,
                                     const vtss_port_no_t            port_no,
                                     const vtss_phy_ts_fifo_conf_t *fifo_conf)
{
    vtss_rc    rc = VTSS_RC_ERROR;
    vtss_state_t   *vtss_state;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst,  &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_1588_oos_mitigation_steps_private(vtss_state, port_no, fifo_conf);
    }
    VTSS_EXIT();
    return rc;
}


static vtss_rc token_reg_write_func(vtss_state_t *vtss_state, const vtss_port_no_t port_no, u32 register_val, u16 value1, u16 mask1, u16 value2, u16 mask2)
{
    u16 reg;
    u32 address;

    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));    // Go to Token Ring Page 0x52b5
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    address = 0xa000 | register_val;

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, address));   // Setup Address, Reg16 for READING Address 0xc80
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, &reg));
    VTSS_I("VTSS_PHY_PAGE_TR_16 Port_no %u Value 0x%x\n", port_no, reg);


    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, value1, mask1)); /*- Read-Modify-Write of Reg18 to have a value of 0x0045 */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg));
    VTSS_I("VTSS_PHY_PAGE_TR_18 Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, value2, mask2)); /*- Read-Modify-Write of Reg17 to have a value of 0x1000 */
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
    VTSS_I("VTSS_PHY_PAGE_TR_17 Port_no %u Value 0x%x\n", port_no, reg);

    address = 0x8000 | register_val;

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, address));   // Setup Address, Reg16 for WRITING Address 0xc80
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, &reg));
    VTSS_I("VTSS_PHY_PAGE_TR_16 Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));   // Go back to Std Page
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    return VTSS_RC_OK;
}


//FOR 100BT and 10BT speeds.
static vtss_rc vtss_phy_1588_oos_mitigation_save_cfg(vtss_state_t *vtss_state,
                                                     const vtss_port_no_t port_no,
                                                     u16 *reg0,
                                                     u16 *reg9,
                                                     u16 *extreg29,
                                                     u16 *reg23)
{
    u16 reg;
    //Save Reg 0 and Reg 9 and register 29E1
    // set reg0 [MiiRead $port 0]
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));   // Go back to Std Page
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    //read register 0
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL , reg0));
    //set reg9 [MiiRead $port 9]
    //Save register 9
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no,  VTSS_PHY_1000BASE_T_CONTROL , reg9));

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no,  VTSS_PHY_EXTENDED_PHY_CONTROL , reg23));

    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, extreg29));

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return VTSS_RC_OK;
}

vtss_rc vtss_phy_ts_isolate_phy(vtss_state_t *vtss_state,
                                const vtss_port_no_t port_no)
{
    vtss_phy_type_t                phy_id;
    //Only Perform the Operation for Viper B.

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    if (!((phy_id.part_number == VTSS_PHY_TYPE_8582) || (phy_id.part_number == VTSS_PHY_TYPE_8584) || (phy_id.part_number == VTSS_PHY_TYPE_8575))) {
        VTSS_I("Not A Viper PHY, returning port_no %u\n", port_no);
        return VTSS_RC_OK;
    }

    if(!(phy_id.revision >= 1)){
        VTSS_I("Viper Rev A, OOS algorithm should not be executed\n");
        return VTSS_RC_OK;
    }

    if ((vtss_phy_ts_algo_execute_check(vtss_state, port_no)) == FALSE) {
        VTSS_I("PTP is not configured on the port exiting quietly\n");
        return VTSS_RC_OK;
    }


    VTSS_RC(token_reg_write_func(vtss_state, port_no, 0x0cc0, 0x2, 0x2, 0x610, 0x610));

    //TeslaCsrWrite $port $proc_id 0x00 0x46;#Enable 1588 Bypass
    VTSS_RC(vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, TRUE));

    //after 1
    MEPA_MSLEEP(1);

    //TrWrite $port mac_isolate_rx -1 1;#Prevent mac side traffic
    VTSS_I("3.Configure mac_isolate_rx and wait for 1m (to prevent media side traffic) \n");
    VTSS_RC(token_reg_write_func(vtss_state, port_no, 0x0c80, 0x0045, 0x0045, 0x1000, 0x1000));

    //TrWrite $port mac_isolate_tx -1 1
    VTSS_I("3.Configure mac_isolate_tx and wait for 1m (to prevent media side traffic) \n");
    VTSS_RC(token_reg_write_func(vtss_state, port_no, 0x0c80, 0x0085, 0x0085, 0x1000, 0x1000));

    return VTSS_RC_OK;

}
vtss_rc vtss_phy_1588_oos_mitigation_isolate_phy(vtss_state_t *vtss_state,
                                                        const vtss_port_no_t port_no,
                                                        BOOL copper)
{
    vtss_rc rc = VTSS_RC_OK;

    //TrWrite $port epg_testmode -1 1

    VTSS_I("Enabling EPG in test mode\n");
    rc = token_reg_write_func(vtss_state, port_no, 0x0cc0, 0x2, 0x2, 0x610, 0x610);

    //TeslaCsrWrite $port $proc_id 0x00 0x46;#Enable 1588 Bypass
    rc = vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, TRUE);

    //after 1
    MEPA_MSLEEP(1);

    //TrWrite $port mac_isolate_rx -1 1;#Prevent mac side traffic
    VTSS_I("3.Configure mac_isolate_rx and wait for 1m (to prevent media side traffic) \n");
    rc = token_reg_write_func(vtss_state, port_no, 0x0c80, 0x0045, 0x0045, 0x1000, 0x1000);

    //TrWrite $port mac_isolate_tx -1 1
    VTSS_I("3.Configure mac_isolate_tx and wait for 1m (to prevent media side traffic) \n");
    rc = token_reg_write_func(vtss_state, port_no, 0x0c80, 0x0085, 0x0085, 0x1000, 0x1000);

    if(copper) {
        //MiiWrite $port 9 0x1F00;#Force Master
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, 0x1F00));

        //MiiWriteBits $port 0 9 9 1;#Restart ANEG
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                    VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG,
                    VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG));

        //MiiWrite $port 0 0x4140; #Forced 1G mode and Near-End loopback
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0x4140));
    } else {
        //set Near-end loopback
        VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL,
                    VTSS_F_PHY_MODE_CONTROL_LOOP,
                    VTSS_F_PHY_MODE_CONTROL_LOOP));
    }

    return rc;
}
static vtss_rc  vtss_phy_1588_oos_mitigation_media_interface_link_status(vtss_state_t *vtss_state,
                                                                 const vtss_port_no_t port_no)
{
    u16 reg;
    u32 count;
    reg = count = 0;

    VTSS_I("vtss_phy_1588_oos_mitigation_media_interface_link_status  Media connected is Cu-SFP checking media interface link status\n");
    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));    // Go to Extended page 3
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_STATUS, &reg));

    count = 0;

    while(!(reg & VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_MEDIA_LINK_STATUS))
    {
        count++;

        if (count >= 10) {
            VTSS_E("LOCAL REMOTE STATUS GOOD POLL took too much time\n");
            break;
        }
        VTSS_I("VTSS_PHY_1000BASE_T_STATUS 14:12 still not set\n");
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_PCS_STATUS, &reg));
        VTSS_I("VTSS_PHY_1000BASE_T_STATUS value %x", reg);
        MEPA_MSLEEP(1);
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));    // Go to standard Page

    return VTSS_RC_OK;

}
static vtss_rc vtss_phy_1588_oos_mitigation_check_frames_remote_local_good(vtss_state_t *vtss_state,
                                                                           const vtss_port_no_t port_no)
{
    u16 reg, rec_cnt, rx_er, tx_cnt;
    u32 count;
    BOOL check_for_no_frames;
    //while {![MiiReadBits $port 10 14 12] == "0x7"} {};#Waiting to receive remote&local status good
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_STATUS, &reg));

    count = 0;

    while (!((reg & 0x7000) == 0x7000)) {
        count++;

        if (count >= 10) {
            VTSS_E("LOCAL REMOTE STATUS GOOD POLL took too much time\n");
            break;
        }
        VTSS_I("VTSS_PHY_1000BASE_T_STATUS 14:12 still not set\n");
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_STATUS, &reg));
        VTSS_I("VTSS_PHY_1000BASE_T_STATUS value %x", reg);
        MEPA_MSLEEP(1);
    }

    //after 1
    MEPA_MSLEEP(1);


    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    check_for_no_frames = 1;
    count = 0;
    while (check_for_no_frames) {

        count++;
        if (count > 10) {
            VTSS_E("No of times this loop has run is greater than 10 Exiting\n");
            break;
        }

        VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
        VTSS_RC(vtss_phy_rd(vtss_state, port_no, 18, &rec_cnt));
        VTSS_RC(vtss_phy_rd(vtss_state, port_no, 19, &rx_er));
        rec_cnt &= 0x3FFF;
        rx_er &= 0xFF;

        tx_cnt = 0;
        //tx_cnt read using the register reads provided in image
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));  // Set page to token ring.
        VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
        VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xbf88));   // Setup Address, Reg16 for READING Address 0xc80
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, &reg));
        VTSS_I("VTSS_PHY_PAGE_TR_16 Port_no %u Value 0x%x\n", port_no, reg);

        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, &reg));
        tx_cnt |= reg << 16;
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, &reg));
        tx_cnt |= reg;

        //        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));   // Go back to Std Page
        //        VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
        //        VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

        VTSS_I("tx_cnt %u, rec_cnt %u rx_er %u\n", tx_cnt, rec_cnt, rx_er);

        if ((rec_cnt == 0) && (rx_er == 0) && (tx_cnt == 0)) {
            check_for_no_frames = 0;
        }
        MEPA_MSLEEP(1);
    }
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return VTSS_RC_OK;
}
static vtss_rc vtss_phy_1588_oos_mitigation_soft_reset_pop_fifo(vtss_state_t *vtss_state,
                                                                const vtss_port_no_t port_no)
{
    u16 reg;
    vtss_phy_ts_overflow_info_t overflow_conf;
    //Ext4MiiWriteBits 0 21 15 15 1;#1588 reset
    VTSS_I("7.Give 1588 soft reset\n");
    VTSS_RC(vtss_phy_page_ext4(vtss_state, port_no));
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_1588_PPS_0_MUX_CTRL , VTSS_F_PHY_1588_PPS_0_MUX_CTRL_1588_SOFT_RESET,
                VTSS_F_PHY_1588_PPS_0_MUX_CTRL_1588_SOFT_RESET));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_1588_PPS_0_MUX_CTRL , &reg));

    VTSS_I("VTSS_PHY_1588_PPS_0_MUX_CTRL Port_no %u Value 0x%x\n", port_no, reg);

    //after 1
    MEPA_MSLEEP(1);

    //TeslaCsrWrite $port $proc_id 0x00 0x42;#Disable 1588 bypass
    vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, TRUE);

    //after 1
    MEPA_MSLEEP(1);
    //TeslaCsrWrite $port $proc_id 0x9F 0x69;#SW_POP_FIFO
    //TeslaCsrWrite $port $proc_id 0xC0 0x69
    VTSS_RC(vtss_phy_ts_sw_pop_fifo(vtss_state, port_no, FALSE));

    //TeslaCsrWrite $port $proc_id 0x9F 0x68;
    //TeslaCsrWrite $port $proc_id 0xC0 0x68
    VTSS_RC(vtss_phy_ts_sw_pop_fifo(vtss_state, port_no, TRUE));
    // set d2 [TeslaCsrRead $port $proc_id 0x2D]
    // set d4 [TeslaCsrRead $port $proc_id 0x4D]
    // TeslaCsrWrite $port $proc_id 0x2D $d2;
    //     TeslaCsrWrite $port $proc_id 0x4D $d4
    VTSS_RC(vtss_phy_intr_status(vtss_state, port_no, &overflow_conf));

    return VTSS_RC_OK;
}
static vtss_rc vtss_phy_1588_oos_mitigation_epg_transmit_frames(vtss_state_t *vtss_state,
                                                                const vtss_port_no_t port_no,
                                                                BOOL copper)
{
    u16 reg;
    u32 count;
    u16 rec_cnt;

    //ExtMiiRead $port 18
    VTSS_I("Read Good CRC counter\n");
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));        // Switch to extended register-page 1
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_CU_MEDIA_CRC_GOOD_COUNTER, &reg));

    VTSS_I("Value of register VTSS_PHY_CU_MEDIA_CRC_GOOD_COUNTER is 0x%x\n", reg);

    //ExtMiiWrite $port 29 0x8042;#Enable EPG
    VTSS_I("9.Enable EPG. Just enable, don't start it\n");
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));        // Switch to extended register-page 1
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, 0x8042));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg));
    VTSS_I("EPG_CTRL_REG_1 Port_no %u Value 0x%x\n", port_no, reg);


    //ExtMiiWriteBits $port 29 14 14 1;#Trigger 300 EPG frames
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg));
    reg = reg | 0x4000;
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, reg));

    if(copper){
        count = 0;
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg));

        while (reg & 0x4000) {
            if(count >= 10){
                VTSS_E("EPG taking way too long to transmit packets\n");
                return VTSS_RC_ERROR;
            }
            VTSS_I("Waiting to transmit EPG frames\n");
            MEPA_MSLEEP(1);
            VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg));
            count++;
        }
    }
    //after 10
    MEPA_MSLEEP(10);

    //set rec_cnt [hex2dec [ExtMiiReadBits $port 18 13 0]]
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));

    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 18, &rec_cnt));
    //htEcho 1 "----Received $rec_cnt"
    rec_cnt &= 0x3FFF;
    VTSS_I("Recieved %u\n", rec_cnt);

    rec_cnt = 0;
    //[Ext3MiiReadBits $port 28 13 0]
    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 28, &rec_cnt));
    VTSS_I("Media-MAC SerDes Receive CRC Good Counter rec_cnt %u\n",rec_cnt);


    return VTSS_RC_OK;
}
static vtss_rc vtss_phy_1588_oos_mitigation_execute_core_patch_execute(vtss_state_t *vtss_state,
                                                                       const vtss_port_no_t port_no)
{
    vtss_phy_ts_overflow_info_t overflow_conf;
    vtss_phy_ts_pop_fifo_t pop_fifo;
    u32 core_patch_cnt;

    //htEcho 1 "2D:[TeslaCsrRead $port $proc_id 0x2D]"
    //htEcho 1 "4D:[TeslaCsrRead $port $proc_id 0x4D]"
    //htEcho 1 "9F:[TeslaCsrRead $port $proc_id 0x9F]"
    //htEcho 1 "C0:[TeslaCsrRead $port $proc_id 0xC0]"

    VTSS_RC(vtss_phy_sw_pop_fifo_get(vtss_state, port_no, &pop_fifo));
    VTSS_I("Value of register 0x9F INGR_SW_POP_FIFO is 0x%x\n", pop_fifo.egr_pop_fifo);
    VTSS_I("Value of register 0xC0 EGR_SW_POP_FIFO is 0x%x\n", pop_fifo.ingr_pop_fifo);

    //set core_patch_cnt 0
    core_patch_cnt = 0;


    while ((pop_fifo.ingr_pop_fifo  == 0x69) || (pop_fifo.egr_pop_fifo  == 0x69)) {

        core_patch_cnt++;

        if (core_patch_cnt > 10) {
            VTSS_I("Core patch executing way too many times, exiting\n");
            break;

        }
        //check if the core patch is the same for 100BT and normal Cu-Fiber Operations => It is same
        //core_patch $port $proc_id
        VTSS_RC(vtss_phy_10g_oos_core_patch(vtss_state, port_no));

        //htEcho 1 "2D:[TeslaCsrRead $port $proc_id 0x2D]"
        //htEcho 1 "4D:[TeslaCsrRead $port $proc_id 0x4D]"
        //htEcho 1 "9F:[TeslaCsrRead $port $proc_id 0x9F]"
        //htEcho 1 "C0:[TeslaCsrRead $port $proc_id 0xC0]"
        VTSS_RC(vtss_phy_intr_status(vtss_state, port_no, &overflow_conf));
        VTSS_I("Value of register 0x2D INGR_INT_STATUS is 0x%x\n", overflow_conf.ingr_intr_status);
        VTSS_I("Value of register 0x4D EGR_INT_STATUS is 0x%x\n", overflow_conf.egr_intr_status);
        VTSS_RC(vtss_phy_sw_pop_fifo_get(vtss_state, port_no, &pop_fifo));
        VTSS_I("Value of register 0x9F INGR_SW_POP_FIFO is 0x%x\n", pop_fifo.egr_pop_fifo);
        VTSS_I("Value of register 0xC0 EGR_SW_POP_FIFO is 0x%x\n", pop_fifo.ingr_pop_fifo);

    }
    return VTSS_RC_OK;
}
static vtss_rc vtss_phy_1588_oos_mitigation_restore_setup(vtss_state_t *vtss_state, const vtss_port_no_t port_no, u16 *reg0, u16 *reg9, u16 *extreg29, u16 *reg23)
{
    u16 reg;
    vtss_rc rc = VTSS_RC_OK;
    //ExtMiiWriteBits $port 29 15 15 0;#Disable EPG to enable datapath
    VTSS_I("11.   Disable EPG bit. (This will enable normal datapath.)\n");
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));        // Switch to extended register-page 1
    VTSS_RC(vtss_phy_rd(vtss_state, port_no, 31, &reg));
    VTSS_I("Current Page Value Port_no %u Value 0x%x\n", port_no, reg);

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, *extreg29));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, EPG_CTRL_REG_1, &reg));
    VTSS_I("EPG_CTRL_REG_1 Port_no %u Value 0x%x\n", port_no, reg);

    //TrWrite $port epg_testmode -1 0
    VTSS_I("Disable EPG Test mode\n");

    rc = token_reg_write_func(vtss_state, port_no, 0x0cc0, 0x0, 0x2, 0x610, 0x610);

    //after 1
    MEPA_MSLEEP(1);

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, *reg23));

    //TrWrite $port mac_isolate_rx -1 0
    VTSS_I("16.Disable mac_isolate_rx and wait for 1ms\n");
    rc = token_reg_write_func(vtss_state, port_no, 0x0c80, 0x0005, 0x0045, 0x1000, 0x1000);

    //TrWrite $port mac_isolate_tx -1 0
    VTSS_I("16.5.Disable mac_isolate_tx and wait for 1ms\n");
    rc = token_reg_write_func(vtss_state, port_no, 0x0c80, 0x0005, 0x0085, 0x1000, 0x1000);

    //after 1
    MEPA_MSLEEP(1);

    VTSS_I("Normal Operation being restored\n");
    //MiiWrite $port 9 $reg9
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, *reg9));

    //MiiWrite $port 0 $reg0;#This will take care of disabling Near-End loopback
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, *reg0));

    return rc;
}
vtss_rc vtss_phy_1588_oos_mitigation_steps_private(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t port_no, const vtss_phy_ts_fifo_conf_t *fifo_conf)
{
    vtss_phy_port_state_t          *ps = &vtss_state->phy_state[port_no];
    vtss_phy_media_interface_t     media_type = ps->reset.media_if;
    vtss_port_speed_t              speed = ps->status.speed;
    vtss_phy_type_t                phy_id;
    vtss_rc                        rc = VTSS_RC_OK;
    BOOL ts_new_rev = TRUE;
    BOOL cu_mode;   /*If the bit is set it is copper interface, otherwise it is fiber interface */
    BOOL ams_mode = FALSE;
    BOOL macsec_enable = FALSE;
    BOOL cu_sfp = FALSE;
    u16 is_power_down = 0;

#if defined(VTSS_FEATURE_MACSEC)
    macsec_enable =  vtss_state->macsec_conf[port_no].glb.init.enable;
#endif

#ifdef VTSS_FIFO_SYNC_DEBUG
    struct timeval   tv;
    gettimeofday(&tv, NULL);
    VTSS_I("Time At the entry of Algoritm: Sec %ld, Usec  %ld\n", tv.tv_sec, tv.tv_usec);
#endif

    VTSS_I("Speed configured in the previous Run is %u\n", speed);

    VTSS_I("Media type selected is %u\n", media_type);


    if (vtss_state->phy_ts_port_conf[port_no].port_ts_init_done == FALSE) {
        VTSS_I("Port ts not initialized! exiting quietly port: %d", port_no);
        return VTSS_RC_OK;
    }
    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));

    if (!((phy_id.part_number == VTSS_PHY_TYPE_8582) || (phy_id.part_number == VTSS_PHY_TYPE_8584) || (phy_id.part_number == VTSS_PHY_TYPE_8575))) {
        //OOS Algorithm is supported on only 1588 Supported SKU's
        //i.e PHY ID 8584, 8582, 8575
        return VTSS_RC_OK;
    }

    if(!(phy_id.revision >= 1)){
        VTSS_I("Viper Rev A, OOS algorithm should not be executed\n");
        return VTSS_RC_OK;
    }

    //Check if PHY is in power down mode, in that case do not execute the algorithm.
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no,VTSS_PHY_MODE_CONTROL, &is_power_down));
    if(is_power_down & VTSS_F_PHY_MODE_CONTROL_POWER_DOWN) {
        VTSS_I("PHY is in Power Down mode, Algorithm not supported. Exiting Silently\n");
        return VTSS_RC_OK;
    }

    if ((vtss_phy_ts_algo_execute_check(vtss_state, port_no)) == FALSE) {
        VTSS_I("PTP is not configured on the port exiting quietly\n");
        return VTSS_RC_OK;
    }

    if(!fifo_conf->skip_rev_check){
        vtss_phy_ts_version_check(vtss_state, port_no, &ts_new_rev);
        if (ts_new_rev == TRUE) {
            VTSS_I("Not running oos alog port %u\n", port_no);
            return VTSS_RC_OK;
        }
    }

    //Select mode of execution depending on the media_type configured on the device.
    switch (media_type) {
        case VTSS_PHY_MEDIA_IF_CU:
            cu_mode = TRUE;
            break;
        case VTSS_PHY_MEDIA_IF_SFP_PASSTHRU:
            cu_sfp = TRUE;
            cu_mode = TRUE;
            break;
        case VTSS_PHY_MEDIA_IF_FI_1000BX:
            cu_mode = FALSE;
            break;
        case VTSS_PHY_MEDIA_IF_FI_100FX:
            cu_mode = FALSE;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU:
            cu_mode = TRUE;
            ams_mode = TRUE;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU:
            cu_mode = FALSE;
            ams_mode = TRUE;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_1000BX:
            cu_mode = TRUE;
            ams_mode = TRUE;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_1000BX:
            cu_mode = FALSE;
            ams_mode = TRUE;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_CU_100FX:
            cu_mode = TRUE;
            ams_mode = TRUE;
            break;
        case VTSS_PHY_MEDIA_IF_AMS_FI_100FX:
            cu_mode = FALSE;
            ams_mode = TRUE;
            break;
        default:
            VTSS_E("No Media Type selected\n");
            return VTSS_RC_OK;
            break;
    }

    if(ams_mode == TRUE)
        cu_mode = TRUE;   //Need to run fiber patch in AMS cases

    VTSS_I("Calling OOS Alog ams_mode : %s  cu_mode : %s port_no : %u\n", ams_mode ? "TRUE " : "FALSE ", cu_mode ? "TRUE " : "FALSE ", port_no);

    if(!macsec_enable)
        rc = vtss_phy_1588_oos_mitigation_steps_execute(vtss_state, port_no, cu_mode, ams_mode, cu_sfp);
    else
        VTSS_I("MACsec is enabled, Current 1588 OOS Algorithm does not support MACsec modes");

#ifdef VTSS_FIFO_SYNC_DEBUG
    gettimeofday(&tv, NULL);
    VTSS_I("Time At the exit of Algoritm: Sec %ld, Usec  %ld\n", tv.tv_sec, tv.tv_usec);
#endif
    return rc;
}
static vtss_rc vtss_phy_1588_oos_mitigation_steps_execute(vtss_state_t *vtss_state,
                                                         const vtss_port_no_t port_no, 
                                                         BOOL copper,
                                                         BOOL ams_mode,
                                                         BOOL cu_sfp)
{
    vtss_rc rc = VTSS_RC_OK;
    vtss_phy_ts_overflow_info_t overflow_conf = {};
    vtss_phy_ts_pop_fifo_t pop_fifo = {};
    u16 reg0, reg9, extreg29, reg23;
    VTSS_I("Enter vtss_phy_1588_oos_mitigation_steps_execute port_no %u mode of operation %s\n", port_no, copper? "Copper": "Fiber");

    rc = vtss_phy_1588_oos_mitigation_save_cfg(vtss_state, port_no, &reg0, &reg9, &extreg29, &reg23);

    if(rc != VTSS_RC_OK){
        VTSS_E("Not Able to save configuration, returning");
        return VTSS_RC_ERROR;
    }

    if(rc == VTSS_RC_OK)
        rc = vtss_phy_1588_oos_mitigation_isolate_phy(vtss_state, port_no, copper);

    if(ams_mode){
        rc = PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL,
                VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_OVERRIDE(2),
                VTSS_M_PHY_EXTENDED_PHY_CONTROL_AMS_OVERRIDE);
    }

    if(rc == VTSS_RC_OK){
        if(copper && !cu_sfp){
            rc = vtss_phy_1588_oos_mitigation_check_frames_remote_local_good(vtss_state, port_no);
        } else if (cu_sfp) {
            rc = vtss_phy_1588_oos_mitigation_media_interface_link_status(vtss_state, port_no);
        }

    }

    //TeslaCsrWrite $port $proc_id 0x00 0x42;#Disable 1588 bypass
    if(rc == VTSS_RC_OK){
        rc = vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, TRUE);
    }

    //after 1
    MEPA_MSLEEP(1);
    if(rc == VTSS_RC_OK){
        rc = vtss_phy_intr_status(vtss_state, port_no, &overflow_conf);
    }

    VTSS_I("Value of register 0x2D INGR_INT_STATUS is 0x%x\n", overflow_conf.ingr_intr_status);
    VTSS_I("Value of register 0x4D EGR_INT_STATUS is 0x%x\n", overflow_conf.egr_intr_status);

    if(rc == VTSS_RC_OK)
        rc = vtss_phy_sw_pop_fifo_get(vtss_state, port_no, &pop_fifo);

    VTSS_I("Value of register 0x9F INGR_SW_POP_FIFO is 0x%x\n", pop_fifo.egr_pop_fifo);
    VTSS_I("Value of register 0xC0 EGR_SW_POP_FIFO is 0x%x\n", pop_fifo.ingr_pop_fifo);

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, TRUE);

    //after 1
    MEPA_MSLEEP(1);

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_1588_oos_mitigation_soft_reset_pop_fifo(vtss_state, port_no);

    //after 1
    MEPA_MSLEEP(1);

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_1588_oos_mitigation_epg_transmit_frames(vtss_state, port_no, copper);

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, TRUE);

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_1588_oos_mitigation_soft_reset_pop_fifo(vtss_state, port_no);

    MEPA_MSLEEP(1);

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_1588_oos_mitigation_execute_core_patch_execute(vtss_state, port_no);

    //After 1
    MEPA_MSLEEP(1);

    //Enable 1588 Bypass

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_ts_bypass_set(vtss_state, port_no, TRUE, TRUE);

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_1588_oos_mitigation_restore_setup(vtss_state, port_no,&reg0, &reg9, &extreg29, &reg23);

    MEPA_MSLEEP(1);

    if(rc == VTSS_RC_OK)
    rc = vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, TRUE);

    if(rc != VTSS_RC_OK){
       VTSS_E("Failure in the execution of Algorithm, Restoring PHY operation");
       rc = vtss_phy_ts_bypass_set(vtss_state, port_no, FALSE, TRUE);
       rc = vtss_phy_1588_oos_mitigation_restore_setup(vtss_state, port_no,&reg0, &reg9, &extreg29, &reg23);
       return VTSS_RC_ERROR;
    }
    VTSS_I("*******************************************************************************\n");
    VTSS_I("********************ALGORITHM EXECUTION COMPLETED******************************\n");
    VTSS_I("*******************************************************************************\n");

    return rc;
}
#else
vtss_rc vtss_phy_ts_viper_fifo_reset(const vtss_inst_t               inst,
                                     const vtss_port_no_t            port_no,
                                     const vtss_phy_ts_fifo_conf_t *fifo_conf)
{
    return VTSS_RC_OK;
}


vtss_rc vtss_phy_1588_oos_mitigation_steps_private(vtss_state_t *vtss_state,
                                                   const vtss_port_no_t port_no,
                                                   const vtss_phy_ts_fifo_conf_t *fifo_conf)
{
    return VTSS_RC_OK;
}
#endif
static vtss_rc vtss_phy_1g_ts_fifo_sync_private(vtss_state_t               *vtss_state,
                                                const vtss_port_no_t       port_no,
                                                const vtss_debug_printf_t  pr,
                                                const vtss_phy_ts_fifo_conf_t *fifo_conf,
                                                BOOL                          *OOS)
{
    vtss_rc        rc = VTSS_RC_OK;
    vtss_phy_type_t         phy_id;

    VTSS_RC(vtss_phy_id_get_private(vtss_state, port_no, &phy_id));
    VTSS_I("Enter vtss_phy_1g_ts_fifo_sync_private port_no %u PHY_ID 0x%x\n", port_no, phy_id.part_number);

    if ((phy_id.part_number == VTSS_PHY_TYPE_8582) || (phy_id.part_number == VTSS_PHY_TYPE_8584) || (phy_id.part_number == VTSS_PHY_TYPE_8575)) {

        rc = vtss_phy_1588_oos_mitigation_steps_private(vtss_state, port_no, fifo_conf); 

    } 
    return rc;
}
vtss_rc vtss_phy_1g_ts_fifo_sync(const vtss_inst_t  inst,
                                 const vtss_port_no_t port_no,
                                 const vtss_debug_printf_t pr,
                                 const vtss_phy_ts_fifo_conf_t *fifo_conf,
                                 BOOL *OOS)
{
    vtss_rc        rc = VTSS_RC_OK;
    vtss_state_t   *vtss_state;

    VTSS_ENTER();

    if ((rc = vtss_inst_port_no_check(inst,  &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = vtss_phy_1g_ts_fifo_sync_private(vtss_state, port_no, pr, fifo_conf, OOS);
    }

    VTSS_EXIT();
    return rc;
}


#endif /* #if defined(VTSS_CHIP_CU_PHY) */
#endif /* VTSS_OPT_PHY_TIMESTAMP */

