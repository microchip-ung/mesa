// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// This file declares the lan8042 MCU chip specic APIs and corresponding
// data structures


#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <lan80xx_mcu.h>
#include "lan80xx_private.h"
#include "lan80xx_mcu_dfu.h"
#include "regs_lan80xx_mcu_mailbox.h"
#include "regs_lan80xx_mcu_io_mngt_misc.h"
#include "regs_lan80xx_gpio_ctrl.h"
#include "regs_lan8042.h"
#include "sha256/sha256.h"

static uint8_t gau8RespBuffer[1024] = { 0 };

mepa_rc RevokeAllOtpKeys(const mepa_device_t  *dev);
mepa_rc RevokeRotKey(const mepa_device_t  *dev);
mepa_rc OTPProgReplacementKey(const mepa_device_t  *dev,
                              u8 u8KeyNo,
                              u8 *pu8KeyData);
static mepa_rc authenticate_fw_image();

static mepa_rc lan80xx_ram_init(mepa_device_t    *dev, mepa_port_no_t  port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_rc rc = MEPA_RC_OK;
    u32 val = 0;
    /* Read Channel ID */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_SLICE_SPARE_RW_0, &val);
    u8 channel_id =  LAN80XX_X_HOST_SLICE_SPARE_RW_0_SPARE_RW_0_CHN_ID(val);

    /* Update BIST BYPASS Strap Configuration */
    LAN80XX_CSR_WRM(port_no, LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS, LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_BIST_BYPASS,
                    LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_BIST_BYPASS);

    /* As BIST is Bypass Consider BIST is Passed */
    LAN80XX_CSR_WRM(port_no, LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS, (LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE0_PASS << channel_id),
                    (LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE0_PASS << channel_id));

    /* UNG_MALIBU_25G-1973: Configure TX & RX clock of SERDES muxing and enable MAC_RETIMING MODE */
    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Enable MAC Retimer Mode (Bit 7) and Switch DESCLK with SERCLK at BIST (Bit 8) */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, (LAN80XX_BIT(7) | LAN80XX_BIT(8)),
                        (LAN80XX_BIT(7) | LAN80XX_BIT(8)));
    } else {
        /* Switch DESCLK with SERCLK at BIST (Bit 8) */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, LAN80XX_BIT(8), LAN80XX_BIT(8));
    }

    /* UNG_MALIBU_25G-2469: some synchronizers in path and some MAC and MACSEC SW_RST bits have to be first cleared */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG, 0,
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG, 0,
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG, 0, LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG, 0, LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_SW_RST);

    /* POST 1 RAM Init */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_SLICE_LINE_RAM_INIT_RAM_INIT, LAN80XX_POST1_TRIGGER);
    T_I(MEPA_TRACE_GRP_GEN, "\nPOST 1 RAM INIT Triggeredon Port : %d\n", port_no);

    /* Wait for 50us to do RAM Initialization */
    MEPA_NSLEEP(50000);

    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Switch to PCS Retimer mode back and Do not replace DESCLK with SERCLK */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0x0, LAN80XX_BIT(7) | LAN80XX_BIT(8));
    } else {
        /* Do not replace DESCLK with SERCLK */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0, LAN80XX_BIT(8));
    }

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_SLICE_LINE_RAM_INIT_RAM_INIT_BUSY, &val);

    if (val != 0) {
        T_E(MEPA_TRACE_GRP_GEN, "POST 1 Ram Initialization Failed on Port : %d \n", port_no);
        LAN80XX_CSR_WRM(port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_INIT_STATUS_ADDR + channel_id)),  0, LAN80XX_POST1_TRIGGER);
        base_data->post1_passed = 0;
        rc = MEPA_RC_ERROR;
    } else {
        LAN80XX_CSR_WRM(port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_INIT_STATUS_ADDR + channel_id)),  LAN80XX_POST1_TRIGGER,
                        LAN80XX_POST1_TRIGGER);
    }
    return rc;
}



static mepa_rc lan80xx_post1_bist_trigger(mepa_device_t  *dev, mepa_port_no_t  port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_rc rc = MEPA_RC_OK;
    u32 val = 0;

    /* Read Channel ID */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_SLICE_SPARE_RW_0, &val);
    u8 channel_id =  LAN80XX_X_HOST_SLICE_SPARE_RW_0_SPARE_RW_0_CHN_ID(val);

    /* UNG_MALIBU_25G-1973: Configure TX & RX clock of SERDES muxing and enable MAC_RETIMING MODE */
    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Enable MAC Retimer Mode (Bit 7) and Switch DESCLK with SERCLK at BIST (Bit 8) */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, (LAN80XX_BIT(7) | LAN80XX_BIT(8)),
                        (LAN80XX_BIT(7) | LAN80XX_BIT(8)));
    } else {
        /* Switch DESCLK with SERCLK at BIST (Bit 8) */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, LAN80XX_BIT(8), LAN80XX_BIT(8));
    }

    /* UNG_MALIBU_25G-2469: some synchronizers in path and some MAC and MACSEC SW_RST bits have to be first cleared */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG, 0,
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG, 0,
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG, 0, LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG, 0, LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_SW_RST);

    T_I(MEPA_TRACE_GRP_GEN, "POST 1 BIST Trigger on Port : %d\n", port_no);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_SLICE_BIST1_GO, LAN80XX_POST1_TRIGGER);

    /* Wait for 350us to run BIST */
    MEPA_NSLEEP(350000);

    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Switch to PCS Retimer mode back and Do not replace DESCLK with SERCLK */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0x0, LAN80XX_BIT(7) | LAN80XX_BIT(8));
    } else {
        /* Do not replace DESCLK with SERCLK */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0, LAN80XX_BIT(8));
    }

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_SLICE_BIST1_STATUS, &val);
    T_I(MEPA_TRACE_GRP_GEN, "POST 1 BIST Status on Port : 0x%x\n", val);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_BIST_STATUS_ADDR + channel_id)), val);

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_SLICE_BIST1_RESULT, &val);
    T_I(MEPA_TRACE_GRP_GEN, "POST 1 BIST Result on Port : 0x%x\n", val);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_BIST_RESULT_ADDR + channel_id)), val);

    if (val != LAN80XX_POST1_TRIGGER) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_BIST_STATUS_ADDR + channel_id)),
                        LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_BIST_TO,
                        LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_BIST_TO)

        T_E(MEPA_TRACE_GRP_GEN, "POST 1 Init Failed on Port : %d\n", port_no);
        base_data->post1_passed = 0;
        rc = MEPA_RC_ERROR;
    }
    return rc;
}

mepa_rc lan80xx_post1_init(mepa_device_t   *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    u32 val = 0;
    mepa_rc rc = MEPA_RC_OK;
    base_data->post1_passed = 1;

    if (data->port_state.power != LAN80XX_PHY_POWER_ENABLE) {
        /* Performing Serdes Configuration to Enable Serdes Clocks to Perform POST 1 */
        if (lan80xx_serdes_configuration(dev, port_no, MESA_SPEED_10G, &data->port_state.port_mode) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Serdes Init Failed on Port : %d \n", data->port_no);
            return MEPA_RC_ERROR;
        }
    }
    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &val);

    /* A0 and A1 BIST Failed in RTL, so BIST BYPASS STRAP should be 1 */
    if (data->dev.rev == LAN80XX_REV_A0 || data->dev.rev == LAN80XX_REV_A1) {
        val = val | LAN80XX_BIST_BYPASS_STRAP;
    }
    for (u8 i = 0; i < base_data->max_port_cnt; i++) {

        if (base_data->other_port_dev[i] == NULL) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Port %d Instance is not available in Base Dev \n", base_data->chip_ports[i]);
            base_data->post1_passed = 0;
            return MEPA_RC_ERROR;
        }

        if (val & LAN80XX_BIST_BYPASS_STRAP) {
            rc = lan80xx_ram_init(base_data->other_port_dev[i], base_data->chip_ports[i]);
        } else {
            rc = lan80xx_post1_bist_trigger(base_data->other_port_dev[i], base_data->chip_ports[i]);
        }
    }
    if ((base_data->post1_passed == 1)) {
        /* Update POST 1 Done */
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS, LAN80XX_POST1_STATUS_P1_POST_DONE, LAN80XX_POST1_STATUS_P1_POST_DONE);
    } else {
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS, 0, LAN80XX_POST1_STATUS_P1_POST_DONE);
        rc = MEPA_RC_ERROR;
    }
    return rc;
}


mepa_rc lan80xx_check_mcu_rdy(mepa_device_t *dev)
{
    T_D(MEPA_TRACE_GRP_GEN, "Waiting for MCU rdy");
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val;
    mepa_rc rc = MEPA_RC_ERROR;
    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &val);
    if (val & 0x4) {
        T_D(MEPA_TRACE_GRP_GEN, "%s MCU ready ", __FUNCTION__);
        rc = MEPA_RC_OK;
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s Error in MCU ready ", __FUNCTION__);
        rc = MEPA_RC_ERROR;
    }
    return rc;
}

mepa_rc lan80xx_mcu_mailbox_init(const mepa_device_t *dev, u32 u32McuIntMask, u32 u32HostIntMask)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "Device not created!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;

    /* Clearing Interrupt Mask and Flags */
    LAN80XX_CSR_WR(dev, data->port_no, LAN80XX_MCU_MAILBOX_MAILBOX_HOST_INT_MASK, 0);
    LAN80XX_CSR_WR(dev, data->port_no, LAN80XX_MCU_MAILBOX_MAILBOX_MCU_INT_MASK, 0);
    LAN80XX_CSR_WR(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), MALIBOX_FALG_CLEAR_ALL);

    /* Enable Host interrupt mask register */
    LAN80XX_CSR_WRM(data->port_no, LAN80XX_MCU_MAILBOX_MAILBOX_HOST_INT_MASK, u32HostIntMask, LAN80XX_BIT(1));
    /* Enable MCU interrupt mask register */
    LAN80XX_CSR_WRM(data->port_no, LAN80XX_MCU_MAILBOX_MAILBOX_MCU_INT_MASK, u32McuIntMask, LAN80XX_BIT(0));
    /* Enable INTR_SRC_EN_1 with mailbox interrupt */
    LAN80XX_CSR_WRM(data->port_no, LAN80XX_GPIO_CTRL_INTR_SRC_EN(1), LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_MCU_MBOX_INTR_EN,
                    LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_MCU_MBOX_INTR_EN);
    return rc;
}

uint16_t crc_16(const unsigned char *input, size_t num_bytes)
{
    uint8_t i;
    uint16_t u16crc;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    T_D(MEPA_TRACE_GRP_GEN, "calculating CRC");
    u16crc = CRC_START_CCITT;
    while (num_bytes--) {
        u16crc ^= *(unsigned char *)input++ << 8;
        for (i = 0; i < 8; i++) {
            u16crc = u16crc & 0x8000 ? (u16crc << 1) ^ CRC_POLY_CCITT : u16crc << 1;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "CRC: 0x%04x", u16crc);

    return u16crc & CRC_START_CCITT;
}

/*
* FN: lan80xx_CreatePacket
* This function is used to create request packet to used for Host communication
* Reference: DOS-05247 Malibu-25G Optical PHY Product Firmware DOS
* Section 8.3.1 Request Packet Format
* offset    Size(B)     Name                        Value
* 0x00      1           Request Packet ID           PKT_ID
* 0x01      1           Reserved                    0xFF
* 0x02      2           Request Packet Length       Total Request packet length (max is 1024)
* 0x04      N           Request Data                Request data of N bytes
* 0x04+N    2           CRC16                       CRC16
*
* Device Commands:
* GET_DEVICE_INFO - 0x00
* DEVICE_RESET - 0x01
* MEM_READ  -   0x06
* MEM_WRITE - 0x07
* DFU_UPDATE - 0x0B
*/
uint16_t lan80xx_CreatePacket(uint8_t u8PacketId, uint16_t u16CmdParamLen, uint8_t *pu8PktBuf, uint8_t *pu8CmdData, uint8_t u8Reserved)
{
    uint16_t u16Len = 0;
    PKT_HDR_T *PktHdr = (PKT_HDR_T *)pu8PktBuf;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    u16Len = u16CmdParamLen + MB_MAX_PKT_HEADER_LEN + MB_MAX_CRC_LEN;
    T_D(MEPA_TRACE_GRP_GEN, "Creating packet with pkt id: 0x%x of len: 0x%x", u8PacketId, u16Len);
    PktHdr->u8PktId = u8PacketId;
    PktHdr->u8Reserved = u8Reserved;
    PktHdr->u16PktLen = u16Len;
    if ((pu8CmdData != NULL) && (u16CmdParamLen > 0)) {
        T_D(MEPA_TRACE_GRP_GEN, "Copying cmd parameter data of length %d", u16CmdParamLen);
        memcpy(&pu8PktBuf[MB_PKT_DATA_OFFSET], pu8CmdData, u16CmdParamLen);
    }

    //Add CRC16 to the end
    T_D(MEPA_TRACE_GRP_GEN, "Adding CRC")
    uint16_t u16CRC = crc_16(pu8PktBuf, u16CmdParamLen + MB_MAX_PKT_HEADER_LEN);
    uint16_t *pu16PktCrc = (uint16_t *)(pu8PktBuf + MB_PKT_DATA_OFFSET + u16CmdParamLen);
    *pu16PktCrc = u16CRC;
    T_D(MEPA_TRACE_GRP_GEN, "Created packet of length %d", u16Len);

    return u16Len;
}

static mepa_rc ValidateCRC(uint8_t *pu8PktBuf, uint16_t u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t u16CRC = 0, u16PktCRC = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    /* compute crc */
    u16CRC = crc_16(pu8PktBuf, u16Len);
    /* extract packet crc */
    u16PktCRC = MAKEWORD(pu8PktBuf[u16Len], pu8PktBuf[u16Len + 1]);
    /* Now compare crc */
    if (u16CRC != u16PktCRC) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. CRC Error , Expected CRC : %lu ,\
            Calculated CRC : %lu", __FUNCTION__, u16CRC, u16PktCRC);
        /* crc match failed */
        rc = MEPA_RC_ERR_MB_INVALID_CRC;
    }

    return rc;
}

mepa_rc lan80xx_ValidatePacket(uint8_t *u8PktBuf)
{
    mepa_rc rc = MEPA_RC_OK;
    PKT_HDR_T *pPktHdr = (PKT_HDR_T *)u8PktBuf;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    /* Payload can not be more than MAX_PKT_LEN */
    if (pPktHdr->u16PktLen > MB_MAX_PKT_LEN) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Invalid Pkt length 0x%x, \
                Validate Packet failed ", __FUNCTION__, pPktHdr->u16PktLen);
        /* invalid packet payload length */
        rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
        return rc;
    }
    rc = ValidateCRC(u8PktBuf, (pPktHdr->u16PktLen - MB_MAX_CRC_LEN));
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Invalid CRC, Validate Packet failed", __FUNCTION__);
        /* Packet crc validation failed */
    }
    return rc;
}


/*
* Fn: MB_ClearResponseFlag
* This function is used to clear Response Flag
* Mailbox Flag Register - 0xDA00 (Bit 31:24)
*/
mepa_rc lan80xx_MB_ClearFlag(const mepa_device_t *dev, uint32_t u32ClearMask)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "Device not created!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;
    T_D(MEPA_TRACE_GRP_GEN, "Clear flag mask: 0x%x", u32ClearMask);
    LAN80XX_CSR_WR(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), u32ClearMask);

    return rc;
}

/*
* Fn: MB_SetRequestFlag
* This function is used to set Request Flag
* Mailbox MCU Interrupt Mask Register - 0xDA01
* Mailbox Flag Register - 0xDA00 (Bit 23:16)
*/
mepa_rc lan80xx_MB_SetFlag(const mepa_device_t *dev, uint32_t u32SetMask)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "Device not created!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;
    T_D(MEPA_TRACE_GRP_GEN, "Set flag mask: 0x%x", u32SetMask);
    LAN80XX_CSR_WR(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), u32SetMask);

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
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    T_I(MEPA_TRACE_GRP_GEN, "%s\n", __FUNCTION__);
    base_data->ft_gpio_read = gpio_cb;
    return rc;
}

mepa_rc lan80xx_MB_SendRequest(const mepa_device_t *dev, uint8_t *au8CmdPkt, uint16_t u16DataLen)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;
    mepa_port_no_t port_no = 0;
    uint16_t u16Counter = 0;
    uint32_t u32SpiData = 0x00000000;
    uint16_t u16Reg = MAILBOX_CMD_ADDR;

    T_I(MEPA_TRACE_GRP_GEN, "%s\n", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "device not registered!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;
    port_no = data->port_no;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    /* Rounding off the packet length into multiples of 4 to facilitate SPI read/write */
    if (u16DataLen % SPI_VAL_LEN != 0) {
        u16DataLen += (SPI_VAL_LEN - (u16DataLen % 4));
    }

    T_D(MEPA_TRACE_GRP_GEN, "Writing pkt to mailbox request area\n");
    while (u16DataLen) {
        u32SpiData = 0;
        u32SpiData = (au8CmdPkt[u16Counter + 3] << 24 | au8CmdPkt[u16Counter + 2] << 16 | \
                      au8CmdPkt[u16Counter + 1] << 8 | au8CmdPkt[u16Counter]);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, u16Reg), u32SpiData);

        u16Reg++;
        u16Counter += SPI_VAL_LEN;
        u16DataLen -= SPI_VAL_LEN;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Pkt written, checking MCU busy status...\n");
    uint8_t u8McuInterrupt = 0;
    if (base_data->ft_gpio_read == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "INTR_A/B callback not registered!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;

    }
    u8McuInterrupt = base_data->ft_gpio_read();
    uint32_t u32Val = 0;
    if (1 == u8McuInterrupt) {
        /*
         * The Host interrupt shall be set due to multiple reasons
         * check MCU interrupt flag is set or not
         * If set, wait until it clears
         * We should not overwrite the request area
         */
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
        if (u32Val & MAILBOX_INTR_ENABLE) {
            T_W(MEPA_TRACE_GRP_GEN, "MCU busy with older command, Waiting for MCU ready...");
        }
        while (u32Val & MAILBOX_INTR_ENABLE) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "Raising MCU interrupt");
    /* Enable MCU interrupt mask register */
    u32Val = 0;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), &u32Val);
    u32Val |= MAILBOX_INTR_ENABLE;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), u32Val);
    /* Set flag */
    rc = lan80xx_MB_SetFlag(dev, MAILBOX_FLAG_SET_BIT0);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Failed to Set Mailbox Request Flag: %d", __FUNCTION__, rc);
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "Request packet sent");
    }
    return rc;
}

/*
* Fn: MB_ReadResponse
* This function is uses Host communication protocol to receive data from the Host application
* Response buffer - D900 to D9FF
*/
mepa_rc lan80xx_MB_ReadResponse(const mepa_device_t *dev, uint8_t *u8ResponsePkt, uint16_t *u16PayloadLen, uint16_t u16MailboxTimeout)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t u16Timeout = 0;
    uint8_t u8McuInterrupt = 0;
    phy25g_phy_state_t *data = NULL;
    mepa_port_no_t port_no = 0;
    uint32_t u32Val = 0x00000000;
    uint16_t u16PktLen;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;
    port_no = data->port_no;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    T_D (MEPA_TRACE_GRP_GEN, "Waiting for HOST interrupt...");
    while (1) {
        u8McuInterrupt = base_data->ft_gpio_read();
        /*
         * If interrupt is set, then make sure HOST interrupt is set before reading response
         */
        if (u8McuInterrupt) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
            if (u32Val & MAILBOX_HOST_INTR_MASK) {
                /* This is valid for mailbox command */
                T_I(MEPA_TRACE_GRP_GEN, "Got Host interrupt! Took %d msec", u16Timeout);
                break;
            }
        }
        MEPA_NSLEEP(1);
        u16Timeout++;
        if (u16Timeout > u16MailboxTimeout) {
            break;
        }
    }
    if (u16Timeout > u16MailboxTimeout) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Timeout. No response from MCU", __FUNCTION__);
        /*
        * Clear MCU request flag using Set function
        */
        lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT0);
        rc = MEPA_RC_ERR_MB_RESP_TIMEOUT;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Reading response packet...");
    if (u8McuInterrupt) {
        //Read Response

        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_RESP_ADDR), &u32Val);

        PKT_HDR_T *pPktHdr = (PKT_HDR_T *)&u32Val;
        if (pPktHdr->u16PktLen == 0) {
            /* Clear HOST interrupt flag */
            lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT1);
            T_W(MEPA_TRACE_GRP_GEN, "%s: Response Area is empty", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        *u16PayloadLen = pPktHdr->u16PktLen;

        u8ResponsePkt[0] = u32Val & 0xFF;
        u8ResponsePkt[1] = u32Val >> 8 & 0xFF;
        u8ResponsePkt[2] = u32Val >> 16 & 0xFF;
        u8ResponsePkt[3] = u32Val >> 24 & 0xFF;

        /*Rounding off the pktlen to read in multiples of 4 (Mailbox read size)*/
        if (pPktHdr->u16PktLen & 0x03) {
            u16PktLen = (pPktHdr->u16PktLen) + (4 - (pPktHdr->u16PktLen & 0x03));
        } else {
            u16PktLen = pPktHdr->u16PktLen;
        }

        /*Read rest of the mailbox response*/
        uint16_t u16Counter = 4;
        uint16_t u16Reg = MAILBOX_RESP_ADDR + 1;

        while (u16Counter < u16PktLen) {
            u32Val = 0x00000000;

            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, u16Reg), &u32Val);

            u8ResponsePkt[u16Counter] = u32Val & 0xFF;
            u8ResponsePkt[u16Counter + 1] = u32Val >> 8 & 0xFF;
            u8ResponsePkt[u16Counter + 2] = u32Val >> 16 & 0xFF;
            u8ResponsePkt[u16Counter + 3] = u32Val >> 24 & 0xFF;
            u16Reg += 1;
            u16Counter += 4;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "Read full response of length 0x%x", u16PktLen);
    T_D(MEPA_TRACE_GRP_GEN, "clearing HOST interrupt...");

    rc = lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT1);
    if ((rc != MEPA_RC_OK)) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Failed to clear response flag", __FUNCTION__);
    }

    return rc;
}

mepa_rc lan80xx_get_fw_info(const mepa_device_t *dev, DEVICE_INFO *psDevInfo)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen = 0, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    // Step 1: Create Packet for Device Info
    u16PktLen = lan80xx_CreatePacket(eGET_DEVICE_INFO, 0, au8CmdBuffer, NULL, RESERVED_ID);

    // Step 2: Send Request Packet
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    // Step 4: Validate Packet
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    if (recvPkt->u8PktId == eGET_DEVICE_INFO + 0x80) {
        psDevInfo->PartId = (uint16_t)(pu8Payload[0]) | (pu8Payload[1] << 8);
        psDevInfo->TargetId = pu8Payload[2];
        psDevInfo->ImageType = (enIMAGE_TYPE_T)(pu8Payload[3]);
        psDevInfo->FirmwareVersion = ((uint16_t)pu8Payload[4] << 8) | pu8Payload[5];
        T_I(MEPA_TRACE_GRP_GEN, "%s. Success", __FUNCTION__);
        T_I(MEPA_TRACE_GRP_GEN, "Part ID: 0x%x\n", psDevInfo->PartId);
        T_I(MEPA_TRACE_GRP_GEN, "Target ID: 0x%x\n", psDevInfo->TargetId);
        T_I(MEPA_TRACE_GRP_GEN, "Image Type: 0x%x\n", psDevInfo->ImageType);
        T_I(MEPA_TRACE_GRP_GEN, "Firmware Version: %02x.%02x\n", pu8Payload[4], pu8Payload[5]);
    } else {
        if (recvPkt->u8PktId == eGET_DEVICE_INFO + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eGET_DEVICE_INFO);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
    }
    return rc;
}

mepa_rc lan80xx_memory_read(const mepa_device_t *dev, uint32_t u32Addres, uint8_t *pu8Data, const uint16_t u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PayloadLen = 0;
    uint8_t au8CmdParam[8] = { 0 };

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    if (u16Len > MB_MAX_PAYLOAD_LEN) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Invalid length. Max supported length is: %d", __FUNCTION__, MB_MAX_PAYLOAD_LEN);
        rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
        return rc;
    }

    T_D (MEPA_TRACE_GRP_GEN, "Reading from address 0x%04X of length %d", u32Addres, u16Len);
    /* Step 1: Create Packet */
    /* 32 bit address */
    au8CmdParam[0] = (u32Addres) & 0xff;
    au8CmdParam[1] = (u32Addres >> 8) & 0xff;
    au8CmdParam[2] = (u32Addres >> 16) & 0xff;
    au8CmdParam[3] = (u32Addres >> 24) & 0xff;

    /*16 bit length */
    au8CmdParam[4] = (u16Len) & 0xFF;
    au8CmdParam[5] = (u16Len >> 8) & 0xFF;

    uint16_t u16PktLen = lan80xx_CreatePacket(eMEM_READ, 6, au8CmdBuffer, &au8CmdParam[0], RESERVED_ID);

    /* Step 2: Send Command */
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /*Step 4: Validate Response packet */
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: pkt validate failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    /*If response parameter length < 2, error response */
    if (recvPkt->u8PktId == eMEM_READ + 0x80) {
        /*Extracting len and data bytes from packet */
        uint16_t u16DataLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        memcpy(pu8Data, &pu8Payload[0], u16DataLen);
        T_I(MEPA_TRACE_GRP_GEN, "%s: Success with len %d", __FUNCTION__, u16DataLen);
    } else {
        if (recvPkt->u8PktId == eMEM_READ + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eMEM_READ);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
    }
    return rc;
}

mepa_rc lan80xx_memory_write(const mepa_device_t *dev, uint32_t u32Addres, uint8_t *pu8Data, const u16 u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[1024] = { 0 };
    uint16_t u16RespLen = 0;
    uint16_t u16CmdParamLen = 0;

    /* Form command parameter array for Packet data */
    uint8_t au8cmdParam[MB_MAX_PAYLOAD_LEN] = { 0 };

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    if (u16Len > (MB_MAX_PAYLOAD_LEN - 6)) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Invalid length! Maximum writable per packet is (%d) Bytes", \
            __FUNCTION__, (MB_MAX_PAYLOAD_LEN - 6));
        rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
        return rc;
    }

    T_D (MEPA_TRACE_GRP_GEN, "MEM Write at 0x%04X of length %d", u32Addres, u16Len);
    /* Step 1: Create Packet */
    /* 32 bit address */
    au8cmdParam[0] = (u32Addres) & 0xff;
    au8cmdParam[1] = (u32Addres >> 8) & 0xff;
    au8cmdParam[2] = (u32Addres >> 16) & 0xff;
    au8cmdParam[3] = (u32Addres >> 24) & 0xff;

    /*16 bit length */
    au8cmdParam[4] = (u16Len) & 0xFF;
    au8cmdParam[5] = (u16Len >> 8) & 0xFF;
    u16CmdParamLen = 6;

    /* Copy Data bytes of length wLen */
    memcpy(&au8cmdParam[u16CmdParamLen], &pu8Data[0], u16Len);
    u16CmdParamLen += u16Len;

    uint16_t u16PktLen = lan80xx_CreatePacket(eMEM_WRITE, u16CmdParamLen, au8CmdBuffer, &au8cmdParam[0], RESERVED_ID);

    /* Step 2: Send Command*/
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_GEN, "%s: Mailbox send command failed ", __FUNCTION__);
        return rc;
    }

    /* Step 3: Read response from Mailbox area into response buffer */
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16RespLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_GEN, "%s: Mailbox read response failed ", __FUNCTION__);
        return rc;
    }

    /* Step 4: Validate packet */
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: pkt validate failed", __FUNCTION__);
        return rc;
    }

    /* Decode the response packet to read the message */
    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    if (recvPkt->u8PktId == eMEM_WRITE + 0x80) {
        T_I(MEPA_TRACE_GRP_GEN, "%s:Memory write success", __FUNCTION__);
    } else {
        if (recvPkt->u8PktId == eMEM_WRITE + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eMEM_WRITE);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
    }
    return rc;
}

mepa_rc lan80xx_mcu_reset(const mepa_device_t *dev)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    // Step 1: Create Packet for Reset
    u16PktLen = lan80xx_CreatePacket(eDEVICE_RESET, 0, au8CmdBuffer, NULL, RESERVED_ID);

    // Step 2: Send command
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_GEN, "%s: Mailbox send command failed ", __FUNCTION__);
        return rc;
    }

    //Step 3: Clear Response Flasg
    rc = lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT1);

    return rc;
}

static mepa_rc authenticate_fw_image()
{
    mepa_rc rc = MEPA_RC_OK;
    struct sha256_buff sha256_ctx;
    unsigned char sha256_out[32] = {0};

    sha256_init(&sha256_ctx);
    sha256_update(&sha256_ctx, gau8FwImageData, gu32FwImageLen);
    sha256_finalize(&sha256_ctx);
    sha256_read(&sha256_ctx, sha256_out);
    /*
     * Compare the calculated sha256 checksum
     * with one that come along with firmware image
     */
    if (memcmp(sha256_out, gau8Sha256Sum, 32) != 0) {
        T_E(MEPA_TRACE_GRP_GEN, "SHA checksum failed!");
        rc = MEPA_RC_ERROR;
    }

    return rc;
}

mepa_rc lan80xx_fw_update(mepa_device_t *dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;
    mepa_port_no_t port_no = 0;
    uint8_t au8CmdBuffer[1024] = { 0 };
    uint16_t u16RespLen = 0;
    uint8_t au8CmdParam[MB_MAX_PAYLOAD_LEN] = { 0 };
    uint32_t u32Val = 0;
    uint16_t u16Timeout = 0;
    uint8_t u8McuInterrupt = 0;
    uint16_t u16Count = 0;
    uint32_t u32Offset = 0, u32BytesWritten = 0;
    uint16_t u16CmdParamLen = 0;
    uint32_t u32Size = gu32FwImageLen;
    uint8_t *pu8FwData = gau8FwImageData;
#ifdef DFU_PROFILING_EN
    uint64_t u64Dfu_time_ms = 0;
    uint64_t u64DfuStart_time_ms = 0, u64DfuStop_time_ms = 0;
#endif

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);

    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

#ifdef DFU_PROFILING_EN
    u64DfuStart_time_ms = MEPA_UPTIME_MSECONDS();
#endif

    data = (phy25g_phy_state_t *)dev->data;
    port_no = data->port_no;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    /* Without INTR_A/B DFU can't be handled */
    if (base_data->ft_gpio_read == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "INTR_A/B callback not registered!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    /* perform SHA256 authentication, send to MCU only if SHA is valid */
    rc = authenticate_fw_image();
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "FW image SHA Authentication failed\n");
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "FW image SHA authentication success!!\n");
    /* Set the DFU Strap Register*/
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
    u32Val |= DFU_STRAP;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), u32Val);

    /* Read DFU Strap*/
    u16Timeout = 0;
    while (1) {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
        if (u32Val) {
            break;
        }
        MEPA_NSLEEP(1000);
        u16Timeout++;
        if (u16Timeout > MAILBOX_INTR_TIMEOUT) {
            break;
        }
    }

    if (u32Val == 0) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. DFU Strap not set, Abort Firmware Update", __FUNCTION__);
        rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Resetting MCU...");
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 1, BLOCK_LVL_SOFT_RESET2), SW_RESET_MCU);

    T_D (MEPA_TRACE_GRP_GEN, "Waiting for First packet interrupt");
    /* Configure Mailbox MCU and Host interrupt mask after reset */
    rc = lan80xx_mcu_mailbox_init(dev, MAILBOX_INTR_ENABLE, MAILBOX_HOST_INTR_MASK);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "mailbox init failed\n");
        return rc;
    }
    // Wait for DFU first packet Interrupt
    u16Timeout = 0;
    while (1) {
        u8McuInterrupt = base_data->ft_gpio_read();
        if (u8McuInterrupt) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
            if (u32Val & MAILBOX_DFU_FIRST_PKT) {
                /* This is valid for mailbox command */
                T_I(MEPA_TRACE_GRP_GEN, "Got first packet interrupt! Took %d msec", u16Timeout);
                break;
            }
        }

        MEPA_NSLEEP(1000);
        u16Timeout++;
        if (u16Timeout > (MAILBOX_INTR_TIMEOUT)) {
            break;
        }
    }
    /* Clear first packet interrupt */
    lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT6);

    if (u8McuInterrupt && (u16Timeout < MAILBOX_INTR_TIMEOUT)) {
        /* UNG_MALIBU_25G-2476 Workaround */
        uint8_t byDataBuffer[4] = {0};
        lan80xx_memory_read(dev, LAN80XX_MCU_CODE_RAM_START_REGION, byDataBuffer, 4);
        lan80xx_memory_read(dev, LAN80XX_MCU_CODE_RAM_START_REGION + LAN80XX_MEMORY_SLICE_ONE_OFFSET, byDataBuffer, 4);
        lan80xx_memory_read(dev, LAN80XX_MCU_CODE_RAM_START_REGION + LAN80XX_MEMORY_SLICE_TWO_OFFSET, byDataBuffer, 4);
        lan80xx_memory_read(dev, LAN80XX_MCU_CODE_RAM_START_REGION + LAN80XX_MEMORY_SLICE_THREE_OFFSET, byDataBuffer, 4);
        do {
            u16Count++;
            if ((u32Offset + MB_MAX_PAYLOAD_LEN) > u32Size) {
                u16CmdParamLen = u32Size - u32Offset;
            } else {
                u16CmdParamLen = MB_MAX_PAYLOAD_LEN;
            }
            u32BytesWritten += u16CmdParamLen;

            memcpy(&au8CmdParam[0], &pu8FwData[u32Offset], u16CmdParamLen);

            /* Create Packet */
            uint16_t u16PktLen = lan80xx_CreatePacket(eDFU_UPDATE, u16CmdParamLen, au8CmdBuffer, au8CmdParam, RESERVED_ID);

            if (MEPA_RC_OK != (rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen))) {
                T_E(MEPA_TRACE_GRP_GEN, "%s. Mailbox send command failed at packet %d", __FUNCTION__, u16Count);
                break;
            }

            if (MEPA_RC_OK != (rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16RespLen, MAILBOX_INTR_TIMEOUT))) {
                T_E(MEPA_TRACE_GRP_GEN, "%s. Mailbox read response for DFU command failed at packet %d", __FUNCTION__, u16Count);
                break;
            }

            PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
            if (recvPkt->u8PktId == eDFU_UPDATE + 0x80) {
                T_D(MEPA_TRACE_GRP_GEN, "%s:DFU Packet %d success", __FUNCTION__, u16Count);
            } else {
                if (recvPkt->u8PktId == eDFU_UPDATE + 0x81) {
                    T_E(MEPA_TRACE_GRP_GEN, "%s. Fail", __FUNCTION__);
                    rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
                } else {
                    T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                        __FUNCTION__, (recvPkt->u8PktId - 0x80), eDFU_UPDATE);
                    rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
                }
                break;
            }
            u32Offset += MB_MAX_PAYLOAD_LEN;
        } while ((u32Offset < u32Size));

        /* Clearing DFU Strap */
        T_D(MEPA_TRACE_GRP_GEN, "Clearing DFU strap");
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
        u32Val &= ~(DFU_STRAP);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), u32Val);
        if (u32BytesWritten == u32Size) {
            T_I(MEPA_TRACE_GRP_GEN, "All packets sent, Raise Last packet interrupt");
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), MAILBOX_DFU_LAST_PKT);
            if (MEPA_RC_OK != (rc = lan80xx_MB_SetFlag(dev, MAILBOX_FLAG_SET_BIT7))) {
                T_E(MEPA_TRACE_GRP_GEN, "%s. Failed to set Bit 7 marking the end of DFU transfer", __FUNCTION__);
                rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
                return rc;
            }
            T_D(MEPA_TRACE_GRP_GEN, "Sent last packet interrupt");
            /* Read Strap */
            LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
            /* Perform POST1 when Serdes Init Strap is Set */
            if (u32Val & SERDES_INIT_STRAP) {
                if (lan80xx_post1_init(dev, data->port_no) != MEPA_RC_OK) {
                    T_E(MEPA_TRACE_GRP_GEN, "POST1 Failed on Port %d \n", data->port_no);
                    return MEPA_RC_ERROR;
                }
            }
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
            T_D(MEPA_TRACE_GRP_GEN, "Waiting for FW ready interrupt");
            u16Timeout = 0;
            while (u16Timeout < MAILBOX_INTR_TIMEOUT) {
                /* Read FW Status */
                LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
                /* As endianess is different, bit 0 goes to MSB*/
                if (u32Val & 0x04) {
                    /* If BIT0 set, FW status active*/
                    T_I(MEPA_TRACE_GRP_GEN, "Switched to Application. Took %d msecs", u16Timeout);
                    break;
                }
                MEPA_NSLEEP(1000);
                u16Timeout++;
            }
            if (u16Timeout == MAILBOX_INTR_TIMEOUT) {
                T_I(MEPA_TRACE_GRP_GEN, "MB Flag reg value : 0x%x", u32Val);
                LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), &u32Val);
                T_I(MEPA_TRACE_GRP_GEN, "MB mask reg value : 0x%x", u32Val);
                T_E(MEPA_TRACE_GRP_GEN, "Failed to start Application, aborting");
                rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
                return rc;
            }

            /* Memory read DFU_STATUS_REG to check if Signature Verification is successful */
            uint8_t u8ReadBytes[4] = { 0 };
            rc = lan80xx_memory_read(dev, (MCU_DATA_RAM_OFFSET + DFU_STATUS_REG_OFFSET), u8ReadBytes, 4);
            if (rc != MEPA_RC_OK) {
                /* Memory read failed */
                T_E(MEPA_TRACE_GRP_GEN, "DFU STATUS REG read failed");
                rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
                return rc;
            }
            if (u8ReadBytes[0] & DFU_SIGN_VERIFY_FAIL_POS) {
                T_E(MEPA_TRACE_GRP_GEN, "MCHP Signature Verification failed");
                rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
                return rc;
            }
            T_I(MEPA_TRACE_GRP_GEN, "%s. Signature Verification passed", __FUNCTION__);
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "Timeout! No first packet interrupt received");
        rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
        /* Clearing DFU Strap  for failure case before return */
        T_D(MEPA_TRACE_GRP_GEN, "Clearing DFU strap");
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
        u32Val &= ~(DFU_STRAP);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), u32Val);
    }
#ifdef DFU_PROFILING_EN
    u64DfuStop_time_ms = MEPA_UPTIME_MSECONDS();
    u64Dfu_time_ms = u64DfuStop_time_ms - u64DfuStart_time_ms;
    T_D(MEPA_TRACE_GRP_GEN, "DFU start (ms): %u", u64DfuStart_time_ms);
    T_D(MEPA_TRACE_GRP_GEN, "DFU stop (ms): %u", u64DfuStop_time_ms);
    T_E(MEPA_TRACE_GRP_GEN, "DFU Time (ms): %u", u64Dfu_time_ms);
#endif

    return rc;
}

mepa_rc lan80xx_otp_cfg_read(const mepa_device_t  *dev,
                             u8 u8RecIdx,
                             u8 *pu8Cfg,
                             u16 *pu16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (u8RecIdx > MAX_OTP_CFG_RECORDS) || (pu8Cfg == NULL) || (pu16Len == NULL)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP Cfg read request with index: %d", u8RecIdx);
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(eOTP_CFG_READ, 1, au8CmdBuffer, &u8RecIdx, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    if (recvPkt->u8PktId == eOTP_CFG_READ + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen == 0) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            *pu16Len = 0;
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        T_D(MEPA_TRACE_GRP_GEN, "Read cfg with len: %d", u16PktLen);
        /* Copy the payload to record data buffer */
        memcpy(pu8Cfg, &pu8Payload[0], u16PktLen);
        *pu16Len = u16PktLen;
        T_I(MEPA_TRACE_GRP_GEN, "OTP Config read success");
    } else if (recvPkt->u8PktId == eOTP_CFG_READ + 0x81) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd Failed with %d", __FUNCTION__, pu8Payload[0]);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
            __FUNCTION__, (recvPkt->u8PktId - 0x80), eOTP_CFG_READ);
        rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
    }

    return rc;
}

mepa_rc lan80xx_otp_read(const mepa_device_t  *dev,
                         u8 *pu8Data,
                         u16 u16Offset,
                         const u16 u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16DataLen, u16PayloadLen = 0x00;
    /* Form command parameter array for Packet data */
    uint8_t u8cmdParam[4] = { 0 };
    uint16_t u16OtpAddr, u16CurLen;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (pu8Data == NULL) || (u16Len == 0) || (u16Len > MAX_OTP_SIZE) || ((u16Offset + u16Len) > MAX_OTP_SIZE)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    u16OtpAddr = u16Offset;
    u16PktLen = 0;
    u16CurLen = 0;
    u16DataLen = 0;
    while (u16CurLen < u16Len) {
        u16DataLen = ((u16Len - u16CurLen) > (MB_MAX_PAYLOAD_LEN - 4)) ? (MB_MAX_PAYLOAD_LEN - 4) : (u16Len - u16CurLen);
        T_D(MEPA_TRACE_GRP_GEN, "OTP Read at Addr: %04x Len: %d", u16OtpAddr, u16DataLen);
        /* 16 bit address */
        u8cmdParam[0] = (u16OtpAddr) & 0xff;
        u8cmdParam[1] = (u16OtpAddr >> 8) & 0xff;
        /*16 bit length */
        u8cmdParam[2] = (u16DataLen) & 0xFF;
        u8cmdParam[3] = (u16DataLen >> 8) & 0xFF;
        /* Create command request Packet */
        u16PktLen = lan80xx_CreatePacket(eOTP_READ, 4, au8CmdBuffer, &u8cmdParam[0], RESERVED_ID);
        /* Send command Request Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
        rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
            break;
        }
        /* Read Response Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
        rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
            break;
        }
        /* Validate Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
        if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
            break;
        }
        PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
        uint8_t *pu8Payload = NULL;
        pu8Payload = &gau8RespBuffer[4];
        if (recvPkt->u8PktId == eOTP_READ + 0x80) {
            u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
            if ((u16PktLen == 0) || (u16PktLen != u16DataLen)) {
                T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
                T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
                rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
                break;
            }
            T_D(MEPA_TRACE_GRP_GEN, "Otp Read with len: %d", u16PktLen);
            /* Copy the payload to data buffer */
            memcpy(pu8Data + u16CurLen, &pu8Payload[0], u16PktLen);
            u16CurLen += u16DataLen;
            u16OtpAddr += u16DataLen;
            T_I(MEPA_TRACE_GRP_GEN, "OTP read success");
        } else if (recvPkt->u8PktId == eOTP_READ + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd Failed with %d", __FUNCTION__, pu8Payload[0]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
            break;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eOTP_READ);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
            break;
        }
    }

    return rc;
}

mepa_rc lan80xx_otp_write(const mepa_device_t  *dev,
                          u8 *pu8Data,
                          u16 u16Offset,
                          const u16 u16Len,
                          u8 u8WriteMode)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[1024] = { 0 };
    uint16_t u16PktLen, u16DataLen, u16PayloadLen = 0x00;
    /* Form command parameter array for Packet data */
    uint8_t u8cmdParam[MB_MAX_PAYLOAD_LEN] = { 0 };
    uint16_t u16OtpAddr, u16CurLen, u16CmdParamLen = 0, u16Idx = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (pu8Data == NULL) || (u16Len == 0) || (u16Len > MAX_OTP_SIZE) || ((u16Offset + u16Len) > MAX_OTP_SIZE)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    u16OtpAddr = u16Offset;
    u16PktLen = 0;
    u16CurLen = 0;
    u16DataLen = 0;
    while (u16CurLen < u16Len) {
        u16DataLen = ((u16Len - u16CurLen) > (MB_MAX_PAYLOAD_LEN - 4)) ? (MB_MAX_PAYLOAD_LEN - 4) : (u16Len - u16CurLen);
        T_D(MEPA_TRACE_GRP_GEN, "OTP Write at Addr: %04x Len: %d", u16OtpAddr, u16DataLen);
        /* 16 bit address */
        u8cmdParam[0] = (u16OtpAddr) & 0xff;
        u8cmdParam[1] = (u16OtpAddr >> 8) & 0xff;
        /*16 bit length */
        u8cmdParam[2] = (u16DataLen) & 0xFF;
        u8cmdParam[3] = (u16DataLen >> 8) & 0xFF;
        u16CmdParamLen = 4;
        /* Updating command parameter */
        memcpy(&u8cmdParam[u16CmdParamLen], &pu8Data[u16Idx], u16DataLen);
        u16CmdParamLen += u16DataLen;
        /* Create command request Packet */
        u16PktLen = lan80xx_CreatePacket(eOTP_WRITE, u16CmdParamLen, au8CmdBuffer, &u8cmdParam[0], u8WriteMode);
        /* Send command Request Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
        rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
            break;
        }
        /* Read Response Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
        if (u8WriteMode == eOTPWRITE_AUTH) {
            rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_SIGN_TIMEOUT);
        } else {
            rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
        }

        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
            break;
        }
        /* Validate Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
        if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
            break;
        }
        PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
        uint8_t *pu8Payload = NULL;
        pu8Payload = &gau8RespBuffer[4];
        if (recvPkt->u8PktId == eOTP_WRITE + 0x80) {
            u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
            if (u16PktLen != 1) {
                T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
                T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
                rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
                break;
            }
            T_D(MEPA_TRACE_GRP_GEN, "Otp write done with len: %d", u16PktLen);
            u16CurLen += u16DataLen;
            u16OtpAddr += u16DataLen;
            u16Idx += u16DataLen;
            T_I(MEPA_TRACE_GRP_GEN, "OTP write success");
        } else if (recvPkt->u8PktId == eOTP_WRITE + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd Failed with %d", __FUNCTION__, pu8Payload[0]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
            break;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eOTP_WRITE);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
            break;
        }
    }

    return rc;
}

mepa_rc lan80xx_otp_getKey_Status(const mepa_device_t  *dev,
                                  enOTP_ACTIVE_KEY *pKey)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (pKey == NULL)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP get active key");
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(eOTP_KEY_STATUS, 0, au8CmdBuffer, NULL, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    if (recvPkt->u8PktId == eOTP_KEY_STATUS + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen != 1) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        *pKey = pu8Payload[0];
        switch (*pKey) {
        case eMCHP_PUB_KEY:
            /* MCHP Public key */
            T_D(MEPA_TRACE_GRP_GEN, "MCHP Public key is active");
            break;
        case eREPLACEMENT_KEY1:
            /* Reaplcement key 1 */
            T_D(MEPA_TRACE_GRP_GEN, "Replacement key 1 is active");
            break;
        case eREPLACEMENT_KEY2:
            /* Reaplcement key 2 */
            T_D(MEPA_TRACE_GRP_GEN, "Replacement key 2 is active");
            break;
        case eREPLACEMENT_KEY3:
            /* Reaplcement key 3 */
            T_D(MEPA_TRACE_GRP_GEN, "Replacement key 3 is active");
            break;
        case eALL_KEYS_COMPROMISED:
            /* Key None, all keys revoked */
            T_D(MEPA_TRACE_GRP_GEN, "All Keys compromised");
            break;
        default:
            /* Unknown data, Needs protocol update */
            T_E(MEPA_TRACE_GRP_GEN, "Needs protocol update!!");
            break;
        }
        T_I(MEPA_TRACE_GRP_GEN, "OTP Get key status success");
    } else if (recvPkt->u8PktId == eOTP_KEY_STATUS + 0x81) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd Failed with %d", __FUNCTION__, pu8Payload[0]);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
            __FUNCTION__, (recvPkt->u8PktId - 0x80), eOTP_KEY_STATUS);
        rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
    }

    return rc;
}

mepa_rc lan80xx_otp_revoke_AllKeys(const mepa_device_t  *dev,
                                   u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t u16OffsetAddr;
    uint8_t i;
    enOTP_ACTIVE_KEY KeyStatus;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Getting Key status...");
    rc = lan80xx_otp_getKey_Status(dev, &KeyStatus);
    if (rc == MEPA_RC_OK) {
        if (KeyStatus == eALL_KEYS_COMPROMISED) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - All OTP Keys revoked", __FUNCTION__);
            rc = MEPA_RC_ERR_OTP_ALL_KEY_COMPROMISED;
            return rc;
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s - OTP get key status failed", __FUNCTION__);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Revoking all otp keys...");
    rc = RevokeAllOtpKeys(dev);
    /*If revoke all keys command success, set register value for all keys compromised */
    if (rc != MEPA_RC_OK) {
        return rc;
    }
    for (i = 0; i < u8UpdateCnt - 1; i++) {
        T_D(MEPA_TRACE_GRP_GEN, "------ Sending OTP Writes ------");
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d offset 0X%X", i, pCfgUpdates[i].u16Offset);
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d len 0X%X", i, pCfgUpdates[i].u16Len);

        /* writeMode set to BUFF for Record, Index and PRG CTR updates */
        u16OffsetAddr = pCfgUpdates[i].u16Offset;
        rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, pCfgUpdates[i].u16Len, eOTPWRITE_BUFF);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "OTP Write failed");
            return rc;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "sending signature...");
    u16OffsetAddr = pCfgUpdates[i].u16Offset;
    rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, OTP_SIGNATURE_LEN, eOTPWRITE_AUTH);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Revoke OTP Keys failed with authentication");
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "Revoke OTP keys success");
    }

    return rc;
}

mepa_rc lan80xx_otp_revoke_ROTKey(const mepa_device_t  *dev,
                                  u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_OK;
    enOTP_ACTIVE_KEY KeyStatus;
    uint16_t u16OffsetAddr;
    uint8_t i;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Getting Key status...");
    rc = lan80xx_otp_getKey_Status(dev, &KeyStatus);
    if (rc == MEPA_RC_OK) {
        if (KeyStatus == eALL_KEYS_COMPROMISED) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - All OTP Keys revoked", __FUNCTION__);
            rc = MEPA_RC_ERR_OTP_ALL_KEY_COMPROMISED;
            return rc;
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s - OTP get key status failed", __FUNCTION__);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Revoking ROT key...");
    rc = RevokeRotKey(dev);
    /*IF revoke ROT key command success, set Key Revocation register bit */
    if (rc != MEPA_RC_OK) {
        return rc;
    }
    for (i = 0; i < u8UpdateCnt - 1; i++) {
        T_D(MEPA_TRACE_GRP_GEN, "------ Sending OTP Writes ------");
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d offset 0X%X", i, pCfgUpdates[i].u16Offset);
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d len 0X%X", i, pCfgUpdates[i].u16Len);

        /* writeMode set to BUFF for Record, Index and PRG CTR updates*/
        u16OffsetAddr = pCfgUpdates[i].u16Offset;
        rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, pCfgUpdates[i].u16Len, eOTPWRITE_BUFF);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "OTP Write failed");
            return rc;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "sending signature...");
    u16OffsetAddr = pCfgUpdates[i].u16Offset;
    rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, OTP_SIGNATURE_LEN, eOTPWRITE_AUTH);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Revoke OTP Keys failed with authentication");
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "Revoke ROT key success");
    }

    return rc;
}

mepa_rc lan80xx_otp_prog_RepKey(const mepa_device_t  *dev,
                                u8 *pu8SignedKey,
                                u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_OK;
    enOTP_ACTIVE_KEY KeyStatus;
    uint8_t u8KeyNo, i;
    uint16_t u16OffsetAddr;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Getting Key status...");
    rc = lan80xx_otp_getKey_Status(dev, &KeyStatus);
    if (rc == MEPA_RC_OK) {
        switch (KeyStatus) {
        case eMCHP_PUB_KEY:
            /* MCHP Public key */
            T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement Key 1...");
            u8KeyNo = ePROG_OTP_KEY1;
            break;
        case eREPLACEMENT_KEY1:
            /* Reaplcement key 1 */
            T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement Key 2...");
            u8KeyNo = ePROG_OTP_KEY2;
            break;
        case eREPLACEMENT_KEY2:
            /* Reaplcement key 2 */
            T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement Key 3...");
            u8KeyNo = ePROG_OTP_KEY3;
            break;
        case eREPLACEMENT_KEY3:
            /* Reaplcement key 3 */
            T_I(MEPA_TRACE_GRP_GEN, "No more key programming is allowed");
            rc = MEPA_RC_ERR_OTP_ALL_KEY_PROGRAMMED;
            break;
        case eALL_KEYS_COMPROMISED:
            /* Key None, all keys revoked */
            T_E(MEPA_TRACE_GRP_GEN, "%s - All OTP Keys revoked", __FUNCTION__);
            rc = MEPA_RC_ERR_OTP_ALL_KEY_COMPROMISED;
            break;
        default:
            /* Unknown data, Needs protocol update */
            T_E(MEPA_TRACE_GRP_GEN, "Needs protocol update!!");
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
            break;
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s - OTP get key status failed", __FUNCTION__);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    }
    if (rc != MEPA_RC_OK) {
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement key%d...", u8KeyNo);
    rc = OTPProgReplacementKey(dev, u8KeyNo, pu8SignedKey);

    for (i = 0; i < u8UpdateCnt - 1; i++) {
        T_D(MEPA_TRACE_GRP_GEN, "------ Sending OTP Writes ------");
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d offset 0X%X", i, pCfgUpdates[i].u16Offset);
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d len 0X%X", i, pCfgUpdates[i].u16Len);

        /* writeMode set to BUFF for Record, Index and PRG CTR updates*/
        u16OffsetAddr = pCfgUpdates[i].u16Offset;
        rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, pCfgUpdates[i].u16Len, eOTPWRITE_BUFF);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "OTP Write failed");
            return rc;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "sending signature...");
    u16OffsetAddr = pCfgUpdates[i].u16Offset;
    rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, OTP_SIGNATURE_LEN, eOTPWRITE_AUTH);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "program Replacement Key failed");
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement key%d success", u8KeyNo);
    }

    return rc;
}

mepa_rc lan80xx_otp_cfg_program(const mepa_device_t  *dev,
                                u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t u16OffsetAddr;
    uint8_t i;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    for (i = 0; i < u8UpdateCnt - 1; i++) {
        T_D(MEPA_TRACE_GRP_GEN, "------ Sending OTP Writes ------");
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d offset 0X%X", i, pCfgUpdates[i].u16Offset);
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d len 0X%X", i, pCfgUpdates[i].u16Len);

        /* writeMode set to BUFF for Record, Index and PRG CTR updates*/
        u16OffsetAddr = pCfgUpdates[i].u16Offset;
        rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, pCfgUpdates[i].u16Len, eOTPWRITE_BUFF);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "OTP Write failed");
            return rc;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "sending signature...");
    u16OffsetAddr = pCfgUpdates[i].u16Offset;
    rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, OTP_SIGNATURE_LEN, eOTPWRITE_AUTH);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "OTP cfg program failed");
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "OTP cfg program success");
    }

    return rc;
}

mepa_rc OTPProgReplacementKey(const mepa_device_t  *dev,
                              u8 u8KeyNo,
                              u8 *pu8KeyData)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[256] = { 0 };
    uint8_t u8CmdParam[OTP_REP_KEY_LEN + OTP_REP_KEY_SIGN_LEN] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (pu8KeyData == NULL)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP PRG replacement key");
    /* Copy the key data into cmdparam */
    T_D(MEPA_TRACE_GRP_GEN, "Copying key data...");
    memcpy(&u8CmdParam[0], pu8KeyData, OTP_REP_KEY_LEN + OTP_REP_KEY_SIGN_LEN);
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(u8KeyNo, OTP_REP_KEY_LEN + OTP_REP_KEY_SIGN_LEN, au8CmdBuffer, u8CmdParam, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_SIGN_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    if (recvPkt->u8PktId == u8KeyNo + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen != 1) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        T_I(MEPA_TRACE_GRP_GEN, "OTP PRG replacement key success");
    } else if (recvPkt->u8PktId == u8KeyNo + 0x81) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd Failed with %d", __FUNCTION__, pu8Payload[0]);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
            __FUNCTION__, (recvPkt->u8PktId - 0x80), u8KeyNo);
        rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
    }

    return rc;
}

mepa_rc RevokeAllOtpKeys(const mepa_device_t  *dev)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;
    const uint8_t u8PktId = eREVOKE_OTP_KEYS;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (dev == NULL) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP revoke all keys");
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(u8PktId, 0, au8CmdBuffer, NULL, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_SIGN_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[MB_PKT_DATA_OFFSET];

    if (recvPkt->u8PktId == u8PktId + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen != 1) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        T_I(MEPA_TRACE_GRP_GEN, "OTP revoke all keys success");
    } else if (recvPkt->u8PktId == u8PktId + 0x81) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd Failed with %d", __FUNCTION__, pu8Payload[0]);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
            __FUNCTION__, (recvPkt->u8PktId - 0x80), u8PktId);
        rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
    }

    return rc;
}

mepa_rc RevokeRotKey(const mepa_device_t  *dev)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;
    const uint8_t u8PktId = eREVOKE_ROT_KEY;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (dev == NULL) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP revoke ROT key");
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(u8PktId, 0, au8CmdBuffer, NULL, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_SIGN_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[MB_PKT_DATA_OFFSET];

    if (recvPkt->u8PktId == u8PktId + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen != 1) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        T_I(MEPA_TRACE_GRP_GEN, "OTP revoke ROT key success");
    } else if (recvPkt->u8PktId == u8PktId + 0x81) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd Failed with %d", __FUNCTION__, pu8Payload[0]);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
            __FUNCTION__, (recvPkt->u8PktId - 0x80), u8PktId);
        rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
    }

    return rc;
}

mepa_rc lan80xx_get_serdes_config(const mepa_device_t *dev, SD_CFG_SPEED_IDX_t speed, eSERDES_CFG_T cfgType, __SERDES_CONFIG_T *const data)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen = 0, u16PayloadLen = 0x00, u16Len = 0;
    uint8_t au8CmdParam[8] = { 0 };
    uint16_t u16CmdParamLen = 0;
    const uint8_t u8PktId = eGET_SERDES_CONFIG;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    au8CmdParam[u16CmdParamLen++] = speed;
    au8CmdParam[u16CmdParamLen++] = cfgType;
    // Step 1: Create Packet for Device Info
    u16PktLen = lan80xx_CreatePacket(u8PktId, u16CmdParamLen, au8CmdBuffer, au8CmdParam, RESERVED_ID);

    // Step 2: Send Request Packet
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    // Step 4: Validate Packet
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    unsigned char *pCfg = NULL;
    pCfg = (unsigned char *) &gau8RespBuffer[MB_PKT_DATA_OFFSET];
    /* Strip off the packet header length to get payload length */
    u16PayloadLen -= (MB_MAX_PKT_HEADER_LEN + MB_MAX_CRC_LEN);

    if (recvPkt->u8PktId == u8PktId + 0x80) {
        switch (cfgType) {
        case eTX_EQ_CFG:
            u16Len = sizeof(tx_eq_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *)&data->sTx_eq_cfg, (void *)pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eCDR_CFG:
            u16Len = sizeof(cdr_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sCdr_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eSPEED_CHANGE_CFG:
            u16Len = sizeof(speed_change_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sSpeed_change_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eRX_EQ_CFG:
            u16Len = sizeof(rx_eq_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sRx_eq_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eDFE_CFG:
            u16Len = sizeof(dfe_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sDfe_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case ePOL_SQ_CFG:
            u16Len = sizeof(pol_sq_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sPol_sq_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eTX_SWING_CFG:
            u16Len = sizeof(tx_swing_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sTx_swing_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eMISC_CFG:
            u16Len = sizeof(misc_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sMisc_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eALL_CFG:
            u16Len = sizeof(tx_eq_cfg_t) + sizeof(cdr_cfg_t) + sizeof(speed_change_cfg_t) +
                     sizeof(rx_eq_cfg_t) + sizeof(dfe_cfg_t) + sizeof(pol_sq_cfg_t) +
                     sizeof(tx_swing_cfg_t) + sizeof(misc_cfg_t);
            if (u16PayloadLen == u16Len) {
                u16Len = sizeof(tx_eq_cfg_t);
                memcpy((void *)&data->sTx_eq_cfg, (void *)pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(cdr_cfg_t);
                memcpy((void *) &data->sCdr_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(speed_change_cfg_t);
                memcpy((void *) &data->sSpeed_change_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(rx_eq_cfg_t);
                memcpy((void *) &data->sRx_eq_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(dfe_cfg_t);
                memcpy((void *) &data->sDfe_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(pol_sq_cfg_t);
                memcpy((void *) &data->sPol_sq_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(tx_swing_cfg_t);
                memcpy((void *) &data->sTx_swing_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(misc_cfg_t);
                memcpy((void *) &data->sMisc_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eUNKNOWN_CFG:
        default:
            T_E(MEPA_TRACE_GRP_GEN, "Invalid config type!!");
            rc = MESA_RC_ERROR;
            break;
        }
    } else {
        if (recvPkt->u8PktId == u8PktId + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), u8PktId);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
    }
    return rc;
}

mepa_rc lan80xx_set_serdes_config(const mepa_device_t *dev, SD_CFG_SPEED_IDX_t speed, eSERDES_CFG_T cfgType, const __SERDES_CONFIG_T *data)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[128] = { 0 };
    uint16_t u16PktLen = 0, u16PayloadLen = 0x00, u16Len = 0;
    uint8_t au8CmdParam[128] = { 0 };
    const uint8_t u8PktId = eSET_SERDES_CONFIG;
    uint16_t u16CmdParamLen = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    au8CmdParam[u16CmdParamLen++] = speed;
    au8CmdParam[u16CmdParamLen++] = cfgType;
    /* Increment len, as 2 cmd param added */
    unsigned char *pCfg = (unsigned char *) &au8CmdParam[u16CmdParamLen];
    switch (cfgType) {
    case eTX_EQ_CFG:
        u16Len = sizeof(tx_eq_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sTx_eq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eCDR_CFG:
        u16Len = sizeof(cdr_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sCdr_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eSPEED_CHANGE_CFG:
        u16Len = sizeof(speed_change_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sSpeed_change_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eRX_EQ_CFG:
        u16Len = sizeof(rx_eq_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sRx_eq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eDFE_CFG:
        u16Len = sizeof(dfe_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sDfe_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case ePOL_SQ_CFG:
        u16Len = sizeof(pol_sq_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sPol_sq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eTX_SWING_CFG:
        u16Len = sizeof(tx_swing_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sTx_swing_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eMISC_CFG:
        u16Len = sizeof(misc_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sMisc_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eALL_CFG:
        u16Len = sizeof(tx_eq_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sTx_eq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(cdr_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sCdr_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(speed_change_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sSpeed_change_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(rx_eq_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sRx_eq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(dfe_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sDfe_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(pol_sq_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sPol_sq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(tx_swing_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sTx_swing_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(misc_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sMisc_cfg, u16Len);
        u16CmdParamLen += u16Len;

        break;
    case eUNKNOWN_CFG:
    default:
        T_E(MEPA_TRACE_GRP_GEN, "Invalid config type!!");
        rc = MESA_RC_ERROR;
        return rc;
    }

    // Step 1: Create Packet for Device Info
    u16PktLen = lan80xx_CreatePacket(u8PktId, u16CmdParamLen, au8CmdBuffer, au8CmdParam, RESERVED_ID);

    // Step 2: Send Request Packet
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    // Step 4: Validate Packet
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];

    if (recvPkt->u8PktId == u8PktId + 0x80) {
        T_I(MEPA_TRACE_GRP_GEN, "SD Config set success\n");
    } else {
        if (recvPkt->u8PktId == u8PktId + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[4]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), u8PktId);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
    }
    return rc;
}
