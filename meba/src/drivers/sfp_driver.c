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

#include <ctype.h>
#include <mscc/ethernet/board/api.h>
#include <unistd.h>
#include "../meba_aux.h"

/* Get array size */
#define VTSS_ARRSZ(t)          /*lint -e{574} */                             \
    (sizeof(t) / sizeof(t[0])) /* Suppress Lint Warning 574: Signed-unsigned \
                                  mix with relational */

typedef struct {
    mesa_port_no_t port_no;
    mesa_inst_t inst;
    meba_inst_t meba_inst;
} sfp_data_t;

static mesa_rc dev_delete(meba_sfp_device_t *dev) {
    sfp_data_t *data = (sfp_data_t *)dev->data;
    free(data);
    free(dev);
    dev = NULL;
    return MESA_RC_OK;
}

static mesa_rc dev_reset(meba_sfp_device_t *dev) { return MESA_RC_OK; }

static mesa_rc dev_poll(meba_sfp_device_t *dev,
                        meba_sfp_driver_status_t *status) {
    sfp_data_t *data = (sfp_data_t *)(dev->data);
    mesa_port_status_t mesa_status = {};

    mesa_rc rc = mesa_port_status_get(data->inst, data->port_no, &mesa_status);
    if (rc != MESA_RC_OK) return rc;

    status->link = mesa_status.link;
    status->speed = mesa_status.speed;
    status->fdx = mesa_status.fdx;

    if (data->meba_inst->api.meba_sfp_status_get)
        rc = data->meba_inst->api.meba_sfp_status_get(data->meba_inst,
                                                      data->port_no, &dev->sfp);
    if (rc != MESA_RC_OK) return rc;

    // fill up status
    status->los = dev->sfp.los;

    return MESA_RC_OK;
}

static mesa_rc cisco_sgmii_phy_read(meba_inst_t meba_inst,
                                    mesa_port_no_t port_no, uint8_t addr,
                                    uint16_t *value) {
    uint8_t data[2];

    mesa_rc rc = meba_inst->api.meba_sfp_i2c_xfer(meba_inst, port_no, false,
                                                  0x56, addr, data, 2, true);
    if (rc != MESA_RC_OK) return MESA_RC_OK;

    *value = ((data[0] << 8) | data[1]);
    return MESA_RC_OK;
}

// Write PHY register via I2C
static mesa_rc cisco_sgmii_phy_write(meba_inst_t meba_inst,
                                     mesa_port_no_t port_no, uint8_t addr,
                                     uint16_t value) {
    uint8_t data[2];

    data[0] = ((value >> 8) & 0xff);
    data[1] = (value & 0xff);
    return meba_inst->api.meba_sfp_i2c_xfer(meba_inst, port_no, true, 0x56,
                                            addr, data, 2, true);
}

#define VTSS_MSLEEP(m) usleep((m)*1000)
static mesa_bool_t cisco_sgmii_set(meba_inst_t meba_inst,
                                   mesa_port_no_t port_no) {
    uint16_t i, reg2 = 0, reg3 = 0;

    // Read PHY ID registers
    mesa_bool_t phy_present = false;
    for (i = 0; i < 10; i++) {
        if (cisco_sgmii_phy_read(meba_inst, port_no, 2, &reg2) == MESA_RC_OK &&
            cisco_sgmii_phy_read(meba_inst, port_no, 3, &reg3) == MESA_RC_OK) {
            phy_present = true;
            break;
        }
        VTSS_MSLEEP(50);  // Wait while the SFP module wakes up
    }

    //  BZ#22772:
    //  If Cu-SFP is default using SGMII mode, we don't need to setup PHY
    //  Else this Cu-SFP must be set to SGMII mode via I2C. However,
    //  this kind of configuration is not standard and implemented by
    //  different SFP manufacturers.
    //  Currently, we only set it for Marvell 88EE1111.
    if (phy_present == false || reg2 != 0x0141 || (reg3 & 0xfff0) != 0x0cc0) {
        /* The PHY is not Marvell 88E1111 */
        return false;
    }

    // The SFP's PHY supports SGMII(at present, only Marvell 88E1111 is
    // supported), execute follwoing setting to configure to SGMII mode
    for (i = 0; i < 10; i++) {
        if (cisco_sgmii_phy_write(meba_inst, port_no, 27, 0x9084) ==
                MESA_RC_OK &&  // SGMII mode
            cisco_sgmii_phy_write(meba_inst, port_no, 9, 0x0f00) ==
                MESA_RC_OK &&  // Advertise 1000BASE-T Full/Half-Duplex
            cisco_sgmii_phy_write(meba_inst, port_no, 0, 0x8140) ==
                MESA_RC_OK &&  // Apply Software reset
            cisco_sgmii_phy_write(meba_inst, port_no, 4, 0x0de1) ==
                MESA_RC_OK &&  // Advertise 10/100BASE-T Full/Half-Duplex
            cisco_sgmii_phy_write(meba_inst, port_no, 0, 0x9140) ==
                MESA_RC_OK) {  // Apply Software reset
            return true;
        }
        VTSS_MSLEEP(50);  // Wait while the SFP module wakes up
    }
    return false;
}

static mesa_rc cisco_sgmii_conf_set(meba_sfp_device_t *dev,
                                    const meba_sfp_driver_conf_t *conf) {
    sfp_data_t *data = (sfp_data_t *)(dev->data);

    if (conf->admin.enable && !cisco_sgmii_set(data->meba_inst, data->port_no))
        return MESA_RC_ERROR;

    return MESA_RC_OK;
}

static mesa_rc cisco_sgmii_if_get(meba_sfp_device_t *dev,
                                  mesa_port_speed_t speed,
                                  mesa_port_interface_t *mac_if) {
    switch (speed) {
        case MESA_SPEED_AUTO:
            *mac_if = MESA_PORT_INTERFACE_SGMII_CISCO;
            return MESA_RC_OK;
        default:
            // Set the same interface, even the user sets wrong speed,
            // so we will have one interface.
            *mac_if = MESA_PORT_INTERFACE_SGMII_CISCO;
            return MESA_RC_ERROR;
    }
}

static meba_sfp_device_t *dev_probe(meba_sfp_driver_t *drv,
                                    const meba_sfp_driver_address_t *mode,
                                    const meba_sfp_device_info_t *info) {
    if (mode->mode != mscc_sfp_driver_address_mode) return NULL;

    meba_sfp_device_t *device =
        (meba_sfp_device_t *)calloc(1, sizeof(meba_sfp_device_t));

    if (device == NULL) goto out_device;

    sfp_data_t *data = (sfp_data_t *)calloc(1, sizeof(sfp_data_t));

    if (data == NULL) goto out_data;

    device->drv = drv;
    data->inst = mode->val.mscc_address.inst;
    data->meba_inst = mode->val.mscc_address.meba_inst;
    data->port_no = mode->val.mscc_address.port_no;
    device->data = data;
    device->info = *info;

    device->sfp.present = true;
    device->sfp.los = false;
    device->sfp.tx_fault = false;

    return device;

out_data:
    free(device);
out_device:
    return NULL;
}

static mesa_rc serdes_if_get(meba_sfp_device_t *dev, mesa_port_speed_t speed,
                             mesa_port_interface_t *mac_if) {
    switch (speed) {
        case MESA_SPEED_100M:
            *mac_if = MESA_PORT_INTERFACE_100FX;
            return MESA_RC_OK;
        case MESA_SPEED_AUTO:
        case MESA_SPEED_1G:
            *mac_if = MESA_PORT_INTERFACE_SERDES;
            return MESA_RC_OK;
        default:
            *mac_if = MESA_PORT_INTERFACE_SERDES;
            return MESA_RC_ERROR;
    }
}

static mesa_rc serdes_conf_set(meba_sfp_device_t *dev,
                               const meba_sfp_driver_conf_t *conf) {
    sfp_data_t *data = (sfp_data_t *)(dev->data);
    mesa_port_clause_37_control_t control = {};
    mesa_port_clause_37_adv_t *adv = NULL;

    control.enable = conf->speed == MESA_SPEED_AUTO ? true : false;
    adv = &control.advertisement;
    adv->fdx = true;
    adv->hdx = false;
    adv->symmetric_pause = conf->flow_control;
    adv->asymmetric_pause = conf->flow_control;
    adv->remote_fault = conf->admin.enable ? MESA_PORT_CLAUSE_37_RF_LINK_OK
                                           : MESA_PORT_CLAUSE_37_RF_OFFLINE;
    adv->acknowledge = 0;
    adv->next_page = 0;

    mesa_port_clause_37_control_t ctrl_now = {};
    mesa_port_clause_37_control_get(data->inst, data->port_no, &ctrl_now);
    if (memcmp(&control, &ctrl_now, sizeof(control)) != 0) {
        return mesa_port_clause_37_control_set(data->inst, data->port_no,
                                               &control);
    }

    return MESA_RC_OK;
}

static mesa_rc fx_if_get(meba_sfp_device_t *dev, mesa_port_speed_t speed,
                         mesa_port_interface_t *mac_if) {
    *mac_if = MESA_PORT_INTERFACE_100FX;
    switch (speed) {
        case MESA_SPEED_AUTO:
        case MESA_SPEED_100M:
            return MESA_RC_OK;
        default:
            return MESA_RC_ERROR;
    }
}

static mesa_rc sfi_if_get(meba_sfp_device_t *dev, mesa_port_speed_t speed,
                          mesa_port_interface_t *mac_if) {
    switch (speed) {
        case MESA_SPEED_AUTO:
        case MESA_SPEED_1G:
            *mac_if = MESA_PORT_INTERFACE_SERDES;
            return MESA_RC_OK;
        case MESA_SPEED_2500M:
            *mac_if = MESA_PORT_INTERFACE_VAUI;
            return MESA_RC_OK;
        case MESA_SPEED_100M:
            *mac_if = MESA_PORT_INTERFACE_100FX;
            return MESA_RC_OK;
        case MESA_SPEED_5G:
        case MESA_SPEED_10G:
        case MESA_SPEED_25G:
            *mac_if = MESA_PORT_INTERFACE_SFI;
            return MESA_RC_OK;
        default:
            *mac_if = MESA_PORT_INTERFACE_SFI;
            return MESA_RC_ERROR;
    }
}

static mesa_rc sfi_mt_none_get(meba_sfp_device_t *dev,
                                mesa_sd10g_media_type_t *mt) {
    *mt = MESA_SD10G_MEDIA_PR_NONE;
    return MESA_RC_OK;
}

static mesa_rc sfi_mt_get(meba_sfp_device_t *dev,
                                mesa_sd10g_media_type_t *mt) {
    *mt = MESA_SD10G_MEDIA_SR;
    return MESA_RC_OK;
}

static mesa_rc sfi_mt_zr_get(meba_sfp_device_t *dev,
                             mesa_sd10g_media_type_t *mt) {

    *mt = MESA_SD10G_MEDIA_ZR;
    return MESA_RC_OK;
}

static mesa_rc sfi_mt_dac_get(meba_sfp_device_t *dev,
                             mesa_sd10g_media_type_t *mt) {
    *mt = MESA_SD10G_MEDIA_DAC;
    return MESA_RC_OK;
}

static mesa_rc tr_1000_sx_get(meba_sfp_device_t *dev,
                              meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_1000BASE_SX;
    return MESA_RC_OK;
}

static mesa_rc tr_1000_lx_get(meba_sfp_device_t *dev,
                              meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_1000BASE_LX;
    return MESA_RC_OK;
}

static mesa_rc tr_1000_zx_get(meba_sfp_device_t *dev,
                              meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_1000BASE_ZX;
    return MESA_RC_OK;
}

static mesa_rc tr_1000_cx_get(meba_sfp_device_t *dev,
                              meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_1000BASE_CX;
    return MESA_RC_OK;
}

static mesa_rc tr_1000_t_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_1000BASE_T;
    return MESA_RC_OK;
}

static mesa_rc tr_1000_x_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_1000BASE_X;
    return MESA_RC_OK;
}

static mesa_rc tr_2g5_get(meba_sfp_device_t *dev,
                          meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_2G5;
    return MESA_RC_OK;
}

static mesa_rc tr_5g_get(meba_sfp_device_t *dev, meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_5G;
    return MESA_RC_OK;
}

static mesa_rc tr_10g_get(meba_sfp_device_t *dev,
                          meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_10G;
    return MESA_RC_OK;
}

static mesa_rc tr_10g_dac_get(meba_sfp_device_t *dev,
                              meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_10G_DAC;
    return MESA_RC_OK;
}

static mesa_rc tr_10g_sr_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_10G_SR;
    return MESA_RC_OK;
}

static mesa_rc tr_10g_lr_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_10G_LR;
    return MESA_RC_OK;
}

static mesa_rc tr_10g_er_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_10G_ER;
    return MESA_RC_OK;
}

static mesa_rc tr_10g_lrm_get(meba_sfp_device_t *dev,
                              meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_10G_LRM;
    return MESA_RC_OK;
}

static mesa_rc tr_25g_get(meba_sfp_device_t *dev,
                          meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_25G;
    return MESA_RC_OK;
}

static mesa_rc tr_25g_dac_get(meba_sfp_device_t *dev,
                              meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_25G_DAC;
    return MESA_RC_OK;
}

static mesa_rc tr_25g_sr_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_25G_SR;
    return MESA_RC_OK;
}

static mesa_rc tr_25g_lr_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_25G_LR;
    return MESA_RC_OK;
}

static mesa_rc tr_25g_er_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_25G_ER;
    return MESA_RC_OK;
}

static mesa_rc tr_25g_lrm_get(meba_sfp_device_t *dev,
                              meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_25G_LRM;
    return MESA_RC_OK;
}

static mesa_rc tr_100_fx_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_100FX;
    return MESA_RC_OK;
}

static mesa_rc tr_100_lx_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_100BASE_LX;
    return MESA_RC_OK;
}

static mesa_rc tr_100_zx_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_100BASE_ZX;
    return MESA_RC_OK;
}

static mesa_rc tr_100_sx_get(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr) {
    *tr = MEBA_SFP_TRANSRECEIVER_100BASE_SX;
    return MESA_RC_OK;
}

meba_sfp_drivers_t meba_cisco_driver_init() {
    static meba_sfp_driver_t cisco_drivers[] = {
        {
            .product_name = "SP7041-R",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = cisco_sgmii_conf_set,
            .meba_sfp_driver_if_get = cisco_sgmii_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_t_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "AFBR-5715APZ-CS4",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = serdes_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_sx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "FTLF8519P2BCL-C4",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = serdes_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_sx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "SPP5100SR-C5",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = sfi_if_get,
            .meba_sfp_driver_mt_get = sfi_mt_get,
            .meba_sfp_driver_tr_get = tr_10g_sr_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "SFBR-7702SDZ-CS5",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = sfi_if_get,
            .meba_sfp_driver_mt_get = sfi_mt_get,
            .meba_sfp_driver_tr_get = tr_10g_sr_get,
            .meba_sfp_driver_probe = dev_probe,
        }};

    meba_sfp_drivers_t result;
    result.sfp_drv = cisco_drivers;
    result.count = VTSS_ARRSZ(cisco_drivers);

    return result;
}

meba_sfp_drivers_t meba_axcen_driver_init() {
    static meba_sfp_driver_t axcen_drivers[] = {
        {
            .product_name = "AXFE-1314-0521",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = fx_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_100_fx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "AXGE-5854-0511",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = serdes_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_sx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "AXGT-R1T4-05I1",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = cisco_sgmii_conf_set,
            .meba_sfp_driver_if_get = cisco_sgmii_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_t_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "AXFE-1314-0531",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = fx_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_100_lx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "AXXE-5886-05B1",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = sfi_if_get,
            .meba_sfp_driver_mt_get = sfi_mt_get,
            .meba_sfp_driver_tr_get = tr_10g_sr_get,
            .meba_sfp_driver_probe = dev_probe,
        }};

    meba_sfp_drivers_t result;
    result.sfp_drv = axcen_drivers;
    result.count = VTSS_ARRSZ(axcen_drivers);

    return result;
}

meba_sfp_drivers_t meba_finisar_driver_init() {
    static meba_sfp_driver_t finisar_drivers[] = {
        {
            .product_name = "FTLX8571D3BCL",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = sfi_if_get,
            .meba_sfp_driver_mt_get = sfi_mt_get,
            .meba_sfp_driver_tr_get = tr_10g_sr_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "SPT-SFP+C1",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = sfi_if_get,
            .meba_sfp_driver_mt_get = sfi_mt_get,
            .meba_sfp_driver_tr_get = tr_10g_dac_get,
            .meba_sfp_driver_probe = dev_probe,
        }};

    meba_sfp_drivers_t result;
    result.sfp_drv = finisar_drivers;
    result.count = VTSS_ARRSZ(finisar_drivers);

    return result;
}

meba_sfp_drivers_t meba_hp_driver_init() {
    static meba_sfp_driver_t hp_drivers[] = {
        {
            .product_name = "WST-SEAMCV-A6H",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = cisco_sgmii_conf_set,
            .meba_sfp_driver_if_get = cisco_sgmii_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_t_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "SP7041-HPB-3-R",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = cisco_sgmii_conf_set,
            .meba_sfp_driver_if_get = cisco_sgmii_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_t_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "TRF5326ANLB404",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = fx_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_100_fx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "RTXM191-400",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = serdes_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_lx_get,
            .meba_sfp_driver_probe = dev_probe,
        }};

    meba_sfp_drivers_t result;
    result.sfp_drv = hp_drivers;
    result.count = VTSS_ARRSZ(hp_drivers);

    return result;
}

meba_sfp_drivers_t meba_oem_driver_init() {
    static meba_sfp_driver_t oem_drivers[] = {{
        .product_name = "SFP-T",
        .meba_sfp_driver_delete = dev_delete,
        .meba_sfp_driver_reset = dev_reset,
        .meba_sfp_driver_poll = dev_poll,
        .meba_sfp_driver_conf_set = cisco_sgmii_conf_set,
        .meba_sfp_driver_if_get = cisco_sgmii_if_get,
        .meba_sfp_driver_mt_get = NULL,
        .meba_sfp_driver_tr_get = tr_1000_t_get,
        .meba_sfp_driver_probe = dev_probe,
    }};

    meba_sfp_drivers_t result;
    result.sfp_drv = oem_drivers;
    result.count = VTSS_ARRSZ(oem_drivers);

    return result;
}

meba_sfp_drivers_t meba_wavesplitter_driver_init() {
    static meba_sfp_driver_t wavesplitter_drivers[] = {{
        .product_name = "WST-S3CCIM-401H",
        .meba_sfp_driver_delete = dev_delete,
        .meba_sfp_driver_reset = dev_reset,
        .meba_sfp_driver_poll = dev_poll,
        .meba_sfp_driver_conf_set = serdes_conf_set,
        .meba_sfp_driver_if_get = serdes_if_get,
        .meba_sfp_driver_mt_get = NULL,
        .meba_sfp_driver_tr_get = tr_1000_lx_get,
        .meba_sfp_driver_probe = dev_probe,
    }};

    meba_sfp_drivers_t result;
    result.sfp_drv = wavesplitter_drivers;
    result.count = VTSS_ARRSZ(wavesplitter_drivers);

    return result;
}

meba_sfp_drivers_t meba_d_link_driver_init() {
    static meba_sfp_driver_t d_link_drivers[] = {{
        .product_name = "DEM-311GT",
        .meba_sfp_driver_delete = dev_delete,
        .meba_sfp_driver_reset = dev_reset,
        .meba_sfp_driver_poll = dev_poll,
        .meba_sfp_driver_conf_set = serdes_conf_set,
        .meba_sfp_driver_if_get = serdes_if_get,
        .meba_sfp_driver_mt_get = NULL,
        .meba_sfp_driver_tr_get = tr_1000_sx_get,
        .meba_sfp_driver_probe = dev_probe,
    }};

    meba_sfp_drivers_t result;
    result.sfp_drv = d_link_drivers;
    result.count = VTSS_ARRSZ(d_link_drivers);

    return result;
}

meba_sfp_drivers_t meba_avago_driver_init() {
    static meba_sfp_driver_t avago_drivers[] = {{
        .product_name = "AFBR-5710LZ",
        .meba_sfp_driver_delete = dev_delete,
        .meba_sfp_driver_reset = dev_reset,
        .meba_sfp_driver_poll = dev_poll,
        .meba_sfp_driver_conf_set = serdes_conf_set,
        .meba_sfp_driver_if_get = serdes_if_get,
        .meba_sfp_driver_mt_get = NULL,
        .meba_sfp_driver_tr_get = tr_1000_sx_get,
        .meba_sfp_driver_probe = dev_probe,
    }};

    meba_sfp_drivers_t result;
    result.sfp_drv = avago_drivers;
    result.count = VTSS_ARRSZ(avago_drivers);

    return result;
}

meba_sfp_drivers_t meba_excom_driver_init() {
    static meba_sfp_driver_t excom_drivers[] = {
        {
            .product_name = "SFP-SX-M1002",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = fx_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_100_sx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "SFP-LH-S1010",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = fx_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_100_lx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "SFP+10G-LR10",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = sfi_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_10g_lr_get,
            .meba_sfp_driver_probe = dev_probe,
        }};

    meba_sfp_drivers_t result;
    result.sfp_drv = excom_drivers;
    result.count = VTSS_ARRSZ(excom_drivers);

    return result;
}

meba_sfp_drivers_t meba_mac_to_mac_driver_init() {
    static meba_sfp_driver_t mac_to_mac_drivers[] = {
        {
            .product_name = "MAC-to-MAC-1G",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = serdes_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_1000_sx_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "MAC-to-MAC-2.5G",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = sfi_if_get,
            .meba_sfp_driver_mt_get = NULL,
            .meba_sfp_driver_tr_get = tr_2g5_get,
            .meba_sfp_driver_probe = dev_probe,
        },
        {
            .product_name = "MAC-to-MAC-10G",
            .meba_sfp_driver_delete = dev_delete,
            .meba_sfp_driver_reset = dev_reset,
            .meba_sfp_driver_poll = dev_poll,
            .meba_sfp_driver_conf_set = serdes_conf_set,
            .meba_sfp_driver_if_get = sfi_if_get,
            .meba_sfp_driver_mt_get = sfi_mt_get,
            .meba_sfp_driver_tr_get = tr_10g_sr_get,
            .meba_sfp_driver_probe = dev_probe,
        }};

    meba_sfp_drivers_t result;
    result.sfp_drv = mac_to_mac_drivers;
    result.count = VTSS_ARRSZ(mac_to_mac_drivers);

    return result;
}

typedef mesa_rc (*tr_func_t)(meba_sfp_device_t *dev,
                             meba_sfp_transreceiver_t *tr);
typedef mesa_rc (*if_func_t)(meba_sfp_device_t *dev, mesa_port_speed_t speed,
                             mesa_port_interface_t *mac_if);
typedef mesa_rc (*mt_func_t)(meba_sfp_device_t *dev,
                             mesa_sd10g_media_type_t *mt);
typedef mesa_rc (*conf_func_t)(meba_sfp_device_t *dev,
                               const meba_sfp_driver_conf_t *conf);

#define SFP_MSA_BASE_PX 0x80
#define SFP_MSA_BASE_BX10 0x40
#define SFP_MSA_100BASE_FX 0x20
#define SFP_MSA_100BASE_LX 0x10
#define SFP_MSA_1000BASE_T 0x08
#define SFP_MSA_1000BASE_CX 0x04
#define SFP_MSA_1000BASE_LX 0x02
#define SFP_MSA_1000BASE_SX 0x01
#define SFP_MSA_10GBASE_ER 0x80
#define SFP_MSA_10GBASE_LRM 0x40
#define SFP_MSA_10GBASE_LR 0x20
#define SFP_MSA_10GBASE_SR 0x10
#define SFP_MSA_SFP_PLUS_PASSIVE 0x04
#define SFP_MSA_SFP_PLUS_ACTIVE 0x08

static tr_func_t get_tr(uint8_t *rom, uint32_t rom_size) {
    // Values are are based on SFF-8472 - Table 5-3.
    uint8_t eth_10g = rom[3];  // SFP+/SFP28 Ethernet Compliance Codes
    uint8_t eth = rom[6];      // Ethernet Compiance Codes
    uint8_t speed = rom[12];   // Nominal speed[100Md]
    uint8_t tech = rom[8];     // SFP+ Cable Technology

    if ((tech & SFP_MSA_SFP_PLUS_PASSIVE) && (speed >= 100 && speed < 250))
        return tr_10g_dac_get;
    if ((tech & SFP_MSA_SFP_PLUS_PASSIVE) && (speed >= 250))
        return tr_25g_dac_get;
    if ((speed >= 100 && speed < 250) && ((eth_10g & 0xf0) > 0)) {
        if (eth_10g & SFP_MSA_10GBASE_ER) return tr_10g_er_get;
        if (eth_10g & SFP_MSA_10GBASE_LRM) return tr_10g_lrm_get;
        if (eth_10g & SFP_MSA_10GBASE_LR) return tr_10g_lr_get;
        return tr_10g_sr_get;
    }
    if (speed >= 250 && ((eth_10g & 0xf0) > 0)) {
        if (eth_10g & SFP_MSA_10GBASE_ER) return tr_25g_er_get;
        if (eth_10g & SFP_MSA_10GBASE_LRM) return tr_25g_lrm_get;
        if (eth_10g & SFP_MSA_10GBASE_LR) return tr_25g_lr_get;
        return tr_25g_sr_get;
    }
    if (eth & SFP_MSA_1000BASE_SX) return tr_1000_sx_get;
    if (eth & SFP_MSA_1000BASE_CX) return tr_1000_cx_get;
    if (eth & SFP_MSA_1000BASE_T) return tr_1000_t_get;
    if (eth & SFP_MSA_1000BASE_LX) {
        if ((speed == 0xd && rom[14] == 0x50 && rom[15] == 0xFF) || 
            (speed == 0xc && rom[14] == 0x58 && rom[15] == 0xFF)) {
            return tr_1000_zx_get;
        } else {
            return tr_1000_lx_get;
        }
    }
    if (eth & SFP_MSA_100BASE_FX) return tr_100_fx_get;
    if (eth == 0 || (eth & (SFP_MSA_BASE_BX10 | SFP_MSA_BASE_PX))) {
        if (speed == 1 && rom[14] == 0x50 && rom[15] == 0xFF) {
            // This is a special SFP which is not defined in SFF-8472, but is
            // requested by a customer. See bugzilla#E2020
            return tr_100_zx_get;
        } else if (rom[14] == 0x0 && rom[15] == 0x0 &&
                   rom[16] == 0xC8 && rom[17] == 0xC8 && rom[18] == 0x0) {
            // This is a special SFP which is not defined in SFF-8472, but is
            // requested by a customer. See bugzilla#E2146
            if(speed == 0x1) {
                    return tr_100_sx_get;
            } else if(speed == 0x2) {
                    return tr_100_fx_get;
            } else {
                    return tr_100_lx_get;
            }
        } else if (speed < 10) {
            return tr_100_lx_get;
        } else if (speed < 25) {
            return tr_1000_x_get;
        } else if (speed < 50) {
            return tr_2g5_get;
        } else if (speed < 100) {
            return tr_5g_get;
        } else if (speed < 250) {
            return tr_10g_get;
        } else {
            return tr_25g_get;
        }
    }

    return tr_1000_sx_get;
}

static if_func_t get_if(uint8_t *rom, uint32_t rom_size) {
    meba_sfp_transreceiver_t tr;
    tr_func_t tr_func = get_tr(rom, rom_size);
    tr_func(NULL, &tr);
    switch (tr) {
        case MEBA_SFP_TRANSRECEIVER_100FX:
        case MEBA_SFP_TRANSRECEIVER_100BASE_LX:
        case MEBA_SFP_TRANSRECEIVER_100BASE_ZX:
        case MEBA_SFP_TRANSRECEIVER_100BASE_SX:
            return fx_if_get;
        case MEBA_SFP_TRANSRECEIVER_1000BASE_T:
            return cisco_sgmii_if_get;
        case MEBA_SFP_TRANSRECEIVER_1000BASE_BX10:
        case MEBA_SFP_TRANSRECEIVER_1000BASE_CX:
        case MEBA_SFP_TRANSRECEIVER_1000BASE_SX:
        case MEBA_SFP_TRANSRECEIVER_1000BASE_LX:
        case MEBA_SFP_TRANSRECEIVER_1000BASE_ZX:
        case MEBA_SFP_TRANSRECEIVER_1000BASE_LR:
        case MEBA_SFP_TRANSRECEIVER_1000BASE_X:
            return serdes_if_get;
        case MEBA_SFP_TRANSRECEIVER_2G5:
        case MEBA_SFP_TRANSRECEIVER_5G:
        case MEBA_SFP_TRANSRECEIVER_10G:
        case MEBA_SFP_TRANSRECEIVER_10G_SR:
        case MEBA_SFP_TRANSRECEIVER_10G_LR:
        case MEBA_SFP_TRANSRECEIVER_10G_LRM:
        case MEBA_SFP_TRANSRECEIVER_10G_ER:
        case MEBA_SFP_TRANSRECEIVER_10G_DAC:
        case MEBA_SFP_TRANSRECEIVER_25G:
        case MEBA_SFP_TRANSRECEIVER_25G_SR:
        case MEBA_SFP_TRANSRECEIVER_25G_LR:
        case MEBA_SFP_TRANSRECEIVER_25G_LRM:
        case MEBA_SFP_TRANSRECEIVER_25G_ER:
        case MEBA_SFP_TRANSRECEIVER_25G_DAC:
            return sfi_if_get;
        default:
            break;
    }
    return serdes_if_get;
}

static mt_func_t get_mt(uint8_t *rom, uint32_t rom_size) {
    meba_sfp_transreceiver_t tr;
    tr_func_t tr_func = get_tr(rom, rom_size);
    tr_func(NULL, &tr);
    switch (tr) {
        case MEBA_SFP_TRANSRECEIVER_10G:
        case MEBA_SFP_TRANSRECEIVER_25G: return sfi_mt_none_get;
        case MEBA_SFP_TRANSRECEIVER_10G_SR:
        case MEBA_SFP_TRANSRECEIVER_25G_SR:
        case MEBA_SFP_TRANSRECEIVER_10G_LRM:
        case MEBA_SFP_TRANSRECEIVER_25G_LRM: return sfi_mt_get;
        case MEBA_SFP_TRANSRECEIVER_10G_ER:
        case MEBA_SFP_TRANSRECEIVER_25G_ER:
        case MEBA_SFP_TRANSRECEIVER_10G_LR:
        case MEBA_SFP_TRANSRECEIVER_25G_LR: return sfi_mt_zr_get;
        case MEBA_SFP_TRANSRECEIVER_10G_DAC:
        case MEBA_SFP_TRANSRECEIVER_25G_DAC: return sfi_mt_dac_get;
     default:
         return sfi_mt_get;
    }
    return NULL;
}

static conf_func_t get_conf(uint8_t *rom, uint32_t rom_size) {
    meba_sfp_transreceiver_t tr;
    tr_func_t tr_func = get_tr(rom, rom_size);
    tr_func(NULL, &tr);
    if (tr == MEBA_SFP_TRANSRECEIVER_1000BASE_T) return cisco_sgmii_conf_set;
    return serdes_conf_set;
}

/* The size of destination array argument should be atleast (len + 1) */
static void sfp_strncpy(char *dest, uint8_t *rom, uint32_t len) {
    int i, c, replace = '\0';

    for (i = len - 1; i >= 0; i--) {
        c = rom[i];

        if (isprint(c) && (c != ' ')) {
            replace = ' ';
            dest[i] = c;
        } else {
            dest[i] = replace;
        }
    }
    dest[len] = '\0';
}

static mesa_bool_t get_sfp_rom(meba_inst_t meba_inst, uint8_t *buf, mesa_port_no_t port_no) {
    for (int i = 0; i < 10; ++i)
        if ((meba_inst->api.meba_sfp_i2c_xfer(meba_inst, port_no, false, 0x50, 0, buf, 88, false) == MESA_RC_OK))
            if (buf[0] == 0x03)
                return true;
    return false;
}

mesa_bool_t meba_fill_driver(meba_inst_t meba_inst, mesa_port_no_t port_no,
                             meba_sfp_driver_t *driver, meba_sfp_device_info_t *info) {

    static uint32_t rom_size = 88;
    uint8_t rom[rom_size];

    if (!get_sfp_rom(meba_inst, rom, port_no))
        return false;

    driver->product_name = (char *)calloc(17, sizeof(char));
    sfp_strncpy(driver->product_name, &rom[40], 16);

    // set function that will be for any driver
    driver->meba_sfp_driver_probe = dev_probe;
    driver->meba_sfp_driver_delete = dev_delete;
    driver->meba_sfp_driver_reset = dev_reset;
    driver->meba_sfp_driver_poll = dev_poll;

    // set function based on data from rom
    driver->meba_sfp_driver_if_get = get_if(rom, rom_size);    // SFP type -> API interface type
    driver->meba_sfp_driver_mt_get = get_mt(rom, rom_size);    // SFP type -> 10G/25G media type
    driver->meba_sfp_driver_tr_get = get_tr(rom, rom_size);    // SFP Rom  -> SFP tranceiver type
    driver->meba_sfp_driver_conf_set = get_conf(rom, rom_size);// SFP type -> Serdes/Cisco-SGMII

    // fill out vendor details
    sfp_strncpy(info->vendor_name, &rom[20], 16);
    sfp_strncpy(info->vendor_pn,   &rom[40], 16);
    sfp_strncpy(info->vendor_rev,  &rom[56],  4);
    sfp_strncpy(info->vendor_sn,   &rom[68], 16);
    return true;
}
