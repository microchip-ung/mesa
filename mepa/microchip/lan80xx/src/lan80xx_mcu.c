// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// This file declares the lan80xx MCU chip specic APIs and corresponding
// data structures


#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_private.h"
#include <lan80xx_mcu.h>

mepa_rc lan80xx_mcu_mailbox_init(const mepa_device_t *dev, u32 u32McuIntMask, u32 u32HostIntMask)
{
    mepa_rc rc = MEPA_RC_OK;

    MEPA_ENTER(dev);
    rc = lan80xx_mcu_mailbox_init_priv(dev, u32McuIntMask, u32HostIntMask);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_MB_INTR_register_callback(const mepa_device_t *dev, gpio_callback_t gpio_cb)
{
    mepa_rc rc = MEPA_RC_OK;

    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "Device not created!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    T_I(MEPA_TRACE_GRP_GEN, "%s\n", __FUNCTION__);
    base_data->ft_gpio_read = gpio_cb;
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_get_fw_info(const mepa_device_t *dev, DEVICE_INFO *psDevInfo)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_get_fw_info_priv(dev, psDevInfo);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_fw_update(mepa_device_t *dev)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_fw_update_priv(dev);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_mcu_reset(const mepa_device_t *dev)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_mcu_reset_priv(dev);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_memory_read(const mepa_device_t *dev, uint32_t u32Addres,
                            uint8_t *pu8Data, const uint16_t u16Len)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_memory_read_priv(dev, u32Addres, pu8Data, u16Len);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_memory_write(const mepa_device_t *dev, uint32_t u32Addres,
                             uint8_t *pu8Data, const u16 u16Len)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_memory_write_priv(dev, u32Addres, pu8Data, u16Len);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_otp_cfg_read(const mepa_device_t  *dev,
                             u8 u8RecIdx,
                             u8 *pu8Cfg,
                             u16 *pu16Len)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_otp_cfg_read_priv(dev, u8RecIdx, pu8Cfg, pu16Len);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_otp_read(const mepa_device_t  *dev,
                         u8 *pu8Data,
                         u16 u16Offset,
                         const u16 u16Len)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_otp_read_priv(dev, pu8Data, u16Offset, u16Len);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_otp_write(const mepa_device_t  *dev,
                          u8 *pu8Data,
                          u16 u16Offset,
                          const u16 u16Len,
                          u8 u8WriteMode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_otp_write_priv(dev, pu8Data, u16Offset, u16Len, u8WriteMode);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_otp_getKey_Status(const mepa_device_t  *dev,
                                  enOTP_ACTIVE_KEY *pKey)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_otp_getKey_Status_priv(dev, pKey);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_otp_revoke_AllKeys(const mepa_device_t  *dev,
                                   u8 *pu8OTPBuffer,
                                   OTPRAMUpdatedDB_t *pCfgUpdates,
                                   u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_otp_revoke_AllKeys_priv(dev, pu8OTPBuffer, pCfgUpdates, u8UpdateCnt);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_otp_revoke_ROTKey(const mepa_device_t  *dev,
                                  u8 *pu8OTPBuffer,
                                  OTPRAMUpdatedDB_t *pCfgUpdates,
                                  u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_otp_revoke_ROTKey_priv(dev, pu8OTPBuffer, pCfgUpdates, u8UpdateCnt);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_otp_prog_RepKey(const mepa_device_t  *dev,
                                u8 *pu8SignedKey,
                                u8 *pu8OTPBuffer,
                                OTPRAMUpdatedDB_t *pCfgUpdates,
                                u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_otp_prog_RepKey_priv(dev, pu8SignedKey, pu8OTPBuffer, pCfgUpdates, u8UpdateCnt);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_otp_cfg_program(const mepa_device_t  *dev,
                                u8 *pu8OTPBuffer,
                                OTPRAMUpdatedDB_t *pCfgUpdates,
                                u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_otp_cfg_program_priv(dev, pu8OTPBuffer, pCfgUpdates, u8UpdateCnt);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_get_serdes_config(const mepa_device_t *dev,
                                  SD_CFG_SPEED_IDX_t speed,
                                  eSERDES_CFG_T cfgType,
                                  __SERDES_CONFIG_T *const data)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_get_serdes_config_priv(dev, speed, cfgType, data);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_set_serdes_config(const mepa_device_t *dev,
                                  SD_CFG_SPEED_IDX_t speed,
                                  eSERDES_CFG_T cfgType,
                                  const __SERDES_CONFIG_T *data)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_set_serdes_config_priv(dev, speed, cfgType, data);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_KRLog_Enable(const mepa_device_t *dev,
                             mepa_bool_t bkrlog_enable,
                             mepa_bool_t bline_port_en,
                             mepa_bool_t  bhost_port_en)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_KRLog_Enable_priv(dev, bkrlog_enable, bline_port_en, bhost_port_en);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_KRLog_Reset(const mepa_device_t *dev,
                            uint32_t u32KRLogOffset,
                            uint16_t u16Len)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);
    rc = lan80xx_KRLog_Reset_priv(dev, u32KRLogOffset, u16Len);
    MEPA_EXIT(dev);

    return rc;
}
