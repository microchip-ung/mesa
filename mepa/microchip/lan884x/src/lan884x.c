// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>

#include "../../common/include/lan8814_registers.h" // Re-use Indy register defines
#include "lan884x_private.h"

mepa_rc pfe_direct_reg_rd(mepa_device_t *dev, uint16_t addr, uint16_t *value)
{
    if (dev->callout->miim_read(dev->callout_ctx, addr, value) != MESA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Port %d miim read failed\n", dev->numeric_handle);
    }
    return MEPA_RC_OK;
}

mepa_rc pfe_direct_reg_wr(mepa_device_t *dev, uint16_t addr, uint16_t value, uint16_t mask)
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

// MMD read and write functions
// MMD device range : 0 - 31
mepa_rc pfe_mmd_reg_rd(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t *value)
{
    // Set-up to MMD register.
    MEPA_RC(pfe_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL, mmd, INDY_DEF_MASK));
    MEPA_RC(pfe_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(pfe_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL,
                               INDY_F_MMD_ACCESS_CTRL_MMD_FUNC | mmd, INDY_DEF_MASK));

    // Read the value
    MEPA_RC(pfe_direct_reg_rd(dev, INDY_MMD_ACCESS_ADDR_DATA, value));
    return MEPA_RC_OK;
}

mepa_rc pfe_mmd_reg_wr(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t value, uint16_t mask)
{
    // Set-up to MMD register.
    MEPA_RC(pfe_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL, mmd, INDY_DEF_MASK));
    MEPA_RC(pfe_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(pfe_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL,
                               INDY_F_MMD_ACCESS_CTRL_MMD_FUNC | mmd, INDY_DEF_MASK));

    // write the value
    MEPA_RC(pfe_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, value, mask));
    return MEPA_RC_OK;
}

static mepa_rc pfe_delete(mepa_device_t *dev)
{
    return mepa_delete_int(dev);
}

static mepa_rc pfe_get_device_info(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t id;

    pfe_direct_reg_rd(dev, INDY_DEVICE_ID_2, &id);

    data->dev.model = INDY_X_DEV_ID_MODEL(id);
    data->dev.rev = INDY_X_DEV_ID_REV(id);
    T_I(MEPA_TRACE_GRP_GEN, "model 0x%x rev %d\n", data->dev.model, data->dev.rev);

    return MEPA_RC_OK;
}

const char *if2txt(mesa_port_interface_t if_type)
{
    switch (if_type) {
    case MESA_PORT_INTERFACE_GMII:          return "GMII";
    case MESA_PORT_INTERFACE_RGMII:         return "RGMII";
    case MESA_PORT_INTERFACE_RGMII_ID:      return "RGMII_ID";
    case MESA_PORT_INTERFACE_RGMII_RXID:    return "RGMII_RXID";
    case MESA_PORT_INTERFACE_RGMII_TXID:    return "RGMII_TXID";
    default: return "?   ";
    }
}

static mepa_device_t *pfe_probe(mepa_driver_t *drv,
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

    T_I(MEPA_TRACE_GRP_GEN, "pfe driver probed for port %d", data->port_no);
    return dev;
}

static mepa_rc pfe_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    if (rst_conf->reset_point == MEPA_RESET_POINT_DEFAULT) {
        pfe_direct_reg_wr(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SOFT_RESET, INDY_F_BASIC_CTRL_SOFT_RESET);
    }
    MEPA_MSLEEP(1);
    pfe_get_device_info(dev);
    return MEPA_RC_OK;
}

static mepa_rc pfe_conf_get(mepa_device_t *dev, mepa_conf_t *const config)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    *config = data->conf;
    MEPA_EXIT(dev);
    T_D(MEPA_TRACE_GRP_GEN, "returning phy config on port %d", data->port_no);
    return MEPA_RC_OK;
}

static mesa_rc pfe_conf_set(mepa_device_t      *dev,
                            const mepa_conf_t  *config)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    MEPA_ENTER(dev);
    data->conf = *config;
    MEPA_EXIT(dev);

    return MESA_RC_OK;
}

static mesa_rc pfe_if_get(mepa_device_t *dev, mesa_port_speed_t speed,
                             mesa_port_interface_t *mac_if)
{
    uint16_t val=0, rxcdll_val, txcdll_val;
    mesa_rc rc;
    phy_data_t *data = (phy_data_t *)dev->data;

    rc = pfe_mmd_reg_rd(dev, 2, LAN8840_OPERATION_MODE_STRAP_LOW_REGISTER, &val);
    if(MEPA_RC_OK != rc) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not read from port %d", data->port_no);
    }

    if (val & LAN8840_OPERATION_MODE_STRAP_LOW_REGISTER_STRAP_RGMII_EN) {
        rc = pfe_mmd_reg_rd(dev, PFE_MMD_COMMON_CTRL_REG, PFE_RXC_DLL_CTRL, &rxcdll_val);
        rc |= pfe_mmd_reg_rd(dev, PFE_MMD_COMMON_CTRL_REG,  PFE_TXC_DLL_CTRL, &txcdll_val);
        if (rc != MEPA_RC_OK) {
            return rc;
        }

        if ((rxcdll_val & DISABLE_DLL_MASK) && (txcdll_val & DISABLE_DLL_MASK)) {
            *mac_if = MESA_PORT_INTERFACE_RGMII;
        } else if (!(rxcdll_val & DISABLE_DLL_MASK) && (txcdll_val & DISABLE_DLL_MASK)) {
            *mac_if = MESA_PORT_INTERFACE_RGMII_RXID;
        } else if ((rxcdll_val & DISABLE_DLL_MASK) && !(txcdll_val & DISABLE_DLL_MASK)) {
            *mac_if = MESA_PORT_INTERFACE_RGMII_TXID;
        } else {
            *mac_if = MESA_PORT_INTERFACE_RGMII_ID;
        }
    } else {
        *mac_if = MESA_PORT_INTERFACE_GMII;
    }


    return MESA_RC_OK;
}

static mepa_rc pfe_config_rgmii_delay(mepa_device_t *dev, mepa_port_interface_t interface)
{
	u16 rxcdll_val, txcdll_val;
    mepa_rc rc;

    // Note:
    // Extra phy delay in CONTROL_PAD_SKEW, RX_DATA_PAD_SKEW, TX_DATA_PAD_SKEW, CLK_PAD_SKEW
    // currently not supported

	switch (interface) {
	case MESA_PORT_INTERFACE_RGMII:
		rxcdll_val = DISABLE_DLL_RX_BIT;
		txcdll_val = DISABLE_DLL_TX_BIT;
		break;
	case MESA_PORT_INTERFACE_RGMII_ID:
		rxcdll_val = PFE_DLL_ENABLE_DELAY;
		txcdll_val = PFE_DLL_ENABLE_DELAY;
		break;
	case MESA_PORT_INTERFACE_RGMII_RXID:
		rxcdll_val = PFE_DLL_ENABLE_DELAY;
		txcdll_val = DISABLE_DLL_TX_BIT;
		break;
	case MESA_PORT_INTERFACE_RGMII_TXID:
		rxcdll_val = DISABLE_DLL_RX_BIT;
		txcdll_val = PFE_DLL_ENABLE_DELAY;
		break;
	default:
		return 0;
	}

	rc = pfe_mmd_reg_wr(dev, PFE_MMD_COMMON_CTRL_REG,
                        PFE_RXC_DLL_CTRL,
                        rxcdll_val, DISABLE_DLL_MASK);

    if (rc != MEPA_RC_OK) {
        return rc;
    }

	return pfe_mmd_reg_wr(dev, PFE_MMD_COMMON_CTRL_REG,
                          PFE_TXC_DLL_CTRL,
                          txcdll_val, DISABLE_DLL_MASK);
}

static mepa_rc pfe_if_set(mepa_device_t *dev,
                          mepa_port_interface_t mac_if)
{
    mepa_rc rc = MEPA_RC_OK;

    if (mac_if == MESA_PORT_INTERFACE_RGMII ||
        mac_if == MESA_PORT_INTERFACE_RGMII_ID ||
        mac_if == MESA_PORT_INTERFACE_RGMII_RXID ||
        mac_if == MESA_PORT_INTERFACE_RGMII_TXID) {
        rc = pfe_config_rgmii_delay(dev, mac_if);
    }

    return rc;
}

static mepa_rc pfe_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    phy_info->part_number = 8841;
    phy_info->revision = data->dev.rev;
    phy_info->cap = MEPA_CAP_SPEED_MASK_1G;

    return MEPA_RC_OK;
}

static mepa_rc pfe_poll(mepa_device_t *dev, mepa_status_t *status)
{
    uint16_t val, val2 = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_ENTER(dev);
    pfe_direct_reg_rd(dev, INDY_BASIC_STATUS, &val);
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
        pfe_direct_reg_rd(dev, INDY_ANEG_LP_BASE, &val);
        pfe_direct_reg_rd(dev, INDY_ANEG_MSTR_SLV_STATUS, &val2);
        // 1G half duplex is not supported. Refer direct register - 9
        if ((val2 & INDY_F_ANEG_MSTR_SLV_STATUS_1000_T_FULL_DUP) &&
            data->conf.aneg.speed_1g_fdx) {
            status->speed = MEPA_SPEED_1G;
            status->fdx = 1;
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
        pfe_direct_reg_rd(dev, INDY_BASIC_CONTROL, &val2);
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
    data->link_status = status->link;
    data->speed_status = status->speed;
    data->fdx_status   = status->fdx;
    MEPA_EXIT(dev);
    T_D(MEPA_TRACE_GRP_GEN, "port %d status link %d, speed %d, fdx %d", data->port_no, status->link, status->speed, status->fdx);
    return MEPA_RC_OK;
}

static mepa_rc pfe_aneg_status_get(mepa_device_t *dev, mepa_aneg_status_t *status)
{
    uint16_t val;

    MEPA_ENTER(dev);
    pfe_direct_reg_rd(dev, INDY_ANEG_MSTR_SLV_STATUS, &val);
    status->master_cfg_fault = (val & INDY_F_ANEG_MSTR_SLV_STATUS_CFG_FAULT) ? TRUE : FALSE;
    status->master = val & INDY_F_ANEG_MSTR_SLV_STATUS_CFG_RES ? TRUE : FALSE;
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "aneg status get mstr %d", status->master);
    return MEPA_RC_OK;
}

// read direct registers for debugging
static mepa_rc pfe_direct_reg_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    mepa_rc rc;
    uint16_t addr = address & 0x1f;

    MEPA_ENTER(dev);
    rc = pfe_direct_reg_rd(dev, addr, value);
    MEPA_EXIT(dev);
    return rc;
}

// write direct registers. Used for debugging.
static mepa_rc pfe_direct_reg_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    mepa_rc rc;
    uint16_t addr = address & 0x1f;

    MEPA_ENTER(dev);
    rc = pfe_direct_reg_wr(dev, addr, value, 0xFFFF);
    MEPA_EXIT(dev);
    return rc;
}

// read extended page/mmd register for debugging
static mepa_rc pfe_ext_mmd_reg_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;

    MEPA_ENTER(dev);
    if (mmd) {
        rc = pfe_mmd_reg_rd(dev, mmd, addr, value);
    }
    MEPA_EXIT(dev);
    return rc;
}

// write extended page/mmd register. Used for debugging.
static mepa_rc pfe_ext_mmd_reg_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;

    MEPA_ENTER(dev);
    if (mmd) {
        rc = pfe_mmd_reg_wr(dev, mmd, addr, value, 0xFFFF);
    }
    MEPA_EXIT(dev);
    return rc;
}

static void pfe_phy_deb_pr_reg(mepa_device_t *dev,
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
        rc = pfe_mmd_reg_rd(dev, mmd, addr, value);
    } else {
        rc = pfe_direct_reg_rd(dev, addr, value);
    }
    if(pr && (MEPA_RC_OK == rc)) {
        pr("%-45s:  0x%02x  0x%02x   0x%04x     0x%08x\n", str, to_u32(port_no), id, addr, *value);
    }
}

static mepa_rc reg_dump(struct mepa_device *dev,
                            const mepa_debug_print_t pr)
{
    uint16_t val = 0;

    //Direct registers
    pr("%-45s   PORT_NO PAGE_ID REG_ADDR   VALUE\n", "REG_NAME");
    pr("Main Page Registers\n");
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 0, "Basic Control Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 1, "Basic Status Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 2, "Device Identifier 1 Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 3, "Device Identifier 2 Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 4, "Auto-Negotiation Advertisement Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 5, "Auto-Negotiation Link Partner Base Page Ability Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 6, "Auto-Negotiation Expansion Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 7, "Auto-Negotiation Next Page TX Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 8, "Auto-Negotiation Next Page RX Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 9, "Auto-Negotiation Master Slave Control Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 10, "Auto-Negotiation Master Slave Status Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 13, "MMD Access Control Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 14, "MMD Access Address/Data Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 15, "Extended Status Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 16, "PCS Loop-back Lane Skew Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 17, "PCS Loop-back Swap/Polarity Control Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 18, "Cable Diagnostic Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 19, "Digital PMA/PCS Status Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 20, "Digital AX/AN Status Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 21, "RXER Counter Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 22, "LED Mode Select Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 23, "LED Behavior Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 24, "Interrupt Enable Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 25, "Output control Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 26, "UNH Test Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 27, "Interrupt Status Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 28, "Digital Debug Control 1 Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 29, "Digital Debug Control 2 Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 30, "Reserved Register", &val);
    pfe_phy_deb_pr_reg(dev, pr, 0, 0, 31, "Control Register", &val);
    return MEPA_RC_OK;
}


static mepa_rc pfe_debug_info_dump(struct mepa_device *dev,
                                    const mepa_debug_print_t pr,
                                    const mepa_debug_info_t   *const info)
{
    mepa_rc rc = MEPA_RC_OK;
    mepa_phy_info_t phy_info;
    mesa_port_interface_t mac_if = 0;

    (void)pfe_info_get(dev, &phy_info);
    (void)pfe_if_get(dev, 1000,  &mac_if);

    if (info->layer == MEPA_DEBUG_LAYER_AIL || info->layer == MEPA_DEBUG_LAYER_ALL) {
        MEPA_ENTER(dev);
        pr("Port:%d   Family:Pfeiffer   Type:%d   Rev:%d   MacIf:%s\n",dev->numeric_handle,
           phy_info.part_number, phy_info.revision, if2txt(mac_if));
        MEPA_EXIT(dev);
    }

    if (info->layer == MEPA_DEBUG_LAYER_CIL || info->layer == MEPA_DEBUG_LAYER_ALL) {

        switch(info->group)
        {
        case MEPA_DEBUG_GROUP_ALL:
        case MEPA_DEBUG_GROUP_PHY:
        {
            MEPA_ENTER(dev);
            rc = reg_dump(dev, pr);
            MEPA_EXIT(dev);
        }
        break;
        default:
            rc = MEPA_RC_OK;
        }

    }
    return rc;
}

mepa_drivers_t mepa_lan884x_driver_init()
{
    static const int nr_pfeiffer_drivers = 1;
    static mepa_driver_t pfeiffer_drivers[] = {
        {
            .id = 0x221650,  // Pfeiffer RGMII/GMII PHY
            .mask = 0xfffff0,
            .mepa_driver_delete = pfe_delete,
            .mepa_driver_reset = pfe_reset,
            .mepa_driver_poll = pfe_poll,
            .mepa_driver_conf_set = pfe_conf_set,
            .mepa_driver_conf_get = pfe_conf_get,
            .mepa_driver_if_set = pfe_if_set,
            .mepa_driver_if_get = pfe_if_get,
            .mepa_driver_probe = pfe_probe,
            .mepa_driver_aneg_status_get = pfe_aneg_status_get,
            .mepa_driver_clause22_read = pfe_direct_reg_read,
            .mepa_driver_clause22_write = pfe_direct_reg_write,
            .mepa_driver_clause45_read  = pfe_ext_mmd_reg_read,
            .mepa_driver_clause45_write = pfe_ext_mmd_reg_write,
            .mepa_driver_phy_info_get = pfe_info_get,
            .mepa_debug_info_dump = pfe_debug_info_dump,
        },
    };

    mepa_drivers_t result;
    result.phy_drv = pfeiffer_drivers;
    result.count = nr_pfeiffer_drivers;

    return result;
}
