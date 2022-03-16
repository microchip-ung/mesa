/*
 Copyright (c) 2004-2022 Microsemi Corporation "Microsemi".

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

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>

#include "AQ_API.h"
#include "AQ_PhyInterface.h"
#include "AQ_Firmware.h"
#include "AQ_User.h"

#define T_D(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);

#define TRUE 1
#define FALSE 0

#define VTSS_FREE(_p_)                          free(_p_)
#define MSLEEP(sec)                             usleep(sec*1000)

#define AQR_2_MESA_RC(aq_rc)                    ((aq_rc == AQ_RET_OK) ? MESA_RC_OK : MESA_RC_ERROR)
#define AQR_TEST_RC(func)                       if ((aq_rc = func) != AQ_RET_OK) { \
                                                    T_I("Operation failed, aq_rc: %u", aq_rc);\
                                                    return AQR_2_MESA_RC(aq_rc); \
                                                }

#define AQ_PORT(dev) (&(((AQR_priv_data_t *)dev->data)->aq_port))

typedef struct {
    AQ_Port          aq_port;
    int              phy_diag_done;
    int              phy_shutdown;
} AQR_priv_data_t;

static mesa_rc aqr_delete(mepa_device_t *dev)
{
    AQR_priv_data_t *data = (AQR_priv_data_t *)dev->data;
    VTSS_FREE(data);
    VTSS_FREE(dev);
    return MESA_RC_OK;
}

static void aqr_port_id_init(AQ_Port              *data,
                             AQ_API_Port          *aq_port)
{
    if (aq_port != NULL) {
        aq_port->device = AQ_DEVICE_EUR;
        aq_port->PHY_ID = *data;
    } else {
        T_E("null aqr port, port_no: %u", data->dev->numeric_handle);
    }
}

static AQ_Retcode aqr_phy_conf_get(AQ_Port *data,
                                   AQ_API_StaticConfiguration *aq_conf)
{
    AQ_API_Port                aq_port;
    AQ_Retcode                 aq_rc = AQ_RET_OK;

    T_D("Enter, port_no: %u", data->dev->numeric_handle);

    aqr_port_id_init(data, &aq_port);

    memset(aq_conf, 0, sizeof(AQ_API_StaticConfiguration));

    AQR_TEST_RC(AQ_API_GetStaticConfiguration(&aq_port, aq_conf));

    T_D("port_no: %u, OUI: %u, IEEE_ModelNumber: %u, IEEE_RevisionNumber: %u, aq_rc: %d", data->dev->numeric_handle,
        aq_conf->OUI, aq_conf->IEEE_ModelNumber,
        aq_conf->IEEE_RevisionNumber, aq_rc);

    return aq_rc;
}

static mesa_rc aqr_conf_set_private(mepa_device_t *dev,
                                    const mepa_conf_t *config,
                                    mesa_bool_t is_409)
{
    AQR_priv_data_t *priv = (AQR_priv_data_t *)dev->data;
    AQ_Port *data = AQ_PORT(dev);

    AQ_Retcode                          aq_rc = AQ_RET_OK;
    AQ_API_Port                         aq_port;
    AQ_API_AutonegotiationControl       aq_autoneg_config;
    AQ_API_Configuration                aq_config;

    T_D("aqr_conf_set_private Enter, port_no: %u", data->dev->numeric_handle);

    memset(&aq_port, 0, sizeof(AQ_API_Port));
    memset(&aq_autoneg_config, 0, sizeof(AQ_API_AutonegotiationControl));
    memset(&aq_config, 0, sizeof(AQ_API_Configuration));

    aqr_port_id_init(data, &aq_port);

    if (config->admin.enable && (!is_409 || priv->phy_shutdown)) {
        priv->phy_shutdown = FALSE;
        AQR_TEST_RC(AQ_API_SetActive(&aq_port));
        uint8_t retry_cnt = 0;
        while (retry_cnt < 5) {
            MSLEEP(50);
            T_D("aqr_conf_set_private mmd_read");
            uint16_t reg_value;
            data->dev->callout->mmd_read(dev->callout_ctx, 0x1e, 0xc831, &reg_value);
            if (!(reg_value & 0x8000)) {
                break; //1E.C831 Processor-intensive MDIO operation completed 0x0000: p584
            }
            retry_cnt++;
        }
    } else if (!config->admin.enable) {
        AQR_TEST_RC(AQ_API_SetLowPower(&aq_port));
        priv->phy_shutdown = TRUE;
        return AQR_2_MESA_RC(aq_rc);
    }

    if ((aq_rc = AQ_API_GetAutonegotiationControl(&aq_port, &aq_autoneg_config)) != AQ_RET_OK) {
        T_E("failed to get AQR PHY autoneg conf, portno:%d, rc:%d\n", data->dev->numeric_handle, aq_rc);
    }

    if ((aq_rc = AQ_API_GetConfiguration(&aq_port, &aq_config)) != AQ_RET_OK) {
        T_E("failed to get AQR PHY conf, portno:%d, rc:%d\n", data->dev->numeric_handle, aq_rc);
    }

    T_D("set config");
    aq_config.LED_Control[0].LED_On_When5G_LinkEstablished       = (AQ_boolean) TRUE;
    aq_config.LED_Control[0].LED_On_When2_5G_LinkEstablished     = (AQ_boolean) TRUE;
    aq_config.LED_Control[1].LED_On_When1G_LinkEstablished       = (AQ_boolean) TRUE;
    aq_config.LED_Control[1].LED_On_When100M_LinkEstablished     = (AQ_boolean) TRUE;

    aq_autoneg_config.enableAutomaticDownshift          = (AQ_boolean) TRUE;
    aq_autoneg_config.automaticDownshiftRetryAttempts   = 3;
    aq_autoneg_config.portType                          = AQ_API_AN_MultiPort;

    aq_autoneg_config.advertiseSymmetricPAUSE           = (AQ_boolean) config->flow_control;
    aq_autoneg_config.advertiseAsymmetricPAUSE          = (AQ_boolean) config->flow_control;

    aq_autoneg_config.MDI_MDI_X_Control                 = AQ_API_MDC_Automatic;

    if (config->speed == MESA_SPEED_AUTO) {
        aq_autoneg_config.advertise2_5G = (AQ_boolean) config->aneg.speed_2g5_fdx;
        aq_autoneg_config.advertise5G = (AQ_boolean) config->aneg.speed_5g_fdx;
        aq_autoneg_config.advertise10GBASE_T = (AQ_boolean) config->aneg.speed_10g_fdx;
        aq_autoneg_config.advertise10BASE_T_HalfDuplex = (AQ_boolean) config->aneg.speed_10m_hdx;
        aq_autoneg_config.advertise10BASE_T_FullDuplex = (AQ_boolean) config->aneg.speed_10m_fdx;
        aq_autoneg_config.advertise100BASE_TX_HalfDuplex = (AQ_boolean) config->aneg.speed_100m_hdx;
        aq_autoneg_config.advertise100BASE_TX_FullDuplex = (AQ_boolean) config->aneg.speed_100m_fdx;
        aq_autoneg_config.advertise1000BASE_T_FullDuplex = (AQ_boolean) config->aneg.speed_1g_fdx;
        aq_autoneg_config.advertise1000BASE_T_HalfDuplex = (AQ_boolean) FALSE;

        T_I("port_no: %u, 10g_fdx:%d, 5g_fdx:%d, 2g5_fdx:%d, 10m_hdx:%d, \n\t10m_fdx:%d, 100m_hdx:%d, 100m_fdx:%d, 1g_fdx:%d, 1g_hdx:%d", data->dev->numeric_handle,
            aq_autoneg_config.advertise10GBASE_T, aq_autoneg_config.advertise5G, aq_autoneg_config.advertise2_5G, aq_autoneg_config.advertise10BASE_T_HalfDuplex,
            aq_autoneg_config.advertise10BASE_T_FullDuplex, aq_autoneg_config.advertise100BASE_TX_HalfDuplex, aq_autoneg_config.advertise100BASE_TX_FullDuplex, aq_autoneg_config.advertise1000BASE_T_FullDuplex, aq_autoneg_config.advertise1000BASE_T_HalfDuplex);
    } else {
        aq_autoneg_config.advertise2_5G                     = (AQ_boolean) ((config->speed == MESA_SPEED_2500M) ? TRUE : FALSE);
        aq_autoneg_config.advertise10BASE_T_HalfDuplex      = (AQ_boolean) ((!config->fdx && (config->speed == MESA_SPEED_10M)) ? TRUE : FALSE);
        aq_autoneg_config.advertise10BASE_T_FullDuplex      = (AQ_boolean) ((config->fdx && (config->speed == MESA_SPEED_10M)) ? TRUE : FALSE);
        aq_autoneg_config.advertise100BASE_TX_HalfDuplex    = (AQ_boolean) ((!config->fdx && (config->speed == MESA_SPEED_100M)) ? TRUE : FALSE);
        aq_autoneg_config.advertise100BASE_TX_FullDuplex    = (AQ_boolean) ((config->fdx && (config->speed == MESA_SPEED_100M)) ? TRUE : FALSE);
        aq_autoneg_config.advertise1000BASE_T_HalfDuplex    = (AQ_boolean) ((!config->fdx && (config->speed == MESA_SPEED_1G)) ? TRUE : FALSE);
        aq_autoneg_config.advertise1000BASE_T_FullDuplex    = (AQ_boolean) ((config->fdx && (config->speed == MESA_SPEED_1G)) ? TRUE : FALSE);
    }

    if ((aq_rc = AQ_API_SetAutonegotiationControl(&aq_port, &aq_autoneg_config)) != AQ_RET_OK) {
        T_E("Failed to set AQ Autonegotiation information, port_no: %u, rc: %d\n", data->dev->numeric_handle, aq_rc);
        return AQR_2_MESA_RC(aq_rc);
    }

    if ((aq_rc = AQ_API_RestartAutonegotiation(&aq_port)) != AQ_RET_OK) {
        T_E("Failed to restart autoneg, port_no:%d, rc:%d\n", data->dev->numeric_handle, aq_rc);
    }

    return AQR_2_MESA_RC(aq_rc);
}

static mesa_rc aqr_409_conf_set(mepa_device_t *dev,
                                const mepa_conf_t *config)
{
    return aqr_conf_set_private(dev, config, true);
}

static mesa_rc aqr_conf_set(mepa_device_t *dev,
                            const mepa_conf_t *config)
{
    return aqr_conf_set_private(dev, config, false);
}

static mesa_rc aqr_poll(mepa_device_t *dev, mepa_status_t *status)
{
    AQ_Port *data = AQ_PORT(dev);

    AQ_Retcode                           aq_rc = AQ_RET_OK;
    AQ_API_Port                          aq_port;
    AQ_API_ConnectionStatus              connectionStatus;
    AQ_API_AlarmStatus                   alarmStatus;
    AQ_API_LinkPartnerStatus             linkPartnerStatus;
    AQ_API_AutonegotiationControl        aq_autoneg_config;

    T_D("aqr_poll Enter, port_no: %u", data->dev->numeric_handle);

    memset(&connectionStatus, 0, sizeof(AQ_API_ConnectionStatus));
    memset(&linkPartnerStatus, 0, sizeof(AQ_API_LinkPartnerStatus));
    memset(&aq_autoneg_config, 0, sizeof(AQ_API_AutonegotiationControl));

    aqr_port_id_init(data, &aq_port);

    AQR_TEST_RC(AQ_API_GetConnectionStatus(&aq_port, &connectionStatus));
    AQR_TEST_RC(AQ_API_GetAlarmStatus(&aq_port, &alarmStatus));
    AQR_TEST_RC(AQ_API_GetLinkPartnerStatus(&aq_port, &linkPartnerStatus));
    AQR_TEST_RC(AQ_API_GetAutonegotiationControl(&aq_port, &aq_autoneg_config));

    status->fdx = connectionStatus.duplex;

    switch (connectionStatus.sysIntfCurrentRate) {
    case AQ_API_SIR_100M:
        status->link = (connectionStatus.state == AQ_API_ConnS_100M_Connected) ? TRUE : FALSE;
        status->speed = MESA_SPEED_100M;
        break;
    case AQ_API_SIR_1G:
        status->link = (connectionStatus.state == AQ_API_ConnS_1G_Connected) ? TRUE : FALSE;
        status->speed = MESA_SPEED_1G;
        break;
    case AQ_API_SIR_2_5G:
        status->link = (connectionStatus.state == AQ_API_ConnS_2_5G_Connected) ? TRUE : FALSE;
        status->speed = MESA_SPEED_2500M;
        break;
    case AQ_API_SIR_5G:
        status->link = (connectionStatus.state == AQ_API_ConnS_5G_Connected) ? TRUE : FALSE;
        status->speed = MESA_SPEED_5G;
        break;
    case AQ_API_SIR_10G:
        status->link = (connectionStatus.state == AQ_API_ConnS_10G_Connected) ? TRUE : FALSE;
        status->speed = MESA_SPEED_10G;
        break;
    case AQ_API_SIR_Other:
    default:
        status->link = FALSE;
        status->speed = MESA_SPEED_UNDEFINED;
    }

    status->link = ((status->link || (connectionStatus.state == AQ_API_ConnS_LoopbackMode)) && connectionStatus.farEndDeviceExists);

    bool sym_pause = aq_autoneg_config.advertiseSymmetricPAUSE;
    bool asym_pause = aq_autoneg_config.advertiseAsymmetricPAUSE;

    bool lp_sym_pause = linkPartnerStatus.symmetricPAUSE;
    bool lp_asym_pause = linkPartnerStatus.asymmetricPAUSE;

    if (status->speed != MESA_SPEED_10G) {
        status->aneg.obey_pause = 1;
        status->aneg.generate_pause =
            (lp_sym_pause && (sym_pause || (asym_pause && lp_asym_pause)) ? 1 : 0);
    } else {
        status->aneg.obey_pause =
            (sym_pause && (lp_sym_pause || (asym_pause && lp_asym_pause)) ? 1 : 0);
        status->aneg.generate_pause =
            (lp_sym_pause && (sym_pause || (asym_pause && lp_asym_pause)) ? 1 : 0);
    }

    return AQR_2_MESA_RC(aq_rc);
}

static mesa_rc aqr_if_get(mepa_device_t *dev, mesa_port_speed_t speed,
                          mesa_port_interface_t *mac_if)
{
    AQ_Port *data = AQ_PORT(dev);
    *mac_if = data->mac_if;
    return MESA_RC_OK;
}

static mesa_rc aqr_409_if_get(mepa_device_t *dev, mesa_port_speed_t speed,
                              mesa_port_interface_t *mac_if)
{
    switch (speed) {
    case MESA_SPEED_100M:
        *mac_if = MESA_PORT_INTERFACE_SGMII_CISCO;
        break;
    default:
        *mac_if = MESA_PORT_INTERFACE_SGMII;
        break;
    }
    return MESA_RC_OK;
}

static mesa_rc aqr_veriphy_start(mepa_device_t *dev, int mode)
{
    AQR_priv_data_t *priv = (AQR_priv_data_t *)dev->data;
    AQ_Port *data = AQ_PORT(dev);

    AQ_Retcode                          aq_rc = AQ_RET_OK;
    AQ_API_Port                         aq_port;

    T_D("Enter, aqr_veriphy_start, port_no: %u", data->dev->numeric_handle);

    aqr_port_id_init(data, &aq_port);
    if (!priv->phy_diag_done) {
        aq_rc = AQ_API_RunBasicCableDiags(&aq_port);
        if (aq_rc == AQ_RET_OK) {
            T_I("Successfully started cable diagonistic, port_no:%d\n", data->dev->numeric_handle);
            priv->phy_diag_done = TRUE;
            MSLEEP(10);
        } else {
            T_E("Run veriphy failed: %d", aq_rc);
        }
    }
    return AQR_2_MESA_RC(aq_rc);
}

static void aqr_fill_status(mepa_cable_diag_result_t  *res,
                            uint32_t                  index,
                            AQ_API_BasicPairStatus    status,
                            AQ_Port                   *data)
{
    switch (status) {
    case AQ_API_BasicPairStatus_OK:
        res->status[index] = MESA_VERIPHY_STATUS_OK;
        break;
    case AQ_API_BasicPairStatus_Short:
        res->status[index] = MESA_VERIPHY_STATUS_SHORT;
        break;
    case AQ_API_BasicPairStatus_LowMismatch:
    case AQ_API_BasicPairStatus_HighMismatch:
        res->status[index] = MESA_VERIPHY_STATUS_UNKNOWN;
        break;
    case AQ_API_BasicPairStatus_Open:
        res->status[index] = MESA_VERIPHY_STATUS_OPEN;
        break;
    case AQ_API_BasicPairStatus_CrossoverA:
        res->status[index] = MESA_VERIPHY_STATUS_SHORT_A;
        break;
    case AQ_API_BasicPairStatus_CrossoverB:
        res->status[index] = MESA_VERIPHY_STATUS_SHORT_B;
        break;
    case AQ_API_BasicPairStatus_CrossoverC:
        res->status[index] = MESA_VERIPHY_STATUS_SHORT_C;
        break;
    case AQ_API_BasicPairStatus_CrossoverD:
        res->status[index] = MESA_VERIPHY_STATUS_SHORT_D;
        break;
    default:
        T_E("Unknown status");
    }
}

static mesa_rc aqr_veriphy_get(mepa_device_t         *dev,
                               mepa_cable_diag_result_t *res)
{
    AQR_priv_data_t *priv = (AQR_priv_data_t *)dev->data;
    AQ_Port *data = AQ_PORT(dev);

    AQ_Retcode                      aq_rc = AQ_RET_OK;
    AQ_API_Port                     aq_port;
    AQ_API_BasicCableDiagResults    result;

    T_D("Enter, aqr_veriphy_get, port_no: %u", data->dev->numeric_handle);

    aqr_port_id_init(data, &aq_port);
    if (priv->phy_diag_done) {
        memset(&result, 0, sizeof(AQ_API_BasicCableDiagResults));

        while ((aq_rc = AQ_API_GetBasicCableDiagsResults(&aq_port, &result)) == AQ_RET_CABLEDIAG_STILL_RUNNING) {
            MSLEEP(10);
            continue;
        }
        AQR_TEST_RC(aq_rc);

        aqr_fill_status(res, 0, result.pairAResult.status, data);
        aqr_fill_status(res, 1, result.pairBResult.status, data);
        aqr_fill_status(res, 2, result.pairCResult.status, data);
        aqr_fill_status(res, 3, result.pairDResult.status, data);

        res->length[0]  = result.pairAResult.reflection_1_Distance;
        T_D("A: dis_1to2: %d", result.pairAResult.reflection_1_Distance);

        res->length[1]  = result.pairBResult.reflection_1_Distance;
        T_D("B: dis_1to2: %d", result.pairBResult.reflection_1_Distance);


        res->length[2]  = result.pairCResult.reflection_1_Distance;
        T_D("C: dis_1to2: %d", result.pairCResult.reflection_1_Distance);


        res->length[3]  = result.pairDResult.reflection_1_Distance;
        T_D("D: dis_1to2: %d", result.pairDResult.reflection_1_Distance);

        priv->phy_diag_done = FALSE;

        T_I("Got result(rc:%d). port_no:%d, L0:%d, L1:%d, L2:%d, L3:%d\n", aq_rc, data->dev->numeric_handle, res->length[0], res->length[1], res->length[2], res->length[3]);
    }

    T_I("Leaving> port_no:%d, ready:%d, rc:%d", data->dev->numeric_handle, priv->phy_diag_done, aq_rc);

    return AQR_2_MESA_RC(aq_rc);
}

static mesa_rc aqr_fw_check(AQ_Port  *data,
                            uint8_t  major_id,
                            uint8_t  minor_id,
                            uint8_t  build_id)
{
    AQ_API_StaticConfiguration aq_config;
    AQ_Retcode                 aq_ret;
    int rom;

    aq_ret = aqr_phy_conf_get(data, &aq_config);
    if (aq_ret) {
        T_E("aqr_fw_check/aqr_phy_conf_get failed. Port: %d, RC: %d", data->dev->numeric_handle, aq_ret);
        return MEPA_RC_ERROR;
    }

    // In earlier version of SW check was only performed if major number match
    if (aq_config.firmwareMajorRevisionNumber != major_id) {
        return MEPA_RC_OK;
    }

    rom = (aq_config.firmwareROM_ID_Number & 0xf0) >> 4;
    if (aq_config.firmwareMajorRevisionNumber != major_id &&
        (aq_config.firmwareMinorRevisionNumber != minor_id || rom != build_id)) {
        T_E("Unexpected firmware version. Port: %d, Major: %d/%d && (Minor %d/%d || ROM: %d/%d) (actual/expect)",
            data->dev->numeric_handle,
            aq_config.firmwareMajorRevisionNumber, major_id,
            aq_config.firmwareMinorRevisionNumber, minor_id,
            rom, build_id);
        return MEPA_RC_ERROR;
    }

    return MEPA_RC_OK;
}

static mesa_rc aqr_407_if_set(mepa_device_t *dev,
                              mesa_port_interface_t mac_if)
{
    AQ_Port *data = AQ_PORT(dev);
    // TODO, validate input!
    data->mac_if = mac_if;

    if (mac_if == MESA_PORT_INTERFACE_SGMII_2G5) {
        // Board JAGUAR2_AQR_REF
        return aqr_fw_check(data,
                            BUILT_IN_AQR_24_FW_MAJOR_REV_NUM,
                            BUILT_IN_AQR_24_FW_MINOR_REV_NUM,
                            BUILT_IN_AQR_24_FW_BUILD_ID_NUM);
    } else {
        // Board JAGUAR2_REF side board or other platform
        return aqr_fw_check(data,
                            BUILT_IN_AQR_4_FW_MAJOR_REV_NUM,
                            BUILT_IN_AQR_4_FW_MINOR_REV_NUM,
                            BUILT_IN_AQR_4_FW_BUILD_ID_NUM);
    }
}

static mesa_rc aqr_gen3a_if_set(mepa_device_t *dev,
                                mesa_port_interface_t mac_if)
{
    AQ_Port *data = AQ_PORT(dev);
    // TODO, validate input!
    data->mac_if = mac_if;

    // Board JAGUAR2_AQR_REF
    return aqr_fw_check(data,
                        BUILT_IN_AQR_4_G3A_FW_MAJOR_REV_NUM,
                        BUILT_IN_AQR_4_G3A_FW_MINOR_REV_NUM,
                        BUILT_IN_AQR_4_G3A_FW_BUILD_ID_NUM);
}

static mesa_rc aqr_gen3b_if_set(mepa_device_t *dev,
                                mesa_port_interface_t mac_if)
{
    AQ_Port *data = AQ_PORT(dev);
    // TODO, validate input!
    data->mac_if = mac_if;

    // Board JAGUAR2_AQR_REF
    return aqr_fw_check(data,
                        BUILT_IN_AQR_4_G3B_FW_MAJOR_REV_NUM,
                        BUILT_IN_AQR_4_G3B_FW_MINOR_REV_NUM,
                        BUILT_IN_AQR_4_G3B_FW_BUILD_ID_NUM);
}

#if 0
static void aqr_daisy_chain_reset(const mesa_inst_t     inst,
                                  const mesa_port_no_t  dc_master_port,
                                  const meba_inst_t     board_inst,
                                  AQ_Port               *data)
{
    mesa_port_map_t   port_map;
    mesa_port_no_t    dc_master_chip_port;
    mesa_port_no_t    port_no;
    mesa_port_no_t    port_start_no;
    mesa_port_no_t    port_end_no = 0;
    meba_port_entry_t entry;

    T_D("enter, aqr_daisy_chain_reset");

    board_inst->api.meba_port_entry_get(board_inst, dc_master_port, &entry);
    port_map = entry.map;
    dc_master_chip_port = port_map.chip_port;

    if (board_inst->props.board_type == VTSS_BOARD_JAGUAR2_REF) {
        port_start_no = 24;
        port_end_no = 28;
    } else if (board_inst->props.board_type == VTSS_BOARD_JAGUAR2_AQR_REF) {
        port_start_no = 0;
        port_end_no = 24;
    } else {
        T_E("board_type is wrong!");
        return;
    }

    for (port_no = port_start_no; port_no < port_end_no; port_no++) {
        board_inst->api.meba_port_entry_get(board_inst, port_no, &entry);
        port_map = entry.map;
        if (port_no == dc_master_port) {
            continue;
        }

        T_D("daisy chain reset port_no: %d", port_no);

        uint16_t reg_value;
        uint16_t hop_count;
        // Refer to AN-N2101_FirmwareOverview_v1.0.pdf, the daisy-chain reset must follwoing chip port order,
        // otherwise the firmware provisioning will be incorrect and make MDIO can't be accessed.
        // An alternative method to ensure correct provisioning is to override the hop-count value to specifc port.
        hop_count = port_map.chip_port - dc_master_chip_port;
        data->mmd_read(inst, port_no, 0x1e, 0xc471, &reg_value);
        // override the hop-count via writing 1E.C471.6:0
        reg_value |= (hop_count | 1 << 6);
        data->mmd_write(inst, port_no, 0x1e, 0xc471, reg_value);
        // Reset daisy chain via toggling 1E.C442.0
        data->mmd_read(inst, port_no, 0x1e, 0xc442, &reg_value);
        reg_value ^= 0x1;
        data->mmd_write(inst, port_no, 0x1e, 0xc442, reg_value);
    }
}
#endif

static mepa_device_t *aqr_probe(mepa_driver_t *drv,
                                const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                struct mepa_board_conf                  *board_conf)
{
    mepa_device_t   *dev;
    AQR_priv_data_t *priv;
    AQ_Port         *data;

    dev = mepa_create_int(drv, callout, callout_ctx, board_conf, sizeof(AQR_priv_data_t));
    if (!dev) {
        return 0;
    }

    priv = dev->data;
    data = &priv->aq_port;
    data->dev = dev;  // TODO, why?

    return dev;
}

static mesa_rc aqr_status_1g_get(mepa_device_t     *dev,
                                 mepa_aneg_status_t *status)
{
    AQ_Port *data = AQ_PORT(dev);

    AQ_Retcode                 aq_rc = AQ_RET_OK;
    AQ_API_Port                aq_port;
    AQ_API_ConnectionStatus    connectionStatus;
    AQ_API_AlarmStatus         alarmStatus;

    aqr_port_id_init(data, &aq_port);
    AQR_TEST_RC(AQ_API_GetAlarmStatus(&aq_port, &alarmStatus));
    AQR_TEST_RC(AQ_API_GetConnectionStatus(&aq_port, &connectionStatus));

    status->master_cfg_fault = alarmStatus.autonegotiationAlarms.masterSlaveConfigurationFault;
    switch (connectionStatus.masterSlaveStatus) {
    case AQ_API_MSS_Master:
        status->master = TRUE;
        break;
    case AQ_API_MSS_Slave:
        status->master = FALSE;
        break;
    }

    return AQR_2_MESA_RC(aq_rc);
}

static mepa_rc aqr_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy_info->cap = 0;
    phy_info->part_number = dev->drv->id;
    phy_info->revision = dev->drv->id & 0xF;
    phy_info->cap |= MEPA_CAP_SPEED_MASK_10G;
    phy_info->cap |= MEPA_CAP_SPEED_MASK_1G;
    return MEPA_RC_OK;
}

static mepa_rc aqr_mmd_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    AQ_Port *data = AQ_PORT(dev);
    uint16_t page_mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;

    return data->dev->callout->mmd_read(dev->callout_ctx, page_mmd, addr, value);
}

static mepa_rc aqr_mmd_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    AQ_Port *data = AQ_PORT(dev);
    uint16_t page_mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;

    return data->dev->callout->mmd_write(dev->callout_ctx, page_mmd, addr, value);
}

mepa_drivers_t mepa_aqr_driver_init()
{
#define NR_AQR_PHY 11
    mepa_drivers_t res;
    static mepa_driver_t aqr_drivers[NR_AQR_PHY] = {};

    // 407
    aqr_drivers[0].id = 0xB552;
    aqr_drivers[0].mask = 0x0000FFff;
    aqr_drivers[0].mepa_driver_delete = aqr_delete;
    aqr_drivers[0].mepa_driver_poll = aqr_poll;
    aqr_drivers[0].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[0].mepa_driver_if_set = aqr_407_if_set;
    aqr_drivers[0].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[0].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[0].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[0].mepa_driver_probe = aqr_probe;
    aqr_drivers[0].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[0].mepa_driver_phy_info_get = aqr_info_get;
    aqr_drivers[0].mepa_driver_clause45_read  = aqr_mmd_read;
    aqr_drivers[0].mepa_driver_clause45_write = aqr_mmd_write;

    aqr_drivers[1].id = 0xB582;
    aqr_drivers[1].mask = 0x0000FFff;
    aqr_drivers[1].mepa_driver_delete = aqr_delete;
    aqr_drivers[1].mepa_driver_poll = aqr_poll;
    aqr_drivers[1].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[1].mepa_driver_if_set = aqr_407_if_set;
    aqr_drivers[1].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[1].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[1].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[1].mepa_driver_probe = aqr_probe;
    aqr_drivers[1].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[1].mepa_driver_phy_info_get = aqr_info_get,

    aqr_drivers[2].id = 0xB581;
    aqr_drivers[2].mask = 0x00000FFff;
    aqr_drivers[2].mepa_driver_delete = aqr_delete;
    aqr_drivers[2].mepa_driver_poll = aqr_poll;
    aqr_drivers[2].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[2].mepa_driver_if_set = aqr_407_if_set;
    aqr_drivers[2].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[2].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[2].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[2].mepa_driver_probe = aqr_probe;
    aqr_drivers[2].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[2].mepa_driver_phy_info_get = aqr_info_get,

    // 409
    aqr_drivers[3].id = 0xB692;
    aqr_drivers[3].mask = 0x0000FFff;
    aqr_drivers[3].mepa_driver_delete = aqr_delete;
    aqr_drivers[3].mepa_driver_poll = aqr_poll;
    aqr_drivers[3].mepa_driver_conf_set = aqr_409_conf_set;
    aqr_drivers[3].mepa_driver_if_set = aqr_407_if_set;
    aqr_drivers[3].mepa_driver_if_get = aqr_409_if_get;
    aqr_drivers[3].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[3].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[3].mepa_driver_probe = aqr_probe;
    aqr_drivers[3].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[3].mepa_driver_phy_info_get = aqr_info_get,

    aqr_drivers[4].id = 0xB572;
    aqr_drivers[4].mask = 0x0000FFff;
    aqr_drivers[4].mepa_driver_delete = aqr_delete;
    aqr_drivers[4].mepa_driver_poll = aqr_poll;
    aqr_drivers[4].mepa_driver_conf_set = aqr_409_conf_set;
    aqr_drivers[4].mepa_driver_if_set = aqr_407_if_set;
    aqr_drivers[4].mepa_driver_if_get = aqr_409_if_get;
    aqr_drivers[4].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[4].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[4].mepa_driver_probe = aqr_probe;
    aqr_drivers[4].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[4].mepa_driver_phy_info_get = aqr_info_get,

    // 411
    aqr_drivers[5].id = 0xB6E0;
    aqr_drivers[5].mask = 0x0000FFff;
    aqr_drivers[5].mepa_driver_delete = aqr_delete;
    aqr_drivers[5].mepa_driver_poll = aqr_poll;
    aqr_drivers[5].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[5].mepa_driver_if_set = aqr_gen3a_if_set;
    aqr_drivers[5].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[5].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[5].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[5].mepa_driver_probe = aqr_probe;
    aqr_drivers[5].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[5].mepa_driver_phy_info_get = aqr_info_get,

    aqr_drivers[6].id = 0xB700;
    aqr_drivers[6].mask = 0x0000FFff;
    aqr_drivers[6].mepa_driver_delete = aqr_delete;
    aqr_drivers[6].mepa_driver_poll = aqr_poll;
    aqr_drivers[6].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[6].mepa_driver_if_set = aqr_gen3a_if_set;
    aqr_drivers[6].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[6].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[6].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[6].mepa_driver_probe = aqr_probe;
    aqr_drivers[6].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[6].mepa_driver_phy_info_get = aqr_info_get,

    aqr_drivers[7].id = 0xB6E2;
    aqr_drivers[7].mask = 0x0000FFff;
    aqr_drivers[7].mepa_driver_delete = aqr_delete;
    aqr_drivers[7].mepa_driver_poll = aqr_poll;
    aqr_drivers[7].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[7].mepa_driver_if_set = aqr_gen3b_if_set;
    aqr_drivers[7].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[7].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[7].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[7].mepa_driver_probe = aqr_probe;
    aqr_drivers[7].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[7].mepa_driver_phy_info_get = aqr_info_get,

    // 412
    aqr_drivers[8].id = 0xB6F0;
    aqr_drivers[8].mask = 0x0000FFff;
    aqr_drivers[8].mepa_driver_delete = aqr_delete;
    aqr_drivers[8].mepa_driver_poll = aqr_poll;
    aqr_drivers[8].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[8].mepa_driver_if_set = aqr_gen3a_if_set;
    aqr_drivers[8].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[8].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[8].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[8].mepa_driver_probe = aqr_probe;
    aqr_drivers[8].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[8].mepa_driver_phy_info_get = aqr_info_get,

    aqr_drivers[9].id = 0xB710;
    aqr_drivers[9].mask = 0x0000FFff;
    aqr_drivers[9].mepa_driver_delete = aqr_delete;
    aqr_drivers[9].mepa_driver_poll = aqr_poll;
    aqr_drivers[9].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[9].mepa_driver_if_set = aqr_gen3a_if_set;
    aqr_drivers[9].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[9].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[9].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[9].mepa_driver_probe = aqr_probe;
    aqr_drivers[9].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[9].mepa_driver_phy_info_get = aqr_info_get,

    aqr_drivers[10].id = 0xB6F2;
    aqr_drivers[10].mask = 0x0000FFff;
    aqr_drivers[10].mepa_driver_delete = aqr_delete;
    aqr_drivers[10].mepa_driver_poll = aqr_poll;
    aqr_drivers[10].mepa_driver_conf_set = aqr_conf_set;
    aqr_drivers[10].mepa_driver_if_set = aqr_gen3b_if_set;
    aqr_drivers[10].mepa_driver_if_get = aqr_if_get;
    aqr_drivers[10].mepa_driver_cable_diag_start = aqr_veriphy_start;
    aqr_drivers[10].mepa_driver_cable_diag_get = aqr_veriphy_get;
    aqr_drivers[10].mepa_driver_probe = aqr_probe;
    aqr_drivers[10].mepa_driver_aneg_status_get = aqr_status_1g_get;
    aqr_drivers[10].mepa_driver_phy_info_get = aqr_info_get,

    res.phy_drv = aqr_drivers;
    res.count = NR_AQR_PHY;

    return res;
#undef NR_AQR_PHY
}
