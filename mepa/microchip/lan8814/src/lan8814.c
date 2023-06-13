// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>

#include "../../common/include/lan8814_registers.h"
#include "lan8814_ts_registers.h"

#include "lan8814_private.h"

extern mepa_ts_driver_t indy_ts_drivers;

static mepa_rc indy_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info);
static mepa_rc indy_if_get(mepa_device_t *dev, mepa_port_speed_t speed, mepa_port_interface_t *mac_if);
static mepa_rc indy_conf_set(mepa_device_t *dev, const mepa_conf_t *config);
static mepa_rc indy_qsgmii_aneg(mepa_device_t *dev, mepa_bool_t ena);
static mepa_rc indy_event_enable_set(mepa_device_t *dev, mepa_event_t event, mepa_bool_t enable);

mepa_rc indy_direct_reg_rd(mepa_device_t *dev, uint16_t addr, uint16_t *value)
{
    if (dev->callout->miim_read(dev->callout_ctx, addr, value) != MESA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Port %d miim read failed\n", dev->numeric_handle);
    }
    return MEPA_RC_OK;
}
mepa_rc indy_direct_reg_wr(mepa_device_t *dev, uint16_t addr, uint16_t value, uint16_t mask)
{
    uint16_t reg_val = value;
    mesa_rc rc;

    rc = dev->callout->miim_read(dev->callout_ctx, addr, &reg_val);
    if (rc == MESA_RC_OK) {
        if (mask != INDY_DEF_MASK) {
            reg_val = (reg_val & ~mask) | (value & mask);
        } else {
            reg_val = value;
        }
        rc = dev->callout->miim_write(dev->callout_ctx, addr, reg_val);
        if (rc != MESA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Port %d miim write failed\n", dev->numeric_handle);
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "Port %d miim write failed\n", dev->numeric_handle);
    }
    return MEPA_RC_OK;
}

// Extended page read and write functions
// Extended page numbers range : 0 - 31
mepa_rc indy_ext_reg_rd(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t *value)
{
    // Set-up to access extended page register.
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL, page, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL,
                               INDY_F_EXT_PAGE_ACCESS_CTRL_EP_FUNC | page, INDY_DEF_MASK));

    // Read the value
    MEPA_RC(indy_direct_reg_rd(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, value));
    return MEPA_RC_OK;
}
mepa_rc indy_ext_reg_wr(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t value, uint16_t mask)
{
    // Set-up to access extended page register.
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL, page, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL,
                               INDY_F_EXT_PAGE_ACCESS_CTRL_EP_FUNC | page, INDY_DEF_MASK));

    // write the value
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, value, mask));
    return MEPA_RC_OK;
}

// Extended page address incremental read. After reading one register address of would automatically be
// incremented to next location in this function. This is useful for reading contiguous group of registers.
mepa_rc indy_ext_incr_reg_rd(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t *value, mepa_bool_t start_addr)
{
    if (start_addr) {
        // Set-up to access extended page register.
        MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL, page, INDY_DEF_MASK));
        MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
        MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL,
                INDY_F_EXT_PAGE_ACCESS_CTRL_INCR_RD_WR | page, INDY_DEF_MASK));
    }
    // Read the value
    MEPA_RC(indy_direct_reg_rd(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, value));
    return MEPA_RC_OK;
}

// MMD read and write functions
// MMD device range : 0 - 31
mepa_rc indy_mmd_reg_rd(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t *value)
{
    // Set-up to MMD register.
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL, mmd, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL,
                               INDY_F_MMD_ACCESS_CTRL_MMD_FUNC | mmd, INDY_DEF_MASK));

    // Read the value
    MEPA_RC(indy_direct_reg_rd(dev, INDY_MMD_ACCESS_ADDR_DATA, value));
    return MEPA_RC_OK;
}

mepa_rc indy_mmd_reg_wr(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t value, uint16_t mask)
{
    // Set-up to MMD register.
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL, mmd, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL,
                               INDY_F_MMD_ACCESS_CTRL_MMD_FUNC | mmd, INDY_DEF_MASK));

    // write the value
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, value, mask));
    return MEPA_RC_OK;
}

static mepa_rc indy_delete(mepa_device_t *dev)
{
    return mepa_delete_int(dev);
}

static mepa_rc indy_get_device_info(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t id;

    RD(dev, INDY_DEVICE_ID_2, &id);

    data->dev.model = INDY_X_DEV_ID_MODEL(id);
    data->dev.rev = INDY_X_DEV_ID_REV(id);
    T_I(MEPA_TRACE_GRP_GEN, "model 0x%x rev %d\n", data->dev.model, data->dev.rev);

    return MEPA_RC_OK;
}

static void indy_phy_deb_pr_reg (mepa_device_t *dev,
                                const mepa_debug_print_t pr,
                                uint16_t mmd, uint16_t page, uint16_t addr,
                                const char *str, uint16_t *value)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_port_no_t port_no = data->port_no;
    uint16_t id = page;

    if (mmd) {
        id = mmd;
        rc = indy_mmd_reg_rd(dev, mmd, addr, value);
    } else if (page) {
        rc = indy_ext_reg_rd(dev, (page-1), addr, value);
    } else {
        rc = indy_direct_reg_rd(dev, addr, value);
    }
    if(pr && (MEPA_RC_OK == rc)) {
        pr("%-45s:  0x%02x  0x%02x   0x%04x     0x%08x\n", str, to_u32(port_no), id, addr, *value);
    }
}

static mepa_rc indy_reg_dump(struct mepa_device *dev,
                             const mepa_debug_print_t pr)
{
    uint16_t val = 0;
    uint16_t id = 0;

    //Direct registers
    pr("%-45s   PORT_NO PAGE_ID REG_ADDR   VALUE\n", "REG_NAME");
    pr("Main Page Registers\n");
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 0, "Basic Control Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 1, "Basic Status Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 2, "Device Identifier 1 Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 3, "Device Identifier 2 Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 4, "Auto-Negotiation Advertisement Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 5, "Auto-Negotiation Link Partner Base Page Ability Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 6, "Auto-Negotiation Expansion Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 7, "Auto-Negotiation Next Page TX Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 8, "Auto-Negotiation Next Page RX Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 9, "Auto-Negotiation Master Slave Control Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 10, "Auto-Negotiation Master Slave Status Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 13, "MMD Access Control Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 14, "MMD Access Address/Data Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 15, "Extended Status Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 16, "PCS Loop-back Lane Skew Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 17, "PCS Loop-back Swap/Polarity Control Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 18, "Cable Diagnostic Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 19, "Digital PMA/PCS Status Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 20, "Digital AX/AN Status Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 21, "RXER Counter Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 22, "EP Access Control Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 23, "EP Access Address/Data Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 24, "GPHY Interrupt Enable Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 25, "GPHY Revision Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 26, "UNH Test Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 27, "GPHY Interrupt Status Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 28, "Digital Debug Control 1 Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 29, "Digital Debug Control 2 Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 30, "Reserved Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 0, 31, "Control Register", &val);

    //Extended page-0,1,2,3,4,5,7,28,29,31 registers
    pr("Extended Page-0 Registers\n");
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 0, "Debug-Mode First-Level-Select Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 1, "Debug-Mode Second-Level-Select for DIGITOP Part 1 Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 2, "Debug-Mode Second-Level-Select for DIGITOP Part 2 Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 3, "Auto-Negotiation Timer Register 1", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 4, "Auto-Negotiation Timer Register 2", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 5, "Auto-Negotiation Timer Register 3", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 6, "Auto-Negotiation Timer Register 4", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 7, "Auto-Negotiation Timer Register 5", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 8, "Auto-Negotiation Timer Register 6", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 9, "Auto-Negotiation Timer Register 7", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 10, "MDIX Select Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 11, "Max-Timer for 1.24 Millisecond Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 12, "Auto-Negotiation Wait Timer Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 13, "Max Link Timer Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 14, "Debug Bus Option Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 15, "Fast Link Fail (FLF) Configuration and Status Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 1, 16, "Link Partner Force FD Override Register", &val);

    pr("Extended Page-1 Registers\n");
    for(id = 0; id < 239; id++) {
        indy_phy_deb_pr_reg(dev, pr, 0, 2, id, "Extended Page 1 Registers", &val);
    }

    pr("Extended Page-2 Registers\n");
    for(id = 0; id < 111; id++) {
        indy_phy_deb_pr_reg(dev, pr, 0, 3, id, "Extended Page 2 Registers", &val);
    }

    pr("Extended Page-3 Registers\n");
    for(id = 0; id < 28; id++) {
        indy_phy_deb_pr_reg(dev, pr, 0, 4, id, "Extended Page 3 Registers", &val);
    }

    pr("Extended Page-4 Registers\n");
    for(id = 0; id < 772; id++) {
        indy_phy_deb_pr_reg(dev, pr, 0, 5, id, "Extended Page 4 Registers", &val);
    }

    pr("Extended Page-5 Registers\n");
    for(id = 0; id < 708; id++) {
        indy_phy_deb_pr_reg(dev, pr, 0, 6, id, "Extended Page 5 Registers", &val);
    }

    pr("Extended Page-7 Registers\n");
    indy_phy_deb_pr_reg(dev, pr, 0, 8, 58, "EP7 Register 58", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 8, 59, "EP7 Register 59", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 8, 62, "EEE Link Partner Ability Override Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 8, 63, "EEE Message Code Register", &val);

    pr("Extended Page-28 Registers\n");
    for(id = 0; id < 80; id++) {
        indy_phy_deb_pr_reg(dev, pr, 0, 29, id, "Extended Page 28 Registers", &val);
    }

    pr("Extended Page-29 Registers\n");
    for(id = 0; id < 80; id++) {
        indy_phy_deb_pr_reg(dev, pr, 0, 30, id, "Extended Page 29 Registers", &val);
    }

    pr("Extended Page-31 Registers\n");
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 0, "Speed Mode with TESTBUS Control Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 8, "Clock Management Mode 0", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 9, "Clock Management Mode 1", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 10, "Clock Management Mode 2", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 11, "Clock Management Mode 3", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 12, "Clock Management Mode 4", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 13, "Clock Management Mode 5", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 14, "Clock Management Mode 6", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 15, "Clock Management Mode 7", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 16, "Clock Management Mode 8", &val);
    indy_phy_deb_pr_reg(dev, pr, 0, 32, 17, "Clock Management Mode 9", &val);

    //MMD-3,7 registers
    pr("%-45s   PORT_NO DEV_ID REG_ADDR   VALUE\n", "REG_NAME");
    pr("MMD-3 Registers\n");
    indy_phy_deb_pr_reg(dev, pr, 3, 0x0, 0, "PCS Control 1 Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 3, 0x0, 1, "PCS Status 1 Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 3, 0x0, 20,"EEE Control and Capability Register", &val);

    pr("MMD-7 Registers\n");
    indy_phy_deb_pr_reg(dev, pr, 7, 0x0, 60,"EEE Advertisement Register", &val);
    indy_phy_deb_pr_reg(dev, pr, 7, 0x0, 61,"EEE Link Partner Ability Register", &val);

    return MEPA_RC_OK;
}

static mepa_rc indy_debug_info_dump(struct mepa_device *dev,
                                    const mepa_debug_print_t pr,
                                    const mepa_debug_info_t   *const info)
{
    mepa_rc rc = MEPA_RC_OK;
    mepa_phy_info_t phy_info;
    mepa_port_interface_t mac_if;

    (void)indy_info_get(dev, &phy_info);
    (void)indy_if_get(dev, MEPA_SPEED_1G,  &mac_if);

    if (info->layer == MEPA_DEBUG_LAYER_AIL || info->layer == MEPA_DEBUG_LAYER_ALL) {
        MEPA_ENTER(dev);
        pr("Port:%d   Family:Indy   Type:%d   Rev:%d   MacIf:%s\n", (int)dev->numeric_handle,
           phy_info.part_number, phy_info.revision, (mac_if == MESA_PORT_INTERFACE_QSGMII) ? "QSGMII" : "?");
        MEPA_EXIT(dev);
    }

    if (info->layer == MEPA_DEBUG_LAYER_CIL || info->layer == MEPA_DEBUG_LAYER_ALL) {
        //PHY Debugging
        switch(info->group)
        {
        case MEPA_DEBUG_GROUP_ALL:
        case MEPA_DEBUG_GROUP_PHY:
        {
            MEPA_ENTER(dev);
            rc = indy_reg_dump(dev, pr);
            MEPA_EXIT(dev);
        }
        break;
        default:
            rc = MEPA_RC_OK;
        }
    }

    //PHY_TS Debugging
    indy_ts_debug_info_dump(dev, pr, info);

    return rc;
}

static mepa_device_t *indy_probe(mepa_driver_t *drv,
                                 const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                 struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                 struct mepa_board_conf              *board_conf)
{
    mepa_device_t *dev;
    phy_data_t *data;

    dev = mepa_create_int(drv, callout, callout_ctx, board_conf, sizeof(phy_data_t));
    if (!dev) {
        return 0;
    }

    data = dev->data;
    data->port_no = board_conf->numeric_handle;
    data->events = 0;

#ifdef REG_DBG
    (void) indy_reg_dump(dev);
#endif

    T_I(MEPA_TRACE_GRP_GEN, "indy driver probed for port %d", data->port_no);
    return dev;
}

static mepa_rc indy_init_conf(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t val;

    indy_get_device_info(dev);

    // Set config only for base port of phy.
    if (data->dev.model == 0x26) {
        if (data->packet_idx == 0) {
            //EP_WR(dev, INDY_CHIP_HARD_RESET, 1);
            MEPA_MSLEEP(1);

            if (!data->qsgmii_phy_aneg_dis) {
                // Disable QSGMII auto-negotiation common for 4 ports.
                EP_WRM(dev, INDY_QSGMII_AUTO_ANEG, 0, INDY_F_QSGMII_AUTO_ANEG_AUTO_ANEG_ENA);
                data->qsgmii_phy_aneg_dis = TRUE;
            }
        }
    }

    // Enable Fast link config
    val = INDY_FLF_CFG_STAT_LINK_DOWN | INDY_FLF_CFG_STAT_FLF_ENABLE;
    EP_WRM(dev, INDY_FLF_CONFIG_STATUS, val, val);

    // Clear all GPHY interrupts during initialisation
    WR(dev, INDY_GPHY_INTR_ENA, 0);
    EP_WRM(dev, INDY_PTP_TSU_INT_EN, 0, INDY_DEF_MASK);
    RD(dev, INDY_GPHY_INTR_STATUS, &val);
    // Enable chip level interrupt
    EP_WRM(dev, INDY_INTR_CTRL, INDY_INTR_CTRL_CHIP_LVL_ENA, INDY_INTR_CTRL_CHIP_LVL_ENA);
    return MEPA_RC_OK;
}

// Configure qsgmii aneg advertisement capabilities
static void indy_qsgmii_tx_abilities(mepa_device_t *dev, mepa_port_speed_t speed, mepa_bool_t duplex)
{
    uint16_t value = 0x1; // default disable EEE enable & EEE clock stop
    uint16_t eee_val;

    MMD_RD(dev, INDY_LINK_PARTNER_EEE_ABILITY, &eee_val);
    if (speed == MEPA_SPEED_1G) {
        value |= (eee_val & INDY_F_LP_EEE_ABILITY_1000_BT) ? 0x180 : 0;
    } else if (speed == MEPA_SPEED_100M) {
        value |= (eee_val & INDY_F_LP_EEE_ABILITY_100_BT) ? 0x180 : 0;
    }
    if (duplex) {
        value |= INDY_BIT(12);
    }
    value |= (speed == MEPA_SPEED_1G) ? INDY_BIT(10) : (speed == MEPA_SPEED_100M) ? INDY_BIT(9) : 0;
    value |= INDY_BIT(14);
    EP_WR(dev, INDY_QSGMII_PCS1G_ANEG_TX_ADVERTISE_CAP, value);

    EP_WRM(dev, INDY_QSGMII_PCS1G_ANEG_CONFIG, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_RESTART, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_RESTART);
}

static mepa_rc indy_qsgmii_aneg(mepa_device_t *dev, mepa_bool_t ena)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    if (data->dev.model != 0x26) {
        return MEPA_RC_OK;
    }
    T_I(MEPA_TRACE_GRP_GEN, "qsgmii aneg ena %d", ena);
    if (!ena) {
        // Disable QSGMII auto-negotiation
        EP_WRM(dev, INDY_QSGMII_PCS1G_ANEG_CONFIG, 0, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_ENA);
    } else {
        // Enable QSGMII auto-negotiation.
        EP_WRM(dev, INDY_QSGMII_PCS1G_ANEG_CONFIG, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_ENA, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_ENA);
    }
    return MEPA_RC_OK;
}

static mepa_rc indy_rev_workaround(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t val;

    // work-arounds applicable for both models 0x26 & 0x27
    do {
        // work-around for Rev C done.
        if (data->dev.rev >= 2) {
            break;
        }
        // MDI-X setting for swap A,B transmit
        EP_WRM(dev, INDY_ALIGN_SWAP, INDY_F_ALIGN_TX_A_B_SWAP, INDY_M_ALIGN_TX_SWAP);
    } while (0);
    // work-around for model 0x27 only
    if (data->dev.model == 0x27 && data->dev.rev <= 2) {
        EP_WR(dev, INDY_1000BT_FIX_LATENCY_ENABLE, 1);
        // In Indy internal phy clock generation stops when link goes down.
        EP_WR(dev, INDY_CLOCK_MANAGEMENT_MODE_5, 0x27e);
        EP_RD(dev, INDY_LINK_QUALITY_MONITOR_SETTING, &val);
    }
    // work-around for model 0x27 done.
    if (data->dev.model != 0x26) {
        return MEPA_RC_OK;
    }
    // work-arounds applicable for only model 0x26
    // Rev A, B, C
    // PLL trim
    EP_WR(dev, INDY_ANALOG_CONTROL_1, 0x40);
    EP_WR(dev, INDY_ANALOG_CONTROL_10, 0x1);

    // Rev C work-around done.
    if (data->dev.rev >= 2) {
        return MEPA_RC_OK;
    }
    // Rev B work-around done.
    if (data->dev.rev >= 1) {
        return MEPA_RC_OK;
    }
    EP_WR(dev, INDY_OPERATION_MODE_STRAP_LOW, 0x2);
    EP_WR(dev, INDY_OPERATION_MODE_STRAP_HIGH, 0xc001);

    T_D(MEPA_TRACE_GRP_GEN, "rev A work-around configured");
    return MEPA_RC_OK;
}

static mepa_rc indy_workaround_after_reset(mepa_device_t *dev)
{
    // Improve cable reach beyond 130m
    EP_WR(dev, INDY_PD_CONTROLS, 0x248b);
    EP_WR(dev, INDY_DFE_INIT2_100, 0x3c30);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_0, 0x10a);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_1, 0xed);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_2, 0xd3);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_3, 0xbc);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_4, 0xa8);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_5, 0x96);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_6, 0x85);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_7, 0x77);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_8, 0x6a);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_9, 0x5e);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_10, 0x54);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_11, 0x4b);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_12, 0x43);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_13, 0x3c);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_14, 0x35);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_15, 0x2f);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_16, 0x2a);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_17, 0x26);

    // Set Rx-clk to avoid crc errors in near-end loopback
    WRM(dev, INDY_UNH_TEST, INDY_F_TEST_RX_CLK, INDY_F_TEST_RX_CLK);

    // Magjack center tapped ports
    EP_WR(dev, INDY_POWER_MGMT_MODE_3, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_4, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_5, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_6, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_7, 0x0077);
    EP_WR(dev, INDY_POWER_MGMT_MODE_8, 0x4377);
    EP_WR(dev, INDY_POWER_MGMT_MODE_9, 0x4377);
    EP_WR(dev, INDY_POWER_MGMT_MODE_10, 0x6777);
    EP_WR(dev, INDY_POWER_MGMT_MODE_11, 0x0777);
    EP_WR(dev, INDY_POWER_MGMT_MODE_12, 0x0777);
    EP_WR(dev, INDY_POWER_MGMT_MODE_13, 0x6777);
    EP_WR(dev, INDY_POWER_MGMT_MODE_14, 0x6777);

    // Trimming 10BT also for template and Diff output fixes
    EP_WR(dev, INDY_AFED_CONTROL, 0xe214);
    EP_WR(dev, INDY_ANALOG_CONTROL_4, 0x81e0);

    // EEE wake TX timer max value
    EP_WR(dev, INDY_EEE_WAKE_TX_TIMER, 0x1f);

    return MEPA_RC_OK;
}

// Work-around for 10M, 100M speed with half duplex configuration.
static mepa_rc indy_workaround_half_duplex(mepa_device_t *dev)
{
    EP_WR(dev, INDY_RX_RA_FIFO_THRESHOLDS_1, 0x200);
    EP_WR(dev, INDY_RX_RA_FIFO_THRESHOLDS_2, 0x404);
    EP_WR(dev, INDY_RX_RA_FIFO_THRESHOLDS_3, 0x608);
    EP_WR(dev, INDY_TX_RA_FIFO_THRESHOLDS_1, 0x200);
    EP_WR(dev, INDY_TX_RA_FIFO_THRESHOLDS_2, 0x404);
    EP_WR(dev, INDY_TX_RA_FIFO_THRESHOLDS_3, 0x608);
    return MEPA_RC_OK;
}

// If earlier speed,duplex are 10M,100M with half duplex config, work-around applied earlier needs to be cleaned up.
static mepa_rc indy_workaround_fifo_reset(mepa_device_t *dev)
{
    EP_WR(dev, INDY_TX_RA_FIFO_RESET, 1);
    EP_WR(dev, INDY_RX_RA_FIFO_RESET, 1);
    return MEPA_RC_OK;
}

// Frame pre-emption bit must be set before setting TSU_ENABLE bit in TSU_GENERAL_CONFIG register.
// It also implies that it must be called before indy_ts_mode_set API.
static mepa_rc indy_framepreempt_set(mepa_device_t *dev, mepa_bool_t const enable)
{
    uint16_t val;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_device_t *base_dev = data->base_dev;
    phy_data_t *base_data = base_dev ? ((phy_data_t *)(base_dev->data)) : NULL;

    if (!data || !base_dev || !base_data)
        return MEPA_RC_OK;

    MEPA_ENTER(dev);

    //Update base port with reset_conf::framepreempt_en
    if (base_dev == dev)
        base_data->framepreempt_en = enable;

    //Set Frame Preemption
    val = 0;
    EP_RD(dev, INDY_PTP_TSU_GEN_CONF, &val);
    if (base_data->framepreempt_en)
        val |= INDY_PTP_TSU_GEN_CONF_PREEMPTION_EN;
    else
        val &= ~INDY_PTP_TSU_GEN_CONF_PREEMPTION_EN;
    EP_WRM(dev, INDY_PTP_TSU_GEN_CONF, val, INDY_DEF_MASK);

    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_selftest_stop(struct mepa_device *dev)
{
    uint16_t val;

    EP_RD(dev, INDY_SELFTEST_PGEN_EN, &val);

    if (val & INDY_F_SELFTEST_PGEN_EN) {
        // stop self-test
        EP_WR(dev, INDY_SELFTEST_PGEN_EN, 0);
        // Disable Ext_lpbk bit in the Reserved Register
        WR(dev, INDY_RESV_CON_LOOP, 0xfc00);
    }

    return MEPA_RC_OK;
}

static mepa_rc indy_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    MEPA_ENTER(dev);
    if (!data->init_done) {
        indy_init_conf(dev);
        indy_rev_workaround(dev);
        indy_qsgmii_aneg(dev, FALSE);
        data->init_done = TRUE;
        if (data->dev.model == 0x26) {
            data->crc_workaround = TRUE;
            data->aneg_after_link_up = FALSE;
        }
    }

    //Clear self-test if enabled before reset
    indy_selftest_stop(dev);

    if (rst_conf->reset_point == MEPA_RESET_POINT_DEFAULT) {
        WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SOFT_RESET, INDY_F_BASIC_CTRL_SOFT_RESET);
    } else if (rst_conf->reset_point == MEPA_RESET_POINT_POST_MAC) {
        // To avoid qsgmii serdes and Gphy blocks settling in different speeds, use qsgmii soft reset and restart aneg.
        // This must be applied after Mac serdes is configured.
        if (data->dev.model == 0x26) {
            EP_WR(dev, INDY_QSGMII_SOFT_RESET, 0x1);
            WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_RESTART_ANEG, INDY_F_BASIC_CTRL_RESTART_ANEG);
            data->post_mac_rst = TRUE;
        }
    }

    MEPA_MSLEEP(1);
    // Some of the work-around registers get cleared after reset. So, they are called here
    // after every reset.
    indy_workaround_after_reset(dev);

    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "Reconfiguring the phy after reset");
    // Reconfigure the phy after reset
    if (rst_conf->reset_point == MEPA_RESET_POINT_DEFAULT) {
        indy_conf_set(dev, &data->conf);
        if (data->events) {
            indy_event_enable_set(dev, data->events, TRUE);
        }
    }

    //Configure frame preemption
    indy_framepreempt_set(dev, rst_conf->framepreempt_en);

    return MEPA_RC_OK;
}

static mepa_rc indy_poll(mepa_device_t *dev, mepa_status_t *status)
{
    uint16_t val, val2 = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_ENTER(dev);
    RD(dev, INDY_BASIC_STATUS, &val);
    status->link = (val & INDY_F_BASIC_STATUS_LINK_STATUS) ? 1 : 0;

    if (data->loopback.near_end_ena == TRUE) {
        // loops back to Mac. Ignore Line side status to Link partner.
        status->link = 1;
    }
    if (data->conf.speed == MEPA_SPEED_AUTO || data->conf.speed == MEPA_SPEED_1G) {
        uint16_t lp_sym_pause = 0, lp_asym_pause = 0;
        // Default values
        status->speed = MEPA_SPEED_UNDEFINED;
        status->fdx = 1;
        // check if auto-negotiation is completed or not.
        if (!data->loopback.near_end_ena && status->link && !(val & INDY_F_BASIC_STATUS_ANEG_COMPLETE)) {
            T_I(MEPA_TRACE_GRP_GEN, "Aneg is not completed for port %d", data->port_no);
            status->link = 0;
        } else if (data->loopback.near_end_ena) {
            status->speed = MEPA_SPEED_1G;
        }
        if (!status->link || data->loopback.near_end_ena) {
            // No need to read aneg values when link is down or when near-end loopback enabled.
            goto end;
        }
        // Obtain speed and duplex from link partner's advertised capability.
        RD(dev, INDY_ANEG_LP_BASE, &val);
        RD(dev, INDY_ANEG_MSTR_SLV_STATUS, &val2);
        // 1G half duplex is not supported. Refer direct register - 9
        if ((val2 & INDY_F_ANEG_MSTR_SLV_STATUS_1000_T_FULL_DUP) &&
            data->conf.aneg.speed_1g_fdx) {
            // Work-around for CRC errors begin.
            if (data->crc_workaround) {
                if (!((val2 & INDY_F_ANEG_MSTR_SLV_LOCAL_RCVR_STATUS) &&
                     (val2 & INDY_F_ANEG_MSTR_SLV_REMOTE_RCVR_STATUS)) ||
                     !data->post_mac_rst) {
                    //link not completely up
                    status->link = 0;
                } else if (!data->aneg_after_link_up) {// poll the status for 1 iteration assuming the polling interval is 1 second apart.
                    T_I(MEPA_TRACE_GRP_GEN, "Aneg restarted on port %d", data->port_no);
                    WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_RESTART_ANEG, INDY_F_BASIC_CTRL_RESTART_ANEG);
                    data->aneg_after_link_up = TRUE;
                    status->link = 0;
                } else if (data->aneg_after_link_up) {// After auto-negotiation restarted, set the link status as up.
                    status->speed = MEPA_SPEED_1G;
                    status->fdx = 1;
                    data->crc_workaround = FALSE;
                    data->aneg_after_link_up = FALSE;
                } else {
                    T_I(MEPA_TRACE_GRP_GEN, "no link");
                    status->link = 0;
                }
            // Work-around for CRC errors end.
            } else {
                status->speed = MEPA_SPEED_1G;
                status->fdx = 1;
            }
        } else if ((val & INDY_F_ANEG_LP_BASE_100_X_FULL_DUP) &&
                   data->conf.aneg.speed_100m_fdx) {
            status->speed = MEPA_SPEED_100M;
            status->fdx = 1;
        } else if ((val & INDY_F_ANEG_LP_BASE_100_X_HALF_DUP) &&
                   data->conf.aneg.speed_100m_hdx) {
            status->speed = MEPA_SPEED_100M;
            status->fdx = 0;
        } else if ((val & INDY_F_ANEG_LP_BASE_10_T_FULL_DUP) &&
                   data->conf.aneg.speed_10m_fdx) {
            status->speed = MEPA_SPEED_10M;
            status->fdx = 1;
        } else if ((val & INDY_F_ANEG_LP_BASE_10_T_HALF_DUP) &&
                   data->conf.aneg.speed_10m_hdx) {
            status->speed = MEPA_SPEED_10M;
            status->fdx = 0;
        }
        // Get flow control status
        lp_sym_pause = (val & INDY_F_ANEG_LP_BASE_SYM_PAUSE) ? 1 : 0;
        lp_asym_pause = (val & INDY_F_ANEG_LP_BASE_ASYM_PAUSE) ? 1 : 0;
        status->aneg.obey_pause = data->conf.flow_control && (lp_sym_pause || lp_asym_pause);
        status->aneg.generate_pause = data->conf.flow_control && lp_sym_pause;
    } else {
        uint8_t speed;
        // Forced speed
        RD(dev, INDY_BASIC_CONTROL, &val2);
        speed = (!!(val2 & INDY_F_BASIC_CTRL_SPEED_SEL_BIT_0)) |
                (!!(val2 & INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1) << 1);
        status->speed = (speed == 0) ? MEPA_SPEED_10M :
                        (speed == 1) ? MEPA_SPEED_100M :
                        (speed == 2) ? MEPA_SPEED_1G : MEPA_SPEED_UNDEFINED;
        status->fdx = !!(val2 & INDY_F_BASIC_CTRL_DUP_MODE);
        //check that aneg is not enabled.
        if (val2 & INDY_F_BASIC_CTRL_ANEG_ENA) {
            T_W(MEPA_TRACE_GRP_GEN, "Aneg is enabled for forced speed config on port %d", data->port_no);
        }
    }

end:
    if (data->dev.model == 0x26) {
        if (status->link != data->link_status) {
            if (status->link) { // link up
                if ( data->conf.speed == MEPA_SPEED_AUTO || data->conf.speed == MEPA_SPEED_1G) {
                    if (data->conf.mac_if_aneg_ena) {
                        // copy the capabilities on host side
                        indy_qsgmii_tx_abilities(dev, status->speed, status->fdx);
                    }
                }
                if ((status->speed == MEPA_SPEED_10M || status->speed == MEPA_SPEED_100M) &&
                    (status->fdx == FALSE)) {
                    indy_workaround_half_duplex(dev);
                }
            } else {// link down event.
                indy_workaround_fifo_reset(dev);
            }
        }
    }
    data->link_status = status->link;
    data->speed_status = status->speed;
    data->fdx_status   = status->fdx;
    MEPA_EXIT(dev);
    T_D(MEPA_TRACE_GRP_GEN, "port %d status link %d, speed %d, fdx %d", data->port_no, status->link, status->speed, status->fdx);
    return MEPA_RC_OK;
}

static mepa_rc indy_conf_mdi_mode(mepa_device_t *dev, const mepa_media_mode_t mode)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_media_mode_t old_mode = data->conf.mdi_mode;
    uint16_t val;

    if (old_mode == mode) return MEPA_RC_OK;

    /*
      BIT(7) = mdi_set
        mdi_set has no function when swapoff (reg28.6) is de-asserted.
        When swapoff is asserted, if mdi_set is asserted, chip will operate at MDI mode.
        When swapoff is asserted, if mdi_set is de-asserted, chip will operate at MDI-X
        mode.
      BIT(6) = swapoff
        1 = disable auto crossover function.
        0 = enable auto crossover function.
     */

    // Read current MDI settings
    RD(dev, INDY_GPHY_DBG_CTL1, &val);
    val &= ~INDY_F_MDI_SET;
    switch (mode) {
      case MEPA_MEDIA_MODE_MDI:
        val |= INDY_F_MDI_SET;
        // Fall through
      case MEPA_MEDIA_MODE_MDIX:
        val |= INDY_F_SWAPOFF;
      break;
      default:
        val &= ~INDY_F_SWAPOFF;
      break;
    }
    // Set the current MDI
    WRM(dev, INDY_GPHY_DBG_CTL1, val, INDY_DEF_MASK);

    // Update local cache
    data->conf.mdi_mode = mode;

    T_D(MEPA_TRACE_GRP_GEN, "port %d old mdi_mode %d, new mdi_mode %d",
        data->port_no, old_mode, data->conf.mdi_mode);

    return MEPA_RC_OK;
}

static mepa_rc indy_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t new_value, mask, old_value;
    mepa_bool_t restart_aneg = FALSE;
    mepa_bool_t qsgmii_aneg = config->speed != MEPA_SPEED_AUTO ? FALSE : config->mac_if_aneg_ena;

    MEPA_ENTER(dev);
    if (config->admin.enable) {
        // Check & configure MDI mode as needed
        indy_conf_mdi_mode(dev, config->mdi_mode);

        if (qsgmii_aneg != data->conf.mac_if_aneg_ena) {
            indy_qsgmii_aneg(dev, qsgmii_aneg);
        }
        if (config->speed == MEPA_SPEED_AUTO || config->speed == MEPA_SPEED_1G) {
            if ((data->conf.speed == MEPA_SPEED_10M || data->conf.speed == MEPA_SPEED_100M) &&
                !data->conf.fdx) {
                indy_workaround_fifo_reset(dev);
            }
            if (data->conf.admin.enable != config->admin.enable) {
                restart_aneg = TRUE;
            }

            // 1G manual negotiation & speed
            new_value = config->aneg.speed_1g_fdx ? INDY_F_ANEG_MSTR_SLV_CTRL_1000_T_FULL_DUP : 0;
            mask = INDY_F_ANEG_MSTR_SLV_CTRL_1000_T_FULL_DUP;
            if (config->man_neg) {
                new_value |= INDY_F_ANEG_MSTR_SLV_CTRL_CFG_ENA;
                new_value |= config->man_neg == MEPA_MANUAL_NEG_REF ? INDY_F_ANEG_MSTR_SLV_CTRL_CFG_VAL : 0;
            }
            mask |= (INDY_F_ANEG_MSTR_SLV_CTRL_CFG_VAL | INDY_F_ANEG_MSTR_SLV_CTRL_CFG_ENA);
            if (config->aneg.speed_1g_fdx != data->conf.aneg.speed_1g_fdx ||
                (config->man_neg && (config->man_neg != data->conf.man_neg))) {
                restart_aneg = TRUE;
            }
            WRM(dev, INDY_ANEG_MSTR_SLV_CTRL, new_value, mask);

            // Set up auo-negotiation advertisement in register 4
            new_value = (((config->aneg.tx_remote_fault ? 1 : 0) << 13) |
                         ((config->flow_control ? 1 : 0) << 11) |
                         ((config->flow_control ? 1 : 0) << 10) |
                         ((config->aneg.speed_100m_fdx ? 1 : 0) << 8) |
                         ((config->aneg.speed_100m_hdx ? 1 : 0) << 7) |
                         ((config->aneg.speed_10m_fdx ? 1 : 0) << 6) |
                         ((config->aneg.speed_10m_hdx ? 1 : 0) << 5) |
                         (1 << 0)); // default selector field - 1
            RD(dev, INDY_ANEG_ADVERTISEMENT, &old_value);
            if (old_value != new_value) {
                restart_aneg = TRUE;
            }
            WR(dev, INDY_ANEG_ADVERTISEMENT, new_value);
            // Enable & restart auto-negotiation
            new_value = INDY_F_BASIC_CTRL_ANEG_ENA;
            WRM(dev, INDY_BASIC_CONTROL, new_value, new_value | INDY_F_BASIC_CTRL_SOFT_POW_DOWN);
            if (restart_aneg) {
                T_I(MEPA_TRACE_GRP_GEN, "Aneg restarted on port %d", data->port_no);
                WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_RESTART_ANEG, INDY_F_BASIC_CTRL_RESTART_ANEG);
            }
        } else if (config->speed != MEPA_SPEED_UNDEFINED) {
            if ((data->conf.speed == MEPA_SPEED_10M || data->conf.speed == MEPA_SPEED_100M) &&
                !data->conf.fdx) {
                indy_workaround_fifo_reset(dev);
            }
            T_I(MEPA_TRACE_GRP_GEN, "forced speed %d configured\n", config->speed);
            new_value = ((config->speed == MEPA_SPEED_100M ? 1 : 0) << 13) | (0 << 12) |
                        ((config->fdx ? 1 : 0) << 8) |
                        ((config->speed == MEPA_SPEED_1G ? 1 : 0) << 6);
            mask = INDY_BIT(13) | INDY_BIT(12) | INDY_BIT(8) | INDY_BIT(6) | INDY_F_BASIC_CTRL_SOFT_POW_DOWN | INDY_F_BASIC_CTRL_ANEG_ENA;
            WRM(dev, INDY_BASIC_CONTROL, new_value, mask);

            // half duplex work-around for 10M, 100M speeds
            if (!config->fdx) {
                indy_workaround_half_duplex(dev);
            }
        }
    } else {
        T_I(MEPA_TRACE_GRP_GEN, "set power down\n");
        // set soft power down bit
        WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SOFT_POW_DOWN, INDY_F_BASIC_CTRL_SOFT_POW_DOWN);
    }
    data->conf = *config;
    data->conf.mac_if_aneg_ena = qsgmii_aneg;
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_conf_get(mepa_device_t *dev, mepa_conf_t *const config)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    *config = data->conf;
    MEPA_EXIT(dev);
    T_D(MEPA_TRACE_GRP_GEN, "returning phy config on port %d", data->port_no);
    return MEPA_RC_OK;
}

static mepa_rc mas_if_set(mepa_device_t *dev,
                           mepa_port_interface_t mac_if)
{
    if (mac_if != MESA_PORT_INTERFACE_SGMII) {
        return MEPA_RC_ERROR;
    }
    return MEPA_RC_OK;
}

static mepa_rc mas_if_get(mepa_device_t *dev, mepa_port_speed_t speed,
                          mepa_port_interface_t *mac_if)
{
    *mac_if = MESA_PORT_INTERFACE_SGMII;
    return MEPA_RC_OK;
}

static mepa_rc indy_if_set(mepa_device_t *dev,
                           mepa_port_interface_t mac_if)
{
    if (mac_if != MESA_PORT_INTERFACE_QSGMII) {
        return MEPA_RC_ERROR;
    }

    return MEPA_RC_OK;
}

static mepa_rc indy_if_get(mepa_device_t *dev, mepa_port_speed_t speed,
                           mepa_port_interface_t *mac_if)
{

    MEPA_ENTER(dev);
    *mac_if = MESA_PORT_INTERFACE_QSGMII;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

// wait in loop while cable diagnostics is running.
static mepa_bool_t indy_wait_for_cable_diagnostics(mepa_device_t *dev)
{
    uint8_t cnt = 0;
    uint16_t value;
    mepa_bool_t ret = FALSE;

    while (cnt < 100) { // wait for utmost 1 second
        RD(dev, INDY_CABLE_DIAG, &value);
        if (value & INDY_F_CABLE_DIAG_TEST_ENA) {
            MEPA_MSLEEP(10);
            cnt++;
        } else {
            ret = TRUE;
            break;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "ret = %d cnt= %d value=0x%x\n", ret, cnt, value);
    return ret;
}
//Before starting cable diagnostics, do necessary phy configuration like reset speed config.
static mepa_rc indy_cab_diag_enter_config(mepa_device_t *dev)
{
    WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SOFT_RESET, INDY_F_BASIC_CTRL_SOFT_RESET);
    MEPA_MSLEEP(1);
    WR(dev, INDY_BASIC_CONTROL, 0x140);
    MEPA_MSLEEP(50);
    return MEPA_RC_OK;
}
// After exiting cable diagnostics/self-test , restore phy configuration.
static mepa_rc indy_restore_config(mepa_device_t *dev)
{
    mepa_reset_param_t rst_cfg = {};

    rst_cfg.reset_point = MEPA_RESET_POINT_DEFAULT;
    // Restore configuration after cable diagnostics/self-test.
    indy_reset(dev, &rst_cfg);
    return MEPA_RC_OK;
}
// Indy phy dignostics is calculated only when there is no remote link partner for the port.
// For mode values {0,1} corresponding to {VTSS_PHY_MODE_ANEG, VTSS_PHY_MODE_FORCED}, diagnostics is calculated.
// For power down mode(2), diagnostics is not calculated.
static mepa_rc indy_cab_diag_start(mepa_device_t *dev, int32_t mode)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t value, mask = 0, pair, status;
    mepa_cable_diag_result_t *res = &data->cable_diag;

    T_I(MEPA_TRACE_GRP_GEN, "port=%d mode=%d\n", data->port_no, mode);
    MEPA_ENTER(dev);
    // Initialize diagnostics
    for (pair = 0; pair < 4; pair++) {
        res->status[pair] = MEPA_CABLE_DIAG_STATUS_UNKNOWN;
        res->length[pair] = 0;
        res->link = FALSE;
    }
    // return for power down mode
    if (mode == INDY_CABLE_MODE_POWER_DOWN) {
        MEPA_EXIT(dev);
        return MEPA_RC_ERROR;
    }
    indy_cab_diag_enter_config(dev);
    for (pair = 0; pair < 4; pair++) {
        // clear diag test ena before starting
        WRM(dev, INDY_CABLE_DIAG, 0, INDY_F_CABLE_DIAG_TEST_ENA);

        value = mask = status = 0;
        value |= INDY_F_CABLE_DIAG_TEST_ENA;
        value |= INDY_F_CABLE_TEST_PAIR(pair);
        mask |= INDY_F_CABLE_DIAG_TEST_ENA | INDY_M_CABLE_TEST_PAIR;
        WRM(dev, INDY_CABLE_DIAG, value, mask);
        if (indy_wait_for_cable_diagnostics(dev)) {
            RD(dev, INDY_CABLE_DIAG, &value);
            status = INDY_X_CABLE_DIAG_STATUS(value);
            if ((status == INDY_CABLE_OPEN) || (status == INDY_CABLE_SHORT)) {
                res->status[pair] = (status == INDY_CABLE_SHORT) ? MEPA_CABLE_DIAG_STATUS_SHORT : MEPA_CABLE_DIAG_STATUS_OPEN;
                res->length[pair] = 0.8 * (INDY_X_CABLE_DIAG_DATA(value) - 22);
                res->link = TRUE;
                T_I(MEPA_TRACE_GRP_GEN, "pair=%d status=%d length=%d\n", pair, res->status[pair], res->length[pair]);
            } else if (status == INDY_CABLE_FAIL) {
                res->status[pair] = MEPA_CABLE_DIAG_STATUS_ABNORM;
                res->link = FALSE;
                T_I(MEPA_TRACE_GRP_GEN, "link status failed for pair %d \n", pair);
            } else { // status as INDY_CABLE_NORMAL
                res->link = TRUE;
                T_I(MEPA_TRACE_GRP_GEN, "pair=%d status=%d \n", pair, status);
            }
        }
    }
    MEPA_EXIT(dev);
    indy_restore_config(dev);
    return MEPA_RC_OK;
}
static mepa_rc indy_cab_diag_get(mepa_device_t *dev, mepa_cable_diag_result_t *res)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    MEPA_ENTER(dev);
    *res = data->cable_diag;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_aneg_status_get(mepa_device_t *dev, mepa_aneg_status_t *status)
{
    uint16_t val;

    MEPA_ENTER(dev);
    RD(dev, INDY_ANEG_MSTR_SLV_STATUS, &val);
    status->master_cfg_fault = (val & INDY_F_ANEG_MSTR_SLV_STATUS_CFG_FAULT) ? TRUE : FALSE;
    status->master = val & INDY_F_ANEG_MSTR_SLV_STATUS_CFG_RES ? TRUE : FALSE;
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "aneg status get mstr %d", status->master);
    return MEPA_RC_OK;
}

// read direct registers for debugging
static mepa_rc indy_direct_reg_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    mepa_rc rc;
    uint16_t addr = address & 0x1f;

    MEPA_ENTER(dev);
    rc = indy_direct_reg_rd(dev, addr, value);
    MEPA_EXIT(dev);
    return rc;
}

// write direct registers. Used for debugging.
static mepa_rc indy_direct_reg_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    mepa_rc rc;
    uint16_t addr = address & 0x1f;

    MEPA_ENTER(dev);
    rc = indy_direct_reg_wr(dev, addr, value, 0xFFFF);
    MEPA_EXIT(dev);
    return rc;
}

// read extended page/mmd register for debugging
static mepa_rc indy_ext_mmd_reg_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    mepa_rc rc;
    uint16_t page_mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;
    uint16_t mmd = (page_mmd >> 11);

    MEPA_ENTER(dev);
    if (mmd) {
        rc = indy_mmd_reg_rd(dev, mmd, addr, value);
    } else {
        rc = indy_ext_reg_rd(dev, page_mmd, addr, value);
    }
    MEPA_EXIT(dev);
    return rc;
}

// write extended page/mmd register. Used for debugging.
static mepa_rc indy_ext_mmd_reg_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    mepa_rc rc;
    uint16_t page_mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;
    uint16_t mmd = (page_mmd >> 11);

    MEPA_ENTER(dev);
    if (mmd) {
        rc = indy_mmd_reg_wr(dev, mmd, addr, value, 0xFFFF);
    } else {
        rc = indy_ext_reg_wr(dev, page_mmd, addr, value, 0xFFFF);
    }
    MEPA_EXIT(dev);
    return rc;
}

// Enable events
static mepa_rc indy_event_enable_set(mepa_device_t *dev, mepa_event_t event, mepa_bool_t enable)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t ev_mask = 0, i;
    phy_data_t *data = (phy_data_t *)dev->data;
    data->events = enable ? (data->events | event) :
                   (data->events & ~event);
    MEPA_ENTER(dev);
    for (i = 0; i < sizeof(mepa_event_t) * 8; i++) {
        switch (event & (1 << i)) {
        case MEPA_LINK_LOS:
            ev_mask = ev_mask | INDY_F_GPHY_INTR_ENA_LINK_DOWN;
            break;
        case MEPA_FAST_LINK_FAIL:
            ev_mask = ev_mask | INDY_F_GPHY_INTR_ENA_FLF_INTR;
            break;
        default:
            // Not yet implemented
            break;
        }
    }
    WRM(dev, INDY_GPHY_INTR_ENA, enable ? ev_mask : 0, ev_mask);
    T_I(MEPA_TRACE_GRP_GEN, "events enabled 0x%x \n", data->events);
    MEPA_EXIT(dev);
    return rc;
}

// Get current enabled events
static mepa_rc indy_event_enable_get(mepa_device_t *dev, mepa_event_t *const event)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    MEPA_ENTER(dev);
    *event = data->events;
    MEPA_EXIT(dev);
    return rc;
}

// Poll the status of currently enabled events
static mepa_rc indy_event_status_poll(mepa_device_t *dev, mepa_event_t *const status)
{
    uint16_t val;
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    *status = 0;
    MEPA_ENTER(dev);
    rc = RD(dev, INDY_GPHY_INTR_STATUS, &val);
    if (val & INDY_F_GPHY_INTR_ENA_LINK_DOWN) {
        *status |= data->events & MEPA_LINK_LOS;
    }
    if (val & INDY_F_GPHY_INTR_ENA_FLF_INTR) {
        *status |= data->events & MEPA_FAST_LINK_FAIL;
    }
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, " port %d events polled 0x%x val %x\n", data->port_no, *status, val);
    return rc;
}

// Set loopback modes in phy
static mepa_rc indy_loopback_set(mepa_device_t *dev, const mepa_loopback_t *loopback)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    if ((loopback->mac_serdes_input_ena == TRUE) || (loopback->mac_serdes_facility_ena == TRUE) ||
        (loopback->mac_serdes_equip_ena == TRUE) || (loopback->media_serdes_input_ena == TRUE) ||
        (loopback->media_serdes_facility_ena == TRUE) || (loopback->media_serdes_equip_ena == TRUE)) {
        // Not supported on Indy
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    MEPA_ENTER(dev);
    // Far end loopback
    if (loopback->far_end_ena == TRUE) {
        WRM(dev, INDY_PCS_LOOP_POLARITY_CTRL, INDY_F_PCS_LOOP_CTRL_PORT_LOOP,
            INDY_F_PCS_LOOP_CTRL_PORT_LOOP);
    } else if (data->loopback.far_end_ena == TRUE) {
        WRM(dev, INDY_PCS_LOOP_POLARITY_CTRL, 0, INDY_F_PCS_LOOP_CTRL_PORT_LOOP);
    }
    if (loopback->near_end_ena == TRUE) {
        WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_LOOPBACK, INDY_F_BASIC_CTRL_LOOPBACK);
        if (data->conf.speed == MEPA_SPEED_AUTO || data->conf.speed == MEPA_SPEED_1G) {
            // Set 1000mbps speed for loopback when there is auto-negotiation mode. While removing loopback, restore the original mode.
            // Disable auto-negotiation
            WRM(dev, INDY_BASIC_CONTROL, 0, INDY_F_BASIC_CTRL_ANEG_ENA);
            // Set 1000mbps speed
            WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1, INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1 | INDY_F_BASIC_CTRL_SPEED_SEL_BIT_0);
        }
    } else if (data->loopback.near_end_ena == TRUE) {
        WRM(dev, INDY_BASIC_CONTROL, 0, INDY_F_BASIC_CTRL_LOOPBACK);
        if (data->conf.speed == MEPA_SPEED_AUTO || data->conf.speed == MEPA_SPEED_1G) {
            // Remove 1000mbps config applied while setting loopback.
            WRM(dev, INDY_ANEG_MSTR_SLV_CTRL, 0, INDY_F_ANEG_MSTR_SLV_CTRL_CFG_ENA |
                INDY_F_ANEG_MSTR_SLV_CTRL_CFG_VAL);
            // Enable aneg
            WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_ANEG_ENA | INDY_F_BASIC_CTRL_RESTART_ANEG,
                INDY_F_BASIC_CTRL_ANEG_ENA | INDY_F_BASIC_CTRL_RESTART_ANEG);
        }
        if (data->dev.rev <= 3) {
            EP_WR(dev, INDY_POWER_MGMT_MODE_5, 0x6677);
            EP_WR(dev, INDY_POWER_MGMT_MODE_6, 0x6677);
            EP_WR(dev, INDY_POWER_MGMT_MODE_8, 0x4377);
            EP_WR(dev, INDY_POWER_MGMT_MODE_11, 0x4377);
        }
    }
    if (loopback->connector_ena == TRUE) {
        WR(dev, INDY_RESV_CON_LOOP, 0xfc08);
    } else if (data->loopback.connector_ena == TRUE) {
        WR(dev, INDY_RESV_CON_LOOP, 0xfc00);
    }
    if (loopback->qsgmii_pcs_tbi_ena == TRUE) { // Enable tbi loopback
        EP_WRM(dev, INDY_QSGMII_PCS1G_DEBUG, INDY_F_QSGMII_PCS1G_DBG_TBI_HOST_LOOPBACK,
               INDY_F_QSGMII_PCS1G_DBG_TBI_HOST_LOOPBACK);
    } else if (data->loopback.qsgmii_pcs_tbi_ena == TRUE) { // Disable tbi loopback
        EP_WRM(dev, INDY_QSGMII_PCS1G_DEBUG, 0, INDY_F_QSGMII_PCS1G_DBG_TBI_HOST_LOOPBACK);
    }
    if (loopback->qsgmii_pcs_gmii_ena == TRUE) { // Enable gmii loopback
        EP_WRM(dev, INDY_QSGMII_PCS1G_DEBUG, INDY_F_QSGMII_PCS1G_DBG_GMII_LOOPBACK,
               INDY_F_QSGMII_PCS1G_DBG_GMII_LOOPBACK);
    } else if (data->loopback.qsgmii_pcs_gmii_ena == TRUE) { // Disable gmii loopback
        EP_WRM(dev, INDY_QSGMII_PCS1G_DEBUG, 0, INDY_F_QSGMII_PCS1G_DBG_GMII_LOOPBACK);
    }
    if (loopback->qsgmii_serdes_ena == TRUE) { // Enable qsgmii serdes loopback.
        // Serdes configuration would affect all the 4 ports.
        EP_WRM(dev, INDY_QSGMII_SERDES_MISC_CTRL, INDY_F_QSGMII_SERDES_MISC_CTRL_LB_MODE,
               INDY_F_QSGMII_SERDES_MISC_CTRL_LB_MODE);
    } else if (data->loopback.qsgmii_serdes_ena == TRUE) {
        EP_WRM(dev, INDY_QSGMII_SERDES_MISC_CTRL, 0, INDY_F_QSGMII_SERDES_MISC_CTRL_LB_MODE);
    }
    data->loopback = *loopback;
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "loopback enabled\n");
    return MEPA_RC_OK;
}
mepa_rc indy_loopback_get(struct mepa_device *dev, mepa_loopback_t *const loopback)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_ENTER(dev);
    *loopback = data->loopback;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}
// Returns gpio using port number and led number
static uint8_t led_num_to_gpio_mapping(mepa_device_t *dev, mepa_led_num_t led_num)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    uint8_t gpio = 11;// port 0 as default.
    switch (data->packet_idx) {
    case 0:
        gpio = led_num == MEPA_LED0 ? 11 : 12;
        break;
    case 1:
        gpio = led_num == MEPA_LED0 ? 17 : 18;
        break;
    case 2:
        gpio = led_num == MEPA_LED0 ? 19 : 20;
        break;
    case 3:
        gpio = led_num == MEPA_LED0 ? 13 : 14;
        break;
    default:
        // invalid.
        break;
    }
    T_I(MEPA_TRACE_GRP_GEN, "gpio mapped %d\n", gpio);
    return gpio;
}
static uint8_t led_mepa_mode_to_indy(mepa_gpio_mode_t mode)
{
    uint8_t ret = 0;
    switch (mode) {
    case MEPA_GPIO_MODE_LED_LINK_ACTIVITY:
        ret = 0;
        break;
    case MEPA_GPIO_MODE_LED_LINK1000_ACTIVITY:
        ret = 1;
        break;
    case MEPA_GPIO_MODE_LED_LINK100_ACTIVITY:
        ret = 2;
        break;
    case MEPA_GPIO_MODE_LED_LINK10_ACTIVITY:
        ret = 3;
        break;
    case MEPA_GPIO_MODE_LED_LINK100_1000_ACTIVITY:
        ret = 4;
        break;
    case MEPA_GPIO_MODE_LED_LINK10_1000_ACTIVITY:
        ret = 5;
        break;
    case MEPA_GPIO_MODE_LED_LINK10_100_ACTIVITY:
        ret = 6;
        break;
    case MEPA_GPIO_MODE_LED_DUPLEX_COLLISION:
        ret = 8;
        break;
    case MEPA_GPIO_MODE_LED_COLLISION:
        ret = 9;
        break;
    case MEPA_GPIO_MODE_LED_ACTIVITY:
        ret = 10;
        break;
    case MEPA_GPIO_MODE_LED_AUTONEGOTIATION_FAULT:
        ret = 12;
        break;
    case MEPA_GPIO_MODE_LED_FORCE_LED_OFF:
        ret = 14;
        break;
    case MEPA_GPIO_MODE_LED_FORCE_LED_ON:
        ret = 15;
        break;
    case MEPA_GPIO_MODE_LED_DISABLE_EXTENDED:
        ret = 0xf0;
        break;
    default:
        ret = 0xff; // Not valid for indy
        break;
    }
    return ret;
}
// In Indy, LED0 of software Api maps to LED1 of hardware,
//          LED1 of software Api maps to LED2 of hardware.
static mepa_rc indy_led_mode_set(mepa_device_t *dev, mepa_gpio_mode_t led_mode, mepa_led_num_t led_num)
{
    uint16_t mode;

    // Indy supports only LED0 and LED1
    if ((led_num != MEPA_LED0) && (led_num != MEPA_LED1)) {
        T_W(MEPA_TRACE_GRP_GEN, "8814 supports only leds 0 & 1\n");
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    if ((mode = led_mepa_mode_to_indy(led_mode)) == 0xff) {// Not valid
        T_W(MEPA_TRACE_GRP_GEN, "Not valid led mode");
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    if (mode == MEPA_GPIO_MODE_LED_DISABLE_EXTENDED) {
        // Normal operation
        EP_WRM(dev, INDY_LED_CONTROL_REG1, INDY_F_LED_CONTROL_KSZ_LED_MODE, INDY_F_LED_CONTROL_KSZ_LED_MODE);
    } else { // extended mode
        EP_WRM(dev, INDY_LED_CONTROL_REG1, 0, INDY_F_LED_CONTROL_KSZ_LED_MODE);
        EP_WRM(dev, INDY_LED_CONTROL_REG2, INDY_ENCODE_BITFIELD(mode, led_num * 4, 4), INDY_ENCODE_BITMASK(led_num * 4, 4));
    }
    return MEPA_RC_OK;
}
static mepa_rc indy_gpio_mode_private(mepa_device_t *dev, const mepa_gpio_conf_t *data)
{
    uint16_t gpio_en = 0, dir, val = 0, gpio_no = data->gpio_no;
    mepa_gpio_mode_t mode = data->mode;

    if (mode == MEPA_GPIO_MODE_OUT || mode == MEPA_GPIO_MODE_IN) {
        gpio_en = 1;
        dir = mode == MEPA_GPIO_MODE_OUT ? 1 : 0;
    } else if (mode >= MEPA_GPIO_MODE_LED_LINK_ACTIVITY && mode <= MEPA_GPIO_MODE_LED_DISABLE_EXTENDED) {
        MEPA_RC(indy_led_mode_set(dev, mode, data->led_num));
        // Enable alternative gpio mode for led.
        gpio_no = led_num_to_gpio_mapping(dev, data->led_num);
    } else if (mode == MEPA_GPIO_MODE_RCVRD_CLK_OUT1 || mode == MEPA_GPIO_MODE_RCVRD_CLK_OUT2) {
        gpio_no = mode == MEPA_GPIO_MODE_RCVRD_CLK_OUT1 ? 9 : 10;
    }
    if (gpio_no < 16) {
        val = 1 << gpio_no;
        dir = dir << gpio_no;
        EP_WRM(dev, INDY_GPIO_EN2, gpio_en ? val : 0, val);
        if (gpio_en) {
            EP_WRM(dev, INDY_GPIO_DIR2, dir, val);
        }
    } else if (gpio_no < 24) {
        val = 1 << (gpio_no - 16);
        dir = dir << (gpio_no - 16);
        EP_WRM(dev, INDY_GPIO_EN1, gpio_en ? val : 0, val);
        if (gpio_en) {
            EP_WRM(dev, INDY_GPIO_DIR1, dir, val);
        }
    } else {
        // Not supported. Illegal for Indy.
        T_W(MEPA_TRACE_GRP_GEN, "Not valid gpio on 8814 phy");
    }
    return MEPA_RC_OK;
}

// Set gpio mode to input, output or alternate function
static mepa_rc indy_gpio_mode_set(mepa_device_t *dev, const mepa_gpio_conf_t *gpio_conf)
{
    mepa_rc rc = MEPA_RC_OK;

    // Indy has 0-23 gpios.
    if (gpio_conf->gpio_no > 23) {
        T_W(MEPA_TRACE_GRP_GEN, "Not valid gpio on 8814 phy");
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    MEPA_ENTER(dev);
    rc = indy_gpio_mode_private(dev, gpio_conf);
    MEPA_EXIT(dev);
    return rc;
}

// Set Isolate mode
static mepa_rc indy_isolate_mode_conf(mepa_device_t *dev, const mepa_bool_t iso_en)
{

    MEPA_ENTER(dev);

    if (iso_en == TRUE) {
        WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_ISO_MODE_EN, INDY_F_BASIC_CTRL_ISO_MODE_EN);
    } else {
        WRM(dev, INDY_BASIC_CONTROL, 0, INDY_F_BASIC_CTRL_ISO_MODE_EN);
    }

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_gpio_out_set(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t value)
{
    uint16_t val = 0;

    // Indy has 0-23 gpios.
    if (gpio_no > 23) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    MEPA_ENTER(dev);
    if (gpio_no < 16) {
        val = 1 << gpio_no;
        EP_WRM(dev, INDY_GPIO_DATA2, value ? val : 0, val);
    } else if (gpio_no < 24) {
        val = 1 << (gpio_no - 16);
        EP_WRM(dev, INDY_GPIO_DATA1, value ? val : 0, val);
    } else {
        // Not supported. Illegal for Indy.
        T_W(MEPA_TRACE_GRP_GEN, "Not valid gpio on 8814 phy");
    }

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}
static mepa_rc indy_gpio_in_get(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t *const value)
{
    uint16_t val = 0;

    // Indy has 0-23 gpios.
    if (gpio_no > 23) {
        T_W(MEPA_TRACE_GRP_GEN, "Not valid gpio on 8814 phy");
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    MEPA_ENTER(dev);
    if (gpio_no < 16) {
        EP_RD(dev, INDY_GPIO_DATA2, &val);
        *value = (val >> gpio_no) & 0x1 ? TRUE : FALSE;
    } else if (gpio_no < 24) {
        EP_RD(dev, INDY_GPIO_DATA1, &val);
        *value = ((val >> (gpio_no - 16)) & 0x1) ? TRUE : FALSE;
    }
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_recovered_clk_set(mepa_device_t *dev, const mepa_synce_clock_conf_t *conf)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    mepa_gpio_conf_t gpio_conf;
    uint16_t divider = 1;
    uint16_t clkout_src = 7;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_ENTER(dev);
    // Enable recovered clock outputs in gpio
    gpio_conf.mode = (conf->dst == MEPA_SYNCE_CLOCK_DST_1) ? MEPA_GPIO_MODE_RCVRD_CLK_OUT1 : MEPA_GPIO_MODE_RCVRD_CLK_OUT2;
    rc = indy_gpio_mode_private(dev, &gpio_conf);

    switch (conf->freq) {
    case MEPA_FREQ_25M:
        divider = 5; // 125Mhz/25Mhz = 5
        break;
    case MEPA_FREQ_31_25M:
        divider = 4; // 125Mhz/31.25Mhz = 4
        break;
    case MEPA_FREQ_125M:
    default:
        divider = 1; // 125Mhz/125Mhz = 1
        break;
    }
    switch (conf->src) {
    case MEPA_SYNCE_CLOCK_SRC_DISABLED:
        clkout_src = 7; // Forces Recovered Clock Output to 0
        break;
    case MEPA_SYNCE_CLOCK_SRC_COPPER_MEDIA:
        clkout_src = data->packet_idx % 4;
        break;
    case MEPA_SYNCE_CLOCK_SRC_CLOCK_IN_1:
        clkout_src = 0b100; // Recovered Clock Input 1
        break;
    case MEPA_SYNCE_CLOCK_SRC_CLOCK_IN_2:
        clkout_src = 0b101; // Recovered Clock Input 2
        break;
    case MEPA_SYNCE_CLOCK_SRC_SERDES_MEDIA:
    default:
        T_W(MEPA_TRACE_GRP_GEN, "Invalid valid clock source, port-no : %d\n", dev->numeric_handle);
        break;
    }
    T_I(MEPA_TRACE_GRP_GEN, "port_ena %d divider %d\n", clkout_src, divider);
    if (conf->dst == MEPA_SYNCE_CLOCK_DST_1) {
        EP_WR(dev, INDY_RCVRD_CLK_OUT_SEL_1, clkout_src);
        EP_WR(dev, INDY_RCVRD_CLK_OUT_DIV_1, divider);
    } else if (conf->dst == MEPA_SYNCE_CLOCK_DST_2) {
        EP_WR(dev, INDY_RCVRD_CLK_OUT_SEL_2, clkout_src);
        EP_WR(dev, INDY_RCVRD_CLK_OUT_DIV_2, divider);
    }

    MEPA_EXIT(dev);

    data->synce_conf = *conf;
    return rc;
}
// Link the base port
static mepa_rc indy_link_base_port(mepa_device_t *dev, mepa_device_t *base_dev, uint8_t packet_idx)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    data->base_dev = base_dev;
    data->packet_idx = packet_idx;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    phy_data_t *base_data = data->base_dev ? ((phy_data_t *)(data->base_dev->data)) : NULL;

    phy_info->cap = 0;
    phy_info->part_number = 8814;
    phy_info->revision = data->dev.rev;
    phy_info->cap |= (data->dev.model == 0x26) ? MEPA_CAP_TS_MASK_GEN_3 : MEPA_CAP_TS_MASK_NONE;
    phy_info->cap |= MEPA_CAP_SPEED_MASK_1G;
    phy_info->ts_base_port = base_data ? base_data->port_no : 0;

    return MEPA_RC_OK;
}

// Open Alliance TC1 / TC12 DCQ Signal Quality Index(SQI) method.
// Default values of MSE(mean square error) in SQI Table registers(1.232 - 1.238) is used for mapping signal quality indices 0-7.
// SQI for pair A is returned from this function.
static mepa_rc indy_sqi_read(mepa_device_t *dev, uint32_t *const value)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t val;

    MEPA_ENTER(dev);

    // SQI is supported only for 100Mbps and 1Gbps
    // SQI values should not be available if link is down
    if ((data->conf.speed ==  MEPA_SPEED_10M) || !data->link_status || !data->conf.admin.enable) {
        MEPA_EXIT(dev);
        return MEPA_RC_ERROR;
    }

    EP_RD(dev, INDY_DCQ_CTRL, &val);
    val &= ~INDY_M_DCQ_CTRL_CHANNEL_MASK; // Getting SQI value for channel 0;
    val |= INDY_F_DCQ_CTRL_READ_CAPTURE; // Enable this bit for capturing SQI values
    EP_WR(dev, INDY_DCQ_CTRL, val);

    EP_RD(dev, INDY_DCQ_SQI, &val);

    *value = INDY_X_DCQ_SQI_VALUE(val);

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_port_flow_mapping_get(uint8_t packet_idx, mepa_bool_t ingress, int *map_val)
{
    switch (packet_idx % 4) {
    case 0:
        *map_val = ingress ? 1 : 0;
    break;
    case 1:
        *map_val = ingress ? 3 : 2;
    break;
    case 2:
        *map_val = ingress ? 5 : 4;
    break;
    case 3:
        *map_val = ingress ? 7 : 6;
    break;
    default:
        return MEPA_RC_ERROR;
    }

    return MEPA_RC_OK;
}

static mepa_rc indy_start_of_frame_conf_set(mepa_device_t *dev, mepa_start_of_frame_conf_t *const sof_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_gpio_conf_t gpio_conf;
    int rc = MEPA_RC_OK;
    uint16_t val;
    int map_val;

    MEPA_ENTER(dev);

    rc = indy_port_flow_mapping_get(data->packet_idx, sof_conf->ingress, &map_val);
    if (rc < 0) {
       MEPA_EXIT(dev);
       return rc;
    }

    EP_RD(dev, INDY_GPIO_SOF_SEL, &val);
    switch (sof_conf->sof_no) {
    case 0:
        val &= ~INDY_M_GPIO_SOF_SEL_SOF0;
        val |= map_val;
        gpio_conf.gpio_no = 15;
        break;
    case 1:
        val &= ~INDY_M_GPIO_SOF_SEL_SOF1;
        val |= (map_val << 3);
        gpio_conf.gpio_no = 21;
        break;
    case 2:
        val &= ~INDY_M_GPIO_SOF_SEL_SOF2;
        val |= (map_val << 6);
        gpio_conf.gpio_no = 16;
        break;
    case 3:
        val &= ~INDY_M_GPIO_SOF_SEL_SOF3;
        val |= (map_val << 9);
        gpio_conf.gpio_no = 23;
        break;
    default:
        MEPA_EXIT(dev);
        return MEPA_RC_ERROR;
    }

    if (sof_conf->sof_preemption_mode > 3) {
        MEPA_EXIT(dev);
        return MEPA_RC_ERROR;
    }

    // Enabling SOF for corresponding port, direction and GPIO
    EP_WR(dev, INDY_GPIO_SOF_SEL, val);

    // Enabling SOF preemption
    EP_RD(dev, INDY_SOF, &val);
    val &= ~INDY_M_SOF_PREEMPTION_ENABLE;
    val |= sof_conf->sof_preemption_mode << 8;
    EP_WR(dev, INDY_SOF, val);

    gpio_conf.mode = MEPA_GPIO_MODE_OUT;
    rc = indy_gpio_mode_private(dev, &gpio_conf);
    if (rc < 0) {
       MEPA_EXIT(dev);
       return rc;
    }

    data->sof_conf = *sof_conf;

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_start_of_frame_conf_get(mepa_device_t *dev, mepa_start_of_frame_conf_t *const value)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    *value = data->sof_conf;

    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_framepreempt_get(mepa_device_t *dev, mepa_bool_t *const value)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    phy_data_t *base_data = data->base_dev ? ((phy_data_t *)(data->base_dev->data)) : NULL;

    MEPA_ASSERT(value == NULL);
    MEPA_ENTER(dev);

    *value = (base_data ? base_data->framepreempt_en : FALSE);
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_selftest_start(struct mepa_device *dev, const mepa_selftest_info_t *inf)
{
    uint16_t val;
    uint8_t retry = 0;
    mepa_bool_t link_up = FALSE;

    if (inf == NULL)
	return MEPA_RC_ERROR;

    if ((inf->speed != MEPA_SPEED_1G) && (inf->mdi == MEPA_MEDIA_MODE_AUTO))
	return MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    EP_RD(dev, INDY_SELFTEST_PGEN_EN, &val);
    if (val & INDY_F_SELFTEST_PGEN_EN) {
        T_W(MEPA_TRACE_GRP_GEN, "Self-Test already enabled!\n");
        goto en_err;
    }

    //Reset PHY
    WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SOFT_RESET, INDY_F_BASIC_CTRL_SOFT_RESET);
    //wait for reset complete
    MEPA_MSLEEP(1);

    /* 1. Setup basic configuration */
    // Set AN
    val = INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1 |
	  INDY_F_BASIC_CTRL_DUP_MODE |
	  INDY_F_BASIC_CTRL_RESTART_ANEG |
	  INDY_F_BASIC_CTRL_ANEG_ENA;
    WR(dev, INDY_BASIC_CONTROL, val);
    MEPA_MSLEEP(10);

    if (inf->speed == MEPA_SPEED_1G) {
      // Enable Ext_lpbk bit in the Reserved Register
      WR(dev, INDY_RESV_CON_LOOP, 0xfc08);

      // Set Master-Slave configuration to master
      val = INDY_F_ANEG_MSTR_SLV_CTRL_1000_T_FULL_DUP |
	    INDY_F_ANEG_MSTR_SLV_CTRL_CFG_VAL |
	    INDY_F_ANEG_MSTR_SLV_CTRL_CFG_ENA;
      WR(dev, INDY_ANEG_MSTR_SLV_CTRL, val);

    } else /*< 10BASE-T and 100BASE-TX */ {
        // Disable Auto-MDIX and set the desired configuration (MDI vs. MDIX)
        RD(dev, INDY_GPHY_DBG_CTL1, &val);
        val &= ~INDY_F_MDI_SET;
        switch (inf->mdi) {
          case MEPA_MEDIA_MODE_MDI:
            val |= INDY_F_MDI_SET;
            // Fall through
          default:
            val |= INDY_F_SWAPOFF;
          break;
        }
        // Set the current MDI
        WRM(dev, INDY_GPHY_DBG_CTL1, val, INDY_DEF_MASK);
    }

    // Set force speed
    val = INDY_F_BASIC_CTRL_DUP_MODE;
    if (inf->speed == MEPA_SPEED_1G)
        val |= INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1;
    else if (inf->speed == MESA_SPEED_100M)
        val |= INDY_F_BASIC_CTRL_SPEED_SEL_BIT_0;
    WR(dev, INDY_BASIC_CONTROL, val);

    // Wait for link-up
    while(retry++ < 100) {
        RD(dev, INDY_BASIC_STATUS, &val);
        if (val & INDY_F_BASIC_STATUS_LINK_STATUS) {
	    link_up = TRUE;
            break;
        }
        MEPA_MSLEEP(10);
    }

    if (!link_up) {
        T_W(MEPA_TRACE_GRP_GEN, "Link Down!\n");
	    goto ret_err;
    }

    // 0.5secs delay before starting self-test
    MEPA_MSLEEP(500);

    // 2. setup number of packet gen. will run forever if not set
    EP_WR(dev, INDY_SELFTEST_FRAME_CNT, 0);
    EP_WR(dev, INDY_SELFTEST_PKT_CNT_LO, (inf->frames & 0xFFFF));
    EP_WR(dev, INDY_SELFTEST_PKT_CNT_HI, ((inf->frames & 0xFFFF0000) >> 16));
    EP_WR(dev, INDY_SELFTEST_FRAME_CNT, INDY_F_SELFTEST_FRAME_CNT_EN);

    // 3. enable the checking counter
    EP_WR(dev, INDY_SELFTEST_EN_REG, 0); //disble checker to clear counter
    val = INDY_F_SELFTEST_RX_CRC_CHK_EN |
	  INDY_F_SELFTEST_TX_CRC_CHK_EN |
	  INDY_F_SELFTEST_EN;
    EP_WR(dev, INDY_SELFTEST_EN_REG, val); //enable checker

    // 4. Start self-test
    EP_WR(dev, INDY_SELFTEST_PGEN_EN, INDY_F_SELFTEST_PGEN_EN);


    MEPA_EXIT(dev);
    return MEPA_RC_OK;

ret_err:
    MEPA_EXIT(dev);

    //Restore PHY Config
    indy_restore_config(dev);

    return MEPA_RC_ERROR;

en_err:
    MEPA_EXIT(dev);

    return MEPA_RC_ERROR;
}

static mepa_rc indy_selftest_read(struct mepa_device *dev, mepa_selftest_info_t *const inf)
{
    uint16_t val;
    uint16_t lo, hi;

    if (inf == NULL)
	return MEPA_RC_ERROR;

    inf->frames = 0;
    inf->good_cnt = 0;
    inf->err_cnt = 0;

    MEPA_ENTER(dev);

    EP_RD(dev, INDY_SELFTEST_PGEN_EN, &val);
    if (!(val & INDY_F_SELFTEST_PGEN_EN)) {
        T_W(MEPA_TRACE_GRP_GEN, "Self-Test is not Enabled!\n");
        goto ret_err;
    }

    inf->mdi = MEPA_MEDIA_MODE_AUTO;
    RD(dev, INDY_GPHY_DBG_CTL1, &val);
    if (val & INDY_F_MDI_SET)
        inf->mdi = MEPA_MEDIA_MODE_MDI;
    else if (val & INDY_F_SWAPOFF)
        inf->mdi = MEPA_MEDIA_MODE_MDIX;

    inf->speed = MESA_SPEED_10M;
    RD(dev, INDY_BASIC_CONTROL, &val);
    if (val & INDY_F_BASIC_CTRL_SPEED_SEL_BIT_0)
        inf->speed = MESA_SPEED_100M;
    else if (val & INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1)
        inf->speed = MESA_SPEED_1G;

    EP_RD(dev, INDY_SELFTEST_PKT_CNT_HI, &val);
    inf->frames = val;
    inf->frames = (inf->frames)<< 16;
    EP_RD(dev, INDY_SELFTEST_PKT_CNT_LO, &val);
    inf->frames |= val;

    // 5. check counter value
    lo = hi = 0;
    //Self-Test Correct Count HI Register / Self-Test Correct Count LO Register
    EP_RD(dev, INDY_SELFTEST_GOOD_CNT_LO, &lo);
    EP_RD(dev, INDY_SELFTEST_GOOD_CNT_HI, &hi);
    inf->good_cnt = hi;
    inf->good_cnt = ((inf->good_cnt) << 16) | lo;

    lo = hi = 0;
    //Self-Test Error Count HI Register / Self-Test Error Count LO Register
    EP_RD(dev, INDY_SELFTEST_ERR_CNT_LO, &lo);
    EP_RD(dev, INDY_SELFTEST_ERR_CNT_HI, &hi);
    inf->err_cnt = hi;
    inf->err_cnt = ((inf->err_cnt) << 16) | lo;

    T_D(MEPA_TRACE_GRP_GEN, "speed=%d mdi=%d frames=0x%x good=0x%x err=0x%x\n",
	inf->speed, inf->mdi, inf->frames, inf->good_cnt, inf->err_cnt);

    if (inf->frames && (inf->frames == (inf->good_cnt + inf->err_cnt)))
	indy_selftest_stop(dev);

    MEPA_EXIT(dev);

    return MEPA_RC_OK;

ret_err:
    MEPA_EXIT(dev);

    return MEPA_RC_ERROR;
}

static mepa_rc indy_serdes_set(mepa_device_t *dev, uint16_t addr, uint16_t data, uint8_t op_rd)
{
    uint16_t val;

    EP_WR(dev, INDY_SERDES_CR_ADDR, addr);
    if (!op_rd) {
        EP_WR(dev, INDY_SERDES_CR_DATA, data);
        EP_RD(dev, INDY_SERDES_CR_CONTROL, &val);
        val |= INDY_F_SERDES_CR_CONTROL_1 | INDY_F_SERDES_CR_CONTROL_0;
        EP_WR(dev, INDY_SERDES_CR_CONTROL, val);
    } else {
        EP_RD(dev, INDY_SERDES_CR_CONTROL, &val);
        val &= ~INDY_F_SERDES_CR_CONTROL_1;
        val |= INDY_F_SERDES_CR_CONTROL_0;
        EP_WR(dev, INDY_SERDES_CR_CONTROL, val);
        EP_RD(dev, INDY_SERDES_CR_DATA, &val);
    }
    return MEPA_RC_OK;
}

struct serd_set {
    uint16_t addr;
    uint16_t data;
    uint8_t op_rd;
};

static mepa_rc indy_prbs7_init(mepa_device_t *dev)
{
    mepa_rc rc;
    int i;

        struct serd_set serdes_settings[] = {
            {0x1018, 0x0aa8, 0},
            {0x1018, 0x0550, 0},
            {0x0011, 0x004c, 0}, // Disable rtune req (SSP_CR_SUP_DIG_MPLL_OVRD_IN_LO.SSP_CR_SUP_DIG_MPLL_OVRD_IN_LO_RTUNE_REQ)
            {0x0011, 0x084c, 0}, // Enable override (SSP_CR_SUP_DIG_MPLL_OVRD_IN_LO.SSP_CR_SUP_DIG_MPLL_OVRD_IN_LO_RTUNE_REQ_OVRD)
            {0x1001, 0x0040, 0}, // Set Tx Reset high (LANEX_DIG_TX_OVRD_IN_HI.TX_RESET)
            {0x1001, 0x00c0, 0}, // Enable override (LANEX_DIG_TX_OVRD_IN_HI.TX_RESET_OVRD)
            {0x1006, 0x1000, 0}, // Set Rx reset high (LANEX_DIG_RX_OVRD_IN_HI.RX_RESET)
            {0x1006, 0x3000, 0}, // Enable override (LANEX_DIG_RX_OVRD_IN_HI.RX_RESET_OVRD)
            {0x0011, 0x084e, 0}, // Enable override (SUP_DIG_MPLL_OVRD_IN_LO.MPLL_EN_OVRD)
            {0x1000, 0x0200, 0}, // Enable override (LANEX.DIG.TX.OVRD_IN_LO.TX_CM_EN_OVRD)
            {0x1000, 0x0280, 0}, // Enable override (LANEX.DIG.TX.OVRD_IN_LO.TX_EN_OVRD)
            {0x1005, 0x0008, 0}, // Enable override (LANEX.DIG.RX.OVRD_IN_LO.RX_PLL_EN_OVRD)
            {0x1005, 0x0028, 0}, // Enable override (LANEX_DIG_RX_OVRD_IN_LO.RX_DATA_EN_OVRD)
            {0x1000, 0x02a0, 0}, // Enable override (LANEX_DIG_TX_OVRD_IN_LO.TX_DATA_EN_OVRD)
            {0x0015, 0x0000, 0}, // Set MPLL Half Rate to 0
            {0x0015, 0x1000, 0},
            {0x0012, 0x0000, 0}, // Do not use FSEL override pins for multiplier for ssp (SUP.DIG.MPLL_OVRD_IN_HI.FSEL)
            {0x0012, 0x0200, 0}, // Enable FSEL override (SUP.DIG.MPLL_OVRD_IN_HI.FSEL_OVRD)
            {0x0013, 0x0000, 0}, // Write Fraction multipler to: 0x000 (SUP_DIG_SSC_OVRD_IN.SSC_REF_CLK_SEL)
            {0x0013, 0x0000, 0}, // Disable ssc override (SUP_DIG_SSC_OVRD_IN.SSC_EN)
            {0x0013, 0x2000, 0}, // Enable override (SUP_DIG_SSC_OVRD_IN.SSC_OVRD_IN_EN)
            {0x1001, 0x00c0, 0}, // Set TX lane rate (LANEX_DIG_TX_OVRD_IN_HI.TX_RATE) to 00
            {0x1001, 0x00c4, 0}, // Enable override (LANEX_DIG_TX_OVRD_IN_HI.TX_RATE_OVRD)
            {0x1006, 0x3000, 0}, // Set RX lane rate (LANEX_DIG_RX_OVRD_IN_HI.RX_RATE) to 00
            {0x1006, 0x3004, 0}, // Enable override (LANEX_DIG_RX_OVRD_IN_HI.RX_RATE_OVRD)
            {0x0012, 0x8200, 0}, // Set tx_vboost_lvl
            {0x0015, 0x5000, 0}, // Set los_bias
            {0x0015, 0x5009, 0}, // Set los_level
            {0x0015, 0x5029, 0}, // Set acjt_level
            {0x0015, 0x5429, 0}, // Set enable for tx_vboost_lvl/los_bias/los_level/acjt_level
            {0x1002, 0x007f, 0}, // Set the TX amplitude (LANEX_DIG_TX_OVRD_DRV_LO.AMPLITUDE)
            {0x1002, 0x0c7f, 0}, // Set the TX preemphasis (LANEX_DIG_TX_OVRD_DRV_LO.PREEMPH)
            {0x1002, 0x4c7f, 0}, // Enable override (LANEX_DIG_TX_OVRD_DRV_LO.EN)
            {0x1003, 0x0000, 0}, // Override tx_term_offset to 0 (LANE0_DIG_TX_OVRD_DRV_HI.TERM_OFFSET)
            {0x1003, 0x0020, 0}, // Enable override (LANE0_DIG_TX_OVRD_DRV_HI.EN)
            {0x0003, 0x0010, 0}, // Set Rtune to TX(SUP.DIG.RTUNE_DEBUG.TYPE)
            {0x0003, 0x0012, 0}, // Force Rtune High(SUP.DIG.RTUNE_DEBUG.MAN_TUNE)
            {0x0003, 0x0010, 0}, // Force Rtune Low(SUP.DIG.RTUNE_DEBUG.MAN_TUNE)
            {0x1001, 0x01c4, 0}, // Set tx_vboost_en (LANEX.DIG.TX.OVRD_IN_HI.TX_VBOOST_EN
            {0x1001, 0x03c4, 0}, // Enable override (LANEX.DIG.TX.OVRD_IN_LO.TX_VBOOST_EN_OVRD)
            {0x1006, 0x3004, 0}, // Set Rx Eq to use a fixed setting (LANEX.DIG.RX.OVRD_IN_HI.RX_EQ_EN)
            {0x1006, 0x3084, 0}, // Enable override (LANEX.DIG.RX.OVRD_IN_HI.RX_EQ_EN_OVRD)
            {0x1006, 0x3284, 0}, // Set Rx Eq value(LANEX_DIG_RX_OVRD_IN_HI.RX_EQ)
            {0x1006, 0x3a84, 0}, // Enable override (LANEX_DIG_RX_OVRD_IN_HI.RX_EQ_OVRD)
            {0x1006, 0x3a9c, 0}, // Set Rx Los filter to XAUI mode (LANEX.DIG.RX.OVRD_IN_HI.RX_LOS_FILTER)
            {0x1006, 0x3abc, 0}, // Enable override (LANEX.DIG.RX.OVRD_IN_HI.RX_LOS_FILTER_OVRD)
            {0x1005, 0x0028, 0}, // Set Rx Bit shift to 0(LANEX.DIG.RX.OVRD_IN_LO.RX_BIT_SHIFT)
            {0x1005, 0x0228, 0}, // Enable override (LANEX.DIG.RX.OVRD_IN_LO.RX_BIT_SHIFT_OVRD)
            {0x1005, 0x0228, 0}, // Set Rx invert bit to: 0 (LANEX.DIG.RX.OVRD_IN_LO.RX_INVERT)
            {0x1005, 0x022a, 0}, // Enable override (LANEX.DIG.RX.OVRD_IN_LO.RX_INVERT_OVRD)
            {0x1005, 0x122a, 0}, // Enable rx los(LANEX.DIG.RX.OVRD_IN_LO.RX_LOS_EN)
            {0x1005, 0x322a, 0}, // Enable override (LANEX.DIG.RX.OVRD_IN_LO.RX_LOS_EN_OVRD)
            {0x1005, 0x326a, 0}, // Set Rx Align(LANEX_DIG_RX_OVRD_IN_LO.RX_ALIGN_EN)
            {0x1005, 0x32ea, 0}, // Enable override (LANEX_DIG_RX_OVRD_IN_LO.RX_ALIGN_EN_OVRD)
            {0x1005, 0x36ea, 0}, // Set Term enable(LANEX_DIG_RX_OVRD_IN_LO.RX_TERM_EN)
            {0x1005, 0x3eea, 0}, // Enable override (LANEX_DIG_RX_OVRD_IN_LO.RX_TERM_EN_OVRD)
            {0x0012, 0x8600, 0}, // Reset MPll. Set bit to 1 (SUP_DIG_MPLL_OVRD_IN_HI.MPLL_RST)
            {0x0012, 0x8200, 0}, // Reset MPll. Set bit to 0 (SUP_DIG_MPLL_OVRD_IN_HI.MPLL_RST)
            {0x1015, 0x03e0, 0}, // Set pattern generator to send commas, not commas (LANEX_DIG_TX_LBERT_CTL.PAT0)
            {0x1015, 0x03e6, 0}, // Set pattern generator to correct mode (LANEX_DIG_TX_LBERT_CTL.MODE)
            {0x1001, 0x0384, 0}, // Set Tx Reset low (LANEX_DIG_TX_OVRD_IN_HI.TX_RESET)
            {0x1006, 0x2abc, 0}, // Set Rx reset low (LANEX_DIG_RX_OVRD_IN_HI.RX_RESET)
            {0x1005, 0x3eee, 0}, // Turn on RX PLL Enable (LANEX.DIG.RX.OVRD_IN_LO.RX_PLL_EN)
            {0x1005, 0x3efe, 0}, // Enable Rx(LANEX_DIG_RX_OVRD_IN_LO.RX_DATA_EN)
            {0x101c, 0x0000, 1}, // Verify CDR has locked
            {0x1005, 0x3ebe, 0}, // Turn off data alignment(LANEX_DIG_RX_OVRD_IN_LO.RX_ALIGN_EN)
            {0x1015, 0x25c6, 0}, // Set patten generator to selected pattern(LANEX_DIG_TX_LBERT_CTL.PAT0)
        };
        int arr_len = (sizeof(serdes_settings) / sizeof(struct serd_set));
        for (i = 0; i < arr_len; i++) {
            rc = indy_serdes_set(dev, serdes_settings[i].addr, serdes_settings[i].data, serdes_settings[i].op_rd);
            if (rc < 0)
                return rc;
        }
    return MEPA_RC_OK;
}

static mepa_rc indy_prbs7_clk(mepa_device_t *dev, mepa_prbs_clock_t clk)
{
    mepa_rc rc;
    int i;
    uint16_t val;

    EP_RD(dev, INDY_SERDES_CLOCK_CONF, &val);
    if(clk == MEPA_PRBS_CLK125_MHZ && val == 0x0016) {
         struct serd_set serdes_settings[] = {
            {0x0010, 0x0001, 0}, // Set ref_clock divider value to 1 (SUP_DIG_ATEOVRD.ref_clkdiv2)
            {0x0011, 0x08a2, 0}, // Set multiplier value (SUP_DIG_MPLL_OVRD_IN_LO.MPLL_MULTIPLIER)
            {0x0011, 0x0aa2, 0}, // Enable override (SUP_DIG_MPLL_OVRD_IN_LO.MPLL_MULTIPLIER_OVRD)
            {0x0011, 0x0aa3, 0}, // Enable MPLL (SUP_DIG_MPLL_OVRD_IN_LO.MPLL_EN)
        };
        int arr_len = (sizeof(serdes_settings) / sizeof(struct serd_set));
        for (i = 0; i < arr_len; i++) {
            rc = indy_serdes_set(dev, serdes_settings[i].addr, serdes_settings[i].data, serdes_settings[i].op_rd);
            if (rc < 0)
                return rc;
        }

    }
    else if (clk == MEPA_PRBS_CLK25_MHZ && val == 0x0006) {
        struct serd_set serdes_settings[] = {
            {0x0010, 0x0000, 0}, // Set ref_clock divider value to 0 (SUP_DIG_ATEOVRD.ref_clkdiv2)
            {0x0011, 0x0992, 0}, // Set multiplier value (SUP_DIG_MPLL_OVRD_IN_LO.MPLL_MULTIPLIER)
            {0x0011, 0x0b92, 0}, // Enable override (SUP_DIG_MPLL_OVRD_IN_LO.MPLL_MULTIPLIER_OVRD)
            {0x0011, 0x0b93, 0}, // Enable MPLL (SUP_DIG_MPLL_OVRD_IN_LO.MPLL_EN)
      };
        int arr_len = (sizeof(serdes_settings) / sizeof(struct serd_set));
        for (i = 0; i < arr_len; i++) {
            rc = indy_serdes_set(dev, serdes_settings[i].addr, serdes_settings[i].data, serdes_settings[i].op_rd);
            if (rc < 0)
                return rc;
        }
    }
    else if(clk == MEPA_PRBS_CLK125_MHZ && val == 0x0006)
        return MEPA_RC_ERROR;
    else
        return MEPA_RC_ERROR;
    return MEPA_RC_OK;
}

static mepa_rc indy_prbs7_loopback(mepa_device_t *dev, mepa_prbs_loopback_t loopback)
{
    mepa_rc rc;
    int i;
    if(loopback == MEPA_PRBS_INTERNAL_LOOPBACK) {
        struct serd_set serdes_settings[] = {
            {0x1000, 0x02a1, 0}, // Enable internal loopback (LANEX.DIG.TX.OVRD_IN_LO.LOOPBK_EN)
            {0x1000, 0x02a3, 0}, // Enable override (LANEX.DIG.TX.OVRD_IN_LO.TX_LOOPBK_EN_OVRD)
            {0x1000, 0x02a3, 0}, // Turn off Beacon Enable (LANEX.DIG.TX.OVRD_IN_LO.TX_BEACON_EN)
            {0x1000, 0x0aa3, 0}, // Enable override (LANEX.DIG.TX.OVRD_IN_LO.TX_BEACON_EN_OVRD)
            {0x1000, 0x0aa3, 0}, // Turn off tx_rx detect (LANEX.DIG.TX.OVRD_IN_LO.TX_DETECT_RX_REQ)
            {0x1000, 0x2aa3, 0}, // Enable override (LANEX.DIG.TX.OVRD_IN_LO.TX_DETECT_RX_REQ_OVRD)
            {0x1000, 0x2aa3, 0}, // Turn off tx invert (LANEX.DIG.TX.OVRD_IN_LO.TX_INVERT)
            {0x1000, 0x2aab, 0}, // Enable override (LANEX.DIG.TX.OVRD_IN_LO.TX_INVERT_OVRD)
            {0x1000, 0x2bab, 0}, // Set TX CM Enable (LANEX.DIG.TX.OVRD_IN_LO.TX_CM_EN)
            {0x1000, 0x2beb, 0}, // Turn on TX Enable (LANEX.DIG.TX.OVRD_IN_LO.TX_EN)
            {0x1000, 0x2bfb, 0}, // Set Tx Data Enable high(LANEX_DIG_TX_OVRD_IN_LO.TX_DATA_EN)
        };
        int arr_len = (sizeof(serdes_settings) / sizeof(struct serd_set));
        for (i = 0; i < arr_len; i++) {
            rc = indy_serdes_set(dev, serdes_settings[i].addr, serdes_settings[i].data, serdes_settings[i].op_rd);
            if (rc < 0)
                return rc;
        }
    }
    else
        return MEPA_RC_ERROR;
    return MEPA_RC_OK;
}

static mepa_rc indy_prbs7_enable(mepa_device_t *dev)
{
    mepa_rc rc;
    int i;
    struct serd_set serdes_settings[] = {
        {0x1015, 0x0000, 0},
        {0x1015, 0x25c4, 0}, // Set patten generator to selected mode(LANEX_DIG_TX_LBERT_CTL.MODE)
        {0x1016, 0x0004, 0}, // Set patten matcher to selected mode(LANEX_DIG_RX_LBERT_CTL.MODE)
        {0x1016, 0x0004, 0}, // Sync pattern matcher low(LANEX_DIG_RX_LBERT_CTL.SYNC)
        {0x1016, 0x0014, 0}, // Sync pattern matcher high(LANEX_DIG_RX_LBERT_CTL.SYNC)
        {0x1016, 0x0004, 0}, // Sync pattern matcher low(LANEX_DIG_RX_LBERT_CTL.SYNC)
        {0x1016, 0x0014, 0}, // Sync the patten matchers high (LANEX.DIG.RX.LBERT_CTL.SYNC)
        {0x1016, 0x0004, 0}, // Sync the pattern matchers low (LANEX.DIG.RX.LBERT_CTL.SYNC)
    };
    int arr_len = (sizeof(serdes_settings) / sizeof(struct serd_set));
    for (i = 0; i < arr_len; i++) {
        rc = indy_serdes_set(dev, serdes_settings[i].addr, serdes_settings[i].data, serdes_settings[i].op_rd);
        if (rc < 0)
            return rc;
    }
    return MEPA_RC_OK;
}

static mepa_rc indy_prbs7_set(mepa_device_t *dev, mepa_bool_t enable, mepa_prbs_clock_t clk, mepa_prbs_loopback_t loopback)
{
    mepa_rc rc = MEPA_RC_OK;

    if (enable) {
        rc = indy_prbs7_init(dev);
        if (rc < 0 )
            return rc;
        rc = indy_prbs7_loopback(dev,loopback);
        if (rc < 0 )
            return rc;
        rc = indy_prbs7_clk(dev, clk);
        if (rc < 0 )
            return rc;
        rc = indy_prbs7_enable(dev);
        if (rc < 0 )
            return rc;
    }
    else {
        rc = indy_serdes_set(dev, 0x1015,0x0000,0);
        if (rc < 0)
            return rc;

        //QSGMII Hard Reset
        EP_WR(dev, INDY_QSGMII_HARD_RESET,0x1);
    }

    return MEPA_RC_OK;
}

static mepa_rc indy_prbs_set(mepa_device_t *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const prbs_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    if (prbs_conf == NULL) {
        return MEPA_RC_ERROR;
    }

    if (type >= MEPA_PHY_PRBS_TYPE_CNT || direction >= MEPA_PHY_DIRECTION_CNT) {
        return MEPA_RC_ERROR;
    }

    if (direction == MEPA_PHY_DIRECTION_HOST && type == MEPA_PHY_PRBS_TYPE_SERDES) {
        mepa_rc rc = MEPA_RC_OK;

        if (prbs_conf->prbsn_sel == MEPA_PRBS7){

            MEPA_ENTER(dev);
            rc = indy_prbs7_set(dev, prbs_conf->enable, prbs_conf->clk, prbs_conf->loopback);
            MEPA_EXIT(dev);

            data->prbs_conf = *prbs_conf;
            return rc < 0 ? rc : MEPA_RC_OK;
        }
    }
    return MEPA_RC_ERROR;
}

static mepa_rc indy_prbs_get(mepa_device_t *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const prbs_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    *prbs_conf = data->prbs_conf;

    MEPA_EXIT(dev);

    return MEPA_RC_OK;

}

static mepa_rc indy_prbs_monitor_set(mepa_device_t *dev, mepa_phy_prbs_monitor_conf_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (value->prbsn_sel == MEPA_PRBS7) {
        MEPA_ENTER(dev);
        //Introducing one error into sequence
        rc = indy_serdes_set(dev, 0x1015, 0x0014, 0);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc indy_prbs_monitor_get(mepa_device_t *dev, mepa_phy_prbs_monitor_conf_t *const value)
{
    uint16_t val;

    if (value->prbsn_sel == MEPA_PRBS7) {

        MEPA_ENTER(dev);
        EP_WR(dev, INDY_SERDES_CR_ADDR, 0x1017); // Check for  errors
        EP_RD(dev, INDY_SERDES_CR_CONTROL, &val);
        val &= ~INDY_F_SERDES_CR_CONTROL_1;
        val |= INDY_F_SERDES_CR_CONTROL_0;
        EP_WR(dev, INDY_SERDES_CR_CONTROL, val);
        EP_RD(dev, INDY_SERDES_CR_DATA, &val);
        value->no_of_errors = val;
        MEPA_EXIT(dev);

        return MEPA_RC_OK;
    }
    return MEPA_RC_ERROR;
}

mepa_drivers_t mepa_lan8814_driver_init()
{
    static const int nr_indy_drivers = 2;
    static mepa_driver_t indy_drivers[] = {
        {
            .id = 0x221660,  // LAN8814 QSGMII standalone PHY
            .mask = 0xfffff0,
            .mepa_driver_delete = indy_delete,
            .mepa_driver_reset = indy_reset,
            .mepa_driver_poll = indy_poll,
            .mepa_driver_conf_set = indy_conf_set,
            .mepa_driver_conf_get = indy_conf_get,
            .mepa_driver_if_set = indy_if_set,
            .mepa_driver_if_get = indy_if_get,
            .mepa_driver_cable_diag_start = indy_cab_diag_start,
            .mepa_driver_cable_diag_get = indy_cab_diag_get,
            .mepa_driver_probe = indy_probe,
            .mepa_driver_aneg_status_get = indy_aneg_status_get,
            .mepa_driver_clause22_read = indy_direct_reg_read,
            .mepa_driver_clause22_write = indy_direct_reg_write,
            .mepa_driver_clause45_read  = indy_ext_mmd_reg_read,
            .mepa_driver_clause45_write = indy_ext_mmd_reg_write,
            .mepa_driver_event_enable_set = indy_event_enable_set,
            .mepa_driver_event_enable_get = indy_event_enable_get,
            .mepa_driver_event_poll = indy_event_status_poll,
            .mepa_driver_loopback_set = indy_loopback_set,
            .mepa_driver_loopback_get = indy_loopback_get,
            .mepa_driver_gpio_mode_set = indy_gpio_mode_set,
            .mepa_driver_gpio_out_set = indy_gpio_out_set,
            .mepa_driver_gpio_in_get = indy_gpio_in_get,
            .mepa_driver_link_base_port = indy_link_base_port,
            .mepa_ts = &indy_ts_drivers,
            .mepa_driver_synce_clock_conf_set = indy_recovered_clk_set,
            .mepa_driver_phy_info_get = indy_info_get,
            .mepa_driver_isolate_mode_conf = indy_isolate_mode_conf,
            .mepa_debug_info_dump = indy_debug_info_dump,
            .mepa_driver_sqi_read = indy_sqi_read,
            .mepa_driver_start_of_frame_conf_set = indy_start_of_frame_conf_set,
            .mepa_driver_start_of_frame_conf_get = indy_start_of_frame_conf_get,
            .mepa_driver_framepreempt_get = indy_framepreempt_get,
            .mepa_driver_selftest_start = indy_selftest_start,
            .mepa_driver_selftest_read = indy_selftest_read,
            .mepa_driver_prbs_set = indy_prbs_set,
            .mepa_driver_prbs_get = indy_prbs_get,
            .mepa_driver_prbs_monitor_set = indy_prbs_monitor_set,
            .mepa_driver_prbs_monitor_get = indy_prbs_monitor_get,
        },
        {
            .id = 0x221670,  // Single PHY based on LAN8814 instantiated in LAN966x
            .mask = 0xfffff0,
            .mepa_driver_delete = indy_delete,
            .mepa_driver_reset = indy_reset,
            .mepa_driver_poll = indy_poll,
            .mepa_driver_conf_set = indy_conf_set,
            .mepa_driver_conf_get = indy_conf_get,
            .mepa_driver_if_set = mas_if_set,
            .mepa_driver_if_get = mas_if_get,
            .mepa_driver_cable_diag_start = indy_cab_diag_start,
            .mepa_driver_cable_diag_get = indy_cab_diag_get,
            .mepa_driver_probe = indy_probe,
            .mepa_driver_aneg_status_get = indy_aneg_status_get,
            .mepa_driver_clause22_read = indy_direct_reg_read,
            .mepa_driver_clause22_write = indy_direct_reg_write,
            .mepa_driver_clause45_read  = indy_ext_mmd_reg_read,
            .mepa_driver_clause45_write = indy_ext_mmd_reg_write,
            .mepa_driver_event_enable_set = indy_event_enable_set,
            .mepa_driver_event_enable_get = indy_event_enable_get,
            .mepa_driver_event_poll = indy_event_status_poll,
            .mepa_driver_loopback_set = indy_loopback_set,
            .mepa_driver_loopback_get = indy_loopback_get,
            .mepa_driver_gpio_mode_set = indy_gpio_mode_set,
            .mepa_driver_gpio_out_set = indy_gpio_out_set,
            .mepa_driver_gpio_in_get = indy_gpio_in_get,
            .mepa_driver_synce_clock_conf_set = indy_recovered_clk_set,
            .mepa_driver_phy_info_get = indy_info_get,
            .mepa_driver_isolate_mode_conf = indy_isolate_mode_conf,
            .mepa_debug_info_dump = indy_debug_info_dump,
            .mepa_driver_sqi_read = indy_sqi_read,
            .mepa_driver_start_of_frame_conf_set = indy_start_of_frame_conf_set,
            .mepa_driver_start_of_frame_conf_get = indy_start_of_frame_conf_get,
            .mepa_driver_framepreempt_get = indy_framepreempt_get,
            .mepa_driver_selftest_start = indy_selftest_start,
            .mepa_driver_selftest_read = indy_selftest_read,
            .mepa_driver_prbs_set = indy_prbs_set,
            .mepa_driver_prbs_get = indy_prbs_get,
            .mepa_driver_prbs_monitor_set = indy_prbs_monitor_set,
            .mepa_driver_prbs_monitor_get = indy_prbs_monitor_get,
        },
    };

    mepa_drivers_t result;
    result.phy_drv = indy_drivers;
    result.count = nr_indy_drivers;

    return result;
}
