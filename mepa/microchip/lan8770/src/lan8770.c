// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan8770_registers.h"
#include "lan8770_private.h"

/* LAN8770 is a Single-Port 100BASE-T1 Ethernet Phy*/

static mepa_device_t lan8770_device[MAX_LAN8770_PHY];
static phy_data_t lan8770_data[MAX_LAN8770_PHY];

// LAN8770 Driver Register Access APIs

static mepa_rc phy_direct_reg_rd(mepa_device_t *const dev, uint16_t const offset, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    if (dev->callout->miim_read != NULL) {
        rc = dev->callout->miim_read(dev->callout_ctx, offset, value);
    }

    return rc;
}

static mepa_rc phy_direct_reg_wr(mepa_device_t *const dev, uint16_t const offset, uint16_t const value)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    if (dev->callout->miim_write != NULL) {
        rc = dev->callout->miim_write(dev->callout_ctx, offset, value);
    }

    return rc;
}

static mepa_rc phy_direct_read_mod_write_register(mepa_device_t *const dev, uint16_t const offset, uint16_t const value, uint16_t const mask)
{
    uint16_t val = 0x0;
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, phy_direct_reg_rd(dev, offset, &val));
    val = (val & (mask ^ 0xFFFF)) | value;
    MEPA_RC(rc, phy_direct_reg_wr(dev, offset, val));
    T_D( MEPA_TRACE_GRP_GEN, "modify_register addr=0x%x, set=0x%x,"
         "clr=0x%x, reg_val=0x%x, ret_code=%d \r\n",
         offset, value, mask, val, rc);
error:
    return rc;
}

static mepa_rc phy_ext_bank_reg_rd(mepa_device_t *const dev, uint16_t const bank, uint16_t const offset, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (bank == LAN8770_PHY_BANK_SMI) {
        MEPA_RC(rc, phy_direct_reg_rd(dev, offset, value));
    } else if (bank <= LAN8770_PHY_BANK_INSTRUMENT) {
        uint16_t regdata = 0, timeout = 200;

        regdata = offset;
        regdata |= LAN8770_EXT_REG_CTRL_REG_BANK_SET(bank);
        regdata |= LAN8770_EXT_REG_CTRL_WRT_CTRL;
        MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_EXT_REG_CTRL_OFFSET, regdata));
        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_CTRL_OFFSET, &regdata));
        while (regdata & LAN8770_EXT_REG_CTRL_READ_CTRL) {
            MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_CTRL_OFFSET, &regdata));
            timeout--;
            if (timeout) {
                MEPA_NSLEEP(10);
            }
        };

        if (!timeout) {
            T_E(MEPA_TRACE_GRP_GEN, "PHY bank register read timeout\r\n");
            rc = MEPA_RC_ERROR;
            goto error;
        }

        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_RD_DATA, value));
    } else {
        rc = MEPA_RC_ERR_PARM;
    }

error:
    return rc;
}

static mepa_rc phy_ext_bank_reg_wr(mepa_device_t *const dev, uint16_t const bank, uint16_t const offset, uint16_t const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (bank == LAN8770_PHY_BANK_SMI) {
        MEPA_RC(rc, phy_direct_reg_wr(dev, offset, value));
    } else if (bank <= LAN8770_PHY_BANK_INSTRUMENT) {
        uint16_t regdata = 0, timeout = 200;

        regdata = offset;
        regdata |= LAN8770_EXT_REG_CTRL_REG_BANK_SET(bank);
        regdata |= LAN8770_EXT_REG_CTRL_WRT_CTRL;
        MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_EXT_REG_WR_DATA, value));
        MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_EXT_REG_CTRL_OFFSET, regdata));

        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_CTRL_OFFSET, &regdata));
        while (regdata & LAN8770_EXT_REG_CTRL_WRT_CTRL) {
            MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_CTRL_OFFSET, &regdata));
            timeout--;
            if (timeout) {
                MEPA_NSLEEP(10);
            }
        };

        if (!timeout) {
            T_E(MEPA_TRACE_GRP_GEN, "PHY bank register write timeout\r\n");
            rc = MEPA_RC_ERROR;
            goto error;
        }

    } else {
        rc = MEPA_RC_ERR_PARM;
    }

error:
    return rc;
}

static mepa_rc phy_read_mod_write_register(mepa_device_t *const dev, uint16_t const phy_bank, uint16_t const offset, uint16_t const value, uint16_t const mask)
{
    uint16_t val = 0x0;
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, phy_bank, offset, &val));
    val = (val & (mask ^ 0xFFFF)) | value;
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, phy_bank, offset, val));

error:
    return rc;
}

// LAN8770 Driver Helper APIs

static mepa_rc phy_init_conf(mepa_device_t *const dev, mepa_bool_t master)
{
    mepa_rc rc = MEPA_RC_ERROR;
    uint16_t intr_val, intr2_val;
    uint16_t value = 0, timeout = 200;

    /* Remember previous interrupt settings. */
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_INTR_MASK_OFFSET, &intr_val));
    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_INT2_MASK_OFFSET, &intr2_val));

    /**** HW_INIT LOW ***/
    MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_POWER_DOWN_CTRL_OFFSET, LAN8770_POWER_DOWN_CTRL_FORCE_TX_EN));

    /*** SOFT RESET ***/
    MEPA_RC(rc, phy_direct_read_mod_write_register(dev, LAN8770_BASIC_CONTROL_OFFSET, LAN8770_BASIC_CTRL_SW_RESET, LAN8770_BASIC_CTRL_SW_RESET));
    MEPA_NSLEEP(100);

    /*** SET MASTER/SLAVE ***/
    value = ( LAN8770_MASTER_SLAVE_CTRL_MAN_CFG_EN |
              (master ? LAN8770_MASTER_SLAVE_CTRL_MAN_CFG_VAL : 0x0) );
    MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_MASTER_SLAVE_CTRL_OFFSET, value));

    /*** SOFT RESET ***/
    MEPA_RC(rc, phy_direct_read_mod_write_register(dev, LAN8770_BASIC_CONTROL_OFFSET, LAN8770_BASIC_CTRL_SW_RESET, LAN8770_BASIC_CTRL_SW_RESET));
    MEPA_NSLEEP(100);

    /*** Script 13v ****/

    /* Script Wrapper */
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_AFE, LAN8770_AFE_PORT_CFG1_OFFSET, 0x002B));
    MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_POWER_DOWN_CTRL_OFFSET, 0x0308));

    /* Auto Polarity */
    MEPA_RC(rc, phy_direct_read_mod_write_register(dev, LAN8770_PCS_CTRL_OFFSET, 0x0000, 0x0380));

    /* Slave DSP Config */
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MASTER_SLAVE_STATUS_OFFSET, &value));
    if ((value & LAN8770_MASTER_SLAVE_STATUS_CFG_RESOL) == 0) {
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_EQ_FD_STG1_FRZ_CFG, 0x0002));
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_EQ_FD_STG2_FRZ_CFG, 0x0002));
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_EQ_FD_STG3_FRZ_CFG, 0x0002));
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_EQ_FD_STG4_FRZ_CFG, 0x0002));
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_EQ_WT_FD_LCK_FRZ_CFG, 0x0002));
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_PST_EQ_LCK_STG1_FRZ_CFG, 0x0002));
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_DFE_TAP1_INIT_COEF, 0x0014));
        /* Auto polarity fix */
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_PCS, LAN8770_PCS_DESCM_CONTROL0, 0x6FFF));
    }

    /* DSP Config */
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CDR_CFG_PRE_LOCK, 0x0AB1));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CDR_CFG_POST_LOCK, 0x0AB3));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_EQU_LOCK_STG1_THR, 0x5274));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_SLV_HD_MULT_CFG, 0x0D74));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_SLV_FD_MULT_CFG, 0x0D53));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_COEF_PROT_DIS, 0x0360));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_KP_LOOP_SAT_CFG, 0x0C30));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_LCK_STG2_MUFACT_CFG, 0x0AEA));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_LCK_STG3_MUFACT_CFG, 0x0AEB));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_POST_LCK_MUFACT_CFG, 0x0AEB));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_TX_RX_FIFO_CFG, 0x1C00));

    /* TX IIR */
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1000));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1821));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1021));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1842));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1042));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1863));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1063));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x18a4));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x10a4));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x18c5));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x10c5));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x18e6));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x10e6));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x18c7));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x10c7));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x18c8));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x10c8));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1889));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1089));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x184a));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x104a));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x180b));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x100b));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x180c));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x100c));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x180d));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x100d));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x180e));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x100e));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x180f));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x100f));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1810));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1010));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1811));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1011));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_TX_LPF_FIR_CFG, 0x1000));

    /* SQI Enable  */
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_SQI_CONFIG, 0x9572));

    /* Flag LPS and WUR as idle errors  */
    MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_MDIO_CTRL2_OFFSET, 0x0014));

    /* Script Wrapper */
    MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_POWER_DOWN_CTRL_OFFSET, 0x0200));
    MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_MDIO_CTRL2_OFFSET, 0x0094));
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MDIO_CTRL2_OFFSET, &value));
    while ((value & 0x0080) == 0x0080) {
        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MDIO_CTRL2_OFFSET, &value));
        timeout--;
        if (timeout) {
            MEPA_NSLEEP(10);
        }
    }
    if (!timeout) {
        T_E( MEPA_TRACE_GRP_GEN, "PHY Init timeout.\r\n");
        rc = MEPA_RC_ERROR;
        goto error;
    }
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_AFE, LAN8770_AFE_PORT_CFG1_OFFSET, 0x000A));
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_INTR_SRC_OFFSET, &value));
    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_INT2_SRC_OFFSET, &value));
    /******************/

    /* TC10 */
    // Turn on ROSC
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, 0x0020, 0x0020));
    // Set WUR and LPS detect length
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_PCS, LAN8770_PCS_SLEEP_WAKE_DET_OFFSET, 0x3C3C));
    // Enable LPS/WUR detection in idles
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_MDIO_CTRL2_OFFSET, 0x0020, 0x0020));
    //Set WAKE_IN debounce length
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL1_OFFSET, 0x2700, 0xFF00));
    //Sleep en, INH en, WI debouce units, write to VBAT domain
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, 0x8006, 0x800E));
    //// Write to VBAT domain, WUP digital filt, WUP debouce units, WUP debounce units
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_PRT_CTL1_OFFSET, 0xD010));
    // Fix for Slave TXPD in sleep silent (does not need to be written to VBAT domain)
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_PRT_CTL2_OFFSET, 0x0020, 0x0020));
    //EnableRemoteWakeupReaction
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_PRT_CTL1_OFFSET, 0x8100, 0x8100));
    //set wake out len
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL1_OFFSET, 0x0064, 0x0064));

    /* Enable interrupts again. */
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_INTR_MASK_OFFSET, &value));
    if (value != intr_val) {
        MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_INTR_MASK_OFFSET, intr_val));
    }
    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_INT2_MASK_OFFSET, &value));
    if (value != intr2_val) {
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_INT2_MASK_OFFSET, intr2_val));
    }

    /* HW_INIT HIGH */
    MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_POWER_DOWN_CTRL_OFFSET, (LAN8770_POWER_DOWN_CTRL_FORCE_TX_EN | LAN8770_POWER_DOWN_CTRL_HW_INIT_EN)));

error:
    return rc;
}

static mepa_rc phy_get_device_info(mepa_device_t *const dev)
{
    uint16_t val = 0;
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_PHY_ID1_OFFSET, &val));
    /**
     *  PHY_ID_NUM0: Assigned to the 3rd through 18th bits of the Organizationally Unique Identifier (OUI), respectively.
     */
    data->dev.id = LAN8770_PHY_ID_NUM0(val);

    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_PHY_ID2_OFFSET, &val));
    data->dev.rev   = LAN8770_PHY_REV_NUM(val);
    data->dev.model = LAN8770_PHY_MODEL_NUM(val);
    /**
     *  PHY_ID_NUM1: Assigned to the 19th through 24th bits of the OUI.
     */
    data->dev.id |= LAN8770_PHY_ID_NUM1(val);

    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MASTER_SLAVE_STATUS_OFFSET, &val));
    data->dev.is_master = LAN8770_MASTER_SLAVE_STATUS_IS_MASTER(val);
    data->dev.is_master_fault = LAN8770_MASTER_SLAVE_STATUS_IS_FAULT(val);

    T_D(MEPA_TRACE_GRP_GEN, "phy_info phy_id=0x%x, mode=%s[fault=%u],"
        "model=0x%x, rev=%u, error=%d  \r\n",
        data->dev.id, (data->dev.is_master == TRUE ? "master" : "slave"),
        data->dev.is_master_fault, data->dev.model, data->dev.rev, rc);
error:
    return rc;
}

static mepa_rc phy_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    uint16_t regval = 0;
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_manual_neg_t curr_val = ((config->man_neg == MEPA_MANUAL_NEG_REF) ? MEPA_MANUAL_NEG_REF : MEPA_MANUAL_NEG_CLIENT);
    /**
     * NOTE: Following are always fixed. Change in conf set will be ignored.
     *  speed = 100Mbps
     *  auto-neg always disabled
     *  fdx always enabled.
     */
    if (!(config->man_neg == MEPA_MANUAL_NEG_REF || config->man_neg == MEPA_MANUAL_NEG_CLIENT) ||
        (config->fdx != TRUE) || (config->speed != MESA_SPEED_100M) || (config->mac_if_aneg_ena != FALSE)) {
        T_E(MEPA_TRACE_GRP_GEN, "Invalid configuration Parameters\r\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    data->conf.speed = MESA_SPEED_100M;
    data->conf.fdx = TRUE;
    data->conf.mac_if_aneg_ena = FALSE;
    data->conf.flow_control = config->flow_control;

    if (!data->init_done) {
        MEPA_RC(rc, phy_init_conf(dev, (config->man_neg == MEPA_MANUAL_NEG_REF)));
        data->init_done = TRUE;

        regval = config->admin.enable ? 0x0 : LAN8770_BASIC_CTRL_POWER_DOWN;
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_BASIC_CONTROL_OFFSET, regval, LAN8770_BASIC_CTRL_POWER_DOWN));

        data->conf.man_neg = config->man_neg;
        data->conf.admin.enable = config->admin.enable;
    }

    if (data->conf.man_neg != config->man_neg) {
        MEPA_RC(rc, phy_init_conf(dev, (config->man_neg == MEPA_MANUAL_NEG_REF)));
    }

    if (data->conf.admin.enable != config->admin.enable) {
        regval = config->admin.enable ? 0x0 : LAN8770_BASIC_CTRL_POWER_DOWN;
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_BASIC_CONTROL_OFFSET, regval, LAN8770_BASIC_CTRL_POWER_DOWN));
    }

    data->conf.admin        = config->admin;
    data->conf.man_neg      = curr_val;

error:
    return rc;
}

static mepa_rc phy_get_link_status_enhanced(mepa_device_t *const dev, mepa_status_t *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t reg_0A_data = 0, reg_11_data = 0, pcs_descram_st = 0;

    /* bit 12 remote recceiver status; bit 13 local receiver status */
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MASTER_SLAVE_STATUS_OFFSET, &reg_0A_data));
    /*bit 0 link status; bit 2:1 tx mode status; bit 3 scrambler lock status*/
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MODE_STATUS_OFFSET, &reg_11_data));
    /* get pcs descrambler state */
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, LAN8770_BIT(11U), LAN8770_BIT(11U)));
    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_PCS, LAN8770_PCS_DEBUG_BUS_STS_OFFSET, &pcs_descram_st));

    status->link = LAN8770_LINKDOWN;

    if (((reg_0A_data & 0x3000) == 0x3000) && ((reg_11_data & 0x0D) == 0x0D)) {
        status->link = LAN8770_LINKUP;
        status->speed = data->conf.speed;
        status->fdx = data->conf.fdx;
    }
    T_D( MEPA_TRACE_GRP_GEN, "status link=%u, speed=%u, fdx=%u  \r\n", status->link, status->speed, status->fdx);
    data->link_status = status->link;

error:
    return rc;
}

static mepa_rc phy_cable_diag_start(mepa_device_t *dev, int32_t mode)
{
    uint16_t tempReg = 0;
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (!data->init_done) {
        T_E(MEPA_TRACE_GRP_GEN, "PHY not initilized\r\n");
        return MEPA_RC_INV_STATE;
    }

    /*** SOFT RESET ***/
    MEPA_RC(rc, phy_direct_read_mod_write_register(dev, LAN8770_BASIC_CONTROL_OFFSET, LAN8770_BASIC_CTRL_SW_RESET, LAN8770_BASIC_CTRL_SW_RESET));
    MEPA_NSLEEP(100);

    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_POWER_DOWN_CTRL_OFFSET,
                                            LAN8770_POWER_DOWN_CTRL_HW_INIT_EN, LAN8770_POWER_DOWN_CTRL_HW_INIT_EN));
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_BASIC_CONTROL_OFFSET, &tempReg));
    // check if part is alive - if not, return diagnostic error
    if (tempReg !=  (LAN8770_BASIC_CTRL_DUPLEX_MODE | LAN8770_BASIC_CTRL_SPEED_SEL_LSB)/*0x2100*/) {
        T_E(MEPA_TRACE_GRP_GEN, "PHY diagnositc error\r\n");
        rc = MEPA_RC_ERROR;
        return rc;
    }
    tempReg = 0;
    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MASTER_SLAVE_STATUS_OFFSET, &tempReg));
    // master/slave specific writes
    /* Local PHY configuration resolved to Slave */
    if ((tempReg & LAN8770_MASTER_SLAVE_STATUS_CFG_RESOL /*0x4000*/) != LAN8770_MASTER_SLAVE_STATUS_CFG_RESOL /*0x4000*/) {
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_AFE, LAN8770_AFE_AFE_PORT_CFG4_OFFSET, 0x0005, 0x0007));
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_POWER_DOWN_CTRL_OFFSET, 0x0008, 0x0008));
    } else { /* Local PHY configuration resolved to Master */
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_MDIO_CTRL2_OFFSET, 0x0, LAN8770_MDIO_CTRL2_EN_DET_MST_MODE));
    }

    // DSP configuration
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_MIN_WAIT_CFG, 0));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_MAX_WAIT_CFG, 10));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_CYC_WAIT_CFG, 90));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_PGA_THR, 60));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_MAX_PGA_GAIN, 31));

    // clock align for each iteration
    MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CALIB_CFG, 0x0000, 0x0038));
    MEPA_NSLEEP(50000);
    // max cycle wait config
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_MAX_WAIT_CFG, 70));
    // start cable diag
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_STS_CTL, 0x01));

    data->cdiags_start = TRUE;

error:
    return rc;
}

static mepa_rc phy_cable_diag_get(mepa_device_t *const dev, mepa_cable_diag_result_t *const res)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (!data->init_done) {
        T_E( MEPA_TRACE_GRP_GEN, "PHY not initilized\r\n");
        return MEPA_RC_INV_STATE;
    }

    res->link = data->link_status;
    if (data->link_status == LAN8770_LINKUP) {
        res->length[0] = 0;// cannot measure length
        res->status[0] = MESA_VERIPHY_STATUS_OK;
        rc = phy_read_mod_write_register(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_STS_CTL, FALSE, FALSE);
    } else if (data->cdiags_start) {
        uint16_t gainIdx = 0, posPeak = 0, negPeak = 0, posPeakTime = 0, negPeakTime = 0;
        uint16_t posPeakInPhasesHybrid = 0;
        uint16_t posPeakCycle = 0, posPeakInPhases = 0, posPeakPhase = 0, negPeakCycle = 0, negPeakInPhases = 0, negPeakPhase = 0;
        float wavePropagationVelocity = 0.6811 * 2.9979;
        uint16_t detect = 1;
        float distance = -1;
        uint16_t noiseMargin = 20, timeMargin = 89, maxDistance = 35, jitterVariation = 30;
        uint16_t minTimeDifference = 96, maxTimeDifference = 96 + timeMargin;
        mepa_bool_t bDone = FALSE;
        mepa_bool_t diagTimeout = FALSE;
        mepa_bool_t bFault = FALSE;

        mepa_mtimer_t   timer;
        MEPA_MTIMER_START(&timer, 4000);

        res->status[0] = MESA_VERIPHY_STATUS_ABNORM;
        // wait for cable diag to finish or timeout (4 seconds)
        while (!(bDone | diagTimeout)) {
            uint16_t tmp = 0;

            diagTimeout = MEPA_MTIMER_TIMEOUT(&timer);

            T_I( MEPA_TRACE_GRP_GEN, "cable_diag ctrl 0x%x  \r\n", tmp);

            MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_STS_CTL, &tmp));
            T_D( MEPA_TRACE_GRP_GEN, "cable_diag ctrl 0x%x  \r\n", tmp);
            if ((tmp & 2) == 2) {
                bDone = TRUE;
            }
        }
        // return diagnostic error if timeout occurred
        if (diagTimeout == TRUE) {
            T_E( MEPA_TRACE_GRP_GEN, "PHY diags error\r\n");
            rc = MEPA_RC_INCOMPLETE;
            goto error;
        } else {
            // stop cable diag (clear start bit)
            MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_STS_CTL, 0x0));
        }
        if (diagTimeout == FALSE) {
            // read non-hybrid results
            MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_GAIN_IDX, &gainIdx));

            MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_PEAK, &posPeak));

            MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_NEG_PEAK, &negPeak));

            MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_PEAK_TIME, &posPeakTime));

            MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_CABLE_DIAG_NEG_PEAK_TIME, &negPeakTime));

            // calculate non-hybrid values
            posPeakCycle = (posPeakTime >> 7) & 0x7F;
            posPeakPhase = posPeakTime & 0x7F;
            posPeakInPhases = (posPeakCycle * 96) + posPeakPhase;
            negPeakCycle = (negPeakTime >> 7) & 0x7F;
            negPeakPhase = negPeakTime & 0x7F;
            negPeakInPhases = (negPeakCycle * 96) + negPeakPhase;

            // process values
            if ((posPeakInPhases > negPeakInPhases) &&
                ((posPeakInPhases - negPeakInPhases) >= minTimeDifference) &&
                ((posPeakInPhases - negPeakInPhases) < maxTimeDifference) &&
                (posPeakInPhasesHybrid < posPeakInPhases) &&
                (posPeakInPhasesHybrid < (negPeakInPhases + jitterVariation))) {
                detect = 2;
                distance = (negPeakInPhases - posPeakInPhasesHybrid) * 156.2499 * 0.0001 * wavePropagationVelocity * 0.5;
            } else if ((negPeakInPhases > posPeakInPhases) &&
                       ((negPeakInPhases - posPeakInPhases) >= minTimeDifference) &&
                       ((negPeakInPhases - posPeakInPhases) < maxTimeDifference) &&
                       (posPeakInPhasesHybrid < negPeakInPhases) &&
                       (posPeakInPhasesHybrid < (posPeakInPhases + jitterVariation))) {
                detect = 1;
                distance = (posPeakInPhases - posPeakInPhasesHybrid) * 156.2499 * 0.0001 * wavePropagationVelocity * 0.5;
            }

            if ((posPeak > noiseMargin) && (negPeak > noiseMargin) && (distance < maxDistance) && (gainIdx >= 0)) {
                if ((detect == 1) || (detect == 2)) {
                    bFault = TRUE;
                }
            }
            rc = MEPA_RC_OK;

            if (bFault == FALSE) {
                detect = 0;
                distance = 0;
            }

            // Set cable length
            res->length[0] = ((uint8_t)distance) & 0xFF;

            // Set status
            switch (detect) {
            case 0:
                res->status[0] = MESA_VERIPHY_STATUS_OK;
                break;
            case 1:
                res->status[0] = MESA_VERIPHY_STATUS_OPEN;
                break;
            case 2:
                res->status[0] = MESA_VERIPHY_STATUS_SHORT;
                break;
            default:
                res->status[0] = MESA_VERIPHY_STATUS_ABNORM;
                break;
            }
            data->cdiags_start = FALSE;
        }
    } else {
        rc = MEPA_RC_INV_STATE;
    }

error:
    return rc;
}

static uint16_t phy_convert_led_mode(mepa_gpio_mode_t const mode, mepa_bool_t master)
{
    uint16_t ret = 0;

    switch (mode) {
    case MEPA_GPIO_MODE_LED_ACTIVITY:
    case MEPA_GPIO_MODE_LED_LINK100_ACTIVITY:
    case MEPA_GPIO_MODE_LED_LINK100BASE_FX_ACTIVITY:
    case MEPA_GPIO_MODE_LED_LINK_ACTIVITY:
        ret |= LAN8770_MISC_CTRL_0_LED_MODE_ACTIVITY;
        break;
    case MEPA_GPIO_MODE_LED_FORCE_LED_ON:
        ret |= (master == TRUE ? LAN8770_MISC_CTRL_0_LED_MODE_MASTER : LAN8770_MISC_CTRL_0_LED_MODE_SLAVE);
        break;
    case MEPA_GPIO_MODE_LED_LINK_RX:
        ret |= LAN8770_MISC_CTRL_0_LED_MODE_RX_ACTIVITY;
        break;
    case MEPA_GPIO_MODE_LED_LINK_TX:
        ret |= LAN8770_MISC_CTRL_0_LED_MODE_TX_ACTIVITY;
        break;
    default:
        ret = LAN8770_MISC_CTRL_0_LED_DIS; // disable LED lan8770
        break;
    }

    return ret;
}

static mepa_rc phy_led_mode_set(mepa_device_t *const dev, mepa_gpio_mode_t const led_mode, mepa_led_num_t const led_num)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *) dev->data;

    uint16_t led_ctrl = phy_convert_led_mode(led_mode, data->dev.is_master);

    rc = phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_CTRL_0_OFFSET, led_ctrl);

    T_I( MEPA_TRACE_GRP_GEN, "led_mode_set led_mode=%u, led_ctrl=%u, ret_code=%d \r\n", led_mode, led_ctrl, rc);

    return rc;
}

static void phy_dbg_pr (mepa_device_t *dev, const mepa_debug_print_t pr,
                        uint16_t bank, uint16_t offset, const char *str)
{
    if (pr != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;
        mepa_port_no_t port_no = data->port_no;
        uint16_t value = 0;
        if (MEPA_RC_OK == phy_ext_bank_reg_rd(dev, bank, offset, &value)) {
            pr("%-45s:\t%-2u  %u.%-4u = %u \r\n", str, port_no, bank, offset, value);
        }
    }
}

static mepa_rc phy_reg_dump(struct mepa_device *dev,
                            const mepa_debug_print_t pr)
{
    //Direct registers
    pr("%-45s:\tPORT\tPAGE\tREG\tVALUE \r\n", "REG_NAME");
    pr("SMI Main Registers\r\n");
    phy_dbg_pr(dev, pr, 0, 0, "Basic Control Register");
    phy_dbg_pr(dev, pr, 0, 1, "Basic Status Register");
    phy_dbg_pr(dev, pr, 0, 2, "PHY Identifier 1 Register");
    phy_dbg_pr(dev, pr, 0, 3, "PHY Identifier 2 Register");
    phy_dbg_pr(dev, pr, 0, 9, "Master Slave Control Register");
    phy_dbg_pr(dev, pr, 0, 10, "Master Slave Status Register");
    phy_dbg_pr(dev, pr, 0, 15, "MDIO Control 1 Register");
    phy_dbg_pr(dev, pr, 0, 16, "MDIO Control 2 Register");
    phy_dbg_pr(dev, pr, 0, 17, "Mode Status Register");
    phy_dbg_pr(dev, pr, 0, 18, "Loopback Control Register");
    phy_dbg_pr(dev, pr, 0, 19, "Reset Control Register");
    phy_dbg_pr(dev, pr, 0, 20, "External Register Control Register");
    phy_dbg_pr(dev, pr, 0, 21, "External Register Read Data Register");
    phy_dbg_pr(dev, pr, 0, 22, "External Register Write Data Register");
    phy_dbg_pr(dev, pr, 0, 23, "PCS Control Register");
    phy_dbg_pr(dev, pr, 0, 24, "Interrupt Source Register");
    phy_dbg_pr(dev, pr, 0, 25, "Interrupt Mask Register");
    phy_dbg_pr(dev, pr, 0, 26, "Power Down Control Register");
    phy_dbg_pr(dev, pr, 0, 27, "BIST Control Register");
    phy_dbg_pr(dev, pr, 0, 28, "BIST Status Register");
    phy_dbg_pr(dev, pr, 0, 29, "BIST Error Count Status Register");
    phy_dbg_pr(dev, pr, 0, 30, "PCS Receive Error Count Status Register");
    phy_dbg_pr(dev, pr, 0, 31, "Test Control Status Register");
    pr("Miscellaneous Registers\r\n");
    phy_dbg_pr(dev, pr, 1, 0x10, "Control 0 Register");
    phy_dbg_pr(dev, pr, 1, 0x11, "Control 1 Register");
    phy_dbg_pr(dev, pr, 1, 0x15, "Control 2 Register");
    phy_dbg_pr(dev, pr, 1, 0x17, "Control 3 Register");
    phy_dbg_pr(dev, pr, 1, 0x1A, "DCQ Error Max Register");
    phy_dbg_pr(dev, pr, 1, 0x20, "Wakeup Common Control 0 Register");
    phy_dbg_pr(dev, pr, 1, 0x21, "Wakeup Common Control 1 Register");
    phy_dbg_pr(dev, pr, 1, 0x24, "Wakeup Port Control Register");
    pr("PCS and Energy Registers\r\n");
    phy_dbg_pr(dev, pr, 2, 0x20, "Sleep Wake Detect Register");
    pr("AFE Registers\r\n");
    pr("DSP Registers\r\n");

    return MEPA_RC_OK;
}

static mepa_rc phy_sqi_read(mepa_device_t *const dev, uint32_t *const value)
{
    uint16_t temp;
    int i, j;
    float sqiAvg = 0, linkAvg = 0;
    uint32_t sqiNum = 0;
    uint16_t rawTable[200];
    uint16_t linkTable[200];
    mepa_status_t status;
    phy_data_t *data = (phy_data_t *) dev->data;
    mepa_rc rc = MEPA_RC_ERROR;

    if (!data->init_done) {
        T_E( MEPA_TRACE_GRP_GEN, "PHY not initilized\r\n");
        return MEPA_RC_INV_STATE;
    }

    memset(rawTable, 0, sizeof(rawTable));
    memset(linkTable, 1, sizeof(linkTable));

    MEPA_RC(rc, phy_get_link_status_enhanced(dev, &status));
    if (status.link == LAN8770_LINKUP) {
        // method 1 config
        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, 0x04, 0x16D6));

        MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_DSP, 0x2E, 0x9572));

        MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_DSP, 0x2E, &temp));

        if (temp != 0x9572) {
            T_E( MEPA_TRACE_GRP_GEN, "PHY invalid mode\r\n");
            rc = MEPA_RC_INCOMPLETE;
            goto error;
        }

        // update DSP d130/131
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_DSP,
                                                LAN8770_DSP_COEF_RW_CTL_CFG_OFFSET,
                                                LAN8770_DSP_COEF_RW_CTL_CFG_POKE_DIS,
                                                LAN8770_DSP_COEF_RW_CTL_CFG_POKE_DIS ));

        MEPA_NSLEEP(50000);

        // get 200 raw readings
        for (i = 0; i < 200; i++) {
            MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_DSP,
                                                    LAN8770_DSP_COEF_RW_CTL_CFG_OFFSET,
                                                    LAN8770_DSP_COEF_RW_CTL_CFG_POKE_DIS,
                                                    LAN8770_DSP_COEF_RW_CTL_CFG_POKE_DIS));

            MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_DSP, LAN8770_DSP_SQI_SQU_MEAN_MSB_OFFSET, &temp));
            rawTable[i] = temp;
            MEPA_RC(rc, phy_get_link_status_enhanced(dev, &status));
            linkTable[i] = status.link;
        }

        // sort raw sqi values in ascending order
        for (i = 0; i < 200; i++) {
            for (j = 0; j < 200; j++) {
                if (rawTable[j] > rawTable[i]) {
                    temp = rawTable[i]; // sqi values
                    rawTable[i] = rawTable[j];
                    rawTable[j] = temp;

                    uint16_t linkTemp = linkTable[i]; // link statuses
                    linkTable[i] = linkTable[j];
                    linkTable[j] = linkTemp;
                }
            }
        }
        // sum middle 120 values
        for (i = 0; i < 200; i++) {
            if ((i >= 40) && (i < 160)) {
                sqiAvg += rawTable[i];
            }
            linkAvg += linkTable[i];
        }

        // get averages
        sqiAvg /= 120;
        linkAvg /= 200;

        if (sqiAvg >= 299) {
            sqiNum = 0;
        } else if ((sqiAvg < 299) && (sqiAvg >= 237)) {
            sqiNum = 1;
        } else if ((sqiAvg < 237) && (sqiAvg >= 189)) {
            sqiNum = 2;
        } else if ((sqiAvg < 189) && (sqiAvg >= 150)) {
            sqiNum = 3;
        } else if ((sqiAvg < 150) && (sqiAvg >= 119)) {
            sqiNum = 4;
        } else if ((sqiAvg < 119) && (sqiAvg >= 94)) {
            sqiNum = 5;
        } else if ((sqiAvg < 94) && (sqiAvg >= 75)) {
            sqiNum = 6;
        } else if ((sqiAvg < 75) && (sqiAvg >= 0)) {
            sqiNum = 7;
        } else {
            sqiNum = 8;
        }

        if (linkAvg < 1) {
            sqiNum = 0;
        }
    }

error:
    *value = sqiNum;

    return rc;
}


// LAN8770 Driver MEPA APIs

static mepa_rc lan8770_delete(mepa_device_t *const dev)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_ENTER(dev);

    data->ctx_status = FALSE;
    memset(data, 0, sizeof(phy_data_t));

    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc lan8770_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_ENTER(dev);

    T_I(MEPA_TRACE_GRP_GEN, "Reseting and Configuring PHY\r\n");

    MEPA_RC(rc, phy_init_conf(dev, (data->conf.man_neg == MEPA_MANUAL_NEG_REF)));
    data->init_done = TRUE;
    MEPA_RC(rc, phy_get_device_info(dev));
    MEPA_RC(rc, phy_conf_set(dev, &data->conf));

error:
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan8770_poll(mepa_device_t *const dev, mepa_status_t *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_get_link_status_enhanced(dev, status);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_conf_set(dev, config);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_conf_get(mepa_device_t *const dev, mepa_conf_t *const config)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    *config = data->conf;

    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc lan8770_media_get(struct mepa_device *dev, mepa_media_interface_t *const media_if)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    *media_if = data->media_intf;

    MEPA_EXIT(dev);

    T_D( MEPA_TRACE_GRP_GEN, "media type %d\r\n", *media_if);

    return MEPA_RC_OK;
}

static mepa_rc lan8770_cable_diag_start(mepa_device_t *dev, int32_t mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_cable_diag_start(dev, mode);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_cable_diag_get(mepa_device_t *const dev, mepa_cable_diag_result_t *const res)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_cable_diag_get(dev, res);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_device_t *lan8770_probe(mepa_driver_t *drv,
                                    const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                    struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                    struct mepa_board_conf                  *conf)
{
    uint8_t pidx = 0;

    for (pidx = 0; pidx < MAX_LAN8770_PHY; pidx++) {
        if (lan8770_data[pidx].ctx_status) {
            continue;
        }

        lan8770_device[pidx].drv = drv;
        lan8770_device[pidx].data = (void *)&lan8770_data[pidx];
        lan8770_device[pidx].callout = callout;
        lan8770_device[pidx].callout_ctx = callout_ctx;

        lan8770_data[pidx].ctx_status = TRUE;
        lan8770_data[pidx].port_no = conf->numeric_handle;
        lan8770_data[pidx].init_done = FALSE;
        lan8770_data[pidx].events = 0;
        lan8770_data[pidx].conf.man_neg = MEPA_MANUAL_NEG_REF;
        lan8770_data[pidx].conf.admin.enable = TRUE;
        lan8770_data[pidx].conf.speed = MESA_SPEED_100M;
        lan8770_data[pidx].conf.fdx = TRUE;
        lan8770_data[pidx].conf.mac_if_aneg_ena = FALSE;
        lan8770_data[pidx].media_intf = MESA_PHY_MEDIA_IF_T1_100FX;
        lan8770_data[pidx].mac_if = MESA_PORT_INTERFACE_INTERNAL;

        T_I(MEPA_TRACE_GRP_GEN, "LAN8770 driver probed for port %u  \r\n", lan8770_data[pidx].port_no);

        return &lan8770_device[pidx];
    }

    T_E(MEPA_TRACE_GRP_GEN, "MAX LAN8770 probed\r\n");
    return NULL;
}

static mepa_rc lan8770_direct_reg_read(mepa_device_t *const dev, uint32_t const addr, uint16_t *const value)
{
    mepa_rc rc = MESA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_direct_reg_rd(dev, LAN8770_PHY_REG_ADDR(addr), value);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_direct_reg_write(mepa_device_t *const dev, uint32_t const addr, uint16_t const value)
{
    mepa_rc rc = MESA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_direct_reg_wr(dev, LAN8770_PHY_REG_ADDR(addr), value);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_ext_bank_reg_read(mepa_device_t *const dev, uint32_t const addr, uint16_t *const value)
{
    mepa_rc rc = MESA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_ext_bank_reg_rd(dev, LAN8770_PHY_EXT_BANK(addr), LAN8770_PHY_REG_ADDR(addr), value);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_ext_bank_reg_write(mepa_device_t *const dev, uint32_t const addr, uint16_t const value)
{
    mepa_rc rc = MESA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_ext_bank_reg_wr(dev, LAN8770_PHY_EXT_BANK(addr), LAN8770_PHY_REG_ADDR(addr), value);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_event_enable_set(mepa_device_t *const dev, mepa_event_t const event, mepa_bool_t const enable)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t ev_mask = 0, i;
    phy_data_t *data = (phy_data_t *)dev->data;

    data->events = enable ? (data->events | event) :
                   (data->events & ~event);

    MEPA_ENTER(dev);

    for (i = 0; i < INTR_BIT_LEN; i++) {
        if (event & LAN8770_BIT(i)) {
            ev_mask = ev_mask |  LAN8770_BIT(i);
        }
    }
    rc = phy_direct_reg_wr(dev, LAN8770_INTR_MASK_OFFSET, ev_mask);

    MEPA_EXIT(dev);

    T_D( MEPA_TRACE_GRP_GEN, "set events 0x%x! rc=%d\r\n", data->events, rc);
    return rc;
}

static mepa_rc lan8770_event_enable_get(mepa_device_t *const dev, mepa_event_t *const event)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    *event = data->events;

    MEPA_EXIT(dev);
    T_D( MEPA_TRACE_GRP_GEN, "events configured 0x%x \r\n", *event);

    return MEPA_RC_OK;
}

static mepa_rc lan8770_event_status_poll(mepa_device_t *const dev, mepa_event_t *const status)
{
    uint16_t val = 0;
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    rc = phy_direct_reg_rd(dev, LAN8770_INTR_SRC_OFFSET, &val);
    *status = val;

    MEPA_EXIT(dev);
    T_D( MEPA_TRACE_GRP_GEN, "events=0x%x polled 0x%x \r\n", data->events, *status);
    return rc;
}

/**
 * Loopback Modes:
 * MAC Loopback: Digital loopback at PCS.
 * PMA Loopback: Analog loopback inside AFE.
 * Far End Loopback: Loopback from wire to PCS and back to wire.
**/
static mepa_rc lan8770_loopback_set(mepa_device_t *dev, const mepa_loopback_t *loopback)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    // En(Dis)able MAC Loopback: Digital loopback at PCS
    if (loopback->near_end_ena == TRUE) {
        uint16_t val = 0;
        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_BASIC_CONTROL_OFFSET, &val));
        val |= LAN8770_BASIC_CTRL_PCS_LOOPBACK;
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_BASIC_CONTROL_OFFSET, val, val));
    } else if (data->loopback.near_end_ena == TRUE) {
        uint16_t val = 0;
        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_BASIC_CONTROL_OFFSET, &val));
        val &= ~LAN8770_BASIC_CTRL_PCS_LOOPBACK;
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_BASIC_CONTROL_OFFSET, val, val));
    }

    // En(Dis)able Far End Loopback: Loopback from wire to PCS and back to wire.
    if (loopback->far_end_ena == TRUE) {
        uint16_t val = 0;
        MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, &val));
        val |= LAN8770_LPBK_CTRL_FAR;
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, val, val));
    } else if (data->loopback.far_end_ena == TRUE) {
        uint16_t val = 0;
        MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, &val));
        val &= ~LAN8770_LPBK_CTRL_FAR;
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, val, val));
    }

    // En(Dis)able PMA Loopback: Analog loopback inside AFE.
    if (loopback->connector_ena == TRUE) {
        uint16_t val = 0;
        MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, &val));
        val |= LAN8770_LPBK_CTRL_PMA;
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, val, val));
    } else if (data->loopback.connector_ena == TRUE) {
        uint16_t val = 0;
        MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, &val));
        val &= ~LAN8770_LPBK_CTRL_PMA;
        MEPA_RC(rc, phy_read_mod_write_register(dev, LAN8770_PHY_BANK_SMI, LAN8770_LOOPBACK_CTRL_OFFSET, val, val));
    }

    memcpy(&data->loopback, loopback, sizeof(data->loopback));

error:
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan8770_loopback_get(mepa_device_t *dev, mepa_loopback_t *const loopback)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    memcpy(loopback, &data->loopback, sizeof(mepa_loopback_t));

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

// Set gpio mode to input, output or alternate function
static mepa_rc lan8770_gpio_mode_set(mepa_device_t *dev, const mepa_gpio_conf_t *gpio_conf)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    MEPA_ENTER(dev);

    if ((gpio_conf != NULL) && ((gpio_conf->mode >= MEPA_GPIO_MODE_LED_LINK_ACTIVITY) && (gpio_conf->mode <= MEPA_GPIO_MODE_LED_DISABLE_EXTENDED))) {
        rc = phy_led_mode_set(dev, gpio_conf->mode, gpio_conf->led_num);
    }

    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan8770_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)(dev->data);

    if (data->init_done == 1U) {
        MEPA_ENTER(dev);
        phy_info->part_number = data->dev.model;
        phy_info->revision = data->dev.rev;
        phy_info->cap = (data->conf.speed == MESA_SPEED_100M ? MEPA_CAP_SPEED_MASK_1G : MEPA_CAP_TS_MASK_NONE);

        MEPA_EXIT(dev);
        rc = MEPA_RC_OK;
    }

    return rc;
}

static mepa_rc lan8770_isolate_mode_set(struct mepa_device *dev, mepa_bool_t const val)
{
    uint16_t reg_val = 0;
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_BASIC_CONTROL_OFFSET, &reg_val));
    //Enabled so set the bit
    if (val == TRUE) {
        reg_val |= LAN8770_BASIC_CTRL_ISOLATE;
    }
    //Disabled so clear the bit
    else {
        reg_val &= ~LAN8770_BASIC_CTRL_ISOLATE;
    }
    rc = phy_direct_reg_wr(dev, LAN8770_BASIC_CONTROL_OFFSET, reg_val);

error:
    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_debug_info(struct mepa_device *dev,
                                  const mepa_debug_print_t pr,
                                  const mepa_debug_info_t   *const info)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (pr != NULL) {
        //PHY Debugging
        switch (info->group) {
        case MEPA_DEBUG_GROUP_ALL:
        case MEPA_DEBUG_GROUP_PHY: {
            MEPA_ENTER(dev);
            rc = phy_reg_dump(dev, pr);
            MEPA_EXIT(dev);
        }
        break;
        default:
            rc = MEPA_RC_OK;
        }
    }
    return rc;
}

static mepa_rc lan8770_sqi_read(mepa_device_t *const dev, uint32_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_sqi_read(dev, value);

    MEPA_EXIT(dev);

    return rc;
}

mepa_drivers_t mepa_lan8770_driver_init()
{
    mepa_drivers_t result = {0};
    static const int nr_lan8770_drivers = LAN8770_PHY_ID_MAX;
    static mepa_driver_t lan8770_driver[LAN8770_PHY_ID_MAX] = {
        {
            .id = LAN8770_PHY_ID,           // LAN8770 PHY standalone
            .mask = LAN8770_PHY_ID_MASK,
            .mepa_driver_delete             = lan8770_delete,
            .mepa_driver_reset              = lan8770_reset,
            .mepa_driver_poll               = lan8770_poll,
            .mepa_driver_conf_set           = lan8770_conf_set,
            .mepa_driver_conf_get           = lan8770_conf_get,
            .mepa_driver_media_get          = lan8770_media_get,
            .mepa_driver_cable_diag_start   = lan8770_cable_diag_start,
            .mepa_driver_cable_diag_get     = lan8770_cable_diag_get,
            .mepa_driver_probe              = lan8770_probe,
            .mepa_driver_clause22_read      = lan8770_direct_reg_read,
            .mepa_driver_clause22_write     = lan8770_direct_reg_write,
            .mepa_driver_clause45_read      = lan8770_ext_bank_reg_read,
            .mepa_driver_clause45_write     = lan8770_ext_bank_reg_write,
            .mepa_driver_event_enable_set   = lan8770_event_enable_set,
            .mepa_driver_event_enable_get   = lan8770_event_enable_get,
            .mepa_driver_event_poll         = lan8770_event_status_poll,
            .mepa_driver_loopback_set       = lan8770_loopback_set,
            .mepa_driver_loopback_get       = lan8770_loopback_get,
            .mepa_driver_gpio_mode_set      = lan8770_gpio_mode_set,
            .mepa_driver_phy_info_get       = lan8770_info_get,
            .mepa_driver_isolate_mode_conf  = lan8770_isolate_mode_set,
            .mepa_debug_info_dump           = lan8770_debug_info,
            .mepa_driver_sqi_read           = lan8770_sqi_read,
        },
        {
            .id = LAN8770_PHY_ID_LAN938X,   // LAN8770 PHY in LAN938X switch
            .mask = LAN8770_PHY_ID_MASK,
            .mepa_driver_delete             = lan8770_delete,
            .mepa_driver_reset              = lan8770_reset,
            .mepa_driver_poll               = lan8770_poll,
            .mepa_driver_conf_set           = lan8770_conf_set,
            .mepa_driver_conf_get           = lan8770_conf_get,
            .mepa_driver_media_get          = lan8770_media_get,
            .mepa_driver_cable_diag_start   = lan8770_cable_diag_start,
            .mepa_driver_cable_diag_get     = lan8770_cable_diag_get,
            .mepa_driver_probe              = lan8770_probe,
            .mepa_driver_clause22_read      = lan8770_direct_reg_read,
            .mepa_driver_clause22_write     = lan8770_direct_reg_write,
            .mepa_driver_clause45_read      = lan8770_ext_bank_reg_read,
            .mepa_driver_clause45_write     = lan8770_ext_bank_reg_write,
            .mepa_driver_event_enable_set   = lan8770_event_enable_set,
            .mepa_driver_event_enable_get   = lan8770_event_enable_get,
            .mepa_driver_event_poll         = lan8770_event_status_poll,
            .mepa_driver_loopback_set       = lan8770_loopback_set,
            .mepa_driver_loopback_get       = lan8770_loopback_get,
            .mepa_driver_gpio_mode_set      = lan8770_gpio_mode_set,
            .mepa_driver_phy_info_get       = lan8770_info_get,
            .mepa_driver_isolate_mode_conf  = lan8770_isolate_mode_set,
            .mepa_debug_info_dump           = lan8770_debug_info,
            .mepa_driver_sqi_read           = lan8770_sqi_read,
        },
        {
            .id = LAN8770_PHY_ID_LAN937X,   // LAN8770 PHY in LAN937X switch
            .mask = LAN8770_PHY_ID_MASK,
            .mepa_driver_delete             = lan8770_delete,
            .mepa_driver_reset              = lan8770_reset,
            .mepa_driver_poll               = lan8770_poll,
            .mepa_driver_conf_set           = lan8770_conf_set,
            .mepa_driver_conf_get           = lan8770_conf_get,
            .mepa_driver_media_get          = lan8770_media_get,
            .mepa_driver_cable_diag_start   = lan8770_cable_diag_start,
            .mepa_driver_cable_diag_get     = lan8770_cable_diag_get,
            .mepa_driver_probe              = lan8770_probe,
            .mepa_driver_clause22_read      = lan8770_direct_reg_read,
            .mepa_driver_clause22_write     = lan8770_direct_reg_write,
            .mepa_driver_clause45_read      = lan8770_ext_bank_reg_read,
            .mepa_driver_clause45_write     = lan8770_ext_bank_reg_write,
            .mepa_driver_event_enable_set   = lan8770_event_enable_set,
            .mepa_driver_event_enable_get   = lan8770_event_enable_get,
            .mepa_driver_event_poll         = lan8770_event_status_poll,
            .mepa_driver_loopback_set       = lan8770_loopback_set,
            .mepa_driver_loopback_get       = lan8770_loopback_get,
            .mepa_driver_gpio_mode_set      = lan8770_gpio_mode_set,
            .mepa_driver_phy_info_get       = lan8770_info_get,
            .mepa_driver_isolate_mode_conf  = lan8770_isolate_mode_set,
            .mepa_debug_info_dump           = lan8770_debug_info,
            .mepa_driver_sqi_read           = lan8770_sqi_read,
        },
        {
            .id = LAN8770_PHY_ID_LAN937X_TC10,   // LAN8770 PHY in LAN937X switch with TC10 support
            .mask = LAN8770_PHY_ID_MASK,
            .mepa_driver_delete             = lan8770_delete,
            .mepa_driver_reset              = lan8770_reset,
            .mepa_driver_poll               = lan8770_poll,
            .mepa_driver_conf_set           = lan8770_conf_set,
            .mepa_driver_conf_get           = lan8770_conf_get,
            .mepa_driver_media_get          = lan8770_media_get,
            .mepa_driver_cable_diag_start   = lan8770_cable_diag_start,
            .mepa_driver_cable_diag_get     = lan8770_cable_diag_get,
            .mepa_driver_probe              = lan8770_probe,
            .mepa_driver_clause22_read      = lan8770_direct_reg_read,
            .mepa_driver_clause22_write     = lan8770_direct_reg_write,
            .mepa_driver_clause45_read      = lan8770_ext_bank_reg_read,
            .mepa_driver_clause45_write     = lan8770_ext_bank_reg_write,
            .mepa_driver_event_enable_set   = lan8770_event_enable_set,
            .mepa_driver_event_enable_get   = lan8770_event_enable_get,
            .mepa_driver_event_poll         = lan8770_event_status_poll,
            .mepa_driver_loopback_set       = lan8770_loopback_set,
            .mepa_driver_loopback_get       = lan8770_loopback_get,
            .mepa_driver_gpio_mode_set      = lan8770_gpio_mode_set,
            .mepa_driver_phy_info_get       = lan8770_info_get,
            .mepa_driver_isolate_mode_conf  = lan8770_isolate_mode_set,
            .mepa_debug_info_dump           = lan8770_debug_info,
            .mepa_driver_sqi_read           = lan8770_sqi_read,
        },
    };

    result.phy_drv = &lan8770_driver[0];
    result.count = nr_lan8770_drivers;

    return result;
}
